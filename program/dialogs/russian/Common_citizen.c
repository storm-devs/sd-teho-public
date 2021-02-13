// boal 25/04/04 общий диалог горожан
#include "DIALOGS\russian\Rumours\Common_rumours.c" //homo 25/06/06
void ProcessDialogEvent()
{
    ref NPChar, sld;
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
    ProcessCommonDialogRumors(NPChar, Link, NextDiag); //homo 16/06/06
    int iTest, iTemp;
    iTest = FindColony(NPChar.City); // город
    ref rColony;
    string sTemp, sCity;
    if (iTest != -1)
    {
        rColony = GetColonyByIndex(iTest);
    }

    String attrLoc = Dialog.CurrentNode;

    if (HasSubStr(attrLoc, "RumourAboutOwners_"))
    {
        NPChar.RumourOwnerType = FindStringAfterChar(attrLoc, "_");
        Dialog.CurrentNode = "RumourAboutOwners_TakeRumour";
    }

    switch (Dialog.CurrentNode)
    {
    case "Exit":
        NextDiag.CurrentNode = NextDiag.TempNode;
        DialogExit();
        break;

    case "fight":
        LAi_group_Attack(NPChar, Pchar);
        NextDiag.CurrentNode = NextDiag.TempNode;
        DialogExit();
        break;

    case "First time":
        /*if (GetNationRelation2MainCharacter(sti(NPChar.nation)) == RELATION_ENEMY && sti(NPChar.nation) != PIRATE)
            {
                dialog.text = RandPhraseSimple("Шпион? Стража!!!!!", "Караул! В городе враг!");
                link.l1 = "Заткнись! Я уже ухожу.";
                link.l1.go = "fight";
                break;
            }*/

        if (sti(NPChar.nation) == PIRATE)
        {
            if (sti(rColony.HeroOwn) == true) // наш горожанин
            {
                dialog.text = RandPhraseSimple("Ходит слух, что вы и есть владел" + GetSexPhrase("ец", "ица") + " этого города, " + GetSexPhrase("сэр", "мисс") + ".", "Какая приятная встреча, сам" + GetSexPhrase("", "а") + " глава города обратил" + GetSexPhrase("ся", "ась") + " ко мне с вопросом.");
                link.l1 = RandPhraseSimple("Я передумал" + GetSexPhrase("", "а") + ". Удачи!", "Просто осматриваю город. До свидания.");
                link.l1.go = "exit";
                link.l2 = RandPhraseSimple("У меня есть вопрос к тебе.", "Мне нужна информация.");
                link.l2.go = "quests"; //(перессылка в файл города)
                if (CheckAttribute(pchar, "GenQuest.Loan.FindCitizen") && !CheckAttribute(pchar, "GenQuest.Loan.FindCitizenDone") && !CheckAttribute(pchar, "GenQuest.Loan.FindCitizenFalied"))
                {
                    if (Characters[sti(pchar.GenQuest.Loan.FindCitizenIdx)].id == Npchar.id)
                    {
                        link.l3 = RandPhraseSimple("Хочу обсудить финансовые дела.", "Касательно финансов...");
                        link.l3.go = "LoanForAll"; //(перессылка в кредитный генератор)
                    }
                }
                break;
            }
            else
            { // пираты, не наши
                dialog.text = RandPhraseSimple("Чего тебе? Проходи мимо.", "Хватит загораживать дорогу, отвали.");
                link.l1 = RandPhraseSimple("Знаешь что? Не гавкай!", "Поумерь свой пыл. Не то быстро охлажу его!");
                link.l1.go = "exit";
                link.l2 = RandPhraseSimple("Хочу спросить тебя.", "Минутку внимания, всего один вопрос.");
                link.l2.go = "quests"; //(перессылка в файл города)
                if (CheckAttribute(pchar, "GenQuest.Loan.FindCitizen") && !CheckAttribute(pchar, "GenQuest.Loan.FindCitizenDone") && !CheckAttribute(pchar, "GenQuest.Loan.FindCitizenFalied"))
                {
                    if (Characters[sti(pchar.GenQuest.Loan.FindCitizenIdx)].id == Npchar.id)
                    {
                        link.l3 = RandPhraseSimple("Хочу обсудить финансовые дела.", "Касательно финансов...");
                        link.l3.go = "LoanForAll"; //(перессылка в кредитный генератор)
                    }
                }
                break;
            }
        }
        if (NPChar.quest.meeting == "0")
        {
            NPChar.quest.meeting = "1";

            // homo 05/08/06
            dialog.Text = NPCharRepPhrase(npchar,
                                          LinkRandPhrase("Меня зовут ", "Моё имя ", "Можешь называть меня ") + GetFullName(npchar) + LinkRandPhrase(". Чего тебе нужно?", ". Я тебя раньше здесь не " + NPCharSexPhrase(NPChar, "видел", "видела") + ", кто ты так" + GetSexPhrase("ой", "ая") + "?", ". Кто ты и что тебе от меня надо?"),

                                          LinkRandPhrase("Приветствую вас, " + GetAddress_Form(NPChar) + ". Моё имя " + GetFullName(npchar) + ". А как зовут вас?",
                                                         "Здравствуйте, " + GetAddress_Form(NPChar) + "! Я " + GetFullName(npchar) + ". Могу я узнать ваше имя?",
                                                         "Да, " + GetAddress_Form(NPChar) + ". Что вы хотели? Кстати, меня зовут " + GetFullName(npchar) + ". А вас?"));

            Link.l1 = pcharrepphrase(
                LinkRandPhrase("Разрази меня гром! ", "Тысяча чертей! ", "Чтоб тебе пусто было! ") + "Да я капитан " + GetFullName(Pchar) + LinkRandPhrase(", ты разве не слыхал" + NPCharSexPhrase(NPChar, "", "а") + " обо мне" + NPCharSexPhrase(NPChar, ", каналья?", "?"), " и " + GetSexPhrase("самый известный пират", "самая известная женщина-пират") + " в этих водах! ", " и провалиться мне на этом месте, если это не так!"),
                LinkRandPhrase("Я " + GetFullName(Pchar) + ", капитан.", "Меня зовут " + GetFullName(Pchar) + ".", "Можешь называть меня капитан " + GetFullName(Pchar)));

            //LinkRandPhrase("Я " + GetFullName(Pchar) + ", капитан.", "Меня зовут " + GetFullName(Pchar) + ".", "Можешь называть меня капитан " + GetFullName(Pchar));
            Link.l1.go = "Meeting";
        }
        else
        {
            if (rand(5) == 1 && NPChar.sex == "woman" && !CheckAttribute(NPChar, "CitizenFindItem.NoQuest") && !CheckAttribute(PChar, "GenQuest.CitizenFindItem.StartQuest") && CheckAttribute(NPChar, "City"))
            {
                dialog.Text = "Капитан, вы не могли бы помочь мне в одном деле?";
                link.l1 = LinkRandPhrase("Извини, нет. У меня сейчас очень мало времени.", "Прости, не могу. Дела...", "Нет, не могу. У меня сейчас очень много важных дел.");
                link.l1.go = "CitizenFindItem_NoQuest";
                link.l2 = LinkRandPhrase("Конечно. Что за дело?", "Да, помогу. Расскажите мне, что это за дело...", "Расскажите мне об этом деле поподробнее...");
                link.l2.go = "CitizenFindItem_1";
                NextDiag.TempNode = "First time";
                break;
            }

            if (CheckAttribute(PChar, "GenQuest.CitizenFindItem.CitizenID") && PChar.GenQuest.CitizenFindItem.CitizenID == NPChar.ID && CheckCharacterItem(PChar, "DOjeronRing"))
            {
                dialog.Text = "Да капитан, я вас слушаю.";
                link.l1 = NPChar.name + ", я наш" + GetSexPhrase("ел", "ла") + " ваше обручальное кольцо.";
                link.l1.go = "CitizenFindItem_Complete_1";
                break;
            }

            link.l1 = PCharRepPhrase("Хотел" + GetSexPhrase("", "а") + " кое-что узнать об этом городишке!", "Хотел" + GetSexPhrase("", "а") + " узнать кое-что о городе.");
            link.l1.go = "new question";
            link.l2 = RandPhraseSimple("У меня есть вопрос к тебе.", "Мне нужна информация.");
            if (CheckCharacterItem(pchar, "CaptainBook"))
            {
                if ((pchar.questTemp.different.GiveShipLetters.city == npchar.city) && CheckAttribute(pchar, "questTemp.different.GiveShipLetters"))
                {
                    link.l2.go = "ShipLetters_7"; // генератор  "Найденные документы"
                }
                else
                {
                    link.l2.go = "quests";
                }
            }
            else
            {
                link.l2.go = "quests"; //(перессылка в файл города)
            }
            if (CheckAttribute(pchar, "GenQuest.Loan.FindCitizen") && !CheckAttribute(pchar, "GenQuest.Loan.FindCitizenDone") && !CheckAttribute(pchar, "GenQuest.Loan.FindCitizenFalied"))
            {
                if (Characters[sti(pchar.GenQuest.Loan.FindCitizenIdx)].id == Npchar.id)
                {
                    link.l3 = RandPhraseSimple("Хочу обсудить финансовые дела.", "Касательно финансов...");
                    link.l3.go = "LoanForAll"; //(перессылка в кредитный генератор)
                }
            }
            // --> квестовый генератор мэра, поиск шпиёна на улице. eddy
            if (CheckAttribute(pchar, "GenQuest.SeekSpy.City") && pchar.location == (npchar.city + "_town"))
            {
                link.l4 = NPCharSexPhrase(npchar, LinkRandPhrase("Стойте! Немедленно скажите мне, кто вы такой?! Я ищу вражеского лазутчика по поручению губернатора " + XI_ConvertString("Colony" + characters[GetCharacterIndex(pchar.GenQuest.SeekSpy.MayorId)].city + "Gen") + "!", "Немедленно стой! Я действую в интересах города " + XI_ConvertString("Colony" + characters[GetCharacterIndex(pchar.GenQuest.SeekSpy.MayorId)].city + "Gen") + " по поручению губернатора. Ищу в городе вражеского агента.", "Стоять, приятель! Местный губернатор " + characters[GetCharacterIndex(pchar.GenQuest.SeekSpy.MayorId)].lastname + " очень хочет разыскать шпиона в городе."),
                                          LinkRandPhrase("Женщина, стойте! Немедленно скажите мне, кто вы такая?! Я ищу вражеского лазутчика по поручению губернатора " + XI_ConvertString("Colony" + characters[GetCharacterIndex(pchar.GenQuest.SeekSpy.MayorId)].city + "Gen") + "!",
                                                         "Женщина, я долж" + GetSexPhrase("ен", "на") + " вас задержать! Я действую в интересах города " + XI_ConvertString("Colony" + characters[GetCharacterIndex(pchar.GenQuest.SeekSpy.MayorId)].city + "Gen") + " по поручению губернатора. Ищу в городе вражеского агента.",
                                                         "Постой, красавица! Местный губернатор " + characters[GetCharacterIndex(pchar.GenQuest.SeekSpy.MayorId)].lastname + " очень хочет разыскать шпиона в городе..."));
                link.l4.go = "SitySpy";
            }
            // <-- квестовый генератор мэра, поиск шпиёна на улице

            //Jason --> генератор Неудачливый вор
            if (CheckAttribute(pchar, "GenQuest.Device.Shipyarder") && NPChar.location == pchar.GenQuest.Device.Shipyarder.City + "_town" && pchar.GenQuest.Device.Shipyarder == "begin" && !CheckAttribute(npchar, "quest.Device"))
            {
                link.l16 = "Послушайте, может вы мне подскажете. Я хочу купить " + pchar.GenQuest.Device.Shipyarder.Type + ", и мне сказали, что у вас в городе она продавалась. Ну, кто-то продавал на улицах. Ничего об этом сказать не можете?";
                link.l16.go = "Device_Citizen";
            }
            // <-- генератор Неудачливый вор

            // Квестовый генератор священника. Квест №2. Warship -->
            if (CheckAttribute(PChar, "GenQuest.ChurchQuest_2.AskPeople") && !CheckAttribute(NPChar, "GenQuest.ChurchQuest_2.AskedPeople") && NPChar.location == PChar.GenQuest.ChurchQuest_2.QuestTown + "_town")
            {
                    link.l5 = LinkRandPhrase("Ты в курсе", "Ты знаешь", "Ты знаешь что-нибудь о том") + ", что недавно была ограблена местная церковь?");
                    link.l5.go = "Citiz_GenQuest_Church_2_1";
            }
            // <-- Квестовый генератор священника. Квест №2.

            dialog.Text = NPCharRepPhrase(npchar,
                                          PCharRepPhrase(LinkRandPhrase("А, это ты " + GetFullName(Pchar) + " " + GetSexPhrase("- старый пройдоха", "- отчаянная деваха") + "", "Рад тебя видеть, " + GetSexPhrase("старина", "красавица") + " " + Pchar.name, "О, да это же " + GetSexPhrase("сам капитан", "сама") + " " + GetFullName(Pchar)) + LinkRandPhrase(". Думал, тебя уже нет на этом свете!", ". И, наверное, " + GetSexPhrase("как всегда пьян.", "уже слегка навеселе.") + "", ". И, как вижу, ещё на свободе!") + LinkRandPhrase(" Ну, говори, чего тебе нужно?", " Чего тебе на этот раз?", " Опять тревожишь меня по пустякам?"),
                                                         LinkRandPhrase(TimeGreeting() + ", капитан ", "Здравствуйте, " + GetAddress_Form(NPChar) + " ", "Приветствую вас, капитан ") + GetFullName(Pchar) + LinkRandPhrase(". Что может быть нужно " + GetSexPhrase("такому почтенному человеку", "такой бравой девушке") + ", как вы, от меня?", ". Зачем вы пришли?", ". Что на этот раз вы хотите узнать?")

                                                             ),

                                          PCharRepPhrase(LinkRandPhrase("Здравствуйте, капитан ", "Приветствую, ах это вы " + GetAddress_Form(NPChar) + " ", "А, капитан ") + GetFullName(Pchar) + LinkRandPhrase(", я думал" + NPCharSexPhrase(NPChar, " ", "а ") + "мы больше с вами не встретимся,", ", не скажу, что рад" + NPCharSexPhrase(NPChar, " ", "а ") + "вас видеть, но", ", вижу, вы ещё живы, прискорбно, а") + LinkRandPhrase(" что вам нужно?", " зачем вы пришли?", " чем могу быть " + NPCharSexPhrase(NPChar, "полезен?", "полезна?")),
                                                         LinkRandPhrase(TimeGreeting() + ", капитан " + GetFullName(Pchar) + ". Чем могу помочь?",
                                                                        "О, да это же сам" + GetSexPhrase("", "а") + " капитан " + GetFullName(Pchar) + "! Что вы хотите узнать на этот раз?",
                                                                        "Здравствуйте, " + GetAddress_Form(NPChar) + " " + Pchar.lastname + ". Вы что-то хотели?")));
            link.l6 = PCharRepPhrase(RandPhraseSimple("Тебе послышалось, я пойду.", "Нет, ничего - просто ш" + GetSexPhrase("ёл", "ла") + " в таверну."),
                                     RandPhraseSimple("Ладно, ничего. Удачи!", "Просто осматриваю город. До свидания."));
            link.l6.go = "exit";
        }
        NextDiag.TempNode = "First time";
        break;

    case "ShipLetters_7":
        dialog.text = "Какие вопросы?";
        link.l1 = "Вам ничего не говорит имя в этих бумагах?";
        link.l1.go = "ShipLetters_8";
        break;

    case "ShipLetters_8":
        dialog.text = LinkRandPhrase("Мне нет дела до незнакомых бумаг, да и читать я не умею. Ступайте к ростовщику, он, говорят, и дьявольской грамоте обучен.",
                                     "Понятия не имею о чём Вы говорите, поспрашивайте ещё жителей этого города, капитан " + GetFullName(Pchar) + ".",
                                     "Даже не знаю как Вам помочь, капитан " + GetFullName(Pchar) + ". Попробуйте обратиться к ростовщику, может он знает?");
        link.l1 = "С удовольствием воспользуюсь Вашим советом!";
        link.l1.go = "exit";
        break;

    case "Meeting":
        dialog.Text = NPCharRepPhrase(npchar, LinkRandPhrase("А ты не врёшь, капитан " + GetFullName(Pchar) + "?", "И что с того " + PChar.name + "?", "Я запомню тебя, " + GetFullName(Pchar) + ".") + " А теперь говори, чего тебе надо?",
                                      LinkRandPhrase("Приятно познакомиться, капитан " + PChar.name,
                                                     "Рад" + NPCharSexPhrase(NPChar, " ", "а ") + " нашему знакомству, " + GetAddress_Form(NPChar) + " " + PChar.lastname,
                                                     "Очень приятно, капитан " + PChar.name) +
                                          ". Но вряд ли вы просто хотели узнать моё имя, не так ли?");

        link.l1 = PCharRepPhrase("Хотел" + GetSexPhrase("", "а") + " кое-что узнать об этом городишке!", "Хотел" + GetSexPhrase("", "а") + " узнать кое-что о городе.");
        link.l1.go = "new question";
        Link.l2 = RandPhraseSimple("У меня есть вопрос к тебе.", "Мне нужна информация.");
        if (CheckCharacterItem(pchar, "CaptainBook"))
        {
            if ((pchar.questTemp.different.GiveShipLetters.city == npchar.city) && CheckAttribute(pchar, "questTemp.different.GiveShipLetters"))
            {
                link.l2.go = "ShipLetters_7"; // генератор  "Найденные документы"
            }
            else
            {
                Link.l2.go = "quests";
            }
        }
        else
        {
            link.l2.go = "quests"; //(перессылка в файл города)
        }
        if (CheckAttribute(pchar, "GenQuest.Loan.FindCitizen") && !CheckAttribute(pchar, "GenQuest.Loan.FindCitizenDone") && !CheckAttribute(pchar, "GenQuest.Loan.FindCitizenFalied"))
        {
            if (Characters[sti(pchar.GenQuest.Loan.FindCitizenIdx)].id == Npchar.id)
            {
                link.l3 = RandPhraseSimple("Хочу обсудить финансовые дела.", "Касательно финансов...");
                link.l3.go = "LoanForAll"; //(перессылка в кредитный генератор)
            }
        }

        //Jason --> генератор Неудачливый вор
        if (CheckAttribute(pchar, "GenQuest.Device.Shipyarder") && NPChar.location == pchar.GenQuest.Device.Shipyarder.City + "_town" && pchar.GenQuest.Device.Shipyarder == "begin" && !CheckAttribute(npchar, "quest.Device"))
        {
            link.l16 = "Послушайте, может вы мне подскажете. Я хочу купить " + pchar.GenQuest.Device.Shipyarder.Type + ", и мне сказали, что у вас в городе она продавалась. Ну, кто-то продавал на улицах. Ничего об этом сказать не можете?";
            link.l16.go = "Device_Citizen";
        }
        // <-- генератор Неудачливый вор

        // --> квестовый генератор мэра, поиск шпиёна на улице. eddy
        if (CheckAttribute(pchar, "GenQuest.SeekSpy.City") && pchar.location == (npchar.city + "_town"))
        {
            link.l4 = NPCharSexPhrase(npchar, LinkRandPhrase("Стойте! Немедленно скажите мне, кто вы такой?! Я ищу вражеского лазутчика по поручению губернатора " + XI_ConvertString("Colony" + characters[GetCharacterIndex(pchar.GenQuest.SeekSpy.MayorId)].city + "Gen") + "!", "Немедленно стой! Я действую в интересах города " + XI_ConvertString("Colony" + characters[GetCharacterIndex(pchar.GenQuest.SeekSpy.MayorId)].city + "Gen") + " по поручению губернатора. Ищу в городе вражеского агента.", "Стоять, приятель! Местный губернатор " + characters[GetCharacterIndex(pchar.GenQuest.SeekSpy.MayorId)].lastname + " очень хочет разыскать шпиона в городе."),
                                      LinkRandPhrase("Женщина, стойте! Немедленно скажите мне, кто вы такая?! Я ищу вражеского лазутчика по поручению губернатора " + XI_ConvertString("Colony" + characters[GetCharacterIndex(pchar.GenQuest.SeekSpy.MayorId)].city + "Gen") + "!",
                                                     "Женщина, я долж" + GetSexPhrase("ен", "на") + " вас задержать! Я действую в интересах города " + XI_ConvertString("Colony" + characters[GetCharacterIndex(pchar.GenQuest.SeekSpy.MayorId)].city + "Gen") + " по поручению губернатора. Ищу в городе вражеского агента.",
                                                     "Постой, красавица! Местный губернатор " + characters[GetCharacterIndex(pchar.GenQuest.SeekSpy.MayorId)].lastname + " очень хочет разыскать шпиона в городе..."));
            link.l4.go = "SitySpy";
        }
        // <-- квестовый генератор мэра, поиск шпиёна на улице
        // Квестовый генератор священника. Квест №2. Warship -->
        if (CheckAttribute(PChar, "GenQuest.ChurchQuest_2.AskPeople") && !CheckAttribute(NPChar, "GenQuest.ChurchQuest_2.AskedPeople") && NPChar.location == PChar.GenQuest.ChurchQuest_2.QuestTown + "_town")
        {
                link.l5 = LinkRandPhrase("Ты в курсе", "Тебе что-нибудь известно о том", "Ты знаешь что-нибудь о том") + ", что недавно была ограблена местная церковь?");
                link.l5.go = "Citiz_GenQuest_Church_2_1";
        }
        // <-- Квестовый генератор священника. Квест №2.

        Link.l6 = PCharRepPhrase(RandPhraseSimple("Тебе послышалось, я пойду.", "Нет, ничего - просто ш" + GetSexPhrase("ёл", "ла") + " в таверну."),
                                 RandPhraseSimple("Ладно, ничего. Удачи!", "Просто осматриваю город. До свидания."));
        Link.l6.go = "exit";
        break;

    case "new question":
        dialog.text = NPCharRepPhrase(npchar,
                                      PCharRepPhrase(LinkRandPhrase("О, да я рад" + NPCharSexPhrase(NPChar, " ", "а ") + " тебе, как выпивке, спрашивай, чего хочешь.", "Любишь поболтать, капитан? Что ж, я тоже... Особенно за кружечкой рома.", "Да, " + PChar.name + "?"),
                                                     LinkRandPhrase("Ну, чего тебе ещё?", "Вижу, капитан " + PChar.name + ", ты охотни" + GetSexPhrase("к", "ца") + " поболтать? ", "Замучил" + GetSexPhrase("", "а") + " вопросами, капитан, лучше бы угостил" + GetSexPhrase("", "а") + " ромом.")),
                                      PCharRepPhrase(LinkRandPhrase("Что вы хотели узнать " + GetAddress_Form(NPChar) + "?", "Я вас слушаю капитан.", "Мне нужно идти, поэтому спрашивайте скорее, капитан."),
                                                     LinkRandPhrase("Всегда рад" + NPCharSexPhrase(NPChar, " ", "а ") + " приятному собеседнику, " + GetAddress_Form(NPChar) + " " + PChar.lastname + ". Говорите.",
                                                                    "Да, " + GetAddress_Form(NPChar) + "?",
                                                                    "Любите поболтать, капитан? Что ж, я тоже...")));

        // homo 25/06/06
        link.l1 = LinkRandPhrase("Какие байки в ходу в здешней таверне?",
                                 "Что новенького в этих краях?",
                                 "Как течёт жизнь на суше?");
        link.l1.go = "rumours_citizen";
        link.l2 = LinkRandPhrase("Не объясните мне дорогу?", "Что-то я никак не найду дороги кое-куда...", "Подскажите дорогу...");
        link.l2.go = "town"; //(перессылка в файл города)
        if (Rand(1) == 0)
        {
            link.l3 = LinkRandPhrase("Хочу узнать, что тут говорят об одном человеке.", "Не знаете, что говорят тут об одной персоне?", "Хотелось бы узнать кое-что о местных жителях.");
            if (rand(1) == 0 || PChar.location == "LaVega_Town" || PChar.location == "PuertoPrincipe_town" || PChar.location == "Pirates_town" || PChar.location == "Panama_town" || !CheckAttribute(NPChar, "City"))
            {
                link.l3.go = "info"; //(перессылка в файл города)
            }
            else
            {
                link.l3.go = "RumourAboutOwners"; // Warship. Сделал по-другому - у жителя каждого города будет свой диалог.
            }
        }
        else
        {
            link.l3 = "Расскажите мне о вашей колонии.";
            link.l3.go = "colony";
        }
        link.l4 = RandPhraseSimple("Есть важное дело!", "У меня к вам дело.");
        link.l4.go = "quests"; //(перессылка в файл города)
        link.l5 = PCharRepPhrase(RandPhraseSimple("Тебе послышалось, я пойду.", "Нет, ничего - просто ш" + GetSexPhrase("ёл", "ла") + " в таверну."),
                                 RandPhraseSimple("Ладно, ничего. Удачи!", "Просто осматриваю город. До свидания."));
        link.l5.go = "exit";
        break;

    case "RumourAboutOwners":
        Dialog.Text = "О ком из жителей вы хотите узнать?";
        if (GetCharacterIndex(NPChar.city + "_Mayor") != -1)
        {
            link.l1 = "О губернаторе.";
            link.l1.go = "RumourAboutOwners_Mayor";
        }
        if (GetCharacterIndex(NPChar.city + "_TavernKeeper") != -1)
        {
            link.l2 = "О местном хозяине таверны.";
            link.l2.go = "RumourAboutOwners_TavernKeeper";
        }
        if (GetCharacterIndex(NPChar.city + "_ShipYarder") != -1)
        {
            link.l3 = "О хозяине верфи.";
            link.l3.go = "RumourAboutOwners_ShipYarder";
        }
        if (GetCharacterIndex(NPChar.city + "_Trader") != -1)
        {
            link.l4 = "О местном хозяине магазина.";
            link.l4.go = "RumourAboutOwners_Trader";
        }
        link.l9 = "Ни о ком. Забудь.";
        link.l9.go = "exit";
        break;

    case "RumourAboutOwners_TakeRumour":
        sTemp = sRumourAboutOwners_CityRumour(NPChar.City, NPChar.RumourOwnerType);
        Dialog.Text = sTemp;
        link.l1 = "Спасибо.";
        link.l1.go = "exit";
        // Здесь можно делать проверка по квестам, какой слух выпал
        DeleteAttribute(PChar, "QuestTemp.RumoursAboutOwners");
        break;

    case "colony":
        dialog.text = LinkRandPhrase("Честно говоря, я не слишком-то разбираюсь в этом. Но кое-что могу рассказать.",
                                     "Что же вас интересует в нашей колонии?", "Всегда пожалуйста. О чём вы хотите услышать?");
        switch (Rand(1))
        {
        case 0:
            link.l1 = "Что это за город?";
            link.l1.go = "colony_town";
            break;

        case 1:
            link.l1 = "Что вы знаете о форте, защищающем город?";
            link.l1.go = "fort";
            break;
        }
        link.l2 = "Поговорим о чём-нибудь другом.";
        link.l2.go = "new question";
        break;
        // to_do
    case "colony_town":
        dialog.text = "О, да вы издеваетесь? Или шутите? Посмотрите в правый угол экрана.";
        link.l1 = "Точно, туплю.";
        link.l1.go = "exit";
        break;

    case "fort":
        dialog.text = "Ничего про это не знаю.";
        link.l1 = "Жаль.";
        link.l1.go = "exit";
        break;

    //Jason --> генератор Неудачливый вор
    case "Device_Citizen":
        dialog.text = "Гм, " + pchar.GenQuest.Device.Shipyarder.Type + "? Впервые слышу... Хоть что это за вещь такая - сколько живу на свете, ничего подобного в глаза не видел" + NPCharSexPhrase(npchar, "", "а") + ".";
        link.l1 = "Ну, это судостроительный инструмент, " + pchar.GenQuest.Device.Shipyarder.Describe + ". Кто-нибудь такое продавал в городе, или, может, носил с собой и вы заметили?";
        link.l1.go = "Device_Citizen_1";
        npchar.quest.Device = "true";
        break;

    case "Device_Citizen_1":
        if (sti(pchar.GenQuest.Device.Shipyarder.Chance1) > 3 && sti(pchar.GenQuest.Device.Shipyarder.Chance1) < 6 && npchar.sex != "woman")
        {
            dialog.text = "Хм... Да, видел я человека с похожей вещью, ходил он по улицам несколько часов назад. Интересная штуковина.";
            link.l1 = "А как выглядел этот человек и куда пошёл? Мне очень нужен этот инструмент.";
            link.l1.go = "Device_Common";
        }
        else
        {
            dialog.text = "Нет, ничего такого не видел" + NPCharSexPhrase(npchar, "", "а") + ". Поспрашивайте ещё у кого.";
            link.l1 = "Ясно. Пойду спрашивать!";
            link.l1.go = "exit";
        }
        break;

    //============================ Генератор мэра. Квест по розыску шпиона на улице ============================
    case "SitySpy":
        dialog.text = NPCStringReactionRepeat(NPCharSexPhrase(npchar, "Ну, а я здесь при чём? Я местный житель!", "Ну, а я то здесь при чём? Я живу в этом городе, и знать ничего такого не желаю!"),
                                              NPCharSexPhrase(npchar, "Что опять вам от меня нужно? Говорил вам уже, что я не шпион!", "Я же говорила вам уже, что я местная!"),
                                              NPCharSexPhrase(npchar, "Ну, сколько можно? Отстаньте от меня, я местный житель!", "Ну что вы опять ко мне пристаёте со своими дурацкими расспросами?"),
                                              NPCharSexPhrase(npchar, "Что, опять?! Ну это ни в какие ворота не лезет!!!", "Послушайте, отстаньте от меня наконец, прошу вас!!"), "block", 0, npchar, Dialog.CurrentNode);
        link.l1 = HeroStringReactionRepeat("Кто может подтвердить твои слова?", "Ой, извините, я вас уже опрашивал" + GetSexPhrase("", "а") + "...",
                                           "Простите, столько народа...", "Хорошо, хорошо...", npchar, Dialog.CurrentNode);
        link.l1.go = DialogGoNodeRepeat("SitySpy_1", "exit", "exit", "exit", npchar, Dialog.CurrentNode);
        // ==> выбираем подтверждателя
        int num = FindNearCharacters(npchar, 20.0, -1.0, -1.0, 1.0, false, true);
        if (num > 0)
        {
            for (i = 0; i < num; i++)
            {
                iTemp = chrFindNearCharacters[i].index;
                if (CheckAttribute(&characters[iTemp], "CityType"))
                {
                    if (characters[iTemp].CityType == "soldier" || characters[iTemp].CityType == "citizen")
                    {
                        break;
                    }
                }
            }
            pchar.GenQuest.SeekSpy.Idx = chrFindNearCharacters[i].index;                           //индекс выбранного
            pchar.GenQuest.SeekSpy.Type = characters[sti(pchar.GenQuest.SeekSpy.Idx)].chr_ai.type; //тип кто помог
            pchar.GenQuest.SeekSpy.BaseIdx = npchar.index;                                         //индекс
        }
        break;
    case "SitySpy_1":
        if (sti(pchar.GenQuest.SeekSpy.Idx) == -1 || sti(pchar.GenQuest.SeekSpy.Idx) == 1) //на всякий случай
        {
            dialog.text = "Да кто угодно! Послушайте, что вы меня достаёте?! Если у вас какие-то проблемы, то пройдёмте к губернатору, и всё проясним!",
            link.l1 = "Гм... пожалуй, не будем его тревожить зря. Я вам верю...";
            link.l1.go = "exit";
            break;
        }
        dialog.text = "Кто угодно в этом городе! " + NPCharSexPhrase(npchar, GetFullName(&characters[sti(pchar.GenQuest.SeekSpy.Idx)]) + " может без проблем, благо " + NPCharSexPhrase(&characters[sti(pchar.GenQuest.SeekSpy.Idx)], "он", "она") + " в двух шагах.",
                                                                     "Ой, Господи, да вот, хотя бы " + NPCharSexPhrase(&characters[sti(pchar.GenQuest.SeekSpy.Idx)], GetAddress_FormToNPC(NPChar) + " " + characters[sti(pchar.GenQuest.SeekSpy.Idx)].lastname, GetFullName(&characters[sti(pchar.GenQuest.SeekSpy.Idx)])) + " может.");
        link.l1 = "Что ж, давайте послушаем...";
        link.l1.go = "SitySpy_2";
        sld = &characters[sti(pchar.GenQuest.SeekSpy.Idx)];
        sld.dialog.currentnode = "SeekSpy_Checking";
        pchar.GenQuest.SeekSpy.time = 4.0; //время на подбежать
        if (sld.chr_ai.type == "merchant")
            pchar.GenQuest.SeekSpy.time = 0.0; //мерчант базарит сразу
        LAi_SetActorTypeNoGroup(sld);
        break;
    case "SitySpy_2":
        sld = &characters[sti(pchar.GenQuest.SeekSpy.Idx)];
        LAi_SetActorTypeNoGroup(npchar);
        LAi_ActorTurnToCharacter(npchar, sld);
        LAi_ActorDialog(sld, pchar, "", stf(pchar.GenQuest.SeekSpy.time), 0);
        DialogExit();
        break;
    //=================== ноды квеста мэра. поиск шпиона на улице, опрос свидетеля ==================
    case "SeekSpy_Checking":
        dialog.text = "Да, я подтверждаю, " + NPCharSexPhrase(&characters[sti(pchar.GenQuest.SeekSpy.BaseIdx)], "он действительно местный житель.", "она действительно местная жительница.");
        link.l1 = RandPhraseSimple("Я понял" + GetSexPhrase("", "а") + ". Спасибо за помощь.", "Всё ясно. Спасибо за помощь.");
        link.l1.go = "SeekSpy_Checking_1";
        break;
    case "SeekSpy_Checking_1":
        switch (pchar.GenQuest.SeekSpy.Type)
        {
        case "guardian":
            LAi_SetGuardianTypeNoGroup(npchar);
            break;
        case "patrol":
            LAi_SetPatrolTypeNoGroup(npchar);
            break;
        case "citizen":
            LAi_SetCitizenTypeNoGroup(npchar);
            break;
        case "merchant":
            LAi_SetMerchantTypeNoGroup(npchar);
            break;
        }
        LAi_SetCitizenTypeNoGroup(&characters[sti(pchar.GenQuest.SeekSpy.BaseIdx)]);
        NextDiag.CurrentNode = "First Time";
        DialogExit();
        break;

    // Мини квест на поиск обручального кольца -->
    case "CitizenFindItem_1":
        dialog.text = "Дело в том, что я вчера прогуливалась за городом и потеряла своё обручальное кольцо... " + GetSexPhrase("Капитан, вы не могли бы поискать его?", "Девушка, пожалуйста, помогите мне его найти!") + "";
        link.l1 = "Конечно " + GetSexPhrase("могу! Ради такой прекрасной девушки я готов сделать всё, что угодно!", "помогу. Церковь учит помогать ближнему.") + "";
        link.l1.go = "CitizenFindItem_2";
        link.l2 = LinkRandPhrase("Нет, не могу. Извини. У меня очень много дел.", "Извини, не могу. Я вдруг вспомнил" + GetSexPhrase("", "а") + ", что у меня ещё осталось одно не завершённое дельце...", "У меня сейчас очень мало времени, так что помочь я ничем не смогу...");
        link.l2.go = "CitizenFindItem_NoQuest";
        break;

    case "CitizenFindItem_2":
        dialog.text = "" + GetSexPhrase("Капитан", "Девушка") + ", это же прекрасно! Пожалуйста, найдите это кольцо, ведь через " + sti(NPChar.LifeDay) + " дня приезжает мой муж и я не хотела бы, чтобы он меня увидел без обручального кольца.";
        link.l1 = RandPhraseSimple("Как вы сказали, где вы его потеряли?", "Так где вы его потеряли?");
        link.l1.go = "CitizenFindItem_3";
        break;

    case "CitizenFindItem_3":
        dialog.text = "Сразу за городскими воротами...";
        link.l1 = "Ну, тогда я пош" + GetSexPhrase("ёл", "ла") + " искать...";
        link.l1.go = "CitizenFindItem_4";
        break;

    case "CitizenFindItem_4":
        dialog.text = "Да, ступайте. И поторопитесь. Помните, у вас есть всего " + sti(NPChar.LifeDay) + " дня.";
        link.l1 = "Помню.";
        link.l1.go = "exit";
        PChar.GenQuest.CitizenFindItem.StartQuest = true;
        PChar.GenQuest.CitizenFindItem.City = NPChar.City;
        PChar.GenQuest.CitizenFindItem.CitizenID = NPChar.ID;

        sCity = NPChar.City + "_ExitTown";

        //sTemp = "randitem" + (rand(1)+1); // Т.е. может получиться, что его вовсе найти не удастся. И это гуд.
        sTemp = "randitem1";
        Log_TestInfo("Кольцо будет в локаторе - " + sTemp);
        PChar.GenQuest.CitizenFindItem.ItemLocator = sTemp;
        ChangeItemDescribe("DOjeronRing", "itmdescr_WeddingRing");
        items[FindItem("DOjeronRing")].Name = "itmname_WeddingRing";
        items[FindItem("DOjeronRing")].City = XI_ConvertString("Colony" + NPChar.City + "Gen");
        SetFunctionTimerCondition("CitizenFindItemMiniQuest_Timer", 0, 0, sti(NPChar.LifeDay), false);
        PChar.GenQuestRandItem.(sCity).(sTemp) = "DOjeronRing";
        SetGameModeCondition("CitizenFindItemMiniQuest_CheckItem");
        break;

    case "CitizenFindItem_NoQuest":
        DialogExit();
        NextDiag.CurrentNode = "First time";
        NPChar.CitizenFindItem.NoQuest = true; // Эта девушка квест больше не даст
        break;

    case "CitizenFindItem_Complete_1":
        dialog.text = "" + GetSexPhrase("Капитан", "Девушка") + "! Я так рада! Как я могу вас отблагодарить?";
        link.l1 = "Не надо благодарностей, я делал" + GetSexPhrase("", "а") + " это совершенно бескорыстно.";
        link.l1.go = "CitizenFindItem_Complete_2";
        link.l2 = "Мне не помешала бы сотня-другая песо...";
        link.l2.go = "CitizenFindItem_Complete_3";
        RemoveItems(PChar, "DOjeronRing", 1);
        DeleteAttribute(PChar, "GenQuest.CitizenFindItem");
        NPChar.CitizenFindItem.NoQuest = true;
        PChar.Quest.CitizenFindItemMiniQuest_Timer.over = "yes";
        BackItemDescribe("DOjeronRing");
        items[FindItem("DOjeronRing")].Name = "itmname_DOjeronRing";
        DeleteAttribute(&items[FindItem("DOjeronRing")], "City");
        break;

    case "CitizenFindItem_Complete_2":
        dialog.text = "Ах, " + GetSexPhrase("капитан, какой вы прекрасный человек", "девушка, вы такая благородная") + "! Я обязательно помолюсь за вас в церкви! До свидания...";
        link.l1 = "Прощайте, " + NPChar.name + ".";
        link.l1.go = "exit";
        ChangeCharacterComplexReputation(PChar, "nobility", 1);
        AddCharacterExpToSkill(PChar, "Leadership", 10);
        AddCharacterExpToSkill(PChar, "Fortune", 10);
        break;

    case "CitizenFindItem_Complete_3":
        iTemp = (rand(3) + 1) * 50;
        dialog.text = "Ах да, конечно. Вот вам " + FindRussianMoneyString(iTemp) + ". Это всё, что у меня есть. Возьмите их... И прощайте.";
        link.l1 = "До свидания, " + GetFullName(NPChar) + ".";
        link.l1.go = "exit";
        AddMoneyToCharacter(PChar, iTemp);
        break;
    // <-- Мини квест на поиск обручального кольца

    //=================== ноды квеста священника. поиск грабителей (квест №2)==================
    case "Citiz_GenQuest_Church_2_1":
        if (rand(3) != 1)
        {
            dialog.text = LinkRandPhrase("Нет, я ничего об этом не знаю.", "Мне ничего не известно по этому вопросу.", "Я ничего не знаю.");
            link.l1 = LinkRandPhrase("Ладно, хорошо.", "Ясно, спасибо.", "Хорошо, извини.");
            link.l1.go = "exit";
        }
        else
        {
            dialog.text = LinkRandPhrase("Я ничего об этом не знаю, но вы можете расспросить завсегдатаев в таверне - они уж точно что-нибудь вам расскажут.", "Я вам ничего сказать не могу, спросите лучше кого-нибудь в таверне.", "Мне ничего конкретного не известно, но я слышал, что об этом трепались в таверне.");
            link.l1 = "Спасибо и на том.";
            link.l1.go = "exit";
        }

        NPChar.GenQuest.ChurchQuest_2.AskedPeople = true;
        break;

    //замечение по обнаженному оружию
    case "CitizenNotBlade":
        if (loadedLocation.type == "town")
        {
            dialog.text = NPCharSexPhrase(NPChar, "Послушайте, я, как гражданин этого города, прошу вас не ходить у нас с обнажённым клинком.", "Знаете, я, как гражданка этого города, прошу вас не ходить у нас с обнажённым клинком.");
            link.l1 = LinkRandPhrase("Хорошо.", "Ладно.", "Как скажете...");
        }
        else
        {
            dialog.text = NPCharSexPhrase(NPChar, "Острожней на поворотах, " + GetSexPhrase("приятель", "подруга") + ", когда бежишь с оружием в руках. Я ведь могу и занервничать...", "Мне не нравится, когда " + GetSexPhrase("мужчины", "всякие тут") + " ходят передо мной с оружием на изготовку. Это меня пугает...");
            link.l1 = RandPhraseSimple("Понял" + GetSexPhrase("", "а") + ".", "Убираю.");
        }
        link.l1.go = "exit";
        NextDiag.TempNode = "First Time";
        break;
    }
}
