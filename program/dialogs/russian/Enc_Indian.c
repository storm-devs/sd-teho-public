//Jason диалог индейцев в джунглях
void ProcessDialogEvent()
{
    ref NPChar;
    aref Link, NextDiag;
    int iQty;

    DeleteAttribute(&Dialog, "Links");

    makeref(NPChar, CharacterRef);
    makearef(Link, Dialog.Links);
    makearef(NextDiag, NPChar.Dialog);

    switch (Dialog.CurrentNode)
    {
    case "First time":
        dialog.text = NPCStringReactionRepeat("" + GetSexPhrase("Бледнолицый", "Белая скво") + " хочет говорить?",
                                              "Снова ты, " + GetSexPhrase("бледнолицый", "белая скво") + ".",
                                              "" + GetSexPhrase("Бледнолицый любит говорить. Он похож на скво.", "Белая скво любит говорить.") + "",
                                              "Духи привели ко мне бледнолиц" + GetSexPhrase("его брата", "ую сестру") + ".", "block", 1, npchar, Dialog.CurrentNode);
        link.l1 = HeroStringReactionRepeat("Да.",
                                           "Да, снова я.",
                                           "Очень поэтично.",
                                           "Я тоже рад" + GetSexPhrase("", "а") + " тебя видеть.", npchar, Dialog.CurrentNode);
        link.l1.go = "exit";

        if (npchar.quest.meeting == "0")
        {
            dialog.text = "Здравствуй, белый брат. Ты хотеть говорить индеец?";
            link.l1 = "Приветствую, сын джунглей. Я рад тебя видеть, но мне пора продолжить свой путь.";
            link.l1.go = "exit";
            link.l2 = "Да. Я слышал, у вас можно купить интересные вещички. У тебя нет чего-нибудь на продажу?";
            link.l2.go = "select_trade";
            npchar.quest.meeting = "1";
        }
        NextDiag.TempNode = "First time";
        break;

    case "select_trade": //индейская торговля
        switch (drand(7))
        {
        case 0: // торговля через интерфейс
            dialog.text = "Тебе повезти, белый брат. У " + npchar.name + " есть мала-мала вещей на продажа. Смотри сюда.";
            link.l1 = "Показывай свои товары...";
            link.l1.go = "torg";
            if (CheckCharacterItem(pchar, "cannabis7") && CheckAttribute(pchar, "questTemp.Mangarosa") && !CheckAttribute(npchar, "quest.mangarosa"))
            {
                if (pchar.questTemp.Mangarosa == "gipsy" || pchar.questTemp.Mangarosa == "gipsy_trade")
                {
                    link.l9 = "Погоди. Сегодня у меня есть кое-что на продажу. Это растение, называется мангароса. Я слыхал, вы таким интересуетесь...";
                    link.l9.go = "mangarosa";
                }
            }
            break;

        case 1: // не торгует
            dialog.text = "Нет, белый брат. " + npchar.name + " ничем не торгует. " + npchar.name + " - воин.";
            link.l1 = "Понятно. Ладно, прощай, краснокожий брат.";
            link.l1.go = "exit";
            break;

        case 2: // жемчуг большой
            npchar.quest.item.qty = 25 + drand(25);
            npchar.quest.item.price = 30 + drand(10);
            dialog.text = "У " + npchar.name + " есть слезы богов. Большие слезы богов, белый брат. Всего " + FindRussianQtyString(sti(npchar.quest.item.qty)) + ". Ты хотеть покупать их? Я продать за " + FindRussianMoneyString(sti(npchar.quest.item.price)) + " штука.";
            link.l1 = "Нет, мне это не интересно.";
            link.l1.go = "exit";
            link.l2 = "Конечно! За такую цену я готов их приобрести.";
            link.l2.go = "big_pearl";
            if (CheckCharacterItem(pchar, "cannabis7") && CheckAttribute(pchar, "questTemp.Mangarosa") && !CheckAttribute(npchar, "quest.mangarosa"))
            {
                if (pchar.questTemp.Mangarosa == "gipsy" || pchar.questTemp.Mangarosa == "gipsy_trade")
                {
                    link.l9 = "Погоди. Сегодня у меня есть кое-что на продажу. Это растение, называется мангароса. Я слыхал, вы таким интересуетесь...";
                    link.l9.go = "mangarosa";
                }
            }
            break;

        case 3: // жемчуг малый
            npchar.quest.item.qty = 40 + drand(40);
            npchar.quest.item.price = 10 + drand(5);
            dialog.text = "У " + npchar.name + " есть слезы богов. Маленькие слезы богов, белый брат. Всего " + FindRussianQtyString(sti(npchar.quest.item.qty)) + ". Ты хотеть покупать их? Я продать за " + FindRussianMoneyString(sti(npchar.quest.item.price)) + " штука.";
            link.l1 = "Нет, мне это не интересно.";
            link.l1.go = "exit";
            link.l2 = "Конечно! За такую цену я готов их приобрести.";
            link.l2.go = "small_pearl";
            if (CheckCharacterItem(pchar, "cannabis7") && CheckAttribute(pchar, "questTemp.Mangarosa") && !CheckAttribute(npchar, "quest.mangarosa"))
            {
                if (pchar.questTemp.Mangarosa == "gipsy" || pchar.questTemp.Mangarosa == "gipsy_trade")
                {
                    link.l9 = "Погоди. Сегодня у меня есть кое-что на продажу. Это растение, называется мангароса. Я слыхал, вы таким интересуетесь...";
                    link.l9.go = "mangarosa";
                }
            }
            break;

        case 4: //золотые самородки
            npchar.quest.item.qty = 20 + drand(20);
            npchar.quest.item.price = 90 + drand(20);
            dialog.text = "У " + npchar.name + " есть желтый металл, который вы, бледнолицые, любить. Всего " + FindRussianQtyString(sti(npchar.quest.item.qty)) + ". Я продать дешево, всего за " + FindRussianMoneyString(sti(npchar.quest.item.price)) + " штука.";
            link.l1 = "Нет, мне это не интересно.";
            link.l1.go = "exit";
            link.l2 = "Конечно! За такую цену я готов их приобрести.";
            link.l2.go = "gold";
            if (CheckCharacterItem(pchar, "cannabis7") && CheckAttribute(pchar, "questTemp.Mangarosa") && !CheckAttribute(npchar, "quest.mangarosa"))
            {
                if (pchar.questTemp.Mangarosa == "gipsy" || pchar.questTemp.Mangarosa == "gipsy_trade")
                {
                    link.l9 = "Погоди. Сегодня у меня есть кое-что на продажу. Это растение, называется мангароса. Я слыхал, вы таким интересуетесь...";
                    link.l9.go = "mangarosa";
                }
            }
            break;

        case 5: // серебряные самородки
            npchar.quest.item.qty = 40 + drand(40);
            npchar.quest.item.price = 40 + drand(10);
            dialog.text = "У " + npchar.name + " есть белый металл, который вы, бледнолицые, любить. Всего " + FindRussianQtyString(sti(npchar.quest.item.qty)) + ". Я продать дешево, всего за " + FindRussianMoneyString(sti(npchar.quest.item.price)) + " штука.";
            link.l1 = "Нет, мне это не интересно.";
            link.l1.go = "exit";
            link.l2 = "Конечно! За такую цену я готов их приобрести.";
            link.l2.go = "silver";
            if (CheckCharacterItem(pchar, "cannabis7") && CheckAttribute(pchar, "questTemp.Mangarosa") && !CheckAttribute(npchar, "quest.mangarosa"))
            {
                if (pchar.questTemp.Mangarosa == "gipsy" || pchar.questTemp.Mangarosa == "gipsy_trade")
                {
                    link.l9 = "Погоди. Сегодня у меня есть кое-что на продажу. Это растение, называется мангароса. Я слыхал, вы таким интересуетесь...";
                    link.l9.go = "mangarosa";
                }
            }
            break;

        case 6: // повтор через интерфейс
            dialog.text = "Тебе повезти, белый брат. У " + npchar.name + " есть мала-мала вещей на продажа. Смотри сюда.";
            link.l1 = "Показывай свои товары...";
            link.l1.go = "torg";
            if (CheckCharacterItem(pchar, "cannabis7") && CheckAttribute(pchar, "questTemp.Mangarosa") && !CheckAttribute(npchar, "quest.mangarosa"))
            {
                if (pchar.questTemp.Mangarosa == "gipsy" || pchar.questTemp.Mangarosa == "gipsy_trade")
                {
                    link.l9 = "Погоди. Сегодня у меня есть кое-что на продажу. Это растение, называется мангароса. Я слыхал, вы таким интересуетесь...";
                    link.l9.go = "mangarosa";
                }
            }
            break;

        case 7: // повтор не торгует
            dialog.text = "Нет, белый брат. " + npchar.name + " ничем не торгует. " + npchar.name + " - воин.";
            link.l1 = "Понятно. Ладно, прощай, краснокожий брат.";
            link.l1.go = "exit";
            break;
        }
        break;

    case "torg":
        DialogExit();
        if (CheckNPCQuestDate(npchar, "Torg_date"))
        {
            SetNPCQuestDate(npchar, "Torg_date");
            GiveItemToTrader(npchar);
        }
        NextDiag.CurrentNode = "First time";
        LaunchItemsTrade(NPChar, 0);
        ChangeIndianRelation(0.25);
        break;

    // большой жемчуг
    case "big_pearl":
        dialog.text = "Сколько слез ты хотеть купить?";
        link.l1 = "";
        Link.l1.edit = 4;
        link.l1.go = "big_pearl_qty";
        break;

    case "big_pearl_qty":
        iQty = sti(dialogEditStrings[4]);
        npchar.quest.item.Byeqty = iQty;
        if (iQty < 1)
        {
            dialog.text = "Ты пошутить, бледнолицый? Тебе не нужны слезы богов? Тогда прощай.";
            link.l1 = "Гм...";
            link.l1.go = "exit";
            break;
        }
        if (iQty > sti(npchar.quest.item.qty))
        {
            dialog.text = "Я же сказать, сколько у меня слез. Ты шутить над индеец, бледнолицый? Тогда прощай.";
            link.l1 = "Гм...";
            link.l1.go = "exit";
            break;
        }
        npchar.quest.item.Summ = iQty * sti(npchar.quest.item.price);
        dialog.text = "" + iQty + " слез? Хорошо. С тебя " + FindRussianMoneyString(sti(npchar.quest.item.Summ)) ", белый брат.";
        if (sti(Pchar.money) >= sti(npchar.quest.item.Summ))
        {
            link.l1 = "Держи свои монеты, краснокожий брат.";
            link.l1.go = "big_pearl_1";
        }
        link.l2 = "У меня сейчас недостаточно денег. Жаль, но я не смогу купить у тебя жемчуг.";
        link.l2.go = "exit";
        break;

    case "big_pearl_1":
        AddMoneyToCharacter(pchar, -sti(npchar.quest.item.Summ));
        TakeNItems(pchar, "jewelry52", sti(npchar.quest.item.Byeqty));
        PlaySound("interface\important_item.wav");
        dialog.text = "Вот, возьми, белый брат. Теперь они твои.";
        link.l1 = "Благодарю!";
        link.l1.go = "exit";
        ChangeIndianRelation(0.5);
        break;

    // малый жемчуг
    case "small_pearl":
        dialog.text = "Сколько слез ты хотеть купить?";
        link.l1 = "";
        Link.l1.edit = 4;
        link.l1.go = "small_pearl_qty";
        break;

    case "small_pearl_qty":
        iQty = sti(dialogEditStrings[4]);
        npchar.quest.item.Byeqty = iQty;
        if (iQty < 1)
        {
            dialog.text = "Ты пошутить, бледнолиый? Тебе не нужны слезы богов? Тогда прощай.";
            link.l1 = "Гм...";
            link.l1.go = "exit";
            break;
        }
        if (iQty > sti(npchar.quest.item.qty))
        {
            dialog.text = "Я же сказать, сколько у меня слез. Ты шутить над индеец, бледнолицый? Тогда прощай.";
            link.l1 = "Гм...";
            link.l1.go = "exit";
            break;
        }
        npchar.quest.item.Summ = iQty * sti(npchar.quest.item.price);
        dialog.text = "" + iQty + " слез? Хорошо. С тебя " + FindRussianMoneyString(sti(npchar.quest.item.Summ)) ", белый брат.";
        if (sti(Pchar.money) >= sti(npchar.quest.item.Summ))
        {
            link.l1 = "Держи свои монеты, краснокожий брат.";
            link.l1.go = "small_pearl_1";
        }
        link.l2 = "У меня сейчас недостаточно денег. Жаль, но я не смогу купить у тебя жемчуг.";
        link.l2.go = "exit";
        break;

    case "small_pearl_1":
        AddMoneyToCharacter(pchar, -sti(npchar.quest.item.Summ));
        TakeNItems(pchar, "jewelry53", sti(npchar.quest.item.Byeqty));
        PlaySound("interface\important_item.wav");
        dialog.text = "Вот, возьми, белый брат. Теперь они твои.";
        link.l1 = "Благодарю!";
        link.l1.go = "exit";
        ChangeIndianRelation(0.5);
        break;

    // золотые самородки
    case "gold":
        dialog.text = "Сколько ты хотеть купить?";
        link.l1 = "";
        Link.l1.edit = 4;
        link.l1.go = "gold_qty";
        break;

    case "gold_qty":
        iQty = sti(dialogEditStrings[4]);
        npchar.quest.item.Byeqty = iQty;
        if (iQty < 1)
        {
            dialog.text = "Ты пошутить, бледнолиый? Тебе не нужны самородки? Тогда прощай.";
            link.l1 = "Гм...";
            link.l1.go = "exit";
            break;
        }
        if (iQty > sti(npchar.quest.item.qty))
        {
            dialog.text = "Я же сказать, сколько у меня есть. Ты шутить над индеец, бледнолицый? Тогда прощай.";
            link.l1 = "Гм...";
            link.l1.go = "exit";
            break;
        }
        npchar.quest.item.Summ = iQty * sti(npchar.quest.item.price);
        dialog.text = "" + iQty + " кусков? Хорошо. С тебя " + FindRussianMoneyString(sti(npchar.quest.item.Summ)) ", белый брат.";
        if (sti(Pchar.money) >= sti(npchar.quest.item.Summ))
        {
            link.l1 = "Держи свои монеты, краснокожий брат.";
            link.l1.go = "gold_1";
        }
        link.l2 = "У меня сейчас недостаточно денег. Жаль, но я не смогу купить у тебя самородки.";
        link.l2.go = "exit";
        break;

    case "gold_1":
        AddMoneyToCharacter(pchar, -sti(npchar.quest.item.Summ));
        TakeNItems(pchar, "jewelry5", sti(npchar.quest.item.Byeqty));
        PlaySound("interface\important_item.wav");
        dialog.text = "Вот, возьми, белый брат. Теперь они твои.";
        link.l1 = "Благодарю!";
        link.l1.go = "exit";
        ChangeIndianRelation(0.5);
        break;

    // серебряные самородки
    case "silver":
        dialog.text = "Сколько ты хотеть купить?";
        link.l1 = "";
        Link.l1.edit = 4;
        link.l1.go = "silver_qty";
        break;

    case "silver_qty":
        iQty = sti(dialogEditStrings[4]);
        npchar.quest.item.Byeqty = iQty;
        if (iQty < 1)
        {
            dialog.text = "Ты пошутить, бледнолиый? Тебе не нужны самородки? Тогда прощай.";
            link.l1 = "Гм...";
            link.l1.go = "exit";
            break;
        }
        if (iQty > sti(npchar.quest.item.qty))
        {
            dialog.text = "Я же сказать, сколько у меня есть. Ты шутить над индеец, бледнолицый? Тогда прощай.";
            link.l1 = "Гм...";
            link.l1.go = "exit";
            break;
        }
        npchar.quest.item.Summ = iQty * sti(npchar.quest.item.price);
        dialog.text = "" + iQty + " кусков? Хорошо. С тебя " + FindRussianMoneyString(sti(npchar.quest.item.Summ)) ", белый брат.";
        if (sti(Pchar.money) >= sti(npchar.quest.item.Summ))
        {
            link.l1 = "Держи свои монеты, краснокожий брат.";
            link.l1.go = "silver_1";
        }
        link.l2 = "У меня сейчас недостаточно денег. Жаль, но я не смогу купить у тебя самородки.";
        link.l2.go = "exit";
        break;

    case "silver_1":
        AddMoneyToCharacter(pchar, -sti(npchar.quest.item.Summ));
        TakeNItems(pchar, "jewelry6", sti(npchar.quest.item.Byeqty));
        PlaySound("interface\important_item.wav");
        dialog.text = "Вот, возьми, белый брат. Теперь они твои.";
        link.l1 = "Благодарю!";
        link.l1.go = "exit";
        ChangeIndianRelation(0.5);
        break;

    // мангароса
    case "mangarosa":
        dialog.text = "Мангароса? Я хотеть на нее глянуть.";
        link.l1 = "Пожалуйста, смотри...";
        link.l1.go = "mangarosa_1";
        break;

    case "mangarosa_1":
        npchar.quest.mangarosa = "indian_" + (drand(10) + 1);
        dialog.text = "Да. Она. Этот растение иметь один из названий - мангароса. Я дать за него тебе амулет, очень хороший амулет, называться - " + XI_ConvertString(npchar.quest.mangarosa) + ". Будешь меняться?";
        link.l1 = "Послушай, краснокожий брат, я бы хотел побольше узнать об этом растении. Зачем оно так вам нужно, не расскажешь?";
        link.l1.go = "mangarosa_2";
        break;

    case "mangarosa_2":
        dialog.text = "" + npchar.name + " не понимать. Если ты хотеть меняться - я дать тебе за мангароса амулет. Если нет - тогда я идти.";
        link.l1 = "Ох, ладно. Давай меняться.";
        link.l1.go = "mangarosa_3";
        link.l2 = "Нет. Я отдавать это растение за амулет не буду.";
        link.l2.go = "exit";
        break;

    case "mangarosa_3":
        Log_Info("Вы получили амулет");
        GiveItem2Character(pchar, npchar.quest.mangarosa);
        RemoveItems(pchar, "cannabis7", 1);
        dialog.text = "Держи свой " + XI_ConvertString(npchar.quest.mangarosa) + ". Он тебе пригодится.";
        link.l1 = "Не сомневаюсь. Счастливой дороги, краснокожий друг...";
        link.l1.go = "exit";
        ChangeIndianRelation(0.5);
        break;

    //замечание по обнаженному оружию от персонажей типа citizen
    case "CitizenNotBlade":
        dialog.text = NPCharSexPhrase(NPChar, "Не искушать судьбу, бледнолицый! Убери свой сабля!", "Знаете, я, как гражданка этого города, прошу вас не ходить у нас с обнаженным клинком.");
        link.l1 = LinkRandPhrase("Хорошо.", "Ладно.", "Как скажешь...");
        link.l1.go = "exit";
        break;

    case "Exit":
        NextDiag.CurrentNode = NextDiag.TempNode;
        DialogExit();
        break;
    }
}
