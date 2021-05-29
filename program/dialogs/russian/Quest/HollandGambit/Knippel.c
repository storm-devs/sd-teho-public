// Чарли Книппель - старый артиллерист
void ProcessDialogEvent()
{
	ref NPChar, sld, rItm, rItem;
	aref Link, NextDiag, rType;
	int i, iTemp, amount;
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
		//ветка на взятие 2 варианта прохождения - за Англию
		if(CheckAttribute(pchar, "questTemp.HWIC.CanTake") && !CheckAttribute(pchar, "questTemp.HWIC.CanTake.Eng") && !CheckAttribute(npchar, "quest.HWICTake") && !CheckAttribute(pchar, "questTemp.HWIC.Holl") && !CheckAttribute(pchar, "questTemp.HWIC.Self"))
		{
			dialog.text = "Доброго дня, мистер, книппель мне в корму! Каким попутным ветром вас сюда занесло?";
			link.l1 = "Здравствуйте. Я без конкретного дела зашел, просто поприветствовать и поговорить...";
			link.l1.go = "exit";
			link.l2 = "Послушайте, Чарли, ходят слухи, что вы каким-то образом связаны с английским военным флотом. У меня отличный корабль и обученная команда. Я бы хотел предложить себя и свое судно для работы на благо Англии. Причем настоящей работы, достойной военного моряка. Не могли бы ли вы что-нибудь посоветовать, или кому-нибудь рекомендовать, или еще как-то помочь в этом вопросе?";
			link.l2.go = "Knippel_check";
			break;
		}
		//за Голландию
		if (CheckAttribute(pchar, "questTemp.HWIC.Holl"))
		{
			if (pchar.questTemp.HWIC.Holl == "toKnippel")
			{
				dialog.text = "Доброго дня, мистер, книппель мне в корму! Каким попутным ветром вас сюда занесло?";
				link.l1 = "Здравствуйте, Чарли. Я слышал, что вы связаны с военным английским флотом, вот и хотел к вам обратиться за помощью...";
				link.l1.go = "Dominica";
				break;
			}
			dialog.text = "Книппель мне в корму! Что вы хотели, мистер?";
			link.l1 = "Да нет, ничего. Я уже ухожу.";
			link.l1.go = "exit";
			break;
		}
		//за Англию
		if (CheckAttribute(pchar, "questTemp.HWIC.Eng"))
		{
			if (pchar.questTemp.HWIC.Eng == "TakeHollConvoy")
			{
				dialog.text = "Добрый день, капитан. До меня уже дошли слухи о перехвате серебряного конвоя...";
				link.l1 = "Я готов отчитаться о выполнении вашего задания, Чарли.";
				link.l1.go = "HollConvoy_Check";
				break;
			}
			if (pchar.questTemp.HWIC.Eng == "Start_main" && GetQuestPastDayParam("questTemp.HWIC.Eng_1") > 0)
			{
				dialog.text = "Рад вас видеть, капитан! Мой командир, Ричард Флитвуд, намеревался прийти сюда, чтобы познакомиться с вами, но вчера вечером приключилось такое несчастье... На Ричарда было совершено покушение, прямо на улицах города, книппель мне в корму!";
				link.l1 = "Невероятно! И куда только стража смотрит?";
				link.l1.go = "Fleetwood_house";
				break;
			}
			dialog.text = "У вас еще какие-то вопросы, капитан?";
			link.l1 = "Нет, ничего. Я уже ухожу.";
			link.l1.go = "exit";
		break;
		}
			dialog.text = "Доброго дня, мистер, книппель мне в корму! Каким попутным ветром вас сюда занесло?";
			link.l1 = "Здравствуйте. Я без конкретного дела зашел, просто поприветствовать и поговорить...";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;

//-------------------------------------------за Голландию--------------------------------------------------	
		case "Dominica":
			dialog.text = "Хех! И чем же может старый моряк, уже давно списанный на берег, помочь вам, мистер?";
			link.l1 = "Понимаете... я обычный капитан, и делаю регулярные рейсы с товаром между Мартиникой и Кюрасао. Так вот, у берегов Мартиники я уже дважды подвергся нападению жуткого корабля-призрака... Хотя, какой он призрак, если его паруса ядрами рвутся!";
			link.l1.go = "Dominica_1";			
		break;
		
		case "Dominica_1":
			dialog.text = "Вот как? Это очень интересно, книппель мне в рею...";
			link.l1 = "Меня спасло только то, что мое судно способно развивать приличную скорость в бейдевинд. В последний раз, чтобы убежать, мне пришлось выбросить за борт весь товар... вы представляете, какие это убытки?";
			link.l1.go = "Dominica_2";			
		break;
		
		case "Dominica_2":
			dialog.text = "Сочувствую, кэп...";
			link.l1 = "Губернатор Кюрасао - Матиас Бек - только отмахнулся от моих жалоб на пирата. Сказал, что всё это выдумки. Губернатор Мартиники пообещал выслать патруль, но по выражению его лица я сразу понял, что никакого патруля он посылать не собирается. А мне теперь закрыт путь на Мартинику, пока там орудует этот мерзавец - корабль у меня маленький, сопротивляться ему я не могу, и в третий раз можно и не уйти...";
			link.l1.go = "Dominica_3";			
		break;
		
		case "Dominica_3":
			dialog.text = "Мне жаль, мистер. Но чем же я могу вам помочь?";
			link.l1 = "От матросов в таверне я слышал, что один военный моряк Сент-Джонса, некто сэр Флитвуд, ведет охоту на корабль этого подлеца. Я не знаю его, поэтому и обратился к вам - может, вы бы передали ему мой рассказ? Я уверен, что гнусный пират скрывается где-то у диких берегов Доминики и рейдирует пространство между Барбадосом и Мартиникой.";
			link.l1.go = "Dominica_4";			
		break;
		
		case "Dominica_4":
			dialog.text = "Между Барбадосом и Мартиникой? Действительно, весьма похоже на этого ублюдка...";
			link.l1 = "Я небогат, и мне нечем будет заплатить военным за избавление тамошних вод от негодяя. Но раз сэр Флитвуд разыскивает этот корабль - то по крайней мере, передайте ему, где искать этого 'Летучего Голландца'.";
			link.l1.go = "Dominica_5";			
		break;
		
		case "Dominica_5":
			dialog.text = "Вы хорошо сделали, мистер, что пришли ко мне. Я сообщу обо всем услышанном куда следует, книппель мне в печень! Скоро вы снова сможете торговать с Мартиникой.";
			link.l1 = "Ваши бы слова да Богу в уши! Спасибо, что выслушали меня, Чарли. Надеюсь на лучшее. До свидания!";
			link.l1.go = "Dominica_6";			
		break;
		
		case "Dominica_6":
			DialogExit();	
			pchar.questTemp.HWIC.Holl = "toDominica";
			AddQuestRecord("Holl_Gambit", "1-17");
			pchar.quest.toDominica.win_condition.l1 = "location";
			pchar.quest.toDominica.win_condition.l1.location = "Dominica";
			pchar.quest.toDominica.function = "PrepareToFleetwoodAttack";
		break;

//----------------------------------------------за Англию--------------------------------------------------	
		case "Knippel_check"://начинаем проверять нашего ГГ по всем статьям
			if(makeint(PChar.reputation.nobility) < 41)//низкая репа
			{
				PlaySound("VOICE\Russian\hambit\Charlie Knippel-04.wav");
				dialog.text = "Англия не нуждается в услугах проходимцев, книппель мне в корму! Я ничего не могу вам посоветовать.";
				link.l1 = "Эй-эй, полегче, приятель, с выражениями!";
				link.l1.go = "exit";
				break;
			}
			if(GetSummonSkillFromName(pchar, SKILL_SAILING) < 30)//низкая навигация
			{
				dialog.text = "Капитан, нашему флоту нужны более опытные капитаны. Приходите, когда лучше овладеете искусством кораблевождения.";
				link.l1 = "Понятно... Тогда я загляну к вам попозже.";
				link.l1.go = "exit";
				break;
			}
			if(sti(Pchar.rank) > 15)//высокий ранг
			{
				PlaySound("VOICE\Russian\hambit\Charlie Knippel-03.wav");
				dialog.text = "Вы слишком известны на архипелаге, кэп. Не думаю, что вам будут интересны мои задания, да и мне поручить вам нечего.";
				link.l1 = "Ладно, раз неинтересны - значит, неинтересны. Прощайте.";
				link.l1.go = "exit";
				break;
			}
			dialog.text = "Хм... Вы очень вовремя обратились, капитан, книппель мне в корму! А то Ричард даже и не знал, кому поручить это дело, думал, что придется отказаться... Попробую озадачить данным вопросом вас. Если хорошо себя покажете - я порекомендую вас одному очень хорошему человеку. Теперь слушайте, что надо сделать.";
			link.l1 = "Я весь внимание.";
			link.l1.go = "Knippel_task";
		break;
		
		case "Knippel_task"://первое задание
			dialog.text = "День или два назад, из Виллемстада, что на Кюрасао, в Филипсбург, должен был выйти караван Голландской Вест-Индской торговой Компании, перевозящий большую партию серебра. В караване несколько кораблей - ост-индец с интересующим нас грузом, и один или два - корабли охранения. Перехватите этот караван, захватите ост-индец с грузом серебра и приведите на Антигуа. Эскорт можете утопить, книппель ему в печенку!";
			link.l1 = "Хорошо. Незамедлительно отправляюсь на розыск каравана!";
			link.l1.go = "Knippel_task_1";			
		break;
		
		case "Knippel_task_1":
			dialog.text = "Позволю себе несколько советов, капитан: путь от Кюрасао на Синт-Маартен лежит мимо берегов острова Сент-Кристофер. Я бы организовал засаду именно там. Также хорошо подготовьтесь к встрече - это не торговый, а самый настоящий военный караван... Желаю удачи!";
			link.l1 = "Спасибо! Судя по вашим словам, она мне понадобится. До встречи!";
			link.l1.go = "Knippel_task_2";			
		break;
		
		case "Knippel_task_2":
			DialogExit();
			npchar.quest.HWICTake = "true";
			pchar.questTemp.HWIC.CanTake.Eng = "true";//признак, что английка уже бралась
			HWICSilverConvoyInWorld();
			AddQuestRecord("Holl_Gambit", "2-1");
			pchar.questTemp.HWIC.Eng = "begin";
			SetFunctionTimerCondition("HollConvoy_Over", 0, 0, 15, false);
		break;
		
		case "HollConvoy_Check"://начинаем проверять
			int iHal = 0;
			for(i = 0; i < COMPANION_MAX; i++)
			{
				iTemp = GetCompanionIndex(PChar, i);
				if(iTemp > 0)
				{
					sld = GetCharacter(iTemp);
					pchar.questTemp.HWIC.Eng.CompanionIndex = sld.Index;
					if(sti(RealShips[sti(sld.ship.type)].basetype) == SHIP_EASTINDIAMAN) iHal++;
				}
			}//признак наличия ТГ в компаньонах
			if (iHal > 0)
			{
				amount = sti(pchar.questTemp.HWIC.Eng.SlvQty) - GetSquadronGoods(pchar, GOOD_SILVER);
				if (amount <= 0)
				{
					dialog.text = "Ну, отчета не нужно - после досмотра вашего судна в порту мне всё уже рассказали... Вы отлично справились с поручением, капитан. Великолепно! Это было непростое дело, книппель мне в корму!";
					link.l1 = "Спасибо! Приятно слышать лестную оценку своих действий.";
					link.l1.go = "HollConvoy_complete";
				}
				else
				{
					dialog.text = "Ну, отчета не нужно - после досмотра вашего судна в порту мне всё уже рассказали... Капитан, вы привезли не весь груз, книппель мне в корму! Я достоверно знал, сколько серебра должно было быть на этом галеоне. Это задание было не только проверкой ваших боевых качеств, но и вашей честности. Испытания на жадность вы не прошли. Я не желаю иметь с вами дел - покиньте мой дом!";
					link.l1 = "Ну и черт с тобой, чистоплюй!";
					link.l1.go = "HollConvoy_fail";
				}
			}
			else
			{
				dialog.text = "Что-то я не вижу у вас в эскадре голландского ост-индца. Я ведь говорил вам, что его надо обязательно привести призом. Вы его продали?";
				link.l1 = "Гм... вы разве говорили привести корабль? Кажется, речь шла только о серебре.";
				link.l1.go = "HollConvoy_noShip";
			}
		break;
		
		case "HollConvoy_noShip":
			dialog.text = "Не звените книппелями, мистер! Я прекрасно помню, что я говорю, а чего - нет. Вы нарушили условия нашего договора, и я более не желаю иметь с вами дел - проходимцам здесь не место. Покиньте мой дом немедленно!";
			link.l1 = "Ну и черт с тобой!";
			link.l1.go = "HollConvoy_fail";
		break;
		
		case "HollConvoy_fail":
			DialogExit();
			AddQuestRecord("Holl_Gambit", "2-3");
			CloseQuestHeader("Holl_Gambit");
			DeleteAttribute(pchar, "questTemp.HWIC.Eng");//зачищаем для возможности отката к голландскому варианту
			pchar.questTemp.HWIC.Fail2 = "true";
		break;
		
		case "HollConvoy_complete":
			dialog.text = "Зайдите ко мне завтра - я познакомлю вас с моим патроном. Думаю, он сможет предложить работу, достойную вас. А за выполненное задание предусмотрена награда - вы ее завтра же и получите от моего командира. До встречи!";
			link.l1 = "Хорошо, Чарли. Я приду к вам завтра.";
			link.l1.go = "exit";
			npchar.greeting = "knippel_2";
			AddDialogExitQuestFunction("HollConvoy_Remove");
			pchar.questTemp.HWIC.Eng = "Start_main";
			SaveCurrentQuestDateParam("questTemp.HWIC.Eng_1");
			AddQuestRecord("Holl_Gambit", "2-4");
			AddSimpleRumourCity("Говорят, что вы захватили голландский корабль, полный серебра. Лихо! Вы отчаянный и бравый моряк, капитан!", "SentJons", 10, 3, "");
		break;
		
		case "Fleetwood_house":
			dialog.text = "Вот и я задаю себе этот же вопрос... Какой-то негодяй подло бросил патрону в глаза молотый кайенский перец, и прежде чем Ричард успел обнажить клинок, нанес ему удар в грудь. Убийца рассчитывал покончить с Ричардом одним ударом, так как на второй уже не было бы времени, но просчитался: командир всегда носит под мундиром пурпан, и он спас его\nГнусный мерзавец, книппель ему в печень, скрылся без следа, словно растворился - очевидно, в городе у него есть сообщники. Единственное, что удалось запомнить очевидцам - что он был одноглазый. Но разве это примета? Таких циклопов в каждом порту по десятку разгуливает\nРичард потерял много крови, кроме того, не успел сразу промыть глаза, и теперь почти ничего не видит...";
			link.l1 = "М-да, сочувствую вашему командиру. Нападавшего объявили в розыск?";
			link.l1.go = "Fleetwood_house_1";
		break;
		
		case "Fleetwood_house_1":
			dialog.text = "Морпехи Ричарда обыскали весь город и окрестные бухты, но никого не нашли, книппель им в рею! Если не удалось найти по горячим следам, то теперь уже и подавно не найдем. У Ричарда недругов много... Но, капитан, несмотря на произошедшее, патрон желает вас видеть. Он у себя дома, так что отправляемся к нему. Следуйте за мной!";
			link.l1 = "Хорошо, Чарли. Ведите!";
			link.l1.go = "Fleetwood_house_2";
		break;
		
		case "Fleetwood_house_2":
			chrDisableReloadToLocation = true;//закрыть локацию
			bDisableFastReload = true;//закроем быстрый переход
			LocatorReloadEnterDisable("SentJons_town", "reload1_back", true);
			LocatorReloadEnterDisable("SentJons_town", "reload2_back", true);
			LocatorReloadEnterDisable("SentJons_town", "gate_back", true);//чтобы не сбежал
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "SentJons_town", "reload", "houseH1", "OpenTheDoors", -1);
			pchar.quest.Knippel_Outside.win_condition.l1 = "location";
			pchar.quest.Knippel_Outside.win_condition.l1.location = "SentJons_town";
			pchar.quest.Knippel_Outside.function = "Knippel_GoTown";
			LocatorReloadEnterDisable("SentJons_town", "houseSP3", true);
			sld = characterFromId("Fleetwood");
			LAi_SetStayType(sld);
			ChangeCharacterAddressGroup(sld, "SentJons_houseSP3_room", "goto", "goto1");
			pchar.GenQuestBox.SentJons_houseSP3_room = true;
			pchar.GenQuestBox.SentJons_houseSP3_room.box1.money = 110000;
		break;
		
		case "InFleetwoodHouse":
			dialog.text = "Ричард у себя в комнате, наверху. Поднимайтесь к нему, он вас ждет, а я побуду здесь.";
			link.l1 = "Я понял, Чарли. Уже иду.";
			link.l1.go = "exit";	
		break;
		
		case "Knippel_ToOfficer":
			dialog.text = "Капитан, тут такое дело... Ричард под хорошим присмотром и в безопасности. А я хочу помочь вам отомстить за его ранение. Я предлагаю вам свои услуги в качестве офицера. Махать шашкой я не горазд - годы, понимаете ли, но наводить орудия еще не разучился.";
			link.l1 = "Добро пожаловать в команду, Чарли!";
			link.l1.go = "Knippel_ToOfficer_1";	
		break;
		
		case "Knippel_ToOfficer_1":
			LocatorReloadEnterDisable("SentJons_town", "reload1_back", false);
			LocatorReloadEnterDisable("SentJons_town", "reload2_back", false);
			LocatorReloadEnterDisable("SentJons_town", "gate_back", false);//откроем локаторы
			//Книппеля - в офицеры
			npchar.quest.OfficerPrice = sti(pchar.rank)*500;
			Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(npchar.id);
			npchar.OfficerWantToGo.DontGo = true; //не пытаться уйти
			npchar.HalfImmortal = true;//полубессмертен
			npchar.loyality = 20;
			AddDialogExitQuestFunction("LandEnc_OfficerHired");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			SetFunctionTimerCondition("GotoBridgetownOver", 0, 0, 30, false);//на все дела - 1 месяц
			AddSimpleRumourCity("Говорят, капитан, вами заинтересовался сам Ричард Флитвуд. Он очень значительная личность в нашем городе, скажу я вам...", "SentJons", 10, 3, "");
		break;
		
		case "hired":
			dialog.text = "Вы что-то хотели, капитан?";
			link.l1 = "Да нет, ничего.";
			link.l1.go = "exit";
			NextDiag.TempNode = "hired";
		break;
		
		case "MC_GoAway":
			PlaySound("VOICE\Russian\hambit\Charlie Knippel-07.wav");
			if (pchar.questTemp.HWIC.Eng == "MirageFail")
			{
				dialog.text = "Вы полный олух и тупица, капитан, книппель мне в корму! Нужно было выполнить элементарную задачу - захватить 'Мираж', не потеряв при этом 'Валькирию', но вы с этим не справились\nНаша команда не желает больше вам ни подчиняться, ни вообще видеть вас. Мы уверены - сэр Флитвуд одобрит наше решение, ибо он не терпит неумех.";
				link.l1 = "Да и черт с тобой и твоим хозяином!";
				link.l1.go = "exit";
			}
			if (pchar.questTemp.HWIC.Eng == "GotoBridgetown" || pchar.questTemp.HWIC.Eng == "SeekVanBerg")
			{
				dialog.text = "Капитан, вы полный олух, книппель мне в корму! Мы уже неведомо сколько времени занимаемся решением ваших личных проблем, вместо того, чтобы идти на встречу\nНаша команда не желает больше вам ни подчиняться, ни вообще видеть вас. Мы уверены - сэр Флитвуд одобрит наше решение.";
				link.l1 = "Да и черт с тобой и твоим хозяином!";
				link.l1.go = "exit";
			}
			if (pchar.questTemp.HWIC.Eng == "VanBergFailInWorld")
			{
				dialog.text = "Капитан, вы полный олух, книппель мне в корму! Вам же ясно было сказано - нужно сыграть роль купца на 'Валькирии', а вы здесь что устроили? Вы спугнули пирата своими кораблями! Надо было идти в одиночку, и только на 'Валькирии'! Он теперь в жизни на эту уловку не попадется\nНаша команда не желает больше вам ни подчиняться, ни вообще видеть вас. Мы уверены - сэр Флитвуд одобрит наше решение.";
				link.l1 = "Да и черт с тобой и твоим хозяином!";
				link.l1.go = "exit";
			}
			if (pchar.questTemp.HWIC.Eng == "MirageTake")
			{
				dialog.text = "Капитан, вы что же, книппель мне в корму, решили, что мы теперь должны без конца мотаться по вашим личным делам? Вам же ясно было сказано - захватить 'Мираж' и направляться назад на Антигуа! Сколько можно бороздить море без цели?\nНаша команда не желает больше вам ни подчиняться, ни вообще видеть вас. Мы уверены - сэр Флитвуд одобрит наше решение.";
			link.l1 = "Да и черт с тобой и твоим хозяином!";
			link.l1.go = "exit";
			}
			PChar.quest.Munity = "Deads";
			LAi_LocationFightDisable(&Locations[FindLocation("Ship_deck")], false);
			if(sti(RealShips[sti(pchar.ship.type)].basetype) == SHIP_VALCIRIA)//если сам на Валькирии
			{
				pchar.Ship.Type = GenerateShipExt(SHIP_TARTANE, true, pchar);
				pchar.Ship.name = "Лодка";
				SetBaseShipData(pchar);
				SetCrewQuantityOverMax(PChar, 0);
			}
			else
			{
				for(i = 1; i < COMPANION_MAX; i++)
				{
					iTemp = GetCompanionIndex(PChar, i);
					if(iTemp > 0)
					{
						sld = GetCharacter(iTemp);
						if(sti(RealShips[sti(sld.ship.type)].basetype) == SHIP_VALCIRIA)
						{
							pchar.questTemp.HWIC.Eng.CompanionIndex = sld.Index;
							sld = GetCharacter(sti(pchar.questTemp.HWIC.Eng.CompanionIndex));
							RemoveCharacterCompanion(PChar, sld);
							AddPassenger(PChar, sld, false);
						}
					}
				}
			}
			LAi_CharacterDisableDialog(npchar);
			LAi_SetImmortal(npchar, true);
			ChangeCharacterAddressGroup(npchar, "SentJons_houseH1", "goto", "goto1");//Книппеля домой
			pchar.questTemp.HWIC.Eng = "end";
			pchar.questTemp.HWIC.Detector = "eng_fail";
			CloseQuestHeader("Holl_Gambit");
		break;
		
		case "OnCuracao":
			pchar.quest.HWICEng_toBarbadosOver.over = "yes";//снять прерывание
			dialog.text = "Здравствуйте, капитан. Рад вас видеть!";
			link.l1 = "Приветствую, Чарли. Деньги у тебя? Давай их мне, и нам нужно выдвигаться в Виллемстад за Абигайль. Ты пойдешь со мной?";
			link.l1.go = "OnCuracao_1";	
		break;
		
		case "OnCuracao_1":
			dialog.text = "Капитан, тут такое дело... Уже никуда выдвигаться не нужно.";
			link.l1 = "Ты это о чем? Что за вздор?!";
			link.l1.go = "OnCuracao_2";	
		break;
		
		case "OnCuracao_2":
			dialog.text = "У меня для вас письмо от Ричарда. И деньги. Но деньги предназначены не для отца Абигайль, а для вас лично. Двести тысяч песо. Прочтите письмо и постарайтесь не судить строго...";
			link.l1 = "Да что же это за чертовщина такая в последнее время творится? Опять неприятный сюрприз? Давай сюда свое письмо!";
			link.l1.go = "OnCuracao_3";	
		break;
		
		case "OnCuracao_3":
			DialogExit();
			NextDiag.CurrentNode = "OnCuracao_4";
			AddMoneyToCharacter(pchar, 200000);
			LAi_SetCitizenType(npchar);
			npchar.lifeday = 1;//еще денек пусть погуляет по пляжу
			pchar.quest.Holland_ShoreAttack.win_condition.l1 = "location";
			pchar.quest.Holland_ShoreAttack.win_condition.l1.location = "Curacao";
			pchar.quest.Holland_ShoreAttack.function = "CreateHollandShorePatrol";//патруль в прибрежных водах
			LocatorReloadEnterDisable("SentJons_town", "basement1_back", false);//открыть подземелье
			pchar.questTemp.HWIC.Eng = "MerdokMeeteng";
			AddQuestRecordInfo("LetterFromFleetwood", "1");
			AddQuestRecord("Holl_Gambit", "2-23");
		break;
		
		case "OnCuracao_4":
			dialog.text = "Прочли, капитан? Мне очень стыдно за Ричарда и за его поступок, книппель ему в... ах, ладно. Роденбург пришел в ярость, когда узнал, с кем сбежала Абигайль. На Кюрасао усилены патрули, в море крейсируют военные корабли. Вы не встретили их? Нам надо убираться отсюда, и побыстрее\nИ, капитан: вам не нужен толковый канонир? Мне много не надо: кусок сухаря, ломоть солонины и кружка воды - что еще нужно старому артиллеристу?";
			link.l1 = "Я согласен, Чарли. Добро пожаловать в команду!";
			link.l1.go = "Knippel_hire";
			link.l2 = "Знаешь, я уже пожалел, что помог твоему патрону. Теперь не знаю, как и выпутываться. Ступай своей дорогой, хватит с меня сюрпризов.";
			link.l2.go = "Knippel_exit";
		break;
		
		case "Knippel_hire":
			DialogExit();
			DeleteAttribute(npchar, "LifeDay");
			npchar.quest.OfficerPrice = sti(pchar.rank)*200;
			npchar.OfficerWantToGo.DontGo = true;
			DeleteAttribute(npchar, "CompanionDisable");//теперь можем и в компаньоны
			DeleteAttribute(npchar, "HalfImmortal");
			npchar.loyality = MAX_LOYALITY;
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, true);
			npchar.Payment = true;
			LAi_SetImmortal(npchar, false);
			LAi_SetHP(npchar, 120, 120);
			LAi_SetOfficerType(npchar);
			npchar.greeting = "knippel_hire";
			NextDiag.CurrentNode = "Knippel_officer";
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			SaveCurrentNpcQuestDateParam(npchar, "HiredDate");
		break;
		
		case "Knippel_exit":
			DialogExit();
			npchar.lifeday = 0;
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload2", "none", "", "", "", -1);
		break;
		
//------------------------------------------------против всех-----------------------------------------------
		case "Knippel_abordage":
			dialog.text = "Гнусный негодяй! Зачем ты напал на мирное голландское судно? У меня в трюмах нет ни ценных товаров, ни золота, книппель мне в корму!";
			link.l1 = "Голландское? Ха-ха! Не смеши меня, 'голландец'. Я захватил твою бригантину, чтобы взять тебя в плен, дорогой Чарли. Добро пожаловать в трюм. Побеседуем, куда ты шел, и зачем...";
			link.l1.go = "Knippel_abordage_1";	
		break;
		
		case "Knippel_abordage_1":
			AddQuestRecord("Holl_Gambit", "3-20");
            pchar.quest.Knippel_DieHard.over = "yes";
		    DoQuestCheckDelay("LAi_ReloadBoarding", 1.0);
            DialogExit();
			LAi_SetPlayerType(pchar);
			pchar.questTemp.HWIC.Self = "KnippelPrisoner";
			npchar.lifeday = 0;
			SetFunctionTimerCondition("RemoveKnippelOver", 0, 0, 1, false);//таймер до конца суток, ибо нефиг
		break;
		
		case "Knippel_prisoner":
			PlaySound("VOICE\Russian\hambit\Charlie Knippel-07.wav");
			dialog.text = "Вы сущий дьявол, капитан... Гореть вам в аду за все ваши деяния! Будь вы...";
			link.l1 = "Уймись, проповедник. Сейчас тебе самое время о душе подумать, а не морали читать.";
			link.l1.go = "Knippel_prisoner_1";
		break;
		
		case "Knippel_prisoner_1":
			dialog.text = "Что вы задумали, негодяй? Что вам надо от моего патрона и от несчастной голландской девушки?";
			link.l1 = "Это уже не твое дело, Чарли. Ты мне больше не нужен. Встань.";
			link.l1.go = "Knippel_prisoner_2";	
		break;
		
		case "Knippel_prisoner_2":
			dialog.text = "Вы решили меня убить? Ну что же... достойно такого мерзавца, как вы.";
			link.l1 = "Встань, Чарли. И повернись ко мне спиной.";
			link.l1.go = "Knippel_prisoner_3";	
		break;
		
		case "Knippel_prisoner_3":
			DialogExit();
			LAi_SetActorType(pchar);
			sld = characterFromId("KnippelClone");
			LAi_SetActorType(sld);
			LAi_ActorAnimation(sld, "Ground_StandUp", "Kill_Knippel", 3.5);
			pchar.quest.RemoveKnippelOver.over = "yes";//снять таймер
		break;
		
		//--> ----------------------------------- офицерский блок ------------------------------------------
		case "Knippel_officer":
			dialog.text = "Внимательно слушаю вас, капитан, книппель мне в грот!";
			if (CheckAttribute(pchar, "questTemp.Dolly_Tieyasal") && !CheckAttribute(npchar, "quest.Tieyasal"))
			{
				Link.l4 = "Чарли, я собираюсь отправиться в старый индейский город Тайясаль. Не буду скрывать: это крайне опасное путешествие, и более того - необычное: через телепортационный истукан. Ты... пойдешь со мной?";
				Link.l4.go = "tieyasal";
			}
			Link.l1 = "Слушай мой приказ!";
            Link.l1.go = "stay_follow";
			link.l2 = "Пока ничего. Вольно!";
			link.l2.go = "exit";
			NextDiag.TempNode = "Knippel_officer";
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
	
	// на Тайясаль
		case "tieyasal":
			dialog.text = "Я чертовски привязался к вам за время слубы, "+pchar.name+", да и не в моих правилах бросать своего капитана. Я с вами!";
			link.l1 = "Спасибо, Чарли! Я рад, что не ошибся в тебе.";
			link.l1.go = "tieyasal_1";
		break;
		
		case "tieyasal_1":
			dialog.text = "Когда состоится поход?";
			link.l1 = "Немного позже. А пока мы подготовимся к нему.";
			link.l1.go = "tieyasal_2";
		break;
		
		case "tieyasal_2":
			DialogExit();
			AddQuestRecord("Tieyasal", "22");
			npchar.quest.Tieyasal = "teleport";
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		//--> блок реагирования на попытку залезть в сундук
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("Да ты "+ GetSexPhrase("вор, милейший! Стража, держи его","воровка! Стража, держи ее") +"!!!", "Вот это да! Чуть я загляделся, а ты сразу в сундук с головой! Держи "+ GetSexPhrase("вора","воровку") +"!!!", "Стража! Грабят!!! Держи "+ GetSexPhrase("вора","воровку") +"!!!");
			link.l1 = "А-ать, дьявол!!!";
			link.l1.go = "exit";
			LAi_group_Attack(NPChar, Pchar);
		break;
		//<-- блок реагирования на попытку залезть в сундук
	}
}