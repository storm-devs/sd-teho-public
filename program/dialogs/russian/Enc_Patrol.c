void ProcessDialogEvent()
{
	ref NPChar, sld;
	ref arItem;
	aref Link, Diag;
	int i, iShipType, iShipGoods;
	int jewelType;
	string sItemName = "";
	string sItem;
	
	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(Diag, NPChar.Dialog);
	int iTemp = sti(npchar.EncQty);
	string sTemp = "Patrol" + locations[FindLocation(npchar.location)].index + "_";
	string sGroup = "PatrolGroup_" + locations[FindLocation(npchar.location)].index;
	string sTemp1, sTemp2;

	switch(Dialog.CurrentNode)
	{
		case "exit":
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();			
		break;

		case "exit_fight":
			for(i = 0; i < iTemp; i++)
			{
				sld = CharacterFromID(sTemp + i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, sGroup);
			}
			LAi_group_SetRelation(sGroup, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups(sGroup, LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck(sGroup, "LandEnc_PatrolAfrer");
			DialogExit();	
			AddDialogExitQuest("MainHeroFightModeOn");
		break;

		case "exit_noFight":
			for(i = 0; i < iTemp; i++)
			{
				sld = CharacterFromID(sTemp + i);
				sld.Dialog.CurrentNode = "GoodBye";
				sld.greeting = "soldier_common";
				LAi_SetWarriorType(sld);
				LAi_warrior_DialogEnable(sld, true);
				LAi_group_MoveCharacter(sld, sGroup);				
			}
			LAi_group_SetCheck(sGroup, "LandEnc_PatrolAfrer");
			DialogExit();			
		break;

		case "First Time":
			for(i = 0; i < iTemp; i++)
			{
				sld = CharacterFromID(sTemp + i);
				LAi_type_actor_Reset(sld);
				LAi_RemoveCheckMinHP(sld);
			}
			if (GetNationRelation2MainCharacter(sti(NPChar.nation)) == RELATION_ENEMY && sti(NPChar.nation) != PIRATE)
			{
    			if (pchar.nation == npchar.nation)
				{
					dialog.text = RandPhraseSimple("А-а-а, кажется, "+ GetSexPhrase("этот мерзавец поднял","эта мерзавка подняла") +" тревогу в " + XI_ConvertString("Colony" + npchar.city + "Dat") + "! Схватить е"+ GetSexPhrase("го","е") +"!!", "Хех, вы только полюбуйтесь! Некоторые " + NationNamePeople(sti(pchar.nation))+ " умудряются быть во вражде с " + NationNameAblative(sti(npchar.nation)) + "! Схватить негодя"+ GetSexPhrase("я","йку") +"!!!");
				}
				else
				{
					dialog.text = RandPhraseSimple("Вражеский агент близ " + XI_ConvertString("Colony" + npchar.city + "Gen") + "! Взять е"+ GetSexPhrase("го","е") +"!!", "Смотрите-ка, " + NationNamePeople(sti(pchar.nation))+ " разгуливают чуть ли не в " + XI_ConvertString("Colony" + npchar.city + "Dat") + "! Немедленно схватить!!!");
				}
				link.l1 = RandPhraseSimple("Попробуйте, здесь мы в одиночестве...", "Хех, здесь вам помощи ждать неоткуда.");
				link.l1.go = "exit_fight"; 				
			}
			else
			{				
				dialog.text = LinkRandPhrase("Имею честь представиться! Я начальник патруля из " + XI_ConvertString("Colony" + npchar.city + "Gen") + ", мы разыскиваем беглого каторжника.",
					"Здравствуйте, я начальник этого патруля. Мы разыскиваем сбежавшего из " + XI_ConvertString("Colony" + npchar.city + "Gen") + " раба.",
					"Приветствую вас, " + GetAddress_Form(NPChar) + ". Мое подразделение осуществляет патрулирование территории близ " + XI_ConvertString("Colony" + npchar.city + "Gen") + ".");
				Link.l1 = LinkRandPhrase("Прекрасно. Чем я могу вам помочь?",
				"Очень хорошо. Могу ли я быть вам чем-нибудь полез"+ GetSexPhrase("ен","на") +", " + GetAddress_FormToNPC(NPChar) + "?",
				"Великолепно. Что лично я могу для вас сделать?");
				Link.l1.go = "Node_2";
			}
		break;
		
		case "Node_2":
			dialog.text = RandPhraseSimple("Вы не видели ничего подозрительного в округе?",
				"Встречался ли вам кто-нибудь, внушающий подозрения, " + GetAddress_Form(NPChar) + "?");
			Link.l1 = RandPhraseSimple("Нет, ничего такого.", "Нет, офицер, все спокойно.");
			Link.l1.go = "Node_3";		
		break;

		case "Node_3":
			Diag.TempNode = "GoodBye";
			dialog.text = RandPhraseSimple("Ну что же, не смею вас задерживать. Прощайте, " + GetAddress_Form(NPChar) + ".",
				"Понятно. В таком случае, прощайте.");
			Link.l1 = "Удачи вам.";
			Link.l1.go = "exit_noFight";
		break;

		case "GoodBye":
			Diag.TempNode = "GoodBye";
			dialog.text = LinkRandPhrase("Не отвлекайте нас от несения службы.",
				"Я прошу вас не мешать нам!",
				"А, это опять вы... Идите своей дорогой, не мешайте нам.");
			Link.l1 = "Хорошо.";
			Link.l1.go = "Exit";			
		break;
		
		// генератор "Повод для спешки"
		case "Reason_To_Fast_1":
				if(Pchar.Location == Pchar.location.from_sea)
				{
					dialog.text = "Хм... я тебя раньше не видел. Ты кто таков"+ GetSexPhrase("","а") +"?";
					link.l1 = "Я т"+ GetSexPhrase("от","а") +", кого ты ждешь...";
					link.l1.go = "Reason_To_Fast_11";
					link.l2 = "Я капитан " + GetFullName(pchar) + ". Хочу поинтересоваться, зачем ты сюда так торопился, чуть портки в борделе не оставил...";
					link.l2.go = "Reason_To_Fast_21";
					link.l3 = "Я капитан " + GetFullName(pchar) + ". Гуляю здесь, морским бризом дышу...";
					link.l3.go = "Reason_To_Fast_31";
				}
				else
				{
					Diag.TempNode = "GoodBye";
					dialog.text = "Приш"+ GetSexPhrase("ел","ла") +", наконец. Я уж думал, не дождусь... А этот тип с тобой что-ли?";
					link.l1 = "Какой тип?";
					link.l1.go = "Reason_To_Fast_Hunter";
				} 
		break;
		
		case "Reason_To_Fast_Hunter":
			DialogExit();	
			AddDialogExitQuest("ReasonToFast_MeetHunter");
		break;
		
		case "Reason_To_Fast_11":
			dialog.text = "Не очень-то ты похож"+ GetSexPhrase("","а") +" на того, кому бы доверился " + GetName( NAMETYPE_MAIN, pchar.questTemp.ReasonToFast.p3, NAME_NOM) + ".";
			if(!CheckCharacterItem(pchar,"mapQuest"))
			{
				link.l1 = "Хорошо, я так ему и передам.";
				link.l1.go = "Reason_To_Fast_12";
			}	
			link.l2 = "А кто такой этот " + GetName( NAMETYPE_MAIN, pchar.questTemp.ReasonToFast.p3, NAME_NOM) + "?";
			link.l2.go = "Reason_To_Fast_13";
		break;
		
		case "Reason_To_Fast_21":
			dialog.text = "Любопытство, конечно не порок, но иногда изрядно укорачивает жизнь...";
			link.l1 = "Ну-ну!";
			link.l1.go = "Reason_To_Fast_ExitFight";
			pchar.questTemp.ReasonToFast = "PatrolAfter";	
		break;
		
		case "Reason_To_Fast_31":
			Diag.TempNode = "Reason_To_Fast_GoodBye";
			dialog.text = "Скоро прилив. Вы бы покинули бухту, здесь вода поднимается до самых пальмовых зарослей.";
			link.l1 = "Ничего, я хорошо плаваю.";
			link.l1.go = "Reason_To_Fast_GoodBye_0";
			pchar.questTemp.ReasonToFast = "MeetPatrolFail";
		break;
		
		case "Reason_To_Fast_12":
			jewelType = sti(pchar.questTemp.ReasonToFast.p4);
			pchar.questTemp.ReasonToFast.item = "jewelry" + jewelType;
			sItem = "jewelry" + jewelType;
			switch (jewelType)
			{
				case 1:
					sItemName = "аметистов";
				break;
				case 2:
					sItemName = "алмазов";
				break;
				case 3:
					sItemName = "рубинов";
				break;
				case 4:
					sItemName = "изумрудов";
				break;
			}
			pchar.questTemp.ReasonToFast.jewType = sItemName;
			dialog.text = "Ладно, ладно. Обещанные 30 " + sItemName + " с тобой?";
			link.l1 = GetName(NAMETYPE_MAIN , pchar.questTemp.ReasonToFast.p3, NAME_NOM) + " сказал, что времени мало было, чтобы столько камешков собрать. Велел деньги предложить.";
			link.l1.go = "Reason_To_Fast_14";
			if (GetCharacterItem(pchar, pchar.questTemp.ReasonToFast.item) >= 30)
			{
				link.l2 = "Получи.";
				link.l2.go = "Reason_To_Fast_15";
			}			
		break;
		
		case "Reason_To_Fast_13":
			dialog.text = "Хех! На том свете узнаешь!";
			link.l1 = "Какая самоуверенность...";
			link.l1.go = "Reason_To_Fast_ExitFight";
			pchar.questTemp.ReasonToFast = "PatrolAfter";	
		break;
		
		case "Reason_To_Fast_14":
			dialog.text = "Отлично, тогда с тебя " + sti(pchar.questTemp.ReasonToFast.p5) + " песо, как и уговаривались.";
			link.l1 = "Не много ли ты просишь?";
			link.l1.go = "Reason_To_Fast_16";
			if(makeint(pchar.money) >= sti(pchar.questTemp.ReasonToFast.p5))
			{
				link.l2 = "Получи.";
				link.l2.go = "Reason_To_Fast_17";
			}	
			link.l3 = "Но у меня нет при себе такой суммы!";
			link.l3.go = "Reason_To_Fast_18";	
			AddQuestRecord("ReasonToFast", "9");
			AddQuestUserData("ReasonToFast", "sText", pchar.questTemp.ReasonToFast.jewType);
		break;
		
		case "Reason_To_Fast_15":
			TakeNItems(pchar, pchar.questTemp.ReasonToFast.item, -30); 
			dialog.text = "Все согласно уговору. Вот, держи. Эту карту отняли у того повешенного пирата, о котором спрашивал "  + GetName( NAMETYPE_MAIN, pchar.questTemp.ReasonToFast.p3, NAME_NOM) + ".";
			link.l1 = "Дело сделано!";
			link.l1.go = "Reason_To_Fast_15_1";
		break;
		
		case "Reason_To_Fast_15_1":
			Diag.TempNode = "Reason_To_Fast_GoodBye";
			DialogExit();
			AddQuestRecord("ReasonToFast", "10");
			AddQuestUserData("ReasonToFast", "sName", GetName( NAMETYPE_MAIN, pchar.questTemp.ReasonToFast.p3, NAME_NOM));
			pchar.questTemp.ReasonToFast = "PatrolSuccess_2";
			GiveItem2Character(pchar, "mapQuest"); 
			arItem = ItemsFromID("mapQuest");
			ReasonToFast_GenerateTreasureMap(arItem);	
			DeleteAttribute(pchar, "questTemp.ReasonToFast.cantSpeakOther");//можем говорить с губером 
			AddDialogExitQuest("pchar_back_to_player");	
			LAi_LocationFightDisable(&locations[FindLocation(pchar.questTemp.ReasonToFast.PatrolLocation)], false);	
		break;
		
		case "Reason_To_Fast_16":
			dialog.text = "Мы о сумме с " + GetName( NAMETYPE_MAIN, pchar.questTemp.ReasonToFast.p3, NAME_ABL) + " заранее договорились... Что-то не нравится мне это... Вали е"+ GetSexPhrase("го","е") +", ребята!";
			link.l1 = "Что ж, попробуй!";
			link.l1.go = "Reason_To_Fast_ExitFight";
			pchar.questTemp.ReasonToFast = "PatrolAfter";	
		break;
		
		case "Reason_To_Fast_17":
			pchar.questTemp.ReasonToFast = "PatrolSuccess_1";
			AddMoneyToCharacter(pchar, -makeint(sti(pchar.questTemp.ReasonToFast.p5)));
			pchar.GenQuest.CannotWait = 1; // лочим интерфейс отдыха
			if(CheckAttribute(pchar,"questTemp.ReasonToFast.chain")) DeleteAttribute(pchar,"questTemp.ReasonToFast.chain");
			if(CheckAttribute(pchar,"questTemp.ReasonToFast.ShipName")) DeleteAttribute(pchar,"questTemp.ReasonToFast.ShipName");
			if(CheckAttribute(pchar,"questTemp.ReasonToFast.ShipTypeName")) DeleteAttribute(pchar,"questTemp.ReasonToFast.TypeName");
			switch (sti(pchar.questTemp.ReasonToFast.target))
			{
				case 0: // корабль с товаром
					sTemp1 = generateRandomNameToShip(sti(pchar.questTemp.ReasonToFast.GuardNation));
					iShipType = ReasonToFast_GetVictimShipType();
					iShipGoods = ReasonToFast_GetVictimShipGoods();
					dialog.text = "Отлично! Теперь о деле. Мы перехватили тот " + GetStrSmallRegister(pchar.questTemp.ReasonToFast.ShipTypeName) +" '" + sTemp1 + "' с грузом " + GetGoodsNameAlt(iShipGoods) + ", весь экипаж уже в казематах, а 'товар' пока на борту. Транспортная команда набрана из портовых забулдыг, и до завтра в порт попадёт вряд ли. Поступай с ними, как сочтёшь нужным.";
					link.l1 = "Хорошо. Все так и передам " + GetName( NAMETYPE_MAIN, pchar.questTemp.ReasonToFast.p3, NAME_DAT) + ".";
					link.l1.go = "Reason_To_Fast_GoodBye_0";
					pchar.questTemp.ReasonToFast.chain = "A0";
					pchar.questTemp.ReasonToFast.ShipName = sTemp1;										
					DeleteAttribute(pchar, "questTemp.ReasonToFast.cantSpeakOther");//можем говорить с губером
					AddQuestRecord("ReasonToFast", "11");
					AddQuestUserData("ReasonToFast", "sShipType", pchar.questTemp.ReasonToFast.ShipTypeName);					
					AddQuestUserData("ReasonToFast", "sShipName", sTemp1);
					AddQuestUserData("ReasonToFast", "sGoodsName", GetGoodsNameAlt(iShipGoods));
					ReasonToFast_GenerateVictimShip(iShipType, iShipGoods);					
				break;

				case 1: // сокровища губернатора
					switch(rand(3))
					{
						case 0:
							sTemp1 = "Приданое своей дочурки";
						break;
						case 1:
							sTemp1 = "Подарки для вице-короля";
						break;
						case 2:
							sTemp1 = "Подарки к своему юбилею";
						break;
						case 3:
							sTemp1 = "Свои 'пенсионные'";
						break;
					}
					switch(rand(3))
					{
						case 0:
							sTemp2 = "Плутовка";
						break;
						case 1:
							sTemp2 = "Шалунья";
						break;
						case 2:
							sTemp2 = "Проказница";
						break;
						case 3:
							sTemp2 = "Озорница";
						break;
					}
					pchar.questTemp.ReasonToFast.password = sTemp2;
					sTemp2 = generateRandomNameToShip(sti(pchar.questTemp.ReasonToFast.GuardNation));
					dialog.text = "Отлично! " + sTemp1 + " губернатор хранит у себя в будуаре. Курьерское судно для транспортировки будет со дня на день, но ты успеешь. Лакей 'наш' человек. Пароль: '"+ pchar.questTemp.ReasonToFast.password +"', отзыв: '"+ sTemp2 +"'.";
					link.l1 = "Хорошо. Все так и передам " + GetName( NAMETYPE_MAIN, pchar.questTemp.ReasonToFast.p3, NAME_DAT) + ".";
					link.l1.go = "Reason_To_Fast_GoodBye_0";
					pchar.questTemp.ReasonToFast.chain = "A1";
					AddQuestRecord("ReasonToFast", "12");
					pchar.questTemp.ReasonToFast.ShipName = sTemp2;
					DeleteAttribute(pchar, "questTemp.ReasonToFast.cantSpeakOther");//можем говорить с губером
					
					pchar.quest.ReasonToFast_ClearLakey.win_condition.l1 = "Timer";
					pchar.quest.ReasonToFast_ClearLakey.win_condition.l1.date.day = GetAddingDataDay(0, 0, 2);
					pchar.quest.ReasonToFast_ClearLakey.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 2);
					pchar.quest.ReasonToFast_ClearLakey.win_condition.l1.date.year = GetAddingDataYear(0, 0, 2);
					pchar.quest.ReasonToFast_ClearLakey.function = "ReasonToFast_ClearLakey";
				break;				
			}
		break;
		
		case "Reason_To_Fast_18":
			if(makeint(pchar.money) >= sti(pchar.questTemp.ReasonToFast.p5))
			{
				dialog.text = "Да ты пытаешься меня обмануть?! Собака!";
				link.l1 = "Закрой рот!";
				link.l1.go = "Reason_To_Fast_ExitFight";
				pchar.questTemp.ReasonToFast = "PatrolAfter";	
			}
			else
			{
				dialog.text = "Ты пропил"+ GetSexPhrase("","а") +"! Мои! Деньги!... Аргх.";
				link.l1 = "Вот черт!";
				link.l1.go = "Reason_To_Fast_ExitFight";
				pchar.questTemp.ReasonToFast = "PatrolAfter";	
			}
		break;

		case "Reason_To_Fast_GoodBye_0":
			LAi_SetPlayerType(pchar);
			for(i = 0; i < iTemp; i++)
			{
				sld = CharacterFromID(sTemp + i);
				sld.Dialog.CurrentNode = "Reason_To_Fast_GoodBye";
				sld.greeting = "soldier_common";
				LAi_SetWarriorType(sld);
				LAi_warrior_DialogEnable(sld, true);
				LAi_group_MoveCharacter(sld, sGroup);				
			}
			pchar.quest.RemovePatrolFromShore.win_condition.l1          = "ExitFromLocation";
			pchar.quest.RemovePatrolFromShore.win_condition.l1.location = pchar.location; 
            pchar.quest.RemovePatrolFromShore.function    				= "ReasonToFast_DeletePatrolFromShore"; 
			DialogExit();			
		break;
		
		case "Reason_To_Fast_GoodBye":
			Diag.TempNode = "Reason_To_Fast_GoodBye";
			dialog.text = "Вы бы покинули бухту, уже прилив начался...";
			link.l1 = "Да-да, уже ухожу.";
			link.l1.go = "Exit";
		break;
		
		case "Reason_To_Fast_ExitFight":
			pchar.questTemp.ReasonToFast.relation = GetNationRelation2MainCharacter(sti(pchar.questTemp.ReasonToFast.GuardNation));
			SetNationRelation2MainCharacter(sti(pchar.questTemp.ReasonToFast.GuardNation), RELATION_ENEMY); 
			
			pchar.GenQuest.HunterScore2Pause = 1; //НЗГ не начисляются
			pchar.GenQuest.ReputationNotChange = 1; //репутацию не менять
			
			chrDisableReloadToLocation = true;
			LAi_SetPlayerType(pchar);
			LAi_LocationFightDisable(&locations[FindLocation(pchar.questTemp.ReasonToFast.PatrolLocation)], false);	
			for(i = 0; i < iTemp; i++)
			{
				sld = CharacterFromID(sTemp + i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, sGroup);
			}
			if(pchar.questTemp.ReasonToFast == "PatrolAngry")
			{
				sld = CharacterFromID("ReasonToFast_Hunter");
				if(sld != -1) 
				{ 
					LAi_SetWarriorType(sld); 
					LAi_group_MoveCharacter(sld, sGroup);
				}
			}			
			LAi_group_SetRelation(sGroup, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups(sGroup, LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck(sGroup, "OpenTheDoors"); 
			LAi_group_SetCheck(sGroup, "ReasonToFast_PatrolDied");
			DialogExit();	
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "Reason_To_Fast_AfterHunter1":
			dialog.text = "Мы же договаривались, что посыльный должен быть один!";
			link.l1 = "Неувязочка вышла. Видишь, посыльный заплутал? Меня на подмену прислали.";
			link.l1.go = "Reason_To_Fast_11";
			link.l2 = "А я и приш"+ GetSexPhrase("ел один","ла одна") +", только не за тем, о чём ты думаешь.";
			link.l2.go = "Reason_To_Fast_AfterHunter2";
		break;
		
		case "Reason_To_Fast_AfterHunter2":
			dialog.text = "Значит, всё-таки выследил"+ GetSexPhrase("","а") +"... Ну, тогда не обессудь.";
			link.l1 = "Аргх...";
			link.l1.go = "Reason_To_Fast_ExitFight";
			pchar.questTemp.ReasonToFast = "PatrolAfterHunter";	
		break;
		
		case "Reason_To_Fast_AfterHunter3":
			dialog.text = "Ах, мерзав"+ GetSexPhrase("ец","ка") +"! А я чуть не попался!.. Стража! Взять е"+ GetSexPhrase("го","е") +"...";
			link.l1 = "Аргх...";
			link.l1.go = "Reason_To_Fast_ExitFight";
			pchar.questTemp.ReasonToFast = "PatrolAngry";	
		break;
		// генератор "Повод для спешки"
	}
}
