#include "DIALOGS\russian\Rumours\Common_rumours.c"  //homo 25/06/06
#include "interface\ship.c"
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
    // вызов диалога по городам -->
    NPChar.FileDialog2 = "DIALOGS\" + LanguageGetLanguage() + "\Tavern\" + NPChar.City + "_Tavern.c";
    if (LoadSegment(NPChar.FileDialog2))
	{
        ProcessCommonDialog(NPChar, Link, NextDiag);
		UnloadSegment(NPChar.FileDialog2);
	}
    // вызов диалога по городам <--
	ProcessCommonDialogRumors(NPChar, Link, NextDiag);//homo 25/06/06
	
	int iTest, iTemp;
	string sTemp;
	string NPCCity = NPChar.City;
    iTest = FindColony(NPChar.City); // город 
    ref rColony;
	if (iTest != -1)
	{
		rColony = GetColonyByIndex(iTest);
	}
	bool ok;

	if(!CheckAttribute(pchar, "questTemp.TavernVisit."+(NPCCity) )) 
	{
		pchar.questTemp.TavernVisit.(NPCCity) = true;
		pchar.questTemp.TavernVisit.counter = sti(pchar.questTemp.TavernVisit.counter) + 1;
	}	
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			NextDiag.TempNode = "First time";
			if (LAi_grp_playeralarm > 0)
			{
       			dialog.text = NPCharRepPhrase(pchar,
					LinkRandPhrase("В городе поднята тревога, тебя всюду ищут! На твоем месте я бы не стал здесь задерживаться.", "Вся городская стража рыщет по городу в поисках тебя. Я не идиот и разговаривать с тобой не буду!", "Беги, "+ GetSexPhrase("приятель","подруга") +", пока солдаты не сделали из тебя решето..."),
					LinkRandPhrase("Что тебе нужно, "+ GetSexPhrase("негодяй","мерзавка") +"?! Городская стража уже взяла твой след, далеко тебе не уйти"+ GetSexPhrase(", грязный пират!","") +"", "Грязн"+ GetSexPhrase("ый","ая") +" убийца, вон из моего дома! Стража!!", "Я не боюсь тебя, мерзав"+ GetSexPhrase("ец","ка") +"! Скоро тебя повесят в нашем форте, далеко тебе не уйти..."));
				link.l1 = NPCharRepPhrase(pchar,
					RandPhraseSimple("Хех, тревога для меня не проблема...", "Им меня ни за что не поймать."),
					RandPhraseSimple("Заткни свою пасть, " + GetWorkTypeOfMan(npchar, "") + ", а не то вырву твой поганый язык!", "Хех, " + GetWorkTypeOfMan(npchar, "") + ", а все туда же - пиратов ловить! Вот что я тебе скажу, приятель: сиди тихо и будешь жить..."));
				link.l1.go = "exit";
				break;
			}
			if (sti(pchar.GenQuest.Piratekill) > 20 && sti(npchar.nation) == PIRATE)
			{
				dialog.text = RandPhraseSimple("А, это ты, мерзавец! Думаешь, тебе здесь рому нальют? Как бы не так! Ребята! К оружию! Режь психа!", "Выпить захотел, скотина? Ан нет! Сейчас тебе покажут, где раки зимуют! Ребята, здесь больной псих с оружием! Тревога!");
				link.l1 = RandPhraseSimple("А? Что?", "Э, ты чего это?!");
				link.l1.go = "fight";
				bDisableFastReload = true;//закрыть переход
				pchar.quest.pirate_in_town.win_condition.l1 = "ExitFromLocation";
				pchar.quest.pirate_in_town.win_condition.l1.location = pchar.location;
				pchar.quest.pirate_in_town.function = "TownPirate_battle";
				break;
			}
			//Jason, Бремя гасконца
			if (CheckAttribute(pchar, "questTemp.Sharlie") && pchar.questTemp.Sharlie == "crew" && npchar.city == "FortFrance")
			{
				dialog.text = "Вы что-то хотели, месье?";
				Link.l1 = "Послушай, я бы хотел нанять команду на свой корабль. Не поможешь в этом вопросе?";
				Link.l1.go = "Sharlie_crew";
				break;
			}
			
			if (CheckAttribute(pchar, "questTemp.Sharlie") && pchar.questTemp.Sharlie == "skiper" && npchar.city == "FortFrance")
			{
				dialog.text = "Что на этот раз, месье?";
				Link.l1 = ""+npchar.name+", я понимаю, что утомил тебя своими расспросами, но все же подскажи еще раз. Мне нужен штурман. Где я смогу его найти?";
				Link.l1.go = "Sharlie_skiper";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.Sharlie.Lock"))
			{
    			dialog.text = "Что вам угодно, месье?";
				Link.l1 = "Я надеюсь, ты сможешь ответить на пару вопросов.";
				Link.l1.go = "quests";
				link.l2 = "Я хотел бы снять комнату.";
                link.l2.go = "room";
				break;
			}			
			//Бремя гасконца
			// Addon 2016-1 Jason пиратская линейка
			if (CheckAttribute(pchar, "questTemp.Mtraxx.Retribution") && pchar.questTemp.Mtraxx.Retribution == "tavern" && npchar.city == "Tortuga")
			{
				dialog.text = "Рад видеть дорогого гостя! Что желаете? Ром, бренди, шотландский виски?";
				Link.l1 = "Бутылку отличного французского вина и ключ от комнаты.";
				Link.l1.go = "mtraxx_tortuga";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.Mtraxx.Retribution") && pchar.questTemp.Mtraxx.Retribution == "room" && npchar.city == "Tortuga")
			{
				dialog.text = "Вы уже все оплатили, месье, поднимайтесь в вашу комнату.";
				Link.l1 = "...";
				Link.l1.go = "exit";
				break;
			}

			if(NPChar.quest.meeting == "0")
			{
				dialog.Text = GetNatPhrase(npchar, LinkRandPhrase("С прибытием в таверну '" + XI_ConvertString(NPChar.City + "TavernName") + "', сэр. Я рад видеть вас.","К вашим услугам, сэр! В таверне '" + XI_ConvertString(NPChar.City + "TavernName") + "' рады новым гостям.","Вижу, вы впервые у меня, сэр? Не стесняйтесь, в таверне '" + XI_ConvertString(NPChar.City + "TavernName") + "' вы всегда почувствуете себя, как дома!"), LinkRandPhrase("Прошу вас, месье капитан. Вы впервые посетили таверну '" + XI_ConvertString(NPChar.City + "TavernName") + "'?","Не встречал вас раньше, месье. Будем знакомы: я "+GetFullName(npchar)+", хозяин таверны '" + XI_ConvertString(NPChar.City + "TavernName") + "'.","Я рад новому гостю, месье капитан! В таверне '" + XI_ConvertString(NPChar.City + "TavernName") + "' первое угощение всегда за мой счет! Я - хозяин этого заведения, "+GetFullName(npchar)+", будем знакомы."), LinkRandPhrase("Сеньор капитан! Добро пожаловать в таверну '" + XI_ConvertString(NPChar.City + "TavernName") + "'!","О, какой блестящий идальго посетил сегодня таверну '" + XI_ConvertString(NPChar.City + "TavernName") + "'! Вы впервые у нас, сеньор?","Здравствуйте, кабальеро! Я "+GetFullName(npchar)+", хозяин таверны '" + XI_ConvertString(NPChar.City + "TavernName") + "', рад приветствовать вас у себя!"),LinkRandPhrase("Здравствуйте, минхер капитан. Я хозяин таверны '" + XI_ConvertString(NPChar.City + "TavernName") + "'. Впервые у нас?","Добрый день, минхер. Добро пожаловать в таверну '" + XI_ConvertString(NPChar.City + "TavernName") + "'.","Очень приятно, минхер капитан! Таверна '" + XI_ConvertString(NPChar.City + "TavernName") + "' приветствует вас! Рому, вина, эля?"));
				Link.l1 = LinkRandPhrase("А у вас тут уютно... Позвольте представиться - "+GetFullName(pchar)+", рад знакомству.",""+GetFullName(pchar)+", рад знакомству. Что вы мне предложите?","Мое имя "+GetFullName(pchar)+" и я здесь совсем недавно. Чем угостите гостя?");
				Link.l1.go = "meeting";
/*				
				if(!CheckAttribute(pchar, "questTemp.TavernVisit."+(NPCCity) )) 
				{
					pchar.questTemp.TavernVisit.(NPCCity) = true;
					pchar.questTemp.TavernVisit.counter = sti(pchar.questTemp.TavernVisit.counter) + 1;
				}	
*/				
				NPChar.quest.meeting = "1";
			}
			else
			{
				// Квестовый генератор священника. Квест №1. Warship -->
				if(CheckAttribute(PChar, "GenQuest.ChurchQuest_1.NeedToDialogWithBarmen") && PChar.location == PChar.GenQuest.ChurchQuest_1.CurPortManColony + "_tavern")
		        {
		            if(CheckAttribute(PChar, "GenQuest.ChurchQuest_1.NoMoneyToBarmen"))
		            {
		            	iTemp = sti(PChar.GenQuest.ChurchQuest_1.MoneyToBarmen);
		            	dialog.Text = "Ну что кэп, вы принесли мне " + FindRussianMoneyString(iTemp) + ".";
		            	if(sti(PChar.Money) >= iTemp)
		            	{
							link.l1 = "Да, принес"+ GetSexPhrase("","ла") +". Вот они...";
							link.l1.go = "Tavern_ChurchGenQuest1_Node_4_1";
						}
						else
						{
							link.l1 = "Нет, еще не принес"+ GetSexPhrase("","ла") +"...";
							link.l1.go = "exit";
						}
		            }
		            else
		            {
		            	dialog.Text = "Чего изволите, милостив"+ GetSexPhrase("ый господин","ая госпожа") +"?";
						link.l1 = "Бутылку рома моему приятелю, вон за тем столиком.";
						link.l1.go = "Tavern_ChurchGenQuest1_Node_1";
					}
					break;
				}
				// <-- Квестовый генератор священника. Квест №1.
				dialog.Text = pcharrepphrase(LinkRandPhrase(LinkRandPhrase("Какие гости! Эй, там, ну-ка, очистите место бравому капитану! Да пошевеливайтесь, пока он сам вас не поторопил, ха-ха!","О! Сам "+GetFullName(pchar)+"! Дебош мы не заказывали, но вы проходите, проходите...","А-а, "+GetAddress_Form(NPChar)+", вижу, вы не в духе? Позвольте угостить вас? Поверьте, лучшее вино наливаю..."),LinkRandPhrase("Сам капитан "+GetFullName(pchar)+"! Эй-эй, там! Куда побежали, голодранцы?! Простите, кэп, видимо, они вспомнили о каких-то делах...","О, "+GetAddress_Form(NPChar)+" "+GetFullName(pchar)+"! Похоже, сегодня мы тут не заскучаем...","Добрый день, "+GetFullName(pchar)+", я рад вам... Только, прошу, сегодня без скандалов, пожалуйста."),LinkRandPhrase("Здравствуйте, капитан. Располагайтесь, но помните – в моем заведении даже сам капитан Шарп всегда соблюдал приличия.","О-хо-хо! Кого я вижу? Это же сам "+GetFullName(pchar)+"! А мы тут без вас совсем заскучали...","Ха-ха, да это же сам "+GetFullName(pchar)+"! Надеюсь, вы больше не будете пугать моих завсегдатаев рассказами о своих похождениях?")),LinkRandPhrase(LinkRandPhrase(""+GetFullName(pchar)+"! Старый моряк всегда рад видеть вас в своем заведении!","Прошу вас, капитан, прошу! Я рад приветствовать своего лучшего гостя. Что вам налить?","Рад снова видеть вас, "+GetFullName(pchar)+"! Где изволите присесть – в зале? Или налить вам кружку прямо у стойки?"),LinkRandPhrase("Добрый день, капитан. Позвольте предложить вам первоклассный глинтвейн!","Здравствуйте, капитан "+GetFullName(pchar)+"! Я рад, что вы снова заглянули ко мне. Чем вас угостить?","Очень рад вам, "+GetAddress_Form(NPChar)+" "+GetFullName(pchar)+"! Вижу, вам приглянулось мое заведение? Я очень стараюсь, чтобы вам угодить."),LinkRandPhrase("Господин капитан! Добро пожаловать! Я тут раздобыл великолепное анжуйское – впору самому королю – и сберег его для вас!",""+GetFullName(pchar)+"! Как я рад вашему визиту! Разогнать этих голодранцев, капитан, или вы позволите им остаться? Поверьте, я готов хоть всю таверну очистить для своего лучшего гостя!","У нас снова в гостях капитан "+GetFullName(pchar)+"! Эй, вертихвостки, немедленно лучшую скатерть на стол господина капитана!")));
				Link.l1 = pcharrepphrase(RandPhraseSimple(RandPhraseSimple("Вижу, меня тут не забывают... Ты наливай пока, дружок, а я тут осмотрюсь...","Спокойно, приятель, я сегодня на редкость благодушен. Плесни-ка мне для начала рому..."),RandPhraseSimple("Та-ак... Это что же, мне тут не рады?! Надеюсь, я ослышался?","Ну, дружок, надеюсь, твое вино лучше твоих приветствий? А то я ведь могу и рассердиться...")),RandPhraseSimple(RandPhraseSimple("Всегда рад тебя посетить, дружище. Что там есть – согреть замерзшего на ветру морского волка?","Ха, дружище, твое заведение все краше день ото дня! Всегда приятно к тебе зайти..."),RandPhraseSimple("Не забываешь морского странника? Ну что же, я польщен, приятель.","Как приятно увидеть старого знакомого... Ром-то еще не весь выпили?")));
				Link.l1.go = "step_node";
			}
			break;
				
			case "step_node":
				dialog.Text = LinkRandPhrase("Внимательно слушаю вас, капитан.","Таверна '" + XI_ConvertString(NPChar.City + "TavernName") + "' к вашим услугам, капитан!","Слушаю, кэп! Каков будет сегодня ваш заказ?");
				Link.l1 = "Есть на острове парни, готовые уйти в плавание?";
				Link.l1.go = "crew hire";
				Link.l2 = "Я надеюсь, ты сможешь ответить на пару вопросов.";
				Link.l2.go = "int_quests";
				if (CheckAttribute(pchar, "GenQuest.LoanChest.TakeChest") && sti(pchar.GenQuest.LoanChest.TargetIdx) == sti(NPChar.index))
				{
					link.l21 = "Слушай, нам нужно поговорить о финансовых делах.";
					link.l21.go = "LoanForAll";//(перессылка в кредитный генератор)
				}
				
				// Квестовый генератор священника. Квест №2. Warship -->
				if(CheckAttribute(PChar, "GenQuest.ChurchQuest_2.AskBarmen") && PChar.location == PChar.GenQuest.ChurchQuest_2.QuestTown + "_tavern")
		            	{
					link.l10 = LinkRandPhrase("Ты что-нибудь можешь сказать об недавнем ограблении церкви?", "Что ты знаешь об недавнем ограблении местной церкви?", "Ты что-нибудь слышал об недавнем ограблении местной церкви?");
					link.l10.go = "Tavern_GenQuest_Church_2_1";
				}
				// <-- Квестовый генератор священника. Квест №2.
				
				//Jason --> генератор Неудачливый вор
				if (CheckAttribute(pchar, "GenQuest.Device.Shipyarder") && NPChar.location == pchar.GenQuest.Device.Shipyarder.City + "_tavern" && pchar.GenQuest.Device.Shipyarder == "begin" && !CheckAttribute(npchar, "quest.Device"))
				{
					link.l16 = "Послушайте, говорят, ты все про все знаешь в этой колонии. Я хочу купить "+pchar.GenQuest.Device.Shipyarder.Type+", и мне сказали, что у вас в городе она продавалась. Ну, кто-то продавал на улицах. Ничего об этом сказать не можешь?";
					link.l16.go = "Device_Tavern";
				}
				// <-- генератор Неудачливый вор
			
				//Jason --> генератор Место под солнцем
				if (CheckAttribute(pchar, "GenQuest.Sunplace.Trader") && pchar.GenQuest.Sunplace.Trader == "continue" && NPChar.location == pchar.GenQuest.Sunplace.Trader.CityT + "_tavern")
				{
					link.l17 = "Скажи, у вас в городе проживает барышник по имени "+pchar.GenQuest.Sunplace.Trader.Enemyname+". Где мне его найти?";
					link.l17.go = "Sunplace_Tavern";
				}
				// <-- генератор Место под солнцем
			
				// --> Голландский гамбит
				if (CheckAttribute(pchar, "questTemp.HWIC.Holl") && pchar.questTemp.HWIC.Holl == "JacobOnMain" && NPChar.location == pchar.questTemp.HWIC.Holl.JacobCity + "_tavern")
				{
					link.l18 = "Приветствую, " + npchar.name + ". Мне нужно найти Якоба ван Берга, где он? Что-то я его у тебя в зале не вижу...";
					link.l18.go = "HWICHollJacob_Tavern";
				}
				if (CheckAttribute(pchar, "questTemp.HWIC.Self") && pchar.questTemp.HWIC.Self == "start" && NPChar.nation == SPAIN && !CheckAttribute(npchar, "quest.HWICTalked"))
				{
					link.l18 = "Приветствую, " + npchar.name + ". Я ищу одного кабальеро, Фернандо Родригес его зовут. Он у вас в городе не появлялся?";
					link.l18.go = "HWICSelfFernando_Tavern";
				}
				// <-- Голландский гамбит
			
				//Jason --> гонки на гидропланах
				if (CheckAttribute(pchar, "GenQuest.Racing.Go.Advantage") && NPChar.location == pchar.GenQuest.Racing.Go.StartCity + "_tavern")
				{
					link.l19 = "Я пришел за своим выигрышем, который хранится у тебя, " + npchar.name + ".";
					link.l19.go = "Race_Advantage";
				}
				// <-- гонки на гидропланах
			
				//Jason --> захват пассажиров
				if (CheckAttribute(pchar, "GenQuest.Marginpassenger") && pchar.GenQuest.Marginpassenger == "take" && NPChar.location == pchar.GenQuest.Marginpassenger.Targetcity+"_tavern")
				{
					link.l20 = "Я бы хотел спросить, где я могу найти человека по имени "+pchar.GenQuest.Marginpassenger.q2Name+"? Он у вас в городе проживает.";
					link.l20.go = "Marginpassenger";
				}
				// <-- захват пассажиров
			
				link.l3 = pcharrepphrase("Есть ли в твоем клоповнике свободная конура?", "Нет ли у тебя свободной комнаты, я хотел"+ GetSexPhrase("","а") +" бы остановиться здесь на некоторое время.");
				link.l3.go = "room";
				Link.l4 = "Увы, я уже ухожу, " + NPChar.name + ". До встречи.";
				Link.l4.go = "exit";
		break;
		
		case "Meeting":
			// Квестовый генератор священника. Квест №1. Warship -->
			if(CheckAttribute(PChar, "GenQuest.ChurchQuest_1.NeedToDialogWithBarmen") && PChar.location == PChar.GenQuest.ChurchQuest_1.CurPortManColony + "_tavern")
	        {
	            dialog.Text = "Чего изволите, милостив"+ GetSexPhrase("ый господин","ая госпожа") +"?";
				link.l1 = "Бутылку рома моему приятелю вон за тем столиком.";
				link.l1.go = "Tavern_ChurchGenQuest1_Node_1";
				break;
			}
			// <-- Квестовый генератор священника. Квест №1.
			dialog.Text = LinkRandPhrase("Внимательно слушаю вас, капитан.","Что вам предложить, капитан?","Слушаю, кэп! Каков будет ваш заказ?");
			Link.l1 = "Мне нужна команда, " + NPChar.name + ".";
			Link.l1.go = "crew hire";
			Link.l2 = NPChar.name + ", давай поговорим...";
			Link.l2.go = "int_quests";
			if (CheckAttribute(pchar, "GenQuest.LoanChest.TakeChest") && sti(pchar.GenQuest.LoanChest.TargetIdx) == sti(NPChar.index))
			{
				link.l21 = "Слушай, нам нужно поговорить о финансовых делах.";
				link.l21.go = "LoanForAll";//(перессылка в кредитный генератор)
			}
			// Квестовый генератор священника. Квест №2. Warship -->
			if(CheckAttribute(PChar, "GenQuest.ChurchQuest_2.AskBarmen") && PChar.location == PChar.GenQuest.ChurchQuest_2.QuestTown + "_tavern")
	        {
				link.l10 = LinkRandPhrase("Ты что-нибудь можешь сказать об недавнем ограблении церкви?", "Что ты знаешь об недавнем ограблении местной церкви?", "Ты что-нибудь слышал об недавнем ограблении местной церкви?");
				link.l10.go = "Tavern_GenQuest_Church_2_1";
			}
			// <-- Квестовый генератор священника. Квест №2.
			
			//Jason --> генератор Неудачливый вор
			if (CheckAttribute(pchar, "GenQuest.Device.Shipyarder") && NPChar.location == pchar.GenQuest.Device.Shipyarder.City + "_tavern" && pchar.GenQuest.Device.Shipyarder == "begin" && !CheckAttribute(npchar, "quest.Device"))
			{
   				link.l16 = "Послушайте, говорят, ты все про все знаешь в этой колонии. Я хочу купить "+pchar.GenQuest.Device.Shipyarder.Type+", и мне сказали, что у вас в городе она продавалась. Ну, кто-то продавал на улицах. Ничего об этом сказать не можешь?";
				link.l16.go = "Device_Tavern";
			}
			// <-- генератор Неудачливый вор
			
			//Jason --> генератор Место под солнцем
			if (CheckAttribute(pchar, "GenQuest.Sunplace.Trader") && pchar.GenQuest.Sunplace.Trader == "continue" && NPChar.location == pchar.GenQuest.Sunplace.Trader.CityT + "_tavern")
			{
   				link.l17 = "Скажи, у вас в городе проживает барышник по имени "+pchar.GenQuest.Sunplace.Trader.Enemyname+". Где мне его найти?";
				link.l17.go = "Sunplace_Tavern";
			}
			// <-- генератор Место под солнцем
			
			//--> Голландский гамбит
			if (CheckAttribute(pchar, "questTemp.HWIC.Holl") && pchar.questTemp.HWIC.Holl == "JacobOnMain" && NPChar.location == pchar.questTemp.HWIC.Holl.JacobCity + "_tavern")
				{
					link.l18 = "Приветствую, " + npchar.name + ". Мне нужно найти Якоба ван Берга, где он? Что-то я его у тебя в зале не вижу...";
					link.l18.go = "HWICHollJacob_Tavern";
				}
				if (CheckAttribute(pchar, "questTemp.HWIC.Self") && pchar.questTemp.HWIC.Self == "start" && NPChar.nation == SPAIN && !CheckAttribute(npchar, "quest.HWICTalked"))
				{
					link.l18 = "Приветствую, " + npchar.name + ". Я ищу одного кабальеро, Фернандо Родригес его зовут. Он у вас в городе не появлялся?";
					link.l18.go = "HWICSelfFernando_Tavern";
				}
				//<-- Голландский гамбит
				
				//Jason --> гонки на гидропланах
				if (CheckAttribute(pchar, "GenQuest.Racing.Go.Advantage") && NPChar.location == pchar.GenQuest.Racing.Go.StartCity + "_tavern")
				{
					link.l19 = "Я пришел за своим выигрышем, который хранится у тебя, " + npchar.name + ".";
					link.l19.go = "Race_Advantage";
				}
				// <-- гонки на гидропланах
				//Jason --> захват пассажиров
				if (CheckAttribute(pchar, "GenQuest.Marginpassenger") && pchar.GenQuest.Marginpassenger == "take" && NPChar.location == pchar.GenQuest.Marginpassenger.Targetcity+"_tavern")
				{
					link.l20 = "Я бы хотел спросить, где я могу найти человека по имени "+pchar.GenQuest.Marginpassenger.q2Name+"? Он у вас в городе проживает.";
					link.l20.go = "Marginpassenger";
				}
				// <-- захват пассажиров
				
			link.l3 = pcharrepphrase("Есть ли в твоем клоповнике свободная конура?", "Нет ли у тебя свободной комнаты, я хотел"+ GetSexPhrase("","а") +" бы остановиться здесь на некоторое время.");
			link.l3.go = "room";
			Link.l4 = "Пожалуй, загляну к тебе попозже.";
			Link.l4.go = "exit";
		break;
		
		case "crew hire":
			ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
			ok = sti(Pchar.Ship.Type) != SHIP_NOTUSED && ok;
			
			if (!ok)
			{
				Dialog.text = "А на что тебе матросы? Что-то не вижу твоего корабля в порту.";
				link.l1 = RandPhraseSimple("Точно... я его пришвартовал"+ GetSexPhrase("","а") +" не в том месте.", "Забыл"+ GetSexPhrase("","а") +" войти в порт...");
				link.l1.go = "exit";
				break;
			}
			
            if (makeint(environment.time) > 22.0 || makeint(environment.time) < 7.0)
			{
				Dialog.text = "Обычно у меня в таверне полно людей, желающих стать матросами, но сейчас слишком поздно, и они начнут появляться только утром. Может быть, вы хотите снять комнату, и подождать их?";
				link.l1 = "Хорошо. У тебя есть свободные комнаты?";
				link.l1.go = "room";
				link.l2 = "Меня не интересует комната на данный момент. До встречи.";
				link.l2.go = "exit";
			}
			else
			{
                if (GetNationRelation2MainCharacter(sti(NPChar.nation)) == RELATION_ENEMY && sti(NPChar.nation) != PIRATE)
                {
                    Dialog.text = "А ты думаешь, к тебе кто-то пойдет, когда ты с нами во вражде? Скажи спасибо, что стражу не зову.";
					link.l1 = "Спасибо.";
					link.l1.go = "exit";
                }
                else
                {
					if (CheckAttribute(NPChar, "CrewHired.PGGId") && GetNpcQuestPastDayParam(NPChar, "CrewHired") < 3 && GetCrewQuantity(rColony) == 0)
					{
						Dialog.text = "Извините, но сейчас нет никого. Все ушли с отважным кэпом " + GetFullName(CharacterFromID(NPChar.CrewHired.PGGId)) + ".";
						link.l1 = "Эх, жаль!";
						link.l1.go = "exit_crew";
					}
					else
					{						
						if(bPartitionSet)
						{		
							if(GetPartitionAmount("CrewPayment") > 0)
							{
								if(IsEquipCharacterByArtefact(pchar, "totem_07"))
								{
									DeleteAttribute(NPChar, "CrewHired"); //на всяк случай.
									NextDiag.CurrentNode =  NextDiag.TempNode;
									DialogExit();
									LaunchHireCrew();							
								}
								else
								{
									dialog.text = "Капитан, поговаривают, что вы скуповаты. У меня нет желающих пойти в вашу команду.";
									link.l1 = "Понятно...";
									link.l1.go = "exit";
								}
							}
							else
							{
								DeleteAttribute(NPChar, "CrewHired"); //на всяк случай.
								NextDiag.CurrentNode =  NextDiag.TempNode;
								DialogExit();
								LaunchHireCrew();	
							}
						}	
						else
						{
							DeleteAttribute(NPChar, "CrewHired"); //на всяк случай.
							NextDiag.CurrentNode =  NextDiag.TempNode;
							DialogExit();
							LaunchHireCrew();							
						}						
					}
				}
			}
		break;
		
		case "exit_crew" :
			DeleteAttribute(NPChar, "CrewHired"); //на всяк случай.
			NextDiag.CurrentNode =  NextDiag.TempNode;
			DialogExit();
			LaunchHireCrew();
		break;
	////////////////////////////////////////////////////////=============================================///////////////////////////////////////////////////////	
        case "int_quests":
			dialog.text = "Я весь внимание.";
			//link.l1 = "Я ищу работу. Не поможешь мне?";
			//link.l1.go = "work";
			//homo 15/06/06 слухи
			link.l2 = LinkRandPhrase("Расскажи мне последние новости?","Что новенького в этих краях?",
                                    "Как течет жизнь на суше?");
			link.l2.go = "rumours_tavern";
			//homo
			link.l3 = "Я по другому делу.";
			link.l3.go = "quests";
			if(CheckAttribute(pchar,"GenQuest.EncGirl"))
			{
				if(pchar.GenQuest.EncGirl == "EncGirlFack_fighted")
				{
					link.l5 = "Не знаешь, где мне найти " + pchar.GenQuest.EncGirl.name +"?";
					link.l5.go = "EncGirl_1";
				}	
				if(pchar.GenQuest.EncGirl == "toParents" || pchar.GenQuest.EncGirl == "FindLover")
				{
					link.l6 = "Не подскажешь, где мне искать " + pchar.GenQuest.EncGirl.sLoverId + "?";
					link.l6.go = "EncGirl_3";
				}
				if(pchar.GenQuest.EncGirl == "toLoverFather" && pchar.GenQuest.EncGirl.LoverFather == "tavern_keeper" && pchar.GenQuest.EncGirl.LoverCity == npchar.city)
				{
					link.l7 = "Здравствуйте, я приш"+ GetSexPhrase("ел","ла") +" по приглашению вашего сына."; 
					link.l7.go = "EncGirl_4";
					pchar.quest.EncGirl_GetLoverFather.over = "yes";
				}
			}
			if(CheckAttribute(pchar,"GenQuest.CaptainComission") && NPChar.city == pchar.GenQuest.CaptainComission.City && CheckAttribute(pchar,"GenQuest.CaptainComission.Speak_Tavern"))
			{
				if(pchar.GenQuest.CaptainComission.variant == "A0")
				{												
					if(pchar.GenQuest.CaptainComission.Speak_Tavern == true)
					{
						link.l9 = "Ну что, не заходил " + pchar.GenQuest.CaptainComission.Name + "?";
						link.l9.go = "CaptainComission_3";
					}
					else
					{
						link.l9 = "Не подскажешь, где может быть " + pchar.GenQuest.CaptainComission.Name + "?";
						link.l9.go = "CaptainComission_1";
					}
				}	

				if(pchar.GenQuest.CaptainComission.variant == "A2" && pchar.GenQuest.CaptainComission == "Begin_1")
				{ // лесник окончание  - патрулного люггера,барка и т.д..........
					link.l9 = "Скажи-ка, любезный, где может быть капитан патрульного " + GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name") + "Gen")) + ", " + pchar.GenQuest.CaptainComission.Name + "?";
					link.l9.go = "CaptainComission_Tavern7";					
				}				
				if(pchar.GenQuest.CaptainComission.variant == "A3" && pchar.GenQuest.CaptainComission == "Begin_1")
				{
					if(pchar.GenQuest.CaptainComission.Speak_Tavern == true)
					{
						link.l9 = "Ну что, не заходил " + GetName( NAMETYPE_ORIG, pchar.GenQuest.CaptainComission.CanoneerName, NAME_NOM) + "?";
						link.l9.go = "CaptainComission_3";
					}
					else
					{		// лесник - изменеие предложения из за имени . 		
						link.l9 = "Скажи-ка, любезный, тебе известен капитан патрульного " + GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name") + "Gen")) + ", " + pchar.GenQuest.CaptainComission.Name + "?";
						link.l9.go = "CaptainComission_Tavern1";
						if(!CheckAttribute(pchar,"GenQuest.CaptainComission.GetRumour"))
						{
							pchar.GenQuest.CaptainComission.GetRumour = true;
							SaveCurrentQuestDateParam("GenQuest.CaptainComission.GetRumour");
						}	
					}	
				}					
			}
			if(CheckAttribute(pchar,"GenQuest.Hold_GenQuest") && NPChar.city == pchar.GenQuest.Hold_GenQuest.City && pchar.GenQuest.Hold_GenQuest.Speak_Tavern == false )
			{
				link.l10 = "Не подскажете, где мне найти господина по имени " + pchar.GenQuest.Hold_GenQuest.Name + "?";
				link.l10.go = "hold_genquest1";
			}
			if (CheckCharacterItem(pchar, "CaptainBook") && CheckAttribute(pchar, "questTemp.different.GiveShipLetters") && !CheckAttribute(pchar, "questTemp.different.GiveShipLetters.speakTavern") && (pchar.questTemp.different.GiveShipLetters.city == npchar.city))
			{
				link.l11 = "Я совершенно случайно неподалеку наш"+ GetSexPhrase("ел","ла") +" судовые документы....";
				link.l11.go = "ShipLetters_4";			
			}

			// Jason --> квест губера на поиск дезертира
			if(CheckAttribute(pchar, "GenQuest.FindFugitive") && pchar.GenQuest.FindFugitive != "Late" && sti(NPChar.nation) == PIRATE)
			{
				link.l12 = "Послушай, я ищу своего старого друга, "+pchar.GenQuest.FindFugitive.Name+" его зовут. Один шкипер сказал мне, что он собирался направиться именно в ваше поселение. Не слыхал ничего об этом человеке?";
				link.l12.go = "FindFugitiveTav";
			}
			//<-- поиск дезертира

			link.l15 = "Спасибо, ничего. До свидания.";
			link.l15.go = "exit";
		break;
		
		case "hold_genquest1":
			switch(sti(pchar.GenQuest.Hold_GenQuest.TavernVariant))
			{
				case 0:
					dialog.text = LinkRandPhrase("Как вы говорите? " + pchar.GenQuest.Hold_GenQuest.Name + "? Хм, никогда не слыхал о таком.",
						"Вы точно знаете, что он именно из нашего поселения? Просто не слыхивал о таком ни разу.",
						"В нашем поселении такого отродясь не было. Сколько здесь живу - не слышал.");
					link.l1 = "А вы уверены?";
					link.l1.go = "hold_genquest2";					
				break;
				
				case 1: 
					switch (drand(3))
					{
						case 0:
							pchar.GenQuest.Hold_GenQuest.foundStr = "в церковь";						
							pchar.GenQuest.Hold_GenQuest.found = "church";
						break;
						case 1:
							if (npchar.city != "Panama")
							{
							pchar.GenQuest.Hold_GenQuest.foundStr = "на верфь";						
							pchar.GenQuest.Hold_GenQuest.found = "shipyard";
							}
							else
							{
								pchar.GenQuest.Hold_GenQuest.foundStr = "в церковь";						
								pchar.GenQuest.Hold_GenQuest.found = "church";
							}
						break;
						case 2:
							pchar.GenQuest.Hold_GenQuest.foundStr = "к ростовщику";												
							pchar.GenQuest.Hold_GenQuest.found = "bank";
						break;
						case 3:
							pchar.GenQuest.Hold_GenQuest.foundStr = "в магазин";						
							pchar.GenQuest.Hold_GenQuest.found = "store";
						break;
					} 
					dialog.text = "Зайдите " + pchar.GenQuest.Hold_GenQuest.foundStr + ", он там часто бывает.";
					link.l1 = "Спасибо, зайду непременно.";
					link.l1.go = "hold_genquest3";				
				break;
				
				case 2:
					dialog.text = LinkRandPhrase(
						RandPhraseSimple("Как вы говорите? " + pchar.GenQuest.Hold_GenQuest.Name + "? Хм, никогда не слыхал о таком. А вы уверены, что он именно из нашего поселения?",
						"Э-хе-хе... разве один Господь Бог знает, где теперь его искать - то ли на небесах, то ли в преисподней. Помер он... уже второй год как помер, а всё о нём выспрашивают, вынюхивают, всё ему покоя не дают бедняге..."),
						RandPhraseSimple("Не найдёте вы его уже, на этом свете так точно. Не так давно помер он, от жёлтой лихорадки... Царствие ему небесное... А какой крепкий мужик был! В молодости, рассказывают, такие дела творил, что не приведи Господь! А поди ж ты - пришла невеста - и поминай, как звали...",
						"Эк, хватились! Он съехал давно уж. Не то к детям подался, не то в Европу - никому не известно. Просто собрал пожитки и смотался."),
						"А-а, это не того ли " + pchar.GenQuest.Hold_GenQuest.Name + " вы ищете, что вдруг разбогател и купил себе дом в Новом Альбионе? А ведь были времена, когда я его в долг ромом потчевал! Он и по сей день мне должен остался. Так поди ж ты - достань его теперь! Нет, не помнят люди добра...");
					link.l1 = "Ясно. Ну, спасибо и на этом.";	
					link.l1.go = "hold_genquest4";
				break;
				
				case 3:
					dialog.text = "А где же его искать, если не у нас в таверне? Он здесь частенько появляется - ромом старые грехи заливает, хе-хе. Вы зайдите попозже, если он появится, я скажу, чтоб вас дождался.";	
					link.l1 = "Спасибо, зайду.";
					link.l1.go = "hold_genquest5";
				break;
			}
			pchar.GenQuest.Hold_GenQuest.Speak_Tavern = true;
		break;
		
		case "hold_genquest2":
			dialog.text = "Как же не быть уверенным-то, если я всех здешних поселенцев, как одного знаю. Чай не первый год таверну держу. "+
				"Я их всех в разных видах видывал - кого жена домой тащит, кто всегда сам с полным трюмом в гавань добирается, а кого и взашей выставлять приходилось. А вы мне - 'уверены'!";
			link.l1 = "Ну ладно, спасибо и на этом...";	
			link.l1.go = "exit";
			pchar.GenQuest.Hold_GenQuest = "prisoner_escaped";
			AddQuestRecord("HoldQuest", "7");
			AddQuestUserData("HoldQuest", "sName", pchar.GenQuest.Hold_GenQuest.CapName);
			AddDialogExitQuestFunction("Hold_GenQuest_PrisonerEscaped");
		break;
		
		case "hold_genquest3":
			Hold_GenQuest_GenerateChar();		
			AddQuestRecord("HoldQuest", "8");
			AddQuestUserData("HoldQuest", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.Hold_GenQuest.City + "Gen")); 			
			AddQuestUserData("HoldQuest", "sFoundChar", pchar.GenQuest.Hold_GenQuest.foundStr);
			AddQuestUserData("HoldQuest", "sName", pchar.GenQuest.Hold_GenQuest.Name);
			SetFunctionTimerConditionParam("Hold_GenQuest_FindCharTimeIsOver", 0, 0, 1, MakeInt(24 - GetHour()), false);
			DialogExit();
		break;
		
		case "hold_genquest4":
			AddQuestRecord("HoldQuest", "13");
			AddQuestUserData("HoldQuest", "sName", pchar.GenQuest.Hold_GenQuest.CapName);
			AddQuestUserData("HoldQuest", "sNameChar", pchar.GenQuest.Hold_GenQuest.Name);
			AddQuestUserData("HoldQuest", "sSex", GetSexPhrase("ел","ла"));
			CloseQuestHeader("HoldQuest");
			DeleteAttribute(pchar,"GenQuest.Hold_GenQuest");			
			DialogExit();
		break;
		
		case "hold_genquest5":
			SetFunctionTimerConditionParam("Hold_GenQuest_GetMapTimeIsOver", 0, 0, 1, MakeInt(24 - GetHour()), false);
			DialogExit();
			AddDialogExitQuestFunction("Hold_GenQuest_GenerateMapChar");			
		break;
		
		case "CaptainComission_1":
			dialog.text = LinkRandPhrase("Он частенько сюда заходит, но сейчас что-то не видно. Заглядывайте ко мне время от времени, если он появится, я скажу, чтоб вас дождался.","Он часто здесь бывает. Если вы зайдёте позже, то наверняка его застанете.","Заходите время от времени, он здесь часто появляется. Я передам, что вы его искали.");
			link.l1 = "Спасибо, зайду попозже...";
			link.l1.go = "CaptainComission_2";
			pchar.GenQuest.CaptainComission.Speak_Tavern = true;
		break;
		
		case "CaptainComission_2":
			pchar.quest.CapComission_ExitFromTavern.win_condition.l1 = "ExitFromLocation";
			pchar.quest.CapComission_ExitFromTavern.win_condition.l1.location = pchar.location;
			pchar.quest.CapComission_ExitFromTavern.function = "CaptainComission_GenerateChar";

			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "CaptainComission_3":
			dialog.text = "Заходил. Должен сидеть где-то здесь...";
			link.l1 = "Спасибо.";
			link.l1.go = "exit";
			DeleteAttribute(pchar,"GenQuest.CaptainComission.Speak_Tavern");
		break;
		
		case "CaptainComission_Tavern1":
			pchar.GenQuest.CaptainComission.Speak_Tavern = true;
			dialog.text = "Кто же о нём не знает? Вот уже который день в поселении только об этом и судачат.";
			link.l1 = "Можешь рассказать подробнее?";
			link.l1.go = "CaptainComission_Tavern2";
		break;
		
		case "CaptainComission_Tavern2":
			dialog.text = "В общем, казнили этого капитана вместе с частью его команды, другую часть рассеяли по архипелагу, лишив выслуги и чинов... За что? В обвинительном приговоре перед казнью зачитали, что он во время патрулирования якобы пустил ко дну проходящее в акватории судно, а товар из его трюма спрятал\n"+
				"Но верится в это с трудом, потому что, ни владельца судна этого, ни товар так и не нашли... До сих пор все бухты прочёсывают.";
			link.l1 = "что, никто из команды не признался, где тайник?";	
			link.l1.go = "CaptainComission_Tavern3";	
		break;
		
		case "CaptainComission_Tavern3":
			dialog.text = "Ни один!.. Не возьму в толк, почему губернатор так легко поверил этому поклёпу? Ведь капитан " + pchar.GenQuest.CaptainComission.Name + " был на хорошем счету, а как команду держал - любой адмирал позавидует, уж поверьте моему слову.";
			link.l1 = "А где мне искать оставшихся в живых членов команды?";
			link.l1.go = "CaptainComission_Tavern4";
		break;
		
		case "CaptainComission_Tavern4":
			dialog.text = "Ну, этого уж я не знаю, увезли их всех... Хотя нет, один остался, но толку от него вам вряд ли будет. Он контуженый, раньше был канониром. Его нашли без сознания в какой-то бухте спустя два дня после того злополучного случая. Сначала в госпиталь определили, как героя, а когда дело приняло другой оборот - посадили в каземат и пытались допрашивать, но потом решили, что всё-таки нужно лечить.";
			link.l1 = "Так он сейчас в поселении?";
			link.l1.go = "CaptainComission_Tavern5";
		break;
		
		case "CaptainComission_Tavern5":
			pchar.GenQuest.CaptainComission.CanoneerName = "l" + rand(GetNamesCount(NAMETYPE_ORIG) - 1);
			dialog.text = "Да, " + GetName( NAMETYPE_ORIG, pchar.GenQuest.CaptainComission.CanoneerName, NAME_NOM) + " его зовут, иногда сюда заходит, ром выпрашивает. Если я его увижу, скажу - чтоб вас дождался.";
			link.l1 = "Спасибо, я позже наведаюсь.";
			link.l1.go = "CaptainComission_Tavern6";
		break;
		
		case "CaptainComission_Tavern6":
			AddQuestRecord("CaptainComission2", "39");
			AddQuestUserData("CaptainComission2", "sShipType", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name") + "Gen"))); 
			AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);
			AddQuestUserData("CaptainComission2", "sCharName", GetName( NAMETYPE_ORIG, pchar.GenQuest.CaptainComission.CanoneerName, NAME_ABL));
			AddQuestUserData("CaptainComission2", "sShipName", pchar.GenQuest.CaptainComission.ShipTypeName);			
			SetFunctionExitFromLocationCondition("CaptainComission_GenerateCanoneer", pchar.location, false);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "CaptainComission_Tavern7":
			DeleteAttribute(pchar,"GenQuest.CaptainComission.Speak_Tavern");
			dialog.text = "Как не знать? Знаю конечно. А вам он на что?";
			link.l1 = "Дело у меня к нему.";
			link.l1.go = "CaptainComission_Tavern8";
		break;
		
		case "CaptainComission_Tavern8":
			dialog.text = "Вы бы, " + GetAddress_Form(pchar) + ", поосторожнее с этим 'делом'. " + pchar.GenQuest.CaptainComission.Name + " схвачен по подозрению в служебном преступлении, и сейчас по всему острову рыщут губернаторские ищейки в поисках его сообщников.";
			link.l1 = "Однако... А что он такое натворил?";
			link.l1.go = "CaptainComission_Tavern9";
		break;
		
		case "CaptainComission_Tavern9":
			dialog.text = "Не знаю насколько это правда, но говорят, что он спрятал груз, который конфисковал у проходящего мимо пиратского судна. Только вот ни пирата, ни груза найти никому не удалось. Не возьму в толк, почему губернатор так легко поверил этому поклёпу? Ведь капитан " + pchar.GenQuest.CaptainComission.CapName + " был на хорошем счету, и вояка он отменный, уж поверьте моему слову, " + GetAddress_Form(pchar) + ".";
			link.l1 = "Ну, спасибо, что предупредил. Всего хорошего.";
			link.l1.go = "CaptainComission_Tavern10";
		break;
		
		case "CaptainComission_Tavern10":
			if(!CheckAttribute(pchar,"GenQuest.CaptainComission.GetRumour"))
			{
				pchar.GenQuest.CaptainComission.GetRumour = true;
				SaveCurrentQuestDateParam("GenQuest.CaptainComission.GetRumour");
				SetFunctionTimerConditionParam("CaptainComission_TimeIsOver", 0, 0, 2, MakeInt(24 - GetHour()), false);
				AddQuestRecord("CaptainComission2", "19");
				AddQuestUserData("CaptainComission2", "sShipType", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name") + "Gen"))); // лесник окончание
				AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);
			}			
			DialogExit();
		break;
				
		case "EncGirl_1":
			dialog.text = "А вам она зачем понадобилась?";
			link.l1 = "Дело к ней есть...";
			link.l1.go = "EncGirl_2";
		break;
		
		case "EncGirl_2":
			dialog.text = "У половины мужиков нашего поселения к ней дело есть. Если бы женщины её поймали, то голышом вышвырнули бы за городские ворота.";
			link.l1 = "М-да. "+ GetSexPhrase("Похоже, я стал в хвост длинной очереди. Если её кто будет спрашивать, скажи, пусть занимает за мной","Понятно") +"...";
			link.l1.go = "exit";
			pchar.quest.EncGirl_SpeakTavernKeeper.over = "yes";
			DeleteAttribute(pchar, "GenQuest.EncGirl");
		break;
		
		case "EncGirl_3":
			dialog.text = "Он частенько сюда заходит в надежде подыскать работу, но сейчас что-то не видно. Заглядывайте ко мне время от времени, если он появится, я скажу, чтоб вас дождался.";
			link.l1 = "Спасибо, зайду попозже...";
			link.l1.go = "exit";
			pchar.GenQuest.EncGirl = "FindingLover";
			pchar.quest.EncGirl_ExitTavern.win_condition.l1 = "ExitFromLocation";
			pchar.quest.EncGirl_ExitTavern.win_condition.l1.location = pchar.location;
			pchar.quest.EncGirl_ExitTavern.function = "EncGirl_GenerateLover";
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
			dialog.text = "Какая благодарность?! за что благодарность?! Мало того, что этот оболтус уже полгода слоняется без работы, так ещё и любезничать время нашёл! Да я в его годы уже своё дело держал. А он, ишь, разохотился! У губернатора, вон, дочка на выданье, а этот приволок какую-то шалаву безродную, прости Господи, и благословения родительского испрашивает!";
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
			dialog.text = "Какие такие чувства?! О каких чувствах вы говорите? Взрослый, вроде человек, а туда же... чувства! Стыдно вам должно быть молодёжи в таких делах потакать, да в сводни подряжаться. Девчонку из родительского гнезда вырвали и моему молокососу жизнь сломали. Не будет вам никакой благодарности. Прощайте.";
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
				
		case "ShipLetters_4":
			pchar.questTemp.different.GiveShipLetters.speakTavern = true;
			if(sti(pchar.questTemp.different.GiveShipLetters.variant) == 0)
			{
				dialog.text = "Дайте-ка взглянуть ! Хм... Вы же сами - капитан. Думаю, Вам стоит зайти к начальнику порта.";
				link.l1 = "Спасибо за совет.";
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = "Дайте-ка взглянуть! О! Судя по имени, они принадлежат одному моему постоянному посетителю, весьма достойному человеку. Я могу сам передать документы владельцу.";
				link.l1	= "Пожалуй, нет ...";
				link.l1.go = "exit";
				link.l2 = "Рад"+ GetSexPhrase("","а") +", что смог"+ GetSexPhrase("","ла") +" быть ему полез"+ GetSexPhrase("ен","на") +".";
				link.l2.go = "ShipLetters_end";				
			}	
		break;
		
		case "ShipLetters_end":
			TakeItemFromCharacter(pchar, "CaptainBook"); 
			pchar.questTemp.different = "free";
			pchar.quest.GiveShipLetters_null.over = "yes"; //снимаем таймер 
			AddQuestRecord("GiveShipLetters", "3");			
			CloseQuestHeader("GiveShipLetters");
			DeleteAttribute(pchar, "questTemp.different.GiveShipLetters"); 
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		//zagolski. переделка
		case "work":
			if (sti(NPChar.nation) != PIRATE && GetNationRelation2MainCharacter(sti(NPChar.nation)) == RELATION_ENEMY)
			{
				dialog.text = RandPhraseSimple("Мне без разницы кого обслуживать - деньги не имеют национальности. Но вот помогать тебе я не стану, так как ты приш"+ GetSexPhrase("ел","ла") +" под флагом " + NationNameGenitive(sti(pchar.nation)) + ".", "Я всего лишь простой хозяин таверны, но сотрудничать с " + NationNameAblative(sti(pchar.nation)) + " никакого желания не имею.");
				link.l1 = RandPhraseSimple("Хм, твое право...", "Ну, как знаешь...");
				link.l1.go = "exit";
				break;
			}
			if (isBadReputation(pchar, 40))
			{
				dialog.text = RandPhraseSimple("Пассажиров обычно хватает. Только вряд ли среди них найдется такой простофиля, чтобы решился путешествовать на твоем судне. Дурная слава бежит впереди тебя, а репутацию честного капитана еще заслужить нужно.", "Ко мне часто обращаются торговцы, которым нужно сопровождение. Но дурная слава ходит за тобой по пятам, и я никому не стану рекомендовать твои услуги. Мне своя репутация дороже.");
				link.l1 = RandPhraseSimple("Да ты верь поменьше разным сплетням...", "Да уж, всем рты не позатыкаешь...", "Эх, трусоватый нынче народец пошел...");
				link.l1.go = "exit";
				break;
			}
			if (sti(Pchar.Ship.Type) == SHIP_NOTUSED)
        	{
				dialog.text = "А корабль твой где? Ты что - на собственном горбу пассажиров возить собрался?";
				link.l1 = "Хм, и то верно...";
				link.l1.go = "exit";
				break;
			}
			dialog.text = "Работа найдется, если не боишься ходить в пиратские поселения или в порты вражеских наций. Что-то конкретное интересует?";
			link.l1 = "Ну, это не страшно. Я бы взял"+ GetSexPhrase("ся","ась") +" за эскорт.";
			link.l1.go = "work_1";
			link.l2 = "Пассажиры есть? Отвезу, хоть к черту в зубы, лишь бы деньги платили.";
			link.l2.go = "work_2";
			link.l3 = "Нет, такая работа не по мне. Спасибо.";
			link.l3.go = "exit";
		break;

		case "work_1":
				dialog.text = "По поводу эскорта ко мне не обращаются обычно. Поспрашивай сам в таверне купцов - возможно, им понадобится твоя помощь.";
				link.l1 = "Хорошо. Как скажешь.";
                link.l1.go = "exit";
		break;

		case "work_2":
			if (!CheckAttribute(npchar, "work_date") || GetNpcQuestPastDayParam(npchar, "work_date") >= 2 || bBettaTestMode)
    		{					
				if (GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) < 5)//при низком авторитете не даем
				{
					dialog.text = "Извините, но желающих отправиться в путь вместе с вами у меня нет.";
					link.l1 = "Понятно. Как скажете.";
					link.l1.go = "exit";
					break;
				}
		         // пассажир
				if (drand(6) > 1)
				{
					dialog.Text = "Вон тип в таверну зашел, он недавно попутное судно спрашивал, куда-то добраться хотел. Если хочешь, переговори с ним.";
					link.l1 = RandPhraseSimple("А что за тип? Может проходимец какой, или в розыске?", "А кто он такой? Проблем с ним не будет?");
					Link.l1.go = "PassangerAreYouSure";
				}
				else
				{
					dialog.text = "Нет, сегодня ни один не спрашивал. Может, в другой день...";
					link.l1 = RandPhraseSimple("Ну нет, так нет. Чего уж тут...", "Да, не свезло... Ну ладно, прощайте.");
					link.l1.go = "exit";
				}
            }
    		else
    		{
				dialog.text = "Сегодня уже никого нет. Заходите через пару дней.";
				link.l1 = "Хорошо. Как скажешь.";
                link.l1.go = "exit";
    		}
        break;

        case "ConvoyAreYouSure":
		    dialog.text = LinkRandPhrase("Да кто ж его знает. Ты спросил"+ GetSexPhrase("","а") +" - я ответил.", "Ну, это уж тебе само"+ GetSexPhrase("му","й") +" решать. Я бы тут ни за кого не поручился.", "Решай сам"+ GetSexPhrase("","а") +", ко мне всякие захаживают. Это же таверна, а не резиденция губернатора.");
			Link.l1 = "Ну спасибо, сейчас поторгуемся.";
			Link.l1.go = "exit";
			pchar.quest.destination = findTraderCity(npchar);
			pchar.ConvoyQuest.City = npchar.city;
			AddDialogExitQuest("prepare_for_convoy_quest");
			SaveCurrentNpcQuestDateParam(npchar, "work_date");
        break;

        case "PassangerAreYouSure":
		    dialog.text = LinkRandPhrase("Да кто ж его знает. Ты спросил"+ GetSexPhrase("","а") +" - я ответил.", "Ну, это уж тебе само"+ GetSexPhrase("му","й") +" решать. Я бы тут ни за кого не поручился.", "Решай сам"+ GetSexPhrase("","а") +", ко мне всякие захаживают. Это же таверна, а не резиденция губернатора.");
			Link.l1 = "Ясно, сейчас выясним что это за тип.";
			Link.l1.go = "exit";
			sGlobalTemp = findPassangerCity(npchar);
			pchar.GenQuest.GetPassenger_City = npchar.city;
			AddDialogExitQuest("prepare_for_passenger_quest");
			SaveCurrentNpcQuestDateParam(npchar, "work_date");
        break;

		 case "fight":
			DialogExit();
            NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_group_Attack(NPChar, Pchar);
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "room":
   			if (chrDisableReloadToLocation || CheckAttribute(pchar, "questTemp.different.Church_NightGuard")) //кто-то должен подойти к ГГ.
			{
				dialog.text = "Сейчас комната занята, " + GetAddress_Form(NPChar) + ", ничем не могу помочь.";
				link.l1 = "Жаль, очень жаль...";
				link.l1.go = "exit";
				break;
			}
			// суп из черепахи
			if (CheckAttribute(pchar, "questTemp.Terrapin.Room_close") && npchar.location == "Tortuga_tavern")
			{
				dialog.text = "Комнату у меня сейчас снимает месье Анри Тибо, и оплатил ее на месяц вперед, так что ничем помочь не могу, капитан.";
				link.l1 = "Жаль, очень жаль...";
				link.l1.go = "exit";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.Terrapin") && pchar.questTemp.Terrapin == "cave" && npchar.location == "Tortuga_tavern")
			{
				dialog.text = "Сейчас комната занята, " + GetAddress_Form(NPChar) + ", ничем не могу помочь.";
				link.l1 = "Жаль, очень жаль...";
				link.l1.go = "exit";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "shore" && npchar.location == "Baster_tavern") // 070712
			{
				dialog.text = "Сейчас комната занята, " + GetAddress_Form(NPChar) + ", ничем не могу помочь.";
				link.l1 = "Жаль, очень жаль...";
				link.l1.go = "exit";
				break;
			}
			//-->> квест официантки
			if (pchar.questTemp.different == "FackWaitress_toRoom")
			{
				dialog.text = "Вы хотите снять комнату? Не проблема. С вас 100 монет - и можете туда пройти.";
				if (sti(pchar.money) >= 100)
				{
					link.l1 = "Забирай свои деньги, открывай комнату, приятель...";
					link.l1.go = "exit";
					AddMoneyToCharacter(pchar, -100);
					LocatorReloadEnterDisable(npchar.city + "_tavern", "reload2_back", false);
					pchar.questTemp.different = "FackWaitress_toRoomUp";
				}
				else
				{
					link.l1 = "Хм, я, пожалуй, подойду попозже...";
					link.l1.go = "exit";
				}
				break;
			}
			if (pchar.questTemp.different == "FackWaitress_toRoomUp")//квест официантки
			{
				dialog.text = "Комната ваша, идите и отдыхайте...";
				link.l1 = "Хорошо, приятель, спасибо.";
				link.l1.go = "exit";
				break;
			}
			//<<-- квест официантки
			// --> квест "Девица в джунглях"
			if(CheckAttribute(pchar,"GenQuest.EncGirl") && npchar.city == pchar.GenQuest.EncGirl.city)
			{
				if(pchar.GenQuest.EncGirl == "EncGirl_ToTavern")
				{
					dialog.text = "Вы хотите снять комнату? Не проблема. С вас 100 монет - и можете туда пройти.";
					if (sti(pchar.money) >= 100)
					{
						link.l1 = "Забирай свои деньги, открывай комнату, приятель...";
						link.l1.go = "exit";
						AddMoneyToCharacter(pchar, -100);
						LocatorReloadEnterDisable(npchar.city + "_tavern", "reload2_back", false);
						pchar.GenQuest.EncGirl = "EncGirl_toRoomUp";
					}
					else
					{
						link.l1 = "Хм, я, пожалуй, подойду попозже...";
						link.l1.go = "exit";
					}
					break;
				}
				if (pchar.GenQuest.EncGirl == "EncGirl_toRoomUp")//квест  по спасению тетки в пампасах
				{
					dialog.text = "Комната ваша, идите и отдыхайте...";
					link.l1 = "Хорошо, приятель, спасибо.";
					link.l1.go = "exit";
					break;
				}
			}
			// <-- квест "Девица в джунглях"
			dialog.text = "На какой срок вы планируете остановиться?";
			if(!isDay())
			{
				link.l1 = "До утра.";
				link.l1.go = "room_day";
			}
			else
			{
				link.l1 = "До ночи.";
				link.l1.go = "room_night";
				link.l2 = "До следующего утра.";
				link.l2.go = "room_day_next";
			}
		break;

		case "room_day":
			dialog.text = "Это обойдется вам в 5 песо.";
			if (makeint(pchar.money) >= 5)
			{
				link.l1 = "Идет. Вот твои деньги.";
				link.l1.go = "room_day_wait";
			}
			link.l2 = pcharrepphrase("Ты сдаешь королевские покои? Нет уж, за такую цену я лучше посижу в общей зале.",
            "Увы, видимо, такая роскошь, как сон на кровати, не для моего кошелька. Я переночую в общей зале.");
			link.l2.go = "hall_day_wait";
			if (!CheckAttribute(pchar, "questTemp.Sharlie.Lock"))
			{
				link.l3 = "Не сейчас. Давай поговорим о чем-нибудь другом.";
				link.l3.go = "int_quests";
			}
		break;

		case "room_day_next":
			dialog.text = "Это обойдется вам в 10 песо.";
			if (makeint(pchar.money) >= 10)
			{
				link.l1 = "Идет. Вот твои деньги.";
				link.l1.go = "room_day_wait_next";
			}
			link.l2 = pcharrepphrase("Ты сдаешь королевские покои? Нет уж, за такую цену я лучше посижу в общей зале.",
            "Увы, видимо, такая роскошь, как сон на кровати, не для моего кошелька. Я переночую в общей зале.");
			link.l2.go = "hall_day_wait";
			if (!CheckAttribute(pchar, "questTemp.Sharlie.Lock"))
			{
				link.l3 = "Не сейчас. Давай поговорим о чем-нибудь другом.";
				link.l3.go = "int_quests";
			}
		break;

		case "room_night":
			dialog.text = "Это обойдется вам в 5 песо.";
			if (makeint(pchar.money) >= 5)
			{
				link.l1 = "Идет. Вот твои деньги.";
				link.l1.go = "room_night_wait";
			}
			link.l2 = pcharrepphrase("Ты сдаешь королевские покои? Нет уж, за такую цену я лучше посижу в общей зале.",
            "Увы, видимо, такая роскошь, как сон на кровати не для моего кошелька. Я переночую в общей зале.");
			link.l2.go = "hall_night_wait";
			if (!CheckAttribute(pchar, "questTemp.Sharlie.Lock"))
			{
				link.l3 = "Не сейчас. Давай поговорим о чем-нибудь другом.";
				link.l3.go = "int_quests";
			}
		break;

		case "room_night_wait":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			AddMoneyToCharacter(pchar, -5);
			AddDialogExitQuest("sleep_in_tavern");
			TavernWaitDate("wait_night");
		break;

		case "hall_night_wait":
			if (cRand(3) == 1)
            {
                Dialog.text = "Убирайся, оборван"+ GetSexPhrase("ец","ка") +"! Нечего тут в общей зале просиживать за бесплатно.";
				link.l1 = "Ладно, ладно... уже ухожу.";
				link.l1.go = "exit";
            }
            else
            {
				DialogExit();
				NextDiag.CurrentNode = NextDiag.TempNode;
				TavernWaitDate("wait_night");
			}
		break;

		case "room_day_wait":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			AddMoneyToCharacter(pchar, -5);
			AddDialogExitQuest("sleep_in_tavern");
			if (CheckAttribute(pchar, "GenQuest.LigaAttack") && drand(1) == 1)
			{
				TavernWaitDate("wait_night");
				pchar.GenQuest.LigaAttack.Go = "true"; //атака киллеров
			}
			else TavernWaitDate("wait_day");
		break;

		case "room_day_wait_next":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			AddMoneyToCharacter(pchar, -10);
			AddDialogExitQuest("sleep_in_tavern");
			if (CheckAttribute(pchar, "GenQuest.LigaAttack") && drand(1) == 1)
			{
				TavernWaitDate("wait_night");
				pchar.GenQuest.LigaAttack.Go = "true"; //атака киллеров
			}
			else TavernWaitDate("wait_day");
		break;

		case "hall_day_wait":
			if (drand(1) == 1)
            {
                Dialog.text = "Убирайся, оборван"+ GetSexPhrase("ец","ка") +"! Нечего тут в общей зале просиживать за бесплатно.";
				link.l1 = "Ладно, ладно... уже ухожу.";
				link.l1.go = "exit";
            }
            else
            {
				DialogExit();
				NextDiag.CurrentNode = NextDiag.TempNode;
				TavernWaitDate("wait_day");
			}
		break;
		
		case "tavern_keeper":
			NextDiag.TempNode = "First time";

			dialog.text = "Уважаемые, прошу вас прекратить это безобразие в моей таверне, или я позову стражников!";
			link.l1 = "Ладно, ладно, я уже ухожу.";
			link.l1.go = "exit_sit";
		break;

		case "exit_sit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			AddDialogExitQuest("exit_sit");
		break;
		
		//******************* ноды квеста священника. поиск грабителей (квест № 2)**********************
		case "Tavern_GenQuest_Church_2_1":
			dialog.text = "Мне об этом мало что известно... Спроси лучше кого-нибудь из завсегдатаев.";
			link.l1 = "Ясно, спасибо.";
			link.l1.go = "exit";
			DeleteAttribute(PChar, "GenQuest.ChurchQuest_2.AskBarmen");
		break;
			
		//******************* ноды квеста священника. вернуть рукописи (квест № 1)**********************
		case "Tavern_ChurchGenQuest1_Node_1":
			dialog.text = "Мы не обслуживаем в долг, судар"+ GetSexPhrase("ь","ыня") +".";
			link.l1 = "Я привык"+ GetSexPhrase("","ла") +" расплачиваться звонкой монетой, любезный. Или здесь уже не принимают золото или серебро?";
			link.l1.go = "Tavern_ChurchGenQuest1_Node_2";
		break;
			
		case "Tavern_ChurchGenQuest1_Node_2":
			dialog.text = "Простите, госпо"+ GetSexPhrase("дин","жа") +" капитан, но ваш друг задолжал, и я подумал...";
			link.l1 = "Поменьше думай, любезный, и расторопней обслуживай. Так сколько тебе должен мой доблестный друг?";
			link.l1.go = "Tavern_ChurchGenQuest1_Node_3";
		break;
			
		case "Tavern_ChurchGenQuest1_Node_3":
			iTemp = (rand(3)+1)*100;
			PChar.GenQuest.ChurchQuest_1.MoneyToBarmen = iTemp;
			if(rand(1) == 0) // "Если он простой и сразу отдаёт"
			{
				dialog.text = FindRussianMoneyString(iTemp) + ", госпо"+ GetSexPhrase("дин","жа") +" капитан, и он оставил в залог церковные книги - это всё, что у него было при себе ценного.";
				if(sti(PChar.money) >= iTemp)
				{
					link.l1 = "Держи монеты и давай сюда манускрипты. Да аккуратнее, это тебе не бочонок эля, а писания Божьих праведников!";
					link.l1.go = "Tavern_ChurchGenQuest1_Node_4_1";
				}
				else
				{
					link.l1 = "Подожди немного... Сейчас я принесу тебе эти деньги";
					link.l1.go = "exit";
					PChar.GenQuest.ChurchQuest_1.NoMoneyToBarmen = true;
				}
			}
			else // "Если он не простой"
			{
				dialog.text = FindRussianMoneyString(iTemp) + ", госпо"+ GetSexPhrase("дин","жа") +" капитан.";
				link.l1 = "Я оплачу его долг и заберу то, что он оставил в залог.";
				link.l1.go = "Tavern_ChurchGenQuest1_Node_4_2";
			}
		break;
			
		case "Tavern_ChurchGenQuest1_Node_4_1":
			DialogExit();
			AddMoneyToCharacter(PChar, -sti(PChar.GenQuest.ChurchQuest_1.MoneyToBarmen));
			AddItems(PChar, "Bible", 1);	// Даем рукописи
			items[FindItem("Bible")].Name = "itmname_ChurchGenQuest1Bible";	// Меняем имя. Потом поменять обратно!
			ChangeItemDescribe("Bible", "itmdescr_ChurchGenQuest1Bible"); // Меняем дескрайб. Потом поменять обратно!
			items[FindItem("Bible")].City = XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.QuestTown + "Gen"); // Переменная. Потом удалить!
			DeleteAttribute(PChar, "GenQuest.ChurchQuest_1.NeedToDialogWithBarmen");
			sQuestTitle = PChar.GenQuest.ChurchQuest_1.QuestTown + "ChurchGenQuest1";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest1", "8");
			AddQuestUserData(sQuestTitle, "sColony", XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.QuestTown + "Gen"));
			AddQuestUserData(sQuestTitle, "sName", GetFullName(CharacterFromID("ChurchGenQuest1_Cap")));
			PChar.GenQuest.ChurchQuest_1.Complete = true; // Квест выполнен
			SetFunctionTimerCondition("Church_GenQuest1_DeleteCapitan", 0, 0, 2, false);
		break;
			
		case "Tavern_ChurchGenQuest1_Node_4_2":
			dialog.text = "Нет, судар"+ GetSexPhrase("ь","ыня") +", так не пойдёт.";
			link.l1 = "Что значит 'не пойдёт'?! За кэпа выплачивают его долг - он доволен. Ты получаешь свои деньги - ты доволен. Мне возвращают залог - я довол"+ GetSexPhrase("ен","ьна") +". Все довольны, и всем хорошо. Почему это 'не пойдёт'?";
			link.l1.go = "Tavern_ChurchGenQuest1_Node_4_2_1";
		break;
			
		case "Tavern_ChurchGenQuest1_Node_4_2_1":
			dialog.text = "Потому, госпо"+ GetSexPhrase("дин","жа") +" капитан, что мне не нужны деньги. Я слишком хорошо знаю этого вашего капитана, и даже не надеялся, что когда-нибудь он сможет расплатиться, и потребует назад эти рукописи.";
			link.l1 = "Как это - не нужны деньги? Значит, ты хотел оставить себе книги? Но зачем, во имя Господа?!";
			link.l1.go = "Tavern_ChurchGenQuest1_Node_4_2_2";
		break;
			
		case "Tavern_ChurchGenQuest1_Node_4_2_2":
			dialog.text = "Как раз во имя Господа, судар"+ GetSexPhrase("ь","ыня") +". Мой маленький сын был очень болен, и мы с женой дали обет, что пожертвуем на храм, если Создатель избавит дитя от лихорадки. Божье милосердие безгранично, ребёнок жив и здоров, и теперь мы должны исполнить свой обет. И вот как раз вовремя появляется капитан " + PChar.GenQuest.ChurchQuest_1.CapFullName + " и оставляет в залог церковные книги. Я не мог допустить такого непотребства - чтобы за выпивку расплачивались Словом Божием - и решил сегодня же пожертвовать книги нашему приходскому священнику.";
			link.l1 = "Сомнений нет, дело благое, но тебе следует знать, что эти манускрипты принадлежат другому священнику, то есть даже не священнику, а могущественному епископу, моему духовному наставнику, который очень рассердится, а возможно и проклянёт того, кто на них посягает... Я хотел"+ GetSexPhrase("","а") +" бы выкупить их у тебя и доставить ему в целости и сохранности.";
			link.l1.go = "Tavern_ChurchGenQuest1_Node_4_2_3";
		break;
			
		case "Tavern_ChurchGenQuest1_Node_4_2_3":
			dialog.text = "Судар"+ GetSexPhrase("ь","ыня") +"... Госпо"+ GetSexPhrase("дин","жа") +" капитан... Конечно, я отдам, и не нужно никаких денег. Только замолвите словечко перед епископом, пусть он благословит нас и зачтёт выполнение обета...";
			link.l1 = "Безусловно, любезный, обет вам с женой зачтётся, потому что вы, как-никак, пожертвовали выручкой, вернув рукописи по принадлежности, а уж в какую церковь - не важно, все под одним Богом ходим. Давай-ка их сюда, и удачи тебе...";
			link.l1.go = "Tavern_ChurchGenQuest1_Node_4_2_4";
		break;
			
		case "Tavern_ChurchGenQuest1_Node_4_2_4":
			DialogExit();
			AddItems(PChar, "Bible", 1);	// Даем рукописи
			items[FindItem("Bible")].Name = "itmname_ChurchGenQuest1Bible";	// Меняем имя. Потом поменять обратно!
			ChangeItemDescribe("Bible", "itmdescr_ChurchGenQuest1Bible"); // Меняем дескрайб. Потом поменять обратно!
			items[FindItem("Bible")].City = XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.QuestTown + "Gen"); // Переменная. Потом удалить!
			AddMoneyToCharacter(PChar, -sti(PChar.GenQuest.ChurchQuest_1.MoneyToBarmen));
			DeleteAttribute(PChar, "GenQuest.ChurchQuest_1.NeedToDialogWithBarmen");
			sQuestTitle = PChar.GenQuest.ChurchQuest_1.QuestTown + "ChurchGenQuest1";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest1", "9");
			AddQuestUserData(sQuestTitle, "sColony", XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.QuestTown + "Acc"));
			PChar.GenQuest.ChurchQuest_1.Complete = true; // Квест выполнен
			SetFunctionTimerCondition("Church_GenQuest1_DeleteCapitan", 0, 0, 2, false);
		break;
		
		//Jason --> генератор Неудачливый вор
		case "Device_Tavern":
			dialog.text = "Гм, "+pchar.GenQuest.Device.Shipyarder.Type+"? Впервые слышу... Хоть что это за вещь такая - сколько живу на свете, ничего подобного в глаза не видел.";
			link.l1 = "Ну, это судостроительный инструмент, "+pchar.GenQuest.Device.Shipyarder.Describe+". Никто ничего подобного тебе не предлагал?";
			link.l1.go = "Device_Trader_1";
			npchar.quest.Device = "true";
		break;
		
		case "Device_Trader_1":
			if (sti(pchar.GenQuest.Device.Shipyarder.Chance1) == 6)
			{
				dialog.text = "Хм... Да, приносил мне такую вещь один странный тип. Только он ее никак не назвал, а просто пытался обменять на выпивку. Я ему отказал - мне эта штуковина ни к чему.";
				link.l1 = "А как выглядел этот человек и куда пошел? Мне очень нужен этот инструмент.";
				link.l1.go = "Device_Common";
			}
			else
			{
				dialog.text = "Нет, никто не приносил. Так что помочь ничем не могу. Поспрашивай еще у кого.";
				link.l1 = "Ясно. Пойду спрашивать!";
				link.l1.go = "exit";
			}
		break;
		// <-- генератор Неудачливый вор
		
		//Jason --> генератор Место под солнцем
		case "Sunplace_Tavern":
			if (makeint(environment.time) > 12.0 && makeint(environment.time) < 17.0)//в магазине
			{
				dialog.text = ""+pchar.GenQuest.Sunplace.Trader.Enemyname+"? Он недавно был у меня, а сейчас вроде должен быть у своего компаньона - нашего лавочника. Зайдите в магазин, там вы его наверняка застанете.";
				link.l1 = "Спасибо! Ты мне здорово помог!";
				link.l1.go = "Sunplace_Tavern_1";
			}
			else//ушел на рыбалку
			{
				dialog.text = ""+pchar.GenQuest.Sunplace.Trader.Enemyname+"? Он сегодня с раннего утра вышел в море на своем люггере на морскую прогулку. Бьюсь об заклад, он сейчас в какой-нибудь бухте стоит у фальшборта и любуется пейзажем. Так что если он вам нужен - или поищите его в море, или подождите, пока вернется через день-другой...";
				link.l1 = "Спасибо! Ждать я, пожалуй, не буду - мне проще его разыскать в море. Всего доброго!";
				link.l1.go = "Sunplace_Tavern_2";
			}
		break;
		
		case "Sunplace_Tavern_1"://магазин
			pchar.quest.Sunplace_Store.win_condition.l1 = "location";
			pchar.quest.Sunplace_Store.win_condition.l1.location = pchar.GenQuest.Sunplace.Trader.CityT + "_store";
			pchar.quest.Sunplace_Store.function = "Sunplace_CreateTrader";
			AddQuestRecord("Sunplace", "6");
			AddQuestUserData("Sunplace", "sName", pchar.GenQuest.Sunplace.Trader.Enemyname);
			AddQuestUserData("Sunplace", "sCity", XI_ConvertString("Colony"+pchar.GenQuest.Sunplace.Trader.CityT+"Gen"));
			DialogExit();
			pchar.GenQuest.Sunplace.Trader = "hunt";
		break;
		
		case "Sunplace_Tavern_2"://рыбалка
			pchar.GenQuest.Sunplace.Trader.IslandID = GetCharacterCurrentIslandId(npchar);
			pchar.GenQuest.Sunplace.Trader.EnemyNation = npchar.nation;
			pchar.quest.Sunplace_Sea.win_condition.l1 = "location";
			pchar.quest.Sunplace_Sea.win_condition.l1.location = pchar.GenQuest.Sunplace.Trader.IslandID;
			pchar.quest.Sunplace_Sea.function = "Sunplace_CreateTraderLugger";
			AddQuestRecord("Sunplace", "7");
			AddQuestUserData("Sunplace", "sName", pchar.GenQuest.Sunplace.Trader.Enemyname);
			AddQuestUserData("Sunplace", "sCity", XI_ConvertString("Colony"+pchar.GenQuest.Sunplace.Trader.CityT+"Gen"));
			DialogExit();
			pchar.GenQuest.Sunplace.Trader = "hunt";
		break;
		// <-- генератор Место под солнцем	
		
		// Jason --> Голландский гамбит
		case "HWICHollJacob_Tavern":
			dialog.text = "Тс-с-с... Ты чего так орешь? Он уже давно тебя ждет. Целую кварту рома вылакал. Поднимайся наверх, в комнату, он там.";
			link.l1 = "А-а, понятно. Ладно, бывай.";
			link.l1.go = "exit";
			LocatorReloadEnterDisable(pchar.questTemp.HWIC.Holl.JacobCity+"_tavern", "reload2_back", false);
			pchar.questTemp.HWIC.Holl = "JacobInRoom";
			AddDialogExitQuestFunction("Create_JacobVanBerg");
		break;
		
		case "HWICSelfFernando_Tavern":
			if (NPChar.location == pchar.questTemp.HWIC.Self.SpainCity +"_tavern")
			{
				if (makeint(environment.time) > 10.0 && makeint(environment.time) < 18.0)//на улице
				{
					dialog.text = "Да, я знаю этого благородного господина. Он должен быть где-то в городе - я недавно видел, как он проходил мимо моей таверны.";
					link.l1 = "Спасибо! Поспешу на поиски!";
					link.l1.go = "Fernando_Land";
				}
				else //в море
				{
					dialog.text = "Да, он гостит в нашем городе. Сейчас, правда, его нет - он вышел в море на своей бригантине. Думаю, он сейчас где-то недалеко, в водах нашего острова.";
					link.l1 = "Спасибо! Ты мне здорово помог!";
					link.l1.go = "Fernando_Sea";
				}
				pchar.questTemp.HWIC.Self = "KillFernando";
			}
			else
			{
				dialog.text = "Фернандо Родригес? Впервые слышу о таком. Нет, я ничего не знаю об этом человеке.";
				link.l1 = "Понятно. Буду искать дальше...";
				link.l1.go = "exit";
			}
			npchar.quest.HWICTalked = "true";
		break;
		
		case "Fernando_Land":
			pchar.quest.HWIC_Fernando.win_condition.l1 = "location";
			pchar.quest.HWIC_Fernando.win_condition.l1.location = pchar.questTemp.HWIC.Self.SpainCity +"_town";
			pchar.quest.HWIC_Fernando.function = "CreateFernandoOnLand";
			AddQuestRecord("Holl_Gambit", "3-2");
			DialogExit();
		break;
		
		case "Fernando_Sea":
			pchar.questTemp.HWIC.Self.FernandoIslandID = GetCharacterCurrentIslandId(npchar);
			pchar.quest.HWIC_Fernando.win_condition.l1 = "location";
			pchar.quest.HWIC_Fernando.win_condition.l1.location = pchar.questTemp.HWIC.Self.FernandoIslandID;
			pchar.quest.HWIC_Fernando.function = "CreateFernandoOnSea";
			AddQuestRecord("Holl_Gambit", "3-3");
			DialogExit();
		break;
		//<-- Голландский гамбит
		
		//Jason --> гонки на гидропланах
		case "Race_Advantage":
			dialog.text = "Да, конечно. Я уже в курсе о вашей победе. Вот, возьмите ваши деньги.";
			link.l1 = "Спасибо, " + npchar.name + ".";
			link.l1.go = "Race_Advantage_1";
		break;
		
		case "Race_Advantage_1":
			DialogExit();
			AddMoneyToCharacter(pchar, sti(pchar.GenQuest.Racing.Go.Money)*2);
			AddQuestRecord("Racing", "4");
			AddQuestUserData("Racing", "sStartCity", XI_ConvertString("Colony"+pchar.GenQuest.Racing.Go.StartCity+"Gen"));
			CloseQuestHeader("Racing");
			DeleteAttribute(pchar, "GenQuest.Racing.Go");
		break;
		//<-- гонки на гидропланах
		
		//Jason --> захват пассажиров
		case "Marginpassenger":
			if (CheckAttribute(pchar, "GenQuest.Marginpassenger.lose"))
			{
				dialog.text = "Э-э, сударь, так "+pchar.GenQuest.Marginpassenger.q2Name+" уж помер как "+LinkRandPhrase("месяц","три недели","два месяца")+" тому назад. "+LinkRandPhrase("Скоропостижно скончался от лихорадки","Зарезали за городскими воротами, бандиты, или дикари краснокожие","Застрелили на дуэли")+". Земля ему пухом, спаси, Господи, его душу...";
				link.l1 = "Вот это да!.. И что же мне теперь с его... кхм, делать? Ладно, спасибо за информацию. Бывай, " + npchar.name + ".";
				link.l1.go = "Marginpassenger_1";
			}
			else
			{
				dialog.text = ""+pchar.GenQuest.Marginpassenger.q2Name+"? Да должен быть где-то в городе. Поищите на улицах. Только имейте в виду, что каждый день до двенадцати дня он проводит в канцелярии губернатора, да и после девяти запирается у себя дома.";
				link.l1 = "Спасибо! Пойду искать...";
				link.l1.go = "Marginpassenger_2";
			}
		break;
		
		case "Marginpassenger_1":
			DialogExit();
			AddQuestRecord("Marginpassenger", "7");
			AddQuestUserData("Marginpassenger", "sName2", pchar.GenQuest.Marginpassenger.q2Name);
			AddQuestUserData("Marginpassenger", "sCity", XI_ConvertString("Colony"+pchar.GenQuest.Marginpassenger.City));
			pchar.GenQuest.Marginpassenger = "cabin";
		break;
		
		case "Marginpassenger_2":
			DialogExit();
			AddQuestRecord("Marginpassenger", "8");
			AddQuestUserData("Marginpassenger", "sName2", pchar.GenQuest.Marginpassenger.q2Name);
			pchar.GenQuest.Marginpassenger = "street";
		break;
		//<-- захват пассажиров
		
		//Jason --> поиск дезертира
		case "FindFugitiveTav":
			if (NPChar.city == pchar.GenQuest.FindFugitive.City && sti(pchar.GenQuest.FindFugitive.Chance) == 0)
			{
				dialog.text = NPCStringReactionRepeat("Похоже, этот твой шкипер не солгал. "+pchar.GenQuest.FindFugitive.Name+" действительно недавно прибыл в наш поселок. Ищи его на улицах днем, он часто слоняется без дела.", "Ты уже спрашивал меня об этом человеке, и я тебе все рассказал!", "Ты что, издеваешься, или на самом деле тупой? Третий раз спрашиваешь одно и то же!", "Ох, и как только такой дурень капитаном стал...", "block", 1, npchar, Dialog.CurrentNode);
				link.l1 = HeroStringReactionRepeat("Спасибо, дружище, ты мне очень помог!", "Да, да, хорошо.", "Тише, не кипятись. Я просто забыл.", "Ну ты же видишь - стал как-то...", npchar, Dialog.CurrentNode); 
				link.l1.go = DialogGoNodeRepeat("FindFugitiveTav_1", "exit", "", "", npchar, Dialog.CurrentNode);
			}
			else
			{
				dialog.text = NPCStringReactionRepeat("Нет, приятель, впервые слышу это имя. Спроси у кого еще, может, кто и слышал про такого...", "Ты уже спрашивал меня об этом человеке, и я тебе сказал: не знаю!", "Ты что, издеваешься, или на самом деле тупой? Третий раз спрашиваешь одно и то же!", "Ох, и как только такой дурень капитаном стал...", "block", 1, npchar, Dialog.CurrentNode);
				link.l1 = HeroStringReactionRepeat("Понятно. Ну, и на том спасибо.", "Да, да, хорошо.", "Тише, не кипятись. Я просто забыл.", "Ну ты же видишь - стал как-то...", npchar, Dialog.CurrentNode); 
				link.l1.go = DialogGoNodeRepeat("exit", "", "", "", npchar, Dialog.CurrentNode);	
			}
		break;
		
		case "FindFugitiveTav_1":
			DialogExit();
			AddQuestRecord("MayorsQuestsList", "12-1");
			sld = characterFromId("Fugitive");
			LAi_SetWarriorType(sld);
			LAi_warrior_DialogEnable(sld, true);
			sld.dialog.currentnode = "Fugitive_city";
			LAi_SetLoginTime(sld, 11.0, 18.0);
			ChangeCharacterAddressGroup(sld, pchar.GenQuest.FindFugitive.City+"_town", "goto", "goto"+(rand(9)+1));
		break;
		//<-- поиск дезертира
		
		//--> Бремя гасконца
		case "Sharlie_crew":
			dialog.text = "К сожалению, в данный момент я ничем не могу вам помочь - люди, которых я знаю, к вам на службу точно не пойдут. Но я дам вам совет - обратитесь вон к тому матросу, который только что сел за столик позади вас - он из группы списанных на берег с одного купеческого судна. Возможно, они согласятся пойти на ваше судно.";
			link.l1 = "Хорошо, я так и сделаю. Спасибо!";
			link.l1.go = "exit";
			pchar.questTemp.Sharlie = "sailor";
			//усадим матроса
			sld = GetCharacter(NPC_GenerateCharacter("SharlieSailor" , "citiz_31", "man", "man", 10, FRANCE, -1, true, "quest"));
			FantomMakeCoolFighter(sld, 10, 20, 20, "blade_05", "", "", 10);
			sld.Dialog.Filename = "Quest\Sharlie\OtherNPC.c";
			sld.dialog.currentnode = "Sharlie_sailor";
			sld.greeting = "town_sailor";
			LAi_SetSitType(sld);
			LAi_SetImmortal(sld, true);
			FreeSitLocator("FortFrance_tavern", "sit7");
			ChangeCharacterAddressGroup(sld, "FortFrance_tavern", "sit", "sit7");
		break;
		
		case "Sharlie_skiper":
			dialog.text = "Ничего конкретного не могу подсказать, приятель. Сейчас у меня в таверне не ошивается ни одного специалиста в навигации. Попробуй поспрашивать в порту - может, кто-то из людей что и подскажет тебе.";
			link.l1 = "Ясно. Ладно, пойду, побеседую с людьми.";
			link.l1.go = "exit";
			pchar.questTemp.Sharlie = "findskiper";
			//сгенерим наводчика
			sld = GetCharacter(NPC_GenerateCharacter("SharlieSkiperTalker", "citiz_"+(rand(19)+21), "man", "man", 10, FRANCE, -1, true, "marginal"));
			FantomMakeCoolFighter(sld, 10, 20, 20, RandPhraseSimple("blade_04","blade_06"), "", "", 10);
			sld.Dialog.Filename = "Quest\Sharlie\OtherNPC.c";
			sld.dialog.currentnode = "skipertalker";
			sld.greeting = "marginal";
			LAi_SetWarriorType(sld);
			LAi_SetImmortal(sld, true);
			LAi_group_MoveCharacter(sld, "FRANCE_CITIZENS");
			ChangeCharacterAddressGroup(sld, "FortFrance_town", "patrol", "patrol"+(rand(13)+1));
			LAi_SetLoginTime(sld, 6.0, 21.99);
		break;
		//<-- Бремя гасконца
		
		// Addon 2016-1 Jason пиратская линейка
		case "mtraxx_tortuga":
			sld = characterFromId("Tortuga_waitress");
            dialog.text = "Сию минуту, месье!.. Лучшее французское вино! А дверь в комнату вам сейчас отворят. "+sld.name+"! Ступай и отопри комнату, быстро!.. С вас 1000 песо, месье.";
			link.l1 = "Держи!..";
			link.l1.go = "mtraxx_tortuga_1";
		break;
		
		case "mtraxx_tortuga_1":
			AddMoneyToCharacter(pchar, -1000);
            DialogExit();
			pchar.questTemp.Mtraxx.Retribution = "room";
			pchar.quest.mtraxx_retribution_room.win_condition.l1 = "locator";
			pchar.quest.mtraxx_retribution_room.win_condition.l1.location = "Tortuga_tavern";
			pchar.quest.mtraxx_retribution_room.win_condition.l1.locator_group = "reload";
			pchar.quest.mtraxx_retribution_room.win_condition.l1.locator = "reload2_back";
			pchar.quest.mtraxx_retribution_room.function = "Mtraxx_RetributionToRoom";
		break;
	}
}

string findTraderCity(ref NPChar)
{
	int n, nation;
    int storeArray[MAX_COLONIES];
    int howStore = 0;

	for(n=0; n<MAX_COLONIES; n++)
	{
		nation = GetNationRelation(sti(npchar.nation), sti(colonies[n].nation));
		if (colonies[n].id != "Panama" && colonies[n].nation != "none" && GetIslandByCityName(npchar.city) != colonies[n].islandLable) //не на свой остров
		{
			if (nation == RELATION_ENEMY || sti(npchar.nation) == PIRATE)
			{
				storeArray[howStore] = n;
				howStore++;
			}
		}
	}
	if (howStore == 0) return "none";
	nation = storeArray[cRand(howStore-1)];
	return colonies[nation].id;
}

string findPassangerCity(ref NPChar)
{
	int n, nation;
    int storeArray[MAX_COLONIES];
    int howStore = 0;

	for(n=0; n<MAX_COLONIES; n++)
	{
		nation = GetNationRelation(sti(npchar.nation), sti(colonies[n].nation));
		if (colonies[n].nation != "none" && colonies[n].id != "Panama" && GetIslandByCityName(npchar.city) != colonies[n].islandLable) //не на свой остров
		{
			if (nation == RELATION_ENEMY || sti(npchar.nation) == PIRATE)
			{
			storeArray[howStore] = n;
			howStore++;
		}
	}
	}
	if (howStore == 0) return "none";
	nation = storeArray[cRand(howStore-1)];
	return colonies[nation].id;
}
