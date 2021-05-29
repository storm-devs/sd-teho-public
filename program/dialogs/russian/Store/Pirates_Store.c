// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
	bool bOk;
	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat("Go ahead, what do you want?",
                          "We were just talking about that. You must have forgotten...", "This is the third time today you're talking about some question...",
                          "Listen, this is a store. People buy stuff here. Don't disturb me!", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("You know, " + NPChar.name + ", maybe next time.", "Right, I've forgotten for some reason...",
                      "Yes, it really is the third time...", "Hm, I wont...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			if(CheckAttribute(pchar, "questTemp.Tieyasal") && pchar.questTemp.Tieyasal == "begin" && !CheckAttribute(npchar, "quest.Tieyasal"))
			{
				link.l1 = "Listen, "+npchar.name+", have you seen Miguel Dichoso on Isla Tesoro lately?";
				link.l1.go = "tieyasal";
			}
			// Addon 2016-1 Jason пиратскаЯ линейка
			if(CheckAttribute(pchar, "questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "pasq_start")
			{
				link.l1 = ""+npchar.name+", I am here on behalf of Marcus Tyrex. He said that you needed a man for a job.";
				link.l1.go = "mtraxx";
			}
			if(CheckAttribute(pchar, "questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "pasq_win")
			{
				link.l1 = ""+npchar.name+", the 'Rosbohom' was found and captured. Should we start unloading and counting?";
				link.l1.go = "mtraxx_5";
			}
		break;
				
		// город майя
		case "tieyasal":
			dialog.text = "Yes, I have. He bought supplies for his ship here. It has been very recently by the way. You literally missed each other by a few days. By the way, he might still be in this settlement. I don't spy for people, you know. Ask around some more and who knows you just might find your don.";
			link.l1 = "All right. Thanks for the info!";
			link.l1.go = "tieyasal_1";
		break;
		
		case "tieyasal_1":
			DialogExit();
			npchar.quest.tieyasal = "true";
		break;
		
		// Addon 2016-1 Jason пиратскаЯ линейка
		case "mtraxx":
			pchar.quest.Mtraxx_PasqualeLate.over = "yes";
            dialog.text = "Precisely! It's good you arrived in time. Now let me tell you the crux of the matter...";
			link.l1 = "I am all ears.";
			link.l1.go = "mtraxx_1";
		break;
		
		case "mtraxx_1":
			string sTemp = GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.questTemp.Mtraxx.Crdn.Ship), "Name")));
            dialog.text = "At this moment a "+sTemp+", the Dutch vessel named 'Rosbohom', is arriving to our waters along with one guard ship. She is loaded with black wood and sailing from Willemstad to meet another guard ship to ensure a safety voyage to Europe. I don't know what route she takes, via Sint Maarten or via Espanyol, but I know the coordinates of their rendezvous point\nYour mission is to find the Dutch there, board the trader and get her cargo to me. I will pay as soon as the cargo is delivered.";
			link.l1 = "Got it. Time and location?";
			link.l1.go = "mtraxx_2";
		break;
		
		case "mtraxx_2":
			int i = sti(pchar.questTemp.Mtraxx.Crdn.minN2)-10;
			int n = sti(pchar.questTemp.Mtraxx.Crdn.minW2)-10;
            dialog.text = ""+sti(pchar.questTemp.Mtraxx.Crdn.degN)+" "+i+" North and "+sti(pchar.questTemp.Mtraxx.Crdn.degW)+" "+n+" West. It must be somewhere South or South-West from Isla Tesoro, I am not good in it, I am not a sailor, but you are. You have around five days to do the job.";
			link.l1 = "Noted... I got it. No wasting time then!";
			link.l1.go = "mtraxx_3";
		break;
		
		case "mtraxx_3":
            dialog.text = "Godspeed captain. I'll be waiting for you and the cargo.";
			link.l1 = "...";
			link.l1.go = "mtraxx_4";
		break;
		
		case "mtraxx_4":
           DialogExit();
		   pchar.questTemp.Mtraxx = "pasq_convoy";
		   i = sti(pchar.questTemp.Mtraxx.Crdn.minN2)-10;
           n = sti(pchar.questTemp.Mtraxx.Crdn.minW2)-10;
		   AddQuestRecord("Roger_4", "3");
		   AddQuestUserData("Roger_4", "sShip", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.questTemp.Mtraxx.Crdn.Ship), "Name")+ "Gen")));
		   AddQuestUserData("Roger_4", "sdegN", sti(pchar.questTemp.Mtraxx.Crdn.degN));
		   AddQuestUserData("Roger_4", "sminN", i);
		   AddQuestUserData("Roger_4", "sdegW", sti(pchar.questTemp.Mtraxx.Crdn.degW));
		   AddQuestUserData("Roger_4", "sminW", n);
		   SetFunctionTimerCondition("Mtraxx_PasqualeTimeConvoy", 0, 0, 6, false);
		   SetFunctionTimerCondition("Mtraxx_PasqualeConvoyOver", 0, 0, 7, false);
		break;
		
		case "mtraxx_5":
			iTotalTemp = GetSquadronGoods(pchar, GOOD_EBONY);
			if (iTotalTemp < 1)
			{
				dialog.text = "Are you kidding me young man? Your cargo holds do not have a single center of black wood in them! This is an insolent trickery! Get out of here! I will inform Marcus of this! Get out!!!";
				link.l1 = "Hm...";
				link.l1.go = "mtraxx_6";
				break;
			}
			if (iTotalTemp < makeint(sti(pchar.questTemp.Mtraxx.Crdn.Ebony)/4))
			{
				dialog.text = "Are you kidding me young man? Your cargo holds have only crumbs of black wood! This is an insolent trickery! Get out of here! I will inform Marcus of this! Get out!!!";
				link.l1 = "Hm...";
				link.l1.go = "mtraxx_6";
				break;
			}
			if (iTotalTemp < sti(pchar.questTemp.Mtraxx.Crdn.Ebony)-20)
			{
				dialog.text = "The Rosbohom had at least "+FindRussianQtyString(sti(pchar.questTemp.Mtraxx.Crdn.Ebony))+" of black wood. Why did you bring me less?";
				link.l1 = "Well... you know, had to get rid of some part of it during the fight. Plus the rats, damn them...";
				link.l1.go = "mtraxx_7";
				break;
			}
            dialog.text = "Very well. How much do you have? "+FindRussianQtyString(iTotalTemp)+"? Splendid! I will pay you 150 pesos for a piece.";
			link.l1 = "150 pesos? I guess that black wood costs much more.";
			link.l1.go = "mtraxx_10";
		break;
		
		case "mtraxx_6":
           DialogExit();
		   pchar.questTemp.Mtraxx = "pasq_angry";
		   DoQuestReloadToLocation("Pirates_town", "reload", "reload6", "");
		   AddQuestRecord("Roger_4", "8");
		   CloseQuestHeader("Roger_4");
		   QuestSetCurrentNode("Terrax", "mtraxx_34");
		break;
		
		case "mtraxx_7":
            dialog.text = "Rats? Well-well... But okay. 100 pesos for a piece and you are free to go.";
			link.l1 = "100 pesos only? This is a robbery!";
			link.l1.go = "mtraxx_8";
		break;
		
		case "mtraxx_8":
			AddMoneyToCharacter(pchar, iTotalTemp*100);
			RemoveCharacterGoods(pchar, GOOD_EBONY, iTotalTemp);
            dialog.text = "Robbery is your craft, captain, I am a simple merchant. Take your money and let's don't keep arguing, you have already made a good sum selling a part of my cargo elsewhere.";
			link.l1 = "Fuck you then!";
			link.l1.go = "mtraxx_9";
		break;
		
		case "mtraxx_9":
           DialogExit();
		   pchar.questTemp.Mtraxx = "pasq_fail";
		   AddQuestRecord("Roger_4", "8");
		   CloseQuestHeader("Roger_4");
		   QuestSetCurrentNode("Terrax", "mtraxx_34");
		break;
		
		case "mtraxx_10":
            dialog.text = "And you are right, captain, but first, try to sell stolen goods and I'll see how much other merchants will pay you for them. The price offered to you is very high. Second, it was my lead, you would never find that caravan on your own, plus there were other valuables and goods on it and I am not claiming them. Third, I will give you best credits in the eyes of Marcus Tyrex and this costs a lot, trust me. And finally, fourth, a poor merchant must make a living somehow.";
			link.l1 = "Whoa! I must retreat in the face of such arguments "+npchar.name+". Let's do counting.";
			link.l1.go = "mtraxx_11";
		break;
		
		case "mtraxx_11":
			AddMoneyToCharacter(pchar, iTotalTemp*150);
			RemoveCharacterGoods(pchar, GOOD_EBONY, iTotalTemp);
            dialog.text = "Splendid. Take your coins. It was a pleasure. Make sure to check my shop from time to time. May you be fortunate in the sea!";
			link.l1 = "And you in the trade...";
			link.l1.go = "mtraxx_12";
		break;
		
		case "mtraxx_12":
           DialogExit();
		   pchar.questTemp.Mtraxx = "pasq_complete";
		   AddQuestRecord("Roger_4", "9");
		   pchar.quest.mtr_pasq_fin.win_condition.l1 = "location";
		   pchar.quest.mtr_pasq_fin.win_condition.l1.location = "Pirates_town";
		   pchar.quest.mtr_pasq_fin.function = "Mtraxx_PasqualeJeffry";
		   bDisableFastReload = true;
		break;
	}
	UnloadSegment(NPChar.FileDialog2);
}