// Даниэль Хоук - жена Натаниэля Хоука
void ProcessDialogEvent()
{
	ref NPChar, sld, rItm, rItem;
	aref Link, NextDiag, rType;
	int i;
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
		case "First time": //первая встреча - знакомство
			PlaySound("VOICE\Russian\saga\Denny Hawk-02.wav");
			dialog.text = "Wait, handsome! I think that we can have a talk.";
			link.l1 = "Do I know you? Anyway, I always have few extra hours for a lady.";
			link.l1.go = "meeting";			
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting":
			PlaySound("VOICE\Russian\saga\Denny Hawk-01.wav");
			dialog.text = "Don't make plans, captain. Find yourself some younger fool girl for extra few hours. And I have got business for you. I am married actually. My husband's name is Nathaniel Hawk.";
			link.l1 = "Isn't that something! So you must be that bit... eh, Dannie Hawk, mister Swanson mentioned you.";
			link.l1.go = "meeting_1";
		break;
		
		case "meeting_1":
			dialog.text = "In the flesh. Yes, I am aware that the Forest Devil doesn't think much of me, the feeling is mutual, but he had to warn you that I wear my saber not because it's pretty. So, cut to the chase, son!\nI have been shadowing Swanson and his visitors for a while because he was the one who sent my husband in jungles to die. I thought that he was working with Jackman, but now I see that he is not. I was hiding under the window all the time. Couldn't eavesdrop everything, but learned a lot of useful information\nAre you really willing to find my husband and kick Jackman's ass? Or were you only talking cheap?";
			link.l1 = "Eavesdropping is bad, madame Hawk. But I will forgive you for that if you talk to me in the more respectful way. Will I find Hawk or not, it's my concern only. Speak if you have something useful to say or leave me if you don't. I won't ask twice.";
			link.l1.go = "meeting_2";
		break;
		
		case "meeting_2":
			dialog.text = "A-ha, such a hothead! Come on, captain... My temper is not really comfortable that's for sure. I see that you are not a coward and you know your worth. So... let's be on familiar. I promise you that I will be careful with what I am saying. I need you and you need me. We share goals. Take me to your crew and you won't regret it. I will serve you with good faith and fidelity until we find Nathan, you have my word.";
			link.l1 = "Consider yourself accepted... Dannie. Swanson told me that you have already been searching for your husband. Have you found anything?";
			link.l1.go = "meeting_3";
		break;
		
		case "meeting_3":
			dialog.text = "Not much, but enough to accuse Jackman of lying. The bastard said that mines guards, my Nathan faced, didn't take prisoners. It is true that no one has seen Hawk's corpse at the bay. And how could they, because he actually was taken to the mines as a prisoner. Snake Eye, a shaman of Miskito people, found him there\nHe also arranged an escape. But where is Hawk now stays unknown. The shaman was mumbling something about some Kukulcan who could eat him, but I didn't understand anything. Besides, the red skin made pretty clear that white women are nothing more but a joke for him. You should speak with him, maybe he will be more conversable";
			link.l1 = "That's is something! Such news make me happier. Where can I find this Indian?";
			link.l1.go = "meeting_4";
		break;
		
		case "meeting_4":
			dialog.text = "There is a village deep in the jungles. We need to land at Amatique Bay and go west trough jungles. I will show the way if you don't find it yourself. The stone idol stands not far from the village and savages revere it as their god. I have been there several times. Nothing special really. Just a simple stone covered by moss.";
			link.l1 = "Interesting. Fine, let's go. We will talk with the shaman and we will see what to do next. Ready?";
			link.l1.go = "meeting_5";
		break;
		
		case "meeting_5":
			dialog.text = "Sure! Of course, I am ready. I have been travelling all the time since I've left Maroon Town. Besides I don't want to be just another your passenger.";
			link.l1 = "Fine. Let's go to the ship.";
			link.l1.go = "meeting_6";
		break;
		
		case "meeting_6":
			dialog.text = "Aye-aye, captain!";
			link.l1 = "...";
			link.l1.go = "meeting_7";
		break;
		
		case "meeting_7":
			DialogExit();
			chrDisableReloadToLocation = false;//открыть локацию
			npchar.quest.OfficerPrice = sti(pchar.rank)*700;
			npchar.OfficerWantToGo.DontGo = true; //не пытаться уйти
			npchar.CompanionDisable = true; //нельзя в компаньоны - чтобы не утонула
			LAi_SetImmortal(npchar, false);
			npchar.HalfImmortal = true; //чтобы не убили в сухопутном бою
			npchar.loyality = MAX_LOYALITY;
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, true);
			npchar.Payment = true;
			npchar.DontClearDead = true;
			NextDiag.CurrentNode = "Danielle_officer";
			npchar.HoldEquip = true; // лесник -  не отдавать саблю и пистоль																					 
			SaveCurrentNpcQuestDateParam(npchar, "HiredDate");
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			AddQuestRecord("BaronReturn", "2");
			Saga_CreateSnakeEye();
			//выбираем амулеты
			pchar.questTemp.Saga.BaronReturn.Indian = "indian_"+(rand(10)+1);
			pchar.questTemp.Saga.BaronReturn.Amulet = "amulet_"+(rand(10)+1);
			pchar.questTemp.Saga.BaronReturn.Obereg = "obereg_"+(rand(10)+1);
			// на локацию с истуканом
			npchar.quest.talk = "dolly";
			pchar.quest.Saga_Dolly.win_condition.l1 = "location";
			pchar.quest.Saga_Dolly.win_condition.l1.location = "Pearl_jungle_03";
			pchar.quest.Saga_Dolly.function = "Saga_DannyTalk";
			AddCharacterExpToSkill(pchar, "Fortune", 50);//везение
			AddCharacterExpToSkill(pchar, "Leadership", 50);
			npchar.greeting = "danny_1";
		break;
		
		// у истукана в джунглях
		case "Dolly":
			dialog.text = ""+pchar.name+"! Come on! I will show you that stone idol which the Indian shaman was talking about. Just a usual stone pillar. Let's go!";
			link.l1 = "...";
			link.l1.go = "Dolly_1";
		break;
		
		case "Dolly_1":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocator(npchar, "item", "torch1", "Saga_ShowDolly", -1);
		break;
		
		case "Dolly_2":
			dialog.text = "Hey! Take a look, it is just a stone statue. Nothing special...";
			link.l1 = "I see... Though the figure at the top is a bit sinister, don't you think? ";
			link.l1.go = "Dolly_3";
		break;
		
		case "Dolly_3":
			dialog.text = "All Indian statues are scary and evil. I have seen something like that before. They are all the same. Fine, let's go, the village is near!";
			link.l1 = "Let's go!";
			link.l1.go = "Dolly_4";
		break;
		
		case "Dolly_4":
			chrDisableReloadToLocation = false;//открыть локацию
			DialogExit();
			LAi_SetOfficerType(npchar);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			npchar.dialog.currentnode = "Danielle_officer";
		break;
		
		// у мискито
		case "SnakeEye":
			dialog.text = "So, what do you say, "+pchar.name+"? What did that redskin ventriloquist tell you? Did you understand anything from his philosophizing?";
			link.l1 = "Were you eavesdropping again, Dannie?";
			link.l1.go = "SnakeEye_1";
		break;
		
		case "SnakeEye_1":
			dialog.text = "Well... a bit. Yes, yes, we, women are just like that. But you must understand - I worry about my husband. I actually love him. So what? Have you got any ideas?";
			link.l1 = "I am trying to... Yes, it wasn't easy to understand Snake Eye. It seems that the idol which we've seen on our way to the village is some sort of magic portal which can teleport people.";
			link.l1.go = "SnakeEye_2";
		break;
		
		case "SnakeEye_2":
			dialog.text = "";
			link.l1 = "Don't look at me like that. It wasn't my idea, I've got no problems with my head so far. You have asked me what shaman told me so I am telling you.";
			link.l1.go = "SnakeEye_3";
		break;
		
		case "SnakeEye_3":
			dialog.text = "Please, excuse me. I won't look at you like that anymore. Go on.";
			link.l1 = "He said that when Nathan was almost caught by pursuers, he has shown him the statue as the way to rescue, he called it Kukulcan and said that it had eaten Nathan and spat out him. To put it simply, it seems that Nathan was teleported by the statue.";
			link.l1.go = "SnakeEye_4";
		break;
		
		case "SnakeEye_4":
			dialog.text = "God, what the... Me and Nathan have already been in such mess and now it happens again. We had enough of that Indian temple filled with Maya magic...";
			link.l1 = "What did you just say?";
			link.l1.go = "SnakeEye_5";
		break;
		
		case "SnakeEye_5":
			dialog.text = "No, it's nothing, "+pchar.name+", it doesn't matter. Just memories of my heated youth. But how was Nathan able to do that? I mean to teleport? We have just been near that idol, I was walking around it and touching it... it's only a stone!";
			link.l1 = "Snake Eye has told me that the idol lives at midnight. Only then it becomes golden and the spirit of Kukulcan gets into it. It is the time you shouldn't touch it. Or conversely should...";
			link.l1.go = "SnakeEye_6";
		break;
		
		case "SnakeEye_6":
			dialog.text = "Creepy... Now what? Let's wait until midnight and go to the jungle then?";
			link.l1 = "No. The shaman said that the idol not only teleports people but also eats their lives. As i understood it drains their health. Snake Eye has passed three times through these statues and he has healed himself with some unique potion after every teleportation.";
			link.l1.go = "SnakeEye_7";
		break;
		
		case "SnakeEye_7":
			dialog.text = "Have you asked him for this potion?";
			link.l1 = "Sure. But, first, there are only three flasks left and, secondly, he demanded three amulets for each.";
			link.l1.go = "SnakeEye_8";
		break;
		
		case "SnakeEye_8":
			dialog.text = "How about we do this without the potion? Let's go to the statue at night and touch it...";
			link.l1 = "Too risky. I concede that the Indian is a bit out of mind and fools us, but he doesn't look like a psychopath so I believe that he was telling the truth. I recall that you were telling me something about Indian magic... Do you doubt it's existence?";
			link.l1.go = "SnakeEye_9";
		break;
		
		case "SnakeEye_9":
			dialog.text = "Yes, I was. I don't doubt it because I saw it with my own eyes. Yes, I suppose you are right, there is no point in risking.";
			link.l1 = "Exactly. That is why we will find amulets at first, get that wonderful potion from shaman and go to the statue. I will go. Alone.";
			link.l1.go = "SnakeEye_10";
		break;
		
		case "SnakeEye_10":
			dialog.text = "Why is that? And what about me?";
			link.l1 = "And you will stay on my ship and you'll be in charge while I am away. Don't even try to argue, Dannie. There are only three flasks of the potion. It is unknown where the portal leads to in case the shaman was right and this thing works for real. Perhaps, I won't be even able to find Nathan there.";
			link.l1.go = "SnakeEye_11";
		break;
		
		case "SnakeEye_11":
			dialog.text = "You are just like Nathan. All men are the same... Fine, I agree.";
			link.l1 = "It is good that we understand each other. Let's go now, we need to find amulets.";
			link.l1.go = "Dolly_4";
		break;
		
		// перед походом к истукану
		case "teleport":
			dialog.text = "So what? Did you get potions?";
			link.l1 = "Yes. I got potions and instructions. The one thing is left - to go to the idol at midnight and touch it.";
			link.l1.go = "teleport_1";
		break;
		
		case "teleport_1":
			dialog.text = "Are you afraid?";
			link.l1 = "Yes. I am afraid that the shaman may turn out to be crazy and no teleportation will happen.";
			link.l1.go = "teleport_2";
		break;
		
		case "teleport_2":
			dialog.text = "Well-well... Aren't you really scared? Not even a little bit?";
			link.l1 = "Dannie, don't press on me... Sure, I am not feeling confident, it must be confessed.";
			link.l1.go = "teleport_3";
		break;
		
		case "teleport_3":
			dialog.text = "I will go with you.";
			link.l1 = "Are you going to start arguing again? I thought that we had a deal...";
			link.l1.go = "teleport_4";
		break;
		
		case "teleport_4":
			dialog.text = "You got me wrong. I will only stay near you. I will have to be sure that the statue will work... or it won't.";
			link.l1 = "I have got no objections. But don't even think to follow me in case the statue 'eats' me. Did you hear me?";
			link.l1.go = "teleport_5";
		break;
		
		case "teleport_5":
			dialog.text = "I did. I promise that I won't be willful... captain.";
			link.l1 = "Nice. And, Dannie, it seems that you are not that bitch as they say.";
			link.l1.go = "teleport_6";
		break;
		
		case "teleport_6":
			dialog.text = "You don't know me well, "+pchar.name+". Fine, let's not talk about it.";
			link.l1 = "Let's not... Well, now prepare yourself for the night trip!";
			link.l1.go = "Dolly_4";
			npchar.quest.talk = "shadowstar";
			pchar.quest.Saga_Dolly1.win_condition.l1 = "location";
			pchar.quest.Saga_Dolly1.win_condition.l1.location = "Pearl_jungle_03";
			pchar.quest.Saga_Dolly1.win_condition.l2 = "Hour";
			pchar.quest.Saga_Dolly1.win_condition.l2.start.hour = 0.00;
			pchar.quest.Saga_Dolly1.win_condition.l2.finish.hour = 1.00;
			pchar.quest.Saga_Dolly1.function = "Saga_DannyTalk";
		break;
		
		// перед телепортацией
		case "shadowstar":
			dialog.text = "Look, "+pchar.name+"! I swear by all saints, there is an odd light above the statue!";
			link.l1 = "It seems that shaman wasn't lying. And, if the dark doesn't deceive me, the top of the statue doesn't look that stony anymore.";
			link.l1.go = "shadowstar_1";
		break;
		
		case "shadowstar_1":
			dialog.text = "Exactly... It looks like it was made of gold! Incredible!";
			link.l1 = "The time has come, Dannie. Wish me luck and cross your fingers for me. Don't come close to the idol! Stay here.";
			link.l1.go = "shadowstar_2";
		break;
		
		case "shadowstar_2":
			dialog.text = "Good luck, "+pchar.name+". let's hope that it will work... Have you prepared shaman's potion?";
			link.l1 = "Yes, I have. All will be fine, Dannie. Well, here I go! (Press T to activate the idol)";
			link.l1.go = "shadowstar_3";
		break;
		
		case "shadowstar_3":
			DialogExit();
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			DoQuestReloadToLocation(pchar.location, pchar.location.group, pchar.location.locator, "");
		break;
		
		// прибыл назад 
		case "arrive":
			dialog.text = "A-a-ah?! Fuck! What is this monster, God damn it?! Screw you! I have seen worse creatures in my life including Van der Decken! Now I'll give you what you're asking for!";
			link.l1 = "(faintly) Dannie, wait! Stop it! Now!";
			link.l1.go = "arrive_1";
		break;
		
		case "arrive_1":
			dialog.text = "Ah?! What did you say?! Dannie?";
			link.l1 = "(faintly) Stop that immediately! Hold your saber! Let me take this thing off!";
			link.l1.go = "arrive_2";
		break;
		
		case "arrive_2":
			dialog.text = "Damn, this thing sounds like... "+pchar.name+"?!";
			link.l1 = "(faintly) Oh-oh... You don't say!";
			link.l1.go = "arrive_3";
		break;
		
		case "arrive_3":
			DialogExit();
			RemoveCharacterEquip(pchar, CIRASS_ITEM_TYPE);
			DoQuestCheckDelay("Pearl_TeleportArrive_1", 1.5);
		break;
		
		case "arrive_4":
			dialog.text = "Fuh, you have almost scared me to death! I was close to start chopping you with my saber!";
			link.l1 = "I saw that... and why are you so fiery, huh?";
			link.l1.go = "arrive_5";
		break;
		
		case "arrive_5":
			dialog.text = "That is who I am... Oh, my heart is still ready comes out of chest...";
			link.l1 = "Dannie where are we now? Not far from the Miskito village, right?";
			link.l1.go = "arrive_6";
		break;
		
		case "arrive_6":
			dialog.text = "And where else could we be! There is a statue which made you disappear. That was spectacular! I will remember that for the rest of my life.";
			link.l1 = "I see, you have been waiting for me since then?";
			link.l1.go = "arrive_7";
		break;
		
		case "arrive_7":
			dialog.text = "Tell me then what else was I supposed to do? After the statue had eaten you, I only hoped that one day it will spit you out back. Besides, Snake Eye said that this is exactly what most likely would happen\nI lived with the Miskito and watched the idol every day. Why are we even talking about such hogwash? Go on! What happened out there? Where have you been?";
			link.l1 = "Dannie, this story is too long, I have seen a lot... But to get it off your chest I'll tell you that I have found Nathaniel!";
			link.l1.go = "arrive_8";
		break;
		
		case "arrive_8":
			dialog.text = "Have you found Nathan? Where is he? How is he?!";
			link.l1 = "I won't lie - he is alive but he is really feeling bad. He had no potion of Comanche and the idol has drained all of his health. He is lying in a cabin of some old and broken vessel at the strange Island of Abandoned Ships. I was teleported there too, so Snake Eye was right!";
			link.l1.go = "arrive_9";
		break;
		
		case "arrive_9":
			dialog.text = "Poor Nathan... Where is that damn island? How to get there?! Through the idol only? I will buy every single health potion from Miskito and go there this night! I will make it somehow...";
			link.l1 = "Stop! Wait! Nathan is ill but there is no threat to his life. One lad is looking after him and feeding him. If you will go through teleport you will become a ruin and the Island is dangerous. It is too risky!";
			link.l1.go = "arrive_10";
		break;
		
		case "arrive_10":
			dialog.text = "So what are you suggesting? To do nothing while Nathan is suffering or dying perhaps?";
			link.l1 = "Stop you hysterics. First, I told you that Nathan is ill but he is not dying. I have spoken to him. Secondly, I am going to sail to the Island and you will go with me.";
			link.l1.go = "arrive_11";
		break;
		
		case "arrive_11":
			dialog.text = "Do you know where is that Island?";
			link.l1 = "Sure, I do! I have found there not only Nathan but also Shark Dodson. Now I have got fair coordinates of the Island and a sailing directions to bypass the reefs around it. And now we are going back to the ship and sail to Blueweld...";
			link.l1.go = "arrive_12";
		break;
		
		case "arrive_12":
			dialog.text = "For what purpose? Why can't we sail straight to the Island now?";
			link.l1 = "Dannie, I need to organize an expedition. There is a huge lack of provision on the Island so I will buy as much as I can. Then I will have to choose a ship to sail there, not any ship will be able to bypass the Island's reefs. And I also want to talk with Swanson first...";
			link.l1.go = "arrive_13";
		break;
		
		case "arrive_13":
			dialog.text = "";
			link.l1 = "It won't take too long to prepare. The Island is not far from here, it's north-west from Havana, right to the Gulf of Mexico.";
			link.l1.go = "arrive_14";
		break;
		
		case "arrive_14":
			dialog.text = "Fine... Let it be. You have found Nathan and that's the most important. Thank you! Is he feeling bad there?";
			link.l1 = "Well... he is ill. And in addition he is depressed and desperate. He missed you. Yes, Nathan asked me to tell you that he loves you very much.";
			link.l1.go = "arrive_15";
		break;
		
		case "arrive_15":
			dialog.text = "(wiping away a tear) Old fool! He had never listened to me... "+pchar.name+", let's head to the ship! I want to sail as quickly as possible!";
			link.l1 = "Sure, Dannie. And I will tell you about my adventures. Let's go!";
			link.l1.go = "Dolly_4";
			AddQuestRecord("BaronReturn", "9");
			LAi_LocationDisableOfficersGen("Pearl_jungle_03", false); // пускать офицеров в локу телепорта
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешить драться
			setCharacterShipLocation(pchar, "Shore9"); // калеуче
			setWDMPointXZ("Shore9"); // корабль в бухту Аматике
			bNoEatNoRats  = false; // еду и крыс включить
		break;
		
		// в LSC у причала
		case "nathaniel":
			dialog.text = "Yes, I have never seen any place like that before. This is a whole island made of ships!";
			link.l1 = "I have told you about it, Dannie...";
			link.l1.go = "nathaniel_1";
		break;
		
		case "nathaniel_1":
			dialog.text = "But now I can see it with my own eyes. Fine. Tell me where to find Nathaniel?";
			link.l1 = "He is inside one of the ships. But you must swim there.";
			link.l1.go = "nathaniel_2";
		break;
		
		case "nathaniel_2":
			dialog.text = "I don't care. Tell me how to get to this ship.";
			link.l1 = "Dannie, calm down. You and Nathan have been waiting for a long time so wait just a bit more now! I will lead you to him, you will never find him yourself. I don't want you to run against Narwhals or Rivados, you will start to argue with them and it won't end well.";
			link.l1.go = "nathaniel_3";
		break;
		
		case "nathaniel_3":
			dialog.text = "Fine, let's go then. I will follow you.";
			link.l1 = "Don't forget that we will have to swim a lot.";
			link.l1.go = "nathaniel_4";
		break;
		
		case "nathaniel_4":
			dialog.text = "It's fine, I can handle it.";
			link.l1 = "Glad to hear that... You will see your husband soon!";
			link.l1.go = "nathaniel_5";
		break;
		
		case "nathaniel_5":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			pchar.quest.LSC_Danny_Natan.win_condition.l1 = "location";
			pchar.quest.LSC_Danny_Natan.win_condition.l1.location = "FernandaDiffIndoor";
			pchar.quest.LSC_Danny_Natan.function = "LSC_DannyAndNatan";
			AddQuestRecord("LSC", "15");
			// следующая нода
			if (CheckCharacterItem(pchar, "keys_skel")) // идет Оле
			{
				sld = characterFromId("Ole");
				LAi_SetActorType(sld);
				LAi_ActorDialog(sld, pchar, "", -1, 0);
			}
			else
			{
				if (GetCharacterIndex("Mary") != -1) // иначе Мэри
				{
					sld = characterFromId("Mary");
					LAi_SetActorType(sld);
					LAi_ActorDialog(sld, pchar, "", -1, 0);
				}
				else // иначе завершение
				{
					chrDisableReloadToLocation = false;
					LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
				}
			}
		break;
		
		case "nathaniel_6":
			dialog.text = "Nathaniel... Nathan! Damn it! My love...";
			link.l1 = "...";
			link.l1.go = "nathaniel_7";
		break;
		
		case "nathaniel_7":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_SetActorType(pchar);
			SetMusic("music_romantic");
			bDisableCharacterMenu = true;//лоченые интерфейсы
			locCameraRotateAroundHero(0.0, 2.0, 0.0, 0.005, 0.0, 2.0, 0.0, 1000);
			DoQuestCheckDelay("LSC_DanielleRomantic", 15.0);
		break;
		
		case "nathaniel_8":
			dialog.text = "Jesus, just look at yourself... Why did you do that to yourself?!..(crying) You never listen to me, never! I told you not to go to that selva! And you have gone there! Why Nathan?!";
			link.l1 = "Dannie... I am sorry. I had no choice, you know that...";
			link.l1.go = "nathaniel_9";
		break;
		
		case "nathaniel_9":
			sld = characterFromId("Blaze");
			dialog.text = "I know that! Oh, God, darling... what has happened with you! (through tears) It is alright, darling, all is gonna be alright... I am here. We will take you to Miskito, to Snake Eye. "+sld.name+"  told me that the shaman will heal you. We have got a ship... Everything is going to be fine!";
			link.l1 = "Dannie, dear... my love! Your presence here has half healed me. We will go wherever you say. If to Snake Eye, then to him.";
			link.l1.go = "nathaniel_10";
		break;
		
		case "nathaniel_10":
			dialog.text = "Pack up your things. Oh, I am so stupid... There are no any things to pack except empty bottles. Nathan...";
			link.l1 = "Dannie...";
			link.l1.go = "nathaniel_11";
		break;
		
		case "nathaniel_11": // перекидываем pchar
			DialogExit();
			LAi_SetStayType(pchar);
			DeleteAttribute(pchar, "GenQuest.MusicContinue");
			SetMainCharacterIndex(GetCharacterIndex("Blaze"));
			PChar = GetMainCharacter();			
			LAi_SetPlayerType(PChar);
			sld = characterFromId("Danielle");
			sld.dialog.currentnode = "nathaniel_12";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "nathaniel_12":
			dialog.text = ""+pchar.name+", you... Forgive me and Nathan for the scene.";
			link.l1 = "Dannie! Forgive you for what? It is alight. Are you ashamed of your feelings?";
			link.l1.go = "nathaniel_13";
		break;
		
		case "nathaniel_13":
			dialog.text = "No, I am not... It just...";
			link.l1 = "No one will never know about this scene. I promise. And no one will know what happened to Nathan. The pirates of Maroon Town will see strong and formidable Nathaniel Hawk!";
			link.l1.go = "nathaniel_14";
		break;
		
		case "nathaniel_14":
			dialog.text = "Thanks... Thank you, "+pchar.name+"! I owe you... Fine, I will take my husband to the ship. Don't worry, I will manage to deliver him, I have remembered the way. I will put him in a bed and I will stay with him. We'll sail to Snake Eye after you will do all you need here. I believe in his ability to heal Nathan.";
			link.l1 = "Fine, Dannie. We won't stay here for long. Are you sure that you don't need help?";
			link.l1.go = "nathaniel_15";
		break;
		
		case "nathaniel_15":
			dialog.text = "I am sure. We will reach the ship. Don't worry, I won't let my husband die!";
			link.l1 = "Dannie, you are... wonderful!";
			link.l1.go = "nathaniel_16";
		break;
		
		case "nathaniel_16":
			dialog.text = "(brushing away a tear) Go... just go, "+pchar.name+"... and please don't stay here for too long!";
			link.l1 = "...";
			link.l1.go = "nathaniel_17";
		break;
		
		case "nathaniel_17":
			chrDisableReloadToLocation = false;//открыть локацию
			bDisableCharacterMenu = false;//лоченые интерфейсы
			EndQuestMovie();
			DialogExit();
			pchar.quest.LSC_NatanPassenger.win_condition.l1 = "ExitFromLocation";
			pchar.quest.LSC_NatanPassenger.win_condition.l1.location = pchar.location;
			pchar.quest.LSC_NatanPassenger.function = "LSC_SetNatanPassenger";
			pchar.quest.Saga_NatanTreatment.win_condition.l1 = "location";
			pchar.quest.Saga_NatanTreatment.win_condition.l1.location = "Miskito_village";
			pchar.quest.Saga_NatanTreatment.function = "Saga_NatanPrepareTreatment";
			pchar.questTemp.Saga.BaronReturn = "shamane";
			AddQuestRecord("BaronReturn", "11");
			// открываем вход к Мэри
			if (GetCharacterIndex("Mary") != -1)
			{
				for (i=0; i<=3; i++)
				{
					LocatorReloadEnterDisable("LostShipsCity_town", "reload6"+i, false);
				}
			}
			else
			{
				bQuestDisableMapEnter = false; //открыть карту
				DeleteAttribute(pchar, "GenQuest.CannotWait");//можно мотать время
			}
		break;
		
		case "treatment":
			dialog.text = "So what? Will he heal my husband? Tell me that he will heal him!";
			link.l1 = "Daniel, Nathan will stay here. Alone. Shaman asked to not bother his rites. It concerns you too. He has promised to heal Nathaniel in a month.";
			link.l1.go = "treatment_1";
		break;
		
		case "treatment_1":
			dialog.text = "You know, "+pchar.name+", now I can breath freely. I have a strong confidence that shaman will bring my husband back to the normal life. I will leave Nathan here unhesitatingly because if Snake Eye won't heal him - no one would.";
			link.l1 = "Everything will be alright, Dannie. Snake Eye has never lied to me. I trust him.";
			link.l1.go = "treatment_2";
		break;
		
		case "treatment_2":
			dialog.text = "So do I. I will stay with you for a while, "+pchar.name+", are you fine about that? We still have to find the main bastard Jackman, he is responsible for all our troubles. He organized the ambush! He took Nathan's place in Maroon Town! He stole our frigate 'Centurion'!";
			link.l1 = "Agree. We have to deal with Jackman in a hard way. None of us is safe until Jackman is alive. It won't be easy to kill him though.";
			link.l1.go = "treatment_3";
		break;
		
		case "treatment_3":
			if (!CheckAttribute(pchar, "questTemp.Saga.DodsonDie")) sTemp = "Shark Dodson";
			else sTemp = "Marcus Tyrex";
			dialog.text = "Got any plan, "+pchar.name+"?";
			link.l1 = "Not yet. I need to go to Jan Swanson and ask for his advice. Let's be consecutive, we have to promote "+sTemp+"  to the head of Brethren of the Coast. We need to get a vote from every pirate baron to do that.";
			link.l1.go = "treatment_4";
		break;
		
		case "treatment_4":
			dialog.text = "Fine, Let's go to Swanson. Let's listen to what that old fogy will tell us...";
			link.l1 = "Don't be so critical about Jan. Actually you'd better make peace with him... after all we all share a goal!";
			link.l1.go = "treatment_5";
		break;
		
		case "treatment_5":
			dialog.text = "Only because I respect you... Fine, "+pchar.name+", I am sorry. I didn't mean to insult Swanson, I am just nervous. It won't happen again.";
			link.l1 = "Nice. Dannie, everything will be fine. I promise you!";
			link.l1.go = "treatment_6";
		break;
		
		case "treatment_6":
			dialog.text = "I trust you, "+pchar.name+". I put absolute trust in you. Let's go to Swanson?";
			link.l1 = "Let's go, Dannie!";
			link.l1.go = "Dolly_4";
			AddQuestRecord("BaronReturn", "13");
		break;
		
		case "islatesoro":
			dialog.text = "Yes? I am listening. How can I help you?";
			link.l1 = "Do you have any ideas where Jackman can hide? You know this bastard better than I do. Perhaps he has got some places, bases...";
			link.l1.go = "islatesoro_1";
		break;
		
		case "islatesoro_1":
			dialog.text = "Damned if I know! Jacob was always secretive. I haven't ever heard about his lairs. It will be better to try to think logically... Let's read the letter which you have got from Knave again. We might find something.";
			link.l1 = "Let's try...";
			link.l1.go = "islatesoro_2";
		break;
		
		case "islatesoro_2":
			RemoveItems(pchar, "letter_chad", 1);
			dialog.text = "Well... There is something about Isla Tesoro and some testament... Does it sound familiar to you?";
			link.l1 = "Me and Jan think that Blaze Sharp was killed by Jackman at Isla Tesoro and Shark was blamed for nothing. And a testament... a bitch... it must be Helen... Damn it, and how didn't I get it before! This bastard must be sailing near Isla Tesoro!";
			link.l1.go = "islatesoro_3";
		break;
		
		case "islatesoro_3":
			dialog.text = "Let's not waste our time then, "+pchar.name+"?";
			link.l1 = "Yes. Let's go to Isla Tesoro. The old 'Marlin' will help us in this raid.";
			link.l1.go = "islatesoro_4";
		break;
		
		case "islatesoro_4":
			DialogExit();
			AddQuestRecord("BarbTemptation", "18");
			pchar.questTemp.Saga.BarbTemptation = "islatesoro";
			// ставим прерывание на Исла-Тесоро
			pchar.quest.Saga_AttackJackman.win_condition.l1 = "location";
			pchar.quest.Saga_AttackJackman.win_condition.l1.location = "Bermudes";
			pchar.quest.Saga_AttackJackman.function = "Saga_CheckJackmanBermudes";
		break;
		
		case "after_boarding":
			dialog.text = "This scum is dead at last... I can't believe it - I am standing on the deck of 'Centurion' again! I know every nail here and it looks like that the ship has recognized me too.";
			link.l1 = "She is yours again, Dannie. Yours and Nathaniel's.";
			link.l1.go = "after_boarding_1";
		break;
		
		case "after_boarding_1":
			PlaySound("VOICE\Russian\saga\Denny Hawk-03.wav");
			dialog.text = "You can't even imagine how glad I am. Nathaniel often used to talk about our ship, he will be glad to know that it is ours once again.";
			link.l1 = "What are you going to do now, Dannie?";
			link.l1.go = "after_boarding_2";
		break;
		
		case "after_boarding_2":
			dialog.text = "Me? I will take the ship to Sharp town, hire at least a minimum crew and sail to Blueweld. I will ask Jan Swanson to look after 'Centurion' and go to Miskito people to wait there until Snake Eye heals my husband.";
			link.l1 = "Are you really going to go to Jan Swanson? I am surprised...";
			link.l1.go = "after_boarding_3";
		break;
		
		case "after_boarding_3":
			dialog.text = ""+pchar.name+", it is all your merit. I've been thinking about your words: 'we all share the same goal'. Remember? I want to make peace with Swanson, he has helped to return Nathan back to me after all. It's time to stop arguing.";
			link.l1 = "Wise words, Dannie! Nathaniel will have to retake his position in Maroon Town back when he feels better.";
			link.l1.go = "after_boarding_4";
		break;
		
		case "after_boarding_4":
			dialog.text = "That's true... but pirate baron is an elective office. What if meeting will decide otherwise?";
			link.l1 = "Let Swanson to deal with it. He can persuade anyone. The eliminating of Jackman will play its role too.";
			link.l1.go = "after_boarding_5";
		break;
		
		case "after_boarding_5":
			dialog.text = "Fine. I need to make Swanson my friend anyway... "+pchar.name+"! I want to thank you for all you have done to me and Nathan. You have saved my husband and returned us everything we lost. I owe you.";
			link.l1 = "Come on, Dannie. We are friends.";
			link.l1.go = "after_boarding_6";
		break;
		
		case "after_boarding_6":
			dialog.text = "I want you to know that we will always be glad to see you in Maroon Town. Find us there when you'll have time. Nathaniel and me will find a way to reward you.";
			link.l1 = "Good heavens, Dannie! I accept your invitation with pleasure. We'll sit, drink and talk about how you and Nathan have sunk Van der Decken...";
			link.l1.go = "after_boarding_7";
		break;
		
		case "after_boarding_7":
			dialog.text = "Did he tell? Oh, don't remind me about it...";
			link.l1 = "Fine, Dannie. You've got a lot of work with your ship and I have to visit our sworn friends - Marcus and Barbazon. I hope that you will let me to topsy-turvy this cabin, I am sure that there are a lot of interesting things lying in Jackman's chests.";
			link.l1.go = "after_boarding_8";
		break;
		
		case "after_boarding_8":
			dialog.text = "Sure, do you really think that I will object?";
			link.l1 = "Nice. Actually it's a pity to part with you, Dannie... See you in Maroon Town!";
			link.l1.go = "after_boarding_9";
		break;
		
		case "after_boarding_9":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "OpenTheDoors", -1);
			LAi_SetHP(npchar, 280, 280); 
			LAi_SetImmortal(npchar, false); // если сработало
			pchar.GenQuest.CannotTakeShip = true; // нельзя захватить
			DoQuestFunctionDelay("Saga_CheckJackmanCabinItems", 5.0); // первая проверка через 5 сек
			AddCharacterExpToSkill(pchar, "Leadership", 300);
		break;
		
		// в Марун-Тауне
		case "marun_town":
			dialog.text = ""+pchar.name+", I am very glad to see you! We are back at Maroon Town and Nathan is on his rightful place again. Actually, everyone in the village are happy about it. Now it all will go well as it used to! I am very grateful for your unselfish help!\nI want to give you a gift. Here, take it. This talisman can make the fight much easier for you. The formula will allow you to make more of those for yourself.";
			link.l1 = "Thanks, Dannie!";
			link.l1.go = "marun_town_1";
		break;
		
		case "marun_town_1":
			GiveItem2Character(pchar, "totem_12"); 
			GiveItem2Character(pchar, "recipe_totem_12"); 
			Log_Info("You have received a talisman");
			Log_Info("You have received a recipe of talisman");
			PlaySound("interface\important_item.wav");
			dialog.text = "It's not all. I have also found too chests filled with gold here. They were Jackman's property no doubt. Take them as a token of my gratitude. And don't dare to refuse! I know how much you have wasted to help me and Nathan.";
			link.l1 = "Fine, fine, Dannie, I accept them!";
			link.l1.go = "marun_town_2";
		break;
		
		case "marun_town_2":
			TakeNItems(pchar, "chest", 2); 
			Log_Info("You have received chests with doubloons");
			PlaySound("interface\important_item.wav");
			dialog.text = "Excellent! "+pchar.name+", I want you to know that you are the best friend of ours. Nathan and me will always be glad to see you in Maroon Town! See us more often!";
			link.l1 = "Thanks! I would be glad to see you again so expect me!";
			link.l1.go = "exit";
			NextDiag.TempNode = "marun_town_3";
		break;
		
		case "marun_town_3":
			dialog.text = "I am glad to see you, "+pchar.name+"! Rum, wine? Or a girl?";
			link.l1 = "Thanks, Dannie! I just wanted to see you...";
			link.l1.go = "exit";
			NextDiag.TempNode = "marun_town_3";
		break;
		
	// ------------------------------------------- провалы Саги ------------------------------------------------
		case "failcenturion":
			dialog.text = "At last me and Nathan can breath freely! This damn bastard Jackman is dead! I feel bad for 'Centurion'  but I have already accepted taken her leaving when that scum has stolen her from me. So I don't worry much.";
			link.l1 = "But I do. I am an idiot! All evidences has gone at the bottom with the ship. They could help us in voting for the new head of Brethren of the Coast. Now... it's all gone.";
			link.l1.go = "failcenturion_1";
		break;
		
		case "failcenturion_1":
			dialog.text = "Don't get so upset! It happens. Next time you will get lucky... Whatever. I want to thank you for what you've done for me and Nathan. You saved my husband's life. I owe you a great deal\nI want you to know that Maroon Town will always be glad to see you. Check me and Nate there when you have time. We will find a way to repay you.";
			link.l1 = "Fine, Dannie. I will visit you for sure. Are you leaving already?";
			link.l1.go = "failcenturion_2";
		break;
		
		case "failcenturion_2":
			dialog.text = "Yes, I will go to Miskito, I hope that Snake Eye has already healed Nathan. Then we will return to Maroon Town.";
			link.l1 = "Heh, I'm already so used to you, it's too bad that we have to part with you... Good luck, Daniel!";
			link.l1.go = "failcenturion_3";
		break;
		
		case "failcenturion_3":
			DialogExit();
			RemovePassenger(pchar, npchar);
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "Saga_FailCenturion", 10.0);
			npchar.greeting = "danny_2";
		break;
		
		//--> ----------------------------------- офицерский блок ------------------------------------------
		case "Danielle_officer":
			dialog.text = "What do you want, captain?";
			if (CheckAttribute(pchar, "questTemp.Saga.BarbTemptation") && pchar.questTemp.Saga.BarbTemptation == "danielle")
			{
				Link.l3 = "Dannie, I want to ask for you advice!";
				Link.l3.go = "islatesoro";
			}
			Link.l1 = "Listen to my order!";
            Link.l1.go = "stay_follow";
			link.l2 = "It's nothing. Dismissed!";
			link.l2.go = "exit";
			NextDiag.TempNode = "Danielle_officer";
			sld = characterFromId("Danielle");
		    sld.HoldEquip = true; // лесник -  не отдавать саблю и пистоль для текущей игры. поэтому так . другого способа не нашел						 
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
					Link.l3 = "Change the type of ammo for your firearms.";
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
            dialog.Text = "There is change of disposition!";
            Link.l1 = "Dismissed.";
            Link.l1.go = "Exit";
            Npchar.chr_ai.tmpl = LAI_TMPL_STAY;
        break;
        
        case "Boal_Follow":
            SetCharacterTask_FollowCharacter(Npchar, PChar);
            dialog.Text = "There is change of disposition!";
            Link.l1 = "Dismissed.";
            Link.l1.go = "Exit";
        break;
		//<-- ----------------------------------- офицерский блок ----------------------------------------
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
	}
}