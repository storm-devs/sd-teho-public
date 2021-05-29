void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, Diag;
	int i;
	string sTemp;
	
	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(Diag, NPChar.Dialog);

	switch(Dialog.CurrentNode)
	{
		case "exit":
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();			
		break;
		//----------------- уничтожение банды ----------------------
		case "DestroyGang_begin":
			chrDisableReloadToLocation = false;
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false); //боевке можно
			DeleteAttribute(&locations[FindLocation(pchar.GenQuest.DestroyGang.Location)], "DisableEncounters"); //энкаунтеры можно 
			for(i = 1; i <= 3; i++)
			{
				if (GetCharacterIndex("MayorQuestGang_" + i) == -1) continue;
				sld = CharacterFromID("MayorQuestGang_" + i);
				LAi_type_actor_Reset(sld);
				LAi_RemoveCheckMinHP(sld);
			}
			sTemp = GetFullName(&characters[GetCharacterIndex(pchar.GenQuest.DestroyGang.MayorId)]);
			dialog.text = LinkRandPhrase("Деньги на бочку "+ GetSexPhrase("приятель","подруга") +"! Меня зовут " + GetFullName(npchar) + ", и я не терплю возражений в свой адрес...",
				"Покажи-ка мне содержимое своего кошелька, "+ GetSexPhrase("приятель","подруга") +", и побыстрее! Меня зовут " + GetFullName(npchar) + ", и, я надеюсь, ты слышал"+ GetSexPhrase("","а") +" обо мне...",
				"Выкладывай все ценное, что у тебя есть, я реквизирую содержимое твоего кошелька. И побыстрей, так как я, " + GetFullName(npchar) + ", не очень терпелив. Но зато очччень кровожаден!");
			Link.l1 = LinkRandPhrase("Хех, так ты и есть тот самый " + GetFullName(npchar) + ", о котором местный губернатор " + sTemp + " только и говорит?",
				"О-о, так ты и есть тот самый бандит, за которым охотится местный губернатор " + sTemp + " ?!", 
				"Рад"+ GetSexPhrase("","а") +" видеть тебя, " + GetFullName(npchar) + ". Местный губернатор, " + sTemp + ", только о тебе и говорит...");
			Link.l1.go = "DestroyGang_1";
		break;		
		case "DestroyGang_1":
			dialog.text = LinkRandPhrase("Да, я известен в этих краях, хе-хе... Стоп, а ты не "+ GetSexPhrase("очередной ли пес","очередная ли шавка") +" губернатора, "+ GetSexPhrase("которого","которую") +" он пытается натравить на меня?",
				"Губернатор - мой большой друг, чего скрывать? Ха, а не "+ GetSexPhrase("очередной ли ты герой, отправленный","не очередная ли ты героиня, отправленная") +", им за моей головой?",
				"'Дружеское' расположение губернатора ко мне - факт, хе-хе. А ты откуда об этом знаешь? Может, он послал тебя по мою душу?");
			Link.l1 = LinkRandPhrase("Точно так, мерзавец. Готовься к смерти!", "Надо же, какой ты догадливый. Ну что же, пора приступать к твоей ликвидации. Поговорили, хватит уже...", "Да, это я и есть. Доставай оружие, приятель! Посмотрим, какого цвета у тебя кровь.");
			Link.l1.go = "DestroyGang_ExitFight";	
			Link.l2 = LinkRandPhrase("Да нет, что ты! Мне эти проблемы совершенно ни к чему...", "Нет, я за такие дела не берусь, не геройствую, в общем...", "Нет-нет, ни в коем разе! Мне проблемы ни к чему...");
			Link.l2.go = "DestroyGang_2";	
		break;
		case "DestroyGang_2":
			dialog.text = LinkRandPhrase("Так-то лучше, "+ GetSexPhrase("дружище","подруга") +"... А теперь проваливай!",
				"И это правильное решение, знал"+ GetSexPhrase("","а") +" бы ты, сколько героев я отправил на тот свет... Ладно, меньше лирики. Вали отсюда, "+ GetSexPhrase("мешок с дерьмом","шлюха") +"!",
				"Молодец, хвалю! Очень мудрая жизненная позиция - не лезть куда не просят... Ладно, проваливай, "+ GetSexPhrase("приятель","подруга") +".");
			Link.l1 = "До свидания, желаю здравствовать...";
			Link.l1.go = "DestroyGang_ExitAfraid";	
		break;

		case "DestroyGang_ExitAfraid":
			pchar.GenQuest.DestroyGang = "Found"; //флаг нашел, но струсил
			npchar.money = AddMoneyToCharacter(npchar, sti(pchar.money));
			pchar.money = 0;
			LAi_SetWarriorType(npchar);
			LAi_SetImmortal(npchar, false);
			LAi_SetCheckMinHP(npchar, LAi_GetCharacterHP(npchar)-1, false, "DestroyGang_SuddenAttack");
			for(i = 1; i < 4; i++)
			{
				if (GetCharacterIndex("MayorQuestGang_" + i) == -1) continue;	
				sld = CharacterFromID("MayorQuestGang_" + i);
				LAi_SetActorType(sld);
				LAi_ActorFollow(sld, npchar, "", -1);
				LAi_SetImmortal(sld, true);
				LAi_SetCheckMinHP(sld, LAi_GetCharacterHP(sld)-1, false, "DestroyGang_SuddenAttack");
			}
			DialogExit();
		break;

		case "DestroyGang_ExitFight":
			for(i = 0; i < 4; i++)
			{
				if (GetCharacterIndex("MayorQuestGang_" + i) == -1) continue;
				sld = CharacterFromID("MayorQuestGang_" + i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "DestroyGang_Afrer");
			DialogExit();	
			AddDialogExitQuest("MainHeroFightModeOn");
		break;

		// ОЗГ - пассажир
		case "ContraPass_abordage":
			dialog.text = "Аргх, мерзавец! Как ты посмел напасть на мое судно?! Тебе это даром не пройдет!";
			link.l1 = "Конечно, не пройдет! Мне за это заплатят... У тебя на борту есть один человек, "+pchar.GenQuest.TakePassenger.Name+" его зовут. Он-то мне и нужен.";
			link.l1.go = "ContraPass_abordage_1";
		break;
		
		case "ContraPass_abordage_1":
			dialog.text = "Я так и знал, что этот проходимец накличет на нас беду... Но я так просто не сдамся! Держись, мерзкий пират!";
			link.l1 = "Сам держись и не падай, пес!";
			link.l1.go = "ContraPass_abordage_2";
		break;
		
		case "ContraPass_abordage_2":
			DialogExit();
			LAi_SetCurHPMax(npchar);
			QuestAboardCabinDialogFree();
			LAi_group_SetRelation(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck(LAI_GROUP_BRDENEMY, "ContraPass_GivePrisoner");
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "Tempsailor":
			dialog.text = "Капитан, мы обыскали каюты и трюм, как вы и говорили. Мерзавец пытался спрятаться, но мы его нашли.";
			link.l1 = "Отлично! Где он?";
			link.l1.go = "Tempsailor_1";
		break;
		
		case "Tempsailor_1":
			dialog.text = "Как вы и приказали - отвели в трюм и надели кандалы.";
			link.l1 = "Молодцы! Теперь уходим с этой посудины. Нам пора в обратный путь.";
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
			sld = GetCharacter(NPC_GenerateCharacter("ContraPass", "citiz_"+(rand(9)+11), "man", "man", 10, sti(pchar.GenQuest.TakePassenger.Nation), -1, true, "quest"));
			sld.name = pchar.GenQuest.TakePassenger.Name;
			sld.lastname = "";
			pchar.GenQuest.LastQuestPrisonerIdx = SetCharToPrisoner(sld);
			SetCharacterRemovable(&characters[sti(pchar.GenQuest.LastQuestPrisonerIdx)], false);
			Pchar.GenQuest.TakePassenger.PrisonerIDX = sti(pchar.GenQuest.LastQuestPrisonerIdx);
		break;
		
		case "Fugitive_city": // ходит по городу
			pchar.quest.AllMayorsQuests_Late.over = "yes"; //снимаем общий таймер
			dialog.text = "Что вам угодно, сударь?";
			link.l1 = "Так-так... Ведь это вы - "+pchar.GenQuest.FindFugitive.Name+"? Очень рад вас видеть...";
			link.l1.go = "Fugitive_city_1";
		break;
		
		case "Fugitive_city_1":
			dialog.text = "Ну, положим, это я. И чем же вызвана ваша радость от встречи со мной? Я вас впервые вижу... Потрудитесь объясниться!";
			link.l1 = "Конечно. Я прибыл сюда из "+XI_ConvertString("Colony"+pchar.GenQuest.FindFugitive.Startcity+"Gen")+", по распоряжению тамошнего губернатора. Мною получен приказ арестовать вас и доставить в указанный город... Не хватайтесь за эфес шпаги, уважаемый, хуже будет!";
			link.l1.go = "Fugitive_city_2";
		break;
		
		case "Fugitive_city_2":
			dialog.text = "Значит, вы все-таки нашли меня... Сударь, выслушайте меня, и, возможно, вы измените свое решение. Да, я действительно дезертировал со службы. Но у меня просто уже не было сил смотреть на безобразие, которое творится в наших регулярных частях!\nЯ хочу тихой и мирной жизни, и здесь, в этом поселке, я нашел ее. Оставьте меня в покое, скажите, что не нашли, или что я сбежал с пиратами в море, а я взамен отдам вам вот этот мешочек с янтарем. Очень ценная вещь, скажу вам...";
			link.l1 = "Не пытайтесь меня подкупить, любезный! Немедленно сдайте оружие и следуйте за мной!";
			link.l1.go = "Fugitive_city_fight";
			link.l2 = "Хм. Безобразия? Тихой и мирной жизни? Хорошо... Пожалуй, я пойду вам навстречу. Где ваш янтарь?";
			link.l2.go = "Fugitive_city_gift";
		break;
		
		case "Fugitive_city_fight":
			dialog.text = "Тогда обнажи свой клинок, наемник! Так просто я не дамся!";
			link.l1 = "Ну, давай посмотрим, чего ты стоишь!";
			link.l1.go = "Fugitive_fight_1";
		break;
		
		case "Fugitive_city_gift":
			TakeNItems(pchar, "jewelry8", 50+drand(25));
			TakeNItems(pchar, "jewelry7", 2+drand(5));
			PlaySound("interface\important_item.wav");
			Log_Info("Вы получили янтарь");
			dialog.text = "Вот, держите... Надеюсь, я больше никогда не увижу ни вас, ни других 'посланников'.";
			link.l1 = "Думаю, что не увидите. Прощайте, сударь!";
			link.l1.go = "Fugitive_gift_exit";
		break;
		
		case "Fugitive_gift_exit":
			DialogExit();
			npchar.lifeday = 0;
			LAi_CharacterDisableDialog(npchar);
			pchar.GenQuest.FindFugitive = "Found"; //флаг провалил
			AddQuestRecord("MayorsQuestsList", "12-4");
			AddQuestUserData("MayorsQuestsList", "ColonyName", XI_ConvertString("Colony"+pchar.GenQuest.FindFugitive.Startcity));
		break;
		
		case "Fugitive_fight_1":// в городе и бухте
			chrDisableReloadToLocation = true;//закрыть локацию
			DialogExit();
			Diag.currentnode = "Fugitive_afterfight";
			LAi_SetImmortal(npchar, false);
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_SetCheckMinHP(npchar, 10.0, true, "Fugitive_afterfight");
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
		case "Fugitive_afterfight":
			dialog.text = "Аргх! Я сдаюсь... Твоя взяла, разрази тебя гром...";
			link.l1 = "Полегче с выражениями, сударь! А теперь будьте любезны свою шпагу... Следуйте за мной, и без глупостей!";
			link.l1.go = "Fugitive_afterfight_1";
		break;
		
		case "Fugitive_afterfight_1":
			DialogExit();
			RemoveAllCharacterItems(npchar, true);
			LAi_SetActorType(npchar);
			LAi_ActorFollow(npchar, pchar, "", -1);
			DeleteAttribute(npchar, "LifeDay");
			LAi_SetImmortal(npchar, true);
			pchar.GenQuest.LastQuestPrisonerIdx = SetCharToPrisoner(npchar);
			SetCharacterRemovable(&characters[sti(pchar.GenQuest.LastQuestPrisonerIdx)], false);
			Pchar.GenQuest.FindFugitive.PrisonerIDX = sti(pchar.GenQuest.LastQuestPrisonerIdx);
			pchar.GenQuest.FindFugitive = "Execute"; //флаг выполнил успешно
			pchar.quest.FindFugitive1.win_condition.l1 = "location";
			pchar.quest.FindFugitive1.win_condition.l1.location = pchar.GenQuest.FindFugitive.Startcity+"_townhall";
			pchar.quest.FindFugitive1.function = "FindFugitive_inResidence";
			SetFunctionTimerCondition("FindFugitive_Over", 0, 0, 30, false);
		break;
		
		case "Fugitive_shore": // в бухте
			pchar.quest.AllMayorsQuests_Late.over = "yes"; //снимаем общий таймер
			dialog.text = "Сударь, я не настроен с вами разговаривать. Так что...";
			link.l1 = "Как бы там ни было, а поговорить все-таки придется. Вы - "+pchar.GenQuest.FindFugitive.Name+"? Думаю, вам не стоит отрицать этого.";
			link.l1.go = "Fugitive_shore_1";
		break;
		
		case "Fugitive_shore_1":
			dialog.text = "И не собираюсь. Это действительно я. Что вам надо?";
			link.l1 = "Мне надо доставить вас в "+XI_ConvertString("Colony"+pchar.GenQuest.FindFugitive.Startcity)+", вас прямо-таки жаждет видеть тамошний губернатор. И попрошу без глупостей. Сдайте оружие и следуйте за мной!";
			link.l1.go = "Fugitive_shore_2";
		break;
		
		case "Fugitive_shore_2":
			dialog.text = "Так вот оно что... Сударь, прежде чем рубить сплеча, послушайте, что я вам скажу. Да, я действительно дезертировал из гарнизона. Но сделал это не от хорошей жизни. Я больше не могу находиться на военной службе, это свыше моих сил! Понимаете - не мо-гу!\nЯ хочу тихой и мирной жизни, и здесь, в этом поселке, я нашел ее... Оставьте меня в покое, скажите, что не нашли, или что я сбежал с пиратами в море, а я взамен отдам вам свой недельный улов жемчуга. Это все, что у меня есть.";
			link.l1 = "Не пытайтесь меня подкупить, любезный! Немедленно сдайте оружие и следуйте за мной!";
			link.l1.go = "Fugitive_city_fight";
			link.l2 = "Хм. Устали от военной службы? Хорошо... Пожалуй, я пойду вам навстречу. Где ваш жемчуг?";
			link.l2.go = "Fugitive_shore_gift";
		break;
		
		case "Fugitive_shore_gift":
			TakeNItems(pchar, "jewelry52", 100+drand(40));
			TakeNItems(pchar, "jewelry53", 400+drand(100));
			PlaySound("interface\important_item.wav");
			Log_Info("Вы получили жемчуг");
			dialog.text = "Вот, держите... Надеюсь, я больше никогда не увижу ни вас, ни других 'посланников'.";
			link.l1 = "Думаю, что не увидите. Прощайте, сударь!";
			link.l1.go = "Fugitive_gift_exit";
		break;
		
		case "Fugitive_tavern": // в таверне
			pchar.quest.AllMayorsQuests_Late.over = "yes"; //снимаем общий таймер
			dialog.text = "Э-э... ик! Сударь, я не ищу компании, особенно в вашем лице. Проваливайте!";
			link.l1 = "Зато я ищу вашей компании, "+pchar.GenQuest.FindFugitive.Name+". Точнее, вы мне скоро ее составите, причем в трюме моего корабля. Нас ждет путь в "+XI_ConvertString("Colony"+pchar.GenQuest.FindFugitive.Startcity)+", к тамошнему губернатору. Он просто сгорает от желания вас увидеть.";
			link.l1.go = "Fugitive_tavern_1";
		break;
		
		case "Fugitive_tavern_1":
			dialog.text = "И-ик!.."+RandSwear()+" Он все-таки достал меня! Послушай, дружище, ты не знаешь того, что произошло... Я не мог после этого оставаться на службе, не мог! Я до сих пор каждый вечер напиваюсь в стельку, лишь бы забыть об этом\nПослушай, давай договоримся. Скажи, что не нашел меня, или что я сбежал с пиратами в море, а я взамен отдам тебе самородки, которые я нашел в местной пещере. У меня больше ничего нет, я все отдаю тебе, лишь бы никогда больше не увидеть "+XI_ConvertString("Colony"+pchar.GenQuest.FindFugitive.Startcity)+"...";
			link.l1 = "Не пытайтесь меня подкупить, любезный! Немедленно сдайте оружие и следуйте за мной!";
			link.l1.go = "Fugitive_tavern_fight";
			link.l2 = "Хм. Неприятная история? Мучает совесть, или кошмары? Хорошо... Пожалуй, я пойду вам навстречу. Где ваши самородки?";
			link.l2.go = "Fugitive_tavern_gift";
		break;
		
		case "Fugitive_tavern_gift":
			TakeNItems(pchar, "jewelry5", 50+drand(30));
			TakeNItems(pchar, "jewelry6", 100+drand(50));
			PlaySound("interface\important_item.wav");
			Log_Info("Вы получили самородки");
			dialog.text = "Вот, держи... Надеюсь, я больше никогда не увижу ни тебя, ни других 'посланников'.";
			link.l1 = "Думаю, что не увидите. Прощайте, сударь!";
			link.l1.go = "Fugitive_gift_exit";
		break;
		
		case "Fugitive_tavern_fight":
			dialog.text = "Тогда обнажи свой клинок, наемник! Так просто я не дамся!";
			link.l1 = "Ну, давай посмотрим, чего ты стоишь!";
			link.l1.go = "Fugitive_fight_2";
		break;
		
		case "Fugitive_fight_2":// в таверне
			DialogExit();
			chrDisableReloadToLocation = true;//закрыть локацию
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешить драться
			LAi_SetImmortal(npchar, false);
			LAi_SetStayType(npchar);
			GetCharacterPos(pchar, &locx, &locy, &locz);
			ChangeCharacterAddressGroup(npchar, pchar.location, "goto", LAi_FindNearestFreeLocator("goto", locx, locy, locz));
			Diag.currentnode = "Fugitive_afterfight";
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_SetCheckMinHP(npchar, 10.0, true, "Fugitive_afterfight");
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
	}
}
