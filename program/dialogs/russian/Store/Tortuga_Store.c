// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{

	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Какие вопросы?", "Что вам угодно?"), "Совсем недавно вы пытались задать мне вопрос...", "В магазине Тортуги таких вопросов не было давно...",
                          "Вопросы, вопросы, опять вопросы...", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Я передумал...", "Сейчас мне не о чем говорить"), "Хм, что-то с памятью моей стало...",
                      "Ну, не было - так не было.", "Во-о-о-просы, да...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "tortuga2")
			{
				link.l1 = "Послушай, мне нужно найти Гая Марше. Как мне сказали, он завязал с каперством и стал добропорядочным негоциантом, отбив у испанцев отличный галеон. Не закупал ли он у тебя каких товаров для негоции?";
                link.l1.go = "guardoftruth";
			}
		break;
		
		case "guardoftruth":
			dialog.text = "Гай Марше? Как же, как же, помню! Вот только ничего он не закупал, а предоставил свой корабль для фрахта. Мне как раз нужно было судно с объемным трюмом - большая партия сырых кож.";
			link.l1 = "И какой был пункт выгрузки?";
			link.l1.go = "guardoftruth_1";
		break;
		
		case "guardoftruth_1":
			dialog.text = "Филипсбург, Синт-Маартен.";
			link.l1 = "Ясно. Спасибо, ты мне очень помог!";
			link.l1.go = "guardoftruth_2";
		break;
		
		case "guardoftruth_2":
			dialog.text = "Всегда пожалуйста, капитан. Буду рад видеть вас в своем магазине хоть каждый день!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddQuestRecord("Guardoftruth", "10");
			pchar.questTemp.Guardoftruth = "maarten";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);
}

