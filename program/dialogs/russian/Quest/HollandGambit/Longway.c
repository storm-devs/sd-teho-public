// китаец Лонгвэй, подручный Роденбурга
void ProcessDialogEvent()
{
	ref NPChar, sld, rItm, rItem;
	aref Link, NextDiag, rType;
	int i;
	string 	sAttr, sGun, sBullet, attrL;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	sAttr = Dialog.CurrentNode;
	if (findsubstr(sAttr, "SetGunBullets1_" , 0) != -1)
 	{
        i = findsubstr(sAttr, "_" , 0);
	 	NPChar.SetGunBullets = strcut(sAttr, i + 1, strlen(sAttr) - 1); // индекс в конце
 	    Dialog.CurrentNode = "SetGunBullets2";
 	}
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "Здравствуйте, капитан. Моя зовут Лонгвэй. Лонгвэй предоставляет свой парусник в ваше распоряжение. Лонгвэй также поступает в ваше распоряжение. Приказ минхера Роденбурга.";
			link.l1 = "Понятно, минхер Лонгвэй. Рад вас приветствовать. Думаю, мы с вами сработаемся. Расскажите мне о цели нашего задания - где нам искать Якоба ван Берга?";
			link.l1.go = "Longway_neutral";
			link.l2 = "Ха, ну хоть раз в жизни взгляну на живого китайца... Вы назначены моим офицером, вижу, вы в курсе. Не переживайте, я буду аккуратен с вашим кораблем, и не буду заставлять вас нести ночные вахты и драить палубу, хе-хе - вы же, как-никак, капитан этого судна! Теперь расскажите мне о цели нашего задания - где нам искать Якоба ван Берга?";
			link.l2.go = "Longway_enemy";
			link.l3 = "Здравствуйте, минхер Лонгвэй. Мне, право, неудобно - вы, капитан великолепного судна, поступаете в мое распоряжение в качестве офицера... Это неправильно. В общем, я продолжаю вас по-прежнему считать не менее, чем капитаном этого корабля, а себя - временным гостем. Надеюсь, вы поможете мне во всем, что касается корабельных дел. Расскажите мне о цели нашего задания - где нам искать Якоба ван Берга?";
			link.l3.go = "Longway_friend";	
			NextDiag.TempNode = "First time";
			pchar.questTemp.HWIC.Holl.JacobCity = SelectJacobCity();
		break;
		
//-----------------------------------------------за Голландию-----------------------------------------------
		case "Longway_neutral":
			dialog.text = "Я уверен, Лонгвэй с вами сработается. Якоб ван Берг сейчас находится в "+XI_ConvertString("Colony"+pchar.questTemp.HWIC.Holl.JacobCity+"Gen")+". Я назначил ему встречу в местной таверне. Там его и следует искать.";
			link.l1 = "Отправляемся в путь!";
			link.l1.go = "Longway_JacobGo";	
			pchar.questTemp.HWIC.Holl.LongwayNeutral = "true";//признак враждебности китайца
		break;
		
		case "Longway_enemy":
			dialog.text = "Приказ минхера Роденбурга - закон для Лонгвэя... Якоб ван Берг сейчас находится в "+XI_ConvertString("Colony"+pchar.questTemp.HWIC.Holl.JacobCity+"Gen")+". Я назначил ему встречу в местной таверне. Там его и следует искать.";
			link.l1 = "Отправляемся в путь!";
			link.l1.go = "Longway_JacobGo";	
			pchar.questTemp.HWIC.Holl.LongwayEnemy = "true";//признак враждебности китайца
		break;
		
		case "Longway_friend":
			dialog.text = "Лонгвэй поможет вам всем, чем возможно, капитан. А Якоб ван Берг сейчас находится в "+XI_ConvertString("Colony"+pchar.questTemp.HWIC.Holl.JacobCity+"Dat")+". Я назначил ему встречу в местной таверне. Там его и следует искать.";
			link.l1 = "Отправляемся в путь!";
			link.l1.go = "Longway_JacobGo";	
			pchar.questTemp.HWIC.Holl.LongwayFriend = "true";//признак враждебности китайца
		break;
		
		case "Longway_JacobGo":
			//Лонгвэя - в офицеры
			npchar.quest.OfficerPrice = sti(pchar.rank)*500;
			Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(npchar.id);
			npchar.OfficerWantToGo.DontGo = true; //не пытаться уйти
			npchar.HalfImmortal = true;//полубессмертен
			npchar.loyality = 18;
			AddDialogExitQuestFunction("LandEnc_OfficerHired");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload2_back", "none", "", "", "", -1);
			AddQuestRecord("Holl_Gambit", "1-8");
			AddQuestUserData("Holl_Gambit", "sCity", XI_ConvertString("Colony"+pchar.questTemp.HWIC.Holl.JacobCity+"Dat"));
			pchar.questTemp.HWIC.Holl = "JacobOnMain";
			SetFunctionTimerCondition("JacobOnMainOver", 0, 0, 15, false);
		break;
		
		case "hired":
			dialog.text = "Вы что-то хотели от Лонгвэя, капитан?";
			link.l1 = "Да нет, ничего.";
			link.l1.go = "exit";
			NextDiag.TempNode = "hired";
		break;
		
		case "MC_GoAway":
			PlaySound("VOICE\Russian\hambit\Longway-02.wav");
			if (pchar.questTemp.HWIC.Holl == "MirageFail")
			{
				dialog.text = "Вы полный олух и тупица, капитан! Нужно было выполнить элементарную задачу - захватить 'Мираж', не потеряв при этом 'Мейфенг'. 'Мираж' без своего капитана был легкой добычей - но вы с этим не справились\nЛонгвэй не желает больше вам ни подчиняться, ни вообще видеть вас. Лонгвэй уверен - минхер Роденбург одобрит его решение, ибо он не терпит неумех не меньше, чем Лонгвэй.";
				link.l1 = "Да и черт с тобой и твоим хозяином!";
				link.l1.go = "exit";
				AddQuestRecord("Holl_Gambit", "1-10");
			}
			if (pchar.questTemp.HWIC.Holl == "JacobOnMain" || pchar.questTemp.HWIC.Holl == "JacobInRoom")
			{
				dialog.text = "Капитан, вы полный олух. Мы уже неведомо сколько времени занимаемся решением ваших личных проблем, вместо того, чтобы идти на встречу с Якобом ван Бергом. Его, безусловно, уже нет в "+XI_ConvertString("Colony"+pchar.questTemp.HWIC.Holl.JacobCity+"Dat")+"\nВы провалили элементарное задание. Лонгвэй более не желает вас видеть. Лонгвэй уверен - минхер Роденбург тоже не захочет вас видеть, ибо он не терпит неумех не меньше, чем Лонгвэй.";
				link.l1 = "Да и черт с тобой и твоим хозяином!";
				link.l1.go = "exit";
				AddQuestRecord("Holl_Gambit", "1-9");
			}
			if (pchar.questTemp.HWIC.Holl == "lateVillemstad")
			{
				dialog.text = "Капитан, сколько можно ходить по морю без цели? Вы что же решили - что 'Мейфенг' - ваше личное судно, а Лонгвэй - ваш постоянный офицер? Так вот, это не так. Лонгвэй отправляется в Виллемстад к минхеру Роденбургу сам\nЛонгвэй не желает больше вам ни подчиняться, ни вообще видеть вас. Лонгвэй уверен - минхер Роденбург одобрит его решение, ибо он не терпит разгильдяев не меньше, чем Лонгвэй.";
				link.l1 = "Да и черт с тобой и твоим хозяином!";
				link.l1.go = "exit";
			}
			PChar.quest.Munity = "Deads";
			LAi_LocationFightDisable(&Locations[FindLocation("Ship_deck")], false);
			if(sti(RealShips[sti(pchar.ship.type)].basetype) == SHIP_MAYFANG)//если сам на Мейфенг
			{
			pchar.Ship.Type = GenerateShipExt(SHIP_TARTANE, true, pchar);
			pchar.Ship.name = "Лодка";
			SetBaseShipData(pchar);
			SetCrewQuantityOverMax(PChar, 0);
			}
			else
			{
				for(i=1; i < COMPANION_MAX; i++)
				{
					int iTemp = GetCompanionIndex(PChar, i);
					if(iTemp > 0)
					{
						sld = GetCharacter(iTemp);
						if(sti(RealShips[sti(sld.ship.type)].basetype) == SHIP_MAYFANG)
						{
							pchar.questTemp.HWIC.Holl.CompanionIndex = sld.Index;
							sld = GetCharacter(sti(pchar.questTemp.HWIC.Holl.CompanionIndex));
							RemoveCharacterCompanion(PChar, sld);
							AddPassenger(PChar, sld, false);
						}
					}
				}
			}
			LAi_CharacterDisableDialog(npchar);
			LAi_SetImmortal(npchar, true);
			npchar.lifeday = 0;
			DeleteAttribute(pchar, "questTemp.HWIC.TakeQuestShip");//ПУ откроем
			DeleteAttribute(pchar, "questTemp.HWIC.HollEquip");
			pchar.questTemp.HWIC.Holl = "end";
			CloseQuestHeader("Holl_Gambit");
			pchar.questTemp.HWIC.Detector = "holl_fail";
		break;
		
		case "Longway_hire":
			PlaySound("VOICE\Russian\hambit\Longway-03.wav");
			dialog.text = "Капитан, Лонгвэй покинул минхера Роденбурга. Лонгвэй больше никогда к нему не вернется. Вы были вежливы с Лонгвэем, и вы - храбрый моряк. Лонгвэй желает пойти к вам в команду офицером.";
			link.l1 = "Добро пожаловать на борт, дружище!";
			link.l1.go = "Longway_hire_1";	
			link.l2 = "Нет, спасибо, Лонгвэй. Ты вольный капитан. Я не могу представить себя твоим командиром.";
			link.l2.go = "Longway_exit";	
		break;
		
		case "Longway_exit":
			DialogExit();
			npchar.lifeday = 0;
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload2", "none", "", "", "", 30.0);
			AddQuestRecord("Holl_Gambit", "1-37");
		break;
		
		case "Longway_hire_1"://нанимаем китайца
			DialogExit();
			DeleteAttribute(npchar, "LifeDay");
			DeleteAttribute(npchar, "HalfImmortal");
			npchar.quest.OfficerPrice = sti(pchar.rank)*500;
			npchar.OfficerWantToGo.DontGo = true;
			npchar.loyality = MAX_LOYALITY;
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, true);
			DeleteAttribute(npchar, "CompanionDisable");//теперь можем и в компаньоны
			npchar.Payment = true;
			LAi_SetOfficerType(npchar);
			NextDiag.CurrentNode = "Longway_officer";
			npchar.quest.meeting = true;
			npchar.HoldEquip = true;
			LAi_SetImmortal(npchar, false);
			LAi_SetHP(npchar, 200, 200);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			SaveCurrentNpcQuestDateParam(npchar, "HiredDate");
			AddQuestRecord("Holl_Gambit", "1-38");
		break;
		
//---------------------------------------------против всех-------------------------------------------------
		case "Longway_abordage":
			PlaySound("VOICE\Russian\hambit\Longway-02.wav");
			dialog.text = "Чего остановился? Добивай, у Лонгвэя нет больше сил, Лонгвэй проиграл.";
			link.l1 = "Погоди, дружок. Добить я тебя всегда успею. Я сначала хочу с тобой побеседовать. Возможно, по-доброму - все будет зависеть от тебя. А теперь добро пожаловать в трюм!";
			link.l1.go = "Longway_abordage_1";			
		break;
		
		case "Longway_abordage_1":
			AddQuestRecord("Holl_Gambit", "3-45");
		    DoQuestCheckDelay("LAi_ReloadBoarding", 1.0);
            DialogExit();
			LAi_SetPlayerType(pchar);
			pchar.questTemp.HWIC.Self = "LongwayPrisoner";
			npchar.lifeday = 0;
			SetFunctionTimerCondition("RemoveLongwayOver", 0, 0, 1, false);//таймер до конца суток, ибо нефиг
		break;
		
		case "Longway_prisoner":
			dialog.text = "";
			link.l1 = "Ну, вот теперь мы можем поговорить спокойно. Лонгвэй... Мне нужна информация, которой ты располагаешь, а то, что ты ей располагаешь - для меня сомнений нет. Вопрос заключается в том, выложишь ли ты ее добровольно или... под принуждением.";
			link.l1.go = "Longway_prisoner_1";			
		break;
		
		case "Longway_prisoner_1":
			dialog.text = "";
			link.l1 = "Молчишь? Хорошо. Я предлагаю тебе сделку. Я сохраню тебе жизнь, высадив на каком-нибудь пустынном берегу, а ты взамен расскажешь, куда и с какой целью отправил тебя Лукас Роденбург. Мне все известно, и про тебя, и про Роденбурга, так что отпираться бессмысленно. Ну?";
			link.l1.go = "Longway_prisoner_2";			
		break;
		
		case "Longway_prisoner_2":
			dialog.text = "";
			link.l1 = "Смотрю, ты хороший слушатель. Но пора бы уже и начать говорить. Если мы не найдем общий язык - поверь, ты все равно расскажешь обо всем. Алонсо - мастер по развязыванию языков. До того, как подняться на борт моего корабля, он был солдатом в Сантьяго... в инквизиции. Он знает массу способов, применяемых святыми отцами для получения признаний у еретиков...";
			link.l1.go = "Longway_prisoner_3";			
		break;
		
		case "Longway_prisoner_3":
			dialog.text = "";
			link.l1 = "Ты все расскажешь, мой друг. Всё... Вот только жить дальше не сможешь - слишком тяжелые повреждения останутся на твоем теле после близкого знакомства с Алонсо. Так что выбирай: или ты расскажешь мне всю правду и останешься жив, или тоже всё расскажешь, но умрешь. Подумай...";
			link.l1.go = "Longway_prisoner_4";			
		break;
		
		case "Longway_prisoner_4":
			dialog.text = "";
			link.l1 = "Я вижу в твоих глазах сомнение. Решайся. Зачем тебе умирать за грехи своего патрона? Он стоит того? Ответь, Роденбург действительно стоит того, чтобы ты отдал в муках свою жизнь за него?";
			link.l1.go = "Longway_prisoner_5";			
		break;
		
		case "Longway_prisoner_5":
			dialog.text = "Лонгвэй будет говорить. Но Лонгвэй хочет быть уверен, что вы сдержите свое слово, капитан.";
			link.l1 = "Ха! Я слышу разумные слова! Я обещаю тебе, что сдержу слово.";
			link.l1.go = "Longway_prisoner_6";			
		break;
		
		case "Longway_prisoner_6":
			dialog.text = "Простите, капитан, но этого недостаточно. Вы можете получить информацию и тут же убить Лонгвэя. Лонгвэй хочет быть уверенным - хотя бы чуть-чуть.";
			link.l1 = "Хорошо. Какие гарантии тебе нужны?";
			link.l1.go = "Longway_prisoner_7";			
		break;
		
		case "Longway_prisoner_7":
			dialog.text = "Южнее Гваделупы есть маленький остров, с бухтой под названием мыс Недоступный. Высадите Лонгвэя там на берег и дайте ему оружие. На берегу Лонгвэй расскажет вам все, что знает о Лукасе Роденбурге.";
			link.l1 = "Гм... Тебе не кажется, что ты не в том положении, чтобы ставить мне условия?";
			link.l1.go = "Longway_prisoner_8";			
		break;
		
		case "Longway_prisoner_8":
			dialog.text = "Если бы вы были в шкуре Лонгвэя, вы бы действовали точно так же, капитан. Вашему человеку будет не просто вытянуть из меня хоть слово, даже пыткой. Лонгвэй - не белый человек.";
			link.l1 = "Ладно. Договорились. Но предупреждаю: попробуешь со мной шутить - я лично разрежу тебя на куски. Маленькие куски, чтобы растянуть удовольствие... Алонсо!";
			link.l1.go = "Longway_prisoner_9";
		break;
		
		case "Longway_prisoner_9":
			DialogExit();
			NextDiag.Currentnode = "Longway_prisoner_0";
			npchar.greeting = "longway";
			sld = characterFromId("Sailor_3");
			sld.dialog.currentnode = "Sailor_deck_7";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);	
			pchar.quest.RemoveLongwayOver.over = "yes";//снять таймер
			pchar.quest.RemoveLongwayTimer.win_condition.l1 = "Timer";
			pchar.quest.RemoveLongwayTimer.win_condition.l1.date.hour  = sti(GetTime());
			pchar.quest.RemoveLongwayTimer.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 10);
			pchar.quest.RemoveLongwayTimer.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 10);
			pchar.quest.RemoveLongwayTimer.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 10);
			pchar.quest.RemoveLongwayTimer.function = "RemoveLongwayOver";
			pchar.questTemp.HWIC.Self = "GotoGuadeloupe";
		break;
		
		case "Longway_prisoner_0":
			dialog.text = "Мы уже прибыли на Гваделупу, английский капитан?";
			link.l1 = "Нет еще... Сиди смирно, скоро будем на месте.";
			link.l1.go = "exit";
			NextDiag.Tempnode = "Longway_prisoner_0";
		break;
		
		case "Longway_prisoner_10":
			dialog.text = "Вы сдержали свое слово, капитан, и Лонгвэй сдержит свое. Вы хотели узнать, какое задание Лонгвэй получил от Роденбурга?";
			link.l1 = "Да. Но я напомню тебе - в трюме ты сказал, что расскажешь о Роденбурге ВСЕ, что знаешь.";
			link.l1.go = "Longway_prisoner_11";			
		break;
		
		case "Longway_prisoner_11":
			dialog.text = "Лонгвэй помнит об этом. Он расскажет все, о чем спросите, касательно Роденбурга, английский капитан.";
			link.l1 = "Замечательно. Начнем с твоего задания, которое ты получил.";
			link.l1.go = "Longway_prisoner_12";			
		break;
		
		case "Longway_prisoner_12":
			dialog.text = "'Мейфенг' вышла из порта Виллемстад и взяла курс на север, к берегам Сент-Кристофера. В ближайшие пять дней у берегов этого острова, направляясь в сторону Кюрасао, будет проходить тяжелый галеон под командованием Питера Стайвесанта. В задачу Лонгвэя входило уничтожить этот корабль вместе с капитаном.";
			link.l1 = "Постой... Роденбург приказал тебе убить Стайвесанта? Что за вздор?";
			link.l1.go = "Longway_prisoner_13";			
		break;
		
		case "Longway_prisoner_13":
			dialog.text = "Лонгвэй говорит правду, английский капитан. Таков был приказ минхера Роденбурга. Лонгвэю это было не по душе, но Лонгвэй не привык обсуждать приказы.";
			link.l1 = "Что-то я перестал понимать... Что за игру затеял твой чертов хозяин?";
			link.l1.go = "Longway_prisoner_14";			
		break;
		
		case "Longway_prisoner_14":
			dialog.text = "Бывший хозяин, английский капитан. Лонгвэй не намерен возвращаться на службу к минхеру Роденбургу. Цель Роденбурга - захват власти на Кюрасао. С Матиасом Беком он разделался легко: использовав свой авторитет и связи с комендантом, посадил за решетку\nЕдинственный, кому он теперь обязан подчиняться - это директор Компании минхер Стайвесант. С его ликвидацией у Роденбурга в руках оказываются все нити власти в голландских колониях.";
			link.l1 = "Хм. Странное совпадение. А скажи-ка мне, Лонгвэй, что сподвигло уважаемого и влиятельного человека на такие радикальные действия против своего начальства? В солнечный удар или внезапное умопомешательство мне слабо верится...";
			link.l1.go = "Longway_prisoner_15";			
		break;
		
		case "Longway_prisoner_15":
			dialog.text = "Это Лонгвэй хотел бы узнать сам у вас, английский капитан. Ведь это вы захватили курьера Компании и дали ему письмо для Роденбурга? Причина - в этом письме.";
			link.l1 = "Уже яснее... Да, видать, много чего содержится в архиве Джона, раз Роденбург так перепугался, что пошел на дворцовый переворот.";
			link.l1.go = "Longway_prisoner_16";			
		break;
		
		case "Longway_prisoner_16":
			dialog.text = "Вы что-то еще хотели узнать, капитан?";
			link.l1 = "Да. Какие еще действия предпринял Роденбург, кроме приказа убить Стайвесанта?";
			link.l1.go = "Longway_prisoner_17";			
		break;
		
		case "Longway_prisoner_17":
			dialog.text = "Минхер Роденбург приказал устранить вас. До отплытия на охоту за Стайвесантом, Лонгвэй был в Каракасе, встретился с капитаном Якобом и передал указания.";
			link.l1 = "Якоб? Якоб... Хм. Якоб ван Берг?";
			link.l1.go = "Longway_prisoner_18";			
		break;
		
		case "Longway_prisoner_18":
			dialog.text = "Вы хорошо осведомлены. Да. Капитан Якоб теперь ведет за вами охоту, английский капитан. И он найдет вас, так или иначе. От ван Берга не удавалось скрыться никому.";
			link.l1 = "Не так страшен черт, как его малюют. Разберемся и с твоим ван Бергом, и с его кораблем-призраком.";
			link.l1.go = "Longway_prisoner_19";			
		break;
		
		case "Longway_prisoner_19":
			dialog.text = "Вам многое известно, господин капитан. Однако Лонгвэю более добавить нечего. Спрашивайте, если у вас еще остались вопросы.";
			link.l1 = "Стайвесант будет у берегов Сент-Кристофера?";
			link.l1.go = "Longway_prisoner_20";			
		break;
		
		case "Longway_prisoner_20":
			dialog.text = "Да, капитан. В течение недели вы сможете обнаружить его галеон у берегов этого острова.";
			link.l1 = "Отлично! Будем действовать против хитрой лисы его же методами... Больше вопросов нет. Я узнал всё, что хотел.";
			link.l1.go = "Longway_prisoner_21";			
		break;
		
		case "Longway_prisoner_21":
			dialog.text = "Последний совет, английский капитан. Если вы хотите подойти к галеону Стайвесанта и не быть атакованным - у вас должен быть корабль, который не вызовет у него подозрений. А именно - 'Мейфенг'.";
			link.l1 = "Понятно. Спасибо за информацию.";
			link.l1.go = "Longway_prisoner_22";			
		break;
		
		case "Longway_prisoner_22":
			dialog.text = "А теперь Лонгвэй уходит. Прощайте, английский капитан.";
			link.l1 = "Бывай, сын Поднебесной.";
			link.l1.go = "Longway_prisoner_23";			
		break;
		
		case "Longway_prisoner_23":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "ReturnShoreToNormal", -1);
			npchar.lifeday = 0;
			AddQuestRecord("Holl_Gambit", "3-49");
			pchar.questTemp.HWIC.Self = "MeetingStivesant";
			pchar.quest.Seek_Piter.win_condition.l1 = "location";
			pchar.quest.Seek_Piter.win_condition.l1.location = "Nevis";
			pchar.quest.Seek_Piter.function = "CreatePiterHalleon";
			pchar.quest.RemoveLongwayTimer.over = "yes";//снять прерывание
			SetFunctionTimerCondition("QuestShipsTerms_Over", 0, 0, 8, false); // таймер
		break;
		
		//--> ----------------------------------- офицерский блок ------------------------------------------
		case "Longway_officer":
			dialog.text = "Лонгвэй слушает вас, капитан.";
			if (CheckAttribute(pchar, "questTemp.Dolly_Tieyasal") && !CheckAttribute(npchar, "quest.Tieyasal"))
			{
				Link.l4 = "Лонгвэй, я собираюсь отправиться в старый индейский город Тайясаль. Не буду скрывать: это крайне опасное путешествие, и более того - необычное: через телепортационный истукан. Ты... пойдешь со мной?";
				Link.l4.go = "tieyasal";
			}
			if (CheckAttribute(NPChar, "IsCompanionClone"))//////////////////компаньон//////////////////////////////////////////////
			{
				//dialog.text = "Я прибыл по вашему распоряжению, капитан.";
				Link.l2 = "У меня есть для тебя несколько приказов.";
				Link.l2.go = "Companion_Tasks";
				NextDiag.TempNode = "Longway_officer";// не забыть менять в зависисомости от оффа
				break;
			}
			Link.l1 = "Слушай мой приказ!";
            Link.l1.go = "stay_follow";
			link.l2 = "Пока ничего. Вольно!";
			link.l2.go = "exit";
			NextDiag.TempNode = "Longway_officer";
		break;
		//Указания для компаньона 19.02.08 -->/////////////////////////////////////////////////////////////////////////////////////////
		case "Companion_Tasks":
			dialog.Text = "Внимательно слушаю.";
			Link.l1 = "Это касается абордажа.";
			Link.l1.go = "Companion_TaskBoarding";
			Link.l2 = "Это касается твоего корабля.";
			Link.l2.go = "Companion_TaskChange";
			Link.l8 = "Пока ничего.";
			Link.l8.go = "exit";
			//NPChar.id = "Tonzag"; 
		break;
		
		case "Companion_TaskBoarding":
			dialog.Text = "Что же вы желаете?";
			Link.l1 = "Я хочу чтобы ты не брал корабли на абордаж. Побереги себя и свою команду.";
			Link.l1.go = "Companion_TaskBoardingNo";
			Link.l2 = "Мне нужно чтобы ты брал вражеские корабли на абордаж.";
			Link.l2.go = "Companion_TaskBoardingYes";
		break;
		
		case "Companion_TaskChange":
			dialog.Text = "Что же вы желаете?";
			Link.l1 = "Я хочу чтобы ты не менял свой корабль после абордажа. Он слишком ценен.";
			Link.l1.go = "Companion_TaskChangeNo";
			Link.l2 = "Когда будешь брать врагов на абордаж, посмотри, вдруг кораблик приличный будет, тогда бери себе.";
			Link.l2.go = "Companion_TaskChangeYes";
		break;
		
		case "Companion_TaskBoardingNo":
			dialog.Text = "Так точно.";
			Link.l1 = "Вольно.";
			Link.l1.go = "exit";
			NPChar.Tasks.CanBoarding = false;
		break;
		
		case "Companion_TaskBoardingYes":
			dialog.Text = "Будет исполнено.";
			Link.l1 = "Вольно.";
			Link.l1.go = "exit";
			NPChar.Tasks.CanBoarding = true;
		break;
		
		case "Companion_TaskChangeNo":
			dialog.Text = "Так точно.";
			Link.l1 = "Вольно.";
			Link.l1.go = "exit";
			NPChar.Tasks.CanChangeShipAfterBoarding = false;
		break;
		
		case "Companion_TaskChangeYes":
			dialog.Text = "Будет исполнено.";
			Link.l1 = "Вольно.";
			Link.l1.go = "exit";
			NPChar.Tasks.CanChangeShipAfterBoarding = true;
		break;
	//	<========/////////////////////////////////////////////////////////////////////////
		case "stay_follow":
            dialog.Text = "Какие будут приказания?";
            Link.l1 = "Стой здесь!";
            Link.l1.go = "Boal_Stay";
            Link.l2 = "Следуй за мной и не отставай!";
            Link.l2.go = "Boal_Follow";
			sGun = GetCharacterEquipByGroup(NPChar, GUN_ITEM_TYPE);
			if(sGun != "")
			{
				rItm = ItemsFromID(sGun);
				if(CheckAttribute(NPChar, "chr_ai.bulletNum") && sti(NPChar.chr_ai.bulletNum) > 1)
				{
					Link.l3 = "Нужно изменить тип боеприпаса для твоего огнестрельного оружия.";
					Link.l3.go = "SetGunBullets";
				}	
			}		
		break;
		
		case "SetGunBullets":
			Dialog.Text = "Выбор типа боеприпаса:";
			sGun = GetCharacterEquipByGroup(NPChar, GUN_ITEM_TYPE);
			rItm = ItemsFromID(sGun);
			makearef(rType, rItm.type);	
			for (i = 0; i < sti(NPChar.chr_ai.bulletNum); i++)
			{
				sAttr = GetAttributeName(GetAttributeN(rType, i));
				sBullet = rItm.type.(sAttr).bullet;
				rItem = ItemsFromID(sBullet);								
				attrL = "l" + i;
				Link.(attrL) = GetConvertStr(rItem.name, "ItemsDescribe.txt");;
				Link.(attrL).go = "SetGunBullets1_" + i;
			}
		break;	

		case "SetGunBullets2":
			i = sti(NPChar.SetGunBullets) + 1; 
			sGun = GetCharacterEquipByGroup(NPChar, GUN_ITEM_TYPE);
			rItm = ItemsFromID(sGun);
			sAttr = "t" + i;
			sBullet = rItm.type.(sAttr).bullet;
			LAi_SetCharacterUseBullet(NPChar, sBullet);
			LAi_GunSetUnload(NPChar);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DeleteAttribute(NPChar,"SetGunBullets");
			DialogExit();
		break;		
		
        case "Boal_Stay":
            Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(Npchar.id);
            AddDialogExitQuestFunction("LandEnc_OfficerStay");
            dialog.Text = "Есть изменить дислокацию!";
            Link.l1 = "Вольно.";
            Link.l1.go = "Exit";
            Npchar.chr_ai.tmpl = LAI_TMPL_STAY;
        break;
        
        case "Boal_Follow":
            SetCharacterTask_FollowCharacter(Npchar, PChar);
            dialog.Text = "Есть изменить дислокацию!";
            Link.l1 = "Вольно.";
            Link.l1.go = "Exit";
        break;
	//<-- ----------------------------------- офицерский блок ----------------------------------------
	
	// на Тайясаль
		case "tieyasal":
			dialog.text = "Лонгвэй шел за вами все это время, Лонгвэй пойдет за вами и дальше. Лонгвэй не бросать свой капитан.";
			link.l1 = "Спасибо, Лонгвэй! Я рад, что не ошибся в тебе.";
			link.l1.go = "tieyasal_1";
		break;
		
		case "tieyasal_1":
			dialog.text = "Когда мы отправляться?";
			link.l1 = "Немного позже. А пока подготовимся к походу.";
			link.l1.go = "tieyasal_2";
		break;
		
		case "tieyasal_2":
			DialogExit();
			AddQuestRecord("Tieyasal", "24");
			npchar.quest.Tieyasal = "teleport";
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}

string SelectJacobCity()
{
	string sTemp;
	switch (drand(4))
	{
		case 0: sTemp = "Cumana" break;
		case 1: sTemp = "Caracas" break;
		case 2: sTemp = "Maracaibo" break;
		case 3: sTemp = "Cartahena" break;
		case 4: sTemp = "Portobello" break;
	}
	return sTemp;
}