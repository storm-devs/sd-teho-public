// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Какие вопросы?", "Что вам угодно?"), "Совсем недавно вы пытались задать мне вопрос...", "У себя на верфи, а и вообще в городе, я таких однообразно любознательных не видал.",
                          "Ну что за вопросы? Мое дело - корабли строить, давайте этим и займемся.", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Я "+ GetSexPhrase("передумал","передумала") +"...", "Сейчас мне не о чем говорить."), "Хм, что-то с памятью моей стало...",
                      "Хм, однако...", "Давайте...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			if (pchar.questTemp.Slavetrader == "FindRatPortobello")
            {
                link.l1 = "Послушай, к тебе не обращался капер по имени Франсуа Гонтьер? Он недавно был в Порто Белло, я точно знаю.";
                link.l1.go = "Portobello_ratS_1";
            }
		break;
		
		case "Portobello_ratS_1":
			dialog.text = "Обращался. Он приобрел у меня корвет и вскоре вышел в море.";
			link.l1 = "Спасибо! А куда он отправился, ты часом не в курсе?";
			link.l1.go = "Portobello_ratS_2";
		break;
			
		case "Portobello_ratS_2":
			dialog.text = "Нет, "+ GetSexPhrase("дружище","подруга") +", без малейшего понятия. Я корабли чиню да продаю, а не отслеживаю, кто куда направляется. Мне до этого дела нет.";
			link.l1 = "Ну что же, будем узнавать...";
			link.l1.go = "exit";
			pchar.questTemp.Slavetrader = "FindRatPortobello_1";
			AddQuestRecord("Slavetrader", "21_2");
		break;
			
			
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

