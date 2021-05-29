// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Какие вопросы?", "Что вам угодно?"), "Совсем недавно вы пытались задать мне вопрос...", "У себя на верфи, а и вообще в городе, я таких однообразно любознательных не видал.",
                          "Ну что за вопросы? Мое дело - корабли строить, давайте этим и займемся.", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Я "+ GetSexPhrase("передумал","передумала") +"...", "Сейчас мне не о чем говорить"), "Хм, что-то с памятью моей стало...",
                      "Хм, однако...", "Давайте...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			// Addon-2016 Jason ФМК-Мартиника
			if (CheckAttribute(pchar, "questTemp.FMQM") && pchar.questTemp.FMQM == "begin")
            {
                link.l1 = "Ваш человек встретил меня у пирса и сообщил, что вы желаете меня видеть. Слушаю вас внимательно.";
                link.l1.go = "FMQM";
            }
			if (CheckAttribute(pchar, "questTemp.FMQM") && pchar.questTemp.FMQM == "oil" && GetSquadronGoods(pchar, GOOD_OIL) >= 50)
            {
                link.l1 = "Я выполнил ваше задание. Смолы в количестве "+FindRussianQtyString(GetSquadronGoods(pchar, GOOD_OIL))+" находятся у меня в трюме.";
                link.l1.go = "FMQM_9";
            }
		break;
		
		// Addon-2016 Jason ФМК-Мартиника
		case "FMQM":
			pchar.quest.FMQM_Denial.over = "yes";
			dialog.text = "Да-да, капитан "+GetFullName(pchar)+". Я увидел, как ваш корабль входит в порт, и сразу отправил одного из своих людей. Перейду сразу к делу: вы хоть и недавно в наших краях, но уже ходят слухи, что вы стали бывалым моряком, и вам сопутствует удача. Поэтому у меня к вам предложение.";
			link.l1 = "Очень интересно! Ну, давайте, выкладывайте.";
			link.l1.go = "FMQM_1";
		break;
		
		case "FMQM_1":
			dialog.text = "В корабельном деле, для придания дополнительной прочности корпусу, используется смоляная пропитка древесины. Для этого применяются специальные природные смолы, которые добываются на испанском острове Тринидад. Товар дорогой и редкий, так как испанцы используют их для потребностей своего военного флота и не горят желанием делиться с кем-либо. Торговля данным товаром находится под контролем колониальных властей всех держав, проще говоря - свободный оборот под запретом\nА вот мне, для выполнения одного специального заказа, очень нужны эти смолы. Естественно, наш магазин ими не располагает, да и на военных складах их нет, или не пожелали продать - это уже неважно... Важно то, что они мне крайне необходимы - раз, и то, что я узнал, где и как их можно достать - два. Но для второго пункта требуется капитан, не страшащийся абордажных схваток.";
			link.l1 = "Кажется, я начинаю понимать суть вашего предложения...";
			link.l1.go = "FMQM_2";
		break;
		
		case "FMQM_2":
			dialog.text = "Прекрасно. Сейчас в порту Сан-Хосе стоит небольшой торговый конвой. В трюмах одного из кораблей будет отправлена приличная партия так нужных мне смол. Если вы не находите ничего ужасного в том, чтобы пощипать врагов нашей державы - я расскажу вам все подробности. Если нет - то и суда нет. Теперь слово за вами.";
			link.l1 = "Предложение интересное. Я готов попытаться.";
			link.l1.go = "FMQM_3";
			link.l2 = "Пожалуй, я откажусь, месье. Мой корабль и команда сейчас не в самом лучшем состоянии.";
			link.l2.go = "FMQM_exit";
		break;
		
		case "FMQM_exit":
			dialog.text = "Что же, как знаете. Это ваше право. Простите, что отнял ваше время, капитан.";
			link.l1 = "Всего доброго.";
			link.l1.go = "FMQM_exit_1";
		break;
		
		case "FMQM_exit_1":
			DialogExit();
			pchar.questTemp.FMQM = "fail";
			AddQuestRecord("FMQ_Martinique", "3");
			CloseQuestHeader("FMQ_Martinique");
		break;
		
		case "FMQM_3":
			string sTemp = "баркентине";
			if (MOD_SKILL_ENEMY_RATE < 7) sTemp = "барке";// Addon 2016-1 Jason пиратская линейка
			dialog.text = "Тогда запоминайте: конвой состоит из трех судов. Смола будет находиться среди прочих товаров на "+sTemp+" с названием 'Бенсэхо'. Это и есть ваша цель. Как я уже сказал, испанцы отправляются из Сан-Хосе, что на Тринидаде. Пункт прибытия - Сан-Хуан, это на Пуэрто-Рико. Конвой отправится в путь завтра на рассвете - так что прикиньте, где вам удобнее будет перехватить его.";
			link.l1 = "Ясно. Что насчет оплаты?";
			link.l1.go = "FMQM_4";
		break;
		
		case "FMQM_4":
			dialog.text = "Меня интересует только смола. И я заплачу по пятнадцать золотых дублонов за каждый бочонок товара. По моим сведениям, на 'Бенсэхо' не меньше сотни бочонков.";
			link.l1 = "Ого! Это огромная сумма получается!..";
			link.l1.go = "FMQM_5";
		break;
		
		case "FMQM_5":
			dialog.text = "Да. Я говорил вам - товар редкий и дорогой.";
			link.l1 = "Но вы также говорили и о том, что свободный оборот смолы запрещен...";
			link.l1.go = "FMQM_6";
		break;
		
		case "FMQM_6":
			dialog.text = "Не переживайте. Вы же не понесете ее в магазин или контрабандистам. После операции возвращаетесь в Сен-Пьер и ставите свое судно ко мне в доки на ремонт, вечером. По темноте, дабы не привлекать внимание плотников, двое моих верных людей перенесут всю смолу с вашего корабля в укромное место на верфи. Никто ничего не заподозрит.";
			link.l1 = "Вы предусмотрительны, мастер. Хорошо. Тогда я не буду терять время и отправляюсь на свое судно.";
			link.l1.go = "FMQM_7";
		break;
		
		case "FMQM_7":
			dialog.text = "Желаю вам удачи, капитан.";
			link.l1 = "...";
			link.l1.go = "FMQM_8";
		break;
		
		case "FMQM_8":
			DialogExit();
			pchar.questTemp.FMQM = "convoy";
			AddQuestRecord("FMQ_Martinique", "4");
			SetFunctionTimerCondition("FMQM_ConvoyStart", 0, 0, 1, false);
		break;
		
		case "FMQM_9":
			dialog.text = "Превосходно! Давайте поставим ваше судно в доки, а в сумерки займемся разгрузкой, как и договаривались. Вы отправляйтесь на корабль, а я пока соберу монеты и подготовлю вашу награду.";
			link.l1 = "Так и поступим.";
			link.l1.go = "FMQM_10";
		break;
		
		case "FMQM_10":
			pchar.quest.FMQM_Late.over = "yes";
			DialogExit();
			InterfaceStates.Buttons.Save.enable = false;
			chrDisableReloadToLocation = true;
			pchar.GenQuest.FrameLockEsc = true;
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], true);
			pchar.questTemp.FMQM = "remove_oil";
			pchar.questTemp.FMQM.Oil = "true";
			pchar.questTemp.FMQM.Qty = GetSquadronGoods(pchar, GOOD_OIL);
			DoQuestFunctionDelay("FMQM_WaitTime", 1.0);
			RemoveCharacterGoods(pchar, GOOD_OIL, GetSquadronGoods(pchar, GOOD_OIL));
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}


