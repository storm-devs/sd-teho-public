//пассажир на доставку
void ProcessDialogEvent()
{
	ref NPChar, d;
	aref Link, Diag, arAll;
	string NPC_Meeting, sTemp, sTitle, sTavern;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makeref(d, Dialog);
	makearef(Diag, NPChar.Dialog);

	switch(Dialog.CurrentNode)
	{
		case "exit":
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
		break;
		
		case "prepare_convoy_quest":
			if (isBadReputation(pchar, 40)) 
			{
				dialog.text = RandPhraseSimple("О-о-о, черт!! Я знаю, кто ты "+ GetSexPhrase("такой","такая") +"! Только полный идиот может пойти к тебе на борт пассажиром. Прощай!", "А-а, я знаю, кто ты есть! К тебе на борт моя нога не ступит. Ищи дурака...");
				link.l1 = RandPhraseSimple("Хех, боязливый какой...", "Пугливый какой народ пошел!");
				link.l1.go = "convoy_refused";
			}
			else
			{
				dialog.text = TimeGreeting() + ", "+GetAddress_Form(NPChar) + "! Я "+ GetFullName(NPChar) + ". Я слышал, что вы берете на борт пассажиров?";
				link.l1 = "Возможно да, все зависит от моей выгоды.";
				link.l1.go = "prepare_convoy_quest_3";
			}
		break;
		
		case "prepare_convoy_quest_3":
			LookShipPassenger();
			GenerateConvoyPassengerQuest(npchar);
			dialog.text = "Мне нужно, чтобы меня доставили в таверну " + XI_ConvertString("Colony" + npchar.GenQuest.GetPassenger_Destination + "Gen") + ", что на " + XI_ConvertString(GetIslandByCityName(npchar.GenQuest.GetPassenger_Destination) + "Dat") +
                          ", за " + FindRussianDaysString(sti(npchar.GenQuest.GetPassenger_Time)) + ", и за это я заплачу вам " + FindRussianMoneyString(sti(npchar.GenQuest.GetPassenger_Money)) + ". Что скажете?";
			link.l1 = "Я "+ GetSexPhrase("согласен","согласна") +".";
			link.l1.go = "convoy_agreeded";
			link.l2 = "Не думаю, что мне это интересно.";
			link.l2.go = "convoy_refused";
		break;
		
		case "convoy_refused":
			chrDisableReloadToLocation = false;
			sTemp = npchar.id + "_TimeOver";
			pchar.quest.(sTemp).over = "yes";
			sTemp = npchar.id + "_dead";
			pchar.quest.(sTemp).over = "yes";			
			DeleteAttribute(npchar, "GenQuest.GetPassenger");
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "", 5.0);
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
		break;
		
		case "convoy_agreeded":
			sTitle = npchar.index + "convoy_passenger";
			AddQuestRecordEx(sTitle, "Gen_convoy_passenger", "1");
			sTemp = XI_ConvertString("Colony" + npchar.GenQuest.GetPassenger_Destination + "Gen") + ", что на " + XI_ConvertString(GetIslandByCityName(npchar.GenQuest.GetPassenger_Destination) + "Dat") + ",";
			AddQuestUserDataForTitle(sTitle, "sCity", sTemp);
			AddQuestUserDataForTitle(sTitle, "sName", GetFullName(npchar));
			AddQuestUserData(sTitle, "sCity", sTemp);
			AddQuestUserData(sTitle, "sSex", GetSexPhrase("ся","ась"));
			AddQuestUserData(sTitle, "sName", GetFullName(npchar));
			AddQuestUserData(sTitle, "sDay", FindRussianDaysString(sti(npchar.GenQuest.GetPassenger_Time)));
            AddQuestUserData(sTitle, "sMoney", FindRussianMoneyString(sti(npchar.GenQuest.GetPassenger_Money)));
            // по городу вернем его таверну
			sTavern = npchar.GenQuest.GetPassenger_Destination + "_tavern";
			sTemp = npchar.id + "_complited";
			pchar.quest.(sTemp).win_condition.l1 = "location";
			pchar.quest.(sTemp).win_condition.l1.location = sTavern;
			pchar.quest.(sTemp).win_condition = "AllPassangersComplited";	
			pchar.quest.(sTemp).Idx	= npchar.index; 
			if (rand(2) == 1) TraderHunterOnMap();
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, false);
			chrDisableReloadToLocation = false;
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "", 5.0);			
			Diag.CurrentNode = "convoy_DeskTalk";
			DialogExit();
		break;
		
		case "complete_convoy_quest":
			dialog.text = "Спасибо вам. Вы выполнили свои обязательства. Теперь я на месте. Вот ваша награда.";
			Link.l1 = "Благодарю вас.";
			link.l1.go = "complete_convoy_quest_1";
		break;

		case "complete_convoy_quest_1":
			//слухи
			AddSimpleRumour(LinkRandPhrase("Некий человек по имени " + GetFullName(npchar) + " говорит, что можно доверять капитану " + GetMainCharacterNameDat() + ", так как "+ GetSexPhrase("тот","та") +" без особых проблем "+ GetSexPhrase("доставил","доставила") +" его до " + XI_ConvertString("Colony" + npchar.GenQuest.GetPassenger_Destination + "Gen") + ".", 
				"Пассажир по имени " + GetFullName(npchar) + " говорит, что капитану " + GetMainCharacterNameDat() + " можно верить. "+ GetSexPhrase("Тот доставил","Та доставила") +" его до " + XI_ConvertString("Colony" + npchar.GenQuest.GetPassenger_Destination + "Gen") + " в целости и сохранности.", 
				"Я слышал, капитан, что вы держите слово, данное пассажирам. Некий барышник по имени " + GetFullName(npchar) + " очень хорошо о вас отзывается."), sti(npchar.nation), 40, 1);
			chrDisableReloadToLocation = false;
			DeleteAttribute(pchar, "GenQuest.ConvoyPassenger." + npchar.id); //извлекаем из структуры недовольных
			//--> смотрим Deck
    		makearef(arAll, pchar.GenQuest.ConvoyPassenger);
			if (GetAttributesNum(arAll) == 0) pchar.quest.ConvoyMapPassenger.over = "yes";
			//<-- смотрим Deck
			AddMoneyToCharacter(pchar, makeint(npchar.GenQuest.GetPassenger_Money));
			ChangeCharacterComplexReputation(pchar, "nobility",1);
			ChangeCharacterComplexReputation(pchar, "fame",1);
			RemovePassenger(PChar, npchar);
			OfficersReaction("good");						
			AddCharacterExpToSkill(pchar, "Sailing", 80);
			AddCharacterExpToSkill(pchar, "Leadership", 20);			
			sTitle = npchar.index + "convoy_passenger";
			AddQuestRecordEx(sTitle, "Gen_convoy_passenger", "4");			
            CloseQuestHeader(sTitle);	
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "", 5.0);	
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
		break;
		
		case "convoy_DeskTalk":
			dialog.text = NPCStringReactionRepeat(LinkRandPhrase(RandSwear() + "Капитан, время вышло. Когда же, в конце концов, я попаду в " + XI_ConvertString("Colony" + npchar.GenQuest.GetPassenger_Destination + "Acc") + "?", 
						  RandSwear() + "Капитан, сколько можно блуждать неизвестно где?! Когда мы доберемся до " + XI_ConvertString("Colony" + npchar.GenQuest.GetPassenger_Destination + "Gen") + "?" , 
						  RandSwear() + "Послушайте, капитан, мне необходимо было добраться до " + XI_ConvertString("Colony" + npchar.GenQuest.GetPassenger_Destination + "Gen") + ", и я хочу получить четкий и ясный ответ, когда это произойдет!"), 
				RandPhraseSimple("Капитан, уже второй раз я поднимаю тему исполнения вами своих обязательств. Когда мы доберемся до " + XI_ConvertString("Colony" + npchar.GenQuest.GetPassenger_Destination + "Gen") + "?", "Капитан, второй раз я вынужден поставить вопрос о моей доставке. Когда, наконец, мы увидим берега " + XI_ConvertString("Colony" + npchar.GenQuest.GetPassenger_Destination + "Gen") + "?"), 
				RandPhraseSimple(RandSwear() + "Капитан, третий раз я спрашиваю вас о том же - когда мы прибудем в " + XI_ConvertString("Colony" + npchar.GenQuest.GetPassenger_Destination + "Acc") + "?", "Капитан, мы потеряли черт знает сколько времени! Когда вы доставите меня в " + XI_ConvertString("Colony" + npchar.GenQuest.GetPassenger_Destination + "Acc") + "?"), 
                "Послушайте, капитан, это уже ни в какие ворота не лезет...", "block", 0, npchar, Dialog.CurrentNode);
            if (sti(npchar.GenQuest.GetPassenger_Money) > 100)
            {
				link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Прошу меня простить, дела... "+ GetSexPhrase("замотался","замоталась") +"... Через 7 дней вы точно будете на месте.", "Извините " + GetAddress_Form(NPChar) + ", совсем не было возможности выполнить обязательства по отношению к вам. Но можете не переживать, через неделю будем на месте."),
					RandPhraseSimple("Я "+ GetSexPhrase("вынужден","вынуждена") +" во второй раз извиниться... Через неделю мы будем на месте.", "Я вторично приношу извинения. Через неделю мы будем на месте."),
					RandPhraseSimple("И в третий раз я "+ GetSexPhrase("вынужден","вынуждена") +" просить прощения у вас... Мы будем на месте через неделю.", "Я приношу извинения в третий раз. Через неделю мы будем на месте, обещаю..."),
					"Я понимаю, " + GetAddress_Form(NPChar) + ", но прошу еще немного потерпеть... Через семь дней я доставлю вас до места назначения!", npchar, Dialog.CurrentNode);
    			link.l1.go = "convoy_DeskTalk_1";
			}
			link.l2 = HeroStringReactionRepeat(RandPhraseSimple("А-а... пассажир... я и "+ GetSexPhrase("забыл","забыла") +" про вас. Думаю, в трюме вам будет спокойнее, и доставать меня вы прекратите.", "Хех, ну надо же! У меня на корабле - посторонние!.. Полагаю, тебе нужно познакомиться с моим трюмом."),
				"Второй раз? Ну, надо же... Пожалуй, я отправлю тебя в трюм на экскурсию.",
				"Третий раз? Как это нехорошо, хе-хе... Вот что, приятель, тебе пора в трюм, нечего разгуливать на моем корабле.",
				"Ворота? А-а, понимаю, это высшая степень раздражения! Ну, хватит, наверное, в бирюльки играть... Добро пожаловать в трюм, " + GetAddress_Form(NPChar) + ".", npchar, Dialog.CurrentNode);
			link.l2.go = "convoy_Prison_1";
			pchar.quest.Munity = "Deads"; //дверцы откроем
		break;
		
		case "convoy_DeskTalk_1":
			dialog.text = LinkRandPhrase("Хорошо, но я сокращу оплату за такую проволочку.", "Ну что же, поверю... Но учтите, что я сокращу размер выплаты вам!", "Хм, деваться мне некуда с корабля, но имейте в виду, что размер вашего гонорара сократится...");
			Link.l1 = LinkRandPhrase("Договорились.", "Ну, хорошо...", "Ладно, пусть будет так.");
			link.l1.go = "convoy_DeskTalk_2";
		break;

		case "convoy_DeskTalk_2":
			dialog.text = RandPhraseSimple("Я хочу верить, что в этот раз договор будет выполнен.", "Я надеюсь, что это наш последний разговор на столь неприятную тему...");
			Link.l1 = "Разумеется.";
			link.l1.go = "convoy_DeskTalk_exit";
		break;

		case "convoy_DeskTalk_exit":
			DeleteAttribute(pchar, "GenQuest.ConvoyPassenger." + npchar.id); //извлекаем из структуры недовольных
			sTemp = npchar.id + "_TimeOver";
			SetTimerCondition(sTemp, 0, 0, 7, false);
			pchar.quest.(sTemp).win_condition              = "AllPassangersTimeOver";
			pchar.quest.(sTemp).Idx						   = npchar.index; 
			npchar.GenQuest.GetPassenger_Money = makeint(sti(npchar.GenQuest.GetPassenger_Money) / 1.5);			
			sTitle = npchar.index + "convoy_passenger";
			AddQuestRecordEx(sTitle, "Gen_convoy_passenger", "5");
			AddQuestUserData(sTitle, "sMoney", FindRussianMoneyString(sti(npchar.GenQuest.GetPassenger_Money)));
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "", 4.0);	
			Diag.CurrentNode = "convoy_DeskTalk";
			DialogExit();
		break;

		case "convoy_Prison_1":
			dialog.text = RandSwear() + "Какой еще трюм? Я не понимаю вас!";
			if (GetPrisonerQty() < PRISONER_MAX)
			{
    			Link.l1 = "Что тут неясного? Теперь ты мой пленник! Пошел в трюм!";
    			link.l1.go = "convoy_Prison_2";
            }
			Link.l2 = "Шучу я... Дней через семь будем точно в нужном городе.";
			link.l2.go = "convoy_DeskTalk_1";
		break;
		
		case "convoy_Prison_2":
			dialog.text = RandSwear() + "Ты еще заплатишь за это, "+ GetSexPhrase("мерзавец","мерзавка") +"!";
			Link.l1 = "Все так говорят, но выходит как раз наоборот - платят мне!";
			link.l1.go = "convoy_Prison_3";
		break;
		
		case "convoy_Prison_3":
			AddSimpleRumour(LinkRandPhrase("Стало известно, что некий капитан " + GetFullName(pchar) + " взялся доставить пассажира по имени " + GetFullName(npchar) + ", но слова своего не "+ GetSexPhrase("сдержал","сдержала") +". К тому же "+ GetSexPhrase("пленил","пленила") +" беднягу. Вот так - доверять малознакомым людям...", 
				"Эх, куда катится мир?! Капитан " + GetFullName(pchar) + " "+ GetSexPhrase("захватил","захватила") +" беднягу по имени " + GetFullName(npchar) + ", хотя тот был пассажиром на его корабле...", 
				"Ходят слухи, капитан, что вы "+ GetSexPhrase("порядочный мерзавец","порядочная мерзавка") +". Погоривают, что бедняга " + GetFullName(npchar) + " был пленен на вашем корабле. А вы ведь обещали доставить его до " + XI_ConvertString("Colony" + npchar.GenQuest.GetPassenger_Destination + "Gen") + ". Да уж, некрасиво..."), sti(npchar.nation), 40, 1);
            RemovePassenger(PChar, NPChar);
        	LAi_SetActorType(NPChar);
        	LAi_ActorRunToLocation(NPChar, "reload", "reload1", "none", "", "", "", 5.0);
        	ChangeCharacterComplexReputation(pchar,"nobility", -5);
            OfficersReaction("bad");
			ChangeCharacterHunterScore(pchar, NationShortName(sti(NPChar.nation)) + "hunter", 10+rand(10));// награда            
			DeleteAttribute(pchar, "GenQuest.ConvoyPassenger." + npchar.id); //извлекаем из структуры недовольных
			sTemp = npchar.id + "_complited";
            pchar.quest.(sTemp).over = "yes";
			sTemp = npchar.id + "_dead";
			pchar.quest.(sTemp).over = "yes";
			sTemp = npchar.id + "_TimeOver";
			pchar.quest.(sTemp).over = "yes";
			sTitle = npchar.index + "convoy_passenger";
			AddQuestRecordEx(sTitle, "Gen_convoy_passenger", "6");			
			AddQuestUserData(sTitle, "sSex", GetSexPhrase("","а"));
            CloseQuestHeader(sTitle);			
			AddCharacterExpToSkill(pchar, "COMMERCE", 25);
            SetCharToPrisoner(NPChar);
        	DialogExit();
		break;
	}
} 

void GenerateConvoyPassengerQuest(ref npchar)
{
	int iTradeMoney, iNation, irank;
	string sTemp, sR;

	iNation = GetRelation2BaseNation(sti(npchar.nation)); //если привезти нужно во вражеский город
	npchar.GenQuest.GetPassenger_Destination = sGlobalTemp;
	int daysQty = GetMaxDaysFromIsland2Island(GetArealByCityName(pchar.GenQuest.GetPassenger_City), GetArealByCityName(sGlobalTemp));
	if (sti(daysQty) > 14) daysQty = 14;
	npchar.GenQuest.GetPassenger_Time  = makeint(sti(daysQty)*(frand(1.3)+0.7));
	iTradeMoney = (sti(daysQty)*500*sti(pchar.GenQuest.GetPassenger.Shipmod)+rand(100))*sti(daysQty)/sti(npchar.GenQuest.GetPassenger_Time);
	if (iNation == RELATION_ENEMY && sti(npchar.nation != PIRATE)) iTradeMoney = makeint(iTradeMoney * 1.3); //то размер награды увеличивается
	npchar.GenQuest.GetPassenger_Money = iTradeMoney;

	//Log_Info(FindRussianDaysString(sti(daysQty)));
	//Log_Info(npchar.GenQuest.GetPassenger_Destination);
	//Log_Info(pchar.GenQuest.GetPassenger_City);
	

	sTemp = npchar.id + "_TimeOver";
	SetTimerCondition(sTemp, 0, 0, sti(npchar.GenQuest.GetPassenger_Time), false);
	pchar.quest.(sTemp).win_condition              = "AllPassangersTimeOver";
	pchar.quest.(sTemp).Idx						   = npchar.index; 

	sTemp = npchar.id + "_dead";
	pchar.quest.(sTemp).win_condition.l1           = "NPC_Death";
	pchar.quest.(sTemp).win_condition.l1.character = npchar.id;
	pchar.quest.(sTemp).win_condition              = "AllPassangersDead";
	pchar.quest.(sTemp).Idx						   = npchar.index; 	
}

void LookShipPassenger()
{
	switch(makeint(6-sti(RealShips[sti(Pchar.Ship.Type)].Class)))
	{
		case 0:
			pchar.GenQuest.GetPassenger.Shipmod = 0.8;
		break;
		case 1:
			pchar.GenQuest.GetPassenger.Shipmod = 1;
		break;
		case 2:
			pchar.GenQuest.GetPassenger.Shipmod = 1.2;
		break;
		case 3:
			pchar.GenQuest.GetPassenger.Shipmod = 1.5;
		break;
		case 4:
			pchar.GenQuest.GetPassenger.Shipmod = 2.2;
		break;
		case 5:
			pchar.GenQuest.GetPassenger.Shipmod = 3;
		break;
	}
}
