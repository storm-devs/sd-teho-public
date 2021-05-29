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
	
	bool ok;
    int iTest;
    ref rColony;
    string sFrom_sea = "";
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
		dialog.text = "Явный баг. Сообщите об этом Jason'у, как и при каких обстоятельствах его получили.";
		link.l1 = "Обязательно сообщу!";
		link.l1.go = "exit";
		break;
		
		case "Avendel_tavern":
			pchar.quest.Portugal_BeginOver.over = "yes";
			dialog.text = "О, ещё один бывалый моряк! Я вашего брата издалека примечаю, мой распроклятый глаз на вас намётан, хе! Спросите почему?";
			link.l1 = "Мой вопрос о другом – о вашем долге,  хозяйке местного... гм, заведения. Она просила меня напомнить о деньгах, иначе – завтра она вынуждена будет обратиться к страже.";
			link.l1.go = "Avendel_tavern_1";
		break;
		
		case "Avendel_tavern_1":
			dialog.text = "Потому что я... ох, проклятье! Йоханна, она не может так со мной поступить? Вы уверены? Она так и сказала – отправит меня в казематы за какие-то растреклятые гроши?";
			link.l1 = "Несомненно. Так она и сказала. Полагаю, на этом моя миссия выполнена, всего доброго, минхер Авендел.";
			link.l1.go = "Avendel_tavern_2";
		break;
		
		case "Avendel_tavern_2":
			dialog.text = "Постойте! Подождите, я прошу вас! Вы выглядите опытным капитаном. У вас наверняка найдётся горсть монет – я совсем на мели, и только местный добряк корчмарь наливает мне по старой памяти в долг. Выслушайте моё предло.. ик, предложение! Если вы отдадите за меня этот долг, я возьму вас в долю\nЕсть одно дело... прибыльное дело, чтоб его якорем да под килем! Клянусь своей проклятой селезёнкой – поверьте, капитан, как вас там!\nВсего один маленький долг, всего лишь десять тысяч монет, и вы сможете заработать столько, что хватит скупить все бордели Нового, будь он неладен, Света, и портовые притоны впридачу! Что скажете? Вы мне – я вам, всё честно... ик!";
			link.l1 = "Оборванец, сулящий золотые горы... Увольте – я не подаю милостыню таким как вы. Ищите деньги, или будете обживать тюремные казематы. Прощайте!";
			link.l1.go = "Avendel_tavern_3";
			link.l2 = "Заработать? И я должен поверить слову спившегося бродяги, ради фантастических обещаний?";
			link.l2.go = "Avendel_tavern_4";
		break;
		
		case "Avendel_tavern_3":
			DialogExit();
			npchar.lifeday = 0;
			LAi_CharacterDisableDialog(npchar);
			pchar.questTemp.Portugal = "end";
		break;
		
		case "Avendel_tavern_4":
			dialog.text = "Выслушайте меня, капитан! Ик, чтоб мне провалится на этом месте, если вру! Я говорю правду! Судите сами – если вру, вы выпустите мне проклятые потроха этой вашей красоткой, что таскаете на бедре! Да один её эфес стоит в пять раз больше моего никчемного долга, проглоти его селёдка! Ну же? Вы ничего не теряете!";
			link.l1 = "Вы меня утомили своей болтовней. Прощайте.";
			link.l1.go = "Avendel_tavern_3";
			link.l2 = "Ладно, Хьюго... я рискну поверить в этот бред. Но учтите – если, когда я вернусь, вы не убедите меня что деньги потрачены не зря, пеняйте на себя.";
			link.l2.go = "Avendel_tavern_5";
		break;
		
		case "Avendel_tavern_5":
			dialog.text = "Не надо угроз – я и так всё понимаю. Я же поклялся, капитан! Мы разбогатеем! Возвращайтесь, как только этот проклятый долг будет улажен, и мы всё обго... ик! Обговорим! Вы не останетесь за бортом!";
			link.l1 = "Хорошо, я отдам долг, но молись, Хьюго Авендел, чтобы твоё 'предложение' и впрямь себя оправдало.";
			link.l1.go = "Avendel_tavern_6";
		break;
		
		case "Avendel_tavern_6":
			DialogExit();
			pchar.questTemp.Portugal = "HostressMoney";
			Nextdiag.Currentnode = "Avendel_repeat";
		break;
		
		case "Avendel_repeat":
			dialog.text = "Капитан, возвращайтесь поскорее - мне не терпится изложить вам суть дела.";
			link.l1 = "Да-да, сейчас отдам твой долг и приду.";
			link.l1.go = "exit";
			Nextdiag.TempNode = "Avendel_repeat";
		break;
		
		case "Avendel_tavern_7":
			pchar.quest.Portugal_BeginOver.over = "yes";
			dialog.text = "Вы вернулись, капитан! Гром и проклятая молния, я рад вас видеть! Как там долг?";
			link.l1 = "Дело улажено, теперь твой черёд, Хьюго. Выкладывай свою историю, и постарайся, чтобы она выглядела хоть немного правдиво!";
			link.l1.go = "Avendel_tavern_8";
		break;
		
		case "Avendel_tavern_8":
			dialog.text = "Не беспокойтесь, капитан! Вы знаете, что я охотник за головами? Вернее, я был им. Мне просто не везло. Наверное, сам Дьявол, со всеми его авантюрами, не был большим неудачником, чем я. А на последнем деле я потерял всё – команда разбежалась, корабль пришлось продать в счёт долгов...";
			link.l1 = "О вашем героическом прошлом, я уже осведомлён. К делу, Хьюго, не испытывайте моё терпение.";
			link.l1.go = "Avendel_tavern_9";
		break;
		
		case "Avendel_tavern_9":
			dialog.text = "Да-да, капитан... "+GetFullName(pchar)+", правильно? Видите, я тоже кое-что о вас поразузнал. Но, провалиться мне, если это важно. Слыхали такое имя - Бартоломью Португалец?";
			link.l1 = "Барт Португалец? Конечно, кто о нём не слышал, хотел бы я знать! Пират, мясник и мерзавец, насколько мне известно, а причём он в вашей истории?";
			link.l1.go = "Avendel_tavern_10";
		break;
		
		case "Avendel_tavern_10":
			dialog.text = "Самым распроклятым образом причём! Я выслеживал его последние полтора года - Голландская Компания дала за его голову неплохую цену. Но я не преуспел и потерял всё. А не так давно Компания утроила сумму, причём, с условием того, что треклятого пирата, сожри его селёдка, доставят к ним живьём и никак иначе!";
			link.l1 = "Насколько я знаю, это не так-то просто. В любом случае, какое мне до этого дело, Хьюго? Возникает ощущение, что ты водишь меня за нос!";
			link.l1.go = "Avendel_tavern_11";
		break;
		
		case "Avendel_tavern_11":
			dialog.text = "И не думал капитан, и не думал! Знаете, местный доктор – Питер Ван Шталь, милейший человек – он выдавал мне настойку, когда распроклятая голова по утрам трещала как от бортового залпа. Так вот, доктора уже второй день нет дома, и...";
			link.l1 = "Хьюго, моё терпение на исходе! Я обещал даме, что не буду дырявить тебя шпагой, но сойдут и кулаки! Клянусь – завтра твоя голова будет трещать так, что никакая настойка не поможет!";
			link.l1.go = "Avendel_tavern_12";
		break;
		
		case "Avendel_tavern_12":
			dialog.text = "Да постойте же, капитан! Послушайте: возле дома доктора, я видел пару человек, и узнал их – они с 'Альбатроса' - проклятого фрегата Португальца! И один из них говорил что-то о здоровье капитана! Понимаете, " + pchar.name + ", Бартоломью здесь, в Филипсбурге! Прямо у нас под носом, и он ранен, или нездоров, вот зачем им проклятый доктор!\nВряд ли Португалец, лопни его потроха, привёл сюда всю команду, но один я туда всё одно не сунусь! А вы явно знаете, с какой стороны у треклятой шпаги рукоять! Возьмите пару молодчиков покрепче, и мы найдём, где он прячется! Схватим его и сдадим властям!\nИ две тысячи полновесных, распроклятых дублонов, почитай у нас в кармане!";
			link.l1 = "Нет, Хьюго, с меня довольно болтовни. Даже если ты прав, я не буду в этом участвовать. Прощай.";
			link.l1.go = "Avendel_tavern_3";
			link.l2 = "А вот это уже интересно. Ты знаешь, где он прячется? Если всё выгорит, долю обсудим позже – медлить нельзя!";
			link.l2.go = "Avendel_tavern_13";
		break;
		
		case "Avendel_tavern_13":
			dialog.text = "Нет, капитан, я побоялся следить за этими ребятами. Если бы Одноглазый Пес меня заметил... бр-р! Но с вашими-то парнями мы быстро прочешем город – собирайте людей, и вперед! Проклятье, голландские дублоны уже нас заждались! Такой распроклятый шанс выпадает раз в жизни, укуси меня селедка!";
			link.l1 = "Похвальный энтузиазм... надеюсь, ты хоть из-за стола встать сможешь, головорез. Я отправляюсь на поиски немедленно, если хочешь – плетись следом, только не путайся под ногами.";
			link.l1.go = "Avendel_tavern_14";
		break;
		
		case "Avendel_tavern_14":
			DialogExit();
			SetFunctionTimerCondition("Portugal_DoctorOver", 0, 0, 2, false);
			pchar.quest.Portugal_Guard.win_condition.l1 = "location";
			pchar.quest.Portugal_Guard.win_condition.l1.location = "Marigo_houseF1";
			pchar.quest.Portugal_Guard.function = "CreatePortugalGuard";
			AddQuestRecord("Portugal", "1");
			NextDiag.Currentnode = "Avendel_tavern_repeat";
		break;
		
		case "Avendel_tavern_repeat":
			dialog.text = "Да-да, капитан, сейчас допью ром и присоединюсь к вам... Откуда начнём поиски?";
			link.l1 = "Ладно, сиди уже тут... помощник.";
			link.l1.go = "exit";
			Nextdiag.TempNode = "Avendel_tavern_repeat";
		break;
		
		case "Portugal_guard":
			dialog.text = "Ты, дружок, ошибся адресом. Давай, проваливай отсюда, живо!";
			link.l1 = "Хм. А вот мне кажется, что я как раз попал туда, куда надо...";
			link.l1.go = "Portugal_guard_1";
		break;
		
		case "Portugal_guard_1":
			dialog.text = "Ну, раз ты так считаешь - возражать не буду...";
			link.l1 = "...";
			link.l1.go = "Portugal_guard_2";
		break;
		
		case "Portugal_guard_2":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешить драться
			for (i=1; i<=3; i++)
			{
			sld = characterFromId("PortugalGuard_"+i);
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "OpenTheDoors");
			AddDialogExitQuest("MainHeroFightModeOn");
			pchar.quest.Portugal_Doctor.win_condition.l1 = "location";
			pchar.quest.Portugal_Doctor.win_condition.l1.location = "Marigo_RoomHouseF1";
			pchar.quest.Portugal_Doctor.function = "CreatePortugalDoctor";
		break;
		
		case "Bart_lay":
			dialog.text = "Круче к ветру, курвины дети... готовь бортовые... ах-ха-ха, моя красотка!";
			link.l1 = "Понятно...";
			link.l1.go = "exit";
			Nextdiag.TempNode = "Bart_lay";
		break;
		
		case "Portugal_doctor":
			pchar.quest.Portugal_DoctorOver.over = "yes";
			dialog.text = "Господи, кто вы? Уберите, ради Бога, оружие! Здесь же больной человек!";
			link.l1 = "Этот ваш 'человек' убил больше людей, чем вы видели за всю жизнь, доктор. С дороги!";
			link.l1.go = "Portugal_doctor_1";
		break;
		
		case "Portugal_doctor_1":
			dialog.text = "Он мой пациент, и не может даже встать, не то что защищаться! Неужели не видите? Прошу вас, уберите свою шпагу!";
			link.l1 = "А что с ним, чёрт возьми?";
			link.l1.go = "Portugal_doctor_2";
		break;
		
		case "Portugal_doctor_2":
			dialog.text = "Полагаю, это следствие ранения, возможно – оружие карибов, смазанное каким-то ядом... Он всё время в бреду, не может ни двигаться, ни говорить... а те люди, что приволокли меня сюда, сказали, что если он умрёт – я отправлюсь следом! Но я делаю всё что могу, скажите же им!";
			link.l1 = "Вам незачем более беспокоиться об этих людях, доктор. Мои ребята присмотрят за домом на всякий случай, а мне пора к губернатору. Полагаю, он будет рад. Не отлучайтесь, пока я не вернусь, док.";
			link.l1.go = "Portugal_doctor_3";
		break;
		
		case "Portugal_doctor_3":
			chrDisableReloadToLocation = false;
			DialogExit();
			LAi_SetStayType(npchar);
			Nextdiag.Currentnode = "Doctor_repeat";
			pchar.quest.Avendel_House.win_condition.l1 = "location";
			pchar.quest.Avendel_House.win_condition.l1.location = "Marigo_houseF1";
			pchar.quest.Avendel_House.function = "AvendelInHouse";
		break;
		
		case "Doctor_repeat":
			dialog.text = "Я никуда не уйду, не беспокойтесь. Давайте уже быстрее сдадим его властям и покончим с этим кошмаром.";
			link.l1 = "Конечно, я уже иду.";
			link.l1.go = "exit";
			Nextdiag.TempNode = "Doctor_repeat";
		break;
		
		case "Avendel_house":
			dialog.text = "У нас получилось, капитан! Мы нашли его – я же говорил, мы разбогатеем! Что будем делать дальше?";
			link.l1 = "Надеюсь, что так, Хьюго. В любом случае, пленный Португалец - это ещё не всё. Полагаю, мне следует отправиться к губернатору и обсудить вопрос нашего вознаграждения.";
			link.l1.go = "Avendel_house_1";
		break;
		
		case "Avendel_house_1":
			dialog.text = "Нет-нет, капитан, только не к распроклятому Томасу! Поверьте мне, этот пройдоха заберёт нашего пленника и, в лучшем случае, угостит вас чашечкой кофе! Его светлость та ещё рыбина – если вы хотите получить вознаграждение сполна, то нужно брать курс сразу на Кюрасао! Иначе – опомниться не успеете, как Португалец будет за семью треклятыми замками под надзором гарнизона – а нас с вами выпрут взашей, как попрошаек!";
			link.l1 = "Что же, если ты так в этом уверен...";
			link.l1.go = "Avendel_house_2";
		break;
		
		case "Avendel_house_2":
			dialog.text = "Уверен, капитан, проглоти распроклятая селёдка, уверен! Но помните: люди Бартоломью могут ещё быть в городе, да и внимание гарнизона, чтоб его якорем, привлекать не стоит. Нам надо решить, как незаметно вывезти Португальца на ваше судно.";
			link.l1 = "Хорошо... не хотелось бы, по дороге в Виллемстад отстреливаться от его фрегата. Есть предложения?";
			link.l1.go = "Avendel_house_3";
		break;
		
		case "Avendel_house_3":
			dialog.text = "Да, есть одна мыслишка – переоденем его во что-нибудь поприличнее, и выволочем через заднюю дверь, как перебравшего чёртова рому офицера! Никто и не заподозрит растреклятого пирата, поверьте!";
			link.l1 = "Не уверен, но лучшего плана у меня пока что нет. Попробую раздобыть какую-нибудь приличную одежду для нашего пассажира. А ты будь здесь - присматривай за Бартом и доком.";
			link.l1.go = "Avendel_house_4";
		break;
		
		case "Avendel_house_4":
			DialogExit();
			AddQuestRecord("Portugal", "3");
			LAi_ActorRunToLocation(npchar, "reload", "houseF1", "Marigo_houseF1", "goto", "goto2", "", -1);
			pchar.quest.Portugal_Cloves.win_condition.l1 = "Timer";
			pchar.quest.Portugal_Cloves.win_condition.l1.date.hour  = sti(GetTime());
			pchar.quest.Portugal_Cloves.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.Portugal_Cloves.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.Portugal_Cloves.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.Portugal_Cloves.function = "PortugalClovesOver";//1 сутки
			pchar.questTemp.Portugal = "Findcloves";
			LAi_SetStayType(npchar);
			npchar.dialog.currentnode = "Avendel_house_guard";
		break;
		
		case "Avendel_house_guard":
			dialog.text = "Не беспокойтесь, капитан, Португалец под надёжной охраной, хе-хе...";
			link.l1 = "Хотелось бы в это верить...";
			link.l1.go = "exit";
			Nextdiag.TempNode = "Avendel_house_guard";
		break;
		
		case "Portugal_doctor_4":
			dialog.text = "Я не вижу солдат, минхер. Где они? Вы сказали, что его арестуют, как только вы сообщите о том что случилось властям, так почему же нет солдат до сих пор?";
			link.l1 = "Их и не будет, минхер Ван Шталь. Я собираюсь обойтись своими силами, и как можно быстрее отплываю на Кюрасао с вашим пациентом. А теперь нужно переодеть... больного. Его слишком опасно вести через город в таком виде, а время нас не ждёт.";
			link.l1.go = "Portugal_doctor_5";
		break;
		
		case "Portugal_doctor_5":
			dialog.text = "Капитан, послушайте, я не могу справиться с его приступами – лишь облегчить жар на какое-то время. Он почти не приходит в сознание, всё время в бреду – нет сомнений, он умрёт и без прочих вмешательств, а корабельная качка убьёт его в считаные дни! Я дам вам микстуры, чтобы в дороге, вы могли...";
			link.l1 = "Нет, док, вы отправляетесь с нами. Во-первых, я не силён в медицине, а во-вторых, неужели вы хотите остаться и объяснять головорезам Португальца, куда исчез их капитан?";
			link.l1.go = "Portugal_doctor_6";
		break;
		
		case "Portugal_doctor_6":
			dialog.text = "Да... вы правы, пожалуй. Но, учтите – этот пират крепкий орешек, я видел людей, что не протянули и трёх дней, с простыми царапинами от индейского оружия. А, по словам притащивших меня головорезов, он в таком состоянии уже почти неделю! Тем не менее, готов утверждать - он не протянет долго в море, по самым смелым прогнозам, у нас есть не более трёх дней!\nПотом – я умываю руки. ";
			link.l1 = "За три дня до Кюрасао даже птица не долетит. Но, кажется, я знаю что делать! В Сент-Джонсе, на Антигуа, у меня есть один... гм, знакомый, он разбирается в медицине, и, если кто и сможет помочь нам, то это он. Дело за малым – успеть добраться туда прежде, чем Португалец отдаст концы. Собирайтесь док, мы отправляемся немедленно, а вашего пациента переправят следом!";
			link.l1.go = "Portugal_doctor_7";
		break;
		
		case "Portugal_doctor_7":
			DialogExit();
			AddQuestRecord("Portugal", "5");
			pchar.quest.Portugal_Cloves.over = "yes";
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", -1);
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, false);
			sld = characterFromId("Avendel");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload1", "none", "", "", "", -1);
			AddPassenger(pchar, sld, false);
			SetCharacterRemovable(sld, false);
			RemoveItems(PChar, "suit_1", 1);
			sld = characterFromId("Portugal");
			sld.model = "Port_B"; //меняем модель
			ChangeCharacterAddressGroup(sld, "My_Deck", "goto", "goto6");
			SetFunctionTimerCondition("Portugal_ToAntiguaOver", 0, 0, 4, false);
			pchar.questTemp.Portugal = "ToAntigua";
			//временно для тестов откроем комнату Джино, потом убрать
			LocatorReloadEnterDisable("SentJons_HouseF3", "reload4", false);
		break;
		
		case "Avendel_goodbye":
			dialog.text = "Жаль, что так вышло, капитан. Но – мы проиграли, и не видать нам распроклятого золотишка. Прощайте.";
			link.l1 = "Прощай, Хьюго.";
			link.l1.go = "Avendel_goodbye_1";
		break;
		
		case "Avendel_goodbye_1":
			DialogExit();
			chrDisableReloadToLocation = false;//открыть локацию
			npchar.lifeday = 0;
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", -1);
		break;
		
		case "Portugal_doctor_9":
			dialog.text = "...";
			link.l1 = "Док, немедленно подготовьте больного к перевозке на берег. Шлюпка уже спущена на воду. Поторопитесь!";
			link.l1.go = "Portugal_doctor_10";
		break;
		
		case "Portugal_doctor_10":
			dialog.text = "Уже бегу, минхер.";
			link.l1 = "...";
			link.l1.go = "Portugal_doctor_11";
		break;
		
		case "Portugal_doctor_11":
			DialogExit();
			AddQuestRecord("Portugal", "7");
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", -1);
			sld = characterFromId("Portugal");
			ChangeCharacterAddressGroup(sld, "SentJons_HouseF3_Room2", "quest", "quest1");
			sld = characterFromId("Jino");
			ChangeCharacterAddressGroup(sld, "SentJons_HouseF3_Room2", "goto", "goto3");
			pchar.quest.Portugal_ToAntiguaOver.over = "yes";//снять таймер
			pchar.questTemp.Portugal = "TreatmentStart";
			pchar.quest.Portugal_Ill.win_condition.l1 = "Timer";
			pchar.quest.Portugal_Ill.win_condition.l1.date.hour  = sti(GetTime());
			pchar.quest.Portugal_Ill.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 4);
			pchar.quest.Portugal_Ill.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 4);
			pchar.quest.Portugal_Ill.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 4);
			pchar.quest.Portugal_Ill.function = "Portugal_ToAntiguaOver";//не придет через 4 дня - Португальцу капут
		break;
		
		case "Avendel_Room":
			dialog.text = "В этом доме всё насквозь провоняло треклятыми микстурами! Если Португалец тут отдаст Богу душу, будет вовсе удивительно – тут можно просто глубоко вздохнуть и вылечишься от всех чёртовых хворей!\nА его парни найдут нас по запаху через половину проклятого Архипелага!";
			link.l1 = "Хьюго, оставь при себе свои шутки. Я поставил людей на улице, приглядывать за домом, но ещё один сторож нашему гостю не помешает. Следи за ним в оба, и постарайся не так сквернословить, иначе, Джино выдаст тебе какую-нибудь микстуру - я уверен, это лечится.";
			link.l1.go = "Avendel_Room_1";
		break;
		
		case "Avendel_Room_1":
			dialog.text = "Не стоит беспокойства, капитан! Я буду неусыпно следить за нашими денежками – никуда они не сбегут, даже если полностью поправятся! И умоляю, не нужно никаких лекарств!";
			link.l1 = "Можешь ведь, когда захочешь. Будь начеку, мне пора.";
			link.l1.go = "exit";
			chrDisableReloadToLocation = false;
		break;
		
		case "Avendel_Room_2":
			dialog.text = "Уходим, капитан? Отлично! Давно пора! Сегодня весь день тут по улице шастают чёрто... какие-то подозрительные ребята. Они не похожи на людей Португальца, но явно что-то вынюхивали – надо быть настороже, капитан!";
			link.l1 = "Хорошо, спасибо за предупреждение, Хьюго. Отправляемся на корабль.";
			link.l1.go = "Avendel_Room_3";
		break;
		
		case "Avendel_Room_3":
			DialogExit();
			chrDisableReloadToLocation = false;
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", -1);
			//ставим Португальца
			sld = characterFromId("Portugal");
			ChangeCharacterAddressGroup(sld, "SentJons_HouseF3", "goto", "goto1");
			LAi_SetActorType(sld);
			LAi_ActorFollowEverywhere(sld, "", -1);
		break;
		
		case "Portugal_hunter":
			dialog.text = "Капитан, как долго мы ждали этой встречи! А кто это за вами? Никак сам Бартоломэо Португалец собственной бородатой рожей, ха, а Лысый Пьер был прав – это он! Отойдите в сторонку, кэп, мы его заберём и никто не пострадает.";
			link.l1 = "Кто вы такие, чёрт возьми! Прочь с дороги, или пострадавшие будут прямо сейчас!";
			link.l1.go = "Portugal_hunter_1";
		break;
		
		case "Portugal_hunter_1":
			dialog.text = "Какой грозный, глядите-ка парни! Послушай меня, щенок – не стой между Лео Кордом и его деньгами! Мы выслеживали Португальца почти полгода, и вот он у нас в руках, а ты опусти эту зубочистку, и отваливай, пока цел! Мы не жадные, нам он сойдёт и мёртвым, ха-ха!";
			link.l1 = "Ну это уже слишком! Защищайтесь, господа оборванцы!";
			link.l1.go = "Portugal_hunter_2";
		break;
		
		case "Portugal_hunter_2":
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешим драться
		DialogExit();
		sld = characterFromId("Portugal");
		LAi_group_Register("Bart_Portugal");
		LAi_group_SetRelation("Bart_Portugal", LAI_GROUP_PLAYER, LAI_GROUP_FRIEND);
		LAi_group_MoveCharacter(sld, "Bart_Portugal");
		for (i=1; i<=5; i++)
		{
		sld = characterFromId("PortugalHunter_"+i);
		LAi_SetWarriorType(sld);
		LAi_group_MoveCharacter(sld, "EnemyFight");
		}
		LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
		LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
		LAi_group_SetCheck("EnemyFight", "PortugalHunterDied");
		AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "Avendel_street":
			sld = characterFromId("Portugal");
			if (LAi_GetCharacterHP(sld) > 0)
			{
				dialog.text = "Так и знал, что что-то тут не чисто! А лихо вы их, капитан! Но, нам пора – у Лео Корда, гореть ему на сковородке, полно головорезов и неплохой корабль! Нужно быстрее убираться с острова!";
				link.l1 = "Верно подмечено, Хьюго, и я рад, что в ту щель, куда ты забился на время драки не залетела шальная пуля.";
				link.l1.go = "Avendel_street_1";
			}
			else
			{
				dialog.text = "Жаль, что так вышло, капитан. Но – мы проиграли, и не видать нам распроклятого золотишка. Прощайте.";
				link.l1 = "Прощай, Хьюго.";
				link.l1.go = "Avendel_goodbye_1";
				sld = characterFromId("PortugalDoctor");
				RemovePassenger(Pchar, sld);
				sld.lifeday = 0;
				RemovePassenger(Pchar, npchar);
				AddQuestRecord("Portugal", "35");
				CloseQuestHeader("Portugal");
				pchar.questTemp.Portugal = "end";
			}
		break;
		
		case "Avendel_street_1":
			dialog.text = "Я... я прикрывал тыл, капитан! Вы неплохо справлялись, но вдруг кто-нибудь зашёл бы с другой стороны улицы?";
			link.l1 = "Может поэтому ты и не преуспел в своём деле? Всё, хватит болтать – на корабль! Время не ждёт!";
			link.l1.go = "Avendel_street_2";
		break;
		
		case "Avendel_street_2":
			DialogExit();
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "", 10);
			AddQuestRecord("Portugal", "8");
			pchar.quest.Portugal_seahunter.win_condition.l1 = "location";
			pchar.quest.Portugal_seahunter.win_condition.l1.location = "Antigua";
			pchar.quest.Portugal_seahunter.function = "PortugalSeaHunter";
			pchar.quest.Portugal_martinique.win_condition.l1 = "location";
			pchar.quest.Portugal_martinique.win_condition.l1.location = "FortFrance_town";
			pchar.quest.Portugal_martinique.function = "PortugalOnMartinique";
		break;
		
		case "Portugal_doctor_12":
			dialog.text = "Капитан, Португалец совсем плох, нам нужна остановка!";
			link.l1 = "Затем мы сюда и прибыли, не беспокойтесь, минхер ван Шталь, наше путешествие почти окончено. Я сниму комнату в таверне, наш пленник полежит там пару дней, и мы продолжим путь.";
			link.l1.go = "Portugal_doctor_13";
		break;
		
		case "Portugal_doctor_13":
			DialogExit();
			LAi_ActorRunToLocation(npchar, "reload", "reload4_back", "none", "", "", "", 5);
		break;
		
		case "Portugal_doctor_14":
			dialog.text = "Минхер капитан, я присмотрю за Португальцем, ему сейчас нужен полный покой.";
			link.l1 = "Понял, я вас оставляю, всё в порядке, док. Проклятье – да сколько мне ещё носится с этим пиратом, как с больной тётушкой? То ему вредно, то ему нужно! Можно подумать, я нанимался в няньки, а не... хм, простите, доктор, накипело... Всего доброго.";
			link.l1.go = "Portugal_doctor_15";
		break;
		
		case "Portugal_doctor_15":
			DialogExit();
			AddQuestRecord("Portugal", "15");
			pchar.quest.Portugal_patrol.win_condition.l1 = "location";
			pchar.quest.Portugal_patrol.win_condition.l1.location = "FortFrance_town";
			pchar.quest.Portugal_patrol.function = "CreateFrancePatrol";
		break;
		
		case "Portugal_patrol":
			dialog.text = "Месье, это вы капитан "+GetFullName(pchar)+", чей корабль сегодня прибыл в гавань?";
			link.l1 = "Вы не ошиблись, чем могу быть полезен?";
			link.l1.go = "Portugal_patrol_1";
		break;
		
		case "Portugal_patrol_1":
			dialog.text = "Вас срочно желает видеть его светлость Жак Дил ду Парке, губернатор нашей колонии. Дело не терпит отлагательств!";
			link.l1 = "Хорошо, мсье, я навещу его превосходительство сегодня же.";
			link.l1.go = "Portugal_patrol_2";
		break;
		
		case "Portugal_patrol_2":
			DialogExit();
			chrDisableReloadToLocation = false;//открыть локацию
			pchar.questTemp.Portugal = "MartiniqueGovernor";
			LAi_ActorGoToLocation(npchar, "reload", "reload4_back", "none", "", "", "", -1);
			AddQuestRecord("Portugal", "9");
		break;
		
		case "Avendel_seapatrol":
			dialog.text = "Вот мы и на Мартинике, капитан! Наши денежки уже не за горами...";
			link.l1 = "Если Португалец доживёт до Виллемстада, конечно. Хьюго, мне нужно будет отлучиться на корабль, так что охранять дока и его пациента предстоит тебе.";
			link.l1.go = "Avendel_seapatrol_1";
		break;
		
		case "Avendel_seapatrol_1":
			dialog.text = "Отлучиться? Зачем? Оставите пару матросов в помощь?";
			link.l1 = "Увы, нет. Не думаю, что тут, посреди города, вам что-то будет грозить – гарнизон поднят по тревоге, и солдат на улицах больше обычного. Возле острова видели большое судно... предположительно – пиратское. И его светлость губернатор, попросил меня усилить патрули своим кораблём.";
			link.l1.go = "Avendel_seapatrol_2";
		break;
		
		case "Avendel_seapatrol_2":
			dialog.text = "Судно? Пиратское? Это ведь может быть 'Альбатрос'? Или кто-нибудь из коллег нашего знакомого, Лео Корда!";
			link.l1 = "А может, это обычное пиратское корыто. Так или иначе, Хьюго, если этот корабль по наши души, то лучше я его встречу наперёд, в компании местных сторожевых судов, да ещё и за казённое золото, чем всю дорогу до Кюрасао озираться через корму. А если тревога ложная – то хоть не придётся просиживать штаны в таверне несколько дней.";
			link.l1.go = "Avendel_seapatrol_3";
		break;
		
		case "Avendel_seapatrol_3":
			dialog.text = "Подумайте, капитан – разумно ли оставлять про... Португальца почти без присмотра, если в округе, возможно, болтается его фрегат? Приняв гонорар губернатора, вы рискуете нашим вознаграждением!";
			link.l1 = "Хватит болтать, Хьюго Авендел! Капитан здесь я, и решаю тоже я. Так что изволь делать то, что тебе прикажут. Отправляйся в таверну и не спускай глаз с доктора и Португальца, пока я не вернусь на берег.";
			link.l1.go = "Avendel_seapatrol_4";
		break;
		
		case "Avendel_seapatrol_4":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload4_back", "none", "", "", "", 10.0);
			chrDisableReloadToLocation = false;//открыть локацию
			LocatorReloadEnterDisable("Fortfrance_town", "reload4_back", true);//закрыть таверну
		break;
		
		case "Avendel_seapatrol_5":
			dialog.text = "Вы вернулись, капитан – наконец-то! У нас плохие новости – Португалец пропал, а с ним и док!";
			link.l1 = "Как пропал?! Куда ты смотрел, остолоп!";
			link.l1.go = "Avendel_seapatrol_6";
		break;
		
		case "Avendel_seapatrol_6":
			dialog.text = "Готов биться об заклад – то судно из-за которого весь шум поднялся – 'Альбатрос'. Я видел людей Португальца – они ввалились в таверну и я... я сбежал. Простите, но встретиться с Одноглазым Псом лицом к лицу – это слишком, даже за такие деньги!";
			link.l1 = "Проклятье! Расскажи, хоть что произошло в таверне?";
			link.l1.go = "Avendel_seapatrol_7";
		break;
		
		case "Avendel_seapatrol_7":
			dialog.text = "Говорю же – я ничего не видел – только заметил через окно Франца Гарке и его ребят, поднимающихся на крыльцо – сразу побежал в кухню и выскочил через заднюю дверь... И то – едва успел! Это случилось вчерашним вечером – и я не знал, как подать вам весточку в море-то...";
			link.l1 = "Да, смелости тебе действительно не занимать... Ладно, дам тебе ещё один шанс – мы отправляемся на поиски. Я слишком долго спасал шкуру этого негодяя, и, уже начал считать её почти что собственностью! У нас ещё есть время попробовать их перехватить - начнём с таверны, может кто-то видел больше, чем твои пятки. Иди, собирайся!";
			link.l1.go = "Avendel_seapatrol_8";
		break;
		
		case "Avendel_seapatrol_8":
			DialogExit();
			bQuestDisableMapEnter = false;//открыть карту
			DeleteAttribute(pchar, "GenQuest.CannotWait");//можно мотать время
			chrDisableReloadToLocation = false;
			LAi_ActorFollowEverywhere(npchar, "", -1);
			SetFunctionTimerCondition("MartiniquePortugalOver", 0, 0, 2, false); //таймер
			sld = characterFromId("PortugalDoctor");
			sld.lifeday = 0;//убираем доктора
			RemovePassenger(Pchar, sld);	
			sld = characterFromId("Portugal");
			ChangeCharacterAddressGroup(sld, "none", "", "");//Португальца спрячем
			LocatorReloadEnterDisable("Fortfrance_tavern", "reload2_back", true);//комнату закроем
			AddQuestRecord("Portugal", "12");
		break;
		
		case "Avendel_seapatrol_9":
			dialog.text = "Слышали, капитан – он же описал Одноглазого Пса – Франца Гарке, о котором я вам говорил. А кастилец шепелявый – Эрнандо Васкес, Кровавый дон – мясник из Веракрус – его-то я не успел заметить!";
			link.l1 = "Успокойся, Хьюго. Я уверен, Бартоломью ещё на острове, он слишком слаб, даже если ему и полегчало. И я, кажется, даже знаю, где его искать! Мы настигнем их – от своей награды я так просто не отступлюсь! Если не струсишь – следуй за мной, ещё не всё потеряно.";
			link.l1.go = "Avendel_seapatrol_10";
		break;
		
		case "Avendel_seapatrol_10":
			DialogExit();
			bDisableFastReload = false;//открыть быстрый переход
			pchar.questTemp.Portugal = "PortugalLeFransua";//в Ле Франсуа
			AddQuestRecord("Portugal", "13");
			LAi_LocationDisableOfficersGen("LeFransua_tavern", true);//офицеров не пускать
		break;
		
		case "LeFransua_pirate":
			dialog.text = "Много вопросов задаёшь, капитан... Постой-ка, а не тот ли ты вертлявый субчик, из Филипсбурга? Бегал, бегал от нас, и гляди - сам пришёл...";
			link.l1 = "Не спеши радоваться, собака!";
			link.l1.go = "LeFransua_pirate_1";
		break;
		
		case "LeFransua_pirate_1":
			DialogExit();
			pchar.quest.MartiniquePortugalOver.over = "yes"; //снять таймер
			chrDisableReloadToLocation = true;
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			for (i=1; i<=3; i++)
			{
			sld = characterFromId("LeFransuaPirate_"+i);
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "LeFransuaAfterFight");
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "FranzGarke":
			dialog.text = "...ты, крабий потрох, всё нам расскажешь, попомни моё слово, крыса, всё! До, или после того, как с тебя сдерут шкуру и повесят на рее вместо марселя... А ты ещё кто такой? Тысяча акул, ни в чём на этих обезьян нельзя положиться! Придётся самому...";
			link.l1 = "Кажется, я вам помешал, господа?";
			link.l1.go = "FranzGarke_1";
		break;
		
		case "FranzGarke_1":
			DialogExit();
			chrDisableReloadToLocation = true;
			sld = characterFromId("FranzGarke");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "LeFransua_PortugalTalk");
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "Portugal_LFTalk":
			dialog.text = "Вы как нельзя вовремя... полагаю, именно вам я обязан тем, что дожил до этого дня?";
			link.l1 = "Ты не ошибся. Моё имя - " + GetFullName(pchar) + ", и ты, Португалец, всё ещё мой пленник. Так что не задавай лишних вопросов – нам пора.";
			link.l1.go = "Portugal_LFTalk_1";
		break;
		
		case "Portugal_LFTalk_1":
			dialog.text = "Постойте, капитан... В посёлке полно людей Васкеса, и нам не дадут так просто уйти. Если вы дадите мне саблю – будет немного проще.";
			link.l1 = "А ты не очень то ладишь с бывшими подельниками, да? Хорошо, лишний клинок не помешает – возьми оружие Одноглазого, и будь на виду!";
			link.l1.go = "Portugal_LFTalk_2";
			link.l2 = "Не думаешь же ты, что я и впрямь дам тебе оружие и повернусь спиной?! Просто держись позади.";
			link.l2.go = "Portugal_LFTalk_4";
			pchar.quest.Portugal_LeFransua.win_condition.l1 = "location";
			pchar.quest.Portugal_LeFransua.win_condition.l1.location = "LeFransua_town";
			pchar.quest.Portugal_LeFransua.function = "CreateVaskezsPirates";
			bDisableFastReload = true;//закрыть переход
		break;
		
		case "Portugal_LFTalk_2":
			dialog.text = "Не переживайте, капитан, я скорее сдохну, чем попаду в руки Васкеза снова.";
			link.l1 = "Хочется верить. Пошли, нельзя терять время.";
			link.l1.go = "Portugal_LFTalk_3";
		break;
		
		case "Portugal_LFTalk_3":
			DialogExit();
			GiveItem2Character(npchar, "blade_17");
			EquipCharacterbyItem(npchar, "blade_17");
			GiveItem2Character(npchar, "pistol6");
			EquipCharacterbyItem(npchar, "pistol6");
			TakeNItems(npchar, "bullet", 50);
			AddItems(npchar, "gunpowder", 50);
			TakeNItems(npchar, "potion2", 3);
			LAi_SetCharacterUseBullet(npchar, "bullet");
			pchar.questTemp.Portugal.Condition1 = "true";
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
		break;
		
		case "Portugal_LFTalk_4":
			dialog.text = "Зря, желай я вам смерти, помог бы Одноглазому...";
			link.l1 = "Но ты и мне не помог, так что прекращай болтать и вперёд!";
			link.l1.go = "Portugal_LFTalk_5";
		break;
		
		case "Portugal_LFTalk_5":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
		break;
		
		case "Vaskezs_pirate":
			PlaySound("VOICE\Russian\EvilPirates01.wav");
			dialog.text = "А-ать! Вот они! Держи их!";
			link.l1 = "...";
			link.l1.go = "Vaskezs_pirate_1";
		break;
		
		case "Vaskezs_pirate_1":
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешим драться
			DialogExit();
			if (CheckAttribute(pchar, "questTemp.Portugal.Condition1"))
			{
				sld = characterFromId("Portugal");
				LAi_SetImmortal(sld, false);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			}
			for (i=1; i<=9; i++)
			{
				sld = characterFromId("VaskezsPirate_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "VaskezsPiratesDied");
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "Avendel_LeFransua":
			chrDisableReloadToLocation = false;
			bDisableFastReload = false;//открыть переход
			sld = characterFromId("Portugal");
			if (LAi_GetCharacterHP(sld) > 0)
			{
				dialog.text = "Отличная работа! Вы свалили Одноглазого Пса – вот это я понимаю - мастер! Скольких ещё его ребят вы отправили на сковородки?";
				link.l1 = "Я не считал, я дрался. А где был ты, Хьюго?";
				link.l1.go = "Avendel_LeFransua_1";
			}
			else
			{
				dialog.text = "Жаль, что так вышло, капитан. Но – мы проиграли, и не видать нам распроклятого золотишка. Прощайте.";
				link.l1 = "Прощай, Хьюго.";
				link.l1.go = "Avendel_goodbye_1";
				RemovePassenger(Pchar, npchar);
				CloseQuestHeader("Portugal");
				pchar.questTemp.Portugal = "end";
			}
		break;
		
		case "Avendel_LeFransua_1":
			dialog.text = "Я... обеспечивал безопасный отход... тыл прикрывал, в общем.";
			link.l1 = "Ну, это уже ни в какой фарватер... Хью Авендел, твоя трусость превзошла все мои представления – ты знаешь, как нелегко нам пришлось? Мы справились просто чудом!";
			link.l1.go = "Avendel_LeFransua_2";
		break;
		
		case "Avendel_LeFransua_2":
			dialog.text = "Не горячитесь, капитан... да, сознаюсь – спрятался. Но ведь я нашёл вам это дельце! Вспомните – я вас привёл к нему! Впрочем... имея в виду ваше справедливое негодование, я согласен на треть от суммы награды.";
			link.l1 = "Прекрасно! Теперь ты ещё и торгуешься? Нет, друг мой – твоё участие в этом деле закончилось! Свои деньги ты упустил в таверне Сен-Пьера. Ты бросил их там и сбежал, так что говорить более не о чем.";
			link.l1.go = "Avendel_LeFransua_3";
		break;
		
		case "Avendel_LeFransua_3":
			dialog.text = "Капитан, вы явно преувеличиваете... Хорошо – я согласен на четверть... пятую часть! Десять процентов!!";
			link.l1 = "Не испытывай моё терпение! Убирайся с глаз долой! Мне не нужен в команде трус, особенно сейчас, когда счёт пойдёт на часы!";
			link.l1.go = "Avendel_LeFransua_4";
		break;
		
		case "Avendel_LeFransua_4":
			dialog.text = ""+pchar.name+", вы не находите это несколько нечестным?";
			link.l1 = "Причина и следствие, Хьюго... Ты свой выбор сделал, так что прощай. И напоследок: сделай выводы и не лезь больше в подобные авантюры, это явно не твоё.";
			link.l1.go = "Avendel_LeFransua_5";
		break;
		
		case "Avendel_LeFransua_5":
			DialogExit();
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", -1);
			sld = characterFromId("Portugal");
			sld.dialog.currentnode = "Portugal_LeFransua";
			LAi_ActorDialog(sld, pchar, "", -1, 0);
			pchar.questTemp.Portugal.GG2 = "true"; // Jason Дороже золота
		break;
		
		case "Portugal_LeFransua":
			dialog.text = "Сбрасываете балласт, капитан? Оно и верно, хе... Васкез ещё на свободе, а на 'Альбатросе' полно пушек и людей – ставлю эти шикарные штаны против старого платка, что Эрнандо не даст нам уйти из этих вод.";
			link.l1 = "Что же, значит придётся лично его поприветствовать. Шагайте, мсье Португалец, и постарайтесь поменьше болтать – мы снимаемся с якоря при первой возможности.";
			link.l1.go = "Portugal_LeFransua_1";
		break;
		
		case "Portugal_LeFransua_1":
			DialogExit();
			chrDisableReloadToLocation = false;
			LAi_ActorFollowEverywhere(npchar, "", -1);
			pchar.quest.Portugal_LeFransua1.win_condition.l1 = "location";
			pchar.quest.Portugal_LeFransua1.win_condition.l1.location = "Martinique";
			pchar.quest.Portugal_LeFransua1.function = "CreateVaskezsFrigate";
		break;
		
		case "VaskezsHelper_abordage":
			dialog.text = "Ну, чего ты ждёшь, лопни твоя селезёнка!";
			link.l1 = "Где Эрнандо Васкез? Говори, и я сохраню тебе жизнь.";
			link.l1.go = "VaskezsHelper_abordage_1";
		break;
		
		case "VaskezsHelper_abordage_1":
			dialog.text = "Убирайся к Дьяволу со своими вопросами!";
			link.l1 = "После вас, сударь...";
			link.l1.go = "VaskezsHelper_abordage_2";
		break;
		
		case "VaskezsHelper_abordage_2":
			DialogExit();
			QuestAboardCabinDialogExitWithBattle(""); 	
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "Portugal_treasure":
			bQuestDisableMapEnter = false;
			if (CheckAttribute(pchar, "questTemp.Portugal.Condition1") && CheckAttribute(pchar, "questTemp.Portugal.Condition2"))
			{
				dialog.text = "А вот и мой отчаянный друг, наконец-то мы можем побеседовать! Поздравляю, капитан – уложить Одноглазого Пса, а потом разнести 'Альбатрос' - это не каждому по плечу! Вообще, вы столько сделали в последнее время во имя спасения моей шкуры... Наверное, я должен сказать вам спасибо?";
				link.l1 = "Скажешь, когда спляшешь на виселице, или что там тебе приготовили в Виллемстаде.";
				link.l1.go = "Portugal_treasure_6";
			}
			else
			{
				dialog.text = "А вот и мой отчаянный друг, наконец-то мы можем побеседовать! Поздравляю, капитан – уложить Одноглазого Пса один на один, само по себе деяние достойное какой-нибудь занюханной песни, ха! Вообще, вы столько сделали в последнее время, во имя спасения моей шкуры, наверное, я должен сказать вам спасибо?";
				link.l1 = "Скажешь, когда спляшешь на виселице, или что там тебе приготовили в Виллемстаде.";
				link.l1.go = "Portugal_treasure_1";
			}
		break;
		
		case "Portugal_treasure_1":
			dialog.text = "Удивительно! Вы почти две недели только и делаете, что спасаете жизнь совершенно незнакомому человеку, привозите его в свой дом, защищаете его с клинком в руках, а теперь спокойно отправите на эшафот? С трудом верится... я вот склонен считать вас почти своим другом, хе-хе.";
			link.l1 = "Пират, взывающий к благородству? Португалец, ты надо мной насмехаешься? Я спасал тебя с единственной целью – позволить убийце и разбойнику предстать перед справедливым судом!";
			link.l1.go = "Portugal_treasure_2_1";
			link.l2 = "Другом... звучит, как насмешка. Но, тем не менее, в чём-то ты прав. Это будет бесчестно с моей стороны, Португалец...";
			link.l2.go = "Portugal_treasure_2_2";
		break;
		
		case "Portugal_treasure_2_1":
			dialog.text = "Да уж, заливайте, капитан! Готов поспорить на всё те же кружевные штаны, что сейчас на мне – деньги Компании, обещанные за удовольствие принимать в гостях мою особу – вот, что вас прельстило! Не пытайтесь казаться честнее, чем вы есть, сударь мой – вам это не идёт.";
			link.l1 = "А вот это уже мне судить. Пожалуй, закончим наш разговор. Пора отправляться в Виллемстад.";
			link.l1.go = "Portugal_treasure_3";
		break;
		
		case "Portugal_treasure_2_2":
			dialog.text = "Видимо, благородство ещё иногда встречается в наши дни... Жаль, что оно сильно стеснено деньгами, да, капитан?";
			link.l1 = "Странно слышать такое от висельника и пирата, Португалец. Я отпущу тебя... не спрашивай почему, просто убирайся к чёрту в первом же порту. И запомни: если когда-нибудь придёт день, в котором мы с тобой снова встретимся - я закончу начатое без сожалений.";
			link.l1.go = "Portugal_treasure_4";
		break;
		
		case "Portugal_treasure_3":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);//запрет диалога
			pchar.questTemp.Portugal.Villemstad = "true";//сдать губернатору
			AddQuestRecord("Portugal", "21");
		break;
		
		case "Portugal_treasure_4":
			dialog.text = "Вот как! Это мне по душе, капитан! Не прикажете подать в трюм немного рому? Ну, знаете – отпраздновать ваши рыцарские качества, наше взаимопонимание и отсрочку моего приговора?";
			link.l1 = "Не ёрничай – ты всё ещё пленник. До первого берега. Прощай.";
			link.l1.go = "Portugal_treasure_5";
		break;
		
		case "Portugal_treasure_5":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);//запрет диалога
			pchar.quest.Remove_Portugal.win_condition.l1 = "Location_Type";
			pchar.quest.Remove_Portugal.win_condition.l1.location_type = "town";
			pchar.quest.Remove_Portugal.function = "RemovePortugal";
			AddQuestRecord("Portugal", "20");
		break;
		
		case "Portugal_treasure_6":
			dialog.text = "Вот значит как... виселица. Ну что же, вполне ожидаемо. Да только выслушайте, что я скажу, капитан. Вы так тряслись, чтобы я дожил до верёвки, и я не могу это не оценить. Но и просить вас изменить своё решение просто так, будет, по меньшей мере глупо, да? Тогда, что вы скажете, если я предложу кое-что взамен? Так сказать, сделку, а?";
			link.l1 = "Ничего не скажу, Португалец. Ты пират и негодяй, и в Виллемстаде, ты ответишь за свои преступления.";
			link.l1.go = "Portugal_treasure_2_1";
			link.l2 = "Сделка? А что ты можешь предложить мне?";
			link.l2.go = "Portugal_treasure_7";
			link.l3 = "Не нужна мне твоя сделка... просто проваливай с глаз моих в первом же порту. У тебя сегодня счастливый день.";
			link.l3.go = "Portugal_treasure_4";
		break;
		
		case "Portugal_treasure_7":
			dialog.text = "Знаете, такое упорное спасение моей жизни, пусть и с не очень приятными мне целями, всё равно заслуживает некой признательности. А Бартоломео Португальцу не чужда благодарность. Послушайте – за месяц до нашей... встречи с вами мы взяли одно судно Голландской Компании. Они дрались до последнего, но в трюмах были лишь ядра и крысы\nМоим ребятам это пришлось не по нраву, но в капитанской каюте я обнаружил весьма занятный сундучок и письменный приказ. Это был курьерский корабль, доставляющий в Европу пробные образцы с приисков где-то в Гайяне за Амазонией... в сундучке были чистейшие алмазы и рубины – целое состояние!";
			link.l1 = "Занятный приз... теперь я понимаю, откуда у Компании такой к тебе интерес, но в чём суть истории?";
			link.l1.go = "Portugal_treasure_8";
		break;
		
		case "Portugal_treasure_8":
			dialog.text = "Васкез – мой старпом, и Франц Гарке уже давно держали команду в кулаке, и я решил воспользоваться выпавшим мне шансом. Я скрыл камни от них, и сжёг письмо. Голландец сильно потрепал нашу оснастку во время абордажа, и 'Альбатрос' пришлось завести в одну бухточку на маленьком островке на севере архипелага. Там, пока все искали дерево для укрепления мачты и латали дыры в борту, я ненадолго отлучился\nПрипрятал камушки – сами понимаете, хранить их на судне было весьма опасно, учитывая обстоятельства. Я планировал сбежать в первом же порту – угнать или купить лодчонку и смотаться на островок за своим призом – а там... прости-прощай прежняя жизнь! Европа, тихий особнячок и всё прочее...";
			link.l1 = "И что не заладилось?";
			link.l1.go = "Portugal_treasure_9";
		break;
		
		case "Portugal_treasure_9":
			dialog.text = "Да практически всё! На этом чёртовом островке оказалась целая орава местных людоедов – то ли приплыли поохотиться, то ли живут там – не знаю. Они напали на нас, когда я вернулся на побережье. Пришлось спешно отчаливать, отбиваясь от разъярённых дикарей – там-то меня и зацепило. Думал, царапина – а оно вон как вышло\nЧерез день я слёг в лихорадке, и, подозреваю, метаясь в бреду, выболтал что-то про камни. Франц и Васкез смекнули, что я припрятал на островке, но не знали где, а блуждать там под стрелами канибалов и копать каждую кочку им не улыбалось. Вот мерзавцы и потащили меня в ближайший порт в поисках доктора – нашего-то ядром зашибло, когда брали Голландца\nТак я и попал к тому докторишке в Филипсбурге - они хотели лишь привести меня в сознание, чтобы выпытать где и закопал камешки, а после – порезать на корм крабам... Их очень расстроило известие об уплывших из-под самого носа денежках, хе-хе...";
			link.l1 = "Не могу сказать, что я их осуждаю – ты пытался провести своих людей. Итак – к чему вся эта история?";
			link.l1.go = "Portugal_treasure_10";
		break;
		
		case "Portugal_treasure_10":
			dialog.text = "Это шакальё - не люди, поверьте, тем более, все они теперь на своём месте... на сковородке у чертей, ха-ха! А я могу назвать вам место и островок, где всё случилось – в уплату, скажем так, моего долга за ваши хлопоты. ";
			link.l1 = "Нет, Бартоломью – твоё предательство соратников меня окончательно убедило в твоей низости. Виллемстад и законное возмездие – вот что тебя ждёт. Никаких сделок.";
			link.l1.go = "Portugal_treasure_2_1";
			link.l2 = "И я должен поверить, что эти камни действительно есть, и лежат там, где ты укажешь? Впрочем – что я теряю... Сделкой эта история началась, будет справедливо, если она ею и закончится. Я принимаю твои условия, Португалец.";
			link.l2.go = "Portugal_treasure_11";
		break;
		
		case "Portugal_treasure_11":
			dialog.text = "Считайте это скромной благодарностью. Эх, узнать бы потом, сколько стоила шкура Бартоломео Португальца в пересчёте на звонкие песо, ха! Хотя и хотелось бы мне верить, что дело не в деньгах, но всё равно – я признателен вам капитан... за всё, хе-хе\nОстровок этот - Теркс, а камни я спрятал в джунглях недалеко от побережья. Найдите корявое высохшее дерево - оно одно там такое. У его ствола я и закопал сундучок. Так что не забудьте захватить лопату. Удачной охоты...";
			link.l1 = "Хорошо, я запомню, а ты можешь взять шлюпку прямо сейчас и отправляться прочь с моего судна. Прощай.";
			link.l1.go = "Portugal_treasure_12";
		break;
		
		case "Portugal_treasure_12":
			dialog.text = "И ещё одно, напоследок, капитан. Полагаю, там всё ещё полно этих проклятущих дикарей, но вам следует опасаться не только их. Васкеза ведь не было на борту 'Альбатроса', когда вы его разносили по щепкам, так? Кровавый Дон слишком хитёр... оглядывайтесь почаще, пока не увидите его в петле или с пулей в голове.";
			link.l1 = "Спасибо за предупреждение Португалец, а теперь – соизволь всё же покинуть мой корабль... не искушай судьбу.";
			link.l1.go = "Portugal_treasure_13";
		break;
		
		case "Portugal_treasure_13":
			DialogExit();
			LAi_SetImmortal(npchar, false);
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "", 2.0);
			AddQuestRecord("Portugal", "23");
			pchar.quest.Portugal_Terks.win_condition.l1 = "location";
			pchar.quest.Portugal_Terks.win_condition.l1.location = "Terks_Jungle_01";
			pchar.quest.Portugal_Terks.function = "CreateHollIndBattle";
		break;
		
		case "Avendel_Marigo":
			pchar.quest.SetAvendelMarigoOver.over = "yes"; //снять таймер
			dialog.text = "О, кого я вижу! Капитан "+pchar.name+" собственной персоной! Не желаете пропустить кружечку?";
			link.l1 = "Знаешь, не сказал бы, что я рад тебя видеть. Но, возможно тогда на Мартинике я несколько... погорячился, да.";
			link.l1.go = "Avendel_Marigo_1";
		break;
		
		case "Avendel_Marigo_1":
			dialog.text = "Пустое, капитан! Что было – то было. В конце концов, я действительно дал вам повод. Однако, вы не представляете, кто гостит нынче в Филипсбурге!";
			link.l1 = "Только не говори мне что...";
			link.l1.go = "Avendel_Marigo_2";
		break;
		
		case "Avendel_Marigo_2":
			dialog.text = "Нет-нет, капитан, это не Португалец, ха! И не ещё какой-нибудь подраненный негодяй. Всё гораздо удивительней! Это Эрнандо Васкез... Кровавый Дон собственной персоной! Он гостит у губернатора уже несколько дней.";
			link.l1 = "Васкез? У губернатора? Так, это кое-что проясняет. Хьюго, расскажи мне поподробнее – что, чёрт подери, тут происходит?";
			link.l1.go = "Avendel_Marigo_3";
		break;
		
		case "Avendel_Marigo_3":
			pchar.questTemp.Portugal.AvMoney = 10000;
			dialog.text = "Ну, знаю я много... но, благодаря нашей с вами поездке, я опять на мели. Возможно, ваша нужда в информации будет стоить несколько песо?";
			link.l1 = "Хьюго, ты вымогатель и прохвост, ни капельки не изменился! Выкладывай, что у тебя там – даю 5 000 песо, и то, только по старой дружбе.";
			link.l1.go = "Avendel_Marigo_4_1";
			if (sti(pchar.money) >= 10000)
			{
			link.l2 = "Отчего-то я не удивлён. Вот, держи 10 000 песо, и лучше бы твоей информации стоить этих денег!";
			link.l2.go = "Avendel_Marigo_4_2";
			}
			link.l3 = "У меня есть предложение получше. Как насчёт места в моей команде? Мне кажется, у тебя талант к цифирям, так что если надоело строить из себя бравого вояку -  мне бы пригодился толковый каптенармус.";
			link.l3.go = "Avendel_Marigo_4_3";
		break;
		
		case "Avendel_Marigo_4_1":
			pchar.questTemp.Portugal.AvMoney = 15000;
			dialog.text = "Нет, капитан, так не пойдёт! Вы ведь наверняка, сорвали куш с этим треклятым Португальцем – так что считайте это моей долей в деле, и не скупитесь. 15 000 и не грошом меньше!";
			if (sti(pchar.money) >= 15000)
			{
			link.l1 = "Чёрт с тобой, держи!";
			link.l1.go = "Avendel_Marigo_4_2";
			}
			link.l2 = "Да уж, а ещё говорят, что жадность - не порок. Не слишком ли жирно тебе будет, а?";
			link.l2.go = "Avendel_Marigo_wait";
		break;
		
		case "Avendel_Marigo_4_2":
			AddMoneyToCharacter(pchar, -sti(pchar.questTemp.Portugal.AvMoney));
			dialog.text = "Вот это цена по мне, капитан! Слушайте: Васкез плыл со мной на одном судне сюда, в Филипсбург, только мне пришлось драить палубу за проезд, а он прохлаждался в пассажирской каюте, так что слава Богу, мы виделись лишь мельком, и он меня не узнал. Зато я его сразу приметил, и, когда мы прибыли, стал приглядывать за этим дьяволом... Весьма любопытная вышла с ним история.";
			link.l1 = "Давай, не тяни! Что он делает у губернатора?";
			link.l1.go = "Avendel_Marigo_5";
		break;
		
		case "Avendel_Marigo_5":
			dialog.text = "Понятия не имею, но, после его прибытия весь гарнизон стоял на ушах пару дней, а потом большое военное судно, стоявшее в гавани, вдруг снялось с якоря и отбыло в крайней спешке – весь город терялся в догадках и слухах...";
			link.l1 = "Так вот кто меня встретил! Занятно... Не отвлекайся, Хьюго, рассказывай дальше.";
			link.l1.go = "Avendel_Marigo_6";
		break;
		
		case "Avendel_Marigo_6":
			dialog.text = "Ну, так вот, я и говорю – ушёл корабль, а Васкез с той поры вроде как гость при особе Мартина Томаса – губернатора нашего, стало быть. Время от времени вижу его в городе – всегда в обществе пары-тройки солдат. И не поймёшь – то ли почётный экскорт, то ли конвой, хе-хе. Но это сказать вам только в резиденции смогут, если захотят, конечно.";
			if (CheckAttribute(pchar, "questTemp.Portugal.AvOfficer"))
			{
				link.l1 = "Возможно ты прав. Но, мы договорились – помнишь? Никакого геройства, так что отправляйся на судно и жди моего возвращения. Попробую разговорить нашего гостеприимного губернатора.";
				link.l1.go = "Avendel_hire";
			}
			else
			{
				link.l1 = "Что ж, занятно. Ты мне действительно помог, Хьюго. Пей свой ром, остальное тебя уже не касается.";
				link.l1.go = "Avendel_Marigo_del";
			}
			AddDialogExitQuestFunction("InMarigoResidence");
		break;
		
		case "Avendel_Marigo_4_3":
			dialog.text = "Вот так дела, капитан! Что это с вами? То прогоняете чуть не в рыло пистолетом тыча, а теперь вот такие предложения?";
			if (sti(pchar.money) >= 10000)
			{
			link.l1 = "Забудь, я наверное оговорился. Вот, возьми 10 000 песо, и выкладывай всё, что знаешь про Васкеза, я спешу.";
			link.l1.go = "Avendel_Marigo_4_2";
			}
			link.l2 = "Возможно, мне стоит извиниться за тот случай. Боец из тебя, видно, никудышный, но со счётом всё в порядке. Я повторяю своё предложение, что скажешь?";
			link.l2.go = "Avendel_Marigo_7"
		break;
		
		case "Avendel_Marigo_7":
			pchar.questTemp.Portugal.AvMoney = 20000;
			pchar.questTemp.Portugal.AvOfficer = "true";
			dialog.text = "Что тут сказать... соглашусь, но, не раньше, чем получу свою долю, капитан. Помните – мы расстались на десятой части? Вы ведь выручили две тысячи золотых дублонов за шкуру этого пройдохи – так что если зовёте меня в команду, начните с выплаты долгов. Десятую часть и без обмана!";
			link.l1 = "Ты настоящий аферист, Хьюго. Сейчас у меня нет нужной суммы, я вернусь позже. Никуда не уходи.";
			link.l1.go = "Avendel_Marigo_wait";
			if (sti(pchar.money) >= 20000)
			{
			link.l2 = "Надеюсь, ты оправдаешь мои ожидания, с такой-то хваткой, ха! Держи свою долю!";
			link.l2.go = "Avendel_Marigo_4_2";
			}
		break;
		
		case "Avendel_Marigo_wait":
			dialog.text = "Ну, как знаете, капитан. Я буду здесь и пока никуда не ухожу. Надумаете - возвращайтесь.";
			link.l1 = "Хорошо, Хьюго.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Avendel_Marigo_repeat";
		break;
		
		case "Avendel_Marigo_repeat":
			dialog.text = "Не передумали, капитан? Тогда я жду свои деньги.";
			if (sti(pchar.money) >= sti(pchar.questTemp.Portugal.AvMoney))
			{
				link.l1 = "Держи свои монеты, пройдоха!";
				link.l1.go = "Avendel_Marigo_4_2";
			}
			link.l2 = "Нет у меня пока такой суммы.";
			link.l2.go = "exit";
			NextDiag.TempNode = "Avendel_Marigo_repeat";
		break;
		
		case "Avendel_Marigo_del":
			DialogExit();
			npchar.lifeday = 0;
			LAi_CharacterDisableDialog(npchar);
		break;
		
		case "Avendel_hire":
			DialogExit();
			LAi_SetImmortal(npchar, false); // patch-8
			SetCharacterRemovable(npchar, true);
			npchar.quest.OfficerPrice = sti(pchar.rank)*1000;
			Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(npchar.id);
			npchar.loyality = 25;
			npchar.dialog.FileName = "Enc_Officer_dialog.c";
			AddDialogExitQuestFunction("LandEnc_OfficerHired");
			NextDiag.CurrentNode = NextDiag.TempNode;
		break;
		
		case "Servant":
			pchar.quest.InMarigoResidenceOver.over = "yes"; //снять таймер
			dialog.text = "Здравствуйте, капитан, вы что-то хотели?";
			link.l1 = "Нет-нет, я просто жду, пока освободится минхер Томас. Жду аудиенции... да. Скажи, неужели правда, что его превосходительство привечает известного корсара Эрнандо Васкеза?";
			link.l1.go = "Servant_1";
		break;
		
		case "Servant_1":
			dialog.text = "Что вы, минхер! Этот негодяй сдался властям, но почему-то не был казнён. Возможно – ему удалось купить жизнь, сдав своих бывших подельников... не знаю. Он содержался тут под стражей несколько дней... это был ужас, минхер! Этот зверь в человеческом обличии прямо в особняке!";
			link.l1 = "Действительно ужасно! Что же он должен был разболтать, что помешало минхеру Томасу сразу отправить его на виселицу – представить не могу!";
			link.l1.go = "Servant_2";
		break;
		
		case "Servant_2":
			dialog.text = "Не знаю уж в чём там дело, но скажу вам по секрету – вся прислуга была счастлива, когда его светлость наконец избавился от такого гостя...";
			link.l1 = "Избавился? Он всё же попал на заслуженную плаху?";
			link.l1.go = "Servant_3";
		break;
		
		case "Servant_3":
			dialog.text = "Нет... пока что. Пару дней назад, ночью, его перевезли на военный бриг и отправили прямиком в Виллемстад. Знаете, что-то минхер Томас внезапно охладел к негодяю - не иначе, как обманул его этот мерзавец\nА ещё ходят слухи, что поймали его бывшего капитана – Бартоломео Португальца, только подумайте! Видимо, власти Компании хотят повесить их рядышком, в назидание прочим мерзавцам. Говорят, через месяц будет суд, только не знаю – к чему так тянуть?";
			link.l1 = "Португальца?! Кхм... спасибо, мой друг... кажется, минхер Томас уже освободился – мне надо идти.";
			link.l1.go = "Servant_4";
		break;
		
		case "Servant_4":
			DialogExit();
			npchar.lifeday = 0;
			LAi_CharacterDisableDialog(npchar);
			AddQuestRecord("Portugal", "31");
			pchar.questTemp.Portugal = "SeekPortVillemstad";
			SetFunctionTimerCondition("InMarigoResidenceOver", 0, 0, 30, false);
			colonies[FindColony("Villemstad")].jail = 0;
			sld = characterFromId("Portugal");
			sld.model = "Port_A"; //меняем модель
			sld.dialog.currentnode = "Portugal_free";
			LAi_SetStayType(sld);
			ChangeCharacterAddressGroup(sld, "Villemstad_prison", "goto", "goto9");
			sld = GetCharacter(NPC_GenerateCharacter("PortHolOfficer", "off_hol_4", "man", "man", 35, HOLLAND, 30, true, "soldier"));
			FantomMakeCoolFighter(sld, sti(pchar.rank)+MOD_SKILL_ENEMY_RATE+10, 100, 100, "blade_19", "pistol3", "grapeshot", 100);
			SetCharacterPerk(sld, "SwordplayProfessional");
			LAi_CharacterDisableDialog(sld);
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "HOLLAND_CITIZENS");
			ChangeCharacterAddressGroup(sld, "Villemstad_prison", "goto", "goto23");
			LAi_LocationDisableOfficersGen("Villemstad_prison", true);//офицеров не пускать
		break;
		
		case "Vaskez":
			dialog.text = "Теперь вам конец... обоим!";
			link.l1 = "...";
			link.l1.go = "Vaskez_1";
		break;
		
		case "Vaskez_1":
			DialogExit();
			LAi_ActorAnimation(npchar, "shot", "VaskezFight", 2.0);
		break;
		
		case "Portugal_free":
			if (LAi_group_GetTarget(pchar) <= 0)
			{
				dialog.text = "Вот уж кого я действительно не ожидал увидеть, капитан! Что-то не похоже на дружеский визит – кровь, шум, выстрелы, а?";
				link.l1 = "Не ёрничай, Португалец – мне просто не понравилось, как ты распорядился выкупленной у меня жизнью. Я слишком долго упорствовал ради её спасения, чтобы позволить тебе так бездарно попасться сразу после нашего расставания!";
				link.l1.go = "Portugal_free_1";
			}
			else
			{
				dialog.text = "Осторожнее, дружище! Эх, жаль, не могу помочь тебе!";
				link.l1 = "...";
				link.l1.go = "exit";
				NextDiag.TempNode = "Portugal_free";
			}
		break;
		
		case "Portugal_free_1":
			dialog.text = "Значит благородство бывает не только за деньги, да? Ха... осторожно, сзади!";
			link.l1 = "Проклятье!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("CreateErnandoVaskez");
			NextDiag.TempNode = "Portugal_free";
		break;
		
		case "Portugal_free_2":
			dialog.text = "А я предупреждал, что этот парень ещё доставит хлопот!";
			link.l1 = "Он чуть не пристрелил меня со спины! Как он выбрался?";
			link.l1.go = "Portugal_free_3";
		break;
		
		case "Portugal_free_3":
			dialog.text = "Я видел, он давненько припас отмычки – передал поди кто-то... у него всегда были связи в самом низу. Что же, капитан, теперь мы отчасти квиты...";
			link.l1 = "Да ну! Ладно, поспешим, пока сюда не сбежался весь гарнизон. Сейчас я сломаю твой замок...";
			link.l1.go = "Portugal_free_4";
		break;
		
		case "Portugal_free_4":
			DialogExit();
			InterfaceStates.Buttons.Save.enable = true;//разрешить сохраняться
			chrDisableReloadToLocation = false;
			DoQuestReloadToLocation("Villemstad_Exittown", "rld", "loc17", "PortugalFree");
		break;
		
		case "Portugal_free_5":
			dialog.text = "Знаете, капитан, свежий воздух... начинаешь его ценить после нескольких недель в подземелье, с тех пор, как на вашу шлюпку наткнулся местный сторожевой корабль. Полагаю, за мной всё же остался долг за спасение.";
			link.l1 = "Оставь это, Португалец. Я не благородный рыцарь, просто... поступаю так, как считаю нужным.";
			link.l1.go = "Portugal_free_6";
		break;
		
		case "Portugal_free_6":
			dialog.text = "Ха, и это отменное качество! Но, я всё же настаиваю – вот, возьмите... это единственное, что мне удалось утаить в тюрьме... Мой талисман. Он всегда приносил мне удачу в море. Вы отличный моряк, так что он вам точно пригодится.";
			link.l1 = "Хороша же его удача, если ты угодил прямёхонько в лапы голландцам?";
			link.l1.go = "Portugal_free_7";
		break;
		
		case "Portugal_free_7":
			dialog.text = "Эй! Я ведь жив, а? И, заметьте – больше не за решеткой... Берите, капитан, пусть он теперь послужит вам. И благодарю ещё раз!";
			link.l1 = "Ну, прощай, Португалец. И постарайся не окончить свои дни на виселице! Хотя бы из уважения к моим мытарствам, ха-ха!";
			link.l1.go = "Portugal_free_8";
		break;
		
		case "Portugal_free_8":
			TakeNItems(pchar, "talisman2", 1);
			Log_Info("Вы получили талисман");
			PlaySound("interface\important_item.wav");
			DialogExit();
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "", 10.0);
			npchar.lifeday = 0;
			LAi_LocationDisableOfficersGen("Villemstad_prison", false);//офицеров пускать
			AddQuestRecord("Portugal", "34");
			CloseQuestHeader("Portugal");
			pchar.questTemp.Portugal = "end";
			pchar.questTemp.Portugal.GG1 = "true"; // Jason Дороже золота
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}