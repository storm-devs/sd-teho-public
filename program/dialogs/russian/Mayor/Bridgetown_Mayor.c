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
        //Голландский гамбит
        if (CheckAttribute(pchar, "questTemp.HWIC.Eng") && pchar.questTemp.HWIC.Eng == "GotoBridgetown" && !CheckAttribute(npchar, "quest.HWICTalked"))
        {
            link.l1 = "Я совершил на Мартинике выгодную сделку, и сейчас в мои планы входит отправиться в Блювельд. Я намерен закупить в вашей колонии красное дерево и кофе. Кроме того, моего брига недостаточно для партии товара, которую я хочу купить - мне нужно приобрести на вашей верфи флейт. Вы не могли бы оказать мне содействие в этих вопросах?";
            link.l1.go = "MayorDone";
        }
        break;

    case "MayorDone":
        dialog.text = "Моё содействие? Наш купец - весьма честный человек, я не думаю, что он будет пытаться вас обжулить. Что касается флейта - поговорите с хозяином верфи, думаю, он сможет вам помочь. Ну, а если всё-таки у вас возникнут проблемы - тогда приходите ко мне. Я заинтересован в развитии торговых связей с нашей колонией и окажу вам свою поддержку\nДа, я сегодня вечером организую званый вечер, будут все сливки Бриджтауна. Приходите  и вы, капитан.";
        link.l1 = "Благодарю за приглашение, но у меня, к сожалению, не получится - очень много дел. До свидания и спасибо за поручительство!";
        link.l1.go = "exit";
        npchar.quest.HWICTalked = "true";
        pchar.questTemp.HWIC.Eng.BridgeCounter = sti(pchar.questTemp.HWIC.Eng.BridgeCounter) + 1;
        AddQuestRecord("Holl_Gambit", "2-8");
        if (sti(pchar.questTemp.HWIC.Eng.BridgeCounter) == 7)
        {
            AddQuestRecord("Holl_Gambit", "2-6");
            pchar.questTemp.HWIC.Eng = "SeekVanBerg";
            pchar.quest.GotoBridgetownOver.over = "yes"; //снять таймер
            pchar.quest.VanBergAttack_Check.win_condition.l1 = "MapEnter";
            pchar.quest.VanBergAttack_Check.function = "VanBergAttackCheck";
            //if(sti(RealShips[sti(pchar.ship.type)].basetype) != SHIP_VALCIRIA || GetCompanionQuantity(pchar) > 1) AddDialogExitQuestFunction("FailVanBergInWorld");
            //else AddDialogExitQuestFunction("CreateVanBergInWorld");
        }
        break;
    }
    UnloadSegment(NPChar.FileDialog2); // если где-то выход внутри switch  по return не забыть сделать анлод
}
