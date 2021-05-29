// Мэри Каспер - взаимная любовь и офицер
void ProcessDialogEvent()
{
	ref NPChar, sld, rItm, rItem;
	aref Link, NextDiag, rType;
	int i;
	int iTime, iAddTime;
	string 	sTemp, sAttr, sGun, sBullet, attrL;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	sAttr = Dialog.CurrentNode;
	if (findsubstr(sAttr, "SetGunBullets1_" , 0) != -1)
 	{
        i = findsubstr(sAttr, "_" , 0);
	 	NPChar.SetGunBullets = strcut(sAttr, i + 1, strlen(sAttr) - 1); // индекс в конце
 	    Dialog.CurrentNode = "SetGunBullets2";
 	}
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "Want something?";
			link.l1 = "No, it's nothing.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
	// ---------------------------------покушение на Акулу - вариант R --------------------------------
		// разговор в каюте Адольфа
		case "Cabin":
			dialog.text = "Marcello, I know him. He is a friend of Rivados and the pirates. Adolf would never work with him. Smell the air... do you feel a sense of gun powder? And there is blood on the wall... He has killed Adolf and now trying to fool us! He must be working for the admiral! Kill him!";
			link.l1 = "...";
			link.l1.go = "Cabin_fight";
		break;
		
		case "Cabin_fight":
			chrDisableReloadToLocation = true;//закрыть локацию
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешить драться
			DialogExit();
			sld = characterFromId("Marchello");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			if (CheckAttribute(pchar, "questTemp.Saga.SharkHunt.TownAttack"))
			{
				for (i=1; i<=3; i++)
				{
					sld = characterFromId("CyclopGuard_"+i);
					LAi_SetWarriorType(sld);
					LAi_group_MoveCharacter(sld, "EnemyFight");
				}
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "LSC_CyclopNMaryDie");
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
		// на улице
		case "Town":
			dialog.text = "Oh, excuse me... Can I ask you to help me?";
			link.l1 = "Hm. I am always ready to help such a pretty lady. What's the problem?";
			link.l1.go = "Town_1";
		break;
		
		case "Town_1":
			dialog.text = "See, I bought a chest filled with all kinds of metal pieces from Sessile Gallard. She lives on the 'Eva'. Jurgen promised to forge a good thing for me, alright... I bought it, yes, but I can't bring it to him. So foolish of me!\nPerhaps you could help me to carry the chest from 'Eva' to Narwhal's block post on 'Esmeralda'? Please, I'd be very grateful!";
			link.l1 = "And that's it? Sure, miss, I will help you. Not much of a trouble.";
			link.l1.go = "Town_2";
		break;
		
		case "Town_2":
			dialog.text = "Thank you! Follow me and I will show you the chest.";
			link.l1 = "Sure...";
			link.l1.go = "Town_3";
		break;
		
		case "Town_3":
			DialogExit();
			LAi_SetActorType(pchar);
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocator(npchar, "reload", "reload41", "LSC_EnterAevaWithMary", -1);
			LAi_ActorFollow(pchar, npchar, "", -1);
		break;
		
		case "Town_4":
			dialog.text = "And here we are... Now tell me, bastard, where is the key?!";
			link.l1 = "Wow! Ha, it seems that no help is needed... Mary.";
			link.l1.go = "Town_5";
		break;
		
		case "Town_5":
			dialog.text = "Smart boy, huh? Less talking, damn you! Where is the key? Give it or you will regret!";
			link.l1 = "So rude! Such a bad tongue of such a beautiful girl. What kind of a key?";
			link.l1.go = "Town_6";
		break;
		
		case "Town_6":
			dialog.text = "The key which you have taken from Adolf Barbier. And don't try to deny that - You have seen leaving his cabin. Adolf is dead and it was your work... Now, give me the key!";
			link.l1 = "So it was you after all... That was a mistake, girl, a very big mistake!";
			link.l1.go = "Town_7";
		break;
		
		case "Town_7":
			PlaySound("VOICE\Russian\LSC\Mary Casper-04.wav");
			dialog.text = "What did you say?... Damn it, you are not an ordinary robber! He is working for the admiral! Take him down, lads!";
			link.l1 = "...";
			link.l1.go = "Cabin_fight";
		break;
		
	// ---------------------------------покушение на Акулу - вариант N --------------------------------
		case "caroline":
			dialog.text = "Chad, that's him! Damn it, he has taken a helper here! Lads, kill them all!";
			link.l1 = "...";
			link.l1.go = "caroline_1";
		break;
		
		case "caroline_1":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешить драться
			// Акулу к бою
			sld = characterFromId("Dodson");
			LAi_SetImmortal(sld, false);
			LAi_SetWarriorType(sld);
			sld.cirassId = Items_FindItemIdx("cirass1");
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			// устанавливаем 4 толстых нарвалов
			int iRank = 20+MOD_SKILL_ENEMY_RATE*2;
			int iScl = 65;
			for (i=1; i<=4; i++)
			{
				sld = GetCharacter(NPC_GenerateCharacter("MaryGuard_"+i, "citiz_5"+(i+4), "man", "man", iRank, PIRATE, -1, true, "soldier"));
				FantomMakeCoolFighter(sld, iRank, iScl, iScl, "blade_19", "pistol5", "bullet", iScl*2);
				if (i < 3) ChangeCharacterAddressGroup(sld, "CarolineBank", "reload", "reload3");
				else ChangeCharacterAddressGroup(sld, "CarolineBank", "reload", "reload2");
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			// Мэри и Чада к бою
			sld = characterFromId("Capper");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "LSC_MarynChadDie");
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
	// ---------------------------------покушение на Акулу - вариант M --------------------------------
		case "mary":
			dialog.text = "You are just in time... I would have never dealt with them myself... Fuh! To be honest, I thought that I am done!";
			link.l1 = "You were fighting well. I have never seen such a beautiful girl with such skills in fencing...";
			link.l1.go = "mary_1";
		break;
		
		case "mary_1":
			dialog.text = "Ha-ha, you are a gentleman, aren't you: making compliments with a sword still in your hand. Thanks for your help. You have saved my life, alright! Introduce yourself, gentleman, I have never seen you before. Are you new here?";
			link.l1 = "My name is "+GetFullName(pchar)+", but beautiful ladies can call me "+pchar.name+". . Am I new here? Hm... I am.";
			link.l1.go = "mary_2";
		break;
		
		case "mary_2":
			dialog.text = "This is obvious because I would have noticed such handsome man immediately. My name is Mary, Mary Casper though they call me Red Mary. That is because I am a redhead, alright.";
			link.l1 = "I am glad to meet you, Mary...";
			link.l1.go = "mary_3";
		break;
		
		case "mary_3":
			dialog.text = "Oh, you can't imagine how I am glad... considering that I was almost dead a minute ago. This bastard Chad wasn't bluffing. Such a vermin! And I was a fool to leave bottom doors opened. You've used them to get inside, right?";
			link.l1 = "Yes. I was swimming around the island looking for a place to get up.";
			link.l1.go = "mary_4";
		break;
		
		case "mary_4":
			dialog.text = "True-true. This unlocked door almost had me killed. Jurgen himself forged the locks for me, you can't open them without a right key and lock picking won't help. Besides, I won't stay idle while someone is trying to get inside - four barrels of my pistol mean four holes on a door or a body, ha-ha!\nBut damned Chad won't leave me alone. He had already sent cutthroats to 'persuade' me to take his side, he is definitely serious about it. If it wasn't for you, I would have said yes. I'll have to stay here under the siege, "+pchar.name+", alright! Thank God I have predicted that, I have enough supplies and Jurgen is my neighbour, I didn't quarrel with him.";
			link.l1 = "Mary, why won't you tell me more about your problems? I see that you need my help, but I didn't understand a thing from your words.";
			link.l1.go = "mary_5";
		break;
		
		case "mary_5":
			dialog.text = "Sure, I need help, alright! I am alone now. I had a fight with Donald, Chad turned out to be a villain. Oh, I am sorry, I am bubbling again. Fine, I will tell you about the situation I've found myself in...";
			link.l1 = "Know that I am new here, so I don't understand much yet. Who is that Chad trying to 'persuade' or to kill you? Who is Donald?";
			link.l1.go = "mary_6";
		break;
		
		case "mary_6":
			dialog.text = "Chad is a pirate from admiral's Shark Dodson crew, a jailer of 'Tartarus'...";
			link.l1 = "Wait! What did you say? Shark Dodson? Is he here?";
			link.l1.go = "mary_7";
		break;
		
		case "mary_7":
			dialog.text = "You must have reached this place this night since you don't already know that. Where else Shark would be but here? My troubles began when he arrived here several months ago. Though, I admit, this is all Narwhals' and Rivados' fault. When Shark came here with his crew, he wanted to establish a base, but our people and Rivados really disliked the idea. They attacked Shark's brig at night and set it on fire\nThey better didn't! Shark's crew is full of devils not men, alright. First, they destroyed hostile boats, then landed and started a real slaughter. Narwhals retreated and Rivados run away as fast as they could. Finally, pirates captured San Augustine where the most of Island's provision supplies are held, then they took Tartarus\nShark imprisoned our leader Alan Milrow, who also was my... my close friend, and Rivados wizard Chimiset. He sent them to rot in Tartarus's cages like beasts. It's easy to swim to Tartarus from here and I managed to visit Alan a few times. There I met Chad Kapper, Shark made him a jailer. I asked Chad to release Alan, promised him money, but he was afraid to confront admiral\nAnd then Alan was murdered right in the prison. Chad told me that Shark did this, alright. So I went to Donald, who was elected as a leader in place of Alan, and demanded from him to attack the pirates immediately, yet he refused, said that those sea devils are too tough for us. That was when I told him to fuck himself\nMy people were worthless in this matter, so I made a deal with Kapper, the scum wanted to take Shark's place. We had a plan - to lure admiral from his fortress to some shady place and kill him there. We also found a sniper with a good rifle, he could shoot admiral from the Fury's mast\nNow the interesting part comes, the day before yesterday I visited Tartarus at night, wanted to say something important to Chad concerning our plan. Swam to the boat and accidentally overheard Chad talking with two Narwhals. Turned out that Shark didn't kill Alan. Chad did and then secretly spread gossips about admiral's involvement\nHe murdered him because of me. First, he wanted to make me his plaything in a bed. Second, he wanted to use me in order to get rid of Shark - he knew that I would always seek vengeance. Just think about it, such a bastard!";
			link.l1 = "Yeah, I know that type...";
			link.l1.go = "mary_8";
		break;
		
		case "mary_8":
			dialog.text = "Fucker is even worse! He... I am lacking in words to describe that nonentity! I went away that time, I found him next morning and told him everything I think of him. Sure, I denied participating in killing admiral.";
			link.l1 = "And he didn't like it, that's for sure... That was hasty, Mary. You must be more cunning.";
			link.l1.go = "mary_9";
		break;
		
		case "mary_9":
			dialog.text = "I can't. And I couldn't keep my mouth shut either. The bastard killed Alan and tried to use me in order to achieve his dirty goals! Scum! Yes, sure, he got angry and promised that I would regret that. I told him that was yet unknown who would regret.\nHe threatened that he would send his Narwhal buddies for me if I didn't change my mind. I laughed, I thought that no Narwhal would dare to raise a hand on me.";
			link.l1 = "It seems that you were mistaken about them.";
			link.l1.go = "mary_10";
		break;
		
		case "mary_10":
			dialog.text = "Yeah, "+pchar.name+", I have underestimated Chad and overestimated myself. He found heroes brave enough to attack the lone girl at her own cabin together. And what should I do now? I can't trust anyone. I can't trust even my own people. These two are Narwhals, I knew both of them, alright. While Chad is alive - I am in danger, he will send more, no doubt\nI am scared to walk out, the sniper we found to assassinate Shark may shoot me from Rivados territory and disappear easily. I won't go to Donald, he will not listen\nAdmiral? And how am I supposed to explain my role in preparations of his assassination? He will send me to rot inside 'Tartarus', I am sure! Fuck, I am trapped. I am going to sit here with my guns ready and when supplies will run out then... I have no idea. Troubles!";
			link.l1 = "Well, in that case I have nothing else, but to help you. It collaborates with my future plans...";
			link.l1.go = "mary_11";
		break;
		
		case "mary_11":
			dialog.text = "Do you want to help me? But how? Are you going to kill Chad?";
			link.l1 = "Something like that.";
			link.l1.go = "mary_12";
		break;
		
		case "mary_12":
			dialog.text = "Listen, "+pchar.name+", , of course I appreciate your intentions, but Chad is out of your range. He is one of the most trusted friends of the admiral and even if you will get him - Shark's pirates will kill you, they don't know the truth, alright.";
			link.l1 = "Calm down. I will have to talk with Shark anyway.";
			link.l1.go = "mary_13";
		break;
		
		case "mary_13":
			dialog.text = "Are you a pirate too? Tell me about yourself, just look at him: broke into my place, helped me, saved my life and I don't know anything about him!";
			link.l1 = "Fine... I am not a pirate, but currently I work with pirate baron Jan Swanson. I came here to find Nathaniel Hawk. Do you know him?";
			link.l1.go = "mary_14";
		break;
		
		case "mary_14":
			dialog.text = "No, who is he?";
			link.l1 = "He is another famous pirate. Pity that you don't know him, he must be somewhere here. I was looking for Shark as well, but I didn't expect to find him here.";
			link.l1.go = "mary_15";
		break;
		
		case "mary_15":
			dialog.text = "And how did you get here? You look too well for a survivor of the ship wreck.";
			link.l1 = "And why do you think that I am a survivor?";
			link.l1.go = "mary_16";
		break;
		
		case "mary_16":
			dialog.text = "It is the only way to get here. Only Shark got here on the ship somehow.";
			link.l1 = "Well, not only Shark as you see now.";
			link.l1.go = "mary_17";
		break;
		
		case "mary_17":
			dialog.text = "So, have you got a ship? Great!";
			link.l1 = "Don't be glad that soon, Mary. I got here through... on a barque, but it is sunken now.";
			link.l1.go = "mary_18";
		break;
		
		case "mary_18":
			dialog.text = "A-ah... Well, as I have said before - the ship wreck. You are trapped here with us now, alright.";
			link.l1 = "Mary, let me tell you my plan. You have said that Chad was planning to kill Shark. I don't like it, I need Shark alive, Jan and me are going to make him the head of pirates. That is why I have to warn him because I am sure that Chad will do it even without your help.";
			link.l1.go = "mary_19";
		break;
		
		case "mary_19":
			dialog.text = "Probably yes. He has friends among Narwhals...";
			link.l1 = "It means that my primary goal is to warn Shark. I will kill Chad by the official order, so to speak, if Shark would trust me. Have you got any evidences?";
			link.l1.go = "mary_20";
		break;
		
		case "mary_20":
			dialog.text = "I have got his letter which was brought here by one of those... on the floor. There are threats and details which admiral might find interesting to read. Wait! And what about me? Shark will reveal that I was working with Chad!";
			link.l1 = "Mary, are you going to sit here forever with armed pistols, hiding your beauty from everyone? Do you really think that I am that idiot to screw you? Let me read the letter first and I will think how to help you...";
			link.l1.go = "mary_21";
		break;
		
		case "mary_21":
			GiveItem2Character(pchar, "letter_chad_1");
			RemoveItems(npchar, "letter_chad_1", 1);
			dialog.text = "Take it. Will you find the way to help me?";
			link.l1 = "Wait... (reading). Yes, Chad is a rare bastard. This letter will be enough to make Shark eager to hang him with his own hands. Don't worry about yourself, I will show you from the best side in my future talk with Shark and he won't suspect anything.";
			link.l1.go = "mary_22";
		break;
		
		case "mary_22":
			dialog.text = "Will you do that? Promise me, alright! Swear that you won't betray me!";
			link.l1 = "Mary, I swear that I won't betray you. Don't worry about that. Next item. Chad won't leave you in peace, that's for sure, you know too much about him. Stay here until he is finished by me or Shark.";
			link.l1.go = "mary_23";
		break;
		
		case "mary_23":
			dialog.text = "I will stay here. I don't want to be shot by a sniper or to be stabbed in some dark corner.";
			link.l1 = "Good girl. Close every door including the bottom ones. Have you got the only key?";
			link.l1.go = "mary_24";
		break;
		
		case "mary_24":
			dialog.text = "No. There is one more. Do you want to have it?";
			link.l1 = "Yes. Can you trust me?";
			link.l1.go = "mary_25";
		break;
		
		case "mary_25":
			dialog.text = "Well, if the gentleman who has just saved me will betray me then there is no point to continue living at all... Take it.";
			link.l1 = "Don't be scared, beauty! I won't let you down. I will see you as soon as I solve all problems. I hope that it won't take too long.";
			link.l1.go = "mary_26";
		break;
		
		case "mary_26":
			GiveItem2Character(pchar, "key_mary");
			dialog.text = "It's alright, I will be able to hold this place for a few weeks.";
			link.l1 = "Great. Fine, I won't waste time then. I will take the corpses out and talk with Shark. He is on the 'San Augustine', right?";
			link.l1.go = "mary_27";
		break;
		
		case "mary_27":
			dialog.text = "Yes, he is always there. And get out the same way you got here - I won't let you step on the upper deck of 'Ceres Smithy'.";
			link.l1 = "Interesting, and why is that?";
			link.l1.go = "mary_28";
		break;
		
		case "mary_28":
			dialog.text = "Because I want you to help me and you won't be able to do so if you die. This is a Narwhals' territory and they will kill you as an outsider.";
			link.l1 = "Hm... Got it. Well, Mary, see you. I will be back as soon as I deal with this mess.";
			link.l1.go = "mary_29";
		break;
		
		case "mary_29":
			dialog.text = "You can see me whenever you want, I have no problems with that.";
			link.l1 = "Fine... Bye!";
			link.l1.go = "mary_30";
		break;
		
		case "mary_30":
			DialogExit();
			LAi_SetOwnerType(npchar);
			NextDiag.CurrentNode = "mary_wait";
			npchar.greeting = "mary_3";
			AddQuestRecord("SharkHunt", "31");
			AddQuestRecordInfo("Chad_Mary_letter", "2");
			LocatorReloadEnterDisable("CeresSmithy", "reload6", false);
			LocatorReloadEnterDisable("CeresSmithy", "reload7", false); // открываем выходы
		break;
		
		case "mary_wait":
			dialog.text = "So what, "+pchar.name+", got any good news for me?";
			if (pchar.questTemp.Saga.SharkHunt == "mary_whiskey")
			{
				link.l1 = "The problem with admiral is solved. He has no interest in you, Chad's treason is the only thing that troubles him.";
				link.l1.go = "letters";
			}
			else
			{
				link.l1 = "Not yet, Mary. But I will do everything I can.";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "mary_wait";
		break;
		
		case "letters":
			dialog.text = "Oh, thank God! Thank you, I won't forget it, alright! At least there is no threat from admiral. And what about Chad? What did Shark do?";
			link.l1 = "We have convinced Rivados to attack him. Layton Dexter has taken guards away from 'Tartarus' and gave the key to Black Eddie. Black guys wanted to free their wizard Chimiset, but they have failed to kill Chad. They have killed two of his Narwhal friends, but he ran away and is hiding somewhere.";
			link.l1.go = "letters_1";
		break;
		
		case "letters_1":
			dialog.text = "Damn! That means that I must be even more careful now...";
			link.l1 = "Calm down, Mary. You are out of his concerns now. I am sure that he knows who let the black to attack him. He will do anything to kill Shark, not you.";
			link.l1.go = "letters_2";
		break;
		
		case "letters_2":
			dialog.text = "Do you believe in that? Ah, I am too tired to fear...";
			link.l1 = "Hm. I thought that you are not frightened.";
			link.l1.go = "letters_3";
		break;
		
		case "letters_3":
			dialog.text = "Ha! Am I not? I am not scared to fight face to face, but to sit on my butt idle and expect Chad's actions, alright. I am very scared, "+pchar.name+"...";
			link.l1 = "Trust me: Kapper is interested only in the admiral now... Mary, I need your advice.";
			link.l1.go = "letters_4";
		break;
		
		case "letters_4":
			dialog.text = "My advice? What kind of advice?";
			link.l1 = "Eddie has found some two Chad's letters. Read them, perhaps you will give me some tips. You were planning an attempt with Chad together after all...";
			link.l1.go = "letters_5";
		break;
		
		case "letters_5":
			RemoveItems(pchar, "letter_chad", 1);
			RemoveItems(pchar, "letter_chad_1", 1);
			dialog.text = "Give them here... (reading). Axel is our merchant on 'Esmeralda', alright. Chad wanted to buy some whiskey from him for some reason. Strange! Chad drinks rum only, he calls whiskey the moonshine of peasants...";
			link.l1 = "And what about the second letter?";
			link.l1.go = "letters_6";
		break;
		
		case "letters_6":
			dialog.text = "Marcello? Marcello Cyclops, the ex royal hunter. He is the reason why I fear to leave this cabin.";
			link.l1 = "He is the sniper you've hired?";
			link.l1.go = "letters_7";
		break;
		
		case "letters_7":
			dialog.text = "Yes. Marcello can shoot a fly from forty feet, despite of his lack of eye, alright. His mission was to take down Shark using a long range stutzen from the bowsprit of the Santa Florentina or from Fury's platform...";
			link.l1 = "So it seems that Chad has decided to shoot Shark. But what's the point of Eva then? Cecille? Drinks?";
			link.l1.go = "letters_8";
		break;
		
		case "letters_8":
			dialog.text = "Eva is a neutral ship and Cecille is Cecille Halard, a funny old woman who lives there. She got there not long ago from the Santa Florentina. Orelie Bertine is a friend of hers. They have been living here together since the time I wasn't even born, alright.";
			link.l1 = "Hm. Nonsense. Two big guys are hiding from an old woman to drink a barrel of whiskey together. Rubbish... That is not the best time to drink, Chad!";
			link.l1.go = "letters_9";
		break;
		
		case "letters_9":
			dialog.text = "I have told you already that he doesn't drink whiskey. Rum only.";
			link.l1 = "Fine, whatever. Do you know where to find Cyclops?";
			link.l1.go = "letters_10";
		break;
		
		case "letters_10":
			dialog.text = "No. He is very secretive. He shoots birds every day at the outer ring and no one is aware where he sleeps. He was often visiting Rivados before.";
			link.l1 = "Such a bad luck... Well, I will go and talk to Axel then. Perhaps he will make it more clear. See you, Mary! Close the door.";
			link.l1.go = "letters_11";
		break;
		
		case "letters_11":
			dialog.text = ""+pchar.name+"! I ask you to find Chad. Be quick... I haven't been sleeping since the attack.";
			link.l1 = "Hold on, darling. I will do what I can.";
			link.l1.go = "letters_12";
		break;
		
		case "letters_12":
			DialogExit();
			NextDiag.CurrentNode = "mary_wait";
			pchar.questTemp.Saga.SharkHunt = "trader_whiskey"; // флаг на магазин - поиск виски
			AddQuestRecord("SharkHunt", "35");
		break;
		
		case "happy":
			dialog.text = ""+pchar.name+"! How did he get here? Did he come to...";
			link.l1 = "Yes, to kill you, Mary. He came here through the Jurgen's cabin and used a rope to get down here.";
			link.l1.go = "happy_1";
		break;
		
		case "happy_1":
			dialog.text = "Ah! And I was a fool to forget about that way! Chad has taught him, I am sure, alright.";
			link.l1 = "Exactly. Fuh, I barely made it. He was coming for you.";
			link.l1.go = "happy_2";
		break;
		
		case "happy_2":
			dialog.text = "And I was sleeping. He would have taken me in a second... But how did you know that he was coming here?";
			link.l1 = "I did... I just did, Mary.";
			link.l1.go = "happy_3";
		break;
		
		case "happy_3":
			dialog.text = "You have saved me for the second time. And you always come just in time, alright. How do you do this?";
			link.l1 = "Well, I don't know. It's a gift. Your siege is over - Chad Kapper is dead and so are all of his friends. Cyclops was the last.";
			link.l1.go = "happy_4";
		break;
		
		case "happy_4":
			dialog.text = "Really? Is it true, "+pchar.name+"? You aren't fooling me, right?";
			link.l1 = "Sure, I am not. Eh, now I understand how I got tired for the last days...";
			link.l1.go = "happy_5";
		break;
		
		case "happy_5":
			dialog.text = "Can I breath freely now? Thank you... Thank you so much! You are my hero, alright!";
			link.l1 = "It is great to hear such words, Mary. It is also great to be your hero.";
			link.l1.go = "happy_6";
		break;
		
		case "happy_6":
			dialog.text = "So?";
			link.l1 = "What, pretty one?";
			link.l1.go = "happy_7";
		break;
		
		case "happy_7":
			dialog.text = "Why are you standing? Come on, gentleman.";
			link.l1 = "And what should I do?";
			link.l1.go = "happy_8";
		break;
		
		case "happy_8":
			dialog.text = "You really are a gentleman... Come here and hug me, kiss me at last, you want this, I see that, alright!";
			link.l1 = "Mary...";
			link.l1.go = "happy_9";
		break;
		
		case "happy_9":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_SetActorType(pchar);
			StartQuestMovie(true, true, true);
			PlayStereoOGG("music_romantic");
			bDisableCharacterMenu = true;//лоченые интерфейсы
			InterfaceStates.Buttons.Save.enable = false;//запретить сохраняться
			locCameraRotateAroundHero(0.0, 2.0, 0.0, 0.005, 0.0, 2.0, 0.0, 1700);
			DoQuestCheckDelay("LSC_MaryRomantic_1", 22.0);
			pchar.questTemp.LSC.MaryBye = "true"; // атрибут обязательного прощания перед телепортацией
			LocatorReloadEnterDisable("LostShipsCity_town", "reload62", false);
			LocatorReloadEnterDisable("LostShipsCity_town", "reload63", false); // открываем Церес снаружи
		break;
		
		case "happy_10":
			dialog.text = "Don't leave me...";
			link.l1 = "I am here, Mary, darling...";
			link.l1.go = "happy_11";
		break;
		
		case "happy_11":
			dialog.text = "It all can wait. Admiral will wait, your pirates will wait. Next night belongs only to us both. Alright...";
			link.l1 = "Sure...";
			link.l1.go = "happy_12";
		break;
		
		case "happy_12":
			dialog.text = "And all the next nights too...";
			link.l1 = "Yes, Mary.";
			link.l1.go = "happy_13";
		break;
		
		case "happy_13":
			DialogExit();
			LSC_MaryLoveWaitTime();
			SetLaunchFrameFormParam("Next morning...", "", 0, 4);
			LaunchFrameForm();
			DoQuestCheckDelay("LSC_MaryRomantic_5", 4.0);
		break;
		
	// ----------------------------------вместе с Мэри на Церес Смити------------------------------------------
		case "LSC_love":
			if (pchar.questTemp.LSC.Mary == "return") // эта нода важнее даже ругани с нарвалами
			{
				dialog.text = ""+pchar.name+"! You are back... without her. So she has failed to take your heart!";
				link.l1 = "Mary, your suspicions were reasonless. You are the only one. I was always with you in my thoughts and in my dreams.";
				link.l1.go = "adversary_hire_return";
				break;
			}
			if (CheckAttribute(pchar, "GenQuest.NarvalConflict"))
			{
				dialog.text = ""+pchar.name+", , why are you fighting with Narwhals? I live on their territories, actually, I am one of them in case you've forgotten. Please, go to Fazio and make a peace, I'm begging you.";
				link.l1 = "Alright, Mary, I will do what you ask.";
				link.l1.go = "exit";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.LSC.FindDolly")) // нашел статую - прощается
			{
				dialog.text = ""+pchar.name+", there is a mark of troubles on your face. Something is wrong?";
				link.l1 = "Something like that. Mary, I want to talk with you.";
				link.l1.go = "dolly";
				break;
			}
			if (CheckAttribute(npchar, "quest.donald"))
			{
				dialog.text = ""+pchar.name+"! All Narwhals are talking about you!";
				link.l1 = "Really, my darling?";
				link.l1.go = "donald";
				break;
			}
			if (CheckAttribute(npchar, "quest.talisman")) // подарок
			{
				dialog.text = ""+pchar.name+"! This broadsword is incredible! Thank you again!.. I want to give you a present too. Of course, it cannot be compared to yours but I want you to take it, alright.";
				link.l1 = "Mary, the value of present doesn't really matter...";
				link.l1.go = "talisman";
				break;
			}
			if (stf(environment.time) >= 5.0 && stf(environment.time) < 10.0) // утро
			{
				dialog.text = "Got a busy day ahead, "+pchar.name+"? Good luck!";
				if (CheckAttribute(npchar, "quest.narval_blade"))
				{
					link.l3 = "Mary, we have to go and see Jurgen today.";
					link.l3.go = "narval";
				}
				link.l1 = "Thanks, Mary! I have no doubt in that.";
				link.l1.go = "exit";
				link.l2 = "No, Mary. I want to take a good rest here. Are you fine with that?";
				link.l2.go = "rest_morning"; // отдых
			}
			else
			{
				dialog.text = "Well, "+pchar.name+", how are you doing? Running around the Island as usual?";
				link.l1 = "Yes, Mary. There are a lot of things to be done...";
				link.l1.go = "LSC_love_1";
			}
			NextDiag.TempNode = "LSC_love";
		break;
		
		case "LSC_love_1":
			if (stf(environment.time) >= 18.0 && stf(environment.time) < 22.0) //вечер
			{
				dialog.text = "It is evening already, "+pchar.name+", what things are you talking about? Stay here, let's have some drinks and relax, alright! It all can wait until morning!";
				link.l1 = "(laughing) Sure, love, you have persuaded me...";
				link.l1.go = "LSC_love_evening";
				if (sti(pchar.money) >= 500)
				{
					link.l2 = "Mary, let's got to the tavern today!";
					link.l2.go = "LSC_tavern";
				}
				link.l3 = "Mary, darling, I am really busy now. I will be back a bit later.";
				link.l3.go = "LSC_love_2";
				break;
			}
			if (stf(environment.time) >= 10.0 && stf(environment.time) < 18.0) //день
			{
				dialog.text = "Don't forget to visit me in the evening. And don't even try to avoid it, alright!";
				if (CheckAttribute(npchar, "quest.narval_blade"))
				{
					link.l3 = "Mary, we have to go and see Jurgen today.";
					link.l3.go = "narval";
				}
				link.l1 = "Sure, Mary, how can I? I will visit you for sure.";
				link.l1.go = "exit";
				link.l2 = "No, Mary. I want to take a good rest here. Are you fine with that?";
				link.l2.go = "rest_afternoon"; // отдых
				NextDiag.TempNode = "LSC_love";
				break;
			}
			dialog.text = "What things are you talking about? It is night! No, you ain't going anywhere, you will stay here, alright! And don't you dare to object!";
			link.l1 = "(laughing) I won't...";
			link.l1.go = "LSC_love_night";
			NextDiag.TempNode = "LSC_love";
		break;
		
		case "LSC_love_2":
			dialog.text = "Don't even...";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "LSC_love";
		break;
		
		// сходить в таверну
		case "LSC_tavern":
			dialog.text = LinkRandPhrase("A great idea, "+pchar.name+", alright! I agree!","Sure, let's go, "+pchar.name+"! Sancho has a fine collection of wines, there is a great choice!","Oh, I would be glad, alright! There is always a fun in Sancho's tavern and a great choice of wines!");
			link.l1 = "Let's go!";
			link.l1.go = "LSC_love_tavern";
		break;
		
		// --> отдых
		case "rest_morning":
			dialog.text = "Of course, I am, "+pchar.name+"? Sure, have a rest, alright!";
			link.l1 = "I will stay until the midday...";
			link.l1.go = "rest_day";
			link.l2 = "I will stay until the evening...";
			link.l2.go = "rest_evening";
		break;
		
		case "rest_afternoon":
			dialog.text = "Of course, I am, "+pchar.name+"? Sure, have a rest, alright!";
			link.l1 = "I will stay until the evening...";
			link.l1.go = "rest_evening";
		break;
		
		case "rest_day":
			DialogExit();
			iTime = sti(environment.time);
			iAddTime = 13 - iTime;
			WaitDate("",0,0,0,iAddtime,5);
			RecalculateJumpTable();
			LAi_Fade("", "");
			if (CheckAttribute(pchar, "questTemp.LSC.MaryBye")) NextDiag.CurrentNode = "LSC_love";
			else NextDiag.CurrentNode = "LSC_love_3";
		break;
		
		case "rest_evening":
			DialogExit();
			iTime = sti(environment.time);
			iAddTime = 18 - iTime;
			WaitDate("",0,0,0,iAddtime,5);
			RecalculateJumpTable();
			LAi_Fade("", "");
			if (CheckAttribute(pchar, "questTemp.LSC.MaryBye")) NextDiag.CurrentNode = "LSC_love";
			else NextDiag.CurrentNode = "LSC_love_3";
		break;
		// <-- отдых
		
	//--> если скоро уходит через портал
		case "LSC_love_3": 
			if (pchar.questTemp.LSC.Mary == "return") // эта нода важнее даже ругани с нарвалами
			{
				dialog.text = ""+pchar.name+"! You are back... without her. So she has failed to take your heart!";
				link.l1 = "Mary, your suspicions were reasonless. You are the only one. I was always with you in my thoughts and in my dreams.";
				link.l1.go = "adversary_hire_return";
				break;
			} // 291112
			if (CheckAttribute(pchar, "GenQuest.NarvalConflict"))
			{
				dialog.text = ""+pchar.name+", why are you fighting with Narwhals? I live on their territories, actually, I am one of them if you've forgotten. Please, go to Fazio and make peace, I'm begging you.";
				link.l1 = "Alright, Mary, I will do what you ask.";
				link.l1.go = "exit";
				break;
			}
			if (CheckAttribute(npchar, "quest.talisman")) // подарок
			{
				dialog.text = ""+pchar.name+"! This broadsword is incredible! Thank you again!.. I want to give you a present too. Of course, it cannot be compared to yours, but I want you to take it, alright.";
				link.l1 = "Mary, the value of present doesn't really matter...";
				link.l1.go = "talisman";
				break;
			}
			if (stf(environment.time) >= 5.0 && stf(environment.time) < 10.0) // утро
			{
				dialog.text = "Leaving already, "+pchar.name+"? Good luck and don't forget about me...";
				if (CheckAttribute(npchar, "quest.narval_blade"))
				{
					link.l3 = "Mary, we have to go and see Jurgen today.";
					link.l3.go = "narval";
				}
				link.l1 = "Of course, Mary.";
				link.l1.go = "exit";
				link.l2 = "No, Mary. I want to have a good rest here. Are you fine with that?";
				link.l2.go = "rest_morning"; // отдых
			}
			else
			{
				dialog.text = "Aren't you going to your Kukulcan thingy, "+pchar.name+"?";
				link.l1 = "Not yet, still preparing.";
				link.l1.go = "LSC_love_4";
			}
			NextDiag.TempNode = "LSC_love_3";
		break;
		
		case "LSC_love_4":
			if (stf(environment.time) >= 18.0 && stf(environment.time) < 22.0) //вечер
			{
				dialog.text = "It is evening already, "+pchar.name+". Why won't you stay here? I want to be with you.";
				link.l1 = "Alright, darling, I am staying...";
				link.l1.go = "LSC_love_evening";
				if (sti(pchar.money) >= 500)
				{
					link.l2 = "Mary let's got to the tavern today!";
					link.l2.go = "LSC_tavern";
				}
				break;
			}
			if (stf(environment.time) >= 10.0 && stf(environment.time) < 18.0) //день
			{
				dialog.text = "Good luck and don't forget about me... Come and see me in the evening if you can, alright!";
				if (CheckAttribute(npchar, "quest.narval_blade"))
				{
					link.l3 = "Mary, we have to go and see Jurgen today.";
					link.l3.go = "narval";
				}
				link.l1 = "Very well, darling.";
				link.l1.go = "exit";
				link.l2 = "Mary, I want to have a rest here. Are you fine with that?";
				link.l2.go = "rest_afternoon"; // отдых
				NextDiag.TempNode = "LSC_love_3";
				break;
			}
			dialog.text = "What things are you talking about? It is night! No, you ain't going anywhere, you will stay here, alright! And don't dare to object!";
			link.l1 = "(laughing) I won't...";
			link.l1.go = "LSC_love_night";
			NextDiag.TempNode = "LSC_love_3";
		break;
		// <-- скоро уходит через портал
		
	// --> взаимоотношения - секс и прочее
		case "LSC_love_tavern":
			DialogExit();
			sld = ItemsFromID("potionrum");
			sld.shown = true;
			sld.startLocation = "FleuronTavern";
			sld.startLocator = "bottle";
			DoQuestReloadToLocation("FleuronTavern", "quest", "sit2", "LSC_MaryTavern");
		break;
		
		case "LSC_love_evening":
			DialogExit();
			if(CheckAttribute(PChar, "IsMushketer")) SetMainCharacterToMushketer("", false);
			LSC_MaryEveneng();
		break;
		
		case "LSC_love_night":
			DialogExit();
			LSC_MaryLove();
		break;
		
		case "LSC_love_morning":
			if (CheckAttribute(npchar, "quest.hire"))
			{
				dialog.text = "Captain "+pchar.name+"! Officer Mary Casper is ready to serve under your command!";
				link.l1 = "Well done, officer! I order you to arrive on the ship immediately. But first order: kiss your captain!";
				link.l1.go = "LSC_mary_hire";
			}
			else
			{
				dialog.text = "That was amazing, love... Good morning!";
				link.l1 = "Good morning, honey! You are wonderful!";
				link.l1.go = "LSC_love_morning_1";
			}
		break;
		
		case "LSC_love_morning_1":
			DialogExit();
			LAi_SetOwnerType(npchar);
			if (CheckAttribute(pchar, "questTemp.LSC.MaryBye")) NextDiag.CurrentNode = "LSC_love";
			else NextDiag.CurrentNode = "LSC_love_3";
		break;
		// <-- взаимоотношения
		
		// стал другом нарвалам
		case "donald":
			dialog.text = "Have you spoken to Donald? Is it true that admiral wanted to make an alliance with Rivados and fight against Narwhals? Is it true that you have persuaded him to don't do that? And there is a peace between pirates and Narwhals, right?";
			link.l1 = "You are right, Mary.";
			link.l1.go = "donald_1";
		break;
		
		case "donald_1":
			dialog.text = ""+pchar.name+", I can't find proper words... They also say that Donald considers you as a friend. You might become one of Narwhals, alright!";
			link.l1 = "See Donald when you can - he wants to make peace with you. He asks you to forgive him for his words and for failing to protect you from those two bastards.";
			link.l1.go = "donald_2";
		break;
		
		case "donald_2":
			dialog.text = "Hell with Donald! Though I am glad to hear that of course. I will see him. But you! I... no, not like that... I am proud to be with you, alright!";
			link.l1 = "Good Lord, Mary... you are... ah, you are wonderful!";
			link.l1.go = "exit";
			NextDiag.TempNode = "LSC_love";
			DeleteAttribute(npchar, "quest.donald");
		break;
		
		// ноды прощания
		case "dolly":
			dialog.text = "Let's talk! Are you in trouble?";
			link.l1 = "No. Mary, do you remember the night we first met? After we dealt with those two bastards, I told you that I had arrived here on a long boat.";
			link.l1.go = "dolly_1";
		break;
		
		case "dolly_1":
			dialog.text = "I remember, sure. Your barque was sunk and you had to swim your way here... alright!";
			link.l1 = "I lied. You would have thought that I am crazy. There was no barque. I have used an unexplainable force of Indian god Kukulcan to get to this place.";
			link.l1.go = "dolly_2";
		break;
		
		case "dolly_2":
			dialog.text = ""+pchar.name+"... What are you talking about? What Kukulcan?";
			link.l1 = "Mary, dear, I ask you to believe me because there is no rational point in it. Nathaniel Hawk had disappeared by touching the Indian idol, he was chased and it saved him...";
			link.l1.go = "dolly_3";
		break;
		
		case "dolly_3":
			dialog.text = "";
			link.l1 = "I was looking for Nathaniel. I had a talk with the Indian shaman and did the same thing as Hawk. I was teleported inside the cargo hold of the 'San Augustine', I got out and have finally found you.";
			link.l1.go = "dolly_4";
		break;
		
		case "dolly_4":
			dialog.text = "Are you serious or you are kidding me?";
			link.l1 = "I am serious, Mary. I understand that it is hard to believe and it's much easier to consider me as a psycho, but try to trust me.";
			link.l1.go = "dolly_5";
		break;
		
		case "dolly_5":
			dialog.text = "It seems that Eric's stories were true... And I thought that they were just tales, alright!";
			link.l1 = "Who is Eric? And what did he tell you?";
			link.l1.go = "dolly_6";
		break;
		
		case "dolly_6":
			dialog.text = "Eric was one of the locals, an old sailor. He is dead already. When I was a kid, he used to tell me stories about the golden idol, the shrine where Rivados sacrificed men. Here, on the Island\nThose who touched it, vanished and were never seen again.";
			link.l1 = "It is true, Mary. Eric wasn't lying.";
			link.l1.go = "dolly_7";
		break;
		
		case "dolly_7":
			dialog.text = "Fortunately, the ship with that terrible idle has sunk. I've never seen it.";
			link.l1 = "I have found it at the bottom.";
			link.l1.go = "dolly_8";
		break;
		
		case "dolly_8":
			dialog.text = "Did you dive there?! Did that blasted inventor Vedecker give you the suit? There are crabs, crawling down there, alright!";
			link.l1 = "Mary, don't worry about me. I am able to deal with those monsters. They are not that scary as people say. I have been looking for the statue since my first day on the Island and, at last, I have found it.";
			link.l1.go = "dolly_9";
		break;
		
		case "dolly_9":
			dialog.text = "And what's now?";
			link.l1 = "This is the only way out of here. I have reached this place through the statue and I will leave it the same way... Mary! Are you crying? Stop that!";
			link.l1.go = "dolly_10";
		break;
		
		case "dolly_10":
			if (!CheckAttribute(pchar, "questTemp.Saga.DodsonDie")) sTemp = "Shark, ";
			else sTemp = "";
			dialog.text = "Why should I? I will cry, I want to cry, alright... (sobbing) Things always happen to my men!";
			link.l1 = "What thing will happen to me? I will be back here on a ship. I need to take with me "+sTemp+"Nathaniel and you, of course. Will you follow me to the outer world?";
			link.l1.go = "dolly_11";
		break;
		
		case "dolly_11":
			dialog.text = "(in tears) Of course.... Sure, I will... Will you return for me, yes? And how are you going to find the Island? Only admiral knows how to sail here!";
			link.l1 = "He has given me sailing directions and coordinates. I will bypass reefs and ships' remainings. The Island is no longer a mystery for me.";
			link.l1.go = "dolly_12";
		break;
		
		case "dolly_12":
			dialog.text = "You have said that statue had taken you here right from Main, but what if our statue will take you somewhere to Africa?";
			link.l1 = "Doubt it. Kukulcan is an Indian god so it will take me somewhere within the Caribbean or Main. I only need to find any settlement, then it will be easy to find my ship!";
			link.l1.go = "dolly_13";
		break;
		
		case "dolly_13":
			dialog.text = "Will you be back? Promise me... no, swear, alright!";
			link.l1 = "Mary, dear, I swear that I will be back. And I will take you from here. You won't miss me for too long. Enough with the tears.";
			link.l1.go = "dolly_14";
		break;
		
		case "dolly_14":
			dialog.text = "Fine, "+pchar.name+"... ... Come home, I will be waiting, alright! When are you going to leave?";
			link.l1 = "I don't know yet. I need to prepare myself first, then I will dive and touch the statue. They will tell you that I have drowned - don't believe them. All will be well.";
			link.l1.go = "dolly_15";
		break;
		
		case "dolly_15":
			dialog.text = "I got it. "+pchar.name+", dear, hug me... Kiss me...";
			link.l1 = "Mary... My dear Mary...";
			link.l1.go = "dolly_16";
		break;
		
		case "dolly_16":
			DialogExit();
			DeleteAttribute(pchar, "questTemp.LSC.MaryBye"); // можно телепортироваться
			DeleteAttribute(pchar, "questTemp.LSC.FindDolly");
			SetMusic("music_romantic");
			SetLaunchFrameFormParam("", "", 0, 15);
			SetLaunchFrameFormPic("loading\inside\kiss.tga");
			LaunchFrameForm();
			WaitDate("", 0, 0, 0, 1, 10); //крутим время
			RecalculateJumpTable();
			NextDiag.CurrentNode = "LSC_love_3";
			npchar.greeting = "mary_5"; 
		break;
		
		// дарим Мэри палаш Нарвал
		case "narval":
			dialog.text = "Jurgen? Why?";
			link.l1 = "You'll see. This is going to be a pleasant surprise.";
			link.l1.go = "narval_1";
		break;
		
		case "narval_1":
			dialog.text = "Oh, how interesting! Pleasant? This is great, alright! Let's go before I die of curiosity!";
			link.l1 = "You are going to like it, I am sure. Let's go!";
			link.l1.go = "narval_2";
		break;
		
		case "narval_2":
			DialogExit();
			NextDiag.CurrentNode = "narval_wait";
			LocatorReloadEnterDisable("CeresSmithy", "reload6", true);
			LocatorReloadEnterDisable("CeresSmithy", "reload7", true);
			pchar.quest.LSC_PresentMary.win_condition.l1 = "ExitFromLocation";
			pchar.quest.LSC_PresentMary.win_condition.l1.location = pchar.location;
			pchar.quest.LSC_PresentMary.function = "LSC_GotoPresentMary";
		break;
		
		case "narval_wait":
			dialog.text = "Let's go, "+pchar.name+"!";
			link.l1 = "Sure...";
			link.l1.go = "exit";
			NextDiag.TempNode = "narval_wait";
		break;
		
		case "narval_3":
			dialog.text = "Well, "+pchar.name+", , what surprise have you got for me?";
			link.l1 = "Mary! Jurgen and I decided to make you a present. This is a unique blade, broadsword named Narwhal. There are only two of them in the whole world: first was owned by Alan Milrow, second will be yours. It is made of special steel which will always stay sharp and it will never go rusty.";
			link.l1.go = "narval_4";
		break;
		
		case "narval_4":
			DialogExit();
			LAi_SetActorType(pchar);
			SetMainCharacterIndex(GetCharacterIndex("Schmidt"));
			PChar = GetMainCharacter();			
			LAi_SetPlayerType(PChar);
			sld = characterFromId("Mary");
			sld.dialog.currentnode = "narval_5";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;
		
		case "narval_5":
			dialog.text = "";
			link.l1 = "Our dear girl... All Narwhals know how have you suffered. I suppose that you deserve to wear this broadsword, the symbol of Narwhal clan. Own it with a pride. This blade will be a threat to your enemies and your protector in the fight.";
			link.l1.go = "narval_6";
		break;
		
		case "narval_6":
			PlaySound("interface\important_item.wav");
			sld = characterFromId("Mary");
			RemoveCharacterEquip(sld, BLADE_ITEM_TYPE);
			RemoveItems(sld, "blade_17", 1);
			sTemp = GetBestGeneratedItem("blade_31");
			GiveItem2Character(sld, sTemp);
			EquipCharacterbyItem(sld, sTemp);
			sld = characterFromId("Blaze");
			dialog.text = "Jurgen? Is this excellent blade for me?..";
			link.l1 = "Yes, Mary. "+sld.name+"  has asked me to make it for you and brought some unique iron from the bottom of the sea, no steel can stand against this metal. I've put a part of my soul in it, just as I did once with the Alan's broadsword.";
			link.l1.go = "narval_7";
		break;
		
		case "narval_7":
			dialog.text = "I can't find words... Thank you, Jurgen! Thank you, alright! I will be worthy of this blade, I swear! I haven't been training with broadswords enough, but I will train hard now!";
			link.l1 = "In that I have no doubt, girl.";
			link.l1.go = "narval_8";
		break;
		
		case "narval_8":
			DialogExit();
			LAi_SetStayType(pchar);
			SetMainCharacterIndex(GetCharacterIndex("Blaze"));
			PChar = GetMainCharacter();			
			LAi_SetPlayerType(PChar);
			sld = characterFromId("Mary");
			sld.dialog.currentnode = "narval_9";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;
		
		case "narval_9":
			dialog.text = ""+pchar.name+"... you... not, not like that... You are the best man I've ever known! You are amazing, alright! You can't even imagine how valuable is this gift for me! You've done so much for me already and you are just keeping to surprise me! How can I thank you?";
			link.l1 = "Your happy eyes are the best reward, Mary.";
			link.l1.go = "narval_10";
		break;
		
		case "narval_10":
			dialog.text = "Thank you! I will repay you, I promise!.. Such a wonderful blade, alright! It requires a strong hand... I am eager to take it and start training!";
			link.l1 = "So what is the problem? Your cabin is near, go and try your new broadsword.";
			link.l1.go = "narval_11";
		break;
		
		case "narval_11":
			dialog.text = "That is what I am going to do. Thank you again, gentlemen! "+pchar.name+"! ! Come and see me when you are ready...";
			link.l1 = "Of course, darling. I will see you in the evening.";
			link.l1.go = "narval_12";
		break;
		
		case "narval_12":
			DialogExit();
			EndQuestMovie();
			sld = characterFromId("Schmidt");
			sld.dialog.currentnode = "Jurgen";
			DeleteAttribute(sld, "quest.narval_blade");
			DeleteAttribute(npchar, "quest.narval_blade");
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload2", "CeresSmithy", "goto", "goto10", "LSC_MaryReturnNormal", -1);
			LocatorReloadEnterDisable("CeresSmithy", "reload6", false);
			LocatorReloadEnterDisable("CeresSmithy", "reload7", false); // открываем проход через трюм
			// владение Нарвалом повышает скилл ТО у Мэри и открывает перк тяжелой руки
			SetSelfSkill(npchar, 95, 50, 90, 90, 50);
			SetCharacterPerk(npchar, "HardHitter");
			npchar.quest.talisman = "true";
			npchar.quest.blade31 = "true";
		break;
		
		// Мэри дарит талисман
		case "talisman":
			dialog.text = "Here, take a look. I have found it in one of the ships from the outer ring inside a captain's chest. Every sailor from the Island says that this item is extremely valuable for a navigator, it is able to protect a ship from any storm. Some of them were even eager to buy it, but I haven't sold it... I want you to have this amulet, alright. Take it.";
			link.l1 = "Thank you, Mary! This is a really useful item for the sailor!";
			link.l1.go = "talisman_1";
		break;
		
		case "talisman_1":
			GiveItem2Character(pchar, "talisman2"); 
			PlaySound("interface\important_item.wav");
			Log_Info("You have received a talisman of 'Jonah'");
			dialog.text = "Really? Do you like it? Oh, that is great! I am so glad!";
			link.l1 = "This is a very rare and valuable talisman. Thank you, darling!";
			link.l1.go = "talisman_2";
		break;
		
		case "talisman_2":
			DialogExit();
			DeleteAttribute(npchar, "quest.talisman");
		break;
		
	// --------------------------------------вернулся на Остров---------------------------------------------
		case "return":
			dialog.text = ""+pchar.name+"... You are back. I have been waiting for you, I was looking at horizon every day, alright! You are here...";
			link.l1 = "Yes, Mary. I am here as I promised. Let me hug you, darling!";
			link.l1.go = "return_1";
		break;
		
		case "return_1":
			dialog.text = "Аh, "+pchar.name+"... You can't even imagine how I was feeling! All Narwhals were talking about your death, they said that you drowned. Everybody was sure that you are dead. And kept telling them that you are alive... Of course, nobody believed me, they thought that I have gone crazy because of Alan and you.";
			link.l1 = "Mary... My dear! What is wrong with you? You are trembling... Are you cold?";
			link.l1.go = "return_2";
		break;
		
		case "return_2":
			dialog.text = "No, I am not cold. I am just... I don't want to talk about it here. Come to my cabin when you are done. I want to stay with you alone, alright... Aren't you going to see admiral and Nathaniel now?";
			link.l1 = "Yes. I have to talk with Shark and, of course, take Danielle to Nathaniel. It won't take too much time. I will see you soon, Mary.";
			link.l1.go = "return_3";
		break;
		
		case "return_3":
			dialog.text = "I am looking forward to... see you. Come as soon as possible, alright!";
			link.l1 = "...";
			link.l1.go = "return_4";
		break;
		
		case "return_4":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload62", "CeresSmithy", "goto", "goto11", "LSC_MaryWaitInCabin", 20.0);
		break;
		
		case "adversary":
			dialog.text = ""+pchar.name+"! At last. We have to talk, alright!";
			link.l1 = "What is wrong, Mary? I see that something is eating you! What happened?";
			link.l1.go = "adversary_1";
		break;
		
		case "adversary_1":
			dialog.text = "She happened... "+pchar.name+", who is that whore on your ship?";
			link.l1 = "Who? Are you talking about Danielle? But you already kn...";
			link.l1.go = "adversary_2";
		break;
		
		case "adversary_2":
			dialog.text = "No, not Danielle. I mean that blonde, barely covered with clothes, who is walking around your ship's deck! I saw her through the spyglass, alright!";
			link.l1 = "A-ah! That is Helen McArthur. She is involved in this odd story just like Danielle is. She is serving as my officer. Temporary, of course.";
			link.l1.go = "adversary_3";
		break;
		
		case "adversary_3":
			dialog.text = "Officer? She is an officer?";
			link.l1 = "Well, yes. And what is wrong?.. Mary, damn it! You are jealous!";
			link.l1.go = "adversary_4";
		break;
		
		case "adversary_4":
			dialog.text = "And what did you think?.. (in tears) I had been waiting for him, I didn't sleep because of him and he comes here with some tow-haired...";
			link.l1 = "Mary! Stop crying! What's wrong with you? You can wipe out any fire-eater, but your eyes are always wet... Mary, dear, Helen is just my officer, nothing more.";
			link.l1.go = "adversary_5";
		break;
		
		case "adversary_5":
			if (CheckAttribute(npchar, "quest.blade31")) sTemp = "I have been training hard with the broadsword you gave me, now I master it perfectly.";
			else sTemp = "I have been training hard with rapiers and I master my bretta perfectly.";
			dialog.text = "(sobbing) Officer... Then I also want to be your officer, alright! I can fight, you know that! "+sTemp+" And I shoot well! Yes, I don't have any naval skills but I learn fast, I am talented, alright!";
			// проход первый - ГГ либо соглашается, либо нет, отказ ведет к полному разрыву
			link.l1 = "(agree) Mary... I wanted to offer you that myself. I can't imagine any better war girlfriend than you!";
			link.l1.go = "adversary_hire";
			link.l2 = "(deny) Mary! Being a boarding officer is too dangerous! You don't understand what you are asking for. I can't risk your life.";
			link.l2.go = "adversary_fail";
		break;
		
		// отказ
		case "adversary_fail":
			dialog.text = "Can't you? So that blonde whore can be an officer and I can't? You are lying to me, "+pchar.name+", you simply don't want to be with me! (crying) Is that girl is better than me, yes?";
			link.l1 = "Mary, you don't understand!";
			link.l1.go = "adversary_fail_1";
		break;
		
		case "adversary_fail_1":
			dialog.text = "I do! I saw her glowing eyes upon you! She is not just an officer, alright! I understand that (sobbing). Sure, how can I compete with her - she knows how to run a ship...";
			link.l1 = "Mary, what are you talking about!";
			link.l1.go = "adversary_fail_2";
		break;
		
		case "adversary_fail_2":
			dialog.text = "It's over... (crying) Go away! Go away to your whore! And I will stay here... I ain't going anywhere! Give me my key!";
			link.l1 = "But Mary...";
			link.l1.go = "adversary_fail_3";
		break;
		
		case "adversary_fail_3":
			RemoveItems(pchar, "key_mary", 1);
			dialog.text = "Go away...";
			link.l1 = "...";
			link.l1.go = "adversary_fail_4";
		break;
		
		case "adversary_fail_4": // обидел Мэри - больше от нее ничего не получишь
			DialogExit();
			LAi_CharacterDisableDialog(npchar);//запрет диалога
			for (i=0; i<=3; i++)
			{
				LocatorReloadEnterDisable("LostShipsCity_town", "reload6"+i, true); // закрываем вход к Мэри
			}
			DoQuestReloadToLocation("LostShipsCity_town", "reload", "reload62", "");
			pchar.questTemp.LSC.Mary = "fail";
			AddQuestRecord("LSC", "23");
			bQuestDisableMapEnter = false; //открыть карту
			DeleteAttribute(pchar, "GenQuest.CannotWait");//можно мотать время
		break;
		
		// соглашаемся
		case "adversary_hire":
			// проход второй - смотрим, Элен может стать подругой или нет
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_friend"))
			{
				dialog.text = "Are you kidding me? Did you really want to offer me to be your officer? "+pchar.name+", damn it, you can't imagine how glad I am! I want to be your officer so much... but not on the same ship with that blonde!";
				link.l1 = "Mary, but why?!";
				link.l1.go = "adversary_hire_no";
			}
			else
			{
				dialog.text = "Are you kidding me? Did you really want to offer me to be your officer? "+pchar.name+", damn it, you can't imagine how glad I am! I swear, I won't let you down, you'll see!";
				link.l1 = "Jesus, Mary, darling, you are a kid. You were crying a minute ago and now you are smiling! And, Mary, you are not just another ordinary officer for me.";
				link.l1.go = "adversary_hire_yes";
			}
		break;
		
		case "adversary_hire_no": // Мэри не пойдет, пока не ГГ не расстанется с Элен. Выбирай, кто тебе милее...
			dialog.text = "You might consider her just an officer though she considers you not just her captain, I saw how she was looking at you, I know that look, alright!";
			link.l1 = "Mary, darling, but I have already told you that I do not have feelings for her and that is it! There is nothing between us! I can swear, damn it! I need her to deal with mess about the Brethren of the Coast. Jan Swanson will not help me to capture Tortuga, if I don't help her and I need that!";
			link.l1.go = "adversary_hire_no_1";
		break;
		
		case "adversary_hire_no_1":
			dialog.text = ""+pchar.name+", dear, hug me... I believe you. But I won't be able stay close to her and watch her trying to flirt with you, alright! One day I will take my sword and split her in halves!";
			link.l1 = "Yeah, you definitely can do that... And are you so hot-temper, huh?";
			link.l1.go = "adversary_hire_no_2";
		break;
		
		case "adversary_hire_no_2":
			dialog.text = "And if I'd kill her - you will reject me, alright... I'd never forgive myself.";
			link.l1 = "So what is your proposal, Mary? What should I do with her?";
			link.l1.go = "adversary_hire_no_3";
		break;
		
		case "adversary_hire_no_3":
			dialog.text = "You've said that she is a temporary officer. I will join you as soon as you ground her. I will follow you at the back of beyond, alright! "+pchar.name+", dear, is she really that better than me?";
			link.l1 = "What rubbish are you talking about, Mary? Why do you think that she is better than you? You are the best in all of the world...";
			link.l1.go = "adversary_hire_no_4";
		break;
		
		case "adversary_hire_no_4":
			dialog.text = "Prove me that then. I don't want to share you, "+pchar.name+"! I'd better be alone then the second, alright...";
			link.l1 = "Fine, Mary. Let's have a deal. I can't get rid of Helen now, she is an important figure in the game. I will solve her problems, make her a mistress of Isla Tesoro, ground her and there is nothing will be left between us. It will take a month or two. Will you wait for me that long?";
			link.l1.go = "adversary_hire_no_5";
		break;
		
		case "adversary_hire_no_5":
			dialog.text = "Of course I will, alright! It is my decision... Your return will mean that you've chosen me instead of her. And if you won't return... it is my fate then. I will stay here and found my own clan. Casper clan...";
			link.l1 = "Crying again? Mary, what nonsense are talking about? Staying here, clan... Do not think that I will leave you here to stay among these cold ships debris!";
			link.l1.go = "adversary_hire_no_6";
		break;
		
		case "adversary_hire_no_6":
			dialog.text = "Return as soon as possible then... "+pchar.name+", honey, kiss me, please...";
			link.l1 = "I will be back. I promise you!"; // ага, а мы посмотрим, обманешь или нет
			link.l1.go = "adversary_hire_no_7";
		break;
		
		case "adversary_hire_no_7":
			DialogExit();
			SetMusic("music_romantic");
			SetLaunchFrameFormParam("", "", 0, 15);
			SetLaunchFrameFormPic("loading\inside\kiss.tga");
			LaunchFrameForm();
			WaitDate("", 0, 0, 0, 1, 10); //крутим время
			RecalculateJumpTable();
			NextDiag.CurrentNode = "LSC_love"; // оставляем штучки с Мэри на Острове в силе
			pchar.questTemp.LSC.MaryWait = "true";
			AddQuestRecord("LSC", "22");
			bQuestDisableMapEnter = false; //открыть карту
			DeleteAttribute(pchar, "GenQuest.CannotWait");//можно мотать время
		break;
		
		// повторный разговор после расставания с Элен
		case "adversary_hire_return":
			dialog.text = "Are you joking on a poor girl? "+pchar.name+", have you really been thinking about me?";
			link.l1 = "Of course! Have I ever cheated on you? I've been through a lot during our separation and I am not going to part with you again... my talisman.";
			link.l1.go = "adversary_hire_yes";
			DeleteAttribute(pchar, "questTemp.LSC.MaryWait");
		break;
		
		case "adversary_hire_yes": // Элен заведомо не друг - Мэри идет сразу, либо если выбрал Мэри
			dialog.text = "Really? "+pchar.name+"! I will always follow you! I will never lie to you, I will never betray you, I swear!";
			link.l1 = "I believe you, my dear... Neither will I."; // а куда же ты денешься )
			link.l1.go = "adversary_hire_yes_1";
		break;
		
		case "adversary_hire_yes_1":
			dialog.text = ""+pchar.name+", darling, hug me... We will be together, right? Tell me!";
			link.l1 = "Yes, we will be together, Mary. Forever.";
			link.l1.go = "adversary_hire_yes_2";
		break;
		
		case "adversary_hire_yes_2":
			dialog.text = "Just like Danielle and Nathaniel?";
			link.l1 = "(laughing) Yes, just like them.";
			link.l1.go = "adversary_hire_yes_3";
		break;
		
		case "adversary_hire_yes_3":
			dialog.text = ""+pchar.name+"... I love you! I will marry you if you want, alright...";
			link.l1 = "Dear Mary... You don't know me well. But I like the way you think - we will talk about it later. Now your life on this ship cemetery is over - welcome aboard my vessel and to the big world, my love!";
			link.l1.go = "adversary_hire_yes_4";
		break;
		
		case "adversary_hire_yes_4":
			dialog.text = "Then let's  spend the last night on this Island together, on 'Ceres Smithy'. Just two of us. Only you and me... I won't let you go anywhere until the morning comes, alright!";
			link.l1 = "Well, we are not on my ship so I will follow your command... my Mary!";
			link.l1.go = "adversary_hire_yes_5";
		break;
		
		case "adversary_hire_yes_5":
			DialogExit();
			npchar.quest.hire = "true";
			LAi_SetActorType(npchar);
			LAi_SetActorType(pchar);
			SetMusic("music_romantic");
			DoQuestCheckDelay("LSC_LastNight_CS", 3.0);
			bQuestDisableMapEnter = false; //открыть карту
			DeleteAttribute(pchar, "GenQuest.CannotWait");//можно мотать время
		break;
		
		case "LSC_mary_hire":
			dialog.text = "Aye-aye, sir!";
			link.l1 = "...";
			link.l1.go = "LSC_mary_hire_1";
		break;
		
		case "LSC_mary_hire_1":
			DialogExit();
			DoQuestReloadToLocation("LostShipsCity_town", "reload", "reload62", "LSC_Mary_hire");
			if (pchar.questTemp.LSC.Mary != "return") AddQuestRecord("LSC", "24");
			pchar.questTemp.LSC.Mary = "officer";
			RemoveItems(pchar, "key_mary", 1);
		break;
		
	// --> консультации по морским сражениям
		case "sea_bomb":
			dialog.text = ""+pchar.name+"! I have an idea...";
			link.l1 = ""+npchar.name+"? It's not safe here and I have ordered you to stay on the ship...";
			link.l1.go = "sea_bomb_1";
		break;
		
		case "sea_bomb_1":
			dialog.text = ""+pchar.name+", there are too much gunpowder in this old tub so if it explodes then the whole island will fly sky high. There is no difference where to stay now. Listen to me!";
			link.l1 = "So? What do you want to tell me?";
			link.l1.go = "sea_bomb_2";
		break;
		
		case "sea_bomb_2":
			dialog.text = "The pirate corvette and the frigate. They believe that we are one of them... Knive, alright. This could be an opportunity for us. Let's take a few barrels of gunpowder, a fuse and sail to them.\nAfter they let us closer, we light the fuse, drop the barrel to one of the ships and sail away as fast as we can. Sailing away fast is critical, alright. And then we will observe a spectacular explosion... What do you think?";
			link.l1 = "You are such an inventor! Though, you plan might work... Only in case they won't recognize us.";
			link.l1.go = "sea_bomb_3";
		break;
		
		case "sea_bomb_3":
			dialog.text = "Let's just risk it, "+pchar.name+"?";
			link.l1 = "Fine. We will do that! Lads! Take three barrels of gunpowder! And we are going to get away from here! You are very imaginative, "+npchar.name+"... I would have never come to this idea by myself.";
			link.l1.go = "sea_bomb_4";
		break;
		
		case "sea_bomb_4":
			dialog.text = "I told you that I am talented!";
			link.l1 = "...";
			link.l1.go = "sea_bomb_5";
		break;
		
		case "sea_bomb_5":
			chrDisableReloadToLocation = false;
			DialogExit();
			LAi_SetOfficerType(npchar);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			npchar.dialog.currentnode = "Mary_officer";
			pchar.questTemp.Saga.BarbTemptation.Bomb = "true";
			AddQuestRecord("BarbTemptation", "15");
			AddQuestUserData("BarbTemptation", "sName", "Мэри");
			pchar.questTemp.Saga.BarbTemptation.adviser = "Mary";
		break;
		
		case "fugas":
			dialog.text = "Yes, sure, darling. I am always ready to help, alright! What is the matter?";
			link.l1 = "There is a Jackman's ship at Sabo-Matila Cove, the heavy frigate 'Centurion'. This ship was a property of Hawkes family, besides there must be important things and documents in Jackman's cabin... anyway, we must board it.";
			link.l1.go = "fugas_1";
		break;
		
		case "fugas_1":
			dialog.text = "I see. And how are you going to perform that on our little bird? They have more men and cannons. I have looked through the spyglass, alright!";
			link.l1 = "You are right. Jackman has at least twice more men than we have and all of them are perfectly skilled selected mercenaries. It would be madness to attack them without any preparatory bombardment. The protracted fighting is not the best option too. So I've been thinking about what to do with that.";
			link.l1.go = "fugas_2";
		break;
		
		case "fugas_2":
			dialog.text = "You won't believe, "+pchar.name+", but I have an idea! They haven't recognized us as an enemy yet like those two idiots back at Turks... We can repeat our trick...";
			link.l1 = "Mary, I have just told you that we must board the frigate, sinking her is not an option.";
			link.l1.go = "fugas_3";
		break;
		
		case "fugas_3":
			dialog.text = "I know that, "+pchar.name+". We will not sink her. Listen, we are going to take a few empty rum barrels, put there gunpowder, grapeshot and a very short fuse. Then we will come close to their frigate and throw barrels with our fire rum at their deck.";
			link.l1 = "Ha! Do you think that it is going to work?";
			link.l1.go = "fugas_4";
		break;
		
		case "fugas_4":
			dialog.text = "And why not? Their boards are higher than ours, but two men will be able to throw a barrel easily. We'll shout them - 'a present from Knave'! Barrels will explode even before they realize what is really going on.";
			link.l1 = "Grapeshot will spread and eliminate everybody close to explosion... Damn, it sounds tempting. There are hordes of mercenaries walking around at the deck! There are the most dangerous.";
			link.l1.go = "fugas_5";
		break;
		
		case "fugas_5":
			dialog.text = "Let's throw five barrels at different places. "+pchar.name+", we have got a great advantage - a surprise. They don't suspect of anything! And then we will immediately sail away from them before they board us.";
			link.l1 = "Well, let's try. They must not identify us before we will throw barrels... Damn it, it won't be easy to get close to them. Jackman is not that idiotic like Ghoul was.";
			link.l1.go = "fugas_6";
		break;
		
		case "fugas_6":
			dialog.text = "Let's risk it, "+pchar.name+"! It won't get worse anyway.";
			link.l1 = "It won't, that is for sure... Who will prepare the fougasses? You?";
			link.l1.go = "fugas_7";
		break;
		
		case "fugas_7":
			dialog.text = "Of course, I will, my captain! I promise that I will prepare them perfectly, alright!";
			link.l1 = "Heh, they didn't let you stun crabs back on the Island, at least you can explode some stuff here... Mary, you are wonderful!";
			link.l1.go = "fugas_8";
		break;
		
		case "fugas_8":
			dialog.text = "Thank you, "+pchar.name+"! I won't let you down!";
			link.l1 = "In that I have no doubt. I hope that we won't let you down... To arms!";
			link.l1.go = "fugas_9";
		break;
		
		case "fugas_9":
			DialogExit();
			npchar.dialog.currentnode = "Mary_officer";
			pchar.questTemp.Saga.BarbTemptation.Fugas = "true";
			AddQuestRecord("BarbTemptation", "21");
			DeleteAttribute(npchar, "quest.fugas");
		break;
		// <-- консультации по морским сражениям
		
		// --> суп из черепахи
		case "terrapin_grot":
			dialog.text = "Here you are! It wasn't easy to find you... That was amazing, my captain! I've never seen such a roof run and such a jump from a breathtaking height before! I was beside myself with delight! Though I almost had a heart attack\nOne day you will kill me with these tricks of yours, dear... Well now, and who the fuck is she? "+pchar.name+", just let him stay parted from me for a second and he is flirting already with some whore!";
			link.l1 = "Mary, this 'whore' is Catherine Fox, a daughter of colonel Fox, the commander of Sea Foxes. We will take her to Antigua.";
			link.l1.go = "terrapin_grot_1";
		break;
		
		case "terrapin_grot_1":
			dialog.text = "Really? Isn't that something! Fine, you will tell me about her... this night when we stay together. Now let's go on the boat, we have to hurry out.";
			link.l1 = "You are the best, Mary. What would I do without you? Catherine, follow me!";
			link.l1.go = "terrapin_grot_2";
		break;
		
		case "terrapin_grot_2":
			DialogExit();
			npchar.dialog.currentnode = "Mary_officer";
			LAi_SetOfficerType(npchar);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			Terrapin_GotoShip();
		break;
		// <-- суп из черепахи
		
		// --> калеуче
		case "on_coast":
			dialog.text = "Finally you've woken up, my darling. What a load off my mind! Don't ever again scare me like that!";
			link.l1 = "Mary... dear, what happened? My head is splitting...";
			link.l1.go = "on_coast_1";
		break;
		
		case "on_coast_1":
			dialog.text = "When we entered the captain's cabin, you were lying on the floor still. My heart was beating so fast! The guys picked you up and dragged you to our ship - and just in time, since the dead men lying on the deck began to rise again\nThat was a real nightmare! We couldn't do anything to them! We quickly cut the lines and tried to sail away, but a volley from their ship quickly turned our old tub into splinters. They were some real devils, I say! And then they hoisted sails and were gone in blink of an eye\nOur ship sank, and everyone who managed to survive, have reached the shore in a boat. I managed to take your chest from the cabin. And it was not that easy with all that bustle, I say!";
			link.l1 = "You're a good girl, Mary... What would I do without you?";
			link.l1.go = "on_coast_2";
		break;
		
		case "on_coast_2":
			dialog.text = "Perhaps you'd have gone down or you would've stayed on that ship, and the dead would have ripped you apart... My hands are still shaking!";
			link.l1 = "Thank you, pretty one. I am indebted to you. How long have I been lying there, unconscious?";
			link.l1.go = "on_coast_3";
		break;
		
		case "on_coast_3":
			dialog.text = "For an entire day. I washed and bound your wounds, gave you medicine and poured some rum into you. You should get well soon. Don't even think of dying!";
			link.l1 = "I promise I won't die this time, darling. Although I don't feel really well...";
			link.l1.go = "on_coast_4";
		break;
		
		case "on_coast_4":
			dialog.text = "That's for sure... Was it the 'Flying Dutchman', cap? Why did they attack us? And why didn’t they shoot at us before the boarding, but sank the ship with just one salvo later?";
			link.l1 = "Their captain needed the amulet, about which I had talked to Tuttuathapak, an Indian shaman. That's why they hadn't sunk us immediately, but as their leader took the amulet, they quickly disposed of us... What a nightmare! A ship manned by the dead! Impossible to believe...";
			link.l1.go = "on_coast_5";
		break;
		
		case "on_coast_5":
			dialog.text = "Yeah, now it was our turn to encounter the 'Flying Dutchman'. When I have the chance, I'll go to church, light the candle for our miraculous delivery, and pray to our Lord...";
			link.l1 = "Me too, Mary, I guess. But first I'll go back to that village. I need to tell Tuttuathapak everything about it. That accursed ship attacked us because of the amulet! I hope that red-skinned devil has some ideas, why the hell those living dead might have needed it.";
			link.l1.go = "on_coast_6";
		break;
		
		case "on_coast_6":
			dialog.text = "Alright. But you must be careful - your wounds have barely healed.";
			link.l1 = "But you will help me to heal, won't you? And... Mary, I love you...";
			link.l1.go = "on_coast_7";
		break;
		
		case "on_coast_7":
			dialog.text = "I love you too, my darling...";
			link.l1 = "...";
			link.l1.go = "on_coast_8";
		break;
		
		case "on_coast_8":
			chrDisableReloadToLocation = false;//открыть локацию
			DialogExit();
			npchar.dialog.currentnode = "Mary_officer";
			LAi_SetOfficerType(npchar);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			AddQuestRecord("Caleuche", "5");
		break;
		// <-- калеуче
		
	// --> Мэри вне LSC
		// секс - Мэри не отказывает никогда
		case "cabin_sex":
			dialog.text = RandPhraseSimple(""+pchar.name+", there is no a greater happiness for me then being in your arms, alright... Let's go!",""+pchar.name+", I'd like to be with you every second if it would be possible. Let's go!");
			link.l1 = RandPhraseSimple("You are the best, my girl...","You are wonderful, my beauty...");
			link.l1.go = "cabin_sex_go";
		break;
		
		case "cabin_sex_go":
			DialogExit();
			chrDisableReloadToLocation = true;//закрыть локацию
			DoQuestCheckDelay("Mary_LoveSex", 2.0);
			NextDiag.CurrentNode = "sex_after";
			npchar.greeting = "mary_hire";
		break;
		
		case "sex_after":
			dialog.text = RandPhraseSimple("Dear, you were amazing... you always are!","It was great!");
			link.l1 = RandPhraseSimple("I am glad that you are happy, my love...","I love you Mary...");
			link.l1.go = "exit";
			NextDiag.TempNode = "Mary_officer";
			chrDisableReloadToLocation = false;//открыть локацию
			npchar.quest.daily_sex = true;
			SetFunctionTimerCondition("Mary_SexReady", 0, 0, 1, false);
		break;
		
		case "room_sex":
			if (CheckAttribute(pchar, "questTemp.Terrapin") && pchar.questTemp.Terrapin == "tavern")
			{
				dialog.text = ""+pchar.name+", there is no a greater happiness for me then being in your arms, alright... But it is not the best time - we have to catch that scum Thibaut until he ran away.";
				link.l1 = "You are right as always, my girl...";
				link.l1.go = "exit";
				break;
			}
			dialog.text = RandPhraseSimple(""+pchar.name+", there is no a greater happiness for me then being in your arms, alright... Let's go!",""+pchar.name+", I'd like to be with you every second if it would be possible. Let's go!");
			link.l1 = RandPhraseSimple("You are the best, my girl...","You are wonderful, my beauty...");
			link.l1.go = "room_sex_go";
		break;
		
		case "room_sex_go":
			DialogExit();
			chrDisableReloadToLocation = true;//закрыть локацию
			if (sti(pchar.money) >= 10) AddMoneyToCharacter(pchar, -10);
			if (npchar.chr_ai.type == "actor")
			{
				LAi_SetOfficerType(npchar);
				LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			}
			if (findsubstr(locations[FindLocation(pchar.location)].id, "tavern_upstairs" , 0) == -1)
			{
			DoQuestReloadToLocation(pchar.location+"_upstairs", "quest", "quest4", "");
			ChangeCharacterAddressGroup(npchar, pchar.location+"_upstairs", "quest", "quest3");
			} // patch-8
			DoQuestCheckDelay("Mary_LoveSex", 2.5);
			NextDiag.CurrentNode = "sex_after";
			npchar.greeting = "mary_hire";
		break;
		
		// требует секса, если давно не давал
		case "givemesex":
			dialog.text = RandPhraseSimple(""+pchar.name+", it's been too long since we had sex... You have completely forgotten about me, alright! Darling, I want to relax, let's take a room and retire from troubles!",""+pchar.name+", you have been too busy and I am starting to suspect that you have completely forgotten about me! Darling, I want to... stay with you in private. Let's take a room, alright!");
			link.l1 = "Mary, dear, what are you talking about - 'completely forgotten about me'? Silly girl... But I have been really too busy, those problems are endless. Forgive me, my girl. Sure, let's go upstairs and the world can wait!";
			link.l1.go = "room_sex_go";
		break;
		
		// ругается за то, что ходил по борделям, ГГ изворачивается
		case "brothel":
			dialog.text = "Yes, there is! You don't like me anymore, do you? Tell me!";
			link.l1 = "What?! Mary, what nonsense are you talking about? Why do you think that?";
			link.l1.go = "brothel_1";
		break;
		
		case "brothel_1":
			dialog.text = "Then why have you been visiting those bitches, those brothel whores? I know that, don't deny that! You don't like something in me when we are making love, yes? (crying) Tell me...";
			link.l1 = "Mary, Mary... calm down, please, my girl. Yes, I have been at the brothel for a few times but only because of business matter. I wasn't seeking any fun!";
			link.l1.go = "brothel_2";
		break;
		
		case "brothel_2":
			dialog.text = "And what 'business matters' had brought you upstairs to the whore room? (sobbing) You are lying, "+pchar.name+"!";
			link.l1 = "Mary, dear, stop that at last... I really had some business matters with the mistress of brothel.  And I had been coming upstairs for a few times. Last time was by the personal ask of the governor - he asked me find his wedding ring. How could I say no to His Excellency?";
			link.l1.go = "brothel_3";
		break;
		
		case "brothel_3":
			dialog.text = "";
			link.l1 = "And how could I explain mistress that I need to search under the bed upstairs? I couldn't. So I had to buy a whore.. Second time I was told that one merchant has lost his ship papers there. I had to pay for a girl again in order to search the room and I was paid well for the documents...";
			link.l1.go = "brothel_4";
		break;
		
		case "brothel_4":
			dialog.text = "";
			link.l1 = "Third time I was helping the local commandant: I had to ask whores about one officer from garrison. That officer was suspected in espionage and connections with pirates. Finally, we had catched him and I got a huge reward...";
			link.l1.go = "brothel_5";
		break;
		
		case "brothel_5":
			dialog.text = "";
			link.l1 = "See now? I tell you, it was all about business matters. Mary, you are the one I love and need. You are the best, I swear! Do you really think that I will do some dirty harbour whore when I have you with me? How could you even think of it!";
			link.l1.go = "brothel_6";
		break;
		
		case "brothel_6":
			dialog.text = ""+pchar.name+"... Is it all true? Are you honest with me? You have not been with them?";
			link.l1 = "Mary, dear, you are the only woman I love, it is true. Come closer, dear. Let me hug you... Wipe your tears and, please, stop being jealous! I will never visit these brothels if you want!";
			link.l1.go = "brothel_7";
		break;
		
		case "brothel_7":
			dialog.text = "Yes, I want!.. "+pchar.name+", I am jealous because I love you... And I don't want to lose you, alright! Do you hear? I will kill any bitch who dares to come closer at you!";
			link.l1 = "Calm down... my proprietress. There is no need to kill anybody. And you won't lose me, I promise. It's all right, calm down. You are my only one and the best girl in the world... Trust me, you are.";
			link.l1.go = "brothel_8";
		break;
		
		case "brothel_8":
			DialogExit();
			SetLaunchFrameFormParam("", "", 0, 5);
			SetLaunchFrameFormPic("loading\inside\kiss.tga");
			LaunchFrameForm();
			pchar.GenQuest.BrothelLock = true; // все, больше не походишь по борделям :)
			DeleteAttribute(pchar, "GenQuest.BrothelCount");
		break;
		
		// на Тайясаль
		case "tieyasal":
			dialog.text = ""+pchar.name+", what an odd question? I love you. You saved me. I am your red talisman - do you really think that I will let you go there alone? Don't even count on that, alright! I am with you! When shall we go?";
			link.l1 = "You are right, dear, it was an odd question... I will tell you later when we are going. We need to prepare ourselves first.";
			link.l1.go = "tieyasal_1";
		break;
		
		case "tieyasal_1":
			dialog.text = "I am ready, my captain! I will follow you at the back of beyond!";
			link.l1 = "Thank you, my love...";
			link.l1.go = "tieyasal_2";
		break;
		
		case "tieyasal_2":
			DialogExit();
			AddQuestRecord("Tieyasal", "19");
			npchar.quest.Tieyasal = "teleport";
		break;
		
		// Jason Дороже золота
		case "GoldenGirl":
			pchar.quest.Mary_giveme_sex1.over = "yes"; // fix 22-03-20
			pchar.questTemp.GoldenGirl.MaryBlock = "true"; // fix 22-03-20
			dialog.text = "What's all the ruckus this time, Captain? Spanish, pirates or worse?";
			link.l1 = "It's worse, Mary, much worse. The governor is intending to pay a visit to an extremely expensive courtesan and I am supposed to accompany him as a curiosity, promised to the mistress. Boring talks, overpriced wine and dull nobles.";
			link.l1.go = "GoldenGirl_1";
			link.l2 = "Quite the opposite, an invitation to burden less social event, run by a noble lady. His Excellency took me by surprise by asking me to accompany him, but to be honest, I am glad to get my mind off things.";
			link.l2.go = "GoldenGirl_3";
		break;
		
		case "GoldenGirl_1":
			dialog.text = "Is that so?! A courtesan? You sayin' like it's not a big deal, huh? Just having a bit fun with His Excellence? Charles, are you fu...";
			link.l1 = "Mary, calm down, please! It's not like I am going there to... it's not a brothel! Well, it is a brothel, but damn me if I am not a nobleman and a man of his word. You really don't trust me? The governor only asked me for a tiny favor and I will oblige him, that's all!";
			link.l1.go = "GoldenGirl_2";
		break;
		
		case "GoldenGirl_2":
			dialog.text = "Yeah, knew a couple of 'noblemen' alright. I've seen them in your company too. Courtesans are the day's work for them! 'High' societies, 'Dignified' entertainment my ass! Even a marriage is not stopping them from going to these... ladies. Damn I had no idea that you are just like them. We are not even... Screw you, all of you!";
			link.l1 = "Mary, wait! Fuck...";
			link.l1.go = "GoldenGirl_6";
		break;
		
		case "GoldenGirl_3":
			dialog.text = "We earned a vacation alright. You think they can handle seeing a dame dressed in Redcoat? Imagine all the whispers in the corners? Someone will surely faint, that'd be fun, right?";
			link.l1 = "Mary, my dear, this is not kind a party where you take a dame... at least a dame of yours. Well, it is a bit complicated but let me explain...";
			link.l1.go = "GoldenGirl_4";
		break;
		
		case "GoldenGirl_4":
			dialog.text = "Whew, don’t bother. Just tell me straight that I am not good enough for those pricks in cuffs. A simple girl for fun, huh? Ashamed to show yourself with her in the world? Not good enough for fancy reception, right, honorable monsieur Charles de Maure?";
			link.l1 = "No at all. You are amazing and I don't care about an impression we make together. The governor is trying to solve his problems with my help just as always. I will be like a valuable trophy. A curious guest to impress noble good-for-nothings.";
			link.l1.go = "GoldenGirl_5";
		break;
		
		case "GoldenGirl_5":
			dialog.text = "So I am not good for you then, yes? I see, it's alright, nobles to nobles, peasants to our simple amusements. Best of luck with your dignified class. I'll talk to you when you are back on our humble soil, yes.";
			link.l1 = "Mary, wait! Fuck...";
			link.l1.go = "GoldenGirl_7";
		break;
		
		case "GoldenGirl_6":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "GoldenGirl_GirlExit", 10.0);
			pchar.questTemp.GoldenGirl.Angry1 = "true";
		break;
		
		case "GoldenGirl_7":
			DialogExit();
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "GoldenGirl_GirlExit", 10.0);
			pchar.questTemp.GoldenGirl.Angry2 = "true";
		break;
		
		case "GoldenGirl_10":
			dialog.text = "Best of luck with your dignified class. I'll talk to you when you are back on our humble soil, yes.";
			link.l1 = "Mary oh, come on!";
			link.l1.go = "GoldenGirl_11";
		break;
		
		case "GoldenGirl_11":
			DialogExit();
			NextDiag.CurrentNode = "GoldenGirl_10";
		break;
		
		case "GoldenGirl_12":
			dialog.text = "Look at this, yes! Our lost in high society captain!";
			link.l1 = "...";
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.Angry1")) link.l1.go = "GoldenGirl_13";
			else link.l1.go = "GoldenGirl_17";
		break;
		
		case "GoldenGirl_13":
			dialog.text = "You disappeared in the whorehouse for the whole day and now people around the town are talking. Charles, name me just one good reason I should talk with you now instead of say, putting a bullet in your... belly? You absolutely disregard me, yes?!";
			link.l1 = "Mary, I'll explain you everything, only later. Now I should get myself in order and go for a duel. Feel free to shoot me if I will live it through. Meanwhile, please take care of our new ship, alright? I won her in a card game last night.";
			link.l1.go = "GoldenGirl_14";
		break;
		
		case "GoldenGirl_14":
			dialog.text = "Forget the ship, you said something about a duel, yes? Locals tell all kinds of bullshit stories I couldn't believe to. They say you fight either a king's son or the freaking Pope himself. Tell me, now, what the fuck is going on?!";
			link.l1 = "This man is a bastard of a very influential nobleman, Count de Levi Vantadur. It was he who challenged me in the first place, and I must win the duel without hurting him to much to avoid his father's wrath.";
			link.l1.go = "GoldenGirl_15";
		break;
		
		case "GoldenGirl_15":
			dialog.text = "While I'll be sitting tight on the tub your won? You gone mad, Charles, yes?";
			link.l1 = "I am afraid it had to be that way. The governor provided me with a couple of noble officers to be my seconds in order to avoid ay confusion afterwards. I cant take you or any of the guys with me. This is too serious, I am sorry.";
			link.l1.go = "GoldenGirl_16";
		break;
		
		case "GoldenGirl_16":
			dialog.text = "You know what I am gonna do now? I will go to that blasted ship and get properly drunk, yes! Do whatever you like, but if the noble whoreson will fail to kill you, I swear I will do it myself!";
			link.l1 = "Mary, everything will be just fine, trust me. Now, wait... Fuck! Here we go again!";
			link.l1.go = "GoldenGirl_21";
		break;
		
		case "GoldenGirl_17":
			dialog.text = "Didn't bother to send a word that you alright all day, yes? Our hair almost turned white when we heard what people at the market are gossiping. The say you played for ships and women, got yourself a duel with some sort of a crowned prince or with the Pope himself! What the fuck is going on here?";
			link.l1 = "It is complicate, it will take a while to explain, Mary. I did won a frigate though. You will have to take care of her while I am settling my dispute with her previous owner.";
			link.l1.go = "GoldenGirl_18";
		break;
		
		case "GoldenGirl_18":
			dialog.text = "So they were right about the duel, yes? Who is this highborn ass? Why are you fighting him?";
			link.l1 = "I have to. It's complicated, but in short: I won his ship and his… dame. He publicly accused me of cheating and challenged me for a duel. This man is a bastard of a very influential nobleman, Count de Levi Vantadur. I will have to do my best to don't kill him.";
			link.l1.go = "GoldenGirl_19";
		break;
		
		case "GoldenGirl_19":
			dialog.text = "A dame? I can understand playing for a ship, but… a woman, yes? They were saying the truth in the streets alright! You admit it just like that?! Like I am… one of your fucking sailors?";
			link.l1 = "Damn it, Mary, it's not like that at all! He won her from the governor, I won her from him to release her, that's it. No second thoughts, I swear!";
			link.l1.go = "GoldenGirl_20";
		break;
		
		case "GoldenGirl_20":
			dialog.text = "Well, maybe it is a casual thing to do among you nobles but I am not like that, yes. Do what you like, say what you like… go and die for her if you want! I will go to the fucking ship you won and get fucking wasted. I so believed this was for real and... will last forever, I hoped so much!";
			link.l1 = "Mary, I don't give a damn about that woman! Just wait, please... Fuck! Here we go again...";
			link.l1.go = "GoldenGirl_21";
		break;
		
		case "GoldenGirl_21":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "GoldenGirl_GirlToFregat", 15.0);
		break;
		
		case "GoldenGirl_24":
			dialog.text = "Charles, you came for me, alright! I knew it, never doubted it! I am so happy to see you!";
			link.l1 = "Me too, Mary! It's been killing me, all this time. Thank God you are alright!";
			link.l1.go = "GoldenGirl_25";
		break;
		
		case "GoldenGirl_25":
			if (pchar.questTemp.GoldenGirl == "alarm_fin")
			{
				dialog.text = "By the way, what exactly did you do to make them set me free so easily? Without a proper brawl, without a shooting, alright. Oh, and I saw this beautiful lady on deck when they were dragging me out. What happened there, Charles?";
			}
			else
			{
				dialog.text = "What exactly did you do to make them to release me just like that? No fight, no shots fired, alright! I saw some British peacocks on deck when they were bringing me out. What was all that about, Charles?";
			}
			link.l1 = "All that matters is you are back with me. I failed you, Mary. I am so sorry! I hope you can find it in your heart to forgive me!";
			link.l1.go = "GoldenGirl_26";
		break;
		
		case "GoldenGirl_26":
			dialog.text = "Already did. I am sorry too, alright! If only I didn't took your dealings with that dame too personal… I would had set a proper watch that night. They would never took us down so easily! So silly of me!";
			link.l1 = "Past is the past. I love you and I will never leave you back. I promise!";
			link.l1.go = "GoldenGirl_27";
		break;
		
		case "GoldenGirl_27":
			dialog.text = "I knew you'd never abandon me, alright. Sorry for ever doubting you, Charles! I guess, I'd better not know what exactly you did, right? Okay, we are together again and that's the main thing.";
			link.l1 = "I have no secrets from you. I will tell you...";
			link.l1.go = "GoldenGirl_28";
		break;
		
		case "GoldenGirl_28":
			DialogExit();
			SetLaunchFrameFormParam("Little time has passed...", "", 0.1, 3.0);
			LaunchFrameForm();
			WaitDate("", 0, 0, 0, 1, 0);
			npchar.dialog.currentnode = "GoldenGirl_28_1";
			LAi_SetActorType(npchar);
			LAi_ActorDialogDelay(npchar, pchar, "", 4.0);
		break;
		
		case "GoldenGirl_28_1":
			if (pchar.questTemp.GoldenGirl == "alarm_fin")
			{
				dialog.text = "What a story to tell, no one to ever believe it, alright! I knew that from the very beginning! I knew your 'playful' night was a funny business! All them noble bloods... with pouches of doubloons instead of hearts! It is so good you are different, alright!";
				link.l1 = "I am pretty sure a lot of people out there consider me far worse. A proper monster from fairy tales.";
			}
			else
			{
				dialog.text = "What a story to tell, no one to ever believe it, alright! I knew that from the beginning! I knew your 'playful' night was a funny business! Politics, spies, con-spi-ra-cies. And you again, saving us all, alright!";
				link.l1 = "Not sure about that. Chances are a war with Britain starts in a few weeks. But I did what had to, Mary. You mean everything to me.";
			}
			link.l1.go = "GoldenGirl_29";
		break;
		
		case "GoldenGirl_29":
			if (pchar.questTemp.GoldenGirl == "alarm_fin")
			{
				dialog.text = "I care not cause you are my monster, Charles! Others can either go and shed tears about that or deal with me! Remember that I will always stay at your side, alright!";
			}
			else
			{
				dialog.text = "I know, Charles. I always knew, but it is so nice to hear you saying it. Know this too that will always remain by your side, alright!";
			}
			link.l1 = "Never doubted that, Mary. Let's go, boys are worrying. Time to set sails and get the hell out of here. You are by my side again and horizon is not going anywhere on its own!";
			link.l1.go = "GoldenGirl_30";
		break;
		
		case "GoldenGirl_30":
			dialog.text = "Aye, aye, Captain!";
			link.l1 = "";
			link.l1.go = "GoldenGirl_31";
		break;
		
		case "GoldenGirl_31":
			DialogExit();
			npchar.dialog.currentnode = "Mary_officer";
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "sea", "none", "", "", "GoldenGirl_GirlGoOnBoard", 10.0);
			GoldenGirl_MaryBlockDelete(); // fix 22-03-20
		break;
		
		case "GoldenGirl_32":
			dialog.text = "Charles, is this really you?! I almost lost all hope, yes! God, I missed you so much! Please, please forgive me, yes!";
			link.l1 = "Forgive me, I absolutely didn't see it coming... Thank God you've made it, Mary! I am so happy!";
			link.l1.go = "GoldenGirl_33";
		break;
		
		case "GoldenGirl_33":
			dialog.text = "Speaking of forgiveness - to be completely honest, I am not sure what I want more: either to shoot you or to hug you. You will tell me what the hell happened, right?";
			link.l1 = "I love you, Mary. This is all I wanted to tell you.";
			link.l1.go = "GoldenGirl_34";
		break;
		
		case "GoldenGirl_34":
			dialog.text = "Yeah, this was helpful, but... Damn, me too, Charles. I love you too, yes. God, finally, we are together!";
			link.l1 = "And I don't want to spend the time we have on talking. Come with me and I won't leave you tonight even if the sky will start falling on this miserable town. I will never leave you again. Ever.";
			link.l1.go = "GoldenGirl_35";
		break;
		
		case "GoldenGirl_35":
			dialog.text = "I guess, I'd better not know what exactly you did, right? Okay, we are together again and that's the main thing.";
			link.l1 = "I have no secrets from you. I will tell you...";
			link.l1.go = "GoldenGirl_36";
		break;
		
		case "GoldenGirl_36":
			DialogExit();
			SetLaunchFrameFormParam("Little time has passed...", "", 0.1, 3.0);
			LaunchFrameForm();
			WaitDate("", 0, 0, 0, 1, 0);
			npchar.dialog.currentnode = "GoldenGirl_36_1";
			LAi_SetActorType(npchar);
			LAi_ActorDialogDelay(npchar, pchar, "", 4.0);
		break;
		
		case "GoldenGirl_36_1":
			dialog.text = "Are you saying this... marquise helped you bring me back? And you almost started a war between England and France, yes? Don't get me wrong - this is so romantic and all, but what will happen now? ";
			link.l1 = "I have no idea, Mary. We are together again, the rest is irrelevant. If those in power will fail to sweep it under the rug… well, I am ready to do my duty before the Crown.";
			link.l1.go = "GoldenGirl_37";
		break;
		
		case "GoldenGirl_37":
			dialog.text = "And that marquise of yours? Did you bring her back too? The Portuguese spoke highly of her. He assured me that you withstood her advances like the Bastille castle. I so much want to believe him, alright, but I must hear that from you!";
			link.l1 = "There is nothing going on between madam Botot and me, Mary. I helped her, she helped me, that's all. Speaking of Bartholomew, where is he?";
			link.l1.go = "GoldenGirl_38";
		break;
		
		case "GoldenGirl_38":
			dialog.text = "He is gone, alright. Set sails immediately after he brought me here. I would never go to that blasted whorehouse, so he rented a room for me, paid in advance for a couple of weeks and just left. Oh, I almost forgot, alright! I've got a letter for you!";
			link.l1 = "A letter? From Bartholomew the Portuguese? This is something new. I don't like where this is going...";
			link.l1.go = "GoldenGirl_39";
		break;
		
		case "GoldenGirl_39":
			dialog.text = "Go ahead, read it. I'll go and show myself to the boys. They worried about me, right? Me too! Terribly! Did everyone make it? Hope you don't mind us having a cup or two downstairs. Don't get yourself into another mess, alright!";
			link.l1 = "Sure thing, but please be careful with them, Mary. Tonight is not the night I'd rather spend time with you instead of carrying drunk bodies back to the ship. Oh, I still can believe I got you back!";
			link.l1.go = "GoldenGirl_40";
		break;
		
		case "GoldenGirl_40":
			DialogExit();
			npchar.dialog.currentnode = "Mary_officer";
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "GoldenGirl_SPGirlReturn", 10.0);
			GoldenGirl_MaryBlockDelete(); // fix 22-03-20
		break;
		
		// Jason Долго и счастливо
		case "LongHappy":
			RemoveItems(pchar, "potionwine", 2);
			dialog.text = "The beatch, you, me, and good wine - Charles, it is so romantic! We should often have a walk like this together, alright!";
			link.l1 = "Glad you like it. I think we will have more time for this since now and generally for each other.";
			link.l1.go = "LongHappy_1";
		break;
		
		case "LongHappy_1":
			dialog.text = "What are you talking about? Something happened to the ship, huh? Why do you have such a face?";
			link.l1 = "Because I love you, Mary. You know that, I know that, everybody knows that. So here and now, in front of this sea and sky, I ask you, Mary Casper - to give me the honor to stand with me before people and God for as many days as we allotted from above. I, Charles de Maure, chevalier de Monper, ask you - will you become my wife?";
			link.l1.go = "LongHappy_2";
		break;
		
		case "LongHappy_2":
			if (pchar.location == "Shore36")
			{
				dialog.text = "I dreamed to hear it, alright! I... you know my answer Charles... oh, sorry!";
				link.l1 = "Nevermind, this is just wine and I never loved this shirt...";
				link.l1.go = "LongHappy_3";
			}
			else
			{
				dialog.text = "Charles, of course yes! Yes, yes, a thousand times yes!!! You... this place... nothing can make me happier!!! Oh god, I'm so happy, alright!";
				link.l1 = "You made me happy, Mary. And I want to drink to you, my burning Carib Sun!";
				link.l1.go = "LongHappy_4";
			}
		break;
		
		case "LongHappy_3":
			DialogExit();
			chrDisableReloadToLocation = true;//закрыть локацию
			DoQuestCheckDelay("Mary_LoveSex", 1.0);
			npchar.dialog.currentnode = "LongHappy_5";
			LAi_SetStayType(npchar);
		break;
		
		case "LongHappy_4":
			dialog.text = "Drink to you, my captain and future husband, alright! You are the best that happened to me!";
			link.l1 = "But this is only the beginning - to us! And to our future together! There's so much waiting us further!";
			link.l1.go = "LongHappy_6";
		break;
		
		case "LongHappy_5":
			dialog.text = "Drink to you, my captain and future husband, alright! You are the best that happened to me!";
			link.l1 = "But this is only the beginning - to us! And to our future together! There's so much waiting us further!";
			link.l1.go = "LongHappy_6";
		break;
		
		case "LongHappy_6":
			DialogExit();
			chrDisableReloadToLocation = false;
			npchar.dialog.currentnode = "Mary_officer";
			LongHappy_MarryToSenPierre();
		break;
		
		case "LongHappy_7":
			dialog.text = "Charles, Abbot Benoit is again in Martinique, so we can proceed, right? But I will not wear a dress, even for the sake of church service, won't you be offended?";
			link.l1 = "Mary, I love you in any outfit and ... well, you know. You can wear anything you wish, I'll deal with anyone who will try to say something! But, I just wanted to consult with you about the guests and the ceremony.";
			link.l1.go = "LongHappy_8";
		break;
		
		case "LongHappy_8":
			if (LongHappy_CheckSaga())
			{
				dialog.text = "You know, most of those, who can sincerely rejoice at our happiness, won't be allowed to enter even this city, I'm not talking about a church, alright. Therefore - let's get married here with all the important people, as expected, and then we'll sail to Isla Tessoro and properly celebrate with real friends! What do you think, alright?";
				link.l1 = "This is the option! So let's do it. I'll talk to Abbot Benoit, but we need to send out invitations and more...";
				link.l1.go = "LongHappy_9";
			}
			else // Сага провалена по времени или утоплен Центурион
			{
				dialog.text = "You know, I don’t have many friends except our guys from the crew. So invite those whom you consider necessary, and I will just be happy, alright!";
				link.l1 = "As you say, sweetheart. I'll talk to Abbot Benoit and organize everything, you are worthy of the most magnificent ceremony.";
				link.l1.go = "LongHappy_9a";
			}
		break;
		
		case "LongHappy_9":
			dialog.text = "Don't worry, as a good wife, I will take part of the preparation on myself, alright. I will write to our friends and arrange everything, but first, tell me: how do you see this wedding?";
			link.l1 = "My ideal is you, me and our closest friends. After all the official faces here in Martinique, we will want some sincerity.";
			link.l1.go = "LongHappy_10";
			link.l2 = "We must remember this day. Call everyone! No one will be left out!";
			link.l2.go = "LongHappy_11";
		break;
		
		case "LongHappy_9a":
			dialog.text = "With you, I'm enough of a ship chaplain on the quarterdeck , under the sunset at some coast, alright. But, if such a thing - we will celebrate! Charles ... I'm going to cry now, hug me, alright ...";
			link.l1 = "Mary...";
			link.l1.go = "LongHappy_9b";
		break;
		
		case "LongHappy_9b":
			dialog.text = "That's it, I'm calm, alright. Sorry, this is all so unusual. But Charles, like a good wife, let me take over the organization. We also need to arrange a party for guys, alright, but it is unlikely that the whole crew will fit in the church. I will come to agree with the tavern, but we will need booze and money - you know how sailors have fun.";
			link.l1 = "All right, that 's what we 're gonna do. What do I have to prepare?";
			link.l1.go = "LongHappy_9c";
		break;
		
		case "LongHappy_9c":
			pchar.questTemp.LongHappy.MarryMoney = 100000;
			pchar.questTemp.LongHappy.MarryRum = 100;
			if (sti(RealShips[sti(pchar.ship.type)].Class) < 2)
			{
				pchar.questTemp.LongHappy.MarryMoney = 200000;
				pchar.questTemp.LongHappy.MarryRum = 150;
			}
			if (GetCompanionQuantity(pchar) > 1)
			{
				pchar.questTemp.LongHappy.MarryMoney = 300000;
				pchar.questTemp.LongHappy.MarryRum = 200;
			}
			dialog.text = "I think, "+sti(pchar.questTemp.LongHappy.MarryMoney)+" pesos will be enough, alright. "+sti(pchar.questTemp.LongHappy.MarryRum)+" barrels of rum, there is nothing worse than be left out of drinks. As soon as you collect everything you need, come to the tavern, I will agree on the rest.";
			link.l1 = "Okay, honey, I'll do it.";
			link.l1.go = "LongHappy_9d";
		break;
		
		case "LongHappy_9d":
			DialogExit();
			npchar.dialog.currentnode = "Mary_officer";
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "LongHappy_GirlNorm", 5.0);
			AddQuestRecord("LongHappy", "10_1");
			AddQuestUserData("LongHappy", "sName", "Mary");
			LongHappy_MarryGoToBenua();
		break;
		
		case "LongHappy_10":
			pchar.questTemp.LongHappy.SmallMarry = "true";
			dialog.text = "Got it, let's do it. But we will have to visit Sharptown and prepare everything. I think fifty barrels of rum and a couple dozen barrels of wine will do just fine, alright. But, just in case, I will need three hundred thousand pesos.";
			link.l1 = "A lot, but it's also a special reason. I will get everything, don't worry. Now, I'm going to drop by to the abbot and go to Sharptown.";
			link.l1.go = "LongHappy_12";
		break;
		
		case "LongHappy_11":
			pchar.questTemp.LongHappy.BigMarry = "true";
			dialog.text = "Great, we'll get everyone together, alright! But we will have to visit Sharptown and prepare everything - we will need a galleon full of booze!  I think a hundred barrels of rum and fifty barrels of wine will do just fine. But, just in case, I will add five hundred thousand pesos. If the celebration ends quickly, what kind of celebration is it, right?";
			link.l1 = "Yes, our friends must not die of thirst -  I will get everything, don't worry! Now, I'm going to drop by to the abbot and go to Sharptown.";
			link.l1.go = "LongHappy_12";
		break;
		
		case "LongHappy_12":
			DialogExit();
			npchar.dialog.currentnode = "Mary_officer";
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "LongHappy_GirlNorm", 5.0);
			AddQuestRecord("LongHappy", "10");
			AddQuestUserData("LongHappy", "sName", "Mary");
			LongHappy_MarryGoToBenua();
		break;
		
		case "LongHappy_13":
			dialog.text = "Everything is ready, Charles, right? I will arrange for the drink to be unloaded, go to agree with the local tavern, meet the baron and hand the invitations. Will you wait here, aright?";
			link.l1 = "You are at the helm, dear! Then I'll just mess around somewhere. I really didn't think that expeditions to the Maine jungle would be easier to prepare than for a wedding.";
			link.l1.go = "LongHappy_14";
		break;
		
		case "LongHappy_14":
			DialogExit();
			SetLaunchFrameFormParam("Several hours have passed...", "", 0.1, 3.0);
			LaunchFrameForm();
			WaitDate("", 0, 0, 0, 4, 0);
			LongHappy_IslaTesoroRemoveGoods();
			npchar.dialog.currentnode = "LongHappy_15";
			LAi_SetActorType(npchar);
			LAi_ActorDialogDelay(npchar, pchar, "", 4.0);
		break;
		
		case "LongHappy_15":
			dialog.text = "We are done here, Charles, alright! I arranged everything, believe me - it will be wonderful! One thing is embarrassing: the local tavern burned down during some feast a week ago. But it was almost rebuilt, bigger and better than the old one, alright! We should all fit.";
			link.l1 = "I do hope we will not burn this one. I really liked the 'Old Woodpecker'! Anyway, we still have a lot to do. It's time to set sail. And yes, Mary - you're the best, do you know it, right?";
			link.l1.go = "LongHappy_16";
		break;
		
		case "LongHappy_16":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "LongHappy_GirlNorm", 5.0);
			AddQuestRecord("LongHappy", "12");
			pchar.questTemp.LongHappy = "marry_wait";
			pchar.questTemp.LongHappy.DrinkReady = "true";
		break;
		
		case "LongHappy_17":
			dialog.text = "So here we go, huh? The guests arrived, the church is ready. I know that we're closer than many spouses, and these are just a few important words in a beautiful hall, but damn me - in that ancient, aboriginal city I was less worried, alright!";
			link.l1 = "It's absolutely normal, my love, absolutely normal. I'm nervous too. I think,  father Benoit is already waiting, I'll go to him and find out when the service will begin.";
			link.l1.go = "LongHappy_18";
		break;
		
		case "LongHappy_18":
			dialog.text = "Okay, I'll walk around the town for a while, want to get ready, alright! Charles, do you understand that there will be no turning back?";
			link.l1 = "Mary, dear, for me, there is no turning back since we've met. I've been waiting for this day with all my heart. Don't worry, everything will be fine.";
			link.l1.go = "LongHappy_19";
		break;
		
		case "LongHappy_19":
			DialogExit();
			pchar.GenQuest.CannotWait = true;//запрет ожидания
			LAi_ActorRunToLocation(npchar, "reload", "reload4_back", "none", "", "", "OpenTheDoors", 5.0);
			AddQuestRecord("LongHappy", "14");
			AddQuestUserData("LongHappy", "sName", "Mary");
		break;
		
		case "LongHappy_20":
			dialog.text = "Yes.";
			link.l1 = "";
			link.l1.go = "LongHappy_21";
		break;
		
		case "LongHappy_21":
			DialogExit();
			sld = characterFromId("Benua");
			sld.dialog.currentnode = "LH_abbat_27";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "LongHappy_22":
			dialog.text = "Yes.";
			link.l1 = "";
			link.l1.go = "LongHappy_23";
		break;
		
		case "LongHappy_23":
			DialogExit();
			sld = characterFromId("Benua");
			sld.dialog.currentnode = "LH_abbat_29";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "LongHappy_24":
			dialog.text = "Yes.";
			link.l1 = "";
			link.l1.go = "LongHappy_25";
		break;
		
		case "LongHappy_25":
			DialogExit();
			sld = characterFromId("Benua");
			sld.dialog.currentnode = "LH_abbat_31";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "LongHappy_26":
			dialog.text = "";
			link.l1 = "I, Charles Henry de Maure, chevalier de Monper, take you, Mary Casper, to be my wife, to have and to hold, from this day forward, for better and for worse, for richer and for poorer, in sickness and in health, until death do us apart. According to God's Holy Law, in the presence of God, I make this vow.";
			link.l1.go = "LongHappy_27";
		break;
		
		case "LongHappy_27":
			dialog.text = "I, Mary Casper, take you, Charles de Maure, to be my husband, to have and to hold, from this day forward, for better and for worse, for richer and for poorer, in sickness and in health, until death do us apart. According to God's Holy Law, in the presence of God, I make this vow.";
			link.l1 = "";
			link.l1.go = "LongHappy_28";
		break;
		
		case "LongHappy_28":
			DialogExit();
			sld = characterFromId("Benua");
			sld.dialog.currentnode = "LH_abbat_33";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "LongHappy_29":
			dialog.text = "Amen.";
			link.l1 = "";
			link.l1.go = "LongHappy_30";
		break;
		
		case "LongHappy_30":
			DialogExit();
			sld = characterFromId("Benua");
			sld.dialog.currentnode = "LH_abbat_35";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "LongHappy_31":
			dialog.text = "This is unbelievable, alright! I'm... I'm crying, I'm sorry Charles, I will... my nose has turned red, right?";
			link.l1 = "Mary de Maure, my wife, you are beautiful on this day and on any other!";
			link.l1.go = "LongHappy_32";
		break;
		
		case "LongHappy_32":
			if (CheckAttribute(pchar, "questTemp.LongHappy.MarrySP")) dialog.text = "Thank you, Charles, thank you... Everything is so solemn and wonderful! This is the best day of my life, alright!!! Look, how happy is everyone around! But, it's time for you to walk around the guests and accept congratulations! Как закончишь - возвращайся - заглянем к ребятам в таверну.";
			else dialog.text = "Thank you, Charles, thank you... Everything is so solemn and wonderful! This is the best day of my life, alright!!! Look, how happy is everyone around! But, it's time for you to walk around the guests and accept congratulations! As you finish, come back, we are being waited in Sharptown.";
			link.l1 = "I'll do it right away, sweetheart. One kiss and I go!";
			link.l1.go = "LongHappy_33";
		break;
		
		case "LongHappy_33":
			DialogExit();
			LongHappy_MarryKiss();
		break;
		
		case "LongHappy_34":
			dialog.text = "Charles, my love, have you already talked to the guests?";
			link.l1 = "Not yet, be patient, sweetheart, I'll back soon.";
			link.l1.go = "LongHappy_34_1";
			link.l2 = "Yes, I've never listened to so many congratulations at once. And you know what - most of them spoke sincerely!";
			link.l2.go = "LongHappy_35";
		break;
		
		case "LongHappy_34_1":
			DialogExit();
			npchar.dialog.currentnode = "LongHappy_34";
		break;
		
		case "LongHappy_35":
			if (CheckAttribute(pchar, "questTemp.LongHappy.MarrySP")) 
			{
				dialog.text = "Yes, Yes! They also told me so many pleasant things! Not everyone, of course, some people are clearly surprised by my outfit, alright! But I am so happy that I even isn't able to hear a half of everything. And in general, everyone is so cute. Charles, guys in the tavern have already been waiting for us - will we go to them? They will be happy to congratulate their captain, alright!";
				link.l1 = "We are going right now. But I would like to end this day in a more romantic place than the room in the port tavern. I hope, my wife, you don't mind spending this night in our cabin? Moreover, now there is no watch on a ship...";
			}
			else
			{
				dialog.text = "Yes, Yes! They also told me so many pleasant things! Not everyone, of course, some people are clearly surprised by my outfit, alright! But I am so happy that I even isn't able to hear a half of everything. And in general, everyone is so cute. Charles! But we are being waited in Sharptown, when we sail?";
				link.l1 = "Right now. We can't allow our guests to drink all the supplies! I hope, my wife, that you don't mind of spending this night in our cabin?";
			}
			link.l1.go = "LongHappy_36";
		break;
		
		case "LongHappy_36":
			dialog.text = "Even in a hut on a desert island, but only with you, you know it!";
			if (CheckAttribute(pchar, "questTemp.LongHappy.MarrySP")) link.l1 = "I know. I love you too. Let's go until boys drink the whole rum and set the tavern on fire.";
			else link.l1 = "I do. I love you to. Then - set sail!";
			link.l1.go = "LongHappy_37";
		break;
		
		case "LongHappy_37":
			DialogExit();
			npchar.dialog.currentnode = "LongHappy_38";
			LongHappy_MarryComplete();
		break;
		
		case "LongHappy_38":
			dialog.text = "Oh my dear, I'm so happy! Today is a wonderful day...";
			link.l1 = "";
			link.l1.go = "LongHappy_38_1";
		break;
		
		case "LongHappy_38_1":
			DialogExit();
			npchar.dialog.currentnode = "LongHappy_38";
		break;
		
		case "LongHappy_39":
			dialog.text = "Tear off his unwashed head, Charles!";
			link.l1 = "";
			link.l1.go = "LongHappy_40";
		break;
		
		case "LongHappy_40":
			DialogExit();
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.Angerran")) // fix 02-04-20
			{
				sld = characterFromId("Angerran");
				sld.dialog.currentnode = "Shivo_6";
			}
			else 
			{
				sld = characterFromId("LH_Dussak");
				sld.dialog.currentnode = "Dussak_5";
			}
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;
		
		case "LongHappy_41":
			dialog.text = "I'm fine, alright! How is Nathan, is he alive?";
			link.l1 = "So much blood... Dannie, is he breathing? I see him breathing!";
			link.l1.go = "LongHappy_42";
		break;
		
		case "LongHappy_42":
			DialogExit();
			sld = characterFromId("Danielle");
			sld.dialog.currentnode = "Danielle_9";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;
		
		case "LongHappy_43":
			dialog.text = "Faster, dear, do not waste time!";
			link.l1 = "";
			link.l1.go = "LongHappy_43_1";
		break;
		
		case "LongHappy_43_1":
			DialogExit();
			npchar.dialog.currentnode = "LongHappy_43";
		break;
		
		case "LongHappy_44":
			dialog.text = "We won, alright! Forgive me, I'm late. We were stuck upstairs, there was a dozen of these bastards, so I was a bit busy!";
			link.l1 = "It's fine, I handled it. I'm happy I was able to finish that story with Jacques... finally. He's got what he deserved.";
			link.l1.go = "LongHappy_45";
		break;
		
		case "LongHappy_45":
			dialog.text = "Then finish here and go back to Sharptown! We should check how is Nathan, alright! He risked his life for us!";
			link.l1 = "You're right, my love. Go, I'm right behind you.";
			if (CheckAttribute(pchar, "questTemp.LongHappy.Terrax.Prisoner")) link.l1.go = "LongHappy_46";
			else link.l1.go = "LongHappy_48";
		break;
		
		case "LongHappy_46":
			dialog.text = "By the way, honey, we found Marcus, alright! He was in the cargo hold, bound and unconscious.";
			link.l1 = "He's alive?";
			link.l1.go = "LongHappy_47";
		break;
		
		case "LongHappy_47":
			dialog.text = "He is wounded, but he will be okay. You can’t easily break our baron, alright! He's just woken up and is already eager for battle.";
			link.l1 = "This is our old Marcus! Well, finish here and to the shore.";
			link.l1.go = "LongHappy_48";
		break;
		
		case "LongHappy_48":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "LongHappy_BarbExit", -1);
		break;
		
		case "LongHappy_49":
			if (CheckAttribute(pchar, "questTemp.LongHappy.Tichingitu_died") && CheckAttribute(pchar, "questTemp.LongHappy.Jino_died"))
			{
				dialog.text = "I'm so sorry, Charles, alright, I... I went for a walk. I saw that you were back, I heard that everyone was alive with a victory, but I... But what's wrong with me, alright!";
				link.l1 = "All is going to be alright, love, all is going to be alright. I'm sad too. But we won, and Jacques Barbason paid for everything he's done.";
				link.l1.go = "LongHappy_50";
			}
			else
			{
				if (CheckAttribute(pchar, "questTemp.LongHappy.Jino_died"))
				{
					dialog.text = "I feel so bad about Gino, Charles, alright! When I found out, I didn’t believe it! How are you?";
					link.l1 = "I can't believe it too... it turned out so stupid, I didn't imagine this day like that.";
				}
				else
				{
					dialog.text = "We won again, alright! My husband My husband is a storm for rebellious barons of the Brethren of the Coast! Friends are alive and enemies are dead - a glorious gift, alright!";
					link.l1 = "Yeah, such a celebration, but we made it, my love. We made it.";
				}
				link.l1.go = "LongHappy_50";
			}
		break;
		
		case "LongHappy_50":
			dialog.text = "You barely stand on your feet, alright! Come on, Dannie found us a house here on the outskirts, I don’t want to return to the ship now. We'll sit and drink to our fallen friends. This all is too much for sober head, alright.";
			link.l1 = "Yes, Mary, let's go.";
			link.l1.go = "LongHappy_51";
		break;
		
		case "LongHappy_51":
			DialogExit();
			LongHappy_LogBook();
			DoQuestCheckDelay("LongHappy_MarryFinalizing", 0.5);
		break;
		
		case "LongHappy_52":
			if (CheckAttribute(pchar, "questTemp.LongHappy.Jino_died"))
			{
				dialog.text = "I feel so bad about Gino, Charles, alright! When I found out, I didn’t believe it! How are you?";
				link.l1 = "I can't believe it too... it turned out so stupid, I didn't imagine this day like that.";
			}
			else
			{
				dialog.text = "Sorry that I'm late, my dear, alright! I went for a walk, then I saw how you approached and ran as fast as I could! Dannielle put me out when Gino said 'the danger is over', alright! I'm so glad that everything is fine now!";
				link.l1 = "Me too, darling. And we won. Barbason is dead, barons are gathering what's left of their crews. The fight is over.";
			}
			link.l1.go = "LongHappy_53";
		break;
		
		case "LongHappy_53":
			dialog.text = "Charles, I see you barely standing on your feet, but no one can find Tichingitu.";
			link.l1 = "Jan gave me some kind of tip... It seems to me that our harsh maskogue went on the razzle-dazzle. Let’s take a walk to Sabo-Matila Cove, a few people saw him leaving in that direction.";
			link.l1.go = "LongHappy_54";
		break;
		
		case "LongHappy_54":
			DialogExit();
			LongHappy_LogBook();
			chrDisableReloadToLocation = false;
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			pchar.quest.longhappy_shoregirl.win_condition.l1 = "location";
			pchar.quest.longhappy_shoregirl.win_condition.l1.location = "Shore_ship1";
			pchar.quest.longhappy_shoregirl.function = "LongHappy_SetShoreGirl";
		break;
		
		case "LongHappy_55":
			dialog.text = "Well, that's our stern native, alright! Come on, Dannie found for us a house here on the outskirts - you already are sleepwalking, Charles, alright!";
			link.l1 = "There is ... kidnap me, my beautiful squaw. And let it all seem like a bad dream tomorrow.";
			link.l1.go = "LongHappy_56";
		break;
		
		case "LongHappy_56":
			DialogExit();
			DoQuestCheckDelay("LongHappy_MarryFinalizing", 0.5);
		break;
		
		case "LongHappy_57":
			dialog.text = "Don't get me wrong, my husband, in the church everything was just luxurious, but here the atmosphere is clearly more soulful, alright! Well, that's all, Charles, now all the troubles are behind, we can relax.";
			link.l1 = "Well, it's not quite 'all', my wife - our life goes on together! It can generally be said  that it just has begun today. So, let's go, have a drink with our guys, and then - well, you remember: the cabin, the wine, and us...";
			link.l1.go = "LongHappy_58";
		break;
		
		case "LongHappy_58":
			DialogExit(); // телепорт в каюту
			DoQuestReloadToLocation("My_Cabin", "rld", "loc1", "LongHappy_InSPcabin");
		break;
		
		case "LongHappy_59":
			dialog.text = "My husband... It sounds so sweet, alright! Now you are mine, forever!";
			link.l1 = "I’ve been yours for a long time already, and will be forever, my love...";
			link.l1.go = "LongHappy_60";
		break;
		
		case "LongHappy_60":
			DialogExit();
			DoQuestCheckDelay("Mary_LoveSex", 1.0);
			npchar.dialog.currentnode = "LongHappy_61";
			LAi_SetStayType(npchar);
		break;
		
		case "LongHappy_61":
			dialog.text = "I am so happy, Charles! And now, we have to keep moving again, right?";
			link.l1 = "Sure, sweetheart! Side by side, together and forever!";
			link.l1.go = "LongHappy_62";
		break;
		
		case "LongHappy_62":
			DialogExit();
			LAi_SetOfficerType(npchar);
			npchar.dialog.currentnode = "Mary_officer";
			DoQuestReloadToLocation("FortFrance_town", "reload", "reload1", "LongHappy_InSPComplete");
		break;
		
		//--> ----------------------------------- офицерский блок ------------------------------------------
		case "Mary_officer":
			// если шлялся по борделям - устроит небольшой скандал 
			if (sti(pchar.GenQuest.BrothelCount) >= 3 && LAi_grp_playeralarm == 0)
			{
				dialog.Text = ""+pchar.name+"! I need to talk with you, alright! Seriously!";
				Link.l1 = "What happened, Mary? Is there a problem?";
				Link.l1.go = "brothel";
				break;
			}
			ref rLoc = &Locations[FindLocation(pchar.location)];
			dialog.text = LinkRandPhrase("I am listening, my dear captain!","Yes, "+pchar.name+", I am all ears!","Do you have any assignment for me, "+pchar.name+"?");
			if (CheckAttribute(pchar, "questTemp.Dolly_Tieyasal") && !CheckAttribute(npchar, "quest.Tieyasal"))
			{
				Link.l4 = "Mary, I am going to visit the old Indian city Tayasal. I won't lie to you: this trip is very dangerous and even more - it includes teleportation through the idol I told you about. Will you... follow me?";
				Link.l4.go = "tieyasal";
			}
			////////////////////////казначей///////////////////////////////////////////////////////////
			// boal отчёт о корабле
			if(CheckAttribute(NPChar, "treasurer") && NPChar.treasurer == 1)
			{
			    Link.l11 = "Mary, give me a full ship report.";
			    Link.l11.go = "QMASTER_1";
				
			    // Warship. Автозакупка товара
				Link.l12 = "I want you to purchase certain goods every time we are docked.";
				Link.l12.go = "QMASTER_2";
			}

			if (CheckAttribute(npchar, "quest.fugas"))
			{
				Link.l3 = "Mary, I need your advice.";
				Link.l3.go = "fugas";
			}
			Link.l1 = "Mary, I have an order for you...";
            Link.l1.go = "stay_follow";
			if (pchar.location == Get_My_Cabin() && !CheckAttribute(npchar, "quest.daily_sex"))
			{
				Link.l2 = RandPhraseSimple("Dear, I want you right now. Are you okay with that?","Mary, how about to... stay together for a while? Just two of us.");
				Link.l2.go = "cabin_sex";
			}
			if (rLoc.type == "tavern" && !CheckAttribute(npchar, "quest.daily_sex") && sti(pchar.money) >= 10)
			{
				Link.l2 = RandPhraseSimple("Mary, let's take a room and stay together?","Love, I want to stay with you in private... how about to take a room and forget about everything for a few hours?");
				Link.l2.go = "room_sex";
			}
			link.l9 = "It's nothing so far, Mary.";
			link.l9.go = "exit";
			NextDiag.TempNode = "Mary_officer";
		break;
		
		/////////////////////////// ответы для казначея ///////////////////////////////////
		case "QMASTER_1":
			dialog.Text = "Charles, she's a beauty, alright! We fixed that teeny-tiny hole below the waterline and dried the sails. Wha- What did you expect? Don't look at me like that, I've never studied to be a purser.";
			Link.l1 = "Sorry, Mary, I really didn't think it through.";
			Link.l1.go = "exit";
		break;	

		case "QMASTER_2":
			dialog.text = "Charles, but I am all good! I already got my wardrobe and my blade. But thanks for asking, it's so nice of you, alright!";
			link.l1 = "But I don't even... Whatever, forget about it, dear, we're good.";
			link.l1.go = "exit";
		break;

		case "stay_follow":
            dialog.Text = "Orders?";
            Link.l1 = "Stand here!";
            Link.l1.go = "Boal_Stay";
            Link.l2 = "Follow me and keep up!";
            Link.l2.go = "Boal_Follow";
			sGun = GetCharacterEquipByGroup(NPChar, GUN_ITEM_TYPE);
			if(sGun != "")
			{
				rItm = ItemsFromID(sGun);
				if(CheckAttribute(NPChar, "chr_ai.bulletNum") && sti(NPChar.chr_ai.bulletNum) > 1)
				{
					Link.l3 = "Mary, change ammo for firearms.";
					Link.l3.go = "SetGunBullets";
				}	
			}		
		break;
		
		case "SetGunBullets":
			Dialog.Text = "Choosing the type of ammo:";
			sGun = GetCharacterEquipByGroup(NPChar, GUN_ITEM_TYPE);
			rItm = ItemsFromID(sGun);
			makearef(rType, rItm.type);	
			for (i = 0; i < sti(NPChar.chr_ai.bulletNum); i++)
			{
				sAttr = GetAttributeName(GetAttributeN(rType, i));
				sBullet = rItm.type.(sAttr).bullet;
				rItem = ItemsFromID(sBullet);								
				attrL = "l" + i;
				Link.(attrL) = GetConvertStr(rItem.name, "ItemsDescribe.txt");;
				Link.(attrL).go = "SetGunBullets1_" + i;
			}
		break;	

		case "SetGunBullets2":
			i = sti(NPChar.SetGunBullets) + 1; 
			sGun = GetCharacterEquipByGroup(NPChar, GUN_ITEM_TYPE);
			rItm = ItemsFromID(sGun);
			sAttr = "t" + i;
			sBullet = rItm.type.(sAttr).bullet;
			LAi_SetCharacterUseBullet(NPChar, sBullet);
			LAi_GunSetUnload(NPChar);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DeleteAttribute(NPChar,"SetGunBullets");
			DialogExit();
		break;		
		
        case "Boal_Stay":
            Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(Npchar.id);
            AddDialogExitQuestFunction("LandEnc_OfficerStay");
            dialog.Text = "At once, my captain!";
            Link.l1 = "...";
            Link.l1.go = "Exit";
            Npchar.chr_ai.tmpl = LAI_TMPL_STAY;
        break;
        
        case "Boal_Follow":
            SetCharacterTask_FollowCharacter(Npchar, PChar);
            dialog.Text = "At once, my captain!";
            Link.l1 = "...";
            Link.l1.go = "Exit";
        break;
		//<-- ----------------------------------- офицерский блок ----------------------------------------
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}