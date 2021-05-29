// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Какие вопросы?", "Что вам угодно, " + GetAddress_Form(NPChar) + "?"), "Совсем недавно вы пытались задать мне вопрос, " + GetAddress_Form(NPChar) + "...", "В течение этого дня вы уже третий раз говорите о каком-то вопросе...",
                          "Опять вопросы будем задавать?", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Я "+ GetSexPhrase("передумал","передумала") +"...", "Сейчас мне не о чем говорить"), "Хм, что-то с памятью моей стало...",
                      "Да уж, действительно в третий раз...", "Да нет, какие вопросы...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			if (pchar.questTemp.Slavetrader == "FindRatJamaica")
            {
                link.l1 = "У вас в городе не появлялся такой Франсуа Гонтьер? Мне он очень нужен.";
                link.l1.go = "Jamaica_ratF_1";
            }
			// Addon 2016-1 Jason пиратская линейка
			if (CheckAttribute(pchar, "questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "silk_4")
            {
                link.l1 = "Послушай, дружище: корабел в Порт-Ройяле закупает для свого производства специальный шёлк... особый такой шёлк, слыхал наверное. И поговаривают, что продавец этого шёлка обретается в вашем поселении. Не подскажешь, что это за человечек? У меня к нему деловое предложение имеется.";
                link.l1.go = "mtraxx";
			}
			if (CheckAttribute(pchar, "questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "silk_5" && GetCharacterItem(pchar, "gold_dublon") >= 50)
            {
                link.l1 = "Я принес тебе пятьдесят дублонов. Держи и рассказывай.";
                link.l1.go = "mtraxx_4_1";
			}
		break;

		case "Jamaica_ratF_1":
			dialog.text = "Появлялся. Снимал у меня комнату несколько дней. Пренеприятнейший тип, я вам скажу. И кроме того, с манией преследования - вечно озирался и всего опасался, как параноик. Не тебя ли он так боялся?";
			link.l1 = "Нет, не меня. А вообще у каперов врагов много, сам знаешь. Так где его найти? Мы с ним договорились месте на дело пойти, а он как сквозь землю провалился!";
			link.l1.go = "Jamaica_ratF_2";
		break;
		
		case "Jamaica_ratF_2":
			dialog.text = "Ушёл в море на своём корабле. А куда - не знаю. Он мне не докладывал.";
			link.l1 = "Эх, жаль! Где ж я теперь его искать буду?";
			link.l1.go = "Jamaica_ratF_3";
		break;
		
		case "Jamaica_ratF_3":
			dialog.text = "Не знаю, "+ GetSexPhrase("дружище","мэм") +". Знал - подсказал бы.";
			link.l1 = "Ладно, все понятно. Пойду, у кого ещё поспрашиваю...";
			link.l1.go = "exit";
			AddQuestRecord("Slavetrader", "21_4");
			pchar.questTemp.Slavetrader = "FindRatJamaica_H";
		break;
		
		// Addon 2016-1 Jason пиратская линейка
		case "mtraxx":
            dialog.text = "Хех, если ты намекаешь на нашего купца, что магазин содержит, то совершенно напрасно, я точно знаю, что он корабельным шёлком не торгует. Контрабандистам у  нас тут нечего делать, чай, таможни не держим. Ну, а больше торговлей в Марун-Тауне никто не промышляет - тут народ несколько другой собрался, ха-ха! Так что брешут люди.";
			link.l1 = "Но кто-то же ему шёлк привозит в Порт-Ройял. Это факт. Есть у тебя какие-то мысли на счёт того, кто этим занимается?";
			link.l1.go = "mtraxx_1";
		break;
		
		case "mtraxx_1":
            dialog.text = "Возможно, контрабандисты в Порт-Ройяле? Или каперы пришлые? Перегружают тихонечко в бухте неприметной... Ха! Имеется у меня одно соображение, приятель. Есть один человечек из местных, который знает всё, что творится в наших прибрежных водах. Если уже и он тебе не подскажет - то значит и нет никакого продавца.";
			link.l1 = "Отлично! И как же зовут этого парня и где его искать?";
			link.l1.go = "mtraxx_2";
		break;
		
		case "mtraxx_2":
            dialog.text = "Кхм... Вот я пытаюсь вспомнить его имя, да всё никак не получается...";
			link.l1 = "Может, немного золотых освежат твою память?";
			link.l1.go = "mtraxx_3";
		break;
		
		case "mtraxx_3":
            dialog.text = "Пожалуй, да... Пять десятков дублонов наверняка вызовут у меня озарение.";
			if (GetCharacterItem(pchar, "gold_dublon") >= 50)
			{
				link.l1 = "Понимаю. Вот, держи.";
				link.l1.go = "mtraxx_4_1";
			}
			else
			{
				link.l1 = "Понимаю. Я еще вернусь...";
				link.l1.go = "mtraxx_4_2";
			}
		break;
		
		case "mtraxx_4_1":
			RemoveItems(pchar, "gold_dublon", 50);
			Log_Info("Вы отдали 50 дублонов");
			PlaySound("interface\important_item.wav");
            dialog.text = "Тебе нужен Билли Сипатый. Он считай всю жизнь прожил на Ямайке, в Порт-Ройяле каждую собаку знает. Бывший пират, много крови попортил англичанам, но уже как три года отошёл от дел после ранения и теперь промышляет рыбной ловлей, охотой на акул и сбором янтаря по бухточкам Ямайки. Со своего старого баркаса на сушу сходит видимо только затем, чтобы закупиться ромом и сухарями\nИщи его в море у берегов Ямайки. Он часто ходит вдоль северного побережья острова, до самой восточной точки, но искать на таком протяжении неприметный баркас - пустое занятие, лучше покарауль у юго-западной оконечности - в течение недели он должен появиться у мыса Негрил. Его скорлупа называется 'Летучая рыба'.";
			link.l1 = "Спасибо, приятель. Ты честно заработал своё золото.";
			link.l1.go = "mtraxx_5";
		break;
		
		case "mtraxx_5":
            dialog.text = "Удачи, дружище. Надеюсь, ты найдёшь то, что искал.";
			link.l1 = "...";
			link.l1.go = "mtraxx_6";
		break;
		
		case "mtraxx_4_2":
            DialogExit();
			AddQuestRecord("Roger_2", "6");
			pchar.questTemp.Mtraxx = "silk_5";
		break;
		
		case "mtraxx_6":
            DialogExit();
			AddQuestRecord("Roger_2", "7");
			pchar.questTemp.Mtraxx = "silk_6";
			pchar.quest.mtr_negril.win_condition.l1 = "Timer";
			pchar.quest.mtr_negril.win_condition.l1.date.hour  = 12+rand(12);
			pchar.quest.mtr_negril.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 2+rand(3));
			pchar.quest.mtr_negril.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 2+rand(3));
			pchar.quest.mtr_negril.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 2+rand(3));
			pchar.quest.mtr_negril.function = "Mtraxx_CreateBilly";
			SetFunctionTimerCondition("Mtraxx_BillySeaTimeOver", 0, 0, 7, false);
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
