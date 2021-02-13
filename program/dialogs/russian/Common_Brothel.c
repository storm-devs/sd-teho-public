void ProcessDialogEvent()
{
    ref NPChar, sld, location;
    aref Link, NextDiag;
    string sTemp, sTemp1, str, str1;
    int s1, s2, s3, s4, s5, p1, iColony, crewWhoreCost, charWhoreCost = 0;

    DeleteAttribute(&Dialog, "Links");

    makeref(NPChar, CharacterRef);
    makearef(Link, Dialog.Links);
    makearef(NextDiag, NPChar.Dialog);

    // вызов диалога по городам -->
    NPChar.FileDialog2 = "DIALOGS\" + LanguageGetLanguage() + "\Brothel\" + NPChar.City + "_Brothel.c ";
                         if (LoadSegment(NPChar.FileDialog2))
    {
        ProcessCommonDialog(NPChar, Link, NextDiag);
        UnloadSegment(NPChar.FileDialog2);
    }
    // вызов диалога по городам <--
    crewWhoreCost = 50 + 7 * MOD_SKILL_ENEMY_RATE - drand(40);
    charWhoreCost = 2460 + sti(pchar.rank) * 40;

    switch (Dialog.CurrentNode)
    {
    // ============= хозяйка борделя =============
    case "First time":
        if (LAi_grp_playeralarm > 0)
        {
            dialog.text = NPCharRepPhrase(pchar,
                                          LinkRandPhrase("" + GetSexPhrase("Милый-дорогой, какие девочки?! За тобой половина гарнизона гонится, а он в бордель пожаловал!", "Шла бы ты отсюда... За тобой половина гарнизона гонится!") + "", "Вся городская стража рыщет по городу в поисках тебя. Я не идиотка, привечать тебя в такой момент...", "Попрошу удалиться из моего заведения, тебе здесь делать нечего!"),
                                          LinkRandPhrase("" + GetSexPhrase("Попробуй только дотронуться до моих девочек - я с тебя живого шкуру сдеру!", "Убирайся отсюда, мерзавка!") + "", "Грязн" + GetSexPhrase("ый", "ая") + " убийца, вон из моего заведения! Стража!!", "Я не боюсь тебя, мерзав" + GetSexPhrase("ец", "ка") + "! Скоро тебя повесят в нашем форте, далеко тебе не уйти..."));
            link.l1 = NPCharRepPhrase(pchar,
                                      RandPhraseSimple("Хех, тревога для меня не проблема...", "Им меня ни за что не поймать."),
                                      RandPhraseSimple("Помолчала бы лучше, дура...", "Заткнись, не то хуже будет..."));
            link.l1.go = "exit";
            break;
        }
        //Jason --> Заносчивый аристократ
        if (!CheckAttribute(pchar, "GenQuest.Badboy") && !CheckAttribute(npchar, "quest.Badboy") && makeint(environment.time) > 15.0 && makeint(environment.time) < 21.0 && sti(pchar.questTemp.HorseQty) > 4)
        {
            dialog.text = "Вы такой видный мужчина. И, скажу более, нравитесь моим девочкам. Я бы хотела попросить вас оказать моему заведению услугу.";
            link.l5 = "Хм... не скрою, я польщён. В чём вам требуется моя помощь?";
            link.l5.go = "Badboy";
            link.l8 = "Извини, но я сейчас занят.";
            link.l8.go = "exit";
            npchar.quest.Badboy = "true";
            break;
        }

        if (CheckAttribute(pchar, "GenQuest.Badboy.Complete") || CheckAttribute(pchar, "GenQuest.Badboy.Continue"))
        {
            if (npchar.City == pchar.GenQuest.Badboy.Brothel.City)
            {
                dialog.text = "О, вы уже вернулись! Ну как, вам удалось добиться того, чтобы " + pchar.GenQuest.Badboy.Brothel.Name + " оставил моих девочек в покое?";
                link.l5 = "Да. Более он сюда не придет.";
                link.l5.go = "Badboy_complete";
                break;
            }
        }
        // <-- Заносчивый аристократ

        //--> Jason Португалец
        if (CheckAttribute(pchar, "questTemp.HWIC.Detector"))
        {
            bool bOk = (pchar.questTemp.HWIC.Detector == "holl_win") || (pchar.questTemp.HWIC.Detector == "eng_win") || (pchar.questTemp.HWIC.Detector == "self_win");
            if (!CheckAttribute(pchar, "questTemp.Portugal") && bOk && !CheckAttribute(npchar, "quest.Portugal") && npchar.location == "Marigo_SecBrRoom" && makeint(environment.time) > 6.0 && makeint(environment.time) < 22.0)
            {
                dialog.text = "Капитан, могу я попросить вас об одном одолжении?";
                link.l5 = "Для вас, мадам, всё что угодно... я к вашим услугам!";
                link.l5.go = "Portugal";
                link.l8 = "Извини, но я сейчас занят.";
                link.l8.go = "exit";
                npchar.quest.Portugal = "true";
                break;
            }
        }
        if (CheckAttribute(pchar, "questTemp.Portugal") && pchar.questTemp.Portugal == "HostressMoney" && npchar.location == "Marigo_SecBrRoom")
        {
            dialog.text = "Вы говорили с Хьюго, минхер капитан?";
            if (sti(pchar.money) >= 10000)
            {
                link.l1 = "Более того, мадам – вот ваши деньги. Всё разрешилось самым благоприятным...";
                link.l1.go = "Portugal_3";
            }
            else
            {
                link.l1 = "Да, я передал вашу просьбу.";
                link.l1.go = "Portugal_exit";
            }
            break;
        }
        //<--Португалец
        // Addon 2016-1 Jason пиратская линейка
        if (CheckAttribute(pchar, "questTemp.Mtraxx.Retribution") && pchar.questTemp.Mtraxx.Retribution == "brothel" && npchar.location == "Tortuga_SecBrRoom")
        {
            dialog.text = "О, кто к нам пожаловал! Знаменитый корсар Чарли Принц собственной персоной!";
            link.l1 = RandSwear() + "Привет, Жанетта. Я здесь по заданию от Маркуса Тиракса.";
            link.l1.go = "mtraxx_R";
            break;
        }
        if (CheckAttribute(pchar, "questTemp.Mtraxx.Retribution") && pchar.questTemp.Mtraxx.Retribution == "brothel_repeat" && npchar.location == "Tortuga_SecBrRoom")
        {
            dialog.text = "Ты уже готов к незабываемому отдыху, отважный корсар?";
            if (sti(pchar.money) >= 31000)
            {
                link.l1 = "Конечно! Чарли Принц слов на ветер не бросает, в отличие от двух-трех десятков тысяч песо, ха-ха-ха!";
                link.l1.go = "mtraxx_R2";
            }
            else
            {
                link.l1 = "Почти... Мне показалось, что я уронил у тебя свою табакерку... Сейчас вернусь с деньгами!";
                link.l1.go = "exit";
            }
            break;
        }

        if (npchar.quest.meeting == "0")
        {
            dialog.text = RandPhraseSimple(TimeGreeting() + ". Добро пожаловать в дом терпимости. Меня зовут " + npchar.name + ", я здесь заведую всем. " + GetSexPhrase("Чем могу быть полезна, " + GetAddress_Form(NPChar) + "?", "Признаюсь, немного удивлена видеть вас здесь, " + GetAddress_Form(NPChar) + ", но смею заверить: мы оказываем услуги не только мужчинам.") + "",
                                           TimeGreeting() + ". Приветствую вас, " + GetSexPhrase("незнакомец", "девушка") + ", в моём скромном заведении. Позвольте представится, я " + NPChar.Name + " - владелица этого приюта обиженных лаской мужчин. " + GetSexPhrase("Чем я могу быть вам полезна?", "Хотя для женщин у нас тоже кое-что есть...") + "");
            npchar.quest.meeting = "1";
        }
        else
        {
            dialog.text = RandPhraseSimple(TimeGreeting() + ". Чем я могу вам помочь, " + GetAddress_Form(NPChar) + "?",
                                           TimeGreeting() + ". Что я могу для вас сделать, " + GetAddress_Form(NPChar) + "?");
        }
        if (!CheckAttribute(pchar, "questTemp.Sharlie.Gigolo")) //не идет квест девочки
        {
            if (!CheckAttribute(pchar, "GenQuest.BrothelLock")) // нет запрета от Мэри 280313
            {
                link.l2 = npchar.name + ", я хочу провести время с одной из твоих девушек.";
                link.l2.go = "Hostess_1";
            }
        }
        if (!CheckAttribute(pchar, "questTemp.Sharlie.Lock")) // не идет старт Шарля
        {
            link.l3 = "Давно я не баловал" + GetSexPhrase("", "а") + " своих парней. Можно сделать оптовый заказ на девочек?";
            link.l3.go = "ForCrew";
        }
        link.l4 = "У меня есть вопрос.";
        if (CheckCharacterItem(pchar, "CaptainBook") && !CheckAttribute(pchar, "questTemp.different.GiveShipLetters.speakBrothelMadam"))
        {
            if ((pchar.questTemp.different.GiveShipLetters.city == npchar.city) && CheckAttribute(pchar, "questTemp.different.GiveShipLetters"))
            {
                link.l4.go = "ShipLetters_1"; // генератор  "Найденные документы"
            }
            else
            {
                link.l4.go = "quests";
            }
        }
        else
        {
            link.l4.go = "quests"; //(перессылка в файл города)
        }
        //-->> квест поиска кольца мэра
        if (pchar.questTemp.different == "TakeMayorsRing" && pchar.questTemp.different.TakeMayorsRing.city == npchar.city && GetNpcQuestPastDayWOInit(npchar, "TakeMayorsRing") > 7)
        {
            link.l5 = "Послушай, " + npchar.name + ", я ищу кольцо губернатора. Он тут кутил у тебя намедни, и потерял его.";
            link.l5.go = "TakeMayorsRing_H1";
            SaveCurrentNpcQuestDateParam(npchar, "TakeMayorsRing");
        }
        //<<-- квест поиска кольца мэра
        link.l9 = "Ничем. Я уже ухожу.";
        link.l9.go = "exit";
        NextDiag.TempNode = "First time";
        break;

    case "ShipLetters_1":
        pchar.questTemp.different.GiveShipLetters.speakBrothelMadam = true;
        dialog.text = RandPhraseSimple("Чего ты хочешь, красавчик?", "Слушаю Вас внимательно, капитан.");
        link.l1 = "Послушай, " + npchar.name + ", я обнаружил" + GetSexPhrase("", "а") + " эти бумаги в приватной зале вашего заведения...";
        link.l1.go = "ShipLetters_2";
        break;

    case "ShipLetters_2":
        if (sti(pchar.questTemp.different.GiveShipLetters.variant) == 0)
        {
            dialog.text = "Дайте-ка взглянуть! Хм... какой-то неизвестный капитан обронил документы? Я думаю, такие вопросы нужно задавать начальнику порта.";
            link.l1 = "Возможно, возможно ...";
            link.l1.go = "exit";
        }
        else
        {
            dialog.text = "Дайте-ка взглянуть! О! Судя по имени, они принадлежат моему уважаемому клиенту и достойному гражданину нашего города. Я могу сама передать документы";
            link.l1 = "Пожалуй, нет ...";
            link.l1.go = "exit";
            link.l2 = "Замечательно! Всегда рад" + GetSexPhrase("", "а") + " помочь уважаемому человеку и достойному заведению.";
            link.l2.go = "ShipLetters_3";
        }
        break;

    case "ShipLetters_3":
        TakeItemFromCharacter(pchar, "CaptainBook");
        pchar.questTemp.different = "free";
        pchar.quest.GiveShipLetters_null.over = "yes"; //снимаем таймер
        AddQuestRecord("GiveShipLetters", "2");
        CloseQuestHeader("GiveShipLetters");
        DeleteAttribute(pchar, "questTemp.different.GiveShipLetters");
        NextDiag.CurrentNode = NextDiag.TempNode;
        DialogExit();
        break;

    case "Hostess_1":
        if (!CheckAttribute(npchar, "quest.selected"))
        {
            if (CheckNPCQuestDate(npchar, "quest.date"))
            {
                dialog.text = "" + GetSexPhrase("Мы всегда рады клиенту. Скажи мне, дорогой, ты уже присмотрел кого-то или тебе всё равно?", "Ну что же, мои девочки вполне смогут тебе... помочь. Ты присмотрела кого-нибудь, или тебе всё равно?") + "";
                Link.l1 = "" + GetSexPhrase("Хех, мне нужна девка и немедленно, а кто она такая - наплевать. У тебя все они симпатичные...", "Да любая, лишь бы дело своё знала...") + "";
                Link.l1.go = "Hostess_NotChoice";
                Link.l2 = "Да, есть одна, " + GetSexPhrase("что мне приглянулась...", "с ней было бы приятнее...") + "";
                Link.l2.go = "Hostess_Choice";
            }
            else
            {
                dialog.text = "Сегодня я уже не могу дать тебе девочку, кроме тебя у меня ещё есть клиенты. Приходи завтра, обслужим как следует!";
                Link.l1 = "Эх, жаль" + GetSexPhrase(", я только вошёл во вкус", "") + "... Ну да ладно.";
                Link.l1.go = "exit";
            }
        }
        else
        {
            dialog.text = "Хм, ты уже оплатил" + GetSexPhrase("", "а") + " девушку. Так что займись ею вплотную, так сказать, и не отвлекай меня по пустякам.";
            Link.l1 = "Хорошо, уже иду.";
            Link.l1.go = "exit";
        }
        break;

    case "Hostess_NotChoice":
        sld = GetFreeHorseRef(npchar.city);
        location = &locations[FindLocation(npchar.city + "_Brothel")];
        if (sld.id == "none" || GetNpcQuestPastDayParam(location, "Brothel_date") > 98)
        {
            dialog.text = "Сейчас у меня нет свободных девушек, тебе нужно будет зайти сюда через пару дней.";
            Link.l1 = "Хорошо, как скажешь.";
            Link.l1.go = "exit";
        }
        else
        {
            dialog.text = "" + GetSexPhrase("Ну что, жеребец, превосходно!", "У меня они все умелые, можешь не сомневаться.") + " Могу предложить прекрасную девушку по имени " + GetFullName(sld) + ", она сейчас свободна. Стоить это удовольствие будет " + FindRussianMoneyString(sti(sld.quest.price) + charWhoreCost) + ". Соглас" + GetSexPhrase("ен", "на") + "?";
            Link.l1 = "Нет, пожалуй, откажусь. Дороговато...";
            Link.l1.go = "exit";
            if (sti(pchar.money) >= (sti(sld.quest.price) + charWhoreCost))
            {
                Link.l2 = "Конечно, соглас" + GetSexPhrase("ен", "на") + ", какие могут быть вопросы?!";
                Link.l2.go = "Hostess_NotChoice_agree";
                npchar.quest.choiceIdx = sld.index;
            }
            else
            {
                Link.l1 = "Агрх, нет у меня сейчас таких денег...";
                Link.l1.go = "exit";
            }
        }
        break;

    case "Hostess_NotChoice_agree":
        sld = &characters[sti(npchar.quest.choiceIdx)];
        if (sti(pchar.money) >= (sti(sld.quest.price) + charWhoreCost))
        {
            dialog.text = "Отлично, дорог" + GetSexPhrase("ой", "уша") + ". " + sld.name + " будет ждать тебя в комнате для уединения на втором этаже.";
            Link.l1 = "" + GetSexPhrase("Хех, ну я пошёл", "Ну, я побежала") + "...";
            Link.l1.go = "exit";
            AddMoneyToCharacter(pchar, -(sti(sld.quest.price) + charWhoreCost));
            sld.dialog.currentnode = "Horse_ReadyFack";
            //--> таймер на возврат, чтобы не вечно ждали
            str = npchar.city;
            pchar.quest.(str).win_condition.l1 = "Timer";
            pchar.quest.(str).win_condition.l1.date.day = GetAddingDataDay(0, 0, 1);
            pchar.quest.(str).win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
            pchar.quest.(str).win_condition.l1.date.year = GetAddingDataYear(0, 0, 1);
            pchar.quest.(str).win_condition = "Brothel_checkVisitTime";
            pchar.quest.(str).HorseId = sld.id;
            pchar.quest.(str).locator = sld.location.locator;
            //<-- таймер на возврат, чтобы не вечно ждали
            ChangeCharacterAddressGroup(sld, npchar.city + "_Brothel_room", "goto", "goto" + (rand(2) + 1));
            LocatorReloadEnterDisable(npchar.city + "_Brothel", "reload2_back", false); //открываем комнату
            npchar.quest.selected = true;                                               //флаг взял девку у хозяйки
            SetNPCQuestDate(npchar, "quest.date");                                      //дату взятия запишем
            for (int n = 0; n < MAX_CHARACTERS; n++)
            {
                makeref(sld, Characters[n]);
                if (sld.location == npchar.city + "_Brothel" && CheckAttribute(sld, "CityType") && sld.CityType == "horse")
                {
                    sld.dialog.currentnode = "Horse_4";
                }
            }

            // генератор найденных бумаг
            if ((rand(4) == 1) && (pchar.questTemp.different == "free") && (!CheckCharacterItem(pchar, "CaptainBook")) && GetNpcQuestPastDayWOInit(npchar, "questShipLetters") > 10)
            {
                pchar.questTemp.different = "GiveShipLetters";
                pchar.questTemp.different.GiveShipLetters = "toBrothel";
                pchar.questTemp.different.GiveShipLetters.Id = GetFullName(npchar);
                pchar.questTemp.different.GiveShipLetters.city = npchar.city;
                pchar.questTemp.different.GiveShipLetters.variant = rand(2);
                p1 = rand(20 - MOD_SKILL_ENEMY_RATE) + 1; // даем хотя бы один день
                s1 = rand(80 - pchar.rank - p1) * 50 + rand(100);
                s2 = s1 * 2;
                s3 = s1 * rand(GetCharacterSPECIAL(pchar, "Luck")) + s1;
                s4 = s2 + s3;
                s5 = s4 * GetCharacterSPECIAL(pchar, "Charisma");
                pchar.questTemp.different.GiveShipLetters.price1 = s1;
                pchar.questTemp.different.GiveShipLetters.price2 = s2;
                pchar.questTemp.different.GiveShipLetters.price3 = s3;
                pchar.questTemp.different.GiveShipLetters.price4 = s4;
                pchar.questTemp.different.GiveShipLetters.price5 = s5;

                sld = ItemsFromID("CaptainBook");
                sld.CityName = XI_ConvertString("Colony" + npchar.city + "Gen");
                //ложим бумаги в итем
                sTemp = "_Brothel_room";
                sTemp1 = "_town";
                sld.shown = true;
                sld.startLocation = pchar.questTemp.different.GiveShipLetters.city + sTemp;
                sld.startLocator = "item" + (rand(4) + 1);
                sld.endLocation = pchar.questTemp.different.GiveShipLetters.city + sTemp1;
                pchar.questTemp.different.GiveShipLetters.item = true; //флаг -  бумаги валяются в итемах
                Log_QuestInfo("Бумаги находятся в локации " + sld.startLocation + ", в локаторе " + sld.startLocator + " p1 : " + p1);

                pchar.quest.CheckShipLetters.win_condition.l1 = "location";
                pchar.quest.CheckShipLetters.win_condition.l1.location = sld.endLocation;
                pchar.quest.CheckShipLetters.function = "CheckShipLetters";

                SetTimerFunction("GiveShipLetters_null", 0, 0, p1); //освобождаем разрешалку на миниквесты
                SaveCurrentNpcQuestDateParam(npchar, "questShipLetters");
            }
            // генератор - "Повод для спешки"
            if ((rand(5) == 2) && !CheckAttribute(pchar, "questTemp.ReasonToFast") && GetNpcQuestPastDayWOInit(npchar, "questReasonToFast") > 20 && !CheckAttribute(pchar, "questTemp.Sharlie.Lock")) // Addon-2016 Jason
            {
                iColony = FindColony(npchar.city);
                if (sti(Colonies[iColony].HeroOwn) == false && npchar.city != "Panama" && npchar.city != "Charles")
                {
                    pchar.questTemp.ReasonToFast = "Begin";
                    pchar.questTemp.ReasonToFast.city = npchar.city;
                    sTemp1 = "_town";
                    pchar.quest.CheckReasonToFast.win_condition.l1 = "location";
                    pchar.quest.CheckReasonToFast.win_condition.l1.location = npchar.city + sTemp1;
                    pchar.quest.CheckReasonToFast.function = "ReasonToFast_CheckHorse";
                    SaveCurrentNpcQuestDateParam(npchar, "questReasonToFast");
                }
            }
        }
        else
        {
            dialog.text = "Всё бы было хорошо, но дело в том, что " + sld.name + " - девушка недешёвая, стоит " + FindRussianMoneyString(sti(sld.quest.price) + charWhoreCost) + ". А у тебя, насколько я вижу, таких денег нет. Приходи как разбогатеешь" + GetSexPhrase(", родной", "") + "...";
            Link.l1 = "Эх, вот так всегда...";
            Link.l1.go = "exit";
        }
        break;

    case "Hostess_Choice":
        dialog.text = "Я всегда рада, когда между девочками и клиентами возникают тёплые чувства... Назови мне её имя.";
        Link.l1.edit = 9;
        Link.l1 = "";
        Link.l1.go = "Hostess_Choice_1";
        break;

    case "Hostess_Choice_1":
        sld = CheckHorsesName(npchar.city, 9);
        if (sld.id == "none")
        {
            dialog.text = "Хм, ты ошибаешься, у меня нет такой девочки в заведении. Возможно, ты неверно называешь её имя.";
            Link.l1 = "Хм, но я только что с ней разговаривал" + GetSexPhrase("", "а") + ".";
            Link.l1.go = "Hostess_Choice_2";
            Link.l2 = "Пожалуй, мне лучше уточнить её имя. Я позже переговорю с тобой на эту тему.";
            Link.l2.go = "exit";
        }
        else
        {
            dialog.text = GetFullName(sld) + ", ты о ней говоришь?";
            Link.l1 = "Ага, именно о ней.";
            Link.l1.go = "Hostess_NotChoice_agree";
            Link.l2 = "Нет, не о ней.";
            Link.l2.go = "Hostess_Choice_2";
            npchar.quest.choiceIdx = sld.index;
        }
        break;

    case "Hostess_Choice_2":
        dialog.text = "Тогда тебе нужно назвать её имя ещё раз, возможно я пойму, о ком идет речь.";
        Link.l1.edit = 9;
        Link.l1 = "";
        Link.l1.go = "Hostess_Choice_1";
        Link.l2 = "Пожалуй, мне лучше уточнить её имя. Я позже переговорю с тобой на эту тему.";
        Link.l2.go = "exit";
        break;
    //==> команда
    case "ForCrew":
        dialog.text = "Хмм... помочь ребятам 'сбросить пар'? У меня солидное заведение и лучшие девочки. Однако я знаю, мир тесен, портовых 'умелиц', способных ублажить всю свободную от вахты команду. С тебя " + FindRussianMoneyString(GetCrewQuantity(pchar) * crewWhoreCost) + ".";
        link.l1 = "Хорошо, я соглас" + GetSexPhrase("ен", "на") + " заплатить эти деньги.";
        link.l1.go = "ForCrew_1";
        link.l2 = "Думаю, они обойдутся как-нибудь...";
        link.l2.go = "exit";
        break;

    case "ForCrew_1":
        if (sti(Pchar.money) >= GetCrewQuantity(pchar) * crewWhoreCost && GetCrewQuantity(pchar) > 0)
        {
            AddMoneyToCharacter(Pchar, -makeint(GetCrewQuantity(pchar) * crewWhoreCost));
            AddCrewMorale(Pchar, 10);
            ChangeCharacterComplexReputation(pchar, "authority", 1);
            LAi_Fade("", "");
            AddTimeToCurrent(5 + rand(1), rand(30));
            DialogExit();
        }
        else
        {
            dialog.text = "Это, конечно, не моё дело, но мне кажется, что тебе сначала нужно заработать на команду, а потом думать о её морали.";
            link.l1 = "Пожалуй, да...";
            link.l1.go = "exit";
        }
        break;

    case "Woman_FackYou":
        dialog.text = "Мил" + GetSexPhrase("ый", "ая") + ", ты куда это полез" + GetSexPhrase("", "ла") + "?! Надо же, а казался порядочн" + GetSexPhrase("ым капитаном", "ой девушкой") + ".\nНу а теперь так просто тебе не уйти, красав" + GetSexPhrase("чик", "ица") + ". Подрежут тебе крылышки...";
        link.l1 = "Заткнись, дура...";
        link.l1.go = "exit_setOwner";
        LAi_group_Attack(NPChar, Pchar);
        if (rand(3) != 1)
            SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
        break;

    //поиски кольца губернатора
    case "TakeMayorsRing_H1":
        dialog.text = "Никакого кольца я не находила.";
        link.l1 = "А девочки твои?";
        link.l1.go = "TakeMayorsRing_H2";
        break;

    case "TakeMayorsRing_H2":
        dialog.text = "Девочки тоже. Если клиент что-то забывает или теряет, то они всё приносят мне обязательно. Никто кольцо губернатора мне не приносил.";
        link.l1 = "Понятно... А может кто-то всё-таки решил его придержать?";
        link.l1.go = "TakeMayorsRing_H3";
        break;

    case "TakeMayorsRing_H3":
        dialog.text = "Это вряд ли. Девочкам разрешается оставлять себе подарки клиентов, и только.";
        link.l1 = "Понятно... Спасибо тебе, " + npchar.name + ".";
        link.l1.go = "exit";
        break;

    case "Hostess_inSexRoom":
        dialog.text = "Ах, вот и ты...";
        link.l1 = "Так точно, моя королева!";
        link.l1.go = "exit";
        pchar.quest.SexWithHostess_null.over = "yes"; //нулим таймер на не пришел
        NextDiag.TempNode = "First time";
        AddDialogExitQuestFunction("SexWithHostess_fack");
        AddCharacterExpToSkill(pchar, "Leadership", 100);
        AddCharacterHealth(pchar, 5);
        break;

    // ================================== рядовой состав =======================================
    case "Horse_talk":
        if (LAi_grp_playeralarm > 0)
        {
            dialog.text = NPCharRepPhrase(pchar,
                                          LinkRandPhrase("Вам лучше уйти из заведения!", "Вся городская стража рыщет по городу! Вам лучше уйти...", "Надебоширили - и к нам?! Нет уж, в другой раз..."),
                                          LinkRandPhrase("Убирайся!!", "Грязн" + GetSexPhrase("ый", "ая") + " убийца, вон отсюда! Стража!!", "Я не боюсь тебя, мерзав" + GetSexPhrase("ец", "ка") + "! Скоро тебя повесят в нашем форте, далеко тебе не уйти..."));
            link.l1 = NPCharRepPhrase(pchar,
                                      RandPhraseSimple("Хех, тревога для меня не проблема...", "Им меня ни за что не поймать."),
                                      RandPhraseSimple("Хех, ну и дура же ты...", "Заткнись, не то хуже будет..."));
            link.l1.go = "exit";
            break;
        }
        dialog.text = NPCStringReactionRepeat("Здравствуйте, " + GetAddress_Form(NPChar) + "" + GetSexPhrase("", ", хи-хи-хи..") + ". Вам нужно обратиться к хозяйке заведения, все заказы проходят через неё.",
                                              "Ой, это опять вы. Простите, но вам нужно сначала уладить все вопросы с хозяйкой. Прошу вас пройти к ней.",
                                              "Послушайте, " + GetAddress_Form(NPChar) + "" + GetSexPhrase(", я очень надеюсь, что вы так же упрямы и в других делах, а не только в разговорах... Ещё", "я ещё") + " раз прошу вас пройти к хозяйке заведения.",
                                              "Ах, " + GetAddress_Form(NPChar) + "" + GetSexPhrase(", какой же вы... настойчивый!", ", хи-хи-хи... Вы, однако, натойчивы.") + " Вам нужно пройти к хозяйке заведения для оформления заказа.", "block", 1, npchar, Dialog.CurrentNode);
        link.l1 = HeroStringReactionRepeat("Хорошо, " + GetSexPhrase("красавица, ", "") + "я понял" + GetSexPhrase("", "а") + ".", "А-а, да, конечно...",
                                           "" + GetSexPhrase("Можешь не сомневаться, красавица, я упрям и силен, как бык!", "Да-да...") + "", "" + GetSexPhrase("Вот дьявол, что-то упустил... Прости, милая.", "Хорошо, хорошо.") + "", npchar, Dialog.CurrentNode);
        link.l1.go = "exit";
        Link.l2 = "А где она находится?";
        Link.l2.go = "Horse_1";
        Link.l3 = LinkRandPhrase("" + GetSexPhrase("Аргх, красавица, в твоих глазах можно утонуть...", "Ты выглядишь просто замечательно, малышка!") + "", "" + GetSexPhrase("Знаешь, я давно не видел такой красивой женщины!", "Знаешь, я давненько не встречала такой симпатяшки!") + "", "" + GetSexPhrase("Эх, милая, ты невероятно прелестна.", "Эх, надоели все эти неотесаные мужланы... А ты просто прелесть!") + "");
        if (!CheckAttribute(npchar, "quest.choice"))
        {
            Link.l3.go = "Horse_2";
        }
        else
        {
            Link.l3.go = "HorseChoice_" + npchar.quest.choice;
        }
        //-->> квест поиска кольца мэра
        if (pchar.questTemp.different == "TakeMayorsRing" && pchar.questTemp.different.TakeMayorsRing.city == npchar.city && GetNpcQuestPastDayWOInit(npchar, "TakeMayorsRing") > 7)
        {
            link.l5 = LinkRandPhrase("Слушай, " + GetSexPhrase("красавица", "милочка") + ", ты не находила здесь обручального кольца? Потерял его тут один человек...",
                                     "Дорогуша, ты, случаем, не находила в вашем заведении обручального кольца?",
                                     "Послушай, " + GetSexPhrase("рыба моя", "малышка") + ", колечко не попадалось тебе тут, обручальное?");
            link.l5.go = "TakeMayorsRing_S1";
            SaveCurrentNpcQuestDateParam(npchar, "TakeMayorsRing");
        }
        //<<-- квест поиска кольца мэра

        // Addon 2016-1 Jason пиратская линейка
        if (pchar.location == "santodomingo_brothel" && CheckAttribute(pchar, "questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "jewelry_1" && npchar.id == "HorseGen_" + reload_location_index + "_2")
        {
            link.l6 = "Привет, дорогуша. Я от Маркуса Тиракса, хочу показать тебе янтарное ожерелье...";
            link.l6.go = "mtraxx";
        }
        NextDiag.TempNode = "Horse_talk";
        break;

    case "Horse_1":
        dialog.text = "Она в своём кабинете, вы можете пройти к ней отсюда через дверь, противоположную выходу на улицу, либо через улицу с другой стороны дома. Её зовут " + characters[GetCharacterIndex(npchar.city + "_Hostess")].name + ".";
        Link.l1 = "Понятно, " + GetSexPhrase("милая", "дорогуша") + ", спасибо.";
        Link.l1.go = "exit";
        break;

    case "Horse_2":
        if (rand(1))
        {
            dialog.text = LinkRandPhrase("Ах, боже мой, до чего приятно слышать такое! Слушай, я сейчас свободна, так что если ты выберешь меня, то не пожалеешь...", "Ты действительно так считаешь? Мне очень и очень приятно... Послушай, я сейчас свободна, так что ты можешь выбрать меня." + GetSexPhrase(" Я обещаю тебе море любви и океан ласки...", "") + "", "" + GetSexPhrase("Вот как?! Хм, не скрою, я польщена, не часто приходится слышать в свой адрес такие слова...", "Эх, девушка... как меня достали эти мужики...") + " Слушай, я не занята в данный момент, так что я предлагаю тебе выбрать меня. Обещаю, что ты останешься довол" + GetSexPhrase("ен", "ьна") + "...");
            link.l1 = "Хех, именно тебя и выбираю!";
            Link.l1.go = "Horse_3";
            Link.l2 = "" + GetSexPhrase("Не-е-ет, это был просто комплимент прекрасной даме", "Это был просто комплимент") + ".";
            Link.l2.go = "exit";
            npchar.quest.choice = 0; //был базар, но ГГ потом отказался
        }
        else
        {
            dialog.text = LinkRandPhrase("" + GetSexPhrase("Знаешь что я тебе скажу, милый мой? Не нужно мне пустых разговоров. Займись делом!", "Ну вот только этого мне не хватало - комплиментов от женщин!") + "", "" + GetSexPhrase("Ты тоже воображаешь, что все женщины любят ушами? Хм, это очень зря... Если хочешь меня - плати хозяйке заведения, а трепотня мне не нужна.", "Девушка, не растрачивайтесь на пустые слова. Хотите дел - платите...") + "", "" + GetSexPhrase("Еще один любитель чувственности... Плати - и я буду твоей, но только без этого нежного бреда!", "Ты чего, дорогуша? Хочешь удовольствия - плати, а не занимайся болтовней!") + "");
            link.l1 = "Ого, какая хватка!";
            Link.l1.go = "exit";
            npchar.quest.choice = 2; //ГГ послали
        }
        break;

    case "Horse_3":
        dialog.text = characters[GetCharacterIndex(npchar.city + "_Hostess")].name + " всё оформляет в своём кабинете. Иди к ней" + GetSexPhrase(", мой герой,", "") + " и назови моё имя - " + npchar.name + ". Я буду тебя ждать...";
        Link.l1 = "Понятно, милая, скоро буду...";
        Link.l1.go = "exit";
        npchar.quest.choice = 1; //она согласная
        SetNPCQuestDate(npchar, "quest.choice");
        break;

    case "Horse_4":
        dialog.text = NPCStringReactionRepeat("Ты уже оплатил" + GetSexPhrase("", "а") + " девушку, она ждет тебя, поднимайся наверх.",
                                              "Я же тебе сказала - поднимайся к ней.",
                                              "Слушай внимательно, ещё раз повторяю - поднимайся к ней...",
                                              "Бесполезно говорить, не доходит...", "block", 1, npchar, Dialog.CurrentNode);
        link.l1 = HeroStringReactionRepeat("Да, я знаю.", "Я помню.",
                                           "Можешь не повторять, о ней я помню.", "Хм, о чем это ты?..", npchar, Dialog.CurrentNode);
        link.l1.go = "exit";
        NextDiag.TempNode = "Horse_4";
        break;

    //===>> реакция на попытки пофлиртовыть, если флирт уже был
    case "HorseChoice_0":
        if (!CheckAttribute(npchar, "quest.sexHappend"))
        {
            dialog.text = NPCStringReactionRepeat("Что-то я тебя не пойму." + GetSexPhrase(" То комплименты делаешь, то вдруг на попятную идёшь. Странный тип...", "") + "",
                                                  "Опять со своим комплиментами? Хм, иди к хозяйке, с ней всё решай.",
                                                  "Хм, и не надоело тебе? Сказала же - иди к хозяйке заведения.",
                                                  "Нам нельзя здесь оскорблять клиентов, но ты нарываешься, мил" + GetSexPhrase("ый", "ая") + "...", "block", 1, npchar, Dialog.CurrentNode);
            link.l1 = HeroStringReactionRepeat("Так вышло, знаешь ли...", "Хорошо, я так и сделаю.",
                                               "Да-да, я понял" + GetSexPhrase("", "а") + "...", "Хм, извини, дорогуша.", npchar, Dialog.CurrentNode);
            link.l1.go = "exit";
        }
        else
        {
            dialog.text = "Спасибо за комплимент. Если ты хочешь взять меня, то иди к хозяйке заведения. Всё как всегда...";
            Link.l1 = "Понятно.";
            Link.l1.go = "exit";
        }
        break;

    case "HorseChoice_1":
        if (!CheckAttribute(npchar, "quest.sexHappend"))
        {
            if (!CheckNPCQuestDate(npchar, "quest.choice"))
            {
                dialog.text = NPCStringReactionRepeat("" + GetSexPhrase("Милый, мы всё оговорили. ", "") + "Не заставляй меня долго ждать...",
                                                      "" + GetSexPhrase("Хм, послушай, милый, мне", "Мне") + " очень приятны всё твои слова, но пора уже и за дело браться...",
                                                      "Послушай, может ты всё-таки уладишь всё с хозяйкой?..",
                                                      "Хм, даже не знаю, что и сказать...", "block", 1, npchar, Dialog.CurrentNode);
                link.l1 = HeroStringReactionRepeat("Да ни за что на свете!", "Обязательно!",
                                                   "Да, конечно!", "Бегу, бегу к хозяйке...", npchar, Dialog.CurrentNode);
                link.l1.go = "exit";
            }
            else
            {
                dialog.text = "Я тебя ждала, а ты так и не взял" + GetSexPhrase("", "а") + " меня! Не могу сказать, что я в восторге от этого...";
                Link.l1 = "Гм, так получилось...";
                Link.l1.go = "exit";
                npchar.quest.choice = 0; //был базар, но ГГ потом отказался
            }
        }
        else
        {
            dialog.text = "Ах-х, это опять ты, мо" + GetSexPhrase("й славный корсар", "я славная девушка") + "! Если тебе опять нужна я, то иди к хозяйке - не пожалеешь..." + GetSexPhrase(" Кстати, я тебя узнала, дорогой, только мы вынуждены обращаться ко всем клиентам стандартно, ты уж извини...", "") + "";
            Link.l1 = "Подожди меня совсем чуть-чуть, " + GetSexPhrase("красавица", "милашка") + ", и мы снова с тобой уединимся.";
            Link.l1.go = "exit";
            Link.l2 = "Мне очень приятно, что ты меня запомнила, но сейчас провести с тобой ночь я, сожалению, не могу.";
            Link.l2.go = "HorseChoice_1_Add";
        }
        break;

    case "HorseChoice_2":
        if (!CheckAttribute(npchar, "quest.sexHappend"))
        {
            dialog.text = NPCStringReactionRepeat("Вот что," + GetSexPhrase(" милый друг,", "") + " займись-ка лучше делом. Это полезней будет, чем языком чесать.",
                                                  "" + GetSexPhrase("Хм, странный ты,", "Ну что ты") + " талдычишь одно и тоже...",
                                                  "Послушай, может хватит уже?!",
                                                  "Хм, ну надо же, ничего нового" + GetSexPhrase(", опять глупые попытки очаровать. Хочешь со мной переспать - иди к хозяйке заведения, недоумок!", "...") + "", "block", 1, npchar, Dialog.CurrentNode);
            link.l1 = HeroStringReactionRepeat("Да, слышал" + GetSexPhrase("", "а") + "...", "Хм, вот так оно и выходит...",
                                               "Хм, может хватит, а может и нет...", "Осторожней в выражениях" + GetSexPhrase(", коза", "") + "...", npchar, Dialog.CurrentNode);
            link.l1.go = "exit";
        }
        else
        {
            dialog.text = "А-а-а, это опять ты! " + GetSexPhrase("И снова с глупыми хвалебными речами, ничего не меняется в этом мире... Е", "Напоминаю, е") + "сли хочешь " + GetSexPhrase("переспать", "побаловаться") + " со мной - плати хозяйке заведения, а слова твои мне безразличны...";
            Link.l1 = "Хех, кто бы сомневался...";
            Link.l1.go = "exit";
        }
        break;

    case "HorseChoice_1_Add":
        dialog.text = "Хм, не скажу, что меня это обрадовало... Очень жаль.";
        Link.l1 = "Извини...";
        Link.l1.go = "exit";
        npchar.quest.choice = 0;
        break;

    //===>> секс
    case "Horse_ReadyFack":
        // Addon 2016-1 Jason пиратская линейка
        if (pchar.location == "SantoDomingo_Brothel_room" && CheckAttribute(pchar, "questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "jewelry_2" && npchar.name == "Габриэла")
        {
            dialog.text = "А вот и ты! Очень хорошо. Здесь можно не опасаться, что нас подслушают...";
            Link.l1 = "Так это тебе испанец подарил голубой янтарь?";
            Link.l1.go = "mtraxx_2";
            break;
        }
        if (!CheckAttribute(npchar, "quest.choice"))
            npchar.quest.choice = 0;
        switch (npchar.quest.choice)
        {
        case "0":
            dialog.text = RandPhraseSimple("Очень рада видеть тебя в комнате уединения. " + GetSexPhrase("И чем мы дальше займёмся?", "Ну что же, будем развлекаться?") + "", "Проходи, не стесняйся" + GetSexPhrase(", чувствуй себя как дома на ближайшие два часа.", ". Я сумею тебя... развлечь, не переживай.") + "");
            Link.l1 = RandPhraseSimple("Скучать не будем, полагаю...", "" + GetSexPhrase("Давай повеселимся, детка!", "Не будем терять времени!") + "");
            break;
        case "1":
            dialog.text = "Ах, вот и ты, мо" + GetSexPhrase("й славный корсар! Я кое-что обещала тебе и готова сдержать своё слово", "я славная девушка! Следующие два часа ты не забудешь никогда") + "...";
            Link.l1 = "Ух, как заманчиво звучит...";
            break;
        case "2":
            dialog.text = "А-а-а, приш" + GetSexPhrase("ел", "ла") + ", наконец-то. Ну, не будем терять времени!";
            Link.l1 = "" + GetSexPhrase("Не будем, киска...", "Ну, покажи мне, что ты можешь...") + "";
            break;
        }
        Link.l1.go = "exit";
        //--> кол-во посещений
        if (!CheckAttribute(npchar, "quest.sexHappend"))
            npchar.quest.sexHappend = 1;
        else
            npchar.quest.sexHappend = sti(npchar.quest.sexHappend) + 1;
        pchar.GenQuest.BrothelCount = sti(pchar.GenQuest.BrothelCount) + 1; // для Данек
        Achievment_SetStat(pchar, 23, 1);
        //<-- кол-во посещений
        str = npchar.city;
        pchar.quest.(str).win_condition.l1 = "ExitFromLocation";
        pchar.quest.(str).win_condition.l1.location = pchar.location;
        pchar.quest.(str).win_condition = "Brothel_checkVisitTime";
        pchar.questTemp.HorseQty = sti(pchar.questTemp.HorseQty) + 1; //счетчик
        NextDiag.TempNode = "Horse_AfterSex";
        AddDialogExitQuest("PlaySex_1");
        // кач от борделя
        if (CheckNPCQuestDate(pchar, "BrothelSex"))
        {
            if (IsEquipCharacterByArtefact(pchar, "totem_03"))
                AddCharacterHealth(pchar, 10);
            else
                AddCharacterHealth(pchar, 5);
            SetNPCQuestDate(pchar, "BrothelSex");
        }
        // изменение статусов
        ChangeCharacterComplexReputation(pchar, "nobility", -1);
        AddCharacterExpToSkill(pchar, "Leadership", 30);
        AddCharacterExpToSkill(pchar, "FencingS", -15);
        AddCharacterExpToSkill(pchar, "Pistol", -15);
        break;

    case "Horse_AfterSex":
        if (CheckAttribute(pchar, "questTemp.ReasonToFast") && pchar.questTemp.ReasonToFast == "Begin")
        {
            dialog.text = "Капитан, а чего ты так" + GetSexPhrase("ой", "ая") + " не разговорчив" + GetSexPhrase("ый", "ая") + "?";
            link.l1 = LinkRandPhrase("Уж как" + GetSexPhrase("ой", "ая") + " есть.", "В следущий раз поболтаем.", RandPhraseSimple("Я тебе не за разговоры плачу.", "Зато ты, " + GetSexPhrase("красотка", "милочка") + ", прямо соловьём заливалась."));
            link.l1.go = "exit";
            link.l2 = "" + GetSexPhrase("Ты была так хороша, что я онемел от восторга! В редкой женщине совмещено столько красоты и темперамента", "Ох-х, умеешь ты всё-таки доставить удовольствие женщине... Я восхищена.") + ".";
            link.l2.go = "Horse_ReasonToFast_1";
        }
        else
        {
            switch (npchar.quest.choice)
            {
            case "0":
                dialog.text = LinkRandPhrase("Тебе понравилось?", "Ну, что скажешь? Всё в порядке?", "Как дела," + GetSexPhrase(" корсар, всё", " всё") + " нормально?");
                Link.l1 = RandPhraseSimple("" + GetSexPhrase("Конечно, всё в порядке", "А ты и впрямь... умеешь") + ".", "" + GetSexPhrase("Всё в норме, крошка", "Ты знаешь, я вполне довольна") + ".");
                Link.l1.go = "exit";
                break;
            case "1":
                dialog.text = LinkRandPhrase("Ну что, я выполнила обещание?", "Ну, как" + GetSexPhrase(" я тебе, понравилась", ", тебе понравилось") + "?", "Я надеюсь, " + GetSexPhrase("ты доволен, потому что я о-о-очень довольна", "ты довольна. Я старалась") + "...");
                Link.l1 = RandPhraseSimple("Да, мне всё очень понравилось.", "" + GetSexPhrase("Отлично покувыркались, ты была на высоте!", "Всё было просто замечательно!") + "");
                Link.l1.go = "exit";
                break;

            case "2":
                dialog.text = RandPhraseSimple("Ну всё, тебе пора.", "Время вышло," + GetSexPhrase(" корсар,", "") + " тебе пора на выход.");
                Link.l1 = RandPhraseSimple("Ага, пока...", "До свидания и спасибо тебе...");
                Link.l1.go = "exit";
                break;
            }
            NextDiag.TempNode = "Horse_AfterSex_2";
        }
        break;

    case "Horse_AfterSex_2":
        if (CheckAttribute(pchar, "GenQuest.EncGirl") && pchar.GenQuest.EncGirl == "Bag_BrothelRoom" && !CheckCharacterItem(pchar, "leather_bag"))
        {
            dialog.text = "Ну, как вам у нас понравилось?";
            link.l1 = "Слушай, красотка, а не видала ли ты где-то здесь саквояж?";
            link.l1.go = "EncGirl_GetBag";
        }
        else
        {
            dialog.text = LinkRandPhrase("Заходи к нам еще как-нибудь...", "До свидания и до новых встреч...", "Будем рады видеть тебя у нас ещё...");
            Link.l1 = "Ладно...";
            Link.l1.go = "exit";
            NextDiag.TempNode = "Horse_AfterSex_2";
        }
        break;

    case "EncGirl_GetBag":
        dialog.text = "Это такой коричневый сундучок с ручкой?";
        link.l1 = "Да, что-то подобное...";
        link.l1.go = "EncGirl_GetBag1";
        break;

    case "EncGirl_GetBag1":
        dialog.text = "Поскольку хозяйки у этого сундучка не нашлось, то мадам отнесла его к себе в будуар.";
        link.l1 = "Спасибо, детка. До свидания.";
        link.l1.go = "exit";
        pchar.GenQuest.EncGirl = "Bag_BrothelHostess";
        NextDiag.TempNode = "Horse_AfterSex_2";
        break;

    // --> генератор - "Повод для спешки"
    case "Horse_ReasonToFast_1":
        dialog.text = "Тогда заходи ещё, я всегда буду тебе рада... Ты так" + GetSexPhrase("ой милый, не то что другие", "ая милая, не то, что эти мужики") + " - ни здрасьте, ни до свиданья, да ещё обидеть норовят...";
        link.l1 = "О чём это ты?..";
        link.l1.go = "Horse_ReasonToFast_2";
        break;

    case "Horse_ReasonToFast_2":
        pchar.questTemp.ReasonToFast.speakHorse = true;
        dialog.text = "Да был перед тобой караульный старшина. Он вообще-то к нам не ходит, а тут принесла нелёгкая. Ещё и меня выбрал... Возился-возился, потом обозвал меня неумёхой и заторопился в бухту какую-то. Так быстро убежал, чуть было портки не оставил, ха-ха-ха...";
        link.l1 = "Тебе ли не знать, " + GetSexPhrase("красавица", "дорогая") + ", какие мужики бывают? Жене сказал, что в бордель пошёл, любовнице - что к жене торопится, а сам - в бухту, на патрулирование. " + GetSexPhrase("Хо-хо-хо-хо!..", "Ха-ха-ха!") + "";
        link.l1.go = "Horse_ReasonToFast_3";
        break;

    case "Horse_ReasonToFast_3":
        NextDiag.TempNode = "Horse_AfterSex_2";
        ReOpenQuestHeader("ReasonToFast");
        AddQuestRecord("ReasonToFast", "1");
        pchar.questTemp.ReasonToFast = "SpeakHorse";
        pchar.questTemp.ReasonToFast.GuardNation = npchar.nation;
        pchar.questTemp.ReasonToFast.cantSpeakOther = true;
        ReasonToFast_InitVariables();
        string TargetLocation = SelectQuestShoreLocation();
        if (TargetLocation != "")
        {
            Locations[FindLocation(TargetLocation)].DisableEncounters = true;
            pchar.quest.ReasonToFast_MeetPatrol.win_condition.l1 = "location";
            pchar.quest.ReasonToFast_MeetPatrol.win_condition.l1.location = TargetLocation;
            pchar.quest.ReasonToFast_MeetPatrol.function = "ReasonToFast_MeetPatrolShore";
            pchar.questTemp.ReasonToFast.PatrolLocation = TargetLocation;
        }
        NextDiag.CurrentNode = NextDiag.TempNode;
        DialogExit();
        break;
        // <-- генератор "Повод для спешки"

    case "exit_setOwner":
        LAi_SetOwnerTypeNoGroup(npchar);
        NextDiag.CurrentNode = NextDiag.TempNode;
        DialogExit();
        break;

    case "Exit":
        NextDiag.CurrentNode = NextDiag.TempNode;
        DialogExit();
        break;

    //поиски кольца мэра
    case "TakeMayorsRing_S1":
        if (CheckAttribute(pchar, "questTemp.different.TakeMayorsRing.item")) //если валяется в итемах
        {
            dialog.text = LinkRandPhrase("Нет, дорогой, не попадалось, к сожалению. Рада бы помочь, да не могу...",
                                         "Нет, " + GetSexPhrase("красавчик", "девушка") + ", кольца не видела...",
                                         "К сожалению, нет. Никакого кольца не видела.");
            link.l1 = "Жаль... Ну что же, спасибо тебе.";
            link.l1.go = "exit";
        }
        else
        {
            if (npchar.id == "HorseGen_" + reload_location_index + "_1")
            {
                dialog.text = "Уж не кольцо ли губернатора ты имеешь в виду?";
                link.l1 = "Именно, крошка!";
                link.l1.go = "TakeMayorsRing_S2";
            }
            else
            {
                dialog.text = LinkRandPhrase("Нет, дорогой, не попадалось, к сожалению. Рада бы помочь, да не могу...",
                                             "Нет, " + GetSexPhrase("красавчик", "девушка") + ", кольца не видела...",
                                             "К сожалению, нет. Никакого кольца не видела.");
                link.l1 = "Жаль... Ну что же, спасибо тебе.";
                link.l1.go = "exit";
            }
        }
        break;

    case "TakeMayorsRing_S2":
        dialog.text = "Извини, но кольцо мне подарено! Так что возвращать его я не обязана.";
        link.l1 = "Подарено?! Кем?";
        link.l1.go = "TakeMayorsRing_S3";
        break;

    case "TakeMayorsRing_S3":
        dialog.text = "Самим губернатором, конечно!";
        link.l1 = "Так он был слегка невеселе, мягко говоря. Он вообще ничего не помнит.";
        link.l1.go = "TakeMayorsRing_S4";
        break;

    case "TakeMayorsRing_S4":
        dialog.text = "Ну а я то здесь при чём? Если он был не в себе, то это его проблемы!";
        link.l1 = "Послушай, дорогуша, это же губернатор. Ну зачем тебе с ним ссориться? Кольцо ведь обручальное, сама понимаешь... Отдай, не делай себе проблем из-за такой мелочи.";
        link.l1.go = "TakeMayorsRing_S5";
        break;

    case "TakeMayorsRing_S5":
        if (rand(1) && sti(pchar.money) > 5000)
        {
            dialog.text = "Кольцо отдам, только ты заплатишь мне пять тысяч песо.";
            link.l1 = "Хорошо, забирай свои деньги и гони кольцо.";
            link.l1.go = "TakeMayorsRing_S6";
        }
        else
        {
            dialog.text = "Хм, ну ладно. Пусть забирает!..";
            link.l1 = "Всенепременно, дорогуша!";
            link.l1.go = "exit";
            GiveItem2Character(pchar, "MayorsRing");
            pchar.questTemp.different.TakeMayorsRing = "HorseTakenRing";
            AddQuestRecord("SeekMayorsRing", "3");
            AddQuestUserData("SeekMayorsRing", "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
            AddQuestUserData("SeekMayorsRing", "sName", GetFullName(npchar));
        }
        break;

    case "TakeMayorsRing_S6":
        dialog.text = "Пожалуйста...";
        link.l1 = "Ну, отлично. Спасибо за помощь, дорогуша.";
        link.l1.go = "exit";
        AddMoneyToCharacter(pchar, -5000);
        GiveItem2Character(pchar, "MayorsRing");
        pchar.questTemp.different.TakeMayorsRing = "HorseTakenRingMoney";
        AddQuestRecord("SeekMayorsRing", "2");
        AddQuestUserData("SeekMayorsRing", "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
        AddQuestUserData("SeekMayorsRing", "sName", GetFullName(npchar));
        break;

    //Jason --> Заносчивый аристократ
    case "Badboy":
        pchar.GenQuest.Badboy.Brothel.City = npchar.city; //город квестодателя
        //log_info(pchar.GenQuest.Badboy.Brothel.City); // patch-6
        pchar.GenQuest.Badboy.Brothel.nation = npchar.nation;
        pchar.GenQuest.Badboy.Brothel.Name = GenerateRandomName_Generator(sti(npchar.nation), "man");
        dialog.text = "Понимаете, нам очень сильно досаждает один клиент - " + pchar.GenQuest.Badboy.Brothel.Name + ". Он надирается в таверне до скотского состояния, потом приходит сюда, снимает девочку и дебоширит. Самое неприятное - что он благородного происхождения и какой-то дальний родственник нашему губернатору, так что его выходки здесь просто вынуждены терпеть. Не могли бы вы урезонить этого молодого нахала... так, чтобы он забыл дорогу в моё заведение?";
        link.l1 = "Родственник губернатора? Хм... пожалуй, не стоит портить отношения с властью. Ну, ты же понимаешь. Так что извини.";
        link.l1.go = "exit";
        link.l2 = "Это можно устроить. Где мне найти этого повесу?";
        link.l2.go = "Badboy_1";
        break;

    case "Badboy_1":
        dialog.text = "В такое время он обычно ошивается в таверне. Накачивается вином, а потом уже идет сюда.";
        link.l1 = "Понятно. Думаю, застану его там.";
        link.l1.go = "exit";
        //создаем дебошира
        int iRank, iType, b;
        string sBlade, sPistol;
        if (sti(pchar.rank) < 6)
            iType = 0;
        if (sti(pchar.rank) >= 6 && sti(pchar.rank) < 16)
            iType = 1;
        if (sti(pchar.rank) >= 16)
            iType = 2;
        switch (iType)
        {
        case 0:
            iRank = 6;
            sBlade = "blade_12";
            sPistol = "pistol1";
            b = 25;
            break;
        case 1:
            iRank = sti(pchar.rank) + 10;
            sBlade = "blade_09";
            sPistol = "pistol1";
            b = 65;
            break;
        case 2:
            iRank = sti(pchar.rank) + 5;
            sBlade = "blade_14";
            sPistol = "pistol1";
            b = 40;
            break;
        }
        sld = GetCharacter(NPC_GenerateCharacter("Badboy", "citiz_" + (7 + rand(1)), "man", "man", iRank, HOLLAND, -1, true, "citizen"));
        FantomMakeCoolFighter(sld, iRank, b, b, sBlade, sPistol, "bullet", makeint(iRank * 5));
        sld.name = pchar.GenQuest.Badboy.Brothel.Name;
        sld.lastname = "";
        sld.dialog.FileName = "Quest\Other_quests_NPC.c";
        sld.dialog.currentnode = "Badboy";
        sld.greeting = "noble_male"; // patch-6
        LAi_SetLoginTime(sld, 15, 22);
        LAi_SetSitType(sld);
        FreeSitLocator(pchar.GenQuest.Badboy.Brothel.City + "_tavern", "sit1");
        ChangeCharacterAddressGroup(sld, pchar.GenQuest.Badboy.Brothel.City + "_tavern", "sit", "sit1");
        pchar.GenQuest.Badboy.Brothel.Type = iType; //запомним тип
        pchar.GenQuest.Badboy.Brothel = "true";
        break;

    case "Badboy_complete":
        dialog.text = "Ах, вы настоящий мужчина. Я знала, что могу на вас положиться.";
        link.l1 = "Всегда готов помочь такой прекрасной даме и её... подопечным.";
        link.l1.go = "Badboy_complete_1";
        break;

    case "Badboy_complete_1":
        dialog.text = "Вы не только храбры, но ещё и очень галантны. Я бы хотела отблагодарить вас по-особенному. Так, как может сделать только женщина. И так, что вы не забудете этого никогда. Поднимайтесь в комнату, отважный моряк...";
        link.l1 = "...";
        link.l1.go = "Badboy_complete_2";
        break;

    case "Badboy_complete_2":
        pchar.questTemp.different.HostessSex.city = pchar.GenQuest.Badboy.Brothel.City;
        AddDialogExitQuestFunction("SexWithHostess_goToRoom");
        SetTimerFunction("SexWithHostess_null", 0, 0, 1);
        DialogExit();
        if (sti(pchar.GenQuest.Badboy.Brothel.Type) != 2)
        {
            DeleteAttribute(pchar, "GenQuest.Badboy");
        }
        else
        {
            pchar.quest.Badboy_Brothel.win_condition.l1 = "location";
            pchar.quest.Badboy_Brothel.win_condition.l1.location = pchar.GenQuest.Badboy.Brothel.City + "_town";
            pchar.quest.Badboy_Brothel.function = "Badboy_friends";
            DeleteAttribute(pchar, "GenQuest.Badboy.Continue"); // patch-6
        }
        SaveCurrentQuestDateParam("questTemp.Badboy");
        break;
    // <-- Заносчивый аристократ

    //Португалец
    case "Portugal":
        dialog.text = "Есть один человек, он задолжал мне, но я, право, не знаю, как вам сказать...";
        link.l1 = "Не нужно слов! Я найду его и вытряхну всё до последнего песо, за один лишь взгляд ваших бездонных глаз! Назовите его имя и только!";
        link.l1.go = "Portugal_1";
        break;

    case "Portugal_1":
        dialog.text = "Нет-нет, вы меня неправильно поняли, капитан! Этот человек... не делайте ему ничего дурного. Просто напомните ему о долге. Его зовут Хьюго Авендел, и, я полагаю, вы найдете его там, где подают самую дешевую выпивку. Только Бога ради, не применяйте к нему силу!\nПросто скажите... напомните, что он обещал заплатить. Я не хочу обращаться к страже, но у меня есть знакомые офицеры, так что передайте ему – я жду, и при всём моём к нему отношении, не позднее завтрашнего дня, я вынуждена буду принять меры. Просто напомните ему о его обещании.";
        link.l1 = "Ваше слово – закон для меня, мадам. Я с удовольствием выполню вашу просьбу.";
        link.l1.go = "Portugal_2";
        break;

    case "Portugal_2":
        DialogExit();
        //создаем Хьюго
        sld = GetCharacter(NPC_GenerateCharacter("Avendel", "Hugh", "man", "man", 10, HOLLAND, -1, true, "quest"));
        FantomMakeCoolFighter(sld, 20, 50, 50, "blade_04", "pistol1", "bullet", 50);
        sld.name = "Хьюго";
        sld.lastname = "Авендел";
        sld.dialog.FileName = "Quest\Portugal_dialog.c";
        sld.dialog.currentnode = "Avendel_tavern";
        sld.greeting = "avendel_1";
        sld.rank = 12;
        LAi_SetHP(sld, 80, 80);
        SetSelfSkill(sld, 10, 12, 10, 10, 70);
        SetShipSkill(sld, 50, 75, 15, 15, 25, 55, 10, 15, 30);
        SetSPECIAL(sld, 3, 8, 3, 10, 10, 3, 6);
        SetCharacterPerk(sld, "BasicCommerce");
        SetCharacterPerk(sld, "AdvancedCommerce");
        SetCharacterPerk(sld, "BasicBattleState");
        SetCharacterPerk(sld, "AdvancedBattleState");
        SetCharacterPerk(sld, "BasicDefense");
        SetCharacterPerk(sld, "Gunman");
        GiveItem2Character(sld, "blade_12");
        sld.equip.blade = "blade_12";
        GiveItem2Character(sld, "pistol1");
        EquipCharacterbyItem(sld, "pistol1");
        TakeNItems(sld, "bullet", 10);
        AddItems(sld, "gunpowder", 10);
        LAi_SetCharacterUseBullet(sld, "bullet");
        LAi_group_MoveCharacter(sld, "HOLLAND_CITIZENS");
        LAi_SetImmortal(sld, true);
        LAi_SetSitType(sld);
        FreeSitLocator("Marigo_tavern", "sit_front1");
        ChangeCharacterAddressGroup(sld, "Marigo_tavern", "sit", "sit_front1");
        SetFunctionTimerCondition("Portugal_BeginOver", 0, 0, 2, false);
        pchar.questTemp.Portugal = "begin";
        break;

    case "Portugal_exit":
        dialog.text = "Спасибо вам, капитан. Надеюсь, что он проявит должное благоразумие.";
        link.l1 = "Я уверен в этом, мадам. На этом позвольте откланяться.";
        link.l1.go = "exit";
        sld = characterFromId("Avendel");
        sld.lifeday = 0;
        pchar.questTemp.Portugal = "end";
        break;

    case "Portugal_3":
        AddMoneyToCharacter(pchar, -10000);
        dialog.text = "О, нет! Скажите, вы ничего с ним не... у него же нет денег, я точно знала! Мы просто выросли в одном городке, я бы никогда не пошла к страже! Просто хотела его припугнуть, расшевелить, пока он окончательно не утонул в своей кружке!";
        link.l1 = "Кхм, и тем не менее – вот ваши деньги. А за Хьюго не беспокойтесь – он в полном порядке… будет, если протрезвеет.";
        link.l1.go = "Portugal_4";
        break;

    case "Portugal_4":
        dialog.text = "Ох, капитан, вы не понимаете! Он ведь был одним из... ну, знаете, их называют охотники за головами – наёмники, выслеживающие пиратов и разбойников. Только, он был не самым удачливым, чтобы не сказать иначе\nНе так давно, он окончательно разорился – потерял команду и корабль, и, с тех пор, плавает по дну своей кружки день за днём. Я, по старой памяти, разрешаю ему иногда приходить сюда. Он так... так жалок теперь. А когда-то был первым красавцем в нашем городишке на побережье Ла-Манша\nЯ знаю, он пообещал вам что-нибудь, и вы заплатили из своего кармана! Я отдам вам эти деньги, только не делайте ему ничего плохого, умоляю, капитан!";
        link.l1 = "Хорошо-хорошо, я понял вас, мадам. Не нужно возвращать деньги – они ваши, и я не сделаю ничего вашему другу. А сейчас, разрешите откланяться – меня ждут дела. Рад был помочь столь прекрасной даме.";
        link.l1.go = "Portugal_5";
        break;

    case "Portugal_5":
        DialogExit();
        sld = characterFromId("Avendel");
        sld.dialog.currentnode = "Avendel_tavern_7";
        pchar.questTemp.Portugal = "AvendelTavern";
        break;

    // Addon 2016-1 Jason пиратская линейка
    case "mtraxx":
        dialog.text = "Тише ты, не ори так... Иди к маман Лолите, и купи со мной свидание. В комнате наверху, где нет лишних ушей, и побеседуем. А до тех пор - ни слова больше!.. Ой, морячок, ты бы сходил к хозяйке сначала, прежде чем меня ручищами своими лапать, хи-хи-хи...";
        link.l1 = "Уже иду, милашка...";
        link.l1.go = "mtraxx_1";
        break;

    case "mtraxx_1":
        DialogExit();
        pchar.questTemp.Mtraxx = "jewelry_2";
        break;

    case "mtraxx_2":
        pchar.quest.Mtraxx_JewelrySDMOver.over = "yes"; //снять таймер
        dialog.text = "Нет, не мне. Если ты не будешь меня перебивать, я всё расскажу по порядку.";
        link.l1 = "Я весь внимание!";
        link.l1.go = "mtraxx_3";
        break;

    case "mtraxx_3":
        dialog.text = "Очень хорошо. Неделю назад в Санто-Доминго прибыл военный корабль. Он был потрёпан то ли в шторме, то ли в бою, потому что сразу стал на ремонт, команда расквартировалась в форте, а капитан буквально прописался в нашем заведении. Два дня подряд он кутил и уединялся с одной нашей девахой. Вот ей-то он и подарил камешек, и не один. Она сама всем похвасталась - Лолита разрешает оставлять себе подарки клиентов\nТа дурёха даже и не знала истинную ценность подарка, а вот я сразу сообразила, что это за штука. А после рассказа малышки о том, как капитан, будучи в стельку пьяным, хвастался, что нашел целые залежи голубого янтаря и теперь обеспечен если не на всю жизнь, то надолго, я сразу послала весточку Тираксу...";
        link.l1 = "";
        link.l1.go = "mtraxx_4";
        break;

    case "mtraxx_4":
        dialog.text = "А к следующему приходу капитана мне удалось подстроить так, что его пассия была занята клиентом, и надолго, и я сама обслужила этого вояку. Попутно попыталась вызнать хоть какие-нибудь подробности, но без особого результата. Ничего, кроме бахвальства, что он скоро будет богат как Крёз и вернётся в Старый Свет, я не услышала\nНи места, где он нашёл голубой янтарь, ни даже прозрачного намёка на это - молчок. Единственная польза от этого разговора в том, что я узнала, что его судно отремонтировано, он отправляется в Гавану и там будет стараться сделать так, чтобы его по службе отправили в плавание в нужном ему направлении - корабль-то не его, а казённый.";
        link.l1 = "Значит, он сейчас в Гаване?";
        link.l1.go = "mtraxx_5";
        break;

    case "mtraxx_5":
        dialog.text = "Он отчалил позавчера на рассвете, так что сам считай, добрался он туда или нет - ты же среди нас двоих моряк.";
        link.l1 = "Имя капитана, название и тип судна сможешь сказать?";
        link.l1.go = "mtraxx_6";
        break;

    case "mtraxx_6":
        dialog.text = "Ты меня за девочку держишь? Конечно. Эсберто Кабаньяс его зовут, а корабль - 'Кантавро'. А тип - вроде шхуной его моряки называли.";
        link.l1 = "Это всё, что ты знаешь?";
        link.l1.go = "mtraxx_7";
        break;

    case "mtraxx_7":
        dialog.text = "Тебе мало? Если поторопишься, то наверняка успеешь его нагнать в Гаване. И не тяни: не думаю, что ему потребуется много времени, чтобы отправиться с Кубы к своей россыпи, а тогда - ищи-свищи. Впрочем, на два часа можешь задержаться - деньги-то уплачены.";
        link.l1 = "Согласен, малышка, два часа в этой ситуации роли не сыграют...";
        link.l1.go = "exit";
        sTotalTemp = npchar.id;
        pchar.GenQuest.BrothelCount = sti(pchar.GenQuest.BrothelCount) + 1; // для Данек
        Achievment_SetStat(pchar, 23, 1);
        //<-- кол-во посещений
        str = npchar.city;
        pchar.quest.(str).win_condition.l1 = "ExitFromLocation";
        pchar.quest.(str).win_condition.l1.location = pchar.location;
        pchar.quest.(str).win_condition = "Brothel_checkVisitTime";
        pchar.questTemp.HorseQty = sti(pchar.questTemp.HorseQty) + 1; //счетчик
        AddDialogExitQuest("PlaySex_1");
        // кач от борделя
        if (CheckNPCQuestDate(pchar, "BrothelSex"))
        {
            if (IsEquipCharacterByArtefact(pchar, "totem_03"))
                AddCharacterHealth(pchar, 10);
            else
                AddCharacterHealth(pchar, 5);
            SetNPCQuestDate(pchar, "BrothelSex");
        }
        // изменение статусов
        ChangeCharacterComplexReputation(pchar, "nobility", -1);
        AddCharacterExpToSkill(pchar, "Leadership", 30);
        AddCharacterExpToSkill(pchar, "FencingS", -15);
        AddCharacterExpToSkill(pchar, "Pistol", -15);
        break;

    case "mtraxx_R":
        dialog.text = "По заданию? У-у... Как огорчительно. А я-то думала - ты отдыхать сюда приехал. Мои девочки скучают по бравым корсарам. Ну, говори, что там за дело?..";
        link.l1 = "Маркус поручил мне два дня кутить в твоём заведении на всю катушку, выпить как можно больше отличного вина и обласкать всех твоих малышек. Когда будем приступать?";
        link.l1.go = "mtraxx_R1";
        break;

    case "mtraxx_R1":
        dialog.text = "Ах, Чарли Принц, твой юмор так же остер, как и твоя шпага! Я уже было расстроилась... Девочки! У нас гость, да какой! Откупоривайте вина и несите закуску!";
        if (sti(pchar.money) >= 31000)
        {
            link.l1 = "Зови всех своих крошек - будем отдыхать и веселиться! Йо-хо-хо!..";
            link.l1.go = "mtraxx_R2";
        }
        else
        {
            link.l1 = "Подожди пару минут, Жанетта - я сбегаю на свой корабль за деньгами для тебя и твоих крошек. Скоро буду!";
            link.l1.go = "exit";
            pchar.questTemp.Mtraxx.Retribution = "brothel_repeat";
            chrDisableReloadToLocation = false;
        }
        break;

    case "mtraxx_R2":
        AddMoneyToCharacter(pchar, -30000);
        dialog.text = "Если бы все клиенты были такими милыми, обаятельными и щедрыми, как ты... Всё будет на высоте. Де-евочки-и!..";
        link.l1 = "...";
        link.l1.go = "exit";
        AddDialogExitQuestFunction("Mtraxx_RetributionInBrothel");
        break;
    }
}

ref GetFreeHorseRef(string City)
{
    ref rCharacter;
    int storeArray[8];
    int howStore = 0;
    for (int n = 0; n < MAX_CHARACTERS; n++)
    {
        makeref(rCharacter, Characters[n]);
        if (rCharacter.location == City + "_Brothel" && CheckAttribute(rCharacter, "CityType") && rCharacter.CityType == "horse")
        {
            storeArray[howStore] = n;
            howStore++;
        }
    }
    if (howStore == 0)
        return &NullCharacter;
    return &characters[storeArray[rand(howStore - 1)]];
}

ref CheckHorsesName(string City, int num)
{
    ref rCharacter;
    string sTemp, sSeeked;
    sSeeked = GetStrSmallRegister(dialogEditStrings[num]);
    for (int n = 0; n < MAX_CHARACTERS; n++)
    {
        makeref(rCharacter, Characters[n]);
        if (rCharacter.location == City + "_Brothel" && CheckAttribute(rCharacter, "CityType") && rCharacter.CityType == "horse")
        {
            sTemp = GetStrSmallRegister(rCharacter.lastname + " " + rCharacter.name);
            if (findsubstr(sSeeked, sTemp, 0) != -1)
                return rCharacter;
            sTemp = GetStrSmallRegister(rCharacter.lastname);
            if (findsubstr(sSeeked, sTemp, 0) != -1)
                return rCharacter;
            sTemp = GetStrSmallRegister(rCharacter.name);
            if (findsubstr(sSeeked, sTemp, 0) != -1)
                return rCharacter;
        }
    }
    return &NullCharacter;
}