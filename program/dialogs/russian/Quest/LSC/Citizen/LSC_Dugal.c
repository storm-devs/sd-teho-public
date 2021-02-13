// Дугал Эббот - дворянин
#include "DIALOGS\russian\Rumours\Common_rumours.c"
void ProcessDialogEvent()
{
    ref NPChar, sld;
    aref Link, NextDiag;

    DeleteAttribute(&Dialog, "Links");

    makeref(NPChar, CharacterRef);
    makearef(Link, Dialog.Links);
    makearef(NextDiag, NPChar.Dialog);

    ProcessCommonDialogRumors(NPChar, Link, NextDiag);

    switch (Dialog.CurrentNode)
    {
    case "First time":
        if (CheckAttribute(pchar, "GenQuest.CitizenConflict") && sti(pchar.GenQuest.CitizenConflict) > 3)
        {
            dialog.text = "Я не желаю с тобой общаться. Ты нападаешь без причины на мирных граждан, провоцируешь их на драку. Уходи прочь!";
            link.l1 = "Гм...";
            link.l1.go = "exit";
            break;
        }
        if (npchar.quest.meeting == "0")
        {
            dialog.text = "Здравствуйте, сударь. Позвольте представиться - Дугалл Эббот. Приятно видеть приличного человека - сброд, обитающий здесь, мне уже порядком опротивел. Никогда бы не подумал, что остаток жизни мне придётся провести среди черни.";
            link.l1 = TimeGreeting() + ". Меня зовут " + GetFullName(pchar) + ". Приятно познакомиться. Чем вам жители Острова так не угодили?";
            link.l1.go = "meeting";
            npchar.quest.meeting = "1";
        }
        else
        {
            dialog.text = "А, " + GetFullName(pchar) + "! " + TimeGreeting() + "! Вы что-то хотели?";
            link.l1 = LinkRandPhrase("Что-нибудь интересное мне расскажете?", "Что нового произошло на острове в последнее время?", "Не расскажете ли последние сплетни?");
            link.l1.go = "rumours_LSC";
            link.l2 = "Я хочу задать вам пару вопросов об острове.";
            link.l2.go = "int_quests"; //информационный блок
            link.l5 = "Да просто решил узнать как у вас дела. Ещё увидимся!";
            link.l5.go = "exit";
        }
        NextDiag.TempNode = "First time";
        break;

    case "meeting": // первая встреча
        dialog.text = "Вы, видимо ещё их мало знаете. Вы ведь недавно здесь? Правда, я что-то не припомню в последнее время ни одного кораблекрушения...";
        link.l1 = "Меня прибило сюда на баркасе...";
        link.l1.go = "meeting_1";
        break;

    case "meeting_1":
        dialog.text = "Да, так часто случается - корабли тонут, а сюда добирается несколько выживших на шлюпках. И, бывает, живёт человек себе уже месяц на Острове, а ты его и в глаза не видел.";
        link.l1 = "Ясно. Приятно было познакомиться, мистер Эббот. Ещё увидимся!";
        link.l1.go = "exit";
        link.l2 = LinkRandPhrase("Что-нибудь интересное мне расскажете?", "Что нового произошло на острове в последнее время?", "Не расскажете ли последние сплетни?");
        link.l2.go = "rumours_LSC";
        link.l3 = "Я хочу задать вам пару вопросов об острове.";
        link.l3.go = "int_quests"; //информационный блок
        NextDiag.TempNode = "First time";
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

        //--------------------------------------- блок вопросов и ответов ---------------------------------------------
    case "int_quests":
        dialog.text = "Внимательно вас слушаю.";
        if (!CheckAttribute(npchar, "quest.answer_1"))
        {
            link.l1 = "А как вы сами попали на Остров?";
            link.l1.go = "ansewer_1";
        }
        if (!CheckAttribute(npchar, "quest.answer_2"))
        {
            link.l2 = "Что вы можете сказать о жителях Острова?";
            link.l2.go = "ansewer_2";
        }
        if (!CheckAttribute(npchar, "quest.answer_3"))
        {
            link.l3 = "Что вы можете сказать о кланах?";
            link.l3.go = "ansewer_3";
        }
        if (!CheckAttribute(npchar, "quest.answer_4"))
        {
            link.l4 = "А как здесь погода на Острове? Штормит часто?";
            link.l4.go = "ansewer_4";
        }
        link.l10 = "Нет вопросов. Извините...";
        link.l10.go = "exit";
        break;

    case "ansewer_1":
        dialog.text = "Это было пять лет назад, но я всё помню, словно это случилось вчера. В один злосчастный день я решил отправиться на своём флейте из Порт-Рояля в Белиз - уж очень ценной была партия груза, и я не мог никому доверить её продажу\nБуквально на следующий же день посыпалось несчастье за несчастьем: сначала боцман напился и вывалился за борт, потом мы чуть не наскочили на рифы, а в довершение штурман ошибся в вычислениях и отклонился от курса\nА потом за нами погнались испанцы - бриг и галеон. Мы не стали принимать бой и попытались от них оторваться, но они были настырны и преследовали нас целый день. Галеон отстал, но бриг в итоге настиг наш корабль\nОпасаясь галеона, мы не стали вступать в долгую перестрелку и сразу пошли на абордаж. Этого кастильские собаки не ожидали. Мы одолели мерзавцев, правда, ценой жизней почти всего экипажа\nА спустя несколько часов налетел шторм. Мы не смогли остатками команды бороться со стихией, и вот результат: наш флейт стоит во внешнем кольце кораблей, а я и ещё трое счастливчиков добрались до Острова.";
        link.l1 = "Понятно...";
        link.l1.go = "int_quests";
        npchar.quest.answer_1 = "true";
        break;

    case "ansewer_2":
        dialog.text = "Сброд. Натуральный сброд. Люмпены всех мастей, другой характеристики у меня для них нет. Вот, например, Ришард Шамбон - у него же на роже написано, что он жулик. А Виктор Кассель? Да ему убить человека проще, чем высморкаться. Джаспер Пратт - каторжник, Леонард Маскетт - пропойца... Дальше перечислять?\nЕдинственный нормальный человек, кроме вас, конечно, это Джозеф Лодердэйл - бывший военный офицер флота Англии. А ещё два человека дворянского происхождения - Антонио Бетанкур и Лоренцо Сольдерра - проклятые кастильцы, я с ними даже за один стол в таверне не сяду.";
        link.l1 = "Ясно...";
        link.l1.go = "int_quests";
        npchar.quest.answer_2 = "true";
        break;

    case "ansewer_3":
        dialog.text = "Сборище мерзавцев и негодяев. Правда, нас они не трогают. Им гораздо интереснее резать и стрелять друг дружку. Они без этого жить не могут. И хотя я пиратов терпеть не могу, но с их появлением на Острове стало значительно спокойнее - нарвалы и ривадос уже не устраивают кровавые бойни ежемесячно.";
        link.l1 = "Очень интересно...";
        link.l1.go = "int_quests";
        npchar.quest.answer_3 = "true";
        break;

    case "ansewer_4":
        dialog.text = "Да практически никогда. Штормы часто бушуют вокруг Острова, а вот здесь словно заколдованное место - тихо и спокойно. Может, за год раз пять налетит сильный шквал - вот и все дела. А что до дождей - так от них ущерба никакого.";
        link.l1 = "Занятно...";
        link.l1.go = "int_quests";
        npchar.quest.answer_4 = "true";
        break;
        // <-- блок вопросов и ответов

        //----------------------------------------- специальные реакции -----------------------------------------------
        //обнаружение ГГ в сундуках
    case "Man_FackYou":
        dialog.text = LinkRandPhrase("Что ты там копаешься, а? Да ты вор!", "Вот это да! Чуть я загляделся, а ты сразу в сундук с головой!", "По сундукам шарить вздумал?! Тебе это даром не пройдёт!");
        link.l1 = "А-ать, дьявол!!!";
        link.l1.go = "fight";
        break;

    case "Woman_FackYou":
        dialog.text = "Ах, вот, значит, как?! По сундукам шарить вздумал?! Тебе это даром не пройдёт!";
        link.l1 = "Вот дура!..";
        link.l1.go = "exit_setOwner";
        LAi_group_Attack(NPChar, Pchar);
        break;

    case "fight":
        NextDiag.CurrentNode = NextDiag.TempNode;
        DialogExit();
        LAi_SetOwnerTypeNoGroup(npchar);
        LAi_group_Attack(NPChar, Pchar);
        AddDialogExitQuest("MainHeroFightModeOn");
        break;

    case "exit_setOwner":
        LAi_SetOwnerTypeNoGroup(npchar);
        NextDiag.CurrentNode = NextDiag.TempNode;
        DialogExit();
        break;

    //замечание по обнаженному оружию
    case "LSCNotBlade":
        dialog.text = LinkRandPhrase("Слушай, ты бы убрал оружие. А то нервируешь немного...", "Знаешь, у нас тут не принято сабелькой размахивать. Убери оружие.", "Слушай, что ты, как д'Артаньян, бегаешь тут, шпагой машешь? Убери оружие, не к лицу это серьёзному мужчине...");
        link.l1 = LinkRandPhrase("Хорошо.", "Ладно.", "Как скажешь...");
        link.l1.go = "exit";
        NextDiag.TempNode = "First Time";
        break;

    case "CitizenNotBlade":
        if (loadedLocation.type == "town")
        {
            dialog.text = NPCharSexPhrase(NPChar, "Послушайте, я, как гражданин этого города, прошу вас не ходить у нас с обнажённым клинком.", "Знаете, я, как гражданка этого города, прошу вас не ходить у нас с обнажённым клинком.");
            link.l1 = LinkRandPhrase("Хорошо.", "Ладно.", "Как скажете...");
        }
        else
        {
            dialog.text = NPCharSexPhrase(NPChar, "Острожней на поворотах, приятель, когда бежишь с оружием в руках. Я ведь могу и занервничать...", "Мне не нравится, когда мужчины ходят передо мной с оружием на изготовку. Это меня пугает...");
            link.l1 = RandPhraseSimple("Понял.", "Убираю.");
        }
        link.l1.go = "exit";
        NextDiag.TempNode = "First Time";
        break;
        // <-- специальные реакции

    case "Exit":
        NextDiag.CurrentNode = NextDiag.TempNode;
        DialogExit();
        break;
    }
}