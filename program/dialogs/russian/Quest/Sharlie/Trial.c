// диалоги НПС по квесту 'Карибские нравы'
void ProcessDialogEvent()
{
	ref NPChar, sld, rColony;
	aref Link, NextDiag;
	int iTemp;
	bool bOk;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "What do you want?";
			link.l1 = "No, nothing.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		// Жерар Лекруа
		case "lecrua":
			pchar.quest.Trial_LineOver.over = "yes"; //снять таймер
			dialog.text = "Good afternoon. You must be "+GetFullName(pchar)+". Unless I'm mistaken?";
			link.l1 = "You're correct, monsieur LeCroix. Captain "+GetFullName(pchar)+" at your service. I've been recommended to you by Fadey the Muscovite...";
			link.l1.go = "lecrua_1";
		break;
		
		case "lecrua_1":
			iTemp = FindColony("Baster");
			rColony = GetColonyByIndex(iTemp);
			bOk = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
			dialog.text = "Yes, yes. Dear old Fadey has described you in detail. I knew it was you as soon as I saw you at the doorway. Tell me captain, what kind of ship do you have?";
			if(sti(pchar.ship.type) == SHIP_NOTUSED || !bOk)
			{
				link.l1 = "Uh-um... At the time being I don't have a ship, monsieur... It's temporary.";
				link.l1.go = "lecrua_noship";
			}
			else
			{
				link.l1 = "I have "+GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(RealShips[sti(pchar.ship.type)].basetype), "Name")))+", called "+pchar.ship.name+".";
				if (5-sti(RealShips[sti(pchar.ship.type)].Class) < 0) link.l1.go = "lecrua_badship";
				else link.l1.go = "lecrua_2";
			}
		break;
		
		case "lecrua_noship":
			dialog.text = "Ha! Well what kind of a captain are you then if you don't have a ship? I'm sorry, monsieur, but in that case I don't have any work to offer you. All the best, give Fadey my regards!";
			link.l1 = "Hm...";
			link.l1.go = "lecrua_exit";
			sTotalTemp = "I don't have a ship at the moment";
		break;
		
		case "lecrua_badship":
			dialog.text = "Well, this is duck soup. What kind of ship is this? This is just a big boat! Alas, monsieur, you do not fit the role. All the best, say hello to Fadey for me!";
			link.l1 = "Hm...";
			link.l1.go = "lecrua_exit";
			sTotalTemp = "my ship wasn't enough for that wretch";
		break;
		
		case "lecrua_exit":
			DialogExit();
			npchar.lifeday = 0;
			NextDiag.CurrentNode = "lecrua_repeat";
			AddQuestRecord("Trial", "3");
			AddQuestUserData("Trial", "sText", sTotalTemp);
			CloseQuestHeader("Trial");
			DeleteAttribute(pchar, "questTemp.Trial");
		break;
		
		case "lecrua_repeat":
			dialog.text = "You and I have discussed everything already, monsieur. Haven't we?";
			link.l1 = "Yes, yes, monsieur LeCroix... I'm on my way.";
			link.l1.go = "exit";
			NextDiag.TempNode = "lecrua_repeat";
		break;
		
		case "lecrua_2":
			dialog.text = "Excellent. In that case you're a good fit for me. Are you ready to set out to sea right away?";
			link.l1 = "Yes, monsieur, I'm ready. What do I have to do?";
			link.l1.go = "lecrua_3";
		break;
		
		case "lecrua_3":
			sld = characterFromId("BasTer_trader");
			dialog.text = "You must deliver a small batch of gun powder and bombs to Port-au-Prince, at French Hispaniola. Commandant has been waiting for it for a while, so don't lose any time, you have about ten days left\nRespected "+GetFullName(sld)+" will take care of delivering and loading it onto your vessel. The commandant will pay you five thousand pesos for the job.";
			link.l1 = "And that's the whole job?";
			link.l1.go = "lecrua_4";
		break;
		
		case "lecrua_4":
			dialog.text = "Oh, by no means, monsieur. The commandant will explain the main task to you to whom you will bring the gun powder and the bombs when you arrive. This freight is just a morsel of the work you have lying ahead. But don't be afraid: if you do the job well, you'll have a good opportunity to make some money.";
			link.l1 = "Great! I'm very happy about the prospect that's opening up. My ship is ready to take the cargo on board.";
			link.l1.go = "lecrua_5";
		break;
		
		case "lecrua_5":
			dialog.text = "Let's not waste any time then, captain! Make your way to your ship and prepare to embark.";
			link.l1 = "I'm going!";
			link.l1.go = "lecrua_6";
		break;
		
		case "lecrua_6":
			DialogExit();
			NextDiag.CurrentNode = "lecrua_repeat";
			AddQuestRecord("Trial", "4");
			CoolTraderHunterOnMap();
			pchar.questTemp.Trial = "fraht";
			SetFunctionTimerCondition("Trial_FrahtFail", 0, 0, 10, false); // таймер
			SetFunctionTimerCondition("Trial_LecruaHide", 0, 0, 1, false); // таймер
			// груз
			SetCharacterGoods(pchar, GOOD_BOMBS, GetCargoGoods(pchar, GOOD_BOMBS)+2500);
			SetCharacterGoods(pchar, GOOD_POWDER, GetCargoGoods(pchar, GOOD_POWDER)+2500);
		break;
		
		// Флориан Шоке
		case "florian_deck":
			pchar.quest.Trial_CannonFail.over = "yes"; //снять таймер
			dialog.text = "What could I help you with, sir?";
			link.l1 = "Good afternoon, captain. You're Florian Shoke, I presume?";
			link.l1.go = "florian_deck_1";
		break;
		
		case "florian_deck_1":
			dialog.text = "I am. And you are a messenger from Port-au-Prince, if I'm not mistaken?";
			link.l1 = "Exactly! I have delivered you fifteen cannons. I was seemingly flying on wings. I barely made it...";
			link.l1.go = "florian_deck_2";
		break;
		
		case "florian_deck_2":
			if (GetSquadronGoods(pchar, GOOD_CANNON_24) < 15)
			{
				dialog.text = "Hm. Strange sense of humour you have, sir! For some reason I don't see enough cannons on your tub for my ship.";
				link.l1 = "God damn it! We had a leak and had to throw some of the cargo overboard...";
				link.l1.go = "florian_deck_fail";
			}
			else
			{
				dialog.text = "Glad to see you, captain?..";
				link.l1 = ""+GetFullName(pchar)+". Captain "+GetFullName(pchar)+".";
				link.l1.go = "florian_deck_3";
			}
		break;
		
		case "florian_deck_3":
			dialog.text = "Nice to meet you. Let's not waste time and get straight to reloading the cannons on my ship. This isn't going be simple, god damn it!";
			link.l1 = "We'll manage somehow. The main thing is getting a lot of people involved...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Trial_TakeCannons");
		break;
		
		case "florian_deck_fail":
			dialog.text = "And why did they entrust a task like this to such a simpleton? Make your way back to your ship, captain, and do something you're better at doing: carrying passengers or products between stores. Otherwise, I doubt you'll be able to handle this. All the best!";
			link.l1 = "But...";
			link.l1.go = "florian_deck_fail_1";
		break;
		
		case "florian_deck_fail_1":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			npchar.DontDeskTalk = true; 
			RemoveCharacterGoods(pchar, GOOD_CANNON_24, GetCargoGoods(pchar, GOOD_CANNON_24));
			SetFunctionTimerCondition("Trial_RemoveFlorian", 0, 0, 1, false);
			sld = characterFromId("Lecrua");
			sld.lifeday = 0;
			AddQuestRecord("Trial", "10");
			CloseQuestHeader("Trial");
			DeleteAttribute(pchar, "questTemp.Trial");
			ChangeCharacterNationReputation(pchar, FRANCE, -3);
		break;
		
		case "florian_deck_4":
			dialog.text = "Well, looks like we're done here... I thank you for the service, captain! Take your reward two hundred doubloons.";
			link.l1 = "Thank you!";
			link.l1.go = "florian_deck_5";
		break;
		
		case "florian_deck_5":
			TakeNItems(pchar, "gold_dublon", 200);
			Log_Info("You've received 200 doubloons.");
			PlaySound("interface\important_item.wav");
			dialog.text = "But that's not all, captain. Would you like to make another two hundred fifty coins?";
			link.l1 = "Ha! Who wouldn't want fill their pocket! But it depends on what you're going to ask me to do for it...";
			link.l1.go = "florian_deck_6";
		break;
		
		case "florian_deck_6":
			dialog.text = "I won't lie, it is dangerous. As you may already know, I am waiting for a Spanish heavy galleon with a valuable cargo. The ship was put in the docks for a repair. According to my information, she was supposed to set sail yesterday but it didn’t happen\nBesides, my agent in Portobello didn't come to rendezvous point to deliver an information he gathered. I suspect that the Spanish arrested him. You should sneak in Portobello and find out why the galleon is still there and what happened to my agent. Are you in?";
			link.l1 = "I'm afraid I lack of a proper training for such an operation. I might get into trouble myself and I won't be able to help you. Alas, I cannot give you a hand.";
			link.l1.go = "florian_deck_bye";
			link.l2 = "The level of danger is high, but I'll risk it anyway. What's your man's name and what is the name of the galleon?";
			link.l2.go = "florian_deck_7";
		break;
		
		case "florian_deck_bye":
			dialog.text = "Well, you're entitled. I understand you. Goodbye then, captain, and thanks again for your help!";
			link.l1 = "All the best, monsieur Shoke.";
			link.l1.go = "florian_deck_bye_1";
		break;
		
		case "florian_deck_bye_1":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			npchar.DontDeskTalk = true; 
			SetFunctionTimerCondition("Trial_RemoveFlorian", 0, 0, 1, false);
			sld = characterFromId("Lecrua");
			sld.lifeday = 0;
			AddQuestRecord("Trial", "11");
			CloseQuestHeader("Trial");
			DeleteAttribute(pchar, "questTemp.Trial");
		break;
		
		case "florian_deck_7":
			dialog.text = "Great! The agent's name is Sylvan Laforet, but in Portobello he introduced himself as Jaime Silicio, a merchant. The galleon bears the name of 'Alacantara'. I advice you to pass through the city gates at night time, through the jungle since Portobello guards are very suspicious nowadays, not to mention that Sylvan's disappearance doesn't give you a pretty picture either. You have no longer than two days for this operation. Good luck, monsieur!";
			link.l1 = "See you soon, Monsieur Shoke...";
			link.l1.go = "florian_deck_8";
		break;
		
		case "florian_deck_8":
			bQuestDisableMapEnter = true;//закрыть карту
			pchar.GenQuest.MapClosedNoBattle = true; // доступно ожидание и sailto
			DialogExit();
			npchar.DeckDialogNode = "florian_deck_repeat";
			NextDiag.CurrentNode = "florian_deck_repeat";
			pchar.questTemp.Trial = "spy";
			AddQuestRecord("Trial", "12");
			pchar.quest.trial_spy_over.win_condition.l1 = "Timer";
			pchar.quest.trial_spy_over.win_condition.l1.date.hour  = sti(GetTime() + 2);
			pchar.quest.trial_spy_over.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 2);
			pchar.quest.trial_spy_over.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 2);
			pchar.quest.trial_spy_over.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 2);
			pchar.quest.trial_spy_over.function = "Trial_SpyTimeOver";
		break;
		
		case "florian_deck_repeat":
			dialog.text = "We've discussed everything, captain, haven't we?";
			link.l1 = "Yes, yes. I'm on my way.";
			link.l1.go = "exit";
			NextDiag.TempNode = "florian_deck_repeat";
		break;
		
		case "florian_failspy":
			pchar.quest.trial_spy_over.over = "yes"; //снять прерывание
			dialog.text = "How are things coming along, captain? What have you managed to find out?";
			link.l1 = "Things are coming along quite moderately, Monsieur Shoke. I'm not much of a spy I was disclosed fairly quickly. I had to escape the city by battle. The only thing I managed to discover is that your man, Sylvan Laforet has been arrested and is being held in jail.";
			link.l1.go = "florian_failspy_1";
		break;
		
		case "florian_failspy_1":
			dialog.text = "God damn it! That's not good... Did you find out anything about the galleon?";
			link.l1 = "No, I didn't.";
			link.l1.go = "florian_failspy_2";
		break;
		
		case "florian_failspy_2":
			dialog.text = "Damn. I really need some information on it. Anyway, I'll try sending one more scout over there... Captain, I ask you not to leave me for now. I might need your help. Will you wait till another day while I'm sniffing out information about Alacantara?";
			link.l1 = "Hm. Of course, I'll wait! I would like to rehabilitate myself for a failure.";
			link.l1.go = "florian_9";
			link.l2 = "I don't think so. Apparently I'm too bad in such games. I'm going homeward.";
			link.l2.go = "florian_failspy_3";
		break;
		
		case "florian_failspy_3":
			dialog.text = "Well, that's your choice. All the best, captain.";
			link.l1 = "Farewell, Monsieur Shoke.";
			link.l1.go = "florian_failspy_4";
		break;
		
		case "florian_failspy_4":
			DialogExit();
			bQuestDisableMapEnter = false;
			DeleteAttribute(pchar, "GenQuest.MapClosedNoBattle");
			LAi_CharacterDisableDialog(npchar);
			npchar.DontDeskTalk = true; 
			SetFunctionTimerCondition("Trial_RemoveFlorian", 0, 0, 1, false);
			sld = characterFromId("Lecrua");
			sld.lifeday = 0;
			CloseQuestHeader("Trial");
			DeleteAttribute(pchar, "questTemp.Trial");
		break;
		
		case "florian_failspy_5":
			pchar.quest.trial_spy_over.over = "yes"; //снять прерывание
			dialog.text = "How are things coming along, captain? What have you managed to find out?";
			link.l1 = "Things are coming along quite moderately, Monsieur Shoke. I'm not much of a spy, I was disclosed fairly quickly. The only thing I managed to discover was that your man, Sylvan Laforet has been arrested and is being held.";
			link.l1.go = "florian_failspy_1";
		break;
		
		case "florian_9":
			dialog.text = "Then make your way to your ship, captain. Tomorrow at about the same time, or a little later, you'll have to visit me. Maybe by that time I'll have found something out. Don't set foot on the shore, wait for me on the ship!";
			link.l1 = "All right. Will do.";
			link.l1.go = "florian_10";
		break;
		
		case "florian_10":
			dialog.text = "And captain: take this purse. Your efforts weren't completely in vain after all. At least we know what happened to poor old Sylvan...";
			link.l1 = "...";
			link.l1.go = "florian_11";
		break;
		
		case "florian_11":
			DialogExit();
			Island_SetReloadEnableGlobal("Portobello", false);//закрыть остров	
			npchar.DeckDialogNode = "florian_deck_wait";
			NextDiag.CurrentNode = "florian_deck_wait";
			pchar.questTemp.Trial = "spy_wait";
			pchar.quest.Trial_spyfail_wait.win_condition.l1 = "Timer";
			pchar.quest.Trial_spyfail_wait.win_condition.l1.date.hour  = sti(GetTime()+rand(12));
			pchar.quest.Trial_spyfail_wait.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.Trial_spyfail_wait.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.Trial_spyfail_wait.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.Trial_spyfail_wait.function = "Trial_Spyfail_NextStage";
			TakeNItems(pchar, "purse2", 1);
			Log_Info("You've received a purse of doubloons");
		break;
		
		case "florian_deck_wait":
			dialog.text = "Captain, I don't have any news at the moment. We're still waiting...";
			link.l1 = "All right...";
			link.l1.go = "exit";
			NextDiag.TempNode = "florian_deck_wait";
		break;
		
		case "florian_12":
			pchar.quest.trial_spy_over.over = "yes"; //снять прерывание
			dialog.text = "How are things coming along, captain? What have you managed to find out?";
			link.l1 = "It's done. Your man, Sylvan Laforet, was arrested and is being held in jail. It is over for him.";
			link.l1.go = "florian_13";
		break;
		
		case "florian_13":
			dialog.text = "God damn it! That's dreadful... Did you find out anything about the galleon?";
			link.l1 = "Yes. She is being prepared to embark for a while now, but the governor of Portobello is intending on holding her at the dock. Right now he's waiting for a bark called 'Puebla' to arrive from Cartagena with a cargo of gunpowder for the 'Alcantara'. According to sailor from the galleon they don`t have enough of it.";
			link.l1.go = "florian_14";
		break;
		
		case "florian_14":
			dialog.text = "How interesting!";
			link.l1 = "But if Puebla doesn't arrive within three days then the Alacantara will stop waiting and set sail.";
			link.l1.go = "florian_15";
		break;
		
		case "florian_15":
			dialog.text = "Excellent work, captain! I'm very pleased with you. Here, take your reward. You've totally earned it!";
			link.l1 = "Thank you! Do you have any other assignments for me?";
			link.l1.go = "florian_16";
		break;
		
		case "florian_16":
			TakeNItems(pchar, "gold_dublon", 250);
			Log_Info("You've received 250 doubloons");
			PlaySound("interface\important_item.wav");
			dialog.text = "You are reading my mind, captain! Yes, damn it! Since Alacantara has a lack of gun powder, I can let her sail into the open sea and then force her to engage in a protracted naval fight, in which their supplies will run off before ours\nYou should make sure that bark Puebla never reaches Portobello. I can't sail close to the shores, patrols will notice my frigate easily and I might never intercept Alacantara if that would be the case\nAnd you can deal with her on your own. Find her and get rid of her. Sink her or board her, I don't care. Just prevent this egg shell from getting here!\nIf you succeed, than go to Guadeloupe and see Gerard LeCroix, I believe that you already know him, don't you? He will pay you the coin you deserve.";
			link.l1 = "Deal! I'll be on my way to cut off the Puebla!";
			link.l1.go = "florian_19";
		break;
		
		case "florian_17":
			dialog.text = "Very good that you've arrived, captain. I've just received important information from my spy and I have an important errand for you.";
			link.l1 = "I'm all ears.";
			link.l1.go = "florian_18";
		break;
		
		case "florian_18":
			dialog.text = "The 'Alacantara' is ready to set sail, but the galleon's captain is waiting for bark 'Puebla' to arrive first from Cartagena loaded with ammunition. Thing is that Alacantara doesn't have enough gun powder, so the Spanish are not ready to set sail yet. But captain' patience has limits and if Puebla won't come in three days then the galleon will leave Portobello\nThe 'Alacantara' has a lack of gun powder, I can let her sail into the open sea and then force her to engage in a protracted naval fight, in which their supplies will run off before ours. Your objective is to intercept the bark and to destroy her. Sink her or board her, I don't care. Just prevent this egg shell from getting here!\nIf you succeed than go to Guadeloupe and see Gerard LeCroix, I believe that you already know him, don't you? He will pay you the coin you deserve.";
			link.l1 = "Deal! I'll be on my way to cut off the Puebla!";
			link.l1.go = "florian_19";
		break;
		
		case "florian_19":
			DialogExit();
			Island_SetReloadEnableGlobal("Portobello", true); // открыть остров
			bQuestDisableMapEnter = false;//открыть карту
			DeleteAttribute(pchar, "GenQuest.MapClosedNoBattle");
			LAi_CharacterDisableDialog(npchar);
			npchar.DontDeskTalk = true; 
			SetFunctionTimerCondition("Trial_RemoveFlorian", 0, 0, 1, false);
			Trial_CreatePueblaBarqueInWorld();
			pchar.questTemp.Trial = "puebla";
			AddQuestRecord("Trial", "19");
		break;
		
		// испанский офицер в таверне
		case "tavern_officer":
			dialog.text = "So, who do we have here? Another French nark? How interesting! Would you like to see Jaime Silicio? Well then, I'll introduce you to him right inside our prison. Take him, boys!";
			link.l1 = "Ah-argh! Just go ahead and try!";
			link.l1.go = "tavern_officer_1";
		break;
		
		case "tavern_officer_1":
			DialogExit();
			chrDisableReloadToLocation = true;//закрыть локацию
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			LAi_SetWarriorTypeNoGroup(npchar);
            LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
            LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
            LAi_group_SetCheck("EnemyFight", "Trial_AfterTavernFight");
			AddDialogExitQuest("MainHeroFightModeOn");
			SetNationRelation2MainCharacter(SPAIN, RELATION_ENEMY);
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
	}
}
