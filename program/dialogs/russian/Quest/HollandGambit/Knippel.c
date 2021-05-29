// Чарли Книппель - старый артиллерист
void ProcessDialogEvent()
{
	ref NPChar, sld, rItm, rItem;
	aref Link, NextDiag, rType;
	int i, iTemp, amount;
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
		//ветка на взятие 2 варианта прохождения - за Англию
		if(CheckAttribute(pchar, "questTemp.HWIC.CanTake") && !CheckAttribute(pchar, "questTemp.HWIC.CanTake.Eng") && !CheckAttribute(npchar, "quest.HWICTake") && !CheckAttribute(pchar, "questTemp.HWIC.Holl") && !CheckAttribute(pchar, "questTemp.HWIC.Self"))
		{
			dialog.text = "Good day, mister, chain shot to my butt! What brought you here?";
			link.l1 = "Greetings. I have nothing special for you, just wanted to say hi.";
			link.l1.go = "exit";
			link.l2 = "Listen, Charlie, there are rumours that you have some sort of connections with the English Navy. I have a fine ship and skilled crew. I'd like to offer me and my ship to the service for England. I mean the real service worthy the experienced captain. Can you give me an advice or recommend me to someone or, perhaps, to help me anyhow in that matter?";
			link.l2.go = "Knippel_check";
			break;
		}
		//за Голландию
		if (CheckAttribute(pchar, "questTemp.HWIC.Holl"))
		{
			if (pchar.questTemp.HWIC.Holl == "toKnippel")
			{
				dialog.text = "Good day, mister, chain shot to my butt! What brought you here?";
				link.l1 = "Greetings, Charlie. There are rumors that you have connections with the English Navy, that is why I want to ask you for help...";
				link.l1.go = "Dominica";
				break;
			}
			dialog.text = "Chain shot to my butt! What do you want, mister?";
			link.l1 = "No, it's nothing. I am leaving.";
			link.l1.go = "exit";
			break;
		}
		//за Англию
		if (CheckAttribute(pchar, "questTemp.HWIC.Eng"))
		{
			if (pchar.questTemp.HWIC.Eng == "TakeHollConvoy")
			{
				dialog.text = "Good day, captain. I have heard some rumours about interception of the silver convoy...";
				link.l1 = "I am ready to report about my success in your mission, Charlie.";
				link.l1.go = "HollConvoy_Check";
				break;
			}
			if (pchar.questTemp.HWIC.Eng == "Start_main" && GetQuestPastDayParam("questTemp.HWIC.Eng_1") > 0)
			{
				dialog.text = "I am glad to see you, captain! My commander, Richard Fleetwood, was going to come here to get know you himself, but an accident happened yesterday evening... There was an attempt on Richard's life right on the streets, chain shot to my butt!";
				link.l1 = "Impossible! And what were the guards doing?";
				link.l1.go = "Fleetwood_house";
				break;
			}
			dialog.text = "Do you have any questions, captain?";
			link.l1 = "No, it's nothing. I am leaving.";
			link.l1.go = "exit";
		break;
		}
			dialog.text = "Good day, mister, chain shot to my butt! What brought you here?";
			link.l1 = "Greetings. I have nothing special for you, just wanted to say hi...";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;

//-------------------------------------------за Голландию--------------------------------------------------	
		case "Dominica":
			dialog.text = "Heh! And how can the old sailor, who was grounded long time ago, help you, mister?";
			link.l1 = "See... I am just a common captain and I do regular voyages between Martinique and Curacao. So I have been attacked twice by the ghost ship not far from Martinique... Though she is not the ghost ship, I was able to tear her sails with simple cannonbals!";
			link.l1.go = "Dominica_1";			
		break;
		
		case "Dominica_1":
			dialog.text = "Is that so? It is very interesting, chain shot to my neck...";
			link.l1 = "I have survived only because my ship does the fine speed by the wind. Last time I had to throw away all my cargo in order to escape... can you imagine my loss?";
			link.l1.go = "Dominica_2";			
		break;
		
		case "Dominica_2":
			dialog.text = "I am sorry, captain...";
			link.l1 = "The governor of Curacao - Mathias Beck just brushed my complaints aside. He said that they are only fables. The governor of Martinique promised to send a patrol there, but his eyes told me that he ain't going to do a thing.  I can't return to Martinique while the bastard is sailing there, my ship is small so is my crew, it is likely that I won't make it in the third time...";
			link.l1.go = "Dominica_3";			
		break;
		
		case "Dominica_3":
			dialog.text = "I am so sorry, mister. But how can I help you?";
			link.l1 = "I heard from the respected sailors that there was one captain of St. John's named Richard Fleetwood who hunted for the ghost ship. I don't know him personally, that is why I told this story to you, perhaps you will tell him a story of my misfortunes? I am sure that the filthy pirate is hiding somewhere near the wild shores of Dominica and raiding between Barbados and Martinique.";
			link.l1.go = "Dominica_4";			
		break;
		
		case "Dominica_4":
			dialog.text = "Between Barbados and Martinique? It sounds very much like this scum...";
			link.l1 = "I am not rich and I don't have money to pay the naval forces for sparing these waters from the bastard. But sir Fleetwood is hunting for him already, so please tell him where to find this 'Flying Dutchman'.";
			link.l1.go = "Dominica_5";			
		break;
		
		case "Dominica_5":
			dialog.text = "You have done a good thing by coming here. I will tell your story to right people, chain shot to my liver! Soon, you will be able to trade with Martinique again.";
			link.l1 = "I hope that God will hear your words! Thank you for listening to me, Charlie. I do hope for the best. Farewell!";
			link.l1.go = "Dominica_6";			
		break;
		
		case "Dominica_6":
			DialogExit();	
			pchar.questTemp.HWIC.Holl = "toDominica";
			AddQuestRecord("Holl_Gambit", "1-17");
			pchar.quest.toDominica.win_condition.l1 = "location";
			pchar.quest.toDominica.win_condition.l1.location = "Dominica";
			pchar.quest.toDominica.function = "PrepareToFleetwoodAttack";
		break;

//----------------------------------------------за Англию--------------------------------------------------	
		case "Knippel_check"://начинаем проверять нашего ГГ по всем статьям
			if(makeint(PChar.reputation.nobility) < 41)//низкая репа
			{
				PlaySound("VOICE\Russian\hambit\Charlie Knippel-04.wav");
				dialog.text = "England don't need services from rogues, chain shot to my arse! I can't give you any advice.";
				link.l1 = "Hey, hey, pal, watch your tongue!";
				link.l1.go = "exit";
				break;
			}
			if(GetSummonSkillFromName(pchar, SKILL_SAILING) < 30)//низкая навигация
			{
				dialog.text = "Captain, our fleet needs more experienced captains. Come back when you will have more skills in navigating.";
				link.l1 = "I see... Then I will see you later.";
				link.l1.go = "exit";
				break;
			}
			if(sti(Pchar.rank) > 15)//высокий ранг
			{
				PlaySound("VOICE\Russian\hambit\Charlie Knippel-03.wav");
				dialog.text = "You are too famous at the archipelago, captain. I doubt that you would be interested in my missions, though I don't have any missions anyway.";
				link.l1 = "Fine, as you wish. Goodbye.";
				link.l1.go = "exit";
				break;
			}
			dialog.text = "Hm... You are just in time, captain, chain shot to my butt! Richard didn't know who to assign on to do that risky business, he was even considering to decline it... So I will give you a chance. If you perform well, then I will recommend you to a very kind and important man. Now listen what is need to be done.";
			link.l1 = "I am listening.";
			link.l1.go = "Knippel_task";
		break;
		
		case "Knippel_task"://первое задание
			dialog.text = "The silver caravan of the Dutch West India Company left Willemstad of Curacao one or two days ago. It is sailing to Philipsburg. There are only a few ships in the caravan. Ost-indian with the silver in her cargo hold and one or two patrol ships. Intercept this caravan, capture the Ost-indian with the silver cargo and bring her to Antigua. You can sink the escort though, chain shot to their livers!";
			link.l1 = "Fine, I am on my way!";
			link.l1.go = "Knippel_task_1";			
		break;
		
		case "Knippel_task_1":
			dialog.text = "I will allow myself to give you some advice, captain. The way from Curacao to Sint Maarten lies not far from the shores of St. Christopher. I would make an ambush there. Prepare yourself well for the meeting, it is not a childish game... Good luck!";
			link.l1 = "Thanks! Your words make me think that I will need it. See you!";
			link.l1.go = "Knippel_task_2";			
		break;
		
		case "Knippel_task_2":
			DialogExit();
			npchar.quest.HWICTake = "true";
			pchar.questTemp.HWIC.CanTake.Eng = "true";//признак, что английка уже бралась
			HWICSilverConvoyInWorld();
			AddQuestRecord("Holl_Gambit", "2-1");
			ReOpenQuestHeader("Holl_Gambit"); // данила ,чтобы вышел из архива. 																				   
			pchar.questTemp.HWIC.Eng = "begin";
			SetFunctionTimerCondition("HollConvoy_Over", 0, 0, 15, false);
		break;
		
		case "HollConvoy_Check"://начинаем проверять
			int iHal = 0;
			for(i = 0; i < COMPANION_MAX; i++)
			{
				iTemp = GetCompanionIndex(PChar, i);
				if(iTemp > 0)
				{
					sld = GetCharacter(iTemp);
					pchar.questTemp.HWIC.Eng.CompanionIndex = sld.Index;
					if(sti(RealShips[sti(sld.ship.type)].basetype) == SHIP_EASTINDIAMAN) iHal++;
				}
			}//признак наличия ТГ в компаньонах
			if (iHal > 0)
			{
				amount = sti(pchar.questTemp.HWIC.Eng.SlvQty) - GetSquadronGoods(pchar, GOOD_SILVER);
				if (amount <= 0)
				{
					dialog.text = "Well, there is no need in report. I was informed about everything right after the custom examination of your ship... You've done really well, captain. Most excellent! It wasn't easy business, chain shot to my butt!";
					link.l1 = "Thanks! It was nice to hear such a high valuation of my actions.";
					link.l1.go = "HollConvoy_complete";
				}
				else
				{
					dialog.text = "Well, there is no need in report. I was informed about everything right after the custom examination of your ship... Captain, you brought not the whole cargo, chain shot to my butt! I surely know how much silver must have been on that galleon. This mission's purpose was not only to test your battle skills but to test your honesty. You have failed the greed test. I don't want to work with you so get out!";
					link.l1 = "Hell with you, sissy!";
					link.l1.go = "HollConvoy_fail";
				}
			}
			else
			{
				dialog.text = "I don't see the Holland Ost-indian in your squadron. I told you to bring her here as a prize. Have you sold her?";
				link.l1 = "Hm... did you tell me to bring the ship? I thought that we had a deal only about silver.";
				link.l1.go = "HollConvoy_noShip";
			}
		break;
		
		case "HollConvoy_noShip":
			dialog.text = "Don't ring your chain shots, mister! I clearly remember what I told you and what I didn't. You have broken the terms of our deal and I don't want to work with you any longer, there is no place for rogues here. Leave my house immediately!";
			link.l1 = "Hell with you!";
			link.l1.go = "HollConvoy_fail";
		break;
		
		case "HollConvoy_fail":
			DialogExit();
			AddQuestRecord("Holl_Gambit", "2-3");
			CloseQuestHeader("Holl_Gambit");
			DeleteAttribute(pchar, "questTemp.HWIC.Eng");//зачищаем для возможности отката к голландскому варианту
			pchar.questTemp.HWIC.Fail2 = "true";
		break;
		
		case "HollConvoy_complete":
			dialog.text = "Visit me tomorrow and I will introduce you to my patron. I think, he will offer you work worthy of you. And also you will get your reward from him. See you!";
			link.l1 = "Fine, Charlie. I will be here tomorrow.";
			link.l1.go = "exit";
			npchar.greeting = "knippel_2";
			AddDialogExitQuestFunction("HollConvoy_Remove");
			pchar.questTemp.HWIC.Eng = "Start_main";
			SaveCurrentQuestDateParam("questTemp.HWIC.Eng_1");
			AddQuestRecord("Holl_Gambit", "2-4");
			AddSimpleRumourCity("They say, that you have captured a Holland ship filled with silver. Well done! You are a brave and reckless sailor, captain!", "SentJons", 10, 3, "");
		break;
		
		case "Fleetwood_house":
			dialog.text = "I've been asking myself the same thing... Some bastard had thrown pepper in patron's eyes and stabbed him in the chest, before Richard managed to grab his blade. Assassin was planning to end Richard with one hit, since he didn't have time for another, but he failed - commander always carry an armour under his clothes\Filthy scum, chain shot to his liver, managed to flee. It looks like he has friends in the town. The only detail we know about him - he has only one eye. It won't help us much though, there are plenty of Cyclops like him these days\nRichard has lost a lot of blood and didn't washed his eyes immediately, so he is almost blind now...";
			link.l1 = "Well, I am sorry for your commander. Was the attacker declared to be wanted?";
			link.l1.go = "Fleetwood_house_1";
		break;
		
		case "Fleetwood_house_1":
			dialog.text = "Richard's marines have searched whole town and the local bays, but they didn't find a thing, chain shots to their necks! If we have failed to find him immediately, then we definitely won't find him ever. Richard has a lot of enemies... But, captain, my patron wants to see you anyway despite the accident. He is in his house now so let's go to him. Follow me!";
			link.l1 = "Fine, Charlie. I will follow!";
			link.l1.go = "Fleetwood_house_2";
		break;
		
		case "Fleetwood_house_2":
			chrDisableReloadToLocation = true;//закрыть локацию
			bDisableFastReload = true;//закроем быстрый переход
			LocatorReloadEnterDisable("SentJons_town", "reload1_back", true);
			LocatorReloadEnterDisable("SentJons_town", "reload2_back", true);
			LocatorReloadEnterDisable("SentJons_town", "gate_back", true);//чтобы не сбежал
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "SentJons_town", "reload", "houseH1", "OpenTheDoors", -1);
			pchar.quest.Knippel_Outside.win_condition.l1 = "location";
			pchar.quest.Knippel_Outside.win_condition.l1.location = "SentJons_town";
			pchar.quest.Knippel_Outside.function = "Knippel_GoTown";
			LocatorReloadEnterDisable("SentJons_town", "houseSP3", true);
			sld = characterFromId("Fleetwood");
			LAi_SetStayType(sld);
			ChangeCharacterAddressGroup(sld, "SentJons_houseSP3_room", "goto", "goto1");
			pchar.GenQuestBox.SentJons_houseSP3_room = true;
			pchar.GenQuestBox.SentJons_houseSP3_room.box1.money = 110000;
		break;
		
		case "InFleetwoodHouse":
			dialog.text = "Richard is upstairs in his room. Go to him, he is waiting for you. I will stay here.";
			link.l1 = "Understood, Charlie. I am on my way.";
			link.l1.go = "exit";	
		break;
		
		case "Knippel_ToOfficer":
			dialog.text = "Captain, listen... Richard is under a good care now and he is safe. And I want to help you to revenge for his injury. I offer you my services as an officer. I am not good in fencing, too old for that, but I am still good in pointing and shooting cannons.";
			link.l1 = "Welcome to aboard, Charlie!";
			link.l1.go = "Knippel_ToOfficer_1";	
		break;
		
		case "Knippel_ToOfficer_1":
			LocatorReloadEnterDisable("SentJons_town", "reload1_back", false);
			LocatorReloadEnterDisable("SentJons_town", "reload2_back", false);
			LocatorReloadEnterDisable("SentJons_town", "gate_back", false);//откроем локаторы
			//Книппеля - в офицеры
			npchar.quest.OfficerPrice = sti(pchar.rank)*500;
			Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(npchar.id);
			npchar.OfficerWantToGo.DontGo = true; //не пытаться уйти
			npchar.HalfImmortal = true;//полубессмертен
			npchar.loyality = 20;
			AddDialogExitQuestFunction("LandEnc_OfficerHired");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			SetFunctionTimerCondition("GotoBridgetownOver", 0, 0, 30, false);//на все дела - 1 месяц
			AddSimpleRumourCity("They say, captain, that Richard Fleetwood himself is very interested in you. You are a very important person in our town, I can tell you.", "SentJons", 10, 3, "");
		break;
		
		case "hired":
			dialog.text = "Want something, captain?";
			link.l1 = "No, it is nothing.";
			link.l1.go = "exit";
			NextDiag.TempNode = "hired";
		break;
		
		case "MC_GoAway":
			PlaySound("VOICE\Russian\hambit\Charlie Knippel-07.wav");
			if (pchar.questTemp.HWIC.Eng == "MirageFail")
			{
				dialog.text = "You are a complete idiot, captain, chain shot to my ass! You have failed to do an elementary task - to capture the 'Mirage' without loosing the 'Valkyrie'\nOur crew won't serve under your command any longer. We are sure that sir Fleetwood will approve our decision, he doesn't like sad sacks.";
				link.l1 = "Fuck you and your master!";
				link.l1.go = "exit";
			}
			if (pchar.questTemp.HWIC.Eng == "GotoBridgetown" || pchar.questTemp.HWIC.Eng == "SeekVanBerg")
			{
				dialog.text = "You are a complete idiot, captain, chain shot to my ass! We have wasted too much time solving your personal problems\nOur crew won't serve you any longer. We are sure that sir Fleetwood will approve our decision.";
				link.l1 = "Fuck you and your master!";
				link.l1.go = "exit";
			}
			if (pchar.questTemp.HWIC.Eng == "VanBergFailInWorld")
			{
				dialog.text = "You are a complete idiot, captain, chain shot to my ass! You were told to play a lone merchant on the 'Valkyrie', and what did you do? You scared the pirate off with this flotilla!\nOur crew won't serve you any longer. We are sure that sir Fleetwood will approve our decision.";
				link.l1 = "Fuck you and your master!";
				link.l1.go = "exit";
			}
			if (pchar.questTemp.HWIC.Eng == "MirageTake")
			{
				dialog.text = "You are a complete idiot, captain, chain shot to my ass! Did you decide to waste our time doing anything but capturing the 'Mirage' and sailing to Antigua?\nOur crew won't serve you any longer. We are sure that sir Fleetwood will approve our decision.";
			link.l1 = "Fuck you and your master!";
			link.l1.go = "exit";
			}
			PChar.quest.Munity = "Deads";
			LAi_LocationFightDisable(&Locations[FindLocation("Ship_deck")], false);
			if(sti(RealShips[sti(pchar.ship.type)].basetype) == SHIP_VALCIRIA)//если сам на Валькирии
			{
				pchar.Ship.Type = GenerateShipExt(SHIP_TARTANE, true, pchar);
				pchar.Ship.name = "Boat";
				SetBaseShipData(pchar);
				SetCrewQuantityOverMax(PChar, 0);
			}
			else
			{
				for(i = 1; i < COMPANION_MAX; i++)
				{
					iTemp = GetCompanionIndex(PChar, i);
					if(iTemp > 0)
					{
						sld = GetCharacter(iTemp);
						if(sti(RealShips[sti(sld.ship.type)].basetype) == SHIP_VALCIRIA)
						{
							pchar.questTemp.HWIC.Eng.CompanionIndex = sld.Index;
							sld = GetCharacter(sti(pchar.questTemp.HWIC.Eng.CompanionIndex));
							RemoveCharacterCompanion(PChar, sld);
							AddPassenger(PChar, sld, false);
						}
					}
				}
			}
			LAi_CharacterDisableDialog(npchar);
			LAi_SetImmortal(npchar, true);
			ChangeCharacterAddressGroup(npchar, "SentJons_houseH1", "goto", "goto1");//Книппеля домой
			pchar.questTemp.HWIC.Eng = "end";
			pchar.questTemp.HWIC.Detector = "eng_fail";
			CloseQuestHeader("Holl_Gambit");
		break;
		
		case "OnCuracao":
			pchar.quest.HWICEng_toBarbadosOver.over = "yes";//снять прерывание
			dialog.text = "Greetings, captain. Glad to see you!";
			link.l1 = "Greetings, Charlie. Do you have the money? Give it to me and let's go to Willemstad for Abigail. Will you join me?";
			link.l1.go = "OnCuracao_1";	
		break;
		
		case "OnCuracao_1":
			dialog.text = "Captain, listen... There is no need to go anywhere now.";
			link.l1 = "What are talking about? This is nonsense!";
			link.l1.go = "OnCuracao_2";	
		break;
		
		case "OnCuracao_2":
			dialog.text = "I have a letter from Richard for you. And the money. But this money is not for Abigail's father, but for you. Two hundred thousand pesos. Read the letter and try to don't judge him too strictly...";
			link.l1 = "What the hell is going on these days?! Another unpleasant surprise? Give me the letter!";
			link.l1.go = "OnCuracao_3";	
		break;
		
		case "OnCuracao_3":
			DialogExit();
			NextDiag.CurrentNode = "OnCuracao_4";
			AddMoneyToCharacter(pchar, 200000);
			LAi_SetCitizenType(npchar);
			npchar.lifeday = 1;//еще денек пусть погуляет по пляжу
			pchar.quest.Holland_ShoreAttack.win_condition.l1 = "location";
			pchar.quest.Holland_ShoreAttack.win_condition.l1.location = "Curacao";
			pchar.quest.Holland_ShoreAttack.function = "CreateHollandShorePatrol";//патруль в прибрежных водах
			LocatorReloadEnterDisable("SentJons_town", "basement1_back", false);//открыть подземелье
			pchar.questTemp.HWIC.Eng = "MerdokMeeteng";
			AddQuestRecordInfo("LetterFromFleetwood", "1");
			AddQuestRecord("Holl_Gambit", "2-23");
		break;
		
		case "OnCuracao_4":
			dialog.text = "Did you read it, captain? I am ashamed of Richard and of what he did, chain shot to his... ah, fuck this. Rodenburg got enraged when he learnt about Abigail's romance with Richard. Patrols are scouting throughout Curacao and there are military ships cruising the local waters. Have you met them already? We should hurry.\Captain, do you need a skilful cannoneer? I don't need much - just a normal sea ration on a regular basis.";
			link.l1 = "I agree, Charlie. Welcome to the crew!";
			link.l1.go = "Knippel_hire";
			link.l2 = "You know, I regret helping your patron. I don't know now how to get out of this mess. Walk your own road, I had enough of surprises.";
			link.l2.go = "Knippel_exit";
		break;
		
		case "Knippel_hire":
			DialogExit();
			DeleteAttribute(npchar, "LifeDay");
			npchar.quest.OfficerPrice = sti(pchar.rank)*200;
			npchar.OfficerWantToGo.DontGo = true;
			DeleteAttribute(npchar, "CompanionDisable");//теперь можем и в компаньоны
			DeleteAttribute(npchar, "HalfImmortal");
			npchar.loyality = MAX_LOYALITY;
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, true);
			npchar.Payment = true;
			LAi_SetImmortal(npchar, false);
			LAi_SetHP(npchar, 120, 120);
			LAi_SetOfficerType(npchar);
			npchar.greeting = "knippel_hire";
			NextDiag.CurrentNode = "Knippel_officer";
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			SaveCurrentNpcQuestDateParam(npchar, "HiredDate");
		break;
		
		case "Knippel_exit":
			DialogExit();
			npchar.lifeday = 0;
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload2", "none", "", "", "", -1);
		break;
		
//------------------------------------------------против всех-----------------------------------------------
		case "Knippel_abordage":
			dialog.text = "Filthy bastard! Why have you attacked this peaceful Dutch ship? I don't have any valuable goods or gold, chain shot to my butt!";
			link.l1 = "Dutch ship? Ha-ha! Don't make me laugh, 'Dutch'. I have attacked your brigantine in order to capture you, dear Charlie. Welcome to my cargo hold. We will have a talk about where to you were sailing and why...";
			link.l1.go = "Knippel_abordage_1";	
		break;
		
		case "Knippel_abordage_1":
			AddQuestRecord("Holl_Gambit", "3-20");
            pchar.quest.Knippel_DieHard.over = "yes";
		    DoQuestCheckDelay("LAi_ReloadBoarding", 1.0);
            DialogExit();
			LAi_SetPlayerType(pchar);
			pchar.questTemp.HWIC.Self = "KnippelPrisoner";
			npchar.lifeday = 0;
			SetFunctionTimerCondition("RemoveKnippelOver", 0, 0, 1, false);//таймер до конца суток, ибо нефиг
		break;
		
		case "Knippel_prisoner":
			PlaySound("VOICE\Russian\hambit\Charlie Knippel-07.wav");
			dialog.text = "You are a devil, captain... Burn in hell for all your deeds! Scre...";
			link.l1 = "Relax, sermonist. You'd better think for your soul now so don't read me morals here.";
			link.l1.go = "Knippel_prisoner_1";
		break;
		
		case "Knippel_prisoner_1":
			dialog.text = "What are you planning, scum? What do you want from my patron and from the poor Dutch girl?";
			link.l1 = "It is not your business now, Charlie. I don't need you anymore. Get up.";
			link.l1.go = "Knippel_prisoner_2";	
		break;
		
		case "Knippel_prisoner_2":
			dialog.text = "Do you want to kill me? Worthy of such a bastard like you. Well... Fuck you!";
			link.l1 = "Get up, Charlie. And turn your back to me.";
			link.l1.go = "Knippel_prisoner_3";	
		break;
		
		case "Knippel_prisoner_3":
			DialogExit();
			LAi_SetActorType(pchar);
			sld = characterFromId("KnippelClone");
			LAi_SetActorType(sld);
			LAi_ActorAnimation(sld, "Ground_StandUp", "Kill_Knippel", 3.5);
			pchar.quest.RemoveKnippelOver.over = "yes";//снять таймер
		break;
		
		//--> ----------------------------------- офицерский блок ------------------------------------------
		case "Knippel_officer":
			dialog.text = "I am listening to you, captain, chain shot to my cave!";
			if (CheckAttribute(pchar, "questTemp.Dolly_Tieyasal") && !CheckAttribute(npchar, "quest.Tieyasal"))
			{
				Link.l4 = "Charlie, I am going to an ancient Indian city Tayasal. I will be clear, this is going to be a really dangerous trip and it is also a mystic one - we will get there through the teleport idol. Will you... join me?";
				Link.l4.go = "tieyasal";
			}
			
			////////////////////////казначей///////////////////////////////////////////////////////////
           	// boal отчёт о корабле
			if(CheckAttribute(NPChar, "treasurer") && NPChar.treasurer == 1)
			{
			    Link.l11 = "Charlie, give me a full ship report.";
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
				NextDiag.TempNode = "Knippel_officer";// не забыть менять в зависисомости от оффа
				break;
			}
			Link.l1 = "Listen to my orders!";
            Link.l1.go = "stay_follow";
			link.l2 = "It's nothing. Dismissed!";
			link.l2.go = "exit";
			NextDiag.TempNode = "Knippel_officer";
		break;
		
		/////////////////////////// ответы для казначея ///////////////////////////////////
		case "QMASTER_1":
			dialog.Text = "Welp... The guns are alrighty, we replace those that explode and keep our powder safe. What kind of a report did you expect, Captain? I am an old cannoneer, not a purser. Knippel to my yard, I am the best cannoneer mind you!";
			Link.l1 = "No arguing here, Charlie, you do know your trade. I will find a purser myself, don't you worry.";
			Link.l1.go = "exit";
		break;	

		case "QMASTER_2":
			dialog.text = "You want old Charlie to change his gun deck for bargaining with shopkeepers? Captain, I sink ships, not put up a fight for each peso. And I am positive they will rip me off in the very first colony we try this.";
			link.l1 = "But of course, Charlie. I should start looking for a proper purser.";
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
			dialog.text = "I have become really attached to you during my service, "+pchar.name+", and I don't leave my captains. I am with you!";
			link.l1 = "Thank you, Charlie! I am glad that I was right about you.";
			link.l1.go = "tieyasal_1";
		break;
		
		case "tieyasal_1":
			dialog.text = "When will we start?";
			link.l1 = "A bit later. We have to prepare ourselves for it.";
			link.l1.go = "tieyasal_2";
		break;
		
		case "tieyasal_2":
			DialogExit();
			AddQuestRecord("Tieyasal", "22");
			npchar.quest.Tieyasal = "teleport";
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		//--> блок реагирования на попытку залезть в сундук
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("You are a "+ GetSexPhrase("thief, mister! Guards, take him","thief, girl! Guards, take her") +"!!!", "Just look at that! As soon as I was lost in contemplation, you decided to check my chest! Take the thief!!!", "Guards! Robbery! Take the thief!!!");
			link.l1 = "Damn it!";
			link.l1.go = "exit";
			LAi_group_Attack(NPChar, Pchar);
		break;
		//<-- блок реагирования на попытку залезть в сундук
	}
}
