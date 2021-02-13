
void ProcessDialogEvent()
{
    ref NPChar;
    aref Link, NextDiag, arRld, arDis;
    int i, Qty;

    DeleteAttribute(&Dialog, "Links");

    makeref(NPChar, CharacterRef);
    makearef(Link, Dialog.Links);
    makearef(NextDiag, NPChar.Dialog);

    switch (Dialog.CurrentNode)
    {
    case "Exit":
        NextDiag.CurrentNode = NextDiag.TempNode;
        DialogExit();
        break;

    case "exit_setOwner":
        LAi_SetOwnerTypeNoGroup(npchar);
        NextDiag.CurrentNode = NextDiag.TempNode;
        DialogExit();
        break;

    case "fight":
        NextDiag.CurrentNode = NextDiag.TempNode;
        DialogExit();
        LAi_SetOwnerTypeNoGroup(npchar);
        LAi_group_Attack(NPChar, Pchar);
        if (rand(3) != 1)
            SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
        AddDialogExitQuest("MainHeroFightModeOn");
        break;
    //--------------------------------- леди в резиденции ---------------------------------
    case "ResWoman":
        NextDiag.TempNode = "ResWoman";
        if (isBadReputation(pchar, 30))
        {
            dialog.text = LinkRandPhrase("Вот это да! Отпетый мерзавец - и у меня в покоях! Убирайся немедленно, не то позову стражу!", "Кошмар какой-то... И как эту пакость вообще пустили в мой дом? Прочь, негодяй! Нечего здесь шастать! Пошел вон!!", "Ну и времена настали. Всякая мерзость заглядывает ко мне прямо в спальню! Вон!!");
            link.l1 = RandPhraseSimple("Полегче...", "Аккуратней в выражениях...");
            link.l1.go = "exit";
        }
        else
        {
            dialog.text = LinkRandPhrase("Что вы делаете в моей спальне? Уходите отсюда немедленно!", "Что за бестактность! Попрошу вас немедленно покинуть мои покои!", "Простите, сударь, но вас сюда не приглашали. Потрудитесь покинуть помещение!");
            link.l1 = RandPhraseSimple("Простите... Я уже ухожу.", "Извините, я ошибся дверью. Ухожу.");
            link.l1.go = "exit";
        }
        break;
    case "Woman_FackYou":
        dialog.text = "Ой, что же это делается?! А я-то, дура, хожу, ничего не замечаю... Охрана!!!";
        link.l1 = "Заткнись, дура...";
        link.l1.go = "exit_setOwner";
        LAi_group_Attack(NPChar, Pchar);
        if (rand(3) != 1)
            SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
        break;
    //--------------------------------- слуга в резиденции ---------------------------------
    case "ResMan":
        NextDiag.TempNode = "ResMan";
        if (isBadReputation(pchar, 30))
        {
            dialog.text = LinkRandPhrase("" + GetSexPhrase("Пошел вон отсюда, мерзавец", "Пошла вон отсюда, мерзавка") + "!", "Немедленно убирайся из дома губернатора, " + GetSexPhrase("негодяй", "негодяйка") + "!", "Мне нет дела до того, что тебе нужно в доме губернатора " + XI_ConvertString("Colony" + npchar.city + "Gen") + ". Но дам тебе совет - убирайся отсюда!");
            link.l1 = RandPhraseSimple("Полегче, родной...", "Смотри, не подавись своими словами!");
            link.l1.go = "exit";
        }
        else
        {
            dialog.text = LinkRandPhrase("Здравствуйте. Я - слуга губернатора. Меня зовут " + GetFullName(NPChar) + ".", "Я присматриваю здесь за порядком, " + GetAddress_Form(NPChar) + ".", "Вы знаете, " + GetAddress_Form(NPChar) + ", наш губернатор - хороший человек, и неплохо платит прислуге...");
            link.l1 = RandPhraseSimple("Очень хорошо.", "Хм, прекрасно...");
            link.l1.go = "exit";
        }
        break;
    case "Man_FackYou":
        dialog.text = "Да ты никак " + GetSexPhrase("вздумал", "вздумала") + " обворовать губернатора?! Охрана, держи " + GetSexPhrase("вора", "воровку") + "!!";
        link.l1 = "Закрой пасть...";
        link.l1.go = "fight";
        LAi_group_Attack(NPChar, Pchar);
        if (rand(3) != 1)
            SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
        break;
    //--------------------------------- солдат в резиденции ---------------------------------
    case "ResGuard":
        NextDiag.TempNode = "ResGuard";
        if (isBadReputation(pchar, 30))
        {
            dialog.text = LinkRandPhrase("" + GetSexPhrase("Шел бы отсюда, приятель", "Шла бы отсюда, подруга") + "...", "Проваливай отсюда!", "Ты, часом, дверью не " + GetSexPhrase("ошибся", "ошиблась") + "? Это дом губернатора " + XI_ConvertString("Colony" + npchar.city + "Gen") + ". Тебе лучше уйти!");
            link.l1 = RandPhraseSimple("Уйду, когда захочу!", "Не лезь не в свое дело...");
            link.l1.go = "exit";
        }
        else
        {
            dialog.text = LinkRandPhrase("Сегодня меня поставили в наряд к губернатору. Неплохое место...", "Я охраняю дом губернатора, " + GetAddress_Form(NPChar) + ".", "Моя задача - охранять дом губернатора.");
            link.l1 = RandPhraseSimple("Здорово.", "Хм, понятно...");
            link.l1.go = "exit";
        }
        break;
    }
}
