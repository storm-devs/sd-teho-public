// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    ref sld;
    int i, tempQty, chComp, iShip, iBaseType;
    string tempStr;
    switch (Dialog.CurrentNode)
    {
    case "quests":
        //Португалец
        if (CheckAttribute(pchar, "questTemp.Portugal.Villemstad") && pchar.location == "villemstad_townhall")
        {
            dialog.text = RandPhraseSimple("Какие вопросы?", "Что вам угодно?");
            link.l1 = "Я знаю, что Голландская Вест-Индская торговая Компания назначила хорошую цену за голову одного пирата, а именно - Бартоломео Португальца. Мне удалось схватить его. Сейчас он находится в трюме моего корабля и я готов выдать его властям.";
            link.l1.go = "Portugal";
            break;
        }
        dialog.text = RandPhraseSimple("Какие вопросы?", "Что вам угодно?");
        link.l1 = RandPhraseSimple("Я передумал" + GetSexPhrase("", "а") + "...", "Сейчас мне не о чем говорить");
        link.l1.go = "exit";
        break;

    case "work_1": // работа на благо короны - линейка нации
        if (CheckAttribute(npchar, "notQuestLine"))
        {
            dialog.text = "К сожалению, я не могу предоставить вам работу. Вы не тот человек, кому я хотел бы доверить свои дела. До свидания.";
            link.l1 = "Вот это да...";
            link.l1.go = "exit";
            break;
        }
        break;

    //Португалец
    case "Portugal":
        dialog.text = "Барт Португалец?! Он у вас? Живой?";
        link.l1 = "Я в курсе, что мёртвым он вам не нужен. Живой. И мне пришлось приложить немало усилий, чёрт побери, чтобы он дожил до этого дня!";
        link.l1.go = "Portugal_1";
        break;

    case "Portugal_1":
        dialog.text = "Великолепно! Теперь он всё расскажет... Минхер, распорядитесь подготовить пленника к перевозке на берег. Мы немедленно подадим военную барку к борту вашего судна.";
        link.l1 = "Я бы хотел сначала обсудить вопрос моей награды, минхер... Если вы не возражаете.";
        link.l1.go = "Portugal_2";
        break;

    case "Portugal_2":
        dialog.text = "Сударь, вы можете не сомневаться - награду вы получите. За голову Бартоломео Португальца мы установили награду - полторы тысячи золотых дублонов. Лейтенант! Принести господину капитану его вознаграждение!";
        link.l1 = "Хм... Значит, Хьюго соврал мне о двух тысячах дублонов... Ладно, полторы - значит, полторы.";
        link.l1.go = "Portugal_3";
        break;

    case "Portugal_3":
        TakeNItems(pchar, "gold_dublon", 1500);
        Log_Info("Вы получили 1500 дублонов");
        PlaySound("interface\important_item.wav");
        dialog.text = "А теперь будьте так любезны, капитан, передать Компании Португальца. Нам просто не терпится начать с ним беседу.";
        link.l1 = "Конечно, минхер. Отправляйте барку с солдатами к моему кораблю.";
        link.l1.go = "Portugal_4";
        break;

    case "Portugal_4":
        DialogExit();
        DoQuestReloadToLocation("Villemstad_town", "reload", "reload1", "Portugal_Final");
        DeleteAttribute(pchar, "questTemp.Portugal.Villemstad");
        break;
    }
    UnloadSegment(NPChar.FileDialog2); // если где-то выход внутри switch  по return не забыть сделать анлод
}
