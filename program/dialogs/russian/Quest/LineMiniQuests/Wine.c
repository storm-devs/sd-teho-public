void ProcessDialogEvent()
{
	ref sld, NPChar;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "Явный баг. Сообщите Jason'у, как и при каких обстоятельствах его получили.";
			link.l1 = "Обязательно сообщу!";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
		case "Wine_fort":
			dialog.text = "Ну что, принес бутылочку?";
			if (CheckCharacterItem(pchar, "potionwine"))
			{
				link.l1 = "Да, держи, как договаривались. Мне оно обошлось в 700 монет, так что с тебя 1000 песо.";
				link.l1.go = "Wine_fort_1";
			}
			link.l2 = "Нет, я еще этим занимаюсь.";
			link.l2.go = "exit";
			NextDiag.TempNode = "Wine_fort";
		break;
	
		case "Wine_fort_1":
			AddMoneyToCharacter(pchar, 1000);
			RemoveItems(PChar, "potionwine", 1);
			dialog.text = "Аргх, спасибо тебе, дружище! Вот, держи свою тысячу, а эта бутылочка теперь моя, ха-ха-ха! Послушай, раз уже такое дело пошло, то у меня к тебе будет еще одна просьба\nНе мог бы ли ты раздобыть в городе еще вина, для меня и всех моих друзей, про запас? Мы тут недавно хорошо контрабандистов пощипали, так что деньги у нас имеются, хе-хе...";
			link.l1 = "Нет, дружище, извини, нет у меня времени.";
			link.l1.go = "Wine_fort_exit";
			link.l2 = "Хм, это интересно. Сколько бутылок вам надо?";
			link.l2.go = "Wine_fort_2";
		break;
	
	case "Wine_fort_exit":
			dialog.text = "Ну, как скажешь. Все равно спасибо за помощь!";
			link.l1 = "Бывай, служивый!";
			link.l1.go = "exit";
			sld = characterFromId(pchar.questTemp.Wine.id);	
			sld.lifeday = 0;
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload2", "none", "", "", "", -1);
			pchar.questTemp.Wine.fail = "true";
			CloseQuestHeader("Wine");
	break;
	
		case "Wine_fort_2":
			dialog.text = "Ну, при учете цены в тысячу за бутылку, штук шестьдесят бутылок мы сможем себе позволить, но не больше. Ну и меньше десяти тоже не приноси - несерьезно получится.";
			link.l1 = "Хорошо. Будет вам ваше вино.";
			link.l1.go = "Wine_fort_3";
		break;
	
		case "Wine_fort_3":
			dialog.text = "Вот и славно! Я надеюсь на вас, капитан. Только постарайтесь принести вино не позже, чем за неделю - потом мы уходим в плавание на патрульном судне, и меня здесь месяц-другой не будет.";
			link.l1 = "Понятно. Постараюсь побыстрее.";
			link.l1.go = "exit";
			pchar.questTemp.Wine.bottles = "true";
			npchar.lifeday = 7;
			AddQuestRecord("Wine", "1");
			AddQuestUserData("Wine", "sCity", XI_ConvertString("Colony"+pchar.questTemp.Wine.City+"Gen"));
			AddQuestUserData("Wine", "sName", pchar.questTemp.Wine.SName);
			SetFunctionTimerCondition("Soldier_wait", 0, 0, 7, false);
			NextDiag.TempNode = "Wine_fort_check";
		break;
	
		case "Wine_fort_check":
			dialog.text = "Ну, капитан, вы принесли вино?";
			if (sti(pchar.items.potionwine) >= 10)
			{
				link.l1 = "Да, принес.";
				link.l1.go = "Wine_take";
			}
			link.l2 = "Нет. Я еще этим занимаюсь.";
			link.l2.go = "exit";
			NextDiag.TempNode = "Wine_fort_check";
		break;
	
		case "Wine_take":
			pchar.questTemp.Wine.Qty = sti(pchar.items.potionwine);
			pchar.questTemp.Wine.Money = sti(pchar.questTemp.Wine.Qty)*1000;
			if (sti(pchar.items.potionwine) > 60)
			{
				dialog.text = "У-у, сколько тут у вас бутылок! Великолепно! Правда, как я уже говорил - денег у нас только на шестьдесят - больше нет, к сожалению. Держите ваши деньги, а шестьдесят бутылочек я забираю.";
				link.l1 = "Забирайте. Уверен, вы с друзьями неплохо отдохнете!";
				link.l1.go = "Wine_take_1";
				pchar.questTemp.Wine.Money = 60000;
				RemoveItems(PChar, "potionwine", 60);
			}
			else
			{
				dialog.text = "Так, давайте посмотрим... Вы принесли "+sti(pchar.questTemp.Wine.Qty)+" бутылок. Отлично! Я их забираю. Оплата - как и договаривались: " + FindRussianMoneyString(sti(pchar.questTemp.Wine.Money))".";
				link.l1 = "Держите ваше вино. Уверен, вы с друзьями неплохо отдохнете!";
				link.l1.go = "Wine_take_1";
				RemoveItems(PChar, "potionwine", sti(pchar.questTemp.Wine.Qty));
			}
		break;
	
		case "Wine_take_1":
			AddMoneyToCharacter(pchar, sti(pchar.questTemp.Wine.Money));
			dialog.text = "Благодарю вас от всей души, " + GetAddress_Form(NPChar) + "! А теперь мне пора идти. Всего доброго!";
			link.l1 = "Пока, служивый!";
			link.l1.go = "Wine_take_2";
		break;
	
		case "Wine_take_2":
			DialogExit();
			PlaySound("interface\important_item.wav");
			Log_Info ("Вы отдали вино");
			pchar.quest.Soldier_wait.over = "yes";//снять прерывание
			DeleteAttribute(pchar, "questTemp.Wine.City");
			sld = characterFromId(pchar.questTemp.Wine.id);
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload2", "none", "", "", "", -1);
			sld.lifeday = 0;
			CloseQuestHeader("Wine");
			AddCharacterExpToSkill(pchar, "Commerce", 150);//торговля
			AddCharacterExpToSkill(pchar, "Leadership", 50);//авторитет
			AddCharacterExpToSkill(pchar, "Fortune", 50);//везение
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
