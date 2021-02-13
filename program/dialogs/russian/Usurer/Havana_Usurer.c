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
        // калеуче
        if (CheckAttribute(pchar, "questTemp.Caleuche") && pchar.questTemp.Caleuche == "graveyard" && !CheckAttribute(npchar, "quest.caleuche"))
        {
            link.l1 = "Послушайте, к вам не обращался человек по имени Жоаким Мерриман? Немолодой сеньор, португалец, носит усы и эспаньолку, с пронзительным взглядом? Может, хотел денег занять, или в рост положить?";
            link.l1.go = "caleuche";
        }
        break;

    // калеуче
    case "caleuche":
        dialog.text = "Боюсь, что ничем не смогу помочь вам, молодой человек. Я представления не имею человеке, о котором вы спрашиваете.";
        link.l1 = "Ясно. Жаль. Буду искать дальше...";
        link.l1.go = "exit";
        npchar.quest.caleuche = "true";
        break;
    }
    UnloadSegment(NPChar.FileDialog2); // если где-то выход внутри switch  по return не забыть сделать анлод
}
