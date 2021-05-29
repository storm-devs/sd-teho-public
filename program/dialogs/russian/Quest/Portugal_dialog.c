void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i, iTemp;
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
		dialog.text = "Bug. Tell the devs.";
		link.l1 = "Sure.";
		link.l1.go = "exit";
		break;
		
		case "Avendel_tavern":
			pchar.quest.Portugal_BeginOver.over = "yes";
			dialog.text = "Oh, another brave sailor! I know your kind, my God damned eye is acquired for you, ha! Ask me why?";
			link.l1 = "I will ask you about different matter, it is about your debt which you owe to the mistress of the local... Hm, establishment. She has asked me to remind you about your debt, I suggest you doing something about it, otherwise she will have to address the guards to do the same tomorrow.";
			link.l1.go = "Avendel_tavern_1";
		break;
		
		case "Avendel_tavern_1":
			dialog.text = "Local est... oh, fuck it! Johanna, she can't do that to me! Are you sure? Has she really said that she would send me to the casemates for a few god damned coins?";
			link.l1 = "Absolutely. That is what she has said. I suppose that my mission is over, farewell, mynheer Avendell.";
			link.l1.go = "Avendel_tavern_2";
		break;
		
		case "Avendel_tavern_2":
			dialog.text = "Wait! Please, wait! You look like an experienced captain. Surely, you've got some coins, I am broken, only good old bartender fills my cup on credit for our old friendship's sake. Listen to my pro... proposal! You pay my debt and I will cut you a slice\nThere is a business... a profitable business, screw me and my ass! I swear to my bloody anchor, just trust me, captain - whatever your name is!\nJust redeem one small debt, ten thousand pesos and you'll have a chance to make enough coins to buy all brothels of the New-bloody-World! What do you say? You give me, I give you, like honest folk do...";
			link.l1 = "A ragged fellow who promises treasures. Spare me from that crap, I don't do charity for the people like you. Find the money or you will be living in the fort's casemates quite soon. Farewell!";
			link.l1.go = "Avendel_tavern_3";
			link.l2 = "A slice? And why should I trust the word of drunken idiot? Because of fantastic promises?";
			link.l2.go = "Avendel_tavern_4";
		break;
		
		case "Avendel_tavern_3":
			DialogExit();
			npchar.lifeday = 0;
			LAi_CharacterDisableDialog(npchar);
			pchar.questTemp.Portugal = "end";
		break;
		
		case "Avendel_tavern_4":
			dialog.text = "Listen to me, captain! Hic, shoot me if I am lying! I am telling the truth! Think about that, if you catch me on lying, then you will cut off my guts with that beauty you carrying on your belt! Damn, her hilt costs five times more than my miserable debt! So what? You have got nothing to loose!";
			link.l1 = "I had enough of your speech. Farewell.";
			link.l1.go = "Avendel_tavern_3";
			link.l2 = "Fine, Hugo... I will risk believing in that nonsense you speak. But remember that you will have to persuade me that my money wasn't wasted for nothing when I will be back, otherwise it's your ass on the line.";
			link.l2.go = "Avendel_tavern_5";
		break;
		
		case "Avendel_tavern_5":
			dialog.text = "No threats needed, I understand. I give you my word, captain! We will be rich! Come back when this damn debt is repaid and we'll t.. talk! Yes, we will! You won't be left aside!";
			link.l1 = "Fine, I will wipe away your debt, but you'd better pray, Hugo Avendell, that your 'proposal' will satisfy me.";
			link.l1.go = "Avendel_tavern_6";
		break;
		
		case "Avendel_tavern_6":
			DialogExit();
			pchar.questTemp.Portugal = "HostressMoney";
			Nextdiag.Currentnode = "Avendel_repeat";
		break;
		
		case "Avendel_repeat":
			dialog.text = "Captain, come back as fast as you can - I am so eager to tell you about our business.";
			link.l1 = "Yes, yes, I will repay your debt soon.";
			link.l1.go = "exit";
			Nextdiag.TempNode = "Avendel_repeat";
		break;
		
		case "Avendel_tavern_7":
			pchar.quest.Portugal_BeginOver.over = "yes";
			dialog.text = "You are back, captain! By the storm and God damn thunder, I am so glad to see you! What about my debt?";
			link.l1 = "I've dealt with it, now it is your turn, Hugo. Tell me your story and try to make it just a bit truthful!";
			link.l1.go = "Avendel_tavern_8";
		break;
		
		case "Avendel_tavern_8":
			dialog.text = "Don't worry, captain! Do you know that I am a bounty hunter? Or I used to be. I wasn't lucky enough. Perhaps, the Devil himself with all of his deeds wasn't that looser as I was. I have lost everything on my last job... The crew ran away and I had to sell my ship because of debts...";
			link.l1 = "I am already informed about your heroic past. Straight to the business, Hugo, don't challenge my patience.";
			link.l1.go = "Avendel_tavern_9";
		break;
		
		case "Avendel_tavern_9":
			dialog.text = "Yes, yes, captain..."+GetFullName(pchar)+", am I right? I know something about you too. But damn me if it is important. Have you heard the name of Bartolomeo the Portuguese?";
			link.l1 = "Bart the Portuguese? Of course I have heard of him. Everyone has. He is a pirate, a butcher and a scum as far as I am informed. And what is his part in your story?";
			link.l1.go = "Avendel_tavern_10";
		break;
		
		case "Avendel_tavern_10":
			dialog.text = "He is taking a God damn main part in it! I have been tracking him down for the last year and a half. The Dutch Company has put a great price for his head. But I have failed and lost everything. And the Company has tripled the price recently for him alive and alive only damn him!";
			link.l1 = "For a good reason, it is not a piece of cake to capture him alive. Anyway, why should I care about that, Hugo? It looks like you are trying to screw me!";
			link.l1.go = "Avendel_tavern_11";
		break;
		
		case "Avendel_tavern_11":
			dialog.text = "I wasn't even going to, captain! You know, the local doctor Peter Van Stal, a very nice man, has given me one potion to cure my headaches! So, the doctor wasn't in his house for almost three days and...";
			link.l1 = "Hugo, my patience is almost gone! I have promised the dame that I won't stab you with my blade, but my fists will do just fine! I swear that no potion will be able to cure your head tomorrow!";
			link.l1.go = "Avendel_tavern_12";
		break;
		
		case "Avendel_tavern_12":
			dialog.text = "Wait, captain! Listen to me, I have seen a few guys near the doctor's home and I have recognized them. They are from the 'Albatross', a frigate of the damn Portuguese! And one of them was talking about their captain's health! See now, " + pchar.name + ", Bartolomeo is here, in this city! Right under our noses, he is either wounded or ill, that is why they need a blasted physician!\nI doubt that the Portuguese has brought his whole crew here, but I won't start this mess alone! Surely, you damn know how to handle your cursed sword! Take a few tough guys with you and we will find the rat! Then we capture him and deliver him to the authorities!\nAnd two thousand good gold doubloons are in our pockets!";
			link.l1 = "No, Hugo, I had enough of your talk. I won't take part in this mess, even if you are right. Farewell.";
			link.l1.go = "Avendel_tavern_3";
			link.l2 = "And that's interesting. Do you know where is he hiding? If it works out we will discuss shares, but we have to hurry now!";
			link.l2.go = "Avendel_tavern_13";
		break;
		
		case "Avendel_tavern_13":
			dialog.text = "No, captain, I was too scared to track down these lads. If the One-eyed would have seen me...fuh! But together, plus your lads, we will be able to comb this town, call you men and let's get started! Damn, the Dutch doubloons are waiting for us! Such a God damn chance happens only once in a lifetime, bite me a herring!";
			link.l1 = "A commendable enthusiasm... I hope that you are able to get out from the table, a 'great' thug. I am going to search immediately and you can follow me if you want, just don't bother me too much.";
			link.l1.go = "Avendel_tavern_14";
		break;
		
		case "Avendel_tavern_14":
			DialogExit();
			SetFunctionTimerCondition("Portugal_DoctorOver", 0, 0, 2, false);
			pchar.quest.Portugal_Guard.win_condition.l1 = "location";
			pchar.quest.Portugal_Guard.win_condition.l1.location = "Marigo_houseF1";
			pchar.quest.Portugal_Guard.function = "CreatePortugalGuard";
			AddQuestRecord("Portugal", "1");
			NextDiag.Currentnode = "Avendel_tavern_repeat";
		break;
		
		case "Avendel_tavern_repeat":
			dialog.text = "Yes, yes, captain, just let me finish my treat and I will join you... Where shall we start?";
			link.l1 = "Whatever, just sit here... helper.";
			link.l1.go = "exit";
			Nextdiag.TempNode = "Avendel_tavern_repeat";
		break;
		
		case "Portugal_guard":
			dialog.text = "Wrong house, pal. Now get out of here!";
			link.l1 = "Hm. And I think that it's the right house...";
			link.l1.go = "Portugal_guard_1";
		break;
		
		case "Portugal_guard_1":
			dialog.text = "Well, If you say so...";
			link.l1 = "Yup.";
			link.l1.go = "Portugal_guard_2";
		break;
		
		case "Portugal_guard_2":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешить драться
			for (i=1; i<=3; i++)
			{
			sld = characterFromId("PortugalGuard_"+i);
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "OpenTheDoors");
			AddDialogExitQuest("MainHeroFightModeOn");
			pchar.quest.Portugal_Doctor.win_condition.l1 = "location";
			pchar.quest.Portugal_Doctor.win_condition.l1.location = "Marigo_RoomHouseF1";
			pchar.quest.Portugal_Doctor.function = "CreatePortugalDoctor";
		break;
		
		case "Bart_lay":
			dialog.text = "Full and by, sons of... prepare cannons on the...ah-ha-ha, my beauty!";
			link.l1 = "Understood.";
			link.l1.go = "exit";
			Nextdiag.TempNode = "Bart_lay";
		break;
		
		case "Portugal_doctor":
			pchar.quest.Portugal_DoctorOver.over = "yes";
			dialog.text = "Oh God, who are you? Please put down your weapon! There is an ill man here!";
			link.l1 = "This 'ill man' of yours has killed more people than you've seen in your life, doctor. Get away!";
			link.l1.go = "Portugal_doctor_1";
		break;
		
		case "Portugal_doctor_1":
			dialog.text = "He is my patient and he is even unable to stand! Don't you see that? Please, put your blade down!";
			link.l1 = "And what is wrong with him, damn it?";
			link.l1.go = "Portugal_doctor_2";
		break;
		
		case "Portugal_doctor_2":
			dialog.text = "I suppose it is all because of his wound, a blow dealt by a poisoned Carib's weapon... and the men who have brought him here said that if he dies I'll die! But I am doing all I can, tell them that!";
			link.l1 = "Don't worry about those men, doctor. My lads will keep an eye on your house and I have to go to see the governor. I suppose that he will piss himself of joy. Don't leave this place until I return, doc.";
			link.l1.go = "Portugal_doctor_3";
		break;
		
		case "Portugal_doctor_3":
			chrDisableReloadToLocation = false;
			DialogExit();
			LAi_SetStayType(npchar);
			Nextdiag.Currentnode = "Doctor_repeat";
			pchar.quest.Avendel_House.win_condition.l1 = "location";
			pchar.quest.Avendel_House.win_condition.l1.location = "Marigo_houseF1";
			pchar.quest.Avendel_House.function = "AvendelInHouse";
		break;
		
		case "Doctor_repeat":
			dialog.text = "I won't leave, don't worry about that. Let's just give him to the authorities already and end this nightmare.";
			link.l1 = "Of course, I am on my way.";
			link.l1.go = "exit";
			Nextdiag.TempNode = "Doctor_repeat";
		break;
		
		case "Avendel_house":
			dialog.text = "We did it, captain! We have found him and we will be rich, just as I told you! What is our plan?";
			link.l1 = "I hope so, Hugo. Anyway, it is not over yet. I suppose I have to go to the governor and discuss our reward.";
			link.l1.go = "Avendel_house_1";
		break;
		
		case "Avendel_house_1":
			dialog.text = "No-no, captain, don't go to this damned Thomas! Trust me, this scoundrel will take away our prisoner and luckily will treat us with a cup of coffee! His Excellency is a fishy type, so if you want to get a full reward you have to sail to Curacao! Otherwise the Portuguese will be taken from us to the fort and they will drive us away like beggars!";
			link.l1 = "Well, if you are really sure of that...";
			link.l1.go = "Avendel_house_2";
		break;
		
		case "Avendel_house_2":
			dialog.text = "I am, captain, damn sure I am! But remember that Bartolomeo's men must be somewhere in the town and we don't want to attract garrison's attention either, that is for damn sure! We have to decide how to get the Portuguese to your ship and how to do it in unnoticeable way.";
			link.l1 = "Fine... I don't want to fight his frigate on the way to Willemstad. Got any ideas?";
			link.l1.go = "Avendel_house_3";
		break;
		
		case "Avendel_house_3":
			dialog.text = "Yes, I have got one. We need to find a more noble suit for him first, then we drag him through the rear entrance as a drunken officer! No one will suspect this damn pirate, trust me!";
			link.l1 = "I am not sure, but we don't have a better plan yet anyway. I will try to get some pretty cloth for our passenger. You stay here and watch over Bart and doc.";
			link.l1.go = "Avendel_house_4";
		break;
		
		case "Avendel_house_4":
			DialogExit();
			AddQuestRecord("Portugal", "3");
			LAi_ActorRunToLocation(npchar, "reload", "houseF1", "Marigo_houseF1", "goto", "goto2", "", -1);
			pchar.quest.Portugal_Cloves.win_condition.l1 = "Timer";
			pchar.quest.Portugal_Cloves.win_condition.l1.date.hour  = sti(GetTime());
			pchar.quest.Portugal_Cloves.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.Portugal_Cloves.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.Portugal_Cloves.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.Portugal_Cloves.function = "PortugalClovesOver";//1 сутки
			pchar.questTemp.Portugal = "Findcloves";
			LAi_SetStayType(npchar);
			npchar.dialog.currentnode = "Avendel_house_guard";
		break;
		
		case "Avendel_house_guard":
			dialog.text = "Don't worry , captain. The Portuguese is under my reliable guard, he-he...";
			link.l1 = "I want to believe...";
			link.l1.go = "exit";
			Nextdiag.TempNode = "Avendel_house_guard";
		break;
		
		case "Portugal_doctor_4":
			dialog.text = "I don't see soldiers, mynheer. Where are they? You said that he would be arrested as soon as you told about the situation to the authorities. So why there are no soldiers here?";
			link.l1 = "There won't be any soldiers, mynheer Van Stal. I am going to do the job myself and I have to take your patient to Curacao as soon as possible.";
			link.l1.go = "Portugal_doctor_5";
		break;
		
		case "Portugal_doctor_5":
			dialog.text = "Captain, listen, I can't handle his wound, all I can do is just to lower a fever a bit. He is mostly unconscious and delirious, there is no doubt that he will die even without any interference and the sea rolling will kill him in a few days. I will give you some mixture to help...";
			link.l1 = "No, doc, you are sailing with us. First, I suck at medicine and second, I doubt that you want to stay here and explain the Portuguese's men where has their captain gone?";
			link.l1.go = "Portugal_doctor_6";
		break;
		
		case "Portugal_doctor_6":
			dialog.text = "Yes, you are right, I suppose. But be aware that this pirate is very resilient, I have seen people with only small scratches made by Indian weapons and all of them died in less than three days. And according to his friends, he has been in this state for a week already! Nevertheless, I affirm that he will survive for a short period of time on a ship in the open sea. Three days, not longer!\nThat's all the time we have.";
			link.l1 = "Even the bird won't reach Curacao in three days. But I think I know what to do! There is my... friend in St. John's at Antigua and he knows how to heal people. He is the only person who can help us. Our goal is simple - to get there before the Portuguese dies. Pack up your things, doc, we will sail immediately and your patient will be transferred next!";
			link.l1.go = "Portugal_doctor_7";
		break;
		
		case "Portugal_doctor_7":
			DialogExit();
			AddQuestRecord("Portugal", "5");
			pchar.quest.Portugal_Cloves.over = "yes";
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", -1);
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, false);
			sld = characterFromId("Avendel");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload1", "none", "", "", "", -1);
			AddPassenger(pchar, sld, false);
			SetCharacterRemovable(sld, false);
			RemoveItems(PChar, "suit_1", 1);
			sld = characterFromId("Portugal");
			sld.model = "Port_B"; //меняем модель
			ChangeCharacterAddressGroup(sld, "My_Deck", "goto", "goto6");
			SetFunctionTimerCondition("Portugal_ToAntiguaOver", 0, 0, 4, false);
			pchar.questTemp.Portugal = "ToAntigua";
			//временно для тестов откроем комнату Джино, потом убрать
			LocatorReloadEnterDisable("SentJons_HouseF3", "reload4", false);
		break;
		
		case "Avendel_goodbye":
			dialog.text = "What a pity, captain. But we have lost and we won't see that damn gold. Farewell.";
			link.l1 = "Farewell, Hugo.";
			link.l1.go = "Avendel_goodbye_1";
		break;
		
		case "Avendel_goodbye_1":
			DialogExit();
			chrDisableReloadToLocation = false;//открыть локацию
			npchar.lifeday = 0;
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", -1);
		break;
		
		case "Portugal_doctor_9":
			dialog.text = "...";
			link.l1 = "Doc, prepare your patient for landing. The ship's longboat is ready. Hurry up!";
			link.l1.go = "Portugal_doctor_10";
		break;
		
		case "Portugal_doctor_10":
			dialog.text = "I am on my way, mynheer.";
			link.l1 = "...";
			link.l1.go = "Portugal_doctor_11";
		break;
		
		case "Portugal_doctor_11":
			DialogExit();
			AddQuestRecord("Portugal", "7");
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", -1);
			sld = characterFromId("Portugal");
			ChangeCharacterAddressGroup(sld, "SentJons_HouseF3_Room2", "quest", "quest1");
			sld = characterFromId("Jino");
			ChangeCharacterAddressGroup(sld, "SentJons_HouseF3_Room2", "goto", "goto3");
			pchar.quest.Portugal_ToAntiguaOver.over = "yes";//снять таймер
			pchar.questTemp.Portugal = "TreatmentStart";
			pchar.quest.Portugal_Ill.win_condition.l1 = "Timer";
			pchar.quest.Portugal_Ill.win_condition.l1.date.hour  = sti(GetTime());
			pchar.quest.Portugal_Ill.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 4);
			pchar.quest.Portugal_Ill.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 4);
			pchar.quest.Portugal_Ill.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 4);
			pchar.quest.Portugal_Ill.function = "Portugal_ToAntiguaOver";//не придет через 4 дня - Португальцу капут
		break;
		
		case "Avendel_Room":
			dialog.text = "This house is stinking with fucking mixtures! It would be a big surprise if the Portuguese will die here, even breathing this smell can heal any disease!\nAnd the man's crew can find us easily thanks to the stench!";
			link.l1 = "Hugo, spare me from you jokes. I have left a few men on the streets to watch over the house, but a one more guard won't be unnecessary to our guest. Keep an eye on him and try to stop swearing like that or Gino will make you drink some mixture of his, I am sure that he can cure that.";
			link.l1.go = "Avendel_Room_1";
		break;
		
		case "Avendel_Room_1":
			dialog.text = "Don't worry, captain! I will watch over our money in the most vigilant way, he won't run away even in case he was healthy! And I beg you, please, no more mixtures!";
			link.l1 = "See, you can when you want. Be on the alert, I have to go.";
			link.l1.go = "exit";
			chrDisableReloadToLocation = false;
		break;
		
		case "Avendel_Room_2":
			dialog.text = "Leaving already, captain? Nice! It is time! There were a few f... suspicious lads on a street. They don't look like the Portuguese men, though they were searching for something, we have to be careful, captain!";
			link.l1 = "Fine, thanks for your warning, Hugo. Let's go to the ship.";
			link.l1.go = "Avendel_Room_3";
		break;
		
		case "Avendel_Room_3":
			DialogExit();
			chrDisableReloadToLocation = false;
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", -1);
			//ставим Португальца
			sld = characterFromId("Portugal");
			ChangeCharacterAddressGroup(sld, "SentJons_HouseF3", "goto", "goto1");
			LAi_SetActorType(sld);
			LAi_ActorFollowEverywhere(sld, "", -1);
		break;
		
		case "Portugal_hunter":
			dialog.text = "Captain, we have been waiting for this meeting far too long! And who is that with you? Bartolomeo the Portuguese himself, ha, the Bold Pierre was right - that was him! Stay away, captain, we are going to take him with us and no one will get hurt.";
			link.l1 = "Who the hell are you?! Get away from here or someone will get hurt right now!";
			link.l1.go = "Portugal_hunter_1";
		break;
		
		case "Portugal_hunter_1":
			dialog.text = "Oh, such a menacing fellow, just look at him, lads! Listen to me, pup, don't stay between Leo Cord and his money! We have been tracking down the Portuguese for almost a half of year and now we have finally got him. So put down that toothpick of yours and get lost while you are still breathing! We are not that greedy, dead man will do just fine, ha-ha!";
			link.l1 = "Enough. Let's dance, gentlemen!";
			link.l1.go = "Portugal_hunter_2";
		break;
		
		case "Portugal_hunter_2":
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешим драться
		DialogExit();
		sld = characterFromId("Portugal");
		LAi_group_Register("Bart_Portugal");
		LAi_group_SetRelation("Bart_Portugal", LAI_GROUP_PLAYER, LAI_GROUP_FRIEND);
		LAi_group_MoveCharacter(sld, "Bart_Portugal");
		for (i=1; i<=5; i++)
		{
		sld = characterFromId("PortugalHunter_"+i);
		LAi_SetWarriorType(sld);
		LAi_group_MoveCharacter(sld, "EnemyFight");
		}
		LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
		LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
		LAi_group_SetCheck("EnemyFight", "PortugalHunterDied");
		AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "Avendel_street":
			sld = characterFromId("Portugal");
			if (LAi_GetCharacterHP(sld) > 0)
			{
				dialog.text = "I knew that something was wrong here! Well done, captain! But it is time to go, that damn Leo Cord has a lot of bandits around here and a fine ship! We have to get away from this island!";
				link.l1 = "You have a point, Hugo, and I am very glad that no bullet was shot at the hole where you were hiding.";
				link.l1.go = "Avendel_street_1";
			}
			else
			{
				dialog.text = "What a pity, captain. But we have lost and we won't see that damn gold. Farewell.";
				link.l1 = "Farewell, Hugo.";
				link.l1.go = "Avendel_goodbye_1";
				sld = characterFromId("PortugalDoctor");
				RemovePassenger(Pchar, sld);
				sld.lifeday = 0;
				RemovePassenger(Pchar, npchar);
				AddQuestRecord("Portugal", "35");
				CloseQuestHeader("Portugal");
				pchar.questTemp.Portugal = "end";
			}
		break;
		
		case "Avendel_street_1":
			dialog.text = "I... I was securing our rear, captain! You were doing fine, but what if someone would have attacked us from other side of the street?";
			link.l1 = "Perhaps that is why you did not succeed in your line of work? Whatever, enough talking, we have to get to the ship! Time is running out!";
			link.l1.go = "Avendel_street_2";
		break;
		
		case "Avendel_street_2":
			DialogExit();
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "", 10);
			AddQuestRecord("Portugal", "8");
			pchar.quest.Portugal_seahunter.win_condition.l1 = "location";
			pchar.quest.Portugal_seahunter.win_condition.l1.location = "Antigua";
			pchar.quest.Portugal_seahunter.function = "PortugalSeaHunter";
			pchar.quest.Portugal_martinique.win_condition.l1 = "location";
			pchar.quest.Portugal_martinique.win_condition.l1.location = "FortFrance_town";
			pchar.quest.Portugal_martinique.function = "PortugalOnMartinique";
		break;
		
		case "Portugal_doctor_12":
			dialog.text = "Captain, the Portuguese is feeling really bad, we need to stop!";
			link.l1 = "That is why we are here, mynheer van Stal, our trip is almost over. I will rent a room in the tavern and our prisoner will stay there for a few days.";
			link.l1.go = "Portugal_doctor_13";
		break;
		
		case "Portugal_doctor_13":
			DialogExit();
			LAi_ActorRunToLocation(npchar, "reload", "reload4_back", "none", "", "", "", 5);
		break;
		
		case "Portugal_doctor_14":
			dialog.text = "Mynheer captain, I will be looking after the Portuguese, he needs a full rest.";
			link.l1 = "I got it, doc, it is alright. Damn it, for how long should I take care of this pirate? That is bad for him, that is not what he needs! It seems that I was hired as a babysitter and... hm, pardon me, doctor, it was just too much.... Good day to you.";
			link.l1.go = "Portugal_doctor_15";
		break;
		
		case "Portugal_doctor_15":
			DialogExit();
			AddQuestRecord("Portugal", "15");
			pchar.quest.Portugal_patrol.win_condition.l1 = "location";
			pchar.quest.Portugal_patrol.win_condition.l1.location = "FortFrance_town";
			pchar.quest.Portugal_patrol.function = "CreateFrancePatrol";
		break;
		
		case "Portugal_patrol":
			dialog.text = "Monsieur, are you captain "+GetFullName(pchar)+", whose ship has arrived in our harbour today?";
			link.l1 = "You are correct, how can I help you?";
			link.l1.go = "Portugal_patrol_1";
		break;
		
		case "Portugal_patrol_1":
			dialog.text = "His Excellency Jacque Dille do Parque, the governor of our colony is waiting for you. The matter is urgent!";
			link.l1 = "Fine, monsieur, I will visit his Excellency today.";
			link.l1.go = "Portugal_patrol_2";
		break;
		
		case "Portugal_patrol_2":
			DialogExit();
			chrDisableReloadToLocation = false;//открыть локацию
			pchar.questTemp.Portugal = "MartiniqueGovernor";
			LAi_ActorGoToLocation(npchar, "reload", "reload4_back", "none", "", "", "", -1);
			AddQuestRecord("Portugal", "9");
		break;
		
		case "Avendel_seapatrol":
			dialog.text = "We have reached Martinique, captain! Our money is not that far now...";
			link.l1 = "Only if the Portuguese will live until we reach Willemstad. Hugo, I have to go to the ship, so you will have to watch over doc and his patient.";
			link.l1.go = "Avendel_seapatrol_1";
		break;
		
		case "Avendel_seapatrol_1":
			dialog.text = "To go to the ship? Why? Will you lend a few men for me to help?";
			link.l1 = "I am sorry, but no. I doubt that anything can threaten you here. The garrison is alerted and there are more soldiers on the streets than usually. They have seen a big ship not far from this island, a pirate one, perhaps. And his Excellency the governor has asked me to fortify patrolling by my ship.";
			link.l1.go = "Avendel_seapatrol_2";
		break;
		
		case "Avendel_seapatrol_2":
			dialog.text = "A ship? Pirate one? It can be the Albatross! Or some colleague of our old friend Leo Cord!";
			link.l1 = "Or perhaps it is just an ordinary pirate ship. Nevertheless, Hugo, if this vessel is here for our heads then I'd better face her with the local patrol ships on my side and for the governor's gold. It is much better than watching over our rear for the rest of the trip. If this alarm is false, then it will simply spare me from sitting my ass in the tavern for a few days.";
			link.l1.go = "Avendel_seapatrol_3";
		break;
		
		case "Avendel_seapatrol_3":
			dialog.text = "Think about it, captain, is it wise to leave the dam... the Portuguese unprotected while there might be his frigate cruising around? You are risking our reward by accepting the governor's fee!";
			link.l1 = "Enough talking, Hugo Avendell! I am the captain here and the final decision is mine! So do as I command you. Go to the tavern and keep an eye on the doctor and the Portuguese until I'll be back.";
			link.l1.go = "Avendel_seapatrol_4";
		break;
		
		case "Avendel_seapatrol_4":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload4_back", "none", "", "", "", 10.0);
			chrDisableReloadToLocation = false;//открыть локацию
			LocatorReloadEnterDisable("Fortfrance_town", "reload4_back", true);//закрыть таверну
		break;
		
		case "Avendel_seapatrol_5":
			dialog.text = "You are back, captain, at last! Iэve got bad news for you - the Portuguese is gone and so is doc!";
			link.l1 = "How?! And what were you doing then, blockhead?!";
			link.l1.go = "Avendel_seapatrol_6";
		break;
		
		case "Avendel_seapatrol_6":
			dialog.text = "I can bet that ship was the 'Albatross'. I have seen the Portuguese men, they entered the tavern and I... I ran away. I am sorry, but meeting the One-eyed Dog was too much even for that much money!";
			link.l1 = "Fuck! Tell me at least what happened in the tavern?";
			link.l1.go = "Avendel_seapatrol_7";
		break;
		
		case "Avendel_seapatrol_7":
			dialog.text = "I told you that I saw nothing. I ran away through a kitchen as soon as I saw Franz Garcke and his men... Too close! It happened yesterday evening and I didn't know how to let you know...";
			link.l1 = "Yes, you are a very brave and resourceful man... Fine, let's give you one more chance, we are going to find them. I have been saving this scoundrel for too long and now I consider him as my property. We still have some time to catch them, so let's start from the tavern, perhaps, someone have seen more than your running heels. Go, prepare yourself!";
			link.l1.go = "Avendel_seapatrol_8";
		break;
		
		case "Avendel_seapatrol_8":
			DialogExit();
			bQuestDisableMapEnter = false;//открыть карту
			DeleteAttribute(pchar, "GenQuest.CannotWait");//можно мотать время
			chrDisableReloadToLocation = false;
			LAi_ActorFollowEverywhere(npchar, "", -1);
			SetFunctionTimerCondition("MartiniquePortugalOver", 0, 0, 2, false); //таймер
			sld = characterFromId("PortugalDoctor");
			sld.lifeday = 0;//убираем доктора
			RemovePassenger(Pchar, sld);	
			sld = characterFromId("Portugal");
			ChangeCharacterAddressGroup(sld, "none", "", "");//Португальца спрячем
			LocatorReloadEnterDisable("Fortfrance_tavern", "reload2_back", true);//комнату закроем
			AddQuestRecord("Portugal", "12");
		break;
		
		case "Avendel_seapatrol_9":
			dialog.text = "Have you heard him, captain, he was talking about the One-eyed Dog, I have told you about him recently. And the lisping Castilian is Hernando Vasquez, the bloody Don - the butcher of Vera Cruz, I didn't see him!";
			link.l1 = "Relax, Hugo. I am sure that Bartholomeo is still on the island, he might have got better, but he is still too weak. And I think I know where to find him! We will get them, I won't step away from my reward. If you are no coward then follow me, it is not over yet.";
			link.l1.go = "Avendel_seapatrol_10";
		break;
		
		case "Avendel_seapatrol_10":
			DialogExit();
			bDisableFastReload = false;//открыть быстрый переход
			pchar.questTemp.Portugal = "PortugalLeFransua";//в Ле Франсуа
			AddQuestRecord("Portugal", "13");
			LAi_LocationDisableOfficersGen("LeFransua_tavern", true);//офицеров не пускать
		break;
		
		case "LeFransua_pirate":
			dialog.text = "You ask too many questions, captain... Wait, aren't you that sneaky guy from Philipsburg? You have been running from us for too long and now look - here you are...";
			link.l1 = "Too bad for you, scum!";
			link.l1.go = "LeFransua_pirate_1";
		break;
		
		case "LeFransua_pirate_1":
			DialogExit();
			pchar.quest.MartiniquePortugalOver.over = "yes"; //снять таймер
			chrDisableReloadToLocation = true;
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			for (i=1; i<=3; i++)
			{
			sld = characterFromId("LeFransuaPirate_"+i);
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "LeFransuaAfterFight");
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "FranzGarke":
			dialog.text = "... you, a crab's shit, you will tell us everything, trust me in that, rat! Then you will be hanged on a yardarm instead of a topsail... And who the hell are you? Damn, those apes can't be trusted! Always have to do everything myself...";
			link.l1 = "Am I bothering you, gentlemen?";
			link.l1.go = "FranzGarke_1";
		break;
		
		case "FranzGarke_1":
			DialogExit();
			chrDisableReloadToLocation = true;
			sld = characterFromId("FranzGarke");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "LeFransua_PortugalTalk");
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "Portugal_LFTalk":
			dialog.text = "I like your timing... I suppose I have to thank you for keeping me alive until today?";
			link.l1 = "You are correct. My name is " + GetFullName(pchar) + " and you, the Portuguese, are still my prisoner. So don't ask me questions, we have to go.";
			link.l1.go = "Portugal_LFTalk_1";
		break;
		
		case "Portugal_LFTalk_1":
			dialog.text = "Wait, captain... there are a lot of Vasquez's men in the town, they won't let us go just like that. Give me a sword and we'll have better chances.";
			link.l1 = "You are not on good terms with your partners, huh? Fine, an extra blade is always welcome, take the corpse's weapon and stay close to me!";
			link.l1.go = "Portugal_LFTalk_2";
			link.l2 = "Don't you think that I will give you a weapon and turn my back to you?! Just stay close to me.";
			link.l2.go = "Portugal_LFTalk_4";
			pchar.quest.Portugal_LeFransua.win_condition.l1 = "location";
			pchar.quest.Portugal_LeFransua.win_condition.l1.location = "LeFransua_town";
			pchar.quest.Portugal_LeFransua.function = "CreateVaskezsPirates";
			bDisableFastReload = true;//закрыть переход
		break;
		
		case "Portugal_LFTalk_2":
			dialog.text = "Don't worry, captain, I'd better die than fall into Vasquez's hands again.";
			link.l1 = "I don't want you dead for now. Go, time is running.";
			link.l1.go = "Portugal_LFTalk_3";
		break;
		
		case "Portugal_LFTalk_3":
			DialogExit();
			GiveItem2Character(npchar, "blade_17");
			EquipCharacterbyItem(npchar, "blade_17");
			GiveItem2Character(npchar, "pistol6");
			EquipCharacterbyItem(npchar, "pistol6");
			TakeNItems(npchar, "bullet", 50);
			AddItems(npchar, "gunpowder", 50);
			TakeNItems(npchar, "potion2", 3);
			LAi_SetCharacterUseBullet(npchar, "bullet");
			pchar.questTemp.Portugal.Condition1 = "true";
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
		break;
		
		case "Portugal_LFTalk_4":
			dialog.text = "Too bad, I would have helped the One-eyed if I wanted you dead...";
			link.l1 = "But you didn't helped me either, so shut up and move!";
			link.l1.go = "Portugal_LFTalk_5";
		break;
		
		case "Portugal_LFTalk_5":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
		break;
		
		case "Vaskezs_pirate":
			PlaySound("VOICE\Russian\EvilPirates01.wav");
			dialog.text = "Damn! That's them! Get them!";
			link.l1 = "...";
			link.l1.go = "Vaskezs_pirate_1";
		break;
		
		case "Vaskezs_pirate_1":
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешим драться
			DialogExit();
			if (CheckAttribute(pchar, "questTemp.Portugal.Condition1"))
			{
				sld = characterFromId("Portugal");
				LAi_SetImmortal(sld, false);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			}
			for (i=1; i<=9; i++)
			{
				sld = characterFromId("VaskezsPirate_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "VaskezsPiratesDied");
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "Avendel_LeFransua":
			chrDisableReloadToLocation = false;
			bDisableFastReload = false;//открыть переход
			sld = characterFromId("Portugal");
			if (LAi_GetCharacterHP(sld) > 0)
			{
				dialog.text = "Splendid! You have killed the One-eyed Dog, that's what I call a masterpiece! How many of his men did you sent to burn in hell?";
				link.l1 = "I was fighting not counting. And where have you been, Hugo?";
				link.l1.go = "Avendel_LeFransua_1";
			}
			else
			{
				dialog.text = "What a pity, captain. But we have lost and we won't see that damn gold. Farewell.";
				link.l1 = "Farewell, Hugo.";
				link.l1.go = "Avendel_goodbye_1";
				RemovePassenger(Pchar, npchar);
				CloseQuestHeader("Portugal");
				pchar.questTemp.Portugal = "end";
			}
		break;
		
		case "Avendel_LeFransua_1":
			dialog.text = "I... was securing the safe withdrawal... protecting our rear so to speak.";
			link.l1 = "Well, this is the limit... Hugo Avendell, your cowardice has surpassed all my expectations, have you got any idea how tough this fight was for us? We barely made it!";
			link.l1.go = "Avendel_LeFransua_2";
		break;
		
		case "Avendel_LeFransua_2":
			dialog.text = "Calm down, captain... I admit I was hiding. But I have found this opportunity for you! Remember, it was me who has lead you to the Portuguese! Well... considering your fair indignation, I agree on only a one third of the reward.";
			link.l1 = "That's just glorious! Are you bargaining now? No, my friend, your part in this business is over! You have lost your money in the tavern of Saint-Pierre. You have left it there and run away so it is over for you now.";
			link.l1.go = "Avendel_LeFransua_3";
		break;
		
		case "Avendel_LeFransua_3":
			dialog.text = "Captain, you are clearly exaggerating... Fine, I agree for a quarter... for a fifth! Ten percent!";
			link.l1 = "Don't test my patience! Get lost! I don't need a coward in my crew, especially now when the clock is ticking!";
			link.l1.go = "Avendel_LeFransua_4";
		break;
		
		case "Avendel_LeFransua_4":
			dialog.text = ""+pchar.name+", don't you think that it is a bit unfair?";
			link.l1 = "Cause and effect, Hugo... You have made your choice, so farewell. Draw a conclusion and don't plunge into adventures like that, this is clearly not for you.";
			link.l1.go = "Avendel_LeFransua_5";
		break;
		
		case "Avendel_LeFransua_5":
			DialogExit();
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", -1);
			sld = characterFromId("Portugal");
			sld.dialog.currentnode = "Portugal_LeFransua";
			LAi_ActorDialog(sld, pchar, "", -1, 0);
			pchar.questTemp.Portugal.GG2 = "true"; // Jason Дороже золота
		break;
		
		case "Portugal_LeFransua":
			dialog.text = "Dropping away the ballast, captain? So true, ha... Vasquez is still free and there are a lot of men and guns on the Albatross, I bet my fine pants against an old kerchief that Hernando won't let us escape.";
			link.l1 = "Well, it seems that we have to go and greet him ourselves. Go, monsieur Portuguese, and try to keep you mouth shut. We are going to weigh anchor as soon as possible.";
			link.l1.go = "Portugal_LeFransua_1";
		break;
		
		case "Portugal_LeFransua_1":
			DialogExit();
			chrDisableReloadToLocation = false;
			LAi_ActorFollowEverywhere(npchar, "", -1);
			pchar.quest.Portugal_LeFransua1.win_condition.l1 = "location";
			pchar.quest.Portugal_LeFransua1.win_condition.l1.location = "Martinique";
			pchar.quest.Portugal_LeFransua1.function = "CreateVaskezsFrigate";
		break;
		
		case "VaskezsHelper_abordage":
			dialog.text = "What are you waiting for, damn it?!";
			link.l1 = "Where is Hernando Vasquez? Speak and I will spare your life.";
			link.l1.go = "VaskezsHelper_abordage_1";
		break;
		
		case "VaskezsHelper_abordage_1":
			dialog.text = "Go to hell with your fucking questions!";
			link.l1 = "After you...";
			link.l1.go = "VaskezsHelper_abordage_2";
		break;
		
		case "VaskezsHelper_abordage_2":
			DialogExit();
			QuestAboardCabinDialogExitWithBattle(""); 	
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "Portugal_treasure":
			bQuestDisableMapEnter = false;
			if (CheckAttribute(pchar, "questTemp.Portugal.Condition1") && CheckAttribute(pchar, "questTemp.Portugal.Condition2"))
			{
				dialog.text = "And here you are, my brave friend, we can have a decent talk at last! Congratulations, captain - killing the One-eyed Dog and destroying the 'Albatross' wasn't an easy job! Actually, you have done so much for saving my life... Perhaps, I should thank you?";
				link.l1 = "You will thank me when you are dancing on the gallows or whatever they have prepared for you in Willemstad.";
				link.l1.go = "Portugal_treasure_6";
			}
			else
			{
				dialog.text = "And here you are my brave friend, we can have a talk at last! Congratulations, captain - killing the One-eyed Dog is worth of an honourable song! Actually, you have done so much for saving my life... Perhaps, I should thank you?";
				link.l1 = "You will thank me when you are dancing on the gallows or whatever they have prepared for you in Willemstad.";
				link.l1.go = "Portugal_treasure_1";
			}
		break;
		
		case "Portugal_treasure_1":
			dialog.text = "Incredible! You have been saving my life for the last two weeks, you have brought me to your home and protected me in fights... and now you are going to send me to death? I can hardly believe in that... Actually, I almost consider you my friend now, ha-ha.";
			link.l1 = "A pirate who is appealing for honour? Portuguese, are you kidding me? I was saving you for only one purpose - to let the murderer and scoundrel face the justice court!";
			link.l1.go = "Portugal_treasure_2_1";
			link.l2 = "Friend of mine... sounds like a mockery. But nevertheless you are right. It would be strange of me to do that, Portuguese...";
			link.l2.go = "Portugal_treasure_2_2";
		break;
		
		case "Portugal_treasure_2_1":
			dialog.text = "Oh, enough, captain. I bet that you were doing all of that only to get money which was promised by the Company for the pleasure to see me alive! Don't try to be more honest than you actually are, sir, it doesn't suit you.";
			link.l1 = "Only I can judge myself. So let's end this conversation. It is time to sail to Willemstad.";
			link.l1.go = "Portugal_treasure_3";
		break;
		
		case "Portugal_treasure_2_2":
			dialog.text = "It seems that still some honesty can be found in people these days... Too bad that money always interferes - eh, captain?";
			link.l1 = "Strange to hear that from the gallows-bird pirate, Portuguese. I will let you go... don't ask me why, just get the hell away in the very first port. And remember that I won't be that kind if we ever meet again.";
			link.l1.go = "Portugal_treasure_4";
		break;
		
		case "Portugal_treasure_3":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);//запрет диалога
			pchar.questTemp.Portugal.Villemstad = "true";//сдать губернатору
			AddQuestRecord("Portugal", "21");
		break;
		
		case "Portugal_treasure_4":
			dialog.text = "Really? I like it, captain! Won't you order to bring here some rum? You know, just to celebrate your knightly qualities, our relationship and the deferment of my sentence?";
			link.l1 = "Don't crack wicked jokes, you are still my prisoner until the first shore. Farewell.";
			link.l1.go = "Portugal_treasure_5";
		break;
		
		case "Portugal_treasure_5":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);//запрет диалога
			pchar.quest.Remove_Portugal.win_condition.l1 = "Location_Type";
			pchar.quest.Remove_Portugal.win_condition.l1.location_type = "town";
			pchar.quest.Remove_Portugal.function = "RemovePortugal";
			AddQuestRecord("Portugal", "20");
		break;
		
		case "Portugal_treasure_6":
			dialog.text = "I see... so it is the gallows then. That was expected. Then listen what I will tell you, captain. You were so eager to keep me alive in order to execute me properly later and I appreciate it. I suppose that it will be stupid of me to ask you to change your mind just like that, right? And what will you say if I offer you something in exchange? A deal so to speak, huh?";
			link.l1 = "I won't say anything, Portuguese. You are a pirate and a bastard. You will answer for your crimes in Willemstad.";
			link.l1.go = "Portugal_treasure_2_1";
			link.l2 = "A deal? What can you offer?";
			link.l2.go = "Portugal_treasure_7";
			link.l3 = "I don't need your deal, just get lost in the very first port. It's your lucky day.";
			link.l3.go = "Portugal_treasure_4";
		break;
		
		case "Portugal_treasure_7":
			dialog.text = "You know, such persistent saving of my life despite the unpleasant reasons behind it still deserves some gratitude. And Bartolomeo the Portuguese knows something of being grateful. Now listen, a month before you and I met, we captured a ship of the Company. They fought like devils to the last men. But their holds had only cannon balls and rats\nMy crew didn't like it, yet I have found a very interesting chest and papers inside a captain's cabin. She was a courier ship, delivering samples from mines somewhere at Amazonia. Pure diamonds and rubies, a fortune!";
			link.l1 = "An interesting prize... Now I see why the Company is so interested in you, but what is the point of your story?";
			link.l1.go = "Portugal_treasure_8";
		break;
		
		case "Portugal_treasure_8":
			dialog.text = "My first mate Vazquez and Franz Garcke had been keeping the crew in order, so I decided to take my chances. I hid the stones from them and burnt the papers. The Dutch had badly damaged our rigging during the boarding and we had to take the 'Albatross' inside a small bay of a small Island in the north. I went deeper in the jungles alone while the whole crew were repairing the frigate\nI buried the stones, keeping them aboard was too risky considering the circumstances. My plan was to escape from my beloved crew in the very first port, buy or steal a small boat and sail to the island, collect my prize, and then... farewells to my old life! Europe, a decent mansion, a hot wife, you know...";
			link.l1 = "Let me guess, something went wrong.";
			link.l1.go = "Portugal_treasure_9";
		break;
		
		case "Portugal_treasure_9":
			dialog.text = "Everything went wrong! The damn island turned out to be homeland to a horde of local cannibals. They attacked us as soon as I returned to the shore. We had to sail away as soon as possible, it was then when I got hit. I thought that it was only a scratch.\nFew days later I was lying half-dead in fever and apparently said something about the stones. Franz and Vazquez realized that I had hid something on the island, yet they didn't know the exact location. They didn't like an idea of wandering there and being constantly shot by the Indians. So the bastards dragged me to the nearest port, since our physician got killed during our fight with the Dutch, they needed a new one.\nThat's how I ended up at that doctor's place, they wanted to return me my consciousness for a time enough to torture me and to find out the location of the stones. I believe, that later they would cut me and feed crabs with my juicy meat.";
			link.l1 = "I can't say that I judge them - you were trying to screw your men. So I ask again, why are you telling me about that?";
			link.l1.go = "Portugal_treasure_10";
		break;
		
		case "Portugal_treasure_10":
			dialog.text = "These dogs were not people, trust me, by the way there are all now in their deserved place - the hell, ha-ha! As a payment for my freedom and my life, I can tell the exact location of the Dutch treasures.";
			link.l1 = "No, Bart, your betrayal has totally convinced me in your meanness. Willemstad and a lawful retribution are waiting for you. No deal.";
			link.l1.go = "Portugal_treasure_2_1";
			link.l2 = "And am I supposed to believe that those gems do exist? Whatever, I won't loose a thing anyway... The deal was the start of this story and the deal will be it's end. I accept your terms, Portuguese.";
			link.l2.go = "Portugal_treasure_11";
		break;
		
		case "Portugal_treasure_11":
			dialog.text = "Consider this to be my modest gratitude. Eh, I wish I knew how much the skin of Bartolomeo the Portuguese costs in shiny pesos, ha! I understand that your goals were strictly practical, but still, thank you, captain, for everything, ha-ha\nIt's Turks, the jungles not far from its shores. Find a dry, crooked tree, there is only one such tree there. I have buried the chest close to it. So don't forget to take a shovel. Happy hunting...";
			link.l1 = "Fine, I will remember that and you can take a longboat right now and get away from my ship. Farewell.";
			link.l1.go = "Portugal_treasure_12";
		break;
		
		case "Portugal_treasure_12":
			dialog.text = "One last thing, captain. I suppose that there are still a lot of savages, but it's not only them you should worry about. Vasquez wasn't on the 'Albatross', right? The Bloody Don is too smart... watch your back until you see him hanged or with a bullet in his head.";
			link.l1 = "Thanks for your warning, Portuguese. Now would be kindly to leave my ship already... don't test my patience.";
			link.l1.go = "Portugal_treasure_13";
		break;
		
		case "Portugal_treasure_13":
			DialogExit();
			LAi_SetImmortal(npchar, false);
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "", 2.0);
			AddQuestRecord("Portugal", "23");
			pchar.quest.Portugal_Terks.win_condition.l1 = "location";
			pchar.quest.Portugal_Terks.win_condition.l1.location = "Terks_Jungle_01";
			pchar.quest.Portugal_Terks.function = "CreateHollIndBattle";
		break;
		
		case "Avendel_Marigo":
			pchar.quest.SetAvendelMarigoOver.over = "yes"; //снять таймер
			dialog.text = "Oh, and who is this! Captain "+pchar.name+" himself! Want to drink?";
			link.l1 = "You know, I am that happy to see you again. But perhaps I was to tough with you on Martinique.";
			link.l1.go = "Avendel_Marigo_1";
		break;
		
		case "Avendel_Marigo_1":
			dialog.text = "Whatever, captain! What was there, was there. By the way, I had really given you a reason. But you won't believe who is a guest in Phillipsburg today!";
			link.l1 = "Don't tell me that it is ...";
			link.l1.go = "Avendel_Marigo_2";
		break;
		
		case "Avendel_Marigo_2":
			dialog.text = "No-no, captain, it is not the Portuguese. And it is not some wounded bastard again. It is much more incredible! It is Hernando Vasquez... The Bloody Don himself! He is being a guest of the local governor for a few last days.";
			link.l1 = "Vasquez? The guest of the governor? I see now. Hugo, tell me more about that, what the hell is going on here?";
			link.l1.go = "Avendel_Marigo_3";
		break;
		
		case "Avendel_Marigo_3":
			pchar.questTemp.Portugal.AvMoney = 10000;
			dialog.text = "Well, I know a lot... but thanks to our voyage, I am a bankrupt again. Perhaps your need of this information is worth a few pesos?";
			link.l1 = "Hugo, you are still a extortioner and a scoundrel! Speak what you have got, take 5000 pesos just for the sake of our old friendship.";
			link.l1.go = "Avendel_Marigo_4_1";
			if (sti(pchar.money) >= 10000)
			{
			link.l2 = "Somehow I am not surprised. Here, take 10000 pesos and you better hope that your information costs that much money!";
			link.l2.go = "Avendel_Marigo_4_2";
			}
			link.l3 = "I have got a better proposal for you. How about to join my crew? I take it that you have a talent of accounting and trade, so if you are fed up to pretend yourself as a brave fighter - you are welcome to take a position of my purser.";
			link.l3.go = "Avendel_Marigo_4_3";
		break;
		
		case "Avendel_Marigo_4_1":
			pchar.questTemp.Portugal.AvMoney = 15000;
			dialog.text = "No, captain, it is not going to work like that! You have snatched a large sum with that damned Portuguese, I am sure. So consider that to be my share, don't be that greedy. 15000 coins and not single peso less!";
			if (sti(pchar.money) >= 15000)
			{
			link.l1 = "Hell with you, take them!";
			link.l1.go = "Avendel_Marigo_4_2";
			}
			link.l2 = "Well, and they say that greed is good... Isn't that too much for you, huh?";
			link.l2.go = "Avendel_Marigo_wait";
		break;
		
		case "Avendel_Marigo_4_2":
			AddMoneyToCharacter(pchar, -sti(pchar.questTemp.Portugal.AvMoney));
			dialog.text = "Now that's the price for me! Now listen, Vasquez was sailing with me on the same ship, yet while I was cleaning decks as a payment for the trip, he was resting in a cabin so thank God we rarely saw each other and he didn't recognized me. But I have started to follow this devil immediately... An interesting story has happened with him.";
			link.l1 = "Go on! What is he doing in the governor's palace?";
			link.l1.go = "Avendel_Marigo_5";
		break;
		
		case "Avendel_Marigo_5":
			dialog.text = "I don't know much, but the garrison have been alerted for a few days after his arrival and the huge warship had suddenly up-anchored and gone in a great hurry. The whole town was lost in guesses and gossips...";
			link.l1 = "So that was the ship I have met! Intriguing... Don't digress from the topic, Hugo, continue your story.";
			link.l1.go = "Avendel_Marigo_6";
		break;
		
		case "Avendel_Marigo_6":
			dialog.text = "Well, as I have said, the ship was gone and Vasquez had become some sort of a guest of our governor Martin Thomas. I see him sometimes in the town, he is always in a company of few soldiers. I don't know if it is his escort or convoy, ha-ha. But only people in residence could to tell you more regarding the Don.";
			if (CheckAttribute(pchar, "questTemp.Portugal.AvOfficer"))
			{
				link.l1 = "Perhaps, you are right. But we have had a deal, remember? Don't play a hero, go to my ship and wait for my return. I will try to talk with our hospitable governor.";
				link.l1.go = "Avendel_hire";
			}
			else
			{
				link.l1 = "Well, that was interesting. You have really helped me, Hugo. Drink your rum, the rest is out of your concern.";
				link.l1.go = "Avendel_Marigo_del";
			}
			AddDialogExitQuestFunction("InMarigoResidence");
		break;
		
		case "Avendel_Marigo_4_3":
			dialog.text = "Are you serious, captain? What is wrong with you? You have driven me away by pointing a gun at my face and now you are coming with such proposals?";
			if (sti(pchar.money) >= 10000)
			{
			link.l1 = "Forget about that, I have must made a slip of the tongue. Here, take 10000 pesos and tell me what you know about Vasquez, I am in a hurry.";
			link.l1.go = "Avendel_Marigo_4_2";
			}
			link.l2 = "Perhaps, I should apologize for that matter. You are a pathetic fighter, but you do fine with coins. I repeat my proposal, what do you say?";
			link.l2.go = "Avendel_Marigo_7";
		break;
		
		case "Avendel_Marigo_7":
			pchar.questTemp.Portugal.AvMoney = 20000;
			pchar.questTemp.Portugal.AvOfficer = "true";
			dialog.text = "What can I say... I will agree, but only after I get my share, captain. Ten percent, remember? You have received two thousands for that scoundrel, so if you are asking me to join your crew you'd better start from wiping away your debts. Ten percent and no arguing!";
			link.l1 = "You are such a swindler, Hugo. I don't have that much on me now, but I will be back soon. Stay here.";
			link.l1.go = "Avendel_Marigo_wait";
			if (sti(pchar.money) >= 20000)
			{
			link.l2 = "I hope, that you will justify my expectations with that business grip of yours, ha! Take your cut!";
			link.l2.go = "Avendel_Marigo_4_2";
			}
		break;
		
		case "Avendel_Marigo_wait":
			dialog.text = "It is your call, captain. I will stay here for a while. Come back if you change your mind.";
			link.l1 = "Fine, Hugo.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Avendel_Marigo_repeat";
		break;
		
		case "Avendel_Marigo_repeat":
			dialog.text = "Have you changed your mind, captain? I wait for my money then.";
			if (sti(pchar.money) >= sti(pchar.questTemp.Portugal.AvMoney))
			{
				link.l1 = "Take your coins, scoundrel!";
				link.l1.go = "Avendel_Marigo_4_2";
			}
			link.l2 = "I don't have such sum yet.";
			link.l2.go = "exit";
			NextDiag.TempNode = "Avendel_Marigo_repeat";
		break;
		
		case "Avendel_Marigo_del":
			DialogExit();
			npchar.lifeday = 0;
			LAi_CharacterDisableDialog(npchar);
		break;
		
		case "Avendel_hire":
			DialogExit();
			LAi_SetImmortal(npchar, false); // patch-8
			SetCharacterRemovable(npchar, true);
			npchar.quest.OfficerPrice = sti(pchar.rank)*1000;
			Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(npchar.id);
			npchar.loyality = 25;
			npchar.dialog.FileName = "Enc_Officer_dialog.c";
			AddDialogExitQuestFunction("LandEnc_OfficerHired");
			NextDiag.CurrentNode = NextDiag.TempNode;
		break;
		
		case "Servant":
			pchar.quest.InMarigoResidenceOver.over = "yes"; //снять таймер
			dialog.text = "Good day, captain. Want something?";
			link.l1 = "No-no, I am just waiting when mynheer Thomas will be free. Waiting for an audience... yes. Tell me, does his Excellency really consider a famous pirate Hernando Vasquez his friend?";
			link.l1.go = "Servant_1";
		break;
		
		case "Servant_1":
			dialog.text = "Of course not, mynheer! This bandit has surrendered to the authorities, but somehow he wasn't hanged. Perhaps bought his life through betraying his old partners in crime... I am not sure. He has been imprisoned for several days here... That was a nightmare, mynheer! That beast in a human form was living in our mansion!";
			link.l1 = "A nightmare it is! What could that beast tell to mynheer Thomas in order to avoid the gallows? I can't even imagine that!";
			link.l1.go = "Servant_2";
		break;
		
		case "Servant_2":
			dialog.text = "I don't know either, but I can secretly tell you that all servants were glad when his Excellency got rid of such guest...";
			link.l1 = "Got rid of him? Did he get what he deserved at last?";
			link.l1.go = "Servant_3";
		break;
		
		case "Servant_3":
			dialog.text = "Not quite so. Yet. A few days ago he was taken to a military brig which sailed to Willemstad. See, mynheer Thomas had lost an interest in the scoundrel, it seems that he tried to fool him\nAlso, they say that his ex captain was caught - Bartolomeo the Portuguese! Just think about it! Looks like the Company wants to hang them together at once. Birds say that the trial will be in a month, but why wait that long?";
			link.l1 = "The Portuguese?! Hm... thanks, my friend... it seems that mynheer Thomas is free now, I have to go.";
			link.l1.go = "Servant_4";
		break;
		
		case "Servant_4":
			DialogExit();
			npchar.lifeday = 0;
			LAi_CharacterDisableDialog(npchar);
			AddQuestRecord("Portugal", "31");
			pchar.questTemp.Portugal = "SeekPortVillemstad";
			SetFunctionTimerCondition("InMarigoResidenceOver", 0, 0, 30, false);
			colonies[FindColony("Villemstad")].jail = 0;
			sld = characterFromId("Portugal");
			sld.model = "Port_A"; //меняем модель
			sld.dialog.currentnode = "Portugal_free";
			LAi_SetStayType(sld);
			ChangeCharacterAddressGroup(sld, "Villemstad_prison", "goto", "goto9");
			sld = GetCharacter(NPC_GenerateCharacter("PortHolOfficer", "off_hol_4", "man", "man", 35, HOLLAND, 30, true, "soldier"));
			FantomMakeCoolFighter(sld, sti(pchar.rank)+MOD_SKILL_ENEMY_RATE+10, 100, 100, "blade_19", "pistol3", "grapeshot", 100);
			SetCharacterPerk(sld, "SwordplayProfessional");
			LAi_CharacterDisableDialog(sld);
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "HOLLAND_CITIZENS");
			ChangeCharacterAddressGroup(sld, "Villemstad_prison", "goto", "goto23");
			LAi_LocationDisableOfficersGen("Villemstad_prison", true);//офицеров не пускать
		break;
		
		case "Vaskez":
			dialog.text = "Now you are dead... both of you!";
			link.l1 = "...";
			link.l1.go = "Vaskez_1";
		break;
		
		case "Vaskez_1":
			DialogExit();
			LAi_ActorAnimation(npchar, "shot", "VaskezFight", 2.0);
		break;
		
		case "Portugal_free":
			if (LAi_group_GetTarget(pchar) <= 0)
			{
				dialog.text = "Now that is whom I wasn't expected to see, captain! But it doesn't look like a friendly visit, all of this blood, noise and a gunfight, eh?";
				link.l1 = "Stop cracking your wicked jokes, Portuguese. I just don't like how you have used your freedom which you bought from me. I have put too much effort on saving you pathetic arse to let you be that stupidly catched right after our parting!";
				link.l1.go = "Portugal_free_1";
			}
			else
			{
				dialog.text = "Be careful, friend! Eh, too bad I can't help you!";
				link.l1 = "...";
				link.l1.go = "exit";
				NextDiag.TempNode = "Portugal_free";
			}
		break;
		
		case "Portugal_free_1":
			dialog.text = "So the nobleness is sometimes not affected by coins, huh? Ha... WATCH IT, RIGHT BEHIND YOU!";
			link.l1 = "Not this shit again!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("CreateErnandoVaskez");
			NextDiag.TempNode = "Portugal_free";
		break;
		
		case "Portugal_free_2":
			dialog.text = "And I have warned you that this guy was a trouble!";
			link.l1 = "He almost managed to shoot me dead in the back! How did he get through?";
			link.l1.go = "Portugal_free_3";
		break;
		
		case "Portugal_free_3":
			dialog.text = "I saw that he had a lock pick, it seems that someone has given it to him... he always had connections in the lower strata. Well, captain, I believe that we should leave this place, do you agree?";
			link.l1 = "You don't say so! Fine, lets hurry up before the whole garrison has arrived here. I will break your lock in a second...";
			link.l1.go = "Portugal_free_4";
		break;
		
		case "Portugal_free_4":
			DialogExit();
			InterfaceStates.Buttons.Save.enable = true;//разрешить сохраняться
			chrDisableReloadToLocation = false;
			DoQuestReloadToLocation("Villemstad_Exittown", "rld", "loc17", "PortugalFree");
		break;
		
		case "Portugal_free_5":
			dialog.text = "You know, captain, this fresh air... you start to value it only after spending a few weeks in a dungeon right after your ship's boat was found by the local patrol. I suppose, that I still owe you for my rescue.";
			link.l1 = "No need, Portuguese. I am not an honourable knight, I just... I do what I think is right and need to be done.";
			link.l1.go = "Portugal_free_6";
		break;
		
		case "Portugal_free_6":
			dialog.text = "Ha, and that is a perfect quality! But I insist, here, take it... this is the only thing I was able to hide in the prison... Yeah, you got it right. This is my talisman. It always gave me luck in the sea. You are a fine sailor and you or your navigator will be able to use it, I am sure.";
			link.l1 = "Yes, and you were lucky enough to get straight in the hands of the Dutch with that talisman.";
			link.l1.go = "Portugal_free_7";
		break;
		
		case "Portugal_free_7":
			dialog.text = "Hey! I am still alive, huh? And for you to know, I am not in prison any longer. Take it, captain, it is time for the talisman to serve you. And I thank you again!";
			link.l1 = "Farewell then, Portuguese. And, please, try not to come to the gallows! Just for the sake of my hard work, ha-ha!";
			link.l1.go = "Portugal_free_8";
		break;
		
		case "Portugal_free_8":
			TakeNItems(pchar, "talisman2", 1);
			Log_Info("You have received the talisman");
			PlaySound("interface\important_item.wav");
			DialogExit();
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "", 10.0);
			npchar.lifeday = 0;
			LAi_LocationDisableOfficersGen("Villemstad_prison", false);//офицеров пускать
			AddQuestRecord("Portugal", "34");
			CloseQuestHeader("Portugal");
			pchar.questTemp.Portugal = "end";
			pchar.questTemp.Portugal.GG1 = "true"; // Jason Дороже золота
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}