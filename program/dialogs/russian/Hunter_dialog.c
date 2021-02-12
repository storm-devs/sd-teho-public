void ProcessDialogEvent()
{
	ref NPChar, TempChar, sld;
	aref Link, Diag;
	
	int i, iTemp;
	string sTemp, sTemp1;
	string sGroup;
	
	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(Diag, NPChar.Dialog);

	switch(Dialog.CurrentNode)
	{
		// -----------------------------------Диалог первый - первая встреча
		case "exit":
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
		break;

		case "First time":
			chrDisableReloadToLocation = false;
			//Lai_SetPlayerType(pchar);
			
			dialog.text = GetFullName(PChar) + "! "+"Мы выслеживали тебя долгое время, и вот, наконец, ты у нас в руках.";
			Link.l1 = "Кто вы такие и что вам от меня нужно?";
			Link.l1.go = "meeting"; 
			
			PChar.GenQuest.HunterStart = true;
		break;

		case "meeting":
			dialog.text = XI_ConvertString(Nations[sti(NPChar.nation)].Name) + " заплатила за твою голову хорошую цену, неважно, "+ GetSexPhrase("живым мы тебя доставим или мертвым","живой мы тебя доставим или мертвой") +".";
			Link.l1 = "Я готов"+ GetSexPhrase("","а") +" заплатить вам еще, лишь бы вы оставили меня в покое.";
			Link.l1.go = "Cost_Head"; 
            // boal 08.04.04 -->
            if (GetSummonSkillFromNameToOld(PChar, SKILL_SNEAK) > 2 || bBettaTestMode)
            {
    			TempChar = characterFromID("Bug Fixer");
    			SetRandomNameToCharacter(TempChar);
    			Link.l2 = ""+ GetSexPhrase("Позвольте, но, похоже, вы обознались. Я "+ GetFullName(TempChar) + " - известный в этих краях торговец","Позвольте, но, похоже, вы обознались. Я простая девушка, мой отец - "+ GetFullName(TempChar) + " - известный в этих краях торговец") +".";
    			Link.l2.go = "lier";
			}
            Link.l3 = "Ну что же, испытайте свою удачу.";
			Link.l3.go = "battle";
		break;
        
        case "lier":
            if (GetSummonSkillFromName(pchar, SKILL_SNEAK) > rand(150) || bBettaTestMode)
            {
                dialog.text = "О! Наверно мы ошиблись, простите нас, "+ GetAddress_Form(NPChar) + ".";
                Link.l1 = "Конечно, бывает...";
                Link.l1.go = "lier_2";
                AddCharacterExpToSkill(pchar, SKILL_SNEAK, 100);
            }
            else
            {
                dialog.text = "Похоже, ты врешь!";
                Link.l1 = "Я готов"+ GetSexPhrase("","а") +" заплатить вам еще, лишь бы вы оставили меня в покое.";
			    Link.l1.go = "Cost_Head";
			    Link.l2 = "Ну что же, испытайте свою удачу.";
			    Link.l2.go = "battle";
			    AddCharacterExpToSkill(pchar, SKILL_SNEAK, 50);
            }
            
        break;
        
        case "lier_2":
            AddDialogExitQuest("GoAway_Hunters_Land");
            if (CheckAttribute(PChar, "GenQuest.HunterStart")) // только ОЗГи, а не кладоисатели
            {   // запись в СЖ
	            AddQuestRecord("HeadHunter", "HeadHunter_free");
				AddQuestUserData("HeadHunter", "sSex", GetSexPhrase("ся","ась"));
				AddQuestUserData("HeadHunter", "sNation", NationNameGenitive(sti(NPChar.Nation)));
				AddQuestUserData("HeadHunter", "sLoc", GetLocHunterName());
                DeleteAttribute(PChar, "GenQuest.HunterStart"); 
            }
            DialogExit();
        break;
        // boal <--
        
        case "battle":
            AddDialogExitQuest("Battle_Hunters_Land");    // BOAL Весь код я перенес сюда по всем нациям, просто не переименовал
            if (CheckAttribute(PChar, "GenQuest.HunterStart")) // только ОЗГи, а не кладоисатели
            {   // запись в СЖ
	            AddQuestRecord("HeadHunter", "HeadHunter_battle");
				AddQuestUserData("HeadHunter", "sSex", GetSexPhrase("ся","ась"));
				AddQuestUserData("HeadHunter", "sNation", NationNameGenitive(sti(NPChar.Nation)));
				AddQuestUserData("HeadHunter", "sLoc", GetLocHunterName());
                DeleteAttribute(PChar, "GenQuest.HunterStart"); 
            }
            DialogExit();
        break;

        case "Cost_Head2":
            AddMoneyToCharacter(pchar, -sti(PChar.HunterCost));

            AddDialogExitQuest("GoAway_Hunters_Land"); 
            
            if (CheckAttribute(PChar, "GenQuest.HunterStart")) // только ОЗГи, а не кладоисатели
            {   // запись в СЖ
	            AddQuestRecord("HeadHunter", "HeadHunter_Buy");
				AddQuestUserData("HeadHunter", "sSex", GetSexPhrase("ся","ась"));
				AddQuestUserData("HeadHunter", "sNation", NationNameGenitive(sti(NPChar.Nation)));
				AddQuestUserData("HeadHunter", "sLoc", GetLocHunterName());
                DeleteAttribute(PChar, "GenQuest.HunterStart"); 
            }
            DialogExit();
        break;

        case "Cost_Head":
			dialog.text = "Я думаю, что " + PChar.HunterCost + " песо нас устроит.";
            if(makeint(Pchar.money) < sti(PChar.HunterCost))
            {
                Link.l1 = "У меня нет таких денег.";
                Link.l1.go = "NoMoney";
            }else{
                Link.l1 = "Вот ваши деньги, забирайте и проваливайте.";
                Link.l1.go = "Cost_Head2";
                Link.l2 = "Такую сумму вам, подонкам... Уж лучше я вас всех здесь перережу!!!";
                Link.l2.go = "battle";
            }
		break;

        case "NoMoney":
			dialog.text = "В таком случае разговор окончен!";
			Link.l1 = "Живым вам меня не взять.";
			Link.l1.go = "battle"; 
		break;
		
		case "TreasureHunter":
			dialog.text = "Постой-ка, "+ GetSexPhrase("приятель","подруга") +"... Сдается, у тебя есть кое-что интересное. Нужно делиться с близкими найдеными сокровищами.";
            Link.l1 = "Хорошо, я готов"+ GetSexPhrase("","а") +" заплатить вам, лишь бы вы оставили меня в покое.";
			Link.l1.go = "Cost_Head";
            // boal 08.04.04 -->
            if (GetSummonSkillFromNameToOld(PChar, SKILL_SNEAK) > 3)
            {
    			TempChar = characterFromID("Bug Fixer");
    			SetRandomNameToCharacter(TempChar);
    			Link.l2 = ""+ GetSexPhrase("Позвольте, но, похоже, вы обознались. Я "+ GetFullName(TempChar) + " - известная в этих краях личность, а не искатель сокровищ","Позвольте, но, похоже, вы обознались. Я простая девушка, а не искательница сокровищ! Мой отец - "+ GetFullName(TempChar) + " - известная в этих краях личность") +"!";
    			Link.l2.go = "TreasureHunterLier";
			}
            Link.l3 = "Ну что же, пришло время отделиться вашим головам от тела.";
			Link.l3.go = "battle";
		break;
		
		case "TreasureHunterLier":
            if (GetSummonSkillFromName(pchar, SKILL_SNEAK) > rand(150))
            {
                dialog.text = "О! Наверно мы ошиблись, простите нас, "+ GetAddress_Form(NPChar)+".";
                Link.l1 = "Конечно, бывает...";
                Link.l1.go = "lier_2";
                AddCharacterExpToSkill(pchar, SKILL_SNEAK, 100);
            }
            else
            {
                dialog.text = "Похоже, ты врешь!";
			    Link.l1 = "Тогда послушайте, как поет моя сабля.";
			    Link.l1.go = "battle";
			    AddCharacterExpToSkill(pchar, SKILL_SNEAK, 50);
            }
        break;
		
		case "TreasureCaptain":
			dialog.text = LinkRandPhrase("Вот кто завладел моей картой сокровищ! Придется тебе, приятель, вернуть всё то, что взял...","А! Конкурент! Далеко ты не убежишь, вижу, что ноги твои подгибаются под тяжестью моих сокровищ...","Ха, мы все-таки догнали тебя! Сокровища в этой пещере - мои, тебе ясно? А ну, выворачивай карманы!");
			Link.l1 = LinkRandPhrase("Придется, дружок, познакомить тебя с моей саблей!","Твои сокровища? Может и так. Были твои - стали мои!","Сейчас я охлажу твой пыл, наглец!");
			Link.l1.go = "TreasureCaptain_fight"; 
		break;
		
		case "TreasureCaptain_fight":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешить драться // patch-6
			for(i=1; i<=4; i++)
			{
				sld = characterFromId("Treasure_sailor_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "OpenTheDoors");
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "TreasureOfficer":
			dialog.text = LinkRandPhrase("Значит, полковник был прав - в этой пещере были спрятаны сокровища... Выворачивай карманы, морячок!","Недаром мы пробирались сквозь эти чертовы джунгли среди колючек по твоим следам, каналья! Теперь ты отдашь нам всё...","Эй, морячок! Сокровища этого пирата - наши, так что не смей накладывать на них свои грязные лапы!");
			Link.l1 = LinkRandPhrase("Вот уж не ожидал подобного от офицера регулярных войск! Ну ладно, сейчас я тебя проучу...","Надо же - мундир нацепил, а сам - пират пиратом...","Да, в наше время солдаты мало чем отличаются от пиратов...");
			Link.l1.go = "TreasureOfficer_fight"; 
		break;
		
		case "TreasureOfficer_fight":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешить драться // patch-6
			for(i=1; i<=4; i++)
			{
				sld = characterFromId("Treasure_soldier_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "OpenTheDoors");
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		// генератор "Повод для спешки"
		case "ReasonToFast_THunter_1":
			if(CheckAttribute(pchar,"GenQuest.CannotWait"))	DeleteAttribute(pchar, "GenQuest.CannotWait");
			dialog.text = "А вот и наше золотишко подоспело. Не зря мы тебя караулили.";
			link.l1 = RandPhraseSimple("О чём это вы, джентльмены? Я "+ GetSexPhrase("представитель","представительница") +" Голландской Вест-Индской Кампании и здесь только проездом! "+ GetSexPhrase("Остановился","Остановилась") +" полюбоваться побережьем!","Мне кажется, что вы меня с кем-то путаете. Я "+ GetSexPhrase("натуралист Жак Франсуа Паганель","натуралистка Мария-Тереза") +" и собираю образцы местной флоры. Не хотите взглянуть на мою коллекцию листьев юкки? Здесь встречаются любопытнейшие образцы!");
			link.l1.go = "ReasonToFast_THunter_2";
			link.l2 = "Чего вам надо?! Убирайтесь с дороги!";
			link.l2.go = "ReasonToFast_THunter_2";
		break;
		
		case "ReasonToFast_THunter_2":
			ReasonToFast_ClearTreasureBox(pchar.questTemp.ReasonToFast.Treasure.Location);
			dialog.text = "Э нет, " + GetSexPhrase("господин хороший","милочка") + ". Так дело не пойдёт... Мы точно знаем, что карта " + GetName( pchar.questTemp.ReasonToFast.mapIdx, pchar.questTemp.ReasonToFast.map, NAME_GEN) +" досталась тебе. А он был изрядным скрягой, и его сундуки ломились от деньжищ. Поэтому с пустыми руками мы не уйдём.";
			link.l1 = "Вы правы. Сундуки были полны. Только вам они не достанутся. Можете сходить в пещеру, там ещё осталась пара дырявых вёдер.";
			link.l1.go = "ReasonToFast_THunter_3";
			if(ReasonToFast_CheckTreasureQty("icollection", sti(pchar.questTemp.ReasonToFast.p8)) >= sti(pchar.questTemp.ReasonToFast.p8) 
				&& ReasonToFast_CheckTreasureQty("Chest", sti(pchar.questTemp.ReasonToFast.p7)) >= sti(pchar.questTemp.ReasonToFast.p7))
			{
				link.l2 = "Вы правы, забирайте ваши сокровища. Но счастья они вам не принесут, - на них слишком много крови...";
				link.l2.go = "ReasonToFast_THunter_4";
			}	
		break;
		
		case "ReasonToFast_THunter_3":
			dialog.text = ""+ GetSexPhrase("Эх, капитан. Такой молодой, тебе бы ещё жить и жить","Эх, девчонка. Такая молодая, тебе бы ещё жить и жить") +"...";
			link.l1 = "А я и не собираюсь умирать!";
			link.l1.go = "ReasonToFastTHunter_Fight";
		break;
		
		case "ReasonToFast_THunter_4":
			dialog.text = "Вот это разумные слова здравомыслящего человека!";
			link.l1 = "Будьте вы прокляты вместе с этими сокровищами...";
			link.l1.go = "ReasonToFast_THunter_GoAway";
		break;
		
		case "ReasonToFast_THunter_GoAway":			
			iTemp = ReasonToFast_CheckTreasureQty("icollection", sti(pchar.questTemp.ReasonToFast.p8));
			if(iTemp > 0) 
			{
				ReasonToFast_GetTreasure("icollection", iTemp );
				Log_Info(XI_ConvertString("You give item"));
				PlayStereoSound("interface\important_item.wav");
			}	
			
			iTemp = ReasonToFast_CheckTreasureQty("Chest", sti(pchar.questTemp.ReasonToFast.p7));
			if(iTemp > 0) 
			{
				ReasonToFast_GetTreasure("Chest", iTemp);
				Log_Info(XI_ConvertString("You give item"));
				PlayStereoSound("interface\important_item.wav");
			}	
			if(pchar.questTemp.ReasonToFast == "GetTreasure")
			{
				AddQuestRecord("ReasonToFast", "24");
				AddQuestUserData("ReasonToFast", "sName", GetName( pchar.questTemp.ReasonToFast.mapIdx, pchar.questTemp.ReasonToFast.map, NAME_GEN));
				CloseQuestHeader("ReasonToFast");	
			}
			DialogExit();	
			AddDialogExitQuest("ReasonToFast_GoAway_Hunters_Land");
		break;
		
		case "ReasonToFastTHunter_Fight":
			sGroup = "LAND_HUNTER";
			sTemp = "LandHunter0";
			iTemp = sti(pchar.HunterCost.Qty);
			chrDisableReloadToLocation = true;
			LAi_SetPlayerType(pchar);
			LAi_SetFightMode(pchar, true);
			for(i = 1; i <= iTemp; i++)
			{
				sld = CharacterFromID(sTemp + i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, sGroup);
			}
			
			LAi_group_SetRelation(sGroup, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups(sGroup, LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck(sGroup, "OpenTheDoors"); 
			LAi_group_SetCheck(sGroup, "ReasonToFast_TrHuntersDied");	
			DialogExit();	
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
		case "ReasonToFast_HunterShore1":
			dialog.text = "Эй, "+ GetSexPhrase("приятель","подруга") +"! " + GetName( NAMETYPE_MAIN, pchar.questTemp.ReasonToFast.p3, NAME_NOM) + " сказал, что у тебя есть кое-что для нас.";
			link.l1 = "Что вы имеете в виду?";
			link.l1.go = "ReasonToFast_HunterShore11";
			pchar.quest.ReasonToFast_SetHunterPort_1.over = "yes";
			pchar.quest.ReasonToFast_SetHunterPort_2.over = "yes";
		break;

		case "ReasonToFast_HunterShore11":
			if(pchar.questTemp.ReasonToFast == "GetMap") 
			{
				dialog.text = "Карта " + GetName( pchar.questTemp.ReasonToFast.mapIdx, pchar.questTemp.ReasonToFast.map, NAME_GEN);
				link.l1 = "Забирайте и передайте " + GetName( NAMETYPE_MAIN, pchar.questTemp.ReasonToFast.p3, NAME_DAT) + " привет. Скажите, что скоро встретимся...";
				link.l1.go = "ReasonToFast_HunterShore12_1";
				link.l2 = GetName( NAMETYPE_MAIN, pchar.questTemp.ReasonToFast.p3, NAME_NOM) + " очень ошибается, если думает, что я буду таскать для него каштаны из огня.";
				link.l2.go = "ReasonToFast_HunterShore23";
			}
			if(pchar.questTemp.ReasonToFast == "LakeyExitSuccess")
			{
				dialog.text = "Цацки, что ты стащил" + GetSexPhrase("","а") + " у губернатора.";
				if(ReasonToFast_CheckTreasureQty("icollection", sti(pchar.questTemp.ReasonToFast.p8)) >= sti(pchar.questTemp.ReasonToFast.p8) 
					&& ReasonToFast_CheckTreasureQty("Chest", sti(pchar.questTemp.ReasonToFast.p7)) >= sti(pchar.questTemp.ReasonToFast.p7))
				{
					link.l1 = "Забирайте и передайте " + GetName( NAMETYPE_MAIN, pchar.questTemp.ReasonToFast.p3, NAME_DAT) + " привет. Скажите, что скоро встретимся...";
					link.l1.go = "ReasonToFast_HunterShore12_2";
				}	
				link.l2 = GetName( NAMETYPE_MAIN, pchar.questTemp.ReasonToFast.p3, NAME_NOM) + " очень ошибается, если думает, что я буду таскать для него каштаны из огня.";
				link.l2.go = "ReasonToFast_HunterShore23";				
			}
			pchar.quest.ReasonToFast_SetHunterPort_1.over = "yes";
			pchar.quest.ReasonToFast_SetHunterPort_2.over = "yes";
			chrDisableReloadToLocation = false;
		break;
		
		case "ReasonToFast_HunterShore12_1":
			TakeNItems(pchar, "mapQuest", -1); 
			AddQuestRecord("ReasonToFast", "20");
			AddQuestUserData("ReasonToFast", "sText", "карту");
			AddQuestUserData("ReasonToFast", "sName", GetName( NAMETYPE_MAIN, pchar.questTemp.ReasonToFast.p3, NAME_GEN));
			CloseQuestHeader("ReasonToFast");
			DialogExit();	
			AddDialogExitQuest("ReasonToFast_GoAway_Hunters_Land");
		break;
		
		case "ReasonToFast_HunterShore12_2":
			iTemp = ReasonToFast_CheckTreasureQty("icollection", sti(pchar.questTemp.ReasonToFast.p8));
			if(iTemp > 0) 
			{
				ReasonToFast_GetTreasure("icollection", iTemp );
				Log_Info(XI_ConvertString("You give item"));
				PlayStereoSound("interface\important_item.wav");
			}	
			
			iTemp = ReasonToFast_CheckTreasureQty("Chest", sti(pchar.questTemp.ReasonToFast.p7));
			if(iTemp > 0) 
			{
				ReasonToFast_GetTreasure("Chest", iTemp);
				Log_Info(XI_ConvertString("You give item"));
				PlayStereoSound("interface\important_item.wav");
			}			
			AddQuestRecord("ReasonToFast", "20");
			AddQuestUserData("ReasonToFast", "sText", "ценности");
			AddQuestUserData("ReasonToFast", "sName", GetName( NAMETYPE_MAIN, pchar.questTemp.ReasonToFast.p3, NAME_GEN));
			CloseQuestHeader("ReasonToFast");
			DialogExit();	
			ReasonToFast_ClearTreasureBox(pchar.questTemp.ReasonToFast.city + "_townhall");
			ReasonToFast_ClearTreasureBox(pchar.questTemp.ReasonToFast.LakeyLocation);
			AddDialogExitQuest("ReasonToFast_GoAway_Hunters_Land");
		break;
		
		case "ReasonToFast_HunterShore2":
			dialog.text = "Эй, "+ GetSexPhrase("приятель","подруга") +"! У " + GetName( NAMETYPE_MAIN, pchar.questTemp.ReasonToFast.p3, NAME_GEN) + " есть к тебе пара вопросов.";
			link.l1 = "А чего же он сам их не задаст?";
			link.l1.go = "ReasonToFast_HunterShore21";
			chrDisableReloadToLocation = false;
		break;
		
		case "ReasonToFast_HunterShore21":
			dialog.text = "Не по чину... Ты сорвал"+ GetSexPhrase("","а") +" операцию, из-за чего мы лишились " + sti(pchar.questTemp.ReasonToFast.p10) + " песо. Так что с тебя должок.";
			link.l1 = "Забирайте и передайте " + GetName( NAMETYPE_MAIN, pchar.questTemp.ReasonToFast.p3, NAME_DAT) + " привет. Скажите, что скоро встретимся...";
			link.l1.go = "ReasonToFast_HunterShore22";
			link.l2 = GetName( NAMETYPE_MAIN, pchar.questTemp.ReasonToFast.p3, NAME_NOM) + " очень ошибается, если думает, что я буду таскать для него каштаны из огня.";
			link.l2.go = "ReasonToFast_HunterShore23";
		break;
		
		case "ReasonToFast_HunterShore22":
			if(makeint(pchar.money) >= sti(pchar.questTemp.ReasonToFast.p10))
			{
				AddMoneyToCharacter(pchar, -makeint(sti(pchar.questTemp.ReasonToFast.p10)));
				AddQuestRecord("ReasonToFast", "20");
				AddQuestUserData("ReasonToFast", "sText", "деньги");
				AddQuestUserData("ReasonToFast", "sName", GetName( NAMETYPE_MAIN, pchar.questTemp.ReasonToFast.p3, NAME_GEN));
				DialogExit();	
				AddDialogExitQuest("ReasonToFast_GoAway_Hunters_Land");
			}
			else
			{
				dialog.text = "У тебя нет таких денег! Ну что ж, ты свой выбор сделал"+ GetSexPhrase("","а") +"... ";
				link.l1 = "Давно...";
				link.l1.go = "ReasonToFastTHunter_Fight";	
				if(pchar.questTemp.ReasonToFast == "LakeyExitSuccess" || pchar.questTemp.ReasonToFast == "LakeyExitFail")
				{
					pchar.quest.ReasonToFast_SetPirateShip.win_condition.l1 = "MapEnter";
					pchar.quest.ReasonToFast_SetPirateShip.function = "ReasonToFast_PreparePirateShip";
				}
			}
		break;
		
		case "ReasonToFast_HunterShore23":
			dialog.text = "Ну что ж, ты свой выбор сделал"+ GetSexPhrase("","а") +"...";
			link.l1 = "Давно...";
			link.l1.go = "ReasonToFastTHunter_Fight";
			if(pchar.questTemp.ReasonToFast == "LakeyExitSuccess" || pchar.questTemp.ReasonToFast == "LakeyExitFail")
			{
				pchar.quest.ReasonToFast_SetPirateShip.win_condition.l1 = "MapEnter";
				pchar.quest.ReasonToFast_SetPirateShip.function = "ReasonToFast_PreparePirateShip";
			}
		break;
		// генератор "Повод для спешки"
	}
}

string GetLocHunterName()
{
	int nLoc = FindLocation(Pchar.location);
	int nFile = LanguageOpenFile("LocLables.txt");
	string ret = "";
	
	if(nFile >= 0) 
	{
		if (CheckAttribute(&locations[nLoc],"islandId"))
		{
			if (locations[nLoc].islandId != "Mein")
			{
				ret = "острова " + LanguageConvertString(nFile, locations[nLoc].islandId);
			}
			else
			{
				ret = "материка";
			}
		}
		//
        if (CheckAttribute(&locations[nLoc],"fastreload"))
		{
			ret += " (" +LanguageConvertString(nFile, locations[nLoc].fastreload + " Town") + ")";
		}
		//ret += LanguageConvertString(nFile, locations[nLoc].id.label);
		LanguageCloseFile( nFile );
	}
	return ret;	
}