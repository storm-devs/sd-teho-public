// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{

	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat("Спрашивай, чего ты хочешь?",
                          "Мы только что поднимали эту тему. Вы, вероятно, запамятовали...", "Сегодня вы уже третий раз говорите о каком-то вопросе...",
                          "Послушай, это магазин, здесь люди покупают что-то. Не отвлекай меня!", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Знаешь, " + NPChar.name + ", как-нибудь в следующий раз.", "Точно, "+ GetSexPhrase("забыл","забыла") +" что-то...",
                      "Да уж, действительно в третий раз...", "Гм, не буду...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			//Jason --> Португалец
			if (CheckAttribute(pchar, "questTemp.Portugal") && pchar.questTemp.Portugal == "Findcloves" && !CheckAttribute(npchar, "quest.Portugal"))
			{
   				link.l1 = "Послушайте, мне нужна хорошая одежда. Подороже, чтобы дворянину было не стыдно облачиться. У вас есть что-то подобное?";
				link.l1.go = "Portugal_cloves";
			}
			//<-- Португалец
			if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "maarten")
			{
				link.l1 = "К вам не так давно привозил груз кож галеон из Тортуги под названием 'Восхитительный'. Припоминаете?";
                link.l1.go = "guardoftruth";
			}
		break;
		
		//Jason --> Португалец
		case "Portugal_cloves":
			dialog.text = "Дворянская одежда? Есть такая, лежит у меня полный комплект - штаны, колет, шёлковая рубашка и сапоги. Стоит 20 000 песо - одежда очень добротная, удобная и имеет великолепный внешний вид, так что за меньшую сумму не отдам.";
			if (sti(pchar.money) >= 20000)
			{
				link.l1 = "Отлично! Давай её сюда.";
				link.l1.go = "Portugal_cloves_1";
			}
			link.l2 = "Гм... Сейчас у меня нет нужной суммы.";
			link.l2.go = "Portugal_cloves_nomoney";
		break;
		
		case "Portugal_cloves_nomoney":
			dialog.text = "Тогда заходите, когда деньги будут.";
			link.l1 = "Хорошо. Я скоро вернусь!";
			link.l1.go = "exit";
		break;
		
		case "Portugal_cloves_1":
			AddMoneyToCharacter(pchar, -20000);
			GiveItem2Character(pchar, "suit_1");
			Log_Info("Вы получили дорогую одежду");
			PlaySound("interface\important_item.wav");
			dialog.text = "Пожалуйста, получите.";
			link.l1 = "Спасибо!";
			link.l1.go = "exit";
			npchar.quest.Portugal = "true";
			sld = characterFromId("PortugalDoctor");
			sld.dialog.currentnode = "Portugal_doctor_4";
		break;
		//<-- Португалец
		case "guardoftruth":
			dialog.text = "Ну да. Прибыл в срок, выгрузил товар, я с ним рассчитался, как положено. А что?";
			link.l1 = "Капитан этого корабля, Гай Марше, мой старинный знакомый. Вот я его и разыскиваю. Не подскажете, что он делал дальше? Может, вы предоставили ему очередной фрахт, или он упоминал, куда собирается отправиться?";
			link.l1.go = "guardoftruth_1";
		break;
		
		case "guardoftruth_1":
			dialog.text = "Ни то, ни другое. Фрахта я ему не предлагал, да и он сам не просил. Своими планами на будущее также не делился. Да и не помню я всех подробностей - знаете, сколько у меня народу за это время прошло? В общем, выгрузился он и ушёл, и больше ничего сказать не могу.";
			link.l1 = "Ясно. Ну, спасибо и на этом. Всего доброго!";
			link.l1.go = "guardoftruth_2";
		break;
		
		case "guardoftruth_2":
			DialogExit();
			AddQuestRecord("Guardoftruth", "11");
			pchar.questTemp.Guardoftruth = "maarten1";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);
}

