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
        // Addon-2016 Jason, французские миниквесты (ФМК) Тортуга
        if (CheckAttribute(pchar, "questTemp.FMQT") && pchar.questTemp.FMQT == "huber")
        {
            link.l1 = "Месье губернатор, у меня для вас неприятные известия. Буду краток: ваша жена хочет вас ограбить. Она пыталась подрядить меня на взлом одного из ваших сундуков. Считаю своим долгом вам об этом сообщить.";
            link.l1.go = "FMQT";
        }
        // Jason НСО
        if (CheckAttribute(pchar, "questTemp.Patria") && pchar.questTemp.Patria == "epizode_2" && !CheckAttribute(npchar, "quest.patria") && !CheckAttribute(pchar, "questTemp.Patria.Visiter_Late"))
        {
            link.l1 = TimeGreeting() + ", ваша светлость. Я прибыл по приказанию генерал-губернатора шевалье де Пуанси. В мою задачу входит доставить на Тортугу барона Ноэля Форже, прибывшего из метрополии с целью инспекции французских колоний для последующей огранизации Французской Вест-Индской торговой Компании. Позвольте представить вам барона... Всё дальнейшее изложит вам непосредственно он сам.";
            link.l1.go = "patria_tortuga";
        }
        break;

    case "FMQT":
        dialog.text = "Что-о-о? Опять? Тварь! Этот раз она не забудет, я позабочусь об этом. Кампачо заставит её вопить. А ты что ещё тут делаешь? Вон!";
        link.l1 = "Я думал, что...";
        if (GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) > 25)
            link.l1.go = "FMQT_2";
        else
            link.l1.go = "FMQT_1";
        break;

    case "FMQT_1":
        AddMoneyToCharacter(pchar, 1000);
        dialog.text = "Всем вам нужно одно и то же! Держи, это всё, что лежит у меня в столе! А теперь проваливай!";
        link.l1 = "Спасибо, ваша милость. Проваливаю.";
        link.l1.go = "FMQT_3";
        break;

    case "FMQT_2":
        AddMoneyToCharacter(pchar, 1000);
        GiveItem2Character(pchar, "pistol6");
        GiveItem2Character(pchar, "purse1");
        Log_Info("Вы получили двуствольный пистолет и кошель дублонов");
        dialog.text = "Всем вам нужно одно и то же! Держи, это всё, что лежит у меня в столе!.. Хотя, ладно, ты вроде не из этих идиотов и неудачников, которыми набит мой остров. Держи ещё сверху... А теперь проваливай!";
        link.l1 = "Спасибо, ваша милость. Проваливаю.";
        link.l1.go = "FMQT_3";
        break;

    case "FMQT_3":
        DialogExit();
        pchar.quest.FMQT_late1.over = "yes";
        ChangeCharacterNationReputation(pchar, FRANCE, 5);
        ChangeCharacterComplexReputation(pchar, "nobility", 2);
        pchar.questTemp.FMQT = "end";
        FMQ_Count();
        AddQuestRecord("FMQ_Tortuga", "7");
        CloseQuestHeader("FMQ_Tortuga");
        FMQT_ClearChest();
        break;

    // Jason НСО
    case "patria_tortuga":
        dialog.text = "Хорошо, капитан Шарль де Мор. Барону с моей стороны будет оказан соответствующий его положению приём и содействие в выполнении его требований.";
        link.l1 = "";
        link.l1.go = "patria_tortuga_1";
        break;

    case "patria_tortuga_1":
        DialogExit();
        sld = characterFromId("Noel");
        sld.dialog.currentnode = "noel_5";
        ChangeCharacterAddressGroup(sld, pchar.location, "goto", "governor1");
        LAi_SetActorType(sld);
        LAi_ActorDialogDelay(sld, pchar, "", 1.0);
        npchar.quest.patria = "true";
        break;
    }
    UnloadSegment(NPChar.FileDialog2); // если где-то выход внутри switch  по return не забыть сделать анлод
}
