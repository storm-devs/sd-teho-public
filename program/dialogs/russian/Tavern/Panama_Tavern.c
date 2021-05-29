// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat("Все сплетни города "+ GetCityName(npchar.city) +" к вашим услугам. Что бы вы хотели узнать?",
                          "Мы только что поднимали эту тему. Вы, вероятно, запамятовали...", "Сегодня вы уже третий раз говорите о каком-то вопросе...",
                          "Что ты "+ GetSexPhrase("заладил","заладила") +" как попугай одно и то же...", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Знаешь, " + NPChar.name + ", как-нибудь в следующий раз.", "Точно, "+ GetSexPhrase("забыл","забыла") +" что-то...",
                      "Да уж, действительно в третий раз...", "Да уж...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			if (pchar.questTemp.Slavetrader == "FindRatPanama")
            {
                link.l1 = "Послушай, говорят, у вас в городе был капер - Франсуа Гонтьер. Не знаешь, где мне его можно найти?";
                link.l1.go = "Panama_rat_1";
            }
			// Addon-2016 Jason ФМК-Гваделупа
			if (CheckAttribute(pchar, "questTemp.FMQG") && pchar.questTemp.FMQG == "headhunter_panama")
            {
                link.l1 = "Послушай, я ищу человека по имени Бертран Пинетт, не слыхал о таком? Он недавно прибыл в Панаму. Солидный такой господин, в парике кручёном. Может, заходил к тебе...";
                link.l1.go = "FMQG";
            }
		break;

		//-->работорговец
		case "Panama_rat_1":
			dialog.text = NPCStringReactionRepeat("Да, был у нас в городе этот тип. Все по тёмным углам прятался... Потом к нему приехали какие-то дружки, на вид - форменные головорезы, и он с ушёл из города.", "Ты уже "+ GetSexPhrase("спрашивал","спрашивала") +" об этом, я тебе ответил.", "Я же говорю тебе, ты уже "+ GetSexPhrase("спрашивал","спрашивала") +" об этом Гонтьере.", "Послушай, отойди и не мешай! Совсем что ли крыша поехала?", "block", 0, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("А куда ушёл, не знаешь?", "Хм, ну да...", "Да, точно, "+ GetSexPhrase("спрашивал","спрашивала") +"...", "Извини, " + npchar.name + "...", npchar, Dialog.CurrentNode);
			link.l1.go = "Panama_rat_2";
		break;
		
		case "Panama_rat_2":
			dialog.text = "Ну, пешком отсюда только одна дорога - в Порто Белло. А он пешком и пошел. Так что ищи его там.";
			link.l1 = "Спасибо, ты мне здорово помог!";
			link.l1.go = "exit";
			pchar.questTemp.Slavetrader = "FindRatPortobello";
			AddQuestRecord("Slavetrader", "21_1");
		break;
		//<--работорговец
		
		// Addon-2016 Jason ФМК-Гваделупа
		case "FMQG":
			dialog.text = "Бертран Пинетт? Француз? Первый раз слышу. Нет, приятель, французов у нас в последнее время не наблюдалось.";
			link.l1 = "Вот незадача... Точно не видал? Он друг одного важного идальго, дона Карлоса де Мильяра. Они вместе должны были приехать.";
			link.l1.go = "FMQG_1";
		break;
		
		case "FMQG_1":
			dialog.text = "Сеньора де Мильяра? Сей идальго Панаму навещал с год назад, на военном построении. А так дон Карлос де Мильяр живёт в Порто-Белло. Большой друг тамошнего губернатора.";
			link.l1 = "Ясно. Значит, я напрасно проделал путь через джугнли. Ладно, спасибо и на том, приятель.";
			link.l1.go = "FMQG_2";
		break;
		
		case "FMQG_2":
			DialogExit();
			pchar.questTemp.FMQG = "headhunter_portobello";
			AddQuestRecord("FMQ_Guadeloupe", "8");
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

