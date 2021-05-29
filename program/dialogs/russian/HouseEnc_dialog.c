
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag, arRld, arDis;
	int i, Qty;
	ref rColony;
	
	int iTest;
	
	bool  ok; // лесник . спецпеременная.

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	iTest = FindColony(NPChar.City);
	if (iTest != -1)
	{
		rColony = GetColonyByIndex(iTest);
	}
	
	switch(Dialog.CurrentNode)
	{
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "exit_setOwner":
			LAi_SetOwnerTypeNoGroup(npchar);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "fight":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LAi_SetOwnerTypeNoGroup(npchar);
			LAi_group_Attack(NPChar, Pchar);
			if (rand(3) != 1) SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;

		case "exit_GoOut":
			makearef(arRld, Locations[reload_cur_location_index].reload);
    		Qty = GetAttributesNum(arRld);
			for (i=0; i<Qty; i++)
    		{
    			arDis = GetAttributeN(arRld, i);
    			if (arDis.go == npchar.location)
    			{
					arDis.disable = true; //закрываем вход в дом
					break;
    			}
    		}
			DoQuestFunctionDelay("HouseEnc_TimerGoUot", 10.0);
			pchar.questTemp.HouseEncTimer = pchar.location;
			pchar.questTemp.HouseEncTimer.Id = npchar.id;
			LAi_SetOwnerTypeNoGroup(npchar);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "exit_close":
			makearef(arRld, Locations[reload_cur_location_index].reload);
    		Qty = GetAttributesNum(arRld);
			for (i=0; i<Qty; i++)
    		{
    			arDis = GetAttributeN(arRld, i);
    			if (arDis.go == npchar.location)
    			{
					arDis.disable = true; //закрываем вход в дом
					break;
    			}
    		}
			LAi_SetOwnerTypeNoGroup(npchar);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		//--------------------------------- мужик ---------------------------------
		case "HouseMan":
			NextDiag.TempNode = "HouseMan";
			if (LAi_grp_playeralarm > 0)
			{
       			dialog.text = PCharRepPhrase(LinkRandPhrase("В городе поднята тревога. Похоже, и мне пора браться за оружие...", "Уж не за тобой ли носится вся городская стража?.. Ко мне, солдаты!!!", "У меня приюта ты не найдёшь. Зато найдёшь несколько дюймов холодной стали под ребро!"), 
					LinkRandPhrase("Что тебе нужно, "+ GetSexPhrase("негодяй","негодяйка") +"?! Городская стража уже взяла твой след, далеко тебе не уйти, "+ GetSexPhrase("грязный пират","мерзавка") +"!", ""+ GetSexPhrase("Грязный","Грязная") +" убийца! Стража!!!", "Я не боюсь тебя, "+ GetSexPhrase("мерзавец","мерзавка") +"! Скоро тебя повесят в нашем форте, далеко тебе не уйти..."));
				link.l1 = PCharRepPhrase(RandPhraseSimple("Похоже, тебе жить надоело...", "Хех, и не живётся же спокойно мирным гражданам " + XI_ConvertString("Colony" + npchar.city + "Gen") + "!"), 
					RandPhraseSimple("Отправляйся в ад!", "Хех, жить тебе осталось несколько секунд..."));
				link.l1.go = PCharRepPhrase("exit_setOwner", "fight");
				break;
			}
			if (isBadReputation(pchar, 40))
			{
				if (CheckAttribute(pchar, "questTemp.HouseEncTimer"))
				{
					dialog.text = "Я тебя предупредил. А дальше "+ GetSexPhrase("сам","сама") +" смотри, нарываться или нет...";
					link.l1 = "Хех!";
					link.l1.go = "exit";
				}
				else
				{
					dialog.text = "Что тебе надо в моём доме, негодяй"+ GetSexPhrase("","ка") +"?! Даю тебе десять секунд, чтобы ты убрался отсюда!";
					link.l1 = LinkRandPhrase("Хех, и здесь меня знают!", "Слава моя идёт впереди меня...", "Хм, понятно.");
					link.l1.go = "exit_GoOut";
				}
			}
			else
			{
				if (IsDay())
				{
					dialog.text = NPCStringReactionRepeat("Рад приветствовать вас в моём доме. Вы по делу ко мне?", 
						"Чем я могу вам помочь?", 
						"Хм, что я могу сделать для вас?",
						"Простите, если я вам не нужен, я попрошу вас меня не беспокоить...", "block", 1, npchar, Dialog.CurrentNode);
					link.l1 = HeroStringReactionRepeat("Нет, просто осматриваю город, знакомлюсь с жителями...", 
						"Да так, ничем особенным...",
						"Ничего...", 
						"Хорошо, как скажешь.", npchar, Dialog.CurrentNode);
					link.l1.go = DialogGoNodeRepeat("HouseMan_1", "exit_setOwner", "exit_setOwner", "exit_setOwner", npchar, Dialog.CurrentNode);
				}
				else
				{
					dialog.text = NPCStringReactionRepeat("Простите, вы не вовремя появились у меня дома - ночь на дворе. Я прошу вас покинуть мой дом!", 
						"Я уже говорил, что время позднее. Прошу вас уйти.", 
						"Не хочу показаться грубым, но я настаиваю, чтобы вы немедленно покинули мой дом!",
						"Черт возьми, что это такое?! Стража, воры!!!", "block", 1, npchar, Dialog.CurrentNode);
					link.l1 = HeroStringReactionRepeat("Хорошо, я понимаю...", 
						"Да, сейчас...",
						"Ладно, не кипятись.", 
						"Заткнись, какие воры?!", npchar, Dialog.CurrentNode);
					link.l1.go = DialogGoNodeRepeat("exit_close", "exit_setOwner", "exit_setOwner", "fight", npchar, Dialog.CurrentNode);
				}
			}
		break;

		case "HouseMan_1":
			dialog.text = "О-о, разрешите представиться - " + GetFullName(npchar) + ". Мы рады вас видеть, законы гостеприимства для нашего города - не пустой звук.";
			link.l1 = GetFullName(pchar) + ", с вашего позволения...";
			link.l1.go = "exit_setOwner";
		break;
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("Да ты "+ GetSexPhrase("вор, милейший! Стража, держи его","воровка! Стража, держи её") +"!!!", "Вот это да! Чуть я загляделся, а ты сразу в сундук с головой! Держи "+ GetSexPhrase("вора","воровку") +"!!!", "Стража! Грабят!!! Держи "+ GetSexPhrase("вора","воровку") +"!!!");
			link.l1 = "А-ать, дьявол!!!";
			link.l1.go = "fight";
		break;
		// --------------------------------- баба ---------------------------------
		case "HouseWoman":
			NextDiag.TempNode = "HouseWoman";
			if (LAi_grp_playeralarm > 0)
			{
       			dialog.text = PCharRepPhrase(LinkRandPhrase("Предупреждаю, что скоро домой явится мой муж! Шли бы вы из моего дома...", "Не думаю, что вам удастся сбежать. И знайте, что скоро домой должен прийти мой муж!", "Мой муж скоро будет дома, вам немедленно нужно уйти отсюда!"), 
					LinkRandPhrase("Эх, жаль, мужа нет дома... Убирайся!!!", "Грязный убийца, вон из моего дома! Стража!!", ""+ GetSexPhrase("Каков мерзавец","Какова мерзавка") +"... Скоро придёт мой муж и посмотрит, какого цвета у тебя кровь!"));
				link.l1 = PCharRepPhrase(RandPhraseSimple("Муж? Что же, с удовольствием познакомлюсь...", "Хех, мужем меня не напугаешь, дорогуша..."), 
					RandPhraseSimple("Заткни свой ротик, а не то кишки выпущу...", "Я останусь здесь столько, сколько захочу. А ты сиди тихо, не то хуже будет..."));
				link.l1.go = "exit_setOwner";
				break;
			}
			if (isBadReputation(pchar, 40))
			{
				if (CheckAttribute(pchar, "questTemp.HouseEncTimer"))
				{
					dialog.text = "Я тебя предупредила. Убирайся, или будет хуже!";
					link.l1 = "Одно слово - дура...";
					link.l1.go = "exit";
				}
				else
				{					
					dialog.text = "Что тебе надо в моём доме, "+ GetSexPhrase("негодяй","негодяйка") +"?! Если ты не уберёшься через десять секунд, то я позову стражу!";
					link.l1 = "Вот дура...";
					link.l1.go = "exit_GoOut";
				}
			}
			else
			{
				if (IsDay())
				{
					dialog.text = NPCStringReactionRepeat("Я рада вас видеть в нашем доме. Меня зовут " + GetFullName(npchar) + ". Чем я могу вам помочь?", 
						"Вы ещё здесь?", 
						"Хм, простите, но вам не кажется, что вы уже засиделись у нас?",
						"Я прошу вас не злоупотреблять нашим гостеприимством.", "block", 1, npchar, Dialog.CurrentNode);
					link.l1 = HeroStringReactionRepeat( GetFullName(pchar) + " к вашим услугам. К вам заш"+ GetSexPhrase("ел","ла") +" без конкретного дела, познакомиться.", 
						"Ещё здесь.",
						"Ну, как сказать...", 
						"Хорошо.", npchar, Dialog.CurrentNode);
					link.l1.go = DialogGoNodeRepeat("HouseWoman_1", "exit_setOwner", "exit_setOwner", "exit_setOwner", npchar, Dialog.CurrentNode);
				}
				else
				{
					dialog.text = NPCStringReactionRepeat("Ах, господи, что же это вы врываетесь в дом в такое время! Прямо испугали меня... Прошу вас уйти, приходите к нам завтра.", 
						"Уйдите же, прошу вас! "+ GetSexPhrase("Я замужняя женщина!","") +"", 
						"Я последний раз добром прошу вас покинуть наш дом!",
						"Да что же это делается?!!", "block", 1, npchar, Dialog.CurrentNode);
					link.l1 = HeroStringReactionRepeat("Не бойтесь, я ничего плохого вам не сделаю.", 
						"Хорошо, не надо волноваться...",
						"Ухожу.", 
						"В чём дело?", npchar, Dialog.CurrentNode);
					link.l1.go = DialogGoNodeRepeat("exit_close", "exit_setOwner", "exit_setOwner", "HouseWoman_2", npchar, Dialog.CurrentNode);
				}
			}
		break;

		case "HouseWoman_1":
			dialog.text = "Хорошо, всегда рады гостям. Только прошу вас не засиживаться"+ GetSexPhrase(" у меня, так как я замужем...",", у меня очень много дел.") +"";
			link.l1 = "О-о, да, конечно...";
			link.l1.go = "exit_setOwner";
		break;
		case "Woman_FackYou":
			dialog.text = "Ах, вот, значит, как?! Я вас пустила в дом как гост"+ GetSexPhrase("я","ью") +", а вы по сундукам шарить вздумали?! Стража-а-а!!!";
			link.l1 = "Заткнись, дура...";
			link.l1.go = "exit_setOwner";
			LAi_group_Attack(NPChar, Pchar);
			if (rand(3) != 1) SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
		break;
		case "HouseWoman_2":
			dialog.text = "Сколько я тебя просила по-хорошему убраться из дома! Ну, хватит... Помогите! Стража!!!";
			link.l1 = "Заткнись дура, с ума сошла?!";
			link.l1.go = "exit_setOwner";
			LAi_group_Attack(NPChar, Pchar);
			if (rand(3) != 1) SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
		break; 
		//--------------------------------- завсклад ---------------------------------		
		case "SkladMan":
			NextDiag.TempNode = "SkladMan1";
			if (LAi_grp_playeralarm > 0)
			{
       			dialog.text = NPCharRepPhrase(pchar, 
					LinkRandPhrase("В городе поднята тревога. Похоже, и мне пора браться за оружие...", "Уж не за тобой ли носится вся городская стража?.. Ко мне, солдаты!!!", "У меня приюта ты не найдёшь. Зато найдёшь несколько дюймов холодной стали под ребро!"), 
					LinkRandPhrase("Что тебе нужно, "+ GetSexPhrase("негодяй","негодяйка") +"?! Городская стража уже взяла твой след, далеко тебе не уйти, "+ GetSexPhrase("грязный пират","мерзавка") +"!", ""+ GetSexPhrase("Грязный","Грязная") +" убийца! Стража!!!", "Я не боюсь тебя, "+ GetSexPhrase("мерзавец","мерзавка") +"! Скоро тебя повесят в нашем форте, далеко тебе не уйти..."));
				link.l1 = NPCharRepPhrase(pchar,
					RandPhraseSimple("Похоже, тебе жить надоело...", "Хех, и не живётся же спокойно мирным гражданам " + XI_ConvertString("Colony" + npchar.city + "Gen") + "!"), 
					RandPhraseSimple("Отправляйся в ад!", "Хех, жить тебе осталось несколько секунд..."));
				link.l1.go = NPCharRepPhrase("exit_setOwner", "fight");
				break;
			}
				dialog.text = NPCStringReactionRepeat("Приветсвую вас! Меня зовут " + GetFullName(npchar) + ". Я здесь заведую всем, так что не вздумай прихватить что-то с собой...", 
				"Веди себя прилично. И помни, что я смотрю за тобой.", 
				"Пока ты не лезешь в сундуки - всё в порядке, можешь находиться здесь. Одному мне скучно...",
				RandPhraseSimple("Эх, тоска тут смертная!", "Эх, чёрт возьми, чем бы заняться?.."), "block", 3, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Хорошо, не переживай.", 
				"Конечно!",
				"Понимаю...", 
				"Да, проблемы у тебя серьёзные...", npchar, Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("exit", "exit", "exit", "exit", npchar, Dialog.CurrentNode);				
		break;
		
		case "SkladMan1":
			NextDiag.TempNode = "SkladMan1";
			if (LAi_grp_playeralarm > 0)
			{
       			dialog.text = NPCharRepPhrase(pchar, 
					LinkRandPhrase("В городе поднята тревога. Похоже, и мне пора браться за оружие...", "Уж не за тобой ли носится вся городская стража?.. Ко мне, солдаты!!!", "У меня приюта ты не найдёшь. Зато найдёшь несколько дюймов холодной стали под ребро!"), 
					LinkRandPhrase("Что тебе нужно, "+ GetSexPhrase("негодяй","негодяйка") +"?! Городская стража уже взяла твой след, далеко тебе не уйти, "+ GetSexPhrase("грязный пират","мерзавка") +"!", ""+ GetSexPhrase("Грязный","Грязная") +" убийца! Стража!!!", "Я не боюсь тебя, "+ GetSexPhrase("мерзавец","мерзавка") +"! Скоро тебя повесят в нашем форте, далеко тебе не уйти..."));
				link.l1 = NPCharRepPhrase(pchar,
					RandPhraseSimple("Похоже, тебе жить надоело...", "Хех, и не живётся же спокойно мирным гражданам " + XI_ConvertString("Colony" + npchar.city + "Gen") + "!"), 
					RandPhraseSimple("Отправляйся в ад!", "Хех, жить тебе осталось несколько секунд..."));
				link.l1.go = NPCharRepPhrase("exit_setOwner", "fight");
				break;
			}
			dialog.text = NPCStringReactionRepeat("Я здесь заведую всем, так что не вздумай прихватить что-то с собой...", 
				"Веди себя прилично. И помни, что я смотрю за тобой.", 
				"Пока ты не лезешь в сундуки - всё в порядке, можешь находиться здесь. Одному мне скучно...",
				RandPhraseSimple("Эх, тоска тут смертная!", "Эх, чёрт возьми, чем бы заняться?.."), "block", 3, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Хорошо, не переживай.", 
				"Конечно!",
				"Понимаю...", 
				"Да, проблемы у тебя серьёзные...", npchar, Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("exit", "exit", "exit", "exit", npchar, Dialog.CurrentNode);				
			//открывание двери верфи по квесту промышленного шпионажа
			if (CheckAttribute(pchar, "questTemp.different.ShipyardsMap") && pchar.questTemp.different.ShipyardsMap == "toTarget" && npchar.city == pchar.questTemp.different.ShipyardsMap.city && locations[reload_cur_location_index].type == "shipyard")
			{
				link.l2 = "Послушай, приятель, хочу поговорить с тобой откровенно.";
				link.l2.go = "ShipyardsMap_1";
				pchar.questTemp.different.ShipyardsMap = "toResult";					
			}
			// ugeen --> склад товаров для ГГ				
			if(CheckAttribute(NPChar,"Storage"))
			{
				if(!CheckAttribute(NPChar, "Storage.Speak"))
				{
					dialog.text = "У меня к вам есть одно заманчивое предложение. Возможно, оно вас заинтересует.";
					link.l7 = "Вот как? Ну что ж, излагайте ваше заманчивое предложение.";
					link.l7.go = "storage_rent";
				}
				else
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
							link.l7 = "Помнится, вы как-то о складе упоминали. Место ещё не занято?";
							link.l7.go = "storage_01";
						}						
					}
				}		
			// <-- ugeen
			}		
		break;
		
		//--------------------------------- Аренда склада ---------------------------------
		case "storage_rent":
			NPChar.Storage.Speak = true;
			dialog.text = "У нас есть площади, пригодные под склад. Не хотите арендовать за умеренную плату? Обзаведётесь собственным складиком...";
			link.l1 = "Складиком, говорите? Заманчиво... А большой он? и сколько попросите за аренду?";
			link.l1.go = "storage_rent1";
		break;
		
		case "storage_rent1":
			NPChar.MoneyForStorage = GetStoragePriceExt(NPChar, pchar); 
			dialog.text = "Он достаточно просторный даже для припортового пакгауза - вместимость 50000 ц. За " + FindRussianMoneyString(sti(NPChar.MoneyForStorage)) + " в месяц я готов обеспечить сохранность ваших запасов. "+
				"Это включает услуги по охране, защиту от подтопления и борьбу с грызунами. Ну как, годится?.. Ну, и конфиденциальность, понятное дело, гарантирую.";
			link.l1 = "Годится. Могу я его осмотреть?";	
			link.l1.go = "storage_rent2";
			link.l2 = "Слишком дорого просите. Там, небось, воды по колено и крысы вовсю шуруют.";
			link.l2.go = "storage_rent3";		
		break;
		
		case "storage_rent2":
			dialog.text = "Конечно-конечно. Только эм-м... оплату за месяц попрошу вперёд.";
			if(sti(pchar.money) >= sti(NPChar.MoneyForStorage))
			{
				link.l1 = "Экий вы... меркантильный. Держите свои деньги - я арендую этот сарай.";
				link.l1.go = "storage_11";
			}
			else
			{	
				link.l1 = "Экий вы... меркантильный. Сейчас деньги принесу.";
				link.l1.go = "exit";
			}	
		break;
		
		case "storage_rent3":
			dialog.text = "Ну, как знаете. Если надумаете - обращайтесь. Только учтите, что такое сокровище долго пустовать не будет. Как бы не опоздали.";
			link.l1 = "Не волнуйтесь. Если понадобится - спрошу.";
			link.l1.go = "exit";
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
			{ // лесник . если забыл с собой корабль то никак.
				ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
		        if (sti(Pchar.Ship.Type) != SHIP_NOTUSED && ok)
				{	
				dialog.text = "Проходите.";
				link.l1 = "Спасибо.";
				link.l1.go = "storage_2";
				}
				else
				{
                dialog.text = RandPhraseSimple("Капитан, а где же ваш корабль? Как вы собираетесь перегружать товары?", "Я не вижу вашего корабля в порту. Как же вы собираетесь производить погрузку?");
                link.l1 = RandPhraseSimple("Ох... совсем забыл.", "А, чёрт... точно!");
			    link.l1.go = "exit";
				break;
                }				
			}
			link.l2 = "Нет, я передумал"+ GetSexPhrase("","а") +".";
			link.l2.go = "exit"; 						
		break;
		
		case "storage_01":
			dialog.text = "Нет, "+ GetSexPhrase("уважаемый","мэм") +", стоит - вас дожидается. Я как знал, что вы не оставите этого предложения.";
			link.l1 = "Это хорошо. Я его арендую.";
			link.l1.go = "storage_1";
			link.l2 = "Да нет, я просто так вспомнил"+ GetSexPhrase("","а") +". Может когда и понадобится...";
			link.l2.go = "exit";
		break;
		
		case "storage_1":
			NPChar.MoneyForStorage = GetStoragePriceExt(NPChar, pchar); 
			dialog.text = "Как вы помните - оплата за месяц вперёд.";
			if(sti(pchar.money) >= sti(NPChar.MoneyForStorage))
			{
				link.l1 = "Помню - держите.";
				link.l1.go = "storage_11";
			}
			else
			{
				link.l1 = "Вот чёрт. Сейчас деньги принесу.";
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
			link.l2 = "Нигде не предложат, говорите? Ладно, оставлю пока за собой. Но цена аренды, долж"+ GetSexPhrase("ен","на") +" сказать... немаленькая, одним словом.";
			link.l2.go = "exit";
		break;
		
		case "storage_4":
			NPChar.MoneyForStorage = GetNpcQuestPastMonthParam(NPChar,"Storage.Date") * sti(NPChar.Storage.MoneyForStorage); 
			if(sti(NPChar.MoneyForStorage) > 0) 			
			{
				dialog.text = "С вас за аренду ещё " + FindRussianMoneyString(sti(NPChar.MoneyForStorage)) + ".";
				if(sti(pchar.money) >= sti(NPChar.MoneyForStorage))			
				{
					link.l1 = "Хорошо.";
					link.l1.go = "storage_5";
				}
			}
			else
			{ // лесник . если нет корабля то и товар не забрать
				ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
		        if (sti(Pchar.Ship.Type) != SHIP_NOTUSED && ok)
				{	
				dialog.text = "Забирайте свой товар и я закрою склад.";
				link.l1 = "Хорошо.";
				link.l1.go = "storage_6";
				}
				else
				{
                dialog.text = RandPhraseSimple("Капитан, а где же ваш корабль? Как вы собираетесь перегружать товары?", "Я не вижу вашего корабля в порту. Как же вы собираетесь производить погрузку?");
                link.l1 = RandPhraseSimple("Ох... совсем забыл.", "А, чёрт... точно!");
			    link.l1.go = "exit";
				break;
                }			
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

		//--------------------------------- Аренда склада ---------------------------------
		
		case "ShipyardsMap_1":
			dialog.text = "Хе! Ну, давай поговорим.";
			link.l1 = "Мне нужно попасть на верфь ночью, когда никого нет.";
			link.l1.go = "ShipyardsMap_2";
		break;
		case "ShipyardsMap_2":
			if (sti(pchar.questTemp.different.ShipyardsMap.skladFight))
			{
				dialog.text = "Вот это да! Эй, стража, тут вор подбирается!!!";
				link.l1 = "Какой вор?! Я поговорить "+ GetSexPhrase("хотел","хотела") +"!..";
				link.l1.go = "fight";
				AddCharacterExpToSkill(pchar, "FencingL", 5);
				AddCharacterExpToSkill(pchar, "FencingS", 5);
				AddCharacterExpToSkill(pchar, "FencingH", 5);
				ChangeCharacterComplexReputation(pchar,"nobility", -1);
			}
			else
			{
				dialog.text = "Хо! Ну, ты даёшь "+ GetSexPhrase("приятель. Пришёл","подруга. Пришла") +" на склад верфи с такой просьбой!";
				link.l1 = "Мне не на склад надо, а на верфь. Сюда я ни ногой...";
				link.l1.go = "ShipyardsMap_3";
				AddCharacterExpToSkill(pchar, "Fortune", 10);
			}
		break;
		case "ShipyardsMap_3":
			dialog.text = "Зачем тебе это?";
			link.l1 = "Надо приятель, надо. Я "+ GetSexPhrase("готов","готова") +" заплатить...";
			link.l1.go = "ShipyardsMap_4";
		break;
		case "ShipyardsMap_4":
			dialog.text = "Хм, уже интересней... В общем, так! Гони " + FindRussianMoneyString(sti(pchar.questTemp.different.ShipyardsMap.sklad)*1000) + ", и следующие сутки входную дверь верфи я буду оставлять открытой.";
			link.l1 = "Это слишком дорого для меня. Обойдусь...";
			link.l1.go = "exit";
			if (sti(pchar.money) >= (sti(pchar.questTemp.different.ShipyardsMap.sklad)*1000))
			{
				link.l2 = "Хорошо, я "+ GetSexPhrase("согласен","согласна") +". Забирай деньги и делай, как договорились.";
				link.l2.go = "ShipyardsMap_5";
			}
		break;
		case "ShipyardsMap_5":
			dialog.text = "Не волнуйся, всё сделаю.";
			link.l1 = "Хорошо, верю...";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, -sti(pchar.questTemp.different.ShipyardsMap.sklad)*1000);
			AddQuestRecord("ShipyardsMap", "5");
			AddQuestUserData("ShipyardsMap", "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			//снимаем close_for_night
			string  sName;
			int location_index = FindLocation(npchar.city + "_town");
    		makearef(arRld, Locations[location_index].reload);
    		Qty = GetAttributesNum(arRld);
    		for (int a=0; a<Qty; a++)
    		{
    			arDis = GetAttributeN(arRld, a);
				sName = arDis.go;
    			if (findsubstr(sName, "_shipyard" , 0) != -1)
    			{
					DeleteAttribute(arDis, "close_for_night");
					break;
    			}
    		}
			LocatorReloadEnterDisable(npchar.city + "_shipyard", "reload2", true);
			//ставим таймер на возврат close_for_night
			SetTimerFunction("ShipyardsMap_returnCFN", 0, 0, 2);
		break;

	}
}
