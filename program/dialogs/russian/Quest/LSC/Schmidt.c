// Юрген Шмидт - оружейник
#include "DIALOGS\russian\Rumours\Common_rumours.c"
void ProcessDialogEvent()
{
    ref NPChar, sld;
    aref Link, NextDiag;
    int iTemp, iRem;

    DeleteAttribute(&Dialog, "Links");

    makeref(NPChar, CharacterRef);
    makearef(Link, Dialog.Links);
    makearef(NextDiag, NPChar.Dialog);

    ProcessCommonDialogRumors(NPChar, Link, NextDiag);

    string NodeName = Dialog.CurrentNode;
    string NodePrevName = "";
    if (CheckAttribute(NextDiag, "PrevNode"))
        NodePrevName = NextDiag.PrevNode;

    switch (Dialog.CurrentNode)
    {
    case "First time":
        if (CheckAttribute(pchar, "GenQuest.NarvalConflict"))
        {
            dialog.text = "Послушайте, уважаемый, вы зачем руки так распустили, а? Пока вы с нами в ссоре - вам нечего делать в моей мастерской. Уходите!";
            link.l1 = "Гм...";
            link.l1.go = "exit";
            break;
        }
        if (npchar.quest.meeting == "0")
        {
            if (CheckAttribute(pchar, "questTemp.LSC.nrv_friend")) // стал другом нарвалов
            {
                dialog.text = "А, " + GetFullName(pchar) + "! Наслышан, наслышан о ваших делах. Приятно, что вы стали другом Дональда и нашим сторонником. Нарвалы умеют ценить дружбу, это я вам говорю точно.";
                link.l1 = "Надеюсь, что это так. Я могу рассчитывать на ваши услуги?";
                link.l1.go = "friend";
            }
            else
            {
                dialog.text = "Ну? Чего тебе надо?";
                link.l1 = TimeGreeting() + ". Меня зовут " + GetFullName(pchar) + ". Я просто знакомлюсь с людьми. Я вас отрываю от дел?";
                link.l1.go = "meeting";
            }
            npchar.quest.meeting = "1";
        }
        else
        {
            if (CheckAttribute(pchar, "questTemp.LSC.nrv_friend")) // стал другом нарвалов
            {
                dialog.text = "А, " + GetFullName(pchar) + "! Наслышан, наслышан о ваших делах. Приятно, что вы стали другом Дональда и нашим сторонником. Нарвалы умеют ценить дружбу, это я вам говорю точно.";
                link.l1 = "Надеюсь, что это так. Теперь я могу рассчитывать на ваши услуги?";
                link.l1.go = "friend";
            }
            else
            {
                dialog.text = "А, " + GetFullName(pchar) + "! Опять поболтать захотелось? Ну, так я вас разочарую - нет у меня на это ни времени, ни желания.";
                link.l1 = "Хорошо, не буду вас отвлекать.";
                link.l1.go = "exit";
            }
        }
        NextDiag.TempNode = "First time";
        break;

    case "meeting": // первая встреча
        dialog.text = "Точно! Вы меня отрываете от дел, сударь. Я Юрген Шмидт, кузнец и оружейник нарвалов, и обеспечиваю наш клан оружием. Но чтобы сделать хороший клинок, или починить механизм башенного мушкетона, или сделать новый замок и ключ - нужно время, терпение и внимательность. Поэтому я не люблю, когда меня отвлекают от работы.";
        link.l1 = "Вы делаете оружие? А заказать у вас что-нибудь можно?";
        link.l1.go = "meeting_1";
        break;

    case "meeting_1":
        dialog.text = "Нет. Я делаю оружие только для членов клана нарвал. Это мой принцип, и я от него не отступлю ни на шаг. Так что не рассчитывайте, сударь. Вступите в клан нарвал, или, как минимум, станьте нашим союзником - тогда и приходите, поговорим.";
        link.l1 = "Ладно. Тогда я пойду. Извините, что побеспокоил!";
        link.l1.go = "exit";
        NextDiag.TempNode = "First time";
        break;

    case "friend":
        dialog.text = "Можете. Друг нарвалов - мой друг, так что можете высказывать свои пожелания.";
        link.l1 = "Я бы хотел изготовить клинок под заказ.";
        link.l1.go = "blade";
        if (CheckAttribute(npchar, "quest.narval_blade") && pchar.questTemp.LSC.Mary == "alive")
        {
            link.l2 = "Я слышал, вы изготовили для покойного Алана Милроу особый клинок. Я видел этот палаш - великолепное оружие. Я мог бы у вас заказать себе такой же?";
            link.l2.go = "narval";
        }
        link.l3 = "Пока никаких пожеланий нет, ничего в голову не приходит. Подумаю - и обязательно вернусь!.";
        link.l3.go = "exit";
        NextDiag.TempNode = "Jurgen";
        break;

    case "Jurgen":
        if (pchar.questTemp.LSC == "return" && !CheckAttribute(npchar, "quest.return_isl"))
        {
            dialog.text = "Ха, " + GetFullName(pchar) + "! Так ты не утонул? Вот это да! Ты точно не мертвец?";
            link.l1 = "Не беспокойся, Юрген. Живой! Я тонуть и не собирался - это вы тут напридумывали невесть чего...";
            link.l1.go = "exit";
            npchar.quest.return_isl = "true";
            NextDiag.TempNode = "Jurgen";
            break;
        }
        dialog.text = "А, " + GetFullName(pchar) + "! По какому делу пожаловали?";
        if (CheckAttribute(npchar, "quest.narval_blade") && npchar.quest.narval_blade == "ferrum")
        {
            if (GetCharacterItem(pchar, "jewelry11") >= 3)
            {
                link.l4 = "Я принёс три куска особого железа, как вы и просили. Гляньте - это оно?";
                link.l4.go = "narval_7";
            }
            if (CheckCharacterItem(pchar, "meteorite"))
            {
                link.l5 = "Гляньте сюда, Юрген. Я нашёл интересный слиток железа на дне, но он весит гораздо больше, чем вы говорили - в нем не меньше пяти фунтов.";
                link.l5.go = "narval_7_1";
            }
        }
        if (!CheckAttribute(npchar, "quest.blade_done"))
        {
            link.l1 = "Я бы хотел изготовить клинок под заказ.";
            if (!CheckAttribute(npchar, "quest.blade_rules"))
                link.l1.go = "blade";
            else
                link.l1.go = "blade_4";
        }
        if (CheckAttribute(npchar, "quest.blade_payseek"))
        {
            link.l1 = "Я принёс ещё дублонов в счёт оплаты за клинок.";
            link.l1.go = "blade_3";
        }
        if (CheckAttribute(npchar, "quest.narval_blade") && pchar.questTemp.LSC.Mary == "alive" && npchar.quest.narval_blade == "begin" && pchar.questTemp.LSC != "return") // patch-9
        {
            link.l2 = "Я слышал, вы изготовили для покойного Алана Милроу особый клинок. Я видел этот палаш - великолепное оружие. Я мог бы у вас заказать себе такой же?";
            link.l2.go = "narval";
        }
        if (CheckAttribute(npchar, "blade_date") && GetNpcQuestPastDayParam(npchar, "blade_date") >= 20)
        {
            link.l1 = "Я пришёл за своим заказом. Он уже должен быть готов, как я понимаю?";
            link.l1.go = "blade_done_2";
        }
        link.l3 = "Да нет, ничего, просто зашёл поздороваться.";
        link.l3.go = "exit";
        NextDiag.TempNode = "Jurgen";
        break;

    // --> заказ клинков
    case "blade":
        dialog.text = "Хорошо. Но у меня есть определённые требования к заказу, так что выслушайте сначала, а потом решайте - заказывать, или нет.";
        link.l1 = "Я вас внимательно слушаю.";
        link.l1.go = "blade_1";
        break;

    case "blade_1":
        dialog.text = "Вы можете заказать у меня только один клинок и только один раз. Также я не принимаю заказа какого-то конкретного клинка, вы можете выбрать только тип, который хотите - рапиру, саблю или палаш, а уж что получится выковать - будет зависеть от того, какие материалы у меня в наличии на данный момент\nТак что хорошенько подумайте, прежде чем сделать выбор. Далее. Срок изготовления - двадцать дней. Оплата - исключительно в дублонах. Ставка у меня фиксированная, за любой клинок - тысяча золотых. Деньги вперёд.";
        link.l1 = "Ого! Недёшево, однако...";
        link.l1.go = "blade_2";
        break;

    case "blade_2":
        dialog.text = "Да, недёшево. Но и клинки я делаю соответствующего качества, так что цена оправдана. Впрочем, я вас не принуждаю: хотите - заказывайте, хотите - нет.";
        link.l1 = "Я вас понял, Юрген. Да, я хочу сделать заказ.";
        link.l1.go = "blade_3";
        link.l2 = "Хм. Пожалуй, мне стоит хорошенько подумать, прежде чем решиться на заказ. Вернёмся к этому разговору позже!";
        link.l2.go = "exit";
        NextDiag.TempNode = "Jurgen";
        npchar.quest.blade_rules = "true";
        npchar.quest.blade_dublon = 1000;
        AddQuestRecord("LSC", "17");
        break;

    case "blade_3":
        dialog.text = "Очень хорошо. Тогда давайте ваши дублоны.";
        if (CheckCharacterItem(pchar, "gold_dublon"))
        {
            npchar.quest.blade_pay = GetCharacterItem(pchar, "gold_dublon");
            link.l1 = "Вот, пожалуйста. У меня есть с собой " + FindRussianQtyString(sti(npchar.quest.blade_pay)) + ".";
            link.l1.go = "blade_pay";
        }
        link.l2 = "Хм. У меня сейчас их с собой нет, к сожалению. Но я обязательно принесу, и мы вернёмся к этому разговору.";
        link.l2.go = "exit";
        NextDiag.TempNode = "Jurgen";
        break;

    case "blade_4":
        dialog.text = "Вы всё-таки сделали свой выбор? Хорошо подумали?";
        link.l1 = "Да. Я полностью определился.";
        link.l1.go = "blade_3";
        break;

    case "blade_pay":                                                     // оплата
        if (sti(npchar.quest.blade_dublon) < sti(npchar.quest.blade_pay)) // полная сумма
        {
            npchar.quest.blade_pay = sti(npchar.quest.blade_dublon);
            iTemp = 0;
        }
        else
            iTemp = sti(npchar.quest.blade_dublon) - sti(npchar.quest.blade_pay);
        npchar.quest.blade_dublon = iTemp; // запоминаем остаток
        RemoveItems(pchar, "gold_dublon", sti(npchar.quest.blade_pay));
        Log_Info("Вы отдали " + sti(npchar.quest.blade_pay) + " дублонов");
        PlaySound("interface\important_item.wav");
        if (iTemp == 0)
        {
            dialog.text = "Отлично. Теперь, когда вы оплатили мою работу и материалы, я могу приступить к делу.";
            link.l1 = "Я могу делать заказ?";
            link.l1.go = "blade_done";
        }
        else
        {
            dialog.text = "Хорошо. Я принимаю у вас дублоны. Вам осталось принести ещё " + FindRussianQtyString(sti(npchar.quest.blade_dublon)) + ".";
            link.l1 = "Как только соберу ещё дублонов - немедленно принесу вам.";
            link.l1.go = "exit";
            npchar.quest.blade_payseek = "true";
        }
        break;

    case "blade_done":
        DeleteAttribute(npchar, "quest.blade_payseek");
        dialog.text = "Конечно! Какая группа вам по душе - рапиры, сабли или палаши?";
        link.l1 = "Рапиры. Люблю изящное легкое оружие.";
        link.l1.go = "rapier";
        link.l2 = "Сабли. Это оптимальный вариант с моей точки зрения.";
        link.l2.go = "sabre";
        link.l3 = "Конечно же, палаши! Рубить так рубить, как говорится!";
        link.l3.go = "palash";
        break;

    case "rapier":
        npchar.quest.blade_done = SelectJurgenBladeDone("rapier");
        dialog.text = "Как скажете. За заказом приходите через двадцать дней, не раньше.";
        link.l1 = "Спасибо! Буду в указанное время. До свидания, Юрген.";
        link.l1.go = "blade_done_1";
        break;

    case "sabre":
        npchar.quest.blade_done = SelectJurgenBladeDone("sabre");
        dialog.text = "Как скажете. За заказом приходите через двадцать дней, не раньше.";
        link.l1 = "Спасибо! Буду в указанное время. До свидания, Юрген.";
        link.l1.go = "blade_done_1";
        break;

    case "palash":
        npchar.quest.blade_done = SelectJurgenBladeDone("palash");
        dialog.text = "Как скажете. За заказом приходите через двадцать дней, не раньше.";
        link.l1 = "Спасибо! Буду в указанное время. До свидания, Юрген.";
        link.l1.go = "blade_done_1";
        break;

    case "blade_done_1":
        DialogExit();
        SaveCurrentNpcQuestDateParam(npchar, "blade_date");
        NextDiag.CurrentNode = "Jurgen";
        AddQuestRecord("LSC", "18");
        break;

    case "blade_done_2":
        dialog.text = "Да. Ваш клинок готов. Пожалуйста, получите и владейте на здоровье. Как только вы возьмёте его в руки, сразу поймёте, что он стоит затраченных на него денег.";
        link.l1 = "Спасибо, Юрген.";
        link.l1.go = "blade_done_3";
        break;

    case "blade_done_3":
        DialogExit();
        NextDiag.CurrentNode = "Jurgen";
        GiveItem2Character(pchar, npchar.quest.blade_done);
        PlaySound("interface\important_item.wav");
        DeleteAttribute(npchar, "blade_date");
        break;

    // заказ палаша Нарвал для Мэри
    case "narval":
        dialog.text = "Увы, дружище, но тут я вам вынужден отказать по двум причинам. Во-первых, такой палаш я возьмусь делать только для члена клана нарвал, и то - не для каждого. А во-вторых, у меня нет материала для его изготовления.";
        link.l1 = "А что за особое железо для него нужно? Я слышал, что его доставали со дна...";
        link.l1.go = "narval_1";
        break;

    case "narval_1":
        dialog.text = "Именно так. Куски этого железа разбросаны на нашем мелководье. Откуда они тут взялись - мне неведомо. Но железо действительно уникальное - не ржавеет вообще, а клинки из него не тупятся. Так что если бы вы каким-то образом достали это железо - можно было бы решить вопрос. Но опять же проблема - вы не нарвал...";
        link.l1 = "Хм. А то, что я не нарвал - это имеет настолько принципиальное значение?";
        link.l1.go = "narval_2";
        break;

    case "narval_2":
        dialog.text = "Да. Воспринимайте это как мою причуду, если хотите, но такой палаш я буду делать только для нарвала.";
        link.l1 = "Так... Ладно, приму, как неизбежность. Но у меня возникла другая мысль. А могу ли я заказать этот клинок в подарок для члена клана нарвал?";
        link.l1.go = "narval_3";
        break;

    case "narval_3":
        dialog.text = "Гм. Ну, если вы принесёте мне железо для изготовления, то наверное, да. Это никак не будет противоречить принципу... А для кого вы хотите сделать этот палаш?";
        link.l1 = "Для Красной Мэри. Она из клана нарвал, и вполне заслуживает право владеть таким замечательным оружием.";
        link.l1.go = "narval_4";
        break;

    case "narval_4":
        dialog.text = "Ха! Я мог бы догадаться и сам. Старею... Ну что же, я согласен. Мэри будет просто в восторге от такого подарка, я уверен... Несите железо - и я сделаю палаш. За работу я возьму... а, впрочем, ничего не надо. Пусть это будет подарок не только от вас, но и от меня.";
        link.l1 = "Спасибо! Сколько вам нужно железа для его изготовления?";
        link.l1.go = "narval_5";
        break;

    case "narval_5":
        dialog.text = "Куски, которые находили на дне, были все примерно одинакового размера - по фунту с небольшим. Мне нужно три куска.";
        link.l1 = "Хорошо. Я постараюсь добыть их. Тогда и вернёмся к нашему разговору.";
        link.l1.go = "narval_6";
        break;

    case "narval_6":
        DialogExit();
        npchar.quest.narval_blade = "ferrum";
        NextDiag.CurrentNode = "Jurgen";
        // кладем гигантский кусок метеорита на дно
        sld = ItemsFromID("meteorite");
        sld.shown = true;
        sld.startLocation = "underwater";
        sld.startLocator = "item" + (rand(7) + 1);
        Log_TestInfo("Метеорит в локаторе" + sld.startLocator);
        pchar.quest.LSC_narval_ferrum.win_condition.l1 = "item";
        pchar.quest.LSC_narval_ferrum.win_condition.l1.item = "meteorite";
        pchar.quest.LSC_narval_ferrum.function = "LSC_NarvalFerrum";
        AddQuestRecord("LSC", "19");
        break;

    case "narval_7":
        RemoveItems(pchar, "jewelry11", 3);
        PlaySound("interface\important_item.wav");
        dialog.text = "Ну-ка, покажите... Да, точно - оно! Это было трудно - отыскать такие небольшие куски на дне?";
        link.l1 = "Ну, как сказать... Но ради Мэри ведь можно было постараться, не так ли?";
        link.l1.go = "narval_8";
        pchar.quest.LSC_narval_ferrum.over = "yes"; //снять прерывание
        break;

    case "narval_7_1":
        RemoveItems(pchar, "meteorite", 1);
        PlaySound("interface\important_item.wav");
        dialog.text = "Ну-ка, покажите... Ого! Да, это то самое донное железо, но таких огромных кусков я ещё не видал. Его одного с лихвой хватит для изготовления палаша. Это было, наверное, трудно - найти его?";
        link.l1 = "Ну, как сказать... Но ради Мэри ведь можно было постараться, не так ли?";
        link.l1.go = "narval_8";
        break;

    case "narval_8":
        dialog.text = "Вы нравитесь мне всё больше и больше, " + pchar.name + "... Ну что же, отлично. Теперь пришло время и мне постараться для нашей прекрасной амазонки. Работа займёт два дня - я оставлю все прочие заказы и займусь палашом\nПриходите послезавтра ко мне вдвоём с Мэри. Только не говорите ей ничего заранее - сделаем сюрприз. Она будет радоваться, как ребёнок.";
        link.l1 = "Хорошо, Юрген. Договорились. Тогда - до послезавтра!";
        link.l1.go = "narval_9";
        break;

    case "narval_9":
        DialogExit();
        npchar.quest.narval_blade = "work";
        NextDiag.CurrentNode = "narval_10";
        SetFunctionTimerCondition("LSC_NarvalBladeForMary", 0, 0, 2, false); // таймер
        AddQuestRecord("LSC", "21");
        break;

    case "narval_10":
        dialog.text = "" + pchar.name + ", не отвлекайте меня. Вы же хотите, чтобы палаш был готов вовремя?";
        link.l1 = "Да, конечно. Я уже ухожу...";
        link.l1.go = "exit";
        NextDiag.TempNode = "narval_10";
        break;

        //----------------------------------------- специальные реакции -----------------------------------------------
        //обнаружение ГГ в сундуках
    case "Man_FackYou":
        dialog.text = LinkRandPhrase("Что ты там копаешься, а? Да ты вор!", "Вот это да! Чуть я загляделся, а ты сразу в сундук с головой!", "По сундукам шарить вздумал?! Тебе это даром не пройдёт!");
        link.l1 = "А-ать, дьявол!!!";
        link.l1.go = "fight";
        break;

    case "fight":
        NextDiag.CurrentNode = NextDiag.TempNode;
        DialogExit();
        LAi_SetOwnerTypeNoGroup(npchar);
        LAi_group_Attack(NPChar, Pchar);
        AddDialogExitQuest("MainHeroFightModeOn");
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

string SelectJurgenBladeDone(string _sType)
{
    string sBlade;
    switch (_sType)
    {
    case "rapier":
        if (sti(pchar.rank) > 15)
            sBlade = "q_blade_18";
        else
            sBlade = "q_blade_16";
        break;

    case "sabre":
        if (sti(pchar.rank) > 15)
            sBlade = "q_blade_19";
        else
            sBlade = "q_blade_10";
        break;

    case "palash":
        if (sti(pchar.rank) > 15)
            sBlade = "q_blade_21";
        else
            sBlade = "q_blade_13";
        break;
    }
    return sBlade;
}