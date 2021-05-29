void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i, n, iTemp;
	string sTemp;
	
	DeleteAttribute(&Dialog,"Links");
	
	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	bool ok;
    int iTest;
    ref rColony;
    string sFrom_sea = "";
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "";
			link.l1 = "";
			link.l1.go = "exit";
		break;
		
		//вестовой
		case "Regata_Cureer":
			dialog.text = "Good day. Are you captain " + GetFullName(pchar) + "?";
			link.l1 = "Yes, it is me. And what is the deal?";
			link.l1.go = "Regata_Cureer_1";
		break;
		
		case "Regata_Cureer_1":
			dialog.text = "I have a letter for you from the governor of Jamaica, sir James Carlisle.";
			link.l1 = "Whoa! I didn't expect... And what does the governor want from me?";
			link.l1.go = "Regata_Cureer_2";
		break;
		
		case "Regata_Cureer_2":
			dialog.text = "Read the letter, sir. In brief, you are offered to take part in the regatta, time trial across all over the archipelago. Rumours about your naval skills and fast traveling around the sea were not unnoticed.";
			link.l1 = "Incredible! Well... I will consider it.";
			link.l1.go = "Regata_Cureer_3";
			GiveItem2Character(pchar, "letter_open");
			ChangeItemDescribe("letter_open", "itmdescr_letter_open_Regata");
			AddQuestRecordInfo("RegataLetter", "1");
		break;
		
		case "Regata_Cureer_3":
			if (Pchar.BaseNation == SPAIN || Pchar.BaseNation == HOLLAND)
			{
				dialog.text = "Also I am to provide you with a free access to the port of Port Royal. Here is a license for 30 days. Now my mission is complete. Goodbye, captain.";
				link.l1 = "Thanks. The license is most welcome. Farewell!";
				link.l1.go = "Cureer_exit";
				GiveNationLicence(HOLLAND, 30);
			}
			else
			{
				dialog.text = "Good. Now my mission is complete. Goodbye, captain.";
				link.l1 = "Farewell!";
				link.l1.go = "Cureer_exit";
			}
		break;
		
		case "Cureer_exit":
			chrDisableReloadToLocation = false;
			bDisableFastReload = false;
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload4_back", "none", "", "", "", -1);
			pchar.questTemp.Regata.ToPortRoyal = "true";
			SetFunctionTimerCondition("RegataToPortRoyalTimeOver", 0, 0, 31, false);
		break;
		
		//распорядитель регаты
		case "Regata_Head":
			if (CheckAttribute(pchar, "questTemp.Regata.Begin"))
			{
				dialog.text = "Good day. You are taking part in the regatta, I take it?";
				link.l1 = "Precisely, sir. My name is " + GetFullName(pchar) + ". I have received the invitation.";
				link.l1.go = "Regata_Head_1";
			}
			else
			{
				dialog.text = "Want something, sir?";
				link.l1 = "No, it is nothing. I am leaving already.";
				link.l1.go = "exit";
				NextDiag.TempNode = "Regata_Head";
			}
		break;
		
		case "Regata_Head_1":
			iTest = FindColony("PortRoyal"); 
			if (iTest != -1)
			{
				rColony = GetColonyByIndex(iTest);
			}
			ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
			if(sti(Pchar.Ship.Type) != SHIP_NOTUSED && ok)//проверка на наличие корабля в порту
			{
				dialog.text = "I am glad to meet you, captain " + GetFullName(pchar) + ". Let's start then. You are already aware about the basics from the letter, right? Luggers only and she has to be the one vessel in your squadron in order to participate in the regatta. Have you fulfilled these terms?";
				if ((GetCompanionQuantity(pchar) > 1) || sti(RealShips[sti(pchar.ship.type)].basetype) != SHIP_LUGGER)
				{
					link.l1 = "Not yet. I will do it now and I'll be back soon.";
					link.l1.go = "exit";
					NextDiag.TempNode = "Regata_Head_repeat";
				}
				else
				{
					link.l1 = "Yes, I have.";
					link.l1.go = "Regata_Head_2";
				}
			}
			else
			{
				dialog.text = "You have come to take part in regatta but where is your ship, captain?";
				link.l1 = "Excuse me, sir. I will get my ship to the port immediately.";
				link.l1.go = "exit";
				NextDiag.TempNode = "Regata_Head_repeat";
			}
		break;
		
		case "Regata_Head_repeat":
			if (CheckAttribute(pchar, "questTemp.Regata.Begin"))
			{
				iTest = FindColony("PortRoyal"); 
				if (iTest != -1)
				{
					rColony = GetColonyByIndex(iTest);
				}
				ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
				if(sti(Pchar.Ship.Type) != SHIP_NOTUSED && ok)//проверка на наличие корабля в порту
				{
					dialog.text = "Ah, it is you again. Have you done everything to fulfil terms of the regatta?";
					if ((GetCompanionQuantity(pchar) > 1) || sti(RealShips[sti(pchar.ship.type)].basetype) != SHIP_LUGGER)
					{
						link.l1 = "Not yet. I will do it now and I'll be back soon.";
						link.l1.go = "exit";
						NextDiag.TempNode = "Regata_Head_repeat";
					}
					else
					{
						link.l1 = "Yes, I have.";
						link.l1.go = "Regata_Head_2";
					}
				}
				else
				{
					dialog.text = "Captain, we have nothing to discuss until I see your ship on a roadstead. Do you get it or should I repeat myself?";
					link.l1 = "Excuse me, sir. I will get my ship to the port immediately.";
					link.l1.go = "exit";
					NextDiag.TempNode = "Regata_Head_repeat";
				}
			}
			else
			{
				dialog.text = "Want something, sir?";
				link.l1 = "No, it is nothing. I am leaving already.";
				link.l1.go = "exit";
				NextDiag.TempNode = "Regata_Head";
			}
		break;
		
		case "Regata_Head_2":
			dialog.text = "Fine. Now the next item. What is the name of your ship?";
			link.l1 = "'"+pchar.Ship.Name+"'.";
			link.l1.go = "Regata_Head_3";
		break;
		
		case "Regata_Head_3":
			dialog.text = "Since the regatta is hosted by English authorities and due to the fixed rules your ship's name must be changed for a time of the event. Don't worry, it concerns every participant.";
			link.l1 = "They say that it is a bad token to change your ship's name.";
			link.l1.go = "Regata_Head_4";
		break;
		
		case "Regata_Head_4":
			dialog.text = "You may change the name back after the regatta. So, your lugger will carry the name 'Santa Catherina'.";
			link.l1 = "I understand it, sir, I will change the name.";
			link.l1.go = "Regata_Head_5";
			pchar.Ship.Name = "Santa Catherina";
		break;
		
		case "Regata_Head_5":
// 10Aug17 change "provide your" to "provide you"
			dialog.text = "Now let's talk about the regatta itself. Listen carefully. I will also provide you with a rule paper.\nThe regatta starts and ends in Port Royal. There are five passages\nFirst one is Port Royal to Belize, West Main\nSecond is Belize to Port-au-Prince, Hispaniola\Third is Port-au-Prince to St.John's, Antigua\nFourth is St.John's to Bridgetown, Barbados\nAnd the last one is Bridgetown to Port Royal\nAm I clear?";
			link.l1 = "Sure, sir.";
			link.l1.go = "Regata_Head_6";
		break;
		
		case "Regata_Head_6":
			dialog.text = "Splendid. You must check in at every port office of following cities: Belize, Port-au-Prince, St.John's, Bridgetown. You will be disqualified if you miss any of these cities or break the right sequence\nThe offices will stay open twenty four hours during the course of the regatta. Knock the door and they will let you in.";
			link.l1 = "Understood.";
			link.l1.go = "Regata_Head_7";
		break;
		
		case "Regata_Head_7":
			dialog.text = "It is forbidden to change the ship and to add more ships to your squadron. This will be verified in every city, consider that.";
			link.l1 = "I will consider that. Who is normally considered as a winner and let's talk prizes.";
			link.l1.go = "Regata_Head_8";
		break;
		
		case "Regata_Head_8":
			dialog.text = "Only the one winner in the regatta - the captain whose ship will be the first to reach Port-Royal. Prize is very valuable. The winner will get a big sum - 250 000 pesos. Also, he will be granted with a set of valuable gifts.";
			link.l1 = "So, losers get nothing?";
			link.l1.go = "Regata_Head_9";
		break;
		
		case "Regata_Head_9":
			dialog.text = "Exactly. Plus, a lot of rich and poor citizens of English colonies make bets on the winner of the regatta. You can also bet on... yourself. Normally every captain does so. If you win, you will earn even more and don't forget about the motivation. Usually I accept the bets\nAre you betting on your victory?";
			link.l1 = "Ha! Sure, I am. How much can I bet?";
			link.l1.go = "Regata_rate";
			link.l2 = "I will think about it. Perhaps I will bet.";
			link.l2.go = "Regata_Head_10";
		break;
		
		case "Regata_Head_10":
			if (CheckAttribute(pchar, "questTemp.Regata.Begin"))
			{
				dialog.text = "Think if you want. You have some time before the regatta starts.";
				link.l1 = "Fine. When does it start?";
				link.l1.go = "Regata_Head_11";
				DeleteAttribute(pchar, "questTemp.Regata.Rate");
				pchar.questTemp.Regata.Ratenext = "true";
			}
			else
			{
				dialog.text = "Think if you want. You have some time before the regatta starts.";
				link.l1 = "Fine.";
				link.l1.go = "exit";
			}
		break;
		
		case "Regata_Head_11":
			CreateRegataAdversaries();
			dialog.text = "Three days later, at twelve o'clock at midday. Come to the pier. Don't be late. You will have five competitors.\n"+pchar.questTemp.Regata.AdversaryName.a+", of the "+pchar.questTemp.Regata.AdversaryShipName.a+"\n"+pchar.questTemp.Regata.AdversaryName.b+", of the "+pchar.questTemp.Regata.AdversaryShipName.b+"\n"+pchar.questTemp.Regata.AdversaryName.c+", of the "+pchar.questTemp.Regata.AdversaryShipName.c+"\n"+pchar.questTemp.Regata.AdversaryName.d+", of the "+pchar.questTemp.Regata.AdversaryShipName.d+"\n"+pchar.questTemp.Regata.AdversaryName.e+", of the "+pchar.questTemp.Regata.AdversaryShipName.e+"\nAll of them are seasoned captains. Well, apparently this is it. Take the rule paper just in case. See you at the start!";
			link.l1 = "Goodbye, sir.";
			if (Pchar.BaseNation == SPAIN || Pchar.BaseNation == HOLLAND) link.l1.go = "Regata_Head_13";
			else link.l1.go = "Regata_Head_12";
		break;
		
		case "Regata_Head_12":
			DialogExit();
			pchar.quest.RegataToPortRoyalTimeOver.over = "yes";//снять таймер
			SetFunctionTimerCondition("Regata_SetTime", 0, 0, 3, false);
			pchar.quest.Regata_Lost.win_condition.l1 = "Timer";
			pchar.quest.Regata_Lost.win_condition.l1.date.hour  = 13.0;
			pchar.quest.Regata_Lost.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 3);
			pchar.quest.Regata_Lost.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 3);
			pchar.quest.Regata_Lost.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 3);
			pchar.quest.Regata_Lost.function = "Regata_Lost";
			pchar.quest.Regata_Start.win_condition.l1 = "Timer";
			pchar.quest.Regata_Start.win_condition.l1.date.hour  = 12.0;
			pchar.quest.Regata_Start.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 3);
			pchar.quest.Regata_Start.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 3);
			pchar.quest.Regata_Start.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 3);
			pchar.quest.Regata_Start.win_condition.l2 = "locator";
			pchar.quest.Regata_Start.win_condition.l2.location = "Portroyal_town";
			pchar.quest.Regata_Start.win_condition.l2.locator_group = "reload";
			pchar.quest.Regata_Start.win_condition.l2.locator = "reload1_back";
			pchar.quest.Regata_Start.function = "Regata_Start";
			AddQuestRecordInfo("RegataRules", "1");
			NextDiag.CurrentNode = "Regata_Prepare";
			DeleteAttribute(pchar, "questTemp.Regata.Begin");
			pchar.questTemp.Regata.Prepare = "true";
		break;
		
		case "Regata_Head_13":
			dialog.text = "Wait! I'll give you the 30 days license for visiting English and French ports. The regatta won't last more than a month. Please, take it.";
			link.l1 = "Thanks!";
			link.l1.go = "Regata_Head_12";
			GiveNationLicence(HOLLAND, 30);
		break;
		
		case "Regata_rate":
			dialog.text = "How much are you betting on?";
			link.l1 = "";
			Link.l1.edit = 4;
			link.l1.go = "Regata_rate_1";
			link.l2 = "I suppose, I still need some time to think.";
			link.l2.go = "Regata_Head_10";
		break;
		
		case "Regata_rate_1":
			int iQty = sti(dialogEditStrings[4]);
			pchar.questTemp.Regata.Rate = sti(iQty);
			if (iQty < 10000)
			{
				dialog.text = "Sir, this is not funny. Why is that meanness? I won't work with such a small sum.";
				link.l1 = "Beg pardon... Let's reconsider the stake.";
				link.l1.go = "Regata_rate";
				break;
			}
			if (iQty > 100000)
			{
				dialog.text = "Sir, I can't accept such stakes due to the rules of the regatta. Reduce it to the reasonable value.";
				link.l1 = "Too bad. Let's reconsider the sum.";
				link.l1.go = "Regata_rate";
				break;
			}
			dialog.text = ""+iQty+"? That is a fine stake. I am ready to accept it. Your money, sir?";
			if (makeint(Pchar.money) >= sti(pchar.questTemp.Regata.Rate))
			{
				link.l1 = "Please, take it.";
				link.l1.go = "Regata_rate_2";
			}
			link.l2 = "I don't have enough coins now. I will come to you later and will make a stake. And I will think more on it, perhaps I will reconsider the sum.";
			link.l2.go = "Regata_Head_10";
		break;
		
		case "Regata_rate_2":
			AddMoneyToCharacter(pchar, -sti(pchar.questTemp.Regata.Rate));
			pchar.questTemp.Regata.Advantage = sti(pchar.questTemp.Regata.Rate)*(1.5+frand(1.5)); // dlc
			dialog.text = "Splendid! Now all you need is to be the first and the prize is yours. It's final value could vary, it all depends on how many people will stake on you in the end.";
			if (!CheckAttribute(pchar, "questTemp.Regata.Ratenext"))
			{
				link.l1 = "I see. When is the start of the regatta?";
				link.l1.go = "Regata_Head_11";
			}
			else
			{
				link.l1 = "I see. I will be waiting for the start. See you!";
				link.l1.go = "exit";
				DeleteAttribute(pchar, "questTemp.Regata.Ratenext");
				NextDiag.TempNode = "Regata_Prepare";
			}
		break;
		
		case "Regata_Prepare":
			dialog.text = "Are you here again, captain " + GetFullName(pchar) + "? What do you want?";
			if (!CheckAttribute(pchar, "questTemp.Regata.Rate"))
			{
				link.l1 = "I want to bet on my victory.";
				link.l1.go = "Regata_rate";
			}
			link.l2 = "No, it is nothing. Just wanted to greet you.";
			link.l2.go = "exit";
			NextDiag.TempNode = "Regata_Prepare";
		break;
		
		//старт регаты
		case "Regata_CitMan":
			dialog.text = RandPhraseSimple(LinkRandPhrase("Captain, are you first-timer? Let me tell you that you should be careful. Your competitors might set up a very unpleasant surprises for you...","Captain, I have made a stake on you. Don't disappoint me!","Captain, the locals in the ports of the regatta might offer you to buy something. It is often can be really useful. Consider that."), LinkRandPhrase("Have a safe sail, captain!","Captain, please be careful, Castilians often hunt the luggers of participants in the Spanish waters.","I have heard that some shady characters often offer their 'services' to the regatta captains. It is your call to accept their offers or not."));
			link.l1 = "Yes, yes, of course...";
			link.l1.go = "exit";
			NextDiag.TempNode = "Regata_CitMan";
		break;
		
		case "Regata_CitWom":
			dialog.text = LinkRandPhrase("Captain, me and my husband has bet ten thousands on your victory. Don't let us down!","Captain! I wish you luck!","Ah, you such a brave and courageous captain...");
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "Regata_CitWom";
		break;
		
		case "Regata_CitHorse":
			dialog.text = LinkRandPhrase("Hey, sailor! Wave to the beauty! I will be waiting for your return!","Hey, salty sailor! Madam has said that she will give me as a prize to the winner of regatta for free... Try to win, you are so handsome!","Don't forget to visit us when you will be back, handsome, we will pleasure you according to the highest standards!");
			link.l1 = "Fine, sweetie.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Regata_CitHorse";
		break;
		
		case "Regata_Prepare_1":
			if (sti(environment.time) < 12.0)
			{
				dialog.text = "Captain, the regatta starts at 12 o'clock. You can rest now, we are preparing the festive part. Come back at midday, your competitors will do the same.";
				link.l1 = "Me and my crew are ready, sir! I am waiting for the start...";
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = "Here you are, captain.";
				link.l1 = "Me and my crew are ready, sir! I am waiting for the start...";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "Regata_Prepare_1";
		break;
		
		case "Regata_Start":
			dialog.text = "So, gentlemen, here we are. I announce the start of the regatta. You know the rules. The one who will return here first will be praised as a winner. Ladies and gentlemen let's wish luck to our brave captains!\nGentlemen! Are you up? Ready! Steady! Go!";
			link.l1 = "...";
			link.l1.go = "Regata_Start_1";
		break;
		
		case "Regata_Start_1":
			DialogExit();
			PlaySound("people fight\mushketshot.wav");
			log_info("The regatta has started! Get aboard! Head to Belize!");
			for (i=1; i <=5; i++)
			{
				sld = characterFromId("Regata_Cap_F"+i);
				LAi_ActorGoToLocation(sld, "reload", "reload1_back", "none", "", "", "", -1);
			}
			Island_SetReloadEnableGlobal("Jamaica", false);//на остров нельзя
			SetFunctionTimerCondition("ReturnJamaicaNorm", 0, 0, 1, false);//таймер на возврат нормы
			LocatorReloadEnterDisable("Portroyal_town", "reload1_back", false);//откроем выход в море
			DeleteAttribute(pchar, "questTemp.Regata.Prepare");
			pchar.questTemp.Regata.Go = "true";
			pchar.questTemp.Regata.Town = "Beliz";
			pchar.quest.Regata_PU.win_condition.l1 = "locator";
			pchar.quest.Regata_PU.win_condition.l1.location = "Beliz_town";
			pchar.quest.Regata_PU.win_condition.l1.locator_group = "reload";
			pchar.quest.Regata_PU.win_condition.l1.locator = "reload10_back";
			pchar.quest.Regata_PU.win_condition.l2 = "Night";
			pchar.quest.Regata_PU.function = "RegataPU_Open";//вход в ПУ ночью
			//ситуации
			pchar.quest.Regata_ShYarder.win_condition.l1 = "location";
			pchar.quest.Regata_ShYarder.win_condition.l1.location = "Beliz_town";
			pchar.quest.Regata_ShYarder.function = "RegataShipyarder";
			sld = characterFromId("Beliz_shipyarder");
			LAi_RemoveLoginTime(sld);
		break;
		//старт регаты
		
		//верфист с парусами
		case "Regata_Shipyarder":
			dialog.text = "Greeting, captain! I am informed that you are taking part in the Caribbean regatta...";
			link.l1 = "It is true. News are truly spread across the archipelago faster than a wind.";
			link.l1.go = "Regata_Shipyarder_1";
		break;
		
		case "Regata_Shipyarder_1":
			dialog.text = "They do, captain. I've got a proposal for you. It concerns your ship and the regatta.";
			link.l1 = "Heh! Interesting. I am listening to you, mister.";
			link.l1.go = "Regata_Shipyarder_2";
		break;
		
		case "Regata_Shipyarder_2":
			dialog.text = "Sir, I have a set of perfect sails for a lugger, they are made of the best cotton. These sails will increase your ship's acceleration and give you an advantage in time over opponents\nI am ready to sell them to you, of course if you are buying.";
			link.l1 = "How much do you want for these sails?";
			link.l1.go = "Regata_Shipyarder_3";
		break;
		
		case "Regata_Shipyarder_3":
			dialog.text = "Only 15 000 pesos. You must admit that this is a very modest price for such a thing and in such situation.";
			if (makeint(Pchar.money) >= 15000)
			{
				link.l1 = "I agree. I am buying these new sails for my lugger from you. Here, take your money. Would you be kindly to deliver them to my ship while I am checking in.";
				link.l1.go = "Regata_Shipyarder_4";
			}
			link.l2 = "I don't have such money. So I won't be able to buy your sails.";
			link.l2.go = "Regata_Shipyarder_exit";
		break;
		
		case "Regata_Shipyarder_4":
			AddMoneyToCharacter(pchar, -15000);
			dialog.text = "It will be done, sir. You won't regret it. Besides these sails are nicely colored in blue. Your beauty will appreciate it.";
			link.l1 = "Fine then! Well, I have to go and you do the sails.";
			link.l1.go = "Shipyarder_exit";
			for (i=1; i <=5; i++)
			{
				if (i==1) sTemp = "a";
				if (i==2) sTemp = "b";
				if (i==3) sTemp = "c";
				if (i==4) sTemp = "d";
				if (i==5) sTemp = "e";
				pchar.questTemp.Regata.AdversarySecondTransition.Time.(sTemp) = sti(pchar.questTemp.Regata.AdversarySecondTransition.Time.(sTemp))+12;//выиграл 12 часов у всех
				log_testinfo(FindRussianDaysString(pchar.questTemp.Regata.AdversarySecondTransition.Time.(sTemp)));
			}
			RealShips[sti(Pchar.Ship.Type)].ship.upgrades.sails = 3;
			SetSailsColor(Pchar, 5);
		break;
		
		case "Regata_Shipyarder_exit":
			dialog.text = "What a pity. Well, it is your choice. Farewell, captain.";
			link.l1 = "Goodbye!";
			link.l1.go = "Shipyarder_exit";
			pchar.questTemp.Regata.AdversarySecondTransition.Time.d = sti(pchar.questTemp.Regata.AdversarySecondTransition.Time.d)-16;//четвертый соперник выиграл 16 часов
			log_testinfo(FindRussianDaysString(pchar.questTemp.Regata.AdversarySecondTransition.Time.e));
		break;
		
		case "Shipyarder_exit":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload5_back", "Beliz_Shipyard", "sit", "sit1", "ReturnRegataSYNorm", 5);
		break;
		//верфист с парусами
		
		//контрики с пушками
		case "Regata_Contra":
			dialog.text = "Hello, captain " + GetFullName(pchar) + ". We have a talk to you... actually, a business proposal.";
			link.l1 = "Hm. Interesting and how do you know who I am?";
			link.l1.go = "Regata_Contra_1";
		break;
		
		case "Regata_Contra_1":
			dialog.text = "Captain, this part was relatively easy. There is the regatta is going on and you are taking part in it, you are famous.";
			link.l1 = "I see. Well, speak your mind.";
			link.l1.go = "Regata_Contra_2";
		break;
		
		case "Regata_Contra_2":
			if (sti(pchar.questTemp.Regata.Index != 1))
			{
				sTemp = pchar.questTemp.Regata.ContraIndex;
				dialog.text = "We are aware that there is one more participant towards you - "+pchar.questTemp.Regata.AdversaryName.(sTemp)+" of the "+pchar.questTemp.Regata.AdversaryShipName.(sTemp)+". He left the port not long ago and soon he will sailing by the Gonaives cape.";
			}
			else
			{
				dialog.text = "We are aware that there is one more participant right behind you - "+pchar.questTemp.Regata.AdversaryName.b+" of the "+pchar.questTemp.Regata.AdversaryShipName.b+". He will be here in a few hours.";
			}
			link.l1 = "You are very well informed.";
			link.l1.go = "Regata_Contra_3";
		break;
		
		case "Regata_Contra_3":
			if (sti(pchar.questTemp.Regata.Index != 1)) sTemp = "letting you pass ahead of him and take his position";
			else sTemp = "therefore you will be taking a lead for a long time";
			dialog.text = "Absolutely. Now let's cut to the chase. We offer you our help for money from you. We have placed four cannons from our ship at cape behind Gonaives bay. Any regatta ship must double it\nThe guns are loaded with chain shots. If we make a deal, I will tell our cannon friends to ruin your competitor's sails, so he will be forced to lose time repairing them, "+sTemp+".";
			link.l1 = "How much do you want for this service?";
			link.l1.go = "Regata_Contra_4";
			link.l2 = "No. I am not going to use such methods to win. You were wrong about me. Farewell, gentlemen.";
			link.l2.go = "Regata_Contra_exit";
		break;
		
		case "Regata_Contra_exit":
			dialog.text = "Well captain, it is your choice. Farewell.";
			link.l1 = "Thanks for the information about the cape. I will stay away from it.";
			link.l1.go = "Contra_exit";
			ChangeCharacterComplexReputation(pchar, "nobility", 3);
		break;
		
		case "Regata_Contra_4":
			if (sti(pchar.questTemp.Regata.Index != 1)) iTemp = 50000;
			else iTemp = 30000;
			dialog.text = "Not much. Only "+iTemp+" pesos. And one of your competitors will loose almost two days because of our... operation, ha-ha!";
			if (makeint(Pchar.money) >= iTemp)
			{
				link.l1 = "Heh! You talk sense, my friend! I am paying. But what about guarantees that you will do your job? And that you won't shoot my ship when I will be passing the cape?";
				link.l1.go = "Regata_Contra_5";
			}
			link.l2 = "I don't have such money. So I won't be able to use your services.";
			link.l2.go = "Regata_Contra_exit";
		break;
		
		case "Regata_Contra_5":
			dialog.text = "Captain, we are smugglers, not pirates. We are honest men... in our way. You must had used our services before, right? You have my word. You can rely on it.";
			link.l1 = "Fair enough, take your money.";
			link.l1.go = "Regata_Contra_6";
		break;
		
		case "Regata_Contra_6":
			ChangeCharacterComplexReputation(pchar, "nobility", -3);
			dialog.text = "You will be pleased by this deal, captain. And I will let my gun boys know about it immediately. Good luck!";
			link.l1 = "Same to you...";
			link.l1.go = "Contra_exit";
			if (sti(pchar.questTemp.Regata.Index != 1))
			{
				AddMoneyToCharacter(pchar, -50000);
				sTemp = pchar.questTemp.Regata.ContraIndex;
				pchar.questTemp.Regata.AdversaryThirdTransition.Time.(sTemp) = sti(pchar.questTemp.Regata.AdversaryThirdTransition.Time.(sTemp))+48;//задержка на 48 часов
				log_testinfo(FindRussianDaysString(pchar.questTemp.Regata.AdversaryThirdTransition.Time.(sTemp)));
			}
			else
			{
				AddMoneyToCharacter(pchar, -30000);
				pchar.questTemp.Regata.AdversaryThirdTransition.Time.b = sti(pchar.questTemp.Regata.AdversaryThirdTransition.Time.b)+36;//задержка на 36 часов
				log_testinfo(FindRussianDaysString(pchar.questTemp.Regata.AdversaryThirdTransition.Time.b));
			}
		break;
		
		case "Contra_exit":
			DialogExit();
			for (i=1; i<=2; i++)
			{
				sld = characterFromId("RegataContra_"+i);
				LAi_SetActorType(sld);
				LAi_ActorRunToLocation(sld, "quest", "quest2", "none", "", "", "", 10.0);
			}
		break;
		//контрики с пушками
		
		//падре
		case "Regata_Padre":
			pchar.questTemp.Regata.BranderName = GenerateRandomNameToShip(ENGLAND);
			dialog.text = "Good day to you, my son. I want to greet you and to humbly ask you: don't you want to contribute to the parish treasury as a loyal servant of England and our great Lord?";
			link.l1 = "Padre, people do charity, because of their souls' call not because of compulsion. I am starting to think that everyone at the archipelago has decided to rob the captain of the regatta...";
			link.l1.go = "Regata_Padre_exit";
			link.l2 = "Sure, holy father. How much would be enough?";
			link.l2.go = "Regata_Padre_1";
		break;
		
		case "Regata_Padre_1":
			dialog.text = "Just as much as your wish and possibilities will let you, my son. Our parish will be glad for even the smallest sum.";
			Link.l1.edit = 4;			
			link.l1 = "";
			link.l1.go = "Regata_Padre_2";
		break;
		
		case "Regata_Padre_2":
			iTemp = sti(dialogEditStrings[4]);
			if (iTemp <= 0 || sti(pchar.money) < iTemp)
			{
				dialog.text = "This is wrong attitude, my son. We all have sins, don't forget about your soul. You will have to appear before our Creator... and perhaps soon.";
				link.l1 = "I don't need your sermons, holy father. Farewell.";
				link.l1.go = "Padre_exit";
				ChangeCharacterComplexReputation(pchar, "nobility", -3);
				break;
			}
			if (iTemp > 0 && iTemp <= 1000)//ничего не скажет
			{
				dialog.text = "Our parish and I thank you for this modest gift.";
				link.l1 = "You are welcome, holy father.";
				link.l1.go = "Padre_exit";
				AddMoneyToCharacter(pchar, -iTemp);
			}
			if (iTemp > 1000 && iTemp <= 5000)//1 категория - намекнет
			{
				dialog.text = "Our parish and I thank you for this gift. And I want to warn you, my son, that some bad people are intend to harm you. Be careful in the sea!";
				link.l1 = "Padre, every day people are planning to do something against me... But thank you for your concerns about my fate.";
				link.l1.go = "Padre_exit";
				AddMoneyToCharacter(pchar, -iTemp);
			}
			if (iTemp > 5000 && iTemp <= 10000)//2 категория - скажет
			{
				dialog.text = "I thank you in the name of our parish for this valuable gift. In return, I want to warn you that bad people are conspiring against you. I heard that these vile apostates are going to sink your vessel at this very harbour\nThey have already prepared a ship for this evil deed. Be careful, my son, these lost souls are serious about their vile intentions. Bless you!";
				link.l1 = "Thank you, holy father. I will be attentive.";
				link.l1.go = "Padre_exit";
				AddMoneyToCharacter(pchar, -iTemp);
			}
			if (iTemp > 10000)//3 категория - расскажет полностью
			{
				dialog.text = "You are very generous, my son. A modesty of a humble servant of the God doesn't allow me to accept the whole sum you are willing to give away for the good our of church. I will take only 10 000 pesos\nIn return, I want to warn you that bad people are conspiring against you. I heard that these vile apostates are going to sink your vessel at this harbor\nThey have prepared a lugger named '"+pchar.questTemp.Regata.BranderName+"', she is sailing under the English flag in order to approach you without causing suspicions. Be careful, my son, these lost souls are serious about their vile intentions.\nDestroy them, I give you absolution for this sin. Bless you! I will pray for you, my son.";
				link.l1 = "Thank you, holy father. If these bastards dare to do something bad, I will send them right to hell!";
				link.l1.go = "Padre_exit";
				AddMoneyToCharacter(pchar, -10000);
				ChangeCharacterComplexReputation(pchar, "nobility", 2);
			}
		break;
		
		case "Regata_Padre_exit":
			dialog.text = "Don be angry, my son. Anger is a sin. It is your right to not do charity. Walk in peace, my son.";
			link.l1 = "Farewell, holy father.";
			link.l1.go = "Padre_exit";
			ChangeCharacterComplexReputation(pchar, "nobility", -1);
		break;
		
		case "Padre_exit":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload7_back", "SentJons_church", "barmen", "stay", "ReturnRegataPadreNorm", 5);
		break;
		
		case "Regata_Spyglass":
			dialog.text = "Good day to you, captain! My name is " + npchar.name + " and I'd like to...";
			link.l1 = "... to offer me something... Am I right, young lady?";
			link.l1.go = "Regata_Spyglass_1";
		break;
		
		case "Regata_Spyglass_1":
			dialog.text = "Of course, captain! And why are you surprised like that? You are a handsome sailor and you are taking part in the regatta, sure everyone are willing to sell you some useful naval stuff.";
			link.l1 = "Fine, beauty, you have a point. What have you got for me?";
			link.l1.go = "Regata_Spyglass_2";
		break;
		
		case "Regata_Spyglass_2":
			if(drand(11) > 10)//отличная труба
			{
				pchar.questTemp.Regata.Spy = "spyglass4";
				sTemp = "an excellent spyglass";
				pchar.questTemp.Regata.SpyPrice = 20000;
				pchar.questTemp.Regata.SpyIndex = 12;//выигрыш - 12 часов
			}
			else
			{
				if(drand(11) < 6)//обычная труба
				{
					pchar.questTemp.Regata.Spy = "spyglass2";
					sTemp = "an ordinary spyglass";
					pchar.questTemp.Regata.SpyPrice = 1800;
					pchar.questTemp.Regata.SpyIndex = 4;//выигрыш - 4 часа
				}
				else//хорошая труба - как пригодится
				{
					pchar.questTemp.Regata.Spy = "spyglass3";
					sTemp = "a good spyglass";
					pchar.questTemp.Regata.SpyPrice = 10000;
					pchar.questTemp.Regata.SpyIndex = 8;//выигрыш - 8 часов
				}
			}
			dialog.text = "Here, take a look. I have inherited it from my father. He also was a sailor just like you are. I don't need it, but you can find it useful. I ask only "+FindRussianMoneyString(sti(pchar.questTemp.Regata.SpyPrice))+" for it.";
			if (sti(pchar.money) >= sti(pchar.questTemp.Regata.SpyPrice))
			{
				link.l1 = "Well, well..."+sTemp+"! Interesting! I say, I'll buy it from you. For your pretty eyes. Do you want "+FindRussianMoneyString(sti(pchar.questTemp.Regata.SpyPrice))+" for it? Please, take your money.";
				link.l1.go = "Regata_Spyglass_3";
			}
			link.l2 = "Hm..."+sTemp+"? No, girl, I am sorry, but I don't need it. I have already got a fine spyglass. So... alas!";
			link.l2.go = "Regata_Spyglass_exit";
		break;
		
		case "Regata_Spyglass_3":
			AddMoneyToCharacter(pchar, -sti(pchar.questTemp.Regata.SpyPrice));
			GiveItem2Character(pchar, pchar.questTemp.Regata.Spy);
			dialog.text = "Thank you, captain. I hope that it will serve you well. I am glad that you have found it useful. Good luck in the regatta!";
			link.l1 = "Thank you, " + npchar.name + "! Farewell.";
			link.l1.go = "Spyglass_exit";
			for (i=1; i <=5; i++)
			{
				if (i==1) sTemp = "a";
				if (i==2) sTemp = "b";
				if (i==3) sTemp = "c";
				if (i==4) sTemp = "d";
				if (i==5) sTemp = "e";
				pchar.questTemp.Regata.AdversaryFourthTransition.Time.(sTemp) = sti(pchar.questTemp.Regata.AdversaryFourthTransition.Time.(sTemp))+sti(pchar.questTemp.Regata.SpyIndex);//купил трубу - выиграл время
				log_testinfo(FindRussianDaysString(pchar.questTemp.Regata.AdversaryFourthTransition.Time.(sTemp)));
			}
		break;
		
		case "Regata_Spyglass_exit":
			dialog.text = "What a pity, captain. I was hoping that it will be useful for you. Well, I will try to sell it to someone else. Farewell!";
			link.l1 = "Goodbye, " + npchar.name + ".";
			link.l1.go = "Spyglass_exit";
			pchar.questTemp.Regata.AdversaryFourthTransition.Time.c = sti(pchar.questTemp.Regata.AdversaryFourthTransition.Time.c)-sti(pchar.questTemp.Regata.SpyIndex);//третий соперник выиграл время
		break;
		
		case "Spyglass_exit":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload4_back", "none", "", "", "", 10);
			bDisableFastReload = false;
			chrDisableReloadToLocation = false;
		break;
		
		case "Regata_SiegeOfficer":
			dialog.text = "Greetings, captain. Aren't you a participant of the regatta? Am I right?";
			link.l1 = "Yes. And what is the deal, officer?";
			link.l1.go = "Regata_SiegeOfficer_1";
		break;
		
		case "Regata_SiegeOfficer_1":
			dialog.text = "You must be informed already that our colony is under Spanish siege. That is why our governor wants to talk with you. Would you be kindly to pay him a visit? Right now, the matter is very urgent and I'd say it is vital.";
			link.l1 = "Hm... Sure, I am going to see his Excellency immediately, though I don't really understand how can I be involved in the military operations.";
			link.l1.go = "Regata_SiegeOfficer_2";
		break;
		
		case "Regata_SiegeOfficer_2":
			dialog.text = "You are involved, captain. Let's not waste time and move to the residence. Follow me.";
			link.l1.go = "Regata_SiegeOfficer_3";
		break;
		
		case "Regata_SiegeOfficer_3":
			DialogExit();
			LAi_ActorGoToLocation(npchar, "reload", "reload3_back", "Bridgetown_townhall", "goto", "governor1", "RegataSiegeHover", -1);
		break;
		
		case "Regata_SiegeOfficer_4":
			dialog.text = "Sir! I am ready to dispatch civilians to your ship. Are we going now?";
			link.l1 = "Yes, sure. We are going to sail immediately. Forward people to longboats.";
			link.l1.go = "Regata_SiegeOfficer_5";
		break;
		
		case "Regata_SiegeOfficer_5":
			DialogExit();
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "RegataSiegeOpen", -1);
			for (i=1; i <=9; i++)
			{
				sld = characterFromId("RegataBridgWom_"+i);
				LAi_SetActorType(sld);
				LAi_ActorGoToLocation(sld, "quest", "quest1", "none", "", "", "", 30);
			}
		break;
		
		case "Regata_SiegeOfficer_6":
			dialog.text = "We did it... Looks like this sloop was a scout of the squadron and these Castilian bastards were scouting around. Captain, help me to get women to the caverns, there is a possibility that there are more Spanish detachments.";
			link.l1 = "Fine. Lets go!";
			link.l1.go = "Regata_SiegeOfficer_7";
		break;
		
		case "Regata_SiegeOfficer_7":
			DialogExit();
			sld = characterFromId("SiegeOfficer");
			LAi_ActorFollowEverywhere(sld, "", -1);
			pchar.quest.Regata_Siege3.win_condition.l1 = "location";
			pchar.quest.Regata_Siege3.win_condition.l1.location = "Barbados_cave";
			pchar.quest.Regata_Siege3.function = "RegataBarbadosCave";
		break;
		
		case "Regata_SiegeOfficer_8":
			dialog.text = "Gratitude for you help, captain! If it wasn't for you and your courage... You are a true hero, you have completed this operation despite all dangers and your own interests. I have been thinking on how to reward you... there is a way to improve your chances in the regatta.";
			link.l1 = "Interesting. What is this way?";
			link.l1.go = "Regata_skiper";
		break;
		
		case "Regata_Hovernor":
			dialog.text = "Greeting, captain " + GetFullName(pchar) + ". It is good that you have come. Our town is need of your help.";
			link.l1 = "Sir, if you are talking about Spanish squadron which is storming your colony right now, then I have no idea how I can help you. I command a lugger not a the ship of the line...";
			link.l1.go = "Regata_Hovernor_1";
		break;
		
		case "Regata_Hovernor_1":
			dialog.text = "Listen to me, captain, and you will understand. We are in a serious trouble. The city is under the Spanish siege. A decisive battle with the fort is about to begin. Besides, a few hundred of Spanish have already landed and blocked every exit from the city, now they can attack us from the sea and the land\nFort's garrison is preparing to defend the city from the squadron and there are not enough soldiers in the settlement itself. Every man capable of handling a weapon is mobilized but what about the others?\nThere are hundred souls of women in Bridgetown. Can you imagine what will happen to them if we fail to protect our colony? I believe that you understand.";
			link.l1 = "Sir, I understand you, but, again, how can I help? What do you want from me? To fight ships of the line or to enlist with my crew in the town's militia?";
			link.l1.go = "Regata_Hovernor_2";
		break;
		
		case "Regata_Hovernor_2":
			switch (sti(Pchar.BaseNation))
			{
				case ENGLAND: sTemp = "You are English , help us to save English citizens and what is important - women!" break;
				case FRANCE: sTemp = "You are French, so you basically are our ally, help us to save English citizens and what is more important - women!" break;
				case SPAIN: sTemp = "I know that you are Spanish and there are your people in the sea, but you are participating in the English regatta and you are flying our colours. Don't you think that it is right to fight for peaceful people, for women? Help them!" break;
				case HOLLAND: sTemp = "I know that you are Dutch and our nations are in war, but you are participating in the English regatta under the English flag. Don't you think that it is right to fight for peaceful people, for women? Help them!" break;
			}
			dialog.text = "Neither. I ask you for only one thing. Take women and children away from here on your ship. There are not many of them, about a hundred. Take them to Harrison Cape along with lieutenant Mahony, he will make sure they are save in the cave\nI am sure that the Spanish won't search for them. I don't have any ships to spare, everything we had was sunk by the Spanish squadron. You are my last hope. You can take them to the cape in one voyage, even though your vessel will be overloaded. Ships of the line won't follow you.\nI can't ask anyone else to do it. "+sTemp+"";
			link.l1 = "Sir, I am sorry but my ship is overloaded already and she will not be able to hold that many people even for two voyages. Any random cannon ball even felled near will sent my ship and your women to the bottom of the sea. Forgive me, but I can't help you.";
			link.l1.go = "Regata_Hovernor_exit";
			link.l2 = "Sure, sir. I will help you. The sailor's honour obliges me to  that.";
			link.l2.go = "Regata_Hovernor_3";
		break;
		
		case "Regata_Hovernor_3":
			dialog.text = "I am glad that you have agreed. You are a true soldier. Lieutenant Mahony will bring women and children to your ship. May God speed you!";
			link.l1 = "Thank you, sir. Let's not waste time!";
			link.l1.go = "Regata_Hovernor_4";
		break;
		
		case "Regata_Hovernor_wait":
			dialog.text = "Hurry up, captain. Time is running.";
			link.l1 = "I am sailing already!";
			link.l1.go = "exit";
			NextDiag.TempNode = "Regata_Hovernor_wait";
		break;
		
		case "Regata_Hovernor_exit":
			dialog.text = "This is unbelievable. You are not going to even try? Well, you are in your right. I can't demand anything from you. If you were just an ordinary captain, I would confiscate your ship for the sake of hundred women, but you participating in the regatta, therefore you are under protection of general-governor of English colonies\nI was hoping that your conscience will take better of you, yet I was wrong. Go and let God be merciful on your soul!";
			link.l1 = "Farewell, sir.";
			link.l1.go = "Hovernor_exit";
		break;
		
		case "Hovernor_exit":
			DialogExit();
			pchar.questTemp.Regata.AdversaryFifthTransition.Time.e = sti(pchar.questTemp.Regata.AdversaryFifthTransition.Time.e)-36;//пятый противник выиграл 36 часов
			ChangeCharacterComplexReputation(pchar, "nobility", -8);
			ChangeCharacterNationReputation(pchar, ENGLAND, -5);
			//вертаем губера в норму
			npchar.Dialog.Filename = "Common_Mayor.c";
			npchar.dialog.currentnode = "First time";
			//удаляем лейтенанта
			sld = characterFromId("SiegeOfficer");
			sld.lifeday = 0;
			//открываем ворота и выход в море
			bDisableFastReload = false;
			LocatorReloadEnterDisable("Bridgetown_town", "reload1_back", false);
			LocatorReloadEnterDisable("Bridgetown_town", "reload2_back", false);
			LocatorReloadEnterDisable("Bridgetown_town", "gate1_back", false);
			LocatorReloadEnterDisable("Bridgetown_town", "gate_back", false);
			LocatorReloadEnterDisable("Bridgetown_Exittown", "reload3", false);
			//остров в норму
			n = FindIsland("Barbados");	
			DeleteAttribute(Islands[n], "DontSetShipInPort");
			//осаду снимем через 5 дней
			SetFunctionTimerCondition("RegataSiegeDelete", 0, 0, 5, false);
			for (i=1; i <=9; i++)//девок счистим
			{
				sld = characterFromId("RegataBridgWom_"+i);
				sld.lifeday = 0; // patch-7
				LAi_CharacterDisableDialog(sld);
			}
		break;
		
		case "Regata_Hovernor_4":
			DialogExit();
			NextDiag.CurrentNode = "Regata_Hovernor_wait";
			sld = characterFromId("SiegeOfficer");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload2", "Bridgetown_town", "goto", "goto4", "", 10);
			pchar.quest.Regata_evacuation.win_condition.l1 = "location";
			pchar.quest.Regata_evacuation.win_condition.l1.location = "Bridgetown_town";
			pchar.quest.Regata_evacuation.function = "RegataSiegeEvacuation";
		break;
		
		case "Regata_BridgWom":
			dialog.text = "Spanish are on us! God, help us!";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "Regata_BridgWom";
		break;
		
		case "Regata_BridgWom_1":
			dialog.text = "Lieutenant Mahony is dead... it must be a nightmare. He was a brave officer. Captain, will you please take us to a cavern? Just take us there and we will take care about ourselves.";
			link.l1 = "Sure. Follow me!";
			link.l1.go = "Regata_BridgWom_2";
		break;
		
		case "Regata_BridgWom_2":
			DialogExit();
			for (i=1; i <=9; i++)
			{
				sld = characterFromId("RegataBridgWom_"+i);
				LAi_SetActorType(sld);
				LAi_ActorFollowEverywhere(sld, "", -1);
			}
			pchar.quest.Regata_Siege3.win_condition.l1 = "location";
			pchar.quest.Regata_Siege3.win_condition.l1.location = "Barbados_cave";
			pchar.quest.Regata_Siege3.function = "RegataBarbadosCave";
		break;
		
		case "Regata_BridgWom_3":
			dialog.text = "Here we are... thank you, captain! You have just saved all of us! I have been thinking how to reward you... there is a way to improve your chances in the regatta.";
			link.l1 = "Go on.";
			link.l1.go = "Regata_skiper";
		break;
		
		case "Regata_skiper":
			pchar.questTemp.Regata.Name = GetFullName(npchar);
			dialog.text = "Are you heading to Port Royal? The shortest route lies through Curacao. Return to Bridgetown. Find a man named Woodrow Dougherty, he is an old sailor and an experienced navigator. He perfectly knows the area between Barbados and Jamaica, he'd be a great help\nThis will save you a lot of critical time you so need to win. Find the man in the local church and tell him that " + GetFullName(npchar) + " - has sent you, he won't turn you down. Take him to Port Royal, he was going to sail there anyway.";
			link.l1 = "Very well! A good navigator will be useful for me. Farewell.";
			link.l1.go = "Regata_skiper_1";
		break;
		
		case "Regata_skiper_1":
			dialog.text = "Farewell, captain! Good luck!";
			link.l1 = "Perhaps, we will meet again...";
			link.l1.go = "Regata_skiper_2";
		break;
		
		case "Regata_skiper_2":
			DialogExit();
			ChangeCharacterComplexReputation(pchar, "nobility", 10);
			ChangeCharacterNationReputation(pchar, ENGLAND, 10);
			LAi_SetStayType(npchar);
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeday = 0; // patch-8
			for (i=1; i <=9; i++)
			{
				sld = characterFromId("RegataBridgWom_"+i);
				LAi_SetStayType(sld);
				LAi_CharacterDisableDialog(sld);
				sld.lifeday = 0; // patch-8
			}
			//вертаем губера в норму
			sld = characterFromId("Bridgetown_Mayor");
			sld.Dialog.Filename = "Common_Mayor.c";
			sld.dialog.currentnode = "First time";
			//открываем ворота и выход в море
			LocatorReloadEnterDisable("Shore4", "boat", false);
			LocatorReloadEnterDisable("Bridgetown_town", "gate1_back", false);
			LocatorReloadEnterDisable("Bridgetown_town", "gate_back", false);
			LocatorReloadEnterDisable("Bridgetown_Exittown", "reload3", false);
			LocatorReloadEnterDisable("Barbados_cave", "reload1", false);
			bQuestDisableMapEnter = false;
			//осаду снимем через 5 дней
			SetFunctionTimerCondition("RegataSiegeDelete", 0, 0, 5, false);
			RegataSiegeSkiper();//поставим Вудро в церковь
		break;
		
		case "Regata_SiegeSkiper":
			dialog.text = "Good day. Want something?";
			link.l1 = "Your name is Woodrow Dougherty, am I right?";
			link.l1.go = "Regata_SiegeSkiper_1";
		break;
		
		case "Regata_SiegeSkiper_1":
			dialog.text = "You are right. How can I be of service?";
			link.l1 = "I know that you are a seasoned navigator and you know well the waters between Barbados and Curacao. I also know that you want to get to Port Royal. I am a participant of the regatta and there is the last passage left - to Port Royal. I want to ask you to join my crew as a navigator for this last passage.";
			link.l1.go = "Regata_SiegeSkiper_2";
		break;
		
		case "Regata_SiegeSkiper_2":
			dialog.text = "Interesting... And why do you think that I will join your crew?";
			link.l1 = "Well, because I got known about you from "+pchar.questTemp.Regata.Name+" with all guarantees that you won't say no. And because of my help to Bridgetown in this critical moment...";
			link.l1.go = "Regata_SiegeSkiper_3";
		break;
		
		case "Regata_SiegeSkiper_3"://а тут - как уж свезет
			if(drand(2) != 2)
			{
				dialog.text = "From "+pchar.questTemp.Regata.Name+"? I see now, sure. Alright, captain, I will help you to sail the shortest way to Port Royal. Are you going to set sail now?";
				link.l1 = "Yes.";
				link.l1.go = "Regata_SiegeSkiper_4";
			}
			else
			{
				dialog.text = ""+pchar.questTemp.Regata.Name+"? I see. But, captain, I can't leave my city in such a dangerous time. You must understand me as a soldier who provided us with a disinterested aid\nI don't want people to whisper behind my back that old Woodrow fled away in light of the final battle against the Spanish. I shall stay. Hold no grudges, captain.";
				link.l1 = "And this is your last word? But I've helped your colony...";
				link.l1.go = "Regata_SiegeSkiper_6";
			}
		break;
		
		case "Regata_SiegeSkiper_4":
			dialog.text = "Let's not waste time then. Just let me pack my things and will be in your disposal.";
			link.l1 = "My seamen will be waiting for you on the pier and will deliver you to the 'Santa Catherina'. Thank you, Woodrow!";
			link.l1.go = "SiegeSkiper_hire";
		break;
		
		case "Regata_SiegeSkiper_6":
			dialog.text = "Captain, the regatta is a sport and the Spanish siege of my home is a life. I ain't going with you anywhere. And I will repeat myself, you have to understand me - honour and duty still mean something in this world. This is my last word and I am not going to change it.";
			link.l1 = "Well... I am disappointed. Farewell, Woodrow.";
			link.l1.go = "SiegeSkiper_exit";
		break;
		
		case "SiegeSkiper_exit":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "", 10.0);
			npchar.lifeday = 0;
		break;
		
		case "SiegeSkiper_hire":
			chrDisableReloadToLocation = true;//закрыть локацию
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "OpenTheDoors", 10.0);
			npchar.quest.OfficerPrice = sti(pchar.rank)*500;
			Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(npchar.id);
			npchar.OfficerWantToGo.DontGo = true; //не пытаться уйти
			npchar.loyality = 25;
			npchar.Dialog.Filename = "Enc_Officer_dialog.c";
			AddDialogExitQuestFunction("LandEnc_OfficerHired");
			NextDiag.CurrentNode = NextDiag.TempNode;
			//пересчитываем время пятого перехода
			for (i=1; i <=5; i++)
			{
				if (i==1) sTemp = "a";
				if (i==2) sTemp = "b";
				if (i==3) sTemp = "c";
				if (i==4) sTemp = "d";
				if (i==5) sTemp = "e";
				pchar.questTemp.Regata.AdversaryFifthTransition.Time.(sTemp) = sti(pchar.questTemp.Regata.AdversaryFifthTransition.Time.(sTemp))+18+(rand(18));//выигрыш до 1.5 суток
				log_testinfo(FindRussianDaysString(pchar.questTemp.Regata.AdversaryFourthTransition.Time.(sTemp)));
			}
			SetFunctionTimerCondition("SiegeSkiperOver", 0, 0, 15, false);//чтобы не присвоил офицера
			DialogExit();
		break;
		
		case "Regata_Finish":
		iTest = FindColony("Portroyal"); 
		if (iTest != -1)
		{
			rColony = GetColonyByIndex(iTest);
			sFrom_sea = rColony.from_sea;
		}
		ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
		if(sti(Pchar.Ship.Type) != SHIP_NOTUSED && ok)//проверка на наличие корабля в порту
		{
			//снимаем запреты
			bQuestDisableMapEnter = false;//открыть карту
			DeleteAttribute(pchar, "GenQuest.CannotWait");//можно мотать время
			if (CheckAttribute(pchar, "questTemp.Regata.Breach") || !CheckAttribute(pchar, "questTemp.Regata.Bridgetown") || GetCompanionQuantity(pchar) > 1 || sti(RealShips[sti(pchar.ship.type)].basetype) != SHIP_LUGGER || pchar.Ship.Name != "Santa Catherina")
			{
				dialog.text = "You have broken the rules of regatta on the very last stage. Your result was disqualified. I have nothing more to tell you, captain.";
				link.l1 = "Eh...what a ! Well, there is nothing to do then, you were too attentive. Farewell!";
				link.l1.go = "exit";
				npchar.lifeday = 1;
				DeleteAttribute(pchar, "questTemp.Regata");
			}
			else
			{
				n=1;
				for (i=1; i <=5; i++)
				{
					if (i==1) sTemp = "a";
					if (i==2) sTemp = "b";
					if (i==3) sTemp = "c";
					if (i==4) sTemp = "d";
					if (i==5) sTemp = "e";
					if (pchar.questTemp.Regata.AdversaryFifthTransition.Time.(sTemp) < sti(pchar.questTemp.Regata.FifthTransitionTime)) n++;
					pchar.questTemp.Regata.Result = n;//место в регате
				}
				if (n==1)
				{
					dialog.text = "Captain "+GetFullName(pchar)+", my congratulations! It took "+sti(pchar.questTemp.Regata.FifthTransitionTime)+" hours from you to finish the regatta and you have left all your opponents way behind. This is a remarkable result!";
					link.l1 = "Thank you for your kind words, sir!";
					link.l1.go = "First_result";
				}
				else
				{
					if (n==6)
					{
						dialog.text = "Captain, alas but your result is the worst, you have spent "+sti(pchar.questTemp.Regata.FifthTransitionTime)+" hours. Don't be sad, you had really tough opponents.";
						link.l1 = "I am not sad, sir. I am glad that I have participated in the regatta and tried my skills.";
						link.l1.go = "Other_result";
					}
					else
					{
          					dialog.text = "Captain, your rank is number "+n+". Congratulations with the successful sail, you have shown a worthy time - "+sti(pchar.questTemp.Regata.FifthTransitionTime)+" hours. Congratulations despite your loss!";
						link.l1 = "It is alright, sir. I am glad that I have shown a fine result in this tough competition.";
						link.l1.go = "Other_result";
					}
				}
			}
			Pchar.questTemp.FiringOfficerIDX = GetCharacterIndex("SiegeSkiper");
			sld = &Characters[sti(Pchar.questTemp.FiringOfficerIDX)];
			CheckForReleaseOfficer(sti(Pchar.questTemp.FiringOfficerIDX));
			RemovePassenger(Pchar, sld);
			DeleteAttribute(sld, "Payment");
			DeleteAttribute(Pchar, "questTemp.FiringOfficerIDX");//удаляем из офицеров
			log_info("Woodrow Dougherty has landed");
			pchar.quest.SiegeSkiperOver.over = "yes"; //снять таймер
		}
		else
		{
			dialog.text = "Sir, let me ask you something - where is your ship? I don't see it...";
			link.l1 = "I am sorry, sir. I will get her to the port immediately.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Regata_Finish";
		}
		break;
		
		case "First_result":
			if (CheckAttribute(pchar, "questTemp.Regata.Rate")) sTemp = "Come and see me in my office. I will give you your prize for your stake.";
			else sTemp = "And if you had made a stake on your victory as I offered you to, you would have got an extra prize too.";
			dialog.text = "Visit governor-general tomorrow and he will give you your 250 000 pesos and valuable gifts. "+sTemp+" Don't leave the town, according to traditions the prizes will be given to the town's treasury in case the winner won't take them in a week time.";
			link.l1 = "I got it, sir. I will visit him tomorrow!";
			link.l1.go = "First_result_1";
		break;
		
		case "First_result_1":
			DialogExit();
			//npchar.lifeday = 7;
			Achievment_SetStat(pchar, 9, 1);
			npchar.dialog.currentnode = "Other_result_repeat";
			pchar.questTemp.Regata.Win = "true";
			pchar.quest.Regata_Final.win_condition.l1 = "Timer";
			pchar.quest.Regata_Final.win_condition.l1.date.hour  = 6.0;
			pchar.quest.Regata_Final.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.Regata_Final.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.Regata_Final.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.Regata_Final.function = "RegataFinal";
			SetFunctionTimerCondition("RegataFinalOver", 0, 0, 8, false);//таймер не снимаем - через 8 дней подчистится все автоматически
			// слухи
			AddSimpleRumour("Ah, you are the legendary captain, the winner of the regatta! It's such a pleasure to see you in flesh!", ENGLAND, 60, 10);
			AddSimpleRumour("Ha, look at this, a master of wind and waves, the winner of the regatta! You have my respect...", ENGLAND, 60, 10);
			AddSimpleRumour("Oh, a great sailor, a king of wind and sea, the winner of the regatta has visited our city! We are glad to see you, captain!", ENGLAND, 60, 10);
			AddSimpleRumour("Oh, yes I was lucky to chat with a living legend, the captain who is capable of crossing the archipelago in three days even facing a headwind! My respects, captain!", ENGLAND, 60, 10);
			AddSimpleRumour("Ah, so you are the legendary captain, the winner of the regatta! Pleasure to see you!", FRANCE, 60, 10);
			AddSimpleRumour("Ha, aren't you the master of wind and waves, the winner of the regatta! You have my respects...", FRANCE, 60, 10);
			AddSimpleRumour("Oh, a great sailor, a king of wind and sea, the winner of the regatta has visited our city! We are glad to see you, captain!", FRANCE, 60, 10);
			AddSimpleRumour("Oh, yes I was lucky to chat with a living legend, the captain capable of crossing the archipelago in three days even facing a headwind! My respects, captain!", FRANCE, 60, 10);
			// экспа
			AddComplexSeaExpToScill(2000, 300, 300, 0, 500, 500, 0);
			AddCharacterExpToSkill(pchar, "Leadership", 2000);//авторитет
			AddCharacterExpToSkill(pchar, "Fortune", 1000);//везение
			AddCharacterExpToSkill(pchar, "Sneak", 300);//скрытность
			ChangeCharacterComplexReputation(pchar, "authority", 10);
			ChangeCharacterComplexReputation(pchar, "fame", 15);
			ChangeOfficersLoyality("good_all", 3);
		break;
		
		case "Other_result":
			dialog.text = "It is good to hear an honourable response. Good luck, captain!";
			link.l1 = "Farewell, sir.";
			link.l1.go = "Other_result_1";
		break;
		
		case "Other_result_1":
			DialogExit();
			npchar.dialog.currentnode = "Other_result_repeat";
			SetFunctionTimerCondition("RegataFinalOver", 0, 0, 1, false);
			// экспа
			AddComplexSeaExpToScill(500, 100, 100, 0, 100, 100, 0);
			AddCharacterExpToSkill(pchar, "Leadership", 200);//авторитет
			AddCharacterExpToSkill(pchar, "Fortune", 100);//везение
			AddCharacterExpToSkill(pchar, "Sneak", 100);//скрытность
			ChangeCharacterComplexReputation(pchar, "authority", 1);
			ChangeCharacterComplexReputation(pchar, "fame", 1);
		break;
		
		case "Other_result_repeat":
			dialog.text = "Want something else, captain?";
			link.l1 = "No, it is nothing.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Other_result_repeat";
		break;
		
		case "Give_advantage":
			dialog.text = "Ah, there you are, mister "+GetFullName(pchar)+". Glad to see you. Are you here for your prize? It is ready for you.";
			link.l1 = "It is good to hear that! What it the size of my additional prize?";
			link.l1.go = "Give_advantage_1";
		break;
		
		case "Give_advantage_1":
			dialog.text = "Considering all stakes, your final prize is "+FindRussianMoneyString(makeint(pchar.questTemp.Regata.Advantage))+". Please, take it. Congratulations!";
			link.l1 = "Thanks!";
			link.l1.go = "Give_advantage_2";
		break;
		
		case "Give_advantage_2":
			AddMoneyToCharacter(pchar, makeint(pchar.questTemp.Regata.Advantage));
			dialog.text = "Sure, your popularity among the citizens of Port Royal has grown. I think, that you are able to see that... but alas the people's memory is short. So bath in the glory while it is still that bright!";
			link.l1 = "You are talking of the nicest things, sir... Let see how is it to bath in the glory. Farewell! It was a pleasure.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Other_result_repeat";
		break;
		
		case "Regata_CitMan_1":
			if (CheckAttribute(pchar, "questTemp.Regata"))
			{
				if (CheckAttribute(pchar, "questTemp.Regata.Result"))
				{
					if (sti(pchar.questTemp.Regata.Result) == 1)
					{
						dialog.text = "Congratulations with your victory, captain! An excellent result!";
						link.l1 = "Thanks!";
						link.l1.go = "exit";
					}
					else
					{
						dialog.text = "Don't be sad, captain. It is not easy to win the regatta, even participating in it is a privilege!";
						link.l1 = "Don't worry about me. I am satisfied with my result.";
						link.l1.go = "exit";
					}
				}
				else
				{
					dialog.text = "Glad to see you, captain! You should register yourself by talking to sir Stevenson.";
					link.l1 = "I see. I am on my way to him!";
					link.l1.go = "exit";
				}
			}
			else
			{
				dialog.text = "Ah, captain, why have you failed like that and on the very last stage!";
				link.l1 = "Yes, so stupid of me...";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "Regata_CitMan_1";
		break;
		
		case "Regata_CitWom_1":
			if (CheckAttribute(pchar, "questTemp.Regata"))
			{
				if (CheckAttribute(pchar, "questTemp.Regata.Result"))
				{
					if (sti(pchar.questTemp.Regata.Result) == 1)
					{
						dialog.text = "Congratulations on you victory, captain! An excellent result!";
						link.l1 = "Thank you!";
						link.l1.go = "exit";
					}
					else
					{
						dialog.text = "Don't be sad, captain. It is not easy to win the regatta, even participating in it is a privilege!";
						link.l1 = "Don't worry about me. I am satisfied with my result.";
						link.l1.go = "exit";
					}
				}
				else
				{
					dialog.text = "Glad to see you, captain! You should register yourself by talking to sir Stevenson.";
					link.l1 = "I see. I am on my way!";
					link.l1.go = "exit";
				}
			}
			else
			{
				dialog.text = "Ah, captain, why have you failed like that and on the very last stage!";
				link.l1 = "Yes, so stupid of me...";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "Regata_CitWom_1";
		break;
		
		case "Regata_CitHorse_1":
			if (CheckAttribute(pchar, "questTemp.Regata"))
			{
				if (CheckAttribute(pchar, "questTemp.Regata.Result"))
				{
					if (sti(pchar.questTemp.Regata.Result) == 1)
					{
						dialog.text = "Congratulations with you victory, captain! An excellent result!";
						link.l1 = "Thank you!";
						link.l1.go = "exit";
					}
					else
					{
						dialog.text = "Don't be sad, captain. It is not easy to win in the regatta, even participating in it is a privilege!";
						link.l1 = "Don't worry about me. I am satisfied with my result.";
						link.l1.go = "exit";
					}
				}
				else
				{
					dialog.text = "Glad to see you, captain! You should register yourself by talking to sir Stevenson.";
					link.l1 = "I see. I am on my way!";
					link.l1.go = "exit";
				}
			}
			else
			{
				dialog.text = "Ah, captain, why have you failed like that and on the very last stage!";
				link.l1 = "Yes, so stupid of me...";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "Regata_CitHorse_1";
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}

void CreateRegataAdversaries()
{
	string sTemp;
	for (int i=0; i<=4; i++)
	{
	if (i==0) sTemp = "a";
	if (i==1) sTemp = "b";
	if (i==2) sTemp = "c";
	if (i==3) sTemp = "d";
	if (i==4) sTemp = "e";
	pchar.questTemp.Regata.AdversaryName.(sTemp) = GenerateRandomName_Generator(i, "man");
	pchar.questTemp.Regata.AdversaryShipName.(sTemp) = GenerateRandomNameToShip(ENGLAND);
	pchar.questTemp.Regata.AdversarySpeed.(sTemp) = 0.4+frand(0.9);
	log_testinfo(FindRussianDaysString(stf(pchar.questTemp.Regata.AdversarySpeed.(sTemp))));
	}
}