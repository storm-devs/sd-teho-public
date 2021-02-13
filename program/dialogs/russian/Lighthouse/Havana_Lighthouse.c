// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
    {
    case "quests":
        dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Что вам угодно?", "Что вы хотели узнать?"), "Так скажите, что же вас интересует, " + GetAddress_Form(NPChar) + "?", "Третий раз за сегодня вы пытаетесь задать вопрос...", "Всё, вы меня утомили. Покиньте мой дом!", "block", 1, npchar, Dialog.CurrentNode);
        link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Я передумал" + GetSexPhrase("", "а") + "...", "Сейчас мне не о чем говорить"), "Ох, что-то я запамятовал. Простите...",
                                           "Да уж, действительно в третий раз...", "Извиняюсь...", npchar, Dialog.CurrentNode);
        link.l1.go = "exit";
        // калеуче
        if (CheckAttribute(pchar, "questTemp.Caleuche") && pchar.questTemp.Caleuche == "graveyard" && !CheckAttribute(npchar, "quest.caleuche"))
        {
            link.l1 = "Послушай, сюда не прибывал человек по имени Жоаким Мерриман? Немолодой сеньор, португалец, носит усы и эспаньолку, с пронзительным взглядом? Может, в бухте высадился, или на маяке? Не видал такого?";
            link.l1.go = "merriman";
        }
        break;

    // калеуче
    case "merriman":
        dialog.text = "Нет, дружище, не видал. Мне никто такой на глаза не попадался.";
        link.l1 = "Ясно. Жаль. Буду искать дальше...";
        link.l1.go = "exit";
        npchar.quest.caleuche = "true";
        break;
    }
    UnloadSegment(NPChar.FileDialog2);
}
