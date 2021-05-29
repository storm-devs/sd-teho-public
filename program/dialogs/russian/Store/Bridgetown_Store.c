// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{

	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat("Спрашивай, чего ты хочешь?",
                          "Мы только что поднимали эту тему. Вы, вероятно, запамятовали...", "Сегодня вы уже третий раз говорите о каком-то вопросе...",
                          "Послушай, это магазин, здесь люди покупают что-то. Не отвлекай меня!", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Знаешь, " + NPChar.name + ", как-нибудь в следующий раз.", "Точно, "+ GetSexPhrase("забыл","забыла") +" что-то...",
                      "Да уж, действительно в третий раз...", "Гм, не буду...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			//Голландский гамбит
			if (CheckAttribute(pchar, "questTemp.HWIC.Eng") && pchar.questTemp.HWIC.Eng == "GotoBridgetown" && !CheckAttribute(npchar, "quest.HWICTalked"))
            {
                link.l1 = "Послушай, мне тут на ушко шепнули, что в Белизе скоро поднимутся цены на красное дерево и какао. Я как раз провернул выгодную сделку, набил мошну дублонами, хе-хе... Хочу у тебя приобрести большую партию этих товаров. Я могу рассчитывать на скидку?";
                link.l1.go = "StoreDone";
            }
			if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "barbados1")
			{
				link.l1 = "В вашу колонию недавно заходил галеон 'Восхитительный' под командованием капитана Гая Марше. Может, он закупал у вас припасы или товары для перепродажи? Не подскажете?";
                link.l1.go = "guardoftruth";
			}
		break;
		
		case "StoreDone":
			dialog.text = "Ну, мистер, если партия будет действительно большой - конечно, поторгуемся.";
			link.l1 = "Прекрасно! Говорят, на верфи со дня на день должен появиться в продаже новый флейт. Я подожду и куплю этот корабль, а то в мой бриг, хоть я и снял с него почти все орудия, вмещается маловато. Я ещё зайду!";
			link.l1.go = "exit";	
			npchar.quest.HWICTalked = "true";
			pchar.questTemp.HWIC.Eng.BridgeCounter = sti(pchar.questTemp.HWIC.Eng.BridgeCounter)+1;
			AddQuestRecord("Holl_Gambit", "2-11");
			if (sti(pchar.questTemp.HWIC.Eng.BridgeCounter) == 7) 
			{
				AddQuestRecord("Holl_Gambit", "2-6");
				pchar.questTemp.HWIC.Eng = "SeekVanBerg";
				pchar.quest.GotoBridgetownOver.over = "yes";//снять таймер
				pchar.quest.VanBergAttack_Check.win_condition.l1 = "MapEnter";
				pchar.quest.VanBergAttack_Check.function = "VanBergAttackCheck";
			}
		break;
		
		case "guardoftruth":
			dialog.text = "Ха! Я помню этого чудака! Он поверил слухам, что на Гваделупе в ближайшее время сильно возрастёт потребность в ванили, потому как якобы туда прибудет большой торговый караван, направляющийся в метрополию, и купцы будут закупать пряности\nЯ подобную чепуху слышу ежемесячно и уже не придаю ей никакого значения. Однако Марше отнёсся к этому крайне серьёзно. Он неделю стоял у меня, ожидая пока я соберу достаточное количество ванили, чтобы заполнить его трюмы\nОн, похоже, вложил в это безрассудство все свои сбережения. Мне его, право, жаль, но я никому не мешаю сходить с ума, если им так хочется.";
			link.l1 = "Значит, он сейчас может быть на Гваделупе?";
			link.l1.go = "guardoftruth_1";
		break;
		
		case "guardoftruth_1":
			dialog.text = "Скорее всего. Ибо ждать своих 'купцов' он будет до второго пришествия, а продать ваниль он сможет только в убыток. Если он не совсем дурак, то останется в Бас-Тере до тех пор, пока там не вырастет спрос на ваниль, либо пока не узнает достоверно, где она нужнее.";
			link.l1 = "Ясно. Спасибо, вы мне очень помогли!";
			link.l1.go = "guardoftruth_2";
		break;
		
		case "guardoftruth_2":
			DialogExit();
			AddQuestRecord("Guardoftruth", "14");
			pchar.questTemp.Guardoftruth = "guadeloupe";
			pchar.quest.GuardOT_guadeloupe.win_condition.l1 = "location";
			pchar.quest.GuardOT_guadeloupe.win_condition.l1.location = "guadeloupe";
			pchar.quest.GuardOT_guadeloupe.function = "GuardOT_CreateTwoShips";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);
}

