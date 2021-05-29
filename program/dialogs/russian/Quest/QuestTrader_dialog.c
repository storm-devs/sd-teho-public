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
		bool ok = CheckFreeSitFront(npchar);
			if(drand(11) > 8 && ok && !CheckAttribute(pchar, "GenQuest.Racing.Go") && !CheckAttribute(npchar, "quest.race") && sti(Pchar.Ship.Type) != SHIP_NOTUSED && 6-sti(RealShips[sti(pchar.ship.type)].Class) > 0)//гонки на гидропланах
			{
				dialog.text = TimeGreeting() + ", "+GetAddress_Form(NPChar) + "! My name is "+ GetFullName(NPChar) + ", I am a captain. I see that you are a captain too. Would you like to join me and have a drink together? My treat.";
				link.l1 = "Why not? I don't mind a few drinks and a company.";
				link.l1.go = "Race_prepare";
				link.l2 = "I am sorry, but I am in a hurry. Next time.";
				link.l2.go = "exit";
				npchar.quest.race = "true";
			}
			else
			{
			//конвой торгового судна
				if(!CheckAttribute(pchar, "GenQuest.Escort.Trader") && !CheckAttribute(npchar, "quest.race") && sti(Pchar.Ship.Type) != SHIP_NOTUSED && !CheckAttribute(npchar, "repeat_work") && 6-sti(RealShips[sti(pchar.ship.type)].Class) > 0 && GetCompanionQuantity(pchar) < 3)
				{
					dialog.text = TimeGreeting() + ", "+GetAddress_Form(NPChar) + "! I am "+ GetFullName(NPChar) + ", a merchant. I take it that you are a captain. How about to make a few thousands pesos?";
					link.l1 = "I am always eager to make some coins. What kind of work are you going to propose me?";
					link.l1.go = "Escort_choice";
					link.l2 = "And what kind of work can the merchant propose, huh? To protect his sieved vessel? I don't help profiteers.";
					link.l2.go = "exit_distress";
					SaveCurrentNpcQuestDateParam(npchar, "repeat_work");
				}
				else
				{
					dialog.text = TimeGreeting() + ", "+GetAddress_Form(NPChar) + "! How are you doing? Need something?";
					link.l1 = TimeGreeting() + ", " + GetAddress_FormToNPC(NPChar) + ". No, I don't. Just wanted to say hi. Have a nice rest!";
					link.l1.go = "exit";
				}
			}
		break;
		
		case "exit_distress":
			DialogExit();
			NextDiag.CurrentNode = "Trader_distress";
		break;
		
		case "Trader_distress":
			dialog.text = "Captain, we've had a talk already, right? You 'don't help profiteers', so what do you want from me now?";
			link.l1 = "Yes, you are right. Fine, just sit on you fat arse and drink your rum. I have to go.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Trader_distress";
		break;
		
		case "Escort_choice"://первые развилки - выбираем между городом, бухтой и необитайкой
			pchar.GenQuest.Escort.Trader.StartCity = GetCurrentTown();//стартовый город
			pchar.GenQuest.Escort.Trader.ShipType = TraderShipType();//тип корабля торговца
			pchar.GenQuest.Escort.Trader.Nation = npchar.nation;//нация торговца
			switch (drand(2))
			{
				case 0://город дружественный
					pchar.GenQuest.Escort.Trader.City = FindFriendCityToMC(false);//целевой город
					pchar.GenQuest.Escort.Trader.DaysQty = GetMaxDaysFromIsland2Island(GetArealByCityName(pchar.GenQuest.Escort.Trader.StartCity), GetArealByCityName(pchar.GenQuest.Escort.Trader.City))+5;//дни
					pchar.GenQuest.Escort.Trader.Money = makeint(sti(pchar.GenQuest.Escort.Trader.DaysQty)*400*ShipFactorMC()+sti(pchar.GenQuest.Escort.Trader.ShipType)*700);//оплата от расстояния и классов кораблей ГГ и неписи
					pchar.GenQuest.Escort.Trader.Type1 = "true";//тип задания
					pchar.GenQuest.Escort.Trader.Chance = rand(1);
					pchar.GenQuest.Escort.Trader.Add = "to "+XI_ConvertString("Colony"+pchar.GenQuest.Escort.Trader.City+"Gen")+"";
					dialog.text = "I'd like to ask you to escort me to "+XI_ConvertString("Colony"+pchar.GenQuest.Escort.Trader.City+"Gen")+" within "+FindRussianDaysString(sti(pchar.GenQuest.Escort.Trader.DaysQty))+". I will pay you "+FindRussianMoneyString(sti(pchar.GenQuest.Escort.Trader.Money))+".";
					link.l1 = "Why not? It is always safer to sail together, I understand. I agree.";
					link.l1.go = "EscortType";
					link.l2 = "I'd be glad to help, but I am heading at the different direction.";
					link.l2.go = "Escort_exit";
				break;
				case 1://бухта
					GetEscortTraderShore();//целевая бухта
					while(pchar.GenQuest.Escort.Trader.City == "Terks" || pchar.GenQuest.Escort.Trader.City == "caiman" || pchar.GenQuest.Escort.Trader.City == "dominica")
					{
						GetEscortTraderShore();
					} // patch-6
					pchar.GenQuest.Escort.Trader.DaysQty = GetMaxDaysFromIsland2Island(GetArealByCityName(pchar.GenQuest.Escort.Trader.StartCity), pchar.GenQuest.Escort.Trader.Island)+5;//дни
					pchar.GenQuest.Escort.Trader.Money = makeint(sti(pchar.GenQuest.Escort.Trader.DaysQty)*400*ShipFactorMC()+sti(pchar.GenQuest.Escort.Trader.ShipType)*700);//оплата
					pchar.GenQuest.Escort.Trader.Type2 = "true";//тип задания
					pchar.GenQuest.Escort.Trader.Chance = rand(2);
					pchar.GenQuest.Escort.Trader.Add = "to "+XI_ConvertString(pchar.GenQuest.Escort.Trader.Shore+"Gen")+", not far from "+XI_ConvertString("Colony"+pchar.GenQuest.Escort.Trader.City+"Gen")+"";
					dialog.text = "I'd like to ask you to escort me to "+XI_ConvertString(pchar.GenQuest.Escort.Trader.Shore+"Gen")+", not far from "+XI_ConvertString("Colony"+pchar.GenQuest.Escort.Trader.City+"Gen")+" within "+FindRussianDaysString(sti(pchar.GenQuest.Escort.Trader.DaysQty))+". I will pay you "+FindRussianMoneyString(sti(pchar.GenQuest.Escort.Trader.Money))+".";
					link.l1 = "Why not? It is always safer to sail together, I understand. I agree.";
					link.l1.go = "EscortType";
					link.l2 = "I'd be glad to help, but I am heading at the different direction.";
					link.l2.go = "Escort_exit";
				break;
				case 2://необитайка
					pchar.GenQuest.Escort.Trader.Island = DesIsland();//целевой остров
					pchar.GenQuest.Escort.Trader.Shore = SelectQuestShoreLocationFromSea(pchar.GenQuest.Escort.Trader.Island);//и бухта на нем
					pchar.GenQuest.Escort.Trader.DaysQty = GetMaxDaysFromIsland2Island(GetArealByCityName(pchar.GenQuest.Escort.Trader.StartCity), pchar.GenQuest.Escort.Trader.Island)+5;//дни
					pchar.GenQuest.Escort.Trader.Money = makeint(sti(pchar.GenQuest.Escort.Trader.DaysQty)*400*ShipFactorMC()+sti(pchar.GenQuest.Escort.Trader.ShipType)*700);//оплата
					pchar.GenQuest.Escort.Trader.Type3 = "true";//тип задания
					pchar.GenQuest.Escort.Trader.Chance = rand(2);
					pchar.GenQuest.Escort.Trader.Add = "to "+XI_ConvertString(pchar.GenQuest.Escort.Trader.Shore+"Gen")+" of inhabitant island "+XI_ConvertString(pchar.GenQuest.Escort.Trader.Island)+"";
					dialog.text = "I'd like to ask you to escort me to "+XI_ConvertString(pchar.GenQuest.Escort.Trader.Shore+"Gen")+" which is at "+XI_ConvertString(pchar.GenQuest.Escort.Trader.Island)+", for "+FindRussianDaysString(sti(pchar.GenQuest.Escort.Trader.DaysQty))+". I will pay you "+FindRussianMoneyString(sti(pchar.GenQuest.Escort.Trader.Money))+".";
					link.l1 = "Why not? It is always safer to sail together, I understand. I agree. But I have never heard about shops and trading posts there.";
					link.l1.go = "EscortType";
					link.l2 = "I'd be glad to help but I am heading at the different direction.";
					link.l2.go = "Escort_exit";
				break;
			}
		break;
		
		case "Escort_exit":
			DialogExit();
			DeleteAttribute(pchar, "GenQuest.Escort.Trader");
		break;
		
		case "Trader_wait":
			dialog.text = "Are you ready to sail, captain? I am waiting for your orders.";
			link.l1 = "Yes, we are going to set sail now. See you at the port.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Trader_wait";
		break;
		
		case "EscortType":
			dialog.text = "Splendid! I am glad that we had a deal. I hope that our trip will be safe.";
			link.l1 = "So do I. It is time to set sail!";
			link.l1.go = "EscortType_go";
			NextDiag.CurrentNode = "Trader_wait";
		break;
		
		case "EscortType_go":
			//общие параметры
			DialogExit();
			pchar.GenQuest.Escort.Trader.id = npchar.id;
			CreateTraderShipAndAdd(npchar);//присоединяем торговца
			pchar.GenQuest.Escort.Trader.ShipMaxHP = sti(npchar.ship.HP);
			ReOpenQuestHeader("TraderEscort");
			AddQuestRecord("TraderEscort", "1");
			AddQuestUserData("TraderEscort", "sDay", FindRussianDaysString(sti(pchar.GenQuest.Escort.Trader.DaysQty)));
			AddQuestUserData("TraderEscort", "sMoney", FindRussianMoneyString(sti(pchar.GenQuest.Escort.Trader.Money)));
			AddQuestUserData("TraderEscort", "sStartCity", XI_ConvertString("Colony"+pchar.GenQuest.Escort.Trader.StartCity+"Gen"));
			AddQuestUserData("TraderEscort", "sAdd", pchar.GenQuest.Escort.Trader.Add);
			pchar.GenQuest.Escort.Trader = "begin";
			//различные параметры
			if (CheckAttribute(pchar, "GenQuest.Escort.Trader.Type1"))//в дружественный город
			{
				pchar.GenQuest.Escort.Trader.Location = pchar.GenQuest.Escort.Trader.City+"_tavern";
			if (sti(pchar.GenQuest.Escort.Trader.Chance) == 1) CoolTraderHunterOnMap();
				else TraderHunterOnMap();//запуск ДУ на глобалке
			}
			if (CheckAttribute(pchar, "GenQuest.Escort.Trader.Type2"))//в бухту
			{
				pchar.GenQuest.Escort.Trader.Location = pchar.GenQuest.Escort.Trader.Shore;
				if (sti(pchar.GenQuest.Escort.Trader.Chance) != 2) TraderHunterOnMap();
				else
				{
					pchar.quest.EscortTrader_Attack.win_condition.l1 = "location";
					pchar.quest.EscortTrader_Attack.win_condition.l1.location = pchar.GenQuest.Escort.Trader.Island;
					pchar.quest.EscortTrader_Attack.function = "EscortTraderAttackInShore";
				}
			}
			if (CheckAttribute(pchar, "GenQuest.Escort.Trader.Type3"))//на необитайку
			{
				pchar.GenQuest.Escort.Trader.Location = pchar.GenQuest.Escort.Trader.Shore;
				if (sti(pchar.GenQuest.Escort.Trader.Chance) == 0) TraderHunterOnMap();
				if (sti(pchar.GenQuest.Escort.Trader.Chance) == 1) 
				{
					if(sti(RealShips[sti(pchar.Ship.Type)].BaseType) <= sti(pchar.GenQuest.Escort.Trader.ShipType) && sti(RealShips[sti(pchar.Ship.Type)].BaseType) != SHIP_GALEON_H && GetCompanionQuantity(pchar) < 3)//меряемся кораблями
					{//нападет сам
						pchar.quest.EscortTrader_Attack.win_condition.l1 = "location";
						pchar.quest.EscortTrader_Attack.win_condition.l1.location = pchar.GenQuest.Escort.Trader.Island;
						pchar.quest.EscortTrader_Attack.function = "DesIslandAttack";
					}
					else CoolTraderHunterOnMap();
				}
				else
				{//будет засада + сам нападет
					pchar.quest.EscortTrader_Attack.win_condition.l1 = "location";
					pchar.quest.EscortTrader_Attack.win_condition.l1.location = pchar.GenQuest.Escort.Trader.Island;
					pchar.quest.EscortTrader_Attack.function = "DesIslandAttack";
				}
			}
			pchar.quest.EscortTrader_Complete.win_condition.l1 = "location";
			pchar.quest.EscortTrader_Complete.win_condition.l1.location = pchar.GenQuest.Escort.Trader.Location;
			pchar.quest.EscortTrader_Complete.function = "EscortTraderComplete";
			SetFunctionTimerCondition("EscortTrader_Over", 0, 0, sti(pchar.GenQuest.Escort.Trader.DaysQty), false);
			pchar.quest.EscortTrader_fail.win_condition.l1 = "NPC_Death";//прерывание на потопление сопровождаемого
			pchar.quest.EscortTrader_fail.win_condition.l1.character = pchar.GenQuest.Escort.Trader.id;
			pchar.quest.EscortTrader_fail.function = "EscortTrader_failed";
		break;
		
		case "EscortTrader_complete"://сдаем квест
			sld = characterFromId(pchar.GenQuest.Escort.Trader.id);
			if (sti(sld.ship.HP) < makeint(sti(pchar.GenQuest.Escort.Trader.ShipMaxHP)/4))//если корпуса осталось меньше 1/4 - первая проверка
			{
				dialog.text = "Captain, tell me why have I hired you? Look at my ship! What does she look like? She is ruined! She is barely keeping above the water. Can't you see that? I don't get it - who was escorting who? Anyway, you won't get any reward, forget about it.";
				link.l1 = "Hm... If it wasn't for me you'd be feeding crabs, you stupid merchant. Fine, the world is small and I will meet you someday in the open sea!";
				link.l1.go = "EscortTrader_complete_1";
				break;
			}
			if (sti(sld.ship.HP) < makeint(sti(pchar.GenQuest.Escort.Trader.ShipMaxHP)/2))//если корпуса осталось меньше 1/2 - вторая проверка
			{
				pchar.GenQuest.Escort.Trader.Money = makeint(sti(pchar.GenQuest.Escort.Trader.Money))/2;
				dialog.text = "Captain, tell me why have I hired you? Look at my ship! What does she look like? She is ruined! She is barely keeping above the water.. Can't you see that? Anyway, I will pay you only half of your reward. Don't count on getting more!";
				link.l1 = "Hm... Fine, I agree. Your ship is really... a bit damaged...";
				link.l1.go = "EscortTrader_complete_2";
				break;
			}
			if (CheckAttribute(pchar, "GenQuest.Escort.Trader.Type2") && sti(pchar.GenQuest.Escort.Trader.Chance) == 1)//вместо денег - наводка
			{
				dialog.text = "Captain, you see... I don't have money to pay you for you job. But don't worry please, I want to offer you another kind of payment which is much bigger than I have promised you before!";
				link.l1 = "Hm... Actually I was expecting to get coins right now. But I am all ears if that is a case.";
				link.l1.go = "EscortTrader_complete_4";
				break;
			}
			dialog.text = "Thank you very much, captain. It was safe sailing with you despite all dangers. Here, take your reward.";
			link.l1 = "You are welcome... I just did my job.";
			link.l1.go = "EscortTrader_complete_3";
		break;
		
		case "EscortTrader_complete_1":
			dialog.text = "Don't try to scare me! Your battle skills make your threats pathetic. Farewell!";
			link.l1 = "Get lost, profiteer...";
			link.l1.go = "complete_exit";
			AddQuestRecord("TraderEscort", "4");
			AddComplexSeaExpToScill(20, 20, 20, 0, 20, 0, 0);
			AddCharacterExpToSkill(pchar, "Fortune", 20);//везение
		break;
		
		case "EscortTrader_complete_2":
			dialog.text = "Yes, a very wise observation... Here, take your "+FindRussianMoneyString(sti(pchar.GenQuest.Escort.Trader.Money))+" and farewell.";
			link.l1 = "See you, " + npchar.name + ".";
			link.l1.go = "complete_exit";
			AddMoneyToCharacter(pchar, sti(pchar.GenQuest.Escort.Trader.Money));
			AddQuestRecord("TraderEscort", "5");
			AddQuestUserData("TraderEscort", "sMoney", FindRussianMoneyString(sti(pchar.GenQuest.Escort.Trader.Money)));
			AddComplexSeaExpToScill(50, 50, 50, 0, 50, 0, 50);
			AddCharacterExpToSkill(pchar, "Fortune", 40);//везение
		break;
		
		case "EscortTrader_complete_3":
			dialog.text = "You did great! Well I have to go now. Goodbye, captain!";
			link.l1 = "Good luck, " + npchar.name + "!";
			link.l1.go = "complete_exit";
			AddMoneyToCharacter(pchar, sti(pchar.GenQuest.Escort.Trader.Money));
			AddQuestRecord("TraderEscort", "6");
			AddQuestUserData("TraderEscort", "sMoney", FindRussianMoneyString(sti(pchar.GenQuest.Escort.Trader.Money)));
			AddComplexSeaExpToScill(100, 100, 100, 50, 100, 100, 150);
			AddCharacterExpToSkill(pchar, "Leadership", 80);//авторитет
			AddCharacterExpToSkill(pchar, "Fortune", 80);//везение
			AddCharacterExpToSkill(pchar, "Sneak", 50);//скрытность
		break;
		
		case "EscortTrader_complete_4":
			pchar.GenQuest.Escort.Trader.Enemyname = GenerateRandomName_Generator(sti(npchar.nation), "man");
			GetEnemyTraderGoods();
			pchar.GenQuest.Escort.Trader.EnIsland = DesIsland();
			dialog.text = "There is one merchant - "+ pchar.GenQuest.Escort.Trader.Enemyname +". He owns and commands a flute. I was informed that in two weeks he will arrive to the inhabitant island "+ XI_ConvertString(pchar.GenQuest.Escort.Trader.EnIsland) +", in order to restore his water supplies and to trade with the local Indians. He will have a lot of "+pchar.GenQuest.Escort.Trader.add+" aboard. A pathetic fighter, you won't face any troubles taking his ship\nSo you will benefit from it anyway, captain.";
			link.l1 = "Homo homini lupus est?";
			link.l1.go = "EscortTrader_complete_5";
		break;
		
		case "EscortTrader_complete_5":
			dialog.text = "What?";
			link.l1 = "You are 'giving away' you colleague in such an easy and honest manner... But I don't care about your conscience and thanks for your information. Good luck, sir!";
			link.l1.go = "EscortTrader_complete_6";
		break;
		
		case "EscortTrader_complete_6":
			DialogExit();
			chrDisableReloadToLocation = false;
			bDisableFastReload = false;
			pchar.quest.EscortTrader_fail.over = "yes";
			pchar.quest.EscortTrader_Over.over = "yes";//снять оба прерывания
			npchar.lifeday = 0;
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "", 20.0);
			RemoveCharacterCompanion(Pchar, npchar);
			AddQuestRecord("TraderEscort", "7");
			AddQuestUserData("TraderEscort", "sIsland", XI_ConvertString(pchar.GenQuest.Escort.Trader.EnIsland));
			AddQuestUserData("TraderEscort", "sAdd", pchar.GenQuest.Escort.Trader.add);
			pchar.quest.EscortTrader_EnTrader.win_condition.l1 = "Timer";
			pchar.quest.EscortTrader_EnTrader.win_condition.l1.date.hour  = sti(GetTime());
			pchar.quest.EscortTrader_EnTrader.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 12);
			pchar.quest.EscortTrader_EnTrader.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 12);
			pchar.quest.EscortTrader_EnTrader.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 12);
			pchar.quest.EscortTrader_EnTrader.win_condition.l2 = "location";
			pchar.quest.EscortTrader_EnTrader.win_condition.l2.location = pchar.GenQuest.Escort.Trader.EnIsland;
			pchar.quest.EscortTrader_EnTrader.function = "Create_EnemyTraderFleut";
			SetFunctionTimerCondition("EscortTraderEnemy_Over", 0, 0, 16, false); // таймер
			AddComplexSeaExpToScill(100, 100, 100, 50, 100, 100, 150);
			AddCharacterExpToSkill(pchar, "Leadership", 80);//авторитет
			AddCharacterExpToSkill(pchar, "Fortune", 80);//везение
			AddCharacterExpToSkill(pchar, "Sneak", 50);//скрытность
		break;
		
		case "complete_exit":
			DialogExit();
			CloseQuestHeader("TraderEscort");
			chrDisableReloadToLocation = false;
			bDisableFastReload = false;
			pchar.quest.EscortTrader_fail.over = "yes";
			pchar.quest.EscortTrader_Over.over = "yes";//снять оба прерывания
			pchar.quest.EscortTrader_Attack.over = "yes"; // patch-8
			npchar.lifeday = 0;
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "", 20.0);
			RemoveCharacterCompanion(Pchar, npchar);
			DeleteAttribute(pchar, "GenQuest.Escort.Trader");
		break;
		
		case "Race_prepare":
			NextDiag.TempNode = "Race_begin";
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			pchar.questTemp.friend_in_tavern = npchar.id;
			AddDialogExitQuest("alc");
		break;
		
		case "exit_sit":
			NextDiag.CurrentNode = "First time";
			DialogExit();
			AddDialogExitQuest("exit_sit");
		break;
		
		case "Race_begin"://гонки на гидропланах
			dialog.text = "Eh, let's drink some old good rum, captain! How are you doing, how is your trade?";
			link.l1 = "I am not really a merchant. But I am doing just fine.";
			link.l1.go = "Race_begin_1";
		break;
		
		case "Race_begin_1":
			dialog.text = "And that's the most important! Considering that unsafe situation in the open sea.";
			link.l1 = "Yes, you are right. Especially for you, merchants, there are a lot of hunters for your cargo. And you are rarely able neither to flee nor to fight back. Your vessels are slow and your cannons are small, since you put your profits first. Sailing in convoys with four or five ships together, that is what saves you.";
			link.l1.go = "Race_begin_2";
		break;
		
		case "Race_begin_2":
			dialog.text = "Well, not all of us are like that, friend. I always sail alone, I don't need any ballast. I perfectly know the Caribbean sea and might I say, I am really good in navigating, sailing and commanding my men. I am able to outrun any pirate.";
			link.l1 = "Really? I can hardly believe that. With a full stored cargo? On the trade vessel? So do you mean that you can escape from a pirate brigantine or a lugger?";
			link.l1.go = "Race_begin_3";
		break;
		
		case "Race_begin_3":
			dialog.text = "It looks like you, pal, are doubting that my ship is able to sail fast? Fine. I offer you a bet.";
			link.l1 = "What kind of a bet?";
			link.l1.go = "Race_begin_4";
		break;
		
		case "Race_begin_4"://тут устанавливаем все параметры
			if (!CheckAttribute(pchar, "GenQuest.Racing")) pchar.GenQuest.Racing.Count = 0;
			pchar.GenQuest.Racing.Go.Nation = npchar.nation;
			pchar.GenQuest.Racing.Go.StartCity = GetCurrentTown();
			pchar.GenQuest.Racing.Go.City = FindFriendCityToMC(false);//целевой дружественный город
			pchar.GenQuest.Racing.Go.Island = GetIslandByCityName(pchar.GenQuest.Racing.Go.City);
			pchar.GenQuest.Racing.Go.DaysQty = makeint((GetMaxDaysFromIsland2Island(GetArealByCityName(pchar.GenQuest.Racing.Go.StartCity), GetArealByCityName(pchar.GenQuest.Racing.Go.City)))/1.3);//дни
			pchar.GenQuest.Racing.Go.ShipName = GenerateRandomNameToShip(sti(npchar.nation));
			if (sti(pchar.GenQuest.Racing.Go.DaysQty) < 1) pchar.GenQuest.Racing.Go.DaysQty = 1; // patch-8
			dialog.text = "Listen. I am going to set sail today to "+XI_ConvertString("Colony"+pchar.GenQuest.Racing.Go.City)+". And I say that I will be there in "+FindRussianDaysString(pchar.GenQuest.Racing.Go.DaysQty)+". Try to outrun me and get to "+XI_ConvertString("Colony"+pchar.GenQuest.Racing.Go.City)+" sooner. The time starts to tick now. Want to risk? Or is it too tough for you?";
			link.l1 = "For who? For me? Don't be that funny. Are you going to make it in that time? Ridiculous. I accept your bet. How much are you ready to loose?";
			link.l1.go = "Race_begin_5";
			link.l2 = "I am too busy to start a race because of some silly boasting.";
			link.l2.go = "Race_exit";
		break;
		
		case "Race_exit":
			dialog.text = "Hm... Are you afraid to loose? Whatever. But don't be so quick to judge other people, there are a lot of experienced sailors among merchants... much more experienced than you are.";
			link.l1 = "Fine, fine, don't sermonize me, philosopher. Farewell...";
			link.l1.go = "exit_sit";
			DeleteAttribute(pchar, "GenQuest.Racing.Go");
			NextDiag.TempNode = "First time";
		break;
		
		case "Race_begin_5":
			dialog.text = "It is your choice, captain.";
			iTemp = 1;
			for (i=5; i>=1; i--)
			{
					sTemp = "l"+iTemp;
					link.(sTemp) = ""+FindRussianMoneyString(sti(10000*i))+"";
					link.(sTemp).go = "Racing_rate"+i;
					iTemp++;
			}
		break;
		
		case "Racing_rate5"://50 000
			if (drand(9) > 6)
			{
			dialog.text = "Fine. I agree. Your coins please. Here is my bet.";
			link.l1 = "Just let me to get my purse...";
			link.l1.go = "Racing_rate";
			pchar.GenQuest.Racing.Go.Money = 50000;
			}
			else
			{
			dialog.text = "What a senseless offer, captain? You can buy a schooner for that much money and drink rum for a whole month. Speak the reasonable sum.";
			link.l1 = "This sum looks reasonable for me and I am not going to waste my time with you for the less. We are not beggars to bet for a few pesos. Fine... we have had a sit, enough now. If you fear to bet, It is your choice... Boasting is cheap.";
			link.l1.go = "Race_exit";
			link.l2 = "Really? Fine. Let me think...";
			link.l2.go = "Race_begin_5";
			}
		break;
		
		case "Racing_rate4"://40 000
			if (drand(9) > 4)
			{
			dialog.text = "Fine. I agree. Your coins please. Here is my bet.";
			link.l1 = "Just let me get my purse...";
			link.l1.go = "Racing_rate";
			pchar.GenQuest.Racing.Go.Money = 40000;
			}
			else
			{
			dialog.text = "What a senseless offer, captain? You can buy a barque for that much money and drink rum for a whole month. Speak the reasonable sum.";
			link.l1 = "This sum looks reasonable for me and I am not going to waste my time with you for the less. We are not beggars to bet for a few pesos. Fine... we have had a sit, enough now. If you fear to bet, It is your choice... Boasting is cheap.";
			link.l1.go = "Race_exit";
			link.l2 = "Really? Fine. Let me think...";
			link.l2.go = "Race_begin_5";
			}
		break;
		
		case "Racing_rate3"://30 000
			if (drand(9) > 2)
			{
			dialog.text = "Fine. I agree. Your coins please. Here is my bet.";
			link.l1 = "Just let me get my purse...";
			link.l1.go = "Racing_rate";
			pchar.GenQuest.Racing.Go.Money = 30000;
			}
			else
			{
			dialog.text = "What a senseless offer, captain? You can buy a sloop for that much money and drink rum for a whole month. Speak the reasonable sum.";
			link.l1 = "This sum looks reasonable for me and I am not going to waste my time with you for the less. We are not beggars to bet for a few pesos. Fine... we have had a sit, enough now. If you fear to bet, It is your choice... Boasting is cheap..";
			link.l1.go = "Race_exit";
			link.l2 = "Really? Fine. Let me think...";
			link.l2.go = "Race_begin_5";
			}
		break;
		
		case "Racing_rate2"://20 000
			if (drand(9) > 0)
			{
			dialog.text = "Fine. I agree. Your coins please. Here is my bet.";
			link.l1 = "Just let me get my purse...";
			link.l1.go = "Racing_rate";
			pchar.GenQuest.Racing.Go.Money = 20000;
			}
			else
			{
			dialog.text = "What a senseless offer, captain? You can buy a lugger for that much money and drink rum for a whole month. Speak the reasonable sum.";
			link.l1 = "This sum looks reasonable for me and I am not going to waste my time with you for the less. We are not beggars to bet for a few pesos. Fine... we have had a sit, enough now. If you fear to bet, It is your choice... Boasting is cheap.";
			link.l1.go = "Race_exit";
			link.l2 = "Really? Fine. Let me think...";
			link.l2.go = "Race_begin_5";
			}
		break;
		
		case "Racing_rate1"://10 000
			dialog.text = "Fine. I agree. Your coins please. Here is my bet.";
			link.l1 = "Just let me get my purse...";
			link.l1.go = "Racing_rate";
			pchar.GenQuest.Racing.Go.Money = 10000;
		break;
		
		case "Racing_rate":
			dialog.text = "So?";
			if (sti(pchar.money) >= sti(pchar.GenQuest.Racing.Go.Money))
			{
			link.l1 = "Here!";
			link.l1.go = "Racing_Go";
			}
			else
			{
			link.l1 = "Hm... it looks like I don't have that much.";
			link.l1.go = "Racing_rate_nomoney";
			}
		break;
		
		case "Racing_rate_nomoney":
			if (sti(pchar.GenQuest.Racing.Go.Money) == 10000 || sti(pchar.Money) < 10000)
			{
			dialog.text = "Well, you know we are not some beggars to bet for a few pesos or are you just scared? Fine, hell with you. But don't be so quick to judge other people, there are a lot of experienced sailors among merchants... much more experienced than you are.";
			link.l1 = "Fine, fine, don't sermonize me, philosopher. Farewell...";
			link.l1.go = "exit_sit";
			DeleteAttribute(pchar, "GenQuest.Racing.Go");
			NextDiag.TempNode = "First time";
			}
			else
			{
			dialog.text = "So why don't you check your purse and make a lesser stake?";
			link.l1 = "Fine, I'll try to remember how much coins I have...";
			link.l1.go = "Race_begin_5";
			link.l2 = "I have changed my mind.";
			link.l2.go = "Racing_exit";
			}
		break;
		
		case "Racing_exit":
			dialog.text = "Changed your mind, huh? Aren't you just scared? Fine, hell with you. But don't be so quick to judge other people, there are a lot of experienced sailors among merchants... much more experienced than you are.";
			link.l1 = "Fine, fine, don't sermonize me, philosopher. Farewell...";
			link.l1.go = "exit_sit";
			DeleteAttribute(pchar, "GenQuest.Racing.Go");
			NextDiag.TempNode = "First time";
		break;
		
		case "Racing_Go":
			AddMoneyToCharacter(pchar, -sti(pchar.GenQuest.Racing.Go.Money));
			dialog.text = "We have got a bet then! Let's call a bartender to witness if you don't mind... and let's give our stakes to him. Winner will return and take the whole sum. Cheating is impossible since gossips spread over the archipelago very fast so he will know who is the winner.";
			link.l1 = "I agree. That seems right.";
			link.l1.go = "Racing_Go_1";
		break;
		
		case "Racing_Go_1":
			dialog.text = "Well, I suppose it time for us to get on our ships and set sail, the time is ticking. I don't know about you, but I am going to set sail right now. Oh, and my ship is a flute and her name is "+pchar.GenQuest.Racing.Go.ShipName+". I suppose that you will easily recognize her at the port of arrival.";
			link.l1 = "Don't jump of joy that soon. See you in the tavern of "+XI_ConvertString("Colony"+pchar.GenQuest.Racing.Go.City+"Gen")+"!";
			link.l1.go = "Racing_Go_2";
		break;
		
		case "Racing_Go_2":
			DialogExit();
			npchar.lifeday = 0;
			GetCharacterPos(pchar, &locx, &locy, &locz);
			ChangeCharacterAddressGroup(npchar, pchar.GenQuest.Racing.Go.StartCity + "_tavern", "goto", LAi_FindNearestFreeLocator("goto", locx, locy, locz));
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "exit_sit", -1);
			//работает корректно только через клон :(
			sTemp = npchar.model;
			int iNation = sti(npchar.Nation);
			sld = GetCharacter(NPC_GenerateCharacter("RaceTrader", sTemp, "man", "man", sti(PChar.rank)+5, iNation, -1, true, "quest"));
			sld.name = npchar.name;
			sld.lastname = npchar.lastname;
			sld.Dialog.Filename = "Quest\QuestTrader_dialog.c";
			pchar.quest.Racing_Timer.win_condition.l1 = "Timer";
			pchar.quest.Racing_Timer.win_condition.l1.date.hour  = sti(GetTime()+rand(6));
			pchar.quest.Racing_Timer.win_condition.l1.date.day   = GetAddingDataDay(0, 0, sti(pchar.GenQuest.Racing.Go.DaysQty));
			pchar.quest.Racing_Timer.win_condition.l1.date.month = GetAddingDataMonth(0, 0, sti(pchar.GenQuest.Racing.Go.DaysQty));
			pchar.quest.Racing_Timer.win_condition.l1.date.year  = GetAddingDataYear(0, 0, sti(pchar.GenQuest.Racing.Go.DaysQty));
			pchar.quest.Racing_Timer.function = "TraderRaceInTargetCity";
			pchar.quest.Racing_Finish.win_condition.l1 = "location";
			pchar.quest.Racing_Finish.win_condition.l1.location = pchar.GenQuest.Racing.Go.City + "_town";
			pchar.quest.Racing_Finish.function = "MCRaceInTargetCity";
			SetFunctionTimerCondition("RacingTimeOver", 0, 0, sti(pchar.GenQuest.Racing.Go.DaysQty)+10, false);
			ReOpenQuestHeader("Racing");
			AddQuestRecord("Racing", "1");
			AddQuestUserData("Racing", "sStartCity", XI_ConvertString("Colony"+pchar.GenQuest.Racing.Go.StartCity+"Gen"));
			AddQuestUserData("Racing", "sCity", XI_ConvertString("Colony"+pchar.GenQuest.Racing.Go.City+"Gen"));
			AddQuestUserData("Racing", "sDay", FindRussianDaysString(pchar.GenQuest.Racing.Go.DaysQty));
			AddQuestUserData("Racing", "sMoney", FindRussianMoneyString(sti(pchar.GenQuest.Racing.Go.Money)));
		break;
		
		case "Racing_Finished":
			if (CheckAttribute(pchar, "GenQuest.Racing.Go.MCWin"))
			{
			dialog.text = "Heh! I am surprised actually... Congratulations, captain! You were really faster than me. They say that there is always stronger force for any force, right?";
			link.l1 = "Exactly, sir. But I want to tell you that you are surprisingly experienced and skillful for a captain of the trade ship. Not every merchant is able to sail that way on a flute for such a short time.";
			link.l1.go = "Racing_Finished_1";
			}
			else
			{
			dialog.text = "Well, aren't you surprised, captain? As I said, I perfectly know the sea and sail my ship good enough. See now?";
			link.l1 = "Argh! Incredible! On a flute... that far and for such a small time... Congratulations, captain!";
			link.l1.go = "Racing_Finished_2";
			}
			//bDisableFastReload = false;
			//LocatorReloadEnterDisable(pchar.GenQuest.Racing.Go.City + "_town", "reload1_back", false);
			//LocatorReloadEnterDisable(pchar.GenQuest.Racing.Go.City + "_town", "reload2_back", false);
			//LocatorReloadEnterDisable(pchar.GenQuest.Racing.Go.City + "_town", "gate_back", false);
		break;
		
		case "Racing_Finished_1":
			dialog.text = "Well, you are the winner. Now, you have to return to "+XI_ConvertString("Colony"+pchar.GenQuest.Racing.Go.StartCity)+" and take your money from the bartender. You have surely deserved it!";
			link.l1 = "On my way already. It was a pleasure. Goodbye!";
			link.l1.go = "Racing_end";
			pchar.GenQuest.Racing.Count = sti(pchar.GenQuest.Racing.Count)+1;
			//запустить регату
			if (!CheckAttribute(pchar, "questTemp.RegataGo") && sti(pchar.GenQuest.Racing.Count) == 3)
			{
				pchar.questTemp.RegataGo = "true";
				pchar.questTemp.Regata.CureerCity = FindFriendCityToMC(true);//город, в котором вестовой подойдет
				if (pchar.questTemp.Regata.CureerCity == "PortRoyal") pchar.questTemp.Regata.CureerCity = "SentJons";
				pchar.quest.Regata_Cureer.win_condition.l1 = "location";
				pchar.quest.Regata_Cureer.win_condition.l1.location = pchar.questTemp.Regata.CureerCity+"_town";
				pchar.quest.Regata_Cureer.function = "PrepareToRegata";
				log_testinfo(pchar.questTemp.Regata.CureerCity);
			}
			pchar.GenQuest.Racing.Go.Advantage = "true";
			npchar.lifeday = 0;
			AddCharacterExpToSkill(pchar, "Sailing", 200);//навигация
			AddCharacterExpToSkill(pchar, "Fortune", 200);//везение
			AddCharacterExpToSkill(pchar, "Leadership", 100);//харизма
			ChangeCharacterComplexReputation(pchar,"authority", 3);
			ChangeOfficersLoyality("good_all", 3);
		break;
		
		case "Racing_Finished_2":
			dialog.text = "There is no secret in that just skill and experience. And I have to go to "+XI_ConvertString("Colony"+pchar.GenQuest.Racing.Go.StartCity)+" in order to collect my prize.";
			link.l1 = "You have earned it. Goodbye!";
			link.l1.go = "Racing_end";
			npchar.lifeday = 0;
			DeleteAttribute(pchar, "GenQuest.Racing.Go");
			AddCharacterExpToSkill(pchar, "Sailing", 50);//навигация
			AddCharacterExpToSkill(pchar, "Fortune", 50);//везение
			AddCharacterExpToSkill(pchar, "Leadership", 20);//харизма
			ChangeCharacterComplexReputation(pchar,"authority", 1);
			AddQuestRecord("Racing", "5");
			CloseQuestHeader("Racing");
		break;
		
		case "Racing_end":
			DialogExit();
			NextDiag.currentNode = "Racing_end_repeat";
			pchar.quest.Racing_fail.over = "yes";
			Group_DeleteGroup("RacingTrader");
			sld = characterFromId("RaceTraderSkiper");
			sld.lifeday = 0;
		break;
		
		case "Racing_end_repeat":
			dialog.text = "Is there is anything else you want to talk about?";
			link.l1 = "No, it is nothing.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Racing_end_repeat";
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}

float ShipFactorMC()//коэффициент от класса корабля ГГ
{
	float f;
	int iInvert = 6-sti(RealShips[sti(pchar.Ship.Type)].Class);
	switch (iInvert)
	{
		case 0: f = 0.5 break;
		case 1: f = 1.0 break;
		case 2: f = 1.2 break;
		case 3: f = 1.5 break;
		case 4: f = 2.2 break;
		case 5: f = 3.0 break;
		case 6: f = 4.5 break;
	}
	return f;
}

int TraderShipType()//корабль торговца
{
	int iShipType;
	int iRank = sti(pchar.rank);
	if (iRank < 5) iShipType = SHIP_BARQUE + rand(makeint(SHIP_SCHOONER - SHIP_BARQUE)); 
	if (iRank >= 5 && iRank < 11) iShipType = SHIP_BARKENTINE + rand(makeint(SHIP_FLEUT - SHIP_BARKENTINE));
	if (iRank >= 11 && iRank < 18) iShipType = SHIP_FLEUT + rand(makeint(SHIP_CARAVEL - SHIP_FLEUT));
	if (iRank >= 18 && iRank < 25) iShipType = SHIP_CARAVEL + rand(makeint(SHIP_CARACCA - SHIP_CARAVEL)); 
	if (iRank >= 25) iShipType = SHIP_CARAVEL + rand(makeint(SHIP_NAVIO - SHIP_CARAVEL)); 
	return iShipType;
}

void GetEnemyTraderGoods()//выберем товар
{
switch (rand(7))
	{
		case 0:
			pchar.GenQuest.Escort.Trader.Goods = GOOD_EBONY;
			pchar.GenQuest.Escort.Trader.add = "ebony";
			break;
		case 1:
			pchar.GenQuest.Escort.Trader.Goods = GOOD_MAHOGANY;
			pchar.GenQuest.Escort.Trader.add = "redwood";
			break;
		case 2:
			pchar.GenQuest.Escort.Trader.Goods = GOOD_TOBACCO;
			pchar.GenQuest.Escort.Trader.add = "tobacco";
			break;
		case 3:
			pchar.GenQuest.Escort.Trader.Goods = GOOD_COFFEE;
			pchar.GenQuest.Escort.Trader.add = "coffee";
			break;
		case 4:
			pchar.GenQuest.Escort.Trader.Goods = GOOD_CINNAMON;
			pchar.GenQuest.Escort.Trader.add = "cinnamon";
			break;
		case 5:
			pchar.GenQuest.Escort.Trader.Goods = GOOD_FOOD;
			pchar.GenQuest.Escort.Trader.add = "provision";
			break;
		case 6:
			pchar.GenQuest.Escort.Trader.Goods = GOOD_WEAPON;
			pchar.GenQuest.Escort.Trader.add = "weapon";
			break;
		case 7:
			pchar.GenQuest.Escort.Trader.Goods = GOOD_CHOCOLATE;
			pchar.GenQuest.Escort.Trader.add = "cacao";
			break;
	}
}

bool CheckFreeSitFront(ref _npchar)
{
 	ref rCharacter;
	int n;

	if (!CheckAttribute(_npchar, "Default.ToLocator")) return false;
	
	for (n=0; n<MAX_CHARACTERS; n++)
	{
		makeref(rCharacter, Characters[n]);
		if (CheckAttribute(rCharacter, "location") && rCharacter.location == _npchar.location)
		{
            if (rCharacter.location.locator == _npchar.Default.ToLocator)
                return  false;
		}
    }
    return  true;
}