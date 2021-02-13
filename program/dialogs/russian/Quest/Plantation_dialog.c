// диалоги обитателей плантаций
void ProcessDialogEvent()
{
    ref NPChar;
    aref Link, NextDiag;
    int iTemp;
    string sTemp;

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

    case "First time":
        dialog.text = "Вы что-то хотели?";
        link.l1 = "Да нет, ничего.";
        link.l1.go = "exit";
        break;

    case "fight":
        DialogExit();
        NextDiag.CurrentNode = NextDiag.TempNode;
        LAi_group_Attack(NPChar, Pchar);
        SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
        AddDialogExitQuest("MainHeroFightModeOn");
        break;

    // рабы
    case "plantation_slave":
        if (CheckAttribute(npchar, "CityType") && npchar.CityType == "citizen" && findsubstr(npchar.id, "Slave_", 0) != -1)
        {
            dialog.text = RandPhraseSimple(RandPhraseSimple("Я так устал - просто с ног валюсь.", "Нет больше сил так жить!"), RandPhraseSimple("Эта работа слишком тяжелая для меня.", "Надсмотрщики уже не оставили живого места на моей шкуре!"));
            link.l1 = RandPhraseSimple("Сочувствую, приятель.", "Мне жаль тебя.");
            link.l1.go = "exit";
        }
        break;

    // охрана - солдаты
    case "plantation_soldier":
        dialog.text = RandPhraseSimple(RandPhraseSimple("Все вопросы - к управляющему плантацией.", "Только не отвлекай рабов от работы своими разговорами, приятель."), RandPhraseSimple("Моя задача - гонять этих бездельников.", "Ну и жарища же сегодня... впрочем, как и всегда."));
        link.l1 = RandPhraseSimple("Понятно...", "Ясно...");
        link.l1.go = "exit";
        break;

    // охрана - протектор
    case "plantation_protector":
        if (GetNationRelation2MainCharacter(sti(NPChar.nation)) == RELATION_ENEMY && sti(NPChar.nation) != PIRATE)
        {
            if (sti(pchar.nation) == PIRATE)
            {
                PlaySound("VOICE\Russian\soldier_arest_1.wav");
                dialog.text = RandPhraseSimple("Пираты на нашей плантации?! Ну дела... Хватай его!!", "Это пират!! Держи его!!!");
                link.l1 = RandPhraseSimple("Пират, ну и что?..", "Хех, попробуйте схватить.");
                link.l1.go = "fight";
                break;
            }
            PlaySound("VOICE\Russian\soldier_arest_2.wav");
            dialog.text = RandPhraseSimple("Хо-хо, да ведь ты ходишь под флагом " + NationNameGenitive(sti(pchar.nation)) + "! Думаю, комендант обрадуется, когда мы сдадим ему тебя!", "Так-так, что-то у нас тут " + NationNameAblative(sti(pchar.nation)) + " завоняло! Шпионишь, мерзавец? Пора тебя познакомить с нашим комендантом!");
            link.l1 = RandPhraseSimple("Сейчас я тебя познакомлю с моей саблей.", "Думаю, что я сначала сдам тебя чертям.");
            link.l1.go = "fight";
        }
        else
        {
            if (GetNationRelation(sti(NPChar.nation), GetBaseHeroNation()) == RELATION_ENEMY && sti(NPChar.nation) != PIRATE)
            {
                if (sti(pchar.nation) == PIRATE)
                {
                    PlaySound("VOICE\Russian\soldier_arest_1.wav");
                    dialog.text = RandPhraseSimple("Пират?! Ну дела... Хватай его!!", "Это пират!! Держи его!!!");
                    link.l1 = RandPhraseSimple("Да, пират, ну и что?..", "Хех, попробуйте схватить...");
                    link.l1.go = "fight";
                    break;
                }
                PlaySound("VOICE\Russian\soldier_arest_4.wav");
                dialog.text = RandPhraseSimple("Кто ты и что тебе здесь нужно?", "Стой! Что ты забыл здесь?");
                if (CheckNationLicence(HOLLAND))
                {
                    link.l1 = "Я хочу пройти к управляющему плантацией для обсуждения торговых сделок. У меня есть торговая лицензия.";
                    link.l1.go = "Licence";
                    link.l2 = "Я хочу пройти к управляющему плантацией для обсуждения торговых сделок.";
                    if (GetSummonSkillFromName(pchar, SKILL_SNEAK) < (10 + rand(50) + rand(50)))
                        link.l1.go = "PegYou";
                    else
                        link.l2.go = "NotPegYou";
                }
                else
                {
                    link.l1 = "Я хочу пройти к управляющему плантацией для обсуждения торговых сделок.";
                    if (GetSummonSkillFromName(pchar, SKILL_SNEAK) < (10 + rand(50) + rand(50)))
                        link.l1.go = "PegYou";
                    else
                        link.l1.go = "NotPegYou";
                }
            }
            else
            {
                PlaySound("VOICE\Russian\soldier_arest_4.wav");
                dialog.text = RandPhraseSimple("Кто ты и что тебе здесь нужно?", "Стой! Что ты забыл здесь?");
                link.l1 = "Я хочу пройти к управляющему плантацией для обсуждения торговых сделок.";
                link.l1.go = "NotPegYou";
            }
        }
        break;

    case "Licence":
        iTemp = GetDaysContinueNationLicence(HOLLAND);
        if (ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 0) <= -12)
        {
            PlaySound("VOICE\Russian\soldier_arest_2.wav");
            dialog.text = "Лицензия? Постой-ка... Не смеши! Я узнал тебя! Твои портреты висят в каждой казарме, и за твою поимку обещана хорошая награда. Взять его!";
            link.l1 = RandPhraseSimple("Аргх!..", "Ну, ты сам напросился...");
            link.l1.go = "fight";
            break;
        }
        if (iTemp == -1)
        {
            PlaySound("VOICE\Russian\soldier_arest_1.wav");
            dialog.text = "Сейчас посмотрим... Ха! Твоя лицензия просрочена и поэтому недействительна. Пожалуй, надо сдать тебя в комендатуру, голубчик...";
            link.l1 = RandPhraseSimple("Как бы не так!", "После дождичка, в четверг...");
            link.l1.go = "fight";
            TakeNationLicence(HOLLAND);
            break;
        }
        dialog.text = "Хорошо. Можешь проходить. Веди себя прилично и не приставай к рабам, а то им достанется из-за тебя.";
        link.l1 = "Не беспокойся, приятель.";
        link.l1.go = "plantation_exit";
        break;

    case "PegYou":
        PlaySound("VOICE\Russian\soldier_arest_2.wav");
        dialog.text = "Торговых сделок? Ха-ха! Меня не проведешь! Да от тебя на милю несет " + NationNameAblative(sti(GetBaseHeroNation())) + "! Шпионишь, мерзавец? Пора тебе познакомиться с нашим комендантом.";
        link.l1 = "Нет, это тебе пора познакомиться с моей саблей.";
        link.l1.go = "fight";
        break;

    case "NotPegYou":
        dialog.text = "Хорошо. Можешь проходить. Веди себя прилично и не приставай к рабам, а то им достанется из-за тебя.";
        link.l1 = "Не беспокойся, приятель.";
        link.l1.go = "plantation_exit";
        break;

    case "plantation_exit":
        DialogExit();
        NextDiag.CurrentNode = "plantation_repeat";
        break;

    case "plantation_repeat":
        dialog.text = "Давай, проходи уже, не стой, как истукан!";
        link.l1 = "...";
        link.l1.go = "plantation_exit";
        break;

    // управляющий в Маракайбо
    case "Plantator":
        if (CheckAttribute(pchar, "questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "plant_2" && GetSquadronGoods(pchar, GOOD_SLAVES) >= 50)
        {
            dialog.text = "По какому делу зашли, сеньор?";
            link.l1 = TimeGreeting() + ", сеньор. У меня к вам деловое предложение. В трюмах моего корабля находятся рабы, " + FindRussianQtyString(sti(GetSquadronGoods(pchar, GOOD_SLAVES))) + ". Не желаете ли их приобрести по сходной цене?";
            link.l1.go = "mtraxx";
        }
        dialog.text = "По какому делу зашли, сеньор?";
        link.l1 = "Просто гулял по окрестностям Маракайбо и заглянул на вашу плантацию. Я уже ухожу.";
        link.l1.go = "exit";
        break;

    case "plantator_1":
        dialog.text = "А, это опять вы, сеньор. Как ваши дела?";
        link.l1 = "Спасибо, все отлично...";
        link.l1.go = "exit";
        break;

    case "mtraxx":
        dialog.text = "Вынужден вас огорчить, сеньор, но в данный момент наша плантация в рабах не нуждается. Недавно капитан Эдуардо де Лосада обеспечил наши потребности висельниками-пиратами, захваченными им в боевом рейде. Так что...";
        link.l1 = "Пираты работают на вашей плантации? Ох, сеньор, и как вы можете спать спокойно?";
        link.l1.go = "mtraxx_1";
        break;

    case "mtraxx_1":
        dialog.text = "Охрана у нас хорошая, так что бунта бояться нечего. Но в чем-то вы правы: эти канальи совсем не желают нормально работать. Я бы не покупал их, но дон губернатор так настойчиво просил уважить дона де Лосада... да и цену тот установил совсем невысокую.";
        link.l1 = "Понятно. Придется идти в Лос-Текес... Да, сеньор, вы не позволите мне немного погулять по вашей плантации и осмотреть ее? Возможно, я бы приобрел вашу продукцию на продажу...";
        link.l1.go = "mtraxx_2";
        break;

    case "mtraxx_2":
        dialog.text = "Вы торговец?";
        link.l1 = "Ну, в какой-то степени да. Профессиональным купцом я себя не назову, конечно, но от выгодной негоции никогда не отказываюсь.";
        link.l1.go = "mtraxx_3";
        break;

    case "mtraxx_3":
        dialog.text = "Это интересно. Ну что же, я не возражаю против вашего присутствия. Гуляйте, смотрите. Если что-то надумаете - приходите, обсудим.";
        link.l1 = "Спасибо, сеньор. Думаю, мы еще продолжим нашу беседу.";
        link.l1.go = "mtraxx_4";
        break;

    case "mtraxx_4":
        DialogExit();
        NextDiag.CurrentNode = "plantator_1";
        pchar.questTemp.Mtraxx = "plant_3";
        AddQuestRecord("Roger_3", "5");
        break;

    case "":
        dialog.text = "";
        link.l1 = "";
        link.l1.go = "";
        break;

    case "":
        dialog.text = "";
        link.l1 = "";
        link.l1.go = "";
        break;

    case "":
        dialog.text = "";
        link.l1 = "";
        link.l1.go = "";
        break;

    case "":
        dialog.text = "";
        link.l1 = "";
        link.l1.go = "";
        break;

    case "":
        dialog.text = "";
        link.l1 = "";
        link.l1.go = "";
        break;
    }
}
