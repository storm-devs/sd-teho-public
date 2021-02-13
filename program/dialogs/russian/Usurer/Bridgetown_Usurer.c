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
        //Голландский гамбит
        if (CheckAttribute(pchar, "questTemp.HWIC.Eng") && pchar.questTemp.HWIC.Eng == "GotoBridgetown" && !CheckAttribute(npchar, "quest.HWICTalked"))
        {
            link.l1 = "Я направляюсь в Блювельд с грузом вина. Но тут у знакомого капитана узнал, что в Блювельде резко возрос спрос на кофе, уж не знаю, с чем это связано. Я вот и думаю продать вино и закупить вместо него кофе, но денег мне не хватает, чтобы заполнить трюмы доверху. Можно ли взять у вас деньги под процент?";
            link.l1.go = "UsurerDone";
        }
        break;

    case "UsurerDone":
        dialog.text = "Кредит для уважаемого негоцианта - это всегда пожалуйста. Какая сумма вам нужна? Давайте обсудим.";
        link.l1 = "Хорошо. Я загружу трюмы, посчитаю, сколько еще останется места, прикину недостающую сумму и приду к вам.";
        link.l1.go = "exit";
        npchar.quest.HWICTalked = "true";
        pchar.questTemp.HWIC.Eng.BridgeCounter = sti(pchar.questTemp.HWIC.Eng.BridgeCounter) + 1;
        AddQuestRecord("Holl_Gambit", "2-13");
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
