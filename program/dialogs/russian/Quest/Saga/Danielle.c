// Даниэль Хоук - жена Натаниэля Хоука
void ProcessDialogEvent()
{
	ref NPChar, sld, rItm, rItem;
	aref Link, NextDiag, rType;
	int i;
	string 	sTemp, sAttr, sGun, sBullet, attrL;

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
		case "First time": //первая встреча - знакомство
			PlaySound("VOICE\Russian\saga\Denny Hawk-02.wav");
			dialog.text = "Постой, красавчик! Мне кажется, нам есть, что сказать друг другу.";
			link.l1 = "Мы разве знакомы? Впрочем, даже для незнакомой дамы у меня всегда найдётся пара часов свободного времени.";
			link.l1.go = "meeting";			
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting":
			PlaySound("VOICE\Russian\saga\Denny Hawk-01.wav");
			dialog.text = "Не строй планов на мой счёт, капитан. Найди себе на пару часов дурочку помоложе. А у меня к тебе конкретный разговор. Я как бы замужем. И моего мужа зовут Натаниэль Хоук.";
			link.l1 = "Вот это да! Так вы и есть та самая стер... э-э-э, Данни Хоук, про которую мне только что рассказывал мистер Свенсон?";
			link.l1.go = "meeting_1";
		break;
		
		case "meeting_1":
			dialog.text = "Она самая. Знаю, Лесной Дьявол обо мне не очень высокого мнения, как, впрочем и я о нём, но предупредить тебя на счёт того, что саблю я ношу не для вида, он был обязан. Так что ближе к делу, сынок!\nЯ давно наблюдаю за Свенсоном и всеми, кто к нему приходит, поскольку именно он послал моего мужа в джунгли на погибель. Я думала, что он заодно с Джекманом, но теперь понимаю, что это не так. Я проторчала под окнами всё это время. Подслушать удалось не всё, но всё же я узнала для себя много интересного\nТы действительно намерен найти моего мужа и надрать задницу Джекману? Или просто трепался?";
			link.l1 = "Подслушивать, мадам Хоук, нехорошо. Но я вас, пожалуй, прощу, если впредь вы будете разговаривать со мной более почтительно. Найду я Хоука или нет, это мои проблемы. Если вам есть что сказать - говорите. Если сказать нечего, уйдите с дороги. Пока прошу по-хорошему.";
			link.l1.go = "meeting_2";
		break;
		
		case "meeting_2":
			dialog.text = "А-та-та, какие мы горячие! Ну ладно тебе, капитан... Характер у меня и впрямь сложный. Вижу, что ты не из трусливых, и цену себе знаешь. И это... Давай на 'ты'. Обещаю, что буду легче на поворотах. Ты нужен мне, а я могу пригодиться тебе. У нас есть общие цели. Возьми меня к себе в команду, не пожалеешь. Пока не найдём Натана, буду служить тебе верой и правдой.";
			link.l1 = "Считай себя уже зачисленной... Данни. Свенсон сказал, что ты занималась розысками мужа в одиночку. Тебе удалось узнать какие-нибудь подробности?";
			link.l1.go = "meeting_3";
		break;
		
		case "meeting_3":
			dialog.text = "Немного, но этого достаточно, чтобы обвинить Джекмана во лжи. Этот подонок сказал, что охрана рудника, на засаду которой напоролся Натан, пленных не брала. Трупа Хоука в бухте действительно никто не видел. Но его и не могли увидеть, так как он всё же оказался в плену на руднике. Его там нашёл шаман мискито Змеиный Глаз\nОн же помог ему бежать. А вот куда Хоук делся потом - неизвестно. Шаман что-то бормотал про какого-то Кукулькана, который мог его сожрать. Но я в этом его бреду ничего не поняла. К тому же краснокожий явно дал мне понять, что белых женщин всерьёз не воспринимает. Поговорил бы ты с ним. Может с тобой он будет более откровенным.";
			link.l1 = "Уже что-то! Такие новости меня обнадёживают. Где находится индейская деревня, в которой живёт этот шаман?";
			link.l1.go = "meeting_4";
		break;
		
		case "meeting_4":
			dialog.text = "Деревня находится в глубине джунглей. Лучше всего добраться до бухты Аматике и отправиться на запад по лесным тропам. Я покажу дорогу, если сам не найдёшь. А каменный идол, который местные дикари почитают как своего бога, действительно стоит недалеко от деревни. Была я там пару раз. Ничего особенного. Камень, покрытый мхом, и ничего более.";
			link.l1 = "Интересно. Ладно, собираемся в путь. Поговорим с шаманом - будем думать, что делать дальше. Ты готова?";
			link.l1.go = "meeting_5";
		break;
		
		case "meeting_5":
			dialog.text = "Спрашиваешь! Конечно, готова. После того, как мне пришлось убраться из Марун-Тауна, я только и делаю, что путешествую. К тому же, я не пассажиром к тебе просилась.";
			link.l1 = "Отлично. Тогда отправляемся на корабль.";
			link.l1.go = "meeting_6";
		break;
		
		case "meeting_6":
			dialog.text = "Есть, капитан!";
			link.l1 = "...";
			link.l1.go = "meeting_7";
		break;
		
		case "meeting_7":
			DialogExit();
			chrDisableReloadToLocation = false;//открыть локацию
			npchar.quest.OfficerPrice = sti(pchar.rank)*700;
			npchar.OfficerWantToGo.DontGo = true; //не пытаться уйти
			npchar.CompanionDisable = true; //нельзя в компаньоны - чтобы не утонула
			LAi_SetImmortal(npchar, false);
			npchar.HalfImmortal = true; //чтобы не убили в сухопутном бою
			npchar.loyality = MAX_LOYALITY;
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, true);
			npchar.Payment = true;
			npchar.DontClearDead = true;
			NextDiag.CurrentNode = "Danielle_officer";
			npchar.HoldEquip = true; // лесник -  не отдавать саблю и пистоль																					 
			SaveCurrentNpcQuestDateParam(npchar, "HiredDate");
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			AddQuestRecord("BaronReturn", "2");
			Saga_CreateSnakeEye();
			//выбираем амулеты
			pchar.questTemp.Saga.BaronReturn.Indian = "indian_"+(rand(10)+1);
			pchar.questTemp.Saga.BaronReturn.Amulet = "amulet_"+(rand(10)+1);
			pchar.questTemp.Saga.BaronReturn.Obereg = "obereg_"+(rand(10)+1);
			// на локацию с истуканом
			npchar.quest.talk = "dolly";
			pchar.quest.Saga_Dolly.win_condition.l1 = "location";
			pchar.quest.Saga_Dolly.win_condition.l1.location = "Pearl_jungle_03";
			pchar.quest.Saga_Dolly.function = "Saga_DannyTalk";
			AddCharacterExpToSkill(pchar, "Fortune", 50);//везение
			AddCharacterExpToSkill(pchar, "Leadership", 50);
			npchar.greeting = "danny_1";
		break;
		
		// у истукана в джунглях
		case "Dolly":
			dialog.text = ""+pchar.name+"! Идём! Я покажу тебе этого каменного истукана, про которого талдычил индейский колдун. Самый обычный каменный столб. Пошли!";
			link.l1 = "...";
			link.l1.go = "Dolly_1";
		break;
		
		case "Dolly_1":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocator(npchar, "item", "torch1", "Saga_ShowDolly", -1);
		break;
		
		case "Dolly_2":
			dialog.text = "Эй! Смотри: просто каменная статуя. Ничего такого особенного...";
			link.l1 = "Вижу... Хотя фигурка наверху жутковатая, не находишь?";
			link.l1.go = "Dolly_3";
		break;
		
		case "Dolly_3":
			dialog.text = "У индейцев все истуканы такие - страшные и злые. Я раньше видала очень похожий идол. Все они одинаковые. Ладно, пойдём, деревня уже близко!";
			link.l1 = "Пошли!";
			link.l1.go = "Dolly_4";
		break;
		
		case "Dolly_4":
			chrDisableReloadToLocation = false;//открыть локацию
			DialogExit();
			LAi_SetOfficerType(npchar);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			npchar.dialog.currentnode = "Danielle_officer";
		break;
		
		// у мискито
		case "SnakeEye":
			dialog.text = "Ну, что скажешь, "+pchar.name+"? Что тебе поведал этот краснокожий чревовещатель? Ты хоть что-нибудь понял из его мудрствований?";
			link.l1 = "Ты опять подслушивала, Данни?";
			link.l1.go = "SnakeEye_1";
		break;
		
		case "SnakeEye_1":
			dialog.text = "Ну... только совсем чуть-чуть. Да, да, мы, женщины, такие. Но ты должен меня простить - я очень волнуюсь за своего мужа. Если что, то я его люблю, вообще-то. Ну? Ты хоть немного разобрался в том, что этот прорицатель рассказал?";
			link.l1 = "Пытаюсь осмыслить... Да, понять Змеиного Глаза очень трудно. Получается примерно так: идол, мимо которого мы проходили по пути в деревню, тот самый, который ты назвала камнем, покрытым мхом, есть не что иное, как некий магический портал, способный перемещать человека в пространстве и времени.";
			link.l1.go = "SnakeEye_2";
		break;
		
		case "SnakeEye_2":
			dialog.text = "";
			link.l1 = "Ты чего так на меня уставилась? Я не сам это придумал, у меня с головой всё в порядке. Ты спросила, что мне поведал шаман - я тебе и рассказываю.";
			link.l1.go = "SnakeEye_3";
		break;
		
		case "SnakeEye_3":
			dialog.text = "Прости, пожалуйста. Я больше не буду так смотреть. Продолжай.";
			link.l1 = "Он сказал, что когда Натана настигала погоня, он указал ему на этого истукана, как на возможность спасения, за счёт того, что Кукулькан - шаман так называет это божество - пожрёт и выплюнет его. Говоря человеческим языком, это значит, что Натаниэль мог через статую мгновенно попасть в другое место - телепортироваться.";
			link.l1.go = "SnakeEye_4";
		break;
		
		case "SnakeEye_4":
			dialog.text = "Господи, держите меня семеро... Мало нам с Натаном досталось в индейском храме, напичканном магией майя, так ещё под старость лет такая же ерунда начинается...";
			link.l1 = "Что ты сейчас сказала?";
			link.l1.go = "SnakeEye_5";
		break;
		
		case "SnakeEye_5":
			dialog.text = "Нет, ничего, "+pchar.name+", не обращай внимания. Так, воспоминания о бурной молодости. Но как Натан мог это сделать? В смысле, телепортироваться? Мы же с тобой только что были у этого истукана, я ходила вокруг него, прикасалась к нему... камень-камнем!";
			link.l1 = "Змеиный Глаз сказал, что истукан оживает в полночь. Тогда он из каменного становится золотым и в нем поселяется дух Кукулькана. Вот тогда-то, наверное, к нему и стоит прикасаться. Или наоборот, не стоит.";
			link.l1.go = "SnakeEye_6";
		break;
		
		case "SnakeEye_6":
			dialog.text = "Жуть какая... Теперь что? Ждем полночи и идём в джунгли?";
			link.l1 = "Нет. Шаман сказал, что истукан не только перемещает человека, но и подвергает его жизнь риску. Как я понял - высасывает здоровье. Змеиный Глаз сам трижды проходил через эти статуи, и после каждого прохождения лечился каким-то уникальным зельем.";
			link.l1.go = "SnakeEye_7";
		break;
		
		case "SnakeEye_7":
			dialog.text = "Ты попросил у него это зелье?";
			link.l1 = "Конечно. Но во-первых, у него осталось всего три фляги, а во-вторых, он потребовал за них три амулета.";
			link.l1.go = "SnakeEye_8";
		break;
		
		case "SnakeEye_8":
			dialog.text = "А может, обойдёмся без этих зелий? Пойдём ночью к истукану и потрогаем его...";
			link.l1 = "Опрометчивый шаг. Я, конечно, допускаю, что этот индеец попросту свихнулся и морочит нам голову, но на психопата он не похож, а потому весьма вероятно, что он говорит правду. Ты что-то там говорила про индейскую магию? Ты сомневаешься в её существовании?";
			link.l1.go = "SnakeEye_9";
		break;
		
		case "SnakeEye_9":
			dialog.text = "Да, говорила. Не сомневаюсь ни на секунду, потому что видела её в действии собствеными глазами. Пожалуй, ты прав: рисковать не стоит.";
			link.l1 = "Вот-вот. Поэтому мы раздобудем амулеты, которые просит шаман, возьмём его чудесное зелье и только потом отправимся к статуе. Точнее, я отправлюсь. Один.";
			link.l1.go = "SnakeEye_10";
		break;
		
		case "SnakeEye_10":
			dialog.text = "Это ещё почему? А как же я?";
			link.l1 = "А ты останешься на моём корабле за старшего. Данни, и даже не спорь. Зелий всего три пузырька. Неизвестно, что там ждёт за порталом. И, в конце-концов, неизвестно, куда меня забросит, если шаман прав и эта штука действительно работает. Может, Натана там и в помине не будет.";
			link.l1.go = "SnakeEye_11";
		break;
		
		case "SnakeEye_11":
			dialog.text = "Ты такой же, как и Натан. Все вы, мужчины, одинаковые... Ладно, будь по-твоему.";
			link.l1 = "Вот и славно, что мы с тобой договорились. А теперь идём - нам нужно раздобыть амулеты.";
			link.l1.go = "Dolly_4";
		break;
		
		// перед походом к истукану
		case "teleport":
			dialog.text = "Ну что? Получил зелья?";
			link.l1 = "Да. Получил и зелья, и наставления. Теперь осталось последнее - отправиться в полночь к истукану и прикоснуться к нему.";
			link.l1.go = "teleport_1";
		break;
		
		case "teleport_1":
			dialog.text = "Тебе страшно?";
			link.l1 = "Да. Мне страшно, что шаман может оказаться сумасшедшим и никакого телепорта не произойдёт.";
			link.l1.go = "teleport_2";
		break;
		
		case "teleport_2":
			dialog.text = "Ну-ну... Неужели совсем, ни капельки не боязно?";
			link.l1 = "Данни, ну что ты пристала... Конечно, немного не по себе, чего уж там греха таить.";
			link.l1.go = "teleport_3";
		break;
		
		case "teleport_3":
			dialog.text = "Я пойду с тобой.";
			link.l1 = "Ты опять начинаешь? Мы же вроде договорились...";
			link.l1.go = "teleport_4";
		break;
		
		case "teleport_4":
			dialog.text = "Ты не понял. Я просто буду неподалеку. Надо же мне убедиться, что этот истукан работает... или не работает.";
			link.l1 = "Против этого я не возражаю. Но только не вздумай последовать за мной, если статуя всё-таки 'пожрет' меня. Ты слышишь?";
			link.l1.go = "teleport_5";
		break;
		
		case "teleport_5":
			dialog.text = "Слышу. Обещаю, что не стану своевольничать... капитан.";
			link.l1 = "Вот и отлично. И, Данни: похоже, не такая уж ты и стерва, как рассказывают.";
			link.l1.go = "teleport_6";
		break;
		
		case "teleport_6":
			dialog.text = "Ты меня ещё плохо знаешь, "+pchar.name+". Ладно, давай не будем об этом.";
			link.l1 = "Не будем... Ну, тогда готовься к ночному походу!";
			link.l1.go = "Dolly_4";
			npchar.quest.talk = "shadowstar";
			pchar.quest.Saga_Dolly1.win_condition.l1 = "location";
			pchar.quest.Saga_Dolly1.win_condition.l1.location = "Pearl_jungle_03";
			pchar.quest.Saga_Dolly1.win_condition.l2 = "Hour";
			pchar.quest.Saga_Dolly1.win_condition.l2.start.hour = 0.00;
			pchar.quest.Saga_Dolly1.win_condition.l2.finish.hour = 1.00;
			pchar.quest.Saga_Dolly1.function = "Saga_DannyTalk";
		break;
		
		// перед телепортацией
		case "shadowstar":
			dialog.text = "Смотри, "+pchar.name+"! Клянусь всеми святыми, над этим истуканом горит какой-то странный свет!";
			link.l1 = "Похоже, шаман не солгал. И, если мне не кажется в темноте, то верх статуи уже совсем не каменный.";
			link.l1.go = "shadowstar_1";
		break;
		
		case "shadowstar_1":
			dialog.text = "Точно... Он словно отлит из золота! Невероятно!";
			link.l1 = "Данни, мне пора. Пожелай удачи и держи кулаки за меня. Не приближайся к истукану! Стой тут.";
			link.l1.go = "shadowstar_2";
		break;
		
		case "shadowstar_2":
			dialog.text = "Удачи, "+pchar.name+". Дай-то Бог, всё получится... Зелье шамана у тебя наготове?";
			link.l1 = "Да, под рукой. Всё будет хорошо, Данни. Ну, вперёд!";
			link.l1.go = "shadowstar_3";
		break;
		
		case "shadowstar_3":
			DialogExit();
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			DoQuestReloadToLocation(pchar.location, pchar.location.group, pchar.location.locator, "");
		break;
		
		// прибыл назад 
		case "arrive":
			dialog.text = "А-а-а?! Чёрт побери, что за чудовище?! Ну, погоди! Я и не таких тварей на своём веку повидала - один Ван дер Декен чего стоил! Сейчас я тебе задам жару!";
			link.l1 = "(глухо) Данни, стой! Остановись сейчас же!";
			link.l1.go = "arrive_1";
		break;
		
		case "arrive_1":
			dialog.text = "А?! Что? Что ты сейчас сказало?! Данни?";
			link.l1 = "(глухо) Да стой же ты наконец! Не хватайся за саблю! Дай мне снять с себя эту штуковину!";
			link.l1.go = "arrive_2";
		break;
		
		case "arrive_2":
			dialog.text = "Чёрт возьми, эта дрянь говорит как... "+pchar.name+"?!";
			link.l1 = "(глухо) Ох-х... Ну неужели!";
			link.l1.go = "arrive_3";
		break;
		
		case "arrive_3":
			DialogExit();
			RemoveCharacterEquip(pchar, CIRASS_ITEM_TYPE);
			DoQuestCheckDelay("Pearl_TeleportArrive_1", 1.5);
		break;
		
		case "arrive_4":
			dialog.text = "Фух, как же ты меня напугал! Я чуть не начала тебя кромсать саблей!";
			link.l1 = "Я видел... да что же ты такая горячая, а?";
			link.l1.go = "arrive_5";
		break;
		
		case "arrive_5":
			dialog.text = "Уж какая есть... Ох, до сих пор сердце готово из груди выпрыгнуть...";
			link.l1 = "Данни, мы сейчас где? У деревни мискито, что ли?";
			link.l1.go = "arrive_6";
		break;
		
		case "arrive_6":
			dialog.text = "А где же ещё! Вон, стоит истукан, при помощи которого ты испарился. Да, вот это было зрелище! До конца дней помнить буду.";
			link.l1 = "Так ты что, столько времени ждала меня здесь?";
			link.l1.go = "arrive_7";
		break;
		
		case "arrive_7":
			dialog.text = "Скажи на милость, а что же мне ещё оставалось делать? После того, как статуя сожрала тебя, у меня была одна надежда - что когда-нибудь она тебя и выплюнет. К тому же, Змеиный Глаз сказал, что скорее всего так и случится\nЯ жила у мискито и ежедневно дежурила у истукана. Да что мы о ерунде-то говорим? Рассказывай! Что было там? Куда тебя носило?";
			link.l1 = "Данни, это очень долгая история - чего только я не насмотрелся... Но чтобы облегчить твою душу, скажу сразу: я нашёл Натаниэля!";
			link.l1.go = "arrive_8";
		break;
		
		case "arrive_8":
			dialog.text = "Нашёл Натана? Где он? Как он?!";
			link.l1 = "Не буду лгать - он жив, но очень плох. У него не было с собой зелья команчей, и истукан высосал из него всё здоровье. Он лежит сейчас в каюте старого разбитого корабля на странном Острове Погибших Кораблей, куда меня, собственно, и забросило. Змеиный Глаз оказался прав от начала и до конца!";
			link.l1.go = "arrive_9";
		break;
		
		case "arrive_9":
			dialog.text = "Бедный Натан... Где этот чёртов остров? Как туда попасть?! Только через истукан? Я скуплю все лечебные зелья у мискито и сегодня же ночью отправляюсь туда! Как-нибудь выживу...";
			link.l1 = "Стой! Да подожди ты! Натан болен, но угрозы его жизни нет. За ним ухаживает один парень, кормит его и присматривает за ним. А если ты пойдёшь через телепорт, то вмиг превратишься в развалину, да и на Острове том такие порядки, что... опасно это!";
			link.l1.go = "arrive_10";
		break;
		
		case "arrive_10":
			dialog.text = "Что ты предлагаешь? Сидеть, сложа руки, пока Натан там мучается, а, возможно, умирает?";
			link.l1 = "Так, прекрати истерику. Во-первых, я тебе сказал - Натан болен, но не умирает. Я разговаривал с ним. А во-вторых, я собираюсь отправиться на этот Остров на корабле, и ты пойдёшь со мной.";
			link.l1.go = "arrive_11";
		break;
		
		case "arrive_11":
			dialog.text = "Ты знаешь, где этот Остров?";
			link.l1 = "Ну конечно! Там я нашёл, кроме Натана, ещё и Акулу Додсона. У меня теперь есть точные координаты Острова и лоция, чтобы пройти через рифы, которыми он окружён. Сейчас мы возвращаемся назад, к кораблю и идём в Блювельд...";
			link.l1.go = "arrive_12";
		break;
		
		case "arrive_12":
			dialog.text = "А это ещё зачем? Почему нельзя отправиться сразу?";
			link.l1 = "Данни, мне надо подготовить экспедицию. Закупить побольше продовольствия - на Острове оно дефицит, решить, на каком судне мы туда пойдём - не каждый корабль пройдёт через островные рифы. Да и хочу поговорить со Свенсоном...";
			link.l1.go = "arrive_13";
		break;
		
		case "arrive_13":
			dialog.text = "";
			link.l1 = "Подготовка будет недолгой. А Остров отсюда недалеко - на северо-запад от Гаваны, в сторону Мексиканского залива.";
			link.l1.go = "arrive_14";
		break;
		
		case "arrive_14":
			dialog.text = "Ну хорошо... Пускай будет так. Главное - что Натан найден. Спасибо тебе! Ему там совсем плохо, да?";
			link.l1 = "Ну... болеет он. А кроме того, сильно хандрит - отчаялся совсем. И скучает по тебе. Да, Натан попросил передать, что очень любит тебя.";
			link.l1.go = "arrive_15";
		break;
		
		case "arrive_15":
			dialog.text = "(смахивая слезу) Старый дурак! Никогда меня не слушал, всё по-своему... "+pchar.name+", давай пойдём к кораблю! Я хочу как можно быстрее отправиться в путь!";
			link.l1 = "Конечно, Данни. А по пути я расскажу тебе о своих приключениях. Идём!";
			link.l1.go = "Dolly_4";
			AddQuestRecord("BaronReturn", "9");
			LAi_LocationDisableOfficersGen("Pearl_jungle_03", false); // пускать офицеров в локу телепорта
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешить драться
			setCharacterShipLocation(pchar, "Shore9"); // калеуче
			setWDMPointXZ("Shore9"); // корабль в бухту Аматике
			bNoEatNoRats  = false; // еду и крыс включить
		break;
		
		// в LSC у причала
		case "nathaniel":
			dialog.text = "Да, подобного места мне ещё не доводилось видеть. Да это же целый остров из кораблей!";
			link.l1 = "Я же тебе рассказывал, Данни...";
			link.l1.go = "nathaniel_1";
		break;
		
		case "nathaniel_1":
			dialog.text = "Одно дело - слышать, и совсем другое - видеть собственными глазами. Ладно. Скажи, где мне искать Натаниэля?";
			link.l1 = "Он на одном из кораблей. Но туда можно добраться только вплавь.";
			link.l1.go = "nathaniel_2";
		break;
		
		case "nathaniel_2":
			dialog.text = "Плевать. Рассказывай, как добраться до этого корабля.";
			link.l1 = "Данни, не торопи события. Ты и Натан уже столько ждали - подожди ещё немного! Я проведу тебя к нему, сама ты будешь плутать, да ещё нарвёшься не дай Бог на нарвалов или ривадос и начнёшь с ними препираться - добром не кончится.";
			link.l1.go = "nathaniel_3";
		break;
		
		case "nathaniel_3":
			dialog.text = "Хорошо, тогда пошли. Я буду держаться за тобой.";
			link.l1 = "Учти, нам придётся проплыть приличное расстояние...";
			link.l1.go = "nathaniel_4";
		break;
		
		case "nathaniel_4":
			dialog.text = "Ничего, я это как-нибудь переживу.";
			link.l1 = "Рад это слышать... Скоро ты увидишь своего мужа!";
			link.l1.go = "nathaniel_5";
		break;
		
		case "nathaniel_5":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			pchar.quest.LSC_Danny_Natan.win_condition.l1 = "location";
			pchar.quest.LSC_Danny_Natan.win_condition.l1.location = "FernandaDiffIndoor";
			pchar.quest.LSC_Danny_Natan.function = "LSC_DannyAndNatan";
			AddQuestRecord("LSC", "15");
			// следующая нода
			if (CheckCharacterItem(pchar, "keys_skel")) // идет Оле
			{
				sld = characterFromId("Ole");
				LAi_SetActorType(sld);
				LAi_ActorDialog(sld, pchar, "", -1, 0);
			}
			else
			{
				if (GetCharacterIndex("Mary") != -1) // иначе Мэри
				{
					sld = characterFromId("Mary");
					LAi_SetActorType(sld);
					LAi_ActorDialog(sld, pchar, "", -1, 0);
				}
				else // иначе завершение
				{
					chrDisableReloadToLocation = false;
					LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
				}
			}
		break;
		
		case "nathaniel_6":
			dialog.text = "Натаниэль... Натан! Чёрт бы тебя побрал! Любимый мой...";
			link.l1 = "...";
			link.l1.go = "nathaniel_7";
		break;
		
		case "nathaniel_7":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_SetActorType(pchar);
			SetMusic("music_romantic");
			bDisableCharacterMenu = true;//лоченые интерфейсы
			locCameraRotateAroundHero(0.0, 2.0, 0.0, 0.005, 0.0, 2.0, 0.0, 1000);
			DoQuestCheckDelay("LSC_DanielleRomantic", 15.0);
		break;
		
		case "nathaniel_8":
			dialog.text = "Господи, ну на кого же ты похож... До чего ты себя довёл!..(плачет) Ты никогда меня не слушаешь, никогда! Я ведь говорила тебе - не ходи в эту проклятую сельву! А ты пошёл! Зачем, Натан?!";
			link.l1 = "Данечка... прости. Я не мог поступить иначе, ты же знаешь...";
			link.l1.go = "nathaniel_9";
		break;
		
		case "nathaniel_9":
			sld = characterFromId("Blaze");
			dialog.text = "Знаю, что мог! Господи, милый... что же с тобой стало! (сквозь слёзы) Ничего, дорогой, всё будет хорошо... Я здесь. Мы отвезём тебя к мискито, к Змеиному Глазу. "+sld.name+" сказал, что шаман тебя вылечит. У нас есть корабль... Всё будет хорошо!";
			link.l1 = "Данечка, дорогая моя... любимая! То, что ты тут - уже исцелило меня наполовину. Мы пойдём, куда скажешь. К Змеиному Глазу - значит, к Змеиному Глазу.";
			link.l1.go = "nathaniel_10";
		break;
		
		case "nathaniel_10":
			dialog.text = "Собирайся. Хотя, вот я глупая... Что же тебе здесь собирать, кроме пустых бутылок? Натан...";
			link.l1 = "Данни...";
			link.l1.go = "nathaniel_11";
		break;
		
		case "nathaniel_11": // перекидываем pchar
			DialogExit();
			LAi_SetStayType(pchar);
			DeleteAttribute(pchar, "GenQuest.MusicContinue");
			SetMainCharacterIndex(GetCharacterIndex("Blaze"));
			PChar = GetMainCharacter();			
			LAi_SetPlayerType(PChar);
			sld = characterFromId("Danielle");
			sld.dialog.currentnode = "nathaniel_12";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "nathaniel_12":
			dialog.text = ""+pchar.name+", ты это... Извини меня за эту сцену. И Натана тоже.";
			link.l1 = "Данни! Какие могут быть извинения? Всё в порядке. Или ты стыдишься ваших чувств?";
			link.l1.go = "nathaniel_13";
		break;
		
		case "nathaniel_13":
			dialog.text = "Нет, не стыжусь... Просто...";
			link.l1 = "Никто и никогда не узнает о том, что здесь происходило. Обещаю. Также никто не узнает, что было с Натаном. Пираты Марун-Тауна увидят его прежним, сильным и грозным Натаниэлем Хоуком!";
			link.l1.go = "nathaniel_14";
		break;
		
		case "nathaniel_14":
			dialog.text = "Спасибо... Спасибо тебе, "+pchar.name+"! Я в долгу перед тобой... Ладно, я отведу мужа на наш корабль. Не беспокойся, я сумею сама его доставить - я запомнила дорогу. Я уложу его в постель и буду при нём. Как только закончишь все свои дела на Острове - отправимся к Змеиному Глазу. Я верю, что он вылечит Натана.";
			link.l1 = "Хорошо, Данни. Мы здесь долго не задержимся. Ты уверена, что тебе не нужна помощь?";
			link.l1.go = "nathaniel_15";
		break;
		
		case "nathaniel_15":
			dialog.text = "Уверена. Мы доберемся до корабля. Можешь идти спокойно - я не позволю моему мужу умереть!";
			link.l1 = "Данни, ты... замечательная!";
			link.l1.go = "nathaniel_16";
		break;
		
		case "nathaniel_16":
			dialog.text = "(смахивая слезу) Ступай... ступай, "+pchar.name+"... И не затягивай с отплытием, я прошу тебя!";
			link.l1 = "...";
			link.l1.go = "nathaniel_17";
		break;
		
		case "nathaniel_17":
			chrDisableReloadToLocation = false;//открыть локацию
			bDisableCharacterMenu = false;//лоченые интерфейсы
			EndQuestMovie();
			DialogExit();
			pchar.quest.LSC_NatanPassenger.win_condition.l1 = "ExitFromLocation";
			pchar.quest.LSC_NatanPassenger.win_condition.l1.location = pchar.location;
			pchar.quest.LSC_NatanPassenger.function = "LSC_SetNatanPassenger";
			pchar.quest.Saga_NatanTreatment.win_condition.l1 = "location";
			pchar.quest.Saga_NatanTreatment.win_condition.l1.location = "Miskito_village";
			pchar.quest.Saga_NatanTreatment.function = "Saga_NatanPrepareTreatment";
			pchar.questTemp.Saga.BaronReturn = "shamane";
			AddQuestRecord("BaronReturn", "11");
			// открываем вход к Мэри
			if (GetCharacterIndex("Mary") != -1)
			{
				for (i=0; i<=3; i++)
				{
					LocatorReloadEnterDisable("LostShipsCity_town", "reload6"+i, false);
				}
			}
			else
			{
				bQuestDisableMapEnter = false; //открыть карту
				DeleteAttribute(pchar, "GenQuest.CannotWait");//можно мотать время
			}
		break;
		
		case "treatment":
			dialog.text = "Ну что? Шаман взялся за лечение? Скажи, что это так!";
			link.l1 = "Даниэль, Натан остаётся у Змеиного Глаза. Один. Шаман попросил, чтобы никто не мешал его обрядам, в том числе и ты. Он пообещал вылечить Натаниэля за месяц.";
			link.l1.go = "treatment_1";
		break;
		
		case "treatment_1":
			dialog.text = "Ты знаешь, "+pchar.name+", вот только теперь я спокойна. У меня глубокая уверенность в том, что этот шаман вернёт моего мужа к нормальной жизни. Я без колебаний оставляю его у Змеиного Глаза, потому что если он ему не поможет - то не поможет никто.";
			link.l1 = "Всё будет хорошо, Данни. Змеиный Глаз не обманул ещё ни разу. Я верю ему.";
			link.l1.go = "treatment_2";
		break;
		
		case "treatment_2":
			dialog.text = "Я тоже ему верю. Я останусь в твоей команде ещё на некоторое время, "+pchar.name+", ты не возражаешь? Нам нужно найти главного мерзавца и виновника наших бед - скотину Джекмана. Это он организовал засаду на Натана! Он захватил его место в Марун-Тауне! Он украл 'Центурион', наш фрегат!";
			link.l1 = "Я согласен. С Джекманом надо разобраться радикально, ибо пока он жив, ни тебе, ни мне, ни Натану покоя не будет. Однако сделать это будет не так просто.";
			link.l1.go = "treatment_3";
		break;
		
		case "treatment_3":
			if (!CheckAttribute(pchar, "questTemp.Saga.DodsonDie")) sTemp = "Акулу Додсона";
			else sTemp = "Маркуса Тиракса";
			dialog.text = "У тебя есть какой-то план, "+pchar.name+"?";
			link.l1 = "Пока нет. Надо отправлиться к Яну Свенсону и посоветоваться с ним. Будем последовательны - сейчас нужно выдвинуть "+sTemp+" на пост главы Берегового братства. А для этого нужно заручиться поддержкой всех пиратских баронов.";
			link.l1.go = "treatment_4";
		break;
		
		case "treatment_4":
			dialog.text = "Хорошо. Пойдём к Свенсону. Послушаем, что этот старый пень скажет...";
			link.l1 = "Не будь столь критична к Яну. Да и в конце концов, помирились бы вы с ним, что ли... одно дело делаем!";
			link.l1.go = "treatment_5";
		break;
		
		case "treatment_5":
			dialog.text = "Ну разве что из уважения к тебе... Ладно, "+pchar.name+", прости меня. Я не хотела оскорбить Свенсона, просто я вся на нервах в последнее время. Я не буду больше.";
			link.l1 = "Вот и славно. Данни, всё будет хорошо. Обещаю тебе!";
			link.l1.go = "treatment_6";
		break;
		
		case "treatment_6":
			dialog.text = "Я верю тебе, "+pchar.name+". Верю, как никому другому. Пойдём к Свенсону?";
			link.l1 = "В путь, Данни!";
			link.l1.go = "Dolly_4";
			AddQuestRecord("BaronReturn", "13");
		break;
		
		case "islatesoro":
			dialog.text = "Да? Тогда я тебя внимательно слушаю. О чём речь?";
			link.l1 = "У тебя есть какие-нибудь предположения, где может скрываться Джекман? Ты знаешь этого ублюдка получше меня - может, у него есть какие-то места, базы...";
			link.l1.go = "islatesoro_1";
		break;
		
		case "islatesoro_1":
			dialog.text = "Да чёрт его знает. Якоб всегда был довольно скрытен. Про какие-то его укромные местечки я не слышала. Тут лучше попробовать рассудить логично... Давай ещё раз прочтём письмо, которое ты нашёл у Валета. Может, что-то высмотрим.";
			link.l1 = "Давай...";
			link.l1.go = "islatesoro_2";
		break;
		
		case "islatesoro_2":
			RemoveItems(pchar, "letter_chad", 1);
			dialog.text = "Так... Здесь упоминается Исла Тесоро и какое-то завещание... Тебе это ни о чём не говорит?";
			link.l1 = "Мы с Яном считаем, что Блейза Шарпа на Исла Тесоро убрал Джекман, свалив вину на Акулу. А завещание... девка... это он Элен имеет в виду... Чёрт возьми, да как же я раньше не догадался! Этот подонок наверняка ошивается где-то у Исла Тесоро!";
			link.l1.go = "islatesoro_3";
		break;
		
		case "islatesoro_3":
			dialog.text = "Тогда не будем терять времени, "+pchar.name+"?";
			link.l1 = "Да. Отправляемся к Исла Тесоро. Старина 'Марлин' послужит нам для этого рейда как нельзя лучше.";
			link.l1.go = "islatesoro_4";
		break;
		
		case "islatesoro_4":
			DialogExit();
			AddQuestRecord("BarbTemptation", "18");
			pchar.questTemp.Saga.BarbTemptation = "islatesoro";
			// ставим прерывание на Исла-Тесоро
			pchar.quest.Saga_AttackJackman.win_condition.l1 = "location";
			pchar.quest.Saga_AttackJackman.win_condition.l1.location = "Bermudes";
			pchar.quest.Saga_AttackJackman.function = "Saga_CheckJackmanBermudes";
		break;
		
		case "after_boarding":
			dialog.text = "Ну наконец-то этот ублюдок сдох... Даже не верится - я снова на палубе 'Центуриона'! Я знаю здесь каждый гвоздь и мне кажется, что корабль тоже узнал меня.";
			link.l1 = "Теперь он снова твой, Данни. Твой и Натаниэля.";
			link.l1.go = "after_boarding_1";
		break;
		
		case "after_boarding_1":
			PlaySound("VOICE\Russian\saga\Denny Hawk-03.wav");
			dialog.text = "Ты не представляешь, как я рада. Натаниэль часто вспоминал наш корабль - весть о том, что он снова наш, а не в руках подлеца Джекмана, прибавит ему сил.";
			link.l1 = "Что ты сейчас будешь делать, Данни?";
			link.l1.go = "after_boarding_2";
		break;
		
		case "after_boarding_2":
			dialog.text = "Что? Отведу корабль в Шарптаун, отремонтирую, найму хотя бы минимум команды и пойду в Блювельд. Попрошу Яна Свенсона, чтобы его люди присмотрели за 'Центурионом', а сама отправлюсь к мискито - буду ждать, пока Змеиный Глаз вылечит моего мужа.";
			link.l1 = "Ты пойдёшь к Яну Свенсону? Право, я удивлён...";
			link.l1.go = "after_boarding_3";
		break;
		
		case "after_boarding_3":
			dialog.text = ""+pchar.name+", в этом твоя заслуга. Я долго думала о твоих словах: 'мы делаем одно дело'. Помнишь? Я хочу помириться со Свенсоном - ведь он, хоть и косвенно, но помог вернуть мне Натана. Да и в конце-концов, хватит ссор.";
			link.l1 = "Разумные слова, Данни! Когда Натаниэль выздоровеет, он снова должен занять своё положенное место в Марун-Тауне.";
			link.l1.go = "after_boarding_4";
		break;
		
		case "after_boarding_4":
			dialog.text = "Так-то оно так... Но пиратский барон -  выборная должность. Вдруг сходка Марун-Тауна проголосует иначе?";
			link.l1 = "Предоставь это Свенсону. Он уговорит кого угодно. Уничтожение Джекмана тоже сыграет свою роль.";
			link.l1.go = "after_boarding_5";
		break;
		
		case "after_boarding_5":
			dialog.text = "Хорошо. Теперь нам со Свенсоном придётся стать друзьями в любом случае... "+pchar.name+"! Я хочу от всей души поблагодарить тебя за то, что ты сделал для меня и Натана. Ты фактически спас моего мужа, а теперь ещё и вернул всё потерянное нами. Я в неоплатном долгу перед тобой.";
			link.l1 = "Брось, Данни. Мы же друзья.";
			link.l1.go = "after_boarding_6";
		break;
		
		case "after_boarding_6":
			dialog.text = "Я хочу, чтобы ты знал - в Марун-Тауне тебе всегда будут рады. Когда будет возможность - обязательно загляни к нам. Мы с Натаниэлем придумаем, как тебя отблагодарить.";
			link.l1 = "Да Бог с тобой, Даниэль. Но я с удовольствием принимаю твое приглашение. Посидим, выпьем, вспомним, как вы с Натаном топили Ван дер Декена...";
			link.l1.go = "after_boarding_7";
		break;
		
		case "after_boarding_7":
			dialog.text = "Это Натан тебе рассказал? Ох, не напоминай мне об этом...";
			link.l1 = "Ладно, Данни. Тебе предстоит ещё много хлопот со своим кораблём, а мне пора навестить заклятых друзей - Маркуса и Барбазона. Но сначала я переверну вверх дном эту каюту, уж не взыщи: я уверен, что в сундуках у Джекмана лежит много вещей, которые меня заинтересуют.";
			link.l1.go = "after_boarding_8";
		break;
		
		case "after_boarding_8":
			dialog.text = "Да пожалуйста, неужели ты думаешь, что я стану возражать?";
			link.l1 = "Чудесно. А вообще, мне даже как-то жаль с тобой расставаться, Данни... Увидимся в Марун-Тауне!";
			link.l1.go = "after_boarding_9";
		break;
		
		case "after_boarding_9":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "OpenTheDoors", -1);
			LAi_SetHP(npchar, 280, 280); 
			LAi_SetImmortal(npchar, false); // если сработало
			pchar.GenQuest.CannotTakeShip = true; // нельзя захватить
			DoQuestFunctionDelay("Saga_CheckJackmanCabinItems", 5.0); // первая проверка через 5 сек
			AddCharacterExpToSkill(pchar, "Leadership", 300);
		break;
		
		// в Марун-Тауне
		case "marun_town":
			dialog.text = ""+pchar.name+", очень рада тебя видеть! Мы снова в Марун-Тауне, и Натан занял своё законное место. Кстати, все в посёлке были этому очень рады. Теперь опять всё будет по-прежнему! Огромное тебе спасибо за твою бескорыстную помощь!\nЯ хочу сделать тебе подарок. Вот, возьми. Этот талисман очень поможет тебе в бою. А следуя этому рецепту ты всегда сможешь создать его самостоятельно.";
			link.l1 = "Спасибо, Данни!";
			link.l1.go = "marun_town_1";
		break;
		
		case "marun_town_1":
			GiveItem2Character(pchar, "totem_12"); 
			GiveItem2Character(pchar, "recipe_totem_12"); 
			Log_Info("Вы получили талисман");
			Log_Info("Вы получили рецепт талисмана");
			PlaySound("interface\important_item.wav");
			dialog.text = "Ещё не всё. Я нашла в резиденции в шкафу два сундука с золотом. Оно наверняка принадлежало Джекману. Возьми и их в знак моей признательности. И не смей отказываться! Я знаю, сколько ты денег истратил, пока решал мои с Натаном проблемы.";
			link.l1 = "Хорошо, хорошо, Данни, не откажусь!";
			link.l1.go = "marun_town_2";
		break;
		
		case "marun_town_2":
			TakeNItems(pchar, "chest", 2); 
			Log_Info("Вы получили сундуки с дублонами");
			PlaySound("interface\important_item.wav");
			dialog.text = "Вот и славно! "+pchar.name+", я хочу, чтобы ты знал: ты - наш лучший друг. Мы с Натаном всегда будем рады видеть тебя в Марун-Тауне! Заходи почаще!";
			link.l1 = "Спасибо! Мне тоже будет очень приятно видеть вас, так что ждите в гости!";
			link.l1.go = "exit";
			NextDiag.TempNode = "marun_town_3";
		break;
		
		case "marun_town_3":
			dialog.text = "Рада тебя видеть, "+pchar.name+"! Рому, вина? Может, девочку?";
			link.l1 = "Спасибо, Данни! Я просто зашёл вас проведать...";
			link.l1.go = "exit";
			NextDiag.TempNode = "marun_town_3";
		break;
		
	// ------------------------------------------- провалы Саги ------------------------------------------------
		case "failcenturion":
			dialog.text = "Ну наконец-то мы с Натаном сможем вздохнуть спокойно! Этот проклятый ублюдок Джекман сдох!.. Жаль, конечно, 'Центуриона', но я всё равно уже с ним давно попрощалась, когда этот мерзавец отобрал его у меня. Так что я особо не расстраиваюсь.";
			link.l1 = "Зато я расстраиваюсь, и очень. Ну надо же было оказаться таким растяпой! Вместе с этим кораблём на дно ушли все улики, которые могли сыграть на руку при выборе нового главы Берегового братства. А теперь... всё пропало.";
			link.l1.go = "failcenturion_1";
		break;
		
		case "failcenturion_1":
			dialog.text = "Да не печалься ты так! В жизни всякое бывает. В другой раз обзательно повезёт... Ладно. Я хочу от всей души поблагодарить тебя за то, что ты сделал для меня и Натана. Ты фактически спас моего мужа. Я в неоплатном долгу перед тобой\nЯ хочу, чтобы ты знал - в Марун-Тауне тебе всегда будут рады. Когда будет возможность - обязательно загляни к нам. Мы с Натаниэлем придумаем, как тебя отблагодарить.";
			link.l1 = "Хорошо, Данни. Обязательно загляну к вам в гости. Ты уже уходишь?";
			link.l1.go = "failcenturion_2";
		break;
		
		case "failcenturion_2":
			dialog.text = "Да, отправлюсь к мискито - надеюсь, Змеиный Глаз уже поставил Натана на ноги. А затем мы вернёмся в Марун-Таун.";
			link.l1 = "Хех, я уже так привык к тебе, что жаль с тобой расставаться... Удачи, Даниэль!";
			link.l1.go = "failcenturion_3";
		break;
		
		case "failcenturion_3":
			DialogExit();
			RemovePassenger(pchar, npchar);
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "Saga_FailCenturion", 10.0);
			npchar.greeting = "danny_2";
		break;
		
		//--> ----------------------------------- офицерский блок ------------------------------------------
		case "Danielle_officer":
			dialog.text = "Ну что тебе, капитан?";
			if (CheckAttribute(pchar, "questTemp.Saga.BarbTemptation") && pchar.questTemp.Saga.BarbTemptation == "danielle")
			{
				Link.l3 = "Данни, я бы хотел с тобой посоветоваться.!";
				Link.l3.go = "islatesoro";
			}
			Link.l1 = "Слушай мой приказ!";
            Link.l1.go = "stay_follow";
			link.l2 = "Пока ничего. Вольно!";
			link.l2.go = "exit";
			NextDiag.TempNode = "Danielle_officer";
			sld = characterFromId("Danielle");
		    sld.HoldEquip = true; // лесник -  не отдавать саблю и пистоль для текущей игры. поэтому так . другого способа не нашел						 
		break;
		
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
		
		case "":
			dialog.text = "";
			link.l1 = "";
			link.l1.go = "";
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
	}
}