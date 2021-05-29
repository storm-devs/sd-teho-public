// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
	ref FortChref;
	FortChref = GetFortCommander(NPChar.City);
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Что вы хотели? Спрашивайте.", "Я слушаю вас, что за вопрос?"), "Второй раз за день вы пытаетесь задать ворпос...", "В третий раз за день вы опять пытаетесь задать вопрос...",
                          "Да когда же это кончится?! У меня дел полно по управлению делами города, а ты все вопросы пытаешься задать!", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Я передумал"+ GetSexPhrase("","а") +"...", "Не сейчас, не место и не время..."), "Да, верно... Но не сейчас, позже...",
                      "Задам, задам... Только позже...", "Извините, " + GetAddress_FormToNPC(NPChar) + "...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			// Addon 2016-1 Jason пиратская линейка
			if (CheckAttribute(pchar, "questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "jewelry_6")
			{
				link.l1 = "Ваша светлость, я к вам по поводу находящегося ныне под арестом офицера Лопе Монторо...";
                link.l1.go = "Mtraxx";
			}
		break;
		
		case "Cupture_after":
            dialog.text = RandPhraseSimple("Вы уже все забрали. Что вам еще нужно?", "Неужели осталось еще что-то, что вы не прихватили?");
            link.l1 = RandPhraseSimple("Осматриваюсь напоследок...", "Проверяю, может забыл"+ GetSexPhrase("","а") +" что забрать...");
            link.l1.go = "exit";
            NextDiag.TempNode = "Cupture_after";
		break;
		
		case "Slavetrader_HavanaAttack":
			dialog.text = "Чертовы ладроны! Посметь напасть на Гавану - это неслыханная дерзость! Что вам нужно?!";
			link.l1 = "Подумай хорошенько - поймешь.";
			link.l1.go = "Slavetrader_HavanaAttack_1";
			pchar.quest.Slavetrader_HavanaOver.over = "yes";
			AfterTownBattle();
        break;
		
		case "Slavetrader_HavanaAttack_1":
			dialog.text = "Золото, конечно! Что вам, проклятым, кроме золота еще может быть нужно? Да только нет у нас его... Разве что те жалкие несколько мер, что лежат на складе магазина?";
			link.l1 = "Хе-хе... Нет, мы не за золотом. Мы пришли за слоновой костью... черной слоновой костью. Ты понял, о чем я толкую?";
			link.l1.go = "Slavetrader_HavanaAttack_2";
        break;
		
		case "Slavetrader_HavanaAttack_2":
			if (CheckAttribute(FortChref, "Fort.Mode") && sti(FortChref.Fort.Mode) != FORT_DEAD)//для особо хитрых - нефиг лезть с суши
			{
				dialog.text = "Ха-ха! Я подозревал, что именно рабы - ваша цель. Да только они находятся в форте. Сейчас прибудет подкрепление, и от вашей банды не останется даже дырявой треуголки.";
				link.l1 = "Вот дьявол! Ладно, сиди тихо и не дергайся... Уходим! Проклятье...";
				link.l1.go = "Slavetrader_HavanaAttack_lose";
			}
			else
			{
				dialog.text = "Как... Как вы узнали об этом?";
				link.l1 = "Ха! Собрать пять тысяч рабов в одном месте и надеяться, что об этом никому не станет известно, может лишь полный идиот. Да от них вонь стоит до самой Тортуги... Как ты понимаешь, мы их забираем.";
				link.l1.go = "Slavetrader_HavanaAttack_3";
			}
        break;
		
		case "Slavetrader_HavanaAttack_3":
			dialog.text = "Ну что же, вы победили, и мы вынуждены подчиниться насилию. Но не думайте, что этот грабеж и потопление двух военных кораблей Испании сойдет вам с рук! Вы дорого заплатите за этот произвол!";
			link.l1 = "Не пыжься так сильно, удар хватит. Сиди тихо и не дергайся...";
			link.l1.go = "Slavetrader_HavanaAttack_4";
			ChangeCharacterHunterScore(pchar, NationShortName(sti(npchar.Nation)) + "hunter", 50);
			ChangeCharacterComplexReputation(pchar,"nobility", -8);
        break;
		
		 case "Slavetrader_HavanaAttack_4":
			string sTemp;
            NextDiag.CurrentNode = "Cupture_after";
			DialogExit();
			SetReturn_Gover_Dialog_Exit(NPChar);
            Statistic_AddValue(Pchar, NationShortName(sti(NPChar.nation)) + "_GrabbingTown", 1);
			pchar.quest.Slavetrader_DieHardHavana.over = "yes";//теперь можно на карту
            SetCharacterGoods(pchar, GOOD_SLAVES, 5000+rand(500));// c перегрузом пойдет
            Log_SetStringToLog("Рабы погружены на корабль");
			Log_SetStringToLog("У вас 30 дней на доставку рабов к работодателю");
			chrDisableReloadToLocation = false;
			sTemp = GetSquadronGoods(Pchar, GOOD_SLAVES);
			AddQuestRecord("Slavetrader", "27");
			AddQuestUserData("Slavetrader", "sQty", sTemp);
			SetFunctionTimerCondition("Slavetrader_FiveTSlavesOver", 0, 0, 30, false);	//таймер
			pchar.questTemp.Slavetrader = "Win_HavanaFort";
        break;
		
		case "Slavetrader_HavanaAttack_lose":
            NextDiag.CurrentNode = "Cupture_after";
			DialogExit();
			SetReturn_Gover_Dialog_Exit(NPChar);
			ChangeCharacterComplexReputation(pchar,"nobility", -8);
            Statistic_AddValue(Pchar, NationShortName(sti(NPChar.nation)) + "_GrabbingTown", 1);
			chrDisableReloadToLocation = false;
			pchar.quest.Slavetrader_DieHardHavana.over = "yes";//можно на карту
			pchar.quest.Slavetrader_HavanaAttack.over = "yes";//если из Сантьяго по суше пришел - уберем корабли
			AddQuestRecord("Slavetrader", "27_1");
			AddQuestUserData("Slavetrader", "sSex", GetSexPhrase("","а"));
			CloseQuestHeader("Slavetrader");
			pchar.questTemp.Slavetrader = "End_quest";
        break;
		
		// Addon 2016-1 Jason пиратская линейка
		case "Mtraxx":
            dialog.text = "Очень интересно... Еще одна жалоба?";
			link.l1 = "Нет, совсем наоборот, ваша светлость. Лопе - мой старый товарищ, мы не один фунт соли вместе съели на полях брани в Европе... Я бы хотел как-нибудь помочь ему. Вы не можете поспособствовать моим начинаниям?";
			link.l1.go = "Mtraxx_1";
		break;
		
		case "Mtraxx_1":
            dialog.text = "Хм... Ну, полагаю, раз вы пришли ко мне, то вы знаете всю эту... нелепую историю?";
			link.l1 = "Да, ваша светлость.";
			link.l1.go = "Mtraxx_2";
		break;
		
		case "Mtraxx_2":
            dialog.text = "Я вам рекомендую обратиться к дону Росарио Гусману. Он тоже, как и вы, жаждет помочь дону Лопе Монторо. Он уже пытался делать шаги в этом направлении - разговаривал с потерпевшей стороной, однако, как мне известно, переговоры успехом не увенчались. Идите к нему, он прояснит вам подробности. Найти дона Росарио вы можете в городе на улицах ежедневно, с четырех до восьми часов пополудни - в это время он обходит посты городской стражи.";
			link.l1 = "Спасибо, ваша светлость!";
			link.l1.go = "Mtraxx_3";
		break;
		
		case "Mtraxx_3":
            DialogExit();
			pchar.questTemp.Mtraxx = "jewelry_7";
			AddQuestRecord("Roger_1", "17");
			Mtraxx_CreateRosario();
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

