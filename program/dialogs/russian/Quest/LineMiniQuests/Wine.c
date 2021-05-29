void ProcessDialogEvent()
{
	ref sld, NPChar;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "Bug. Let the devs know.";
			link.l1 = "Sure!";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
		case "Wine_fort":
			dialog.text = "So, did you bring the bottle?";
			if (CheckCharacterItem(pchar, "potionwine"))
			{
				link.l1 = "Yes, take it. I paid 700 pesos for it, so I expect 1000 pesos from you.";
				link.l1.go = "Wine_fort_1";
			}
			link.l2 = "No, I am still on it.";
			link.l2.go = "exit";
			NextDiag.TempNode = "Wine_fort";
		break;
	
		case "Wine_fort_1":
			AddMoneyToCharacter(pchar, 1000);
			RemoveItems(PChar, "potionwine", 1);
			dialog.text = "Argh, thank you, pal! Here, take your thousand and this bottle is mine now, ha-ha! Listen, since we are already doing a fine business here, I have another request for you\nCould you get more wine for me and my friends, for future use? We have shaken smugglers pretty hard recently, so we have coins, he-he...";
			link.l1 = "No, pal, I am sorry, I don't have time for this.";
			link.l1.go = "Wine_fort_exit";
			link.l2 = "Hm, interesting. How many bottles do you need?";
			link.l2.go = "Wine_fort_2";
		break;
	
	case "Wine_fort_exit":
			dialog.text = "As you wish. Thanks for your help anyway!";
			link.l1 = "Keep up, soldier!";
			link.l1.go = "exit";
			sld = characterFromId(pchar.questTemp.Wine.id);	
			sld.lifeday = 0;
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload2", "none", "", "", "", -1);
			pchar.questTemp.Wine.fail = "true";
			CloseQuestHeader("Wine");
	break;
	
		case "Wine_fort_2":
			dialog.text = "Well, considering the price of each bottle, we can afford to buy sixty bottles, but not more. But don't bring us less than ten too - it will make no sense.";
			link.l1 = "Fine. You will get your wine.";
			link.l1.go = "Wine_fort_3";
		break;
	
		case "Wine_fort_3":
			dialog.text = "Nice! I am counting on you, captain. Try to bring me the wine no later than in a week cause then we will go to the sea, and I won't be around for a couple of months.";
			link.l1 = "I see. I'll try to be quick.";
			link.l1.go = "exit";
			pchar.questTemp.Wine.bottles = "true";
			npchar.lifeday = 7;
			AddQuestRecord("Wine", "1");
			AddQuestUserData("Wine", "sCity", XI_ConvertString("Colony"+pchar.questTemp.Wine.City+"Gen"));
			AddQuestUserData("Wine", "sName", pchar.questTemp.Wine.SName);
			SetFunctionTimerCondition("Soldier_wait", 0, 0, 7, false);
			NextDiag.TempNode = "Wine_fort_check";
		break;
	
		case "Wine_fort_check":
			dialog.text = "So, captain, have you brought the wine?";
			if (sti(pchar.items.potionwine) >= 10)
			{
				link.l1 = "Yes, I have.";
				link.l1.go = "Wine_take";
			}
			link.l2 = "No. I am still on it.";
			link.l2.go = "exit";
			NextDiag.TempNode = "Wine_fort_check";
		break;
	
		case "Wine_take":
			pchar.questTemp.Wine.Qty = sti(pchar.items.potionwine);
			pchar.questTemp.Wine.Money = sti(pchar.questTemp.Wine.Qty)*1000;
			if (sti(pchar.items.potionwine) > 60)
			{
				dialog.text = "Whoa, so many bottles here! Excellent! Though as I've said, we can afford to buy only sixty bottles, unfortunately we don't have enough money to buy more. Take your coins and I will take care about these sixty bottles.";
				link.l1 = "Take them. I am sure that you will have a good time with your friends!";
				link.l1.go = "Wine_take_1";
				pchar.questTemp.Wine.Money = 60000;
				RemoveItems(PChar, "potionwine", 60);
			}
			else
			{
				dialog.text = "Well, let's see... You have brought "+sti(pchar.questTemp.Wine.Qty)+" bottles. Nice! I'll take them. The payment is " + FindRussianMoneyString(sti(pchar.questTemp.Wine.Money))".";
				link.l1 = "Take your wine. I am sure that you will have a good rest with your friends!";
				link.l1.go = "Wine_take_1";
				RemoveItems(PChar, "potionwine", sti(pchar.questTemp.Wine.Qty));
			}
		break;
	
		case "Wine_take_1":
			AddMoneyToCharacter(pchar, sti(pchar.questTemp.Wine.Money));
			dialog.text = "My gratitude, " + GetAddress_Form(NPChar) + "! And I have to go now. Goodbye!";
			link.l1 = "Goodbye, soldier!";
			link.l1.go = "Wine_take_2";
		break;
	
		case "Wine_take_2":
			DialogExit();
			PlaySound("interface\important_item.wav");
			Log_Info ("You have given the wine");
			pchar.quest.Soldier_wait.over = "yes";//снять прерывание
			DeleteAttribute(pchar, "questTemp.Wine.City");
			sld = characterFromId(pchar.questTemp.Wine.id);
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload2", "none", "", "", "", -1);
			sld.lifeday = 0;
			CloseQuestHeader("Wine");
			AddCharacterExpToSkill(pchar, "Commerce", 150);//торговля
			AddCharacterExpToSkill(pchar, "Leadership", 50);//авторитет
			AddCharacterExpToSkill(pchar, "Fortune", 50);//везение
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
