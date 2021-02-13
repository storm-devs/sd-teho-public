// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
    {
    case "quests":
        dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Какие вопросы?", "Что вам угодно?"), "Совсем недавно вы пытались задать мне вопрос...", "У себя на верфи, а и вообще в городе, я таких однообразно любознательных не видал.",
                                              "Ну что за вопросы? Мое дело - корабли строить, давайте этим и займемся.", "block", 1, npchar, Dialog.CurrentNode);
        link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Я " + GetSexPhrase("передумал", "передумала") + "...", "Сейчас мне не о чем говорить."), "Хм, что-то с памятью моей стало...",
                                           "Хм, однако...", "Давайте...", npchar, Dialog.CurrentNode);
        link.l1.go = "exit";
        //Голландский гамбит
        if (CheckAttribute(pchar, "questTemp.HWIC.Eng") && pchar.questTemp.HWIC.Eng == "GotoBridgetown" && !CheckAttribute(npchar, "quest.HWICTalked"))
        {
            link.l1 = "Я тут направляюсь в Блювельд с грузом кофе, и хочу докупить еще товара, но вот незадача: на этом бриге, который я купил у вояки, просто безобразное количество тяжелых пушек, целых 24 штуки. Я же не на войну собрался? Я хочу продать тебе их все, и купить 12 шестифунтовок - вполне достаточно, чтобы припугнуть пиратов. А освободившееся место заполню товаром.";
            link.l1.go = "ShipyardDone";
        }
        break;

    case "ShipyardDone":
        dialog.text = "Да пожалуйста, продавай. Шестифунтовок у меня всегда хватает, а вот с тяжелыми пушками проблема, так что заплачу тебе за них неплохую цену, если они, конечно, еще в годном состоянии.";
        link.l1 = "Вот и отлично! Пойду отдавать распоряжения.";
        link.l1.go = "exit";
        npchar.quest.HWICTalked = "true";
        pchar.questTemp.HWIC.Eng.BridgeCounter = sti(pchar.questTemp.HWIC.Eng.BridgeCounter) + 1;
        AddQuestRecord("Holl_Gambit", "2-10");
        if (sti(pchar.questTemp.HWIC.Eng.BridgeCounter) == 7)
        {
            AddQuestRecord("Holl_Gambit", "2-6");
            pchar.quest.GotoBridgetownOver.over = "yes"; //снять таймер
            pchar.questTemp.HWIC.Eng = "SeekVanBerg";
            pchar.quest.VanBergAttack_Check.win_condition.l1 = "MapEnter";
            pchar.quest.VanBergAttack_Check.function = "VanBergAttackCheck";
            //if(sti(RealShips[sti(pchar.ship.type)].basetype) != SHIP_VALCIRIA || GetCompanionQuantity(pchar) > 1) AddDialogExitQuestFunction("FailVanBergInWorld");
            //else AddDialogExitQuestFunction("CreateVanBergInWorld");
        }
        break;
    }
    UnloadSegment(NPChar.FileDialog2); // если где-то выход внутри switch  по return не забыть сделать анлод
}
