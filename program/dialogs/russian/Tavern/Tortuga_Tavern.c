// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
    {
    case "quests":
        dialog.text = NPCStringReactionRepeat("Все сплетни города " + GetCityName(npchar.city) + " к вашим услугам. Что бы вы хотели узнать?",
                                              "Мы только что поднимали это тему. Вы, вероятно, запамятовали...", "Сегодня вы уже третий раз говорите о каком-то вопросе...",
                                              "Что ты " + GetSexPhrase("заладил", "заладила") + " как попугай одно и то же...", "block", 1, npchar, Dialog.CurrentNode);
        link.l1 = HeroStringReactionRepeat("Знаешь, " + NPChar.name + ", как-нибудь в следующий раз.", "Точно, " + GetSexPhrase("забыл", "забыла") + " что-то...",
                                           "Да уж, действительно в третий раз...", "Да уж...", npchar, Dialog.CurrentNode);
        link.l1.go = "exit";
        if (pchar.questTemp.Slavetrader == "FindRatTortuga") // работорговец
        {
            link.l1 = "Послушай, где мне найти Франсуа Гонтьера? Он должен был уже прибыть на Тортугу.";
            link.l1.go = "Tortuga_ratT_1";
        }
        // суп из черепахи
        if (CheckAttribute(PChar, "questTemp.Terrapin") && pchar.questTemp.Terrapin == "tortuga")
        {
            link.l1 = "Я ищу Анри Тибо. Где мне его найти?";
            link.l1.go = "terrapin";
        }
        if (CheckAttribute(PChar, "questTemp.Terrapin") && pchar.questTemp.Terrapin == "tortuga1")
        {
            link.l1 = "Я ищу Анри Тибо. Где мне его найти?";
            link.l1.go = "terrapin_2";
        }
        if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "tortuga")
        {
            link.l1 = "Скажи, в вашу колонию в последнее время не заходил галеон под названием 'Санта-Маргарита'? Быть может, в качестве каперского приза?";
            link.l1.go = "guardoftruth";
        }
        // Addon 2016-1 Jason Пиратская линейка
        if (CheckAttribute(pchar, "questTemp.Mtraxx.Jeweller"))
        {
            link.l1 = "Послушай, мне нужен господин по имени Гаспар Парментье. Где я могу его найти?";
            link.l1.go = "mtraxx_jew";
        }
        break;

    case "Tortuga_ratT_1":
        dialog.text = "Франсуа Гонтьер? А кто это такой? Я не знаю человека с таким именем.";
        link.l1 = "Ну, он капитан корвета '" + pchar.questTemp.Slavetrader.ShipName + "'.";
        link.l1.go = "Tortuga_ratT_2";
        break;

    case "Tortuga_ratT_2":
        dialog.text = "Не имею ни малейшего представления, " + GetSexPhrase("дружище", "мэм") + ". И корвет с таким названием у нас в порту не причаливал, я совершенно точно знаю.";
        link.l1 = "Ну хорошо, а чужаков в городе в последнее время не видал?";
        link.l1.go = "Tortuga_ratT_3";
        break;

    case "Tortuga_ratT_3":
        dialog.text = "Ну, спросил" + GetSexPhrase("", "а") + "! Это же портовый город, а не деревня. Тут чужаки каждый день появляются... Хотя, слыхал я про каких-то странных типов, недавно объявившихся у нас\nХодят всегда вместе, впятером, и за эфесы сабель держатся, словно во вражеской колонии. Их уже и патруль проверял - нет, все в порядке. Но прибыли они точно не на корвете - ни в порту, ни на рейде - ни одного корвета, смекаешь?";
        link.l1 = "Гм... Ну что же, понятно. Спасибо, " + npchar.name + ".";
        link.l1.go = "exit";
        AddQuestRecord("Slavetrader", "21_8");
        pchar.questTemp.Slavetrader = "wait1"; //затычка
        break;

    // суп из черепахи
    case "terrapin":
        dialog.text = "Ну, месье Тибо – личность на Тортуге известная. Его особняк находится недалеко от портового управления. Как выйдешь из моей таверны - иди в сторону порта. Не доходя арки, ведущей в порт, на перекрестке поверни налево и ступай по улице до конца, пока не упрешься в каменный двухэтажный дом с красной крышей. Это и есть особняк месье Тибо.";
        link.l1 = "Спасибо!  Пойду в гости...";
        link.l1.go = "terrapin_1";
        break;

    case "terrapin_1":
        DialogExit();
        pchar.questTemp.Terrapin = "house";
        sld = characterFromId("Tibo");
        ChangeCharacterAddressGroup(sld, "Tortuga_houseS2", "barmen", "stay");
        LAi_SetOwnerType(sld);
        break;

    case "terrapin_2":
        dialog.text = "Сегодня на месье Тибо настоящий спрос, только что прибегал посыльный от губернатора. Тоже интересовался. А чего его искать? В последнее время он постоянно снимает у меня комнату на втором этаже, хотя у самого целый особняк. Не знаю, зачем ему это нужно, только входит он туда гораздо чаще, чем выходит. И бывает там только по вечерам.";
        link.l1 = "Может, и сейчас он у тебя";
        link.l1.go = "terrapin_3";
        break;

    case "terrapin_3":
        if (stf(environment.time) < 20.0 && stf(environment.time) > 8.0)
        {
            dialog.text = "Нет. Он сказал, что будет сегодня не раньше восьми вечера. Можешь попробовать поискать его у себя в особняке, но это вряд ли - я видел, что он отправился на патрульном люггере в море.";
            link.l1 = "Спасибо! Зайду к нему позже.";
            link.l1.go = "terrapin_4";
        }
        else
        {
            dialog.text = "Да. Если хочешь - можешь подняться.";
            link.l1 = "Спасибо! Пойду в гости...";
            link.l1.go = "terrapin_4";
        }
        break;

    case "terrapin_4":
        DialogExit();
        pchar.questTemp.Terrapin = "tavern";
        sld = characterFromId("Tibo");
        sld.dialog.currentnode = "tibo_9";
        LAi_SetLoginTime(sld, 20.0, 8.0);
        ChangeCharacterAddressGroup(sld, "Tortuga_tavern_upstairs", "goto", "goto1");
        LocatorReloadEnterDisable("Tortuga_tavern", "reload2_back", false);                  // откроем комнату
        LAi_LocationFightDisable(&Locations[FindLocation("Tortuga_tavern_upstairs")], true); //запретить драться
        LAi_SetStayType(sld);
        // Addon 2016-1 Jason Пиратская линейка
        if (GetCharacterIndex("Mary") != -1)
        {
            sld = characterFromId("Mary");
            if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && !IsOfficer(sld))
            {
                ChangeCharacterAddressGroup(sld, "none", "", "");
            }
        }
        if (GetCharacterIndex("Helena") != -1)
        {
            sld = characterFromId("Helena");
            if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && !IsOfficer(sld))
            {
                ChangeCharacterAddressGroup(sld, "none", "", "");
            }
        }
        break;

    case "guardoftruth":
        dialog.text = "Как уж там назывался этот корабль - 'Санта Маргарита', или 'Кастильская блудница', я не знаю, но с месяц назад действительно притащили сюда испанский галеон, взятый призом. Причем взяли его на шлюпе! Гай Марше, капитан этого шлюпа, потом два дня хлестал ром в таверне и все бахвалился своей удачей - первый поход, и такой приз!\nНу да, велик героизм: на том галеоне даже абордажной роты не было, взяли их голыми руками, как ягнят. Да и кому там сопротивление оказывать было, когда плыли на нем какие-то церковные крысы? Видать, забыли паписты старую поговорку...";
        link.l1 = "Да-да, на Бога надейся, но сам не плошай, это точно. А как мне увидеть этого удачливого кэпа? Он сейчас здесь, на Тортуге?";
        link.l1.go = "guardoftruth_1";
        break;

    case "guardoftruth_1":
        dialog.text = "А пес его знает. Я уже давно его не видел у себя в таверне. Он как протрезвел, так сразу загнал трофейный галеон в доки и бегал вокруг него, как угорелый. Понятия не имею, где Марше сейчас. Может, на Тортуге, а может - в плавании.";
        link.l1 = "Ясно. Ну что же, спасибо за рассказ, дружище!";
        link.l1.go = "guardoftruth_2";
        break;

    case "guardoftruth_2":
        dialog.text = "Всегда пожалуйста, месье " + pchar.name + ", любая информация для нашего славного капитана, спасителя Сен-Пьера! Заходите еще!";
        link.l1 = "...";
        link.l1.go = "exit";
        AddQuestRecord("Guardoftruth", "8");
        pchar.questTemp.Guardoftruth = "tortuga1";
        break;

    // Addon 2016-1 Jason Пиратская линейка
    case "mtraxx_jew":
        dialog.text = "Смотрю, Гаспар становится все популярней и популярней у вашей братии... Его дом находится у городской стены. Выйдешь из таверны, повернешь налево, пройдешь в сторону порта, не выходя в порт еще раз налево, до упора прямо и затем направо. Двухэтажный особняк.";
        link.l1 = "Спасибо, дружище!";
        link.l1.go = "exit";
        AddDialogExitQuestFunction("Mtraxx_WolfreekJewellerHouse");
        break;
    }
    UnloadSegment(NPChar.FileDialog2); // если где-то выход внутри switch  по return не забыть сделать анлод
}
