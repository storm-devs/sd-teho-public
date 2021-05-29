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
			//Jason, Бремя гасконца
			if (CheckAttribute(PChar, "questTemp.Sharlie.Storehelper") && pchar.questTemp.Sharlie.Storehelper == "hire" && !CheckAttribute(npchar, "quest.storehelper"))
			{
				link.l1 = "Послушай, " + npchar.name + ", я к тебе по одному необычному делу. Мне нужно найти человека, который хотел бы тихой и спокойной жизни на берегу в качестве помощника торговца в магазин Сен-Пьера. Жалование хорошее, и крыша над головой обеспечена. Не можешь посоветовать, к кому обратиться?";
				link.l1.go = "storehelper";
			}
			if (CheckAttribute(PChar, "questTemp.Sharlie") && pchar.questTemp.Sharlie == "seabattle" && !CheckAttribute(npchar, "quest.seabattle") && pchar.location.from_sea == "LeFransua_port")
			{
				link.l1 = "Я по поводу бочонков с вином, которые ты собираешься погрузить на мой корабль для доставки на Гваделупу...";
				link.l1.go = "seabattle";
			}
			//Бремя гасконца
			//Jason, Португалец
			if (CheckAttribute(PChar, "questTemp.Portugal") && pchar.questTemp.Portugal == "PortugalLeFransua" && !CheckAttribute(npchar, "quest.portugal") && Pchar.location.from_sea == "LeFransua_port")
			{
				link.l1 = "Знаешь, " + npchar.name + ", я ищу одного своего друга. Он должен был приехать сюда, и ему нездоровилось. Возможно, ему помогали друзья...";
				link.l1.go = "Portugal";
			}
			//Португалец
		break;
		
		case "storehelper":
			dialog.text = "Хм... Есть тут у нас несколько человек, желающих сменить профессию моряка на жизнь сухопутной крысы. Я могу помочь тебе, но сразу говорю: не бесплатно.";
			link.l1 = "Хех! И сколько же ты хочешь?";
			link.l1.go = "storehelper_1";
			npchar.quest.storehelper = "true";
		break;
		
		case "storehelper_1":
			dialog.text = "Тысячу песо. И тебе вообще ничего не придется делать - через час желающие наняться будут у меня в таверне, и не один. Сможешь поговорить с ними и выбрать, кто приглянётся больше других.";
			if (sti(Pchar.money) >= 1000)
			{
				link.l1 = "Эх-х... Ладно, держи свою тысячу!";
				link.l1.go = "storehelper_2";
			}
			link.l2 = "Мне жаль, но у меня нет таких денег!";
			link.l2.go = "storehelper_exit";
		break;
		
		case "storehelper_2":
			AddMoneyToCharacter(pchar, -1000);
			dialog.text = "Не переживай так, приятель. Половина этой суммы вернется тебе от кандидата - я скажу, что такова оплата твоих услуг, хе-хе... Больше пятисот потребовать не получится. Заходи в мою таверну через час - к этому времени я уже приглашу нужных тебе людей.";
			link.l1 = "Хорошо. Я вернусь через час, " + npchar.name + ".";
			link.l1.go = "storehelper_3";
		break;
		
		case "storehelper_3":
			DialogExit();
			pchar.quest.storehelper1.win_condition.l1 = "Timer";
			pchar.quest.storehelper1.win_condition.l1.date.hour  = sti(GetTime() + 1);
			pchar.quest.storehelper1.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 0);
			pchar.quest.storehelper1.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 0);
			pchar.quest.storehelper1.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 0);
			pchar.quest.storehelper1.win_condition.l2 = "location";
			pchar.quest.storehelper1.win_condition.l2.location = "lefransua_tavern";
			pchar.quest.storehelper1.function = "Storehelper_hire";
		break;
		
		case "storehelper_exit":
			dialog.text = "Мне тоже жаль, приятель, что у тебя их нет. Но за спасибо такие дела не делаются, сам понимаешь. Так что...";
			link.l1 = "Понимаю. Но денег действительно нет. Ладно, бывай...";
			link.l1.go = "exit";
			pchar.quest.storehelper.over = "yes";
			DeleteAttribute(pchar, "questTemp.Sharlie.Storehelper");
			CloseQuestHeader("SharlieA");
		break;
		
		case "seabattle":
			dialog.text = "Ты это сейчас о чем, приятель? О каком вине ты говоришь?";
			link.l1 = "Меня прислал к тебе человек по имени Уолтер Катчер. Он сказал, что тебе нужен корабль для перевозки партии вина на Гваделупу, за десять тысяч песо. И что тебе нужен именно мой корабль для этой работы...";
			link.l1.go = "seabattle_1";
			npchar.quest.seabattle = "true";
		break;
		
		case "seabattle_1":
			dialog.text = "Послушай, дружище, я не торгую вином, и не нуждаюсь в твоих услугах, и никакого Уолтера Катчера знать не знаю.";
			link.l1 = "Вот так номер! Так значит, этот Катчер был вовсе не от тебя... Но к чему тогда вся эта комедия?";
			link.l1.go = "seabattle_2";
		break;
		
		case "seabattle_2":
			dialog.text = "Хех! Ну, это или какая-то ошибка, или глупая шутка, или...";
			link.l1 = "Что 'или'?";
			link.l1.go = "seabattle_3";
		break;
		
		case "seabattle_3":
			dialog.text = "А сам не догадываешься? Кому-то понадобилось заманить тебя в Ле Франсуа, а вот уже для чего - не знаю. На твоём месте я бы сейчас поспешил убраться отсюда, соблюдая всю возможную осторожность. Это дело дурно пахнет, приятель...";
			link.l1 = "Пожалуй, ты прав. Мне рожа этого Катчера сразу не понравилась. Ладно, последую твоему совету. Бывай, Чезаре!";
			link.l1.go = "seabattle_4";
		break;
		
		case "seabattle_4":
			DialogExit();
			AddQuestRecord("Sharlie", "16");
			pchar.quest.seabattle.win_condition.l1 = "location";
			pchar.quest.seabattle.win_condition.l1.location = "Martinique";
			pchar.quest.seabattle.function = "SharlieSeabattle_ship";
		break;
		
		case "Portugal":
			dialog.text = "Да, приехал ваш друг, капитан. Ещё вчера приехал, и снял комнату наверху. И дружки его здесь, хе-хе... вон сидят, у них и спросите!";
			link.l1 = "...";
			link.l1.go = "Portugal_1";
		break;
		
		case "Portugal_1":
			DialogExit();
			AddDialogExitQuestFunction("Portugal_enterPirates");
			npchar.quest.portugal = "true";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

