//Jason общий диалог уличных контриков
#include "DIALOGS\russian\Rumours\Common_rumours.c"
void ProcessDialogEvent()
{
    ref NPChar;
    aref Link, NextDiag;

    DeleteAttribute(&Dialog, "Links");

    makeref(NPChar, CharacterRef);
    makearef(Link, Dialog.Links);
    makearef(NextDiag, NPChar.Dialog);

    // вызов диалога по городам -->
    NPChar.FileDialog2 = "DIALOGS\" + LanguageGetLanguage() + "\Citizen\" + NPChar.City + "_Citizen.c ";
                         if (LoadSegment(NPChar.FileDialog2))
    {
        ProcessCommonDialog(NPChar, Link, NextDiag);
        UnloadSegment(NPChar.FileDialog2);
    }
    // вызов диалога по городам <--

    ProcessCommonDialogRumors(NPChar, Link, NextDiag);

    switch (Dialog.CurrentNode)
    {
    case "First time":
        dialog.text = "Что вам надо?";
        link.l1 = "Ничего.";
        link.l1.go = "exit";
        link.l2 = RandPhraseSimple("У меня есть вопрос к тебе.", "Мне нужна информация.");
        link.l2.go = "quests"; //(перессылка в файл города)

        if (npchar.quest.meeting == "0")
        {
            if (sti(Pchar.Ship.Type) != SHIP_NOTUSED && CheckAttribute(npchar, "quest.passenger") && !CheckAttribute(pchar, "GenQuest.Marginpassenger")) //захват пассажира
            {
                dialog.text = "Эй ты, моряк! Да-да, ты. Подойди-ка поближе, у меня к тебе дело есть...";
                link.l1 = "И что же это за дело-то такое, а?";
                link.l1.go = "passenger";
                link.l2 = "Друг, я спешу. Как-нибудь в следующий раз...";
                link.l2.go = "exit_quest";
                npchar.quest.meeting = "1";
                DeleteAttribute(npchar, "talker"); //снимаем говорилку
                break;
            }
            dialog.text = LinkRandPhrase("Эй, моряк, я вообще-то занят. Чего тебе?", "Что ты хочешь, солёный сюртук?", "Кэп, мне тут не до праздной трескотни. Что ты хотел?");
            link.l1 = "Приветствую, " + GetAddress_FormToNPC(NPChar) + ". Постой на минутку, я хочу, чтобы ты мне кое-что рассказал.";
            link.l1.go = "question";
            link.l2 = RandPhraseSimple("У меня есть вопрос к тебе.", "Мне нужна информация.");
            link.l2.go = "quests"; //(перессылка в файл города)
            link.l3 = "Да ничего, вот, в таверну иду...";
            link.l3.go = "exit";
            npchar.quest.meeting = "1";
        }
        NextDiag.TempNode = "First time";
        break;

        //----------------------------------------захват пассажиров для выкупа------------------------------------------
    case "passenger":
        DeleteAttribute(npchar, "talker");
        dialog.text = "Хм. Ты - капитан корабля, не торгаш, и, похоже, у тебя водятся деньжата... Как насчёт одной очень презанятной информации в обмен на пригоршню полновесных дублонов?";
        link.l1 = "Ты сначала скажи, стоит ли твоя информация хоть одного серебряного песо. И о чем пойдёт речь?";
        link.l1.go = "passenger_1";
        break;

    case "passenger_1":
        dialog.text = "Стоит, кэп, стоит. Она стоит намного дороже, чем я запрошу. Вы мне - золото, а я вам расскажу, когда и на каком корабле поплывет пассажиром человек, за которого можно содрать неплохой выкуп... И даже скажу, у кого. Интересно?";
        link.l1 = "Ни капли. Я не занимаюсь похищениями людей. Проваливай!";
        link.l1.go = "exit_quest";
        link.l2 = "А откуда мне знать, что ты не соврёшь, а?";
        link.l2.go = "passenger_2";
        break;

    case "passenger_2":
        pchar.GenQuest.Marginpassenger.Dublon = 70 + drand(5) * 10;
        dialog.text = "Я не стану обманывать тебя, солёный сюртук. Я живу в этом городе, и мне не нужны проблемы. За каких-то " + sti(pchar.GenQuest.Marginpassenger.Dublon) + " дублонов я предоставлю тебе исчерпывающие сведения. Ты заработаешь на этом значительно больше.";
        if (GetCharacterItem(pchar, "gold_dublon") >= sti(pchar.GenQuest.Marginpassenger.Dublon))
        {
            link.l1 = "Уговорил. Вот, держи. Но попробуй только рассказать мне какой-нибудь вздор или солгать...";
            link.l1.go = "passenger_4";
        }
        link.l2 = "У меня нет сейчас с собой такого количества золотых монет.";
        link.l2.go = "passenger_3";
        link.l3 = "Ты смеёшься? Платить такую кучу золота за неизвестно что? Шёл бы ты отсюда...";
        link.l3.go = "exit_quest";
        break;

    case "passenger_3":
        dialog.text = "Нет? Хорошо. Я могу и подождать день-другой, и эти сведения тоже. Как найдёшь золотишко - подходи, отыскать меня будет несложно, по крайней мере, сегодня, ха-ха!";
        link.l1 = "Чего зубы скалишь? Ладно, если надумаю - принесу тебе золото...";
        link.l1.go = "passenger_wait";
        break;

    case "passenger_wait":
        DialogExit();
        SetFunctionTimerCondition("Marginpassenger_Over", 0, 0, 2, false);
        npchar.dialog.currentnode = "passenger_repeat";
        break;

    case "passenger_repeat":
        dialog.text = "Ну что, таки принёс золотишко?";
        if (GetCharacterItem(pchar, "gold_dublon") >= sti(pchar.GenQuest.Marginpassenger.Dublon))
        {
            link.l1 = "Да. Вот, держи. Но попробуй только рассказать мне какой-нибудь вздор или солгать...";
            link.l1.go = "passenger_4";
        }
        link.l2 = "Пока нет. Может, позже...";
        link.l2.go = "exit";
        Nextdiag.Tempnode = "passenger_repeat";
        break;

    case "passenger_4":                                //установка параметров
        pchar.quest.Marginpassenger_Over.over = "yes"; //снять возможный таймер
        RemoveItems(pchar, "gold_dublon", sti(pchar.GenQuest.Marginpassenger.Dublon));
        pchar.GenQuest.Marginpassenger.Name = GetFullName(npchar);
        pchar.GenQuest.Marginpassenger.City = npchar.city;
        pchar.GenQuest.Marginpassenger.Targetcity = SelectAnyColony(npchar.city);
        pchar.GenQuest.Marginpassenger.Nation = npchar.nation;
        pchar.GenQuest.Marginpassenger.Days = 10 + drand(5);
        pchar.GenQuest.Marginpassenger.ShipName = GenerateRandomNameToShip(sti(npchar.nation));
        pchar.GenQuest.Marginpassenger.q2Name = GenerateRandomName(sti(npchar.nation), "man");
        pchar.GenQuest.Marginpassenger.Chance = 0.8 + frand(0.4);
        SelectMarginpassengerParameter();
        log_testinfo(pchar.GenQuest.Marginpassenger.Targetcity);
        dialog.text = "Не трать порох понапрасну, кэп, он тебе пригодится. Теперь слушай: через " + FindRussianDaysString(sti(pchar.GenQuest.Marginpassenger.Days)) + " из нашей колонии выйдет " + GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.Marginpassenger.ShipType), "Name"))) + " под названием '" + pchar.GenQuest.Marginpassenger.ShipName + "' и направится в сторону " + XI_ConvertString("Colony" + pchar.GenQuest.Marginpassenger.Targetcity + "Gen") + ". На борту будет пассажир - " + pchar.GenQuest.Marginpassenger.Text + ", зовут - " + pchar.GenQuest.Marginpassenger.q1Name + "\nКапитан " + GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.Marginpassenger.ShipType), "Name") + "Gen")) + " трусоват, что поделать - торгаш... так что тебе возможно даже и драться с ним не придётся. Припугни его хорошенько - он сам и отдаст тебе своего пассажира, хе-хе... Ну а дальше уже останется только получить выкуп\nКак ты понимаешь, " + pchar.GenQuest.Marginpassenger.Text1 + ", деньги ты, наверное, получишь, но после этого власти тебя затравят до смерти. Лучше отвези свою добычу в " + XI_ConvertString("Colony" + pchar.GenQuest.Marginpassenger.Targetcity) + ". Там найдёшь человека по имени " + pchar.GenQuest.Marginpassenger.q2Name + "\n" + pchar.GenQuest.Marginpassenger.Text2 + " и имени твоего не спросит. Ну, а сколько денег запросить - это уже тебе решать, сам думай, и не забывай поговорку - большая ложка рот дерёт... Но " + sti(pchar.GenQuest.Marginpassenger.Dublon) * 4 + " дублонов можешь требовать смело. Всё запомнил?";
        link.l1 = "Да. Сейчас отправлюсь на корабль и запишу, чтобы не забыть.";
        link.l1.go = "passenger_5";
        break;

    case "passenger_5":
        dialog.text = "Точно! Очень правильное решение. Ладно, кэп, удачи тебе в этом несложном деле. Да, чуть не забыл: " + GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.Marginpassenger.ShipType), "Name"))) + " будет отправляться не из порта, а из одной из бухт неподалёку, какой - не знаю. Так что смотри в оба. Бывай, и спасибо за золото!";
        link.l1 = "Пожалуйста. Надеюсь, ты не спустишь его за один вечер в кабаке...";
        link.l1.go = "exit_quest";
        npchar.lifeday = 0;
        ReOpenQuestHeader("Marginpassenger");
        AddQuestRecord("Marginpassenger", "1");
        AddQuestUserData("Marginpassenger", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.Marginpassenger.City));
        AddQuestUserData("Marginpassenger", "sTargetCity", XI_ConvertString("Colony" + pchar.GenQuest.Marginpassenger.Targetcity));
        AddQuestUserData("Marginpassenger", "sName", pchar.GenQuest.Marginpassenger.Name);
        AddQuestUserData("Marginpassenger", "sName1", pchar.GenQuest.Marginpassenger.q1Name);
        AddQuestUserData("Marginpassenger", "sName2", pchar.GenQuest.Marginpassenger.q2Name);
        AddQuestUserData("Marginpassenger", "sDay", FindRussianDaysString(sti(pchar.GenQuest.Marginpassenger.Days)));
        AddQuestUserData("Marginpassenger", "sShipType", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.Marginpassenger.ShipType), "Name") + "Voc")));
        AddQuestUserData("Marginpassenger", "sShipName", pchar.GenQuest.Marginpassenger.ShipName);
        AddQuestUserData("Marginpassenger", "sText", pchar.GenQuest.Marginpassenger.Text1);
        pchar.GenQuest.Marginpassenger = "begin";
        SetFunctionTimerCondition("Marginpassenger_InWorld", 0, 0, sti(pchar.GenQuest.Marginpassenger.Days), false);
        break;

    //замечание по обнаженному оружию от персонажей типа citizen
    case "CitizenNotBlade":
        dialog.text = NPCharSexPhrase(NPChar, "Послушайте, я, как гражданин этого города, прошу вас не ходить у нас с обнажённым клинком.", "Знаете, я, как гражданка этого города, прошу вас не ходить у нас с обнажённым клинком.");
        link.l1 = LinkRandPhrase("Хорошо.", "Ладно.", "Как скажете...");
        link.l1.go = "exit";
        break;

    case "question":
        dialog.text = LinkRandPhrase("Тогда не тяни кота за хвост. Выкладывай!", "Ох, ну хорошо. Что ты хочешь?", "Вопросы задавать будем? Ладно, моряк, слушаю.");
        link.l1 = LinkRandPhrase("Не расскажешь последние новости вашего города?", "Расскажи, что интересного в последнее время произошло?", "Что интересного творится на архипелаге, не в курсе?");
        link.l1.go = "rumours_marginal";
        break;

    case "exit_quest":
        DialogExit();
        LAi_CharacterDisableDialog(npchar);
        break;

    case "Exit":
        NextDiag.CurrentNode = NextDiag.TempNode;
        DialogExit();
        break;
    }
}

void SelectMarginpassengerParameter()
{
    if (drand(1) == 0)
    {
        pchar.GenQuest.Marginpassenger.q1Name = GenerateRandomName(sti(pchar.GenQuest.Marginpassenger.Nation), "woman");
        pchar.GenQuest.Marginpassenger.model = "women_" + (rand(5) + 11);
        pchar.GenQuest.Marginpassenger.sex = "woman";
        pchar.GenQuest.Marginpassenger.ani = "towngirl";
        pchar.GenQuest.Marginpassenger.Text2 = "Он хочет на ней жениться, без колебаний выложит за девушку кругленькую сумму";
        switch (drand(4))
        {
        case 0:
            pchar.GenQuest.Marginpassenger.Text = "дочка купца, хозяина магазина";
            pchar.GenQuest.Marginpassenger.Text1 = "у её отца, хозяина магазина";
            pchar.GenQuest.Marginpassenger.loc = pchar.GenQuest.Marginpassenger.City + "_store";
            break;
        case 1:
            pchar.GenQuest.Marginpassenger.Text = "дочка владельца верфи";
            pchar.GenQuest.Marginpassenger.Text1 = "у её отца, владельца верфи";
            pchar.GenQuest.Marginpassenger.loc = pchar.GenQuest.Marginpassenger.City + "_shipyard";
            break;
        case 2:
            pchar.GenQuest.Marginpassenger.Text = "дочка трактирщика";
            pchar.GenQuest.Marginpassenger.Text1 = "у её отца, трактирщика";
            pchar.GenQuest.Marginpassenger.loc = pchar.GenQuest.Marginpassenger.City + "_tavern";
            break;
        case 3:
            pchar.GenQuest.Marginpassenger.Text = "дочка ростовщика";
            pchar.GenQuest.Marginpassenger.Text1 = "у её отца, ростовщика";
            pchar.GenQuest.Marginpassenger.loc = pchar.GenQuest.Marginpassenger.City + "_bank";
            break;
        case 4:
            pchar.GenQuest.Marginpassenger.Text = "дочка начальника портового управления";
            pchar.GenQuest.Marginpassenger.Text1 = "у её отца, начальника портового управления";
            pchar.GenQuest.Marginpassenger.loc = pchar.GenQuest.Marginpassenger.City + "_portoffice";
            break;
        }
    }
    else
    {
        pchar.GenQuest.Marginpassenger.q1Name = GenerateRandomName(sti(pchar.GenQuest.Marginpassenger.Nation), "man");
        pchar.GenQuest.Marginpassenger.model = "citiz_" + (rand(9) + 11);
        pchar.GenQuest.Marginpassenger.sex = "man";
        pchar.GenQuest.Marginpassenger.ani = "man";
        pchar.GenQuest.Marginpassenger.Text2 = "Он давно хочет втереться в доверие к этой семье, без колебаний выложит за пленника кругленькую сумму";
        switch (drand(4))
        {
        case 0:
            pchar.GenQuest.Marginpassenger.Text = "близкий родственник купца, хозяина магазина";
            pchar.GenQuest.Marginpassenger.Text1 = "у его родственника, хозяина магазина";
            pchar.GenQuest.Marginpassenger.loc = pchar.GenQuest.Marginpassenger.City + "_store";
            break;
        case 1:
            pchar.GenQuest.Marginpassenger.Text = "близкий родственник владельца верфи";
            pchar.GenQuest.Marginpassenger.Text1 = "у его родственника, владельца верфи";
            pchar.GenQuest.Marginpassenger.loc = pchar.GenQuest.Marginpassenger.City + "_shipyard";
            break;
        case 2:
            pchar.GenQuest.Marginpassenger.Text = "близкий родственник трактирщика";
            pchar.GenQuest.Marginpassenger.Text1 = "у его родственника, трактирщика";
            pchar.GenQuest.Marginpassenger.loc = pchar.GenQuest.Marginpassenger.City + "_tavern";
            break;
        case 3:
            pchar.GenQuest.Marginpassenger.Text = "близкий родственник ростовщика";
            pchar.GenQuest.Marginpassenger.Text1 = "у его родственника, ростовщика";
            pchar.GenQuest.Marginpassenger.loc = pchar.GenQuest.Marginpassenger.City + "_bank";
            break;
        case 4:
            pchar.GenQuest.Marginpassenger.Text = "близкий родственник начальника портового управления";
            pchar.GenQuest.Marginpassenger.Text1 = "у его родственника, начальника портового управления";
            pchar.GenQuest.Marginpassenger.loc = pchar.GenQuest.Marginpassenger.City + "_portoffice";
            break;
        }
    }
    if (sti(pchar.rank) < 4)
        pchar.GenQuest.Marginpassenger.ShipType = SHIP_BARQUE;
    if (sti(pchar.rank) >= 4 && sti(pchar.rank) < 7)
        pchar.GenQuest.Marginpassenger.ShipType = SHIP_BARKENTINE + rand(makeint(SHIP_FLEUT - SHIP_BARKENTINE));
    if (sti(pchar.rank) >= 7 && sti(pchar.rank) < 10)
        pchar.GenQuest.Marginpassenger.ShipType = SHIP_CARAVEL + rand(makeint(SHIP_CARACCA - SHIP_CARAVEL));
    if (sti(pchar.rank) >= 10 && sti(pchar.rank) < 16)
        pchar.GenQuest.Marginpassenger.ShipType = SHIP_GALEON_L;
    if (sti(pchar.rank) >= 16)
        pchar.GenQuest.Marginpassenger.ShipType = SHIP_NAVIO + rand(makeint(SHIP_GALEON_H - SHIP_NAVIO));
}
