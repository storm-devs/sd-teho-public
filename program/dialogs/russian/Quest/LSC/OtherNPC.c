// диалоги прочих НПС по квесту LSC
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "Want something?";
			link.l1 = "No, it is nothing.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		//-----------------------------------бандосы Акулы в трюме с припасами--------------------------------------
		case "PantryGuard":
			dialog.text = "Ho, ho, just look at this, lads! Who has come to visit us! A thief looting people's chests! Come here! And you, pal, don't even try to play stupid and take your blade - I won't miss from such close distance... Chad will be really glad to see you!";
			link.l1 = "But I... I have just got here!";
			link.l1.go = "PantryGuard_1";
		break;
		
		case "PantryGuard_1":
			dialog.text = "You are right, ha-ha! You have just got in a real mess, buddy... And you won't get away from it. Now, surrender your weapons and follow me! The cage on the 'Tartarus' has been waiting for you for so long, thief!";
			link.l1 = "...";
			link.l1.go = "PantryGuard_2";
		break;
		
		case "PantryGuard_2":
			DialogExit();
			chrDisableReloadToLocation = false;
			SetLaunchFrameFormParam("Few hours later...", "", 0, 3);
			LaunchFrameForm();
			WaitDate("", 0, 0, 0, 7, 10); //крутим время
			RecalculateJumpTable();
			DoQuestFunctionDelay("LSC_GotoPrison", 3.0);
		break;
		
		case "CommonGuard":
			dialog.text = "Don't try to steal anything from here. I will watch over you.";
			link.l1 = "You are most welcome.";
			link.l1.go = "exit";
			NextDiag.TempNode = "CommonGuard";
		break;
		
		case "ChadGuard":
			dialog.text = "Go and do what Chad told you. Don't talk too much!";
			link.l1 = "Yes, I am on my way...";
			link.l1.go = "exit";
			NextDiag.TempNode = "ChadGuard";
		break;
		
		case "ChadGuard_Attack":
			dialog.text = "Hey! What the hell are you doing there? Bastard! Now you are done!";
			link.l1 = "...";
			link.l1.go = "ChadGuard_Attack_1";
		break;
		
		case "ChadGuard_Attack_1":
			DialogExit();
			sld = characterFromId("Chimiset");
			LAi_SetActorType(sld);
			LAi_ActorAnimation(sld, "afraid", "", -1);
			for(i = 1; i <= 3; i++)
			{				
				sld = CharacterFromID("ChadGuard_"+i);
				LAi_RemoveCheckMinHP(sld);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			sld = characterFromId("Capper");
			LAi_SetWarriorType(sld);
			ChangeCharacterAddressGroup(sld, "Tartarusprison", "goto", "goto8");
			LAi_group_MoveCharacter(sld, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "LSC_ChadGuard_Die");
			AddDialogExitQuest("MainHeroFightModeOn");
			pchar.GenQuest.Notsearchbody = true; // запрет обыска трупов
		break;
		
		// ----------------------------------Марчелло Циклоп--------------------------------
		// если ждали в каюте
		case "Cabin":
			dialog.text = "Hey, what the fuck are you doing here, god damn it? Where is Barbier?";
			link.l1 = "Our friend Adolfo is... ill. He couldn't come to the meeting so he asked me to sit a bit in his cabin and wait for you.";
			link.l1.go = "Cabin_1";
		break;
		
		case "Cabin_A":
			dialog.text = "Hey, what the fuck are you doing here, god damn it?";
			link.l1 = "Our friend Adolfo is... ill. He couldn't come to the meeting so he asked me to be instead of him. So to speak.";
			link.l1.go = "Cabin_1";
		break;
		
		case "Cabin_1":
			dialog.text = "Sounds strange... he was fine this morning and now he is ill.";
			link.l1 = "Well, you know how things happen. The sudden attack of fever...";
			link.l1.go = "Cabin_2";
		break;
		
		case "Cabin_2":
			dialog.text = "Oh, I don't like your face. You are lying. Barbier would never trust this meeting to anyone else. Speak, bastard, who are you and what did you do to him?";
			link.l1 = "You know, you are not a pretty face either. I have already told you that Barbier is ill. Are you a slow thinking type or should I repeat myself? He was supposed to give you the key and...";
			link.l1.go = "Cabin_3";
		break;
		
		case "Cabin_3":
			DialogExit();
			sld = characterFromId("Mary");
			LAi_SetActorType(sld);
			LAi_CharacterEnableDialog(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		// на Церес Смити - спасаем Мэри
		case "mary":
			dialog.text = "Damn it! You have tracked me down...";
			link.l1 = "Yes, scum! You won't lay a hand on her! Prepare to die!";
			link.l1.go = "mary_1";
		break;
		
		case "mary_1":
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешить драться
			DialogExit();
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "LSC_KillCyclop_CS");
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		// посланник от Акулы по варианту N
		case "SharkCureer":
			dialog.text = "Are you "+GetFullName(pchar)+"?";
			link.l1 = "Yes, it is me. What is the matter?";
			link.l1.go = "SharkCureer_1";
		break;
		
		case "SharkCureer_1":
			dialog.text = "Shark has sent me. He asks you to see him as soon as possible. He has something important for you.";
			link.l1 = "What's the hurry?.. Fine, I am going to the 'San Agustin' immediately.";
			link.l1.go = "SharkCureer_2";
		break;
		
		case "SharkCureer_2":
			// сюда можно поставить таймер на гибель Акулы, если не придет до конца суток
			DialogExit();
			LAi_SetActorType(npchar);
			npchar.lifeday = 0;
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", -1);
			sld = characterFromId("Dodson");
			sld.dialog.currentnode = "entrance_20"; // ноду Акуле
		break;
		
		// посланник от Акулы по варианту M
		case "SharkCureer_3":
			dialog.text = "Are you "+GetFullName(pchar)+"?";
			link.l1 = "Yes, it is me. What is the matter?";
			link.l1.go = "SharkCureer_4";
		break;
		
		case "SharkCureer_4":
			if (!CheckAttribute(pchar, "questTemp.Saga.DodsonDie"))
			{
				dialog.text = "Uh, I am tired of looking for you... The Shark and Layton Dexter. They ask you to see them immediately. It is a very important matter so hurry up.";
				link.l1 = "Is it? Fine, I am going to the 'San Agustin' immediately.";
				link.l1.go = "SharkCureer_6";
			}
			else
			{
				dialog.text = "Uh, I am tired of looking for you... Admiral Layton Dexter asks you to see him immediately. It is a very important matter so hurry up.";
				link.l1 = "Admiral?";
				link.l1.go = "SharkCureer_5";
			}
		break;
		
		case "SharkCureer_5":
			dialog.text = "Yes. As being the second in command he has become our admiral after the Shark's death.";
			link.l1 = "I see. Fine, I am going to the 'San Agustin' immediately.";
			link.l1.go = "SharkCureer_6";
		break;
		
		case "SharkCureer_6":
			DialogExit();
			LAi_SetActorType(npchar);
			npchar.lifeday = 0;
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", -1);
		break;
		
		// тюремщик вместо Каппера
		case "Prisonboss":
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "Ah, here you are... I remember you, you are the last man who has spoken to Chimiset. Have you killed him?";
				link.l1 = "Cut the bullshit! You perfectly know that it wasn't me. I think that you know who is the killer.";
				link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "Eh, it is so boring to stay here the whole day! If only you would bring rum and cards here, pal, we might have a gamble...";
				link.l1 = "Sorry, pal, I don't have time for this. Perhaps, later.";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "Prisonboss";
		break;
		
		case "meeting":
			dialog.text = "I have a few guesses, yes, but I don't have any facts. No one saw the death of the black guy. There are gossips all around the island that we, Shark's people, are responsible and they say that some newbie did this by the order of the admiral. See now? So don't go to Rivados, especially now. They are too angry.";
			link.l1 = "Fine. I got it.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Prisonboss";
		break;
		
		case "Prisonboss_M":
			dialog.text = "Eh, it is so boring to stay here the whole day! If only you would bring rum and cards here, pal, we might have a gamble...";
			link.l1 = "Sorry, pal, I don't have time for this. Perhaps, later.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Prisonboss_M";
		break;
		
		// заместитель Акселя в магазине
		case "AxelHelper":
			dialog.text = "What do you want, pal?";
			link.l1 = "Hm. And what is your business here? Where is Axel?";
			link.l1.go = "AxelHelper_1";
		break;
		
		case "AxelHelper_1":
			dialog.text = "Axel is busy. He is having a meeting with Donald Greenspen and he will stay with him until the end of the day. So if you want to buy something - talk to him tomorrow morning. And I am looking after the shop so don't try to steal anything...";
			link.l1 = "I see. And why is he doing it today? Fine, I will come here tomorrow morning.";
			link.l1.go = "exit";
			NextDiag.TempNode = "AxelHelper_2";
		break;
		
		case "AxelHelper_2":
			dialog.text = NPCStringReactionRepeat("I have already told you everything. Come here tomorrow.", 
				"Don't bother me, pal. Get lost!", 
				"Don't make me angry, jerk!",
				"Go away!!", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Fine.", 
				"I got it, I got it.",
				"Shut up...", 
				"What?!", npchar, Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("exit", "", "", "", npchar, Dialog.CurrentNode);
		break;
		
		// мать Белого Мальчика - Агнес Кристиансен
		case "agnes":
			dialog.text = "What do you want, mynheer?";
			link.l1 = "Hm... I am sorry, mistress. Forgive me for my impudence and bad manners, but I want to ask you something: do you know a man named Ole Christiansen?";
			link.l1.go = "agnes_1";
		break;
		
		case "agnes_1":
			dialog.text = "Repeat again what you've said... Ole Christiansen? Ole?!";
			link.l1 = "Yes. They also call him the White Boy for a special color of his hair. Do you know him?";
			link.l1.go = "agnes_2";
		break;
		
		case "agnes_2":
			dialog.text = "Do I know him?! He is my son and he has been missing for a decade! Do you know where is he, mynheer? Tell me already where is he, what has happened to him?!";
			link.l1 = "Calm down, mistress, don't worry like that. He is fine. He is on my ship. All he needs is to land and come here.";
			link.l1.go = "agnes_3";
		break;
		
		case "agnes_3":
			dialog.text = "Oh... It seems that the Lord has finally heard my prays! You can't imagine how I was worrying when he has missed! And it was my and only my fault! Where have you found him? He is not a common kid... well, you must know what I am talking about.";
			link.l1 = "I do. Yes, he is special. And he hasn't changed. It seems that he is still a child. I found him on one island. We met each other by accident. He asked me for a white bead... damn it!... For a pearl.";
			link.l1.go = "agnes_4";
		break;
		
		case "agnes_4":
			dialog.text = "A pearl? Oh, God! Pearls were the reason why my boy has disappeared! It is all because of that damn necklace!";
			link.l1 = "Is it true that Ole... has gone from his home because of tearing your pearl necklace?... Calm down, mistress, don't cry!";
			link.l1.go = "agnes_5";
		break;
		
		case "agnes_5":
			dialog.text = "Yes, it is true. Ole tore my necklace at the pier and all pearls fell into water. I was so swearing at him and my late husband... punished him. Ole disappeared the next day. You can't imagine how I was blaming myself for this!";
			link.l1 = "Ole has been collecting pearls for years. He calls them the white beads. He has collected them all for you and asked me to take him to you. I had no details except the house with a red roof. But I have finally managed to find you.";
			link.l1.go = "agnes_6";
		break;
		
		case "agnes_6":
			dialog.text = "Collecting pearls?! Oh, God! I am so guilty towards my poor boy! I... and he has been collecting pearls! Oh!";
			link.l1 = "I suppose that I'd better call for your son, mistress. He was so eager to see you. He said that you will be happy to see pearls. But I think that you will be happy not because of them...";
			link.l1.go = "agnes_7";
		break;
		
		case "agnes_7":
			dialog.text = "Mynheer... would you be kindly. Bring my Ole to me. I want to hug him and ask for his forgiveness...";
			link.l1 = "Sure, mistress. They will bring him here at once.";
			link.l1.go = "agnes_8";
		break;
		
		case "agnes_8":
			DialogExit();
			SetLaunchFrameFormParam("Прошел час...", "", 0, 5);
			LaunchFrameForm();
			WaitDate("", 0, 0, 0, 1, 10); //крутим время
			RecalculateJumpTable();
			DoQuestFunctionDelay("LSC_OleGoHome", 5.0);
		break;
		
		case "agnes_9":
			dialog.text = "";
			link.l1 = "Well, mistress, here is your son - Ole Christiansen. Do you recognize him?";
			link.l1.go = "agnes_10";
		break;
		
		case "agnes_10": // перекидываем pchar
			DialogExit();
			LAi_SetActorType(pchar);
			LAi_ActorTurnToCharacter(pchar, characterFromID("Agnes"));
			ChangeShowIntarface();
			SetMainCharacterIndex(GetCharacterIndex("Agnes"));
			PChar = GetMainCharacter();			
			LAi_SetPlayerType(PChar);
			sld = characterFromId("Ole");
			sld.dialog.currentnode = "home";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "agnes_11":
			dialog.text = "Mynheer... I am sorry, I didn't ask for your name... "+pchar.name+"?";
			link.l1 = ""+GetFullName(pchar)+", mistress. Captain "+GetFullName(pchar)+".";
			link.l1.go = "agnes_12";
		break;
		
		case "agnes_12":
			dialog.text = "Captain, you can't imagine how grateful am I for my son! You have helped him and brought him here. You have made me to live again! I will do everything for my boy, I will give him all my love which he missed for all this years.";
			link.l1 = "I am glad for you, mistress. And for Ole too. He is a good boy and he helped me in the tough situation. He has a kind heart. I know a man who was saved by Ole from the death.";
			link.l1.go = "agnes_13";
		break;
		
		case "agnes_13":
			dialog.text = "Mynheer, I insist that you must come here tomorrow or at any whenever you find time. I want to thank you for my son. At this moment I am just a bit... well, you know.";
			link.l1 = "I do, mistress.";
			link.l1.go = "agnes_14";
		break;
		
		case "agnes_14":
			dialog.text = "Come back here tomorrow. I will reward you properly for all good you have done to my son and to me.";
			link.l1 = "Fine. I will visit you for sure!";
			link.l1.go = "agnes_15";
		break;
		
		case "agnes_15":
			DialogExit();
			bDisableCharacterMenu = false;//лоченые интерфейсы
			chrDisableReloadToLocation = false;//открыть локацию
			LAi_SetOwnerType(npchar);
			LocatorReloadEnterDisable("Marigo_town", "houseSp2", true);
			NextDiag.CurrentNode = "agnes_16";
			pchar.quest.LSC_Ole_return.win_condition.l1 = "Timer";
			pchar.quest.LSC_Ole_return.win_condition.l1.date.hour  = 8.0;
			pchar.quest.LSC_Ole_return.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.LSC_Ole_return.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.LSC_Ole_return.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.LSC_Ole_return.function = "LSC_OleAgnesRegard";
			// удаляем Оле из пассажиров
			sld = characterFromId("Ole");
			RemovePassenger(Pchar, sld);
			DeleteAttribute(pchar, "GenQuest.Ole");
			DoQuestReloadToLocation("Marigo_town", "reload", "houseSp2", "");
		break;
		
		case "agnes_16":
			dialog.text = "Ah, here you are, mynheer "+GetFullName(pchar)+"! Come, take a sit...";
			link.l1 = "Thanks! How is Ole?";
			link.l1.go = "agnes_17";
		break;
		
		case "agnes_17":
			dialog.text = "Oh, you can't imagine what you have done! You was a sight for sore mother's heart... I owe you and I will pray for you forever.";
			link.l1 = "You make me blush, mistress...";
			link.l1.go = "agnes_18";
		break;
		
		case "agnes_18":
			dialog.text = "I always knew that modesty is what makes noble people noble… I have prepared gifts for what you've done. Yes-yes! And don't even dare to decline! Here, take this... First, there is a chest filled with doubloons. Second, take this enchanted amulet, they call it a Scarab\nMy husband owned it, and I am sure that he would had be glad to know that his treasure will belong to such a noble captain, who returned my son to me. My husband was a carpenter, he used to say that Scarab speeds up his work\nI hope that this ring will serve you well. You deserve to wear it, no doubt! And finally, take my tailoring tools. It's a fine set. You will be able to craft a lot of good things with it.";
			link.l1 = "Oh! These are really valuable gifts for any captain! Thanks, mistress.";
			link.l1.go = "agnes_19";
		break;
		
		case "agnes_19":
			PlaySound("interface\important_item.wav");
			Log_Info("You have received a chest with doubloons");
			Log_Info("You have received the 'Scarab' amulet");
			Log_Info("You have received a sartorial set");
			GiveItem2Character(pchar, "chest");
			GiveItem2Character(pchar, "talisman7");
			GiveItem2Character(pchar, "tailor_tool");
			dialog.text = "And I want you to know that the doors of my house are always open for you any time. You will always find here food, a bottle of fine wine and anything else you want.";
			link.l1 = "Thanks for your kind words, mistress. I will be glad to see you when I visit this town again.";
			link.l1.go = "agnes_20";
		break;
		
		case "agnes_20":
			dialog.text = "Don't fail to come!";
			link.l1 = "And now I have to go. Goodbye and good luck!";
			link.l1.go = "agnes_21";
		break;
		
		case "agnes_21":
			DialogExit();
			NextDiag.CurrentNode = "agnes_22";
			AddCharacterExpToSkill(pchar, "Fortune", 350);
			AddCharacterExpToSkill(pchar, "Leadership", 500);
			ChangeCharacterComplexReputation(pchar, "nobility", 10);
			ChangeCharacterComplexReputation(pchar, "authority", 4);
		break;
		
		case "agnes_22":
			dialog.text = "Ah, captain "+GetFullName(pchar)+"! I am so glad to see you! Come and sit, I will serve you a drink...";
			link.l1 = "Thanks! I just wanted to greet you and to know how you were doing. I am glad that you and Ole are fine.";
			link.l1.go = "exit";
			NextDiag.TempNode = "agnes_22";
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		//----------------------------------------- специальные реакции -----------------------------------------------
		//обнаружение ГГ в сундуках
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("What are you doing there, ah? Thief!", "Just look at that! As soon as I was lost in contemplation, you decided to check my chest!", "Decided to check my chests? You won't get away with it!");
			link.l1 = "Damn it!";
			link.l1.go = "fight";
		break;
		
		case "Woman_FackYou":
			dialog.text = "What?! Decided to check my chests? You won't get away with it!";
			link.l1 = "Foolish girl!";
			link.l1.go = "exit_setOwner";
			LAi_group_Attack(NPChar, Pchar);
		break;
		
		case "fight":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LAi_SetOwnerTypeNoGroup(npchar);
			LAi_group_Attack(NPChar, Pchar);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "exit_setOwner":
			LAi_SetOwnerTypeNoGroup(npchar);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}