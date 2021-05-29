// Бесчестный конкурент
void ProcessDialogEvent()
{
	ref sld, NPChar;
	aref Link, NextDiag;
	int i;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "Явный баг. Сообщите Jason'у, как и при каких обстоятельствах его получили.";
			link.l1 = "Обязательно сообщу!";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
		case "ShadowGuarder":
			dialog.text = "Чего тебе надо?";
			link.l1 = "Ты - "+pchar.questTemp.Shadowtrader.Guardername+"? Меня прислал хозяин местного магазина. Он тебя уже заждался, и требует, чтобы ты немедленно отправился к нему.";
			link.l1.go = "ShadowGuarder_1";
		break;
	
		case "ShadowGuarder_1":
			dialog.text = "А-а, а я-то его здесь жду! Мне же сказали, что он придет в таверну! Хорошо, я уже иду.";
			link.l1 = "Вот и хорошо!";
			link.l1.go = "ShadowGuarder_2";
		break;
	
		case "ShadowGuarder_2":
			DialogExit();
			sld = characterFromId("ShadowGuarder");	
			LAi_SetStayType(sld);
			GetCharacterPos(pchar, &locx, &locy, &locz);
			ChangeCharacterAddressGroup(sld, pchar.questTemp.Shadowtrader.City + "_tavern", "goto", LAi_FindNearestFreeLocator("goto", locx, locy, locz));
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload1_back", pchar.questTemp.Shadowtrader.City +"_store", "goto", "goto2", "", -1);
			pchar.questTemp.Shadowtrader = "begin";
		break;
	
		case "ShadowAgent":
			dialog.text = "Доброй ночи, капитан. Пришли за дешевыми товарами, хе-хе? Следуйте за мной!";
			link.l1 = "Хорошо.";
			link.l1.go = "ShadowAgent_1";
		break;
	
		case "ShadowAgent_1":
			DeleteAttribute(pchar, "questTemp.Shadowtrader.SeekTrader");
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "quest", "quest2", "CommonFlamHouse", "barmen", "stay", "Shadow_inRoom", 40);
		break;
	
		case "ShadowTrader":
			dialog.text = "Доброй ночи, господин. Приятно познакомиться с новым клиентом, хе-хе. Представимся: меня зовут " + GetFullName(npchar) + ". У меня самые дешевые товары в этом городе, смею уверить.";
			link.l1 = "Ну вот мы и встретились... " + npchar.name + ". Пожалуй, я тебя разочарую: я разыскал тебя не для торговли, а чтобы пресечь твои грязные делишки. Уж очень много ты попортил крови одному человеку в этом городе. Так много, он жаждет закрытия твоей лавочки... любой ценой.";
			link.l1.go = "ShadowTrader_1";
			link.l2 = "Ага, вот ты и попался, каналья! Разве тебе не известно, что коммерческая деятельность без уплаты налогов в городскую казну является серьезным преступлением? " + GetFullName(npchar) + ", именем закона ты арестован и будешь препровожден в тюрьму, а товар подлежит конфискации! За дверью отряд солдат, так что без глупостей, уважаемые!";
			link.l2.go = "ShadowTrader_2";
		break;
	
		case "ShadowTrader_1":
			dialog.text = "Вот как? Не ожидал... Кого вы мне привели? Это же подстава! Я даже догадываюсь, кто его нанял! Закрыть любой ценой... а ну, ребята, в расход его!";
			link.l1 = "Держитесь, канальи!";
			link.l1.go = "ShadowTrader_fight";
			NextDiag.currentnode = "ShadowTrader_6";
		break;
	
	case "ShadowTrader_2":
		dialog.text = "Ой... офицер, послушайте! Давайте договоримся. Вы же разумный человек! Я заплачу вам 5 000 песо, и вы дадите нам уйти через второй этаж. Товары тоже заберете... вам ведь это нужно, да? Зачем вам я? Я сегодня же покину город и никто ничего не узнает. А денежки будут у вас. По рукам, офицер?";
		link.l1 = "Ты что же, негодяй, решил, что за такую смехотворную сумму я буду марать честь мундира?";
		link.l1.go = "ShadowTrader_3";
		break;
	
	case "ShadowTrader_3":
		dialog.text = "Хорошо-хорошо, офицер, возьмите все, что у меня есть - 10 000 песо. У меня нет больше, клянусь!";
		link.l1 = "Хм... Если я тебя задержу, то, пожалуй, все твои деньги конфискуют... а, ладно! Незаконная торговая точка закрыта, товар конфискован... Давай сюда монеты и проваливай, и чтобы я духу твоего в этом городе больше не видел!";
		link.l1.go = "ShadowTrader_4";
		break;
		
	case "ShadowTrader_4":
			dialog.text = "Спасибо, спасибо, господин офицер! Вот ваши деньги, а меня вы больше здесь не увидите. Уходим!";
			link.l1 = "Давай шевелись, или мне все-таки придется арестовать тебя!";
			link.l1.go = "ShadowTrader_escape";
		break;
	
		case "ShadowTrader_fight":
			LAi_SetPlayerType(pchar);
			for (i=1; i<=2; i++)
			{
				sld = characterFromId("ShadowAgent_"+i);	
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
				sld.nation = PIRATE;
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
            LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
            LAi_group_SetCheck("EnemyFight", "ShadowTrader_afterfight");
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
	
		case "ShadowTrader_escape"://напугали
			AddMoneyToCharacter(pchar, 10000);
			LAi_SetPlayerType(pchar);
			for (i=1; i<=2; i++)
			{
				sld = characterFromId("ShadowAgent_"+i);	
				LAi_SetActorType(sld);
				LAi_ActorRunToLocation(sld, "reload", "reload3", "none", "", "", "", 7.0);
			}
			sld = characterFromID("ShadowTrader"); 
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "reload3", "none", "", "", "", 7.0);
			DialogExit();
			DoQuestFunctionDelay("ShadowTrader_final", 9.0);
			pchar.questTemp.Shadowtrader.End.Escape = "true";
			AddQuestRecord("Shadowtrader", "8");
			AddCharacterExpToSkill(pchar, "Leadership", 200);//авторитет
			AddCharacterExpToSkill(pchar, "Fortune", 250);//везение
			AddCharacterExpToSkill(pchar, "Sneak", 300);//скрытность
		break;
	
		case "ShadowTrader_6":
			dialog.text = "Ай! Пощади, не убивай меня! Я отдам тебе всё, что у меня есть!";
			link.l1 = "Все, что у тебя есть, будет конфисковано властями. Или ты и вправду решил, что я сейчас после всего произошедшего буду перетаскивать товары к себе на корабль?";
			link.l1.go = "ShadowTrader_7";
		break;
	
		case "ShadowTrader_7":
			dialog.text = "Я... я отдам тебе все мои деньги и личные вещи! Только отпусти меня! Я сегодня же покину этот город и больше здесь не появлюсь!";
			link.l1 = "Ладно. Выворачивай карманы, а затем выметайся. И только попробуй вновь развернуть свою деятельность в этом городе - второй раз не пощажу.";
			link.l1.go = "ShadowTrader_free";
			link.l2 = "Нет, мерзавец. Тебе не откупиться от меня. С такими подонками можно бороться только одним способом - сталью и свинцом!";
			link.l2.go = "ShadowTrader_killed";
		break;
		
		case "ShadowTrader_free"://отпустили
			AddMoneyToCharacter(pchar, 20550);
			TakeNItems(pchar, "jewelry1", rand(5));
			TakeNItems(pchar, "jewelry2", rand(20));
			TakeNItems(pchar, "jewelry5", rand(20));
			PlaySound("interface\important_item.wav");
			Log_Info("Вы получили предметы");
			LAi_SetPlayerType(pchar);
			sld = characterFromID("ShadowTrader"); 
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "reload3", "none", "", "", "", 5.0);
			DialogExit();
			DoQuestFunctionDelay("ShadowTrader_final", 7.0);
			pchar.questTemp.Shadowtrader.End.Free = "true";
			AddQuestRecord("Shadowtrader", "9");
			ChangeCharacterComplexReputation(pchar,"nobility", 5); 
			AddComplexSelfExpToScill(70, 70, 70, 70);
			AddCharacterExpToSkill(pchar, "Leadership", 100);//авторитет
			AddCharacterExpToSkill(pchar, "Fortune", 100);//везение
		break;
	
		case "ShadowTrader_killed":
			DialogExit();
			LAi_SetImmortal(npchar, false);
			LAi_SetActorType(pchar);
			LAi_ActorAnimation(pchar, "Shot", "ShadowTrader_killed_end", 1.3);
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}