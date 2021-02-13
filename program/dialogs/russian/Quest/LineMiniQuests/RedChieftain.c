void ProcessDialogEvent()
{
    ref sld, NPChar;
    aref Link, NextDiag;

    DeleteAttribute(&Dialog, "Links");

    makeref(NPChar, CharacterRef);
    makearef(Link, Dialog.Links);
    makearef(NextDiag, NPChar.Dialog);

    switch (Dialog.CurrentNode)
    {
    case "First time":
        dialog.text = "Явный баг. Сообщите Jason'у, как и при каких обстоятельствах его получили.";
        link.l1 = "Обязательно сообщу!";
        link.l1.go = "exit";
        NextDiag.TempNode = "First time";
        break;

    case "RedChieftain":
        dialog.text = "Приветствую тебя, белый человек. Я видеть, ты капитан большого каноэ. Моя зовут Канаури, и я вождь рода Кайман великого племени араваков. Моя хотеть говорить с тобой.";
        link.l1 = "Слушаю тебя, вождь. Какая беда привела тебя ко мне?";
        link.l1.go = "RedChieftain_0";
        link.l2 = "Что тебе может быть от меня нужно, краснорожая образина? Ступай в свои джунгли, откуда ты выполз, и не беспокой меня своими просьбами.";
        link.l2.go = "RedChieftain_exit";
        break;

    case "RedChieftain_exit":
        dialog.text = "Гу-у! Гу-у! Белый капитан не обучен вежливости? Я хотеть предложить тебе заработать много-много денег, но теперь я уходить. Прощай, бледнолицый.";
        link.l1 = "Давай, топай уже отсюда...";
        link.l1.go = "RedChieftain_exit_1";
        break;

    case "RedChieftain_exit_1":
        DialogExit();
        LAi_ActorRunToLocation(npchar, "reload", "reload4_back", "none", "", "", "", -1);
        npchar.lifeday = 0;
        DeleteAttribute(pchar, "questTemp.RedChieftain");
        chrDisableReloadToLocation = false;
        ChangeIndianRelation(-3.0);
        break;

    case "RedChieftain_0":
        dialog.text = "Белый брат проницателен, как змей. С моим родом стрястись беда. К мой деревня прийти большой-большой каноэ белых людей. Они захватывать почти всех мужчин мой род в плен на свой каноэ и увезти в море...";
        link.l1 = "Постой... ты хочешь сказать, что твоих соплеменников захватили в рабство белые с корабля?";
        if (sti(pchar.Basenation) == SPAIN)
            link.l1.go = "RedChieftain_2";
        else
            link.l1.go = "RedChieftain_1";
        break;

    case "RedChieftain_1":
        dialog.text = "Так, белый брат. Эти люди не друзья тебе, я узнать. Это испанцы. Они увезти моих людей, я найти их. Испанцы заставить индеец работать от зари до зари, нырять вода, таскать раковины со слезами богов.";
        link.l1 = "Ловцы жемчуга... Это тяжёлый труд.";
        link.l1.go = "RedChieftain_3";
        pchar.questTemp.RedChieftain.Spa = "true";
        pchar.questTemp.RedChieftain.AttackNation = SPAIN;
        break;

    case "RedChieftain_2":
        dialog.text = "Так, белый брат. Эти люди не друзья тебе, я узнать. Это англичане. Они увезти моих людей, я найти их. Англичане заставить индеец работать от зари до зари, нырять вода, таскать раковины со слезами богов.";
        link.l1 = "Ловцы жемчуга... Это тяжёлый труд.";
        link.l1.go = "RedChieftain_3";
        pchar.questTemp.RedChieftain.Eng = "true";
        pchar.questTemp.RedChieftain.AttackNation = ENGLAND;
        break;

    case "RedChieftain_3":
        dialog.text = "От тяжкий труд индеец болеть и умирать. Белые не жалеть индеец. Плеть и пистолет - закон белых для индеец. Моя уже стар и не иметь мужчин рода для сражений. Араваки мирный народ. Я просить тебя, белый брат, обнажить плеть и пистолет против наш общий враг.";
        link.l1 = "Хм. Пока не понимаю, что ты от меня хочешь. Мне нужно развязать войну?";
        link.l1.go = "RedChieftain_4";
        break;

    case "RedChieftain_4":
        dialog.text = "Освободи мужчин мой род из рабства. За это мы отдать тебе все слёзы богов, которые быть в лодках. Убей злой белый, помоги индеец, получи слёзы богов, продай за много-много золота.";
        link.l1 = "А, теперь понятно. Нет, Канаури, я ничем не смогу тебе помочь. У меня сейчас нет такой возможности - судно надо ремонтировать, припасов нет...";
        link.l1.go = "RedChieftain_wait";
        link.l2 = "С удовольствием возьмусь за это дело. Давай перейдём к подробностям. Где твои люди? Ты сказал, что нашёл их...";
        link.l2.go = "RedChieftain_5";
        break;

    case "RedChieftain_wait":
        dialog.text = "Гу-у! Я могу подождать, белый брат... Я быть в этом порту ещё одна луна, искать защитника мой род. Ты найти меня тут.";
        link.l1 = "...";
        link.l1.go = "RedChieftain_wait_1";
        break;

    case "RedChieftain_wait_1":
        DialogExit();
        LAi_ActorGoToLocator(npchar, "quest", "quest1", "RedChieftainStay", -1);
        chrDisableReloadToLocation = false;
        bDisableFastReload = false;
        SetFunctionTimerCondition("RedChieftainDelete", 0, 0, 30, false);
        break;

    case "RedChieftain_wait_2":
        dialog.text = "Ты вернуться, белый брат? Ты помочь наказать злой люди и спасти индеец?";
        link.l1 = "Да, я, пожалуй, возьмусь за это дело...";
        link.l1.go = "RedChieftain_wait_4";
        link.l2 = "Мне ещё нужно подготовиться.";
        link.l2.go = "RedChieftain_wait_3";
        break;

    case "RedChieftain_wait_3":
        dialog.text = "Я буду тут, белый брат.";
        link.l1 = "...";
        link.l1.go = "exit";
        NextDiag.Tempnode = "RedChieftain_wait_2";
        break;

    case "RedChieftain_wait_4":
        dialog.text = "Я очень рад, что ты согласился, белый брат!";
        link.l1 = "Давай перейдём к подробностям, Канаури. Где твои люди? Ты сказал, что нашёл их...";
        link.l1.go = "RedChieftain_5";
        pchar.quest.RedChieftainDelete.over = "yes"; //снять таймер
        break;

    case "RedChieftain_5":
        if (CheckAttribute(pchar, "questTemp.RedChieftain.Spa"))
        {
            pchar.questTemp.RedChieftain.Island = "Cumana";
            pchar.questTemp.RedChieftain.Shore = "Shore19";
            pchar.questTemp.RedChieftain.Add1 = "испанским";
            pchar.questTemp.RedChieftain.Add2 = "в бухте Карупано, что недалеко от Куманы";
            dialog.text = "Они находиться в лагерь на берегу моря в бухте Карупано, что близко поселения испанцев Кумана. Каждый день они выходить на лодках в море и нырять вода, глубоко-глубоко...";
            link.l1 = "Понятно. Их, конечно, стерегут испанцы?";
            link.l1.go = "RedChieftain_6";
        }
        else
        {
            pchar.questTemp.RedChieftain.Island = "SantaCatalina";
            pchar.questTemp.RedChieftain.Shore = "Shore54";
            pchar.questTemp.RedChieftain.Add1 = "английским";
            pchar.questTemp.RedChieftain.Add2 = "у мыса Перлас, что недалеко от Блювельда";
            dialog.text = "Они находиться в лагерь на берегу моря на мыс Перлас, что близко поселения англичан Блювельд. Каждый день они выходить на лодках в море и нырять вода, глубоко-глубоко...";
            link.l1 = "Понятно. Их, конечно, стерегут англичане?";
            link.l1.go = "RedChieftain_6";
        }
        break;

    case "RedChieftain_6":
        dialog.text = "Да, их охранять два каноэ бледнолицых с солдатами. Лагерь на берегу тоже под охраной - индеец не мочь бежать.";
        link.l1 = "Какие это корабли? Можешь их описать? Очень большие? Какие у них паруса?";
        link.l1.go = "RedChieftain_7";
        break;

    case "RedChieftain_7":
        dialog.text = "Каноэ большой, но бывает и больше. Парус спереди косой-косой на три угла, сзади - сверху узкий, снизу широкий.";
        link.l1 = "Похоже на шхуну...";
        link.l1.go = "RedChieftain_8";
        break;

    case "RedChieftain_8":
        dialog.text = "Канаури не знать. Бледнолицые псы очень осторожен - едва увидят на горизонте каноэ - сгонять лодки с индеец на берег, пока чужой каноэ не уплыть.";
        link.l1 = "Это плохо. Как же тогда к ним подобраться?";
        link.l1.go = "RedChieftain_9";
        break;

    case "RedChieftain_9":
        dialog.text = "Если бледнолицый брат возьмёт небольшой каноэ, то можно незаметно прокрасться вдоль берега. Я показать дорогу. Но только на один маленький каноэ, иначе бледнолицый собака увидеть и загнать индеец с лодка в джунгли...";
        link.l1 = "Ясно. Для этой операции нужен люггер или шлюп. Хм. На одном шлюпе против двух шхун... а, ладно, справимся как-нибудь!";
        link.l1.go = "RedChieftain_10";
        break;

    case "RedChieftain_10":
        dialog.text = "Мы отправляться в путь, белый брат? У нас в запасе не больше одной луны.";
        link.l1 = "Да. Поднимайся на борт моего корабля, вождь. Не будем терять времени!";
        link.l1.go = "RedChieftain_11";
        break;

    case "RedChieftain_11":
        DialogExit();
        LAi_SetActorType(npchar);
        LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "", -1);
        AddPassenger(pchar, npchar, false);
        SetCharacterRemovable(npchar, false);
        chrDisableReloadToLocation = false;
        bDisableFastReload = false;
        pchar.quest.Red_Chieftain_2.win_condition.l1 = "location";
        pchar.quest.Red_Chieftain_2.win_condition.l1.location = pchar.questTemp.RedChieftain.Island;
        pchar.quest.Red_Chieftain_2.function = "RedChieftain_CreateShooner";
        SetFunctionTimerCondition("RedChieftainOver", 0, 0, 30, false);
        AddQuestRecord("RedChieftain", "1");
        AddQuestUserData("RedChieftain", "sText1", pchar.questTemp.RedChieftain.Add1);
        AddQuestUserData("RedChieftain", "sText2", pchar.questTemp.RedChieftain.Add2);
        break;

    case "RedChieftain_pearl":
        dialog.text = "Благодарю тебя, белый брат. Ты спасти мой род и индеец в долгу тебе. Путь очищен от бледнолицый пёс, и индеец может идти джунгли. Мы отдать тебе все слёзы богов, какие есть лодках.";
        link.l1 = "Ну, давай посмотрим, что там у вас...";
        link.l1.go = "RedChieftain_pearl_1";
        break;

    case "RedChieftain_pearl_1":
        DialogExit();
        pchar.questTemp.RedChieftain.Ind = 1;
        AddDialogExitQuest("RedChieftain_Pearl");
        break;

    case "RedChieftain_pearl_give":
        int iSmallPearl = rand(200) + rand(250) + rand(200) + 250;
        int iBigPearl = rand(100) + rand(100) + rand(50) + 150;
        TakeNItems(pchar, "jewelry52", iBigPearl);
        TakeNItems(pchar, "jewelry53", iSmallPearl);
        PlaySound("interface\important_item.wav");
        Log_SetStringToLog("Индеец отдал вам " + iSmallPearl + " малых и " + iBigPearl + " больших жемчужин.");
        dialog.text = LinkRandPhrase("Я радоваться, что слёзы богов достаться тебе!", "Индеец благодарит тебя, отважный бледнолицый!", "Возьми наш улов, белый брат!");
        link.l1 = LinkRandPhrase("Рад, что сумел помочь вам!", "Спасибо, краснокожий брат!", "Да, вы в долгу не останетесь!");
        link.l1.go = "exit";
        pchar.questTemp.RedChieftain.Ind = sti(pchar.questTemp.RedChieftain.Ind) + 1;
        AddDialogExitQuest("RedChieftain_Pearl");
        break;

    case "RedChieftain_final":
        chrDisableReloadToLocation = false; //открыть локацию
        dialog.text = "Канаури ещё раз благодарит тебя, бледнолицый брат! Я надеяться, что слёзы богов будут достаточной награда за жизнь индейцев. А теперь мы прощаться - нам пора в путь в родной селение.";
        link.l1 = "Счастливо, Канаури! Не попадайте больше в рабство!";
        link.l1.go = "RedChieftain_final_1";
        break;

    case "RedChieftain_final_1":
        DialogExit();
        RemovePassenger(Pchar, npchar);
        LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "", -1);
        npchar.lifeday = 0;
        int n = pchar.questTemp.RedChieftain.Tartane;
        for (i = 1; i <= n; i++)
        {
            sld = characterFromId("RC_Indian_" + i);
            LAi_ActorRunToLocation(sld, "reload", "reload1_back", "none", "", "", "", -1);
        }
        InterfaceStates.Buttons.Save.enable = true;                                            //разрешить сохраняться
        locations[FindLocation(pchar.questTemp.RedChieftain.Shore)].DisableEncounters = false; //энкаутеры открыть
        AddComplexSelfExpToScill(50, 50, 50, 50);
        AddCharacterExpToSkill(pchar, "Fortune", 50); //везение
        AddQuestRecord("RedChieftain", "8");
        CloseQuestHeader("RedChieftain");
        DeleteAttribute(pchar, "questTemp.RedChieftain");
        break;

    case "Exit":
        NextDiag.CurrentNode = NextDiag.TempNode;
        DialogExit();
        break;
    }
}
