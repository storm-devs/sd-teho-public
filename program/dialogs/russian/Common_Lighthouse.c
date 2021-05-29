#include "DIALOGS\russian\Rumours\Common_rumours.c" //Jason
// Jason общий диалог смотрителей маяков
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;	

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

    // вызов диалога по городам -->
    NPChar.FileDialog2 = "DIALOGS\" + LanguageGetLanguage() + "\Lighthouse\" + NPChar.City + "_Lighthouse.c";
    if (LoadSegment(NPChar.FileDialog2))
	{
        ProcessCommonDialog(NPChar, Link, NextDiag);
		UnloadSegment(NPChar.FileDialog2);
	}
    // вызов диалога по городам <--
	ProcessCommonDialogRumors(NPChar, Link, NextDiag);
	
    int iTest, iTemp;
	string sTemp;
	bool ok;
    iTest = FindColony(NPChar.City); // город
    ref rColony;
	if (iTest != -1)
	{
		rColony = GetColonyByIndex(iTest);
	}
	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (LAi_grp_playeralarm > 0)
			{
       			dialog.text = PCharRepPhrase(LinkRandPhrase("В городе поднята тревога. Похоже, и мне пора браться за оружие...", "Уж не за тобой ли носится вся городская стража?.. Ко мне, солдаты!!!", "У меня приюта ты не найдешь. Зато найдешь несколько дюймов холодной стали под ребро!"), 
					LinkRandPhrase("Что тебе нужно, "+ GetSexPhrase("негодяй","негодяйка") +"?! Городская стража уже взяла твой след, далеко тебе не уйти, "+ GetSexPhrase("грязный пират","мерзавка") +"!", ""+ GetSexPhrase("Грязный","Грязная") +" убийца! Стража!!!", "Я не боюсь тебя, "+ GetSexPhrase("мерзавец","мерзавка") +"! Скоро тебя повесят в нашем форте, далеко тебе не уйти..."));
				link.l1 = PCharRepPhrase(RandPhraseSimple("Похоже, тебе жить надоело...", "Хех, и не живется же спокойно мирным гражданам " + XI_ConvertString("Colony" + npchar.city + "Gen") + "!"), 
					RandPhraseSimple("Отправляйся в ад!", "Хех, жить тебе осталось несколько секунд..."));
				link.l1.go = PCharRepPhrase("exit_setOwner", "fight");
				break;
			}
			if (npchar.quest.meeting == "0")
			{
				dialog.text = RandPhraseSimple("Добрый день, моряк! Меня зовут "+GetFullName(npchar)+", и я - смотритель этого маяка. Каким ветром вас сюда занесло?", "Здравствуйте! Давненько я не видал новых лиц на моем маяке... Позвольте представиться - "+GetFullName(npchar)+", а этот маяк - мой дом и моя работа. Чем могу служить?");
				link.l1 = "Здравствуй, "+npchar.name+"! Мое имя - "+GetFullName(pchar)+", я капитан корабля. Гулял по этой чудесной бухте, решил заглянуть, посмотреть - кто тут живет...";
				link.l1.go = "Lightman_meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "А-а, мой старый знакомый, капитан "+GetFullName(pchar)+"! Проходите, проходите! Что привело вас ко мне на этот раз?";
				link.l1 = "Приветствую, старый морской волк! Ты еще не воешь от одиночества на своем маяке?";
				link.l1.go = "Lightman_talk";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "Lightman_meeting":
			dialog.text = "Ну вот, теперь будете знать. Я тоже моряк, как и вы, правда, давно уже не ступал на палубу корабля... Эх! Теперь моя забота - этот маяк. А также приторговываю всякой всячиной...";
			link.l1 = "А чем ты торгуешь, скажи пожалуйста?";
			link.l1.go = "trade_info";
			NextDiag.TempNode = "First time";
		break;
		
		case "Lightman_talk":
			dialog.text = "Что привело вас ко мне на сей раз?";
			link.l1 = RandPhraseSimple("Не расскажешь, что интересного в вашей колонии случилось за последнее время?","Давно не был на суше... Что новенького в ваших краях?");
			link.l1.go = "rumours_lighthouse";
			link.l2 = "Давай посмотрим, что у тебя есть сегодня в продаже.";
			link.l2.go = "Trade_lighthouse";
			if (CheckAttribute(npchar, "artefact"))
			{
				if (CheckAttribute(npchar, "quest.art"))
				{
					link.l3 = "Ну что, "+npchar.name+", мой амулет еще не привезли?";
					link.l3.go = "Trade_artefact_3";
				}
				else
				{
					link.l3 = ""+npchar.name+", я хочу заказать у тебя амулет.";
					link.l3.go = "Trade_artefact_1";
				}
				// калеуче
				if (CheckAttribute(pchar, "questTemp.Caleuche") && pchar.questTemp.Caleuche == "amulet" && !CheckAttribute(npchar, "quest.Caleuche"))
				{
					link.l5 = "Послушай, "+npchar.name+", я знаю, что ты занимаешься привозом амулетов под заказ. Значит, ты наверняка в них хорошо разбираешься. Посмотри, пожалуйста, на эту вещицу - что ты можешь сказать о ней?";
					link.l5.go = "Caleuche";
				}
				if (npchar.id == pchar.questTemp.Caleuche.Amuletmaster && CheckAttribute(pchar, "questTemp.Caleuche") && pchar.questTemp.Caleuche == "mayak")
				{
					link.l5 = "Приятель, я снова к тебе по поводу тех странных амулетов.";
					link.l5.go = "Caleuche_9";
				}
			}
			link.l4 = "Я вот что "+ GetSexPhrase("хотел","хотела") +" спросить...";
			link.l4.go = "quests";
			link.l9 = "Просто на огонек заглянул...";
			link.l9.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
		case "trade_info":
			dialog.text = "Время от времени я хожу за раковинами. Здесь недалеко есть неплохое местечко. Так что у меня всегда можно купить жемчужины. После каждого шторма я обхожу свой пляж - море выбрасывает на берег куски янтаря - его я тоже продаю, хотя сразу говорю - недешево\nИногда волны выкидывают всякие занятные вещицы с утонувших кораблей, да и мои старые знакомцы привозят диковины на продажу, но меня в основном интересуют заговоренные амулеты - за них можно выручить у знающего человека хорошую сумму\nИногда мне приносят, или я сам нахожу на... ну, неважно где, сабли и прочее оружие. Всякий хлам у меня покупает городской торговец, а достойные экземпляры я привожу в порядок и выставляю на продажу\nА вот насчет купить - меня интересует ром. Только не это дешевое пойло, что в кабаке по два песо за кружку продают, а бутилированный ямайский ром многолетней выдержки. Он способен исцелять от хворей и невероятно бодрит с первого же глотка. Я готов платить десятикратную цену за каждую бутылку, так что приносите.";
			link.l1 = "Послушай, "+npchar.name+", ты сказал, что у тебя есть старые друзья-моряки, которые привозят тебе заговоренные амулеты. А нельзя ли заказать тебе конкретный амулет? Я хорошо заплачу.";
			link.l1.go = "Trade_artefact";
		break;
		
		case "Trade_lighthouse":
			//иногда продает корабельные товары // Addon-2016 Jason
			npchar.quest.goods = GOOD_COFFEE + drand(sti(GOOD_PAPRIKA - GOOD_COFFEE));
			npchar.quest.goodsqty = 50+drand(100);
			if (sti(npchar.quest.goods) == GOOD_EBONY || sti(npchar.quest.goods) == GOOD_MAHOGANY) npchar.quest.goodsqty = 25+drand(50);
			npchar.quest.goodsprice = makeint(sti(Goods[sti(npchar.quest.goods)].Cost)/4);//цена единицы товара
			npchar.quest.goodscost = sti(npchar.quest.goodsprice)*sti(npchar.quest.goodsqty);//стоимость товара
			ok = (!CheckAttribute(npchar, "goods_date")) || (GetNpcQuestPastDayParam(npchar, "goods_date") >= 10)
			if (drand(4) == 1 && makeint(GetCharacterFreeSpace(pchar, sti(npchar.quest.goods))) > sti(npchar.quest.goodsqty) && sti(pchar.money) >= sti(npchar.quest.goodscost) && ok)
			{
				dialog.text = "Капитан, тут недавно на берег выбросило приличное количество товара - " + GetGoodsNameAlt(sti(npchar.quest.goods))+ ". Часть была испорчена морской водой, но " + FindRussianQtyString(sti(npchar.quest.goodsqty)) + " мне удалось сохранить в отличном состоянии. Не желаете ли купить? Дешево отдам, всего за "+FindRussianMoneyString(sti(npchar.quest.goodsprice))+" за штуку.";
				link.l1 = "Нет, не желаю. Показывай, что ты насобирал на продажу.";
				link.l1.go = "Trade_lighthouse_double";
				link.l2 = "Хм... Хорошее предложение, я согласен. Думаю, я без труда перепродам это с выгодой для себя. Так, посмотрим... В сумме это составит "+FindRussianMoneyString(sti(npchar.quest.goodscost))+". Всё правильно?";
				link.l2.go = "Trade_goods";
				SaveCurrentNpcQuestDateParam(npchar, "goods_date");
			}
			else
			{
				DialogExit();
				if (!CheckAttribute(npchar, "trade_date") || GetNpcQuestPastDayParam(npchar, "trade_date") >= 10)
				{
					GiveItemToTrader(npchar);
					SaveCurrentNpcQuestDateParam(npchar, "trade_date");
				}
				LaunchItemsTrade(npchar, 0);
			}
		break;
		
		case "Trade_lighthouse_double":
			DialogExit();
			if (!CheckAttribute(npchar, "trade_date") || GetNpcQuestPastDayParam(npchar, "trade_date") >= 10)
			{
				GiveItemToTrader(npchar);
				SaveCurrentNpcQuestDateParam(npchar, "trade_date");
			}
			LaunchItemsTrade(npchar, 0);
		break;
		
		case "Trade_goods":
			AddCharacterGoods(pchar, sti(npchar.quest.goods), sti(npchar.quest.goodsqty));
			AddMoneyToCharacter(pchar, -sti(npchar.quest.goodscost));
			AddMoneyToCharacter(npchar, sti(npchar.quest.goodscost));
			dialog.text = "Вы верно подсчитали, капитан. Отличная сделка! Мы оба в накладе не остались...";
			link.l1 = "Вот и замечательно. Сейчас пришлю матросов. А теперь показывай, что ты насобирал на продажу.";
			link.l1.go = "Trade_lighthouse_double";
		break;
//------------------------------------------------заказ артефактов------------------------------------------------
		case "Trade_artefact": // Addon-2016 Jason за дублоны
			if (CheckAttribute(npchar, "artefact"))
			{
				dialog.text = "Ну, не все конечно, но кое-какие вещицы мне привозят чаще других, так что, думаю, смогу вам помочь. Сразу предупреждаю: стоимость любого амулета под заказ - 100 дублонов. Сами понимаете...";
				link.l1 = "Цена меня не пугает. И какие амулеты ты сможешь достать?";
				link.l1.go = "Trade_artefact_1";
				link.l2 = "Да ну! Дороговато выходит. Лучше я уж как-нибудь сам...";
				link.l2.go = "exit_artefact";
			}
			else
			{
				dialog.text = "Нет, капитан. Эти вещицы находят случайно, как их можно привезти под заказ? Да и ждать пришлось бы невесть сколько времени...";
				link.l1 = "Ну, как говорится, на нет - и суда нет...";
				link.l1.go = "exit_artefact";
			}
		break;
		
		case "exit_artefact":
			if (CheckAttribute(npchar, "artefact")) dialog.text = "Ну, как знаете. Надумаете - обращайтесь.";
			else dialog.text = "Будете смотреть, что у меня есть сегодня в продаже, капитан? Если ничего достойного не найдете - заходите еще, почаще, может, что интересующее вас и появится.";
			link.l1 = "Покажи мне свои товары.";
			link.l1.go = "Trade_lighthouse";
			link.l2 = RandPhraseSimple("Лучше расскажи, что интересного в вашей колонии случилось за последнее время?","Торговля-торговлей, а вот я давненько не был на суше... Что новенького в ваших краях?");
			link.l2.go = "rumours_lighthouse";
			link.l3 = "Всё это, конечно, хорошо, но я вот что "+ GetSexPhrase("хотел","хотела") +" спросить...";
			link.l3.go = "quests";
			link.l4 = "Всего доброго, "+npchar.name+"! Приятно было познакомиться! Еще загляну...";
			link.l4.go = "exit";
		break;
		
		case "Trade_artefact_1":
			dialog.text = "Выбирайте.";
			iTemp = 1;
			string sArt;
			if (CheckAttribute(npchar, "artefact.indian")) sArt = "indian_";
			if (CheckAttribute(npchar, "artefact.amulet")) sArt = "amulet_";
			if (CheckAttribute(npchar, "artefact.obereg")) sArt = "obereg_";
			for (i=11; i>=1; i--)
			{
				sTemp = "l"+iTemp;
				link.(sTemp) = XI_ConvertString(sArt+i);
				link.(sTemp).go = sArt+i;
				iTemp++;
			}
			link.l12 = "К сожалению, ничего из этого списка меня не интересует.";
			link.l12.go = "exit";
		break;
		
		//группа indian
		case "indian_1":
			dialog.text = "Кукла Вуду? Уважаете огнестрельное оружие? Хорошо...";
			link.l1 = "Когда мне вернуться к тебе за своим заказом?";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "indian_1";
		break;
		
		case "indian_2":
			dialog.text = "Пороховой тестер? Меткая стрельба - залог успеха в схватке. Хорошо...";
			link.l1 = "Когда мне вернуться к тебе за своим заказом?";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "indian_2";
		break;
		
		case "indian_3":
			dialog.text = "Ритуальный нож? Любите от души рубануть своего врага тяжелым палашом? Тогда это точно для вас. Хорошо...";
			link.l1 = "Когда мне вернуться к тебе за своим заказом?";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "indian_3";
		break;
		
		case "indian_4":
			dialog.text = "Секира? Нет надежней удара, чем рубануть сверху вниз здоровенным топором! Хорошо...";
			link.l1 = "Когда мне вернуться к тебе за своим заказом?";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "indian_4";
		break;
		
		case "indian_5":
			dialog.text = "Тсантса? Эта штучка припугнет даже самого отчаянного пирата. Хорошо...";
			link.l1 = "Когда мне вернуться к тебе за своим заказом?";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "indian_5";
		break;
		
		case "indian_6":
			dialog.text = "Коралловая голова? Пусть картечь из ваших пушек летит всегда точно в цель! Хорошо...";
			link.l1 = "Когда мне вернуться к тебе за своим заказом?";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "indian_6";
		break;
		
		case "indian_7":
			dialog.text = "Горбун? Неутомимость - это лучший друг воина. Хорошо...";
			link.l1 = "Когда мне вернуться к тебе за своим заказом?";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "indian_7";
		break;
		
		case "indian_8":
			dialog.text = "Шиутекутли? Пускай корпус вражеского судна рассыпется в труху! Хорошо...";
			link.l1 = "Когда мне вернуться к тебе за своим заказом?";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "indian_8";
		break;
		
		case "indian_9":
			dialog.text = "Бальд? Наденьте Бальд - и пусть все ядра летят точно в цель! Хорошо...";
			link.l1 = "Когда мне вернуться к тебе за своим заказом?";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "indian_9";
		break;
		
		case "indian_10":
			dialog.text = "Каскавела? Нет ничего страшнее змеиного яда. Хорошо...";
			link.l1 = "Когда мне вернуться к тебе за своим заказом?";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "indian_10";
		break;
		
		case "indian_11":
			dialog.text = "Маска нгомбо? Надень и усыпи бдительность врагов, ха-ха! Хорошо...";
			link.l1 = "Когда мне вернуться к тебе за своим заказом?";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "indian_11";
		break;
		
		//группа amulet
		case "amulet_1":
			dialog.text = "Щит нгомбо? Если не удалось увернуться от пули, этот амулет может спасти жизнь. Хорошо...";
			link.l1 = "Когда мне вернуться к тебе за своим заказом?";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "amulet_1";
		break;
		
		case "amulet_2":
			dialog.text = "Молитвослов? Добрая молитва способна даже пулю отвести в сторону. Хорошо...";
			link.l1 = "Когда мне вернуться к тебе за своим заказом?";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "amulet_2";
		break;
		
		case "amulet_3":
			dialog.text = "Нательный крест? Он здорово поможет христианину в рукопашной схватке. Хорошо...";
			link.l1 = "Когда мне вернуться к тебе за своим заказом?";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "amulet_3";
		break;
		
		case "amulet_4":
			dialog.text = "Эль Трозо? Он делает смертельную рану легкой царапиной. Хорошо...";
			link.l1 = "Когда мне вернуться к тебе за своим заказом?";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "amulet_4";
		break;
		
		case "amulet_5":
			dialog.text = "Согбо? И пусть пушки будут всегда готовы к бою! Хорошо...";
			link.l1 = "Когда мне вернуться к тебе за своим заказом?";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "amulet_5";
		break;
		
		case "amulet_6":
			dialog.text = "Мадонна? Образ Пресвятой Девы обладает воистину исцеляющими способностями. Хорошо...";
			link.l1 = "Когда мне вернуться к тебе за своим заказом?";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "amulet_6";
		break;
		
		case "amulet_7":
			dialog.text = "Святая вода? Даже хиляк, окропившийся святой водой, становится богатырем! Хорошо...";
			link.l1 = "Когда мне вернуться к тебе за своим заказом?";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "amulet_7";
		break;
		
		case "amulet_8":
			dialog.text = "Якорь? И пусть судно остается на плаву под градом ядер, ха-ха! Хорошо...";
			link.l1 = "Когда мне вернуться к тебе за своим заказом?";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "amulet_8";
		break;
		
		case "amulet_9":
			dialog.text = "Энколпион? Никакой ветер не страшен парусам, если у вас есть этот амулет. Хорошо...";
			link.l1 = "Когда мне вернуться к тебе за своим заказом?";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "amulet_9";
		break;
		
		case "amulet_10":
			dialog.text = "Чудотворец? Да хранит Господь вашу команду на суше и на море! Хорошо...";
			link.l1 = "Когда мне вернуться к тебе за своим заказом?";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "amulet_10";
		break;
		
		case "amulet_11":
			dialog.text = "Чимарута? Мушкетные пули просвистят над головами, не причинив вреда! Хорошо...";
			link.l1 = "Когда мне вернуться к тебе за своим заказом?";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "amulet_11";
		break;
		
		//группа obereg
		case "obereg_1":
			dialog.text = "Тередо? Каждый корабельный плотник мечтает о нем. Хорошо...";
			link.l1 = "Когда мне вернуться к тебе за своим заказом?";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "obereg_1";
		break;
		
		case "obereg_2":
			dialog.text = "Шочипили? Всё меньше колоть пальцы иглой, штопая паруса. Хорошо...";
			link.l1 = "Когда мне вернуться к тебе за своим заказом?";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "obereg_2";
		break;
		
		case "obereg_3":
			dialog.text = "Обезьяна? А по мне так - вьючный мул! Хорошо...";
			link.l1 = "Когда мне вернуться к тебе за своим заказом?";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "obereg_3";
		break;
		
		case "obereg_4":
			dialog.text = "Веер цыганки? Надень шоры на глаза патрулю! Хорошо...";
			link.l1 = "Когда мне вернуться к тебе за своим заказом?";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "obereg_4";
		break;
		
		case "obereg_5":
			dialog.text = "Нефритовая черепашка? Это ваш джокер в колоде карт! Хорошо...";
			link.l1 = "Когда мне вернуться к тебе за своим заказом?";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "obereg_5";
		break;
		
		case "obereg_6":
			dialog.text = "Обезьяний кулак? Как говорится - заставь уважать себя! Хорошо...";
			link.l1 = "Когда мне вернуться к тебе за своим заказом?";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "obereg_6";
		break;
		
		case "obereg_7":
			dialog.text = "Рыбак? Его видит во сне каждый штурман. Хорошо...";
			link.l1 = "Когда мне вернуться к тебе за своим заказом?";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "obereg_7";
		break;
		
		case "obereg_8":
			dialog.text = "Четки торговца? Деньги любят счет, не правда ли? Хорошо...";
			link.l1 = "Когда мне вернуться к тебе за своим заказом?";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "obereg_8";
		break;
		
		case "obereg_9":
			dialog.text = "Эхекатль? Любое тихоходное корыто несется быстрее ветра! Хорошо...";
			link.l1 = "Когда мне вернуться к тебе за своим заказом?";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "obereg_9";
		break;
		
		case "obereg_10":
			dialog.text = "Серьга морехода? Вставьте ее в ухо своему рулевому! Хорошо...";
			link.l1 = "Когда мне вернуться к тебе за своим заказом?";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "obereg_10";
		break;
		
		case "obereg_11":
			dialog.text = "Пилигрим? Встречный ветер становится попутным. Хорошо...";
			link.l1 = "Когда мне вернуться к тебе за своим заказом?";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "obereg_11";
		break;
		
		case "Trade_artefact_2":
			dialog.text = "Месяца через два, не раньше. Думаю, к тому моменту мне уже его привезут. Так что жду вас к этому времени с деньгами.";
			link.l1 = "Хорошо! Обязательно буду! Спасибо, "+npchar.name+"!";
			link.l1.go = "exit";
			SaveCurrentNpcQuestDateParam(npchar, "art_date");
			npchar.quest.artday = rand(20)+50;
			sTemp = "Amulet_"+npchar.location;
			AddQuestRecord(sTemp, "1");
			ReOpenQuestHeader(sTemp);
			AddQuestUserData(sTemp, "sAml", XI_ConvertString(npchar.quest.art)); // dlc
		break;
		
		case "Trade_artefact_3":
			if (CheckAttribute(npchar, "art_date") && GetNpcQuestPastDayParam(npchar, "art_date") >= sti(npchar.quest.artday))
			{
			dialog.text = "Да, он у меня. Вы приготовили 100 дублонов, капитан?"; // Addon-2016 Jason
				if(GetCharacterItem(pchar, "gold_dublon") >= 100)
				{
					link.l1 = "Конечно! Вот, держи, как и договаривались.";
					link.l1.go = "Trade_artefact_4";
				}
				else
				{
					link.l1 = "Эх, деньги на корабле забыл! Сейчас принесу...";
					link.l1.go = "exit";
				}
			}
			else
			{
			dialog.text = "Еще нет. Загляните ко мне попозже и не беспокойтесь - привезут обязательно.";
			link.l1 = "Хорошо.";
			link.l1.go = "exit";
			}
		break;
		
		case "Trade_artefact_4":
			RemoveItems(pchar, "gold_dublon", 100); // Addon-2016 Jason
			Log_Info("Вы отдали 100 дублонов");
			dialog.text = "Так, все верно. Вот, получите ваш амулет. Пользуйтесь на здоровье!";
			link.l1 = "Спасибо, "+npchar.name+"!";
			link.l1.go = "Trade_artefact_5";
		break;
		
		case "Trade_artefact_5":
			DialogExit();
			Log_Info("Вы получили "+XI_ConvertString(npchar.quest.art)+"");
			PlaySound("interface\important_item.wav");
			TakeNItems(pchar, npchar.quest.art, 1);
			DeleteAttribute(npchar, "quest.art");
			sTemp = "Amulet_"+npchar.location;
			AddQuestRecord(sTemp, "2");
			CloseQuestHeader(sTemp);
		break;
		
		// --> калеуче
		case "caleuche":
			PlaySound("interface\important_item.wav");
			dialog.text = "Показывай, что там у тебя.";
			link.l1 = "Вот, похоже на старинный индейский амулет. Но только для чего он может быть нужен - ума не приложу.";
			link.l1.go = "caleuche_1";
			npchar.quest.caleuche = "true";
		break;
		
		case "caleuche_1":
			if (npchar.id == pchar.questTemp.Caleuche.Amuletmaster)
			{
				dialog.text = "Так-так... Ты уже третий, кто показывает мне такую штуковину. Этот амулет, приятель, попал сюда из дикой сельвы Южного Мэйна. Где-то там, далеко, южнее Панамы, у подножия гор, живут индейцы, которые носят похожие на этот амулеты. Сами краснокожие говорят, что это наследие их 'великих предков'\nКто их великие предки, и какое наследие они им оставили - я не ведаю. Но могу дать совет, у кого расспросить подробнее. Тебе это интересно?";
				link.l1 = "Конечно!";
				link.l1.go = "caleuche_2";
			}
			else
			{
				dialog.text = "Хм... Держал я много самых разных амулетов в своих руках, но такой на Карибах встечаю впервые. Извини, дружище, ничем помочь не могу - сам не знаю, что это за диковина. Но то, что вещь не простая - факт. Спроси еще у кого-нибудь - может, кто-то встречал подобное.";
				link.l1 = "Жаль... Буду спрашивать дальше - глядишь, повезет.";
				link.l1.go = "exit";
			}
		break;
		
		case "caleuche_2":
			dialog.text = "На Доминике есть деревня карибов вождя Мокнитекуври. У них есть шаман по имени Туттуатхапак, очень уважаемый индеец. Он не из карибов, а как раз из тех мест, про которые я тебе сказал. Он-то наверняка сможет поведать об этом амулете побольше меня. Но будь осторожен - Туттуатхапак очень не любит белых. Очень. Ведь они когда-то забрали его в рабство и увезли из родных мест...";
			link.l1 = "Значит, он именно таким образом и попал на Карибы?";
			link.l1.go = "caleuche_3";
		break;
		
		case "caleuche_3":
			dialog.text = "Да. Тут очень интересная история... Судно, на котором перевозили индейцев-рабов, попало в мертвый штиль у острова Мария Галанте, и половина команды умерла за несколько дней от внезапной эпидемии лихорадки. Но ни один индеец-раб не заболел!\nА потом капитан рехнулся и поджег свою лоханку. В итоге пленные индейцы в суматохе вырвались на свободу и порешили почти всех матросов. Как думаешь, кто был у них главарем?";
			link.l1 = "Догадываюсь...";
			link.l1.go = "caleuche_4";
		break;
		
		case "caleuche_4":
			dialog.text = "Вот-вот. Не пить мне рома до конца дней моих, если это не шаман навел колдовскими чарами штиль на море, заразу на команду и помешательство на капитана. Этот индеец очень умен и очень опасен. Если пойдешь к нему - веди себя вежливо и следи за тем, что говоришь - иначе быть беде. И без подношения к нему не суйся - он даже не станет с тобой разговаривать.";
			link.l1 = "А что за подношение ему нужно?";
			link.l1.go = "caleuche_5";
		break;
		
		case "caleuche_5":
			dialog.text = "Всякой чепухой ты его не купишь. Как я слышал, он отправляет своих воинов-карибов покупать у белых огнестрельное оружие. Принеси ему в подарок мушкет - думаю, он обрадуется и уделит тебе немного своего внимания.";
			link.l1 = "Спасибо! Так и сделаю... Скажи, приятель, а откуда ты все это знаешь?";
			link.l1.go = "caleuche_6";
		break;
		
		case "caleuche_6":
			dialog.text = "Мой друг был матросом на том злосчастном корабле. По счастью, ему удалось выжить в том аду кромешном... У него я и увидел в первый раз побрякушки с таким рисунком, как на твоем амулете - видать, вместе с индейцами капитан покойный прихватил еще и их скарб. Уверен, что и твой амулет из его коллекции - когда капитан свихнулся и устроил пожар, матросы его кокнули, а потом разграбили сундуки в каюте.";
			link.l1 = "Ясно. Тогда мне остается только отправиться с подарком на Доминику. Спасибо за помощь и за интересный рассказ!";
			link.l1.go = "caleuche_7";
		break;
		
		case "caleuche_7":
			dialog.text = "Удачи, дружище, и будь осторожен с этим краснокожим дьяволом...";
			link.l1 = "...";
			link.l1.go = "caleuche_8";
		break;
		
		case "caleuche_8":
			DialogExit();
			AddQuestRecord("Caleuche", "2");
			pchar.questTemp.Caleuche = "dominica"; 
			Caleuche_CreateShamane();
		break;
		
		case "caleuche_9":
			dialog.text = "Да? Ты был у Туттуатхапака?";
			link.l1 = "Точно. И теперь я хочу найти еще два амулета. Ты же вроде говорил, что я третий, кто тебе такой артефакт показал. А кто были еще двое?";
			link.l1.go = "caleuche_10";
		break;
		
		case "caleuche_10":
			dialog.text = "Один - это мой друг, тот самый матрос с корабля работорговцев, на котором привезли Туттуатхапака. С того случая он больше в море ни ногой. Я его давно не видел, но знаю, где он обретается. Ищи его на Западном Мэйне в Белизе - он заделался охотником и теперь шастает по джунглям. Имя - Фергус Хупер.";
			link.l1 = "Запомню. А второй?";
			link.l1.go = "caleuche_11";
		break;
		
		case "caleuche_11":
			dialog.text = "Про второго я знаю немного. Его зовут то ли Джек, то ли Джексон, и он то ли капер, то ли мелкий делец, то ли просто авантюрист. У него шебека с каким-то странным именем... м-м-м... как же называлась его лоханка? Черт возьми, забыл! Но имечко какое-то бесовское. Я спросил его, что оно означает, и он сказал, что это полуженщина-полуптица, рожденная морскими божествами. Тьфу ты, нехристь...";
			link.l1 = "Вот умник выискался... Так названия шебеки ты не помнишь?";
			link.l1.go = "caleuche_12";
		break;
		
		case "caleuche_12":
			dialog.text = "Нет, разрази меня гром, не помню. А, и еще: когда он представлялся мне, то сказал, что он с Барбадоса.";
			link.l1 = "Уже что-то! Ладно, попробую разыскать этого любителя пернатых женщин, пока его не нашел кое-кто другой... Спасибо, дружище, ты мне очень помог!";
			link.l1.go = "caleuche_13";
		break;
		
		case "caleuche_13":
			dialog.text = "Не за что, кэп, захаживай еще, поболтаем.";
			link.l1 = "Загляну обязательно!";
			link.l1.go = "caleuche_14";
		break;
		
		case "caleuche_14":
			DialogExit();
			AddQuestRecord("Caleuche", "7");
			pchar.questTemp.Caleuche = "hunting"; 
			pchar.questTemp.Caleuche.Belizterms = rand(4)+3;
			pchar.quest.caleuche_prepare_beliz.win_condition.l1 = "location";
			pchar.quest.caleuche_prepare_beliz.win_condition.l1.location = "Beliz";
			pchar.quest.caleuche_prepare_beliz.function = "Caleuche_PrepareBeliz";
		break;
		
		case "fight":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_group_Attack(NPChar, Pchar);
			if (rand(3) != 1) SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "exit_setOwner":
			LAi_SetOwnerTypeNoGroup(npchar);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "Man_FackYou"://реакция на попытку залезть в сундук
			dialog.text = LinkRandPhrase("Да ты "+ GetSexPhrase("вор, милейший! Стража, держи его","воровка! Стража, держи ее") +"!!!", "Вот это да! Чуть я загляделся, а ты сразу в сундук с головой! Держи "+ GetSexPhrase("вора","воровку") +"!!!", "Стража! Грабят!!! Держи "+ GetSexPhrase("вора","воровку") +"!!!");
			link.l1 = "А-ать, дьявол!!!";
			link.l1.go = "fight";
		break;
	}
}