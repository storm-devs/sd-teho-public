// диалог прочих и малозначимых НПС
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	bool bOk;
	int i, n, iTemp;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "Вы что-то хотели?";
			link.l1 = "Да нет, ничего.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		// --> матрос на корабле, прибытие в Сен-Пьер
		case "Startsailor":
			dialog.text = "Эх, первым делом, как сойду на берег - напьюсь!.. Просыпайтесь, месье... как вас там... Прибыли!";
			link.l1 = "А-ах! Что, уже? Чертова жара...";
			link.l1.go = "Startsailor_1";			
		break;
		
		case "Startsailor_1":
			dialog.text = "Привыкайте, месье, тут другой погоды и не бывает... Разве что хуже.";
			link.l1 = "Куда уж хуже! Под одной полотняной рубашкой пот катится градом!";
			link.l1.go = "Startsailor_2";			
		break;
		
		case "Startsailor_2":
			dialog.text = "Не забудьте свои вещи... Поторопитесь, месье, шлюпка ждать не станет. Вы же не хотите добираться до берега вплавь?";
			link.l1 = "Да, я уже готов... Где моя шпага? Ах, вот...";
			link.l1.go = "Startsailor_3";			
		break;
		
		case "Startsailor_3":
			dialog.text = "Да, тут вам не Европа... Будьте осторожны, месье. Здесь в последнее время не любят тех, кто задает слишком много вопросов. Времена нынче, знаете ли, неспокойные. Говорят, что остров продали каким-то фанатикам веры. Я до сих пор не замечал каких-то перемен в привычном укладе жителей Мартиники. Но за время моего отсутствия многое могло измениться.";
			link.l1 = "Фанатики веры? Что за вздор!";
			link.l1.go = "Startsailor_4";			
		break;
		
		case "Startsailor_4":
			dialog.text = "Вздор, или не вздор, а слухи ходят. Да и без этого напастей хватает. Людоеды в джунглях, лихорадка, пираты в море, бандиты в переулках...";
			link.l1 = "Ну, началось... Страсти-то какие. Пока единственные напасти, которые я встретил - это жара и москиты, проклятые... Ладно, я готов. Идем?";
			link.l1.go = "Startsailor_5";			
		break;
		
		case "Startsailor_5":
			dialog.text = "Поднимайтесь наверх и ступайте в шлюпку, месье. Добро пожаловать на Карибы!";
			link.l1 = "";
			link.l1.go = "Startsailor_6";			
		break;
		
		case "Startsailor_6":
			DialogExit();
			chrDisableReloadToLocation = false;
			i = FindLocation("Fortfrance_town");
			setCharacterShipLocation(pchar, GetCityFrom_Sea(locations[i].fastreload));
		    setWDMPointXZ(GetCityFrom_Sea(locations[i].fastreload));
			DoQuestReloadToLocation("Fortfrance_town", "reload", "reload1", "Sharlie_onLand");
		break;
		// <-- матрос на корабле, прибытие в Сен-Пьер
		
		// --> арест в резиденции
		case "Sharlie_arest":
			dialog.text = "Немедленно сдайте оружие, месье, и следуйте за нами!";
			link.l1 = "Вот так влип...";
			link.l1.go = "Sharlie_arest_1";			
		break;
		
		case "Sharlie_arest_1":
			DialogExit();
			chrDisableReloadToLocation = false;
			DoFunctionReloadToLocation("FortFrance_prison", "goto", "goto9", "");
			WaitDate("", 0, 0, 2, 0, 10); //крутим время
			RecalculateJumpTable();
			RemoveAllCharacterItems(PChar, true);
			sld = characterFromId("Puancie");
			sld.dialog.currentnode = "Puancie_Jail"; 
			LAi_SetActorTypeNoGroup(sld);
			ChangeCharacterAddressGroup(sld, "FortFrance_prison", "goto", "goto13");
			DoQuestFunctionDelay("Puancie_InJail", 10.0);
		break;
		// арест в резиденции
		
		// --> офицер базы
		case "Maltie_officer":
			ref location = &Locations[FindLocation(pchar.location)];
			if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "begin")
			{
				dialog.text = "Рад вас видеть, месье де Мор. По какому вопросу пожаловали?";
				link.l1 = TimeGreeting()+", офицер. Я хочу поговорить о моем брате, Мишеле де Монпе. Причем неофициально. Мне хотелось бы немного больше узнать о его службе здесь.";
				link.l1.go = "spanish";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "think")
			{
				dialog.text = "Ну, как прошел допрос? Много нового узнали?";
				link.l1 = "Настолько много, что я забираю этого испанца к себе на корабль. Это важный свидетель, и он должен быть доставлен на Сент-Кристофер для дальнейших разбирательств.";
				link.l1.go = "spanish_10";
				break;
			}
			if (!CheckAttribute(location, "first_meeting"))
			{
				dialog.text = "Месье, как вы попали сюда? По какому делу вы здесь?";
				link.l1 = "Я пришел, чтобы увидеть своего брата, Мишеля де Монпе.";
				link.l1.go = "Maltie_officer_1";
				location.first_meeting = true;
			}
			else
			{
				dialog.text = "Месье, я прошу вас не забывать, что вы находитесь на военном объекте. Так что ведите себя соответсвующим образом.";
				link.l1 = "Да, конечно, офицер.";
				link.l1.go = "exit";
				NextDiag.TempNode = "Maltie_officer";
			}
		break;
		
		case "Maltie_officer_1":
			dialog.text = "Мишель де Монпе находится под стражей в одной из камер, заключен по личному приказу шевалье Филиппа де Пуанси. Спуститесь на нижний ярус, там отыщете казематы. Думаю, не заблудитесь.";
			link.l1 = "Спасибо!";
			link.l1.go = "exit";
			NextDiag.TempNode = "Maltie_officer";
		break;
		// офицер базы
		
		// --> солдаты базы
		case "Maltie_soldier":
			dialog.text = "Здравствуйте, месье. Я чем-нибудь могу помочь вам?";
			link.l1 = "Благодарю, солдат. Увы, помочь вы мне ничем не можете...";
			link.l1.go = "exit";
			NextDiag.TempNode = "Maltie_soldier";
		break;
		// --> солдаты базы
		
		// --> мальтиец-проводник
		case "Sharlie_maltie":
			dialog.text = "Я здесь, месье. Так это вы ищете Мишеля де Монпе? И вы - его брат?";
			link.l1 = "Да, это так. Я его сводный брат Шарль. Мне нужно срочно увидеть Мишеля! Он попал в неприятности, да?";
			link.l1.go = "Sharlie_maltie_1";			
		break;
		
		case "Sharlie_maltie_1":
			dialog.text = "К сожалению, да, месье. Мишель арестован и находится в нашей тюрьме. Приказ о его помещении под стражу выдан и подписан самим шевалье де Пуанси, генерал-губернатором французских колоний архипелага. Мы все были буквально ошарашены этим\nВаш брат - образец мужественности, решительности и отваги, гордость нашего Ордена, и тут - такое! Угнетает также то, что мы, его друзья, вынуждены теперь запирать за ним решетку каземата и смотреть, как за преступником! Мы делаем все, чтобы облегчить его участь, но... тюрьма есть тюрьма.";
			link.l1 = "Так в чем же его обвиняют? Он совершил преступление?";
			link.l1.go = "Sharlie_maltie_1_1";			
		break;
		
		case "Sharlie_maltie_1_1":
			dialog.text = "Вздор! Чистой воды вздор! Они обвинили Мишеля в растрате и присвоении государственных денег. Это полная чушь! Мы все уверены в том, что это какие-то грязные политические игры. Мишель участвовал в секретных операциях, проводимых Орденом, и, видимо, узнал больше, чем положено было знать\nИли что-то еще. Но украсть деньги! В это никто не верит. Это предлог, а не причина, причем грубый и нелепый предлог! Но довольно слов. Ваш брат очень ждал вас, и, думаю, он сам вам все расскажет.";
			link.l1 = "Хорошо. Где находится тюрьма?";
			link.l1.go = "Sharlie_maltie_1_2";
		break;
		
		case "Sharlie_maltie_1_2":
			dialog.text = "Это на нашей подземной базе, тут, в городе. Следуйте за мной, я вас проведу!";
			link.l1 = "...";
			link.l1.go = "Sharlie_maltie_2";
		break;
		
		case "Sharlie_maltie_2":
			DialogExit();
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "FortFrance_town", "reload", "reload7_back", "Maltie_GoTown", -1);
		break;
		
		case "Sharlie_maltie_3":
			dialog.text = "Вот мы и пришли. Это наша база - Ордена Мальтийских рыцарей. Казематы находятся внизу. Пройдите мимо столовой и комнаты для молитв и спуститесь по лестнице вниз. Там вы найдете коридор с зарешеченными камерами. В одной из них и содержится ваш несчастный брат\nСтупайте, Шарль, и помогите нашему Мишелю! Он ни в чем не виноват, здесь все готовы подтвердить это под присягой...";
			link.l1 = "Я затем и прибыл в эту глушь, чтобы помочь брату. Надеюсь, мне удастся хоть что-то сделать.";
			link.l1.go = "Sharlie_maltie_4";
		break;
		
		case "Sharlie_maltie_4":
			DialogExit();
			chrDisableReloadToLocation = false;//открыть локацию
			npchar.lifeday = 0;
			LAi_ActorGoToLocator(npchar, "goto", "goto1", "none", -1);
		break;
		// мальтиец-проводник
		
		// --> найм матросов
		case "Sharlie_sailor":
			dialog.text = "Доброго здоровья, месье. Вы что-то хотели?";
			link.l1 = "Да. У меня есть в собственности корабль, но нет команды. Бармен посоветовал мне поговорить с тобой на эту тему - ты и твои товарищи, вроде, как были уволены с какого-то судна и вам нужна работа...";
			link.l1.go = "Sharlie_sailor_1";
		break;
		
		case "Sharlie_sailor_1":
			dialog.text = "Ну, это действительно так. Хотите нанять нас на службу? Что у вас за корабль?";
			link.l1 = "Корабль как корабль, "+GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(RealShips[sti(pchar.ship.type)].basetype), "Name")))+". А вам не все равно?";
			link.l1.go = "Sharlie_sailor_2";
		break;
		
		case "Sharlie_sailor_2":
			dialog.text = "Ну, знаете, месье, не очень-то хочется служить на баркасе или тартане, ну а "+GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(RealShips[sti(pchar.ship.type)].basetype), "Name")))+" нас устраивает. Но сразу хочу предупредить, капитан, что мы пойдем на службу только все вместе. Сработались мы за прошлое время, понимаете...";
			link.l1 = "А сколько вас человек?";
			link.l1.go = "Sharlie_sailor_3";
		break;
		
		case "Sharlie_sailor_3":
			dialog.text = "Нас ровно сорок. Моряки мы опытные, не крысы сухопутные, да и пороху понюхать тоже приходилось не раз. И с парусами управимся, и у орудий встанем, коль нужда придет, и за сабли возьмемся, если потребуется.";
			link.l1 = "Хорошо. Сколько вы хотите?";
			link.l1.go = "Sharlie_sailor_4";
		break;
		
		case "Sharlie_sailor_4":
			dialog.text = "Аванс - по 200 песо на брата, ну а потом - как на всех кораблях. Мы лишнего не попросим, за это не беспокойтесь.";
			if (sti(Pchar.money) >= 8000)
			{
				link.l1 = "Ну что же, тогда - по рукам! Вот ваши монеты.";
				link.l1.go = "Sharlie_sailor_5";
			}
			link.l2 = "К сожалению, у меня нет пока такой суммы.";
			link.l2.go = "Sharlie_sailor_nomoney";
		break;
		
		case "Sharlie_sailor_5":
			if (GetSquadronGoods(pchar, GOOD_FOOD) < 20 || GetSquadronGoods(pchar, GOOD_MEDICAMENT) < 30)
			{
				dialog.text = "А запасы продовольствия у вас есть в трюме, капитан? И лекарства? Нет? Ну, тогда сначала закупите хотя бы какой-то минимум - тогда и возвращайтесь.";
				link.l1 = "Хм. Ты прав. Хорошо, я так и сделаю.";
				link.l1.go = "exit";
				NextDiag.TempNode = "Sharlie_sailor_again";
			}
			else
			{
				AddMoneyToCharacter(pchar, -8000);
				dialog.text = "Отлично, капитан! Я немедленно собираю ребят и мы сейчас же отправимся на ваш корабль.";
				link.l1 = "Превосходно. Готовьте судно к выходу в море.";
				link.l1.go = "Sharlie_sailor_6";
			}
		break;
		
		case "Sharlie_sailor_6":
			DialogExit();
			LAi_SetStayType(npchar);
			GetCharacterPos(pchar, &locx, &locy, &locz);
			ChangeCharacterAddressGroup(npchar, "Fortfrance_tavern", "goto", LAi_FindNearestFreeLocator("goto", locx, locy, locz));
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "", "", "", "", 5);
			npchar.lifeday = 0;
			SetCrewQuantityOverMax(PChar, 40);
			pchar.Ship.Crew.Morale = 50;
			pchar.Ship.Crew.Exp.Sailors = 50;
			pchar.Ship.Crew.Exp.Cannoners = 50;
			pchar.Ship.Crew.Exp.Soldiers = 50;
			AddQuestRecord("Sharlie", "7");
			pchar.questTemp.Sharlie = "skiper";
			DeleteAttribute(pchar, "GenQuest.CannotWait");//снимаем запрет, если не был снят раньше
		break;
		
		case "Sharlie_sailor_nomoney":
			dialog.text = "Ну, тогда как соберете - возвращайтесь. Думаю, вы сможете найти меня здесь, в таверне - пока никаких кораблей на рейде нет, службы не предвидится. Будем и дальше пропивать свои монеты, ха-ха!";
			link.l1 = "Хорошо. Я постараюсь вернуться как можно скорее.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Sharlie_sailor_again";
		break;
		
		case "Sharlie_sailor_again":
			dialog.text = "Ну что, капитан, вы готовы нанять меня и моих товарищей на свое судно? Нам не терпится снова выйти в море! Да и в карманах уже начинает ветер гулять...";
			if (sti(Pchar.money) < 8000)
			{
				link.l1 = "Нет пока, я еще подготавливаюсь.";
				link.l1.go = "exit";
				NextDiag.TempNode = "Sharlie_sailor_again";
			}
			else
			{
				link.l1 = "Да. Получите ваш аванс. Теперь вы у меня на службе.";
				link.l1.go = "Sharlie_sailor_5";
			}
		break;
		// найм матросов
		
		// наводчик на штурмана
		case "skipertalker":
			dialog.text = LinkRandPhrase("Приветствую, капитан! Что вам угодно?","Здравствуйте, сударь. Чем могу быть вам полезен?","Доброго дня, уважаемый. Вы что-то хотели?");
			link.l1 = RandPhraseSimple("У меня есть вопрос к тебе.", "Мне нужна информация о делах в этой колонии.");
			link.l1.go = "skipertalker_1";
			link.l2 = "Просто решил поздороваться. Бывай!";
			link.l2.go = "exit";
			NextDiag.TempNode = "skipertalker";
		break;
		
		case "skipertalker_1":
			dialog.text = RandPhraseSimple("Какие вопросы?", "Что вам угодно?");
			link.l1 = "Послушайте, "+GetAddress_FormToNPC(NPChar)+", тут такое дело... Я ищу штурмана на свой корабль - может, знаете подходящего человека в вашем городе?";
			link.l1.go = "skipertalker_2";
		break;
		
		case "skipertalker_2":
			dialog.text = "Штурман? Хм... Есть тут такой... вот только незадача - в тюрьме он сейчас. За долги его посадили, наверное, уже месяц в каземате, бедолага.";
			link.l1 = "За долги? Хм... Как его зовут, не подскажете?";
			link.l1.go = "skipertalker_3";
		break;
		
		case "skipertalker_3":
			dialog.text = "Фульк Делюк его зовут. Спросите у коменданта в тюрьме. Но только не думаю, что его отпустят так просто, разве что вы заплатите за него долг, ха-ха!";
			link.l1 = "Возможно, и заплачу. Благодарю за информацию, вы мне очень помогли!";
			link.l1.go = "exit";
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeday = 0;
			pchar.questTemp.Sharlie = "jailskiper";
			AddQuestRecord("Sharlie", "8");
		break;
		
		// --> штурман
		case "Folke":
			dialog.text = "Чем обязан такому вниманию, месье?";
			link.l1 = "Приветствую, Фульк. Все очень просто - у меня есть корабль, но нет штурмана, а он мне очень нужен. Поэтому я и выкупил тебя из долговой ямы...";
			link.l1.go = "Folke_1";
		break;
		
		case "Folke_1":
			dialog.text = "Вы хотите сказать, что вытащили меня отсюда, чтобы взять к себе на службу?";
			link.l1 = "Именно так. Думаю, ты быстро отработаешь затраченные на тебя деньги. А затем... впрочем, там и посмотрим.";
			link.l1.go = "Folke_2";
		break;
		
		case "Folke_2":
			dialog.text = "Благодарю вас, месье. Мне чертовски опостылели эти казематы. Я с удовольствием вновь поднимусь на палубу корабля. Эх, море, море...";
			link.l1 = "Я рад, что мы поняли друг друга, Фульк. Да, еще: у тебя есть еще какие-то познания в морском деле, кроме как управлении кораблем?";
			link.l1.go = "Folke_3";
		break;
		
		case "Folke_3":
			dialog.text = "Всего понемногу, кэп. Когда я служил наемником в голландском флоте, я научился наводить орудия и грамотно перезаряжать их. Так что в бою могу занять место на орудийной палубе. А вот торговаться c купцами или забрасывать абордажные крючья - это совсем не мое.";
			link.l1 = "Понятно. Теперь следуй за мной на корабль, посмотришь опытным глазом, что да как. А потом я хочу как можно скорее отправиться на Гваделупу.";
			link.l1.go = "Folke_4";
		break;
		
		case "Folke_4":
			dialog.text = "Слушаюсь, кэп!";
			link.l1 = "...";
			link.l1.go = "Folke_5";
		break;
		
		case "Folke_5":
			DialogExit();
			chrDisableReloadToLocation = false;//открыть локацию
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешить драться
			AddQuestRecord("Sharlie", "10");
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			pchar.quest.Sharlie_skiper.win_condition.l1 = "location";
			pchar.quest.Sharlie_skiper.win_condition.l1.location = "My_Cabin_Small";
			pchar.quest.Sharlie_skiper.function = "Sharlie_SkiperTalk";
			//прерывание на засаду пиратов - принудительный квест
			pchar.quest.Sharlie_seabattle.win_condition.l1 = "location";
			pchar.quest.Sharlie_seabattle.win_condition.l1.location = "Fortfrance_town";
			pchar.quest.Sharlie_seabattle.function = "SharlieSeabattle_agent";
		break;
		
		case "Folke_6":
			pchar.GenQuest.StoreGoods.StoreIdx = Fortfrance_STORE;
			pchar.GenQuest.StoreGoods.Starting = true; // заполняем магазин 250912
			dialog.text = "Отличный люггер, капитан! Весьма и весьма достойный корабль. На таком можно без опаски не то что на Гваделупу отправляться, но хоть через все Карибское море.";
			link.l1 = "Очень хорошо. По крайней мере, деньги не пропали даром... Какие-нибудь советы перед тем как отправиться в путь будут, Фульк?";
			link.l1.go = "Folke_8";
		break;
		
		case "Folke_7":
			dialog.text = "Да уж, этот шлюп основательно поврежден, капитан. Для перехода до Гваделупы он с большего годен, но по прибытию в Бас-Тер нужно сразу поставить его на ремонт.";
			link.l1 = "У меня не было выбора - на верфи предложили только эту посудину. Да еще и содрали приличную сумму, а чинить ее, понимаешь ли, времени у них нет... Какие-нибудь советы перед тем как отправиться в путь будут, Фульк?";
			link.l1.go = "Folke_8";
		break;
		
		bOk = (GetSquadronGoods(pchar, GOOD_BALLS) >= 80) && (GetSquadronGoods(pchar, GOOD_GRAPES) >= 80) && (GetSquadronGoods(pchar, GOOD_KNIPPELS) >= 80) && (GetSquadronGoods(pchar, GOOD_BOMBS) >= 80) && (GetSquadronGoods(pchar, GOOD_POWDER) >= 180);
		case "Folke_8":
			if (bOk)
			{
				dialog.text = "Ну, боеприпасами вы запаслись достаточно, капитан. Этого арсенала нам хватит вполне, только не забывайте своевременно пополнять его.";
				link.l1 = "Конечно, это же само собой разумеется. Еще какие-то замечания?";
				link.l1.go = "Folke_10";
			}
			else
			{
				dialog.text = "Я осмотрел трюм, капитан. У нас недостаточно боеприпасов. Нужно как минимум по сто штук ядер, книппелей и бомб, а также сто порций картечи и пороха на двести выстрелов. Закупите необходимый арсенал, капитан - все это не будет стоить дорого, зато спасет наши жизни в случае нападения пиратов или испанцев.";
				link.l1 = "Хорошо. Я последую твоему совету. Отправляюсь на берег.";
				link.l1.go = "Folke_9";
			}
		break;
		
		case "Folke_9":
			DialogExit();
			NextDiag.CurrentNode = "Folke_goods_1";
			LAi_SetStayType(npchar);
			AddQuestRecord("Sharlie", "12");
		break;
		
		case "Folke_goods_1":
			dialog.text = "Вы закончили закупку амуниции, капитан?";
			if (bOk)
			{
				link.l1 = "Да, закончил. Еще какие-то замечания?";
				link.l1.go = "Folke_10";
			}
			else
			{
				link.l1 = "Нет, я еще этим занимаюсь.";
				link.l1.go = "exit";
				NextDiag.TempNode = "Folke_goods_1";
			}
		break;
		
		bOk = (GetSquadronGoods(pchar, GOOD_WEAPON) >= 50);
		case "Folke_10":
			if (bOk)
			{
				dialog.text = "Оружия для команды вы закупили достаточно, и правильно сделали - не дай Бог рукопашная - не голыми же руками драться. Не забывайте проверять его количество, потому что безоружный матрос - это мертвый матрос\nИ лучше держать оружие с запасом, ибо проклятые крысы любят грызть рукояти сабель и пистолей, приводя их в негодность.";
				link.l1 = "Понятно. Вижу, ты еще что-то хочешь сказать?";
				link.l1.go = "Folke_11";
			}
			else
			{
				dialog.text = "У нас нехватка оружия для матросов. Не дай Бог рукопашная - что им, голыми руками драться? Безоружный матрос - это мертвый матрос. Как я понял, у вас сорок человек экипажа\nНужно купить оружие каждому, и лучше с запасом, комплектов пятьдесят, ибо проклятые крысы любят грызть рукояти сабель и пистолей, приводя их в негодность.";
				link.l1 = "Так и поступим. Скоро вернусь.";
				link.l1.go = "Folke_10_1";
			}
		break;
		
		case "Folke_10_1":
			DialogExit();
			NextDiag.CurrentNode = "Folke_goods_2";
			LAi_SetStayType(npchar);
			AddQuestRecord("Sharlie", "13");
		break;
		
		case "Folke_goods_2":
			dialog.text = "Вы закончили закупку оружия, капитан?";
			if (bOk)
			{
				link.l1 = "Оружие в трюме. Вижу, ты еще что-то хочешь сказать?";
				link.l1.go = "Folke_11";
			}
			else
			{
				link.l1 = "Нет, я еще этим занимаюсь.";
				link.l1.go = "exit";
				NextDiag.TempNode = "Folke_goods_2";
			}
		break;
		
		bOk = (GetSquadronGoods(pchar, GOOD_FOOD) >= 100) && (GetSquadronGoods(pchar, GOOD_RUM) >= 10);
		case "Folke_11":
			if (bOk)
			{
				dialog.text = "Наверное, больше ничего. Провизии у нас достаточно, о роме для команды вы тоже позаботились - очень хорошо, так как нет лучшего лекарства от всех хворей, как добрая кружка рому после вахты. Матросы любят и уважают капитанов, выдающих ежедневные порции рома...";
				link.l1 = "Ну, как я понял, мы можем смело отправляться в путь?";
				link.l1.go = "Folke_12";
			}
			else
			{
				dialog.text = "Да. Это касается провианта и рома. Если на корабле мало провианта - это плохо. Никогда не знаешь, на сколько затянется рейс - штиль или шторм могут нарушить все планы. А если закончится еда - быть беде: голодный бунт обеспечен\nКасательно рома всё не так серьезно, конечно, но рекомандую держать его на корабле постоянно - нет лучшего лекарства от всех хворей, как добрая кружка рому после вахты. Матросы любят и уважают капитанов, выдающих ежедневные порции рома\nТак что докупите необходимое количество, хотя бы сто пачек провианта и десять бочонков рому.";
				link.l1 = "Пожалуй, ты прав. Пойду снова к купцу.";
				link.l1.go = "Folke_11_1";
			}
		break;
		
		case "Folke_11_1":
			DialogExit();
			NextDiag.CurrentNode = "Folke_goods_3";
			LAi_SetStayType(npchar);
			AddQuestRecord("Sharlie", "14");
		break;
		
		case "Folke_goods_3":
			dialog.text = "Вы закончили закупку провизии и рома, капитан?";
			if (bOk)
			{
				link.l1 = "Да. Теперь мы можем смело отправляться в путь?";
				link.l1.go = "Folke_12";
			}
			else
			{
				link.l1 = "Нет, я еще этим занимаюсь.";
				link.l1.go = "exit";
				NextDiag.TempNode = "Folke_goods_3";
			}
		break;
		
		case "Folke_12":
			dialog.text = "Да, кэп. Можно поднимать якоря и брать курс на север, к Гваделупе, как вы и хотели.";
			link.l1 = "Не будем медлить! В путь!";
			link.l1.go = "Folke_13";
		break;
		
		case "Folke_13":
			dialog.text = "Тогда я отправляюсь на свое место на палубе. Приказывайте отчаливать, капитан!";
			link.l1 = "...";
			link.l1.go = "Folke_14";
		break;
		
		case "Folke_14":
			DialogExit();
			LAi_SetImmortal(npchar, false);
			chrDisableReloadToLocation = true;
			LAi_SetActorType(npchar);
			AddQuestRecord("Sharlie", "15");
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "OpenTheDoors", -1);
			npchar.quest.OfficerPrice = 20;
			Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(npchar.id);
			npchar.loyality = 30;
			npchar.greeting = "Gr_Officer";
			npchar.Dialog.Filename = "Enc_Officer_dialog.c";
			npchar.quest.meeting = true;
			AddDialogExitQuestFunction("LandEnc_OfficerHired");
			pchar.questTemp.Sharlie = "seabattle";//в Ле Франсуа
			DeleteAttribute(pchar, "NoNavyPenalty"); // штрафуем за нехватку навигации
		break;
		// штурман
		
		// --> пират-обманщик
		case "Seabattle_pirate":
			dialog.text = "Прошу прощения, ведь это вы - "+GetFullName(pchar)+"?";
			link.l1 = "Именно так. Чем обязан вашему вниманию, сударь?";
			link.l1.go = "Seabattle_pirate_1";
		break;
		
		case "Seabattle_pirate_1":
			dialog.text = "Позвольте представиться - "+GetFullName(npchar)+". Меня послал к вам Чезаре Крейг. Вы, должны его знать - это хозяин таверны в Ле Франсуа. Насколько ему известно, вы собираетесь на Гваделупу, и он хочет предложить вам неплохо подзаработать.";
			link.l1 = "Хм... Забавно! Интересно, и откуда же Чезаре Крейг так осведомлен о моих планах?";
			link.l1.go = "Seabattle_pirate_2";
		break;
		
		case "Seabattle_pirate_2":
			dialog.text = "Капитан, это же просто. Ваш корабль в порту Сен-Пьера сейчас - единственный, так что про вас уже всем практически все известно: и кто вы, и куда идете. В наших краях слухи разносятся молниеносно. Так вам интересно послушать мое предложение?";
			link.l1 = "Конечно. Я никогда не прочь заработать.";
			link.l1.go = "Seabattle_pirate_3";
		break;
		
		case "Seabattle_pirate_3":
			dialog.text = "Вот это разговор! Сразу видно деловую хватку. Так вот, Чезаре нужно срочно перевезти на Гваделупу тамошнему купцу груз нашего местного вина, двести бочонков. Трюм вашего корабля без труда их вместит\nЗа эту несложную работу вы получите целых десять тысяч песо - Чезаре очень спешит, а других кораблей, кроме вашего, сейчас у наших берегов нет. Соглашайтесь - такие выгодные предложения не каждый день поступают.";
			link.l1 = "Десять тысяч песо? Ну конечно же я согласен! Где нужно произвести погрузку?";
			link.l1.go = "Seabattle_pirate_4";
		break;
		
		case "Seabattle_pirate_4":
			dialog.text = "Отправляйтесь на корабле в порт Ле Франсуа и поговорите с Чезаре. Он сам все организует - вам нужно будет только поставить корабль у берега. Не подведите, кэп: Крейг пообещал мне тысячу песо, если мне удастся уговорить вас...";
			link.l1 = "Не волнуйтесь, сударь. Считайте, что вы меня уговорили. Как только я буду готов к выходу в море - сразу отправлюсь в Ле Франсуа.";
			link.l1.go = "Seabattle_pirate_5";
		break;
		
		case "Seabattle_pirate_5":
			dialog.text = "Вот и славно! Тогда я пойду за своей тысячей. Спасибо, кэп!";
			link.l1 = "Да не за что...";
			link.l1.go = "Seabattle_pirate_6";
		break;
		
		case "Seabattle_pirate_6":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "gate_back", "none", "", "", "Seabattle_pirate_open", -1);
			AddQuestRecord("Sharlie", "11");
		break;
		// пират-обманщик
		
		// офицер Гриффондора
		case "griffondor_officer":
			dialog.text = "";
			link.l1 = "";
			link.l1.go = "exit";
		break;
		
		// командир абордажной роты по защите Сен-Пьера
		case "rosetti":
			PlaySound("VOICE\Russian\EvilPirates01.wav");
			dialog.text = "Капитан, абордажная рота построена и в полной боевой готовности! Ждем ваших приказаний!";
			link.l1 = "";
			link.l1.go = "rosetti_1";
		break;
		
		case "rosetti_1":
			DialogExit();
			bDisableCharacterMenu = true;//лоченые интерфейсы
			ChangeShowIntarface();
			LAi_SetActorType(pchar);
			SetMainCharacterIndex(GetCharacterIndex("DefendSP_soldier_0"));
			PChar = GetMainCharacter();			
			LAi_SetPlayerType(PChar);
			sld = characterFromId("Blaze");
			sld.dialog.filename = "MainHero_dialog.c";
			sld.dialog.currentnode = "SP_defend";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;
		
		case "rosetti_2":
			PlaySound("interface\abordage_wining.wav");
			dialog.text = "Есть, капитан! Рота, готовьсь! Выступаем! Ура, ура, ура! Вперед, за капитаном!";
			link.l1 = "";
			link.l1.go = "rosetti_3";
		break;
		
		case "rosetti_3":
			DialogExit();
			PlaySound("interface\abordage_wining.wav");
			bDisableCharacterMenu = false;//лоченые интерфейсы
			ChangeShowIntarface();
			for (i=0; i<=12; i++)
			{
				sld = CharacterFromID("DefendSP_soldier_"+i);
				LAi_SetActorType(sld);
				LAi_ActorFollowEverywhere(sld, "", -1);
				LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			}
			// прерывание на джунгли перед выходом из города
			pchar.quest.DefendSP_jungle1.win_condition.l1 = "location";
			pchar.quest.DefendSP_jungle1.win_condition.l1.location = "Martinique_jungle_01";
			pchar.quest.DefendSP_jungle1.function = "DefendSP_SpainPatrol";
		break;
		
		case "spain_patrol":
			dialog.text = "Французы! К бою! Лоренцо, бегом в лагерь! Поднять тревогу!";
			link.l1 = "...";
			link.l1.go = "spain_patrol_1";
		break;
		
		case "spain_patrol_1":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешить драться
			for (i=1; i<=4; i++)
			{
				sld = CharacterFromID("DefendSP_spapatrol_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
				LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
				LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
				LAi_group_SetCheck("EnemyFight", "DefendSP_SpaPatrolDie");
				AddDialogExitQuest("MainHeroFightModeOn");
			}
			sld = CharacterFromID("DefendSP_spapatrol_5");
			LAi_ActorRunToLocation(sld, "reload", "reload2_back", "none", "", "", "DefendSP_GateAlarm", -1);
		break;
		
		// страж истины
		case "spanish":
			dialog.text = "Вы понимаете, что я не могу разглашать подобную информацию?";
			link.l1 = "А вы понимаете, что только благодаря моей своевременной помощи Сен-Пьер не был разобран испанцами по кирпичику? Мой брат скрылся, оставив службу Ордену. Это неспроста. Я, как представитель интересов Филиппа де Пуанси, обязан разобраться в этом!";
			link.l1.go = "spanish_1";
		break;
		
		case "spanish_1":
			dialog.text = "Хорошо-хорошо, месье де Мор. Я отвечу на все ваши вопросы. Только не горячитесь. Спрашивайте.";
			link.l1 = "Что предшествовало заключению Мишеля под стражу?";
			link.l1.go = "spanish_2";
		break;
		
		case "spanish_2":
			dialog.text = "Мишель де Монпе вел переговоры среди влиятельных пиратских баронов, чтобы вызвать политическую перестановку на Тортуге.";
			link.l1 = "Это мне уже известно. Что еще?";
			link.l1.go = "spanish_3";
		break;
		
		case "spanish_3":
			dialog.text = "Также он готовил военную операцию против испанцев, а именно - захват испанского корабля с очень ценным грузом. Ваш брат должен был каким-то образом вывести испанский транспорт в нужное место прямо под пушки малого фрегата 'Гриффондор'. Мишель отбыл в длительную экспедицию, и некоторое время о нем не было ни слуху, ни духу\nОднако что-то у него пошло не так, поскольку испанского транспорта 'Гриффондор' не дождался, а сам Мишель был обнаружен рыбаками, выброшенный волнами на берег в бухте Ле Марен, контуженный и едва живой. Видимо, операция провалилась\nКазалось бы - на войне, как на войне, хорошо, что вообще жив остался, однако шевалье де Пуанси совершенно неожиданно ополчился против Мишеля, обвинил в растрате и присвоении денежных средств Ордена и заключил под стражу\nКонечно, мы не поверили этим обвинениям: Мишель - честнейший парень, так что одному Богу известно, какая черная кошка пробежала между ним и шевалье. Быть может, сам месье де Пуанси поведает вам об этом?";
			link.l1 = "Возможно. Это все, что вам известно?";
			link.l1.go = "spanish_4";
		break;
		
		case "spanish_4":
			dialog.text = "К сожалению, добавить к сказанному мне нечего. Подробности всех операций, проводимых вашим братом, были известны только ему самому и шевалье де Пуанси. Мы, офицеры и солдаты Ордена, просто выполняли приказы.";
			link.l1 = "Раз шевалье так доверял Мишелю, значит, не все его операции были провальными? Были и успехи?";
			link.l1.go = "spanish_5";
		break;
		
		case "spanish_5":
			dialog.text = "Конечно. Последняя неудача Мишеля де Монпе была также и его первой неудачей, поэтому мы буквально были поражены реакцией шевалье. Еще незадолго до этого при помощи тщательно спланированной операции Мишеля 'Гриффондором' был захвачен испанский галеон, доверху груженый серебром. Одно это могло компенсировать десяток неудач в будущем. И все же ваш брат был арестован.";
			link.l1 = "Ясно. У вас есть какие-то предположения, почему Мишель так спешно скрылся из Сен-Пьера?";
			link.l1.go = "spanish_6";
		break;
		
		case "spanish_6":
			dialog.text = "Я подозреваю, что причины его ареста - в межличностном конфликте с Филиппом де Пуанси. Ваш брат, очевидно, опасается, что преследования со стороны шевалье продолжатся и после освобождения, поэтому принял превентивные меры. И знаете что, месье де Мор - здесь никто не осуждает его решение!\nЧеловек мужественно и доблестно работал на благо Ордена, а его при первой же неудаче, которую он бы компенсировал в дальнейшем сторицей, раненого и больного, бросают в камеру, обвиняя в какой-то совершенной нелепице!\nДа, если что: разговор наш неофициальный, и под присягой повторять свои слова я не буду. Мы поняли друг друга, месье де Мор?";
			link.l1 = "Безусловно, офицер. Мы договорились об этом с самого начала. Скажите, а нападение испанцев на Сен-Пьер не могло быть спровоцировано военными операциями Ордена против испанских кораблей? Ну, тот же галеон с серебром, о котором вы упомянули? Уж больно рьяно кастильцы орудовали на вашей базе...";
			link.l1.go = "spanish_7";
		break;
		
		case "spanish_7":
			dialog.text = "Навряд ли. О нашей базе на Мартинике вообще мало кому известно, да и все наши действия против испанцев были точечными и аккуратно спланированными. Но вы можете сами спросить об этом у пленного испанского офицера, который в данный момент содержится в наших казематах. Мы уже допросили его\nАтака Сен-Пьера - обычный грабительский налет, организованный испанским грандом, бароном Рамоном де-Мендосой-и-Риба, с целью личной наживы и устрашения гражданского населения французких колоний, а также чтобы выслужиться перед Эскориалом.";
			link.l1 = "Я побеседую с вашим пленным. Где мне его найти?";
			link.l1.go = "spanish_8";
		break;
		
		case "spanish_8":
			dialog.text = "Внизу, в камере, где содержался ваш брат.";
			link.l1 = "Хорошо. Я вернусь, после того как допрошу испанца. Возможно, у меня появятся еще вопросы.";
			link.l1.go = "spanish_9";
		break;
		
		case "spanish_9":
			DialogExit();
			NextDiag.CurrentNode = "Maltie_officer";
			AddQuestRecord("Guardoftruth", "2");
			pchar.questTemp.Guardoftruth = "prisoner";
			sld = characterFromId("spa_baseprisoner");
			LAi_CharacterEnableDialog(sld);
			chrDisableReloadToLocation = true;//закрыть локацию
		break;
		
		case "spanish_10":
			dialog.text = "Вот это новость! Но я не могу отпустить пленника, он участвовал в набеге на Сен-Пьер...";
			link.l1 = "Офицер, это важный свидетель. Нападение на Сен-Пьер было совершено не для грабежа. Дону Рамону Мендосе нужно было другое. Мы должны разобраться с этим окончательно. Так вы выдадите мне этого испанца, или мне затребовать разрешение у де Пуанси?";
			link.l1.go = "spanish_11";
		break;
		
		case "spanish_11":
			dialog.text = "Ладно, забирайте его, раз уж он так важен вам. Все равно я собирался казнить мерзавца публично на площади Сен-Пьера... Но строго под вашу личную ответственность!";
			link.l1 = "Безусловно. Перед шевалье де Пуанси за этого испанца буду отвечать я. Распорядитесь надеть на пленника кандалы и доставить в порт к моей шлюпке.";
			link.l1.go = "spanish_12";
		break;
		
		case "spanish_12":
			dialog.text = "Будет сделано, капитан.";
			link.l1 = "И еще, офицер: имя 'Мигель Дичозо' о чем-нибудь говорит вам?";
			link.l1.go = "spanish_13";
		break;
		
		case "spanish_13":
			dialog.text = "Нет. Впервые слышу. А что?";
			link.l1 = "Точно нет? То есть ни на вашей базе, ни в губернаторском дворце, ни вообще в Сен-Пьере вы не встречали человека с таким именем?";
			link.l1.go = "spanish_14";
		break;
		
		case "spanish_14":
			dialog.text = "Нет, не встречал. У нас, знаете ли, не жалуют испанцев.";
			link.l1 = "Ясно. Впрочем, этого и следовало ожидать. Было бы слишком просто... Ладно, я еще раз поговорю с пленным испанцем, а вы тем временем подготовьте его к доставке. И: спасибо, офицер! Вы мне очень помогли.";
			link.l1.go = "spanish_15";
		break;
		
		case "spanish_15":
			dialog.text = "Да не за что... Как вы думаете, месье де Мор: где же сейчас ваш брат?";
			link.l1 = "Я бы и сам хотел знать ответ на этот вопрос. И узнаю... рано или поздно. Удачи!";
			link.l1.go = "spanish_16";
		break;
		
		case "spanish_16":
			DialogExit();
			NextDiag.CurrentNode = "Maltie_officer";
			AddQuestRecord("Guardoftruth", "3");
			pchar.questTemp.Guardoftruth = "toship";
			sld = characterFromId("spa_baseprisoner");
			sld.dialog.currentnode = "spa_prisoner_28";
			LAi_CharacterEnableDialog(sld);
		break;
		
		// монах-посланник от Винсенто
		case "monk_vinsento":
			dialog.text = TimeGreeting()+"! Вы и есть капитан "+GetFullName(pchar)+"?";
			link.l1 = "Да, это я. Что вам угодно?";
			link.l1.go = "monk_vinsento_1";
		break;
		
		case "monk_vinsento_1":
			dialog.text = "Я к вам от отца Винсенто. У меня для вас...";
			link.l1 = "От отца Винсенто? Боюсь, с Его Преосвященством у меня дела окончены. После того, как он натравил на меня дружка Диего де Монтойи, Алонсо де Мальдонадо. Однако он просчитался, так ему и передайте.";
			link.l1.go = "monk_vinsento_2";
		break;
		
		case "monk_vinsento_2":
			dialog.text = "Постойте, капитан. Отец Винсенто ожидал от вас такой реакции, и предупредил меня об этом. Уверяю, Его Преосвященство не желает вам зла. Пожалуйста, прочтите его письмо. Это очень, очень важно.";
			link.l1 = "Не желает мне зла? Хм. Может, он также ничего не рассказывал про меня и дону де Мальдонадо? Не верится мне что-то.";
			link.l1.go = "monk_vinsento_3";
		break;
		
		case "monk_vinsento_3":
			dialog.text = "Возьмите письмо, капитан. Прочтите его, и решайте сами. Только помните, что судьба всего христианского мира сейчас в ваших руках, и отнеситесь к этому со всей серьезностью. Да просветит вас Господь, и да направит он ваши стопы на путь истинный!";
			link.l1 = "Ладно, давайте сюда письмо.";
			link.l1.go = "monk_vinsento_4";
		break;
		
		case "monk_vinsento_4":
			GiveItem2Character(pchar, "specialletter"); 
			ChangeItemDescribe("specialletter", "itmdescr_specialletter_vinsento");
			sld = ItemsFromID("specialletter");
			sld.text = "Letter_Vincento_last";
			dialog.text = "Держите. Надеюсь, вы примете правильное решение.";
			link.l1 = "...";
			link.l1.go = "monk_vinsento_5";
		break;
		
		case "monk_vinsento_5":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload4_back", "none", "", "", "", 30.0);
			ReOpenQuestHeader("Sharlie"); // patch-8
			AddQuestRecord("Sharlie", "40");
			CloseQuestHeader("Ksochitam");
		break;
		
		// падре Адриан
		case "adrian":
			dialog.text = "Приветствую, сын мой. Да благословит Господь дела твои...";
			link.l1 = "Здравствуйте, отец Адриан. Его Преосвященство сказал мне, что вы можете снабдить меня оберегами и лекарствами...";
			link.l1.go = "adrian_1";
		break;
		
		case "adrian_1":
			dialog.text = "Да, конечно. Вот то, что я привез из Сантьяго специально для тебя. Здесь освященные обереги и целебные отвары. И даже редкая, уникальная тинктура Ометочтли, улучшающая боевые качества. Это всё тебе, сын мой.";
			link.l1 = "Спасибо!";
			link.l1.go = "adrian_2";
		break;
		
		case "adrian_2":
			for(i=2; i<=10; i++)
			{
				if (i == 4 || i == 5 || i == 8 || i == 9) continue;
				TakeNItems(pchar, "amulet_"+i, 2);
			}
			TakeNItems(pchar, "potion2", 20);
			TakeNItems(pchar, "potion4", 10);
			TakeNItems(pchar, "potion7", 3);
			TakeNItems(pchar, "berserker_potion", 3);
			dialog.text = "Если тебе еще понадобятся целебные зелья - ты можешь приобрести их у меня, по одному пузырьку каждого вида в день. Я буду их готовить по мере надобности.";
			link.l1 = "Хорошо, отец Адриан. Я учту это.";
			link.l1.go = "exit";
			link.l2 = "Отлично. Я прямо сейчас хочу приобрести некоторые из них.";
			link.l2.go = "potion";
			NextDiag.TempNode = "adrian_3";
		break;
		
		case "adrian_3":
			dialog.text = "Да благословит тебя Господь, сын мой. Что ты хотел?";
			link.l1 = "Я хочу купить несколько лечебных эликсиров.";
			link.l1.go = "potion";
			link.l2 = "Пока ничего, готовлюсь к походу. Просто заглянул проведать.";
			link.l2.go = "exit";
			NextDiag.TempNode = "adrian_3";
		break;
		
		case "potion":
			dialog.text = "Конечно, сын мой. Какое лекарство ты желаешь приобрести?";
			if (!CheckAttribute(npchar, "potion1_date") || GetNpcQuestPastDayParam(npchar, "potion1_date") >= 1)
			{
				link.l1 = "Простую лечебную эссенцию.";
				link.l1.go = "potion1";
			}
			if (!CheckAttribute(npchar, "potion2_date") || GetNpcQuestPastDayParam(npchar, "potion2_date") >= 1)
			{
				link.l2 = "Целебный эликсир.";
				link.l2.go = "potion2";
			}
			if (!CheckAttribute(npchar, "potion3_date") || GetNpcQuestPastDayParam(npchar, "potion3_date") >= 1)
			{
				link.l3 = "Противоядие.";
				link.l3.go = "potion3";
			}
			if (!CheckAttribute(npchar, "potion4_date") || GetNpcQuestPastDayParam(npchar, "potion4_date") >= 1)
			{
				link.l4 = "Травяную микстуру.";
				link.l4.go = "potion4";
			}
			link.l5 = "Извините, отец Адриан, я передумал.";
			link.l5.go = "exit";
		break;
		
		case "potion1":
			npchar.quest.price = 90;
			npchar.quest.type = 1;
			dialog.text = "Лечебную эссенцию? С тебя 90 песо, сын мой.";
			if (sti(Pchar.money) >= 90)
			{
				link.l1 = "Пожалуйста, отец Адриан. Вот деньги.";
				link.l1.go = "potion_pay";
			}
			else
			{
				link.l1 = "К сожалению, у меня недостаточно средств... Я вернусь позже.";
				link.l1.go = "exit";
			}
		break;
		
		case "potion2":
			npchar.quest.price = 500;
			npchar.quest.type = 2;
			dialog.text = "Целебный эликсир? С тебя 500 песо, сын мой.";
			if (sti(Pchar.money) >= 500)
			{
				link.l1 = "Пожалуйста, отец Адриан. Вот деньги.";
				link.l1.go = "potion_pay";
			}
			else
			{
				link.l1 = "К сожалению, у меня недостаточно средств... Я вернусь позже.";
				link.l1.go = "exit";
			}
		break;
		
		case "potion3":
			npchar.quest.price = 200;
			npchar.quest.type = 3;
			dialog.text = "Противоядие? С тебя 200 песо, сын мой.";
			if (sti(Pchar.money) >= 200)
			{
				link.l1 = "Пожалуйста, отец Адриан. Вот деньги.";
				link.l1.go = "potion_pay";
			}
			else
			{
				link.l1 = "К сожалению, у меня недостаточно средств... Я вернусь позже.";
				link.l1.go = "exit";
			}
		break;
		
		case "potion4":
			npchar.quest.price = 900;
			npchar.quest.type = 4;
			dialog.text = "Микстуру? С тебя 900 песо, сын мой.";
			if (sti(Pchar.money) >= 900)
			{
				link.l1 = "Пожалуйста, отец Адриан. Вот деньги.";
				link.l1.go = "potion_pay";
			}
			else
			{
				link.l1 = "К сожалению, у меня недостаточно средств... Я вернусь позже.";
				link.l1.go = "exit";
			}
		break;
		
		case "potion_pay":
			AddMoneyToCharacter(pchar, -sti(npchar.quest.price));
			iTemp = sti(npchar.quest.type);
			GiveItem2Character(pchar, "potion"+iTemp);
			PlaySound("interface\important_item.wav");
			dialog.text = "Пожалуйста. Держи свое лекарство. Да хранит тебя Господь!";
			link.l1 = "Спасибо, отец Адриан.";
			link.l1.go = "exit";
			SaveCurrentNpcQuestDateParam(npchar, "potion"+iTemp+"_date");
			NextDiag.TempNode = "adrian_3";
		break;
		
		// посланец Дичозо
		case "Dichoso_agent":
			dialog.text = "Капитан "+GetFullName(pchar)+"?";
			link.l1 = "Да, это я. Чем обязан?";
			link.l1.go = "Dichoso_agent_1";
		break;
		
		case "Dichoso_agent_1":
			dialog.text = "У меня к вам сообщение от капитана Мигеля Дичозо. Он сказал, что вы знаете его.";
			link.l1 = "Чести знать лично не удостоился, а слышать о нем - не спорю, доводилось.";
			link.l1.go = "Dichoso_agent_2";
		break;
		
		case "Dichoso_agent_2":
			dialog.text = "Капитан Дичозо хочет с вами встретится. У него предложение к вам лично касательно похода в глубь Мэйна к индейскому городу Тайясаль. Как он сказал - ваш опыт, помноженный на его знания, дадут отличный результат.";
			link.l1 = "Прямо так и сказал?";
			link.l1.go = "Dichoso_agent_3";
		break;
		
		case "Dichoso_agent_3":
			dialog.text = "Именно! Капитан Дичозо будет ждать вас на острове Сент-Кристофер. Дабы избежать ненужных глаз и ушей, Мигель предлагает провести встречу в большой крипте кладбища Капстервиля.";
			link.l1 = "Хм...";
			link.l1.go = "Dichoso_agent_4";
		break;
		
		case "Dichoso_agent_4":
			dialog.text = "Дичозо предупредил, что вы будете колебаться и уполномочил меня заверить, что гарантирует мирный исход переговоров независимо ни от чего. А также попросил передать, что то, что вы нашли на одном острове, лишь малая толика того, что есть в Тайясале.";
			link.l1 = "Даже так! Тогда это очень интересно. Но почему же капитан Дичозо не явился ко мне сам, а прислал третье лицо?";
			link.l1.go = "Dichoso_agent_5";
		break;
		
		case "Dichoso_agent_5":
			dialog.text = "Дон Дичозо разыскивал вас на Исла-Тесоро, потом здесь, а теперь отбыл на Сент-Кристофер, в надежде найти вас там. Ведь вы же офицер самого Филиппа де Пуанси, я не прав? А я должен был ожидать тут, на случай, если вы прибудете в Блювельд.";
			link.l1 = "Тогда все ясно. Ну что же, не буду терять времени и отправляюсь в Капстервиль.";
			link.l1.go = "Dichoso_agent_6";
		break;
		
		case "Dichoso_agent_6":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload4_back", "none", "", "", "Tieyasal_PrepareDichosoTrap", -1);
		break;
		
		// агент Дичозо
		case "Dichoso_crypt_agent":
			dialog.text = "Ну, наконец мы с тобой встретились, капитан "+GetFullName(pchar)+"...";
			if (CheckAttribute(pchar, "questTemp.Tieyasal.MigelKnow")) 
			{
				link.l1 = "Где Мигель Дичозо? И не пытайся юлить. Я прекрасно знаю, кто он есть на самом деле. Думаю, что и ты тоже.";
				link.l1.go = "Dichoso_crypt_agent_2";
			}
			else
			{
				link.l1 = "Полагаю, передо мной Мигель Дичозо собственной персоной?";
				link.l1.go = "Dichoso_crypt_agent_1";
			}
		break;
		
		case "Dichoso_crypt_agent_1":
			dialog.text = "Правильно полагаешь, капитан. Мы уже давно ходим по следу друг друга, разве не так?";
			if (CheckAttribute(pchar, "questTemp.Ksochitam.SQCapBookRead")) // прочел журнал Санта-Квитерии
			{
				link.l1 = "Вот смотрю я на тебя, приятель, и понимаю, что ты лжешь. Никакой ты не Дичозо. Я читал записи в судовом журнале капитана 'Санта-Квитерии', а также расспрашивал о его внешности. Что-то не похож ты на него. Даже сабельного шрама на лице нет.";
				link.l1.go = "Dichoso_crypt_agent_2";
			}
			else
			{
				link.l1 = "Именно так. Как я понимаю, речь пойдет о Тайясале?";
				link.l1.go = "Dichoso_crypt_agent_7";
			}
		break;
		
		case "Dichoso_crypt_agent_2":
			dialog.text = "Хм. Ну что же, не вижу смысла играть в прятки. Мигель предупреждал, что ты чертовски сообразительный каналья...";
			link.l1 = "Где Дичозо?";
			link.l1.go = "Dichoso_crypt_agent_3";
		break;
		
		case "Dichoso_crypt_agent_3":
			dialog.text = "Его тут нет. Я уполномочен встретить тебя и побеседовать от его имени.";
			link.l1 = "У меня нет желания разговаривать с пешкой. Мне нужен ферзь. Так где он?";
			link.l1.go = "Dichoso_crypt_agent_4";
		break;
		
		case "Dichoso_crypt_agent_4":
			dialog.text = "Мы не будем долго с тобой разговаривать, капитан. В общем-то, тебя пригласили сюда не для разглагольствований.";
			link.l1 = "Понимаю. Примитивная ловушка-засада. Я угадал?";
			link.l1.go = "Dichoso_crypt_agent_5";
		break;
		
		case "Dichoso_crypt_agent_5":
			dialog.text = "В точку, приятель. За вот той маленькой дверью есть подвал, а в нем мои люди. Кроме того, в каждый гроб я спрятал по отменному стрелку. Выход назад тебе отрезан. Так что ловушка хоть и примитивная, но ты в нее залез. Желание увидеть Тайясаль перевесило осторожность, да?";
			link.l1 = "А вообще удачное ты выбрал место для засады, дружок. Сразу тут тебя и твоих бандитов по гробам и упакуем.";
			link.l1.go = "Dichoso_crypt_agent_6";
		break;
		
		case "Dichoso_crypt_agent_6":
			dialog.text = "Мне нравится твое чувство юмора. В этом ты похож на Мигеля. Что ни говори - родная кровь... Я сделаю, как он просил: отправлю тебя на тот свет максимально быстро и безболезненно. Ребята, к бою!";
			link.l1 = "Многие пытались это сделать, да руки коротки...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Tieyasal_StartCryptBattle");
		break;
		
		case "Dichoso_crypt_agent_7":
			dialog.text = "Очень хочется туда попасть? Понимаю. Но не думаю, что это хорошая идея.";
			link.l1 = "Тогда о чем ты собрался со мной беседовать?";
			link.l1.go = "Dichoso_crypt_agent_8";
		break;
		
		case "Dichoso_crypt_agent_8":
			dialog.text = "А я и не собираюсь с тобой разводить долгие разговоры. Ты здесь, и этого мне достаточно.";
			link.l1 = "Понимаю. Примитивная ловушка-засада. Я угадал?";
			link.l1.go = "Dichoso_crypt_agent_5";
		break;
		
		// командир абордажников
		case "newcastle_officer":
			dialog.text = "Ждем ваших приказаний, капитан!";
			link.l1 = "Выдвигаемся через джунгли в сторону кладбища Сент-Кристофера. На само кладбище не заходите, занимаете позицию в джунглях у тропы и следите за происходящим. В случае опасности - атакуете.";
			link.l1.go = "newcastle_officer_1";
		break;
		
		case "newcastle_officer_0":
			dialog.text = "Ждем ваших приказаний, капитан!";
			link.l1 = "Выдвигаемся через джунгли в сторону кладбища Сент-Кристофера. На само кладбище не заходите, занимаете позиции в джунглях по обе стороны тропы - окружаете территорию и следите за происходящим. Враг наверняка готовит засаду. Как только увидите неприятеля - немедленно атакуете.";
			link.l1.go = "newcastle_officer_1";
		break;
		
		case "newcastle_officer_1":
			dialog.text = "Есть, капитан!";
			link.l1 = "Хорошо. Вперед!";
			link.l1.go = "newcastle_officer_2";
		break;
		
		case "newcastle_officer_2":
			DialogExit();
			chrDisableReloadToLocation = false;
			locations[FindLocation("Charles_exittown")].DisableEncounters = true; //энкаутеры закрыть
			locations[FindLocation("Charles_CaveEntrance")].DisableEncounters = true; //энкаутеры закрыть
			for(i=2; i<=4; i++)
			{
				locations[FindLocation("Charles_Jungle_0"+i)].DisableEncounters = true; //энкаутеры закрыть
			}
			LocatorReloadEnterDisable("Shore42", "boat", true);
			for(i=1; i<=iTotalTemp; i++)
			{
				sld = characterFromID("Tieyasal_Oursoldier_"+i);
				LAi_SetActorType(sld);
				LAi_ActorFollowEverywhere(sld, "", -1);
				LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			}
			// на локацию перед кладбищем
			pchar.quest.Tieyasal_newcastle.win_condition.l1 = "location";
			pchar.quest.Tieyasal_newcastle.win_condition.l1.location = "Charles_exittown";
			pchar.quest.Tieyasal_newcastle.function = "Tieyasal_NewcastleGoJungle";
			// на крипту
			pchar.quest.Tieyasal_graveyard.win_condition.l1 = "location";
			pchar.quest.Tieyasal_graveyard.win_condition.l1.location = "Charles_CryptBig2";
			pchar.quest.Tieyasal_graveyard.function = "Tieyasal_InGraveyardCrypt";
		break;
		
		case "Europe":
			PlaySound("VOICE\Russian\military01.wav");
			dialog.text = "Капитан Гобарт! По сведениям лазутчиков, в этом имении укрываются беглые мятежники. В вашем распоряжении пять драгун - обыщите дом и схватите всех, кто там находится! Можете не церемониться, вы действуете от имени короля!";
			link.l1 = "Есть, сэр!";
			link.l1.go = "Europe_1";
		break;
		
		case "Europe_1":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_SetActorType(pchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "Europe_SharlieFinal_1", 5);
		break;
		
		//замечание по обнаженному оружию от персонажей типа citizen
		case "CitizenNotBlade":
			dialog.text = NPCharSexPhrase(NPChar, "Послушайте, я, как гражданин этого города, прошу вас не ходить у нас с обнаженным клинком.", "Знаете, я, как гражданка этого города, прошу вас не ходить у нас с обнаженным клинком.");
			link.l1 = LinkRandPhrase("Хорошо.", "Ладно.", "Как скажете...");
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
			if (npchar.id == "GigoloMan") NextDiag.TempNode = "GigoloMan";
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}