// диалог прочих НПС по квесту Саги
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i, iTemp;
	string sTemp;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "Вы что-то хотели?";
			link.l1 = "Да нет, пожалуй, ничего.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
//---------------------------------------------Джимми в доме в Марун-Тауне------------------------------------
		case "Jimmy":
			dialog.text = "Чего тебе надо? Не видишь - горе у меня! Проваливай, пока я не спустил тебя с лестницы! ";
			link.l1 = "Сначала купи себе дом больше, чем в один этаж, а потом уже с лестницы спускай, герой выискался...";
			link.l1.go = "Jimmy_1_1";
			link.l2 = "Кто тебя так расстроил, Джимми? Не пить мне больше рому, если в этом не замешана какая-нибудь красотка! Только они могут заставить такого морского волка, как ты, бросаться на старых друзей, толком не разглядев...";
			link.l2.go = "Jimmy_1_2";
		break;
		
		case "Jimmy_1_1":
			dialog.text = "Ненавижу чистоплюев вроде тебя! Вечно вам достаются лучшие куски. Мне не дали прикончить одного выскочку, но на тебе я отыграюсь сполна!";
			link.l1 = "...";
			link.l1.go = "Jimmy_fight";
		break;
		
		case "Jimmy_fight":
			chrDisableReloadToLocation = true;//закрыть локацию
			DialogExit();
			LAi_SetImmortal(npchar, false);
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "Saga_KillJimmy");
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
		case "Jimmy_1_2":
			dialog.text = "Да?! Мы знакомы? Убей, не помню...";
			link.l1 = "Да это же я, "+pchar.name+"! Славно мы посидели с тобой в Блювельде после того, как ты чуть было не вспорол брюхо этому наглецу в мундире. Как его звали, кстати? Вылетело из головы... Попадется он мне в море, не посмотрю на пушки его корвета!";
			link.l1.go = "Jimmy_2";
		break;
		
		case "Jimmy_2":
			dialog.text = "Его звали Артур! Артур Донован, капитан корвета 'Арбутус'! Гнусный мерзавец! Так ты говоришь, что я его чуть не отправил к дьяволу?";
			link.l1 = "Так и было! Ты набросился на него как кашалот на креветку. У него не было шансов, если бы не вмешались твои ребята. Прости их, им просто не хотелось, чтобы тебя повесили за убийство морского офицера.";
			link.l1.go = "Jimmy_3";
		break;
		
		case "Jimmy_3":
			dialog.text = "Аргх! Если бы у меня был корабль! Этого мерзавца легко найти около Антигуа... Ха! Если ты отправишь его на дно - я твой должник!";
			link.l1 = "По рукам, ха-ха! А что, Румба действительно стоит твоих страданий?";
			link.l1.go = "Jimmy_4";
		break;
		
		case "Jimmy_4":
			dialog.text = "Что ты! Лучше нее я не встречал до сих пор. Но она только смеется надо мной. За этой русалкой кто только не охотится. Тут мне по большому секрету сказали, что наш Якоб разыскивает девушку, по всем приметам похожую на мою Румбу. И этот туда же! Как я теперь могу выполнять его приказы?";
			link.l1 = "Тише, приятель! У стен могут быть уши... А с чего ты взял, что Джекман ищет именно Румбу?";
			link.l1.go = "Jimmy_5";
		break;
		
		case "Jimmy_5":
			dialog.text = "Ну как же! Он ищет какого-то Генри Висельника, Глэдис Чандлер и девушку со светлыми волосами и голубыми глазами, примерно двадцати лет от роду. Ее опекуншей должна быть некая Глэдис Чандлер родом из Белиза. Все сходится.";
			link.l1 = "Постой! У Глэдис же другая фамилия.";
			link.l1.go = "Jimmy_6";
		break;
		
		case "Jimmy_6":
			dialog.text = "Джимми хитрый! Его на мякине не проведешь! Я под Румбу давно клинья подбиваю и втихаря выяснил, что Глэдис вышла замуж за Шона Мак Артура как раз двадцать лет назад. А до этого она жила в Белизе. А ее первого мужа звали Пит Чандлер\nБеднягу Пита кто-то зашиб по пьяни. Поговаривают, что сам Мак Артур и приложил к этому руку, поскольку запал на толстушку Глэдис. Она стала вдовой с младенцем на руках. Так вот ребенок этот ненамного пережил своего папашу и помер от лихоманки\nА вскоре Глэдис с Шоном появились в Блювельде с живой девчушкой на руках, которую записали как дочку Мак Артура. Когда она успела родить второго? Сечешь?";
			link.l1 = "Ты кому-нибудь уже рассказал про это?";
			link.l1.go = "Jimmy_7";
		break;
		
		case "Jimmy_7":
			dialog.text = "Пока нет. Смотри, держи язык за зубами, а не то... ты меня знаешь!";
			link.l1 = "Ага, знаю. Это поганый язык, который готов разболтать любые тайны первому встречному. Правильно Румба послала тебя куда подальше, трепло...";
			link.l1.go = "Jimmy_8_1";
			link.l2 = "О чем речь! Я буду нем, как могила! А сейчас мне пора. Прощай, Джимми.";
			link.l2.go = "Jimmy_8_2";
		break;
		
		case "Jimmy_8_1":
			dialog.text = "Что... Что ты сказал?!";
			link.l1 = "Больше ты это никому не расскажешь...";
			link.l1.go = "Jimmy_fight";
			pchar.questTemp.Saga.Jimmysecret = "true";
		break;
		
		case "Jimmy_8_2":
			DialogExit();
			pchar.questTemp.Saga = "jackman";
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeday = 0;
			AddQuestRecord("Saga", "4_1");
		break;
// <-- Джимми 
		
//-------------------------------------------корвет Донована, абордаж-----------------------------------------
		//Донован
		case "Donovan_abordage":
			PlaySound("VOICE\Russian\saga\Artur Donovan.wav");
			dialog.text = "Аргх, гнусный мерзавец!";
			link.l1 = "Это кто еще из нас мерзавец, сударь! Где Румба?";
			link.l1.go = "Donovan_abordage_1";
		break;
		
		case "Donovan_abordage_1":
			dialog.text = "Какой еще Румба? У меня нет на корабле негодяев, отзывающихся на клички. Это английское военное судно!";
			link.l1 = "Не дури, Донован. Ты прекрасно понимаешь, о ком я говорю. Где девушка? Где Элен, я тебя спрашиваю?";
			link.l1.go = "Donovan_abordage_2";
		break;
		
		case "Donovan_abordage_2":
			dialog.text = "Элен? На моем судне нет портовых шлюх, гнусное отродье!";
			link.l1 = "Нет? А вот я так не считаю, потому что одна из них стоит сейчас прямо передо мной... И, как я вижу, дальнейший разговор не имеет смысла. Сдохни, тварь!";
			link.l1.go = "Donovan_abordage_3";
		break;
		
		case "Donovan_abordage_3":
			chrDisableReloadToLocation = true;//закрыть локацию
			DialogExit();
			LAi_SetCurHPMax(npchar);
			QuestAboardCabinDialogFree();
			LAi_group_SetRelation(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck(LAI_GROUP_BRDENEMY, "Saga_AfterDonovanBoarding");
			AddDialogExitQuest("MainHeroFightModeOn");
			pchar.questTemp.Saga.Takehelen = "true";//признак, что абордировали судно
		break;
		
		//наш матрос
		case "Tempsailor":
			dialog.text = "Капитан, мы обыскали каюты и трюм, как вы и говорили. В трюме нашли девушку, закованную в кандалы...";
			link.l1 = "Вот мерзавец! Я так и думал... Девушку освободили?";
			link.l1.go = "Tempsailor_1";
		break;
		
		case "Tempsailor_1":
			dialog.text = "Конечно, капитан. Она уже на нашем корабле, в безопасности.";
			link.l1 = "Молодцы! Отведите ее ко мне в каюту, я хочу немедленно побеседовать с ней.";
			link.l1.go = "Tempsailor_2";
		break;
		
		case "Tempsailor_2":
			dialog.text = "Есть, капитан!";
			link.l1 = "...";
			link.l1.go = "Tempsailor_3";
		break;
		
		case "Tempsailor_3":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "OpenTheDoors", 10.0);
		break;
		//<-- абордаж корвета Донована
		
//----------------------------------------поиск Энрике Гонсалеса, Картахена----------------------------------
		//фальшивый Гонсалес №1, дом
		case "GonsalesA":
			dialog.text = "Что вам угодно, сeньор?";
			link.l1 = "Ну здравствуй, Висельник! Привет тебе от капитана Бучера.";
			link.l1.go = "GonsalesA_1_1";
			link.l2 = "Меня зовут Шарль де Мор. Я разыскиваю сына сeньоры Гонзалес Энрике по просьбе ее старого друга. Мне кажется, что это вы...";
			link.l2.go = "GonsalesA_2_1";
		break;
		
		case "GonsalesA_1_1":
			dialog.text = "Какого черта! Я не знаю никакого Бучера!";
			link.l1 = "Брось кривляться, Генри. Расскажи мне, зачем тебя ищут пираты Джекмана, и я не сделаю тебе больно.";
			link.l1.go = "GonsalesA_1_2";
		break;
		
		case "GonsalesA_1_2":
			dialog.text = "Караул! Пираты! Убивают!";
			link.l1 = "Тише, придурок! На твои вопли сбежится полгорода. Ах, вот ты так?!";
			link.l1.go = "GonsalesA_1_fight";
		break;
		
		case "GonsalesA_1_fight":
			DialogExit();
			SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
			LAi_group_MoveCharacter(NPChar, "EnemyFight");
			LAi_group_Attack(NPChar, Pchar);
			LAi_group_SetCheck("EnemyFight", "Saga_KillGonsalesA");
			AddDialogExitQuest("MainHeroFightModeOn");
			pchar.questTemp.Saga.Trap = "true";
		break;
		
		case "GonsalesA_2_1":
			dialog.text = "Хм... Любезный, вы, вероятно, ошиблись. Я воспитывался в чужой семье и свою мать не помню. Я взял фамилию своего опекуна. Фамилия моей матери мне не известна. Но вряд ли она тоже была Гонзалес. Вы можете навести обо мне справки в мэрии, да и любой старожил города подтвердит мои слова. Мой названый отец был человек известный, и этот дом перешел ко мне от него по наследству, так как своих детей у него не было, а...";
			link.l1 = "Извините. Видимо, я действительно ошибся. Всего хорошего.";
			link.l1.go = "GonsalesA_2_2";
		break;
		
		case "GonsalesA_2_2":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			chrDisableReloadToLocation = false;//открыть локацию
			AddQuestRecord("Saga", "17");
		break;
		
		// фальшивый Гонсалес №2, улицы
		case "GonsalesB":
			PlaySound("VOICE\Russian\citizen\Pirati v Gorode-08.wav");
			dialog.text = "Я гляжу, тебе тесак мой приглянулся. Хочешь, продам? Возьму недорого, а то трубы горят, а в кармане только вошь на аркане.";
			link.l1 = "На кой ляд он мне сдался? Меня просил передать тебе привет Лесной дьявол.";
			link.l1.go = "GonsalesB_1_1";
			if (sti(pchar.money) >= 1000)
			{
				link.l2 = "Да уж. Тесак у тебя знатный. Сколько хочешь за него?";
				link.l2.go = "GonsalesB_2_1";
			}
		break;
		
		case "GonsalesB_1_1":
			dialog.text = "Лучше бы он передал для меня сотню песо! ";
			link.l1 = "Так ты знаешь Свенсона?";
			link.l1.go = "GonsalesB_1_2";
		break;
		
		case "GonsalesB_1_2":
			dialog.text = "Да пошел ты со своим Свенсоном к дьяволу! Хошь к лесному, хошь к морскому. Не желаешь помочь больному человеку и купить тесак, так я его тебе даром в корму запихаю!";
			link.l1 = "Да? Ну давай, посмотрим, как ты это сделаешь, синяя рожа!";
			link.l1.go = "GonsalesB_1_fight";
		break;
		
		case "GonsalesB_1_fight":
			chrDisableReloadToLocation = true;
			DialogExit();
			LAi_group_MoveCharacter(NPChar, "EnemyFight");
			LAi_group_Attack(NPChar, Pchar);
			LAi_group_SetCheck("EnemyFight", "Saga_KillGonsalesB");
			AddDialogExitQuest("MainHeroFightModeOn");
			pchar.questTemp.Saga.Trap = "true";
		break;
		
		case "GonsalesB_2_1":
			dialog.text = "Сразу видно бывалого человека! Тысяча песо - и он твой.";
			link.l1 = "Заметано!";
			link.l1.go = "GonsalesB_2_2";
		break;
		
		case "GonsalesB_2_2":
			AddMoneyToCharacter(pchar, -1000);
			GiveItem2Character(pchar, "blade_10");
			RemoveCharacterEquip(npchar, BLADE_ITEM_TYPE);
			dialog.text = "Таких висельников во всей Картахене всего два – у меня и старика Альвареса на маяке. Но тот свой хангер ни за что не продаст. Хоть он и корчит из себя святошу, но я бывшего пирата за милю узнаю. Этот клинок для него навроде талисмана\nВидно есть, что вспомнить бродяге. Недаром он каждый месяц в церковь бегает - не иначе грехи спокойно спать не дают.";
			link.l1 = "А ты, я смотрю, тоже хлебнул вольной жизни. Не про тебя ли мне Свенсон все уши прожужжал? Говорит, как встретишь в Картахене Генри, передавай ему от меня привет и зови в гости.";
			link.l1.go = "GonsalesB_2_3";
		break;
		
		case "GonsalesB_2_3":
			dialog.text = "Свенсон? Не знаю такого. Меня зовут Энрике Гальярдо. Но если у твоего Свенсона найдется для меня бутылка рома, то я согласен побыть для него Генри. Меня хоть клистиром назови, только в гузно не суй. Ну что, рванули?";
			link.l1 = "Не сегодня. Свенсон далеко, а трактир рядом. Ты теперь при деньгах, так что бывай, Энрике.";
			link.l1.go = "GonsalesB_2_4";
		break;
		
		case "GonsalesB_2_4":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload4_back", "none", "", "", "", 20.0);
			npchar.lifeday = 0;
			AddQuestRecord("Saga", "19");
			pchar.questTemp.Saga = "ortega";
			Saga_SetOrtega();
		break;
		
		//настоящий Гонсалес - Ортега, маяк
		case "Ortega":
			dialog.text = "Я не жду гостей сегодня, как, впрочем, и в любой другой день. Что тебе нужно?";
			link.l1 = "Ну здравствуй, Висельник. Меня послал к тебе Лесной дьявол. Хорошо, что я успел найти тебя раньше Джекмана. Его люди ищут тебя по всем Карибам. На твое счастье, Генри, только Свенсон знает, откуда ты родом. Он попросил предупредить тебя.";
			link.l1.go = "Ortega_1";
		break;
		
		case "Ortega_1":
			dialog.text = "Так вот оно что... Стало быть, Свенсон до сих пор жив и не забыл старого друга. Сколько крови утекло с тех пор, когда я впервые увидел его салагой с потрепанного брига... Как быстро пролетела жизнь, и мне уже совсем немного осталось\nХотелось умереть своей смертью на этом пустыре подальше от людей, и поближе к морю. Но если Джекман снова появился на Карибах, то в покое он меня не оставит. Задолжал я его хозяину не по своей воле. Но кто мне теперь поверит\nСмерти я не боюсь, я боюсь боли. А Джекман большой мастак по этой части. При одной мысли об этом у меня в глазах темнеет и сердце останавливается.";
			link.l1 = "Если ты про Бучера, то его повесили двадцать лет назад. Так что долг тебе возвращать некому. А если боишься Джекмана, можешь передать свой долг мне. Думаю, моя встреча с ним неизбежна, и рассказать о ней сможет лишь один из нас.";
			link.l1.go = "Ortega_2";
		break;
		
		case "Ortega_2":
			dialog.text = "Таких, как капитан Бучер, мало повесить один раз. Бывший палач Сент-Джонса мог бы рассказать много интересного о мертвецах, которые возвращаются с того света. Впрочем, Якоб многому научился у капитана и я даже не знаю, с кем из них я бы предпочел не встречаться подольше.";
			link.l1 = "Зачем ты понадобился Джекману?";
			link.l1.go = "Ortega_3";
		break;
		
		case "Ortega_3":
			dialog.text = "Я должен был передать золото одной вдове на содержание дочери Бучера. А что ты так удивился? Да, у капитана незадолго до гибели 'Нептуна' родилась дочь. Он не смог за ней вернуться вовремя и послал меня, чтобы я позаботился о малышке и ее кормилице.";
			link.l1 = "Кормилицу звали Глэдис Чандлер?";
			link.l1.go = "Ortega_4";
		break;
		
		case "Ortega_4":
			dialog.text = "Не прикидывайся простаком. Если Джекман ищет меня, значит, ему нужна дочь Бучера, а не мой старый хангер. И ты наверняка знаешь, что помимо Висельника он ищет женщину по имени Глэдис родом из Белиза и ее воспитанницу. Будь честным со мной, и может быть я тебе поверю.";
			link.l1 = "Что ты должен был сказать Глэдис?";
			link.l1.go = "Ortega_5";
		break;
		
		case "Ortega_5":
			dialog.text = "Ничего. Я должен был показать ей перстень Бучера. По нему она признала бы меня, как гонца от капитана. А еще я должен был передать ей сундук с золотыми дублонами на содержание крошки. Чтобы забрать этот перстень у одного негодяя, мне пришлось его убить. Из-за этого я задержался на Антигуа на целый месяц\nА когда наконец добрался до Белиза Глэдис и след простыл, а город лежал в руинах после набега испанцев. Она успела продать свой дом и укатила куда-то вместе с новым хахалем, прихватив малютку Элен с собой. Надеюсь, она позаботилась о ней, а не продала цыганам или в бордель на забаву.";
			link.l1 = "Дочь Бучера звали Элен?";
			link.l1.go = "Ortega_6";
		break;
		
		case "Ortega_6":
			dialog.text = "Именно так. В честь матери Бучера. Если ты не боишься живых мертвецов и пиратов с мертвыми глазами, как у моего приятеля Якоба, я могу отдать тебе перстень и золото. Я не тронул его. С голоду подыхал, но не тронул.  Отдай эту посылку, кому сочтешь нужным. А взамен я попрошу те...";
			link.l1 = "Что с тобой, Генри?!";
			link.l1.go = "Ortega_7";
		break;
		
		case "Ortega_7":
			dialog.text = "Те... бя... Попро... ах!";
			link.l1 = "Нет!";
			link.l1.go = "Ortega_8";
		break;
		
		case "Ortega_8":
			DialogExit();
			LAi_SetImmortal(npchar, false);
			LAi_KillCharacter(npchar);
			AddQuestRecord("Saga", "20");
			pchar.questTemp.Saga = "svenson1";
			PlaySound("interface\important_item.wav");
			GiveItem2Character(pchar, "chest");
			GiveItem2Character(pchar, "bucher_ring"); //перстень Бучера
			//таймер на возврат смотрителя
			SetFunctionTimerCondition("Saga_LightmanReturn", 0, 0, 10, false);
			//ставим прерывания, если ГГ наследил в городе
			if (CheckAttribute(pchar, "questTemp.Saga.Trap"))
			{
				pchar.quest.Saga_Trap.win_condition.l1 = "location";
				pchar.quest.Saga_Trap.win_condition.l1.location = "Mayak11";
				pchar.quest.Saga_Trap.function = "Saga_CreateTrapBandos";
				CoolTraderHunterOnMap();
			}
			AddCharacterExpToSkill(pchar, "Sneak", 50);//скрытность
		break;
		
		//бандиты в поисках Гонсалеса, маяк
		case "saga_trap":
			dialog.text = "А-а, вот и наш любопытный дружок! Успел таки добраться до Гонсалеса? Молодец, что вывел нас на него... более ты нам не нужен. Ребята, валим этого пижона!";
			link.l1 = "Ну, держитесь, крабьи потроха!";
			link.l1.go = "saga_trap_1";
		break;
		
		case "saga_trap_1":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешить драться
			int n = makeint(MOD_SKILL_ENEMY_RATE/3);
			for (i=1; i<=3+n; i++)
			{	
				sld = characterFromId("sagatrap_sold_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "OpenTheDoors");
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		//<-- поиск Гонсалеса, Картахена
		
//--------------------------------------------НПС по квесту Возвращение барона---------------------------------
		
		// доминиканский вождь
		case "DominicaHead":
			dialog.text = "Ахой! Ахой! Великий Кукулькан требовать новый жертва! О-ей! Дух великого воина прошлого прийти наш деревня, дабы быть принесенным великий Кукулькан! О-ей! Все склониться перед духом великий воин!";
			link.l1 = "(глухо) Черт возьми, куда я попал?";
			link.l1.go = "DominicaHead_1";
			NextDiag.TempNode = "DominicaHead";
		break;
		
		case "DominicaHead_1":
			dialog.text = "О-ей! Великий воин желать быть пожран великий Кукулькан! Солнце становиться выше, тени короче! Великий Кукулькан скоро оживать! Мы отвести тебя к нему, о великий воин, и ты продолжить свой путь по стране предков!";
			link.l1 = "(глухо) Ну и вздор... Опять Кукулькан? Эй, вождь, я прибыл с миром! Я пришел...";
			link.l1.go = "DominicaHead_2";
		break;
		
		case "DominicaHead_2":
			dialog.text = "О-ей! Великий воин сказать мне, что желать быть принесенным в жертву Кукулькан немедля. О, великий воин! Мы отправиться к Кукулькан сейчас и ждать, когда его дух посетит нас! Воины! Нам выпасть огромный честь - провести дух предка к Кукулькан!";
			link.l1 = "(глухо) Вот дубина... Ладно, придется идти с ними. Хорошо, хоть не напали всем скопом - в этой штуковине я бы от них не отбился...";
			link.l1.go = "DominicaHead_3";
		break;
		
		case "DominicaHead_3":
			DialogExit();
			LAi_SetActorType(pchar);
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocator(npchar, "reload", "reload1_back", "Saga_DominicaDollyReload", -1);
			LAi_ActorFollow(pchar, npchar, "", -1);
			for (i=2; i<=10; i++)
			{
				sld = characterFromId("Dominica_ind_"+i);
				LAi_SetActorType(sld);
				LAi_ActorFollow(sld, npchar, "", -1);
			}
		break;
		
		case "DominicaHead_4":
			dialog.text = "Мы прийти к Кукулькан, великий дух предка. Скоро солнце идти вниз, тени расти, и Кукулькан явиться к нам. Жди, великий воин...";
			link.l1 = "(глухо) Все с тобой понятно, индейский военачальник...";
			link.l1.go = "DominicaHead_5";
		break;
		
		case "DominicaHead_5":
			DialogExit();
			bDisableCharacterMenu = true;//лочим Ф2
			AddQuestRecord("BaronReturn", "7");
			LAi_SetActorType(pchar);
			DoQuestCheckDelay("Saga_DominicaDollyWait", 5.0);
			pchar.questTemp.Saga.BaronReturn = "third_teleport";
		break;
		
		case "DominicaHead_6":
			dialog.text = "Кукулькан ожить! Кукулькан с нами! Великий воин может быть принесен жертва Кукулькан! Воины, склонить головы перед великий дух предка!";
			link.l1 = "(глухо) Не мешай, вождь. Я сам принесу себя в жертву Кукулькану. Не в первый раз...";
			link.l1.go = "DominicaHead_7";
		break;
		
		case "DominicaHead_7":
			DialogExit();
			bDisableCharacterMenu = false;//разлочим Ф2
			AddQuestRecord("BaronReturn", "8");
			for (i=2; i<=10; i++)
			{
				sld = characterFromId("Dominica_ind_"+i);
				LAi_SetActorType(sld);
			}
		break;
		
//----------------------------------------НПС по квесту Искушение Барбазона----------------------------------
		// капитан рыболовного баркаса, стыривший шелк, море
		case "BarbCapBarkas":
			dialog.text = "Чем обязан вашему визиту, минхер?";
			link.l1 = "Так-так... Ну, рассказывай, дружище, что это ты тут делаешь?";
			link.l1.go = "BarbCapBarkas_1";
		break;
		
		case "BarbCapBarkas_1":
			dialog.text = "Что делаю? Я рыбак, и занимаюсь ловлей рыбы. А какого черта вы мне тут устраиваете допрос, да еще в таком тоне?";
			link.l1 = "Не лги мне, приятель. Может, ты и рыбак, да только сейчас ты ловил совсем не рыбу. Здесь, на этом месте, из одного корабля был выброшен ценный парусный шелк. И твое присутствие тут кажется мне весьма подозрительным.";
			link.l1.go = "BarbCapBarkas_2";
		break;
		
		case "BarbCapBarkas_2":
			dialog.text = "Что за вздор? Какой еще шелк?";
			link.l1 = "Какой шелк? Который из Китая привозят... Не строй из себя дурака! Значит, так: или ты немедленно достаешь из трюма своей скорлупы выловленный шелк и передаешь его мне, или я сам его заберу. Правда перед этим тебя и твоих матросов моя абордажная рота уложит физиономиями в палубу. Ну? Мне звать своих ребят?";
			link.l1.go = "BarbCapBarkas_3";
		break;
		
		case "BarbCapBarkas_3":
			dialog.text = "Нет! Сударь, откуда же я мог знать... Плавают себе и плавают тюки, вот я и решил...";
			link.l1 = "Живо переноси шелк на мой корабль!";
			link.l1.go = "BarbCapBarkas_4";
		break;
		
		case "BarbCapBarkas_4":
			dialog.text = "Да, да, конечно. Сейчас мы все сделаем, только не трогайте мою лодку!";
			link.l1 = "Давай пошевеливайся! У меня мало времени...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Saga_BarbBarkasSilk");
		break;
		
		case "BarbCapBarkas_5":
			dialog.text = "Вот, мы перенесли все, что выловили в море, все девять тюков. Больше не было, я клянусь...";
			link.l1 = "Ладно. Рыбачь себе дальше и впредь не зарься на чужое!";
			link.l1.go = "BarbCapBarkas_6";
		break;
		
		case "BarbCapBarkas_6":
			DialogExit();
			npchar.DontDeskTalk = true;
			npchar.lifeday = 0;
			LAi_SetStayType(npchar);
			pchar.quest.BarbBarkas_Sink.over = "yes"; //снять прерывание
			pchar.quest.BarbBarkas_Abordage.over = "yes"; //снять прерывание
			NextDiag.CurrentNode = "BarbCapBarkas_7";
			AddQuestRecord("BarbTemptation", "6");
			pchar.questTemp.Saga.BarbTemptation = "give_silk";
			AddCharacterExpToSkill(pchar, "Fortune", 100);//везение
			AddCharacterExpToSkill(pchar, "Sneak", 50);//скрытность
		break;
		
		case "BarbCapBarkas_7":
			dialog.text = "Вы уже получили, что хотели. У меня больше ничего нет! Что вам еще от меня надо?";
			link.l1 = "Не переживай, приятель. Я уже ухожу.";
			link.l1.go = "exit";
			NextDiag.TempNode = "BarbCapBarkas_7";
		break;
		
		// Моррель, капитан потопленного судна, тюрьма
		case "Morelle":
			dialog.text = "Если ты от Барбазона, то передай ему, что по своей воле я из тюрьмы не выйду. Я лучше дождусь суда. Даже голландская пенька на шее лучше его ласк.";
			link.l1 = "Не порть воздух раньше времени. Жак со слов твоего штурмана считает тебя покойником. Он послал меня разыскивать свой шелк, который ты якобы выкинул за борт. Сколько его было на борту твоей бригантины?";
			link.l1.go = "Morelle_1";
		break;
		
		case "Morelle_1":
			dialog.text = "Я сам во всем виноват, бес попутал. Связной передал для Барабазона девять тюков шелка. Я приказал выследить его. Он поднял шум и его пришлось прикончить. В его тайнике нашлось еще три тюка, которые я забрал для себя и перепрятал в укромном месте. Вероятно, шум привлек внимание\nНас быстро вычислили, и в море 'Соленого Пса' ждал голландский патруль, уйти от которого нам так и не удалось. Не говори Барбазону про меня, и можешь забрать лишний шелк себе. Тайник находится на пляже Гранд Кейс, между камней в тупике. Мне-то он теперь вряд ли понадобится.";
			link.l1 = "Хорошо. Я не скажу Барбазону, что ты еще жив. Если то, что о нем болтают правда, то тебе и впрямь лучше быть повешенным голландцами. А может еще и каторгой отделаешься.";
			link.l1.go = "Morelle_2";
		break;
		
		case "Morelle_2":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			// тайник - модель
			//int m = Findlocation("Shore40");
			//locations[m].models.always.Roll = "Roll_of_rolls";
			//Locations[m].models.always.Roll.locator.group = "quest";
			//Locations[m].models.always.Roll.locator.name = "quest1";
			pchar.quest.Saga_MorelGoods.win_condition.l1 = "locator";
			pchar.quest.Saga_MorelGoods.win_condition.l1.location = "Shore40";
			pchar.quest.Saga_MorelGoods.win_condition.l1.locator_group = "quest";
			pchar.quest.Saga_MorelGoods.win_condition.l1.locator = "quest1";
			pchar.quest.Saga_MorelGoods.function = "Saga_SetMorelGoods";
			AddCharacterExpToSkill(pchar, "Fortune", 200);//везение
			AddCharacterExpToSkill(pchar, "Sneak", 200);//скрытность
		break;
		
		// Валет, брат Джекмана в Капстервиле
		case "valet":
			dialog.text = "Я жду человека, который знает, когда начнется охота на белую акулу.";
			link.l1 = "Охота уже началась.";
			link.l1.go = "valet_1";
		break;
		
		case "valet_1":
			dialog.text = "Наконец-то! Теперь слушай меня внимательно: тебе нужно отправиться в гости к Маркусу Тираксу в Ла Вегу и сообщить ему, что бригантина 'Разлучница' была атакована у острова Теркс и укрылась в южной бухте. Ее капитан тяжело ранен, а команда  ждет помощи. Сам ты узнал об этом случайно, подобрав в море матроса с 'Разлучницы'. Матрос умер. Больше ты ничего не знаешь. Запомнил?";
			link.l1 = "А зачем для такого пустяка нужен именно я? Стоило ждать столько времени...";
			link.l1.go = "valet_2";
		break;
		
		case "valet_2":
			dialog.text = "Тебе платят за то, чтобы ты работал, а не вопросы задавал. Впрочем, ты прав. Это еще не все. Должен тебя предупредить, что Тиракс вряд ли тебя отпустит, пока не убедится, что ты говоришь правду. Ну, а когда убедится, вознаградит тебя по заслугам. Если успеет...";
			link.l1 = "Что-то ты темнишь, сударь... А почему бы тебе самому не воспользоваться его благодарностью?";
			link.l1.go = "valet_3";
		break;
		
		case "valet_3":
			dialog.text = "Карамба! Кто бы ты ни был, но твое любопытство мне не нравится! Твоя болтовня однажды сведет тебя в могилу.";
			link.l1 = "Да, временами я бываю просто несносен. Особенно, когда вижу, что меня собираются подставить. Нет, дружок, играть мы будем по моим правилам. Кто твой хозяин, черт бы тебя побрал? Отвечай, или я вытащу из тебя эти сведения!";
			link.l1.go = "valet_4";
		break;
		
		case "valet_4":
			dialog.text = "Ах ты... мерзавец! Ну, Барбазону это аукнется, а тебе недолго жить осталось, наглец!";
			link.l1 = "Ха! Другой реакции я и не ожидал. Держись, прохвост!";
			link.l1.go = "valet_5";
		break;
		
		case "valet_5":
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешить драться
			chrDisableReloadToLocation = true;//закрыть локацию
			DialogExit();
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "Saga_ValetDie");
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
		case "vensan":
			// Addon 2016-1 Jason пиратская линейка патч 17/1
			if (CheckAttribute(pchar, "questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "full_complete_end")
			{
				dialog.text = "Чарли Принц? Что ты здесь делаешь? А-аргх, три тысячи чертей, я понял! Это ты все затеял!";
				link.l1 = "Уймись, Берни. Я на твоей стороне. Засада на берегу уничтожена, так что твоему судну и тебе ничего не угрожает, если, конечно, не раскуривать трубку на палубе.";
				link.l1.go = "vensan_8";
			}
			else
			{
				dialog.text = "Черт возьми, вы кто? Как вы сюда попали? Уходите быстрее - мой корабль заминирован, и негодяи, засевшие на берегу, могут взорвать его одним выстрелом.";
				link.l1 = "Не беспокойтесь, сударь. Засада на берегу уничтожена. Вашему судну ничего не угрожает, если, конечно, не раскуривать трубку на палубе. Ваше имя?";
				link.l1.go = "vensan_1";
			}
		break;
		
		case "vensan_1":
			dialog.text = "Венсан. Бернар Венсан. А вы?";
			link.l1 = "Капитан "+GetFullName(pchar)+". Сейчас я разрежу веревки и освобожу вас...";
			link.l1.go = "vensan_2";
		break;
		
		case "vensan_2":
			LAi_SetStayType(npchar);
			dialog.text = "Ох... Спасибо. Как мне отблагодарить вас?";
			link.l1 = "Еще не все закончилось, сударь. У вас еще остались живые люди на корабле?";
			link.l1.go = "vensan_3";
		break;
		
		case "vensan_3":
			dialog.text = "Три десятка матросов заперты в трюме...";
			link.l1 = "Выпускайте их и немедленно убирайтесь отсюда.";
			link.l1.go = "vensan_4";
		break;
		
		case "vensan_4":
			dialog.text = "Но...";
			link.l1 = "Не теряйте времени, Бернар. Благодарности выскажете потом, в Ла Веге, у... Тиракса.";
			link.l1.go = "vensan_5";
		break;
		
		case "vensan_5":
			dialog.text = "Так вы здесь не случайно? Вы знали?";
			link.l1 = "Да, не случайно. Мне удалось раскрыть махинацию Джекмана, с помощью которой этот мерзавец рассчитывал уничтожить Маркуса. Да, и попроси Тиракса ничего не предпринимать, пока я не нанесу ему визит - своим вмешательством он может спугнуть Джекмана.";
			link.l1.go = "vensan_6";
		break;
		
		case "vensan_6":
			dialog.text = "Обязательно передам! Вы уже уходите?";
			link.l1 = "Да. И вы поторапливайтесь.";
			link.l1.go = "vensan_7";
		break;
		
		case "vensan_7":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "goto", "goto2", "none", "", "", "", 5.0);
			Ship_SetTaskRunaway(SECONDARY_TASK, GetCharacterIndex("Cap_Vensan"), GetMainCharacterIndex());
			pchar.questTemp.Saga.BarbTemptation.Vensan_free = "true";
			if (!CheckAttribute(pchar, "questTemp.Saga.BarbTemptation.vensan_attack"))
			{
				if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sld = characterFromId("Mary");
				else sld = characterFromId("Helena");
				sld.dialog.currentnode = "sea_bomb"; 
				LAi_SetActorType(sld);
				ChangeCharacterAddressGroup(sld, pchar.location, "goto", "goto6");
				LAi_ActorDialog(sld, pchar, "", -1, 0);
			}
			AddCharacterExpToSkill(pchar, "Leadership", 100);//авторитет
			AddCharacterExpToSkill(pchar, "Fortune", 100);//везение
			AddCharacterExpToSkill(pchar, "Sneak", 50);//скрытность
			sld = characterFromId("Cap_Vensan");
			sld.lifeday = 1;
			sld.DontDeskTalk = true;
		break;
		
		// Addon 2016-1 Jason пиратская линейка патч 17/1
		case "vensan_8":
			dialog.text = "Это правда? Прости, брат, просто я...";
			link.l1 = "Все, забудь. Сейчас я разрежу веревки и освобожу тебя.";
			link.l1.go = "vensan_9";
		break;
		
		case "vensan_9":
			LAi_SetStayType(npchar);
			dialog.text = "Ох... Руки затекли...";
			link.l1 = "Берни, у тебя еще остались живые люди на корабле?";
			link.l1.go = "vensan_10";
		break;
		
		case "vensan_10":
			dialog.text = "Три десятка матросов заперты в трюме...";
			link.l1 = "Выпускай их и немедленно убирайся отсюда.";
			link.l1.go = "vensan_11";
		break;
		
		case "vensan_11":
			dialog.text = "Но...";
			link.l1 = "Ты будешь мне только мешать, если останешься. Живо поднимай паруса, лети в Ла Вегу и расскажи обо всем Тираксу.";
			link.l1.go = "vensan_12";
		break;
		
		case "vensan_12":
			dialog.text = "Тебя послал Маркус?";
			link.l1 = "Нет. Просто мне удалось раскрыть махинацию одного мерзавца, с помощью которой тот рассчитывал уничтожить Маркуса. Да, и попроси Тиракса ничего не предпринимать, пока я сам не навещу его - своим вмешательством он может спугнуть птичку... Скажи - Принц знает, что делает. И еще передай ему, чтобы он перестал на меня дуться. Все, Берни, не теряй времени!";
			link.l1.go = "vensan_7";
		break;
		
 //--------------------------------------НПС по Завещанию Шарпа--------------------------------------------------
		// Устрица, Поль Моллиган
		case "molligan":
			dialog.text = "Что вам нужно на моем судне, сударь?";
			link.l1 = "Здравствуй, Поль. Ведь это ты - Поль Моллиган?";
			link.l1.go = "molligan_0";
		break;
		
		case "molligan_0":
			dialog.text = "Да, это я. Чем обязан?";
			link.l1 = "Я - "+GetFullName(pchar)+", и меня послал за тобой Ян Свенсон.";
			link.l1.go = "molligan_1";
		break;
		
		case "molligan_1":
			dialog.text = "Ян? А-а, припоминаю я тебя. Точно! Ты в последнее время постоянно ошиваешься в его доме. Так что же Яну нужно от меня?";
			link.l1 = "Ты поторопился уйти из Блювельда. Ян хотел погрузить тебе еще двести центеров красного дерева, чтобы ты передал его лорду Уиллогби в Бриджтауне. Готовь судно под погрузку - мои люди перенесут тебе в трюмы древесину с моего судна.";
			link.l1.go = "molligan_2";
		break;
		
		case "molligan_2":
			dialog.text = "Красное дерево? Это Ян так сказал? Хм. А почему ты сам не можешь отвезти его на Барбадос? Зачем для этого понадобился я?";
			link.l1 = "Потому что ты идешь в Бриджтаун, а я - нет. У меня срочное задание от Свенсона, и мне некогда задерживаться. К тому же Ян не доверяет мне переговоров с лордом Уиллогби и возложил это на тебя, уж не обессудь. Давай грузиться, мне уже пора.";
			link.l1.go = "molligan_3";
		break;
		
		case "molligan_3":
			dialog.text = "Послушай, но у меня нет места в трюмах. Я не смогу выполнить просьбу Яна, как бы мне того ни хотелось...";
			link.l1 = "Нет места? Странно... А мне Ян сказал, что у тебя трюмы заполнены не доверху.";
			link.l1.go = "molligan_4";
		break;
		
		case "molligan_4":
			dialog.text = "Это так, но Ян не знал, что я поставил на 'Устрицу' новые, более тяжелые орудия. Я не могу погрузить груза больше, чем у меня уже есть. Отвези древесину на Барбадос сам, а, дружище? Скажешь Яну, что я не смог. А с Уиллогби уметь разговаривать не надо: пришел, сдал груз, получил расписку и ушел. Ничего сложного.";
			link.l1 = "Гм. Это совсем не входило в мои планы... Может, спустимся в трюмы, глянем? Мой квартирмейстер просто мастер упаковки - так уложит товар, что еще и место останется...";
			link.l1.go = "molligan_5";
		break;
		
		case "molligan_5":
			dialog.text = "Приятель, но я действительно не могу взять лишний груз. Или ты хочешь, чтобы я выбросил для этого за борт орудия и оставил 'Устрицу' беззащитной?";
			link.l1 = "Ладно. Ну, раз ты так категоричен... Но Яну это не понравится, учти!";
			link.l1.go = "molligan_6";
		break;
		
		case "molligan_6":
			dialog.text = "Я объясню Свенсону, не переживай. В конце концов, Лесной Дьявол сам дал промашку, не поинтересовавшись заранее, будет ли у меня место.";
			link.l1 = "Эх, тащи теперь эти бревна до Барбадоса, чтоб они в труху рассыпались... Пока, приятель.";
			link.l1.go = "molligan_7";
		break;
		
		case "molligan_7":
			DialogExit();
			// ставим проверку скрытности
			if (GetSummonSkillFromName(pchar, SKILL_SNEAK) > (10+drand(50)))
			{
				pchar.questTemp.Saga.Molligan.friend = "true"; // будет шанс критического залпа картечью
				sTemp = "Негодяй, похоже, ничего не заподозрил. Подойду к нему поближе и сделаю залп картечью: неожиданное нападение - залог успеха в любой схватке. ";
				log_Testinfo("Друзья");
				AddCharacterExpToSkill(pchar, "Fortune", 200);//везение
				AddCharacterExpToSkill(pchar, "Sneak", 300);//скрытность
			}
			else
			{
				pchar.questTemp.Saga.Molligan.enemy = "true"; // нападет
				sTemp = "";
				log_Testinfo("Враги");
				AddCharacterExpToSkill(pchar, "Sneak", 150);//скрытность
			}
			AddQuestRecord("Testament", "7");
			AddQuestUserData("Saga", "sText", sTemp);
			NextDiag.CurrentNode = "molligan_8";
			npchar.DontDeskTalk = true; // patch-5
		break;
		
		case "molligan_8":
			dialog.text = "Мы все обсудили, дружище, разве нет?";
			link.l1 = "Да, да. Я уже отправляюсь на свой корабль.";
			link.l1.go = "exit";
			NextDiag.TempNode = "molligan_8";
		break;
		
	//-----------------------------------------НПС по Теням прошлого--------------------------------------------
		// Джим Бенсон, плешивая мэгги
		case "benson":
			dialog.text = "Зачем я вам понадобился? Я не люблю сплетни и азартные игры. А ром предпочитаю глушить в одиночестве. К тому же у меня после этого рейса особенно паршивое настроение.";
			link.l1 = "А что такого особенного произошло в этом рейсе?";
			link.l1.go = "benson_1";
		break;
		
		case "benson_1":
			dialog.text = "Человек мне один хороший доверился, а я пошел на поводу у команды и выкинул его за борт. Ну не то, чтобы выкинул, все же старый баркас и запас продовольствия оставляют ему шансы, но, признаться, небольшие.";
			link.l1 = "Чем же он провинился, этот бедолага?";
			link.l1.go = "benson_2";
		break;
		
		case "benson_2":
			dialog.text = "Я тут недавно и мало с кем знаком. Ну и нанял этого добродушного толстяка корабельным врачом, ничего не зная о его прошлом. Когда мы возвращались обратно, от самого Барбадоса у нас на хвосте повисли пираты. Зачем им вдруг понадобилась моя лоханка?\nЕле-еле оторвались благодаря шторму. Ну выпили на радостях по такому случаю. Так вот этот дурень  ничего лучше не придумал, как заявить при всех, что гнались скорее всего за ним, так как он бывший палач и чего-то там знает лишнего\nНу, ясное дело, матросы взвились. Как это так?! Палач на борту да еще в качестве врача! Да и с пиратами дел никто иметь не хочет... Ну и пришлось мне высадить его, бедолагу. Сам виноват, болтать нужно меньше. Но на душе все равно тошно. Жалко этого увальня, да и врач он от Бога. Мне вот похмелье как рукой снял.";
			link.l1 = "Черт побери! Его звали Раймонд Бейкер, этого вашего врача?";
			link.l1.go = "benson_3";
		break;
		
		case "benson_3":
			dialog.text = "Да. Именно так. А вы откуда знаете? Уж не вы ли гнались за мной?";
			link.l1 = "Нет, не я. Мне просто очень нужен этот человек - второго такого лекаря днем с огнем не сыскать. Где вы его высадили?";
			link.l1.go = "benson_4";
		break;
		
		case "benson_4":
			dialog.text = "Я высадил его в районе 15 гр. 28' северной широты и 63 гр. 28' западной долготы. Поторопитесь, сударь! Он должен быть еще жив, и если вы его спасете - вы снимете грех с моей души!";
			link.l1 = "Уже поднимаю якоря!";
			link.l1.go = "benson_5";
		break;
		
		case "benson_5":
			DialogExit();
			NextDiag.CurrentNode = "benson_6";
			AddQuestRecord("Shadows", "3");
			npchar.lifeday = 0;
			bQuestDisableMapEnter = false;
			pchar.quest.Saga_Shadows_Baker.win_condition.l1 = "location";
			pchar.quest.Saga_Shadows_Baker.win_condition.l1.location = "Dominica";
			pchar.quest.Saga_Shadows_Baker.function = "Saga_SetBakerBoat";
		break;
		
		case "benson_6":
			dialog.text = "Капитан, поспешите! Он должен быть еще жив!";
			link.l1 = "Да-да, бегу...";
			link.l1.go = "exit";
			NextDiag.TempNode = "benson_6";
		break;
		
	//---------------------------------------бандиты у джекмановского рудника-------------------------------
		case "mine_bandit":
			if (CheckAttribute(pchar, "questTemp.Saga.MineAttack"))
			{
				dialog.text = "Эй! А ну стой, где стоишь! Ни шагу дальше! Эта территория - под охраной!";
				link.l1 = "Не будь столь суров, старина! Свои! Мы от Джекмана. Нам нужно пройти на рудник. Приказ хозяина...";
				link.l1.go = "mine_attack";
				break;
			}
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "Эй! А ну стой, где стоишь! Ни шагу дальше! Эта территория - под охраной!";
				link.l1 = "Хм. Но я хочу пройти... С какой стати ты мне это запрещаешь?";
				link.l1.go = "mine_bandit_1";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "А-а, это опять ты?! Вижу, по-хорошему до тебя не доходит... Ребята, пли!!";
				link.l1 = "...";
				link.l1.go = "mine_bandit_fire";
			}
		break;
		
		case "mine_bandit_0":
			dialog.text = "Давай, проходи, нечего тут стоять!";
			link.l1 = "Хорошо...";
			link.l1.go = "exit";
			NextDiag.TempNode = "mine_bandit_0";
		break;
		
		case "mine_bandit_1":
			dialog.text = "А с такой, что рудник за моей спиной - частная собственность, и я здесь стою для того, чтобы не пускать туда всяких проходимцев, вроде тебя. Лучше разворачивайся и уходи с миром, незнакомец. Наши пушки заряжены картечью - так шарахнем, что от тебя только мокрое место останется.";
			link.l1 = "Хех, понятно. Серьезная у вашего рудника охрана. Хорошо, я ухожу.";
			link.l1.go = "mine_bandit_exit";
			link.l2 = "Ах ты, мерзавец! Ну это мы сейчас посмотрим, от кого что останется!";
			link.l2.go = "mine_bandit_2";
		break;
		
		case "mine_bandit_exit":
			DialogExit();
			LAi_SetGuardianType(npchar);
			LAi_group_MoveCharacter(npchar, "PIRATE_CITIZENS");
			chrDisableReloadToLocation = false;//открыть локацию
			DoQuestReloadToLocation("Mine_02", "reload", "reload3", "");
		break;
		
		case "mine_bandit_2":
			dialog.text = "Ну, ты сам напросился... Ребята, пли!!";
			link.l1 = "...";
			link.l1.go = "mine_bandit_fire";
		break;
		
		case "mine_bandit_fire":
			DialogExit();
			DoQuestCheckDelay("Saga_MineBanditsFire", 1.5);
		break;
		
		case "mine_banditx":
			if (CheckAttribute(pchar, "questTemp.Saga.MineAttack"))
			{
				dialog.text = "Эй! А ну поворачивай назад! Эта территория - под охраной!";
				link.l1 = "Хей, полегче, приятель! Мы от Джекмана. Нам нужно пройти на рудник. Приказ хозяина...";
				link.l1.go = "mine_attackx";
				break;
			}
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "Эй! А ну поворачивай назад! Эта территория - под охраной!";
				link.l1 = "Хм. А что там такое?";
				link.l1.go = "mine_banditx_1";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "А-а, это опять ты?! Вижу, по-хорошему до тебя не доходит... Мушкеты на изготовку! Пли!!";
				link.l1 = "...";
				link.l1.go = "mine_banditx_fire";
			}
		break;
		
		case "mine_banditx_1":
			dialog.text = "Не твое дело. Убирайся, или мы положим тебя на месте, клянусь!";
			link.l1 = "Ладно, не кипятись. Я уже ухожу.";
			link.l1.go = "mine_banditx_exit";
			link.l2 = "Ах ты, мерзавец! Ну это мы сейчас посмотрим, кто кого положит!";
			link.l2.go = "mine_banditx_2";
		break;
		
		case "mine_banditx_exit":
			DialogExit();
			LAi_SetGuardianType(npchar);
			LAi_group_MoveCharacter(npchar, "PIRATE_CITIZENS");
			DoQuestReloadToLocation("Mine_04", "reload", "reload3", "");
		break;
		
		case "mine_banditx_2":
			dialog.text = "Ну, ты сам напросился... Мушкеты на изготовку! Пли!!";
			link.l1 = "...";
			link.l1.go = "mine_banditx_fire";
		break;
		
		case "mine_banditx_fire":
			DialogExit();
			DoQuestCheckDelay("Saga_MineBanditsxFire", 0.6);
		break;
		
		case "mine_attackx":
			dialog.text = "Вот как? Ну тогда тебе должен быть известен пароль для входа. Говори его, а если ты солгал - даже пожалеть об этом не успеешь...";
			link.l1.edit = 5;
			link.l1 = "";
			link.l1.go = "mine_attackx_1";
		break;
		
		case "mine_attackx_1":
			sTemp = GetStrSmallRegister(dialogEditStrings[5]);
			if (sTemp == "нептун")
			{
				dialog.text = "Все верно. Но ты, приятель, пришел не с той стороны. Разве тебя не предупредили? Топай назад по тропе, потом пройдешь мимо сухого колодца, возьмешь левее, на тропинку вокруг холма - она тебя приведет к центральному входу.";
				link.l1 = "А здесь пройти никак нельзя?";
				link.l1.go = "mine_attackx_2";
			}
			else
			{
				dialog.text = "Ребята, у нас тут шпик! Мушкеты на изготовку! Пли!!";
				link.l1 = "...";
				link.l1.go = "mine_banditx_fire";
			}
		break;
		
		case "mine_attackx_2":
			dialog.text = "Нет. Только через центральный вход.";
			link.l1 = "Хорошо, дружище... Эй! Смотри! Что это за дрянь наверху частокола?";
			link.l1.go = "mine_attackx_3";
		break;
		
		case "mine_attackx_3":
			DialogExit();
			for (i=1; i<=4; i++)
			{
				sld = characterFromId("Mine_banditx_"+i);
				LAi_RemoveCheckMinHP(sld);
			}
			sld = characterFromId("Svensons_sold_12");
			LAi_SetActorType(sld);
			LAi_ActorTurnToLocator(sld, "soldiers", "soldier1");
			LAi_ActorAnimation(sld, "shot", "Saga_MineBanditxDie", 1.0);
		break;
		
		case "mine_attack":
			dialog.text = "Да неужели? Ну тогда тебе должен быть известен пароль. Говори его, и говори четко, чтобы я хорошо расслышал. Ну, а если ты сейчас попытался схитрить - то это была последняя неудачная шутка в твоей жизни.";
			link.l1.edit = 5;
			link.l1 = "";
			link.l1.go = "mine_attack_1";
		break;
		
		case "mine_attack_1":
			sTemp = GetStrSmallRegister(dialogEditStrings[5]);
			if (sTemp == "нептун")
			{
				dialog.text = "Верно. Можете проходить. Старший по лагерю находится в доме слева от входа в шахту. Топайте сразу к нему.";
				link.l1 = "Хорошо, приятель...";
				link.l1.go = "mine_attack_2";
			}
			else
			{
				dialog.text = "Ребята, у нас тут шпик! Орудия, пли!!";
				link.l1 = "...";
				link.l1.go = "mine_bandit_fire";
			}
		break;
		
		case "mine_attack_2":
			DialogExit();
			NextDiag.CurrentNode = "mine_attack_3";
			LAi_SetActorType(pchar);
			LAi_ActorFollow(pchar, npchar, "ActorDialog_Any2Pchar", -1);
			LAi_ActorTurnToCharacter(npchar, pchar);
			SetActorDialogAny2Pchar(npchar.id, "", 0.0, 0.0);
		break;
		
		case "mine_attack_3":
			dialog.text = "Чего тебе еще? Забыл что-то?";
			link.l1 = "Да. Меня просили передать тебе привет.";
			link.l1.go = "mine_attack_4";
		break;
		
		case "mine_attack_4":
			dialog.text = "Мне? Ха-ха! И от кого же?";
			link.l1 = "От Яна Свенсона, мразь!";
			link.l1.go = "mine_attack_5";
		break;
		
		case "mine_attack_5":
			DialogExit();
			LAi_SetPlayerType(pchar);
			for (i=1; i<=6; i++)
			{
				sld = characterFromId("Mine_bandit_"+i);
				LAi_RemoveCheckMinHP(sld);
			}
			if (pchar.questTemp.Saga.MineAttack == "soldiers")
			{
				sld = characterFromId("Svensons_sold_12");
				LAi_SetActorType(sld);
				LAi_ActorTurnToLocator(sld, "soldiers", "soldier1");
				LAi_ActorAnimation(sld, "shot", "Saga_MineBanditDie", 1.0);
			}
			else
			{
				for (i=1; i<=6; i++)
				{
					sld = characterFromId("Mine_bandit_"+i);
					LAi_SetWarriorType(sld);
					LAi_group_MoveCharacter(sld, "EnemyFight");
				}
				LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
				LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
				LAi_group_SetCheck("EnemyFight", "Saga_BanditsDestroyed");
				AddDialogExitQuest("MainHeroFightModeOn");	
			}
			pchar.quest.Saga_MineAttack_07.win_condition.l1 = "NPC_Death";
			pchar.quest.Saga_MineAttack_07.win_condition.l1.character = "Mine_bandit_1";
			pchar.quest.Saga_MineAttack_07.win_condition.l2 = "NPC_Death";
			pchar.quest.Saga_MineAttack_07.win_condition.l2.character = "Mine_bandit_2";
			pchar.quest.Saga_MineAttack_07.function = "Saga_SvensonMineexitAttack";
		break;
		
	// ----------------------------- диалоги НПС при штурме бандитского рудника -------------------------------
		case "Svensons_off":
			dialog.text = LinkRandPhrase("Мы порвем этих грязных подонков, как старую тряпку!","Мне не терпится врезать как следует по шее этим мерзавцам!","Шестеркам Джекмана не место на Западном Мэйне! Мы выбьем отсюда эту погань!");
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "Svensons_off";
		break;
		
		case "Svensons_sold":
			dialog.text = LinkRandPhrase("Мы готовы к бою!","Покажем этим ублюдкам!","Они еще не знают, с кем связались!");
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "Svensons_sold";
		break;
		
		case "gunner":
			PlaySound("Voice\russian\evilpirates01.wav");
			dialog.text = "Командир, орудие к бою готово. Заряжено бомбой, как вы приказали.";
			link.l1 = "Смотрю, никто не ждет нас тут в гости... Надо заявить о себе. Ян сказал, что лагерь бандитов за этим холмом. Попадешь туда, как думаешь?";
			link.l1.go = "gunner_0_1";
		break;
		
		case "gunner_0_1":
			dialog.text = "Запросто, командир. Поднимем ствол повыше, и - в самый раз... Вот так\nГотовьсь!.. Огонь!!";
			link.l1 = "...";
			link.l1.go = "gunner_0_2";
			npchar.quest.canonada = "1";
		break;
		
		case "gunner_0_2":
			DialogExit();
			LAi_SetActorType(pchar);
			DoQuestCheckDelay("Saga_Gunfire", 3.0);
			LAi_ActorTurnToLocator(npchar, "goto", "goto14");
		break;
		
		case "gunner_1":
			dialog.text = "";
			link.l1 = "Хм. Как думаешь, Рандольф, мы хоть куда-то попали?";
			link.l1.go = "gunner_1_1";
		break;
		
		case "gunner_1_1":
			PlaySound("interface\_bombs_npc.wav");
			dialog.text = "Командир, куда-то мы точно попали, но вот куда... За этим проклятым холмом ни черта не видно. Сейчас попробую немного изменить угол\nГотовьсь! Огонь!";
			link.l1 = "...";
			link.l1.go = "gunner_0_2";
			npchar.quest.canonada = "2";
		break;
		
		case "gunner_2":
			PlaySound("interface\abordage_wining.wav");
			PlaySound("types\warrior03.wav");
			dialog.text = "Ха! Смотрите, командир! Посмотрите наверх - это дым! Раздери меня селедка, если мы не угодили бомбой в какой-то бандитский сарай! Ура-а!";
			link.l1 = "Точно - дым... Перезаряжаем орудие и наводим на тропу - клянусь честью, сейчас к нам пожалуют гости! Встретим их как следует!";
			link.l1.go = "gunner_2_1";
		break;
		
		case "gunner_2_1":
			PlaySound("interface\_bombs_npc.wav");
			dialog.text = "Есть, командир! Зарядить бомбой! Приготовиться к выстрелу! Фитиль! Огонь по моей команде!";
			link.l1 = "...";
			link.l1.go = "gunner_2_2";
			npchar.quest.canonada = "3";
		break;
		
		case "gunner_2_2":
			DialogExit();
			LAi_SetActorType(pchar);
			DoQuestCheckDelay("Saga_LoginBandos_01", 6.0);
			LAi_ActorTurnToLocator(pchar, "goto", "goto14");
			LAi_ActorTurnToLocator(npchar, "goto", "goto14");
		break;
		
		case "gunner_3":
			PlaySound("interface\abordage_wining.wav");
			PlaySound("types\warrior03.wav");
			PlaySound("Voice\russian\evilpirates05.wav");
			dialog.text = "Ха-ха, получили, куриные потроха!";
			link.l1 = "Не расслабляться! Зарядить орудие! Не думаю, что это их остановило - сейчас пожалуют еще!";
			link.l1.go = "gunner_3_1";
		break;
		
		case "gunner_3_1":
			PlaySound("interface\_bombs_npc.wav");//
			dialog.text = "Есть, командир! Зарядить бомбой! Готовьсь! Огонь по моей команде!";
			link.l1 = "...";
			link.l1.go = "gunner_3_2";
			npchar.quest.canonada = "4";
		break;
		
		case "gunner_3_2":
			DialogExit();
			LAi_SetActorType(pchar);
			DoQuestCheckDelay("Saga_LoginBandos_02", 5.0);
			LAi_ActorTurnToLocator(pchar, "goto", "goto14");
			LAi_ActorTurnToLocator(npchar, "goto", "goto14");
		break;
		
		case "gunner_5":
			PlaySound("types\warrior04.wav");
			PlaySound("Voice\russian\evilpirates06.wav");
			dialog.text = "Ха-ха-ха, мерзавцы показали спины! Собачье мясо! Картечь с близкого расстояния - убойная штука! Похоже, желание атаковать у них поостыло!";
			link.l1 = "Теперь пора нам пойти в контратаку. Рандольф, ты остаешься возле орудия. Дай пару выстрелов бомбами в направлении тропы за холмом, потом целься на дым - преврати их логово в дымящиеся развалины! Только нас не подстрели.";
			link.l1.go = "gunner_5_1";
		break;
		
		case "gunner_5_1":
			PlaySound("interface\_bombs_npc.wav");
			dialog.text = "Есть, командир! Орудие к бою! Зарядить бомбой!";
			link.l1 = "Отря-яд! К оружию! За мной, в атаку! Ура-а!!";
			link.l1.go = "attack";
		break;
		
		case "attack":
			DialogExit();
			n = Findlocation("mine");
			Locations[n].hidden_fire = true;
			PlaySound("interface\abordage_wining.wav");
			PlaySound("interface\abordage_wining.wav");
			LAi_ActorTurnToLocator(npchar, "goto", "goto14");
			LAi_group_MoveCharacter(npchar, "TMP_FRIEND");
			if (GetCharacterIndex("Svensons_sold_12") != -1 && pchar.questTemp.Saga.MineAttack == "soldiers")
			{
				sld = characterFromId("Svensons_sold_12");
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			}
			for (i=1; i<=8; i++)
			{
				if (GetCharacterIndex("Ourmine_sold_"+i) != -1)
				{
					sld = characterFromId("Ourmine_sold_"+i);
					if (i == 1) sld.MusketerDistance = 10; 
					LAi_SetWarriorType(sld);
					LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
				}
			}
			LAi_group_SetRelation("EnemyFight", "TMP_FRIEND", LAI_GROUP_NEITRAL);
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "Saga_MineBandos_05Die");
			AddDialogExitQuest("MainHeroFightModeOn");	
			DoQuestCheckDelay("Saga_MineSetMusic", 0.3);
			// запусткаем автобабахалку на 10 выстрелов
			iTotalTemp = 0;
			DoQuestCheckDelay("Saga_GunAutoFire", 7.0);
			bDisableCharacterMenu = false;//разлочим интерфейсы
			InterfaceStates.Buttons.Save.enable = true;//разрешим сохраняться
		break;
		
		case "convict":
			if (LAi_grp_playeralarm > 0)
			{
				dialog.text = LinkRandPhrase("Не трогайте меня, я не из них! Убейте бандитов!","Освободи нас, дружище! Перебей мерзавцев!","Режь их, приятель, режь! Чтоб они все сдохли, подонки!");
				link.l1 = "Ха! Не переживай - именно это мы и делаем!";
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = LinkRandPhrase("Неужели рабство закончится? Вы освободите нас?","Хех, неужели я дожил до этого дня?","Мерзавцы выпили из нас всю кровь...");
				link.l1 = "Думаю, приятель, ты скоро сможешь наслаждаться свободой...";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "convict";
		break;
		
		// жена Яна Свенсона
		case "js_girl":
			if (LAi_grp_playeralarm > 0)
			{
				dialog.text = "Лучше бы вам убраться отсюда, сударь. Мы не укрываем преступников и не конфликтуем с властями колонии.";
				link.l1 = "Хорошо, я уже ухожу...";
				link.l1.go = "exit";
				NextDiag.TempNode = "js_girl";
				break;
			}
			if(NPChar.quest.meeting == "0")
			{
				dialog.text = TimeGreeting()+", сэр. Вы, как я полагаю, к Яну?";
				link.l1 = "Здравствуйте. Приятно познакомиться, мисс?..";
				link.l1.go = "js_girl_1";
			}
			else
			{
				if (CheckAttribute(pchar, "questTemp.Saga") && pchar.questTemp.Saga == "blueveld")
				{
					dialog.text = TimeGreeting()+", капитан "+GetFullName(pchar)+". Если вы к Яну, то я вынуждена вас огорчить - его нет дома. Он отбыл по срочным делам.";
					link.l1 = "Черт побери! И это именно тогда, когда он мне больше всего нужен! Скажите, миссис Свенсон, а когда ваш муж вернется - он не сказал?";
					link.l1.go = "js_girl_3";
					break;
				}
				dialog.text = "А-а, это опять вы, капитан "+GetFullName(pchar)+"... Проходите, Ян как обычно - у себя на втором этаже.";
				link.l1 = "Спасибо, миссис Свенсон...";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "js_girl";
		break;
		
		case "js_girl_1":
			dialog.text = "Миссис. Миссис Джоанна Свенсон.";
			link.l1 = "Капитан "+GetFullName(pchar)+".";
			link.l1.go = "js_girl_2";
		break;
		
		case "js_girl_2":
			if (CheckAttribute(pchar, "questTemp.Saga") && pchar.questTemp.Saga == "blueveld")
			{
				dialog.text = "Даже капитан? Ну что же, рада приветствовать вас в моем доме. Но если вы пришли к Яну - то я вынуждена вас огорчить - его нет дома. Он отбыл по срочным делам.";
				link.l1 = "Черт побери! И это именно тогда, когда он мне больше всего нужен! Скажите, миссис Свенсон, а когда ваш муж вернется - он не сказал?";
				link.l1.go = "js_girl_3";
				break;
			}
			dialog.text = "Даже капитан? Ну что же, рада приветствовать вас в моем доме. Муж на втором этаже в своем кабинете. Поднимайтесь вверх по лестнице.";
			link.l1 = "Я понял, миссис Свенсон...";
			link.l1.go = "exit";
			NPChar.quest.meeting = "1";
			NextDiag.TempNode = "js_girl";
		break;
		
		case "js_girl_3":
			dialog.text = "Нет. Точной даты возвращения он не сказал даже мне, поскольку и сам не знает, сколько продлятся поиски.";
			link.l1 = "Простите, что вмешиваюсь не в свое дело, но мне и правда очень нужен Ян... Какими поисками он занят, не скажете?";
			link.l1.go = "js_girl_4";
		break;
		
		case "js_girl_4":
			dialog.text = "Скажу, конечно. Пропала его любимица Элен по прозвищу Румба, дочь старого приятеля по лихим годам Шона Мак Артура, упокой Господи его душу. Ян относится к этой чертовке, словно к своей дочери. Сильно она по характеру похожа на его старинную любовь, такая же безбашенная, видимо, в этом и кроется его привязанность\nИ вот неделю назад эта девка пропала вместе со своей шхуной 'Радугой' и всей командой. Шон Мак Артур выучил Элен морскому делу, а 'Радуга' досталась ей в наследство. Вот теперь она и играет в капитана...";
			link.l1 = "Что могло с ней случиться?";
			link.l1.go = "js_girl_5";
		break;
		
		case "js_girl_5":
			dialog.text = "Кто же знает... Неделя – срок небольшой, но вдова Мак Артура Глэдис уверена, что с ее дочерью случилось что-то скверное, и смогла убедить в этом Яна. Тот поднял на ноги своих людей и сам отправился на поиски, но пока безрезультатно. Хотя лично мое мнение - ничего с Элен страшного не произошло, и Ян только напрасно себе душу истерзал\nНаслушался бредней старой толстухи Глэдис и забил тревогу. А девка, скорее всего, сейчас кувыркается с каким-нибудь очередным ухажером подальше от людских глаз, и всех дел. Нагуляется - приплывет назад.";
			link.l1 = "Джоанна, где мне найти эту Глэдис? Я хочу поговорить с ней...";
			link.l1.go = "js_girl_6";
		break;
		
		case "js_girl_6":
			dialog.text = "Ее дом рядом с пристанью, налево от причала. Но там ее скорее всего нет. Она целыми днями торчит на стенах форта, все высматривает свою ненаглядную дочку.";
			link.l1 = "Ясно. Спасибо огромное за информацию!";
			link.l1.go = "js_girl_7";
		break;
		
		case "js_girl_7":
			DialogExit();
			NextDiag.CurrentNode = "js_girl_8";
			sld = characterFromId("Gladis"); //устанавливаем Глэдис на форт
			ChangeCharacterAddressGroup(sld, "SantaCatalina_fort", "goto", "goto53");
			LAi_SetStayType(sld);
			sld.dialog.currentnode = "FindHelena";
			pchar.questTemp.Saga = "gladis";
		break;
		
		case "js_girl_8":
			dialog.text = "Ян пока еще не вернулся из поисков, капитан, так что заходите позже.";
			link.l1 = "Понятно...";
			link.l1.go = "exit";
			NextDiag.TempNode = "js_girl_8";
		break;
		
		// хронометр Алекса
		case "Alexs_bandos":
			dialog.text = "Эй! Ты чего здесь выискиваешь, а?";
			link.l1 = "Это я тебя хотел спросить - что ты со своими дружками забыл в моем подземелье?!";
			link.l1.go = "Alexs_bandos_1";
		break;
		
		case "Alexs_bandos_1":
			dialog.text = "Ха! Твое подземелье? Когда же оно стало твоим, пижон?";
			link.l1 = "Тогда, когда твой папаша совершал ошибку, греша с твоей маманей.";
			link.l1.go = "Alexs_bandos_2";
		break;
		
		case "Alexs_bandos_2":
			dialog.text = "Нарываешься, да?";
			link.l1 = "Слушай, дружок: даю тебе шанс свалить отсюда подобру-поздорову. Это мое подземелье, и я не позволю по нему расхаживать не пойми кому, ясно? Стоит мне свистнуть - и здесь через минуту будет половина пиратов Исла Тесоро.";
			link.l1.go = "Alexs_bandos_3";
		break;
		
		case "Alexs_bandos_3":
			dialog.text = "Ну что же, тогда мы постараемся заткнуть тебе рот побыстрее, чтобы ты не свистел!";
			link.l1 = "Ха-ха! Ты жалок, оборванец!";
			link.l1.go = "Alexs_bandos_4";
		break;
		
		case "Alexs_bandos_4":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation("Bermudes_Dungeon")], false);
			for (i=1; i<=4; i++)
			{
				sld = characterFromId("Alexs_bandos_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			int iRank = sti(pchar.rank)+MOD_SKILL_ENEMY_RATE+5;
			int iScl = 25+2*sti(pchar.rank);
			sld = GetCharacter(NPC_GenerateCharacter("Alexs_bandos_5", "mush_ctz_8", "man", "mushketer", iRank, PIRATE, -1, false, "soldier"));
			FantomMakeCoolFighter(sld, iRank, iScl, iScl, "", "mushket1", "cartridge", iScl*2+50);
			ChangeCharacterAddressGroup(sld, "Bermudes_Dungeon", "monsters", "monster8");
			LAi_group_MoveCharacter(sld, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "AlexClock_BandosDie");
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
	}
}