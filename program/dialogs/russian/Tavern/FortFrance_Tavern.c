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
			//--> Jason, Бремя гасконца
			if (!CheckAttribute(npchar, "quest.Rum") && CheckAttribute(pchar, "questTemp.Sharlie.Lock") && pchar.questTemp.Sharlie == "ship" && makeint(environment.time) > 5.0 && makeint(environment.time) < 19.0)
			{
				link.l1 = "Месье, я ищу работу. Может, у вас есть какое-нибудь поручение, которое вы смогли бы поручить мне?";
                link.l1.go = "Sharlie_rum";
			}
			if (CheckAttribute(pchar, "questTemp.Sharlie.Rum") && pchar.questTemp.Sharlie.Rum == "regard")
			{
				link.l1 = "Я выполнил ваше задание. Баркас с ромом доставлен в бухту Ле Франсуа и передан вашим людям.";
                link.l1.go = "Sharlie_rum_5";
			}	
			//<-- Бремя гасконца
			
			//Jason, Португалец
			if (CheckAttribute(PChar, "questTemp.Portugal") && pchar.questTemp.Portugal == "ToMartinique" && !CheckAttribute(npchar, "quest.Portugal"))
			{
				link.l1 = "Мне нужно снять комнату у тебя на два-три дня - у меня на борту раненый, ему нужно отдохнуть и поправиться.";
				link.l1.go = "Portugal";
			}
			if (CheckAttribute(PChar, "questTemp.Portugal") && pchar.questTemp.Portugal == "MartiniqueGovernorEnd")
			{
				link.l1 = "Скажите, мой друг, которому я снял комнату, куда он уехал? Обещал дождаться меня, но комната пуста.";
				link.l1.go = "Portugal_2";
			}
			//Португалец
			// Jason Долго и счастливо
			if (!CheckAttribute(npchar, "quest.LongHappy") && CheckAttribute(PChar, "questTemp.LongHappy.MarryRum") && LongHappy_CheckTavernGoods())
			{
				link.l1 = "Я собираюсь устроить небольшой сабантуй для своих ребят. Полагаю, вы уже в курсе?";
				link.l1.go = "LH_tavern_SP";
			}
			if (CheckAttribute(npchar, "quest.LongHappy.Nomoney") && LongHappy_CheckTavernGoods() && sti(Pchar.money) >= 100000+sti(pchar.questTemp.LongHappy.MarryMoney))
			{
				link.l1 = "Я принёс всё необходимое для моего праздника.";
				link.l1.go = "LH_tavern_SP_3";
			}
		break;
		
		//--> Jason, Бремя гасконца
		case "Sharlie_rum":
			dialog.text = "Поручение? Хм... Вы выглядите сообразительным молодым человеком. И можете вполне подойти... есть у меня одно дельце. Оно на первый взгляд несложное, но требует ответственности и главное - наличия мозгов в черепной коробке\nПотому что доверить переговоры этим болванам - значит, заранее обречь всё на провал...";
			link.l1 = "Послушайте, расскажите, наконец, толком, что за дело вы хотите мне доверить? Клянусь, я не подведу, ну уж во всяком случае - постараюсь.";
			link.l1.go = "Sharlie_rum_1";
		break;
		
		case "Sharlie_rum_1":
			switch(rand(4))
			{
				case 0:
					pchar.questTemp.Sharlie.Rum.Pass = "старый Томас заждался пива";
				break;
				case 1:
					pchar.questTemp.Sharlie.Rum.Pass = "доски и пакля будут утром";
				break;
				case 2:
					pchar.questTemp.Sharlie.Rum.Pass = "не стоит ждать южного ветра";
				break;
				case 3:
					pchar.questTemp.Sharlie.Rum.Pass = "бухта готова для высадки";
				break;
				case 4:
					pchar.questTemp.Sharlie.Rum.Pass = "верблюды идут на север";
				break;
			}
			dialog.text = "Хорошо. Задача такова: мне нужно доставить в мою таверну несколько ящиков элитного ямайского рома в обход портовых чиновников. Уж больно высокие поборы они накладывают на ввоз этого товара, а спрос на него среди моих лучших клиентов весьма и весьма велик\nСегодня вечером к берегам Мартиники в районе пляжа Ламантен подойдёт судно, люггер под названием 'Призрак'. Вам нужно будет найти это судно и подняться к нему на борт\nДля этой цели в вашем распоряжении будет баркас с пятью матросами на борту. Они будут вести лодку, куда скажете. После того, как окажетесь на палубе, к вам подойдет человек. Вам нужно сказать ему пароль: '"+pchar.questTemp.Sharlie.Rum.Pass+"'\nЕсли скажете неправильно или будете молчать, вас просто вышвырнут за борт и сделка не состоится. Поэтому я и не могу доверить это дело безмоглым тупицам, которые поплывут с вами. Повторите пароль.";
			link.l1 = "'"+pchar.questTemp.Sharlie.Rum.Pass+"'.";
			link.l1.go = "Sharlie_rum_2";
		break;
		
		case "Sharlie_rum_2":
			dialog.text = "Отлично. Повторите его себе ещё несколько раз, а лучше - запишите где-нибудь. Отзыв на пароль - 'выпей рому, моряк'. После этого на баркас будут перегружены ящики с бутылками рома, которые нужно доставить в бухту пиратского поселения Ле Франсуа - вас там встретят\nВот и вся задача. Из бухты Ле Франсуа до Сен-Пьера доберётесь пешком - баркас останется в бухте. Если вам ещё не стало страшно и вы готовы выполнить это задание, то по завершении я заплачу вам пять тысяч песо.";
			link.l1 = "С чего это вы решили, что мне должно стать страшно? Я сделаю, что вы говорите. Где баркас?";
			link.l1.go = "Sharlie_rum_3";
			link.l2 = "То есть вы предлагаете мне заняться контрабандой? Гм... Знаете, я не могу рисковать своим именем. Прошу меня извинить, будем считать, что я ничего не слышал.";
			link.l2.go = "Sharlie_rum_exit";
		break;
		
		case "Sharlie_rum_exit":
			dialog.text = "Как знаете, месье. Иных поручений у меня нет.";
			link.l1 = "Понятно. Тогда всего доброго, "+npchar.name+".";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.Sharlie.Rum");
		break;
		
		case "Sharlie_rum_3":
			dialog.text = "Баркас будет у пирса, который ближе к верфи, в семь вечера. Не опаздывайте - до пляжа Ламантен не менее пяти-шести часов пути, а 'Призрак' будет ждать вас только до пяти утра. Да, и возьмите для облегчения поисков вот эту подзорную трубу. Она, конечно, дрянь-дрянью, но лучше, чем ничего. Пляж Ламантен находится на северной оконечности острова, так что выйдя из порта держите курс на север. И не забудьте пароль!";
			link.l1 = "Я помню. До встречи, "+npchar.name+"!";
			link.l1.go = "Sharlie_rum_4";
		break;
		
		case "Sharlie_rum_4":
			DialogExit();
			AddQuestRecord("SharlieB", "1");
			GiveItem2Character(pchar, "spyglass1"); 
			Log_Info("Вы получили подзорную трубу");
			PlaySound("interface\important_item.wav");
			pchar.quest.Sharlie_rum.win_condition.l1 = "locator";
			pchar.quest.Sharlie_rum.win_condition.l1.location = "Fortfrance_town";
			pchar.quest.Sharlie_rum.win_condition.l1.locator_group = "rld";
			pchar.quest.Sharlie_rum.win_condition.l1.locator = "loc0";
			pchar.quest.Sharlie_rum.win_condition.l2 = "HardHour";
			pchar.quest.Sharlie_rum.win_condition.l2.hour = 19.00;
			pchar.quest.Sharlie_rum.function = "Rum_CreateBarkas";
			SetFunctionTimerCondition("Rum_CreateBarkasOver", 0, 0, 1, false);
			pchar.questTemp.Sharlie.Rum = "true";
			npchar.quest.Rum = "true";
		break;
		
		case "Sharlie_rum_5":
			dialog.text = "Замечательно! Я знал, что на вас можно положиться. Это было трудно?";
			link.l1 = "Ну, это как посмотреть...";
			link.l1.go = "Sharlie_rum_6";
		break;
		
		case "Sharlie_rum_6":
			dialog.text = "Вот ваша награда - пять тысяч. Подзорную трубу оставьте себе. И ещё маленький презент - возьмите эти три бутылки рома. После того, как вы его попробуете, вы сразу поймёте, почему на него такой спрос.";
			link.l1 = "Спасибо! Было приятно с вами работать! До встречи!";
			link.l1.go = "Sharlie_rum_7";
		break;
		
		case "Sharlie_rum_7":
			DialogExit();
			AddMoneyToCharacter(pchar, 5000);
			TakeNItems(pchar, "potionrum", 3);
			AddQuestRecord("SharlieB", "5");
			CloseQuestHeader("SharlieB");
			DeleteAttribute(pchar, "questTemp.Sharlie.Rum");
		break;
		//<-- Бремя гасконца
		
		//Португалец
		case "Portugal":
			dialog.text = "Да без проблем, есть у меня комната. Платите 50 песо - и на три дня она ваша.";
			if (sti(pchar.money) >= 50)
			{
				link.l1 = "Вот, держи.";
				link.l1.go = "Portugal_1";
			}
			else
			{
				link.l1 = "Сейчас возьму у казначея деньги и вернусь.";
				link.l1.go = "exit";
			}
		break;
		
		case "Portugal_1":
			ref sld;
			DialogExit();
			AddMoneyToCharacter(pchar, -50);
			npchar.quest.Portugal = "true";
			LocatorReloadEnterDisable("Fortfrance_tavern", "reload2_back", false);
			pchar.quest.Portugal_Ill3.over = "yes";
			LocatorReloadEnterDisable("Fortfrance_town", "reload1_back", true);
			LocatorReloadEnterDisable("Fortfrance_town", "reload2_back", true);
			LocatorReloadEnterDisable("Fortfrance_town", "gate_back", true);//закрыть выходы из города
			sld = characterFromId("Portugal");
			ChangeCharacterAddressGroup(sld, "FortFrance_tavern_upstairs", "goto", "goto3");
			sld = characterFromId("PortugalDoctor");
			ChangeCharacterAddressGroup(sld, "FortFrance_tavern_upstairs", "goto", "goto1");
			pchar.quest.Portugal_tavernroom.win_condition.l1 = "location";
			pchar.quest.Portugal_tavernroom.win_condition.l1.location = "FortFrance_tavern_upstairs";
			pchar.quest.Portugal_tavernroom.function = "PortugalInTavernRoom";
		break;
		
		case "Portugal_2":
			dialog.text = "Не сказал бы, что он прямо сам уехал, мсье. Вчера сюда пришли какие-то люди, с ними были такой одноглазый верзила – ну чисто бандит с виду, и шепелявый тип, похожий на кастильца. Я удивился было, но этот шепелявый так на меня глянул... ну чисто на вошь, перед тем как раздавить. И спрашивали, значит, про вашего друга... ну, я и сказал – а что мне делать было?";
			link.l1 = "Знаю, " + npchar.name + ", ты не герой, и правильно. Что ты ещё видел? Куда они направились?";
			link.l1.go = "Portugal_3";
		break;
		
		case "Portugal_3":
			dialog.text = "Да вроде ничего больше... хотя, нет! Постойте, одноглазый говорил что-то про повозку. Вроде как повозку они наняли, вашего друга куда-то на другую сторону острова везти. Вот и все, клянусь мсье... я бы стражу вызвал, но этот шепелявый на прощание сказал, что у меня красивая жена... Понимаете? Если они узнают, что я вам всё рассказал, они же её...";
			if (pchar.money >= 1000)
			{
				link.l1 = "Не бойся, от меня им точно ничего, кроме пули, не получить. Ты мне очень помог, спасибо. Вот, возьми 1000 песо.";
				link.l1.go = "Portugal_4";
			}
			link.l2 = "Не много, но спасибо и на том. В следующий раз зови стражу и не будь таким тюфяком.";
			link.l2.go = "Portugal_5";
		break;
		
		case "Portugal_4":
			AddMoneyToCharacter(pchar, -1000);
			dialog.text = "Спасибо, мсье. Ваш друг, к слову, он почти поправился, во всяком случае, шёл сам. А второй человек - ну, этот тихий голландец, он как раз заходил с улицы, заприметил эту свору и сиганул наружу, только его и видели.";
			link.l1 = "Полагаю, он уже отплыл на первом попавшемся судне. Благодарю за информацию, мне пора.";
			link.l1.go = "Portugal_6";
		break;
		
		case "Portugal_5":
			dialog.text = "Не всем же быть героями с саблей наголо, капитан.";
			link.l1 = "Ну-ну... каждый выбирает сам.";
			link.l1.go = "Portugal_6";
		break;
		
		case "Portugal_6":
			DialogExit();
			sld = characterFromId("Avendel");
			sld.dialog.currentnode = "Avendel_seapatrol_9";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		//Португалец
		
		// Jason Долго и счастливо
		case "LH_tavern_SP":
			npchar.quest.LongHappy = "true";
			dialog.text = "Да, ваша помощница забегала, но я сказал ей и повторю вам - мне не привыкать к толпам пьяных моряков и я знаю чем это чревато. То что здесь останется к утру будет напоминать Рим, после захвата Карлом V. Хорошо, если сама таверна устоит. Так что, если хотите утроить массовый дебош - мне потребуется невозвратный залог сверх того, что вы уже принесли. На случай последствий, так сказать.";
			link.l1 = "Ну и хитрый ты лис! Я сам не первый год пью с морскими волками, бывал в разных... заведениях, и знаю, что за те деньги, что я принёс, такой портовый притон можно отстроить заново с фундамента. Пользуешься поводом, так? Ладно, у меня свадьба, и я не настроен мелочиться - сколько ты хочешь сверху?";
			link.l1.go = "LH_tavern_SP_1";
		break;
		
		case "LH_tavern_SP_1":
			dialog.text = "Ещё ста тысяч должно хватить и не переживайте - сделаю всё в лучшем виде. Ваши парни надолго запомнят эту гулянку, попомните моё слово!";
			if (sti(Pchar.money) >= 100000+sti(pchar.questTemp.LongHappy.MarryMoney))
			{
				link.l1 = "Ты уж постарайся - повод особенный, сам понимаешь. И да, потом не приходи ко мне с жалобами, даже если твой трактир сгорит дотла.";
				link.l1.go = "LH_tavern_SP_4";
			}
			else
			{
				link.l1 = "Да я будто графский приём заказываю! Потерпи, я скоро вернусь.";
				link.l1.go = "LH_tavern_SP_2";
			}
		break;
		
		case "LH_tavern_SP_2":
			DialogExit();
			npchar.quest.LongHappy.Nomoney = "true";
		break;
		
		case "LH_tavern_SP_3":
			dialog.text = "Отлично! Ваши парни не скоро забудут эту гулянку, попомните моё слово!";
			link.l1 = "Ты уж постарайся - повод особенный, сам понимаешь. И да, потом не приходи ко мне с жалобами, даже если твой трактир сгорит дотла.";
			link.l1.go = "LH_tavern_SP_4";
		break;
		
		case "LH_tavern_SP_4":
			DialogExit();
			RemoveCharacterGoods(pchar, GOOD_RUM, sti(pchar.questTemp.LongHappy.MarryRum));
			AddMoneyToCharacter(pchar, -sti(pchar.questTemp.LongHappy.MarryMoney));
			AddMoneyToCharacter(pchar, -100000);
			DeleteAttribute(npchar, "quest.LongHappy.Nomoney");
			pchar.questTemp.LongHappy.DrinkReady = "true";
			pchar.questTemp.LongHappy.MarrySP = "true";
			DeleteAttribute(pchar, "questTemp.LongHappy.MarryMoney");
			DeleteAttribute(pchar, "questTemp.LongHappy.MarryRum");
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}