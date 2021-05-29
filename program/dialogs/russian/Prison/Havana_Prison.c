// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
 	switch(Dialog.CurrentNode)
	{
        case "quests":
            dialog.text = "Говорите, я слушаю.";
			link.l1 = "Я "+ GetSexPhrase("ошибся","ошиблась") +". Прощайте.";
			link.l1.go = "Exit";
			// Addon 2016-1 Jason пиратская линейка
			if (CheckAttribute(pchar, "questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "jewelry_4")
			{
				link.l1 = "Офицер, я узнал, что у вас в тюрьме содержится арестованный офицер с судна 'Кантавро'. Это так?";
                link.l1.go = "Mtraxx";
			}
			if (CheckAttribute(pchar, "questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "jewelry_8")
			{
				link.l1 = "Я снова по поводу дона Лопе, офицер. Приказ о его освобождении уже поступил?";
                link.l1.go = "Mtraxx_5";
			}
		break;
		
		// Addon 2016-1 Jason пиратская линейка
		case "Mtraxx":
            dialog.text = "Офицер со шхуны 'Кантавро'? Дон Лопе Монторо? Да, он содержится у нас под стражей. А вам-то что за дело?";
			link.l1 = "Я хотел попросить вас разрешить мне повидаться с ним.";
			link.l1.go = "Mtraxx_1";
		break;
		
		case "Mtraxx_1":
            dialog.text = "Простите, но на каком основании?";
			link.l1 = "На основании личной просьбы. Мы с Лопе встречались еще в Европе, и я был поражен новостью о том, что его упекли за решетку, и о том, какие слухи распространяют о нем в городе. Я хочу с ним побеседовать.";
			link.l1.go = "Mtraxx_2";
		break;
		
		case "Mtraxx_2":
            dialog.text = "Кхм...";
			link.l1 = "Офицер, может, я смог бы как-то... отблагодарить вас за этот визит?";
			link.l1.go = "Mtraxx_3";
		break;
		
		case "Mtraxx_3":
            dialog.text = "Не надо никаких подношений. Я разрешаю вам пройти к дону Монторо. Ступайте, стража вас пропустит.";
			link.l1 = "Спасибо!";
			link.l1.go = "Mtraxx_4";
		break;
		
		case "Mtraxx_4":
			DialogExit();
            pchar.questTemp.jailCanMove = true;
			pchar.questTemp.Mtraxx = "jewelry_5";
		break;
		
		case "Mtraxx_5":
            dialog.text = "Действительно, мне предписано передать дона Лопе Монторо в руки коменданта форта. Видимо, недельки-другой гаупвахты ему все же не избежать. Если хотите - можете пройти к нему, он еще здесь.";
			link.l1 = "Спасибо, офицер, именно это я и хочу сделать.";
			link.l1.go = "Mtraxx_6";
		break;
		
		case "Mtraxx_6":
            DialogExit();
            pchar.questTemp.jailCanMove = true;
			pchar.questTemp.Mtraxx = "jewelry_9";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
