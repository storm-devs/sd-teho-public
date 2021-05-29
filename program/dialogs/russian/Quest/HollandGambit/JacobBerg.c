// Якоб ван Берг - злодей и пират, капитан Миража
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (CheckAttribute(pchar, "questTemp.HWIC.Holl") && pchar.questTemp.HWIC.Holl == "JacobInRoom")
			{
				dialog.text = "Аргх! И-ик... Ты кто такой? Где этот чертов китаец? Я тебя спрашиваю, ты что, оглох? И-ик!";
				link.l1 = "Я тебя прекрасно слышу, не ори. Китайца не будет. Я за него.";
				link.l1.go = "HollJacob_inRoom";
				break;
			}
			dialog.text = "Явный баг. Сообщите об этом Jason'у, как и при каких обстоятельствах его получили.";
			link.l1 = "Обязательно сообщу!";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "HollJacob_inRoom":
			dialog.text = "Что? А ты вообще кто такой? Какого черта ты делаешь здесь? Я тебя спрашиваю, каналья!";
			link.l1 = "Тебе этого знать не нужно. Мне нужен твой корабль.";
			link.l1.go = "HollJacob_inRoom_1";			
		break;
		
		case "HollJacob_inRoom_1":
			dialog.text = "Аргх... Вот это наглость! Или... постой! Ты - проклятая английская ищейка! Дьявол! Выследили, значит... Ну, так просто я не дамся!";
			link.l1 = "Ну, раз ты так спешишь...";
			link.l1.go = "HollJacob_inRoom_fight";			
		break;
		
		case "HollJacob_inRoom_fight":
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.questTemp.HWIC.Holl.JacobCity+"_tavern_upstairs")], false);
			pchar.quest.JacobOnMainOver.over = "yes";//снять таймер
			chrDisableReloadToLocation = true;
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
            LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
            LAi_group_SetCheck("EnemyFight", "HollJacob_dead");
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
		case "JacobBerg_abordage":
			if (CheckAttribute(pchar, "questTemp.HWIC.Eng"))
			{
				dialog.text = "Аргх! Проклятие! Как я мог так глупо вляпаться! Ты ведь не торговец, верно?";
				link.l1 = "Верно, мразь. Думаю, ты это уже понял по моей команде из отборных английских морпехов. Мы с Ричардом Флитвудом придумали историю с торговцем, а ты и повелся. Твои похождения окончены, негодяй!";
				link.l1.go = "JacobBerg_abordage_1";
			}
			else
			{
				dialog.text = "Ну вот и встретились, капитан. А ты ловкий малый... Давненько мне не попадался такой серьезный противник.";
				link.l1 = "Я твой последний противник, Якоб. Отсюда ты живым не уйдешь.";
				link.l1.go = "JacobBerg_abordage_3";
			}
		break;
		
		case "JacobBerg_abordage_1":
			dialog.text = "Похоже, что так. Твоя команда захватила мой корабль, и пощады ждать не приходится. Но прежде чем сюда придут к тебе на помощь, я успею отправить тебя в ад! Ван Берг дорого продаст свою шкуру!";
			link.l1 = "Это ты так думаешь. А я считаю, что твоя шкура уже не стоит и пенни. Довольно слов, к бою!";
			link.l1.go = "JacobBerg_abordage_2";			
		break;
		
		case "JacobBerg_abordage_2":
			LAi_SetCurHPMax(NPChar);
			LAi_GetCharacterMaxEnergy(NPChar);			
			QuestAboardCabinDialogExitWithBattle(""); 
			DialogExit();	
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "JacobBerg_abordage_3":
			dialog.text = "Да ну? Вот ты не уйдешь точно. Я поджег шнур, ведущий в крюйт-камеру. Так что скоро обе лоханки - и твоя, и моя, взлетят на воздух.";
			link.l1 = "Я думаю, что полетишь ты один вместе со своим корытом. Я сейчас тебя прикончу, освобожу свой корабль, и отойду в сторонку, а потом понаблюдаю за фейерверком.";
			link.l1.go = "JacobBerg_abordage_4";			
		break;
		
		case "JacobBerg_abordage_4":
			dialog.text = "А я думаю, что прикончу тебя, успею выпрыгнуть в окно и доплыть до берега, и посмотрю, как эти два чертовых корабля разлетятся на куски!";
			link.l1 = "Разрешим наш спор?";
			link.l1.go = "JacobBerg_abordage_5";			
		break;
		
		case "JacobBerg_abordage_5":
			LAi_SetCurHPMax(NPChar);
			LAi_GetCharacterMaxEnergy(NPChar);			
			QuestAboardCabinDialogExitWithBattle("PrepareToBoom2"); 
			DialogExit();	
			AddDialogExitQuest("MainHeroFightModeOn");
			pchar.GenQuest.Detonation = true; // patch-4
		break;
}
}