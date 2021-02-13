// boal 25/04/04 общий диалог солдат форта
void ProcessDialogEvent()
{
    ref NPChar;
    aref Link, NextDiag;

    DeleteAttribute(&Dialog, "Links");

    makeref(NPChar, CharacterRef);
    makearef(Link, Dialog.Links);
    makearef(NextDiag, NPChar.Dialog);

    // вызов диалога по городам -->
    NPChar.FileDialog2 = "DIALOGS\" + LanguageGetLanguage() + "\Fort\" + NPChar.City + "_Fort.c ";
                         if (LoadSegment(NPChar.FileDialog2))
    {
        ProcessCommonDialog(NPChar, Link, NextDiag);
        UnloadSegment(NPChar.FileDialog2);
    }
    // вызов диалога по городам <--
    int iTest, iTemp;
    string sTemp;
    iTest = FindColony(NPChar.City); // город
    ref rColony;
    if (iTest != -1)
    {
        rColony = GetColonyByIndex(iTest);
    }
    switch (Dialog.CurrentNode)
    {
    case "Exit":
        sTemp = npchar.location;
        if (findsubstr(sTemp, "_townhall", 0) != -1)
            AddDialogExitQuest("MainHeroFightModeOff");
        NextDiag.CurrentNode = NextDiag.TempNode;
        DialogExit();
        break;

    case "fight":
        DialogExit();
        NextDiag.CurrentNode = NextDiag.TempNode;
        LAi_group_Attack(NPChar, Pchar);
        if (rand(3) != 1)
            SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
        AddDialogExitQuest("MainHeroFightModeOn");
        break;

    case "First time":
        NextDiag.TempNode = "First time";
        if (GetNationRelation2MainCharacter(sti(NPChar.nation)) == RELATION_ENEMY && sti(NPChar.nation) != PIRATE)
        {
            dialog.text = RandPhraseSimple("Шпион? Сдать оружие!! Следовать за мной!", "Вражеский агент!! Немедленно схватить е" + GetSexPhrase("го", "ё") + "!");
            link.l1 = RandPhraseSimple("Заткнись, малахольный!", "Как бы не так!");
            link.l1.go = "fight";
        }
        else
        {
            // eddy. проверяем, не казачок ли. -->
            if (GetRelation2BaseNation(sti(npchar.nation)) == RELATION_ENEMY && sti(NPChar.nation) != PIRATE)
            {
                dialog.text = RandPhraseSimple("Кто ты и что тебе здесь нужно?", "Стой! Кто ты? На каком основании пытаешься войти в форт?");
                //==> по лицензии
                if (CheckNationLicence(HOLLAND))
                {
                    link.l1 = "Офицер, у меня имеется " + GetRusNameNationLicence(sti(npchar.nation)) + ", так что, я нахожусь здесь на законных основаниях. Прошу ознакомиться...";
                    link.l1.go = "LicenceOk";
                }
                else
                {
                    //==> по флагу
                    // заглушка на пирата
                    if (sti(pchar.nation) == PIRATE)
                    {
                        dialog.text = RandPhraseSimple("Пираты в форте?! Держи е" + GetSexPhrase("го", "ё") + "!!", "Это пират, он" + GetSexPhrase("", "а") + " вынюхивает здесь что-то!! Держи е" + GetSexPhrase("го", "ё") + "!!!");
                        link.l1 = RandPhraseSimple("Да, пират, ну и что?..", "Хех, попробуйте схватить...");
                        link.l1.go = "fight";
                        break;
                    }
                    if (findsubstr(pchar.location.from_sea, "_town", 0) != -1) //если причалил в городе
                    {
                        link.l1 = "Ты что, не видишь, как на мачте моего корабля развевается флаг" + NationNameGenitive(sti(pchar.nation)) + "?!";
                    }
                    else //если причалил не в городе
                    {
                        link.l1 = "Я бросил якорь у " + XI_ConvertString(GetIslandByCityName(npchar.city) + "Gen") + " под флагом " + NationNameGenitive(sti(pchar.nation)) + ". Что тебе ещё не ясно?";
                    }
                    if (GetSummonSkillFromName(pchar, SKILL_SNEAK) < (10 + rand(50) + rand(50)))
                    {
                        link.l1.go = "PegYou";
                    }
                    else
                    {
                        link.l1.go = "NotPegYou";
                    }
                }
            }
            // <-- eddy. проверяем, не казачок ли.
            else
            {
                if (sti(NPChar.nation) == PIRATE)
                {
                    if (sti(rColony.HeroOwn)) // наш горожанин
                    {
                        switch (rand(10))
                        {
                        case 0:
                            dialog.text = "Эх, капитан, как славно было с вами в море! Сколько кораблей мы потопили под вашей командой! А тут...";
                            link.l1 = "А тут, друг мой, перед вами постоянно мелькают очаровательные женщины, которых в море не бывает.";
                            link.l1.go = "exit";
                            break;

                        case 1:
                            dialog.text = "Капитан, за что такое наказание?! Мы ведь не сухопутные крысы!";
                            link.l1 = "Спокойно, моряк! Вы на важном и почётном посту, так что не нойте.";
                            link.l1.go = "exit";
                            break;

                        case 2:
                            dialog.text = "Как там в море, капитан? Мы когда-нибудь снова увидим его?";
                            link.l1 = "Конечно, матрос! Сменитесь с караула, выйдете на пирс и наслаждайтесь морем сколько угодно.";
                            link.l1.go = "exit";
                            break;

                        case 3:
                            dialog.text = "Спешу пожаловаться, капитан: мы все стремимся снова в море. Эта служба на суше просто поперек горла стоит!";
                            link.l1 = "Я устал" + GetSexPhrase("", "а") + " от этого нытья! Выпивки вам хватает и на земле! Служи там, где тебя поставил" + GetSexPhrase("", "а") + " капитан! А то кое-кого придётся вздёрнуть для примера.";
                            link.l1.go = "exit";
                            break;

                        case 4:
                            dialog.text = "Скажу вам по секрету, капитан, новый губернатор - взяточник и казнокрад. Но это, конечно, не моё дело…";
                            link.l1 = "Ты прав, корсар: твоё дело - стоять на посту и следить за порядком. Ну а вздёрнуть губернатора на нок рее - это уже занятие для меня. Молодец!";
                            link.l1.go = "exit";
                            break;

                        case 5:
                            dialog.text = "Спасибо, что не забываете о нас капитан! Мы за вас и в огонь и в воду!";
                            link.l1 = "Знаю я вас, проходимцев! Любите только золото. Сегодня в таверне попойка, я угощаю. Не забудь заглянуть.";
                            link.l1.go = "exit";
                            break;

                        case 6:
                            dialog.text = "Эх, капитан! Ну, какие из корсаров блюстители порядка?! Как давно мы не были в настоящем деле!";
                            link.l1 = "Не расслабляйся, корсар! Вражеские армады рыщут вокруг наших островов, так что кровавая баня может приключиться в любой момент.";
                            link.l1.go = "exit";
                            break;

                        case 7:
                            dialog.text = "Капитан, говорят, королевские власти снова посылают сюда эскадру?";
                            link.l1 = "Конечно, корсар. Пока мы живы, мира не будет никогда. Даже в Аду нам придётся сражаться с чертями!";
                            link.l1.go = "exit";
                            break;

                        case 8:
                            dialog.text = "Йо-хо-хо! Какая знатная вчера у нас была попойка, капитан! Жалко, что вас не было.";
                            link.l1 = "Ничего, я своё ещё наверстаю. И вам, ребята, я не завидую.";
                            link.l1.go = "exit";
                            break;

                        case 9:
                            dialog.text = "Скажу вам по секрету, капитан, поскольку вы нас никогда не обижали, завалили мы вчера с ребятами здесь одну телочку...";
                            link.l1 = "Эх, корсар, плачет по вам петля!";
                            link.l1.go = "exit";
                            break;

                        case 10:
                            dialog.text = "Кэп! Освободите вы меня от этой проклятой повинности! Ну, не могу я здесь блюстителя порядка разыгрывать!";
                            link.l1 = "Ты лучше вспомни: ночную вахту на корабле стоять тоже нелегко. Служба, брат, она везде служба.";
                            link.l1.go = "exit";
                            break;
                        }
                        link.l2 = RandPhraseSimple("Есть важное дело!", "У меня к тебе дело.");
                        link.l2.go = "quests"; //(перессылка в файл города)
                        break;
                    }
                }

                //Jason --> мини-квест Дефицитный товар
                if (!CheckAttribute(pchar, "questTemp.Sharlie.FastStart") && sti(pchar.rank) < 4 && !CheckAttribute(pchar, "questTemp.Wine") && npchar.location.group == "soldiers")
                { // Addon 2016-1 Jason пиратская линейка
                    if (npchar.location.locator == "protector1" || npchar.location.locator == "protector2")
                    {
                        dialog.text = "Эй, дружище! Не окажешь мне маленькую услугу?";
                        link.l1 = "Ну, смотря о чём попросишь.";
                        link.l1.go = "Wine_soldier";
                        link.l2 = "Некогда мне.";
                        link.l2.go = "exit";
                        pchar.questTemp.Wine = "true";
                        break;
                    }
                }
                // <-- мини-квест Дефицитный товар

                switch (rand(10))
                {
                case 0: ////////////////////////////////////////
                    dialog.text = "Не видишь, я на посту! Не отвлекай меня.";
                    link.l1 = "Хорошо, хорошо...";
                    link.l1.go = "exit";
                    break;

                case 1:
                    dialog.text = "Ты хочешь сообщить мне о чём-то подозрительном?";
                    link.l1 = "Нет, ничего такого, к тому же я капитан. Вижу, ты уже не слушаешь? Прощай.";
                    link.l1.go = "exit";
                    break;

                case 2: ///////////////////////////////////////////
                    dialog.text = "Запомни, это военный объект! Так что веди себя здесь тихо.";
                    link.l1 = "Хорошо, я приму это к сведению.";
                    link.l1.go = "exit";
                    break;

                case 3:
                    dialog.text = "Какая погода, а я вынужден стоять здесь. Эх, в городах хоть девушки ходят, а здесь только гарнизонные крысы вокруг...";
                    link.l1 = "" + GetSexPhrase("Сочувствую. Но ничем не могу помочь, работа у тебя такая.", "Эй! А я что - не девушка?") + "";
                    link.l1.go = "exit";
                    break;

                case 4: ///////////////////////////////////////////
                    dialog.text = "Если вам хочется поболтать, то найдите себе кого-нибудь другого, а я должен следить за порядком, и мне некогда чесать с вами языком.";
                    link.l1 = "Да нет, я просто " + GetSexPhrase("проверял", "проверяла") + ", жив ли ты ещё, а то стоишь, как статуя.";
                    link.l1.go = "exit";
                    break;

                case 5: ////////////////////////////////////////////
                    dialog.text = "Вот вы думаете, гарнизонные будни - это игрушки? Как бы не так! Это очень ответственный и опасный труд. Вот помнится...";
                    link.l1 = "Расскажешь свою историю как-нибудь в другой раз, а сейчас я спешу.";
                    link.l1.go = "exit";
                    break;

                case 6: ////////////////////////////////////////////
                    dialog.text = "Аккуратней здесь, это форт! Веди себя тише воды...";
                    link.l1 = "Как скажешь, солдат.";
                    link.l1.go = "exit";
                    break;

                case 7:
                    dialog.text = "Эй! Нет ли у тебя воды? Умираю от жажды.";
                    link.l1 = "Нет, приятель, потерпи...";
                    link.l1.go = "exit";
                    break;

                case 8: /////////////////////////////////////////////
                    dialog.text = "" + GetSexPhrase("Эх, и скука же в гарнизоне, вокруг одни неотёсанные мужланы вроде тебя! А вот городской гарнизон жирует...", "Эй, красавица! Как насчёт того, чтобы немного пофлиртовать с бравым воякой?") + "";
                    link.l1 = "" + GetSexPhrase("И это называется 'нести службу'? Смотри, проворонишь какого-нибудь лазутчика!", "Твоё дело за порядком следить... и слюни подбери.") + "";
                    link.l1.go = "exit";
                    break;

                case 9: /////////////////////////////////////////////
                    dialog.text = "" + GetSexPhrase("Ты выглядишь крепким парнем! Не хочешь поступить на службу в гарнизон форта? У нас просторная казарма, двухразовое питание, плюс выпивка бесплатно.", "О, вы даже не представляете, девушка, насколько приятно встретить в этом захолустье такую милую особу, как вы!") + "";
                    link.l1 = "" + GetSexPhrase("Соблазнительно, чёрт побери, но я вынужден отказаться. Казарменная муштра не для меня", "Спасибо за комплимент, солдат") + ".";
                    link.l1.go = "exit";
                    break;

                case 10:
                    dialog.text = "Эта жара... Я бы полжизни отдал, чтобы снова оказаться в Европе.";
                    link.l1 = "Да, смотрю, для здешнего климата ты здоровьем не вышел.";
                    link.l1.go = "exit";
                    break;
                }
                link.l3 = "Н-да... ясно. Я вот что " + GetSexPhrase("хотел", "хотела") + " спросить...";
                link.l3.go = "quests"; //(перессылка в файл города)
            }
        }
        break;

    //Jason --> мини-квест Дефицитный товар
    case "Wine_soldier":
        dialog.text = "Понимаешь, я очень-очень хочу вина... Но не это пойло местного разлива из гнилых фруктов, по два песо за баррель, а бутылочку настоящего европейского вина. Его можно достать в городе у торговцев. Стоит оно недёшево, но я заплачу сполна, и добавлю три сотни песо сверх того. Принесёшь?";
        link.l1 = "А чего сам сходить не можешь? Закончится смена, и иди покупай, и не надо переплачивать... В чём подвох-то?";
        link.l1.go = "Wine_soldier_1";
        break;

    case "Wine_soldier_1":
        dialog.text = "Никакого подвоха нет. Просто я не могу отлучаться из форта в город - служба, понимаешь ли, а в увольнение ещё не скоро. Кроме того, наш командир строжайше запрещает употреблять спиртное в форте, чёрт бы его побрал. Ну так что, поможешь солдату?";
        link.l1 = "А почему бы и нет? Принесу тебе твоё вино, время свободное у меня есть.";
        link.l1.go = "Wine_soldier_2";
        link.l2 = "Извини, приятель, но я не могу этим заняться. Поищи себе другого помощника.";
        link.l2.go = "exit";
        break;

    case "Wine_soldier_2":
        dialog.text = "Вот и замечательно, спасибо тебе! Сегодня я в карауле, так что приходи завтра. Найдёшь меня на самой верхней площадке форта. Там незаметно и передашь бутылочку...";
        link.l1 = "Хорошо. Жди, завтра навещу тебя.";
        link.l1.go = "exit";
        pchar.questTemp.Wine.id = npchar.ID;
        pchar.questTemp.Wine.SName = GetFullName(npchar);
        pchar.questTemp.Wine.bottle = "true";
        npchar.lifeday = 5;
        SetFunctionTimerCondition("Wine_Exchange", 0, 0, 1, false);
        pchar.questTemp.Wine.City = GetCityNameByIsland(LoadedLocation.islandId);
        Log_TestInfo(pchar.questTemp.Wine.City);
        SaveCurrentQuestDateParam("questTemp.Wine_bottle");
        AddQuestRecord("Wine", "0");
        break;
    // <-- мини-квест Дефицитный товар

    //============================== ноды на разборки при распознавании =========================
    case "PegYou":
        dialog.text = RandPhraseSimple("Сдаётся мне, что это обман... Давай-ка пройдём к коменданту, голуб" + GetSexPhrase("чик", "ушка") + ", там разберёмся...", "Хм, что-то подсказывает мне, что ты не " + GetSexPhrase("тот", "та") + ", за кого себя выдаёшь... Немедленно сдай оружие, " + GetAddress_Form(npchar) + ", и следуй за мной для дальнейшего разбирательства!");
        link.l1 = RandPhraseSimple("Как бы не так!", "После дождичка, в четверг...");
        link.l1.go = "fight";
        if (sti(pchar.questTemp.stels.landFort) != GetDataDay())
        {
            AddCharacterExpToSkill(pchar, SKILL_SNEAK, 40);
            pchar.questTemp.stels.landFort = GetDataDay();
        }
        break;
    case "NotPegYou":
        dialog.text = RandPhraseSimple("А-а-а, вижу... Всё в порядке, вы можете идти, " + GetAddress_Form(pchar) + ".", "Что-то я немного подустал в карауле... Всё в порядке, " + GetAddress_Form(pchar) + ", прошу прощения.");
        link.l1 = "Так-то!";
        link.l1.go = "exit";
        if (sti(pchar.questTemp.stels.landFort) != GetDataDay())
        {
            AddCharacterExpToSkill(pchar, SKILL_SNEAK, 80);
            pchar.questTemp.stels.landFort = GetDataDay();
        }
        break;
    case "LicenceOk":
        iTemp = GetDaysContinueNationLicence(HOLLAND);
        if (ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 0) <= -12)
        {
            dialog.text = "Только подумать, какая наглость! Явиться сюда под видом торговца! Да твои портреты развешаны в каждой казарме, негодяй! Ну, теперь ты не уйдёшь! Хватай его!";
            link.l1 = RandPhraseSimple("Аргх!..", "Ну, вы сами напросились...");
            link.l1.go = "fight";
            TakeNationLicence(HOLLAND);
            break;
        }
        if (findsubstr(pchar.location.from_sea, "_town", 0) == -1) //если причалил не в городе
        {
            dialog.text = "Вы прибыли сюда торговать? Позвольте спросить - на чём? Где ваш корабль? Всё это очень подозрительно - я вынужден вас задержать до выяснения. Сдайте оружие и следуйте за мной!";
            link.l1 = RandPhraseSimple("Как бы не так!", "После дождичка, в четверг...");
            link.l1.go = "fight";
            TakeNationLicence(HOLLAND);
            break;
        }
        if (iTemp == -1)
        {
            dialog.text = "Ваша лицензия подлежит изъятию, так как просрочена и поэтому недействительна. Сдайте оружие и следуйте за мной для последующих разбирательств!";
            link.l1 = RandPhraseSimple("Как бы не так!", "После дождичка, в четверг...");
            link.l1.go = "fight";
            TakeNationLicence(HOLLAND);
            break;
        }
        if (iTemp == 0)
        {
            dialog.text = "Хм, всё верно. Однако позволю себе заметить, что срок действия вашей лицензии сегодня истекает. Я пропущу вас сейчас, но вам нужно будет получить новую лицензию.";
            link.l1 = "Спасибо, я сделаю это при первой же возможности.";
            link.l1.go = "exit";
        }
        if (iTemp > 0 && iTemp <= 10)
        {
            dialog.text = "Хм, всё верно. Однако позволю себе заметить, что срок действия вашей лицензии вскоре истекает - она действительна ещё только " + FindRussianDaysString(iTemp) + ". Так что имейте в виду, " + GetAddress_Form(npchar) + ".";
            link.l1 = "Спасибо, я обзаведусь новой при первой же возможности.";
            link.l1.go = "exit";
        }
        if (iTemp > 10)
        {
            dialog.text = LinkRandPhrase("Ну что же, очень хорошо, ваша лицензия действует ещё " + FindRussianDaysString(iTemp) + ". Вы можете пройти.", "Всё ясно, " + GetAddress_Form(npchar) + ". Вы можете свободно проходить в город, ваша лицензия действует ещё " + FindRussianDaysString(iTemp) + ". Прошу прощения за беспокойство.", "Всё в порядке, " + GetAddress_Form(npchar) + ", не смею вас задерживать.");
            link.l1 = RandPhraseSimple("Отлично. Всего хорошего.", "Спасибо, офицер.");
            link.l1.go = "exit";
        }
        break;

    //замечение по обнаженному оружию
    case "SoldierNotBlade":
        dialog.text = LinkRandPhrase("Какого чёрта ты бегаешь по городу с обнажённым клинком? Немедленно убери оружие!", "Приказываю вам немедленно убрать оружие в ножны!", "Эй, " + GetSexPhrase("приятель", "подруга") + ", прекрати пугать народ! Убери оружие в ножны.");
        link.l1 = LinkRandPhrase("Хорошо.", "Ладно.", "Как скажешь...");
        link.l1.go = "exit";
        link.l2 = LinkRandPhrase("Чёрта с два!", "Помечтай...", "После дождичка, в четверг.");
        link.l2.go = "fight";
        npchar.greeting = "soldier_common";
        NextDiag.TempNode = "First Time";
        break;
    }
}