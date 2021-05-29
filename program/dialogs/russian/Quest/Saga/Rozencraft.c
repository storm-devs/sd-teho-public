// Михаэль Розенкрафт - голландский капитан, квестовый покупатель бакаута
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int iTemp;
	string sTemp;
	
	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "Вы что-то хотели?";
			link.l1 = "Да нет, ничего.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		case "rozencraft":
			if (pchar.questTemp.Saga.Oyster == "cantalk")
			{
				dialog.text = "Хм... А где Моллиган? Он что, не соизволил сам ко мне явиться?";
				link.l1 = "Наш бедолага Поль лежит с приступом лихорадки. Ему сейчас не до торговли. Я за него.";
				link.l1.go = "rozencraft_1";
			}
			else
			{
				dialog.text = "Что вам угодно, сударь?";
				link.l1 = "Я полагаю, это вы ждете партию бакаута для покупки?";
				link.l1.go = "rozencraft_no";
			}
		break;
		
		case "rozencraft_no":
			dialog.text = "Кто вам сказал подобную чушь, сударь? Я ничего и никого не жду. Мое судно выполняет задание губернатора Виллемстада по патрулированию здешних вод - мы разыскиваем одного пирата. Так что извольте покинуть палубу моего судна, вы, вероятно, с кем-то меня спутали.";
			link.l1 = "Гм.. Ясно. Извините за беспокойство.";
			link.l1.go = "rozencraft_no_1";
		break;
		
		case "rozencraft_no_1":
			DialogExit();
			AddQuestRecord("Testament", "8");
			NextDiag.CurrentNode = "rozencraft_no_repeat";
		break;
		
		case "rozencraft_no_repeat":
			dialog.text = "Мы все обсудили, сударь, разве нет?";
			link.l1 = "Да, да. Я уже отправляюсь на свой корабль.";
			link.l1.go = "exit";
			NextDiag.TempNode = "rozencraft_no_repeat";
		break;
		
		case "rozencraft_1":
			dialog.text = "А ты сам-то кто?";
			link.l1 = "Какая тебе разница, с кем иметь дело? Я привез бакаут на продажу. Сколько ты за него заплатишь?";
			link.l1.go = "rozencraft_2";
		break;
		
		case "rozencraft_2":
			dialog.text = "Согласно уговору - по сорок золотых за штуку.";
			link.l1 = "Хм...";
			link.l1.go = "rozencraft_3";
		break;
		
		case "rozencraft_3":
			npchar.quest.bakaut = GetSquadronGoods(pchar, GOOD_SANDAL);
			dialog.text = "Приятель, мы так договаривались с Моллиганом. Это хорошая цена, выше ты не получишь. Так что не надо здесь вести себя, как в купеческой лавке. Сколько у тебя бакаута?";
			link.l1 = ""+FindRussianQtyString(sti(npchar.quest.bakaut))+".";
			link.l1.go = "rozencraft_4";
		break;
		
		case "rozencraft_4":
			iTemp = sti(npchar.quest.bakaut);
			if(iTemp >= 90)
			{
				dialog.text = "Отлично. Это даже больше, чем я ожидал. Вот, держи золото. Если разживешься еще бакаутом - приходи в таверну Синт-Маартена и поговори... сам понимаешь с кем. Он сведет тебя со мной. Вижу, с тобой можно вести дела, и получше, чем с этим недоноском Моллиганом.";
				link.l1 = "Хорошо. Считай, что мы договорились.";
				link.l1.go = "rozencraft_5";
				pchar.GenQuest.Bakaut = "true"; // генератор сбыта бакаута
				break;
			}
			if(iTemp >= 70 && iTemp < 90)
			{
				dialog.text = "Хорошо. Вот, держи золото. Если разживешься еще бакаутом - приходи в таверну Филипсбурга и поговори... сам понимаешь с кем. Он сведет тебя со мной. Вижу, с тобой можно вести дела, и не хуже, чем с этим недоноском Моллиганом.";
				link.l1 = "Хорошо. Считай, что мы договорились.";
				link.l1.go = "rozencraft_5";
				pchar.GenQuest.Bakaut = "true"; // генератор сбыта бакаута
				break;
			}
			if(iTemp >= 40 && iTemp < 70)
			{
				dialog.text = "Гм... Я рассчитывал на большее. Ладно. Вот, держи золото. И передай Моллигану, чтобы в следующий раз партия была не меньше 100 штук.";
				link.l1 = "Хорошо. Обязательно передам!";
				link.l1.go = "rozencraft_5";
				break;
			}
			dialog.text = "Ты что, смеешься? Мы же договаривались с Моллиганом, что партия должна быть не меньше пятидесяти штук! Проваливай, и не появляйся, пока у тебя в трюмах не будет нужного количества.";
			link.l1 = "Хорошо-хорошо, не кипятись.";
			link.l1.go = "rozencraft_5";
		break;
		
		case "rozencraft_5":
			DialogExit();
			npchar.DontDeskTalk = true; // чтоб не доставал, в генераторе - снимаем
			iTemp = sti(npchar.quest.bakaut);
			if (iTemp < 40) DeleteAttribute(npchar, "quest.bakaut");
			else 
			{
				TakeNItems(pchar, "gold_dublon", iTemp*40);
				RemoveCharacterGoods(pchar, GOOD_SANDAL, iTemp);
				// считаем, сколько мы должны Свенсону
				int ibak = makeint((iTemp*40-1500)/2);
				sld = characterFromId("Svenson");
				sld.quest.bakaut_sum = ibak; // доля Яна
				AddQuestRecord("Testament", "9");
				AddQuestUserData("Testament", "sSum", iTemp*40);
				AddQuestUserData("Testament", "sSum1", ibak);
				if (CheckAttribute(pchar, "GenQuest.Bakaut")) AddQuestUserData("Testament", "sText", "Кроме того, если я еще добуду бакаут - я смогу сбыть эту ценную древесину Михаэлю Розенкрафту, договорившись через его человека в таверне Филипсбурга.");
				pchar.questTemp.Saga = "removebakaut";
				// корабль Розенкрафта сохраняем, в АИ на него будет стоять проверка на попадание
				pchar.quest.Saga_Rozencraft_GetOut.over = "yes"; //снять прерывание
				pchar.quest.Saga_Rozencraft_AfterBattle.over = "yes"; //снять прерывание
				// ставим новое прерывание на потопление Розенкрафта
				pchar.quest.Bakaut_Rozencraft_Die.win_condition.l1 = "Group_Death";
				pchar.quest.Bakaut_Rozencraft_Die.win_condition.l1.group = "Rozencraft_Group";
				pchar.quest.Bakaut_Rozencraft_Die.function = "Bakaut_RozencraftDie";
				pchar.quest.Bakaut_Rozencraft_Remove.win_condition.l1 = "MapEnter";
				pchar.quest.Bakaut_Rozencraft_Remove.function = "Bakaut_RozencraftRemove";
			}
			NextDiag.CurrentNode = "rozencraft_no_repeat";
		break;
		
	// ------------------------------------генератор сбыта бакаута-----------------------------------------------
		case "bakaut":
			dialog.text = "А, старый знакомый! Привез бакаут на продажу?";
			link.l1 = "Именно так, Михаэль. Займемся торговлей?";
			link.l1.go = "bakaut_0";
		break;
		
		case "bakaut_0":
			dialog.text = "Сколько у тебя товара? Мне нужна партия не меньше "+FindRussianQtyString(sti(pchar.GenQuest.Bakaut.Value))+".";
			if (GetSquadronGoods(pchar, GOOD_SANDAL) >= sti(pchar.GenQuest.Bakaut.Value))
			{
				link.l1 = "Я в курсе. У меня в трюмах "+FindRussianQtyString(GetSquadronGoods(pchar, GOOD_SANDAL))+" так нужного тебе бакаута.";
				link.l1.go = "bakaut_1";
			}
			else
			{
				link.l1 = "Хм. Такого количества у меня, к сожалению, сейчас нет.";
				link.l1.go = "bakaut_no";
			}
		break;
		
		case "bakaut_no":
			if (!CheckAttribute(npchar, "quest.bakaut_angry"))
			{
				dialog.text = "Черт возьми, тебя что, не предупредили? Или крысы сжевали древесину? Мне нужно "+FindRussianQtyString(sti(pchar.GenQuest.Bakaut.Value))+", и ни единицей меньше. Привози в следующий раз столько, сколько тебе скажет мой агент. Надеюсь, больше ты меня не разочаруешь, а то придется отказаться от твоих услуг.";
				link.l1 = "Хорошо, минхер, впредь я буду более внимателен.";
				link.l1.go = "bakaut_no_1";
			}
			else
			{
				if (sti(npchar.quest.bakaut_angry) == 1)
				{
					dialog.text = "Ты второй раз меня подводишь. Мне это очень не нравится. Имей в виду: еще раз не выполнишь условия сделки - более я с тобой дел вести не буду.";
					link.l1 = "Проклятые крысы испортили товар!.. Больше накладок не будет, Михаэль, я обещаю.";
					link.l1.go = "bakaut_no_1";
				}
				else
				{
					dialog.text = "Вот теперь мое терпение действительно лопнуло! Я более не желаю вести с тобой никаких дел. Можешь убираться на все четыре стороны и забыть про меня.";
					link.l1 = "Но минхер...";
					link.l1.go = "bakaut_no_2";
				}
			}
			npchar.DontDeskTalk = true;
			pchar.quest.Bakaut_Rozencraft_Find.over = "yes"; //снять прерывание
		break;
		
		case "bakaut_no_1":
			DialogExit();
			NextDiag.CurrentNode = "rozencraft_no_repeat";
			if (!CheckAttribute(npchar, "quest.bakaut_angry")) npchar.quest.bakaut_angry = 1;
			else npchar.quest.bakaut_angry = sti(npchar.quest.bakaut_angry)+1;
			pchar.quest.Bakaut_Rozencraft_Reset.win_condition.l1 = "MapEnter";
			pchar.quest.Bakaut_Rozencraft_Reset.function = "Bakaut_RozencraftRemove";
			AddQuestRecord("Bakaut", "3");
			CloseQuestHeader("Bakaut");
		break;
		
		case "bakaut_no_2":
			DialogExit();
			NextDiag.CurrentNode = "rozencraft_no_repeat";
			pchar.quest.Bakaut_Rozencraft_Fail.win_condition.l1 = "MapEnter";
			pchar.quest.Bakaut_Rozencraft_Fail.function = "Bakaut_RozencraftDie";
			AddQuestRecord("Bakaut", "4");
			CloseQuestHeader("Bakaut");
		break;
		
		case "bakaut_1":
			iTemp = GetSquadronGoods(pchar, GOOD_SANDAL);
			if (iTemp > sti(pchar.GenQuest.Bakaut.Value)+20)
			{ // перебор
				dialog.text = "Ого! Приятель, ты извини, конечно, но я могу купить у тебя только "+FindRussianQtyString(sti(pchar.GenQuest.Bakaut.Value)+20)+" товара - больше у меня просто нет денег. Я рассчитывал на партию в "+FindRussianQtyString(sti(pchar.GenQuest.Bakaut.Value))+", по сорок дублонов...";
				link.l1 = "Хорошо. Забирай сейчас "+FindRussianQtyString(sti(pchar.GenQuest.Bakaut.Value)+20)+", а остальное продам в следующий раз.";
				link.l1.go = "bakaut_2";
				npchar.quest.bakaut = sti(pchar.GenQuest.Bakaut.Value)+20;
			}
			else
			{
				dialog.text = "Очень хорошо. Цена - как обычно, сорок дублонов за штуку.";
				link.l1 = "Нет возражений. Забирай свой товар.";
				link.l1.go = "bakaut_2";
				npchar.quest.bakaut = iTemp;
			}
		break;
		
		case "bakaut_2":
			LAi_Fade("", "");
			WaitDate("",0,0,0,1,10);
			dialog.text = "Приятно иметь с тобой дело. Решишь продать мне еще бакаута - ты знаешь, куда и к кому обращаться.";
			link.l1 = "Еще увидимся, сударь. Наше сотрудничество приносит мне неплохие барыши. До встречи!";
			link.l1.go = "bakaut_3";
		break;
		
		case "bakaut_3":
			DialogExit();
			iTemp = sti(npchar.quest.bakaut);
			TakeNItems(pchar, "gold_dublon", iTemp*40);
			RemoveCharacterGoods(pchar, GOOD_SANDAL, iTemp);
			npchar.DontDeskTalk = true;
			pchar.quest.Bakaut_Rozencraft_Find.over = "yes"; //снять прерывание
			pchar.quest.Bakaut_Rozencraft_Reset.win_condition.l1 = "MapEnter";
			pchar.quest.Bakaut_Rozencraft_Reset.function = "Bakaut_RozencraftRemove";
			NextDiag.CurrentNode = "rozencraft_no_repeat";
			AddQuestRecord("Bakaut", "2");
			AddQuestUserData("Bakaut", "sQty", iTemp);
			AddQuestUserData("Bakaut", "sDublon", iTemp*40);
			AddQuestUserData("Bakaut", "sDublon1", iTemp*40-iTemp*30);
			CloseQuestHeader("Bakaut");
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
	}
}