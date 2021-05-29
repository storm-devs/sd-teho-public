void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i, iTemp, iQty;
	string sTemp;
	
	DeleteAttribute(&Dialog,"Links");
	
	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "Явный баг в коде. Сообщите Jason'у, как и при каких обстоятельствах его получили.";
			link.l1 = "Обязательно сообщу!";
			link.l1.go = "exit";
		break;
		
		//разговор на палубе
		case "MarchCap":
			pchar.quest.MarchCapOver.over = "yes"; //снять прерывание
			dialog.text = "Вот и вы, капитан. Теперь приступим к обсуждению подробностей моего предложения. Вы сразу поймете, почему я не захотел об этом говорить в людном месте.";
			link.l1 = "Давайте уже, сударь, не тяните. Я вас внимательно слушаю.";
			link.l1.go = "MarchCap_1";
		break;
		
		case "MarchCap_1":
			pchar.GenQuest.MarchCap.Goods = SelectMarchCapGoods1();//целевой товар
			switch (rand(2))
			{
				case 0: //конвой у острова, установка параметров
					pchar.GenQuest.MarchCap.Island = GetRandomIslandId();
					while(pchar.GenQuest.MarchCap.Island == pchar.GenQuest.MarchCap.Startisland)
					{
						pchar.GenQuest.MarchCap.Island = GetRandomIslandId();
					}
					pchar.GenQuest.MarchCap.Island.Shore = GetIslandRandomShoreId(pchar.GenQuest.MarchCap.Island);
					while(pchar.GenQuest.MarchCap.Island.Shore == "")
					{
						pchar.GenQuest.MarchCap.Island = GetRandomIslandId();
						pchar.GenQuest.MarchCap.Island.Shore = GetIslandRandomShoreId(pchar.GenQuest.MarchCap.Island);
						if (!isLocationFreeForQuests(pchar.GenQuest.MarchCap.Island) || !isLocationFreeForQuests(pchar.GenQuest.MarchCap.Island.Shore)) pchar.GenQuest.MarchCap.Island.Shore = "";
					}
					pchar.GenQuest.MarchCap.DaysQty = GetMaxDaysFromIsland2Island(pchar.GenQuest.MarchCap.Startisland, pchar.GenQuest.MarchCap.Island)+3;
					dialog.text = "Мне удалось разузнать, что через "+FindRussianDaysString(sti(pchar.GenQuest.MarchCap.DaysQty))+" небольшой торговый конвой под флагом "+NationNameGenitive(sti(pchar.GenQuest.MarchCap.Nation))+", два купеческих судна и корабль охранения, будут проходить у "+XI_ConvertString(pchar.GenQuest.MarchCap.Island.Shore+"Gen")+", это у "+XI_ConvertString(pchar.GenQuest.MarchCap.Island+"Gen")+". В трюмах купцов полно "+GetGoodsNameAlt(sti(pchar.GenQuest.MarchCap.Goods))+". Было бы глупо не воспользоваться этой информацией, капитан\nВдвоем мы легко разделаемся с сопровождением, а содержимое трюмов торгашей станет нашим. Ну как, вы согласны отправиться со мной в этот поход?";
					link.l1 = "Звучит заманчиво. Пожалуй, я согласен!";
					link.l1.go = "MarchCap_1_1";
					link.l2 = "Из-за какого-то "+GetGoodsNameAlt(sti(pchar.GenQuest.MarchCap.Goods))+" портить отношения с "+NationNameAblative(sti(pchar.GenQuest.MarchCap.Nation))+"? Нет, я на такое не подпишусь! Прощайте, сударь, и даже не пытайтесь меня задерживать!";
					link.l2.go = "MarchCap_exit";
				break;
				
				case 1: //энкаунтер на глобалке, установка параметров
					pchar.GenQuest.MarchCap.Startcity = SelectAnyColony(pchar.GenQuest.MarchCap.basecity);
					pchar.GenQuest.MarchCap.Finishcity = SelectAnyColony2(pchar.GenQuest.MarchCap.basecity, pchar.GenQuest.MarchCap.Startcity);
					pchar.GenQuest.MarchCap.DaysQty = 5+drand(5);
					dialog.text = "Мне удалось разузнать, что через "+FindRussianDaysString(sti(pchar.GenQuest.MarchCap.DaysQty))+" небольшой торговый конвой под флагом "+NationNameGenitive(sti(pchar.GenQuest.MarchCap.Nation))+", два купеческих судна и корабль охранения, выйдут из "+XI_ConvertString("Colony"+pchar.GenQuest.MarchCap.Startcity+"Gen")+" и отправятся в "+XI_ConvertString("Colony"+pchar.GenQuest.MarchCap.Finishcity+"Acc")+". В трюмах купцов полно "+GetGoodsNameAlt(sti(pchar.GenQuest.MarchCap.Goods))+". Было бы глупо не воспользоваться этой информацией, капитан\nВдвоем мы легко разделаемся с сопровождением, а содержимое трюмов торгашей станет нашим. Основная трудность - отыскать их в море между этими двумя городами... Ну как, вы согласны отправиться со мной в этот поход?";
					link.l1 = "Звучит заманчиво. Пожалуй, я согласен!";
					link.l1.go = "MarchCap_2_1";
					link.l2 = "Из-за какого-то "+GetGoodsNameAlt(sti(pchar.GenQuest.MarchCap.Goods))+" портить отношения с "+NationNameAblative(sti(pchar.GenQuest.MarchCap.Nation))+"? Нет, я на такое не подпишусь! Прощайте, сударь, и даже не пытайтесь меня задерживать!";
					link.l2.go = "MarchCap_exit";
				break;
				
				case 2: //одиночный пиратский кулсейлор у бухты, установка параметров
					pchar.GenQuest.MarchCap.Goods = GOOD_GOLD + drand(makeint(GOOD_SILVER - GOOD_GOLD));
					pchar.GenQuest.MarchCap.GoodsQty = sti(pchar.rank)*50+170+rand(30);
					if (sti(pchar.GenQuest.MarchCap.GoodsQty) > 1600) pchar.GenQuest.MarchCap.GoodsQty = 1500+rand(100);
					pchar.GenQuest.MarchCap.Island = GetRandomIslandId();
					while(pchar.GenQuest.MarchCap.Island == pchar.GenQuest.MarchCap.Startisland)
					{
						pchar.GenQuest.MarchCap.Island = GetRandomIslandId();
					}
					pchar.GenQuest.MarchCap.Island.Shore = GetIslandRandomShoreId(pchar.GenQuest.MarchCap.Island);
					while(pchar.GenQuest.MarchCap.Island.Shore == "")
					{
						pchar.GenQuest.MarchCap.Island = GetRandomIslandId();
						pchar.GenQuest.MarchCap.Island.Shore = GetIslandRandomShoreId(pchar.GenQuest.MarchCap.Island);
						if (!isLocationFreeForQuests(pchar.GenQuest.MarchCap.Island) || !isLocationFreeForQuests(pchar.GenQuest.MarchCap.Island.Shore)) pchar.GenQuest.MarchCap.Island.Shore = "";
					}
					pchar.GenQuest.MarchCap.DaysQty = GetMaxDaysFromIsland2Island(pchar.GenQuest.MarchCap.Startisland, pchar.GenQuest.MarchCap.Island)+1;
					pchar.GenQuest.MarchCap.PirateName = "l" + rand(GetNamesCount(NAMETYPE_ORIG) - 1);//пират
					pchar.GenQuest.MarchCap.ShipType = SelectPirateShipType();
					pchar.GenQuest.MarchCap.Cannon = SelectLevelCannonParameter(sti(pchar.GenQuest.MarchCap.ShipType));
					dialog.text = "Я получил достоверные сведения об одном пирате по кличке "+GetName( NAMETYPE_ORIG, pchar.GenQuest.MarchCap.PirateName, NAME_NOM)+". Так вот, этот головорез недавно хорошенько пощипал "+RandPhraseSimple(RandPhraseSimple("англичан","французов"), RandPhraseSimple("испанцев","голландцев"))+" и загрузил себе полный трюм "+GetGoodsNameAlt(sti(pchar.GenQuest.MarchCap.Goods))+". Но вот ведь незадача: в бою его "+GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.MarchCap.ShipType), "Name")+"Acc"))+" так сильно потрепали, что он со всем этим грузом был вынужден встать на ремонт\nСейчас он находится у "+XI_ConvertString(pchar.GenQuest.MarchCap.Island.Shore+"Gen")+", это у "+XI_ConvertString(pchar.GenQuest.MarchCap.Island+"Gen")+", устанавливает новые мачты и латает пробоины в корпусе. По моим расчетам, у него на это уйдет не больше, чем "+FindRussianDaysString(sti(pchar.GenQuest.MarchCap.DaysQty))+". Если постараемся - то сможем успеть к нему на свидание, и тогда весь груз "+GetGoodsNameAlt(sti(pchar.GenQuest.MarchCap.Goods))+" станет нашим\nСправиться в одиночку с этим пиратом мне не под силу - он весьма искушен в ведении морского боя, но вдвоем мы сумеем разделаться с ним, несмотря на весь его опыт. Ну как, вы согласны отправиться со мной в этот поход?";
					link.l1 = "Звучит заманчиво. Пожалуй, я согласен!";
					link.l1.go = "MarchCap_3_1";
					link.l2 = "Хм. Сдается мне, что эта добыча не только вам в одиночку, но и нам вдвоем не по зубам. Нет, я на такое не подпишусь. Прощайте, сударь, и даже не пытайтесь меня задерживать!";
					link.l2.go = "MarchCap_exit";
				break;
			}
		break;
		
		case "MarchCap_1_1":
			dialog.text = "Я знал, что на вас можно рассчитывать! Тогда не будем терять ни минуты. Отправляйтесь на ваш корабль и становитесь впереди. Выходим в море!";
			link.l1 = "Приказывайте поднимать якоря, капитан! Мы отправляемся немедленно.";
			link.l1.go = "MarchCap_1_2";
		break;
		
		case "MarchCap_1_2":
			DialogExit();
			NextDiag.CurrentNode = "MarchCap_repeat";
			Group_DelCharacter("MarchGroup", "MarchCap");
			SetCompanionIndex(pchar, -1, sti(npchar.index));
			npchar.loyality = MAX_LOYALITY;
			SetCharacterRemovable(npchar, false);
			Character_SetAbordageEnable(npchar, false);
			npchar.Tasks.CanBoarding = false; // запрет идти на абордаж // Addon 2016-1 Jason Пиратская линейка
			pchar.quest.MarchCap1_1.win_condition.l1 = "Timer";
			pchar.quest.MarchCap1_1.win_condition.l1.date.hour  = sti(GetTime()+rand(10));
			pchar.quest.MarchCap1_1.win_condition.l1.date.day   = GetAddingDataDay(0, 0, sti(pchar.GenQuest.MarchCap.DaysQty));
			pchar.quest.MarchCap1_1.win_condition.l1.date.month = GetAddingDataMonth(0, 0, sti(pchar.GenQuest.MarchCap.DaysQty));
			pchar.quest.MarchCap1_1.win_condition.l1.date.year  = GetAddingDataYear(0, 0, sti(pchar.GenQuest.MarchCap.DaysQty));
			pchar.quest.MarchCap1_1.win_condition.l2 = "location";
			pchar.quest.MarchCap1_1.win_condition.l2.location = pchar.GenQuest.MarchCap.Island;
			pchar.quest.MarchCap1_1.function = "MarchCap1_CreateConvoy";
			SetFunctionTimerCondition("MarchCap_Attack_Over", 0, 0, sti(pchar.GenQuest.MarchCap.DaysQty)+2, false); //таймер на нахождение
			pchar.quest.MarchCap1_fail.win_condition.l1 = "NPC_Death";
			pchar.quest.MarchCap1_fail.win_condition.l1.character = "MarchCap";
			pchar.quest.MarchCap1_fail.function = "MarchCap_fail";
			ReOpenQuestHeader("MarchCap");
			AddQuestRecord("MarchCap", "1");
			AddQuestUserData("MarchCap", "sShore", XI_ConvertString(pchar.GenQuest.MarchCap.Island.Shore+"Gen"));
			AddQuestUserData("MarchCap", "sIsland", XI_ConvertString(pchar.GenQuest.MarchCap.Island+"Gen"));
			AddQuestUserData("MarchCap", "sDays", FindRussianDaysString(sti(pchar.GenQuest.MarchCap.DaysQty)));
			AddQuestUserData("MarchCap", "sGoods", GetGoodsNameAlt(sti(pchar.GenQuest.MarchCap.Goods)));
			AddQuestUserData("MarchCap", "sName", GetFullName(npchar));
		break;
		
		case "MarchCap_TimeOver":
			dialog.text = "И зачем я только с вами связался, не подскажете, а, капитан? Из-за вас мы упустили такую богатую добычу! Лучше бы я пошел один...";
			link.l1 = "Из-за меня? Да вы на себя и свою лоханку посмотрите! Что вы сделали для общего дела? Плелись, как краб по отмели? Я только и делал, что ждал, пока вы подтянетесь! Прощайте!";
			link.l1.go = "MarchCap_Talk_exit";
			pchar.GenQuest.MarchCap = "late";
		break;
		
		case "MarchCap_Talk_exit":
			pchar.quest.MarchCap1_fail2.over = "yes"; //снять прерывание
			pchar.quest.MarchCap1_fail1.over = "yes"; //снять прерывание
			pchar.quest.MarchCap1_fail.over = "yes"; //снять прерывание
			DialogExit();
			npchar.lifeday = 0;
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", 10.0);
			DeleteAttribute(npchar, "AlwaysFriend");
			npchar.DontDeskTalk = true;
			if (CheckAttribute(pchar, "GenQuest.MarchCap.Deck"))
			{
				PChar.quest.Munity = "Deads";
				LAi_LocationFightDisable(&Locations[FindLocation("Ship_deck")], false);
			}
			else
			{
				LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
				chrDisableReloadToLocation = false;
			}
			RemoveCharacterCompanion(pchar, npchar);
			if (pchar.GenQuest.MarchCap == "late") AddQuestRecord("MarchCap", "2");
			if (pchar.GenQuest.MarchCap == "bad") AddQuestRecord("MarchCap", "5");
			if (pchar.GenQuest.MarchCap == "poor" || pchar.GenQuest.MarchCap == "good" || pchar.GenQuest.MarchCap == "exellent")
			{
				iQty = makeint(GetSquadronGoods(pchar, sti(pchar.GenQuest.MarchCap.Goods))-sti(pchar.GenQuest.MarchCap.StartGoodsQty));
				iTemp = iQty-sti(pchar.GenQuest.MarchCap.CapPart);
				RemoveCharacterGoods(pchar, sti(pchar.GenQuest.MarchCap.Goods), iQty);
				AddCharacterGoods(pchar, sti(pchar.GenQuest.MarchCap.Goods), iTemp);
				if (pchar.GenQuest.MarchCap == "poor") AddQuestRecord("MarchCap", "6");
				if (pchar.GenQuest.MarchCap == "good") AddQuestRecord("MarchCap", "7");
				if (pchar.GenQuest.MarchCap == "exellent") AddQuestRecord("MarchCap", "8");
			}
			AddQuestUserData("MarchCap", "sName", GetFullName(npchar));
			CloseQuestHeader("MarchCap");
			DeleteAttribute(pchar, "GenQuest.MarchCap");
		break;
		
		case "MarchCap_AfterBattle":
			iTemp = makeint(GetSquadronGoods(pchar, sti(pchar.GenQuest.MarchCap.Goods))-sti(pchar.GenQuest.MarchCap.StartGoodsQty))*sti(Goods[sti(pchar.GenQuest.MarchCap.Goods)].Weight);
			iQty = makeint(GetSquadronGoods(pchar, sti(pchar.GenQuest.MarchCap.Goods))-sti(pchar.GenQuest.MarchCap.StartGoodsQty));
			pchar.GenQuest.MarchCap.CapPart = iQty/sti(pchar.GenQuest.MarchCap.Parts);
			if (iTemp < 50)
			{
				dialog.text = "Какой же вы неумеха, капитан! Мы ничего не захватили, вообще, ни-че-го!! А все из-за вас! Это вы во всем виноваты, разрази вас гром!";
				link.l1 = "Из-за меня? Да на себя посмотрите! Вы ничем мне не помогли в бою, ничем! Я только зря потратил время, связавшись с вами... Убирайтесь с моего корабля!";
				link.l1.go = "MarchCap_Talk_exit";
				pchar.GenQuest.MarchCap = "bad";
				break;
			}
			if (iTemp > 50 && iTemp < 500)
			{
				dialog.text = "Да уж, неудачный вышел рейд. Захватили какие-то жалкие крохи... Ладно, кэп, делим то, что есть, и расходимся в разные стороны.";
				link.l1 = "Если бы вы мне помогали, как следует, а не бакланов в небе считали, рейд был бы удачным... Забирайте свою долю - "+FindRussianQtyString(sti(pchar.GenQuest.MarchCap.CapPart))+", и проваливайте!";
				link.l1.go = "MarchCap_Talk_exit";
				pchar.GenQuest.MarchCap = "poor";
				break;
			}
			if (iTemp > 500 && iTemp < 1500)
			{
				dialog.text = "Неплохо сработали, капитан! Как я вам и говорил - мы без труда опустошим трюмы этих торгашей, хе-хе... Добыча, как я вижу, составила "+FindRussianQtyString(iQty)+" товара. Моя доля - "+FindRussianQtyString(sti(pchar.GenQuest.MarchCap.CapPart))+".";
				link.l1 = "Вы все верно подсчитали, "+npchar.name+". У меня нет возражений. Шлюпки уже грузятся. Возможно, еще когда-нибудь встретимся с вами...";
				link.l1.go = "MarchCap_Talk_exit";
				pchar.GenQuest.MarchCap = "good";
				break;
			}
			dialog.text = "Отличная работа, капитан! Как я вам и говорил - мы без труда опустошим трюмы этих торгашей, хе-хе... Добыча превзошла все мои ожидания и, как я вижу, составила "+FindRussianQtyString(iQty)+" товара. Моя доля - "+FindRussianQtyString(sti(pchar.GenQuest.MarchCap.CapPart))+".";
			link.l1 = "Вы все верно подсчитали, "+npchar.name+". У меня нет возражений. Шлюпки уже грузятся. Может, еще как-нибудь сходим в совместный рейд, а? Вы мне кажетесь вполне подходящим компаньоном.";
			link.l1.go = "MarchCap_Deck_continue";
			pchar.GenQuest.MarchCap = "exellent";
		break;
		
		//если будет время - здесь создаем еще одного клона с уникальным ИД для продолжения квеста
		case "MarchCap_Deck_continue":
			dialog.text = "Все возможно, капитан. Если подвернется денежное дельце, с которым я не смогу справиться сам - я постараюсь найти вас. Вы мне тоже кажетесь надежным боевым товарищем.";
			link.l1 = "Вот и славно! Ну, а теперь - прощайте, капитан. Удачи!";
			link.l1.go = "MarchCap_Talk_exit";
		break;
		
		case "MarchCap_2_1":
			dialog.text = "Я знал, что на вас можно рассчитывать! Тогда не будем терять ни минуты. Отправляйтесь на ваш корабль и становитесь впереди. Выходим в море и смотрим в оба!";
			link.l1 = "Приказывайте поднимать якоря, капитан! Мы отправляемся немедленно.";
			link.l1.go = "MarchCap_2_2";
		break;
		
		case "MarchCap_2_2":
			DialogExit();
			NextDiag.CurrentNode = "MarchCap_repeat";
			Group_DelCharacter("MarchGroup", "MarchCap");
			SetCompanionIndex(pchar, -1, sti(npchar.index));
			npchar.loyality = MAX_LOYALITY;
			SetCharacterRemovable(npchar, false);
			Character_SetAbordageEnable(npchar, false);
			npchar.Tasks.CanBoarding = false; // запрет идти на абордаж // Addon 2016-1 Jason Пиратская линейка
			pchar.quest.MarchCap1_1.win_condition.l1 = "Timer";
			pchar.quest.MarchCap1_1.win_condition.l1.date.hour  = sti(GetTime()+rand(10));
			pchar.quest.MarchCap1_1.win_condition.l1.date.day   = GetAddingDataDay(0, 0, sti(pchar.GenQuest.MarchCap.DaysQty));
			pchar.quest.MarchCap1_1.win_condition.l1.date.month = GetAddingDataMonth(0, 0, sti(pchar.GenQuest.MarchCap.DaysQty));
			pchar.quest.MarchCap1_1.win_condition.l1.date.year  = GetAddingDataYear(0, 0, sti(pchar.GenQuest.MarchCap.DaysQty));
			pchar.quest.MarchCap1_1.function = "MarchCap2_CreateConvoy";
			pchar.GenQuest.MarchCap.WdmEnc = "true";
			pchar.quest.MarchCap1_fail.win_condition.l1 = "NPC_Death";
			pchar.quest.MarchCap1_fail.win_condition.l1.character = "MarchCap";
			pchar.quest.MarchCap1_fail.function = "MarchCap_fail";
			ReOpenQuestHeader("MarchCap");
			AddQuestRecord("MarchCap", "10");
			AddQuestUserData("MarchCap", "sCity1", XI_ConvertString("Colony"+pchar.GenQuest.MarchCap.Startcity+"Gen"));
			AddQuestUserData("MarchCap", "sCity2", XI_ConvertString("Colony"+pchar.GenQuest.MarchCap.Finishcity+"Acc"));
			AddQuestUserData("MarchCap", "sDays", FindRussianDaysString(sti(pchar.GenQuest.MarchCap.DaysQty)));
			AddQuestUserData("MarchCap", "sGoods", GetGoodsNameAlt(sti(pchar.GenQuest.MarchCap.Goods)));
			AddQuestUserData("MarchCap", "sName", GetFullName(npchar));
		break;
		
		case "MarchCap_3_1":
			dialog.text = "Я знал, что на вас можно рассчитывать! Тогда не будем терять ни минуты - у нас едва хватает времени, чтобы успеть. Отправляйтесь на ваш корабль и становитесь впереди. Выходим в море!";
			link.l1 = "Приказывайте поднимать якоря, капитан! Мы отправляемся немедленно.";
			link.l1.go = "MarchCap_3_2";
		break;
		
		case "MarchCap_3_2":
			DialogExit();
			NextDiag.CurrentNode = "MarchCap_repeat";
			Group_DelCharacter("MarchGroup", "MarchCap");
			SetCompanionIndex(pchar, -1, sti(npchar.index));
			npchar.loyality = MAX_LOYALITY;
			SetCharacterRemovable(npchar, false);
			Character_SetAbordageEnable(npchar, false);
			npchar.Tasks.CanBoarding = false; // запрет идти на абордаж // Addon 2016-1 Jason Пиратская линейка
			pchar.quest.MarchCap1_1.win_condition.l1 = "location";
			pchar.quest.MarchCap1_1.win_condition.l1.location = pchar.GenQuest.MarchCap.Island;
			pchar.quest.MarchCap1_1.function = "MarchCap3_CreatePirate";
			SetFunctionTimerCondition("MarchCap_Attack_Over", 0, 0, sti(pchar.GenQuest.MarchCap.DaysQty), false); //таймер
			pchar.quest.MarchCap1_fail.win_condition.l1 = "NPC_Death";
			pchar.quest.MarchCap1_fail.win_condition.l1.character = "MarchCap";
			pchar.quest.MarchCap1_fail.function = "MarchCap_fail";
			pchar.GenQuest.MarchCap.Pirate = "true";
			ReOpenQuestHeader("MarchCap");
			AddQuestRecord("MarchCap", "11");
			AddQuestUserData("MarchCap", "sShore", XI_ConvertString(pchar.GenQuest.MarchCap.Island.Shore+"Gen"));
			AddQuestUserData("MarchCap", "sIsland", XI_ConvertString(pchar.GenQuest.MarchCap.Island+"Gen"));
			AddQuestUserData("MarchCap", "sDays", FindRussianDaysString(sti(pchar.GenQuest.MarchCap.DaysQty)));
			AddQuestUserData("MarchCap", "sGoods", GetGoodsNameAlt(sti(pchar.GenQuest.MarchCap.Goods)));
			AddQuestUserData("MarchCap", "sName", GetFullName(npchar));
			AddQuestUserData("MarchCap", "sName1", GetName(NAMETYPE_ORIG, pchar.GenQuest.MarchCap.PirateName, NAME_NOM));
		break;
		
		case "MarchCap_DieHard":
			dialog.text = "Вы струсили, черт бы вас побрал! Вы попросту сбежали с поля боя!";
			link.l1 = "А что, по-вашему, я должен был дать этому пирату потопить мое судно? Нет уж, лучше быть живым трусом, чем мертвым идиотом!";
			link.l1.go = "MarchCap_DieHard_1";
		break;
		
		case "MarchCap_DieHard_1":
			dialog.text = "И зачем я только связался с вами? Надо было поискать кого-нибудь другого, у кого не дрожат коленки при виде абордажных сабель!";
			link.l1 = "Идите читать нотации в другом месте, сударь! Мы чуть было не погибли, а вы тут устраиваете разглагольствования! Вас погубит жадность, попомните мое слово! А теперь попрошу вас покинуть мой корабль - я отправляюсь на ремонт.";
			link.l1.go = "MarchCap_Talk_exit";
		break;
		
		case "MarchCap_AfterBattleGold":
			iTemp = makeint(GetSquadronGoods(pchar, sti(pchar.GenQuest.MarchCap.Goods))-sti(pchar.GenQuest.MarchCap.StartGoodsQty))*sti(Goods[sti(pchar.GenQuest.MarchCap.Goods)].Weight);
			iQty = makeint(GetSquadronGoods(pchar, sti(pchar.GenQuest.MarchCap.Goods))-sti(pchar.GenQuest.MarchCap.StartGoodsQty));
			pchar.GenQuest.MarchCap.CapPart = iQty/sti(pchar.GenQuest.MarchCap.Parts);
			if (iTemp < 10)
			{
				dialog.text = "Какой же вы неумеха, капитан! Мы ничего не захватили, вообще, ни-че-го!! А все из-за вас! Это вы во всем виноваты, разрази вас гром!";
				link.l1 = "Из-за меня? Да на себя посмотрите! Вы ничем мне не помогли в бою, ничем! Я только зря потратил время, связавшись с вами... Убирайтесь с моего корабля!";
				link.l1.go = "MarchCap_Talk_exit";
				pchar.GenQuest.MarchCap = "bad";
				break;
			}
			if (iTemp > 10 && iTemp < 100)
			{
				dialog.text = "Да уж, неудачный вышел рейд. Захватили какие-то жалкие крохи... Ладно, кэп, делим то, что есть, и расходимся в разные стороны.";
				link.l1 = "Если бы вы мне помогали, как следует, а не бакланов в небе считали, рейд был бы удачным... Забирайте свою долю - "+FindRussianQtyString(sti(pchar.GenQuest.MarchCap.CapPart))+", и проваливайте!";
				link.l1.go = "MarchCap_Talk_exit";
				pchar.GenQuest.MarchCap = "poor";
				break;
			}
			if (iTemp > 100 && iTemp < 500)
			{
				dialog.text = "Неплохо сработали, капитан! Как я вам и говорил - вдвоем мы справимся с этим пиратом! Добыча, как я вижу, составила "+FindRussianQtyString(iQty)+" товара. Моя доля - "+FindRussianQtyString(sti(pchar.GenQuest.MarchCap.CapPart))+".";
				link.l1 = "Вы все верно подсчитали, "+npchar.name+". У меня нет возражений. Шлюпки уже грузятся. Возможно, еще когда-нибудь встретимся с вами...";
				link.l1.go = "MarchCap_Talk_exit";
				pchar.GenQuest.MarchCap = "good";
				break;
			}
			dialog.text = "Отличная работа, капитан! Как я вам и говорил - вдвоем мы справимся с этим пиратом! Добыча превзошла все мои ожидания и, как я вижу, составила "+FindRussianQtyString(iQty)+" товара. Моя доля - "+FindRussianQtyString(sti(pchar.GenQuest.MarchCap.CapPart))+".";
			link.l1 = "Вы все верно подсчитали, "+npchar.name+". У меня нет возражений. Шлюпки уже грузятся. Может, еще как-нибудь сходим в совместный рейд, а? Вы мне кажетесь вполне подходящим компаньоном.";
			link.l1.go = "MarchCap_Deck_continue";
			pchar.GenQuest.MarchCap = "exellent";
		break;
		
		case "":
			dialog.text = "";
			link.l1 = "";
			link.l1.go = "";
		break;
		
		case "MarchCap_repeat":
			dialog.text = ""+GetAddress_Form(NPChar)+", ступайте на свой корабль. У нас совершенно нет времени на разговоры. В путь!";
			link.l1 = "Да-да, конечно, вы правы.";
			link.l1.go = "exit";
			NextDiag.TempNode = "MarchCap_repeat";
		break;
		
		case "MarchCap_exit":
			dialog.text = "Хм... Да и не собираюсь. Проваливайте ко всем чертям! И без вас управлюсь!";
			link.l1 = "Ну-ну, счастливого пути...";
			link.l1.go = "MarchCap_DeckExit";
		break;
		
		case "MarchCap_DeckExit":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeday = 0;
			DeleteAttribute(npchar, "AlwaysFriend");
			npchar.DontDeskTalk = true;
			DeleteAttribute(pchar, "GenQuest.MarchCap");
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}

int SelectMarchCapGoods1()
{
	int iGoods;
	switch (drand(5))
	{
		case 0: iGoods = GOOD_EBONY; break;
		case 1: iGoods = GOOD_MAHOGANY; break;
		case 2: iGoods = GOOD_CINNAMON; break;
		case 3: iGoods = GOOD_COFFEE; break;
		case 4: iGoods = GOOD_CHOCOLATE; break;
		case 5: iGoods = GOOD_TOBACCO; break;
	}
	return iGoods;
}

int SelectPirateShipType()
{
	int iShip;
	
	if(sti(pchar.rank) >= 19) iShip = SHIP_LINESHIP;	
	if(sti(pchar.rank) >= 13 && sti(pchar.rank) < 18) iShip = SHIP_GALEON_H;	
	if(sti(pchar.rank) >= 8 && sti(pchar.rank) < 12) iShip = SHIP_CORVETTE;
	if(sti(pchar.rank) >= 5 && sti(pchar.rank) < 8) iShip = SHIP_SCHOONER_W;	
	if(sti(pchar.rank) < 5) iShip = SHIP_LUGGER + drand(makeint(SHIP_BRIG - SHIP_LUGGER));
	
	return iShip;
}