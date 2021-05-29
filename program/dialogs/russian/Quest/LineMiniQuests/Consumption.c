// диалоги по квесту Цена чахотки
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
			if (pchar.questTemp.Consumption == "final")
			{
				dialog.text = "Captain! You went to sea, I heard! What happened? Did you find out anything? Please tell me, spit it out!";
				if (CheckAttribute(pchar, "questTemp.Consumption.TakeMoney"))
				{//взял деньги
					link.l1 = "No, my beauty, this raid was made at the request of His Grace governor. I am very sorry, but Angelo died in the casemates of the fort - now there is no doubt in that. Stand firm! ";
					link.l1.go = "Waitress";
				}
				else
				{//убил Хуана
					if (CheckAttribute(pchar, "questTemp.Consumption.KillJuan"))
					{
						link.l1 = "You were right. Your bother was kidnapped. Commandant had been selling prisoners like cattle to a slaver nicknamed Consumption. But I caught up with his ship, and now he is lying on the bottom, and your brother Angelo will come ashore soon. Unfortunately, I do not have as many long boats as needed for all passengers to be delivered ashore at once. ";
						link.l1.go = "Waitress_2";
					}
					else
					{//отпустил Хуана
						link.l1 = "You were right. Your bother was kidnapped. Commandant had been selling prisoners like cattle to a slaver nicknamed Consumption. But I caught up with his ship, and, despite that I failed to kill that bastard, your brother Angelo will come ashore soon. Unfortunately, I do not have as many long boats as needed for all passengers to delivered ashore at once. ";
						link.l1.go = "Waitress_2";
					}
					sld = characterFromId("ConAndjelo");
					sld.lifeday = 0;
					RemovePassenger(Pchar, sld);
				}
			}
			else
			{
				dialog.text = "Did you manage to find out anything about Angelo's fate, captain?";
				link.l1 = "Not yet. But I think I will have news soon. You just need to wait. ";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		case "without_moneysss": // лесник  если Гг нажрался..сволочь:D:D:D
		    dialog.text = "Senor, you promised to find my brother... Why are you wasting time drinking here?";
			link.l1 = "Ohh..Yeah, right..hic.. Chill, lass, I'm already gone...hic..";
			link.l1.go = "exit";
		break;
		
		case "Servant":
			dialog.text = "Good afternoon, senor. What's your business here?";
			link.l1 = "I've brought a dispatch for senor commandant, but I should give it to him personally.";
			link.l1.go = "Servant_1";
		break;
		
		case "Servant_1":
			dialog.text = "Then you go look for him in the fort.";
			link.l1 = "This dispatch is too important and not for soldiers' eyes and ears. Maybe I came too early, but I can wait for him here. Trust me, it is very important!";
			link.l1.go = "Servant_2";
		break;
		
		case "Servant_2":
			if (GetSummonSkillFromName(pchar, SKILL_SNEAK) < 20)
			{
				dialog.text = "Senor commandant usually warns me about all important issues that require changing the routine... You know, actually, he did warn me about this particular case.";
				link.l1 = "And what did he say?";
				link.l1.go = "Servant_3";
			}
			else
			{
				dialog.text = "Alright, I believe you. And I will believe you even more, when senor commandant arrives to confirm your words. But before that I will constantly keep an eye on you.";
				link.l1 = "You can watch me as much as you want...";
				link.l1.go = "Servant_4";
			}
		break;
		
		case "Servant_3":
			dialog.text = "He told me to call the garrison guards in such cases. But we will probably manage by ourselves. Men! Kill him!";
			link.l1 = "Fuck!";
			link.l1.go = "Servant_fight";
		break;
		
		case "Servant_4":
			DialogExit();
			NextDiag.CurrentNode = "Servant_repeat";
			LAi_SetOwnerType(npchar);
			chrDisableReloadToLocation = false;
		break;
		
		case "Servant_repeat":
			dialog.text = "What else do you want? Have you decided to give the message to me?";
			link.l1 = "No, I will wait for the commandant...";
			link.l1.go = "exit";
			NextDiag.TempNode = "Servant_repeat";
		break;
		
		case "Servant_fight":
			int iRank = sti(pchar.rank)+5;
			int iScl = 15 + 2*sti(pchar.rank);
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			chrDisableReloadToLocation = true;
			for (i=9; i<=11; i++)
			{	
				sld = GetCharacter(NPC_GenerateCharacter("Conservant_"+i, "citiz_"+i, "man", "man", iRank, SPAIN, -1, true, "quest"));
				FantomMakeCoolFighter(sld, iRank, iScl, iScl, "blade_10", "pistol1", "bullet", iScl*2);
				DeleteAttribute(sld, "SaveItemsForDead");
				DeleteAttribute(sld, "DontClearDead");
				LAi_SetWarriorType(sld);
				ChangeCharacterAddressGroup(sld, "PortSpein_houseF2", "goto", "goto5");
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "Consumption_AfterHouseFight");
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		//попытка залезть в сундук
		case "Man_FackYou":
			dialog.text = "You are a thief! Or, perhaps, a spy? Guys, here, quickly!";
			link.l1 = "Hup, devil!";
			link.l1.go = "Servant_fight";
		break;
		
		case "Sergio":
			dialog.text = "Excuse me, may I talk to you?";
			link.l1 = "To be honest, I am in a hurry. What do you want?";
			link.l1.go = "Sergio_1";
		break;
		
		case "Sergio_1":
			dialog.text = "I overheard that you are asking around about a man named Juan and disease in our prison...";
			link.l1 = "So... explain yourself.";
			link.l1.go = "Sergio_2";
		break;
		
		case "Sergio_2":
			dialog.text = "Easy, easy! Calm down and don't touch your sword! We are on the same side! I don't know why would you care about our problems, but this must be stopped! I can not keep silence any more!";
			link.l1 = "Keep silence? About what? What do you know about the consumption?";
			link.l1.go = "Sergio_3";
		break;
		
		case "Sergio_3":
			dialog.text = "I know a lot if not everything, and I will explain myself - but not here. Let's meet in the evening: when lights are out, I am a medical assistant, so I am allowed to leave the fort. We will meet beyond the town gates, and I will tell you everything. I beg you - stop asking questions, before you get their attention, if you didn't already... I have to go now. Remember: after sunset beyond the town gates.";
			link.l1 = "Alright, I will be there. Hey! Wait...";
			link.l1.go = "Sergio_4";
		break;
		
		case "Sergio_4":
			DialogExit();
			AddQuestRecord("Consumption", "8");
			LAi_ActorRunToLocation(npchar, "reload", "gate_back", "none", "", "", "OpenTheDoors", -1);
			pchar.quest.Consumption3.win_condition.l1 = "location";
			pchar.quest.Consumption3.win_condition.l1.location = "PortSpein_Exittown";
			pchar.quest.Consumption3.win_condition.l2 = "Hour";
			pchar.quest.Consumption3.win_condition.l2.start.hour = 0;
			pchar.quest.Consumption3.win_condition.l2.finish.hour = 3;
			pchar.quest.Consumption3.function = "Consumption_MeetSergio";
			pchar.quest.Consumption4.win_condition.l1 = "Timer";
			pchar.quest.Consumption4.win_condition.l1.date.hour  = sti(GetTime());
			pchar.quest.Consumption4.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.Consumption4.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.Consumption4.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.Consumption4.function = "Consumption_FailSergio";
			locations[FindLocation("PortSpein_Exittown")].DisableEncounters = true; //энкаутеры закрыть
			LAi_LocationDisableOfficersGen("PortSpein_Exittown", true);//офицеров не пускать
		break;
		
		case "Sergio_5":
			dialog.text = "Thank God, you are here... I hope you were not being followed?";
			link.l1 = "Why? You are too suspicious; perhaps, even more than senor commandant is, so you'd better get down to business... What do you know about Juan?";
			link.l1.go = "Sergio_6";
		break;
		
		case "Sergio_6":
			dialog.text = "My name is Sergio Saldo. I serve as a medical assistant in our fort and...";
			link.l1 = "Wait! Did you hear that?";
			link.l1.go = "Sergio_7";
		break;
		
		case "Sergio_7":
			dialog.text = "What?! Where?";
			link.l1 = "Shit, we are not alone here... Whom did you bring with you, scum?";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Consumption_CreateBandits");
		break;
		
		case "Bandit":
			dialog.text = "They have noticed us! You take the doc, and I take the other one!";
			link.l1 = "...";
			link.l1.go = "Bandit_1";
		break;
		
		case "Bandit_1":
			DialogExit();
			sld = characterFromId("Sergio");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			for (i=1; i<=3; i++)
			{	
				sld = characterFromId("Conbandit_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "Conbandit_AfterFight");
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "Sergio_8":
			dialog.text = "Put away your sword, it's over! You've seen by yourself now that they tried to kill me too!";
			link.l1 = "Well, it seems too sophisticated for foul play - so, you are not with them. Where have we left off? You are a prison doctor, aren't you?";
			link.l1.go = "Sergio_9";
		break;
		
		case "Sergio_9":
			dialog.text = "Yes. I serve as a prison doctor. I used to study medicine when I was young, and there are not many educated people here. That's why I know better than anyone about what's going on in the prison!";
			link.l1 = "What's going on then? What about prisoners? Do you know anything about their disappearing.";
			link.l1.go = "Sergio_10";
		break;
		
		case "Sergio_10":
			dialog.text = "Our commandant sells them... sells them like cattle to one slaver by the name of Juan. He picks those who will not be searched for - paupers, sailors from random ships. And then they suddenly 'die of consumption' - you can figure the rest...";
			link.l1 = "That Juan is a human, after all! What do you know about him?";
			link.l1.go = "Sergio_11";
		break;
		
		case "Sergio_11":
			dialog.text = "A bit. Used to do his dirty business in Morocco along with Berberian pirates, he likes to tell stories about those times when he pays us a visit. That was the place where he got his nickname - Consumption. Don't want to think about it's origins\nHe comes here every month and takes all prisoners aboard.";
			link.l1 = "'Consumption!' And they accused me of being cynical! So that's why... That senor commandant of yours is a real jerk!";
			link.l1.go = "Sergio_12";
		break;
		
		case "Sergio_12":
			dialog.text = "As I understand, you need someone from among the lost prisoners, otherwise how would you know about this story, am I right? If so, you should hurry: this night is the last this month. I have already signed the papers stating death of three more people, and Juan will haul anchor tomorrow before noon, when he receives them!";
			link.l1 = "What have you signed? I don't quite follow you...";
			link.l1.go = "Sergio_13";
		break;
		
		case "Sergio_13":
			dialog.text = "Yes, I had to do it - as I had been doing it for several months already! That is why I came here to stop this. Do you know how did Doctor Pinero die? The one who had treated prisoners before me?";
			link.l1 = "I think I was told that he died of consumption, did he not? So, you are forced into it. That is logical - but why didn't anyone contact the authorities regarding this matter?";
			link.l1.go = "Sergio_14";
		break;
		
		case "Sergio_14":
			dialog.text = "And who will believe in this? I don't posses any proof and those soldiers who are supposed to guard prisoners are being generously paid, so they wouldn't care even if they were selling people to Caribs as a meal\nNobody gives a shit about prisoners and that is an ace in the commandant's hand. But you can stop this, at least for some time, by eliminating Juan!";
			link.l1 = "As far as I understand, these guys ashore were his men, weren't they? How can I find him?";
			link.l1.go = "Sergio_15";
		break;
		
		case "Sergio_15":
			dialog.text = "You have probably caught someone's attention with your questions... I told you to be more careful! But that is not important now. I know nothing about Juan's ship, but prisoners are always sent to Galera Point, which is in the northern part of the island. I suppose that the slaver's ship should be nearby and you might catch up with him. His messengers have mentioned today that he was going to sail away tomorrow at noon.";
			if (!CheckCharacterItem(pchar, "letter_consumption"))
			{
				link.l1 = "Thank you, Sergio, you are a true officer and a man of honour. I will raise an anchor right now, and I will find this filthy ship. You need to get back to the fort before you are missed.";
				link.l1.go = "Sergio_16";
			}
			else
			{
				link.l1 = "Well, that's all I need to know. I have to raise an anchor right now if I don't wanna look for that 'Consumption' across the entire New World. Meanwhile you can study this.";
				link.l1.go = "Sergio_17";
			}
		break;
		
		case "Sergio_16":
			dialog.text = "Good luck, captain! Don't worry about me - the most important thing is to stop this at least for a while. I wish you luck!";
			link.l1 = "My cannons are the best treatment for ailment and meanness. I swear that all prisoners will be ashore before dawn - and Juan's ship will rest on the seabed!";
			link.l1.go = "Sergio_19";
		break;
		
		case "Sergio_17":
			RemoveItems(PChar, "letter_consumption", 1);
			Log_Info("You have given the letter");
			PlaySound("interface\important_item.wav");
			dialog.text = "What is it? Here is the colonel's name and a monogram 'J'? Incredible! Where did you get it from?";
			link.l1 = "You'd better not know that, but I think you'll use it in the best way possible.";
			link.l1.go = "Sergio_18";
		break;
		
		case "Sergio_18":
			dialog.text = "I will, I swear by all that is holy! The colonel will go to the gallows before end of the month! I will personally take care of that!";
			link.l1 = "I am afraid that it will end up with a disciplinary punishment, which, as I take it, will not be the first one in his life. Maybe, it's better to shoot that cur? It is a very efficient remedy... I have to go now - I don't want to keep 'Consumption' waiting.";
			link.l1.go = "Sergio_19";
		break;
		
		case "Sergio_19":
			DialogExit();
			AddQuestRecord("Consumption", "11");
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "OpenTheDoors", -1);
			pchar.quest.Consumption5.win_condition.l1 = "location";
			pchar.quest.Consumption5.win_condition.l1.location = "Trinidad";
			pchar.quest.Consumption5.function = "Consumption_CreateJuan";
			pchar.quest.Consumption6.win_condition.l1 = "HardHour";
			pchar.quest.Consumption6.win_condition.l1.hour = 13;
			pchar.quest.Consumption6.function = "Consumption_FailJuan";
			// Сержио теперь наш друг и будет торговать смолами
			SetFunctionTimerCondition("Oil_PrepareSergio", 0, 0, 20, false); // таймер
		break;
		
		// генератор торговли смолами
		case "Sergio_20":
			dialog.text = "Oh, what a lucky meeting! Senor "+GetFullName(pchar)+"! I am so glad to see you!";
			link.l1 = "Senor Sergio! I have not expected to meet you! How are you? How's good old commandant?";
			link.l1.go = "Sergio_21";
		break;
		
		case "Sergio_21":
			dialog.text = "I am fine, and mister commandant has gone to Los-Teques mines - his filthy machinations with Juan Consumption have been revealed.";
			link.l1 = "Mines?! Upon my soul! I never thought that justice would be served in his case...";
			link.l1.go = "Sergio_22";
		break;
		
		case "Sergio_22":
			dialog.text = "Ah, if only it was, captain... He was just transferred and demoted. He serves at the garrison now, and he wasn't even stripped of the officer rank. Well, at least San Jose got rid of this scum.";
			link.l1 = "Well, so far so good. Though I expected more.";
			link.l1.go = "Sergio_23";
		break;
		
		case "Sergio_23":
			dialog.text = "Me neither. But let's forget about the scum - he doesn't deserve to be talked about. Senor, as I had heard that you ship was about to enter the port, I hurried to the pier with all haste. I have a deal for you.";
			link.l1 = "Really? I am listening.";
			link.l1.go = "Sergio_24";
		break;
		
		case "Sergio_24":
			dialog.text = "Captain, you seem to be a man who can be trusted. Another very significant thing is that you are French and you have your own ship. I suggest we conclude a trade agreement.";
			link.l1 = "Sounds promising! What kind of agreement?";
			link.l1.go = "Sergio_25";
		break;
		
		case "Sergio_25":
			dialog.text = "We'd better discuss this at another place - at the lighthouse in the keeper's hut. He is my old friend, and I trust him. Come to the lighthouse of San Jose today or tomorrow. I will be waiting for you. I am confident that you will find my proposal most interesting!";
			link.l1 = "Alright, senor Sergio. I'll see you there!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Oil_SergioRuntoMayak");
		break;
		
		case "Sergio_26":
			chrDisableReloadToLocation = true;//закрыть локацию
			pchar.quest.Oil_SetSergioToMayakOver.over = "yes"; //снять прерывание
			dialog.text = "Welcome again, senor. Let me put you in the matter. ";
			link.l1 = "I am all ears. ";
			link.l1.go = "Sergio_27";
		break;
		
		case "Sergio_27":
			dialog.text = "As you may already know, I am not only a soldier, but also a doctor. Why? Because I am a well educated man. My education stopped me from wasting my time here on women and drinks. Instead, I had organized several expeditions and managed to find a deposit of resin not far from here\nThis is a resource of strategic importance, this island is the only place where you can find the special resin which is used to build solid and lasting vessels\nA governor and a commandant ordered me to sell all of resin to the Spanish navy\nProblem is, that they pay me a half of its market price and I can't sell it somewhere else. Therefore, I offer you to buy it from me. It is a very important merchandise and it is very hard to get.";
			link.l1 = "What are conditions of our agreement? ";
			link.l1.go = "Sergio_28";
		break;
		
		case "Sergio_28":
			dialog.text = "According to my calculations, I will be able to collect 60 barrels per month without causing suspicions. Let's make a deal - every fifth of each month I will visit this lighthouse to have a drink with my friend. Come and join us if you want to buy the resin. Ten golden doubloons for a barrel\nYou pay for a whole batch and take it all at once. No pressure, it's up to you. Deal?";
			link.l1 = "That's a decent offer. Of course, that's a deal!";
			link.l1.go = "Sergio_29";
		break;
		
		case "Sergio_29":
			dialog.text = "Wonderful. Then on the fifth of each month I will drink a bottle of Canarian wine with my old friend, the keeper, waiting for you.";
			link.l1 = "Fine. Let's do it this way.";
			link.l1.go = "Sergio_30";
		break;
		
		case "Sergio_30":
			dialog.text = "I am glad that we have come to an agreement. See you, captain!";
			link.l1 = "Good luck in your resin business, senor!";
			link.l1.go = "Sergio_31";
		break;
		
		case "Sergio_31":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "OpenTheDoors", 5);
			pchar.questTemp.OilTrade = "true";
			pchar.quest.Oil_fail.win_condition.l1 = "NPC_Death";
			pchar.quest.Oil_fail.win_condition.l1.character = "Sergio";
			pchar.quest.Oil_fail.function = "Oil_TradeFail";
			AddQuestRecord("Unique_Goods", "4");
		break;
		
		case "oil_trade":
			dialog.text = "Hello, senor captain! You have come for a batch of resin, as I suppose.";
			link.l1 = "That's right, senor Sergio. Is everything ready?";
			link.l1.go = "oil_trade_1";
			link.l2 = "Senor Sergio, I am in no mood for trade. Maybe later.";
			link.l2.go = "oil_trade_exit";
		break;
		
		case "oil_trade_exit":
			DialogExit();
			NextDiag.CurrentNode = "oil_trade";
		break;
		
		case "oil_trade_1":
			dialog.text = "Yes. Have you got six hundred doubloons with you?";
			if (GetCharacterItem(pchar, "gold_dublon") >= 600)
			{
				link.l1 = "Sure. Here you are.";
				link.l1.go = "oil_trade_2";
			}
			else
			{
				link.l1 = "Tough luck! I've forgotten the money on my ship. I'll bring it here at once!";
				link.l1.go = "oil_trade_exit";
			}
		break;
		
		case "oil_trade_2":
			chrDisableReloadToLocation = true;//закрыть локацию
			RemoveItems(pchar, "gold_dublon", 600);
			Log_Info("You've given 600 doubloons");
			PlaySound("interface\important_item.wav");
			dialog.text = "It is pleasure to deal with you, captain. My people will help you with loading barrels on your ship.";
			link.l1 = "Thank you!";
			link.l1.go = "oil_trade_3";
		break;
		
		case "oil_trade_3":
			dialog.text = "The deal still stands. Should you need another batch, come back in a month.";
			link.l1 = "Alright, Sergio. See you.";
			link.l1.go = "oil_trade_4";
		break;
		
		case "oil_trade_4":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "OpenTheDoors", 5);
			AddCharacterGoods(pchar, GOOD_OIL, 60);
			AddCharacterExpToSkill(pchar, "Commerce", 200);
		break;
	// <-- генератор смол
		
		case "Juan_abordage":
			dialog.text = "Who the hell are you!?";
			link.l1 = "My name is "+GetFullName(pchar)+", as for you, Consumption, the devil is waiting for you - and he'll have your soul very soon!";
			link.l1.go = "Juan_abordage_1";
		break;
		
		case "Juan_abordage_1":
			if (CheckAttribute(pchar, "questTemp.Consumption.House"))
			{
				dialog.text = "This ship will blow up - a wick is already burning in the gunpowder room - why should we both die? Let's put the swords down. You will have enough time to get out, and I will jump off the ship, Galera Point is within spitting distance from here. If you need gold, take it! Five hundred doubloons, cash on the nail - and you forget about me, and I forget about you! Deal?";
				link.l1 = "Gold? I started all this not for money, Juan, but for killing the scum, and you are is the greatest reward on its own.";
				link.l1.go = "Juan_abordage_2";
				link.l2 = "Five hundred doubloons? You are laughing at me, Consumption. I think you've stacked here at least twice as much... Give me a thousand right now and you can go to hell, otherwise...";
				link.l2.go = "Juan_abordage_3";
			}
			else
			{
				dialog.text = "The ship is about to blow up, so I will have a good company, what do you think?";
				link.l1 = "You are talking too much, Consumption, get down to business!";
				link.l1.go = "Juan_abordage_5";
			}
		break;
		
		case "Juan_abordage_2":
			dialog.text = "We could have had an agreement... Eh!";
			link.l1 = "You took these poor people from their cells, and they could neither resist nor run away. You are a coward, Consumption, and you will die as a coward now.";
			link.l1.go = "Juan_abordage_5";
		break;
		
		case "Juan_abordage_3":
			dialog.text = "You've got a business grip, friend... Here - this is all I have. Not too much for a life, though, isn't it?";
			link.l1 = "Your life is not worth a bullet, so it seems that it's the most profitable bargain in my life. Now get lost.";
			link.l1.go = "Juan_abordage_4";
			TakeNItems(pchar, "gold_dublon", 1000);
			Log_Info("You received 1000 doubloons");
			PlaySound("interface\important_item.wav");
			ChangeCharacterComplexReputation(pchar, "nobility", -10);
			OfficersReaction("bad");
			pchar.questTemp.Consumption.TakeMoney = "true"; //атрибут для диалога
		break;
		
		case "Juan_abordage_4":
			DialogExit();
			chrDisableReloadToLocation = true;
			sld = &Characters[sti(pchar.GenQuest.QuestAboardCabinDialogIdx)];
			Lai_SetPlayerType(pchar);
			LAi_RemoveCheckMinHP(sld);
			LAi_SetImmortal(sld, true);
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "reload1", "none", "", "", "ConJuan_AfterFight_1", 10.0);
		break;
		
		case "Juan_abordage_5":
			dialog.text = "It is a pity that you will not have time to save everyone and kill me, will you? The wick is burning, and time passes...";
			link.l1 = "Damn it! I have to get the people out of here... Get lost, scum - you'll get what you deserve sooner or later!";
			link.l1.go = "Juan_abordage_4";
			link.l2 = "I will try anyway...";
			link.l2.go = "Juan_abordage_6";
			ChangeCharacterComplexReputation(pchar, "nobility", 5);
			OfficersReaction("good");
			sld = GetCharacter(NPC_GenerateCharacter("ConAndjelo", "citiz_9", "man", "man", 5, SPAIN, -1, true, "quest"));
			sld.name = "Angelo";
			sld.lastname = "";
			AddPassenger(pchar, sld, false);
			SetCharacterRemovable(sld, false);
		break;
		
		case "Juan_abordage_6":
			//LAi_SetCurHPMax(NPChar);
			//LAi_GetCharacterMaxEnergy(NPChar);			
			QuestAboardCabinDialogExitWithBattle("ConJuan_AfterFight_2"); 
			DialogExit();	
			AddDialogExitQuest("MainHeroFightModeOn");
			pchar.questTemp.Consumption.KillJuan = "true"; //атрибут для диалога
		break;
		
		case "Waitress":
			dialog.text = "Ah... I am speechless... What a nightmare!";
			link.l1 = "I couldn't do anything - alas! I am sorry. Farewell.";
			link.l1.go = "Waitress_1";
		break;
		
		case "Waitress_1":
			DialogExit();
			AddQuestRecord("Consumption", "16");
			Consumption_Close();
		break;
		
		case "Waitress_2":
			dialog.text = "Unbelievable! You... did you really save him? I have no idea how to thank you.";
			if (CheckAttribute(npchar, "quest.Consumption.sex"))
			{
				link.l1 = "I can imagine that, beauty. But my part of the deal is done now - just one little thing remains.";
				link.l1.go = "Waitress_3";
			}
			link.l2 = "Duty called - and I acted. That's it.";
			link.l2.go = "Waitress_5";
			if (CheckAttribute(pchar, "questTemp.Consumption.KillJuan")) AddQuestRecord("Consumption", "18");
			else AddQuestRecord("Consumption", "17");
		break;
		
		case "Waitress_3":
			dialog.text = "I ... oh God! You are right. For him, as I promised... Go upstairs into the room - we don't have much time.";
			link.l1 = "Let's hurry, then!";
			link.l1.go = "Waitress_4";
		break;
		
		case "Waitress_4"://благодарность натурой
			DialogExit();
			LocatorReloadEnterDisable("PortSpein_tavern", "reload1_back", true); //закрыть таверну
			LocatorReloadEnterDisable("PortSpein_tavern", "reload2_back", false); //открыть комнату
			bDisableFastReload = true;//закрыть переход
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload2_back", "PortSpein_tavern_upstairs", "goto", "goto3", "ConsumptionSexWaitress", -1);
			pchar.questTemp.Consumption.Sex = "true";
		break;
		
		case "Waitress_sex":
			dialog.text = "";
			link.l1 = "Well, sweetheart, let's pop up that cherry here! It's your lucky day, after all....";
			link.l1.go = "Waitress_sex_1";
		break;
		
		case "Waitress_sex_1":
			DialogExit();
			DoQuestCheckDelay("PlaySex_1", 0.1);
		break;
		
		case "Waitress_5":
			if (CheckAttribute(pchar, "questTemp.Consumption.KillJuan"))
			{
				dialog.text = "You are a real knight! Caballero! Here - don't take it as an insult, but I want you to take it. I collected this money to ransom Angelo, but now it is not important! Please, do not refuse - take it!";
				link.l1 = "Well, I will remember your eyes, senorita - they are so much more beautiful when they shine with the tears of happiness and not pain. I accept you gift. Bye, and good luck to you and Angelo.";
				link.l1.go = "Waitress_6";
				AddMoneyToCharacter(pchar, 5000);
			}
			else
			{
				dialog.text = "You are a real knight! Caballero! I will tell everybody! I will always remember you!";
				link.l1 = "Well, and I will remember your eyes, senorita - they are so much more beautiful when they shine with the tears of happiness and not pain. May you always be happy. Farewell!";
				link.l1.go = "Waitress_6";
			}
		break;
		
		case "Waitress_6":
			DialogExit();
			ChangeCharacterComplexReputation(pchar, "nobility", 3);
			Consumption_Close();
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}