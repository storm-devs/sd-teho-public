// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
    {
    case "quests":
        dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Какие вопросы?", "Что вам угодно, " + GetAddress_Form(NPChar) + "?"), "Совсем недавно вы пытались задать мне вопрос " + GetAddress_Form(NPChar) + "...", "В течение этого дня вы уже третий раз говорите о каком-то вопросе...",
                                              "Послушайте, если вы не по делам порта, то не стоит меня вопросами донимать.", "block", 1, npchar, Dialog.CurrentNode);
        link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Я передумал" + GetSexPhrase("", "а") + "...", "Сейчас мне не о чем говорить"), "Хм, что-то с памятью моей стало...",
                                           "Да уж, действительно в третий раз...", "Извините, но портовые дела меня сейчас не интересуют.", npchar, Dialog.CurrentNode);
        link.l1.go = "exit";

        //работорговец
        if (pchar.questTemp.Slavetrader == "EscapeSlaveVillemstad_P")
        {
            link.l1 = "Я бы хотел" + GetSexPhrase("", "а") + " узнать по поводу барка, пропавшего в ночь после восстания рабов.";
            link.l1.go = "EscapeSlave_Villemstad_P1";
        }
        //Голландский гамбит, против всех
        if (CheckAttribute(pchar, "questTemp.HWIC.Self") && pchar.questTemp.HWIC.Self == "SeekFleut")
        {
            link.l1 = "Я бы хотел найти капитана по имени Тофф Келлер. У него флейт под названием 'Лейден'. Я совершенно точно знаю, что он периодически бывает в Виллемстаде, так что, думаю, помочь мне для вас труда не составит.";
            link.l1.go = "SeekTradeFleut";
        }
        break;

    //работорговец
    case "EscapeSlave_Villemstad_P1":
        dialog.text = "Хм... А с какой стати вдруг это вас заинтересовало?";
        link.l1 = "Я действую по указаниям Матиаса Бека, губернатора. Есть основания полагать, что к исчезновению корабля причастны беглые рабы. Поэтому я прошу вас оказать мне всё возможное содействие в розысках.";
        link.l1.go = "EscapeSlave_Villemstad_P2";
        break;

    case "EscapeSlave_Villemstad_P2":
        dialog.text = "Понятно. Но, к сожалению, я мало чем могу вам помочь. Барк с именем " + pchar.questTemp.Slavetrader.ShipName + ", пропал ночью, никто ничего не видел и не слышал. Вахтенный исчез бесследно\nРозыск корабля по горячим следам ничего не дал, собственно, потому что никаких следов не было. Город был взбудоражен, все ожидали нападения рабов, готовились к обороне...";
        link.l1 = "Да уж, действительно информации немного. Но спасибо и на этом. До свидания.";
        link.l1.go = "exit";
        AddQuestRecord("Slavetrader", "22_3");
        AddQuestUserData("Slavetrader", "sShipName", pchar.questTemp.Slavetrader.ShipName);
        pchar.questTemp.Slavetrader = "EscapeSlaveVillemstad_H";
        break;
    //Голландский гамбит
    case "SeekTradeFleut":
        dialog.text = "Тофф Келлер? Ну конечно же я его знаю! Он совершает регулярные рейсы между Виллемстадом, Сан-Хосе на Тринидаде и Куманой. Недавно он отбыл на Тринидад. Думаю, что вы там его найдёте.";
        link.l1 = "Спасибо!";
        link.l1.go = "SeekTradeFleut_1";
        break;

    case "SeekTradeFleut_1":
        DialogExit();
        pchar.questTemp.HWIC.Self = "FleutOnTrinidad";
        AddQuestRecord("Holl_Gambit", "3-59");
        pchar.quest.Seek_Fleut.win_condition.l1 = "location";
        pchar.quest.Seek_Fleut.win_condition.l1.location = "Trinidad";
        pchar.quest.Seek_Fleut.function = "CreateTradeFleut";
        break;
    }
    UnloadSegment(NPChar.FileDialog2); // если где-то выход внутри switch  по return не забыть сделать анлод
}
