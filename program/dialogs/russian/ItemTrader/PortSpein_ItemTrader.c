// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Какие вопросы?", "Что вам угодно, " + GetAddress_Form(NPChar) + "?"), "Опять вопросы, " + GetAddress_Form(NPChar) + "...", "Вопросы, вопросы... Может торговлей займёмся, " + GetAddress_Form(NPChar) + "?",
                          "Послушайте, ну сколько можно пустые разговоры вести?", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Нет вопросов...", "Сейчас мне не о чем говорить"), "Эх, опять...",
                      "Да, действительно лучше торговаться...", "Хм, извини, торговец...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			//Цена чахотки
			if (!CheckAttribute(npchar, "quest.Consumption") && CheckAttribute(pchar, "questTemp.Consumption.AskJuan"))
			{
				link.l1 = "Скажите, а имя 'Хуан' вам что-нибудь говорит?";
				link.l1.go = "Consumption";
			}
		break;
		
		//Цена чахотки
		case "Consumption":
			dialog.text = "Послушайте, не мешайте торговать... Что за идиотский вопрос?";
			link.l1 = "Ясно. Простите за беспокойство...";
			link.l1.go = "exit";
			npchar.quest.Consumption = "true";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

