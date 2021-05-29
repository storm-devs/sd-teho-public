#include "DIALOGS\russian\Rumours\Common_rumours.c"  //homo 25/06/06
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag, arCapBase, arCapLocal;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	// доп повека
	if (!CheckAttribute(NPChar, "Portman")) NPChar.Portman = 0;
	if (!CheckAttribute(NPChar, "PortManPrice")) NPChar.PortManPrice = (0.06 + frnd()*0.1);

    // вызов диалога по городам -->
    NPChar.FileDialog2 = "DIALOGS\" + LanguageGetLanguage() + "\PortMan\" + NPChar.City + "_PortMan.c";
    if (LoadSegment(NPChar.FileDialog2))
	{
        ProcessCommonDialog(NPChar, Link, NextDiag);
		UnloadSegment(NPChar.FileDialog2);
	}
    // вызов диалога по городам <--
	ProcessCommonDialogRumors(NPChar, Link, NextDiag);//homo 25/06/06

    int i, cn, iTemp;
    ref chref;
	ref rRealShip;
    string attrL, sTitle, sCapitainId, s1;
	string sColony;
    
	String sLastSpeakDate = LastSpeakDate();
	
	// Warship 25.07.09 Генер "Сгоревшее судно". Даты отказа ГГ - если отказал, то предложит снова только на след сутки
	if(CheckAttribute(NPChar, "Quest.BurntShip.LastQuestDate") && NPChar.Quest.BurntShip.LastQuestDate != sLastSpeakDate)
	{
		DeleteAttribute(NPChar, "Quest.BurntShip");
	}
    
    bool ok;
    int iTest = FindColony(NPChar.City); // город магазина
    ref rColony;
    string sFrom_sea = "";
	npchar.quest.qty = CheckCapitainsList(npchar); //для списка кэпов

	if (iTest != -1)
	{
		rColony = GetColonyByIndex(iTest);
		sFrom_sea = rColony.from_sea;
	}
	
	attrL = Dialog.CurrentNode;
	
	if(HasSubStr(attrL, "ShipStockManBack_"))
 	{
        i = findsubstr(attrL, "_" , 0);
	 	NPChar.ShipToStoreIdx = strcut(attrL, i+1, strlen(attrL)-1); // индех в конце
 	    Dialog.CurrentNode = "ShipStockManBack";
 	}
    
	if(HasSubStr(attrL, "BurntShip19_"))
	{
		i = findsubstr(attrL, "_" , 0);
	 	NPChar.Quest.BurntShip.ShipCompanionIndex = strcut(attrL, i + 1, strlen(attrL) - 1); // индех в конце
 	    Dialog.CurrentNode = "BurntShip19";
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
			NextDiag.TempNode = "First time";
			if (LAi_grp_playeralarm > 0)
			{
       			dialog.text = NPCharRepPhrase(pchar, 
					LinkRandPhrase("В городе поднята тревога, тебя всюду ищут! На твоём месте я бы не стал здесь задерживаться.", "Вся городская стража рыщет по городу в поисках тебя. Я не идиот и разговаривать с тобой не буду!", "Беги, "+ GetSexPhrase("приятель","подруга") +", пока солдаты не сделали из тебя решето..."), 
					LinkRandPhrase("Что тебе нужно, "+ GetSexPhrase("негодяй","мерзавка") +"?! Городская стража уже взяла твой след, далеко тебе не уйти"+ GetSexPhrase(", грязный пират","") +"!", "Грязн"+ GetSexPhrase("ый","ая") +" убийца, вон из моего дома! Стража!!", "Я не боюсь тебя, мерзав"+ GetSexPhrase("ец","ка") +"! Скоро тебя повесят в нашем форте, далеко тебе не уйти..."));
				link.l1 = NPCharRepPhrase(pchar,
					RandPhraseSimple("Хех, тревога для меня не проблема...", "Им меня ни за что не поймать."), 
					RandPhraseSimple("Заткни свою пасть, " + GetWorkTypeOfMan(npchar, "") + ", а не то вырву твой поганый язык!", "Хех, " + GetWorkTypeOfMan(npchar, "") + ", а всё туда же - пиратов ловить! Вот что я тебе скажу, приятель: сиди тихо и будешь жить..."));
				link.l1.go = "fight";
				break;
			}
			//Jason, фрахт
			if (CheckAttribute(pchar, "questTemp.WPU"))
			{
				if (pchar.questTemp.WPU.Fraht == "fail" && pchar.questTemp.WPU.Fraht.Nation == npchar.nation)
				{
					dialog.text = "А-а, я знаю, кто вы. Вы подрядились доставить груз и украли его! Стража, сюда!";
					Link.l1 = "А-а-ть!";
					Link.l1.go = "exit";
					LAi_group_Attack(NPChar, Pchar);
					break;
				}
			}
			//фрахт
			//--> Jason Бремя гасконца
			if (CheckAttribute(pchar, "questTemp.Sharlie.Lock"))
			{
				dialog.text = "Чем могу быть полезен, месье?";
				Link.l1 = "У меня к вам одно дело...";
				Link.l1.go = "quests";
				Link.l2 = "Прошу прощения, но мне надо идти.";
				Link.l2.go = "exit";
				NPChar.quest.meeting = "1"; // patch-6
				break;
			}			
			//<-- Бремя гасконца
			if(NPChar.quest.meeting == "0")
			{
				NPChar.quest.meeting = "1";
				dialog.text = "Приветствую вас, " + GetAddress_Form(NPChar) + ". Мы, кажется, не знакомы. Я "  + GetFullName(npchar)+ " - начальник порта.";
				Link.l1 = "Здравствуйте, " + GetFullName(NPChar) + ". Я " + GetFullName(PChar) + ", капитан корабля '" + PChar.ship.name + "'.";
			}
			else
			{
				dialog.text = LinkRandPhrase("Приветствую вас, " + GetAddress_Form(NPChar) + ". Вы ко мне по делу?",
                                    "Здравствуйте, " + GetFullName(Pchar) + ". Я видел, как ваш корабль вошёл в порт, и был уверен, что вы ко мне зайдёте.",
                                    "А, капитан " + GetFullName(Pchar) + ". Что привело вас ко мне?");
				Link.l1 = "Здравствуйте, " + GetFullName(NPChar) + ". Я хочу с вами поговорить.";
			}
			Link.l1.go = "node_2";
		break;
		
		case "node_2":
			// Церковный генератор 1
			if(CheckAttribute(PChar, "GenQuest.ChurchQuest_1.AskPortMan") && PChar.GenQuest.ChurchQuest_1.AskPortMan_InColony == NPChar.city)
			{
				dialog.text = "Прекрасно. Я к вашим услугам, " + GetFullName(PChar) + ".";
				if(!CheckAttribute(PChar, "GenQuest.ChurchQuest_1.CapFullInfo"))	// Получаем полную инфу
				{
					if(CheckAttribute(PChar, "GenQuest.ChurchQuest_1.NoMoneyToPortMan"))
					{
						dialog.text = "Так, что там с деньгами? Вы принесли мне хотя бы тысячу песо?";
						if(sti(PChar.Money) >= 1000)
						{
							link.l1 = "Да, принёс"+ GetSexPhrase("","ла") +". Вот ровно тысяча песо. Теперь информация!";
							link.l1.go = "Church_GenQuest1_Node_FillFullInfo_3";
						}
						else
						{
							link.l1 = LinkRandPhrase("Нет, ещё не принёс"+ GetSexPhrase("","ла") +"...", "Ещё нет...", "Ещё не принёс"+ GetSexPhrase("","ла") +", но скоро принесу...");
							link.l1.go = "exit";
						}
					}
					else
					{
						link.l1 = "Позвольте изложить вам суть вопроса. Я разминул"+ GetSexPhrase("ся","ась") +" со своим старым другом, капитаном " + PChar.GenQuest.ChurchQuest_1.CapFullName + ", всего на несколько часов, а у меня к нему срочное дело. Теперь придётся его догонять, но я, к сожалению, не осведомлён"+ GetSexPhrase("","а") +", в каком направлении он отбыл.";
						link.l1.go = "Church_GenQuest1_Node_FillFullInfo";
					}
				}
				else	// Полная инфа уже есть
				{
					link.l1 = "Господин начальник порта, мне нужна информация о судне '" + PChar.GenQuest.ChurchQuest_1.CapShipName + "', капитана " + PChar.GenQuest.ChurchQuest_1.CapFullName + ".";
					if(CheckAttribute(PChar, "GenQuest.ChurchQuest_1.NextColonyIsLast")) // Он здесь, в этой колонии!		
						link.l1.go = "Church_GenQuest1_Node_CapOnThisColony_1";
					else // Отправляет в рандомную колонию
						link.l1.go = "Church_GenQuest1_Node_FillInfoOfCapColony_1";
				}				
				break;
			}		
//-------------------------------------------//Jason, фрахт---------------------------------------------------
				if (CheckAttribute(PChar, "questTemp.WPU.Fraht.TargetPortmanID") && CheckAttribute(PChar, "questTemp.WPU.Fraht.LevelUp") && pchar.questTemp.WPU.Fraht.TargetPortmanID == npchar.id)
				{
					dialog.text = "Прекрасно. Я к вашим услугам, " + GetFullName(PChar) + ".";
					Link.l1 = "В трюме моего корабля груз для вашей колонии.";
					Link.l1.go = "Fraht_completeLevelUp";
					break;
				}
				if (CheckAttribute(PChar, "questTemp.WPU.Fraht.TargetPortmanID") && pchar.questTemp.WPU.Fraht != "lost" && pchar.questTemp.WPU.Fraht.TargetPortmanID == npchar.id)
				{
					dialog.text = "Прекрасно. Я к вашим услугам, " + GetFullName(PChar) + ".";
					Link.l1 = "В трюме моего корабля груз для вашей колонии.";
					Link.l1.go = "Fraht_complete";
					break;
				}
			
				if (CheckAttribute(PChar, "questTemp.WPU.Fraht.TargetPortmanID") && pchar.questTemp.WPU.Fraht == "lost" && pchar.questTemp.WPU.Fraht.Nation == npchar.nation)
				{
					if (pchar.questTemp.WPU.Fraht.TargetPortmanID == npchar.id)
					{
						dialog.text = "А, вот вы всё-таки и явились. Право, не думал, что вы придёте - мы уже подали властям петицию на объявление вас в розыск. Ну, что скажете?";
						Link.l1 = "Мне помешали обстоятельства доставить груз вовремя. Но я хочу урегулировать ситуацию мирным путём. Я привёз ваш груз и надеюсь на разрешение конфликта.";
						Link.l1.go = "Fraht_complete_bad";
					}
					else
					{
						dialog.text = "А-а, я знаю, кто вы. Вы подрядились доставить груз и украли его! Стража, сюда!";
						Link.l1 = "А-а-ть!";
						Link.l1.go = "exit";
						LAi_group_Attack(NPChar, Pchar);
					}
				}
// <-- фрахт
//-------------------------------------------//Jason, почта---------------------------------------------------	
		
				if (CheckAttribute(PChar, "questTemp.WPU.Postcureer.TargetPortmanID") && pchar.questTemp.WPU.Postcureer != "lost" && pchar.questTemp.WPU.Postcureer.TargetPortmanID == npchar.id)
				{
					dialog.text = "Прекрасно. Я к вашим услугам, " + GetFullName(PChar) + ".";
					Link.l1 = "Я доставил почту для вашей колонии.";
					Link.l1.go = "Postcureer_complete";
					break;
				}
			
				if (CheckAttribute(PChar, "questTemp.WPU.Postcureer.TargetPortmanID") && pchar.questTemp.WPU.Postcureer == "lost" && pchar.questTemp.WPU.Postcureer.TargetPortmanID == npchar.id)
				{
					dialog.text = "Гм, вы всё-таки появились... А мы, право, решили, что вас уже нет в живых... Ну да ладно, я рад, что вы оказались просто растяпой, а не мертвецом.";
					Link.l1 = "Мне помешали обстоятельства доставить почту вовремя. Вот она, возьмите.";
					Link.l1.go = "Postcureer_complete_bad";
					break;
				}
			
				if (CheckAttribute(PChar, "questTemp.WPU.Postcureer.fail") && pchar.questTemp.WPU.Postcureer.StartCity == npchar.city)
				{
					dialog.text = "Что случилось? На вас лица нет...";
					Link.l1 = "" + GetAddress_FormToNPC(NPChar) + ", вы были правы, предупреждая об опасности. Прямо на выходе из портового управления на меня напали двое в чёрном... ну, в общем, они отобрали у меня пакет.";
					Link.l1.go = "Postcureer_complete_fail";
					break;
				}
// <-- почта
//-------------------------------------------//Jason, эскорт---------------------------------------------------	
				if(CheckAttribute(PChar, "questTemp.WPU.Escort.TargetPortmanID") && CheckAttribute(pchar, "questTemp.WPU.Escort.LevelUp_0") && pchar.questTemp.WPU.Escort.TargetPortmanID == npchar.id)
				{
					dialog.text = "Прекрасно. Я к вашим услугам, " + GetFullName(PChar) + ".";
					Link.l1 = "Меня прислал начальник порта "+XI_ConvertString("Colony"+pchar.questTemp.WPU.Escort.StartCity+"Gen")+". Я должен сопроводить корабль с грузом оружия и боеприпасов, стоящий у вас на рейде. Вот мои бумаги.";
					Link.l1.go = "Escort_LUGo_0";
					break;
				}
				if(CheckAttribute(PChar, "questTemp.WPU.Escort.TargetPortmanID") && CheckAttribute(pchar, "questTemp.WPU.Escort.LevelUpGo_0") && npchar.location == pchar.questTemp.WPU.Escort.StartCity +"_portoffice")
				{
					dialog.text = "Прекрасно. Я к вашим услугам, " + GetFullName(PChar) + ".";
					Link.l1 = "Я сопроводил судно с оружием, как мы и договаривались.";
					Link.l1.go = "Escort_LUGo_complete";
					break;
				}
				if(CheckAttribute(PChar, "questTemp.WPU.Escort.TargetPortmanID") && CheckAttribute(pchar, "questTemp.WPU.Escort.LevelUp_1WM") && pchar.questTemp.WPU.Escort == "current" && npchar.location == pchar.questTemp.WPU.Escort.StartCity +"_portoffice")
				{
					dialog.text = "Прекрасно. Я к вашим услугам, " + GetFullName(PChar) + ".";
					Link.l1 = "Я нашёл пропавшее судно и доставил его в ваш порт. Думаю, его капитан уже доложил вам об этом.";
					Link.l1.go = "Escort_LU1WM_complete";
					break;
				}
				if(CheckAttribute(PChar, "questTemp.WPU.Escort.TargetPortmanID") && CheckAttribute(pchar, "questTemp.WPU.Escort.LevelUp_1VSP") && pchar.questTemp.WPU.Escort == "win" && npchar.location == pchar.questTemp.WPU.Escort.StartCity +"_portoffice")
				{
					dialog.text = "Прекрасно. Я к вашим услугам, " + GetFullName(PChar) + ".";
					Link.l1 = "Я нашёл пропавшее судно и доставил его в ваш порт. Думаю, его капитан уже доложил вам об этом.";
					Link.l1.go = "Escort_LU1VSP_complete";
					break;
				}
				if(CheckAttribute(PChar, "questTemp.WPU.Escort.TargetPortmanID") && CheckAttribute(pchar, "questTemp.WPU.Escort.LevelUp_1VSP") && pchar.questTemp.WPU.Escort == "sink" && npchar.location == pchar.questTemp.WPU.Escort.StartCity +"_portoffice")
				{
					dialog.text = "Прекрасно. Я к вашим услугам, " + GetFullName(PChar) + ".";
					Link.l1 = "Я нашёл пропавшее судно у берегов острова "+XI_ConvertString(pchar.questTemp.WPU.Current.TargetIslandID)+". Его капитан вёл неравный бой с превосходящими силами пиратов. Я оказал ему всю возможную помощь, но мои усилия оказались тщетны: проклятые негодяи потопили корабль. Я только смог отомстить им за него.";
					Link.l1.go = "Escort_LU1VSP_completeSink";
					break;
				}
				if(CheckAttribute(PChar, "questTemp.WPU.Escort.TargetPortmanID") && CheckAttribute(pchar, "questTemp.WPU.Escort.LevelUp_1S") && pchar.questTemp.WPU.Escort == "win" && npchar.location == pchar.questTemp.WPU.Escort.StartCity +"_portoffice")
				{
					dialog.text = "Прекрасно. Я к вашим услугам, " + GetFullName(PChar) + ".";
					Link.l1 = "Я нашёл пропавшее судно у берегов острова "+XI_ConvertString(pchar.questTemp.WPU.Current.TargetIslandID)+". Точнее, не само судно, а только полсотни человек его команды и капитана. Все они в безопасности - команда у меня на корабле, а капитан в вашем городе - наверное, он уже заходил к вам.";
					Link.l1.go = "Escort_LU1S_complete";
					break;
				}
				if(CheckAttribute(PChar, "questTemp.WPU.Escort.TargetPortmanID") && CheckAttribute(pchar, "questTemp.WPU.Escort.LevelUp_2") && pchar.questTemp.WPU.Escort == "win" && npchar.location == pchar.questTemp.WPU.Escort.StartCity +"_portoffice")
				{
					dialog.text = "Прекрасно. Я к вашим услугам, " + GetFullName(PChar) + ".";
					Link.l1 = "Я выполнил ваше поручение. Пиратская эскадра, атаковавшая торговый караван, уничтожена.";
					Link.l1.go = "Escort_LU2_complete";
					break;
				}
				if (CheckAttribute(PChar, "questTemp.WPU.Escort.TargetPortmanID") && CheckAttribute(pchar, "questTemp.WPU.Escort.Bonus") && pchar.questTemp.WPU.Escort.Bonus != "fail" && pchar.questTemp.WPU.Escort.TargetPortmanID == npchar.id)
				{
					dialog.text = "Прекрасно. Я к вашим услугам, " + GetFullName(PChar) + ".";
					Link.l1 = "Я капитан судна сопровождения. Я доставил в порт торговые корабли и хочу отчитаться.";
					Link.l1.go = "Escort_complete";
					break;
				}
				if (CheckAttribute(PChar, "questTemp.WPU.Escort.TargetPortmanID") && CheckAttribute(pchar, "questTemp.WPU.Escort.Bonus") && pchar.questTemp.WPU.Escort.Bonus == "fail" && pchar.questTemp.WPU.Escort.TargetPortmanID == npchar.id)
				{
					dialog.text = "Прекрасно. Я к вашим услугам, " + GetFullName(PChar) + ".";
					Link.l1 = "Я капитан судна сопровождения. Я должен был доставить в порт два торговых судна и груз, но, к сожалению, оба сопровождаемых корабля утонули в бою с вражеским караваном. Мне очень жаль. Но груз я доставил.";
					Link.l1.go = "Escort_fail";
					break;
				}
				if (CheckAttribute(PChar, "questTemp.WPU.Escort.TargetPortmanID") && pchar.questTemp.WPU.Escort.TargetPortmanID == npchar.id && !CheckAttribute(PChar, "questTemp.WPU.Escort.LevelUp"))
				{
					dialog.text = "Прекрасно. Я к вашим услугам, " + GetFullName(PChar) + ".";
					Link.l1 = "Я капитан судна сопровождения. Я доставил в порт торговые корабли и хочу отчитаться.";
					Link.l1.go = "Escort_complete";
					break;
				}
// <-- эскорт
		
		      /* if (rand(3) <= 2)
			  {		
			    if (ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 0) <= -20)
			    {
                dialog.text = "Я замечу что вы, уважаемый, находитесь в розыске и за вашу голову объявлена награда. Поэтому я откажу вам в обслуживании и вызову стражу. Стража!!!";
                link.l1 = "Да уж.. Высоко пойдёшь. Смотри, как бы не упасть!";
                link.l1.go = "exit"; // fight
                LAi_group_Attack(NPChar, Pchar);
                break;
                }
              }	*/	
			dialog.text = "Прекрасно. Я к вашим услугам, " + GetFullName(PChar) + ".";
			if (npchar.city != "Panama") // Captain Beltrop, 24.12.2020, запрет брать задания и ставить корабли в ПУ Панамы
			{
				Link.l2 = "Здесь можно подыскать работу? Или контракт?";
				Link.l2.go = "Work_check"; //фрахты-почта-эскорт
				Link.l14 = "Может, у вас есть дело, требующее сторонней помощи? Могу предложить свои услуги.";
				Link.l14.go = "node_4"; //на мини-квесты
				Link.l3 = "Могу я оставить один из своих кораблей на время?";
				Link.l3.go = "ShipStock_1";
			}
			if (sti(NPChar.Portman) > 0)
			{
                Link.l4 = "Я хочу забрать свой корабль обратно.";
    			Link.l4.go = "ShipStockReturn_1";
			}
			if (CheckAttribute(pchar, "GenQuest.LoanChest.TakeChest") && sti(pchar.GenQuest.LoanChest.TargetIdx) == sti(NPChar.index))
			{
				link.l5 = "Я к вам по финансовым делам.";
				link.l5.go = "LoanForAll";//(перессылка в кредитный генератор)	
			}
  			if (CheckAttribute(pchar, "GenQuest.Intelligence") && pchar.GenQuest.Intelligence.SpyId == npchar.id && pchar.GenQuest.Intelligence == "") //квест мэра - на связь с нашим шпионом
			{
				link.l7 = RandPhraseSimple("Я здесь по поручению одного человека. Его зовут губернатор " + GetFullName(characterFromId(pchar.GenQuest.Intelligence.MayorId)) + ".", 
					GetFullName(characterFromId(pchar.GenQuest.Intelligence.MayorId)) + " прислал меня к вам. Я долж"+ GetSexPhrase("ен","на") +" кое-что забрать...");
				link.l7.go = "IntelligenceForAll";
			}
			link.l6 = "Меня интересуют капитаны, которые отмечались в вашем портовом управлении.";
			link.l6.go = "CapitainList";
			
			link.l8 = "Я по другому вопросу.";
			// Warship 26.07.09 Генер "Сгоревшее судно"
			if(CheckAttribute(NPChar, "Quest.BurntShip") && !CheckAttribute(NPChar, "Quest.BurntShip.LastQuestDate"))
			{
				if(CheckAttribute(NPChar, "Quest.BurntShip.TimeIsOver")) // Просрочено
				{
					link.l8.go = "BurntShip10";
				}
				else
				{
					if(CheckAttribute(NPChar, "Quest.BurntShip.TwoDaysWait"))
					{
						if(GetNpcQuestPastDayParam(NPChar, "Quest.BurntShip.TwoDaysWait") >= 2)
						{
							link.l8.go = "BurntShip17";
						}
						else
						{
							link.l8.go = "quests";
						}
					}
					else
					{
						link.l8.go = "BurntShip12";
					}
				}
			}
			else
			{
				link.l8.go = "quests";
			}
			if(CheckAttribute(pchar,"GenQuest.EncGirl"))
			{
				if(pchar.GenQuest.EncGirl == "toLoverFather" && pchar.GenQuest.EncGirl.LoverFather == "portman_keeper" && pchar.GenQuest.EncGirl.LoverCity == npchar.city)
				{
					link.l9 = "Здравствуйте, я приш"+ GetSexPhrase("ёл","ла") +" по приглашению вашего сына."; 
					link.l9.go = "EncGirl_4";
					pchar.quest.EncGirl_GetLoverFather.over = "yes";
				}	
				if(pchar.GenQuest.EncGirl == "toParents" || pchar.GenQuest.EncGirl == "FindLover")
				{
					if(pchar.GenQuest.EncGirl.Father == "portman_keeper" && npchar.city == pchar.GenQuest.EncGirl.city)
					{
						link.l9 = "Я по поводу вашей дочери ...";
						link.l9.go = "EncGirl_1";
					}
				}
			}
			if (CheckCharacterItem(pchar, "CaptainBook"))
			{
				if(pchar.questTemp.different == "free")
				{
					link.l10 = "Я по случайности наш"+ GetSexPhrase("ёл","ла") +" вот этот пакет судовых документов.";
					link.l10.go = "ShipLetters_out1";				
				}
				else
				{
					if(pchar.questTemp.different.GiveShipLetters.city == npchar.city)
					{
						link.l10 = "Я по случайности наш"+ GetSexPhrase("ёл","ла") +" вот этот, наверняка кем-то позабытый, пакет судовых документов.";
						if(!CheckAttribute(pchar, "questTemp.different.GiveShipLetters.speakPortman"))
						{
							link.l10.go = "ShipLetters_Portman1_1";						
						}
						else
						{
							link.l10.go = "ShipLetters_Portman2";
						}
					}
				}		
			}												
			Link.l15 = "Благодарю. До свидания.";
			Link.l15.go = "exit";
		break;

		case "Church_GenQuest1_Node_FillFullInfo":
			dialog.text = "Ваша проблема легко разрешима. Вы можете обратиться к любому чиновнику службы навигации, и получить всю имеющуюся информацию о маршруте судна вашего друга.";
			link.l1 = "К сожалению, не всё так просто. Именно в вашем порту мой друг сменил название судна... из религиозных побуждений.";
			link.l1.go = "Church_GenQuest1_Node_FillFullInfo_2";
		break;
			
		case "Church_GenQuest1_Node_FillFullInfo_2":
			dialog.text = "Так. Это уже сложнее. Мне нужно поднять записи в судовом реестре, это потребует времени. А в наши дни, как известно, время - деньги...";
			if(sti(pchar.money) >= 1000)
			{
				link.l1 = "Я это прекрасно понимаю, г-н " + GetFullName(NPChar) + ", и готов"+ GetSexPhrase("","а") +" достойно оценить ваше время... в размере, скажем, 1000 песо.";
				link.l1.go = "Church_GenQuest1_Node_FillFullInfo_3";
			}
			else
			{
				DeleteAttribute(pchar, "GenQuest.ChurchQuest_1.CurPortManColony"); // Можно будет спросить.
				link.l1 = "М-да... А денег-то у меня и нету... Вернусь позже...";
				link.l1.go = "exit";
			}
		break;
			
		case "Church_GenQuest1_Node_FillFullInfo_3":
			sColony = GetColonyExpect2Colonies(NPChar.city, PChar.GenQuest.ChurchQuest_1.QuestTown);
			PChar.GenQuest.ChurchQuest_1.CapGoToColony = sColony;
			if(CheckAttribute(pchar, "GenQuest.ChurchQuest_1.NoMoneyToPortMan"))
			{
				dialog.text = "Отлично! Сейчас посмотрим, что там у нас... минуту... так... вот, пожалуйста. В судовом реестре отмечено переименование, и судно, называемое отныне '" + PChar.GenQuest.ChurchQuest_1.CapShipName + "' под управлением капитана " + PChar.GenQuest.ChurchQuest_1.CapFullName + " отправилось сегодня в сторону " + XI_ConvertString("Colony" + sColony + "Gen") + ".";
				DeleteAttribute(pchar, "GenQuest.ChurchQuest_1.NoMoneyToPortMan");
			}
			else
				dialog.text = "О-о-о!... То есть, да, вы оценили по достоинству, так как я очень, очень занятой человек. Минуту... так... вот, пожалуйста. В судовом реестре отмечено переименование. Судно, называемое отныне '" + PChar.GenQuest.ChurchQuest_1.CapShipName + "' под управлением капитана " + PChar.GenQuest.ChurchQuest_1.CapFullName + " отбыло сегодня в сторону " + XI_ConvertString("Colony" + sColony + "Gen") + ".";			
				link.l1 = "Благодарю вас, сударь, вы оказали мне действительно большую услугу.";
				link.l1.go = "Church_GenQuest1_Node_FillFullInfo_4";
				AddMoneyToCharacter(pchar, -1000);
		break;
			
		case "Church_GenQuest1_Node_FillFullInfo_4":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			sQuestTitle = PChar.GenQuest.ChurchQuest_1.QuestTown + "ChurchGenQuest1";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest1", "4");
			AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("ен","на"));
			AddQuestUserData(sQuestTitle, "sColony", XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.CapGoToColony + "Gen"));
			AddQuestUserData(sQuestTitle, "sShipName", PChar.GenQuest.ChurchQuest_1.CapShipName);	
			PChar.GenQuest.ChurchQuest_1.AskPortMan_InColony = PChar.GenQuest.ChurchQuest_1.CapGoToColony;
			PChar.GenQuest.ChurchQuest_1.CapFullInfo = true;
		break;
			
		case "Church_GenQuest1_Node_FillInfoOfCapColony_1":
			dialog.text = "Что именно вы хотите узнать?";
			link.l1 = "Скажите, не заходило ли судно этого капитана в ваш порт?";
			link.l1.go = "Church_GenQuest1_Node_FillInfoOfCapColony_2";
		break;
						
		case "Church_GenQuest1_Node_FillInfoOfCapColony_2":
			PChar.GenQuest.ChurchQuest_1.CapGoToColony = GetColonyExpect2Colonies(NPChar.city, PChar.GenQuest.ChurchQuest_1.QuestTown);
			dialog.text = "Хм... Позвольте узнать, с какой целью вы его разыскиваете?";
			link.l1 = "У меня к нему дело. Если он не был в вашем порту или вы не...";
			link.l1.go = "Church_GenQuest1_Node_FillInfoOfCapColony_3";
		break;
			
		case "Church_GenQuest1_Node_FillInfoOfCapColony_3":
			dialog.text = "Он был. Но - слава Святым Угодникам - не далее как сегодня утром, наконец милосердно избавил нас, грешных, от своего общества и направился в " + XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.CapGoToColony + "Acc") + ". И мне, признаться, искренне жаль любого, кому предстоит иметь с ним дело.";
			link.l1 = "В таком случае пожелайте мне удачи, и благодарю за помощь.";
			link.l1.go = "Church_GenQuest1_Node_FillInfoOfCapColony_4";
		break;
			
		case "Church_GenQuest1_Node_FillInfoOfCapColony_4":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			sQuestTitle = PChar.GenQuest.ChurchQuest_1.QuestTown + "ChurchGenQuest1";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest1", "5");
			AddQuestUserData(sQuestTitle, "sColony", XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.CapGoToColony + "Dat"));
			AddQuestUserData(sQuestTitle, "sName", PChar.GenQuest.ChurchQuest_1.CapFullName);
			PChar.GenQuest.ChurchQuest_1.AskPortMan_InColony = PChar.GenQuest.ChurchQuest_1.CapGoToColony; // Спрашиваем портмана в колонии, куда отправился кэп.
			if(rand(2) == 1) 
			{
				Log_TestInfo("Следующая колония - последняя");
				PChar.GenQuest.ChurchQuest_1.NextColonyIsLast = true; // Флаг - следующая колония будет последней
			}
		break;
			
		case "Church_GenQuest1_Node_CapOnThisColony_1":
			dialog.text = "Что именно вас интересует, госпо"+ GetSexPhrase("дин","жа") +" " + GetFullName(PChar) + "?";
			link.l1 = "Скажите, не заходил ли в ваш порт этот капитан?";
			link.l1.go = "Church_GenQuest1_Node_CapOnThisColony_2";
		break;
			
		case "Church_GenQuest1_Node_CapOnThisColony_2":
			dialog.text = "Хм, заходил... Так зашёл, что я с нетерпением ожидаю, когда он покинет мой многострадальный порт.";
			link.l1 = "То есть, это судно всё ещё находится здесь?";
			link.l1.go = "Church_GenQuest1_Node_CapOnThisColony_3";
		break;
			
		case "Church_GenQuest1_Node_CapOnThisColony_3":
			dialog.text = "Да, милостив"+ GetSexPhrase("ый господин","ая госпожа") +". Весь порт, от последнего грузчика до главы лоцманской службы, молится о его скорейшем благополучном отбытии. Судно только что вышло из сухого дока, где получило необходимый ремонт, а его доблестный капитан успел перессориться с каждым плотником, и забраковать три партии отборных досок для наружной обшивки. Но уже завтра всевидящий и всеблагой Господь избавит нас от этой... от этой чумы, от этой язвы в человеческом обличии!";
			link.l1 = "Успокойтесь, господин " + NPChar.Name + ", и подумайте о том, что кому-то сейчас придётся тяжелее, чем вам. Вы уже прошли через это испытание, а мне только предстоит встретиться с этим капитаном... Позвольте откланяться.";
			link.l1.go = "Church_GenQuest1_Node_CapOnThisColony_4";
		break;
			
		case "Church_GenQuest1_Node_CapOnThisColony_4":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			sQuestTitle = PChar.GenQuest.ChurchQuest_1.QuestTown + "ChurchGenQuest1";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest1", "6");
			AddQuestUserData(sQuestTitle, "sColony", XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.QuestTown));
//			PChar.GenQuest.ChurchQuest_1.NeedToDialogWithSailors = true; // Спрашиваем моряков
			PChar.GenQuest.ChurchQuest_1.NeedToDialogWithCap = true; // Говорим с капитаном
//			SetFunctionLocationCondition("Church_GenQuest1_ChangeCapitanLocation", "Deck_Near_Ship", true);
			PChar.GenQuest.ChurchQuest_1.CurPortManColony = NPChar.city;
			Group_SetAddress("ChurchGenQuest1_CapGroup", colonies[FindColony(NPChar.City)].Island, "IslandShips1", "Ship_1"); // Ставим кэпа в порту колонии
			Characters[GetCharacterIndex("ChurchGenQuest1_Cap")].Nation = sti(NPChar.Nation); // Сменим нацию, чтоб вражды не было
			DeleteAttribute(PChar, "GenQuest.ChurchQuest_1.AskPortMan"); // Больше не спрашиваем
//			if(rand(1) == 0) PChar.GenQuest.ChurchQuest_1.CapWaitOnTavern = true;
			sld = CharacterFromID("ChurchGenQuest1_Cap");
			sld.DeckDialogNode = "ChurchGenQuest_1_DeckDialog_1";
		break;
						
		case "ShipLetters_out1":
			dialog.text = "Дайте-ка взглянуть! Да, в моих документах этот комплект значится недействительным. Вы весьма добры, раз нашли время заглянуть ко мне и передать бумаги. Попутного ветра, капитан!";
			link.l1 = "Благодарю!";
			link.l1.go = "exit";
			TakeItemFromCharacter(pchar, "CaptainBook"); 			
			pchar.questTemp.different = "free";
			pchar.quest.GiveShipLetters_null.over = "yes"; //снимаем таймер 
			AddQuestRecord("GiveShipLetters", "10");			
			CloseQuestHeader("GiveShipLetters");
			DeleteAttribute(pchar, "questTemp.different.GiveShipLetters");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit(); 
		break;
				
		case "ShipLetters_Portman1_1":
			pchar.questTemp.different.GiveShipLetters.speakPortman = true;
			s1 = "Дайте-ка взглянуть! Да, в моих документах значатся и это судно, и его владелец. ";
			s1 = s1 + "Ваша сознательность, капитан, делает Вам честь! Разумеется, Ваши труды должны быть вознаграждены. ";
			dialog.text = s1 + "Скажем, " + sti(pchar.questTemp.different.GiveShipLetters.price1) + " песо Вы сочтёте достойной оплатой?";
			link.l1 = "Разумеется нет!";
			link.l1.go = "exit";
			link.l2 = "Что же, весьма скромная сумма, но и услуга не велика. Да, я принимаю Ваше предложение, "  + npchar.name +" .";
			link.l2.go = "ShipLetters_Portman1_2";
		break;
		
		case "ShipLetters_Portman1_2" :
			TakeItemFromCharacter(pchar, "CaptainBook"); 
			addMoneyToCharacter(pchar, sti(pchar.questTemp.different.GiveShipLetters.price1)); 			
			pchar.questTemp.different = "free";
			pchar.quest.GiveShipLetters_null.over = "yes"; //снимаем таймер 
			AddQuestRecord("GiveShipLetters", "5");			
			CloseQuestHeader("GiveShipLetters");
			DeleteAttribute(pchar, "questTemp.different.GiveShipLetters");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit(); 
		break;
		
		case "ShipLetters_Portman2":
			dialog.text = "Вы согласны принять моё предложение?";
			link.l1 = "Разумеется, нет!";
			link.l1.go = "exit";
			link.l2 = "Пожалуй. Хотя уверен"+ GetSexPhrase("","а") +", что эти бумаги стоят дороже.";
			link.l2.go = "ShipLetters_Portman2_1";
		break;
		
		case "ShipLetters_Portman2_1":
			TakeItemFromCharacter(pchar, "CaptainBook"); 
			addMoneyToCharacter(pchar, sti(pchar.questTemp.different.GiveShipLetters.price1)); 			
			pchar.questTemp.different = "free";
			pchar.quest.GiveShipLetters_null.over = "yes"; //снимаем таймер 
			AddQuestRecord("GiveShipLetters", "6");			
			CloseQuestHeader("GiveShipLetters");
			DeleteAttribute(pchar, "questTemp.different.GiveShipLetters");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit(); 		
		break;

		case "EncGirl_1":
			dialog.text = "Слушаю вас внимательно.";
			link.l1 = "Я привел"+ GetSexPhrase("","а") +" вашу беглянку.";
			link.l1.go = "EncGirl_2";
		break;
		
		case "EncGirl_2":
			dialog.text = "Ах, капитан, спасибо вам большое! Как она? здорова, не пострадала? Уж скоро сутки, как убежала, негодница. Разве ж я ей плохого желаю? Замуж отдать собрался... Жених богатый, молодой, а что собою не пригож, так ведь с лица воду не пить. Нет! она всё по-своему норовит - вся в мать, чтоб её\nХотя, и она бы на свет не появилась, если бы её мамаша в своё время не сбежала с одним предприимчивым оболтусом... ну да что вспоминать... Молодость наивна, глупа... и жестока.";
			link.l1 = "Конечно, вы отец и решать вам, но я бы не торопил"+ GetSexPhrase("ся","ась") +" со свадьбой...";
			link.l1.go = "EncGirl_3";
		break;
		
		case "EncGirl_3":
			dialog.text = "Да что вы понимаете?.. У вас свои дети есть? Нету? Вот, когда будут - заходите, тогда и поговорим...\nДа... я обещал вознаграждение тому, кто её вернёт - примите, пожалуйста.";
			link.l1 = "Спасибо. И держите её покрепче. Что-то мне подсказывает, что она на этом не остановится.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("EncGirl_ToLoverParentsExit");
		break;
		
		case "EncGirl_4":
			if(sti(pchar.GenQuest.EncGirl.LoverFatherAngry) == 0)
			{
				dialog.text = "А, так вы и есть т"+ GetSexPhrase("от капитан, который привёз","а девушка, которая привезла") +" моего блудного сына с молодой невестой?";
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
		
		case "node_4":
			//--> проверка миниквестов начальника порта. 
			if (npchar.quest == "PortmansJornal") //взят квест на судовой журнал
			{
				dialog.text = "Вы должны были найти капитана по имени " + npchar.quest.PortmansJornal.capName + " и вернуть ему судовой журнал. Вы сделали это?";
				link.l1 = "Нет, не получилось пока...";
				link.l1.go = "PortmanQuest_NF";
				break;
			}
			if (npchar.quest == "PortmansSeekShip" || npchar.quest == "SeekShip_sink") //взят квест на поиски украденного корабля
			{
				dialog.text = "Вы подвизались разыскать " + GetStrSmallRegister(XI_ConvertString(npchar.quest.PortmansSeekShip.shipTapeName+"Acc")) + " '" + npchar.quest.PortmansSeekShip.shipName + "'. Пока вы не выполните это задание, ни о каких других поручениях не может быть и речи.";
				link.l1 = "Я продолжу поиски, ждите.";
				link.l1.go = "exit";
				link.l2 = "Хочу отказаться от выполнения вашего поручения.";
				link.l2.go = "SeekShip_break";
				break;
			}
			if (npchar.quest == "SeekShip_success") //украденный корабль взят на абордаж
			{
				dialog.text = "Вы обещали мне разыскать " + GetStrSmallRegister(XI_ConvertString(npchar.quest.PortmansSeekShip.shipTapeName+"Acc")) + " '" + npchar.quest.PortmansSeekShip.shipName + "'. Вы сделали это?";
				bool bOk = false;
				for (i=0; i<=COMPANION_MAX; i++)
				{
					cn = GetCompanionIndex(pchar, i);
					if(cn != -1)
					{
						sld = &characters[cn];
						if (sld.ship.name == npchar.quest.PortmansSeekShip.shipName && 
							RealShips[sti(sld.ship.type)].BaseName == npchar.quest.PortmansSeekShip.shipTapeName &&
							RealShips[sti(sld.Ship.Type)].basetype == npchar.quest.PortmansSeekShip.shipTape)
						{
							if (i == 0)
							{	//если нужный корабль - у ГГ
								sld.Ship.Type = GenerateShip(SHIP_TARTANE, true);
								SetBaseShipData(sld);
								SetCrewQuantityFull(sld);
							}
							else
							{
								RemoveCharacterCompanion(pchar, sld);
								AddPassenger(pchar, sld, false);
							}
							bOk = true;
						}
					}
				}				
				if (bOk)
				{
					link.l1 = "Да. Корабль стоит в порту на рейде. Можете забирать.";
					link.l1.go = "SeekShip_good";
				}
				else
				{
					link.l1 = "Я продолжу поиски, ждите.";
					link.l1.go = "exit";
				}
				link.l2 = "Хочу отказаться от выполнения вашего поручения.";
				link.l2.go = "SeekShip_break";
				break;
			}
			//<-- проверка миниквестов начальника порта. 

			//--> дача миниквестов начальника порта. 
			if (rand(2) < 2 && pchar.questTemp.different == "free" && GetNpcQuestPastDayWOInit(npchar, "quest.meeting") > 7)
			{
				dialog.text = LinkRandPhrase("Да, чёрт возьми! У меня есть для вас работа!", 
					"Ха! Вы как нельзя вовремя! У меня есть одна проблема, требующая разрешения.", 
					"Ещё бы! Конечно, у меня есть работа! Проблемы, знаете ли, просто задавили...");
				link.l1 = "Излагайте суть дела, " + GetAddress_FormToNPC(NPChar) + ".";
				link.l1.go = "PortmanQuest";
				SaveCurrentNpcQuestDateParam(npchar, "quest.meeting");
				break;
			}
			
			// Warship 25.07.09 Генер "Сгоревшее судно"
			if(dRand(4) == 2 && !CheckAttribute(NPChar, "Quest.BurntShip"))
			{
				dialog.text = "Боже! Капитан " + GetFullName(PChar) + ", вы как нельзя вовремя! Приключилось такое несчастье, такое несчастье... У нас на рейде сгорело судно, оставленное на попечение портового управления! По недосмотру охранной команды сгорело... по самую ватерлинию...\n" +
					"Господи, за что же мне такое наказание-то? Ведь столько лет верой и правдой...";
				link.l1 = "Хм, эка невидаль - судно сгорело. А страховые договора на что? Или вы его не застраховали, в целях экономии? А теперь рады бы локоток укусить, да...";
				link.l1.go = "BurntShip4";
				link.l2 = "С такими вопросами вам за помощью на верфь нужно, а не ко мне. За пару месяцев вам хоть старое восстановят, хоть новое соорудят. Я не судостроитель"+ GetSexPhrase("","ница") +", так что извините, не по адресу...";
				link.l2.go = "BurntShip2";
				break;
			}
			//<-- дача миниквестов начальника порта.

			dialog.text = "Губернатор радеет за благополучие города - у него всегда есть работа. Потом, в таверне могут быть заинтересованные купцы, ну и магазин иногда фрахтует капитанов.";
			Link.l1 = "Ещё один вопрос.";
			Link.l1.go = "node_2";
			Link.l2 = "Благодарю. До свидания.";
			Link.l2.go = "exit";
		break;

///Jason-----------------------новые генераторы накопительного типа для портмана----------------------------
		int iTime, idaysQty, iGoods, iGoodsQty, amount;
		case "Work_check"://фейс-контроль - общая проверка профпригодности ГГ и выбор задания
			ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
			if(sti(Pchar.Ship.Type) != SHIP_NOTUSED && ok)//проверка на наличие корабля в порту
			{
				if (!CheckAttribute(npchar, "work_date") || GetNpcQuestPastDayParam(npchar, "work_date") >= 2)//проверка повтора
				{
					if (sti(NPChar.nation) != PIRATE && GetNationRelation2MainCharacter(sti(NPChar.nation)) == RELATION_ENEMY)//проверка межнациональных отношений
					{
						dialog.text = RandPhraseSimple("Здесь нет работы для тех, кто ходит под флагом " + NationNameGenitive(sti(pchar.nation)) + "! Покиньте мой кабинет немедленно!", "Я не намерен сотрудничать с " + NationNameAblative(sti(pchar.nation)) + ". Вон отсюда!");
						link.l1 = RandPhraseSimple("Хм, ваше право...", "Ну, как знаешь...");
						link.l1.go = "exit";
						break;
					}
					if (makeint(PChar.reputation.nobility) < 41) // проверка репутации ГГ
					{
						dialog.text = "Ваша репутация не внушает мне доверия. Я не намерен с вами сотрудничать. Всего доброго.";
						link.l1 = "Чего-о?! Да врут всё люди.";
						link.l1.go = "exit";
						break;
					}
					if (GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) < 5)//при низком авторитете не даем
					{
						dialog.text = "Не хочу вас обидеть, капитан, но... я опасаюсь, что вы не сможете выполнить моё поручение - у вас слишком мало опыта. Я не могу заключить с вами контракт.";
						link.l1 = "Понятно. Как скажете.";
						link.l1.go = "exit";
						break;
					}
					dialog.Text = "Хм... Ну, это смотря какого рода работа вас интересует.";
					link.l1 = "Я бы хотел предложить вам зафрахтовать моё судно для перевозки грузов.";
					Link.l1.go = "Fraht_begin";
					link.l2 = "Ну, может вы что-нибудь сами предложите?";
					Link.l2.go = "Check_other";
				}
				else
				{
					dialog.Text = "Сегодня уже ничего нет. Зайдите в другой день.";
					link.l1 = "Хорошо.";
					Link.l1.go = "exit";
				}
			}
			else
			{
				dialog.text = "Что-то я не вижу в порту вашего корабля. Встаньте на рейд и приходите ко мне снова - попробуем что-нибудь подобрать для вас.";
				link.l1 = "Хорошо, я так и сделаю."; 
				link.l1.go = "exit";
			}
		break;
	
		case "Check_other"://выбор между почтовым курьером, эскортом и ничем
		SaveCurrentNpcQuestDateParam(npchar, "work_date"); // mitrokosta безусловно сохраняем
		int nTask = 0;
		string tasks[10]; // mitrokosta сделал выбор задания расширяемым на тот случай если задания добавятся
		if (stf(RealShips[sti(pchar.Ship.Type)].SpeedRate) >= 15) {
			tasks[nTask] = "cureer";
			nTask++;
		}
		if (GetCompanionQuantity(pchar) < 3 && sti(RealShips[sti(pchar.Ship.Type)].BaseType) >= SHIP_BRIG && sti(RealShips[sti(pchar.Ship.Type)].BaseType) != SHIP_GALEON_L && sti(RealShips[sti(pchar.Ship.Type)].BaseType) != SHIP_PINNACE) {
			tasks[nTask] = "escort";
			nTask++;
		}
		if (nTask > 0 && drand(5) > 1) {
			string sTask = tasks[drand(nTask - 1)];
			switch (sTask) {
				case "cureer":
					if (pchar.questTemp.WPU.Postcureer == "begin" || pchar.questTemp.WPU.Postcureer == "late" || pchar.questTemp.WPU.Postcureer == "lost" || pchar.questTemp.WPU.Postcureer == "fail" || CheckAttribute(pchar, "questTemp.WPU.Postcureer.LevelUp")) { // если заняты
						dialog.text = "К сожалению, ничего такого вам предложить сегодня не могу. Зайдите через пару дней.";
						link.l1 = "Хорошо, я так и сделаю.";
						link.l1.go = "exit";
					} else { // если не заняты
						if (sti(pchar.questTemp.WPU.Postcureer.count) > 3 && drand(1) == 1) { //если 2 уровень
							dialog.text = "Так-так... Вы уже неоднократно и успешно выполняли работу почтового курьера, как мне известно. Пожалуй, задание, которое я предложу, будет вполне вам по силам.";
							link.l1 = "Слушаю вас внимательно, " + GetAddress_FormToNPC(NPChar) + ".";
							link.l1.go = "Postcureer_LevelUp";
						} else { // первый уровень
							dialog.text = "Я вижу, у вас быстрый корабль. Могу предложить работу в качестве почтового курьера - доставить корреспонденцию и деловые бумаги.";
							link.l1 = "Это интересно. Пожалуй, я согласен. Куда нужно отправиться?";
							link.l1.go = "Postcureer";
							link.l2 = "Спасибо, но такое занятие мне не по душе.";
							link.l2.go = "exit";
						}
					}
				break;

				case "escort":
					if (pchar.questTemp.WPU.Escort == "begin" || pchar.questTemp.WPU.Escort == "late" || pchar.questTemp.WPU.Escort == "win" || CheckAttribute(pchar, "questTemp.WPU.Escort.LevelUp")) { // если заняты
						dialog.text = "К сожалению, ничего такого вам предложить сегодня не могу. Зайдите через пару дней.";
						link.l1 = "Хорошо, я так и сделаю.";
						link.l1.go = "exit";
					} else { // если не заняты
						if (sti(pchar.questTemp.WPU.Escort.count) > 3 && drand(1) == 1) { // 2 уровень
							dialog.text = "Вы уже неоднократно и успешно выполняли работу по конвоированию торговых судов. У меня есть задание, которое я хотел бы поручить именно вам.";
							link.l1 = "Слушаю вас внимательно.";
							link.l1.go = "Escort_LevelUp";
						} else { // 1 уровень
							if (sti(RealShips[sti(pchar.Ship.Type)].BaseType) == SHIP_GALEON_H && 2500 - makeint(GetCharacterFreeSpace(pchar, GOOD_RUM)) < 0 && !CheckAttribute(pchar, "questTemp.WPU.Fraht.TargetPortmanID")) { // если на ТГ
								dialog.text = "У меня есть работа, как раз для вас. В нашем порту стоят на рейде два торговых судна. Они давно должны были отправиться в путь, но корабль сопровождения получил повреждения и починится еще не скоро\nВаш корабль идеально подходит для эскорта этих судов, так как мне необходимо разместить ещё дополнительную партию груза в вашем трюме. Оплата, безусловно, будет двойной - за фрахт и за сопровождение.";
								link.l1 = "Интересное предложение. Берусь!";
								link.l1.go = "escort_bonus";
								link.l2 = "Спасибо, но такое занятие мне не по душе.";
								link.l2.go = "exit";
							} else { // просто эскорт
								dialog.text = "У меня есть работа, как раз для вас. В нашем порту стоят на рейде два торговых судна - они нуждаются в корабле охранения. Я предлагаю вам осуществить их эскорт. Возьмётесь?";
								link.l1 = "Интересное предложение. Берусь!";
								link.l1.go = "escort";
								link.l2 = "Спасибо, но такое занятие мне не по душе.";
								link.l2.go = "exit";
							}
						}
					}
				break;
			}
			break;
		}
		//ничего не подошло
		dialog.text = "К сожалению, ничего такого вам предложить сегодня не могу. Зайдите через пару дней.";
		link.l1 = "Хорошо, я так и сделаю.";
		link.l1.go = "exit";
		break;

///--> ------фрахт со свободным выбором пункта назначения, оплаты и вида груза из предложенного списка---------

		case "Fraht_begin":
			if (drand(4) < 4)
			{
				if (pchar.questTemp.WPU.Fraht == "begin" || pchar.questTemp.WPU.Fraht == "late" || pchar.questTemp.WPU.Fraht == "lost" || CheckAttribute(pchar, "questTemp.WPU.Escort.Bonus"))//проверка на занятость
				{
					dialog.Text = "Но мне известно, что ваше судно уже зафрахтовано. Я не могу дать вам более фрахтов. Выполняйте взятые обязательства.";
					link.l1 = "Да, пожалуй, вы правы.";
					Link.l1.go = "exit";
					break;
				}
				if (1500 - makeint(GetCharacterFreeSpace(pchar, GOOD_RUM)) > 0)//мало места - не даем
				{
					dialog.text = "У вас слишком мало места в трюмах. Для фрахта мне нужен более вместительный корабль, чем ваш. Обратитесь в магазин - местный купец частенько нанимает капитанов для перевозки небольших партий грузов.";
					link.l1 = "Понятно. Как скажете.";
					link.l1.go = "exit";
					break;
				}
				if (pchar.questTemp.WPU.Fraht.count > 3 && rand(1) == 0)
				{
					dialog.text = "Сейчас ничего подходящего нет. Но вы уже неоднократно и успешно выполняли задания по перевозке грузов. У меня есть определённая работа, которую я бы хотел поручить именно вам.";
					link.l1 = "Слушаю вас внимательно. Что за работа?";
					link.l1.go = "Fraht_LevelUp";
					break;
				}
				dialog.Text = "Ну что же, могу предложить несколько вариантов фрахта.";
				link.l1 = "Давайте посмотрим.";
				Link.l1.go = "Fraht_choise";
			}
			else
			{
				dialog.Text = "Сегодня уже ничего по фрахтам нет. Зайдите в другой день.";
				link.l1 = "Хорошо.";
				Link.l1.go = "exit";
			}
		break;
	
		int iFrahtGoods1, iFrahtGoods2, iFrahtGoods3, iFrahtGoods;
		int iFrahtGoodsQty1, iFrahtGoodsQty2, iFrahtGoodsQty3;
		case "Fraht_choise":
			//выбираем города
			pchar.questTemp.WPU.Fraht.City1 = findCurrentCity1(npchar);
			pchar.questTemp.WPU.Fraht.City2 = findCurrentCity2(npchar);
			pchar.questTemp.WPU.Fraht.City3 = findCurrentCity3(npchar);
			//выбираем товары
			iFrahtGoods1 = drand(GOOD_PAPRIKA);
			iFrahtGoods2 = drand(GOOD_PAPRIKA-3);
			iFrahtGoods3 = drand(GOOD_PAPRIKA-7);
			pchar.questTemp.WPU.Fraht.Goods1 = iFrahtGoods1;
			pchar.questTemp.WPU.Fraht.Goods2 = iFrahtGoods2;
			pchar.questTemp.WPU.Fraht.Goods3 = iFrahtGoods3;
			//определим количество
			iFrahtGoodsQty1 = makeint(GetCharacterFreeSpace(pchar, iFrahtGoods1))/(1+frand(0.5));
			iFrahtGoodsQty2 = makeint(GetCharacterFreeSpace(pchar, iFrahtGoods2))/(1+frand(0.5));
			iFrahtGoodsQty3 = makeint(GetCharacterFreeSpace(pchar, iFrahtGoods3))/(1+frand(0.5));
			if (sti(iFrahtGoodsQty1) > 10000) iFrahtGoodsQty1 = 10000 + rand(500);
			if (sti(iFrahtGoodsQty2) > 10000) iFrahtGoodsQty2 = 10000 + rand(500);
			if (sti(iFrahtGoodsQty3) > 10000) iFrahtGoodsQty3 = 10000 + rand(500);
			pchar.questTemp.WPU.Fraht.GoodsQty1 = iFrahtGoodsQty1;
			pchar.questTemp.WPU.Fraht.GoodsQty2 = iFrahtGoodsQty2;
			pchar.questTemp.WPU.Fraht.GoodsQty3 = iFrahtGoodsQty3;
			pchar.questTemp.WPU.Fraht.StartCity = npchar.city;//город квестодателя
			pchar.questTemp.WPU.Fraht.Chance = rand(4);//форс-мажор
			//определим сроки с учетом рандома
			int daysQty1 = GetMaxDaysFromIsland2Island(GetArealByCityName(pchar.questTemp.WPU.Fraht.StartCity), GetArealByCityName(pchar.questTemp.WPU.Fraht.City1));
			int daysQty2 = GetMaxDaysFromIsland2Island(GetArealByCityName(pchar.questTemp.WPU.Fraht.StartCity), GetArealByCityName(pchar.questTemp.WPU.Fraht.City2));
			int daysQty3 = GetMaxDaysFromIsland2Island(GetArealByCityName(pchar.questTemp.WPU.Fraht.StartCity), GetArealByCityName(pchar.questTemp.WPU.Fraht.City3));
			pchar.questTemp.WPU.Fraht.DaysQty1 = makeint(sti(daysQty1)*(frand(1.3)+0.7));
			pchar.questTemp.WPU.Fraht.DaysQty2 = makeint(sti(daysQty2)*(frand(1.3)+0.7));
			pchar.questTemp.WPU.Fraht.DaysQty3 = makeint(sti(daysQty3)*(frand(1.3)+0.7));
			//установим цену исходя из объема груза, дальности и сроков
			pchar.questTemp.WPU.Fraht.Money1 = (makeint((sti(iFrahtGoodsQty1) * sti(Goods[iFrahtGoods1].Weight) / sti(Goods[iFrahtGoods1].Units))))*(sti(daysQty1)*2)*sti(daysQty1)/sti(pchar.questTemp.WPU.Fraht.DaysQty1);
			pchar.questTemp.WPU.Fraht.Money2 = (makeint((sti(iFrahtGoodsQty2) * sti(Goods[iFrahtGoods2].Weight) / sti(Goods[iFrahtGoods2].Units))))*(sti(daysQty2)*2)*sti(daysQty2)/sti(pchar.questTemp.WPU.Fraht.DaysQty2);
			pchar.questTemp.WPU.Fraht.Money3 = (makeint((sti(iFrahtGoodsQty3) * sti(Goods[iFrahtGoods3].Weight) / sti(Goods[iFrahtGoods3].Units))))*(sti(daysQty3)*2)*sti(daysQty3)/sti(pchar.questTemp.WPU.Fraht.DaysQty3);
			if (drand(5) < 4)//три варианта
			{
				dialog.text = "Есть следующие варианты:\n" +
					"груз " + GetGoodsNameAlt(iFrahtGoods1)+ " в количестве " + FindRussianQtyString(iFrahtGoodsQty1) + " в город " + XI_ConvertString("Colony" + pchar.questTemp.WPU.Fraht.City1) + ", за " +  FindRussianDaysString(pchar.questTemp.WPU.Fraht.DaysQty1) + ". Оплата - " + FindRussianMoneyString(sti(pchar.questTemp.WPU.Fraht.Money1)) + "\nгруз " + GetGoodsNameAlt(iFrahtGoods2)+ " в количестве " + FindRussianQtyString(iFrahtGoodsQty2) + " в город " + XI_ConvertString("Colony" + pchar.questTemp.WPU.Fraht.City2) + ", за " +  FindRussianDaysString(pchar.questTemp.WPU.Fraht.DaysQty2) + ". Оплата - " + FindRussianMoneyString(sti(pchar.questTemp.WPU.Fraht.Money2)) + "\nгруз " + GetGoodsNameAlt(iFrahtGoods3)+ " в количестве " + FindRussianQtyString(iFrahtGoodsQty3) + " в город " + XI_ConvertString("Colony" + pchar.questTemp.WPU.Fraht.City3) + ", за " +  FindRussianDaysString(pchar.questTemp.WPU.Fraht.DaysQty3) + ". Оплата - " + FindRussianMoneyString(sti(pchar.questTemp.WPU.Fraht.Money3)) + "\nЧто выбираете?";
				Link.l1 = "Я выбираю первый вариант - фрахт до города " + XI_ConvertString("Colony" + pchar.questTemp.WPU.Fraht.City1) + " с грузом " + GetGoodsNameAlt(iFrahtGoods1)+ ".";
				Link.l1.go = "Fraht_Choise_1";
				Link.l2 = "Я выбираю второй вариант - фрахт до города " + XI_ConvertString("Colony" + pchar.questTemp.WPU.Fraht.City2) + " с грузом " + GetGoodsNameAlt(iFrahtGoods2)+ ".";
				Link.l2.go = "Fraht_Choise_2";
				Link.l3 = "Я выбираю третий вариант - фрахт до города " + XI_ConvertString("Colony" + pchar.questTemp.WPU.Fraht.City3) + " с грузом " + GetGoodsNameAlt(iFrahtGoods3)+ ".";
				Link.l3.go = "Fraht_Choise_3";
			}
			else //два варианта
			{
				dialog.text = "Есть следующие варианты:\n" +
					"груз " + GetGoodsNameAlt(iFrahtGoods1)+ " в количестве " + FindRussianQtyString(iFrahtGoodsQty1) + " в город " + XI_ConvertString("Colony" + pchar.questTemp.WPU.Fraht.City1) + ", за " +  FindRussianDaysString(pchar.questTemp.WPU.Fraht.DaysQty1) + ". Оплата - " + FindRussianMoneyString(sti(pchar.questTemp.WPU.Fraht.Money1)) + "\nгруз " + GetGoodsNameAlt(iFrahtGoods2)+ " в количестве " + FindRussianQtyString(iFrahtGoodsQty2) + " в город " + XI_ConvertString("Colony" + pchar.questTemp.WPU.Fraht.City2) + ", за " +  FindRussianDaysString(pchar.questTemp.WPU.Fraht.DaysQty2) + ". Оплата - " + FindRussianMoneyString(sti(pchar.questTemp.WPU.Fraht.Money2)) + "\nЧто выбираете?";
				Link.l1 = "Я выбираю первый вариант - фрахт до города " + XI_ConvertString("Colony" + pchar.questTemp.WPU.Fraht.City1) + " с грузом " + GetGoodsNameAlt(iFrahtGoods1)+ ".";
				Link.l1.go = "Fraht_Choise_1";
				Link.l2 = "Я выбираю второй вариант - фрахт до города " + XI_ConvertString("Colony" + pchar.questTemp.WPU.Fraht.City2) + " с грузом " + GetGoodsNameAlt(iFrahtGoods2)+ ".";
				Link.l2.go = "Fraht_Choise_2";
			}
			Link.l4 = "К сожалению, мне ничего не подходит.";
			Link.l4.go = "exit";
			SaveCurrentNpcQuestDateParam(npchar, "work_date");
		break;
	
		case "Fraht_Choise_1":
			dialog.text = "Ну что же, замечательно. Сейчас оформим документы. Готовьте судно под погрузку.";
			link.l1 = "Всё будет сделано в лучшем виде!";
			link.l1.go = "Fraht_Forcemajor";
			AddCharacterGoods(pchar, sti(pchar.questTemp.WPU.Fraht.Goods1), sti(pchar.questTemp.WPU.Fraht.GoodsQty1));
			iFrahtGoods1 = pchar.questTemp.WPU.Fraht.Goods1;
			ReOpenQuestHeader("Fraht");
			AddQuestRecord("Fraht", "1");
			AddQuestUserData("Fraht", "sGoods", GetGoodsNameAlt(iFrahtGoods1));
			AddQuestUserData("Fraht", "sGoodQty", FindRussianQtyString(sti(pchar.questTemp.WPU.Fraht.GoodsQty1)));
			AddQuestUserData("Fraht", "sDay", FindRussianDaysString(sti(pchar.questTemp.WPU.Fraht.DaysQty1)));
			AddQuestUserData("Fraht", "sMoney", FindRussianMoneyString(sti(pchar.questTemp.WPU.Fraht.Money1)));
			AddQuestUserData("Fraht", "sStartCity", XI_ConvertString("Colony"+pchar.questTemp.WPU.Fraht.StartCity+"Gen"));
			AddQuestUserData("Fraht", "sTargetColony",XI_ConvertString("Colony"+pchar.questTemp.WPU.Fraht.City1+"Gen"));
			SetFunctionTimerCondition("FrahtTime_Over", 0, 0, sti(pchar.questTemp.WPU.Fraht.DaysQty1), false);
			pchar.questTemp.WPU.Fraht.TargetPortmanID = pchar.questTemp.WPU.Fraht.City1+"_portman";
			pchar.questTemp.WPU.Fraht.GoodsAverigePrice = sti(Goods[iFrahtGoods1].Cost);//цена единицы товара
			pchar.questTemp.WPU.Fraht.GoodsAverigeCost = sti(Goods[iFrahtGoods1].Cost)*sti(pchar.questTemp.WPU.Fraht.GoodsQty1);//средняя стоимость товара
			pchar.questTemp.WPU.Fraht.Goods = sti(pchar.questTemp.WPU.Fraht.Goods1);
			pchar.questTemp.WPU.Fraht.GoodsQty = sti(pchar.questTemp.WPU.Fraht.GoodsQty1);
			pchar.questTemp.WPU.Fraht.Money = sti(pchar.questTemp.WPU.Fraht.Money1);
		break;
	
		case "Fraht_Choise_2":
			dialog.text = "Ну что же, замечательно. Сейчас оформим документы. Готовьте судно под погрузку.";
			link.l1 = "Всё будет сделано в лучшем виде!";
			link.l1.go = "Fraht_Forcemajor";
			AddCharacterGoods(pchar, sti(pchar.questTemp.WPU.Fraht.Goods2), sti(pchar.questTemp.WPU.Fraht.GoodsQty2));
			iFrahtGoods2 = pchar.questTemp.WPU.Fraht.Goods2;
			ReOpenQuestHeader("Fraht");
			AddQuestRecord("Fraht", "1");
			AddQuestUserData("Fraht", "sGoods", GetGoodsNameAlt(iFrahtGoods2));
			AddQuestUserData("Fraht", "sGoodQty", FindRussianQtyString(sti(pchar.questTemp.WPU.Fraht.GoodsQty2)));
			AddQuestUserData("Fraht", "sDay", FindRussianDaysString(sti(pchar.questTemp.WPU.Fraht.DaysQty2)));
			AddQuestUserData("Fraht", "sMoney", FindRussianMoneyString(sti(pchar.questTemp.WPU.Fraht.Money2)));
			AddQuestUserData("Fraht", "sStartCity", XI_ConvertString("Colony"+pchar.questTemp.WPU.Fraht.StartCity+"Gen"));
			AddQuestUserData("Fraht", "sTargetColony",XI_ConvertString("Colony"+pchar.questTemp.WPU.Fraht.City2+"Gen"));
			SetFunctionTimerCondition("FrahtTime_Over", 0, 0, sti(pchar.questTemp.WPU.Fraht.DaysQty2), false);
			pchar.questTemp.WPU.Fraht.TargetPortmanID = pchar.questTemp.WPU.Fraht.City2+"_portman";
			pchar.questTemp.WPU.Fraht.GoodsAverigePrice = sti(Goods[iFrahtGoods2].Cost);//цена единицы товара
			pchar.questTemp.WPU.Fraht.GoodsAverigeCost = sti(Goods[iFrahtGoods2].Cost)*sti(pchar.questTemp.WPU.Fraht.GoodsQty2);//средняя стоимость товара
			pchar.questTemp.WPU.Fraht.Goods = sti(pchar.questTemp.WPU.Fraht.Goods2);
			pchar.questTemp.WPU.Fraht.GoodsQty = sti(pchar.questTemp.WPU.Fraht.GoodsQty2);
			pchar.questTemp.WPU.Fraht.Money = sti(pchar.questTemp.WPU.Fraht.Money2);
		break;
	
		case "Fraht_Choise_3":
			dialog.text = "Ну что же, замечательно. Сейчас оформим документы. Готовьте судно под погрузку.";
			link.l1 = "Всё будет сделано в лучшем виде!";
			link.l1.go = "Fraht_Forcemajor";
			AddCharacterGoods(pchar, sti(pchar.questTemp.WPU.Fraht.Goods3), sti(pchar.questTemp.WPU.Fraht.GoodsQty3));
			iFrahtGoods3 = pchar.questTemp.WPU.Fraht.Goods3;
			ReOpenQuestHeader("Fraht");
			AddQuestRecord("Fraht", "1");
			AddQuestUserData("Fraht", "sGoods", GetGoodsNameAlt(iFrahtGoods3));
			AddQuestUserData("Fraht", "sGoodQty", FindRussianQtyString(sti(pchar.questTemp.WPU.Fraht.GoodsQty3)));
			AddQuestUserData("Fraht", "sDay", FindRussianDaysString(sti(pchar.questTemp.WPU.Fraht.DaysQty3)));
			AddQuestUserData("Fraht", "sMoney", FindRussianMoneyString(sti(pchar.questTemp.WPU.Fraht.Money3)));
			AddQuestUserData("Fraht", "sStartCity", XI_ConvertString("Colony"+pchar.questTemp.WPU.Fraht.StartCity+"Gen"));
			AddQuestUserData("Fraht", "sTargetColony",XI_ConvertString("Colony"+pchar.questTemp.WPU.Fraht.City3+"Gen"));
			SetFunctionTimerCondition("FrahtTime_Over", 0, 0, sti(pchar.questTemp.WPU.Fraht.DaysQty3), false);
			pchar.questTemp.WPU.Fraht.TargetPortmanID = pchar.questTemp.WPU.Fraht.City3+"_portman";
			pchar.questTemp.WPU.Fraht.GoodsAverigePrice = sti(Goods[iFrahtGoods3].Cost);//цена единицы товара
			pchar.questTemp.WPU.Fraht.GoodsAverigeCost = sti(Goods[iFrahtGoods3].Cost)*sti(pchar.questTemp.WPU.Fraht.GoodsQty3);//средняя стоимость товара
			pchar.questTemp.WPU.Fraht.Goods = sti(pchar.questTemp.WPU.Fraht.Goods3);
			pchar.questTemp.WPU.Fraht.GoodsQty = sti(pchar.questTemp.WPU.Fraht.GoodsQty3);
			pchar.questTemp.WPU.Fraht.Money = sti(pchar.questTemp.WPU.Fraht.Money3);
		break;
	
		case "Fraht_Forcemajor":
			pchar.questTemp.WPU.Fraht = "begin";
			sld = characterFromId(pchar.questTemp.WPU.Fraht.TargetPortmanID);
			pchar.questTemp.WPU.Fraht.Nation = sld.nation;//нация получателя
			pchar.questTemp.WPU.Current.TargetIslandID = GetCharacterCurrentIslandId(sld);//ИД целевого ареала
			pchar.questTemp.WPU.Fraht.TargetCity = FindTownOnIsland(pchar.questTemp.WPU.Current.TargetIslandID);
			pchar.questTemp.WPU.Fraht.count = sti(pchar.questTemp.WPU.Fraht.count)+1;//считаем сделанные фрахты
			if (pchar.questTemp.WPU.Fraht.Chance > 3) TraderHunterOnMap();//запуск ДУ на глобалке
			if (pchar.questTemp.WPU.Fraht.Chance == 2) FrahtHunterOnSea();//создание ДУ в акватории
			DialogExit();
		break;
	
		case "Fraht_complete":
		ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
		if(sti(Pchar.Ship.Type) != SHIP_NOTUSED && ok)//проверка на наличие корабля в порту
		{
			iFrahtGoods = makeint(pchar.questTemp.WPU.Fraht.Goods);
			amount = sti(pchar.questTemp.WPU.Fraht.GoodsQty) - GetSquadronGoods(pchar, sti(pchar.questTemp.WPU.Fraht.Goods));
			if (amount > 0)
			{
				dialog.text = "Давайте посмотрим. Вы должны были привезти груз " + GetGoodsNameAlt(iFrahtGoods)+ " в количестве " + FindRussianQtyString(pchar.questTemp.WPU.Fraht.GoodsQty) + ". Но я вижу, что вы привезли не весь груз -  не хватает " + FindRussianQtyString(sti(amount)) + " товара.";
				link.l1 = "Тысяча акул! Проклятые крысы сожрали! Не беспокойтесь, " + GetAddress_FormToNPC(NPChar) + ", я докуплю недостающее количество и сдам груз в полном комплекте.";
				link.l1.go = "Fraht_complete_3";
				break;
			}
			dialog.text = "Давайте посмотрим. Вы должны были привезти груз " + GetGoodsNameAlt(iFrahtGoods)+ " в количестве " + FindRussianQtyString(pchar.questTemp.WPU.Fraht.GoodsQty) + ". Так?";
			link.l1 = "Совершенно верно, " + GetAddress_FormToNPC(NPChar) + ".";
			link.l1.go = "Fraht_complete_1";
		}
		else
		{
			dialog.text = "Что-то я не вижу в порту вашего корабля. Встаньте на рейд и приходите ко мне снова - тогда и поговорим.";
			link.l1 = "Хорошо, я так и сделаю.";
			link.l1.go = "exit";
		}
		break;
	
		case "Fraht_complete_1":
			if (pchar.questTemp.WPU.Fraht == "late")//опоздали
			{
				iTime = makeint(GetQuestPastDayParam("questTemp.Fraht.Late"))+1;
				pchar.questTemp.WPU.Fraht.DayLate = iTime;
				pchar.questTemp.WPU.Fraht.PercentLate = iTime/0.2;
				pchar.questTemp.WPU.Fraht.Money = makeint(sti(pchar.questTemp.WPU.Fraht.Money) - sti(pchar.questTemp.WPU.Fraht.Money)*sti(pchar.questTemp.WPU.Fraht.PercentLate)/100);//снижаем оплату согласно числа дней опоздания
				dialog.text = "Хм... Но вы опоздали на " + FindRussianDaysString(iTime)+ ". Поэтому я вынужден снизить размер оплаты за фрахт. Согласно договору, штраф составляет 5 процентов от суммы за каждый день просрочки. Получите, пожалуйста, ваши " + FindRussianMoneyString(sti(pchar.questTemp.WPU.Fraht.Money)) + ", и впредь постарайтесь выполнять условия договора в точности.";
				link.l1 = "Спасибо и на этом.";
				link.l1.go = "Fraht_complete_2";
				break;
			}
			dialog.text = "Спасибо за проделанную работу. Получите вашу оплату - " + FindRussianMoneyString(sti(pchar.questTemp.WPU.Fraht.Money)) + ".";
			link.l1 = "Спасибо!";
			link.l1.go = "Fraht_complete_2";
		break;
	
		case "Fraht_complete_2":
			if (pchar.questTemp.WPU.Fraht == "begin")
			{
				pchar.quest.FrahtTime_Over.over = "yes";
				AddQuestRecord("Fraht", "2");
			}
			else
			{
				pchar.quest.FrahtTime_FullOver.over = "yes";//снять второй таймер
				pchar.questTemp.WPU.Fraht.count = sti(pchar.questTemp.WPU.Fraht.count)-1;//опоздавший рейс не засчитываем
				AddQuestRecord("Fraht", "4");
				AddQuestUserData("Fraht", "sDay", FindRussianDaysString(pchar.questTemp.WPU.Fraht.DayLate));
				AddQuestUserData("Fraht", "sMoney", FindRussianMoneyString(sti(pchar.questTemp.WPU.Fraht.Money)));
			}
			RemoveCharacterGoods(pchar, sti(pchar.questTemp.WPU.Fraht.Goods), sti(pchar.questTemp.WPU.Fraht.GoodsQty));
			AddMoneyToCharacter(pchar, sti(pchar.questTemp.WPU.Fraht.Money));
			CloseQuestHeader("Fraht");
			DeleteAttribute(pchar, "questTemp.WPU.Fraht.TargetPortmanID");
			DeleteAttribute(pchar, "questTemp.WPU.Current.TargetIslandID");
			pchar.questTemp.WPU.Fraht = "complete";
			SaveCurrentNpcQuestDateParam(npchar, "work_date");
			AddCharacterExpToSkill(pchar, "Sailing", 100);//навигация
			AddCharacterExpToSkill(pchar, "Commerce", 100);//торговля
			AddCharacterExpToSkill(pchar, "Leadership", 50);//авторитет
			AddCharacterExpToSkill(pchar, "Fortune", 50);//везение
			ChangeCharacterComplexReputation(pchar,"nobility", 2);
			ChangeCharacterNationReputation(pchar, sti(pchar.questTemp.WPU.Fraht.Nation), 2);
			Group_DeleteGroup("Fraht_Attack");
			DialogExit();
		break;
	
		case "Fraht_complete_bad":
			dialog.text = "Привезли груз? Да нам пришлось его самим закупать и отдавать получателю. И, знаете, нам это недёшево обошлось. Если хотите восстановить свою деловую репутацию - вы будете должны компенсировать наши убытки и оплатить неустойку. Груз можете оставить себе, он нам уже не нужен.";
			link.l1 = "Да, безусловно. Назовите сумму.";
			link.l1.go = "Fraht_complete_bad_1";
		break;
	
		case "Fraht_complete_bad_1":
			pchar.questTemp.WPU.Fraht.GoodsAverigeCost = sti(pchar.questTemp.WPU.Fraht.GoodsAverigeCost)*3;
			dialog.text = "Стоимость товара в трёхкратном размере. Это составит " + FindRussianMoneyString(sti(pchar.questTemp.WPU.Fraht.GoodsAverigeCost)) + ".";
			if (sti(Pchar.money) >= sti(pchar.questTemp.WPU.Fraht.GoodsAverigeCost))
			{
				link.l1 = "Недёшево. Но я понимаю, бизнес есть бизнес. Вот ваши деньги.";
				link.l1.go = "Fraht_complete_pay";
			}
			link.l2 = "Да вы с ума сошли! Требовать такую кучу денег - это верх жадности! Ничего вы от меня не получите!";
			link.l2.go = "Fraht_complete_fail";
		break;
	
		case "Fraht_complete_pay":
			AddMoneyToCharacter(pchar, -sti(pchar.questTemp.WPU.Fraht.GoodsAverigeCost));
			dialog.text = "Ну что же, разумное решение. Теперь я вижу, что имею дело с серьёзным человеком. Думаю, что мы сможем с вами работать и дальше.";
			link.l1 = "Спасибо. Мне пора идти.";
			link.l1.go = "exit";
			ChangeCharacterComplexReputation(pchar,"nobility", 12);
			ChangeCharacterNationReputation(pchar, sti(pchar.questTemp.WPU.Fraht.Nation), 30);
			if (CheckAttribute(pchar, "questTemp.WPU.Escort.Bonus"))
			{
				AddQuestRecord("Escort", "8");
				AddQuestUserData("Escort", "sMoney", FindRussianMoneyString(sti(pchar.questTemp.WPU.Fraht.GoodsAverigeCost)));
				CloseQuestHeader("Escort");
				pchar.questTemp.WPU.Escort = "complete";
				DeleteAttribute(pchar, "questTemp.WPU.Escort.TargetPortmanID");
				DeleteAttribute(pchar, "questTemp.WPU.Escort.Bonus");
			}
			else
			{
				AddQuestRecord("Fraht", "6");
				AddQuestUserData("Fraht", "sMoney", FindRussianMoneyString(sti(pchar.questTemp.WPU.Fraht.GoodsAverigeCost)));
				CloseQuestHeader("Fraht");
				pchar.questTemp.WPU.Fraht = "complete";
				DeleteAttribute(pchar, "questTemp.WPU.Fraht.TargetPortmanID");
			}
			DeleteAttribute(pchar, "questTemp.WPU.Current.TargetIslandID");
			SaveCurrentNpcQuestDateParam(npchar, "work_date");
			AddCharacterExpToSkill(pchar, "Sailing", 100);//навигация
			AddCharacterExpToSkill(pchar, "Commerce", 50);//торговля
			AddCharacterExpToSkill(pchar, "Leadership", 70);//авторитет
			AddCharacterExpToSkill(pchar, "Fortune", 70);//везение
		break;
	
		case "Fraht_complete_fail":
			dialog.text = "Значит, вот так... Ну что же, тогда более даже не смейте обращаться ни по каким вопросам в портовые управления " + NationNameGenitive(sti(pchar.questTemp.WPU.Fraht.Nation)) + "! Убирайтесь!";
			link.l1 = "Невелика потеря...";
			link.l1.go = "exit";
			if (CheckAttribute(pchar, "questTemp.WPU.Escort.Bonus"))
			{
				AddQuestRecord("Escort", "9");
				AddQuestUserData("Escort", "sMoney", FindRussianMoneyString(sti(pchar.questTemp.WPU.Fraht.GoodsAverigeCost)));
				CloseQuestHeader("Escort");
				pchar.questTemp.WPU.Escort = "complete";
				DeleteAttribute(pchar, "questTemp.WPU.Escort.TargetPortmanID");
				DeleteAttribute(pchar, "questTemp.WPU.Escort.Bonus");
			}
			else
			{
				AddQuestRecord("Fraht", "7");
				CloseQuestHeader("Fraht");
				DeleteAttribute(pchar, "questTemp.WPU.Fraht.TargetPortmanID");
			}
			DeleteAttribute(pchar, "questTemp.WPU.Current.TargetIslandID");
			pchar.questTemp.WPU.Fraht = "fail";
			ChangeCharacterComplexReputation(pchar,"nobility", -10);
		break;
	
		case "Fraht_complete_3":
			dialog.text = "Поторопитесь, получатель уже знает, что ваше судно прибыло, и переживает за свой товар.";
			link.l1 = "Тогда не буду терять времени!";
			link.l1.go = "exit";
		break;
	//фрахт <--
	
/// -------------------------------работа курьером по доставке почты-------------------------------------

		case "Postcureer":
			pchar.questTemp.WPU.Postcureer.City = findCurrentCity2(npchar);
			pchar.questTemp.WPU.Postcureer.StartCity = npchar.city;//город квестодателя
			pchar.questTemp.WPU.Postcureer.Chance = rand(4);//форс-мажор
			idaysQty = GetMaxDaysFromIsland2Island(GetArealByCityName(pchar.questTemp.WPU.Postcureer.StartCity), GetArealByCityName(pchar.questTemp.WPU.Postcureer.City));
			pchar.questTemp.WPU.Postcureer.DaysQty = makeint(sti(idaysQty)*(frand(0.3)+0.7)); 
			if (sti(pchar.questTemp.WPU.Postcureer.DaysQty) == 1) pchar.questTemp.WPU.Postcureer.DaysQty = 2;
			pchar.questTemp.WPU.Postcureer.Money = (sti(idaysQty)*1000)*sti(idaysQty)/sti(pchar.questTemp.WPU.Postcureer.DaysQty)*(1+frand(0.2));
			dialog.text = "Необходимо доставить вот этот пакет в портовое управление города " + XI_ConvertString("Colony" + pchar.questTemp.WPU.Postcureer.City) + ", за " +  FindRussianDaysString(pchar.questTemp.WPU.Postcureer.DaysQty) + ", и как можно быстрее. Оплата - " + FindRussianMoneyString(sti(pchar.questTemp.WPU.Postcureer.Money))".";
			link.l1 = "Я согласен!";
			link.l1.go = "Postcureer_1";
			link.l2 = "Гм... но мне совсем в другую сторону. Вынужден отказаться.";
			link.l2.go = "exit";
		break;
	
		case "Postcureer_1":
			dialog.text = "Замечательно! Очень на вас рассчитываю. Получите, пожалуйста, пакет.";
			link.l1 = "Уже выхожу в море!";
			link.l1.go = "exit";
			GiveItem2Character(pchar, "PostLetters");
			pchar.questTemp.WPU.Postcureer = "begin";
			pchar.questTemp.WPU.Postcureer.TargetPortmanID = pchar.questTemp.WPU.Postcureer.City +"_portman";//ИД портмана
			sld = characterFromId(pchar.questTemp.WPU.Postcureer.TargetPortmanID);
			pchar.questTemp.WPU.Postcureer.Nation = sld.nation;//нация получателя
			pchar.questTemp.WPU.Current.TargetIslandID = GetCharacterCurrentIslandId(sld);//ИД целевого ареала
			pchar.questTemp.WPU.Postcureer.EnemyNation = GetEnemyNationToMainCharacter();//вражеская нация
			while (sti(pchar.questTemp.WPU.Postcureer.EnemyNation) == PIRATE)
			{
				pchar.questTemp.WPU.Postcureer.EnemyNation = GetEnemyNationToMainCharacter();
			}
			pchar.questTemp.WPU.Postcureer.count = sti(pchar.questTemp.WPU.Postcureer.count)+1;//считаем сделанные доставки
			//запустить регату при счетчике > 4
			if (!CheckAttribute(pchar, "questTemp.RegataGo") && sti(pchar.questTemp.WPU.Postcureer.count) > 4)
			{
				pchar.questTemp.RegataGo = "true";
				pchar.questTemp.Regata.CureerCity = FindFriendCityToMC(true);//город, в котором вестовой подойдет
				if (pchar.questTemp.Regata.CureerCity == "PortRoyal") pchar.questTemp.Regata.CureerCity = "SentJons";
				pchar.quest.Regata_Cureer.win_condition.l1 = "location";
				pchar.quest.Regata_Cureer.win_condition.l1.location = pchar.questTemp.Regata.CureerCity+"_town";
				pchar.quest.Regata_Cureer.function = "PrepareToRegata";
				log_testinfo(pchar.questTemp.Regata.CureerCity);
			}
			if (pchar.questTemp.WPU.Postcureer.Chance > 3) EnemyNationHunterOnMap(false);//запуск перехватчиков на глобалке
			if (pchar.questTemp.WPU.Postcureer.Chance == 2) FrahtHunterOnSea();//создание перехватчиков в акватории
			ReOpenQuestHeader("Postcureer");
			AddQuestRecord("Postcureer", "1");
			AddQuestUserData("Postcureer", "sDay", FindRussianDaysString(sti(pchar.questTemp.WPU.Postcureer.DaysQty)));
			AddQuestUserData("Postcureer", "sMoney", FindRussianMoneyString(sti(pchar.questTemp.WPU.Postcureer.Money)));
			AddQuestUserData("Postcureer", "sStartCity", XI_ConvertString("Colony"+pchar.questTemp.WPU.Postcureer.StartCity+"Gen"));
			AddQuestUserData("Postcureer", "sTargetColony",XI_ConvertString("Colony"+pchar.questTemp.WPU.Postcureer.City+"Gen"));
			SetFunctionTimerCondition("PostcureerTime_Over", 0, 0, sti(pchar.questTemp.WPU.Postcureer.DaysQty), false);
		break;
	
		case "Postcureer_complete":
			if (pchar.questTemp.WPU.Postcureer == "late")//опоздали
			{
				iTime = makeint(GetQuestPastDayParam("questTemp.Postcureer.Late"))+1;
				pchar.questTemp.WPU.Postcureer.DayLate = iTime;
				pchar.questTemp.WPU.Postcureer.PercentLate = iTime/0.1;
				pchar.questTemp.WPU.Postcureer.Money = makeint(sti(pchar.questTemp.WPU.Postcureer.Money) - sti(pchar.questTemp.WPU.Postcureer.Money)*sti(pchar.questTemp.WPU.Postcureer.PercentLate)/100);//снижаем оплату согласно числа дней опоздания
				dialog.text = "Хм... Но вы опоздали на " + FindRussianDaysString(iTime)+ ". Поэтому я вынужден снизить размер оплаты за работу. Согласно договору, штраф составляет 10 процентов от суммы за каждый день просрочки. Получите, пожалуйста, ваши " + FindRussianMoneyString(sti(pchar.questTemp.WPU.Postcureer.Money)) + ", и впредь постарайтесь выполнять условия договора в точности.";
				link.l1 = "Спасибо и на этом.";
				link.l1.go = "Postcureer_complete_1";
				break;
			}
			dialog.text = "Спасибо за проделанную работу. Получите вашу оплату - " + FindRussianMoneyString(sti(pchar.questTemp.WPU.Postcureer.Money)) + ".";
			link.l1 = "Спасибо!";
			link.l1.go = "Postcureer_complete_1";
		break;
	
		case "Postcureer_complete_1":
			if (pchar.questTemp.WPU.Postcureer == "begin")
			{
				pchar.quest.PostcureerTime_Over.over = "yes";
				AddQuestRecord("Postcureer", "2");
			}
			else
			{
				pchar.quest.PostcureerTime_FullOver.over = "yes";//снять второй таймер
				pchar.questTemp.WPU.Postcureer.count = sti(pchar.questTemp.WPU.Postcureer.count)-1;//опоздавший рейс не засчитываем
				AddQuestRecord("Postcureer", "4");
				AddQuestUserData("Postcureer", "sDay", FindRussianDaysString(pchar.questTemp.WPU.Postcureer.DayLate));
				AddQuestUserData("Postcureer", "sMoney", FindRussianMoneyString(sti(pchar.questTemp.WPU.Postcureer.Money)));
			}
			RemoveItems(PChar, "PostLetters", 1);
			AddMoneyToCharacter(pchar, sti(pchar.questTemp.WPU.Postcureer.Money));
			CloseQuestHeader("Postcureer");
			DeleteAttribute(pchar, "questTemp.WPU.Postcureer.TargetPortmanID");
			DeleteAttribute(pchar, "questTemp.WPU.Current.TargetIslandID");
			pchar.questTemp.WPU.Postcureer = "complete";
			AddCharacterExpToSkill(pchar, "Sailing", 100);//навигация
			AddCharacterExpToSkill(pchar, "Sneak", 100);//скрытность
			AddCharacterExpToSkill(pchar, "Leadership", 100);//авторитет
			AddCharacterExpToSkill(pchar, "Fortune", 100);//везение
			ChangeCharacterComplexReputation(pchar,"nobility", 2);
			ChangeCharacterNationReputation(pchar, sti(pchar.questTemp.WPU.Postcureer.Nation), 2);
			Group_DeleteGroup("Fraht_Attack");
			SaveCurrentNpcQuestDateParam(npchar, "work_date");
			DialogExit();
		break;
	
		case "Postcureer_complete_bad":
			dialog.text = "Ну и зачем она теперь нам? Люди её ждали чёрти когда, а вы привезли только сегодня. Ладно, давайте её сюда, может, на что ещё и сгодится. Как вы понимаете, ни о какой оплате не может быть и речи.";
			link.l1 = "Понимаю, конечно. Заберите вашу связку. Прощайте.";
			link.l1.go = "exit";
			RemoveItems(PChar, "PostLetters", 1);
			CloseQuestHeader("Postcureer");
			DeleteAttribute(pchar, "questTemp.WPU.Postcureer.TargetPortmanID");
			DeleteAttribute(pchar, "questTemp.WPU.Current.TargetIslandID");
			Group_DeleteGroup("Fraht_Attack");
			pchar.questTemp.WPU.Postcureer = "fail";
		break;
	
/// ---------------------------работа в качестве эскорта для торговых кораблей----------------------------

		case "escort":
			pchar.questTemp.WPU.Escort.ShipName1 = GenerateRandomNameToShip(sti(npchar.nation));//имена кораблей
			pchar.questTemp.WPU.Escort.ShipName2 = GenerateRandomNameToShip(sti(npchar.nation));
			pchar.questTemp.WPU.Escort.Goods1 = rand(GOOD_PAPRIKA);
			pchar.questTemp.WPU.Escort.Goods2 = rand(GOOD_PAPRIKA);
			pchar.questTemp.WPU.Escort.City = findCurrentCity1(npchar);//целевой город
			pchar.questTemp.WPU.Escort.StartCity = npchar.city;//город квестодателя
			pchar.questTemp.WPU.Escort.Chance = rand(4);//форс-мажор
			idaysQty = GetMaxDaysFromIsland2Island(GetArealByCityName(pchar.questTemp.WPU.Escort.StartCity), GetArealByCityName(pchar.questTemp.WPU.Escort.City));
			pchar.questTemp.WPU.Escort.DaysQty = makeint(sti(idaysQty)*(frand(0.5)+1)); 
			pchar.questTemp.WPU.Escort.Money = (sti(idaysQty)*2000)*sti(idaysQty)/sti(pchar.questTemp.WPU.Escort.DaysQty)*(1+frand(0.2));
			dialog.text = "Итак, необходимо сопроводить корабли '" + pchar.questTemp.WPU.Escort.ShipName1 + "' и '" + pchar.questTemp.WPU.Escort.ShipName2 + "' до города " + XI_ConvertString("Colony" + pchar.questTemp.WPU.Escort.City) + ", за " +  FindRussianDaysString(pchar.questTemp.WPU.Escort.DaysQty) + ". Оплата - " + FindRussianMoneyString(sti(pchar.questTemp.WPU.Escort.Money))". Оба корабля должны достичь пункта назначения в целости и сохранности. Корабли сдадите тамошнему служащему портового управления, оплату получите у него же.";
			link.l1 = "Задача ясна. Приступаю к выполнению?";
			link.l1.go = "escort_1";
			link.l2 = "Гм... но мне совсем в другую сторону. Вынужден отказаться.";
			link.l2.go = "exit";
		break;
	
		case "escort_1":
			dialog.text = "Приступайте. Корабли передаются под ваше командование.";
			link.l1 = "Отправляюсь в путь!";
			link.l1.go = "escort_add_ships";
			pchar.questTemp.WPU.Escort = "begin";
			pchar.questTemp.WPU.Escort.ShipNation = npchar.nation;//нация отправителя
			pchar.questTemp.WPU.Escort.TargetPortmanID = pchar.questTemp.WPU.Escort.City +"_portman";//ИД портмана
			sld = characterFromId(pchar.questTemp.WPU.Escort.TargetPortmanID);
			pchar.questTemp.WPU.Escort.Nation = sld.nation;//нация получателя
			pchar.questTemp.WPU.Current.TargetIslandID = GetCharacterCurrentIslandId(sld);//ИД целевого ареала
			pchar.questTemp.WPU.Escort.EnemyNation = GetEnemyNationToMainCharacter();//вражеская нация
			while (sti(pchar.questTemp.WPU.Postcureer.EnemyNation) == PIRATE)
			{
				pchar.questTemp.WPU.Escort.EnemyNation = GetEnemyNationToMainCharacter();
			}
			pchar.questTemp.WPU.Escort.count = sti(pchar.questTemp.WPU.Escort.count)+1;//считаем сделанные эскорты
			if (pchar.questTemp.WPU.Escort.Chance > 3) EnemyNationHunterOnMap(false);//запуск перехватчиков на глобалке
			if (pchar.questTemp.WPU.Escort.Chance == 3) TraderHunterOnMap();//запуск ДУ на глобалке
			if (pchar.questTemp.WPU.Escort.Chance < 2) FrahtHunterOnSea();//создание перехватчиков в акватории
			ReOpenQuestHeader("Escort");
			AddQuestRecord("Escort", "1");
			AddQuestUserData("Escort", "sDay", FindRussianDaysString(sti(pchar.questTemp.WPU.Escort.DaysQty)));
			AddQuestUserData("Escort", "sMoney", FindRussianMoneyString(sti(pchar.questTemp.WPU.Escort.Money)));
			AddQuestUserData("Escort", "sStartCity", XI_ConvertString("Colony"+pchar.questTemp.WPU.Escort.StartCity+"Gen"));
			AddQuestUserData("Escort", "sTargetColony",XI_ConvertString("Colony"+pchar.questTemp.WPU.Escort.City+"Gen"));
			SetFunctionTimerCondition("EscortTime_Over", 0, 0, sti(pchar.questTemp.WPU.Escort.DaysQty), false);
		break;
	
		case "escort_add_ships":
			int iGoods1, iGoods2, iSpace1, iSpace2, ShipType, Rank;
			int iNation = pchar.questTemp.WPU.Escort.ShipNation;
			int iLifeday = sti(pchar.questTemp.WPU.Escort.DaysQty)+10;
			string sTemp;
	        for (i=1; i<=2; i++)
	        {
				switch (rand(2))
				{
					case 0:  
						ShipType = SHIP_FLEUT;     					
						Rank = 10 + rand(5);
					break; 		
					case 1:  
						ShipType = SHIP_GALEON_L;			
						Rank = 15 + rand(5);
					break; 
					case 2: 
						ShipType = SHIP_PINNACE; 				
						Rank = 20 + rand(5);
					break;
				}
				if (i == 1) sTemp = pchar.questTemp.WPU.Escort.ShipName1;
				if (i == 2) sTemp = pchar.questTemp.WPU.Escort.ShipName2;
				if (i == 2) ShipType = SHIP_FLEUT;//один всегда флейт
	            sld = GetCharacter(NPC_GenerateCharacter("EscortCaptain_"+i, "trader_"+(rand(15)+1), "man", "man", Rank, iNation, iLifeday, true, "citizen"));
				FantomMakeSmallSailor(sld, ShipType, sTemp, CANNON_TYPE_CANNON_LBS16, 10+rand(10), 10+rand(10), 10+rand(10), 10+rand(10), 10+rand(10));
				DeleteAttribute(sld, "SaveItemsForDead");
				DeleteAttribute(sld, "DontClearDead");
				SetCharacterGoods(sld, GOOD_FOOD, 400+rand(200));
				SetCharacterGoods(sld, GOOD_MEDICAMENT, 60+rand(30));
	            iGoods1 = sti(pchar.questTemp.WPU.Escort.Goods1);
				iSpace1 = GetCharacterFreeSpace(sld, iGoods1);
				iSpace1 = makeint(iSpace1/2 + rand(iSpace1/2));
				iGoods2 = sti(pchar.questTemp.WPU.Escort.Goods2);
				iSpace2 = GetCharacterFreeSpace(sld, iGoods2);
				iSpace2 = makeint(iSpace2/2 + rand(iSpace2/2));
				if (i == 1) SetCharacterGoods(sld, iGoods1, iSpace1);
				if (i == 2) SetCharacterGoods(sld, iGoods2, iSpace2);
				sld.CompanionEnemyEnable = false; //всегда друзья
	            SetCompanionIndex(pchar, -1, sti(sld.index));
				sld.loyality = MAX_LOYALITY;
				SetCharacterRemovable(sld, false);
				sld.Dialog.Filename = "Common_portman.c";
				sld.dialog.currentnode = "Escort_companion";
				pchar.quest.Escort_fail.win_condition.l1 = "NPC_Death";
				pchar.quest.Escort_fail.win_condition.l1.character = "EscortCaptain_1";
				pchar.quest.Escort_fail.win_condition.l2 = "NPC_Death";
				pchar.quest.Escort_fail.win_condition.l2.character = "EscortCaptain_2";
				pchar.quest.Escort_fail.function = "Escort_failed";
	        }
			if (pchar.questTemp.WPU.Escort.Chance > 3) EnemyNationHunterOnMap(false);//запуск перехватчиков на глобалке
			if (pchar.questTemp.WPU.Escort.Chance == 3) TraderHunterOnMap();//запуск ДУ на глобалке
			if (pchar.questTemp.WPU.Escort.Chance < 2) FrahtHunterOnSea();//создание перехватчиков в акватории
			DialogExit();
		break;
	
		case "Escort_complete":
		ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
		if(sti(Pchar.Ship.Type) != SHIP_NOTUSED && ok)//проверка на наличие корабля в порту
		{
			//проверяем, все ли корабли
			if (GetCharacterIndex("EscortCaptain_1") == -1 || GetCharacterIndex("EscortCaptain_2") == -1)
			{
				dialog.text = "Гм... Я вижу, у вас в составе эскорта только один корабль. Это так?";
				link.l1 = "Да, " + GetAddress_FormToNPC(NPChar) + ". Второй утонул в бою с неприятельской эскадрой.";
				if (CheckAttribute(pchar, "questTemp.WPU.Escort.Bonus")) 
				{
					link.l1.go = "EscortBonus_complete_fail";
				}
				else
				{
					link.l1.go = "Escort_complete_fail";
				}
				break;
			}
			iGoods = pchar.questTemp.WPU.Escort.Goods;
			if (CheckAttribute(pchar, "questTemp.WPU.Escort.Bonus")) 
			{
				//pchar.questTemp.WPU.Escort.Money = sti(pchar.questTemp.WPU.Escort.Money)+sti(pchar.questTemp.WPU.Escort.BonusMoney);
				pchar.questTemp.WPU.Escort.Money = sti(pchar.questTemp.WPU.Escort.TotalMoney);
				amount = sti(pchar.questTemp.WPU.Escort.GoodsQty) - GetSquadronGoods(pchar, sti(pchar.questTemp.WPU.Escort.Goods));
				if (amount > 0)
				{
					dialog.text = "Так, замечательно. Вы должны были сопроводить корабли и привезти груз " + GetGoodsNameAlt(iGoods)+ " в количестве " + FindRussianQtyString(sti(pchar.questTemp.WPU.Escort.GoodsQty)) + ". Но я вижу, что вы привезли не весь груз -  не хватает " + FindRussianQtyString(sti(amount)) + " товара.";
					link.l1 = "Тысяча акул! Проклятые крысы сожрали! Не беспокойтесь, " + GetAddress_FormToNPC(NPChar) + ", я докуплю недостающее количество и сдам груз в полном комплекте.";
					link.l1.go = "Fraht_complete_3";
					break;
				}
			}
			if (pchar.questTemp.WPU.Escort == "late")//опоздали
			{
				iTime = makeint(GetQuestPastDayParam("questTemp.Escort.Late"))+1;
				pchar.questTemp.WPU.Escort.DayLate = iTime;
				pchar.questTemp.WPU.Escort.PercentLate = iTime/0.1;
				pchar.questTemp.WPU.Escort.Money = makeint(sti(pchar.questTemp.WPU.Escort.Money) - sti(pchar.questTemp.WPU.Escort.Money)*sti(pchar.questTemp.WPU.Escort.PercentLate)/100);//снижаем оплату согласно числа дней опоздания
				dialog.text = "Хм... Но вы опоздали на " + FindRussianDaysString(iTime)+ ". Поэтому я вынужден снизить размер оплаты за работу. Согласно договору, штраф составляет 10 процентов от суммы за каждый день просрочки. Получите, пожалуйста, ваши " + FindRussianMoneyString(sti(pchar.questTemp.WPU.Escort.Money)) + ", и впредь постарайтесь выполнять условия договора в точности.";
				link.l1 = "Спасибо и на этом.";
				link.l1.go = "Escort_complete_1";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.WPU.Escort.Bonus")) 
			{
				dialog.text = "Так, замечательно. Вы должны были сопроводить корабли и привезти груз " + GetGoodsNameAlt(iGoods)+ " в количестве " + FindRussianQtyString(sti(pchar.questTemp.WPU.Escort.GoodsQty)) + ". Спасибо за проделанную работу. Получите вашу оплату - " + FindRussianMoneyString(sti(pchar.questTemp.WPU.Escort.Money)) + ".";
			}
			else
			{
				dialog.text = "Спасибо за проделанную работу. Получите вашу оплату - " + FindRussianMoneyString(sti(pchar.questTemp.WPU.Escort.Money)) + ".";
			}
			link.l1 = "Спасибо!";
			link.l1.go = "Escort_complete_1";
		}
		else
		{
			dialog.text = "Что-то я не вижу в порту вашего корабля. Встаньте на рейд и приходите ко мне снова - тогда и поговорим.";
			link.l1 = "Хорошо, я так и сделаю.";
			link.l1.go = "exit";
		}
		break;
	
		case "Escort_complete_1":
			pchar.quest.Escort_fail.over = "yes";//снять прерывание
			if (pchar.questTemp.WPU.Escort == "begin")
			{
				pchar.quest.EscortTime_Over.over = "yes";//снять таймер
				AddQuestRecord("Escort", "2");
			}
			else
			{
				pchar.questTemp.WPU.Escort.count = sti(pchar.questTemp.WPU.Escort.count)-1;//опоздавший рейс не засчитываем
				pchar.quest.EscortTime_FullOver.over = "yes";//снять второй таймер
				if (CheckAttribute(pchar, "questTemp.WPU.Escort.Bonus"))
				{
					pchar.questTemp.WPU.Fraht.count = sti(pchar.questTemp.WPU.Fraht.count)-1;//опоздавший рейс не засчитываем
				}
				AddQuestRecord("Escort", "4");
				AddQuestUserData("Escort", "sDay", FindRussianDaysString(pchar.questTemp.WPU.Escort.DayLate));
				AddQuestUserData("Escort", "sMoney", FindRussianMoneyString(sti(pchar.questTemp.WPU.Escort.Money)));
			}
			RemoveCharacterCompanion(Pchar, characterFromID("EscortCaptain_1"));//удалим компаньонов
			RemoveCharacterCompanion(Pchar, characterFromID("EscortCaptain_2"));
			AddMoneyToCharacter(pchar, sti(pchar.questTemp.WPU.Escort.Money));
			if (CheckAttribute(pchar, "questTemp.WPU.Escort.Bonus")) RemoveCharacterGoods(pchar, sti(pchar.questTemp.WPU.Escort.Goods), sti(pchar.questTemp.WPU.Escort.GoodsQty));
			CloseQuestHeader("Escort");
			DeleteAttribute(pchar, "questTemp.WPU.Escort.TargetPortmanID");
			DeleteAttribute(pchar, "questTemp.WPU.Current.TargetIslandID");
			DeleteAttribute(pchar, "questTemp.WPU.Escort.Bonus");
			pchar.questTemp.WPU.Escort = "complete";
			SaveCurrentNpcQuestDateParam(npchar, "work_date");
			AddCharacterExpToSkill(pchar, "Sailing", 100);//навигация
			AddCharacterExpToSkill(pchar, "Defence", 100);//защита
			AddCharacterExpToSkill(pchar, "Leadership", 100);//авторитет
			AddCharacterExpToSkill(pchar, "Fortune", 100);//везение
			ChangeCharacterComplexReputation(pchar,"nobility", 2);
			ChangeCharacterNationReputation(pchar, sti(pchar.questTemp.WPU.Escort.Nation), 2);
			Group_DeleteGroup("Fraht_Attack");
			DialogExit();
		break;
	
		case "escort_bonus":
			pchar.questTemp.WPU.Escort.ShipName1 = GenerateRandomNameToShip(sti(npchar.nation));//имена кораблей
			pchar.questTemp.WPU.Escort.ShipName2 = GenerateRandomNameToShip(sti(npchar.nation));
			pchar.questTemp.WPU.Escort.Goods = 	drand(GOOD_PAPRIKA);//для ГГ
			pchar.questTemp.WPU.Escort.Goods1 = drand(GOOD_PAPRIKA-3);
			pchar.questTemp.WPU.Escort.Goods2 = drand(GOOD_PAPRIKA-5);
			iGoods = pchar.questTemp.WPU.Escort.Goods;
			iGoodsQty = makeint(GetCharacterFreeSpace(pchar, iGoods))-(50+rand(100));//количество груза
			pchar.questTemp.WPU.Escort.GoodsQty = iGoodsQty;
			pchar.questTemp.WPU.Escort.City = findCurrentCity1(npchar);//целевой город
			pchar.questTemp.WPU.Escort.StartCity = npchar.city;//город квестодателя
			pchar.questTemp.WPU.Escort.Chance = rand(4);//форс-мажор
			idaysQty = GetMaxDaysFromIsland2Island(GetArealByCityName(pchar.questTemp.WPU.Escort.StartCity), GetArealByCityName(pchar.questTemp.WPU.Escort.City));
			pchar.questTemp.WPU.Escort.DaysQty = makeint(sti(idaysQty)*(frand(0.5)+1));//дни
			pchar.questTemp.WPU.Escort.Money = (sti(idaysQty)*2000)*sti(idaysQty)/sti(pchar.questTemp.WPU.Escort.DaysQty)*(1+frand(0.2));//оплата за сопровождение
			pchar.questTemp.WPU.Escort.BonusMoney = (makeint((sti(iGoodsQty) * sti(Goods[iGoods].Weight) / sti(Goods[iGoods].Units))))*(sti(idaysQty)*2)*sti(idaysQty)/sti(pchar.questTemp.WPU.Escort.DaysQty);//оплата за фрахт
			pchar.questTemp.WPU.Escort.TotalMoney = sti(pchar.questTemp.WPU.Escort.Money)+sti(pchar.questTemp.WPU.Escort.BonusMoney); // общая сумма
			dialog.text = "Итак, необходимо сопроводить корабли '" + pchar.questTemp.WPU.Escort.ShipName1 + "' и '" + pchar.questTemp.WPU.Escort.ShipName2 + "' до города " + XI_ConvertString("Colony" + pchar.questTemp.WPU.Escort.City) + ", за " +  FindRussianDaysString(pchar.questTemp.WPU.Escort.DaysQty) + ". Оплата - " + FindRussianMoneyString(sti(pchar.questTemp.WPU.Escort.Money))+ "\nТакже на вашем корабле я размещаю груз " + GetGoodsNameAlt(iGoods)+ " в количестве " + FindRussianQtyString(iGoodsQty) + ". Оплата за его доставку - " + FindRussianMoneyString(sti(pchar.questTemp.WPU.Escort.BonusMoney))+".";
			link.l1 = "Задача ясна. Приступаю к выполнению?";
			link.l1.go = "escort_bonus_1";
			link.l2 = "Гм... но мне совсем в другую сторону. Вынужден отказаться.";
			link.l2.go = "exit";
		break;
	
		case "escort_bonus_1":
			dialog.text = "Очень хорошо! Принимайте командование эскадрой.";
			link.l1 = "Отправляюсь в путь!";
			link.l1.go = "escort_add_ships";
			iGoods = pchar.questTemp.WPU.Escort.Goods;
			AddCharacterGoods(pchar, sti(pchar.questTemp.WPU.Escort.Goods), sti(pchar.questTemp.WPU.Escort.GoodsQty));
			pchar.questTemp.WPU.Escort = "begin";
			pchar.questTemp.WPU.Escort.Bonus = "true";
			pchar.questTemp.WPU.Escort.ShipNation = npchar.nation;//нация отправителя
			pchar.questTemp.WPU.Escort.TargetPortmanID = pchar.questTemp.WPU.Escort.City +"_portman";//ИД портмана
			sld = characterFromId(pchar.questTemp.WPU.Escort.TargetPortmanID);
			pchar.questTemp.WPU.Escort.Nation = sld.nation;//нация получателя
			pchar.questTemp.WPU.Current.TargetIslandID = GetCharacterCurrentIslandId(sld);//ИД целевого ареала
			pchar.questTemp.WPU.Escort.EnemyNation = GetEnemyNationToMainCharacter();//вражеская нация
			while (sti(pchar.questTemp.WPU.Postcureer.EnemyNation) == PIRATE)
			{
				pchar.questTemp.WPU.Escort.EnemyNation = GetEnemyNationToMainCharacter();
			}
			pchar.questTemp.WPU.Escort.count = sti(pchar.questTemp.WPU.Escort.count)+1;//считаем сделанные эскорты
			pchar.questTemp.WPU.Fraht.count = sti(pchar.questTemp.WPU.Fraht.count)+1;//считаем сделанные фрахты
			if (pchar.questTemp.WPU.Escort.Chance > 3) EnemyNationHunterOnMap(false);//запуск перехватчиков на глобалке
			if (pchar.questTemp.WPU.Escort.Chance == 3) TraderHunterOnMap();//запуск ДУ на глобалке
			if (pchar.questTemp.WPU.Escort.Chance < 3) FrahtHunterOnSea();//создание перехватчиков в акватории
			ReOpenQuestHeader("Escort");
			AddQuestRecord("Escort", "6");
			AddQuestUserData("Escort", "sDay", FindRussianDaysString(sti(pchar.questTemp.WPU.Escort.DaysQty)));
			AddQuestUserData("Escort", "sMoney", FindRussianMoneyString(sti(pchar.questTemp.WPU.Escort.Money)));
			AddQuestUserData("Escort", "sStartCity", XI_ConvertString("Colony"+pchar.questTemp.WPU.Escort.StartCity+"Gen"));
			AddQuestUserData("Escort", "sTargetColony",XI_ConvertString("Colony"+pchar.questTemp.WPU.Escort.City));
			AddQuestUserData("Escort", "sGoods", GetGoodsNameAlt(iGoods));
			AddQuestUserData("Escort", "sGoodQty", FindRussianQtyString(sti(pchar.questTemp.WPU.Escort.GoodsQty)));
			AddQuestUserData("Escort", "sMoney1", FindRussianMoneyString(sti(pchar.questTemp.WPU.Escort.BonusMoney)));
			pchar.questTemp.WPU.Fraht.GoodsAverigePrice = sti(Goods[iGoods].Cost);//цена единицы товара
			pchar.questTemp.WPU.Fraht.GoodsAverigeCost = sti(Goods[iGoods].Cost)*sti(pchar.questTemp.WPU.Escort.GoodsQty);//средняя стоимость товара
			SetFunctionTimerCondition("EscortTime_Over", 0, 0, sti(pchar.questTemp.WPU.Escort.DaysQty), false);
		break;
	
		case "Escort_complete_fail":
			dialog.text = "Невероятно! А зачем же тогда нужны были вы? Как вы допустили такое?! Я думаю, вам понятно, что ни о каком вознаграждении речи быть не может. Прощайте.";
			link.l1 = "Какое уж там вознаграждение... Всего доброго.";
			link.l1.go = "exit";
			pchar.quest.Escort_fail.over = "yes";//снять прерывание
			pchar.quest.EscortTime_Over.over = "yes";//снять прерывание // patch-2
			if (GetCharacterIndex("EscortCaptain_1") == -1) RemoveCharacterCompanion(pchar, characterFromID("EscortCaptain_2"));
			else RemoveCharacterCompanion(pchar, characterFromID("EscortCaptain_1"));
			AddQuestRecord("Escort", "11");
			CloseQuestHeader("Escort");
			pchar.questTemp.WPU.Escort.count = sti(pchar.questTemp.WPU.Escort.count)-1;//рейс не засчитываем
			DeleteAttribute(pchar, "questTemp.WPU.Escort.TargetPortmanID");
			DeleteAttribute(pchar, "questTemp.WPU.Current.TargetIslandID");
			pchar.questTemp.WPU.Escort = "complete";
			SaveCurrentNpcQuestDateParam(npchar, "work_date");
			AddCharacterExpToSkill(pchar, "Sailing", 50);//навигация
			AddCharacterExpToSkill(pchar, "Defence", 150);//защита
			AddCharacterExpToSkill(pchar, "Fortune", 50);//везение
			Group_DeleteGroup("Fraht_Attack");
		break;
	
		case "EscortBonus_complete_fail":
			if (GetCharacterIndex("EscortCaptain_1") == -1) RemoveCharacterCompanion(pchar, characterFromID("EscortCaptain_2"));
			else RemoveCharacterCompanion(pchar, characterFromID("EscortCaptain_1"));//удалим компаньона
			pchar.quest.Escort_fail.over = "yes";//снять прерывание
			amount = sti(pchar.questTemp.WPU.Escort.GoodsQty) - GetSquadronGoods(pchar, sti(pchar.questTemp.WPU.Escort.Goods));
			pchar.questTemp.WPU.Escort.GoodsQty = GetSquadronGoods(pchar, sti(pchar.questTemp.WPU.Escort.Goods));
			if (pchar.questTemp.WPU.Escort == "begin")
			{
				pchar.quest.EscortTime_Over.over = "yes";//снять таймер
				pchar.questTemp.WPU.Escort.MinusMoney = makeint(sti(pchar.questTemp.WPU.Escort.BonusMoney) - sti(pchar.questTemp.WPU.Fraht.GoodsAverigePrice)*sti(amount));
				if (sti(pchar.questTemp.WPU.Escort.MinusMoney) < 0) amount = 101;
				if (amount > 0 && amount <= 100)
				{
					pchar.questTemp.WPU.Escort.BonusMoney = sti(pchar.questTemp.WPU.Escort.MinusMoney);
					dialog.text = "Невероятно! А зачем же тогда нужны были вы? Как вы допустили такое?! Я думаю, вам понятно, что ни о каком вознаграждении за сопровождение речи быть не может... Да ещё и груза у вас недостача - " + FindRussianQtyString(sti(amount)) + "\nВ общем, я плачу вам вознаграждение только за фрахт, за вычетом стоимости недостающего товара, за то, что вы хоть груз доставили в приемлемом виде. Получите ваши " + FindRussianMoneyString(sti(pchar.questTemp.WPU.Escort.BonusMoney))+ " и можете быть свободны.";
					link.l1 = "Спасибо и на этом.";
					link.l1.go = "EscortBonus_complete_fail_1";
					break;
				}
				if (amount > 100)
				{
					dialog.text = "Невероятно! А зачем же тогда нужны были вы? Как вы допустили такое?! Я думаю, вам понятно, что ни о каком вознаграждении за сопровождение речи быть не может... Да ещё и груза у вас огромная недостача\nУ меня нет возможности ждать, пока вы докупите недостающее количество. Поэтому вам придётся компенсировать стоимость груза деньгами в полном объёме - " + FindRussianMoneyString(sti(pchar.questTemp.WPU.Fraht.GoodsAverigeCost))+ ". Сам же груз оставьте себе.";
					if (sti(pchar.money) >= sti(pchar.questTemp.WPU.Fraht.GoodsAverigeCost))
					{
						link.l1 = "Хорошо-хорошо, не кипятитесь, вот ваши деньги.";
						link.l1.go = "EscortBonus_complete_fail_2";
					}
					link.l2 = "Да вы тут с ума посходили! Это же самое настоящее вымогательство! Ничего я вам не дам!";
					link.l2.go = "EscortBonus_complete_fail_3";
					break;
				}
				dialog.text = "Невероятно! А зачем же тогда нужны были вы? Как вы допустили такое?! Я думаю, вам понятно, что ни о каком вознаграждении за сопровождение речи быть не может\nВ общем, я плачу вам вознаграждение только за фрахт, за то, что вы хоть груз доставили. Получите ваши " + FindRussianMoneyString(sti(pchar.questTemp.WPU.Escort.BonusMoney))+ " и можете быть свободны.";
				link.l1 = "Спасибо и на этом.";
				link.l1.go = "EscortBonus_complete_fail_1";
				break;
			}
			if (pchar.questTemp.WPU.Escort == "late")
			{
				pchar.quest.EscortTime_FullOver.over = "yes";//снять второй таймер
				iTime = makeint(GetQuestPastDayParam("questTemp.Escort.Late"))+1;
				pchar.questTemp.WPU.Escort.DayLate = iTime;
				pchar.questTemp.WPU.Escort.PercentLate = iTime/0.1;
				pchar.questTemp.WPU.Escort.BonusMoney = makeint(sti(pchar.questTemp.WPU.Escort.BonusMoney) - sti(pchar.questTemp.WPU.Escort.BonusMoney)*sti(pchar.questTemp.WPU.Escort.PercentLate)/100);//снижаем оплату согласно числа дней опоздания
				if (amount > 0)
				{
					dialog.text = "Невероятно! А зачем же тогда нужны были вы? Как вы допустили такое?! Я думаю, вам понятно, что ни о каком вознаграждении за сопровождение речи быть не может... Корабль потеряли, опоздали на " + FindRussianDaysString(iTime)+ ", да ещё и груза у вас недостача - " + FindRussianQtyString(sti(amount)) + "\nУ меня нет возможности ждать, пока вы докупите недостающее количество. Поэтому вам придется компенсировать стоимость груза деньгами в полном объёме - " + FindRussianMoneyString(sti(pchar.questTemp.WPU.Fraht.GoodsAverigeCost))+ ". Сам же груз оставьте себе.";
					if (sti(pchar.money) >= sti(pchar.questTemp.WPU.Fraht.GoodsAverigeCost))
					{
						link.l1 = "Хорошо-хорошо, не кипятитесь, вот ваши деньги.";
						link.l1.go = "EscortBonus_complete_fail_2";
					}
					link.l2 = "Да вы тут с ума посходили! Это же самое настоящее вымогательство! Ничего я вам не дам!";
					link.l2.go = "EscortBonus_complete_fail_3";
					break;
				}
				dialog.text = "Невероятно! А зачем же тогда нужны были вы? Как вы допустили такое?! Я думаю, вам понятно, что ни о каком вознаграждении за сопровождение речи быть не может... Да ещё и опоздали на " + FindRussianDaysString(iTime)+ "\nПоэтому я вынужден снизить размер оплаты за фрахт. Согласно договору, штраф составляет 10 процентов от суммы за каждый день просрочки. Получите, пожалуйста, ваши " + FindRussianMoneyString(sti(pchar.questTemp.WPU.Escort.BonusMoney)) + ", и можете быть свободны.";
				link.l1 = "Спасибо и на этом.";
				link.l1.go = "EscortBonus_complete_fail_1";
				break;
			}
		break;
	
		case "EscortBonus_complete_fail_1"://потеряли корабль, время и груз в норме или частично
			AddQuestRecord("Escort", "12");
			AddQuestUserData("Escort", "sMoney", FindRussianMoneyString(sti(pchar.questTemp.WPU.Escort.BonusMoney)));
			CloseQuestHeader("Escort");
			AddMoneyToCharacter(pchar, sti(pchar.questTemp.WPU.Escort.BonusMoney));
			RemoveCharacterGoods(pchar, sti(pchar.questTemp.WPU.Escort.Goods), sti(pchar.questTemp.WPU.Escort.GoodsQty));
			pchar.questTemp.WPU.Escort.count = sti(pchar.questTemp.WPU.Escort.count)-1;//рейс не засчитываем
			DeleteAttribute(pchar, "questTemp.WPU.Escort.TargetPortmanID");
			DeleteAttribute(pchar, "questTemp.WPU.Current.TargetIslandID");
			DeleteAttribute(pchar, "questTemp.WPU.Escort.Bonus");
			pchar.questTemp.WPU.Escort = "complete";
			SaveCurrentNpcQuestDateParam(npchar, "work_date");
			AddCharacterExpToSkill(pchar, "Sailing", 50);//навигация
			AddCharacterExpToSkill(pchar, "Defence", 150);//защита
			AddCharacterExpToSkill(pchar, "Fortune", 50);//везение
			AddCharacterExpToSkill(pchar, "Commerce", 100);//торговля
			Group_DeleteGroup("Fraht_Attack");
			DialogExit();
		break;
	
		case "EscortBonus_complete_fail_2"://потеряли корабль и груз, время норма или нет, мир
			AddQuestRecord("Escort", "13");
			AddQuestUserData("Escort", "sMoney", FindRussianMoneyString(sti(pchar.questTemp.WPU.Fraht.GoodsAverigeCost)));
			CloseQuestHeader("Escort");
			AddMoneyToCharacter(pchar, -sti(pchar.questTemp.WPU.Fraht.GoodsAverigeCost));
			pchar.questTemp.WPU.Escort.count = sti(pchar.questTemp.WPU.Escort.count)-1;//рейс не засчитываем
			pchar.questTemp.WPU.Escort.count = sti(pchar.questTemp.WPU.Fraht.count)-1;//рейс не засчитываем
			DeleteAttribute(pchar, "questTemp.WPU.Escort.TargetPortmanID");
			DeleteAttribute(pchar, "questTemp.WPU.Current.TargetIslandID");
			DeleteAttribute(pchar, "questTemp.WPU.Escort.Bonus");
			pchar.questTemp.WPU.Escort = "complete";
			SaveCurrentNpcQuestDateParam(npchar, "work_date");
			AddCharacterExpToSkill(pchar, "Sailing", 50);//навигация
			AddCharacterExpToSkill(pchar, "Defence", 150);//защита
			AddCharacterExpToSkill(pchar, "Fortune", 50);//везение
			AddCharacterExpToSkill(pchar, "Commerce", 50);//торговля
			Group_DeleteGroup("Fraht_Attack");
			DialogExit();
		break;
	
		case "EscortBonus_complete_fail_3"://потеряли корабль и груз, время норма или нет, война
			dialog.text = "Значит, вот так... Ну что же, тогда более даже не смейте обращаться ни по каким вопросам в портовые управления " + NationNameGenitive(sti(pchar.questTemp.WPU.Escort.Nation)) + "! Убирайтесь!";
			link.l1 = "Невелика потеря...";
			link.l1.go = "exit";
			AddQuestRecord("Escort", "14");
			AddQuestUserData("Escort", "sMoney", FindRussianMoneyString(sti(pchar.questTemp.WPU.Fraht.GoodsAverigeCost)));
			CloseQuestHeader("Escort");
			pchar.questTemp.WPU.Escort.count = 0;//счетчик в ноль
			pchar.questTemp.WPU.Escort.count = 0;//счетчик в ноль
			DeleteAttribute(pchar, "questTemp.WPU.Escort.TargetPortmanID");
			DeleteAttribute(pchar, "questTemp.WPU.Current.TargetIslandID");
			DeleteAttribute(pchar, "questTemp.WPU.Escort.Bonus");
			pchar.questTemp.WPU.Escort = "complete";
			pchar.questTemp.WPU.Fraht = "fail";
			ChangeCharacterComplexReputation(pchar,"nobility", -10);
			ChangeCharacterHunterScore(pchar, NationShortName(sti(pchar.questTemp.WPU.Escort.Nation)) + "hunter", 30);
			pchar.questTemp.WPU.Fraht.Nation = pchar.questTemp.WPU.Escort.Nation;
			SaveCurrentNpcQuestDateParam(npchar, "work_date");
			Group_DeleteGroup("Fraht_Attack");
		break;
	
		case "Escort_fail"://потеряли 2 корабля
			dialog.text = "Это очень и очень плохо! А для чего, скажите, вас тогда нанимали, а? Для охраны, или просто так?";
			link.l1 = "Я всё понимаю. Противник был очень силён, и... ну, к чему слова - дело-то уже сделано... Но груз-то, груз я привёз! Давайте с ним разбираться.";
			link.l1.go = "Escort_fail_complete";
		break;
	
		case "Escort_fail_complete":
			iFrahtGoods = makeint(pchar.questTemp.WPU.Escort.Goods);
			amount = sti(pchar.questTemp.WPU.Escort.GoodsQty) - GetSquadronGoods(pchar, sti(pchar.questTemp.WPU.Escort.Goods));
			if (amount > 0)
			{
				dialog.text = "Давайте посмотрим. Вы должны были привезти груз " + GetGoodsNameAlt(iFrahtGoods)+ " в количестве " + FindRussianQtyString(pchar.questTemp.WPU.Escort.GoodsQty) + ". Но я вижу, что вы привезли не весь груз - не хватает " + FindRussianQtyString(sti(amount)) + " товара.";
				link.l1 = "Тысяча акул! Проклятые крысы сожрали! Не беспокойтесь, " + GetAddress_FormToNPC(NPChar) + ", я докуплю недостающее количество и сдам груз в полном комплекте.";
				link.l1.go = "Fraht_complete_3";
				break;
			}
			dialog.text = "Давайте посмотрим. Вы должны были привезти груз " + GetGoodsNameAlt(iFrahtGoods)+ " в количестве " + FindRussianQtyString(pchar.questTemp.WPU.Escort.GoodsQty) + ". Так?";
			link.l1 = "Совершенно верно, " + GetAddress_FormToNPC(NPChar) + ".";
			link.l1.go = "Escort_fail_complete_1";
		break;
	
		case "Escort_fail_complete_1":
			DeleteAttribute(pchar, "questTemp.WPU.Escort.Bonus");
			pchar.questTemp.WPU.Escort.Money = makeint(sti(pchar.questTemp.WPU.Escort.BonusMoney)/2);
			if (pchar.questTemp.WPU.Escort == "late")//опоздали
			{
				iTime = makeint(GetQuestPastDayParam("questTemp.Escort.Late"))+1;
				pchar.questTemp.WPU.Escort.DayLate = iTime;
				pchar.questTemp.WPU.Escort.PercentLate = iTime/0.1;
				pchar.questTemp.WPU.Escort.Money = makeint(sti(pchar.questTemp.WPU.Escort.Money) - sti(pchar.questTemp.WPU.Escort.Money)*sti(pchar.questTemp.WPU.Escort.PercentLate)/100);//снижаем оплату согласно числа дней опоздания
				dialog.text = "Хм... Мало того, что вы потеряли вверенные корабли, вы ещё и опоздали на " + FindRussianDaysString(iTime)+ ". Поэтому я вынужден снизить размер оплаты за фрахт. Так как вы не смогли сохранить караван, оплату за фрахт я уменьшаю вдвое, и это самое большее, что я могу вам заплатить\nКроме того, согласно договору, штраф составляет 10 процентов от суммы за каждый день просрочки. Получите, пожалуйста, ваши " + FindRussianMoneyString(sti(pchar.questTemp.WPU.Escort.Money)) + ", и можете быть свободны.";
				link.l1 = "Спасибо и на этом.";
				link.l1.go = "Escort_fail_complete_2";
				break;
			}
			dialog.text = "Ну что же, хоть я и невероятно расстроен, что вы не смогли защитить вверенные корабли, по крайней мере груз вы доставили. Так как вы не смогли сохранить караван, оплату за фрахт я уменьшаю вдвое, и это самое большее, что я могу вам заплатить\nПолучите вашу оплату - " + FindRussianMoneyString(sti(pchar.questTemp.WPU.Escort.Money)) + " и можете быть свободны.";
			link.l1 = "Спасибо и на этом.";
			link.l1.go = "Escort_fail_complete_2";
		break;
	
		case "Escort_fail_complete_2":
			if (pchar.questTemp.WPU.Escort == "begin")
			{
				pchar.quest.EscortTime_Over.over = "yes";
				AddQuestRecord("Escort", "17");
				AddQuestUserData("Escort", "sMoney", FindRussianMoneyString(sti(pchar.questTemp.WPU.Escort.Money)));
			}
			else
			{
				pchar.quest.EscortTime_FullOver.over = "yes";//снять второй таймер
				AddQuestRecord("Escort", "18");
				AddQuestUserData("Escort", "sDay", FindRussianDaysString(pchar.questTemp.WPU.Escort.DayLate));
				AddQuestUserData("Escort", "sMoney", FindRussianMoneyString(sti(pchar.questTemp.WPU.Escort.Money)));
			}
			pchar.questTemp.WPU.Fraht.count = sti(pchar.questTemp.WPU.Fraht.count)-1;//фейловый рейс не засчитываем
			RemoveCharacterGoods(pchar, sti(pchar.questTemp.WPU.Escort.Goods), sti(pchar.questTemp.WPU.Escort.GoodsQty));
			AddMoneyToCharacter(pchar, sti(pchar.questTemp.WPU.Escort.Money));
			CloseQuestHeader("Escort");
			DeleteAttribute(pchar, "questTemp.WPU.Escort.TargetPortmanID");
			DeleteAttribute(pchar, "questTemp.WPU.Current.TargetIslandID");
			pchar.questTemp.WPU.Escort = "complete";
			SaveCurrentNpcQuestDateParam(npchar, "work_date");
			AddCharacterExpToSkill(pchar, "Sailing", 50);//навигация
			AddCharacterExpToSkill(pchar, "Commerce", 50);//торговля
			AddCharacterExpToSkill(pchar, "Fortune", 50);//везение
			Group_DeleteGroup("Fraht_Attack");
			DialogExit();
		break;
	
//-------------------------------------задания 2 уровня для курьера---------------------------------------------
		case "Postcureer_LevelUp":
			pchar.questTemp.WPU.Postcureer.City = findCurrentCity2(npchar);//целевой город
			pchar.questTemp.WPU.Postcureer.StartCity = npchar.city;//город квестодателя
			idaysQty = GetMaxDaysFromIsland2Island(GetArealByCityName(pchar.questTemp.WPU.Postcureer.StartCity), GetArealByCityName(pchar.questTemp.WPU.Postcureer.City));
			pchar.questTemp.WPU.Postcureer.DaysQty = makeint(sti(idaysQty)*(frand(0.3)+0.6));//дни
			pchar.questTemp.WPU.Postcureer.Money = (sti(idaysQty)*3000)*sti(idaysQty)/sti(pchar.questTemp.WPU.Postcureer.DaysQty)*(1+frand(0.2));//оплата
			pchar.questTemp.WPU.Postcureer.Chance = rand(4);//форс-мажор
			pchar.questTemp.WPU.Postcureer.StartNation = npchar.nation;//нация отправителя
			pchar.questTemp.WPU.Postcureer.TargetPortmanID = pchar.questTemp.WPU.Postcureer.City +"_portman";//ИД портмана
			sld = characterFromId(pchar.questTemp.WPU.Postcureer.TargetPortmanID);
			pchar.questTemp.WPU.Postcureer.Nation = sld.nation;//нация получателя
			pchar.questTemp.WPU.Current.TargetIslandID = GetCharacterCurrentIslandId(sld);//ИД целевого ареала
			pchar.questTemp.WPU.Postcureer.EnemyNation = GetEnemyNationToMainCharacter();//вражеская нация
			while (sti(pchar.questTemp.WPU.Postcureer.EnemyNation) == PIRATE)
			{
				pchar.questTemp.WPU.Postcureer.EnemyNation = GetEnemyNationToMainCharacter();
			}

			switch (rand(3))
			{
				case 0:
					dialog.text = "Необходимо срочно доставить важную государственную депешу для губернатора города "+XI_ConvertString("Colony"+pchar.questTemp.WPU.Postcureer.City+"Gen")+" не позже, чем за "+FindRussianDaysString(sti(pchar.questTemp.WPU.Postcureer.DaysQty))+". Соблюдайте меры предосторожности - за этой депешей может вестись охота. Оплата за доставку - "+FindRussianMoneyString(sti(pchar.questTemp.WPU.Postcureer.Money))+".";
					link.l1 = "Я согласен!";
					link.l1.go = "Postcureer_LevelUp_Go";
					link.l2 = "Нет, откажусь, пожалуй.";
					link.l2.go = "Postcureer_LevelDown";
					pchar.questTemp.WPU.Postcureer.TargetPortmanID = pchar.questTemp.WPU.Postcureer.City +"_Mayor";//ИД губера
					if (pchar.questTemp.WPU.Postcureer.TargetPortmanID == "Villemstad_Mayor") pchar.questTemp.WPU.Postcureer.TargetPortmanID = "hol_guber"; // фикс Матиаса Бека #717
					pchar.questTemp.WPU.Current.Add = "депешу для губернатора";
					pchar.questTemp.WPU.Current.Item = "letter_2";//предмет
					pchar.questTemp.WPU.Current.Itemdescr = "itmdescr_letter_2_PortmanLevelUp1";//описание
				break;
			
				case 1:
					dialog.text = "Необходимо доставить эти бумаги для хозяина магазина "+XI_ConvertString("Colony"+pchar.questTemp.WPU.Postcureer.City+"Gen")+" не позже, чем за "+FindRussianDaysString(sti(pchar.questTemp.WPU.Postcureer.DaysQty))+". Это последняя сводка цен в магазинах всего архипелага - ценнейший коммерческий документ. Следует проявить осторожность - конкуренты вполне могут устроить охоту. Оплата за доставку - "+FindRussianMoneyString(sti(pchar.questTemp.WPU.Postcureer.Money))+".";
					link.l1 = "Я согласен!";
					link.l1.go = "Postcureer_LevelUp_Go";
					link.l2 = "Нет, откажусь, пожалуй.";
					link.l2.go = "Postcureer_LevelDown";
					pchar.questTemp.WPU.Postcureer.TargetPortmanID = pchar.questTemp.WPU.Postcureer.City +"_trader";//ИД торговца
					pchar.questTemp.WPU.Current.Add = "сводку цен для хозяина магазина";
					pchar.questTemp.WPU.Current.Item = "letter_2";//предмет
					pchar.questTemp.WPU.Current.Itemdescr = "itmdescr_letter_2_PortmanLevelUp2";//описание
				break;
			
				case 2:
					dialog.text = "Необходимо доставить этот пакет документов для ростовщика города "+XI_ConvertString("Colony"+pchar.questTemp.WPU.Postcureer.City+"Gen")+" не позже, чем за "+FindRussianDaysString(sti(pchar.questTemp.WPU.Postcureer.DaysQty))+". Здесь очень важная деловая информация о курсах валют и ценных бумаг. Будьте начеку - этим пакетом уже интересовались какие-то тёмные личности. Оплата за доставку - "+FindRussianMoneyString(sti(pchar.questTemp.WPU.Postcureer.Money))+".";
					link.l1 = "Я согласен!";
					link.l1.go = "Postcureer_LevelUp_Go";
					link.l2 = "Нет, откажусь, пожалуй.";
					link.l2.go = "Postcureer_LevelDown";
					pchar.questTemp.WPU.Postcureer.TargetPortmanID = pchar.questTemp.WPU.Postcureer.City +"_usurer";//ИД ростовщика
					pchar.questTemp.WPU.Current.Add = "пакет с деловой информацией для ростовщика";
					pchar.questTemp.WPU.Current.Item = "letter_2";//предмет
					pchar.questTemp.WPU.Current.Itemdescr = "itmdescr_letter_2_PortmanLevelUp3";//описание
				break;
			
				case 3:
					dialog.text = "Необходимо доставить этот сверток хозяину верфи города "+XI_ConvertString("Colony"+pchar.questTemp.WPU.Postcureer.City+"Gen")+" не позже, чем за "+FindRussianDaysString(sti(pchar.questTemp.WPU.Postcureer.DaysQty))+". В нём находится строительный чертёж нового "+RandPhraseSimple(LinkRandPhrase("брига","корвета","фрегата"), LinkRandPhrase("флейта","пинаса","галеона"))+", содержащий уникальные технические разработки. Думаю, понятно, что этим чертежом могут интересоваться и другие... заинтересованные лица, так что учтите это. Оплата за доставку - "+FindRussianMoneyString(sti(pchar.questTemp.WPU.Postcureer.Money))+".";
					link.l1 = "Я согласен!";
					link.l1.go = "Postcureer_LevelUp_Go";
					link.l2 = "Нет, откажусь, пожалуй.";
					link.l2.go = "Postcureer_LevelDown";
					pchar.questTemp.WPU.Postcureer.TargetPortmanID = pchar.questTemp.WPU.Postcureer.City +"_shipyarder";//ИД верфиста
					pchar.questTemp.WPU.Current.Add = "чертеж нового корабля для хозяина верфи";
					pchar.questTemp.WPU.Current.Item = "ShipyardsMap";//предмет
					pchar.questTemp.WPU.Current.Itemdescr = "itmdescr_ShipyardsMap_PortmanLevelUp4";//описание
				break;
			}
		break;
	
		case "Postcureer_LevelUp_Go":
			dialog.text = "Тогда держите документы и отправляйтесь в путь. Желаю удачи и... да хранит вас Господь.";
			link.l1 = "Спасибо!";
			link.l1.go = "Forsmajor_choose";
			pchar.questTemp.WPU.Postcureer = "begin";
			pchar.questTemp.WPU.Postcureer.LevelUp = "true";
			pchar.questTemp.WPU.Postcureer.count = sti(pchar.questTemp.WPU.Postcureer.count) + 1;
			//запустить регату при счетчике > 4
			if (!CheckAttribute(pchar, "questTemp.RegataGo") && sti(pchar.questTemp.WPU.Postcureer.count) > 4)
			{
				pchar.questTemp.RegataGo = "true";
				pchar.questTemp.Regata.CureerCity = FindFriendCityToMC(true);//город, в котором вестовой подойдет
				if (pchar.questTemp.Regata.CureerCity == "PortRoyal") pchar.questTemp.Regata.CureerCity = "SentJons";
				pchar.quest.Regata_Cureer.win_condition.l1 = "location";
				pchar.quest.Regata_Cureer.win_condition.l1.location = pchar.questTemp.Regata.CureerCity+"_town";
				pchar.quest.Regata_Cureer.function = "PrepareToRegata";
				log_testinfo(pchar.questTemp.Regata.CureerCity);
			}
			GiveItem2Character(pchar, pchar.questTemp.WPU.Current.Item);
			ChangeItemDescribe(pchar.questTemp.WPU.Current.Item, pchar.questTemp.WPU.Current.Itemdescr);
			ReOpenQuestHeader("Postcureer");
			AddQuestRecord("Postcureer", "6");
			AddQuestUserData("Postcureer", "sDay", FindRussianDaysString(sti(pchar.questTemp.WPU.Postcureer.DaysQty)));
			AddQuestUserData("Postcureer", "sMoney", FindRussianMoneyString(sti(pchar.questTemp.WPU.Postcureer.Money)));
			AddQuestUserData("Postcureer", "sStartCity", XI_ConvertString("Colony"+pchar.questTemp.WPU.Postcureer.StartCity+"Gen"));
			AddQuestUserData("Postcureer", "sTargetColony",XI_ConvertString("Colony"+pchar.questTemp.WPU.Postcureer.City+"Gen"));
			AddQuestUserData("Postcureer", "sText", pchar.questTemp.WPU.Current.Add);
			SetFunctionTimerCondition("PostcureerTime_Over", 0, 0, sti(pchar.questTemp.WPU.Postcureer.DaysQty), false);
		break;
	
		case "Postcureer_LevelDown":
			dialog.text = "Жаль, очень жаль... Вообще-то, такими предложениями не разбрасываются. Но это ваше дело, конечно.";
			link.l1 = "Вот именно - моё дело. До свидания, " + GetAddress_FormToNPC(NPChar) + ".";
			link.l1.go = "exit";
			pchar.questTemp.WPU.Postcureer.count = sti(pchar.questTemp.WPU.Postcureer.count) - 1;//за отказ от спецзадания счетчик скрутим
		break;
	
		case "Forsmajor_choose":
			switch (sti(pchar.questTemp.WPU.Postcureer.Chance))
			{
				case 0://охотники в городе прибытия + ДУ
					pchar.quest.Postcureer_Hunter.win_condition.l1 = "Location";
					pchar.quest.Postcureer_Hunter.win_condition.l1.location = pchar.questTemp.WPU.Postcureer.City + "_town";
					pchar.quest.Postcureer_Hunter.function = "PostcureerGopHuntersOnLand";
					TraderHunterOnMap();
				break;
		
				case 1://создание скоростного перехватчика на глобалке
					EnemyNationHunterOnMap(true);
				break;
		
				case 2://запуск ДУ на глобалке и в порту прибытия
					TraderHunterOnMap();
					FrahtHunterOnSea();
				break;
		
				case 3://наемники в стартовом городе
					pchar.quest.Postcureer_Hunter.win_condition.l1 = "Location";
					pchar.quest.Postcureer_Hunter.win_condition.l1.location = pchar.questTemp.WPU.Postcureer.StartCity + "_town";
					pchar.quest.Postcureer_Hunter.function = "PostcureerProfHuntersOnLand";
				break;
		
				case 4://агент
					pchar.quest.Postcureer_Hunter.win_condition.l1 = "Location";
					pchar.quest.Postcureer_Hunter.win_condition.l1.location = pchar.questTemp.WPU.Postcureer.StartCity + "_town";
					pchar.quest.Postcureer_Hunter.function = "PostcureerAgent";
				break;
			}
			DialogExit();
		break;

		case "Postcureer_complete_fail":
			dialog.text = "Проклятие! Значит, они всё-таки выследили... Эх, жаль, капитан, что вы не солдат - так может всё по-другому бы вышло... Как они выглядели?";
			link.l1 = "Два крепких здоровых типа, в чёрной одежде, в полумасках на лицах, вооружены секирами и двустволками...";
			link.l1.go = "Postcureer_complete_fail_1";
		break;

		case "Postcureer_complete_fail_1":
			dialog.text = "Я немедленно сообщу губернатору, чтобы начали поиск. Ну, всего доброго, " + GetAddress_Form(NPChar) + ". Повторюсь - очень жаль, что вы не солдат...";
			link.l1 = "Мне тоже очень жаль, " + GetAddress_FormToNPC(NPChar) + ", что так вышло. До свидания.";
			link.l1.go = "exit";
			if (pchar.questTemp.WPU.Postcureer == "begin") pchar.quest.PostcureerTime_Over.over = "yes";//снять таймер
			if (pchar.questTemp.WPU.Postcureer == "late") pchar.quest.PostcureerTime_FullOver.over = "yes";//снять второй таймер
			CloseQuestHeader("Postcureer");
			ChangeCharacterComplexReputation(pchar,"nobility", -2);
			pchar.questTemp.WPU.Postcureer.count = sti(pchar.questTemp.WPU.Postcureer.count)-3;//скрутим счетчик
			DeleteAttribute(pchar, "questTemp.WPU.Postcureer.TargetPortmanID");
			DeleteAttribute(pchar, "questTemp.WPU.Current");
			DeleteAttribute(pchar, "questTemp.WPU.Postcureer.LevelUp");
			DeleteAttribute(pchar, "questTemp.WPU.Postcureer.fail");
			pchar.questTemp.WPU.Postcureer = "complete";
		break;
	
//----------------------------------------задания 2 уровня фрахт------------------------------------------

	case "Fraht_LevelUp":
		rColony = GetColonyByIndex(FindColony(npchar.city));
		pchar.questTemp.WPU.Fraht.StartCity = npchar.city;//город квестодателя
		pchar.questTemp.WPU.Fraht.Nation = npchar.nation;//нация получателя
		switch (rand(4))//для тестов
		{
			case 0:
				pchar.questTemp.WPU.Fraht.Goods = GOOD_CHOCOLATE + drand(makeint(GOOD_TOBACCO - GOOD_CHOCOLATE));
				iGoods = pchar.questTemp.WPU.Fraht.Goods;
				//iGoodsQty = 3000 + sti(pchar.rank)*30*(drand(9)+1);
				iGoodsQty = 1000+sti(pchar.rank)*10*(drand(9)+1); // min 1100 max 5000
				pchar.questTemp.WPU.Fraht.GoodsQty = iGoodsQty;
				pchar.questTemp.WPU.Fraht.GoodsAverigePrice = sti(Goods[iGoods].Cost)*2;//двойная цена единицы товара
				pchar.questTemp.WPU.Fraht.Money = sti(Goods[iGoods].Cost)*sti(pchar.questTemp.WPU.Fraht.GoodsQty)*2;//двойная стоимость товара
				pchar.questTemp.WPU.Current1.Add = "двойную";  // лесник  Current1 вместо Current
				dialog.text = "В нашей колонии резко возрос спрос на один товар. В магазине его уже не достать. Я бы хотел попросить вас привезти мне " + GetGoodsNameAlt(iGoods)+ " в количестве " + FindRussianQtyString(iGoodsQty) + ", и готов заплатить за него двойную цену - " + FindRussianMoneyString(sti(pchar.questTemp.WPU.Fraht.GoodsAverigePrice)) + " за единицу. В сумме это составит " + FindRussianMoneyString(sti(pchar.questTemp.WPU.Fraht.Money)) + ". Да, и постарайтесь уложиться за месяц - дольше ждать я не могу.";
				link.l1 = "Хорошо, я берусь за это дело.";
				link.l1.go = "Fraht_LevelUp_Go";
				link.l2 = "Мне жаль разочаровывать вас, но сейчас я заняться этим не могу.";
				link.l2.go = "Fraht_LevelDown";
				SetNull2StoreGood(rColony, sti(pchar.questTemp.WPU.Fraht.Goods));
			break;
		
			case 1:
				pchar.questTemp.WPU.Fraht.Goods = GOOD_EBONY + drand(makeint(GOOD_CINNAMON - GOOD_EBONY));
				iGoods = pchar.questTemp.WPU.Fraht.Goods;
				//iGoodsQty = 1500 + sti(pchar.rank)*20*(drand(9)+1);
				iGoodsQty = 600+sti(pchar.rank)*5*(drand(6)+1); // min 630 max 2000
				pchar.questTemp.WPU.Fraht.GoodsQty = iGoodsQty;
				pchar.questTemp.WPU.Fraht.GoodsAverigePrice = sti(Goods[iGoods].Cost)*2;//двойная цена единицы товара
				pchar.questTemp.WPU.Fraht.Money = sti(Goods[iGoods].Cost)*sti(pchar.questTemp.WPU.Fraht.GoodsQty)*2;//двойная стоимость товара
				pchar.questTemp.WPU.Current1.Add = "двойную"; // лесник  Current1 вместо Current
				dialog.text = "В нашей колонии резко возрос спрос на один товар. В магазине его уже не достать. Я бы хотел попросить вас привезти мне " + GetGoodsNameAlt(iGoods)+ " в количестве " + FindRussianQtyString(iGoodsQty) + ", и готов заплатить за него двойную цену - " + FindRussianMoneyString(sti(pchar.questTemp.WPU.Fraht.GoodsAverigePrice)) + " за единицу. В сумме это составит " + FindRussianMoneyString(sti(pchar.questTemp.WPU.Fraht.Money)) + ". Да, и постарайтесь уложиться за месяц - дольше ждать я не могу.";
				link.l1 = "Хорошо, я берусь за это дело.";
				link.l1.go = "Fraht_LevelUp_Go";
				link.l2 = "Мне жаль разочаровывать вас, но сейчас я заняться этим не могу.";
				link.l2.go = "Fraht_LevelDown";
				SetNull2StoreGood(rColony, sti(pchar.questTemp.WPU.Fraht.Goods));
			break;
		
			case 2:
				//pchar.questTemp.WPU.Fraht.Goods = GOOD_BOMBS + drand(makeint(GOOD_POWDER - GOOD_BOMBS));
				pchar.questTemp.WPU.Fraht.Goods = GOOD_BOMBS;
				iGoods = pchar.questTemp.WPU.Fraht.Goods;
				//iGoodsQty = 15000 + sti(pchar.rank)*300*(drand(9)+1);
				iGoodsQty = 5000+sti(pchar.rank)*10*(drand(9)+1); // min 5100 max 9000
				pchar.questTemp.WPU.Fraht.GoodsQty = iGoodsQty;
				pchar.questTemp.WPU.Fraht.GoodsAverigePrice = sti(Goods[iGoods].Cost)*3;//тройная цена единицы товара
				pchar.questTemp.WPU.Fraht.Money = makeint((sti(Goods[iGoods].Cost)*sti(pchar.questTemp.WPU.Fraht.GoodsQty)*3)/20);//тройная стоимость товара
				pchar.questTemp.WPU.Current1.Add = "тройную"; //лесник  Current1 вместо Current
				dialog.text = "В арсенале нашей колонии катастрофически не хватает " + GetGoodsNameAlt(iGoods)+ ". В магазине этого товара уже не достать. Я бы хотел попросить вас привезти мне " + GetGoodsNameAlt(iGoods)+ " в количестве " + FindRussianQtyString(iGoodsQty) + ", и готов заплатить тройную цену - " + FindRussianMoneyString(sti(pchar.questTemp.WPU.Fraht.GoodsAverigePrice)) + " за единицу. В сумме это составит " + FindRussianMoneyString(sti(pchar.questTemp.WPU.Fraht.Money)) + ". Да, и постарайтесь уложиться за месяц - дольше ждать я не могу.";
				link.l1 = "Хорошо, я берусь за это дело.";
				link.l1.go = "Fraht_LevelUp_Go";
				link.l2 = "Мне жаль разочаровывать вас, но сейчас я заняться этим не могу.";
				link.l2.go = "Fraht_LevelDown";
				SetNull2StoreGood(rColony, sti(pchar.questTemp.WPU.Fraht.Goods));
			break;
		
			case 3:
				pchar.questTemp.WPU.Fraht.Goods = GOOD_MEDICAMENT;
				iGoods = pchar.questTemp.WPU.Fraht.Goods;
				iGoodsQty = 7000 + sti(pchar.rank)*300*(drand(9)+1);
				pchar.questTemp.WPU.Fraht.GoodsQty = iGoodsQty;
				pchar.questTemp.WPU.Fraht.GoodsAverigePrice = sti(Goods[iGoods].Cost)*3;//тройная цена единицы товара
				pchar.questTemp.WPU.Fraht.Money = makeint((sti(Goods[iGoods].Cost)*sti(pchar.questTemp.WPU.Fraht.GoodsQty)*3)/30);//тройная стоимость товара
				pchar.questTemp.WPU.Current1.Add = "тройную"; // лесник  Current1 вместо Current
				dialog.text = "После недавней вспышки эпидемии лихорадки в нашей колонии, мы испытываем острый недостаток в лекарствах - их нет даже в магазине. Губернатор обеспокоен безопасностью города. Я хочу попросить вас привезти мне " + GetGoodsNameAlt(iGoods)+ " в количестве " + FindRussianQtyString(iGoodsQty) + ", и готов заплатить тройную цену - " + FindRussianMoneyString(sti(pchar.questTemp.WPU.Fraht.GoodsAverigePrice)) + " за пачку. В сумме это составит " + FindRussianMoneyString(sti(pchar.questTemp.WPU.Fraht.Money)) + ". Да, и постарайтесь уложиться за месяц - дольше ждать я не могу.";
				link.l1 = "Хорошо, я берусь за это дело.";
				link.l1.go = "Fraht_LevelUp_Go";
				link.l2 = "Мне жаль разочаровывать вас, но сейчас я заняться этим не могу.";
				link.l2.go = "Fraht_LevelDown";
				SetNull2StoreGood(rColony, sti(pchar.questTemp.WPU.Fraht.Goods));
			break;
		
			case 4:
				pchar.questTemp.WPU.Fraht.Goods = GOOD_FOOD;
				iGoods = pchar.questTemp.WPU.Fraht.Goods;
				iGoodsQty = 15000 + sti(pchar.rank)*300*(drand(9)+1);
				pchar.questTemp.WPU.Fraht.GoodsQty = iGoodsQty;
				pchar.questTemp.WPU.Fraht.GoodsAverigePrice = sti(Goods[iGoods].Cost)*2;//двойная цена единицы товара
				pchar.questTemp.WPU.Fraht.Money = makeint((sti(Goods[iGoods].Cost)*sti(pchar.questTemp.WPU.Fraht.GoodsQty)*2)/10);//двойная стоимость товара
				pchar.questTemp.WPU.Current1.Add = "двойную"; // лесник  Current1 вместо Current
				dialog.text = "После неурожая наша колония постоянно нуждается в привозном продовольствии. На данный момент запасы уже на исходе - даже в магазине раскуплены последние запасы. Я хочу попросить вас привезти мне " + GetGoodsNameAlt(iGoods)+ " в количестве " + FindRussianQtyString(iGoodsQty) + ", и готов заплатить двойную цену - " + FindRussianMoneyString(sti(pchar.questTemp.WPU.Fraht.GoodsAverigePrice)) + " за пачку. В сумме это составит " + FindRussianMoneyString(sti(pchar.questTemp.WPU.Fraht.Money)) + ". Да, и постарайтесь уложиться за месяц - дольше ждать я не могу.";
				link.l1 = "Хорошо, я берусь за это дело.";
				link.l1.go = "Fraht_LevelUp_Go";
				link.l2 = "Мне жаль разочаровывать вас, но сейчас я заняться этим не могу.";
				link.l2.go = "Fraht_LevelDown";
				SetNull2StoreGood(rColony, sti(pchar.questTemp.WPU.Fraht.Goods));
			break;
		}
	break;
		
	case "Fraht_LevelDown":
		DialogExit();
		pchar.questTemp.WPU.Fraht.count = sti(pchar.questTemp.WPU.Fraht.count)-1;//скрутим счетчик
	break;
		
	case "Fraht_LevelUp_Go":
		dialog.text = "Отлично! Я рад, что вы согласились. Надеюсь увидеть вас в скором времени снова.";
		link.l1 = "Безусловно, " + GetAddress_FormToNPC(NPChar) + ".";
		link.l1.go = "exit";
		pchar.questTemp.WPU.Fraht = "begin";
		pchar.questTemp.WPU.Fraht.LevelUp = "true";
		pchar.questTemp.WPU.Fraht.count = sti(pchar.questTemp.WPU.Fraht.count) + 1;
		pchar.questTemp.WPU.Fraht.TargetPortmanID = pchar.questTemp.WPU.Fraht.StartCity +"_portman";//ИД портмана
		iGoods = pchar.questTemp.WPU.Fraht.Goods;
		ReOpenQuestHeader("Fraht");
		AddQuestRecord("Fraht", "8");
		AddQuestUserData("Fraht", "sMoney", FindRussianMoneyString(sti(pchar.questTemp.WPU.Fraht.Money)));
		AddQuestUserData("Fraht", "sStartCity", XI_ConvertString("Colony"+pchar.questTemp.WPU.Fraht.StartCity+"Gen"));
		AddQuestUserData("Fraht", "sGoods", GetGoodsNameAlt(iGoods));
		AddQuestUserData("Fraht", "sGoodQty", FindRussianQtyString(sti(pchar.questTemp.WPU.Fraht.GoodsQty)));
		AddQuestUserData("Fraht", "sText", pchar.questTemp.WPU.Current1.Add);
		SetFunctionTimerCondition("FrahtTimeLevelUp_Over", 0, 0, 30, false);
	break;
	
	case "Fraht_completeLevelUp":
	ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
	if(sti(Pchar.Ship.Type) != SHIP_NOTUSED && ok)//проверка на наличие корабля в порту
	{
		iGoods = makeint(pchar.questTemp.WPU.Fraht.Goods);
		amount = sti(pchar.questTemp.WPU.Fraht.GoodsQty) - GetSquadronGoods(pchar, sti(pchar.questTemp.WPU.Fraht.Goods));
		if (amount > 0)
		{
			dialog.text = "Шутить изволите? У вас же нет необходимого количества заказанного мной товара!";
			link.l1 = "Прошу прощения, ошибочка вышла...";
			link.l1.go = "exit";
		}
		else
		{
			dialog.text = "Так, вы должны были привезти груз " + GetGoodsNameAlt(iGoods)+ " в количестве " + FindRussianQtyString(pchar.questTemp.WPU.Fraht.GoodsQty) + ". Замечательно! Благодарю вас. Получите вашу оплату - "+FindRussianMoneyString(sti(pchar.questTemp.WPU.Fraht.Money))+".";
			link.l1 = "Приятно с вами работать, " + GetAddress_FormToNPC(NPChar) + "!";
			link.l1.go = "Fraht_completeLevelUp_1";
		}
	}
	else
	{
		dialog.text = "Что-то я не вижу в порту вашего корабля. Встаньте на рейд и приходите ко мне снова - тогда и поговорим.";
		link.l1 = "Хорошо, я так и сделаю.";
		link.l1.go = "exit";
	}
	break;
	
	case "Fraht_completeLevelUp_1":
		pchar.quest.FrahtTimeLevelUp_Over.over = "yes";//снять таймер
		AddQuestRecord("Fraht", "2");
		CloseQuestHeader("Fraht");
		RemoveCharacterGoods(pchar, sti(pchar.questTemp.WPU.Fraht.Goods), sti(pchar.questTemp.WPU.Fraht.GoodsQty));
		AddMoneyToCharacter(pchar, sti(pchar.questTemp.WPU.Fraht.Money));
		DeleteAttribute(pchar, "questTemp.WPU.Fraht.TargetPortmanID");
		DeleteAttribute(pchar, "questTemp.WPU.Current1"); // лесник  Current1 вместо Current
		DeleteAttribute(pchar, "questTemp.WPU.Fraht.LevelUp");
		pchar.questTemp.WPU.Fraht = "complete";
		AddCharacterExpToSkill(pchar, "Sailing", 100);//навигация
		AddCharacterExpToSkill(pchar, "Commerce", 200);//торговля
		AddCharacterExpToSkill(pchar, "Leadership", 150);//авторитет
		AddCharacterExpToSkill(pchar, "Fortune", 100);//везение
		ChangeCharacterComplexReputation(pchar,"nobility", 2);
		ChangeCharacterNationReputation(pchar, sti(pchar.questTemp.WPU.Fraht.Nation), 2);
		DialogExit();
	break;
	
//----------------------------------------задания 2 уровня эскорт ------------------------------------------

	case "Escort_LevelUp":
		pchar.questTemp.WPU.Escort.LevelUp = "true";//установим атрибут
		pchar.questTemp.WPU.Escort.StartCity = npchar.city;//город квестодателя
		pchar.questTemp.WPU.Escort.Nation = npchar.nation;//нация квестодателя
		pchar.questTemp.WPU.Escort.EnemyNation = GetEnemyNationToMainCharacter();//вражеская нация
		while (pchar.questTemp.WPU.Escort.EnemyNation == PIRATE)
		{
			pchar.questTemp.WPU.Escort.EnemyNation = GetEnemyNationToMainCharacter();
		}
		switch (drand(2))
		{
			case 0://приключения на необитаемых островах
				pchar.questTemp.WPU.Current.TargetIslandID = DesIsland();//выбор необитайки
				while (!isLocationFreeForQuests(pchar.questTemp.WPU.Current.TargetIslandID)) pchar.questTemp.WPU.Current.TargetIslandID = DesIsland();
				pchar.questTemp.WPU.Escort.ShipType = Escort_ShipType();//выбор корабля
				pchar.questTemp.WPU.Escort.ShipName = GenerateRandomNameToShip(sti(pchar.nation));//имя корабля
				pchar.questTemp.WPU.Escort.TargetPortmanID = pchar.questTemp.WPU.Escort.StartCity +"_portman";//ИД портмана
				pchar.questTemp.WPU.Escort.ShipBaseName = GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.questTemp.WPU.Escort.ShipType), "Name") + "Gen"));
				dialog.text = "Эта беда случилась десять дней назад... Торговый караван, направлявшийся в нашу колонию, был атакован пиратами. Налетевший шторм вынудил пиратов отступить, но корабли каравана были размётаны кто куда и потеряли друг друга. В дальнейшем все суда прибыли в разные порты, кроме одного\n"+pchar.questTemp.WPU.Escort.ShipBaseName+" '"+pchar.questTemp.WPU.Escort.ShipName+"' бесследно пропал, его судьба так и осталась неизвестной. Предположительно корабль исчез в районе необитаемого острова "+XI_ConvertString(pchar.questTemp.WPU.Current.TargetIslandID)+". Я прошу вас отправиться туда, разыскать указанное судно и привести его в наш порт. Либо получить доказательства его гибели. Размер вашего гонорара определим после выполнения работы, но могу сказать, что он будет достаточно большим.";
				link.l1 = "Конечно же я согласен!";
				link.l1.go = "Escort_LevelUp_1";
				link.l2 = "Сожалею, но мне это не подходит. Вынужден отказаться.";
				link.l2.go = "Escort_LevelUp_exit";
			break;
			case 1://защитить конвой вблизи текущего острова от пиратов
				pchar.questTemp.WPU.Current.TargetIslandID = Islands[GetCharacterCurrentIsland(PChar)].id;//текущий остров
				pchar.questTemp.WPU.Escort.TargetPortmanID = pchar.questTemp.WPU.Escort.StartCity +"_portman";//ИД портмана
				dialog.text = "В нашу колонию должен был прибыть торговый караван. Но на самом подходе к порту караван был атакован дерзкими пиратами. Бой идёт вдали от форта, кораблей охранения у меня на данный момент нет - мы ничем не можем помочь попавшим в беду купцам. Вы отважный капитан, прошу вас - вмешайтесь в это сражение, помогите расправиться с пиратами! Вы сделаете это?";
				link.l1 = "Конечно же! Это дело чести!";
				link.l1.go = "Escort_LevelUp_2";
				link.l2 = "Сожалею, но мне это не подходит. Вынужден отказаться.";
				link.l2.go = "Escort_LevelUp_exit";
			break;
			case 2://встретить и довести
				pchar.questTemp.WPU.Escort.ShipName = GenerateRandomNameToShip(sti(pchar.nation));
				pchar.questTemp.WPU.Escort.ShipType = Escort_ShipType();
				pchar.questTemp.WPU.Escort.City = findCurrentCity1(npchar);//город, откуда забрать
				pchar.questTemp.WPU.Escort.TargetPortmanID = pchar.questTemp.WPU.Escort.City +"_portman";//ИД портмана
				sld = characterFromId(pchar.questTemp.WPU.Escort.TargetPortmanID);
				pchar.questTemp.WPU.Escort.Nation = sld.nation;//нация получателя
				pchar.questTemp.WPU.Current.TargetIslandID = GetCharacterCurrentIslandId(npchar);//ИД целевого ареала
				pchar.questTemp.WPU.Escort.DaysQty = GetMaxDaysFromIsland2Island(GetArealByCityName(pchar.questTemp.WPU.Escort.StartCity), GetArealByCityName(pchar.questTemp.WPU.Escort.City));//расстояние в днях
				pchar.questTemp.WPU.Escort.Money = sti(pchar.questTemp.WPU.Escort.DaysQty)*2000+20000;
				pchar.questTemp.WPU.Escort.Chance = rand(1);
				dialog.text = "В колонию "+XI_ConvertString(pchar.questTemp.WPU.Escort.City)+" прибыло судно с оружием и боеприпасами для нашей колонии. Судно сопровождения село на прибрежные рифы, получило очень сильные повреждения и выйти в море сможет ещё не скоро. Мы не можем позволить себе рисковать, отправляя корабль с арсеналом в одиночку\nЯ предлагаю вам осуществить его эскорт до нашей колонии. Оплата за работу установлена в размере "+FindRussianMoneyString(sti(pchar.questTemp.WPU.Escort.Money))+".";
				link.l1 = "Конечно же я согласен!";
				link.l1.go = "Escort_LevelUp_0";
				link.l2 = "Сожалею, но мне это не подходит. Вынужден отказаться.";
				link.l2.go = "Escort_LevelUp_exit";
			break;
		}
	break;
	
	case "Escort_LevelUp_exit":
		dialog.text = "Жаль, очень жаль. А я так на вас надеялся...";
		link.l1 = "Мне тоже жаль. До свидания, " + GetAddress_FormToNPC(NPChar) + ".";
		link.l1.go = "exit";
		pchar.questTemp.WPU.Escort.count = sti(pchar.questTemp.WPU.Escort.count)-1;//скрутим счетчик
		DeleteAttribute(pchar, "questTemp.WPU.Escort.LevelUp");
		DeleteAttribute(pchar, "questTemp.WPU.Escort.TargetPortmanID");
	break;
	
	case "Escort_LevelUp_0":
		dialog.text = "Замечательно! Я знал, что могу на вас рассчитывать. Постарайтесь не задерживаться - думаю, "+FindRussianDaysString(pchar.questTemp.WPU.Escort.DaysQty)+" будет вполне достаточно, чтобы добраться до "+XI_ConvertString("Colony"+pchar.questTemp.WPU.Escort.City+"Gen")+". Вот, возьмите эту верительную грамоту для удостоверения вашей личности. Попутного ветра, капитан!";
		link.l1 = "Спасибо! Не беспокойтесь, я вас не подведу.";
		link.l1.go = "Escort_LevelUp_0_go";
	break;
	
	case "Escort_LevelUp_0_go":
		ReOpenQuestHeader("Escort");
		AddQuestRecord("Escort", "19");
		AddQuestUserData("Escort", "sMoney", FindRussianMoneyString(sti(pchar.questTemp.WPU.Escort.Money)));
		AddQuestUserData("Escort", "sStartCity", XI_ConvertString("Colony"+pchar.questTemp.WPU.Escort.StartCity+"Gen"));
		AddQuestUserData("Escort", "sTargetColony",XI_ConvertString("Colony"+pchar.questTemp.WPU.Escort.City));
		AddQuestUserData("Escort", "sDay", FindRussianDaysString(pchar.questTemp.WPU.Escort.DaysQty));
		SetFunctionTimerCondition("EscortArsenalShip_Over", 0, 0, sti(pchar.questTemp.WPU.Escort.DaysQty)+1, false);
		DialogExit();
		pchar.questTemp.WPU.Escort = "begin";
		pchar.questTemp.WPU.Escort.LevelUp_0 = "true";
		pchar.questTemp.WPU.Escort.count = sti(pchar.questTemp.WPU.Escort.count)+1;
	break;
	
	case "Escort_LUGo_0":
	ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
	if(sti(Pchar.Ship.Type) != SHIP_NOTUSED && ok)//проверка на наличие корабля в порту
	{
		pchar.quest.EscortArsenalShip_Over.over = "yes";
		dialog.text = "Ну наконец-то! Мне этот корабль уже все глаза намозолил. Принимайте командование. Судно называется "+pchar.questTemp.WPU.Escort.ShipName+", его капитан будет немедленно извещён о вашем прибытии.";
		link.l1 = "Спасибо. Пусть готовит свой корабль к отплытию - я намерен отправиться в путь как можно быстрее.";
		link.l1.go = "Escort_LUGo_01";
	}
	else
	{
		dialog.text = "Что-то я не вижу в порту вашего корабля. Встаньте на рейд и приходите ко мне снова, тогда и поговорим.";
		link.l1 = "Хорошо, я так и сделаю.";
		link.l1.go = "exit";
	}
	break;
	
	case "Escort_LUGo_01"://добавляем компаньона
		int iShipType = sti(pchar.questTemp.WPU.Escort.ShipType);
		sTemp = pchar.questTemp.WPU.Escort.ShipName;
		sld = GetCharacter(NPC_GenerateCharacter("ArsenalShipCaptain", "citiz_41", "man", "man", 15, sti(pchar.nation), -1, true, "quest"));
		FantomMakeSmallSailor(sld, iShipType, sTemp, CANNON_TYPE_CANNON_LBS16, 65, 22, 24, 35, 33);
		SetFantomParamFromRank(sld, 15, true); 
		SetCaptanModelByEncType(sld, "war");
		SetCharacterGoods(sld, GOOD_FOOD, 500);
		SetCharacterGoods(sld, GOOD_BALLS, 5000);
		SetCharacterGoods(sld, GOOD_GRAPES, 3000);
		SetCharacterGoods(sld, GOOD_KNIPPELS, 3000);
		SetCharacterGoods(sld, GOOD_BOMBS, 5000);
		SetCharacterGoods(sld, GOOD_POWDER, 10000);
		SetCharacterGoods(sld, GOOD_WEAPON, 3000);
		sld.CompanionEnemyEnable = false; //всегда друзья
		SetCompanionIndex(pchar, -1, sti(sld.index));
		SetCharacterRemovable(sld, false);
		sld.loyality = MAX_LOYALITY;
		sld.Dialog.Filename = "Common_portman.c";
		sld.dialog.currentnode = "Escort_companion";
		DialogExit();
		AddQuestRecord("Escort", "20");
		AddQuestUserData("Escort", "sSName", pchar.questTemp.WPU.Escort.ShipName);
		pchar.quest.Escort_fail.win_condition.l1 = "NPC_Death";//прерывание на потопление сопровождаемого
		pchar.quest.Escort_fail.win_condition.l1.character = "ArsenalShipCaptain";
		pchar.quest.Escort_fail.function = "EscortArsenalShip_failed";
		SetFunctionTimerCondition("EscortArsenalShipGo_Over", 0, 0, sti(pchar.questTemp.WPU.Escort.DaysQty)+6, false);
		DeleteAttribute(pchar, "questTemp.WPU.Escort.LevelUp_0");
		pchar.questTemp.WPU.Escort.LevelUpGo_0 = "true";
		if (sti(pchar.questTemp.WPU.Escort.Chance) == 0) EnemyNationHunterOnMap(true);//скоростной перехватчик
		else FrahtHunterOnSea();
	break;
	
	case "Escort_LUGo_complete":
	ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
	if(sti(Pchar.Ship.Type) != SHIP_NOTUSED && ok)//проверка на наличие корабля в порту
	{
		pchar.quest.Escort_fail.over = "yes";
		pchar.quest.EscortArsenalShipGo_Over.over = "yes";
		dialog.text = "Отлично! Вы уже в который раз доказываете, что на вас можно положиться. Спасибо за проделанную работу. Получите ваше вознаграждение - "+FindRussianMoneyString(sti(pchar.questTemp.WPU.Escort.Money))+". Не забывайте периодически навещать меня - работа для такого капитана, как вы, есть практически всегда.";
		link.l1 = "Приятно это слышать, " + GetAddress_FormToNPC(NPChar) + "! Безусловно, мы будем сотрудничать и дальше. Всего доброго!";
		link.l1.go = "Escort_LUGo_complete_1";
	}
	else
	{
		dialog.text = "Что-то я не вижу в порту вашего корабля. Встаньте на рейд и приходите ко мне снова, тогда и поговорим.";
		link.l1 = "Хорошо, я так и сделаю.";
		link.l1.go = "exit";
	}
	break;
	
	case "Escort_LUGo_complete_1":
		RemoveCharacterCompanion(Pchar, characterFromID("ArsenalShipCaptain"));
		sld = characterFromId("ArsenalShipCaptain");
		sld.lifeday = 0;//на всякий случай
		AddMoneyToCharacter(pchar, sti(pchar.questTemp.WPU.Escort.Money));
		ChangeCharacterComplexReputation(pchar,"nobility", 2);
		ChangeCharacterNationReputation(pchar, sti(pchar.questTemp.WPU.Escort.Nation), 2);
		AddQuestRecord("Escort", "24");
		AddQuestUserData("Escort", "sSName", pchar.questTemp.WPU.Escort.ShipName);
		CloseQuestHeader("Escort");
		DialogExit();
		pchar.questTemp.WPU.Escort = "complete";
		DeleteAttribute(pchar, "questTemp.WPU.Escort.LevelUpGo_0");
		DeleteAttribute(pchar, "questTemp.WPU.Escort.LevelUp");
		DeleteAttribute(pchar, "questTemp.WPU.Escort.TargetPortmanID");
		AddComplexSeaExpToScill(100, 100, 100, 0, 100, 0, 0);
		AddComplexSelfExpToScill(30, 30, 30, 30);
		AddCharacterExpToSkill(pchar, "Leadership", 100);//авторитет
		SaveCurrentNpcQuestDateParam(npchar, "work_date");
	break;
	
	case "Escort_LevelUp_1":
		dialog.text = "Тогда я пожелаю вам счастливого пути. И не затягивайте с поисками, прошу вас! Возможно, моряки с этого судна нуждаются в немедленной помощи.";
		link.l1 = "Я понял. Отправляюсь в путь сегодня же!";
		link.l1.go = "Escort_LevelUp_1_select";
	break;
	
	case "Escort_LevelUp_1_select"://выберем приключение
		switch (rand(2))
		{
			case 0://весь побитый и остался без мачты
				pchar.quest.DisasterShip_WM.win_condition.l1 = "location";
				pchar.quest.DisasterShip_WM.win_condition.l1.location = pchar.questTemp.WPU.Current.TargetIslandID;
				pchar.quest.DisasterShip_WM.function = "CreateDisasterShip_WithoutMasts";
				pchar.questTemp.WPU.Escort.LevelUp_1WM = "true";
			break;
			case 1://ведет бой с пиратусами в шторме
				pchar.quest.DisasterShip_VSP.win_condition.l1 = "location";
				pchar.quest.DisasterShip_VSP.win_condition.l1.location = pchar.questTemp.WPU.Current.TargetIslandID;
				pchar.quest.DisasterShip_VSP.function = "CreateDisasterShip_VSPirate";
				for (i=0; i<MAX_ISLANDS; i++)//устроим шторм
				{				
					if (Islands[i].id == pchar.questTemp.WPU.Current.TargetIslandID)
					{
					Islands[i].alwaysStorm = true; 
					Islands[i].storm = true;
					Islands[i].tornado = true; 
					}
				}
				pchar.questTemp.WPU.Escort.LevelUp_1VSP = "true";
			break;
			case 2://потонул
				pchar.questTemp.WPU.Current.TargetIslandID.Shore = SelectQuestShoreLocationFromSea(pchar.questTemp.WPU.Current.TargetIslandID);
				pchar.quest.DisasterShip_S.win_condition.l1 = "location";
				pchar.quest.DisasterShip_S.win_condition.l1.location = pchar.questTemp.WPU.Current.TargetIslandID.Shore;
				pchar.quest.DisasterShip_S.function = "CreateDisasterShip_Crew";
				pchar.questTemp.WPU.Escort.LevelUp_1S = "true";
			break;
		}
		ReOpenQuestHeader("Escort");
		AddQuestRecord("Escort", "25");
		AddQuestUserData("Escort", "sStartCity", XI_ConvertString("Colony"+pchar.questTemp.WPU.Escort.StartCity+"Gen"));
		AddQuestUserData("Escort", "sIsland", XI_ConvertString(pchar.questTemp.WPU.Current.TargetIslandID));
		AddQuestUserData("Escort", "sSName", pchar.questTemp.WPU.Escort.ShipName);
		AddQuestUserData("Escort", "sTargetColony",XI_ConvertString("Colony"+pchar.questTemp.WPU.Escort.City));
		SetFunctionTimerCondition("DesIsland_Over", 0, 0, 15, false);
		DialogExit();
		pchar.questTemp.WPU.Escort = "begin";
		pchar.questTemp.WPU.Escort.count = sti(pchar.questTemp.WPU.Escort.count)+1;
	break;
	
	case "Escort_LU1WM_complete":
	ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
	if(sti(Pchar.Ship.Type) != SHIP_NOTUSED && ok)//проверка на наличие корабля в порту
	{
		dialog.text = "Да, мне уже сообщили. Великолепная работа, " + GetAddress_Form(NPChar) + "! Вы уже в который раз доказываете, что на вас можно положиться. Получите ваше вознаграждение - 30 000 песо\nНе забывайте периодически заглядывать ко мне - такие люди как вы, по праву могут считаться незаменимыми, и у меня обязательно найдётся для вас работа.";
		link.l1 = "Приятно это слышать, " + GetAddress_FormToNPC(NPChar) + "! Безусловно, мы будем сотрудничать и дальше. Всего доброго!";
		link.l1.go = "Escort_LU1WM_complete_1";
	}
	else
	{
		dialog.text = "Что-то я не вижу в порту вашего корабля. Встаньте на рейд и приходите ко мне снова, тогда и поговорим.";
		link.l1 = "Хорошо, я так и сделаю.";
		link.l1.go = "exit";
	}
	break;
	
	case "Escort_LU1WM_complete_1":
		sld = characterFromId("WMCaptain");
		sld.lifeday = 0;
		DialogExit();
		AddMoneyToCharacter(pchar, 30000);
		ChangeCharacterComplexReputation(pchar,"nobility", 5);
		ChangeCharacterNationReputation(pchar, sti(pchar.questTemp.WPU.Escort.Nation), 5);
		AddQuestRecord("Escort", "32");
		AddQuestUserData("Escort", "sStartCity", XI_ConvertString("Colony"+pchar.questTemp.WPU.Escort.StartCity+"Gen"));
		AddQuestUserData("Escort", "sMoney", 30000);
		CloseQuestHeader("Escort");
		pchar.questTemp.WPU.Escort = "complete";
		DeleteAttribute(pchar, "questTemp.WPU.Escort.LevelUp_1WM");
		DeleteAttribute(pchar, "questTemp.WPU.Escort.LevelUp");
		DeleteAttribute(pchar, "questTemp.WPU.Escort.TargetPortmanID");
		AddCharacterExpToSkill(pchar, "Sailing", 100);//навигация
		AddCharacterExpToSkill(pchar, "Repair", 300);//починка
		AddCharacterExpToSkill(pchar, "Commerce", 100);//торговля
		AddCharacterExpToSkill(pchar, "Leadership", 100);//авторитет
		AddCharacterExpToSkill(pchar, "Fortune", 100);//везение
		SaveCurrentNpcQuestDateParam(npchar, "work_date");
	break;
	
	case "Escort_LU1VSP_complete":
	ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
	if(sti(Pchar.Ship.Type) != SHIP_NOTUSED && ok)//проверка на наличие корабля в порту
	{
		dialog.text = "Да, он мне уже всё рассказал - как вы героически защищали его судно в бою с пиратами. Отличная работа, " + GetAddress_Form(NPChar) + "! Вы уже в который раз доказываете, что на вас можно положиться. Получите ваше вознаграждение - 50 000 песо\nНе забывайте периодически заглядывать ко мне - такие люди как вы, по праву могут считаться незаменимыми, и у меня обязательно найдётся для вас работа.";
		link.l1 = "Приятно это слышать, " + GetAddress_FormToNPC(NPChar) + "! Безусловно, мы будем сотрудничать и дальше. Всего доброго!";
		link.l1.go = "Escort_LU1VSP_complete_1";
	}
	else
	{
		dialog.text = "Что-то я не вижу в порту вашего корабля. Встаньте на рейд и приходите ко мне снова, тогда и поговорим.";
		link.l1 = "Хорошо, я так и сделаю.";
		link.l1.go = "exit";
	}
	break;
	
	case "Escort_LU1VSP_complete_1":
		sld = characterFromId("WMCaptain");
		sld.lifeday = 0;
		DialogExit();
		AddMoneyToCharacter(pchar, 50000);
		ChangeCharacterComplexReputation(pchar,"nobility", 10);
		ChangeCharacterNationReputation(pchar, sti(pchar.questTemp.WPU.Escort.Nation), 6);
		AddQuestRecord("Escort", "32");
		AddQuestUserData("Escort", "sStartCity", XI_ConvertString("Colony"+pchar.questTemp.WPU.Escort.StartCity+"Gen"));
		AddQuestUserData("Escort", "sMoney", 50000);
		CloseQuestHeader("Escort");
		pchar.questTemp.WPU.Escort = "complete";
		DeleteAttribute(pchar, "questTemp.WPU.Escort.LevelUp_1VSP");
		DeleteAttribute(pchar, "questTemp.WPU.Escort.LevelUp");
		DeleteAttribute(pchar, "questTemp.WPU.Escort.TargetPortmanID");
		AddComplexSeaExpToScill(100, 150, 150, 100, 0, 0, 0);
		AddComplexSelfExpToScill(50, 50, 50, 50);
		AddCharacterExpToSkill(pchar, "Leadership", 100);//авторитет
		AddCharacterExpToSkill(pchar, "Fortune", 100);//везение
		SaveCurrentNpcQuestDateParam(npchar, "work_date");
	break;
	
	case "Escort_LU1VSP_completeSink":
		dialog.text = "Какой трагический конец... упокой, Господи, их души.";
		link.l1 = "Я сделал всё, что было в моих силах, " + GetAddress_FormToNPC(NPChar) + ". Ситуацию осложнило то, что бой пришлось вести в шторм.";
		link.l1.go = "Escort_LU1VSP_completeSink_1";
	break;
	
	case "Escort_LU1VSP_completeSink_1":
		dialog.text = "Я верю, " + GetAddress_Form(NPChar) + ", что вы предприняли всё возможное, чтобы спасти корабль и несчастных моряков. Увы... Возьмите ваше вознаграждение - 10 000 песо, и спасибо за службу.";
		link.l1 = "Не за что, " + GetAddress_FormToNPC(NPChar) + ". Мне тоже очень жаль. До свидания.";
		link.l1.go = "Escort_LU1VSP_completeSink_2";
	break;
	
	case "Escort_LU1VSP_completeSink_2":
		DialogExit();
		AddMoneyToCharacter(pchar, 10000);
		ChangeCharacterComplexReputation(pchar,"nobility", 1);
		AddQuestRecord("Escort", "32");
		AddQuestUserData("Escort", "sStartCity", XI_ConvertString("Colony"+pchar.questTemp.WPU.Escort.StartCity+"Gen"));
		AddQuestUserData("Escort", "sMoney", 10000);
		CloseQuestHeader("Escort");
		pchar.questTemp.WPU.Escort = "complete";
		DeleteAttribute(pchar, "questTemp.WPU.Escort.LevelUp_1VSP");
		DeleteAttribute(pchar, "questTemp.WPU.Escort.LevelUp");
		DeleteAttribute(pchar, "questTemp.WPU.Escort.TargetPortmanID");
		AddComplexSeaExpToScill(50, 50, 50, 50, 0, 0, 0);
		AddCharacterExpToSkill(pchar, "Fortune", 50);//везение
		SaveCurrentNpcQuestDateParam(npchar, "work_date");
	break;
	
	case "Escort_LU1S_complete":
		dialog.text = "Да, он мне уже всё рассказал - как вы героически сражались с краснокожими язычниками, а затем с пиратским кораблём. Отличная работа, " + GetAddress_Form(NPChar) + "! Вы уже в который раз доказываете, что на вас можно положиться\nПолучите ваше вознаграждение - 40 000 песо. Не забывайте периодически заглядывать ко мне - такие люди как вы, по праву могут считаться незаменимыми, и у меня обязательно найдётся для вас работа.";
		link.l1 = "Приятно это слышать, " + GetAddress_FormToNPC(NPChar) + "! Безусловно, мы будем сотрудничать и дальше. Всего доброго!";
		link.l1.go = "Escort_LU1S_complete_1";
	break;
	
	case "Escort_LU1S_complete_1":
		sld = characterFromId("WMCaptain");
		sld.lifeday = 0;
		DialogExit();
		AddMoneyToCharacter(pchar, 40000);
		ChangeCharacterComplexReputation(pchar,"nobility", 8);
		ChangeCharacterNationReputation(pchar, sti(pchar.questTemp.WPU.Escort.Nation), 3);
		AddQuestRecord("Escort", "32");
		AddQuestUserData("Escort", "sStartCity", XI_ConvertString("Colony"+pchar.questTemp.WPU.Escort.StartCity+"Gen"));
		AddQuestUserData("Escort", "sMoney", 40000);
		CloseQuestHeader("Escort");
		pchar.questTemp.WPU.Escort = "complete";
		DeleteAttribute(pchar, "questTemp.WPU.Escort.LevelUp_1S");
		DeleteAttribute(pchar, "questTemp.WPU.Escort.LevelUp");
		DeleteAttribute(pchar, "questTemp.WPU.Escort.TargetPortmanID");
		AddComplexSeaExpToScill(100, 150, 150, 100, 0, 0, 0);
		AddComplexSelfExpToScill(100, 100, 100, 100);
		AddCharacterExpToSkill(pchar, "Leadership", 100);//авторитет
		AddCharacterExpToSkill(pchar, "Fortune", 100);//везение
		SaveCurrentNpcQuestDateParam(npchar, "work_date");
	break;
	
	case "Escort_LevelUp_2":
		dialog.text = "Я знал, что могу на вас рассчитывать. Удачи, капитан! Вся колония желает вам победы!";
		link.l1 = "Постараюсь оправдать ваши надежды. Выхожу в море, и да поможет нам Бог!";
		link.l1.go = "Escort_LevelUp_2_go";
	break;
	
	case "Escort_LevelUp_2_go":
		ReOpenQuestHeader("Escort");
		AddQuestRecord("Escort", "41");
		AddQuestUserData("Escort", "sStartCity", XI_ConvertString("Colony"+pchar.questTemp.WPU.Escort.StartCity+"Gen"));
		SetFunctionTimerCondition("CaravanNearIsland_Over", 0, 0, 2, false);
		pchar.questTemp.WPU.Escort.count = sti(pchar.questTemp.WPU.Escort.count)+1;
		pchar.quest.CaravanNearIsland_Start.win_condition.l1 = "location";
		pchar.quest.CaravanNearIsland_Start.win_condition.l1.location = pchar.questTemp.WPU.Current.TargetIslandID;
		pchar.quest.CaravanNearIsland_Start.function = "CreateCaravanNearIsland";
		pchar.questTemp.WPU.Escort.LevelUp_2 = "true";
		pchar.questTemp.WPU.Escort = "begin";
		DialogExit();
	break;
	
	case "Escort_LU2_complete":
		switch (sti(pchar.questTemp.WPU.Escort.LevelUp_2.Qty))
		{
			case 1:
				pchar.questTemp.WPU.Escort.LevelUp_2.Money = 10000;
				dialog.text = "Да, весь город наблюдал за сражением. Жаль купцов, конечно, очень жаль. Но один корабль вы всё же спасли. Поэтому награда в 10 000 песо вами честно заслужена. Возьмите эти деньги и большое спасибо за оказанную помощь.";
				link.l1 = "Не за что... Досадно, что бой прошёл не лучшим образом, но я сделал всё, что мог. До свидания, " + GetAddress_FormToNPC(NPChar) + ".";
				link.l1.go = "Escort_LU2_complete_1";
			break;
			case 2:
				pchar.questTemp.WPU.Escort.LevelUp_2.Money = 25000;
				dialog.text = "Да, весь город наблюдал за сражением. Вы очень грамотно вели бой. Жаль погибшего купца, конечно, очень жаль. Но если бы не вы, никто из них мог бы не уйти живым. Поэтому награда в 25 000 песо вами полностью заслужена. Возьмите эти деньги и большое спасибо за оказанную помощь.";
				link.l1 = "Благодарю за лестную оценку моих действий, но я не считаю, что провёл сражение хорошо - один корабль потерян. Ну что же... такова судьба. До свидания, " + GetAddress_FormToNPC(NPChar) + ".";
				link.l1.go = "Escort_LU2_complete_1";
			break;
			case 3:
				pchar.questTemp.WPU.Escort.LevelUp_2.Money = 50000;
				dialog.text = "Да, весь город наблюдал за сражением. Вы были великолепны! Как лихо вы разгромили эскадру грязных пиратов! Они убедились на своей шкуре, каково это - противостоять морскому военному офицеру, а не беззащитному торговцу. Жаль, эта наука им уже не пригодится... Ваше вознаграждение составляет 50 000 песо - получите, пожалуйста.";
				link.l1 = "Благодарю за лестную оценку моих действий! Всегда рад помочь. А теперь, " + GetAddress_FormToNPC(NPChar) + " позвольте откланяться.";
				link.l1.go = "Escort_LU2_complete_1";
			break;
		}
	break;
	
	case "Escort_LU2_complete_1":
		iTemp = sti(pchar.questTemp.WPU.Escort.LevelUp_2.Qty);
		DialogExit();
		Group_DeleteGroup("CaravanShip");
		AddMoneyToCharacter(pchar, sti(pchar.questTemp.WPU.Escort.LevelUp_2.Money));
		ChangeCharacterComplexReputation(pchar,"nobility", iTemp*2);
		ChangeCharacterNationReputation(pchar, sti(pchar.questTemp.WPU.Escort.Nation), iTemp);
		AddQuestRecord("Escort", "32");
		AddQuestUserData("Escort", "sStartCity", XI_ConvertString("Colony"+pchar.questTemp.WPU.Escort.StartCity+"Gen"));
		AddQuestUserData("Escort", "sMoney", sti(pchar.questTemp.WPU.Escort.LevelUp_2.Money));
		CloseQuestHeader("Escort");
		AddCharacterExpToSkill(pchar, "Sailing", iTemp*35);//навигация
		AddCharacterExpToSkill(pchar, "Accuracy", iTemp*50);//меткость
		AddCharacterExpToSkill(pchar, "Cannons", iTemp*50);//орудия
		AddCharacterExpToSkill(pchar, "Grappling", iTemp*35);//абордаж
		AddCharacterExpToSkill(pchar, "Leadership", iTemp*40);//авторитет
		AddCharacterExpToSkill(pchar, "Fortune", iTemp*35);//везение
		AddCharacterExpToSkill(pchar, "FencingLight", iTemp*35);//легкое оружие
		AddCharacterExpToSkill(pchar, "Fencing", iTemp*35);//среднее оружие
		AddCharacterExpToSkill(pchar, "FencingHeavy", iTemp*35);//тяжелое оружие
		AddCharacterExpToSkill(pchar, "Pistol", iTemp*35); //пистоли
		pchar.questTemp.WPU.Escort = "complete";
		DeleteAttribute(pchar, "questTemp.WPU.Escort.LevelUp_2");
		DeleteAttribute(pchar, "questTemp.WPU.Escort.LevelUp");
		DeleteAttribute(pchar, "questTemp.WPU.Escort.TargetPortmanID");
		SaveCurrentNpcQuestDateParam(npchar, "work_date");
	break;
	
		case "PortmanQuest_NF":
			dialog.text = "Хм, это плохо. В таком случае, ни о какой новой работе у меня не может быть и речи.";
			link.l1 = "Понятно. Вот ещё что хотел"+ GetSexPhrase("","а") +" сказать...";
			link.l1.go = "node_2";
		break;
		
		//сгоревшее судно
		case "BurntShip2":
			dialog.text = "Очень жаль, капитан... очень жаль, что вы не хотите мне помочь.";
			link.l1 = "Тут не в желании дело, уважаемый. Вы же сами понимаете... До свидания...";
			link.l1.go = "exit";
			NPChar.Quest.BurntShip.LastQuestDate = sLastSpeakDate;
		break;
		
		case "BurntShip4":
			dialog.text = "Да что вы, капитан?! Побойтесь Бога!.. Как можно?! Я своё дело твёрдо знаю, чай столько лет служу. И страховые договора есть, и страховая контора выплату готова произвести, и сумма страховая немалая, уверяю вас.";
			link.l1 = "Уважаемый, так в чём же ваша проблема? От пожара взорвалась крюйт-камера, и пострадали люди, а  вас привлекают к суду за халатность?";
			link.l1.go = "BurntShip5";
		break;
		
		case "BurntShip5":
			sCapitainId = GenerateRandomName(sti(NPChar.nation), "man");
			
			dialog.text = "Ну уж чего не было, того не было, - Господь миловал, иначе бы не сносить мне головы. Пустёхонек трюм был, как есть пуст был, слава тебе Господи, Пресвятая Дева Мария!\n" +
				"А вся проблема в том, что судно-то принадлежит... вернее принадлежало, известному на все Карибы господину по имени " + sCapitainId + ". И строилось оно в Европе по спецзаказу, с неординарными характеристиками. " +
				"И этим судном владелец очень гордился и хвастался где ни попадя, болван эдакий, прости Господи... Что я теперь ему скажу? Хоть в петлю лезь, ей-богу...";
			link.l1 = "О-о, вижу, вы здорово влипли. А что у него не так было, как у всех судов? То есть, чем в своём кораблике этот господин так гордился?";
			link.l1.go = "BurntShip6";
			
			NPChar.Quest.BurntShip.ShipOwnerName = sCapitainId;
		break;
		
		case "BurntShip6":
			BurntShipQuest_FillStartParams(NPChar);
			
			attrL = NPChar.Quest.BurntShip.ShipAttribute;
			iTest = sti(NPChar.Quest.BurntShip.ShipType);
			
			switch(attrL)
			{
				case "speedrate":
					attrL = "У его " + GetStrSmallRegister(XI_ConvertString(ShipsTypes[iTest].Name + "Gen")) + " скорость по ветру была более " + NPChar.Quest.BurntShip.ShipNeededValue + " узлов. Для капера это первейшая гордость была... Он просто велит своим молодчикам повесить меня на рее! Чёрт принёс его в нашу гавань вместе с его пиратской лоханкой...";
				break;
				
				case "turnrate":
					attrL = "У его " + GetStrSmallRegister(XI_ConvertString(ShipsTypes[iTest].Name + "Gen")) + " манёвренность была более " + NPChar.Quest.BurntShip.ShipNeededValue + " единиц. Это для вояки первейшая гордость была... Он велит засечь меня шпицрутенами! Чёрт его надоумил оставить у меня свою посудину...";
				break;
				
				case "capacity":
					attrL = "У его " + GetStrSmallRegister(XI_ConvertString(ShipsTypes[iTest].Name + "Gen")) + " дедвейт был более " + NPChar.Quest.BurntShip.ShipNeededValue + " единиц водоизмещения. Для купца это первейшая гордость была... Он меня без суда четвертует. Чёрт его дёрнул именно у меня своё корыто оставить!";
				break;
			}
			
			dialog.text = attrL;
			link.l1 = "А что на верфи говорят? Неужели здесь такое соорудить невозможно?";
			link.l1.go = "BurntShip7";
		break;
		
		case "BurntShip7":
			dialog.text = "Никто не берётся. Я уж и на соседний остров ходил с поклоном. Говорят, что в Шарптауне мастер есть знатный. Но где мы, - а где Исла Тесоро. Осталось только на помощь таких свободных капитанов, как вы рассчитывать. Ведь вы топите эти лоханки десятками. Может вам не составит труда подыскать подобное судёнышко для меня. А мы его здесь подкрасим, подправим, чтоб хозяин не в претензии был\n" +
				"Я щедро отблагодарю, и страховая компания не поскупится. Дело-то неординарное, сами понимаете. Кому охота в немилость к такому влиятельному господину попасть?";
			link.l1 = "Да, дело не простое. А сколько у меня есть времени?";
			link.l1.go = "BurntShip8";
			link.l2 = "Нет, милейший, не возьмусь я за это. Да и гарантий никто не даст, что судно с подобными характеристиками существует. Не обессудь...";
			link.l2.go = "BurntShip2";
		break;
		
		case "BurntShip8":
			dialog.text = "Время, слава Богу, есть. Хозяин отбыл в Европу и ранее полугода не обернётся.";
			link.l1 = "Что ж, берусь. Доставлю я вам подобное судно. Но учтите, если начнёте скупиться и выкраивать - сожгу его прямо у вас на глазах!";
			link.l1.go = "BurntShip9";
		break;
		
		case "BurntShip9":
			dialog.text = "Да что вы, капитан? Как можно? Я же понимаю, что это не лоханку из первой лужи выловить, тут время потребуется... Вы только приведите судно, а мы уж расстараемся. Будьте уверены...";
			link.l1 = "Надеюсь... Ждите меня с хорошими вестями. До свидания.";
			link.l1.go = "BurntShip9_exit";
		break;
		
		case "BurntShip9_exit":
			attrL = "BurntShipQuest_TimeIsOver_" + NPChar.Id;
			PChar.Quest.(attrL).win_condition.l1 = "Timer";
			PChar.Quest.(attrL).win_condition.l1.date.day = GetAddingDataDay(0, 6, 0);
			PChar.Quest.(attrL).win_condition.l1.date.month = GetAddingDataMonth(0, 6, 0);
			PChar.Quest.(attrL).win_condition.l1.date.year = GetAddingDataYear(0, 6, 0);
			PChar.Quest.(attrL).function = "BurntShipQuest_TimeIsOver";
			PChar.Quest.(attrL).PortmanId = NPChar.id;
			
			attrL = NPChar.Quest.BurntShip.ShipAttribute;
			
			iTest = sti(NPChar.Quest.BurntShip.ShipType);
			
			switch(attrL)
			{
				case "speedrate":
					attrL = "скорости. У " + GetStrSmallRegister(XI_ConvertString(ShipsTypes[iTest].name + "Gen")) + " скорость по ветру должна быть не менее " + NPChar.Quest.BurntShip.ShipNeededValue;
				break;
				
				case "turnrate":
					attrL = "манёвренности. У " + GetStrSmallRegister(XI_ConvertString(ShipsTypes[iTest].name + "Gen")) + " манёвренность должна быть не менее " + NPChar.Quest.BurntShip.ShipNeededValue;
				break;
				
				case "capacity":
					attrL = "трюма. У " + GetStrSmallRegister(XI_ConvertString(ShipsTypes[iTest].name + "Gen")) + " трюм должен быть не менее " + NPChar.Quest.BurntShip.ShipNeededValue;
				break;
			}
			
			sTitle = "BurntShipQuest" + NPChar.location;
			ReOpenQuestHeader(sTitle);
			AddQuestRecordEx(sTitle, "BurntShipQuest", "1");
			AddQuestUserDataForTitle(sTitle, "cityName", XI_ConvertString("Colony" + NPChar.city + "Dat"));
			AddQuestUserData(sTitle, "portmanName", GetFullName(NPChar));
			AddQuestUserData(sTitle, "cityName", XI_ConvertString("Colony" + NPChar.city + "Gen"));
			AddQuestUserData(sTitle, "text", attrL);
			
			NPChar.Quest.BurntShip.LastPortmanName = GetFullName(NPChar); // Запомнм имя
			
			DialogExit();
		break;
		
		// Вариант, когда не уложились в сроки
		case "BurntShip10":
			dialog.text = "О чём вы хотели поговорить?";
			link.l1 = "А где прежний начальник портового управления, господин " + NPChar.Quest.BurntShip.LastPortmanName + "? У меня к нему дело.";
			link.l1.go = "BurntShip11";
		break;
		
		case "BurntShip11":
			dialog.text = "А его нет... Представляете? он сжёг судно одного известного господина и прикарманил страховую сумму. Пока власти разобрались что к чему, он уже подал в отставку и улизнул в Европу. Каков плут, а?..";
			link.l1 = "Да, мне известна эта история. Извините, мне пора...";
			link.l1.go = "BurntShip11_exit";
		break;
		
		case "BurntShip11_exit":
			AddCharacterExpToSkill(pchar, "Sailing", 100);
			AddCharacterExpToSkill(pchar, "Fortune", 100);
			sTitle = "BurntShipQuest" + NPChar.location;
			AddQuestRecordEx(sTitle, "BurntShipQuest", "2");
			AddQuestUserData(sTitle, "portmanName", NPChar.Quest.BurntShip.LastPortmanName);
			CloseQuestHeader(sTitle);
			
			DeleteAttribute(NPChar, "Quest.BurntShip");
			NPChar.Quest.BurntShip.LastQuestDate = sLastSpeakDate;
			
			DialogExit();
		break;
		
		// Не просрочено - проверяем корабль
		case "BurntShip12":
			dialog.text = "О чём вы хотели поговорить?";
			link.l1 = "Я привел"+ GetSexPhrase("","а") +" вам судно с неординарной характеристикой. Жду обещанного вознаграждения.";
			link.l1.go = "BurntShip14";
			link.l2 = "Знаете, " + GetFullName(NPChar) + ", никак мне не попадаются суда с заказанной вами характеристикой. Пожалуй я откажусь от этого поручения. Извините, если подвёл"+ GetSexPhrase("","а") +"...";
			link.l2.go = "BurntShip13";
		break;
		
		case "BurntShip13":
			dialog.text = "Очень жаль, капитан... очень жаль, что вы не хотите мне помочь.";
			link.l1 = "Тут не в желании дело, уважаемый. Вы же сами понимаете... До свидания...";
			link.l1.go = "BurntShip13_exit";
		break;
		
		case "BurntShip13_exit":
			sTitle = "BurntShipQuest" + NPChar.location;
			CloseQuestHeader(sTitle);
			
			ChangeCharacterComplexReputation(pchar,"nobility", -5);
			DeleteAttribute(NPChar, "Quest.BurntShip");
			NPChar.Quest.BurntShip.LastQuestDate = sLastSpeakDate;
			
			DialogExit();
		break;
		
		case "BurntShip14":
			dialog.text = "Вот как! И как же называется наше новое судно?";
			
			sTitle = NPChar.Quest.BurntShip.ShipAttribute;
			ok = (sFrom_sea == "") || (Pchar.location.from_sea == sFrom_sea);
			
			if(sti(Pchar.Ship.Type) != SHIP_NOTUSED && ok)
			{
				for(i = 1; i < COMPANION_MAX; i++)
				{
					cn = GetCompanionIndex(PChar, i);
					
					if(cn > 0)
					{
						chref = GetCharacter(cn);
						
						sld = &RealShips[sti(chref.ship.type)];
						
						if(GetRemovable(chref) && sti(sld.basetype) == sti(NPchar.Quest.BurntShip.ShipType) &&
							stf(sld.(sTitle)) >= stf(NPChar.Quest.BurntShip.ShipNeededValue))
						{
							attrL = "l" + i;
							Link.(attrL) = chref.Ship.Name;
							Link.(attrL).go = "BurntShip15";
						}
					}
				}
			}
			
			link.l99 = "Извините, я зайду позже.";
			link.l99.go = "exit";
		break;
		
		case "BurntShip15":
			AddCharacterExpToSkill(pchar, "Leadership", 100);
			AddCharacterExpToSkill(pchar, "Sailing", 100);
			AddCharacterExpToSkill(pchar, "Fortune", 100);
			dialog.text = "Ах, капитан, я рад, что не ошибся в вас! Как"+ GetSexPhrase("ой","ая") +" вы всё-таки молодец, просто спасли меня от смерти... Я вас очень попрошу, зайдите за деньгами дня через два. Формальности, знаете ли, с получением страховой суммы нужно уладить... А вы пока приведите судно в порядок. Ну, паруса обновить, пробоины подлатать, кренгование, опять же, не помешает...";
			link.l99 = "Вы не забыли, что я обещал"+ GetSexPhrase("","а") +", если начнутся проволочки с выплатой?";
			link.l99.go = "BurntShip16";
		break;
		
		case "BurntShip16":
			dialog.text = "Нет-нет, Боже упаси! Я своё слово сдержу, не волнуйтесь. Просто, зная, что предстоят ещё траты по, так сказать, маскировке корабля, я положил страховую сумму в рост. Вы уж поймите меня правильно...";
			link.l1 = "Я вас пойму, когда песо будут лежать в моём сундуке. До встречи.";
			link.l1.go = "BurntShip16_exit";
		break;
		
		case "BurntShip16_exit":
			sTitle = "BurntShipQuest" + NPChar.location;
			AddQuestRecordEx(sTitle, "BurntShipQuest", "3");
			
			NPChar.Quest.BurntShip.TwoDaysWait = true;
			SaveCurrentNpcQuestDateParam(NPChar, "Quest.BurntShip.TwoDaysWait"); // Запомним дату
			
			sTitle = "BurntShipQuest" + NPChar.Id;
			PChar.Quest.(sTitle).over = "yes"; // Завершаем прерывание на время
			
			DialogExit();
		break;
		
		case "BurntShip17":
			dialog.text = "О чём вы хотели поговорить?";
			link.l1 = "Я приш"+ GetSexPhrase("ел","ла") +" за вознаграждением. Нужное вам судно по-прежнему у меня.";
			link.l1.go = "BurntShip18";
		break;
		
		case "BurntShip18":
			dialog.text = "Напомните, пожалуйста, его название. А то с этими нервотрёпками памяти, знаете ли, совсем не осталось.";
			
			sTitle = NPChar.Quest.BurntShip.ShipAttribute;
			ok = (sFrom_sea == "") || (Pchar.location.from_sea == sFrom_sea);
			
			if(sti(Pchar.Ship.Type) != SHIP_NOTUSED && ok)
			{
				for(i = 1; i < COMPANION_MAX; i++)
				{
					cn = GetCompanionIndex(PChar, i);
					
					if(cn > 0)
					{
						chref = GetCharacter(cn);
						
						sld = &RealShips[sti(chref.ship.type)];
						
						if(GetRemovable(chref) && sti(sld.basetype) == sti(NPchar.Quest.BurntShip.ShipType) &&
							stf(sld.(sTitle)) >= stf(NPChar.Quest.BurntShip.ShipNeededValue))
						{
							attrL = "l" + i;
							Link.(attrL) = chref.Ship.Name;
							Link.(attrL).go = "BurntShip19_" + i;
						}
					}
				}
			}
			
			link.l99 = "Извините, я зайду позже.";
			link.l99.go = "exit";
		break;
		
		case "BurntShip19":
			sld = &Characters[GetCompanionIndex(PChar, sti(NPChar.Quest.BurntShip.ShipCompanionIndex))];
			cn = GetShipSellPrice(sld, CharacterFromID(NPChar.city + "_shipyarder")) * 2;
			rRealShip = GetRealShip(GetCharacterShipType(sld));
			if (sti(rRealShip.Stolen)) cn *= 3;
			
			dialog.text = "Да, великолепно! Я готов выдать ваше вознаграждение, " + FindRussianMoneyString(cn) + ". Именно так страховая контора оценила сгоревшее судно. Страховка выплачена кредитными сундуками - наличных денег нет, извините.";
			link.l1 = "Э нет, такая сумма меня не устроит. Я уверен"+ GetSexPhrase("","а") +", что это судно стоит гораздо дороже.";
			link.l1.go = "BurntShip21";
			link.l2 = "Вот это совсем другое дело. Я рад"+ GetSexPhrase("","а") +", что смог"+ GetSexPhrase("","ла") +" вам помочь. До встречи.";
			link.l2.go = "BurntShip20_exit";
			NPChar.Quest.BurntShip.Money = cn;
		break;
		
		case "BurntShip20_exit":
			TakeNItems(pchar, "chest", makeint(sti(NPChar.Quest.BurntShip.Money)/12000));
			Log_Info("Вы получили кредитные сундуки");
			PlaySound("interface\important_item.wav");
			sTitle = "BurntShipQuest" + NPChar.location;
			AddQuestRecordEx(sTitle, "BurntShipQuest", "4");
			AddQuestUserData(sTitle, "sSex", GetSexPhrase("","а"));
			AddQuestUserData(sTitle, "money", NPChar.Quest.BurntShip.Money);
			CloseQuestHeader(sTitle);
			
			ChangeCharacterComplexReputation(pchar,"nobility", 3);
			
			sld = &Characters[GetCompanionIndex(PChar, sti(NPChar.Quest.BurntShip.ShipCompanionIndex))];
			RemoveCharacterCompanion(PChar, sld);
			AddPassenger(PChar, sld, false);
			
			DeleteAttribute(NPChar, "Quest.BurntShip");
			NPChar.Quest.BurntShip.LastQuestDate = sLastSpeakDate;
			
			DialogExit();
		break;
		
		case "BurntShip21":
			dialog.text = "Ну что вы, капитан?! Поверьте мне, я знаю, что говорю. За такие деньги вы могли бы купить два подобных судна!";
			link.l1 = "Лучше я оставлю его себе. Уж очень оно мне приглянулось... Прощайте.";
			link.l1.go = "BurntShip21_exit";
		break;
		
		case "BurntShip21_exit":
			ChangeCharacterComplexReputation(pchar,"nobility", -5);
			
			sTitle = "BurntShipQuest" + NPChar.location;
			AddQuestRecordEx(sTitle, "BurntShipQuest", "5");
			AddQuestUserData(sTitle, "sSex", GetSexPhrase("","а"));
			AddQuestUserData(sTitle, "money", NPChar.Quest.BurntShip.Money);
			CloseQuestHeader(sTitle);
			
			DeleteAttribute(NPChar, "Quest.BurntShip");
			NPChar.Quest.BurntShip.LastQuestDate = sLastSpeakDate;
			
			DialogExit();
		break;
		
		//--> миниквесты портмана
		case "PortmanQuest":
			if (cRand(5) == 2)
			{	//квест догнать и передать судовой журнал
				dialog.text = "У меня забыл судовой журнал один капитан. Это же надо быть таким разиней!.. В общем, нужно его догнать и вернуть пропажу.";
				link.l1 = "Ну, это можно... За эту работу я берусь!";
				link.l1.go = "PortmanQuest_1";
				link.l2 = "Нет, не хочу этим заниматься. Это его проблемы, собственно...";
				link.l2.go = "node_2";
			}
			else
			{	//квест разыскать украденный корабль
				dialog.text = "У меня со стоянки был украден корабль. Я хочу, чтобы вы разыскали и вернули его мне.";
				link.l1 = "Хм, ну что же, я готов"+ GetSexPhrase("","а") +" взяться за розыски.";
				link.l1.go = "SeekShip_1";
				link.l2 = "Простите, но розыском кораблей я не занимаюсь.";
				link.l2.go = "node_2";
			}
		break;
//-------------------------------- квест доставки судового журнала до рассеяного кэпа ---------------------
		case "PortmanQuest_1":
			dialog.text = "Отлично, вот его журнал... Уф-ф, прямо груз с плеч долой! Потеря судового журнала - штука неприятная, переживаю я за таких капитанов.";
			link.l1 = "Это точно, переживать стоит! Ну, а теперь расскажите мне подробней об этом рассеянном капитане.";
			link.l1.go = "PortmanQuest_2";
			pchar.questTemp.different = "PortmansJornal";
			SetTimerFunction("SmallQuests_free", 0, 0, 1); //освобождаем разрешалку на миниквесты
			SetJornalCapParam(npchar);
			GiveItem2Character(pchar, "PortmansBook");
			pchar.questTemp.PortmansJornal.gem = GenQuestPortman_GenerateGem();
		break;
		case "PortmanQuest_2":
			dialog.text = "Да, конечно! Его зовут " + npchar.quest.PortmansJornal.capName + ", он капитан " + GetStrSmallRegister(XI_ConvertString(npchar.quest.PortmansJornal.shipTapeName + "Gen")) + " с именем '" + npchar.quest.PortmansJornal.shipName + "'. Вышел он в море недавно, а направился в " + XI_ConvertString("Colony" + npchar.quest.PortmansJornal.city + "Acc") + ".";
			link.l1 = "Понятно. Ну что же, я его обязательно найду. Как быть с оплатой?";
			link.l1.go = "PortmanQuest_3";
		break;
		case "PortmanQuest_3":
			dialog.text = npchar.quest.PortmansJornal.capName + " сам с вами рассчитается, это в его интересах. Только постарайтесь найти его быстрей, и всё будет нормально.";
			link.l1 = "Ясно. Ну, я пош"+ GetSexPhrase("ел","ла") +"...";
			link.l1.go = "exit";
			sTitle = npchar.id + "PortmansBook_Delivery";
			ReOpenQuestHeader(sTitle);
			AddQuestRecordEx(sTitle, "PortmansBook_Delivery", "1");
			AddQuestUserDataForTitle(sTitle, "sCapName", npchar.quest.PortmansJornal.capName);
			AddQuestUserDataForTitle(sTitle, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(sTitle, "sShipTypeName", GetStrSmallRegister(XI_ConvertString(npchar.quest.PortmansJornal.shipTapeName + "Gen")));
			AddQuestUserData(sTitle, "sShipName", npchar.quest.PortmansJornal.shipName);
			AddQuestUserData(sTitle, "sCapName", npchar.quest.PortmansJornal.capName);
			AddQuestUserData(sTitle, "sCapName2", npchar.quest.PortmansJornal.capName);
			AddQuestUserData(sTitle, "sTargetCity", XI_ConvertString("Colony" + npchar.quest.PortmansJornal.city + "Acc"));
			if (GetIslandByCityName(npchar.quest.PortmansJornal.city) != npchar.quest.PortmansJornal.city)
			{
				AddQuestUserData(sTitle, "sAreal", ", что находится на " + XI_ConvertString(GetIslandByCityName(npchar.quest.PortmansJornal.city) + "Dat"));
			}			
		break;
		// -------------------------------- квест розыска украденного корабля ----------------------------------
		case "SeekShip_1":
			dialog.text = "Прекрасно! Вы знаете, украденный корабль принадлежит не последнему человеку, так что он очень важен для меня. Я неплохо заплачу за работу...";
			link.l1 = "Понятно. Расскажите подробней, что за корабль, при каких обстоятельствах был украден.";
			link.l1.go = "SeekShip_2";
			pchar.questTemp.different = "PortmansSeekShip";
			SetTimerFunction("SmallQuests_free", 0, 0, 1); //освобождаем разрешалку на миниквесты
			SetSeekShipCapParam(npchar);
		break;
		case "SeekShip_2":
			dialog.text = XI_ConvertString(npchar.quest.PortmansSeekShip.shipTapeName+"Acc") + " '" + npchar.quest.PortmansSeekShip.shipName + "' украли ночью, " + FindRussianDaysString(rand(5)+10) + " назад. Вахтенный убит.";
			link.l1 = "Хм, они уже успели уйти, небось, прилично. В общем, о горячих следах говорить не приходится...";
			link.l1.go = "SeekShip_3";
		break;
		case "SeekShip_3":
			dialog.text = "Да, верно. Но и смысла мне сразу панику поднимать не было. Военные если и догонят, то разнесут корабль в щепки, а это не совсем то, что мне нужно.";
			link.l1 = "Понятно. Ну что же, приступаю к поискам. Надеюсь, мне повезёт.";
			link.l1.go = "exit";
			sTitle = npchar.id + "Portmans_SeekShip";
			ReOpenQuestHeader(sTitle);
			AddQuestRecordEx(sTitle, "Portmans_SeekShip", "1");
			AddQuestUserDataForTitle(sTitle, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(sTitle, "sShipTypeName", GetStrSmallRegister(XI_ConvertString(npchar.quest.PortmansSeekShip.shipTapeName+"Acc")));
			AddQuestUserData(sTitle, "sShipName", npchar.quest.PortmansSeekShip.shipName);
		break;

		case "SeekShip_break":
			dialog.text = "Хм, ну что же, очень жаль. Хотя, на успех сложно было рассчитывать...";
			link.l1 = "Да, слишком много времени прошло с момента кражи.";
			link.l1.go = "SeekShip_break_1";
		break;
		case "SeekShip_break_1":
			dialog.text = "Ну что же, спасибо за оказанную помощь, хоть она и не увенчалась успехом.";
			link.l1 = "Не за что...";
			link.l1.go = "exit";
			sTemp = "SeekShip_checkAbordage" + npchar.index;
			pchar.quest.(sTemp).over = "yes"; //снимаем прерывание на абордаж
			cn = GetCharacterIndex("SeekCap_" + npchar.index);
			//если кэп-вор еще жив - убираем его
			if (cn > 0)
			{
				characters[cn].LifeDay = 0; 
				Map_ReleaseQuestEncounter(characters[cn].id);
				group_DeleteGroup("SeekCapShip_" + characters[cn].index);
			}
			sTitle = npchar.id + "Portmans_SeekShip";
			AddQuestRecordEx(sTitle, "Portmans_SeekShip", "7");
			CloseQuestHeader(sTitle);
			DeleteAttribute(npchar, "quest.PortmansSeekShip");
			npchar.quest = ""; //освобождаем личный флаг квеста для портмана
			ChangeCharacterComplexReputation(pchar,"nobility", -7);
		break;	

		case "SeekShip_good":
			if (npchar.quest == "SeekShip_sink")
			{
				dialog.text = "Отлично! Однако, полагаю, что это не совсем тот корабль, что был украден... Хотя, собственно, всё равно! Я беру его у вас.";
				link.l1 = "Да, действительно...";
				//npchar.quest.money = makeint(sti(npchar.quest.money) / 4); //снижаем оплату
				ChangeCharacterComplexReputation(pchar,"nobility", 5);
				ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 10);
                AddCharacterExpToSkill(GetMainCharacter(), "Leadership", 10);
                AddCharacterExpToSkill(GetMainCharacter(), "Sailing", 10);
                AddCharacterExpToSkill(GetMainCharacter(), "Commerce", 50);
                AddCharacterExpToSkill(GetMainCharacter(), "Cannons", 20);
			}
			else
			{
				dialog.text = "Превосходно! Вы мне очень помогли. Представляю, насколько это было сложно.";
				link.l1 = "Да, действительно...";
				ChangeCharacterComplexReputation(pchar,"nobility", 10);
				ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 20);
                AddCharacterExpToSkill(GetMainCharacter(), "Leadership", 100);
                AddCharacterExpToSkill(GetMainCharacter(), "Sailing", 150);
                AddCharacterExpToSkill(GetMainCharacter(), "Grappling", 100);
			}
			link.l1.go = "SeekShip_good_1";
		break;
		case "SeekShip_good_1":
			dialog.text = "Я готов выплатить вам вознаграждение. Оно составляет " + FindRussianMoneyString(makeint(sti(npchar.quest.chest)*15000)) + " в сундуках. Больше я заплатить не могу, к сожалению.";
			link.l1 = "Ну что же, этого тоже достаточно. Спасибо и всего хорошего.";
			link.l1.go = "exit";
			TakeNItems(pchar, "chest", sti(npchar.quest.chest));
			sTitle = npchar.id + "Portmans_SeekShip";
			AddQuestRecordEx(sTitle, "Portmans_SeekShip", "6");
			CloseQuestHeader(sTitle);
			DeleteAttribute(npchar, "quest.PortmansSeekShip");
			npchar.quest = ""; //освобождаем личный флаг квеста для портмана
		break;

		//------------------------------> инфа по базе квествых кэпов
		//ВНИМАНИЕ. в квестбук должна заносится типовая строка по примеру   PortmansBook_Delivery  #TEXT   5
		//в список портмана заносим тайтл, заголовок и номер строки из quest_text.txt
		//ПРИМЕР: в конце метода  void SetCapitainFromCityToSea(string qName)
		case "CapitainList":
			if (sti(npchar.quest.qty) > 0)
			{
				dialog.text = "Есть отметившиеся капитаны. Кто конкретно вас интересует?";
				makearef(arCapBase, npchar.quest.capitainsList); 
				for (i=0; i<sti(npchar.quest.qty); i++)
				{
    				arCapLocal = GetAttributeN(arCapBase, i);
					sCapitainId = GetAttributeName(arCapLocal);
					sld = characterFromId(sCapitainId);
					attrL = "l" + i;
					link.(attrL) = GetFullName(sld) + ", капитан " + GetStrSmallRegister(XI_ConvertString(RealShips[sti(sld.Ship.Type)].BaseName + "Gen")) + " '" + sld.Ship.name + "'.";
					link.(attrL).go = "CapList_"+attrL;
				}
			}
			else
			{
				dialog.text = "У меня в списках нет капитанов, способных вас заинтересовать.";
				link.l1 = "Понятно. Спасибо за информацию.";
				link.l1.go = "node_2";
			}
		break;
		case "CapList_l0":
			makearef(arCapBase, npchar.quest.capitainsList);
    		arCapLocal = GetAttributeN(arCapBase,  0);
			sCapitainId = GetAttributeName(arCapLocal);
			sld = characterFromId(sCapitainId);
			dialog.text = LinkRandPhrase("Та-а-ак, давайте посмотрим... Ага, есть! ", "Так-так... Ага, нашёл! ", "Значит, так. ") +
				"Капитан " + GetFullName(sld) + " " + arCapLocal.date + " года ушёл из нашего порта в " + XI_ConvertString("Colony" + arCapLocal + "Acc") + ".";
			link.l1 = "Спасибо. Хотелось бы посмотреть список дальше...";
			link.l1.go = "CapitainList";
			link.l2 = "Всё, капитаны меня более не интересуют.";
			link.l2.go = "node_2";
			//заносим запись в СЖ
			AddQuestRecordEx(arCapLocal.QBString1, arCapLocal.QBString2, arCapLocal.QBQty);
			AddQuestUserData(arCapLocal.QBString1, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(arCapLocal.QBString1, "sCapName", GetFullName(sld));
			AddQuestUserData(arCapLocal.QBString1, "sShipTypeName", GetStrSmallRegister(XI_ConvertString(RealShips[sti(sld.Ship.Type)].BaseName + "Voc")));
			AddQuestUserData(arCapLocal.QBString1, "sShipName", sld.Ship.name);
			AddQuestUserData(arCapLocal.QBString1, "sDate", arCapLocal.date);
			AddQuestUserData(arCapLocal.QBString1, "sTargetCity", XI_ConvertString("Colony" + arCapLocal + "Acc"));
			if (GetIslandByCityName(arCapBase.(sCapitainId)) != arCapBase.(sCapitainId))
			{
				AddQuestUserData(arCapLocal.QBString1, "sAreal", ", что находится на " + XI_ConvertString(GetIslandByCityName(arCapBase.(sCapitainId)) + "Dat"));
			}
			//убираем из списка
			DeleteAttribute(arCapBase, sCapitainId); 
		break;
		case "CapList_l1":
			makearef(arCapBase, npchar.quest.capitainsList);
    		arCapLocal = GetAttributeN(arCapBase,  1);
			sCapitainId = GetAttributeName(arCapLocal);
			sld = characterFromId(sCapitainId);
			dialog.text = LinkRandPhrase("Та-а-ак, давайте посмотрим... Ага, есть! ", "Так-так... Ага, нашёл! ", "Значит, так. ") +
				"Капитан " + GetFullName(sld) + " " + arCapLocal.date + " года ушёл из нашего порта в " + XI_ConvertString("Colony" + arCapLocal + "Acc") + ".";
			link.l1 = "Спасибо. Хотелось бы посмотреть список дальше...";
			link.l1.go = "CapitainList";
			link.l2 = "Всё, капитаны меня более не интересуют.";
			link.l2.go = "node_2";
			//заносим запись в СЖ
			AddQuestRecordEx(arCapLocal.QBString1, arCapLocal.QBString2, arCapLocal.QBQty);
			AddQuestUserData(arCapLocal.QBString1, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(arCapLocal.QBString1, "sCapName", GetFullName(sld));
			AddQuestUserData(arCapLocal.QBString1, "sShipTypeName", GetStrSmallRegister(XI_ConvertString(RealShips[sti(sld.Ship.Type)].BaseName + "Dat")));
			AddQuestUserData(arCapLocal.QBString1, "sShipName", sld.Ship.name);
			AddQuestUserData(arCapLocal.QBString1, "sDate", arCapLocal.date);
			AddQuestUserData(arCapLocal.QBString1, "sTargetCity", XI_ConvertString("Colony" + arCapLocal + "Acc"));
			if (GetIslandByCityName(arCapBase.(sCapitainId)) != arCapBase.(sCapitainId))
			{
				AddQuestUserData(arCapLocal.QBString1, "sAreal", ", что находится на " + XI_ConvertString(GetIslandByCityName(arCapBase.(sCapitainId)) + "Dat"));
			}
			//убираем из списка
			DeleteAttribute(arCapBase, sCapitainId); 
		break;
		case "CapList_l2":
			makearef(arCapBase, npchar.quest.capitainsList);
    		arCapLocal = GetAttributeN(arCapBase,  2);
			sCapitainId = GetAttributeName(arCapLocal);
			sld = characterFromId(sCapitainId);
			dialog.text = LinkRandPhrase("Та-а-ак, давайте посмотрим... Ага, есть! ", "Так-так... Ага, нашёл! ", "Значит, так. ") +
				"Капитан " + GetFullName(sld) + " " + arCapLocal.date + " года ушёл из нашего порта в " + XI_ConvertString("Colony" + arCapLocal + "Acc") + ".";
			link.l1 = "Спасибо. Хотелось бы посмотреть список дальше...";
			link.l1.go = "CapitainList";
			link.l2 = "Всё, капитаны меня более не интересуют.";
			link.l2.go = "node_2";
			//заносим запись в СЖ
			AddQuestRecordEx(arCapLocal.QBString1, arCapLocal.QBString2, arCapLocal.QBQty);
			AddQuestUserData(arCapLocal.QBString1, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(arCapLocal.QBString1, "sCapName", GetFullName(sld));
			AddQuestUserData(arCapLocal.QBString1, "sShipTypeName", GetStrSmallRegister(XI_ConvertString(RealShips[sti(sld.Ship.Type)].BaseName + "Dat")));
			AddQuestUserData(arCapLocal.QBString1, "sShipName", sld.Ship.name);
			AddQuestUserData(arCapLocal.QBString1, "sDate", arCapLocal.date);
			AddQuestUserData(arCapLocal.QBString1, "sTargetCity", XI_ConvertString("Colony" + arCapLocal + "Acc"));
			if (GetIslandByCityName(arCapBase.(sCapitainId)) != arCapBase.(sCapitainId))
			{
				AddQuestUserData(arCapLocal.QBString1, "sAreal", ", что находится на " + XI_ConvertString(GetIslandByCityName(arCapBase.(sCapitainId)) + "Dat"));
			}
			//убираем из списка
			DeleteAttribute(arCapBase, sCapitainId); 
		break;
		case "CapList_l3":
			makearef(arCapBase, npchar.quest.capitainsList);
    		arCapLocal = GetAttributeN(arCapBase,  3);
			sCapitainId = GetAttributeName(arCapLocal);
			sld = characterFromId(sCapitainId);
			dialog.text = LinkRandPhrase("Та-а-ак, давайте посмотрим... Ага, есть! ", "Так-так... Ага, нашёл! ", "Значит, так. ") +
				"Капитан " + GetFullName(sld) + " " + arCapLocal.date + " года ушёл из нашего порта в " + XI_ConvertString("Colony" + arCapLocal + "Acc") + ".";
			link.l1 = "Спасибо. Хотелось бы посмотреть список дальше...";
			link.l1.go = "CapitainList";
			link.l2 = "Всё, капитаны меня более не интересуют.";
			link.l2.go = "node_2";
			//заносим запись в СЖ
			AddQuestRecordEx(arCapLocal.QBString1, arCapLocal.QBString2, arCapLocal.QBQty);
			AddQuestUserData(arCapLocal.QBString1, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(arCapLocal.QBString1, "sCapName", GetFullName(sld));
			AddQuestUserData(arCapLocal.QBString1, "sShipTypeName", GetStrSmallRegister(XI_ConvertString(RealShips[sti(sld.Ship.Type)].BaseName + "Dat")));
			AddQuestUserData(arCapLocal.QBString1, "sShipName", sld.Ship.name);
			AddQuestUserData(arCapLocal.QBString1, "sDate", arCapLocal.date);
			AddQuestUserData(arCapLocal.QBString1, "sTargetCity", XI_ConvertString("Colony" + arCapLocal + "Acc"));
			if (GetIslandByCityName(arCapBase.(sCapitainId)) != arCapBase.(sCapitainId))
			{
				AddQuestUserData(arCapLocal.QBString1, "sAreal", ", что находится на " + XI_ConvertString(GetIslandByCityName(arCapBase.(sCapitainId)) + "Dat"));
			}
			//убираем из списка
			DeleteAttribute(arCapBase, sCapitainId); 
		break;
		case "CapList_l4":
			makearef(arCapBase, npchar.quest.capitainsList);
    		arCapLocal = GetAttributeN(arCapBase,  4);
			sCapitainId = GetAttributeName(arCapLocal);
			sld = characterFromId(sCapitainId);
			dialog.text = LinkRandPhrase("Та-а-ак, давайте посмотрим... Ага, есть! ", "Так-так... Ага, нашёл! ", "Значит, так. ") +
				"Капитан " + GetFullName(sld) + " " + arCapLocal.date + " года ушёл из нашего порта в " + XI_ConvertString("Colony" + arCapLocal + "Acc") + ".";
			link.l1 = "Спасибо. Хотелось бы посмотреть список дальше...";
			link.l1.go = "CapitainList";
			link.l2 = "Всё, капитаны меня более не интересуют.";
			link.l2.go = "node_2";
			//заносим запись в СЖ
			AddQuestRecordEx(arCapLocal.QBString1, arCapLocal.QBString2, arCapLocal.QBQty);
			AddQuestUserData(arCapLocal.QBString1, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(arCapLocal.QBString1, "sCapName", GetFullName(sld));
			AddQuestUserData(arCapLocal.QBString1, "sShipTypeName", GetStrSmallRegister(XI_ConvertString(RealShips[sti(sld.Ship.Type)].BaseName + "Dat")));
			AddQuestUserData(arCapLocal.QBString1, "sShipName", sld.Ship.name);
			AddQuestUserData(arCapLocal.QBString1, "sDate", arCapLocal.date);
			AddQuestUserData(arCapLocal.QBString1, "sTargetCity", XI_ConvertString("Colony" + arCapLocal + "Acc"));
			if (GetIslandByCityName(arCapBase.(sCapitainId)) != arCapBase.(sCapitainId))
			{
				AddQuestUserData(arCapLocal.QBString1, "sAreal", ", что находится на " + XI_ConvertString(GetIslandByCityName(arCapBase.(sCapitainId)) + "Dat"));
			}
			//убираем из списка
			DeleteAttribute(arCapBase, sCapitainId); 
		break;
		//<--------------------------- инфа по базе квествых кэпов

		case "ShipStock_1":
			if (CheckAttribute(pchar, "questTemp.HWIC.Holl") && pchar.questTemp.HWIC.Holl == "JacobTakeShip" && !CheckAttribute(npchar, "quest.HWICHoll"))
			{
			dialog.text = "Слушаю вас - какой корабль, на какой срок?";
    		Link.l1 = "Я от Лукаса Роденбурга. Он сказал, что стоянка для моего корабля будет бесплатной.";
    		Link.l1.go = "ShipStock_HWICHoll";
			break;
			}
			if (CheckAttribute(pchar, "questTemp.HWIC.Eng") && pchar.questTemp.HWIC.Eng == "GotoPortoffice" && !CheckAttribute(npchar, "quest.HWICEng"))
			{
			dialog.text = "Слушаю вас - какой корабль, на какой срок?";
    		Link.l1 = "Я от Ричарда Флитвуда. Он сказал, что я могу поставить свой флагман на стоянку за 10 000 песо.";
    		Link.l1.go = "ShipStock_HWICEng";
			break;
			}
            if (sti(NPChar.Portman) >= 3 || CheckAttribute(pchar, "questTemp.HWIC.TakeQuestShip"))
			{
                dialog.text = "Вообще-то, да. Но сейчас я не могу принять корабль. Нет мест в доках.";
    			Link.l1 = "Очень жаль.";
    			Link.l1.go = "exit";
			}
            else
            {
    			ok = (sFrom_sea == "") || (Pchar.location.from_sea == sFrom_sea);
			    if (sti(Pchar.Ship.Type) != SHIP_NOTUSED && ok)
				{
					dialog.text = "Какой именно корабль вы хотите оставить?";
	    			for(i=1; i<COMPANION_MAX; i++)
	                {
	        	        cn = GetCompanionIndex(PChar, i);
	        	        if( cn >0 )
	        	        {
	        		        chref = GetCharacter(cn);
	                        if (!GetRemovable(chref)) continue;
	
	        		        attrL = "l"+i;
	        		        Link.(attrL)    = XI_ConvertString(RealShips[sti(chref.Ship.Type)].BaseName) + " '" + chref.Ship.Name + "'.";
	        		        Link.(attrL).go = "ShipStockMan_" + i;
	        		    }
	        	    }
	    			Link.l9 = "Спасибо, не нужно.";
	    			Link.l9.go = "exit";
    			}
    			else
    			{
					dialog.text = "Хм. Я не вижу ваших кораблей в порту.";
	    			Link.l1 = "Да, я просто хотел"+ GetSexPhrase("","а") +" узнать о возможности стоянки.";
	    			Link.l1.go = "exit";
				}
			}
		break;

		case "ShipStockMan_1":
            NPChar.ShipToStoreIdx = GetCompanionIndex(PChar, 1);
			dialog.text = "Посмотрим, что это за корабль.";
			Link.l1 = "Хорошо.";
			Link.l1.go = "ShipStock_2";
			Link.l2 = "Нет, я передумал"+ GetSexPhrase("","а") +".";
			Link.l2.go = "exit";
		break;

		case "ShipStockMan_2":
            NPChar.ShipToStoreIdx = GetCompanionIndex(PChar, 2);
			dialog.text = "Посмотрим, что это за корабль.";
			Link.l1 = "Хорошо.";
			Link.l1.go = "ShipStock_2";
			Link.l2 = "Нет, я передумал"+ GetSexPhrase("","а") +".";
			Link.l2.go = "exit";
		break;

		case "ShipStockMan_3":
            NPChar.ShipToStoreIdx = GetCompanionIndex(PChar, 3);
			dialog.text = "Посмотрим, что это за корабль.";
			Link.l1 = "Хорошо.";
			Link.l1.go = "ShipStock_2";
			Link.l2 = "Нет, я передумал"+ GetSexPhrase("","а") +".";
			Link.l2.go = "exit";
		break;
		
		case "ShipStockMan_4":
            NPChar.ShipToStoreIdx = GetCompanionIndex(PChar, 4);
			dialog.text = "Посмотрим что это за корабль.";
			Link.l1 = "Хорошо.";
			Link.l1.go = "ShipStock_2";
			Link.l2 = "Нет, я передумал"+ GetSexPhrase("","а") +".";
			Link.l2.go = "exit";
		break;

		case "ShipStock_2":
            chref = GetCharacter(sti(NPChar.ShipToStoreIdx));
			NPChar.MoneyForShip = GetPortManPriceExt(NPChar, chref);
			dialog.Text = XI_ConvertString(RealShips[sti(chref.Ship.Type)].BaseName) + " '" + chref.Ship.Name + "', класс " + RealShips[sti(chref.Ship.Type)].Class +
                     ", стоимость стоянки " + FindRussianMoneyString(sti(NPChar.MoneyForShip)) + " в месяц, оплата за месяц вперёд.";
			Link.l1 = "Да. Это меня устраивает.";
			if (sti(Pchar.Money) >= sti(NPChar.MoneyForShip))
			{
			    Link.l1.go = "ShipStock_3";
			}
			else
			{
                Link.l1.go = "ShipStock_NoMoney";
			}
			Link.l2 = "Нет, я передумал"+ GetSexPhrase("","а") +".";
			Link.l2.go = "exit";
		break;

		case "ShipStock_NoMoney":
			dialog.text = "Меня тоже всё устроит, если у вас будет нужная сумма.";
			Link.l1 = "Упс... зайду позже.";
			Link.l1.go = "exit";
		break;

		case "ShipStock_3":
            AddMoneyToCharacter(pchar, -makeint(NPChar.MoneyForShip));
            chref = GetCharacter(sti(NPChar.ShipToStoreIdx));
            chref.ShipInStockMan = NPChar.id;
			// Warship 22.03.09 fix Не перенеслось с КВЛ 1.2.3
			chref.ShipInStockMan.MoneyForShip = NPChar.MoneyForShip;
            chref.ShipInStockMan.AltDate = GetQuestBookDataDigit(); // для печати
            SaveCurrentNpcQuestDateParam(chref, "ShipInStockMan.Date"); // для расчета
            chref.Ship.Crew.Quantity  = 0;
            RemoveCharacterCompanion(pchar, chref);
            chref.location = "";
            chref.location.group = "";
            chref.location.locator = "";

            NPChar.Portman    = sti(NPChar.Portman) + 1;
            pchar.ShipInStock = sti(pchar.ShipInStock) + 1;

			dialog.text = "Хорошо. Заберёте, когда будет нужно.";
			Link.l1 = "Спасибо.";
			Link.l1.go = "exit";
		break;

		case "ShipStockReturn_1":
            ok = (sFrom_sea == "") || (Pchar.location.from_sea == sFrom_sea);
		    if (sti(Pchar.Ship.Type) != SHIP_NOTUSED && ok)
			{
				if (GetCompanionQuantity(pchar) < COMPANION_MAX)
	            {
	                dialog.text = "Какой именно корабль вы заберёте?";
	                cn = 1;
	                for(i=1; i<MAX_CHARACTERS; i++)
	            	{
	            		makeref(chref, Characters[i]);
	            		if (CheckAttribute(chref, "ShipInStockMan"))
	            		{
	                        if (chref.ShipInStockMan == NPChar.id)
	        		        {
	                            attrL = "l"+cn;
	            		        Link.(attrL)    = XI_ConvertString(RealShips[sti(chref.Ship.Type)].BaseName) + " '" + chref.Ship.Name + "'.";
	            		        Link.(attrL).go = "ShipStockManBack_" + i;
	            		        cn++;
	        		        }
	            		}
	                }
	
	    			Link.l9 = "Нет, я передумал"+ GetSexPhrase("","а") +".";
	    			Link.l9.go = "exit";
				}
				else
				{
	                dialog.text = "Нет ли у вас места для ещё одного корабля?";
	    			Link.l1 = "Да, точно. Спасибо.";
	    			Link.l1.go = "exit";
				}
			}
			else
			{
				dialog.text = "Хм. Я не вижу вашего флагмана в порту. А забрать свои корабли вы можете только здесь.";
    			Link.l1 = "Хорошо, я прибуду за ними позднее.";
    			Link.l1.go = "exit";
			}
		break;

        case "ShipStockManBack":
            chref = GetCharacter(sti(NPChar.ShipToStoreIdx));
			// --> mitrokosta сюрприз для хитрецов поставивших бунтовщика в ПУ
			if (CheckAttribute(chref, "quest.Mutiny.date")) {
				dialog.text = "Посмотрим... Этот корабль ушёл из порта " + chref.quest.Mutiny.date + " года.";
				link.l1 = "То есть как это - ушёл? Он должен был быть здесь, в доках!";
				link.l1.go = "ShipStockManMutiny";
				break;
			}
			// <--
            NPChar.MoneyForShip =  GetNpcQuestPastMonthParam(chref, "ShipInStockMan.Date") * sti(chref.ShipInStockMan.MoneyForShip);
			if (sti(NPChar.MoneyForShip) > 0)
			{
			    dialog.Text = "Забираете? С вас за хранение ещё " + FindRussianMoneyString(sti(NPChar.MoneyForShip)) + ".";
			}
			else
			{
				dialog.Text = "Забираете?";
			}
			if (sti(NPChar.MoneyForShip) <= sti(pchar.Money))
			{
				Link.l1 = "Да.";
				Link.l1.go = "ShipStockManBack2";
			}
			Link.l2 = "Нет, я передумал"+ GetSexPhrase("","а") +".";
			Link.l2.go = "exit";
		break;
		
		case "ShipStockManBack2":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
            AddMoneyToCharacter(Pchar, -sti(NPChar.MoneyForShip));
			chref = GetCharacter(sti(NPChar.ShipToStoreIdx));
			DeleteAttribute(chref, "ShipInStockMan");
			SetCompanionIndex(pchar, -1, sti(NPChar.ShipToStoreIdx));
			NPChar.Portman    = sti(NPChar.Portman) - 1;
            pchar.ShipInStock = sti(pchar.ShipInStock) - 1;
		break;
		
		//--> Jason Голландский гамбит
		case "ShipStock_HWICHoll":
			if (GetCompanionQuantity(pchar) > 1)
			{
				dialog.text = "Да-да, я в курсе. Но я могу принять на бесплатную стоянку от вас только один корабль. Пожалуйста, разберитесь со своей эскадрой, а затем вновь возвращайтесь ко мне.";
				link.l1 = "Хорошо, я приведу на стоянку только флагман.";
				link.l1.go = "exit";	
			}
			else
			{
				dialog.text = "Да-да, я в курсе. По приказу минхера Роденберга мы принимаем на хранение ваше судно и обеспечиваем его вахтенным офицером на всё время стоянки. Пожалуйста, подпишите вот тут и вот тут...";
				link.l1 = "Хорошо... Всё, теперь все формальности улажены?";
				link.l1.go = "ShipStock_HWICHoll_1";	
			}
		break;
		
		case "ShipStock_HWICHoll_1":
			dialog.text = "Да. О своем корабле не беспокойтесь - мы о нём позаботимся. Можете спокойно отправляться к минхеру Роденбергу.";
			link.l1 = "Благодарю. До свидания.";
			link.l1.go = "exit";	
			npchar.quest.HWICHoll = "done";
			pchar.Ship.Type = SHIP_NOTUSED;//все одно сгорит
		break;
		
		case "ShipStock_HWICEng":
			if (GetCompanionQuantity(pchar) > 1)
			{
				dialog.text = "Да-да, я в курсе. Но я могу принять стоянку от вас только один корабль. Пожалуйста, разберитесь со своей эскадрой, а затем вновь возвращайтесь ко мне.";
				link.l1 = "Хорошо, я приведу на стоянку только флагман.";
				link.l1.go = "exit";	
			}
			else
			{
				dialog.text = "Да, конечно. Деньги при вас?";
				if(makeint(Pchar.money) >= 10000)
				{
					link.l1 = "Да, при мне. Возьмите.";
					link.l1.go = "ShipStock_HWICEng_1";	
				}
				else
				{
					link.l1 = "Нет. Сейчас принесу.";
					link.l1.go = "exit";	
				}
			}
		break;
		
		case "ShipStock_HWICEng_1":
			dialog.text = "Хорошо. Мы позаботимся о вашем судне и обеспечим его вахтенным офицером на время стоянки.";
			link.l1 = "Спасибо!";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, -10000);
			npchar.quest.HWICEng = "done";
			pchar.Ship.Type = SHIP_NOTUSED;//все одно сгорит
		break;
		//<-- Голландский гамбит
		case "Escort_companion":
			dialog.text = "Вы что-то хотели, кэп?";
			link.l1 = "Да нет, ничего.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Escort_companion";
		break;
		
		// --> mitrokosta сюрприз для хитрецов поставивших бунтовщика в ПУ
		case "ShipStockManMutiny":
			chref = GetCharacter(sti(NPChar.ShipToStoreIdx));
			DeleteAttribute(chref, "ShipInStockMan");
			NPChar.Portman    = sti(NPChar.Portman) - 1;
            pchar.ShipInStock = sti(pchar.ShipInStock) - 1;
			dialog.text = "Вахтенный офицер " + GetFullName(chref) + " сообщил" + NPCharSexPhrase(chref, "", "а") + ", что " + NPCharSexPhrase(chref, "ему", "ей") + " немедленно нужно было выйти в море по вашему приказу. Я не стал " + NPCharSexPhrase(chref, "ему", "ей") + " препятствовать.";
			link.l1 = "Проклятье! Я не отдавал такого приказа! Нельзя было доверять корабль " + NPCharSexPhrase(chref, "этому прохвосту", "этой плутовке") + "! Ну и чёрт с " + NPCharSexPhrase(chref, "ним", "ней") + " и с моим кораблём, сейчас уже ничего не поделать.";
			link.l1.go = "ShipStockManMutiny1";
			// вот тут можно микроквестик сделать
			//link.l2 = "Вот это неожиданность... А " + NPCharSexPhrase(chref, "он", "она") + " не говорил вам, куда отправляется?";
			//link.l2.go = "ShipStockManMutiny2";
		break;
		
		case "ShipStockManMutiny1":
			chref = GetCharacter(sti(NPChar.ShipToStoreIdx));
			chref.lifeday = 0;

			dialog.text = "Соболезную, " + GetAddress_Form(NPChar) + ". Вам стоит лучше подбирать себе людей.";
			link.l1 = "Знаю, " + GetSexPhrase("сам дурак", "сама дура") + ". Прощайте, " + GetAddress_Form(NPChar) + ".";
			link.l1.go = "exit";
		break;
		// <--
	}
}

float BurntShipQuest_GetMaxNeededValue(int iShipType, string _param)
{
	float NeededValue = makefloat(GetBaseShipParamFromType(iShipType, _param));
	switch (_param)
	{
		case "speedrate":
			NeededValue += ((0.72 + frandSmall(0.30)) * (NeededValue/10.0)); 
		break;
		case "turnrate":
			NeededValue += ((0.72 + frandSmall(0.30)) * (NeededValue/10.0)); 
		break;
		case "capacity":
			NeededValue += ((0.72 + frandSmall(0.30)) * (NeededValue/8.0)); 
		break;
	}
	return NeededValue;
}

// Warship 25.07.09 Генер "Сгоревшее судно". Начальные иниты для портмана - тип разыскиваемого судна, выдающаяся характеристика и т.д.
void BurntShipQuest_FillStartParams(ref _npchar)
{
	int rank = sti(PChar.rank);
	int shipType, temp;
	float neededValue;
	String shipAttribute;
	
	// TODO Пересмотреть зависимость от ранга
	if(rank <= 5)
	{
		shipType = SHIP_LUGGER + rand(1);
		
		switch(shipType)
		{
			case SHIP_LUGGER:
				shipAttribute = "speedrate";
			break;
			
			case SHIP_SLOOP:
				temp = rand(2);
				
				if(temp == 2)
				{
					shipAttribute = "speedrate";
				}
				else
				{
					if(temp == 1)
					{
						shipAttribute = "turnrate";
					}
					else
					{
						shipAttribute = "capacity";
					}
				}
			break;
		}
	}
	
	if(rank > 5 && rank <= 15)
	{
		shipType = SHIP_SCHOONER + rand(2);
		
		switch(shipType)
		{
			case SHIP_SCHOONER:
				if(rand(1) == 0)
				{
					shipAttribute = "speedrate";
				}
				else
				{
					shipAttribute = "turnrate";
				}
			break;
			
			case SHIP_BARKENTINE:
				shipAttribute = "capacity";
			break;
			
			case SHIP_SHNYAVA:
				shipAttribute = "capacity";
			break;
		}
	}
	
	if(rank > 15 && rank <= 25)
	{
		shipType = SHIP_FLEUT + rand(3);
		
		switch(shipType)
		{
			case SHIP_FLEUT:
				shipAttribute = "turnrate";
			break;
			
			case SHIP_CARAVEL:
				if(rand(1) == 1)
				{
					shipAttribute = "speedrate";
				}
				else
				{
					shipAttribute = "turnrate";
				}
			break;
			
			case SHIP_PINNACE:
				shipAttribute = "capacity";
			break;
			
			case SHIP_CARACCA:
				if(rand(1) == 1)
				{
					shipAttribute = "speedrate";
				}
				else
				{
					shipAttribute = "turnrate";
				}
			break;
			
		}
	}
	
	if(rank > 25 && rank <= 35)
	{
		shipType = SHIP_SCHOONER_W + rand(2);
		
		switch(shipType)
		{
			case SHIP_SCHOONER_W:
				if(rand(1) == 1)
				{
					shipAttribute = "speedrate";
				}
				else
				{
					shipAttribute = "turnrate";
				}
			break;
			
			case SHIP_GALEON_L:
				shipAttribute = "capacity";
			break;
			
			case SHIP_CORVETTE:
				if(rand(1) == 1)
				{
					shipAttribute = "speedrate";
				}
				else
				{
					shipAttribute = "capacity";
				}
			break;
		}
	}
	
	if(rank > 35)
	{
		shipType = SHIP_GALEON_H + rand(1);
		
		switch(shipType)
		{
			case SHIP_GALEON_H:
				temp = rand(2);
				
				if(temp == 0)
				{
					shipAttribute = "speedrate";
				}
				else
				{
					if(temp == 1)
					{
						shipAttribute = "turnrate";
					}
					else
					{
						shipAttribute = "capacity";
					}
				}
			break;
			
			case SHIP_FRIGATE:
				shipAttribute = "turnrate";
			break;
		}
	}
	
	neededValue = BurntShipQuest_GetMaxNeededValue(shipType, shipAttribute);
	
	Log_TestInfo("shipType == " + shipType);
	Log_TestInfo("ShipAttribute == " + shipAttribute);
	Log_TestInfo("ShipNeededValue == " + neededValue);
	
	_npchar.Quest.BurntShip.ShipType = shipType;
	_npchar.Quest.BurntShip.ShipAttribute = shipAttribute;
	
	if(shipAttribute != "capacity") // Чтобы трюм с десятичными не писался
	{
		_npchar.Quest.BurntShip.ShipNeededValue = FloatToString(neededValue, 2);
	}
	else
	{
		_npchar.Quest.BurntShip.ShipNeededValue = MakeInt(neededValue);
	}
}

void SetJornalCapParam(ref npchar)
{
	//созадем рассеянного кэпа
	ref sld = GetCharacter(NPC_GenerateCharacter("PortmansCap_" + npchar.index, "", "man", "man", 20, sti(npchar.nation), -1, true, "citizen"));
	SetShipToFantom(sld, "trade", true);
	sld.Ship.Mode = "trade";
	SetCaptanModelByEncType(sld, "trade");
	sld.dialog.filename = "Quest\ForAll_dialog.c";
	sld.dialog.currentnode = "PortmansCap";
	sld.DeckDialogNode = "PortmansCap_inDeck";
	DeleteAttribute(sld, "SinkTenPercent");
	DeleteAttribute(sld, "SaveItemsForDead");
	DeleteAttribute(sld, "DontClearDead");
	DeleteAttribute(sld, "AboardToFinalDeck");
	DeleteAttribute(sld, "SinkTenPercent");
	DeleteAttribute(sld, "DontRansackCaptain");
	sld.AlwaysSandbankManeuver = true;
	sld.AnalizeShips = true;  //анализировать вражеские корабли при выборе таска
	sld.DontRansackCaptain = true; //не сдаваться
	SetCharacterPerk(sld, "ShipTurnRateUp");
	SetCharacterPerk(sld, "ShipTurnRateUp");
	LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER_OWN);
	//в морскую группу кэпа
	string sGroup = "PorpmansShip_" + sld.index;
	Group_FindOrCreateGroup(sGroup);
	Group_SetType(sGroup,"trade");
	Group_SetTaskAttackInMap(sGroup, PLAYER_GROUP);
	Group_LockTask(sGroup);
	Group_AddCharacter(sGroup, sld.id);
	Group_SetGroupCommander(sGroup, sld.id);
	SetRandGeraldSail(sld, sti(sld.Nation)); 
	//записываем данные в структуры портмана и кэпа
	npchar.quest = "PortmansJornal"; //личный флаг квеста для портмана
	npchar.quest.PortmansJornal.capName = GetFullName(sld); //имя кэпа
	npchar.quest.PortmansJornal.shipName = sld.Ship.name; //имя корабля
	npchar.quest.PortmansJornal.shipTapeName = RealShips[sti(sld.Ship.Type)].BaseName; //название корабля
	npchar.quest.PortmansJornal.city = SelectNotEnemyColony(npchar); //определим колонию, куда ушел кэп
	sld.quest = "InMap"; //личный флаг рассеянного кэпа
	sld.quest.targetCity = npchar.quest.PortmansJornal.city; //продублируем колонию-цель в структуру кэпа
	sld.quest.firstCity = npchar.city; //капитану знать откуда вышел в самом начале
	sld.quest.stepsQty = 1; //количество выходов в море
	sld.quest.money = ((sti(RealShips[sti(sld.Ship.Type)].basetype)+1) * 150) + (sti(pchar.rank)*150); //вознаграждение
	Log_TestInfo("Рассеянный кэп " + sld.id + " направился в: " + sld.quest.targetCity);
	//определим бухту, куда ставить энкаунтер. чтобы сразу не генерился перед ГГ у города
	string sTemp = GetArealByCityName(npchar.city);
	sld.quest.baseShore = GetIslandRandomShoreId(sTemp);
	//на карту
	sld.mapEnc.type = "trade";
	sld.mapEnc.worldMapShip = "ranger";
	sld.mapEnc.Name = XI_ConvertString(npchar.quest.PortmansJornal.shipTapeName) + " '" + npchar.quest.PortmansJornal.shipName + "'";
	int daysQty = GetMaxDaysFromIsland2Island(sTemp, GetArealByCityName(sld.quest.targetCity))+5; //дней доехать даем с запасом
	Map_CreateTrader(sld.quest.baseShore, sld.quest.targetCity, sld.id, daysQty);
	//заносим Id кэпа в базу нпс-кэпов
	sTemp = sld.id;
	NullCharacter.capitainBase.(sTemp).quest = "jornal"; //идентификатор квеста
	NullCharacter.capitainBase.(sTemp).questGiver = "none"; //запомним Id квестодателя для затирки в случае чего
	NullCharacter.capitainBase.(sTemp).Tilte1 = npchar.id + "PortmansBook_Delivery"; //заголовок квестбука
	NullCharacter.capitainBase.(sTemp).Tilte2 = "PortmansBook_Delivery"; //имя квеста в квестбуке
	NullCharacter.capitainBase.(sTemp).checkTime = daysQty + 5;
    NullCharacter.capitainBase.(sTemp).checkTime.control_day = GetDataDay();
    NullCharacter.capitainBase.(sTemp).checkTime.control_month = GetDataMonth();
    NullCharacter.capitainBase.(sTemp).checkTime.control_year = GetDataYear();
}
//проверить список отметившихся квестовых кэпов
int CheckCapitainsList(ref npchar)
{
	int bResult = 0;
	if (!CheckAttribute(npchar, "quest.capitainsList")) return bResult;
	aref arCapBase, arCapLocal;
    makearef(arCapBase, npchar.quest.capitainsList);
    int	Qty = GetAttributesNum(arCapBase);
	if (Qty < 1) return bResult;
	string sCapitainId; 
	for (int i=0; i<Qty; i++)
    {
    	arCapLocal = GetAttributeN(arCapBase, i);
        sCapitainId = GetAttributeName(arCapLocal);
    	if (GetCharacterIndex(sCapitainId) > 0) //если еще жив
    	{
			bResult++;			
    	}
		else
		{
			DeleteAttribute(arCapBase, sCapitainId);
			i--;
			Qty--;
		}
    }
	if (bResult > 5) bResult = 5;
	return bResult;
}

void SetSeekShipCapParam(ref npchar)
{
	//создаем кэпа-вора
	int Rank = sti(pchar.rank) + 5;
	if (Rank > 30) Rank = 30;
	ref sld = GetCharacter(NPC_GenerateCharacter("SeekCap_" + npchar.index, "", "man", "man", Rank, PIRATE, -1, true, "soldier"));
	SetShipToFantom(sld, "pirate", true);
	sld.Ship.Mode = "pirate";
	SetCaptanModelByEncType(sld, "pirate");
	sld.dialog.filename = "Quest\ForAll_dialog.c";
	sld.dialog.currentnode = "SeekCap";
	sld.DeckDialogNode = "SeekCap_inDeck";
	DeleteAttribute(sld, "SinkTenPercent");
	DeleteAttribute(sld, "SaveItemsForDead");
	DeleteAttribute(sld, "DontClearDead");
	DeleteAttribute(sld, "AboardToFinalDeck");
	DeleteAttribute(sld, "SinkTenPercent");
	DeleteAttribute(sld, "DontRansackCaptain");
	sld.AlwaysSandbankManeuver = true;
	sld.AnalizeShips = true;  //анализировать вражеские корабли при выборе таска
	sld.DontRansackCaptain = true; //не сдаваться
	SetCharacterPerk(sld, "FastReload");
	SetCharacterPerk(sld, "HullDamageUp");
	SetCharacterPerk(sld, "SailsDamageUp");
	SetCharacterPerk(sld, "CrewDamageUp");
	SetCharacterPerk(sld, "CriticalShoot");
	SetCharacterPerk(sld, "LongRangeShoot");
	SetCharacterPerk(sld, "CannonProfessional");
	SetCharacterPerk(sld, "ShipDefenseProfessional");
	SetCharacterPerk(sld, "ShipTurnRateUp");
	SetCharacterPerk(sld, "ShipTurnRateUp");
	SetCharacterPerk(sld, "StormProfessional");
	SetCharacterPerk(sld, "SwordplayProfessional");
	SetCharacterPerk(sld, "AdvancedDefense");
	SetCharacterPerk(sld, "CriticalHit");
	SetCharacterPerk(sld, "Sliding");
	SetCharacterPerk(sld, "Tireless");
	SetCharacterPerk(sld, "HardHitter");
	SetCharacterPerk(sld, "GunProfessional");
	//в морскую группу кэпа
	string sGroup = "SeekCapShip_" + sld.index;
	Group_FindOrCreateGroup(sGroup);
	Group_SetTaskAttackInMap(sGroup, PLAYER_GROUP);
	Group_LockTask(sGroup);
	Group_AddCharacter(sGroup, sld.id);
	Group_SetGroupCommander(sGroup, sld.id);
	SetRandGeraldSail(sld, sti(sld.Nation)); 
	//записываем данные в структуры портмана и кэпа
	npchar.quest = "PortmansSeekShip"; //личный флаг квеста для портмана
	npchar.quest.PortmansSeekShip.capName = GetFullName(sld); //имя кэпа-вора
	npchar.quest.PortmansSeekShip.shipName = sld.Ship.name; //имя украденного корабля
	npchar.quest.PortmansSeekShip.shipTapeName = RealShips[sti(sld.Ship.Type)].BaseName; //название украденного корабля
	npchar.quest.PortmansSeekShip.shipTape = RealShips[sti(sld.Ship.Type)].basetype; //тип украденного корабля
	//npchar.quest.money = ((sti(RealShips[sti(sld.Ship.Type)].basetype)+1) * 1000) + (sti(pchar.rank)*500); //вознаграждение
	npchar.quest.chest = 7-sti(RealShips[sti(sld.Ship.Type)].Class); //в сундуках
	sld.quest = "InMap"; //личный флаг кэпа-вора
	sld.city = SelectAnyColony(npchar.city); //определим колонию, откуда кэп-вор выйдет
	sld.quest.targetCity = SelectAnyColony2(npchar.city, sld.city); //определим колонию, куда он придет
	//Log_TestInfo("Кэп-вор " + sld.id + " вышел из: " + sld.city + " и направился в: " + sld.quest.targetCity);
	sld.quest.cribCity = npchar.city; //город, откуда кэп-вор спер корабль
	//на карту
	sld.mapEnc.type = "trade";
	sld.mapEnc.worldMapShip = "Galleon_red";
	sld.mapEnc.Name = XI_ConvertString(npchar.quest.PortmansSeekShip.shipTapeName) + " '" + npchar.quest.PortmansSeekShip.shipName + "'";
	int daysQty = GetMaxDaysFromIsland2Island(GetArealByCityName(sld.quest.targetCity), GetArealByCityName(sld.city))+3; //дней доехать даем с запасом
	Map_CreateTrader(sld.city, sld.quest.targetCity, sld.id, daysQty);
	//прерывание на абордаж
	string sTemp = "SeekShip_checkAbordage" + npchar.index;
	pchar.quest.(sTemp).win_condition.l1 = "Character_Capture";
	pchar.quest.(sTemp).win_condition.l1.character = sld.id;
	pchar.quest.(sTemp).function = "SeekShip_checkAbordage";
	pchar.quest.(sTemp).CapId = sld.id;
	//прерывание на потопление без абордажа
	sTemp = "SeekShip_checkSink" + npchar.index;
	pchar.quest.(sTemp).win_condition.l1 = "Character_sink";
	pchar.quest.(sTemp).win_condition.l1.character = sld.id;
	pchar.quest.(sTemp).function = "SeekShip_checkSink";
	pchar.quest.(sTemp).CapId = sld.id;
	//заносим Id кэпа в базу нпс-кэпов
	sTemp = sld.id;
	NullCharacter.capitainBase.(sTemp).quest = "robber"; //идентификатор квеста
	NullCharacter.capitainBase.(sTemp).questGiver = "none"; //запомним Id квестодателя для затирки в случае чего
	NullCharacter.capitainBase.(sTemp).Tilte1 = npchar.id + "Portmans_SeekShip"; //заголовок квестбука
	NullCharacter.capitainBase.(sTemp).Tilte2 = "Portmans_SeekShip"; //имя квеста в квестбуке
	NullCharacter.capitainBase.(sTemp).checkTime = daysQty + 5;
    NullCharacter.capitainBase.(sTemp).checkTime.control_day = GetDataDay();
    NullCharacter.capitainBase.(sTemp).checkTime.control_month = GetDataMonth();
    NullCharacter.capitainBase.(sTemp).checkTime.control_year = GetDataYear();
}

string GenQuestPortman_GenerateGem() // камни
{
	string itemID;
	switch(rand(5))
	{
		case 0:
			itemID = "jewelry1";	
		break;
		case 1:
			itemID = "jewelry2"; 
		break;
		case 2:
			itemID = "jewelry3"; 
		break;
		case 3:
			itemID = "jewelry3"; 
		break;
		case 4:
			itemID = "jewelry5"; 
		break;
		case 5:
			itemID = "jewelry6"; 
		break;
	}
	return itemID;
}

string findTraderCity_PU(ref NPChar)
{
	int n, nation;
    int storeArray[MAX_COLONIES];
    int howStore = 0;

	for(n=0; n<MAX_COLONIES; n++)
	{
		nation = GetNationRelation(sti(npchar.nation), sti(colonies[n].nation));
		if (nation != RELATION_ENEMY && colonies[n].id != "Panama" && colonies[n].id != "Minentown" && colonies[n].id != "SanAndres" && colonies[n].nation != "none" && GetIslandByCityName(npchar.city) != colonies[n].islandLable) //на свой остров
		{
			storeArray[howStore] = n;
			howStore++;
		}
	}
	if (howStore == 0) return "none";
	nation = storeArray[cRand(howStore-1)];
	return colonies[nation].id;
}

string findPassangerCity_PU(ref NPChar)
{
	int n, nation;
    int storeArray[MAX_COLONIES];
    int howStore = 0;

	for(n=0; n<MAX_COLONIES; n++)
	{
		nation = GetNationRelation(sti(npchar.nation), sti(colonies[n].nation));
		if (nation != RELATION_ENEMY && colonies[n].nation != "none" && colonies[n].id != "Panama" && colonies[n].id != "Minentown" && colonies[n].id != "SanAndres" && GetIslandByCityName(npchar.city) != colonies[n].islandLable) //на свой остров
		{
			storeArray[howStore] = n;
			howStore++;
		}
	}
	if (howStore == 0) return "none";
	nation = storeArray[cRand(howStore-1)];
	return colonies[nation].id;
}

// --> Jason, новые мини-квесты
string findCurrentCity1(ref NPChar)//выбираем целевой город 1
{
	int n, nation;
    int storeArray[MAX_COLONIES];
    int howStore = 0;

	for(n=0; n<MAX_COLONIES; n++)
	{
		nation = GetNationRelation(sti(pchar.nation), sti(colonies[n].nation));
		if (nation != RELATION_ENEMY && colonies[n].id != "Panama" && colonies[n].id != "Minentown" && colonies[n].id != "SanAndres" && colonies[n].nation != "none" && GetIslandByCityName(npchar.city) != colonies[n].islandLable) //на свой остров
		{
			storeArray[howStore] = n;
			howStore++;
		}
	}
	if (howStore == 0) return "none";
	nation = storeArray[dRand(howStore-1)];
	return colonies[nation].id;
}

string findCurrentCity2(ref NPChar)//выбираем целевой город 2
{
	int n, nation;
    int storeArray[MAX_COLONIES];
    int howStore = 0;

	for(n=0; n<MAX_COLONIES; n++)
	{
		nation = GetNationRelation(sti(pchar.nation), sti(colonies[n].nation));
		if (nation != RELATION_ENEMY && colonies[n].id != "Panama" && colonies[n].id != "Minentown" && colonies[n].id != "SanAndres" && colonies[n].nation != "none" && GetIslandByCityName(npchar.city) != colonies[n].islandLable) //на свой остров
		{
			storeArray[howStore] = n;
			howStore++;
		}
	}
	if (howStore == 0) return "none";
	nation = storeArray[abs(dRand(howStore-1)-3)];
	return colonies[nation].id;
}

string findCurrentCity3(ref NPChar)//выбираем целевой город 3
{
	int n, nation;
    int storeArray[MAX_COLONIES];
    int howStore = 0;

	for(n=0; n<MAX_COLONIES; n++)
	{
		nation = GetNationRelation(sti(pchar.nation), sti(colonies[n].nation));
		if (nation != RELATION_ENEMY && colonies[n].id != "Panama" && colonies[n].id != "Minentown" && colonies[n].id != "SanAndres" && colonies[n].nation != "none" && GetIslandByCityName(npchar.city) != colonies[n].islandLable) //на свой остров
		{
			storeArray[howStore] = n;
			howStore++;
		}
	}
	if (howStore == 0) return "none";
	nation = storeArray[abs(dRand(howStore-1)-7)];
	return colonies[nation].id;
}

int Escort_ShipType()
{
	int iShipType;
	switch (rand(2))
	{
		case 0: iShipType = SHIP_FLEUT; 	break;
		case 1: iShipType = SHIP_GALEON_L; 	break;
		case 2: iShipType = SHIP_PINNACE;	break;
	}
	return iShipType;
}

//<-- новые мини-квесты
