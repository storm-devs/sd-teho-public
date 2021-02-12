void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	string sLoc;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (LAi_grp_playeralarm > 0)
			{
       			dialog.text = NPCharRepPhrase(pchar,
					LinkRandPhrase("В городе поднята тревога, тебя всюду ищут! На твоем месте я бы не стал здесь задерживаться.", "Вся городская стража рыщет по городу в поисках тебя. Я не идиот и разговаривать с тобой не буду!", "Беги, "+ GetSexPhrase("приятель","подруга") +", пока солдаты не сделали из тебя решето..."),
					LinkRandPhrase("Что тебе нужно, "+ GetSexPhrase("негодяй","мерзавка") +"?! Городская стража уже взяла твой след, далеко тебе не уйти"+ GetSexPhrase(", грязный пират!","") +"", "Грязн"+ GetSexPhrase("ый","ая") +" убийца, вон из моего дома! Стража!!", "Я не боюсь тебя, мерзав"+ GetSexPhrase("ец","ка") +"! Скоро тебя повесят, далеко тебе не уйти..."));
				link.l1 = NPCharRepPhrase(pchar,
					RandPhraseSimple("Хех, тревога для меня не проблема...", "Им меня ни за что не поймать."),
					RandPhraseSimple("Заткни свою пасть, " + GetWorkTypeOfMan(npchar, "") + ", а не то вырву твой поганый язык!", "Хех, " + GetWorkTypeOfMan(npchar, "") + ", а все туда же - пиратов ловить! Вот что я тебе скажу, приятель: сиди тихо и будешь жить..."));
				link.l1.go = "exit";
				break;
			}
			if (npchar.quest.meeting == "0")
			{
				dialog.text = TimeGreeting() + "! Я вас раньше не видел, сеньор. Осмелюсь предположить, что вы капитан... Я угадал? Меня зовут "+GetFullName(npchar)+", и мой магазин к вашим услугам. Золото, серебро и много чего такого, что заинтересует любознательного человека.";
				Link.l1 = "Понятно. Я " + GetFullName(pchar) + ". Рад с вами познакомиться, "+npchar.name+".";
				Link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = TimeGreeting() + ", сеньор! Рад снова видеть вас в моем магазине. Желаете приобрести золотые самородки? Или, быть может, вас сегодня интересуют минералы?";
				link.l1 = "Покажите мне свои товары, "+npchar.name+".";
				link.l1.go = "trade";
				link.l4 = "Нет, ничего не надо, "+npchar.name+". Я просто зашел поздороваться с вами.";
				link.l4.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting":
			dialog.text = "Я тоже, сеньор. Будете смотреть мои товары? Я уверен, что некоторые из них вас точно заинтересуют.";
			link.l1 = "Я здесь впервые, и хотел бы немного больше узнать об этом поселении.";
			link.l1.go = "info";
			link.l2 = "Тогда показывайте, что там у вас на продажу.";
			link.l2.go = "trade";
		break;
		
		case "info":
			dialog.text = "Наш небольшой город построился благодаря золотоносному руднику. В шахте добывается золотая руда, а также золотые и серебряные самородки. Попадаются и ценные камни. Поначалу здесь был только гарнизон солдат, но потом к нам присоединились дружественные индейцы и немного белых переселенцев\nЗатем сюда прибыл Игнасио Ортега, который построил свою таверну, благодаря которой наша жизнь стала хоть чуточку веселее. Частыми гостями у нас стали авантюристы всех мастей, которые так и норовили украсть золото из шахты\nОднако после того, как мы вздернули несколько воров без долгих расследований прямо посередине города, желающих красть поубавилось. Золотую руду мы под надежной охраной солдат и дружественных индейцев транспортируем к берегу на корабли\nА вот золотые и серебряные самородки вы всегда можете купить в моем магазине. Кроме того, у меня в продаже есть интересные минералы. Так что заходите ко мне почаще, я постоянно обновляю ассортимент товаров.";
			link.l1 = "Спасибо за интересный рассказ! Приму к сведению.";			
			link.l1.go = "exit";
		break;
		
		case "trade":
			DialogExit();
			if (!CheckAttribute(npchar, "trade_date") || GetNpcQuestPastDayParam(npchar, "trade_date") >= 10)
			{
				GiveItemToTrader(npchar);
				SaveCurrentNpcQuestDateParam(npchar, "trade_date");
			}
			LaunchItemsTrade(npchar, 0);
		break;

 		case "Exit":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
		break;

		// ============== Грабеж среди бела дня, попытка залезть в сундуки =========================
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("Грабеж среди бела дня!!! Это что же такое делается?! Ну, погоди, "+ GetSexPhrase("приятель","подруга") +"...", "Эй, ты чего это там копаешься?! Никак, вздумал"+ GetSexPhrase("","а") +" ограбить меня? Ну, тогда тебе конец...", "Постой, ты куда это полез"+ GetSexPhrase("","ла") +"? Да ты вор"+ GetSexPhrase("","овка") +", оказывается! Ну, считай, что ты приплыл"+ GetSexPhrase("","а") +", родн"+ GetSexPhrase("ой","ая") +"...");
			link.l1 = LinkRandPhrase("Дьявол!!", "Каррамба!!", "А-ать, черт!");
			link.l1.go = "PL_Q3_fight";
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
	}
}
