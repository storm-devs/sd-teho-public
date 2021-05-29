// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat("Все сплетни города "+ GetCityName(npchar.city) +" к вашим услугам. Что бы вы хотели узнать?",
                          "Мы только что поднимали это тему. Вы, вероятно, запамятовали...", "Сегодня вы уже третий раз говорите о каком-то вопросе...",
                          "Что ты заладил"+ GetSexPhrase("","а") +" как попугай одно и то же...", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Знаешь, " + NPChar.name + ", как-нибудь в следующий раз.", "Точно, "+ GetSexPhrase("забыл","забыла") +" что-то...",
                      "Да уж, действительно в третий раз...", "Да уж...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			// Страж Истины
			if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "merdok" && !CheckAttribute(npchar, "quest.jino"))
			{
				link.l1 = "Послушай, не появлялся ли у вас в городе ученый-алхимик, лекарь? Он итальянец, лет тридцати, зовут Джино Гвинейли. Не слыхал о таком?";
				link.l1.go = "guardoftruth";
			}
			// Калеуче
			if (CheckAttribute(pchar, "questTemp.Caleuche") && pchar.questTemp.Caleuche == "hunting" && !CheckAttribute(npchar, "quest.Caleuche"))
			{
				link.l1 = "Послушай, мне нужен охотник по имени Фергус Хупер. Мне сказали, что он в Белизе живет. Где я могу его найти?";
				link.l1.go = "caleuche";
			}
		break;
		
		case "guardoftruth":
			dialog.text = LinkRandPhrase("Нет, не слыхал. Есть у нас травники, и лекари - но ни одного с таким именем.","Впервые такое чудное имя слышу. Нет, таких у нас отродясь не водилось.","Да у нас и вовсе никаких алхимиков нет. Лекари есть, но ни одного с таким чудным именем.");
			link.l1 = "Ясно. Жаль. Буду искать дальше!";
			link.l1.go = "exit";
			npchar.quest.jino = "true";
		break;
		
		// Калеуче
		case "caleuche":
			dialog.text = "Фергус? Он у меня частенько бывает. Но сейчас его нет - ушел в сельву не позже, как вчера. Но ты не переживай, недели не пройдет, как он снова будет сидеть у меня за столиком, пить ром и пугать всех сказками о своих морских похождениях. Хотя охотник он знатный, не спорю. Никто лучше него не умеет ловить змей.";
			link.l1 = "Змей? Хм. Так когда мне наведаться к тебе, чтобы застать Фергуса?";
			link.l1.go = "caleuche_1";
		break;
		
		case "caleuche_1":
			dialog.text = "Ну, раньше чем через три дня его не жди. Потом захаживай. Только учти, что он блюдет режим дня, и никогда не приходит раньше шести вечера, и уходит спать не позже десяти.";
			link.l1 = "Как он выглядит? А то я ни разу его не видел.";
			link.l1.go = "caleuche_2";
		break;
		
		case "caleuche_2":
			dialog.text = "Бородатый такой, немолод уже, ходит всегда в коричневом камзоле, шляпе и сапогах.";
			link.l1 = "Спасибо! Ты мне очень помог, дружище. До встречи!";
			link.l1.go = "caleuche_3";
		break;
		
		case "caleuche_3":
			DialogExit();
			AddQuestRecord("Caleuche", "8");
			int iTerms = sti(pchar.questTemp.Caleuche.Belizterms);
			SetFunctionTimerCondition("Caleuche_FergusCome", 0, 0, iTerms, false);
			npchar.quest.Caleuche = "true";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

