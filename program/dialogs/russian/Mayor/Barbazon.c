// Жак Барбазон в Ле Франсуа
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	string sLoc, sTemp;
	int i;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

//--> -----------------------------------------------блок angry-------------------------------------------------
    if (CheckAttribute(npchar, "angry") && !CheckAttribute(npchar, "angry.ok"))
    {
        npchar.angry.ok = 1;
        if (!CheckAttribute(npchar, "angry.first")) //ловушка первого срабатывания
        {
            NextDiag.TempNode = NextDiag.CurrentNode;
            Dialog.CurrentNode = "AngryExitAgain";
            npchar.angry.first = 1;
        }
        else
        {
            switch (npchar.angry.kind) //сюда расписываем реакцию ангри. В npchar.angry.name пробелы удалены!!!
            {
                case "repeat":
                    if (npchar.angry.name == "Firsttime") Dialog.CurrentNode = "AngryRepeat_1";
                    if (npchar.angry.name == "I_know_you_good") Dialog.CurrentNode = "AngryRepeat_2";
                break;
            }
        }
    }
//<-- -------------------------------------------блок angry------------------------------------------------------

	switch(Dialog.CurrentNode)
	{
	// ----------------------------------- Диалог первый - первая встреча---------------------------------------
		case "First time":
            dialog.text = NPCStringReactionRepeat("Do you have anything to tell me? No? Then get away from here!",
                         "I think that I've made myself clear, stop annoying me.", "Although I've made myself clear, but you keep annoying me!",
                         "Right, I am getting tired of this rudeness.", "repeat", 3, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("I am leaving already.",
                                               "Sure, Jaques...",
                                               "Sorry, Jaques...",
                                               "Ouch...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
			
			if (sti(pchar.GenQuest.Piratekill) > 20)
			{
				dialog.text = RandPhraseSimple("Are you insane? Wanted to play a butcher? All pirates are angry with you, pal, so you better leave this place…", "It seems, pal, that you got mad. Wanted to stretch your hands a bit? No offence, but you have nothing to do here. Get lost!");
				link.l1 = RandPhraseSimple("Listen, I want to fix the situation...", "Help me to solve the problem...");
				link.l1.go = "pirate_town";
				break;
			}
			
		//----------------------------------Сага - искушение Барбазона---------------------------------------
			if (CheckAttribute(pchar, "questTemp.Saga.BarbTemptation") && pchar.questTemp.Saga.BarbTemptation == "begin")
			{
				link.l1 = "I need to talk with you, Jaques... In private.";
				link.l1.go = "Temptation";
			}
			if (CheckAttribute(pchar, "questTemp.Saga.BarbTemptation") && pchar.questTemp.Saga.BarbTemptation == "give_silk" && GetSquadronGoods(pchar, GOOD_SHIPSILK) >= 60)
			{
				link.l1 = "I am just from Sint Maarten, Jaques...";
				link.l1.go = "Temptation_6";
			}
			if (CheckAttribute(pchar, "questTemp.Saga.BarbTemptation") && pchar.questTemp.Saga.BarbTemptation == "terrax")
			{
				link.l1 = "And when are you going to stop barking and start talking like a man, Jaques? Didn't expect to see me?";
				link.l1.go = "terrax";
			}
			
			//поручение капитана - выкуп
			if (CheckAttribute(pchar, "GenQuest.CaptainComission") && NPChar.city == pchar.GenQuest.CaptainComission.PiratesCity)
			{
				if(CheckAttribute(pchar,"GenQuest.CaptainComission.toMayor"))
				{
					link.l1 = "I am here about your prisoner.";
					link.l1.go = "CapComission1";
					DeleteAttribute(pchar,"GenQuest.CaptainComission.toMayor");
				}
             	
				if (pchar.GenQuest.CaptainComission.PirateShips == "died" || pchar.GenQuest.CaptainComission.PirateShips == "goaway") // лесник. новая проверка. искл. возможность сразу сдать задание,минуя 15 дней.
				{
					link.l1 = "Hello, Jaques, I am here because of your mission.";
					link.l1.go = "CapComission3";
				}
				if(CheckAttribute(pchar,"GenQuest.CaptainComission.RepeatSpeak") && !CheckAttribute(pchar,"GenQuest.CaptainComission.vikupzaplatil")) 
				{ // лесник . второй диалог с проверкой ,если ГГ ещё не принес деньги за выкуп.
					link.l1 = "I am here about your prisoner.";
					link.l1.go = "CapComission6";
				}
			}	
			if (CheckAttribute(pchar, "GenQuest.Marginpassenger") && pchar.GenQuest.Marginpassenger == "cabin")
			{
				link.l1 = "I've heard that you are engaged in a business related to prisoners...";
				link.l1.go = "Marginpassenger";
			}
		break;
			

 		case "Exit":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
		break;

        case "I_know_you_good":
            dialog.text = NPCStringReactionRepeat(GetFullName(pchar) + "! What do you need this time?",
                         "Have you forgotten anything to tell me? I am listening.", "And for how long will it last? If you've got nothing to do, then don't bother other people!",
                         "You've asked me to be polite. But I demand the same from you!", "repeat", 10, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("It's nothing. Just a visit.",
                                               "Nothing...",
                                               "Fine...",
                                               "You're right. I am sorry.", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			NextDiag.TempNode = "I_know_you_good";

			if (sti(pchar.GenQuest.Piratekill) > 20)
			{
				dialog.text = RandPhraseSimple("Are you insane? Wanted to play a butcher? All pirates are angry with you, pal, so you better leave this place...", "It seems, pal, that you got mad. Wanted to stretch your hands a bit? No offence, but you have nothing to do here. Get lost!");
				link.l1 = RandPhraseSimple("Listen, I want to fix the situation...", "Help me to solve the problem…");
				link.l1.go = "pirate_town";
				break;
			}

			//поручение капитана - выкуп
			if (CheckAttribute(pchar, "GenQuest.CaptainComission") && CheckAttribute(pchar,"GenQuest.CaptainComission.toMayor"))
			{
				link.l1 = "I am here about your prisoner.";
				link.l1.go = "CapComission1";
				DeleteAttribute(pchar,"GenQuest.CaptainComission.toMayor");
			}	
			if (pchar.GenQuest.CaptainComission.PirateShips == "died" || pchar.GenQuest.CaptainComission.PirateShips == "goaway")//  правка лесник,новая проверка ,исключающая тут же сдачу задания
			{
				link.l1 = "Hello, Jaques, It's about your mission.";
				link.l1.go = "CapComission3";
			}
		/*	if(CheckAttribute(pchar,"GenQuest.CaptainComission.RepeatSpeak")) //лишний диалог лесник
			{
				link.l1 = "I am here about your prisoner.";
				link.l1.go = "CapComission6";
			}*/
			if (CheckAttribute(pchar, "GenQuest.Marginpassenger") && pchar.GenQuest.Marginpassenger == "cabin")
			{
				link.l1 = "I've heard that you are engaged in a business related to prisoners...";
				link.l1.go = "Marginpassenger";
			}
		break;

//--> -----------------------------------Сага - Искушение Барбазона---------------------------------------------
		case "Temptation":
			dialog.text = "Do you know that bothering me is risky? Fine, I am listening to you.";
			link.l1 = "I have a debt. A big one. The time to pay is soon and I've got no coins. Kind people have whispered that you have a talent of making plans and you always know where to grab a big jackpot...";
			link.l1.go = "Temptation_1";
		break;
		
		case "Temptation_1":
			dialog.text = "Meh, pal! I am Jaques the Kindman only for those who are loyal to me. I am Barbazon for others and sometimes Lucifer himself. How could I know that I can trust you?";
			link.l1 = "Try me. I swear that you won't regret it!";
			link.l1.go = "Temptation_2";
		break;
		
		case "Temptation_2":
			dialog.text = "Hm... that 'kind people' must have already told you what I do to them who tries to cheat on me. But this time I will not confuse you with terrible details. I've got a small mission. If you'll succeed then all of your financial problems are gone.";
			link.l1 = "Don't doubt in me, I've been in a lot of fights and...";
			link.l1.go = "Temptation_3";
		break;
		
		case "Temptation_3":
			dialog.text = "Shut up and listen to me! A few weeks ago a Dutch patrol had caught one of my employees not far from Sint Maarten. He was delivering to me the Dutch silk. It's very rare, the Dutch bring only small batches here for the needs of the Company's navy\nSo, I managed to bite six bales of silk and Simon Morel was supposed to bring them to me on his brigantine 'Salt Dog', but he faced a Dutch patrol by accident. Or not by accident. That is what Morel's navigator said, he told me he was the only one who survived the fight\nHe also gave me Morel's log which confirms the story. According to the log, Morel had thrown away the silk during an escape attempt. It's strange, isn't it? The silk is light. They should had thrown their cannons, they didn't stand a chance against the patrol anyway.";
			link.l1 = "Something is really wrong here.";
			link.l1.go = "Temptation_4";
		break;
		
		case "Temptation_4":
			dialog.text = "All is possible. A lot of brave men works for me and much less of smart ones. No offence. You must check the location where Morel got rid of the cargo. It is 21 degrees 10' North and 61 degrees 30' West according to the captain's log\nThe Dutch reel the silk around cork rods so the bales must still stay above the water. There must be six bales. Set sail immediately, timing is critical.";
			link.l1 = "I am on my way!";
			link.l1.go = "Temptation_5";
		break;
		
		case "Temptation_5":
			DialogExit();
			SetFunctionTimerCondition("Saga_BarbTemptationOver", 0, 0, 10, false); // таймер
			pchar.quest.BarbTemptation.win_condition.l1 = "location";
			pchar.quest.BarbTemptation.win_condition.l1.location = "SentMartin";
			pchar.quest.BarbTemptation.function = "Saga_BarbTemptationBarkas";
			pchar.questTemp.Saga.BarbTemptation = "silk";
			AddQuestRecord("BarbTemptation", "2");
		break;
		
		case "Temptation_6":
			dialog.text = "Great! Have you found my silk?";
			link.l1 = "Yes, six of them as you said.";
			link.l1.go = "temptation_wrong";
			if (GetSquadronGoods(pchar, GOOD_SHIPSILK) >= 90)
			{
				link.l2 = "Yes. But there were more than you said, nine of them not six. I brought them all here, your part is to figure out how this could happen.";
				link.l2.go = "temptation_right";
			}
		break;
		
		case "temptation_wrong":
			dialog.text = "Wrong answer. There should have been nine bales. And if you found six of them then you must have found the rest. So you're either a rat or just a lazy idiot. You owe me three bales of silk and three more as a moral compensation because of your trying to cheat on me.";
			if (GetSquadronGoods(pchar, GOOD_SHIPSILK) >= 120)
			{
				link.l1 = "Such a smart ass! I'll remember that. Here is your silk and let's forget about my fault.";
				link.l1.go = "temptation_wrong_1";
			}
			link.l2 = "You've been told that there were six bales not any single more. I have given to you all that I found and I don't give a shit about your thoughts. I don't have any more silk anyway.";
			link.l2.go = "temptation_wrong_2";
		break;
		
		case "temptation_wrong_1":
			RemoveCharacterGoods(pchar, GOOD_SHIPSILK, 120);
			dialog.text = "Fine. I hope that it won't happen again because I want to give you an important task. How much money do you want to make?";
			link.l1 = "Money is always welcome, for now fifty thousand pesos would be fine.";
			link.l1.go = "junior";
		break;
		
		case "temptation_wrong_2":
			dialog.text = "Oh, that's how you're speaking now! You won't get away from this. I have warned you - don't goddamn try to cheat on me! Guards! There is a freaking rat in the residence!";
			link.l1 = "Shit!";
			link.l1.go = "temptation_wrong_fight";
		break;
		
		case "temptation_wrong_fight":
			chrDisableReloadToLocation = true;//закрыть локацию
			DialogExit();
			LAi_SetWarriorType(npchar);
			ChangeCharacterAddressGroup(npchar, "LeFransua_townhall", "goto", "goto1");
			LAi_SetImmortal(npchar, true);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			for (i = 1; i <= 3; i++)
			{
				sld = GetCharacter(NPC_GenerateCharacter("BarbGuard_"+i, "citiz_4"+(i+6), "man", "man", 80, PIRATE, 1, true, "quest"));
				FantomMakeCoolFighter(sld, 80, 100, 100, "blade_21", "pistol4", "bullet", 3000);
				ChangeCharacterAddressGroup(sld, "LeFransua_townhall", "reload", "reload1");
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
		case "temptation_right":
			RemoveCharacterGoods(pchar, GOOD_SHIPSILK, 80);
			dialog.text = "Good work. I was checking you on a greed and you have passed my test. There must have been nine bales. One of them is yours. Now we can talk seriously. How much money do you need?";
			link.l1 = "Money is always welcome, for now fifty thousand pesos would be fine.";
			link.l1.go = "junior";
		break;
		
		case "junior":
			dialog.text = "You've got an opportunity to earn even more. One serious man has asked me to find a reliable guy like you for one delicate and dangerous business. This man is very rich and he will be able to reward you deservedly if you don't let him down.";
			link.l1 = "I am ready.";
			link.l1.go = "junior_1";
		break;
		
		case "junior_1":
			dialog.text = "Fine. Listen now. You have to find his agent named 'Knave'. He is the captain of the polacre 'Marlin' and that is all I know about him. You will find him in Kapsterville. Password is 'the hunt has begun'. He will tell you what to do. You don't owe me a thing. I just want to help you. If you'll be fortuned enough then we will meet again.";
			link.l1 = "Thanks for your help. I am on my way!";
			link.l1.go = "junior_2";
		break;
		
		case "junior_2":
			DialogExit();
			AddQuestRecord("BarbTemptation", "7");
			Saga_SetJuniorInCharles(); // ставим Валета
			pchar.questTemp.Saga.BarbTemptation = "valet";
		break;
		
		case "terrax":
			dialog.text = "What?! I will tear out your...";
			link.l1 = "You won't, Barbazon. Let's see our cards! I work for Jan Swanson. I have revealed your conspiracy with Jackman. I know everything, what you were planning and what kind of role you had too. Jackman and his brother are dead, the first one killed Blaze Sharp and that determined his fate, and the second one wasn't talkative enough.";
			link.l1.go = "terrax_1";
		break;
		
		case "terrax_1":
			dialog.text = "Damn it! Tyrex won't ever forgive me for that, but I am still..";
			link.l1 = "Don't do anything stupid, Jaques. I knew that it would't be an easy conversation so I have preserved myself. Take a look to the window... your shack is rounded by my musketeers. My people are all around your village and there is a striking force group right in front of the gates. Want to start a slaughter? Easy enough!";
			link.l1.go = "terrax_2";
		break;
		
		case "terrax_2":
			dialog.text = "Damn you! What do you want?";
			link.l1 = "You won't believe me, Barbazon, but all I want is... Peace! I want the peace. That is I why I won't tell Tyrex about your part in this conspiracy against him. But only if you'll do what I want...";
			link.l1.go = "terrax_3";
		break;
		
		case "terrax_3":
			dialog.text = "What do you want from me? Money? How much?";
			if (!CheckAttribute(pchar, "questTemp.Saga.DodsonDie")) // Акула жив
			{
				link.l1 = "Oh, no, leave it to your agents with no brains. I need something different. I need your vote for Steven Dodson.";
			}
			else
			{
				link.l1 = "Oh, no, leave it to your agents with no brains. I need something different. I need your vote for Marcus Tyrax.";
			}
			link.l1.go = "terrax_4";
		break;
		
		case "terrax_4":
			if (!CheckAttribute(pchar, "questTemp.Saga.DodsonDie")) sTemp = "And Steven Dodson is on our side.";
			else sTemp = "";
			dialog.text = "Seriously? Let me think... and what if I'll say no?";
			link.l1 = "Then you will stand alone. Absolutely alone. Swanson, Tyrex and Hawk will go against you."+sTemp+"I will only show them the Knave's letter, Jackman's brother. And my word will be trusted too. And how do you think, for how long will you sit on your cozy place after that?";
			link.l1.go = "terrax_5";
		break;
		
		case "terrax_5":
			dialog.text = "Hawk? He's alive?!";
			link.l1 = "He is. I have saved him from the trap made by Jackman. So the closest friend of Jacob will be his blood enemy. And I will join them, remember that, Barbazon.";
			link.l1.go = "terrax_6";
		break;
		
		case "terrax_6":
			dialog.text = "Jackman is not my friend! Damn you! You have cornered me!";
			link.l1 = "Nonsense. Give your vote for the man I told you for and nothing will change for you. I have already told you, Jaques, I want a peace. I could make all barons hate you but I didn't.";
			link.l1.go = "terrax_7";
		break;
		
		case "terrax_7":
			GiveItem2Character(pchar, "splinter_jb"); // дать осколок
			dialog.text = "Fine. Agreed. You've got my word. Here, take my stone shard, you need it, am I right?";
			link.l1 = "Exactly. I am glad that we've had a deal, Jaques. And take this 'Knave's' letter as a sweet memento. Or better burn it, you don't want it to be found. Oh, and one last thing...";
			link.l1.go = "terrax_8";
		break;
		
		case "terrax_8":
			RemoveItems(pchar, "letter_chad", 1);
			dialog.text = "One last thing?! What else do you need from me?";
			if (CheckAttribute(pchar, "questTemp.Mtraxx.Corrida.Barbazon"))
			{
				link.l1 = "Let me remind you something. Not so long ago you sent your dog Ignacio Marco to assassinate me. It was me who killed him. It was me who buried your plan of plundering a Spanish gold galleon. It was me who sent your friends to the Spanish ambush near Sint-Maarten. My name is Charley Prince! We are done now, Jacques, and be more polite with me next time we'll see each other. Believe me, buddy, we'll meet again, and more than once I guess. Don't forget, I have every pirate baron by my side. Farewell, Barbason...";
				link.l1.go = "terrax_9";
			}
			else
			{
				if (!CheckAttribute(pchar, "questTemp.Mtraxx.Corrida.Barbazon") && CheckAttribute(pchar, "questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "full_complete_end")
				{
					link.l1 = "Let me remind you something. Not so long ago you sent your dog Ignacio Marco to assassinate me. It was me who killed him. It was me who buried your plan of plundering a Spanish gold galleon. My name is Charley Prince! We are done now, Jacques, and be more polite with me next time we'll see each other. Believe me, buddy, we'll meet again, and more than once I guess. Don't forget, I have every pirate baron by my side. Farewell, Barbason...";
					link.l1.go = "terrax_9";
				}
				else
				{
					link.l1 = "And be more polite with me next time we'll see each other. Believe me, buddy, we'll meet again, and more than once I guess. Don't forget, I have every pirate baron by my side. Farewell, Barbason...";
					link.l1.go = "terrax_9";
				}
			}
		break;
		
		case "terrax_9":
			DialogExit();
			NextDiag.CurrentNode = "I_know_you_good";
			AddQuestRecord("BarbTemptation", "26");
			if (CheckCharacterItem(pchar, "splinter_mt") && CheckCharacterItem(pchar, "splinter_jb") && CheckCharacterItem(pchar, "splinter_zm")) Saga_GiveCalendar();
			pchar.quest.Saga_storming_group1.win_condition.l1 = "location";
			pchar.quest.Saga_storming_group1.win_condition.l1.location = "LeFransua_town";
			pchar.quest.Saga_storming_group1.function = "Saga_DeleteStormingGroup";
			ChangeCharacterComplexReputation(pchar, "fame", 1);
		break;

//-----------------------------------Поручение капитана - Выкуп-------------------------------------------------
		case "CapComission1":
			dialog.text = "Ha-ha. Do you think that I've got only one prisoner here? Name him.";
			link.l1 = pchar.GenQuest.CaptainComission.SlaveName + ". Is he here?";
			link.l1.go = "CapComission2";
			DeleteAttribute(pchar,"GenQuest.CaptainComission.toMayor");
		break;

		case "CapComission2":
			if(CheckAttribute(pchar,"GenQuest.CaptainComission.DaysLeft"))
			{
				dialog.text = "He was. I have sold him away to that plantation owner from Barbados - colonel Bishop, when he was here a week ago.";
				link.l1 = "Damn...";
				link.l1.go = "CapComission2_1";
			}
			else
			{
				dialog.text = "Ah, at last. I was thinking to sell him away to that plantation owner from Barbados, he will be here in a week or two... Do you have a ransom?";
				link.l1 = "Look, there is a little problem... Actually, I don't have that much money. But I am ready to work.";
				link.l1.go = "CapComission2_2";
				if(makeint(pchar.money) > 150000)
				{
					link.l2 = "It's good that you haven't sold him. Here are your coins - 150000 pesos. Where can I get him?";
					link.l2.go = "CapComission2_3";
				}	
			}
		break;
		
		case "CapComission2_1":
			dialog.text = "You were too slow... And why do you care about him? I have been negotiating with his relatives only.";
			link.l1 = "They have asked me to come here.";
			link.l1.go = "CapComission2_11";
		break;
		
		case "CapComission2_11":
			dialog.text = "Well, you're late. I can do nothing.";
			link.l1 = "Listen, for how much have you sold him if it's not a secret?"; 
			link.l1.go = "CapComission2_12";
		break;
		
		case "CapComission2_12":
			dialog.text = "Eh, it's not. But I won't tell you... You will laugh if I tell. Ha-ha-ha-ha! Farewell.";
			link.l1 = "See you.";
			link.l1.go = "exit";
			AddQuestRecord("CaptainComission1", "10");
			AddQuestUserData("CaptainComission1", "sName", "Jacques Barbazon");//правка лесник.  в СЖ запись ниже не работает																																				  
			//AddQuestUserData("CaptainComission1", "sName", ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_NOM));
			CaptainComission_GenerateManager();
		break;
		
		case "CapComission2_2":
			if(rand(3) == 1)
			{

				dialog.text = "Well, " + pchar.name + ", you know, it doesn't work like that. Come back with money and you'll get your weakling, ha-ha.";
				link.l1 = "Fine. See you.";
				link.l1.go = "CapComission2_4";
			}
			else
			{
				dialog.text = "Well, well.. I've got one business... Don't even know how to start. I need to sink one pirate who went too far.";
				link.l1 = "Can't he simply be killed in the jungle?";
				link.l1.go = "CapComission2_2_1";
			}
		break;

		case "CapComission2_2_1":
			dialog.text = "It's not the way how business works, you know... I don't need his death, I need to teach some people to avoid taking my part of a loot. But if he goes to feed the sharks, I won't be upset.";
			link.l1 = "Why don't you send your own people for him?";
			link.l1.go = "CapComission2_2_2";
		break;
		
		case "CapComission2_2_2":
			CaptainComission_GetRandomShore();
			pchar.GenQuest.CaptainComission.ShipName1 = GenerateRandomNameToShip(sti(NPChar.nation));
			pchar.GenQuest.CaptainComission.ShipName2 = GenerateRandomNameToShip(sti(NPChar.nation));
			pchar.GenQuest.CaptainComission.UnknownPirateName = "l" + rand(GetNamesCount(NAMETYPE_ORIG) - 1);
			sLoc = XI_ConvertString(pchar.GenQuest.CaptainComission.Island + "Abl");
			dialog.text = "Hm... Well, " + GetName( NAMETYPE_ORIG, pchar.GenQuest.CaptainComission.UnknownPirateName, NAME_NOM) + " has convinced a part of pirates that their share of loot is kept in our stash not far from " + XI_ConvertString(pchar.GenQuest.CaptainComission.Island.Shore + "Gen") + ". Their two ships '" + pchar.GenQuest.CaptainComission.ShipName1 + "' and '" + pchar.GenQuest.CaptainComission.ShipName2 + "' raised anchors not long ago and sailed to " + sLoc + ". Now you see why I can't trust my men to do that job?";
			link.l1 = "I do. How much time do I have?";
			link.l1.go = "CapComission2_2_3";
		break;
		
		case "CapComission2_2_3":
			dialog.text = "12-15 days not more, it's important to me if they won't get to the stash, or it will be no sense to sink them with a valuable cargo. In that case, it would be better if they brought it here...";
			link.l1 = "Fine, I am in. I'll try to catch them.";
			link.l1.go = "CapComission2_2_4";
		break;
		
		case "CapComission2_2_4":
			AddQuestRecord("CaptainComission1", "24");
			AddQuestUserData("CaptainComission1", "sName", "Jacques Barbazon");//правка
			//AddQuestUserData("CaptainComission1", "sName", ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_NOM));// в СЖ не работает имя . лесник
			AddQuestUserData("CaptainComission1", "sShipName1", pchar.GenQuest.CaptainComission.ShipName1);
			AddQuestUserData("CaptainComission1", "sShipName2", pchar.GenQuest.CaptainComission.ShipName2);
			AddQuestUserData("CaptainComission1", "sShoreName", XI_ConvertString(pchar.GenQuest.CaptainComission.Island.Shore + "Abl"));
			AddQuestUserData("CaptainComission1", "sShoreType", XI_ConvertString(GetIslandByArealName(pchar.GenQuest.CaptainComission.Island) + "Dat"));
			pchar.quest.CapComission_PirateAttack.win_condition.l1 = "location";
            pchar.quest.CapComission_PirateAttack.win_condition.l1.location = pchar.GenQuest.CaptainComission.Island;
            pchar.quest.CapComission_PirateAttack.function = "CaptainComission_GeneratePirateShips"; 
			SetFunctionTimerCondition("CaptainComission_PirateShipsOver", 0, 0, 15, false);
			
			DialogExit();
		break;
		
		case "CapComission2_3":
			dialog.text = "Don't worry. My men will deliver him to your ship. And why do you care about him?";
			link.l1 = "I don't. His relatives asked me to deliver him.";
			link.l1.go = "CapComission2_31";
		break;
		
		case "CapComission2_31":
			dialog.text = "Ah, that's fine. I was almost sorry for giving such a low price for your man. Ha-ha-ha-ha! Farewell.";
			link.l1 = "See you.";
			link.l1.go = "CapComission2_32";
		break;
		
		case "CapComission2_32":
			AddQuestRecord("CaptainComission1", "9");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("","а"));
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City));			
			addMoneyToCharacter(pchar, -150000);
			pchar.GenQuest.CaptainComission.vikupzaplatil = true; // новая проверка ,если шарль заплатил выкуп за пленника. лесник																																								
			DialogExit();
			AddDialogExitQuestFunction("CaptainComission_GeneratePassengerSlave");	
		break;
		
		case "CapComission2_4":
			if(!CheckAttribute(pchar,"GenQuest.CaptainComission.RepeatSpeak"))
			{
				AddQuestRecord("CaptainComission1", "31");
				AddQuestUserData("CaptainComission1", "sName", "Jacques Barbazon");		// лесник																												  
				//AddQuestUserData("CaptainComission1", "sName", ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_NOM)); в СЖ не работает
			}	
			pchar.GenQuest.CaptainComission.RepeatSpeak = true;		
			DialogExit();
		break;
		
		case "CapComission3":
			dialog.text = "So, , " + GetFullName(pchar) + ", did you sink my buddy? He-he-he...";
			if(pchar.GenQuest.CaptainComission.PirateShips == "goaway")
			{
				link.l1 = "No. I failed to catch them. And I didn't meet them on return.";
				link.l1.go = "CapComission4";
			}
			if(pchar.GenQuest.CaptainComission.PirateShips == "died")	
			{
				link.l1 = "I did. I've sent them to feed the sharks.";
				link.l1.go = "CapComission5";
			}
			DeleteAttribute(pchar,"GenQuest.CaptainComission.PirateShips");
		break;
		
		case "CapComission4":
			dialog.text = "Damn! Met them or didn't, it doesn't matter now! And what will be your next suggest?";
			link.l1 = "Maybe you've got an easer job for me?";
			link.l1.go = "CapComission4_1";
			link.l2 = "Listen, "+ NPChar.name +", bring down the price for the prisoner...";
			link.l2.go = "CapComission4_2";
		break;
		
		case "CapComission4_1":
			dialog.text = "No.";
			link.l1 = "Farewell then...";
			link.l1.go = "CapComission4_3";
		break;
		
		case "CapComission4_2":
			dialog.text = "Bring down the price?! I've just lost my stash because of your slowness! And now I can rise up the price! You can take him for 200000 pesos if you want, or you can get the hell away.";
			link.l1 = "It's too expensive... Farewell...";
			link.l1.go = "CapComission4_4";
			if(sti(pchar.money) >= 200000)
			{
				link.l2 = "Damn, take your coins.";
				link.l2.go = "CapComission4_5";
			}	
		break;
		
		case "CapComission4_3":
			ChangeCharacterComplexReputation(pchar,"nobility", -2);
			AddQuestRecord("CaptainComission1", "27");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("","ла"));
			AddQuestUserData("CaptainComission1", "sName", "Barbazon"); // лесник																			  
			//AddQuestUserData("CaptainComission1", "sName", ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_DAT));// в СЖ не работает
			AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Acc"));
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			DeleteAttribute(pchar,"GenQuest.CaptainComission.PirateShips");
			DialogExit();
		break;
		
		case "CapComission4_4":
			ChangeCharacterComplexReputation(pchar,"nobility", -2);
			AddQuestRecord("CaptainComission1", "28");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("","а"));
			AddQuestUserData("CaptainComission1", "sName", "Barbazon"); // правка	// лесник																	  
			//AddQuestUserData("CaptainComission1", "sName", ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_NOM)); в сж не работает
			AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Acc"));
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			DeleteAttribute(pchar,"GenQuest.CaptainComission.PirateShips");
			DialogExit();		
		break;
		
		case "CapComission4_5":
			dialog.text = "You can take this weakling...";
			link.l1 = "Farewell.";
			link.l1.go = "CapComission4_6";
		break;
		
		case "CapComission4_6":
			addMoneyToCharacter(pchar, -200000);
			AddQuestRecord("CaptainComission1", "29");
			AddQuestUserData("CaptainComission1", "sName", "Barbazon"); // правки имени в сж лесник
			AddQuestUserData("CaptainComission1", "sName", ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_NOM));//в СЖ не работает
			AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Acc"));
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			DeleteAttribute(pchar,"GenQuest.CaptainComission.PirateShips");
			pchar.GenQuest.CaptainComission.SlaveAddMoney = true;
			DialogExit();	
			AddDialogExitQuestFunction("CaptainComission_GeneratePassengerSlave");	
		break;
		
		case "CapComission5":
			dialog.text = "Ho-ho! Well done! Take your weakling and good luck.";
			link.l1 = "Thanks. Farewell.";
			link.l1.go = "CapComission5_1";
		break;
		
		case "CapComission5_1":
			AddQuestRecord("CaptainComission1", "34");
			AddQuestUserData("CaptainComission1", "sName", pchar.GenQuest.CaptainComission.SlaveName);
			AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Acc"));
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			DeleteAttribute(pchar,"GenQuest.CaptainComission.PirateShips");
			DialogExit();		
			AddDialogExitQuestFunction("CaptainComission_GeneratePassengerSlave");	
		break;
		
	   	/*case "CapComission6":    // ЕСЛИ В ПЕРВЫЙ РАЗ ОТКАЗАЛ В ЗАДАНИИ ,ТО ПУСТЬ БАБКИ ИЩЕТ
		     ИНАЧЕ ПОВТОРНАЯ ДАЧА ЗАДАНИЯ ПРЕВРАЩАЕТ КВЕСТ В КАШУ.. лесник
			dialog.text = "Ты выкуп привёз"+ GetSexPhrase("","ла") +"? Ведь я не шутил, когда сказал, что продам его плантаторам.";			
			link.l1 = "Слушай, "+ NPChar.name +", тут такое дело... В общем, у меня нет таких денег. Но я готов"+ GetSexPhrase("","а") +" отработать.";
			link.l1.go = "CapComission2_2";
			if(makeint(pchar.money) > 150000)
			{
				link.l2 = "It's good that you haven't sold him. Here are your coins - 150000 pesos. Where can I get him?"
				link.l2.go = "CapComission2_3";
			}			
		break;*/
		  case "CapComission6":                        // лесник . пусть шарль бабло ищет,или забить на пленника.
			dialog.text = "Have you brought money? I wasn't kidding about selling that man to planters.";			
			link.l1 = "I don't have the money, "+ NPChar.name +", but I'm working on it.";
			link.l1.go = "exit";
			if(makeint(pchar.money) > 150000)
			{
				link.l2 = "It's good that you haven't sold him. Here are your coins - 150000 pesos. Where can I get him?"
				link.l2.go = "CapComission2_3";
			}			
		break;
																																					 																																													  																																															
//--------------------------------------------Похититель------------------------------------------------------
		case "Marginpassenger":
			dialog.text = "And why do you care about what I do? You know, you'd better go aw...";
			link.l1 = "Tshh, calm down. I have a business for you. It's about your prisoner.";
			link.l1.go = "Marginpassenger_1";
		break;
		
		case "Marginpassenger_1":
			dialog.text = "Ah, fine. Who do you want to ransom?";
			link.l1 = "Wait. I am not here to buy out, I am here to offer you to buy a prisoner. Well, and you will have an opportunity to get a ransom for him.";
			link.l1.go = "Marginpassenger_2";
		break;
		
		case "Marginpassenger_2":
			dialog.text = "Hm. And why do you need my agency? Why don't you want to get money directly for yourself?";
			link.l1 = "It's quite risky to me. I may have problems with authorities.";
			link.l1.go = "Marginpassenger_3";
		break;
		
		case "Marginpassenger_3":
			dialog.text = "Ha-h... fine then. Let's take a look. Who is your prisoner?";
			link.l1 = "This is "+pchar.GenQuest.Marginpassenger.Text+" "+XI_ConvertString("Colony"+pchar.GenQuest.Marginpassenger.City+"Gen")+".";
			link.l1.go = "Marginpassenger_4";
		break;
		
		case "Marginpassenger_4":
			int iTemp = makeint(sti(pchar.GenQuest.Marginpassenger.Dublon)*2*stf(pchar.GenQuest.Marginpassenger.Chance))*100;
			dialog.text = "I see and it would be a fine trade if you are not lying. I suppose that I can pay you for this man "+iTemp+" pesos or give some interesting information instead. It's your choice.";
			link.l1 = "I'd better take pesos. I had enough of this business...";
			link.l1.go = "Marginpassenger_money";
			link.l2 = "Ha! Tell me more. I am sure that you'll give me an interesting information.";
			link.l2.go = "Marginpassenger_offer";
		break;
		
		case "Marginpassenger_money":
			dialog.text = "Money then. Take them. Now, it's not your problem. Deliver the subject of sale here.";
			link.l1 = "He has to be near the town's gates already. Thanks! You have really helped me.";
			link.l1.go = "Marginpassenger_money_1";
		break;
		
		case "Marginpassenger_money_1":
			iTemp = makeint(sti(pchar.GenQuest.Marginpassenger.Dublon)*2*stf(pchar.GenQuest.Marginpassenger.Chance))*100;
			dialog.text = "You're welcome, bring me more... See you!";
			link.l1 = "Good luck...";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, iTemp);
			sld = characterFromId("MarginPass");
			RemovePassenger(Pchar, sld);
			sld.lifeday = 0;
			AddQuestRecord("Marginpassenger", "12");
			AddQuestUserData("Marginpassenger", "sSum", iTemp);
			CloseQuestHeader("Marginpassenger");
			DeleteAttribute(Pchar, "GenQuest.Marginpassenger");
		break;
		
		case "Marginpassenger_offer":
			pchar.GenQuest.Marginpassenger.Goods = GOOD_EBONY + rand(makeint(GOOD_MAHOGANY - GOOD_EBONY));
			pchar.GenQuest.Marginpassenger.GoodsQty = 200+rand(10)*10;
			switch (drand(1))
			{
				case 0: //бухта на южном мейне
					SelectSouthshore();
					while (!isLocationFreeForQuests(pchar.GenQuest.Marginpassenger.Shore)) SelectSouthshore();
					dialog.text = "It's good to do business with a smart man. Now listen: in few days to " + XI_ConvertString(pchar.GenQuest.Marginpassenger.Shore+"Dat") + " a Spanish expedition will arrive from Main, loaded with valuable woods. They will be waiting for a ship supposed to take the cargo. If you get there for a week, you will have a chance to take the cargo for yourself\nIf I were you, I would be already moving to my ship. And bring the prisoner here.";
					link.l1 = "Thanks! The wood will be a nice compensation for my troubles. And my passenger has to be near the town's gates already. He will be brought to you.";
					link.l1.go = "Marginpassenger_offer_1";
				break;
				
				case 1: //просто кораблик
					SelectSouthcity();
					pchar.GenQuest.Marginpassenger.ShipName1 = GenerateRandomNameToShip(SPAIN);
					dialog.text = "It's good to do business with a smart man. Now listen: about in a week a Spanish brigantine '"+pchar.GenQuest.Marginpassenger.ShipName1+"' loaded with valuable woods will sail from "+XI_ConvertString("Colony"+pchar.GenQuest.Marginpassenger.Southcity+"Gen")+" to "+XI_ConvertString("Colony"+pchar.GenQuest.Marginpassenger.Southcity1+"Gen")+". If you hurry, you will catch it easily\nYou are still here? If I were you, I would be already moving to my ship. And bring the prisoner here.";
					link.l1 = "Thanks! The wood will be a nice compensation for my troubles. And my passenger has to be near the town's gates already. He will be brought to you.";
					link.l1.go = "Marginpassenger_offer_2";
				break;
			}
			sld = characterFromId("MarginPass");
			RemovePassenger(Pchar, sld);
			sld.lifeday = 0;
			pchar.GenQuest.Marginpassenger = "final";
		break;
		
		case "Marginpassenger_offer_1":
			DialogExit();
			AddQuestRecord("Marginpassenger", "13");
			AddQuestUserData("Marginpassenger", "sShore", XI_ConvertString(pchar.GenQuest.Marginpassenger.Shore+"Abl"));//лесник - окончание в СЖ
			SetFunctionTimerCondition("Marginpassenger_SouthshoreOver", 0, 0, 7, false);
			pchar.quest.Marginpassenger.win_condition.l1 = "location";
			pchar.quest.Marginpassenger.win_condition.l1.location = pchar.GenQuest.Marginpassenger.Shore;
			pchar.quest.Marginpassenger.function = "Marginpassenger_Southshore";
		break;
		
		case "Marginpassenger_offer_2":
			DialogExit();
			AddQuestRecord("Marginpassenger", "16");
			AddQuestUserData("Marginpassenger", "sCity", XI_ConvertString("Colony"+pchar.GenQuest.Marginpassenger.Southcity+"Gen"));
			AddQuestUserData("Marginpassenger", "sCity1", XI_ConvertString("Colony"+pchar.GenQuest.Marginpassenger.Southcity1+"Acc")); // лесник - окончание в СЖ
			AddQuestUserData("Marginpassenger", "sShipName", pchar.GenQuest.Marginpassenger.ShipName1);
			SetFunctionTimerCondition("Marginpassenger_SouthshipInWorld", 0, 0, 5+rand(2), false);
		break;
		
//---------------------------------------попытка залезть в сундуки --------------------------------------------
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("Robbery!!! That is unacceptable! Prepare yourself, "+ GetSexPhrase("pal","girl") +"...", "Hey, what the hell are you doing there?! Thought that you could rob me? You are done... ", "Wait, what the hell? Take your hands off! Turns out that you are a thief! End of the line, bastard...");
			link.l1 = LinkRandPhrase("Shit!", "Carramba!!", "Damn it!!");
			link.l1.go = "PL_Q3_fight";
		break;
					
// ----------------------------------------------блок нод angry--------------------------------------------------
		case "AngryRepeat_1":
            dialog.text = "Get out of here!";
			link.l1 = "Oups...";
		    link.l1.go = "AngryExitAgainWithOut";
            if (CheckAttribute(npchar, "angry.terms")) //примиряемся через 10 дней.
            {
                if (GetNpcQuestPastDayParam(npchar, "angry.terms") > sti(npchar.angry.terms))
                {
         			dialog.text = "Don't bother me with your cheap talks. Next time, you won't like the result...";
        			link.l1 = "I got it.";
        			link.l1.go = NextDiag.TempNode;
        			CharacterDelAngry(npchar);
                }
            }
    	break;
		case "AngryRepeat_2":
            dialog.text = RandPhraseSimple("It's over, no talking.", "I don't want to talk to you anymore, so you'd better don't bother me.");
			link.l1 = RandPhraseSimple("As you wish...", "Hm, fine then...");
		    link.l1.go = "AngryExitAgain";
            if (CheckAttribute(npchar, "angry.terms")) //примиряемся через 10 дней.
            {
                if (GetNpcQuestPastDayParam(npchar, "angry.terms") > sti(npchar.angry.terms))
                {
         			dialog.text = "I hope that you will show more respect to me as well and will stop getting rude?";
        			link.l1 = "You can be sure, Jaques, I will.";
        			link.l1.go = NextDiag.TempNode;
        			CharacterDelAngry(npchar);
                }
            }
    	break;
		
		case "AngryExitAgain":
            DialogExit();
            DeleteAttribute(npchar, "angry.ok");
		break;
		
		case "AngryExitAgainWithOut":
            DialogExit();
            DeleteAttribute(npchar, "angry.ok");
            DoReloadCharacterToLocation("LeFransua_town","reload","reload6");
		break;
		
		case "pirate_town":
            dialog.text = "Solve the problem? Do you underdstand what you've done? Anyway, bring me a million pesos and I will persuade lads to forget your 'feats'. If don't like the idea then you may go to hell.";
			if (sti(Pchar.money) >= 1000000)
			{
				link.l1 = "Fine, I am ready to pay.";
				link.l1.go = "pirate_town_pay";
			}
			link.l2 = "Got it. I am leaving.";
			link.l2.go = "pirate_town_exit";
		break;
		
		case "pirate_town_exit":
			DialogExit();
            bDisableFastReload = true;//закрыть переход
			pchar.quest.pirate_in_town.win_condition.l1 = "ExitFromLocation";
			pchar.quest.pirate_in_town.win_condition.l1.location = pchar.location;
			pchar.quest.pirate_in_town.function = "TownPirate_battle";
		break;
		
		case "pirate_town_pay":
            dialog.text = "Good! Consider yourself clean again. But I hope that you will not do such disgusting things again.";
			link.l1 = "I won't. Way too expensive for me. Farewell...";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, -1000000);
			pchar.GenQuest.Piratekill = 0;
		break;
	}
}

void SelectSouthshore()
{
	switch (rand(6))
	{
		case 0: pchar.GenQuest.Marginpassenger.Shore = "shore37"; break;
		case 1: pchar.GenQuest.Marginpassenger.Shore = "shore47"; break;
		case 2: pchar.GenQuest.Marginpassenger.Shore = "shore48"; break;
		case 3: pchar.GenQuest.Marginpassenger.Shore = "shore25"; break;
		case 4: pchar.GenQuest.Marginpassenger.Shore = "shore21"; break;
		case 5: pchar.GenQuest.Marginpassenger.Shore = "shore20"; break;
		case 6: pchar.GenQuest.Marginpassenger.Shore = "shore19"; break;
	}
}

void SelectSouthcity()
{
	switch (drand(2))
	{
		case 0: 
			pchar.GenQuest.Marginpassenger.Southcity = "Maracaibo";
			pchar.GenQuest.Marginpassenger.Southcity1 = "Havana"; 
		break;
		
		case 1:
			pchar.GenQuest.Marginpassenger.Southcity = "Cartahena";
			pchar.GenQuest.Marginpassenger.Southcity1 = "Santiago"; 
		break;
		
		case 2:
			pchar.GenQuest.Marginpassenger.Southcity = "Portobello";
			pchar.GenQuest.Marginpassenger.Southcity1 = "Santodomingo"; 
		break;
	}
}
