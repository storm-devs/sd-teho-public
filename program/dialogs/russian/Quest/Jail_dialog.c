void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;
	string sTemp;
	
	DeleteAttribute(&Dialog,"Links");
	
	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	switch(Dialog.CurrentNode)
	{
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
        case "First time":
			dialog.text = "";
			link.l1 = "";
			link.l1.go = "";
		break;
		
		case "Jail_officer_take":
		//--> Сомнительное предложение
		if (CheckAttribute(pchar, "GenQuest.Contraoffer.Jail"))
		{
			dialog.text = "Вы задержаны с поличным при попытке провезти и сбыть контрабанду. Поскольку вы пошли следствию навстречу, и учитывая ваше положение в обществе, вы проведёте в тюрьме всего лишь "+FindRussianDaysString(sti(pchar.questTemp.JailTemp2))+". Кроме того, все деньги от сделки с контрабандным товаром - "+FindRussianMoneyString(sti(pchar.questTemp.JailTemp1))+" изымаются и поступают в городскую казну. Приятного времяпровождения, капитан! Хе-хе!";
			link.l1 = "";
			link.l1.go = "Jail_officer_take_1";
			DeleteAttribute(pchar, "GenQuest.Contraoffer.Jail");
			NextDiag.currentnode = "Jail_officer_free";
			break;
		}
		//<-- Сомнительное предложение
			dialog.text = "Вы задержаны за совершение преступления и проведёте в тюрьме "+FindRussianDaysString(sti(pchar.questTemp.JailTemp2))+". Кроме того, вы будете оштрафованы на "+FindRussianMoneyString(sti(pchar.questTemp.JailTemp1))+". Приятного времяпровождения, хе-хе!";
			link.l1 = "";
			link.l1.go = "Jail_officer_take_1";
			NextDiag.currentnode = "Jail_officer_free";
		break;
		
		case "Jail_officer_take_1":
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", 10);
			DialogExit();
			DoQuestFunctionDelay("InPrison", 10.0);
		break;
		
		case "Jail_officer_free":
			dialog.text = "Ну что же, срок вашего заключения истёк. Надеюсь, это послужит вам уроком. Вы свободны. Свои вещи заберёте в сундуке на столе у дежурного. И не попадайтесь больше!";
			link.l1 = "";
			link.l1.go = "Jail_officer_free_1";
		break;
		
		case "Jail_officer_free_1":
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", 5);
			DialogExit();
			DoQuestFunctionDelay("GoFromPrison", 5.0);
		break;
	}
} 
