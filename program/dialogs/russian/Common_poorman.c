#include "DIALOGS\russian\Rumours\Common_rumours.c"
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	ProcessCommonDialogRumors(NPChar, Link, NextDiag);//homo 25/06/06

	switch(Dialog.CurrentNode)
	{
		case "First time":
			// --> калеуче
			if (CheckAttribute(pchar, "questTemp.Caleuche.SeekAmulet") && drand(1) == 0 && sti(Pchar.money) >= 2000) 
			{
				dialog.text = "Послушайте, господин, не желаете приобрести одну занятную вещицу? Недорого возьму, всего каких-то пару тысяч песо...";
				link.l1 = "Хм. Небось, стащил эту 'вещицу', а теперь пытаешься мне сбагрить?";
				link.l1.go = "caleuche";
				break;
			}
			// <-- калеуче
			if (npchar.quest.meeting == "0")
			{
				dialog.text = LinkRandPhrase("Здравствуйте. Меня зовут " + GetFullName(npchar) + ". Не думаю, что вам было бы приятно со мной познакомиться, но, возможно, вы запомните мое имя...", 
					"Приветствую вас, " + GetAddress_Form(NPChar) +  ". Меня зовут " + GetFullName(npchar) + ".", 
					"Мое имя - " + GetFullName(npchar) + ", " + GetAddress_Form(NPChar) + ". Рад с вами познакомиться.");
				link.l1 = RandPhraseSimple("Приветствую.", "Здравствуйте.");
				link.l1.go = "First time";
				// карибские нравы
				if (CheckAttribute(pchar, "questTemp.Trial") && pchar.questTemp.Trial == "spy_drink" && pchar.location == "portobello_town")
				{
					link.l2 = "Послушай, не хочешь ли вместо жалкой милостыни заработать пару-тройку тысяч песо, а?";
					link.l2.go = "trial";
				}
				npchar.quest.meeting = "1";
			}			
			else
			{
				dialog.text = NPCStringReactionRepeat("Эх, вот видишь, до чего докатился...", 
					"Жить подаянием непросто...", 
					"Хотелось бы мне вырваться из нищеты!",
					"Опять ты?..", "block", 1, npchar, Dialog.CurrentNode);

				link.l1 = HeroStringReactionRepeat("Вижу. Ну, ничего страшного.", 
					"Оно и понятно. На эти деньги не разгуляешься, поди...",
					"Тогда тебе нужно не протирать здесь штаны, а что-то делать для этого.", 
					"Ага. Неужели "+ GetSexPhrase("надоел","надоела") +"?", npchar, Dialog.CurrentNode);
				link.l1.go = DialogGoNodeRepeat("exit", "exit", "exit", "pester", npchar, Dialog.CurrentNode);
				link.l2 = RandPhraseSimple("Что тебе нужно?", "Чего ты хочешь?");
				link.l2.go = "Whants";
				// карибские нравы
				if (CheckAttribute(pchar, "questTemp.Trial") && pchar.questTemp.Trial == "spy_drink" && pchar.location == "portobello_town")
				{
					link.l2 = "Послушай, не хочешь ли вместо жалкой милостыни заработать пару-тройку тысяч песо, а?";
					link.l2.go = "trial";
				}
				link.l3 = LinkRandPhrase("Что-нибудь интересное мне расскажешь?", 
					"Что нового в городе?", "Эх, с удовольствием "+ GetSexPhrase("послушал","послушала") +" бы последние сплетни...");
				link.l3.go = "rumours_poor";
			}
			NextDiag.TempNode = "First time";
		break;
		case "pester":
			dialog.text = RandPhraseSimple("Да нет, почему сразу "+ GetSexPhrase("надоел","надоела") +"? Я не особо занят, как ты "+ GetSexPhrase("сам","сама") +" видишь...", 
				"Не "+ GetSexPhrase("надоел","надоела") +", но порядком "+ GetSexPhrase("утомил","утомила") +". Я хоть и нищий, но тоже человек.");
			link.l1 = "Хех, ясно...";
			link.l1.go = "exit";
		break;
		//выходы
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		//милостыня
		case "Whants":
			if (!CheckAttribute(npchar, "wants_date") || GetNpcQuestPastDayParam(npchar, "wants_date") >= 1 || bBettaTestMode)
    		{
				dialog.text = PCharRepPhrase("Хм, " + GetAddress_Form(NPChar) +  ", о вас ходят нехорошие слухи. Но я верю в людей, даже в таких, как вы. Я прошу дать мне денег на еду и питье, сжальтесь.",
					"Прошу вас, " + GetAddress_Form(NPChar) +  "! Не обойдите вниманием несчастного человека, подайте на пропитание...");
				link.l1 = RandPhraseSimple("Ничего тебе не дам.", "Обойдешься.");
				link.l1.go = "exit";
				Link.l2 = "Хорошо. И сколько тебе нужно денег?";
				Link.l2.go = "Whants_1";
			}
			else
			{
				dialog.text = PCharRepPhrase("От тебя? Ничего.", "Ничего не нужно, " + GetAddress_Form(NPChar) + ", спасибо.");
				link.l1 = RandPhraseSimple("Хм, ну ладно.", "Знать хорошо живется тебе, приятель.");
				link.l1.go = "exit";
			}
		break;
		case "Whants_1":
			dialog.text = "И от гроша ломаного не откажусь, " + GetAddress_Form(NPChar) + ". Сколько вам позволят ваши кошелек и милосердие...";
			Link.l1.edit = 2;			
			link.l1 = "";
			link.l1.go = "Whants_2";
		break;
		case "Whants_2":
			SaveCurrentNpcQuestDateParam(npchar, "wants_date");
			int iTemp = sti(dialogEditStrings[2]);
			if (iTemp <= 0 || sti(pchar.money) < iTemp)
			{
				dialog.text = "Грешно смеяться надо больными людьми...";
				link.l1 = "Ха-ха-ха, а ты что думал, юродивый, я тебе денег дам?!";
				link.l1.go = "exit";
				ChangeCharacterComplexReputation(pchar,"nobility", -2);
				break;
			}
			if (iTemp > 0 && iTemp <= 100)
			{
				dialog.text = "Спасибо за " + FindRussianMoneyString(iTemp) + ", " + GetAddress_Form(NPChar) + ". Я куплю хлеба на эти деньги...";
				link.l1 = "Давай, иди подкрепись, бродяга.";
				link.l1.go = "exit";
				pchar.money = sti(pchar.money) - iTemp;
				Achievment_SetStat(pchar, 41, 1);
			}
			if (iTemp > 100 && iTemp <= 500)
			{
				dialog.text = "Спасибо вам, " + GetAddress_Form(NPChar) + ". Этих денег мне хватит на неделю!";
				link.l1 = ""+ GetSexPhrase("Рад был","Рада была") +" помочь.";
				link.l1.go = "exit";
				OfficersReaction("good");
				pchar.money = sti(pchar.money) - iTemp;
				Achievment_SetStat(pchar, 41, 1);
			}
			if (iTemp > 500 && iTemp <= 1000)
			{
				dialog.text = "Благодарю вас, " + GetAddress_Form(NPChar) + ". Я всем расскажу о вашей доброте!";
				link.l1 = "Ну, это не обязательно...";
				link.l1.go = "exit";
				ChangeCharacterComplexReputation(pchar,"nobility", sti(iTemp/2000+0.5));
				pchar.money = sti(pchar.money) - iTemp;
				Achievment_SetStat(pchar, 41, 1);
			}
			if (iTemp > 1000 && iTemp <= 5000)
			{
				dialog.text = "Спасибо вам, досточтим"+ GetSexPhrase("ый","ая") +" " + GetAddress_Form(NPChar) + ". Да хранит вас Господь...";
				link.l1 = "Да, покровительство Господа мне не помешает уж точно!";
				link.l1.go = "exit";
				ChangeCharacterNationReputation(pchar, sti(NPChar.nation), sti(iTemp/10000+0.5));
				pchar.money = sti(pchar.money) - iTemp;
				Achievment_SetStat(pchar, 41, 1);
			}
			if (iTemp > 5000 && iTemp <= 10000)
			{
				dialog.text = "Спасибо вам, "+ GetSexPhrase("досточтимый","досточтимая") +" " + GetAddress_Form(NPChar) + ". Желаю вам удачи!";
				link.l1 = "Спасибо, приятель.";
				link.l1.go = "exit";
				AddCharacterExpToSkill(pchar, "Leadership", sti(iTemp/5000));
				AddCharacterExpToSkill(pchar, "Fortune", sti(iTemp/5000));
				pchar.money = sti(pchar.money) - iTemp;
				Achievment_SetStat(pchar, 41, 1);
			}
			if (iTemp > 10000)
			{
				dialog.text = "Послушайте, " + GetAddress_Form(NPChar) + ", вы в своем уме? Вы отдаете мне " + FindRussianMoneyString(iTemp) + "! Я не возьму такие деньги, чувствую, здесь какой-то подвох... Уходите!";
				link.l1 = "Ну, как знаешь...";
				link.l1.go = "exit";
			}
		break;
		
		case "trial":
			dialog.text = "Спрашиваете, сеньор! Конечно, хочу. А что для этого надо будет сделать? Вы же не просто так дадите мне деньги.";
			link.l1 = "Конечно, не просто так. Слушай внимательно. Я выполняю поручение самого губернатора. Его светлость считает, что кто-то на верфи намеренно задерживает выход его галеона, 'Алькантары', из доков. Особенно его подозрения укрепились после недавней поимки французского шпиона...";
			link.l1.go = "trial_1";
		break;
		
		case "trial_1":
			dialog.text = "";
			link.l1 = "Объяснения корабела его светлость уже слышал, однако сомневается в их достоверности. Нужно узнать, кто и почему саботирует работу. Отправляйся в доки, походи, поспрашивай у рабочих - какого черта 'Алькантара' до сих пор не готова к выходу в море...";
			link.l1.go = "trial_2";
		break;
		
		case "trial_2":
			dialog.text = "";
			link.l1 = "Тебя никто ни в чем не заподозрит, может, еще и табачком разживешься, а мне точно никто ничего не скажет - сразу поймут, на кого я работаю. Если узнаешь что-нибудь достойное внимания - получишь три тысячи песо. Месяц на свою 'работу' сможешь не выходить.";
			link.l1.go = "trial_3";
		break;
		
		case "trial_3":
			dialog.text = "Три тысячи песо? Досточтимый господин...";
			link.l1 = "Ты что, торгуешься? Если узнаешь имя того, по чьей вине работяги тянут кота за хвост - получишь еще две тысячи. Понял?";
			link.l1.go = "trial_4";
		break;
		
		case "trial_4":
			dialog.text = "Хорошо, сеньор. Задача, чай, не сложная - у меня есть старинные знакомые, которые стучат топорами на нашей верфи. Эх, а ведь когда-то я тоже был моряком. Вот помню, с десяток лет назад...";
			link.l1 = "Расскажешь свою историю потом. Встречаемся сегодня вечером после одиннадцати на пирсе. Теперь ступай.";
			link.l1.go = "trial_5";
		break;
		
		case "trial_5":
			chrDisableReloadToLocation = true;//закрыть локацию
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload5_back", "none", "", "", "OpenTheDoors", 10.0);
			LAi_RemoveLoginTime(npchar);
			pchar.questTemp.Trial = "spy_poorman";
			pchar.quest.trial_spy_poorman.win_condition.l1 = "Timer";
			pchar.quest.trial_spy_poorman.win_condition.l1.date.hour  = 23.00;
			pchar.quest.trial_spy_poorman.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 0);
			pchar.quest.trial_spy_poorman.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 0);
			pchar.quest.trial_spy_poorman.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 0);
			pchar.quest.trial_spy_poorman.function = "Trial_SetPoormanInPort";
			SetTimerCondition("Trial_ReturnPoormanNorm", 0, 0, 1, false);
			AddQuestRecord("Trial", "15");
		break;
		
		case "trial_6":
			dialog.text = "Добрый вечер, господин...";
			link.l1 = "Ну как, узнал что-нибудь?";
			link.l1.go = "trial_7";
		break;
		
		case "trial_7":
			dialog.text = "Узнал, сеньор, узнал. Правда, не совсем понимаю, как это вяжется с вашими словами... Вы деньги принесли? Пять тысяч песо?";
			if (sti(pchar.money) >= 5000)
			{
				link.l1 = "Не переживай. Вот твои монеты. Рассказывай.";
				link.l1.go = "trial_8";
			}
			else
			{
				link.l1 = "Сначала информация, потом деньги. Давай, не тяни время!";
				link.l1.go = "trial_fail";
			}
		break;
		
		case "trial_fail":
			dialog.text = "Вы пытаетесь меня надуть, сеньор! Не хотите платить деньги - узнавайте все сами. И даже не смейте хвататься за свою железяку - стражу позову!";
			link.l1 = "...";
			link.l1.go = "trial_fail_1";
		break;
		
		case "trial_fail_1":
			chrDisableReloadToLocation = true;//закрыть локацию
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload4_back", "none", "", "", "OpenTheDoors", 10.0);
			pchar.questTemp.Trial = "spy_fail";
			AddQuestRecord("Trial", "16");
			sld = characterFromId("Florian");
			sld.DeckDialogNode = "florian_failspy_5";
		break;
		
		case "trial_8":
			AddMoneyToCharacter(pchar, -5000);
			dialog.text = "Дело обстоит так. 'Алькантара' к выходу в море уже давно готова, но ее намеренно не ставят под погрузку, причем по приказу самого губернатора. Ну, это мне так сказали. А плотники сейчас делают всякую мелкую работу, которая на выход судна в море никак не влияет\nВсе ждут прихода какого-то барка из Картахены. Дело в том, что на 'Алькантаре' недостаточный, по мнению капитана, запас пороха. Вот и ждут, пока 'Пуэбла' привезет порох для 'Алькантары'\nНо всем это ожидание уже порядком надоело, так что если 'Пуэбла' не прибудет через три дня - 'Алькантара' отправится в путь и так...";
			link.l1 = "Да ну? И кто же тебе такое сказал? Имя?";
			link.l1.go = "trial_9";
		break;
		
		case "trial_9":
			dialog.text = "Да один из матросов 'Алькантары', Фелипе Дабиньо... Но никто из этого секрета не делал, да и сам господин губернатор приказал...";
			link.l1 = "Все ясно. Этого я и ожидал. Распустили языки, как бабы базарные! В городе орудуют французские шпионы, а каждый встречный-поперечный может узнать обо всех планах его светлости! Ох, и получит же этот Фелипе Дабиньо! И боцман 'Алькантары', за то, что распустил дисциплину на судне!";
			link.l1.go = "trial_10";
		break;
		
		case "trial_10":
			dialog.text = "А?.. Так вы что, все знали? Но зачем тогда?.. Я ни в чем не виноват! Вы сами попросили меня!";
			link.l1 = "Да ты-то можешь не переживать. Теперь мы знаем, что экипаж 'Алькантары' способен выболтать врагу любую информацию, даже секретную! Все, ты можешь идти. Благодарю за помощь! Ступай, трать свои деньги.";
			link.l1.go = "trial_11";
		break;
		
		case "trial_11":
			chrDisableReloadToLocation = true;//закрыть локацию
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload4_back", "none", "", "", "OpenTheDoors", 10.0);
			pchar.questTemp.Trial = "spy_win";
			AddQuestRecord("Trial", "17");
			sld = characterFromId("Florian");
			sld.DeckDialogNode = "florian_12";
		break;
		
		// --> калеуче
		case "Caleuche":
			dialog.text = "Помилуйте, добрый господин... Я ее выиграл намедни в кости у какого-то проезжего, думал - заговоренный целебный амулет, да прогадал: и хвори она не исцеляет, и рыночным барышникам неинтересна. А вот вы - моряк, капитан, человек ученый - глядишь, вам она и пригодилась бы\nДа для вас эти пара тысяч - сущий пустяк, а мне - кусок хлеба и глоток рому на месяц. Взгляните, господин...";
			link.l1 = "Ладно, показывай...";
			link.l1.go = "Caleuche_1";
		break;
		
		case "Caleuche_1":
			Log_Info("Вы получили странный амулет");
			PlaySound("interface\important_item.wav");
			dialog.text = "Вот...";
			link.l1 = "Так-так... Занятная вещица, согласен. Явно вывезена из индейских поселений. Хорошо, я забираю ее. Вот твоё серебро.";
			link.l1.go = "Caleuche_2";
		break;
		
		case "Caleuche_2":
			AddMoneyToCharacter(pchar, -2000);
			dialog.text = "Спасибо, милостивый господин! Надеюсь, эта вещь принесет вам удачу! Да хранит вас Господь!";
			link.l1 = "И тебе счастливо, приятель. Не спусти только все деньги за один раз в кабаке.";
			link.l1.go = "Caleuche_3";
		break;
		
		case "Caleuche_3":
			DialogExit();
			GiveItem2Character(pchar, "kaleuche_amulet1"); 
		break;
		// <-- калеуче
	}
}