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
			if (pchar.questTemp.Slavetrader == "FindRatPortobello")
            {
                link.l1 = "Послушай, не видел ли ты капера по имени Франсуа Гонтьер? Он недавно был в вашем городе.";
                link.l1.go = "Portobello_rat_1";
            }			
			// карибские нравы
			if (CheckAttribute(pchar, "questTemp.Trial") && pchar.questTemp.Trial == "spy" && !CheckAttribute(npchar, "quest.trial"))
            {
                link.l1 = "Послушай, не подскажешь, где найти торговца по имени Хайме Силисио? Он вроде как к вам собирался...";
                link.l1.go = "trial";
            }
			// Addon-2016 Jason ФМК-Гваделупа
			if (CheckAttribute(pchar, "questTemp.FMQG") && pchar.questTemp.FMQG == "headhunter_portobello" && !CheckAttribute(npchar, "quest.FMQG"))
            {
                link.l1 = "Послушай, я ищу человека по имени Бертран Пинетт, не слыхал о таком? Он недавно прибыл в Порто-Белло. Солидный такой господин, торговец, в парике кручёном. Может, заходил к тебе...";
                link.l1.go = "FMQG";
            }
		break;
		
		case "Portobello_rat_1":
			dialog.text = NPCStringReactionRepeat("Нет, не знаю. В таверну он не заходил, да и в городе я его не видел.", "Ты уже "+ GetSexPhrase("спрашивал","спрашивала") +" об этом, я тебе ответил.", "Я же говорю тебе, ты уже "+ GetSexPhrase("спрашивал","спрашивала") +" об этом Гонтьере.", "Послушай, отойди и не мешай! Совсем что ли крыша поехала?", "block", 0, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Ну что же, будем искать.", "Хм, ну да...", "Да, точно, "+ GetSexPhrase("спрашивал","спрашивала") +"...", "Извини, " + npchar.name + "...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
		break;		

		case "trial":
			dialog.text = "Сеньор Хайме Силисио? О, этот досточтимый кабальеро очень известен в нашем городе, особенно в последние пару дней! Погодите минутку, я позову человека, который проводит вас к нему... сеньор Артуро! Тут по поводу Хайме Силисио!";
			link.l1 = "...";
			link.l1.go = "exit";
			npchar.quest.trial = true;
			AddDialogExitQuestFunction("Trial_TavernEnterSoldiers");
		break;
		
		// Addon-2016 Jason ФМК-Гваделупа
		case "FMQG":
			dialog.text = "Ничего не слышал об этом господине, приятель.";
			link.l1 = "Он знакомый дона Карлоса де Мильяра. Точно ничего не припомнишь?";
			link.l1.go = "FMQG_1";
		break;
		
		case "FMQG_1":
			dialog.text = "Нет. Так если они с доном де Мильяром друзья, иди на прием к губернатору и попроси о встрече с сеньором Карлосом. У него и справишься о своем торговце.";
			link.l1 = "Пожалуй, так и сделаю. Спасибо за совет!";
			link.l1.go = "FMQG_2";
		break;
		
		case "FMQG_2":
			DialogExit();
			AddQuestRecord("FMQ_Guadeloupe", "9");
			npchar.quest.FMQG = true;
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

