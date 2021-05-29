// Addon-2016 Jason, французские миниквесты (ФМК) Гваделупа
void ProcessDialogEvent()
{
	ref sld, NPChar;
	aref Link, NextDiag;
	int i;
	string sTemp;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "An obvious bug. Tell the devs about it.";
			link.l1 = "Oh, I will.";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
		// квестодатель
		case "citizen":
			dialog.text = "Greeting, captain! I have a business proposal which you will find very interesting.";
			link.l1 = "Go on, monsieur.";
			link.l1.go = "citizen_1";
		break;
		
		case "citizen_1":
			dialog.text = "I want to hire your vessel for a transportation job from Guadeloupe to the Spanish Main.";
			link.l1 = "You want to sail there as a passenger?";
			link.l1.go = "citizen_2";
			link.l2 = "Spanish Main? I'll pass. We are not really friends with the Spanish. I suggest you finding another crew.";
			link.l2.go = "citizen_no";
		break;
		
		case "citizen_no":
			dialog.text = "As you say, captain, though it's not a high risk voyage. Farewell.";
			link.l1 = "Farewell.";
			link.l1.go = "citizen_exit";
		break;
		
		case "citizen_no_1":
			dialog.text = "As you wish, captain. Farewell!";
			link.l1 = "Farewell.";
			link.l1.go = "citizen_exit";
		break;
		
		case "citizen_exit":
			DialogExit();
			chrDisableReloadToLocation = false;
			npchar.lifeday = 0;
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload4_back", "none", "", "", "", 20.0);
		break;
		
		case "citizen_2":
			dialog.text = "Not quite so, monsieur. A passenger is a man dependable from a captain's will. I want to hire you, your crew and your ship in order to get myself along with two friends of mine to Panama.";
			link.l1 = "To Panama? How? You want to sail around the whole continent?";
			link.l1.go = "citizen_3";
		break;
		
		case "citizen_3":
			dialog.text = "Good joke, captain. Of course not. All your job is to deliver us to Mosquitoes Bay which is not far from Portobello. We'll make our way to Panama on our own, it won't be our first tour through the jungles.";
			link.l1 = "What about the payment?";
			link.l1.go = "citizen_4";
		break;
		
		case "citizen_4":
			dialog.text = "Two chests of doubloons. Three hundred pieces. You'll get one in advance once we are onboard. The second chest will be yours as soon as we reach our destination.";
			link.l1 = "A serious reward for such an easy job. What's the catch, my good man?";
			link.l1.go = "citizen_5";
		break;
		
		case "citizen_5":
			dialog.text = "Captain, time is money and me, my friends, we don't have it. We have to sail from here tonight and be there in ten days. This will be our second term. So, are you in?";
			link.l1 = "Deal!";
			link.l1.go = "citizen_6";
			link.l2 = "I am sorry, monsieur, but your proposal sounds way too suspicious to me. Find yourself another crew.";
			link.l2.go = "citizen_no_1";
		break;
		
		case "citizen_6":
			dialog.text = "Splendid. My friends are in the jungles at the moment, I'll let them know about our agreement. You'll find us at Capster bay tonight by ten o'clock. Don't be late, captain!";
			link.l1 = "Fine. Capster Bay, tonight, ten o'clock.";
			link.l1.go = "citizen_7";
		break;
		
		case "citizen_7":
			dialog.text = "A minute, captain, we didn't even introduce ourselves. My name is Bertrand Pinette. And you are...";
			link.l1 = ""+GetFullName(pchar)+". Captain "+GetFullName(pchar)+". See you, monsieur Pinette.";
			link.l1.go = "citizen_8";
		break;
		
		case "citizen_8":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "gate_back", "none", "", "", "OpenTheDoors", 20.0);
			AddQuestRecord("FMQ_Guadeloupe", "1");
			pchar.quest.FMQG_Capster.win_condition.l1 = "Hour";
			pchar.quest.FMQG_Capster.win_condition.l1.start.hour = 22.00;
			pchar.quest.FMQG_Capster.win_condition.l1.finish.hour = 23.99;
			pchar.quest.FMQG_Capster.win_condition.l2 = "Ship_location";
			pchar.quest.FMQG_Capster.win_condition.l2.location = "Shore29";
			pchar.quest.FMQG_Capster.win_condition.l3 = "location";
			pchar.quest.FMQG_Capster.win_condition.l3.location = "Shore29";
			pchar.quest.FMQG_Capster.function = "FMQG_CapsterBeach";
			SetFunctionTimerCondition("FMQG_StartLate", 0, 0, 1, false);
			pchar.questTemp.FMQG = "begin";
			pchar.GenQuest.SmugglersBlock = "baster_tavern";
		break;
		
		case "citizen_9":
			dialog.text = "Captain "+GetFullName(pchar)+", there you are. Are we good to go?";
			link.l1 = "Yes. Welcome aboard.";
			link.l1.go = "citizen_10";
		break;
		
		case "citizen_10":
			dialog.text = "Very well. Accept your advance - a chest full of doubloons. And remember - you have only ten days to get us to our destination. Not a day longer!";
			link.l1 = "I remember the terms. Don't be worry, we shall make it in time. Take your seats.";
			link.l1.go = "citizen_11";
		break;
		
		case "citizen_11":
			DialogExit();
			GiveItem2Character(pchar, "chest");
			log_info("You have received a chest full of doubloons");
			PlaySound("interface\important_item.wav");
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "officers", "sea_1", "none", "", "", "FMQG_OnBoard", 20.0);
			for (i=2; i<=3; i++)
			{
				sld = characterFromId("FMQG_pass_"+i);
				LAi_ActorRunToLocation(sld, "officers", "sea_"+i, "none", "", "", "", 10.0);
			}
			pchar.quest.FMQG_SailStart.win_condition.l1 = "location";
			pchar.quest.FMQG_SailStart.win_condition.l1.location = "Guadeloupe";
			pchar.quest.FMQG_SailStart.function = "FMQG_SailingStart";
			SetFunctionTimerCondition("FMQG_SailingLate", 0, 0, 10, false);
			SetFunctionTimerCondition("FMQG_MutiniActivate", 0, 0, 20, false);
			pchar.questTemp.FMQG = "sail";
			DeleteAttribute(pchar, "GenQuest.SmugglersBlock");
		break;
		
		case "citizen_12":
			dialog.text = "So, captain, you have completely fulfilled your part of the bargain. It's my turn now. Accept this chest along with our gratitude.";
			link.l1 = "Pleasure doing business with you, monsieur.";
			link.l1.go = "citizen_13";
		break;
		
		case "citizen_13":
			GiveItem2Character(pchar, "chest");
			log_info("You have receives a chest full of doubloons");
			PlaySound("interface\important_item.wav");
			AddCharacterExpToSkill(pchar, "Sailing", 200);//навигация
			AddCharacterExpToSkill(pchar, "Leadership", 200);//авторитет
			AddCharacterExpToSkill(pchar, "Sneak", 100);//скрытность
			dialog.text = "Likewise. Farewell, captain "+GetFullName(pchar)+".";
			link.l1 = "Farewell!";
			link.l1.go = "citizen_14";
		break;
		
		case "citizen_14":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "OpenTheDoors", 20.0);
			for (i=2; i<=3; i++)
			{
				sld = characterFromId("FMQG_pass_"+i);
				LAi_ActorRunToLocation(sld, "reload", "reload1_back", "none", "", "", "", 10.0);
				sld.lifeday = 0;
			}
			AddQuestRecord("FMQ_Guadeloupe", "6");
			CloseQuestHeader("FMQ_Guadeloupe");
			pchar.questTemp.FMQG = "pause";
			pchar.quest.FMQG_Continue.win_condition.l1 = "Ship_location";
			pchar.quest.FMQG_Continue.win_condition.l1.location = "Baster_town";
			pchar.quest.FMQG_Continue.win_condition.l2 = "location";
			pchar.quest.FMQG_Continue.win_condition.l2.location = "Baster_town";
			pchar.quest.FMQG_Continue.function = "FMQG_BasterContinue";
			pchar.quest.FMQG_Block1.win_condition.l1 = "Rank";
			pchar.quest.FMQG_Block1.win_condition.l1.value = 13;
			pchar.quest.FMQG_Block1.win_condition.l1.operation = ">=";
			pchar.quest.FMQG_Block1.function = "FMQG_Block";
			SetFunctionTimerCondition("FMQG_Block", 0, 0, 90, false);
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);	// лесник - открыть оружие снова.
		break;
		
		case "citizen_12a":
			dialog.text = "So, captain, here we are. You have fulfilled only half of your part of the bargain, so I will do the same. Keep your advance as a full pay. I hope you won't object, it was your fault after all.";
			link.l1 = "Can't say I like this, but I admit that you are right. Let's part our ways now.";
			link.l1.go = "citizen_13a";
		break;
		
		case "citizen_13a":
			AddCharacterExpToSkill(pchar, "Sailing", 50);//навигация
			AddCharacterExpToSkill(pchar, "Leadership", 50);//авторитет
			AddCharacterExpToSkill(pchar, "Sneak", 50);//скрытность
			dialog.text = "Anyways, thank you for the service, сcaptain "+GetFullName(pchar)+". Farewell!";
			link.l1 = "Farewell.";
			link.l1.go = "citizen_14";
		break;
		
		case "citizen_15":
			dialog.text = "Oh! What a meeting! "+TimeGreeting()+", "+GetFullName(pchar)+"! But how?";
			link.l1 = TimeGreeting()+", monsieur Pinette. It wasn't easy to find you.";
			link.l1.go = "citizen_16";
		break;
		
		case "citizen_16":
			sld = characterFromId("Baster_usurer");
			dialog.text = "And what's the reason, сaptain?";
			link.l1 = "My good sir, there is a man named "+GetFullName(sld)+" and he is very eager to see you. I assume you know why.";
			link.l1.go = "citizen_17";
		break;
		
		case "citizen_17":
			sld = characterFromId("Baster_usurer");
			dialog.text = "Sure, I do, but you, my dear captain, must also know that I am not eager to see monsieur "+GetFullName(sld)+" at all. Are you his bounty hunter? I just don't get it.";
			link.l1 = "Alas, but that is who I am at the moment and I am not happy about it. I made a mistake and now monsieur "+GetFullName(sld)+", damn him, have presented me with a choice. It's either your glorious return to Guadeloupe or it's my ass as an accomplice in your little endeavor of freeing don Carlos de Milyar. That will hurt me, you know that.";
			link.l1.go = "citizen_18";
		break;
		
		case "citizen_18":
			sld = characterFromId("Baster_usurer");
			dialog.text = "Ah, that bastard! This is a very sinful way to blackmail people!.. So, captain, what's your decision?";
			link.l1 = "And what do you think? I believe you are coming with me to Basse-Terre.";
			link.l1.go = "citizen_19";
			link.l2 = "Do I have a choice here?";
			link.l2.go = "citizen_25";
		break;
		
		case "citizen_19":
			dialog.text = "Oh, I must disappoint you, captain. I have no wish to get aboard of your beautiful ship. You won't achieve anything by force here, the place is surrounded by guards and I will scream for help in case you show any violent intentions. Sure, you may try to stab me, but our good friend won't get any coins from a cold corpse. So, the most smart way for you at this moment - is to leave me be. I will allow you to go unharmed.";
			link.l1 = "Do you really believe that I will just walk away after everything happened? You have dragged me into this mess, bastard, time to cash out!!";
			link.l1.go = "citizen_20";
			link.l2 = "You are right, I suppose. I like the idea of stabbing you, but it's pointless. Don't even try to hope that this is the end. I am leaving to Basse-Terre now where I will let our good friend know about your whereabouts. And then he will send masked men after you.";
			link.l2.go = "citizen_21";
		break;
		
		case "citizen_20":
			dialog.text = "A-ah! Soldiers! Help!!!";
			link.l1 = "...";
			link.l1.go = "citizen_fight";
		break;
		
		case "citizen_21":
			dialog.text = "But of course. Tell you boss to keep his masked men in line - I am getting popular these days. Farewell, captain.";
			link.l1 = "...";
			link.l1.go = "citizen_22";
		break;
		
		case "citizen_22":
			DialogExit();
			LAi_SetActorType(npchar);
			AddQuestRecord("FMQ_Guadeloupe", "19");
			pchar.quest.FMQG_Mayak.win_condition.l1 = "location";
			pchar.quest.FMQG_Mayak.win_condition.l1.location = "Mayak2";
			pchar.quest.FMQG_Mayak.function = "FMQG_Lighthouse";
		break;
		
		case "citizen_23":
			dialog.text = "Wait! I surrender! I surrender!";
			link.l1 = "Right on! Now drop your weapon and march to the ship!";
			link.l1.go = "citizen_24";
		break;
		
		case "citizen_24":
			DialogExit();
			chrDisableReloadToLocation = false;
			RemoveAllCharacterItems(npchar, true);
			DoQuestReloadToLocation("Mayak2", "goto", "goto1", "FMQG_OnLighthouse");
		break;
		
		case "citizen_25":
			dialog.text = "There is always a choice, captain. As far as understand, you wouldn't be hunting if there were no threats from that banker?";
			link.l1 = "Exactly.";
			link.l1.go = "citizen_26";
		break;
		
		case "citizen_26":
			dialog.text = "Good. Then I will organize you a solid way to shut his mouth. Let's write a letter which you will take to your employer. Tell him that if he ever starts talking, the governor of Guadeloupe will learn about the man who planned and invested in the disappearance of the Courage - a courier lugger on a mission to transport a large batch of diamonds.";
			link.l1 = "Hm. I think I am starting to follow, monsieur Pinette.";
			link.l1.go = "citizen_27";
		break;
		
		case "citizen_27":
			dialog.text = "Glad you are that smart, monsieur captain. De Lion will personally nail the sly scrooge's head to the city gates if he learn the truth behind the Courage's disappearance. In this letter, I am about to write, you will find evidences which will calm down the blackmailer. Give me a minute to get my pen.";
			link.l1 = "Alright...";
			link.l1.go = "citizen_28";
		break;
		
		case "citizen_28":
			LAi_Fade("", "");
			GiveItem2Character(pchar, "letter_baker");
			ChangeItemDescribe("letter_baker", "itmdescr_letter_pinett");
			dialog.text = "(writing) Here, take it. There are two similar letters in this package. Give one to the banker, let him enjoy it. Keep the other for yourself and keep it hidden.";
			link.l1 = " Is the information trustworthy?";
			link.l1.go = "citizen_29";
		break;
		
		case "citizen_29":
			sld = characterFromId("Baster_usurer");
			dialog.text = "I can swear on it. Rest assured, monsieur Pinette will leave you be once he read this testament. Ah, yes... One more thing, captain. Since we settled this peacefully... I have a stash and I will tell you where to find it if you promise me to stay away from my operations in the future. They won't let me to ever land a foot on Guadeloupe anyway.";
			link.l1 = "If the letter will work as intended then by all means I can promise you that.";
			link.l1.go = "citizen_30";
		break;
		
		case "citizen_30":
			dialog.text = "It's a deal then. Search within the rocks inside the cave of Guadeloupe. Let it serve you as modest compensation for your troubles. Godspeed, captain.";
			link.l1 = "Same to you, monsieur Pinette.";
			link.l1.go = "citizen_31";
		break;
		
		case "citizen_31":
			DialogExit();
			pchar.questTemp.FMQG = "letter";
			AddQuestRecord("FMQ_Guadeloupe", "24");
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeday = 1;
		break;
		
		case "citizen_fight":
			chrDisableReloadToLocation = true;
			LAi_group_Delete("EnemyFight");
			DialogExit();
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "OpenTheDoors");
			AddDialogExitQuest("MainHeroFightModeOn");
			DoQuestFunctionDelay("FMQG_PlantationGuards", 3.0);
			pchar.questTemp.FMQG = "fail";
			AddQuestRecord("FMQ_Guadeloupe", "18");
			CloseQuestHeader("FMQ_Guadeloupe");
		break;
		
		// вестовой к ростовщику
		case "cureer":
			dialog.text = "Greeting, monsieur! You are captain "+GetFullName(pchar)+", correct?";
			link.l1 = "Correct. What can I do for you?";
			link.l1.go = "cureer_1";
		break;
		
		case "cureer_1":
			sld = characterFromId("BasTer_usurer");
			dialog.text = "Monsieur "+GetFullName(pchar)+", the Basse-Terre bank owner is asking you to pay him a visit as soon as possible. He ordered me to check our port office every day to ensure that you arrival will not be missed.";
			link.l1 = "Interesting, and why would he be that eager to see me?";
			link.l1.go = "cureer_2";
		break;
		
		case "cureer_2":
			dialog.text = "Monsieur "+GetFullName(sld)+" will personally tell you why. I hope that you won't decline his invitation.";
			link.l1 = "Hm.. Fine. These bankers are a powerful folk and they never waste time on little fish. I'll go see the man as soon as possible.";
			link.l1.go = "cureer_3";
		break;
		
		case "cureer_3":
			dialog.text = "Thank you, captain. Farewell!";
			link.l1 = "Farewell.";
			link.l1.go = "cureer_4";
		break;
		
		case "cureer_4":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload4_back", "none", "", "", "", 10.0);
			chrDisableReloadToLocation = false;
			LocatorReloadEnterDisable("Baster_town", "reload1_back", true);
			LocatorReloadEnterDisable("Baster_town", "reload2_back", true);
			LocatorReloadEnterDisable("Baster_town", "gate_back", true);//закрыть выходы из города
			pchar.questTemp.FMQG = "continue";
			pchar.quest.FMQG_Block.over = "yes";
			pchar.quest.FMQG_Block1.over = "yes";
		break;
		
		// Жан Дено
		case "Juan":
			dialog.text = "Argh! You scum! No way it is a random meeting...";
			link.l1 = "True to that, Jean... beg pardon, I mean Juan. I have tracked you down. Now would you kindly move yourself inside my cargo hold? Blow off some steam and we'll talk.";
			link.l1.go = "Juan_1";			
		break;
		
		case "Juan_1":
			DialogExit();
			Lai_SetPlayerType(pchar);
			DeleteAttribute(npchar, "DontRansackCaptain");
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", 3.0);
			pchar.questTemp.FMQG.Prisoner = GetFullName(npchar);
			pchar.GenQuest.LastQuestPrisonerIdx = SetCharToPrisoner(npchar);
			AddQuestRecord("FMQ_Guadeloupe", "14");
			pchar.questTemp.FMQG = "juan_capture";
			DoQuestCheckDelay("LAi_ReloadBoarding", 3.5);
		break;
		
		case "Juan_2":
			dialog.text = "";
			link.l1 = "I've fulfilled my part of the bargain. Now it's your turn. Shoot it and keep in mind the consequences of lying.";
			link.l1.go = "Juan_3";
		break;
		
		case "Juan_3":
			dialog.text = "You'll find Bertrand Pinette on Barbados, at the main plantation, to be more specific. He was going to continue his operations there. The plantation's overseer is a friend of his.";
			link.l1 = "What sort of operations?";
			link.l1.go = "Juan_4";
		break;
		
		case "Juan_4":
			dialog.text = "Same as he had at Guadeloupe. Half-legal trade, smuggling, slaves. I think he aims to do slave business and sugar trade, why would he had moved to a plantation otherwise?";
			link.l1 = "I see. Has he got any patrons among the English authorities?";
			link.l1.go = "Juan_5";
		break;
		
		case "Juan_5":
			dialog.text = "I guess. A curious character, he is. Always got friends everywhere.";
			link.l1 = "Anything else?";
			link.l1.go = "Juan_6";
		break;
		
		case "Juan_6":
			dialog.text = "Like what? Sly and smart, always know things, always got an ace in his hand. I didn't have much time to learn more about him.";
			link.l1 = "Got it. Fine, got to sail to Bridgetown. You are free to go, don Juan. Don't even think about warning Pinette. If I won't find him there, it's your ass on the line again.";
			link.l1.go = "Juan_7";
		break;
		
		case "Juan_7":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "", 10.0);
			npchar.lifeday = 0;
			chrDisableReloadToLocation = false;
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			pchar.questTemp.FMQG = "headhunter_pinett";
			AddQuestRecord("FMQ_Guadeloupe", "17");
			// Пинетта - в Бриджтаун
			sld = characterFromId("FMQG_pass_1");
			ChangeCharacterAddressGroup(sld, "Plantation_F2", "goto", "goto1");
			sld.Dialog.currentnode = "citizen_15";
			LAi_SetStayType(sld);
		break;
		
		case "killer":
			dialog.text = "I am sorry, pal. Nothing personal. You know too much, that's you problem.";
			link.l1 = "...";
			link.l1.go = "killer_1";
		break;
		
		case "killer_1":
			DialogExit();
			LAi_group_Delete("EnemyFight");
			int n = 2;
			if (MOD_SKILL_ENEMY_RATE > 6) n = 3;
			for (i=1; i<=n; i++)
			{
				sld = characterFromId("FMQG_killer_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "FMQG_KillersDestroy");
			//AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
