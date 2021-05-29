void ProcessDialogEvent()
{
	ref NPChar, her;
	aref Link, NextDiag;
	bool bOk = false;
    bool bOk2;
    
	int Sum, nRel, nDay, iChurchQuest2_Summ;
	ref sld;
	
	// Церковный квест № 2 -->
	if(CheckAttribute(PChar, "GenQuest.ChurchQuest_2.AskContra_1") && !CheckAttribute(PChar, "GenQuest.ChurchQuest_2.Summ_To_Contra"))
	{
		iChurchQuest2_Summ = sti(PChar.rank)*100 + (rand(3)+1)*100;
		PChar.GenQuest.ChurchQuest_2.Summ_To_Contra = sti(iChurchQuest2_Summ);
	}
	// <-- Церковный квест № 2
	
	string sColony;
	
	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
    string iDay, iMonth;
	iDay = environment.date.day;
	iMonth = environment.date.month;
	string lastspeak_date = iday + " " + iMonth;

	if (!CheckAttribute(npchar, "quest.trade_date"))
    {
        npchar.quest.trade_date = "";
    }

	//тереть нафиг аттрибут при прошествии дней (navy fix)
	if (CheckAttribute(pchar, "GenQuest.contraTravel.days") && GetQuestPastDayParam("contraTravel") > sti(PChar.GenQuest.contraTravel.days))
	{
		DeleteAttribute(pchar, "GenQuest.contraTravel");
		CloseQuestHeader("Gen_ContrabandTravel");
	}

	switch(Dialog.CurrentNode)
	{
        case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "Smuggling_exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			PlaceSmugglersOnShore(Pchar.quest.contraband.CurrentPlace);
			Pchar.quest.Contraband.active = true;
			pchar.GenQuest.Contraband.GuardNation = npchar.nation;
			pchar.GenQuest.Contraband.SmugglerId  = npchar.id;				
			SetAllContraGoods(&Stores[sti(Pchar.GenQuest.Contraband.StoreIdx)], npchar);
			ReOpenQuestHeader("Gen_Contraband");
            if (GetIslandByCityName(npchar.city) == "Mein")
            {
            	AddQuestRecord("Gen_Contraband", "t1_1");
            }
            else
            {
	            AddQuestRecord("Gen_Contraband", "t1");
				AddQuestUserData("Gen_Contraband", "sIsland", XI_ConvertString(GetIslandByCityName(npchar.city)));
			}
			AddQuestUserData("Gen_Contraband", "sLoc", GetConvertStr(Pchar.quest.contraband.CurrentPlace, "LocLables.txt"));
				
			DialogExit();
		break;
		
		case "First time":											
			//--> Jason если идет первая часть квеста Шарля
			if (CheckAttribute(pchar, "questTemp.Sharlie.Lock"))
            {
				dialog.text = "Месье, ступайте своей дорогой. Не думаю, что у нас с вами могут быть какие-то дела.";
				link.l1 = "Да что ты такое говоришь! Тебя смущает моя физиономия? Ладно, прощай...";
				link.l1.go = "exit";
				break;
			}
			//<-- идет первая часть квеста Шарля
			//--> Addon-2016 Jason блокировка контры во избежание конфликтов с квестами
			if (CheckAttribute(pchar, "GenQuest.SmugglersBlock") && pchar.GenQuest.SmugglersBlock == npchar.location)
            {
				dialog.text = "Сегодня никаких сделок не будет.";
				link.l1 = "Понятно.";
				link.l1.go = "exit";
				break;
			}
			
			//--> Jason Цена чахотки
			if (CheckAttribute(pchar, "questTemp.Consumption.Contra"))
            {
				dialog.text = "Что вы хотели, капитан?";
				link.l1 = "Можем мы немного поговорить?";
				link.l1.go = "Consumption";
				break;
			}
			//<-- Цена чахотки
			
			if(NPChar.quest.meeting == "0")
			{
				Dialog.Text = "Что вам надо, капитан? Я не знаю вашего имени, и не могу назвать вам свое.";
				Link.l1 = "Я капитан " + GetFullName(pchar) + ".";
				Link.l1.go = "meeting";
				NPChar.quest.meeting = "1"; 
			}
			else
			{
				if(CheckAttribute(pchar,"GenQuest.CaptainComission.GetRumour") && GetQuestPastDayParam("GenQuest.CaptainComission.GetRumour") < 1)
				{
					if(!CheckAttribute(pchar,"GenQuest.CaptainComission.SpeakContra"))
					{
						pchar.GenQuest.CaptainComission.SpeakContra = true;
						dialog.text = "Сегодня никаких сделок не будет. Во всех бухтах полно патруля, губернатор ищет груз, который капитан патрульного " + GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name") + "Acc")) + " " + pchar.GenQuest.CaptainComission.Name + " якобы конфисковал у какого-то пирата и спрятал.";
						link.l1 = "А где сам капитан " + pchar.GenQuest.CaptainComission.Name + "?";
						link.l1.go = "CapComission_1";
						break;
					}
					else
					{
						dialog.text = "Сегодня никаких сделок не будет.";
						link.l1 = "Понятно.";
						link.l1.go = "exit";					
						break;
					}
				}

				if(pchar.questTemp.Slavetrader == "FindMayak" && Islands[GetCharacterCurrentIsland(pchar)].id == pchar.questTemp.Slavetrader.EsIsland)
				{
					dialog.text = "Сегодня никаких сделок не будет.";
					link.l1 = "Понятно.";
					link.l1.go = "exit";
					break;
				}

				Dialog.Text = "Что вас интересует, капитан?";
				if (LAi_group_GetPlayerAlarm() > 0)
				{
	       			Dialog.Text = RandPhraseSimple("Говори быстрей, "+ GetSexPhrase("приятель","подруга") +", что тебе надо? А то, знаешь ли, погоня за тобой!", "Не медли, быстрее излагай суть дела! За тобой солдатня бегает, не до долгих бесед, знаешь ли...");
				}
				
				if(FindContrabandGoods(PChar) != -1)
				{
					Link.l1 = "Я бы хотел"+ GetSexPhrase("","а") +" кое-что продать или купить.";
					Link.l1.go = "Meeting_3";
				}

				if (CheckAttribute(pchar, "GenQuest.contraTravel.active") && sti(pchar.GenQuest.contraTravel.active) == true)
					Link.l2 = "Насчет поездки...";
				else
					Link.l2 = "Мне нужно добраться кое-куда.";
				Link.l2.go = "Travel";
				if (CheckCharacterItem(pchar, "CaptainBook") && !CheckAttribute(pchar, "questTemp.different.GiveShipLetters.speakSmuggler"))
				{
					if((pchar.questTemp.different.GiveShipLetters.city == npchar.city) && CheckAttribute(pchar, "questTemp.different.GiveShipLetters"))
					{
						link.l3 = "У меня есть 'особенный' товар, думаю тебе будет любопытно. Взгляни!";
						link.l3.go = "SM_ShipLetters_1";
					}	
				}				

				//Jason --> мини-квест Бесчестный конкурент
				if(CheckAttribute(PChar, "questTemp.Shadowtrader.seeksmugglers") && NPChar.location == pchar.questTemp.Shadowtrader.City + "_tavern")
				{
					Link.l8 = "У меня к тебе дело несколько необычного порядка.";
					Link.l8.go = "Shadowtrader_smugglers";
				}
				// <-- мини-квест Бесчестный конкурент
				//Jason --> генератор сбыта бакаута
				if(NPChar.location == "Marigo_tavern" && CheckAttribute(PChar, "GenQuest.Bakaut") && !CheckAttribute(PChar, "GenQuest.Bakaut.Info"))
				{
					Link.l9 = "Мне нужно встретиться с Михаэлем Розенкрафтом. У меня есть интересующий его товар.";
					Link.l9.go = "bakaut";
				}
				// <-- генератор сбыта бакаута
				
				// Церковный генератор №2 -->
				if(CheckAttribute(PChar, "GenQuest.ChurchQuest_2.AskContra_1") && NPChar.location == PChar.GenQuest.ChurchQuest_2.QuestTown + "_tavern")
				{
					Link.l4 = "Мне нужно кое-что выяснить, приятель.";
					Link.l4.go = "Contra_GenQuest_Church_2_1";
				}
				
				if(CheckAttribute(PChar, "GenQuest.ChurchQuest_2.AskContra_2") && NPChar.location == PChar.GenQuest.ChurchQuest_2.Contra_Colony + "_tavern")
				{
					Link.l5 = "Твой коллега и мой добрый приятель из " + XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_2.QuestTown + "Gen") + " сказал, что ты в курсе одного дела.";
					Link.l5.go = "Contra_GenQuest_Church_2_Contra2_1";
				}
				// <-- Церковный генератор №2
				
				Link.l7 = "Ничего. До встречи.";
				Link.l7.go = "Exit";				
			}
		break;
		
		case "CapComission_1":
			if(pchar.GenQuest.CaptainComission.variant == "A2")
			{
				dialog.text = "В подвале форта, где же ему ещё быть?.. Капитан в любой момент может выдать властям место, где спрятал груз, и тогда мы останемся с носом. Так что, пока не уляжется вся эта суета, даже не думайте о сделках.";
				link.l1 = "Слушайте, вы же каждый камень на острове знаете. Неужели вам не известен тайник капитана " + pchar.GenQuest.CaptainComission.Name + "?";
				link.l1.go = "CapComission_4";
			}
			if(pchar.GenQuest.CaptainComission.variant == "A3")
			{
				dialog.text = "На небесах, наверное. Казнили его недавно вместе с командой. А в приговоре-то не сказали, что судно было пиратским.";
				link.l1 = "А почему ты уверен, что судно принадлежало пиратам?";
				link.l1.go = "CapComission_2";
			}	
		break;
		
		case "CapComission_2":
			dialog.text = "Мы наблюдали тот бой со скалы пока не стемнело. В трубу отчётливо было видно, что " + GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipTypeVictim),"Name"))) + " под Чёрным Роджером. А потом, спустя часов пять, мы увидели в темноте только вспышку, будто крюйт-камера рванула. За это время вполне можно было вывезти товар на берег.";
			link.l1 = "А разве вам не известно, где тайник капитана " + pchar.GenQuest.CaptainComission.Name +"? Вы же каждый камень на острове знаете.";
			link.l1.go = "CapComission_3";
		break;
		
		case "CapComission_3":
			dialog.text = "Нет. Мы его тоже ищем, но не для того, чтобы обрадовать губернатора...";
			link.l1 = "Понятно... Ну, счастливо оставаться.";
			link.l1.go = "exit";
			AddQuestRecord("CaptainComission2", "38");
			AddQuestUserData("CaptainComission2", "sSex", GetSexPhrase("","а"));
			AddQuestUserData("CaptainComission2", "sShipType", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name") + "Acc")));
			AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);
			AddQuestUserData("CaptainComission2", "sShipTypeQuest", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipTypeVictim),"Name") + "Acc")));
		break;
		
		case "CapComission_4":
			dialog.text = "Нет. Мы его тоже ищем, но не для того, чтобы обрадовать губернатора, хе-хе...";
			link.l1 = "Понятно... Ну, счастливо оставаться.";
			link.l1.go = "exit";
			AddQuestRecord("CaptainComission2", "19");
			AddQuestUserData("CaptainComission2", "sShipType", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name") + "Acc")));
			AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);
		break;
				
		case "SM_ShipLetters_1":
			pchar.questTemp.different.GiveShipLetters.speakSmuggler = true;
			if(sti(pchar.questTemp.different.GiveShipLetters.variant) == 0)
			{
				dialog.text = "Почему ты так решил"+ GetSexPhrase("","а") +"? Я честный каботажник. Ищи другого покупателя.";
				link.l1 = "Спасибо и на этом....";
				link.l1.go = "exit";
			}
			else
			{
				if(!CheckAttribute(pchar, "questTemp.different.GiveShipLetters.speakUsurer_1"))
				{
					dialog.text = "Как сказать? Может быть, и пригодится твой 'товар'. Бери " + sti(pchar.questTemp.different.GiveShipLetters.price2) + " золотых, и забудь об этом.";
					link.l1 = "Пожалуй, нет.";
					link.l1.go = "SM_ShipLetters_2";	
					link.l2 = "Да, ты угадал, уже начинаю забывать!";
					link.l2.go = "SM_ShipLetters_3";
				}
				else
				{
					if(sti(pchar.questTemp.different.GiveShipLetters.variant) == 1)
					{
						dialog.text = "Точно! Мне уже не просто любопытно. Думаю, если заплачу тебе "+ sti(pchar.questTemp.different.GiveShipLetters.price3) +" золотых, то и тебе станет совсем не любопытно, что да как в этих бумагах.";
						link.l1 = "Пожалуй, нет.";
						link.l1.go = "SM_ShipLetters_2";
						link.l2 = "Да, ты угадал, уже начинаю забывать!";
						link.l2.go = "SM_ShipLetters_3";
					}
					if(sti(pchar.questTemp.different.GiveShipLetters.variant) == 2)
					{
						dialog.text = "Вот это шанс прищучить наглеца! Это очень, очень любопытно. Давай так: я плачу тебе " + sti(pchar.questTemp.different.GiveShipLetters.price4) + " золотом, а ты делаешь вид, что забыл"+ GetSexPhrase("","а") +" документы на столе?";
						link.l1 = "Пожалуй, нет.";
						link.l1.go = "SM_ShipLetters_2";
						link.l2 = "Да, ты угадал, уже начинаю забывать!";
						link.l2.go = "SM_ShipLetters_3";
					}
				}
			}
		break;
		
		case "SM_ShipLetters_2":
			dialog.text = "Ну-ну, смотри не наживи врагов.";
			link.l1 = "И ты оглядываться не забывай!";
			link.l1.go = "exit";
		break;
		
		case "SM_ShipLetters_3":
			TakeItemFromCharacter(pchar, "CaptainBook"); 
			if(sti(pchar.questTemp.different.GiveShipLetters.variant) == 1)
			{
				if(!CheckAttribute(pchar, "questTemp.different.GiveShipLetters.speakUsurer_1"))
				{
					addMoneyToCharacter(pchar, sti(pchar.questTemp.different.GiveShipLetters.price2)); 
				}
				else
				{
					addMoneyToCharacter(pchar, sti(pchar.questTemp.different.GiveShipLetters.price3)); 
				}
			}
			if(sti(pchar.questTemp.different.GiveShipLetters.variant) == 2)
			{
				if(!CheckAttribute(pchar, "questTemp.different.GiveShipLetters.speakUsurer_1"))
				{
					addMoneyToCharacter(pchar, sti(pchar.questTemp.different.GiveShipLetters.price2)); 
				}
				else
				{
					addMoneyToCharacter(pchar, sti(pchar.questTemp.different.GiveShipLetters.price4)); 
				}
			}
						
			if((sti(pchar.questTemp.different.GiveShipLetters.variant) == 0) || (sti(pchar.questTemp.different.GiveShipLetters.variant) == 2))
			{	
				ChangeCharacterComplexReputation(pchar,"nobility", -1); 
				OfficersReaction("bad"); 
			}	
			pchar.questTemp.different = "free";
			pchar.quest.GiveShipLetters_null.over = "yes"; //снимаем таймер 
			AddQuestRecord("GiveShipLetters", "7");			
			CloseQuestHeader("GiveShipLetters");
			DeleteAttribute(pchar, "questTemp.different.GiveShipLetters");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "Meeting":
			if(CheckAttribute(pchar,"GenQuest.CaptainComission.GetRumour") && GetQuestPastDayParam("GenQuest.CaptainComission.GetRumour") < 2)
			{
				if(!CheckAttribute(pchar,"GenQuest.CaptainComission.SpeakContra"))
				{
					pchar.GenQuest.CaptainComission.SpeakContra = true;
					dialog.text = "Сегодня никаких сделок не будет. Во всех бухтах полно патруля, губернатор ищет груз, который капитан патрульного " + GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name") + "Acc")) + " " + pchar.GenQuest.CaptainComission.Name + " якобы конфисковал у какого-то пирата и спрятал.";
					link.l1 = "А где сам капитан " + pchar.GenQuest.CaptainComission.Name + "?";
					link.l1.go = "CapComission_1";
					break;
				}
				else
				{
					dialog.text = "Сегодня никаких сделок не будет.";
					link.l1 = "Понятно.";
					link.l1.go = "exit";					
					break;
				}
			}
			
			if(pchar.questTemp.Slavetrader == "FindMayak" && Islands[GetCharacterCurrentIsland(pchar)].id == pchar.questTemp.Slavetrader.EsIsland)
			{
				dialog.text = "Сегодня никаких сделок не будет.";
				link.l1 = "Понятно.";
				link.l1.go = "exit";
				break;
			}
			
			Dialog.Text = "Чем могу быть полезен вам, капитан?";
			
			if(FindContrabandGoods(PChar) != -1)
			{
				Link.l1 = "Я бы хотел кое-что продать или купить.";
				Link.l1.go = "Meeting_1";
			}
			
			Link.l2 = "Мне нужно добраться кое-куда.";
			Link.l2.go = "Travel";				
			
			//Jason --> мини-квест Бесчестный конкурент
			if(CheckAttribute(PChar, "questTemp.Shadowtrader.seeksmugglers") && NPChar.location == pchar.questTemp.Shadowtrader.City + "_tavern")
			{
				Link.l8 = "У меня к тебе дело несколько необычного порядка.";
				Link.l8.go = "Shadowtrader_smugglers";
			}
			// <-- мини-квест Бесчестный конкурент
			//Jason --> генератор сбыта бакаута
			if(NPChar.location == "Marigo_tavern" && CheckAttribute(PChar, "GenQuest.Bakaut") && !CheckAttribute(PChar, "GenQuest.Bakaut.Info"))
			{
				Link.l9 = "Мне нужно встретиться с Михаэлем Розенкрафтом. У меня есть интересующий его товар.";
				Link.l9.go = "bakaut";
			}
			// <-- генератор сбыта бакаута
			
			// Церковный генератор №2 -->
			if(CheckAttribute(PChar, "GenQuest.ChurchQuest_2.AskContra_1") && NPChar.location == PChar.GenQuest.ChurchQuest_2.QuestTown + "_tavern")
			{
				Link.l3 = "Мне нужно кое-что выяснить, приятель.";
				Link.l3.go = "Contra_GenQuest_Church_2_1";
			}
			
			if(CheckAttribute(PChar, "GenQuest.ChurchQuest_2.AskContra_2") && NPChar.location == PChar.GenQuest.ChurchQuest_2.Contra_Colony + "_tavern")
			{
				Link.l3 = "Твой коллега и мой добрый приятель из " + XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_2.QuestTown + "Gen") + " сказал, что ты в курсе одного дела.";
				Link.l3.go = "Contra_GenQuest_Church_2_Contra2_1";
			}
			// <-- Церковный генератор №2

			Link.l5 = "Ничем. Удачи!";
			Link.l5.go = "Exit";				
		break;

		// Церковный генератор №2 -->
		case "Contra_GenQuest_Church_2_1":
			iChurchQuest2_Summ = PChar.GenQuest.ChurchQuest_2.Summ_To_Contra;
			dialog.text = "Я тебе не приятель. А кое-что выяснить может дорого тебе обойтись.";
				link.l1 = "Хм. Мне нужно узнать нечто, стоящее не более " + FindRussianMoneyString(iChurchQuest2_Summ) + ".";
				link.l1.go = "Contra_GenQuest_Church_2_2";
			break;
			
		case "Contra_GenQuest_Church_2_2":
			iChurchQuest2_Summ = PChar.GenQuest.ChurchQuest_2.Summ_To_Contra;
			if(sti(PChar.money) >= iChurchQuest2_Summ)
			{
				dialog.text = "Давай сюда свои деньги. И учти, за такую сумму много не узнаешь.";
				link.l1 = "Мне много и не надо. Понимаешь, разминул"+ GetSexPhrase("ся","ась") +" я тут с друзьями. Опоздал"+ GetSexPhrase("","а") +" на встречу, а они не стали ждать...";
				link.l1.go = "Contra_GenQuest_Church_2_3";
				AddMOneyToCharacter(PChar, -iChurchQuest2_Summ);
				DeleteAttribute(PChar, "GenQuest.ChurchQuest_2.AskContra_1");
				DeleteAttribute(PChar, "GenQuest.ChurchQuest_2.Summ_To_Contra");
			}
			else
			{
				dialog.text = "Хех, да у тебя же нету денег! Приходи, когда разбогатеешь...";
				link.l1 = "Точно.";
				link.l1.go = "exit";
			}
			break;
			
		case "Contra_GenQuest_Church_2_3":
				dialog.text = "А я здесь причем?";
				link.l1 = "В городе их нет, своего корабля у них тоже не было. Вот я и подумал"+ GetSexPhrase("","а") +", может быть, кто из твоих деловых партнёров оказал им некую услугу?..";
				link.l1.go = "Contra_GenQuest_Church_2_4";
			break;
			
		case "Contra_GenQuest_Church_2_4":
			sColony = QuestGetColony(PChar.GenQuest.ChurchQuest_2.QuestTown);
			dialog.text = "Вот оно что... Ну, было дело. Подошли люди, сказали, что им срочно нужно отчаливать, и при этом неважно куда. Мы в таких случаях причины не спрашиваем, лишь бы  цену платили. У нас ходка была в " + XI_ConvertString("Colony" + sColony + "Acc") + ", что находится на " + XI_ConvertString(locations[FindLocation(sColony + "_Town")].IslandID + "Dat") + ", туда они и погрузились. Можем и тебя подбросить, если в цене сойдёмся.";
			link.l1 = "Спасибо, я под своим парусом.";
			link.l1.go = "exit";
			sQuestTitle = PChar.GenQuest.ChurchQuest_2.QuestTown + "ChurchGenQuest2";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest2", "8");
			AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("","а"));
			AddQuestUserData(sQuestTitle, "sCity", XI_ConvertString("Colony" + sColony + "Acc"));
			AddQuestUserData(sQuestTitle, "sIsland", XI_ConvertString(locations[FindLocation(sColony + "_Town")].IslandID + "Dat"));
			PChar.GenQuest.ChurchQuest_2.AskContra_2 = true;
			PChar.GenQuest.ChurchQuest_2.Contra_Colony = sColony;
		break;
			
		case "Contra_GenQuest_Church_2_Contra2_1":
			dialog.text = "С тобой я пока не имел никаких дел.";
			link.l1 = "Ну, это вопрос времени. Не так давно вы привезли сюда моих друзей, с которыми я разминул"+ GetSexPhrase("ся","ась") +".";
			link.l1.go = "Contra_GenQuest_Church_2_Contra2_2";
		break;
			
		case "Contra_GenQuest_Church_2_Contra2_2":
			string sGenLocation = IslandGetLocationFromType(locations[FindLocation(PChar.GenQuest.ChurchQuest_2.Contra_Colony + "_Town")].IslandID, "Shore");
			PChar.GenQuest.ChurchQuest_2.QuestGangShore = sGenLocation;
			PChar.GenQuest.ChurchQuest_2.BanditsInShore = true;
			dialog.text = "Хм, мы высадили их " + XI_ConvertString(sGenLocation + "Dat") + "... Знаешь, лучше бы они и вправду оказались тебе друзьями, иначе бы я не советовал их беспокоить.";
			link.l1 = "Спасибо за заботу, но я вооружен"+ GetSexPhrase("","а") +" и очень обаятел"+ GetSexPhrase("ен","ьна") +".";
			link.l1.go = "exit";
			SetFunctionLocationCondition("Church_GenQuest2_GenerateBandits", sGenLocation, false);
			sQuestTitle = PChar.GenQuest.ChurchQuest_2.QuestTown + "ChurchGenQuest2";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest2", "9");
			AddQuestUserData(sQuestTitle, "sShore", XI_ConvertString(sGenLocation + "Acc"));
			locations[FindLocation(sGenLocation)].DisableEncounters = true;
			SetFunctionTimerCondition("Church_GenQuest2_TimeIsLeft", 0, 0, 1, false);
			DeleteAttribute(PChar, "GenQuest.ChurchQuest_2.AskContra_2");
		break;
		// <-- Церковный генератор №2

		case "Meeting_1":
			Dialog.Text = "Хм... Причем здесь я? Наверное, вы не туда зашли, капитан. Идите в магазин - там покупайте и продавайте все что вам нужно.";
			Link.l1 = "Боюсь, что мне нужны именно вы.";
			Link.l1.go = "Meeting_2";				
			Link.l2 = "Спасибо за совет. Всего хорошего.";
			Link.l2.go = "exit";				
		break;

		case "Meeting_2":
			Dialog.Text = "Зачем же?";
			Link.l1 = "Возможно вас заинтересуют некоторые товары, возможно и вы что-то сможете мне предложить - не правда ли ?"
			Link.l1.go = "Meeting_3";				
		break;

		case "Meeting_3":
			int iTmp = false;
			int iChIdx, i;

			// поиск мин.  те старшего класса
			for (i=0; i<COMPANION_MAX; i++)
			{
				iChIdx = GetCompanionIndex(GetMainCharacter(), i);
				if (iChIdx>=0)
				{
					sld = GetCharacter(iChIdx);
            		if (GetCharacterShipClass(sld) < ((MOD_SKILL_ENEMY_RATE/5.0) + 1.5)) iTmp = true;
				}
			}
			
			if (iTmp)
			{
				dialog.text = NPCStringReactionRepeat("Ты бы еще на королевском мановаре явил"+ GetSexPhrase("ся","ась") +". Да твою посудину за милю видать из форта. Мы не будем рисковать своими головами. Приходи на меньшем корабле, и только на одном.", 
					"Я что, непонятно выражаюсь? Найди себе суденышко поменьше, тогда и приходи.", 
					"Ты что, тупица или притворяешься? Говорю же тебе - найди себе шхуну, ну бриг на крайний случай, или сделка не состоится.",
					"Ох, и как таких дур"+ GetSexPhrase("аков","") +" земля носит...", "block", 1, npchar, Dialog.CurrentNode);
				link.l1 = HeroStringReactionRepeat("Хорошо, я тебя понял"+ GetSexPhrase("","а") +". Приду позже, как кораблик сменю.", 
					"Да все понятно, просто уточнить хотел"+ GetSexPhrase("","а") +".",
					"Нет, не тупица, просто жадина. Подумал"+ GetSexPhrase("","а") +", может поменялось что. Я бы еще пару пинасов с собой прихватил"+ GetSexPhrase("","а") +"...", 
					"Ну ты же видишь - носит как-то...", npchar, Dialog.CurrentNode);
				link.l1.go = DialogGoNodeRepeat("exit", "", "", "", npchar, Dialog.CurrentNode);	
				break;
			}
			bOk  = CheckAttribute(pchar, "GenQuest.contraTravel.active") && (sti(pchar.GenQuest.contraTravel.active) == true);
			bOk2 = CheckAttribute(Pchar, "quest.Contraband.Active") && (sti(Pchar.quest.Contraband.Active) == true);
			bool bOk3 = CheckAttribute(Pchar, "questTemp.pirateStartQuest") && (Pchar.questTemp.pirateStartQuest == "3");
			if (bOk)
			{
			    if (GetQuestPastDayParam("contraTravel") > sti(PChar.GenQuest.contraTravel.days))
				{  // просрочка
					DeleteAttribute(PChar, "GenQuest.contraTravel");
					CloseQuestHeader("Gen_ContrabandTravel");
					bOk = false;
				}
			}

//navy --> PGG
			if (CheckFreeServiceForNPC(NPChar, "Smugglers") != -1)
			{
				Dialog.Text = "Извини, "+ GetSexPhrase("парень","деваха") +", у нас уже есть дела. Зайди через пару дней.";
				Link.l1 = "Жаль...";
				Link.l1.go = "Exit";		
				break;
			}
//navy <--

			if (bOk || bOk2 || bOk3)
			{
				Dialog.Text = "Может, стоит завершить одно дело прежде, чем браться за другое?";
				Link.l1 = "Пожалуй, ты прав.";
				Link.l1.go = "Exit";				
			}
			else
			{
                if (npchar.quest.trade_date != lastspeak_date)
    			{
                    npchar.quest.trade_date = lastspeak_date;
                    
                    if (ChangeContrabandRelation(pchar, 0) > 5)
                    {
                        Pchar.quest.contraband.CurrentPlace = SelectSmugglingLocation();
						Pchar.quest.contraband.City = NPChar.city;
                        if (Pchar.quest.contraband.CurrentPlace != "None")//boal fix
                        {
                            if (ChangeContrabandRelation(pchar, 0) >= 70)
                            {
                                Dialog.Text = "Я знаю, с тобой можно иметь дело. Мы будем ждать тебя в месте, называющемся " + GetConvertStr(Pchar.quest.contraband.CurrentPlace, "LocLables.txt") + ".";
                            }
                            else
                            {
            				    Dialog.Text = "Хм... Возможно, покупатель и найдется. Мы будем ждать вас в месте, называющемся " + GetConvertStr(Pchar.quest.contraband.CurrentPlace, "LocLables.txt") + ".";
            				}
            				Link.l1 = "Хорошо. До встречи.";
            				Link.l1.go = "Smuggling_exit";
        				}
        				else
        				{   //boal fix
                            Dialog.Text = "Сегодня сделок больше не будет. Приходи завтра.";
            				Link.l1 = "Хорошо.";
            				Link.l1.go = "Exit";
        				}
    				}
    				else
    				{
                        Dialog.Text = "И после всего ты думаешь, что кто-то захочет работать с тобой? Радуйся, что мы еще не послали наемных убийц за твоей головой. Убирайся!";
        				Link.l1 = "Эх... значит не судьба мне стать контрабандистом.";
        				Link.l1.go = "Exit";
    				}
				}
				else
				{
                    Dialog.Text = "Сегодня сделок больше не будет. Приходи завтра.";
    				Link.l1 = "Хорошо.";
    				Link.l1.go = "Exit";
				}
			}
		break;
////////////////////////////////////////////////////////////////////////////////
//	Корсарское метро
////////////////////////////////////////////////////////////////////////////////
		case "Travel":
//navy --> PGG
			if (CheckFreeServiceForNPC(NPChar, "Smugglers") != -1)
			{
				Dialog.Text = "Извини, "+ GetSexPhrase("парень","деваха") +", у нас уже есть дела. Зайди через пару дней.";
				Link.l1 = "Жаль...";
				Link.l1.go = "Exit";		
				break;
			}
//navy <--
			//если нет корабля у ГГ и нет компаньонов все ок
			if (sti(pchar.ship.type) == SHIP_NOTUSED && GetCompanionQuantity(pchar) == 1 && GetPassengersQuantity(pchar) == 0)
			{
				//случай если уже была инфа
				if (CheckAttribute(pchar, "GenQuest.contraTravel.active") && sti(pchar.GenQuest.contraTravel.active) == true)
				{
					//платил уже
					if (CheckAttribute(pchar, "GenQuest.contraTravel.payed") && sti(pchar.GenQuest.contraTravel.payed) == true)
					{
						Dialog.Text = "Мы, кажется уже договорились?";
						Link.l2 = "Да, точно!";
					}
					//не платил, значит можно запалатить пока не вышел срок.
					else
					{
						if(GetQuestPastDayParam("contraTravel") == sti(PChar.GenQuest.contraTravel.days))
						{
							Dialog.Text = "Принес"+ GetSexPhrase("","ла") +" деньги?";
							Link.l1 = "Да.";
							Link.l1.go = "Travel_pay";
							Link.l3 = "Я передумал"+ GetSexPhrase("","а") +"....";
							Link.l3.go = "Travel_abort";
							Link.l2 = "Нет пока.";
						}
						else
						{
                            if (GetQuestPastDayParam("contraTravel") < sti(PChar.GenQuest.contraTravel.days))
							{
								Dialog.Text = "Я тебе уже все сказал.";
								Link.l2 = "Точно.";
								Link.l1 = "Я передумал"+ GetSexPhrase("","а") +"....";
								Link.l1.go = "Travel_abort";
							}
							else // просрочка
							{
							    Dialog.Text = "Сегодня я ничем не могу помочь. Приходи через пару дней, может, что и будет.";
								Link.l2 = "Жаль.";
								DeleteAttribute(PChar, "GenQuest.contraTravel");
								CloseQuestHeader("Gen_ContrabandTravel");
							}
						}
					}
				}
				//если не было договора, обговариваем условия
				else
				{
					nRel = ChangeContrabandRelation(pchar, 0);
					//если нормальные отношения и количество подстав меньше 20, работаем....
					if (nRel > 0 && Statistic_AddValue(PChar, "contr_TravelKill", 0) < 20)
					{
						//бухта...
						pchar.GenQuest.contraTravel.CurrentPlace = SelectSmugglingLocation();
						aref arTmp; makearef(arTmp, pchar.GenQuest.contraTravel);
						SetSmugglersTravelDestination(arTmp);
						//за сколько доставят 
						pchar.GenQuest.contraTravel.price = (sti(PChar.rank)*250 + (100 - nRel)*10 + rand(30)*20) + sti(arTmp.destination.days)*100;
						
						//если метро активно, и нет пассажиров у ГГ, и еще сегодня не виделись, есть доступная бухта, и ранд ...
						bOk = !bPauseContrabandMetro && CheckNPCQuestDate(npchar, "Travel_Talk") && 
							Pchar.GenQuest.contraTravel.CurrentPlace != "None" && rand(50) < nRel;
                        bOk2 = CheckAttribute(Pchar, "quest.Contraband.Active") && (sti(Pchar.quest.Contraband.Active) == true);
						if (bOk && !bOk2)
						{
							nDay = 1 + rand(3);
							SetNPCQuestDate(npchar, "Travel_Talk");
							SaveCurrentQuestDateParam("contraTravel");

							Dialog.Text = "Что ж, можем доставить тебя до места " + GetConvertStr(locations[FindLocation(pchar.GenQuest.contraTravel.destination.loc)].id, "LocLables.txt") + " близ " +
								XI_ConvertString("Colony" + pchar.GenQuest.contraTravel.destination + "Gen") + " за " + pchar.GenQuest.contraTravel.price + " золотых. Принесешь деньги через " +
								FindRussianDaysString(nDay) + ". Корабль будет ждать тебя в месте под названием " +
								GetConvertStr(locations[FindLocation(Pchar.GenQuest.contraTravel.CurrentPlace)].id, "LocLables.txt") + " ровно сутки.";

							pchar.GenQuest.contraTravel.days = nDay;
							Link.l1 = "Хорошо, меня устраивает.";
							Link.l1.go = "Travel_agree";
							Link.l2 = "Нет, спасибо.";
						}
						else
						{
							Dialog.Text = "Сегодня я ничем не могу помочь. Приходи через пару дней, может что и будет.";
							Link.l2 = "Жаль.";
						}
					}
					//нет, посылаем в сад
					else
					{
                        Dialog.Text = "И после всего ты думаешь, что кто-то захочет работать с тобой? Радуйся, что мы еще не послали наемных убийц за твоей головой. Убирайся!";
        				Link.l2 = "Эх... значит не судьба.";
					}

				}
			}
			//корабль есть, посылаем в сад...
			else 
			{
				if(GetPassengersQuantity(pchar) != 0)
				{
					Dialog.Text = "Нет, мы не повезем вас. Только одного.";
					Link.l2 = RandSwear() + " И не нужно!";
				}
				else
				{
					Dialog.Text = "А свой корабль тебе зачем? Нет, мы этим не занимаемся.";
					Link.l2 = "Видно, не судьба...";
				}
			}
			Link.l2.go = "Exit";
			break;

		//отмена
		case "Travel_abort":
			ChangeContrabandRelation(pchar, -2);
			DeleteAttribute(PChar, "GenQuest.contraTravel");
			CloseQuestHeader("Gen_ContrabandTravel");
			Dialog.Text = "Ну, как хочешь...";
			Link.l1 = "";
			Link.l1.go = "Exit";
			break;

		//ГГ согласен ехать
		case "Travel_agree":
			ReOpenQuestHeader("Gen_ContrabandTravel");
			AddQuestRecord("Gen_ContrabandTravel", "1");
			AddQuestUserData("Gen_ContrabandTravel", "sSex", GetSexPhrase("","а"));
			AddQuestUserData("Gen_ContrabandTravel", "sLoc", GetConvertStr(pchar.GenQuest.contraTravel.CurrentPlace, "LocLables.txt"));
			AddQuestUserData("Gen_ContrabandTravel", "sLocTo", GetConvertStr(pchar.GenQuest.contraTravel.destination.loc, "LocLables.txt"));
			AddQuestUserData("Gen_ContrabandTravel", "sPlaceTo", XI_ConvertString("Colony" + pchar.GenQuest.contraTravel.destination + "Gen"));
			AddQuestUserData("Gen_ContrabandTravel", "sDays", FindRussianDaysString(sti(pchar.GenQuest.contraTravel.days)));
			AddQuestUserData("Gen_ContrabandTravel", "sPrice", pchar.GenQuest.contraTravel.price);

			//активируем квест
			pchar.GenQuest.contraTravel.active = true;
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			break;

		//ГГ согласен платить
		case "Travel_pay":
			//денег хватает?
			Sum = sti(pchar.GenQuest.contraTravel.price);
			if (sti(pchar.money) >= Sum)
			{
				AddMoneyToCharacter(pchar, -1*Sum);
				//ставим флаг оплаты
				pchar.GenQuest.contraTravel.payed = true;
				Dialog.Text = "Приятно иметь с тобой дело. Корабль ждет, не опоздай.";
				Link.l1 = "Постараюсь.";
				AddQuestRecord("Gen_ContrabandTravel", "2");
				AddQuestUserData("Gen_ContrabandTravel", "sSex", GetSexPhrase("","а"));
				
				//ставим контру.
				PlaceSmugglersOnShore(PChar.GenQuest.contraTravel.CurrentPlace);
				//корабль на волнах в бухте....
				Sum = sti(pchar.GenQuest.contraTravel.destination.days);
				sld = GetCharacter(NPC_GenerateCharacter("Abracham_Gray", "citiz_46", "man", "man", 5, PIRATE, Sum + 2, true, "hunter"));
				//воскресим...
				sld.nation = PIRATE;
				SetRandomNameToCharacter(sld);
				SetMerchantShip(sld, rand(GOOD_PAPRIKA));
				SetFantomParamHunter(sld);
				SetCaptanModelByEncType(sld, "pirate");
				SetCharacterShipLocation(sld, PChar.GenQuest.contraTravel.CurrentPlace);

				SetTimerCondition("RemoveTravelSmugglers", 0, 0, 1, false);
			}
			//нет, посылаем в сад...
			else
			{
				Dialog.Text = "Похоже, у тебя проблемы с наличностью."
				Link.l1 = "Жаль, приду позже.";
			}
			Link.l1.go = "Exit";
		break;  
////////////////////////////////////////////////////////////////////////////////
//	END OF Корсарское метро
////////////////////////////////////////////////////////////////////////////////
				
		//Jason --> мини-квест Бесчестный конкурент
		case "Shadowtrader_smugglers":
			dialog.text = "Очень интересно. Ну, выкладывай, что там у тебя.";
			link.l1 = "Мне стало известно, что в этом городе есть подпольный магазин, открытый не без вашей помощи. Я бы очень хотел потолковать с хозяином этой лавочки.";
			link.l1.go = "Shadowtrader_fail";
			link.l2 = "Я слышал, что теперь с вами можно торговать не только... особенным товаром. Причем по очень заманчивым ценам. Мне со дня на день отправляться в плавание, а денег на все необходимое не хватает - хотел бы закупиться подешевле...";
			link.l2.go = "Shadowtrader_smugglers_1";
			DeleteAttribute(pchar, "questTemp.Shadowtrader.seeksmugglers");
		break;
		
		case "Shadowtrader_fail":
			dialog.text = "О чем это ты? Я тебя не понимаю. Никакого магазина мы не открывали - ты сам-то соображаешь, о чем говоришь, ха-ха-ха! Хочешь торговать - привози товар, тогда и поговорим, как обычно, в укромном месте. Тоже мне придумал - магазин!";
			link.l1 = "Гм...";
			link.l1.go = "exit";
			pchar.questTemp.Shadowtrader = "true";
			AddQuestRecord("Shadowtrader", "3");
			CloseQuestHeader("Shadowtrader");
		break;
		
		case "Shadowtrader_smugglers_1":
			dialog.text = "Хочешь затариться по низким ценам? Ну, это мы можем устроить. Приходи, когда стемнеет, к портовому управлению. Там тебя встретит наш человек и проводит в нужное место.";
			link.l1 = "Хорошо. Обязательно приду!";
			link.l1.go = "Shadowtrader_smugglers_2";		
		break;
		
		case "Shadowtrader_smugglers_2":
			pchar.questTemp.Shadowtrader.SeekTrader = "true";
			AddQuestRecord("Shadowtrader", "5");
			AddQuestUserData("Shadowtrader", "sCity", XI_ConvertString("Colony"+pchar.questTemp.Shadowtrader.City+"Gen"));
			SetFunctionTimerCondition("ShadowtraderTimeSmugglers_Over", 0, 0, 2, false);
			int iNation = pchar.questTemp.Shadowtrader.nation;
			int iRank = sti(pchar.rank)+MOD_SKILL_ENEMY_RATE+3;
			sld = GetCharacter(NPC_GenerateCharacter("ShadowAgent_1", "citiz_"+(rand(9)+41), "man", "man", iRank, iNation, 2, true, "quest"));
			SetFantomParamFromRank(sld, iRank, true);
			GiveItem2Character(sld, "blade_04");
			EquipCharacterbyItem(sld, "blade_04");
			LAi_SetCitizenType(sld);
			sld.dialog.Filename = "Common_citizen.c";
			sld.dialog.currentnode = "First time";	
			sld.greeting = "cit_common"; 
			sld.city = pchar.questTemp.Shadowtrader.City;
			LAi_SetImmortal(sld, true);
			ChangeCharacterAddressGroup(sld, pchar.questTemp.Shadowtrader.City +"_town", "goto", "goto1");
			pchar.quest.Shadowtrader_SMG.win_condition.l1 = "locator";
			pchar.quest.Shadowtrader_SMG.win_condition.l1.location = pchar.questTemp.Shadowtrader.City + "_town";
			pchar.quest.Shadowtrader_SMG.win_condition.l1.locator_group = "reload";
			pchar.quest.Shadowtrader_SMG.win_condition.l1.locator = "reload10_back";
			pchar.quest.Shadowtrader_SMG.win_condition.l2 = "Night";
			pchar.quest.Shadowtrader_SMG.function = "ShadowAgent";
			DialogExit();
		break;
		// <-- Бесчестный конкурент
			
		//--> Цена чахотки
		case "Consumption":
			dialog.text = "Тут полная зала праздных гуляк, сударь – нет дела – ступайте к ним, пейте и пустословьте, пока под стол не свалитесь. А здесь место занято.";
			link.l1 = "Попробуем иначе. Я оплачу твое время и свое любопытство – мне нужны кое-какие ответы.";
			link.l1.go = "Consumption_1";
		break;
		
		case "Consumption_1":
			if (sti(pchar.money) >= 3002)
			{
				dialog.text = "Оплатит он, вишь как, ха! Мое время недешево, сеньор, с вас 3000 песо и кружка этого паршивого пойла, что по ошибке здесь зовут ромом.";
				link.l1 = "По рукам! А теперь расскажи-ка мне о парне из ваших, что пробыл почти полгода в тюрьме, а потом вышел. Что с ним произошло?";
				link.l1.go = "Consumption_2";
			}
			else
			{
				dialog.text = "Сначала набей карманы серебром, а лучше - золотом. Тогда и приходи, некогда мне тут с тобой за бесплатно распинаться.";
				link.l1 = "...";
				link.l1.go = "exit";
			}
		break;
		
		case "Consumption_2":
			AddMoneyToCharacter(pchar, -3002);
			dialog.text = "Да, была такая история, хоть я и не пойму, что вам до нее за дело. Парень совсем свихнулся в этих подземельях – спивался здесь день за днем и все нес какую-то чушь про чахотку, что забирает людей, и никто ничего не слышит и не говорит. Утверждал, представляете, какая глупость, что у чахотки той имя есть, но называть его нельзя – иначе она придет и за тобой.";
			link.l1 = "что с ним случилось потом?";
			link.l1.go = "Consumption_3";
		break;
		
		case "Consumption_3":
			dialog.text = "Странный вышел случай, синьор. Местных гуляк и матросню это весьма забавляло, но приелось, как и любые басни, вот они его и раззадорили как-то раз, подбили назвать это имя. Парень брыкался и упирался, потом не выдержал насмешек и почти выкрикнул его\nНикто ничего особенного не почувствовал, и свечи не гасли, но беднягу на утро нашли за таверной с перерезанной глоткой.";
			link.l1 = "Больше похоже на дела людские, чем на происки темных сил. А что за имя он назвал, не припомнишь?";
			link.l1.go = "Consumption_4";
		break;
		
		case "Consumption_4":
			dialog.text = "Помню, конечно, но, черт меня подери, если я назову его вслух. Может произошедшее и не связано между собой, но есть во всем этом что-то зловещее, не находите?";
			link.l1 = "Эй, приятель, ты получил от меня кошель звонких монет, ты не забыл? Так что будь так любезен - назови это имя.";
			link.l1.go = "Consumption_5";
		break;
		
		case "Consumption_5":
			dialog.text = "Ох, не кончится это добром, сеньор, ох не кончится...(понижает голос) Он сказал - Хуан...";
			link.l1 = "Тьфу ты! Хуан? Да это же обычное имя, причем весьма популярное, что в нем такого?";
			link.l1.go = "Consumption_6";
		break;
		
		case "Consumption_6":
			dialog.text = "Не знаю, но человека, произнесшего его в тот вечер, убили еще до следующего восхода солнца. Поверьте чутью старого пройдохи – недоброе это имя, и что бы оно ни значило, это тоже не к добру. Это все, что вы хотели знать?";
			link.l1 = "Да, пожалуй, все. Ром купишь себе сам. Бывай!";
			link.l1.go = "Consumption_7";
		break;
		
		case "Consumption_7":
			DialogExit();
			DeleteAttribute(pchar, "questTemp.Consumption.Contra");
			pchar.questTemp.Consumption.AskJuan = 0;
			pchar.questTemp.Consumption = "current";
			AddQuestRecord("Consumption", "6");
		break;
		//<-- Цена чахотки
		
		//Jason --> генератор сбыта бакаута
		case "bakaut":
			dialog.text = "Вот как? Хорошо. Минхеру Розенкрафту сейчас нужна партия бакаута объемом не меньше "+FindRussianQtyString(sti(pchar.GenQuest.Bakaut.Value))+". У вас есть столько товара?";
			if (GetSquadronGoods(pchar, GOOD_SANDAL) >= sti(pchar.GenQuest.Bakaut.Value))
			{
				link.l1 = "Да, есть. Где мне найти минхера Розенкрафта?";
				link.l1.go = "bakaut_1";
			}
			else
			{
				link.l1 = "Хм. Такого количества у меня, к сожалению, сейчас нет.";
				link.l1.go = "bakaut_no";
			}
		break;
		
		case "bakaut_no":
			dialog.text = "Тогда не стоит и беспокоить минхера Розенкрафта. Приходите, когда у вас будет такая партия.";
			link.l1 = "Хорошо, договорились...";
			link.l1.go = "exit";
		break;
		
		case "bakaut_1":
			dialog.text = "Его галеон будет крейсировать у берегов "+XI_ConvertString(pchar.GenQuest.Bakaut.Island+"Gen")+" еще в течение "+FindRussianDaysString(sti(pchar.GenQuest.Bakaut.DaysQty))+". Так что не опаздывайте - потом он вполне может уйти в другое место архипелага.";
			link.l1 = "Хорошо, я потороплюсь. Спасибо!";
			link.l1.go = "bakaut_2";
		break;
		
		case "bakaut_2":
			DialogExit();
			sld = characterFromId("Rozencraft");
			sld.DeckDialogNode = "bakaut";
			DeleteAttribute(sld, "DontDeskTalk"); // можно выслать шлюпку
			pchar.GenQuest.Bakaut.Info = "true";
			ReOpenQuestHeader("Bakaut");
			AddQuestRecord("Bakaut", "1");
			AddQuestUserData("Bakaut", "sIsland", XI_ConvertString(pchar.GenQuest.Bakaut.Island+"Gen"));
			AddQuestUserData("Bakaut", "sDays", FindRussianDaysString(sti(pchar.GenQuest.Bakaut.DaysQty)));
			AddQuestUserData("Bakaut", "sQty", FindRussianQtyString(sti(pchar.GenQuest.Bakaut.Value)));
			// таймер
			pchar.quest.Bakaut_Rozencraft_Find.win_condition.l1 = "Timer";
			pchar.quest.Bakaut_Rozencraft_Find.win_condition.l1.date.hour  = sti(GetTime());
			pchar.quest.Bakaut_Rozencraft_Find.win_condition.l1.date.day   = GetAddingDataDay(0, 0, sti(pchar.GenQuest.Bakaut.DaysQty));
			pchar.quest.Bakaut_Rozencraft_Find.win_condition.l1.date.month = GetAddingDataMonth(0, 0, sti(pchar.GenQuest.Bakaut.DaysQty));
			pchar.quest.Bakaut_Rozencraft_Find.win_condition.l1.date.year  = GetAddingDataYear(0, 0, sti(pchar.GenQuest.Bakaut.DaysQty));
			pchar.quest.Bakaut_Rozencraft_Find.function = "Bakaut_RozencraftRemove";
		break;
		// <-- генератор сбыта бакаута
	}
}
