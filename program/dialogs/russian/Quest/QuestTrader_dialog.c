void ProcessDialogEvent()
{
    ref NPChar, sld;
    aref Link, NextDiag;
    int i, iTemp;
    string sTemp;

    DeleteAttribute(&Dialog, "Links");

    makeref(NPChar, CharacterRef);
    makearef(Link, Dialog.Links);
    makearef(NextDiag, NPChar.Dialog);

    switch (Dialog.CurrentNode)
    {
    case "First time":
        bool ok = CheckFreeSitFront(npchar);
        if (drand(11) > 8 && ok && !CheckAttribute(pchar, "GenQuest.Racing.Go") && !CheckAttribute(npchar, "quest.race") && sti(Pchar.Ship.Type) != SHIP_NOTUSED && 6 - sti(RealShips[sti(pchar.ship.type)].Class) > 0) //гонки на гидропланах
        {
            dialog.text = TimeGreeting() + ", " + GetAddress_Form(NPChar) + "! Меня зовут " + GetFullName(NPChar) + ", я капитан. Вижу, что вы тоже капитан корабля. Присоединитесь ко мне, опрокинем по стаканчику?";
            link.l1 = "Почему бы и нет? Давайте, выпьем, поболтаем.";
            link.l1.go = "Race_prepare";
            link.l2 = "Сожалею, но у меня нет времени. В другой раз.";
            link.l2.go = "exit";
            npchar.quest.race = "true";
        }
        else
        {
            //конвой торгового судна
            if (!CheckAttribute(pchar, "GenQuest.Escort.Trader") && !CheckAttribute(npchar, "quest.race") && sti(Pchar.Ship.Type) != SHIP_NOTUSED && !CheckAttribute(npchar, "repeat_work") && 6 - sti(RealShips[sti(pchar.ship.type)].Class) > 0 && GetCompanionQuantity(pchar) < 3)
            {
                dialog.text = TimeGreeting() + ", " + GetAddress_Form(NPChar) + "! Я " + GetFullName(NPChar) + ", торговец. Вижу, вы капитан корабля. Не желаете подзаработать пару тысяч песо?";
                link.l1 = "Заработать всегда желаю. Какого рода работу вы мне хотите предложить?";
                link.l1.go = "Escort_choice";
                link.l2 = "И какую же это работу мне может предложить торгаш, а? Охранять его дырявую лоханку? Я не оказываю услуг барыгам.";
                link.l2.go = "exit_distress";
                SaveCurrentNpcQuestDateParam(npchar, "repeat_work");
            }
            else
            {
                dialog.text = TimeGreeting() + ", " + GetAddress_Form(NPChar) + "! Как ваши дела? Вы что-то хотели?";
                link.l1 = TimeGreeting() + ", " + GetAddress_FormToNPC(NPChar) + ". Да нет, ничего не хотел - просто поздоровался. Удачно вам отдохнуть!";
                link.l1.go = "exit";
            }
        }
        break;

    case "exit_distress":
        DialogExit();
        NextDiag.CurrentNode = "Trader_distress";
        break;

    case "Trader_distress":
        dialog.text = "Капитан, мы ведь уже все обсудили - не так ли? Вы не имеете дел с 'барыгами' - так чего же вы от меня хотите?";
        link.l1 = "Да, обсудили. Ладно, сиди, пей свой ром. Мне пора.";
        link.l1.go = "exit";
        NextDiag.TempNode = "Trader_distress";
        break;

    case "Escort_choice":                                          //первые развилки - выбираем между городом, бухтой и необитайкой
        pchar.GenQuest.Escort.Trader.StartCity = GetCurrentTown(); //стартовый город
        pchar.GenQuest.Escort.Trader.ShipType = TraderShipType();  //тип корабля торговца
        pchar.GenQuest.Escort.Trader.Nation = npchar.nation;       //нация торговца
        switch (drand(2))
        {
        case 0:                                                                                                                                                                                        //город дружественный
            pchar.GenQuest.Escort.Trader.City = FindFriendCityToMC(false);                                                                                                                             //целевой город
            pchar.GenQuest.Escort.Trader.DaysQty = GetMaxDaysFromIsland2Island(GetArealByCityName(pchar.GenQuest.Escort.Trader.StartCity), GetArealByCityName(pchar.GenQuest.Escort.Trader.City)) + 5; //дни
            pchar.GenQuest.Escort.Trader.Money = makeint(sti(pchar.GenQuest.Escort.Trader.DaysQty) * 400 * ShipFactorMC() + sti(pchar.GenQuest.Escort.Trader.ShipType) * 700);                         //оплата от расстояния и классов кораблей ГГ и неписи
            pchar.GenQuest.Escort.Trader.Type1 = "true";                                                                                                                                               //тип задания
            pchar.GenQuest.Escort.Trader.Chance = rand(1);
            pchar.GenQuest.Escort.Trader.Add = "до " + XI_ConvertString("Colony" + pchar.GenQuest.Escort.Trader.City + "Gen") + "";
            dialog.text = "Я хотел бы вас попросить сопроводить меня до " + XI_ConvertString("Colony" + pchar.GenQuest.Escort.Trader.City + "Gen") + " за " + FindRussianDaysString(sti(pchar.GenQuest.Escort.Trader.DaysQty)) + ". За это я заплачу вам " + FindRussianMoneyString(sti(pchar.GenQuest.Escort.Trader.Money)) + ".";
            link.l1 = "Ну что же, почему бы и нет? Вдвоем всегда безопаснее, это понятно. Я согласен.";
            link.l1.go = "EscortType";
            link.l2 = "Я бы и рад помочь, но мне совсем в другую сторону.";
            link.l2.go = "Escort_exit";
            break;
        case 1:                     //бухта
            GetEscortTraderShore(); //целевая бухта
            while (pchar.GenQuest.Escort.Trader.City == "Terks" || pchar.GenQuest.Escort.Trader.City == "caiman" || pchar.GenQuest.Escort.Trader.City == "dominica")
            {
                GetEscortTraderShore();
            }                                                                                                                                                                        // patch-6
            pchar.GenQuest.Escort.Trader.DaysQty = GetMaxDaysFromIsland2Island(GetArealByCityName(pchar.GenQuest.Escort.Trader.StartCity), pchar.GenQuest.Escort.Trader.Island) + 5; //дни
            pchar.GenQuest.Escort.Trader.Money = makeint(sti(pchar.GenQuest.Escort.Trader.DaysQty) * 400 * ShipFactorMC() + sti(pchar.GenQuest.Escort.Trader.ShipType) * 700);       //оплата
            pchar.GenQuest.Escort.Trader.Type2 = "true";                                                                                                                             //тип задания
            pchar.GenQuest.Escort.Trader.Chance = rand(2);
            pchar.GenQuest.Escort.Trader.Add = "до " + XI_ConvertString(pchar.GenQuest.Escort.Trader.Shore + "Gen") + ", что недалеко от " + XI_ConvertString("Colony" + pchar.GenQuest.Escort.Trader.City + "Gen") + "";
            dialog.text = "Я хотел бы вас попросить сопроводить меня до " + XI_ConvertString(pchar.GenQuest.Escort.Trader.Shore + "Gen") + ", это недалеко от " + XI_ConvertString("Colony" + pchar.GenQuest.Escort.Trader.City + "Gen") + ", за " + FindRussianDaysString(sti(pchar.GenQuest.Escort.Trader.DaysQty)) + ". За это я заплачу вам " + FindRussianMoneyString(sti(pchar.GenQuest.Escort.Trader.Money)) + ".";
            link.l1 = "Ну что же, почему бы и нет? Я согласен.";
            link.l1.go = "EscortType";
            link.l2 = "Я бы и рад помочь, но мне совсем в другую сторону.";
            link.l2.go = "Escort_exit";
            break;
        case 2:                                                                                                                                                                      //необитайка
            pchar.GenQuest.Escort.Trader.Island = DesIsland();                                                                                                                       //целевой остров
            pchar.GenQuest.Escort.Trader.Shore = SelectQuestShoreLocationFromSea(pchar.GenQuest.Escort.Trader.Island);                                                               //и бухта на нем
            pchar.GenQuest.Escort.Trader.DaysQty = GetMaxDaysFromIsland2Island(GetArealByCityName(pchar.GenQuest.Escort.Trader.StartCity), pchar.GenQuest.Escort.Trader.Island) + 5; //дни
            pchar.GenQuest.Escort.Trader.Money = makeint(sti(pchar.GenQuest.Escort.Trader.DaysQty) * 400 * ShipFactorMC() + sti(pchar.GenQuest.Escort.Trader.ShipType) * 700);       //оплата
            pchar.GenQuest.Escort.Trader.Type3 = "true";                                                                                                                             //тип задания
            pchar.GenQuest.Escort.Trader.Chance = rand(2);
            pchar.GenQuest.Escort.Trader.Add = "до " + XI_ConvertString(pchar.GenQuest.Escort.Trader.Shore + "Gen") + ", что на необитаемом острове " + XI_ConvertString(pchar.GenQuest.Escort.Trader.Island) + "";
            dialog.text = "Я хотел бы вас попросить сопроводить меня до " + XI_ConvertString(pchar.GenQuest.Escort.Trader.Shore + "Gen") + ", это на острове " + XI_ConvertString(pchar.GenQuest.Escort.Trader.Island) + ", за " + FindRussianDaysString(sti(pchar.GenQuest.Escort.Trader.DaysQty)) + ". За это я заплачу вам " + FindRussianMoneyString(sti(pchar.GenQuest.Escort.Trader.Money)) + ".";
            link.l1 = "Ну что же, почему бы и нет? Я согласен. Хотя никогда не слышал про магазины или торговые точки на необитаемых островах.";
            link.l1.go = "EscortType";
            link.l2 = "Я бы и рад помочь, но мне совсем в другую сторону.";
            link.l2.go = "Escort_exit";
            break;
        }
        break;

    case "Escort_exit":
        DialogExit();
        DeleteAttribute(pchar, "GenQuest.Escort.Trader");
        break;

    case "Trader_wait":
        dialog.text = "Вы готовы к выходу в море, капитан? Я жду ваших указаний.";
        link.l1 = "Да, мы уже отправляемся. Встретимся в порту.";
        link.l1.go = "exit";
        NextDiag.TempNode = "Trader_wait";
        break;

    case "EscortType":
        dialog.text = "Замечательно! Я рад, что мы договорились. Надеюсь, путешествие пройдет без неприятных приключений.";
        link.l1 = "Я тоже на это надеюсь. Отправляемся в путь!";
        link.l1.go = "EscortType_go";
        NextDiag.CurrentNode = "Trader_wait";
        break;

    case "EscortType_go":
        //общие параметры
        DialogExit();
        pchar.GenQuest.Escort.Trader.id = npchar.id;
        pchar.GenQuest.Escort.Trader.model = npchar.model;
        npchar.lifeday = sti(pchar.GenQuest.Escort.Trader.DaysQty) + 1; // 170712
        DeleteAttribute(npchar, "CityType");
        CreateTraderShipAndAdd(); //присоединяем торговца
        pchar.GenQuest.Escort.Trader.ShipMaxHP = sti(npchar.ship.HP);
        ReOpenQuestHeader("TraderEscort");
        AddQuestRecord("TraderEscort", "1");
        AddQuestUserData("TraderEscort", "sDay", FindRussianDaysString(sti(pchar.GenQuest.Escort.Trader.DaysQty)));
        AddQuestUserData("TraderEscort", "sMoney", FindRussianMoneyString(sti(pchar.GenQuest.Escort.Trader.Money)));
        AddQuestUserData("TraderEscort", "sStartCity", XI_ConvertString("Colony" + pchar.GenQuest.Escort.Trader.StartCity + "Gen"));
        AddQuestUserData("TraderEscort", "sAdd", pchar.GenQuest.Escort.Trader.Add);
        pchar.GenQuest.Escort.Trader = "begin";
        //различные параметры
        if (CheckAttribute(pchar, "GenQuest.Escort.Trader.Type1")) //в дружественный город
        {
            pchar.GenQuest.Escort.Trader.Location = pchar.GenQuest.Escort.Trader.City + "_tavern";
            if (sti(pchar.GenQuest.Escort.Trader.Chance) == 1)
                CoolTraderHunterOnMap();
            else
                TraderHunterOnMap(); //запуск ДУ на глобалке
        }
        if (CheckAttribute(pchar, "GenQuest.Escort.Trader.Type2")) //в бухту
        {
            pchar.GenQuest.Escort.Trader.Location = pchar.GenQuest.Escort.Trader.Shore;
            if (sti(pchar.GenQuest.Escort.Trader.Chance) != 2)
                TraderHunterOnMap();
            else
            {
                pchar.quest.EscortTrader_Attack.win_condition.l1 = "location";
                pchar.quest.EscortTrader_Attack.win_condition.l1.location = pchar.GenQuest.Escort.Trader.Island;
                pchar.quest.EscortTrader_Attack.function = "EscortTraderAttackInShore";
            }
        }
        if (CheckAttribute(pchar, "GenQuest.Escort.Trader.Type3")) //на необитайку
        {
            pchar.GenQuest.Escort.Trader.Location = pchar.GenQuest.Escort.Trader.Shore;
            if (sti(pchar.GenQuest.Escort.Trader.Chance) == 0)
                TraderHunterOnMap();
            if (sti(pchar.GenQuest.Escort.Trader.Chance) == 1)
            {
                if (sti(RealShips[sti(pchar.Ship.Type)].BaseType) <= sti(pchar.GenQuest.Escort.Trader.ShipType) && sti(RealShips[sti(pchar.Ship.Type)].BaseType) != SHIP_GALEON_H && GetCompanionQuantity(pchar) < 3) //меряемся кораблями
                {                                                                                                                                                                                                     //нападет сам
                    pchar.quest.EscortTrader_Attack.win_condition.l1 = "location";
                    pchar.quest.EscortTrader_Attack.win_condition.l1.location = pchar.GenQuest.Escort.Trader.Island;
                    pchar.quest.EscortTrader_Attack.function = "DesIslandAttack";
                }
                else
                    CoolTraderHunterOnMap();
            }
            else
            { //будет засада + сам нападет
                pchar.quest.EscortTrader_Attack.win_condition.l1 = "location";
                pchar.quest.EscortTrader_Attack.win_condition.l1.location = pchar.GenQuest.Escort.Trader.Island;
                pchar.quest.EscortTrader_Attack.function = "DesIslandAttack";
            }
        }
        pchar.quest.EscortTrader_Complete.win_condition.l1 = "location";
        pchar.quest.EscortTrader_Complete.win_condition.l1.location = pchar.GenQuest.Escort.Trader.Location;
        pchar.quest.EscortTrader_Complete.function = "EscortTraderComplete";
        SetFunctionTimerCondition("EscortTrader_Over", 0, 0, sti(pchar.GenQuest.Escort.Trader.DaysQty), false);
        pchar.quest.EscortTrader_fail.win_condition.l1 = "NPC_Death"; //прерывание на потопление сопровождаемого
        pchar.quest.EscortTrader_fail.win_condition.l1.character = pchar.GenQuest.Escort.Trader.id;
        pchar.quest.EscortTrader_fail.function = "EscortTrader_failed";
        break;

    case "EscortTrader_complete": //сдаем квест
        sld = characterFromId(pchar.GenQuest.Escort.Trader.id);
        if (sti(sld.ship.HP) < makeint(sti(pchar.GenQuest.Escort.Trader.ShipMaxHP) / 4)) //если корпуса осталось меньше 1/4 - первая проверка
        {
            dialog.text = "Капитан, вы не подскажете, зачем я нанял вас? Вы только посмотрите на мой корабль! На что он похож? На решето! Он еле на плаву держится! Вы это видите? Я так и не понял, кто кого сопровождал - вы меня, или я вас. В общем, награды вы не получите, и не надейтесь. Вы ее не заслужили.";
            link.l1 = "Э-гхм... Если бы не я - ты бы вообще сейчас кормил крабов, тупой торгаш. Ладно, земля круглая - попадешься ты мне еще в море!";
            link.l1.go = "EscortTrader_complete_1";
            break;
        }
        if (sti(sld.ship.HP) < makeint(sti(pchar.GenQuest.Escort.Trader.ShipMaxHP) / 2)) //если корпуса осталось меньше 1/2 - вторая проверка
        {
            pchar.GenQuest.Escort.Trader.Money = makeint(sti(pchar.GenQuest.Escort.Trader.Money)) / 2;
            dialog.text = "Капитан, вы не подскажете, зачем я нанял вас? Вы только посмотрите на мой корабль! На что он похож? На решето! Вы это видите? В общем, я заплачу вам только половину причитавшейся суммы. И на большее не рассчитывайте!";
            link.l1 = "Э-гхм.. Ладно, я согласен. Ваш корабль и впрямь... немного пострадал.";
            link.l1.go = "EscortTrader_complete_2";
            break;
        }
        if (CheckAttribute(pchar, "GenQuest.Escort.Trader.Type2") && sti(pchar.GenQuest.Escort.Trader.Chance) == 1) //вместо денег - наводка
        {
            dialog.text = "Капитан, тут такое дело... У меня нет денег, чтобы заплатить вам за работу. Но не кипятитесь, пожалуйста, я хочу вам предложить оплату, которая значительно превзойдет обещанную мной.";
            link.l1 = "Гм... Я вообще-то рассчитывал получить деньги сейчас. Но, раз так - я тебя готов выслушать.";
            link.l1.go = "EscortTrader_complete_4";
            break;
        }
        dialog.text = "Спасибо вам большое, капитан. Вместе с вами я чувствовал себя как никогда уверенно, несмотря на грозившие опасности. Вот, возьмите ваше вознаграждение.";
        link.l1 = "Пожалуйста... Если что - обращайтесь снова!";
        link.l1.go = "EscortTrader_complete_3";
        break;

    case "EscortTrader_complete_1":
        dialog.text = "Не пытайтесь меня напугать! С вашим умением вести морские сражения эта угроза выглядит нелепо. Прощайте!";
        link.l1 = "Проваливай, барыга...";
        link.l1.go = "complete_exit";
        AddQuestRecord("TraderEscort", "4");
        AddComplexSeaExpToScill(20, 20, 20, 0, 20, 0, 0);
        AddCharacterExpToSkill(pchar, "Fortune", 20); //везение
        break;

    case "EscortTrader_complete_2":
        dialog.text = "Да, вы очень верно подметили - 'немного пострадал'... Вот, держите " + FindRussianMoneyString(sti(pchar.GenQuest.Escort.Trader.Money)) + " и прощайте.";
        link.l1 = "Всего доброго, " + npchar.name + ".";
        link.l1.go = "complete_exit";
        AddMoneyToCharacter(pchar, sti(pchar.GenQuest.Escort.Trader.Money));
        AddQuestRecord("TraderEscort", "5");
        AddQuestUserData("TraderEscort", "sMoney", FindRussianMoneyString(sti(pchar.GenQuest.Escort.Trader.Money)));
        AddComplexSeaExpToScill(50, 50, 50, 0, 50, 0, 50);
        AddCharacterExpToSkill(pchar, "Fortune", 40); //везение
        break;

    case "EscortTrader_complete_3":
        dialog.text = "Непременно! Ну, а теперь мне пора идти. До свидания, капитан!";
        link.l1 = "Удачи, " + npchar.name + "!";
        link.l1.go = "complete_exit";
        AddMoneyToCharacter(pchar, sti(pchar.GenQuest.Escort.Trader.Money));
        AddQuestRecord("TraderEscort", "6");
        AddQuestUserData("TraderEscort", "sMoney", FindRussianMoneyString(sti(pchar.GenQuest.Escort.Trader.Money)));
        AddComplexSeaExpToScill(100, 100, 100, 50, 100, 100, 150);
        AddCharacterExpToSkill(pchar, "Leadership", 80); //авторитет
        AddCharacterExpToSkill(pchar, "Fortune", 80);    //везение
        AddCharacterExpToSkill(pchar, "Sneak", 50);      //скрытность
        break;

    case "EscortTrader_complete_4":
        pchar.GenQuest.Escort.Trader.Enemyname = GenerateRandomName_Generator(sti(npchar.nation), "man");
        GetEnemyTraderGoods();
        pchar.GenQuest.Escort.Trader.EnIsland = DesIsland();
        dialog.text = "На архипелаге есть один торговец - " + pchar.GenQuest.Escort.Trader.Enemyname + ". У него собственный флейт, на котором он перевозит товары. Я совершенно точно знаю, что примерно через две недели он будет находиться у берегов необитаемого острова " + XI_ConvertString(pchar.GenQuest.Escort.Trader.EnIsland) + " - пополнять запасы воды и торговать с местными индейцами, а в трюмах его флейта будет полно " + pchar.GenQuest.Escort.Trader.add + ". Вояка он никудышный, захватить его корабль вам труда не составит\nТак что вы еще окажетесь в выигрыше, капитан.";
        link.l1 = "М-да... Homo homini lupus est, так, уважаемый?";
        link.l1.go = "EscortTrader_complete_5";
        break;

    case "EscortTrader_complete_5":
        dialog.text = "Что-что вы сейчас сказали? Я не понял...";
        link.l1 = "Я сказал - человек человеку - волк, да? Вы так легко и беззастенчиво 'сдаете' своего коллегу... Впрочем, мне до вашей совести дела нет, а за наводку спасибо. Счастливо оставаться, сударь!";
        link.l1.go = "EscortTrader_complete_6";
        break;

    case "EscortTrader_complete_6":
        DialogExit();
        chrDisableReloadToLocation = false;
        bDisableFastReload = false;
        pchar.quest.EscortTrader_fail.over = "yes";
        pchar.quest.EscortTrader_Over.over = "yes"; //снять оба прерывания
        npchar.lifeday = 0;
        LAi_SetActorType(npchar);
        LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "", 20.0);
        RemoveCharacterCompanion(Pchar, npchar);
        AddQuestRecord("TraderEscort", "7");
        AddQuestUserData("TraderEscort", "sIsland", XI_ConvertString(pchar.GenQuest.Escort.Trader.EnIsland));
        AddQuestUserData("TraderEscort", "sAdd", pchar.GenQuest.Escort.Trader.add);
        pchar.quest.EscortTrader_EnTrader.win_condition.l1 = "Timer";
        pchar.quest.EscortTrader_EnTrader.win_condition.l1.date.hour = sti(GetTime());
        pchar.quest.EscortTrader_EnTrader.win_condition.l1.date.day = GetAddingDataDay(0, 0, 12);
        pchar.quest.EscortTrader_EnTrader.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 12);
        pchar.quest.EscortTrader_EnTrader.win_condition.l1.date.year = GetAddingDataYear(0, 0, 12);
        pchar.quest.EscortTrader_EnTrader.win_condition.l2 = "location";
        pchar.quest.EscortTrader_EnTrader.win_condition.l2.location = pchar.GenQuest.Escort.Trader.EnIsland;
        pchar.quest.EscortTrader_EnTrader.function = "Create_EnemyTraderFleut";
        SetFunctionTimerCondition("EscortTraderEnemy_Over", 0, 0, 16, false); // таймер
        AddComplexSeaExpToScill(100, 100, 100, 50, 100, 100, 150);
        AddCharacterExpToSkill(pchar, "Leadership", 80); //авторитет
        AddCharacterExpToSkill(pchar, "Fortune", 80);    //везение
        AddCharacterExpToSkill(pchar, "Sneak", 50);      //скрытность
        break;

    case "complete_exit":
        DialogExit();
        CloseQuestHeader("TraderEscort");
        chrDisableReloadToLocation = false;
        bDisableFastReload = false;
        pchar.quest.EscortTrader_fail.over = "yes";
        pchar.quest.EscortTrader_Over.over = "yes";   //снять оба прерывания
        pchar.quest.EscortTrader_Attack.over = "yes"; // patch-8
        npchar.lifeday = 0;
        LAi_SetActorType(npchar);
        LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "", 20.0);
        RemoveCharacterCompanion(Pchar, npchar);
        DeleteAttribute(pchar, "GenQuest.Escort.Trader");
        break;

    case "Race_prepare":
        NextDiag.TempNode = "Race_begin";
        NextDiag.CurrentNode = NextDiag.TempNode;
        DialogExit();
        pchar.questTemp.friend_in_tavern = npchar.id;
        AddDialogExitQuest("alc");
        break;

    case "exit_sit":
        NextDiag.CurrentNode = "First time";
        DialogExit();
        AddDialogExitQuest("exit_sit");
        break;

    case "Race_begin": //гонки на гидропланах
        dialog.text = "Эх, давай выпьем по кружке доброго рому, капитан! Как жизнь твоя, как торговля?";
        link.l1 = "Да я не сказал бы, что я - торговец. Но в любом случае дела идут неплохо.";
        link.l1.go = "Race_begin_1";
        break;

    case "Race_begin_1":
        dialog.text = "И это главное! С учетом того, как неспокойно нынче в море.";
        link.l1 = "Да, это точно. Особенно тревожно вам, купцам - вон сколько охотников за содержимым ваших трюмов. А вы ни уйти от них не можете, ни защититься толком - лоханки ваши тихоходные и орудия самых малых калибров стоят - все за прибылью гонитесь. Только и спасает вас, что караванами по четыре-пять судов ходите.";
        link.l1.go = "Race_begin_2";
        break;

    case "Race_begin_2":
        dialog.text = "Ну, не все такие, дружище. Вот я, например, всегда в одиночку хожу - мне лишний балласт не нужен. Я отлично знаю воды Карибского моря, и, позволю себе заметить, неплохо управляюсь со своим кораблем и командой. Так что я запросто уйду в море от любого пирата.";
        link.l1 = "Да ну? Свежо предание, но верится с трудом. С полным трюмом товара? На торговой лоханке? Ты хочешь сказать, что сможешь уйти от пиратской бригантины или люггера?";
        link.l1.go = "Race_begin_3";
        break;

    case "Race_begin_3":
        dialog.text = "Похоже, дружище, ты сомневаешься в том, что мой корабль может ходить быстро? Хорошо. Предлагаю тебе пари.";
        link.l1 = "Какое пари?";
        link.l1.go = "Race_begin_4";
        break;

    case "Race_begin_4": //тут устанавливаем все параметры
        if (!CheckAttribute(pchar, "GenQuest.Racing"))
            pchar.GenQuest.Racing.Count = 0;
        pchar.GenQuest.Racing.Go.Nation = npchar.nation;
        pchar.GenQuest.Racing.Go.StartCity = GetCurrentTown();
        pchar.GenQuest.Racing.Go.City = FindFriendCityToMC(false); //целевой дружественный город
        pchar.GenQuest.Racing.Go.Island = GetIslandByCityName(pchar.GenQuest.Racing.Go.City);
        pchar.GenQuest.Racing.Go.DaysQty = makeint((GetMaxDaysFromIsland2Island(GetArealByCityName(pchar.GenQuest.Racing.Go.StartCity), GetArealByCityName(pchar.GenQuest.Racing.Go.City))) / 1.3); //дни
        pchar.GenQuest.Racing.Go.ShipName = GenerateRandomNameToShip(sti(npchar.nation));
        if (sti(pchar.GenQuest.Racing.Go.DaysQty) < 1)
            pchar.GenQuest.Racing.Go.DaysQty = 1; // patch-8
        dialog.text = "А вот такое. Я сегодня намереваюсь выйти в море и направляюсь в " + XI_ConvertString("Colony" + pchar.GenQuest.Racing.Go.City) + ". Я заявляю, что буду там через " + FindRussianDaysString(pchar.GenQuest.Racing.Go.DaysQty) + ". Попробуй обогнать меня и прибыть в " + XI_ConvertString("Colony" + pchar.GenQuest.Racing.Go.City) + " раньше. Отсчет времени начнем прямо сейчас. Рискнешь? Или не потянешь, хе-хе?";
        link.l1 = "Кто? Я не потяну? Не смеши. Ты рассчитываешь уложиться в эти сроки? Забавно. Я принимаю твое пари. С какой суммой ты готов расстаться?";
        link.l1.go = "Race_begin_5";
        link.l2 = "Больше у меня других дел нет, как устраивать гонки из-за какого-то глупого пари.";
        link.l2.go = "Race_exit";
        break;

    case "Race_exit":
        dialog.text = "Хм... Опасаетесь проиграть? Впрочем, и ладно. Но на будущее - не торопитесь со скоропалительными выводами - среди торговцев очень много опытных моряков... гораздо опытнее вас.";
        link.l1 = "Ладно-ладно, нечего мне тут морали читать, философ нашелся. Прощай...";
        link.l1.go = "exit_sit";
        DeleteAttribute(pchar, "GenQuest.Racing.Go");
        NextDiag.TempNode = "First time";
        break;

    case "Race_begin_5":
        dialog.text = "Предлагайте, капитан.";
        iTemp = 1;
        for (i = 5; i >= 1; i--)
        {
            sTemp = "l" + iTemp;
            link.(sTemp) = "" + FindRussianMoneyString(sti(10000 * i)) + "";
            link.(sTemp).go = "Racing_rate" + i;
            iTemp++;
        }
        break;

    case "Racing_rate5": //50 000
        if (drand(9) > 6)
        {
            dialog.text = "Отлично. Я согласен. Деньги на бочку, капитан. Вот моя ставка.";
            link.l1 = "Сейчас, только кошель достану...";
            link.l1.go = "Racing_rate";
            pchar.GenQuest.Racing.Go.Money = 50000;
        }
        else
        {
            dialog.text = "Что за несуразные предложения, капитан? За такие деньги можно купить шхуну и еще месяц пить не просыхая. Назовите разумную сумму.";
            link.l1 = "Для меня эта сумма и есть разумная - за меньшую я не намерен тут с тобой цацкаться. Мы ведь не в подворотне, сударь, чтобы спорить на два песо. Ладно... посидели - и хватит. Боишься спорить - как хочешь... Хвастать только горазд.";
            link.l1.go = "Race_exit";
            link.l2 = "Вот как? Ну, ладно. Давай подумаем...";
            link.l2.go = "Race_begin_5";
        }
        break;

    case "Racing_rate4": //40 000
        if (drand(9) > 4)
        {
            dialog.text = "Отлично. Я согласен. Деньги на бочку, капитан. Вот моя ставка.";
            link.l1 = "Сейчас, только кошель достану...";
            link.l1.go = "Racing_rate";
            pchar.GenQuest.Racing.Go.Money = 40000;
        }
        else
        {
            dialog.text = "Что за несуразные предложения, капитан? За такие деньги можно купить барк и еще месяц пить не просыхая. Назовите разумную сумму.";
            link.l1 = "Для меня эта сумма и есть разумная - за меньшую я не намерен тут с тобой цацкаться. Мы ведь не в подворотне, сударь, чтобы спорить на два песо. Ладно... посидели - и хватит. Боишься спорить - как хочешь... Хвастать только горазд.";
            link.l1.go = "Race_exit";
            link.l2 = "Вот как? Ну, ладно. Давай подумаем...";
            link.l2.go = "Race_begin_5";
        }
        break;

    case "Racing_rate3": //30 000
        if (drand(9) > 2)
        {
            dialog.text = "Отлично. Я согласен. Деньги на бочку, капитан. Вот моя ставка.";
            link.l1 = "Сейчас, только кошель достану...";
            link.l1.go = "Racing_rate";
            pchar.GenQuest.Racing.Go.Money = 30000;
        }
        else
        {
            dialog.text = "Что за несуразные предложения, капитан? За такие деньги можно купить шлюп и еще месяц пить не просыхая. Назовите разумную сумму.";
            link.l1 = "Для меня эта сумма и есть разумная - за меньшую я не намерен тут с тобой цацкаться. Мы ведь не в подворотне, сударь, чтобы спорить на два песо. Ладно... посидели - и хватит. Боишься спорить - как хочешь... Хвастать только горазд.";
            link.l1.go = "Race_exit";
            link.l2 = "Вот как? Ну, ладно. Давай подумаем...";
            link.l2.go = "Race_begin_5";
        }
        break;

    case "Racing_rate2": //20 000
        if (drand(9) > 0)
        {
            dialog.text = "Отлично. Я согласен. Деньги на бочку, капитан. Вот моя ставка.";
            link.l1 = "Сейчас, только кошель достану...";
            link.l1.go = "Racing_rate";
            pchar.GenQuest.Racing.Go.Money = 20000;
        }
        else
        {
            dialog.text = "Что за несуразные предложения, капитан? За такие деньги можно купить люггер и еще месяц пить не просыхая. Назовите разумную сумму.";
            link.l1 = "Для меня эта сумма и есть разумная - за меньшую я не намерен тут с тобой цацкаться. Мы ведь не в подворотне, сударь, чтобы спорить на два песо. Ладно... посидели - и хватит. Боишься спорить - как хочешь... Хвастать только горазд.";
            link.l1.go = "Race_exit";
            link.l2 = "Вот как? Ну, ладно. Давай подумаем...";
            link.l2.go = "Race_begin_5";
        }
        break;

    case "Racing_rate1": //10 000
        dialog.text = "Отлично. Я согласен. Деньги на бочку, капитан. Вот моя ставка.";
        link.l1 = "Сейчас, только кошель достану...";
        link.l1.go = "Racing_rate";
        pchar.GenQuest.Racing.Go.Money = 10000;
        break;

    case "Racing_rate":
        dialog.text = "Ну, и?..";
        if (sti(pchar.money) >= sti(pchar.GenQuest.Racing.Go.Money))
        {
            link.l1 = "Вот! Моя ставка!";
            link.l1.go = "Racing_Go";
        }
        else
        {
            link.l1 = "Гм... Кажется, у меня нет такой суммы.";
            link.l1.go = "Racing_rate_nomoney";
        }
        break;

    case "Racing_rate_nomoney":
        if (sti(pchar.GenQuest.Racing.Go.Money) == 10000 || sti(pchar.Money) < 10000)
        {
            dialog.text = "Ну, знаете, мы не в подворотне, чтобы спорить на два песо. Или вы просто боитесь? А, ладно, черт с вами. Но на будущее - не торопитесь со скоропалительными выводами - среди торговцев очень много опытных моряков... гораздо опытнее вас.";
            link.l1 = "Ладно-ладно, нечего мне тут морали читать, философ нашелся. Прощай...";
            link.l1.go = "exit_sit";
            DeleteAttribute(pchar, "GenQuest.Racing.Go");
            NextDiag.TempNode = "First time";
        }
        else
        {
            dialog.text = "Тогда, может, посмотрите, сколько у вас есть, и сделаете ставку пониже?";
            link.l1 = "Хорошо, сейчас попробую вспомнить, сколько у меня денег имеется...";
            link.l1.go = "Race_begin_5";
            link.l2 = "Нет, пожалуй, не буду я с тобой спорить. Передумал.";
            link.l2.go = "Racing_exit";
        }
        break;

    case "Racing_exit":
        dialog.text = "Передумали? Хм... А может, вы просто боитесь? Впрочем, ладно, черт с вами. Но на будущее - не торопитесь со скоропалительными выводами - среди торговцев очень много опытных моряков... гораздо опытнее вас.";
        link.l1 = "Ладно-ладно, нечего мне тут морали читать, философ нашелся. Прощай...";
        link.l1.go = "exit_sit";
        DeleteAttribute(pchar, "GenQuest.Racing.Go");
        NextDiag.TempNode = "First time";
        break;

    case "Racing_Go":
        AddMoneyToCharacter(pchar, -sti(pchar.GenQuest.Racing.Go.Money));
        dialog.text = "Принято! Призовем в свидетели бармена, если вы не против... ему же и оставим наши ставки. Победитель вернется и заберет всю сумму. Обмануть не выйдет - новости по архипелагу разносятся очень быстро, так что трактирщик будет в курсе, кто из нас выиграл.";
        link.l1 = "Согласен. Так будет вернее.";
        link.l1.go = "Racing_Go_1";
        break;

    case "Racing_Go_1":
        dialog.text = "Ну, а теперь, думаю, нам следует отправиться на свои корабли - отсчет времени уже пошел. Не знаю, как вы, а я выхожу в море. Да, если что: мой корабль - флейт, называется - " + pchar.GenQuest.Racing.Go.ShipName + ". Думаю, вы легко его узнаете в порту прибытия, хе-хе...";
        link.l1 = "Не радуйся раньше времени. До встречи в таверне " + XI_ConvertString("Colony" + pchar.GenQuest.Racing.Go.City + "Gen") + "!";
        link.l1.go = "Racing_Go_2";
        break;

    case "Racing_Go_2":
        DialogExit();
        npchar.lifeday = 0;
        GetCharacterPos(pchar, &locx, &locy, &locz);
        ChangeCharacterAddressGroup(npchar, pchar.GenQuest.Racing.Go.StartCity + "_tavern", "goto", LAi_FindNearestFreeLocator("goto", locx, locy, locz));
        LAi_SetActorType(npchar);
        LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "exit_sit", -1);
        //работает корректно только через клон :(
        sTemp = npchar.model;
        int iNation = sti(npchar.Nation);
        sld = GetCharacter(NPC_GenerateCharacter("RaceTrader", sTemp, "man", "man", sti(PChar.rank) + 5, iNation, -1, true, "quest"));
        sld.name = npchar.name;
        sld.lastname = npchar.lastname;
        sld.Dialog.Filename = "Quest\QuestTrader_dialog.c";
        pchar.quest.Racing_Timer.win_condition.l1 = "Timer";
        pchar.quest.Racing_Timer.win_condition.l1.date.hour = sti(GetTime() + rand(6));
        pchar.quest.Racing_Timer.win_condition.l1.date.day = GetAddingDataDay(0, 0, sti(pchar.GenQuest.Racing.Go.DaysQty));
        pchar.quest.Racing_Timer.win_condition.l1.date.month = GetAddingDataMonth(0, 0, sti(pchar.GenQuest.Racing.Go.DaysQty));
        pchar.quest.Racing_Timer.win_condition.l1.date.year = GetAddingDataYear(0, 0, sti(pchar.GenQuest.Racing.Go.DaysQty));
        pchar.quest.Racing_Timer.function = "TraderRaceInTargetCity";
        pchar.quest.Racing_Finish.win_condition.l1 = "location";
        pchar.quest.Racing_Finish.win_condition.l1.location = pchar.GenQuest.Racing.Go.City + "_town";
        pchar.quest.Racing_Finish.function = "MCRaceInTargetCity";
        SetFunctionTimerCondition("RacingTimeOver", 0, 0, sti(pchar.GenQuest.Racing.Go.DaysQty) + 10, false);
        ReOpenQuestHeader("Racing");
        AddQuestRecord("Racing", "1");
        AddQuestUserData("Racing", "sStartCity", XI_ConvertString("Colony" + pchar.GenQuest.Racing.Go.StartCity + "Gen"));
        AddQuestUserData("Racing", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.Racing.Go.City + "Gen"));
        AddQuestUserData("Racing", "sDay", FindRussianDaysString(pchar.GenQuest.Racing.Go.DaysQty));
        AddQuestUserData("Racing", "sMoney", FindRussianMoneyString(sti(pchar.GenQuest.Racing.Go.Money)));
        break;

    case "Racing_Finished":
        if (CheckAttribute(pchar, "GenQuest.Racing.Go.MCWin"))
        {
            dialog.text = "Хех! Однако, я удивлен... Мои поздравления, капитан! Вы и впрямь оказались быстрее. Как говорится, на каждую силу найдется большая сила, так?";
            link.l1 = "Именно так, сударь. Но хочу вам сказать, что для кэпа торгового судна вы на редкость опытны и умелы - нечасто встретишь торговца, способного на флейте за такое короткое время покрыть это расстояние.";
            link.l1.go = "Racing_Finished_1";
        }
        else
        {
            dialog.text = "Ну что, капитан, удивлены? Как я вам уже говорил - я прекрасно знаю море и достаточно неплохо управляюсь с кораблем. Убедились?";
            link.l1 = "Аргх! Просто невероятно! На флейте, за такое время, на такое расстояние... поздравляю, капитан!";
            link.l1.go = "Racing_Finished_2";
        }
        //bDisableFastReload = false;
        //LocatorReloadEnterDisable(pchar.GenQuest.Racing.Go.City + "_town", "reload1_back", false);
        //LocatorReloadEnterDisable(pchar.GenQuest.Racing.Go.City + "_town", "reload2_back", false);
        //LocatorReloadEnterDisable(pchar.GenQuest.Racing.Go.City + "_town", "gate_back", false);
        break;

    case "Racing_Finished_1":
        dialog.text = "Что же, вы выиграли. Теперь вам нужно вернуться в поселение " + XI_ConvertString("Colony" + pchar.GenQuest.Racing.Go.StartCity) + " и забрать у бармена свои деньги. Вы их действительно заслужили!";
        link.l1 = "Именно это я и собираюсь сделать. А теперь позвольте откланяться. Был искренне рад нашему знакомству. До свидания!";
        link.l1.go = "Racing_end";
        pchar.GenQuest.Racing.Count = sti(pchar.GenQuest.Racing.Count) + 1;
        //запустить регату
        if (!CheckAttribute(pchar, "questTemp.RegataGo") && sti(pchar.GenQuest.Racing.Count) == 3)
        {
            pchar.questTemp.RegataGo = "true";
            pchar.questTemp.Regata.CureerCity = FindFriendCityToMC(true); //город, в котором вестовой подойдет
            if (pchar.questTemp.Regata.CureerCity == "PortRoyal")
                pchar.questTemp.Regata.CureerCity = "SentJons";
            pchar.quest.Regata_Cureer.win_condition.l1 = "location";
            pchar.quest.Regata_Cureer.win_condition.l1.location = pchar.questTemp.Regata.CureerCity + "_town";
            pchar.quest.Regata_Cureer.function = "PrepareToRegata";
            log_testinfo(pchar.questTemp.Regata.CureerCity);
        }
        pchar.GenQuest.Racing.Go.Advantage = "true";
        npchar.lifeday = 0;
        AddCharacterExpToSkill(pchar, "Sailing", 200);    //навигация
        AddCharacterExpToSkill(pchar, "Fortune", 200);    //везение
        AddCharacterExpToSkill(pchar, "Leadership", 100); //харизма
        ChangeCharacterComplexReputation(pchar, "authority", 3);
        ChangeOfficersLoyality("good_all", 3);
        break;

    case "Racing_Finished_2":
        dialog.text = "А на самом деле никакой мистики нет - просто умение и опыт. А теперь мне нужно собираться в обратный путь в " + XI_ConvertString("Colony" + pchar.GenQuest.Racing.Go.StartCity) + ", за своим выигрышем.";
        link.l1 = "Вы его заслужили. А теперь позвольте откланяться. Был искренне рад нашему знакомству. До свидания!";
        link.l1.go = "Racing_end";
        npchar.lifeday = 0;
        DeleteAttribute(pchar, "GenQuest.Racing.Go");
        AddCharacterExpToSkill(pchar, "Sailing", 50);    //навигация
        AddCharacterExpToSkill(pchar, "Fortune", 50);    //везение
        AddCharacterExpToSkill(pchar, "Leadership", 20); //харизма
        ChangeCharacterComplexReputation(pchar, "authority", 1);
        AddQuestRecord("Racing", "5");
        CloseQuestHeader("Racing");
        break;

    case "Racing_end":
        DialogExit();
        NextDiag.currentNode = "Racing_end_repeat";
        pchar.quest.Racing_fail.over = "yes";
        Group_DeleteGroup("RacingTrader");
        sld = characterFromId("RaceTraderSkiper");
        sld.lifeday = 0;
        break;

    case "Racing_end_repeat":
        dialog.text = "Что-то еще, капитан?";
        link.l1 = "Да нет, ничего.";
        link.l1.go = "exit";
        NextDiag.TempNode = "Racing_end_repeat";
        break;

    case "Exit":
        NextDiag.CurrentNode = NextDiag.TempNode;
        DialogExit();
        break;
    }
}

float ShipFactorMC() //коэффициент от класса корабля ГГ
{
    float f;
    int iInvert = 6 - sti(RealShips[sti(pchar.Ship.Type)].Class);
    switch (iInvert)
    {
    case 0:
        f = 0.5 break;
    case 1:
        f = 1.0 break;
    case 2:
        f = 1.2 break;
    case 3:
        f = 1.5 break;
    case 4:
        f = 2.2 break;
    case 5:
        f = 3.0 break;
    case 6:
        f = 4.5 break;
    }
    return f;
}

int TraderShipType() //корабль торговца
{
    int iShipType;
    int iRank = sti(pchar.rank);
    if (iRank < 5)
        iShipType = SHIP_BARQUE + rand(makeint(SHIP_SCHOONER - SHIP_BARQUE));
    if (iRank >= 5 && iRank < 11)
        iShipType = SHIP_BARKENTINE + rand(makeint(SHIP_FLEUT - SHIP_BARKENTINE));
    if (iRank >= 11 && iRank < 18)
        iShipType = SHIP_FLEUT + rand(makeint(SHIP_CARAVEL - SHIP_FLEUT));
    if (iRank >= 18 && iRank < 25)
        iShipType = SHIP_CARAVEL + rand(makeint(SHIP_CARACCA - SHIP_CARAVEL));
    if (iRank >= 25)
        iShipType = SHIP_CARAVEL + rand(makeint(SHIP_NAVIO - SHIP_CARAVEL));
    return iShipType;
}

void GetEnemyTraderGoods() //выберем товар
{
    switch (rand(7))
    {
    case 0:
        pchar.GenQuest.Escort.Trader.Goods = GOOD_EBONY;
        pchar.GenQuest.Escort.Trader.add = "черного дерева";
        break;
    case 1:
        pchar.GenQuest.Escort.Trader.Goods = GOOD_MAHOGANY;
        pchar.GenQuest.Escort.Trader.add = "красного дерева";
        break;
    case 2:
        pchar.GenQuest.Escort.Trader.Goods = GOOD_TOBACCO;
        pchar.GenQuest.Escort.Trader.add = "табака";
        break;
    case 3:
        pchar.GenQuest.Escort.Trader.Goods = GOOD_COFFEE;
        pchar.GenQuest.Escort.Trader.add = "кофе";
        break;
    case 4:
        pchar.GenQuest.Escort.Trader.Goods = GOOD_CINNAMON;
        pchar.GenQuest.Escort.Trader.add = "корицы";
        break;
    case 5:
        pchar.GenQuest.Escort.Trader.Goods = GOOD_FOOD;
        pchar.GenQuest.Escort.Trader.add = "провианта";
        break;
    case 6:
        pchar.GenQuest.Escort.Trader.Goods = GOOD_WEAPON;
        pchar.GenQuest.Escort.Trader.add = "оружия";
        break;
    case 7:
        pchar.GenQuest.Escort.Trader.Goods = GOOD_CHOCOLATE;
        pchar.GenQuest.Escort.Trader.add = "какао";
        break;
    }
}

bool CheckFreeSitFront(ref _npchar)
{
    ref rCharacter;
    int n;

    if (!CheckAttribute(_npchar, "Default.ToLocator"))
        return false;

    for (n = 0; n < MAX_CHARACTERS; n++)
    {
        makeref(rCharacter, Characters[n]);
        if (CheckAttribute(rCharacter, "location") && rCharacter.location == _npchar.location)
        {
            if (rCharacter.location.locator == _npchar.Default.ToLocator)
                return false;
        }
    }
    return true;
}