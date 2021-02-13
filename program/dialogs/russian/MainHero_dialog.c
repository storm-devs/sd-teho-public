void ProcessDialogEvent()
{
    ref NPChar;
    aref Link, NextDiag;

    DeleteAttribute(&Dialog, "Links");

    makeref(NPChar, CharacterRef);
    makearef(Link, Dialog.Links);
    makearef(NextDiag, NPChar.Dialog);

    ref chr, sld, rShip, rItm, rItem;
    float fTemp;
    bool bOk;
    int i, iTemp;
    string sAttr, sGun, sBullet, attrL;
    aref rType;

    // генератор ИДХ по кейсу -->
    sAttr = Dialog.CurrentNode;
    if (findsubstr(sAttr, "CabinCompanionTalk_", 0) != -1)
    {
        i = findsubstr(sAttr, "_", 0);
        PChar.GenQuest.CabinCompanionNum = strcut(sAttr, i + 1, strlen(sAttr) - 1); // индекс в конце
        Dialog.CurrentNode = "Cabin_Companion_Talk";
    }

    if (findsubstr(sAttr, "SetGunBullets1_", 0) != -1)
    {
        i = findsubstr(sAttr, "_", 0);
        PChar.GenQuest.SetGunBullets = strcut(sAttr, i + 1, strlen(sAttr) - 1); // индекс в конце
        Dialog.CurrentNode = "SetGunBullets2";
    }
    // генератор ИДХ по кейсу <--

    switch (Dialog.CurrentNode)
    {
    case "Exit":
        NextDiag.CurrentNode = NextDiag.TempNode;
        DialogExit_Self();
        break;

    case "First time":
        NextDiag.TempNode = "First time";

        Dialog.Text = "Если вы читаете эти строки, значит, где-то явный баг в коде";
        Link.l1 = "Выход";
        Link.l1.go = "exit";
        //--> Голландский гамбит
        if (CheckAttribute(pchar, "questTemp.HWIC_FindIsland"))
        {
            dialog.text = "Итак, вот мы и нашли это место на карте. Отмечу его. Можно отправляться на поиски.";
            link.l1 = "...";
            link.l1.go = "exit";
            AddDialogExitQuestFunction("SearchingForIslandOnMap");
        }
        if (CheckAttribute(pchar, "questTemp.HWICMC") && pchar.questTemp.HWICMC == "Fleetwood")
        {
            dialog.text = "Так-так, вот мы и на месте. Надо спрятать корабль в заливе Южном, а сюда прийти пешком через джунгли и организовать Флитвуду сюрприз.";
            link.l1 = "...";
            link.l1.go = "exit";
            pchar.quest.Fleetwood_repeatShore.win_condition.l1 = "ExitFromLocation";
            pchar.quest.Fleetwood_repeatShore.win_condition.l1.location = pchar.location;
            pchar.quest.Fleetwood_repeatShore.function = "Fleetwood_repeatShore";
        }
        //<-- Голландский гамбит

        //--> Ложный след
        if (CheckAttribute(pchar, "questTemp.FalseTrace") && pchar.questTemp.FalseTrace == "TalkCabinWoman" && PChar.location == Get_My_Cabin())
        {
            dialog.text = "Хм... Верить этому проходимцу - дело неблагодарное, хотя его история похожа на правду. Быть может, на этот раз он не врет. Но, пожалуй, побеседую-ка я с его женушкой... Боцман! Привести мне захваченную в плен женщину!";
            link.l1 = "Есть, капитан!";
            Link.l1.go = "exit";
            chr = characterFromId("FalseTraceWife");
            chr.dialog.currentnode = "FalseTrace_wife_6";
            pchar.questTemp.FalseTrace.CharID = "FalseTraceWife";
            AddDialogExitQuest("SetFalseTraceCharToCabin");
        }
        //<-- Ложный след

        //--> Португалец
        if (CheckAttribute(pchar, "questTemp.Portugal") && pchar.questTemp.Portugal == "DigGems")
        {
            dialog.text = "Кажется, вот это место. Это единственное высохшее дерево в округе. Пожалуй, копать надо именно здесь.";
            link.l1 = "(выкопать клад)";
            link.l1.go = "exit";
            AddDialogExitQuest("FindPortugalGems");
        }
        //<-- Португалец
        // Сага
        if (CheckAttribute(pchar, "questTemp.Saga.JessSoul"))
        {
            dialog.text = "Что это? Где я?! Что за странное место?";
            link.l1 = "...";
            link.l1.go = "exit";
            AddDialogExitQuest("Saga_JessikaSoul_2");
        }
        //--> приколы со стуком в дверь Диффиндура, LSC
        if (CheckAttribute(pchar, "questTemp.LSC.DiffIndoor"))
        {
            dialog.text = "Вот дверь, ведущая во внутренние помещения корабля. Закрыто... Хоук должен быть там. Как там говорил Оле? Надо постучать условным стуком.";
            link.l1 = "Постучать два раза.";
            link.l1.go = "knock_2";
            link.l2 = "Постучать три раза.";
            link.l2.go = "knock_3";
            link.l3 = "Постучать один раз, пауза, три раза.";
            link.l3.go = "knock_1_3";
            link.l4 = "Постучать два раза, пауза, два раза.";
            link.l4.go = "knock_2_2";
            link.l5 = "Постучать три раза, пауза, один раз.";
            link.l5.go = "knock_3_1";
        }
        //<-- приколы со стуком в дверь Диффиндура, LSC

        //--> напялили водолазный скафандр, для перехода в режим шага
        if (pchar.model == "protocusto")
        {
            dialog.text = "Уф! Ну и тяжелая же эта штуковина!";
            link.l1 = "";
            link.l1.go = "exit";
        }
        //<-- водолазный скафандр
        // отказ от телепортации
        if (IsCharacterInLocator(pchar, "item", "dolly1") || IsCharacterInLocator(pchar, "item", "dolly2") || IsCharacterInLocator(pchar, "item", "dolly3"))
        {
            dialog.text = "Нет-нет-нет! Даже и не подумаю! Трех раз хватило вдоволь!..";
            link.l1 = "...";
            link.l1.go = "exit";
        }
        if (CheckAttribute(pchar, "questTemp.Terrapin") && pchar.questTemp.Terrapin == "roof")
        {
            dialog.text = "Дело сделано - Левассер мертв. Это оказалось проще, чем я думал... Но что-то ту не так. Ведь Тибо даже не разговаривал с Мартэном! Это значит, что либо Робер предал меня, либо сыграл слепой случай\nНо куда же мог убежать этот гад Тибо? Наверняка, он уже мчится к Кэтрин. Надо что-то делать, если я хочу вырвать девушку из его лап...";
            link.l1 = "";
            link.l1.go = "terrapin";
        }
        if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "think")
        {
            dialog.text = "Сокровища, сокровища... индейский город... Я не верю в чудесные совпадения, черт возьми... Бьюсь об заклад, что к исчезновению фрегата этого Мигеля Дичозо приложил руку мой драгоценный братец. Думаю, он также позаботился о том, чтобы закрыть рот Дичозо\nА быть может, он был с ним в сговоре - не просто так же испанцы предположили, что Дичозо скрывается в Сен-Пьере. Тут неясно. Но я уверен, что индейское золото, которое Мишель 'вез де Пуанси', и золото Мигеля Дичозо - одно и то же. Рассказ этого пленного кастильца вполне стыкуется с показаниями офицера об 'операциях' братишки и де Пуанси\nОднако получается, что Мишель вез-вез, да не довез, и Дичозо вез-вез, да не довез... забавно! И где же тогда пресловутые сокровища? Не за ними ли так спешно отправился братец, а? Думаю, что именно за ними\nСледовательно, если мне найти это золото, то я убью двух зайцев: и братцу дорогому взгляну в бесстыжие глаза, и... да-да, золото еще никому не помешало. Но с какого же конца распутывать этот клубок? Видимо, придется близко знакомиться с испанцами\nДон Рамон Мендоса отпадает - с ним я навряд ли договорюсь, а вот святой отец Винсенто, инквизитор, заклятый друг барона... вот этот подойдет. Братья Ордена Иисуса не отличаются щепетильностью, зато любят деньги и не брезгуют грязными методами\nДичозо, Дичозо... где-то я уже слышал это имя... или нет? Ладно, черт с ним. Пойду к офицеру, забирать своего испанца, и отправляюсь в Сантьяго.";
            link.l1 = "";
            link.l1.go = "exit";
        }
        if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "shore")
        {
            dialog.text = "Ваниль перегружена на каракку, ее паруса давно скрылись за горизонтом, а этот чертов галеон, вместо того, чтобы выходить в открытое море, взял и вернулся в порт, будь он неладен. В порту на корабле показываться мне нежелательно: пусть думают, что я ушел с Гваделупы... Отправлюсь-ка я пешком в город через джунгли и разведаю, что делает мой дорогой Марше...";
            link.l1 = "";
            link.l1.go = "exit";
        }
        if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "galeon")
        {
            dialog.text = "Охраны на верхней палубе немного, и все они, как один - сонные и клюют носом. Думаю, я смогу вырубить их всех по одному, если тихонько зайду со спины и тресну кастетом по затылку...";
            link.l1 = "";
            link.l1.go = "exit";
        }
        if (CheckAttribute(pchar, "questTemp.Guardoftruth_room"))
        {
            dialog.text = "Незапертый пустой дом с уютной комнаткой на втором этаже, и прямо по соседству с апартаментами Колхауна... просто подарок судьбы. Если вылезти в окно и пройти по козырьку крыши, то я без труда заберусь в комнату Арчи. И делать это надо ночью, чтобы никто не заметил...";
            link.l1 = "";
            link.l1.go = "exit";
            AddDialogExitQuest("GuardOT_FindWayToRoom");
        }
        // Поиски Ксочитэма
        if (CheckAttribute(pchar, "questTemp.Ksochitam_Dolly") && pchar.questTemp.Ksochitam_Dolly == "half_pearl")
        {
            dialog.text = "Так-так! Вот я и нашел место, указанное 'проявлением': это индейский истукан! Рядом с ним стрелка компаса Стрела Пути перестает метаться и указывает строго одно и то же направление, как ни крутись. Логично - индейская магия - индейский истукан. Теперь надо отметить направление, куда указывает Стрела Пути, на карте, а затем отправляться на Доминику.";
            link.l1 = "";
            link.l1.go = "exit";
            AddDialogExitQuest("Ksochitam_FindFirstWay");
        }
        if (CheckAttribute(pchar, "questTemp.Ksochitam_Dolly") && pchar.questTemp.Ksochitam_Dolly == "half_dominica")
        {
            dialog.text = "Так-так! Вот я и нашел место, указанное 'проявлением': это индейский истукан! Рядом с ним стрелка компаса Стрела Пути перестает метаться и указывает строго в одну и ту же сторону, как ни крутись. Логично - индейская магия - индейский истукан. Теперь надо отметить направление, куда указывает Стрела Пути, на карте, а затем отправляться на Мэйн.";
            link.l1 = "";
            link.l1.go = "exit";
            AddDialogExitQuest("Ksochitam_FindSecondWay");
        }
        if (CheckAttribute(pchar, "questTemp.Ksochitam_Dolly") && pchar.questTemp.Ksochitam_Dolly == "full")
        {
            dialog.text = "Оба проявления найдены! Теперь нужно отметить второе направление на карте. Пересечение двух направлений и укажет мне местонахождение острова Ксочитэм.";
            link.l1 = "";
            link.l1.go = "exit";
            AddDialogExitQuest("Ksochitam_FindFullWay");
        }
        // рассуждения по Тайясалю
        if (CheckAttribute(pchar, "questTemp.Tieyasal_CabinTalk"))
        {
            if (pchar.questTemp.Tieyasal_CabinTalk == "calendar")
            {
                dialog.text = "Алонсо де Мальдонадо сказал, что есть какой-то путь в Тайясаль с севера полуострова Юкатан. Значит, стоит поискать проход в глубь сельвы в тамошних тропах. Однако у меня не идут из головы слова Джино о том, что телепортационные статуи изначально предназначались для захвата и переноса случайных людей в Тайясаль\nДа и шаман мискито Змеиный Глаз говорил, что истуканы по логике должны отправлять 'пожранных' в одно место. Но почему же тогда порталы так странно работают? Хм. Кроме того, на карте Двух Появлений около первого проявления, обозначающего истукан в джунглях мискито, есть какое-то обозначение в виде круга\nЧто бы это могло значить? Еще одно магическое место? Или какие-то дополнительные свойства истукана? Пожалуй, надо отправиться к мискито и побеседовать об этой статуе. Либо не морочить себе голову и пойти на поиски тропы, ведущей к Тайясалю. Вероятно, она берет свой путь в одной из бухт на северо-западном Мэйне.";
                link.l1 = "";
                link.l1.go = "exit";
            }
            else
            {
                dialog.text = "Алонсо де Мальдонадо сказал, что есть какой-то путь в Тайясаль с севера полуострова Юкатан. Значит, стоит поискать проход в глубь сельвы в тамошних тропах. Вероятно, нужная мне тропа берет свой путь в одной из бухт на северо-западном Мэйне.";
                link.l1 = "";
                link.l1.go = "exit";
            }
            AddDialogExitQuest("Tieyasal_AfterCabinTalk");
        }
        // решаем - титры или фриплей 010912
        if (CheckAttribute(pchar, "questTemp.Tieyasal_final"))
        {
            dialog.text = "Вот и конец длинного пути. И разве мог я себе представить, что освобождая своего брата, я тем самым готовился к смертельной схватке с ним? Что я поставил под угрозу весь мир? Слава Богу, все позади\nБолее ничто меня не держит на Карибах. Пришло время возвращаться домой, во Францию. Но... вот только хочу ли я этого?";
            link.l1 = "Да, я возвращаюсь в Европу.";
            link.l1.go = "final_1";
            link.l2 = "Нет, я остаюсь здесь, на Карибах.";
            link.l2.go = "final_2";
        }
        // фэйловый финал 040912
        if (CheckAttribute(pchar, "questTemp.Europe"))
        {
            PlaySound("VOICE\Russian\military02.wav");
            dialog.text = "Вы слышали, что сказал полковник? Здесь прячутся мятежники! Обыскать весь дом, перевернуть всё и схватить всех, кто там находится! Вперед!!";
            link.l1 = "...";
            link.l1.go = "exit";
            AddDialogExitQuest("Europe_SharlieFinal_2");
        }
        // Addon-2016 Jason, французские миниквесты (ФМК) Гваделупа
        if (CheckAttribute(pchar, "questTemp.FMQG.Info") && pchar.location == "Bridgetown_Plantation")
        {
            dialog.text = "Вот самое лучшее место для засады. Здесь буду стоять и поджидать Пинетта.";
            link.l1 = "...";
            link.l1.go = "exit";
            AddDialogExitQuest("FMQG_KidnappingInfo");
        }
        // Addon-2016 Jason, французские миниквесты (ФМК) Сент-Кристофер
        if (CheckAttribute(pchar, "questTemp.FMQN.Choose") && pchar.location == "shore40")
        {
            dialog.text = "Хм. Вся эта история дурно пахнет. Сдается мне, что никакого люггера из Сент-Джонса здесь и не предвиделось. Этот лейтенант втягивает меня в свою военную авантюру. Но мне-то она зачем? Я не воюю с голландцами... Что же мне делать? Уйти отсюда от греха подальше и кинуть ко всем чертям англичан, или остаться?";
            link.l1 = "Убраться восвояси.";
            link.l1.go = "FMQN_1";
            link.l2 = "Остаться.";
            link.l2.go = "FMQN_2";
        }
        // Addon 2016-1 Jason пиратская линейка
        if (CheckAttribute(pchar, "questTemp.Mtraxx.Chest") && pchar.location == "shore37")
        {
            dialog.text = "Итак, сундук подготовлен. Буду складывать в него оружие для людей Жана Пикара. Сабли и топоры в нужном количестве возьмем из арсенала на корабле, а пистоли и мушкеты придется собирать вручную по возможности: пистолей - 30, мушкетов - 2. К каждому пистолю нужен хотя бы 1 заряд, а к мушкету - 20, иначе от них не будет толка. Лечебных зелий желательно побольше, но свыше 3 штук на человека не имеет смысла. Приступаю к сбору!";
            link.l1 = "*для принятия решения об окончании сбора амуниции используйте 'Мысли вслух'*";
            link.l1.go = "exit";
            AddDialogExitQuest("Mtraxx_PlantChestReadyExit");
        }
        if (CheckAttribute(pchar, "questTemp.Mtraxx.Boats") && pchar.location == "Maracaibo_river")
        {
            dialog.text = "Итак, нужно построить шесть лодок. Для этого моим людям потребуется 20 связок распиленных досок и 10 тюков кожи. Инстументы возьмем на корабле. Руководить работами должен человек, разбирающийся в плотницком деле и починке кораблей.";
            link.l1 = "*для отдачи приказа о постройке лодок используйте 'Мысли вслух'*";
            link.l1.go = "exit";
            DeleteAttribute(pchar, "questTemp.Mtraxx.Boats");
            AddQuestRecord("Roger_5", "11");
        }
        if (CheckAttribute(pchar, "questTemp.Mtraxx.Retribution.Powder") && pchar.location == "shore10")
        {
            dialog.text = "Итак, я просто-напросто взорву этот завал из старых деревьев. Для этого мне потребуется 300 картузов пороха, чтобы наверняка, а также надо не забыть взять с собой огниво - поджечь фитиль.";
            link.l1 = "*для отдачи приказа о доставке пороха к завалу используйте 'Мысли вслух'*";
            link.l1.go = "exit";
            DeleteAttribute(pchar, "questTemp.Mtraxx.Retribution.Powder");
            pchar.questTemp.Mtraxx.Retribution = "powder";
            chrDisableReloadToLocation = false;
        }
        if (CheckAttribute(pchar, "questTemp.Mtraxx.Retribution.ExitClosed") && pchar.location == "Judgement_dungeon_01")
        {
            dialog.text = RandSwear() + "Выход заперт!! Дверь не поддается - словно ее подперли снаружи чем-то тяжелым!.. " + RandSwear() + "\nЧ-ш-ш... Что это?..";
            link.l1 = "";
            link.l1.go = "mtraxx_dungeon";
            DeleteAttribute(pchar, "questTemp.Mtraxx.Retribution.ExitClosed");
        }
        if (CheckAttribute(pchar, "questTemp.Mtraxx.Retribution.Bead") && pchar.location == "Judgement_church")
        {
            dialog.text = "Ну вот и все... Тупик. Дальше идти некуда\nПохоже, дон Энрико был прав: из этих подземелий не выбраться. Появилась было надежда, когда я отпер дверь из зала с 'сокровищами', когда нашел вторую дверь в подземелье с водой, но теперь... Я уже потерял счет времени - сколько я уже хожу по этим темным проходам? Полдня, день? Как же тут тихо и жутко, словно в гробу\nА вот здесь, видимо, когда-то была церковь. Самое подходящее место для того, чтобы помолиться. Грехов у меня много, слишком много... Помолюсь, а затем лягу спать: я ужасно устал, еле держусь на ногах, и рана на спине разболелась. Может, повезет, и не проснусь больше...";
            link.l1 = "";
            link.l1.go = "exit";
            DeleteAttribute(pchar, "questTemp.Mtraxx.Retribution.Bead");
            AddDialogExitQuestFunction("Mtraxx_RetributionBead");
        }
        break;

    // boal -->
    case "TalkSelf_Main":
        NextDiag.TempNode = "First time";
        //navy --> after duel in tavern
        if (CheckAttribute(pchar, "questTemp.LocationClone"))
        {
            Dialog.Text = RandPhraseSimple("Жаркая была схватка... Теперь можно позвать разбежавшихся трусов.", "Ха! Это было просто. А эти сухопутные крысы разбежались!");
            link.l1 = "...";
            link.l1.go = "exit";
            DeleteAttribute(pchar, "questTemp.LocationClone");
            break;
        }
        //navy <--
        Dialog.Text = RandPhraseSimple("Хм... Что бы мне сейчас хотелось сделать?", "Чем бы заняться?");
        if (!bDisableMapEnter && pchar.location == Get_My_Cabin())
        {
            //navy --> 13.02.08
            if (!bDisableMapEnter && GetCompanionQuantity(PChar) > 1)
            {
                link.l3 = "Вызвать компаньона.";
                link.l3.go = "Cabin_CompanionSelect";
            }
            //navy <--
        }
        else
        { //исп.линейка, квест №6, возможность переночевать в оплаченной комнате
            if (CheckAttribute(pchar, "questTemp.State.Open") && pchar.location == "Tortuga_tavern_upstairs")
            {
                if (makeint(environment.time) >= 22.0 || makeint(environment.time) < 10.0)
                {
                    link.l1 = "Отдыхать до утра.";
                    link.l1.go = "TalkSelf_room_day";
                }
                else
                {
                    link.l1 = "Отдыхать до ночи.";
                    link.l1.go = "TalkSelf_room_night";
                    link.l2 = "Отдыхать до следующего утра.";
                    link.l2.go = "TalkSelf_room_day";
                }
            }
        }
        if (!bDisableMapEnter) //боя в море нет
        {
            if (GetCargoGoods(pchar, GOOD_SLAVES) > 0)
            {
                Link.l5 = "Зачислить рабов в команду";
                Link.l5.go = "TalkSelf_SlavesToCrew";
            }
        }
        // захват города
        if (GetCharIDXForTownAttack(pchar.location) != -1 && !CheckAttribute(Pchar, "GenQuestFort.StartAttack") && !CheckAttribute(Pchar, "questTemp.Sharlie.DefendSP"))
        {
            Link.l6 = "Начать захват ближайшего города.";
            Link.l6.go = "TalkSelf_TownAttack";
        }

        bool bSeaBattle = (bDisableMapEnter) && (bSeaActive) && (!CheckAttribute(pchar, "GenQuest.MapClosedNoBattle"));
        if (!bSeaBattle && PChar.location != "Deck_Near_Ship" && findsubstr(PChar.location, "_shipyard", 0) == -1 && PChar.location != "CommonPackhouse_2" && !CheckAttribute(pchar, "GenQuest.CannotWait"))
        {
            Link.l7 = "Мне не мешало бы отдохнуть...";
            Link.l7.go = "TalkSelf_StartWait";
        }

        sGun = GetCharacterEquipByGroup(pchar, GUN_ITEM_TYPE);
        if (sGun != "")
        {
            if (CheckAttribute(pchar, "chr_ai.bulletNum") && sti(pchar.chr_ai.bulletNum) > 1)
            {
                Link.l8 = "Хочу выбрать тип боеприпаса для огнестрельного оружия.";
                Link.l8.go = "SetGunBullets";
            }
        }

        Link.l14 = "Хочу выбрать тип лечебного зелья для постоянного употребления.";
        Link.l14.go = "ChoosePotion";

        //--> Голландский гамбит
        if (CheckAttribute(pchar, "questTemp.HWIC_Coordinates") && PChar.location == Get_My_Cabin())
        {
            Link.l9 = "Заняться нахождением острова по координатам на карте.";
            Link.l9.go = "Seek_AbyIsland";
        }
        //<-- Голландский гамбит

        //--> Ложный след
        if (CheckAttribute(pchar, "questTemp.FalseTrace") && pchar.questTemp.FalseTrace == "TalkCabin" && PChar.location == Get_My_Cabin())
        {
            Link.l11 = "Вызвать Адама Рейнера.";
            Link.l11.go = "FalseTrace_Cabin";
        }
        if (CheckAttribute(pchar, "questTemp.FalseTrace") && pchar.questTemp.FalseTrace == "CatchAdam" && PChar.location == Get_My_Cabin())
        {
            Link.l11 = "Арестовать Адама Рейнера.";
            Link.l11.go = "FalseTrace_Cabin";
        }
        //<-- Ложный след
        // Addon 2016-1 Jason Пиратская линейка
        if (CheckAttribute(pchar, "questTemp.Mtraxx.Ammo") && PChar.location == "Shore37") // прогон 3
        {
            Link.l15 = "Пересчитать содержимое сундука и принять решение по окончанию сбора амуниции для Жана Пикара.";
            Link.l15.go = "mtraxx_ammo";
        }
        if (CheckAttribute(pchar, "questTemp.Mtraxx.Mutiny") && pchar.location == "Maracaibo_Plantation" && stf(environment.time) >= 3.00 && stf(environment.time) < 4.00)
        {
            Link.l15 = "Отдать приказ об атаке на плантацию Маракайбо.";
            Link.l15.go = "mtraxx_mutiny";
        }
        if (CheckAttribute(pchar, "questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "merida_boats" && pchar.location == "Maracaibo_river")
        {
            Link.l15 = "Отдать приказ о постройке лодок.";
            Link.l15.go = "mtraxx_boats";
        }
        if (CheckAttribute(pchar, "questTemp.Mtraxx.Retribution") && pchar.questTemp.Mtraxx.Retribution == "powder" && pchar.location == "shore10")
        {
            Link.l15 = "Отдать приказ о доставке пороха к завалу.";
            Link.l15.go = "mtraxx_powder";
        }
        // Jason Долго и счастливо
        if (CheckAttribute(pchar, "questTemp.LongHappy") && pchar.questTemp.LongHappy == "letter")
        {
            Link.l16 = "Обдумать свадьбу.";
            Link.l16.go = "LH_marry";
        }
        if (CheckAttribute(pchar, "questTemp.LongHappy") && pchar.questTemp.LongHappy == "marry_offer" && LongHappy_CheckShore()) // 28-03-20
        {
            Link.l16 = "Сделать предложение руки и сердца.";
            Link.l16.go = "LH_marry_3";
        }
        if (CheckAttribute(pchar, "questTemp.LongHappy") && pchar.questTemp.LongHappy == "toIslaTesoro" && pchar.location == "Pirates_town")
        {
            Link.l16 = "Подготовить праздник.";
            Link.l16.go = "LH_marry_4";
        }
        // -->Авторемонт
        if (Pchar.Location == Pchar.location.from_sea && CheckOfficersPerk(pchar, "SelfRepair") && CheckSelfRepairConditions())
        {
            Link.l12 = "Начать ремонт кораблей";
            Link.l12.go = "StartSelfRepair";
        }
        // <--Авторемонт
        //--> завершение игры
        if (CheckAttribute(pchar, "questTemp.Tieyasal_WinEnd")) // patch-9
        {
            Link.l13 = "Закончить дела на Карибах и отправиться в Европу.";
            Link.l13.go = "final_1";
        }
        //<-- завершение игры
        Link.l10 = RandPhraseSimple("Не сейчас. Нет времени.", "Некогда. Дела ждут.");
        Link.l10.go = "exit";
        break;

    case "StartSelfRepair":
        NextDiag.CurrentNode = NextDiag.TempNode;
        DialogExit_Self();
        LaunchRepair(pchar);
        break;

    case "SetGunBullets":
        Dialog.Text = "Выбор типа боеприпаса :";
        sGun = GetCharacterEquipByGroup(pchar, GUN_ITEM_TYPE);
        rItm = ItemsFromID(sGun);
        makearef(rType, rItm.type);
        for (i = 0; i < sti(pchar.chr_ai.bulletNum); i++)
        {
            sAttr = GetAttributeName(GetAttributeN(rType, i));
            sBullet = rItm.type.(sAttr).bullet;
            rItem = ItemsFromID(sBullet);
            attrL = "l" + i;
            Link.(attrL) = GetConvertStr(rItem.name, "ItemsDescribe.txt");
            ;
            Link.(attrL).go = "SetGunBullets1_" + i;
        }
        break;

    case "SetGunBullets2":
        i = sti(PChar.GenQuest.SetGunBullets) + 1;
        sGun = GetCharacterEquipByGroup(pchar, GUN_ITEM_TYPE);
        rItm = ItemsFromID(sGun);
        sAttr = "t" + i;
        sBullet = rItm.type.(sAttr).bullet;
        LAi_SetCharacterUseBullet(pchar, sBullet);
        LAi_GunSetUnload(pchar);
        NextDiag.CurrentNode = NextDiag.TempNode;
        DeleteAttribute(pchar, "GenQuest.SetGunBullets");
        DialogExit_Self();
        break;

    case "ChoosePotion":
        Dialog.Text = "";
        Link.l1 = "Лечебную эссенцию.";
        Link.l1.go = "ChoosePotion1";
        Link.l2 = "Эликсир.";
        Link.l2.go = "ChoosePotion2";
        Link.l3 = "Микстуру.";
        Link.l3.go = "ChoosePotion3";
        Link.l4 = "Имбирный корень.";
        Link.l4.go = "ChoosePotion4";
        Link.l5 = "Ром.";
        Link.l5.go = "ChoosePotion5";
        Link.l6 = "Вино.";
        Link.l6.go = "ChoosePotion6";
        if (CheckAttribute(pchar, "GenQuest.Potion_choice"))
        {
            Link.l7 = "Хочу выбирать автоматически.";
            Link.l7.go = "ChoosePotion7";
        }
        Link.l8 = "Стоп, я передумал.";
        Link.l8.go = "ChoosePotion8";
        break;

    case "ChoosePotion1":
        log_info("По умолчанию будет использоваться зелье 'лечебная эссенция'");
        pchar.GenQuest.Potion_choice = "potion1";
        DialogExit_Self();
        break;

    case "ChoosePotion2":
        log_info("По умолчанию будет использоваться зелье 'эликсир'");
        pchar.GenQuest.Potion_choice = "potion2";
        DialogExit_Self();
        break;

    case "ChoosePotion3":
        log_info("По умолчанию будет использоваться зелье 'микстура'");
        pchar.GenQuest.Potion_choice = "potion4";
        DialogExit_Self();
        break;

    case "ChoosePotion4":
        log_info("По умолчанию будет использоваться зелье 'имбирный корень'");
        pchar.GenQuest.Potion_choice = "potion5";
        DialogExit_Self();
        break;

    case "ChoosePotion5":
        log_info("По умолчанию будет использоваться зелье 'ром'");
        pchar.GenQuest.Potion_choice = "potionrum";
        DialogExit_Self();
        break;

    case "ChoosePotion6":
        log_info("По умолчанию будет использоваться зелье 'вино'");
        pchar.GenQuest.Potion_choice = "potionwine";
        DialogExit_Self();
        break;

    case "ChoosePotion7":
        log_info("Лечебное зелье будет выбираться автоматически");
        DeleteAttribute(pchar, "GenQuest.Potion_choice");
        DialogExit_Self();
        break;

    case "ChoosePotion8":
        DialogExit_Self();
        break;

    case "TalkSelf_StartWait":
        NextDiag.CurrentNode = NextDiag.TempNode;
        DialogExit_Self();
        PChar.GenQuest.CallFunctionParam = "LaunchTavernWaitScreen";
        DoQuestCheckDelay("CallFunctionParam", 0.1); // Нужно с задержкой, иначе - ГГ начинает крутиться
        break;

    case "TalkSelf_room_night":
        NextDiag.CurrentNode = NextDiag.TempNode;
        //AddDialogExitQuestFunction("TavernWaitDate_Night");
        TavernWaitDate("wait_night");
        DialogExit_Self();
        break;

    case "TalkSelf_room_day":
        NextDiag.CurrentNode = NextDiag.TempNode;
        //AddDialogExitQuestFunction("TavernWaitDate_Day");
        TavernWaitDate("wait_day");
        DialogExit_Self();
        break;
    //  захват города
    case "TalkSelf_TownAttack":
        bOk = (GetPartyCrewQuantity(Pchar, true) >= 500) || bBettaTestMode;
        if (sti(Pchar.Ship.Type) != SHIP_NOTUSED && bOk)
        {
            chr = GetCharacter(GetCharIDXForTownAttack(pchar.location));
            if (chr.from_sea == Pchar.location.from_sea)
            {
                Dialog.Text = "Начать захват, конечно, можно, да вот только корабль под залпами форта долго не продержится. И десант высадить не успеем.";
                Link.l1 = "...";
                Link.l1.go = "exit";
            }
            else
            {
                if (pchar.location == "Panama_ExitTown" || pchar.location == "Tortuga_ExitTown") // patch-5
                {
                    Dialog.Text = "Не-е-ет, я не сумасшедший. Взять этот город с суши невозможно...";
                    Link.l1 = "...";
                    Link.l1.go = "exit";
                }
                else
                {
                    if (pchar.location == "Minentown_ExitTown")
                    {
                        Dialog.Text = "Нет смысла атаковать этот рудник без достоверных сведений о собранном на нем золоте и серебре. Только напрасно людей положу под его стенами...";
                        Link.l1 = "...";
                        Link.l1.go = "exit";
                    }
                    else
                    {
                        Dialog.Text = "Напасть на город " + GetCityName(chr.City) + ".";
                        if (CheckAttribute(pchar, "questTemp.Patria.SanJoseAttack") && pchar.location == "PortSpein_ExitTown") // Jason НСО
                        {
                            Link.l1 = "Хватит заниматься глупостями! Отставить!";
                            Link.l1.go = "exit";
                            break;
                        }
                        if (CheckAttribute(pchar, "questTemp.Patria")) // Jason НСО
                        {
                            if (pchar.questTemp.Patria != "fail" || pchar.questTemp.Patria != "complete")
                            {
                                if (pchar.location == "Marigo_ExitTown" || pchar.location == "Villemstad_ExitTown")
                                {
                                    Link.l1 = "Хватит заниматься глупостями! Отставить!";
                                    Link.l1.go = "exit";
                                    break;
                                }
                            }
                        }
                        Link.l1 = "К оружию!";
                        Link.l1.go = "TalkSelf_TownAttack_Start";
                        Link.l2 = "Отставить!";
                        Link.l2.go = "exit";
                    }
                }
            }
        }
        else
        {
            if (!CheckAttribute(Pchar, "GenQuestFort.StartAttack"))
            {
                Dialog.Text = "Эх! Команды маловато, нужно хотя бы 500 человек.";
                Link.l1 = "...";
                Link.l1.go = "exit";
            }
            else
            {
                Dialog.Text = "Не разбредаться! Продолжаем атаку!";
                Link.l2 = "...";
                Link.l2.go = "exit";
            }
        }
        break;

    case "TalkSelf_TownAttack_Start":
        NextDiag.CurrentNode = NextDiag.TempNode;

        Pchar.GenQuestFort.StartAttack = true;
        Pchar.GenQuestFort.fortCharacterIdx = GetCharIDXForTownAttack(pchar.location);
        DeleteQuestAttribute("Union_with_Escadra");
        chr = GetCharacter(sti(Pchar.GenQuestFort.fortCharacterIdx));
        if (isCityHasFort(chr.City))
        {
            SetLocationCapturedState(chr.from_sea, true);
        }
        else
        {
            SetLocationCapturedState(chr.Default, true); // для сухопутных
        }
        AddDialogExitQuest("Capture_Forts");
        Ship_NationAgressive(chr, chr);
        DialogExit_Self();
        break;
    // Зачислить рабов в команду  -->
    case "TalkSelf_SlavesToCrew":
        if (GetCurCrewEscadr() >= GetMaxCrewAble())
        {
            Dialog.Text = "Никто из рабов не хочет идти в команду.";
            Link.l1 = "Ну и не нужно!";
            Link.l1.go = "exit";
        }
        else
        {
            if (GetCrewQuantity(pchar) >= GetMaxCrewQuantity(pchar))
            {
                Dialog.Text = "На корабле нет места для новых матросов.";
                Link.l1 = "Эх! Нужно переместить часть экипажа на другой корабль.";
                Link.l1.go = "exit";
            }
            else
            {
                if (GetFreeCrewQuantity(pchar) <= GetCargoGoods(pchar, GOOD_SLAVES))
                {
                    pchar.GenQuest.SlavesToCrew = GetFreeCrewQuantity(pchar);
                }
                else
                {
                    pchar.GenQuest.SlavesToCrew = GetCargoGoods(pchar, GOOD_SLAVES);
                }
                Dialog.Text = "В команду желают пойти " + pchar.GenQuest.SlavesToCrew + " рабов. Взять их?";
                Link.l1 = "Да";
                Link.l1.go = "TalkSelf_SlavesToCrew_1";
                Link.l2 = "Нет";
                Link.l2.go = "exit";
            }
        }
        break;

    case "TalkSelf_SlavesToCrew_1":
        if (CheckOfficersPerk(pchar, "IronWill"))
        {
            AddCrewMorale(pchar, -makeint(sti(pchar.GenQuest.SlavesToCrew) / 5.0))
        }
        else
        {
            AddCrewMorale(pchar, -makeint(sti(pchar.GenQuest.SlavesToCrew) / 3.0))
        }
        ChangeCharacterComplexReputation(pchar, "authority", -0.5);
        // падение опыта -->
        fTemp = stf(GetCrewQuantity(pchar) + sti(pchar.GenQuest.SlavesToCrew));
        pchar.Ship.Crew.Exp.Sailors = (stf(pchar.Ship.Crew.Exp.Sailors) * GetCrewQuantity(pchar) +
                                       stf(pchar.Ship.Crew.Exp.Sailors) * 0.3 * sti(pchar.GenQuest.SlavesToCrew)) /
                                      fTemp;
        pchar.Ship.Crew.Exp.Cannoners = (stf(pchar.Ship.Crew.Exp.Cannoners) * GetCrewQuantity(pchar) +
                                         stf(pchar.Ship.Crew.Exp.Cannoners) * 0.3 * sti(pchar.GenQuest.SlavesToCrew)) /
                                        fTemp;
        pchar.Ship.Crew.Exp.Soldiers = (stf(pchar.Ship.Crew.Exp.Soldiers) * GetCrewQuantity(pchar) +
                                        stf(pchar.Ship.Crew.Exp.Soldiers) * 0.3 * sti(pchar.GenQuest.SlavesToCrew)) /
                                       fTemp;
        // падение опыта <--
        pchar.Ship.Crew.Quantity = sti(pchar.Ship.Crew.Quantity) + sti(pchar.GenQuest.SlavesToCrew);
        RemoveCharacterGoodsSelf(pchar, GOOD_SLAVES, sti(pchar.GenQuest.SlavesToCrew));

        NextDiag.CurrentNode = NextDiag.TempNode;
        DialogExit_Self();
        break;
        // Зачислить рабов в команду  <--
        // boal <--

        //navy CONTRABAND METRO -->
    case "GenTravel_Main":
        NextDiag.TempNode = "First time";
        dialog.Text = "Теперь этот отличный корабль мой, и я здесь капитан! Жаль, пришлось вырезать всю команду.";
        Link.l1 = "Пора на берег...";
        Link.l1.go = "exit";

        chr = CharacterFromID("Abracham_Gray");
        chr.location = "none";
        SeaExchangeCharactersShips(PChar, chr, false, false);
        SetCrewQuantity(PChar, 0);

        //грузим ГГ куда нужно...
        SetAnyReloadToLocation(pchar.GenQuest.contraTravel.destination.loc, pchar.GenQuest.contraTravel.destination.group, pchar.GenQuest.contraTravel.destination.locator, "", 0, 0, 0, 0);
        AddDialogExitQuest("AnyReloadToLocation");
        chrDisableReloadToLocation = false;

        CloseQuestHeader("Gen_ContrabandTravel");
        setCharacterShipLocation(PChar, pchar.GenQuest.contraTravel.destination.loc);
        setWDMPointXZ(pchar.GenQuest.contraTravel.destination.loc);

        //трем аттрибуты
        DeleteAttribute(PChar, "GenQuest.contraTravel");
        break;
        //navy CONTRABAND METRO <--

        //navy --> 13.02.08
    case "Cabin_CompanionSelect":
        Dialog.Text = "Кого из компаньонов вызвать?";
        for (i = 1; i < GetCompanionQuantity(PChar); i++)
        {
            chr = GetCharacter(GetCompanionIndex(PChar, i));
            if (!CheckAttribute(chr, "Tasks.Clone") && sti(chr.Payment) == true)
            {
                sAttr = "l" + i;
                rShip = GetRealShip(sti(chr.Ship.Type));
                link.(sAttr) = GetFullName(chr) + " - " + xiStr(rShip.BaseName) + " '" + chr.Ship.Name + "'.";
                link.(sAttr).go = "CabinCompanionTalk_" + i;
            }
        }
        link.l9 = "В другой раз.";
        link.l9.go = "exit";
        break;

    case "Cabin_Companion_Talk":
        i = sti(PChar.GenQuest.CabinCompanionNum);
        PlaceCompanionCloneNearMChr(i, false);

        NextDiag.CurrentNode = NextDiag.TempNode;
        DialogExit_Self();
        break;
        //navy <--

    //--> Голландский гамбит
    case "Seek_AbyIsland":
        bOk = CheckCharacterItem(pchar, "bussol") && CheckCharacterItem(pchar, "clock2");
        bool bOk1 = CheckCharacterItem(pchar, "sextant2");
        if (bOk || bOk1)
        {
            DialogExit();
            DeleteAttribute(pchar, "questTemp.HWIC_Coordinates");
            pchar.questTemp.HWIC_FindIsland = "true";
            AddDialogExitQuestFunction("PrepareSearchingFor");
        }
        else
        {
            dialog.text = "Эх, у меня нет необходимых навигационных приборов для определения широты и долготы. Жаль. Поиски острова придется отложить.";
            link.l1 = "";
            link.l1.go = "exit";
        }
        break;
    //<-- Голландский гамбит

    //--> Ложный след
    case "FalseTrace_Cabin":
        dialog.text = "Боцман! Немедленно доставить ко мне Адама Рейнера!";
        link.l1 = "Есть, капитан!";
        link.l1.go = "exit";
        chr = characterFromId("Mugger");
        if (pchar.questTemp.FalseTrace == "CatchAdam")
            chr.dialog.currentnode = "FalseTrace_17";
        else
            chr.dialog.currentnode = "FalseTrace_7";
        pchar.questTemp.FalseTrace.CharID = "Mugger";
        AddDialogExitQuest("SetFalseTraceCharToCabin");
        break;

    case "FalseTrace_Woman":
        DialogExit();
        chr = characterFromId("FalseTraceWife");
        chr.dialog.currentnode = "FalseTrace_wife_6";
        pchar.questTemp.FalseTrace.CharID = "FalseTraceWife";
        AddDialogExitQuest("SetFalseTraceCharToCabin");
        break;
    //<-- Ложный след

    //--> LSC, приколы со стуком в дверь
    case "knock_2":
        PlaySound("interface\knock_2.wav");
        dialog.text = "Постучали, теперь подождем ответа...";
        link.l1 = "(ждать)";
        link.l1.go = "knock_wrong";
        break;

    case "knock_3":
        PlaySound("interface\knock.wav");
        dialog.text = "Постучали, теперь подождем ответа...";
        link.l1 = "(ждать)";
        link.l1.go = "knock_wrong";
        break;

    case "knock_3_1":
        PlaySound("interface\knock_3_1.wav");
        dialog.text = "Постучали, теперь подождем ответа...";
        link.l1 = "(ждать)";
        link.l1.go = "knock_wrong";
        break;

    case "knock_1_3":
        PlaySound("interface\knock_1_3.wav");
        dialog.text = "Постучали, теперь подождем ответа...";
        link.l1 = "(ждать)";
        link.l1.go = "knock_wrong";
        break;

    case "knock_2_2":
        PlaySound("interface\knock_2_2.wav");
        dialog.text = "Постучали, теперь подождем ответа...";
        link.l1 = "(ждать)";
        link.l1.go = "knock_right";
        break;

    case "knock_wrong":
        dialog.text = "Не открывает... Значит, стучать надо было не так. Что же, приду завтра и попробую еще раз - сегодня мне уже наверняка не откроют.";
        link.l1 = "(уйти)";
        link.l1.go = "exit";
        break;

    case "knock_right":
        PlaySound("interface\key.wav");
        PlaySound("voice\russian\YouFace.wav");
        dialog.text = "О! Отозвался! И дверь отпер! Можно входить...";
        link.l1 = "(войти)";
        link.l1.go = "exit";
        DeleteAttribute(pchar, "questTemp.LSC.DiffIndoor");
        LocatorReloadEnterDisable("LostShipsCity_town", "reload74", false);
        break;
    //<-- LSC, приколы со стуком в дверь

    // суп из черепахи
    case "terrapin":
        PlaySound("Interface\Door_Kick.wav");
        PlaySound("voice\russian\EvilPirates02.wav");
        dialog.text = "Карамба! Вот и дождались! Пришла запоздалая подмога Левассеру... Через дверь не выйти. Ну что же, последую следом за Тибо - через окно. Ведь смылся же куда-то этот прохвост!";
        link.l1 = "";
        link.l1.go = "exit";
        AddDialogExitQuest("Terrapin_GoWindow");
        break;

    // защита Сен-Пьера
    case "SP_defend":
        PlaySound("VOICE\Russian\military02.wav");
        dialog.text = "Итак, перед нами поставлена задача - отбить атаку проклятых кастильцев на поселение Сен-Пьер. Форт захвачен, бои идут на улицах города. В бухте Сен-Пьера расположилась мощная вражеская эскадра, флагман которой - линейный корабль. Атаковать эскадру бесполезно - в форте засели испанцы, кроме того, кастильцы в городе не позволят нам высадить десант на лодках\nПоэтому мною было принято решение пройти через джунгли и атаковать мерзавцев с тыла через городские ворота. Очистив город и форт от захватчиков, займемся эскадрой. Лишенная поддержки форта, она станет гораздо более уязвимой\nБой предстоит непростой, и я отдал распоряжение выплатить сверх вашего жалования сто тысяч песо на всю команду. Надеюсь, это укрепит вашу решимость в предстоящей битве. Вперед!";
        link.l1 = "";
        link.l1.go = "exit";
        AddDialogExitQuest("DefendSP_GoJungle");
        break;

    // финал игры
    case "final_1":                                                // Jason НСО
        if (CheckAttribute(pchar, "questTemp.Patria.GenGovernor")) // генерал-губернатор никуда не уедет
        {
            dialog.text = "Хотя, куда это я собрался? Я не могу покинуть пост генерал-губернатора без разрешения из Парижа! Иначе во Франции меня будет определенно ждать арест за самовольное оставление вверенных колоний. Париж, я буду скучать по тебе...";
            link.l1 = "";
            link.l1.go = "exit";
        }
        else
        {
            dialog.text = "Тогда не будем терять времени! Я уже соскучился по полям родной Гаскони! Поднимаем паруса!";
            link.l1 = "";
            link.l1.go = "exit";
            AddDialogExitQuest("Final_ReturnToEurope");
        }
        break;

    case "final_2":
        dialog.text = "И я думаю, это правильное решение! Что я там забыл, в этой старушке-Европе, когда здесь я нашел самого себя? А вернуться во Францию я всегда успею!";
        link.l1 = "";
        link.l1.go = "exit";
        AddDialogExitQuest("Final_StayInCarribean"); // 010912
        DeleteAttribute(pchar, "questTemp.Tieyasal_final");
        break;

    // Addon-2016 Jason, французские миниквесты (ФМК) Сент-Кристофер
    case "FMQN_1":
        dialog.text = "И это самое верное решение. Отправляюсь на корабль и немедленно поднимаю паруса.";
        link.l1 = "";
        link.l1.go = "exit";
        AddDialogExitQuestFunction("FMQN_ChooseExit");
        break;

    case "FMQN_2":
        dialog.text = "Нет уж, все-таки останусь. Но черта с два я буду сидеть и ждать у моря погоды - отправляюсь на корабль, пойду в порт Филипсбурга и разнюхаю обстановку. Я не намерен становиться слепым орудием в руках не внушающего доверия англичанина.";
        link.l1 = "";
        link.l1.go = "exit";
        AddDialogExitQuestFunction("FMQN_ChooseContinue");
        break;

    // Addon 2016-1 Jason Пиратская линейка
    case "mtraxx_ammo":
        Mtraxx_PlantCheckShoreBox();                                                                                             // анализируем содержимое сундука
        if (CheckAttribute(pchar, "questTemp.Mtraxx.Weapon.Blade") && !CheckAttribute(pchar, "questTemp.Mtraxx.Weapon.NoBlade")) // собрали 30 сабель
        {
            dialog.text = "Тридцать единиц холодного оружия в сундуке! Можно завершать, либо донести еще пистолей, пуль, зелий?..";
            link.l1 = "Сбор оружия и амуниции закончен!";
            link.l1.go = "mtraxx_ammo_1";
            link.l2 = "Нет, надо заполнять сундук дальше.";
            link.l2.go = "exit";
        }
        else
        {
            dialog.text = "Тридцать единиц холодного оружия еще не собраны! Надо продолжать работу.";
            link.l1 = "";
            link.l1.go = "exit";
        }
        break;

    case "mtraxx_ammo_1":
        dialog.text = "Сундук запираем и разрабатываем план по его скрытной доставке на плантацию.";
        link.l1 = "";
        link.l1.go = "exit";
        AddDialogExitQuestFunction("Mtraxx_PlantShoreBoxComplete");
        break;

    case "mtraxx_mutiny":
        dialog.text = "Вперед, в атаку! Ура!!";
        link.l1 = "";
        link.l1.go = "exit";
        AddDialogExitQuestFunction("Mtraxx_PlantMutiny");
        break;

    case "mtraxx_boats":
        if (GetSquadronGoods(pchar, GOOD_PLANKS) >= 20 && GetSquadronGoods(pchar, GOOD_LEATHER) >= 10) // наличие материалов
        {
            if (Mtraxx_MeridaCheckCarpenter()) // наличие плотника
            {
                dialog.text = "Все материалы подготовлены, приступить к постройке лодок!";
                link.l1 = "";
                link.l1.go = "exit";
                AddDialogExitQuestFunction("Mtraxx_MeridaBuildBoats");
            }
            else
            {
                dialog.text = "Нет достаточно опытного плотника, способого взять руководство постройкой лодок. Надо назначить такого офицера.";
                link.l1 = "";
                link.l1.go = "exit";
            }
        }
        else
        {
            dialog.text = "Недостаточно материалов, нужно не менее 20 связок досок и 10 тюков кожи.";
            link.l1 = "";
            link.l1.go = "exit";
        }
        break;

    case "mtraxx_powder":
        if (GetSquadronGoods(pchar, GOOD_POWDER) >= 300) // наличие пороха
        {
            if (GetCrewQuantity(pchar) >= 20) // наличие команды
            {
                dialog.text = "Для доставки пороха все готово - отнести бочонки к завалу!";
                link.l1 = "";
                link.l1.go = "exit";
                AddDialogExitQuestFunction("Mtraxx_RetributionBarrels");
            }
            else
            {
                dialog.text = "Нет достаточного количества людей для переноски бочонков, надо не меньше 20 человек в команде.";
                link.l1 = "";
                link.l1.go = "exit";
            }
        }
        else
        {
            dialog.text = "Недостаточно пороха, нужно не меньше 300 картузов.";
            link.l1 = "";
            link.l1.go = "exit";
        }
        break;

    case "mtraxx_dungeon":
        PlaySound("ambient\jail\jail_door2.wav");
        dialog.text = "Кажется, где-то скрипнула и хлопнула дверь...";
        link.l1 = "";
        link.l1.go = "mtraxx_dungeon_1";
        break;

    case "mtraxx_dungeon_1":
        PlaySound("ambient\jail\jail_door1.wav");
        dialog.text = "Точно!.. Кто-то пожаловал сюда... Жан?..";
        link.l1 = "";
        link.l1.go = "exit";
        AddDialogExitQuestFunction("Mtraxx_RetributionRunToEnrico");
        break;

    // Jason Долго и счастливо
    case "LH_marry":
        if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer"))
            sld = characterFromId("Helena");
        else
            sld = characterFromId("Mary");
        string sTemp = sld.name;
        dialog.text = "Мы с " + sTemp + " давно вместе, и наши узы крепче любых церковных клятв, но я хочу, чтобы этот момент запомнился нам обоим. Поэтому - надо решить где мне стоит с ней поговорить:";
        if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer"))
        {
            link.l1 = "Исла Тесоро - этот остров много значит в нашей истории. Полагаю, лучше места не найти: бухта Сабу-Матила - очаровательна на закате!";
            link.l1.go = "LH_marry_1_1";
        }
        link.l2 = "Тортуга - символ свободы нашего времени, а вид с маяка на пролив Тортю достоин кисти любого живописца!";
        link.l2.go = "LH_marry_1_2";
        if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer"))
        {
            link.l3 = "Ямайка - с ней столько всего связано! А любоваться рассветом в бухте Портленд - это то, как я представляю себе рай на земле.";
            link.l3.go = "LH_marry_1_3";
        }
        break;

    case "LH_marry_1_1":
        pchar.questTemp.LongHappy.Shore = "Shore_ship1";
        AddQuestRecord("LongHappy", "2_1");
        if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer"))
            sld = characterFromId("Helena");
        else
            sld = characterFromId("Mary");
        sTemp = sld.name;
        AddQuestUserData("LongHappy", "sName", sTemp);
        dialog.text = "Но, без торжества в церкви не обойтись - все должно быть по всем канонам, чтобы отцу пришлось принять мой выбор. Значит - мне понадобится священник, и я не вижу в этой должности никого, кроме аббата Бенуа. Он старый друг отца и с него начались мои приключения в Новом Свете. Думаю, он согласится оказать мне такую честь.";
        link.l1 = "";
        link.l1.go = "LH_marry_2";
        break;

    case "LH_marry_1_2":
        pchar.questTemp.LongHappy.Shore = "Mayak6";
        AddQuestRecord("LongHappy", "2_2");
        if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer"))
            sld = characterFromId("Helena");
        else
            sld = characterFromId("Mary");
        sTemp = sld.name;
        AddQuestUserData("LongHappy", "sName", sTemp);
        dialog.text = "Но, без торжества в церкви не обойтись - все должно быть по всем канонам, чтобы отцу пришлось принять мой выбор. Значит - мне понадобится священник, и я не вижу в этой должности никого, кроме аббата Бенуа. Он старый друг отца и с него начались мои приключения в Новом Свете. Думаю, он согласится оказать мне такую честь.";
        link.l1 = "";
        link.l1.go = "LH_marry_2";
        break;

    case "LH_marry_1_3":
        pchar.questTemp.LongHappy.Shore = "Shore36";
        AddQuestRecord("LongHappy", "2_3");
        if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer"))
            sld = characterFromId("Helena");
        else
            sld = characterFromId("Mary");
        sTemp = sld.name;
        AddQuestUserData("LongHappy", "sName", sTemp);
        dialog.text = "Но, без торжества в церкви не обойтись - все должно быть по всем канонам, чтобы отцу пришлось принять мой выбор. Значит - мне понадобится священник, и я не вижу в этой должности никого, кроме аббата Бенуа. Он старый друг отца и с него начались мои приключения в Новом Свете. Думаю, он согласится оказать мне такую честь.";
        link.l1 = "";
        link.l1.go = "LH_marry_2";
        break;

    case "LH_marry_2":
        AddQuestRecord("LongHappy", "3");
        if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer"))
            sld = characterFromId("Helena");
        else
            sld = characterFromId("Mary");
        sTemp = sld.name;
        AddQuestUserData("LongHappy", "sName", sTemp);
        dialog.text = "Ну и куда без торжества мирского. Впрочем - это я бы предпочел обсудить с " + sTemp + " чуть позже.";
        link.l1 = "";
        link.l1.go = "exit";
        pchar.questTemp.LongHappy = "choose";
        break;

    case "LH_marry_3":
        dialog.text = "Ну что же, я готов!";
        link.l1 = "";
        link.l1.go = "exit";
        LongHappy_MarryOffer();
        break;

    case "LH_marry_4":
        if (LongHappy_CheckGoods())
        {
            dialog.text = "Все подготовлено!";
            link.l1 = "";
            link.l1.go = "exit";
            LongHappy_OnIslaTesoro();
        }
        else
        {
            dialog.text = "Еще не собраны все необходимые товары и деньги!";
            link.l1 = "";
            link.l1.go = "exit";
        }
        break;
    }
}

void DialogExit_Self()
{
    DialogExit();
    locCameraSleep(false); //boal
}