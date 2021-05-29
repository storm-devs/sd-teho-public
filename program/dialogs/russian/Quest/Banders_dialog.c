
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "fight":
            LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
            LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "quest_fight":
            LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
            LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
            LAi_group_SetCheck("EnemyFight", "DeliverToBander_Dead");
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;

		case "First time":
			dialog.text = "Ты кто так"+ GetSexPhrase("ой","ая") +"?!";
			link.l1 = "Тихо, шуму не поднимай. Меня прислал твой приятель, что в каземате сидит. " + pchar.questTemp.jailCanMove.Deliver.name + ", знаешь такого?";
			link.l1.go = "Step_1";			
			NextDiag.TempNode = "Second time";
		break;
		
		case "Step_1":
			dialog.text = "Чем докажешь, что ты не из губернаторских ищеек?";
			link.l1 = "Записку просил передать. Вот она.";
			link.l1.go = "Step_2";
			TakeItemFromCharacter(pchar, "Malyava");
		break;
		
		case "Step_2":
			dialog.text = "Так...(читает). Вот чёрт! Надо же ему было так неудачно вляпаться... Эх, такое дело пропадает... Слушай, моря"+ GetSexPhrase("к","чка") +", ты, смотрю, "+ GetSexPhrase("парень неслабый","деваха боевая") +". Не хочешь подзаработать? И ты в выигрыше будешь, и нам перепадёт.";
			link.l1 = "Подзаработать - это я всегда хочу. Что ты предлагаешь?";
			link.l1.go = "Step_3";
		break;
			
		case "Step_3":
			dialog.text = "Могу поделиться информацией. Мне она теперь ни к чему - не успеть уже, а тебе может сгодиться. Только не бесплатно - сам"+ GetSexPhrase("","а") +" понимаешь, это денег стоит. Дело выгодное, поверь.";
			link.l1 = "Сколько ты хочешь?";
			if (drand(2) == 0) link.l1.go = "Step_4";
			else link.l1.go = "Step_4d";
		break;
		
		case "Step_4":
			iTotalTemp = 0;
			dialog.text = "Пятьдесят тысяч песо.";
			if(makeint(Pchar.money) >= 50000)
			{
				link.l1 = "Хм, немало. Но если дело того стоит... соглас"+ GetSexPhrase("ен","на") +". Где наша ни пропадала! О чём пойдёт речь?";
				link.l1.go = "Step_5";
			}
			link.l2 = "Нет. Я не намерен"+ GetSexPhrase("","а") +" платить неизвестно за что. Покупкой котов в мешках я не занимаюсь.";
			link.l2.go = "Step_no";
		break;
		
		case "Step_4d":
			iTotalTemp = 250+drand(25)*10;
			dialog.text = ""+FindRussianDublonString(iTotalTemp)+". И ни монетой меньше!";
			if (GetCharacterItem(pchar, "gold_dublon") >= iTotalTemp)
			{
				link.l1 = "Хм, немало. Но если дело того стоит... соглас"+ GetSexPhrase("ен","на") +". Где наша ни пропадала! О чём пойдёт речь?";
				link.l1.go = "Step_5";
			}
			link.l2 = "Нет. Я не намерен"+ GetSexPhrase("","а") +" платить неизвестно за что. Покупкой котов в мешках я не занимаюсь.";
			link.l2.go = "Step_no";
		break;
		
		case "Step_5":
			switch (sti(pchar.questTemp.jailCanMove.Deliver.good))
			{
				case 0://попытка грабежа
					dialog.text = "Так-так, отлично, "+ GetSexPhrase("повёлся, фраерок","повелась, дуреха") +". Ну-ка, гони сюда свои денежки!";
					link.l1 = "Экий ты наглец... А твой приятель говорил, что друзья у него щедрые.";
					link.l1.go = "Step_fight";
				break;
				
				case 1://кидалово
					if (iTotalTemp == 0) AddMoneyToCharacter(pchar, -50000);
					else RemoveItems(pchar, "gold_dublon", iTotalTemp);
					GetBandersTradeShore();
					GetBandersTradeGoods();
					GetBandersTradeNation();
					pchar.questTemp.jailCanMove.Deliver.terms = 10+rand(2);
					pchar.questTemp.jailCanMove.Deliver.ShipName1 = GenerateRandomNameToShip(sti(pchar.questTemp.jailCanMove.Deliver.Nation));
					pchar.questTemp.jailCanMove.Deliver.ShipName2 = GenerateRandomNameToShip(sti(pchar.questTemp.jailCanMove.Deliver.Nation));
					dialog.text = "Хорошо, слушай. Мне стало достоверно известно, что в ближайшие " + FindRussianDaysString(sti(pchar.questTemp.jailCanMove.Deliver.terms)) + " у берегов "+ pchar.questTemp.jailCanMove.Deliver.Island.Areal +" будут находиться два "+ pchar.questTemp.jailCanMove.Deliver.add1 +" купеческих корабля - '"+ pchar.questTemp.jailCanMove.Deliver.ShipName1 +"' и '"+ pchar.questTemp.jailCanMove.Deliver.ShipName2 +"', с трюмами, полными "+ pchar.questTemp.jailCanMove.Deliver.add +". Можешь попытаться их перехватить.";
					link.l1 = "Отлично! Кажется, я недаром поделил"+ GetSexPhrase("ся","ась") +" с вами деньжатами.";
					link.l1.go = "Step_lay";
				break;
				
				case 2://наведем на торговый корабль
					if (iTotalTemp == 0) AddMoneyToCharacter(pchar, -50000);
					else RemoveItems(pchar, "gold_dublon", iTotalTemp);
					GetBandersTradeShore();
					GetBandersTradeGoods();
					GetBandersTradeNation();
					pchar.questTemp.jailCanMove.Deliver.terms = 10+rand(2);
					pchar.questTemp.jailCanMove.Deliver.ShipName1 = GenerateRandomNameToShip(sti(pchar.questTemp.jailCanMove.Deliver.Nation));
					pchar.questTemp.jailCanMove.Deliver.ShipName2 = GenerateRandomNameToShip(sti(pchar.questTemp.jailCanMove.Deliver.Nation));
					
					dialog.text = "Хорошо, слушай. Мне стало достоверно известно, что в ближайшие " + FindRussianDaysString(sti(pchar.questTemp.jailCanMove.Deliver.terms)) + " у берегов "+ pchar.questTemp.jailCanMove.Deliver.Island.Areal +" будут находиться два "+ pchar.questTemp.jailCanMove.Deliver.add1 +" купеческих корабля - '"+ pchar.questTemp.jailCanMove.Deliver.ShipName1 +"' и '"+ pchar.questTemp.jailCanMove.Deliver.ShipName2 +"', с трюмами, полными "+ pchar.questTemp.jailCanMove.Deliver.add +". Можешь попытаться их перехватить.";
					link.l1 = "Отлично! Кажется, я недаром поделил"+ GetSexPhrase("ся","ась") +" с вами деньжатами.";
					link.l1.go = "Step_trader";
				break;
				
				case 3://наведем на курьерский корабль
					if (iTotalTemp == 0) AddMoneyToCharacter(pchar, -50000);
					else RemoveItems(pchar, "gold_dublon", iTotalTemp);
					GetBandersTradeShore();
					GetBandersTradeNation();
					pchar.questTemp.jailCanMove.Deliver.ShipName = GenerateRandomNameToShip(sti(pchar.questTemp.jailCanMove.Deliver.Nation));
					pchar.questTemp.jailCanMove.Deliver.terms = 5+rand(5);
					dialog.text = "Хорошо, слушай. Мне стало достоверно известно, что в ближайшие " + FindRussianDaysString(sti(pchar.questTemp.jailCanMove.Deliver.terms)) + " у берегов "+ pchar.questTemp.jailCanMove.Deliver.Island.Areal +" будет проходить курьерский корабль "+ pchar.questTemp.jailCanMove.Deliver.add2 +" под названием '"+ pchar.questTemp.jailCanMove.Deliver.ShipName +"'. Он перевозит целую кучу драгоценностей. Можешь попытаться его перехватить.";
					link.l1 = "Отлично! Кажется, я недаром поделил"+ GetSexPhrase("ся","ась") +" с вами деньжатами.";
					link.l1.go = "Step_cureer";
				break;
			}
		break;
			
		case "Step_fight":
			dialog.text = "Если бы он не был таким болваном, то пил бы ром в таверне, а не помои в каземате. Так что все вопросы потом ему и задашь, ха-ха-ха! А теперь деньги на бочку, иначе " + GetSexPhrase("живым","живой") + " отсюда не выйдешь.";
			link.l1 = "Ну, это мы сейчас поглядим, клоун...";
			link.l1.go = "quest_fight";
			link.l2 = "Ладно, забирайте деньги... Сила не на моей стороне.";
			link.l2.go = "Step_takemoney";
		break;
		
		case "Step_takemoney":
			dialog.text = "Вот и "+ GetSexPhrase("молодец","умница") +". А вернёт их тебе наш общий друг... хе-хе, когда откинется. И давай, топай отсюда по-тихому...";
			link.l1 = "Будьте вы прокляты!";
			link.l1.go = "exit";
			if (iTotalTemp == 0) AddMoneyToCharacter(pchar, -50000);
			else RemoveItems(pchar, "gold_dublon", 300);
			AddQuestRecord("GivePrisonFree", "17");
			AddQuestUserData("GivePrisonFree", "sSex", GetSexPhrase("","а"));
			CloseQuestHeader("GivePrisonFree");
			LAi_SetWarriorTypeNoGroup(npchar);
			chrDisableReloadToLocation = false;
			DeleteAttribute(pchar, "questTemp.jailCanMove.Deliver");
		break;
		
		case "Step_lay":
			dialog.text = "Конечно, недаром... Всё, а теперь давай, поторапливайся. И выходи тихонько, внимания не привлекай.";
			link.l1 = "Прощай.";
			link.l1.go = "exit";
			AddQuestRecord("GivePrisonFree", "13");
			AddQuestUserData("GivePrisonFree", "sGoods", pchar.questTemp.jailCanMove.Deliver.add);
			AddQuestUserData("GivePrisonFree", "sDay", FindRussianDaysString(sti(pchar.questTemp.jailCanMove.Deliver.terms)));
			AddQuestUserData("GivePrisonFree", "sShipName1", pchar.questTemp.jailCanMove.Deliver.ShipName1);
			AddQuestUserData("GivePrisonFree", "sShipName2", pchar.questTemp.jailCanMove.Deliver.ShipName2);
			AddQuestUserData("GivePrisonFree", "sShoreName", pchar.questTemp.jailCanMove.Deliver.Island.Areal);
			pchar.quest.jailCanMoveDeliver_ShipsAttack.win_condition.l1 = "location";
            pchar.quest.jailCanMoveDeliver_ShipsAttack.win_condition.l1.location = pchar.questTemp.jailCanMove.Deliver.Island;//отправляем в локацию
            pchar.quest.jailCanMoveDeliver_ShipsAttack.function = "Deliver_lay";//придем - а там пусто
			SetFunctionTimerCondition("Deliver_TraderShipsOver", 0, 0, sti(pchar.questTemp.jailCanMove.Deliver.terms), false);//таймер
			LAi_SetWarriorTypeNoGroup(npchar);
			chrDisableReloadToLocation = false;
		break;
		
		case "Step_trader":
			dialog.text = "Конечно, недаром... Всё, а теперь давай, поторапливайся. И выходи тихонько, внимания не привлекай.";
			link.l1 = "Прощай.";
			link.l1.go = "exit";
			AddQuestRecord("GivePrisonFree", "13");
			AddQuestUserData("GivePrisonFree", "sGoods", pchar.questTemp.jailCanMove.Deliver.add);
			AddQuestUserData("GivePrisonFree", "sDay", FindRussianDaysString(sti(pchar.questTemp.jailCanMove.Deliver.terms)));
			AddQuestUserData("GivePrisonFree", "sShipName1", pchar.questTemp.jailCanMove.Deliver.ShipName1);
			AddQuestUserData("GivePrisonFree", "sShipName2", pchar.questTemp.jailCanMove.Deliver.ShipName2);
			AddQuestUserData("GivePrisonFree", "sShoreName", pchar.questTemp.jailCanMove.Deliver.Island.Areal);
			pchar.quest.jailCanMoveDeliver_ShipsAttack.win_condition.l1 = "location";
            pchar.quest.jailCanMoveDeliver_ShipsAttack.win_condition.l1.location = pchar.questTemp.jailCanMove.Deliver.Island;//отправляем в локацию
            pchar.quest.jailCanMoveDeliver_ShipsAttack.function = "Deliver_CreateTraderShips";//создание кораблей
			SetFunctionTimerCondition("Deliver_TraderShipsOver", 0, 0, sti(pchar.questTemp.jailCanMove.Deliver.terms), false);//таймер
			LAi_SetWarriorTypeNoGroup(npchar);
			chrDisableReloadToLocation = false;
		break;
		
		case "Step_cureer":
			dialog.text = "Конечно, недаром... Всё, а теперь давай, поторапливайся. И выходи тихонько, внимания не привлекай.";
			link.l1 = "Прощай.";
			link.l1.go = "exit";
			AddQuestRecord("GivePrisonFree", "14");
			AddQuestUserData("GivePrisonFree", "sDay", FindRussianDaysString(sti(pchar.questTemp.jailCanMove.Deliver.terms)));
			AddQuestUserData("GivePrisonFree", "sText", pchar.questTemp.jailCanMove.Deliver.add2);
			AddQuestUserData("GivePrisonFree", "sShipName", pchar.questTemp.jailCanMove.Deliver.ShipName);
			AddQuestUserData("GivePrisonFree", "sShoreName", pchar.questTemp.jailCanMove.Deliver.Island.Areal);
			pchar.quest.jailCanMoveDeliver_ShipsCAttack.win_condition.l1 = "location";
            pchar.quest.jailCanMoveDeliver_ShipsCAttack.win_condition.l1.location = pchar.questTemp.jailCanMove.Deliver.Island;//отправляем в локацию
            pchar.quest.jailCanMoveDeliver_ShipsCAttack.function = "Deliver_CreateCureerShips";//создание кораблей
			SetFunctionTimerCondition("Deliver_CureerShipsOver", 0, 0, sti(pchar.questTemp.jailCanMove.Deliver.terms), false);//таймер
			LAi_SetWarriorTypeNoGroup(npchar);
			chrDisableReloadToLocation = false;
		break;
		
		case "Step_no":
			dialog.text = "Ну, как знаешь. Тогда проваливай, не о чем нам с тобой больше трепаться.";
			link.l1 = "Ладно, прощай.";
			link.l1.go = "exit";
			AddQuestRecord("GivePrisonFree", "16");
			AddQuestUserData("GivePrisonFree", "sSex", GetSexPhrase("","а"));
			AddQuestUserData("GivePrisonFree", "sSex1", GetSexPhrase("ся","ась"));
			CloseQuestHeader("GivePrisonFree");
			LAi_SetWarriorTypeNoGroup(npchar);
			chrDisableReloadToLocation = false;
			DeleteAttribute(pchar, "questTemp.jailCanMove.Deliver");
		break;

		case "Second time":
			dialog.text = "Ну чего ещё? Сказано же - вали по-тихому.";
			link.l1 = "Ладно, уже иду...";
			link.l1.go = "exit";			
			NextDiag.TempNode = "Second time";
		break;
		
		case "Man_FackYou":
			dialog.text = "Ты что, " + GetSexPhrase("пижон, сам","дуреха, сама") + " на кинжал лезешь?!";
			link.l1 = LinkRandPhrase("Дьявол!!", "Каррамба!!", "А-ать, чёрт!");
			link.l1.go = "fight";
		break;
	}
}

void GetBandersTradeShore()//выберем остров для торгашей и курьера
{
	pchar.questTemp.jailCanMove.Deliver.Island = GetRandomIslandId();
	pchar.questTemp.jailCanMove.Deliver.Island.Shore = GetIslandRandomShoreId(pchar.questTemp.jailCanMove.Deliver.Island);
	while (pchar.questTemp.jailCanMove.Deliver.Island.Shore == "")
	{
		pchar.questTemp.jailCanMove.Deliver.Island = GetRandomIslandId();
		pchar.questTemp.jailCanMove.Deliver.Island.Shore = GetIslandRandomShoreId(pchar.questTemp.jailCanMove.Deliver.Island);
		if (!isLocationFreeForQuests(pchar.questTemp.jailCanMove.Deliver.Island)) pchar.questTemp.jailCanMove.Deliver.Island.Shore = "";
	} 
	pchar.questTemp.jailCanMove.Deliver.Island.Town = FindTownOnIsland(pchar.questTemp.jailCanMove.Deliver.Island);
	if (pchar.questTemp.jailCanMove.Deliver.Island.Town == "" || pchar.questTemp.jailCanMove.Deliver.Island.Town == "Caiman" || pchar.questTemp.jailCanMove.Deliver.Island.Town == "Terks" || pchar.questTemp.jailCanMove.Deliver.Island.Town == "Dominica")
	{
		pchar.questTemp.jailCanMove.Deliver.Island.Areal = GetConvertStr(pchar.questTemp.jailCanMove.Deliver.Island, "LocLables.txt") + "");
	}
	else
	{
		pchar.questTemp.jailCanMove.Deliver.Island.Areal = XI_ConvertString("Colony" + pchar.questTemp.jailCanMove.Deliver.Island.Town + "Gen");
	}
}

void GetBandersTradeGoods()//выберем товар для торгашей
{
	switch (rand(6))
	{
		case 0:
			pchar.questTemp.jailCanMove.Deliver.Goods = GOOD_EBONY;
			pchar.questTemp.jailCanMove.Deliver.add = "чёрного дерева";
		break;
		
		case 1:
			pchar.questTemp.jailCanMove.Deliver.Goods = GOOD_MAHOGANY;
			pchar.questTemp.jailCanMove.Deliver.add = "красного дерева";
		break;
		
		case 2:
			pchar.questTemp.jailCanMove.Deliver.Goods = GOOD_CHOCOLATE;
			pchar.questTemp.jailCanMove.Deliver.add = "какао";
		break;
		
		case 3:
			pchar.questTemp.jailCanMove.Deliver.Goods = GOOD_COFFEE;
			pchar.questTemp.jailCanMove.Deliver.add = "кофе";
		break;
		
		case 4:
			pchar.questTemp.jailCanMove.Deliver.Goods = GOOD_CINNAMON;
			pchar.questTemp.jailCanMove.Deliver.add = "корицы";
		break;
		
		case 5:
			pchar.questTemp.jailCanMove.Deliver.Goods = GOOD_FOOD;
			pchar.questTemp.jailCanMove.Deliver.add = "провианта";
		break;
		
		case 6:
			pchar.questTemp.jailCanMove.Deliver.Goods = GOOD_WEAPON;
			pchar.questTemp.jailCanMove.Deliver.add = "оружия";
		break;
	}
}

void GetBandersTradeNation()//выберем нацию торгаша и курьера
{
	switch (rand(3))
	{
		case 0:
			pchar.questTemp.jailCanMove.Deliver.Nation = SPAIN;
			pchar.questTemp.jailCanMove.Deliver.add1 = "испанских";
			pchar.questTemp.jailCanMove.Deliver.add2 = "испанского казначейства";
		break;
		
		case 1:
			pchar.questTemp.jailCanMove.Deliver.Nation = FRANCE;
			pchar.questTemp.jailCanMove.Deliver.add1 = "французских";
			pchar.questTemp.jailCanMove.Deliver.add2 = "французского казначейства";
		break;
		
		case 2:
			pchar.questTemp.jailCanMove.Deliver.Nation = HOLLAND;
			pchar.questTemp.jailCanMove.Deliver.add1 = "голландских";
			pchar.questTemp.jailCanMove.Deliver.add2 = "голландской Вест-Индской торговой Компании";
		break;
		
		case 3:
			pchar.questTemp.jailCanMove.Deliver.Nation = ENGLAND;
			pchar.questTemp.jailCanMove.Deliver.add1 = "английских";
			pchar.questTemp.jailCanMove.Deliver.add2 = "английского казначейства";
			break;
	}
}