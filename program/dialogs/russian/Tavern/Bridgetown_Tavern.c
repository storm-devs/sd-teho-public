// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Какие вопросы?", "Что вам угодно, " + GetAddress_Form(NPChar) + "?"), "Совсем недавно вы пытались задать мне вопрос, " + GetAddress_Form(NPChar) + "...", "В течение этого дня вы уже третий раз говорите о каком-то вопросе...",
                          "Опять вопросы будем задавать?", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Я "+ GetSexPhrase("передумал","передумала") +"...", "Сейчас мне не о чем говорить"), "Хм, что-то с памятью моей стало...",
                      "Да уж, действительно в третий раз...", "Да нет, какие вопросы...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			//Голландский гамбит /за Англию/
			if (CheckAttribute(pchar, "questTemp.HWIC.Eng") && pchar.questTemp.HWIC.Eng == "GotoBridgetown" && !CheckAttribute(npchar, "quest.HWICTalked"))
            {
                link.l1 = "Я хочу выпить. Налей мне самого лучшего рома, который у тебя есть.";
                link.l1.go = "TavernDone";
            }
			if (CheckAttribute(pchar, "questTemp.HWIC.Eng") && pchar.questTemp.HWIC.Eng == "toBarbados")
            {
                link.l1 = "Послушай, а где Плешивый Гастон?";
                link.l1.go = "Tonzag_Letter";
            }
			//Голландский гамбит /против всех/
			if (!CheckAttribute(npchar, "quest.HWICTake") && CheckAttribute(pchar, "questTemp.HWIC.CanTake") && !CheckAttribute(pchar, "questTemp.HWIC.CanTake.Self") && !CheckAttribute(pchar, "questTemp.HWIC.Eng") && !CheckAttribute(pchar, "questTemp.HWIC.Holl"))
			{
                link.l1 = "Нет ли у тебя какой-нибудь работы? Или, может, что-нибудь посоветуешь?";
                link.l1.go = "Tonzag_check";
            }
			if (CheckAttribute(pchar, "questTemp.HWIC.Self") && pchar.questTemp.HWIC.Self == "FernandoDie")
			{
                link.l1 = "Я выполнил работу. Фернандо Родригес мертв.";
                link.l1.go = "Task_check";
            }
			// Страж Истины
			if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "merdok" && !CheckAttribute(npchar, "quest.jino"))
			{
				link.l1 = "Послушай, не появлялся ли у вас в городе ученый-алхимик, лекарь? Он итальянец, лет тридцати, зовут Джино Гвинейли. Не слыхал о таком?";
				link.l1.go = "guardoftruth";
			}
		break;
		
		//Голландский гамбит /за Англию/
		case "TavernDone":
			dialog.text = "Выпивка - да пожалуйста, самый лучший ром для дорогого гостя! У вас праздник какой, или просто горло промочить зашли?";
			link.l1 = "Можно сказать, и праздник. Я везу рабов в Блювельд - недавно переделал свой новый бриг специально под эти цели - а тут зашел на плантацию, поболтал с управляющим - он заказал мне приличную партию 'черного дерева'. Так что скоро жди меня опять в гости. Отвезу товар в Блювельд - буду возить на Барбадос, хе-хе...";
			link.l1.go = "TavernDone_1";
		break;
		
		case "TavernDone_1":
			dialog.text = "Вот как? Ну, за хорошую сделку не грех и выпить! Говорите, будете 'товар' на Барбадос возить, ха-ха?! Здорово...";
			link.l1 = "Ладно... Пойду поищу место, где присесть.";
			link.l1.go = "exit";	
			npchar.quest.HWICTalked = "true";
			pchar.questTemp.HWIC.Eng.BridgeCounter = sti(pchar.questTemp.HWIC.Eng.BridgeCounter)+1;
			AddQuestRecord("Holl_Gambit", "2-12");
			if (sti(pchar.questTemp.HWIC.Eng.BridgeCounter) == 7) 
			{
				AddQuestRecord("Holl_Gambit", "2-6");
				pchar.questTemp.HWIC.Eng = "SeekVanBerg";
				pchar.quest.GotoBridgetownOver.over = "yes";//снять таймер
				pchar.quest.VanBergAttack_Check.win_condition.l1 = "MapEnter";
				pchar.quest.VanBergAttack_Check.function = "VanBergAttackCheck";
			}
		break;
		
		case "Tonzag_Letter":
			dialog.text = "Гастон исчез из города через пару дней после того, как вы устроили тут цирк, разыгрывая из себя торговца не-пойми-чем. Ваш обман быстро распознали, поскольку городок маленький и слухи расходятся быстро. Вот тут-то Гастон и засобирался куда-то. Больше его никто не видел. А вам, сударь, он оставил письмо. Просил передать лично, если вы появитесь на Барбадосе раньше него\nКстати, Гастона уже искали: какой-то узкоглазый здоровяк и пожилой, то ли испанец, то ли португалец. Все они на одно лицо. Но лицо этого старика я долго не смогу забыть. Было в нем что-то такое... словами не скажешь.";
			link.l1 = "Давай сюда письмо... Спасибо!";
			link.l1.go = "Tonzag_Letter_1";
		break;
		
		case "Tonzag_Letter_1":
			DialogExit();
			AddQuestRecord("Holl_Gambit", "2-22");
			AddQuestRecordInfo("LetterFromGaston", "1");
			pchar.questTemp.HWIC.Eng = "toCuracao";
			LocatorReloadEnterDisable("SentJons_town", "houseSP3", true);//закрыть дом Флитвуда
			LocatorReloadEnterDisable("SentJons_town", "HouseF3", true);//закрыть аптеку
			LocatorReloadEnterDisable("SentJons_town", "basement1_back", true);//закрыть подземелье
			pchar.quest.Knippel_Shore.win_condition.l1 = "location";
			pchar.quest.Knippel_Shore.win_condition.l1.location = "Shore24";
			pchar.quest.Knippel_Shore.function = "KnippelOnCuracao";
		break;
		
		//Голландский гамбит /против всех/
		case "Tonzag_check"://начинаем проверять нашего ГГ по всем статьям
			if(sti(pchar.reputation.nobility) > 41)//высокая репа
			{
				PlaySound("VOICE\Russian\hambit\Ercule Tongzag-03.wav");
				dialog.text = "Я не нуждаюсь в услугах белоручек. Я ничего не могу вам посоветовать.";
				link.l1 = "Эй-эй, полегче, приятель, с выражениями!";
				link.l1.go = "exit";
				break;
			}
			if(GetSummonSkillFromName(pchar, SKILL_F_LIGHT) < 25 || GetSummonSkillFromName(pchar, SKILL_FENCING) < 25 || GetSummonSkillFromName(pchar, SKILL_F_HEAVY) < 25 || GetSummonSkillFromName(pchar, SKILL_PISTOL) < 25)//слабое фехтование
			{
				dialog.text = "Капитан, для работы мне нужен боец посноровистее, чем вы. Приходите, когда научитесь лучше махать железкой, что у вас на поясе болтается. Да и меткости тоже подучиться не мешает.";
				link.l1 = "Понятно. Тогда я навещу вас позже.";
				link.l1.go = "exit";
				break;
			}
			if(sti(Pchar.rank) > 15)//высокий ранг
			{
				dialog.text = "Вы слишком известны на Архипелаге, кэп. Не думаю, что вам будут интересны мои задания.";
				link.l1 = "Ладно, раз неинтересны - значит, неинтересны. Прощайте.";
				link.l1.go = "exit";
				break;
			}
			PlaySound("VOICE\Russian\hambit\Ercule Tongzag-02.wav");
			dialog.text = "Хм... Вообще-то вы вовремя, у меня как раз есть одно дело, которое требует незамедлительного выполнения. Если хорошо себя покажете - познакомлю вас с очень влиятельными людьми. Теперь слушайте, что от вас требуется.";
			link.l1 = "Я весь внимание.";
			link.l1.go = "Tonzag_task";
		break;
		
		case "Tonzag_task":
			pchar.questTemp.HWIC.Self.SpainCity = FindSpainCity();
			log_Testinfo(pchar.questTemp.HWIC.Self.SpainCity);
			dialog.text = "На Карибы прибыл из Кастилии один идальго, в расчете переждать последствия одной... дуэли в Европе. Однако жажда мести границ не имеет - влиятельная испанская семья желает, чтобы этот идальго умер. Выполните их волю любым способом\nВ качестве доказательства вы должны отрезать его палец с фамильным перстнем и доставить мне. Кроме того, принесите мне все, что найдете при нем, все вещи. Вы готовы взяться за эту работу?";
			link.l1 = "Если оплата будет достойной, то конечно возьмусь.";
			link.l1.go = "Tonzag_task_1";
			link.l2 = "Работать наемным убийцей? Да ни за что!";
			link.l2.go = "Tonzag_exit";
			npchar.quest.HWICTake = "true";
			pchar.questTemp.HWIC.CanTake.Self = "true";//признак, что против всех уже бралась
		break;
		
		case "Tonzag_exit":
			dialog.text = "Тогда проваливайте, и забудьте о нашем разговоре.";
			link.l1 = "Счастливо оставаться.";
			link.l1.go = "exit";	
			DeleteAttribute(pchar, "questTemp.HWIC.Self");//откат к двум другим вариантам
			pchar.questTemp.HWIC.Fail3 = "true";
		break;
		
		case "Tonzag_task_1":
			dialog.text = "Награда определена в размере 30 000 песо - в накладе вы не останетесь. Кроме того, можете забрать себе с трупа все деньги, какие найдете. Теперь подробности: вашего клиента зовут дон Фернандо Родригес. Его приметы: на вид 35 лет, высокий, смуглый, одевается как военный. Хороший моряк и опытный фехтовальщик\nГде его найти - сказать точно не могу, но достоверно известно, что он сейчас в одном из испанских поселений архипелага и не собирается никуда выдвигаться еще два месяца. Обойдите все испанские города, расспросите людей - кто-нибудь обязательно его видел\nИ еще: я достоверно знаю, с какими вещами он никогда не расстается, так что не вздумайте что-либо от меня утаить. Вопросы есть?";
			link.l1 = "Вопросов нет. Отправляюсь в путь!";
			link.l1.go = "Tonzag_task_2";	
		break;
		
		case "Tonzag_task_2":
			DialogExit();
			pchar.questTemp.HWIC.Self = "start";
			SetFunctionTimerCondition("TargetFernandoOver", 0, 0, 60, false); //таймер
			AddQuestRecord("Holl_Gambit", "3-1");
			ReOpenQuestHeader("Holl_Gambit"); // данила . чтобы вышел из архива																				  
			Log_TestInfo(""+XI_ConvertString("Colony"+pchar.questTemp.HWIC.Self.SpainCity)+"");
		break;
		
		case "Task_check":
			dialog.text = "Палец с перстнем у тебя? Покажи.";
			if (CheckCharacterItem(pchar, "Finger"))
			{
				link.l1 = "Да, конечно. Вот он.";
				link.l1.go = "Task_check_1";	
			}
			else
			{
				link.l1 = "Нет. Фернандо утонул вместе со своим кораблем, и палец утонул вместе с Фернандо.";
				link.l1.go = "Task_fail";	
			}
		break;
		
		case "Task_fail":
			dialog.text = "Палец с кольцом был обязательным условием контракта. Это подтверждение гибели клиента. Кто знает, не выплыл ли Родригес на берег со своего затонувшего корабля? Ты проверил? Нет. В общем, с задачей ты не справился, так что на этом наше сотрудничество окончено. Всего доброго.";
			link.l1 = "Но я же его уничтожил! А, пес с тобой... На архипелаге и других занятий хватает. Бывай.";
			link.l1.go = "exit";
			pchar.questTemp.HWIC.Fail3 = "true";
			AddQuestRecord("Holl_Gambit", "3-8");
			CloseQuestHeader("Holl_Gambit");
			DeleteAttribute(pchar, "questTemp.HWIC.Self");//зачищаем для возможности отката к голландскому варианту
		break;
		
		case "Task_check_1":
			RemoveItems(PChar, "Finger", 1);
			dialog.text = "Великолепно! Палец я оставляю себе. Теперь по содержимому его карманов. Давай посмотрим, что ты привез.";
			link.l1 = "Пожалуйста, смотри...";
			link.l1.go = "Task_check_2";	
		break;
		
		case "Task_check_2":
			if (CheckCharacterItem(pchar, "jewelry7") && CheckCharacterItem(pchar, "totem_05") && CheckCharacterItem(pchar, "amulet_1"))
			{
				dialog.text = "Ага, всё, что мне нужно. Молодец! Ты отлично выполнил работу. Я доволен тобой.";
				link.l1 = "Спасибо! Слышать похвалу всегда приятно.";
				link.l1.go = "Task_complete";	
			}
			else
			{
				dialog.text = "Хм... Я же тебя предупреждал - я знаю, с чем Родригес никогда не расстается. И я не вижу здесь того, что мне надо. Ты прикарманил эти вещи? Или потерял? Неважно. Я более не желаю иметь с тобой дело. Проваливай.";
				link.l1 = "Ну и пес с тобой...";
				link.l1.go = "exit";
				pchar.questTemp.HWIC.Fail3 = "true";
				AddQuestRecord("Holl_Gambit", "3-9");
				CloseQuestHeader("Holl_Gambit");
				DeleteAttribute(pchar, "questTemp.HWIC.Self");//зачищаем для возможности отката к голландскому варианту
			}
		break;
		
		case "Task_complete":
			RemoveItems(PChar, "jewelry7", 1);
			RemoveItems(PChar, "totem_05", 1);
			RemoveItems(PChar, "amulet_1", 1);
			AddMoneyToCharacter(pchar, 30000);
			dialog.text = "Вот твое вознаграждение, как и было обещано - тридцать тысяч. И у меня сразу есть для тебя очередное, очень ответственное задание, связанное со значительным риском, но и оплата будет соответствующей - 40 000 песо.";
			link.l1 = "Слушаю внимательно. Кто очередной клиент?";
			link.l1.go = "Fleetwood_house";	
		break;
		
		//2 задание
		case "Fleetwood_house":
			PlaySound("VOICE\Russian\hambit\Ercule Tongzag-05.wav");
			dialog.text = "В этот раз охотиться нужно не за человеком, а за вещью. Тебе нужно проникнуть в дом английского капитана, Ричарда Флитвуда, проживающего на Антигуа, и выкрасть его судовой журнал. Дом этот охраняется изнутри, да и сам Ричард со своим журналом нечасто в нем бывает\nПлан таков: ровно через 10 дней губернатор Сент-Джонса дает у себя во дворце званый ужин, куда будет приглашен и капитан Флитвуд. Тебе нужно проникнуть в дом ночью, между часом и тремя часами - тогда не будет опасности твоего обнаружения. Внутри будет всего один солдат - когда Ричарда нет дома, то и охраны немного. Охранника ликвидируешь. Журнал следует искать в апартаментах Ричарда на втором этаже\nВозьми этот ключ - с помощью него ты откроешь запертую дверь дома.";
			link.l1 = "Хм... Интересно. Задачу понял, готов отправиться в путь!";
			link.l1.go = "Fleetwood_house_1";	
		break;
		
		case "Fleetwood_house_1":
			GiveItem2Character(pchar, "key3");
			dialog.text = "Будь осторожен. Не суйся в дом раньше указанной мной даты, иначе тебя в лучшем случае просто оттуда выпроводят, а в худшем - окажешься за решеткой. Повтори дату и время.";
			link.l1 = "Ровно через десять дней, с часу до трех ночи.";
			link.l1.go = "Fleetwood_house_2";	
		break;
		
		case "Fleetwood_house_2":
			dialog.text = "Хорошо. Теперь отправляйся. Удачи!";
			link.l1 = "Спасибо, Гастон.";
			link.l1.go = "Fleetwood_house_3";
		break;
		
		case "Fleetwood_house_3":
			DialogExit();
			AddQuestRecord("Holl_Gambit", "3-10");
			pchar.questTemp.HWIC.Self = "theft";
			DeleteAttribute(pchar, "questTemp.HWIC.CanTake");//иные варианты более невозможны
			LocatorReloadEnterDisable("SentJons_houseSP3", "reload2", true);//комнату закроем
			pchar.GenQuestBox.SentJons_houseSP3_room = true;
			pchar.GenQuestBox.SentJons_houseSP3_room.box1.items.FleetwoodJournal = 1;//положим в комод СЖ
			pchar.GenQuestBox.SentJons_houseSP3_room.box1.items.sand_clock = 1;//и песочные часы
			AddDialogExitQuestFunction("CreateFleetwoodSoldiers");//4 солдат в доме
			SetFunctionTimerCondition("FleetwoodJournalOver", 0, 0, 11, false);//таймер
			pchar.quest.Fleetwood_Journal.win_condition.l1 = "Timer";
			pchar.quest.Fleetwood_Journal.win_condition.l1.date.hour  = sti(GetTime());
			pchar.quest.Fleetwood_Journal.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 9);
			pchar.quest.Fleetwood_Journal.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 9);
			pchar.quest.Fleetwood_Journal.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 9);
			pchar.quest.Fleetwood_Journal.win_condition.l2 = "Hour";
			pchar.quest.Fleetwood_Journal.win_condition.l2.start.hour = 0;
			pchar.quest.Fleetwood_Journal.win_condition.l2.finish.hour = 3;
			pchar.quest.Fleetwood_Journal.win_condition.l3 = "locator";
			pchar.quest.Fleetwood_Journal.win_condition.l3.location = "SentJons_town";
			pchar.quest.Fleetwood_Journal.win_condition.l3.locator_group = "reload";
			pchar.quest.Fleetwood_Journal.win_condition.l3.locator = "houseSP3";//доступно открывание двери
			pchar.quest.Fleetwood_Journal.function = "FleetwoodHouseEnter";
			pchar.quest.Fleetwood_Soldier.win_condition.l1 = "location";
			pchar.quest.Fleetwood_Soldier.win_condition.l1.location = "SentJons_houseSP3";
			pchar.quest.Fleetwood_Soldier.function = "Fleetwood_Soldier";//если надумает раньше заявиться
		break;
		
		case "guardoftruth":
			dialog.text = LinkRandPhrase("Нет, не слыхал. Есть у нас травники, и лекари - но ни одного с таким именем.","Впервые такое чудное имя слышу. Нет, таких у нас отродясь не водилось.","Да у нас и вовсе никаких алхимиков нет. Лекари есть, но ни одного с таким чудным именем.");
			link.l1 = "Ясно. Жаль. Буду искать дальше!";
			link.l1.go = "exit";
			npchar.quest.jino = "true";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

string FindSpainCity()//Jason выбрать радномный испанский город - пусть побегает
{
	int n, nation;
    int storeArray[MAX_COLONIES];
    int howStore = 0;

	for(n=0; n<MAX_COLONIES; n++)
	{
		if (colonies[n].nation == SPAIN && colonies[n].id != "Panama" && colonies[n].id != "Minentown" && colonies[n].id != "SanAndres" && colonies[n].nation != "none")
		{
			storeArray[howStore] = n;
			howStore++;
		}
	}
	if (howStore == 0) return "none";
	nation = storeArray[dRand(howStore-1)];
	return colonies[nation].id;
}