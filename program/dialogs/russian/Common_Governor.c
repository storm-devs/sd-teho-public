// boal 25/04/04 общий диалог Governor
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

    // вызов диалога по городам -->
    NPChar.FileDialog2 = "DIALOGS\" + LanguageGetLanguage() + "\Governor\" + NationShortName(sti(NPChar.nation)) + "_Governor.c";
    if (LoadSegment(NPChar.FileDialog2))
	{
        ProcessCommonDialog(NPChar, Link, NextDiag);
		UnloadSegment(NPChar.FileDialog2);
	}
    // вызов диалога по городам <--
    
    ref offref, sld;
    int i, cn;
    int qty;
    int iSumm;
    string attrLoc;

    /// выкуп колонии
    ref CaptGovenor, FortColony;
    int f, colony_money;

    int k = 1000;
    if (CheckAttribute(Nations[sti(NPChar.nation)], "Fort"))
    {
        k = (300 - sti(Nations[sti(NPChar.nation)].Fort)*10);
    }
	bool ok;
	
	attrLoc = Dialog.CurrentNode;
	if (findsubstr(attrLoc, "CityGive_" , 0) != -1)
 	{
        i = findsubstr(attrLoc, "_" , 0);
	 	NPChar.quest.CityIdx = strcut(attrLoc, i+1, strlen(attrLoc)-1); // индех в конце
 	    Dialog.CurrentNode = "ColonyGive";
 	}
 	
	switch (Dialog.CurrentNode)
	{
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOff");
		break;
		
		case "fight":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_group_Attack(NPChar, Pchar);
		break;
		
		case "First time":
            NextDiag.TempNode = "First time";
			if (LAi_grp_playeralarm > 0)
			{
       			dialog.text = NPCharRepPhrase(pchar, 
					LinkRandPhrase("Вы посмели явиться к генерал-губернатору?! Смелый шаг...", "Как эти бездельники допустили, чтобы ко мне ворвался враг?! Уму непостижимо...", "Да уж, моя охрана немногого стоит, раз "+ GetSexPhrase("какой-то бездельник","какая-то бездельница") +" бегает в моей резиденции..."), 
					LinkRandPhrase("Что тебе нужно, "+ GetSexPhrase("негодяй","негодяйка") +"?! Мои солдаты уже взяла твой след, далеко тебе не уйти, "+ GetSexPhrase("грязный пират","мерзавка") +"!", ""+ GetSexPhrase("Грязный","Грязная") +" убийца, вон из моей резиденции! Стража!!", "Я не боюсь тебя, "+ GetSexPhrase("мерзавец","мерзавка") +"! Скоро тебя повесят в форте, далеко тебе не уйти..."));
				link.l1 = NPCharRepPhrase(pchar,
					RandPhraseSimple("Солдатня мало чего стоит...", "Им меня ни за что не поймать."), 
					RandPhraseSimple("Заткни свою пасть, приятель, а не то вырву твой поганый язык!", "Вот что я тебе скажу, приятель: сиди тихо, и будешь жить..."));
				link.l1.go = "fight";
				break;
			}
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "Я слышал, что вы очень настойчиво просили аудиенции. Меня зовут " + GetFullName(npchar) +
                              ". Я генерал-губернатор колоний " + NationNameGenitive(sti(NPChar.nation))+ ", наместник короны " + NationKingsName(npchar)+
                              " в этих водах. А теперь соблаговолите сообщить цель вашего визита, " + GetAddress_Form(NPChar) + ".";
				link.l1 = "Мое имя " + GetFullName(pchar) + ".";
				link.l1.go = "node_1";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = RandPhraseSimple("А, это опять вы? По какому вопросу вам понадобился генерал-губернатор " + NationNameGenitive(sti(NPChar.nation))+ " на этот раз?",
                              "Опять отрываете меня от важных государственных дел? Что вам угодно, " +GetAddress_Form(NPChar)+"?");
				link.l1 = "Я хочу поговорить о работе на благо короны " + NationNameGenitive(sti(NPChar.nation));
				link.l1.go = "work";
				link.l2 = "Нужно поговорить с вами об одном деле.";
				link.l2.go = "quests"; // файл нации
				//Jason --> Регата
				if (CheckAttribute(pchar, "questTemp.Regata.ToPortRoyal") && NPChar.location == "Portroyal_townhall")
				{
					link.l3 = "Я прибыл по приглашению для участия в регате. Вот мое приглашение.";
					link.l3.go = "Regata";
				}
				//<-- Регата
				link.l10 = "Прошу простить, но меня ждут дела.";
				link.l10.go = "exit";
			}
		break;
		
		case "node_1":
			dialog.text = "Так какая причина заставила вас прийти сюда и отвлекать меня от важных государственных дел?";
			link.l1 = "Я хочу поговорить о работе на благо короны " + NationNameGenitive(sti(NPChar.nation));
			link.l1.go = "work";
			link.l2 = "Нужно поговорить с вами об одном деле.";
			link.l2.go = "quests";
			//Jason --> Регата
			if (CheckAttribute(pchar, "questTemp.Regata.ToPortRoyal") && NPChar.location == "Portroyal_townhall")
			{
				link.l3 = "Я прибыл по приглашению для участия в регате. Вот мое приглашение.";
				link.l3.go = "Regata";
			}
			//<-- Регата
			link.l10 = "Это просто визит вежливости и ничего более, "+GetAddress_FormToNPC(NPChar);
			link.l10.go = "node_2";
		break;

		case "node_2":
			dialog.text = "В таком случае, я попрошу вас покинуть мой кабинет и не мешать мне работать.";
			link.l1 = "Да, да, конечно, извините, что потревожил"+ GetSexPhrase("","а") +" вас.";
			link.l1.go = "exit";
		break;
		
		case "work":
            dialog.text = "По поводу работы обращайтесь к губернаторам колоний. Им частенько требуются сметливые и толковые капитаны.";
			link.l1 = "Приму к сведению. Спасибо.";
			link.l1.go = "exit";
		break;
		
		//--> Jason регата
		case "Regata":
			dialog.text = "А-а, замечательно, рад вас видеть, капитан! Вы пришли вовремя, регата стартует через несколько дней. Вы прочли о правилах регаты в письме, переданном вам вестовым?";
			link.l1 = "Да, сэр, прочел.";
			link.l1.go = "Regata_1";
			RemoveItems(PChar, "letter_open", 1);//уберем письмо
			TakeNationLicence(HOLLAND);//уберем лицензию
			DeleteAttribute(pchar, "questTemp.Regata.ToPortRoyal"); // patch-5
		break;
		
		case "Regata_1":
			dialog.text = "Итак, вы приготовили 50 000 песо - взнос в призовой фонд?";
			if (makeint(Pchar.money) >= 50000)
			{
				link.l1 = "Да, конечно. Вот, примите мой взнос.";
				link.l1.go = "Regata_2";
			}
			link.l2 = "У меня сейчас недостаточно денег. Но я обязательно принесу их.";
			link.l2.go = "Regata_nomoney";
		break;
		
		case "Regata_2":
			dialog.text = "Очень хорошо. Если вы победите - ваши деньги вернутся к вам, причем в пятикратном размере. Теперь вам нужно получше ознакомиться с правилами регаты\nВсе подробности узнаете у сэра Генри Стивенсона, он должен находиться в комнате резиденции. Пройдите к нему - он вам все объяснит.";
			link.l1 = "Хорошо. Я так и сделаю.";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, -50000);
			pchar.quest.Regata_Guber.win_condition.l1 = "location";
			pchar.quest.Regata_Guber.win_condition.l1.location = "Portroyal_Roomtownhall";
			pchar.quest.Regata_Guber.function = "PrepareToRegataInPortroyal";
			pchar.questTemp.Regata.Begin = "true";
			NextDiag.TempNode = "First time";
		break;
		
		case "Regata_nomoney":
			dialog.text = "Хорошо. Но только не затягивайте с этим, капитан. Регате скоро будет дан старт.";
			link.l1 = "Я понимаю. Буду у вас на приеме, с деньгами, как можно скорее.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Regata_1";
			pchar.questTemp.Regata.nomoney = "true";
		break;
		
		//регата-финал
		case "Regata_Final":
			dialog.text = "А, вот и победитель регаты! Добрый день, капитан " + GetFullName(pchar) + "! Поздравляю вас с этим значительным успехом - победители нашей регаты всегда пользуются заслуженной популярностью в английских колониях. ";
			link.l1 = "Спасибо за поздравление, сэр!";
			link.l1.go = "Regata_complete";
		break;
		
		case "Regata_complete":
			dialog.text = "Теперь перейдем к самой приятной для вас части - получению награды. Итак, денежное вознаграждение за победу составляет 250 000 песо. Извольте получить!";
			link.l1 = "Благодарю!";
			link.l1.go = "Regata_complete_1";
		break;
		
		case "Regata_complete_1":
			AddMoneyToCharacter(pchar, 250000);
			int iGift;
			string sItem1, sItem2, sItem3, sAdd;
			if (sti(pchar.rank) < 6) iGift = 0;
			if (sti(pchar.rank) >= 6 && sti(pchar.rank) < 13) iGift = 1;
			if (sti(pchar.rank) >= 13 && sti(pchar.rank) < 20) iGift = 2;
			if (sti(pchar.rank) > 20) iGift = 3;
			switch (iGift)
			{
				case 0:
					sItem1 = "blade_10";//корд
					sItem2 = "cirass6";
					sItem3 = "bussol";
					sAdd = "корд, жилет бретера и буссоль";
				break;
				
				case 1:
					sItem1 = "blade_15";//маринера
					sItem2 = "cirass2";//рейтарский панцирь
					sItem3 = "bussol";
					sAdd = "маринера, рейтарский панцирь и буссоль";
				break;
				
				case 2:
					sItem1 = "blade_17";//бретта
					sItem2 = "cirass7";//карацена
					sItem3 = "bussol";
					sAdd = "бретта, карацена и буссоль";
				break;
				
				case 3://
					sItem1 = "blade_20";//мадонна
					sItem2 = "cirass2";//офицерская кираса
					sItem3 = "bussol";
					sAdd = "'мадонна', офицерская кираса и буссоль";
				break;
			}
			GiveItem2Character(pchar, sItem1);
			GiveItem2Character(pchar, sItem2);
			GiveItem2Character(pchar, sItem3);
			dialog.text = "Также вам положен комплект ценных призов: "+sAdd+". Теперь все это - ваше.";
			link.l1 = "Очень рад, сэр. Право, даже не ожидал.";
			link.l1.go = "Regata_complete_2";
		break;
		
		case "Regata_complete_2":
			dialog.text = "От лица всех жителей английских колоний благодарю вас за участие в регате, и еще раз поздравляю с победой! Если вы сделали ставку - самое время пойти к сэру Генри Стивенсону и получить свой выигрыш, если вы этого еще не сделали. Желаю вам удачи, капитан!";
			link.l1 = "Спасибо за теплые слова, сэр! В свою очередь благодарю вас за то, что дали мне возможность участвовать в этом великолепном мероприятии. А теперь разрешите откланяться.";
			link.l1.go = "Regata_complete_3";
		break;
		
		case "Regata_complete_3":
			DialogExit();
			NextDiag.CurrentNode = "First time";
		break;
		//<-- регата
	}
}