// boal 25/04/04 общий диалог мэры
#include "DIALOGS\russian\Rumours\Common_rumours.c" //homo 25/06/06
void ProcessDialogEvent()
{
    ref NPChar, sld;
    aref aData;
    aref Link, NextDiag, arName;

    DeleteAttribute(&Dialog, "Links");

    ref FortChref; // фортовый командер
    ref arItem;

    makeref(NPChar, CharacterRef);
    makearef(Link, Dialog.Links);
    makearef(NextDiag, NPChar.Dialog);

    // вызов диалога по городам -->
    NPChar.FileDialog2 = "DIALOGS\" + LanguageGetLanguage() + "\Mayor\" + NPChar.City + "_Mayor.c ";
                         if (LoadSegment(NPChar.FileDialog2))
    {
        ProcessCommonDialog(NPChar, Link, NextDiag);
        UnloadSegment(NPChar.FileDialog2);
    }
    // вызов диалога по городам <--
    ProcessCommonDialogRumors(NPChar, Link, NextDiag); //homo 25/06/06

    FortChref = GetFortCommander(NPChar.City); // будет или фортовик или сам губернатор

    ref offref;
    int i, cn, iRank, iDay;
    int qty;
    string attrLoc, QuestName, sTemp;
    bool bOk;

    if (CheckNPCQuestDate(npchar, "Card_date"))
    {
        SetNPCQuestDate(npchar, "Card_date");
        npchar.money = 5000 + (rand(10) + 1) * makeint(100 * sti(PChar.rank) * (10.0 / MOD_SKILL_ENEMY_RATE));
    }
    // генератор ИДХ по кейсу -->
    attrLoc = Dialog.CurrentNode;
    if (findsubstr(attrLoc, "GetPrisonerIdx_", 0) != -1)
    {
        i = findsubstr(attrLoc, "_", 0);
        pchar.GenQuest.GetPrisonerIdx = strcut(attrLoc, i + 1, strlen(attrLoc) - 1); // индех в конце
        Dialog.CurrentNode = "sell_prisoner_2";
    }
    // генератор ИДХ по кейсу <--

    switch (Dialog.CurrentNode)
    {
    case "Exit":
        NextDiag.CurrentNode = NextDiag.TempNode;
        DialogExit();
        AddDialogExitQuest("MainHeroFightModeOff");
        break;

    case "fight":
        Pchar.quest.ArestInResidenceEnd.win_condition.l1 = "ExitFromLocation";
        Pchar.quest.ArestInResidenceEnd.win_condition.l1.location = Pchar.location;
        Pchar.quest.ArestInResidenceEnd.win_condition = "ArestInResidenceEnd";
        Pchar.quest.ArestInResidenceEnd.ResidenceLocation = Pchar.location;
        DialogExit();
        NextDiag.CurrentNode = NextDiag.TempNode;

        LAi_LockFightMode(Pchar, true); // ножками путь убегает
        LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
        LAi_group_Attack(NPChar, Pchar);                               // не работает на бессмертного мера :(
        i = GetCharIDXByParam("CityType", "location", Pchar.location); // фантом солдат
        if (i != -1)
        {
            LAi_group_Attack(&Characters[i], Pchar);
        }
        break;

    case "First time":
        NextDiag.TempNode = "First time";
        if (LAi_grp_playeralarm > 0)
        {
            dialog.text = NPCharRepPhrase(pchar,
                                          LinkRandPhrase("Вы посмели явиться к губернатору?! Смелый шаг...", "Как эти бездельники допустили, чтобы ко мне ворвался враг?! Уму непостижимо...", "Да уж, моя охрана немногого стоит, раз " + GetSexPhrase("какой-то бездельник", "какая-то бездельница") + " бегает в моей резиденции..."),
                                          LinkRandPhrase("Что тебе нужно, " + GetSexPhrase("негодяй", "мерзавка") + "?! Мои солдаты уже взяли твой след, далеко тебе не уйти" + GetSexPhrase(", грязный пират", "") + "!", "Грязн" + GetSexPhrase("ый", "ая") + " убийца, вон из моей резиденции! Стража!!", "Я не боюсь тебя, мерзав" + GetSexPhrase("ец", "ка") + "! Скоро тебя повесят в форте, далеко тебе не уйти..."));
            link.l1 = NPCharRepPhrase(pchar,
                                      RandPhraseSimple("Солдатня мало чего стоит...", "Им меня ни за что не поймать."),
                                      RandPhraseSimple("Заткни свою пасть, " + GetWorkTypeOfMan(npchar, "") + ", а не то вырву твой поганый язык!", "Вот что я тебе скажу, приятель: сиди тихо, и будешь жить..."));
            link.l1.go = "fight";
            break;
        }
        if (sti(NPChar.nation) == PIRATE)
        {
            if (CheckAttribute(pchar, "GenQuest.CaptainComission") && CheckAttribute(pchar, "GenQuest.CaptainComission.PiratesCity") && NPChar.city == pchar.GenQuest.CaptainComission.PiratesCity)
            {
                dialog.text = "Что тебе нужно?";
                link.l1 = "Нужно поговорить с вами об одном деле.";
                link.l1.go = "quests";
                break;
            }
            if (CheckAttribute(pchar, "GenQuest.Marginpassenger") && pchar.GenQuest.Marginpassenger == "cabin" && NPChar.city == "LeFransua")
            {
                dialog.text = "Что тебе нужно?";
                link.l1 = "Нужно поговорить с вами об одном деле.";
                link.l1.go = "quests";
                break;
            }
            dialog.text = "Нам не о чем говорить, я занят.";
            link.l1 = "Ну и ладно.";
            link.l1.go = "Exit";
        }
        if (sti(NPChar.nation) != PIRATE && ChangeCharacterHunterScore(Pchar, NationShortName(sti(NPChar.nation)) + "hunter", 0) > 10)
        {
            iTotalTemp = ChangeCharacterHunterScore(Pchar, NationShortName(sti(NPChar.nation)) + "hunter", 0);
            dialog.text = "О! Кто пришёл! Это же сам" + GetSexPhrase("", "а") + " " + GetFullName(pchar) + ". Мы как раз недавно высылали охотников за головами, чтобы они привели вас сюда. И знаете, это уже встало нам в кругленькую сумму.";
            if (sti(pchar.Money) >= iTotalTemp * 6000)
            {
                link.l1 = "Я как раз хочу уладить наши разногласия.";
                link.l1.go = "arestFree_1";
            }
            link.l2 = "Э... пожалуй, мне пора.";
            link.l2.go = "arest_1";
            break;
        }
        if (GetNationRelation2MainCharacter(sti(NPChar.nation)) == RELATION_ENEMY && sti(NPChar.nation) != PIRATE)
        {
            dialog.text = "Враг в резиденции! Тревога!!";
            link.l1 = "А-ать, дьявол!";
            link.l1.go = "fight";
            break;
        }
        //--> Jason, Бремя гасконца
        if (CheckAttribute(pchar, "questTemp.Sharlie.Citcount") && npchar.city == "FortFrance")
        {
            dialog.text = "Что вам угодно, месье?";
            link.l1 = "Здравствуйте, Ваша Светлость. Я только что прибыл из Парижа. Я разыскиваю Мишеля де Монпе. Не могли бы вы посодействовать в моих поисках?";
            link.l1.go = "Sharlie";
            npchar.quest.meeting = "1"; // patch-6
            break;
        }

        if (CheckAttribute(pchar, "questTemp.Sharlie.Lock") && npchar.city == "FortFrance")
        {
            if (CheckAttribute(pchar, "questTemp.Sharlie.Pardon"))
            {
                dialog.text = "А, это вы, месье де Мор... Видимо, я должен извиниться за то, что так круто с вами обошёлся. Но поймите и меня тоже, я забочусь о нашей национальной безопасности...";
                link.l1 = "Конечно, Ваша Светлость. В конце концов, всё прояснилось.";
                link.l1.go = "Sharlie_2";
            }
            else
            {
                dialog.text = "Вы что-то хотели, Шарль?";
                link.l1 = "У меня к вам один вопрос...";
                link.l1.go = "quests";
                link.l2 = "Да нет, ничего.";
                link.l2.go = "exit";
            }
            npchar.quest.meeting = "1"; // patch-6
            break;
        }
        //<-- Бремя гасконца
        // Jason НСО
        if (CheckAttribute(pchar, "questTemp.Patria.Governor") && npchar.city == "Marigo" && pchar.model == "Sharle_6")
        {
            dialog.text = "Рад вас видеть, господин губернатор. Как ваши дела? На Синт-Маартене всё под контролем.";
            link.l1 = "Я приехал ненадолго. Рад, что у вас всё в порядке.";
            link.l1.go = "exit";
            link.l2 = "Нужно поговорить с вами об одном деле.";
            link.l2.go = "quests"; //(перессылка в файл города)
            link.l8 = "Может, вы хотите немного передохнуть от важных дел? Могу предложить провести время за игрой.";
            link.l8.go = "Play_Game";
            break;
        }
        if (CheckAttribute(pchar, "questTemp.Patria.GenGovernor") && npchar.nation == FRANCE && pchar.model == "Sharle_6")
        {
            dialog.text = "Рад вас видеть, господин генерал-губернатор! В моей колонии всё просто замечательно! Отдохните, я сейчас прикажу накрыть на стол...";
            link.l1 = "Не надо. Я приехал ненадолго. Рад, что у вас всё в порядке.";
            link.l1.go = "exit";
            link.l2 = "Нужно поговорить с вами об одном деле.";
            link.l2.go = "quests"; //(перессылка в файл города)
            link.l8 = "Может, вы хотите немного передохнуть от важных дел? Могу предложить провести время за игрой.";
            link.l8.go = "Play_Game";
            break;
        }
        if (CheckAttribute(pchar, "questTemp.Patria.GenGovernor") && pchar.model == "Sharle_6")
        {
            dialog.text = "О, какие у нас гости! Месье генерал-губернатор французских колоний! Чего изволите, ваша светлость? Присаживайтесь, я прикажу слугам принести вина и фруктов.";
            link.l1 = "Не извольте беспокоиться, это визит вежливости, я не мог, посетив вашу колонию, не зайти к вам.";
            link.l1.go = "exit";
            link.l2 = "Нужно поговорить с вами об одном деле.";
            link.l2.go = "quests"; //(перессылка в файл города)
            link.l8 = "Может, вы хотите немного передохнуть от важных дел? Могу предложить провести время за игрой.";
            link.l8.go = "Play_Game";
            break;
        }
        //--> Jason, Португалец
        if (CheckAttribute(pchar, "questTemp.Portugal") && pchar.questTemp.Portugal == "MartiniqueGovernor" && npchar.city == "FortFrance")
        {
            dialog.text = "А, вот и вы, капитан! Не слишком то вы спешили, должен заметить.";
            link.l1 = "Я прибыл при первой же возможности, ваше превосходительство. Мне передали что-то о неотложном деле, я могу оказать вам услугу?";
            link.l1.go = "Portugal";
            break;
        }
        //<-- Португалец

        if (npchar.quest.meeting == "0")
        {
            dialog.text = "Я слышал, что вы очень настойчиво просили аудиенции. Меня зовут " + GetFullName(npchar) +
                          ". Я губернатор города " + GetCityName(NPChar.city) + " подданства " + NationKingsName(npchar) +
                          ". А теперь соблаговолите сообщить цель вашего визита, " + GetAddress_Form(NPChar) + ".";
            link.l1 = "Мое имя " + GetFullName(pchar) + ".";
            link.l1.go = "node_1";
            npchar.quest.meeting = "1";
        }
        else
        {
            //ОСАДЫ homo
            if (CheckAttribute(Colonies[FindColony(npchar.City)], "Siege"))
            {

                makearef(aData, NullCharacter.Siege);

                if (CheckAttribute(aData, "HelpColony") && sti(aData.HelpColony) == true)
                {
                    dialog.text = "Мы вроде всё уже обсудили, не так ли?";
                    link.l1 = "Всё верно - не стану вас более задерживать.";
                    link.l1.go = "exit";
                }
                else
                {
                    dialog.text = "Должен вас огорчить, но в данный момент у меня нет времени, чтобы принять вас. Как вы, наверное, уже знаете, на нашу колонию напали " + NationNamePeople(sti(aData.nation)) + ". И мне необходимо организовать оборону города.";
                    link.l1 = "Так я как раз хотел" + GetSexPhrase("", "а") + " предложить свою помощь в обороне форта.";
                    link.l1.go = "siege_task";
                    link.l2 = "Тогда не стану вас более задерживать.";
                    link.l2.go = "exit";
                }
            }
            else
            { //->
                makearef(aData, NullCharacter.Siege);
                if (CheckAttribute(aData, "PlayerHelpMayor") && sti(aData.PlayerHelpMayor) == true && CheckAttribute(aData, "HelpColony") && sti(aData.HelpColony) == true)
                {
                    AddMoneyToCharacter(Pchar, (sti(aData.iSquadronPower) * 1500));
                    ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 20);
                    ChangeCharacterComplexReputation(pchar, "nobility", 10);
                    AddCharacterExpToSkill(GetMainCharacter(), "Leadership", 80);
                    AddCharacterExpToSkill(GetMainCharacter(), "Sailing", 100);
                    AddCharacterExpToSkill(GetMainCharacter(), "Accuracy", 100);
                    AddCharacterExpToSkill(GetMainCharacter(), "Cannons", 100);
                    //--> слухи
                    SiegeRumour("Поговаривают, что вы помогли нам отбиться от " + NationNameSK(sti(aData.nation)) + "ой эскадры - и отстоять нашу колонию! Мы так благодарны вам, " + GetAddress_Form(NPChar) + ".", aData.Colony, sti(aData.conation), -1, 15, 3);
                    //<-- слухи
                    DeleteAttribute(aData, "PlayerHelpMayor");
                    DeleteAttribute(aData, "HelpColony");
                    dialog.text = "Ах, это вы, " + GetAddress_Form(NPChar) + " " + GetFullName(pchar) + ", рад вас видеть. Добрые вести для нашей колонии - мы отбились от " + NationNameSK(sti(aData.nation)) + "их захватчиков. В этом есть и ваша заслуга, вот ваша награда " + (sti(aData.iSquadronPower) * 1500) + " песо. Извольте получить.";
                    link.l1 = "Спасибо, " + GetAddress_FormToNPC(NPChar) + ", приятно иметь с вами дело!";
                    link.l1.go = "exit";
                }
                else
                {
                    //--> дача квеста найти кольцо в борделе
                    if (rand(4) == 4 && pchar.questTemp.different == "free" && GetNpcQuestPastDayWOInit(npchar, "questTakeRing") > 365 && sti(pchar.questTemp.HorseQty) > 10)
                    { // Addon-2016 Jason
                        if (npchar.city == "Bridgetown" || npchar.city == "Charles" || npchar.city == "FortFrance" || npchar.city == "Marigo" || npchar.city == "Panama" || npchar.city == "PortRoyal" || npchar.city == "SantoDomingo" || npchar.city == "Tortuga")
                        {
                            dialog.text = "Послушайте, у меня есть к вам дело, хм.. несколько необычного порядка.";
                            link.l1 = "Слушаю вас внимательно.";
                            link.l1.go = "TakeRing_1";
                            SaveCurrentNpcQuestDateParam(npchar, "questTakeRing");
                            break;
                        }
                    }
                    //<-- дача квеста найти кольцо в борделе
                    dialog.text = RandPhraseSimple("А, это опять вы? По какому вопросу на этот раз?", "Опять отрываете меня от дел управления городом? Что вам угодно, " + GetAddress_Form(NPChar) + "?");
                    if (npchar.city != "Panama") // Addon-2016 Jason
                    {
                        link.l1 = "Я хочу поговорить о работе на благо короны " + NationNameGenitive(sti(NPChar.nation)) + ".";
                        link.l1.go = "work";
                    }
                    // Warship Генер "Пираты на необитайке" - сдаем пиратов властям
                    if (CheckAttribute(PChar, "Quest.PiratesOnUninhabited_OnShore") || CheckAttribute(PChar, "Quest.PiratesOnUninhabited_ShipSink"))
                    {
                        link.l11 = XI_ConvertString(PChar.GenQuest.PiratesOnUninhabited.StartShore + "Dat") + " я встретил" + GetSexPhrase("", "а") + " пиратов. Все " + PChar.GenQuest.PiratesOnUninhabited.PiratesCount + " человек сейчас у меня на борту. Хочу сдать их властям.";
                        link.l11.go = "PiratesOnUninhabited_1";
                    }

                    link.l2 = "Нужно поговорить с вами об одном деле.";
                    if (CheckAttribute(pchar, "questTemp.ReasonToFast") && !CheckAttribute(pchar, "questTemp.ReasonToFast.SpeakOther") && !CheckAttribute(pchar, "questTemp.ReasonToFast.cantSpeakOther") && (pchar.questTemp.ReasonToFast.city == NPChar.city))
                    {
                        link.l2.go = "ReasonToFast_Mayor1";
                    }
                    else
                    {
                        link.l2.go = "quests"; //(перессылка в файл города)
                    }
                    if (CheckAttribute(pchar, "GenQuest.CaptainComission") && (pchar.GenQuest.CaptainComission.variant == "A2") && (pchar.GenQuest.CaptainComission.City == NPChar.city))
                    {
                        if (pchar.GenQuest.CaptainComission == "Begin_1" && !CheckAttribute(pchar, "GenQuest.CaptainComission.SpeakMayor"))
                        {
                            link.l12 = "У вас капитаном патрульного " + GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType), "Name") + "Gen")) + " служит некий " + pchar.GenQuest.CaptainComission.Name + ", как я могу с ним повидаться?";
                            link.l12.go = "CapComission_Mayor1";
                        }
                        if (CheckAttribute(pchar, "GenQuest.CaptainComission.PrisonFree"))
                        {
                            link.l12 = "Бывший капитан патрульного " + GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType), "Name") + "Gen")) + " " + pchar.GenQuest.CaptainComission.Name + " согласился открыть свой тайник властям.";
                            link.l12.go = "CapComission_Mayor9";
                        }
                        if (pchar.GenQuest.CaptainComission == "GetGoodsSuccess")
                        {
                            link.l12 = "Бывший капитан патрульного " + GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType), "Name") + "Gen")) + " " + pchar.GenQuest.CaptainComission.Name + " открыл мне свой тайник.";
                            link.l12.go = "CapComission_Mayor13";
                        }
                    }
                    if (CheckAttribute(pchar, "GenQuest.ShipWreck") && pchar.GenQuest.ShipWreck == "SailorsOnShore" && GetQuestPastDayParam("GenQuest.ShipWreck") < 25 && sti(npchar.nation) == sti(pchar.GenQuest.ShipWreck.Nation))
                    {
                        if (!CheckAttribute(pchar, "GenQuest.ShipWreck.SpeakMayor"))
                        {
                            iDay = GetQuestPastDayParam("GenQuest.ShipWreck");
                            if (CheckAttribute(pchar, "GenQuest.ShipWreck.Mutiny"))
                            {
                                link.l13 = UpperFirst(XI_ConvertString(pchar.GenQuest.ShipWreck.Shore + "Dat")) + " я встретил" + GetSexPhrase("", "а") + " капитана " + pchar.GenQuest.ShipWreck.Name + " и его моряков, высаженных на берег пиратом " + pchar.GenQuest.ShipWreck.BadName + ". " +
                                           "К сожалению, перегруз команды на моём судне не позволил взять их на борт. Но я оставил" + GetSexPhrase("", "а") + " им провизию и оружие. Если экспедиционное судно не успеет забрать их в течение " + (30 - iDay) + " дней, то не знаю, удастся ли застать их живыми.";
                                link.l13.go = "ShipWreck1";
                            }
                            else
                            {
                                link.l13 = UpperFirst(XI_ConvertString(pchar.GenQuest.ShipWreck.Shore + "Dat")) + " я встретил" + GetSexPhrase("", "а") + " моряков из потерпевшего крушение судна '" + pchar.GenQuest.ShipWreck.ShipTypeName + "' во главе с их капитаном. " +
                                           "К сожалению, перегруз команды на моём судне не позволили взять их на борт. Но я оставил" + GetSexPhrase("", "а") + " им провизию и оружие. Если экспедиционное судно не успеет забрать их в течение " + (30 - iDay) + " дней, то не знаю, удастся ли застать их живыми.";
                                link.l13.go = "ShipWreck1";
                            }
                        }
                    }
                    if (GetPrisonerQty() > 0)
                    {
                        link.l3 = "Мне нужно сдать пленного капитана властям.";
                        link.l3.go = "sell_prisoner";
                    }
                    if (npchar.Default == npchar.location) // если не в тюрьме
                    {
                        if (CheckAttribute(pchar, "GenQuest.LoanChest.TakeChest") && sti(pchar.GenQuest.LoanChest.TargetIdx) == sti(NPChar.index))
                        {
                            link.l4 = "Мне нужно прояснить с вами ряд финансовых вопросов.";
                            link.l4.go = "LoanForAll"; //(перессылка в кредитный генератор)
                        }
                    }
                    //-->> сдача найденного в борделе кольца
                    if (CheckCharacterItem(pchar, "MayorsRing"))
                    {
                        if (pchar.questTemp.different.TakeMayorsRing == "toBrothel")
                        {
                            link.l5 = "Мне удалось найти ваше кольцо. Вот оно.";
                            link.l5.go = "TakeRing_S1";
                        }
                        else
                        {
                            link.l5 = "Ваше обручальное кольцо у меня. Как оказалось, вы подарили его одной из бордельных девок.";
                            link.l5.go = "TakeRing_S3";
                        }
                    }
                    //<<-- сдача найденного в борделе кольца

                    //--> Jason, генер почтового курьера 2 уровня
                    if (CheckAttribute(PChar, "questTemp.WPU.Postcureer.LevelUp"))
                    {
                        if (pchar.questTemp.WPU.Postcureer.TargetPortmanID == npchar.id)
                        {
                            link.l14 = "Я доставил вам депешу из города " + XI_ConvertString("Colony" + pchar.questTemp.WPU.Postcureer.StartCity + "Gen") + ".";
                            link.l14.go = "Postcureer_LevelUp_ForAll";
                        }
                    }
                    //<-- генер почтового курьера 2 уровня

                    // Warship, 16.05.11. Квест "Правосудие на продажу" -->
                    if (CheckAttribute(PChar, "GenQuest.JusticeOnSale.MayorWait") && CheckAttribute(PChar, "GenQuest.JusticeOnSale.CityId") && NPChar.location == PChar.GenQuest.JusticeOnSale.CityId + "_townhall")
                    {
                        link.l15 = UpperFirst(GetAddress_FormToNPC(NPChar)) + ", я обнаружил банду контрабандистов, чьего главаря недавно поймала стража. Они планируют вызволить его. Их корабль '" + PChar.GenQuest.JusticeOnSale.ShipName + "' стоит " + XI_ConvertString(PChar.GenQuest.JusticeOnSale.ShoreId + "Dat") + ".";
                        link.l15.go = "JusticeOnSale_1";
                    }

                    if (CheckAttribute(PChar, "GenQuest.JusticeOnSale.ShipSink") && CheckAttribute(PChar, "GenQuest.JusticeOnSale.CityId") && NPChar.location == PChar.GenQuest.JusticeOnSale.CityId + "_townhall")
                    {
                        link.l15 = UpperFirst(GetAddress_FormToNPC(NPChar)) + ", банда контрабандистов была уничтожена!";
                        link.l15.go = "JusticeOnSale_7";
                    }
                    // <--Правосудие на продажу
                    //Jason --> Регата
                    if (CheckAttribute(pchar, "questTemp.Regata.ToPortRoyal") && NPChar.location == "Portroyal_townhall")
                    {
                        link.l16 = "Я прибыл для участия в регате. Вот моё приглашение.";
                        link.l16.go = "Regata";
                    }
                    link.l8 = "Может, вы хотите немного передохнуть от важных дел? Могу предложить провести время за игрой.";
                    link.l8.go = "Play_Game";
                    link.l10 = "Прошу простить меня, но меня ждут дела.";
                    link.l10.go = "exit";
                }
            } //<-
        }
        break;

    // Warship Генер "Пираты на необитайке"
    case "PiratesOnUninhabited_1":
        offref = CharacterFromID("PirateOnUninhabited_0");
        qty = makeint(sti(PChar.GenQuest.PiratesOnUninhabited.PiratesCount) * (sti(offref.rank) * (800 + GetCharacterSPECIALSimple(NPChar, SPECIAL_L) * 100) + GetCharacterSkillToOld(offref, "Leadership") * 500 + GetCharacterSkillToOld(PChar, "commerce") * 500) / 20);

        PChar.GenQuest.PiratesOnUninhabited.MoneyForPirates = qty;

        dialog.text = "Очень похвальное решение. Так совместными усилиями и нужно бороться с этой напастью. Я немедленно отправлю за ними конвой. Будьте уверены, что не далее, чем через неделю они будут болтаться на виселице. Да, и Вам полагается вознаграждение " + FindRussianMoneyString(qty) + ".";
        link.l1 = "Спасибо, ваша светлость. Всегда рад" + GetSexPhrase("", "а") + " служить. ";
        link.l1.go = "PiratesOnUninhabited_2";
        link.l2 = "Нет. Не пойдет.";
        link.l2.go = "exit";
        break;

    case "PiratesOnUninhabited_2":
        offref = CharacterFromID("PirateOnUninhabited_0");

        AddMoneyToCharacter(PChar, sti(PChar.GenQuest.PiratesOnUninhabited.MoneyForPirates));

        RemovePassenger(PChar, offref);
        RemoveCharacterCrew(PChar, sti(PChar.GenQuest.PiratesOnUninhabited.PiratesCount) - 1);

        sTemp = "PiratesOnUninhabited" + PChar.GenQuest.PiratesOnUninhabited.StartShore;
        AddQuestRecordEx(sTemp, "PiratesOnUninhabited", "12");
        AddQuestUserData(sTemp, "sSex", GetSexPhrase("", "а"));
        AddQuestUserData(sTemp, "mayorName", GetFullName(NPChar));
        CloseQuestHeader(sTemp);

        PChar.Quest.PiratesOnUninhabited_OnShore.over = "yes";
        PChar.Quest.PiratesOnUninhabited_OnMayak.over = "yes";

        if (CheckAttribute(PChar, "Quest.PiratesOnUninhabited_ShipSink"))
        {
            PChar.Quest.PiratesOnUninhabited_ShipSink.over = "yes";

            PChar.GenQuest.PiratesOnUninhabited.ClearShip = true;
            Map_ReleaseQuestEncounter("PiratesOnUninhabited_BadPirate"); // Убираем с глобалки
        }

        DeleteAttribute(PChar, "GenQuest.PiratesOnUninhabited");

        DialogExit();
        break;

    // ------------------------- Повод для спешки -----------------------------
    case "ReasonToFast_Mayor1":
        dialog.text = "Я внимательно слушаю вас, капитан.";
        link.l1 = "Я хочу доложить о преступном сговоре офицера вашего гарнизона и пиратов... (излагает обстоятельства дела)";
        if (sti(pchar.reputation.nobility) < 41)
        {
            link.l1.go = "ReasonToFast_BMayor";
        }
        else
        {
            link.l1.go = "ReasonToFast_GMayor";
        }
        pchar.questTemp.ReasonToFast.SpeakOther = true;
        break;

    case "ReasonToFast_GMayor":
        if (pchar.questTemp.ReasonToFast == "PatrolSuccess_1")
        {
            // вилка_А
            dialog.text = "Благодарю Вас, судар" + GetSexPhrase("ь", "ыня") + "! Я немедленно отдам приказ задержать негодяя\nОднако вы изрядно потратились, а муниципальная казна, увы, пуста...";
            link.l1 = "Ваша светлость! Я делал" + GetSexPhrase("", "а") + " это не ради денег...";
            link.l1.go = "ReasonToFast_GMayor_11";
            if (pchar.questTemp.ReasonToFast.chain == "A0")
                ReasonToFast_RemoveVictim();
            if (pchar.questTemp.ReasonToFast.chain == "A1")
                pchar.quest.ReasonToFast_ClearLakey.over = "yes";
        }
        if (pchar.questTemp.ReasonToFast == "PatrolSuccess_2")
        {
            // получена карта
            dialog.text = "Благодарю вас, судар" + GetSexPhrase("ь", "ыня") + "! Я немедленно отдам приказ задержать негодяя\nТолько подумайте! Мы хотели наградить его именным оружием за безупречную службу. Как хорошо, что всё прояснилось, и не вышло такого конфуза!";
            link.l2 = "Всегда рад послужить справедливости...";
            link.l2.go = "ReasonToFast_GMayor_21";
        }
        if (pchar.questTemp.ReasonToFast == "PatrolDied")
        {
            // патруль перебит
            dialog.text = "Судар" + GetSexPhrase("ь", "ыня") + "! Мы давно подозревали, что этот офицер и окружавший его сброд нечисты на руку, но мне кажется, что вы поступили опрометчиво, разделавшись с ними без свидетелей.";
            link.l3 = "Ваша светлость! Но я вынужден" + GetSexPhrase("", "а") + " был защищать свою жизнь...";
            link.l3.go = "ReasonToFast_GMayor_31";
            pchar.questTemp.ReasonToFast.speakAfterPatrolDied = true;
            pchar.quest.ReasonToFast_SpeakMayor.over = "yes";
        }
        break;

    case "ReasonToFast_BMayor":
        if (pchar.questTemp.ReasonToFast == "PatrolSuccess_1")
        {
            dialog.text = "Капитан, вы хоть понимаете, во что вляпались?!! Мы больше месяца пытались организовать эту ловушку! А вы ради развлечения сорвали встречу нашего патруля с посыльным " + GetName(NAMETYPE_MAIN, pchar.questTemp.ReasonToFast.p3, NAME_GEN) + " и ещё пришли ко мне этим похвастаться! Может, вы теперь расскажете, каким образом я должен обосновать казённые затраты для организации этой операции?!!";
            link.l1 = "Ваша Светлость! Вы отказываетесь видеть суть происходящего...";
            link.l1.go = "ReasonToFast_BMayor_1";
            pchar.questTemp.ReasonToFast = "speakSuccess_chain_A";
            if (pchar.questTemp.ReasonToFast.chain == "A0")
                ReasonToFast_RemoveVictim();
            if (pchar.questTemp.ReasonToFast.chain == "A1")
                pchar.quest.ReasonToFast_ClearLakey.over = "yes";
        }
        if (pchar.questTemp.ReasonToFast == "PatrolSuccess_2")
        {
            // получена карта
            dialog.text = "Дайте-ка взглянуть на эту карту...\nВы надо мной издеваетесь? Этот затёртый клочок пергамента – доказательство?";
            link.l2 = "Ваша Светлость! Вы отказываетесь видеть суть происходящего...";
            link.l2.go = "ReasonToFast_BMayor_1";
            TakeItemFromCharacter(pchar, "mapQuest");
            pchar.questTemp.ReasonToFast = "speakSuccess_chain_B";
        }
        if (pchar.questTemp.ReasonToFast == "PatrolDied")
        {
            // патруль перебит
            dialog.text = "Оригинальное оправдание гибели целого патрульного отряда. Ну что ж, по крайней мере, придя сюда, вы избавили нас от необходимости искать убийцу.";
            link.l3 = "Ваша Светлость! Вы отказываетесь видеть суть происходящего...";
            link.l3.go = "ReasonToFast_BMayor_1";
            pchar.questTemp.ReasonToFast = "speakSuccess_chain_A";
            pchar.quest.ReasonToFast_SpeakMayor.over = "yes";
        }
        break;

    case "ReasonToFast_GMayor_11":
        dialog.text = "Тем не менее, я хочу, чтобы ваши труды были вознаграждены. Вот, возьмите карту, найденную в вещах недавно вздёрнутого морского разбойника. Возможно, при содействии Господа, вы действительно обнаружите сокровища, хотя это весьма сомнительно...";
        link.l1 = "Спасибо, вы очень щедры!";
        link.l1.go = "exit";
        AddQuestRecord("ReasonToFast", "15");
        ChangeCharacterComplexReputation(pchar, "nobility", 1);
        GiveItem2Character(pchar, "mapQuest");
        arItem = ItemsFromID("mapQuest");
        ReasonToFast_GenerateTreasureMap(arItem);
        pchar.questTemp.ReasonToFast.state = "chain_A"; // вилка_А, наводки не генерим
        pchar.questTemp.ReasonToFast = "GetMap";
        ReasonToFast_SetHunterCoastal();
        break;

    case "ReasonToFast_GMayor_21":
        dialog.text = "Похвальное рвение. Возьмите этот клинок в награду. Это меньшее, чем я могу вас одарить! Да... и оставьте эту карту себе. Уверен - по архипелагу ходит множество подобных фальшивок.";
        link.l1 = "Спасибо, вы очень щедры!";
        link.l1.go = "exit";
        AddQuestRecord("ReasonToFast", "14");
        ChangeCharacterComplexReputation(pchar, "nobility", 1);
        GiveItem2Character(pchar, pchar.questTemp.ReasonToFast.p6);
        pchar.questTemp.ReasonToFast.state = "chain_B"; // была получена карта
        pchar.questTemp.ReasonToFast = "GetMap";
        ReasonToFast_SetHunterCoastal();
        break;
    case "ReasonToFast_GMayor_31":
        dialog.text = "Да, возможно, возможно... Что же, я готов считать, что дело разрешилось Божьим судом и по воле Его.";
        link.l1 = "Спасибо, вы очень щедры!";
        link.l1.go = "exit";
        ChangeCharacterComplexReputation(pchar, "nobility", 1);
        AddQuestRecord("ReasonToFast", "16");
        CloseQuestHeader("ReasonToFast");
        DeleteAttribute(pchar, "ReasonToFast");
        break;

    case "ReasonToFast_BMayor_1":
        dialog.text = "Не смейте меня поучать! Для меня очевиден ваш сговор с мошенниками! Караул, взять " + GetSexPhrase("этого 'доброжелателя'", "эту 'доброжелательницу'") + "!";
        link.l1 = "Ну уж нет!";
        link.l1.go = "fight";

        pchar.quest.ReasonToFast_ExitFromTown.win_condition.l1 = "EnterToSea";
        pchar.quest.ReasonToFast_ExitFromTown.function = "ReasonToFast_ExitFromTownFight";
        pchar.questTemp.ReasonToFast.canSpeakSailor = true;
        pchar.TownEscape = true;
        Flag_PIRATE();
        break;

    // ------------------------- Повод для спешки -----------------------------

    // --------------------------Операция 'Галеон'-----------------------------
    case "CapComission_Mayor1":
        dialog.text = "В данный момент это невозможно. Он под арестом и ожидает суда.";
        link.l1 = "Вот как? А в чём его подозревают?";
        link.l1.go = "CapComission_Mayor2";
        break;

    case "CapComission_Mayor2":
        dialog.text = "К сожалению, это не подозрения, а доказанный факт. К нам поступила информация, что под видом патрулирования, он занимался по сути морским разбоем - конфисковывал у проходящих торговых судов товары и тайно сбывал их. А ведь мы считали его одним из лучших капитанов патрульной эскадры.";
        link.l1 = "А кто предоставил доказательства?";
        link.l1.go = "CapComission_Mayor3";
        break;

    case "CapComission_Mayor3":
        dialog.text = "Один из пострадавших прислал донесение, в котором подробно изложен инцидент с указанием даты, названия потерпевшего судна и количества конфискованного товара. " +
                      "Поверьте, там фигурируют весьма солидные цифры. В этот день патрульный " + GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType), "Name"))) + " этого капитана действительно нёс дежурство. Капитан в своём рапорте изложил этот инцидент как стычку с пиратским судном, но ни слова не упомянул о грузе.";
        link.l1 = "А был ли груз вообще?";
        link.l1.go = "CapComission_Mayor4";
        pchar.GenQuest.CaptainComission.SpeakMayor = true;
        break;

    case "CapComission_Mayor4":
        dialog.text = "В этом не может быть никаких сомнений, пострадавший слишком известная персона, чтобы заниматься мелкой клеветой. Как раз сейчас патрульные отряды разыскивают тайник с товаром. Как только он будет найден, капитан " + pchar.GenQuest.CaptainComission.Name + ". " +
                      "предстанет перед судом.\nЕсли вы окажете нам помощь в этом деле, то власти города в моём лице будут вам весьма признательны.";
        link.l1 = "Пожалуй нет. Я слишком плохо знаю окрестные места, чтобы заниматься поисками тайника. Извините, мне пора.";
        link.l1.go = "CapComission_Mayor5";
        link.l2 = "Пожалуй, я готов" + GetSexPhrase("", "а") + " согласиться. Сколько у меня есть времени?";
        link.l2.go = "CapComission_Mayor6";
        break;

    case "CapComission_Mayor5":
        AddQuestRecord("CaptainComission2", "49");
        AddQuestUserData("CaptainComission2", "sShipType", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType), "Name") + "Gen")));
        AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);
        ChangeCharacterComplexReputation(pchar, "nobility", -2);
        pchar.GenQuest.CaptainComission = "MayorTalkBad";
        CaptainComission_GenerateCaptainInPrison();
        DialogExit();
        break;

    case "CapComission_Mayor6":
        dialog.text = "Думаю, дня за два патруль разыщет тайник и без вас, поэтому советую поторопиться.";
        link.l1 = "Хорошо, я берусь за это дело. Только мне понадобится свидание с арестованным капитаном. Можно это как-то организовать?";
        link.l1.go = "CapComission_Mayor7";
        break;

    case "CapComission_Mayor7":
        dialog.text = "Конечно, с этим проблем не будет, я предупрежу коменданта тюрьмы о вашем визите.";
        link.l1 = "Спасибо. Разрешите откланяться.";
        link.l1.go = "CapComission_Mayor8";
        break;

    case "CapComission_Mayor8":
        AddQuestRecord("CaptainComission2", "50");
        AddQuestUserData("CaptainComission2", "sSex", GetSexPhrase("ся", "ась"));
        AddQuestUserData("CaptainComission2", "sSex1", GetSexPhrase("", "а"));
        AddQuestUserData("CaptainComission2", "sShipType", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType), "Name") + "Gen")));
        AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);
        AddQuestUserData("CaptainComission2", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Gen"));
        OfficersReaction("good");
        pchar.GenQuest.CaptainComission.MayorTalkGood = true;
        pchar.GenQuest.CaptainComission = "MayorTalkGood";
        pchar.quest.CaptainComission_TimeIsOver.over = "yes";
        SetFunctionTimerConditionParam("CaptainComission_GetSecretTimeIsOut", 0, 0, 2, MakeInt(24 - GetHour()), false);
        CaptainComission_GenerateCaptainInPrison();
        DialogExit();
        break;

    case "CapComission_Mayor9":
        dialog.text = "Великолепно! И где же нам искать его сокровища?";
        link.l1 = "Пока не знаю. Точного места он мне ещё не указал.";
        link.l1.go = "CapComission_Mayor10";
        break;

    case "CapComission_Mayor10":
        dialog.text = "Хм, какое совпадение! Мне он тоже 'ещё не указал' точного места...";
        link.l1 = "Но я над этим работаю.";
        link.l1.go = "CapComission_Mayor11";
        break;

    case "CapComission_Mayor11":
        dialog.text = "Уже нет\nСтража!.. Отконвоируйте заключённого обратно в камеру\nВы можете быть свободны, " + GetFullName(pchar) + ".";
        link.l1 = "Но, господин губернатор...";
        link.l1.go = "CapComission_Mayor12";
        break;

    case "CapComission_Mayor12":
        sld = CharacterFromID("CapComission_1");
        sld.lifeDay = 0;
        LAi_group_MoveCharacter(sld, "EnemyFight");
        LAi_SetActorType(sld);
        LAi_ActorRunToLocation(sld, "reload", "reload1_back", "none", "", "", "", -1);
        pchar.quest.CapComission_DeletePrisonGroup.win_condition.l1 = "ExitFromLocation";
        pchar.quest.CapComission_DeletePrisonGroup.win_condition.l1.location = pchar.location;
        pchar.quest.CapComission_DeletePrisonGroup.win_condition = "CaptainComission_DeletePrisonGroup";
        ChangeOfficersLoyality("bad_all", 1);
        ChangeCharacterComplexReputation(pchar, "nobility", -4);
        AddQuestRecord("CaptainComission2", "23");
        AddQuestUserData("CaptainComission2", "sSex", GetSexPhrase("", "а"));
        CloseQuestHeader("CaptainComission2");
        DeleteAttribute(pchar, "GenQuest.CaptainComission");
        DialogExit();
        break;

    case "CapComission_Mayor13":
        pchar.quest.CaptainComission_SpeakMayorGoods.over = "yes";
        dialog.text = "Великолепно! И где же нам искать его сокровища?";
        link.l1 = "В " + RandPhraseSimple(RandPhraseSimple("северной", "западной"), RandPhraseSimple("восточной", "южной")) + " оконечности " + XI_ConvertString(pchar.GenQuest.CaptainComission.ConvoyShore + "Gen") + " у подножия скалы есть большая ниша, вход в которую завален камнями. Это и есть тайник.";
        link.l1.go = "CapComission_Mayor14";
        break;

    case "CapComission_Mayor14":
        dialog.text = "Отличная работа! А где сам " + pchar.GenQuest.CaptainComission.Name + " ? Мне доложили, что вы увели его из тюремных подвалов.";
        link.l1 = "К сожалению, он погиб в стычке с контрабандистами.";
        link.l1.go = "CapComission_Mayor15";
        break;

    case "CapComission_Mayor15":
        dialog.text = "Это плохо... Это очень плохо, госпо" + GetSexPhrase("дин", "жа") + " " + GetFullName(pchar) + ". Я хотел казнить его публично, в назидание остальным офицерам. " +
                      "Ну да ладно, виселицы ему всё равно было не избежать\nИтак, поскольку вы формально преступили закон, самовольно освободив заключённого, да ещё и не уберегли его, я не могу не зафиксировать этого в протоколе. Поэтому вознаграждения вы не получите... Но я хотел бы отблагодарить вас лично от себя. Примите мой подарок - весьма полезная для боевого капитана вещь. ";
        link.l1 = "Благодарю вас. Всегда рад" + GetSexPhrase("", "а") + " служить.";
        link.l1.go = "CapComission_Mayor16";
        break;

    case "CapComission_Mayor16":
        AddQuestRecord("CaptainComission2", "30");
        AddQuestUserData("CaptainComission2", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Gen"));
        CloseQuestHeader("CaptainComission2");
        GiveItem2Character(pchar, pchar.GenQuest.CaptainComission.Prize);
        ChangeCharacterComplexReputation(pchar, "nobility", 4);
        ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 10);
        OfficersReaction("good");
        DeleteAttribute(pchar, "GenQuest.CaptainComission.MayorTalkGood");
        DeleteAttribute(pchar, "GenQuest.CaptainComission");
        DialogExit();
        break;
    // --------------------------Операция 'Галеон'-----------------------------

    // -------------------------- Генератор "Кораблекрушенцы" ------------
    case "ShipWreck1":
        if (iDay > 15)
        {
            dialog.text = RandPhraseSimple("Как Вы себе это представляете? До этого места ходу при свежем попутном ветре не менее пятнадцати дней!", "Капитан " + GetFullName(pchar) + ", Ваша безответственность меня поражает! Почему нельзя было сообщить об этом раньше?");
            link.l1 = "Даже не знаю, что Вам на это ответить...";
            link.l1.go = "ShipWreck2";
        }
        else
        {
            dialog.text = "Это хорошая новость! Ведь мы уже не надеялись увидеть " + pchar.GenQuest.ShipWreck.Name + " живым. Я немедленно организую спасательную экспедицию. И возьмите это скромное вознаграждение за Вашу расторопность и участие в их спасении.";
            link.l1 = "Благодарю, ваша светлость. Рад" + GetSexPhrase("", "а") + ", что сумел" + GetSexPhrase("", "а") + " помочь вам и вашим людям. Уверен" + GetSexPhrase("", "а") + ", -  экспедиция успеет вовремя.";
            link.l1.go = "ShipWreck3";
        }
        pchar.GenQuest.ShipWreck.SpeakMayor = true;
        pchar.quest.ShipWreck_MeetInShore.over = "yes";
        break;

    case "ShipWreck2":
        dialog.text = "Что теперь уже можно ответить? Идите и изучите морской устав! Я в любом случае сделаю всё возможное, чтобы спасти этих людей.";
        link.l1 = "Ваша Светлость, но я оставил" + GetSexPhrase("", "а") + " им достаточно провианта. Вы успеете, уверяю вас...";
        link.l1.go = "ShipWreck4";
        break;

    case "ShipWreck3":
        addMoneyToCharacter(pchar, sti(pchar.rank) * 300 + 3000 + rand(3000));
        ChangeCharacterComplexReputation(pchar, "nobility", 2);
        AddQuestRecord("ShipWrecked", "14");
        AddQuestUserData("ShipWrecked", "sSex", GetSexPhrase("", "а"));
        AddQuestUserData("ShipWrecked", "sCity", XI_ConvertString(NPChar.city + "Gen"));
        AddQuestUserData("ShipWrecked", "ShoreName", XI_ConvertString(pchar.GenQuest.ShipWreck.Shore + "Dat"));
        CloseQuestHeader("ShipWrecked");
        DeleteAttribute(pchar, "GenQuest.ShipWreck.SpeakMayor");
        DialogExit();
        AddDialogExitQuest("ShipWreck_RemoveSailorsFromShore");
        break;

    case "ShipWreck4":
        ChangeCharacterComplexReputation(pchar, "nobility", -5);
        AddQuestRecord("ShipWrecked", "13");
        AddQuestUserData("ShipWrecked", "sSex", GetSexPhrase("", "а"));
        AddQuestUserData("ShipWrecked", "sCity", XI_ConvertString(NPChar.city + "Gen"));
        AddQuestUserData("ShipWrecked", "ShoreName", XI_ConvertString(pchar.GenQuest.ShipWreck.Shore + "Dat"));
        CloseQuestHeader("ShipWrecked");
        DeleteAttribute(pchar, "GenQuest.ShipWreck.SpeakMayor");
        DialogExit();
        AddDialogExitQuest("ShipWreck_RemoveSailorsFromShore");
        break;
    // -------------------------- Генератор "Кораблекрушенцы" ------------

    // ---------------------- найти кольцо в борделе ----------------------------
    case "TakeRing_1":
        dialog.text = "Мне известно, что вы, как бы это сказать... " + GetSexPhrase("завсегдатай борделей", "бываете в борделях") + ". Поэтому и решил к вам обратиться за помощью\n" +
                      "Вы знаете, стыдно признаться, но я там был недавно...";
        link.l1 = "Хм, а зачем этого стыдиться? Всё в порядке, влечение и все дела...";
        link.l1.go = "TakeRing_2";
        break;
    case "TakeRing_2":
        dialog.text = "Хе, да я не этого стыжусь. Я там выпил лишнего и потерял обручальное кольцо!..";
        link.l1 = "У-у-у, это серьёзная проблема, сочувствую.";
        link.l1.go = "TakeRing_3";
        break;
    case "TakeRing_3":
        dialog.text = "Хм, сочувствия не требуется. Нужно вернуть кольцо. Разыщите до полуночи, и в случае успеха я буду очень щедр. А в случае неудачи - мне конец.";
        link.l1 = "Понятно... А где конкретно вы могли его потерять? Вы что-нибудь можете сказать более или менее точно?";
        link.l1.go = "TakeRing_4";
        break;
    case "TakeRing_4":
        dialog.text = "Увы, нет. Ничего не помню...";
        link.l1 = "Ясно. Ну что же, будем искать.";
        link.l1.go = "TakeRing_5";
        link.l2 = "Вы знаете, " + GetAddress_FormToNPC(NPChar) + ", я, пожалуй, откажусь от этой работы. Прошу меня извинить...";
        link.l2.go = "TakeRing_6";
        break;
    case "TakeRing_5":
        dialog.text = "Очень хорошо! Но помните - до полуночи вы должны его найти.";
        link.l1 = "Я помню. Ждите меня с новостями.";
        link.l1.go = "exit";
        pchar.questTemp.different = "TakeMayorsRing";
        pchar.questTemp.different.TakeMayorsRing = "toBrothel";
        pchar.questTemp.different.TakeMayorsRing.Id = GetFullName(npchar);
        pchar.questTemp.different.TakeMayorsRing.city = npchar.city;
        pchar.questTemp.different.TakeMayorsRing.price = sti(pchar.rank) * 100 + 1000;
        sld = ItemsFromID("MayorsRing");
        sld.CityName = XI_ConvertString("Colony" + npchar.city + "Gen");
        //ложим кольцо в итем
        if (rand(3) != 2)
        {
            switch (rand(2))
            {
            case 0:
                sTemp = "_Brothel_room";
                break;
            case 1:
                sTemp = "_Brothel";
                break;
            case 2:
                sTemp = "_SecBrRoom";
                break;
            }
            sld.shown = true;
            sld.startLocation = pchar.questTemp.different.TakeMayorsRing.city + sTemp;
            sld.startLocator = "item" + (rand(4) + 1);
            pchar.questTemp.different.TakeMayorsRing.item = true; //флаг кольцо валяется в итемах
            Log_QuestInfo("Кольцо находится в локации " + sld.startLocation + ", в локаторе " + sld.startLocator);
        }
        SetTimerFunction("TakeMayorsRing_null", 0, 0, 1); //освобождаем разрешалку на миниквесты
        ReOpenQuestHeader("SeekMayorsRing");
        AddQuestRecord("SeekMayorsRing", "1");
        AddQuestUserData("SeekMayorsRing", "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
        AddQuestUserData("SeekMayorsRing", "sName", pchar.questTemp.different.TakeMayorsRing.Id);
        break;
    case "TakeRing_6":
        dialog.text = "Вот как? Хм, не ожидал, не ожидал... Ну что же, всего хорошего, капитан.";
        link.l1 = "Прощайте.";
        link.l1.go = "exit";
        ChangeCharacterComplexReputation(pchar, "nobility", -2);
        break;

    case "TakeRing_S1":
        dialog.text = "Отлично, это действительно оно!! Вы мне просто жизнь спасли!";
        link.l1 = "Ну что вы...";
        link.l1.go = "TakeRing_S2";
        TakeItemFromCharacter(pchar, "MayorsRing");
        break;
    case "TakeRing_S2":
        dialog.text = "Вот ваши деньги за проделанную работу. И знайте, что я вам очень благодарен!";
        link.l1 = "Хм, буду иметь в виду...";
        link.l1.go = "exit";
        ChangeCharacterComplexReputation(pchar, "nobility", 5);
        ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 10);
        AddCharacterExpToSkill(pchar, "Leadership", 20);
        AddCharacterExpToSkill(pchar, "Fortune", 20);
        AddMoneyToCharacter(pchar, sti(pchar.questTemp.different.TakeMayorsRing.price));
        pchar.questTemp.different = "free";
        pchar.quest.TakeMayorsRing_null.over = "yes"; //снимаем таймер
        AddQuestRecord("SeekMayorsRing", "7");
        AddQuestUserData("SeekMayorsRing", "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
        CloseQuestHeader("SeekMayorsRing");
        DeleteAttribute(pchar, "questTemp.different.TakeMayorsRing");
        break;
    case "TakeRing_S3":
        dialog.text = "Вот это да!! Надо меньше пить...";
        link.l1 = "Это точно! Ну что же, вот ваше кольцо.";
        link.l1.go = "TakeRing_S4";
        break;
    case "TakeRing_S4":
        dialog.text = "Да-да, спасибо вам огромное. Я - ваш должник! Вот ваши деньги за проделанную работу.";
        link.l1 = "Спасибо " + GetAddress_FormToNPC(NPChar) + ".";
        link.l1.go = "exit";
        TakeItemFromCharacter(pchar, "MayorsRing");
        ChangeCharacterComplexReputation(pchar, "nobility", 3);
        ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 3);
        AddCharacterExpToSkill(pchar, "Leadership", 20);
        AddMoneyToCharacter(pchar, sti(pchar.questTemp.different.TakeMayorsRing.price));
        pchar.questTemp.different = "free";
        pchar.quest.TakeMayorsRing_null.over = "yes"; //снимаем таймер
        AddQuestRecord("SeekMayorsRing", "7");
        AddQuestUserData("SeekMayorsRing", "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
        CloseQuestHeader("SeekMayorsRing");
        DeleteAttribute(pchar, "questTemp.different.TakeMayorsRing");
        break;
        // ---------------------- найти кольцо в борделе ----------------------------

    case "node_1":
        //ОСАДЫ homo
        if (CheckAttribute(Colonies[FindColony(npchar.City)], "Siege"))
        {

            makearef(aData, NullCharacter.Siege);

            if (CheckAttribute(aData, "HelpColony") && sti(aData.HelpColony) == true)
            {
                dialog.text = "Мы вроде всё уже обсудили, не так ли?";
                link.l1 = "Всё верно - не стану вас более задерживать.";
                link.l1.go = "exit";
            }
            else
            {
                dialog.text = "Должен вас огорчить, но в данный момент у меня нет времени, чтобы принять вас. Как вы, наверное, уже знаете, на нашу колонию напали " + NationNamePeople(sti(aData.nation)) + ". И мне необходимо организовать оборону города.";
                link.l1 = "Так я как раз хотел" + GetSexPhrase("", "а") + " предложить свою помощь в обороне форта.";
                link.l1.go = "siege_task";
                link.l2 = "Тогда не стану вас более задерживать.";
                link.l2.go = "exit";
            }
        }
        else
        { //->
            makearef(aData, NullCharacter.Siege);
            if (CheckAttribute(aData, "PlayerHelpMayor") && sti(aData.PlayerHelpMayor) == true && CheckAttribute(aData, "HelpColony") && sti(aData.HelpColony) == true)
            {
                AddMoneyToCharacter(Pchar, (sti(aData.iSquadronPower) * 3000));
                ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 20);
                ChangeCharacterComplexReputation(pchar, "nobility", 10);
                AddCharacterExpToSkill(GetMainCharacter(), "Leadership", 80);
                AddCharacterExpToSkill(GetMainCharacter(), "Sailing", 100);
                AddCharacterExpToSkill(GetMainCharacter(), "Accuracy", 100);
                AddCharacterExpToSkill(GetMainCharacter(), "Cannons", 100);
                //--> слухи
                SiegeRumour("Поговаривают, что вы помогли нам отбиться от " + NationNameSK(sti(aData.nation)) + "ой эскадры - и отстоять нашу колонию! Мы так благодарны вам, " + GetAddress_Form(NPChar) + ".", aData.Colony, sti(aData.conation), -1, 15, 3);
                //<-- слухи
                DeleteAttribute(aData, "PlayerHelpMayor");
                DeleteAttribute(aData, "HelpColony");
                dialog.text = "Ах, это вы, " + GetAddress_Form(NPChar) + " " + GetFullName(pchar) + ", рад вас видеть. Добрые вести для нашей колонии - мы отбились от " + NationNameSK(sti(aData.nation)) + "их захватчиков. В этом есть и ваша заслуга, вот ваша награда " + (sti(aData.iSquadronPower) * 1500) + " песо. Извольте получить.";
                link.l1 = "Спасибо, " + GetAddress_FormToNPC(NPChar) + ", приятно иметь с вами дело!";
                link.l1.go = "exit";
            }
            else
            {
                if (CheckAttribute(aData, "PlayerHelpMayor"))
                    DeleteAttribute(aData, "PlayerHelpMayor");
                dialog.text = "Так какая причина заставила вас прийти сюда и отвлекать меня от важных государственных дел?";
                if (npchar.city != "Panama") // Addon-2016 Jason
                {
                    link.l1 = "Я хочу поговорить о работе на благо короны " + NationNameGenitive(sti(NPChar.nation)) + ".";
                    link.l1.go = "work";
                }
                // Warship Генер "Пираты на необитайке" - сдаем пиратов властям
                if (CheckAttribute(PChar, "Quest.PiratesOnUninhabited_OnShore") || CheckAttribute(PChar, "Quest.PiratesOnUninhabited_ShipSink"))
                {
                    link.l11 = XI_ConvertString(PChar.GenQuest.PiratesOnUninhabited.StartShore + "Dat") + " я встретил" + GetSexPhrase("", "а") + " пиратов. Все " + PChar.GenQuest.PiratesOnUninhabited.PiratesCount + " человек сейчас у меня на борту. Хочу сдать их властям.";
                    link.l11.go = "PiratesOnUninhabited_1";
                }

                link.l2 = "Нужно поговорить с вами об одном деле.";
                if (CheckAttribute(pchar, "questTemp.ReasonToFast") && !CheckAttribute(pchar, "questTemp.ReasonToFast.SpeakOther") && !CheckAttribute(pchar, "questTemp.ReasonToFast.cantSpeakOther") && (pchar.questTemp.ReasonToFast.city == NPChar.city))
                {
                    link.l2.go = "ReasonToFast_Mayor1";
                }
                else
                {
                    link.l2.go = "quests";
                }
                if (CheckAttribute(pchar, "GenQuest.CaptainComission") && (pchar.GenQuest.CaptainComission.variant == "A2") && (pchar.GenQuest.CaptainComission.City == NPChar.city))
                {
                    if (pchar.GenQuest.CaptainComission == "Begin_1" && !CheckAttribute(pchar, "GenQuest.CaptainComission.SpeakMayor"))
                    {
                        link.l12 = "У вас капитаном патрульного " + GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType), "Name") + "Gen")) + " служит некий " + pchar.GenQuest.CaptainComission.Name + ", как я могу с ним повидаться?";
                        link.l12.go = "CapComission_Mayor1";
                    }
                    if (CheckAttribute(pchar, "GenQuest.CaptainComission.PrisonFree"))
                    {
                        link.l12 = "Бывший капитан патрульного " + GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType), "Name") + "Gen")) + " " + pchar.GenQuest.CaptainComission.Name + " согласился открыть свой тайник властям.";
                        link.l12.go = "CapComission_Mayor9";
                    }
                    if (pchar.GenQuest.CaptainComission == "GetGoodsSuccess")
                    {
                        link.l12 = "Бывший капитан патрульного " + GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType), "Name") + "Gen")) + " " + pchar.GenQuest.CaptainComission.Name + " открыл мне свой тайник.";
                        link.l12.go = "CapComission_Mayor13";
                    }
                }
                if (CheckAttribute(pchar, "GenQuest.ShipWreck") && pchar.GenQuest.ShipWreck == "SailorsOnShore" && GetQuestPastDayParam("GenQuest.ShipWreck") < 25 && sti(npchar.nation) == sti(pchar.GenQuest.ShipWreck.Nation))
                {
                    if (!CheckAttribute(pchar, "GenQuest.ShipWreck.SpeakMayor"))
                    {
                        iDay = GetQuestPastDayParam("GenQuest.ShipWreck");
                        if (CheckAttribute(pchar, "GenQuest.ShipWreck.Mutiny"))
                        {
                            link.l13 = UpperFirst(XI_ConvertString(pchar.GenQuest.ShipWreck.Shore + "Dat")) + " я встретил" + GetSexPhrase("", "а") + " капитана " + pchar.GenQuest.ShipWreck.Name + " и его моряков, высаженных на берег пиратом " + pchar.GenQuest.ShipWreck.BadName + ". " +
                                       "К сожалению, перегруз команды на моём судне не позволил взять их на борт. Но я оставил" + GetSexPhrase("", "а") + " им провизию и оружие. Если экспедиционное судно не успеет забрать их в течение " + (30 - iDay) + " дней, то не знаю, удастся ли застать их живыми.";
                            link.l13.go = "ShipWreck1";
                        }
                        else
                        {
                            link.l13 = UpperFirst(XI_ConvertString(pchar.GenQuest.ShipWreck.Shore + "Dat")) + " я встретил" + GetSexPhrase("", "а") + " моряков из потерпевшего крушение судна '" + pchar.GenQuest.ShipWreck.ShipTypeName + "' во главе с их капитаном. " +
                                       "К сожалению, перегруз команды на моём судне не позволил взять их на борт. Но я оставил" + GetSexPhrase("", "а") + " им провизию и оружие. Если экспедиционное судно не успеет забрать их в течение " + (30 - iDay) + " дней, то не знаю, удастся ли застать их живыми.";
                            link.l13.go = "ShipWreck1";
                        }
                    }
                }
                //--> Jason, генер почтового курьера 2 уровня
                if (CheckAttribute(PChar, "questTemp.WPU.Postcureer.LevelUp"))
                {
                    if (pchar.questTemp.WPU.Postcureer.TargetPortmanID == npchar.id)
                    {
                        link.l14 = "Я доставил вам депешу из города " + XI_ConvertString("Colony" + pchar.questTemp.WPU.Postcureer.StartCity + "Gen") + ".";
                        link.l14.go = "Postcureer_LevelUp_ForAll";
                    }
                }
                //<-- генер почтового курьера 2 уровня

                // --> Warship, 16.05.11. Квест "Правосудие на продажу".
                if (CheckAttribute(PChar, "GenQuest.JusticeOnSale.MayorWait") && CheckAttribute(PChar, "GenQuest.JusticeOnSale.CityId") && NPChar.location == PChar.GenQuest.JusticeOnSale.CityId + "_townhall")
                {
                    link.l15 = "Милорд, я обнаружил банду контрабандистов, чьего главаря недавно поймала стража. Они планируют вызволить его. Их корабль '" + PChar.GenQuest.JusticeOnSale.ShipName + "' стоит " + XI_ConvertString(PChar.GenQuest.JusticeOnSale.ShoreId + "Dat") + ".";
                    link.l15.go = "JusticeOnSale_1";
                }
                //<-- Правосудие на продажу

                if (GetPrisonerQty() > 0)
                {
                    link.l3 = "Мне нужно сдать пленного капитана властям.";
                    link.l3.go = "sell_prisoner";
                }
                //Jason --> Регата
                if (CheckAttribute(pchar, "questTemp.Regata.ToPortRoyal") && NPChar.location == "Portroyal_townhall")
                {
                    link.l4 = "Я прибыл по приглашению для участия в регате. Вот мое приглашение.";
                    link.l4.go = "Regata";
                }
                link.l5 = "Может, вы хотите немного передохнуть от важных дел?";
                link.l5.go = "Play_Game";
                link.l10 = "Это просто визит вежливости и ничего более, " + GetAddress_FormToNPC(NPChar) + ".";
                link.l10.go = "node_2";
            }
        } //<-
        break;

    case "Play_Game":
        dialog.text = "Хм, и какие игры вы предпочитаете?";
        link.l1 = "Перекинемся в карты на солидный интерес?";
        link.l1.go = "Card_Game";
        link.l2 = "Погремим костями в покер-джокер?";
        link.l2.go = "Dice_Game";
        link.l10 = "Прошу простить, но меня ждут дела.";
        link.l10.go = "exit";
        break;

    //  карты -->
    case "Card_Game":
        if (!CheckNPCQuestDate(npchar, "Card_date_Yet") || sti(PChar.rank) < 4 || isBadReputation(pchar, 50) || GetCharacterSkillToOld(pchar, SKILL_LEADERSHIP) < rand(5))
        {
            SetNPCQuestDate(npchar, "Card_date_Yet");
            if (pchar.model == "Sharle_6")
                dialog.text = "Прошу меня извинить, монсеньор, но сейчас у меня нет на это времени. Может быть, в другой раз."; // Jason НСО
            else
                dialog.text = "Я не буду играть в азартные игры с разными проходимцами!";
            link.l1 = "Как вам будет угодно.";
            link.l1.go = "exit";
        }
        else
        {
            if (CheckNPCQuestDate(npchar, "Card_date_begin"))
            {
                dialog.text = "Давайте! Отдых никогда не вредил здоровью... только кошельку...";
                link.l1 = "Замечательно.";
                link.l1.go = "Cards_begin";
                link.l2 = "По каким правилам игра?";
                link.l2.go = "Cards_Rule";
            }
            else
            {
                dialog.text = "Нет, с меня довольно на сегодня. Дела ждут.";
                link.l1 = "Как вам будет угодно.";
                link.l1.go = "exit";
            }
        }
        break;

    case "Cards_Rule":
        dialog.text = CARDS_RULE;
        link.l1 = "Что ж, давайте начнём!";
        link.l1.go = "Cards_begin";
        link.l3 = "Нет, это не для меня...";
        link.l3.go = "exit";
        break;

    case "Cards_begin":
        dialog.text = "Давайте определимся со ставкой.";
        link.l1 = "Играем по 1000 песо.";
        link.l1.go = "Cards_Node_100";
        link.l2 = "Давайте по 5000 песо.";
        link.l2.go = "Cards_Node_500";
        link.l3 = "Пожалуй, мне пора.";
        link.l3.go = "exit";
        break;

    case "Cards_Node_100":
        if (!CheckCardsGameSmallRate())
        {
            dialog.text = "О тебе ходит слава непревзойдённого шулера. Я не буду с тобой играть.";
            link.l1 = "Всё врут! Ну и не нужно.";
            link.l1.go = "exit";
            break;
        }

        if (sti(pchar.Money) < 3000)
        {
            dialog.text = "Изволите шутить, " + GetAddress_Form(NPChar) + "? У вас нет денег!";
            link.l1 = "Бывает.";
            link.l1.go = "exit";
            break;
        }
        if (sti(npchar.Money) < 3000)
        {
            dialog.text = "Всё! Нужно завязывать с картами, а то запишут в растратчики и сместят с поста...";
            link.l1 = "Жаль.";
            link.l1.go = "exit";
            break;
        }
        dialog.text = "Хорошо, играем по 1000 монет.";
        link.l1 = "Начали!";
        link.l1.go = "Cards_begin_go";
        pchar.GenQuest.Cards.npcharIdx = npchar.index;
        pchar.GenQuest.Cards.iRate = 1000;
        pchar.GenQuest.Cards.SitType = false;
        break;

    case "Cards_Node_500":
        if (!CheckCardsGameSmallRate())
        {
            dialog.text = "О тебе ходит слава непревзойдённого шулера. Я не буду с тобой играть.";
            link.l1 = "Всё врут! Ну и не нужно.";
            link.l1.go = "exit";
            break;
        }
        if (!CheckCardsGameBigRate())
        {
            dialog.text = "Я слышал, что ты очень хорошо играешь. Я не буду играть с тобой по таким большим ставкам.";
            link.l1 = "Давайте по более низким ставкам?";
            link.l1.go = "Cards_Node_100";
            link.l2 = "Извините, мне пора.";
            link.l2.go = "exit";
            break;
        }

        if (sti(pchar.Money) < 15000)
        {
            dialog.text = "Изволите шутить, " + GetAddress_Form(npchar) + "? У вас нет 15000 песо!";
            link.l1 = "Будут!";
            link.l1.go = "exit";
            break;
        }
        if (sti(npchar.Money) < 15000)
        {
            dialog.text = "Нет, такие ставки не доведут до добра казну города.";
            link.l1 = "Как угодно.";
            link.l1.go = "exit";
            break;
        }
        dialog.text = "Хорошо, играем по 5000 монет.";
        link.l1 = "Начали!";
        link.l1.go = "Cards_begin_go";
        pchar.GenQuest.Cards.npcharIdx = npchar.index;
        pchar.GenQuest.Cards.iRate = 5000;
        pchar.GenQuest.Cards.SitType = false;
        break;

    case "Cards_begin_go":
        SetNPCQuestDate(npchar, "Card_date_begin");
        NextDiag.CurrentNode = NextDiag.TempNode;
        DialogExit();
        LaunchCardsGame();
        break;
    // карты <--

    //  Dice -->
    case "Dice_Game":
        if (!CheckNPCQuestDate(npchar, "Dice_date_Yet") || sti(PChar.rank) < 4 || isBadReputation(pchar, 50) || GetCharacterSkillToOld(pchar, SKILL_LEADERSHIP) < rand(5))
        {
            SetNPCQuestDate(npchar, "Dice_date_Yet");
            if (pchar.model == "Sharle_6")
                dialog.text = "Прошу меня извинить, монсеньор, но сейчас у меня нет на это времени. Может быть, в другой раз."; // Jason НСО
            else
                dialog.text = "Я не буду играть в азартные игры с разными проходимцами!";
            link.l1 = "Как вам будет угодно.";
            link.l1.go = "exit";
        }
        else
        {
            if (CheckNPCQuestDate(npchar, "Dice_date_begin"))
            {
                dialog.text = "Давайте! Отдых никогда не вредил здоровью... только кошельку...";
                link.l1 = "Замечательно.";
                link.l1.go = "Dice_begin";
                link.l2 = "По каким правилам игра?";
                link.l2.go = "Dice_Rule";
            }
            else
            {
                dialog.text = "Нет, с меня довольно на сегодня. Дела ждут.";
                link.l1 = "Как вам будет угодно.";
                link.l1.go = "exit";
            }
        }
        break;

    case "Dice_Rule":
        dialog.text = DICE_RULE;
        link.l1 = "Что ж, давайте начнём!";
        link.l1.go = "Dice_begin";
        link.l3 = "Нет, это не для меня...";
        link.l3.go = "exit";
        break;

    case "Dice_begin":
        dialog.text = "Давайте определимся со ставкой.";
        link.l1 = "Играем по 500 песо за кубик.";
        link.l1.go = "Dice_Node_100";
        link.l2 = "Давайте по 2000 песо за кубик.";
        link.l2.go = "Dice_Node_500";
        link.l3 = "Пожалуй, мне пора.";
        link.l3.go = "exit";
        break;

    case "Dice_Node_100":
        if (!CheckDiceGameSmallRate())
        {
            dialog.text = "О тебе ходит слава непревзойдённого шулера. Я не буду с тобой играть.";
            link.l1 = "Всё врут! Ну и не нужно.";
            link.l1.go = "exit";
            break;
        }

        if (sti(pchar.Money) < 3000)
        {
            dialog.text = "Изволите шутить, " + GetAddress_Form(NPChar) + "? У вас нет денег!";
            link.l1 = "Бывает.";
            link.l1.go = "exit";
            break;
        }
        if (sti(npchar.Money) < 3000)
        {
            dialog.text = "Всё! Нужно завязывать с играми, а то запишут в растратчики и сместят с поста...";
            link.l1 = "Жаль.";
            link.l1.go = "exit";
            break;
        }
        dialog.text = "Хорошо, играем по 500 монет.";
        link.l1 = "Начали!";
        link.l1.go = "Dice_begin_go";
        pchar.GenQuest.Dice.npcharIdx = npchar.index;
        pchar.GenQuest.Dice.iRate = 500;
        pchar.GenQuest.Dice.SitType = false;
        break;

    case "Dice_Node_500":
        if (!CheckDiceGameSmallRate())
        {
            dialog.text = "О тебе ходит слава непревзойдённого шулера. Я не буду с тобой играть.";
            link.l1 = "Всё врут! Ну и не нужно.";
            link.l1.go = "exit";
            break;
        }
        if (!CheckDiceGameBigRate())
        {
            dialog.text = "Я слышал, что ты очень хорошо играешь. Я не буду играть с тобой по таким большим ставкам.";
            link.l1 = "Давайте по более низким ставкам?";
            link.l1.go = "Dice_Node_100";
            link.l2 = "Извините, мне пора.";
            link.l2.go = "exit";
            break;
        }

        if (sti(pchar.Money) < 15000)
        {
            dialog.text = "Изволите шутить, " + GetAddress_Form(NPChar) + "? У вас нет 15000 песо!";
            link.l1 = "Будут!";
            link.l1.go = "exit";
            break;
        }
        if (sti(npchar.Money) < 15000)
        {
            dialog.text = "Нет, такие ставки не доведут до добра казну города.";
            link.l1 = "Как угодно.";
            link.l1.go = "exit";
            break;
        }
        dialog.text = "Хорошо, играем по 2000 монет за кубик.";
        link.l1 = "Начали!";
        link.l1.go = "Dice_begin_go";
        pchar.GenQuest.Dice.npcharIdx = npchar.index;
        pchar.GenQuest.Dice.iRate = 2000;
        pchar.GenQuest.Dice.SitType = false;
        break;

    case "Dice_begin_go":
        SetNPCQuestDate(npchar, "Dice_date_begin");
        NextDiag.CurrentNode = NextDiag.TempNode;
        DialogExit();
        LaunchDiceGame();
        break;
    // Dice <--
    case "node_2":
        dialog.text = "В таком случае, я попрошу вас покинуть мой кабинет и более не мешать мне работать.";
        link.l1 = "Да, да, конечно, извините, что потревожил" + GetSexPhrase("", "а") + " вас.";
        link.l1.go = "exit";
        break;

    //---------------------------- генератор квестов мэра -------------------------------
    case "work":
        dialog.text = "Это есть баг, известите Эдди о наличие оного.";
        link.l1 = "Хорошо, приятель!";
        link.l1.go = "exit";

        //==> взят ли какой-либо квест
        if (CheckAttribute(pchar, "GenQuest.questName"))
        {
            //--> Федот, да не тот
            QuestName = pchar.GenQuest.questName;
            if (pchar.GenQuest.(QuestName).MayorId != npchar.id)
            {
                dialog.text = RandPhraseSimple("Насколько мне известно, вы уже имеете задание от губернатора " + XI_ConvertString("Colony" + characters[GetCharacterIndex(pchar.GenQuest.(QuestName).MayorId)].city + "Gen") + ". Пока не выполните предыдущие задачи, новых я вам не дам.",
                                               "Хм, а не вы ли в " + XI_ConvertString("Colony" + characters[GetCharacterIndex(pchar.GenQuest.(QuestName).MayorId)].city + "Dat") + " брались за выполнение неких поручений местного губернатора? Да, именно так! Пока вы не выполните свои обязательства, ничего нового я вам не поручу.");
                link.l1 = RandPhraseSimple("Понятно...", "Я понял" + GetSexPhrase("", "а") + ", " + GetAddress_FormToNPC(NPChar) + ".");
                link.l1.go = "exit";
                break;
            }
            //<--Федот, да не тот
            //-------- взят квест уничтожения банды ---------->>
            if (QuestName == "DestroyGang")
            {
                switch (pchar.GenQuest.DestroyGang)
                {
                    makearef(arName, pchar.GenQuest.DestroyGang);
                case "":
                    dialog.text = LinkRandPhrase("Задание на поиск бандита по имени " + GetFullName(arName) + " вами уже получено. Выполняйте!",
                                                 "Вы уже имеете задание на поиск бандита по имени " + GetFullName(arName) + ". Я жду результатов!",
                                                 "Пока вы тут прохлаждаетесь у меня в резиденции, " + GetFullName(arName) + " грабит наших колонистов! Немедленно выполняйте возложенное на вас поручение!");
                    link.l1 = RandPhraseSimple("Хорошо, " + GetAddress_FormToNPC(NPChar) + ".", "Я занимаюсь этим, " + GetAddress_FormToNPC(NPChar) + ".");
                    link.l1.go = "exit";
                    break;
                case "Late":
                    dialog.text = RandPhraseSimple("Время, данное вам на поиск и уничтожение бандита, вышло. И как вы думаете, что мне докладывают? А я вам скажу - " + GetFullName(arName) + " до сих пор жив и здоров! Извольте объясниться, " + GetAddress_Form(NPChar) + ".",
                                                   "Все сроки, предоставленные вам для уничтожения этого мерзавца по имени " + GetFullName(arName) + ", вышли. Однако, мне докладывают, что подвижек нет. В чём дело?");
                    link.l1 = "Я не сумел" + GetSexPhrase("", "а") + " выполнить ваше задание в означенное время, " + GetAddress_FormToNPC(NPChar) + ".";
                    link.l1.go = "All_Late";
                    break;
                case "Found":
                    dialog.text = RandPhraseSimple("Итак, что скажете? Вы сумели уничтожить указанного бандита? " + GetFullName(arName) + " наконец убит?", "Скажите мне только одно - " + GetFullName(arName) + " жив или мёртв?");
                    link.l1 = "К сожалению, жив, " + GetAddress_FormToNPC(NPChar) + ". Мне удалось разыскать его, но силы оказались неравны и мне пришлось отступить. Прошу прощения, этот бандит мне не по зубам.";
                    link.l1.go = "All_Found";
                    break;
                case "Execute":
                    dialog.text = RandPhraseSimple("Итак, что скажете? Вы сумели уничтожить указанного бандита? " + GetFullName(arName) + " наконец убит?", "Скажите мне только одно - " + GetFullName(arName) + " жив или мёртв?");
                    link.l1 = "Он мёртв, " + GetAddress_FormToNPC(NPChar) + ".";
                    link.l1.go = "All_Execute";
                    AddCharacterExpToSkill(PChar, "Leadership", 80);
                    ChangeCharacterComplexReputation(pchar, "authority", 1);
                    break;
                }
            }
            //-------- контркурьер ---------->>
            if (QuestName == "TakePostcureer")
            {
                switch (pchar.GenQuest.TakePostcureer)
                {
                case "":
                    dialog.text = LinkRandPhrase("Задание на захват курьерского судна вами уже получено. Выполняйте!",
                                                 "Вы уже имеете задание на захват курьерского судна. Я жду результатов!",
                                                 "Пока вы тут прохлаждаетесь у меня в резиденции, нужные мне документы идут прямиком в руки врага! Немедленно выполняйте возложенное на вас поручение!");
                    link.l1 = RandPhraseSimple("Хорошо, " + GetAddress_FormToNPC(NPChar) + ".", "Я занимаюсь этим, " + GetAddress_FormToNPC(NPChar) + ".");
                    link.l1.go = "exit";
                    break;
                case "Late":
                    dialog.text = RandPhraseSimple("Время, данное вам на поиск и захват курьерского корабля вышло. И как вы думаете, что мне докладывают? А я вам скажу - документы, которые я ждал, попали в руки неприятеля! Извольте объясниться, " + GetAddress_Form(NPChar) + ".",
                                                   "Все сроки, предоставленные вам для захвата документов с курьерского корабля вышли. Результатов нет. В чём дело?");
                    link.l1 = "Я не сумел" + GetSexPhrase("", "а") + " выполнить ваше задание в означенное время, " + GetAddress_FormToNPC(NPChar) + ".";
                    link.l1.go = "All_Late";
                    break;
                case "Found":
                    dialog.text = RandPhraseSimple("Итак, что скажете? Вы захватили пакет документов?", "Скажите мне только одно - пакет с корреспонденцией у вас?");
                    link.l1 = "К сожалению, нет, " + GetAddress_FormToNPC(NPChar) + ". Мне удалось разыскать корабль, однако документы я захватить не смог.";
                    link.l1.go = "All_Found";
                    break;
                case "Execute":
                    dialog.text = RandPhraseSimple("Итак, что скажете? Вы захватили пакет документов?", "Скажите мне только одно - пакет с корреспонденцией у вас?");
                    link.l1 = "Да, " + GetAddress_FormToNPC(NPChar) + ". Я готов предоставить его вам. Вот он.";
                    link.l1.go = "All_Execute";
                    AddCharacterExpToSkill(PChar, "Leadership", 100);
                    AddCharacterExpToSkill(PChar, "Fortune", 200);
                    AddCharacterExpToSkill(PChar, "Sneak", 50);
                    RemoveItems(pchar, "ContraPostLetters", 1);
                    ChangeCharacterComplexReputation(pchar, "authority", 1);
                    break;
                }
            }
            //-------- контрфрахт - арсенал ---------->>
            if (QuestName == "TakeArsenalship")
            {
                switch (pchar.GenQuest.TakeArsenalship)
                {
                case "":
                    dialog.text = LinkRandPhrase("Задание на уничтожение военного транспорта вами уже получено. Выполняйте!",
                                                 "Вы уже имеете задание на уничтожение военного транспорта. Я жду результатов!",
                                                 "Пока вы тут прохлаждаетесь у меня в резиденции, порох и боеприпасы идут прямиком к вражеским пушкам! Немедленно выполняйте возложенное на вас поручение!");
                    link.l1 = RandPhraseSimple("Хорошо, " + GetAddress_FormToNPC(NPChar) + ".", "Я занимаюсь этим, " + GetAddress_FormToNPC(NPChar) + ".");
                    link.l1.go = "exit";
                    break;
                case "Late":
                    dialog.text = RandPhraseSimple("Время, данное вам на поиск и уничтожение военного транспорта вышло. И как вы думаете, что мне докладывают? А я вам скажу - вражеский конвой благополучно дошел до места назначения! Извольте объясниться, " + GetAddress_Form(NPChar) + ".",
                                                   "Все сроки, предоставленные вам для уничтожения вражеского военного транспорта вышли. Результатов нет. В чём дело?");
                    link.l1 = "Я не сумел" + GetSexPhrase("", "а") + " выполнить ваше задание в означенное время, " + GetAddress_FormToNPC(NPChar) + ".";
                    link.l1.go = "All_Late";
                    break;
                case "Found":
                    dialog.text = RandPhraseSimple("Итак, что скажете? Вы уничтожили вражеский военный транспорт?", "Скажите мне только одно - вражеский арсенал на дне моря?");
                    link.l1 = "К сожалению, нет, " + GetAddress_FormToNPC(NPChar) + ". Мне удалось разыскать конвой, однако потопить нужный корабль я не смог.";
                    link.l1.go = "All_Found";
                    break;
                case "Execute":
                    dialog.text = RandPhraseSimple("Итак, что скажете? Вы уничтожили вражеский военный транспорт?", "Скажите мне только одно - вражеский арсенал на дне моря?");
                    link.l1 = "Да, " + GetAddress_FormToNPC(NPChar) + ". Порох и боеприпасы не достанутся врагу.";
                    link.l1.go = "All_Execute";
                    AddCharacterExpToSkill(PChar, "Leadership", 120);
                    AddCharacterExpToSkill(PChar, "Fortune", 200);
                    AddCharacterExpToSkill(PChar, "Sneak", 50);
                    ChangeCharacterComplexReputation(pchar, "authority", 1);
                    break;
                }
            }
            //-------- ОЗГ - пират ---------->>
            if (QuestName == "TakePirateship")
            {
                switch (pchar.GenQuest.TakePirateship)
                {
                case "":
                    dialog.text = LinkRandPhrase("Задание на уничтожение пирата вами уже получено. Выполняйте!",
                                                 "Вы уже имеете задание на уничтожение пиратского корабля. Я жду результатов!",
                                                 "Пока вы тут прохлаждаетесь у меня в резиденции, гнусный пират разыскивает очередную жертву! Немедленно выполняйте возложенное на вас поручение!");
                    link.l1 = RandPhraseSimple("Хорошо, " + GetAddress_FormToNPC(NPChar) + ".", "Я занимаюсь этим, " + GetAddress_FormToNPC(NPChar) + ".");
                    link.l1.go = "exit";
                    break;
                case "Late":
                    dialog.text = RandPhraseSimple("Время, данное вам на поиск и уничтожение пирата вышло. И как вы думаете, что мне докладывают? А я вам скажу - гнусный пират продолжает грабить наши корабли! Извольте объясниться, " + GetAddress_Form(NPChar) + ".",
                                                   "Все сроки, предоставленные вам для уничтожения пиратского корабля вышли. Результатов нет. В чём дело?");
                    link.l1 = "Я не сумел" + GetSexPhrase("", "а") + " выполнить ваше задание в означенное время, " + GetAddress_FormToNPC(NPChar) + ".";
                    link.l1.go = "All_Late";
                    break;
                case "Found":
                    dialog.text = RandPhraseSimple("Итак, что скажете? Вы уничтожили пиратский корабль?", "Скажите мне только одно - гнусный пират на дне моря?");
                    link.l1 = "К сожалению, нет, " + GetAddress_FormToNPC(NPChar) + ". Мне удалось разыскать негодяя, однако потопить его корабль я не смог.";
                    link.l1.go = "All_Found";
                    break;
                case "Execute":
                    dialog.text = RandPhraseSimple("Итак, что скажете? Вы уничтожили пиратский корабль?", "Скажите мне только одно - гнусный пират на дне моря?");
                    link.l1 = "Да, " + GetAddress_FormToNPC(NPChar) + ". Этот негодяй больше никогда не побеспокоит мирные суда наших торговцев.";
                    link.l1.go = "All_Execute";
                    AddCharacterExpToSkill(PChar, "Leadership", 150);
                    AddCharacterExpToSkill(PChar, "Fortune", 200);
                    AddCharacterExpToSkill(PChar, "Sneak", 50);
                    ChangeCharacterComplexReputation(pchar, "authority", 1);
                    break;
                }
            }
            //-------- ОЗГ - пассажир ---------->>
            if (QuestName == "TakePassenger")
            {
                switch (pchar.GenQuest.TakePassenger)
                {
                case "":
                    dialog.text = LinkRandPhrase("Задание на розыск преступника вами уже получено. Выполняйте!",
                                                 "Вы уже имеете задание на розыск преступника. Я жду результатов!",
                                                 "Пока вы тут прохлаждаетесь у меня в резиденции, гнусный негодяй спокойно плывет себе на корабле! Немедленно выполняйте возложенное на вас поручение!");
                    link.l1 = RandPhraseSimple("Хорошо, " + GetAddress_FormToNPC(NPChar) + ".", "Я занимаюсь этим, " + GetAddress_FormToNPC(NPChar) + ".");
                    link.l1.go = "exit";
                    break;
                case "Late":
                    dialog.text = RandPhraseSimple("Время, данное вам на поиск негодяя вышло. И как вы думаете, что мне докладывают? А я вам скажу - он благополучно прибыл в место назначения и скрылся неведомо куда! Извольте объясниться, " + GetAddress_Form(NPChar) + ".",
                                                   "Все сроки, предоставленные вам для розыска преступника вышли. Результатов нет. В чём дело?");
                    link.l1 = "Я не сумел" + GetSexPhrase("", "а") + " выполнить ваше задание в означенное время, " + GetAddress_FormToNPC(NPChar) + ".";
                    link.l1.go = "All_Late";
                    break;
                case "Found":
                    dialog.text = RandPhraseSimple("Итак, что скажете? Вы захватили мерзавца?", "Скажите мне только одно - гнусный мерзавец в кандалах у вас в трюме?");
                    link.l1 = "К сожалению, нет, " + GetAddress_FormToNPC(NPChar) + ". Мне не удалось захватить негодяя. Он утонул вместе с кораблем, на котором плыл.";
                    link.l1.go = "All_Found";
                    break;
                case "Execute":
                    dialog.text = RandPhraseSimple("Итак, что скажете? Вы захватили мерзавца?", "Скажите мне только одно - гнусный мерзавец в кандалах у вас в трюме?");
                    link.l1 = "Да, " + GetAddress_FormToNPC(NPChar) + ". Прикажите прислать солдат к пирсу, и я немедленно свезу его на берег.";
                    link.l1.go = "All_Execute";
                    AddCharacterExpToSkill(PChar, "Leadership", 150);
                    AddCharacterExpToSkill(PChar, "Fortune", 200);
                    AddCharacterExpToSkill(PChar, "Sneak", 100);
                    ChangeCharacterComplexReputation(pchar, "authority", 1);
                    sld = &Characters[sti(Pchar.GenQuest.TakePassenger.PrisonerIDX)];
                    ReleasePrisoner(sld); //освободили пленника
                    sld.lifeday = 0;
                    break;
                }
            }
            //-------- таможенный патруль ---------->>
            if (QuestName == "CustomPatrol")
            {
                switch (pchar.GenQuest.CustomPatrol)
                {
                case "":
                    dialog.text = LinkRandPhrase("Задание на розыск контрабандистов вами уже получено. Выполняйте!",
                                                 "Вы уже имеете задание на розыск контрабандистов. Я жду результатов!",
                                                 "Пока вы тут прохлаждаетесь у меня в резиденции, контрабандисты спокойно готовятся к сделке! Немедленно выполняйте возложенное на вас поручение!");
                    link.l1 = RandPhraseSimple("Хорошо, " + GetAddress_FormToNPC(NPChar) + ".", "Я занимаюсь этим, " + GetAddress_FormToNPC(NPChar) + ".");
                    link.l1.go = "exit";
                    break;
                case "Late":
                    dialog.text = RandPhraseSimple("Время, данное вам на поиск контрабандистов вышло. И как вы думаете, что мне докладывают? А я вам скажу - они благополучно продали товар! Извольте объясниться, " + GetAddress_Form(NPChar) + ".",
                                                   "Все сроки, предоставленные вам для розыска контрабандистов вышли. Результатов нет. В чём дело?");
                    link.l1 = "Я не сумел" + GetSexPhrase("", "а") + " выполнить ваше задание в означенное время, " + GetAddress_FormToNPC(NPChar) + ".";
                    link.l1.go = "All_Late";
                    break;
                case "Found":
                    dialog.text = RandPhraseSimple("Итак, что скажете? Вы расправились с контрабандистами?", "Скажите мне только одно - контрабандная сделка сорвана?");
                    link.l1 = "К сожалению, нет, " + GetAddress_FormToNPC(NPChar) + ". Мне не удалось помешать негодяям.";
                    link.l1.go = "All_Found";
                    break;
                case "Execute":
                    dialog.text = RandPhraseSimple("Итак, что скажете? Вы расправились с контрабандистами?", "Скажите мне только одно - контрабандная сделка сорвана?");
                    link.l1 = "Да, " + GetAddress_FormToNPC(NPChar) + ". Я настиг их корабли и уничтожил обоих, как продавца, так и покупателя.";
                    link.l1.go = "All_Execute";
                    AddCharacterExpToSkill(PChar, "Leadership", 100);
                    AddCharacterExpToSkill(PChar, "Fortune", 200);
                    AddCharacterExpToSkill(PChar, "Sneak", 200);
                    ChangeCharacterComplexReputation(pchar, "authority", 1);
                    break;
                }
            }
            //-------- Дезертир ---------->>
            if (QuestName == "FindFugitive")
            {
                switch (pchar.GenQuest.FindFugitive)
                {
                case "":
                    dialog.text = LinkRandPhrase("Задание на розыск дезертира вами уже получено. Выполняйте!",
                                                 "Вы уже имеете задание на розыск дезертира. Я жду результатов!",
                                                 "Пока вы тут прохлаждаетесь у меня в резиденции, дезертир, возможно, выдаёт государственные секреты! Немедленно выполняйте возложенное на вас поручение!");
                    link.l1 = RandPhraseSimple("Хорошо, " + GetAddress_FormToNPC(NPChar) + ".", "Я занимаюсь этим, " + GetAddress_FormToNPC(NPChar) + ".");
                    link.l1.go = "exit";
                    break;
                case "Late":
                    dialog.text = RandPhraseSimple("Время, данное вам на поиск дезертира вышло. И как вы думаете, что мне докладывают? А я вам скажу - что никаких результатов нет! Извольте объясниться, " + GetAddress_Form(NPChar) + ".",
                                                   "Все сроки, предоставленные вам для розыска дезертира вышли. Результатов нет. В чём дело?");
                    link.l1 = "Я не сумел" + GetSexPhrase("", "а") + " выполнить ваше задание в означенное время, " + GetAddress_FormToNPC(NPChar) + ".";
                    link.l1.go = "All_Late";
                    break;
                case "Found":
                    dialog.text = RandPhraseSimple("Итак, что скажете? Вы захватили дезертира?", "Скажите мне только одно - дезертир в кандалах у вас в трюме?");
                    link.l1 = "К сожалению, нет, " + GetAddress_FormToNPC(NPChar) + ". Мне не удалось захватить негодяя. Я нашёл его след в поселении " + XI_ConvertString("Colony" + pchar.GenQuest.FindFugitive.City) + ", однако буквально за день до моего прибытия он скрылся на пиратском судне в неизвестном направлении. Думаю, он примкнул к джентльменам удачи...";
                    link.l1.go = "All_Found";
                    break;
                case "Execute":
                    dialog.text = RandPhraseSimple("Так-так... Вот и наш " + pchar.GenQuest.FindFugitive.Name + "... Отличная работа, капитан! Розыски были трудными?", "О, какие у нас гости! Доброго дня, " + pchar.GenQuest.FindFugitive.Name + "! Отличная работа, капитан! Много сил затратили на розыски?");
                    link.l1 = "Как сказать, " + GetAddress_FormToNPC(NPChar) + ". Как бы там ни было - ваше задание я выполнил.";
                    link.l1.go = "All_Execute";
                    AddCharacterExpToSkill(PChar, "Leadership", 200);
                    AddCharacterExpToSkill(PChar, "Fortune", 200);
                    AddCharacterExpToSkill(PChar, "Sneak", 100);
                    ChangeCharacterComplexReputation(pchar, "authority", 1);
                    sld = &Characters[sti(Pchar.GenQuest.FindFugitive.PrisonerIDX)];
                    ReleasePrisoner(sld); //освободили пленника
                    LAi_SetActorType(sld);
                    sld.lifeday = 0;
                    pchar.quest.FindFugitive_Over.over = "yes"; //снимаем таймер
                    chrDisableReloadToLocation = false;         //открыть локацию
                    break;
                }
            }
            //------ проникновение во враждебный город ------------>>
            if (QuestName == "Intelligence")
            {
                switch (pchar.GenQuest.Intelligence)
                {
                case "":
                    if (GetQuestPastDayParam("GenQuest.Intelligence") > sti(pchar.GenQuest.Intelligence.Terms))
                    {
                        dialog.text = RandPhraseSimple("Время, данное вам на доставку письма, вышло. И я так понимаю, что результата у вас нет.",
                                                       "Все сроки, предоставленные вам для доставки письма, вышли. Однако, как я понимаю, подвижек нет. В чём дело?");
                        link.l1 = "Я не сумел" + GetSexPhrase("", "а") + " выполнить вашего задания, " + GetAddress_FormToNPC(NPChar) + ".";
                        link.l1.go = "All_Late";
                    }
                    else
                    {
                        dialog.text = LinkRandPhrase("Задание на доставку мне письма вами уже получено. Выполняйте!",
                                                     "Вы уже имеете задание на доставку мне письма лично в руки. Я жду результатов, мне нужно это письмо как можно быстрей!",
                                                     "Пока вы тут прохлаждаетесь у меня в резиденции, нужная мне информация до сих пор у того, кто должен её отправить! Немедленно приступайте к заданию, доставьте мне письмо!");
                        link.l1 = RandPhraseSimple("Хорошо, " + GetAddress_FormToNPC(NPChar) + ".", "Займусь прямо сейчас, " + GetAddress_FormToNPC(NPChar) + ".");
                        link.l1.go = "exit";
                    }
                    break;
                case "Execute":
                    dialog.text = RandPhraseSimple("Вы доставили ожидаемое мной письмо?", "Говорите же быстрей, пакет у вас?!");
                    link.l1 = "Да, я всё сделал" + GetSexPhrase("", "а") + ". Как мы и договаривались - вручаю лично в руки.";
                    if (GetQuestPastDayParam("GenQuest.Intelligence") > sti(pchar.GenQuest.Intelligence.Terms))
                    {
                        link.l1.go = "Intelligence_ExecuteLate";
                        AddCharacterExpToSkill(PChar, "Sneak", 200);
                    }
                    else
                    {
                        link.l1.go = "All_Execute";
                        AddCharacterExpToSkill(PChar, "Leadership", 100);
                        AddCharacterExpToSkill(PChar, "Sneak", 200);
                    }
                    TakeItemFromCharacter(pchar, "sicretLetter");
                    DeleteAttribute(ItemsFromID("sicretLetter"), "City");
                    DeleteAttribute(ItemsFromID("sicretLetter"), "Mayor");
                    break;
                }
            }
            break;
        }
        sTemp = npchar.city;
        //занят ПГГ
        i = CheckAvailableTaskForNPC(NPChar, PGG_TASK_WORKONMAYOR);
        if (i != -1)
        {
            dialog.text = "Увы, на сегодня у меня заданий больше нет. Последнее выполнил " + GetFullName(&Characters[i]) + ". Зайдите завтра, может что-то появится.";
            link.l1 = "Ах, чёрт!!! Не везёт...";
            link.l1.go = "exit";
            break;
        }
        //navy <--
        if (!CheckAttribute(npchar, "work_date") || GetNpcQuestPastDayParam(npchar, "work_date") > 2 || bBettaTestMode)
        {
            SaveCurrentNpcQuestDateParam(npchar, "work_date");
            if (rand(5) > 4 && !bBettaTestMode && pchar.location == "Panama_townhall") // patch-5
            {
                dialog.text = LinkRandPhrase("Сейчас у меня нет работы для таких, как вы. Зайдите завтра, что ли...",
                                             "Никакого поручения для вас у меня сегодня нет. Заходите позже, через день-другой.",
                                             "Сегодня ничего нет такого, что я мог бы вам поручить. Буду рад видеть вас в другой день.");
                link.l1 = "Я понял" + GetSexPhrase("", "а") + ", " + GetAddress_FormToNPC(NPChar) + ".";
                link.l1.go = "exit";
            }
            else
            {
                i = dRand(7);
                switch (i)
                {
                //========== квест уничтожения банды ============ //Jason: оставляем, как классику
                case 0:
                    pchar.GenQuest.DestroyGang.Terms = dRand(2) + 2;                                            //сроки выполнения задания
                    pchar.GenQuest.DestroyGang.Money = ((dRand(6) + 4) * 250) + (sti(pchar.rank) * 300 + 2000); //вознаграждение
                    makearef(arName, pchar.GenQuest.DestroyGang);
                    arName.nation = PIRATE;
                    arName.sex = "man";
                    SetRandomNameToCharacter(arName); //имя бандита в структуру квеста
                    dialog.text = "Именно сейчас у меня есть для вас задание. В джунглях близ " + XI_ConvertString("Colony" + npchar.city + "Gen") + " появилась банда грабителей, и мне известно, что главарём в ней является некий " + GetFullName(arName) + ". Разыщите и уничтожьте эту шайку разбойников.";
                    link.l1 = "Я каким-то образом ограничен" + GetSexPhrase("", "а") + " в сроках?";
                    link.l1.go = "DestroyGang";
                    break;
                //========== пробраться во вражеский город ============//Jason: оставляем, как годный
                case 1:
                    pchar.GenQuest.Intelligence.Terms = dRand(10) + (42 - MOD_SKILL_ENEMY_RATE);                    //сроки выполнения задания
                    pchar.GenQuest.Intelligence.Money = ((dRand(4) + 6) * 1000) + (sti(pchar.rank) * 1000 + 10000); //вознаграждение
                    pchar.GenQuest.Intelligence.City = GetSpyColony(npchar);                                        //враждебная колония
                    sTemp = ", что на " + XI_ConvertString(colonies[FindColony(pchar.GenQuest.Intelligence.City)].islandLable + "Dat");
                    dialog.text = "У меня есть для вас задание, сопряжённое с серьёзным риском. Мне нужно, чтобы вы пробрались в " + XI_ConvertString("Colony" + pchar.GenQuest.Intelligence.City + "Acc") + sTemp + ", встретились там с указанным человеком и доставили мне то, что он вам даст.";
                    link.l1 = "Хм, не сказал" + GetSexPhrase("", "а") + " бы, что в " + XI_ConvertString("Colony" + pchar.GenQuest.Intelligence.City + "Dat") + " будут рады меня видеть...";
                    link.l1.go = "Intelligence";
                    break;

                //========== контркурьер - отобрать почту ============
                case 2:
                    dialog.text = "Да, у меня есть поручение, для выполнения которого вам потребуется максимум расторопности, а также умение грамотно вести морской бой. Вы готовы проявить себя?";
                    link.l1 = "Ваша светлость, вы можете поподробнее изложить суть предстоящего задания?";
                    link.l1.go = "TakePostcureer";
                    break;

                //========== контрфрахт - потопить корабль с боеприпасами ============
                case 3:
                    dialog.text = "Да, у меня есть поручение, для выполнения которого вам потребуется недюжинная отвага, а также умение грамотно вести морской бой. Вы готовы проявить себя?";
                    link.l1 = "Ваша светлость, вы можете поподробнее изложить суть предстоящего задания?";
                    link.l1.go = "TakeArsenalship";
                    break;
                //========== ОЗГ - охотник на пирата ============
                case 4:
                    dialog.text = "Да, у меня есть для вас ответственное задание, для выполнения которого вам потребуется приложить все ваши умения в морском деле. Это связано с пиратами...";
                    link.l1 = "С пиратами? Можно подробнее узнать, что именно мне предстоит сделать?";
                    link.l1.go = "TakePirateship";
                    break;
                //========== ОЗГ - охотник на пассажира ============
                case 5:
                    dialog.text = "Вы вовремя, сударь. У меня есть неотложное задание, которое, как мне кажется, я вполне могу поручить вам. Это связано с поиском и захватом одного человека...";
                    link.l1 = "Розыск человека? Можно подробнее узнать, что именно мне предстоит сделать?";
                    link.l1.go = "TakePassenger";
                    break;
                //========== Патруль - таможенник ============
                case 6:
                    dialog.text = "Вы как нельзя вовремя, капитан. Мне нужно срочно решить проблему, связанную с контрабандой товара в нашу колонию. Надеюсь, корабль у вас в надлежащем состоянии и готов к сражению?";
                    link.l1 = "Мое судно всегда в боевой готовности. Введите меня в курс предстоящего дела, ваша светлость.";
                    link.l1.go = "CustomPatrol";
                    break;
                    //========== Найти дезертира ============
                case 7:
                    dialog.text = "У меня есть для вас задание, связанное с посещением ряда поселений на архипелаге. Вы готовы к продолжительному путешествию?";
                    link.l1 = "Я и мои люди всегда готовы отправиться в путь немедленно. Что конкретно мне предстоит сделать?";
                    link.l1.go = "FindFugitive";
                    break;
                }
            }
        }
        else
        {
            dialog.text = LinkRandPhrase("Сегодня я уже ничего не могу предложить в качестве работы.", "На сегодня работы для вас уже нет.", "На сегодня уже всё, работы нет. Все вопросы по поводу работы - завтра.");
            link.l1 = RandPhraseSimple("Жаль...", "Эх, очень жаль, " + GetAddress_FormToNPC(NPChar) + ". ");
            link.l1.go = "exit";
        }
        //---------------------------- генератор квестов мэра -------------------------------
        break;

    case "sell_prisoner":
        dialog.text = "Кого вы хотите отпустить за выкуп?";

        qty = 1;
        for (i = 0; i < GetPassengersQuantity(pchar); i++)
        {
            cn = GetPassenger(pchar, i);
            if (cn != -1)
            {
                offref = GetCharacter(cn);
                if (CheckAttribute(offref, "prisoned"))
                {
                    if (sti(offref.prisoned) == true && GetRemovable(offref)) // ставим только фантомов
                    {
                        attrLoc = "l" + qty;
                        link.(attrLoc) = GetFullName(offref) + " - " + NationNameMan(sti(offref.nation)) + ".";
                        link.(attrLoc).go = "GetPrisonerIdx_" + offref.index;
                        qty++;
                    }
                }
            }
        }
        link.l99 = "Никого.";
        link.l99.go = "exit";
        break;

    case "sell_prisoner_2":
        offref = GetCharacter(sti(pchar.GenQuest.GetPrisonerIdx));
        attrLoc = "Итак, это капитан " + GetFullName(offref) + ", " + NationNameMan(sti(offref.nation)) + ".";
        // цена зависит от губернатора
        qty = makeint(sti(offref.rank) * (800 + GetCharacterSPECIALSimple(NPChar, SPECIAL_L) * 100) + GetCharacterSkillToOld(offref, "Leadership") * 500 + GetCharacterSkillToOld(pchar, "commerce") * 500);
        if (sti(offref.nation) == sti(NPChar.nation))
        {
            attrLoc = attrLoc + " Я готов выкупить соотечественника за " + FindRussianMoneyString(qty) + ".";
        }
        else
        {
            if (sti(offref.nation) == PIRATE)
            {
                qty = qty / 5;
                attrLoc = attrLoc + " Я могу дать за этого висельника " + FindRussianMoneyString(qty) + ". И мы сразу же казним негодяя.";
            }
            else
            {
                qty = qty / 2;
                attrLoc = attrLoc + " За этого человека я могу заплатить не более " + FindRussianMoneyString(qty) + ".";
            }
        }
        dialog.text = attrLoc;
        pchar.PrisonerSellPrice = qty;
        link.l1 = "По рукам. Он полностью ваш, " + GetAddress_FormToNPC(NPChar) + ".";
        link.l1.go = "sell_prisoner_3";
        link.l3 = "Нет. Не пойдет.";
        link.l3.go = "exit";
        break;

    case "sell_prisoner_3":
        dialog.text = "Вот и славно.";
        link.l1 = "Всего хорошего.";
        link.l1.go = "exit";
        OfficersReaction("bad");

        offref = GetCharacter(sti(pchar.GenQuest.GetPrisonerIdx));
        AddMoneyToCharacter(pchar, sti(pchar.PrisonerSellPrice));
        if (sti(offref.nation) == sti(NPChar.nation))
        {
            AddCharacterExpToSkill(pchar, "Commerce", 25);
        }
        else
        {
            if (sti(offref.nation) == PIRATE)
            {
                ChangeCharacterComplexReputation(pchar, "nobility", -2);
            }
            else
            {
                AddCharacterExpToSkill(pchar, "Commerce", 5);
            }
        }

        offref.location = "";
        ReleasePrisoner(offref); // освободили пленника
        break;
    ////   CAPTURE //////////
    case "CAPTURE_Main":
        NextDiag.TempNode = "CAPTURE_Main";
        AfterTownBattle(); // всё, все свободны

        // --> Левассер
        if (pchar.location == "Tortuga_townhall" && CheckAttribute(pchar, "questTemp.Sharlie.Hardcore_Tortuga"))
        {
            dialog.Text = "Аргх! Какого чёрта вы творите этот беспредел, де Мор? С каких пор французы нападают на французов?";
            Link.l1 = "По приказу Франсуа Ловинье де Пуанси ты, Левассер, смещён с поста губернатора Тортуги и приговорён к смерти. А я - исполнитель этого приговора!";
            Link.l1.go = "levasser";
            break;
        }
        // <-- Левассер
        // fix от грабежа 5 раз на дню -->
        if (!CheckNPCQuestDate(npchar, "GrabbingTownDate"))
        {
            dialog.Text = "Вы уже всё забрали. Что вам ещё нужно?";
            Link.l1 = "Да, точно, ошиб" + GetSexPhrase("ся", "лась") + " городом.";
            Link.l1.go = "Exit_City";

            NPChar.NoGiveMoney = true;

            ChangeCharacterHunterScore(GetMainCharacter(), NationShortName(sti(NPChar.nation)) + "hunter", 20);
            // вернем диалог после разговора и спрячем
            SetReturn_Gover_Dialog_Exit(NPChar);
            break;
        }
        SetNPCQuestDate(npchar, "GrabbingTownDate");
        // fix от грабежа 5 раз на дню <--

        if (CheckAttribute(FortChref, "Fort.Mode") && sti(FortChref.Fort.Mode) != FORT_DEAD)
        { // а форт-то ЖИВ, значит с суши прошли
            dialog.Text = "Какая неслыханная наглость! Скоро прибудет подкрепление из форта, и вам не поздоровится!";
            Link.l2 = "Я не собираюсь торчать тут до его прихода. Заплати мне, и мы покинем этот город.";
            Link.l2.go = "Summ";
            Pchar.HalfOfPaymentByCity = true; // токо половина денег
        }
        else
        {
            dialog.Text = "На этот раз ваша взяла, но знайте, что скоро прибудет наша эскадра, и от вас мокрого места не останется.";
            if (!bWorldAlivePause || bBettaTestMode)
            {
                int iColony = FindColony(npchar.city);
                if (!CheckAttribute(&colonies[iColony], "notCaptured")) //незахватываемые города
                {
                    if (CheckAttribute(FortChref, "Default.Prison"))
                    {
                        Link.l1 = "Поговори ещё! Этот город отныне принадлежит мне, а вашу эскадру я отправлю на свидание к морскому дьяволу. Эй, парни, возьмите эту свинку и посадите за решетку.";
                    }
                    else
                    {
                        Link.l1 = "Этот город отныне принадлежит мне, и как его защитить - я решу сам" + GetSexPhrase("", "а") + ". Эй, парни, уберите этого выскочку.";
                    }
                    Link.l1.go = "City";
                }
            }
            if (!isCityHasFort(NPChar.City))
            {
                Link.l2 = "Десант эскадры? Хм... Заплати мне - и мы покинем этот город.";
            }
            else
            {
                Link.l2 = "Эскадра... Хммм... Заплати мне - и мы покинем этот город.";
            }
            Link.l2.go = "Summ";

            bOk = !bWorldAlivePause || bBettaTestMode;
            if (isMainCharacterPatented() && bOk && !CheckAttribute(&colonies[iColony], "notCaptured")) //не даем захватить колонию
            {
                // восстановим нацию патента
                PChar.nation = GetBaseHeroNation();

                dialog.Text = "Это неслыханная наглость! Как вы посмели напасть на колонию, принадлежащую " + NationNameGenitive(sti(NPChar.nation)) + "?! Вы дорого заплатите за кровь, бессмысленно пролитую вами, и за ущерб, нанесённый нашей державе.";
                Link.l1 = "С этого момента колония принадлежит мне, а если кто-то попытается в этом усомниться, то отправится прямиком на небеса.";
                Link.l1.go = "City_patent";
                Link.l2 = "Я представляю интересы " + NationNameGenitive(sti(PChar.nation)) + " и официально заявляю, что отныне эта колония принадлежит " + NationKingsCrown(PChar) + "!";
                Link.l2.go = "City_nation";
                Link.l3 = "Нам следует обсудить размеры выкупа. Если же вы будете упрямствовать, то мы превратим ваш чудесный город в груду пепла, а вас повесим на городской площади.";
                Link.l3.go = "Summ_patent";
            }
        }
        break;

    // --> Левассер
    case "levasser":
        dialog.Text = "Пуанси?! Проклятый старый хрыч! С ним я ещё разберусь, а тебе пришёл конец, негодяй! Я лично позабочусь о том, чтобы ты не вышел отсюда живым!";
        Link.l1 = "Меньше слов, старый развратник! К бою!";
        Link.l1.go = "levasser_1";
        break;

    case "levasser_1":
        chrDisableReloadToLocation = true; //закрыть локацию
        DialogExit();
        LAi_SetImmortal(npchar, false);
        ChangeCharacterAddressGroup(npchar, pchar.location, "goto", "goto6");
        LAi_SetWarriorType(npchar);
        LAi_group_MoveCharacter(npchar, "EnemyFight");
        LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
        LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
        LAi_group_SetCheck("EnemyFight", "LevasserDiedResidence");
        AddDialogExitQuest("MainHeroFightModeOn");
        break;
        // <-- Левассер

    case "City":
        ChangeCharacterHunterScore(GetMainCharacter(), NationShortName(sti(NPChar.nation)) + "hunter", 40);
        AddCharacterExpToSkill(GetMainCharacter(), "Leadership", 300);

        Pchar.GenQuestFort.fortCharacterIdx = FortChref.index;
        AddDialogExitQuest("Residence_Captured_Any");

        Statistic_AddValue(Pchar, NationShortName(sti(NPChar.nation)) + "_TakeTown", 1);
        // ремонт
        RepairAllShips();
        Log_Info("Все корабли отремонтированы.");
        //  СЖ -->
        ReOpenQuestHeader("Gen_CityCapture");
        AddQuestRecord("Gen_CityCapture", "t3");
        AddQuestUserData("Gen_CityCapture", "sSex", GetSexPhrase("", "а"));
        AddQuestUserData("Gen_CityCapture", "sCity", XI_ConvertString("colony" + NPChar.City));
        //  СЖ <--
        NextDiag.CurrentNode = "Prison";
        DialogExit();
        break;

    case "City_patent":
        ChangeCharacterComplexReputation(GetMainCharacter(), "nobility", -20); // пираты мы, но у нас патент
        dialog.Text = "На этот раз ваша взяла, но знайте, скоро прибудет наша эскадра, и от вас мокрого места не останется.";
        Link.l1 = "Поговори ещё! Эта колония отныне принадлежит мне, а вашу эскадру я отправлю на свидание к морскому дьяволу. Эй, парни, возьмите эту свинку и посадите за решетку.";
        Link.l1.go = "City";
        break;

    case "Exit_for_pay":
        dialog.Text = "Что вам от меня ещё нужно?";
        Link.l1 = "Смотрю, всё ли я забрал" + GetSexPhrase("", "а") + "...";
        Link.l1.go = "exit";

        NextDiag.TempNode = "Exit_for_pay";
        break;

    case "Exit_City":
        NextDiag.CurrentNode = "Exit_for_pay";
        Pchar.GenQuestFort.fortCharacterIdx = FortChref.index;
        if (sti(NPChar.NoGiveMoney) == false) // себе берем
        {
            // вернем диалог после разговора и спрячем
            SetReturn_Gover_Dialog_Exit(NPChar);
            AddDialogExitQuestFunction("TWN_ExitForPay");
        }
        DialogExit();
        break;

    case "Summ":
        dialog.Text = "Мне больше ничего не остается, как согласиться на ваши условия. Забирайте свои кровавые деньги и немедленно покиньте воды нашей колонии.";
        Link.l1 = "Позвольте откланяться.";
        Link.l1.go = "Exit_City";
        NPChar.NoGiveMoney = false;

        ChangeCharacterHunterScore(GetMainCharacter(), NationShortName(sti(NPChar.nation)) + "hunter", 30);
        AddCharacterExpToSkill(GetMainCharacter(), SKILL_FORTUNE, 200);
        AddCharacterExpToSkill(GetMainCharacter(), "Commerce", 200);

        Statistic_AddValue(Pchar, NationShortName(sti(NPChar.nation)) + "_GrabbingTown", 1);
        //  СЖ -->
        ReOpenQuestHeader("Gen_CityCapture");
        AddQuestRecord("Gen_CityCapture", "t2");
        AddQuestUserData("Gen_CityCapture", "sSex", GetSexPhrase("", "а"));
        AddQuestUserData("Gen_CityCapture", "sCity", XI_ConvertString("colony" + NPChar.City));
        //  СЖ <--
        break;

    case "Summ_patent":
        dialog.Text = "Хорошо, вы можете диктовать свои условия...";
        Link.l1 = "Да, по праву победителя. Где мои деньги?";
        Link.l1.go = "Summ";
        ChangeCharacterComplexReputation(GetMainCharacter(), "nobility", -10); // не на службе
        break;

    case "City_nation":
        dialog.Text = "Что ж, мы отдаёмся на милость победителей.";
        Link.l1 = "Советую вам побыстрее покинуть пределы города, ещё неизвестно, как на вашем здоровье отразятся грядущие перемены. Прощайте.";
        Link.l1.go = "Exit_City";
        NPChar.NoGiveMoney = true;

        ChangeCharacterComplexReputation(GetMainCharacter(), "nobility", 5);
        AddCharacterExpToSkill(GetMainCharacter(), "Leadership", 500);
        AddCharacterExpToSkill(GetMainCharacter(), "Sneak", 300);
        SetNationRelationBoth(sti(PChar.nation), sti(NPChar.nation), RELATION_ENEMY);

        PChar.questTemp.DontSetNewDialogToMayor = true; // иначе может сменить диалог и сбойнуть
        PChar.questTemp.DontNullDeposit = true;         // чтоб не нулили ростовщика
        SetCaptureTownByNation(NPChar.City, sti(PChar.nation));
        DeleteAttribute(PChar, "questTemp.DontSetNewDialogToMayor");
        AddDialogExitQuestFunction("LaunchColonyInfoScreen"); // табличка
                                                              //  СЖ -->
        sTemp = GetNationNameByType(sti(PChar.nation));
        ReOpenQuestHeader("Gen_CityCapture");
        AddQuestRecord("Gen_CityCapture", "t1");
        AddQuestUserData("Gen_CityCapture", "sCity", XI_ConvertString("colony" + NPChar.City));
        AddQuestUserData("Gen_CityCapture", "sNation", XI_ConvertString(sTemp + "Gen"));
        //  СЖ <--
        AddTitleNextRate(sti(PChar.nation), 1);                                                   // счетчик звания
        SetCharacterRelationBoth(sti(FortChref.index), GetMainCharacterIndex(), RELATION_FRIEND); // нечего не дает, тк работает OtherChar - а это губер, но он и так друг
        UpdateRelations();

        // 22.03.05  fix вернем диалог после разговора и спрячем
        //  внутри диалога не работало
        SetReturn_Gover_Dialog_Exit(NPChar);

        Statistic_AddValue(Pchar, NationShortName(sti(NPChar.nation)) + "_TakeTown", 1);
        break;

    case "Prison":
        dialog.Text = "Что вам от меня ещё надо, негодяй" + GetSexPhrase("", "ка") + "?";
        Link.l3 = "Посмотрел" + GetSexPhrase("", "а") + ", как ваше сиятельство поживает. Ну, а теперь мне пора!";
        Link.l3.go = "exit";
        NextDiag.TempNode = "Prison";
        break;

    case "arestFree_1":
        dialog.text = "Уладить? Как вы себе это представляете?";
        link.l1 = "Я думаю, сумма в " + iTotalTemp * 6000 + " песо может меня спасти?";
        link.l1.go = "arestFree_2";
        link.l2 = "Никак, мне пора. Всего доброго.";
        link.l2.go = "arest_1";
        break;

    case "arestFree_2":
        if (GetCharacterSkillToOld(PChar, SKILL_FORTUNE) >= drand(7) && iTotalTemp < 21)
        {
            dialog.text = "Пожалуй, можно уладить наш инцидент таким способом. Вы ещё не успели зайти так далеко, чтобы ситуация стала непоправимой.";
            link.l1 = "Замечательно! Я очень рад. Вот, возьмите моё пожертвование.";
            link.l1.go = "Exit";
            AddMoneyToCharacter(pchar, -iTotalTemp * 6000);
            ChangeCharacterHunterScore(Pchar, NationShortName(sti(NPChar.nation)) + "hunter", -iTotalTemp);
            AddCharacterExpToSkill(pchar, "Fortune", 100);
        }
        else
        {
            dialog.text = "Вы предлагаете мне мзду? О, нет! Ваши злодеяния можно искупить единственным способом... Стража! Отведите е" + GetSexPhrase("го", "ё") + " в тюрьму!";
            link.l1 = "Постойте!";
            link.l1.go = "arest_2";
            AddCharacterExpToSkill(pchar, "Fortune", 10);
        }
        break;

    case "arest_1":
        dialog.text = "Конечно пора, вас проводят. Стража! Взять е" + GetSexPhrase("го", "ё") + "!";
        link.l1 = "Ну, уж нет!";
        link.l1.go = "fight";
        break;

    case "arest_2":
        dialog.text = "Раньше надо было думать! Стража!";
        link.l1 = "Ну, уж нет! Просто так вы меня не возьмёте !";
        link.l1.go = "fight";
        break;
    /////////////////////////////////////////////////////////////////////////////////////////////////
    //    Уничтожение банды
    /////////////////////////////////////////////////////////////////////////////////////////////////
    case "DestroyGang":
        dialog.text = "Естественно. На выполнение этого задания я даю вам " + FindRussianDaysString(sti(pchar.GenQuest.DestroyGang.Terms)) + ", ваше вознаграждение за проделанную работу будет составлять " + FindRussianMoneyString(sti(pchar.GenQuest.DestroyGang.Money)) + ".";
        link.l1 = "Хорошо, я берусь за это задание.";
        link.l1.go = "DestroyGang_agree";
        link.l2 = "Хм... нет, пожалуй, я откажусь.";
        link.l2.go = "All_disagree";
        break;
    case "DestroyGang_agree":
        npchar.greeting = NationShortName(sti(npchar.nation)) + "_gov_complete";
        pchar.GenQuest.questName = "DestroyGang";                      //тип квеста
        pchar.GenQuest.DestroyGang.Location = GetGangLocation(npchar); //определяем локацию,где банда
        pchar.GenQuest.DestroyGang.MayorId = npchar.id;                //Id мэра, чтобы знать, кто дал квест
        if (pchar.GenQuest.DestroyGang.Location == "none")             //на всякий случай
        {
            dialog.text = "Подождите, я совсем забыл о вчерашнем докладе! Дело в том, что эта банда уже покинула пределы нашего острова. Так что я отменяю задание.";
            link.l1 = "Понятно. Ну что же, очень жаль.";
            link.l1.go = "exit";
            DeleteAttribute(pchar, "GenQuest." + pchar.GenQuest.questName);
            DeleteAttribute(pchar, "GenQuest.questName");
        }
        else
        {
            dialog.text = "Ну что же, великолепно! Жду вас у себя в резиденции с результатами работы.";
            link.l1 = "Полагаю, что не заставлю вас долго ждать, " + GetAddress_FormToNPC(NPChar) + ".";
            link.l1.go = "exit";
            pchar.quest.DestroyGang.win_condition.l1 = "location";
            pchar.quest.DestroyGang.win_condition.l1.location = pchar.GenQuest.DestroyGang.Location;
            pchar.quest.DestroyGang.win_condition = "DestroyGang_fight";
            pchar.quest.DestroyGang.again = true; //тупо дожидаться своего часа бандиты не будут
            SetTimerCondition("AllMayorsQuests_Late", 0, 0, sti(pchar.GenQuest.DestroyGang.Terms), false);
            //==> энкаунтеров в квестовой локации не будет
            locations[FindLocation(pchar.GenQuest.DestroyGang.Location)].DisableEncounters = true;
            ReOpenQuestHeader("MayorsQuestsList");
            AddQuestRecord("MayorsQuestsList", "1");
            AddQuestUserData("MayorsQuestsList", "ColonyName", XI_ConvertString("Colony" + npchar.city + "Gen"));
            AddQuestUserData("MayorsQuestsList", "MayorName", GetFullName(npchar));
            makearef(arName, pchar.GenQuest.DestroyGang);
            AddQuestUserData("MayorsQuestsList", "GangName", GetFullName(arName));
            AddQuestUserData("MayorsQuestsList", "sDay", FindRussianDaysString(sti(pchar.GenQuest.DestroyGang.Terms)));
            AddQuestUserData("MayorsQuestsList", "sMoney", FindRussianMoneyString(sti(pchar.GenQuest.DestroyGang.Money)));
        }
        break;
    /////////////////////////////////////////////////////////////////////////////////////////////////
    //    Контркурьер
    /////////////////////////////////////////////////////////////////////////////////////////////////
    case "TakePostcureer":
        //установка параметров
        pchar.GenQuest.questName = "TakePostcureer";                            //тип квеста
        pchar.GenQuest.TakePostcureer.Nation = GetEnemyNationToMainCharacter(); //вражеская нация
        while (sti(pchar.GenQuest.TakePostcureer.Nation) == PIRATE)
            pchar.GenQuest.TakePostcureer.Nation = GetEnemyNationToMainCharacter();
        pchar.GenQuest.TakePostcureer.City = FindEnemyCityToMC(false);
        pchar.GenQuest.TakePostcureer.Island = GetArealByCityName(pchar.GenQuest.TakePostcureer.City);
        pchar.GenQuest.TakePostcureer.Terms = GetMaxDaysFromIsland2Island(Islands[GetCharacterCurrentIsland(PChar)].id, pchar.GenQuest.TakePostcureer.Island) + 5;
        pchar.GenQuest.TakePostcureer.LoginDay = sti(pchar.GenQuest.TakePostcureer.Terms) - 1;
        pchar.GenQuest.TakePostcureer.ShipType = SelectCureerShipType();
        pchar.GenQuest.TakePostcureer.ShipName = GenerateRandomNameToShip(sti(pchar.GenQuest.TakePostcureer.Nation));
        pchar.GenQuest.TakePostcureer.Cannon = SelectLevelCannonParameter(sti(pchar.GenQuest.TakePostcureer.ShipType));
        pchar.GenQuest.TakePostcureer.Money = ((dRand(5) + drand(6) + 4) * 1000) + (sti(pchar.rank) * 500);
        dialog.text = "Конечно. Вам необходимо найти курьерский корабль " + NationNameGenitive(sti(pchar.GenQuest.TakePostcureer.Nation)) + " под названием '" + pchar.GenQuest.TakePostcureer.ShipName + "', абордировать его и привезти мне бумаги, которые найдёте в капитанской каюте. Указанное мной судно будет проходить у " + XI_ConvertString("Colony" + pchar.GenQuest.TakePostcureer.City + "Gen") + " примерно через " + FindRussianDaysString(pchar.GenQuest.TakePostcureer.Terms) + ".";
        link.l1 = "Хорошо, я берусь за это задание. А что за бумаги следует искать?";
        link.l1.go = "TakePostcureer_agree";
        link.l2 = "Хм... нет, пожалуй, я откажусь.";
        link.l2.go = "All_disagree";
        break;

    case "TakePostcureer_agree":
        npchar.greeting = NationShortName(sti(npchar.nation)) + "_gov_complete";
        pchar.GenQuest.TakePostcureer.MayorId = npchar.id; //Id мэра, чтобы знать, кто дал квест
        dialog.text = "Почтовую корреспонденцию. Там, среди прочего, будут содержаться очень важные для меня документы. Но вам копаться в бумагах не нужно, просто доставьте мне весь пакет целиком. За эту услугу я заплачу вам " + FindRussianMoneyString(sti(pchar.GenQuest.TakePostcureer.Money)) + "\nИтак, я жду вас у себя в резиденции с результатами работы.";
        link.l1 = "Полагаю, что не заставлю вас долго ждать, " + GetAddress_FormToNPC(NPChar) + ".";
        link.l1.go = "exit";
        pchar.quest.TakePostcureer.win_condition.l1 = "location";
        pchar.quest.TakePostcureer.win_condition.l1.location = pchar.GenQuest.TakePostcureer.Island;
        pchar.quest.TakePostcureer.win_condition.l2 = "Timer";
        pchar.quest.TakePostcureer.win_condition.l2.date.hour = sti(GetTime());
        pchar.quest.TakePostcureer.win_condition.l2.date.day = GetAddingDataDay(0, 0, sti(pchar.GenQuest.TakePostcureer.LoginDay));
        pchar.quest.TakePostcureer.win_condition.l2.date.month = GetAddingDataMonth(0, 0, sti(pchar.GenQuest.TakePostcureer.LoginDay));
        pchar.quest.TakePostcureer.win_condition.l2.date.year = GetAddingDataYear(0, 0, sti(pchar.GenQuest.TakePostcureer.LoginDay));
        pchar.quest.TakePostcureer.function = "TakePostcureer_CreateShip";
        SetTimerCondition("AllMayorsQuests_Late", 0, 0, sti(pchar.GenQuest.TakePostcureer.Terms), false);
        ReOpenQuestHeader("MayorsQuestsList");
        AddQuestRecord("MayorsQuestsList", "3");
        AddQuestUserData("MayorsQuestsList", "ColonyName", XI_ConvertString("Colony" + npchar.city + "Gen"));
        AddQuestUserData("MayorsQuestsList", "MayorName", GetFullName(npchar));
        AddQuestUserData("MayorsQuestsList", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.TakePostcureer.City + "Gen"));
        AddQuestUserData("MayorsQuestsList", "sDay", FindRussianDaysString(sti(pchar.GenQuest.TakePostcureer.Terms)));
        AddQuestUserData("MayorsQuestsList", "sMoney", FindRussianMoneyString(sti(pchar.GenQuest.TakePostcureer.Money)));
        AddQuestUserData("MayorsQuestsList", "sNation", NationNameGenitive(sti(pchar.GenQuest.TakePostcureer.Nation)));
        AddQuestUserData("MayorsQuestsList", "sShipName", pchar.GenQuest.TakePostcureer.ShipName);
        break;

    /////////////////////////////////////////////////////////////////////////////////////////////////
    //    Контрфрахт - уничтожить корабль с арсеналом
    /////////////////////////////////////////////////////////////////////////////////////////////////
    case "TakeArsenalship":
        //установка параметров
        pchar.GenQuest.questName = "TakeArsenalship";                            //тип квеста
        pchar.GenQuest.TakeArsenalship.Nation = GetEnemyNationToMainCharacter(); //вражеская нация
        while (sti(pchar.GenQuest.TakeArsenalship.Nation) == PIRATE)
            pchar.GenQuest.TakeArsenalship.Nation = GetEnemyNationToMainCharacter();
        pchar.GenQuest.TakeArsenalship.City = FindEnemyCityToMC(false);
        pchar.GenQuest.TakeArsenalship.Island = GetArealByCityName(pchar.GenQuest.TakeArsenalship.City);
        pchar.GenQuest.TakeArsenalship.Terms = GetMaxDaysFromIsland2Island(Islands[GetCharacterCurrentIsland(PChar)].id, pchar.GenQuest.TakeArsenalship.Island) + 5;
        pchar.GenQuest.TakeArsenalship.LoginDay = sti(pchar.GenQuest.TakeArsenalship.Terms) - 1;
        pchar.GenQuest.TakeArsenalship.ShipType = SelectArsenalShipType();
        pchar.GenQuest.TakeArsenalship.ShipTypeA = SelectCureerShipType();
        pchar.GenQuest.TakeArsenalship.ShipName = GenerateRandomNameToShip(sti(pchar.GenQuest.TakeArsenalship.Nation));
        pchar.GenQuest.TakeArsenalship.Cannon = SelectLevelCannonParameter(sti(pchar.GenQuest.TakeArsenalship.ShipType));
        pchar.GenQuest.TakeArsenalship.CannonA = SelectLevelCannonParameter(sti(pchar.GenQuest.TakeArsenalship.ShipTypeA)); // Addon 2016-1 Jason пиратская линейка
        pchar.GenQuest.TakeArsenalship.Money = ((dRand(5) + drand(6) + 4) * 900) + (sti(pchar.rank) * 500);
        dialog.text = "Конечно. Вам будет необходимо найти военный транспорт " + NationNameGenitive(sti(pchar.GenQuest.TakeArsenalship.Nation)) + ", перевозящий порох и боеприпасы, судно под названием '" + pchar.GenQuest.TakeArsenalship.ShipName + "', и уничтожить его. Этим мы нанесём ущерб вражеской державе\nУказанный транспорт будет идти в составе эскорта в колонию " + XI_ConvertString("Colony" + pchar.GenQuest.TakeArsenalship.City) + ", и будет там примерно через " + FindRussianDaysString(pchar.GenQuest.TakeArsenalship.Terms) + ", так что вам следует поторопиться.";
        link.l1 = "Хорошо, я берусь за это задание. Мне нужно потопить или захватить судно с арсеналом?";
        link.l1.go = "TakeArsenalship_agree";
        link.l2 = "Хм... нет, пожалуй, я откажусь.";
        link.l2.go = "All_disagree";
        break;

    case "TakeArsenalship_agree":
        npchar.greeting = NationShortName(sti(npchar.nation)) + "_gov_complete";
        pchar.GenQuest.TakeArsenalship.MayorId = npchar.id; //Id мэра, чтобы знать, кто дал квест
        dialog.text = "Как хотите, для меня это значения не имеет. Главное - чтобы груз не пришёл по назначению. Если вы справитесь с этим поручением, я заплачу вам " + FindRussianMoneyString(sti(pchar.GenQuest.TakeArsenalship.Money)) + "... Более не задерживаю вас, капитан.";
        link.l1 = "Полагаю, что не заставлю вас долго ждать, " + GetAddress_FormToNPC(NPChar) + ".";
        link.l1.go = "exit";
        pchar.quest.TakeArsenalship.win_condition.l1 = "location";
        pchar.quest.TakeArsenalship.win_condition.l1.location = pchar.GenQuest.TakeArsenalship.Island;
        pchar.quest.TakeArsenalship.win_condition.l2 = "Timer";
        pchar.quest.TakeArsenalship.win_condition.l2.date.hour = sti(GetTime());
        pchar.quest.TakeArsenalship.win_condition.l2.date.day = GetAddingDataDay(0, 0, sti(pchar.GenQuest.TakeArsenalship.LoginDay));
        pchar.quest.TakeArsenalship.win_condition.l2.date.month = GetAddingDataMonth(0, 0, sti(pchar.GenQuest.TakeArsenalship.LoginDay));
        pchar.quest.TakeArsenalship.win_condition.l2.date.year = GetAddingDataYear(0, 0, sti(pchar.GenQuest.TakeArsenalship.LoginDay));
        pchar.quest.TakeArsenalship.function = "TakeArsenalship_CreateShip";
        SetTimerCondition("AllMayorsQuests_Late", 0, 0, sti(pchar.GenQuest.TakeArsenalship.Terms), false);
        ReOpenQuestHeader("MayorsQuestsList");
        AddQuestRecord("MayorsQuestsList", "8");
        AddQuestUserData("MayorsQuestsList", "ColonyName", XI_ConvertString("Colony" + npchar.city + "Gen"));
        AddQuestUserData("MayorsQuestsList", "MayorName", GetFullName(npchar));
        AddQuestUserData("MayorsQuestsList", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.TakeArsenalship.City));
        AddQuestUserData("MayorsQuestsList", "sDay", FindRussianDaysString(sti(pchar.GenQuest.TakeArsenalship.Terms)));
        AddQuestUserData("MayorsQuestsList", "sMoney", FindRussianMoneyString(sti(pchar.GenQuest.TakeArsenalship.Money)));
        AddQuestUserData("MayorsQuestsList", "sNation", NationNameGenitive(sti(pchar.GenQuest.TakeArsenalship.Nation)));
        AddQuestUserData("MayorsQuestsList", "sShipName", pchar.GenQuest.TakeArsenalship.ShipName);
        break;

    /////////////////////////////////////////////////////////////////////////////////////////////////
    //    ОЗГ - уничтожить корабль пиратов
    /////////////////////////////////////////////////////////////////////////////////////////////////
    case "TakePirateship":
        //установка параметров
        pchar.GenQuest.questName = "TakePirateship"; //тип квеста
        pchar.GenQuest.TakePirateship.City = FindEnemyCityToMC(false);
        pchar.GenQuest.TakePirateship.Island = GetArealByCityName(pchar.GenQuest.TakePirateship.City);
        pchar.GenQuest.TakePirateship.Terms = GetMaxDaysFromIsland2Island(Islands[GetCharacterCurrentIsland(PChar)].id, pchar.GenQuest.TakePirateship.Island) + 5;
        pchar.GenQuest.TakePirateship.ShipType = SelectCureerShipType();
        pchar.GenQuest.TakePirateship.ShipName = GenerateRandomNameToShip(PIRATE);
        pchar.GenQuest.TakePirateship.Name = GenerateRandomName(PIRATE, "man");
        pchar.GenQuest.TakePirateship.Cannon = SelectLevelCannonParameter(sti(pchar.GenQuest.TakePirateship.ShipType));
        pchar.GenQuest.TakePirateship.Money = ((dRand(5) + drand(6) + 4) * 1200) + (sti(pchar.rank) * 500);
        dialog.text = "Безусловно. Меня буквально выводит из себя бурная деятельность одного пиратского капитана по имени " + pchar.GenQuest.TakePirateship.Name + ". Мерзавец повадился грабить корабли наших купцов, и очень мешает торговле между колониями. Сейчас момент для расправы с этим негодяем как нельзя удачный, поскольку мне стало известно место, где он в данное время скрывается. Вы готовы отправиться в путь и покончить с врагом нашей короны?";
        link.l1 = "Почту за честь! Где искать этого богоотступника?";
        link.l1.go = "TakePirateship_agree";
        link.l2 = "Хм... нет, пожалуй, я откажусь.";
        link.l2.go = "All_disagree";
        break;

    case "TakePirateship_agree":
        npchar.greeting = NationShortName(sti(npchar.nation)) + "_gov_complete";
        pchar.GenQuest.TakePirateship.MayorId = npchar.id; //Id мэра, чтобы знать, кто дал квест
        dialog.text = "В ближайшие " + FindRussianDaysString(pchar.GenQuest.TakePirateship.Terms) + " его корабль под названием '" + pchar.GenQuest.TakePirateship.ShipName + "' будет крейсировать у берегов недалеко от " + XI_ConvertString("Colony" + pchar.GenQuest.TakePirateship.City + "Gen") + ". Найдите его и уничтожьте. Отправьте на корм рыбам вместе с кораблем, возьмите на абордаж - мне всё равно, лишь бы этот треклятый пират перестал осквернять землю своим присутствием\nЗа выполнение этой задачи я готов заплатить вам " + FindRussianMoneyString(sti(pchar.GenQuest.TakePirateship.Money)) + ". Не теряйте времени, капитан: негодяй не будет ждать вас у " + XI_ConvertString("Colony" + pchar.GenQuest.TakePirateship.City + "Gen") + " вечно. Ступайте, и да поможет вам Бог!";
        link.l1 = "Уже поднимаю якоря, " + GetAddress_FormToNPC(NPChar) + "! Результат не заставит себя долго ждать!";
        link.l1.go = "exit";
        pchar.quest.TakePirateship.win_condition.l1 = "location";
        pchar.quest.TakePirateship.win_condition.l1.location = pchar.GenQuest.TakePirateship.Island;
        pchar.quest.TakePirateship.function = "TakePirateship_CreateShip";
        SetTimerCondition("AllMayorsQuests_Late", 0, 0, sti(pchar.GenQuest.TakePirateship.Terms), false);
        ReOpenQuestHeader("MayorsQuestsList");
        AddQuestRecord("MayorsQuestsList", "9");
        AddQuestUserData("MayorsQuestsList", "ColonyName", XI_ConvertString("Colony" + npchar.city + "Gen"));
        AddQuestUserData("MayorsQuestsList", "MayorName", GetFullName(npchar));
        AddQuestUserData("MayorsQuestsList", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.TakePirateship.City + "Gen"));
        AddQuestUserData("MayorsQuestsList", "sDay", FindRussianDaysString(sti(pchar.GenQuest.TakePirateship.Terms)));
        AddQuestUserData("MayorsQuestsList", "sMoney", FindRussianMoneyString(sti(pchar.GenQuest.TakePirateship.Money)));
        AddQuestUserData("MayorsQuestsList", "sName", pchar.GenQuest.TakePirateship.Name);
        AddQuestUserData("MayorsQuestsList", "sShipName", pchar.GenQuest.TakePirateship.ShipName);
        break;

    /////////////////////////////////////////////////////////////////////////////////////////////////
    //    ОЗГ - захватить пассажира
    /////////////////////////////////////////////////////////////////////////////////////////////////
    case "TakePassenger":
        //установка параметров
        pchar.GenQuest.questName = "TakePassenger"; //тип квеста
        pchar.GenQuest.TakePassenger.City = FindEnemyCityToMC(false);
        pchar.GenQuest.TakePassenger.CityA = SelectAnyColony(pchar.GenQuest.TakePassenger.City);
        pchar.GenQuest.TakePassenger.Nation = GetEnemyNationToMainCharacter(); //вражеская нация
        while (sti(pchar.GenQuest.TakePassenger.Nation) == PIRATE)
            pchar.GenQuest.TakePassenger.Nation = GetEnemyNationToMainCharacter();
        pchar.GenQuest.TakePassenger.Terms1 = GetMaxDaysFromIsland2Island(Islands[GetCharacterCurrentIsland(PChar)].id, GetArealByCityName(pchar.GenQuest.TakePassenger.City));
        pchar.GenQuest.TakePassenger.Terms2 = GetMaxDaysFromIsland2Island(GetArealByCityName(pchar.GenQuest.TakePassenger.City), GetArealByCityName(pchar.GenQuest.TakePassenger.CityA)) + 1;
        pchar.GenQuest.TakePassenger.Terms = sti(pchar.GenQuest.TakePassenger.Terms1) + sti(pchar.GenQuest.TakePassenger.Terms2);
        pchar.GenQuest.TakePassenger.ShipType = SelectCureerShipType();
        pchar.GenQuest.TakePassenger.ShipName = GenerateRandomNameToShip(sti(pchar.GenQuest.TakePassenger.Nation));
        pchar.GenQuest.TakePassenger.Name = GenerateRandomName(sti(pchar.GenQuest.TakePassenger.Nation), "man");
        pchar.GenQuest.TakePassenger.Cannon = SelectLevelCannonParameter(sti(pchar.GenQuest.TakePassenger.ShipType));
        pchar.GenQuest.TakePassenger.Money = ((dRand(5) + drand(6) + 4) * 1100) + (sti(pchar.rank) * 500);
        string sText = SelectPassText();
        dialog.text = "Безусловно. Речь пойдёт о мерзавце по имени " + pchar.GenQuest.TakePassenger.Name + ". " + sText + " Я давно разыскиваю его, и, наконец, мне удалось получить достоверные сведения, где его искать. Мне нужно, чтобы вы доставили сюда этого человека, причем живым. Я хочу показательно вздёрнуть его на площади нашего города. Вы готовы взяться за это дело?";
        link.l1 = "Готов, " + GetAddress_FormToNPC(NPChar) + ". Где мне искать этого негодяя?";
        link.l1.go = "TakePassenger_agree";
        link.l2 = "Хм... нет, пожалуй, я откажусь.";
        link.l2.go = "All_disagree";
        break;

    case "TakePassenger_agree":
        npchar.greeting = NationShortName(sti(npchar.nation)) + "_gov_complete";
        pchar.GenQuest.TakePassenger.MayorId = npchar.id; //Id мэра, чтобы знать, кто дал квест
        dialog.text = "Буквально через " + FindRussianDaysString(pchar.GenQuest.TakePassenger.Terms1) + ", он, в качестве пассажира, на корабле под названием '" + pchar.GenQuest.TakePassenger.ShipName + "', выйдет из " + XI_ConvertString("Colony" + pchar.GenQuest.TakePassenger.City + "Gen") + " и отправится в " + XI_ConvertString("Colony" + pchar.GenQuest.TakePassenger.CityA + "Acc") + ". У вас в распоряжении не более " + FindRussianDaysString(pchar.GenQuest.TakePassenger.Terms) + ", чтобы найти этот корабль на указанном отрезке пути, взять на абордаж и захватить уже известного вам мерзавца в плен. Если вы выполните это поручение, я заплачу вам " + FindRussianMoneyString(sti(pchar.GenQuest.TakePassenger.Money)) + ". Желаю удачи, капитан!";
        link.l1 = "Не буду терять времени, " + GetAddress_FormToNPC(NPChar) + "! Немедленно отправляюсь в путь.";
        link.l1.go = "exit";
        SetFunctionTimerCondition("TakePassenger_CreateShip", 0, 0, sti(pchar.GenQuest.TakePassenger.Terms1), false);
        SetTimerCondition("AllMayorsQuests_Late", 0, 0, sti(pchar.GenQuest.TakePassenger.Terms), false);
        ReOpenQuestHeader("MayorsQuestsList");
        AddQuestRecord("MayorsQuestsList", "10");
        AddQuestUserData("MayorsQuestsList", "ColonyName", XI_ConvertString("Colony" + npchar.city + "Gen"));
        AddQuestUserData("MayorsQuestsList", "MayorName", GetFullName(npchar));
        AddQuestUserData("MayorsQuestsList", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.TakePassenger.City + "Gen"));
        AddQuestUserData("MayorsQuestsList", "sCityA", XI_ConvertString("Colony" + pchar.GenQuest.TakePassenger.CityA + "Acc"));
        AddQuestUserData("MayorsQuestsList", "sDay1", FindRussianDaysString(sti(pchar.GenQuest.TakePassenger.Terms1)));
        AddQuestUserData("MayorsQuestsList", "sDay2", FindRussianDaysString(sti(pchar.GenQuest.TakePassenger.Terms)));
        AddQuestUserData("MayorsQuestsList", "sMoney", FindRussianMoneyString(sti(pchar.GenQuest.TakePassenger.Money)));
        AddQuestUserData("MayorsQuestsList", "sName", pchar.GenQuest.TakePassenger.Name);
        AddQuestUserData("MayorsQuestsList", "sShipName", pchar.GenQuest.TakePassenger.ShipName);
        break;

    /////////////////////////////////////////////////////////////////////////////////////////////////
    //    Таможенный патруль
    /////////////////////////////////////////////////////////////////////////////////////////////////
    case "CustomPatrol":
        //установка параметров
        pchar.GenQuest.questName = "CustomPatrol";               //тип квеста
        pchar.GenQuest.CustomPatrol.Nation = sti(npchar.nation); //нация
        pchar.GenQuest.CustomPatrol.Island = Islands[GetCharacterCurrentIsland(PChar)].id;
        pchar.GenQuest.CustomPatrol.LoginDay = rand(4) + 1;
        pchar.GenQuest.CustomPatrol.Loginlocator = rand(3) + 4;
        pchar.GenQuest.CustomPatrol.ShipType = SelectCureerShipType();
        pchar.GenQuest.CustomPatrol.ShipTypeA = SelectCureerShipType();
        pchar.GenQuest.CustomPatrol.Cannon = SelectLevelCannonParameter(sti(pchar.GenQuest.CustomPatrol.ShipType));
        pchar.GenQuest.CustomPatrol.Money = ((dRand(5) + drand(6) + 4) * 700) + (sti(pchar.rank) * 300);
        dialog.text = "Я получил достоверные сведения о том, что некий капитан договорился о сделке с негодяями-контрабандистами о продаже партии рабов. Как вам должно быть известно, сделки такого рода частными лицами в нашей колонии являются контрабандой\nПроблема заключается в том, что я не знаю ни точного времени, ни даты, ни места, где контрабандисты будут встречаться. Известно лишь то, что преступная сделка будет совершена в течение ближайших пяти дней на нашем острове. Как назло, все мои патрульные корабли сейчас либо на ремонте, либо задействованы для других задач и не могут караулить негодяев\nЯ предлагаю вам заняться этим вопросом - выследить контрабандистов и разобраться с ними самыми радикальными методами, чтобы другим неповадно было. Вы готовы выполнить это поручение?";
        link.l1 = "Готов, " + GetAddress_FormToNPC(NPChar) + ". Скажите, может, есть какие-то зацепки, например, имя капитана, тип или название его судна?";
        link.l1.go = "CustomPatrol_agree";
        link.l2 = "Хм... нет, пожалуй, я откажусь.";
        link.l2.go = "All_disagree";
        break;

    case "CustomPatrol_agree":
        npchar.greeting = NationShortName(sti(npchar.nation)) + "_gov_complete";
        pchar.GenQuest.CustomPatrol.MayorId = npchar.id; //Id мэра, чтобы знать, кто дал квест
        dialog.text = "Мой источник сказал лишь то, что сделка готовится и обязательно состоится. И это всё. Так что вам надлежит внимательно смотреть за всеми подозрительными кораблями, которые появятся в нашей акватории. Если вы успешно справитесь с этим, то я заплачу вам вознаграждение в размере " + FindRussianMoneyString(sti(pchar.GenQuest.CustomPatrol.Money)) + "\nКроме того, учитывая сложившиеся обстоятельства, я разрешаю вам забрать себе весь контрабандный груз, который вы найдёте. Неофициально, конечно, и при условии, что вы не станете сбывать его в нашем городе.";
        link.l1 = "Ну что же, я приступаю к патрулированию вод вашей колонии, " + GetAddress_FormToNPC(NPChar) + ".";
        link.l1.go = "exit";
        SetTimerCondition("AllMayorsQuests_Late", 0, 0, 6, false);
        pchar.quest.CustomPatrol.win_condition.l1 = "location";
        pchar.quest.CustomPatrol.win_condition.l1.location = pchar.GenQuest.CustomPatrol.Island;
        pchar.quest.CustomPatrol.win_condition.l2 = "Timer";
        pchar.quest.CustomPatrol.win_condition.l2.date.hour = sti(GetTime() + rand(8));
        pchar.quest.CustomPatrol.win_condition.l2.date.day = GetAddingDataDay(0, 0, sti(pchar.GenQuest.CustomPatrol.LoginDay));
        pchar.quest.CustomPatrol.win_condition.l2.date.month = GetAddingDataMonth(0, 0, sti(pchar.GenQuest.CustomPatrol.LoginDay));
        pchar.quest.CustomPatrol.win_condition.l2.date.year = GetAddingDataYear(0, 0, sti(pchar.GenQuest.CustomPatrol.LoginDay));
        pchar.quest.CustomPatrol.function = "CustomPatrol_CreateShip";
        ReOpenQuestHeader("MayorsQuestsList");
        AddQuestRecord("MayorsQuestsList", "11");
        AddQuestUserData("MayorsQuestsList", "ColonyName", XI_ConvertString("Colony" + npchar.city + "Gen"));
        AddQuestUserData("MayorsQuestsList", "MayorName", GetFullName(npchar));
        AddQuestUserData("MayorsQuestsList", "sMoney", FindRussianMoneyString(sti(pchar.GenQuest.CustomPatrol.Money)));
        break;

    /////////////////////////////////////////////////////////////////////////////////////////////////
    //    Найти дезертира
    /////////////////////////////////////////////////////////////////////////////////////////////////
    case "FindFugitive":
        //установка параметров
        pchar.GenQuest.questName = "FindFugitive"; //тип квеста
        pchar.GenQuest.FindFugitive.Startcity = npchar.city;
        pchar.GenQuest.FindFugitive.City = SelectFugitiveCity();
        pchar.GenQuest.FindFugitive.Chance = rand(2);
        pchar.GenQuest.FindFugitive.Name = GenerateRandomName(sti(npchar.Nation), "man");
        pchar.GenQuest.FindFugitive.Money = ((dRand(5) + drand(6) + 4) * 1300) + (sti(pchar.rank) * 600);
        sText = SelectFugitiveText();
        log_testinfo(pchar.GenQuest.FindFugitive.City);
        log_testinfo(FindRussianDaysString(sti(pchar.GenQuest.FindFugitive.Chance)));
        dialog.text = "Расскажу в деталях. Случилась крайне некрасивая история - " + sText + ". Опросив его сослуживцев и знакомых, мы не без оснований считаем, что дезертир укрылся среди пиратов в одном из их поселений\nЯ предлагаю вам посетить пиратские гнёзда, разыскать беглеца, арестовать и доставить сюда: дезертирство - тяжкий проступок, и не может остаться без наказания. Вы готовы взяться за это дело?";
        link.l1 = "Готов, " + GetAddress_FormToNPC(NPChar) + ". Вы можете назвать имя дезертира?";
        link.l1.go = "FindFugitive_agree";
        link.l2 = "Хм... нет, пожалуй, я откажусь.";
        link.l2.go = "All_disagree";
        break;

    case "FindFugitive_agree":
        npchar.greeting = NationShortName(sti(npchar.nation)) + "_gov_complete";
        pchar.GenQuest.FindFugitive.MayorId = npchar.id; //Id мэра, чтобы знать, кто дал квест
        dialog.text = "Да, конечно. Его зовут " + pchar.GenQuest.FindFugitive.Name + ". Сомневаюсь, что он будет одет в свою военную форму, так что внимательней присматривайтесь ко всякому сброду. На поиски я отвожу вам один месяц, так как боюсь, что по истечении этого срока искать беглеца будет уже бессмысленно. Если вы успешно выполните это поручение, я заплачу вам " + FindRussianMoneyString(sti(pchar.GenQuest.FindFugitive.Money)) + ".";
        link.l1 = "Не буду терять времени, " + GetAddress_FormToNPC(NPChar) + "! Немедленно отправляюсь в путь.";
        link.l1.go = "exit";
        SetTimerCondition("AllMayorsQuests_Late", 0, 0, 30, false);
        ReOpenQuestHeader("MayorsQuestsList");
        AddQuestRecord("MayorsQuestsList", "12");
        AddQuestUserData("MayorsQuestsList", "ColonyName", XI_ConvertString("Colony" + npchar.city + "Gen"));
        AddQuestUserData("MayorsQuestsList", "MayorName", GetFullName(npchar));
        AddQuestUserData("MayorsQuestsList", "sMoney", FindRussianMoneyString(sti(pchar.GenQuest.FindFugitive.Money)));
        AddQuestUserData("MayorsQuestsList", "sName", pchar.GenQuest.FindFugitive.Name);
        //создаем дезертира
        sld = GetCharacter(NPC_GenerateCharacter("Fugitive", "citiz_" + (21 + rand(9)), "man", "man", sti(pchar.rank) + MOD_SKILL_ENEMY_RATE, sti(npchar.nation), 30, true, "soldier"));
        SetFantomParamFromRank(sld, sti(pchar.rank) + MOD_SKILL_ENEMY_RATE, true);
        sld.name = pchar.GenQuest.FindFugitive.Name;
        sld.lastname = "";
        sld.dialog.FileName = "MayorQuests_dialog.c";
        sld.greeting = "marginal";
        break;
    /////////////////////////////////////////////////////////////////////////////////////////////////
    //    Проникновение во враждебный город
    /////////////////////////////////////////////////////////////////////////////////////////////////
    case "Intelligence":
        dialog.text = "Я понимаю. Возможно, вознаграждение в " + FindRussianMoneyString(sti(pchar.GenQuest.Intelligence.Money)) + " станет для вас хорошим стимулом.";
        link.l1 = "Да, это хорошие деньги... Я берусь за это задание.";
        link.l1.go = "Intelligence_agree";
        link.l2 = "Хм... нет, пожалуй, я откажусь - слишком опасно.";
        link.l2.go = "All_disagree";
        break;
    case "Intelligence_agree":
        if (pchar.GenQuest.Intelligence.City == "none" || isBadReputation(pchar, 30)) //на всякий случай
        {
            dialog.text = "Хотя, я не могу сказать, что могу доверять вам в полной мере... Пожалуй, я не дам вам это задание.";
            link.l1 = "М-да, однако... Ну что же, очень жаль.";
            link.l1.go = "exit";
            DeleteAttribute(pchar, "GenQuest." + pchar.GenQuest.questName);
        }
        else
        {
            npchar.greeting = NationShortName(sti(npchar.nation)) + "_gov_complete";
            pchar.GenQuest.questName = "Intelligence"; //тип квеста
            sTemp = pchar.GenQuest.Intelligence.City;
            switch (rand(4))
            {
            case 0:
                sTemp += "_Priest";
                break;
            case 1:
                sTemp += "_trader";
                break;
            case 2:
                sTemp += "_shipyarder";
                break;
            case 3:
                sTemp += "_usurer";
                break;
            case 4:
                sTemp += "_PortMan";
                break;
            }
            pchar.GenQuest.Intelligence.SpyId = sTemp; //Id нашего шпиона в городе
            dialog.text = "Прекрасно! Теперь по делу. В " + XI_ConvertString("Colony" + pchar.GenQuest.Intelligence.City + "Dat") + " вам необходимо разыскать местного " + GetWorkTypeOfMan(&characters[GetCharacterIndex(sTemp)], "Gen") +
                          ", его зовут " + GetFullName(&characters[GetCharacterIndex(sTemp)]) + ". Ему вы назовёте моё имя, и получите пакет документов. На доставку этого пакета лично мне в руки я даю вам " + FindRussianDaysString(sti(pchar.GenQuest.Intelligence.Terms)) + ". И имейте в виду, что всё нужно сделать тихо. В случае вашего обнаружения в городе, агент не будет подвергать себя риску и не пойдёт на контакт. Вам всё ясно?";
            link.l1 = "Да, я всё понял" + GetSexPhrase("", "а") + ", " + GetAddress_FormToNPC(NPChar) + ". Немедленно приступаю к выполнению задания.";
            link.l1.go = "exit";
            pchar.GenQuest.Intelligence.MayorId = npchar.id;    //Id мэра, чтобы знать, кто дал квест
            SaveCurrentQuestDateParam("GenQuest.Intelligence"); //запись даты получения квеста
            ReOpenQuestHeader("MayorsQuestsList");
            AddQuestRecord("MayorsQuestsList", "6");
            AddQuestUserData("MayorsQuestsList", "ColonyName", XI_ConvertString("Colony" + npchar.city + "Gen"));
            AddQuestUserData("MayorsQuestsList", "MayorName", GetFullName(npchar));
            AddQuestUserData("MayorsQuestsList", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.Intelligence.City + "Acc"));
            AddQuestUserData("MayorsQuestsList", "sIsland", XI_ConvertString(colonies[FindColony(pchar.GenQuest.Intelligence.City)].islandLable + "Dat"));
            AddQuestUserData("MayorsQuestsList", "sWho", GetWorkTypeOfMan(&characters[GetCharacterIndex(sTemp)], "Gen"));
            AddQuestUserData("MayorsQuestsList", "SpyName", GetFullName(&characters[GetCharacterIndex(sTemp)]));
            AddQuestUserData("MayorsQuestsList", "sDay", FindRussianDaysString(sti(pchar.GenQuest.Intelligence.Terms)));
            AddQuestUserData("MayorsQuestsList", "sMoney", FindRussianMoneyString(sti(pchar.GenQuest.Intelligence.Money)));
            AddQuestUserData("MayorsQuestsList", "sCity2", XI_ConvertString("Colony" + pchar.GenQuest.Intelligence.City + "Dat"));
        }
        break;
    case "Intelligence_ExecuteLate":
        QuestName = pchar.GenQuest.questName;
            pchar.GenQuest.(QuestName).Money = sti(pchar.GenQuest.(QuestName).Money) / 2);
            dialog.text = RandPhraseSimple("Это неплохо. Однако, вы не уложились в отведённые сроки, поэтому я вынужден уменьшить сумму вашего вознаграждения. Ваш гонорар теперь составляет " + FindRussianMoneyString(sti(pchar.GenQuest.(QuestName).Money)) + ". Извольте получить.",
                                           "Это хорошо. Однако вы не уложились в отведённое время, а я ждал это письма раньше. Вы спутали мои планы, поэтому я вынужден сократить сумму вашего гонорара. Итак, я все же рад вручить вам положенное вознаграждение - " + FindRussianMoneyString(sti(pchar.GenQuest.(QuestName).Money)) + ". Извольте получить.");
            link.l1 = "Не сказал" + GetSexPhrase("", "а") + " бы, что мне это приятно, но, в конце концов, установленные сроки действительно были нарушены. Поэтому я претензий не имею, " + GetAddress_FormToNPC(NPChar) + ".";
            link.l1.go = "All_Execute_1";
            //--> слухи
            AddSimpleRumour(RandPhraseSimple("Вы знаете, губернатор " + GetFullName(npchar) + " не очень доволен расторопностью некоего капитана " + GetMainCharacterNameGen() + ".",
                                             "Губернатор " + GetFullName(npchar) + " не очень доволен капитаном " + GetMainCharacterNameDat() + ", т" + GetSexPhrase("от", "а") + " выполнил" + GetSexPhrase("", "а") + " его поручения, но не успел" + GetSexPhrase("", "а") + " в установленные сроки..."),
                            sti(npchar.nation), 5, 1);
            //<-- слухи
            break;

    // -------------- общий набор для всех квестов мэра ------------------
    case "All_disagree":
        dialog.text = "Вы разочаровываете меня!";
        link.l1 = "Прошу прощения, " + GetAddress_FormToNPC(NPChar) + ", но за это дело я взяться не могу.";
        link.l1.go = "exit";
        ChangeCharacterComplexReputation(pchar, "nobility", -2);

        if (CheckAttribute(pchar, "GenQuest.questName"))
        {
            QuestName = pchar.GenQuest.questName;
            DeleteAttribute(pchar, "GenQuest." + QuestName);
            DeleteAttribute(pchar, "GenQuest.questName");
        }
        break;
    case "All_Late":
        QuestName = pchar.GenQuest.questName;
        dialog.text = RandPhraseSimple("Ну, что я могу сказать - очень плохо. Я рассчитывал на вас, а в итоге попусту потратил время. Я разочарован.",
                                       "М-да, признаться, я разочарован в вас донельзя... У меня в резиденции всегда полно народу, готового выполнять такие поручения, а я тратил время на вас. М-да...");
        link.l1 = "Простите, " + GetAddress_FormToNPC(NPChar) + ", я сделал всё, что мог.";
        link.l1.go = "exit";
        //--> слухи
        AddSimpleRumour(LinkRandPhrase("Вы знаете, губернатор " + GetFullName(npchar) + " очень недоволен капитаном " + GetMainCharacterNameDat() + ". Представляете, тот не успел выполнить его поручение!",
                                       "Губернатор " + GetFullName(npchar) + " несколько раздражён нем, что некий капитан " + GetFullName(pchar) + " взялся за дело, но не успел выполнить его в срок. Нехорошо...",
                                       "Я слышал, что губернатор " + GetFullName(npchar) + " очень недоволен вами, капитан " + GetFullName(pchar) + ", так как вы не успели выполнить его задание в установленный срок."),
                        sti(npchar.nation), 5, 1);
        //<-- слухи
        ChangeCharacterComplexReputation(pchar, "nobility", -4);
        ChangeCharacterNationReputation(pchar, sti(NPChar.nation), -1);
        DeleteAttribute(pchar, "GenQuest." + QuestName);
        DeleteAttribute(pchar, "GenQuest.questName");
        npchar.greeting = NationShortName(sti(npchar.nation)) + "_gov_common"; //реплику вертаем
        SaveCurrentNpcQuestDateParam(npchar, "work_date");                     //сразу еще один не даем
        CloseQuestHeader("MayorsQuestsList");
        break;
    case "All_Found":
        QuestName = pchar.GenQuest.questName;
        dialog.text = RandPhraseSimple("Я просто в шоке! Суметь разыскать цель, но не позаботиться в достаточной мере о создании превосходства - это, знаете ли, верх безрассудства. Я разочарован!",
                                       "М-да, признаться, я разочарован в вас. Мало найти цель, нужно уметь её уничтожить. У меня в резиденции обретается достаточно головорезов, готовых выполнять такого рода задачи. Почему я связался с вами?..");
        link.l1 = "Простите, " + GetAddress_FormToNPC(NPChar) + ", но я не хочу рисковать собственной жизнью так безрассудно.";
        link.l1.go = "exit";
        //--> слухи
        AddSimpleRumour(LinkRandPhrase("Вы знаете, губернатор " + GetFullName(npchar) + " очень недоволен капитаном " + GetMainCharacterNameDat() + ". Представляете, " + GetSexPhrase("он оказался форменным трусом", "она оказалась форменной трусихой") + "!",
                                       "Губернатор " + GetFullName(npchar) + " несколько раздражён тем, что некий капитан " + GetFullName(pchar) + " взял" + GetSexPhrase("ся", "ась") + " за дело, но не сумел" + GetSexPhrase("", "а") + " его выполнить из-за собственной нерешительности. Хи-хи, какие капитаны пошли!",
                                       "Я слышал, что губернатор " + GetFullName(npchar) + " очень недоволен вами, капитан " + GetFullName(pchar) + ". Говорят, вы попросту трус" + GetSexPhrase("", "иха") + "..."),
                        sti(npchar.nation), 5, 1);
        //<-- слухи
        ChangeCharacterComplexReputation(pchar, "nobility", -6);
        ChangeCharacterNationReputation(pchar, sti(NPChar.nation), -1);
        DeleteAttribute(pchar, "GenQuest." + QuestName);
        DeleteAttribute(pchar, "GenQuest.questName");
        npchar.greeting = NationShortName(sti(npchar.nation)) + "_gov_common"; //реплику вертаем
        SaveCurrentNpcQuestDateParam(npchar, "work_date");                     //сразу еще один не даем
        CloseQuestHeader("MayorsQuestsList");
        AddQuestRecord("MayorsQuestsList", "21");
        AddQuestUserData("MayorsQuestsList", "ColonyName", XI_ConvertString("Colony" + npchar.city + "Gen"));
        AddQuestUserData("MayorsQuestsList", "MayorName", GetFullName(npchar));
        break;
    case "All_Execute":
        QuestName = pchar.GenQuest.questName;
        dialog.text = RandPhraseSimple("Прекрасная новость! Ну что же, пора подвести итоги. Ваш гонорар составляет " + FindRussianMoneyString(sti(pchar.GenQuest.(QuestName).Money)) + ". Извольте получить.",
                                       "Великолепно! Так будет лучше для всех... Итак, рад вручить вам положенное вознаграждение - " + FindRussianMoneyString(sti(pchar.GenQuest.(QuestName).Money)) + ". Извольте получить.");
        link.l1 = "Спасибо, " + GetAddress_FormToNPC(NPChar) + ", " + RandPhraseSimple("приятно иметь с вами дело!", "я приятно удивлен" + GetSexPhrase("", "а") + " чёткостью взаиморасчётов.");
        link.l1.go = "All_Execute_1";
        //--> слухи
        AddSimpleRumour(LinkRandPhrase("Вы знаете, губернатор " + GetFullName(npchar) + " очень хвалит за исполнительность нек" + GetSexPhrase("оего капитана", "ую девушку") + " " + GetMainCharacterNameGen() + ".",
                                       "Губернатор " + GetFullName(npchar) + " превозносит капитана " + GetMainCharacterNameGen() + ", т" + GetSexPhrase("от", "а") + " чётко выполняет все его поручения. Незаменимый человек для губернатора, я вам скажу...",
                                       "Я слышал, что губернатор " + GetFullName(npchar) + " очень доволен вами, капитан " + GetFullName(pchar) + ". Он характеризует вас как аккуратного и исполнительного офицера. Приятно это слышать, капитан..."),
                        sti(npchar.nation), 5, 1);
        //<-- слухи
        break;
    case "All_Execute_1":
        QuestName = pchar.GenQuest.questName;
        dialog.text = RandPhraseSimple("Ну, вот и славно. Можете заходить ко мне ещё, возможно, я найду для вас работу.", "Ну что же, прекрасно! Пожалуй, я буду и впредь предлагать вам работу подобного рода.");
        link.l1 = RandPhraseSimple("Отлично.", "Прекрасно.");
        link.l1.go = "exit";
        AddMoneyToCharacter(pchar, sti(pchar.GenQuest.(QuestName).Money));
        CloseQuestHeader("MayorsQuestsList");
        ChangeCharacterComplexReputation(pchar, "nobility", 4);
        ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 1);
        AddCharacterExpToSkill(PChar, "Leadership", 80);
        OfficersReaction("good"); // dlc

        DeleteAttribute(pchar, "GenQuest." + QuestName);
        DeleteAttribute(pchar, "GenQuest.questName");
        npchar.greeting = NationShortName(sti(npchar.nation)) + "_gov_common"; //реплику вертаем
        SaveCurrentNpcQuestDateParam(npchar, "work_date");                     //сразу еще один не даем
        // инкремент в базу заданий мэров
        sTemp = npchar.City;
        if (!CheckAttribute(pchar, "GenQuest.MayorQuestsList." + sTemp))
            pchar.GenQuest.MayorQuestsList.(sTemp) = 0;
        pchar.GenQuest.MayorQuestsList.(sTemp) = sti(pchar.GenQuest.MayorQuestsList.(sTemp)) + 1;
        break;
        //<-- осады homo
    case "siege_task":
        makearef(aData, NullCharacter.Siege);
        aData.HelpColony = true;
        dialog.text = "В столь тяжёлое время любая помощь ценна для нас. Мы принимаем вашу помощь - помогите нам отстоять колонию, и вы будете вознаграждены.";
        link.l1 = "Так не будем медлить.";
        link.l1.go = "exit";
        break;

    //Jason --> Бремя гасконца
    case "Sharlie":
        dialog.text = "Вы ищете Мишеля де Монпе? Очень интересно... И зачем же он вам понадобился?";
        link.l1 = "Я его брат. Отец сообщил мне, что у Мишеля неприятности и ему требуется помощь, и я...";
        link.l1.go = "Sharlie_1";
        break;

    case "Sharlie_1":
        dialog.text = "Вот как? Что-то я не припомню никакого брата у месье де Монпе... Вот что, сударь: вы мне кажетесь очень подозрительным, и я вас арестую для дальнейшего разбирательства. Лейтенант! Взять этого человека под стражу!";
        link.l1 = "Но, Ваша Светлость!";
        link.l1.go = "exit";
        AddDialogExitQuestFunction("Sharlie_enterSoldiers");
        break;

    case "Sharlie_2":
        dialog.text = "И всё же я хотел бы загладить свою вину перед вами. Вот, возьмите эту шпагу, этот пистолет и этот лёгкий доспех от меня в подарок. Думаю, эти вещи вам пригодятся.";
        link.l1 = "Благодарю, месье. С учетом того, что меня обобрали до нитки, это будет весьма кстати.";
        link.l1.go = "Sharlie_3";
        break;

    case "Sharlie_3":
        DialogExit();
        Log_Info("Вы получили экипировку");
        PlaySound("interface\important_item.wav");
        TakeNItems(pchar, "blade_08", 1);
        TakeNItems(pchar, "pistol1", 1);
        TakeNItems(pchar, "cirass5", 1);
        pchar.quest.Sharlie_PardonOver.over = "yes";
        DeleteAttribute(pchar, "questTemp.Sharlie.Pardon");
        break;
    //<-- Бремя гасконца

    //Jason --> Португалец
    case "Portugal":
        dialog.text = "Можете, капитан! Именно поэтому я вас и побеспокоил.";
        link.l1 = "Тогда я весь внимание.";
        link.l1.go = "Portugal_1";
        break;

    case "Portugal_1":
        dialog.text = "Местные рыбаки ещё вчера вечером видели вблизи острова странное судно. По их словам, это чуть не линейный корабль, без флагов и сигнальных огней. Не думаю, однако, что это судно, на самом деле больше фрегата, но и это уже чересчур!";
        link.l1 = "Да, у страха глаза, как известно, велики... но в чём суть дела?";
        link.l1.go = "Portugal_2";
        break;

    case "Portugal_2":
        dialog.text = "Я как раз перехожу к ней, капитан. Мои торговые партнёры взволнованны этими слухами – они полагают, что это пираты, либо испанский рейдер, а и то и то равно плохо скажется на торговле. Хуже всего другое – то, что в колонии сейчас нет военных кораблей, только пара шлюпов охранения, да старая шхуна, годные лишь гонять контрабандистов\nА я не могу оставить это без внимания... во всяком случае, теперь, когда о загадочном корабле судачит полгорода! Прошу вас, присоединитесь со своим судном к патрулированию – я знаю вас, как неплохого капитана, и, даже если там действительно небольшой фрегат, может ваши орудия убедят их поискать добычу в другом месте!";
        link.l1 = "Месье.. признаться, у меня были иные планы...";
        link.l1.go = "Portugal_3";
        break;

    case "Portugal_3":
        dialog.text = "Прошу вас, капитан! Всего на пару дней, пока не улягутся эти беспокойные слухи! Ваш рейд будет оплачен, разумеется! Сумма в 10 000 песо вас устроит?";
        link.l1 = "Хм-м, но ваше превосходительство, я...";
        link.l1.go = "Portugal_4";
        break;

    case "Portugal_4":
        dialog.text = "И мы удвоим её, если вам доведётся вступить в бой с этим судном, и утроим, если вы отправите его на дно! Что скажете?";
        link.l1 = "Хорошо, я, всё равно, планировал задержаться тут на несколько дней.";
        link.l1.go = "Portugal_5";
        break;

    case "Portugal_5":
        dialog.text = "Прекрасно, я в вас не сомневался, мсье капитан! Помните – два дня в наших водах, и оговоренная сумма ваша. В случае если вы вступите в сражение – плата соответственно результату.";
        link.l1 = "Я понял, ваше превосходительство. Наш контракт заключён, я отправляюсь на корабль.";
        link.l1.go = "Portugal_6";
        break;

    case "Portugal_6":
        dialog.text = "Жду вас с хорошими новостями, капитан!";
        link.l1 = "Разрешите откланяться.";
        link.l1.go = "Portugal_7";
        break;

    case "Portugal_7":
        DialogExit();
        AddQuestRecord("Portugal", "10");
        NextDiag.CurrentNode = "Portugal_8";
        LocatorReloadEnterDisable("Fortfrance_town", "reload1_back", false);
        LocatorReloadEnterDisable("Fortfrance_town", "reload2_back", false);
        LocatorReloadEnterDisable("Fortfrance_town", "gate_back", false); //открыть выходы из города
        bDisableFastReload = true;                                        //закрыть быстрый переход
        pchar.GenQuest.CannotWait = true;                                 //запрет ожидания
        pchar.quest.Portugal_Seapatrol.win_condition.l1 = "location";
        pchar.quest.Portugal_Seapatrol.win_condition.l1.location = "Martinique";
        pchar.quest.Portugal_Seapatrol.function = "PortugalSeapatrolGo";
        pchar.quest.Portugal_SeapatrolAvendel.win_condition.l1 = "location";
        pchar.quest.Portugal_SeapatrolAvendel.win_condition.l1.location = "Fortfrance_town";
        pchar.quest.Portugal_SeapatrolAvendel.function = "AvendelSpeach";
        break;

    case "Portugal_8":
        dialog.text = "Капитан, мы же, кажется, договорились с вами о двух днях патрулирования наших прибрежных вод!";
        link.l1 = "Да, конечно. Я всё помню.";
        link.l1.go = "exit";
        NextDiag.TempNode = "Portugal_8";
        break;

    case "Portugal_9":
        dialog.text = "Ну что же, вы выполнили условия контракта. Вот ваши 10 000 песо.";
        link.l1 = "Благодарю! Как видите, ваши опасения не подтвердились. Всего доброго!";
        link.l1.go = "Portugal_10";
        break;

    case "Portugal_10":
        DialogExit();
        AddMoneyToCharacter(pchar, 10000);
        NextDiag.CurrentNode = "First time";
        pchar.quest.MartiniqueGovernorOver.over = "yes"; //снять таймер
        break;
    //<-- Португалец

    // Warship, 16.05.11. Генер "Правосудие на продажу".
    case "JusticeOnSale_1":
        dialog.text = "О " + GetAddress_Form(NPChar) + ", вы меня удивили! Неужели эти канальи настолько обнаглели? Надо немедленно известить стражу и направить туда береговой патруль!";
        link.l1 = "Рад был помочь, разрешите откланяться?";
        link.l1.go = "JusticeOnSale_2";

        DeleteAttribute(PChar, "GenQuest.JusticeOnSale.MayorWait");
        DeleteAttribute(PChar, "GenQuest.JusticeOnSale.PrisonWait");

        DeleteQuestCondition("JusticeOnSale_MapEnter");
        break;

    case "JusticeOnSale_2":
        dialog.text = "Конечно, капитан. Вот, примите на прощание скромную благодарность от меня лично.";
        link.l1 = "Благодарю.";
        link.l1.go = "JusticeOnSale_3";
        break;

    case "JusticeOnSale_3":
        AddQuestRecord("JusticeOnSale", "5");
        CloseQuestHeader("JusticeOnSale");

        AddMoneyToCharacter(PChar, 1000 + sti(PChar.rank) * 30 * dRand(10));

        DeleteAttribute(PChar, "GenQuest.JusticeOnSale");

        DialogExit();
        break;

    case "JusticeOnSale_4":
        dialog.text = "Вы правы, капитан! Мы не можем это так оставить! Я прошу вас отправиться " + XI_ConvertString(PChar.GenQuest.JusticeOnSale.ShoreId + "Acc") + ", найти их корабль, и взять всю их шайку! Если будут сопротивляться – применяйте силу, не раздумывая!";
        link.l1 = "Разрешите откланяться.";
        link.l1.go = "JusticeOnSale_5";
        break;

    case "JusticeOnSale_5":
        dialog.text = "Ступайте. Доплывите туда, и проследите, чтобы никто не ушёл от правосудия! Думаю, вам сначала надо будет высадиться на берег, а потом уже заняться кораблем.";
        link.l1 = "...";
        link.l1.go = "JusticeOnSale_6";
        break;

    case "JusticeOnSale_6":
        sld = GetCharacter(NPC_GenerateCharacter("JusticeOnSale_ShipPirate", "", "man", "man", sti(PChar.rank) + 5, PIRATE, -1, true, "quest"));
        sld.Ship.Type = GenerateShipExt(sti(PChar.GenQuest.JusticeOnSale.ShipType), true, sld);
        sld.Ship.Name = PChar.GenQuest.JusticeOnSale.ShipName;
        SetBaseShipData(sld);
        SetCrewQuantityFull(sld);
        Fantom_SetCannons(sld, "pirate");
        Fantom_SetBalls(sld, "pirate");
        Fantom_SetUpgrade(sld, "pirate");
        SetCaptanModelByEncType(sld, "pirate");
        SetRandGeraldSail(sld, PIRATE);

        Character_SetAbordageEnable(sld, false);

        Group_FindOrCreateGroup("JusticeOnSaleGroup");
        Group_AddCharacter("JusticeOnSaleGroup", "JusticeOnSale_ShipPirate");
        Group_SetGroupCommander("JusticeOnSaleGroup", "JusticeOnSale_ShipPirate");
        Group_SetAddress("JusticeOnSaleGroup", PChar.curislandid, "reload", Island_GetLocationReloadLocator(PChar.curislandid, PChar.GenQuest.JusticeOnSale.ShoreId));
        Group_SetTaskNone("JusticeOnSaleGroup");
        Group_LockTask("JusticeOnSaleGroup");

        sld.AlwaysFriend = true;
        SetCharacterRelationBoth(sti(sld.index), GetMainCharacterIndex(), RELATION_FRIEND);

        SetCharacterShipLocation(sld, PChar.GenQuest.JusticeOnSale.ShoreId);

        DeleteAttribute(sld, "SinkTenPercent");
        DeleteAttribute(sld, "SaveItemsForDead");
        DeleteAttribute(sld, "DontClearDead");
        DeleteAttribute(sld, "AboardToFinalDeck");

        sld.AlwaysSandbankManeuver = true;
        sld.AnalizeShips = true;
        sld.DontRansackCaptain = true;

        sld = &Locations[FindLocation(PChar.GenQuest.JusticeOnSale.ShoreId)];
        sld.DisableEncounters = true;

        PChar.Quest.JusticeOnSale_ShoreEnterFromMayor.win_condition.l1 = "location";
        PChar.Quest.JusticeOnSale_ShoreEnterFromMayor.win_condition.l1.location = PChar.GenQuest.JusticeOnSale.ShoreId;
        PChar.Quest.JusticeOnSale_ShoreEnterFromMayor.function = "JusticeOnSale_ShoreEnterFromMayor";

        PChar.Quest.JusticeOnSale_PirateShip_Sink.win_condition.l1 = "Character_sink";
        PChar.Quest.JusticeOnSale_PirateShip_Sink.win_condition.l1.character = "JusticeOnSale_ShipPirate";
        PChar.Quest.JusticeOnSale_PirateShip_Sink.function = "JusticeOnSale_PirateShip_Sink";

        DialogExit();
        break;

    case "JusticeOnSale_7":
        dialog.text = "Благодарю вас за помощь. Эти мерзавцы получили то, что им причитается. Позвольте вручить вам скромную премию от меня лично. Я весьма ценю покой во вверенном мне городе.";
        link.l1 = "...";
        link.l1.go = "JusticeOnSale_8";
        break;

    case "JusticeOnSale_8":
        AddMoneyToCharacter(PChar, sti(PChar.rank) * 300 + dRand(1000));
        DeleteAttribute(PChar, "GenQuest.JusticeOnSale");
        DialogExit();
        break;
        //<-- Правосудие на продажу

        //--> Jason регата
    case "Regata":
        dialog.text = "А-а, замечательно, рад вас видеть, капитан! Вы пришли вовремя, регата стартует через несколько дней. Вы прочли о правилах регаты в письме, переданном вам вестовым?";
        link.l1 = "Да, сэр, прочёл.";
        link.l1.go = "Regata_1";
        RemoveItems(PChar, "letter_open", 1);                   //уберем письмо
        TakeNationLicence(HOLLAND);                             //уберем лицензию
        DeleteAttribute(pchar, "questTemp.Regata.ToPortRoyal"); // patch-5
        break;

    case "Regata_1":
        dialog.text = "Итак, вы приготовили 50 000 песо - взнос в призовой фонд?";
        if (makeint(Pchar.money) >= 50000)
        {
            link.l1 = "Да, конечно. Вот, примите мой взнос.";
            link.l1.go = "Regata_2";
        }
        link.l2 = "У меня сейчас недостаточно денег. Но я обязательно принесу их.";
        link.l2.go = "Regata_nomoney";
        break;

    case "Regata_2":
        dialog.text = "Очень хорошо. Если вы победите - ваши деньги вернутся к вам, причём в пятикратном размере. Теперь вам нужно получше ознакомиться с правилами регаты\nВсе подробности узнаете у сэра Генри Стивенсона, он должен находиться в комнате резиденции. Пройдите к нему - он вам всё объяснит.";
        link.l1 = "Хорошо. Я так и сделаю.";
        link.l1.go = "exit";
        AddMoneyToCharacter(pchar, -50000);
        pchar.quest.Regata_Guber.win_condition.l1 = "location";
        pchar.quest.Regata_Guber.win_condition.l1.location = "Portroyal_Roomtownhall";
        pchar.quest.Regata_Guber.function = "PrepareToRegataInPortroyal";
        pchar.questTemp.Regata.Begin = "true";
        NextDiag.TempNode = "First time";
        break;

    case "Regata_nomoney":
        dialog.text = "Хорошо. Но только не затягивайте с этим, капитан. Регате скоро будет дан старт.";
        link.l1 = "Я понимаю. Буду у вас на приёме, с деньгами, как можно скорее.";
        link.l1.go = "exit";
        NextDiag.TempNode = "Regata_1";
        pchar.questTemp.Regata.nomoney = "true";
        break;

    //регата-финал
    case "Regata_Final":
        dialog.text = "А, вот и победитель регаты! Добрый день, капитан " + GetFullName(pchar) + "! Поздравляю вас с этим значительным успехом - победители нашей регаты всегда пользуются заслуженной популярностью в английских колониях. ";
        link.l1 = "Спасибо за поздравление, сэр!";
        link.l1.go = "Regata_complete";
        break;

    case "Regata_complete":
        dialog.text = "Теперь перейдём к самой приятной для вас части - получению награды. Итак, денежное вознаграждение за победу составляет 250 000 песо. Извольте получить!";
        link.l1 = "Благодарю!";
        link.l1.go = "Regata_complete_1";
        break;

    case "Regata_complete_1":
        AddMoneyToCharacter(pchar, 250000);
        int iGift;
        string sItem1, sItem2, sItem3, sAdd;
        if (sti(pchar.rank) < 11)
            iGift = 0;
        if (sti(pchar.rank) >= 11 && sti(pchar.rank) < 25)
            iGift = 1;
        if (sti(pchar.rank) >= 25)
            iGift = 2;
        switch (iGift)
        {
        case 0:
            sItem1 = "blade_27"; //саксенфедер
            sItem2 = "cirass7";  //бригант
            sItem3 = "bussol";
            sAdd = "саксенфедер, бригант и буссоль";
            break;

        case 1:
            sItem1 = "blade_20";      //мадонна
            sItem2 = "grape_mushket"; //склопетта
            sItem3 = "bussol";
            sAdd = "'мадонна', склопетта и буссоль";
            break;

        case 2:
            sItem1 = "blade_26"; //асоледа
            sItem2 = "cirass4";  //миланский панцирь
            sItem3 = "bussol";
            sAdd = "асоледа, миланский панцирь и буссоль";
            break;
        }
        GiveItem2Character(pchar, sItem1);
        GiveItem2Character(pchar, sItem2);
        GiveItem2Character(pchar, sItem3);
        dialog.text = "Также вам положен комплект ценных призов: " + sAdd + ". Теперь всё это - ваше.";
        link.l1 = "Очень рад, сэр. Право, даже не ожидал.";
        link.l1.go = "Regata_complete_2";
        break;

    case "Regata_complete_2":
        dialog.text = "От лица всех жителей английских колоний благодарю вас за участие в регате, и ещё раз поздравляю с победой! Если вы сделали ставку - самое время пойти к сэру Генри Стивенсону и получить свой выигрыш. Желаю вам удачи, капитан!";
        link.l1 = "Спасибо за тёплые слова, сэр! В свою очередь благодарю вас за то, что дали мне возможность участвовать в этом великолепном мероприятии. А теперь разрешите откланяться.";
        link.l1.go = "Regata_complete_3";
        break;

    case "Regata_complete_3":
        DialogExit();
        NextDiag.CurrentNode = "First time";
        break;
        //<-- регата
    }
}

string GetGangLocation(ref npchar)
{
    int n;
    string island = GetArealByCityName(npchar.city);
    string LocationId, sAreal;
    int storeArray[MAX_LOCATIONS];
    int howStore = 0;

    for (n = 0; n < MAX_LOCATIONS; n++)
    {
        if (GiveArealByLocation(&locations[n]) == island)
        {
            //==> на всякий случай
            if (CheckAttribute(&locations[n], "DisableEncounters") && locations[n].DisableEncounters == true)
                continue;
            LocationId = locations[n].id;
            if (findsubstr(LocationId, "jungle", 0) != -1 || findsubstr(LocationId, "Shore", 0) != -1 || findsubstr(LocationId, "CaveEntrance", 0) != -1)
            {
                storeArray[howStore] = n;
                howStore++;
            }
        }
    }
    if (howStore == 0)
        return "none";
    n = storeArray[dRand(howStore - 1)];
    return locations[n].id;
}

string GetSpyLocation(ref npchar)
{
    aref arCommon, arRld, arRld2;
    int i, n, Qty, Qty2;
    string LocId;
    string storeArray[50];
    int howStore = 0;
    makearef(arRld, Locations[FindLocation(npchar.city + "_town")].reload);
    Qty = GetAttributesNum(arRld);
    if (CheckAttribute(pchar, "questTemp.jailCanMove.Deliver.locationId")) //если взят квест по доставке малявы
    {
        for (i = 0; i < Qty; i++)
        {
            arCommon = GetAttributeN(arRld, i);
            LocId = arCommon.go;
            if (findsubstr(LocId, "Common", 0) != -1 && LocId != pchar.questTemp.jailCanMove.Deliver.locationId)
            {
                storeArray[howStore] = LocId;
                howStore++;
            }
            if (arCommon.label != "Sea")
            {
                makearef(arRld2, Locations[FindLocation(LocId)].reload);
                Qty2 = GetAttributesNum(arRld2);
                for (n = 0; n < Qty2; n++)
                {
                    arCommon = GetAttributeN(arRld2, n);
                    LocId = arCommon.go;
                    if (findsubstr(LocId, "Common", 0) != -1 && LocId != pchar.questTemp.jailCanMove.Deliver.locationId && LocId != "CommonPackhouse_1" && LocId != "CommonPackhouse_2")
                    {
                        storeArray[howStore] = LocId;
                        howStore++;
                    }
                }
            }
        }
    }
    else
    {
        for (i = 0; i < Qty; i++)
        {
            arCommon = GetAttributeN(arRld, i);
            LocId = arCommon.go;
            if (findsubstr(LocId, "Common", 0) != -1)
            {
                storeArray[howStore] = LocId;
                howStore++;
            }
            if (arCommon.label != "Sea")
            {
                makearef(arRld2, Locations[FindLocation(LocId)].reload);
                Qty2 = GetAttributesNum(arRld2);
                for (n = 0; n < Qty2; n++)
                {
                    arCommon = GetAttributeN(arRld2, n);
                    LocId = arCommon.go;
                    if (findsubstr(LocId, "Common", 0) != -1 && LocId != "CommonPackhouse_1" && LocId != "CommonPackhouse_2")
                    {
                        storeArray[howStore] = LocId;
                        howStore++;
                    }
                }
            }
        }
    }
    if (howStore == 0)
        return "none";
    LocId = storeArray[dRand(howStore - 1)];
    SetOpenDoorCommonLoc(npchar.city, LocId); //открываем дверь
    for (n = 0; n < MAX_CHARACTERS; n++)
    {
        if (CheckAttribute(&characters[n], "locations") && characters[n].locations == LocId)
        {
            characters[n].lifeDay = 0;
        }
    }
    return LocId;
}

string GetSpyColony(ref NPChar)
{
    int storeArray[MAX_COLONIES];
    int howStore = 0;
    string sChrId;

    for (int n = 0; n < MAX_COLONIES; n++)
    {
        if (colonies[n].nation != "none" && sti(colonies[n].nation) != PIRATE && GetRelation2BaseNation(sti(colonies[n].nation)) == RELATION_ENEMY && colonies[n].id != "Panama" && colonies[n].id != "Minentown" && colonies[n].id != "SanAndres" && colonies[n].id != npchar.City)
        {
            storeArray[howStore] = n;
            howStore++;
        }
    }
    if (howStore == 0)
        return "none";
    return colonies[storeArray[Rand(howStore - 1)]].id;
}

int SelectCureerShipType()
{
    int iShipType;
    if (sti(pchar.rank) >= 14)
    {
        iShipType = SHIP_CORVETTE + rand(makeint(SHIP_POLACRE - SHIP_CORVETTE));
    }
    if (sti(pchar.rank) >= 6 && sti(pchar.rank) < 14)
    {
        iShipType = SHIP_BRIGANTINE + rand(makeint(SHIP_SCHOONER_W - SHIP_BRIGANTINE));
    }
    if (sti(pchar.rank) < 6)
    {
        iShipType = SHIP_CAREERLUGGER + rand(makeint(SHIP_SLOOP - SHIP_CAREERLUGGER));
    }
    return iShipType;
}

int SelectArsenalShipType()
{
    int iShipType;
    if (sti(pchar.rank) >= 18)
    {
        iShipType = SHIP_GALEON_H;
    }
    if (sti(pchar.rank) >= 14 && sti(pchar.rank) < 18)
    {
        iShipType = SHIP_GALEON_L;
    }
    if (sti(pchar.rank) >= 8 && sti(pchar.rank) < 14)
    {
        iShipType = SHIP_CARAVEL + rand(makeint(SHIP_CARACCA - SHIP_CARAVEL));
    }
    if (sti(pchar.rank) >= 4 && sti(pchar.rank) < 8)
    {
        iShipType = SHIP_SCHOONER + rand(makeint(SHIP_FLEUT - SHIP_SCHOONER));
    }
    if (sti(pchar.rank) < 4)
    {
        iShipType = SHIP_BARQUE;
    }
    return iShipType;
}

string SelectPassText()
{
    string sText;
    switch (drand(5))
    {
    case 0:
        sText = "Этот иуда, воспользовавшись своим положением, выдал за деньги важную государственную тайну враждебной державе.";
        break;
    case 1:
        sText = "Этот негодяй подло убил своего родственника, известного и знатного человека, ради наследства.";
        break;
    case 2:
        sText = "Этот гнусный негодяй нанёс тяжкое оскорбление моей семье и мне лично.";
        break;
    case 3:
        sText = "Этот вороватый пройдоха выкрал из казны нашего города приличную сумму денег.";
        break;
    case 4:
        sText = "Этот негодяй виновен в смерти почти десятка наших граждан.";
        break;
    case 5:
        sText = "Этот пройдоха, используя свои связи, обманом завладел одним купеческим судном, украл его и продал на соседней верфи.";
        break;
    }
    return sText;
}

string SelectFugitiveCity()
{
    string sCity;
    switch (rand(3))
    {
    case 0:
        sCity = "LaVega";
        break;
    case 1:
        sCity = "PuertoPrincipe";
        break;
    case 2:
        sCity = "LeFransua";
        break;
    case 3:
        sCity = "FortOrange";
        break;
    }
    return sCity;
}

string SelectFugitiveText()
{
    string sText;
    switch (drand(5))
    {
    case 0:
        sText = "один из младших офицеров нашего гарнизона бросил службу и скрылся на купеческом корабле из нашей колонии.";
        break;
    case 1:
        sText = "один из наших офицерских чинов дезертировал, прямо во время несения службы, и сбежал на корабле контрабандистов.";
        break;
    case 2:
        sText = "один из наших морских офицеров, служивших на патрульном бриге, по непонятным причинам дезертировал, угнал баркас и скрылся.";
        break;
    case 3:
        sText = "один тюремный стражник по необъяснимой причине бросил службу и сбежал из нашей колонии на частном судне.";
        break;
    case 4:
        sText = "один солдат нашего гарнизона бросил свой пост, прямо в то время, когда нёс караул, отправился в бухту и покинул наши места на неопознанном корабле.";
        break;
    case 5:
        sText = "один наш военный офицер, капитан патрульного люггера, бросил своё судно прямо в море и скрылся в неизвестном направлении на рыбацком баркасе.";
        break;
    }
    return sText;
}
