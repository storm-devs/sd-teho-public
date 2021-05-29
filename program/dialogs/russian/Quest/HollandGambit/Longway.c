// китаец Лонгвэй, подручный Роденбурга
void ProcessDialogEvent()
{
	ref NPChar, sld, rItm, rItem;
	aref Link, NextDiag, rType;
	int i;
	string 	sAttr, sGun, sBullet, attrL;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	sAttr = Dialog.CurrentNode;
	if (findsubstr(sAttr, "SetGunBullets1_" , 0) != -1)
 	{
        i = findsubstr(sAttr, "_" , 0);
	 	NPChar.SetGunBullets = strcut(sAttr, i + 1, strlen(sAttr) - 1); // индекс в конце
 	    Dialog.CurrentNode = "SetGunBullets2";
 	}
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "Hello, captain. My name is Longway. Longway gives his ship under your command. Longway is also under your command. The order of mynheer Rodenburg.";
			link.l1 = "I see, mynheer Longway. I am glad to meet you. I think that we will cooperate well. Tell me about the target of our mission - where will we look for Jacob van Berg?";
			link.l1.go = "Longway_neutral";
			link.l2 = "Ha, I always wanted to see a Chinese in flesh... You were ordered to be my officer and I take it that you know that already. Don't worry, I will be accurate with your ship and I won't make you wash decks and keep night watch, ha-ha, you are her captain after all! Now tell me about the target of our mission - where will we look for Jacob van Berg?";
			link.l2.go = "Longway_enemy";
			link.l3 = "Greetings, mynheer Longway. Apologies, you are the captain of this wounderful ship and still you were ordered to stay under my command as an officer... This is not right. Anyway, I will consider you as a captain of her and I will be just a temporary guest. I hope that you will assist me with ship's matters. Tell me about the target of our mission - where will we look for Jacob van Berg?";
			link.l3.go = "Longway_friend";	
			NextDiag.TempNode = "First time";
			pchar.questTemp.HWIC.Holl.JacobCity = SelectJacobCity();
		break;
		
//-----------------------------------------------за Голландию-----------------------------------------------
		case "Longway_neutral":
			dialog.text = "I am sure that we will work well together. Jacob van Berg is currently at "+XI_ConvertString("Colony"+pchar.questTemp.HWIC.Holl.JacobCity+"Gen")+". I have appointed a meeting with him in the local tavern. He will be there.";
			link.l1 = "Let's set sail!";
			link.l1.go = "Longway_JacobGo";	
			pchar.questTemp.HWIC.Holl.LongwayNeutral = "true";//признак враждебности китайца
		break;
		
		case "Longway_enemy":
			dialog.text = "The order of mynheer Rodenburg is a law for Longway... Jacob van Berg is currently at "+XI_ConvertString("Colony"+pchar.questTemp.HWIC.Holl.JacobCity+"Gen")+". I have appointed a meeting with him in the local tavern. He will be there.";
			link.l1 = "Let's set sail!";
			link.l1.go = "Longway_JacobGo";	
			pchar.questTemp.HWIC.Holl.LongwayEnemy = "true";//признак враждебности китайца
		break;
		
		case "Longway_friend":
			dialog.text = "Longway will do all he can, captain. And Jacob van Berg is currently at "+XI_ConvertString("Colony"+pchar.questTemp.HWIC.Holl.JacobCity+"Dat")+". I have appointed a meeting with him in the local tavern. He will be there.";
			link.l1 = "Let's set sail!";
			link.l1.go = "Longway_JacobGo";	
			pchar.questTemp.HWIC.Holl.LongwayFriend = "true";//признак враждебности китайца
		break;
		
		case "Longway_JacobGo":
			//Лонгвэя - в офицеры
			npchar.quest.OfficerPrice = sti(pchar.rank)*500;
			Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(npchar.id);
			npchar.OfficerWantToGo.DontGo = true; //не пытаться уйти
			npchar.HalfImmortal = true;//полубессмертен
			npchar.loyality = 18;
			AddDialogExitQuestFunction("LandEnc_OfficerHired");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload2_back", "none", "", "", "", -1);
			AddQuestRecord("Holl_Gambit", "1-8");
			AddQuestUserData("Holl_Gambit", "sCity", XI_ConvertString("Colony"+pchar.questTemp.HWIC.Holl.JacobCity+"Dat"));
			pchar.questTemp.HWIC.Holl = "JacobOnMain";
			SetFunctionTimerCondition("JacobOnMainOver", 0, 0, 15, false);
		break;
		
		case "hired":
			dialog.text = "Want something from Longway, captain?";
			link.l1 = "No, it's nothing.";
			link.l1.go = "exit";
			NextDiag.TempNode = "hired";
		break;
		
		case "MC_GoAway":
			PlaySound("VOICE\Russian\hambit\Longway-02.wav");
			if (pchar.questTemp.HWIC.Holl == "MirageFail")
			{
				dialog.text = "You are an idiot, captain! We were told to do an easy task - to capture the 'Mirage' without loosing the 'Meifeng'. She was an easy target without her captain, yet you failed to do the job\nLongway doesn't wish neither serve you, nor see you. Longway is sure that mynheer Rodenburg will approve his decision.";
				link.l1 = "Hell with you and your master!";
				link.l1.go = "exit";
				AddQuestRecord("Holl_Gambit", "1-10");
			}
			if (pchar.questTemp.HWIC.Holl == "JacobOnMain" || pchar.questTemp.HWIC.Holl == "JacobInRoom")
			{
				dialog.text = "Captain, you are an idiot. We have spent too much time solving your own matters instead of meeting Jacob van Berg. There is no doubt that he is already not at "+XI_ConvertString("Colony"+pchar.questTemp.HWIC.Holl.JacobCity+"Dat")+"\nYou have failed to do the task. Longway doesn't wish neither serve you, nor see you. Longway is sure that mynheer Rodenburg will approve his decision.";
				link.l1 = "Hell with you and your master!";
				link.l1.go = "exit";
				AddQuestRecord("Holl_Gambit", "1-9");
			}
			if (pchar.questTemp.HWIC.Holl == "lateVillemstad")
			{
				dialog.text = "Captain, you have been wasting too much time absent result. It's not your ship and Longway is not your permanent officer, he's going to return to Willemstad\nLongway doesn't wish neither serve you, nor see you. Longway is sure that mynheer Rodenburg will approve his decision.";
				link.l1 = "Hell with you and your master!";
				link.l1.go = "exit";
			}
			PChar.quest.Munity = "Deads";
			LAi_LocationFightDisable(&Locations[FindLocation("Ship_deck")], false);
			if(sti(RealShips[sti(pchar.ship.type)].basetype) == SHIP_MAYFANG)//если сам на Мейфенг
			{
			pchar.Ship.Type = GenerateShipExt(SHIP_TARTANE, true, pchar);
			pchar.Ship.name = "Boat";
			SetBaseShipData(pchar);
			SetCrewQuantityOverMax(PChar, 0);
			}
			else
			{
				for(i=1; i < COMPANION_MAX; i++)
				{
					int iTemp = GetCompanionIndex(PChar, i);
					if(iTemp > 0)
					{
						sld = GetCharacter(iTemp);
						if(sti(RealShips[sti(sld.ship.type)].basetype) == SHIP_MAYFANG)
						{
							pchar.questTemp.HWIC.Holl.CompanionIndex = sld.Index;
							sld = GetCharacter(sti(pchar.questTemp.HWIC.Holl.CompanionIndex));
							RemoveCharacterCompanion(PChar, sld);
							AddPassenger(PChar, sld, false);
						}
					}
				}
			}
			LAi_CharacterDisableDialog(npchar);
			LAi_SetImmortal(npchar, true);
			npchar.lifeday = 0;
			DeleteAttribute(pchar, "questTemp.HWIC.TakeQuestShip");//ПУ откроем
			DeleteAttribute(pchar, "questTemp.HWIC.HollEquip");
			pchar.questTemp.HWIC.Holl = "end";
			CloseQuestHeader("Holl_Gambit");
			pchar.questTemp.HWIC.Detector = "holl_fail";
		break;
		
		case "Longway_hire":
			PlaySound("VOICE\Russian\hambit\Longway-03.wav");
			dialog.text = "Captain, Longway has left mynheer Rodenburg. Longway will never get back to him. You were polite with Longway and you are a brave sailor. Longway want to join your crew as an officer.";
			link.l1 = "Welcome aboard, friend!";
			link.l1.go = "Longway_hire_1";	
			link.l2 = "No, thanks, Longway. You are a free captain. I can't imagine myself as your commander.";
			link.l2.go = "Longway_exit";	
		break;
		
		case "Longway_exit":
			DialogExit();
			npchar.lifeday = 0;
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload2", "none", "", "", "", 30.0);
			AddQuestRecord("Holl_Gambit", "1-37");
		break;
		
		case "Longway_hire_1"://нанимаем китайца
			DialogExit();
			DeleteAttribute(npchar, "LifeDay");
			DeleteAttribute(npchar, "HalfImmortal");
			npchar.quest.OfficerPrice = sti(pchar.rank)*500;
			npchar.OfficerWantToGo.DontGo = true;
			npchar.loyality = MAX_LOYALITY;
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, true);
			DeleteAttribute(npchar, "CompanionDisable");//теперь можем и в компаньоны
			npchar.Payment = true;
			LAi_SetOfficerType(npchar);
			NextDiag.CurrentNode = "Longway_officer";
			npchar.quest.meeting = true;
			npchar.HoldEquip = true;
			LAi_SetImmortal(npchar, false);
			LAi_SetHP(npchar, 200, 200);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			SaveCurrentNpcQuestDateParam(npchar, "HiredDate");
			AddQuestRecord("Holl_Gambit", "1-38");
		break;
		
//---------------------------------------------против всех-------------------------------------------------
		case "Longway_abordage":
			PlaySound("VOICE\Russian\hambit\Longway-02.wav");
			dialog.text = "Why stop? Finish, Longway tired, Longway lost.";
			link.l1 = "Wait, friend. I will find time to kill you if I want. But I need to talk with you first. In a good way perhaps, it all depends on you. And now, welcome to my cargo hold!";
			link.l1.go = "Longway_abordage_1";			
		break;
		
		case "Longway_abordage_1":
			AddQuestRecord("Holl_Gambit", "3-45");
		    DoQuestCheckDelay("LAi_ReloadBoarding", 1.0);
            DialogExit();
			LAi_SetPlayerType(pchar);
			pchar.questTemp.HWIC.Self = "LongwayPrisoner";
			npchar.lifeday = 0;
			SetFunctionTimerCondition("RemoveLongwayOver", 0, 0, 1, false);//таймер до конца суток, ибо нефиг
		break;
		
		case "Longway_prisoner":
			dialog.text = "";
			link.l1 = "Well, now we can talk without any fighting around. Longway... I need information you have and I have no doubts that you really have it. The question is simple: will you tell me it in a good way or in a hard way?";
			link.l1.go = "Longway_prisoner_1";			
		break;
		
		case "Longway_prisoner_1":
			dialog.text = "";
			link.l1 = "Keeping silence? Fine. I offer you a deal. I will spare your life and land you on some shore. In return, you will tell me where and why Lucas Rodenburg has sent you. Deal?";
			link.l1.go = "Longway_prisoner_2";			
		break;
		
		case "Longway_prisoner_2":
			dialog.text = "";
			link.l1 = "I see that you are a good listener. But it is time to start talking. You will tell me everything even in case we won't find a common language, trust me. Alonso is a master of loosen people's tongues. He was a soldier of the Holy Inquisition in Santiago before he hired on my ship. He knows a lot of tricks which he learnt from holy fathers who perfected the art of making folk to confess...";
			link.l1.go = "Longway_prisoner_3";			
		break;
		
		case "Longway_prisoner_3":
			dialog.text = "";
			link.l1 = "You will tell me everything, my friend... Everything... But you won't live long after that, no, you won't. Your body will suffer too much after meeting with Alonso/. So the choice is yours. Either you tell me all the truth and live, or you tell me all the truth and die afterwards. Think about it...";
			link.l1.go = "Longway_prisoner_4";			
		break;
		
		case "Longway_prisoner_4":
			dialog.text = "";
			link.l1 = "I see a doubt in your eyes. Make up your mind. Why should you die for the sins of your patron? Does he worth that? Answer, does Rodenburg really worth your life taken from your suffering body?";
			link.l1.go = "Longway_prisoner_5";			
		break;
		
		case "Longway_prisoner_5":
			dialog.text = "Longway will speak. But Longway wants to be sure that you will keep your word, captain.";
			link.l1 = "Ha! I hear wise words! I give you my word.";
			link.l1.go = "Longway_prisoner_6";			
		break;
		
		case "Longway_prisoner_6":
			dialog.text = "Sorry, captain, but it is not enough. You can get information and kill Longway at once. Longway want to have some confidence, just a bit.";
			link.l1 = "Fine. What guarantees do you want?";
			link.l1.go = "Longway_prisoner_7";			
		break;
		
		case "Longway_prisoner_7":
			dialog.text = "There is small island at the south of Guadeloupe. Cape Inaccessible. Land Longway there and give him a weapon. Only then Longway will tell you everything he knows about Lucas Rodenburg.";
			link.l1 = "Hm... Don't you think that you are not in the right position to bargain?";
			link.l1.go = "Longway_prisoner_8";			
		break;
		
		case "Longway_prisoner_8":
			dialog.text = "You would do the same if you were in my shoes, captain. It won't be easy for your man to get words from me even with tortures. Longway is not a white man.";
			link.l1 = "Fine. Deal. But I warn you - don't try to play around or I will personally cut you to pieces. Small ones, to make my pleasure last longer... Alonso!";
			link.l1.go = "Longway_prisoner_9";
		break;
		
		case "Longway_prisoner_9":
			DialogExit();
			NextDiag.Currentnode = "Longway_prisoner_0";
			npchar.greeting = "longway";
			sld = characterFromId("Sailor_3");
			sld.dialog.currentnode = "Sailor_deck_7";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);	
			pchar.quest.RemoveLongwayOver.over = "yes";//снять таймер
			pchar.quest.RemoveLongwayTimer.win_condition.l1 = "Timer";
			pchar.quest.RemoveLongwayTimer.win_condition.l1.date.hour  = sti(GetTime());
			pchar.quest.RemoveLongwayTimer.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 10);
			pchar.quest.RemoveLongwayTimer.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 10);
			pchar.quest.RemoveLongwayTimer.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 10);
			pchar.quest.RemoveLongwayTimer.function = "RemoveLongwayOver";
			pchar.questTemp.HWIC.Self = "GotoGuadeloupe";
		break;
		
		case "Longway_prisoner_0":
			dialog.text = "Have we arrived at Guadeloupe, captain?";
			link.l1 = "Not yet... sit still, we will be there soon.";
			link.l1.go = "exit";
			NextDiag.Tempnode = "Longway_prisoner_0";
		break;
		
		case "Longway_prisoner_10":
			dialog.text = "You have kept your word, captain, and so will Longway. Did you want to know about Longway's mission?";
			link.l1 = "Yes. But allow me to remind you your own promise to me: you will tell me EVERYTHING you know.";
			link.l1.go = "Longway_prisoner_11";			
		break;
		
		case "Longway_prisoner_11":
			dialog.text = "Longway remembers. He will tell everything you ask about Rodenburg, captain.";
			link.l1 = "Great. So what about your mission?";
			link.l1.go = "Longway_prisoner_12";			
		break;
		
		case "Longway_prisoner_12":
			dialog.text = "'Meifeng' was sailing from the port of Willemstad to the North to the shores of St. Christopher. In five days there would be a galleon under the command of Peter Stuyvesant. Longway's order was to sink this ship with it's captain.";
			link.l1 = "Wait... Did Rodenburg order you to kill Stuyvesant? What a nonsense!";
			link.l1.go = "Longway_prisoner_13";			
		break;
		
		case "Longway_prisoner_13":
			dialog.text = "Longway speaks the truth, captain. That was an order of mynheer Rodenburg. Longway didn't like it but Longway doesn't discuss orders.";
			link.l1 = "I don't get it... What is the game your master is up for?";
			link.l1.go = "Longway_prisoner_14";			
		break;
		
		case "Longway_prisoner_14":
			dialog.text = "Ex master, captain. Longway is not going to return to mynheer Rodenburg. He has seized power in Curacao. Mathias Beck was an easy pray, Rodenburg's authority and connections with a commandant were enough to put the governor in jail\nThe only obstacle left is the Company's director, mynheer Stuyvesant. Once he is eliminated, Rodenburg will hold every string of power in Dutch colonies.";
			link.l1 = "Hm. What a strange coincidence. Tell me, Longway, what has made a respected and powerful man to perform such a radical actions against his boss? I don't really trust in a sunstroke or in a sudden insanity...";
			link.l1.go = "Longway_prisoner_15";			
		break;
		
		case "Longway_prisoner_15":
			dialog.text = "Longway wantd to know it himself from you, captain. It was you who captured the courier of the Company and gave him a letter to Rodenburg, right? The reason in this letter.";
			link.l1 = "I see now... Yes, it seems that there are a lot of wonderful things in John's archive to make Rodenburg scared enough to start a coup.";
			link.l1.go = "Longway_prisoner_16";			
		break;
		
		case "Longway_prisoner_16":
			dialog.text = "Want to know anything else, captain?";
			link.l1 = "Yes. What else has Rodenburg done?";
			link.l1.go = "Longway_prisoner_17";			
		break;
		
		case "Longway_prisoner_17":
			dialog.text = "Mynheer Rodenburg has ordered to kill you. Longway was in Caracas before hunting Stuyvesant and had a meeting with captain Jacob and gave him orders.";
			link.l1 = "Jacob? Jacob... Hm. Jacob van Berg?";
			link.l1.go = "Longway_prisoner_18";			
		break;
		
		case "Longway_prisoner_18":
			dialog.text = "You are well informed. Yes. Captain Jacob is hunting you, captain. He will eventually find you. No one was able to hide from van Berg.";
			link.l1 = "The devil is not so black as they paint him. I will deal with van Berg and with his ghost ship.";
			link.l1.go = "Longway_prisoner_19";			
		break;
		
		case "Longway_prisoner_19":
			dialog.text = "You know a lot, captain. But Longway has nothing to add. Ask if you still have something to ask.";
			link.l1 = "Will Stuyvesant be near the shores of St. Christopher?";
			link.l1.go = "Longway_prisoner_20";			
		break;
		
		case "Longway_prisoner_20":
			dialog.text = "Yes, captain. You will be able to find his galleon in a week time near the shores of this island.";
			link.l1 = "Nice! Let's act against this fox with its own methods... No questions left. I got everything I have wanted.";
			link.l1.go = "Longway_prisoner_21";			
		break;
		
		case "Longway_prisoner_21":
			dialog.text = "The last advice, captain. You have to fly the 'Meifeng' if you want to get close to the galleon and not being attacked.";
			link.l1 = "Got it. Thanks for your information.";
			link.l1.go = "Longway_prisoner_22";			
		break;
		
		case "Longway_prisoner_22":
			dialog.text = "Longway is leaving now. Farewell, captain.";
			link.l1 = "See you, the son of Celestial.";
			link.l1.go = "Longway_prisoner_23";			
		break;
		
		case "Longway_prisoner_23":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "ReturnShoreToNormal", -1);
			npchar.lifeday = 0;
			AddQuestRecord("Holl_Gambit", "3-49");
			pchar.questTemp.HWIC.Self = "MeetingStivesant";
			pchar.quest.Seek_Piter.win_condition.l1 = "location";
			pchar.quest.Seek_Piter.win_condition.l1.location = "Nevis";
			pchar.quest.Seek_Piter.function = "CreatePiterHalleon";
			pchar.quest.RemoveLongwayTimer.over = "yes";//снять прерывание
			SetFunctionTimerCondition("QuestShipsTerms_Over", 0, 0, 8, false); // таймер
		break;
		
		//--> ----------------------------------- офицерский блок ------------------------------------------
		case "Longway_officer":
			dialog.text = "Longway is listening to you, captain.";
			if (CheckAttribute(pchar, "questTemp.Dolly_Tieyasal") && !CheckAttribute(npchar, "quest.Tieyasal"))
			{
				Link.l4 = "Longway, I am going to an ancient Indian city Tayasal. I will be clear, this is going to be a really dangerous trip and it is also a mystic one - we will get there through the teleport idol. Will you... join me?";
				Link.l4.go = "tieyasal";
			}
			
			////////////////////////казначей///////////////////////////////////////////////////////////
           	// boal отчёт о корабле
			if(CheckAttribute(NPChar, "treasurer") && NPChar.treasurer == 1)
			{
			    Link.l11 = "Longway, give me a full ship report.";
			    Link.l11.go = "QMASTER_1";
				
			    // Warship. Автозакупка товара
				Link.l12 = "I want you to purchase certain goods every time we are docked.";
				Link.l12.go = "QMASTER_2";
			}

			if (CheckAttribute(NPChar, "IsCompanionClone"))//////////////////компаньон//////////////////////////////////////////////
			{
				//dialog.text = "Я прибыл по вашему распоряжению, капитан.";
				Link.l2 = "I need to issue several orders to you.";
				Link.l2.go = "Companion_Tasks";
				NextDiag.TempNode = "Longway_officer";// не забыть менять в зависисомости от оффа
				break;
			}
			Link.l1 = "Listen to my order!";
            Link.l1.go = "stay_follow";
			link.l2 = "It's nothing. Dismissed!";
			link.l2.go = "exit";
			NextDiag.TempNode = "Longway_officer";
		break;
		
		/////////////////////////// ответы для казначея ///////////////////////////////////
		case "QMASTER_1":
			dialog.Text = "Longway has never been a purser, Captain. Longway can tell you how to navigate from Trinidad to Havana and how long it will take. But Longway never counts cargo, sales, and trade.";
			Link.l1 = "I guess you are right: it's a shame to ask such a fine navigator of this.";
			Link.l1.go = "exit";
		break;	

		case "QMASTER_2":
			dialog.text = "Longway doesn't trade with white peoples, Captain. Longway always stood at the helm, not in shops where merchants bargain to the last lousy peso.";
			link.l1 = "Hm, you're quite right. I doubt you will get along with shop folk...";
			link.l1.go = "exit";
		break;

		//Указания для компаньона 19.02.08 -->/////////////////////////////////////////////////////////////////////////////////////////
		case "Companion_Tasks":
			dialog.Text = "I am listening to you.";
			Link.l1 = "This is about boarding.";
			Link.l1.go = "Companion_TaskBoarding";
			Link.l2 = "This is about your ship.";
			Link.l2.go = "Companion_TaskChange";
			if (bBettaTestMode) // Только при бета-тесте
			{
				Link.l3 = "I want you to leave my squadron for a while and seek fortune on your own.";
				Link.l3.go = "CompanionTravel";
			}
			Link.l8 = "Nothing so far.";
			Link.l8.go = "exit";
		break;

		case "Companion_TaskBoarding":
			dialog.Text = "So what is your wish.";
			Link.l1 = "Don't board enemy ships. Take care of yourself and the crew.";
			Link.l1.go = "Companion_TaskBoardingNo";
			Link.l2 = "I want you to board enemy ships.";
			Link.l2.go = "Companion_TaskBoardingYes";
		break;

		case "Companion_TaskChange":
			dialog.Text = "So what is your wish.";
			Link.l1 = "I would like you not to swap your ship for another one after boarding. It's too valuable.";
			Link.l1.go = "Companion_TaskChangeNo";
			Link.l2 = "When you are boarding enemy ships, you can take them for yourself, if they happen to be decent.";
			Link.l2.go = "Companion_TaskChangeYes";
		break;

		case "Companion_TaskBoardingNo":
			dialog.Text = "Aye-aye.";
			Link.l1 = "At ease.";
			Link.l1.go = "exit";
			NPChar.Tasks.CanBoarding = false;
		break;

		case "Companion_TaskBoardingYes":
			dialog.Text = "It will be done.";
			Link.l1 = "At ease.";
			Link.l1.go = "exit";
			NPChar.Tasks.CanBoarding = true;
		break;

		case "Companion_TaskChangeNo":
			dialog.Text = "Aye-aye.";
			Link.l1 = "It will be done.";
			Link.l1.go = "exit";
			NPChar.Tasks.CanChangeShipAfterBoarding = false;
		break;

		case "Companion_TaskChangeYes":
			dialog.Text = "It will be done.";
			Link.l1 = "At ease.";
			Link.l1.go = "exit";
			NPChar.Tasks.CanChangeShipAfterBoarding = true;
		break;
	//	<========////////////////////////////////////////
		case "stay_follow":
            dialog.Text = "Orders?";
            Link.l1 = "Stand here!";
            Link.l1.go = "Boal_Stay";
            Link.l2 = "Follow me and keep up!";
            Link.l2.go = "Boal_Follow";
			sGun = GetCharacterEquipByGroup(NPChar, GUN_ITEM_TYPE);
			if(sGun != "")
			{
				rItm = ItemsFromID(sGun);
				if(CheckAttribute(NPChar, "chr_ai.bulletNum") && sti(NPChar.chr_ai.bulletNum) > 1)
				{
					Link.l3 = "Change the type of ammo for your firearms.";
					Link.l3.go = "SetGunBullets";
				}	
			}		
		break;
		
		case "SetGunBullets":
			Dialog.Text = "Choosing the type of ammo:";
			sGun = GetCharacterEquipByGroup(NPChar, GUN_ITEM_TYPE);
			rItm = ItemsFromID(sGun);
			makearef(rType, rItm.type);	
			for (i = 0; i < sti(NPChar.chr_ai.bulletNum); i++)
			{
				sAttr = GetAttributeName(GetAttributeN(rType, i));
				sBullet = rItm.type.(sAttr).bullet;
				rItem = ItemsFromID(sBullet);								
				attrL = "l" + i;
				Link.(attrL) = GetConvertStr(rItem.name, "ItemsDescribe.txt");;
				Link.(attrL).go = "SetGunBullets1_" + i;
			}
		break;	

		case "SetGunBullets2":
			i = sti(NPChar.SetGunBullets) + 1; 
			sGun = GetCharacterEquipByGroup(NPChar, GUN_ITEM_TYPE);
			rItm = ItemsFromID(sGun);
			sAttr = "t" + i;
			sBullet = rItm.type.(sAttr).bullet;
			LAi_SetCharacterUseBullet(NPChar, sBullet);
			LAi_GunSetUnload(NPChar);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DeleteAttribute(NPChar,"SetGunBullets");
			DialogExit();
		break;		
		
        case "Boal_Stay":
            Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(Npchar.id);
            AddDialogExitQuestFunction("LandEnc_OfficerStay");
            dialog.Text = "There is change of disposition!";
            Link.l1 = "Dismissed.";
            Link.l1.go = "Exit";
            Npchar.chr_ai.tmpl = LAI_TMPL_STAY;
        break;
        
        case "Boal_Follow":
            SetCharacterTask_FollowCharacter(Npchar, PChar);
            dialog.Text = "There is change of disposition!";
            Link.l1 = "Dismissed.";
            Link.l1.go = "Exit";
        break;
	//<-- ----------------------------------- офицерский блок ----------------------------------------
	
	// на Тайясаль
		case "tieyasal":
			dialog.text = "Longway has been following you for a long time. Longway will follow you as always. Longway will not leave his captain.";
			link.l1 = "Thank you, Longway! I am glad that I was right about you.";
			link.l1.go = "tieyasal_1";
		break;
		
		case "tieyasal_1":
			dialog.text = "When will we start?";
			link.l1 = "A bit later. We have to prepare ourselves for it.";
			link.l1.go = "tieyasal_2";
		break;
		
		case "tieyasal_2":
			DialogExit();
			AddQuestRecord("Tieyasal", "24");
			npchar.quest.Tieyasal = "teleport";
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}

string SelectJacobCity()
{
	string sTemp;
	switch (drand(4))
	{
		case 0: sTemp = "Cumana" break;
		case 1: sTemp = "Caracas" break;
		case 2: sTemp = "Maracaibo" break;
		case 3: sTemp = "Cartahena" break;
		case 4: sTemp = "Portobello" break;
	}
	return sTemp;
}
