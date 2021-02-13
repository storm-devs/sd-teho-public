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
        //Португалец
        if (CheckAttribute(pchar, "questTemp.Portugal.Villemstad"))
        {
            link.l1 = "Я знаю, что Голландская Вест-Индская торговая Компания назначила хорошую цену за голову одного пирата, а именно - Бартоломео Португальца. Мне удалось схватить его. Сейчас он находится в трюме моего корабля и я готов выдать его властям.";
            link.l1.go = "Portugeze";
        }
        break;

    case "Cupture_after":
        dialog.text = RandPhraseSimple("Вы уже всё забрали. Что вам ещё нужно?", "Неужели осталось ещё что-то, что вы не прихватили?");
        link.l1 = RandPhraseSimple("Осматриваюсь напоследок...", "Проверяю, может забыл" + GetSexPhrase("", "а") + " что забрать...");
        link.l1.go = "exit";
        NextDiag.TempNode = "Cupture_after";
        break;

    //Португалец
    case "Portugeze":
        dialog.text = "Барт Португалец?! Он у вас? Живой?";
        link.l1 = "Я в курсе, что мёртвым он вам не нужен. Живой. И мне пришлось приложить немало усилий, чёрт побери, чтобы он дожил до этого дня!";
        link.l1.go = "Portugeze_1";
        break;

    case "Portugeze_1":
        dialog.text = "Великолепно! Теперь он всё расскажет... Минхер, распорядитесь подготовить пленника к перевозке на берег. Мы немедленно подадим военную барку к борту вашего судна.";
        link.l1 = "Я бы хотел сначала обсудить вопрос моей награды, минхер... Если вы не возражаете.";
        link.l1.go = "Portugeze_2";
        break;

    case "Portugeze_2":
        dialog.text = "Сударь, вы можете не сомневаться - награду вы получите. За голову Бартоломео Португальца мы установили награду - полторы тысячи золотых дублонов. Лейтенант! Принести господину капитану его вознаграждение!";
        link.l1 = "Хм... Значит, Хьюго соврал мне о двух тысячах дублонов... Ладно, полторы - значит, полторы.";
        link.l1.go = "Portugeze_3";
        break;

    case "Portugeze_3":
        TakeNItems(pchar, "gold_dublon", 1500);
        Log_Info("Вы получили 1500 дублонов");
        PlaySound("interface\important_item.wav");
        dialog.text = "А теперь будьте так любезны, капитан, передать Компании Португальца. Нам просто не терпится начать с ним беседу.";
        link.l1 = "Конечно, минхер. Отправляйте барку с солдатами к моему кораблю.";
        link.l1.go = "Portugeze_4";
        break;

    case "Portugeze_4":
        DialogExit();
        DoQuestReloadToLocation("Villemstad_town", "reload", "reload1", "Portugal_Final");
        DeleteAttribute(pchar, "questTemp.Portugal.Villemstad");
        break;
    }
    UnloadSegment(NPChar.FileDialog2); // если где-то выход внутри switch  по return не забыть сделать анлод
}