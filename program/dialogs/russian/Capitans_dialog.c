// разговор с капитаном на палубе  Boal
//homo 25/06/06
#include "DIALOGS\russian\Rumours\Common_rumours.c"
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, Diag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(Diag, NPChar.Dialog);
    //homo Осады
    aref aData;
    makearef(aData, NullCharacter.Siege);
    string sCap, sGroup;
    string fort;

    if (CheckAttribute(aData, "nation"))
    {
	    sCap = NationShortName(sti(aData.nation))+"SiegeCap_";
	    sGroup = "Sea_"+sCap+"1";
	    
	   // string myships  = GetCompanionQuantity(PChar);
       // string escships = Group_GetCharactersNum(sGroup);
        
        switch(sti(aData.conation))
        {
            case 0:  fort = "Английским фортом"; break;
            case 1:  fort = "Французским фортом"; break;
            case 2:  fort = "Испанским фортом"; break;
            case 3:  fort = "Голландским фортом"; break;
            case 4:  fort = "Пиратским фортом"; break;
        }
        int ifortPower = sti(colonies[FindColony(aData.colony)].FortValue);
        int fortDamage = CheckFortInjuri();
        int SquadronDamage = CheckSquadronInjuri();
        
    }

    int iMoney;
	ref sld;
    
    if (CheckNPCQuestDate(npchar, "Card_date"))
	{
		SetNPCQuestDate(npchar, "Card_date");
		npchar.money = 3000 + rand(10) * makeint(100 * sti(PChar.rank) * (10.0 / MOD_SKILL_ENEMY_RATE));
	}
	else
	{
		if(sti(npchar.money) > CAP_MAX_MONEY || sti(npchar.money) < CAP_MIN_MONEY) 	
		{
			npchar.money = CAP_MIN_MONEY + rand(CAP_NORM);
		}
	}
    //homo 26/06/06
	ProcessCommonDialogRumors(NPChar, Link, Diag);
	switch(Dialog.CurrentNode)
	{
        case "Exit":
			DialogExit();
			Diag.CurrentNode = Diag.TempNode;
		break;
		
		case "First time":
			if (!bDisableMapEnter)
			{
				//--> Jason эскорт 2 уровень
				if (CheckAttribute(PChar, "questTemp.WPU.Escort.LevelUp_1WM") && pchar.questTemp.WPU.Escort == "begin" && NPChar.id == "WMCaptain")
				{
					dialog.text = "Здравствуйте, капитан. Черт возьми, вы даже не представляете, как я рад вас видеть!";
					link.l1 = "Добрый день. Позвольте представиться - " + GetFullName(PChar) + ". Я тоже рад вас видеть в добром здравии, поскольку явился сюда именно с целью разыскать вас и ваш корабль.";
					link.l1.go = "WM_Captain";
					break;
				}
				if (CheckAttribute(PChar, "questTemp.WPU.Escort.LevelUp_1WM") && pchar.questTemp.WPU.Escort == "wait" && NPChar.id == "WMCaptain")
				{
					dialog.text = "Вы доставили материал, который я просил?";
					if (sti(pchar.questTemp.WPU.Escort.Planks) - GetSquadronGoods(pchar, GOOD_PLANKS) <= 0 && sti(pchar.questTemp.WPU.Escort.Sailcloth) - GetSquadronGoods(pchar, GOOD_SAILCLOTH) <= 0 && sti(pchar.questTemp.WPU.Escort.Linen) - GetSquadronGoods(pchar, GOOD_COTTON) <= 0)
					{
						link.l1 = "Да. Все, что нужно для ремонта вашего судна находится у меня в трюмах.";
						link.l1.go = "WM_Captain_5";
					}
					else
					{
						link.l1 = "Нет, я еще работаю над этим.";
						link.l1.go = "exit";
					}
					break;
				}
				if (CheckAttribute(PChar, "questTemp.WPU.Escort.LevelUp_1VSP") && pchar.questTemp.WPU.Escort == "toCap" && NPChar.id == "WMCaptain")
				{
					dialog.text = "Здравствуйте, " + GetAddress_Form(NPChar) + ". Меня зовут " + GetFullName(NPChar) + ", я капитан этого корабля. Хочу вам выразить свою безграничную признательность за помощь в бою с этим проклятым пиратским отродьем - без вашего вмешательства все могло бы закончится для нас весьма плачевно. Вы просто спасли нас, черт возьми!";
					link.l1 = "Не стоит благодарности, " + GetAddress_FormToNPC(NPChar) + ". Позвольте представится - " + GetFullName(PChar) + ", я прибыл к вам на помощь по просьбе начальника портового управления "+XI_ConvertString("Colony"+pchar.questTemp.WPU.Escort.StartCity+"Gen")+". Он вкратце рассказал о злоключениях вашего каравана и отправил меня на розыск вашего судна.";
					link.l1.go = "VSP_Captain";
					break;
				}
				//<-- эскорт 2 уровень
				
				if(CheckAttribute(NPChar, "surrendered"))
				{
					Pchar.GenQuest.MoneyForCaptureShip = makeint(Group_GetLiveCharactersNum( GetGroupIDFromCharacter(NPChar)))*(7 - sti(RealShips[sti(NPChar.Ship.Type)].Class))*(1+rand(10))*500);
					dialog.text = "Стой, так и убить можно. Что ты хочешь от меня?";
					//выкуп
					link.l1 = "Давайте решим все мирно. Выкуп вполне меня устроит. Сумма в "+Pchar.GenQuest.MoneyForCaptureShip+" песо меня вполне устроит, "+GetAddress_FormToNPC(NPChar)+". И после этого можете проваливать отсюда ко всем чертям!!";
					link.l1.go = "surrender1";
					// обираем до нитки
					link.l2 = "Хочу поинтересоваться содержимым твоего трюма. И после этого можешь проваливать ко всем чертям.";
					link.l2.go = "surrender2";
					break;
				}
				
				//Голландский Гамбит, против всех
				if (CheckAttribute(PChar, "questTemp.HWIC.Self") && pchar.questTemp.HWIC.Self == "MeetingStivesant" && NPChar.id == "Stivesant")
				{
					dialog.text = "Здравствуйте, минхер. Рад вас видеть. Капитан Лонгвэй, наверно, поднимется на борт позже?";
					link.l1 = "Добрый день, минхер Стайвесант. Позвольте представиться - " + GetFullName(pchar) + ". Лонгвэй не придет, потому что его нет на 'Мейфенг'.";
					link.l1.go = "Stivesant_1";
					pchar.quest.QuestShipsTerms_Over.over = "yes"; //снять таймер
					break;
				}
				if (CheckAttribute(PChar, "questTemp.HWIC.Self") && pchar.questTemp.HWIC.Self == "FleutOnTrinidad" && NPChar.id == "Keller")
				{
					dialog.text = "Здравствуйте, капитан. Что привело вас на борт моего флейта?";
					link.l1 = "Добрый день, минхер Келлер. Позвольте представиться - " + GetFullName(pchar) + ". Я пришел к вам за помощью в одном необычном деле.";
					link.l1.go = "Keller_1";
					break;
					//Голландский гамбит
				}
                if (CheckAttribute(NPChar, "EncType")  && NPChar.EncType == "war")
                {
    			    Dialog.text = TimeGreeting() + ", "+ GetAddress_Form(NPChar)+"! Я "+ GetFullName(NPChar) +" - капитан корабля флота "+NationKingsName(NPChar)+". Что привело вас ко мне на борт?";
    			}
    			else
                {
    			    Dialog.text = TimeGreeting() + ", "+ GetAddress_Form(NPChar)+"! Я капитан "+ GetFullName(NPChar) +". Что привело вас на борт моего корабля?";
    			}
    			link.l1 = "Меня зовут " + GetFullName(Pchar) + ". У меня есть  к вам дело!";
    			link.l1.go = "quests";
                link.l2 = "Ничего особенного, просто "+ GetSexPhrase("зашел","зашла") +" поприветствовать вас!";
    			link.l2.go = "exit";
            }
            else
            {
                Dialog.text = "Вы заметили, " + GetAddress_Form(NPChar) + ", идет битва? Нам сейчас не до разговоров!";
    			link.l1 = "Вы правы! Вернусь на свой корабль.";
    			link.l1.go = "exit";
            }
			Diag.TempNode = "first time";
 		break;

        case "quests":
            if (!CheckAttribute(NPChar, "MainCaptanId")  || NPChar.MainCaptanId == pchar.GenQuest.CaptainId)
            {
                Dialog.text = "Я вас внимательно слушаю, " + GetAddress_Form(NPChar)+".";
                link.l1 = "Я хотел"+ GetSexPhrase("","а") +" бы узнать последние новости архипелага.";
                //homo 25/06/06
                link.l1.go = "rumours_capitan";
                //
                if (CheckAttribute(NPChar, "EncGroupName")) // только для фантомов грабеж
                {
                    link.l2 = RandPhraseSimple("Вы в курсе, кто я? Думаю, ясно, что мои корабельные орудия могут сделать решето из вашего корыта. Давайте решим все мирно. Выкуп вполне меня устроит.",
                                               "Море... и мы одни... Как насчет того, чтобы в целях вашей безопасности немного задобрить моих ребят?.");
                    link.l2.go = "Talk_board";
                }
                if (CheckAttribute(NPChar, "Ship.Mode") && NPChar.Ship.Mode == "Trade")
                {
	           		link.l3 = "Откуда вы идете?";
	    			link.l3.go = "price_1";
	    			link.l4 = "Поторгуем?";
	    			link.l4.go = "Trade_1";
    			}
				//--> квест мэра, поиски пирата
				if (CheckAttribute(pchar, "GenQuest.DestroyPirate"))
				{
	    			link.l6 = "Я разыскиваю пиратский корабль, орудующий в здешних водах. Вы ничего не видели подозрительного?";
	    			link.l6.go = "MQ_step_1";
				}
				//<-- квест мэра, поиски пирата
    			link.l5 = "Желаете развеяться?";
			    link.l5.go = "Play_Game";
                link.l9 = "Думаю, мне пора!";
    			link.l9.go = "exit";
			}
			else
			{
                Dialog.text = "Я не уполномочен решать дела с вами, обратитесь к командующему нашей эскадры. Его имя " + GetFullName(characterFromID(NPChar.MainCaptanId))+
                              ", он находится на корабле " + XI_ConvertString(RealShips[sti(characters[GetCharacterIndex(NPChar.MainCaptanId)].Ship.Type)].BaseName) + " '" + characters[GetCharacterIndex(NPChar.MainCaptanId)].Ship.Name + "'.";
                link.l1 = "Спасибо. Так и поступлю.";
                link.l1.go = "exit";
                Diag.TempNode = "Go_away_Good";
			}
        break;
        case "Trade_1":
			dialog.text = "Почему бы и нет?";
			link.l1 = "Пойдемте смотреть товары.";
			link.l1.go = "Trade_2";
			link.l2 = "Я передумал"+ GetSexPhrase("","а") +".";
			link.l2.go = "exit";
		break;
		
		case "Trade_2":
			FillShipStore(NPChar);
	    	pchar.shiptrade.character = NPChar.id;
   			Diag.CurrentNode = Diag.TempNode;
		    DialogExit();
		    DeleteAttribute(pchar, "PriceList.StoreManIdx"); // не вести лог по кораблям
		    LaunchStore(SHIP_STORE);
		break;
		
        case "Play_Game":
			dialog.text = "Что вы предлагаете?";
			link.l1 = "Перекинемся в карты на солидный интерес?";
			link.l1.go = "Card_Game";
   			link.l2 = "Погремим костями в покер-джокер?";
			link.l2.go = "Dice_Game";
			link.l10 = "Прошу простить, но меня ждут дела.";
			link.l10.go = "exit";
		break;
        // карты -->
        case "Card_Game":
            if (!CheckNPCQuestDate(npchar, "Card_date_Yet") || isBadReputation(pchar, 30) || GetCharacterSkillToOld(pchar, SKILL_LEADERSHIP) < rand(3))
            {
                SetNPCQuestDate(npchar, "Card_date_Yet");
                dialog.text = "Я не буду играть в азартные игры с разными проходимцами!";
    			link.l1 = "Как вам будет угодно.";
    			link.l1.go = "exit";
			}
			else
			{
                dialog.text = "Давайте! Немного передохну от корабельных дел...";
    			link.l1 = "Замечательно.";
    			link.l1.go = "Cards_begin";
    			link.l2 = "По каким правилам играем?";
    			link.l2.go = "Cards_Rule";
			}
		break;

		case "Cards_Rule":
   			dialog.text = CARDS_RULE;
			link.l1 = "Что ж, давайте начнем!";
			link.l1.go = "Cards_begin";
			link.l3 = "Нет, это не для меня...";
			link.l3.go = "exit";
		break;

		case "Cards_begin":
			Dialog.text = "Давайте определимся со ставкой.";
			link.l1 = "Играем по 100 песо.";
			link.l1.go = "Cards_Node_100";
			link.l2 = "Давайте по 500 песо.";
			link.l2.go = "Cards_Node_500";
			link.l3 = "Пожалуй, мне пора.";
			link.l3.go = "exit";
		break;

		case "Cards_Node_100":
		    if (sti(pchar.Money) < 300)
		    {
                dialog.text = "Шутить изволите? У вас нет денег!";
                link.l1 = "Бывает.";
			    link.l1.go = "exit";
			    break;
		    }
		    if (sti(npchar.Money) < 300)
		    {
                dialog.text = "Хватит с меня, а то на содержание корабля не останется...";
                link.l1 = "Жаль.";
			    link.l1.go = "exit";
			    break;
		    }
   			dialog.text = "Хорошо, играем по 100 монет.";
			link.l1 = "Начали!";
			link.l1.go = "Cards_begin_go";
			pchar.GenQuest.Cards.npcharIdx = npchar.index;
            pchar.GenQuest.Cards.iRate     = 100;
            pchar.GenQuest.Cards.SitType   = false;
		break;

		case "Cards_Node_500":
		    if (sti(pchar.Money) < 1500)
		    {
                dialog.text = "Шутить изволите? У вас нет 1500 песо!";
                link.l1 = "Будут!";
			    link.l1.go = "exit";
			    break;
		    }
		    if (sti(npchar.Money) < 1500)
		    {
                dialog.text = "Нет, такие ставки не доведут до добра.";
                link.l1 = "Как угодно.";
			    link.l1.go = "exit";
			    break;
		    }
   			dialog.text = "Хорошо, играем по 500 монет.";
			link.l1 = "Начали!";
			link.l1.go = "Cards_begin_go";
			pchar.GenQuest.Cards.npcharIdx = npchar.index;
            pchar.GenQuest.Cards.iRate     = 500;
            pchar.GenQuest.Cards.SitType   = false;
		break;

		case "Cards_begin_go":
            Diag.CurrentNode = Diag.TempNode;
			DialogExit();
            LaunchCardsGame();
		break;
	    // карты <--
	    //  Dice -->
        case "Dice_Game":
            if (!CheckNPCQuestDate(npchar, "Dice_date_Yet") || isBadReputation(pchar, 30) || GetCharacterSkillToOld(pchar, SKILL_LEADERSHIP) < rand(3))
            {
                SetNPCQuestDate(npchar, "Dice_date_Yet");
                dialog.text = "Я не буду играть в азартные игры с разными проходимцами!";
    			link.l1 = "Как вам будет угодно.";
    			link.l1.go = "exit";
			}
			else
			{
				if (CheckNPCQuestDate(npchar, "Dice_date_begin"))
				{
					dialog.text = "Давайте! Отдых никогда не вредил здоровью... только кошельку...";
	    			link.l1 = "Замечательно.";
	    			link.l1.go = "Dice_begin";
	    			link.l2 = "По каким правилам игра?";
	    			link.l2.go = "Dice_Rule";
    			}
    			else
    			{
					dialog.text = "Нет, с меня довольно на сегодня. Дела ждут.";
	    			link.l1 = "Как вам будет угодно.";
	    			link.l1.go = "exit";
				}
			}
		break;

		case "Dice_Rule":
   			dialog.text = DICE_RULE;
			link.l1 = "Что ж, давайте начнем!";
			link.l1.go = "Dice_begin";
			link.l3 = "Нет, это не для меня...";
			link.l3.go = "exit";
		break;

		case "Dice_begin":
			Dialog.text = "Давайте определимся со ставкой.";
			link.l1 = "Играем по 50 песо за кубик.";
			link.l1.go = "Dice_Node_100";
			link.l2 = "Давайте по 200 песо за кубик.";
			link.l2.go = "Dice_Node_500";
			link.l3 = "Пожалуй, мне пора.";
			link.l3.go = "exit";
		break;

		case "Dice_Node_100":
            if (!CheckDiceGameSmallRate())
		    {
                dialog.text = "О тебе ходит слава непревзойденн"+ GetSexPhrase("ого шулера","ой каталы") +". Я не буду с тобой играть в кости вообще.";
                link.l1 = "Все врут! Ну и не нужно.";
			    link.l1.go = "exit";
			    break;
		    }

			if (sti(pchar.Money) < 300)
		    {
                dialog.text = "Шутить изволите? У вас нет денег!";
                link.l1 = "Бывает.";
			    link.l1.go = "exit";
			    break;
		    }
		    if (sti(npchar.Money) < 300)
		    {
                dialog.text = "Все! Нужно завязывать с играми, а то запишут в растратчики и спишут на берег...";
                link.l1 = "Жаль.";
			    link.l1.go = "exit";
			    break;
		    }
   			dialog.text = "Хорошо, играем по 50 монет.";
			link.l1 = "Начали!";
			link.l1.go = "Dice_begin_go";
			pchar.GenQuest.Dice.npcharIdx = npchar.index;
            pchar.GenQuest.Dice.iRate     = 50;
            pchar.GenQuest.Dice.SitType   = false;
		break;

		case "Dice_Node_500":
            if (!CheckDiceGameSmallRate())
		    {
                dialog.text = "О тебе ходит слава непревзойденн"+ GetSexPhrase("ого шулера","ой каталы") +". Я не буду с тобой играть в кости вообще.";
                link.l1 = "Все врут! Ну и не нужно.";
			    link.l1.go = "exit";
			    break;
		    }
			if (!CheckDiceGameBigRate())
		    {
                dialog.text = "Я слышал, что ты очень хорошо играешь. Я не буду играть с тобой по таким большим ставкам.";
                link.l1 = "Давайте по более низким ставкам?";
			    link.l1.go = "Dice_Node_100";
				link.l2 = "Извините, мне пора.";
			    link.l2.go = "exit";
			    break;
		    }

			if (sti(pchar.Money) < 1500)
		    {
                dialog.text = "Шутить изволите? У вас нет 1500 песо!";
                link.l1 = "Будут!";
			    link.l1.go = "exit";
			    break;
		    }
		    if (sti(npchar.Money) < 1500)
		    {
                dialog.text = "Нет, такие ставки не доведут до добра.";
                link.l1 = "Как угодно.";
			    link.l1.go = "exit";
			    break;
		    }
   			dialog.text = "Хорошо, играем по 200 монет за кубик.";
			link.l1 = "Начали!";
			link.l1.go = "Dice_begin_go";
			pchar.GenQuest.Dice.npcharIdx = npchar.index;
            pchar.GenQuest.Dice.iRate     = 200;
            pchar.GenQuest.Dice.SitType   = false;
		break;

		case "Dice_begin_go":
            SetNPCQuestDate(npchar, "Dice_date_begin");
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
            LaunchDiceGame();
		break;
	    // Dice <--
        case "price_1":
			if (CheckNPCQuestDate(npchar, "trade_date"))
			{
                SetNPCQuestDate(npchar, "trade_date");
				iMoney = findPriceStoreMan(NPChar);
	            if (iMoney == -1)
	            {
	                Dialog.Text = "Зачем вам это знать? Это мое личное дело.";
					Link.l1 = "Как вам будет угодно.";
					Link.l1.go = "exit";
	            }
	            else
	            {
                    sld = &Characters[iMoney];
                    pchar.PriceList.ShipStoreIdx = iMoney;
                    
					Dialog.Text = "Я иду из города " + GetCityName(sld.City) + ".";
					Link.l1 = "Какие цены на товары в местном магазине?";
					Link.l1.go = "price_2";
					Link.l9 = "Мне уже пора.";
					Link.l9.go = "exit";
				}
			}
			else
			{
                Dialog.Text = "Я же вам все уже сказал. Не беспокойте меня по пустякам.";
				Link.l1 = "Да, вы правы. Прощайте.";
				Link.l1.go = "exit";
            }
		break;
		
		case "price_2":
            sld = &Characters[sti(pchar.PriceList.ShipStoreIdx)];
			SetPriceListByStoreMan(&Colonies[FindColony(sld.City)]);
			Dialog.Text = "Вот такие... (вы получили сводку цен на товары).";
			Link.l1 = "Большое спасибо!";
			Link.l1.go = "exit";
			PlaySound("interface\important_item.wav");
		break;
		
        case "Talk_board":
            if ((Group_GetCharactersNum(NPChar.EncGroupName) - Group_GetDeadCharactersNum(NPChar.EncGroupName)) > GetCompanionQuantity(PChar) && rand(11) > GetCharacterSkillToOld(PChar, SKILL_FORTUNE))
            {
                Dialog.text = "Ха-ха! Хорошая шутка. Тем более, что у меня больше кораблей. Убирайтесь на свой корабль и тоните вместе с ним.";
                link.l1 = "Больше - не значит мощнее...";
                link.l1.go = "Boarding";
            }
            else
            {
                if(rand(21) > (GetSummonSkillFromNameToOld(PChar, SKILL_GRAPPLING) + GetSummonSkillFromNameToOld(PChar, SKILL_LEADERSHIP)) )
                {
                    Dialog.text = "Напрасно вы затеяли свое грязное дело, капитан, на борту моего корабля. Я проявлю милосердие и позволю вам вернуться на свой корабль и утонуть вместе с ним.";
                    link.l1 = "Мы еще посмотрим, кто сегодня пойдет на корм акулам!";
                    link.l1.go = "Boarding";
                }
                else
                {
                    Pchar.GenQuest.MoneyForCaptureShip = makeint(100 + (Group_GetCharactersNum(NPChar.EncGroupName) - Group_GetDeadCharactersNum(NPChar.EncGroupName))*(7 - sti(RealShips[sti(NPChar.Ship.Type)].Class))*(1+rand(10))*500);
                    Dialog.text = RandSwear() + "Да, я наслышан о ваших бесчинствах. Будь по-вашему, но помните " +
                                  XI_ConvertString(NationShortName(sti(NPChar.nation))+"hunter") + " не оставит это безнаказанным!";
                    link.l1 = "Замечательно. Сумма в "+Pchar.GenQuest.MoneyForCaptureShip+" песо меня вполне устроит, "+GetAddress_FormToNPC(NPChar)+".";
                    link.l1.go = "Capture";
                    link.l2 = "Ой. Да ладно. Я пошутил"+ GetSexPhrase("","а") +"!";
                    link.l2.go = "exit";
                }
            }
            // тут нужен учет запрета повторного наезда
            Diag.TempNode = "Go_away";
			sld = characterFromId(pchar.GenQuest.CaptainId);
            sld.talk_date_Go_away =  lastspeakdate(); // boal злопамятность :)
        break;
		
		case "surrender1" :
			Diag.TempNode = "surrender_goaway";
            Dialog.Text = "Получите! А теперь убирайтесь вон!";
			Link.l1 = "Замечательно! И вам не хворать!";
			Link.l1.go = "exit";
			sld = characterFromId(pchar.GenQuest.CaptainId);
            sld.talk_date_Go_away = lastspeakdate();
			AddMoneyToCharacter(pchar, sti(Pchar.GenQuest.MoneyForCaptureShip));
			ChangeCharacterComplexReputation(pchar,"nobility", -2); 		
			ChangeCharacterComplexReputation(pchar,"authority", 1.0); 							
			AddCharacterExpToSkill(pchar, "Leadership", 20);
			ChangeCharacterHunterScore(pchar, NationShortName(sti(NPChar.nation)) + "hunter", 7 + rand(10));
		break;
		
		case "surrender_goaway":
			Dialog.Text = "Ну что вы еще от меня хотите?";
			Link.l1 = "Ничего.";
			Link.l1.go = "exit";
			Diag.TempNode = "surrender_goaway";
		break;
		
		case "surrender2":			
			dialog.text = "Мне не остается ничего другого кроме как подчиниться вам.";
			link.l1 = "Давай, пошевеливайся!";
			link.l1.go = "surrender3";				
		break;
						
		case "surrender3":
			Diag.TempNode = "surrender_goaway";
			sld = characterFromId(pchar.GenQuest.CaptainId);
            sld.talk_date_Go_away = lastspeakdate();
			DialogExit(); 
			LaunchTransferMain(pchar, sld, "Transfer");
		break;
				
        case "rumours":
			Dialog.Text = SelectRumour(); // to_do
			Link.l1 = RandPhraseSimple(RandSwear() + "Это очень интересно. Другой вопрос?",
                                     "Еще одно дело.");
			Link.l1.go = "quests";
			Link.l2 = RandPhraseSimple("Спасибо, должен откланяться.",
                                     "Всего хорошего.");
			Link.l2.go = "exit";
			Diag.TempNode = "quests";
		break;
		
		case "Go_away":
			Dialog.Text = "Убирайтесь с моего корабля!";
			Link.l1 = "Уже ухожу.";
			Link.l1.go = "exit";
			Diag.TempNode = "Go_away";
		break;
		
		case "Go_away_Good":
			Dialog.Text = "Наш разговор уже окончен. Ничего нового я вам не скажу, "+GetAddress_Form(NPChar)+".";
			Link.l1 = "Ясно. До встречи в море!";
			Link.l1.go = "exit";
			Diag.TempNode = "Go_away_Good";
		break;

        case "Capture":
            Diag.TempNode = "Go_away";
            Dialog.Text = "Получите! А теперь убирайтесь вон!";
			Link.l1 = "Замечательно!";
			Link.l1.go = "exit";
			AddMoneyToCharacter(pchar, sti(Pchar.GenQuest.MoneyForCaptureShip));
			ChangeCharacterComplexReputation(pchar,"nobility", -5);			
			AddCharacterExpToSkill(pchar, "Leadership", 20);
			ChangeCharacterHunterScore(pchar, NationShortName(sti(NPChar.nation)) + "hunter", 7 + rand(10));
        break;

        case "Boarding":
            if (CheckAttribute(NPChar, "MainCaptanId"))
            {
                PChar.StartBattleAfterDeck = true;
                PChar.StartBattleMainCaptanId = NPChar.MainCaptanId;
                PChar.StartBattleEncGroupName = NPChar.EncGroupName;
            }
            DialogExit();
            Diag.CurrentNode = Diag.TempNode;
        break;
        
        case "QuestAboardCabinDialog":  // тестовый диалог, в игре не работает, для метода SetQuestAboardCabinDialog
			Diag.TempNode = "QuestAboardCabinDialog";
            Dialog.Text = "Стой, так и убить можно. Что ты хочешь от меня?";
			Link.l1 = "Убить!";
			Link.l1.go = "QuestAboardCabinDialog_1";
			Link.l2 = "Взять в плен.";
			Link.l2.go = "QuestAboardCabinDialog_2";
			Link.l3 = "Отдай нам карту, Билли (c)";  // предмет, далее не ясно или  QuestAboardCabinDialog_1 или QuestAboardCabinDialog_2
			Link.l3.go = "QuestAboardCabinDialog_3";  // можно закодить покидание корабля, но экипаж уже вырезан и тп...
        break;
        
        case "QuestAboardCabinDialog_1":
			Dialog.Text = "Ну, это мы еще посмотрим!";
			Link.l1 = "А что тут смотреть?";
			Link.l1.go = "exit";
			// тут можно восстановить НР противника (NPChar) или добавить парочку гардов против ГГ
			LAi_SetCurHPMax(NPChar);
			AddDialogExitQuestFunction("QuestAboardCabinDialogExitWithBattle"); // тут ругань обратно
		break;
		
		case "QuestAboardCabinDialog_2":
			Dialog.Text = "Хорошо, твоя взяла!";
			Link.l1 = "Так бы сразу!";
			Link.l1.go = "exit";
			AddDialogExitQuestFunction("QuestAboardCabinDialogSurrender");
		break;
		
		case "QuestAboardCabinDialog_3":
			Dialog.Text = "Да забирай!";
			Link.l1 = "Вот и хорошо, теперь сдавайся в плен.";
			if (rand(1) == 1)  // пример!!!
			{
				Link.l1.go = "QuestAboardCabinDialog_2";
			}
			else
			{
			    Link.l1.go = "QuestAboardCabinDialog_3_1";
			}
			TakeNItems(NPChar, "Chest", -1);
			TakeNItems(pchar, "Chest", 1);
		break;
		
		case "QuestAboardCabinDialog_3_1":
			Dialog.Text = ""+ GetSexPhrase("Пришел","Пришла") +", наследил"+ GetSexPhrase("","а") +", все отнял"+ GetSexPhrase("","а") +" и еще меня в рабы? Фиг!";
			Link.l1 = "Тогда тапки белые готовь.";
			Link.l1.go = "QuestAboardCabinDialog_1";
		break;
		//eddy. квест мэра, поиски пирата
		case "MQ_step_1":
			Dialog.Text = "Нет, никакого подозрительного корабля, похожего на пиратский, я не видел.";
			Link.l1 = "Понятно.";
			Link.l1.go = "exit";
		break;
		
		//homo Наводка на купца
		case "MerchantTrap_Abordage":

			Dialog.Text = "Именем "+NationKingsName(NPChar)+" сдавайся, "+ GetSexPhrase("подлый пират","подлая злодейка") +"! И тебе сохранят жизнь до справедливого суда, где ты ответишь, за все "+NationNameSK(sti(NPChar.nation))+"ие корабли, которые ты ограбил"+ GetSexPhrase("","а") +".";
			Link.l1 = "Как бы не так - сам сдавайся.";
			Link.l1.go = "exit";
			LAi_SetCurHPMax(NPChar);
			AddDialogExitQuestFunction("QuestAboardCabinDialogExitWithBattleNoParam"); // тут ругань обратно
		break;
		
		case "Siegehelp":		
            ref rchar = Group_GetGroupCommander(sGroup);
            if (NPChar.id == rchar.id)
            {
    			
    			dialog.text = "Я вас слушаю, но давайте поскорее выкладывайте цель вашего визита, у нас идет бой с " + fort +
                          " и мне нужно руководить ходом сражения.";
                link.l1 = "Именно поэтому я здесь, " + GetAddress_FormToNPC(NPChar) + ".";
                link.l1.go = "attack_fort";

                link.l2 = "В таком случае не буду вас больше задерживать. Прощайте, "+ GetAddress_FormToNPC(NPChar) + ".";
                link.l2.go = "exit";
    			
            }
            else
            {
                Dialog.text = "Я не уполномочен решать дела с вами, обратитесь к командующему нашей эскадры. Его имя " + GetFullName(rchar)+
                              ", он находится на корабле " + XI_ConvertString(RealShips[sti(rchar.Ship.Type)].BaseName) + " ''" + rchar.Ship.Name + "''.";
                link.l1 = "Спасибо. Так и поступлю.";
                link.l1.go = "exit";
            
            }
            Diag.TempNode = "Siegehelp";
            
		break;
		
		case "attack_fort":
                dialog.text = "И о чем же идет речь?";
                link.l1 = "Я могу помочь вам разгромить форт колонии " +GetConvertStr(aData.Colony+" Town", "LocLables.txt")+ " и захватить город, а добычу, полученную в случае нашего успеха, мы поделим между собой.";
                link.l1.go = "Siegehelp_1";
                link.l2 = "Собственно, мое дело вряд ли заслуживает вашего внимания. Прощайте, "+ GetAddress_FormToNPC(NPChar) + ".";
                link.l2.go = "exit";
                Diag.TempNode = "Siegehelp_0";
		break;
		
		case "Siegehelp_0":
            Dialog.text = "Это опять вы? Мне казалось, мы все уже обсудили?";
            link.l1 = "Вы правы - забыл"+ GetSexPhrase("","а") +".";
			link.l1.go = "exit";
			NPChar.DeckDialogNode = "Siegehelp_0";
            Diag.TempNode = "Siegehelp_0";

		break;
		
		case "Siegehelp_1":
            SiegeResult("");
            if (sti(aData.win)==0)
            {
                dialog.text = "И какую же часть добычи вы рассчитываете получить?";
                link.l1 = "Половину.";
                link.l1.go = "Big_part";
                link.l2 = "Одну треть.";
                link.l2.go = "Middle_part";
                link.l3 = "Четвертую часть.";
                link.l3.go = "Small_part";
            }
            else
            {
                dialog.text = "Мне не требуются ваши услуги, капитан! Я не нуждаюсь ни в чьей помощи, так как в любом случае захвачу эту колонию.";
                link.l1 = "Откуда такая уверенность, " + GetAddress_FormToNPC(NPChar) + ", неудачи могут постигнуть любого.";
                link.l1.go = "attack_fort_03";
                link.l2 = "В таком случае не буду вас больше задерживать, " + GetAddress_FormToNPC(NPChar) + ". Прощайте!";
                link.l2.go = "exit";
            }
			Diag.TempNode = "Siegehelp_0";

		break;
		
		case "attack_fort_03":
            if((sti(aData.iSquadronPower)*SquadronDamage - (ifortPower)*fortDamage) < 4000)
            {
                dialog.text = "С другой стороны, мои корабли уже изрядно потрепаны в этом сражении, и подкрепление нам бы не помешало. Если вы согласны на " + GetPart(4) + ", то, я думаю, мы сможем договориться.";
                link.l1 = "Меня это устраивает, " + GetAddress_FormToNPC(NPChar) + ". Я попытаюсь взять форт штурмом, а вы со своей стороны поддержите нас огнем корабельных орудий.";
                link.l1.go = "attack_fort_04";
                aData.PartAttaksFort = 4;
                link.l2 = "Я стою не так дешево, " + GetAddress_FormToNPC(NPChar) + ". Прошу прощения, что оторвал"+ GetSexPhrase("","а") +" вас от насущных дел. Прощайте.";
                link.l2.go = "exit";
            }else{
                dialog.text = "В моей эскадре достаточно кораблей, чтобы разнести этот форт в пух и прах, это только вопрос времени. А теперь соизвольте покинуть мой корабль, впереди меня ожидает победа!";
                link.l1 = "Ну что ж, в таком случае, " + GetAddress_FormToNPC(NPChar) + ", позвольте откланяться. Прощайте!";
                link.l1.go = "exit";
            }
		    Diag.TempNode = "Siegehelp_0";
		break;
		case "Big_part":
            if( (sti(aData.iSquadronPower)*SquadronDamage - (ifortPower)*fortDamage) <= -1500)
            {
                dialog.text = "Орудия форта сильно повредили корабли моей эскадры, и исход этого сражения может обернуться не в нашу пользу. Я согласен на ваши условия и принимаю вашу помощь.";
                link.l1 = "Отлично, " + GetAddress_FormToNPC(NPChar) + ", в таком случае мы возьмем форт штурмом, а вы уж поддержите нас огнем корабельных пушек.";
                link.l1.go = "attack_fort_04";
                aData.PartAttaksFort = 2;
            }
            else
            {
                dialog.text = "Не многовато ли, капитан? У вас " + GetNumShips(GetCompanionQuantity(PChar)) +
                              ", в моей эскадре " + GetNumShips(Group_GetCharactersNum(sGroup)) + ". Я могу вам предложить " + GetPart(4) +
                              ". И я думаю, это правильно.";
                aData.PartAttaksFort = 4;
                link.l1 = "Я соглас"+ GetSexPhrase("ен","на") +", " + GetAddress_FormToNPC(NPChar) + ", в таком случае, я беру на себя захват форта, а вы уж поддержите нас огнем корабельных орудий.";
                link.l1.go = "attack_fort_04";
                link.l2 = "К сожалению, я так не думаю, " + GetAddress_FormToNPC(NPChar) + ". Нам больше не о чем разговаривать. Прощайте.";
                link.l2.go = "exit";
            }
            Diag.TempNode = "Siegehelp_0";
        break;
        
        case "attack_fort_04":
            dialog.text = "Как только форт будет захвачен, мы немедленно начинаем высадку десантных групп на берег, а дальше уже продолжим бой в самом городе, где, я надеюсь, мы и встретимся с вами.";
            link.l1 = "На этом и порешим. До встречи, " + GetAddress_FormToNPC(NPChar) + "!";
            link.l1.go = "exit";
            Diag.TempNode = "Siegehelp_0";
            PChar.quest.Union_with_Escadra = "Yes";
        break;

        case "Middle_part":
            if((sti(aData.iSquadronPower)*SquadronDamage - (ifortPower)*fortDamage) <= -600)
            {
                dialog.text = "Пожалуй, я соглашусь на ваши условия. Совместная операция увеличивает мои шансы на благополучный исход этого сражения. В случае успешного завершения дела вы получите свою часть добычи.";
                link.l1 = "Ну вот и славно, что мы договорились, " + GetAddress_FormToNPC(NPChar) + ". Я немедленно отдам приказ своим людям атаковать форт.";
                link.l1.go = "attack_fort_04";
                aData.PartAttaksFort = 3;
            }else{
                dialog.text = "Не многовато ли, капитан? У вас " + GetNumShips(GetCompanionQuantity(PChar)) + ", в моей эскадре " + GetNumShips(Group_GetCharactersNum(sGroup)) + ". Я могу вам предложить " + GetPart(4) + ". И я думаю, это правильно.";
                link.l1 = "Я "+ GetSexPhrase("согласен","согласна") +", " + GetAddress_FormToNPC(NPChar) + ", в таком случае я беру на себя штурм форта, а вы поддержите нас огнем корабельных орудий.";
                link.l1.go = "attack_fort_04";
                aData.PartAttaksFort = 4;
                link.l2 = "К сожалению, я так не думаю, " + GetAddress_FormToNPC(NPChar) + ". Нам больше не о чем разговаривать. Прощайте.";
                link.l2.go = "exit";
            }
            Diag.TempNode = "Siegehelp_0";
        break;

        case "Small_part":
            dialog.text = "Корабли моей эскадры измотаны сражением, так что свежие силы нам не помешают. Я согласен на эти условия и принимаю ваше предложение.";
            link.l1 = "Я рад"+ GetSexPhrase("","а") +", что мы смогли договориться, " + GetAddress_FormToNPC(NPChar) + ". Я немедленно отдам приказ своим людям вступить в бой и начать атаку форта.";
            link.l1.go = "attack_fort_04";
            aData.PartAttaksFort = 4;
            Diag.TempNode = "Siegehelp_0";
        break;
		
		case "Talk_Capture_City":
            AfterTownBattle();  // все, все свободны
            LAi_LoginInCaptureTown(NPChar, false);
            aData.win = 1;
            EndOfTheSiege("End");
            NPChar.location = "";
            int ilt = makeint(sti(aData.loot)/sti(aData.PartAttaksFort));
            dialog.text = "Здравствуйте, капитан! Хоть битва и была жаркой, но все-таки нам удалось сломить яростное сопротивление защитников города. Добыча составляет " + sti(aData.loot)+
                          " песо. И по нашему договору вы получаете "+ilt+
                          ". Вот ваши деньги, вы их, несомненно, заслужили. А теперь прошу меня извинить, но меня ждут дела.";
            link.l1 = "В таком случае позвольте откланяться, " + GetAddress_FormToNPC(NPChar) + ". Прощайте!";
            link.l1.go = "exit";
            //AddDialogExitQuest("End_Siege_and_Attaks_City");

            Diag.TempNode = "no_return_02";
            AddMoneyToCharacter(PChar, ilt);
            ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 20);
            ChangeCharacterComplexReputation(PChar,"nobility", 10);
            AddCharacterExpToSkill(GetMainCharacter(), "Leadership", 80);
            AddCharacterExpToSkill(GetMainCharacter(), "Sailing", 100);
            AddCharacterExpToSkill(GetMainCharacter(), "Defence", 100);
            AddCharacterExpToSkill(GetMainCharacter(), "Accuracy", 100);
            AddCharacterExpToSkill(GetMainCharacter(), "Cannons", 100);
            AddCharacterExpToSkill(GetMainCharacter(), "Fortune", 80);
            aData.loot = sti(aData.loot) - ilt;
            if (CheckAttribute(PChar, "quest.LeaveTown")) Pchar.quest.LeaveTown.over = "yes";
            //--> слухи
            SiegeRumour("Прошел слух, что вы помогли нашей эскадре при штурме "+NationNameSK(sti(aData.conation))+"ой колонии - "+GetConvertStr(aData.Colony+" Town", "LocLables.txt")+"! Мы так благодарны вам, "+ GetAddress_Form(NPChar)+".", "", sti(aData.nation), -1, 30, 3);
            //<-- слухи
		break;

        case "no_return_02":
            dialog.text = "Приветствую вас, капитан! У вас ко мне дело?";
            link.l1 = "Никаких, " + GetAddress_FormToNPC(NPChar) + ". Прощайте!";
            link.l1.go = "exit";
            Diag.TempNode = "no_return_02";
		break;
		
		case "GoldSquadron":
            ref rch = Group_GetGroupCommander("Sea_Head_of_Gold_Squadron");
            if (NPChar.id == rch.id)
            {
    			dialog.text = "Я вас слушаю, но давайте поскорее выкладывайте цель вашего визита, я очень спешу. На меня возложена важная миссия секретного характера, и к тому же мне предписано топить все подозрительные корабли в открытом море, которые могут представлять опасность нашему конвою.";                          
                link.l1 = "В таком случае не буду вас больше задерживать. Прощайте, "+ GetAddress_FormToNPC(NPChar) + ".";
                link.l1.go = "exit";

            }
            else
            {
                Dialog.text = "Я не уполномочен решать дела с вами, обратитесь к командующему нашей эскадры. Его имя " + GetFullName(rch)+
                              ", он находится на корабле " + XI_ConvertString(RealShips[sti(rch.Ship.Type)].BaseName) + " ''" + rch.Ship.Name + "''.";
                link.l1 = "Спасибо. Так и поступлю.";
                link.l1.go = "exit";

            }
            Diag.TempNode = "GoldSquadron";
		break;
		
		case "WM_Captain":
			dialog.text = "Приятно познакомиться, а меня зовут " + GetFullName(npchar) + ". Так вы пришли мне на помощь? О, тогда я вдвойне рад, ибо положение у нас действительно критическое - одни у берегов необитаемого острова, корабль едва на плаву, огромные потери в команде...";
			link.l1 = "Как я слышал, вам пришлось выдержать бой с пиратами, а затем еще и шторм...";
			link.l1.go = "WM_Captain_1";
			pchar.quest.DesIsland_Over.over = "yes";//снять прерывание
		break;
		
		case "WM_Captain_1":
			dialog.text = "Все верно. Мой корабль сильно пострадал в бою - нам даже пришлось отбивать абордажную атаку этих нехристей. А потом налетел шквал... ох, даже вспоминать об этом не хочу. Нас вынесло к этому негостеприимному берегу - мы целый день в шторм стояли на якорях, и молили Пресвятую Деву, чтобы цепи выдержали\nИ вот мы здесь. Мы уже неделю чиним наш корабль, но - сами видите: команды осталось чуть больше полусотни человек, для починки нужны доски - а где их взять? Только в джунглях. Мы целыми днями работаем, и не заготовили еще и пятой части нужного количества материала\nА отправится в путь с такими повреждениями - равносильно самоубийству. Так и живем, капитан...";
			link.l1 = "М-да... Положение незавидное. Давайте подумаем, что можно предпринять, и как я могу вам помочь.";
			link.l1.go = "WM_Captain_2";
		break;
		
		case "WM_Captain_2":
			dialog.text = "Эх, если бы у нас были доски и парусина в необходимом количестве - мы бы за неделю отремонтировали судно - было бы как новенькое\nКапитан, раз вы специально пришли мне на выручку - не могли бы ли вы отправиться в ближайший порт, закупить необходимого материала для починки и привезти сюда? Таким образом, проблема была бы решена. Финансовая сторона пусть вас не волнует - я компенсирую все ваши затраты на покупку.";
			link.l1 = "Безусловно. Сколько и чего вам нужно доставить?";
			link.l1.go = "WM_Captain_3";
		break;
		
		case "WM_Captain_3":
			pchar.questTemp.WPU.Escort.Planks = 300 + drand(5)*10;
			pchar.questTemp.WPU.Escort.Sailcloth = 150 + drand(10)*10;
			pchar.questTemp.WPU.Escort.Linen = 70 + drand(7)*10;
			dialog.text = "Я уже давно все посчитал. С учетом заготовленного, мне необходимо "+FindRussianQtyString(sti(pchar.questTemp.WPU.Escort.Planks))+" досок, "+FindRussianQtyString(sti(pchar.questTemp.WPU.Escort.Sailcloth))+" парусины и "+FindRussianQtyString(sti(pchar.questTemp.WPU.Escort.Linen))+" хлопка. Имея этот набор, мы бы в недельный срок управились с починкой и вышли в море.";
			link.l1 = "Хорошо. Я доставлю вам необходимые материалы. Ждите меня, я вернусь не позже, чем через десять дней.";
			link.l1.go = "WM_Captain_4";
		break;
		
		case "WM_Captain_4":
			dialog.text = "Огромное спасибо, капитан! Фух, камень с души свалился. Мы будем ждать вас и молиться о вашем скорейшем возвращении!";
			link.l1 = "Не переживайте. Скоро у вас будет всё необходимое для ремонта.";
			link.l1.go = "exit";
			AddQuestRecord("Escort", "27");
			AddQuestUserData("Escort", "sSName", pchar.questTemp.WPU.Escort.ShipName);
			AddQuestUserData("Escort", "sIsland", XI_ConvertString("Colony"+pchar.questTemp.WPU.Current.TargetIslandID));
			AddQuestUserData("Escort", "sQty1", FindRussianQtyString(sti(pchar.questTemp.WPU.Escort.Planks)));
			AddQuestUserData("Escort", "sQty2", FindRussianQtyString(sti(pchar.questTemp.WPU.Escort.Sailcloth)));
			AddQuestUserData("Escort", "sQty3", FindRussianQtyString(sti(pchar.questTemp.WPU.Escort.Linen)));
			Diag.TempNode = "WM_Captain_again";
			SetFunctionTimerCondition("WM_Captain_Over", 0, 0, 11, false);
			pchar.questTemp.WPU.Escort = "wait";
		break;
		
		case "WM_Captain_again":
			dialog.text = "Мы будем с нетерпением ожидать вашего возвращения, капитан!";
			link.l1 = "Уже поднимаю якоря!";
			link.l1.go = "exit";
			Diag.TempNode = "WM_Captain_again";
		break;
		
		case "WM_Captain_5":
			dialog.text = "Превосходно! Тогда мы можем приступать к ремонту судна!";
			link.l1 = "Мои люди вам помогут - так мы быстрее справимся. Кроме того, я должен вас сопроводить до колонии "+XI_ConvertString("Colony"+pchar.questTemp.WPU.Escort.StartCity)+", так что чем быстрее мы починимся - тем лучше для меня.";
			link.l1.go = "WM_Captain_6";
		break;
		
		case "WM_Captain_6":
			pchar.questTemp.WPU.Current.TargetIslandID.Shore = SelectQuestShoreLocationFromSea(pchar.questTemp.WPU.Current.TargetIslandID);
			dialog.text = "Ох, даже и не знаю, как мне вас благодарить, капитан... Прикажите сгрузить материалы в бухте под названием " + XI_ConvertString(pchar.questTemp.WPU.Current.TargetIslandID.Shore) + " - мы там все подготовили для ремонта.";
			link.l1 = "Хорошо. Встретимся на берегу.";
			link.l1.go = "exit";
			AddQuestRecord("Escort", "29");
			AddQuestUserData("Escort", "sShore", XI_ConvertString(pchar.questTemp.WPU.Current.TargetIslandID.Shore+"Gen"));
			pchar.quest.DisasterShip_WMC.win_condition.l1 = "location";
			pchar.quest.DisasterShip_WMC.win_condition.l1.location = pchar.questTemp.WPU.Current.TargetIslandID.Shore;
			pchar.quest.DisasterShip_WMC.function = "RepairShip_Prepare";
			Diag.TempNode = "WM_Captain_repeat";
		break;
		
		case "WM_Captain_repeat":
			dialog.text = "Приступаем к ремонту, капитан? Жду вас на берегу.";
			link.l1 = "Да, конечно. Уже отправляюсь.";
			link.l1.go = "exit";
			Diag.TempNode = "WM_Captain_repeat";
		break;
		
		case "Repair_start":
			dialog.text = "Ну вот, все готово к проведению ремонтных работ. Думаю, дней за пять управимся.";
			link.l1 = "Вот и отлично! Я давно хотел получше исследовать этот остров, так что время не пропадет даром.";
			link.l1.go = "Repair_start_1";
		break;
		
		case "Repair_start_1":
			DialogExit();
			pchar.quest.WM_Captain_Over.over = "yes";//снять прерывание
			sld = characterFromId("WMCaptain");
			LAi_SetImmortal(sld, false);
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "reload1_back", "none", "", "", "", 5.0);
			RemoveCharacterGoods(pchar, GOOD_PLANKS, sti(pchar.questTemp.WPU.Escort.Planks));
			RemoveCharacterGoods(pchar, GOOD_SAILCLOTH, sti(pchar.questTemp.WPU.Escort.Sailcloth));
			RemoveCharacterGoods(pchar, GOOD_COTTON, sti(pchar.questTemp.WPU.Escort.Linen));
			DoQuestFunctionDelay("RepairShip_WithoutMasts", 5.0);
		break;
		
		case "Repair_end":
			dialog.text = "Вот и все. Починка окончена, мой корабль готов к выходу в море. Когда отправляемся, капитан?";
			link.l1 = "Если вы готовы, то задерживаться более смысла я не вижу. Поднимаем якоря!";
			link.l1.go = "Repair_end_1";
		break;
		
		case "Repair_end_1":
			DialogExit();
			sld = characterFromId("WMCaptain");
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "reload1_back", "none", "", "", "OpenTheDoors", 5.0);
			AddQuestRecord("Escort", "30");
			AddQuestUserData("Escort", "sSName", pchar.questTemp.WPU.Escort.ShipName);
			AddQuestUserData("Escort", "sStartCity", XI_ConvertString("Colony"+pchar.questTemp.WPU.Escort.StartCity));
			SetFunctionTimerCondition("DisasterShipWM_Over", 0, 0, 25, false);
			log_info("У вас 25 дней, чтобы отконвоировать "+pchar.questTemp.WPU.Escort.ShipBaseName+" '"+pchar.questTemp.WPU.Escort.ShipName+"' в порт "+XI_ConvertString("Colony"+pchar.questTemp.WPU.Escort.StartCity+"Gen")+"");
			pchar.quest.DisasterShip_final.win_condition.l1 = "location";
			pchar.quest.DisasterShip_final.win_condition.l1.location = pchar.questTemp.WPU.Escort.StartCity +"_town";
			pchar.quest.DisasterShip_final.function = "WMShip_final";
		break;
		
		case "WMShip_final":
			pchar.quest.Escort_fail.over = "yes";
			pchar.quest.DisasterShipWM_Over.over = "yes";//снимаем оба прерывания
			RemoveCharacterCompanion(Pchar, characterFromID("WMCaptain"));//удаляем компаньона
			pchar.questTemp.WPU.Escort.LevelUp_1Money = sti(pchar.questTemp.WPU.Escort.Planks)*15+sti(pchar.questTemp.WPU.Escort.Sailcloth)*9+sti(pchar.questTemp.WPU.Escort.Linen)*45;//деньги за материалы
			dialog.text = "Хочу еще раз вас поблагодарить, капитан, за то, что вытащили меня и мою команду из этой передряги. Как я и обещал - я компенсирую ваши затраты на материалы для починки моего судна. Здесь "+FindRussianMoneyString(sti(pchar.questTemp.WPU.Escort.LevelUp_1Money))+", возьмите, пожалуйста. И еще вот этот подарок лично от меня.";
			link.l1 = "Рад был помочь вам.";
			link.l1.go = "WMShip_final_1";
		break;
		
		case "WMShip_final_1":
			AddMoneyToCharacter(pchar, sti(pchar.questTemp.WPU.Escort.LevelUp_1Money));
			TakeNItems(pchar, "obereg_"+(drand(10)+1), 1);
			dialog.text = "Ну, а теперь нам пора проститься, капитан. Не забудьте зайти в портовое управление - там вас уже ждут. До свидания!";
			link.l1 = "Всего доброго, " + npchar.name + "!";
			link.l1.go = "WMShip_final_2";
		break;
		
		case "WMShip_final_2":
			chrDisableReloadToLocation = false;
			bDisableFastReload = false;
			DialogExit();
			sld = characterFromId("WMCaptain");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload1_back", "none", "", "", "", 5.0);
			if (CheckAttribute(PChar, "questTemp.WPU.Escort.LevelUp_1WM")) AddQuestRecord("Escort", "31");
			if (CheckAttribute(PChar, "questTemp.WPU.Escort.LevelUp_1VSP")) AddQuestRecord("Escort", "37");
			if (CheckAttribute(PChar, "questTemp.WPU.Escort.LevelUp_1S")) AddQuestRecord("Escort", "40");
			AddQuestUserData("Escort", "sMoney", FindRussianMoneyString(sti(pchar.questTemp.WPU.Escort.LevelUp_1Money)));
			AddQuestUserData("Escort", "sStartCity", XI_ConvertString("Colony"+pchar.questTemp.WPU.Escort.StartCity+"Gen"));
			AddQuestUserData("Escort", "sSName", pchar.questTemp.WPU.Escort.ShipName);
		break;
		
		case "VSP_Captain":
			dialog.text = "Вот как! А я думал, что про нас все забыли. Да, моему кораблю не повезло больше всех. После того, как шторм вынудил пиратов перкратить атаку каравана, мы сутки боролись с разбушевавшейся стихией. Нас вынесло к этому негостеприимному берегу\nМы несколько дней отдыхали, чинили корабль, поврежденный бурей, уже собирались выйти в море, как на нас снова напали эти богоотступники. Очевидно, они все это время были на другой стороне острова\nА потом опять налетел шторм - мы уже решили, что Господь окончательно прогневался на нас и готовились к худшему. Но тут появились вы, слава Пресвятой деве Марии! Спасибо вам еще раз, капитан!";
			link.l1 = "Все уже позади, " + GetAddress_FormToNPC(NPChar) + ". Теперь я должен сопроводить вас до "+XI_ConvertString("Colony"+pchar.questTemp.WPU.Escort.StartCity+"Gen")+", дабы уберечь от иных возможных бед. Вы готовы отправиться в путь немедленно? Шторм уже пошел на убыль.";
			link.l1.go = "VSP_Captain_1";
		break;
		
		case "VSP_Captain_1":
			dialog.text = "Конечно! Чем быстрее мы покинем эти места, тем спокойнее будет моя истрадавшаяся команда. Отправляемся!";
			link.l1 = "Следуйте за моим кораблем. И успокойте вашу команду - более вам ничего не угрожает.";
			link.l1.go = "VSP_Captain_2";
		break;
		
		case "VSP_Captain_2":
			pchar.quest.DisasterShip_GetOut.over = "yes";
			DialogExit();
			Group_DelCharacter("WMShip", "WMCaptain");//иначе будет клон
			sld = characterFromId("WMCaptain");
			LAi_SetImmortal(sld, false);
			SetCharacterRemovable(sld, false);
			sld.CompanionEnemyEnable = false; //всегда друзья
			SetCompanionIndex(pchar, -1, sti(sld.index));
			sld.loyality = MAX_LOYALITY;
			AddQuestRecord("Escort", "36");
			AddQuestUserData("Escort", "sSName", pchar.questTemp.WPU.Escort.ShipName);
			SetFunctionTimerCondition("DisasterShipWM_Over", 0, 0, 25, false);
			log_info("У вас 25 дней, чтобы отконвоировать "+pchar.questTemp.WPU.Escort.ShipBaseName+" '"+pchar.questTemp.WPU.Escort.ShipName+"' в порт "+XI_ConvertString("Colony"+pchar.questTemp.WPU.Escort.StartCity+"Gen")+"");
			pchar.questTemp.WPU.Escort = "win";
			pchar.quest.Escort_fail.win_condition.l1 = "NPC_Death";//прерывание на потопление сопровождаемого
			pchar.quest.Escort_fail.win_condition.l1.character = "WMCaptain";
			pchar.quest.Escort_fail.function = "DisasterShipWM_failed";
			pchar.quest.DisasterShip_final.win_condition.l1 = "location";
			pchar.quest.DisasterShip_final.win_condition.l1.location = pchar.questTemp.WPU.Escort.StartCity +"_town";
			pchar.quest.DisasterShip_final.function = "WMShip_final";
			Diag.currentnode = "VSP_Captain_again";
			Delete_EscortStorm();//уберем шторм
		break;
		
		case "VSP_Captain_again":
			dialog.text = "Отправляемся в путь, капитан?";
			link.l1 = "Да, конечно. Я уже возвращаюсь на свой корабль.";
			link.l1.go = "exit";
			Diag.TempNode = "VSP_Captain_again";
		break;
		
		case "VSPShip_final":
			pchar.quest.Escort_fail.over = "yes";
			pchar.quest.DisasterShipWM_Over.over = "yes";//снимаем оба прерывания
			RemoveCharacterCompanion(Pchar, characterFromID("WMCaptain"));//удаляем компаньона
			pchar.questTemp.WPU.Escort.LevelUp_1Money = 10000+sti(pchar.rank)*200;
			dialog.text = "Хочу еще раз вас поблагодарить, капитан, за то, что вытащили меня и мою команду из этой передряги. Здесь "+FindRussianMoneyString(sti(pchar.questTemp.WPU.Escort.LevelUp_1Money))+". Мы собрали это всей командой для вас, возьмите, пожалуйста, и не вздумайте отказываться. И еще вот этот подарок лично от меня.";
			link.l1 = "Рад был помочь вам!";
			link.l1.go = "WMShip_final_1";
		break;
		
		case "SShip_final":
			pchar.questTemp.WPU.Escort.LevelUp_1Money = 5000+sti(pchar.rank)*100;
			RemovePassenger(Pchar, npchar);//удаляем пассажира
			dialog.text = "Хочу еще раз вас поблагодарить, капитан, за то, что вытащили меня и мою команду из этой передряги. Примите от меня эти деньги - "+FindRussianMoneyString(sti(pchar.questTemp.WPU.Escort.LevelUp_1Money))+", еще вот этот подарок. Это немного, но это всё, чем я могу отблагодарить вас за свое спасение. И прошу вас не отказываться\nМоя бывшая команда восхищена вами - как вы дрались на берегу с индейцами, и как расправились с пиратским кораблем. Все они хотят остаться у вас на службе. Надеюсь, вы не откажете морякам, потерявшим свое судно, в их маленькой просьбе - служить вам верой и правдой?";
			link.l1 = "Нет, конечно. Я с удовольствием оставлю их в своей команде. Рад был помочь вам!";
			link.l1.go = "WMShip_final_1";
		break;
		
		//Голландский Гамбит
		case "Stivesant_1":
			dialog.text = "Так. Но тогда извольте объясниться, минхер, что здесь происходит? Почему 'Мейфенг' оказалась под вашим командованием? С Лонгвэем случилось несчастье?";
			link.l1 = "У меня есть все исчерпывающие объяснения. Кроме того, у меня важная информация для вас.";
			link.l1.go = "Stivesant_2";			
		break;
		
		case "Stivesant_2":
			dialog.text = "Тогда я вас внимательно слушаю.";
			link.l1 = "В Виллемстаде совершен переворот. Лукас Роденбург занял место губернатора, Матиас Бек посажен им в тюрьму на основании абсурдного подозрения в связи с английской разведкой.";
			link.l1.go = "Stivesant_3";			
		break;
		
		case "Stivesant_3":
			dialog.text = "Хм... Минхер, вы рассказываете удивительные вещи. Я не так давно получал новости из Виллемстада, и ни о чем подобном в них не говорилось.";
			link.l1 = "Выслушайте меня до конца, минхер Стайвесант. Новости вы наверняка получили через посредничество Роденбурга, а он уверен, что вы до Кюрасао не дойдете.";
			link.l1.go = "Stivesant_4";			
		break;
		
		case "Stivesant_4":
			dialog.text = "Сударь, ваши слова мне нравятся все меньше и меньше. Кто вы вообще такой?";
			link.l1 = "Я просто капитан и просто человек, которому небезразлична судьба голландских колонистов. Лукас Роденбург отдал приказ Лонгвэю уничтожить ваш корабль, и вас в живых тоже не оставлять. Пользуясь тем, что 'Мейфенг' не вызвала бы у вас подозрений, он сумел бы это сделать без особого труда.";
			link.l1.go = "Stivesant_5";			
		break;
		
		case "Stivesant_5":
			dialog.text = "Значит вы хотите сказать, что Лукас...";
			link.l1 = "Решил сместить вас с поста директора Компании самым простым способом - путем физического устранения. Кроме вас, нет более человека в регионе, способного оказать сколь бы то ни было значительное сопротивление влиянию Роденбурга на Архипелаге.";
			link.l1.go = "Stivesant_6";			
		break;
		
		case "Stivesant_6":
			dialog.text = "Ушам не верю!";
			link.l1 = "Я не поверил в связь Бека с английской разведкой и предпринял расследование. Узнав, что 'Мейфенг', груженая под завязку отборными головорезами, вышла в направлении Филипсбурга, я догнал ее и дал бой. Захватив в плен Лонгвэя, я получил от него всю эту информацию, в том числе и где вас искать.";
			link.l1.go = "Stivesant_7";			
		break;
		
		case "Stivesant_7":
			dialog.text = "Хм... Похоже на правду. Никто, кроме Роденбурга, не знал и не мог знать ни о времени, ни о маршруте следования моего галеона! Проклятие! Это измена! Где Лонгвэй?!";
			link.l1 = "Я отпустил его в обмен на чистосердечное признание. Надо сказать, он не горел желанием выполнять приказ Роденбурга, но не повиноваться тоже не мог. Он сказал, что на службу к Роденбургу более не вернется - последнее грязное поручение переполнило чашу его терпения.";
			link.l1.go = "Stivesant_8";			
		break;
		
		case "Stivesant_8":
			dialog.text = "Так... Капитан " + GetFullName(pchar) + ", вы отправитесь со мной в Виллемстад. Становитесь на 'Мейфенг' впереди моего корабля. Если все это правда, что вы сказали - Лукас должен быть арестован, и вы окажете в этом содействие. Но если вы мне солгали... пеняйте на себя.";
			link.l1 = "Мне нет смысла лгать вам, минхер. Поторопимся в путь!";
			link.l1.go = "Stivesant_9";			
		break;
		
		case "Stivesant_9":
			DialogExit();
			Diag.CurrentNode = "Stivesant_10";
			AddQuestRecord("Holl_Gambit", "3-52");
			pchar.questTemp.HWIC.Self = "WayWithStivesant";
			Group_DelCharacter("Stivesant_Halleon", "Stivesant");
			SetCharacterRemovable(npchar, false);
			npchar.CompanionEnemyEnable = false; //всегда друзья
			SetCompanionIndex(pchar, -1, sti(npchar.index));
			npchar.loyality = 40;
			DeleteAttribute(npchar, "LifeDay");
			pchar.quest.Seek_Piter.win_condition.l1 = "location";
			pchar.quest.Seek_Piter.win_condition.l1.location = "Villemstad_town";
			pchar.quest.Seek_Piter.win_condition.l2 = "Day";
			pchar.quest.Seek_Piter.function = "StivesantOnStreet";
			pchar.quest.Terms_Over.win_condition.l1 = "Timer";
			pchar.quest.Terms_Over.win_condition.l1.date.hour  = sti(GetTime());
			pchar.quest.Terms_Over.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 15);
			pchar.quest.Terms_Over.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 15);
			pchar.quest.Terms_Over.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 15);
			pchar.quest.Terms_Over.function = "QuestShipsTerms_Over";
		break;
		
		case "Stivesant_10":
			dialog.text = "Капитан, отправляйтесь на 'Мейфенг'. Нам пора в путь.";
			link.l1 = "Да, конечно, минхер.";
			link.l1.go = "exit";
			Diag.TempNode = "Stivesant_10";
		break;
		
		case "Keller_1":
			dialog.text = "Очень интересно! Ну, рассказывайте. Чем смогу - тем помогу.";
			link.l1 = "Минхер Келлер, помните, несколько месяцев назад вы встретили по пути в Виллемстад флейт. На нем была семья еврейских беженцев. Вы отобедали на борту этого корабля, затем отправились в дальнейший путь.";
			link.l1.go = "Keller_2";
		break;
		
		case "Keller_2":
			dialog.text = "Да, кажется, я припоминаю нечто подобное. Да, точно, вспомнил. И в чем же дело?";
			link.l1 = "Флейт был потоплен в этот же день пиратом. Спастись удалось только двоим, этим беженцам - Соломону и его дочери Абигайль. Они укрылись на острове буквально в нескольких милях от места нападения. Мне нужно найти этот остров. Вспомните, пожалуйста, где было место вашей встречи с этим флейтом? Это очень важно.";
			link.l1.go = "Keller_3";
		break;
		
		case "Keller_3":
			dialog.text = "И всего-то? Я знаю этот остров. Он совсем близко отсюда, между Тринидадом и Кюрасао. Маленький, пустынный необитаемый островок. На нем нет даже индейцев.";
			link.l1 = "Вы можете назвать приблизительные координаты?";
			link.l1.go = "Keller_4";
		break;
		
		case "Keller_4":
			dialog.text = "Я назову вам точные. 12 гр. 48' северной широты и 64 гр. 41' градусов западной долготы. Ищите в этом районе. Остров маленький, но, думаю, вы его без труда найдете.";
			link.l1 = "Спасибо, минхер Келлер! Вы мне очень помогли! До свидания.";
			link.l1.go = "Keller_5";
		break;
		
		case "Keller_5":
			DialogExit();
			Diag.CurrentNode = "Keller_6";
			pchar.quest.Keller_fail.over = "yes";
			pchar.questTemp.HWIC_Coordinates = "true"; //атрибут координат на поиск острова через каюту
			DeleteAttribute(pchar, "questTemp.HWICMC");
			AddQuestRecord("Holl_Gambit", "3-66");
		break;
		
		case "Keller_6":
			dialog.text = "Вы что-то еще хотели узнать, капитан?";
			link.l1 = "Нет, спасибо. Я уже отправляюсь на свой корабль.";
			link.l1.go = "exit";
			Diag.TempNode = "Keller_6";
		break;
	}
}

string GetNumShips(int ship)
{
    string numships;
    switch(ship)
    {
       case 0: numships = "ни одного корабля"; break;
       case 1: numships = "один корабль";      break;
       case 2: numships = "два корабля";       break;
       case 3: numships = "три корабля";       break;
       case 4: numships = "четыре корабля";    break;
       case 5: numships = "пять кораблей";     break;
       case 6: numships = "шесть кораблей";    break;
    }
    return numships;
}

string GetPart(int part)
{
    string numpart;
    switch(part)
    {
       case 0: numpart = ""; break;
       case 1: numpart = "всю добычу"; break;
       case 2: numpart = "половину добычи"; break;
       case 3: numpart = "треть добычи"; break;
       case 4: numpart = "четверть добычи";      break;

    }
    return numpart;
}

int findPriceStoreMan(ref NPChar)
{
    ref ch;
	int n;
    int storeArray[40];
    int howStore = 0;

	for(n=0; n<MAX_CHARACTERS; n++)
	{
		makeref(ch,Characters[n]);
		if (CheckAttribute(ch, "Dialog.Filename") && ch.Dialog.Filename == "Common_Store.c") // магазин
		{
            //if (sti(ch.nation) !=  sti(NPChar.nation)) continue;
            if (ch.location == "none") continue; // фикс для новых, невидимых до поры островов
            storeArray[howStore] = n;
            howStore++;
            
            // homo 05/09/06
            if ( CheckAttribute(NPChar, "FromColony") && NPChar.FromColony == ch.City ) return n;
            //
		}
    }
    if (howStore == 0)
    {
        return -1;
    }
    else
    {
        return storeArray[rand(howStore-1)];
    }
}
