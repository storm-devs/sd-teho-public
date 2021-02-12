// boal 08/04/04 общий диалог торговцев
#include "DIALOGS\russian\Rumours\Common_rumours.c"  //homo 25/06/06

void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	

	string iDay, iMonth, sTemp, sMoney, attrL;
	
	iDay = environment.date.day;
	iMonth = environment.date.month;
	string lastspeak_date = iday + " " + iMonth;
	
	int iMoney, iQuantityGoods, iTradeGoods, iTmp;
	
	bool  ok;

	int iTest, cn, i;
	iTest = FindColony(NPChar.City); // город магазина
	ref rColony, chref;
	
	if (iTest != -1)
	{
		rColony = GetColonyByIndex(iTest);
	}
	
	int iSeaGoods = LanguageOpenFile("ShipEatGood.txt"); // нужно заменить на GetGoodsNameAlt(idx)

	if(!CheckAttribute(npchar, "quest.trade_date"))
	{
		npchar.quest.trade_date = "";
	}
    
	// вызов диалога по городам -->
	NPChar.FileDialog2 = "DIALOGS\" + LanguageGetLanguage() + "\Store\" + NPChar.City + "_Store.c";
	if(LoadSegment(NPChar.FileDialog2))
	{
		ProcessCommonDialog(NPChar, Link, NextDiag);
		UnloadSegment(NPChar.FileDialog2);
	}
	
	// вызов диалога по городам <--
	ProcessCommonDialogRumors(NPChar, Link, NextDiag);//homo 25/06/06
	
	string attrLoc   = Dialog.CurrentNode;
	
	if(HasSubStr(attrLoc, "TransferGoodsTo_"))
	{
		NPChar.CharToTransferGoodsID = FindStringAfterChar(attrLoc, "_");
		Dialog.CurrentNode = "TransferGoods_Start";
	}
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (LAi_grp_playeralarm > 0)
			{
				dialog.text = NPCharRepPhrase(pchar, 
					LinkRandPhrase("В городе поднята тревога, тебя всюду ищут! На твоем месте я бы не стал здесь задерживаться.", "Вся городская стража рыщет по городу в поисках тебя. Я не идиот и разговаривать с тобой не буду!", "Беги, "+ GetSexPhrase("приятель","подруга") +", пока солдаты не сделали из тебя решето..."), 
					LinkRandPhrase("Что тебе нужно, "+ GetSexPhrase("негодяй","негодяйка") +"?! Городская стража уже взяла твой след, далеко тебе не уйти, "+ GetSexPhrase("грязный пират","гнусная дрянь") +"!", ""+ GetSexPhrase("Грязный","Грязная") +" убийца, вон из моего дома! Стража!!", "Я не боюсь тебя, "+ GetSexPhrase("мерзавец","мерзавка") +"! Скоро тебя повесят в нашем форте, далеко тебе не уйти..."));
				link.l1 = NPCharRepPhrase(pchar,
					RandPhraseSimple("Хех, тревога для меня не проблема...", "Им меня ни за что не поймать."), 
					RandPhraseSimple("Заткни свою пасть, " + GetWorkTypeOfMan(npchar, "") + ", а не то вырву твой поганый язык!", "Хех, " + GetWorkTypeOfMan(npchar, "") + ", а все туда же - пиратов ловить! Вот что я тебе скажу, приятель: сиди тихо и будешь жить..."));
				link.l1.go = "fight";
				break;
			}
			if (sti(pchar.GenQuest.Piratekill) > 20 && sti(npchar.nation) == PIRATE)
			{
				dialog.text = RandPhraseSimple("А, это ты, мерзавец! Думаешь, тебе здесь рады? Как бы не так! Ребята! К оружию! Режь психа!", "Купить чего-то хочешь, скотина? Ан нет! Сейчас тебе покажут, где раки зимуют! Ребята, здесь больной псих с оружием! Тревога!");
				link.l1 = RandPhraseSimple("А? Что?", "Э, ты чего это?!");
				link.l1.go = "fight";
				bDisableFastReload = true;//закрыть переход
				pchar.quest.pirate_in_town.win_condition.l1 = "ExitFromLocation";
				pchar.quest.pirate_in_town.win_condition.l1.location = pchar.location;
				pchar.quest.pirate_in_town.function = "TownPirate_battle";
				break;
			}
			//--> Jason Бремя гасконца
			if (CheckAttribute(pchar, "questTemp.Sharlie.Lock"))
			{
				//Jason --> мини-квест Дефицитный товар
				if (CheckAttribute(pchar, "questTemp.Wine.Trader") && NPChar.location == pchar.questTemp.Wine.City + "_store" && !CheckAttribute(pchar, "questTemp.Wine.fail"))
				{
					link.l13 = "Я хочу приобрести у вас партию европейского вина, бутылок пятьдесят-шестьдесят. Мне сказали, что оно у вас имеется в достаточном количестве."; 
					link.l13.go = "Wine_Trader";
				}
				if (CheckAttribute(pchar, "questTemp.Wine.Repeat2") && NPChar.location == pchar.questTemp.Wine.City + "_store" && CheckCharacterItem(pchar, "letter_1") && !CheckAttribute(pchar, "questTemp.Wine.fail"))
				{
					link.l13 = "Здравствуйте еще раз. Прочтите вот это письмо, и, быть может, вы пересмотрите вопрос о продаже вина?"; 
					link.l13.go = "Wine_Repeat2";
				}
				if (CheckAttribute(pchar, "questTemp.Wine.wait") && NPChar.location == pchar.questTemp.Wine.City + "_store" && !CheckAttribute(pchar, "questTemp.Wine.fail"))
				{
					link.l13 = "Это опять я. Давайте продолжим нашу прерванную торговлю вином, я раздобыл денег побольше."; 
					link.l13.go = "Wine_Price";
				}
				// <-- мини-квест Дефицитный товар
				dialog.text = "Вы хотели приобрести что-то в моем магазине, месье?";
				Link.l1 = "Конечно! А для чего же еще магазины существуют? Показывайте ваши товары.";
				Link.l1.go = "trade_1";
				Link.l2 = "Я к вам по одному вопросу...";
				Link.l2.go = "quests";
				Link.l3 = "Прошу прощения, но мне надо идти.";
				Link.l3.go = "exit";
				break;
			}			
			//<-- Бремя гасконца
			
			// Warship, 29.05.11. Дело чести - трусливый фехтовальщик.
			if(CheckAttribute(PChar, "QuestTemp.AffairOfHonor.CowardFencer.CanTraderTalk"))
			{
				dialog.text = "Капитан, спасибо за то, что спасли меня.";
				Link.l1 = "Не за что.";
				Link.l1.go = "exit";
				DeleteAttribute(PChar, "QuestTemp.AffairOfHonor.CowardFencer.CanTraderTalk");
				break;
			}
			// Карибские нравы
			if(CheckAttribute(npchar, "quest.trial_usurer"))
			{
				dialog.text = "Что с вами, капитан? Вы что-то потеряли? Что вы так мечетесь по моему магазину?";
				Link.l1 = "Да, представьте себе - потерял. Где этот чертов Жерар Лекруа? Я выполнил все поручения Флориана Шоке, и, поглоти меня акула, мне пришлось здорово постараться! А теперь, когда я являюсь за своей наградой, выясняется, что этого пижона и след простыл!";
				Link.l1.go = "trial";
				break;
			}
			
            dialog.Text = GetNatPhrase(npchar, LinkRandPhrase("Рад приветствовать вас, сэр! Впервые в наших краях?","Добро пожаловать, капитан! Мой магазин к вашим услугам, сэр.","Прошу вас, сэр, проходите! Я рад предложить вам все лучшее, что только можно купить на архипелаге."), LinkRandPhrase("О, месье капитан! Лучшие товары французских колоний – здесь и сейчас – и только для вас!","Какое приятное знакомство, месье! Лучший магазин лучших французских товаров к вашим услугам!","Мы не встречались раньше, месье капитан? Мой магазин не уступит лучшим салонам метрополии!"), LinkRandPhrase("О! Сеньор капитан! Я рад видеть вас в моем магазине!","Рад приветствовать столь блестящего кабальеро в лучшем магазине испанских колоний!","О, благородный идальго! Судьба не зря привела вас в мой скромный магазин – здесь вы найдете все, что только пожелаете!"),LinkRandPhrase("Добрый день, минхер капитан. Это ваш первый визит к нам?","Здравствуйте, минхер. Впервые у нас? Поверьте, качество голландских товаров приятно вас поразит!","Прошу вас, минхер капитан! Самые качественные товары по самым низким ценам – иное было бы не по-голландски!"));
			Link.l1 = LinkRandPhrase("Я вам тоже рад. Мое имя "+GetFullName(pchar)+" и я здесь совсем недавно. Ну, показывайте, чем богат архипелаг?","Приятная встреча, я "+GetFullName(pchar)+". капитан корабля '"+pchar.ship.name+"'.  Итак, что там у вас есть интересного?",""+GetFullName(pchar)+", капитан корабля '"+pchar.ship.name+"', рад знакомству. Что вы мне предложите?");
			link.l1.go = "node_1";
			NextDiag.TempNode = "Second time";
		break;

		case "second time":
			if (LAi_group_GetPlayerAlarm() > 0)
			{
       			dialog.text = NPCharRepPhrase(pchar, 
					LinkRandPhrase("В городе поднята тревога, тебя всюду ищут! На твоем месте я бы не стал здесь задерживаться.", "Вся городская стража рыщет по городу в поисках тебя. Я не идиот и разговаривать с тобой не буду!", "Беги, "+ GetSexPhrase("приятель","подруга") +", пока солдаты не сделали из тебя решето..."), 
					LinkRandPhrase("Что тебе нужно, "+ GetSexPhrase("негодяй","негодяйка") +"?! Городская стража уже взяла твой след, далеко тебе не уйти, "+ GetSexPhrase("грязный пират","гнусная дрянь") +"!", ""+ GetSexPhrase("Грязный","Грязная") +" убийца, вон из моего дома! Стража!!", "Я не боюсь тебя, "+ GetSexPhrase("мерзавец","мерзавка") +"! Скоро тебя повесят в нашем форте, далеко тебе не уйти..."));
				link.l1 = NPCharRepPhrase(pchar,
					RandPhraseSimple("Хех, тревога для меня не проблема...", "Им меня ни за что не поймать."), 
					RandPhraseSimple("Заткни свою пасть, " + GetWorkTypeOfMan(npchar, "") + ", а не то вырву твой поганый язык!", "Хех, " + GetWorkTypeOfMan(npchar, "") + ", а все туда же - пиратов ловить! Вот что я тебе скажу, приятель: сиди тихо и будешь жить..."));
				link.l1.go = "fight";
				break;
			}
            
			//--> Jason, Сомнительное предложение
			if (CheckAttribute(pchar, "GenQuest.Contraoffer.Trader.busy"))
			{
				dialog.text = "Извините, но мне сейчас не до вас.";
				link.l1 = "Да, конечно. Я зайду позже.";
				link.l1.go = "exit";
				break;
			}
			//<-- Сомнительное предложение
            
			// Warship, 29.05.11. Дело чести - трусливый фехтовальщик.
			if(CheckAttribute(PChar, "QuestTemp.AffairOfHonor.CowardFencer.CanTraderTalk"))
			{
				dialog.text = "Капитан, спасибо за то, что спасли меня.";
				Link.l1 = "Не за что.";
				Link.l1.go = "exit";
				DeleteAttribute(PChar, "QuestTemp.AffairOfHonor.CowardFencer.CanTraderTalk");
				break;
			}
			// Карибские нравы
			if(CheckAttribute(npchar, "quest.trial_usurer"))
			{
				dialog.text = "Что с вами, капитан? Вы что-то потеряли? Что вы так мечетесь по моему магазину?";
				Link.l1 = "Да, представьте себе - потерял. Где этот чертов Жерар Лекруа? Я выполнил все поручения Флориана Шоке, и, поглоти меня акула, мне пришлось здорово постараться! А теперь, когда я являюсь за своей наградой, выясняется, что этого пижона и след простыл!";
				Link.l1.go = "trial";
				break;
			}
            
			dialog.Text = pcharrepphrase(LinkRandPhrase(LinkRandPhrase("Кого это к нам занесло? Впрочем, деньги-то не пахнут, так что проходите, капитан, поторгуем...","Не могу сказать, что рад видеть вас, "+GetFullName(pchar)+"... Но поторговать пока готов.","Хе-хе... в гости не приглашаю, капитан, но мой магазин пока еще к вашим услугам."),LinkRandPhrase("О, кого я вижу! Сам "+GetFullName(pchar)+"! Торговать к нам, или так, брать без денег? Шучу, шучу...","Не то, чтобы я был рад вашему визиту, "+GetAddress_Form(NPChar)+". Но если вы при деньгах – заходите, чего уж там...","Хотите поторговать, капитан "+GetFullName(pchar)+"? Давайте, только побыстрее, а то прочие клиенты при вас не торопятся в магазин, а дело от этого страдает."),LinkRandPhrase("Будем торговать, минхер? Минуточку, я кассу приберу, а то ходят тут… всякие... Это я, конечно, не вам, капитан!","Завидев вас в море, "+GetAddress_Form(NPChar)+", я бы, пожалуй, приказал добавить парусов, хе-хе... Но здесь, у себя, предлагаю поторговать.","Кэп, сразу предупреждаю: если, как в прошлый раз, ткани заляпаны кровью, а кофе провонял порохом – ничего брать не буду. А так – смотрите, выбирайте.")),LinkRandPhrase(LinkRandPhrase("И снова я рад приветствовать вас, "+GetAddress_Form(NPChar)+"! Купить или продать  - я всегда рад помочь вам.","Прошу вас, "+GetAddress_Form(NPChar)+", прошу! Я рад приветствовать своего лучшего клиента. Желаете что-нибудь купить или продать?","О, "+GetAddress_Form(NPChar)+" "+GetFullName(pchar)+"! Как я рад снова видеть вас! Хотите купить или продать что-нибудь?"),LinkRandPhrase("Вам понравились наши товары, "+GetAddress_Form(NPChar)+" "+GetFullName(pchar)+"? Я всегда к вашим услугам – смотрите, выбирайте.","Здравствуйте, "+GetAddress_Form(NPChar)+" "+GetFullName(pchar)+". Я рад, что вы снова заглянули ко мне. Угодно глянуть наш ассортимет товаров?","Рад вам, капитан! Я знал, что наши добротные товары вам приглянутся. Посмотрите, что есть новенького?"),LinkRandPhrase("О, "+GetAddress_Form(NPChar)+" "+GetFullName(pchar)+"! Прошу вас, любые товары для вас! В честь вашего визита – с огромными скидками!","Капитан "+GetFullName(pchar)+", вы снова осчастливили меня своим визитом! Выбирайте – что вам угодно!","Что вам угодно, капитан? Рад, что помните дорогу ко мне. Любые товары для вас в наличии – полюбуйтесь, все высшего разряда!")));
			Link.l1 = pcharrepphrase(RandPhraseSimple(RandPhraseSimple("Так вот как ты мне рад, дружище? Что ж, я учту, когда встречу тебя в море... Да не трясись ты так, шучу. Давай, покажи, что там у тебя есть?","Так, друг. Товары мне твои нужны, а вот твой язык – не очень. Сам его придержишь, или помочь? Давай, закрывай рот и показывай товары."),RandPhraseSimple("Ближе к делу, торгаш. Мне некогда тут с тобой мораль обсуждать, я пришел по деловому вопросу. Давай-ка лучше поторгуем, как приличные люди.","Потише на ветре, приятель. Шутки шутками, но я ведь могу и рассердиться... Так что не зли меня и показывай товары.")),RandPhraseSimple(RandPhraseSimple("Всегда рад вас посетить, дружище. Что там у вас в закромах достойно внимания?","К вам всегда приятно зайти, приятель. Что новенького найдется для морских бродяг, месяцами не ступающих на сушу?"),RandPhraseSimple("И снова я в "+XI_ConvertString("Colony"+npchar.City+"Dat")+"! Рад, что меня здесь не забывают. А вот осталось на ваших складах что-нибудь для меня или все уже разобрали? ","Как же к вам не зайти? Вы всегда меня чем-нибудь да порадуете. Ну, что у вас там?")));
			link.l1.go = "node_1";
			NextDiag.TempNode = "Second time";
		break;

		case "node_1":
			dialog.text = NPCStringReactionRepeat(NPCharRepPhrase(npchar,
			                                         pcharrepphrase(RandPhraseSimple("Свистать всех наверх! ","Трюм к осмотру! ") +LinkRandPhrase("Что нужно "+ GetSexPhrase("джентльмену","джентльмену, ой, пардон, леди") +" удачи в моем магазине, хе-хе?",
													                                 "Какой приятный сюрприз для бедного старого торговца! Хе-хе!", "Каким попутным ветром тебя занесло в мой магазин?"),
            														LinkRandPhrase("Открыть порты!", "Крючья к борту!","Держать прямо по курсу!")+RandPhraseSimple(" У меня вы найдете"," В моем магазине")
																	+LinkRandPhrase(" самые лучшие цены на острове."," прекрасный выбор товаров."," товары самого высшего качества.")
																	+RandPhraseSimple(" Я к вашим услугам"," Все, что пожелаете")+", капитан!"),
													 pcharrepphrase(RandPhraseSimple("Любые товары для "+ GetSexPhrase("джентльменов","джентльменов и леди") +" удачи! Хе-хе! Пока их не повесили сушиться на солнышке!",
													                                 "Ветер качает повешенных в порту и разносит звон цепей. Но деньги не пахнут, верно?!"),
                 												"Желаете " +LinkRandPhrase("купить лучшие товары " + NationNameGenitive(sti(NPChar.nation)),"купить или продать груз", "получить выгодный фрахт")
																	+RandPhraseSimple("? Я полностью в вашем распоряжении!","? Мой магазин к вашим услугам!")
																	+RandPhraseSimple(" Рад вас видеть"," Располагайтесь") +", капитан!")),
				                                  NPCharRepPhrase(npchar,
												  	 pcharrepphrase("Мой тебе совет, кэп: не жалей денег на картечь. Обыскивать проще мертвых!",
													                "Я с первого взгляда увидел, что ты "+ GetSexPhrase("ловкий малый","ловкая малая") +". " +RandPhraseSimple("Но теперь я вижу, что ты прямо "+ GetSexPhrase("герой","сорвиголова") +".", "Ты "+ GetSexPhrase("молод","молода") +", но "
																	+RandPhraseSimple("ум у тебя острый.", "тебя не обманешь."))),
													 pcharrepphrase("Я готов покупать у вас весь груз с захваченных призов. Хотите купить золото или серебро? Оно всегда в цене!",
													                "Торговое мореплавание - выгодный бизнес, капитан " + GetFullName(pchar)+", не так ли?")),
												  NPCharRepPhrase(npchar,
												     RandPhraseSimple("Все семьдесят пять не вернулись домой! Они потонули в пучине морской! " ,
													   RandPhraseSimple("Пятнадцать человек на сундук мертвеца!","Пей, и дьявол тебя доведет до конца!") +" Йо-хо-хо! И бутылка рома. ")
													   +RandPhraseSimple("Чего надо, кэп?", "Что вы хотите купить, капитан?"),
													 pcharrepphrase("А вы любите поторговаться, капитан " + GetFullName(pchar)+". Как постоянному клиенту, я предлагаю вам очень выгодные цены!",
													                "Ну хорошо, капитан " + GetFullName(pchar)+", из уважения к вам я готов еще немного уступить в цене! Что вы хотите?")),
												  NPCharRepPhrase(npchar,
												     "Клянусь, мне тошно разговаривать с тобой. "
													 +LinkRandPhrase("Купи два-три земляных ореха. Их так любят свиньи. ","Ты ждешь, что здесь тебе сапоги будут чистить ромом? ",
													 pcharrepphrase("Знаю я вашего брата. Налакаетесь рому - и на виселицу.","Как это твоя мамаша отпустила тебя в море! В море!!! Уж лучше бы ты "+ GetSexPhrase("стал портным","стала портнихой") +"...")),
													 pcharrepphrase(RandPhraseSimple("Я полагал, ","Я надеялся, ")+RandPhraseSimple("что вы покинули наш остров.","что больше никогда вас не увижу.")
													 +RandPhraseSimple(" Мертвецы висят у вас на шее, как мельничные жернова..."," Скольких моряков вы отправили гнить среди кораллов?!"),
													 "Капитан " + GetFullName(pchar)+", ваша страсть к коммерции превосходит все мои ожидания!"
													 +RandPhraseSimple(" Хотите сделать последние покупки перед отплытием?", " Вы хотите купить что-то особенное?"))),
										"cycle", 10, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(NPCharRepPhrase(npchar,
			                                        pcharrepphrase("Давай, показывай, что у тебя есть, старый пират!",
													               "Я всего лишь хочу посмотреть на ваши товары, любезный."),
													pcharrepphrase("Клянусь виселицей, " +GetFullName(npchar)+", я не позволю тебе водить меня за нос! Живо показывай свои товары!",
													               "Давайте посмотрим ваши товары, " +GetAddress_FormToNPC(NPChar)+ ".")),
											   NPCharRepPhrase(npchar,
											        pcharrepphrase("Это точно! Мертвые не кусаются! Ну, что у тебя в трюме есть?",
													               "Вы, милейший, лучше займитесь своим делом. Какие товары можете мне предложить?"),
												    pcharrepphrase("Однажды и ты станешь моим призом, хе-хе. Шучу. Давай свои товары.",
													               "Давайте обсудим торговые дела, " +GetAddress_FormToNPC(NPChar)+ " " +GetFullName(npchar)+ "")),
											   NPCharRepPhrase(npchar,
											        pcharrepphrase("Что мне надо? Хочу купить кое-что!",
													               "Пьянство вас сведет в могилу, " +GetFullName(npchar)+ ". Мне нужно посмотреть ваши товары."),
												    pcharrepphrase("Знаю я твои скидки! Два фунта какао по цене трех! Живо показывай свои товары",
													               "Это всегда приятно. Давайте поторгуемся.")),
											  "Показывай товары, меньше слов и больше дела. Я тороплюсь.",
											  npchar, Dialog.CurrentNode);
			link.l1.go = "market";
			link.l2 = HeroStringReactionRepeat(NPCharRepPhrase(npchar,
			                                        pcharrepphrase("Эх, так бы и "+ GetSexPhrase("прирезал","прирезала") +" кого-нибудь! Ладно, давай к делу.",
													               "Перейдем к другим делам, милейший."),
													pcharrepphrase("Каррамба! Я совсем по другому делу!",
													               "Мне нужно с вами поговорить по делу, "+GetAddress_FormToNPC(NPChar)+" " +GetFullName(npchar)+".")),
											   NPCharRepPhrase(npchar,
											        pcharrepphrase("У меня к тебе дело, старый пират!",
													               "Перейдем к делам, милейший!"),
													pcharrepphrase("Клянусь дьяволом, тебе меня не обмануть, мошенник! У меня другое дело!",
													               "Полностью "+ GetSexPhrase("согласен","согласна") +", " +GetAddress_FormToNPC(NPChar)+ " " +GetFullName(npchar)+ ", я хочу обсудить с вами иные дела.")),
											   NPCharRepPhrase(npchar,
											        pcharrepphrase("Уже надрался, приятель?! У меня к тебе дело.",
													               "Я "+ GetSexPhrase("пришел","пришла") +" не торговать, любезный. У меня другое дело."),
													pcharrepphrase("Разрази тебя гром с твоими ценами, негодяй! У меня дело к тебе.",
													               "Скидки всегда приятны, " + GetAddress_FormToNPC(NPChar)+ " " +GetFullName(npchar)+ ", но я по другому делу.")),
											   NPCharRepPhrase(npchar,
											        pcharrepphrase("Придержи язык, старый пьяница, у меня дело к тебе",
													               "Тошнит вас от рома, я полагаю. Впрочем, я от вас тоже не в восторге. Перейдем к делу."),
													pcharrepphrase("Ты и так уже обобрал меня до нитки, мошенник! У меня к тебе дело.",
													               "Ваша ирония неуместна, у меня к вам дело иного порядка")),
											   npchar, Dialog.CurrentNode);
			link.l2.go = "business";
			link.l3 = HeroStringReactionRepeat(NPCharRepPhrase(npchar,
			                                        pcharrepphrase("Сначала дело, потом веселье. Хочу у тебя узнать кое-что.",
													               "Не сейчас, мне нужна информация."),
													pcharrepphrase("К черту цены! Сначала ты скажешь все, что мне нужно.",
													               "С удовольствием. Я хочу узнать кое-что.")),
											   NPCharRepPhrase(npchar,
											        pcharrepphrase("Спасибо за совет, старый убийца. Мне надо кое-что узнать.",
													               "У меня определенный вопрос."),
												    pcharrepphrase("Золото подождет. Я хочу узнать кое-что.",
													               "Да, я "+ GetSexPhrase("согласен","согласна") +". Хочу вас спросить кое о чем.")),
											   NPCharRepPhrase(npchar,
											        pcharrepphrase("Я думаю, ты знаешь, о чем я хочу спросить.",
													               "Я надеюсь, вы ответите мне на мой вопрос."),
													pcharrepphrase("У тебя в голове есть что-нибудь кроме ценников? Об этом я и хочу спросить.",
													               "Речь не об этом. Мне нужна кое-какая информация.")),
											   NPCharRepPhrase(npchar,
											        pcharrepphrase("Не кипятись, старина! Я просто хочу спросить тебя.",
													               "Не волнуйтесь так, вас хватит удар. Ответьте мне на вопрос, и я уйду"),
													pcharrepphrase("Не жду от тебя умного слова - ум у тебя тараканий. Но ты кое-что знаешь.",
													               "Я не задержу вас надолго. Всего один вопрос.")),
											   npchar, Dialog.CurrentNode);
			link.l3.go = "quests";
			// --> Jason, генер почтового курьера 2 уровня
			if (CheckAttribute(PChar, "questTemp.WPU.Postcureer.LevelUp"))
			{
				if (pchar.questTemp.WPU.Postcureer.TargetPortmanID == npchar.id)
				{
					link.l12 = "Я доставил вам сводку цен из города "+XI_ConvertString("Colony"+pchar.questTemp.WPU.Postcureer.StartCity+"Gen")+".";
					link.l12.go = "Postcureer_LevelUp_ForAll";
				}
			}
			//<--генер почтового курьера 2 уровня	
						
			//Jason --> мини-квест Дефицитный товар
			if (CheckAttribute(pchar, "questTemp.Wine.Trader") && NPChar.location == pchar.questTemp.Wine.City + "_store" && !CheckAttribute(pchar, "questTemp.Wine.fail"))
			{
				link.l13 = "Я хочу приобрести у вас партию европейского вина, бутылок пятьдесят-шестьдесят. Мне сказали, что оно у вас имеется в достаточном количестве."; 
				link.l13.go = "Wine_Trader";
			}
			if (CheckAttribute(pchar, "questTemp.Wine.Repeat2") && NPChar.location == pchar.questTemp.Wine.City + "_store" && CheckCharacterItem(pchar, "letter_1") && !CheckAttribute(pchar, "questTemp.Wine.fail"))
			{
				link.l13 = "Здравствуйте еще раз. Прочтите вот это письмо, и, быть может, вы пересмотрите вопрос о продаже вина?"; 
				link.l13.go = "Wine_Repeat2";
			}
			if (CheckAttribute(pchar, "questTemp.Wine.wait") && NPChar.location == pchar.questTemp.Wine.City + "_store" && !CheckAttribute(pchar, "questTemp.Wine.fail"))
			{
				link.l13 = "Это опять я. Давайте продолжим нашу прерванную торговлю вином, я раздобыл денег побольше."; 
				link.l13.go = "Wine_Price";
			}
			// <-- мини-квест Дефицитный товар
						
			if(CheckAttribute(pchar,"GenQuest.EncGirl"))
			{
				if(pchar.GenQuest.EncGirl == "toLoverFather" && pchar.GenQuest.EncGirl.LoverFather == "store_keeper" && pchar.GenQuest.EncGirl.LoverCity == npchar.city)
				{
					link.l9 = "Здравствуйте, я приш"+ GetSexPhrase("ел","ла") +" по приглашению вашего сына."; 
					link.l9.go = "EncGirl_4";
					pchar.quest.EncGirl_GetLoverFather.over = "yes";
				}
				if(pchar.GenQuest.EncGirl == "toParents" || pchar.GenQuest.EncGirl == "FindLover")
				{
					if(pchar.GenQuest.EncGirl.Father == "store_keeper" && npchar.city == pchar.GenQuest.EncGirl.city)
					{
						link.l9 = "Я по поводу вашей дочери...";
						link.l9.go = "EncGirl_1";
					}
				}				
			}			
			link.l5 = HeroStringReactionRepeat(NPCharRepPhrase(npchar,
			                                        pcharrepphrase("Пока, старый пропойца.",
													               "Всего доброго, "+GetAddress_FormToNPC(NPChar)+" " +GetFullName(npchar)+"."),
													pcharrepphrase("Каррамба! Никуда не уходи. Я еще зайду.",
													               "Приятно было вас видеть, "+GetAddress_FormToNPC(NPChar)+" " +GetFullName(npchar)+"! До свидания!")),
											   NPCharRepPhrase(npchar,
											        pcharrepphrase("Отдать швартовы!",
													               "До свидания, милейший."),
													pcharrepphrase("Эй! Ты что там прячешь? Ром? Нет!?! Ну ладно, пойду, горло промочу.",
													               "Прошу меня извинить, у меня срочные дела в городе.")),
											   NPCharRepPhrase(npchar,
											        pcharrepphrase("Хех! Еще увидимся!",
													               "Мне надо идти. Прощайте, "+GetAddress_FormToNPC(NPChar)+" " +GetFullName(npchar)+"!"),
													pcharrepphrase("И не смей мне перечить! Недосуг мне тут с тобой спорить!",
													               "Пожалуй, стоит проверить, как дела на корабле. Прощайте, "+GetAddress_FormToNPC(NPChar)+" " +GetFullName(npchar)+"!")),
											   NPCharRepPhrase(npchar,
											        pcharrepphrase("Что с тобой, старина? Это же я - " +GetFullName(pchar)+ "! Проспись, я потом зайду.",
													               "Боюсь, ваша печень прикончит вас раньше, чем я еще раз зайду сюда."),
													pcharrepphrase("Считай свои дублоны и гинеи, пройдоха! Я еще зайду.",
													               ""+ GetSexPhrase("Рад был","Рада была") +" вас видеть, " + GetAddress_FormToNPC(NPChar)+" " +GetFullName(npchar)+"!")),
											  npchar, Dialog.CurrentNode);
			link.l5.go = "exit";
		break;

		case "market":
//navy -->
			//занят ПГГ
			if (CheckFreeServiceForNPC(NPChar, "Store") != -1)	 // to_do имя сунуть
			{
				dialog.text = "Извините, но я сейчас занят. Другие клиенты! Заходите завтра.";
				link.l1 = "Да что вы говорите! Ладно, зайду попозже.";
				link.l1.go = "exit";
				break;
			}
//navy <--
			dialog.text = RandPhraseSimple("У меня есть пушечные ядра, парусина, лекарства, ценная древесина и другие товары! Что вас интересует?", "Хотите купить сахару и пряностей? Или, быть может, рому и пороху?");
			link.l1 = pcharrepphrase(LinkRandPhrase("В моем трюме полно добычи! Деньги не пахнут, не так ли?",
			                         "Мне нужно освободить свой трюм от добычи и набить его твоим золотом. Ха-ха!",
									 "За полновесные дублоны ты и родную мать продашь! Но мне всего лишь нужно пополнить запасы."),
									 LinkRandPhrase("Хочу продать груз и пополнить запасы.",
			                         "Я хочу купить товар на продажу.",
									 "Покажи мне ядра, бомбы и прочие товары."));
			link.l1.go = "trade_1";

			if(IsPCharHaveTreasurer() && CheckAttribute(PChar, "TransferGoods.Enable")) // Автозакупка товаров
			{
				link.l5 = "Мой казначей сделает необходимые закупки...";
				link.l5.go = "TransferGoods";
			}
			
			link.l3 = pcharrepphrase(RandPhraseSimple("Отчаливаю без торговли. Бывай!",
			                                          "Пойду, горло промочу. Никуда не уходи."),
									 RandPhraseSimple("Нет, мне сейчас не до покупок. Прощайте.",
									                  "Извините, у меня срочное дело. До свидания!"));
			link.l3.go = "exit";
		break;
		
		case "EncGirl_1":
			dialog.text = "Слушаю вас внимательно.";
			link.l1 = "Я привел"+ GetSexPhrase("","а") +" вашу беглянку.";
			link.l1.go = "EncGirl_2";
		break;
		
		case "EncGirl_2":
			dialog.text = "Ах, капитан, спасибо вам большое! Как она? здорова, не пострадала? Уж скоро сутки, как убежала, негодница. Разве ж я ей плохого желаю? Замуж отдать собрался... Жених богатый, молодой, а что собою не пригож, так ведь с лица воду не пить. Нет! она всё по-своему норовит - вся в мать, чтоб её\nХотя, и она бы на свет не появилась, если бы её мамаша в своё время не сбежала с одним предприимчивым оболтусом... ну да что вспоминать... Молодость наивна, глупа... и жестока.";
			link.l1 = "Конечно, вы отец и решать вам, но я бы не торопил"+ GetSexPhrase("ся","ась") +" со свадьбой...";
			link.l1.go = "EncGirl_3";
		break;
		
		case "EncGirl_3":
			dialog.text = "Да что вы понимаете?.. У вас свои дети есть? Нету? Вот, когда будут - заходите, тогда и поговорим\nДа... я обещал вознаграждение тому, кто её вернёт - примите пожалуйста.";
			link.l1 = "Спасибо. И держите её покрепче. Что-то мне подсказывает, что она на этом не остановится.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("EncGirl_ToLoverParentsExit");
		break;
		
		case "EncGirl_4":
			if(sti(pchar.GenQuest.EncGirl.LoverFatherAngry) == 0)
			{
				dialog.text = "А, так вы и есть "+ GetSexPhrase("тот капитан, который привёз","та девушка, которая привезла") +" моего блудного сына с молодой невестой?";
				link.l1 = "Да, это я помог"+ GetSexPhrase("","ла") +" им сбежать.";
				link.l1.go = "EncGirl_5";
			}
			else
			{
				dialog.text = "А-а, явил"+ GetSexPhrase("ся, благодетель","ась, благодетельница") +". Небось награды ждёшь?";
				link.l1 = "Ну, не то, чтобы награды, но благодарность услышать не мешало бы.";
				link.l1.go = "EncGirl_6";			
			}
		break;
		
		case "EncGirl_5":
			dialog.text = "Я очень вам благодарен, что не оставили моё чадо в затруднительном положении и помогли ему с честью выйти из столь щекотливой ситуации. Разрешите отблагодарить вас, как могу. Примите эту скромную сумму и подарок от меня лично.";
			link.l1 = "Благодарю вас, мне было приятно помогать этим молодым людям.";
			link.l1.go = "EncGirl_5_1";
		break;
		
		case "EncGirl_6":
			dialog.text = "Какая благодарность?! за что благодарность?! Мало того, что этот оболтус уже полгода слоняется без работы, так ещё и любезничать время нашёл! Да я в его годы уже своё дело держал. А он, ишь, разохотился! У губернатора, вон, дочка на выданье, а этот приволок какую-то шалаву безродную, прости Господи, и благословения родительского испрашивает!";
			link.l1 = "Хм, значит вы не верите в искренние чувства?";
			link.l1.go = "EncGirl_6_1";		
		break;
		
		case "EncGirl_5_1":
			AddMoneyToCharacter(pchar, sti(pchar.GenQuest.EncGirl.sum));
			GiveItem2Character(pchar, pchar.GenQuest.EncGirl.item);
			AddQuestRecord("JungleGirl", "18");
			CloseQuestHeader("JungleGirl");
			DeleteAttribute(pchar, "GenQuest.EncGirl");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "EncGirl_6_1":
			dialog.text = "Какие такие чувства?! О каких чувствах вы говорите? Взрослый, вроде человек, а туда же... чувства! Стыдно вам должно быть молодёжи в таких делах потакать да в сводни подряжаться. Девчонку из родительского гнезда вырвали и моему молокососу жизнь сломали. Не будет вам никакой благодарности. Прощайте.";
			link.l1 = "Что ж, и вам не хворать...";
			link.l1.go = "EncGirl_6_2";
		break;
		
		case "EncGirl_6_2":
			ChangeCharacterComplexReputation(pchar,"nobility", -1);
			AddQuestRecord("JungleGirl", "19");
			AddQuestUserData("JungleGirl", "sSex", GetSexPhrase("ел","ла"));
			AddQuestUserData("JungleGirl", "sSex1", GetSexPhrase("","а"));
			CloseQuestHeader("JungleGirl");
			DeleteAttribute(pchar, "GenQuest.EncGirl");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();		
		break;
		
		// Warship. Автозакупка товаров -->
		case "TransferGoods":
			ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
			
			if(sti(Pchar.Ship.Type) != SHIP_NOTUSED && ok)
			{
				dialog.text = LinkRandPhrase("...Уже сделал. Нужно только определьться, на борт какого корабля доставлять товары.",
					"Ваш казначей уже это сделал. Давайте определимся с кораблем, на который будут доставлены товары.",
					"Да, " + PChar.name + ", я знаю. Он уже был у меня с визитом. На какой корабль будем грузить товары?");
					
				for(i=0; i<COMPANION_MAX; i++)
				{
					cn = GetCompanionIndex(PChar, i);
					if(cn > 0)
					{
						chref = GetCharacter(cn);
						if(!GetRemovable(chref)) continue;
						
						attrL = "l"+i;
						Link.(attrL)    = "На " + XI_ConvertString(RealShips[sti(chref.Ship.Type)].BaseName) + " '" + chref.Ship.Name + "'.";
						Link.(attrL).go = "TransferGoodsTo_" + chref.id;
					}
				}
				
				Link.l99    = "Я передумал"+ GetSexPhrase("","а") +", ничего не нужно.";
				Link.l99.go = "exit";
			}
			else // Корабля нету
			{
				dialog.text = NPCharRepPhrase(npchar, pcharrepphrase("Дуришь меня? А где же твой корабль? У пирса его нет!",
					"Клянусь дьяволом, тебе не обмануть меня! У пирса нет твоего корабля!"),
					pcharrepphrase("Я не вижу вашего корабля в порту, капитан " +GetFullName(pchar)+ ". Надеюсь, это не 'Летучий голландец'?",
					"Капитан, удобнее грузить товар с пирса. Пришвартуйте корабль и приходите."));
				link.l1 = NPCharRepPhrase(npchar, pcharrepphrase("" +RandSwear()+"Какая неприятность!!! Ладно, старый проныра, еще увидимся!",
					"Я не хотел"+ GetSexPhrase("","а") +" вас обмануть " +GetFullName(npchar)+ ", корабль на другой стороне острова."),
					pcharrepphrase("Нет. Мой корабль называется Black Pearl. Что это ты побелел? Ха-ха! Шутка!",
					"Спасибо за совет, обязательно им воспользуюсь."));
				link.l1.go = "exit";
			}
			break;
			
		case "TransferGoods_2": // Тут уже не проверяем, есть корабль или нету (выбрали корабль, в который груз не помещается)
			dialog.text = LinkRandPhrase("Ну так что, кэп, на какой корабль будем грузить товары?",
				"Так на какой корабль будем товары грузить?",
				PChar.name + ", так в трюм какого корабля будем производить погрузку?");
				
			for(i=0; i<COMPANION_MAX; i++)
			{
				cn = GetCompanionIndex(PChar, i);
				if(cn > 0)
				{
					chref = GetCharacter(cn);
					if(!GetRemovable(chref)) continue; // Если квестовый - пропускаем
					
					attrL = "l"+i;
					Link.(attrL)    = "На " + XI_ConvertString(RealShips[sti(chref.Ship.Type)].BaseName) + " '" + chref.Ship.Name + "'.";
					Link.(attrL).go = "TransferGoodsTo_" + chref.id;
				}
			}
			
			Link.l99    = "Я передумал"+ GetSexPhrase("","а") +", ничего не нужно.";
			Link.l99.go = "exit";
			break;
			
		case "TransferGoods_Start":
			chref = CharacterFromID(NPChar.CharToTransferGoodsID);
			
			iQuantityGoods = TransferGoods_CalculateWeight(chref);
			
			if(GetCargoFreeSpace(chref) >= iQuantityGoods)
			{
				if(TransferGoods_StartTransfer(chref, NPChar.City) != 0)
				{
					dialog.text = LinkRandPhrase("Все готово! На выбранный корабль началась погрузка.", 
						"Ну вот, товар начали погружать на выбранный корабль.",
						"Кэп, погрузка товара в трюм выбранного корабля начилась.");
					link.l1 = "Спасибо. С вами приятно иметь дело.";
					link.l1.go = "exit";
          SetPriceListByStoreMan(rColony); // mitrokosta обновляем список цен
					WaitDate("", 0, 0, 0, 1, 0); // Крутим время
				}
				else
				{
					dialog.text = LinkRandPhrase("Капитан, весь товар, который запросил ваш казначей, уже есть на борту указанного вами судна!", 
						"Кэп, весь товар уже присутствует на указанном вами корабле!",
						"Кэп, данный корабль в обслуживании не нуждается, так как весь товар на нем уже присутствует.");
					link.l1 = "Да, точно.";
					link.l1.go = "exit";
					link.l2 = "Пожалуй, нужно выбрать другой корабль.";
					link.l2.go = "TransferGoods_2";
				}
			}
			else
			{
				dialog.text = LinkRandPhrase("Сдается мне, столько товара на этот тип корабля не влезет.", 
					"Кэп, столько товара в трюм этого корабля не поместится!",
					"Капитан, столько товара не поместится в трюм этого корабля!");
				link.l1 = "Да, пожалуй. Нужно выбрать другой корабль.";
				link.l1.go = "TransferGoods_2";
				link.l2 = "Я тут подумал"+ GetSexPhrase("","а") +"... Не нужно ничего закупать.";
				link.l2.go = "exit";
			}
			break;
		// <-- Автозакупка товаров

		case "trade_1":
            ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
		    if (sti(Pchar.Ship.Type) != SHIP_NOTUSED && ok)
			{
			    NextDiag.CurrentNode = NextDiag.TempNode;
			    DialogExit();
			    Pchar.PriceList.StoreManIdx = rColony.index; // boal 27.02.05
			    LaunchStore(sti(rColony.StoreNum));
			}
			else
			{
			    dialog.text = NPCharRepPhrase(npchar, pcharrepphrase("Дуришь меня? А где же твой корабль? У пирса его нет!",
				                                                     "Клянусь дьяволом, тебе не обмануть меня! У пирса нет твоего корабля!"),
													  pcharrepphrase("Я не вижу вашего корабля в порту, капитан " +GetFullName(pchar)+ ". Надеюсь, это не 'Летучий голландец'?",
													                 "Капитан, удобнее грузить товар с пирса. Пришвартуйте корабль и приходите."));
				link.l1 = NPCharRepPhrase(npchar, pcharrepphrase("" +RandSwear()+"Какая неприятность!!! Ладно, старый проныра, еще увидимся!",
				                                                 "Я не хотел"+ GetSexPhrase("","а") +" вас обмануть " +GetFullName(npchar)+ ", корабль на другой стороне острова."),
												  pcharrepphrase("Нет. Мой корабль называется Black Pearl. Что это ты побелел? Ха-ха! Шутка!",
												                 "Спасибо за совет, обязательно им воспользуюсь."));
			    link.l1.go = "exit";//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			}
		break;

		case "storage_0":
			NPChar.MoneyForStorage = GetNpcQuestPastMonthParam(NPChar, "Storage.Date") * sti(NPChar.Storage.MoneyForStorage); 
			if(sti(NPChar.MoneyForStorage) > 0) 
			{
				dialog.text = "С вас за аренду еще " + FindRussianMoneyString(sti(NPChar.MoneyForStorage)) + ".";
				if(sti(pchar.money) >= sti(NPChar.MoneyForStorage))
				{
					link.l1 = "Хорошо, сейчас оплачу аренду.";
					link.l1.go = "storage_3";
				}
				else
				{
					link.l1 = "Я зайду попозже.";
					link.l1.go = "exit";
				}
			}		
			else
			{
				dialog.text = "Проходите.";
				link.l1 = "Спасибо.";
				link.l1.go = "storage_2";
			}
			link.l2 = "Нет, я передумал"+ GetSexPhrase("","а") +".";
			link.l2.go = "exit"; 						
		break;
		
		case "storage_01":
			NPChar.MoneyForStorage = GetStoragePriceExt(NPChar, pchar); 
			dialog.text = "Да, у меня есть припортовый пакгауз - вместимость 50000 ц. За " + FindRussianMoneyString(sti(NPChar.MoneyForStorage)) + " в месяц я готов обеспечить сохранность ваших запасов. "+
				"Это включает услуги по охране, защиту от подтопления и борьбу с грызунами. Ну, что скажете? Только эм-м... оплату за месяц попрошу вперёд.";	
			link.l1 = "Годится. Могу я его осмотреть? У вас там крысы небось шуруют?";
			link.l1.go = "storage_1";
			link.l2 = "Да нет, я просто так спросил"+ GetSexPhrase("","а") +". Может когда и понадобится...";
			link.l2.go = "exit";
		break;
		
		case "storage_1":
			NPChar.MoneyForStorage = GetStoragePriceExt(NPChar, pchar); 
			dialog.text = "Как я уже сказал - оплата за месяц вперёд. И никаких крыс!";
			if(sti(pchar.money) >= sti(NPChar.MoneyForStorage))
			{
				link.l1 = "Экий вы... меркантильный. Держите свои деньги - я арендую этот сарай.";
				link.l1.go = "storage_11";
			}
			else
			{
				link.l1 = "Экий вы... меркантильный. Сейчас деньги принесу..";
				link.l1.go = "exit";
			}
		break;
		
		case "storage_11":
			AddMoneyToCharacter(pchar, -makeint(NPChar.MoneyForStorage)); 
			NPChar.Storage.MoneyForStorage = NPChar.MoneyForStorage;
			NPChar.Storage.Activate = true;
			Achievment_SetStat(pchar, 67, 1); // ugeen 2016
			SaveCurrentNpcQuestDateParam(NPChar, "Storage.Date");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LaunchStorage(sti(rColony.StoreNum));			
		break;
				
		case "storage_2":			
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LaunchStorage(sti(rColony.StoreNum));			
		break;
		
		case "storage_3":			
			AddMoneyToCharacter(pchar, -sti(NPChar.MoneyForStorage)); 
			NPChar.MoneyForStorage = GetStoragePriceExt(NPChar, pchar);
			NPChar.Storage.MoneyForStorage = NPChar.MoneyForStorage;
			SaveCurrentNpcQuestDateParam(NPChar, "Storage.Date");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LaunchStorage(sti(rColony.StoreNum));			
		break;		

		case "storage_04":
			dialog.text = "Неужели освобождаете? Ай-яй-яй, такое великолепное место, такие выгодные условия. Уверяю - больше нигде на Карибах вам не предложат подобных услуг.";
			link.l1 = "Я же сказал"+ GetSexPhrase("","а") +" - освобождаю. Или вы предлагаете мне платить за хранение воздуха? Можете искать другого арендатора.";
			link.l1.go = "storage_4";
			link.l2 = "Нигде не предложат, говорите? Ладно, оставлю пока за собой.";
			link.l2.go = "exit";
		break;
		
		case "storage_4":
			NPChar.MoneyForStorage = GetNpcQuestPastMonthParam(NPChar,"Storage.Date") * sti(NPChar.Storage.MoneyForStorage); 
			if(sti(NPChar.MoneyForStorage) > 0) 			
			{
				dialog.text = "С вас за аренду еще " + FindRussianMoneyString(sti(NPChar.MoneyForStorage)) + ".";
				if(sti(pchar.money) >= sti(NPChar.MoneyForStorage))			
				{
					link.l1 = "Хорошо.";
					link.l1.go = "storage_5";
				}
			}
			else
			{
				dialog.text = "Забирайте свой товар и я закрою склад.";
				link.l1 = "Хорошо.";
				link.l1.go = "storage_6";
			}
		break;
		
		case "storage_5":
			SetStorageGoodsToShip(&stores[sti(rColony.StoreNum)]);
			AddMoneyToCharacter(pchar, -sti(NPChar.MoneyForStorage)); 
			NPChar.Storage.NoActivate = true;
			DeleteAttribute(NPChar,"Storage.Activate");
			DialogExit();
		break;
		
		case "storage_6":
			SetStorageGoodsToShip(&stores[sti(rColony.StoreNum)]);
			DeleteAttribute(NPChar,"Storage.Activate");
			NPChar.Storage.NoActivate = true;
			DialogExit();
		break;		

		case "business":
			iTest = 0;			
			
//Jason --> ----------------------------------мини-квест Бесчестный конкурент------------------------------------
			if (!CheckAttribute(pchar, "questTemp.Shadowtrader") && sti(npchar.nation) != PIRATE && sti(pchar.rank) < 6 && drand(2) == 0) 
			{
				dialog.text = "Капитан, я хочу попросить вас об одной услуге. Не поможете мне?";
				link.l1 = "Чем я могу вам помочь?"; 
				link.l1.go = "Shadowtrader_begin";
				break;
			}
			
			if (CheckAttribute(pchar, "questTemp.Shadowtrader"))
			{
				if(pchar.questTemp.Shadowtrader == "begin" && GetNpcQuestPastDayParam(npchar, "Shadowtrader_date") < 5 && NPChar.location == pchar.questTemp.Shadowtrader.City + "_store")
				{
					dialog.text = "Спасибо, капитан, что выполнили мою просьбу. Теперь, когда "+pchar.questTemp.Shadowtrader.Guardername+" здесь, я могу чувствовать себя хоть немного спокойнее.";
					link.l1 = "Хм... Не сочтите за навязчивость, но мне кажется, что у вас какие-то проблемы. Может, расскажете - а вдруг я смогу вам помочь?"; 
					link.l1.go = "Shadowtrader_fort";
					break;
				}
				if(CheckAttribute(pchar, "questTemp.Shadowtrader.Trouble") && NPChar.location == pchar.questTemp.Shadowtrader.City + "_store")
				{
					dialog.text = "Ну как? Вы передали мое письмо?";
					link.l1 = "Да передал. Комендант попросил передать ответ на словах - того, что написано в вашем письме недостаточно, чтобы городская стража предприняла какие-либо действия."; 
					link.l1.go = "Shadowtrader_trouble";
				pchar.quest.ShadowtraderTimeFort_Over.over = "yes";
					break;
				}
				if(CheckAttribute(pchar, "questTemp.Shadowtrader.End.Fort") && NPChar.location == pchar.questTemp.Shadowtrader.City + "_store" && GetQuestPastDayParam("pchar.questTemp.Shadowtrader.EndFort") > 0)
				{
					dialog.text = "Я уже слышал новость - сегодня ночью стража нашла подпольную торговую точку контрабандистов и всех арестовала. Заправлял всем этим один редкостный мерзавец. Ничего, теперь он долго никому не сможет пакостить\nКомендант рассказал мне о вашей роли в этом предприятии - спасибо вам огромное! Вы выполнили своё обещание! Вот, возьмите награду - 15 000 песо. Вы просто спасли меня! Теперь я займусь торговлей по-настоящему!";
					link.l1 = "Да не за что. Это было нетрудно."; 
					link.l1.go = "Shadowtrader_complete";
					break;
				}
				if(CheckAttribute(pchar, "questTemp.Shadowtrader.End.Escape") && NPChar.location == pchar.questTemp.Shadowtrader.City + "_store")
				{
					dialog.text = "Ну, что расскажете хорошего, " + pchar.name + "?";
					link.l1 = "Я разыскал вашего конкурента. Больше он не будет вам докучать - мне удалось... убедить его покинуть этот остров. Его 'магазин' находился в доме у городских ворот - что делать с брошеным товаром, решайте сами. Хотите - сдайте властям, хотите - попробуйте забрать себе."; 
					link.l1.go = "Shadowtrader_Escape_complete";
					break;
				}
				if(CheckAttribute(pchar, "questTemp.Shadowtrader.End.Free") && NPChar.location == pchar.questTemp.Shadowtrader.City + "_store")
				{
					dialog.text = "Я уже слышал новость - сегодня ночью стража обнаружила в одном из домов подпольную торговую точку контрабандистов. Два негодяя найдены мертвыми. Великолепная работа, " + pchar.name + ", я восхищаюсь вами! Вот, возьмите награду - 15 000 песо. Вы просто спасли меня! Теперь я займусь торговлей по-настоящему!\nУдовлетворите мое любопытство - их главный... тоже, среди этих двух мертвецов?";
					link.l1 = "Нет. Но он уже никогда не посмеет даже появиться в вашем городе. Думаю, сейчас он уже на расстоянии нескольких десятков миль от этого острова."; 
					link.l1.go = "Shadowtrader_complete";
					break;
				}
				if(CheckAttribute(pchar, "questTemp.Shadowtrader.End.Kill") && NPChar.location == pchar.questTemp.Shadowtrader.City + "_store")
				{
					dialog.text = "Я уже слышал новость - сегодня ночью стража обнаружила в одном из домов подпольную торговую точку контрабандистов. Три негодяя найдены мертвыми. Великолепная работа, " + pchar.name + ", я восхищаюсь вами! Вот, возьмите награду - 15 000 песо. Вы просто спасли меня! Теперь я займусь торговлей по-настоящему!\nУдовлетворите мое любопытство - их главный... тоже, среди этих трех мертвецов?";
					link.l1 = "Да. Вы навсегда избавлены от вашего конкурента. Более он вас не побеспокоит."; 
					link.l1.go = "Shadowtrader_complete";
					break;
				}
			}
			//<-- мини-квест Бесчестный конкурент
	
			//Jason --> генератор Сомнительное предложение
			/*if (drand(3) == 1 && !CheckAttribute(pchar, "GenQuest.Contraoffer.Trader") && !CheckAttribute(pchar, "GenQuest.Contraoffer.Slaves.Yes") && sti(npchar.nation) != PIRATE && 7-sti(RealShips[sti(pchar.ship.type)].Class) > 0) 
			{
				if (!CheckAttribute(npchar, "Contraoffer") || GetNpcQuestPastDayParam(npchar, "Contraoffer") >= 30) 
				{
					dialog.text = "О! Вы очень вовремя, капитан. Я бы хотел попросить вас оказать мне одну услугу.";
					link.l1 = "Давайте послушаем."; 
					link.l1.go = "Contraoffer";
					break;
				}
			}
		
			if (CheckAttribute(pchar, "GenQuest.Contraoffer.Trader") && NPChar.location == pchar.GenQuest.Contraoffer.Trader.City + "_store") 
			{
				dialog.text = "Внимательно вас слушаю, капитан.";
				link.l5 = "Я привез ваш заказ."; 
				link.l5.go = "Contraoffer_check";
			}
			
			if (!CheckAttribute(pchar, "GenQuest.Contraoffer.Slaves") && sti(npchar.quest.Contraoffer.chance) == 2 && GetNpcQuestPastDayParam(npchar, "Contraoffer") >= 30) //единичный вариант за всю игру, ака 'пасхалка'
			{
				dialog.text = "О! Вы очень вовремя, капитан. Мне нужна особенная услуга.";
				link.l5 = "Давайте послушаем."; 
				link.l5.go = "Contraoffer_slaves";
				break;
			}
			
			if (CheckAttribute(pchar, "GenQuest.Contraoffer.Slaves.Yes") && NPChar.location == pchar.GenQuest.Contraoffer.Slaves.City + "_store") 
			{
				dialog.text = "Внимательно вас слушаю, капитан.";
				link.l5 = "Я привез ваших рабов."; 
				link.l5.go = "Contraoffer_slaves_check";
			}*/
			// <-- генератор Сомнительное предложение
	
			//Jason --> генератор Неудачливый вор
			if (CheckAttribute(pchar, "GenQuest.Device.Shipyarder") && NPChar.location == pchar.GenQuest.Device.Shipyarder.City + "_store" && pchar.GenQuest.Device.Shipyarder == "begin" && !CheckAttribute(npchar, "quest.Device"))
			{
   				link.l16 = "Послушай, ты вот торгуешь всякой всячиной... Тебе вчера или сегодня, никто не предлагал купить "+pchar.GenQuest.Device.Shipyarder.Type+"?";
				link.l16.go = "Device_Trader";
			}
			// <-- генератор Неудачливый вор
			
			//Jason --> генератор Место под солнцем
			if (!CheckAttribute(pchar, "GenQuest.Sunplace.Trader") && !CheckAttribute(npchar, "quest.Sunplace") && sti(npchar.nation) != PIRATE && sti(pchar.rank) < 20 && drand(4) == 4) 
			{
				dialog.text = "Капитан, я хочу попросить вас оказать мне одну услугу. За ее выполнение я хорошо заплачу.";
				link.l1 = "Интересно. Рассказывайте, что там у вас?"; 
				link.l1.go = "Sunplace_begin";
				break;
			}
			
			if (CheckAttribute(pchar, "GenQuest.Sunplace.Trader") && pchar.GenQuest.Sunplace.Trader == "complete" && npchar.location == pchar.GenQuest.Sunplace.Trader.City + "_store") 
			{
				dialog.text = "Капитан, рад вас видеть. Я уже в курсе, что вы выполнили мою просьбу касательно "+pchar.GenQuest.Sunplace.Trader.Enemyname+".";
				link.l1 = "Хех! Это так. "+GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.Sunplace.Trader.ShipType), "Name")))+" "+pchar.GenQuest.Sunplace.Trader.ShipName+" и груз - " + GetGoodsNameAlt(sti(pchar.GenQuest.Sunplace.Trader.Goods))+ ", более вашему конкуренту не принадлежат."; 
				link.l1.go = "Sunplace_complete";
				break;
			}
			
			if (CheckAttribute(pchar, "GenQuest.Sunplace.Trader") && pchar.GenQuest.Sunplace.Trader == "complete_murder" && npchar.location == pchar.GenQuest.Sunplace.Trader.City + "_store") 
			{
				dialog.text = "Господи, капитан... Зачем вы его убили? Я же просил всего лишь потопить его судно! Пресвятая Дева, теперь на мне грех за смерть невинного человека...";
				link.l1 = "Хех! Что за чистоплюйство, " + npchar.name + "? Какая разница - он уже больше никогда не помешает вам!"; 
				link.l1.go = "Sunplace_complete_murder";
				break;
			}
			// <-- генератор Место под солнцем
			
//navy -->
			//занят ПГГ
			iTmp = CheckAvailableTaskForNPC(NPChar, PGG_TASK_WORKONSTORE);
			if (iTmp != -1)
			{
				dialog.text = "Была у меня работенка, но " + GetFullName(&Characters[iTmp]) + " уже взялся выполнить ее для меня.";
				link.l1 = "Да что вы говорите! Ладно, зайду попозже.";
				link.l1.go = "exit";
				break;
			}
//navy <--
			dialog.text = NPCharRepPhrase(npchar,"Дела?! Выкладывай все по порядку!","Я вас слушаю. О каком деле идет речь?");
            ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
            if (sti(Pchar.Ship.Type) != SHIP_NOTUSED && ok)
			{
    			if (CheckQuestAttribute("generate_trade_quest_progress", "begin") || CheckQuestAttribute("generate_trade_quest_progress",  "failed"))
    			{
    				if (pchar.CargoQuest.TraderID == npchar.id )
    				{
    					link.l1 = RandPhraseSimple("В трюме моего корабля груз для вашего магазина.", "Мой корабль зафрахтован для доставки груза в ваш магазин. Товар уже выгружают.");
    					link.l1.go = "generate_quest_2";
    				}
    				else
    				{
                        if (!CheckQuestAttribute("generate_trade_quest_progress",  "failed") && pchar.CargoQuest.GiveTraderID == npchar.id && GetNationRelation2MainCharacter(sti(characters[GetCharacterIndex(pchar.CargoQuest.TraderID)].nation)) == RELATION_ENEMY)
                        {
                            link.l1 = "К сожалению, я вынужден"+ GetSexPhrase("","а") +" отказаться от взятых обязательств. Политическая обстановка не позволяет мне доставить груз.";
            				link.l1.go = "generate_quest_cannot_done";
                        }
                        else
                        {
                            if (rand(1) == 1)
                            {
                                link.l1 = RandPhraseSimple("Я хочу предложить вам зафрахтовать мое судно для перевозки груза.",
								                           "У меня прекрасный корабль, и я могу доставить любой груз, куда только вы пожелаете.");
            				    link.l1.go = "generate_quest_not_closed";
        				    }
    				    }
    				}
    			}
    			else
    			{
    				link.l1 = "Не хотите зафрахтовать судно, " +GetAddress_FormToNPC(NPChar)+ "? У меня надежный корабль и опытные матросы.";
    				link.l1.go = "generate_quest";
    			}
    			// --> на кредитный генератор
    			if (CheckAttribute(pchar, "GenQuest.LoanChest.TakeChest") && sti(pchar.GenQuest.LoanChest.TargetIdx) == sti(NPChar.index))
    			{
	                link.l3 = pcharrepphrase(RandPhraseSimple("Эх, вымотал"+ GetSexPhrase("ся","ась") +" в море... Вот что, приятель, денежный вопрос стоит остро.",
	                                                          "Ну что, старый плут, давай обсудим дела наши денежные."),
	                                        RandPhraseSimple("Я хотел"+ GetSexPhrase("","а") +" бы обсудить с вами финансовые вопросы.",
	                                                         "Давайте обсудим финансовые вопросы, нам есть о чем переговорить."));,
	
	                link.l3.go = "LoanForAll";
                }
				//квест мэра - на связь с нашим шпионом
  				if (CheckAttribute(pchar, "GenQuest.Intelligence") && pchar.GenQuest.Intelligence.SpyId == npchar.id && pchar.GenQuest.Intelligence == "") 
				{
					link.l4 = RandPhraseSimple("Я здесь по поручению одного человека. Его зовут губернатор " + GetFullName(characterFromId(pchar.GenQuest.Intelligence.MayorId)) + ".", 
						GetFullName(characterFromId(pchar.GenQuest.Intelligence.MayorId)) + " прислал меня к вам. Я долж"+ GetSexPhrase("ен","на") +" кое-что забрать...");
					link.l4.go = "IntelligenceForAll";
				}	
				
				//homo 25/06/06 слухи
                link.l6 = pcharrepphrase(RandPhraseSimple("Расскажешь мне последние сплетни? Все равно торчишь тут целый день.",
                                                          "Не суетись, старый мошенник, а лучше расскажи, как течет жизнь на суше?"),
                                        RandPhraseSimple("Кажется, что провел"+ GetSexPhrase("","а") +" в море целую вечность. Что новенького в ваших краях?",
                                                         "Вы, наверное, знаете все последние новости? Что важного произошло?"));,

    		    link.l6.go = "rumours_trader";

				// ugeen --> склад товаров для ГГ
				if(CheckAttribute(NPChar,"Storage") && Pchar.location.from_sea == "Pirates_town")
				{
					if(CheckAttribute(NPChar,"Storage.Activate"))
					{
						link.l7 = "Проводите меня в пакгауз. Я хочу взглянуть на состояние своего склада.";
						link.l7.go = "storage_0";
						link.l8 = "Я решил"+ GetSexPhrase("","а") +" освободить пакгауз. Он мне больше без надобности.";
						link.l8.go = "storage_04";
					}
					else
					{
						if(!CheckAttribute(NPChar,"Storage.NoActivate"))
						{
							link.l7 = "Послушайте уважаемый, вы тут случайно складские помещения в аренду не сдаете?";
							link.l7.go = "storage_01";
						}	
					}
				}				
				// <-- ugeen
				// Jason --> квест губера на поиск дезертира
				if(CheckAttribute(pchar, "GenQuest.FindFugitive") && sti(NPChar.nation) == PIRATE)
				{
					link.l8 = "Послушай, я пытаюсь найти своего компаньона, "+pchar.GenQuest.FindFugitive.Name+" его зовут. В таверне Порт-Рояла мне сказали, что он собирался именно в ваше поселение. Не встречал этого человека?";
					link.l8.go = "FindFugitiveSt";
				}
				//<-- поиск дезертира
				
				// <-- homo
				link.l99 = "Впрочем, сейчас не до разговоров.";
    			link.l99.go = "no_quests";
			}
			else
			{
                link.l1 = NPCharRepPhrase(npchar, pcharrepphrase("" +RandSwear()+"Я оставил"+ GetSexPhrase("","а") +" корабль на другой стороне острова. Зайду попозже!", "Прошу меня простить, " +GetFullName(npchar)+ ", я зайду позже. Мой корабль еще не подошел к пирсу."), pcharrepphrase("Дьявол! Эти ротозеи не поставили корабль под погрузку! Зайду позже!", "Извините, я долж"+ GetSexPhrase("ен","на") +" приказать поставить свой корабль к пирсу!"));
                link.l1.go = "exit";
    			// --> на кредитный генератор
    			if (CheckAttribute(pchar, "GenQuest.LoanChest.TakeChest") && sti(pchar.GenQuest.LoanChest.TargetIdx) == sti(NPChar.index))
    			{
	                link.l3 = pcharrepphrase(RandPhraseSimple("Эх, вымотал"+ GetSexPhrase("ся","ась") +" в море... Вот что, приятель, денежный вопрос стоит остро.",
	                                                          "Ну что, старый плут, давай обсудим дела наши денежные."),
	                                        RandPhraseSimple("Я хотел"+ GetSexPhrase("","а") +" бы обсудить с вами финансовые вопросы.",
	                                                         "Давайте обсудим финансовые вопросы, нам есть о чем переговорить."));,
	
	                link.l3.go = "LoanForAll";
                }
				//квест мэра - на связь с нашим шпионом
  				if (CheckAttribute(pchar, "GenQuest.Intelligence") && pchar.GenQuest.Intelligence.SpyId == npchar.id && pchar.GenQuest.Intelligence == "") 
				{
					link.l7 = RandPhraseSimple("Я здесь по поручению одного человека. Его зовут губернатор " + GetFullName(characterFromId(pchar.GenQuest.Intelligence.MayorId)) + ".", 
						GetFullName(characterFromId(pchar.GenQuest.Intelligence.MayorId)) + " прислал меня к вам. Я долж"+ GetSexPhrase("ен","на") +" кое-что забрать...");
					link.l7.go = "IntelligenceForAll";
				}	
			}
		break;
		
		case "generate_quest":
			if (npchar.quest.trade_date != lastspeak_date || bBettaTestMode)
			{
				npchar.quest.trade_date = lastspeak_date;
				//проверка враждебности нам страны торговца
				if (sti(NPChar.nation) != PIRATE && GetNationRelation2MainCharacter(sti(NPChar.nation)) == RELATION_ENEMY)
				{
					dialog.text = "Нет, не нужно! По крайней мере, до тех пор, пока вы враждуете с " + NationNameAblative(sti(NPChar.nation)) + ".";
					link.l1 = "В таком случае, прощайте.";
					link.l1.go = "exit";
				}
				else
				{
                    // проверка на проф пригодность -->
                    if (isBadReputation(pchar, 42))
                    {
                        dialog.text = RandSwear() + "Ты ведь " + GetFullName(pchar)+ ", не так ли? О тебе " +
                                      RandPhraseSimple("ходят ужасные слухи","говорят не лучшим образом") + ", я не хочу иметь с тобой дело.";
						link.l1 = RandPhraseSimple("Эх... стоит человеку раз оступиться, и все будут в него плевать.",
						                           RandSwear()+ "Что же, в море есть занятия и поинтереснее, "+GetFullName(npchar)+".");
						link.l1.go = "exit";
                        break;
                    }
                    // проверка на проф пригодность <--
                    int iTradeNation = GenerateNationTrade(sti(NPChar.nation));

					if (iTradeNation < 0)
					{
						dialog.text = NPCharRepPhrase(npchar, "Эх, "+GetAddress_Form(NPChar)+", не до фрахтов сегодня. Приходите завтра.","Зайдите завтра. Возможно, я сделаю вам выгодное предложение.");
						link.l1 = "Хорошо, я зайду завтра.";
						link.l1.go = "exit";
					}
					else
					{
                        int storeMan = findStoreMan(NPChar, iTradeNation);
                        if (storeMan > 0)
                        {
                            //проверяем импорт/экспорт
							iTradeGoods = GOOD_COFFEE + drand(sti(GOOD_PAPRIKA - GOOD_COFFEE)); //Jason
    						//проверяем свободное место (при этом должно вмещаться по меньшей мере 100 единиц выбранного груза
    						RecalculateSquadronCargoLoad(pchar); // fix неверное место
    						iQuantityGoods = GetSquadronFreeSpace(pchar, iTradeGoods);
							if (sti(Goods[iTradeGoods].Weight)/sti(Goods[iTradeGoods].Units)*sti(iQuantityGoods) > 1500) iQuantityGoods = makeint(1500/(sti(Goods[iTradeGoods].Weight)/sti(Goods[iTradeGoods].Units))); //Jason: больше 1500 массы не дадим - большие фрахты только через ПУ
    						if (iQuantityGoods < 100)// это в шт. товара
    						{
    							dialog.text = NPCharRepPhrase(npchar, "В твою жалкую посудину не поместится весь груз, сегодня сделки не будет.","К сожалению, капитан "+GetFullName(pchar)+", для доставки груза мне нужен более вместительный корабль, чем ваш.");
    							link.l1 = NPCharRepPhrase(npchar, "У меня достойный корабль, но я понял вашу мысль. До свиданья.","Я вас понимаю, бизнес прежде всего. Прощайте.");
    							link.l1.go = "exit";
    						}
    						else
    						{
    							iQuantityGoods = iQuantityGoods - rand(makeint(iQuantityGoods/3)) - 10;
    							iMoney = makeint((iQuantityGoods * sti(Goods[iTradeGoods].Weight) / sti(Goods[iTradeGoods].Units)) * (4+rand(3) + GetSummonSkillFromNameToOld(pchar, SKILL_COMMERCE)) + 0.5);

    							pchar.CargoQuest.iTradeGoods = iTradeGoods;
    							pchar.CargoQuest.iQuantityGoods = iQuantityGoods;
    							pchar.CargoQuest.iMoney = iMoney;
    							pchar.CargoQuest.iTradeNation = iTradeNation;
    							pchar.CargoQuest.iDaysExpired = 25 + rand(5);
    							
    							pchar.CargoQuest.iTradeColony = Characters[storeMan].city;
    							pchar.CargoQuest.iTradeIsland = GetIslandByCityName(Characters[storeMan].city);
    							pchar.CargoQuest.TraderID     = Characters[storeMan].id;
    							pchar.CargoQuest.GiveTraderID = NPChar.id;
                                SaveCurrentQuestDateParam("CargoQuest");
    							string sNation = XI_ConvertString("Colony"+Characters[storeMan].city);
                                sTemp = "";
                                if (pchar.CargoQuest.iTradeIsland != Characters[storeMan].city)
								{
                                    sTemp = ", что на " + XI_ConvertString(pchar.CargoQuest.iTradeIsland+"Dat");
                                }
                                dialog.text =  "О! Я как раз хотел сам попросить вас об оказании мне одной услуги. Дело в том, что мне нужно доставить груз " +
                                               GetGoodsNameAlt(iTradeGoods)+ " в количестве " + FindRussianQtyString(iQuantityGoods) + " в город " +
                                           sNation + sTemp + ", и как можно быстрее. Если вы успеете сделать это за " +  FindRussianDaysString(makeint(pchar.CargoQuest.iDaysExpired)) +
                                           ", то по прибытии на место получите " +
                                           FindRussianMoneyString(iMoney) + " вознаграждения. Ну как?";
    							link.l1 = "Думаю, что я соглас"+ GetSexPhrase("ен","на") +".";
    							link.l1.go = "exit_trade";
    							link.l2  = "Не думаю, что мне это подходит.";
    							link.l2.go = "exit";
    						}
                        }
                        else
                        {
                            dialog.text = "Политическая обстановка в архипелаге не позволяет мне торговать. "+
                                          XI_ConvertString(NationShortName(sti(NPChar.nation))+"hunter") + " во вражде со всеми, и магазин остался только у меня.";
    						link.l1 = "О! Сожалею. Всего хорошего";
    						link.l1.go = "exit";
                        }
					}
				}
			}
			else
			{
				dialog.text = NPCharRepPhrase(npchar, "Давай проваливай, нет у меня времени на пустые разговоры!","Я же уже говорил вам сегодня, что у меня ничего для вас нет.");
				link.l1 = NPCharRepPhrase(npchar, "Ты обязан разговаривать учтиво, или я научу тебя вежливости!", "О, извините.");
				link.l1.go = "exit";
			}
		break;

		case "exit_trade":
			AddDialogExitQuest("trade_quest_open");
			Nextdiag.CurrentNode = Nextdiag.TempNode;
			DialogExit();
		break;

		case "generate_quest_2":
			if (pchar.quest.generate_trade_quest_progress == "failed")
			{
				dialog.text = RandSwear() + "Вы вспомнили о порученном вам деле слишком поздно, не находите? Мне пришлось заказывать товар повторно. Прощайте.";
				link.l1 = "Простите меня, но я так спешил"+ GetSexPhrase("","а") +". Возможно, если я покрою ваши убытки, это восстановит мою деловую репутацию?";
				link.l1.go = "generate_quest_failed";
				link.l9 = "Всего хорошего.";
				link.l9.go = "exit";
				ChangeCharacterComplexReputation(pchar,"nobility", -1);
			}
			else
			{
                iTradeGoods    =  makeint(pchar.CargoQuest.iTradeGoods);
                iQuantityGoods =  makeint(pchar.CargoQuest.iQuantityGoods);
                
                dialog.text = "Точно! Я его давно ждал. Вы должны доставить мне груз " +
                GetGoodsNameAlt(iTradeGoods) + " в количестве " + FindRussianQtyString(iQuantityGoods) + " и получить за это " +
                FindRussianMoneyString(sti(pchar.CargoQuest.iMoney)) + ".";
				link.l1 = "Именно так.";
				link.l1.go = "generate_quest_ready";
			}
		break;
		
		case "generate_quest_ready":
            iTradeGoods    =  makeint(pchar.CargoQuest.iTradeGoods);
            iQuantityGoods =  makeint(pchar.CargoQuest.iQuantityGoods);
            // блок кидалова нас на бабки -->
            if (rand(8) == 1 && sti(Goods[iTradeGoods].Cost) <= 44 && GetQuestPastDayParam("CargoQuest") > 5)
            {
                dialog.text = RandSwear() + "Я вынужден извиниться перед вами, "+GetAddress_Form(NPChar)+
                              ". Дело в том, что я " + RandPhraseSimple("в затруднительном положении и не смогу оплатить ваши услуги"," уже взял этот груз в другом месте по более выгодной цене")+
                              ". В качестве оплаты вашего фрахта я передаю вам весь доставленный вами груз.";
				link.l1 = RandSwear() + RandPhraseSimple("И я берег"+ GetSexPhrase("","ла") +" этот чертов груз от всех напастей!!! Я две сотни крыс из-за него убил"+ GetSexPhrase("","а") +"!",
                                                         "Вы ставите меня в безвыходное положение, и мне придется согласиться.");
				link.l1.go = "exit";
				ChangeCharacterComplexReputation(pchar,"nobility", 2);
				AddCharacterExpToSkill(pchar, "Sailing", 60);
				AddCharacterExpToSkill(pchar, "Leadership", 20);
				AddCharacterExpToSkill(pchar, "COMMERCE", 15);

				pchar.quest.generate_trade_quest_progress = "";
				pchar.quest.generate_trade_quest.over = "yes";
                
                AddQuestRecord("DELIVERY_TRADE_QUEST", "4");
                AddQuestUserData("DELIVERY_TRADE_QUEST", "sGoodGen", GetGoodsNameAlt(iTradeGoods));
			    AddQuestUserData("DELIVERY_TRADE_QUEST", "sTargetColony",XI_ConvertString("Colony"+pchar.CargoQuest.iTradeColony+"Dat"));
                CloseQuestHeader("DELIVERY_TRADE_QUEST");
                break;
            }
            // блок кидалова нас на бабки <--
			if (GetSquadronGoods(pchar, iTradeGoods) < iQuantityGoods)
			{
                iTmp = iQuantityGoods - GetSquadronGoods(pchar, iTradeGoods);
                dialog.text = "Вы привезли не весь товар!! Согласно условиям договора недостает еще "
                              + FindRussianQtyString(iTmp) + " груза.";
				link.l9 = RandPhraseSimple("Да, действительно. Придется восполнить недостачу. Зайду еще раз.",
                                           RandSwear() +"Дьявольские крысы попортили чертов груз. Я восполню недостачу и зайду еще раз.");
				link.l9.go = "exit";
                AddQuestRecord("DELIVERY_TRADE_QUEST", "8");
                AddQuestUserData("DELIVERY_TRADE_QUEST", "sHaveNotQty", iTmp);
                AddQuestUserData("DELIVERY_TRADE_QUEST", "sGoodGen", GetGoodsNameAlt(iTradeGoods));
			}
			else
			{
                dialog.text = "Замечательно! Вот ваша награда, капитан "+GetFullName(pchar)+".";
				link.l1 = "Приятно с вами работать.";
				link.l1.go = "exit";
				ChangeCharacterComplexReputation(pchar,"nobility", 3);
				AddCharacterExpToSkill(pchar, "Sailing", 100);
				AddCharacterExpToSkill(pchar, "Leadership", 30);
				AddCharacterExpToSkill(pchar, "COMMERCE", 100);

				AddMoneyToCharacter(pchar, makeint(pchar.CargoQuest.iMoney));
				pchar.quest.generate_trade_quest_progress = "";
				pchar.quest.generate_trade_quest.over = "yes";
				RemoveCharacterGoods(pchar, makeint(pchar.CargoQuest.iTradeGoods), makeint(pchar.CargoQuest.iQuantityGoods));
				
                OfficersReaction("good");
                
                AddQuestRecord("DELIVERY_TRADE_QUEST", "2");
                AddQuestUserData("DELIVERY_TRADE_QUEST", "sGoodGen", GetGoodsNameAlt(iTradeGoods));
			    AddQuestUserData("DELIVERY_TRADE_QUEST", "sTargetColony",XI_ConvertString("Colony"+pchar.CargoQuest.iTradeColony+"Gen"));
                CloseQuestHeader("DELIVERY_TRADE_QUEST");
			}
		break;
		
		case "generate_quest_failed":
            iTradeGoods    =  makeint(pchar.CargoQuest.iTradeGoods);
            iQuantityGoods =  makeint(pchar.CargoQuest.iQuantityGoods);
            iMoney =  3*makeint(iQuantityGoods * sti(Goods[iTradeGoods].Cost) / sti(Goods[iTradeGoods].Units));
			dialog.text = "Хорошо... Сумма в " + FindRussianMoneyString(iMoney) + " как раз покроет мои убытки от нарушения вами сроков доставки товара.";
			link.l1 = "Ого! Нет уж! Пожалуй, я не буду больше вообще возить эти чертовы грузы! В море их и так достаточно!";
			link.l1.go = "exit";
            if (sti(pchar.Money) >= iMoney)
            {
    			link.l2 = "Вот требуемая сумма";
    			link.l2.go = "generate_quest_failed_2";
			}
            else
            {
                AddQuestRecord("DELIVERY_TRADE_QUEST", "7");
                AddQuestUserData("DELIVERY_TRADE_QUEST", "sMoney", FindRussianMoneyString(iMoney));
    		    AddQuestUserData("DELIVERY_TRADE_QUEST", "sTargetColony",XI_ConvertString("Colony"+pchar.CargoQuest.iTradeColony+"Gen"));
            }
		break;
		
		case "generate_quest_failed_2":
            iTradeGoods    =  makeint(pchar.CargoQuest.iTradeGoods);
            iQuantityGoods =  makeint(pchar.CargoQuest.iQuantityGoods);
            iMoney =  3*makeint(iQuantityGoods * sti(Goods[iTradeGoods].Cost) / sti(Goods[iTradeGoods].Units));
			dialog.text = "Замечательно. Теперь я могу сообщить своим коллегам, что с вами все же можно иметь дело.";
			link.l1 = "Спасибо! В следующий раз я не подведу.";
			link.l1.go = "exit";
			ChangeCharacterComplexReputation(pchar,"nobility", 10);
			AddCharacterExpToSkill(pchar, "Sailing", -100);
			AddCharacterExpToSkill(pchar, "Leadership", -50);
			AddCharacterExpToSkill(pchar, "COMMERCE", -100);

			AddMoneyToCharacter(pchar, -iMoney);
			pchar.quest.generate_trade_quest_progress = "";
			pchar.quest.generate_trade_quest.over = "yes";

            AddQuestRecord("DELIVERY_TRADE_QUEST", "5");
            AddQuestUserData("DELIVERY_TRADE_QUEST", "sMoney", FindRussianMoneyString(iMoney));
            AddQuestUserData("DELIVERY_TRADE_QUEST", "sGoodGen", GetGoodsNameAlt(iTradeGoods));
		    AddQuestUserData("DELIVERY_TRADE_QUEST", "sTargetColony",XI_ConvertString("Colony"+pchar.CargoQuest.iTradeColony+"Gen"));
            CloseQuestHeader("DELIVERY_TRADE_QUEST");
		break;
		
		case "generate_quest_not_closed":
            iTradeGoods    =  makeint(pchar.CargoQuest.iTradeGoods);
            iQuantityGoods =  makeint(pchar.CargoQuest.iQuantityGoods);

            dialog.text = "Хм. Я слышал, что вы еще не выполнили обязательства по предыдущему фрахту, а уже просите новый. Вы должны были доставить груз " +
            LanguageConvertString(iSeaGoods, "seg_" + Goods[iTradeGoods].Name)+ " в " + XI_ConvertString("Colony"+pchar.CargoQuest.iTradeColony) + ".";
			link.l1 = "Да, точно! Вы правы!";
			link.l1.go = "exit";
		break;
		
		case "generate_quest_cannot_done":
            dialog.text = RandSwear() + GetAddress_Form(NPChar) +", вы подводите меня!!! Может, попытаетесь как-то решить эту проблему?";
			link.l1 = "Хорошо. Я постараюсь доставить груз.";
			link.l1.go = "exit";
			link.l2 = "Нет. Не смогу. Сожалею";
			link.l2.go = "generate_quest_cannot_done_2";
			
		break;
		
		case "generate_quest_cannot_done_2":
		    iTradeGoods    =  makeint(pchar.CargoQuest.iTradeGoods);
            iQuantityGoods =  makeint(pchar.CargoQuest.iQuantityGoods);
            if (GetSquadronGoods(pchar, iTradeGoods) < iQuantityGoods)
			{
				dialog.text = "Минуточку! Но на корабле нет такого количества товара!! Вам недостает еще "
                              + FindRussianQtyString(iQuantityGoods - GetSquadronGoods(pchar, iTradeGoods)) + " груза.";
				link.l9 = RandPhraseSimple("Да, действительно. Придется восполнить недостачу.",
                                           RandSwear() +"Корабельные крысы попортили груз. Я докуплю товар и зайду еще раз.");
				link.l9.go = "exit";
			}
			else
			{
                dialog.text = "Ладно, я понимаю... принимаю товар обратно.";
    			link.l1 = "Спасибо. В следующий раз я не подведу!";
    			link.l1.go = "exit";
    			ChangeCharacterComplexReputation(pchar,"nobility", -3);

				pchar.quest.generate_trade_quest_progress = "";
				pchar.quest.generate_trade_quest.over = "yes";
				RemoveCharacterGoods(pchar, makeint(pchar.CargoQuest.iTradeGoods), makeint(pchar.CargoQuest.iQuantityGoods));
                
                AddQuestRecord("DELIVERY_TRADE_QUEST", "6");
                AddQuestUserData("DELIVERY_TRADE_QUEST", "sGoodQty", FindRussianQtyString(sti(pchar.CargoQuest.iQuantityGoods)));
                AddQuestUserData("DELIVERY_TRADE_QUEST", "sGoodGen", GetGoodsNameAlt(iTradeGoods));
    		    AddQuestUserData("DELIVERY_TRADE_QUEST", "sTargetColony",XI_ConvertString("Colony"+pchar.CargoQuest.iTradeColony+"Dat"));
                CloseQuestHeader("DELIVERY_TRADE_QUEST");
            }
		break;

		//Jason --> -------------------мини-квест Бесчестный конкурент-------------------------------------------
		case "Shadowtrader_begin":
			pchar.questTemp.Shadowtrader = "true";
			pchar.questTemp.Shadowtrader.Guardername = GenerateRandomName_Generator(sti(npchar.nation), "man");
			dialog.text = "Не могли бы вы сходить в таверну, найти там человека по имени "+pchar.questTemp.Shadowtrader.Guardername+" и сказать, чтобы он побыстрее явился ко мне? Я ни на минуту не могу отлучиться из магазина, а этот болван сидит в таверне, хлещет ром и, конечно, не догадается прийти сюда сам, хотя уже находится у меня на службе.";
			link.l1 = "Всегда рад помочь, дружище. Тем более, что я и сам собирался в таверну заглянуть.";
			link.l1.go = "Shadowtrader_begin_1";
			link.l2 = "Ты что, смеешься? Я похож на мальчика на побегушках? Тут до таверны два шага, сам дойдешь, не рассыпешься.";
			link.l2.go = "exit";
		break;
		
		case "Shadowtrader_begin_1":
			dialog.text = "Спасибо! Скажите ему, чтобы шел сюда немедленно. Ох, да за что же мне такое наказание...";
			link.l1 = "Не переживайте. Сейчас я его к вам отправлю.";
			link.l1.go = "exit";
			pchar.questTemp.Shadowtrader.City = npchar.City;
			pchar.questTemp.Shadowtrader.nation = sti(npchar.nation);
			//создаем охранника
			sld = GetCharacter(NPC_GenerateCharacter("ShadowGuarder" , "officer_7", "man", "man", 10, sti(npchar.nation), 5, true, "quest"));
			FantomMakeCoolFighter(sld, 20, 50, 50, "topor_2", "pistol3", "bullet", 50);
			sld.name = pchar.questTemp.Shadowtrader.Guardername;
			sld.lastname = "";
			sld.dialog.FileName = "Quest\LineMiniQuests\ShadowTrader.c";
			sld.dialog.currentnode = "ShadowGuarder";
			sld.greeting = "pirat_common";
			LAi_SetSitType(sld);
			LAi_SetImmortal(sld, true);
			FreeSitLocator(pchar.questTemp.Shadowtrader.City + "_tavern", "sit_front1");
			ChangeCharacterAddressGroup(sld, pchar.questTemp.Shadowtrader.City + "_tavern", "sit", "sit_front1");
			SaveCurrentNpcQuestDateParam(npchar, "Shadowtrader_date");
		break;
		
		case "Shadowtrader_fort":
			dialog.text = "Помочь? Ах, капитан, мне действительно нужна ваша помощь. Не могли бы ли вы отнести вот это письмо коменданту как можно быстрее? Я заплачу вам за это пустяковое дело 300 монет - как я уже говорил, я не могу отлучится из магазина.";
			link.l1 = "Да без проблем. Давайте сюда ваше письмо.";
			link.l1.go = "Shadowtrader_fort_1";
			link.l2 = "Нет, уважаемый, у меня больше нет времени на подобную ерунду.";
			link.l2.go = "Shadowtrader_fort_end";
		break;
		
		case "Shadowtrader_fort_1":
			dialog.text = "Вот, держите. Постарайтесь передать его до конца сегодняшнего дня и доставить мне ответ!";
			link.l1 = "Не переживайте, всё сделаю в лучшем виде.";
			link.l1.go = "exit";
			GiveItem2Character(pchar, "letter_1");
			ChangeItemDescribe("letter_1", "itmdescr_letter_1"); // 240912
			pchar.questTemp.Shadowtrader.Tradername = GetFullName(npchar);
			SetFunctionTimerCondition("ShadowtraderTimeFort_Over", 0, 0, 1, false);
			pchar.questTemp.Shadowtrader = "current"
			pchar.questTemp.Shadowtrader.Fort = "true";
			AddQuestRecord("Shadowtrader", "1");
			AddQuestUserData("Shadowtrader", "sCity", XI_ConvertString("Colony"+pchar.questTemp.Shadowtrader.City+"Gen"));
		break;
		
		case "Shadowtrader_fort_end":
			dialog.text = "Что же, придется попросить кого-то другого. Извините, что отвлек вас от дел, капитан.";
			link.l1 = "Да ничего. До свидания!";
			link.l1.go = "exit";
			pchar.questTemp.Shadowtrader = "true";
		break;
		
		case "Shadowtrader_trouble":
			dialog.text = "Он так и сказал? Да какие же еще ему нужны доказательства?! Мой труп? Ну так скоро он их точно получит, если все продолжится и дальше!..";
			link.l1 = "Тише, тише, " + npchar.name + ", успокойтесь, а то так и впрямь до апоплексического удара недалеко. Выпейте воды... Расскажите мне наконец, что у вас за неприятности - может, я смогу вам помочь?";
			link.l1.go = "Shadowtrader_trouble_1";
			DeleteAttribute(pchar, "questTemp.Shadowtrader.Trouble");
		break;
		
		case "Shadowtrader_trouble_1":
			dialog.text = "Ах, капитан! Да, возьмите ваши 300 песо, я чуть не забыл от расстройства... Я расскажу вам, конечно, правда, не понимаю, чем вы сможете мне помочь. Мой бизнес на грани краха, и всё из-за проклятых контрабандистов и неведомого мерзавца, который ими руководит.";
			link.l1 = "Контрабандисты?";
			link.l1.go = "Shadowtrader_trouble_2";
			AddMoneyToCharacter(pchar, 300);
		break;
		
		case "Shadowtrader_trouble_2":
			dialog.text = "Именно! Эти негодяи явно решили выжить меня из города! До поры все было как обычно - они перепродавали запрещенный товар, патруль их отлавливал, если удавалось, они прятались и откупались. Но с недавнего времени они открыли где-то в городе подпольную лавочку, и стали торговать самым ходовым товаром по невероятно низким ценам!\nЯ не могу позволить себе такой роскоши - мне ведь нужно платить подати - и постепенно разоряюсь: моряки ко мне уже практически не заходят за товарами - все покупают у этих проходимцев.";
			link.l1 = "Но вы должны были в таком случае обратиться к властям! Это их обязанность - пресекать подобные беззакония.";
			link.l1.go = "Shadowtrader_trouble_3";
		break;
		
		case "Shadowtrader_trouble_3":
			dialog.text = "Результат последнего обращения вы видели сами. Губернатор слишком занят, а комендант не верит, что контрабандисты организовали подпольный магазин, или делает вид, что не верит - я уже допускаю и такое\nКонечно, зачем им этим заниматься? А я скажу: я уверен, что всё это придумал какой-то проходимец, желающий разорить меня и вытеснить из города, а потом он спокойно приберет мой бизнес к своим грязным ручонкам.";
			link.l1 = "Хм... ваше предположение небезосновательно. Это очень похоже на торгашей - таскать каштаны из огня чужими руками... ой, простите, вас я, конечно, не имел в виду.";
			link.l1.go = "Shadowtrader_trouble_4";
		break;
		
		case "Shadowtrader_trouble_4":
			dialog.text = "Да ничего... А недавно ко мне пришел какой-то оборванец, который нагло заявил, что если я буду и дальше поднимать шум, то они сожгут мой магазин\nВот я и нанял охранника. "+pchar.questTemp.Shadowtrader.Guardername+" обошелся мне недешево, но он профессионал, и я могу под его защитой чувствовать себя хоть немного спокойнее.";
			link.l1 = "Да уж... Неприятная история. Похоже, вы были правы - я ничем не могу вам помочь. Но я уверен, что всё образуется - подобные черные лавочки обычно долго не существуют. До свидания.";
			link.l1.go = "Shadowtrader_end";
			link.l2 = "Понятно. Послушайте, я могу попробовать вам помочь...";
			link.l2.go = "Shadowtrader_trouble_5";
		break;
		
		case "Shadowtrader_trouble_5":
			dialog.text = "Вы все-таки хотите предложить мне помощь? Но что вы предпримете?";
			link.l1 = "Я попытаюсь найти этого вашего 'коллегу' и... попробую убедить его не мешать вам жить. У меня иногда это неплохо получается - убеждать людей.";
			link.l1.go = "Shadowtrader_trouble_6";
		break;
		
		case "Shadowtrader_trouble_6":
			dialog.text = "Вы серьезно? Да благословит вас Господь на правое дело! Если вы избавите меня от этой пакости - обещаю, в долгу не останусь и щедро отплачу.";
			link.l1 = "Ну что же, считайте, что мы договорились. Я приступаю к поискам.";
			link.l1.go = "exit";
			pchar.questTemp.Shadowtrader.seeksmugglers = "true";
			AddQuestRecord("Shadowtrader", "2");
			AddQuestUserData("Shadowtrader", "sCity", XI_ConvertString("Colony"+pchar.questTemp.Shadowtrader.City+"Gen"));
		break;
		
		case "Shadowtrader_end":
			pchar.questTemp.Shadowtrader = "true";
			CloseQuestHeader("Shadowtrader");
			DialogExit();
		break;
		
		case "Shadowtrader_Escape_complete":
			dialog.text = "Это правда? Неужели я теперь смогу торговать спокойно? Спасибо вам огромное! Вот ваше вознаграждение - 15 000 песо. А товар в их доме лучше всего будет сдать коменданту. Еще раз спасибо!";
			link.l1 = "Да не за что. Это было нетрудно. Я же говорил вам - у меня есть дар убеждения.";
			link.l1.go = "Shadowtrader_complete";
		break;
		
		case "Shadowtrader_complete":
			dialog.text = "Заходите ко мне почаще, капитан - я всегда буду рад вас видеть.";
			link.l1 = "Всенепременно! А теперь позвольте откланяться - дела! Всего доброго и успехов в торговле, " + npchar.name + "!";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.Shadowtrader.End");
			AddMoneyToCharacter(pchar, 15000);
			pchar.questTemp.Shadowtrader = "complete";
			AddQuestRecord("Shadowtrader", "11");
			CloseQuestHeader("Shadowtrader");
		break;
	// <-- мини-квест Бесчестный конкурент
	
//Jason --> мини-квест Дефицитный товар
		case "Wine_Trader":
			dialog.text = "Да что вы такое говорите! Вас явно ввели в заблуждение - я европейским вином не торгую в таких количествах. Ну, бывает иногда одна-две бутылки. Вот нашего, местного - пожалуйста, сколько угодно, и не бутылок, а бутылей!";
			link.l1 = "Вот это да! Но мне же сказали...";
			link.l1.go = "Wine_Trader_1";
		break;
		
		case "Wine_Trader_1":
			dialog.text = "Не знаю, что вам там сказали, но я повторюсь: у меня европейского вина нет. Более по этому вопросу мне добавить нечего.";
			link.l1 = "Ну что же... пойду разбираться!";
			link.l1.go = "exit";
			AddQuestRecord("Wine", "5");
			AddQuestUserData("Wine", "sName", pchar.questTemp.Wine.Name);
			DeleteAttribute(pchar, "questTemp.Wine.Trader");
			pchar.questTemp.Wine.Repeat1 = "true";
		break;
		
		case "Wine_Repeat2":
			RemoveItems(PChar, "letter_1", 1);
			PlaySound("interface\important_item.wav");
			dialog.text = "Вот с этого и следовало начинать. А то знаете - ходят тут всякие, вопросы ненужные задают. Ну-с, приступим к торговле?";
			link.l1 = "Конечно!";
			link.l1.go = "Wine_Price";
			pchar.questTemp.Wine.wait = "true";
			DeleteAttribute(pchar, "questTemp.Wine.Repeat2");
			SetFunctionTimerCondition("Wine_wait", 0, 0, 7, false);
		break;
		
		case "Wine_Price":
			dialog.text = "Сколько бутылок вам нужно? Стоимость одной бутылки - 500 песо, минимальная партия - 20 бутылок.";
			link.l1 = "";
			Link.l1.edit = 4;
			link.l1.go = "Wine_Qty";
			link.l2 = "У меня сейчас недостаточно денег. Я приду позже.";
			link.l2.go = "Wine_Qty_exit";
		break;
		
		case "Wine_Qty":
			int iQty = sti(dialogEditStrings[4]);
			pchar.questTemp.Wine.Qty = sti(iQty);
			if (iQty < 20)
			{
				dialog.text = "Я не занимаюсь розничной торговлей, капитан. Кажется, вы говорили о большой партии.";
				link.l1 = "Прошу прощения... Давайте пересмотрим количество.";
				link.l1.go = "Wine_Price";
				break;
			}
			if (iQty > 70)
			{
				dialog.text = "К сожалению, такого количества у меня нет.";
				link.l1 = "Жаль... Давайте пересмотрим количество.";
				link.l1.go = "Wine_Price";
				break;
			}
			pchar.questTemp.Wine.Summ = sti(iQty)*500;
			dialog.text = ""+sti(iQty)+" бутылок? Хорошо. С вас " + FindRussianMoneyString(sti(pchar.questTemp.Wine.Summ))".";
			if (makeint(Pchar.money) >= sti(pchar.questTemp.Wine.Summ))
			{
				link.l1 = "Пожалуйста, получите.";
				link.l1.go = "Wine_Qty_1";
			}
			link.l2 = "У меня сейчас недостаточно денег. Я приду позже.";
			link.l2.go = "Wine_Qty_exit";
		break;
		
		case "Wine_Qty_exit":
			dialog.text = "Хорошо, только поторопитесь. Этот товар у меня долго не залеживается.";
			link.l1 = "Я скоро вернусь!";
			link.l1.go = "exit";
		break;
		
		case "Wine_Qty_1":
			AddMoneyToCharacter(pchar, -sti(pchar.questTemp.Wine.Summ));
			dialog.text = "Так... всё верно. Забирайте вашу покупку.";
			link.l1 = "Спасибо! Всего доброго.";
			link.l1.go = "Wine_Qty_2";
		break;
		
		case "Wine_Qty_2":
			pchar.quest.Wine_wait.over = "yes";//снять прерывание
			DeleteAttribute(pchar, "questTemp.Wine.wait");
			TakeNItems(pchar, "potionwine", sti(pchar.questTemp.Wine.Qty));
			PlaySound("interface\important_item.wav");
			Log_Info ("Вы получили вино");
			AddQuestRecord("Wine", "8");
			DialogExit();
		break;
		// <-- мини-квест Дефицитный товар
		
// Jason --> -------------------------генератор Сомнительное предложение----------------------------------------
		int iCGood, amount;
		case "Contraoffer":
			pchar.GenQuest.Contraoffer.Trader.Goods = SelectContrabandGoods(pchar);
			while (sti(pchar.GenQuest.Contraoffer.Trader.Goods) == -1)
			{
				pchar.GenQuest.Contraoffer.Trader.Goods = SelectContrabandGoods(pchar);
			}
			iCGood = sti(pchar.GenQuest.Contraoffer.Trader.Goods);
			pchar.GenQuest.Contraoffer.Trader.Qty = makeint(15*(sti(pchar.rank)+30)/(sti(Goods[iCGood].Weight)/sti(Goods[iCGood].Units))*(7-sti(RealShips[sti(pchar.ship.type)].Class)));//количество
			pchar.GenQuest.Contraoffer.Trader.Price = sti(Goods[iCGood].Cost)/sti(Goods[iCGood].Units)*3;//цена единицы товара
			pchar.GenQuest.Contraoffer.Trader.Summ = sti(pchar.GenQuest.Contraoffer.Trader.Price)*sti(pchar.GenQuest.Contraoffer.Trader.Qty);//сумма
			pchar.GenQuest.Contraoffer.Trader.Days = 30+drand(20);//срок
			pchar.GenQuest.Contraoffer.Trader.Chance = rand(5);//17% вероятности, что патруль накроет
			dialog.text = "Мне для проведения крупной сделки не хватает одного товара - " + GetGoodsNameAlt(iCGood)+ ". Проблема в том, что этот товар в нашей колонии - контрабанда, и на покупку его у торговых капитанов рассчитывать не приходится\nМне надо всего лишь " + FindRussianQtyString(sti(pchar.GenQuest.Contraoffer.Trader.Qty)) + " этого товара. Не окажете ли мне любезность привезти мне его? Я хорошо заплачу, по " + FindRussianMoneyString(sti(pchar.GenQuest.Contraoffer.Trader.Price)) + " за единицу, что в сумме составит " + FindRussianMoneyString(sti(pchar.GenQuest.Contraoffer.Trader.Summ)) + ". Да, и товар мне нужен не позже, чем через "+FindRussianDaysString(sti(pchar.GenQuest.Contraoffer.Trader.Days))+". Так вы поможете мне?";
			link.l1 = "Хм... Звучит заманчиво. Я согласен!";
			link.l1.go = "Contraoffer_1";
			link.l2 = "Возить контрабанду? Это мне не интересно.";
			link.l2.go = "exit";
			SaveCurrentNpcQuestDateParam(npchar, "Contraoffer");
		break;
		
		case "Contraoffer_1":
			dialog.text = "Замечательно! Я рад, что вы согласились. Жду вас с товаром.";
			link.l1 = "Скоро буду!";
			link.l1.go = "exit";
			rColony = GetColonyByIndex(FindColony(npchar.city));
			SetNull2StoreGood(rColony, sti(pchar.GenQuest.Contraoffer.Trader.Goods));//нулим товар
			pchar.GenQuest.Contraoffer = "begin";
			pchar.GenQuest.Contraoffer.Trader = "true";
			pchar.GenQuest.Contraoffer.Trader.City = npchar.city;
			pchar.GenQuest.Contraoffer.Trader.Nation = npchar.nation;
			iCGood = pchar.GenQuest.Contraoffer.Trader.Goods;
			ReOpenQuestHeader("Contraoffer");
			AddQuestRecord("Contraoffer", "1");
			AddQuestUserData("Contraoffer", "sGoods", GetGoodsNameAlt(iCGood));
			AddQuestUserData("Contraoffer", "sGoodQty", FindRussianQtyString(sti(pchar.GenQuest.Contraoffer.Trader.Qty)));
			AddQuestUserData("Contraoffer", "sMoney", FindRussianMoneyString(sti(pchar.GenQuest.Contraoffer.Trader.Summ)));
			AddQuestUserData("Contraoffer", "sCity", XI_ConvertString("Colony"+pchar.GenQuest.Contraoffer.Trader.City+"Gen"));
			AddQuestUserData("Contraoffer", "sDays", FindRussianDaysString(sti(pchar.GenQuest.Contraoffer.Trader.Days)));
			SetFunctionTimerCondition("Contraoffer_Over", 0, 0, sti(pchar.GenQuest.Contraoffer.Trader.Days), false);
		break;
		
		case "Contraoffer_check":
			iCGood = sti(pchar.GenQuest.Contraoffer.Trader.Goods);
			amount = sti(pchar.GenQuest.Contraoffer.Trader.Qty) - GetSquadronGoods(pchar, sti(pchar.GenQuest.Contraoffer.Trader.Goods));
			if (amount > 0)
			{
				dialog.text = "Гхм... Шутить изволите? У вас же нет нужного мне количества товара!";
				link.l1 = "Пардон, ошибочка вышла...";
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = "Давайте посмотрим. Вы должны были привезти груз " + GetGoodsNameAlt(iCGood)+ " в количестве " + FindRussianQtyString(pchar.GenQuest.Contraoffer.Trader.Qty) + ". Так?";
				link.l1 = "Именно так, " + GetAddress_FormToNPC(NPChar) + ".";
				link.l1.go = "Contraoffer_pay";
			}
		break;
		
		case "Contraoffer_pay":
			dialog.text = "Спасибо за проделанную работу. Получите вашу оплату - " + FindRussianMoneyString(sti(pchar.GenQuest.Contraoffer.Trader.Summ)) + ".";
		link.l1 = "Спасибо! Приятно с вами иметь дело.";
		link.l1.go = "Contraoffer_complete";
		break;
		
		case "Contraoffer_complete":
			pchar.quest.Contraoffer_Over.over = "yes";
			RemoveCharacterGoods(pchar, sti(pchar.GenQuest.Contraoffer.Trader.Goods), sti(pchar.GenQuest.Contraoffer.Trader.Qty));
			AddMoneyToCharacter(pchar, sti(pchar.GenQuest.Contraoffer.Trader.Summ));
			SaveCurrentNpcQuestDateParam(npchar, "Contraoffer");
			npchar.quest.Contraoffer.chance = rand(2);//личный шанс торговца для 'пасхалки'
			AddCharacterExpToSkill(pchar, "Sailing", 100);//навигация
			AddCharacterExpToSkill(pchar, "Commerce", 100);//торговля
			AddCharacterExpToSkill(pchar, "Leadership", 50);//авторитет
			AddCharacterExpToSkill(pchar, "Fortune", 100);//везение
			ChangeCharacterComplexReputation(pchar,"nobility", -1);
			if (pchar.GenQuest.Contraoffer.Trader.Chance == 3)
			{
				dialog.text = "Ой... Вот так дела! Капитан, у нас с вами проблемы...";
				link.l1 = "Что еще такое?";
				link.l1.go = "exit";
				AddDialogExitQuestFunction("Contraoffer_Patrol");
				pchar.GenQuest.Contraoffer.Trader.busy = "true";
				pchar.quest.Contraoffer_busy.win_condition.l1 = "ExitFromLocation";
				pchar.quest.Contraoffer_busy.win_condition.l1.location = pchar.location;
				pchar.quest.Contraoffer_busy.function = "Trader_free";
			}
			else
			{
				DialogExit();
				AddQuestRecord("Contraoffer", "3");
				CloseQuestHeader("Contraoffer");
				DeleteAttribute(pchar, "GenQuest.Contraoffer.Trader");
			}
		break;
		
		case "Contraoffer_slaves"://единичный вариант за всю игру, ака 'пасхалка'
			pchar.GenQuest.Contraoffer.Slaves.Name = GetFullName(npchar);
			pchar.GenQuest.Contraoffer.Slaves.Price = 300;//цена на рабов, пока фиксированная, можно подставить формулу
			pchar.GenQuest.Contraoffer.Slaves.Qty = 300+rand(50);//количество
			pchar.GenQuest.Contraoffer.Slaves.Days = 14+rand(6);//срок
			pchar.GenQuest.Contraoffer.Slaves.Money = sti(pchar.GenQuest.Contraoffer.Slaves.Qty)*sti(pchar.GenQuest.Contraoffer.Slaves.Price);
			dialog.text = "Мне очень срочно нужна партия рабов в количестве "+sti(pchar.GenQuest.Contraoffer.Slaves.Qty)+" штук. Заплатить готов по "+sti(pchar.GenQuest.Contraoffer.Slaves.Price)+" монет за штуку, что в сумме составит "+sti(pchar.GenQuest.Contraoffer.Slaves.Money)+" песо, срок - "+FindRussianDaysString(sti(pchar.GenQuest.Contraoffer.Slaves.Days))+".";
			link.l1 = "Пожалуй, я соглашусь. Дело хоть и хлопотное, но прибыльное.";
			link.l1.go = "Contraoffer_slaves_1";
			link.l2 = "Меня это не интересует.";
			link.l2.go = "exit";
			pchar.GenQuest.Contraoffer.Slaves = "begin";
		break;
		
		case "Contraoffer_slaves_1":
			dialog.text = "Вы очень точно это подметили - прибыльное. Ну что же, тогда жду вас с товаром.";
			link.l1 = "Я не заставлю себя долго ждать. До встречи!";
			link.l1.go = "exit";
			pchar.GenQuest.Contraoffer.Slaves.Yes = "begin";
			pchar.GenQuest.Contraoffer.Slaves.City = npchar.city;
			ReOpenQuestHeader("Contraoffer");
			AddQuestRecord("Contraoffer", "4");
			AddQuestUserData("Contraoffer", "sDays", FindRussianDaysString(sti(pchar.GenQuest.Contraoffer.Slaves.Days)));
			AddQuestUserData("Contraoffer", "sGoodQty", FindRussianQtyString(sti(pchar.GenQuest.Contraoffer.Slaves.Qty)));
			AddQuestUserData("Contraoffer", "sMoney", FindRussianMoneyString(sti(pchar.GenQuest.Contraoffer.Slaves.Money)));
			AddQuestUserData("Contraoffer", "sCity", XI_ConvertString("Colony"+pchar.GenQuest.Contraoffer.Slaves.City+"Gen"));
			SetFunctionTimerCondition("Contraoffer_Over", 0, 0, sti(pchar.GenQuest.Contraoffer.Slaves.Days), false);
		break;
		
		case "Contraoffer_slaves_check":
			amount = sti(pchar.GenQuest.Contraoffer.Slaves.Qty) - GetSquadronGoods(pchar, GOOD_SLAVES);
			if (amount > 0)
			{
				dialog.text = "Гхм... Шутить изволите? У вас же нет нужного мне количества рабов!";
				link.l1 = "Пардон, ошибочка вышла...";
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = "Давайте посмотрим. Вы должны были привезти рабов в количестве " + FindRussianQtyString(pchar.GenQuest.Contraoffer.Slaves.Qty) + ". Так?";
				link.l1 = "Именно так, " + GetAddress_FormToNPC(NPChar) + ".";
				link.l1.go = "Contraoffer_slaves_pay";
			}
		break;
		
		case "Contraoffer_slaves_pay":
			dialog.text = "Спасибо за проделанную работу. Получите вашу оплату - " + FindRussianMoneyString(sti(pchar.GenQuest.Contraoffer.Slaves.Money)) + ". Кроме того, возьмите эту вещь - она вам пригодится.";
			link.l1 = "Спасибо! Приятно с вами иметь дело.";
			link.l1.go = "Contraoffer_slaves_complete";
		break;
		
		case "Contraoffer_slaves_complete":
			DialogExit();
			pchar.quest.Contraoffer_Over.over = "yes";
			RemoveCharacterGoods(pchar, GOOD_SLAVES, sti(pchar.GenQuest.Contraoffer.Slaves.Qty));
			AddMoneyToCharacter(pchar, sti(pchar.GenQuest.Contraoffer.Slaves.Money));
			AddQuestRecord("Contraoffer", "5");
			CloseQuestHeader("Contraoffer");
			SaveCurrentNpcQuestDateParam(npchar, "Contraoffer");
			AddCharacterExpToSkill(pchar, "Sailing", 150);//навигация
			AddCharacterExpToSkill(pchar, "Commerce", 200);//торговля
			AddCharacterExpToSkill(pchar, "Leadership", 50);//авторитет
			AddCharacterExpToSkill(pchar, "Fortune", 150);//везение
			TakeNItems(pchar, "cirass3", 1);
			ChangeCharacterComplexReputation(pchar,"nobility", -3);
			DeleteAttribute(pchar, "GenQuest.Contraoffer.Slaves.Yes");
		break;
		// <-- генератор Сомнительное предложение
		
		//Jason --> генератор Неудачливый вор
		case "Device_Trader":
			dialog.text = "Гм, "+pchar.GenQuest.Device.Shipyarder.Type+"? Впервые слышу... Хоть что это за вещь такая - сколько живу на свете, ничего подобного в глаза не видел.";
			link.l1 = "Ну, это судостроительный инструмент, "+pchar.GenQuest.Device.Shipyarder.Describe+". Никто ничего подобного тебе не предлагал?";
			link.l1.go = "Device_Trader_1";
			npchar.quest.Device = "true";
		break;
		
		case "Device_Trader_1":
			if (sti(pchar.GenQuest.Device.Shipyarder.Chance1) == 0)
			{
				dialog.text = "Хм... Да, приносил мне такую вещь один странный тип. Только он ее никак не назвал, а просто пытался мне продать. Да только зачем она мне, если я даже не знаю, для чего она нужна? Как я ее потом продать сумею? В общем, отказал я ему, и он ушел.";
				link.l1 = "А как выглядел этот человек и куда пошел? Мне очень нужен этот инструмент.";
				link.l1.go = "Device_Common";
			}
			else
			{
				dialog.text = "Нет, никто не приносил. Так что помочь ничем не могу. Поспрашивай еще у кого.";
				link.l1 = "Ясно. Пойду спрашивать!";
				link.l1.go = "exit";
			}
		break;
		// <-- генератор Неудачливый вор

		//Jason --> генератор Место под солнцем
		case "Sunplace_begin":
			dialog.text = "Конкуренция... В нашем деле без нее никак не обойтись. Алчные негодяи так и норовят ворваться в твой уютный бизнес, и, действуя всяческими гнусными методами, переманить клиентуру к себе\nНо это лирика. А по сути: я хотел бы попросить вас помочь мне избавиться от одного из таких моих конкурентов. Нет, убивать его вовсе не обязательно. Достаточно просто захватить или потопить его корабль с грузом.";
			link.l1 = "Хм, ну, если вы хорошо заплатите, это можно устроить.";
			link.l1.go = "Sunplace_1";
			link.l2 = "Нет уж, я не намерен ввязываться в ваши торгашеские разборки. Топите своего недруга без моего участия.";
			link.l2.go = "Sunplace_exit";
		break;
		
		case "Sunplace_exit"://если отказал - этот непись больше никогда не даст
			npchar.quest.Sunplace = "true";
			DialogExit();
		break;
		
		case "Sunplace_1":
			GetSunplaceShore();//бухта и остров
			pchar.GenQuest.Sunplace.Trader.Enemyname = GenerateRandomName_Generator(sti(npchar.nation), "man");//имя конкурента
			pchar.GenQuest.Sunplace.Trader.Nation = npchar.nation;//нация общая для торговца и конкурента
			pchar.GenQuest.Sunplace.Trader.City = npchar.City;//город квестодателя
			pchar.GenQuest.Sunplace.Trader.CityT = findSunplaceCity(NPChar);//город конкурента
			pchar.GenQuest.Sunplace.Trader.Shiptype = Sunplace_Shiptype();//тип корабля
			pchar.GenQuest.Sunplace.Trader.ShipName = GenerateRandomNameToShip(sti(NPChar.nation));//имя корабля
			pchar.GenQuest.Sunplace.Trader.DaysQty = 5 + drand(5);//дни
			pchar.GenQuest.Sunplace.Trader.Money = sti(pchar.GenQuest.Sunplace.Trader.Shiptype)*3000;//оплата
			pchar.GenQuest.Sunplace.Trader.Goods = GOOD_COFFEE + drand(sti(GOOD_PAPRIKA - GOOD_COFFEE));//товар
			dialog.text = "Очень хорошо. Итак, вашего клиента зовут "+pchar.GenQuest.Sunplace.Trader.Enemyname+". Недавно он снарядил "+GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.Sunplace.Trader.ShipType), "Name") + "Acc"))+" '"+pchar.GenQuest.Sunplace.Trader.ShipName+"' с грузом " + GetGoodsNameAlt(sti(pchar.GenQuest.Sunplace.Trader.Goods))+ " в плавание. Он вложил в этот товар значительную сумму денег, так что потеря груза весьма серьезно ударит по его кошельку.";
			link.l1 = "А вы бы не могли поточнее указать, где мне искать вашего 'друга'?";
			link.l1.go = "Sunplace_2";
		break;
		
		case "Sunplace_2":
			dialog.text = "'Друг' сейчас у себя дома в "+XI_ConvertString("Colony"+pchar.GenQuest.Sunplace.Trader.CityT+"Abl")+". Он вам не нужен - вам нужен его корабль, который, как мне удалось узнать, примерно через "+FindRussianDaysString(sti(pchar.GenQuest.Sunplace.Trader.DaysQty))+" будет проходить у " + XI_ConvertString(pchar.GenQuest.Sunplace.Trader.Shore+"Gen") + ". Вы можете потопить его, можете взять на абордаж - не имеет значения. Главное - чтобы корабль и груз перестали быть собственностью "+pchar.GenQuest.Sunplace.Trader.Enemyname +". А уже кому они станут принадлежать - вам, или морю - мне безразлично. За работу я заплачу вам " + FindRussianMoneyString(sti(pchar.GenQuest.Sunplace.Trader.Money))".";
			link.l1 = "Задачу понял. Отправляюсь в путь!";
			link.l1.go = "Sunplace_3";
		break;
		
		case "Sunplace_3":
			DialogExit();
			pchar.GenQuest.Sunplace.Trader = "true";
			if (sti(pchar.GenQuest.Sunplace.Chance) == 1 && sti(pchar.rank) > 9) pchar.GenQuest.Sunplace.Bonus = "true";
			ReOpenQuestHeader("Sunplace");
			AddQuestRecord("Sunplace", "1");
			AddQuestUserData("Sunplace", "sGoods", GetGoodsNameAlt(sti(pchar.GenQuest.Sunplace.Trader.Goods)));
			AddQuestUserData("Sunplace", "sDay", FindRussianDaysString(sti(pchar.GenQuest.Sunplace.Trader.DaysQty)));
			AddQuestUserData("Sunplace", "sMoney", FindRussianMoneyString(sti(pchar.GenQuest.Sunplace.Trader.Money)));
			AddQuestUserData("Sunplace", "sCity", XI_ConvertString("Colony"+pchar.GenQuest.Sunplace.Trader.City+"Gen"));
			AddQuestUserData("Sunplace", "sType", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.Sunplace.Trader.ShipType), "Name") + "Acc")));
			AddQuestUserData("Sunplace", "sSName", pchar.GenQuest.Sunplace.Trader.ShipName);
			AddQuestUserData("Sunplace", "sName", GetFullName(npchar));
			AddQuestUserData("Sunplace", "sShore", XI_ConvertString(pchar.GenQuest.Sunplace.Trader.Shore+"Gen"));
			SetFunctionTimerCondition("Sunplace_Over", 0, 0, sti(pchar.GenQuest.Sunplace.Trader.DaysQty), false);
			pchar.quest.Sunplace_Trader.win_condition.l1 = "location";
			pchar.quest.Sunplace_Trader.win_condition.l1.location = pchar.GenQuest.Sunplace.Trader.Island;
			pchar.quest.Sunplace_Trader.win_condition.l2 = "Timer";
			pchar.quest.Sunplace_Trader.win_condition.l2.date.hour  = sti(GetTime());
			pchar.quest.Sunplace_Trader.win_condition.l2.date.day   = GetAddingDataDay(0, 0, makeint(sti(pchar.GenQuest.Sunplace.Trader.DaysQty)-2));
			pchar.quest.Sunplace_Trader.win_condition.l2.date.month = GetAddingDataMonth(0, 0, makeint(sti(pchar.GenQuest.Sunplace.Trader.DaysQty)-2));
			pchar.quest.Sunplace_Trader.win_condition.l2.date.year  = GetAddingDataYear(0, 0, makeint(sti(pchar.GenQuest.Sunplace.Trader.DaysQty)-2));
			pchar.quest.Sunplace_Trader.function = "Sunplace_CreateTraderShip";
		break;
		
		case "Sunplace_complete":
			dialog.text = "Замечательно! Я знал, что на вас можно положиться. Пожалуй, я не буду спрашивать, где сейчас груз и корабль. В конце концов, это не мое дело. Ну, а моему другу потребуется немало времени, чтобы оправиться от такого удара, хе-хе. Вот, возьмите ваши деньги и еще раз спасибо за отлично выполненную работу.";
			link.l1 = "Да не за что... До свидания, " + npchar.name + "!";
			link.l1.go = "Sunplace_complete_1";
		break;
		
		case "Sunplace_complete_1":
			AddMoneyToCharacter(pchar, sti(pchar.GenQuest.Sunplace.Trader.Money));
			AddQuestRecord("Sunplace", "12");
			CloseQuestHeader("Sunplace");
			pchar.GenQuest.Sunplace.Chance = rand(2);
			AddComplexSeaExpToScill(50, 50, 50, 50, 50, 0, 0);
			AddComplexSelfExpToScill(20, 20, 20, 20);
			AddCharacterExpToSkill(pchar, "Fortune", 100);//везение
			DeleteAttribute(pchar, "GenQuest.Sunplace.Trader");
			DialogExit();
		break;
		
		case "Sunplace_complete_murder":
			dialog.text = "Бедный "+pchar.GenQuest.Sunplace.Trader.Enemyname+", какая ужасная судьба! И я косвенно повинен в его смерти... Вы ничего не понимаете, капитан! Разве я просил его убивать? Я рассчитывал, что после того, как он потеряет деньги, вложенные в товар, он будет вынужден снова... впрочем, неважно. Вы...";
			link.l1 = "Послушайте, перестаньте, наконец, причитать. Вы просили избавить вас от конкурента - я сделал это. Я сделал даже лучше, чем вы просили изначально - потеряв груз, можно вновь разбогатеть и вредить, а будучи мертвецом уже ничего нельзя сделать.";
			link.l1.go = "Sunplace_complete_murder_1";
		break;
		
		case "Sunplace_complete_murder_1":
			dialog.text = "Всё! Довольно! Не желаю больше слушать ваших кощунственных речей! Получите ваши кровавые деньги и уходите из моего магазина!";
			link.l1 = "Эй, " + npchar.name + ", потише! А не то я быстро ваш пыл остужу - шпага всегда при мне... Ладно, не бойтесь, я шучу. Мне жаль, что так получилось, но вы сами ввели меня в заблуждение. Прощайте.";
			link.l1.go = "Sunplace_complete_murder_2";
		break;
		
		case "Sunplace_complete_murder_2":
			AddMoneyToCharacter(pchar, sti(pchar.GenQuest.Sunplace.Trader.Money));
			AddQuestRecord("Sunplace", "13");
			AddQuestUserData("Sunplace", "sName", GetFullName(npchar));
			CloseQuestHeader("Sunplace");
			npchar.quest.Sunplace = "true";//этот непись повторно квест больше не даст
			AddComplexSeaExpToScill(50, 50, 50, 50, 50, 0, 0);
			AddComplexSelfExpToScill(30, 30, 30, 30);
			AddCharacterExpToSkill(pchar, "Fortune", 50);//везение
			DeleteAttribute(pchar, "GenQuest.Sunplace.Trader");
			DialogExit();
		break;
		
		//Jason --> поиск дезертира
		case "FindFugitiveSt":
			if (NPChar.city == pchar.GenQuest.FindFugitive.City && sti(pchar.GenQuest.FindFugitive.Chance) == 1)
			{
				dialog.text = NPCStringReactionRepeat(""+pchar.GenQuest.FindFugitive.Name+"? Да, я его знаю, он покупал у меня провизию на свой баркас. Днем он рыбачит где-то в укромных бухтах, а вот зато каждый вечер его можно найти в таверне.", "Ты уже спрашивал меня об этом человеке, и я тебе все рассказал!", "Ты что, издеваешься, или на самом деле тупой? Третий раз спрашиваешь одно и то же!", "Ох, и как только такой дурень капитаном стал...", "block", 1, npchar, Dialog.CurrentNode);
				link.l1 = HeroStringReactionRepeat("Спасибо, ты мне очень помог!", "Да, да, хорошо.", "Тише, не кипятись. Я просто забыл.", "Ну ты же видишь - стал как-то...", npchar, Dialog.CurrentNode); 
				link.l1.go = DialogGoNodeRepeat("FindFugitiveSt_1", "exit", "", "", npchar, Dialog.CurrentNode);
			}
			else
			{
				dialog.text = NPCStringReactionRepeat("Не знаю, что там говорят в таверне Порт-Рояла, а в своем магазине я такого человека не встречал. И вообще нигде не видел. Поспрашивайте в поселке, может, кто что скажет...", "Ты уже спрашивал меня об этом человеке, и я тебе сказал: не знаю!", "Ты что, издеваешься, или на самом деле тупой? Третий раз спрашиваешь одно и то же!", "Ох, и как только такой дурень капитаном стал...", "block", 1, npchar, Dialog.CurrentNode);
				link.l1 = HeroStringReactionRepeat("Понятно. Ну, и на том спасибо.", "Да, да, хорошо.", "Тише, не кипятись. Я просто забыл.", "Ну ты же видишь - стал как-то...", npchar, Dialog.CurrentNode); 
				link.l1.go = DialogGoNodeRepeat("exit", "", "", "", npchar, Dialog.CurrentNode);	
			}
		break;
		
		case "FindFugitiveSt_1":
			DialogExit();
			AddQuestRecord("MayorsQuestsList", "12-2");
			sld = characterFromId("Fugitive");
			LAi_SetSitType(sld);
			sld.dialog.currentnode = "Fugitive_tavern";
			LAi_SetLoginTime(sld, 20.0, 23.99);
			FreeSitLocator(pchar.GenQuest.FindFugitive.City + "_tavern", "sit_front1");
			ChangeCharacterAddressGroup(sld, pchar.GenQuest.FindFugitive.City+"_tavern", "sit", "sit_front1");
		break;
		//<-- поиск дезертира
		
		// --> Карибские нравы - временное завершение
		case "trial":
			dialog.text = "Господи, да что же вы так расшумелись, молодой человек! Будьте сдержаннее, в конце концов, и выбирайте выражения, когда говорите об уважаемых людях! Жерар Лекруа отбыл с Гваделупы в экспедицию на материк, но оставил ваше вознаграждение. Успокоились?";
			link.l1 = "Гхм... прошу меня извинить, месье. Я погорячился...";
			link.l1.go = "trial_1";
		break;
		
		case "trial_1":
			dialog.text = "Прекрасно. Постарайтесь впредь сначала спрашивать, а уже потом кричать во весь голос. Вот, возьмите. Здесь 400 золотых дублонов. Надеюсь, вы удовлетворены размером гонорара?";
			link.l1 = "Вполне. Еще раз прошу извинить меня. А теперь позвольте откланяться.";
			link.l1.go = "trial_2";
		break;
		
		case "trial_2":
			TakeNItems(pchar, "gold_dublon", 400);
			Log_Info("Вы получили 400 дублонов");
			PlaySound("interface\important_item.wav");
			dialog.text = "Всего доброго, месье.";
			link.l1 = "...";
			link.l1.go = "trial_3";
		break;
		
		case "trial_3":
			DialogExit();
            NextDiag.CurrentNode = NextDiag.TempNode;
			DeleteAttribute(pchar, "questTemp.Trial");
			DeleteAttribute(npchar, "quest.trial_usurer");
			CloseQuestHeader("Trial");
		break;
		
		/*case "trial":
			dialog.text = "Господи, да что же вы так расшумелись, молодой человек! Будьте сдержаннее, в конце концов, и выбирайте выражения, когда говорите об уважаемых людях! Жерар Лекруа отбыл с Гваделупы в экспедицию на материк, но для вас он оставил сообщение\nВсё, вы успокоились, сударь? Готовы меня выслушать?";
			link.l1 = "Гхм... прошу меня извинить, месье. Я погорячился. Слушаю вас внимательно.";
			link.l1.go = "trial_1";
		break;
		
		case "trial_1":
			dialog.text = "Прекрасно. Постарайтесь впредь сначала спрашивать, а уже потом кричать во весь голос. Ладно... Вам известен человек по имени Симон Моруа?";
			link.l1 = "Ха! Кто же не знает Симона Моруа! Конечно, этот человек мне знаком.";
			link.l1.go = "trial_2";
			link.l2 = "Впервые слышу это имя. Кто он?";
			link.l2.go = "trial_3";
		break;
		
		case "trial_2":
			dialog.text = "Превосходно. Отправляйтесь к нему. Именно он финансировал операцию месье Шоке, так что своё вознаграждение получите у него. И стоило так кипятиться?";
			link.l1 = "Еще раз прошу прощения... Спасибо за помощь, месье. Отправляюсь к господину Моруа немедленно!";
			link.l1.go = "trial_exit";
		break;
		
		case "trial_3":
			dialog.text = "Это владелец банкирского дома Моруа. Возглавляет отделение в Капстервиле. Так что вам предстоит отправиться на Сент-Кристофер и посетить банк Капстервиля. Именно господин Моруа финансировал операцию месье Шоке, так что своё вознаграждение получите у него. И стоило так кипятиться?";
			link.l1 = "Еще раз прошу прощения... Спасибо за помощь, месье. Отправляюсь к господину Моруа немедленно!";
			link.l1.go = "trial_exit";
		break;
		
		case "trial_exit":
			DialogExit();
            NextDiag.CurrentNode = NextDiag.TempNode;
			DeleteAttribute(npchar, "quest.trial_usurer");
			pchar.questTemp.Trial = "usurer";
			AddQuestRecord("Trial", "22");
		break;*/
		
		case "no_quests":
			dialog.text = "В данный момент я не нуждаюсь в ваших услугах.";
			link.l1 = "Очень жаль. Тогда давайте поговорим о другом.";
			link.l1.go = "node_1";
		break;
		
        case "fight":
			DialogExit();
            NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_group_Attack(NPChar, Pchar);
		break;
		
		case "Exit":			
			Nextdiag.CurrentNode = Nextdiag.TempNode;
			DialogExit();			
		break;
	}
	LanguageCloseFile(iSeaGoods);
}

int findStoreMan(ref NPChar, int iTradeNation)
{
    ref ch;
	int n;
    int storeArray[30];
    int howStore = 0;

	for(n=0; n<MAX_CHARACTERS; n++)
	{
		makeref(ch,Characters[n]);
        if (CheckAttribute(ch, "Dialog.Filename") && ch.Dialog.Filename == "Common_Store.c") // магазин
		{
            if (sti(ch.nation) !=  iTradeNation) continue;
            if (NPChar.id == ch.id) continue;
            if (NPChar.id == "Panama_trader" || ch.id == "Panama_trader") continue; //нельзя доплыть
			if (NPChar.id == "SanAndres_trader" || ch.id == "SanAndres_trader") continue; // fix 2016-03-07
            if (ch.location == "none") continue; // фикс для новых, невидимых до поры островов
            if (GetIslandByCityName(ch.city) == GetIslandByCityName(NPChar.city)) continue; // хрен вам, а не читы!
            storeArray[howStore] = n;
            howStore++;
		}
    }
    if (howStore == 0)
    {
        return -1;
    }
    else
    {
        return storeArray[rand(howStore-1)];
    }
}

int Sunplace_Shiptype() // new
{
	int i;
	
	if (sti(pchar.rank) >= 1 && sti(pchar.rank) < 6) i = SHIP_SCHOONER;
	if (sti(pchar.rank) >= 6 && sti(pchar.rank) < 11) i = SHIP_FLEUT;
	if (sti(pchar.rank) >= 11 && sti(pchar.rank) < 18) i = SHIP_PINNACE;
	if (sti(pchar.rank) >= 18) i = SHIP_GALEON_L;
	
	return i;
}

string findSunplaceCity(ref NPChar) // new
{
	int n, nation;
    int storeArray[MAX_COLONIES];
    int howStore = 0;

	for(n=0; n<MAX_COLONIES; n++)
	{
		nation = GetNationRelation(sti(pchar.nation), sti(colonies[n].nation));
		if (nation != RELATION_ENEMY && colonies[n].id != "Panama" && colonies[n].id != "Minentown" && colonies[n].id != "SanAndres" && colonies[n].nation != "none" && GetIslandByCityName(npchar.city) != colonies[n].islandLable) //на свой остров
		{
			storeArray[howStore] = n;
			howStore++;
		}
	}
	if (howStore == 0) return "none";
	nation = storeArray[dRand(howStore-1)];
	return colonies[nation].id;
}