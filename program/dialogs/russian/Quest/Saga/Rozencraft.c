// Михаэль Розенкрафт - голландский капитан, квестовый покупатель бакаута
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int iTemp;
	string sTemp;
	
	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "Want something?";
			link.l1 = "No, it's nothing.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		case "rozencraft":
			if (pchar.questTemp.Saga.Oyster == "cantalk")
			{
				dialog.text = "Hm... And where is Molligan? Wasn't he pleased to come and see me himself?";
				link.l1 = "Our poor Paul has a fever. He is not in a mood to trade. I am instead of him.";
				link.l1.go = "rozencraft_1";
			}
			else
			{
				dialog.text = "What do you want, mister?";
				link.l1 = "I take it that you are waiting ironwood to buy?";
				link.l1.go = "rozencraft_no";
			}
		break;
		
		case "rozencraft_no":
			dialog.text = "Who told you that bullshit, mister? I am not waiting anyone or anything. My vessel is patrolling local area by the order of Willemstad governor. So would you be kindly to leave my ship, you must be mistaken.";
			link.l1 = "Hm... I see. I am sorry for troubling you.";
			link.l1.go = "rozencraft_no_1";
		break;
		
		case "rozencraft_no_1":
			DialogExit();
			AddQuestRecord("Testament", "8");
			NextDiag.CurrentNode = "rozencraft_no_repeat";
		break;
		
		case "rozencraft_no_repeat":
			dialog.text = "Haven't we had a talk already, mister?";
			link.l1 = "Yes, yes. I am leaving to my ship already.";
			link.l1.go = "exit";
			NextDiag.TempNode = "rozencraft_no_repeat";
		break;
		
		case "rozencraft_1":
			dialog.text = "And who are you?";
			link.l1 = "Don't you care who to trade with? I have brought ironwood to sell. How much?";
			link.l1.go = "rozencraft_2";
		break;
		
		case "rozencraft_2":
			dialog.text = "According to the agreement - forty doubloons per a piece.";
			link.l1 = "Hm...";
			link.l1.go = "rozencraft_3";
		break;
		
		case "rozencraft_3":
			npchar.quest.bakaut = GetSquadronGoods(pchar, GOOD_SANDAL);
			dialog.text = "Pal, we had a deal with Molligan. This is a good price, you won't find better. So don't behave like a farmer in the shop. How much ironwood do you have?";
			link.l1 = ""+FindRussianQtyString(sti(npchar.quest.bakaut))+".";
			link.l1.go = "rozencraft_4";
		break;
		
		case "rozencraft_4":
			iTemp = sti(npchar.quest.bakaut);
			if(iTemp >= 90)
			{
				dialog.text = "Splendid. It is more than I have expected. Here, take the gold. If you'll get more ironwood then come at Saint-Martin's tavern and talk to... you know who. He will set a meeting for us. I see that you are a much better partner than that idiot Molligan.";
				link.l1 = "Fine. Consider we had a deal.";
				link.l1.go = "rozencraft_5";
				pchar.GenQuest.Bakaut = "true"; // генератор сбыта бакаута
				break;
			}
			if(iTemp >= 70 && iTemp < 90)
			{
				dialog.text = "Good. Here, take the gold. If you'll get more ironwood then come at Philipsburg's tavern and talk with... you know who. He will contact you with me. I see that we can do business with you, not worse than with that idiot Molligan.";
				link.l1 = "Fine. Consider we had a deal.";
				link.l1.go = "rozencraft_5";
				pchar.GenQuest.Bakaut = "true"; // генератор сбыта бакаута
				break;
			}
			if(iTemp >= 40 && iTemp < 70)
			{
				dialog.text = "Hm... I was expecting for more. Fine. Here, take the gold. And tell Molligan that next time he must bring a batch not less than a one hundred pieces.";
				link.l1 = "Fine. I will tell him.";
				link.l1.go = "rozencraft_5";
				break;
			}
			dialog.text = "Are you kidding me? We had a deal with Molligan, the batch must not be less than fifty pieces! Get lost and don't return back until you'll have enough.";
			link.l1 = "Fine, fine, calm down.";
			link.l1.go = "rozencraft_5";
		break;
		
		case "rozencraft_5":
			DialogExit();
			npchar.DontDeskTalk = true; // чтоб не доставал, в генераторе - снимаем
			iTemp = sti(npchar.quest.bakaut);
			if (iTemp < 40) DeleteAttribute(npchar, "quest.bakaut");
			else 
			{
				TakeNItems(pchar, "gold_dublon", iTemp*40);
				RemoveCharacterGoods(pchar, GOOD_SANDAL, iTemp);
				// считаем, сколько мы должны Свенсону
				int ibak = makeint((iTemp*40-1500)/2);
				sld = characterFromId("Svenson");
				sld.quest.bakaut_sum = ibak; // доля Яна
				AddQuestRecord("Testament", "9");
				AddQuestUserData("Testament", "sSum", iTemp*40);
				AddQuestUserData("Testament", "sSum1", ibak);
				if (CheckAttribute(pchar, "GenQuest.Bakaut")) AddQuestUserData("Testament", "sText", "In addition, if I get an ironwood, I will be able to sell it to Michael Rosencraft by having arranged with his man at Philipsburg's tavern.");
				pchar.questTemp.Saga = "removebakaut";
				// корабль Розенкрафта сохраняем, в АИ на него будет стоять проверка на попадание
				pchar.quest.Saga_Rozencraft_GetOut.over = "yes"; //снять прерывание
				pchar.quest.Saga_Rozencraft_AfterBattle.over = "yes"; //снять прерывание
				// ставим новое прерывание на потопление Розенкрафта
				pchar.quest.Bakaut_Rozencraft_Die.win_condition.l1 = "Group_Death";
				pchar.quest.Bakaut_Rozencraft_Die.win_condition.l1.group = "Rozencraft_Group";
				pchar.quest.Bakaut_Rozencraft_Die.function = "Bakaut_RozencraftDie";
				pchar.quest.Bakaut_Rozencraft_Remove.win_condition.l1 = "MapEnter";
				pchar.quest.Bakaut_Rozencraft_Remove.function = "Bakaut_RozencraftRemove";
			}
			NextDiag.CurrentNode = "rozencraft_no_repeat";
		break;
		
	// ------------------------------------генератор сбыта бакаута-----------------------------------------------
		case "bakaut":
			dialog.text = "Oh, my old friend! Got some ironwood to sell?";
			link.l1 = "Exactly, Michael. Let's trade.";
			link.l1.go = "bakaut_0";
		break;
		
		case "bakaut_0":
			dialog.text = "How much do you have? I need a batch not less than "+FindRussianQtyString(sti(pchar.GenQuest.Bakaut.Value))+".";
			if (GetSquadronGoods(pchar, GOOD_SANDAL) >= sti(pchar.GenQuest.Bakaut.Value))
			{
				link.l1 = "I know that. I have got "+FindRussianQtyString(GetSquadronGoods(pchar, GOOD_SANDAL))+"  of ironwood which you are so eager to get.";
				link.l1.go = "bakaut_1";
			}
			else
			{
				link.l1 = "Hm. Unfortunately I don't have that much.";
				link.l1.go = "bakaut_no";
			}
		break;
		
		case "bakaut_no":
			if (!CheckAttribute(npchar, "quest.bakaut_angry"))
			{
				dialog.text = "Damn it, didn't they warn you? Or have the rats eaten the wood? I need "+FindRussianQtyString(sti(pchar.GenQuest.Bakaut.Value))+" and not a single piece less. Bring next time as much wood as my agent will tell you. I do hope that you won't disappoint me again or I will have to decline your services.";
				link.l1 = "Fine, mynheer, I will be more attentive in future.";
				link.l1.go = "bakaut_no_1";
			}
			else
			{
				if (sti(npchar.quest.bakaut_angry) == 1)
				{
					dialog.text = "Your are screwing me for the second time. I don't like it. Know that it was the last warning, next time I will decline your services.";
					link.l1 = "Damn rats damaged my goods! I promise you, Michael, that it was the last time.";
					link.l1.go = "bakaut_no_1";
				}
				else
				{
					dialog.text = "And now my patience is done! I don't want to do business with you anymore. You can get lost now and forget about me.";
					link.l1 = "But mynheer...";
					link.l1.go = "bakaut_no_2";
				}
			}
			npchar.DontDeskTalk = true;
			pchar.quest.Bakaut_Rozencraft_Find.over = "yes"; //снять прерывание
		break;
		
		case "bakaut_no_1":
			DialogExit();
			NextDiag.CurrentNode = "rozencraft_no_repeat";
			if (!CheckAttribute(npchar, "quest.bakaut_angry")) npchar.quest.bakaut_angry = 1;
			else npchar.quest.bakaut_angry = sti(npchar.quest.bakaut_angry)+1;
			pchar.quest.Bakaut_Rozencraft_Reset.win_condition.l1 = "MapEnter";
			pchar.quest.Bakaut_Rozencraft_Reset.function = "Bakaut_RozencraftRemove";
			AddQuestRecord("Bakaut", "3");
			CloseQuestHeader("Bakaut");
		break;
		
		case "bakaut_no_2":
			DialogExit();
			NextDiag.CurrentNode = "rozencraft_no_repeat";
			pchar.quest.Bakaut_Rozencraft_Fail.win_condition.l1 = "MapEnter";
			pchar.quest.Bakaut_Rozencraft_Fail.function = "Bakaut_RozencraftDie";
			AddQuestRecord("Bakaut", "4");
			CloseQuestHeader("Bakaut");
		break;
		
		case "bakaut_1":
			iTemp = GetSquadronGoods(pchar, GOOD_SANDAL);
			if (iTemp > sti(pchar.GenQuest.Bakaut.Value)+20)
			{ // перебор
				dialog.text = "Wow! I am sorry, friend, but I can buy only "+FindRussianQtyString(sti(pchar.GenQuest.Bakaut.Value)+20)+"  , I don't have money for all of the cargo. I was expecting for a batch of "+FindRussianQtyString(sti(pchar.GenQuest.Bakaut.Value))+" pieces per forty doubloons each...";
				link.l1 = "Fine. Take "+FindRussianQtyString(sti(pchar.GenQuest.Bakaut.Value)+20)+" now and the rest I will sell you next time.";
				link.l1.go = "bakaut_2";
				npchar.quest.bakaut = sti(pchar.GenQuest.Bakaut.Value)+20;
			}
			else
			{
				dialog.text = "Very well. The price is usual, forty doubloons per an each piece.";
				link.l1 = "Works for me. Take your batch.";
				link.l1.go = "bakaut_2";
				npchar.quest.bakaut = iTemp;
			}
		break;
		
		case "bakaut_2":
			LAi_Fade("", "");
			WaitDate("",0,0,0,1,10);
			dialog.text = "Pleasure doing business with you. Come and see me again if you want to sell more ironwood.";
			link.l1 = "See you again, mister. Our collaboration is very profitable for me. Good bye!";
			link.l1.go = "bakaut_3";
		break;
		
		case "bakaut_3":
			DialogExit();
			iTemp = sti(npchar.quest.bakaut);
			TakeNItems(pchar, "gold_dublon", iTemp*40);
			RemoveCharacterGoods(pchar, GOOD_SANDAL, iTemp);
			npchar.DontDeskTalk = true;
			pchar.quest.Bakaut_Rozencraft_Find.over = "yes"; //снять прерывание
			pchar.quest.Bakaut_Rozencraft_Reset.win_condition.l1 = "MapEnter";
			pchar.quest.Bakaut_Rozencraft_Reset.function = "Bakaut_RozencraftRemove";
			NextDiag.CurrentNode = "rozencraft_no_repeat";
			AddQuestRecord("Bakaut", "2");
			AddQuestUserData("Bakaut", "sQty", iTemp);
			AddQuestUserData("Bakaut", "sDublon", iTemp*40);
			AddQuestUserData("Bakaut", "sDublon1", iTemp*40-iTemp*30);
			CloseQuestHeader("Bakaut");
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
	}
}