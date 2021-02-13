// Оеларт Котеел - канонир
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
            dialog.text = "Здравствуйте, минхер! Как вам погодка сегодня?";
            link.l1 = TimeGreeting() + ". Да меня погода любая устраивает, лишь бы не штормило в открытом море...";
            link.l1.go = "meeting";
            npchar.quest.meeting = "1";
        }
        else
        {
            dialog.text = "А, " + GetFullName(pchar) + "! " + TimeGreeting() + "! Вы что-то хотели?";
            link.l1 = LinkRandPhrase("Что-нибудь интересное мне расскажете?", "Что нового произошло на острове в последнее время?", "Не расскажете ли последние сплетни?");
            link.l1.go = "rumours_LSC";
            link.l2 = "Я хочу задать тебе пару вопросов об острове.";
            link.l2.go = "int_quests"; //информационный блок
            link.l5 = "Да просто решил узнать как у вас дела. Ещё увидимся!";
            link.l5.go = "exit";
        }
        NextDiag.TempNode = "First time";
        break;

    case "meeting": // первая встреча
        dialog.text = "Вы не поверите, но мне тоже. Я вас раньше не видел... меня зовут Оеларт Котеел, и я ещё совсем недавно был канониром голландского военного судна.";
        link.l1 = "" + GetFullName(pchar) + ". Да, я недавно на Острове. Можно сказать, только что прибыл.";
        link.l1.go = "meeting_1";
        break;

    case "meeting_1":
        dialog.text = "Я тоже здесь недавно, ещё и года не прошло. И, очень надеюсь, не задержусь, хотя все уверяют меня в обратном. Будем знакомы!";
        link.l1 = "Будем знакомы, " + npchar.name + "...";
        link.l1.go = "exit";
        link.l2 = LinkRandPhrase("Что-нибудь интересное мне расскажете?", "Что нового произошло на острове в последнее время?", "Не расскажете ли последние сплетни?");
        link.l2.go = "rumours_LSC";
        link.l3 = "Я хочу задать вам пару вопросов об острове.";
        link.l3.go = "int_quests"; //информационный блок
        NextDiag.TempNode = "First time";
        break;

        //--------------------------------------- блок вопросов и ответов ---------------------------------------------
    case "int_quests":
        dialog.text = "Внимательно вас слушаю.";
        if (!CheckAttribute(npchar, "quest.answer_1"))
        {
            link.l1 = "Как вы попали на Остров?";
            link.l1.go = "ansewer_1";
        }
        if (!CheckAttribute(npchar, "quest.answer_2"))
        {
            link.l2 = "Вы бы хотели отсюда убраться?";
            link.l2.go = "ansewer_2";
        }
        if (!CheckAttribute(npchar, "quest.answer_3"))
        {
            link.l3 = "Вы никогда не задумывались над тем, как появился этот Остров?";
            link.l3.go = "ansewer_3";
        }
        if (!CheckAttribute(npchar, "quest.answer_4"))
        {
            link.l4 = "Вы никогда не бывали на кораблях кланов?";
            link.l4.go = "ansewer_4";
        }
        link.l10 = "Нет вопросов. Извините...";
        link.l10.go = "exit";
        break;

    case "ansewer_1":
        dialog.text = "Достаточно банально. Мы вступили в бой с английской шхуной и стали одерживать верх. Англичане пустились в бегство, мы погнались за ними. Преследовали их больше суток, почти догнали, но негодяи метким выстрелом сбили нам грот-мачту и, конечно, скрылись\nА нас чуть не потопил внезапно налетевший шквал, затем подхватило сильное течение и в итоге разбило о рифы у наружнего кольца кораблей. Спастись удалось очень немногим...";
        link.l1 = "Понятно...";
        link.l1.go = "int_quests";
        npchar.quest.answer_1 = "true";
        break;

    case "ansewer_2":
        dialog.text = "Это моя мечта. Вы не представляете, как мне здесь всё опротивело. Вот только как это сделать? Не представляю. Кораблей тут нет, возможности построить - нет, а отправляться в путь на лодке или дырявой, криво сколоченной лоханке - самоубийство.";
        link.l1 = "Ясно...";
        link.l1.go = "int_quests";
        npchar.quest.answer_2 = "true";
        break;

    case "ansewer_3":
        dialog.text = "Вероятно, существует он не более ста лет, судя по кораблям, из которых он состоит. Но не исключено, что старше, ибо внешнее кольцо представляет собой нагромождение останков кораблей до самого дна. Возможно, что более древние суда находятся под водой\nА как образовался... думаю, течение и шторма сносили гибнущие корабли на рифы и мелководье, корабли тонули и постепенно образовали такую искусственную отмель из обломков кораблей. На ней уже и образовалось внешнее кольцо\nА внутренние корабли, на которых мы живём... или были одними из первых на Острове, или как-то попали через кольцо. Это вполне возможно - ведь пробрались же сквозь кольцо пираты адмирала на своём бриге.";
        link.l1 = "Интересно...";
        link.l1.go = "int_quests";
        npchar.quest.answer_3 = "true";
        break;

    case "ansewer_4":
        dialog.text = "Бывал, у ривадос. Как-то Чёрному Эдди потребовалась консультация по корабельным пушкам, уж не знаю, правда, зачем, так один из негров нашёл меня и передал пароль. Тогда-то я и побывал у них на 'Протекторе', а заодно и на 'Веласко'. Охрана у них поставлена сурово, не зная пароля - не пройдёшь, даже и не пытайся.";
        link.l1 = "Понятно...";
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
        dialog.text = LinkRandPhrase("Слушай, ты бы убрал оружие. А то нервируешь немного...", "Знаешь, у нас тут не принято сабелькой размахивать. Убери оружие.", "Слушай, что ты, как д'Артаньян, бегаешь тут, шпагой машешь? Убери оружие, не к лицу это серьезному мужчине...");
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