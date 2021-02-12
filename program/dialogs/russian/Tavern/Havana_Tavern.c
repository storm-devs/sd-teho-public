// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat("Все сплетни города "+ GetCityName(npchar.city) +" к вашим услугам. Что бы вы хотели узнать?",
                          "Мы только что поднимали это тему. Вы, вероятно, запамятовали...", "Сегодня вы уже третий раз говорите о каком-то вопросе...",
                          "Что ты "+ GetSexPhrase("заладил","заладила") +" как попугай одно и то же...", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Знаешь, " + NPChar.name + ", как-нибудь в следующий раз.", "Точно, "+ GetSexPhrase("забыл","забыла") +" что-то...",
                      "Да уж, действительно в третий раз...", "Да уж...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			if (CheckAttribute(pchar, "questTemp.Slavetrader") && pchar.questTemp.Slavetrader == "FindRatHavana")
            {
                link.l1 = "Послушай, не появлялся ли у вас в городе Франсуа Гонтьер? У него корвет '" + pchar.questTemp.Slavetrader.ShipName+ "', если что... ";
                link.l1.go = "Havana_ratT_1";
            }
			if (CheckAttribute(npchar, "quest.batabano"))
            {
                link.l1 = "Скажи, приятель, где мне найти дона Диего де Монтойя? Я опоздал? Он уже отплыл на Мэйн?";
                link.l1.go = "guardoftruth";
            }
			// калеуче
			if (CheckAttribute(pchar, "questTemp.Caleuche") && pchar.questTemp.Caleuche == "graveyard" && !CheckAttribute(npchar, "quest.caleuche"))
			{
				link.l1 = "Послушай, к вам в город не прибывал человек по имени Жоаким Мерриман? Немолодой сеньор, португалец, носит усы и эспаньолку, с пронзительным взглядом?";
				link.l1.go = "caleuche";
			}
		break;

		case "Havana_ratT_1":
			dialog.text = "А-а, этот мрачный тип? Да, заходил он ко мне, останавливался. Скажу тебе по секрету: он ходил на прием к самому дону Диего де Толедо. Подавал ходатайство на получение патента. Но что-то там у него не выгорело, и он убрался прочь.";
			Link.l1 = "А куда он отчалил, не в курсе? Я за ним уже с самого Порто Белло тянусь, да все никак найти не получается.";
			Link.l1.go = "Havana_ratT_2";
		break;
		
		case "Havana_ratT_2":
			dialog.text = "А зачем он тебе? Он чужаков боится - вечно прячется ото всех, как увидит вооруженного незнакомца - за шпагу хватается. Ходит только в сопровождении четырех охранников. Не от тебя ли он так бережется?";
			Link.l1 = "Господи, да что же это за наказание такое! Я что, похож"+ GetSexPhrase("","а") +" на наемн"+ GetSexPhrase("ого","ую") +" убийцу? Он мой приятель, я спешу передать ему новости, которые его весьма и весьма обрадуют, да и не надо ему уже прятаться - никто его не ищет.";
			Link.l1.go = "Havana_ratT_3";
		break;
		
		case "Havana_ratT_3":
			dialog.text = "Не надо? Ха-ха-ха! Да только за день до его отбытия из Гаваны в джунглях на него целая свора оборванцев накинулась... Ну, он со своими людьми, правда, их мигом в капусту покрошил. А ты говоришь...";
			Link.l1 = "Брось. Вероятно, местные бандиты на кошель его позарились. Сам знаешь, сколько сейчас отребья по джунглям шастает. Так куда он отправился?";
			Link.l1.go = "Havana_ratT_4";
		break;
		
		case "Havana_ratT_4":
			dialog.text = "Ну, после того как ему дали у нас от ворот поворот, он бубнил, что к лягушатникам, своим соотечественникам, подастся. На Тортугу он отправился... Что-то он еще про любовницу свою бормотал, да я так и не понял толком.";
			Link.l1 = "На Тортугу, значит? Отлично! Надеюсь, хоть там я его догоню. Спасибо тебе, " + npchar.name + ", ты мне здорово помог. Бывай.";
			Link.l1.go = "exit";
			AddQuestRecord("Slavetrader", "21_7");
			pchar.questTemp.Slavetrader = "FindRatTortuga";
			pchar.quest.Slavetrader_findTortugaRat.win_condition.l1 = "location";
            pchar.quest.Slavetrader_findTortugaRat.win_condition.l1.location = "Tortuga_HouseHut";
            pchar.quest.Slavetrader_findTortugaRat.win_condition = "Slavetrader_findTortugaRat";
		break;

		case "guardoftruth":
			dialog.text = "Хм... а с чего бы это французы заинтересовались доном Диего, а?";
			link.l1 = "То, что я француз - значения не имеет. А имеет значение вот эта грамота, подписанная инквизитором. Смотри... теперь понимаешь? У меня для Диего срочная депеша.";
			link.l1.go = "guardoftruth_1";
		break;
		
		case "guardoftruth_1":
			dialog.text = "А-а, так вы работаете на Его Преосвященство отца Винсенто? Конечно, это меняет дело. Дон Диего де Монтойя отбыл в составе эскадры на Мэйн еще два дня назад, однако вскоре вернулся в порт на курьерском люггере. Один из кораблей эскадры умудрился сесть на рифы где-то у южной оконечности Кубы, так он закупал доски и прочие материалы для ремонта, вот только сегодня\nТак что поищите хорошенько в бухте на юге - там должен быть и корабль, и сам дон Диего. Не думаю, что они успели так быстро залатать пробоины.";
			link.l1 = "Спасибо, приятель! Ты мне очень помог!";
			link.l1.go = "guardoftruth_2";
		break;
		
		case "guardoftruth_2":
			dialog.text = "Да не за что, обращайтесь. Всегда рад помочь братьям-иезуитам.";
			link.l1 = "...";
			link.l1.go = "guardoftruth_3";
		break;
		
		case "guardoftruth_3":
			DialogExit();
			DeleteAttribute(npchar, "quest.batabano");
			AddQuestRecord("Guardoftruth", "47");
			pchar.quest.GuardOT_Batabano.win_condition.l1 = "location";
			pchar.quest.GuardOT_Batabano.win_condition.l1.location = "Shore13";
			pchar.quest.GuardOT_Batabano.function = "GuardOT_SanAntonioPrepare";
		break;
		
		// калеуче
		case "caleuche":
			dialog.text = "Черт его знает, дружище. Может, и прибывал, да вот только я о нем ничего не знаю. Уж извини.";
			link.l1 = "Ясно. Жаль. Буду искать дальше...";
			link.l1.go = "exit";
			npchar.quest.caleuche = "true";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

