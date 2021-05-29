// Хенрик Ведекер. Он же Механик.
#include "DIALOGS\russian\Rumours\Common_rumours.c"
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int iTemp;
	string sTemp;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	ProcessCommonDialogRumors(NPChar, Link, NextDiag);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "Добрый день, сударь. Я вас раньше не видел. Недавно на острове, или только впервые решились ко мне зайти?";
				link.l1 = TimeGreeting()+". Меня зовут "+GetFullName(pchar)+". Я действительно недавно тут, вот, хожу, знакомлюсь с людьми...";
				link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				if (pchar.questTemp.LSC == "platinum_wait")
				{
					dialog.text = "Послушайте, "+pchar.name+", если вы будете отвлекать меня, я никогда не закончу ремонт костюма.";
					link.l1 = "Да-да, я помню. Извините за беспокойство!";
					link.l1.go = "exit";
					break;
				}
				// возвращение блудного скафандра
				if (pchar.questTemp.LSC == "return" && !CheckAttribute(npchar, "quest.return_isl"))
				{
					dialog.text = "Ах! Вот это дела! Утопленник вернулся с того света! Ну-ка, рассказывайте, как вам удалось провернуть такой трюк? Ведь вас уже отпели и заочно похоронили, если вы не в курсе...";
					link.l1 = "И напрасно - я еще на тот свет не собираюсь. А трюк этот очень прост - я прикоснулся к статуе Кукулькана, которую нашел на дне, и телепортировался на Доминику, прямо в деревню карибов...";
					link.l1.go = "return";
					break;
				}
				
				dialog.text = "А, "+GetFullName(pchar)+"! "+TimeGreeting()+"!";
				// квестовые ветки
				if(pchar.questTemp.LSC == "mechanic")
				{
					link.l4 = "Хенрик, я пришел к вам по делу. Очень важному делу. Мне тут кое-что рассказал о вас Оле Кристиансен, или как его еще называют, Белый Мальчик.";
					link.l4.go = "mechanic_1";
				}
				if(pchar.questTemp.LSC == "platinum" && GetCharacterItem(pchar, "jewelry10") >= 11)
				{
					link.l4 = "Хенрик, я принес достаточное количество 'серебришка'. Столько, сколько вы просили: один ваш и еще десять. Вот, держите.";
					link.l4.go = "mechanic_15";
				}
				if(pchar.questTemp.LSC == "underwater_check")
				{
					link.l4 = "Это опять я, Хенрик. Как там ваш костюм? Удалось починить?";
					link.l4.go = "mechanic_20";
				}
				if(pchar.questTemp.LSC == "platinum_add_wait" && GetCharacterItem(pchar, "jewelry10") >= sti(pchar.questTemp.LSC.PtAddQty))
				{
					link.l4 = "У меня есть металл в том количестве, которое вы просили. Возьмите.";
					link.l4.go = "mechanic_23";
				}
				if(pchar.questTemp.LSC == "underwater_prepare")
				{
					link.l4 = "Здравствуйте, Хенрик. Ну как, костюм готов для погружения?";
					link.l4.go = "immersion";
				}
				if(pchar.questTemp.LSC == "underwater_natan" && CheckAttribute(pchar, "questTemp.LSC.NatanTalk"))
				{
					link.l4 = "Всё, я решил свои проблемы и готов к погружению. Когда мы начинаем?";
					link.l4.go = "immersion_1";
				}
				if(CheckAttribute(pchar, "questTemp.LSC.UW_ready"))
				{
					link.l5 = "Здравствуйте, Хенрик. Ну как, костюм готов для погружения?";
					link.l5.go = "immersion_next";
				}
				if(CheckAttribute(pchar, "questTemp.LSC.UW_end") && CheckCharacterItem(pchar, "underwater"))
				{
					link.l5 = "Я хочу вернуть вам костюм.";
					link.l5.go = "immersion_next_2";
				}
				// квестовые ветки				
				link.l1 = LinkRandPhrase("Что-нибудь интересное мне расскажете?", "Что нового произошло на острове в последнее время?", "Не расскажете ли последние сплетни?");
				link.l1.go = "rumours_LSC";
				link.l3 = "Да просто решил узнать, как у вас дела.";
				link.l3.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting": // первая встреча
			dialog.text = "Ну а я - Хенрик Ведекер. Правда, большинство жителей острова знают меня как Механика, что, впрочем, полностью соответствует истине.";
			if(pchar.questTemp.LSC == "mechanic")
			{
				link.l1 = "Вы - Хенрик Ведекер? Очень рад! Потому что именно вас я и ищу.";
				link.l1.go = "mechanic";
			}
			else
			{
				link.l1 = "Вы, вероятно, мастер на все руки?";
				link.l1.go = "meeting_1";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting_1":
			dialog.text = "О, да, и клан нарвалов весьма и весьма ценит мои умения. Мои изобретения позволяют им добывать из трюмов погибших кораблей внешнего кольца всевозможные ценности, которые они потом обменивают у адмирала Додсона на продовольствие\nА вообще, моя страсть - исследования и научная деятельность. Так что извините, если не смогу уделять вам достаточно времени - эксперименты отнимают его у меня практически полностью.";
			link.l1 = "Понятно. Я не буду вам докучать без дела, мистер Ведекер, уверяю вас. Очень рад знакомству!";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
		case "mechanic":
			dialog.text = "Ищете меня? А зачем, позвольте спросить?";
			link.l1 = "Мне рассказал про вас Оле Кристиансен, или, как его еще называют, Белый Мальчик.";
			link.l1.go = "mechanic_1";
		break;
		
		case "mechanic_1":
			dialog.text = "А, этот забавный паренек! Да-да, знаю его. Что же он такое вам про меня рассказал?";
			link.l1 = "Заранее хочу извиниться, если это прозвучит глупо но... все же спрошу. Оле сказал мне, что вы сможете научить, как спуститься на дно, под воду. Только не смейтесь пожалуйста, если это просто его выдумка.";
			link.l1.go = "mechanic_2";
		break;
		
		case "mechanic_2":
			dialog.text = "Выдумка? Это отнюдь не выдумка. Я сам бывал на дне, и не раз. Правда, уже давно не спускаюсь, ибо за последние годы гигантских крабов на нашем мелководье развелось просто тьма тьмущая, а я, понимаете ли, ученый, а не боец, и сражаться с этими монстрами мне не по силам\nКроме меня, на дно также спускались еще два человека, из нарвалов, но в итоге тоже отказались - добывать всякую всячину безопаснее из трюмов кораблей, прибиваемых течением к внешнему кольцу, нежели со дна, кишащего жуткими тварями\nТеперь моим водолазным снаряжением пользуются редко, а за последние пару месяцев на дно вообще никто не отправлялся, так как костюм вышел из строя...";
			link.l1 = "У вас есть костюм, в котором можно спускаться на дно? Я не ослышался?";
			link.l1.go = "mechanic_3";
		break;
		
		case "mechanic_3":
			dialog.text = "Со слухом у вас все в порядке, молодой человек. Я сам изобрел и сделал этот костюм из толстой парусины, многократно пропитанной специальными смолами, в результате чего она стала абсолютно водонепроницаема, и металлических составляющих частей, а также специального стального шлема, который мы изготовили совместно с Юргеном в его кузне\nЯ усилил костюм металлическим нагрудником и наплечником, наколенниками и налокотниками на случай столкновения с крабами, а также для придания массы для устойчивости при хождении по дну. Кроме того, в состав костюма входят тяжелые стальные ботинки - опять же для успешного передвижения по дну\nДля поддержания жизни водолаза имеются специальные емкости, наполненные сжатым воздухом, позволяющие некоторое время находится под водой. Вещь уникальная, моя гордость.";
			link.l1 = "Это замечательно. Но вы сказали, что ваш костюм недавно вышел из строя?";
			link.l1.go = "mechanic_4";
		break;
		
		case "mechanic_4":
			dialog.text = "К величайшему сожалению, это действительно так. Отдельные части костюма для придания прочности и гибкости сочленений соединялись при помощи специальных металлических пластин. Однако морская вода оказала на сталь губительное воздействие - за год погружений они подверглись разрушению ржавчиной, и костюм утратил свою герметичность\nХорошо, что я вовремя это заметил и никто не пострадал. Вода оставалась на гибких сочленениях, даже при высушенном костюме, и морская соль с влагой сделали свое черное дело.";
			link.l1 = "Да уж... Но вы же можете починить костюм! Поставить новые детали вместо проржавевших...";
			link.l1.go = "mechanic_5";
		break;
		
		case "mechanic_5":
			dialog.text = "Для чего? Чтобы через год они опять разрушились? Вы знаете, какая это сложная работа - собрать костюм на гибких сочленениях, да так, чтобы он получился герметичным? Да мне неделю без отдыха этим заниматься придется.";
			link.l1 = "Так что, вы из-за этого готовы выбросить свое великолепное творение на свалку?";
			link.l1.go = "mechanic_6";
		break;
		
		case "mechanic_6":
			dialog.text = "Нет, конечно. Я уже придумал, что надо сделать. Нужно изготовить сочленяющие пластины из металла, который не разрушается под воздействием воды и соли. И такой металл есть...";
			link.l1 = "Так в чем же проблема?";
			link.l1.go = "mechanic_7";
		break;
		
		case "mechanic_7":
			dialog.text = "Проблема в том, что этот металл очень редок. У меня есть всего один кусок, чего, безусловно, недостаточно. Нужно еще как минимум десять, а то и пятнадцать таких кусков для выполнения работы.";
			link.l1 = "А что это за металл такой?";
			link.l1.go = "mechanic_8";
		break;
		
		case "mechanic_8":
			dialog.text = "О-о, это уникальный металл, который недооценивается людьми. При высокой прочности и достаточной пластичности он абсолютно устойчив ко всем внешним воздействиям - ни вода, ни соль, ни какие-либо другие вещества не могут его разрушить\nВозможно, вы встречали этот металл. Он белый, и похож на серебро, поэтому испанцы прозвали его 'серебришком'. Кхе! Да он в сотни раз ценнее серебра по своим качествам! Да что серебра - золота! Когда-нибудь люди поймут это, но, видно, время еще не пришло.";
			link.l1 = "Послушайте, а нельзя ли заменить этот металл каким-то другим, раз он так редок? Что если использовать для изготовления пластин золото? Я не слышал такого, чтобы золото ржавело или разрушалось.";
			link.l1.go = "mechanic_9";
		break;
		
		case "mechanic_9":
			dialog.text = "У вас гибкий и живой ум, молодой человек. Это не может не радовать. Но к сожалению, ваше предложение не годится. То, что вы сейчас сказали, было первое, что пришло мне в голову. Но золото слишком мягкий металл, чтобы выполнять данную функцию - соединять части костюма\nУвы, но 'серебришко' - единственный пригодный материал. Я буду делать детали только из него, даже если на сбор достаточного количества уйдет год. Но куски этого металла мне на Острове встречались - он часто смешивается с серебром ввиду внешней схожести.";
			link.l1 = "Хм. А если я помогу вам найти достаточное количество серебришка, вы дадите мне костюм для спуска под воду?";
			link.l1.go = "mechanic_10";
		break;
		
		case "mechanic_10":
			dialog.text = "Ну что за вопрос! Конечно, дам. Тем более, я уже говорил: сам я под воду не полезу из-за крабов, а других желающих в последнее время тоже не наблюдается.";
			link.l1 = "Тогда покажите мне кусок этого металла, чтобы я мог понять, о чем идет речь.";
			link.l1.go = "mechanic_11";
		break;
		
		case "mechanic_11":
			dialog.text = "Так вы беретесь за розыски? Превосходно. Вот, возьмите этот кусок как образец для сравнения. Ищите среди серебряной руды и самородков. Отличить его на первый взгляд непросто, но вы быстро разберетесь, что к чему. На серебре практически всегда есть хотя бы небольшие потемнения. А этот металл чист.";
			link.l1 = "Хорошо. Я немедленно приступаю к поискам. Какие-нибудь предположения, где его можно найти с наибольшей вероятностью, у вас есть?";
			link.l1.go = "mechanic_12";
		break;
		
		case "mechanic_12":
			GiveItem2Character(pchar, "jewelry10");
			PlaySound("interface\important_item.wav");
			Log_Info("Вы получили предмет");
			dialog.text = "Увы, нет. Если бы я знал - то ваша помощь мне бы не потребовалась. Но совет все же дам: поищите на кораблях клана ривадос - я на них не бываю, соответственно, шанс нахождения там больше, ибо корабли нарвалов я уже облазил вдоль и поперек.";
			link.l1 = "Я принял ваши слова к сведению, Хенрик. Надеюсь, мне повезет.";
			link.l1.go = "mechanic_13";
		break;
		
		case "mechanic_13":
			dialog.text = "Соберите еще десять таких кусков. Это минимум, необходимый для ремонта костюма. Желаю удачи!";
			link.l1 = "Спасибо. До встречи, Механик!";
			link.l1.go = "mechanic_14";
		break;
		
		case "mechanic_14":
			DialogExit();
			pchar.questTemp.LSC = "platinum";
			AddQuestRecord("LSC", "7");
			if (GetSummonSkillFromName(pchar, SKILL_FORTUNE) >= 65 || rand(2) == 1) pchar.questTemp.LSC.PtAddQty = 0;
			else pchar.questTemp.LSC.PtAddQty = rand(4);
		break;
		
		case "mechanic_15":
			RemoveItems(pchar, "jewelry10", 11);
			dialog.text = "Так-так, покажите... Великолепно! Отличная работа, молодой человек! Это было трудно?";
			link.l1 = "Ну, как сказать...";
			link.l1.go = "mechanic_16";
		break;
		
		case "mechanic_16":
			dialog.text = "Ну что же, теперь я могу приступить к ремонту костюма. Не буду откладывать дело в долгий ящик и начну завтра. Ведь вам не терпится попасть на дно, я правильно понимаю?";
			link.l1 = "Именно так. Очень хочу исследовать подводное царство.";
			link.l1.go = "mechanic_17";
		break;
		
		case "mechanic_17":
			dialog.text = "Это очень хорошо, потому что у меня будет для вас поручение, когда мы организуем ваше погружение. Но об этом позже. Приходите через пять дней - я надеюсь, к этому моменту я уже управлюсь с ремонтом.";
			link.l1 = "Хорошо. Желаю вам удачи!";
			link.l1.go = "mechanic_18";
		break;
		
		case "mechanic_18":
			dialog.text = "Удача, безусловно, нужна всегда, но сборка костюма - это прежде всего долгий и кропотливый труд. Кроме того, мне сначала нужно сутки провести у плавильного горна с Юргеном - нужно из ваших кусков металла сделать пластины надлежащей формы.";
			link.l1 = "Тогда не буду вам мешать. Встретимся через пять дней. До свидания!";
			link.l1.go = "mechanic_19";
		break;
		
		case "mechanic_19":
			DialogExit();
			pchar.questTemp.LSC = "platinum_wait";
			AddQuestRecord("LSC", "8");
			SetFunctionTimerCondition("LSC_PrepareUnderwater_Check", 0, 0, 5, false); // таймер
			AddCharacterExpToSkill(pchar, "Fortune", 300);
		break;
		
		case "mechanic_20":
			if (sti(pchar.questTemp.LSC.PtAddQty) == 0)
			{
				dialog.text = "Да. Мы с Юргеном замечательно потрудились - принесенных вами слитков как раз хватило для выполнения работы. Костюм починен и собран. Мне осталось только испытать его, но я уверен, что все будет в порядке. Приходите завтра часам к десяти утра - я заправлю резервуары костюма воздухом, и вы сможете наконец осуществить свое желание.";
				link.l1 = "Великолепно! Жду, не дождусь. Тогда до завтра, Хенрик!";
				link.l1.go = "mechanic_24";
				DeleteAttribute(pchar, "questTemp.LSC.PtAddQty");
				AddCharacterExpToSkill(pchar, "Fortune", 100);
			}
			else
			{
				dialog.text = "Я вынужден вас огорчить, "+pchar.name+". Как я и предполагал, металла оказалось недостаточно. Я посчитал - для завершения ремонта мне нужно еще таких слитков в количестве "+FindRussianQtyString(sti(pchar.questTemp.LSC.PtAddQty))+". И я снова вынужден просить вас о помощи.";
				link.l1 = "Ну что же, я ожидал такого поворота событий. Хорошо, я попробую достать недостающие самородки.";
				link.l1.go = "mechanic_21";
			}
		break;
		
		case "mechanic_21":
			dialog.text = "Я буду вас ждать. Будьте уверены, этого количества уже точно хватит. Как только вы принесете - я буквально за сутки закончу работу.";
			link.l1 = "Надеюсь, что это так... До встречи!";
			link.l1.go = "mechanic_22";
		break;
		
		case "mechanic_22":
			DialogExit();
			pchar.questTemp.LSC = "platinum_add_wait";
			AddQuestRecord("LSC", "9");
			AddQuestUserData("LSC", "sQty", FindRussianQtyString(sti(pchar.questTemp.LSC.PtAddQty)));
		break;
		
		case "mechanic_23":
			RemoveItems(pchar, "jewelry10", sti(pchar.questTemp.LSC.PtAddQty));
			dialog.text = "Замечательно! Теперь костюм будет восстановлен. Приходите послезавтра часикам к десяти утра - к этому времени я уже соберу костюм, испытаю, заправлю резервуары воздухом, и вы наконец сможете осуществить свое желание.";
			link.l1 = "Великолепно! Жду, не дождусь. Тогда до послезавтра, Хенрик!";
			link.l1.go = "mechanic_24";
		break;
		
		case "mechanic_24":
			DialogExit();
			if (CheckAttribute(pchar, "questTemp.LSC.PtAddQty"))
			{
				iTemp = 2;
				sTemp = "послезавтра";
				DeleteAttribute(pchar, "pchar.questTemp.LSC.PtAddQty");
			}
			else
			{
				iTemp = 1;
				sTemp = "завтра";
			}
			if (!CheckAttribute(pchar, "questTemp.LSC.NatanTalk")) string sText = "Но прежде чем осуществить погружение, я должен обязательно найти Натаниэля Хоука и поговорить с ним."; //не было разговора с Натаном
			else sText = "";
			AddQuestRecord("LSC", "10");
			AddQuestUserData("LSC", "sText1", sTemp);
			AddQuestUserData("LSC", "sText2", sText);
			pchar.quest.LSC_prepunderwater.win_condition.l1 = "Timer";
			pchar.quest.LSC_prepunderwater.win_condition.l1.date.hour  = 10;
			pchar.quest.LSC_prepunderwater.win_condition.l1.date.day   = GetAddingDataDay(0, 0, iTemp);
			pchar.quest.LSC_prepunderwater.win_condition.l1.date.month = GetAddingDataMonth(0, 0, iTemp);
			pchar.quest.LSC_prepunderwater.win_condition.l1.date.year  = GetAddingDataYear(0, 0, iTemp);
			pchar.quest.LSC_prepunderwater.function = "LSC_PrepareUnderwater";
			pchar.questTemp.LSC = "wait";
		break;
		
		case "immersion":
			dialog.text = "Да, костюм готов, проверен и заправлен воздухом. Можете приступать к погружению.";
			if (!CheckAttribute(pchar, "questTemp.LSC.NatanTalk")) // не было разговора с Натаном
			{
				link.l1 = "Очень хорошо. Но сейчас я пока не могу отправиться под воду - мне нужно решить одну проблему, связанную... эм-м-м... с одним моим знакомым, Натаном Хоуком. Что-то никак не могу его найти. Костюм же может подождать?";
				link.l1.go = "natan";
			}
			else
			{
				link.l1 = "Отлично! Когда мы начинаем? Прямо сейчас?";
				link.l1.go = "immersion_1";
			}
		break;
		
		case "natan":
			dialog.text = "Конечно. Будет ждать, сколько потребуется. Вы же не будете искать вашего друга полгода?";
			link.l1 = "Безусловно. Возможно, я найду его даже сегодня. Как только закончу дела с ним - сразу же приду к вам.";
			link.l1.go = "natan_1";
		break;
		
		case "natan_1":
			dialog.text = "Да пожалуйста. Приходите, как будете готовы спуститься на дно.";
			link.l1 = "Спасибо!";
			link.l1.go = "exit";
			pchar.questTemp.LSC = "underwater_natan";
		break;
		
		case "immersion_1":
			dialog.text = "Да хоть и прямо сейчас. Но сначала я прочитаю вам небольшую лекцию, или инструкцию. Спуск производите с платформы 'Феникс' - проход туда через кормовую галерею 'Сан-Габриэля'. На платформе установлена лебедка, при помощи которой вы спуститесь на дно. С ее же помощью вы подниметесь обратно - никаким иным способом вы всплыть не сможете - костюм очень тяжел\nТак что запомните, где находится крюк лебедки под водой и не потеряйтесь. Далее. Воздуха в резервуарах достаточно на 20 минут нахождения под водой. Если вы израсходуете весь воздух, и при этом останетесь под водой, вы попросту задохнетесь. Так что следите за временем\nНе отходите далеко от крюка лебедки, иначе у вас просто может не хватить времени вернуться к ней назад, и Боже вас упаси отправиться с нашего мелководья в морские глубины - вас сплющит, как камбалу\nПроявляйте острожность, под водой полно гигантских крабов. Если вы подойдете к ним слишком близко - они атакуют вас. Не стоит рисковать понапрасну - если они нападут стаей, вам придется ретироваться, а бегать под водой у вас точно не получится.";
			link.l1 = "С крабами я как-нибудь управлюсь. Насчет остального понял - в глубину не лезть, держаться поближе к лебедке и не забывать о времени. Когда можно спуститься?";
			link.l1.go = "immersion_2";
		break;
		
		case "immersion_2":
			dialog.text = "Спускаться можете когда угодно, но только в светлое время суток, с семи утра до девяти вечера, потому что я ума не приложу, что вы там рассмотрите ночью в кромешной тьме.";
			link.l1 = "Понятно.";
			link.l1.go = "immersion_4";
		break;
		
		case "immersion_4":
			dialog.text = "Ну вот и все инструкции. Костюм возьмете в помещении на платформе, после погружения снимите его и принесите мне, я заправлю его воздухом снова. Но! В день больше одного погружения я вам делать крайне не советую: даже двадцатиминутное нахождение под водой и дыхание сжатым воздухом оказывают вредное воздействие на здоровье.";
			link.l1 = "Ну, тогда больше одного раза в день под воду лезть и не буду.";
			link.l1.go = "immersion_5";
		break;
		
		case "immersion_5":
			dialog.text = "Я рад, что вы все приняли к сведению. Теперь ступайте, и удачи вам!";
			link.l1 = "Спасибо!";
			link.l1.go = "immersion_6";
		break;
		
		case "immersion_6":
			DialogExit();
			pchar.questTemp.LSC = "first_immersion"; // флаг на первое погружение
			pchar.questTemp.LSC.immersion = "true"; // погружение возможно
			pchar.quest.LSC_takeUnderwater.win_condition.l1 = "locator";
			pchar.quest.LSC_takeUnderwater.win_condition.l1.location = "FenixPlatform";
			pchar.quest.LSC_takeUnderwater.win_condition.l1.locator_group = "item";
			pchar.quest.LSC_takeUnderwater.win_condition.l1.locator = "armor";
			pchar.quest.LSC_takeUnderwater.function = "LSC_takeUnderwater"; // выдача костюма
			pchar.quest.LSC_UnderwaterDolly.win_condition.l1 = "locator";
			pchar.quest.LSC_UnderwaterDolly.win_condition.l1.location = "Underwater";
			pchar.quest.LSC_UnderwaterDolly.win_condition.l1.locator_group = "quest";
			pchar.quest.LSC_UnderwaterDolly.win_condition.l1.locator = "dolly";
			pchar.quest.LSC_UnderwaterDolly.function = "LSC_FindUnderwaterDolly"; // нашли статую
			NextDiag.CurrentNode = "after_first_immersion"; // нода после первого погружения
			AddQuestRecord("LSC", "11");
		break;
		
		case "after_first_immersion":
			if (CheckAttribute(pchar, "questTemp.LSC.immersion"))
			{
				dialog.text = "Ну, и почему вы еще здесь? Костюм вас уже заждался.";
				link.l1 = "Да-да, я иду.";
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = "Ну, как прошло первое погружение?";
				if (CheckAttribute(pchar, "questTemp.LSC.FindDolly"))
				{
					link.l1 = "Все как нельзя лучше, я доволен результатами. Я нашел в затонувшем галеоне каменную статую, у которой, как я слышал по рассказам, ривадос ранее проводили жертвоприношения. Скажите, Хенрик, вы не знаете кого-нибудь, кто мог бы поподробнее рассказать, как этот ритуал проводился?";
					link.l1.go = "af_immersion_1";
				}
				else
				{
					link.l1 = "Нормально. У меня все получилось! И мне было очень интересно, хотя и чуточку жутковато.";
					link.l1.go = "af_immersion_2";
				}
			}
			NextDiag.TempNode = "after_first_immersion";
		break;
		
		case "af_immersion_1":
			dialog.text = "Заинтересовались нашей историей? Ну, тогда вам прямая дорога к Антонио Бетанкуру. Он у нас потомственный горожанин, родился на Острове. Он живет на флейте 'Плуто'. Если уже он не знает - то не знает никто.";
			link.l1 = "Отлично! Надо будет обязательно нанести ему визит.";
			link.l1.go = "af_immersion_2";
			pchar.questTemp.LSC.Betancur = "true";
			AddQuestRecord("LSC", "14");
		break;
		
		case "af_immersion_2":
			dialog.text = "Оставьте костюм у меня. Если вы захотите еще раз спуститься на дно - приходите завтра или в любой день позже, я заправлю резервуары воздухом.";
			if (CheckCharacterItem(pchar, "underwater"))
			{
				link.l1 = "Конечно. Вот ваш костюм. Спасибо!";
				link.l1.go = "af_immersion_3";
			}
			else
			{
				link.l1 = "Конечно. Сейчас принесу!";
				link.l1.go = "af_immersion_wait";
			}
		break;
		
		case "af_immersion_wait":
			dialog.text = "Ну, вы принесли мое снаряжение?";
			if (CheckCharacterItem(pchar, "underwater"))
			{
				link.l1 = "Конечно. Вот ваш костюм. Спасибо!";
				link.l1.go = "af_immersion_3";
			}
			else
			{
				link.l1 = "Уже несу!";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "af_immersion_wait";
		break;
		
		case "af_immersion_3":
			DialogExit();
			RemoveCharacterEquip(pchar, CIRASS_ITEM_TYPE);
			RemoveItems(pchar, "underwater", 1);
			LocatorReloadEnterDisable("SanGabrielMechanic", "reload3", false);
			SetFunctionTimerCondition("LSC_ReadyUnderwater", 0, 0, 1, false);
			NextDiag.CurrentNode = "First time";
			// даем старт мини-квестам с крабикусами
			sld = characterFromId("Carpentero");
			sld.quest.crab = "begin";
			if (GetCharacterIndex("LSC_Jacklin") != -1)
			{
				sld = characterFromId("LSC_Jacklin");
				sld.quest.crab = "true";
			}
		break;
		
		// блок погружений, за искл. первого
		case "immersion_next":
			if (CheckAttribute(npchar, "quest.guarantee")) // требует залог
			{
				dialog.text = "Да, конечно. Костюм проверен и заправлен воздухом, стоит на платформе 'Феникс' где обычно. Приготовили залог - 500 тысяч песо?";
				if (sti(pchar.money) >= 500000)
				{
					link.l1 = "Да, конечно. Вот, возьмите.";
					link.l1.go = "immersion_next_pay";
				}
				else
				{
					link.l1 = "Ой! Совсем забыл! Сейчас принесу...";
					link.l1.go = "exit";
				}
			}
			else
			{
				dialog.text = "Да, конечно. Костюм проверен и заправлен воздухом, стоит на платформе 'Феникс' где обычно.";
				link.l1 = "Тогда я отправляюсь под воду. Спасибо!";
				link.l1.go = "immersion_next_1";
			}
		break;
		
		case "immersion_next_1":
			DialogExit();
			DeleteAttribute(pchar, "questTemp.LSC.UW_ready"); 
			LocatorReloadEnterDisable("LostShipsCity_town", "reload72", false); //открываем вход в Феникс
			pchar.questTemp.LSC.immersion = "true"; // погружение возможно
			pchar.quest.LSC_takeUnderwater.win_condition.l1 = "locator";
			pchar.quest.LSC_takeUnderwater.win_condition.l1.location = "FenixPlatform";
			pchar.quest.LSC_takeUnderwater.win_condition.l1.locator_group = "item";
			pchar.quest.LSC_takeUnderwater.win_condition.l1.locator = "armor";
			pchar.quest.LSC_takeUnderwater.function = "LSC_takeUnderwater"; // выдача костюма
		break;
		
		case "immersion_next_2":
			dialog.text = "Хорошо. Если желаете еще спуститься под воду - приходите завтра или позже. Я подготовлю костюм к работе.";
			link.l1 = "Спасибо, Механик!";
			link.l1.go = "immersion_next_3";
		break;
		
		case "immersion_next_3":
			DialogExit();
			DeleteAttribute(pchar, "questTemp.LSC.UW_end"); 
			RemoveCharacterEquip(pchar, CIRASS_ITEM_TYPE);
			RemoveItems(pchar, "underwater", 1);
			if (CheckAttribute(npchar, "quest.guarantee")) AddMoneyToCharacter(pchar, 500000); // возврат залога
			LocatorReloadEnterDisable("SanGabrielMechanic", "reload3", false);
			SetFunctionTimerCondition("LSC_ReadyUnderwater", 0, 0, 1, false);
		break;
		
		case "immersion_next_pay":
			AddMoneyToCharacter(pchar, -500000);
			dialog.text = "Когда вернете мне скафандр - получите ваши деньги назад. Все по-честному.";
			link.l1 = "Спасибо, Механик! Ну, а я отправляюсь под воду.";
			link.l1.go = "immersion_next_1";
		break;
		// блок погружений
		
	//--------------------------------------вернулся на Остров---------------------------------------------
		case "return":
			dialog.text = "Позвольте! К какой статуе? А-а, кажется, я понимаю. Это вы сейчас про истукана, который когда-то затонул вместе с кораблем 'Сан-Херонимо'? Так что, эти сказки ривадос - действительно правда?";
			link.l1 = "Именно! И никакие это не сказки. На архипелаге я знаю еще два таких истукана, и они переносят любого коснувшегося их от одного к другому по кругу.";
			link.l1.go = "return_1";
		break;
		
		case "return_1":
			dialog.text = "Ясно-ясно. Придется вам поверить, хотя вы несете антинаучный бред. Статуи переносят в пространстве.. пхе! Ну кто бы подумал?";
			link.l1 = "Уж лучше просто поверьте и не ломайте над этим голову. Я действительно не лгу.";
			link.l1.go = "return_2";
		break;
		
		case "return_2":
			dialog.text = "Хорошо. Ну, а скафандр вы во время вашей телепортации, надеюсь, не потеряли?";
			if(CheckCharacterItem(pchar, "underwater"))
			{
				link.l1 = "Нет, конечно. Он, можно сказать, спас меня от карибов. Я принес его вам.";
				link.l1.go = "return_4";
			}
			else
			{
				link.l1 = "Нет, конечно. Он, можно сказать, спас меня от карибов. Но сейчас у меня его с собой нет.";
				link.l1.go = "return_3";
			}
		break;
		
		case "return_3":
			dialog.text = "Ну так принесите его мне, черт возьми! Пока не вернете мне скафандр - дальнейшего разговора не будет, так и знайте!";
			link.l1 = "Да не кипятитесь вы так, Механик. Верну я вам скафандр!";
			link.l1.go = "exit";
			NextDiag.TempNode = "return_underwater";
		break;
		
		case "return_underwater":
			if(CheckCharacterItem(pchar, "underwater"))
			{
				dialog.text = "А, вы все-таки принесли мне мой скафандр! Спасибо-спасибо, а то я уже начал было отчаиваться.";
				link.l1 = "Зря вы переживали. Я же сказал - верну, значит - верну.";
				link.l1.go = "return_4";
			}
			else
			{
				dialog.text = "Пока не вернете мне мой скафандр - даже не подходите ко мне.";
				link.l1 = "Хорошо-хорошо...";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "return_underwater";
		break;
		
		case "return_4":
			DeleteAttribute(pchar, "questTemp.LSC.UW_end"); 
			RemoveCharacterEquip(pchar, CIRASS_ITEM_TYPE);
			RemoveItems(pchar, "underwater", 1);
			SetFunctionTimerCondition("LSC_ReadyUnderwater", 0, 0, 1, false);
			dialog.text = "Очень хорошо. Я уже начинал подумывать об изготовлении нового, но это затянулось бы на год, не меньше... Я очень рад, что вы проявили хозяйственность и сохранили вверенное вам имущество в целости. И я даже сделаю вам презент.";
			link.l1 = "Вы что это - серьезно?";
			link.l1.go = "return_5";
		break;
		
		case "return_5":
			dialog.text = "Ну конечно! Вы же помогли мне починить скафандр, потом не бросили его под первым кустом, берегли его, носили с собой и вернули мне. В общем, я дарю вам вот этот набор слесарных инструментов. Научитесь ими пользоваться. С их помощью вы сможете смастерить очень много полезных вещей.";
			link.l1 = "Ну какой же еще подарок можно было ждать от Механика! Конечно - набор инструментов! Спасибо большое, Хенрик, я, право, тронут... Я не заслужил этого подарка.";
			link.l1.go = "return_6";
		break;
		
		case "return_6":
			GiveItem2Character(pchar, "mechanic_tool");
			Log_Info("Вы получили слесарный инструмент");
			PlaySound("interface\important_item.wav");
			dialog.text = "Мне лучше знать, заслужили или нет. Берите-берите! Они вам пригодятся. А вот скафандр теперь я вам буду выдавать только под залог в полмиллиона песо, раз вы такой шустрый и умеете прыгать на расстояния через всякие статуи.";
			link.l1 = "Ого! Ну что же, я понимаю - предосторожность...";
			link.l1.go = "return_7";
		break;
		
		case "return_7":
			dialog.text = "Конечно. А то вдруг вы с ним сбежите однажды? Тогда эти полмиллиона послужат мне компенсацией.";
			link.l1 = "Хорошо, Хенрик. Я согласен. Честно говоря, я думал, вы мне его больше вообще не дадите.";
			link.l1.go = "return_8";
		break;
		
		case "return_8":
			dialog.text = "Отнюдь. Полмиллиона в залог - и пользуйтесь на здоровье.";
			link.l1 = "Договорились! Тогда я смогу как обычно брать его для погружений, начиная с завтрашнего дня?";
			link.l1.go = "return_9";
		break;
		
		case "return_9":
			dialog.text = "Именно так.";
			link.l1 = "Спасибо! Еще увидимся, Хенрик!";
			link.l1.go = "return_10";
		break;
		
		case "return_10":
			DialogExit();
			AddQuestRecord("LSC", "26");
			npchar.quest.return_isl = "true";
			npchar.quest.guarantee = "true"; // залог за скафандр
			NextDiag.CurrentNode = "First time";
		break;
//----------------------------------------- специальные реакции -----------------------------------------------
		//обнаружение ГГ в сундуках
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("Что ты там копаешься, а? Да ты вор!", "Вот это да! Чуть я загляделся, а ты сразу в сундук с головой!", "По сундукам шарить вздумал?! Тебе это даром не пройдет!");
			link.l1 = "А-ать, дьявол!!!";
			link.l1.go = "fight";
		break;
		
		case "Woman_FackYou":
			dialog.text = "Ах, вот, значит, как?! По сундукам шарить вздумал?! Тебе это даром не пройдет!";
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
				dialog.text = NPCharSexPhrase(NPChar, "Послушайте, я, как гражданин этого города, прошу вас не ходить у нас с обнаженным клинком.", "Знаете, я, как гражданка этого города, прошу вас не ходить у нас с обнаженным клинком.");
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