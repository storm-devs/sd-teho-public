// посредник-дипломат кланов Джузеппе Фацио
#include "DIALOGS\russian\Rumours\Common_rumours.c"
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int iTemp;
	string sTemp;
	float locx, locy, locz;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	ProcessCommonDialogRumors(NPChar, Link, NextDiag);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "Здравствуйте-здравствуйте... Недавно на острове? Ваше лицо мне незнакомо. Позвольте представиться - Джузеппе Фацио, специалист по решению различного рода проблем на этом клочке суши среди моря.";
				link.l1 = TimeGreeting()+". Мое имя - "+GetFullName(pchar)+". Вы правы, я действительно здесь недавно. Простите за любопытство, а какие такие проблемы вы решаете?";
				link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "А, это снова вы, дорогой "+pchar.name+"! Что привело вас в мое скромное жилище?";
				if (CheckAttribute(pchar, "GenQuest.NarvalConflict") || CheckAttribute(pchar, "GenQuest.RivadosConflict") || CheckAttribute(pchar, "GenQuest.SharkConflict"))
				{
					link.l10 = "Фацио, у меня возник серьезный конфликт с одним из кланов. Мне нужно как-то решить эту проблему.";
					link.l10.go = "conflict";
				}
				// --> квестовые ветки
				if (CheckAttribute(pchar, "questTemp.Saga.SharkHunt") && pchar.questTemp.Saga.SharkHunt == "search_mush_3")
				{
					link.l4 = "Джузеппе, я разыскиваю человека по имени Адольф Барбье. Мне сказали, что вы недавно с ним беседовали за кружкой эля в таверне...";
					link.l4.go = "adolf";
				}
				if (CheckAttribute(pchar, "questTemp.LSC.Drink") && pchar.questTemp.LSC.Drink == "begin")
				{
					link.l5 = "Джузеппе, тут про вас ходят презанятные слухи. Говорят, что никакой ром не может свалить вас с ног.";
					link.l5.go = "drink";
				}
				if (CheckAttribute(pchar, "questTemp.LSC.Drink") && GetCharacterItem(pchar, "gold_dublon") >= 100 && pchar.questTemp.LSC.Drink == "wait")
				{
					link.l5 = "Я готов сыграть в вашу игру. Вот моя ставка.";
					link.l5.go = "drink_4";
				}
				// <-- квестовые ветки
				if (CheckAttribute(npchar, "quest.parol"))
				{
					link.l1 = "Я хочу узнать текущий пароль кланов для прохода на их территорию.";
					link.l1.go = "parol_choice";
				}
				link.l2 = LinkRandPhrase("Что-нибудь интересное мне расскажете?", "Что нового произошло на острове в последнее время?", "Не расскажете ли последние сплетни?");
				link.l2.go = "rumours_LSC";
				link.l3 = "Ничего особенного, Джузеппе. Я просто зашел поздороваться с вами.";
				link.l3.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting":
			dialog.text = "Разные, мой дорогой, разные. Например, я улаживаю сложности в общении между кланами и адмиралом. Как вам должно быть известно, ривадос, нарвалы и адмирал враждуют между собой. Я осуществляю посредническую деятельность между ними по щекотливым вопросам\nКроме того, часто выступаю в роли нейтральной стороны при продаже продовольствия адмиралом представителям кланов. Но это лишь небольшая часть моей деятельности. Так что если у вас вдруг возникли трудности с нарвалами или ривадос - обращайтесь ко мне, попробуем решить.";
			link.l1 = "Хорошо. Я приму это к сведению.";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
		// пароли
		case "parol_choice":
			dialog.text = "Пароль какого клана вас интересует?";
			link.l1 = "Нарвалов.";
			link.l1.go = "parol_nrv";
			link.l2 = "Ривадос.";
			link.l2.go = "parol_rvd";
		break;
		
		case "parol_nrv":
			dialog.text = "Решили заглянуть к Дональду Гринспи, я прав?";
			link.l1 = "Точно. Так вы знаете текущий пароль нарвалов?";
			link.l1.go = "parol";
			pchar.questTemp.LSC.parol = "нарвалов";
			sTotalTemp = sNrvParol;
		break;
		
		case "parol_rvd":
			dialog.text = "Отправляетесь в гости к Черному Эдди, я угадал?";
			link.l1 = "Вроде того. Так вы знаете текущий пароль ривадос?";
			link.l1.go = "parol";
			pchar.questTemp.LSC.parol = "ривадос";
			sTotalTemp = sRvdParol;
		break;
		
		case "parol":
			if (!CheckAttribute(npchar, "quest.parolrules"))
			{
				dialog.text = "А как же! Но сначала позвольте внести краткие пояснения. Пароли кланов представляют собой одно определенное слово и меняются четыре раза в месяц, то есть практически еженедельно. Смена паролей происходит каждого седьмого, четырнадцатого, двадцать первого и двадцать восьмого числа\nТак что следите за текущей датой, чтобы не попасть впросак. Ну и, как вы понимаете, пароль я вам предоставлю не бесплатно. Стоимость одной услуги - пятьдесят дублонов. За пароли я беру только дублоны, имейте это в виду.";
				link.l1 = "Пятьдесят дублонов? Это же целая куча монет!";
				link.l1.go = "parol_1";
			}
			else
			{
				dialog.text = "Конечно, мой мальчик. Цену вы знаете. У вас есть с собой пятьдесят дублонов?";
				if (GetCharacterItem(pchar, "gold_dublon") >= 50)
				{
					link.l1 = "Да. Вот, держите ваши монеты.";
					link.l1.go = "parol_pay";
				}
				link.l2 = "К сожалению, у меня нет достаточного количества монет. Возможно, позже...";
				link.l2.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "parol_1":
			dialog.text = "Ну-ну, мой мальчик, не стоит так горячиться. Не жадничайте, поверьте: я отлично знаю цену своей информации. Ведь вы на корабли "+pchar.questTemp.LSC.parol+" не на прогулку собрались, верно? Верно. Значит, должны были быть готовы к тому, что вам придется расстаться с некоторой суммой денег... Так вы готовы заплатить пятьдесят дублонов?";
			if (GetCharacterItem(pchar, "gold_dublon") >= 50)
			{
				link.l1 = "Да. Вот, держите ваши монеты.";
				link.l1.go = "parol_pay";
			}
			link.l2 = "К сожалению, у меня нет достаточного количества монет. Возможно, позже...";
			link.l2.go = "exit";
			NextDiag.TempNode = "First time";
			npchar.quest.parolrules = "true";
		break;
		
		case "parol_pay":
			RemoveItems(pchar, "gold_dublon", 50);
			dialog.text = "Отлично! Приятно иметь с вами дело. Текущий пароль "+pchar.questTemp.LSC.parol+": '"+sTotalTemp+"'. Запомните хорошенько, и не ошибитесь, когда будете называть, в противном случае я не дам за вашу жизнь и медного гроша.";
			link.l1 = "Да знаю я, знаю... Спасибо за информацию!";
			link.l1.go = "exit";
			AddQuestRecord("LSC", "parol");
			AddQuestUserData("LSC", "sText", pchar.questTemp.LSC.parol);
			AddQuestUserData("LSC", "sParol", sTotalTemp);
			if (pchar.questTemp.LSC.parol == "ривадос") pchar.questTemp.LSC.RParol_bye = "true";
			else pchar.questTemp.LSC.NParol_bye = "true";
		break;
		
		case "adolf":
			dialog.text = "Ах, ну как же, мой любезный Адольфо! Конечно, я беседовал с ним. Понимаете, мой дорогой, тогда я празновал возвращение моих денег, которые я уже и не чаял увидеть! Адольфо одолжил у меня крупную сумму в песо под залог своего чудо-штуцера, и всё никак не мог вернуть\nЯ уже и не надеялся получить их обратно и подумывал о продаже штуцера нашему драгоценному Акселю Йосту. И тут любезнейший Адольфо приносит мне мои монеты! Он, оказывается, внезапно разжился деньгами, и не только выкупил у меня свой штуцер, но и приобрел у милой Сесил Галард ее каюту на носовой части 'Санта Флорентины'!\nКонечно, там намного удобнее, чем в гамаке в полузатопленном трюме\nТак что наш дорогой Адольфо при штуцере и при новом доме, а я - при своих денежках. И как же нам было с ним не выпить, тем более, что он угощал?";
			link.l1 = "Ах, ну конечно! Столько поводов, что не выпить было нельзя. Тем более, что наливали... Спасибо, Джузеппе, вы мне очень помогли. Теперь я хоть знаю, где мне искать Адольфа.";
			link.l1.go = "adolf_1";
		break;
		
		case "adolf_1":
			dialog.text = "Всегда пожалуйста, мой дорогой. Но не ищите Адольфо у себя в каюте раньше вечера - он очень, очень занятой, что вы, все бегает и бегает по делам... Да, а вы заходите ко мне почаще, еще поболтаем!";
			link.l1 = "Куплю себе каюту - обязательно приглашу вас на новоселье... Всего доброго и до встречи!";
			link.l1.go = "adolf_2";
		break;
		
		case "adolf_2":
			DialogExit();
			LSC_CreateAdolfClone(); // заменяем Адольфа клоном
			pchar.questTemp.Saga.SharkHunt = "search_mush_4"; //флаг на Адольфа в каюте
			AddQuestRecord("SharkHunt", "14");
		break;
		
		case "whiskey":
			switch (sti(npchar.quest.poisonnode))
			{
				case 1: // у себя
					dialog.text = "А? Что ты врываешься ко мне, словно здесь пожар? Что ты себе позволяешь?";
					link.l1 = "Сейчас я позволю себе еще большее... отравитель!";
					link.l1.go = "whiskey_1";
				break;
				
				case 2: // на Эве
					dialog.text = "Пощади! Клянусь, они заставили меня! Они приставили мне пистолет ко...";
					link.l1 = "Замолчи. Я это уже понял. Где последний ублюдок из их компании? Где Марчелло Циклоп?!";
					link.l1.go = "whiskey_3";
					SetFunctionTimerCondition("LSC_FacioReturn", 0, 0, 1, false); // вертаем на место Фацио через сутки
				break;
				
				case 3: // у Акулы
					dialog.text = "Клянусь, они заставили меня! Я уже все рассказал адмиралу! Я не мог им сопротивляться, они бы...";
					link.l1 = "Замолчи. Я это уже понял. Где последний ублюдок из их компании? Где Марчелло Циклоп?!";
					link.l1.go = "whiskey_3";
					SetFunctionTimerCondition("LSC_FacioReturn", 0, 0, 1, false); // вертаем на место Фацио через сутки
				break;
			}
		break;
		
		case "whiskey_1":
			dialog.text = "Что... что ты сказал?";
			link.l1 = "Я все знаю, негодяй. Ты действовал заодно с Чадом Каппером. Ты принес бочонок с отравленным ромом адмиралу. Теперь молись, ничтожество...";
			link.l1.go = "whiskey_2";
		break;
		
		case "whiskey_2":
			dialog.text = "Стой! Остановись! Пощади! Клянусь, они заставили меня! Они приставили мне пистолет ко...";
			link.l1 = "Замолчи. Это понятно. Где последний ублюдок из их компании? Где Марчелло Циклоп?!";
			link.l1.go = "whiskey_3";
		break;
		
		case "whiskey_3":
			dialog.text = "Я... я... я не знаю!";
			link.l1 = "Лжешь, поганый мешок навоза! Я это вижу. Где Циклоп?";
			if (pchar.questTemp.LSC.Mary == "die") link.l1.go = "whiskey_10"; // ушел на Флерон
			else link.l1.go = "whiskey_4";
		break;
		
		case "whiskey_4":
			dialog.text = "Он... он получил от Каппера какой-то приказ и ушел. Я не знаю, где он!";
			link.l1 = "Опять лжешь. Ты все знаешь. Не трусь, малодушная тварь, Каппер мертв и ничего не сделает тебе. Но если ты не скажешь, где Марчелло - я проткну тебя, как жука, прямо сейчас! Что приказал Циклопу Чад?";
			link.l1.go = "whiskey_5";
		break;
		
		case "whiskey_5":
			dialog.text = "Он отправил его убить... Красную Мэри.";
			link.l1 = "Что?! Говори немедленно, каким образом он планирует это сделать? К ней в каюту на 'Церес Смити' не попасть, у нее заперты все двери! Как он собирается убить ее?!";
			link.l1.go = "whiskey_6";
		break;
		
		case "whiskey_6":
			dialog.text = "Он пройдет через корму 'Церес Смити', в каюту Юргена, оружейника, когда тот отлучится. Потом спустится на самое дно трюма по веревке - все трапы, ведущие туда, сломаны. Затем тихо пересечет подтопленный трюм и выйдет прямо к каюте Мэри\nДальше ему нужно будет только дождаться, пока девушка повернется к нему спиной, или заснет - и все, дело сделано. Это все сказал Чад. Клянусь, я больше ничего не знаю!";
			link.l1 = "Этого достаточно. Когда он ушел? Когда, я спрашиваю, Циклоп ушел на 'Церес Смити'?";
			link.l1.go = "whiskey_7";
		break;
		
		case "whiskey_7":
			dialog.text = "Он уже наверняка у Юргена... или спускается в трюм...";
			link.l1 = "Проклятие!! Вплавь вокруг острова я не успею! Говори пароль нарвалов для прохода на их корабли! Говори, а если солжешь - я все равно останусь в живых, но тогда тебе точно конец!";
			link.l1.go = "whiskey_8";
		break;
		
		case "whiskey_8":
			dialog.text = "'"+sNrvParol+"'...";
			link.l1 = "Я запомнил. А теперь молись, чтобы девушка осталась жива!";
			link.l1.go = "whiskey_9";
		break;
		
		case "whiskey_9":
			DialogExit();
			chrDisableReloadToLocation = false;//открыть локацию
			NextDiag.CurrentNode = "whiskey_repeat";
			pchar.quest.LSC_RescueMary.win_condition.l1 = "location";
			pchar.quest.LSC_RescueMary.win_condition.l1.location = "LostShipsCity_town";
			pchar.quest.LSC_RescueMary.function = "LSC_RescueMary";
			AddQuestRecord("SharkHunt", "46");
			AddQuestUserData("SharkHunt", "sParol", sNrvParol);
			pchar.questTemp.LSC.NParol_bye = "true";
		break;
		
		case "whiskey_repeat":
			dialog.text = "Я уже все сказал, что знал! Клянусь!";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "whiskey_repeat";
		break;
		
		case "whiskey_10":
			dialog.text = "Он... О спрятался где-то на каравелле 'Флерон'. Чад сказал ему затаиться там и ждать его дальнейших указаний.";
			link.l1 = "Понятно. Но смотри мне, если солгал...";
			link.l1.go = "whiskey_11";
		break;
		
		case "whiskey_11":
			DialogExit();
			chrDisableReloadToLocation = false;//открыть локацию
			pchar.quest.LSC_FindCyclop.win_condition.l1 = "location";
			pchar.quest.LSC_FindCyclop.win_condition.l1.location = "FleuronTavern";
			pchar.quest.LSC_FindCyclop.function = "LSC_SetCyclop_Fl";
			NextDiag.CurrentNode = "whiskey_repeat";
			AddQuestRecord("SharkHunt", "51");
			
		break;
		
		// --> конфликты
		case "conflict":
			dialog.text = "Вот как? Ну что же, мой мальчик, с каким кланом у тебя неприятности?";
			if (CheckAttribute(pchar, "GenQuest.NarvalConflict"))
			{
				link.l1 = "C нарвалами.";
				link.l1.go = "narval";
				npchar.quest.clan = "narval";
			}
			if (CheckAttribute(pchar, "GenQuest.RivadosConflict"))
			{
				link.l2 = "С ривадос.";
				link.l2.go = "rivados";
				npchar.quest.clan = "rivados";
			}
			if (CheckAttribute(pchar, "GenQuest.SharkConflict"))
			{
				link.l3 = "С пиратами адмирала.";
				link.l3.go = "shark";
				npchar.quest.clan = "shark";
			}
			link.l4 = "Ни с каким. Я пошутил, Джузеппе, у меня все в порядке.";
			link.l4.go = "exit";
		break;
		
		case "narval":
			npchar.quest.price = sti(pchar.GenQuest.NarvalConflict)*50;
			if (sti(pchar.GenQuest.NarvalConflict) < 3) dialog.text = "Ну, это еще не конфликт - так, небольшое недоразумение, хе-хе. "+sti(npchar.quest.price)+" дублонов - и ваша проблема будет решена через сутки.";
			else
			{
				if (sti(pchar.GenQuest.NarvalConflict) >= 3 && sti(pchar.GenQuest.NarvalConflict) < 10) dialog.text = "Как же, как же, наслышан. Драку вы учинили знатную, мой дорогой. Но выход есть. "+sti(npchar.quest.price)+" дублонов - и ваша проблема будет решена через сутки.";
				else dialog.text = "Уже весь Остров знает о резне, которую вы учинили. Сложно будет вам помочь, но ситуация не безвыходная. "+sti(npchar.quest.price)+" дублонов - и я попробую решить вашу проблему.";
			}
			if (GetCharacterItem(pchar, "gold_dublon") >= sti(npchar.quest.price))
			{
				link.l1 = "Вот, держите ваши монеты и уладьте все разногласия.";
				link.l1.go = "pay";
			}
			link.l2 = "К сожалению, у меня нет сейчас такого количества дублонов. Но я обязательно принесу, и мы вернемся к нашему разговору.";
			link.l2.go = "exit";
		break;
		
		case "rivados":
			npchar.quest.price = sti(pchar.GenQuest.RivadosConflict)*50;
			if (sti(pchar.GenQuest.RivadosConflict) < 3) dialog.text = "Ну, это еще не конфликт - так, небольшое недоразумение, хе-хе. "+sti(npchar.quest.price)+" дублонов - и ваша проблема будет решена через сутки.";
			else
			{
				if (sti(pchar.GenQuest.RivadosConflict) >= 3 && sti(pchar.GenQuest.RivadosConflict) < 10) dialog.text = "Как же, как же, наслышан. Драку вы учинили знатную, мой дорогой. Но выход есть. "+sti(npchar.quest.price)+" дублонов - и ваша проблема будет решена через сутки.";
				else dialog.text = "Уже весь Остров знает о резне, которую вы учинили. Сложно будет вам помочь, но ситуация не безвыходная. "+sti(npchar.quest.price)+" дублонов - и я попробую решить вашу проблему.";
			}
			if (GetCharacterItem(pchar, "gold_dublon") >= sti(npchar.quest.price))
			{
				link.l1 = "Вот, держите ваши монеты и уладьте все разногласия.";
				link.l1.go = "pay";
			}
			link.l2 = "К сожалению, у меня нет сейчас такого количества дублонов. Но я обязательно принесу, и мы вернемся к нашему разговору.";
			link.l2.go = "exit";
		break;
		
		case "shark":
			npchar.quest.price = sti(pchar.GenQuest.SharkConflict)*50;
			if (sti(pchar.GenQuest.SharkConflict) < 3) dialog.text = "Ну, это еще не конфликт - так, небольшое недоразумение, хе-хе. "+sti(npchar.quest.price)+" дублонов - и ваша проблема будет решена через сутки.";
			else
			{
				if (sti(pchar.GenQuest.SharkConflict) >= 3 && sti(pchar.GenQuest.SharkConflict) < 10) dialog.text = "Как же, как же, наслышан. Драку вы учинили знатную, мой дорогой. Но выход есть. "+sti(npchar.quest.price)+" дублонов - и ваша проблема будет решена через сутки.";
				else dialog.text = "Уже весь Остров знает о резне, которую вы учинили. Сложно будет вам помочь, но ситуация не безвыходная. "+sti(npchar.quest.price)+" дублонов - и я попробую решить вашу проблему.";
			}
			if (GetCharacterItem(pchar, "gold_dublon") >= sti(npchar.quest.price))
			{
				link.l1 = "Вот, держите ваши монеты и уладьте все разногласия.";
				link.l1.go = "pay";
			}
			link.l2 = "К сожалению, у меня нет сейчас такого количества дублонов. Но я обязательно принесу, и мы вернемся к нашему разговору.";
			link.l2.go = "exit";
		break;
		
		case "pay":
			RemoveItems(pchar, "gold_dublon", sti(npchar.quest.price));
			PlaySound("interface\important_item.wav");
			Log_Info("Вы отдали "+sti(npchar.quest.price)+" дублонов");
			dialog.text = "Замечательно! Теперь присаживайтесь, отдохните. До тех пор, пока я не улажу все вопросы, вам лучше побыть в моей каюте. А то не дай Бог, опять бед натворите, любезнейший.";
			link.l1 = "Хорошо...";
			link.l1.go = "peace";
		break;
		
		case "peace":
			DialogExit();
			GetCharacterPos(pchar, &locx, &locy, &locz);
			pchar.locx = locx;
			pchar.locy = locy;
			pchar.locz = locz;
			SetLaunchFrameFormParam("Прошли сутки..."+ NewStr() +"Фацио урегулировал ваш конфликт", "Reload_To_Location", 0.1, 5.0);
			SetLaunchFrameReloadLocationParam(pchar.location, "goto", LAi_FindNearestFreeLocator2Pchar("goto"), "LocTeleport");
			WaitDate("", 0, 0, 1, 3, 10); //крутим время
			LaunchFrameForm();
			RefreshLandTime();
			RecalculateJumpTable();
			Whr_UpdateWeather();
			switch (npchar.quest.clan)
			{
				case "narval":
					DeleteAttribute(pchar, "GenQuest.NarvalConflict"); // мирим
					if (CheckAttribute(pchar, "questTemp.LSC.nrv_friend") || !CheckAttribute(pchar, "questTemp.LSC.rvd_friend")) LocatorReloadEnterDisable("LostShipsCity_town", "reload48", false);//открыть вход к Дональду
					LAi_group_SetRelation("LSC_NARVAL", LAI_GROUP_PLAYER, LAI_GROUP_NEITRAL);
				break;
				
				case "rivados":
					DeleteAttribute(pchar, "GenQuest.RivadosConflict"); // мирим
					if (CheckAttribute(pchar, "questTemp.LSC.rvd_friend") || !CheckAttribute(pchar, "questTemp.LSC.nrv_friend")) LocatorReloadEnterDisable("LostShipsCity_town", "reload33", false);//открыть вход к Эдди
					LAi_group_SetRelation("LSC_RIVADOS", LAI_GROUP_PLAYER, LAI_GROUP_NEITRAL);
				break;
				
				case "shark":
					DeleteAttribute(pchar, "GenQuest.SharkConflict"); // мирим
					LSC_OpenSanAvgustinDoors(); // открыть сан-августин
					LSC_OpenTartarusDoors(); // открыть тартарус
					LAi_group_SetRelation("LSC_SHARK", LAI_GROUP_PLAYER, LAI_GROUP_NEITRAL);
				break;
			}
			DeleteAttribute(npchar, "quest.clan");
			DeleteAttribute(npchar, "quest.price");
		break;
		
		// --> пей до дна
		case "drink":
			dialog.text = "Ну что вы, мой мальчик! Лгут, всё лгут, хе-хе. Просто у меня голова крепче, чем у большинства, но я такой же человек, как и вы, и тоже пьянею от рома. Если бы ром не вызывал опьянение - кто бы его тогда пил, а? Вы не задумывались над этим, мой драгоценнейший?";
			link.l1 = "Вы правы. Наверное, и пьяниц тогда не было бы на свете...";
			link.l1.go = "drink_1";
		break;
		
		case "drink_1":
			dialog.text = "А хотите сыграть со мной в одну забавную игру? Она называется - 'пей до дна', ха-ха! Уверен, вы уже слышали об этом. Ведь так?";
			link.l1 = "Да, чирикали об этом пташки... Только я бы ее назвал 'мордой в стол', эту вашу игру.";
			link.l1.go = "drink_2";
		break;
		
		case "drink_2":
			dialog.text = "Ха-ха-ха, мой милый мальчик, потешили старика, ничего не скажешь! Мордой в стол! Надо запомнить... Так сыграем, или нет? На сто дублонов?";
			link.l1 = "На сотню?";
			link.l1.go = "drink_3";
		break;
		
		case "drink_3":
			dialog.text = "Да, и проигравший оплачивает все выпитое. Согласны?";
			if (GetCharacterItem(pchar, "gold_dublon") >= 100)
			{
				link.l1 = "Да, согласен. Вот моя ставка.";
				link.l1.go = "drink_4";
			}
			link.l2 = "Хм. У меня нет столько дублонов.";
			link.l2.go = "drink_wait";
		break;
		
		case "drink_wait":
			dialog.text = "Ну, тогда как достанете - обязательно приходите, сыграем, милейший!";
			link.l1 = "Хорошо...";
			link.l1.go = "exit";
			pchar.questTemp.LSC.Drink = "wait";
		break;
		
		case "drink_4":
			RemoveItems(pchar, "gold_dublon", 100);
			Log_Info("Вы отдали 100 дублонов");
			PlaySound("interface\important_item.wav");
			dialog.text = "Отлично, мой драгоценнейший! Тогда встречаемся в девять вечера в таверне у милейшего Санчо и сыграем! Да, если вы вдруг передумаете, или паче чаяния вас отвлекут неотложные дела - то ваша ставка останется у меня, это одно из правил. Но вы ведь придете, так, мой мальчик?";
			link.l1 = "Обязательно, Джузеппе. Готовьтесь к сражению на бутылках!";
			link.l1.go = "drink_5";
		break;
		
		case "drink_5":
			dialog.text = "И вы тоже, драгоценнейший! Мордой в стол! Ну надо же, ха-ха!";
			link.l1 = "До встречи в девять часов в таверне!";
			link.l1.go = "drink_6";
		break;
		
		case "drink_6":
			DialogExit();
			pchar.questTemp.LSC.Drink = "start";
			pchar.quest.LSC_DrinkOver.over = "yes"; //снять таймер
			pchar.quest.LSC_Drink.win_condition.l1 = "Timer";
			pchar.quest.LSC_Drink.win_condition.l1.date.hour  = 21.0;
			pchar.quest.LSC_Drink.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 0);
			pchar.quest.LSC_Drink.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 0);
			pchar.quest.LSC_Drink.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 0);
			pchar.quest.LSC_Drink.function = "LSC_DrinkPrepare";
			pchar.quest.LSC_Drink_Over.win_condition.l1 = "Timer";
			pchar.quest.LSC_Drink_Over.win_condition.l1.date.hour  = 23.0;
			pchar.quest.LSC_Drink_Over.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 0);
			pchar.quest.LSC_Drink_Over.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 0);
			pchar.quest.LSC_Drink_Over.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 0);
			pchar.quest.LSC_Drink_Over.function = "LSC_DrinkDelete";
			AddQuestRecord("LSC_Drink", "2");
		break;
		
		case "drink_8":
			dialog.text = "Ну что, любезнейший, готовы к встрече со столом, хе-хе? Ром наш драгоценный Санчо уже принес. Правила не надо оглашать? Они очень просты: пьем из одной бутылки кружку за кружкой до дна, пока кто-то из нас не отключится\nДа, разговаривать нам с вами, милейший, не запрещается, наоборот - приветствуется! Это же ведь так замечательно - поболтать с хорошим человеком! Ну, а если вам удастся выиграть - то свой приз получите у Санчо. Начинаем?";
			link.l1 = "Пожалуй, да. Приступим, Джузеппе!";
			link.l1.go = "drink_9";
		break;
		
		case "drink_9":
			DialogExit();
			pchar.questTemp.LSC.Drink = "go";
			pchar.quest.LSC_Drink_Over.over = "yes"; //снять таймер
			ChangeCharacterAddressGroup(pchar, "FleuronTavern", "quest", "sit1");
			LAi_SetActorType(pchar);
			LAi_ActorSetSitMode(pchar);
			ChangeCharacterAddressGroup(npchar, "FleuronTavern", "quest", "sit2");
			LAi_SetActorType(npchar);
			LAi_ActorSetSitMode(npchar);
			DoQuestFunctionDelay("LSC_DrinkGo", 0.6);
		break;
		
		case "drunk":
			dialog.text = "Пя-ятнад-цать че-елов-ек, на сундук... ик! Аха!.. Йо-хо-кха... И м... бутылка...";
			link.l1 = "Ясно...";
			link.l1.go = "exit";
			NextDiag.TempNode = "drunk";
		break;
		// <-- пей до дна
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
	}
}