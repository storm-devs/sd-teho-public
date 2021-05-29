void ProcessDialogEvent()
{
	ref sld, NPChar;
	aref Link, NextDiag;
	string sTemp;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "Bug. Let us know.";
			link.l1 = "Sure!";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
		case "FalseTrace":
			dialog.text = "Good afternoon, captain... hmm... kha! Fucking mines... Let me introduce myself. Adam Rayner. I am a simple man and do not like long forewords, so I'll spit it out right away. Do you want to make good money? I offer a small business to you, which we both will not be able to handle on our own.";
			link.l1 = "Heh! Good money? Interesting. I am listening to you, Adam.";
			link.l1.go = "FalseTrace_1";
			link.l2 = "You know, I am sorry, but you don't inspire confidence. So I won't have any business with you.";
			link.l2.go = "FalseTrace_exit";
		break;
		
		case "FalseTrace_exit":
			dialog.text = "Confidence? Ha-ha! One shouldn't judge a man by his face. Well, nevermind. You've just missed a good opportunity to make good money easily and quickly. I will find someone more cooperative...";
			link.l1 = "Our conversation is over, mister. Goodbye!";
			link.l1.go = "FalseTrace_exit_1";
		break;
		
		case "FalseTrace_exit_1":
			DialogExit();
			LAi_ActorRunToLocation(npchar, "reload", "reload4_back", "none", "", "", "", -1);
			npchar.lifeday = 0;
			DeleteAttribute(pchar, "questTemp.FalseTrace");
			chrDisableReloadToLocation = false;
			bDisableFastReload = false;
		break;
		
		case "FalseTrace_1":
			//выбираем целевой пункт
			switch (drand(2))
			{
				case 0: 
					pchar.questTemp.FalseTrace.DayQty = 18;
					pchar.questTemp.FalseTrace.TargetCity = "Beliz";
					pchar.questTemp.FalseTrace.TargetShore = "Shore8";
				break;
				case 1: 
					pchar.questTemp.FalseTrace.DayQty = 22;
					pchar.questTemp.FalseTrace.TargetCity = "Marigo";
					pchar.questTemp.FalseTrace.TargetShore = "Shore41";
				break;
				case 2: 
					pchar.questTemp.FalseTrace.DayQty = 20;
					pchar.questTemp.FalseTrace.TargetCity = "Santodomingo";
					pchar.questTemp.FalseTrace.TargetShore = "Mayak8";
				break;
			}
			pchar.questTemp.FalseTrace.ShipName = GenerateRandomNameToShip(sti(npchar.nation));
			pchar.questTemp.FalseTrace.Mation = sti(npchar.nation);
			dialog.text = "Kha! Pleasure doing business with such a quick-thinker like yourself, captain. So, the job is simple: there is a galleon filled with a decent amount of silver and she will soon set sail from one of local ports. A single vessel, no escort. Silly, right? K-kha\n Easy as pie. I tell you where and when, you take the prize and I get my cut.";
			link.l1 = "And of course, you want to receive it in cash right now?";
			link.l1.go = "FalseTrace_2";
		break;
		
		case "FalseTrace_2":
			dialog.text = "Do I look like a pathetic crook, captain? No way. I will join you in this raid and we shall do it together. I won't stay in a hold during the fight, quite the opposite - I ask you to put me in a boarding party as your officer, temporary, of course\nI know my job, I know how to stab and shoot folk. So I will risk my ass just like you... khe... kha! You will pay me my share after we capture the galleon.";
			link.l1 = "What share of the loot do you claim for yourself?";
			link.l1.go = "FalseTrace_3";
		break;
		
		case "FalseTrace_3":
			dialog.text = "I am not a greedy man, captain. My share is as much as can be loaded in the hold of my old long boat and that is about 200 measures of silver. According to my information, there will be no less than 2000 measures of silver on the galleon, so I will get the tenth part. That's fair, don't you think so?";
			link.l1 = "Tenth part of the loot just for information? I buy such information from the drunkards for a glass of rum at a local tavern. No, we are not going the same way, friend!";
			link.l1.go = "FalseTrace_4";
			link.l2 = "Hm. Guess, I agree. I accept your offer, Adam. Welcome on board. Now about your information: where from, where to, time, name of the ship?";
			link.l2.go = "FalseTrace_5";
		break;
		
		case "FalseTrace_4":
			dialog.text = "What a miser you are, captain! In that case you will get shit! See ya!";
			link.l1 = "Good luck! Find another simpleton for your shady undertaking!";
			link.l1.go = "FalseTrace_exit_1";
		break;
		
		case "FalseTrace_5":
			dialog.text = "The name of the galleon is the "+pchar.questTemp.FalseTrace.ShipName+", she departs from Cartagena and sails "+XI_ConvertString("Colony"+pchar.questTemp.FalseTrace.TargetCity)+". We don't have much time, though. Two weeks, three at most. If we don't find her in three weeks, it is over.";
			link.l1 = "Let's not waste time, then! Adventure calls!";
			link.l1.go = "FalseTrace_6";
		break;
		
		case "FalseTrace_6":
			DialogExit();
			NextDiag.CurrentNode = "FalseTrace_officer";
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "", -1);
			AddPassenger(pchar, npchar, false);
			//LAi_ActorFollowEverywhere(npchar, "", -1);
			chrDisableReloadToLocation = false;
			bDisableFastReload = false;
			AddQuestRecord("FalseTrace", "1");
			AddQuestUserData("FalseTrace", "sCity1", XI_ConvertString("Colony"+pchar.questTemp.FalseTrace.StartCity+"Gen"));
			AddQuestUserData("FalseTrace", "sCity2", XI_ConvertString("Colony"+pchar.questTemp.FalseTrace.TargetCity));
			AddQuestUserData("FalseTrace", "sShip", pchar.questTemp.FalseTrace.ShipName);
			//установим таймер на генерацию энкаунтера
			pchar.quest.False_Trace_2.win_condition.l1 = "Timer";
			pchar.quest.False_Trace_2.win_condition.l1.date.hour  = sti(GetTime());
			pchar.quest.False_Trace_2.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 2);
			pchar.quest.False_Trace_2.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 2);
			pchar.quest.False_Trace_2.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 2);
			pchar.quest.False_Trace_2.function = "CreateFalseTraceGaleonOnMap";
			SetFunctionTimerCondition("FalseTraceGaleonOver", 0, 0, sti(pchar.questTemp.FalseTrace.DayQty)+2, false);//таймер
		break;
		
		case "FalseTrace_officer":
			dialog.text = "Did you want anything, captain?";
			link.l1 = "Nothing, nevermind.";
			link.l1.go = "exit";
			NextDiag.TempNode = "FalseTrace_officer";
		break;
		
		case "FalseTrace_7":
			chrDisableReloadToLocation = true;
			dialog.text = "Did you want to see me, captain?";
			link.l1 = "I think you saw this coming... Where is the silver, damn it? Where is it? I am talking to you! The captain of the galleon told me that it was a foraging vessel! You lied to me!";
			link.l1.go = "FalseTrace_8";
		break;
		
		case "FalseTrace_8":
			dialog.text = "Calm down, captain. I will try to explain everything.";
			link.l1 = "Of course, you will! I have already calmed down! You are not hanging on a yard at the moment only because I still cannot understand your motives. You pursued this galleon with me, knowing beforehand that there was no silver. So please explain yourself.";
			link.l1.go = "FalseTrace_9";
		break;
		
		case "FalseTrace_9":
			dialog.text = "Yes, I really fooled you, captain. But that was the only way to persuade you to do what I need, to capture... khe kha! To capture this damn galleon\nBut I promise you to pay off my debt to you. Now let me tell you why I did it. Have you found a woman on the galleon? I saw crewmen taking her on your vessel...";
			link.l1 = "Hm... So, you needed the gal? And that's why you forced me to start a sea battle and kill plenty of people!?";
			link.l1.go = "FalseTrace_10";
		break;
		
		case "FalseTrace_10":
			dialog.text = "It's my wife. Katerine Rayner. She ran away from me three months ago with this pathetic captain. I made all effort to find them and I did. They both were going to "+XI_ConvertString("Colony"+pchar.questTemp.FalseTrace.TargetCity)+". I couldn't imagine a better way to return Katerine and to deal even with that wife-stealer\nIf I told you the truth, you would walk away. So I had to tell you a juicy story about a galleon filled with silver.";
			link.l1 = "Uhm... Your wife left you, didn't she? Very interesting!";
			link.l1.go = "FalseTrace_11";
		break;
		
		case "FalseTrace_11":
			dialog.text = "This is my lawful wife, I love her and nobody else has a right to be with her! That scoundrel told her beautiful lies about romance and all that crap when I was... away. Don't you know women? She believed that junk, silly girl, and ran off with him.";
			link.l1 = "Alright, I don't really care for your family life, so sort it out with your wife. But you told me about compensating my costs, didn't you? Did I hear you right?";
			link.l1.go = "FalseTrace_12";
		break;
		
		case "FalseTrace_12":
			if (pchar.basenation == SPAIN || pchar.basenation == HOLLAND)
			{
				pchar.questTemp.FalseTrace.QuestCity = "Portobello";
				pchar.questTemp.FalseTrace.QuestShore = "Shore48";
			}
			else
			{
				pchar.questTemp.FalseTrace.QuestCity = "SantaCatalina";
				pchar.questTemp.FalseTrace.QuestShore = "Shore54";
			}
			dialog.text = "Yes, you heard me right, captain. A favour for a favour. I do not have money right now, but if you bring Katerine and me to "+XI_ConvertString("Colony"+pchar.questTemp.FalseTrace.QuestCity)+", I will tell you totally reliable information where you can fetch some gold without any effort.";
			link.l1 = "Very interesting. And why can't you tell me this totally reliable information right now?";
			link.l1.go = "FalseTrace_13";
		break;
		
		case "FalseTrace_13":
			dialog.text = "Because, I don't have this information yet. Let me explain in details. One gentleman of fortune named Squint-eyed Solly - have you ever heard of him? - he is going to plunder some golden mines not far from Blueweld\nBecause of some events, he will have to leave all his gold in some hidden place and put a few guards to protect it. The man himself will go on foot to Belize or to Blueweld in order to get a ship\nI have an agent among Solly's crew, he will be waiting me in "+XI_ConvertString("Colony"+pchar.questTemp.FalseTrace.QuestCity)+". Once we drop an anchor there, he will tell me where Solly hides his goodies\nYou will go there, eliminate guards and take all gold to yourself. I was going to do it myself, but considering the current situation, I'll leave everything to you. No charge.";
			link.l1 = "Your story sounds quite like your previous fable about a galleon loaded with silver. You have already deceived me once. How can you guarantee that you are not lying this time?";
			link.l1.go = "FalseTrace_14";
		break;
		
		case "FalseTrace_14":
			dialog.text = "I give you my word. I don't have other guarantees. But it is true, I swear khe... kha...  damn mines!";
			link.l1 = "Alright. Now go, and I will think about what you've said.";
			link.l1.go = "FalseTrace_15";
		break;
		
		case "FalseTrace_15":
			dialog.text = "Don't think too long. Squint-eyed Solly will return for his treasures, as you should realize. According to my calculations, you have only two weeks to get to "+XI_ConvertString("Colony"+pchar.questTemp.FalseTrace.QuestCity+"Gen")+".";
			link.l1 = "I will keep that in mind. And now go the crew's quarters and join the sailors. I think you'd better be separated with your wife until our arrival. You can go now.";
			link.l1.go = "FalseTrace_16";
		break;
		
		case "FalseTrace_16":
			DialogExit();
			LAi_SetActorType(npchar);
			pchar.questTemp.FalseTrace = "TalkCabinWoman";
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "TalkSelf_Quest", 3.0);
			SetFunctionTimerCondition("FalseTraceSollyOver", 0, 0, 15, false);//таймер
			AddQuestRecord("FalseTrace", "5");
			AddQuestUserData("FalseTrace", "sCity", XI_ConvertString("Colony"+pchar.questTemp.FalseTrace.QuestCity));
		break;
		
		case "FalseTrace_17":
			dialog.text = "Did you call for me, captain?";
			link.l1 = "Yes. Adam Rayner, I will arrest you and lock you up. You had cheated me, and I don't have any other choice, but to isolate you and turn you to the authorities.";
			link.l1.go = "FalseTrace_18";
		break;
		
		case "FalseTrace_18":
			dialog.text = "Really? I expected you to do so, captain. Especially after you came to the hold and shared a talk with that filthy snatcher of someone else's wives. You decided that you're on his side, did you not, captain?";
			link.l1 = "None of your business. You used me, you have crossed me up, and no you're trying to deceive me again with absurd tales of treasures! Bosun, take him!";
			link.l1.go = "FalseTrace_19";
		break;
		
		case "FalseTrace_19":
			dialog.text = "Kha, not so fast, captain... The bosun and the rest of your people will not be able to come in here anytime soon. Haven't you noticed that I've locked the door? Now we are alone here - just you and me. So show me, captain, what you're made of!";
			link.l1 = "Really? You'll regret this, fucker!";
			link.l1.go = "FalseTrace_20";
		break;
		
		case "FalseTrace_20":
			DialogExit();
			NextDiag.currentnode = "FalseTrace_21";
			chrDisableReloadToLocation = true;
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			LAi_SetHP(npchar, 100+MOD_SKILL_ENEMY_RATE*35, 100+MOD_SKILL_ENEMY_RATE*35); // belamour с 40 хп боец из него никудышный
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_SetCheckMinHP(npchar, 10.0, true, "FalseTrace_capture");
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
		case "FalseTrace_21":
			dialog.text = "";
			link.l1 = "That's better... Lay down your arms, scoundrel! Bosun! Put this rascal into irons and throw him into the hold!";
			link.l1.go = "FalseTrace_22";
		break;
		
		case "FalseTrace_22":
			DialogExit();
			chrDisableReloadToLocation = false;
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], true);
			bQuestDisableMapEnter = false;
			RemovePassenger(Pchar, npchar);
			pchar.GenQuest.LastQuestPrisonerIdx = SetCharToPrisoner(npchar);
			SetCharacterRemovable(&characters[sti(pchar.GenQuest.LastQuestPrisonerIdx)], false);
			Pchar.questTemp.FalseTrace.PrisonerAdamIDX = sti(pchar.GenQuest.LastQuestPrisonerIdx);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", 3.0);
			LAi_SetPlayerType(pchar);
			RemoveCharacterEquip(npchar, BLADE_ITEM_TYPE);
			RemoveCharacterEquip(npchar, GUN_ITEM_TYPE);
			RemoveCharacterEquip(npchar, CIRASS_ITEM_TYPE);
			sld = &Characters[sti(Pchar.questTemp.FalseTrace.PrisonerIDX)];
			ReleasePrisoner(sld); //освободили пленника
			AddPassenger(pchar, sld, false);
			SetCharacterRemovable(sld, false);
			DeleteAttribute(sld, "LifeDay") //постоянный персонаж
			GiveItem2Character(sld, "blade_10");
			EquipCharacterbyItem(sld, "blade_10");
			GiveItem2Character(sld, "pistol1");
			EquipCharacterbyItem(sld, "pistol1");//патроны не даю - все одно для антуражу
			DeleteAttribute(pchar, "GenQuest.DontSetCabinOfficer");
			AddComplexSelfExpToScill(40, 40, 40, 40);
			AddQuestRecord("FalseTrace", "11");
			AddQuestUserData("FalseTrace", "sShore", XI_ConvertString(pchar.questTemp.FalseTrace.TargetShore+"Gen"));
			pchar.questTemp.FalseTrace = "AdamPrisoner";
		break;
		
		case "FalseTrace_23":
			pchar.quest.FalseTraceSollyOver.over = "yes"; //снять таймер
			dialog.text = "Thank you, captain, for helping to return my wife! Adam Rayner is in your debt, he won't forget about it, ha-ha, I swear to... kha! Damn mines! Now about Squint-eyed Solly. My man has already given me all details. Solly has left all his goodies in a grotto of San Juan del Norte bay. The man himself is in Blueweld now\nYou should hurry, you have only five days, according to my pal. Take your men with you, Solly's bandits are tough, they will give you some heat\nTime to say farewells. Thank you again, captain, Godspeed!";
			link.l1 = "Good luck to you, Adam. Don't offend your wife!";
			link.l1.go = "FalseTrace_Remove_exit";
			SetFunctionTimerCondition("FalseTraceBonanzaOver", 0, 0, 5, false);//таймер
			pchar.quest.False_Trace_4.win_condition.l1 = "location";
			pchar.quest.False_Trace_4.win_condition.l1.location = "Shore55";
			pchar.quest.False_Trace_4.function = "FalseTrace_SollyBonanza";
			ChangeCharacterComplexReputation(pchar, "nobility", -2);
			AddQuestRecord("FalseTrace", "14");
			AddQuestUserData("FalseTrace", "sCity", XI_ConvertString("Colony"+pchar.questTemp.FalseTrace.QuestCity));
		break;
		
		case "FalseTrace_24":
			pchar.quest.FalseTraceSollyOver.over = "yes"; //снять таймер
			dialog.text = "Ha! Why on earth, captain, have we gone ashore in this bay? I told you that my man was waiting for me in the port of "+XI_ConvertString("Colony"+pchar.questTemp.FalseTrace.QuestCity+"Gen")+"! Are you planning to go there on foot through jungles?";
			link.l1 = "Bad guess, Adam. Did you really think that I would believe your crap once again? Do you think I am a total fool? This time I've made a deal with your wife.";
			link.l1.go = "FalseTrace_25";
		break;
		
		case "FalseTrace_25":
			dialog.text = "What?! Kha! What kind of a deal with my wife? What are you talking about, you rotten fish?!";
			link.l1 = "Because of your false information I captured an empty galleon and killed her captain. I regret I've done that, though it is too late for regrets. Your wife was in love with that sailor, as I understood. That's why she asked me to kill you. That's why we are here in this bay now.";
			link.l1.go = "FalseTrace_26";
		break;
		
		case "FalseTrace_26":
			dialog.text = "I can't believe it! Katerine ... what a bitch! Well, you will yet get what you deserve... So, how did she promise to pay you, fool? She doesn't have a penny, she had even sold all her jewelry in order to run off with that captain!";
			link.l1 = "That's none of your business, scoundrel. But it is time to finish our conversation. I will send you to hell, where you should have been for quite some time already!";
			link.l1.go = "FalseTrace_27";
		break;
		
		case "FalseTrace_27":
			dialog.text = "Let's see what you can do, rotten herring!";
			link.l1 = "...";
			link.l1.go = "FalseTrace_28";
		break;
		
		case "FalseTrace_28":
			DialogExit();
			LAi_SetWarriorType(npchar);
			LAi_SetImmortal(npchar, false);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "FalseTrace_AdamDead");
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
		case "FalseTrace_abordage":
			dialog.text = "Ah! Why on earth have you attacked my ship, you scum? I cannot understand...";
			link.l1 = "Don't pretend to be a lamb, captain. I know what kind of cargo you're transporting. I need it.";
			link.l1.go = "FalseTrace_abordage_1";
		break;
		
		case "FalseTrace_abordage_1":
			dialog.text = "Cargo? Ha-ha! What kind of cargo you expected to see here? My holds are empty!";
			link.l1 = "What did you say, scoundrel! Come again!";
			link.l1.go = "FalseTrace_abordage_2";
		break;
		
		case "FalseTrace_abordage_2":
			dialog.text = "I repeat - I don't have any cargo on board. This galleon is a foraging vessel heading to "+XI_ConvertString("Colony"+pchar.questTemp.FalseTrace.TargetCity)+" to take a cargo of cannonballs and provision for the troops.";
			link.l1 = "You're pulling wool over my eyes. Your holds must be full of silver. And I am going to check it, after we have finished this conversation...";
			link.l1.go = "FalseTrace_abordage_3";
		break;
		
		case "FalseTrace_abordage_3":
			dialog.text = "I don't know who told you about silver. But this is absolute nonsense... I lost to you, so I am giving up. Here is my sword. Now you can go and check the holds. They are empty.";
			link.l1 = "Giving up? No! I don't need witnesses. Take your sword and fight, or I will gut you like a sheep.";
			link.l1.go = "FalseTrace_abordage_4";
			link.l2 = "Good for you that you've shown reason. I think I will be able to get a ransom for you... Hey, guys - throw the captain into the hold!";
			link.l2.go = "FalseTrace_abordage_5";
		break;
		
		case "FalseTrace_abordage_4":
			DialogExit();
			pchar.questTemp.FalseTrace.KillCaptain = "true";//атрибут квеста
			Lai_SetPlayerType(pchar);
			QuestAboardCabinDialogFree();
			LAi_group_SetRelation(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck(LAI_GROUP_BRDENEMY, "FalseTrace_AfterFight");
			AddDialogExitQuest("MainHeroFightModeOn");
			pchar.questTemp.FalseTrace.CapName = GetFullName(npchar);
			ChangeCharacterComplexReputation(pchar, "nobility", -3);
		break;
		
		case "FalseTrace_abordage_5":
			DialogExit();
			pchar.questTemp.FalseTrace.CapPrisoner = "true";//атрибут квеста
			Lai_SetPlayerType(pchar);
			DeleteAttribute(npchar, "DontRansackCaptain");
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "FalseTrace_AfterFight", 3.0);
			pchar.GenQuest.LastQuestPrisonerIdx = SetCharToPrisoner(npchar);
			SetCharacterRemovable(&characters[sti(pchar.GenQuest.LastQuestPrisonerIdx)], false);
			pchar.questTemp.FalseTrace.CapName = GetFullName(npchar);
			ChangeCharacterComplexReputation(pchar, "nobility", 2);
		break;
		
		case "FalseTrace_wife":
			dialog.text = "You killed him, you rascal! Scoundrel! Poor "+pchar.questTemp.FalseTrace.CapName+"!";
			link.l1 = "What's this? Where did you come from, dear?";
			link.l1.go = "FalseTrace_wife_1";
		break;
		
		case "FalseTrace_wife_1":
			dialog.text = "You will burn in hell for all you've done. Screw you!";
			link.l1 = "Calm down, young lady! Do not push your luck cursing me - or I will send you right after your captain!";
			link.l1.go = "FalseTrace_wife_2";
		break;
		
		case "FalseTrace_wife_2":
			dialog.text = "You ... you will not dare to raise your hand on a woman!";
			link.l1 = "I will not even need to. I can shoot you. Or I'll just throw you overboard, and sharks will do the rest... Now, what are you waiting for? Go to my ship. Don't be afraid - I will not let anybody hurt you and will not touch you myself if you are quiet...";
			link.l1.go = "FalseTrace_wife_3";
		break;
		
		case "FalseTrace_wife_3":
			DialogExit();
			pchar.quest.False_Trace_AfterBattle.over = "yes";
			pchar.quest.FalseTraceGaleonOver.over = "yes";
			if (CheckAttribute(pchar, "questTemp.FalseTrace.CapPrisoner")) AddQuestRecord("FalseTrace", "");
			else AddQuestRecord("FalseTrace", "");
			sld = characterFromId("Mugger");
			DeleteAttribute(sld, "HalfImmortal");
			RemovePassenger(Pchar, sld);
			AddPassenger(pchar, sld, false);
			SetCharacterRemovable(sld, false);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", 3.0);
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, false);
			DoQuestCheckDelay("LAi_ReloadBoarding", 4.0);
			bQuestDisableMapEnter = true;
			pchar.questTemp.FalseTrace = "TalkCabin";
			AddQuestRecord("FalseTrace", "4");
		break;
		
		case "FalseTrace_wife_4":
			dialog.text = "What... what are you going to do to him?";
			link.l1 = "What's this? Where did you come from, dear?";
			link.l1.go = "FalseTrace_wife_5";
		break;
		
		case "FalseTrace_wife_5":
			dialog.text = "Poor "+pchar.questTemp.FalseTrace.CapName+"! Tell me - are you going to kill him? Don't...";
			link.l1 = "Listen now, lady - if I wanted to kill him, I would have already done that. He will be staying in the hold, and then I will let him go or probably ransom him... the latter is more likely. And now please be a good gal and go on board of my ship. Don't be afraid - I will not let anybody hurt you and will not touch you myself if you are quiet...";
			link.l1.go = "FalseTrace_wife_3";
		break;
		
		case "FalseTrace_wife_6":
			if (CheckAttribute(pchar, "questTemp.FalseTrace.KillCaptain"))
			{
				dialog.text = "What do you want from me? Throw me to the sharks, as you said you'd do? You ruined my life and I...";
				link.l1 = "Come on, dear. Nobody is going to throw you anywhere. I just want to clarify the situation, since I attacked this galleon because of you and not for any other reason.";
				link.l1.go = "FalseTrace_wife_7";
			}
			else
			{
				dialog.text = "What do you want from me? Where is "+pchar.questTemp.FalseTrace.CapName+"? Ransom? Do you need a ransom?";
				link.l1 = "Alright, lady, let's stop this flow of pointless questions. I called you here not for this. One fact has been clarified, and it will be interesting for you to hear it.";
				link.l1.go = "FalseTrace_wife_20";
			}
		break;
		
		case "FalseTrace_wife_7":
			dialog.text = "Because of me? You are saying that it's my fault that you attacked our ship and killed my beloved one? Poor "+pchar.questTemp.FalseTrace.CapName+", what did he do to you? You will answer to the Lord for all you've done...";
			link.l1 = "The same old stew! Should we return to our shark talk?";
			link.l1.go = "FalseTrace_wife_8";
		break;
		
		case "FalseTrace_wife_8"://ноды пересечения - старт
			dialog.text = "";
			link.l1 = "Quiet now? Great. Now listen to me! I attacked the ship, because I had information that she was carrying a decent load of sliver. And I got this information from Adam Rayner.";
			link.l1.go = "FalseTrace_wife_9";
		break;
		
		case "FalseTrace_wife_9":
			dialog.text = "Ah! What?! Adam? Where is he? Is he here?";
			link.l1 = "I see you know the name... Katerine. And, as you can see, I already know everything about you. I take it, Adam Rayner is your husband, isn't he?";
			link.l1.go = "FalseTrace_wife_10";
		break;
		
		case "FalseTrace_wife_10":
			dialog.text = "Yes. I am this monster's wife. I was under the illusion that this nightmare was finally over... Did he hire you to catch me?";
			link.l1 = "Generally it turned out to be like that. Adam lied to me about sliver, so that I would capture the galleon '"+pchar.questTemp.FalseTrace.ShipName+"'. Definitely, he was determined to bring you back. A quarter an hour ago he explained to me all his actions.";
			link.l1.go = "FalseTrace_wife_11";
		break;
		
		case "FalseTrace_wife_11":
			dialog.text = "And... what does he want? What did he tell you?";
			link.l1 = "He wants his lawful wife to come back to him. He will provide me with information about Squint-eyed Solly's gold as a compensation for deceiving me. And I am going to take you both to "+XI_ConvertString("Colony"+pchar.questTemp.FalseTrace.QuestCity)+".";
			link.l1.go = "FalseTrace_wife_12";
		break;
		
		case "FalseTrace_wife_12":
			dialog.text = "No... (crying) I do not want to come back to this rascal! I made a huge effort to run away from him and cover my tracks, but he has found me anyway... Scoundrel! Bandit! Fucking thief!";
			link.l1 = "Calm down, Katerine... What language. He is your husband, after all. And he said he loved you.";
			link.l1.go = "FalseTrace_wife_13";
		break;
		
		case "FalseTrace_wife_13":
			dialog.text = "(weepingly) My husband? Do you know, who my husband is? He is an ex-prisoner, a convict and now the most cruel bandit of "+XI_ConvertString("Colony"+pchar.questTemp.FalseTrace.StartCity+"Gen")+"! He is low and filthy beast, and I am only a hole between legs to fuck for him!";
			link.l1 = "Hadn't you seen it all before you married him?";
			link.l1.go = "FalseTrace_wife_14";
		break;
		
		case "FalseTrace_wife_14":
			dialog.text = "At first, he was different... And his past seemed so romantic to me... But eventually everything has changed. And I don't even want to see him, not to mention living with him, can't you understand it? I don't want to! Especially after this attack on galleon, which he has arranged!";
			link.l1 = "Hm... What should I do with you, then, sweet lady?";
			link.l1.go = "FalseTrace_wife_15";
		break;
		
		case "FalseTrace_wife_15"://ноды пересечения - конец
			if (CheckAttribute(pchar, "questTemp.FalseTrace.KillCaptain"))
			{
				dialog.text = "What to do? I know what to do. You are tool of sin, thanks to my husband's deeds. You have killed an innocent man, the only man who treated me well. Atone for your sins, captain. Slay Adam. Right in front of my eyes. I want to see this scum dying, I want to spit on his corpse\nWhen he is dead, I will tell you where he hides his treasures. Drunk idiot told me about his stash once, ha-ha, he doesn't even remember it!";
				link.l1 = "Heh! You are a cruel woman, Katerine, as I can see!";
				link.l1.go = "FalseTrace_wife_16";
			}
			else
			{
				dialog.text = ""+pchar.questTemp.FalseTrace.CapName+"... The galleon's captain. You locked him up. Talk to him, I beg you! He will offer you something for our lives and freedom! He will come up with an idea! I... I don't want to come back to Adam, from now on "+pchar.questTemp.FalseTrace.CapName+" is my husband! I beg you - don't bring me back to Adam, to this monster!";
				link.l1 = "Hm. Interesting. And what can my prisoner possibly offer me? I can get a ransom for him from the authorities, and I will get Squint-eyed Solly's gold as well...";
				link.l1.go = "FalseTrace_wife_21";
			}
		break;
		
		case "FalseTrace_wife_16":
			dialog.text = "Look who's talking about cruelty. Sail to "+XI_ConvertString("Colony"+pchar.questTemp.FalseTrace.QuestCity)+", do what Adam told you, just land not at the port but at the nearest bay. Three of us will go there and you will kill the bastard\nOnce it's done, I will tell you about the stash. I swear, I don't lie. I believe that you have more trust in my words rather than in Adam's, he fooled you once, right? What will you say, captain?";
			link.l1 = "Yeah... They say for a reason husband and wife are indeed of the same breed. I look at you, Katerine, and I see that you are the best match for Adam... If you want him dead so much, you might just as well stab him in his drunk sleep... Bosun! Take her away!";
			link.l1.go = "FalseTrace_wife_17";
			link.l2 = "I hate rascals who try to cheat me and use me for their own purpose. Alright, Katherine, I agree to your offer, since it is clear to me that Adam cannot be trusted. But if you deceive me, too, I will find you even in Europe, I swear, and I will put a bullet through your head. Now get lost. Bosun! Take her away!";
			link.l2.go = "FalseTrace_wife_19";
		break;
		
		case "FalseTrace_wife_17":
			dialog.text = "You will regret this... I swear, I ...";
			link.l1 = "Boatswain! Guard her and keep an eye on her all the time until we arrive to "+XI_ConvertString("Colony"+pchar.questTemp.FalseTrace.QuestCity+"Gen")+"!";
			link.l1.go = "FalseTrace_wife_18";
		break;
		
		case "FalseTrace_wife_18":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", 3.0);
			AddQuestRecord("FalseTrace", "6");
			AddQuestUserData("FalseTrace", "sCity", XI_ConvertString("Colony"+pchar.questTemp.FalseTrace.QuestCity));
			AddDialogExitQuestFunction("SetCheckForSolly");
			chrDisableReloadToLocation = false;
			bQuestDisableMapEnter = false;
			DeleteAttribute(pchar, "GenQuest.DontSetCabinOfficer");
		break;
		
		case "FalseTrace_wife_19":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", 3.0);
			AddQuestRecord("FalseTrace", "7");
			AddQuestUserData("FalseTrace", "sCity", XI_ConvertString("Colony"+pchar.questTemp.FalseTrace.QuestCity));
			AddDialogExitQuestFunction("SetCheckForKillAdam");
			chrDisableReloadToLocation = false;
			bQuestDisableMapEnter = false;
			DeleteAttribute(pchar, "GenQuest.DontSetCabinOfficer");
		break;
		
		case "FalseTrace_wife_20":
			dialog.text = "What fact? What are you going to do with us? Why have you captured our ship?";
			link.l1 = "Will you let me speak a word or I should order my boatswain to shut you up with a gag?!";
			link.l1.go = "FalseTrace_wife_8";
		break;
		
		case "FalseTrace_wife_21":
			dialog.text = "Solly's gold? Do you really trust this scoundrel? He will fool you again, this is just his way! Talk to your prisoner!\n"+pchar.questTemp.FalseTrace.CapName+" is a true gentlemen, he will not break his word and he will not lie to you!";
			link.l1 = "You did not persuade me, lady. I have nothing to talk about with your captain. I will get a ransom for him and I'll get Solly's gold from Adam. If Adam deceives me again, I will find him even at the end of the world, and he will curse the day he was born... Bosun! Take her away!";
			link.l1.go = "FalseTrace_wife_23";
			link.l2 = "To tell the truth, I do not trust Adam... I hate to be manipulated. Alright, I will talk to your captain and I'll see what he can tell me. You can go now... Bosun! Take her away!";
			link.l2.go = "FalseTrace_wife_24";
		break;
		
		case "FalseTrace_wife_23":
			dialog.text = "You are a cruel and heartless man! I swear I...";
			link.l1 = "Boatswain! Guard her and keep an eye on her all the time until we arrive to "+XI_ConvertString("Colony"+pchar.questTemp.FalseTrace.QuestCity+"Gen")+"!";
			link.l1.go = "FalseTrace_wife_18";
			SetCharacterRemovable(&characters[sti(pchar.GenQuest.LastQuestPrisonerIdx)], true);
		break;
		
		case "FalseTrace_wife_24":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", 3.0);
			AddQuestRecord("FalseTrace", "8");
			chrDisableReloadToLocation = false;
			pchar.questTemp.FalseTrace.Prisoner = "true";
			SetCharacterRemovable(&characters[sti(pchar.GenQuest.LastQuestPrisonerIdx)], true);
		break;
		
		case "FalseTrace_wife_25":
			dialog.text = "It's over now... Poor "+pchar.questTemp.FalseTrace.CapName+" is avenged, and I can now breathe freely and call myself a widow...";
			link.l1 = "I have fulfilled my part of the deal, Katerine. Now it is your turn.";
			link.l1.go = "FalseTrace_wife_26";
		break;
		
		case "FalseTrace_wife_26":
			dialog.text = "Of course, captain. My husband - thanks God, now ex-husband - was a bandit, as you already know. Fearing possible searches, he did not keep pillaged loot at home. He organized a cache - but he once blabbed out about it. Still, he hid it in a very clever way - there is no access to that place from the shore.";
			link.l1 = "Very interesting... And where is it?";
			link.l1.go = "FalseTrace_wife_27";
		break;
		
		case "FalseTrace_wife_27":
			dialog.text = "On a small island near Hispaniola. In the lighthouse.";
			link.l1 = "Port-au-Prince lighthouse! It is located on the island!";
			link.l1.go = "FalseTrace_wife_28";
		break;
		
		case "FalseTrace_wife_28":
			dialog.text = "Probably so. You will be able to find a lot there. You'll see. That's all. Bye, captain.";
			link.l1 = "Wait... Forgive me, Katerine, if you can. I hope that the death of the one to blame for all your misfortunes will be a relief, anyway. I am really sorry...";
			link.l1.go = "FalseTrace_wife_29";
		break;
		
		case "FalseTrace_wife_29":
			dialog.text = "I don't need your regrets, captain. You did what I asked you to do - and I told you everything you wanted to know. Farewell now, and leave me alone with my grief...";
			link.l1 = "Bye, Katerine.";
			link.l1.go = "FalseTrace_wife_30";
		break;
		
		case "FalseTrace_wife_30":
			DialogExit();
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "", 15);
			LAi_LocationDisableOfficersGen(pchar.questTemp.FalseTrace.QuestShore, false);//офицеров пускать
			LAi_LocationDisableOfficersGen("Mayak7", true);//офицеров не пускать
			locations[FindLocation("Mayak7")].DisableEncounters = true;//энкаунтеры закрыть
			chrDisableReloadToLocation = false;
			bDisableFastReload = false;
			pchar.quest.False_Trace_7.win_condition.l1 = "location";
			pchar.quest.False_Trace_7.win_condition.l1.location = "Mayak7";
			pchar.quest.False_Trace_7.function = "FalseTrace_AdamTreasure";
			AddQuestRecord("FalseTrace", "23");
		break;
		
		case "FalseTrace_wife_31":
			dialog.text = "Filthy scoundrel! He managed to kill all four! Unbelievable!";
			link.l1 = "Didn't expect such a turn, Katerine? I am hard to kill. You play double games pretty well, I must say!";
			link.l1.go = "FalseTrace_wife_32";
		break;
		
		case "FalseTrace_wife_32":
			dialog.text = "You have murdered my man. Do you really think that I could let you keep breathing?! You thought that Adam's death satisfied me? No! You won't leave this place. There is a ship not far from this island, she will sink your old tube along with you!\nNow, do what you want with me.";
			link.l1 = "Didn't I tell you, dear, that you'd loose your head if you deceive me? A crafty devil! You will be way less dangerous dead. This pretty head is getting bullet right now...";
			link.l1.go = "FalseTrace_wife_33";
			link.l2 = "I feel pity for you, Katerine. Your craving for revenge did you nothing good in the end. I am going to leave you to your fate - you will stay on this island. I think local fishermen will find you soon and bring to Hispaniola. And may the Lord judge us for all our deeds...";
			link.l2.go = "FalseTrace_wife_35";
		break;
		
		case "FalseTrace_wife_33":
			dialog.text = "It is you who should pray, monster! Murderer! Help! Fuck y...";
			link.l1 = "I had enough.";
			link.l1.go = "FalseTrace_wife_34";
		break;
		
		case "FalseTrace_wife_34":
			DialogExit();
			LAi_SetActorType(pchar);
			LAi_SetImmortal(npchar, false);
			LAi_ActorAnimation(pchar, "shot", "FalseTrace_CaterinaKilled", 1.0);
		break;
		
		case "FalseTrace_wife_35":
			dialog.text = "May you drown! May you ship crash against the rocks! May you...";
			link.l1 = "Bye, Katerine.";
			link.l1.go = "FalseTrace_wife_36";
		break;
		
		case "FalseTrace_wife_36":
			DialogExit();
			sld = characterFromID("FalseTraceWife"); 
			sld.lifeday = 0;
			LAi_ActorGoToLocation(npchar, "goto", "goto33", "none", "", "", "", -1);
			LAi_SetPlayerType(pchar);
			chrDisableReloadToLocation = false;
			LAi_LocationDisableOfficersGen("Mayak7", false);//офицеров пускать
			locations[FindLocation("Mayak7")].DisableEncounters = false;//энкаунтеры открыть
			AddQuestRecord("FalseTrace", "25");
			ChangeCharacterComplexReputation(pchar, "nobility", 5);
			OfficersReaction("good");
		break;
		
		case "FalseTrace_Bandits":
			dialog.text = "A-ah, here is Adam's murderer! Katerine was right, this bastard came to rob the stash!";
			link.l1 = "What? Katerine? Who are you?";
			link.l1.go = "FalseTrace_Bandits_1";
		break;
		
		case "FalseTrace_Bandits_1":
			dialog.text = "Who are we? We are friends of Adam Rayner, who was murdered by you. He was the head of our brotherhood. Now I am the head, my name is "+GetFullName(npchar)+", and I will punish you for killing my boss and for violence you committed against his wife.";
			link.l1 = "Violence? What the hell are you talking about?";
			link.l1.go = "FalseTrace_Bandits_2";
		break;
		
		case "FalseTrace_Bandits_2":
			dialog.text = "You had stabbed Adam in the back, you filthy traitor, you forced his wife to tell you where Adam kept his gold and then you left poor woman to die on a desert shore\nBut she survived, she asked us to help her, to right a wrong. We have been waiting for several days for you. And here you are, bastard!";
			link.l1 = "Ha-ha! Definitely Katerine's style... Now listen, I have killed Adam, that is true, but I did that because his wife actually asked me to kill him. That was a revenge for the death of her lover. She told me where to find stash in order to repay me...";
			link.l1.go = "FalseTrace_Bandits_3";
		break;
		
		case "FalseTrace_Bandits_3":
			dialog.text = "Don't slander the poor widow, scum! Why would had she come to us then? She offered us to take all gold to ourselves in exchange for your life. She doesn't want coins, she wants your death! A holy death for the death of husband!\nBut I swear, she won't die in poverty, this is as true as my name's "+GetFullName(npchar)+", and that this is time for you to die, Judas!";
			link.l1 = "Holy crap, what a glorious speech. Oh, there she is, eager to watch this comedy personally... Gentlemen?";
			link.l1.go = "FalseTrace_Bandits_4";
		break;
		
		case "FalseTrace_Bandits_4":
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешим драться
			DialogExit();
			for (i=1; i<=4; i++)
			{
				sld = characterFromId("Adam_bandit_"+i);	
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "FalseTrace_BanditsAfterFight");
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
		case "FalseTrace_Remove1":
			dialog.text = "You are such a muddler, captain! To lose a galleon filled with silver... I made a mistake by counting on you. Farewell!";
			link.l1 = "Farewell, Adam.";
			link.l1.go = "FalseTrace_Remove2";
		break;
		
		case "FalseTrace_Remove2":
			DialogExit();
			LAi_ActorGoToLocation(npchar, "reload", "reload4_back", "none", "", "", "", 15);
		break;
		
		case "FalseTrace_Remove_exit":
			DialogExit();
			LAi_ActorGoToLocation(npchar, "reload", "reload4_back", "none", "", "", "FalseTraceWife_Remove", 15);
		break;
		
		case "FalseTrace_Remove2":
			dialog.text = "I have warned you, captain, we only had two weeks! By now Squint-eyed Solly must have already taken away all booty. It's not my fault that you are such a muddler. Farewell!";
			link.l1 = "Yeah, my fault. Farewell, I hope that we won't meet again, you're just a bad luck for me.";
			link.l1.go = "FalseTrace_Remove_exit";
		break;
		
		case "FalseTrace_Solly":
			dialog.text = "Heh! Finally! We are tired of waiting, ant these damn mosquitoes... Wait... And where is Solly? I don't get it...";
			link.l1 = "Solly won't come here. I act on his behalf... So either you will give me the gold or you're as good as dead.";
			link.l1.go = "FalseTrace_Solly_1";
		break;
		
		case "FalseTrace_Solly_1":
			dialog.text = "Argh! We will see! To me, lads! To arms!";
			link.l1 = "Now you all are all dead for sure, scavengers!";
			link.l1.go = "FalseTrace_Solly_2";
			AddDialogExitQuestFunction("FalseTrace_SollyBonanzaAdd");
		break;
		
		case "FalseTrace_Solly_2":
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешим драться
			DialogExit();
			for (i=1; i<=6; i++)
			{
				sld = characterFromId("FTEnemy_crew_"+i);	
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "FalseTrace_SollyAfterFight");
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
		case "FalseTrace_GoldShip":
			dialog.text = "You have fulfilled your part of the bargain, captain. Thanks for trusting me. Don't worry about Adam, I will deliver him to the right place. He will get what he deserves.";
			link.l1 = "I don't care about Adam. What about you promise concerning some ship?";
			link.l1.go = "FalseTrace_GoldShip_1";
		break;
		
		case "FalseTrace_GoldShip_1":
			if (sti(pchar.basenation == HOLLAND) || sti(pchar.basenation == SPAIN))
			{
				pchar.questTemp.FalseTrace.ShipNation = ENGLAND;
				pchar.questTemp.FalseTrace.ShipCity = "PortRoyal";
			}
			else
			{
				pchar.questTemp.FalseTrace.ShipNation = SPAIN;
				pchar.questTemp.FalseTrace.ShipCity = "Maracaibo";
			}
			dialog.text = "Yes, yes, sure. Let see, counting from today... Yes... In 12-14 days from "+XI_ConvertString("Colony"+pchar.questTemp.FalseTrace.ShipCity+"Gen")+"  a heavy galleon loaded with golden ore will set sail to Europe. She will be protected by a single frigate or corvette\nSo prepare yourself, it is a rich booty, but it has teeth. Though, I am sure that you will succeed, you did crush my resistance fairly easy... You must reach "+XI_ConvertString("Colony"+pchar.questTemp.FalseTrace.ShipCity+"Gen")+" in two weeks and prepare an ambush\nRemember that your target is a heavy galleon with a single convoy ship. This is it, I guess. The rest is in your hands.";
			link.l1 = "I see... Well, "+pchar.questTemp.FalseTrace.CapName+", farewell. Perhaps, I should wish you luck and happy life with Katerine? I hope that you two will be alright. It's a pity that we have met under such sad circumstances.";
			link.l1.go = "FalseTrace_GoldShip_2";
		break;
		
		case "FalseTrace_GoldShip_2":
			dialog.text = "Thank you, captain. As I've said before, you have some nobility. I hope that you will make the right conclusion that honest actions give you more profit than dishonourable ones. Devote yourself to serving your nation, and you will become a great naval sailor.";
			link.l1 = "I will think about your words. Well, farewell now!";
			link.l1.go = "FalseTrace_GoldShip_3";
		break;
		
		case "FalseTrace_GoldShip_3":
			DialogExit();
			locations[FindLocation(pchar.questTemp.FalseTrace.TargetShore)].DisableEncounters = false; //энкаутеры открыть
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "FalseTraceDouble_Remove", -1);
			pchar.quest.False_Trace_6.win_condition.l1 = "Timer";
			pchar.quest.False_Trace_6.win_condition.l1.date.hour  = sti(GetTime());
			pchar.quest.False_Trace_6.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 14);
			pchar.quest.False_Trace_6.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 14);
			pchar.quest.False_Trace_6.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 14);
			pchar.quest.False_Trace_6.function = "CreateFalseTraceGoldShipOnMap";
			AddQuestRecord("FalseTrace", "19");
			AddQuestUserData("FalseTrace", "sCity", XI_ConvertString("Colony"+pchar.questTemp.FalseTrace.ShipCity+"Gen"));
			ChangeCharacterComplexReputation(pchar, "nobility", 3);
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
