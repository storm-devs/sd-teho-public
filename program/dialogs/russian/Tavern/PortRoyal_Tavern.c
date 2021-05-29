// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat("Все сплетни города "+ GetCityName(npchar.city) +" к вашим услугам. Что бы вы хотели узнать?",
                          "Мы только что поднимали эту тему. Вы, вероятно, запамятовали...", "Сегодня вы уже третий раз говорите о каком-то вопросе...",
                          "Что ты "+ GetSexPhrase("заладил","заладила") +" как попугай одно и то же...", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Знаешь, " + NPChar.name + ", как-нибудь в следующий раз.", "Точно, забыл что-то...",
                      "Да уж, действительно в третий раз...", "Да уж...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			if (pchar.questTemp.Slavetrader == "FindRatJamaica")
            {
                link.l1 = "Ты не знаешь, где я могу найти Франсуа Гонтьера?";
                link.l1.go = "Jamaica_ratP_1";
            }
			// Страж Истины
			if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "merdok" && !CheckAttribute(npchar, "quest.jino"))
			{
				link.l1 = "Послушай, не появлялся ли у вас в городе ученый-алхимик, лекарь? Он итальянец, лет тридцати, зовут Джино Гвинейли. Не слыхал о таком?";
				link.l1.go = "guardoftruth";
			}
		break;

		case "Jamaica_ratP_1":
			dialog.text = NPCStringReactionRepeat("Без малейшего понятия. Я вообще впервые слышу это имя.", "Ты уже "+ GetSexPhrase("спрашивал","спрашивала") +" об этом, я тебе ответил.", "Я же говорю тебе, ты уже "+ GetSexPhrase("спрашивал","спрашивала") +" об этом Гонтьере.", "Послушай, отойди и не мешай! Совсем что ли крыша поехала?", "block", 0, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Ну что же, будем искать.", "Хм, ну да...", "Да, точно, "+ GetSexPhrase("спрашивал","спрашивала") +"...", "Извини, " + npchar.name + "...", npchar, Dialog.CurrentNode);
		break;
		
		case "guardoftruth":
			dialog.text = LinkRandPhrase("Нет, не слыхал. Есть у нас травники, и лекари, но ни одного с таким именем.","Впервые такое чудное имя слышу. Нет, таких у нас отродясь не водилось.","Да у нас и вовсе никаких алхимиков нет. Лекари есть, но ни одного с таким чудным именем.");
			link.l1 = "Ясно. Жаль. Буду искать дальше!";
			link.l1.go = "exit";
			npchar.quest.jino = "true";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

