void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, Diag;
	string NPC_Meeting;	
	int Shit, i;
	ref refStore;
	ref sld;
	
	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(Diag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
        case "exit":
			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = NPC_Meeting;
			DialogExit();
		break;

        case "First time":
			Diag.TempNode = "first time";
			if(CheckAttribute(PChar, "quest.Contraband.active"))
			{
				int iTmp = false;
				int iChIdx;

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
					dialog.text = NPCStringReactionRepeat("Тебе что, не говорили, чтобы ты не являл"+ GetSexPhrase("ся","ась") +" на таком приметном корыте? Ты бы еще парочку мановаров с собой прихватил"+ GetSexPhrase("","а") +". Проваливай и приходи на меньшем корабле.", 
						"Ш"+ GetSexPhrase("ел","ла") +" бы ты отсюда. А то сами тебя патрулю сдадим.", 
						"Давай-давай, садись в шлюпку и уматывай.",
						"Как же ты меня утомил"+ GetSexPhrase("","a") +"...", "block", 1, npchar, Dialog.CurrentNode);
					link.l1 = HeroStringReactionRepeat("Хорошо-хорошо, пош"+ GetSexPhrase("ел","ла") +" кораблик менять.", 
						"Не злись, я мигом - одна нога тут, другая там.",
						"Эх-х, не удалось схитрить...", 
						"Да, я настырн"+ GetSexPhrase("ый","ая") +"!", npchar, Dialog.CurrentNode);
						link.l1.go = DialogGoNodeRepeat("exit", "", "", "", npchar, Dialog.CurrentNode);	
					break;
				}
			
				Dialog.snd = "voice\SMSH\SMSH001";
				dialog.Text = RandPhraseSimple("Эй, что ты тут забыл"+ GetSexPhrase("","а") +", "+ GetSexPhrase("приятель","подруга") +"?",
                                          RandSwear() + "Что тебе тут нужно?!");
				Link.l1 = "Расслабься, парень, давай смотреть товар!";
				Pchar.quest.Contraband.Counter = 0; // не торговали
				if(Pchar.Location == Pchar.location.from_sea)
				{
					Link.l1.go = "Exchange";
				}
				else
				{
					Link.l1.go = "No_Ship";
				}
				//по заданию губернатора, истребление контры, только эта ветка.
				if (CheckAttribute(pchar, "GenQuest.KillSmugglers") && pchar.GenQuest.KillSmugglers == "" && pchar.GenQuest.KillSmugglers.Areal == GiveArealByLocation(&locations[FindLocation(pchar.location)]))				
				{
					Link.l2 = "Я здесь по распоряжению губернатора " + XI_ConvertString("Colony"+characters[GetCharacterIndex(pchar.GenQuest.KillSmugglers.MayorId)].city+"Gen") + "! Приказываю вам сложить оружие и следовать за мной - вы арестованы!";
					Link.l2.go = "GenQuestKillContraband_1";
				}
			}
			else
			{
//================ METRO ====================
				//если заплатил, то разговаривают, иначе посылают
				if (CheckAttribute(PChar, "GenQuest.contraTravel.payed") && sti(PChar.GenQuest.contraTravel.payed) == true)
				{
                    dialog.Text = RandPhraseSimple("Ага, наконец-то!!! Вот и ты, а то мы уж заждались совсем. Идем, мы отчаливаем.", "Пошевеливайся, тут повсюду патрули. Нужно быстрее убраться отсюда!");
					//по заданию губернатора, истребление контры, только эта ветка.
					if (CheckAttribute(pchar, "GenQuest.KillSmugglers") && pchar.GenQuest.KillSmugglers == "" && pchar.GenQuest.KillSmugglers.Areal == GiveArealByLocation(&locations[FindLocation(pchar.location)]))
					{
						Link.l1 = "Я здесь по распоряжению губернатора " + XI_ConvertString("Colony"+characters[GetCharacterIndex(pchar.GenQuest.KillSmugglers.MayorId)].city+"Gen") + "! Приказываю вам сложить оружие и следовать за мной - вы арестованы!";
						Link.l1.go = "GenQuestKillContraband_1";
						break;
					}
					//если набрал пассажиров, в сад..
					if (GetPassengersQuantity(PChar) > 0)
					{
						dialog.Text = "А ты кто такой? Мы договаривались доставить одного пассажира, а не толпу.";
						Link.l1 = "Упс...";
						Link.l1.go = "Exit";
						break;
					}
					//если набрал компаньонов или купил корабль себе уже :), в сад..
					if (GetCompanionQuantity(PChar) > 1 || sti(PChar.ship.type) != SHIP_NOTUSED)
					{
						dialog.Text = RandPhraseSimple("Ты кто? Мы договаривались доставить пассажира, а не капитана.", "Проваливай! Пока не избавишься от своего корабля, не приходи.");
						Link.l1 = "Ах, черт...";
						Link.l1.go = "Exit";
						break;
					}
					//типа помог отбиться, свой парень... 
					if (CheckAttribute(PChar, "GenQuest.contraTravel.PatrolFight") && sti(PChar.GenQuest.contraTravel.PatrolFight) == true)
					{
						if (chrDisableReloadToLocation) // еще бой идет
						{
						    dialog.Text = "Патруль! Мы тебя не знаем, ты нас не знаешь.";
							Link.l1 = "Да уж...";
							Link.l1.go = "Exit";
							break;
						}
						dialog.Text = RandPhraseSimple("Спасибо за помощь. Мы не забудем этого. Отправляемся.", "Молодец! Отлично сражал"+ GetSexPhrase("ся","ась") +". Идем.");
						ChangeContrabandRelation(PChar, 5);
						PChar.GenQuest.contraTravel.PatrolFight = false;
						AddCharacterExpToSkill(Pchar, "Sneak", 50);
					}
					//тут все ок, отправляемся.
					Link.l2 = "Уже иду.";
					Link.l2.go = "Exit";
					//а это патруль... 
					if (GetSummonSkillFromNameToOld(Pchar, SKILL_SNEAK) < frandSmall(13.0*(1.0 - pow(0.9, sti(PChar.rank)))) && !CheckAttribute(PChar, "GenQuest.contraTravel.PatrolFight"))
					{
						AddDialogExitQuest("Rand_ContrabandInterruption");
						PChar.GenQuest.contraTravel.PatrolFight = true;
					}
					else 
					{
						//поместим Грея в локацию.
						refStore = CharacterFromID("Abracham_Gray");
						ChangeCharacterAddressGroup(refStore, "Ship_deck", "goto", "goto2");
						refStore.dialog.Filename = "Smuggler_Ship_dialog.c";
                        refStore.dialog.CurrentNode = "Travel_talkStart";
						//поплыл, иначе RemoveTravelSmugglers грохнет всю ветку
						PChar.GenQuest.contraTravel.ship = true;
						PChar.quest.Munity = "";  // признак выхода с палубы
						
						SetLaunchFrameFormParam("Прошло " + sti(Pchar.GenQuest.contraTravel.destination.days) + " дней." + NewStr() + "Палуба корабля контрабандистов.",
						                        "Reload_To_Location", 0.1, 5.0);
                        bQuestCheckProcessFreeze = true;
						WaitDate("", 0, 0, sti(Pchar.GenQuest.contraTravel.destination.days), rand(20), 0);
						bQuestCheckProcessFreeze = false;
						MakeCloneShipDeck(refStore, true); // подмена палубы
						SetLaunchFrameReloadLocationParam("Ship_deck", "reload", "reload1", "Travel_talkOnDeck");
						AddDialogExitQuest("LaunchFrameForm");
						AddCharacterExpToSkill(Pchar, "Sneak", 50);
					}
//================ METRO ====================
				}
				else
				{
                    // если таможня уже бежит
					if (CheckAttribute(NPChar, "ContrabandInterruption"))
					{
					    dialog.Text = RandSwear()+ "Патруль! Мы тебя не знаем, ты нас не знаешь!";
						Link.l1 = "Точно!";
						Link.l1.go = "Exit";
					}
					else
					{
						dialog.Text = "Слушай, проваливай отсюда! Сорвешь сделку - мы выпустим тебе кишки!";
						Link.l1 = RandPhraseSimple("Ты смеешь мне угрожать, собака?", "Ты подавишься своими словами, каналья!");
						Link.l1.go = "Exit_fight";
						Link.l2 = "Да ладно, я знаю, что такое бизнес. До встречи.";
						Link.l2.go = "Exit";
					}
				}
			}
		break;

		case "No_Ship":
			Dialog.snd = "voice\SMSH\SMSH003";
			dialog.Text = "На своем горбу, что ли? Где твой корабль?";
			Link.l1 = RandPhraseSimple("Сначала я хотел"+ GetSexPhrase("","а") +" убедиться, что здесь нет никакого подвоха.", "Не хотел"+ GetSexPhrase("","а") +" рисковать кораблем. Предпочитаю сначала поглядеть на все своими глазами.");
			Link.l1.go = "No_ship_1";
			Link.l2 = "Сделка отменяется!";
			Link.l2.go = "Cancellation";
		break;

		case "No_ship_1":
			Dialog.snd = "voice\SMSH\SMSH004";
			dialog.Text = "Мы люди честные, и обманом не живем. Приводите свой корабль, только аккуратнее - чтобы за вами не увязался береговой патруль.";
			Link.l1 = "Хорошо. Ждите меня здесь.";
			Link.l1.go = "Exit";
		break;

		case "Cancellation":
            if (sti(Pchar.quest.Contraband.Counter) == 0)
            {
    			dialog.Text = "Отменяется? Ты что, смеешься?";
    			Link.l1 = "Совершенно серьезно.";
    			Link.l1.go = "Cancellation_1";
			}
			else
            {
    			dialog.Text = "Ну и ладно. Мы и так неплохо поторговали.";
    			Link.l1 = "Точно!";
    			Link.l1.go = "Finish_exit";
			}
		break;

		case "Cancellation_1":
			if( makeint(Pchar.rank) <= 3 || GetSummonSkillFromNameToOld(Pchar, SKILL_FENCING) <= 5 || GetSummonSkillFromNameToOld(Pchar, SKILL_LEADERSHIP) <= 5 )
			{
				if(Rand(1) == 1)
				{
					ChangeContrabandRelation(pchar, -30);
					Dialog.snd = "voice\SMSH\SMSH006";
					dialog.Text = "Паршив"+ GetSexPhrase("ец","ка") +"! Ты не можешь нас так дурачить! Поплатишься за это своей головой!";
					Link.l1 = "А вот это вряд ли!";
					Link.l1.go = "Exit_fight";			
				}
				else
				{
					ChangeContrabandRelation(pchar, -10);
					Dialog.snd = "voice\SMSH\SMSH007";
					dialog.Text = "Это не сойдет тебе с рук!";
					Link.l1 = "Отправляйтесь гавкать куда-нибудь еще, псы!";
					Link.l1.go = "Exit_cancel";
				}
			}	
			else
			{
				ChangeContrabandRelation(pchar, -10);
				Dialog.snd = "voice\SMSH\SMSH008";
				dialog.Text = "Ты об этом еще пожалеешь!";
				Link.l1 = "Ну-ну!";
				Link.l1.go = "Exit_cancel";			
			}	
		break;

		case "GenQuestKillContraband_1":
			//счетчик подстав по "метро"...
			if(CheckAttribute(PChar, "GenQuest.contraTravel.active") && sti(PChar.GenQuest.contraTravel.active) == true)
			{
				Statistic_AddValue(PChar, "contr_TravelKill", 1);
				ChangeContrabandRelation(pchar, -20); //репу контры вниз
			}
			dialog.Text = "Ты нам сейчас ответишь за такую подставу!";
			Link.l1 = "Тогда вы все умрете. У меня четкий приказ - в случае сопротивления живых не брать!";
			Link.l1.go = "Exit_fight";
		break;
		
		case "Exit_Cancel":
            DeleteAttribute(Pchar, "quest.Contraband");
            CloseQuestHeader("Gen_Contraband");
			Pchar.quest.Rand_Smuggling.over = "yes";
			RemoveSmugglersFromShore();
			RemoveAllContraGoods(CharacterFromId(pchar.GenQuest.Contraband.SmugglerId));
			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = NPC_Meeting;
			DialogExit();
		break;
		
		case "Exit_fight":
            DeleteAttribute(Pchar, "quest.Contraband.active");
			DeleteAttribute(Pchar, "quest.Contraband.counter");			

			AddSimpleRumourCity("Слыхали? Недавно в бухте патруль облаву на контрабандистов устроил. И что бы вы думали? Капитану, который местным скупщикам товар отгружал, удалось уйти! " +
				"Лихие ребята у него в команде оказались - весь патрульный отряд положили. И наши местные, как в воду канули. Так в бухте ничего, кроме трупов, и не нашли - ни товара, ни тайника, ни самих контрабандистов. Вот же как у этих проходимцев промысел-то организован!", Pchar.quest.contraband.City, 3, 5, "");	

			CloseQuestHeader("Gen_Contraband");
			Pchar.quest.Rand_Smuggling.over = "yes";
			LAi_group_FightGroups(LAI_GROUP_PLAYER, pchar.GenQuest.Smugglers_Group, true);
			RemoveSmugglersFromShore();
			RemoveAllContraGoods(CharacterFromId(pchar.GenQuest.Contraband.SmugglerId));
			LAi_SetFightMode(Pchar, true);

			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = NPC_Meeting;
			DialogExit();
		break;

		case "Finish_exit":
            // таможня на суше
            if(GetSummonSkillFromName(pchar, "Sneak") < Rand(120))
			{
				AddDialogExitQuest("Rand_ContrabandInterruption");
				for (i=1; i<=3; i++)
				{
					characters[GetCharacterIndex("Rand_Smug0"+i)].ContrabandInterruption = true;
				}
			}
			AddCharacterExpToSkill(Pchar, "Sneak", 100);
			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = NPC_Meeting;
			DialogExit();
			ChangeContrabandRelation(pchar, 15);
            OfficersReaction("bad");
            ChangeCharacterComplexReputation(pchar,"nobility", -1);
            
            CloseQuestHeader("Gen_Contraband");
            
			DeleteAttribute(Pchar, "quest.Contraband.active");
			DeleteAttribute(Pchar, "quest.Contraband.counter");
	
			Pchar.quest.Rand_Smuggling.over = "yes";
			RemoveSmugglersFromShore();
			RemoveAllContraGoods(CharacterFromId(pchar.GenQuest.Contraband.SmugglerId));
		break;

		case "Exchange":
			// сама торговля -->
            if(FindContrabandGoods(Pchar) == -1 && sti(Pchar.quest.Contraband.Counter) == 0)
            {
				dialog.Text = "Ну, и чего ты здесь делаешь? У тебя же ничего нет, что можно продать! Все, что лежит у тебя в трюме, можно купить в городе!";
				Link.l1 = "Не повезло.";
				Link.l1.go = "NoGoods";
			}
			else
			{
                // установим окружение -->
                if (sti(Pchar.quest.Contraband.Counter) == 0) // не торговали еще
                {
                    if(drand(11) == 3)
                    {
        				dialog.Text = "Так-так... пожалуй, мы заберем твой товар бесплатно. Вряд ли ты побежишь жаловаться властям.";
        				Link.l1 = "Что ж, попробуйте!";
        				Link.l1.go = "Exit_fight";
                        break;
        			}
        			// море и солдаты на суше НЕЗАВИСИМЫ!!!
        			if(GetSummonSkillFromNameToOld(Pchar, SKILL_SNEAK) < Rand(12))
        			{
                        SetCoastalGuardPursuit();
        			}
        			// при убегании от патруля на карту - корабли трем
        			SetTimerCondition("Rand_ContrabandInterruptionAtSeaEnded", 0, 0, 2, false);// если в порту сидим, спим, то 2 день
        			
                    Pchar.quest.Rand_ContrabandAtSeaEnded.win_condition.l1 = "MapEnter";
        			Pchar.quest.Rand_ContrabandAtSeaEnded.win_condition = "Rand_ContrabandAtSeaEnded";
    			}
    			// установим окружение <--
				dialog.text = "Итак, давай посмотрим товары.";										  
				Link.l1 = "Ну давай посмотрим.";
				Link.l1.go = "Exchange1"; 
				if (sti(Pchar.quest.Contraband.Counter) == 0)
    			{
        			Link.l99 = "Пожалуй, я передумал"+ GetSexPhrase("","а") +".";
    				Link.l99.go = "Cancellation";
				}				
            }
		break;
		
		case "Exchange1":
			NPChar.quest.meeting = NPC_Meeting;
			Diag.CurrentNode = Diag.TempNode;		 
			DialogExit();
			
			LaunchContrabandTrade(CharacterFromId(pchar.GenQuest.Contraband.SmugglerId),  sti(pchar.FindContrabandGoods.StoreIdx));	
		break;				
	}
}
