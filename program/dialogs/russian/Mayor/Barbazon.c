// Жак Барбазон в Ле Франсуа
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	string sLoc, sTemp;
	int i;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

//--> -----------------------------------------------блок angry-------------------------------------------------
    if (CheckAttribute(npchar, "angry") && !CheckAttribute(npchar, "angry.ok"))
    {
        npchar.angry.ok = 1;
        if (!CheckAttribute(npchar, "angry.first")) //ловушка первого срабатывания
        {
            NextDiag.TempNode = NextDiag.CurrentNode;
            Dialog.CurrentNode = "AngryExitAgain";
            npchar.angry.first = 1;
        }
        else
        {
            switch (npchar.angry.kind) //сюда расписываем реакцию ангри. В npchar.angry.name пробелы удалены!!!
            {
                case "repeat":
                    if (npchar.angry.name == "Firsttime") Dialog.CurrentNode = "AngryRepeat_1";
                    if (npchar.angry.name == "I_know_you_good") Dialog.CurrentNode = "AngryRepeat_2";
                break;
            }
        }
    }
//<-- -------------------------------------------блок angry------------------------------------------------------

	switch(Dialog.CurrentNode)
	{
	// ----------------------------------- Диалог первый - первая встреча---------------------------------------
		case "First time":
            dialog.text = NPCStringReactionRepeat(""+ GetSexPhrase("У тебя дело ко мне? Нет? Тогда вали отсюда!","Ха, " + pchar.name + "! У тебя дело ко мне? Нет? Тогда не отвлекай меня.") +"",
                         "Я кажется ясно выразился.", "Хотя я выразился и ясно, но ты продолжаешь отвлекать меня!",
                         "Та-а-ак, это уже похоже на грубость, меня это утомило.", "repeat", 3, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Уже ухожу.",
                                               "Конечно, Жак...",
                                               "Извини, Жак...",
                                               "Ой...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
			
			if (sti(pchar.GenQuest.Piratekill) > 20)
			{
				dialog.text = RandPhraseSimple("У тебя крыша поехала? Вообразил себя мясником? Все пираты злы на тебя, приятель, так что лучше тебе убраться отсюда побыстрее.", "Ты, приятель, похоже, из ума выжил. Руки чесались сильно? Теперь не обессудь - здесь тебе делать нечего. Вали отсюда побыстрее!");
				link.l1 = RandPhraseSimple("Послушай, я хочу исправить ситуацию...", "Помоги мне решить эту проблему...");
				link.l1.go = "pirate_town";
				break;
			}
			
		//----------------------------------Сага - искушение Барбазона---------------------------------------
			if (CheckAttribute(pchar, "questTemp.Saga.BarbTemptation") && pchar.questTemp.Saga.BarbTemptation == "begin")
			{
				link.l1 = "У меня к тебе важный разговор, Жак... Без свидетелей.";
				link.l1.go = "Temptation";
			}
			if (CheckAttribute(pchar, "questTemp.Saga.BarbTemptation") && pchar.questTemp.Saga.BarbTemptation == "give_silk" && GetSquadronGoods(pchar, GOOD_SHIPSILK) >= 60)
			{
				link.l1 = "Я только-только с Синт-Маартена, Жак...";
				link.l1.go = "Temptation_6";
			}
			if (CheckAttribute(pchar, "questTemp.Saga.BarbTemptation") && pchar.questTemp.Saga.BarbTemptation == "terrax")
			{
				link.l1 = "Да когда же ты наконец перестанешь гавкать и начнёшь разговаривать нормально, а Жак? Не ожидал меня увидеть, да?";
				link.l1.go = "terrax";
			}
			
			//поручение капитана - выкуп
			if (CheckAttribute(pchar, "GenQuest.CaptainComission") && NPChar.city == pchar.GenQuest.CaptainComission.PiratesCity)
			{
				if(CheckAttribute(pchar,"GenQuest.CaptainComission.toMayor"))
				{
					link.l1 = "Я по поводу твоего пленника.";
					link.l1.go = "CapComission1";
					DeleteAttribute(pchar,"GenQuest.CaptainComission.toMayor");
				}
             	
				if (pchar.GenQuest.CaptainComission.PirateShips == "died" || pchar.GenQuest.CaptainComission.PirateShips == "goaway") // лесник. новая проверка. искл. возможность сразу сдать задание,минуя 15 дней.
				{
					link.l1 = "Здравствуй, Жак, я по поводу твоего поручения.";
					link.l1.go = "CapComission3";
				}
				if(CheckAttribute(pchar,"GenQuest.CaptainComission.RepeatSpeak") && !CheckAttribute(pchar,"GenQuest.CaptainComission.vikupzaplatil")) 
				{ // лесник . второй диалог с проверкой ,если ГГ ещё не принес деньги за выкуп.
					link.l1 = "Я по поводу твоего пленника.";
					link.l1.go = "CapComission6";
				}
			}	
			if (CheckAttribute(pchar, "GenQuest.Marginpassenger") && pchar.GenQuest.Marginpassenger == "cabin")
			{
				link.l1 = "Я слышал, что ты занимаешься делами, связанными с пленниками...";
				link.l1.go = "Marginpassenger";
			}
		break;
			

 		case "Exit":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
		break;

        case "I_know_you_good":
            dialog.text = NPCStringReactionRepeat(GetFullName(pchar) + "! Зачем пожаловал на этот раз?",
                         "Ты что-то забыл мне сказать? Я слушаю.", "Долго это будет продолжаться? Если тебе делать нечего, не отвлекай других!",
                         "Ты просил меня быть вежливым. Но я требую и к себе такого же отношения!", "repeat", 10, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Да, собственно, просто так заглянул"+ GetSexPhrase("","а") +", проведать. Ничего по делу нет.",
                                               "Ничего, просто так...",
                                               "Хорошо...",
                                               "Ты прав. Извини.", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			NextDiag.TempNode = "I_know_you_good";

			if (sti(pchar.GenQuest.Piratekill) > 20)
			{
				dialog.text = RandPhraseSimple("У тебя крыша поехала? Вообразил себя мясником? Все пираты злы на тебя, приятель, так что лучше тебе убраться отсюда побыстрее.", "Ты, приятель, похоже, из ума выжил. Руки чесались сильно? Теперь не обессудь - здесь тебе делать нечего. Вали отсюда побыстрее!");
				link.l1 = RandPhraseSimple("Послушай, я хочу исправить ситуацию...", "Помоги мне решить эту проблему...");
				link.l1.go = "pirate_town";
				break;
			}

			//поручение капитана - выкуп
			if (CheckAttribute(pchar, "GenQuest.CaptainComission") && CheckAttribute(pchar,"GenQuest.CaptainComission.toMayor"))
			{
				link.l1 = "Я по поводу твоего пленника.";
				link.l1.go = "CapComission1";
				DeleteAttribute(pchar,"GenQuest.CaptainComission.toMayor");
			}	
			if (pchar.GenQuest.CaptainComission.PirateShips == "died" || pchar.GenQuest.CaptainComission.PirateShips == "goaway")//  правка лесник,новая проверка ,исключающая тут же сдачу задания
			{
				link.l1 = "Здравствуй, Жак, я по поводу твоего поручения.";
				link.l1.go = "CapComission3";
			}
		/*	if(CheckAttribute(pchar,"GenQuest.CaptainComission.RepeatSpeak")) //лишний диалог лесник
			{
				link.l1 = "Я по поводу твоего пленника.";
				link.l1.go = "CapComission6";
			}*/
			if (CheckAttribute(pchar, "GenQuest.Marginpassenger") && pchar.GenQuest.Marginpassenger == "cabin")
			{
				link.l1 = "Я слышал, что ты занимаешься делами, связанными с пленниками...";
				link.l1.go = "Marginpassenger";
			}
		break;

//--> -----------------------------------Сага - Искушение Барбазона---------------------------------------------
		case "Temptation":
			dialog.text = "Ну знаешь, приятель, ко мне по пустякам рискованно обращаться... Ладно, слушаю тебя внимательно.";
			link.l1 = "Я задолжал крупную сумму. Срок выплаты близок, а я на мели. Добрые люди шепнули, что ты мастак на разные выдумки и всегда знаешь, где можно урвать приличный куш.";
			link.l1.go = "Temptation_1";
		break;
		
		case "Temptation_1":
			dialog.text = "Э-э, мил человек! Я Жак Добряк для тех, кто мне верен. Для остальных я Барбазон, а иногда и Люцифер. Откуда мне знать, могу ли я доверять тебе?";
			link.l1 = "Испытай меня в деле. Клянусь, ты не пожалеешь!";
			link.l1.go = "Temptation_2";
		break;
		
		case "Temptation_2":
			dialog.text = "Хм... Ну что же, ты, наверное, уже слышал от 'добрых людей', что бывает с теми, кто пытается меня провести. Поэтому не буду тебя лишний раз смущать жуткими подробностями. Есть у меня одно небольшое поручение. Если справишься - решим твои финансовые проблемы.";
			link.l1 = "Не сомневайся, я бывал во многих переделках, и ещё ни разу...";
			link.l1.go = "Temptation_3";
		break;
		
		case "Temptation_3":
			dialog.text = "Заткнись и слушай, что я тебе говорю. Пару недель назад рядом с Синт-Маартеном голландский патруль прижал одного моего порученца. Тот вёз для меня голландский парусный шёлк. Это большая редкость в наших краях, голландцы завозят его мелкими партиями исключительно для нужд военного флота компании\nТак вот, мне удалось урвать шесть тюков этого шёлка, а Симон Морель на бригантине 'Солёный пёс' должен был его мне доставить, но случайно напоролся на голландский патруль. А может, и не случайно. Это я знаю со слов штурмана Мореля, который якобы единственный, кто спасся после боя с голландцами\nСудовой журнал Мореля, который он мне притащил, это подтверждает. Из него следует, что Морель, уходя от погони, выкинул весь груз вместе с моим шёлком. Странно, правда? Шёлк ведь весит мало. Лучше бы они выкинули пушки, всё равно против патруля им ничего не светило.";
			link.l1 = "Действительно, что-то здесь не сходится.";
			link.l1.go = "Temptation_4";
		break;
		
		case "Temptation_4":
			dialog.text = "Всё может быть. Я частенько имею дело с храбрецами, но вот умных людей среди них немного. Ты уж извини, если задел. Твоя задача проверить место, где Морель сбросил груз. Это в районе 21 гр. 10' северной широты и 61 гр. 30' западной долготы - так было указано в судовом журнале\nГолландцы наматывают этот шёлк на стержни из пробки, так что из-за этого тюки не должны были затонуть и плавают на поверхности по сей день. Там должно быть шесть тюков. Отправляйся немедля, время дорого.";
			link.l1 = "Уже в пути!";
			link.l1.go = "Temptation_5";
		break;
		
		case "Temptation_5":
			DialogExit();
			SetFunctionTimerCondition("Saga_BarbTemptationOver", 0, 0, 10, false); // таймер
			pchar.quest.BarbTemptation.win_condition.l1 = "location";
			pchar.quest.BarbTemptation.win_condition.l1.location = "SentMartin";
			pchar.quest.BarbTemptation.function = "Saga_BarbTemptationBarkas";
			pchar.questTemp.Saga.BarbTemptation = "silk";
			AddQuestRecord("BarbTemptation", "2");
		break;
		
		case "Temptation_6":
			dialog.text = "Прекрасно. Ну что, нашёл мой шёлк?";
			link.l1 = "Да, все шесть тюков, как ты и говорил.";
			link.l1.go = "temptation_wrong";
			if (GetSquadronGoods(pchar, GOOD_SHIPSILK) >= 90)
			{
				link.l2 = "Да. Только тюков оказалось больше, чем ты говорил, а именно - девять. Я приволок тебе все, ты уж сам разберись, как такое могло получиться.";
				link.l2.go = "temptation_right";
			}
		break;
		
		case "temptation_wrong":
			dialog.text = "Это неправильный ответ. Тюков должно было быть девять. И если ты нашёл шесть из них, то должен был найти и остальные. Так что ты либо крыса, либо лентяй и простофиля. Ты должен мне три тюка шёлка и ещё три в качестве моральной компенсации за попытку обмана.";
			if (GetSquadronGoods(pchar, GOOD_SHIPSILK) >= 120)
			{
				link.l1 = "Ну ты и хитрец! Учту на будущее. Держи свой шёлк и забудем о моей оплошности.";
				link.l1.go = "temptation_wrong_1";
			}
			link.l2 = "Тебе сказали, что тюков было шесть и ни одним больше. Я отдал тебе всё, и мне плевать, что ты про это думаешь. Больше у меня всё равно нет.";
			link.l2.go = "temptation_wrong_2";
		break;
		
		case "temptation_wrong_1":
			RemoveCharacterGoods(pchar, GOOD_SHIPSILK, 120);
			dialog.text = "Хорошо. Надеюсь, подобное больше не повторится, так как я намерен поручить тебе важное дело. Сколько денег ты хочешь заработать?";
			link.l1 = "Лишних денег не бывает, но меня вполне устроили бы пятьдесят тысяч песо.";
			link.l1.go = "junior";
		break;
		
		case "temptation_wrong_2":
			dialog.text = "Ах вот как мы запели! Ну, это тебе даром не пройдёт. Я тебя сразу предупреждал - не пытайся меня надуть! Охрана! Крыса в резиденции!";
			link.l1 = "А-ать!";
			link.l1.go = "temptation_wrong_fight";
		break;
		
		case "temptation_wrong_fight":
			chrDisableReloadToLocation = true;//закрыть локацию
			DialogExit();
			LAi_SetWarriorType(npchar);
			ChangeCharacterAddressGroup(npchar, "LeFransua_townhall", "goto", "goto1");
			LAi_SetImmortal(npchar, true);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			for (i = 1; i <= 3; i++)
			{
				sld = GetCharacter(NPC_GenerateCharacter("BarbGuard_"+i, "citiz_4"+(i+6), "man", "man", 80, PIRATE, 1, true, "quest"));
				FantomMakeCoolFighter(sld, 80, 100, 100, "blade_21", "pistol4", "bullet", 3000);
				ChangeCharacterAddressGroup(sld, "LeFransua_townhall", "reload", "reload1");
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
		case "temptation_right":
			RemoveCharacterGoods(pchar, GOOD_SHIPSILK, 80);
			dialog.text = "Хорошая работа. Я проверял тебя на жадность, и ты прошёл проверку. Тюков и должно было быть девять. Один из них достаётся тебе. Ну, а теперь мы можем поговорить всерьёз. Сколько денег ты хочешь заработать?";
			link.l1 = "Лишних денег не бывает, но меня вполне устроили бы пятьдесят тысяч песо.";
			link.l1.go = "junior";
		break;
		
		case "junior":
			dialog.text = "У тебя есть возможность заработать даже больше. Один серьёзный человек просил меня подыскать надёжного парня вроде тебя для одного деликатного и опасного дела. Этот человек очень богат и сможет отблагодарить тебя по достоинству, если ты его не подведёшь.";
			link.l1 = "Я готов.";
			link.l1.go = "junior_1";
		break;
		
		case "junior_1":
			dialog.text = "Слушай внимательно. Ты должен встретиться с его доверенным лицом по кличке Валет. Он капитан полакра 'Марлин', больше я о нём ничего не знаю. Ты найдёшь его в Капстервиле. Пароль - 'охота уже началась'. От него ты узнаешь, что делать дальше. Мне ты ничего не должен. Я просто решил тебе помочь. Если удача не отвернётся от тебя, мы ещё встретимся.";
			link.l1 = "Спасибо за участие. Отправляюсь немедленно!";
			link.l1.go = "junior_2";
		break;
		
		case "junior_2":
			DialogExit();
			AddQuestRecord("BarbTemptation", "7");
			Saga_SetJuniorInCharles(); // ставим Валета
			pchar.questTemp.Saga.BarbTemptation = "valet";
		break;
		
		case "terrax":
			dialog.text = "Что?! Да я вырву у тебя...";
			link.l1 = "Ничего ты не вырвешь, Барбазон. Вскроем карты! Я работаю на Яна Свенсона. Я раскрыл махинацию, которую вы затеяли вместе с Джекманом. Мне всё известно: и что вы задумали, и какова была твоя роль. Джекман и его братец Валет мертвы - один оказался несговорчивым, а второй подписал себе приговор тогда, когда убил Блейза Шарпа. ";
			link.l1.go = "terrax_1";
		break;
		
		case "terrax_1":
			dialog.text = "Чёрт возьми! Тиракс мне никогда этого не простит! Но я ещё...";
			link.l1 = "Не делай глупостей, Жак. Я прекрасно знал, что разговор будет непростым, поэтому принял меры предосторожности. Глянь в окно... твоя халупа окружена моими мушкетёрами. Мой отряд рассредоточен в посёлке, а у ворот стоит штурмовая группа. Хочешь устроить резню? Нет проблем!";
			link.l1.go = "terrax_2";
		break;
		
		case "terrax_2":
			dialog.text = "Дьявол, чего же ты хочешь?";
			link.l1 = "Ты не поверишь, Барбазон... Мира! Я хочу мира. Именно поэтому я не сказал и не скажу Тираксу о твоём участии в заговоре против него. Конечно, если ты пойдёшь мне навстречу...";
			link.l1.go = "terrax_3";
		break;
		
		case "terrax_3":
			dialog.text = "Чего ты хочешь взамен? Денег? Сколько?";
			if (!CheckAttribute(pchar, "questTemp.Saga.DodsonDie")) // Акула жив
			{
				link.l1 = "О нет, оставь эти разговоры для своих слабых на голову порученцев. Мне нужно кое-что другое. А именно - твой голос на Совете в пользу Стивена Додсона.";
			}
			else
			{
				link.l1 = "О нет, оставь эти разговоры для своих слабых на голову порученцев. Мне нужно кое-что другое. А именно - твой голос на Совете в пользу Маркуса Тиракса.";
			}
			link.l1.go = "terrax_4";
		break;
		
		case "terrax_4":
			if (!CheckAttribute(pchar, "questTemp.Saga.DodsonDie")) sTemp = "И Стивен Додсон на нашей стороне. ";
			else sTemp = "";
			dialog.text = "Вот как? Дай-ка подумать... А если я откажусь?";
			link.l1 = "Тогда ты останешься один, Жак. Совсем один. Против тебя пойдут войной Свенсон, Тиракс и Хоук. "+sTemp+"Я всего лишь покажу им письмо Валета, братца Джекмана. Да и слову моему поверят... Как ты думаешь, сколько времени после этого ты просидишь на своём тёплом месте?";
			link.l1.go = "terrax_5";
		break;
		
		case "terrax_5":
			dialog.text = "Хоук? Он жив?";
			link.l1 = "Жив. Я вытащил его из западни, в которую его загнал Джекман. Так что друг Якоба - его кровный враг, имей это в виду. Ну и меня со счетов не сбрасывай, Барбазон.";
			link.l1.go = "terrax_6";
		break;
		
		case "terrax_6":
			dialog.text = "Да не друг мне Джекман! Чёрт бы тебя побрал! Ты загнал меня в угол!";
			link.l1 = "Глупости. Твой голос в Совете за того, кого я назвал - и для тебя ровным счётом ничего не изменится. Я же сказал, Жак: я хочу мира. Я давно уже мог бы настроить против тебя всех баронов, но не сделал этого.";
			link.l1.go = "terrax_7";
		break;
		
		case "terrax_7":
			GiveItem2Character(pchar, "splinter_jb"); // дать осколок
			dialog.text = "Хорошо. Я согласен. Даю слово. Вот, держи мой каменный осколок - ведь тебе нужно это?";
			link.l1 = "Точно. Я рад, что мы договорились, Жак. Забери себе на память письмо Валета. Хотя, лучше сожги - не дай Бог попадёт в чужие руки. Но это ещё не всё...";
			link.l1.go = "terrax_8";
		break;
		
		case "terrax_8":
			RemoveItems(pchar, "letter_chad", 1);
			dialog.text = "Не всё?! Что ещё тебе от меня нужно?";
			if (CheckAttribute(pchar, "questTemp.Mtraxx.Corrida.Barbazon"))
			{
				link.l1 = "Я тебе напомню кое-что. Не так давно ты хотел убить меня и подослал свою шавку, Игнасио Марко. Это я кокнул его. Это я сломал твои планы по захвату испанского галеона с золотом из Гаваны. Это я отправил с Синт-Маартена в лапы испанцев твоего дружка Джимми Джокера, а также Бродягу и Упыря. Я - Чарли Принц! Теперь мы в расчёте, Жак, но будь любезнее со мной при последующих встречах. Ведь мы не раз с тобой ещё увидимся, я думаю. Не забывай, что за мной - все пиратские бароны, включая будущего главу Братства. А теперь - бывай, Барбазон...";
				link.l1.go = "terrax_9";
			}
			else
			{
				if (!CheckAttribute(pchar, "questTemp.Mtraxx.Corrida.Barbazon") && CheckAttribute(pchar, "questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "full_complete_end")
				{
					link.l1 = "Я тебе напомню кое-что. Не так давно ты хотел убить меня и подослал свою шавку, Игнасио Марко. У него ничего не вышло, но за тобой должок. Я - Чарли Принц!  Так что будь любезнее со мной при последующих встречах, Жак. Ведь мы не раз с тобой ещё увидимся, я думаю. Не забывай, что за мной - все пиратские бароны, включая будущего главу Братства. А теперь - бывай, Барбазон...";
					link.l1.go = "terrax_9";
				}
				else
				{
					link.l1 = "Будь любезнее со мной при последующих встречах, Жак. Ведь мы не раз с тобой ещё увидимся, я думаю. Не забывай, что за мной - все пиратские бароны, включая будущего главу Братства. А теперь - бывай, Барбазон...";
					link.l1.go = "terrax_9";
				}
			}
		break;
		
		case "terrax_9":
			DialogExit();
			NextDiag.CurrentNode = "I_know_you_good";
			AddQuestRecord("BarbTemptation", "26");
			if (CheckCharacterItem(pchar, "splinter_mt") && CheckCharacterItem(pchar, "splinter_jb") && CheckCharacterItem(pchar, "splinter_zm")) Saga_GiveCalendar();
			pchar.quest.Saga_storming_group1.win_condition.l1 = "location";
			pchar.quest.Saga_storming_group1.win_condition.l1.location = "LeFransua_town";
			pchar.quest.Saga_storming_group1.function = "Saga_DeleteStormingGroup";
			ChangeCharacterComplexReputation(pchar, "fame", 1);
		break;

//-----------------------------------Поручение капитана - Выкуп-------------------------------------------------
		case "CapComission1":
			dialog.text = "Хо-хо. Ты думаешь, у меня только один пленник? Называй, кого конкретно имеешь в виду?";
			link.l1 = pchar.GenQuest.CaptainComission.SlaveName + ". Есть такой?";
			link.l1.go = "CapComission2";
			DeleteAttribute(pchar,"GenQuest.CaptainComission.toMayor");
		break;

		case "CapComission2":
			if(CheckAttribute(pchar,"GenQuest.CaptainComission.DaysLeft"))
			{
				dialog.text = "Был. Я его продал к чёртовой матери этому плантатору с Барбадоса - полковнику Бишопу, он заезжал на прошлой неделе.";
				link.l1 = "Вот чёрт...";
				link.l1.go = "CapComission2_1";
			}
			else
			{
				dialog.text = "А-а, ну наконец-то. Я уж было подумывал продать его к чёртовой матери этому плантатору с Барбадоса, он должен появиться у меня через неделю-другую... Ты выкуп привёз"+ GetSexPhrase("","ла") +"?";
				link.l1 = "Слушай, тут такое дело... В общем, у меня нет таких денег. Но я готов"+ GetSexPhrase("","а") +" отработать.";
				link.l1.go = "CapComission2_2";
				if(makeint(pchar.money) > 150000)
				{
					link.l2 = "Хорошо, что не продал. Вот деньги - 150000 песо. Где я могу его забрать?";
					link.l2.go = "CapComission2_3";
				}	
			}
		break;
		
		case "CapComission2_1":
			dialog.text = "Долго ты телил"+ GetSexPhrase("ся","ась") +"... А кстати, этот невольник к тебе каким боком? Я, помнится, его родственникам выкуп назначал.";
			link.l1 = "Да я по поручению этих родственников и приехал"+ GetSexPhrase("","а") +".";
			link.l1.go = "CapComission2_11";
		break;
		
		case "CapComission2_11":
			dialog.text = "Ну, опоздал"+ GetSexPhrase("","а") +" ты - что я могу поделать?";
			link.l1 = "Слушай, а за сколько продал, если не секрет?"; 
			link.l1.go = "CapComission2_12";
		break;
		
		case "CapComission2_12":
			dialog.text = "Э-э, не секрет, конечно, но я тебе не скажу. А то смеяться будешь, ха-ха-ха-ха... Ну, бывай.";
			link.l1 = "Счастливо.";
			link.l1.go = "exit";
			AddQuestRecord("CaptainComission1", "10");
			AddQuestUserData("CaptainComission1", "sName", "Жак Барбазон");//правка лесник.  в СЖ запись ниже не работает																																				  
			//AddQuestUserData("CaptainComission1", "sName", ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_NOM));
			CaptainComission_GenerateManager();
		break;
		
		case "CapComission2_2":
			if(rand(3) == 1)
			{
				dialog.text = "Ну, " + pchar.name + ", ты же знаешь, что так дела не делаются. Приходи с деньгами и получишь своего заморыша, хе-хе.";
				link.l1 = "Ну ладно, до встречи.";
				link.l1.go = "CapComission2_4"; 
			}
			else
			{
				dialog.text = "Гхм-гхм... Есть у меня одно дело... Даже не знаю, как начать... В общем, нужно пустить ко дну одного зарвавшегося пирата.";
				link.l1 = "А разве нельзя убрать его в джунглях?";
				link.l1.go = "CapComission2_2_1";  
			}
		break;

		case "CapComission2_2_1":
			dialog.text = "Ну, понимаешь ли, так серьёзные дела не делаются... Мне не смерть его нужна, мне нужно отбить охоту у слишком ретивых разевать рот на мою часть добычи. Хотя, если он отправится к осьминогам - я не огорчусь.";
			link.l1 = "А почему тебе не послать за ним своих людей?";
			link.l1.go = "CapComission2_2_2";
		break;
		
		case "CapComission2_2_2":
			CaptainComission_GetRandomShore();
			pchar.GenQuest.CaptainComission.ShipName1 = GenerateRandomNameToShip(sti(NPChar.nation));
			pchar.GenQuest.CaptainComission.ShipName2 = GenerateRandomNameToShip(sti(NPChar.nation));
			pchar.GenQuest.CaptainComission.UnknownPirateName = "l" + rand(GetNamesCount(NAMETYPE_ORIG) - 1);
			sLoc = XI_ConvertString(pchar.GenQuest.CaptainComission.Island + "Abl");
			dialog.text = "Хм... В общем некий " + GetName( NAMETYPE_ORIG, pchar.GenQuest.CaptainComission.UnknownPirateName, NAME_NOM) + " убедил часть пиратов что в нашем тайнике, близ " + XI_ConvertString(pchar.GenQuest.CaptainComission.Island.Shore + "Gen") + ", есть и их доля. Недавно они снялись с якоря, и на двух судах, '" + pchar.GenQuest.CaptainComission.ShipName1 + "' и '" + pchar.GenQuest.CaptainComission.ShipName2 + "', ушли к " + sLoc + ". Понимаешь теперь, почему я не могу поручить это дело своим людям?";
			link.l1 = "Понятно. И сколько у меня есть времени?";
			link.l1.go = "CapComission2_2_3";
		break;
		
		case "CapComission2_2_3":
			dialog.text = "Думаю, дней 12-15, не больше. Мне важно, чтоб они не успели добраться до тайника, иначе топить их с ценным грузом на борту не будет смысла. Уж лучше пусть везут его сюда.";
			link.l1 = "Хорошо, я берусь за это дело. Постараюсь успеть.";
			link.l1.go = "CapComission2_2_4";
		break;
		
		case "CapComission2_2_4":
			AddQuestRecord("CaptainComission1", "24");
			AddQuestUserData("CaptainComission1", "sName", "Жак Барбазон");//правка
			//AddQuestUserData("CaptainComission1", "sName", ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_NOM));// в СЖ не работает имя . лесник
			AddQuestUserData("CaptainComission1", "sShipName1", pchar.GenQuest.CaptainComission.ShipName1);
			AddQuestUserData("CaptainComission1", "sShipName2", pchar.GenQuest.CaptainComission.ShipName2);
			AddQuestUserData("CaptainComission1", "sShoreName", XI_ConvertString(pchar.GenQuest.CaptainComission.Island.Shore + "Abl"));
			AddQuestUserData("CaptainComission1", "sShoreType", XI_ConvertString(GetIslandByArealName(pchar.GenQuest.CaptainComission.Island) + "Dat"));
			pchar.quest.CapComission_PirateAttack.win_condition.l1 = "location";
            pchar.quest.CapComission_PirateAttack.win_condition.l1.location = pchar.GenQuest.CaptainComission.Island;
            pchar.quest.CapComission_PirateAttack.function = "CaptainComission_GeneratePirateShips"; 
			SetFunctionTimerCondition("CaptainComission_PirateShipsOver", 0, 0, 15, false);
			
			DialogExit();
		break;
		
		case "CapComission2_3":
			dialog.text = "Не переживай. Мои люди доставят его к тебе на борт. А он тебе кто?";
			link.l1 = "Никто. Я выполняю поручение его родственника.";
			link.l1.go = "CapComission2_31";
		break;
		
		case "CapComission2_31":
			dialog.text = "А-а, это хорошо. А то я уж было расстроился, что продешевил, назначив такую низкую цену за твоего человека. Ха-ха-ха-ха... Ну, бывай.";
			link.l1 = "Счастливо.";
			link.l1.go = "CapComission2_32";
		break;
		
		case "CapComission2_32":
			AddQuestRecord("CaptainComission1", "9");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("","а"));
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City));			
			addMoneyToCharacter(pchar, -150000);
			pchar.GenQuest.CaptainComission.vikupzaplatil = true; // новая проверка ,если шарль заплатил выкуп за пленника. лесник																																								
			DialogExit();
			AddDialogExitQuestFunction("CaptainComission_GeneratePassengerSlave");	
		break;
		
		case "CapComission2_4":
			if(!CheckAttribute(pchar,"GenQuest.CaptainComission.RepeatSpeak"))
			{
				AddQuestRecord("CaptainComission1", "31");
				AddQuestUserData("CaptainComission1", "sName", "Жак Барбазон");		// лесник																												  
				//AddQuestUserData("CaptainComission1", "sName", ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_NOM)); в СЖ не работает
			}	
			pchar.GenQuest.CaptainComission.RepeatSpeak = true;		
			DialogExit();
		break;
		
		case "CapComission3":
			dialog.text = "Ну что, " + GetFullName(pchar) + ", пустил"+ GetSexPhrase("","а") +" на дно моего приятеля?.. хе-хе-хе...";
			if(pchar.GenQuest.CaptainComission.PirateShips == "goaway")
			{
				link.l1 = "Нет. Я не успел"+ GetSexPhrase("","а") +" их догнать. И на обратном пути они мне не попадались.";
				link.l1.go = "CapComission4";
			}
			if(pchar.GenQuest.CaptainComission.PirateShips == "died")	
			{
				link.l1 = "Да, как и договаривались - отправил"+ GetSexPhrase("","а") +" кормить акул.";
				link.l1.go = "CapComission5";
			}
			DeleteAttribute(pchar,"GenQuest.CaptainComission.PirateShips");
		break;
		
		case "CapComission4":
			dialog.text = "Чёрт! Попадались - не попадались, какая теперь разница?.. Ну, и что ты предложишь дальше?";
			link.l1 = "Может, у тебя есть какое-нибудь поручение попроще?";
			link.l1.go = "CapComission4_1";
			link.l2 = "Слушай, "+ NPChar.name +", уступи мне этого пленника подешевле...";
			link.l2.go = "CapComission4_2";
		break;
		
		case "CapComission4_1":
			dialog.text = "Нет.";
			link.l1 = "...Ну, тогда счастливо оставаться...";
			link.l1.go = "CapComission4_3";
		break;
		
		case "CapComission4_2":
			dialog.text = "Подешевле?!! Только что из-за твоей нерасторопности я лишился своего тайника! И теперь я могу уступить его подороже! Забирай за 200000, если хочешь.";
			link.l1 = "Дорого это... Прощай...";
			link.l1.go = "CapComission4_4";
			if(sti(pchar.money) >= 200000)
			{
				link.l2 = "А чёрт, держи свои деньги.";
				link.l2.go = "CapComission4_5";
			}	
		break;
		
		case "CapComission4_3":
			ChangeCharacterComplexReputation(pchar,"nobility", -2);
			AddQuestRecord("CaptainComission1", "27");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("","ла"));
			AddQuestUserData("CaptainComission1", "sName", "Барбазоном"); // лесник																			  
			//AddQuestUserData("CaptainComission1", "sName", ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_DAT));// в СЖ не работает
			AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Acc"));
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			DeleteAttribute(pchar,"GenQuest.CaptainComission.PirateShips");
			DialogExit();
		break;
		
		case "CapComission4_4":
			ChangeCharacterComplexReputation(pchar,"nobility", -2);
			AddQuestRecord("CaptainComission1", "28");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("","а"));
			AddQuestUserData("CaptainComission1", "sName", "Барбазон"); // правка	// лесник																	  
			//AddQuestUserData("CaptainComission1", "sName", ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_NOM)); в сж не работает
			AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Acc"));
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			DeleteAttribute(pchar,"GenQuest.CaptainComission.PirateShips");
			DialogExit();		
		break;
		
		case "CapComission4_5":
			dialog.text = "Можешь забрать заморыша...";
			link.l1 = "Счастливо оставаться.";
			link.l1.go = "CapComission4_6";
		break;
		
		case "CapComission4_6":
			addMoneyToCharacter(pchar, -200000);
			AddQuestRecord("CaptainComission1", "29");
			AddQuestUserData("CaptainComission1", "sName", "Барбазон"); // правки имени в сж лесник
			AddQuestUserData("CaptainComission1", "sName", ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_NOM));//в СЖ не работает
			AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Acc"));
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			DeleteAttribute(pchar,"GenQuest.CaptainComission.PirateShips");
			pchar.GenQuest.CaptainComission.SlaveAddMoney = true;
			DialogExit();	
			AddDialogExitQuestFunction("CaptainComission_GeneratePassengerSlave");	
		break;
		
		case "CapComission5":
			dialog.text = "Хо-хо! Вот это работа! Забирай своего заморыша и бывай здоров"+ GetSexPhrase("","а") +".";
			link.l1 = "Спасибо. Счастливо оставаться.";
			link.l1.go = "CapComission5_1";
		break;
		
		case "CapComission5_1":
			AddQuestRecord("CaptainComission1", "34");
			AddQuestUserData("CaptainComission1", "sName", pchar.GenQuest.CaptainComission.SlaveName);
			AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Acc"));
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			DeleteAttribute(pchar,"GenQuest.CaptainComission.PirateShips");
			DialogExit();		
			AddDialogExitQuestFunction("CaptainComission_GeneratePassengerSlave");	
		break;
		
	   	/*case "CapComission6":    // ЕСЛИ В ПЕРВЫЙ РАЗ ОТКАЗАЛ В ЗАДАНИИ ,ТО ПУСТЬ БАБКИ ИЩЕТ
		     ИНАЧЕ ПОВТОРНАЯ ДАЧА ЗАДАНИЯ ПРЕВРАЩАЕТ КВЕСТ В КАШУ.. лесник
			dialog.text = "Ты выкуп привёз"+ GetSexPhrase("","ла") +"? Ведь я не шутил, когда сказал, что продам его плантаторам.";			
			link.l1 = "Слушай, "+ NPChar.name +", тут такое дело... В общем, у меня нет таких денег. Но я готов"+ GetSexPhrase("","а") +" отработать.";
			link.l1.go = "CapComission2_2";
			if(makeint(pchar.money) > 150000)
			{
				link.l2 = "Хорошо, что не продал. Вот деньги - 150000 песо. Где я могу его забрать?"
				link.l2.go = "CapComission2_3";
			}			
		break;*/
		  case "CapComission6":                        // лесник . пусть шарль бабло ищет,или забить на пленника.
			dialog.text = "Ты выкуп привёз"+ GetSexPhrase("","ла") +"? Ведь я не шутил, когда сказал, что продам его плантаторам.";			
			link.l1 = "Пока нет денег, "+ NPChar.name +", но я работаю над этим.";
			link.l1.go = "exit";
			if(makeint(pchar.money) > 150000)
			{
				link.l2 = "Хорошо, что не продал. Вот деньги - 150000 песо. Где я могу его забрать?"
				link.l2.go = "CapComission2_3";
			}			
		break;
																																					 																																													  																																															
//--------------------------------------------Похититель------------------------------------------------------
		case "Marginpassenger":
			dialog.text = "А тебе-то какое дело до того, чем я занимаюсь, а чем нет? Знаешь что, шёл бы ты отс...";
			link.l1 = "Тише, не кипятись. Я пришёл к тебе по делу, причём именно по этому делу.";
			link.l1.go = "Marginpassenger_1";
		break;
		
		case "Marginpassenger_1":
			dialog.text = "А-а, ну ладно. За кого ты привёз выкуп?";
			link.l1 = "Погоди. Я сюда пришёл не для того, чтобы выкупать, а для того, чтобы предложить тебе купить одного моего пленника. Ну, а ты потом cможешь получить за него выкуп.";
			link.l1.go = "Marginpassenger_2";
		break;
		
		case "Marginpassenger_2":
			dialog.text = "Хм. А зачем тебе понадобилось моё посредничество? Чего сам не хочешь получить денежки напрямую?";
			link.l1 = "Для меня в данном случае это опасно. Могут быть проблемы с властями.";
			link.l1.go = "Marginpassenger_3";
		break;
		
		case "Marginpassenger_3":
			dialog.text = "Кхе... Ну, хорошо. Кто он, твой пленник?";
			link.l1 = "Это "+pchar.GenQuest.Marginpassenger.Text+" "+XI_ConvertString("Colony"+pchar.GenQuest.Marginpassenger.City+"Gen")+".";
			link.l1.go = "Marginpassenger_4";
		break;
		
		case "Marginpassenger_4":
			int iTemp = makeint(sti(pchar.GenQuest.Marginpassenger.Dublon)*2*stf(pchar.GenQuest.Marginpassenger.Chance))*100;
			dialog.text = "Так-так... Если ты не врешь, то это может оказаться интересной сделкой. Пожалуй, я готов заплатить за этого человека "+iTemp+" песо, или, если хочешь, могу поделиться полезной информацией. Что тебе больше нравится.";
			link.l1 = "Давай лучше песо. Я уже вдоволь намаялся с этим делом, будь оно неладно...";
			link.l1.go = "Marginpassenger_money";
			link.l2 = "Ха! Лучше расскажи что-нибудь полезное. Уверен, ерунды ты мне не предложишь.";
			link.l2.go = "Marginpassenger_offer";
		break;
		
		case "Marginpassenger_money":
			dialog.text = "Деньги - так деньги. Вот, держи. Теперь это больше не твоя забота. Потрудись привести товар сюда.";
			link.l1 = "Он должен быть уже около городских ворот. Спасибо! Ты меня выручил.";
			link.l1.go = "Marginpassenger_money_1";
		break;
		
		case "Marginpassenger_money_1":
			iTemp = makeint(sti(pchar.GenQuest.Marginpassenger.Dublon)*2*stf(pchar.GenQuest.Marginpassenger.Chance))*100;
			dialog.text = "Да всегда пожалуйста, привози ещё... Бывай!";
			link.l1 = "И тебе всего доброго...";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, iTemp);
			sld = characterFromId("MarginPass");
			RemovePassenger(Pchar, sld);
			sld.lifeday = 0;
			AddQuestRecord("Marginpassenger", "12");
			AddQuestUserData("Marginpassenger", "sSum", iTemp);
			CloseQuestHeader("Marginpassenger");
			DeleteAttribute(Pchar, "GenQuest.Marginpassenger");
		break;
		
		case "Marginpassenger_offer":
			pchar.GenQuest.Marginpassenger.Goods = GOOD_EBONY + rand(makeint(GOOD_MAHOGANY - GOOD_EBONY));
			pchar.GenQuest.Marginpassenger.GoodsQty = 200+rand(10)*10;
			switch (drand(1))
			{
				case 0: //бухта на южном мейне
					SelectSouthshore();
					while (!isLocationFreeForQuests(pchar.GenQuest.Marginpassenger.Shore)) SelectSouthshore(); // исправил окончание . лесник (строчка ниже)
					dialog.text = "Приятно иметь дело со сметливым человеком, парень! Теперь слушай: через несколько дней к " + XI_ConvertString(pchar.GenQuest.Marginpassenger.Shore+"Abl") + " подойдёт испанская экспедиция из Мейна, с запасами ценной древесины, и будет ждать корабля, который должен прийти и забрать груз. Если за неделю ты успеешь туда добраться - у тебя будет шанс забрать весь товар себе\nНа твоём месте я бы уже бежал к своей посудине. И потрудись доставить пленника сюда.";
					link.l1 = "Благодарю! Древесина послужит хорошей компенсацией за мои мытарства! А мой пассажир уже должен быть где-то у городских ворот. Его к тебе приведут.";
					link.l1.go = "Marginpassenger_offer_1";
				break;
				
				case 1: //просто кораблик
					SelectSouthcity();
					pchar.GenQuest.Marginpassenger.ShipName1 = GenerateRandomNameToShip(SPAIN);
					dialog.text = "Приятно иметь дело со сметливым человеком, парень! Теперь слушай: приблизительно через неделю из "+XI_ConvertString("Colony"+pchar.GenQuest.Marginpassenger.Southcity+"Gen")+" выйдет испанская баркентина '"+pchar.GenQuest.Marginpassenger.ShipName1+"' с грузом ценной древесины и отправится в порт "+XI_ConvertString("Colony"+pchar.GenQuest.Marginpassenger.Southcity1+"Gen")+". Если не будешь зевать, то запросто перехватишь её\nТы ещё здесь? На твоём месте я бы уже бежал к своей посудине. И потрудись доставить пленника сюда.";
					link.l1 = "Благодарю! Древесина послужит хорошей компенсацией за мои мытарства! А мой пассажир уже должен быть где-то у городских ворот. Его к тебе приведут.";
					link.l1.go = "Marginpassenger_offer_2";
				break;
			}
			sld = characterFromId("MarginPass");
			RemovePassenger(Pchar, sld);
			sld.lifeday = 0;
			pchar.GenQuest.Marginpassenger = "final";
		break;
		
		case "Marginpassenger_offer_1":
			DialogExit();
			AddQuestRecord("Marginpassenger", "13");
			AddQuestUserData("Marginpassenger", "sShore", XI_ConvertString(pchar.GenQuest.Marginpassenger.Shore+"Abl"));//лесник - окончание в СЖ
			SetFunctionTimerCondition("Marginpassenger_SouthshoreOver", 0, 0, 7, false);
			pchar.quest.Marginpassenger.win_condition.l1 = "location";
			pchar.quest.Marginpassenger.win_condition.l1.location = pchar.GenQuest.Marginpassenger.Shore;
			pchar.quest.Marginpassenger.function = "Marginpassenger_Southshore";
		break;
		
		case "Marginpassenger_offer_2":
			DialogExit();
			AddQuestRecord("Marginpassenger", "16");
			AddQuestUserData("Marginpassenger", "sCity", XI_ConvertString("Colony"+pchar.GenQuest.Marginpassenger.Southcity+"Gen"));
			AddQuestUserData("Marginpassenger", "sCity1", XI_ConvertString("Colony"+pchar.GenQuest.Marginpassenger.Southcity1+"Acc")); // лесник - окончание в СЖ
			AddQuestUserData("Marginpassenger", "sShipName", pchar.GenQuest.Marginpassenger.ShipName1);
			SetFunctionTimerCondition("Marginpassenger_SouthshipInWorld", 0, 0, 5+rand(2), false);
		break;
		
//---------------------------------------попытка залезть в сундуки --------------------------------------------
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("Грабёж среди бела дня!!! Это что же такое делается?! Ну, погоди, "+ GetSexPhrase("приятель","подруга") +"...", "Эй, ты чего это там копаешься?! Никак, вздумал"+ GetSexPhrase("","а") +" ограбить меня? Ну, тогда тебе конец...", "Постой, ты куда это полез"+ GetSexPhrase("","ла") +"? Да ты вор"+ GetSexPhrase("","овка") +", оказывается! Ну, считай, что ты приплыл"+ GetSexPhrase("","а") +", родн"+ GetSexPhrase("ой","ая") +"...");
			link.l1 = LinkRandPhrase("Дьявол!!", "Каррамба!!", "А-ать, черт!");
			link.l1.go = "PL_Q3_fight";
		break;
					
// ----------------------------------------------блок нод angry--------------------------------------------------
		case "AngryRepeat_1":
            dialog.text = RandPhraseSimple(""+ GetSexPhrase("Пошёл вон","Убирайся") +" отсюда!", "Вон из моего дома!");
			link.l1 = "Ай...";
		    link.l1.go = "AngryExitAgainWithOut";
            if (CheckAttribute(npchar, "angry.terms")) //примиряемся через 10 дней.
            {
                if (GetNpcQuestPastDayParam(npchar, "angry.terms") > sti(npchar.angry.terms))
                {
         			dialog.text = "Тебе не стоит отвлекать меня от дела пустыми обращениями. Впредь результат может быть более плачевным...";
        			link.l1 = "Я понял"+ GetSexPhrase("","а") +".";
        			link.l1.go = NextDiag.TempNode;
        			CharacterDelAngry(npchar);
                }
            }
    	break;
		case "AngryRepeat_2":
            dialog.text = RandPhraseSimple("Всё, никакого общения.", "Я не хочу с тобой общаться, так что тебе лучше меня не беспокоить.");
			link.l1 = RandPhraseSimple("Ну как знаешь...", "Хм, ну что же...");
		    link.l1.go = "AngryExitAgain";
            if (CheckAttribute(npchar, "angry.terms")) //примиряемся через 10 дней.
            {
                if (GetNpcQuestPastDayParam(npchar, "angry.terms") > sti(npchar.angry.terms))
                {
         			dialog.text = "Надеюсь, ты тоже будешь проявлять уважение в мой адрес, и не станешь более хамить?";
        			link.l1 = "Жак, ты можешь быть уверен - не буду...";
        			link.l1.go = NextDiag.TempNode;
        			CharacterDelAngry(npchar);
                }
            }
    	break;
		
		case "AngryExitAgain":
            DialogExit();
            DeleteAttribute(npchar, "angry.ok");
		break;
		
		case "AngryExitAgainWithOut":
            DialogExit();
            DeleteAttribute(npchar, "angry.ok");
            DoReloadCharacterToLocation("LeFransua_town","reload","reload6");
		break;
		
		case "pirate_town":
            dialog.text = "Решить проблему? Да ты сам понимаешь, чего ты наворотил? В общем, принесёшь мне миллион песо - я уговорю ребят, чтобы они забыли твои 'подвиги'. Нет - можешь катиться на все четыре стороны.";
			if (sti(Pchar.money) >= 1000000)
			{
				link.l1 = "Хорошо, я готов заплатить.";
				link.l1.go = "pirate_town_pay";
			}
			link.l2 = "Я всё понял. Ухожу.";
			link.l2.go = "pirate_town_exit";
		break;
		
		case "pirate_town_exit":
			DialogExit();
            bDisableFastReload = true;//закрыть переход
			pchar.quest.pirate_in_town.win_condition.l1 = "ExitFromLocation";
			pchar.quest.pirate_in_town.win_condition.l1.location = pchar.location;
			pchar.quest.pirate_in_town.function = "TownPirate_battle";
		break;
		
		case "pirate_town_pay":
            dialog.text = "Вот и славно! Считай, что свою репутацию ты восстановил. Но впредь, я надеюсь, ты больше не будешь делать таких мерзостей.";
			link.l1 = "Не буду. Уж очень дорого они обходятся. Прощай...";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, -1000000);
			pchar.GenQuest.Piratekill = 0;
		break;
	}
}

void SelectSouthshore()
{
	switch (rand(6))
	{
		case 0: pchar.GenQuest.Marginpassenger.Shore = "shore37"; break;
		case 1: pchar.GenQuest.Marginpassenger.Shore = "shore47"; break;
		case 2: pchar.GenQuest.Marginpassenger.Shore = "shore48"; break;
		case 3: pchar.GenQuest.Marginpassenger.Shore = "shore25"; break;
		case 4: pchar.GenQuest.Marginpassenger.Shore = "shore21"; break;
		case 5: pchar.GenQuest.Marginpassenger.Shore = "shore20"; break;
		case 6: pchar.GenQuest.Marginpassenger.Shore = "shore19"; break;
	}
}

void SelectSouthcity()
{
	switch (drand(2))
	{
		case 0: 
			pchar.GenQuest.Marginpassenger.Southcity = "Maracaibo";
			pchar.GenQuest.Marginpassenger.Southcity1 = "Havana"; 
		break;
		
		case 1:
			pchar.GenQuest.Marginpassenger.Southcity = "Cartahena";
			pchar.GenQuest.Marginpassenger.Southcity1 = "Santiago"; 
		break;
		
		case 2:
			pchar.GenQuest.Marginpassenger.Southcity = "Portobello";
			pchar.GenQuest.Marginpassenger.Southcity1 = "Santodomingo"; 
		break;
	}
}
