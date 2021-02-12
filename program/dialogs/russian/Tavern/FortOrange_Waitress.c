// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Вопросы, " + GetAddress_Form(NPChar) + "?", "Что вам угодно, " + GetAddress_Form(NPChar) + "?"), ""+ GetSexPhrase("Хм, уж не пристаете ли вы ко мне, " + GetAddress_Form(NPChar) + "? ","Опять со странными вопросами? Девушка, выпили бы вы рому, что ли...") +"", "В течение этого дня вы уже третий раз говорите о каком-то вопросе..."+ GetSexPhrase(" Это знаки внимания?","") +"",
                          "Опять вопросы будете задавать, " + GetAddress_Form(NPChar) + "?", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Я передумал"+ GetSexPhrase("","а") +"...", "Сейчас мне не о чем говорить"), "Да нет, что ты, красавица...",
                      "Никак нет, дорогуша, склероз...", "Да нет, какие вопросы...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			if (pchar.questTemp.Slavetrader == "FindRatJamaica_W")
            {
                link.l1 = "Послушай, дорогуша, говорят, ты близко общалась с моим приятелем Франсуа Гонтьером. Очень близко общалась...";
                link.l1.go = "Jamaica_ratW_1";
            }
			
			if (pchar.questTemp.Slavetrader == "FindRatJamaica_WP")
            {
				if (CheckCharacterItem(pchar, "jewelry43"))
				{
					link.l1 = "Я принес тебе твой кулон с самоцветами. Держи.";
					link.l1.go = "Jamaica_ratW_5";
				}
				else
				{
					link.l1 = "Да пока ничего. Ищу тебе кулон.";
					link.l1.go = "exit";
				}
            }
			
		break;
		
		case "Jamaica_ratW_1":
            dialog.text = "Да, общалась, и что с того? Я девушка незамужняя, с кем хочу - с тем и общаюсь. Франсуа очень видный моряк, не то, что наши местные проходимцы. Весь такой... ах! А какие подарки он мне делал!";
            link.l1 = "Стоп-стоп, хватит! Я знаю о достоинствах моего товарища, можешь мне их не расписывать. Мне все равно, что там между вами было - хоть женитесь. Мне нужно срочно его найти, понимаешь? Ты знаешь, куда он отправился?";
            link.l1.go = "Jamaica_ratW_2";
        break;
		
		case "Jamaica_ratW_2":
            dialog.text = "Хи-хи... Вы его "+ GetSexPhrase("приятель","приятельница, хи-хи") +", и не знаете, куда он отправился. Вот забавно!";
            link.l1 = "Ничего смешного, малышка. Мы договорились с ним встретиться на Ямайке, а дальше нас ждет совместный рейс... Если ты понимаешь, о чем я. Мне в одиночку не справиться, а он взял и свалил неизвестно куда!";
            link.l1.go = "Jamaica_ratW_3";
        break;
		
		case "Jamaica_ratW_3":
            dialog.text = "Понятно. Ну, раз вас ждет такой прибыльный рейс, и вы с Франсуа друзья... Я скажу вам, куда он направился, но не просто так.";
            link.l1 = "Хм... Сколько ты хочешь?";
            link.l1.go = "Jamaica_ratW_4";
        break;
		
		case "Jamaica_ratW_4":
            dialog.text = "Фу, "+ GetSexPhrase("как пошло","какая вы грубая, девушка") +". Денег мне не надо. Франсуа обещал подарить кулон с самоцветами, я уже и перед подружками расхвасталась, а он взял и смылся... Принесите мне кулон, и я скажу, куда он отправился.";
            link.l1 = "Ах ты плутовка! Хорошо, будет тебе кулон.";
            link.l1.go = "exit";
			AddQuestRecord("Slavetrader", "21_5");
			pchar.questTemp.Slavetrader = "FindRatJamaica_WP";
        break;
		
		case "Jamaica_ratW_5":
            dialog.text = "Ах, какая красота! Теперь все мои подруги лопнут от зависти!";
            link.l1 = "Передай им мои соболезнования. Теперь я жду ответа, куда направился Франсуа.";
            link.l1.go = "Jamaica_ratW_6";
			RemoveItems(PChar, "jewelry43", 1);
        break;
		
		case "Jamaica_ratW_6":
            dialog.text = "Да, конечно, "+ GetSexPhrase("минхер","госпожа") +". Франсуа взял курс на Кубу, в Гавану.";
            link.l1 = "Спасибо, дорогуша. Это все, что я хотел"+ GetSexPhrase("","а") +" знать.";
            link.l1.go = "exit";
			AddQuestRecord("Slavetrader", "21_6");
			pchar.questTemp.Slavetrader = "FindRatHavana";
        break;
		
		
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

