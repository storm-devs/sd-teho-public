
void ProcessDialogEvent()
{
    ref NPChar;
    aref Link, NextDiag;
    string sTemp;
    bool bOk;

    DeleteAttribute(&Dialog, "Links");

    makeref(NPChar, CharacterRef);
    makearef(Link, Dialog.Links);
    makearef(NextDiag, NPChar.Dialog);

    switch (Dialog.CurrentNode)
    {
    case "First time":
        dialog.text = "Не о чем говорить!";
        link.l1 = "...";
        link.l1.go = "exit";
        NextDiag.TempNode = "First time";
        break;

    case "Exit":
        NextDiag.CurrentNode = NextDiag.TempNode;
        DialogExit();
        break;

    // ==> пиплы в поселении
    case "PearlMan":
        NextDiag.TempNode = "PearlMan";
        dialog.text = NPCStringReactionRepeat("Приветствую! Меня зовут " + GetFullName(npchar) + ". Чем я могу тебе помочь?",
                                              "Приветствую еще раз!",
                                              "В нашей глуши гости очень редки...",
                                              "Эх, приятно поболтать с новым человеком! А то эти морды уже опротивели.", "block", 1, npchar, Dialog.CurrentNode);
        link.l1 = HeroStringReactionRepeat("Да ничем особенным...",
                                           "И я тебя тоже...",
                                           "Понимаю.",
                                           "Хех...", npchar, Dialog.CurrentNode);
        link.l1.go = "PearlMan_1";
        break;
    case "PearlMan_1":
        dialog.text = "Мы тут жемчуг добываем, служим " + NationNameGenitive(sti(npchar.nation)) + ", такое вот дело...";
        link.l1 = "Да, я в курсе...";
        link.l1.go = "exit";
        link.l2 = "Слушай, а нельзя ли прикупить немного этих безделушек у производителя, так сказать, а?";
        link.l2.go = "PearlMan_2";
        break;
    case "PearlMan_2":
        if (rand(10) < 9)
        {
            dialog.text = "Да нет, что ты!!! За кражу даже одной маленькой жемчужины - смерть!";
            link.l1 = "Хех, порядки тут у вас жестокие...";
            link.l1.go = "exit";
        }
        else
        {
            dialog.text = "У нас с этим делом жестко, можно запросто лишиться головы. Я этим не занимаюсь, но могу посоветовать тебе обратиться к местным индейцам, что работают вместе с нами. Им есть куда бежать в случае чего, они посмелее нас будут...";
            link.l1 = "Понятно, ну спасибо тебе.";
            link.l1.go = "exit";
        }
        break;
    case "PearlMan_Sharp_1":
        dialog.text = LinkRandPhrase("Ты чего, на голову " + GetSexPhrase("больной? Иди отсюда, придурок", "больная? Иди отсюда, дура") + "!",
                                     "" + GetSexPhrase("Чего?!! Ты, часом, белены не объелся, идиот", "Чего?!! Ты, часом, белены не объелась, дуреха") + "?! Вали отсюда со своими вопросами...",
                                     "" + GetSexPhrase("Ты в своем уме, родной? Какие пираты?! У нас?!! Шел бы ты отсюда, малахольный", "Ты в своем уме, родная? Какие пираты?! У нас?!! Шла бы ты отсюда, милочка") + "...");
        link.l1 = RandPhraseSimple("Не надо хамить...", "Что за выражения?!");
        link.l1.go = "exit";
        break;

    // ==> индейцы в поселении
    case "IndPearlMan":
        NextDiag.TempNode = "IndPearlMan";
        dialog.text = NPCStringReactionRepeat("" + GetSexPhrase("Бледнолицый", "Белая скво") + " хочет говорить?",
                                              "Снова ты, " + GetSexPhrase("бледнолицый", "белая скво") + ".",
                                              "" + GetSexPhrase("Бледнолицый любит говорить. Он похож на скво.", "Белая скво любит говорить.") + "",
                                              "Духи привели ко мне бледнолиц" + GetSexPhrase("его брата", "ую сестру") + ".", "block", 1, npchar, Dialog.CurrentNode);
        link.l1 = HeroStringReactionRepeat("Да.",
                                           "Да, снова я.",
                                           "Очень поэтично.",
                                           "Я тоже рад" + GetSexPhrase("", "а") + " тебя видеть.", npchar, Dialog.CurrentNode);
        link.l1.go = "IndPearlMan_1";
        break;
    case "IndPearlMan_1":
        dialog.text = "Говори, зачем приш" + GetSexPhrase("ел", "ла") + ".";
        link.l1 = "Да ничего особенного, послушать тебя хотел" + GetSexPhrase("", "а") + "...";
        link.l1.go = "exit";
        break;

    case "CitizenNotBlade":
        dialog.text = "Капитан, что за глупости! Уберите оружие, пока бед не наделали!";
        link.l1 = LinkRandPhrase("Хорошо.", "Ладно.", "Не переживай, уже убираю...");
        link.l1.go = "exit";
        break;
    }
}
