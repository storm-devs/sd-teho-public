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
			//Jason, Сага, Тени прошлого
			if (CheckAttribute(PChar, "questTemp.Saga.Shadows") && pchar.questTemp.Saga.Shadows == "sentjons")
			{
				link.l1 = "Я разыскиваю Раймонда Бейкера, бывшего палача. Не знаешь, жив ли он, и как мне его найти?";
				link.l1.go = "baker";
			}
			//Jason, суп из черепахи
			if (CheckAttribute(PChar, "questTemp.Terrapin") && pchar.questTemp.Terrapin == "baster" && !CheckAttribute(npchar, "quest.terrapin"))
			{
				link.l1 = "Я ищу господина Джонса. Не поможешь в розысках, приятель?";
				link.l1.go = "terrapin";
			}
			// Страж Истины
			if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "merdok")
			{
				link.l1 = "Послушай, не появлялся ли у вас в городе ученый-алхимик, лекарь? Он итальянец, лет тридцати, зовут Джино Гвинейли. Не слыхал о таком?";
				link.l1.go = "guardoftruth";
			}
		break;
		
		//Сага, Тени прошлого
		case "baker":
			dialog.text = "Наш толстяк стал популярнее полковника Фокса! Жив он, страдалец. Вот только в городе его сейчас нет. После того, как Раймонд узнал, что им интересуются серьёзные люди вроде вас, он в спешке продал за бесценок свою лачугу и тю-тю.";
			link.l1 = "Куда тю-тю?";
			link.l1.go = "baker_1";
		break;
		
		case "baker_1":
			dialog.text = "А кто ж его знает? Завербовался на первое попавшееся судно корабельным врачом. Только вот судно это сегодня вернулось, а Бейкера сошедшим на берег никто не видел.";
			link.l1 = "Как мне найти капитана?";
			link.l1.go = "baker_2";
		break;
		
		case "baker_2":
			dialog.text = "А чего его искать? Он уже наверняка напился по обыкновению у себя в каюте. Его корыто называется 'Плешивая Мэгги'. Каков капитан - такое и название...";
			link.l1 = "Спасибо за помощь, дружище!";
			link.l1.go = "baker_3";
		break;
		
		case "baker_3":
			DialogExit();
			AddQuestRecord("Shadows", "2");
			pchar.questTemp.Saga.Shadows = "baldmaggy";
			pchar.quest.Saga_ShadowsMaggy.win_condition.l1 = "location";
			pchar.quest.Saga_ShadowsMaggy.win_condition.l1.location = "Antigua";
			pchar.quest.Saga_ShadowsMaggy.function = "Saga_SetBaldMaggy";
		break;
		
		//суп из черепахи
		case "terrapin":
			dialog.text = "Господина Джонса? Ну ты загнул, парень. Господинов Джонсов я что-то не припомню, а просто Джонсов - стряпчих, чернорабочих, солдат - тут как собак нерезаных. Кто именно тебе нужен, скажи конкретнее?";
			link.l1 = "У него есть взрослая сестра Молли. Говорят, редкая красавица.";
			link.l1.go = "terrapin_1";
		break;
		
		case "terrapin_1":
			dialog.text = "Нет. Не припомню никого такого. Извини, приятель...";
			link.l1 = "Ладно, на нет - и суда нет...";
			link.l1.go = "exit";
			npchar.quest.terrapin = "true";
		break;
		
		case "guardoftruth":
			dialog.text = "Нет, не слыхал. Да у нас всего один алхимик в городе, аптекарь Джон Мердок. Микстуры у него знатные - от любых хворей исцеляют.";
			link.l1 = "Как думаешь, он сам готовит эти микстуры?";
			link.l1.go = "guardoftruth_1";
		break;
		
		case "guardoftruth_1":
			dialog.text = "Хороший вопрос. Я сам себе его иногда задаю - Джон совсем не похож на человека, привыкшего к мензуркам, травам и порошкам. У него замашки бывшего солдата, наёмника... это ближе к истине.";
			link.l1 = "Ну, переквалифицировался человек...";
			link.l1.go = "guardoftruth_2";
		break;
		
		case "guardoftruth_2":
			dialog.text = "Возможно, что и так. Но вот что я ещё точно знаю - живет у него на втором этаже кто-то. Окно постоянно занавешено. Даже когда Джон внизу, из этого окна доносится звон, как от стеклянных пузырьков или бутылок, тянет запахом варящихся трав, а по ночам не гаснет свет. Вот и подозреваю я, что обитатель этой комнаты и готовит лекарства Джону на продажу.";
			link.l1 = "Хм. Интересное наблюдение. Спасибо, дружище!";
			link.l1.go = "exit";
			pchar.questTemp.Guardoftruth = "merdok1";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}