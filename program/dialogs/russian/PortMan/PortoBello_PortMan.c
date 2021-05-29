// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Какие вопросы?", "Что вам угодно, " + GetAddress_Form(NPChar) + "?"), "Совсем недавно вы пытались задать мне вопрос " + GetAddress_Form(NPChar) + "...", "В течение этого дня вы уже третий раз говорите о каком-то вопросе...",
                          "Послушайте, если вы не по делам порта, то не стоит меня вопросами донимать.", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Я передумал"+ GetSexPhrase("","а") +"...", "Сейчас мне не о чем говорить"), "Хм, что-то с памятью моей стало...",
                      "Да уж, действительно в третий раз...", "Извините, но портовые дела меня сейчас не интересуют.", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			if (pchar.questTemp.Slavetrader == "FindRatPortobello_1")
            {
                link.l1 = "Добрый день. Я бы хотел"+ GetSexPhrase("","а") +" узнать, куда отправился капитан Франсуа Гонтьер на своем корвете. У меня для него важное поручение.";
                link.l1.go = "Portobello_ratP_1";
            }
		break;

		case "Portobello_ratP_1":
			dialog.text = "Важное дело, говорите? Ну, раз так, давайте посмотрим. Так... Франсуа Гонтьер, корвет '" + pchar.questTemp.Slavetrader.ShipName + "'... Судя по записям, сеньор Гонтьер направился на Ямайку.";
			link.l1 = "Спасибо! Вы мне очень помогли!";
			link.l1.go = "exit";
			pchar.questTemp.Slavetrader = "FindRatJamaica";
			AddQuestRecord("Slavetrader", "21_3");
			AddQuestUserData("Slavetrader", "sShip", pchar.questTemp.Slavetrader.ShipName);
		break;
		

	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}


