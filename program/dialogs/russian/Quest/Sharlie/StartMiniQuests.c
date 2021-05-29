
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	bool bOk;
	int i;

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
		
		//Найти помощника в магазин
		case "Storehelper":
			dialog.text = "Что вы хотели, месье?";
			link.l1 = "Хм. Ведь это вы - Гийом Лавуа, правильно?";
			link.l1.go = "Storehelper_1";
		break;
		
		case "Storehelper_1":
			dialog.text = "Да, я, а вам-то чего надо? Не мешайте мне пить ром, сударь, я не в настроении общаться.";
			link.l1 = "Я не отниму у вас много времени. Меня послал купец Сен-Пьера. Вы ведь работали у него на складе, так? Он разыскивает вас и...";
			link.l1.go = "Storehelper_2";
		break;
		
		case "Storehelper_2":
			dialog.text = "Ха! Он разыскивает меня! Чёртов скряга! Он думал, что я всю жизнь буду работать за его жалкие гроши? Да нет на всех Карибах жаднее купца! Я трудился на него пять лет без роздыху, а он ни разу не выдал даже маленькой премии, даже кружки рома не поставил!\nВот пусть теперь сам свои товары считает, а с меня довольно. Никто в Сен-Пьере не пойдёт работать к этому сквалыге, я-то знаю. У него только одна забота - потуже набить свой бездонный кошель и поменьше заплатить работникам.";
			link.l1 = "То есть, вы уже к нему на службу не вернётесь, как я понимаю?";
			link.l1.go = "Storehelper_3";
		break;
		
		case "Storehelper_3":
			dialog.text = "Нет, разрази меня гром! Я подожду здесь, в Ле Франсуа, какого-нибудь судна и наймусь квартирмейстером, а если не получится - пойду и простым матросом. Глаза б мои не видели этого скупердяя...";
			link.l1 = "Всё понятно. Большего мне знать и не нужно. Удачи, Гийом!";
			link.l1.go = "Storehelper_12";
		break;
		
		case "Storehelper_4":
			dialog.text = "Сударь, отойдите в сторону, вы загораживаете дорогу!";
			link.l1 = "Один вопрос, месье. Ведь это вы - Гийом Лавуа?";
			link.l1.go = "Storehelper_5";
		break;
		
		case "Storehelper_5":
			dialog.text = "Ха! Ну, я. А в чём дело-то?";
			link.l1 = "Вас разыскивает купец из Сен-Пьера. Вы ведь работали у него, так?";
			link.l1.go = "Storehelper_6";
		break;
		
		case "Storehelper_6":
			dialog.text = "Ха-ха! И зачем же я ему понадобился? Он решил доплатить мне невыплаченное жалование за последние две недели? Или у него не получается одновременно бочонки считать и клиентов обманывать, а? Ха-ха-ха!";
			link.l1 = "Он поручил мне разыскать вас и выяснить, почему вы не появляетесь у него в магаз...";
			link.l1.go = "Storehelper_7";
		break;
		
		case "Storehelper_7":
			dialog.text = "Почему я у него не появляюсь? Да потому что он чёртов сквалыга! Жадина, каких свет не видел! Пускай сам на своём складе возится, а я теперь вхожу в Береговое братство, и мне это, чёрт побери, очень нравится!\nСкоро я выйду в море и буду пересчитывать песо и дублоны, добытые у испанцев, а не ящики с бананами! А что до этого скряги - пусть попробует найти мне замену. Ни один дурак в Сен-Пьере не пойдёт к нему на службу, слишком дурная у него репутация, ха-ха!";
			link.l1 = "Всё понятно. Большего мне знать и не нужно. Удачи, Гийом!";
			link.l1.go = "Storehelper_12";
		break;
		
		case "Storehelper_8":
			dialog.text = "Если вы по поводу покупок - то это не ко мне.";
			link.l1 = "Добрый день. Как я понимаю, вы - Гийом Лавуа?";
			link.l1.go = "Storehelper_9";
		break;
		
		case "Storehelper_9":
			dialog.text = "Да, это я. Чем обязан, месье?";
			link.l1 = "Вас разыскивает купец из Сен-Пьера. Вы работали у него на складе...";
			link.l1.go = "Storehelper_10";
		break;
		
		case "Storehelper_10":
			dialog.text = "Ну и пусть себе разыскивает. Я ему ничего не должен. Это он мне остался должен за две недели службы, но я даже и не буду пытаться забрать у него эти деньги. Пусть подавится.";
			link.l1 = "Хм. Так вы окончательно ушли от него, как я понимаю?";
			link.l1.go = "Storehelper_11";
		break;
		
		case "Storehelper_11":
			dialog.text = "Вы всё правильно понимаете, сударь. Такого скряги, как мой бывший работодатель, свет не видывал. Я вот сейчас работаю здесь, и мои таланты оценены по достоинству - я получаю вдвое больше прежнего, и премиальные, если приходится задержаться подольше\nА этот сквалыга пусть попробует теперь отыскать мне замену. Не думаю, что у него это получится - его жадность слишком хорошо известна жителям Сен-Пьера, и ни один дурак не пойдёт к нему на службу.";
			link.l1 = "Всё понятно. Большего мне знать и не нужно. Удачи, Гийом!";
			link.l1.go = "Storehelper_12";
		break;
		
		case "Storehelper_12":
			DialogExit();
			npchar.lifeday = 0;
			AddQuestRecord("SharlieA", "2");
			pchar.questTemp.Sharlie.Storehelper = "return";
			LAi_CharacterDisableDialog(npchar);
			pchar.quest.StorehelperOver.over = "yes"; //снять таймер
		break;
		
		case "Newstorehelper_1":
			dialog.text = "Здравствуйте, месье. Не хочу показаться нескромным - но уверен, что моя кандидатура вам вполне подойдёт.";
			link.l1 = "Добрый день. И почему вы так считаете?";
			link.l1.go = "Newstorehelper_1_1";
		break;
		
		case "Newstorehelper_2":
			dialog.text = "Приветствую, сударь! Позвольте мне немного рассказать о себе.";
			link.l1 = "Я слушаю вас внимательно.";
			link.l1.go = "Newstorehelper_2_1";
		break;
		
		case "Newstorehelper_3":
			dialog.text = "Доброго здоровья, уважаемый господин. Ведь это вы принимаете на работу к купцу?";
			link.l1 = "Да, я. Что вы можете рассказать о себе?";
			link.l1.go = "Newstorehelper_3_1";
		break;
		
		case "Newstorehelper_1_1":
			dialog.text = "Потому что я служил у самого Франциска Дюбуа квартирмейстером. И Франциск был весьма доволен мной. А с морем мне пришлось расстаться из-за ранения - я долго лечился, выздоровел, но одно упоминание о качке повергает меня в уныние. Нет, я хочу обосноваться на твёрдой земле\n(шепчет) А ещё потому, что если вы порекомендуете меня, то я заплачу вам кроме пятисот песо ещё двадцать пять золотых дублонов. Ну как?";
			link.l1 = "Хорошо. Я подумаю над вашими словами.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Newstorehelper_1_2";
		break;
		
		case "Newstorehelper_2_1":
			dialog.text = "Я был мелким торговцем, потом разорился и пошёл в море, служил казначеем на торговом судне. Волею судьбы оказался в этом посёлке. Жизнь моряка мне не по душе, и я бы с радостью принял ваше предложение\n(понижая голос) И я готов прибавить к пятистам песо вот этот увесистый мешочек с янтарём.";
			link.l1 = "Понятно. Я подумаю над тем, что вы сказали.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Newstorehelper_2_2";
		break;
		
		case "Newstorehelper_3_1":
			dialog.text = "Я работал служащим на товарном складе в порту Глазго. Желание разбогатеть привело меня на Карибы, и мне удалось собрать немного денег, чтобы встретить старость не в нищете. Но я устал от морских походов, и хотел бы спокойной жизни на берегу вблизи моря\n(тихонько) За это место я впридачу к пятистам песо добавлю вам ещё пять раз по пятьсот.";
			link.l1 = "Ясно. Я приму это к сведению.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Newstorehelper_3_2";
		break;
		
		case "Newstorehelper_1_2":
			dialog.text = "Месье, вы сделаете правильный выбор. И не забывайте про дублоны...";
			link.l1 = "Я принял решение в вашу пользу. Собирайтесь, мы отправляемся в Сен-Пьер.";
			link.l1.go = "Newstorehelper_1_3";
			link.l2 = "Я ещё не решил...";
			link.l2.go = "exit";
			NextDiag.TempNode = "Newstorehelper_1_2";
		break;
		
		case "Newstorehelper_2_2":
			dialog.text = "Я надеюсь, что ваш выбор падёт на мою кандидатуру. Да и янтарь - весьма ценная и полезная штука...";
			link.l1 = "Я принял решение в вашу пользу. Собирайтесь, мы отправляемся в Сен-Пьер.";
			link.l1.go = "Newstorehelper_2_3";
			link.l2 = "Я ещё не решил...";
			link.l2.go = "exit";
			NextDiag.TempNode = "Newstorehelper_2_2";
		break;
		
		case "Newstorehelper_3_2":
			dialog.text = "Купец не разочаруется в моей работе. Как и вы в пяти раз по пятьсот...";
			link.l1 = "Я принял решение в вашу пользу. Собирайтесь, мы отправляемся в Сен-Пьер.";
			link.l1.go = "Newstorehelper_3_3";
			link.l2 = "Я ещё не решил...";
			link.l2.go = "exit";
			NextDiag.TempNode = "Newstorehelper_3_2";
		break;
		
		case "Newstorehelper_1_3":
			dialog.text = "Только вещи соберу! Я буду ждать вас у входа в таверну.";
			link.l1 = "...";
			link.l1.go = "Newstorehelper_exit";
			pchar.questTemp.Sharlie.Storehelper.Quality = 0;
		break;
		
		case "Newstorehelper_2_3":
			dialog.text = "Одна нога здесь, другая там, месье! Я буду у входа в таверну.";
			link.l1 = "...";
			link.l1.go = "Newstorehelper_exit";
			pchar.questTemp.Sharlie.Storehelper.Quality = 1;
		break;
		
		case "Newstorehelper_3_3":
			dialog.text = "Заберу свой старый саквояж и буду у дверей таверны, сударь!";
			link.l1 = "...";
			link.l1.go = "Newstorehelper_exit";
			pchar.questTemp.Sharlie.Storehelper.Quality = 2;
		break;
		
		case "Newstorehelper_exit":
			DialogExit();
			chrDisableReloadToLocation = false;//открыть локацию
			pchar.questTemp.Sharlie.Storehelper.id = npchar.id;
			DeleteAttribute(npchar, "LifeDay")
			chrDisableReloadToLocation = true;
			for (i=1; i<=3; i++)
			{
				sld = characterFromId("Newstorehelper_"+i);
				LAi_SetActorType(sld);
				LAi_ActorGoToLocation(sld, "reload", "reload1_back", "none", "", "", "OpenTheDoors", 10.0);
			}
			pchar.quest.storehelper2.win_condition.l1 = "location";
			pchar.quest.storehelper2.win_condition.l1.location = "LeFransua_town";
			pchar.quest.storehelper2.function = "NewstorehelperAdd";
			AddQuestRecord("SharlieA", "4");
			pchar.questTemp.Sharlie.Storehelper = "choise";
			pchar.quest.storehelper.over = "yes"; //снять прерывание
		break;
		
		case "Newstorehelper_regard":
			dialog.text = "Ну, как я понимаю, это и есть моё новое место работы? Спасибо, месье, что выбрали именно меня. Вот ваши пятьсот песо и дополнительная награда, как я и обещал.";
			link.l1 = "Благодарствую... Сейчас я представлю вас вашему работодателю, а потом уже - всё в ваших руках.";
			link.l1.go = "Newstorehelper_regard_1";
		break;
		
		case "Newstorehelper_regard_1":
			DialogExit();
			npchar.lifeday = 0;
			switch (sti(pchar.questTemp.Sharlie.Storehelper.Quality))
			{
				case 0:
					AddMoneyToCharacter(pchar, 500);
					TakeNItems(pchar, "gold_dublon", 25);
				break;
				
				case 1:
					AddMoneyToCharacter(pchar, 500);
					TakeNItems(pchar, "jewelry8", 10);
					TakeNItems(pchar, "jewelry7", 1);
				break;
				
				case 2:
					AddMoneyToCharacter(pchar, 3000);
				break;
			}
		break;
		
		//контрабанда рома
		case "Rum_Cap_Over":
			dialog.text = "Месье, я прошу вас немедленно покинуть мой корабль. Я поднимаю якоря и отплываю с минуты на минуту!";
			link.l1 = "Хорошо...";
			link.l1.go = "exit";
			NextDiag.TempNode = "Rum_Cap_Over";
			chrDisableReloadToLocation = false;
			npchar.DontDeskTalk = true;
			LAi_LocationFightDisable(&Locations[FindLocation("Deck_Near_Ship")], false);
		break;
		
		case "Rum_Cap":
			pchar.quest.Sharlie_rum2.over = "yes"; //снять таймер
			chrDisableReloadToLocation = false; // patch-4
			dialog.text = "Ну? Ты кто такой, приятель?";
			link.l1.edit = 1;			
			link.l1 = "";
			link.l1.go = "Rum_Cap_1";
		break;
		
		case "Rum_Cap_1":
			if(GetStrSmallRegister(pchar.questTemp.Sharlie.Rum.Pass) == GetStrSmallRegister(dialogEditStrings[1]))
			{
				dialog.text = "Выпей рому, моряк! Ха-ха! Приветствую на борту моего люггера. Ну, ты пришёл за товаром, как я понимаю?";
				link.l1 = "Да. А за чем же ещё?";
				link.l1.go = "Rum_Cap_2";
			}
			else
			{
				dialog.text = "Вот гнусное отродье! Ребята, похоже, это шпик! За борт его!";
				link.l1 = "А-ать!";
				link.l1.go = "Rum_Cap_getout";
			}
		break;
		
		case "Rum_Cap_getout":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation("Deck_Near_Ship")], false);
			setCharacterShipLocation(pchar, "Shore38"));
			setWDMPointXZ("Shore38");
			DoQuestReloadToLocation("Shore38", "goto", "goto1", "Rum_RemoveBarkas");
		break;
		
		case "Rum_Cap_2":
			dialog.text = "Ребята! Грузи ящики на баркас!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Rum_CarrierEnter");
		break;
		
		case "Rum_Cap_3":
			dialog.text = "Все ящики с ромом на твоём баркасе. Порт Ле Франсуа находится в южном направлении отсюда. Поторопись. Мне тоже пора поднимать якоря!";
			link.l1 = "Не будем терять времени, джентльмены! Удачи!";
			link.l1.go = "Rum_Cap_4";
		break;
		
		case "Rum_Cap_4":
			dialog.text = "И тебе того же, приятель...";
			link.l1 = "...";
			link.l1.go = "Rum_Cap_5";
		break;
		
		case "Rum_Cap_5":
			DialogExit();
			chrDisableReloadToLocation = false;
			LAi_LocationFightDisable(&Locations[FindLocation("Deck_Near_Ship")], false);
			npchar.DontDeskTalk = true;
			NextDiag.CurrentNode = "Rum_Cap_Over";
			pchar.quest.Sharlie_rum4.win_condition.l1 = "Ship_location";
			pchar.quest.Sharlie_rum4.win_condition.l1.location = "LeFransua_port";
			pchar.quest.Sharlie_rum4.function = "Rum_RemoveRum";
			AddQuestRecord("SharlieB", "4");
			i = FindIsland("Martinique");
			Islands[i].EffectRadius = 3000;
		break;
		
		case "Rum_Carrier":
			dialog.text = "Мы уже заждались вас, месье. Как всё прошло? Ящики у вас?";
			link.l1 = "Всё прошло просто замечательно. Ящики с ромом на баркасе.";
			link.l1.go = "Rum_Carrier_1";
		break;
		
		case "Rum_Carrier_1":
			dialog.text = "Отлично. Теперь это наша забота, а вы отправляйтесь в Сен-Пьер в таверну за расчётом.";
			link.l1 = "Всего доброго, джентльмены.";
			link.l1.go = "Rum_Carrier_2";
		break;
		
		case "Rum_Carrier_2":
			DialogExit();
			for (i=1; i<=3; i++)
			{
				
				sld = characterFromId("Rum_Carrier2_"+i);
				LAi_SetActorType(sld);
				LAi_ActorRunToLocation(sld, "goto", "goto8", "none", "", "", "OpenTheDoors", 10.0);
			}
			pchar.questTemp.Sharlie.Rum = "regard";
			i = FindLocation("Fortfrance_town");
			setCharacterShipLocation(pchar, GetCityFrom_Sea(locations[i].fastreload));
		    setWDMPointXZ(GetCityFrom_Sea(locations[i].fastreload));
		break;
		
		//доставить девочку из борделя
		case "GigoloMan":
			dialog.text = "Добрый день, месье! Клянусь, вы не похожи на этих неотёсанных мужланов, что ошиваются в нашей колонии. И, как я вижу, вы нездешний... Прибыли из Европы, я угадал?";
			link.l1 = "Именно так, сударь. "+GetFullName(pchar)+", к вашим услугам. Что вам угодно?";
			link.l1.go = "GigoloMan_1";
		break;
		
		case "GigoloMan_1":
			dialog.text = "Позвольте представиться - "+GetFullName(npchar)+". Прибыл из Франции в эту глушь несколько лет назад. Но давайте перейдём к делу. У меня к вам будет просьба, весьма деликатная и щекотливого характера\nНе будь я уверен в вашем благородном происхождении, я бы никогда не обратился к вам с ней. Но я уверен, что вы меня поймёте, как дворянин дворянина.";
			link.l1 = "Излагайте суть вашей просьбы, месье. Если это будет в моих силах - конечно, попробую помочь.";
			link.l1.go = "GigoloMan_2";
		break;
		
		case "GigoloMan_2":
			dialog.text = "Я рад слышать от вас эти слова, месье де Мор. Так вот. В нашем захолустье есть бордель. Недавно там появилась новая девочка, видимо, из Европы, молодая белокожая блондиночка. Я уже несколько недель за ней наблюдаю и... испытываю неимоверное желание остаться с ней наедине\nОднако моё положение в обществе и статус не позволяют мне посещать сие пристанище греха. Нет, как вы могли догадаться, мой друг, я и не против - но репутация стоит очень дорого\nПоэтому я и обратился к вам. Вы здесь человек новый, вас никто не знает, и никому нет до вас дела, по крайней мере, пока. Вы меня очень обяжете, месье...";
			link.l1 = "И чем же я могу вам помочь, сударь?";
			link.l1.go = "GigoloMan_3";
		break;
		
		case "GigoloMan_3":
			dialog.text = "Всё очень просто. Раз я не могу появиться в борделе - значит, эта девочка должна появиться у меня. Я прошу вас сходить в бордель и договориться с хозяйкой о том, чтобы она предоставила эту блондинку 'на вынос', на одну ночь\nАврора не будет возражать - подобные услуги она предоставляет, только берёт, конечно, дороже. Затем приведёте девочку к моему дому. Я дам вам шесть тысяч песо - ночь с девочкой Аврора обычно оценивает в три-три с половиной тысячи песо, а остальное возьмёте себе в качестве компенсации за беспокойство.";
			link.l1 = "Не вижу никаких сложностей, месье. Я без труда выполню вашу просьбу.";
			link.l1.go = "GigoloMan_4";
			link.l2 = "Сударь, я дорожу своей репутацией не меньше, чем вы. Так что прошу меня простить, но вашу просьбу я исполнить не могу. Позвольте откланяться.";
			link.l2.go = "GigoloMan_exit";
		break;
		
		case "GigoloMan_exit":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeday = 0;
		break;
		
		case "GigoloMan_4":
			dialog.text = "Я очень рад. Теперь слушайте: девушку, которая мне нужна, зовут Люсиль. Я прошу вас привести её ко мне домой когда стемнеет, не раньше одиннадцати вечера, чтобы никто не увидел. Постучитесь в дверь и я вам открою\nМой дом находится слева от резиденции губернатора - двухэтажный особняк с красной крышей. Вы легко его найдёте. Вот, возьмите шесть тысяч песо. И - я жду вас!";
			link.l1 = "Хорошо, сударь, договорились. К ночи ваша блондинка будет у вас на пороге.";
			link.l1.go = "GigoloMan_5";
		break;
		
		case "GigoloMan_5":
			DialogExit();
			AddMoneyToCharacter(pchar, 6000);
			AddQuestRecord("SharlieC", "1");
			AddQuestUserData("SharlieC", "sName", GetFullName(npchar));
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "houseSp1", "none", "", "", "", -1);
			LocatorReloadEnterDisable("Fortfrance_town", "houseSp1", true);
			npchar.lifeday = 0;
			pchar.questTemp.Sharlie.Gigolo = "start";
			pchar.questTemp.Sharlie.Gigolo.Rand1 = rand(1);
			pchar.questTemp.Sharlie.Gigolo.Rand2 = rand(1);
		break;
		
		case "GigoloGirl":
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "Здравствуйте, месье. Это вы оплатили меня на ночь? Хи-хи, надо сказать, мне здорово повезло - вы красавчик и видный господин, в отличие от этих неотёсанных мужланов...";
				link.l1 = "Всё не совсем так, Люсиль. Тебе нужно будет провести ночь не со мной, а с моим хорошим другом, который по ряду причин не может появляться в борделе. Но ты не расстраивайся - он весьма солидный мужчина, дворянин, и ты ему симпатична. Думаю, ты останешься довольна.";
				link.l1.go = "GigoloGirl_1";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "Месье, надеюсь, вы понимаете, что я не могу гулять с вами по ночам? Давайте займёмся делом - вы отведёте меня в дом своего друга. Иначе маман в конце-концов рассердится, и вы потеряете свои деньги.";
				link.l1 = "Хорошо, я понял. Следуй за мной!";
				link.l1.go = "GigoloGirl_2";
			}
		break;
		
		case "GigoloGirl_1":
			dialog.text = "Жаль... Вы мне сразу понравились, месье. Я бы с удовольствием провела эту ночь именно с вами. Ну да ладно. Пойдём?";
			link.l1 = "Да. Следуй за мной!";
			link.l1.go = "GigoloGirl_2";
		break;
		
		case "GigoloGirl_2":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			pchar.quest.Sharlie_Gigolo.win_condition.l1 = "locator";
			pchar.quest.Sharlie_Gigolo.win_condition.l1.location = "Fortfrance_town";
			pchar.quest.Sharlie_Gigolo.win_condition.l1.locator_group = "reload";
			pchar.quest.Sharlie_Gigolo.win_condition.l1.locator = "houseSp1";
			pchar.quest.Sharlie_Gigolo.function = "Sharlie_GiveGigoloGirl";
			pchar.quest.Sharlie_Gigolo1.win_condition.l1 = "Timer";
			pchar.quest.Sharlie_Gigolo1.win_condition.l1.date.hour  = sti(GetTime() + 2);
			pchar.quest.Sharlie_Gigolo1.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 0);
			pchar.quest.Sharlie_Gigolo1.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 0);
			pchar.quest.Sharlie_Gigolo1.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 0);
			pchar.quest.Sharlie_Gigolo1.function = "Sharlie_GigoloGirlOver";
		break;
		
		case "GigoloGirl_3":
			dialog.text = "Пришли?";
			link.l1 = "Да. Заходи в этот дом. Ничего не бойся - мой друг хороший человек.";
			link.l1.go = "GigoloGirl_4";
		break;
		
		case "GigoloGirl_4":
			dialog.text = "Хе... Да я и не боюсь. Всякое на свете повидала. Ладно, месье, прощайте. Может, как-нибудь потом вы оплатите мадам ночь со мной? Обещаю, это будет лучшая ночь в вашей жизни!";
			link.l1 = "Всё может быть, Люсиль. Возможно, ещё и встретимся. Пока!";
			link.l1.go = "GigoloGirl_5";
		break;
		
		case "GigoloGirl_5":
			pchar.quest.Sharlie_Gigolo1.over = "yes";
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "houseSp1", "none", "", "", "GigoloGirl_Remove", 5.0);
		break;
		
		//пираты с пленным испанцем
		case "CaptivePirate":
			pchar.quest.Captive_CreatePiratesOver.over = "yes";//снять таймер
			dialog.text = "Ты кто такой? Что тебе здесь надо? А ну, проваливай, живо!";
			link.l1 = "Что-то вы не сильно вежливы, сударь.";
			link.l1.go = "CaptivePirate_1";
		break;
		
		case "CaptivePirate_1":
			dialog.text = "Послушай, пижон, я вежливости не обучен, как и грамоте, но вот саблей по голове огреть, или пару новых дырок в тебе проделать - это запросто. И, клянусь громом, я это сделаю, если ты сию минуту не уберёшься отсюда. Ты понял?";
			link.l1 = "А теперь ты послушай, олух. Ваш заговор раскрыт. Мне нужен этот пленник. Сопротивление бесполезно - в джунглях отряд французских солдат. Если будете бежать достаточно быстро, то, возможно, вам удастся спасти свои жалкие жизни.";
			link.l1.go = "CaptivePirate_3";
			link.l2 = "Ладно-ладно, не кипятись. Я ухожу.";
			link.l2.go = "CaptivePirate_2";
		break;
		
		case "CaptivePirate_2":
			chrDisableReloadToLocation = false;
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			DialogExit();
			n = makeint(MOD_SKILL_ENEMY_RATE/2);
			if (n <= 1) n = 2;
			for (i=1; i<=n; i++)
			{
				sld = characterFromId("CaptivePirate_"+i);
				LAi_CharacterDisableDialog(sld);
				LAi_SetImmortal(sld, true);
				sld.lifeday = 0;
			}
			sld = characterFromId("CaptiveSpain");
			LAi_SetImmortal(sld, true);
			sld.lifeday = 0;
			pchar.quest.Sharlie_captive1.over = "yes";
			pchar.quest.Sharlie_captive2.over = "yes";//снять прерывание
			AddQuestRecord("SharlieD", "5");
			CloseQuestHeader("SharlieD");
			DeleteAttribute(pchar, "questTemp.Sharlie.Captive");
			pchar.questTemp.Sharlie = "bankskipermoney";
		break;
		
		case "CaptivePirate_3":
			dialog.text = "Что-о? Да ты блефуешь, дружок! Но в любом случае, ты умрёшь первым! Ребята, к оружию!";
			link.l1 = "Ну, держитесь, ублюдки...";
			link.l1.go = "CaptivePirate_4";
		break;
		
		case "CaptivePirate_4":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			int n = makeint(MOD_SKILL_ENEMY_RATE/2);
			if (n <= 1) n = 2;
			for (i=1; i<=n; i++)
			{
				sld = characterFromId("CaptivePirate_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "Captive_PiratesDead");
			AddDialogExitQuest("MainHeroFightModeOn");	
			sld = characterFromId("CaptiveSpain");
			LAi_SetCitizenType(sld);
		break;
		
		//пленный испанец
		case "CaptiveSpain":
			dialog.text = "Карамба! Ты француз? Ловко ты отделал этих мерзавцев. Но не думай, что я так просто сдамся!";
			link.l1 = "Постойте... послушайте, я не...";
			link.l1.go = "CaptiveSpain_1";
		break;
		
		case "CaptiveSpain_1":
			dialog.text = "От французов, кроме тюрьмы, мне ждать нечего. Я снял саблю с одного из трупов, пока ты дрался с последним пиратом... Защищайся, лягушатник!";
			link.l1 = "Вот тупой осёл!";
			link.l1.go = "CaptiveSpain_2";
		break;
		
		case "CaptiveSpain_2":
			DialogExit();
			LAi_SetPlayerType(pchar);
			NextDiag.currentnode = "CaptiveSpain_3";
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_SetCheckMinHP(npchar, 10.0, true, "CaptiveSpain_capture");
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
		case "CaptiveSpain_3":
			dialog.text = "Аргх... Ты победил. Я сдаюсь, проклятый француз. Делай теперь со мной, что хочешь - я в твоей власти.";
			link.l1 = "Брось оружие и дай наконец мне сказать, упрямый кастилец! Мне не нужна твоя смерть! И в тюрьму я тебя не отправлю!";
			link.l1.go = "CaptiveSpain_4";
			RemoveCharacterEquip(npchar, BLADE_ITEM_TYPE);
		break;
		
		case "CaptiveSpain_4":
			dialog.text = "Так что же тебе от меня нужно? Зачем ты тогда убил пиратов? И где твои солдаты?";
			link.l1 = "Нет никаких солдат. Я попытался напугать негодяев, но, как видишь, ничего не вышло. Я действовал в одиночку, по просьбе твоего старого друга. Его зовут "+pchar.questTemp.Sharlie.Captive.Name+", он ростовщик в Сен-Пьере.";
			link.l1.go = "CaptiveSpain_5";
		break;
		
		case "CaptiveSpain_5":
			dialog.text = ""+pchar.questTemp.Sharlie.Captive.Name+"? Я не знаю такого. Впервые слышу это имя!";
			link.l1 = "И тем не менее, о тебе, твоём пленении и передаче тебя на английское судно мне стало известно от него. У меня задача доставить тебя к нему, и, клянусь, я её выполню! Так что если тебе жизнь дорога, следуй за мной безо всяких фокусов.";
			link.l1.go = "CaptiveSpain_6";
		break;
		
		case "CaptiveSpain_6":
			dialog.text = "У меня в любом случае нет выбора... Возможно, твой ростовщик будет всё же лучше английских собак...";
			link.l1 = "Ты наконец-то стал разумно рассуждать. А теперь довольно болтовни - мы отправляемся в Сен-Пьер. Держись ко мне поближе и не вздумай бежать - всё равно догоню!";
			link.l1.go = "CaptiveSpain_7";
		break;
		
		case "CaptiveSpain_7":
			chrDisableReloadToLocation = false;
			DeleteAttribute(pchar, "GenQuest.Notsearchbody"); // 170712
			DialogExit();
			AddQuestRecord("SharlieD", "6");
			LAi_group_Register("TempFriends");
			LAi_group_SetRelation("TempFriends", LAI_GROUP_PLAYER, LAI_GROUP_FRIEND);
			LAi_group_MoveCharacter(npchar, "TempFriends");
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			SetNationRelation2MainCharacter(FRANCE, RELATION_ENEMY);
			pchar.quest.Sharlie_captive3.win_condition.l1 = "locator";
			pchar.quest.Sharlie_captive3.win_condition.l1.location = "Fortfrance_town";
			pchar.quest.Sharlie_captive3.win_condition.l1.locator_group = "reload";
			pchar.quest.Sharlie_captive3.win_condition.l1.locator = "reload8_back";
			pchar.quest.Sharlie_captive3.win_condition.l2 = "Night";
			pchar.quest.Sharlie_captive3.win_condition.l3 = "Alarm";
			pchar.quest.Sharlie_captive3.win_condition.l3.value = 0;
			pchar.quest.Sharlie_captive3.win_condition.l3.operation = "=";
			pchar.quest.Sharlie_captive3.function = "CaptiveSpain_reload";//вход ночью
			pchar.questTemp.Sharlie = "bankskipercaptive";
		break;
		
		//горожанин с пропавшей дочерью
		case "Prosper":
			pchar.quest.Sharlie_RescueDaughter.over = "yes"; //снять прерывание
			dialog.text = "Что вы хотите, месье? У меня совершенно нет времени на разговоры, так что давайте быстрее.";
			link.l1 = "Вы - Проспер Трубаль, так?";
			link.l1.go = "Prosper_1";
		break;
		
		case "Prosper_1":
			dialog.text = "Да, это я. Но вот вы мне совершенно незнакомы. Потрудитесь сообщить, кто вы такой и что вам от меня нужно.";
			link.l1 = "Моё имя - "+GetFullName(pchar)+". Меня прислал "+GetFullName(characterFromId("Fortfrance_portman"))+", начальник порта. Он сказал, что вам срочно требуется помощь...";
			link.l1.go = "Prosper_2";
		break;
		
		case "Prosper_2":
			dialog.text = "Разрази меня гром, если это не так! Этот негодяй комендант даже не выслушал меня до конца. Ему лень оторвать свой зад от стула и отдать приказ своим тупым солдафонам! Вы действительно пришли, чтобы мне помочь? Если это так, то в долгу я не останусь!";
			link.l1 = "Проспер, я действительно пришёл, чтобы помочь. Расскажите по порядку, что произошло и что надо сделать. Мне сказали, что у вас пропала дочь...";
			link.l1.go = "Prosper_3";
		break;
		
		case "Prosper_3":
			dialog.text = "Да, моя дочь Селина пропала два дня назад. Ей нужно было дойти всего лишь до форта, это буквально в двух шагах. К обеду она не вернулась, к вечеру тоже. Я отправился в форт, и там мне сказали, что она даже и не приходила туда!\nА вот теперь начинается самое интересное. На обратном пути на меня напали два размалёванных индейца. Они сидели в зарослях у тропы, в засаде. Они выскочили, как чёртики из табакерки, и попытались оглушить меня своими дубинами\nНо не тут-то было. Я успел врезать кулаком одному мерзавцу прямо в раскрашенную рожу, отскочить, достать пистолет и выстрелить. Я промахнулся, но выстрел напугал их, и я сумел добежать до городских ворот и сообщить страже. Солдаты тут же выбежали в джунгли, но краснокожих и след простыл\nЯ уверен: исчезновение Селины - их рук дело. Кроме того, за последнюю неделю пропали бесследно ещё два человека - Сезар Бланше и Жильберт Курси. Один собирался в бухту, второй - в Ле Франсуа. Ни один не вернулся.";
			link.l1 = "То есть индейцы нападают на горожан прямо у городских ворот? Невероятно...";
			link.l1.go = "Prosper_4";
		break;
		
		case "Prosper_4":
			dialog.text = "Я немедленно вооружился и отправился в разведку. И это дало определённые результаты. К северу от города есть небольшая пещера. Так вот, негодяи засели именно там. Я насчитал несколько индейцев у входа в пещеру, кроме того, ещё какая-то часть находится внутри\nПока я рассматривал мерзавцев, притаившись в зарослях, я услышал из глубин пещеры женский крик. Это была Селина! Я узнал её голос. Я с трудом сдержался, чтобы не напасть на негодяев немедленно - силы неравны, а моя смерть Селину бы не спасла.";
			link.l1 = "Но зачем они нападают и похищают горожан?";
			link.l1.go = "Prosper_5";
		break;
		
		case "Prosper_5":
			dialog.text = "Я не знаю. Может, продадут пиратам, а те - в рабство. А может, вообще съедят - это же дикари.";
			link.l1 = "Они что - людоеды? Вздор какой-то... Хотя где-то это я уже слышал...";
			link.l1.go = "Prosper_6";
		break;
		
		case "Prosper_6":
			dialog.text = "Вздор? Ну, некоторые так тоже считали, пока карибы их не поджарили на костре... Так вот, я немедленно обратился к коменданту с просьбой организовать карательную экспедицию. И что вы думаете? Он отказал. Заявил, что если девушка пропадает, то нужно подозревать не индейцев, а городских парней, и посоветовал поискать её ухажеров\nЧто до ещё двух пропавших, так один, мол, подозревается в связи с контрабандистами, а второй 'вполне возможно, пьянствует в таверне Ле Франсуа'. В общем, я ничего не добился и решил действовать сам.";
			link.l1 = "Что вы намерены предпринять?";
			link.l1.go = "Prosper_7";
		break;
		
		case "Prosper_7":
			dialog.text = "Отправлюсь в джунгли к пещере и перебью всю эту пакость. Надеюсь, Селина ещё жива. Как видите, я купил мушкет - очень убойная штука, а стрелять я ещё не разучился. Я выложил за него кучу денег, но мне плевать на это\nЕсли вы пойдёте со мной, то моя задача намного упростится: вдвоём мы без труда положим эту краснокожую мразь. Главное, чтобы они не напали сзади, пока я буду перезаряжать мушкет. Вы пойдёте со мной спасать мою дочь?";
			link.l1 = "Конечно! Это дело чести! Разве можно допустить, чтобы девушка погибла под ножом дикарей?";
			link.l1.go = "Prosper_8";
			link.l2 = "Хм. Вы знаете, мне кажется, что в словах коменданта есть резон. Может, всё же стоит сначала последовать его совету?";
			link.l2.go = "Prosper_exit";
		break;
		
		case "Prosper_exit":
			dialog.text = "Вы издеваетесь? Нет! Да у вас просто дрожат коленки! Убирайтесь к чёрту! Трус...";
			link.l1 = "Эй-эй, полегче!";
			link.l1.go = "Prosper_exit_1";
		break;
		
		case "Prosper_exit_1":
			DialogExit();
			npchar.lifeday = 0;
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "gate_back", "none", "", "", "", 10.0);
			CloseQuestHeader("SharlieF");
		break;
		
		case "Prosper_8":
			dialog.text = "Я рад, что в этом городе нашёлся хоть один разумный и храбрый человек. Вот, возьмите эти три пузырька. Это лечебное зелье, я купил его у нашего травника. Оно может здорово пригодиться вам в бою.";
			link.l1 = "А как же вы?";
			link.l1.go = "Prosper_9";
		break;
		
		case "Prosper_9":
			TakeNItems(pchar, "potion1", 3);
			PlaySound("interface\important_item.wav");
			dialog.text = "Не волнуйтесь, у меня есть ещё. Вы готовы?";
			link.l1 = "Да, не будем терять времени, оно на вес золота. Вперёд!";
			link.l1.go = "Prosper_10";
		break;
		
		case "Prosper_10":
			DialogExit();
			LAi_SetImmortal(npchar, true);
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			AddQuestRecord("SharlieF", "3");
			pchar.quest.Sharlie_RescueDaughter1.win_condition.l1 = "location";
			pchar.quest.Sharlie_RescueDaughter1.win_condition.l1.location = "Martinique_jungle_04";
			pchar.quest.Sharlie_RescueDaughter1.function = "RescueDaughter_NearCave";
			pchar.quest.Sharlie_RescueDaughter2.win_condition.l1 = "Timer";
			pchar.quest.Sharlie_RescueDaughter2.win_condition.l1.date.hour  = sti(GetTime()+2);
			pchar.quest.Sharlie_RescueDaughter2.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 0);
			pchar.quest.Sharlie_RescueDaughter2.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 0);
			pchar.quest.Sharlie_RescueDaughter2.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 0);
			pchar.quest.Sharlie_RescueDaughter2.function = "RescueDaughter_CaveOver";
			NextDiag.CurrentNode = "Prosper_11";
			pchar.questTemp.Sharlie.RescueDaughter = "true";
		break;
		
		case "Prosper_11":
			dialog.text = "Мы уже почти на месте, "+pchar.name+". За этим поворотом - вход в пещеру. Теперь я хочу рассказать вам свой план - как мы будем действовать.";
			link.l1 = "Слушаю вас внимательно, Проспер.";
			link.l1.go = "Prosper_12";
		break;
		
		case "Prosper_12":
			dialog.text = "Я стреляю без промаха, но для точного попадания нужно хорошо прицелиться. Если мне придётся вступить в рукопашную схватку - о стрельбе можно забыть, я смогу только отбиваться стволом и прикладом. Поэтому очень многое будет зависеть от вашего мужества и вашей ловкости.";
			link.l1 = "Что вы хотите этим сказать?";
			link.l1.go = "Prosper_13";
		break;
		
		case "Prosper_13":
			dialog.text = "Вам нужно будет отвлечь внимание всех врагов на себя, чтобы я мог спокойно стрелять. Поскольку беготня меткости не способствует, я буду стоять на месте. Там, у входа в пещеру - три мерзавца. Вам нужно сразу же броситься на них с обнажённым клинком\nВрежьте кому-нибудь из них, чтобы они за вами погнались, встаньте так, чтобы преградить дорогу ко мне, убегайте в сторону, отводите их подальше от меня. Если они все устремятся за вами - я их расстреляю по одному, как куропаток. Но если эти твари набросятся на меня - то дела наши будут неважные. Не испугаетесь?";
			link.l1 = "Мне не впервой держать клинок в руке. Так что насчёт этого не беспокойтесь.";
			link.l1.go = "Prosper_14";
		break;
		
		case "Prosper_14":
			dialog.text = "Тогда к бою. Ступайте первым, я за вами. Помните: вы должны не подпустить их ко мне на близкое расстояние!";
			link.l1 = "Я помню. Сделаю для этого всё возможное. Вперёд!";
			link.l1.go = "Prosper_15";
		break;
		
		case "Prosper_15":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			LocatorReloadEnterDisable("Martinique_jungle_04", "reload2_back", false);
			NextDiag.CurrentNode = "Prosper_16";
		break;
		
		case "Prosper_16":
			dialog.text = "Отлично сработали, "+pchar.name+"! Эта кучка краснокожих мерзавцев уничтожена. Осталось самое главное - пещера. Я не знаю, сколько их там, но полагаю, что трое-четверо. Теперь послушайте, каков будет наш план\nЯ бывал в этой пещере лет десять назад. Так вот: от входа идёт узкая каверна, ведущая в грот, разделённый стеной на две части, с расселиной посередине. Негодяи, вероятно, засели в гроте. Действовать нужно так же, как и в первый раз: я остаюсь на месте, у входа в пещеру, а вы немедленно бросаетесь в атаку\nНе теряйте ни секунды. Отвлеките их внимание, не старайтесь одолеть всех - главное, чтобы никто не побежал ко мне. Вы можете встать в расселине между двумя частями грота - она узкая, и они не смогут напасть на вас все сразу\nА пока краснорожие будут с вами возиться, я их легко перестреляю. Готовы?";
			link.l1 = "Вперед! Покончим с этим разбойничьим гнездом!";
			link.l1.go = "Prosper_17";
		break;
		
		case "Prosper_17":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			LocatorReloadEnterDisable("Martinique_CaveEntrance", "reload1_back", false);
			AddComplexSelfExpToScill(20, 20, 20, 20);
			pchar.quest.Sharlie_RescueDaughter2.win_condition.l1 = "location";
			pchar.quest.Sharlie_RescueDaughter2.win_condition.l1.location = "Martinique_Grot";
			pchar.quest.Sharlie_RescueDaughter2.function = "RescueDaughter_CreateIndiansGrot";
			NextDiag.CurrentNode = "Prosper_18";
		break;
		
		case "Prosper_18":
			dialog.text = "Моя дочь жива! Слава Богу! Мы успели вовремя, "+pchar.name+". Я в долгу перед вами. Вы отважный человек и хороший боец. Я восхищён!";
			link.l1 = "Я рад, Проспер, что всё закончилось благополучно. Мы сделали большое дело, уничтожив этих негодяев.";
			link.l1.go = "Prosper_19";
		break;
		
		case "Prosper_19":
			DialogExit();
			sld = characterFromId("RD_Selina");
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", 0, 0);
			AddComplexSelfExpToScill(30, 30, 30, 30);
		break;
		
		case "Prosper_20":
			dialog.text = "Ещё раз огромное спасибо, "+pchar.name+"! Давайте теперь все вместе вернёмся в город. Жизнь моей дочери бесценна, и никакими деньгами это не измерить, но я всё же хочу отблагодарить вас, подарив остатки своих сбережений. Как только мы придём в Сен-Пьер - я с радостью отдам вам их. И не вздумайте отказываться!";
			link.l1 = "Не откажусь, Проспер. Хотя я помогал вам вовсе не из-за денег.";
			link.l1.go = "Prosper_21";
		break;
		
		case "Prosper_21":
			dialog.text = "Вы благородный человек, "+pchar.name+"! А теперь давайте не будем здесь задерживаться и отправимся домой.";
			link.l1 = "...";
			link.l1.go = "Prosper_22";
		break;
		
		case "Prosper_22":
			chrDisableReloadToLocation = false;
			DialogExit();
			LAi_SetImmortal(npchar, true);
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			sld = characterFromId("RD_Selina");
			LAi_SetActorType(sld);
			LAi_ActorFollowEverywhere(sld, "", -1);
			sld = characterFromId("RD_Jilberte");
			LAi_SetActorType(sld);
			LAi_ActorFollowEverywhere(sld, "", -1);
		break;
		
		case "Prosper_23":
			SelectPresentAmulet();
			dialog.text = "Вот мы и пришли. Шарль, я ещё раз благодарю вас за помощь и присоединяю к словам вот эту скромную сумму в песо и мешочек золотых дублонов. Это немного за такую услугу, но зато от чистого сердца. Также возьмите вот этот амулет - "+pchar.questTemp.SMQ.Text+"";
			link.l1 = "Спасибо. Прощайте, Проспер, желаю вам и вашей милой дочке счастья!";
			link.l1.go = "Prosper_24";
		break;
		
		case "Prosper_24":
			AddMoneyToCharacter(pchar, 5000);
			TakeNItems(pchar, "gold_dublon", 15);
			TakeNItems(pchar, pchar.questTemp.SMQ.Amulet, 1);
			Log_Info("Вы получили 15 дублонов");
			Log_Info("Вы получили амулет");
			PlaySound("interface\important_item.wav");
			dialog.text = "Ей бы мужа такого, как вы, а то бегают за ней всякие тонконогие хлыщи, а как беда пришла - так все и исчезли куда-то... Эх, ладно. Удачи, Шарль!";
			link.l1 = "...";
			link.l1.go = "Prosper_25";
		break;
		
		case "Prosper_25":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload10_back", "none", "", "", "", 10.0);
			sld = characterFromId("RD_Selina");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload10_back", "none", "", "", "", 10.0);
			ChangeCharacterComplexReputation(pchar, "nobility", 3);
			ChangeCharacterComplexReputation(pchar,"authority", 2);
			AddCharacterExpToSkill(pchar, "Leadership", 120);//авторитет
			AddCharacterExpToSkill(pchar, "Fortune", 70);//везение
			AddCharacterExpToSkill(pchar, "Sneak", 70);//скрытность
			AddQuestRecord("SharlieF", "7");
			CloseQuestHeader("SharlieF");
			DeleteAttribute(pchar, "questTemp.SMQ");
			pchar.questTemp.Prosper_fmql = "true"; // Addon-2016 Jason, французские миниквесты (ФМК)
		break;
		
		case "Selina":
			dialog.text = "Ах! (плачет) Вы... вы не представляете, какой ужас здесь творился! Эти... эти нелюди притащили нас сюда, для того, чтобы убить и съесть! Здесь был Сезар Бланше... Они его... они совершили какой-то жуткий ритуал, а затем... я не могу этого говорить! Я должна была быть следующей! Они собирались меня зарезать... завтра!";
			link.l1 = "Успокойся, Селина. Всё кончено. Негодяи получили по заслугам, и более никому не причинят вреда.";
			link.l1.go = "Selina_1";
		break;
		
		case "Selina_1":
			dialog.text = "Здесь ещё Жильберт Курси. Он там... он до сих пор ещё не пришёл в себя. Поговорите с ним... И давайте побыстрее уйдём отсюда!";
			link.l1 = "Хорошо-хорошо. Всё, девочка, хватит плакать. Всё хорошо. У тебя замечательный отец, он никому не даст тебя в обиду... Идите наружу, я сейчас выведу... как его... Жильберта, и догоню вас.";
			link.l1.go = "Selina_2";
		break;
		
		case "Selina_2":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "Martinique_CaveEntrance", "officers", "reload1_2", "", 5.0);
			sld = characterFromId("RD_Prosper");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload1_back", "Martinique_CaveEntrance", "officers", "reload1_1", "", 5.0);
			AddQuestRecord("SharlieF", "5");
			sld = characterFromId("RD_Jilberte");
			LAi_SetStayType(sld);
		break;
		
		case "Selina_3":
			dialog.text = "Небеса услышали мои молитвы! Вы пришли, чтобы спасти нас?";
			link.l1 = "Ты... Тебя зовут Селина, так?";
			link.l1.go = "Selina_4";
		break;
		
		case "Selina_4":
			dialog.text = "Да... (плачет) Вы... вы не представляете, какой ужас здесь творился! Эти... эти нелюди притащили нас сюда, для того, чтобы убить и съесть! Здесь был Сезар Бланше... Они его... они совершили какой-то жуткий ритуал, а затем... я не могу этого говорить! Я должна была быть следующей! Они собирались меня зарезать... завтра!";
			link.l1 = "Тише, тише, девочка... Прости, я должен огорчить тебя. Мы пришли сюда вдвоём с твоим отцом. Но он погиб в схватке с этими краснокожими тварями. Он отдал свою жизнь, чтобы спасти тебя.";
			link.l1.go = "Selina_5";
		break;
		
		case "Selina_5":
			dialog.text = "Что?! Мой отец... О Боже! Я... я...(рыдает)";
			link.l1 = "Я сожалею, Селина. Тут ещё кто-то есть, да?";
			link.l1.go = "Selina_6";
		break;
		
		case "Selina_6":
			dialog.text = "(сквозь слезы) Да... Жильберт Курси. Он там... он до сих пор ещё не пришёл в себя. Поговорите с ним... И давайте побыстрее уйдём отсюда!";
			link.l1 = "Да, конечно. Мы ни на одну лишнюю минуту не останемся здесь.";
			link.l1.go = "Selina_7";
		break;
		
		case "Selina_7":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "Martinique_CaveEntrance", "officers", "reload1_2", "", 5.0);
			AddQuestRecord("SharlieF", "6");
			sld = characterFromId("RD_Jilberte");
			LAi_SetStayType(sld);
			AddComplexSelfExpToScill(20, 20, 20, 20);
		break;
		
		case "Selina_8":
			dialog.text = "Мой отец... Мой бедный отец! Ах, месье, я даже не поблагодарила вас за спасение...";
			link.l1 = "Я просто рад, Селина, что ты и Жильберт остались живы. Во всяком случае, героическая смерть твоего отца не была напрасной.";
			link.l1.go = "Selina_9";
		break;
		
		case "Selina_9":
			dialog.text = "(плачет) Пожалуйста, месье, проведите нас до города. Надо, чтобы сюда пришли солдаты и забрали тело отца, чтобы похоронить по-христиански...";
			link.l1 = "Конечно, Селина. Следуйте за мной!";
			link.l1.go = "Selina_10";
		break;
		
		case "Selina_10":
			chrDisableReloadToLocation = false;
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			sld = characterFromId("RD_Jilberte");
			LAi_SetActorType(sld);
			LAi_ActorFollowEverywhere(sld, "", -1);
		break;
		
		case "Selina_11":
			dialog.text = "Спасибо вам, месье, за то, что пошли с моим бедным отцом... Спасибо за то, что спасли меня от неминуемой смерти. Я... я... вот, возьмите этот мешочек с дублонами. Я нашла его дома в сундуке отца. И даже не вздумайте отказываться!";
			link.l1 = "Хорошо, Селина. Я рад, что нам удалось спасти тебя, и искренне соболезную тебе по поводу смерти твоего отца.";
			link.l1.go = "Selina_12";
		break;
		
		case "Selina_12":
			TakeNItems(pchar, "gold_dublon", 15);
			PlaySound("interface\important_item.wav");
			dialog.text = "Вы благородный человек, месье. Я никогда не забуду вас. Прощайте!";
			link.l1 = "Прощай, Селина.";
			link.l1.go = "Selina_13";
		break;
		
		case "Selina_13":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload10_back", "none", "", "", "", 10.0);
			npchar.lifeday = 0;
			ChangeCharacterComplexReputation(pchar, "nobility", 3);
			ChangeCharacterComplexReputation(pchar,"authority", 1);
			AddCharacterExpToSkill(pchar, "Leadership", 100);//авторитет
			AddCharacterExpToSkill(pchar, "Fortune", 50);//везение
			AddCharacterExpToSkill(pchar, "Sneak", 50);//скрытность
			AddQuestRecord("SharlieF", "8");
			CloseQuestHeader("SharlieF");
		break;
		
		case "Jilberte":
			PlaySound("Voice\Russian\other\robinzons-08.wav");
			dialog.text = "Господи, неужели всё позади? Я даже не верю... Вы спасли и меня, и Селину. Если бы вы не пришли, завтра её бы постигла участь несчастного Сезара, а через несколько дней то же было бы уготовано и мне.";
			link.l1 = "Эти индейцы - они что, действительно людоеды?!";
			link.l1.go = "Jilberte_1";
		break;
		
		case "Jilberte_1":
			dialog.text = "А вы что, сомневаетесь? Хотите - поройтесь в золе их костра. Думаю, вы там найдёте что-нибудь от бедняги Сезара. Пару обглоданных костей, например...";
			link.l1 = "Б-р-р... Нет уж, увольте. Просто я совсем недавно из Европы, и даже не предполагал, что на нашей Земле творятся такие мерзости.";
			link.l1.go = "Jilberte_2";
		break;
		
		case "Jilberte_2":
			dialog.text = "На Карибах происходит много такого, о чем в вашей Европе даже и слыхом не слыхивали... Индейские колдуны, шаманы, тайные обряды. Поживите у нас подольше - и не такого насмотритесь. Впрочем, простите меня, я так и не поблагодарил вас за спасение - я до сих пор в шоке\nВы спасли мою жизнь, и я намерен выразить свою глубокую признательность за это не только словами, но и звонкой монетой. Проводите меня и Селину до города. Там я смогу отблагодарить вас, как вы того заслуживаете, месье.";
			link.l1 = "Хорошо. Ступайте наружу, а я ещё тут немного осмотрюсь.";
			link.l1.go = "Jilberte_3";
		break;
		
		case "Jilberte_3":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "Martinique_CaveEntrance", "officers", "reload1_3", "OpenTheDoors", 10.0);
			pchar.quest.Sharlie_RescueDaughter5.win_condition.l1 = "location";
			pchar.quest.Sharlie_RescueDaughter5.win_condition.l1.location = "Martinique_CaveEntrance";
			pchar.quest.Sharlie_RescueDaughter5.function = "RescueDaughter_GoHome";
		break;
		
		case "Jilberte_4":
			dialog.text = "Позвольте ещё раз выразить вам свою глубокую благодарность за спасение, месье! Как я и обещал - присоединяю к словесной благодарности благодарность материальную, в серебряных песо и золотых дублонах.";
			link.l1 = "Я рад, что всё закончилось хорошо, Жильберт.";
			link.l1.go = "Jilberte_5";
		break;
		
		case "Jilberte_5":
			AddMoneyToCharacter(pchar, 3000);
			TakeNItems(pchar, "gold_dublon", 20);
			Log_Info("Вы получили 20 дублонов");
			PlaySound("interface\important_item.wav");
			dialog.text = "А как я-то этому рад, вы не представляете! Спасибо ещё раз и позвольте откланяться, месье.";
			link.l1 = "Удачи, Жильберт!";
			link.l1.go = "Jilberte_6";
		break;
		
		case "Jilberte_6":
			chrDisableReloadToLocation = false;
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload4_back", "none", "", "", "", 10.0);
			npchar.lifeday = 0;
			DeleteAttribute(pchar, "questTemp.Sharlie.RescueDaughter");
		break;
		
		//замечание по обнаженному оружию от персонажей типа citizen
		case "CitizenNotBlade":
			dialog.text = NPCharSexPhrase(NPChar, "Послушайте, я, как гражданин этого города, прошу вас не ходить у нас с обнажённым клинком.", "Знаете, я, как гражданка этого города, прошу вас не ходить у нас с обнажённым клинком.");
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

void SelectPresentAmulet()
{
	switch (pchar.HeroParam.HeroType)
	{        
		case "HeroType_1":
			pchar.questTemp.SMQ.Amulet = "indian_7";
			pchar.questTemp.SMQ.Text = "он прибавляет выносливости и открывает второе дыхание.";
		break;
		
		case "HeroType_2":
			pchar.questTemp.SMQ.Amulet = "amulet_7";
			pchar.questTemp.SMQ.Text = "он повышает стойкость к ранениям в бою.";
		break;
		
		case "HeroType_3":
			pchar.questTemp.SMQ.Amulet = "indian_4";
			pchar.questTemp.SMQ.Text = "он увеличит силу удара вашего оружия.";
		break;
		
		case "HeroType_4":
			pchar.questTemp.SMQ.Amulet = "indian_1";
			pchar.questTemp.SMQ.Text = "он делает огнестрельное оружие намного убойнее.";
		break;
	}
}