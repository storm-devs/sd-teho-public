// общий диалог ростовщиков
#include "DIALOGS\russian\Rumours\Common_rumours.c"  //homo 25/06/06
void ProcessDialogEvent()
{
	ref NPChar, chr, sld;
	aref Link, NextDiag;
	string NPC_Area, sTemp, sTitle, sDepositType1, sDepositType2;
	int LoanSum, LoanInterest, LoanPeriod, LoanResult, iPastMonths, DepositSum, DepositInterest, DepositResult, iNum, iTemp, iTotalDublonQty;
	int iRes, iPer, iDep;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	string iDay, iMonth, s1;
	iDay = environment.date.day;
	iMonth = environment.date.month;
	string lastspeak_date = iday + " " + iMonth;

	NPC_Area = Npchar.City;
	sDepositType1 = NPC_Area + "_Type1";
	sDepositType2 = NPC_Area + "_Type2";
 
	if(!CheckAttribute(npchar, "quest.item_date"))
	{
		npchar.quest.item_date = "";
	} 
 
	// вызов диалога по городам -->
    NPChar.FileDialog2 = "DIALOGS\" + LanguageGetLanguage() + "\Usurer\" + NPChar.City + "_Usurer.c";
    if (LoadSegment(NPChar.FileDialog2))
	{
        ProcessCommonDialog(NPChar, Link, NextDiag);
		UnloadSegment(NPChar.FileDialog2);
	}
    // вызов диалога по городам <--
	ProcessCommonDialogRumors(NPChar, Link, NextDiag);//homo 16/06/06

	if (!CheckAttribute(npchar, "quest.trade_date"))
    {
        npchar.quest.trade_date = "";
    }
    if (!CheckAttribute(npchar, "quest.FindCitizenNoShip"))
    {
        npchar.quest.FindCitizenNoShip = 0;
    }

	switch(Dialog.CurrentNode)
	{
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "fight":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_group_Attack(NPChar, Pchar);
		break;
		
		case "First time":
			if (LAi_group_GetPlayerAlarm() > 0)
			{
				//--> работорговец
				if(pchar.questTemp.Slavetrader == "After_enterSoldiers" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
				{
					dialog.text = "Все, поторопитесь, " + pchar.name + ". А я здесь приберусь...";
					link.l1 = "Выхожу в море!";
					link.l1.go = "exit";
					break;
				}
				//<-- работорговец
			
       			dialog.text = NPCharRepPhrase(pchar, 
					LinkRandPhrase("В городе поднята тревога, тебя всюду ищут! На твоем месте я бы не стал здесь задерживаться.", "Вся городская стража рыщет по городу в поисках тебя. Я не идиот и разговаривать с тобой не буду!", "Беги, "+ GetSexPhrase("приятель","подруга") +", пока солдаты не сделали из тебя решето..."), 
					LinkRandPhrase("Что тебе нужно, "+ GetSexPhrase("негодяй","мерзавка") +"?! Городская стража уже взяла твой след, далеко тебе не уйти"+ GetSexPhrase(", грязный пират","") +"!", "Грязн"+ GetSexPhrase("ый","ая") +" убийца, вон из моего дома! Стража!!", "Я не боюсь тебя, мерзав"+ GetSexPhrase("ец","ка") +"! Скоро тебя повесят в нашем форте, далеко тебе не уйти..."));
				link.l1 = NPCharRepPhrase(pchar,
					RandPhraseSimple("Хех, тревога для меня не проблема...", "Им меня ни за что не поймать."), 
					RandPhraseSimple("Заткни свою пасть, " + GetWorkTypeOfMan(npchar, "") + ", а не то вырву твой поганый язык!", "Хех, " + GetWorkTypeOfMan(npchar, "") + ", а все туда же - пиратов ловить! Вот что я тебе скажу, приятель: сиди тихо и будешь жить..."));
				link.l1.go = "fight";
				break;
			}
		//Jason ---------------------------------------Бремя гасконца------------------------------------
			if (CheckAttribute(pchar, "questTemp.Sharlie.Lock") && pchar.location == "Fortfrance_bank")
			{
				dialog.text = "Вы что-то еще хотели, месье?";
				Link.l1 = "Мне нужна кое-какая информация... В общем, есть вопрос.";
				Link.l1.go = "quests";
				Link.l2 = "Как насчет небольшого кредита?";
				Link.l2.go = "sharlie_credit";
				Link.l3 = "Нет, пожалуй, ничего.";
				Link.l3.go = "exit";
				break;
			}			
		//<-- Бремя гасконца
			
			//--> работорговец
			if (pchar.questTemp.Slavetrader == "canTakeQuest" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				dialog.Text = "Ну, наконец-то ко мне заглянул"+ GetSexPhrase(" достойный капитан","а достойная леди") +", а не эти скудоумные обыватели, которые думают, что я их дублоны и гинеи высаживаю во внутреннем дворике банка и каждый месяц собираю урожай, чтоб выплачивать им проценты\nОни дрожат за каждый пенни, совершенно не подозревая, на какие ухищрения приходится идти бедному ростовщику, чтобы самому не умереть с голоду и еще дать им возможность купить гуся к рождеству.";
				Link.l1 = "Думаю, ваши вкладчики не обрадовались бы, услышав такие слова от человека, которому они доверяют свои сбережения.";
				Link.l1.go = "GiveTaskSlave";
				npchar.quest.slave = "current";//чтобы камнем не долбил
				break;
			}	
			
			if (pchar.questTemp.Slavetrader == "TakeShoreCap_end" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				dialog.Text = "...";
				Link.l1 = "Ну, старый хорек, сейчас тебе придется здорово постараться, чтобы объяснить мне все! На корабле в трюме вместо рабов меня поджидала целая рота солдат! Мне едва удалось справиться с ними! Я очень з"+ GetSexPhrase("ол","ла") +", так что поторопись с разъяснениями!";
				Link.l1.go = "Slaveshore_5";
				break;
			}	
			if (pchar.questTemp.Slavetrader == "Win_HavanaFort" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				dialog.Text = "А-а-а, вот и вы, наконец! По всему архипелагу уже ходят слухи о вашем дерзком налете. Рад вас видеть!";
				Link.l1 = "Я бы предпоч"+ GetSexPhrase("ел","ла") +" безвестность такой славе... Уж очень она опасная.";
				Link.l1.go = "Win_Havana_Fort";
				break;
			}	
			if (pchar.questTemp.Slavetrader == "Havana_seekslaves" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				dialog.Text = "Вы привезли пять тысяч рабов?";
				if (GetSquadronGoods(Pchar, GOOD_SLAVES) >= 5000)
				{
					Link.l1 = "Да, привез"+ GetSexPhrase("","ла") +". Они у меня в трюмах.";
					Link.l1.go = "Havana_Fort_yesA";
				}
				else
				{
					Link.l1 = "Нет, я еще работаю над этим.";
					Link.l1.go = "exit";
				}
				break;
			}	
			
			if (pchar.questTemp.Slavetrader == "End_quest_bad" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				dialog.Text = "Хм... Вы еще живы? Странно... Ну, думаю, это ненадолго. Солдаты! На помощь! Здесь бандит!";
				link.l1 = "Вот ведь гад!";
				link.l1.go = "exit";
				LAi_group_Attack(NPChar, Pchar);
				break;
			}
			
			if(pchar.questTemp.Slavetrader == "wait_6" && GetQuestPastDayParam("pchar.questTemp.Slavetrader_wait_6") > 6 && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				dialog.Text = "Добрый день. Меня зовут " + GetFullName(npchar) + ". Чем могу быть вам полезен?";
				link.l1 = "О! А что вы тут делаете, уважаемый?";
				link.l1.go = "Usurer_Escape";
				break;
			}
			//<-- работорговец
			// Addon-2016 Jason, французские миниквесты (ФМК)
			// ФМК-Гваделупа
			if(CheckAttribute(pchar, "questTemp.FMQG") && pchar.questTemp.FMQG == "killers" && npchar.location == "BasTer_bank")
			{
				dialog.Text = "...";
				link.l1 = "Ты что же это затеял, морда шакалья? Убийц по моему следу послал? Надумал рот мне заткнуть? Говори, каналья!";
				link.l1.go = "FMQG_x";
				break;
			}
			
			if(NPChar.quest.meeting == "0")
			{
				dialog.Text = LinkRandPhrase(LinkRandPhrase("Здравствуйте, "+GetAddress_Form(NPChar)+". Чем обязан? Мы с вами не знакомы?","Прошу вас, капитан, проходите! Будем знакомы, я "+GetFullName(npchar)+", здешний ростовщик.","Рад знакомству, "+GetAddress_Form(NPChar)+"! Я здешний ростовщик, и если вы по денежному вопросу, то вы зашли правильно."), LinkRandPhrase("Мы не встречались раньше, капитан? Я "+GetFullName(npchar)+", здешний ростовщик.","Прошу вас, капитан! Будем знакомы, я "+GetFullName(npchar)+", здешний ростовщик.","Здравствуйте, "+GetAddress_Form(NPChar)+". Я "+GetFullName(npchar)+", здешний ростовщик."), LinkRandPhrase("Будем знакомы, "+GetAddress_Form(NPChar)+", я "+GetFullName(npchar)+", скромный ростовщик, единственный в этом прекрасном городе.","Прошу вас, капитан! Желаете взять в долг, или напротив - отдать в рост ваши кровные?","Господин капитан! Я рад, что вы посетили мою скромную контору!"));
				link.l1 = RandPhraseSimple(LinkRandPhrase("Я тоже рад приветствовать вас. Вот, прогуливался по городу и решил заглянуть к вам.","Очень приятно, я "+GetFullName(pchar)+", будем знакомы.",""+GetFullName(pchar)+", капитан корабля "+pchar.ship.name+", рад знакомству. А у вас тут, как я понимаю, банк?"), RandPhraseSimple("Будем знакомы, я "+GetFullName(pchar)+". капитан корабля "+pchar.ship.name+".  Я вот решил заглянуть, познакомиться.","Ага, значит я зашел в местный банк? Рад знакомству, я "+GetFullName(pchar)+", капитан собственного корабля."));
				link.l1.go = "next";
				NPChar.quest.meeting = "1";
			}
			else
			{
				dialog.Text = pcharrepphrase(LinkRandPhrase(LinkRandPhrase("Кого я вижу! И что это вас сюда занесло, "+GetAddress_Form(NPChar)+"?","С чем пожаловали, капитан? Увы, ваша репутация делает вас не очень желанным клиентом...","Ага, к нам пожаловал очередной клиент! А я уж сперва подумал – грабители... Хе-хе, шучу я."),LinkRandPhrase("О! А вам тут что понадобилось, милейший? Здесь у меня банк, а не кабак...","Здравствуйте, капитан. Сразу должен предупредить вас – я очень разборчив в выборе клиентов.","Что вам угодно, "+GetFullName(pchar)+"? Надеюсь, вы помните, что ваша репутация не позволяет вам рассчитывать на крупный займ?"),LinkRandPhrase("Надеюсь, вы пришли сделать вклад, "+GetAddress_Form(NPChar)+"? Ибо насчет кредита договориться нам с вами будет непросто.","Капитан "+GetFullName(pchar)+", что вам угодно от скромного ростовщика? Увы, вряд ли я готов предоставить вам займ... разве что – принять на хранение ваши деньги.","Заходите, "+GetAddress_Form(NPChar)+". С прискорбием должен заметить, что вы сейчас не самый желанный клиент, но я не привык с порога отказывать, так что – проходите.")),LinkRandPhrase(LinkRandPhrase("Здравствуйте, господин "+GetFullName(pchar)+"! Если вы по делу, то я всегда готов помочь вам.","Приветствую вас, "+GetAddress_Form(NPChar)+". Одолжить наличность, или принять на хранение любую сумму – я всегда к вашим услугам.","Дорогой "+GetFullName(pchar)+"! Как я рад снова видеть вас! Что вам угодно?"),LinkRandPhrase("Капитан "+GetFullName(pchar)+"! Я всегда к вашим услугам – одолжить монет, или принять на хранение некую сумму?","Приветствую вас, капитан. Вы всегда желанный клиент - у вас прекрасная деловая репутация!","Добрый день, "+GetFullName(pchar)+". Я рад, что вы снова заглянули ко мне. Надеюсь, по выгодному делу?"),LinkRandPhrase("Добрый день, капитан! Что вам угодно? Хотите взять займ, или открыть вам кредит?","Капитан "+GetFullName(pchar)+"! Не угодно ли вам сделать вклад на выгодных условиях? Я всегда рад столь уважаемому клиенту.","Рад вас видеть снова, капитан! Сделать вклад, или открыть кредит – я всегда готов помочь вам.")));
				link.l1 = pcharrepphrase(RandPhraseSimple(LinkRandPhrase("Шутки в сторону, ростовщик, я пришел по делу.","Много болтаешь, дружок. Давай-ка перейдем к делам.","Деньги не пахнут, слышал такую умную фразу? Ну-ка, зажимай нос и переходи к делу."), LinkRandPhrase("Это так здесь встречают клиентов? Твое счастье, что я сегодня в добром настроении.","Ха! Вижу, здесь мне не рады? Ну, так я и не золотой дублон, чтобы тебе нравиться. И вообще, давай-ка к делу, меняла.","Эх, и поучил бы я тебя вежливости, дружок... да некогда мне. Займемся, пожалуй, мы с тобой денежными вопросами.")),
				RandPhraseSimple(LinkRandPhrase("Рад видеть старого знакомого!","К вам всегда приятно зайти, дружище. Ну что, перейдем к делам?","Очень рад, очень рад. Обсудим дела, дружище?"),LinkRandPhrase("Весьма рад новой встрече. Ну, что нового в финансовых морях-океанах?","Рад, что помните меня, любезный. Я тороплюсь, так что, может быть, сразу перейдем к делам?","Привет, старина! Рад снова видеть старых знакомых!")));
				link.l1.go = "next";
			}
			break;
			
			case "next":
			dialog.text = NPCStringReactionRepeat("Чем я могу вам помочь?", 
				"Что вы хотите на этот раз?", 
				"Хм... Что вы желаете?",
                "Эх, " + GetAddress_Form(npchar) + ", вы себе представить не можете, до чего порой бывают навязчивы клиенты..." , "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Ничем, я просто заш"+ GetSexPhrase("ел","ла") +" посмотреть и поговорить.", 
				"Опять я. И опять просто так поговорить решил"+ GetSexPhrase("","а") +".",
                "Ага, снова я. И снова без конкретного дела заш"+ GetSexPhrase("ел","ла") +" поговорить.", 
				"Да-а-а, тяжело приходится ростовщикам порой... А мне от вас ничего не нужно, просто поболтать хотел"+ GetSexPhrase("","а") +"...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			link.l2 = "Я хочу обсудить наши финансовые взаимоотношения.";
			link.l2.go = "LoanUsurer";//(на кредитный генератор)
			link.l3 = "Драгоценные камни, диковинные идолы - вот что меня интересует.";
			if (!isMultiObjectKnown("gold_dublon"))
			{
				link.l3.go = "items_0";
			}
			else
			{
				link.l3.go = "items_1";
			}	
			link.l4 = "Мне нужна кое-какая информация... В общем, есть вопрос.";
			link.l4.go = "quests";//(перессылка в файл города)
//Jason, генер почтового курьера 2 уровня
			if (CheckAttribute(PChar, "questTemp.WPU.Postcureer.LevelUp"))
			{
				if (pchar.questTemp.WPU.Postcureer.TargetPortmanID == npchar.id)
				{
					link.l12 = "Я доставил вам деловые бумаги из города "+XI_ConvertString("Colony"+pchar.questTemp.WPU.Postcureer.StartCity+"Gen")+".";
					link.l12.go = "Postcureer_LevelUp_ForAll";
				}
			}
			//квесты мэра, проникновение во враждебный город
  			if (CheckAttribute(pchar, "GenQuest.Intelligence") && pchar.GenQuest.Intelligence.SpyId == npchar.id && pchar.GenQuest.Intelligence == "") //квест мэра - на связь с нашим шпионом
			{
				link.l7 = RandPhraseSimple("Я здесь по поручению одного человека. Его зовут губернатор " + GetFullName(characterFromId(pchar.GenQuest.Intelligence.MayorId)) + ".", 
					GetFullName(characterFromId(pchar.GenQuest.Intelligence.MayorId)) + " прислал меня к вам. Я долж"+ GetSexPhrase("ен","на") +" кое-что забрать...");
				link.l7.go = "IntelligenceForAll";
			}
			if(CheckAttribute(pchar,"GenQuest.EncGirl") && pchar.GenQuest.EncGirl == "toLoverFather" && pchar.GenQuest.EncGirl.LoverFather == "usurer_keeper")
			{
				link.l9 = "Здравствуйте, я приш"+ GetSexPhrase("ел","ла") +" по приглашению вашего сына."; 
				link.l9.go = "EncGirl_4";
				pchar.quest.EncGirl_GetLoverFather.over = "yes";
			}	
			if (CheckCharacterItem(pchar, "CaptainBook") && !CheckAttribute(pchar, "questTemp.different.GiveShipLetters.speakUsurer"))
			{
				link.l10 = "Меня интересует, что представляет собой владелец этих документов.";
				link.l10.go = "ShipLetters_Usurer1";			
			}
			
			//--> семейная реликвия
			if (CheckAttribute(pchar, "GenQuest.Noblelombard") && npchar.city == pchar.GenQuest.Noblelombard.City && !CheckAttribute(npchar, "quest.noblelombard"))
			{
				link.l11 = "Я хочу поговорить по поводу долга вашего клиента по имени "+pchar.GenQuest.Noblelombard.Name+". Он отдал в залог свою семейную реликвию. Я представляю его интересы и уполномочен вести переговоры по вопросу возврата залога.";
				link.l11.go = "Noblelombard";			
			}
			if (CheckAttribute(pchar, "GenQuest.Noblelombard.Giveregard") && npchar.city == pchar.GenQuest.Noblelombard.City)
			{
				link.l11 = "Три месяца назад мы с вами встречались по поводу реликвии одного дворянина, по имени "+pchar.GenQuest.Noblelombard.Name+". Вы, наверное, помните? Он должен был открыть депозит на мое имя, на сумму "+FindRussianMoneyString(sti(pchar.GenQuest.Noblelombard.Regard))+"...";
				link.l11.go = "Noblelombard_5";			
			}
			//<-- семейная реликвия
			
			//-->работорговец
			if (pchar.questTemp.Slavetrader == "Seek_slaves" && pchar.questTemp.Slavetrader.UsurerId == npchar.id) 
			{
				link.l8 = "Я по поводу вашего поручения о поставке рабов.";
				link.l8.go = "Checkslaves";
				break;
			}
			if(pchar.questTemp.Slavetrader == "goaway" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "Здравствуйте, " + NPChar.name + ", я по поводу вашего поручения.";
				link.l8.go = "Takeslaves_4_lose";
				break;
			}
			if(pchar.questTemp.Slavetrader == "goaway_pinas" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "Здравствуйте, " + NPChar.name + ", я по поводу вашего поручения.";
				link.l8.go = "Pinas_lose";
				break;
			}
			if(pchar.questTemp.Slavetrader == "died" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "Здравствуйте, " + NPChar.name + ", я по поводу вашего поручения.";
				link.l8.go = "Takeslaves_4_win";
				break;
			}
			if(pchar.questTemp.Slavetrader == "wait" && GetQuestPastDayParam("pchar.questTemp.Slavetrader_wait") > 20 && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "Я приш"+ GetSexPhrase("ел","ла") +", как мы и договаривались. Что там насчет работенки?";
				link.l8.go = "Takeslaves_3";
				break;
			}
			if(pchar.questTemp.Slavetrader == "waitship" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "Как мы и договаривались, я приш"+ GetSexPhrase("ел","ла") +". Что там насчет работенки?";
				link.l8.go = "Takeslaves_3";
				break;
			}
			if(pchar.questTemp.Slavetrader == "wait_1" && GetQuestPastDayParam("pchar.questTemp.Slavetrader_wait_1") > 30 && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "Добрый день, " + npchar.name + ". Как ваши дела? Есть новое задание?";
				link.l8.go = "EscapeSlave";
				break;
			}
			if(pchar.questTemp.Slavetrader == "escapeslave_win" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "Ваше задание выполнено. Мне удалось разыскать беглых рабов, хоть это было и непросто.";
				link.l8.go = "Escape_slaves_win";
				break;
			}
			if(pchar.questTemp.Slavetrader == "wait_2" && GetQuestPastDayParam("pchar.questTemp.Slavetrader_wait_2") > 30 && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "Добрый день, " + npchar.name + ". Я приш"+ GetSexPhrase("ел","ла") +", как мы и договаривались, за очередным выгодным дельцем.";
				link.l8.go = "Slaveshore";
				break;
			}			
			
			if(pchar.questTemp.Slavetrader == "goodbye" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "У меня плохие новости, " + npchar.name + ". Мне не удалось захватить бригантину.";
				link.l8.go = "Brig_lose";
				break;
			}
			if(pchar.questTemp.Slavetrader == "goodbye_1" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "Послушай, " + npchar.name + ". Я настиг"+ GetSexPhrase("","ла") +" бригантину, но никаких бумаг не наш"+ GetSexPhrase("ел","ла") +". Ты уверен, что они там были?";
				link.l8.go = "Letter_lose";
				break;
			}
			if(pchar.questTemp.Slavetrader == "winbrig" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "У меня хорошие новости, " + npchar.name + ". Мне удалось настичь бригантину и достать бумаги. Вот они.";
				link.l8.go = "Brig_win";
				break;
			}
			if(pchar.questTemp.Slavetrader == "wait_3" && GetQuestPastDayParam("pchar.questTemp.Slavetrader_wait_3") > 30 && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "Добрый день, " + npchar.name + ". Ну как, вы уже подготовили для меня новое дело?";
				link.l8.go = "SlaveGalleon";
				break;
			}
			if(pchar.questTemp.Slavetrader == "wingalleon" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "" + npchar.name + ", мне удалось перехватить ваш так называемый 'галеон'.";
				link.l8.go = "Wingalleon";
				break;
			}
			if(pchar.questTemp.Slavetrader == "lostgalleon" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "" + npchar.name + ", мне очень жаль, но я не смог"+ GetSexPhrase("","ла") +" захватить этот галеон.";
				link.l8.go = "Lostgalleon";
				break;
			}
			if(pchar.questTemp.Slavetrader == "wait_4" && GetQuestPastDayParam("pchar.questTemp.Slavetrader_wait_4") > 4 && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "Добрый день, " + npchar.name + ". Я приш"+ GetSexPhrase("ел","ла") +" за своими деньгами.";
				link.l8.go = "FindRat";
				break;
			}
			if(pchar.questTemp.Slavetrader == "wincorvette" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "" + npchar.name + ", твое задание выполнено. Мерзавец Гонтьер мертв, как и вся его команда.";
				link.l8.go = "Wincorvette";
				break;
			}
			if(pchar.questTemp.Slavetrader == "lostcorvette" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "" + npchar.name + ", мне очень жаль, я упустил"+ GetSexPhrase("","а") +" Франсуа Гонтьера, хотя вел"+ GetSexPhrase("","а") +" его до самой Тортуги. Но там ему удалось скрыться на своем корвете прямо у меня из-под носа.";
				link.l8.go = "lostcorvette";
				break;
			}
			if(pchar.questTemp.Slavetrader == "wait_5" && GetQuestPastDayParam("pchar.questTemp.Slavetrader_wait_5") > 30 && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "Добрый день, " + npchar.name + ". Ну, рассказывайте, что за горячее дело вы мне приготовили.";
				link.l8.go = "Havana_fort";
				break;
			}
			//<--работорговец
			NextDiag.TempNode = "First time";
		break;

		case "items_0":
			dialog.text = "Не хотите ли прикупить золотых дублонов и сундучков для их хранения? Поверьте - это очень ценное вложение ваших капиталов.";
			link.l1 = "Да, это очень интересно.";
			link.l1.go = "items";
			AddQuestRecordInfo("Recipe", "Gold_dublon");
			SetAlchemyRecipeKnown("gold_dublon");
			SetAlchemyRecipeKnown("Chest");
			npchar.quest.meeting = "1"; 			
		break;
		
		case "items_1":
			dialog.text = "Вы хотели бы поторговаться за обычные песо или за дублоны?";
			link.l1 = "За песо.";
			link.l1.go = "items";
			link.l2 = "За дублоны.";
			link.l2.go = "items_dub";
		break;
		
		case "items":
			if (npchar.quest.item_date != lastspeak_date)
			{
				GiveItemToTrader(npchar);
				npchar.quest.item_date = lastspeak_date;
			}
			Nextdiag.CurrentNode = Nextdiag.TempNode;
			DialogExit();
			LaunchItemsTrade(NPChar, 0);
		break;
		
		case "items_dub":
			if (npchar.quest.item_date != lastspeak_date)
			{
				GiveItemToTrader(npchar);
				npchar.quest.item_date = lastspeak_date;
			}
			Nextdiag.CurrentNode = Nextdiag.TempNode;
			DialogExit();
			LaunchItemsTrade(NPChar, 1);
		break;
		
		//<<<<----------генератор -"Судовые документы". ------		
		case "ShipLetters_Usurer1":
			pchar.questTemp.different.GiveShipLetters.speakUsurer = true;
			dialog.text = "Чтобы ознакомиться подробно со всеми бумагами нужно много времени, а мое время стоит дорого.";
			link.l1 = "Может быть " + sti(pchar.questTemp.different.GiveShipLetters.price1) + " песо компенсируют Ваши труды?";
			link.l1.go = "ShipLetters_Usurer2";
			link.l2 = "Воля Ваша. Прощайте!";
			link.l2.go = "exit";
		break;
		
		case "ShipLetters_Usurer2":
			AddMoneyToCharacter(pchar, -sti(pchar.questTemp.different.GiveShipLetters.price1));
			pchar.questTemp.different.GiveShipLetters.speakUsurer_1 = true;
			if(sti(pchar.questTemp.different.GiveShipLetters.variant) == 0)
			{
				dialog.text = "Дайте-ка взглянуть! Нет, впервые вижу это имя. Покажите бумаги в портовом управлении.";
				link.l1 = "Позвольте, но мы же договорились, что вы расскажете мне об этом капитане!";
				link.l1.go = "ShipLetters_Usurer2_1";
			}
			if(sti(pchar.questTemp.different.GiveShipLetters.variant) == 1)
			{
				s1 = "Ну что же ... Я знаю владельца этого корабля. Он пусть и не самый богатый, но весьма обеспеченный человек. ";
				dialog.text = s1 + "поговаривают, что он уже давно и успешно торгует контрабандой. Не это ли вы хотели услышать ?";
				link.l1 = "Вас послушать, так можно сделать вывод ....";
				link.l1.go = "ShipLetters_Usurer2_2";
			}
			if(sti(pchar.questTemp.different.GiveShipLetters.variant) == 2)
			{
				s1 = "М-да.... даже и не знаю, повезло ли вам с находкой. ";
				dialog.text = s1 + "Документы оформлены на наш колониальный патрульный корабль, а его капитан известен своей принципиальностью и строгостью нравов.";
				link.l1 = "Патрульный? В ведении коменданта?";
				link.l1.go = "ShipLetters_Usurer2_3";
			}
		break;
		
		case "ShipLetters_Usurer2_1":
			dialog.text = "Мы договорились, что я посмотрю эти бумаги, не более того. Не смею вас больше задерживать.";
			link.l1 = "Спасибо и на этом...";
			link.l1.go = "exit";
		break;
		
		case "ShipLetters_Usurer2_2":
			dialog.text = "Делать выводы вам. Наш комендант давненько 'присматривается', вы догадываетесь к кому? А тут есть не помеченные таможней накладные...";
			link.l1 = "Догадываюсь. Спасибо, милейший!";
			link.l1.go = "exit";		
		break;
		
		case "ShipLetters_Usurer2_3":
			s1 = "Именно так. Кстати, на этого капитана имеют большой зуб местные контрабандисты. ";
			dialog.text = s1 + "Как я уже говорил, владелец этих бумаг весьма строг и не жалует нарушителей закона.";
			link.l1 = "Догадываюсь. Спасибо, милейший!";
			link.l1.go = "exit";		
		break;

		case "EncGirl_4":
			if(sti(pchar.GenQuest.EncGirl.LoverFatherAngry) == 0)
			{
				dialog.text = "А, так вы и есть "+ GetSexPhrase("тот капитан, который привёз","та девушка, которая привезла") +" моего блудного сына с молодой невестой?";
				link.l1 = "Да, это я помог"+ GetSexPhrase("","ла") +" им сбежать.";
				link.l1.go = "EncGirl_5";
			}
			else
			{
				dialog.text = "А-а, явил"+ GetSexPhrase("ся, благодетель","ась, благодетельница") +". Небось награды ждёшь?";
				link.l1 = "Ну, не то, чтобы награды, но благодарность услышать не мешало бы.";
				link.l1.go = "EncGirl_6";			
			}
		break;
		
		case "EncGirl_5":
			dialog.text = "Я очень вам благодарен, что не оставили моё чадо в затруднительном положении и помогли ему с честью выйти из столь щекотливой ситуации. Разрешите отблагодарить вас, как могу. Примите эту скромную сумму и подарок от меня лично.";
			link.l1 = "Благодарю вас, мне было приятно помогать этим молодым людям.";
			link.l1.go = "EncGirl_5_1";
		break;
		
		case "EncGirl_6":
			dialog.text = "Какая благодарность? за что благодарность? Мало того, что этот оболтус уже полгода слоняется без работы, так ещё и любезничать время нашёл! Да я в его годы уже своё дело держал. А он, ишь, разохотился! У губернатора, вон, дочка на выданье, а этот приволок какую-то шалаву безродную, прости Господи, и благословения родительского испрашивает!";
			link.l1 = "Хм, значит вы не верите в искренние чувства?";
			link.l1.go = "EncGirl_6_1";		
		break;
		
		case "EncGirl_5_1":
			AddMoneyToCharacter(pchar, sti(pchar.GenQuest.EncGirl.sum));
			GiveItem2Character(pchar, pchar.GenQuest.EncGirl.item); 
			AddQuestRecord("JungleGirl", "18");
			CloseQuestHeader("JungleGirl");
			DeleteAttribute(pchar, "GenQuest.EncGirl");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "EncGirl_6_1":
			dialog.text = "Какие такие чувства?! О каких чувствах вы говорите? Взрослый, вроде человек, а туда же... чувства! Стыдно вам должно быть молодёжи в таких делах потакать да в сводни подряжаться. Девчонку из родительского гнезда вырвали и моему молокососу жизнь сломали. Не будет вам никакой благодарности. Прощайте.";
			link.l1 = "Что ж, и вам не хворать...";
			link.l1.go = "EncGirl_6_2";
		break;
		
		case "EncGirl_6_2":
			ChangeCharacterComplexReputation(pchar,"nobility", -1);
			AddQuestRecord("JungleGirl", "19");
			AddQuestUserData("JungleGirl", "sSex", GetSexPhrase("ел","ла"));
			AddQuestUserData("JungleGirl", "sSex1", GetSexPhrase("","а"));
			CloseQuestHeader("JungleGirl");
			DeleteAttribute(pchar, "GenQuest.EncGirl");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();		
		break;
		
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////		Кредитный генератор Loan
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		case "LoanUsurer": 
			dialog.text = "Давайте обсудим. Внимательно вас слушаю.";
			//кредиты
            if(CheckAttribute(Pchar, "Quest.Loans." + (NPC_Area)) && makeint(Pchar.Quest.Loans.(NPC_Area)) == true)
			{
				iPastMonths = GetPastTime("Month", makeint(Pchar.Quest.Loans.(NPC_Area).StartYear),makeint(Pchar.Quest.Loans.(NPC_Area).StartMonth),makeint(Pchar.Quest.Loans.(NPC_Area).StartDay), makefloat(Pchar.Quest.Loans.(NPC_Area).StartTime), getDataYear(),getDataMonth(),GetDataDay(), GetTime());
				Pchar.Quest.Loans.(NPC_Area).Result = makeint(Pchar.Quest.Loans.(NPC_Area).Sum) + ((makeint(Pchar.Quest.Loans.(NPC_Area).Sum)/100)*makeint(Pchar.Quest.Loans.(NPC_Area).Interest))*(iPastMonths+1);// boal 23.01.2004
				if(makeint(PChar.money) >= makeint(Pchar.Quest.Loans.(NPC_Area).Result))
				{
					Link.l5 = "Я долж"+ GetSexPhrase("ен","на") +" вам "+ FindRussianMoneyString(sti(Pchar.Quest.Loans.(NPC_Area).Result)) + LinkRandPhrase(". Я готов"+ GetSexPhrase("","а") +" вернуть долг.", ". В данный момент я в состоянии выплатить вам долг.", ". Настало время, наконец, рассчитаться.");
					Link.l5.go = "loan_return";	
					sTemp = "credit";
				}					
			}
			else
			{
				Link.l6 = LinkRandPhrase("Я хочу занять денег.", "Мне срочно понадобилась пара-другая песо.", "Как насчет небольшого кредита?");
				Link.l6.go = "loan";					
				if(makeint(Pchar.money) >= 100)
				{
					Link.l7 = LinkRandPhrase("Я бы хотел"+ GetSexPhrase("","а") +" отдать деньги в рост.","Примете на хранение пару мешков монет?", "Серебришко на черный день оставить можно?"); // patch
					Link.l7.go = "deposit";				
				}			
				if(CheckUseDublons(NPChar))
				{
					Link.l8 = "Хочу сделать вклад в дублонах.";
					Link.l8.go = "deposit_dub";				
				}
			}
			
			if(CheckAttribute(Pchar, "Quest.Deposits." + (sDepositType1)) && makeint(Pchar.Quest.Deposits.(sDepositType1)) == true)
			{
				iPastMonths = GetPastTime("Month", makeint(Pchar.Quest.Deposits.(sDepositType1).StartYear),makeint(Pchar.Quest.Deposits.(sDepositType1).StartMonth),makeint(Pchar.Quest.Deposits.(sDepositType1).StartDay), makefloat(Pchar.Quest.Deposits.(sDepositType1).StartTime), getDataYear(),getDataMonth(),GetDataDay(), GetTime());
				if(CheckAttribute(Pchar, "Quest.Deposits." + (sDepositType1)+ ".Rem"))
				{
					Pchar.Quest.Deposits.(sDepositType1).Result = makeint(Pchar.Quest.Deposits.(sDepositType1).Sum) + ((makeint(Pchar.Quest.Deposits.(sDepositType1).Sum)/100)*makeint(Pchar.Quest.Deposits.(sDepositType1).Interest))*iPastMonths+sti(Pchar.Quest.Deposits.(sDepositType1).Rem);
				}
				else
				{
					Pchar.Quest.Deposits.(sDepositType1).Result = makeint(Pchar.Quest.Deposits.(sDepositType1).Sum) + ((makeint(Pchar.Quest.Deposits.(sDepositType1).Sum)/100)*makeint(Pchar.Quest.Deposits.(sDepositType1).Interest))*iPastMonths;
				}
				Link.l9 = LinkRandPhrase("Я хочу забрать свой вклад в песо.", "Пришло время забрать моё серебро, что у вас хранится.", "Мне нужен мой вклад в песо и набежавшие проценты.");
				Link.l9.go = "Deposit_return";									
			}
			
			if(CheckAttribute(Pchar, "Quest.Deposits." + (sDepositType2)) && makeint(Pchar.Quest.Deposits.(sDepositType2)) == true)
			{
				iPastMonths = GetPastTime("Month", makeint(Pchar.Quest.Deposits.(sDepositType2).StartYear),makeint(Pchar.Quest.Deposits.(sDepositType2).StartMonth),makeint(Pchar.Quest.Deposits.(sDepositType2).StartDay), makefloat(Pchar.Quest.Deposits.(sDepositType2).StartTime), getDataYear(),getDataMonth(),GetDataDay(), GetTime());
				if(CheckAttribute(Pchar, "Quest.Deposits." + (sDepositType2)+ ".Rem"))
				{
					Pchar.Quest.Deposits.(sDepositType2).Result = makeint(Pchar.Quest.Deposits.(sDepositType2).Sum) + ((makeint(Pchar.Quest.Deposits.(sDepositType2).Sum)/100)*makeint(Pchar.Quest.Deposits.(sDepositType2).Interest))*iPastMonths+sti(Pchar.Quest.Deposits.(sDepositType2).Rem);
				}
				else
				{
					Pchar.Quest.Deposits.(sDepositType2).Result = makeint(Pchar.Quest.Deposits.(sDepositType2).Sum) + ((makeint(Pchar.Quest.Deposits.(sDepositType2).Sum)/100)*makeint(Pchar.Quest.Deposits.(sDepositType2).Interest))*iPastMonths;
				}
				Link.l10 = LinkRandPhrase("Я хочу забрать свой вклад в дублонах.", "Пришло время забрать моё золото, что у вас хранится.", "Мне нужен мой вклад в дублонах и набежавшие проценты.");
				Link.l10.go = "Deposit_return_dub";									
			}
/*			
			
*/			
			//выход
			if (sTemp == "credit")
			{
				link.l11 = LinkRandPhrase("Я помню, что брал"+ GetSexPhrase("","а") +" у вас кредит, но рассчитатся пока не готов"+ GetSexPhrase("","а") +"...", "Я знаю, что долж"+ GetSexPhrase("ен","на") +" вам, но сейчас у меня нет денег. Верну позже...", "Я помню, что долж"+ GetSexPhrase("ен","на") +" вам, но в данный момент не имею достаточных средств для погашения кредита. Я сделаю это позже.");
				link.l11.go = "Loan_Remind";
			}
			else
			{
				link.l11 = "Я ошиб"+ GetSexPhrase("ся","лась") +", никаких финансовых дел у меня с вами нет. Прощайте.";
				link.l11.go = "exit";
			}
		break;
		
		//============== кредиты ===============
		case "loan":
            if (sti(NPChar.nation) == PIRATE)
            {
                dialog.text = "Нет, ничем не могу помочь. В нашем неспокойном месте я могу предложить только услуги хранения денег. Можно сделать вклад как в серебряных песо так и золотых дублонах";				
                if(makeint(Pchar.money) >= 100)
				{
	                Link.l1 = "Я хочу сделать вклад в песо и давайте определимся с суммой.";
	                Link.l1.go = "deposit";
				}				
				if(CheckUseDublons(NPChar))
				{
					Link.l2 = "Я хочу сделать вклад в дублонах. Давайте уточним сумму.";
					Link.l2.go = "deposit_dub";
				}
                Link.l3 = "Мне это не интересно.";
				link.l3.go = "exit";
                break;
            }
			// проверка на проф пригодность -->
            if (isBadReputation(pchar, 42))
            {
                dialog.text = RandSwear() + "Ты ведь " + GetFullName(pchar)+ ", не так ли? О тебе " +
                              RandPhraseSimple("ходят ужасные слухи","говорят не лучшим образом") + ", я не хочу иметь с тобой дело.";
				link.l1 = RandPhraseSimple("Эх.. стоит человеку оступиться, и все будут в него плевать.", RandSwear() + "Ну и не надо!");
				link.l1.go = "exit";
                break;
            }
            // проверка на проф пригодность <--
			dialog.text = "О, всегда пожалуйста. Какая сумма вам необходима?";
			Link.l1 = "Совсем небольшая.";
			Link.l1.go = "Small";
			Link.l2 = "Весьма значительная.";
			Link.l2.go = "Medium";
			Link.l3 = "Чем больше, тем лучше.";
			Link.l3.go = "Large";
		break;

		case "small":
			Pchar.Quest.Loans.(NPC_Area).Sum = 500*makeint(Pchar.rank);
			dialog.text = "Отлично. С небольшими суммами всегда проще - меньше риска. Я могу предложить вам " + FindRussianMoneyString(sti(Pchar.Quest.loans.(NPC_Area).sum)) + "...";
			Link.l1 = "Договорились. Под какие проценты?";
			Link.l1.go = "Interest";
			Link.l2 = "Увы, эта сумма не годится. Давайте-ка ее изменим.";
			Link.l2.go = "Loan";
			Link.l3 = "Думаю, мне лучше не влезать в долги. До свидания.";
			Link.l3.go = "ExitDelLoan1";
			Pchar.Quest.Loans.(NPC_Area).Interest = 22 - makeint((GetSummonSkillFromName(pchar, "Commerce")+GetSummonSkillFromName(pchar, "Leadership"))/10);
		break;

		case "Medium":
			Pchar.Quest.Loans.(NPC_Area).Sum = 1500*makeint(Pchar.rank);
			dialog.text = "Не проблема. Надеюсь, что " + FindRussianMoneyString(sti(Pchar.Quest.Loans.(NPC_Area).sum)) + " помогут вам решить ваши проблемы. Это вполне значительная сумма.";
			Link.l1 = "Договорились. Под какие проценты?";
			Link.l1.go = "Interest";
			Link.l2 = "Увы, эта сумма не годится. Давайте-ка ее изменим.";
			Link.l2.go = "Loan";
			Link.l3 = "Думаю, мне лучше не влезать в долги. До свидания.";
			Link.l3.go = "ExitDelLoan1";
			Pchar.Quest.Loans.(NPC_Area).Interest = 27 - makeint((GetSummonSkillFromName(pchar, "Commerce")+GetSummonSkillFromName(pchar, "Leadership"))/10);
		break;

		case "Large":
			Pchar.Quest.Loans.(NPC_Area).Sum = 4000*makeint(Pchar.rank);
			dialog.text = "М-да... Рискованно... Но ладно, я готов предоставить вам заем на сумму в " + FindRussianMoneyString(sti(Pchar.Quest.Loans.(NPC_Area).sum)) + ". Как вы понимаете, капитан, это действительно крупные деньги. Очень прошу вас серьезно отнестись к этому делу.";
			Link.l1 = "Договорились. Под какие проценты?";
			Link.l1.go = "Interest";
			Link.l2 = "Увы, эта сумма не годится. Давайте-ка ее изменим.";
			Link.l2.go = "Loan";
			Link.l3 = "Думаю, мне лучше не влезать в долги. До свидания.";
			Link.l3.go = "ExitDelLoan1";
			Pchar.Quest.Loans.(NPC_Area).Interest = 37 - makeint((GetSummonSkillFromName(pchar, "Commerce")+GetSummonSkillFromName(pchar, "Leadership"))/10);
		break;

		case "Interest":
			dialog.text = Pchar.Quest.Loans.(NPC_Area).Interest + "% в месяц. Основываясь на том, что я о вас знаю, я не могу предложить вам сейчас лучших условий."; 
			Link.l1 = "Меня это вполне устраивает. Осталось обговорить срок.";
			Link.l1.go = "Period";
			Link.l3 = "Думаю, мне лучше не влезать в долги. До свидания.";
			Link.l3.go = "ExitDelLoan1";
		break;

		case "Period":
			Pchar.Quest.Loans.(NPC_Area).Period = makeint(makeint(Pchar.reputation.nobility)/20) + 1;			
			dialog.text =  "Учитывая то, что я о вас слышал, " + Pchar.name + ", я буду ждать возврата этого кредита " + FindRussianMonthString(sti(Pchar.Quest.Loans.(NPC_Area).Period)) + ". После чего, как вы понимаете, я приму меры."; 
			Link.l1 = "Что же, я с удовольствием принимаю ваши условия... И ваши деньги.";
			Link.l1.go = "LoanGranted";
			Link.l3 = "Увы, мы с вами не договорились. До свидания.";
			Link.l3.go = "ExitDelLoan1";
		break;

		case "LoanGranted":
			Dialog.snd = "voice\USDI\USDI022";
			dialog.text = "Искренне этому рад. Но позвольте мне вас предупредить. Я давно занимаюсь своим делом и знаю, как вернуть вложенные средства. Так что если у вас и были какие мысли прикарманить мои деньги, лучше оставьте их\nНе хочу вас обидеть - просто предупреждаю.";
			Link.l1 = "Хм... Ну-ну. Всего хорошего.";
			Link.l1.go = "LoanGranted_exit";
		break;

		case "Loan_Remind":
			Dialog.snd = "voice\USDI\USDI023";
			dialog.text = "Ну, смотрите... Проценты капают. Да и времени у вас осталось не так уж много.";
			Link.l1 = "Не волнуйтесь. До встречи.";
			Link.l1.go = "exit";
		break;

		case "loan_return":
			addMoneyToCharacter(Pchar, -(makeint(Pchar.Quest.Loans.(NPC_Area).Result)));
			// boal 27.01.2004 -->
            if (npchar.quest.trade_date != lastspeak_date) // дыра с прокачкой была
            {
    			AddCharacterExpToSkill(Pchar, "Commerce", makeint(Pchar.Quest.Loans.(NPC_Area).Result) / 350);
    			AddCharacterExpToSkill(Pchar, "Leadership", makeint(Pchar.Quest.Loans.(NPC_Area).Result) / 700);
			}
			// boal 27.01.2004 <--
			DeleteAttribute(PChar, "quest.Loans_" + NPC_Area); // bug fix
			DeleteAttribute(PChar, "quest.Loans." + NPC_Area);
			dialog.text = LinkRandPhrase("О, это просто чудесно! В любое время, как вам понадобятся деньги - я к вашим услугам.", "Благодарю. Очень приятно иметь дело с деловым человеком, умеющим вовремя вернуть долг. А то знаете, разное бывает...",  "О, не зря я был в вас столь уверен, " + GetAddress_Form(NPChar) + "! Надеюсь, это не последний раз, когда вы прибегаете к моим услугам!");
			Link.l1 = LinkRandPhrase("Я хочу занять денег.", "Мне срочно понадобилась пара-другая песо.", "Как насчет небольшого кредита?");
			Link.l1.go = "loan";			
			if(makeint(PChar.money) >= 100)
			{
				Link.l2 = LinkRandPhrase("Я бы хотел"+ GetSexPhrase("","а") +" отдать деньги в рост.","Примете на хранение пиратскую добычу?", "Серебришко на черный день оставить можно?");
				Link.l2.go = "deposit";				
			}		
			if(CheckUseDublons(NPChar))	
			{
				Link.l3 = "Хочу сделать вклад в золотых дублонах.";
				Link.l3.go = "deposit_dub";				
			}
			Link.l4 = "До свидания, " + NPchar.name + ".";
			Link.l4.go = "ExitDelLoan1";
		break;

		case "deposit":
			dialog.text = LinkRandPhrase("Я слышу разумного человека! Так какую сумму в песо вы готовы отдать в рост?", "Хорошо. Поверьте мне, та сумма, что вы мне отдаете, будет ждать вас в целости и сохранности, и даже с процентами... А, кстати, какова эта сумма?", "Я смотрю, вы понимаете, что к чему в этой жизни. Сколько вы хотите отдать мне на хранение?");
			link.l1.edit = 3;
			link.l1 = "";	
			Link.l1.go = "result";
		break;
		
		case "result":
			Pchar.QuestTemp.Deposits.(sDepositType1).Interest = makeint((GetSummonSkillFromName(pchar, "Commerce")+GetSummonSkillFromName(pchar, "Leadership"))/10.0/4.0 + 0.66) + 1; 
			Pchar.QuestTemp.Deposits.(sDepositType1).Sum = dialogEditStrings[3];
			iTemp = sti(dialogEditStrings[3]);
			if (iTemp <= 0)
			{
				dialog.text = "Шутить изволите?";
				link.l1 = "Хм, извините, ошибочка вышла..";
				link.l1.go = "exit";
				break;
			}
			if (iTemp > sti(pchar.money))
			{
				dialog.text = "Хм, такой суммы у вас при себе нет, к сожалению. Давайте без глупостей...";
				link.l1 = "Гм... хорошо.";
				link.l1.go = "exit";
				break;
			}
			dialog.text = "Хорошо. Процентов под эту сумму я готов вам предложить... мм... скажем, " + Pchar.QuestTemp.Deposits.(sDepositType1).Interest + ". Разумеется, в месяц.";
			Link.l1 = "Меня это устраивает.";
			Link.l1.go = "Deposit_placed";
			Link.l2 = "Лучше я изменю сумму.";
			Link.l2.go = "Deposit";
			Link.l3 = "Кажется, мне не стоит расставаться с деньгами. Всего хорошего.";
			Link.l3.go = "Exit";
		break;

		case "Deposit_placed":
			if ( !CheckAttribute(Pchar, "Quest.Deposits." + (sDepositType1)+".Result"))
			{
			    Pchar.Quest.Deposits.(sDepositType1).Result = 0;//fix
			}
			// boal limit
			if ( (sti(Pchar.Quest.Deposits.(sDepositType1).Result) + sti(Pchar.QuestTemp.Deposits.(sDepositType1).Sum)) > sti(NPChar.UsurerDeposit)*1000)
			{
			    dialog.text = "Извините меня, капитан, но эта сумма слишком велика для провинциального банка. Мне просто негде организовать оборот таких денег, чтобы иметь возможность выплачивать проценты по вашему депозиту. Да и отсутствие достойной охраны, знаете ли... ну, надеюсь, вы меня правильно понимаете? В общем, я могу принять от вас в целом не более " +
						FindRussianMoneyString(MakeMoneyShow(sti(NPChar.UsurerDeposit)*1000, MONEY_SIGN,MONEY_DELIVER)) + ".";
				Link.l1 = "Очень жаль, придется обратиться к другому ростовщику.";
				Link.l1.go = "Exit";
			}
			else
			{
				dialog.text = "Теперь вы можете быть уверены, что даже самая жестокая буря не оставит вас без средств к существованию. Если же вы решите забрать вклад, то приходите в любое время.";
				Link.l1 = "Хорошо. Всего хорошего.";
				Link.l1.go = "Deposit_Exit";
			}
		break;
		
		case "Deposit_return":
			Dialog.snd = "voice\USDI\USDI034";
			dialog.text = "Исходя из процентов, которые мы оговорили в прошлый раз, и учитывая прошедшее время, я подсчитал, что должен вам " + FindRussianMoneyString(sti(Pchar.Quest.Deposits.(sDepositType1).Result)) + "... Вы уверены, что хотите забрать эти деньги";
			Link.l1 = "Абсолютно. Давайте их сюда.";			
			Link.l1.go = "Deposit_return_1";		
			Link.l2 = "Я хочу забрать часть денег.";			
			Link.l2.go = "Deposit_return_part";
			Link.l3 = "Знаете, вы правы. Пусть они еще немного полежат. Всего хорошего.";			
			Link.l3.go = "Exit";		
		break;		
		
		case "Deposit_exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			if(CheckAttribute(Pchar, "Quest.Deposits." + (sDepositType1)+ ".Rem"))
			{
				DeleteAttribute(Pchar,"Quest.Deposits." + (sDepositType1)+ ".Rem");
			}
			Pchar.Quest.Deposits.(sDepositType1).Interest = sti(Pchar.QuestTemp.Deposits.(sDepositType1).Interest);
			Pchar.Quest.Deposits.(sDepositType1).Sum      = sti(Pchar.QuestTemp.Deposits.(sDepositType1).Sum);
			Pchar.Quest.Deposits.(sDepositType1).city 	  = NPC_Area;	

			AddMoneyToCharacter(Pchar, -(makeint(Pchar.Quest.Deposits.(sDepositType1).Sum)));
			// общий долг
			Pchar.Quest.Deposits.(sDepositType1).Sum = sti(Pchar.Quest.Deposits.(sDepositType1).Result) + sti(Pchar.Quest.Deposits.(sDepositType1).Sum);
			Pchar.Quest.Deposits.(sDepositType1) = true;
			Pchar.Quest.Deposits.(sDepositType1).StartDay 	= getDataDay();
			Pchar.Quest.Deposits.(sDepositType1).StartMonth = getDataMonth();
			Pchar.Quest.Deposits.(sDepositType1).StartYear 	= getDataYear();
			Pchar.Quest.Deposits.(sDepositType1).StartTime 	= getTime();
			DialogExit();
		break;
		
		//--> Jason забор денег по частям
		case "Deposit_return_part":
			dialog.text = "И сколько же именно?";
			link.l1.edit = 4;
			link.l1 = "";	
			Link.l1.go = "result_part";
		break;

		case "result_part":
			iTemp = sti(dialogEditStrings[4]);
			if (iTemp <= 0)
			{
				dialog.text = "Сударь, что за идиотские шутки!";			
				link.l1 = "Тысяча акул! Простите... Изменим сумму...";	
				Link.l1.go = "Deposit_return_part";
				break;
			}
			if (iTemp > sti(Pchar.Quest.Deposits.(sDepositType1).Result))
			{
				dialog.text = "Сударь, у вас нет столько денег на счете.";			
				link.l1 = "Тысяча акул! Я ошибся. Изменим сумму...";	
				Link.l1.go = "Deposit_return_part";
				break;
			}
			if (iTemp == sti(Pchar.Quest.Deposits.(sDepositType1).Result))
			{
				dialog.text = "Все забираете? Хорошо, как скажете. Вот ваши деньги.";			
				link.l1 = "Спасибо!";	
				Link.l1.go = "Deposit_return_all";
				break;
			}
			dialog.text = "Хорошо. Забирайте. Вот ваши деньги.";			
			link.l1 = "Спасибо!";	
			Link.l1.go = "result_part_1";
		break;
		
		case "result_part_1":
			DialogExit();
			iTemp = sti(dialogEditStrings[4]);
			addMoneyToCharacter(Pchar, iTemp);
			iRes = sti(Pchar.Quest.Deposits.(sDepositType1).Result)-iTemp; //остаток на счете
			iPer = sti(Pchar.Quest.Deposits.(sDepositType1).Interest);
			iDep = sti(Pchar.Quest.Deposits.(sDepositType1).Sum); //стартовая сумма
			if (iRes <= sti(Pchar.Quest.Deposits.(sDepositType1).Sum)) // стало меньше начальной суммы
			{
				DeleteAttribute(Pchar, "quest.Deposits." + (sDepositType1));
				Pchar.Quest.Deposits.(sDepositType1).Interest = iPer;
				Pchar.Quest.Deposits.(sDepositType1).Sum = iRes;
				Pchar.Quest.Deposits.(sDepositType1).Result = 0;
			}
			else // если остаток больше начальной суммы - проценты продолжаем считать с нее, а не с остатка, ибо нефиг, дельту приплюсуем к набежавшим процентам - банкир Jason :) 
			{
				DeleteAttribute(Pchar, "quest.Deposits." + (sDepositType1));
				Pchar.Quest.Deposits.(sDepositType1).Interest = iPer;
				Pchar.Quest.Deposits.(sDepositType1).Sum = iDep;
				Pchar.Quest.Deposits.(sDepositType1).Rem = iRes-iDep;
			}
			Pchar.Quest.Deposits.(sDepositType1).city 	  	= NPC_Area;	
			Pchar.Quest.Deposits.(sDepositType1) 			= true;
			Pchar.Quest.Deposits.(sDepositType1).StartDay 	= getDataDay();
			Pchar.Quest.Deposits.(sDepositType1).StartMonth = getDataMonth();
			Pchar.Quest.Deposits.(sDepositType1).StartYear 	= getDataYear();
			Pchar.Quest.Deposits.(sDepositType1).StartTime 	= getTime();
		break;
		
		case "Deposit_return_all":
			DialogExit();
			iTemp = sti(dialogEditStrings[4]);
			addMoneyToCharacter(Pchar, iTemp);
			DeleteAttribute(Pchar, "quest.Deposits." + (sDepositType1));
		break;
		//<-- забор денег по частям		
		
		case "Deposit_return_1":
			addMoneyToCharacter(Pchar, makeint(Pchar.Quest.Deposits.(sDepositType1).Result));
			Dialog.snd = "voice\USDI\USDI035";
			dialog.text = "Ох... Даже жаль с ними расставаться. Я к ним уже как-то привык. Что же - приходите ко мне еще.";			
			Link.l1 = "Если понадобится - приду. Счастливо оставаться.";			
			Link.l1.go = "Exit";
			DeleteAttribute(Pchar, "quest.Deposits." + (sDepositType1));
		break;
		
		//  ugeen -> вклады в дублонах	
		case "deposit_dub":
			dialog.text = LinkRandPhrase("Я слышу разумного человека! Так какую сумму в дублонах вы готовы отдать в рост?", "Хорошо. Поверьте мне, та сумма, что вы мне отдаете, будет ждать вас в целости и сохранности, и даже с процентами... А, кстати, какова эта сумма?", "Я смотрю, вы понимаете, что к чему в этой жизни. Сколько вы хотите отдать мне на хранение?");
			link.l1.edit = 3;
			link.l1 = "";	
			Link.l1.go = "result_dub";
		break;
		
		case "result_dub":		
			iTotalDublonQty = GetCharacterItem(pchar,"gold_dublon") + CheckItemMyCabin("gold_dublon");		
			Pchar.QuestTemp.Deposits.(sDepositType2).Interest = makeint((GetSummonSkillFromName(pchar, "Commerce")+GetSummonSkillFromName(pchar, "Leadership"))/20.0/4.0 + 0.66) + 1; 
			Pchar.QuestTemp.Deposits.(sDepositType2).Sum = dialogEditStrings[3];
			iTemp = sti(dialogEditStrings[3]);
			if (iTemp <= 0)
			{
				dialog.text = "Шутить изволите?";
				link.l1 = "Хм, извините, ошибочка вышла..";
				link.l1.go = "exit";
				break;
			}						
			if (iTemp > iTotalDublonQty)
			{
				dialog.text = "Хм, такой суммы у вас нет, к сожалению. Давайте без глупостей...";
				link.l1 = "Гм... хорошо.";
				link.l1.go = "exit";
				break;
			}
			dialog.text = "Хорошо. Процентов под эту сумму я готов вам предложить... мм... скажем, " + Pchar.QuestTemp.Deposits.(sDepositType2).Interest + ". Разумеется, в месяц.";
			Link.l1 = "Меня это устраивает.";
			Link.l1.go = "Deposit_placed_dub";
			Link.l2 = "Лучше я изменю сумму.";
			Link.l2.go = "Deposit_dub";
			Link.l3 = "Кажется, мне не стоит расставаться с моим золотом. Всего хорошего.";
			Link.l3.go = "Exit";
		break;
		
		case "Deposit_placed_dub":
			Dialog.snd = "voice\USDI\USDI033";
			if ( !CheckAttribute(Pchar, "Quest.Deposits." + (sDepositType2)+".Result"))
			{
			    Pchar.Quest.Deposits.(sDepositType2).Result = 0;//fix
			}
			// boal limit
			if ( (sti(Pchar.Quest.Deposits.(sDepositType2).Result) + sti(Pchar.QuestTemp.Deposits.(sDepositType2).Sum)) > sti(NPChar.UsurerDeposit)*10)
			{
			    dialog.text = "Извините меня, капитан, но эта сумма слишком велика для провинциального банка. Мне просто негде организовать оборот такого количества золота, чтобы иметь возможность выплачивать проценты по вашему депозиту. Да и отсутствие достойной охраны, знаете ли... ну, надеюсь, вы меня правильно понимаете? В общем, я могу принять от вас в целом не более " +
						FindRussianDublonString(MakeMoneyShow(sti(NPChar.UsurerDeposit)*10, MONEY_SIGN,MONEY_DELIVER)) + ".";
				Link.l1 = "Очень жаль, придется обратиться к другому ростовщику.";
				Link.l1.go = "Exit";
			}
			else
			{
				dialog.text = "Теперь вы можете быть уверены, что даже самая жестокая буря не оставит вас без средств к существованию. Если же вы решите забрать вклад, то приходите в любое время.";
				Link.l1 = "Хорошо. Всего хорошего.";
				Link.l1.go = "Deposit_Exit_dub";
			}
		break;
		
		case "Deposit_return_dub":
			dialog.text = "Исходя из процентов, которые мы оговорили в прошлый раз, и учитывая прошедшее время, я подсчитал, что должен вам " + FindRussianDublonString(sti(Pchar.Quest.Deposits.(sDepositType2).Result)) + "... Вы уверены, что хотите забрать эти деньги";
			Link.l1 = "Абсолютно. Давайте их сюда.";			
			Link.l1.go = "Deposit_return_dub_1";		
			Link.l2 = "Я хочу забрать часть денег.";			
			Link.l2.go = "Deposit_return_dub_part";
			Link.l3 = "Знаете, вы правы. Пусть они еще немного полежат. Всего хорошего.";			
			Link.l3.go = "Exit";		
		break;	

		case "Deposit_exit_dub":
			NextDiag.CurrentNode = NextDiag.TempNode;		
			if(CheckAttribute(Pchar, "Quest.Deposits." + (sDepositType2)+ ".Rem"))
			{
				DeleteAttribute(Pchar,"Quest.Deposits." + (sDepositType2)+ ".Rem");
			}	
			Pchar.Quest.Deposits.(sDepositType2).Interest = sti(Pchar.QuestTemp.Deposits.(sDepositType2).Interest);
			Pchar.Quest.Deposits.(sDepositType2).Sum      = sti(Pchar.QuestTemp.Deposits.(sDepositType2).Sum);
			Pchar.Quest.Deposits.(sDepositType2).city 	  = NPC_Area;	
			
			iTemp = GetCharacterItem(pchar,"gold_dublon");
			if(iTemp > sti(Pchar.Quest.Deposits.(sDepositType2).Sum))
			{
				TakeNItems(pchar,"gold_dublon", -sti(Pchar.Quest.Deposits.(sDepositType2).Sum));
			}
			else
			{
				TakeNItems(pchar,"gold_dublon", -iTemp));
				iTemp = sti(Pchar.Quest.Deposits.(sDepositType2).Sum) - iTemp;
				GetItemMyCabin("gold_dublon", iTemp);
			}
						
			// общий долг
			Pchar.Quest.Deposits.(sDepositType2).Sum = sti(Pchar.Quest.Deposits.(sDepositType2).Result) + sti(Pchar.Quest.Deposits.(sDepositType2).Sum);
			Pchar.Quest.Deposits.(sDepositType2) = true;
			Pchar.Quest.Deposits.(sDepositType2).StartDay 	= getDataDay();
			Pchar.Quest.Deposits.(sDepositType2).StartMonth = getDataMonth();
			Pchar.Quest.Deposits.(sDepositType2).StartYear 	= getDataYear();
			Pchar.Quest.Deposits.(sDepositType2).StartTime 	= getTime();
			DialogExit();
		break;	
		
		//-->забор дублонов по частям
		case "Deposit_return_dub_part":
			dialog.text = "И сколько же именно?";
			link.l1.edit = 4;
			link.l1 = "";	
			Link.l1.go = "result_dub_part";
		break;
		
		case "result_dub_part":
			iTemp = sti(dialogEditStrings[4]);
			if (iTemp <= 0)
			{
				dialog.text = "Сударь, что за идиотские шутки!";			
				link.l1 = "Тысяча акул! Простите... Изменим сумму...";	
				Link.l1.go = "Deposit_return_dub_part";
				break;
			}			
			if (iTemp > sti(Pchar.Quest.Deposits.(sDepositType2).Result))
			{
				dialog.text = "Сударь, у вас нет такого количества золота на счете.";			
				link.l1 = "Тысяча акул! Я ошибся. Изменим сумму...";	
				Link.l1.go = "Deposit_return_dub_part";
				break;
			}			
			if (iTemp == sti(Pchar.Quest.Deposits.(sDepositType2).Result))
			{
				dialog.text = "Все забираете? Хорошо, как скажете. Вот ваше золото.";			
				link.l1 = "Спасибо!";	
				Link.l1.go = "Deposit_return_dub_all";
				break;
			}
			dialog.text = "Хорошо. Забирайте. Вот ваши деньги.";			
			link.l1 = "Спасибо!";	
			Link.l1.go = "result_dub_part_1";
		break;
		
		case "result_dub_part_1":
			DialogExit();
			iTemp = sti(dialogEditStrings[4]);
			TakeNItems(pchar,"gold_dublon", iTemp);
			iRes = sti(Pchar.Quest.Deposits.(sDepositType2).Result)-iTemp; //остаток на счете
			iPer = sti(Pchar.Quest.Deposits.(sDepositType2).Interest);
			iDep = sti(Pchar.Quest.Deposits.(sDepositType2).Sum); //стартовая сумма
			if (iRes <= sti(Pchar.Quest.Deposits.(sDepositType2).Sum)) // стало меньше начальной суммы
			{
				DeleteAttribute(Pchar, "quest.Deposits." + (sDepositType2));
				Pchar.Quest.Deposits.(sDepositType2).Interest = iPer;
				Pchar.Quest.Deposits.(sDepositType2).Sum = iRes;
				Pchar.Quest.Deposits.(sDepositType2).Result = 0;
			}
			else // если остаток больше начальной суммы - проценты продолжаем считать с нее, а не с остатка, ибо нефиг, дельту приплюсуем к набежавшим процентам - банкир Jason :) 
			{
				DeleteAttribute(Pchar, "quest.Deposits." + (sDepositType2));
				Pchar.Quest.Deposits.(sDepositType2).Interest = iPer;
				Pchar.Quest.Deposits.(sDepositType2).Sum = iDep;
				Pchar.Quest.Deposits.(sDepositType2).Rem = iRes-iDep;
			}
			Pchar.Quest.Deposits.(sDepositType2).city 	  	= NPC_Area;	
			Pchar.Quest.Deposits.(sDepositType2) 			= true;
			Pchar.Quest.Deposits.(sDepositType2).StartDay 	= getDataDay();
			Pchar.Quest.Deposits.(sDepositType2).StartMonth = getDataMonth();
			Pchar.Quest.Deposits.(sDepositType2).StartYear 	= getDataYear();
			Pchar.Quest.Deposits.(sDepositType2).StartTime 	= getTime();
		break;
		
		case "Deposit_return_dub_all":
			DialogExit();
			iTemp = sti(dialogEditStrings[4]);
			TakeNItems(pchar,"gold_dublon", iTemp);
			DeleteAttribute(Pchar, "quest.Deposits." + (sDepositType2));
		break;
		//<-- забор денег по частям		
		
		case "Deposit_return_dub_1":
			TakeNItems(pchar,"gold_dublon", sti(Pchar.Quest.Deposits.(sDepositType2).Result));
			dialog.text = "Ох... Даже жаль с ними расставаться. Я к ним уже как-то привык. Что же - приходите ко мне еще.";			
			Link.l1 = "Если понадобится - приду. Счастливо оставаться.";			
			Link.l1.go = "Exit";
			DeleteAttribute(Pchar, "quest.Deposits." + (sDepositType2));
		break;
		//  ugeen <- вклады в дублонах	
		
		case "DeadMotherfucker":
			Dialog.TempNode = "DeadMotherFucker_1";
			dialog.text = "Вы еще живы? Наверное, хотите вернуть мне деньги? К черту! Из-за вас я потерял столько, сколько вы мне в жизни не возместите! Я не успокоюсь, пока не увижу ваш труп!";
            Link.l1 = "Я как раз хочу уладить наши дела мирно.";
			Link.l1.go = "LoanRestore_1";
			Link.l2 = LinkRandPhrase("Ну, давай посмотрим! Только учти, что ты и сам легко можешь стать трупом!", "Угрожаешь мне?! Ну хорошо, посмотрим, что ты предпримешь...", "Деньги - не главное в жизни. Так что не стоит тебе ради них так убиваться самому и убивать других.");
			Link.l2.go = "ExitDelLoan2";
		break;

		case "DeadMotherFucker_1":			
			dialog.text = "Убирайтесь из моего дома! Глаза мои вас бы не видели!";			
			Link.l1 = "...";			
			Link.l1.go = "ExitDelLoan2";
            Dialog.TempNode = "DeadMotherFucker_1";
		break;
		// boal обратимость факапства -->
		case "LoanRestore_1":
            iPastMonths = GetPastTime("Month", makeint(Pchar.Quest.Loans.(NPC_Area).StartYear),makeint(Pchar.Quest.Loans.(NPC_Area).StartMonth),makeint(Pchar.Quest.Loans.(NPC_Area).StartDay), makefloat(Pchar.Quest.Loans.(NPC_Area).StartTime), getDataYear(),getDataMonth(),GetDataDay(), GetTime());
			Pchar.Quest.Loans.(NPC_Area).Result = makeint(Pchar.Quest.Loans.(NPC_Area).Sum) + ((makeint(Pchar.Quest.Loans.(NPC_Area).Sum)/100)*makeint(Pchar.Quest.Loans.(NPC_Area).Interest))*(iPastMonths+1);
			dialog.text = "Да? И что вы предлагаете?";
			Link.l1 = "На сегодня я долж"+ GetSexPhrase("ен","на") +" вам сумму в " + FindRussianMoneyString(sti(Pchar.Quest.Loans.(NPC_Area).Result)) + ". Предлагаю ее вам.";
			Link.l1.go = "DeadMotherFucker_1";
            if (sti(Pchar.Money) >= 2*sti(Pchar.Quest.Loans.(NPC_Area).Result))
            {
    			Link.l2 = "Чтобы наладить отношения, предлагаю вернуть вам сумму долга в размере " + FindRussianMoneyString(2*sti(Pchar.Quest.Loans.(NPC_Area).Result)) + ".";
    			Link.l2.go = "LoanRestore_2";
			}
		break;
		
		case "LoanRestore_2":
			dialog.text = "Это другое дело! С вами все же можно иметь дела.";
			Link.l1 = "Спасибо. Больше не подведу.";
			Link.l1.go = "ExitDelLoan2";
			NextDiag.TempNode = "First time";			
			addMoneyToCharacter(Pchar, -2*sti(Pchar.Quest.Loans.(NPC_Area).Result));
			DeleteAttribute(PChar, "quest.Loans_" + NPC_Area);
			DeleteAttribute(PChar, "quest.Loans." + NPC_Area);
			ChangeCharacterHunterScore(PChar, NationShortName(sti(NPChar.nation)) + "hunter", -30);
			ChangeCharacterComplexReputation(pchar,"nobility", 2);
		break;

		case "ExitDelLoan1":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			DeleteAttribute(Pchar, "quest.Loans." + (NPC_Area));
		break;

		case "ExitDelLoan2":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			DeleteAttribute(Pchar, "quest.Loans." + (NPC_Area));
			DeleteAttribute(Pchar, "quest.Deposits." + (NPC_Area));
		break;
		
        case "LoanGranted_exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			AddMoneyToCharacter(Pchar, makeint(Pchar.Quest.Loans.(NPC_Area).Sum));
			Pchar.Quest.Loans.(NPC_Area) = true;
			Pchar.Quest.Loans.(NPC_Area).StartDay = getDataDay();
			Pchar.Quest.Loans.(NPC_Area).StartMonth = getDataMonth();
			Pchar.Quest.Loans.(NPC_Area).StartYear = getDataYear();
			Pchar.Quest.Loans.(NPC_Area).StartTime = getTime();
			sTemp = "Loans_" + NPC_Area;			
			SetTimerCondition(sTemp, 0, makeint(Pchar.Quest.Loans.(NPC_Area).Period), 0, false);
			pchar.quest.(sTemp).CityId = NPC_Area;
			pchar.quest.(sTemp).win_condition = "LoansForAll";
			DialogExit();
			npchar.quest.trade_date = lastspeak_date; // дыра с прокачкой была
		break;
        
		//работорговец
		int iSlaveMoney;
		int amount;
		case "GiveTaskSlave":
			pchar.questTemp.Slavetrader.iSlaveQuantity = 300 + rand(100);
			pchar.questTemp.Slavetrader.iSlaveMoney = sti(pchar.questTemp.Slavetrader.iSlaveQuantity) * 250;
			dialog.Text = "Ах оставьте! Мы с вами серьезные люди, и ни к чему оглядываться на пересуды всей этой голытьбы, которая готова удавиться за испанский дублон, но при этом и пальцем не пошевелит, чтобы сделать из него два\nЯ ищу человека, которому хочу предложить серьезное дело. Человека отважного и деятельного, честного и пунктуального, но не обремененного... э-эм... излишней щепетильностью в вопросах морали. И очень надеюсь найти такого человека в вашем лице.";
			Link.l1 = "Это во многом будет зависеть от того, какого рода 'дело' вы собираетесь мне предложить.";
			Link.l1.go = "GiveTaskSlave_1";
		break;
			
		case "GiveTaskSlave_1":
			dialog.Text = "Хорошо, слушайте. Сейчас нет на всех Карибах прибыльнее дела, чем работорговля. Я не плантатор, но у меня есть надежный покупатель на этот товар, и не один\nВ общем, мне нужны рабы в количестве " + pchar.questTemp.Slavetrader.iSlaveQuantity + " штук. За каждого я готов заплатить по 250 песо - это неплохая цена, согласитесь. Всего сумма сделки составит " + FindRussianMoneyString(sti(pchar.questTemp.Slavetrader.iSlaveMoney)) + " золотом.";
			Link.l1 = "Нет, работорговлей я не занимаюсь. Ищите себе другого помощника, не обремененного наличием совести.";
			Link.l1.go = "exit_slaves";
			Link.l2 = "Хм, предложение действительно заманчивое. Я бы взял"+ GetSexPhrase("ся","ась") +". Как срочно вам нужны эти рабы?";
			Link.l2.go = "GiveTaskSlave_2";
		break;
			
		case "exit_slaves":
			dialog.Text = "Э-э-эх, мало кто хочет пошевелить задом, чтоб поднять золото, которое валяется прямо под ногами. Я разочарован... Прощайте, и не вздумайте болтать о нашем разговоре - у меня длинные руки...";
			Link.l1 = "Я вижу, что у вас 'грязные' руки... впрочем, как и язык. Всего хорошего.";
			Link.l1.go = "exit";
			pchar.questTemp.Slavetrader = "End_quest";
			DeleteAttribute(npchar, "quest.slave");
		break;
			
		case "GiveTaskSlave_2":
			dialog.Text = "В сроках я вас не ограничиваю, но все же постарайтесь побыстрее. Спрос на 'черную слоновую кость' огромен. Если вы зарекомендуете себя в моих глазах с хорошей стороны, подобные заказы станут поступать вам без перебоя, уверяю.";
			Link.l1 = "Охотно верю. Что же, ждите хороших новостей.";
			Link.l1.go = "exit";						
			pchar.questTemp.Slavetrader = "Seek_slaves"; // это ввод имени квеста и состояния квеста
			AddQuestRecord("Slavetrader", "1");
			AddQuestUserData("Slavetrader", "sName", GetFullName(npchar));
			AddQuestUserData("Slavetrader", "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData("Slavetrader", "sQty", makeint(pchar.questTemp.Slavetrader.iSlaveQuantity));
			AddQuestUserData("Slavetrader", "sSum", makeint(pchar.questTemp.Slavetrader.iSlaveMoney));
			LAi_LocationDisableOfficersGen(&Locations[FindLocation(pchar.location)], true); // блокируем вход офицеров 2015
		break;
			
		case "Checkslaves":
			amount = GetSquadronGoods(Pchar, GOOD_SLAVES) - sti(pchar.questTemp.Slavetrader.iSlaveQuantity);
			dialog.Text = "Ну что, удалось вам добыть уговоренную партию 'черного дерева'?";
            if (amount < 0)
			{
				Link.l1 = "Пока нет. Просто решил"+ GetSexPhrase("","а") +" убедиться, что наш уговор еще в силе.";
            	Link.l1.go = "exit";
			}
			else
			{
				Link.l1 = "Удалось. Вся партия у меня в трюмах.";
            	Link.l1.go = "Takeslaves";
			}
		break;
		
		case "Takeslaves":
			amount = sti(pchar.questTemp.Slavetrader.iSlaveQuantity);
			dialog.Text = "Отлично! Мои люди их заберут... Насчет таможни и коменданта форта не беспокойтесь. У меня этот бизнес поставлен на широкую ногу, так что проблем не будет, и в контрабанде вас никто не обвинит.";
			Link.l1 = "Смотрю, у вас здесь уже все схвачено! Как насчет оплаты?";
            Link.l1.go = "Takeslaves_1";
			RemoveCharacterGoods(Pchar, GOOD_SLAVES, amount);
		break;
		
		case "Takeslaves_1":
			AddMoneyToCharacter(pchar, makeint(pchar.questTemp.Slavetrader.iSlaveMoney));
			dialog.Text = "Пожалуйста, получите... Я слов на ветер не бросаю. Держитесь за меня, капитан, и скоро у вас будет столько песо, что для их перевозки понадобится целый галеон!";
			Link.l1 = "Хорошо бы... Ну а что дальше?";
            Link.l1.go = "Takeslaves_2";
		break;
		
		case "Takeslaves_2":
			dialog.Text = "Дальше? А дальше - зайдите недели через три, у меня как раз зреет солидный заказ. Думаю, к тому времени все уже сложится.";
			Link.l1 = "Договорились. До встречи...";
            Link.l1.go = "exit";
			AddQuestRecord("Slavetrader", "2");
			AddQuestUserData("Slavetrader", "sName", GetFullName(npchar));
			pchar.questTemp.Slavetrader = "wait";
			SaveCurrentQuestDateParam("pchar.questTemp.Slavetrader_wait");//запомнить дату
		break;
		
		case "Takeslaves_3":
			if (4-sti(RealShips[sti(pchar.ship.type)].Class) < 0)//проверка класса корабля
			{
				dialog.Text = "Работа будет. Но есть проблема - у вас слабоват корабль. Я не хочу провалить дело, да и вас посылать на верную смерть тоже нет желания. Поскольку время терпит, обзаведитесь кораблем посолиднее, не меньше баркентины, а лучше бригом или бригантиной. Ну, флейтом, на крайний случай. И не затягивайте, мы можем упустить момент.";
				Link.l1 = "Понятно, этот вопрос решим. До встречи.";
            	Link.l1.go = "Takeslaves_3_smallship";
			}
			else
			{
				dialog.Text = "Наконец-то! Я вас ждал. Теперь к сути дела. Как вы понимаете, в любом бизнесе есть конкуренты. Имеются таковые и у меня. Эти алчные беспринципные негодяи всегда норовят увести клиента из-под самого носа! В общем, я хочу устранить одного такого мерзавца и хорошенько заработать на этом.";
				Link.l1 = "Я в"+ GetSexPhrase("есь","ся") +" внимание.";
            	Link.l1.go = "Takeslaves_4";
			}
		break;
		
		case "Takeslaves_3_smallship":
			pchar.questTemp.Slavetrader = "waitship";
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "Takeslaves_4":
			Slavetrader_GetRandomShore();//выбор бухты
			pchar.questTemp.Slavetrader.ShipName = GenerateRandomNameToShip(sti(NPChar.nation));
			pchar.questTemp.Slavetrader.UnknownPirateName = "l" + rand(GetNamesCount(NAMETYPE_ORIG) - 1);
			dialog.text = "Превосходно. Так вот. Этот проходимец, по кличке " + GetName( NAMETYPE_ORIG, pchar.questTemp.Slavetrader.UnknownPirateName, NAME_NOM) + ", привез из Африки груз рабов, и сейчас остановился в бухте " + XI_ConvertString(pchar.questTemp.Slavetrader.Island.Shore + "Gen") + ", это остров " + XI_ConvertString(pchar.questTemp.Slavetrader.Island) + ". Он ждет там контрабандистов. Его галеон называется '" + pchar.questTemp.Slavetrader.ShipName + "'. Эту сделку нужно сорвать, во что бы то ни стало!";
			link.l1 = "Хм, а что делать с рабами? Не топить же их!";
			link.l1.go = "Takeslaves_5";
		break;
		
		case "Takeslaves_5":
			dialog.Text = "С какой стати? " + GetName( NAMETYPE_ORIG, pchar.questTemp.Slavetrader.UnknownPirateName, NAME_NOM) + " на очень плохом счету, и никто не расстроится, если он исчезнет. Вы захватываете галеон, его самого отправляете в расход, товар привозите мне, а я его продаю. По моим сведниям, у него на борту находится не менее полутора тысяч рабов - огромная партия.";
			Link.l1 = "Ого! Действительно немало. Что насчет гонорара за работу?";
            Link.l1.go = "Takeslaves_6";
			Link.l2 = "Нет, уважаемый, эти интриги не по мне. С какой стати мне ссориться с контрабандистами?";
            Link.l2.go = "exit_slaves_1";
		break;
		
		case "exit_slaves_1":
			dialog.Text = "Да-а, похоже, я в вас ошибся... Прощайте, и забудьте о нашем разговоре. И, если не хотите неприятностей, советую не распространяться о том, что здесь слышали. Как вы уже могли убедиться, у меня в городе все схвачено. А если вы хитрите и попробуете абордировать '" + pchar.questTemp.Slavetrader.ShipName + "' самостоятельно - я позабочусь, чтобы вас вздернули на виселице. Имейте это в виду.";
			Link.l1 = "Можете не переживать - я не занимаюсь доносами. И ваш галеон с рабами мне тоже не нужен. Всего доброго.";
            Link.l1.go = "exit";
			AddQuestRecord("Slavetrader", "8");
			AddQuestUserData("Slavetrader", "sSex", GetSexPhrase("ся","ась"));
			CloseQuestHeader("Slavetrader");
			pchar.questTemp.Slavetrader = "End_quest";//конец квеста
		break;
		
		case "Takeslaves_6":
			dialog.Text = "С учетом того, что я даю полную информацию о местонахождении груза, избавляя вас от необходимости бороздить море в поисках добычи, оплата будет, как вы сами понимаете, несколько ниже. По 200 песо за каждого раба. Но это все равно огромная сумма - порядка трехсот тысяч, если все пройдет успешно.";
			Link.l1 = "Годится. Сколько у меня времени на операцию?";
            Link.l1.go = "Takeslaves_7";
			Link.l2 = "Хо-хо! Вы говорите так, будто эти рабы сами бросятся вплавь, чтобы перебраться ко мне в трюм! Хотите, чтобы мои люди подставляли головы под картечь за такую несуразную цену? Увеличьте вознаграждение, или я не стану этим заниматься.";
            Link.l2.go = "exit_slaves_1";
		break;
		
		case "Takeslaves_7":
			dialog.text = "Думаю, не больше двух недель. Если опоздаете - он успеет выгрузиться и момент будет упущен.";
			link.l1 = "Придется поторопиться. Ждите меня с хорошими новостями. До встречи.";
			link.l1.go = "exit";
			AddQuestRecord("Slavetrader", "3");
			AddQuestUserData("Slavetrader", "sName", GetFullName(npchar));
			AddQuestUserData("Slavetrader", "sShipName", pchar.questTemp.Slavetrader.ShipName);
			AddQuestUserData("Slavetrader", "sShoreName", XI_ConvertString(pchar.questTemp.Slavetrader.Island.Shore + "Abl"));
			AddQuestUserData("Slavetrader", "sShoreType", XI_ConvertString(GetIslandByArealName(pchar.questTemp.Slavetrader.Island) + "Dat"));
			pchar.quest.Slavetrader_ShipsAttack.win_condition.l1 = "location";
            pchar.quest.Slavetrader_ShipsAttack.win_condition.l1.location = pchar.questTemp.Slavetrader.Island;
            pchar.quest.Slavetrader_ShipsAttack.function = "Slavetrader_CreateSlaveShips";//создание кораблей
			SetFunctionTimerCondition("Slavetrader_SlaveShipsOver", 0, 0, 15, false);	//таймер
			pchar.questTemp.Slavetrader = "wait1";	//это заглушка
		break;
		
		case "Takeslaves_4_lose":
			dialog.text = "Ну что, " + GetFullName(pchar) + ", как прошла операция? Судя по вашему унылому виду, вы ее провалили.";
			link.l1 = "Вы правы, черт возьми... Я... ну, это... опоздал"+ GetSexPhrase("","а") +" к острову. Он, видимо, уже ушел оттуда, так как я никого не наш"+ GetSexPhrase("ел","ла") +". Весь путь пришлось идти в бейдевинд - постоянно дул встречный ветер, будь он неладен...";
			link.l1.go = "Takeslaves_5_lose";
		break;
		
		case "Takeslaves_4_win":
			dialog.text = "Ну что, " + GetFullName(pchar) + ", каков нынче улов? Мне уже доложили, что " + GetName( NAMETYPE_ORIG, pchar.questTemp.Slavetrader.UnknownPirateName, NAME_NOM) + " пускает пузыри.";
			link.l1 = "Да, я подоспел"+ GetSexPhrase("","а") +" как раз вовремя! " + GetName( NAMETYPE_ORIG, pchar.questTemp.Slavetrader.UnknownPirateName, NAME_NOM) + " перегружал рабов на корабль контрабандистов. Пришлось и его покупателей заодно отправить на свидание к Дэви Джонсу, так что конкурентов у вас значительно поубавилось.";
			link.l1.go = "Takeslaves_5_win";
		break;
		
		case "Takeslaves_5_lose":
			dialog.text = "Да, похоже, я в тебе ошибся. Ты опоздал"+ GetSexPhrase("","а") +"? А может, просто струсил"+ GetSexPhrase("","а") +", покинув поля боя? Ладно. Теперь это уже не имеет значения. Ты загубил"+ GetSexPhrase("","а") +" отличную идею, и я более не желаю иметь с тобой дел. Проваливай, и забудь обо всем, что ты здесь видел"+ GetSexPhrase("","а") +" и слышал"+ GetSexPhrase("","а") +".";
			link.l1 = "Ну что же, прощайте.";
			link.l1.go = "exit";
			AddQuestRecord("Slavetrader", "5_5");
			AddQuestUserData("Slavetrader", "sSex", GetSexPhrase("","а"));
			AddQuestUserData("Slavetrader", "sName", GetFullName(npchar));
			CloseQuestHeader("Slavetrader");
			pchar.questTemp.Slavetrader = "End_quest";
		break;
		
		case "Takeslaves_5_win":
			pchar.questTemp.Slavetrader.Nation = npchar.nation;
			amount = 1600 - GetSquadronGoods(Pchar, GOOD_SLAVES);
			sTemp = GetSquadronGoods(Pchar, GOOD_SLAVES);
			iSlaveMoney = makeint(sTemp)*200;
			if (amount < 0)
			{
				dialog.text = "Вижу, я в вас не ошибся - "+ GetSexPhrase("головорез вы лихой","морячка вы лихая") +". Такой человек мне и нужен. Вы великолепно справились с поставленной задачей - у вас в трюмах больше полутора тысяч рабов! Но, к сожалению, я могу принять только тысячу шестьсот единиц товара - на большее у меня сейчас просто нет денег. Остальных рабов вам придется сбыть самостоятельно. Итак, ваша награда составляет 320 000 песо.";
				link.l1 = "Благодарю. Приятно иметь с вами дело, " + npchar.name + "!";
				link.l1.go = "Takeslaves_6_win";
				AddMoneyToCharacter(pchar, 320000);
				RemoveCharacterGoods(Pchar, GOOD_SLAVES, 1600);
				AddQuestRecord("Slavetrader", "6");
				AddQuestUserData("Slavetrader", "sName", GetFullName(npchar));
				AddQuestUserData("Slavetrader", "sQty", 1600);
				AddQuestUserData("Slavetrader", "sMoney", 320000);
				break;
			}
			if (amount >= 0 && amount < 200)
			{
				dialog.text = "Вижу, я в вас не ошибся - "+ GetSexPhrase("головорез вы лихой","морячка вы лихая") +". Такой человек мне и нужен. Вы великолепно справились с поставленной задачей - привезли "+ sTemp +" рабов. Ваша награда составляет " + FindRussianMoneyString(iSlaveMoney) + ".";
				link.l1 = "Благодарю. Приятно иметь с вами дело, " + npchar.name + "!";
				link.l1.go = "Takeslaves_6_win";
				AddMoneyToCharacter(pchar, makeint(iSlaveMoney));
				RemoveCharacterGoods(Pchar, GOOD_SLAVES, sTemp);
				AddQuestRecord("Slavetrader", "6");
				AddQuestUserData("Slavetrader", "sName", GetFullName(npchar));
				AddQuestUserData("Slavetrader", "sQty", sTemp);
				AddQuestUserData("Slavetrader", "sMoney", makeint(iSlaveMoney));
				break;
			}
			if (amount >= 200 && amount < 600)
			{
				dialog.text = "Ну что же, вы с честью вышли из сложной ситуации. И хотя добыча меньше, чем я ожидал, я все равно доволен. Итак, вы привезли "+ sTemp +" рабов. Ваша награда составляет " + FindRussianMoneyString(iSlaveMoney) + "";
				link.l1 = "Благодарю. Приятно иметь с вами дело, " + npchar.name + "!";
				link.l1.go = "Takeslaves_6_win";
				AddMoneyToCharacter(pchar, makeint(iSlaveMoney));
				RemoveCharacterGoods(Pchar, GOOD_SLAVES, sTemp);
				AddQuestRecord("Slavetrader", "6");
				AddQuestUserData("Slavetrader", "sName", GetFullName(npchar));
				AddQuestUserData("Slavetrader", "sQty", sTemp);
				AddQuestUserData("Slavetrader", "sMoney", makeint(iSlaveMoney));
				break;
			}
			if (amount >= 600 && amount < 1100)
			{
				dialog.text = "Да уж... Это конечно все понятно, но я рассчитывал на большее. Вы привезли всего лишь "+ sTemp +" рабов. Ну, да ладно, с другой стороны - вы устранили конкурентов, это тоже чего-то стоит. Ваша награда составляет " + FindRussianMoneyString(iSlaveMoney) + ".";
				link.l1 = "Благодарю. Спасибо за понимание, " + npchar.name + "!";
				link.l1.go = "Takeslaves_6_win";
				AddMoneyToCharacter(pchar, makeint(iSlaveMoney));
				RemoveCharacterGoods(Pchar, GOOD_SLAVES, sTemp);
				AddQuestRecord("Slavetrader", "6");
				AddQuestUserData("Slavetrader", "sName", GetFullName(npchar));
				AddQuestUserData("Slavetrader", "sQty", sTemp);
				AddQuestUserData("Slavetrader", "sMoney", makeint(iSlaveMoney));
				break;
			}
			if (amount >= 1100 && amount < 1600)
			{
				dialog.text = "Это конечно весьма занимательно, но... Гм... Похоже, я в тебе ошибся. Что ты мне привез"+ GetSexPhrase("","ла") +"? "+ sTemp +" рабов? А где остальной товар? И только не говори, что ты его утопил"+ GetSexPhrase("","а") +". Ты продал"+ GetSexPhrase("","а") +" его контрабандистам, или, что еще хуже - мерзавцу Вуазье. Убирайся с глаз долой, не желаю больше иметь с тобой никаких дел.";
				link.l1 = "Счастливо оставаться.";
				link.l1.go = "node_hanter_1";
				break;
			}
			dialog.text = "Это конечно весьма занимательно, но... Где рабы? Где наш товар? И только не говори, что ты его утопил"+ GetSexPhrase("","а") +". Ты продал"+ GetSexPhrase("","а") +" его контрабандистам, или, что еще хуже - мерзавцу Вуазье. Убирайся с глаз долой, не желаю больше иметь с тобой никаких дел.";
			link.l1 = "Счастливо оставаться.";
			link.l1.go = "node_hanter_1";
		break;
		
		case "node_hanter_1":
			dialog.text = "Это еще не все. Я никому не позволяю водить себя за нос! И за свое вероломство ты поплатишься - я обеспечу тебе проблемы, не сомневайся. А теперь проваливай!";
			link.l1 = "Черт бы тебя побрал с твоей работорговлей!";
			link.l1.go = "exit";
			AddQuestRecord("Slavetrader", "9");
			CloseQuestHeader("Slavetrader");
			ChangeCharacterHunterScore(pchar, NationShortName(sti(pchar.questTemp.Slavetrader.Nation)) + "hunter", 30);
			pchar.questTemp.Slavetrader = "End_quest";
		break;
			
		case "Takeslaves_6_win":
			dialog.text = "Я вижу, мы сработались, " + pchar.name + ". Я очень этому рад. Заходите ко мне примерно через месяц - возможно, я подберу работу по вашему профилю. У меня как раз намечается кое-что.";
			link.l1 = "Зайду обязательно! Сотрудничество с вами приносит неплохие дивиденды.";
			link.l1.go = "Takeslaves_7_win";
		break;
			
		case "Takeslaves_7_win":
			dialog.text = "Оно принесет вам целое состояние... Да, еще такой вопрос, " + pchar.name + ": во время абордажа вы ничего такого в каюте галеона не находили?";
			link.l1 = "Нет, ничего такого необычного мне не встречалось. А что, что-то должно было быть?";
			link.l1.go = "Nostatue";
			if (CheckCharacterItem(pchar, "talisman8"))
			{
				link.l2 = "Вы имеете в виду вот эту старинную застежку?";
				link.l2.go = "Yestatue";
			}
		break;
			
		case "Nostatue":
			dialog.text = "Может, должно, а может, и не должно... Ладно, не находили - так не находили. Жду вас через месяц. До свидания!";
			link.l1 = "До встречи, " + npchar.name + ".";
			link.l1.go = "exit";
			SaveCurrentQuestDateParam("pchar.questTemp.Slavetrader_wait_1");
			pchar.questTemp.Slavetrader = "wait_1";
		break;
			
		case "Yestatue":
			dialog.text = "Да, именно! Это фибула самих Медичи... слыхали о таких? Значит, она все-таки была в каюте этого мерзавца... Разрешите, я взгляну поближе?";
			link.l1 = "Конечно, держите.";
			link.l1.go = "Yestatue_1";
			RemoveItems(PChar, "talisman8", 1);
		break;
			
		case "Yestatue_1":
			Log_Info("Вы отдали оберег");
			PlaySound("interface\important_item.wav");
			dialog.text = "Так-так... Без сомнения, это она. Послушайте, " + pchar.name + ", продайте мне ее. Я готов заплатить сто тысяч золотом.";
			link.l1 = "Сто тысяч? Хм... Я соглас"+ GetSexPhrase("ен","на") +". Забирайте!";
			link.l1.go = "Buystatue";
			link.l2 = "Нет, не продам. Ценность этой застежки отнюдь не в золоте, которое можно за нее выручить. Я разбираюсь в подобных вещах.";
			link.l2.go = "Nobuystatue";
		break;
			
		case "Buystatue":
			dialog.text = "Превосходно! Я рад, что мы договорились. Получите ваши деньги. И жду вас через месяц. До свидания.";
			link.l1 = "До встречи, " + npchar.name + ".";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, 100000);
			SaveCurrentQuestDateParam("pchar.questTemp.Slavetrader_wait_1");
			pchar.questTemp.Slavetrader = "wait_1";
		break;
			
		case "Nobuystatue":
			dialog.text = "Понимаете, но мне очень нужна эта фибула! Я полностью с вами согласен - она ценна не деньгами - любой безграмотный торгаш не заплатит вам за нее и пяти тысяч. Но вы и впрямь знаете толк в тайных обрядах, если отказываетесь продать его за такую сумму\nРаз вы не хотите за нее денег, то я предлагаю обмен. У меня есть кое-что, что может вас заинтересовать. Вот, посмотрите. Великолепный легкий доспех! Оцените! Предлагаю в обмен на фибулу\nОна не единственная такая на свете. Вы моря"+ GetSexPhrase("к","чка") +", вы сможете отыскать себе еще. А вот мне сложнее. Ну, так что, согласны?";
			link.l1 = "Хех... Пожалуй, я соглас"+ GetSexPhrase("ен","на") +". Давайте мне доспех, и оставьте фибулу себе.";
			link.l1.go = "Nobuystatue_yes";
			link.l2 = "Нет. Фибула имеет для меня большую ценность, нежели этот доспех. Я оставлю его себе.";
			link.l2.go = "Nobuystatue_no";
		break;
			
		case "Nobuystatue_yes":
			dialog.text = "Превосходно! Я рад, что мы договорились. Этот доспех отныне ваш. Получите. И жду вас через месяц. До свидания.";
			link.l1 = "До встречи, " + npchar.name + ".";
			link.l1.go = "exit";
			TakeNItems(pchar, "cirass7", 1);
			Log_Info("Вы получили бригант");
			PlaySound("interface\important_item.wav");
			SaveCurrentQuestDateParam("pchar.questTemp.Slavetrader_wait_1");
			pchar.questTemp.Slavetrader = "wait_1";
		break;
			
		case "Nobuystatue_no":
			dialog.text = "Жаль, очень жаль... Ну что же, возьмите ее назад. Я не осуждаю вас. Жду вас через месяц. До свидания.";
			link.l1 = "До встречи.";
			link.l1.go = "exit";
			TakeNItems(pchar, "talisman8", 1);
			Log_Info("Вы получили оберег");
			PlaySound("interface\important_item.wav");
			SaveCurrentQuestDateParam("pchar.questTemp.Slavetrader_wait_1");
			pchar.questTemp.Slavetrader = "wait_1";
		break;
			
		case "EscapeSlave":
			dialog.text = "Вы вовремя, " + pchar.name + ". Задание есть, если вы готовы приступить к его выполнению прямо сейчас.";
			link.l1 = "Конечно, готов"+ GetSexPhrase("","а") +". Для этого я сюда и явил"+ GetSexPhrase("ся","ась") +".";
			link.l1.go = "EscapeSlave_1";
		break;
			
		case "EscapeSlave_1":
			dialog.text = "Отлично! Теперь по существу. Вы слышали последнюю новость?";
			link.l1 = "Гм... О чем это вы? Новостей много, и каждый день - новая.";
			link.l1.go = "EscapeSlave_2";
		break;
			
		case "EscapeSlave_2":
			dialog.text = "Эта новость касается непосредственно нашего дела. На Кюрасао произошел самый массовый побег рабов за всю историю Нового Света! Сбежало больше тысячи душ, причем попутно вырезали и сожгли несколько голландских факторий.";
			link.l1 = "Интересно. Продолжайте.";
			link.l1.go = "EscapeSlave_3";
		break;
			
		case "EscapeSlave_3":
			dialog.text = "Но они не просто сбежали - они невероятным образом скрылись с острова! Бесследно. Матиас Бек просто в ярости. Но это неважно... Важно то, что я прошу вас отправиться на Кюрасао, выяснить все подробности случившегося, найти этих беглецов и захватить\nНу и, конечно, не передать в руки голландского правосудия, по законам которого их ждет весьма печальная участь, а привезти мне. За каждого раба я заплачу по 300 песо - я слышал, это очень хорошие рабы.";
			link.l1 = "Задача ясна. Беру курс на Кюрасао. Ждите меня с хорошими новостями.";
			link.l1.go = "EscapeSlave_yes";
			link.l2 = "Знаете, я за это не возьмусь. Я не стану отнимать свободу у людей, которые добывали ее, рискуя жизнью. Они ее заслужили.";
			link.l2.go = "EscapeSlave_no";
		break;
			
		case "EscapeSlave_no":
			dialog.text = "Жаль, очень жаль... Не ждал я от вас подвоха в самый неподходящий момент... Я думаю, вам ясно, что после этого наше сотрудничество продолжаться не может. До свидания.";
			link.l1 = "Всего доброго.";
			link.l1.go = "exit";
			AddQuestRecord("Slavetrader", "8");
			AddQuestUserData("Slavetrader", "sSex", GetSexPhrase("ся","ась"));
			CloseQuestHeader("Slavetrader");
			pchar.questTemp.Slavetrader = "End_quest";
		break;
			
		case "EscapeSlave_yes":
			Slavetrader_GetEscapeShore();
			pchar.questTemp.Slavetrader.ShipName = GenerateRandomNameToShip(HOLLAND);
			pchar.questTemp.Slavetrader = "EscapeSlave_Villemstad";
			AddQuestRecord("Slavetrader", "22_1");
			AddQuestUserData("Slavetrader", "sName", GetFullName(npchar));
			DialogExit();
		break;
			
		case "Escape_slaves_win":
			int iSlaveMoneyH;
			string sNum;
			amount = 1100 - GetSquadronGoods(Pchar, GOOD_SLAVES);
			sTemp = GetSquadronGoods(Pchar, GOOD_SLAVES);
			iSlaveMoney = makeint(sTemp)*300;
			sNum = GetSquadronGoods(Pchar, GOOD_SLAVES) - 1100;
			iSlaveMoneyH = makeint(sNum)*100;
			if (amount < 0)
			{
				dialog.text = "Хе-хе! Да вы не только великолепно справились с непростым заданием, но еще и привезли рабов больше означенного количества - "+ sTemp +" рабов. Но "+ sNum +" рабов явно не из беглых с Кюрасао. Я заплачу за них по 100 песо за каждого. Полагаю, в накладе вы не останетесь. Ваша награда составляет 330 000 песо за основную партию рабов, и " + FindRussianMoneyString(iSlaveMoneyH) + " за превышение нормы, хе-хе.";
				link.l1 = "Ха-ха-ха, а вас не проведешь! Соглас"+ GetSexPhrase("ен","на") +", будь по-вашему, " + npchar.name + "!";
				link.l1.go = "Escape_slaves_win_1";
				AddMoneyToCharacter(pchar, 330000);
				AddMoneyToCharacter(pchar, makeint(iSlaveMoneyH));
				RemoveCharacterGoods(Pchar, GOOD_SLAVES, sTemp);
				AddQuestRecord("Slavetrader", "22_5");
				AddQuestUserData("Slavetrader", "sSex", GetSexPhrase("","а"));
				AddQuestUserData("Slavetrader", "sName", GetFullName(npchar));
				AddQuestUserData("Slavetrader", "sQty", sTemp);
				AddQuestUserData("Slavetrader", "sMoney", makeint(iSlaveMoneyH));
				break;
			}
			if (amount < 101 && amount >= 0)
			{
				dialog.text = "Вы великолепно выполнили непростую задачу и привезли "+ sTemp +" рабов. Ваша награда составляет " + FindRussianMoneyString(iSlaveMoney) + ".";
				link.l1 = "Благодарю. Приятно иметь с вами дело, " + npchar.name + "!";
				link.l1.go = "Escape_slaves_win_1";
				AddMoneyToCharacter(pchar, makeint(iSlaveMoney));
				RemoveCharacterGoods(Pchar, GOOD_SLAVES, sTemp);
				AddQuestRecord("Slavetrader", "22_6");
				AddQuestUserData("Slavetrader", "sName", GetFullName(npchar));
				AddQuestUserData("Slavetrader", "sQty", sTemp);
				AddQuestUserData("Slavetrader", "sMoney", makeint(iSlaveMoney));
				break;
			}
			if (amount >= 100 && amount < 600)
			{
				dialog.text = "Вы выполнили сложное задание, и хотя добыча меньше, чем я ожидал, я все равно доволен. Итак, вы привезли "+ sTemp +" рабов. Ваша награда составляет " + FindRussianMoneyString(iSlaveMoney) + ".";
				link.l1 = "Благодарю. Приятно иметь с вами дело, " + npchar.name + "!";
				link.l1.go = "Escape_slaves_win_1";
				AddMoneyToCharacter(pchar, makeint(iSlaveMoney));
				RemoveCharacterGoods(Pchar, GOOD_SLAVES, sTemp);
				AddQuestRecord("Slavetrader", "22_6");
				AddQuestUserData("Slavetrader", "sName", GetFullName(npchar));
				AddQuestUserData("Slavetrader", "sQty", sTemp);
				AddQuestUserData("Slavetrader", "sMoney", makeint(iSlaveMoney));
				break;
			}
			if (amount >= 600 && amount < 1100)
			{
				dialog.text = "Нашли? Гм... Ну а что вы мне привезли? "+ sTemp +" рабов? А где остальной товар? И только не говорите, что вы его утопили. Вы продали его контрабандистам, или, что еще хуже - мерзавцу Вуазье с Исла Тесоро. Убирайтесь с глаз долой, не желаю больше иметь с вами никаких дел.";
				link.l1 = "Счастливо оставаться.";
				link.l1.go = "node_hanter_1";
				break;
			}
			dialog.text = "Нашли? А где рабы? Где наш товар? И только не говорите, что вы его утопили. Вы продали его контрабандистам, или, что еще хуже - мерзавцу Вуазье. Убирайтесь с глаз долой, не желаю больше иметь с тобой никаких дел.";
			link.l1 = "Счастливо оставаться.";
			link.l1.go = "node_hanter_1";
		break;
		
		case "Escape_slaves_win_1":
			dialog.text = "Я весьма доволен вами, " + pchar.name + ". Очень доволен. Приходите через месяц, я подготовлю к этому времени очередное выгодное для нас обоих дельце.";
			link.l1 = "Я тоже рад"+ GetSexPhrase("","а") +" нашему сотрудничеству, " + npchar.name + ". Через месяц обязательно появлюсь.";
			link.l1.go = "exit";
			SaveCurrentQuestDateParam("pchar.questTemp.Slavetrader_wait_2");
			pchar.questTemp.Slavetrader = "wait_2";
		break;
			
		case "Slaveshore":
			dialog.text = "Вы очень вовремя появились, " + pchar.name + ". Мне как раз требуются услуги отважного и не очень щепетильного моряка, хе-хе. Вы готовы выполнить мое поручение?";
			link.l1 = "Да, я вас внимательно слушаю.";
			link.l1.go = "Slaveshore_1";
		break;
			
		case "Slaveshore_1":
			pchar.questTemp.Slavetrader.Island = Islands[GetCharacterCurrentIsland(pchar)].id;
			pchar.questTemp.Slavetrader.Island.Shore = GetIslandRandomShoreId(pchar.questTemp.Slavetrader.Island);
			pchar.questTemp.Slavetrader.ShipName = GenerateRandomNameToShip(sti(NPChar.nation));
			pchar.questTemp.Slavetrader.Nation = NPChar.nation;
			dialog.text = "На этот раз все предельно просто. Сегодня в акватории " + XI_ConvertString(pchar.questTemp.Slavetrader.Island.Shore + "Gen") + " встал на якорь пинас '" + pchar.questTemp.Slavetrader.ShipName + "' под флагом " + NationNameGenitive(sti(npchar.nation)) + ". На него тайно, при помощи местных контрабандистов, уже погружена большая партия 'черного дерева', не менее двух тысяч голов\nКоманда пинаса - обыкновенная портовая матросня, капитан - торгаш. В общем, никудышные вояки. Задача ваша - как обычно: абордировать судно, товар - забрать и привезти мне. Оплата - согласно нашей таксы, по 200 песо за единицу товара. Все, как обычно.";
			link.l1 = "Хм... Не совсем, как в прошлый раз. Вы предлагаете мне напасть на корабль ваших соотечественников!";
			link.l1.go = "Slaveshore_2";
		break;
			
		case "Slaveshore_2":
			dialog.text = "Я что-то не совсем понял вас, " + pchar.name + ". Какая разница, какой нации это судно? Или для вас это имеет принципиальное значение?";
			link.l1 = "Мне? Да мне-то наплевать, у золота нет национальности! Меня просто несколько удивило...";
			link.l1.go = "Slaveshore_3_yes";
			link.l2 = "Да, имеет. Ссориться с " + NationNameAblative(sti(npchar.nation)) + " я не намерен"+ GetSexPhrase("","а") +".";
			link.l2.go = "Slaveshore_3_no";
		break;
			
		case "Slaveshore_3_no":
			dialog.text = "Вот как? Вы что, шутите? Ну раз такое дело, тогда проваливайте. И забудьте обо всем, что здесь видели и слышали!";
			link.l1 = "Счастливо оставаться, " + npchar.name + ".";
			link.l1.go = "node_hanter_1";
		break;
			
		case "Slaveshore_3_yes":
			dialog.text = "Что вас удивило? Что мне тоже неинтересна национальность золотых монет? Уверяю, так и есть, и странно, что вы еще этого не заметили. Мало того, излишние патриотические пристрастия просто вредны для профессионального банкира, если он, конечно, не планирует окончить свои дни на паперти\nНо давайте обойдемся без философии. Ближе к делу - судно будет в нашей акватории до полуночи, так что времени у вас совсем немного. Вы готовы приступить к операции?";
			link.l1 = "Да, " + npchar.name + ", приступаю немедленно.";
			link.l1.go = "Slaveshore_4";
		break;
			
		case "Slaveshore_4":
			dialog.text = "Отлично. Я ни на секунду не сомневаюсь в успехе нашего предприятия. Удачи вам, " + pchar.name + ".";
			link.l1 = "Спасибо! До встречи.";
			link.l1.go = "exit";
            AddQuestRecord("Slavetrader", "10");
			AddQuestUserData("Slavetrader", "sName", GetFullName(npchar));
			AddQuestUserData("Slavetrader", "sShip", pchar.questTemp.Slavetrader.ShipName);
			pchar.quest.Slavetrader_ShoreAttack.win_condition.l1 = "location";
            pchar.quest.Slavetrader_ShoreAttack.win_condition.l1.location = pchar.questTemp.Slavetrader.Island;//отправляем в локацию
            pchar.quest.Slavetrader_ShoreAttack.function = "Slavetrader_CreateShoreShips";//создание кораблей
			SetFunctionTimerCondition("Slavetrader_ShoreShipsOver", 0, 0, 1, false);	//таймер
			pchar.questTemp.Slavetrader = "wait1";	//заглушка
		break;
			
		case "Pinas_lose":
		dialog.text = "Ну что, " + GetFullName(pchar) + ", как прошла операция? Судя по вашему унылому виду, вы ее провалили.";
			link.l1 = "Вы правы, черт возьми... Я... ну, это... опоздал"+ GetSexPhrase("","а") +". Задержал"+ GetSexPhrase("ся","ась") +" в таверне, а когда выш"+ GetSexPhrase("ел","ла") +" в море - уже никого не наш"+ GetSexPhrase("ел","ла") +".";
			link.l1.go = "Takeslaves_5_lose";
		break;
			
		case "Slaveshore_5":
			dialog.text = "" + pchar.name + ", прошу вас, успокойтесь. Это не моя вина! Дьявол, мне доложили слишком поздно... Это предательство! Меня подставил один из моих доверенных людей!";
			link.l1 = "Ладно, вижу, что не врешь. На твое счастье капитан пинаса перед смертью проболтался, что наши дела раскрыты. Если бы не эта его фраза, я бы уже прикончил"+ GetSexPhrase("","а") +" тебя... Но ты же говорил, чертов денежный мешок, что у тебя здесь на острове все схвачено!";
			link.l1.go = "Slaveshore_6";
		break;
			
		case "Slaveshore_6":
			dialog.text = "Засада была организована не местными властями, иначе я бы все знал об этом... " + pchar.name + ", сейчас не время для ругани и оскорблений. Мы с вами оба в смертельной опасности - нас выдал один из моих прежних подрядчиков\nМне удалось узнать, что все собранные доказательства - пакет бумаг - сейчас находятся в пути к нашему генерал-губернатору. Если они попадут к нему в руки - нам конец! И вам, кстати, в первую очередь.";
			link.l1 = "Так вот что имел в виду этот каналья капитан!";
			link.l1.go = "Slaveshore_7";
		break;
			
		case "Slaveshore_7": //выбор острова, куда бригантина пойдет
			switch (sti(NPChar.nation))
            {
                case HOLLAND :
					pchar.questTemp.Slavetraderbrig.Island = "Curacao";
                break;
                case FRANCE :
					pchar.questTemp.Slavetraderbrig.Island = "Nevis";
                break;
                case SPAIN :
					pchar.questTemp.Slavetraderbrig.Island = "Cuba2";  
                break;
                case ENGLAND :
					pchar.questTemp.Slavetraderbrig.Island = "Jamaica";     
                break;
			}
			pchar.questTemp.Slavetraderbrig.ShipName = GenerateRandomNameToShip(sti(NPChar.nation));//имя бригантины
			pchar.questTemp.Slavetrader.Nation = NPChar.nation;
			dialog.text = "Слушайте внимательно. У нас есть еще шанс. Пакет отправили бригантиной '" + pchar.questTemp.Slavetraderbrig.ShipName + "'. Это единственное, что я знаю. Бумаги везут генерал-губернатору, в его резиденцию на острове " + XI_ConvertString(pchar.questTemp.Slavetraderbrig.Island) + ". Вы должны перехватить ее, взять на абордаж и найти этот компромат.";
			link.l1 = "Большего мне не остается. Ну что же, молитесь, и за себя, и за меня, и надейтесь, что я ее догоню. А когда вернусь - мы еще продолжим наш разговор. И не думайте, что я все это вот так оставлю!";
			link.l1.go = "Slaveshore_8";
			AddQuestRecord("Slavetrader", "14");
			AddQuestUserData("Slavetrader", "sName", GetFullName(npchar));
			AddQuestUserData("Slavetrader", "sShipName", pchar.questTemp.Slavetraderbrig.ShipName);
			AddQuestUserData("Slavetrader", "sIsland", XI_ConvertString(GetIslandByArealName(pchar.questTemp.Slavetraderbrig.Island)));
			pchar.quest.Slavetrader_BrigAttack.win_condition.l1 = "location";
            pchar.quest.Slavetrader_BrigAttack.win_condition.l1.location = pchar.questTemp.Slavetraderbrig.Island;//отправляем в локацию
            pchar.quest.Slavetrader_BrigAttack.function = "Slavetrader_CreateBrig";//создание бригантины
			SetFunctionTimerCondition("Slavetrader_BrigOver", 0, 0, 15, false);	//таймер
			pchar.questTemp.Slavetrader = "wait1";	//это нода ожидания, пустая
		break;
		
		case "Slaveshore_8":
			dialog.text = "Главное - найдите пакет! Я буду уверен в своей безопасности, только если вы доставите его мне... Вот черт... " + pchar.name + ", кажется, у нас проблемы...";
			link.l1 = "Что еще такое?";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Slavetrader_enterSoldiers");
			break;
			
		case "Brig_lose":
			dialog.text = "Проклятие... А я так надеялся, на вас, " + pchar.name + ". Ну что же, больше никаких дел мы с вами вести не можем. Если мне не удасться откупиться от следствия, я буду вынужден бежать. Да и вам не советую здесь находиться - солдаты могут нагрянуть в любой момент. Прощайте.";
			link.l1 = "Прощайте, " + npchar.name + ".";
			link.l1.go = "exit";
			pchar.questTemp.Slavetrader = "End_quest";
		break;
			
		case "Letter_lose":
			dialog.text = "Были. Я это знаю достоверно. Ну что же, больше никаких дел мы с вами вести не можем - это теперь небезопасно. Прощайте.";
			link.l1 = "Прощайте, " + npchar.name + ".";
			link.l1.go = "exit";
			CloseQuestHeader("Slavetrader");
			pchar.questTemp.Slavetrader = "End_quest";
		break;
			
		case "Brig_win":
			dialog.text = "Великолепно! Я ни минуты не сомневался в вас, " + pchar.name + ". Пожалуйста, передайте бумаги мне, иначе у меня душа не на месте.";
			link.l1 = "Держите.";
			link.l1.go = "Brig_win_1";
		break;
			
		case "Brig_win_1":
			RemoveItems(PChar, "letter_1", 1);
			dialog.text = "Отлично... Теперь можно быть спокойным. Генерал-губернатор ни о чем не узнает, а с местными властями все вопросы я уже уладил, хотя пришлось посуетиться изрядно, скажу я вам.";
			link.l1 = "Все это конечно, хорошо, но вы не считаете, что должны компенсировать мне моральный и материальный урон из-за ваших непродуманных действий?";
			link.l1.go = "Brig_win_2";
		break;
			
		case "Brig_win_2":
			dialog.text = "Безусловно, " + pchar.name + ". Более того, я обязан вам очень многим. И весьма рассчитываю на продолжение нашего сотрудничества. Но прошу вас войти в мое положение - я понес огромные траты - лояльность губернатора и коменданта стоит недешево. Кроме того, пришлось замять убийство патрульного наряда в моей резиденции...";
			link.l1 = "Вы хотите сказать, что не намерены покрывать мои убытки?!";
			link.l1.go = "Brig_win_3";
		break;
			
		case "Brig_win_3":
			dialog.text = "Не горячитесь, " + pchar.name + ". У меня сейчас и впрямь проблемы с деньгами, поэтому предлагаю вам расчет несколько иного рода.";
			link.l1 = "Тогда я вас внимательно слушаю.";
			link.l1.go = "Brig_win_4";
		break;
			
		case "Brig_win_4":
			dialog.text = "Около года назад у южного побережья Мейна нас с компаньоном застал сильный шторм. Корабли разбило о скалы близ Бока де ла Сьерпе, и хоть на плаву они продержались недолго, мы успели вывезти на берег наш груз - сундуки с драгоценностями, в которых была большая партия камней и ювелирных изделий. Бухта там уютная, и припрятать сокровища не составило труда\nУтром, едва буря улеглась, на нас напали индейцы. Так погибли те немногие, которым удалось выжить в кораблекрушении, и мой компаньон в том числе. А мне с горсткой матросов удалось уйти на шлюпке\nМы благополучно добрались до Куманы, но вернуться за сундуками я не рискнул. Уверен, что местные дикари надежно охраняют от вторжения свой берег, а заодно и мой клад. Но вы - "+ GetSexPhrase("человек сильный и отважный","девушка сильная и отважная") +" - вполне управитесь с этой бандой краснокожих\nА драгоценностей там действительно много - покроют все понесенные вами убытки, а также затраты на экспедицию до южного Мейна.";
			link.l1 = "Хм... ладно. Тогда, пожалуй, отправлюсь к Кумане. Надеюсь, вы мне не врете. Имейте в виду: попробуете меня надуть - из под земли достану!";
			link.l1.go = "Brig_win_5";
		break;
			
		case "Brig_win_5":
			dialog.text = "Можете быть уверены, " + pchar.name + ", все сказанное - правда. Ну, и жду вас примерно через месяц - я уже наметил одно дело, которое призвано укрепить пошатнувшиеся позиции моего бизнеса. До встречи.";
			link.l1 = "До встречи, " + npchar.name + ".";
			link.l1.go = "exit";
			SaveCurrentQuestDateParam("pchar.questTemp.Slavetrader_wait_3");
			pchar.questTemp.Slavetrader = "wait_3";
			Pchar.quest.Slavetrader_Bonanza.win_condition.l1 = "location";
            Pchar.quest.Slavetrader_Bonanza.win_condition.l1.location = "Shore18";
            Pchar.quest.Slavetrader_Bonanza.function = "Slavetrader_Bonanza";
		break;
			
		case "SlaveGalleon":
			dialog.text = "Вот и вы, " + pchar.name + ". Замечательно, вы, как всегда, вовремя. Прежде, чем перейти к сути вопроса, я бы хотел немного ввести вас в курс дел, которые творятся на архипелаге вокруг рынка невольников. Думаю, вам это будет полезно. Знаете ли вы, что означает слово 'репартиментос'?";
			link.l1 = "Хм... Нет, " + npchar.name + ", я не знаю, что это такое. Но, судя по звучанию - близко к тому, чтобы что-то у кого-то отобрать. Я прав"+ GetSexPhrase("","а") +"?";
			link.l1.go = "SlaveGalleon_1";
		break;
			
		case "SlaveGalleon_end":
			dialog.text = "Вы, право, меня удивили. А чего вы ждали от меня? Убирайтесь!";
			link.l1 = "Незаконный бизнес, а тем более, торговля людьми, слишком угнетает морально. Счастливо оставаться.";
			link.l1.go = "node_hanter_1";
		break;
			
		case "SlaveGalleon_1":
			dialog.text = "Вы очень близки к истине, " + pchar.name + ". Именно отобрать, а конкретно - свободу. Репартиментос - это своеобразный хитрый способ закабаления индейцев под благовидными псевдо-законными предлогами - мирным путем, так сказать. Применяется испанскими властями по отношению к коренному населению Мейна. Вам интересно полушать подробности?";
			link.l1 = "Почему бы и нет?";
			link.l1.go = "SlaveGalleon_2";
		break;
			
		case "SlaveGalleon_2":
			dialog.text = "Представители испанской короны посещают индейские поселения. В них они, используя циничный обман и под действием прямых угроз, заставляют индейцев покупать у них за баснословные суммы всякую никому не нужную дрянь: гнилое мясо, старые бритвы и тому подобное. Причем в долг\nСпустя определенный период времени, допустим, год, посланцы возвращаются и требуют платы. Если индейцы не могут расплатиться - а так чаще всего и бывает - испанцы забирают с собой часть работоспособного мужского населения якобы на время, для того, чтобы отработать долг и 'научиться возделывать землю'\nСами понимаете, что назад в свои поселения эти индейцы уже никогда не возвращаются. Вот так наши доверчивые краснокожие братья попадают на плантации сахарного тростника и фактории красного дерева.";
			link.l1 = "Хех, ну это же надо... А индейцы не сопротивляются, когда их увозят в рабство? Или они не понимают?";
			link.l1.go = "SlaveGalleon_3";
		break;
			
		case "SlaveGalleon_3":
			dialog.text = "Понимают, наверное, но открыто выступать, когда тебе тычут бумагу с оттиском большого пальца вождя, мало кто осмеливается. Конечно, подобная тактика чаще применяется в отношении мирных племен - таких как араваки, например, или мискито. С воинственными ица и акавоями, а тем более, караибами, такой ход не пройдет - там и сила-то не всегда помогает\nНу, а теперь перейдем непосредственно к вашей задаче.";
			link.l1 = "Я уже чувствую запах больших денег! Слушаю вас, " + npchar.name + ".";
			link.l1.go = "SlaveGalleon_4";
		break;
			
		case "SlaveGalleon_4":
			Slavetrader_GetHispanShore();
			sTemp = pchar.questTemp.SlavetraderAreal.add; 
			pchar.questTemp.Slavetrader.ShipName = GenerateRandomNameToShip(SPAIN);
			dialog.text = "На днях " + sTemp + " выйдет тяжелый галеон под названием " + pchar.questTemp.Slavetrader.ShipName + ". Он перевозит огромную партию рабов - около 3 000 человек - индейцев, доставленных из различных поселений нижнего Ориноко, захваченных согласно тактике репартиментос\nГалеон идет в Сантьяго - сахарные плантации Кубы остро нуждаются в рабочих руках. Ваша задача - захватить этот галеон вместе с грузом. Оплата за товар - как обычно, по 200 песо за единицу.";
			link.l1 = "Хех! Звучит заманчиво. Я соглас"+ GetSexPhrase("ен","на") +".";
			link.l1.go = "SlaveGalleon_5";
			link.l2 = "Знаете, что-то не нравится мне эта ваша репартиментос, слишком уж она цинична. Пожалуй, я не стану заниматься этим делом.";
			link.l2.go = "SlaveGalleon_end";
		break;
			
		case "SlaveGalleon_5":
			sTemp = pchar.questTemp.SlavetraderAreal.add; 
			dialog.text = "Ну что же, тогда я желаю вам удачи. Имейте в виду: этим галеоном управляет очень опытный военный моряк. Бой с ним будет нелегким, так что подготовьтесь, как следует. И не теряйте времени - ему потребуется дней пятнадцать-двадцать, чтобы добраться " + sTemp + " до Сантьяго. Постарайтесь не упустить его, смотрите в оба - этот галеон вы легко отличите от прочих кораблей\nДа! Чуть не забыл! Кроме того, на корабле будет полно всяких индейских побрякушек - краснокожие платят долги произведениями своих ремесел и предметами культа. Если обнаружите на галеоне что-нибудь необычное - обязательно прихватите и привезите мне - я щедро заплачу за каждую ценную находку.";
			link.l1 = "Я вас понял"+ GetSexPhrase("","а") +". Немедленно выдвигаюсь.";
			link.l1.go = "exit";
			SlavetraderGalleonInWorld();
			SetFunctionTimerCondition("Slavetrader_SlaveGalleonOver", 0, 0, 20, false);
			pchar.questTemp.Slavetrader = "wait1";
			AddQuestRecord("Slavetrader", "18");
			AddQuestUserData("Slavetrader", "sSex", GetSexPhrase("ым","ой"));
			AddQuestUserData("Slavetrader", "sShipName", pchar.questTemp.Slavetrader.ShipName);
			AddQuestUserData("Slavetrader", "sAreal", sTemp);
		break;
			
		case "Lostgalleon":
			dialog.text = "Эх, " + pchar.name + ", это была моя последняя надежда... Поэтому я поручил дело вам - все равно кроме вас с ним никто не смог бы справиться... Как оказалось - и вы тоже. Ну что же, будем прощаться. После давешнего провала и последовавших за ним нехороших слухов, вся моя клиентура разбежалась. Я практически банкрот, и, возможно, мне придется покинуть этот город. Но я вас не виню - задача была очень непростой. Эх-х... Прощайте, " + pchar.name + ".";
			link.l1 = "Мне очень жаль, " + npchar.name + ", что все так получилось. Честное слово. Может, все еще образуется. До свидания.";
			link.l1.go = "exit";
			CloseQuestHeader("Slavetrader");
			pchar.questTemp.Slavetrader = "End_quest";
		break;
			
		case "Wingalleon":
			pchar.questTemp.Slavetrader.Nation = npchar.nation;
			amount = 3000 - GetSquadronGoods(Pchar, GOOD_SLAVES);
			sTemp = GetSquadronGoods(Pchar, GOOD_SLAVES);
			iSlaveMoney = makeint(sTemp)*200;
			if(amount < 1) 
			{
				dialog.text = "Фух, камень с души свалился... Не зря я вам доверился, не зря... А к чему такая ирония? Что-то не так?";
				link.l1 = "А к тому, уважаемый, что ваш галеон был совсем не галеон... Ну, или очень большой галеон... Дьявол!! Это был линейный корабль! А вы меня об этом не предупредили! Тем не менее, я ухитрил"+ GetSexPhrase("ся","ась") +" его захватить. У меня в трюмах находится "+ sTemp +" рабов, и я готов"+ GetSexPhrase("","а") +" вам их передать. Согласно нашего уговора, вы должны мне " + FindRussianMoneyString(iSlaveMoney) + ". И не мешало бы еще и компенсацию за дезинформацию.";
				link.l1.go = "Wingalleon_1";
			}
			else
			{
			dialog.text = "Нашли галеон? А где рабы? Там должно было быть не меньше трех тысяч рабов! Черт возьми, кругом одни негодяи и предатели! Вот от кого-кого, а от вас я этого не ожидал... Вы были моей последней надеждой\nНу, раз так... Клянусь, я потрачу остатки своего состояния и пойду на паперть, но сделаю так, что за вами будет гоняться весь флот " + NationNameGenitive(sti(npchar.nation)) + "! Убирайтесь с глаз моих долой!";
				link.l1 = "Эм-м...";
				link.l1.go = "Wingalleon_goaway";
			}
		break;
			
		case "Wingalleon_goaway":
			AddQuestRecord("Slavetrader", "9");
			CloseQuestHeader("Slavetrader");
			ChangeCharacterHunterScore(pchar, NationShortName(sti(pchar.questTemp.Slavetrader.Nation)) + "hunter", 70);
			pchar.questTemp.Slavetrader = "End_quest";
			DialogExit();
		break;
			
		case "Wingalleon_1":
			dialog.text = "Да вы что! Клянусь, я не знал этого. Должен был выйти именно тяжелый галеон, но никак не линейный корабль! Видимо, в последний момент что-то изменилось... Но вы же справились!\nНасчет денег и компенсации ваших внеплановых издержек я полностью согласен, все признаю, но есть одно обстоятельство непреодолимой силы - у меня просто нет сейчас такой большой суммы. Недавние проблемы... ну, вы и сами все знаете. Но только не горячитесь, " + pchar.name + ", ради Бога. Вы передаете мне товар, я его реализую - заказчик уже ждет\nРовно через пять дней у меня будет вся сумма, и я полностью рассчитаюсь с вами. Можете не сомневаться. А для пущей уверенности, я готов дать вам всю наличность, что у меня есть на данный момент - все мои кредиты.";
			link.l1 = "Хм... Я рассчитывал"+ GetSexPhrase("","а") +" получить деньги сейчас. Знали бы вы, какой бой мне пришлось выдержать! А, ладно... Войду в ваше положение. Но имейте в виду: только попробуйте меня надуть - в Европе достану!";
			link.l1.go = "Wingalleon_yes";
			link.l2 = "Знаете, что, " + npchar.name + ", катитесь вы куда подальше. Мы так не договаривались. Вы даже не представляете, какой бой мне пришлось выдержать. Я оставлю всех рабов себе и реализую их без вашего посредничества.";
			link.l2.go = "Wingalleon_no";
		break;
			
		case "Wingalleon_no":
			dialog.text = "Ах вот, значит, как мы заговорили! Значит, пока доверчивый " + npchar.name + " был для вас дойной коровой, вас все устраивало, а как только дело коснулось отсрочки, вы готовы переступить через него и вести дела самостоятельно. При этом вы сразу забыли, что наводку на эту добычу получили от меня\nНу, раз так... Клянусь, я потрачу остатки своего состояния и пойду на паперть, но сделаю так, что за вами будет гоняться весь флот " + NationNameGenitive(sti(npchar.nation)) + "! Убирайтесь с глаз моих долой!";
			link.l1 = "Не пугай меня, пустой денежный мешок. Твой флот я скормлю крабам. Счастливо оставаться!";
			link.l1.go = "exit";
			AddQuestRecord("Slavetrader", "9");
			CloseQuestHeader("Slavetrader");
			ChangeCharacterHunterScore(pchar, NationShortName(sti(pchar.questTemp.Slavetrader.Nation)) + "hunter", 70);
			pchar.questTemp.Slavetrader = "End_quest";
		break;
			
		case "Wingalleon_yes":
			dialog.text = "Спасибо за понимание, " + pchar.name + ". Обещаю, все будет в лучшем виде, так что ваши угрозы здесь ни к чему\nВозьмите вот это в качестве аванса. Здесь пятнадцать сундуков. Десять пойдут в зачет при окончательном расчете, а пять заберите себе в качестве компенсации морального ущерба. За остальным заходите через пять дней.\nНе забудьте принести все индейские предметы, которые нашли на захваченном корабле... если нашли, конечно. Сейчас мне все равно нечего вам за них предложить.";
			link.l1 = "Ровно через пять дней, " + npchar.name + ". Ровно через пять дней...";
			link.l1.go = "Wingalleon_yes_1";
		break;
			
		case "Wingalleon_yes_1":
			TakeNItems(pchar, "chest", 15);
			Log_Info("Вы получили кредитные сундуки");
			PlaySound("interface\important_item.wav");
			SaveCurrentQuestDateParam("pchar.questTemp.Slavetrader_wait_4");
			pchar.questTemp.Slavetrader = "wait_4";
			AddQuestRecord("Slavetrader", "20");
			AddQuestUserData("Slavetrader", "sName", GetFullName(npchar));
			sTemp = GetSquadronGoods(Pchar, GOOD_SLAVES);
			pchar.questTemp.Slavetrader.iSlaveMoney = makeint(sTemp)*200-120000;
			RemoveCharacterGoods(Pchar, GOOD_SLAVES, sTemp);
			DialogExit();
		break;
	
		case "FindRat":
			dialog.text = "Как я и обещал, " + pchar.name + ", я готов с вами расплатиться. Рабы проданы, заказчик доволен, и мы с вами тоже. За вычетом аванса причитающаяся вам сумма составляет " + FindRussianMoneyString(sti(pchar.questTemp.Slavetrader.iSlaveMoney)) + ". Прошу вас, получите ваши деньги.";
			link.l1 = "Превосходно, " + npchar.name + ". Приятно иметь дело с человеком, способным держать свое слово...";
			link.l1.go = "FindRat_1";
		break;
			
		case "FindRat_1":
			AddMoneyToCharacter(pchar, makeint(pchar.questTemp.Slavetrader.iSlaveMoney));
			dialog.text = "Вы всегда можете верить моему слову, " + pchar.name + ". Я еще ни разу не дал вам повода усомниться в этом. Так будет и впредь. Честность партнеров друг с другом - это фундамент успеха в любом совместном бизнесе\nТеперь об индейских артефактах. Показывайте, что у вас там есть, а то я, как истовый коллекционер, уже весь извелся.";
			link.l1 = "Гхм... Смотрите, пожалуйста.";
			link.l1.go = "FindRat_2";
		break;
			
		case "FindRat_2":
			if (CheckCharacterItem(pchar, "jewelry30"))
			{
				dialog.text = "Вот! Замечательно! Золотой ритуальный нож! Это редкая вещица. Я давно хотел иметь такую в своей коллекции. Предлагаю вам за нее 30 000, или обмен на амулет Эхекатль, у меня таких два.";
				link.l1 = "Я возьму деньги.";
				link.l1.go = "BG_money";
				link.l2 = "Я меняю этот предмет на амулет Эхекатль.";
				link.l2.go = "BG_change";
				link.l3 = "Я оставлю этот нож себе.";
				link.l3.go = "BG_no";
			}
			else
			{
				dialog.text = "Так-так... К сожалению, нет ничего такого, что могло бы меня заинтересовать.";
				link.l1 = "Ну, нет так нет, как скажете.";
				link.l1.go = "BG_PF";
			}
		break;
			
		case "BG_money":
			dialog.text = "Замечательно! Вот ваши 30 000, а этот индейский нож теперь мой.";
			link.l1 = "Прекрасно. Ну, если это все, что вас заинтересовало...";
			link.l1.go = "BG_PF";
			AddMoneyToCharacter(pchar, 30000);
			Log_Info("Вы отдали золотой нож");
			PlaySound("interface\important_item.wav");
			RemoveItems(PChar, "jewelry30", 1);
		break;
			
		case "BG_change":
			dialog.text = "Замечательно! Вот ваш амулет, а этот индейский нож теперь мой.";
			link.l1 = "Прекрасно. Ну, если это все, что вас заинтересовало...";
			link.l1.go = "BG_PF";
			Log_Info("Вы отдали золотой нож");
			Log_Info("Вы получили амулет Эхекатль");
			PlaySound("interface\important_item.wav");
			RemoveItems(PChar, "jewelry30", 1);
			TakeNItems(pchar, "obereg_9", 1);
		break;
			
		case "BG_no":
			dialog.text = "Ну, как знаете. Хотя жаль, очень жаль...";
			link.l1 = "Ну, если это все, что вас заинтересовало...";
			link.l1.go = "BG_PF";
		break;
			
		case "BG_PF":
			dialog.text = "Стойте! Дайте гляну еще разок...";
			link.l1 = "Пожалуйста, смотрите, выбирайте.";
			link.l1.go = "PF_check";
		break;
			
		case "PF_check":
			if (CheckCharacterItem(pchar, "mineral31"))
			{
				dialog.text = "Вот! Я ее сразу не заметил! Меня интересует вот эта кость с медным кольцом. Очень занятный предмет, скажу я вам... Я готов заплатить за нее 20 000 песо, либо обменять на амулет 'Чимарута'.";
				link.l1 = "Я возьму деньги.";
				link.l1.go = "PF_money";
				link.l2 = "Я меняю этот предмет на амулет 'Чимарута'.";
				link.l2.go = "PF_change";
				link.l3 = "Я оставлю этот артефакт себе.";
			link.l3.go = "PF_no";
			}
			else
			{
				dialog.text = "Нет, гм... Все-таки ничего нужного мне у вас нет.";
				link.l1 = "Ну и ладно! На нет и суда нет.";
				link.l1.go = "FindRat_3";
			}
		break;
			
		case "PF_money":
			dialog.text = "Замечательно! Вот ваши 20 000, а эта кость теперь моя.";
			link.l1 = "Прекрасно. Меня наша сделка весьма устроила.";
			link.l1.go = "FindRat_3";
			AddMoneyToCharacter(pchar, 20000);
			Log_Info("Вы отдали заговоренную кость");
			PlaySound("interface\important_item.wav");
			RemoveItems(PChar, "mineral31", 1);
		break;
			
		case "PF_change":
			dialog.text = "Замечательно! Вот ваш амулет, а эта кость теперь моя.";
			link.l1 = "Прекрасно. Меня наша сделка весьма устроила.";
			link.l1.go = "FindRat_3";
			Log_Info("Вы отдали заговоренную кость");
			Log_Info("Вы получили амулет 'Чимарута'");
			PlaySound("interface\important_item.wav");
			RemoveItems(PChar, "mineral31", 1);
			TakeNItems(pchar, "amulet_11", 1);
		break;
			
		case "PF_no":
			dialog.text = "Ну, как знаете. Хотя жаль, очень жаль...";
			link.l1 = "Эта кость мне нужна само"+ GetSexPhrase("му","й") +", извините.";
			link.l1.go = "FindRat_3";
		break;
			
		case "FindRat_3":
			dialog.text = "Ну что же... Захватив этот галеон... простите, линейный корабль, вы буквально спасли меня. Я рад нашему сотрудничеству, " + pchar.name + ". Лучше вас, наверное, у меня не было ни одного агента.";
			link.l1 = "Польщен"+ GetSexPhrase("","а") +", не скрою. Но вы несколько преувеличиваете мои заслуги...";
			link.l1.go = "FindRat_4";
		break;
			
		case "FindRat_4":
			dialog.text = "Я говорю совершенно серьезно. И именно потому, что вы обладаете столь выдающимися способностями, и потому, что я вам полностью доверяю, я прошу вас выполнить мое очередное поручение.";
			link.l1 = "Хех! Неожиданно! Слушаю внимательно. Где очередной галеон с рабами?";
			link.l1.go = "FindRat_5";
		break;
			
		case "FindRat_5":
			dialog.text = "На этот раз у меня будет для вас иное задание, не имеющее отношения к рабам. Вы удивлены? Я хорошо заплачу за выполнение этого поручения... Очень хорошо заплачу.";
			link.l1 = "Давайте ближе к делу.";
			link.l1.go = "FindRat_6";
		break;
			
		case "FindRat_6":
			dialog.text = "Это дело напрямую связано с недавними событиями, к которым вы, между прочим, тоже имели отношение... Итак, как вам известно, я занимаюсь не вполне законным бизнесом - работорговлей. Также вам известно, что я нанимаю для выполнения поручений каперов, таких, как вы\nНедавно один из моих людей, по совершенно непонятной мне причине, предал меня - составил донос и собрал доказательства, уличающие меня и моих доверенных лиц в незаконной торговле рабами. Последствия вы видели - из соседней колонии сюда прибыл корабль с солдатами, ну... остальное вы знаете\nМне с большим трудом удалось урегулировать ситуацию, а также скрыть обстоятельства уничтожения пинаса и убийства солдат в моем доме. Как вы понимаете, предательство не может остаться безнаказанным. Кроме того, я не могу жить и работать спокойно, зная, что эта крыса жива и разгуливает по архипелагу. Я натравил на этого негодяя охотников за головами, но пока результат нулевой\nЯ прошу вас лично заняться этим делом. Тем более, что предательство этого мерзавца коснулось непосредственно и вас.";
			link.l1 = "Хм... Этого негодяя следует вздернуть на нок-рее! Сообщите мне более подробную информацию о нем, ну и, конечно, размер гонорара за работу.";
			link.l1.go = "FindRat_7";
		break;
			
		case "FindRat_7":
			dialog.text = "Насчет вознаграждения не беспокойтесь. Я щедро заплачу вам за его уничтожение, и не только деньгами. Я не пожалею лучших вещей из своей коллекции. Теперь о нем. Эту крысу зовут Франсуа Гонтьер\nНедавно, чтобы замести следы - ибо он знает, что я за ним охочусь - он продал свой фрегат на одной из верфей архипелага и скрылся. Мне удалось выяснить у своих коллег, что его недавно видели в Панаме. Пожалуй, вам стоит начать поиски именно оттуда.";
			link.l1 = "Ну что же, немедленно выдвигаюсь.";
			link.l1.go = "FindRat_8";
		break;
			
		case "FindRat_8":
			dialog.text = "Желаю вам удачи. И будьте осторожны: каналья Гонтьер весьма опытный моряк, и располагает командой отчаянных головорезов. Терять ему нечего, поэтому сражаться он будет отчаянно.";
			link.l1 = "И не таких грозных видали... Но я приму к сведению ваши слова. До свидания, и будьте уверены - я отыщу его даже в преисподней.";
			link.l1.go = "exit";
			pchar.questTemp.Slavetrader.ShipName = GenerateRandomNameToShip(SPAIN);
			AddQuestRecord("Slavetrader", "21");
			AddQuestUserData("Slavetrader", "sName", GetFullName(npchar));
			pchar.questTemp.Slavetrader = "FindRatPanama";
		break;
			
		case "Wincorvette":
			dialog.text = "Великолепно! Пусть теперь строчит свои доносы медузам. Никто не смеет гадить мне безнаказанно! Спасибо вам, " + pchar.name + ", вы просто незаменимый человек.";
			link.l1 = "Спасибо, " + npchar.name + ", за лестную оценку моих действий. Что насчет оплаты?";
			link.l1.go = "Wincorvette_1";
		break;
			
		case "Wincorvette_1":
			dialog.text = "Да, конечно. За эту сложнейшую работу я рассчитаюсь соответствующим образом. Я презентую вам вот эту отличную подзорную трубу.";
			link.l1 = "Ух ты, какой подарок!";
			link.l1.go = "Wincorvette_2";
		break;
			
		case "Wincorvette_2":
			dialog.text = "Кроме того, я выплачу вам 100 000 песо премии и 50 000 песо на покрытие дорожных издержек.";
			link.l1 = "Спасибо, " + npchar.name + ". В очередной раз повторюсь - с вами приятно работать.";
			link.l1.go = "Wincorvette_3";
			Log_Info("Вы получили отличную подзорную трубу");
			PlaySound("interface\important_item.wav");
			TakeNItems(pchar, "spyglass4", 1);
		break;
			
		case "Wincorvette_3":
			dialog.text = "Ну, и как обычно, через месяц, я жду вас у себя. Готовится очень масштабное дело, и вам понадобится хорошо оснащенная эскадра. Прошу, отнеситесь к моим словам серьезно и подготовьтесь, как следует. Если дело выгорит, мы с вами станем богачами.";
			link.l1 = "Хорошо, " + npchar.name + ". Прибуду во всеоружии.";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, 150000);
			AddQuestRecord("Slavetrader", "21_13");
			AddQuestUserData("Slavetrader", "sName", GetFullName(npchar));
			SaveCurrentQuestDateParam("pchar.questTemp.Slavetrader_wait_5");
			pchar.questTemp.Slavetrader = "wait_5";
		break;
			
		case "Lostcorvette":
			dialog.text = "Жаль, очень жаль... Что же, не расстраивайтесь сильно: вы не перв"+ GetSexPhrase("ый","ая") +", кому не удалось поймать этого проходимца. Ничего, я все равно его прищучу\nНу а вас я жду через месяц. Готовится очень масштабное дело, и вам понадобится хорошо оснащенная эскадра. Прошу, отнеситесь к моим словам серьезно и подготовьтесь, как следует. Если дело выгорит, мы с вами станем богачами.";
			link.l1 = "Хорошо, " + npchar.name + ". Прибуду во всеоружии.";
			link.l1.go = "exit";
			AddQuestRecord("Slavetrader", "21_14");
			AddQuestUserData("Slavetrader", "sSex", GetSexPhrase("","а"));
			AddQuestUserData("Slavetrader", "sName", GetFullName(npchar));
			SaveCurrentQuestDateParam("pchar.questTemp.Slavetrader_wait_5");
			pchar.questTemp.Slavetrader = "wait_5";
		break;
		
		case "Havana_fort":
			dialog.text = "Вы очень вовремя, " + pchar.name + "! Я уже было начал волноваться, и собирался послать на ваши поиски человека\nНу-с, приступим! Задача на этот раз перед вами будет стоять очень серьезная, но и вознаграждение будет соответствующим. После проведенной операции вы получите миллион, или больше.";
			link.l1 = "Вот это дело! Слушаю вас внимательно, " + npchar.name + ".";
			link.l1.go = "Havana_fort_1";
		break;
		
		case "Havana_fort_1":
			dialog.text = "В течение последнего месяца в Гавану со всего Мейна, мелкими партиями, свозились порабощенные индейцы, кроме того, туда прибыли из Африки и разгрузились несколько галеонов с 'черной слоновой костью'. В данный момент в Гаване, за высокими стенами форта, находится не меньше пяти тысяч рабов.";
			link.l1 = "Чувствую я, что речь пойдет ни больше, ни меньше, как о штурме Гаваны.";
			link.l1.go = "Havana_fort_2";
		break;
		
		case "Havana_fort_2":
			dialog.text = "Вы все правильно понимаете, " + pchar.name + ". Именно это я и хочу вам поручить. Вам и только вам. Не думаю, что кто-либо из моих других агентов сможет провести столь серьезную операцию\nВы ведь, безусловно, возьметесь за это дело?";
			link.l1 = "Честно сказать, " + npchar.name + ", я несколько ошарашен"+ GetSexPhrase("","а") +". Не думал"+ GetSexPhrase("","а") +" я, что ваша деятельность столь... масштабна. Берусь конечно. " + RandSwear() + "";
			link.l1.go = "Havana_fort_3";
			link.l2 = "Знаете что, " + npchar.name + ", это уже ни в какие ворота не лезет. Меня утомили ваши сюрпризы. С вашей алчностью завтра мне придется идти войной на Испанию. Если вам нужны эти рабы - штурмуйте Гавану лично.";
			link.l2.go = "Havana_fort_not";
		break;
		
		case "Havana_fort_not":
			dialog.text = "Не ожидал я от вас этого. Не ожидал... Черт возьми, что я теперь скажу заказчику? Ладно. Не хотите - как хотите, буду искать другого исполнителя. Прощайте, " + pchar.name + ". Не думаю, что я буду впредь пользоваться вашими услугами. И помните - вы добровольно бросили дело, которое могло обеспечить всех ваших потомков до седьмого колена.";
			link.l1 = "Всех денег не заработаешь. Вы никогда не слышали поговорку 'большая ложка рот дерет'? Всего доброго, " + npchar.name + ".";
			link.l1.go = "exit";
			AddQuestRecord("Slavetrader", "8");
			AddQuestUserData("Slavetrader", "sSex", GetSexPhrase("ся","ась"));
			CloseQuestHeader("Slavetrader");
			pchar.questTemp.Slavetrader = "End_quest";
		break;
		
		case "Havana_fort_3":
			dialog.text = "Я не сомневался, что услышу именно такой ответ. Немного подробностей: форт Гаваны и так взять непросто, но теперь эта задача стала еще сложнее\nУ берегов Гаваны в данный момент постоянно крейсируют два линейных корабля - охраняют подступы к городу с моря. Вам нужно будет избавиться от этих кораблей, прежде чем приступить к штурму...";
			link.l1 = "Понятно. Мне не впервой вести сражение против линейных кораблей. Сколько у меня времени?";
			link.l1.go = "Havana_fort_4";
		break;
		
		case "Havana_fort_4":
			dialog.text = "Немного. Недели три, не больше. После этого рабы будут отправлены на испанские фактории Кубы. Так что вам следует поторопиться.";
			link.l1 = "Тогда не будем медлить. Я отправляюсь!";
			link.l1.go = "Havana_fort_5";
		break;
		
		case "Havana_fort_5":
			dialog.text = "Одну минутку! " + pchar.name + ", у нас с вами никогда не было недопониманий и разногласий. Но все же хочу поставить вас в известность о текущем положении дел. Я рассчитываю на вас, а на меня рассчитывает заказчик\nИ я, и он, уже вложили в это предприятие силы и средства, и немаленькие - для получения информации, которую я вам сейчас предоставил. Все захваченные рабы, все пять тысяч единиц товара, должны быть доставлены мне в целости и сохранности\nВ противном случае мы примем очень и очень радикальные меры в отношении вас. Прошу вас не обижаться на это предупреждение, а просто принять к сведению.";
			link.l1 = "Можете не переживать, " + npchar.name + ", я понимаю, что такое бизнес. До встречи.";
			link.l1.go = "exit";
			AddQuestRecord("Slavetrader", "24");
			AddQuestUserData("Slavetrader", "sSex", GetSexPhrase("","а"));
			AddQuestUserData("Slavetrader", "sName", GetFullName(npchar));
			pchar.quest.Slavetrader_HavanaAttack.win_condition.l1 = "location";
            pchar.quest.Slavetrader_HavanaAttack.win_condition.l1.location = "Cuba2";//отправляем в локацию
            pchar.quest.Slavetrader_HavanaAttack.function = "Slavetrader_CreateLineShips";//создание линейных кораблей
			SetFunctionTimerCondition("Slavetrader_HavanaOver", 0, 0, 20, false);	//таймер
			characters[GetCharacterIndex("Havana_Mayor")].dialog.captureNode = "Slavetrader_HavanaAttack"; //капитулянтская нода мэра
			pchar.questTemp.Slavetrader = "wait1";
		break;
		
		case "Win_Havana_Fort":
			pchar.quest.Slavetrader_FiveTSlavesOver.over = "yes";
			amount = 5000 - GetSquadronGoods(Pchar, GOOD_SLAVES);
			sTemp = GetSquadronGoods(Pchar, GOOD_SLAVES);
			if (amount < 1)
			{
				dialog.text = "Ну-с, каковы результаты вашей победы в материальном эквиваленте?";
				link.l1 = "У меня в трюмах находится " + sTemp + " рабов.";
				link.l1.go = "Havana_Fort_yes";
				break;
			}
			if (amount < 4500 && amount >= 1)
			{
				dialog.text = "Так-так... Вы что, забыли, что я вам говорил? Вы должны были привезти мне не меньше пяти тысяч рабов, а у вас их почему-то всего " + sTemp + ". Как так получилось?";
				link.l1 = "Гм... Не все перенесли дорогу в трюмах сюда от Гаваны...";
				link.l1.go = "Havana_Fort_no";
				break;
			}
			dialog.text = "Так-так... Вы решили меня надуть? Вы что, забыли, что я вам говорил? Где мои рабы? Где они, я вас спрашиваю?!";
			link.l1 = "Гм... Тут такое дело вышло...";
			link.l1.go = "Havana_Fort_no";
		break;
		
		case "Havana_Fort_no":
			dialog.text = "Ладно. Не нужно никаких объяснений. Я даю вам неделю на то, чтобы вы доставили мне согласно нашего договора не меньше пяти тысяч рабов. В противном случае - пеняйте на себя!";
			link.l1 = "Хорошо, хорошо, не кипятитесь, будут вам ваши пять тысяч рабов!";
			link.l1.go = "exit";
			AddQuestRecord("Slavetrader", "29");
			SetFunctionTimerCondition("Slavetrader_HavanaSeekOver", 0, 0, 7, false);
			pchar.questTemp.Slavetrader = "Havana_seekslaves";
		break;
		
		case "Havana_Fort_yes":
			dialog.text = "Великолепно! Вы как всегда, отлично справились с моим поручением. Я весьма и весьма вами доволен.";
			link.l1 = "Я тоже собой довол"+ GetSexPhrase("ен","ьна") +"... Но еще больше буду довол"+ GetSexPhrase("ен","ьна") +", когда получу деньги за товар.";
			link.l1.go = "Havana_Fort_yes_1";
		break;
		
		case "Havana_Fort_yesA":
		dialog.text = "Что же, я этому очень и очень рад. Несмотря на проволочку, вы блестяще справились с моим заданием.";
			link.l1 = "Ну, а теперь я хочу получить деньги за товар.";
			link.l1.go = "Havana_Fort_yes_1";
			pchar.quest.Slavetrader_HavanaSeekOver.over = "yes";
		break;
		
		case "Havana_Fort_yes_1":
			sTemp = GetSquadronGoods(Pchar, GOOD_SLAVES);
			iSlaveMoney = makeint(sTemp)*200;
			dialog.text = "Да, безусловно. Я передам рабов заказчику, он рассчитается, и вы получите свои деньги. Все, как в прошлый раз. Давайте посчитаем: вы привезли " + sTemp + " рабов. Соответственно, причитающаяся вам сумма составляет " + FindRussianMoneyString(iSlaveMoney) + ". Через неделю приходите ко мне за расчетом.";
			link.l1 = "Хорошо, " + npchar.name + ", договорились. Ждите меня через неделю. Но смотрите...";
			link.l1.go = "Havana_Fort_yes_2";
			RemoveCharacterGoods(Pchar, GOOD_SLAVES, sTemp);
		break;
		
		case "Havana_Fort_yes_2":
			dialog.text = "" + pchar.name + ", прошу вас, не надо продолжать. Мы же партнеры, а между партнерами не может быть обмана и недоверия. Я обещал вам огромные деньги - вы их получили, я обещал вам прибыльные задания - они у вас есть. Я компенсировал ваши затраты и покрывал ваши расходы даже в самые тяжелые для моего бизнеса времена. Вы можете пожаловаться, что я хоть раз не сдержал слова?";
			link.l1 = "Гм... Нет.";
			link.l1.go = "Havana_Fort_yes_3";
		break;
		
		case "Havana_Fort_yes_3":
			dialog.text = "Вот видите... " + pchar.name + ", вы мой лучший агент, и я рассчитываю вести с вами бизнес в дальнейшем. Может, хватит уже постоянно высказывать мне свое недоверие, да еще в такой... резкой форме?";
			link.l1 = "Хорошо, " + npchar.name + ". Просто вы и меня поймите: миллион - не маленькая сумма.";
			link.l1.go = "Havana_Fort_yes_4";
		break;
		
		case "Havana_Fort_yes_4":
			dialog.text = "Я вас прекрасно понимаю, но и вы поймите, что товар надо сначала реализовать, и только потом получить деньги.";
			link.l1 = "Ладно. Будем считать, что мы друг друга поняли.";
			link.l1.go = "Havana_Fort_yes_5";
		break;
		
		case "Havana_Fort_yes_5":
			dialog.text = "Вот и замечательно. Через неделю жду вас у себя. А сейчас мне нужно заняться подготовкой сделки с заказчиком.";
			link.l1 = "Тогда не буду мешать. До встречи через неделю, " + npchar.name + ".";
			link.l1.go = "exit";
			pchar.questTemp.Slavetrader.Name = npchar.name;
			AddQuestRecord("Slavetrader", "32");
			SaveCurrentQuestDateParam("pchar.questTemp.Slavetrader_wait_6");
			SetFunctionTimerCondition("Slavetrader_UsurerEscape", 0, 0, 8, false);
			pchar.questTemp.Slavetrader = "wait_6";
			pchar.questTemp.Slavetrader.Cityname = npchar.city +"_town";
			LocatorReloadEnterDisable(npchar.city +"_town", "reload8_back", true);//чтобы не ходил неделю сюда вообще
		break;

		case "Usurer_Escape":
			dialog.text = "Что я здесь делаю? Хм... Это мой банк. Я буквально пару дней назад его приобрел. Вам, как первому клиенту, могу предложить очень выгодные условия кредитов...";
			link.l1 = "К черту кредиты! Где " + pchar.questTemp.Slavetrader.Name + "?";
			link.l1.go = "Usurer_Escape_1";
		break;

		case "Usurer_Escape_1":
			dialog.text = "Тише, тише, не кричите! Его уже давно здесь нет.";
			link.l1 = "Как нет?";
			link.l1.go = "Usurer_Escape_2";
		break;
		
		case "Usurer_Escape_2":
			dialog.text = "А вы не в курсе? Он исчез неделю назад. Потом обнаружилось, что он прихватил с собой денежки всех своих вкладчиков. Говорят, даже губернатор пострадал. Дом этот он бросил, а я выкупил его у города.";
			link.l1 = "Куда исчез? Как?";
			link.l1.go = "Usurer_Escape_3";
		break;
		
		case "Usurer_Escape_3":
			dialog.text = "Слышал, что он уплыл из нашей колонии... Вижу, вам он тоже должен... Много?";
			link.l1 = "Больше миллиона! Ну, я все равно эту крысу достану! Куда он отплыл, неизвестно? На каком корабле?";
			link.l1.go = "Usurer_Escape_4";
		break;
		
		case "Usurer_Escape_4":
			dialog.text = "Никто не знает. Ничего. Вообще. Он словно испарился. Был - и нет. В тот день из гавани вышел флейт, то ли 'Маврикий', то ли 'Мавродий' - наверно, на нем он и скрылся.";
			link.l1 = "Вот проклятье! Это же надо было - довериться такому мерзавцу! От него же за версту несло подлостью! А я, простофиля, поверил"+ GetSexPhrase("","а") +", что мы действительно партнеры! Но он еще здорово пожалеет... Ладно, " + npchar.name + ", прошу меня извинить за грубость... До свидания.";
			link.l1.go = "Usurer_Escape_5";
		break;
		
		case "Usurer_Escape_5":
			string sColony;
			sColony = npchar.city;
			SetNull2Deposit(sColony);
			dialog.text = "Да ничего, я все понимаю. Если вам понадобятся деньги, или наоборот, захотите открыть вклад - я всегда к вашим услугам.";
			link.l1 = "Спасибо. Но лучше я буду хранить деньги при себе. Всего доброго.";
			link.l1.go = "exit";
			AddQuestRecord("Slavetrader", "33");
			AddQuestUserData("Slavetrader", "sSex", GetSexPhrase("ел","ла"));
			CloseQuestHeader("Slavetrader");
			pchar.questTemp.Slavetrader = "wait1";
			LAi_LocationDisableOfficersGen(&Locations[FindLocation(pchar.location)], false); // разблокируем вход офицеров 2015
		break;
	//<--работорговец	

	//--> семейная реликвия
		case "Noblelombard":
			dialog.text = "Вот как? Значит, сам он уже не хочет со мной разговаривать... Хорошо, давайте обсудим это с вами. "+pchar.GenQuest.Noblelombard.Name+" должен мне "+FindRussianMoneyString(sti(pchar.GenQuest.Noblelombard.Summ))+": "+FindRussianMoneyString(sti(pchar.GenQuest.Noblelombard.Money))+" основного долга и "+FindRussianMoneyString(sti(pchar.GenQuest.Noblelombard.Percent))+" процентов за три месяца. И если я не увижу денег в ближайшие сутки - я продам его реликвию, как бы дорога она ему ни была. Бизнес есть бизнес.";
			if(sti(pchar.money) >= sti(pchar.GenQuest.Noblelombard.Summ))
			{
				link.l1 = "Прекрасно! В таком случае, я немедленно оплачиваю всю положенную сумму долга с процентами - "+FindRussianMoneyString(sti(pchar.GenQuest.Noblelombard.Summ))+". Свою реликвию мой доверитель заберет сам. Вот ваши деньги.";
				link.l1.go = "Noblelombard_1";
			}
			if(sti(pchar.money) >= sti(pchar.GenQuest.Noblelombard.Percent)*2)
			{
				link.l2 = "Деньги будут у моего доверителя через три месяца. Давайте заключим соглашение: я оплачиваю вам проценты за истекшие три месяца и авансом проценты еще за три месяца - всего "+FindRussianMoneyString(sti(pchar.GenQuest.Noblelombard.Percent)*2)+". А по истечении этого срока будет погашен основной долг.";
				link.l2.go = "Noblelombard_2";
			}
			if(sti(pchar.money) >= sti(pchar.GenQuest.Noblelombard.Percent))
			{
				link.l3 = "Деньги будут у моего доверителя через три месяца. Может, я погашу набежавшие проценты, а вы подождете до момента, когда мой доверитель будет располагать достаточной суммой?";
				link.l3.go = "Noblelombard_3";
			}
			link.l4 = "Ничего так себе стоимость этого раритета! Да, похоже, моему доверителю придется расстаться со своей реликвией. Всего доброго!";
			link.l4.go = "Noblelombard_4";
			npchar.quest.noblelombard = "true";
		break;
		
		case "Noblelombard_1":
			dialog.text = "Великолепно! Все повернулось как нельзя лучше - теперь и я получу свои деньги, и уважаемый "+pchar.GenQuest.Noblelombard.Name+" вернет назад свою реликвию.";
			link.l1 = "Рад, что мы без труда договорились с вами, "+npchar.name+"! Ну а теперь позвольте откланяться.";
			link.l1.go = "exit";
			pchar.GenQuest.Noblelombard.Regard = sti(pchar.GenQuest.Noblelombard.Summ)*2;
			AddMoneyToCharacter(pchar, -sti(pchar.GenQuest.Noblelombard.Summ));
			pchar.GenQuest.Noblelombard = "full";
			AddCharacterExpToSkill(pchar, "Leadership", 150);
		break;
		
		case "Noblelombard_2":
			if(sti(pchar.GenQuest.Noblelombard.Chance) < 7)
			{
				dialog.text = "Хм... Хорошо. Такой вариант меня вполне устраивает. Но если уважаемый "+pchar.GenQuest.Noblelombard.Name+" не найдет денег через три месяца - то более отсрочек я делать не буду ни на каких условиях. Так и передайте ему.";
				link.l1 = "Обязательно передам! Рад, что мы с вами договорились. Ну а теперь позвольте откланяться.";
				link.l1.go = "exit";
				pchar.GenQuest.Noblelombard.Regard = sti(pchar.GenQuest.Noblelombard.Percent)*4;
				AddMoneyToCharacter(pchar, -sti(pchar.GenQuest.Noblelombard.Percent)*2);
				pchar.GenQuest.Noblelombard = "maxpercent";
				AddCharacterExpToSkill(pchar, "Leadership", 50);
				AddCharacterExpToSkill(pchar, "Fortune", 70);
			}
			else
			{
				dialog.text = "Нет. Не пойдет. Мне нужна вся сумма, причем до заката солнца. Так и передайте вашему 'доверителю'. Больше мне добавить нечего.";
				link.l1 = "Хм. Жаль, конечно, что вы не хотите идти на компромисс. До свидания!";
				link.l1.go = "Noblelombard_4";
				AddCharacterExpToSkill(pchar, "Fortune", 30);
			}
		break;
		
		case "Noblelombard_3":
			if(sti(pchar.GenQuest.Noblelombard.Chance) < 3)
			{
				dialog.text = "Хм... Ладно. Пойду на такую уступку из уважения к вашему доверителю. Но если "+pchar.GenQuest.Noblelombard.Name+" не найдет денег через три месяца - то более отсрочек я делать не буду ни на каких условиях. Так и передайте ему.";
				link.l1 = "Обязательно передам! Рад, что мы с вами договорились. Ну а теперь позвольте откланяться.";
				link.l1.go = "exit";
				pchar.GenQuest.Noblelombard.Regard = sti(pchar.GenQuest.Noblelombard.Percent)*2;
				AddMoneyToCharacter(pchar, -sti(pchar.GenQuest.Noblelombard.Percent));
				pchar.GenQuest.Noblelombard = "minpercent";
				AddCharacterExpToSkill(pchar, "Leadership", 50);
				AddCharacterExpToSkill(pchar, "Fortune", 150);
			}
			else
			{
				dialog.text = "Нет. Не пойдет. Мне нужна вся сумма, причем до заката солнца. Так и передайте вашему 'доверителю'. Больше мне добавить нечего.";
				link.l1 = "Хм. Жаль, конечно, что вы не хотите идти на компромисс. До свидания!";
				link.l1.go = "Noblelombard_4";
				AddCharacterExpToSkill(pchar, "Fortune", 60);
			}
		break;
		
		case "Noblelombard_4":
			DialogExit();
			pchar.GenQuest.Noblelombard = "fail";
		break;
		
		case "Noblelombard_5":
			if(sti(pchar.GenQuest.Noblelombard.Chance) == 9)
			{
				dialog.text = "Да что вы такое говорите! Никакого депозита на ваше имя "+pchar.GenQuest.Noblelombard.Name+" не открывал. И его вообще уже нет в нашей колонии - отбыл в Европу. Честно вам скажу - более непорядочного человека я за всю свою жизнь не встречал. Он хотел меня надуть, но не тут-то было: у меня есть свои рычаги воздействия...";
				link.l1 = "Вот негодяй! А ведь обещал, дал слово чести...";
				link.l1.go = "Noblelombard_6";
			}
			else
			{	// Addon-2016 Jason уменьшаем раздачу дублонов
				dialog.text = "Да, все верно. На ваше имя "+pchar.GenQuest.Noblelombard.Name+" оставил депозит именно на эту сумму. Извольте получить...";
				link.l1 = "Отлично! До свидания, "+npchar.name+".";
				link.l1.go = "Noblelombard_9";
			}
		break;
		
		case "Noblelombard_6":
			dialog.text = "Для таких субъектов, как "+pchar.GenQuest.Noblelombard.Name+", понятие 'слово чести' ничего не значит, потому что чести у него нет, как и совести. Как я понимаю, он вас обманул?";
			link.l1 = "Выходит, что так. Ладно, "+npchar.name+", я тоже на Карибах не навечно, а Европа маленькая... Глядишь, еще и встретимся. До свидания!";
			link.l1.go = "Noblelombard_7";
		break;
		
		case "Noblelombard_7":
			DialogExit();
			AddQuestRecord("Noblelombard", "6");
			AddQuestUserData("Noblelombard", "sName", pchar.GenQuest.Noblelombard.Name);
			CloseQuestHeader("Noblelombard");
			DeleteAttribute(Pchar, "GenQuest.Noblelombard");
			DeleteAttribute(NPchar, "quest.noblelombard");
		break;
		
		case "Noblelombard_9":
			DialogExit();
			iTemp = sti(pchar.GenQuest.Noblelombard.Regard); // Addon-2016 Jason уменьшаем раздачу дублонов
			AddMoneyToCharacter(pchar, iTemp);
			AddQuestRecord("Noblelombard", "7");
			AddQuestUserData("Noblelombard", "sName", pchar.GenQuest.Noblelombard.Name);
			CloseQuestHeader("Noblelombard");
			DeleteAttribute(Pchar, "GenQuest.Noblelombard");
			DeleteAttribute(NPchar, "quest.noblelombard");
		break;
//<-- семейная реликвия

		// Бремя гасконца
		case "sharlie_credit":
			dialog.text = "Месье, я вас совершенно не знаю. Я выдаю кредиты только гражданам нашего города, или капитанам кораблей. Так что не обессудьте...";
			link.l1 = "Понятно. Очень жаль...";
			link.l1.go = "exit";
		break;
		// Бремя гасконца
		
		// Addon-2016 Jason, французские миниквесты (ФМК)
		// ФМК-Гваделупа
		case "FMQG_x":
			dialog.text = "Вы... Вы о чем это сейчас?";
			link.l1 = "Какой же ты все-таки гад! Слушай меня внимательно: не на дурака напал. Пинетт написал письмо в двух экземплярах. Один я отдал тебе, а второй лежит у моего доверенного лица. И если со мной что-нибудь случится - мой человек тут же отнесет его губернатору, Клоду Франсуа де Лиону...";
			link.l1.go = "FMQG_x1";
		break;
		
		case "FMQG_x1":
			dialog.text = "";
			link.l1 = "Так что тебе не убийц ко мне посылать надо, а ежедневно молиться в церкви за мое здоровье. Запомни: еще раз рыпнешься в мою сторону - тебе конец. А теперь выдыхай и считай свои дублоны дальше.";
			link.l1.go = "FMQG_x2";
		break;
		
		case "FMQG_x2":
			DialogExit();
			pchar.questTemp.FMQG = "end";
			FMQ_Count();
			AddQuestRecord("FMQ_Guadeloupe", "27");
			CloseQuestHeader("FMQ_Guadeloupe");
			ChangeCharacterComplexReputation(pchar, "nobility", -2);
			ChangeCharacterComplexReputation(pchar, "authority", 3);
			AddCharacterExpToSkill(pchar, "Sneak", 400);
			AddCharacterExpToSkill(pchar, "Sailing", 200);
			bQuestDisableMapEnter = false;//открыть карту
			DeleteAttribute(pchar, "GenQuest.MapClosedNoBattle");
		break;
	}	
}

int findCitizenMan(ref NPChar, bool bCity)
{
    ref ch;
	int n, nation;
    int storeArray[MAX_COLONIES];
    int howStore = 0;

	if (bCity && sti(Pchar.Ship.Type) == SHIP_NOTUSED)
	{
		ch = GetCharacter(NPC_GenerateCharacter("LoanFindingMan", "citiz_"+(rand(9)+11), "man", "man", 10, sti(npchar.nation), -1, false, "citizen"));
		ch.dialog.filename = "Common_citizen.c";
		ch.city = npchar.city;
		ch.RebirthPhantom = true; 
		LAi_NoRebirthDisable(ch);
		LAi_SetCitizenType(ch);
		LAi_group_MoveCharacter(ch, GetNationNameByType(sti(npchar.nation)) + "_citizens");
		PlaceCharacter(ch, "goto", npchar.city + "_town");
	}
	else
	{		
		for(n=0; n<MAX_COLONIES; n++)
		{			
			nation = GetNationRelation(sti(npchar.nation), sti(colonies[n].nation));	
			if (nation != RELATION_ENEMY && colonies[n].nation != "none")
			{           
				storeArray[howStore] = n;
				howStore++;
			}
		}
		if (howStore == 0) return -1; 
		nation = storeArray[cRand(howStore-1)];
		ch = GetCharacter(NPC_GenerateCharacter("LoanFindingMan", "citiz_"+(rand(9)+11), "man", "man", 10, sti(colonies[nation].nation), -1, false, "citizen"));
		ch.dialog.filename = "Common_citizen.c";
		ch.city = colonies[nation].id;
		ch.RebirthPhantom = true; 
		LAi_NoRebirthDisable(ch);
		LAi_SetCitizenType(ch);
		LAi_group_MoveCharacter(ch, GetNationNameByType(sti(colonies[nation].nation)) + "_citizens");
		PlaceCharacter(ch, "goto", colonies[nation].id + "_town");
	}
	return sti(ch.index);
}

int findChestMan(ref NPChar)
{
    ref ch;
	int n;
    int storeArray[TOTAL_CHARACTERS];
    int howStore = 0;
	string sTemp, sCity;

	for(n=2; n<MAX_CHARACTERS; n++)
	{
		makeref(ch,Characters[n]);
		sTemp = ch.id;
		if (CheckAttribute(ch, "City") && ch.id != "Jackman") sCity = ch.City;
		else continue;
		sTemp = strcut(sTemp, strlen(sCity)+1, strlen(sTemp)-1);
		// магазины
		if (sTemp == "trader")
		{
            if (NPChar.city == ch.city) continue;
            if (ch.location == "none") continue;
            storeArray[howStore] = n;
            howStore++;
		}
        // мэры
		if (sTemp == "Mayor")
		{
            if (NPChar.city == ch.city) continue;
            if (sti(ch.nation) == PIRATE) continue; // пираты не имеют реплик
            if (ch.location == "none") continue;
			if (ch.location != ch.Default) continue; //захвачанных мэров не надо
            storeArray[howStore] = n;
            howStore++;
		}
        // верфисты
		if (sTemp == "shipyarder")
		{
            if (NPChar.city == ch.city) continue;
            if (ch.location == "none") continue;
            storeArray[howStore] = n;
            howStore++;
		}
		// тавернщики
		if (sTemp == "tavernkeeper")
		{
            if (NPChar.city == ch.city) continue;
            if (ch.location == "none") continue;
            storeArray[howStore] = n;
            howStore++;
		}
	    // церковники
		if (sTemp == "Priest")
		{
            if (NPChar.city == ch.city) continue;
            if (ch.location == "none") continue;
            storeArray[howStore] = n;
            howStore++;
		}		
		// ростовщики
		if (sTemp == "usurer")
		{
            if (NPChar.city == ch.city) continue;
            if (ch.location == "none") continue;
            storeArray[howStore] = n;
            howStore++;
		}
		// начальники портов
		if (sTemp == "PortMan")
		{
            if (NPChar.city == ch.city) continue;
            if (ch.location == "none") continue;
            storeArray[howStore] = n;
            howStore++;
		}
    }
    if (howStore == 0)
    {
        return -1;
    }
    else
    {
        return storeArray[cRand(howStore-1)];
    }
}

// ugeen -> проверка, можем ли мы использовать дублоны в качестве вклада
bool CheckUseDublons(ref NPChar)
{
	int iTest 	= FindColony(NPChar.City); // город банка
	if(iTest == -1) return false;
	
	ref rColony = GetColonyByIndex(iTest);
	 	 
	bool bOk1 = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea); 
	bool bOk2 = (GetCharacterItem(pchar,"gold_dublon") > 10) || (CheckItemMyCabin("gold_dublon") > 10);
	
	if(sti(Pchar.Ship.Type) != SHIP_NOTUSED && bOk1 && bOk2) return true;

	return false;
}

void SlavetraderGalleonInWorld()
{
	//создаем галеон с рабами
	ref sld;
	string sName;
	sName = pchar.questTemp.Slavetrader.ShipName;
	sld = GetCharacter(NPC_GenerateCharacter("GaleonCap", "", "man", "man", 45, SPAIN, 20, true, "quest"));
	FantomMakeCoolSailor(sld, SHIP_LINESHIP, sName, CANNON_TYPE_CANNON_LBS36, 100, 100, 100);
	FantomMakeCoolFighter(sld, 45, 100, 100, "blade_21", "pistol5", "bullet", 100);
	sld.Ship.Mode = "war";	
	SetCaptanModelByEncType(sld, "war");
	DeleteAttribute(sld, "SinkTenPercent");
	DeleteAttribute(sld, "SaveItemsForDead");
	DeleteAttribute(sld, "DontClearDead");
	DeleteAttribute(sld, "AboardToFinalDeck");
	sld.AlwaysSandbankManeuver = true;
	sld.AnalizeShips = true;
	sld.DontRansackCaptain = true;
	sld.WatchFort = true;
	sld.AlwaysEnemy = true;
	SetCharacterPerk(sld, "StormProfessional");
	SetCharacterPerk(sld, "SwordplayProfessional");
	SetCharacterPerk(sld, "AdvancedDefense");
	SetCharacterPerk(sld, "CriticalHit");
	SetCharacterPerk(sld, "MusketsShoot");
	SetCharacterPerk(sld, "Sliding");
	SetCharacterPerk(sld, "Tireless");
	SetCharacterPerk(sld, "HardHitter");
	SetCharacterPerk(sld, "GunProfessional");
	SetCharacterGoods(sld, GOOD_SLAVES, 3000 + rand(200));//положить в трюм рабов
	sld.ship.Crew.Morale = 100;
	ChangeCrewExp(sld, "Sailors", 100);
	ChangeCrewExp(sld, "Cannoners", 100);
	ChangeCrewExp(sld, "Soldiers", 100);
	//в морскую группу кэпа
	string sGroup = "SlaveGalleon";
	Group_FindOrCreateGroup(sGroup);
	Group_SetTaskAttackInMap(sGroup, PLAYER_GROUP);
	Group_LockTask(sGroup);
	Group_AddCharacter(sGroup, sld.id);
	Group_SetGroupCommander(sGroup, sld.id);
	SetRandGeraldSail(sld, sti(sld.Nation));
	pchar.quest.SlaveHalleon_AfterBattle.win_condition.l1 = "Group_Death";
	pchar.quest.SlaveHalleon_AfterBattle.win_condition.l1.group = "SlaveGalleon";
	pchar.quest.SlaveHalleon_AfterBattle.function = "Slavetrader_SlaveHalleon_AfterBattle";
	sld.city = pchar.questTemp.Slavetrader.Island; //определим колонию, из бухты которой выйдет
	sld.cityShore = pchar.questTemp.Slavetrader.Island.Shore;
	sld.quest.targetCity = "Santiago"; //определим колонию, в бухту которой он придет
	sld.quest.targetShore = GetIslandRandomShoreId(GetArealByCityName(sld.quest.targetCity));
	//Log_TestInfo("Кэп галеона вышел из: " + sld.city + " и направился в: " + sld.quest.targetShore);
	//==> на карту
	sld.mapEnc.type = "trade";
	//выбор типа кораблика на карте
	sld.mapEnc.worldMapShip = "quest_ship";
	sld.mapEnc.Name = "Галеон '" + sName + " '";
	int daysQty = 20; //дней доехать даем с запасом
	Map_CreateTrader(sld.cityShore, sld.quest.targetShore, sld.id, daysQty);//вот он, сам запуск энкаунтера
}		