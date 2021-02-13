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
        // Jason Дороже золота
        if (CheckAttribute(pchar, "questTemp.GoldenGirl") && pchar.questTemp.GoldenGirl == "antigua")
        {
            link.l1 = "Ваша светлость, я прибыл сообщить, что располагаю информацией о пропаже бригантины 'Меркьюри'.";
            link.l1.go = "G_Girl";
        }
        break;

    // Jason Дороже золота
    case "G_Girl":
        dialog.text = "Информацией? О пропаже, простите, чего?";
        link.l1 = "Бригантины, ваша светлость. Перевозившей кап... почту. Важные документы. Я слышал, ведется расследование, и, как верный друг британской короны, не могу не поделиться важными сведениями.";
        link.l1.go = "G_Girl_1";
        break;

    case "G_Girl_1":
        dialog.text = "Замечательно! Баронет Кортни будет вам очень рад! Я немедленно организую встречу.";
        link.l1 = "Спасибо, сэр. Я немного спешу, так что буду благодарен, если все пройдет быстро.";
        link.l1.go = "G_Girl_2";
        break;

    case "G_Girl_2":
        dialog.text = "Не волнуйтесь, времени у вас будет в достатке. Стража! Взять его!";
        link.l1 = "Я весьма вам... что, простите? Это что, шутка?!";
        link.l1.go = "G_Girl_3";
        break;

    case "G_Girl_3":
        DialogExit();
        GoldenGirl_AntiguaArest();
        break;
    }
    UnloadSegment(NPChar.FileDialog2); // если где-то выход внутри switch  по return не забыть сделать анлод
}
