// Соукинс в Пуэрто-Принсипе
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	switch(Dialog.CurrentNode)
	{
		// ----------------------------------- Диалог первый - первая встреча
		case "First time":
            dialog.text = "У тебя дело ко мне? Нет? Тогда "+ GetSexPhrase("вали отсюда","попрошу не отвлекать меня.") +"";
			link.l1 = "Уже ухожу.";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";


					if (npchar.city == sti(pchar.HeroParam.Location))
					{
						if(!CheckAttribute(PChar, "questTemp.pirateStartQuest"))
						{
							link.l2 = "Может какая работенка для меня найдется?";
							link.l2.go = "pirateStartQuest";
						}
						else
						{
							if(pchar.questTemp.pirateStartQuest == "3" && !CheckAttribute(PChar, "questTemp.pirateStartQuest.many"))
							{
								link.l2 = "Я выш"+ GetSexPhrase("ел","ла") +" на след, но мне нужны деньги - 30 000 песо, чтобы выманить крысу из норы.";
								link.l2.go = "pirateStartQuest_many";	
							}
							if(pchar.questTemp.pirateStartQuest == "3" && GetCharacterItem(pchar, "letter_open") > 0)
							{
								link.l2 = "Посмотри, что за письмо я наш"+ GetSexPhrase("ёл","ла") +" на трупе одного из контрабандистов.";
								link.l2.go = "pirateStartQuest_info_1";	
							}
							if(pchar.questTemp.pirateStartQuest == "5")
							{
								link.l2 = "Дело сделано. Норман Виго вместе со своей лоханкой отправился к морскому дьяволу.";
								link.l2.go = "pirateStartQuest_final";	
							}
						}
					}
		break;

 		case "Exit":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
		break;

		case "fight":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_group_Attack(NPChar, Pchar);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;

		//zagolski. начальный квест за пирата ===================================
		case "pirateStartQuest":
			dialog.text = "Хм... работёнка, говоришь? А это даже очень хорошо, что ты ко мне обратил"+ GetSexPhrase("ся","ась") +". Мне как раз нужен человек со стороны. Необходимо кое-что разузнать в соседнем поселении, а моих ребят там знают, как облупленных. Много денег не обещаю, но кое-что перепадет.";
			link.l1 = "Вот и славно. А что за дело?";
			link.l1.go = "pirateStartQuest_1";
			link.l2 = "Извини, за копейки я рисковать не буду. Прощай...";
			link.l2.go = "exit";
			pchar.questTemp.pirateStartQuest = "0";
		break;
		case "pirateStartQuest_1":
			dialog.text = "А дело в следующем - с месяц назад сговорился я с капитаном шхуны 'Сентблу' о доставке 200 рабов, чтобы продать их одному плантатору из соседнего поселения. Уже и сроки поджимать стали, и заказчик нервничать, и вот вчера мне сообщают, что эту шхуну видели в акватории острова. Но!.. капитан у меня не появился. А сегодня плантатор потребовал вернуть задаток и сказал, что рабов ему предложили в другом месте - хоть и дороже, но всю партию и сразу.";
			link.l1 = "И что? Я долж"+ GetSexPhrase("ен","на") +" в считанные дни раздобыть 200 рабов, чтоб ты не потерял задаток? И всё это за копейки?";
			link.l1.go = "pirateStartQuest_2";
		break;
		case "pirateStartQuest_2":
			dialog.text = "Нет, конечно. Разве я похож на идиота? Задаток я не верну в любом случае. Но мне нужны доказательства, что рабы, которых ему подсовывают - это и есть моя партия. А ты просто найдёшь тех, кто предложил ему новую сделку, и получишь свои 10 000 песо. Остальное моя забота. Ну что, берёшься?";
			link.l1 = "Берусь! А кто это может быть? Есть какие-то соображения?";
			link.l1.go = "pirateStartQuest_3";
			link.l2 = "Нет. Искать непонятно кого, непонятно где и всего за 10 000 - извини, не возьмусь.";
			link.l2.go = "exit";
		break;
		case "pirateStartQuest_3":
			dialog.text = "Если бы у меня был хоть намёк, я обошёлся бы и без твоих услуг. Они бы уже к ночи ловили кальмаров на живца. Но меня больше интересует другое - как они узнали о грузе 'Сентблу' и о моём заказчике? Уж очень всё быстро у них срослось. Смекаешь?";
			link.l1 = "Да, явно кто-то приторговывает сведениями.";
			link.l1.go = "pirateStartQuest_4";

			pchar.questTemp.pirateStartQuest = "1";
			pchar.questTemp.pirateStartQuest.City = npchar.city;
			pchar.questTemp.pirateStartQuest.Areal = GetArealByCityName(pchar.questTemp.pirateStartQuest.City);
			pchar.questTemp.pirateStartQuest.Name = GetFullName(npchar);

			AddQuestRecord("pSQ", "1");
			AddQuestUserData("pSQ", "sCity", XI_ConvertString("Colony" + pchar.questTemp.pirateStartQuest.City + "Gen"));
			AddQuestUserData("pSQ", "sName", pchar.questTemp.pirateStartQuest.Name);
		break;
		case "pirateStartQuest_4":
			dialog.text = "Вот! Вот его и ищу. Поэтому тихо прирезать конкурентов и вернуть рабов - в этом деле не главное. Мне нужен информатор, а вернее - его голова на вертеле. Теперь ты понимаешь, почему никто из моих об этом задании знать не должен? Пока я не выясню, кто продаёт информацию - подозревать буду каждого. А мне этого очень не хочется...";
			link.l1 = "Понятно... Значит, будем действовать тихо и не поднимать волну. Отправляюсь на поиски.";
			link.l1.go = "exit";
		break;

		case "pirateStartQuest_many":
			dialog.text = "Тридцать тысяч, говоришь? Это большая сумма... Могу дать только 5000 песо, больше у меня сейчас нет. Но если вздумаешь сбежать с ними - найду и повешу на ближайшем заборе! Со мной такие шутки не пройдут.";
			link.l1 = "Давай пять тысяч...";
			link.l1.go = "pirateStartQuest_many_1";
		break;
		case "pirateStartQuest_many_1":
			dialog.text = "Вот, держи. Жду результаты поиска.";
			link.l1 = "Всё будет в порядке.";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, 5000);
			pchar.questTemp.pirateStartQuest.many = "";
		break;

		//------------------------------------
		case "pirateStartQuest_info_1":
			dialog.text = "Ха! Отличная новость! Я был уверен, что ты с этим справишься. Ко мне попала весьма любопытная информация.";
			link.l1 = "Я работу свою выполнил"+ GetSexPhrase("","а") +". Хочу получить свои десять тысяч.";
			link.l1.go = "pirateStartQuest_info_2";
			TakeItemFromCharacter(pchar, "letter_open");
		break;
		case "pirateStartQuest_info_2":
			dialog.text = "Конечно, вот обещанная награда. Но ты не спеши, я хочу поручить тебе ещё одно дело\nПфайфер - это человек из команды Нормана Виго, который ходит на люггере 'Септима'. Я уверен, что Норман Виго и есть информатор, хотя он и из наших. Его недавно видели в акватории острова, твоя работа - отправить крысу к морскому дьяволу. В первый раз ты меня не подвёл"+ GetSexPhrase("","а") +", поэтому и сейчас хочу поручить это дело тебе. Заплачу 15 000 песо. Соглас"+ GetSexPhrase("ен","на") +"?";
			link.l1 = "Берусь! Считай, что предатель Норман Виго уже покойник.";
			link.l1.go = "pirateStartQuest_info_3";
			link.l2 = "Знаешь что, неохота мне в это ввязываться... Да и некогда. Извини, но я пас.";
			link.l2.go = "pirateStartQuest_info_noex";
			AddMoneyToCharacter(pchar, 10000);
		break;
		case "pirateStartQuest_info_noex":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			pchar.questTemp.pirateStartQuest = "0";
			CloseQuestHeader("pSQ");
		break;
		case "pirateStartQuest_info_3":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			pchar.questTemp.pirateStartQuest = "4";

			AddQuestRecord("pSQ", "7");
			AddQuestUserData("pSQ", "sName", pchar.questTemp.pirateStartQuest.Name);

			pchar.quest.zpq_seaBattle.win_condition.l1 = "location";
			pchar.quest.zpq_seaBattle.win_condition.l1.location = pchar.questTemp.pirateStartQuest.Areal;
			pchar.quest.zpq_seaBattle.function = "pirateStartQuest_seaBattle";
		break;

		case "pirateStartQuest_final":
			dialog.text = "Знаем-знаем. Мои люди наблюдали бой и уже доложили мне, как ты здорово управил"+ GetSexPhrase("ся","ась") +". Ну что ж, дело своё ты исправно сделал"+ GetSexPhrase("","а") +", вот обещанная награда в 15 000 песо. И спасибо тебе, здорово ты мне помог"+ GetSexPhrase("","ла") +".";
			link.l1 = "Всё в порядке, рад"+ GetSexPhrase(" был","а была") +" помочь! А теперь меня ждут дела, я и так здесь задержал"+ GetSexPhrase("ся","ась") +". До встречи!";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, 15000);
			pchar.questTemp.pirateStartQuest = "0";
			CloseQuestHeader("pSQ");
			group_DeleteGroup("pirateStartQuest_Smuggler_group");
		break;


	}
}
