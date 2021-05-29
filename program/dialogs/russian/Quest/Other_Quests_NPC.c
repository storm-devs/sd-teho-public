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
		case "First time":
			dialog.text = "What do you want?";
			link.l1 = "Nothing.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
        
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////----------------------------------------- работорговец -----------------------------------------------------
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//--> пинас
		case "TakeShoreCap":
    		dialog.text = "Scoundrel! Big surprise to you!";
    		link.l1 = "What?";
    		link.l1.go = "Node_1";
		break;
		
		case "Node_1":
			dialog.text = "Ha-ha! No slaves here! You are here for them, right?";
			link.l1 = "Fuck. And I was thinking why the hell there were so many soldiers on a trading pinnace... A trap!";
			link.l1.go = "Node_2";
		break;
		
 		case "Node_2":
			dialog.text = "Yes, bastard, it is a trap. I am not a merchant, I am a military officer! Though you have won the fight, you won't get away from the judgement!";
			link.l1 = "And why is that? I will end you now, sink your ship and no one will know a thing.";
			link.l1.go = "Node_3";
		break;
		
 		case "Node_3":
			dialog.text = "You are wrong. Your business with that banker was revealed. Soon, the governor-general will learn about your little business and you won't get away from the hallows. But I will do you a favour by slaying you right now and right here!";
			link.l1 = "Try, you governor's dog!";
			link.l1.go = "Node_4";
		break;
		
 		case "Node_4":
 		    pchar.questTemp.Slavetrader = "TakeShoreCap_end"; //это состояние квеста для проверки у квестодателя
            AddQuestRecord("Slavetrader", "13");
			AddQuestUserData("Slavetrader", "sShipName", pchar.questTemp.Slavetrader.ShipName);
            pchar.quest.Slavetrader_DieHard.over = "yes";
			pchar.quest.Slavetrader_AfterBattle.over = "yes";
			pchar.quest.Slavetrader_ShoreShipsOver.over = "yes";
            Island_SetReloadEnableGlobal(pchar.questTemp.Slavetrader.Island, true);
		    LAi_SetCurHPMax(NPChar);
			LAi_GetCharacterMaxEnergy(NPChar);			
			QuestAboardCabinDialogExitWithBattle(""); 
			DialogExit();	
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "Slave_arest":
			dialog.text = "" + GetFullName(pchar) + ", in the name of the law, you are under arrest! Surrender your weapons and follow us!";
			link.l1 = "What is going on, officer? To surrender on what grounds?";
			link.l1.go = "Slave_arest_1";
		break;
		
		case "Slave_arest_1":
			dialog.text = "Don't try to play stupid, captain! Your dirty business was revealed. And for the slaughter you've committed and for the ship of " + NationNameGenitive(sti(npchar.nation)) + " that you sunk will see you hanged!";
			link.l1 = "Well, since you put it that way... Go fuck yourself!";
			link.l1.go = "Slave_arest_2";
		break;
		
		case "Slave_arest_2":
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			LAi_SetWarriorTypeNoGroup(npchar);
            LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
            LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
            LAi_group_SetCheck("EnemyFight", "OpenTheDoors");
            DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		//--> крыса в доме
		case "Rat_bandos":
			dialog.text = "Hey, what are you doing here?!";
    		link.l1 = "Why are so rude, good sir? Is rat Gontier hiding somewhere here, huh?";
    		link.l1.go = "Node_rat_1";
		break;
			
		case "Node_rat_1":
			dialog.text = "No he is not! Get out!";
			link.l1 = "Looks like you are lying. I will conduct a search of the house and I'll see...";
			link.l1.go = "Node_rat_2";
		break;
		
 		case "Node_rat_2":
			dialog.text = "Fuck you! Francois! Run! Guys, help me!";
			link.l1 = "Crap!";
			link.l1.go = "Node_rat_3";
		break;
		
		case "Node_rat_3":
            LAi_SetPlayerType(pchar);
            LAi_SetWarriorType(npchar);
            LAi_group_MoveCharacter(npchar, "EnemyFight");
            LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
            LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "Slavetrader_findTortugaRat1");
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "Rat_lover":
			dialog.text = "Oh! Don't rape me!";
    		link.l1 = "What? Where is Francois Gontier? Answer me, you filthy slut, or you will end you just like those fellows of yours!";
    		link.l1.go = "Rat_lover_1";
		break;
			
		case "Rat_lover_1":
			dialog.text = "No, no, I will tell you everything! He has jumped from the window and run away to his ship.";
    		link.l1 = "What ship? I know that there is no his ship in the port. Don't lie to me, girl, or it will get worse...";
    		link.l1.go = "Rat_lover_2";
		break;
			
		case "Rat_lover_2":
			dialog.text = "I am not lying, I swear! He said that he landed on a small island and got here on a longboat... He must be there! Don't hurt me!";
    		link.l1 = "Alright, it seems that you are telling the truth. Stay here and be quite. And try to make friends in the more clever way in the future. But, you know, I see your eyes and they are telling me that you've got no brains.";
    		link.l1.go = "Rat_lover_3";
			pchar.quest.Slavetrader_RatAttack.win_condition.l1 = "location";
            pchar.quest.Slavetrader_RatAttack.win_condition.l1.location = "Tortuga";//отправляем в локацию
            pchar.quest.Slavetrader_RatAttack.function = "Slavetrader_RatCorvette";//создание корвета
			SetFunctionTimerCondition("Slavetrader_RatCorvetteOver", 0, 0, 1, false);
		break;
			
		case "Rat_lover_3":
 		    LAi_SetPlayerType(pchar);
            SetCharacterRemovable(npchar, false);
            LAi_SetActorType(npchar);
			npchar.lifeday = 0;
			AddQuestRecord("Slavetrader", "21_9");
            DialogExit();
		break;
		
		//--> беглые рабы
		case "Slave_woman":
			dialog.text = "Spare us! Mercy! We surrender!";
    		link.l1 = "Oh, is that so? Go to the cargo hold now! I will shoot anyone who tries to play stupid!";
    		link.l1.go = "exit";
			AddDialogExitQuestFunction("Slavetrader_Slavewoman");
		break;
	//<--работорговец
			
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////----------------------------------------- Генераторы -----------------------------------------------------
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//--> Jason ------------------------ Сомнительное предложение -------------------------------------------	
		int iCGood;
		case "Contraoffer_patrol":
			chrDisableReloadToLocation = false;
			iCGood = sti(pchar.GenQuest.Contraoffer.Trader.Goods);
			pchar.GenQuest.Contraoffer.Trader.PatrolSumm = sti(pchar.GenQuest.Contraoffer.Trader.Summ)/3;
			dialog.text = "Well, well... What have we here? Don't you know that trading goods by and between individuals is forbidden in our colony?";
			link.l1 = "Is it, officer? To be honest, it is the first time I hear about that. This decree was passed not long ago, am I right?";
			link.l1.go = "Contraoffer_patrol_1";
			link.l2 = "What, trading " + GetGoodsNameAlt(iCGood)+ "? I don't see any " + GetGoodsNameAlt(iCGood)+ " around, officer. I see only these shiny coins... And he sees the same. Why won't you and your soldiers take a look at our coins too?";
			link.l2.go = "Contraoffer_patrol_pay1";
		break;
		
		case "Contraoffer_patrol_1":
			if (GetSummonSkillFromName(pchar, SKILL_SNEAK) > drand(120))
			{
				dialog.text = "You didn't know, huh? Hm... it looks like you are not lying. But nevertheless you have violated the law. I won't arrest you, but I am to make you to pay a fine. And the cargo... we will have a talk about it with the second participant of the deal.";
				link.l1 = "And how much is that fine?";
				link.l1.go = "Contraoffer_patrol_pay2";
			}
			else
			{
				dialog.text = "Don't play stupid, captain! Everyone knows that already, and for a long time already. I am arresting you both for smuggling and your cargo is to be confiscated.";
				link.l1 = "I don't like casemates, officer. I like the open sea... and I am going to sail there now. But it seems that I would have to do that only over your dead body.";
				link.l1.go = "Contraoffer_patrol_fight";
				link.l2 = "I have no choice, but to surrender. But I really had no idea!";
				link.l2.go = "Contraoffer_patrol_jail";
			}
		break;
		
		case "Contraoffer_patrol_pay1":
			iCGood = sti(pchar.GenQuest.Contraoffer.Trader.Goods);
			if (GetSummonSkillFromName(pchar, SKILL_FORTUNE) > drand(120))
			{
				dialog.text = "Now you are talking... Let's see your coins... I beleive, I've overheard a quite specific number - " + FindRussianMoneyString(sti(pchar.GenQuest.Contraoffer.Trader.Summ)) + ". Since we have got three participants now I'd like to get " + FindRussianMoneyString(sti(pchar.GenQuest.Contraoffer.Trader.PatrolSumm)) + ". That is from you and the same from your friend.";
				link.l1 = "Sure, officer. Here are my shiny coins, or, I am sorry, your shiny coins - you've just dropped them on the beach by accident... And there is no " + GetGoodsNameAlt(iCGood)+ " here, ha-ha, as I've told you.";
				link.l1.go = "Contraoffer_patrol_complete1";
				link.l2 = "Whoa! You are too greedy, officer. Didn't your mom tell you that greed is not good? I suppose that it would be cheaper for me to deal with you with my blade.";
				link.l2.go = "Contraoffer_patrol_fight";
			}
			else
			{
				dialog.text = "Are joking, captain? Do you want to offer me a bribe? You are under arrest! Seize him!";
				link.l1 = "Well, if you don't want to take a look at my money than take a look at my sword!";
				link.l1.go = "Contraoffer_patrol_fight";
				link.l2 = "I have no choice, but to surrender. But I really had no idea!";
				link.l2.go = "Contraoffer_patrol_jail";
			}
		break;
		
		case "Contraoffer_patrol_complete1":
			dialog.text = "Yes, it looks like you are correct... Nothing of interest here except of several gentlemen and my shiny coins. You are free to go, captain and we will have a talk with your partner.";
			link.l1 = "See you, officer. Don't hurt him.";
			link.l1.go = "Contraoffer_patrol_complete";
		break;
		
		case "Contraoffer_patrol_pay2":
			dialog.text = "" + FindRussianMoneyString(sti(pchar.GenQuest.Contraoffer.Trader.PatrolSumm)) + ". Thank my good mood.";
			link.l1 = "Thank you officer. I really had no idea... Here, I am ready to pay my fine.";
			link.l1.go = "Contraoffer_patrol_complete2";
			link.l2 = "I take it that you aren't that honest too, officer. Your fine is too big. I suppose that I will help this colony by saving it from your existence.";
			link.l2.go = "Contraoffer_patrol_fight";
		break;
		
		case "Contraoffer_patrol_complete2":
			dialog.text = "Fine. You may go now. And I advice you to study the local laws in order to avoid situations like this in the future. Go now, we have to deal with the second participant of the trade, he was aware of everything, that's for sure.";
			link.l1 = "Good day to you, officer.";
			link.l1.go = "Contraoffer_patrol_complete";
		break;
		
		case "Contraoffer_patrol_complete":
			AddMoneyToCharacter(pchar, -sti(pchar.GenQuest.Contraoffer.Trader.PatrolSumm));
			AddQuestRecord("Contraoffer", "6");
			CloseQuestHeader("Contraoffer");
			LAi_CharacterDisableDialog(npchar);
			DialogExit();
		break;
		
		case "Contraoffer_patrol_fight":
			AddQuestRecord("Contraoffer", "7");
			CloseQuestHeader("Contraoffer");
			ChangeCharacterNationReputation(pchar, sti(npchar.Nation), -5);
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			LAi_SetWarriorTypeNoGroup(npchar);
            LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
            LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
            LAi_group_SetCheck("EnemyFight", "OpenTheDoors");
            DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "Contraoffer_patrol_jail":
			dialog.text = "The commandant will deal with you. Follow me!";
			link.l1 = "...";
			link.l1.go = "Contraoffer_patrol_jail_exit";
		break;
		
		case "Contraoffer_patrol_jail_exit":
			GoToPrison(pchar.GenQuest.Contraoffer.Trader.City, sti(pchar.GenQuest.Contraoffer.Trader.Summ), 7);
			DialogExit();
			AddQuestRecord("Contraoffer", "8");
			CloseQuestHeader("Contraoffer");
			pchar.GenQuest.Contraoffer.Jail = "true";
		break;
	//<-- Сомнительное предложение	
		
	//Jason --> ----------------------------------- Неудачливый вор --------------------------------------------
		case "Device_poorman":
			dialog.text = "Good day. Do you want anything?";
			link.l1 = "I do, pal. I take it that you are my guy. It was you who has stolen "+pchar.GenQuest.Device.Shipyarder.Type+"  from the local shipyard? Everything leads to you, so no arguing.";
			link.l1.go = "Device_poorman_1";
		break;
		
		case "Device_poorman_1":
			switch (sti(pchar.GenQuest.Device.Shipyarder.Chance3))
			{
				case 0://выбросил
				if (sti(pchar.GenQuest.Device.Shipyarder.Chance2) != 1)
				{
					dialog.text = "I beg you, my lord! Yes, I have stolen this strange thing from the shipyard. But I failed to sell it, nobody needs such item. So I got rid of it. Spare me, good sir, blame my hunger, not me... I would never dare to steal anything otherwise!";
					link.l1 = "That's a problem... And I don't need you either. I need to find that "+pchar.GenQuest.Device.Shipyarder.Type+". Tell me where did you throw it away?";
					link.l1.go = "Device_poorman_0_1";
				}
				else //просто отдаст
				{
					dialog.text = "I beg you, my lord! Yes, I have stolen this strange thing from the shipyard. But I failed to sell it, nobody needs such item. I will give it to you. Here, take it, just don't hurt me and don't call the soldiers!";
					link.l1 = "Fine, you may live, thug. I don't need your skin, I need that instrument. Give it to me immediately and get lost!";
					link.l1.go = "Device_poorman_0_2";
				}
				break;
				case 1://упирается, хитрый или храбрый
					dialog.text = "What do you mean? What is "+pchar.GenQuest.Device.Shipyarder.Type+"? I don't get it!";
					link.l1 = "You will get it when I will search you or your corpse! Give it to me now!";
					link.l1.go = "Device_poorman_1_1";
				break;
				case 2://трусливый
					dialog.text = "Oh... What is the "+pchar.GenQuest.Device.Shipyarder.Type+"? I... and what is it?";
					link.l1 = "Don't try to play stupid or run away, I will catch you anyway. Just let me check your pockets...";
					link.l1.go = "Device_poorman_2_1";
				break;
			}
		break;
		
		case "Device_poorman_0_1"://идем на поиски
			dialog.text = "Just behind the city gates, not far from the jungles. I beg you, good sir! If you really need that thing you can pick it up by yourself. It still must be over there, I am sure.";
			link.l1 = "I should force you to find and bring it to me, but I fear that I would spend more time finding you than the "+pchar.GenQuest.Device.Shipyarder.Type+". I will do it myself. But I will find you if you are lying to me!";
			link.l1.go = "exit";
			AddQuestRecord("Device", "3");
			string sCity = pchar.GenQuest.Device.Shipyarder.City + "_ExitTown";
			ref rItm = ItemsFromID("Tool");
			rItm.shown = true;
			rItm.startLocation = sCity;
			rItm.startLocator = "item" + (rand(14)+1);
			Log_TestInfo("Device is at the locator " + rItm.startLocator);
			npchar.lifeday = 0;
			LAi_CharacterDisableDialog(npchar);
		break;
		
		case "Device_poorman_0_2"://получили девайс
			dialog.text = "Here, take it. Thank you, kind sir!";
			link.l1 = "Well, it must be what I was looking for... ha! You are free to go now. Move. And be careful next time.";
			link.l1.go = "exit";
			TakeNItems(pchar, "Tool", 1);
			Log_Info("You have received the stolen instrument");
			PlaySound("interface\important_item.wav");
			AddQuestRecord("Device", "4");
			npchar.lifeday = 0;
			LAi_CharacterDisableDialog(npchar);
		break;
		
		case "Device_poorman_1_1":
			pchar.GenQuest.Device.Shipyarder.Poorsumm = 1000+drand(1000);
			dialog.text = "Listen, are you talking about this instrument? It belongs to me and I haven't stolen it! And I am not going to give it to you for free. If you want to get it, pay me " + FindRussianMoneyString(sti(pchar.GenQuest.Device.Shipyarder.Poorsumm)) + ".";
			link.l1 = "Hm... Fine. I will pay you. Here are your coins and give the instrument to me!";
			link.l1.go = "Device_poorman_1_2";
			link.l2 = "Oh, really? Did you really think that I will trust you, miserable thief? Give the "+pchar.GenQuest.Device.Shipyarder.Type+" to me now or I will call the guards, so we could go together to the shipyard and decide whose this instrument really is.";
			link.l2.go = "Device_poorman_1_3";
			link.l3 = "Are you stupid, or what? Listen, bastard, you have got two options: either you give me the "+pchar.GenQuest.Device.Shipyarder.Type+" or I stab you and take the instrument from your dead body!";
			link.l3.go = "Device_poorman_1_4";
		break;
		
		case "Device_poorman_1_2":
			dialog.text = "Nice deal, captain! I suppose that we will all get our profits, he-he... take it.";
			link.l1 = "Less talking, thief! Don't think that I have trusted you, I just want to do it peacefully. These coins won't do anything good for you anyway. Get lost!";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, -sti(pchar.GenQuest.Device.Shipyarder.Poorsumm));
			TakeNItems(pchar, "Tool", 1);
			Log_Info("You have received the stolen instrument");
			PlaySound("interface\important_item.wav");
			AddQuestRecord("Device", "5");
			AddQuestUserData("Device", "sMoney", FindRussianMoneyString(sti(pchar.GenQuest.Device.Shipyarder.Poorsumm)));
			AddQuestUserData("Device", "sName", pchar.GenQuest.Device.Shipyarder.Type);
			npchar.lifeday = 0;
			LAi_CharacterDisableDialog(npchar);
		break;
		
		case "Device_poorman_1_3":
			if (sti(pchar.GenQuest.Device.Shipyarder.Chance2) == 0)//если мы в городе
			{
				dialog.text = "No! Don't call the guards! I...I will give you this damn instrument. Here, take it!";
				link.l1 = "That is much better know! Get lost now. You will end up hanging on a hallow, it is just a matter of time.";
				link.l1.go = "exit_device";
			}
			else//храбрый попался
			{
				dialog.text = "What guards, cap? It is just you and me here. You are arguing too much, so I will have to calm you down... with my blade.";
				link.l1 = "You dare to threaten me, scum?";
				link.l1.go = "Device_poorman_fight";
			}
		break;
		
		case "Device_poorman_1_4":
			if (sti(pchar.GenQuest.Device.Shipyarder.Chance2) == 0)//если мы в городе
			{
				dialog.text = "Ah! Help me! Murderer!";
				link.l1 = "Stop right there, dog!";
			link.l1.go = "exit";
				sld = characterFromId("Device_poorman");
				LAi_SetActorType(sld);
				LAi_ActorRunToLocation(sld, "reload", "reload1", "none", "", "", "", -1);
				sld.lifeday = 0;
				AddQuestRecord("Device", "7");
				CloseQuestHeader("Device");
				DeleteAttribute(pchar, "GenQuest.Device.Shipyarder");
			}
			else//храбрый попался
			{
				dialog.text = "Well, let's see who will stab who, captain!";
				link.l1 = "You dare to threaten me, scum?";
				link.l1.go = "Device_poorman_fight";
			}
		break;
		
		case "Device_poorman_2_1":
			dialog.text = "Searching? Please, good sire!";
			link.l1 = "Now listen, either you will peacefully give me the thing you have just stolen from the shipyard or I will take you to the commandant's office. You will give this thing to me anyway, but your heels will be burned with a red-hot iron first. Perhaps they will even hang you after that. The choice is yours.";
			link.l1.go = "Device_poorman_2_2";
			link.l2 = "Give me what you've stolen immediately, bastard, or I will end you right where you stand!";
			link.l2.go = "Device_poorman_2_3";
		break;
		
		case "Device_poorman_2_2":
			if (sti(pchar.GenQuest.Device.Shipyarder.Chance1) < 2)//тут уж как повезет
			{
				dialog.text = "Well, you will have to catch me first, if you want to take me to the commandant's office ...";
				link.l1 = "Hold right there, dog!";
				link.l1.go = "exit";
				AddQuestRecord("Device", "7");
				sld = characterFromId("Device_poorman");
				LAi_SetActorType(sld);
				LAi_ActorRunToLocation(sld, "reload", "reload1", "none", "", "", "", -1);
				sld.lifeday = 0;
				CloseQuestHeader("Device");
				DeleteAttribute(pchar, "GenQuest.Device.Shipyarder");
			}
			else
			{
				dialog.text = "No, don't take me to the commandant's office! I will give it myself! Here, take it, you must be looking for this thing. Nobody would buy it anyway...";
				link.l1 = "Eh, I suppose I could take you to the fort anyway... Fine, give me the tool and be gone!";
				link.l1.go = "exit_device";
			}
		break;
		
		case "Device_poorman_2_3"://напугали
			dialog.text = "Ouch! Don't hurt me, I will give everything I have to you! Here, take it!";
			link.l1 = "Now you are talking! Get lost, I will deliver you to the commandant if I ever see you again in this town. Farewell!";
			link.l1.go = "exit_device";
		break;
		
		case "exit_device":
			npchar.lifeday = 0;
			TakeNItems(pchar, "Tool", 1);
			Log_Info("You have received the stolen instrument");
			PlaySound("interface\important_item.wav");
			AddQuestRecord("Device", "6");
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
		break;
		
		case "Device_poorman_fight":
			chrDisableReloadToLocation = true;
			sld = characterFromId("Device_poorman");
			TakeNItems(sld, "Tool", 1);
			sld.SaveItemsForDead = true; // сохранять на трупе вещи
            sld.DontClearDead = true; // не убирать труп через 200с
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
            LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
            LAi_group_SetCheck("EnemyFight", "OpenTheDoors");
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
			AddQuestRecord("Device", "8");
			AddComplexSelfExpToScill(30, 30, 30, 50);
		break;
	//<-- Неудачливый вор
//-------------------------------------------почтовый генератор 2 уровня------------------------------------	
		case "PostGopHunters":
			dialog.text = "Stop right there, pal! We need a thing which you are carrying. Give it to us and then walk your way.";
			link.l1 = "What is that thing are you talking about?";
			link.l1.go = "PostGopHunters_1";
			link.l2 = "These street folks are too insolent nowadays... Prepare yourself, scoundrels!";
			link.l2.go = "PostHunters_fight";
		break;
		
		case "PostGopHunters_1":
			dialog.text = "Don't pretend of being a fool! Give us the package and you will live. Otherwise... we will take it from your corpse!";
			link.l1 = "The odds are in your favor... take it, bastards, I have got no choice.";
			link.l1.go = "PostGopHunters_2";
			link.l2 = "Try!";
			link.l2.go = "PostHunters_fight";
		break;
		
		case "PostGopHunters_2":
			dialog.text = "Watch you tongue, pal... It's clever of you to don't challenge you luck. The end would have been the same, ha-ha! You'll live for a while... See you.";
			link.l1 = "...";
			link.l1.go = "exit_gophunter";
		break;
		
		case "PostProfHunters":
			dialog.text = "Wait, " + GetAddress_Form(NPChar) + ", don't hurry like that. I have got a business for you.";
			link.l1 = "What business? I don't know you.";
			link.l1.go = "PostProfHunters_1";
		break;
		
		case "PostProfHunters_1":
			dialog.text = "I do know you, captain. Now straight to the business. You have just received "+pchar.questTemp.WPU.Current.Add+" in "+XI_ConvertString("Colony"+pchar.questTemp.WPU.Postcureer.City+"Gen")+". Don't try to deny it, we know this for sure - after all, we have been looking for this document for a few days.";
			link.l1 = "Now I see. So what?";
			link.l1.go = "PostProfHunters_2";
		break;
		
		case "PostProfHunters_2":
			dialog.text = "Give me the package and our brief meeting ends. Don't try to play hero, captain, we intend to get these papers and we are ready to fight the city garrison if we must\nAs you might understand, you will die first if the skirmish is to start. So give us the documents and we'll part as friends.";
			link.l1 = "The odds are in your favour... take it, bastards, I have got no other choice.";
			link.l1.go = "PostProfHunters_3";
			link.l2 = "You won't scare me, I have seen tougher guys in the sea! Piss off.";
			link.l2.go = "PostProfHunters_4";
		break;
		
		case "PostProfHunters_3":
			dialog.text = "I am glad that you were reasonable, captain. You have put yourself in a great danger by taking this job. Now I am going to take my leave, if you don't mind.";
			link.l1 = "...";
			link.l1.go = "exit_profhunter";
		break;
		
		case "PostProfHunters_4":
			dialog.text = "It was your decision...";
			link.l1 = "...";
			link.l1.go = "PostHunters_fight";
			TraderHunterOnMap();//если деремся - запускаем ДУ вдогонку
		break;
		
		case "PostHunters_fight":
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
            LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
            LAi_group_SetCheck("EnemyFight", "OpenTheDoors");
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "exit_gophunter":
			chrDisableReloadToLocation = false;
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			RemoveItems(PChar, pchar.questTemp.WPU.Current.Item, 1);
			for (i=1; i<=4; i++)
			{
				sld = characterFromId("PostHunters"+i);	
				LAi_SetActorType(sld);
				LAi_ActorGoToLocation(sld, "reload", "reload1_back", "none", "", "", "", 5.0);
			}
			AddQuestRecord("Postcureer", "11");
			DialogExit();
		break;
		
		case "exit_profhunter":
			chrDisableReloadToLocation = false;
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			RemoveItems(PChar, pchar.questTemp.WPU.Current.Item, 1);
			for (i=1; i<=2; i++)
			{
				sld = characterFromId("PostHunters"+i);	
				LAi_SetActorType(sld);
				LAi_ActorGoToLocation(sld, "reload", "reload1_back", "none", "", "", "", 5.0);
			}
			AddQuestRecord("Postcureer", "12");
			pchar.questTemp.WPU.Postcureer.fail = "true";
			DialogExit();
		break;
		
		case "PostAgent":
			bDisableFastReload = true; 
			dialog.text = "Wait, " + GetAddress_Form(NPChar) + ", don't hurry like that. I have got a business for you.";
			link.l1 = "What business? Speak it quickly, I am in a hurry.";
			link.l1.go = "PostAgent_1";
		break;
		
		case "PostAgent_1":
			dialog.text = "I know who you are. And I also know that you have just received a "+pchar.questTemp.WPU.Current.Add+" "+XI_ConvertString("Colony"+pchar.questTemp.WPU.Postcureer.City+"Gen")+". These papers are the reason why I am so eager to talk with you.";
			link.l1 = "And I don't want to discuss this matter with the people I don't know. Do you want to get those papers? Just give me a reason...";
			link.l1.go = "PostAgent_2";
		break;
		
		case "PostAgent_2":
			dialog.text = "Enough, captain! Do I look like a robber? I am a businessman and I represent interests of " + NationNameGenitive(sti(pchar.questTemp.WPU.Postcureer.EnemyNation)) + ". I want to offer you a very profitable deal, but not here. Lets go to the tavern room and discuss this matter. It won't take a lot of your time.";
			link.l1 = "That is way too suspicious... I am not going to have any business with you, sir! Get lost!";
			link.l1.go = "PostAgent_getout";
			link.l2 = "Hm.. Let's see what you can offer me. But don't even try to attack me. Let's move, I will follow you.";
			link.l2.go = "PostAgent_3";
		break;
		
		case "PostAgent_getout":
			dialog.text = "You are a stubborn and a foolish man, captain! I have offered you a chance to make easy money. And you... you will regret it.";
			link.l1 = "Piss off!";
			link.l1.go = "PostAgent_getout_exit";
		break;
	
		case "PostAgent_3":
			dialog.text = "Splendid! Follow me.";
			link.l1 = "...";
			link.l1.go = "exit";
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			NextDiag.TempNode = "PostAgent_inTavern";
			sld = characterFromId("PostAgent");	
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "reload4_back", pchar.questTemp.WPU.Postcureer.StartCity +"_tavern_upstairs", "goto", "goto1", "PostAgent_inTavern_Room", -1);
		break;
		
		case "PostAgent_getout_exit":
			bDisableFastReload = false; 
			chrDisableReloadToLocation = false;
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			sld = characterFromId("PostAgent");	
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "reload1_back", "none", "", "", "", 10);
			pchar.questTemp.WPU.Postcureer.AgentIslandID = GetCharacterCurrentIslandId(pchar);
			pchar.quest.Postcureer_Hunter.win_condition.l1 = "Location";
			pchar.quest.Postcureer_Hunter.win_condition.l1.location = pchar.questTemp.WPU.Postcureer.AgentIslandID;
			pchar.quest.Postcureer_Hunter.function = "PostcureerAgent_ShipAttack";
			AddQuestRecord("Postcureer", "13");
			DialogExit();
		break;
		
		case "PostAgent_inTavern":
			dialog.text = "Now we can talk freely.";
			link.l1 = "And what is your proposal?";
			link.l1.go = "PostAgent_inTavern_1";
		break;
		
		case "PostAgent_inTavern_1":
			dialog.text = "As I said, this is all about the papers you have received at harbour office. All I need is a copy of them, that's it\nYou will keep the original, so they'll pay you for the job. No one will ever know what happened, besides I will pay you well.";
			link.l1 = "Excuse me... But the package is sealed. You won't be able to make copies without breaking a seal!";
			link.l1.go = "PostAgent_inTavern_2";
		break;
		
		case "PostAgent_inTavern_2":
			dialog.text = "I was expecting this question. I will have to break the seal, but don't worry I will be able to restore it. I have got a duplicate cliche and sealing wax of course. No one will notice that the package was opened.";
			link.l1 = "Do you have a false cliche of the port's administration of " +XI_ConvertString("Colony"+pchar.questTemp.WPU.Postcureer.StartCity+"Gen")+ "?";
			link.l1.go = "PostAgent_inTavern_3";
		break;
		
		case "PostAgent_inTavern_3":
			pchar.questTemp.WPU.Postcureer.AgentMoney = sti(pchar.rank)*3500;
			dialog.text = "Why are you asking, captain? Yes, I have one. Do you really think that I am just playing around? I am offering you "+ FindRussianMoneyString(sti(pchar.questTemp.WPU.Postcureer.AgentMoney))+" for a possibility to see these papers. So, will you give me the package at last? Please.";
			link.l1 = "Take it. Do it accurately!";
			link.l1.go = "PostAgent_inTavern_4";
			link.l2 = "You know, I will not. I don't like it.";
			link.l2.go = "PostAgent_inTavern_getout";
		break;
		
		case "PostAgent_inTavern_4":
			dialog.text = "Don't worry. I am a professional. Take a sit and have a rest. It will take about an hour.";
			link.l1 = "Fine.";
			link.l1.go = "PostAgent_inTavern_5";
		break;
		
		case "PostAgent_inTavern_5":
			NextDiag.currentnode = "PostAgent_inTavern_6";
			RemoveItems(PChar, pchar.questTemp.WPU.Current.Item, 1);
			pchar.questTemp.WPU.Postcureer.AgentChance = drand(4);//шанс, что раскроют обман - 20%
			DialogExit();
			AddDialogExitQuest("PostAgent_inTavern_Room_end");
		break;
		
		case "PostAgent_inTavern_getout":
			dialog.text = "Hm... I didn't see this coming. You are too stubborn, captain, so I will have to kill you right where you stand and take the package for free. Pray, because I work with my blade just as good as I work with false cliches.";
			link.l1 = "It is you who should pray, spy!";
			link.l1.go = "PostAgent_inTavern_fight";
		break;
		
		case "PostAgent_inTavern_6":
			dialog.text = "Done. As I said, it has been done in the most accurate way. Take the package and promised "+ FindRussianMoneyString(sti(pchar.questTemp.WPU.Postcureer.AgentMoney))+". And I have to go. Good luck, captain, I am glad that we had a deal.";
			link.l1 = "Farewell...";
			link.l1.go = "PostAgent_inTavern_7";
		break;
		
		case "PostAgent_inTavern_7":
			DialogExit();
			bDisableFastReload = false;
			chrDisableReloadToLocation = false; 
			AddMoneyToCharacter(pchar, sti(pchar.questTemp.WPU.Postcureer.AgentMoney));
			GiveItem2Character(pchar, pchar.questTemp.WPU.Current.Item);
			sld = characterFromID("PostAgent");        
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "reload1", "none", "", "", "", 2);
			AddQuestRecord("Postcureer", "15");
			AddQuestUserData("Postcureer", "sMoney", FindRussianMoneyString(sti(pchar.questTemp.WPU.Postcureer.AgentMoney)));
		break;
		
		case "PostAgent_inTavern_fight":
			bDisableFastReload = false;
			sld = characterFromID("PostAgent"); 
			LAi_group_MoveCharacter(sld, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
            LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
            LAi_group_SetCheck("EnemyFight", "OpenTheDoors");
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
			AddQuestRecord("Postcureer", "16");
		break;
	//<-- почтовый генератор 2 уровня
		
	// --> --------------------------------- эскорт 2 уровень --------------------------------------------------
		case "DisasterCap":
			dialog.text = "Greetings! Oh, I am so glad to see you!";
			link.l1 = "Good day. Hm, tell me, aren't you in command of the "+pchar.questTemp.WPU.Escort.ShipName+"?";
			link.l1.go = "DisasterCap_1";
		break;
		
		case "DisasterCap_1":
			dialog.text = "Oh! And how did you find out about the "+pchar.questTemp.WPU.Escort.ShipName+"? Yes, I am her cap. Or I was... The ship was sunk not far from here.";
			link.l1 = "Ah, and I have found you... Let me introduce myself - " + GetFullName(pchar) + ". I am here by the ask of the harbour master of "+XI_ConvertString("Colony"+pchar.questTemp.WPU.Escort.StartCity+"Gen")+". He briefly told me about your caravan's troubles and sent me to find your ship.";
			link.l1.go = "DisasterCap_2";
		break;
		
		case "DisasterCap_2":
			dialog.text = "So you are a captain of the rescue party?";
			link.l1 = "Something like that. My task was to find your ship or proofs of her death. Unfortunately, I haven't found the ship, but her captain is alive, that is a good thing for sure...";
			link.l1.go = "DisasterCap_3";
		break;
		
		case "DisasterCap_3":
			dialog.text = "Oh, I am sorry, I forgot to introduce myself. I am " + GetFullName(npchar) + ". Do you already know how did we end up here? The storm made our ship uncontrollable\nA few days later, she hit the reefs not far from this bay and the gale destroyed her in minutes. Only a few dozens of my crew survived. The rest are lying at the bottom. We pray for their souls every day...";
			link.l1 = "Accept my condolences, captain " + GetFullName(npchar) + ". I am so sorry.";
			link.l1.go = "DisasterCap_4";
		break;
		
		case "DisasterCap_4":
			dialog.text = "Thank you... Survivors have set up a camp on the shore, hoping to get aid. You are just in time, captain! The local war-like Indians are aware of our presence, we will not stand a chance against hundreds of them if they attack us\nThere is also a pirate ship, cruising in this area, it looks like they are looking for us. Have you met this pirate, captain?";
			link.l1 = "No I haven't.";
			link.l1.go = "DisasterCap_5";
		break;
		
		case "DisasterCap_5":
			dialog.text = "Praise the Lord for that. He is one of those who attacked us before that damn storm. Like a hyena, he is eager to finish a wounded pray, so he has arrived here, to this island.";
			link.l1 = "I see. Now it's time to decide what we do next.";
			link.l1.go = "DisasterCap_6";
		break;
		
		case "DisasterCap_6":
			dialog.text = "To decide what, captain? Take us aboard and let's get away from this cursed place.";
			link.l1 = "Absolutely. I have failed to save the ship, at least I will save her crew. Roll up your camp and I will order to send longboats here. Welcome aboard!";
			link.l1.go = "DisasterCap_7";
		break;
		
		case "DisasterCap_7":
			PlaySound("people fight\rifle_fire1.wav");
			PlaySound("people fight\player_man_shoot_01.wav");
			dialog.text = "Gratitude, captain! It won't take long. Wait... What the hell? Argh! Those red-skinned devils are coming for us again! Alarm! To arms!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("DisasterShipCrew_IndianAttack");
		break;
		
		case "DisasterCap_8":
			dialog.text = "Fuh, we have made it... See, captain, I have told you that this bay is the hell itself. It is the third Indian attack already! We have to leave this place as soon as possible, we won't survive another attack.";
			link.l1 = "Yes, you are right. Gather every living soul and move on my ship! I will order to send us longboats immediately!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("DisasterShipCrew_onBoard");
			AddQuestRecord("Escort", "38");
			AddQuestUserData("Escort", "sIsland", XI_ConvertString(pchar.questTemp.WPU.Current.TargetIslandID));
			AddQuestUserData("Escort", "sSName", pchar.questTemp.WPU.Escort.ShipName);
			AddQuestUserData("Escort", "sShore", XI_ConvertString(pchar.questTemp.WPU.Current.TargetIslandID.Shore));
		break;
	// <-- эскорт 2 уровень
		
	//Jason --> -------------------------- Заносчивый аристократ ------------------------------------------------
		case "Badboy":
			dialog.text = "Hic... What do you want from me? Get lost I have no wish to talk with you.";
			link.l1 = "Are you "+pchar.GenQuest.Badboy.Brothel.Name+"?";
			link.l1.go = "Badboy_1";
		break;
		
		case "Badboy_1":
			dialog.text = "Yes, I am. And what is your business?";
			link.l1 = "It is pretty simple. There is someone in this town who's got enough of your tricks. This person is fed up of them. Now I look at you and I see why. Don't show up in the local brothel ever again or you will get troubles. Got it?";
			link.l1.go = "Badboy_2";
		break;
		
		case "Badboy_2":
			switch (sti(pchar.GenQuest.Badboy.Brothel.Type))
			{
				case 0://или напугается, или будет быковать - от авторитета
					if (GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) < 30)
					{
						dialog.text = "Argh! You... dare to threaten me, jerk? I will pin you on my blade and will cook you like a chicken on the spit!";
						link.l1 = "Prepare yourself, fucker!";
						link.l1.go = "Badboy_fight_1";
						NextDiag.currentnode = "Badboy_after_fight";
					}
					else
					{
						dialog.text = "What? What tricks? There weren't any tricks. I got drunk and had a spree for a few times in the brothel. Nobody is perfect... All right, all right, I will never use their services again. Satisfied now? You have my word.";
						link.l1 = "I hope that the word of honour means something to you and you are aware about consequences in case of breaking it. Keep that in mind. Farewell now.";
						link.l1.go = "exit";
						pchar.GenQuest.Badboy.Complete = "true";
						LAi_CharacterDisableDialog(npchar);
						npchar.lifeday = 0;
					}
				break;
				case 1://дуэль за городом
					dialog.text = "You are such an insolent man, sir! I swear that I will make you regret your words before the sunset. I challenge you! I suppose that we'd better fight in private, somewhere in quite. Jungles will do just fine, meet me there in two hours!";
					link.l1 = "A great idea! At least it would not be a problem to hide your corpse.";
					link.l1.go = "Badboy_duel";
					NextDiag.currentnode = "Badboy_duel_1";
					break;
				case 2://призовет на помощь дружков
					dialog.text = "What? What tricks? There were no any tricks. I got drunk and had a spree for a few times in the brothel. Nobody is perfect... All right, all right, I will never use their services. Satisfied now? You have my word.";
					link.l1 = "I hope that the word of honour means something to you and you are aware about consequences in case of breaking it. Keep that in mind. Farewell now.";
					link.l1.go = "exit_continue";
					pchar.GenQuest.Badboy.Continue = "true";
					NextDiag.currentnode = "Badboy_friends";
				break;
			}
		break;
		
		case "Badboy_fight_1":
			chrDisableReloadToLocation = true;
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			sld = characterFromId("Badboy");
			GetCharacterPos(pchar, &locx, &locy, &locz);
			ChangeCharacterAddressGroup(sld, pchar.GenQuest.Badboy.Brothel.City + "_tavern", "goto", LAi_FindNearestFreeLocator("goto", locx, locy, locz));
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
            LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			AddDialogExitQuest("MainHeroFightModeOn");
			LAi_SetCheckMinHP(npchar, 10.0, true, "Badboy_capture");
			DialogExit();
		break;
		
		case "Badboy_after_fight":
			dialog.text = "Wait! Stop! I surrender! Spare me!";
			link.l1 = "And than's how you are talking now!";
			link.l1.go = "Badboy_after_fight_1";
		break;
		
		case "Badboy_after_fight_1":
			dialog.text = "I beg you, please, spare me! I will do what you ask! I will never show up in that brothel!";
			link.l1 = "This pose suits only to a scum like you. I hope that this will be a lesson for you for the rest of your life. And behave yourself properly in this town.";
			link.l1.go = "Badboy_exit";
			link.l2 = "Sure, you won't. Your trickery will be ended here and now.";
			link.l2.go = "Badboy_killed";
			pchar.GenQuest.Badboy.Complete = "true";
		break;
		
		case "Badboy_exit":
			LAi_SetPlayerType(pchar);
			chrDisableReloadToLocation = false;
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], true);
			LAi_SetActorType(npchar);
			npchar.lifeday = 0;
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "", -1);
			DialogExit();
		break;
		
		case "Badboy_killed":
		DialogExit();
		LAi_SetImmortal(npchar, false);
		LAi_ActorAnimation(pchar, "shot", "Badboy_killed_end", 2.2);
		break;
		
		case "Badboy_duel":
			chrDisableReloadToLocation = true;//закрыть локацию
			LAi_LocationDisableOfficersGen(pchar.GenQuest.Badboy.Brothel.City + "_ExitTown", true);//офицеров не пускать
			locations[FindLocation(pchar.GenQuest.Badboy.Brothel.City + "_ExitTown")].DisableEncounters = true; //энкаутеры закроем
			pchar.quest.BadboyDuelTimer.win_condition.l1 = "Timer";
			pchar.quest.BadboyDuelTimer.win_condition.l1.date.hour  = sti(GetTime() + 2);
			pchar.quest.BadboyDuelTimer.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 0);
			pchar.quest.BadboyDuelTimer.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 0);
			pchar.quest.BadboyDuelTimer.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 0);
			pchar.quest.BadboyDuelTimer.function = "Badboy_duelstart";
			sld = characterFromId("Badboy");
			LAi_SetActorType(sld);
			GetCharacterPos(pchar, &locx, &locy, &locz);
			ChangeCharacterAddressGroup(sld, pchar.GenQuest.Badboy.Brothel.City + "_tavern", "goto", LAi_FindNearestFreeLocator("goto", locx, locy, locz));
			LAi_ActorGoToLocation(sld, "reload", "reload1", "none", "", "", "OpenTheDoors", -1);
			TakeNItems(sld, "jewelry5", rand(10)); 
			TakeNItems(sld, "jewelry3", rand(10)); 
			TakeNItems(sld, "jewelry1", rand(10)); 
			sld.money = 24560;
			sld.SaveItemsForDead = true; // сохранять на трупе вещи
			sld.DontClearDead = true; // не убирать труп через 200с
			LAi_RemoveLoginTime(sld); //удалить время логина
			SetFunctionTimerCondition("Badboy_duelOver", 0, 0, 1, false);
			DialogExit();
		break;
		
		case "Badboy_duel_1":
			dialog.text = "Time to go to hell, fucker! Pray for yourself, but do it fast, I don't have a whole damn day...";
			link.l1 = "Less talking, more fighting, scum!";
			link.l1.go = "Badboy_duel_2";
		break;
		
		case "Badboy_duel_2":
			chrDisableReloadToLocation = true;
			LAi_SetPlayerType(pchar);
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			LAi_group_SetCheck("EnemyFight", "Badboy_die");
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "exit_continue":
			sld = characterFromID("Badboy");        
			LAi_RemoveLoginTime(sld); // patch-6
			LAi_SetActorType(sld);
			GetCharacterPos(pchar, &locx, &locy, &locz);
			ChangeCharacterAddressGroup(sld, pchar.GenQuest.Badboy.Brothel.City + "_tavern", "goto", LAi_FindNearestFreeLocator("goto", locx, locy, locz));
			LAi_ActorRunToLocation(sld, "reload", "reload1", "none", "", "", "", -1);
			DialogExit();
		break;		
		
		case "Badboy_friends":
			dialog.text = "And there he is, this insolent bastard! Let's show him who owns this town, lads!";
			link.l1 = "Ah, you're such a degenerate! But I have warned you. You and your apes will be sent right to the hell in a minute!";
			link.l1.go = "Badboy_friends_fight";
		break;
		
		case "Badboy_friends_fight":
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
            LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
            LAi_group_SetCheck("EnemyFight", "OpenTheDoors");
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
			DeleteAttribute(pchar, "GenQuest.Badboy");
		break;
	//Jason <-- Заносчивый аристократ
		
	//Jason --> ------------------------------- Место под солнцем ----------------------------------------------
		case "Sunplace_Store":
			pchar.quest.SunplaceContinue_Over.over = "yes";
			dialog.text = "Greetings. What do you want?";
			link.l1 = "Aren't you "+pchar.GenQuest.Sunplace.Trader.Enemyname+"? You won't believe me, ha-ha. I want your head.";
			link.l1.go = "Sunplace_Store_1";
			link.l2 = "Hm... No... It is nothing. It looks like I was mistaken. Pardon me for bothering you.";
			link.l2.go = "Sunplace_Store_exit";
		break;
		
		case "Sunplace_Store_1":
			dialog.text = "What a silly joke, sir! Explain yourself or I will...";
			link.l1 = "And what are you going to do, miserable herring? You have done a bad turn to one good man and he is really upset. So pray now and do it quickly because I am in a hurry.";
			link.l1.go = "Sunplace_Store_3";
		break;
		
		case "Sunplace_Store_3":
			dialog.text = "What... what are you doing, sir! Help! Somebody help! Murderer!";
			link.l1 = "And I thought you would spend your last seconds on praying, at least you could've had a chance to reach the heavens...";
			link.l1.go = "Sunplace_Store_fight";
		break;
		
		case "Sunplace_Store_exit":
			sld = CharacterFromID("SunplaceTrader");
			sld.lifeday = 0;
			AddQuestRecord("Sunplace", "9");
			CloseQuestHeader("Sunplace");
			DialogExit();
			DeleteAttribute(pchar, "GenQuest.Sunplace.Trader");
			NextDiag.currentnode = "Sunplace_Store_repeat";
		break;
		
		case "Sunplace_Store_repeat":
			dialog.text = "You again? Why wouldn't you tell me what do you want?";
			link.l1 = "It is nothing.";
			link.l1.go = "exit";
		break;
		
		case "Sunplace_Store_fight":
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
			sld = CharacterFromID("SunplaceTrader");
			LAi_SetImmortal(sld, false);
			LAi_SetActorType(sld);
			LAi_ActorAfraid(sld, Pchar, true);
			sld = characterFromId(pchar.GenQuest.Sunplace.Trader.CityT + "_trader");
			LAi_group_Attack(sld, Pchar);
			pchar.quest.Kill_SunplaceTrader.win_condition.l1 = "ExitFromLocation";
			pchar.quest.Kill_SunplaceTrader.win_condition.l1.location = pchar.location;
			pchar.quest.Kill_SunplaceTrader.function = "Kill_SunplaceTrader";
		break;
	// <-- место под солнцем
		
	//------------------------------------- киллеры Лиги-------------------------------------------------------
		case "LigaHunters":
			dialog.text = "";
			link.l1 = "Ah?! What? What the hell are you doing here, damn you? Who has let you in?";
			link.l1.go = "LigaHunters_1";
		break;
		
		case "LigaHunters_1":
			dialog.text = "The league needs your life, captain...";
			link.l1 = "What? Fuck!";
			link.l1.go = "LigaHunters_2";
		break;
		
		case "LigaHunters_2":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			for (i=1; i<=2; i++)
			{
				sld = characterFromId("LigaHunter_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
            LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
            LAi_group_SetCheck("EnemyFight", "LigaHunters_Dead");
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
	// <-- киллеры Лиги
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		//замечание по обнаженному оружию от персонажей типа citizen
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
			dialog.text = NPCharSexPhrase(NPChar, "Listen, I am the citizen of this town and I'd ask you to hold down your blade.", "Listen, I am the citizen of this town and I'd ask you to hold down your blade.");
			link.l1 = LinkRandPhrase("Fine.", "Okay.", "Sure...");
			link.l1.go = "exit";
			}
			else
			{
				dialog.text = NPCharSexPhrase(NPChar, "Be careful, "+ GetSexPhrase("pal","girl") +", while running with a weapon. I can get nervous ...", "I don't like when there are "+ GetSexPhrase("men","who knows who") +" are walking in front of me with their weapon ready. It scares me...");
				link.l1 = LinkRandPhrase("I got it.", "It's okay.", "Don't worry...");
			}
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
			if (npchar.id == "Device_poorman") NextDiag.TempNode = "Device_poorman";
		break;
	}
}
