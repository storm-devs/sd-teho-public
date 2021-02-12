// Addon-2016 Jason, французские миниквесты (ФМК) Гваделупа
void ProcessDialogEvent()
{
	ref sld, NPChar;
	aref Link, NextDiag;
	int i;
	string sTemp;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "Явный баг. Сообщите Jason'у, как и при каких обстоятельствах его получили.";
			link.l1 = "Обязательно сообщу!";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
		// квестодатель
		case "citizen":
			dialog.text = "Приветствую, капитан! У меня к вам деловое предложение, которое должно вас заинтересовать.";
			link.l1 = "Внимательно вас слушаю, месье.";
			link.l1.go = "citizen_1";
		break;
		
		case "citizen_1":
			dialog.text = "Я хочу зафрахтовать ваше судно для перехода с Гваделупы на испанский Мэйн.";
			link.l1 = "Вас нужно доставить на испанский Мэйн как пассажира?";
			link.l1.go = "citizen_2";
			link.l2 = "Испанский Мэйн? Увольте. Мы с испанцами как-то не сильно дружим. Думаю, вам следует поискать другое судно.";
			link.l2.go = "citizen_no";
		break;
		
		case "citizen_no":
			dialog.text = "Как скажете, капитан, хотя риск в этом путешествии был невелик. Всего доброго!";
			link.l1 = "До свидания.";
			link.l1.go = "citizen_exit";
		break;
		
		case "citizen_no_1":
			dialog.text = "Как знаете, капитан. Всего доброго!";
			link.l1 = "До свидания.";
			link.l1.go = "citizen_exit";
		break;
		
		case "citizen_exit":
			DialogExit();
			chrDisableReloadToLocation = false;
			npchar.lifeday = 0;
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload4_back", "none", "", "", "", 20.0);
		break;
		
		case "citizen_2":
			dialog.text = "Не совсем так, месье. Пассажир - лицо, зависящее от прихотей своего капитана, а я хочу зафрахтовать, то есть - нанять вас, вашу команду и ваше судно для доставки меня и двух моих друзей в Панаму. Оплата, естественно, будет щедрой.";
			link.l1 = "В Панаму? Это как? Обогнуть материк?";
			link.l1.go = "citizen_3";
		break;
		
		case "citizen_3":
			dialog.text = "Шутите, капитан. Нет, конечно. Вам всего лишь надо будет высадить нас в заливе Москитос, что недалеко от Порто-Белло, а уж до Панамы мы сами доберёмся, чай, не первый раз в джунглях бываем.";
			link.l1 = "Каков размер оплаты?";
			link.l1.go = "citizen_4";
		break;
		
		case "citizen_4":
			dialog.text = "Два сундучка с дублонами. Три сотни штук. Один - авансом, когда мы поднимемся на борт, второй - по прибытии на место.";
			link.l1 = "Это высокая цена за столь простую работу. Нет ли здесь подвоха, а, милейший?";
			link.l1.go = "citizen_5";
		break;
		
		case "citizen_5":
			dialog.text = "Капитан, время - деньги, а у меня и моих друзей его нет. Нам нужно отбыть немедленно, сегодня же вечером, и прибыть на место не позднее, чем за десять дней. Это второе условие. Итак, вы согласны?";
			link.l1 = "По рукам!";
			link.l1.go = "citizen_6";
			link.l2 = "Извините, месье, но ваше предложение выглядит каким-то подозрительным и меня не устраивает. Подыщите себе другое судно.";
			link.l2.go = "citizen_no_1";
		break;
		
		case "citizen_6":
			dialog.text = "Отлично. Мои друзья сейчас находятся в джунглях, я извещу их о вашем согласии, мы выйдем на пляж Капстер, где вы нас и заберёте. Думаю, мы доберёмся до побережья сегодня к вечеру, часам к десяти. Не опаздывайте, капитан!";
			link.l1 = "Хорошо. Сегодня к десяти вечера на пляже Капстер.";
			link.l1.go = "citizen_7";
		break;
		
		case "citizen_7":
			dialog.text = "Минутку, капитан, мы даже не представились друг другу. Моё имя - Бертран Пинетт. А вы...";
			link.l1 = "Капитан "+GetFullName(pchar)+". До встречи, месье Пинетт.";
			link.l1.go = "citizen_8";
		break;
		
		case "citizen_8":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "gate_back", "none", "", "", "OpenTheDoors", 20.0);
			AddQuestRecord("FMQ_Guadeloupe", "1");
			pchar.quest.FMQG_Capster.win_condition.l1 = "Hour";
			pchar.quest.FMQG_Capster.win_condition.l1.start.hour = 22.00;
			pchar.quest.FMQG_Capster.win_condition.l1.finish.hour = 23.99;
			pchar.quest.FMQG_Capster.win_condition.l2 = "Ship_location";
			pchar.quest.FMQG_Capster.win_condition.l2.location = "Shore29";
			pchar.quest.FMQG_Capster.win_condition.l3 = "location";
			pchar.quest.FMQG_Capster.win_condition.l3.location = "Shore29";
			pchar.quest.FMQG_Capster.function = "FMQG_CapsterBeach";
			SetFunctionTimerCondition("FMQG_StartLate", 0, 0, 1, false);
			pchar.questTemp.FMQG = "begin";
			pchar.GenQuest.SmugglersBlock = "baster_tavern";
		break;
		
		case "citizen_9":
			dialog.text = "Вот и вы, капитан "+GetFullName(pchar)+". Мы с друзьями можем садиться в шлюпку?";
			link.l1 = "Да. Добро пожаловать на борт.";
			link.l1.go = "citizen_10";
		break;
		
		case "citizen_10":
			dialog.text = "Очень хорошо. Примите ваш аванс - сундучок с дублонами. И помните - нам надо добраться до места за десять дней, не позже!";
			link.l1 = "Я помню. Не волнуйтесь, прибудем в срок. Занимайте места в шлюпке.";
			link.l1.go = "citizen_11";
		break;
		
		case "citizen_11":
			DialogExit();
			GiveItem2Character(pchar, "chest");
			log_info("Вы получили сундук с дублонами");
			PlaySound("interface\important_item.wav");
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "officers", "sea_1", "none", "", "", "FMQG_OnBoard", 20.0);
			for (i=2; i<=3; i++)
			{
				sld = characterFromId("FMQG_pass_"+i);
				LAi_ActorRunToLocation(sld, "officers", "sea_"+i, "none", "", "", "", 10.0);
			}
			pchar.quest.FMQG_SailStart.win_condition.l1 = "location";
			pchar.quest.FMQG_SailStart.win_condition.l1.location = "Guadeloupe";
			pchar.quest.FMQG_SailStart.function = "FMQG_SailingStart";
			SetFunctionTimerCondition("FMQG_SailingLate", 0, 0, 10, false);
			SetFunctionTimerCondition("FMQG_MutiniActivate", 0, 0, 20, false);
			pchar.questTemp.FMQG = "sail";
			DeleteAttribute(pchar, "GenQuest.SmugglersBlock");
		break;
		
		case "citizen_12":
			dialog.text = "Итак, капитан, вы полностью выполнили свои обязательства. Примите вторую часть оплаты и наши благодарности.";
			link.l1 = "Приятно было иметь с вами дело, месье.";
			link.l1.go = "citizen_13";
		break;
		
		case "citizen_13":
			GiveItem2Character(pchar, "chest");
			log_info("Вы получили сундук с дублонами");
			PlaySound("interface\important_item.wav");
			AddCharacterExpToSkill(pchar, "Sailing", 200);//навигация
			AddCharacterExpToSkill(pchar, "Leadership", 200);//авторитет
			AddCharacterExpToSkill(pchar, "Sneak", 100);//скрытность
			dialog.text = "Нам с вами тоже. Всего доброго, капитан "+GetFullName(pchar)+".";
			link.l1 = "До свидания!";
			link.l1.go = "citizen_14";
		break;
		
		case "citizen_14":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "OpenTheDoors", 20.0);
			for (i=2; i<=3; i++)
			{
				sld = characterFromId("FMQG_pass_"+i);
				LAi_ActorRunToLocation(sld, "reload", "reload1_back", "none", "", "", "", 10.0);
				sld.lifeday = 0;
			}
			AddQuestRecord("FMQ_Guadeloupe", "6");
			CloseQuestHeader("FMQ_Guadeloupe");
			pchar.questTemp.FMQG = "pause";
			pchar.quest.FMQG_Continue.win_condition.l1 = "Ship_location";
			pchar.quest.FMQG_Continue.win_condition.l1.location = "Baster_town";
			pchar.quest.FMQG_Continue.win_condition.l2 = "location";
			pchar.quest.FMQG_Continue.win_condition.l2.location = "Baster_town";
			pchar.quest.FMQG_Continue.function = "FMQG_BasterContinue";
			pchar.quest.FMQG_Block1.win_condition.l1 = "Rank";
			pchar.quest.FMQG_Block1.win_condition.l1.value = 13;
			pchar.quest.FMQG_Block1.win_condition.l1.operation = ">=";
			pchar.quest.FMQG_Block1.function = "FMQG_Block";
			SetFunctionTimerCondition("FMQG_Block", 0, 0, 90, false);
		break;
		
		case "citizen_12a":
			dialog.text = "Итак, капитан, мы на месте. Но вы выполнили только половину своих обязательств - не соблюдены оговорённые сроки. Поэтому мы тоже выполним ровно половину своих обязательств об оплате и ограничимся уже полученным вами авансом. Надеюсь, возражений с вашей стороны не последует - ведь вы нарушили наш договор.";
			link.l1 = "Не могу сказать, что я в восторге, но признаю: вы правы. На этом и разойдёмся.";
			link.l1.go = "citizen_13a";
		break;
		
		case "citizen_13a":
			AddCharacterExpToSkill(pchar, "Sailing", 50);//навигация
			AddCharacterExpToSkill(pchar, "Leadership", 50);//авторитет
			AddCharacterExpToSkill(pchar, "Sneak", 50);//скрытность
			dialog.text = "И всё равно спасибо за оказанную услугу, капитан "+GetFullName(pchar)+". Всего доброго!";
			link.l1 = "До свидания.";
			link.l1.go = "citizen_14";
		break;
		
		case "citizen_15":
			dialog.text = "О! Какая неожиданная встреча! "+TimeGreeting()+", "+GetFullName(pchar)+"! Какими судьбами?";
			link.l1 = TimeGreeting()+", месье Пинетт. Я уже с ног сбился, вас искавши.";
			link.l1.go = "citizen_16";
		break;
		
		case "citizen_16":
			sld = characterFromId("Baster_usurer");
			dialog.text = "И в чём же причина такой спешки, капитан?";
			link.l1 = "Вас, милейший, крайне жаждет видеть месье "+GetFullName(sld)+". Я полагаю, вы понимаете, зачем и почему.";
			link.l1.go = "citizen_17";
		break;
		
		case "citizen_17":
			sld = characterFromId("Baster_usurer");
			dialog.text = "Конечно, понимаю, но и вы, уважаемый капитан, должны так же понимать, что я совершенно не жажду увидеть месье "+GetFullName(sld)+", как он того желает. Неужели он нашёл в вашем лице охотника за головами? Я просто в это не верю.";
			link.l1 = "Увы, но это так, хотя я и не рад этому. Я имел неосторожность сболтнуть лишнего, и милейший месье "+GetFullName(sld)+", поглоти его акула, припёр меня к стенке: или вы, Бертран Пинетт, на Гваделупе, или я иду как соучастник в вашей авантюре с побегом дона Карлоса де Мильяра. Чем для меня это чревато - думаю, объяснять не нужно.";
			link.l1.go = "citizen_18";
		break;
		
		case "citizen_18":
			sld = characterFromId("Baster_usurer");
			dialog.text = "Ах, какой же всё-таки негодяй, этот месье "+GetFullName(sld)+"! Так бесчестно шантажировать людей!.. Итак, капитан, что же вы намерены сделать?";
			link.l1 = "А вы как думаете? Полагаю, вам придётся отправиться со мной в Бас-Тер.";
			link.l1.go = "citizen_19";
			link.l2 = "А вы считаете, у меня есть какой-то выбор?";
			link.l2.go = "citizen_25";
		break;
		
		case "citizen_19":
			dialog.text = "Ох, я вынужден вас огорчить, месье капитан. У меня нет ни малейшего желания подниматься на борт вашего прекрасного судна. Силой вы ничего не добьетесь - кругом охрана, и в случае проявления агрессии с вашей стороны, я начну кричать. Вы, конечно, можете попытаться проткнуть меня вашей шпагой, однако скряге-ростовщику мой труп вовсе ни к чему - денег с него не истребуешь. Так что самым разумным поступком с вашей стороны будет просто покинуть этот дом и оставить меня в покое. Я не буду поднимать шум и дам вам спокойно уйти.";
			link.l1 = "И ты считаешь, что я сейчас просто развернусь и уйду после всего, что произошло? Ты втянул меня в эту историю, мерзавец, и тебе не поздоровится!";
			link.l1.go = "citizen_20";
			link.l2 = "Пожалуй, вы правы. Убить вас, конечно, было бы неплохо, но действительно в этом нет смысла, и проблем не оберешься. Но вы не думайте, что я так всё оставлю. Я сейчас же выхожу в море, отправляюсь в Бас-Тер и расскажу ростовщику, где вы прячетесь. А он уже пришлёт за вами людей в чёрных костюмах с полумасками на лицах.";
			link.l2.go = "citizen_21";
		break;
		
		case "citizen_20":
			dialog.text = "А-а! Солдаты! На помощь! Убивают!!";
			link.l1 = "...";
			link.l1.go = "citizen_fight";
		break;
		
		case "citizen_21":
			dialog.text = "Да-да, милейший, и не забудьте передать вашему патрону, чтобы его люди в масках записывались в очередь - желающих и так немало. Всего доброго, капитан.";
			link.l1 = "...";
			link.l1.go = "citizen_22";
		break;
		
		case "citizen_22":
			DialogExit();
			LAi_SetActorType(npchar);
			AddQuestRecord("FMQ_Guadeloupe", "19");
			pchar.quest.FMQG_Mayak.win_condition.l1 = "location";
			pchar.quest.FMQG_Mayak.win_condition.l1.location = "Mayak2";
			pchar.quest.FMQG_Mayak.function = "FMQG_Lighthouse";
		break;
		
		case "citizen_23":
			dialog.text = "Стой! Я сдаюсь! Сдаюсь!";
			link.l1 = "То-то же! А теперь брось оружие и живо марш на корабль!";
			link.l1.go = "citizen_24";
		break;
		
		case "citizen_24":
			DialogExit();
			chrDisableReloadToLocation = false;
			RemoveAllCharacterItems(npchar, true);
			DoQuestReloadToLocation("Mayak2", "goto", "goto1", "FMQG_OnLighthouse");
		break;
		
		case "citizen_25":
			dialog.text = "Выбор есть всегда, капитан. Я так понял, что не будь вам угрозы со стороны ростовщика, вы бы не стали меня разыскивать?";
			link.l1 = "Именно.";
			link.l1.go = "citizen_26";
		break;
		
		case "citizen_26":
			dialog.text = "Отлично. Тогда я организую вам безотказный способ заткнуть ему рот. Сейчас напишем одно письмецо, а вы отвезёте его вашему 'работодателю' и передадите на словах, что если он развяжет варежку, то губернатор Гваделупы узнает, кто являлся идейным и финансовым вдохновителем одной 'операции', в результате которой без вести пропал курьерский люггер 'Куражю', перевозивший крупную партию гранёных алмазов.";
			link.l1 = "Кхм. Кажется, я вас понял, месье Пинетт.";
			link.l1.go = "citizen_27";
		break;
		
		case "citizen_27":
			dialog.text = "Рад, что вы такой сообразительный, месье капитан. Клод Франсуа де Лион лично прибьёт голову этого хитрого скупердяя к городским воротам, если узнает всю правду о пропавшем 'Куражю'. В письме, которое я вам сейчас напишу, будут доказательства, которые утопят вашего шантажиста. Погодите минутку, я возьму перо и бумагу.";
			link.l1 = "Хорошо...";
			link.l1.go = "citizen_28";
		break;
		
		case "citizen_28":
			LAi_Fade("", "");
			GiveItem2Character(pchar, "letter_baker");
			ChangeItemDescribe("letter_baker", "itmdescr_letter_pinett");
			dialog.text = "(пишет) Вот, держите. Здесь в конверте два одинаковых экземпляра. Один отдайте ростовщику, пусть полюбуется, а второй держите в надёжном месте.";
			link.l1 = "Информация достоверная?";
			link.l1.go = "citizen_29";
		break;
		
		case "citizen_29":
			sld = characterFromId("Baster_usurer");
			dialog.text = "Клянусь вам. Будьте спокойны - прочитав эти показания, месье "+GetFullName(sld)+" отстанет от вас навсегда. Да, и ещё, капитан: раз мы решили дело полюбовно... мне всё равно путь на Гваделупу заказан, и если вы пообещаете мне, что более не станете даже пытаться чинить мне козни, я расскажу вам про мой маленький схрон, который я не успел забрать и уже не заберу.";
			link.l1 = "Если ваше письмо отобьёт охоту у ростовщика угрожать мне - то обещаю, что забуду о вашем существовании.";
			link.l1.go = "citizen_30";
		break;
		
		case "citizen_30":
			dialog.text = "Договорились. Поищите хорошенько в пещере Гваделупы среди камней. Это будет вам небольшой компенсацией за перенесённые тяготы. Попутного ветра, капитан.";
			link.l1 = "Всего доброго, месье Пинетт.";
			link.l1.go = "citizen_31";
		break;
		
		case "citizen_31":
			DialogExit();
			pchar.questTemp.FMQG = "letter";
			AddQuestRecord("FMQ_Guadeloupe", "24");
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeday = 1;
		break;
		
		case "citizen_fight":
			chrDisableReloadToLocation = true;
			LAi_group_Delete("EnemyFight");
			DialogExit();
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "OpenTheDoors");
			AddDialogExitQuest("MainHeroFightModeOn");
			DoQuestFunctionDelay("FMQG_PlantationGuards", 3.0);
			pchar.questTemp.FMQG = "fail";
			AddQuestRecord("FMQ_Guadeloupe", "18");
			CloseQuestHeader("FMQ_Guadeloupe");
		break;
		
		// вестовой к ростовщику
		case "cureer":
			dialog.text = "Здравствуйте, месье! Ведь это вы - капитан "+GetFullName(pchar)+"?";
			link.l1 = "Да, это я. Чем обязан?";
			link.l1.go = "cureer_1";
		break;
		
		case "cureer_1":
			sld = characterFromId("BasTer_usurer");
			dialog.text = "Месье "+GetFullName(sld)+", владелец банка Бас-Тер, очень просит вас нанести ему визит, и как можно скорее. Он специально озадачил меня ежедневно справляться в портовом управлении о прибытии вашего судна, а затем - передать вам его приглашение.";
			link.l1 = "Очень интересно - и зачем же я ему понадобился?";
			link.l1.go = "cureer_2";
		break;
		
		case "cureer_2":
			dialog.text = "Об этом вам расскажет лично месье "+GetFullName(sld)+" при встрече. Надеюсь, вы не откажете ему в этой любезности.";
			link.l1 = "Гм... Хорошо. Ростовщики - народ влиятельный, и по пустякам беспокоить не станут. Я отправлюсь к нему по возможности скорее.";
			link.l1.go = "cureer_3";
		break;
		
		case "cureer_3":
			dialog.text = "Благодарю вас, капитан. До свидания!";
			link.l1 = "Всего доброго.";
			link.l1.go = "cureer_4";
		break;
		
		case "cureer_4":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload4_back", "none", "", "", "", 10.0);
			chrDisableReloadToLocation = false;
			LocatorReloadEnterDisable("Baster_town", "reload1_back", true);
			LocatorReloadEnterDisable("Baster_town", "reload2_back", true);
			LocatorReloadEnterDisable("Baster_town", "gate_back", true);//закрыть выходы из города
			pchar.questTemp.FMQG = "continue";
			pchar.quest.FMQG_Block.over = "yes";
			pchar.quest.FMQG_Block1.over = "yes";
		break;
		
		// Жан Дено
		case "Juan":
			dialog.text = "Аргх! Я узнал тебя, каналья! Не поверю, что это случайная встреча...";
			link.l1 = "Точно, Жан... пардон - дон Хуан. Я тебя выследил. А теперь добро пожаловать в трюм. После того, как ты слегка остынешь, мы с тобой побеседуем.";
			link.l1.go = "Juan_1";			
		break;
		
		case "Juan_1":
			DialogExit();
			Lai_SetPlayerType(pchar);
			DeleteAttribute(npchar, "DontRansackCaptain");
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", 3.0);
			pchar.questTemp.FMQG.Prisoner = GetFullName(npchar);
			pchar.GenQuest.LastQuestPrisonerIdx = SetCharToPrisoner(npchar);
			AddQuestRecord("FMQ_Guadeloupe", "14");
			pchar.questTemp.FMQG = "juan_capture";
			DoQuestCheckDelay("LAi_ReloadBoarding", 3.5);
		break;
		
		case "Juan_2":
			dialog.text = "";
			link.l1 = "Я выполнил свою часть сделки. Теперь твоя очередь. Выкладывай, и помни о том, что тебе угрожает, если надумаешь соврать.";
			link.l1.go = "Juan_3";
		break;
		
		case "Juan_3":
			dialog.text = "Ты найдёшь Бертрана Пинетта на Барбадосе, а точнее - на главной плантации. Он собирался продолжить свой бизнес именно там. Смотритель плантации - его дружок.";
			link.l1 = "Какого рода 'бизнес' планировал Пинетт?";
			link.l1.go = "Juan_4";
		break;
		
		case "Juan_4":
			dialog.text = "Да всё тот же, что и на Гваделупе. Полулегальная торговля, поиск и доставка дефицитных товаров, привоз рабов под заказ. Думаю, что сейчас он займётся работорговлей и продажей сахара - иначе с чего бы ему оседать на плантации?";
			link.l1 = "Понятно. У него есть покровители среди английских властей?";
			link.l1.go = "Juan_5";
		break;
		
		case "Juan_5":
			dialog.text = "Возможно. Это фрукт ещё тот. У него повсюду знакомства.";
			link.l1 = "Что ещё можешь сказать о нём?";
			link.l1.go = "Juan_6";
		break;
		
		case "Juan_6":
			dialog.text = "А что тут скажешь? Мутный и хитрый тип, много чего знает, всегда держит козырь в рукаве. Я не так долго с ним знаком был.";
			link.l1 = "Ясно. Ладно, тогда мне пора в Бриджтаун. Ступай, дон Хуан, да не вздумай Пинетту весточку послать, что я у него на хвосте. Если не найду Бертрана на Барбадосе - пеняй на себя. Бывай.";
			link.l1.go = "Juan_7";
		break;
		
		case "Juan_7":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "", 10.0);
			npchar.lifeday = 0;
			chrDisableReloadToLocation = false;
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			pchar.questTemp.FMQG = "headhunter_pinett";
			AddQuestRecord("FMQ_Guadeloupe", "17");
			// Пинетта - в Бриджтаун
			sld = characterFromId("FMQG_pass_1");
			ChangeCharacterAddressGroup(sld, "Plantation_F2", "goto", "goto1");
			sld.Dialog.currentnode = "citizen_15";
			LAi_SetStayType(sld);
		break;
		
		case "killer":
			dialog.text = "Приятель, ты извини - ничего личного. Твоя беда лишь в том, что ты слишком много знаешь...";
			link.l1 = "...";
			link.l1.go = "killer_1";
		break;
		
		case "killer_1":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false); // правки релиза
			LAi_group_Delete("EnemyFight");
			int n = 2;
			if (MOD_SKILL_ENEMY_RATE > 6) n = 3;
			for (i=1; i<=n; i++)
			{
				sld = characterFromId("FMQG_killer_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "FMQG_KillersDestroy");
			//AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
