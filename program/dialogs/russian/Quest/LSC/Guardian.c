// диалог протекторов, солдат и мушкетеров кланов LSC
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	string sTemp;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "Ну чего тебе ещё надо?";
			link.l1 = "Да нет, ничего.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
//------------------------------------- фразы гардов нарвалов --------------------------------------------
		// пост нарвалов на проход на Сан-Габриэль
		case "Narval_warning":
			if (CheckAttribute(pchar, "GenQuest.NarvalConflict"))
			{
				dialog.text = LinkRandPhrase("Ребята, осторожно, здесь тот самый больной псих! К оружию!","Враг на территории! К бою!","Ах ты, мерзавец! Сейчас мы тебе зададим хорошую взбучку!");
				link.l1 = "А-ать!";
				link.l1.go = "check_parol_fight";
				break;
			}
			ref location = &Locations[FindLocation(pchar.location)];
			if (!CheckAttribute(location, "nrv_parolinfo"))
			{
				if (!CheckAttribute(pchar, "questTemp.LSC.nrv_friend")) 
				{
					dialog.text = "Стой, приятель! Дальше - территория нарвалов, куда посторонним вход запрещён. Пройти туда можно только по приглашению. Ты знаешь пароль для прохода?";
					link.l1 = "Да.";
					link.l1.go = "Narval_warning_yes";
					link.l2 = "Нет.";
					link.l2.go = "Narval_warning_no";
				}
				else // если друг нарвалам
				{
					dialog.text = "А-а, это же "+GetFullName(pchar)+"! Привет, дружище, нас предупредили о тебе. Можешь проходить на 'Сан-Габриэль' и 'Церес Смити' свободно. Добро пожаловать!";
					link.l1 = "Спасибо, приятель!";
					link.l1.go = "exit";
				}
				location.nrv_parolinfo = "true";
			}
			else
			{
				if (!CheckAttribute(pchar, "questTemp.LSC.nrv_friend")) 
				{
					dialog.text = "Надеюсь, ты не забыл пароль, приятель...";
					link.l1 = "Не переживай...";
					link.l1.go = "exit";
				}
				else // если друг нарвалам
				{
					dialog.text = TimeGreeting()+", "+pchar.name+"! Как твои дела?";
					link.l1 = "Спасибо, хорошо!";
					link.l1.go = "exit";
				}
			}
			NextDiag.TempNode = "Narval_warning_repeat";
			DeleteAttribute(npchar, "protector.CheckAlways");
		break;
		
		case "Narval_warning_yes":
			dialog.text = "Тогда иди и скажи его вон тому суровому парню внизу. И смотри, не пытайся его обмануть - наши ребята с мушкетами своё дело знают. Так что если ты сейчас пытаешься хитрить - лучше развернись и уходи прочь. Я тебя предупредил.";
			link.l1 = "Хорошо, дружище. Я учту.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Narval_warning_repeat";
		break;
		
		case "Narval_warning_no":
			dialog.text = "Тогда тебе нечего там делать, если ты, конечно, не решил таким способом свести счеты с жизнью. Или ты шутишь, а? Смеёшься надо мной? Впрочем, меня это не интересует. Можешь идти вниз, мое дело предупреждать, а не задерживать. Но если ты действительно не знаешь пароля - назад ты уже не выйдешь.";
			link.l1 = "Хорошо, дружище. Я учту.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Narval_warning_repeat";
		break;
		
		case "Narval_warning_repeat":
			if (!CheckAttribute(pchar, "questTemp.LSC.nrv_friend")) 
			{
				dialog.text = "Ну, чего тебе ещё? Или иди вниз на 'Сан-Габриэль', или проваливай отсюда!";
				link.l1 = "...";
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = "Извини, "+pchar.name+", но я на посту. Не отвлекай меня. Ступай!";
				link.l1 = "...";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "Narval_warning_repeat";
		break;
		
		case "Narval_parol":
			if (CheckAttribute(pchar, "GenQuest.NarvalConflict"))
			{
				dialog.text = LinkRandPhrase("Ребята, осторожно, здесь тот самый больной псих! К оружию!","Враг на территории! К бою!","Ах ты, мерзавец! Сейчас мы тебе зададим хорошую взбучку!");
				link.l1 = "А-ать!";
				link.l1.go = "check_parol_fight";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.LSC.nrv_friend")) 
			{
				dialog.text = "Извини, "+pchar.name+", но я на посту. Не отвлекай меня. Ступай!";
				link.l1 = "...";
				link.l1.go = "exit";
				NextDiag.TempNode = "Narval_parol";
				break;
			}
			dialog.text = "Стоять! Ты не из наших!";
			link.l1 = "Уже стою.";	
			link.l1.go = "check_parol";
		break;
		
		case "check_parol":
			dialog.text = "Говори пароль, и произноси его чётко, чтобы я хорошо расслышал.";
			link.l1.edit = 3;
			link.l1 = "";	
			link.l1.go = "check_parol_1";
		break;
		
		case "check_parol_1":
			sTemp = GetStrSmallRegister(dialogEditStrings[3]);
			if (sTemp == sNrvParol && CheckAttribute(pchar, "questTemp.LSC.NParol_bye"))
			{
				dialog.text = "Хорошо. Можешь проходить.";
				link.l1 = "Спасибо, приятель...";
				link.l1.go = "exit";
				NextDiag.TempNode = "Narval_parol_repeat";
				LAi_SetGuardianType(NPChar);
				LAi_group_MoveCharacter(NPChar, "LSC_NARVAL");
				pchar.questTemp.LSC.parol_nrv = "true";
			}
			else
			{
				dialog.text = "Хм... Ребята! У нас незванные гости!";
				link.l1 = "А-ать!";
				link.l1.go = "check_parol_fight";
			}
		break;
		
		case "check_parol_fight":
			DialogExit();
			LAi_SetGuardianType(NPChar);
			LAi_group_MoveCharacter(NPChar, "LSC_NARVAL");
			LAi_group_Attack(NPChar, Pchar);
		break;
		
		case "Narval_parol_repeat":
			if (CheckAttribute(pchar, "GenQuest.NarvalConflict"))
			{
				dialog.text = LinkRandPhrase("Ребята, осторожно, здесь тот самый больной псих! К оружию!","Враг на территории! К бою!","Ах ты, мерзавец! Сейчас мы тебе зададим хорошую взбучку!");
				link.l1 = "А-ать!";
				link.l1.go = "check_parol_fight";
				break;
			}
			dialog.text = "Давай проходи, не задерживай! Нечего тут стоять!";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "Narval_parol_repeat";
		break;
		
		// у резиденции
		case "Narval_residence":
			if (CheckAttribute(pchar, "GenQuest.NarvalConflict"))
			{
				dialog.text = LinkRandPhrase("Ребята, осторожно, здесь тот самый больной псих! К оружию!","Враг на территории! К бою!","Ах ты, мерзавец! Сейчас мы тебе зададим хорошую взбучку!");
				link.l1 = "А-ать!";
				link.l1.go = "check_parol_fight";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.LSC.nrv_friend")) 
			{
				dialog.text = TimeGreeting()+", "+pchar.name+"! Если ты к боссу - заходи, дверь открыта.";
				link.l1 = "Хорошо...";
				link.l1.go = "exit";
				NextDiag.TempNode = "Narval_residence";
				DeleteAttribute(npchar, "protector.CheckAlways");
				break;
			}
			if (!CheckAttribute(pchar, "questTemp.LSC.nrv_friend") && CheckAttribute(pchar, "questTemp.LSC.rvd_friend")) 
			{
				dialog.text = "Друзьям и пособникам черномазых нечего тут делать. Прямой приказ босса - тебя к нему не пускать!";
				if (CheckAttribute(pchar, "questTemp.LSC.Donald_enter"))
				{
					link.l1 = "И всё-таки ему придётся меня увидеть. У вас крупные неприятности, ребята. Я с официальным визитом от адмирала. Так что открывай эту чёртову дверь!";
					link.l1.go = "negotiations";
				}
				else
				{
				link.l1 = "Да не очень-то и хотелось...";
				link.l1.go = "exit";
				}
				NextDiag.TempNode = "Narval_residence";
				DeleteAttribute(npchar, "protector.CheckAlways");
				break;
			}
			dialog.text = "Ты к боссу? Хм, ну, проходи, если хочешь.";
			link.l1 = "Спасибо, что разрешил...";
			link.l1.go = "exit";
			NextDiag.TempNode = "Narval_residence";
			DeleteAttribute(npchar, "protector.CheckAlways");
		break;
		
		case "Narval_soldier":
			if (CheckAttribute(pchar, "GenQuest.NarvalConflict"))
			{
				dialog.text = LinkRandPhrase("Ребята, осторожно, здесь тот самый больной псих! К оружию!","Враг на территории! К бою!","Ах ты, мерзавец! Сейчас мы тебе зададим хорошую взбучку!");
				link.l1 = "А-ать!";
				link.l1.go = "check_parol_fight";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.LSC.nrv_friend")) 
			{
				dialog.text = TimeGreeting()+", "+pchar.name+"! Как твои дела?";
				link.l1 = "Спасибо, неплохо...";
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = "Послушай, приятель, я не в настроении тут с тобой распинаться. Проходи себе мимо...";
				link.l1 = "Ладно.";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "Narval_soldier";
		break;
		
		case "negotiations":
			dialog.text = "Ладно-ладно... Чего расшумелся? Так бы и сказал, что к боссу от адмирала. Пойми, тут всякие ходят...";
			link.l1 = "Ты дашь мне пройти, наконец? Вот, спасибо!";
			link.l1.go = "negotiations_1";
		break;
		
		case "negotiations_1":
			DialogExit();
			NextDiag.CurrentNode = "negotiations_2";
			LocatorReloadEnterDisable("LostShipsCity_town", "reload48", false); // открыть вход к Дональду Гринспи
		break;
		
		case "negotiations_2":
			dialog.text = "Проходи, проходи, тебе разрешено...";
			link.l1 = "Да неужели?";
			link.l1.go = "exit";
			NextDiag.TempNode = "negotiations_2";
		break;
		
//------------------------------------- фразы гардов ривадос --------------------------------------------
		// пост ривадос на проход на Фурию и Веласко
		case "Rivados_warning":
			if (CheckAttribute(pchar, "GenQuest.RivadosConflict"))
			{
				dialog.text = LinkRandPhrase("Ребята! Осторожно! Здесь агрессивный психопат! К оружию!","Враг на территории! К бою!","Ах ты, больной ублюдок! Сейчас мы тебе зададим перцу!");
				link.l1 = "А-ать!";
				link.l1.go = "Rcheck_parol_fight";
				break;
			}
			location = &Locations[FindLocation(pchar.location)];
			if (!CheckAttribute(location, "rvd_parolinfo"))
			{
				if (!CheckAttribute(pchar, "questTemp.LSC.rvd_friend")) 
				{
					dialog.text = "Немедленно стой! Территория за моей спиной принадлежит клану ривадос, куда посторонним вроде тебя вход воспрещён без приглашения. Ты знаешь пароль?";
					link.l1 = "Да.";
					link.l1.go = "Rivados_warning_yes";
					link.l2 = "Нет.";
					link.l2.go = "Rivados_warning_no";
				}
				else // если друг ривадос
				{
					dialog.text = "Кажется, это сам "+GetFullName(pchar)+"! Очень рады вас видеть! Нас предупредили, что вы можете свободно проходить на наши корабли. Всегда рады!";
					link.l1 = "Спасибо, дружище!";
					link.l1.go = "exit";
				}
				location.rvd_parolinfo = "true";
			}
			else
			{
				if (!CheckAttribute(pchar, "questTemp.LSC.rvd_friend")) 
				{
					dialog.text = "Надеюсь, ты хорошо помнишь пароль, приятель...";
					link.l1 = "Не переживай...";
					link.l1.go = "exit";
				}
				else // если друг ривадос
				{
					dialog.text = TimeGreeting()+", "+pchar.name+"! Как ваши дела?";
					link.l1 = "Спасибо, хорошо!";
					link.l1.go = "exit";
				}
			}
			NextDiag.TempNode = "Rivados_warning_repeat";
			DeleteAttribute(npchar, "protector.CheckAlways");
		break;
		
		case "Rivados_warning_yes":
			dialog.text = "Тогда можешь проходить. Вот тот парень впереди потребует, чтобы ты назвал пароль. Так что если ты сейчас лукавишь - лучше уходи подобру-поздорову. Я тебя предупредил.";
			link.l1 = "Хорошо, приятель. Я учту.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Rivados_warning_repeat";
		break;
		
		case "Rivados_warning_no":
			dialog.text = "Хо-хо! Ты или очень храбрый, или очень глупый человек, раз намереваешься пройти к нам, не зная пароля. Или ты шутишь? Шути дальше. Я здесь стою, чтобы предупреждать, а не удерживать. Но если ты действительно не знаешь пароля - тогда берегись!";
			link.l1 = "Хорошо, приятель. Я учту.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Rivados_warning_repeat";
		break;
		
		case "Rivados_warning_repeat":
			if (!CheckAttribute(pchar, "questTemp.LSC.rvd_friend")) 
			{
				dialog.text = "Ну, чего тебе надо? Или иди вперёд, или проваливай отсюда!";
				link.l1 = "...";
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = "Извините, "+pchar.name+", но я на посту. Эдди будет недоволен, если я стану много болтать.";
				link.l1 = "...";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "Rivados_warning_repeat";
			DeleteAttribute(npchar, "protector.CheckAlways");
		break;
		
		case "Rivados_parol":
			if (CheckAttribute(pchar, "GenQuest.RivadosConflict"))
			{
				dialog.text = LinkRandPhrase("Ребята! Осторожно! Здесь агрессивный психопат! К оружию!","Враг на территории! К бою!","Ах ты, больной ублюдок! Сейчас мы тебе зададим перцу!");
				link.l1 = "А-ать!";
				link.l1.go = "Rcheck_parol_fight";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.LSC.rvd_friend")) 
			{
				dialog.text = "Извини, "+pchar.name+", но я на посту. Эдди будет недоволен, если я стану много болтать.";
				link.l1 = "...";
				link.l1.go = "exit";
				NextDiag.TempNode = "Rivados_parol";
				DeleteAttribute(npchar, "protector.CheckAlways");
				break;
			}
			dialog.text = "Стой где стоишь! Ты не из ривадос!";
			link.l1 = "Я хочу пройти дальше.";	
			link.l1.go = "Rcheck_parol";
		break;
		
		case "Rcheck_parol":
			dialog.text = "Тогда говори пароль, и говори ясно и четко.";
			link.l1.edit = 3;
			link.l1 = "";	
			link.l1.go = "Rcheck_parol_1";
		break;
		
		case "Rcheck_parol_1":
			sTemp = GetStrSmallRegister(dialogEditStrings[3]);
			if (sTemp == sRvdParol && CheckAttribute(pchar, "questTemp.LSC.RParol_bye"))
			{
				dialog.text = "Всё верно. Можешь проходить.";
				link.l1 = "Спасибо, приятель...";
				link.l1.go = "exit";
				NextDiag.TempNode = "Rivados_parol_repeat";
				LAi_SetGuardianType(NPChar);
				LAi_group_MoveCharacter(NPChar, "LSC_RIVADOS");
				pchar.questTemp.LSC.parol_rvd = "true";
			}
			else
			{
				dialog.text = "Ха-ха! Да к нам непрошеный гость пожаловал! Покажем ему!";
				link.l1 = "А-ать!";
				link.l1.go = "Rcheck_parol_fight";
			}
		break;
		
		case "Rcheck_parol_fight":
			DialogExit();
			LAi_SetGuardianType(NPChar);
			LAi_group_MoveCharacter(NPChar, "LSC_RIVADOS");
			LAi_group_Attack(NPChar, Pchar);
		break;
		
		case "Rivados_parol_repeat":
			if (CheckAttribute(pchar, "GenQuest.RivadosConflict"))
			{
				dialog.text = LinkRandPhrase("Ребята! Осторожно! Здесь агрессивный психопат! К оружию!","Враг на территории! К бою!","Ах ты, больной ублюдок! Сейчас мы тебе зададим перцу!");
				link.l1 = "А-ать!";
				link.l1.go = "Rcheck_parol_fight";
				break;
			}
			dialog.text = "Не стой здесь, проходи!";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "Rivados_parol_repeat";
		break;
		
		// у резиденции
		case "Rivados_residence":
			if (CheckAttribute(pchar, "GenQuest.RivadosConflict"))
			{
				dialog.text = LinkRandPhrase("Ребята! Осторожно! Здесь агрессивный психопат! К оружию!","Враг на территории! К бою!","Ах ты, больной ублюдок! Сейчас мы тебе зададим перцу!");
				link.l1 = "А-ать!";
				link.l1.go = "Rcheck_parol_fight";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.LSC.rvd_friend")) 
			{
				dialog.text = TimeGreeting()+", "+pchar.name+"! Если вы к Эдди и Чимисету - заходите, дверь открыта. Они будут рады вас видеть.";
				link.l1 = "Хорошо...";
				link.l1.go = "exit";
				NextDiag.TempNode = "Rivados_residence";
				DeleteAttribute(npchar, "protector.CheckAlways");
				break;
			}
			if (CheckAttribute(pchar, "questTemp.LSC.nrv_friend") && !CheckAttribute(pchar, "questTemp.LSC.rvd_friend")) 
			{
				dialog.text = "Дружкам нарвалов нечего делать в каюте Эдди! Это его прямой приказ. Уходи!";
				link.l1 = "Да не очень-то и хотелось...";
				link.l1.go = "exit";
				NextDiag.TempNode = "Rivados_residence";
				DeleteAttribute(npchar, "protector.CheckAlways");
				break;
			}
			if (GetCharacterIndex("Chimiset") == -1) // Чимисет убит
			{
				dialog.text = "Тебе нечего делать в каюте Эдди! Это его прямой приказ. Убирайся!";
				link.l1 = "Да не очень-то и хотелось...";
				link.l1.go = "exit";
				NextDiag.TempNode = "Rivados_residence";
				DeleteAttribute(npchar, "protector.CheckAlways");
				break;
			}
			dialog.text = "Ты к Эдди? Ну ладно, проходи, он найдёт для тебя минутку.";
			link.l1 = "Спасибо, что разрешил...";
			link.l1.go = "exit";
			NextDiag.TempNode = "Rivados_residence";
			DeleteAttribute(npchar, "protector.CheckAlways");
		break;
		
		case "Rivados_soldier":
			if (CheckAttribute(pchar, "GenQuest.RivadosConflict"))
			{
				dialog.text = LinkRandPhrase("Ребята! Осторожно! Здесь агрессивный психопат! К оружию!","Враг на территории! К бою!","Ах ты, больной ублюдок! Сейчас мы тебе зададим перцу!");
				link.l1 = "А-ать!";
				link.l1.go = "Rcheck_parol_fight";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.LSC.rvd_friend")) 
			{
				dialog.text = TimeGreeting()+", "+pchar.name+"! Как поживаете?";
				link.l1 = "Спасибо, хорошо...";
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = "Послушай, друг, у меня нет никакого желания с тобой болтать. Не стой тут, иди дальше.";
				link.l1 = "Ладно.";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "Rivados_soldier";
		break;
//------------------------------------- фразы гардов пиратов --------------------------------------------	
		// у склада
		case "Shark_storage":
			if (CheckAttribute(pchar, "GenQuest.SharkConflict"))
			{
				dialog.text = LinkRandPhrase("Осторожно! Здесь больной псих с оружием! К бою!","Враг на территории! К бою!","Ах ты, гнусный негодяй! Сейчас мы тебе надерем место пониже спины!");
				link.l1 = "А-ать!";
				link.l1.go = "shark_guard_fight";
				break;
			}
			dialog.text = "Стой! Сюда вход запрещён!";
			link.l1 = "Хорошо, как скажешь...";
			link.l1.go = "exit";
			NextDiag.TempNode = "Shark_storage";
		break;
		
		// у резиденции
		case "Shark_residence":
			if (CheckAttribute(pchar, "GenQuest.SharkConflict"))
			{
				dialog.text = LinkRandPhrase("Осторожно! Здесь больной псих с оружием! К бою!","Враг на территории! К бою!","Ах ты, гнусный негодяй! Сейчас мы тебе надерем место пониже спины!");
				link.l1 = "А-ать!";
				link.l1.go = "shark_guard_fight";
				break;
			}
			if (stf(environment.time) >= 6.00 && stf(environment.time) < 21.00)
			{
				if (pchar.questTemp.LSC == "begin" || pchar.questTemp.LSC == "mary") // тока прибыл
				{
					dialog.text = "Стой! Ты не из наших людей... Акула назначил тебе встречу, или ты просто так припёрся?";
					link.l1 = "Акула?! Стивен Додсон-Акула?";
					link.l1.go = "first_talk_day";
				}
				else
				{
				dialog.text = "Если ты к адмиралу - проходи, он примет тебя.";
				link.l1 = "Спасибо!";
				link.l1.go = "exit";
			}
			}
			else
			{
				if (pchar.questTemp.LSC == "begin" || pchar.questTemp.LSC == "mary") // тока прибыл
				{
					dialog.text = "Куда ломишься? Не видишь - ночь на дворе! Или ты думаешь, что адмирал встанет с койки, чтобы тебя лично поприветствовать? Приходи утром.";
					link.l1 = "Хорошо, как скажешь. А где переночевать-то можно?";
					link.l1.go = "first_talk_night";
				}
			else
			{
				dialog.text = "Уже поздно, адмирал никого не принимает. Приходи завтра.";
				link.l1 = "Хорошо...";
				link.l1.go = "exit";
			}
			}
			NextDiag.TempNode = "Shark_residence";
		break;
		
		case "Shark_soldier":
			if (CheckAttribute(pchar, "GenQuest.SharkConflict"))
			{
				dialog.text = LinkRandPhrase("Осторожно! Здесь больной псих с оружием! К бою!","Враг на территории! К бою!","Ах ты, гнусный негодяй! Сейчас мы тебе надерем место пониже спины!");
				link.l1 = "А-ать!";
				link.l1.go = "shark_guard_fight";
				break;
			}
			dialog.text = "Адмирал будет недоволен, если увидит, что я болтаю на посту. Проходи.";
			link.l1 = "Ладно...";
			link.l1.go = "exit";
			NextDiag.TempNode = "Shark_soldier";
		break;
		
		case "first_talk_night":
			dialog.text = NPCStringReactionRepeat("Ты что, с луны свалился, или перепил? Разворачивайся назад и топай по висячему мосту, пройди прямо через два корабля - найдешь ещё одни висячие мостки, они приведут тебя к таверне. Там и спи себе до утра.", 
				"Ты что, издеваешься? Я же только что тебе объяснял. Проваливай!", 
				"Иди проспись, пьяная рожа...",
				"Пошел вон!!", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Спасибо, сударь. Хотя мог бы и повежливее...", 
				"Прости, забыл...",
				"Да не пьяный я!", 
				"Что?!", npchar, Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("exit", "", "", "", npchar, Dialog.CurrentNode);
		break;
		
		case "first_talk_day":
			dialog.text = "Не делай круглые глаза, парень. Каждый дурак на этом острове знает, что Стив Акула - наш адмирал. У тебя к нему дело?";
			link.l1 = "Да, чёрт побери! У меня к нему дело, и очень срочное.";
			link.l1.go = "first_talk_day_1";
		break;
		
		case "first_talk_day_1":
			dialog.text = "И какое же такое дело у тебя?";
			link.l1 = "Об этом я скажу Акуле лично. Я действую от лица Яна Свенсона, знаешь такого?";
			link.l1.go = "first_talk_day_2";
		break;
		
		case "first_talk_day_2":
			dialog.text = "Лесного Дьявола? Ха! Да его знает половина Мэйна... Слушай, парень, не ерепенься. Или объясни, зачем тебе понадобился Стив, или проваливай, пока я не рассердился. Акула сам сказал не пускать к нему кого попало, так что я просто выполняю приказ.";
			link.l1 = "Хорошо. Вот, посмотри на это письмо, оно от Лесного Дьявола, адресовано лично Акуле.";
			link.l1.go = "first_talk_day_3";
		break;
		
		case "first_talk_day_3":
			PlaySound("interface\important_item.wav");
			dialog.text = "(рассматривает)... Хорошо. Думаю, Стиву это будет интересно. Проходи.";
			link.l1 = "Ну неужели? Верни письмо, если тебя это не затруднит.";
			if (pchar.questTemp.LSC == "mary") link.l1.go = "first_talk_day_5";
			else link.l1.go = "first_talk_day_4";
		break;
		
		case "first_talk_day_4":
			PlaySound("interface\important_item.wav");
			npchar.dialog.currentnode = "First time";
			DialogExit();
			LSC_OpenSanAvgustinDoors(); // открываем Сан-Августин
			LocatorReloadEnterDisable("LostShipsCity_town", "reload2", true); //закрываем кладовку со стороны моря
			pchar.quest.LSC_entry_pantry.over = "yes"; //снять прерывание на арест
			pchar.quest.LSC_findMary.over = "yes"; //снять прерывание на Мэри
			pchar.questTemp.LSC = "entrance"; //меняем флаг
			sld = characterFromId("Dodson");
			sld.dialog.currentnode = "entrance";
			// закрываем вход к Мэри
			LocatorReloadEnterDisable("LostShipsCity_town", "reload60", true);
			LocatorReloadEnterDisable("LostShipsCity_town", "reload61", true);
		break;
		
		case "first_talk_day_5":
			PlaySound("interface\important_item.wav");
			npchar.dialog.currentnode = "First time";
			DialogExit();
			LSC_OpenSanAvgustinDoors(); // открываем Сан-Августин
			sld = characterFromId("Dodson");
			sld.dialog.currentnode = "entrance";
		break;
		
		case "shark_guard_fight":
			DialogExit();
			LAi_SetGuardianType(NPChar);
			LAi_group_MoveCharacter(NPChar, "LSC_SHARK");
			LAi_group_Attack(NPChar, Pchar);
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
	}
}