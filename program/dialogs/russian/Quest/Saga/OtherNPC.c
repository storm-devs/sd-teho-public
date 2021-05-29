// диалог прочих НПС по квесту Саги
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
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "Want something?";
			link.l1 = "No, it's nothing.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
//---------------------------------------------Джимми в доме в Марун-Тауне------------------------------------
		case "Jimmy":
			dialog.text = "What do you want? Don't you see that I am in grief! Get lost before I kick you downstairs!";
			link.l1 = "First, buy yourself a bigger house with stairs in it and only then kick people downstairs, hero...";
			link.l1.go = "Jimmy_1_1";
			link.l2 = "Why so upset, Jimmy? No rum for me for the rest of my damn life if it's not about some beauty! Only beauties can make such an old sea wolf like you threaten your old friends...";
			link.l2.go = "Jimmy_1_2";
		break;
		
		case "Jimmy_1_1":
			dialog.text = "I hate fastidious people like you! You always get the better pieces. They didn't let me to kill one upstart so I will wreak my anger on you!";
			link.l1 = "...";
			link.l1.go = "Jimmy_fight";
		break;
		
		case "Jimmy_fight":
			chrDisableReloadToLocation = true;//закрыть локацию
			DialogExit();
			LAi_SetImmortal(npchar, false);
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "Saga_KillJimmy");
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
		case "Jimmy_1_2":
			dialog.text = "Yeah?! Do I know you? I don't remember a thing God damn it...";
			link.l1 = "It is me, "+pchar.name+"! We had a nice time in Blueweld after you had almost disembowelled that insolent fellow in a coat. What was his name by the way? I have forgotten it... I won't give a damn about cannons of his corvette if I meet him at the sea!";
			link.l1.go = "Jimmy_2";
		break;
		
		case "Jimmy_2":
			dialog.text = "His name was Arthur! Arthur Donovan, captain of 'Arbutus' corvette! Filthy bastard! So you say that I was close to send him to the devil?";
			link.l1 = "So it was! He had no chance, but your pals interfered. Forgive them, they didn't want you to be hanged for a murder of naval officer.";
			link.l1.go = "Jimmy_3";
		break;
		
		case "Jimmy_3":
			dialog.text = "Argh! If only I had a ship! This bastard can be easily found near Antigua... ha! I owe you if you'll send him to the bottom!";
			link.l1 = "Deal, ha-ha! Is Rumba really worth yours sufferings?";
			link.l1.go = "Jimmy_4";
		break;
		
		case "Jimmy_4":
			dialog.text = "By all means! I have never met anyone better than her. But she is just laughing at me. Everybody wants that mermaid. They have secretly told me that our Jacob is looking for some girl who looks just like my Rumba. He wants her too! How can I follow his orders now?";
			link.l1 = "Keep quiet, pal! Walls have ears... And why do you think that Jackman is looking for Rumba?";
			link.l1.go = "Jimmy_5";
		break;
		
		case "Jimmy_5":
			dialog.text = "Sure he is! He is looking for some Henry the Hangman and a twenty years old girl with blond hair and blue eyes. Some Gladys Chandler from Belize must be her tutor.";
			link.l1 = "Wait! But Gladys has a different surname. And she is her mother!";
			link.l1.go = "Jimmy_6";
		break;
		
		case "Jimmy_6":
			dialog.text = "Jimmy is cunning! You can't catch him with chaff! I've been courting Rumba for a while and found out that Gladys married Shawn McArthur exactly twenty years ago. And  before that she lived in Belize. Her first husband was called Pete Chandler\nPoor Pete was killed in a drunk fight. They say that McArthur himself is responsible, he had feelings for plumpy Gladys back then. She became a widow with a baby on her hands. The child didn't outlive the daddy much and died of fever\nAnd soon Gladys and Sean had shown up in Blueweld with a living girl stated to be McArthur's daughter. So, how could Gladys give birth to another baby that soon? Do you follow?";
			link.l1 = "Have you told anyone else about it?";
			link.l1.go = "Jimmy_7";
		break;
		
		case "Jimmy_7":
			dialog.text = "Not yet. Keep your mouth shut or.... You know me!";
			link.l1 = "Yep, I do. That rotten tongue which tells anyone any secrets. Rumba was right to send you away, blabbermouth...";
			link.l1.go = "Jimmy_8_1";
			link.l2 = "Sure! I will be tight-lipped! And now I have to go. Farewell, Jimmy.";
			link.l2.go = "Jimmy_8_2";
		break;
		
		case "Jimmy_8_1":
			dialog.text = "What... what did you say?!";
			link.l1 = "You won't tell it anyone else...";
			link.l1.go = "Jimmy_fight";
			pchar.questTemp.Saga.Jimmysecret = "true";
		break;
		
		case "Jimmy_8_2":
			DialogExit();
			pchar.questTemp.Saga = "jackman";
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeday = 0;
			AddQuestRecord("Saga", "4_1");
		break;
// <-- Джимми 
		
//-------------------------------------------корвет Донована, абордаж-----------------------------------------
		//Донован
		case "Donovan_abordage":
			PlaySound("VOICE\Russian\saga\Artur Donovan.wav");
			dialog.text = "Argh, you creature!";
			link.l1 = "Do you mean yourself, mister?! Where is Rumba?";
			link.l1.go = "Donovan_abordage_1";
		break;
		
		case "Donovan_abordage_1":
			dialog.text = "What Rumba? I don't have scums with nicknames on my ship. This is English naval vessel!";
			link.l1 = "Don't play stupid, Donovan. You perfectly understand about who I am talking about. Where is the girl? Where is Helen, I ask you?";
			link.l1.go = "Donovan_abordage_2";
		break;
		
		case "Donovan_abordage_2":
			dialog.text = "Helen? There are no port whores on my ship, you piece of shit!";
			link.l1 = "No port whores? Hard to think so since one of them is obviously standing right in front of me now... I take it that there is no point to continue our conversation. Die, worm!";
			link.l1.go = "Donovan_abordage_3";
		break;
		
		case "Donovan_abordage_3":
			chrDisableReloadToLocation = true;//закрыть локацию
			DialogExit();
			LAi_SetCurHPMax(npchar);
			QuestAboardCabinDialogFree();
			LAi_group_SetRelation(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck(LAI_GROUP_BRDENEMY, "Saga_AfterDonovanBoarding");
			AddDialogExitQuest("MainHeroFightModeOn");
			pchar.questTemp.Saga.Takehelen = "true";//признак, что абордировали судно
		break;
		
		//наш матрос
		case "Tempsailor":
			dialog.text = "Captain, we have searched cabins and the cargo hold as you told us. We have found a chained girl in cargo hold...";
			link.l1 = "Such a bastard! Just as I thought... Have you unchained the girl?";
			link.l1.go = "Tempsailor_1";
		break;
		
		case "Tempsailor_1":
			dialog.text = "Sure, captain. She is on your ship and she is safe.";
			link.l1 = "Well done! Take her to my cabin, I want to talk with her once the fighting is over.";
			link.l1.go = "Tempsailor_2";
		break;
		
		case "Tempsailor_2":
			dialog.text = "Aye-aye, captain!";
			link.l1 = "...";
			link.l1.go = "Tempsailor_3";
		break;
		
		case "Tempsailor_3":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "OpenTheDoors", 10.0);
		break;
		//<-- абордаж корвета Донована
		
//----------------------------------------поиск Энрике Гонсалеса, Картахена----------------------------------
		//фальшивый Гонсалес №1, дом
		case "GonsalesA":
			dialog.text = "Want something?";
			link.l1 = "Hello, Hangman! Best regards from captain Butcher.";
			link.l1.go = "GonsalesA_1_1";
			link.l2 = "My name is Charles de Maure. I am looking for Enrique, the son of senora Gonzales on behalf of her old friend. I think that you are him...";
			link.l2.go = "GonsalesA_2_1";
		break;
		
		case "GonsalesA_1_1":
			dialog.text = "What the hell! I don't know any Butcher!";
			link.l1 = "Come on, Henry. Tell me why Jackman's pirates are looking for you and I won't hurt you.";
			link.l1.go = "GonsalesA_1_2";
		break;
		
		case "GonsalesA_1_2":
			dialog.text = "Help! Pirates! Murdering!";
			link.l1 = "Shut up, idiot! Half of the town will run here because of you shouts. Ah, is that what you want?!";
			link.l1.go = "GonsalesA_1_fight";
		break;
		
		case "GonsalesA_1_fight":
			DialogExit();
			SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
			LAi_group_MoveCharacter(NPChar, "EnemyFight");
			LAi_group_Attack(NPChar, Pchar);
			LAi_group_SetCheck("EnemyFight", "Saga_KillGonsalesA");
			AddDialogExitQuest("MainHeroFightModeOn");
			pchar.questTemp.Saga.Trap = "true";
		break;
		
		case "GonsalesA_2_1":
			dialog.text = "Hm... Mister, you must be mistaken. I was growing up in a foreign family, I don't remember my mother. I have taken the surname of my tutor. I don't know my mother's name but I doubt that it was Gonzales. You can make inquiries about me and any old resident will confirm my words. My stepfather was a famous man, he didn't have children of his own so I have inherited this house and...";
			link.l1 = "I am sorry. It seems that I was mistaken. Farewell.";
			link.l1.go = "GonsalesA_2_2";
		break;
		
		case "GonsalesA_2_2":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			chrDisableReloadToLocation = false;//открыть локацию
			AddQuestRecord("Saga", "17");
		break;
		
		// фальшивый Гонсалес №2, улицы
		case "GonsalesB":
			PlaySound("VOICE\Russian\citizen\Pirati v Gorode-08.wav");
			dialog.text = "I see that you like my cutlass. I can sell it if you want. I won't ask too much, I am dying to drink some rum and my pockets are empty.";
			link.l1 = "And why the hell would I need it? The Forest Devil has asked me to give you his best regards.";
			link.l1.go = "GonsalesB_1_1";
			if (sti(pchar.money) >= 1000)
			{
				link.l2 = "Well, yes. You have got a fine cutlass. How much?";
				link.l2.go = "GonsalesB_2_1";
			}
		break;
		
		case "GonsalesB_1_1":
			dialog.text = "He'd better give me hundred pesos instead!";
			link.l1 = "So do you know Swanson?";
			link.l1.go = "GonsalesB_1_2";
		break;
		
		case "GonsalesB_1_2":
			dialog.text = "Fuck you and fuck your Swanson, go with him to the devil. To the forest devil or to the sea devil, I don't give a shit. If you are not willing to help the ill man and buy his cutlass then I will insert it right in your ass for free.";
			link.l1 = "Really? Let's see how are you going to perform that, drunk face!";
			link.l1.go = "GonsalesB_1_fight";
		break;
		
		case "GonsalesB_1_fight":
			chrDisableReloadToLocation = true;
			DialogExit();
			LAi_group_MoveCharacter(NPChar, "EnemyFight");
			LAi_group_Attack(NPChar, Pchar);
			LAi_group_SetCheck("EnemyFight", "Saga_KillGonsalesB");
			AddDialogExitQuest("MainHeroFightModeOn");
			pchar.questTemp.Saga.Trap = "true";
		break;
		
		case "GonsalesB_2_1":
			dialog.text = "I see an experienced man! One thousand pesos and it's yours.";
			link.l1 = "Deal!";
			link.l1.go = "GonsalesB_2_2";
		break;
		
		case "GonsalesB_2_2":
			AddMoneyToCharacter(pchar, -1000);
			GiveItem2Character(pchar, "blade_10");
			RemoveCharacterEquip(npchar, BLADE_ITEM_TYPE);
			dialog.text = "There are only two cutlasses like this in Cartagena - mine and old Alvares's from the lighthouse. But he won't sell his. He is a hypocrite, but I can smell a former pirate from a mile away. The blade is a some sort of talisman for him\nIt seems that the poor soul has things he wants to forget. This must be the reason why he goes to church every month, sins don't let him sleep.";
			link.l1 = "And I see that you have also got some history. It must be you who Swanson was talking about about. He said to give you his best regards in case I'll meet you in Cartagena.";
			link.l1.go = "GonsalesB_2_3";
		break;
		
		case "GonsalesB_2_3":
			dialog.text = "Swanson? Don't know him. My name is Henrique Gallardo. But if your Swanson has a bottle of rum for me then I agree to be Henry for him for a while. You can call me however you want. How about a drink?";
			link.l1 = "Not today. Swanson is far away and a tavern is close. You have got coins now, so farewell, Henrique.";
			link.l1.go = "GonsalesB_2_4";
		break;
		
		case "GonsalesB_2_4":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload4_back", "none", "", "", "", 20.0);
			npchar.lifeday = 0;
			AddQuestRecord("Saga", "19");
			pchar.questTemp.Saga = "ortega";
			Saga_SetOrtega();
		break;
		
		//настоящий Гонсалес - Ортега, маяк
		case "Ortega":
			dialog.text = "I don't expect any guests neither today nor any other day. What do you want?";
			link.l1 = "Hello, Hangman. Forest Devil has sent me to you. It is good that I have found you before Jackman's lads. His men are looking for you across all the Caribbean. Lucky for you, Henry, only Swanson knows where you were born. He asked me to warn you.";
			link.l1.go = "Ortega_1";
		break;
		
		case "Ortega_1":
			dialog.text = "I see now... So, it seems that Swanson is still alive and hasn't forgotten his old friend. A lot of blood has flown since I first saw him as a rookie standing on board of a damaged brig... The life was too fast and I don't have much time left\nI wanted to die by natural causes at this wasteland, away from men and close to the sea. But if Jackman is back in the Caribbean, he won't leave me alone. It was not my fault, but I owe his master. But who will believe me now\nI am afraid not of death, but of pain. And Jackman knows a lot about pain. The only thought of it makes my heart stop and everything is going dark.";
			link.l1 = "Butcher was hanged twenty years ago, so you don't have to repay debts to anyone. You can give your debt to me if you are scared of Jackman. I think that you will meet him anyway.";
			link.l1.go = "Ortega_2";
		break;
		
		case "Ortega_2":
			dialog.text = "It is not easy to hang people like Butcher. The former executioner of St. John's could tell you a lot of interesting stories about dead who returned from the hell. Jacob has learned well from his captain though, so I am not sure whom I fear most.";
			link.l1 = "Why Jackman needs you?";
			link.l1.go = "Ortega_3";
		break;
		
		case "Ortega_3":
			dialog.text = "I had to deliver gold to one widow as a payment for Butcher's daughter keeping. Why are you looking at me like that? Yes, she was born not long before the 'Neptune' was sunk. He couldn't back for her in time so he sent me to take care of the baby and her tutor.";
			link.l1 = "Was Gladys Chandler the tutor's name?";
			link.l1.go = "Ortega_4";
		break;
		
		case "Ortega_4":
			dialog.text = "Don't play an idiot. If Jackman is looking for me then he needs Butcher's daughter. You must know already that he is also looking for a woman from Belize named Gladys and her foster child. Be honest with me and I might trust you.";
			link.l1 = "What were you supposed to tell Gladys?";
			link.l1.go = "Ortega_5";
		break;
		
		case "Ortega_5":
			dialog.text = "Nothing. I was supposed to show her a Butcher's ring, that's how she would know that I was a courier from the captain. I also had to give her a chest of doubloons for the baby's needs. I had to kill one bastard to take away the ring. It made me stay at Antigua for an extra month\nAnd when I had finally reached Belize, Gladys was already gone and the city was burnt and plundered by the Spanish. She managed to sell her house and run away with her new boyfriend and the baby Helen. I hope that she took care of her and didn't sell the girl to the gypsies or to the brothel for fun.";
			link.l1 = "Butcher's daughter name was Helen, right?";
			link.l1.go = "Ortega_6";
		break;
		
		case "Ortega_6":
			dialog.text = "Exactly. In honour of Butcher's mother. If you are not scared of living dead and pirates with dead eyes, then I can give you my ring and my gold. I have never even touched it. I was dying of starvation but I didn't touch it. Do with this delivery what you want. And in return I'd ask y...";
			link.l1 = "What is happening, Henry?!";
			link.l1.go = "Ortega_7";
		break;
		
		case "Ortega_7":
			dialog.text = "You...u... I as...k.... oh!";
			link.l1 = "No!";
			link.l1.go = "Ortega_8";
		break;
		
		case "Ortega_8":
			DialogExit();
			LAi_SetImmortal(npchar, false);
			LAi_KillCharacter(npchar);
			AddQuestRecord("Saga", "20");
			pchar.questTemp.Saga = "svenson1";
			PlaySound("interface\important_item.wav");
			GiveItem2Character(pchar, "chest");
			GiveItem2Character(pchar, "bucher_ring"); //перстень Бучера
			//таймер на возврат смотрителя
			SetFunctionTimerCondition("Saga_LightmanReturn", 0, 0, 10, false);
			//ставим прерывания, если ГГ наследил в городе
			if (CheckAttribute(pchar, "questTemp.Saga.Trap"))
			{
				pchar.quest.Saga_Trap.win_condition.l1 = "location";
				pchar.quest.Saga_Trap.win_condition.l1.location = "Mayak11";
				pchar.quest.Saga_Trap.function = "Saga_CreateTrapBandos";
				CoolTraderHunterOnMap();
			}
			AddCharacterExpToSkill(pchar, "Sneak", 50);//скрытность
		break;
		
		//бандиты в поисках Гонсалеса, маяк
		case "saga_trap":
			dialog.text = "A-ah, there is our curious friend! Have you found Gonzales at last? Well done, you have brought us to him... we don't need you now. Lads, kill this jester!";
			link.l1 = "Time to die, crabs giblets!";
			link.l1.go = "saga_trap_1";
		break;
		
		case "saga_trap_1":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешить драться
			int n = makeint(MOD_SKILL_ENEMY_RATE/3);
			for (i=1; i<=3+n; i++)
			{	
				sld = characterFromId("sagatrap_sold_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "OpenTheDoors");
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		//<-- поиск Гонсалеса, Картахена
		
//--------------------------------------------НПС по квесту Возвращение барона---------------------------------
		
		// доминиканский вождь
		case "DominicaHead":
			dialog.text = "U-ah! U-ah! Great Kukulcan demands new victim! O-eh! Spirit of the mighty warrior of the past has come our village to be sacrificed to great Kukulcan! O-eh! All bow to mighty warrior spirit!";
			link.l1 = "(faintly) What the fuck, where am I?";
			link.l1.go = "DominicaHead_1";
			NextDiag.TempNode = "DominicaHead";
		break;
		
		case "DominicaHead_1":
			dialog.text = "O-eh! Great warrior wants be eaten by great Kukulcan! Sun rising, shadows shorten! Great Kukulcan soon alive! We bring you to him, oh mighty warrior, and you continue you pass through the land of ancestors!";
			link.l1 = "(faintly) Nonsense... Kukulcan again? Hey, chief, I came with peace! I am here to...";
			link.l1.go = "DominicaHead_2";
		break;
		
		case "DominicaHead_2":
			dialog.text = "O-eh! Great warrior says me that he wants to be sacrificed for Kukulcan immediately. Oh, great warrior! We go to Kukulcan now and wait his visit! Warriors! We have a great honor to take ancestor spirit to Kukulcan!";
			link.l1 = "(faintly) Idiot... Fine, I have to go with them. It's good that they didn't attack me at once, I wouldn't be able to defend myself in this thing...";
			link.l1.go = "DominicaHead_3";
		break;
		
		case "DominicaHead_3":
			DialogExit();
			LAi_SetActorType(pchar);
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocator(npchar, "reload", "reload1_back", "Saga_DominicaDollyReload", -1);
			LAi_ActorFollow(pchar, npchar, "", -1);
			for (i=2; i<=10; i++)
			{
				sld = characterFromId("Dominica_ind_"+i);
				LAi_SetActorType(sld);
				LAi_ActorFollow(sld, npchar, "", -1);
			}
		break;
		
		case "DominicaHead_4":
			dialog.text = "We come to Kukulcan, great ancestor spirit. Soon the sun go down, shadows grow and Kukulcan will visit us. Wait, great warrior...";
			link.l1 = "(faintly) Now I see, Indian war chief...";
			link.l1.go = "DominicaHead_5";
		break;
		
		case "DominicaHead_5":
			DialogExit();
			bDisableCharacterMenu = true;//лочим Ф2
			AddQuestRecord("BaronReturn", "7");
			LAi_SetActorType(pchar);
			DoQuestCheckDelay("Saga_DominicaDollyWait", 5.0);
			pchar.questTemp.Saga.BaronReturn = "third_teleport";
		break;
		
		case "DominicaHead_6":
			dialog.text = "Kukulcan alive! Kukulcan with us! Great warrior can be sacrificed for Kukulcan! Warriors, bow to great ancestor spirit!";
			link.l1 = "(faintly) Stay away, chief. I will do it myself. It's not my first time...";
			link.l1.go = "DominicaHead_7";
		break;
		
		case "DominicaHead_7":
			DialogExit();
			bDisableCharacterMenu = false;//разлочим Ф2
			AddQuestRecord("BaronReturn", "8");
			for (i=2; i<=10; i++)
			{
				sld = characterFromId("Dominica_ind_"+i);
				LAi_SetActorType(sld);
			}
		break;
		
//----------------------------------------НПС по квесту Искушение Барбазона----------------------------------
		// капитан рыболовного баркаса, стыривший шелк, море
		case "BarbCapBarkas":
			dialog.text = "How can I help you, mynheer?";
			link.l1 = "Well, well..  Now tell me, pal, what are you doing here?";
			link.l1.go = "BarbCapBarkas_1";
		break;
		
		case "BarbCapBarkas_1":
			dialog.text = "What am I doing? I am a fisherman and I am fishing here. And why the hell are you interrogating me in such a tone of voice?";
			link.l1 = "Don't lie to me, pal. Perhaps, you really are a fisherman, but you haven't been fishing the fish here. The valuable ship silk was thrown here, at this location. And your presence here looks quite suspicious to me.";
			link.l1.go = "BarbCapBarkas_2";
		break;
		
		case "BarbCapBarkas_2":
			dialog.text = "What a nonsense? What silk are you talking about?";
			link.l1 = "What silk? Chinese one... Don't play an idiot! Listen to me now: either you immediately get the silk of your cargo hold and give it to me or I will take it myself. But, first, my boarding party will deal with you and your people. So what? Should I call my men?";
			link.l1.go = "BarbCapBarkas_3";
		break;
		
		case "BarbCapBarkas_3":
			dialog.text = "No! Mynheer, how could I know... Those bales were just floating around so I've decided...";
			link.l1 = "Take the silk to my ship. Make haste!";
			link.l1.go = "BarbCapBarkas_4";
		break;
		
		case "BarbCapBarkas_4":
			dialog.text = "Yes, yes, sure. We will do that at once just don't take my boat!";
			link.l1 = "Move your ass! I don't have much time...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Saga_BarbBarkasSilk");
		break;
		
		case "BarbCapBarkas_5":
			dialog.text = "Here, we have brought everything we've found - all nine bales. That is all, I swear...";
			link.l1 = "Fine. You can continue your fishing, but don't have your eye on other peoples belongings in future!";
			link.l1.go = "BarbCapBarkas_6";
		break;
		
		case "BarbCapBarkas_6":
			DialogExit();
			npchar.DontDeskTalk = true;
			npchar.lifeday = 0;
			LAi_SetStayType(npchar);
			pchar.quest.BarbBarkas_Sink.over = "yes"; //снять прерывание
			pchar.quest.BarbBarkas_Abordage.over = "yes"; //снять прерывание
			NextDiag.CurrentNode = "BarbCapBarkas_7";
			AddQuestRecord("BarbTemptation", "6");
			pchar.questTemp.Saga.BarbTemptation = "give_silk";
			AddCharacterExpToSkill(pchar, "Fortune", 100);//везение
			AddCharacterExpToSkill(pchar, "Sneak", 50);//скрытность
		break;
		
		case "BarbCapBarkas_7":
			dialog.text = "You have already got what you wanted. I don't have anything left! What else do you need?";
			link.l1 = "Relax, pal. I am leaving.";
			link.l1.go = "exit";
			NextDiag.TempNode = "BarbCapBarkas_7";
		break;
		
		// Моррель, капитан потопленного судна, тюрьма
		case "Morelle":
			dialog.text = "If you are from Barbazon then tell him that I don't want to leave prison myself. I'd better wait for the trial. Even the Dutch hemp on my neck is better than his kindness.";
			link.l1 = "Don't break wind yet. Your navigator told Jaques that you are dead. He sent me to find the silk you've thrown away. How much of it was in your brigantine?";
			link.l1.go = "Morelle_1";
		break;
		
		case "Morelle_1":
			dialog.text = "My fault, damn it. The courier brought nine bales of silk for Barbazon. I ordered to track him down. He got noisy, so we had to cut his throat. He had extra three bales in his stash which I took for myself and hid in my own stash. It seems that we  had attracted an unwanted attention\nThey had found us fast and a Dutch patrol had been waiting 'Salt Dog' in the open sea. We failed to escape. You can take the silk for yourself if you won't tell Barbazon about me. The stash is located at Grand Case Beach between the stones close to the dead end. It's unlikely that I will need it again.";
			link.l1 = "Fine. I won't tell Barbazon that you are still alive. If they say true about him then you'd better be hanged by the Dutch. Perhaps you'd be lucky if they condemn you to penal servitude.";
			link.l1.go = "Morelle_2";
		break;
		
		case "Morelle_2":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			// тайник - модель
			//int m = Findlocation("Shore40");
			//locations[m].models.always.Roll = "Roll_of_rolls";
			//Locations[m].models.always.Roll.locator.group = "quest";
			//Locations[m].models.always.Roll.locator.name = "quest1";
			pchar.quest.Saga_MorelGoods.win_condition.l1 = "locator";
			pchar.quest.Saga_MorelGoods.win_condition.l1.location = "Shore40";
			pchar.quest.Saga_MorelGoods.win_condition.l1.locator_group = "quest";
			pchar.quest.Saga_MorelGoods.win_condition.l1.locator = "quest1";
			pchar.quest.Saga_MorelGoods.function = "Saga_SetMorelGoods";
			AddCharacterExpToSkill(pchar, "Fortune", 200);//везение
			AddCharacterExpToSkill(pchar, "Sneak", 200);//скрытность
		break;
		
		// Валет, брат Джекмана в Капстервиле
		case "valet":
			dialog.text = "I am waiting for the man who knows when the hunt for white shark will begin.";
			link.l1 = "The hunt has begun.";
			link.l1.go = "valet_1";
		break;
		
		case "valet_1":
			dialog.text = "Finally! Now listen carefully. You will have to visit Marcus Tyrex in La Vega and to tell him that brigantine 'Separator' was attacked near Turks island and now hiding at the Southern Bay. Her captain is heavenly wounded and the crew is waiting for help. You have picked up a sailor of 'Separator' and he told you all about it. He is dead now. That is all you know. Got it?";
			link.l1 = "And why do you need me for that? Waiting for too long...";
			link.l1.go = "valet_2";
		break;
		
		case "valet_2":
			dialog.text = "You are been paid to make you work not to ask questions. You are right though. I have to warn you that Tyrex won't let you go until he is sure that you are telling the truth. But once he finds everything out, he will pay you well. If he will be able to do that...";
			link.l1 = "You pull the wool over my eyes, mister... And why won't you take his thanks for yourself?";
			link.l1.go = "valet_3";
		break;
		
		case "valet_3":
			dialog.text = "Carramba! I don't like your curiosity! Your bubble talking will lead you to the grave one day.";
			link.l1 = "Yeah, sometimes I am being too unbearable. Especially when I see that someone is going to set me down. No, pal, now we will play on my rules. Who is your master, god damn it? Answer or I will make you to!";
			link.l1.go = "valet_4";
		break;
		
		case "valet_4":
			dialog.text = "You... bastard! Barbazon will pay for this and your life is going to end, shit eater!";
			link.l1 = "Ha! I have expected this. Get ready, scoundrel!";
			link.l1.go = "valet_5";
		break;
		
		case "valet_5":
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешить драться
			chrDisableReloadToLocation = true;//закрыть локацию
			DialogExit();
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "Saga_ValetDie");
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
		case "vensan":
			// Addon 2016-1 Jason пиратская линейка патч 17/1
			if (CheckAttribute(pchar, "questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "full_complete_end")
			{
				dialog.text = "Charley Prince? What are you doing here? A-argh, dammit, it was you! This is all your doing!";
				link.l1 = "Relax Bernie. I am on your side. The ambush is eliminated, you and your vessel are safe.";
				link.l1.go = "vensan_8";
			}
			else
			{
				dialog.text = "Who are you, damn it? How did you get here? Leave now, my ship is mined and bastards at the shore can blow it up in one shot.";
				link.l1 = "Don't worry, mister. The ambush at the shore was eliminated. Your ship is safe now as long as you are not going to light a pipe of course. What is your name?";
				link.l1.go = "vensan_1";
			}
		break;
		
		case "vensan_1":
			dialog.text = "Vincent. Bernard Vincent. And what's your name?";
			link.l1 = "Captain "+GetFullName(pchar)+". I will cut those ropes and set you free...";
			link.l1.go = "vensan_2";
		break;
		
		case "vensan_2":
			LAi_SetStayType(npchar);
			dialog.text = "Oh... Gratitude. How can I thank you?";
			link.l1 = "It is not over yet, mister. Is anyone from you crew still alive?";
			link.l1.go = "vensan_3";
		break;
		
		case "vensan_3":
			dialog.text = "Three dozen of my men are locked in the cargo hold...";
			link.l1 = "Release them and get away from here immediately. ";
			link.l1.go = "vensan_4";
		break;
		
		case "vensan_4":
			dialog.text = "But...";
			link.l1 = "Don't waste your time, Bernard. You can thank me later in La Vega... Tyrex might thank me as well.";
			link.l1.go = "vensan_5";
		break;
		
		case "vensan_5":
			dialog.text = "So aren't you here by accident? You knew everything?";
			link.l1 = "Yes, I knew. I managed to reveal Jackman's machination and plans to kill Marcus. Yes, and ask Tyrex to sit still, his meddling can frighten Jackman off.";
			link.l1.go = "vensan_6";
		break;
		
		case "vensan_6":
			dialog.text = "I will tell him for sure! Are you leaving now?";
			link.l1 = "Yes. And you hurry up too.";
			link.l1.go = "vensan_7";
		break;
		
		case "vensan_7":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "goto", "goto2", "none", "", "", "", 5.0);
			Ship_SetTaskRunaway(SECONDARY_TASK, GetCharacterIndex("Cap_Vensan"), GetMainCharacterIndex());
			pchar.questTemp.Saga.BarbTemptation.Vensan_free = "true";
			if (!CheckAttribute(pchar, "questTemp.Saga.BarbTemptation.vensan_attack"))
			{
				if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sld = characterFromId("Mary");
				else sld = characterFromId("Helena");
				sld.dialog.currentnode = "sea_bomb"; 
				LAi_SetActorType(sld);
				ChangeCharacterAddressGroup(sld, pchar.location, "goto", "goto6");
				LAi_ActorDialog(sld, pchar, "", -1, 0);
			}
			AddCharacterExpToSkill(pchar, "Leadership", 100);//авторитет
			AddCharacterExpToSkill(pchar, "Fortune", 100);//везение
			AddCharacterExpToSkill(pchar, "Sneak", 50);//скрытность
			sld = characterFromId("Cap_Vensan");
			sld.lifeday = 1;
			sld.DontDeskTalk = true;
		break;
		
		// Addon 2016-1 Jason пиратская линейка патч 17/1
		case "vensan_8":
			dialog.text = "Really? Look, I am sorry, brother...";
			link.l1 = "Forget it. Just let me cut the ropes and set you free.";
			link.l1.go = "vensan_9";
		break;
		
		case "vensan_9":
			LAi_SetStayType(npchar);
			dialog.text = "Fuck... I don't feel my hands...";
			link.l1 = "Bernie, are there more survivors on the ship?";
			link.l1.go = "vensan_10";
		break;
		
		case "vensan_10":
			dialog.text = "Thirty men are locked in the cargo hold...";
			link.l1 = "Release them and get the hell out of here. Now!";
			link.l1.go = "vensan_11";
		break;
		
		case "vensan_11":
			dialog.text = "But...";
			link.l1 = "You should set sail to La Vega immediately. Tell Marcus everything about this mess in full details.";
			link.l1.go = "vensan_12";
		break;
		
		case "vensan_12":
			dialog.text = "Did Marcus send you?";
			link.l1 = "He didn`t. I've managed to reveal one bastard`s plot. He planned to destroy Marcus with it. Ask him to stay aside from interfering at this moment... I will explain everything to him myself later. And please tell him to stop being mad at me.";
			link.l1.go = "vensan_7";
		break;
		
 //--------------------------------------НПС по Завещанию Шарпа--------------------------------------------------
		// Устрица, Поль Моллиган
		case "molligan":
			dialog.text = "What do you need on my ship, sir?";
			link.l1 = "Good day, Paul. Your name is Paul Molligan, right?";
			link.l1.go = "molligan_0";
		break;
		
		case "molligan_0":
			dialog.text = "Yes, it is me. How can I help you?";
			link.l1 = "My name is "+GetFullName(pchar)+" and Jan Swanson has sent me for you.";
			link.l1.go = "molligan_1";
		break;
		
		case "molligan_1":
			dialog.text = "Jan? A-ah, I remember you. Sure! You have been constantly visiting his house lately. So what does Jan want from me?";
			link.l1 = "You were in such a rush to sail away from Blueweld. Jan wanted to load you with extra two hundred centers of redwood to deliver it to lord Willoughby at Bridgetown. Get ready your vessel, my men will take redwood to your cargo hold.";
			link.l1.go = "molligan_2";
		break;
		
		case "molligan_2":
			dialog.text = "Redwood? Did Jan say that? Hm. And why won't you deliver it to Barbados? Why me?";
			link.l1 = "Because you are sailing there and I am not. I have got an immediate mission from Swanson, so I can't waste my time. Besides, Jan doesn't trust me to do business with lord Willoughby and he wants you to do that. I am sorry. Now let's do loading, I have to go.";
			link.l1.go = "molligan_3";
		break;
		
		case "molligan_3":
			dialog.text = "Listen, I don't have any free room in my cargo holds. I won't be able to do what Jan asks, though I'd like to do.";
			link.l1 = "No room? Strange... Jan told me that you had some free space.";
			link.l1.go = "molligan_4";
		break;
		
		case "molligan_4":
			dialog.text = "It is true, but Jan didn't know that I've equipped 'Oyster' with more heavy cannons. I can't load more cargo than I have already. So deliver the wood to Barbados yourself, hey pal? Tell Jan that I couldn't do that. Dealing with Willoughby is easy: just see him, give him the cargo and take your receipt. Easy enough.";
			link.l1 = "Hm. This wasn't my plan... Let's check your cargo hold, shall we? My quartermaster is a talent of packing stuff, he will be able to pack the goods and leave you some free space...";
			link.l1.go = "molligan_5";
		break;
		
		case "molligan_5":
			dialog.text = "Pal, I can't take more goods. Do you want me to throw away cannons and leave 'Oyster' unprotected?";
			link.l1 = "Fine. Well, if you are so flat... But Jan won't like it, consider that!";
			link.l1.go = "molligan_6";
		break;
		
		case "molligan_6":
			dialog.text = "I will explain it to Swanson, don't worry. After all, it is his fault, he didn't ask me about my ship's tonnage.";
			link.l1 = "Eh, and now I have to sail with those logs all way to Barbados, damn it... Farewell, pal.";
			link.l1.go = "molligan_7";
		break;
		
		case "molligan_7":
			DialogExit();
			// ставим проверку скрытности
			if (GetSummonSkillFromName(pchar, SKILL_SNEAK) > (10+drand(50)))
			{
				pchar.questTemp.Saga.Molligan.friend = "true"; // будет шанс критического залпа картечью
				sTemp = "Scoundrel is still unsuspicious. I should come closer and shoot at him with grapeshot. The sudden strike is always a win in any battle. ";
				log_Testinfo("Друзья");
				AddCharacterExpToSkill(pchar, "Fortune", 200);//везение
				AddCharacterExpToSkill(pchar, "Sneak", 300);//скрытность
			}
			else
			{
				pchar.questTemp.Saga.Molligan.enemy = "true"; // нападет
				sTemp = "";
				log_Testinfo("Враги");
				AddCharacterExpToSkill(pchar, "Sneak", 150);//скрытность
			}
			AddQuestRecord("Testament", "7");
			AddQuestUserData("Saga", "sText", sTemp);
			NextDiag.CurrentNode = "molligan_8";
			npchar.DontDeskTalk = true; // patch-5
		break;
		
		case "molligan_8":
			dialog.text = "We are clear, aren't we?";
			link.l1 = "Yes, yes. I am going to my ship.";
			link.l1.go = "exit";
			NextDiag.TempNode = "molligan_8";
		break;
		
	//-----------------------------------------НПС по Теням прошлого--------------------------------------------
		// Джим Бенсон, плешивая мэгги
		case "benson":
			dialog.text = "What do you want from me? I don't like gossips and gambling. And I drink rum alone. Besides, I am in a bad mood after last cruise.";
			link.l1 = "And what special has happened during your last cruise?";
			link.l1.go = "benson_1";
		break;
		
		case "benson_1":
			dialog.text = "One good man has trusted me and I thrown him overboard because my crew wanted that.";
			link.l1 = "And what was this fault?";
			link.l1.go = "benson_2";
		break;
		
		case "benson_2":
			dialog.text = "I am a newcomer and don't know many people here. That's why I hired that good-hearted fat man as a surgeon without knowing his past. The pirates were chasing us from Barbados. Why would they need my eggshell?\nWe barely managed to escape, thanks to the strong gale. Had a drink for such an occasion. And the old fool thought of nothing better than to tell everyone that they were most likely chasing him because he is a former executioner and knows things he is not supposed to know\nOf course, my crewmen got really angry. Really?! An executioner on board serving as a surgeon! And no one wants to mess with the pirates either... So I had to land the poor soul. It is all his fault, he had to keep his mouth shut. But I feel bad for bumpkin, an excellent physician. It took a minute for him to heal my hangover.";
			link.l1 = "Damn it! Your doctor's name was Raymond Baker, right?";
			link.l1.go = "benson_3";
		break;
		
		case "benson_3":
			dialog.text = "Yes. Exactly. And how do you know? Were you chasing me?";
			link.l1 = "No, not me. I just need that man, he is a great doctor. Where did you land him?";
			link.l1.go = "benson_4";
		break;
		
		case "benson_4":
			dialog.text = "Latitude 15 degrees 28' north, longitude 63 degrees 28' west. Hurry up, mister! He must be still alive and you will take a blame from me if you save him!";
			link.l1 = "I am rising my anchors already!";
			link.l1.go = "benson_5";
		break;
		
		case "benson_5":
			DialogExit();
			NextDiag.CurrentNode = "benson_6";
			AddQuestRecord("Shadows", "3");
			npchar.lifeday = 0;
			bQuestDisableMapEnter = false;
			pchar.quest.Saga_Shadows_Baker.win_condition.l1 = "location";
			pchar.quest.Saga_Shadows_Baker.win_condition.l1.location = "Dominica";
			pchar.quest.Saga_Shadows_Baker.function = "Saga_SetBakerBoat";
		break;
		
		case "benson_6":
			dialog.text = "Captain, hurry up! He must still be alive!";
			link.l1 = "Yes, yes, I am on my way...";
			link.l1.go = "exit";
			NextDiag.TempNode = "benson_6";
		break;
		
	//---------------------------------------бандиты у джекмановского рудника-------------------------------
		case "mine_bandit":
			if (CheckAttribute(pchar, "questTemp.Saga.MineAttack"))
			{
				dialog.text = "Hey! Stay right there! Don't move. This territory is secured!";
				link.l1 = "Don't be too harsh, pal! Friends! Jackman sent us. We need to get to the mine. Master's order...";
				link.l1.go = "mine_attack";
				break;
			}
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "Hey! Stay right there! Don't move. This territory is secured!";
				link.l1 = "Hm. But I want to go through... Why the hell are you stopping me?";
				link.l1.go = "mine_bandit_1";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "A-ah, you again? I see that you didn't get it... Lads, fire!!";
				link.l1 = "...";
				link.l1.go = "mine_bandit_fire";
			}
		break;
		
		case "mine_bandit_0":
			dialog.text = "Come on, move along!";
			link.l1 = "Fine...";
			link.l1.go = "exit";
			NextDiag.TempNode = "mine_bandit_0";
		break;
		
		case "mine_bandit_1":
			dialog.text = "Because the mine behind me is a private property and I am here to stop any stranger like you. You'd better turn around and leave this place, stranger. Our cannons are loaded with grapeshot, just a step and you'll turn into a wet puddle.";
			link.l1 = "Heh, I see. Your mine got a serious guard. Fine, I am leaving.";
			link.l1.go = "mine_bandit_exit";
			link.l2 = "You, bastard! Well, we will see who will become a puddle!";
			link.l2.go = "mine_bandit_2";
		break;
		
		case "mine_bandit_exit":
			DialogExit();
			LAi_SetGuardianType(npchar);
			LAi_group_MoveCharacter(npchar, "PIRATE_CITIZENS");
			chrDisableReloadToLocation = false;//открыть локацию
			DoQuestReloadToLocation("Mine_02", "reload", "reload3", "");
		break;
		
		case "mine_bandit_2":
			dialog.text = "It was your choice... Lads, fire!!";
			link.l1 = "...";
			link.l1.go = "mine_bandit_fire";
		break;
		
		case "mine_bandit_fire":
			DialogExit();
			DoQuestCheckDelay("Saga_MineBanditsFire", 1.5);
		break;
		
		case "mine_banditx":
			if (CheckAttribute(pchar, "questTemp.Saga.MineAttack"))
			{
				dialog.text = "Hey! Go away! This territory is secured!";
				link.l1 = "Hey, relax, pal! Jackman sent us. We need to get to the mine. Master's order...";
				link.l1.go = "mine_attackx";
				break;
			}
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "Hey! Go away! This territory is secured!";
				link.l1 = "Hm. And what is there?";
				link.l1.go = "mine_banditx_1";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "A-ah, you again? I see that you didn't get it... Lads, fire!!";
				link.l1 = "...";
				link.l1.go = "mine_banditx_fire";
			}
		break;
		
		case "mine_banditx_1":
			dialog.text = "None of your business. Get lost or we will shoot you where you stand, I swear!";
			link.l1 = "Calm down. I am leaving.";
			link.l1.go = "mine_banditx_exit";
			link.l2 = "You, bastard! Well, we will see who will shoot who!";
			link.l2.go = "mine_banditx_2";
		break;
		
		case "mine_banditx_exit":
			DialogExit();
			LAi_SetGuardianType(npchar);
			LAi_group_MoveCharacter(npchar, "PIRATE_CITIZENS");
			DoQuestReloadToLocation("Mine_04", "reload", "reload3", "");
		break;
		
		case "mine_banditx_2":
			dialog.text = "It is your choice... Muskets ready! Fire!!";
			link.l1 = "...";
			link.l1.go = "mine_banditx_fire";
		break;
		
		case "mine_banditx_fire":
			DialogExit();
			DoQuestCheckDelay("Saga_MineBanditsxFire", 0.6);
		break;
		
		case "mine_attackx":
			dialog.text = "Really? You must know the password then. Speak it, but you will regret if you are lying...";
			link.l1.edit = 5;
			link.l1 = "";
			link.l1.go = "mine_attackx_1";
		break;
		
		case "mine_attackx_1":
			sTemp = GetStrSmallRegister(dialogEditStrings[5]);
			if (sTemp == "neptune")
			{
				dialog.text = "Correct. But you, pal, has come from the wrong side. Didn't they warn you? Go back and take left from the dry well. Move around the hill and you will get to the main entrance.";
				link.l1 = "And can't I enter here?";
				link.l1.go = "mine_attackx_2";
			}
			else
			{
				dialog.text = "Guys, there is a sleuth! Muskets ready! Fire!!";
				link.l1 = "...";
				link.l1.go = "mine_banditx_fire";
			}
		break;
		
		case "mine_attackx_2":
			dialog.text = "No. Only through the central entrance.";
			link.l1 = "All right, pal... Hey! Look! What the fuck is at the top of the palisade?";
			link.l1.go = "mine_attackx_3";
		break;
		
		case "mine_attackx_3":
			DialogExit();
			for (i=1; i<=4; i++)
			{
				sld = characterFromId("Mine_banditx_"+i);
				LAi_RemoveCheckMinHP(sld);
			}
			sld = characterFromId("Svensons_sold_12");
			LAi_SetActorType(sld);
			LAi_ActorTurnToLocator(sld, "soldiers", "soldier1");
			LAi_ActorAnimation(sld, "shot", "Saga_MineBanditxDie", 1.0);
		break;
		
		case "mine_attack":
			dialog.text = "Really? You should know the password then. Speak it loud and clear to make me hear it. And if you try to fool me, that will be the last joke in your life.";
			link.l1.edit = 5;
			link.l1 = "";
			link.l1.go = "mine_attack_1";
		break;
		
		case "mine_attack_1":
			sTemp = GetStrSmallRegister(dialogEditStrings[5]);
			if (sTemp == "neptune")
			{
				dialog.text = "Correct. Move along. The head of the camp is at the house left to the entrance of mine. Come and see him.";
				link.l1 = "Fine, pal...";
				link.l1.go = "mine_attack_2";
			}
			else
			{
				dialog.text = "Guys, there is a sleuth! Cannons, open fire!!";
				link.l1 = "...";
				link.l1.go = "mine_bandit_fire";
			}
		break;
		
		case "mine_attack_2":
			DialogExit();
			NextDiag.CurrentNode = "mine_attack_3";
			LAi_SetActorType(pchar);
			LAi_ActorFollow(pchar, npchar, "ActorDialog_Any2Pchar", -1);
			LAi_ActorTurnToCharacter(npchar, pchar);
			SetActorDialogAny2Pchar(npchar.id, "", 0.0, 0.0);
		break;
		
		case "mine_attack_3":
			dialog.text = "What else? Did you forget anything?";
			link.l1 = "Yes. I was asked to give you best regards.";
			link.l1.go = "mine_attack_4";
		break;
		
		case "mine_attack_4":
			dialog.text = "Me? Ha-ha! And who asked?";
			link.l1 = "Jan Swanson, you bastard!";
			link.l1.go = "mine_attack_5";
		break;
		
		case "mine_attack_5":
			DialogExit();
			LAi_SetPlayerType(pchar);
			for (i=1; i<=6; i++)
			{
				sld = characterFromId("Mine_bandit_"+i);
				LAi_RemoveCheckMinHP(sld);
			}
			if (pchar.questTemp.Saga.MineAttack == "soldiers")
			{
				sld = characterFromId("Svensons_sold_12");
				LAi_SetActorType(sld);
				LAi_ActorTurnToLocator(sld, "soldiers", "soldier1");
				LAi_ActorAnimation(sld, "shot", "Saga_MineBanditDie", 1.0);
			}
			else
			{
				for (i=1; i<=6; i++)
				{
					sld = characterFromId("Mine_bandit_"+i);
					LAi_SetWarriorType(sld);
					LAi_group_MoveCharacter(sld, "EnemyFight");
				}
				LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
				LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
				LAi_group_SetCheck("EnemyFight", "Saga_BanditsDestroyed");
				AddDialogExitQuest("MainHeroFightModeOn");	
			}
			pchar.quest.Saga_MineAttack_07.win_condition.l1 = "NPC_Death";
			pchar.quest.Saga_MineAttack_07.win_condition.l1.character = "Mine_bandit_1";
			pchar.quest.Saga_MineAttack_07.win_condition.l2 = "NPC_Death";
			pchar.quest.Saga_MineAttack_07.win_condition.l2.character = "Mine_bandit_2";
			pchar.quest.Saga_MineAttack_07.function = "Saga_SvensonMineexitAttack";
		break;
		
	// ----------------------------- диалоги НПС при штурме бандитского рудника -------------------------------
		case "Svensons_off":
			dialog.text = LinkRandPhrase("We will tear those bastards!","I am looking forward to beat those scums!","Jackman's minions have nothing to do at the Western Main! We will beat them of here!");
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "Svensons_off";
		break;
		
		case "Svensons_sold":
			dialog.text = LinkRandPhrase("We are ready to fight!","We'll show them!","They don't even know who are they messing with!");
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "Svensons_sold";
		break;
		
		case "gunner":
			PlaySound("Voice\russian\evilpirates01.wav");
			dialog.text = "Commander, the cannon is ready. It was loaded with a bomb just like you've ordered.";
			link.l1 = "I take it that no one is expecting us here... Time to introduce ourselves. Jan told me that their camp is behind this hill. Will you be able to shoot it?";
			link.l1.go = "gunner_0_1";
		break;
		
		case "gunner_0_1":
			dialog.text = "Easy enough, commander. Let's rise the barrel a bit, that should do... done\nGet ready!.. Fire!!";
			link.l1 = "...";
			link.l1.go = "gunner_0_2";
			npchar.quest.canonada = "1";
		break;
		
		case "gunner_0_2":
			DialogExit();
			LAi_SetActorType(pchar);
			DoQuestCheckDelay("Saga_Gunfire", 3.0);
			LAi_ActorTurnToLocator(npchar, "goto", "goto14");
		break;
		
		case "gunner_1":
			dialog.text = "";
			link.l1 = "Hm. Randolf, think we hit something? I'd like to hear your opinion.";
			link.l1.go = "gunner_1_1";
		break;
		
		case "gunner_1_1":
			PlaySound("interface\_bombs_npc.wav");
			dialog.text = "Commander, we did hit something or someone, but I can't be more specific… this blasted hill is blocking the sight. I'll change the angle\nReady! Fire!";
			link.l1 = "...";
			link.l1.go = "gunner_0_2";
			npchar.quest.canonada = "2";
		break;
		
		case "gunner_2":
			PlaySound("interface\abordage_wining.wav");
			PlaySound("types\warrior03.wav");
			dialog.text = "Ha! Look, commander! There is a smoke! Damn, we must have hit some bandit barn! Hurrah-ah!";
			link.l1 = "Yes, I see the smoke... An epic victory already, no doubt. Reload the gun and point it at the path, it smells like our guests are coming. We will greet them in an appropriate way!";
			link.l1.go = "gunner_2_1";
		break;
		
		case "gunner_2_1":
			PlaySound("interface\_bombs_npc.wav");
			dialog.text = "Aye-aye, commander! Load a bomb! Gun crew at the ready! Fuse ready! Fire at my command!";
			link.l1 = "...";
			link.l1.go = "gunner_2_2";
			npchar.quest.canonada = "3";
		break;
		
		case "gunner_2_2":
			DialogExit();
			LAi_SetActorType(pchar);
			DoQuestCheckDelay("Saga_LoginBandos_01", 6.0);
			LAi_ActorTurnToLocator(pchar, "goto", "goto14");
			LAi_ActorTurnToLocator(npchar, "goto", "goto14");
		break;
		
		case "gunner_3":
			PlaySound("interface\abordage_wining.wav");
			PlaySound("types\warrior03.wav");
			PlaySound("Voice\russian\evilpirates05.wav");
			dialog.text = "Ha-ha, they've got it!";
			link.l1 = "Don't relax yet! Load the gun! I don't think that they had enough. They are coming!";
			link.l1.go = "gunner_3_1";
		break;
		
		case "gunner_3_1":
			PlaySound("interface\_bombs_npc.wav");//
			dialog.text = "Aye-aye, commander! Load a bomb! Ready! Fire at my command!";
			link.l1 = "...";
			link.l1.go = "gunner_3_2";
			npchar.quest.canonada = "4";
		break;
		
		case "gunner_3_2":
			DialogExit();
			LAi_SetActorType(pchar);
			DoQuestCheckDelay("Saga_LoginBandos_02", 5.0);
			LAi_ActorTurnToLocator(pchar, "goto", "goto14");
			LAi_ActorTurnToLocator(npchar, "goto", "goto14");
		break;
		
		case "gunner_5":
			PlaySound("types\warrior04.wav");
			PlaySound("Voice\russian\evilpirates06.wav");
			dialog.text = "Ha-ha-ha, bastards have shown us their back! Dog's meat! Grapeshot is crushing within such distance! It looks like they are not so brave to attack us now!";
			link.l1 = "Now it is our turn. Randolph, you will stay near the cannon. Shoot a few times at the path and then aim at the smoke - burn their lair! Just don't shoot us.";
			link.l1.go = "gunner_5_1";
		break;
		
		case "gunner_5_1":
			PlaySound("interface\_bombs_npc.wav");
			dialog.text = "Aye-aye, commander! Get the cannon ready! Load a bomb!";
			link.l1 = "Men! To arms! Follow me, attack! Hurrah!!";
			link.l1.go = "attack";
		break;
		
		case "attack":
			DialogExit();
			n = Findlocation("mine");
			Locations[n].hidden_fire = true;
			PlaySound("interface\abordage_wining.wav");
			PlaySound("interface\abordage_wining.wav");
			LAi_ActorTurnToLocator(npchar, "goto", "goto14");
			LAi_group_MoveCharacter(npchar, "TMP_FRIEND");
			if (GetCharacterIndex("Svensons_sold_12") != -1 && pchar.questTemp.Saga.MineAttack == "soldiers")
			{
				sld = characterFromId("Svensons_sold_12");
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			}
			for (i=1; i<=8; i++)
			{
				if (GetCharacterIndex("Ourmine_sold_"+i) != -1)
				{
					sld = characterFromId("Ourmine_sold_"+i);
					if (i == 1) sld.MusketerDistance = 10; 
					LAi_SetWarriorType(sld);
					LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
				}
			}
			LAi_group_SetRelation("EnemyFight", "TMP_FRIEND", LAI_GROUP_NEITRAL);
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "Saga_MineBandos_05Die");
			AddDialogExitQuest("MainHeroFightModeOn");	
			DoQuestCheckDelay("Saga_MineSetMusic", 0.3);
			// запускаем автобабахалку на 10 выстрелов
			iTotalTemp = 0;
			DoQuestCheckDelay("Saga_GunAutoFire", 7.0);
			bDisableCharacterMenu = false;//разлочим интерфейсы
			InterfaceStates.Buttons.Save.enable = true;//разрешим сохраняться
		break;
		
		case "convict":
			if (LAi_grp_playeralarm > 0)
			{
				dialog.text = LinkRandPhrase("Don't hurt me, I am not one of them! Kill the bandits!","Free us, pal! Kill them all!","Cut them, friend, cut! Make them dead!");
				link.l1 = "Ha! Don't worry, that is what we are doing now.";
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = LinkRandPhrase("Is slavery over? Will you free us?","Heh, have I really lived until this day?","Bastards have drained all blood from us....");
				link.l1 = "I think that you will be able to enjoy your freedom soon, pal...";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "convict";
		break;
		
		// жена Яна Свенсона
		case "js_girl":
			if (LAi_grp_playeralarm > 0)
			{
				dialog.text = "You'd better leave this place, sir. We don't cover criminals and we don't need conflicts with authorities of the colony.";
				link.l1 = "Fine, I am leaving...";
				link.l1.go = "exit";
				NextDiag.TempNode = "js_girl";
				break;
			}
			if(NPChar.quest.meeting == "0")
			{
				dialog.text = TimeGreeting()+", sir. Do you want to see Jan?";
				link.l1 = "Good day. It was nice to meet you, miss?..";
				link.l1.go = "js_girl_1";
			}
			else
			{
				if (CheckAttribute(pchar, "questTemp.Saga") && pchar.questTemp.Saga == "blueveld")
				{
					dialog.text = TimeGreeting()+", captain "+GetFullName(pchar)+". If you are here for Jan then I have to disappoint you - he is not here. He is off because of some important business.";
					link.l1 = "Damn it! And I need him! Tell me, missis. Swanson, did he tell you when he is going to be back?";
					link.l1.go = "js_girl_3";
					break;
				}
				dialog.text = "A-ah, you again, captain "+GetFullName(pchar)+"... Move along, Jan is upstairs, as usual.";
				link.l1 = "Thank you, missis Swanson...";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "js_girl";
		break;
		
		case "js_girl_1":
			dialog.text = "Missis. Missis Johanna Swanson.";
			link.l1 = "Captain "+GetFullName(pchar)+".";
			link.l1.go = "js_girl_2";
		break;
		
		case "js_girl_2":
			if (CheckAttribute(pchar, "questTemp.Saga") && pchar.questTemp.Saga == "blueveld")
			{
				dialog.text = "Captain? Well, I am glad to welcome you in my house. But if you are here for Jan then I have to disappoint you - he is not here. He is off because of some important business.";
				link.l1 = "Damn it! And I need him! Tell me, missis Swanson, did he tell you when he is going to be back?";
				link.l1.go = "js_girl_3";
				break;
			}
			dialog.text = "Captain? Well, I am glad to welcome you in my house. My husband is on the second floor in his office. Go upstairs.";
			link.l1 = "I got it, missis Swanson...";
			link.l1.go = "exit";
			NPChar.quest.meeting = "1";
			NextDiag.TempNode = "js_girl";
		break;
		
		case "js_girl_3":
			dialog.text = "No. He didn't even tell me the exact date of return, because he doesn't himself know how long the search will last.";
			link.l1 = "I am sorry to interfere but I really need him... What searches is he up for?";
			link.l1.go = "js_girl_4";
		break;
		
		case "js_girl_4":
			dialog.text = "Sure, I'll tell you. His favorite Helen also known as Rumba, a daughter of his late old friend Sean McArthur, has disappeared. Jan treats the young devil as his own daughter. She reminds him of his old love, she had the same reckless temper, that is the reason of such attraction I believe.\nSo the girl disappeared a week ago along with her schooner 'Rainbow' and the whole crew. Sean McArthur taught her seamanship and 'Rainbow' was left to her by his will. And now she plays being a captain...";
			link.l1 = "What could have happened to her?";
			link.l1.go = "js_girl_5";
		break;
		
		case "js_girl_5":
			dialog.text = "Who knows... A week is not that long, but McAthur's widow is confident that something wrong happened with her daughter and she managed to convince Jan in that. He raised his men and started searching by himself with no result yet. Personally, I think that Helen is fine and Jan is just torturing himself for no reason\nListened too much of that old fat woman's nonsense and sounded an alarm. The girl is most likely having fun now with another boyfriend away from people's eyes at the safe place. She will come back as soon as her hunger is sated.";
			link.l1 = "Johanna, where can I find Gladys? I want to talk with her...";
			link.l1.go = "js_girl_6";
		break;
		
		case "js_girl_6":
			dialog.text = "Her house is near the pier on the left. But she is likely not there. She spends everyday standing on the walls of fort looking for her precious daughter.";
			link.l1 = "I see. Thanks a lot for your information!";
			link.l1.go = "js_girl_7";
		break;
		
		case "js_girl_7":
			DialogExit();
			NextDiag.CurrentNode = "js_girl_8";
			sld = characterFromId("Gladis"); //устанавливаем Глэдис на форт
			ChangeCharacterAddressGroup(sld, "SantaCatalina_fort", "goto", "goto53");
			LAi_SetStayType(sld);
			sld.dialog.currentnode = "FindHelena";
			pchar.questTemp.Saga = "gladis";
		break;
		
		case "js_girl_8":
			dialog.text = "Jan is not here yet, captain, so come back later.";
			link.l1 = "I see...";
			link.l1.go = "exit";
			NextDiag.TempNode = "js_girl_8";
		break;
		
		// хронометр Алекса
		case "Alexs_bandos":
			dialog.text = "Hey! What are you doing here?";
			link.l1 = "I'd like to ask you the same - what you and your pals are doing here, in my dungeon?";
			link.l1.go = "Alexs_bandos_1";
		break;
		
		case "Alexs_bandos_1":
			dialog.text = "Ha! Your dungeon? And since when did it become yours, fag?";
			link.l1 = "Since the day your father made a mistake with your mother.";
			link.l1.go = "Alexs_bandos_2";
		break;
		
		case "Alexs_bandos_2":
			dialog.text = "Are you looking for troubles?";
			link.l1 = "Listen, pal, I give you one last chance to leave this place. This is my dungeon and I won't let anyone to walk here, got it? I need just to whistle once, and half of pirates of Isla Tesoro will be here a minute later.";
			link.l1.go = "Alexs_bandos_3";
		break;
		
		case "Alexs_bandos_3":
			dialog.text = "Well, we'll try to shut your mouth then!";
			link.l1 = "Ha-ha! You are pathetic, scum!";
			link.l1.go = "Alexs_bandos_4";
		break;
		
		case "Alexs_bandos_4":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation("Bermudes_Dungeon")], false);
			for (i=1; i<=4; i++)
			{
				sld = characterFromId("Alexs_bandos_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			int iRank = sti(pchar.rank)+MOD_SKILL_ENEMY_RATE+5;
			int iScl = 25+2*sti(pchar.rank);
			sld = GetCharacter(NPC_GenerateCharacter("Alexs_bandos_5", "mush_ctz_8", "man", "mushketer", iRank, PIRATE, -1, false, "soldier"));
			FantomMakeCoolFighter(sld, iRank, iScl, iScl, "", "mushket1", "cartridge", iScl*2+50);
			ChangeCharacterAddressGroup(sld, "Bermudes_Dungeon", "monsters", "monster8");
			LAi_group_MoveCharacter(sld, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "AlexClock_BandosDie");
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
	}
}