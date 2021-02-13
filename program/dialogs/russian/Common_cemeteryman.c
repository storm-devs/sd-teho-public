// Jason общий диалог смотрителей кладбищ
void ProcessDialogEvent()
{
    ref NPChar;
    aref Link, NextDiag;

    DeleteAttribute(&Dialog, "Links");

    makeref(NPChar, CharacterRef);
    makearef(Link, Dialog.Links);
    makearef(NextDiag, NPChar.Dialog);

    // вызов диалога по городам -->
    NPChar.FileDialog2 = "DIALOGS\" + LanguageGetLanguage() + "\Cemetery\" + NPChar.City + "_cemetery.c ";
                         if (LoadSegment(NPChar.FileDialog2))
    {
        ProcessCommonDialog(NPChar, Link, NextDiag);
        UnloadSegment(NPChar.FileDialog2);
    }
    // вызов диалога по городам <--

    int iTemp;
    string sTemp;
    bool ok;

    switch (Dialog.CurrentNode)
    {
    case "First time":
        if (LAi_grp_playeralarm > 0)
        {
            dialog.text = PCharRepPhrase(LinkRandPhrase("В городе поднята тревога. Похоже, и мне пора браться за оружие...", "Уж не за тобой ли носится вся городская стража?.. Ко мне, солдаты!!!", "У меня приюта ты не найдёшь. Зато найдёшь несколько дюймов холодной стали под ребро!"),
                                         LinkRandPhrase("Что тебе нужно, " + GetSexPhrase("негодяй", "негодяйка") + "?! Городская стража уже взяла твой след, далеко тебе не уйти, " + GetSexPhrase("грязный пират", "мерзавка") + "!", "" + GetSexPhrase("Грязный", "Грязная") + " убийца! Стража!!!", "Я не боюсь тебя, " + GetSexPhrase("мерзавец", "мерзавка") + "! Скоро тебя повесят в нашем форте, далеко тебе не уйти..."));
            link.l1 = PCharRepPhrase(RandPhraseSimple("Похоже, тебе жить надоело...", "Хех, и не живётся же спокойно мирным гражданам " + XI_ConvertString("Colony" + npchar.city + "Gen") + "!"),
                                     RandPhraseSimple("Отправляйся в ад!", "Хех, жить тебе осталось несколько секунд..."));
            link.l1.go = PCharRepPhrase("exit_setOwner", "fight");
            break;
        }
        if (npchar.quest.meeting == "0")
        {
            dialog.text = RandPhraseSimple("Добрый день, морячок! Меня зовут " + GetFullName(npchar) + ", и я - единственный живой обитатель сего места, хе-хе. Впрочем, все там будем... Зачем пожаловали?", "Здравствуйте! Давненько я не видал живого человека... Позвольте представиться - " + GetFullName(npchar) + ", а это кладбище - мое последнее пристанище в этой жизни. Видимо, тут же меня и похоронят. Чем могу служить?");
            link.l1 = "Здравствуй, " + npchar.name + "! Моё имя - " + GetFullName(pchar) + ", и я капитан. Вот, ходил по джунглям и забрёл сюда. Думаю, загляну в этот уютный домик, посмотрю, кто не боится здесь жить...";
            link.l1.go = "meeting";
            npchar.quest.meeting = "1";
        }
        else
        {
            dialog.text = "А-а, мой старый знакомый, капитан " + GetFullName(pchar) + "! Проходите, проходите!";
            link.l1 = "Приветствую, дружище! Рад тебя видеть. Тебе ещё не снятся по ночам пляшущие скелеты и мертвецы с медяками на глазах?";
            link.l1.go = "talk";
        }
        NextDiag.TempNode = "First time";
        break;

    case "meeting":
        dialog.text = "А чего же тут бояться-то, капитан? Бояться живых надо, а мёртвые не кусаются. Эх! Когда-то у меня была совсем другая жизнь, а теперь вот моя забота - это кладбище. Приглядываю за могилками. А также приторговываю всякой всячиной...";
        link.l1 = "А чем ты торгуешь, скажи пожалуйста?";
        link.l1.go = "trade_info";
        break;

    case "talk":
        dialog.text = "Что привело вас ко мне на сей раз?";
        link.l1 = "Давай посмотрим, что у тебя есть сегодня в продаже.";
        link.l1.go = "trade";
        link.l2 = "Я вот что " + GetSexPhrase("хотел", "хотела") + " спросить...";
        link.l2.go = "quests";
        link.l3 = "Ничего серьезного. Просто зашёл поздороваться.";
        link.l3.go = "exit";
        NextDiag.TempNode = "First time";
        break;

    case "trade_info":
        dialog.text = "У меня много свободного времени, поэтому я люблю побродить по окрестным джунглям и собрать полезные травки. Потом я продаю их в городе. За них платят сущие гроши, но всё же лучше, чем ничего. Иногда я нахожу занятные камни. Нет, не самоцветы, но мастеровым они почему-то бывают нужны\nНу, и самые разные предметы мне дают мои друзья...";
        link.l1 = "Друзья? То есть, ты перепродаешь то, что тебе привозят?";
        link.l1.go = "trade_info_1";
        break;

    case "trade_info_1":
        dialog.text = "О-хо-хо... Нет, они мне всё предоставляют бесплатно. Какие ещё могут быть друзья у кладбищенского сторожа, если не покойники?";
        link.l1 = "Гм... ты что, обираешь мертвецов?";
        link.l1.go = "trade_info_2";
        break;

    case "trade_info_2":
        dialog.text = "Не обираю, а снимаю вещи, которые им уже не нужны. Здесь же разные люди похоронены. Многие без роду-племени и не из наших мест. Привезёт комендант из города труп - 'на, " + npchar.name + ", похорони с миром'. Или бродяг каких окаянных стража перебьёт, а старый " + npchar.name + " предает их бренные тела земле по христианскому обычаю.";
        link.l1 = "Ясно. Деньги, как говорится, не пахнут. Ладно, покажи мне свои товары.";
        link.l1.go = "trade";
        link.l2 = "Понятно. Мне пора идти. Приятно было познакомиться!";
        link.l2.go = "exit";
        break;

    case "trade":
        DialogExit();
        if (!CheckAttribute(npchar, "trade_date") || GetNpcQuestPastDayParam(npchar, "trade_date") >= 10)
        {
            GiveItemToTrader(npchar);
            SaveCurrentNpcQuestDateParam(npchar, "trade_date");
        }
        LaunchItemsTrade(npchar, 0);
        NextDiag.TempNode = "First time";
        break;

    case "fight":
        DialogExit();
        NextDiag.CurrentNode = NextDiag.TempNode;
        LAi_group_Attack(NPChar, Pchar);
        if (rand(3) != 1)
            SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
        AddDialogExitQuest("MainHeroFightModeOn");
        break;

    case "Exit":
        NextDiag.CurrentNode = NextDiag.TempNode;
        DialogExit();
        break;

    case "exit_setOwner":
        LAi_SetOwnerTypeNoGroup(npchar);
        NextDiag.CurrentNode = NextDiag.TempNode;
        DialogExit();
        break;

    case "Man_FackYou": //реакция на попытку залезть в сундук
        dialog.text = LinkRandPhrase("Да ты " + GetSexPhrase("вор, милейший! Стража, держи его", "воровка! Стража, держи ее") + "!!!", "Вот это да! Чуть я загляделся, а ты сразу в сундук с головой! Держи " + GetSexPhrase("вора", "воровку") + "!!!", "Стража! Грабят!!! Держи " + GetSexPhrase("вора", "воровку") + "!!!");
        link.l1 = "А-ать, дьявол!!!";
        link.l1.go = "fight";
        break;
    }
}