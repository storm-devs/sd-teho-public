// диалоги прочих НПС
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "Явный баг в коде. Сообщите об этом Jason'у, как и при каких обстоятельствах его получили.";
			link.l1 = "Обязательно сообщу!";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			if (npchar.id == "HWICFernando") NextDiag.CurrentNode = "Fernando";
			DialogExit();
		break;
	
//---------------------------------------за Голландию--------------------------------------------------
		//сопроводить торговца
		case "Baltazar":
			pchar.quest.Create_BaltazarOver.over = "yes";//снять прерывание
			dialog.text = "Какая удача! Капитан, мне как раз нужен эскорт до Филипсбурга, очень срочно...";
			link.l1 = "Вы - Бальтазар Риддербок?";
			link.l1.go = "Baltazar_1";			
		break;
		
		case "Baltazar_1":
			dialog.text = "А, черт, я становлюсь известнее вице-короля! Кто вы? Что вам угодно?";
			link.l1 = "Я - капитан " + GetFullName(pchar) + ". Меня прислал Лукас Роденбург. Я должен взять вас и ваше судно под охрану.";
			link.l1.go = "Baltazar_2";			
		break;
		
		case "Baltazar_2":
			dialog.text = "О, значит минхер Роденбург все-таки прислушался к моим мольбам о помощи! А то, понимаете, нашелся какой-то капер...";
			link.l1 = "Опустим подробности этой истории - они мне известны.";
			link.l1.go = "Baltazar_3";			
		break;
		
		case "Baltazar_3":
			dialog.text = "Конечно! Я и так потерял слишком много времени... Мне необходимо быть в Филипсбурге не позднее, чем через две недели.";
			link.l1 = "Тогда отправляйтесь на корабль и готовьте судно к отплытию. Мы отчаливаем немедленно!";
			link.l1.go = "Baltazar_4";			
		break;
		
		case "Baltazar_4":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "", 4);
			SetCharacterRemovable(npchar, false);
			npchar.CompanionEnemyEnable = false; //всегда друзья
			SetCompanionIndex(pchar, -1, sti(npchar.index));
			npchar.loyality = MAX_LOYALITY;
			AddQuestRecord("Holl_Gambit", "1-3");
			SetFunctionTimerCondition("Baltazar_ConvoyOver", 0, 0, 14, false); //таймер
			pchar.quest.BaltazarConvoy_fail.win_condition.l1 = "NPC_Death";//прерывание на потопление сопровождаемого
			pchar.quest.BaltazarConvoy_fail.win_condition.l1.character = "Baltazar";
			pchar.quest.BaltazarConvoy_fail.function = "Baltazar_fail";
			pchar.quest.BaltazarConvoy_complete.win_condition.l1 = "location";//прерывание на выполнение
			pchar.quest.BaltazarConvoy_complete.win_condition.l1.location = "Marigo_town";
			pchar.quest.BaltazarConvoy_complete.function = "Baltazar_complete";
			if (rand(1) == 0)
			{
				BaltazarPirateGlobalCreate();
			}
			else
			{
				pchar.questTemp.HWIC.Holl.BaltazarAttack = "true";
				pchar.quest.BaltazarConvoy_Attack.win_condition.l1 = "location";//прерывание на выполнение
				pchar.quest.BaltazarConvoy_Attack.win_condition.l1.location = "SentMartin";
				pchar.quest.BaltazarConvoy_Attack.function = "BaltazarPirateSeaCreate";
			}
		break;
		
		case "Baltazar_5":
			dialog.text = "Спасибо за ваш труд, капитан! Как я и ожидал - проклятый " + GetName( NAMETYPE_ORIG, pchar.questTemp.HWIC.Holl.PirateName, NAME_NOM) + " напал на меня. И ваша защита оказалась как нельзя кстати, а потому примите мою благодарность и эти 5 000 песо.";
			link.l1 = "Хм, не слишком щедрая награда за жизнь...";
			link.l1.go = "Baltazar_6";			
		break;
		
		case "Baltazar_6":
			dialog.text = "Кроме этого, я обязательно при случае отправлю минхеру Роденбургу письмо с наивысшей оценкой ваших действий. А теперь - мне пора.";
			link.l1 = "Ну что же, прощайте, Бальтазар.";
			link.l1.go = "Baltazar_7";			
		break;
		
		case "Baltazar_7":
			DialogExit();
			chrDisableReloadToLocation = false;
			bDisableFastReload = false;
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload2_back", "none", "", "", "", 3.0);
			AddQuestRecord("Holl_Gambit", "1-6");
			AddMoneyToCharacter(pchar, 5000);
			ChangeCharacterComplexReputation(pchar,"nobility", 2); 
			ChangeCharacterNationReputation(pchar, HOLLAND, 1);
			ChangeOfficersLoyality("good_all", 1);
			pchar.questTemp.HWIC.Holl = "BaltazarCom";
		break;
		
		//командировка в Сантьяго
		case "Santiago_Trip":
			dialog.text = "Сеньор! Подождите... вы, кажется, уронили...";
			link.l1 = "Что? А?!...";
			link.l1.go = "Santiago_Trip_1";
		break;
		
		case "Santiago_Trip_1":
			DialogExit();
			PlaySound("People Fight\Death_NPC_08.wav");
			SetLaunchFrameFormParam("Вас оглушили ударом сзади", "", 0, 5);
			LaunchFrameForm();
			WaitDate("", 0, 0, 0, 15, 10); //крутим время
			RecalculateJumpTable();
			DoQuestFunctionDelay("SantiagoTripInHouse", 5.0);
		break;
		
		case "Santiago_Trip_2":
			dialog.text = "Прости, друг мой – пришлось тебя слегка приложить, чтоб не трепыхался. Понимаю – голова болит. Ничего – пройдет. Если успеет...";
			link.l1 = "Кто ты, раздери тебя черт, и что тут творится?!";
			link.l1.go = "Santiago_Trip_3";
		break;
		
		case "Santiago_Trip_3":
			dialog.text = "Потише, потише, друг – иначе придется тебя опять угомонить. Мы ведь не хотим, чтобы сюда ломились эти скучные солдафоны, бренча своими ржавыми железяками, так? Надо поговорить, спокойно и без шума.";
			link.l1 = "Верните мне мою шпагу, сударь, и мы с вами замечательно побеседуем, клянусь бурей!";
			link.l1.go = "Santiago_Trip_4";
		break;
		
		case "Santiago_Trip_4":
			dialog.text = "Шустрый какой... Нет уж, обойдемся без стали на этот раз. Если расскажешь мне то, что я хочу знать – возможно, уйдешь отсюда на своих двоих. А будешь мутить воду, и шуметь – получишь вот этот милый кинжал в брюхо. Я понятно объясняю? Так что давай просто, как ты сказал - побеседуем\nМолчишь? Хорошо... значит, мы договорились. Что ты вез от Роденбурга к банкиру?";
			link.l1 = "Письмо.";
			link.l1.go = "Santiago_Trip_5";
		break;
		
		case "Santiago_Trip_5":
			dialog.text = "Умно... я знаю, что не букет хризантем. Что было в письме, парень?";
			link.l1 = "Откуда мне знать? Может любовное послание. Я не имею привычки читать доверенную мне корреспонденцию.";
			link.l1.go = "Santiago_Trip_6";
		break;
		
		case "Santiago_Trip_6":
			dialog.text = "Честный капитан – редкость в наше паршивое время. Тем хуже для тебя. А что сказал этот чертов банкир, когда получил пакет? Что у него за дела с голландцами?";
			link.l1 = "Торгуют контрабандным парфюмом из Франции, полагаю... или баварским коровьим навозом.";
			link.l1.go = "Santiago_Trip_7";
			link.l2 = "Речь шла о некой компенсации за что-то. Это все, что мне известно.";
			link.l2.go = "Santiago_Trip_8";
		break;
		
		case "Santiago_Trip_7":
			dialog.text = "А ты смелый парень... еще и с чувством юмора. Жаль будет тебя убивать. Гастону бы ты понравился. Впрочем, посиди пока тут. Мне нужно кое-что проверить, а Мигель приглядит, чтобы ты не шумел, пока меня не будет.";
			link.l1 = "Клянусь, 'друг мой', вы пожалеете!";
			link.l1.go = "Santiago_Trip_9";
		break;
		
		case "Santiago_Trip_8":
			dialog.text = "Вот вам и весь гонор... Запахло жареным, и наш бравый капитан сразу проявил благоразумие. Что ж так тянул-то? Мне придется кое-что проверить, а потом – я вернусь, и мы договорим, если будет о чем. Посиди пока тут, сейчас придет Мигель и приглядит, чтобы ты не шумел, пока меня не будет.";
			link.l1 = "Клянусь, 'друг мой', вы пожалеете!";
			link.l1.go = "Santiago_Trip_11";
		break;
		
		case "Santiago_Trip_9":
			dialog.text = "Ну-ну. Сиди тихо, герой, и может быть, все будет хорошо.";
			link.l1 = "...";
			link.l1.go = "Santiago_Trip_11";
		break;
		
		case "Santiago_Trip_10":
			dialog.text = "Сиди уж, и надейся, что твоя принципиальная гибкость себя оправдает.";
			link.l1 = "...";
			link.l1.go = "Santiago_Trip_11";
		break;
		
		case "Santiago_Trip_11":
			DialogExit();
			AddQuestRecord("Holl_Gambit", "1-44");
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "Santiago_HouseSp2", "goto", "goto4", "", -1);
			pchar.quest.Santiago_Trip1.win_condition.l1 = "item";
			pchar.quest.Santiago_Trip1.win_condition.l1.item = "slave_01";
			pchar.quest.Santiago_Trip1.function = "SantiagoTrip_wait";
		break;
		
		case "Santiago_Trip_12":
			dialog.text = "Что за черт?!";
			link.l1 = "Ну, держись, каналья!";
			link.l1.go = "Santiago_Trip_13";
		break;
		
		case "Santiago_Trip_13":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешить драться
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "SantiagoTripExitFromRoom");
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
		case "Santiago_Trip_14":
			dialog.text = "Вот так дела... а я думаю, что за шум. Мои поздравления – ты ловкий малый!";
			link.l1 = "Ловчее, чем ты думаешь... Ну, а теперь посмотрим, что ты стоишь против вооруженного противника!";
			link.l1.go = "Santiago_Trip_15";
		break;
		
		case "Santiago_Trip_15":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешить драться
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "SantiagoTripExitHouse");
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
		//офицер-посланник по 5 заданию
		case "HollQuest_Officer":
			dialog.text = "Вас срочно вызывает минхер Лукас Роденбург. Прибудьте к нему немедленно.";
			link.l1 = "Хорошо. Я уже иду к нему.";
			link.l1.go = "HollQuest_Officer_exit";			
		break;
		
		case "HollQuest_Officer_exit":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload4_back", "none", "", "", "", -1);
			pchar.questTemp.HWIC.Holl = "MerdokStart";
			AddQuestRecord("Holl_Gambit", "1-36");
		break;
		
//---------------------------------------------против всех----------------------------------------------
		//убрать испанского идальго
		case "Fernando":
			dialog.text = "Что вам от меня нужно?";
			link.l1 = "Твоя голова, каналья!";
			link.l1.go = "Fernando_fight";
			link.l2 = "Да нет, ничего.";
			link.l2.go = "exit";	
			NextDiag.TempNode = "Fernando_repeat";
		break;
		
		case "Fernando_repeat":
			dialog.text = "Это опять вы? Что вы хотите, объясните, наконец!";
			link.l1 = "Твоя голова, каналья!";
			link.l1.go = "Fernando_fight";
			link.l2 = "Да нет, ничего.";
			link.l2.go = "exit";	
			NextDiag.TempNode = "Fernando_repeat";		
		break;
		
		case "Fernando_fight":
			chrDisableReloadToLocation = true;//выходы закроем
			LAi_SetWarriorType(npchar);
            LAi_group_MoveCharacter(npchar, "SPAIN_CITIZENS");
			LAi_group_Attack(NPChar, Pchar);
			SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
            DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");	
			pchar.quest.HWIC_Fernando.win_condition.l1 = "NPC_Death";
			pchar.quest.HWIC_Fernando.win_condition.l1.character = "HWICFernando";
			pchar.quest.HWIC_Fernando.function = "Fernando_died";
		break;
		
		//в доме Флитвуда
		case "Fleetwood_soldier"://для любителей сунуть нос куда не надо
			if (CheckAttribute(npchar, "quest.talked"))
			{
			dialog.text = "Опять вы? Да что же вы тут все вынюхиваете? Не нравится мне все это... Вот что: я вас арестую, и отправлю на разбирательство в комендатуру. Ребята, взять этого типа!";
			link.l1 = "Но я только хотел...";
			link.l1.go = "Fleetwood_soldier_4";	
			}
			else
			{
			dialog.text = "Кто вы такой и что вам здесь надо? Немедленно объяснитесь!";
			link.l1 = "Извините, сэр, я кажется, зашел не в тот дом. Прошу меня извинить.";
			link.l1.go = "Fleetwood_soldier_1";	
			link.l2 = "Я хочу увидеть Ричарда Флитвуда.";
			link.l2.go = "Fleetwood_soldier_2";		
			}
		break;
		
		case "Fleetwood_soldier_1":
			dialog.text = "Точно. Вы здесь не по адресу. Будьте добры покинуть помещение!";
			link.l1 = "Да, конечно.";
			link.l1.go = "Fleetwood_soldier_3";			
		break;
		
		case "Fleetwood_soldier_2":
			dialog.text = "Вот как? И кто же вам сказал, что он здесь живет? Подозрительно все это... Вот что: я вас арестую, и отправлю на разбирательство в комендатуру. Ребята, взять этого типа!";
			link.l1 = "Но я только хотел увидеть Ричарда...";
			link.l1.go = "Fleetwood_soldier_4";	
		break;
		
		case "Fleetwood_soldier_3":
			DialogExit();
			npchar.quest.talked = "true";
			DoQuestReloadToLocation("SentJons_town", "reload", "houseSP3", "");
			pchar.quest.Fleetwood_Soldier.win_condition.l1 = "location";
			pchar.quest.Fleetwood_Soldier.win_condition.l1.location = "SentJons_houseSP3";
			pchar.quest.Fleetwood_Soldier.function = "Fleetwood_Soldier";//для настырных
		break;
		
		case "Fleetwood_soldier_4":
			DialogExit();
			GoToPrison("SentJons", 1000, 10);			
		break;
		
		case "Theft_soldier":
			dialog.text = "Аргх! Вор? Шпион? Ну, держись, голубчик!";
			link.l1 = "А-а-ть!";
			link.l1.go = "Attack_Theft_soldier";			
		break;
		
		case "Attack_Theft_soldier":
			LAi_group_Delete("EnemyFight");
			LAi_SetHP(npchar, 500, 500);
			LAi_SetWarriorType(npchar);
            LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
		case "Attack_soldier":
			dialog.text = "Аргх! Что этот тип тут делает? Ребята, здесь шпион! К оружию!";
			link.l1 = "А-а-ть!";
			link.l1.go = "Attack_soldier_fight";			
		break;
		
		case "Attack_soldier_fight":
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//снять запрет драки
			LAi_group_Delete("EnemyFight");
			for (i=1; i<=4; i++)
			{
			sld = characterFromId("Attack_sold_"+i);	
			LAi_SetWarriorType(sld);
            LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "PrepareToStreetFight");
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
		//Книппель-пленник в трюме
		case "Sailor_deck":
			chrDisableReloadToLocation = true;
			dialog.text = "Капитан, мы допросили этого мерзавца, как вы и сказали. Пришлось слегка прижечь его... При нем оказалось вот это письмо. Негодяй пытался его съесть, но мы вовремя пережали ему глотку. Как вы и предполагали - его цель была вывезти из Виллемстада некую девчонку для своего шефа.";
			link.l1 = "Письмо? Давай посмотрим... Ну, а потом я сам с ним поговорю.";
			link.l1.go = "Sailor_deck_1";			
		break;
		
		case "Sailor_deck_1":
			DialogExit();
			GiveItem2Character(pchar, "NPC_Letter");
			AddQuestRecordInfo("LetterToAbi", "1");
		break;
		
		case "Sailor_deck_2":
			dialog.text = "Какие будут приказания, капитан?";
			link.l1 = "Выбросите эту падаль за борт. И приготовиться к высадке на берег!";
			link.l1.go = "Sailor_deck_3";			
		break;
		
		case "Sailor_deck_3":
			dialog.text = "Есть, капитан!";
			link.l1 = "...";
			link.l1.go = "Sailor_deck_4";			
		break;
		
		case "Sailor_deck_4":
			DialogExit();
			chrDisableReloadToLocation = false;
			AddQuestRecord("Holl_Gambit", "3-21");
			LAi_SetActorType(pchar);
			sld = characterFromId("KnippelClone");
			ChangeCharacterAddressGroup(sld, "none", "", "");
			sld.lifeday = 0;
			for (i=1; i<=3; i++)
			{
				sld = characterFromId("Sailor_"+i);
				LAi_SetActorType(sld);
				LAi_ActorGoToLocation(sld, "reload", "reload1", "none", "", "", "ReturnMCPlayer", 3);
			}
			pchar.questTemp.HWIC.Self = "toVillemstad";
			sld = characterFromId("Solomon");
			sld.greeting = "solomon_2";
			LocatorReloadEnterDisable("Villemstad_town", "houseSP2", false);//откроем дом Аби
			LocatorReloadEnterDisable("Villemstad_houseSP2", "reload2", true);//закроем комнату Аби
		break;
		
		//Лонгвэй-пленник в трюме
		case "Sailor_deck_5":
			chrDisableReloadToLocation = true;
			dialog.text = "Мы подготовили китайца к допросу, как вы приказали, капитан. При нем ничего не было, никаких бумаг. Жаровня зажжена, наручники и клещи сейчас раскаляем.";
			link.l1 = "Хорошо, Алонсо. Но прежде чем ты возьмешься за дело, я попробую поговорить с ним по душам. Может, он решит сотрудничать добровольно?";
			link.l1.go = "Sailor_deck_6";			
		break;
		
		case "Sailor_deck_6":
			dialog.text = "Как прикажете, кэп.";
			link.l1 = "...";
			link.l1.go = "exit";	
			LAi_SetActorType(npchar);
			LAi_ActorFollow(npchar, pchar, "", -1);
		break;
		
		case "Sailor_deck_7":
			dialog.text = "Да, капитан?";
			link.l1 = "Наденьте на него кандалы и глаз не спускать, ни днем, ни ночью, пока не прибудем на Гваделупу. Всем троим неотступно находится здесь. Отвечаете за него.";
			link.l1.go = "Sailor_deck_8";			
		break;
		
		case "Sailor_deck_8":
			dialog.text = "Есть, капитан!";
			link.l1 = "";
			link.l1.go = "Sailor_deck_9";			
		break;
		
		case "Sailor_deck_9":
			chrDisableReloadToLocation = false;
			AddQuestRecord("Holl_Gambit", "3-48");
			sld = characterFromId("LongwayClone");
			LAi_SetActorType(sld);
			LAi_SetGroundSitType(sld);
			DialogExit();
			pchar.quest.Longway_Shore.win_condition.l1 = "location";
			pchar.quest.Longway_Shore.win_condition.l1.location = "Shore31";
			pchar.quest.Longway_Shore.function = "LongwayInShore";
		break;
		
		//пьяница - передача письма Флитвуду
		case "Drunkard":
			dialog.text = "И-ик! Добрый вечер, сэр! Что вам от меня нужно? Может, поставите кружечку старому пропойце? А я...";
			link.l1 = "Вот что, старый пропойца... Это ты - Джек Гаррисон?";
			link.l1.go = "Drunkard_1";			
		break;
		
		case "Drunkard_1":
			dialog.text = "О! Ну конечно, это я. Кто же еще? А что? На-а-дува-е-ет ве-е-тер пару-у-са...";
			link.l1 = "Пресвятая Дева, даруй мне терпение! Какие паруса? Да у тебя на роже написано, что ты сухопутная крыса... Заработать хочешь?";
			link.l1.go = "Drunkard_2";			
		break;
		
		case "Drunkard_2":
			dialog.text = "Заработать всегда хочу. А что делать-то надо? Только никого убивать я не буду. И красть тоже.";
			link.l1 = "Никого убивать не надо, да и сомневаюсь я, что ты на это способен. Руки не оттуда растут... Вот тут письмо. Ты его берешь и относишь в дом слева от резиденции губернатора, для Ричарда Флитвуда.";
			link.l1.go = "Drunkard_3";			
		break;
		
		case "Drunkard_3":
			dialog.text = "Для Ричарда Флитвуда? Не-е... Да меня сразу же арестуют, если я только сунусь к нему на порог.";
			link.l1 = "Заткнись и слушай. Никто тебя не арестует. Скажешь, что ты прибыл от Чарли Книппеля по поводу Абигайль. Тебя пропустят. Повтори, что я тебе сказал.";
			link.l1.go = "Drunkard_4";			
		break;
		
		case "Drunkard_4":
			dialog.text = "А кто это - Абигайль? Книппеля я знаю...";
			link.l1 = "Не твое дело. Меньше знаешь - дольше живешь. Ну, я жду. Повтори.";
			link.l1.go = "Drunkard_5";			
		break;
		
		case "Drunkard_5":
			dialog.text = "Прибыл от Чарли Книппеля по делу э-э... Абигайль, вот.";
			link.l1 = "Молодец. За работу получишь 5 000 песо.";
			link.l1.go = "Drunkard_6";			
		break;
		
		case "Drunkard_6":
			if (makeint(Pchar.money) >= 5000)
			{
			dialog.text = "Пять тысяч? О-ох... Только передать письмо?";
			link.l1 = "Не только. Тебе дадут другое письмо. С ним придешь в таверну и сядешь на это место. Я у тебя его заберу. Не вздумай сглупить, и ничего не бойся - я за тобой наблюдаю и буду рядом. Держи деньги авансом, чтобы тебе спокойнее было.";
			link.l1.go = "Drunkard_7";	
			}
			else
			{
			dialog.text = "Пять тысяч? А у вас есть эти деньги?";
			link.l1 = "Ха! Конечно, есть. Сейчас принесу.";
			link.l1.go = "Drunkard_no_money";	
			NextDiag.CurrentNode = "Drunkard_no_money";
			}
		break;
		
		case "Drunkard_no_money":
			dialog.text = "Вы принесли пять тысяч?";
			if (makeint(Pchar.money) >= 5000)
			{
			link.l1 = "Да. Вот они, не переживай. Держи.";
			link.l1.go = "Drunkard_7";
			}
			else
			{
			link.l1 = "Нет, жди, скоро вернусь.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Drunkard_no_money";
			}
		break;
		
		case "Drunkard_7":
			AddMoneyToCharacter(pchar, -5000);
			RemoveItems(PChar, "MC_Letter", 1);
			dialog.text = "Гм... Идти прямо сейчас, сэр?";
			link.l1 = "Нет, в четверг с утра... Конечно сейчас, тупица! Допивай свой ром и давай живо на выход!";
			link.l1.go = "Drunkard_8";			
		break;
		
		case "Drunkard_8":
		DialogExit();
		AddQuestRecord("Holl_Gambit", "3-26");
		LAi_SetStayType(npchar);
		LAi_RemoveLoginTime(npchar);//удалить время загрузки
		GetCharacterPos(pchar, &locx, &locy, &locz);
		ChangeCharacterAddressGroup(npchar, "sentjons_tavern", "goto", LAi_FindNearestFreeLocator("goto", locx, locy, locz));
		LAi_SetActorType(npchar);
		LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "sentjons_town", "reload", "reload4_back", "DrunkardGoTown", -1);
		chrDisableReloadToLocation = true;//закрыть локацию
		LocatorReloadEnterDisable("SentJons_town", "reload1_back", true);
		LocatorReloadEnterDisable("SentJons_town", "reload2_back", true);
		LocatorReloadEnterDisable("SentJons_town", "gate_back", true);//чтобы не сбежал
		break;
		
		case "Drunkard_9":
			dialog.text = "А, вот и вы, сэр... Право, лучше бы я этого не делал. Ричард пришел в ярость, когда прочитал ваше письмо. Я думал, он меня убьет...";
			link.l1 = "Но не убил же! Не переживай, он не посмел бы этого сделать - ты ему очень дорог был в тот момент, ха-ха! Ты даже не представляешь, как...";
			link.l1.go = "Drunkard_10";			
		break;
		
		case "Drunkard_10":
			dialog.text = "Мне надо выпить... Вот его ответ вам.";
			link.l1 = "Давай сюда. И не вздумай болтать!";
			link.l1.go = "Drunkard_11";			
		break;
		
		case "Drunkard_11":
			GiveItem2Character(pchar, "MC_Letter");
			ChangeItemDescribe("MC_Letter", "itmdescr_MC_Letter1");
			AddQuestRecordInfo("FleetwoodAnswer", "1");
			dialog.text = "Я еще дня два с трудом разговаривать буду... Прощайте... век бы вас не видеть.";
			link.l1 = "Бывай, старый пропойца, ха-ха-ха! Наду-у-ва-а-ет ве-е-тер пару-у-са... Выпей и успокойся, всё уже позади!";
			link.l1.go = "Drunkard_12";			
		break;
		
		case "Drunkard_12":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeday = 0;
			AddQuestRecord("Holl_Gambit", "3-27");
			pchar.questTemp.HWIC.Self = "FleetwoodAgree";
			AddCharacterExpToSkill(pchar, "Sneak", 300);//скрытность
		break;
		
		//кэп курьерского судна
		case "Cureer_abordage":
			dialog.text = "Аргх! Какого черта вы атаковали мой корабль? У меня нет ни ценностей, ни денег - одни бумаги, в которых вы ни черта не поймете!";
			link.l1 = "Заткнись. Ты проиграл бой, поэтому слушай, что тебе буду говорить я. Мне не нужен твой корабль, и твои бумаги тоже. Мне нужно, чтобы ты передал вот это послание своему шефу - гнусной крысе Лукасу Роденбургу. Это ему привет... от капитана Флитвуда.";
			link.l1.go = "Cureer_abordage_1";			
		break;
		
		case "Cureer_abordage_1":
			dialog.text = "Капитана Флитвуда? Но...";
			link.l1 = "Так вы передадите это письмо, или мне проткнуть вас шпагой? Я могу поискать и другого кандидата на доставку - корабли вашей бандитской Компании я граблю еженедельно.";
			link.l1.go = "Cureer_abordage_2";			
		break;
		
		case "Cureer_abordage_2":
			dialog.text = "Конечно, сэр Флитвуд. Передам.";
			link.l1 = "Вот и замечательно. А теперь мы можем с вами проститься, минхер. Считайте, что вам здорово повезло сегодня. Так что не забудьте сходить в церковь по прибытии!";
			link.l1.go = "Cureer_abordage_3";			
		break;
		
		case "Cureer_abordage_3":
			DialogExit();
			sld = &Characters[sti(pchar.GenQuest.QuestAboardCabinDialogIdx)];
			Lai_SetPlayerType(pchar);
			LAi_RemoveCheckMinHP(sld);
			LAi_SetImmortal(sld, true);
			sld.ShipEnemyDisable  = true;
			pchar.quest.HWICCureer_AfterBattle.over = "yes";
			pchar.quest.HWICCureerOnMapOver.over = "yes";
			AddQuestRecord("Holl_Gambit", "3-39");
			Log_TestInfo("ПИСЬМО ОТДАНО!");
			RemoveItems(PChar, "MC_Letter", 1);
			pchar.questTemp.HWIC.Self = "LetterToLucasSent";
			pchar.quest.Curacao_exploring.win_condition.l1 = "location";
			pchar.quest.Curacao_exploring.win_condition.l1.location = "Curacao";
			pchar.quest.Curacao_exploring.function = "CuracaoExploring";
			DoQuestCheckDelay("LAi_ReloadBoarding", 1.0);
			AddComplexSeaExpToScill(50, 50, 50, 100, 50, 50, 0);
			AddComplexSelfExpToScill(30, 30, 30, 30);
		break;
		
		//Матиас Бек в тюрьме
		case "MatiasBek"://на случай если геймер захочет пообщаться
			dialog.text = "Меня арестовали незаконно! Я не имею к англичанам никакого отношения! Это все интриги Роденбурга. Ничего, прибудет Питер Стайвесант - он во всем разберется!";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "MatiasBek";
		break;
		
		//стражник у входа в резиденцию
		case "QuestGuard":
			dialog.text = "Господин Лукас Роденбург никого не принимает. Будьте любезны покинуть территорию резиденции.";
			link.l1 = "Гм. Понятно. Попробую заглянуть через недельку...";
			link.l1.go = "exit";
			NextDiag.TempNode = "QuestGuard";		
		break;
		
		//Питер Стайвесант
		case "Stivesant":
			dialog.text = "Отправляемся в резиденцию, капитан. Я уже послал своих людей в форт, чтобы получить информацию о Матиасе Беке. Если он действительно в тюрьме, то сейчас его уже освободили и сопровождают в город. Следуйте за мной!";
			link.l1 = "Хорошо, минхер Стайвесант.";
			link.l1.go = "Stivesant_1";			
		break;
		
		case "Stivesant_1":
			DialogExit();
			LAi_ActorGoToLocation(npchar, "reload", "reload3_back", "Villemstad_townhall", "goto", "goto2", "OpenVillemstadResidence", -1);
		break;
		
		case "Stivesant_2":
			dialog.text = "Лукас! Что здесь происходит? Где Матиас Бек? Это правда, что вы отправили его в тюрьму?";
			link.l1 = "Здравствуйте, минхер Стайвесант. Я получил доказательства его связи с английской разведкой и непосредственно с капитаном Флитвудом. По его наводке проклятый британец напал на нашу курьерскую бригантину с целью завладеть секретной перепиской компании.";
			link.l1.go = "Stivesant_3";			
		break;
		
		case "Stivesant_3":
			dialog.text = "Откуда у вас такие сведения?";
			link.l1 = "Об этом засвидетельствовал капитан курьерской бригантины. Ричард Флитвуд абордировал его корабль и отнял бумаги, затем корабль был отпущен. Никто, кроме меня, вас и Матиаса Бека не знал ни маршрута, ни времени движения бригантины.";
			link.l1.go = "Stivesant_4";			
		break;
		
		case "Stivesant_4":
			dialog.text = "И поэтому вы решили, что Флитвуда на бригантину навел Бек? Что за вздор? Флитвуд - обычный пират, он нападает только на торговые корабли. Зачем ему бумаги, в которых, кстати, ничего, кроме бухгалтерских сведений, не содержится?";
			link.l1 = "Минхер, кроме простых отчетов курьер вез и более важные документы Компании. Все они теперь в руках у англичан. Поэтому я принял решение о смещении Бека и помещении под стражу.";
			link.l1.go = "Stivesant_5";			
		break;
		
		case "Stivesant_5":
			dialog.text = "Черт возьми! Но это же самое настоящее самоуправство! Вы отдаете себе отчет в своих действиях, Лукас? Где капитан курьерской бригантины?";
			link.l1 = "Отбыл в Филипсбург, минхер.";
			link.l1.go = "Stivesant_6";			
		break;
		
		case "Stivesant_6":
			dialog.text = "Так-так... Я приказал освободить Бека. Сейчас его сюда доставят. Поговорим втроем...";
			link.l1 = "Ну что же, я не возражаю. Втроем, так втроем.";
			link.l1.go = "Stivesant_7";			
		break;
		
		case "Stivesant_7":
			DialogExit();
			sld = characterFromId("hol_guber");
			ChangeCharacterAddressGroup(sld, "Villemstad_townhall", "reload", "reload1");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocator(sld, "goto", "governor1", "DoubleTalkWithLucas", -1.0);
		break;
		
		case "Bek":
			dialog.text = "Вы поплатитесь за свой произвол, Роденбург! Ваши обвинения смехотворны. Вы даже не позволили мне встретится с капитаном бригантины! Все ваши так назывемые обвинения вы сделали сами, лично, не приведя никаких доказательств\nВидит Бог, я невиновен! У меня нет и не было никаких контактов с англичанами!";
			link.l1 = "Вот как? А откуда же тогда Флитвуд узнал про нашу бригантину, и про то, что на ней перевозились не только бумаги?";
			link.l1.go = "Bek_1";			
		break;
		
		case "Bek_1":
			DialogExit();
			sld = characterFromId("Blaze");
			sld.Dialog.Filename = "Quest\HollandGambit\OtherNPC.c";
			sld.dialog.currentnode = "MC_Diag";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", 0, 0);
		break;
		
		case "MC_Diag":
			dialog.text = "Роденбург лжет. Ричард Флитвуд не мог напасть на курьерскую бригантину.";
			link.l1 = "А вы кто такой, минхер, позвольте спросить? И на каком основании делаете подобные заявления?";
			link.l1.go = "MC_Diag_1";			
		break;
		
		case "MC_Diag_1":
			sld = characterFromId("Blaze");
			LAi_ActorTurnToCharacter(characterFromID("Stivesant"), sld);
			LAi_ActorTurnToCharacter(characterFromID("hol_guber"), sld);
			dialog.text = "Мое имя - " + GetFullName(sld) + ". Я лично уничтожил капитана Флитвуда, организовав негодяю ловушку. Сейчас его останки доедают чайки на пустынном берегу Теркса... Я сам положил конец беспределу этого мерзавца, раз официальные власти оказались неспособны защитить нас, голландских торговых капитанов, от его произвола. И случилось это ДО того, как была ограблена курьерская бригантина\nФлитвуд просто не смог бы этого сделать, поскольку был уже мертв. Узнав в таверне Виллемстада от моряков о захвате курьерского корабля, а также о том, что Матиас Бек арестован, я решил докопаться до сути дела, ибо, как мне было известно, минхер Бек - человек кристально чистой репутации\nПоговорив с матросами в порту, я узнал, что вы расквартировали с вашей шебеки гвардейцев Компании и набрали команду из негодяев всех мастей. Я отправился в море, проследил за вашим кораблем, и, улучив момент, захватил его. Перебив свору нанятых вами головорезов, я допросил китайца Лонгвэя - капитана шебеки. В обмен на свободу он раскрыл все ваши карты, минхер Роденбург\nВы решили узурпировать власть на Кюрасао, а Лонгвэю приказали потопить галеон минхера Стайвесанта. Зная ваши методы, я уверен, что капитан бригантины отбыл не в Филипсбург, а прямиком на дно. Ведь это вы сами организовали нападение на бригантину Компании, чтобы создать прецедент, не так ли? И сделали это при помощи вашего наемного убийцы Якоба ван Берга, о котором мне также поведал Лонгвэй?";
			link.l1 = "Это... это наглая ложь! Что вы несете, сударь?! Вы кто вообще такой?!";
			link.l1.go = "MC_Diag_2";			
		break;
		
		case "MC_Diag_2":
			dialog.text = "Я - свободный капитан, который пожелал очистить море и землю от подонка Флитвуда, и оказавшийся втянутым в ваши политические интриги! Я предупредил минхера Стайвесанта о грозящей ему опасности. И я здесь, чтобы совместно с законной властью положить конец вашим бесчинствам на Кюрасао!";
			link.l1 = "Какая дерзость! Вы ответите за ваши слова, минхер 'свободный капитан'! Вы...";
			link.l1.go = "MC_Diag_3";			
		break;
		
		case "MC_Diag_3":
			DialogExit();
			sld = characterFromId("Stivesant");
			sld.Dialog.Filename = "Quest\HollandGambit\OtherNPC.c";
			sld.dialog.currentnode = "Stivesant_8";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", 0, 0);		
		break;
		
		case "Stivesant_8":
			dialog.text = "Довольно, Лукас. Это вы ответите за свои действия! Увиденного и услышанного мне достаточно. Лукас Роденбург, я арестую вас за попытку силового захвата власти, за покушение на убийство директора Компании и по подозрению в убийстве капитана курьерского корабля\nКроме того, в процессе расследования мы наверняка найдем и другие занятные факты вашей биографии. Вы будете помещены под стражу и доставлены в Амстердам, где предстанете перед судом. Увести его!";
			link.l1 = "Но...";
			link.l1.go = "Stivesant_9";			
		break;
		
		case "Stivesant_9":
			DialogExit();
			SetMainCharacterIndex(GetCharacterIndex("Blaze"));
			PChar = GetMainCharacter();
			PChar.Dialog.Filename = "MainHero_dialog.c";
			LAi_ActorTurnToCharacter(pchar, characterFromID("Lucas"));
			sld = characterFromId("Lucas");
			LAi_SetImmortal(sld, true);//защита от хитреца
			LAi_SetActorType(sld);
			ChangeCharacterAddressGroup(sld, "Villemstad_townhall", "goto", "goto6");
			LAi_ActorGoToLocation(sld, "reload", "reload1", "none", "", "", "LucasGoToPrison", -1);
			for (i=3; i<=5; i++)
			{
			sld = characterFromId("StivesantGuard_"+i);
			LAi_ActorFollow(sld, characterFromID("Lucas"), "", -1);
			}
			EndQuestMovie();
			ChangeShowIntarface();
			LAi_SetActorType(PChar);
			DoQuestFunctionDelay("SecondDayInVillemstad", 6.0);
		break;
		
		case "Stivesant_10":
			dialog.text = "Капитан " + GetFullName(pchar) + "! От лица администрации колонии Виллемстад прошу принять нашу искреннюю благодарность за ваши действия, в результате которых был арестован этот опасный преступник. Также хочу поблагодарить вас от себя лично - возможно, я обязан вам жизнью.";
			link.l1 = "Я сделал это ради блага голландских колоний, минхер.";
			link.l1.go = "Stivesant_11";			
		break;
		
		case "Stivesant_11":
			dialog.text = "Ваша скромность внушает уважение, друг мой. Теперь я хотел бы уладить некоторые формальности: поскольку вы захватили 'Мейфенг' исключительно в благих целях и пошли на это из крайней необходимости, никаких претензий быть не может. Но этот корабль принадлежит Компании, и я прошу вас его вернуть.";
			link.l1 = "Безусловно, минхер.";
			link.l1.go = "Stivesant_12";			
		break;
		
		case "Stivesant_12":
		//удаляем Мейфенг
		DeleteAttribute(pchar, "questTemp.HWIC.TakeQuestShip");//удаляем атрибут квестового корабля
		if(sti(RealShips[sti(pchar.ship.type)].basetype) == SHIP_MAYFANG)
		{
			pchar.Ship.Type = GenerateShipExt(SHIP_TARTANE, true, pchar);
			pchar.Ship.name = "Лодка";
			SetBaseShipData(pchar);
			SetCrewQuantityOverMax(PChar, 0);//сажаем на тартану
		}
		else
		{
			for(i = 1; i < COMPANION_MAX; i++)
			{
			int iTemp = GetCompanionIndex(PChar, i);
			if(iTemp > 0)
				{
				sld = GetCharacter(iTemp);
				if(sti(RealShips[sti(sld.ship.type)].basetype) == SHIP_MAYFANG)
					{
						pchar.questTemp.HWIC.Self.CompanionIndex = sld.Index;
						sld = GetCharacter(sti(pchar.questTemp.HWIC.Self.CompanionIndex));
						RemoveCharacterCompanion(PChar, sld);
						AddPassenger(PChar, sld, false);
					}
				}
			}
		}
			dialog.text = "И я прошу вас зайти завтра в резиденцию - вы будете награждены от лица Республики Свободных Провинций за ваши деяния в ее благо. Прошу вас не покидать город.";
			link.l1 = "Хорошо, минхер. Буду у вас на приеме завтра.";
			link.l1.go = "Stivesant_13";			
		break;
		
		case "Stivesant_13":
			DialogExit();
			sld = characterFromId("hol_guber");
			sld.dialog.currentnode = "Bek_2";
			LAi_ActorDialog(sld, pchar, "", 0, 0);
		break;
		
		case "Bek_2":
			dialog.text = "Я тоже хочу поблагодарить вас, капитан, за вашу предприимчивость и за оказание такой своевременной помощи. Не забудьте придти завтра сюда - я приготовлю для вас ценный подарок.";
			link.l1 = "Спасибо, минхер Бек. Буду обязательно!";
			link.l1.go = "Bek_3";			
		break;
		
		case "Bek_3":
			DialogExit();
			pchar.quest.Award_FromPiter.win_condition.l1 = "Timer";
			pchar.quest.Award_FromPiter.win_condition.l1.date.hour  = 9.0;
			pchar.quest.Award_FromPiter.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.Award_FromPiter.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.Award_FromPiter.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.Award_FromPiter.function = "OpenResidenceDoor";
			bDisableFastReload = false;
			LocatorReloadEnterDisable("Villemstad_town", "reload5_back", false);
			LocatorReloadEnterDisable("Villemstad_town", "reload10_back", false);
			LocatorReloadEnterDisable("Villemstad_town", "reload3_back", true);//закрыть вход в резиденцию
			LocatorReloadEnterDisable("Villemstad_town", "reloadR1", true);//закрыть боковой вход в резиденцию
			AddQuestRecord("Holl_Gambit", "3-53");
			DoQuestReloadToLocation("Villemstad_prison", "goto", "goto23", "TalkWithLucasPrisoner");
			for (i=4; i<=5; i++)
			{
				sld = characterFromId("StivesantGuard_"+i);
				sld.lifeday = 0;//подчистим солдат
			}
		break;
		
		case "Stivesant_14":
			dialog.text = "" + GetFullName(pchar) + ", именем Республики Свободных Провинций, за проявленную инициативу в уничтожении врага голландской нации, государственного преступника Ричарда Флитвуда, вы награждаетесь именным оружием и денежной суммой в размере 100 000 песо. Поздравляю!";
			link.l1 = "Благодарю, минхер Стайвесант!";
			link.l1.go = "Stivesant_15";			
		break;
		
		case "Stivesant_15":
			dialog.text = "Также, за беспрецедентную отвагу, за раскрытие коварного заговора внутри Компании и содействие в поимке бывшего вице-директора Компании, сопряженное с серьезным риском, вы награждаетесь денежной премией в размере 150 000 песо. Также вы получаете право на заключение контрактов с Голландской Вест-Индской Компанией\nУверен, что новый вице-директор всегда сможет найти задание, достойное такого храброго капитана, и щедро оплатить ваши услуги.";
			link.l1 = "Спасибо! Приму это во внимание.";
			link.l1.go = "Stivesant_16";			
		break;
		
		case "Stivesant_16":
			AddMoneyToCharacter(pchar, 250000);
			GiveItem2Character(pchar, "blade_16");
			ChangeCharacterComplexReputation(pchar, "nobility", 5);
			dialog.text = "Ну, и вы всегда можете рассчитывать на мое содействие в любых вопросах, до тех пор, пока действуете на стороне и в интересах Голландии. Далее предоставляю слово губернатору Виллемстада, Матиасу Беку.";
			link.l1 = "";
			link.l1.go = "Stivesant_17";			
		break;
		
		case "Stivesant_17":
			DialogExit();
			LAi_SetPlayerType(pchar);
			sld = characterFromId("hol_guber");
			LAi_SetActorType(sld);
			sld.dialog.currentnode = "Bek_4";
			LAi_ActorDialog(sld, pchar, "", -1, 0);		
		break;
		
		case "Bek_4":
			dialog.text = "Выражаю вам свою искреннюю благодарность, капитан, за проявленную храбрость и смекалку в раскрытии государственного заговора. Я хочу подарить вам вот этот ценный навигационный прибор - незаменимая для военного моряка вещь.";
			link.l1 = "Спасибо, минхер Бек.";
			link.l1.go = "Bek_5";			
		break;
		
		case "Bek_5":
			GiveItem2Character(pchar, "bussol");
			dialog.text = "И знайте: в моем лице вы обрели друга, а это многое значит. Вы всегда желанный гость в моей резиденции. Заходите в любое время, по любым вопросам - я буду рад оказать вам любую помощь, которая потребуется.";
			link.l1 = "Рад слышать это, минхер!";
			link.l1.go = "Bek_6";			
		break;
		
		case "Bek_6"://наведем порядок в городе
			DialogExit();
			AddQuestRecord("Holl_Gambit", "3-54");
			LAi_SetPlayerType(pchar);
			sld = characterFromId("hol_guber");
			LAi_SetHuberStayType(sld);
			sld.Dialog.Filename = "Common_Mayor.c";//patch-8
			sld.dialog.currentnode = "First time";
			sld.quest.meeting = "1";
			for (i=1; i<=3; i++)
			{
				sld = characterFromId("StivesantGuard_"+i);
				sld.lifeday = 0;//подчистим солдат
			}
			sld = characterFromId("Stivesant");
			LAi_ActorGoToLocator(sld, "goto", "goto6", "StivesantSitDown", -1);
			bDisableFastReload = false;
			LocatorReloadEnterDisable("Villemstad_town", "reload1_back", false);
			LocatorReloadEnterDisable("Villemstad_town", "reload2_back", false);
			LocatorReloadEnterDisable("Villemstad_town", "gate_back", false);
			AddCharacterExpToSkill(pchar, "Fortune", 100);//везение
		break;
		
		case "Bek_7":
			dialog.text = "Голландия гордится вами, минхер. На таких капитанах, как вы, и зиждется сила голландского флота в Карибском бассейне. Прошу вас, вот ваша награда.";
			link.l1 = "Благодарю, минхер. Служба на благо Голландии - честь для меня!";
			link.l1.go = "Bek_8";
		break;
		
		case "Bek_8":
			TakeNItems(pchar, "gold_dublon", 1000);
			ChangeCharacterComplexReputation(pchar,"authority", 5);
			ChangeCharacterNationReputation(pchar, HOLLAND, 20);
			DialogExit();
			sld = characterFromId("Lucas");
			LAi_SetActorType(sld);
			sld.dialog.currentnode = "LucasAward_2";
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "Stivesant_18":
			dialog.text = "Рад вас видеть. Как у вас дела?";
			link.l1 = "У меня все хорошо. Я просто зашел вас навестить.";
			link.l1.go = "exit";	
			NextDiag.TempNode = "Stivesant_18";
		break;
		
		// Jason НСО
		case "Stivesant_19":
			if (ChangeCharacterHunterScore(pchar, "holhunter", 0) > 10)
			{
				dialog.text = "О! Кто пришел! Это же сам " + GetFullName(pchar) + ". Мы как раз недавно высылали охотников за головами, чтобы они привели вас сюда. И знаете, это уже встало нам в кругленькую сумму.";
				link.l1 = "Э... пожалуй, мне пора.";
				link.l1.go = "arest";
				break;
			}
			if (pchar.questTemp.Patria == "epizode_4" && pchar.model == "Sharle_6")
			{
				dialog.text = "Вы капитан военно-морского флота Франции? Хорошо, у меня хоть и нет времени на посторонние дела, я вас выслушаю. Что привело вас сюда?";
				link.l1 = "Минхер Стайвесант, я прибыл с Сент-Кристофера с посланием от генерал-губернатора французских колоний шевалье Филиппа де Пуанси.";
				link.l1.go = "Stivesant_20";
			}
			else
			{
				dialog.text = "Прошу прощения, капитан, но я сейчас очень занят и не могу уделить вам ни минуты времени. Обратитесь к минхеру Матиасу Беку, пусть он вас выслушает.";
				link.l1 = "Гм...";
				link.l1.go = "Stivesant_19_1";
			}
		break;
		
		case "Stivesant_19_1":
			DialogExit();
			npchar.dialog.currentnode = "Stivesant_19";
		break;
		
		case "Stivesant_20":
			sld = characterFromId("Patria_FlautCap");
			dialog.text = "От шевалье де Пуанси? Вот уж не ожидал, что на этот раз так рано... Кхм... Как дела у шевалье?";
			link.l1 = "Все хорошо, минхер. Месье де Пуанси поручил мне передать вам вот это письмо и доставить ответ на него. Также в мою задачу входило сопроводить флейт '"+sld.ship.name+"' с грузом для вашей Компании в порт Виллемстада. Судно стоит на рейде, груз в целости.";
			link.l1.go = "Stivesant_21";
		break;
		
		case "Stivesant_21":
			dialog.text = "Флейт с грузом для Компании? Как интересно... А письмо, капитан?";
			link.l1 = "Вот оно, пожалуйста.";
			link.l1.go = "Stivesant_22";
		break;
		
		case "Stivesant_22":
			RemoveItems(pchar, "Reserve_item_01", 1);
			dialog.text = "Так-так... (читает). Инспекция из метрополии, значит... Кхм... Хе-хе, ну-ну... Занятно, хе-хе... Кстати, капитан, я слышал, Франция начала самую настоящую войну против Испании на Карибах? Осада и разрушение форта Сан-Хосе, уничтожение испанской военной эскадры у восточного побережья Кубы...";
			link.l1 = "У западного побережья Эспаньолы вблизи Порт-о-Пренса, минхер. А осада Сан-Хосе преследовала целью получить материальное возмещение от испанцев за предшествовавшее нападение на Сен-Пьер. Наши отношения с Испанией уже давно не отличаются теплотой и дружелюбием... Когда мне зайти за ответом?";
			link.l1.go = "Stivesant_23";
		break;
		
		case "Stivesant_23":
			dialog.text = "Я не буду вас задерживать, капитан, вы же человек военный, у вас наверняка много дел, да и шевалье, уверен, с нетерпением ждет вашего возвращения. Будьте так любезны подождать прямо здесь, в приемной, два часа, и я подготовлю вам ответ на депешу. Присядьте, отдохните, сейчас вам принесут рому или вина, как пожелаете...";
			link.l1 = "Благодарю, минхер, предпочту бокал хорошего вина...";
			link.l1.go = "Stivesant_24";
		break;
		
		case "Stivesant_24":
			chrDisableReloadToLocation = true;//закрыть локацию
			pchar.quest.Patria_CureerTimeOver.over = "yes"; //снять таймер
			pchar.quest.Patria_CureerFail.over = "yes"; //снять прерывание
			sld = characterFromId("Patria_FlautCap");
			RemoveCharacterCompanion(pchar, sld);
			sld.lifeday = 0;
			DialogExit();
			npchar.dialog.currentnode = "Stivesant_25";
			LAi_SetActorType(npchar);
			ChangeCharacterAddressGroup(npchar, "Villemstad_townhall", "goto", "goto6");
			LAi_ActorGoToLocation(npchar, "reload", "reload2", "none", "", "", "Patria_StivesantWait", -1);
			pchar.questTemp.Patria = "epizode_4_return";
		break;
		
		case "Stivesant_25":
			GiveItem2Character(pchar, "Reserve_item_01");
			ChangeItemDescribe("Reserve_item_01", "itmdescr_Reserve_item_01_2");
			dialog.text = "Ответ для месье де Пуанси готов. Вот, возьмите, пожалуйста... Счастливого пути, капитан.";
			link.l1 = "Спасибо, минхер. До свидания!";
			link.l1.go = "Stivesant_26";
		break;
		
		case "Stivesant_26":
			DialogExit();
			npchar.dialog.currentnode = "Stivesant_19";
			chrDisableReloadToLocation = false;
			AddQuestRecord("Patria", "23");
			SetFunctionTimerCondition("Patria_CureerBackOver", 0, 0, 31, false);
		break;
		
		case "Stivesant_27":
			if (ChangeCharacterHunterScore(pchar, "holhunter", 0) > 10)
			{
				dialog.text = "О! Кто пришел! Это же сам " + GetFullName(pchar) + ". Мы как раз недавно высылали охотников за головами, чтобы они привели вас сюда. И знаете, это уже встало нам в кругленькую сумму.";
				link.l1 = "Э... пожалуй, мне пора.";
				link.l1.go = "arest";
				break;
			}
			if (pchar.questTemp.Patria == "epizode_6" && pchar.model == "Sharle_6")
			{
				dialog.text = "Вы снова с посланием от генерал-губернатора Филиппа де Пуанси, так?";
				link.l1 = "Да, минхер Стайвесант. У берегов Синт-Маартена произошло неприятное недоразумение - корабль, на борту которого был инспектор из Парижа, барон Ноэль Форже, был обстрелян фортом Филипсбурга, и...";
				link.l1.go = "Stivesant_28";
			}
			else
			{
				dialog.text = "Прошу прощения, капитан, но я сейчас очень занят и не могу уделить вам ни минуты времени. Обратитесь к минхеру Матиасу Беку, пусть он вас выслушает.";
				link.l1 = "Гм...";
				link.l1.go = "Stivesant_27_1";
			}
		break;
		
		case "Stivesant_27_1":
			DialogExit();
			npchar.dialog.currentnode = "Stivesant_27";
		break;
		
		case "Stivesant_28":
			if (pchar.questTemp.HWIC.Detector == "holl_win" || pchar.questTemp.HWIC.Detector == "self_win")
			{
				dialog.text = "И поэтому вы здесь, капитан. Не буду вдаваться в дипломатические дискуссы: передайте шевалье, что он больше не в деле на Синт-Маартене. Хватит с него. А касательно инспекции из метрополии - пусть придумает что-нибудь, для де Пуанси перевернуть все с ног на голову никогда не составляло труда.";
				link.l1 = "Так и передать?";
				link.l1.go = "Stivesant_29";
			}
			else
			{
				dialog.text = "И поэтому вы здесь, капитан. Не буду вдаваться в дипломатические дискуссы: ваш шеф чрезмерно зажрался на Синт-Маартене, поэтому настало время умерить его ненасытные аппетиты. И он это, я думаю, прекрасно понял. К вам, капитан Шарль де Мор, у нас тоже есть вопросы по недавним событиям, связанным с английским разбойником Ричардом Флитвудом, поэтому вы здесь задерживаетесь\nСержант! Примите оружие у капитана и проводите в комендатуру!";
				link.l1 = "Мне кажется, что задерживать французского офицера на при исполнении им служебного долга недопустимо!";
				link.l1.go = "Stivesant_31";
			}
		break;
		
		case "Stivesant_29":
			dialog.text = "Слово в слово, капитан. Ваш командир все поймет, а вам вникать необязательно, это ничего не изменит. Всего доброго. Сержант, проводите месье Шарля де Мора к выходу!";
			link.l1 = "...";
			link.l1.go = "Stivesant_30";
		break;
		
		case "Stivesant_30":
			DialogExit();
			DoQuestReloadToLocation("Villemstad_town", "reload", "reload3", "Patria_DiplomatGetOut");
		break;
		
		case "Stivesant_31":
			dialog.text = "К сожалению, у меня другое мнение. Сержант! В случае сопротивления применяйте силу!";
			link.l1 = "Вы просто еще не знаете, с кем связались, минхер...";
			link.l1.go = "Stivesant_32";
		break;
		
		case "Stivesant_32":
			DialogExit();
			Patria_DiplomatFight();
		break;
		
		case "Stivesant_33":
			dialog.text = "Немного странно видеть вас, капитан Шарль де Мор, в этой роли... Надеюсь, вы сможете гарантировать неприкосновенность лиц, пришедших к вам на переговоры.";
			link.l1 = "Можете быть в этом уверены, минхер Стайвесант.";
			link.l1.go = "Stivesant_34";
		break;
		
		case "Stivesant_34":
			dialog.text = "Итак, вы можете дать мне для прочтения соглашение, которое вы подготовили? Я так понимаю, там будет то, что содержалось в письме?";
			link.l1 = "Именно, минхер, только в официальной форме. Со стороны Франции - восстановление отношений до нейтральных, отказ от любых притязаний на остров Синт-Маартен. Со стороны Англии - прекращение торговой войны. Подробности все описаны... Ну и, конечно, репарации, связанные с возмещением ущерба, который мы понесли в связи с развязанными вами военными действиями.";
			link.l1.go = "Stivesant_35";
		break;
		
		case "Stivesant_35":
			dialog.text = "Будьте любезны дать мне этот документ.";
			link.l1 = "Пожалуйста.";
			link.l1.go = "Stivesant_36";
		break;
		
		case "Stivesant_36":
			dialog.text = "...(читает)...";
			link.l1 = "...";
			link.l1.go = "Stivesant_37";
		break;
		
		case "Stivesant_37":
			LAi_Fade("", "");
			dialog.text = "Поскольку вы не оставили мне выбора, я готов подписать это соглашение. Сохранность Виллемстада и его жителей для меня превыше всего.";
			link.l1 = "Тогда скрепляем все три экземпляра подписями. Я уполномочен генерал-губернатором Филиппом де Пуанси завизировать документ со стороны Франции, полковник Дойли подпишет со стороны Англии.";
			link.l1.go = "Stivesant_38";
		break;
		
		case "Stivesant_38":
			dialog.text = "...(подписывает)...";
			link.l1 = "Отлично! Теперь подпишем мы...";
			link.l1.go = "Stivesant_39";
		break;
		
		case "Stivesant_39":
			LAi_Fade("", "");
			dialog.text = "Сейчас, я полагаю, вы снимете осаду с города?";
			link.l1 = "Вне всякого сомнения. Надеюсь, что все пункты соглашения будут исполняться голландской стороной без нарушений.";
			link.l1.go = "Stivesant_40";
		break;
		
		case "Stivesant_40":
			dialog.text = "Если не последует нарушений со стороны Англии или Франции, то мы будем соблюдать условия договора, не беспокойтесь.";
			link.l1 = "Торговать всегда лучше, чем воевать, минхер Стайвесант. А теперь можете спокойно возвращаться в Виллемстад. Осада будет снята и наша эскадра вскоре покинет воды Кюрасао.";
			link.l1.go = "Stivesant_41";
		break;
		
		case "Stivesant_41":
			DialogExit(); // Стайвесант уходит, подходит Дойли
			Patria_CuracaoStivesantGo();
		break;
		
		case "Stivesant_42":
			dialog.text = "Итак, это вы - барон Ноэль Форже? Ба, да тут еще и месье Шарль де Мор собственной персоной! Здравствуйте, здравствуйте, вице-адмирал! Недаром про вас идет слава самого ловкого интригана архипелага - никогда не знаешь, на чьей вы стороне в данный момент...";
			link.l1 = "В данный момент вице-адмирал на стороне короля Франции и его законного представителя, то есть меня.";
			link.l1.go = "Stivesant_43";
		break;
		
		case "Stivesant_43":
			dialog.text = "Король далеко отсюда, как и вся Франция, барон, а вот Сент-Кристофер и шевалье Пуанси - близко. Истинный хозяин французских колоний именно он. Де-факто... Впрочем, вы здесь за тем, чтобы получить нечто, копрометирующее Пуанси в глазах министра финансов?";
			link.l1 = "Именно, минхер.";
			link.l1.go = "Stivesant_44";
		break;
		
		case "Stivesant_44":
			dialog.text = "Такие документы у меня есть. Это целый гроссбух с нашей с Пуанси бухгалтерией по руднику и некоторым прочим делам. Также в нем есть целый ворох бумаг, относящихся к этой бухгалтерии, с личной подписью Филиппа де Пуанси. Я вам гарантирую, что содержимое этих бумаг в руках заинтересованного человека утопит шевалье глубже дна Карибского моря.";
			link.l1 = "Что вы хотите за этот гроссбух?";
			link.l1.go = "Stivesant_45";
		break;
		
		case "Stivesant_45":
			dialog.text = "О-о, сущие пустяки. Миллион песо серебром.";
			link.l1 = "Миллион песо?!!";
			link.l1.go = "Stivesant_46";
		break;
		
		case "Stivesant_46":
			dialog.text = "Так точно, барон. Эта сумма хотя бы частично покроет мне убытки, нанесенные недавней войной. Я дам вам совет: обратитесь к месье Шарлю де Мору. За время службы у Пуанси и мммм... других персон, он наверняка сколотил огромное состояние, и достать миллион не будет для него особой проблемой. Я в этом практически уверен\nСрок вам даю - один месяц. По истечении этого времени, если вы не принесете указанную сумму, я отправлю письмо шевалье, в котором опишу подробности вашего визита ко мне. Что за этим последует - полагаю, вы догадываетесь.";
			link.l1 = "Это очень похоже на шантаж! Вы же понимаете, что у меня не может быть с собой в колониях миллиона!";
			link.l1.go = "Stivesant_47";
		break;
		
		case "Stivesant_47":
			dialog.text = "Конечно, понимаю. Поэтому сразу указал вам человека, у которого этот миллион есть. Если же месье де Мор откажет вам, то лучше всего для вас, барон, будет уплыть отсюда в Европу раньше, чем шевалье получит мое письмо, иначе вы рискуете остаться здесь навсегда. Ну а месье де Мор... конечно, он лишится своего адмиральского чина, но выкрутится... и, возможно, даже ликвидирует Пуанси своими методами, что меня вполне устроит\nНу, господа, вы меня услышали. Жду вас с миллионом в течение месяца у себя в резиденции. Свободный вход и выход гарантирую. Всего доброго!";
			link.l1 = "...";
			link.l1.go = "Stivesant_48";
		break;
		
		case "Stivesant_48":
			DialogExit();
			LAi_SetActorType(pchar);
			SetMainCharacterIndex(GetCharacterIndex("Blaze"));
			pchar = GetMainCharacter();			
			LAi_SetPlayerType(pchar);
			locCameraTarget(pchar);
			locCameraFollow();
			EndQuestMovie();
			InterfaceStates.Buttons.Save.enable = true;
			bDisableCharacterMenu = false;
			sld = CharacterFromID("Noel");
			sld.dialog.currentnode = "noel_84";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.5);
			sld = CharacterFromID("Stivesant");
			LAi_ActorRunToLocation(sld, "reload", "reload1_back", "none", "", "", "Patria_CondotierStivesantInHall", 12.0);
			for (i=1; i<=3; i++)
			{
				sld = CharacterFromID("Stivesant_sold_"+i);
				LAi_SetActorType(sld);
				LAi_ActorRunToLocation(sld, "reload", "reload1_back", "none", "", "", "", 10.0);
			}
		break;
		
		case "Stivesant_49":
			if (sti(pchar.money) >= 1000000)
			{
				dialog.text = "Я даже не сомневался, вице-адмирал Шарль де Мор, что вы принесете мне эти деньги. Пожалуй, я даже маловато с вас запросил, ну да ладно... Барон - лишь пешка в вашей очередной игре, так? Чина и денег вам недостаточно, теперь вы желаете занять место де Пуанси, я прав? Согласитесь, миллион - невелика плата за должность генерал-губернатора французских колоний! Вы отобьете их за считаные месяцы, учитывая вашу железную хватку.";
				link.l1 = "Возьмите ваш миллион, минхер. И я бы хотел получить обещаный гроссбух.";
				link.l1.go = "Stivesant_50";
			}
			else
			{
				dialog.text = "Вам лучше сосредоточиться на сборе миллиона, месье, а не тратить время на пустые визиты.";
				link.l1 = "...";
				link.l1.go = "Stivesant_49_1";
			}
		break;
		
		case "Stivesant_49_1":
			DialogExit();
			npchar.dialog.currentnode = "Stivesant_49";
		break;
		
		case "Stivesant_50":
			pchar.quest.Patria_CondotierStivesantTimeOver.over = "yes"; // снять таймер
			AddMoneyToCharacter(pchar, -1000000);
			GiveItem2Character(pchar, "Reserve_item_01");
			ref itm = ItemsFromID("Reserve_item_01");
			itm.picIndex = 15;
			itm.picTexture = "ITEMS_26";
			itm.price = 0;
			itm.Weight = 2.0;
			itm.name = "itmname_Reserve_item_01_1";
			ChangeItemDescribe("Reserve_item_01", "itmdescr_Reserve_item_01_4");
			dialog.text = "Конечно, вице-адмирал. И не хмурьтесь так: когда вы станете генерал-губернатором, вы увидите, что Голландская Вест-Индская торговая Компания - более выгодный деловой партнер, чем жадные и воинственные англичане. Вы разве не знаете, что если дать англичанину палец, он заберет всю руку? Если нет, то узнаете. Так что я с вами не прощаюсь. Держите свои бумаги. Надеюсь, ваш барон будет достаточно компетентен, чтобы уничтожить шевалье.";
			link.l1 = "Благодарю. Всего доброго, минхер Стайвесант.";
			link.l1.go = "Stivesant_51";
		break;
		
		case "Stivesant_51":
			DialogExit();
			AddQuestRecord("Patria", "84");
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload2", "none", "", "", "", -1);
			pchar.quest.Patria_CondotierCabin.win_condition.l1 = "location";
			pchar.quest.Patria_CondotierCabin.win_condition.l1.location = "Curacao";
			pchar.quest.Patria_CondotierCabin.function = "Patria_CondotierCabin";
		break;
		
		case "vanberg_sold":
			dialog.text = "Ха-ха! Вы только посмотрите! Якоб был прав, как всегда - этот хитрец направился на остров не просто так. Похоже, в этом сундучке целая куча золота. Неосторожно было с твоей стороны, приятель, явиться сюда в одиночку. Ну да ладно, нам проще будет...";
			link.l1 = "Выследили, гады! Не ожидал... Ну, псы, я вам так просто не дамся!";
			link.l1.go = "vanberg_sold_1";			
		break;
		
		case "vanberg_sold_1":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешить драться
			for (i=1; i<=4; i++)
			{
				sld = characterFromId("vanberg_sold_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "PrepareMassakraInShore");
			AddDialogExitQuest("MainHeroFightModeOn");			
		break;
		
		case "Abihouselady":
			dialog.text = "Вы кого-то ищете?";
			link.l1 = "Да, ищу. А где Соломон и Абигайль Шнеур?";
			link.l1.go = "Abihouselady_1";			
		break;
		
		case "Abihouselady_1":
			dialog.text = "Они здесь больше не живут. Этот дом стал им не по карману, и они переехали в лачугу на берегу моря. Абигайль работает прислугой у губернатора, а Соломон... ну, вы всегда можете найти его в таверне. Он не выдержал невзгод и запил\nБедняжка Абигайль, она трудится целыми днями, чтобы заработать на себя и на содержание своего отца. А ведь ее руки добивался сам минхер Роденбург... пока его не арестовали. Вот это я называю - судьба...";
			link.l1 = "Да уж.. Ладно, спасибо за информацию. Мне пора.";
			link.l1.go = "Abihouselady_2";
		break;
		
		case "Abihouselady_2":
			DialogExit();
			NextDiag.CurrentNode = "Abihouselady_3";
		break;
		
		case "Abihouselady_3":
			dialog.text = "Вы еще что-то хотели узнать, минхер?";
			link.l1 = "Да нет, ничего.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Abihouselady_3";
		break;
		
		//удаление Мейфенг при провале квеста
		case "TempOffGuard":
			DeleteAttribute(pchar, "questTemp.HWIC.TakeQuestShip");//удаляем атрибут квестового корабля
			if(sti(RealShips[sti(pchar.ship.type)].basetype) == SHIP_MAYFANG)
			{
				pchar.Ship.Type = GenerateShipExt(SHIP_TARTANE, true, pchar);
				pchar.Ship.name = "Лодка";
				SetBaseShipData(pchar);
				SetCrewQuantityOverMax(PChar, 0);//сажаем на тартану
			}
			else
			{
				for(i = 1; i < COMPANION_MAX; i++)
				{
						iTemp = GetCompanionIndex(PChar, i);
					if(iTemp > 0)
					{
						sld = GetCharacter(iTemp);
						if(sti(RealShips[sti(sld.ship.type)].basetype) == SHIP_MAYFANG)
						{
							pchar.questTemp.HWIC.Self.CompanionIndex = sld.Index;
							sld = GetCharacter(sti(pchar.questTemp.HWIC.Self.CompanionIndex));
							RemoveCharacterCompanion(PChar, sld);
							AddPassenger(PChar, sld, false);
						}
					}
				}
			}
			dialog.text = "Капитан, вы незаконным способом присвоили себе корабль Голландской Вест-Индской Компании. Я уполномочен конфисковать его у вас, а в случае сопротивления - применить силу без колебаний. Это приказ Питера Стайвесанта.";
			link.l1 = "Ну что же, раз самого Питера Стайвесанта... Я не буду ссориться с Голландией из-за какого-то корабля. Забирайте.";
			link.l1.go = "TempOffGuard_1";			
		break;
		
		case "TempOffGuard_1":
			dialog.text = "Рад, что вы проявили похвальное благоразумие.";
			link.l1 = "...";
			link.l1.go = "TempOffGuard_2";
		break;
		
		case "TempOffGuard_2":
			DialogExit();
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "", 10.0);
			chrDisableReloadToLocation = false;//открыть локацию
			DeleteAttribute(pchar, "questTemp.HWIC.TakeQuestShip");
		break;
		
		// Jason НСО
		case "arest":
			dialog.text = "Конечно пора, вас проводят. Стража! Взять его!";
		    link.l1 = "Ну, уж нет!";
		    link.l1.go = "fight";
		break;
		
		case "fight":
            Pchar.quest.ArestInResidenceEnd.win_condition.l1          = "ExitFromLocation";
		    Pchar.quest.ArestInResidenceEnd.win_condition.l1.location = Pchar.location;
		    Pchar.quest.ArestInResidenceEnd.win_condition             = "ArestInResidenceEnd";
		    Pchar.quest.ArestInResidenceEnd.ResidenceLocation = Pchar.location;
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_LockFightMode(Pchar, true); // ножками путь убегает
		    LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
		    LAi_group_Attack(NPChar, Pchar); // не работает на бессмертного мера :(
			i = GetCharIDXByParam("CityType", "location", Pchar.location); // фантом солдат
			if (i != -1)
			{
			    LAi_group_Attack(&Characters[i], Pchar);
			}
		break;
		
		//замечание по обнаженному оружию от персонажей типа citizen
		case "CitizenNotBlade":
			dialog.text = NPCharSexPhrase(NPChar, "Послушайте, я, как гражданин этого города, прошу вас не ходить у нас с обнаженным клинком.", "Знаете, я, как гражданка этого города, прошу вас не ходить у нас с обнаженным клинком.");
			link.l1 = LinkRandPhrase("Хорошо.", "Ладно.", "Как скажете...");
			link.l1.go = "exit";
		break;
	}
}