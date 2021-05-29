// Addon-2016 Jason, французские миниквесты (ФМК) Сент-Кристофер
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
		
		case "seafox":
			PlaySound("VOICE\Russian\military01.wav");
			dialog.text = TimeGreeting()+", captain. Allow me to introduce myself - lieutenant "+GetFullName(npchar)+", Royal Marines, St. Jones of Antigua. I have a favor to ask.";
			link.l1 = "Greetings lieutenant. My name is "+GetFullName(pchar)+". What kind of favor?";
			link.l1.go = "seafox_1";
		break;
		
		case "seafox_1":
			dialog.text = "Let me briefly explain the situation. Me and four of my subordinates were sailing from St. Jones to the shores of Sint-Maarten when a storm hit us hard. It didn't last long but it was enough for our old tub to spring a leak. We had to change our course and make a stop here. Turned out that repairing our vessel will take a lot of time which we do not posses at the moment\nWe are in a rush and got to make to Grand Case beach of Sint-Maarten. Help us out captain and I will make it worth your while. It's just a two days voyage for a generous pay.";
			link.l1 = "A military operation on the Dutch island? Hm...";
			link.l1.go = "seafox_2";
		break;
		
		case "seafox_2":
			dialog.text = "Don't worry. France is not in war with the Dutch. Just land us at the bay and that will be all. Is it a deal?";
			link.l1 = "Fine, I am in. It really is not that far from here. What about a reward?";
			link.l1.go = "seafox_3";
			link.l2 = "I am sorry, but I am heading in a different direction and it's urgent.";
			link.l2.go = "seafox_exit";
		break;
		
		case "seafox_exit":
			dialog.text = "As you say, captain. I'll keep looking then. Farewell!";
			link.l1 = "Farewell, lieutenant.";
			link.l1.go = "seafox_exit_1";
		break;
		
		case "seafox_exit_1":
			DialogExit();
			chrDisableReloadToLocation = false;
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload4_back", "none", "", "", "", 20.0);
			npchar.lifeday = 0;
		break;
		
		case "seafox_3":
			GiveItem2Character(pchar, "purse2"); 
			Log_Info("You have received a purse of doubloons");
			dialog.text = "Ten thousand pesos. Here's an advance.";
			link.l1 = "Good. Get yourself and your men aboard, let's not waste any time.";
			link.l1.go = "seafox_4";
		break;
		
		case "seafox_4":
			dialog.text = "Aye, captain!";
			link.l1 = "...";
			link.l1.go = "seafox_5";
		break;
		
		case "seafox_5":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload4_back", "none", "", "", "FMQN_SailMaarten", 10.0);
			AddQuestRecord("FMQ_Nevis", "1");
			pchar.questTemp.FMQN = "begin";
		break;
		
		case "seafox_6":
			PlaySound("VOICE\Russian\QuestMan04.wav");
			dialog.text = "Thank you for the transportation, captain! Sadly, and I am sorry for this, I can't pay you at the moment: I was expecting to see a lugger of ours in this area, but she's not here as you can clearly see. I have to ask for your help one more time. Could you wait at this bay for two or three days? Once we are back, take us to Antigua - trust me, colonel Fox will pay you a great deal.";
			link.l1 = "Hm... Obviously, I was expecting for something different...";
			link.l1.go = "seafox_7";
		break;
		
		case "seafox_7":
			dialog.text = "I know that captain, but alas: I have no money at all. I can promise you that you will get a full compensation for both voyages and for waiting for us here.";
			link.l1 = "I see. No choice there for me. Very well, lieutenant...";
			link.l1.go = "seafox_8";
		break;
		
		case "seafox_8":
			dialog.text = "Good. We are heading inside the island. Your waiting will last for about three days and not a day longer.";
			link.l1 = "Godspeed, sir...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("FMQN_EnglishmanGo");
		break;
		
		case "seafox_9":
			PlaySound("VOICE\Russian\QuestMan04.wav");
			dialog.text = "Hm... What a meeting! I though you'd be waiting for us at Grand Case beach, captain...";
			link.l1 = "Well, and I didn't expect to see you dressed like a Dutch colonial military!.. I was looking for you, sir.";
			link.l1.go = "seafox_10";
		break;
		
		case "seafox_10":
			dialog.text = "It's my disguise... Why were you looking for us, captain?";
			link.l1 = "To tell you the news. And the news is bad.";
			link.l1.go = "seafox_11";
		break;
		
		case "seafox_11":
			dialog.text = "Go on!";
			link.l1 = "I went to Philipsburg and talked with locals after your departure. Dutch know everything. They know about your squad and about your mission to rescue the captured high ranked officers.";
			link.l1.go = "seafox_12";
		break;
		
		case "seafox_12":
			dialog.text = "What the hell?! How did they learn about this?";
			link.l1 = "They say that one of your prisoners got too talkative. In return for his freedom he told the Dutch everything he knew about the rescue operation. Now Philipsburg is ready for your arrival and they are waiting for you. The area around this island is being patrolled by a war corvette. It is a trap, lieutenant.";
			link.l1.go = "seafox_13";
		break;
		
		case "seafox_13":
			dialog.text = RandSwear()+"And what are we supposed to do now? Hm...";
			link.l1 = "I suggest you sneaking into Grand Case beach tonight and get aboard of my vessel.";
			link.l1.go = "seafox_14";
		break;
		
		case "seafox_14":
			dialog.text = "And the mission? No way! You have no idea what it's like to fail colonel Fox's orders!";
			link.l1 = "You prefer gallows then?";
			link.l1.go = "seafox_15";
		break;
		
		case "seafox_15":
			dialog.text = "Not a chance... Captain, I need your help. We should do our best to save the day since we both got into this mess. I don't think that the Dutch would tolerate your role in this operation if they catch you.";
			link.l1 = "Go on.";
			link.l1.go = "seafox_16";
		break;
		
		case "seafox_16":
			dialog.text = "The prisoners must be released. We have taken care of the disguise already - take a look at this fancy uniform. If it wasn't for treason, we would just have gone to the local prison and killed everyone inside. But they must have laid an ambush there. We should use extra resources... Captain, go to Philipsburg's church and find a servant named Filippe Jacobsen. You can find him there from eight till ten in the morning. Filippe is a man of ours\nTell him a password: 'How long ago did the captive sailors confess?', tell him about the situation and demand his assistance in my name. Then you should deliver his answer to me. See? Nothing either hard or risky in this for you.";
			link.l1 = "I see. Fine, I'll do this. Tell me about this uniform... it was taken from a Dutch patrol, am I right?";
			link.l1.go = "seafox_17";
		break;
		
		case "seafox_17":
			dialog.text = "Correct.";
			link.l1 = "And where are they now?";
			link.l1.go = "seafox_18";
		break;
		
		case "seafox_18":
			dialog.text = "Held as hostages in the bushes not far away from this cave.";
			link.l1 = "Got it. Fine, I am heading to the town. Wait for me here and try to stay low - the Dutch are patrolling not only in a sea but also in jungles.";
			link.l1.go = "seafox_19";
		break;
		
		case "seafox_19":
			dialog.text = "Hurry up, captain!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("FMQN_ToChurch");
		break;
		
		case "seafox_20":
			PlaySound("VOICE\Russian\soldier_common_4.wav");
			dialog.text = "You again? Captain what are you doing here? Go to the town, don't hang about, you cause too much attention to our hideout...";
			link.l1 = "I am just from the town. What games are you playing?";
			link.l1.go = "seafox_21";
		break;
		
		case "seafox_21":
			dialog.text = "Beg pardon?";
			link.l1 = "I told you that I've been in the town recently. I was in the church. Guess what, there is no servant named Filippe Jacobsen.";
			link.l1.go = "seafox_22";
		break;
		
		case "seafox_22":
			dialog.text = "He visits the place every morning, I've told you already...";
			link.l1 = "Damn it! I was told that he never visited that place! Not in the morning, not in the evening. Fuck it! And why did I even agree on this job?! For fu-...";
			link.l1.go = "seafox_23";
		break;
		
		case "seafox_23":
			dialog.text = "Why are you behaving like an old hag, captain? Stop it!";
			link.l1 = ""+RandSwear()+"";
			link.l1.go = "seafox_24";
		break;
		
		case "seafox_24":
			PlaySound("Ambient\Jail\chain.wav");
			PlaySound("Ambient\Land\door_001.wav");
			dialog.text = "What? Shut up, all of you! What is it? Did you hear?..";
			link.l1 = "";
			link.l1.go = "seafox_25";
		break;
		
		case "seafox_25":
			PlaySound("Ambient\Land\cough_01.wav");
			dialog.text = "Fuck, someone is coming here! You brought the Dutch here you bastard! Traitor!";
			link.l1 = ""+RandSwear()+"!!!";
			link.l1.go = "exit";
			AddDialogExitQuest("FMQN_HollandBattleFight");
		break;
		
		case "seafox_26":
			pchar.quest.FMQN_fail1.over = "yes";
			PlaySound("VOICE\Russian\QuestMan04.wav");
			dialog.text = "How are you doing, captain?";
			link.l1 = "I've met you agent. He did his job. Tonight they will deliver a poisoned wine to the prison. Some gypsies' potion, it's not lethal, yet causes a dead dream. This night you should go there and get your prisoners out. By the way, this operation had cost me twenty five doubloons, hope this donation will be mentioned in the report.";
			link.l1.go = "seafox_27";
		break;
		
		case "seafox_27":
			dialog.text = "Don't worry about the money. Captain, I'd ask you to join us in this operation. Show us the way to the prison. You've been in Philipsburg already, so you must know it's layout. No need to go inside the prison with us, we'll do the job ourselves just get us there.";
			link.l1 = "Eh... This is getting just better and better! Fine, I will help you one more time.";
			link.l1.go = "seafox_28";
		break;
		
		case "seafox_28":
			dialog.text = "You won't regret it. Is your vessel at Grand Case beach?";
			if (pchar.location.from_sea == "Shore40")
			{
				link.l1 = "Yes.";
				link.l1.go = "seafox_29";
			}
			else
			{
				link.l1 = "No.";
				link.l1.go = "seafox_29x";
			}
		break;
		
		case "seafox_29":
			dialog.text = "Good. Then get ready and meet us at the town gates by eleven o'clock in the evening.";
			link.l1 = "Deal. See you there.";
			link.l1.go = "seafox_30";
		break;
		
		case "seafox_29x":
			dialog.text = "Then make sure to move the ship there, we will be leaving the island through the jungles to the beach in a hurry. Sailing from a port or Simpson bay is not an option because of the fort. Get everything ready and meet us at the town gates by eleven o'clock in the evening.";
			link.l1 = "Deal. See you there.";
			link.l1.go = "seafox_30";
		break;
		
		case "seafox_30":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			AddDialogExitQuestFunction("FMQN_EnglandPrepare");
		break;
		
		case "seafox_31":
			PlaySound("VOICE\Russian\Gr_hovernor01.wav");
			dialog.text = "Ready, captain?";
			link.l1 = "Yes.";
			link.l1.go = "seafox_32";
		break;
		
		case "seafox_32":
			dialog.text = "Let's not waste time then. Onwards!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("FMQN_EnglandReload");
		break;
		
		case "seafox_33":
			dialog.text = "Hushhhh... Captain! Quite! It's done, let's get the hell out of here!..";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuest("FMQN_EnglandRunToJungle");
		break;
		
		case "seafox_34":
			dialog.text = "It was a success. You did well, captain. Now for the final part - we should escape from this island in one piece. Move to Grand Case beach, hurry!";
			link.l1 = "Let's move!";
			link.l1.go = "exit";
			AddDialogExitQuest("FMQN_EnglandRunToShore");
		break;
		
		case "seafox_35":
			PlaySound("VOICE\Russian\QuestMan05.wav");
			dialog.text = "Thank you for your assistance, captain! You are a real hero! I'd ask to stay here for a one more day while I am reporting to colonel Fox. Pay him a visit tomorrow, his office is in the governor's palace.";
			link.l1 = "Very well, lieutenant. Please give me some credit out there. The Dutch don't like me much now because of you.";
			link.l1.go = "seafox_36";
		break;
		
		case "seafox_35x":
			PlaySound("VOICE\Russian\QuestMan05.wav");
			dialog.text = "Thank you for your assistance, captain! You are a real hero! Shame that lieutenant Caspar Gretton didn't make it. He died as a true soldier and a patriot of England. I'd ask to stay here for a one more day while I am reporting to colonel Fox. Pay him a visit tomorrow, his office is in the governor's palace.";
			link.l1 = "Very well. Please give me some credit out there. The Dutch don't like me much now because of you.";
			link.l1.go = "seafox_36";
		break;
		
		case "seafox_36":
			dialog.text = "Don't worry. I will give the best credit possible in my report. It was a pleasure sir!";
			link.l1 = "...";
			link.l1.go = "seafox_37";
		break;
		
		case "seafox_37":
			DialogExit();
			npchar.lifeday = 0;
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload3_back", "none", "", "", "", -1);
			pchar.quest.FMQN_eng_reward.win_condition.l1 = "Timer";
			pchar.quest.FMQN_eng_reward.win_condition.l1.date.hour  = 6.0;
			pchar.quest.FMQN_eng_reward.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.FMQN_eng_reward.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.FMQN_eng_reward.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.FMQN_eng_reward.function = "FMQN_EnglandReward";
			AddQuestRecord("FMQ_Nevis", "28");
		break;
		
		case "soldier":
			PlaySound("VOICE\Russian\soldier_common_2.wav");
			dialog.text = "Captain "+GetFullName(pchar)+"?";
			link.l1 = "Hm... Yes, it's me. What can I do for you?";
			link.l1.go = "soldier_1";
		break;
		
		case "soldier_1":
			dialog.text = "A port office has informed us about your recent arrival. His Excellence the governor of Philipsburg mynheer Martin Thomas desires to see you.";
			link.l1 = "I don't get it... Am I under arrest? What for?";
			link.l1.go = "soldier_2";
		break;
		
		case "soldier_2":
			dialog.text = "No, no, mynheer captain, you are not under arrest. The governor ordered to invite every new arrived captain to his office. We've got a situation here. Follow me!";
			link.l1 = "Ah, very well then... I am on my way!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("FMQN_ReloadToGovernor");
		break;
		
		case "hol_officer":
			PlaySound("VOICE\Russian\hol_gov_complete.wav");
			dialog.text = "So mynheer, show us the way to the place where you saw the suspects.";
			link.l1 = "We should go to a cave in the jungles. They are inside.";
			link.l1.go = "hol_officer_1";
		break;
		
		case "hol_officer_1":
			dialog.text = "Go then, we are following you!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuest("FMQN_HollandBattleMarch");
		break;
		
		case "hol_officer_2":
			PlaySound("VOICE\Russian\hol_gov_quest.wav");
			dialog.text = "Wait captain! You mentioned that you had met the spies over there - close to the cave's entrance?";
			link.l1 = "Yes. I briefly saw them going inside after they talked to me.";
			link.l1.go = "hol_officer_3";
		break;
		
		case "hol_officer_3":
			dialog.text = "Most likely they are still there. If we charge all at once - they will see us coming, take defensive positions in narrow corridors of the cave and will make it hard for us. Let's play this the other way. Captain, you will go there alone and distract them. Me and my men will move to a dry well around the corner. It leads right inside the cave. The bastards won't see us coming from there\nYou go inside and if the spies are still there, talk to them, ask them stupid questions, do whatever you want just make them busy with you. Once you have their absolute attention - swear as filthy as you can. You are a sailor, so you must excel in this. This will serve as a signal to us. Two of my men will guard the main entrance in order to prevent them from a possible escape. We'll get them.";
			link.l1 = "Hm... I believe that the spies will start hitting me first...";
			link.l1.go = "hol_officer_4";
		break;
		
		case "hol_officer_4":
			dialog.text = "Don't be afraid, captain. You goal is too shout as loud as you can as soon as you'll see the enemy raiding party. If they attack you - then run and keep shouting. Don't be shy, we need to hear you signal from the well. My men are well trained, so don't worry, they will do the job fast.";
			link.l1 = "I got it. Well... I am on my way.";
			link.l1.go = "exit";
			AddDialogExitQuest("FMQN_HollandBattlePosition");
		break;
		
		case "hol_officer_5":
			PlaySound("VOICE\Russian\hol_gov_common.wav");
			dialog.text = "Tough bastards they were... Nicely done, captain. Congratulations. English dogs are eliminated, our commandant and governor will be pleased.";
			link.l1 = "You took your time, mynheer...";
			link.l1.go = "hol_officer_6";
		break;
		
		case "hol_officer_6":
			dialog.text = "Blame the rope, it turned to be very old and noisy, had to be careful.";
			link.l1 = "There is one of yours missing patrols in the bushes. They might be still alive.";
			link.l1.go = "hol_officer_7";
		break;
		
		case "hol_officer_7":
			dialog.text = "I'll investigate. You should go to the town and take some rest. Pay a visit to our governor tomorrow, he'll have my report by then.";
			link.l1 = "I will. Godspeed mynheer.";
			link.l1.go = "exit";
			AddDialogExitQuest("FMQN_HollandBattleRest");
		break;
		
		case "monk":
			pchar.questTemp.FMQN = "way_eng_2";
			dialog.text = "What can I do for you, my son?";
			link.l1 = "I'd like to know of how long ago did the captive sailors confess?";
			link.l1.go = "monk_1";
		break;
		
		case "monk_1":
			dialog.text = "Yesterday evening, my son... Hush... Be quite... (whispering) I assume that you are already aware about the treason?";
			link.l1 = "Absolutely. I wouldn't be standing here otherwise. Lieutenant Casper Gratton's squad is in the jungles at the moment. All dressed like Dutch military, but we need extra assistance since there is an ambush set in prison.";
			link.l1.go = "monk_2";
		break;
		
		case "monk_2":
			dialog.text = "I prayed every day to save your from the path of ignorance. I have a plan already, yet I need two dozens of golden doubloons to get everything I need to perform it.";
			link.l1 = "What is the plan? Will you tell me?";
			link.l1.go = "monk_3";
		break;
		
		case "monk_3":
			dialog.text = "Of course. Soldiers stationed in prison are aware about English operation. The Dutch superiors provide them with extra portion of good wine every evening in order to support the moral. The wine is being transported from a warehouse I have an access to. There is a gypsy woman who is in my debt, she can give us a dream potion. All I need is to buy a few bottles of good wine, add the potion and change bottles in the warehouse. That's what I need money for.";
			if (GetCharacterItem(pchar, "gold_dublon") >= 24)
			{
				link.l1 = "I have the money. Take it.";
				link.l1.go = "monk_4";
			}
			else
			{
				link.l1 = "I will get the sum!";
				link.l1.go = "monk_wait";
			}
		break;
		
		case "monk_wait":
			DialogExit();
			sld.dialog.currentnode = "monk_repeat";
		break;
		
		case "monk_repeat":
			dialog.text = "Do you have two dozens doubloons with you my son?";
			if (GetCharacterItem(pchar, "gold_dublon") >= 24)
			{
				link.l1 = "Yes, here.";
				link.l1.go = "monk_4";
			}
			else
			{
				link.l1 = "I will get the needed amount soon enough...";
				link.l1.go = "monk_wait";
			}
		break;
		
		case "monk_4":
			RemoveItems(pchar, "gold_dublon", 24);
			Log_Info("You've give 24 doubloons");
			PlaySound("interface\important_item.wav");
			dialog.text = "Splendid. Come see me same time tomorrow - I will tell you the results.";
			link.l1 = "Very well...";
			link.l1.go = "monk_5";
		break;
		
		case "monk_5":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			AddQuestRecord("FMQ_Nevis", "18");
			pchar.quest.FMQN_monk.win_condition.l1 = "Timer";
			pchar.quest.FMQN_monk.win_condition.l1.date.hour  = 6.0;
			pchar.quest.FMQN_monk.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.FMQN_monk.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.FMQN_monk.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.FMQN_monk.function = "FMQN_EnglandMonkPlan";
			pchar.quest.FMQN_fail.win_condition.l1 = "Timer";
			pchar.quest.FMQN_fail.win_condition.l1.date.hour  = 11.0;
			pchar.quest.FMQN_fail.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.FMQN_fail.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.FMQN_fail.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.FMQN_fail.function = "FMQN_EnglandFail";
			pchar.questTemp.FMQN = "way_eng_3";
		break;
		
		case "monk_6":
			pchar.quest.FMQN_fail.over = "yes";
			dialog.text = "Greetings, my son.";
			link.l1 = "Same to you, holy father. Any news?";
			link.l1.go = "monk_6x";
		break;
		
		case "monk_6x":
			dialog.text = "Yes. It's done. The wine is 'loaded' and the right bottles will get to prison guards tonight. They have a supper by nine o'clock in the evening so they will all be sleeping by midnight. This is your only window to do the job, there will be no second chance. Be careful, you can't completely rely on your Dutch disguise.";
			link.l1 = "Got it. Let's not waste any time! Farewell.";
			link.l1.go = "monk_7";
		break;
		
		case "monk_7":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeday = 0;
			AddQuestRecord("FMQ_Nevis", "20");
			sld = CharacterFromID("FMQN_seafox_1");
			sld.dialog.currentnode = "seafox_26";
			LAi_CharacterEnableDialog(sld);
			sld.talker = 9;
			pchar.quest.FMQN_fail1.win_condition.l1 = "Timer";
			pchar.quest.FMQN_fail1.win_condition.l1.date.hour  = 20.0;
			pchar.quest.FMQN_fail1.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 0);
			pchar.quest.FMQN_fail1.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 0);
			pchar.quest.FMQN_fail1.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 0);
			pchar.quest.FMQN_fail1.function = "FMQN_EnglandFail";
			pchar.questTemp.FMQN = "way_eng_4";
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
