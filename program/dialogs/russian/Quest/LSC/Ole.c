// Оле Кристиансен - Белый Мальчик
#include "DIALOGS\russian\Rumours\Common_rumours.c"
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	ProcessCommonDialogRumors(NPChar, Link, NextDiag);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "What do you want?";
			link.l1 = "Nothing.";
			NextDiag.TempNode = "First time";
		break;
		
		// в магазине - первая встреча
		case "store":
			dialog.text = "Oups... Hello, uncle. Do you have a white bead? Give me the white bead...";
			link.l1 = "Hm. Good day. Are you... the White Boy?";
			link.l1.go = "store_1";
		break;
		
		case "store_1":
			dialog.text = "Bead! White bead for the white boy! Do you have a white bead, uncle?";
			if (CheckCharacterItem(pchar, "jewelry52"))
			{
				link.l1 = "Hm, I don't have beads, but I can give you this pearl. It is white and it's just like the bead. Are you okay with that?";
				link.l1.go = "store_2";
			}
			link.l2 = "No, I don't have any beads neither white nor red. I am not a girl or an Indian to wear beads. Tell me...";
			link.l2.go = "pearl";
			sld = characterFromId("Axel");
			sld.quest.ole_pearl = "true";
		break;
		
		case "pearl":
			dialog.text = "Bead! White bead! No bead - no talk. Bad uncle... Give me a bead!";
			link.l1 = "Damn! Such a crazy fellow! The Snake Eye and Chimiset were right - he is a weak head... What kind of bead does he need?";
			link.l1.go = "exit";
			NextDiag.TempNode = "pearl_repeat";
		break;
		
		case "pearl_repeat":
			dialog.text = "Give a bead, uncle. Good uncle... White bead!";
			if (CheckCharacterItem(pchar, "jewelry52"))
			{
				link.l1 = "Here, take your bead. Is that what you want?";
				link.l1.go = "store_2";
			}
			link.l2 = "Oh, damn it...";
			link.l2.go = "exit";
			NextDiag.TempNode = "pearl_repeat";
		break;
		
		case "store_2":
			RemoveItems(pchar, "jewelry52", 1);
			PlaySound("interface\important_item.wav");
			dialog.text = "Yes, yes! It is! Uncle gave a bead! Thanks, good man! Now Ole has one more bead. Soon I will see mama...";
			link.l1 = "I am glad for you. Well, can we talk now?";
			link.l1.go = "store_3";
			sld = characterFromId("Axel");
			DeleteAttribute(sld, "quest.ole_pearl");
		break;
		
		case "store_3":
			dialog.text = "Sure, good man. Are you a good man, uncle? We will be friends. Ole will be glad to talk. What is your name?";
			link.l1 = "My name is "+pchar.name+". Ole, one man told me about you and he is not here anymore. He said that you had helped him and you can help me.";
			link.l1.go = "store_4";
		break;
		
		case "store_4":
			dialog.text = "Uncle gave a bead to Ole - he is a good uncle. Ole likes to help good people. There are not many good people - bad uncles are all around. I will help you, sure. I like to help.";
			link.l1 = "Nice! Well, we are friends now. Ole, tell me do you remember a man with a red skin and with a gorgeous hat with feathers? He told me that you had saved him long ago.";
			link.l1.go = "store_5";
		break;
		
		case "store_5":
			dialog.text = "I remember that uncle. He is a good man. I saved him. I brought him to the statue. And recently I have saved another good man from the cargo hold with food. I have saved him from the bad admiral's uncles. They would have killed him. I wanted to take him to the statue too but he has rejected. Totally.";
			link.l1 = "From the cargo hold? Heh, I suppose, I know who do you mean... And I know this uncle. Tell me, Ole, who is that man you have saved?";
			link.l1.go = "store_6";
		break;
		
		case "store_6":
			dialog.text = "His name is uncle Nathan. He is ill, very-very ill. He barely could walk when Ole found him.";
			link.l1 = "Sure... It is strange that he could even do it.";
			link.l1.go = "store_7";
		break;
		
		case "store_7":
			dialog.text = "No, it's not strange. I found him and gave some fire rum. I swam inside the hole because there is food on that ship. Bad men lock the door, but I always open it. He-he-he... Silly bad men. They lure crabs, I know that. Bad men\nI got there and found Nathan. He wasn't feeling well. I had fire rum - I gave him to drink it, so he got better. Then I gave him the tincture, I always carry one of those, in case scary crab bites Ole. Good uncle Chimiset told me to do so...";
			link.l1 = "Did you give him an antidote and rum? Heh, you are not such a fool as they all think. Well done, Ole.";
			link.l1.go = "store_8";
		break;
		
		case "store_8":
			dialog.text = "Evil uncles consider Ole as a fool and they are teasing him: Ole the fool... Ole is not a fool, he just need to collect all white beads or his mother will send him away. Will you give me another bead later?";
			link.l1 = "Hm... Sure, Ole, we are friends. Tell me, how were you going to send Hawk... uncle Nathan to the statue. Uncle Chimiset told me that it was sunk with the ship...";
			link.l1.go = "store_9";
		break;
		
		case "store_9":
			dialog.text = "Statue is at the bottom. Ole knows. But it is not deep and good uncle Henrik can send uncle Nathan there. Uncle Henrik knows how to walk underwater. But there are a lot of scary crabs. Ole fears them. They painfully bite.";
			link.l1 = "Uncle Henrik? Who is he?";
			link.l1.go = "store_10";
		break;
		
		case "store_10":
			dialog.text = "Uncle Henrik lives among evil uncles Narwhals. Everybody knows him. He can walk underwater and he teaches uncles Narwhals how to dive there. Uncle Henrik is kind, he gave a white bead to Ole.";
			link.l1 = "And how do Narwhals let you in? Or is their territory open for you?";
			link.l1.go = "store_11";
		break;
		
		case "store_11":
			dialog.text = "Tee-hee... Evil uncles don't let Ole come in, but Ole can enter any room in their ships at night. They are big and noisy, but Ole is silent and careful. And I met uncle Henrik while swimming around the ship which uncle Henrik uses to dive from. Uncle Henrik gave a white bead to Ole and we are friends now.";
			link.l1 = "Interesting... I also want to be a friend to uncle Henrik.";
			link.l1.go = "store_12";
		break;
		
		case "store_12":
			dialog.text = "You want to dive and go to the statue? It is there, in the old ship's break. There are a lot of big and scary crabs. Don't you fear them? They can bite.";
			link.l1 = "No, I don't fear them. I have killed one already so they'd better be afraid of me.";
			link.l1.go = "store_13";
		break;
		
		case "store_13":
			dialog.text = "Оh, "+pchar.name+"  is very brave! Then you should go to uncle Henrick, he will teach you how to walk at the bottom and you will kill every crab there. You will also find there one more big bead for Ole. Right?";
			link.l1 = "Sure, I will. But I need to find uncle Henrik first.";
			link.l1.go = "store_14";
		break;
		
		case "store_14":
			dialog.text = "And why to find him? He lives at the ship named 'San Gabriel', in the workshop. But evil uncles Narwhals may not welcome you.";
			link.l1 = "I will deal with the evil uncles myself. And the last question, where is uncle Nathan now? I have been looking for him and he is a reason why I am here.";
			link.l1.go = "store_15";
		break;
		
		case "store_15":
			dialog.text = "I hide uncle Nathan in my sanctuary on the 'Fernanda'. It is far away and no one lives there. Everybody thinks that it will sink soon, but Ole knows the opposite. I saved uncle Nathan and brought him there\nHe is still very ill and he drinks fire rum all the time. He barely walks and unable to lift anything heavier than five pounds. I feel bad for uncle Nathan, I bring him fire rum from chests and food from the hold of admiral's bad men. I also cook him rats I catch. Very tasty rats!";
			link.l1 = "Tasty rats? I see. So is Nathan on the ship named... what did you say - the 'Fernanda'? I don't know her...";
			link.l1.go = "store_16";
		break;
		
		case "store_16":
			dialog.text = "Uncle "+pchar.name+", I have just told you that it is not far from here. You have to swim to get to her. There is a door at her rear, but uncle Nathan doesn't open it. Ole told him to don't. But if you are a friend of uncle Nathan, I will tell you how to open it. Knock on the door like that: knock-knock... knock-knock. He will open it then.";
			link.l1 = "I will remember that. Thanks, Ole! You have really helped me out! I don't know how to thank you properly.";
			link.l1.go = "store_17";
		break;
		
		case "store_17":
			dialog.text = "Bring me one more white bead. If you will find it, of course.";
			link.l1 = "Ah, yes! White beads! Good. See you, Ole!";
			link.l1.go = "store_18";
		break;
		
		case "store_18":
			DialogExit();
			LAi_SetLoginTime(npchar, 12.0, 21.99);
			LAi_SetCitizenType(npchar);
			LAi_group_MoveCharacter(npchar, "LSC_CITIZEN");
			sld = characterFromId("Nathaniel");
			sld.dialog.currentnode = "diffindoor";
			sld.greeting = "Nathaniel_ill"; // ноду и вякалку Натану
			pchar.questTemp.LSC.DiffIndoor = "true"; //атрибут прохода к Натану
			pchar.questTemp.LSC = "mechanic"; // флаг на разговор с Механиком
			NextDiag.CurrentNode = "ole";
			AddQuestRecord("LSC", "6");
		break;
		
		case "ole":
			dialog.text = "Ah, uncle "+pchar.name+"! Glad to see you! How are you doing?";
			link.l1 = "Thanks, Ole, I am fine. I am glad to see you too.";
			link.l1.go = "exit";
			link.l2 = "Listen, Ole, you've said that admiral's pirates close the door to the cargo hold and you always open it... All chests there are closed and you've said that you take rum for uncle Nathan from them. How are you able to do that?";
			link.l2.go = "lock";
			NextDiag.TempNode = "ole";
		break;
		
		case "lock":
			dialog.text = "Ole has a set of fine keys. They open any door or chest. Well, not all of them. Some can't be opened but the most of them can. Ole found it in the evil uncle Jurgen's cabin. He works with his hammer for every day near his oven. He makes locks and keys. And he also makes big and scary muskets for evil Narwhals.";
			link.l1 = "I see. Ole, can you sell me those keys? I can pay for them...";
			link.l1.go = "lock_1";
		break;
		
		case "lock_1":
			dialog.text = "Fine, uncle "+pchar.name+", I will sell you the keys. I will just leave the one for me. It opens the admiral's room. There are a lot of food and rum for uncle Nathan. There are no more beads and rum left in the chests anyway.";
			link.l1 = "How much do you want for them?";
			link.l1.go = "lock_2";
		break;
		
		case "lock_2":
			dialog.text = "First, tell me, uncle "+pchar.name+", do you have a big ship?";
			link.l1 = "Yes, I have. But she is not here, she is at the outer ring. But I will leave the island soon and I will come back here on my big ship for uncle Nathan.";
			link.l1.go = "lock_3";
		break;
		
		case "lock_3":
			dialog.text = "For uncle Nathan? Oh, that is wonderful! Listen then, promise me to take me from here on your big ship and let me sail with you for long as I need. I can be useful. I can catch and cook rats... Also, give me five white beads. And I will give you the keys.";
			if (GetCharacterItem(pchar, "jewelry52") >= 5)
			{
				link.l1 = "Sure! Here are your beads. Take them.";
				link.l1.go = "lock_4";
			}
			link.l2 = "To catch and cook rats? Heh! An interesting skill. Sure, Ole, we have a deal. I will bring you five beads and my word.";
			link.l2.go = "exit";
			NextDiag.TempNode = "ole_1";
		break;
		
		case "ole_1":
			dialog.text = "Ah, uncle "+pchar.name+"! Glad to see you! How are you doing?";
			link.l1 = "Thanks, Ole, I am fine. I am glad to see you too.";
			link.l1.go = "exit";
			if (GetCharacterItem(pchar, "jewelry52") >= 5)
			{
				link.l2 = "I have brought you five white beads for your keys.";
				link.l2.go = "lock_4";
			}
			NextDiag.TempNode = "ole_1";
		break;
		
		case "lock_4":
			RemoveItems(pchar, "jewelry52", 5);
			PlaySound("interface\important_item.wav");
			dialog.text = "Beads! White beads! Uncle "+pchar.name+"  has given beads to Ole! Soon I will see you, mom!... Uncle "+pchar.name+", do you promise that you will take me from here when you will be back?";
			link.l1 = "I do, Ole. I haven't eaten rats yet. I will take you with me.";
			link.l1.go = "lock_5";
		break;
		
		case "lock_5":
			GiveItem2Character(pchar, "keys_skel");
			AddCharacterExpToSkill(pchar, "Sneak", 200);
			dialog.text = "Thank you, thank you, good uncle "+pchar.name+"! Take your keys. It is easy to use them, just insert them one by one and try. One of them will eventually open a lock you need. If it won't then the lock is too tricky and you will definitely need a special key.";
			link.l1 = "I see. I suppose, I will handle it.";
			link.l1.go = "lock_6";
		break;
		
		case "lock_6":
			dialog.text = "Wait, uncle "+pchar.name+"! I have got one more key. It is pretty and smart. Evil uncle Jurgen doesn't make keys like this one. I don't know what it opens, but perhaps you will find it out. Look, it is a very pretty key, you surely haven't seen anything like this one before.";
			link.l1 = "Show me... Yes, the key is very interesting. But what's the use of it if you don't know what can be opened by it?";
			link.l1.go = "lock_7";
		break;
		
		case "lock_7":
			dialog.text = "Uncle "+pchar.name+", , you are very strange. What's the use? If there is the key then somewhere is the lock. If there is the lock then somewhere is the coin. I have found the key on the island. It means that the lock is here too. No doubt in that. It is a smart key and only very valuable items are locked by such key. Ole knows.";
			link.l1 = "To be honest, you are funny, Ole. Fine, I'll buy it. Do you want beads for it?";
			link.l1.go = "lock_8";
		break;
		
		case "lock_8":
			dialog.text = "Yes, Ole wants five beads. Will you give them, uncle "+pchar.name+"?";
			if (GetCharacterItem(pchar, "jewelry52") >= 5)
			{
				link.l1 = "Here, take your beads.";
				link.l1.go = "key";
			}
			link.l2 = "I don't have them, but I will bring beads to you for sure.";
			link.l2.go = "exit";
			NextDiag.TempNode = "ole_2";
		break;
		
		case "key":
			RemoveItems(pchar, "jewelry52", 5);
			PlaySound("interface\important_item.wav");
			GiveItem2Character(pchar, "sant_anna_key");
			AddCharacterExpToSkill(pchar, "Fortune", 200);
			dialog.text = "Beads! White beads for the white boy! For his mamma! Here, uncle "+pchar.name+", take the key. And you will find the lock, Ole knows. You are brave, you don't even fear scary crabs.";
			link.l1 = "Oh, don't make me laugh, Ole! Thanks for the key. See you around!";
			link.l1.go = "exit";
			NextDiag.TempNode = "ole_3";
		break;
		
		case "ole_2":
			dialog.text = "Ah, uncle "+pchar.name+"! Glad to see you! How are you doing?";
			link.l1 = "Thanks, Ole, I am fine. I am glad to see you too.";
			link.l1.go = "exit";
			if (GetCharacterItem(pchar, "jewelry52") >= 5)
			{
				link.l2 = "I have brought you five white beads for you key.";
				link.l2.go = "key";
			}
			NextDiag.TempNode = "ole_2";
		break;
		
		case "ole_3":
			dialog.text = "Ah, uncle "+pchar.name+"! Glad to see you! How are you doing?";
			link.l1 = "Thanks, Ole, I am fine. I am glad to see you too.";
			link.l1.go = "exit";
			NextDiag.TempNode = "ole_3";
		break;
		
		case "return":
			dialog.text = "Oh, uncle "+pchar.name+", you are back! You are back on the big ship! Will you take me from here? Uncle "+pchar.name+", you have promised me, remember?";
			link.l1 = "Sure, I do, Ole. Welcome aboard! I suppose that rats are in trouble, ha-ha!";
			link.l1.go = "return_1";
			link.l2 = "Really? And when have I promised you? I don't remember any promises like this...";
			link.l2.go = "return_3";
		break;
		
		case "return_1":
			dialog.text = "Thanks, uncle! Ole will be useful, you will see! Oh, perhaps, I will see mom? I am on my way now!";
			link.l1 = "Don't hurry like this, Ole. You can pack your stuff. I am not going to sail immediately.";
			link.l1.go = "return_2";
		break;
		
		case "return_2":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "LSC_SetOlePassenger", 10.0);
		break;
		
		case "return_3":
			dialog.text = "You have promised me, you have! You have promised to take Ole from here! Evil uncle! You have cheated Ole! Bad uncle!";
			link.l1 = "...";
			link.l1.go = "return_4";
		break;
		
		case "return_4":
			DialogExit();
			LAi_SetActorType(npchar);
			npchar.lifeday = 0;
			LAi_ActorRunToLocation(npchar, "reload", "reload45", "none", "", "", "", 20.0);
			ChangeCharacterComplexReputation(pchar, "nobility", -5);
			ChangeCharacterComplexReputation(pchar, "authority", -3);
			if (GetCharacterIndex("Mary") != -1) // Мэри
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
		break;
		
		// Блудный сын
		case "givemepearl":
			dialog.text = "Uncle, uncle... I need one more white bead. Please, give a white bead to Ole!";
			if (CheckCharacterItem(pchar, "jewelry52"))
			{
				link.l1 = "I knew, that you will ask for it. Here, take your bead. Satisfied?";
				link.l1.go = "givemepearl_yes";
			}
			link.l2 = "Oh, and what a pain in the neck... I don't have any more beads, Ole, I don't!";
			link.l2.go = "givemepearl_no";
			DeleteAttribute(npchar, "pearl_date");
		break;
		
		case "givemepearl_yes":
			RemoveItems(pchar, "jewelry52", 1);
			PlaySound("interface\important_item.wav");
			AddCharacterExpToSkill(pchar, "Fortune", 50);
			dialog.text = "Thank you! Good, good uncle "+pchar.name+"! Ole has one more bead and there are not many beads left! And I will go to the mom...";
			link.l1 = "Oh, and why are you so odd...";
			link.l1.go = "givemepearl_yes_1";
		break;
		
		case "givemepearl_yes_1":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "OpenTheDoors", 5.0);
			SaveCurrentNpcQuestDateParam(npchar, "pearl_date");
			npchar.quest.pearlqty = sti(npchar.quest.pearlqty)+1;
			NextDiag.CurrentNode = "givemepearl_repeat";
		break;
		
		case "givemepearl_repeat":
			dialog.text = "Thank you for a bead, good uncle "+pchar.name+"!";
			link.l1 = "You are welcome...";
			link.l1.go = "exit";
			NextDiag.TempNode = "givemepearl_repeat";
		break;
		
		case "givemepearl_no":
			dialog.text = "No bead? But how is that, uncle "+pchar.name+"?! Just a few more beads left... I have to collect them. I will land in that case. I will look for beads...";
			if (CheckCharacterItem(pchar, "jewelry52"))
			{
				link.l1 = "And where are you going to go? What will you do alone? No, I don't want to be responsible for your fate. Wait, I will check my pockets.. Here! Take you bead and stay with me. Satisfied?";
				link.l1.go = "givemepearl_yes";
			}
			link.l2 = "It is your right, Ole. If you are bored to sail with me then I won't stop you. We had a deal. You have been catching those rates fine though...";
			link.l2.go = "givemepearl_no_1";
		break;
		
		case "givemepearl_no_1":
			dialog.text = "Farewell, uncle "+pchar.name+". Ole needs white beads or he will never return to his mom...";
			link.l1 = "Oh, I am so sorry for you but what can I do? Go, Ole. Good luck.";
			link.l1.go = "givemepearl_exit";
		break;
		
		case "givemepearl_exit": // Оле уходит - квест не довели до конца
			DialogExit();
			RemovePassenger(Pchar, npchar);
			npchar.lifeday = 0;
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "OpenTheDoors", 5.0);
			DeleteAttribute(pchar, "GenQuest.Ole");
		break;
		
		case "mother":
			dialog.text = "Uncle "+pchar.name+"! I need one more white bead. The last one. Please, give it to Ole!";
			if (CheckCharacterItem(pchar, "jewelry52"))
			{
				link.l1 = "I knew that you will ask for it. Here, take your bead. Satisfied?";
				link.l1.go = "mother_1";
			}
			link.l2 = "Oh, and what a pain in the neck... I don't have any more beads, Ole, I don't!";
			link.l2.go = "givemepearl_no_1";
		break;
		
		case "mother_1":
			RemoveItems(pchar, "jewelry52", 1);
			PlaySound("interface\important_item.wav");
			dialog.text = "Thank you, thank you, good uncle "+pchar.name+"! Now Ole has all of the beads. Yes, all of them! Now Ole can bring them to mom and she won't send Ole away...";
			link.l1 = "Listen, who is that mom you are always talking about? And explain me at last why do you need those pearls... white beads? And what does it mean - you have them all?";
			link.l1.go = "mother_2";
		break;
		
		case "mother_2":
			dialog.text = "Good uncle "+pchar.name+" has helped Ole to collect beads for his mama... Ole was small when he tore mama's necklace of white beads. They all fell into the water. Mama was so angry at Ole, and he cannot return home until he collects all of the lost beads\nI remember how many there were of them. Five times of ten beads. Now Ole has them all. Uncle "+pchar.name+", please, take me home! I want to make mama happy, to return beads. Take me home!";
			link.l1 = "Jesus, what an incredible story... You got to the Island being as a kid. Were you driven away from yours, because you tore your mum's pearl necklace? Creepy...";
			link.l1.go = "mother_3";
		break;
		
		case "mother_3":
			dialog.text = "Take me to my mom, good uncle "+pchar.name+". I want to see her. She will be pleased to see beads.";
			link.l1 = "I'd like to, but do you know where is you home? Where does your mother live?";
			link.l1.go = "mother_4";
		break;
		
		case "mother_4":
			dialog.text = "She lives at the island, in the house with a red roof.";
			link.l1 = "Really! Do you even know how many isles here and how many houses with a red roof on them? What's the name of that island? Give me details...";
			link.l1.go = "mother_5";
		break;
		
		case "mother_5":
			dialog.text = "I don't know its name. I know it was an island, mama was telling father that we were at the island! And we were living in the house with a red roof. Pretty house, a big one. Take me to mom, uncle "+pchar.name+". Please...";
			link.l1 = "Oh, fine. We will search for such a house on every island and we will ask for you mother. What is her name?";
			link.l1.go = "mother_6";
		break;
		
		case "mother_6":
			dialog.text = "Her name? You are so strange, uncle "+pchar.name+". Mother's name is mother. Is your mother's name different?";
			link.l1 = "Oh, God, please, send me some patience... Fine, Ole. We will try to find your home. Now go to the ship.";
			link.l1.go = "mother_7";
		break;
		
		case "mother_7":
			dialog.text = "Thank you, uncle "+pchar.name+". You are very, very kind and good! Soon Ole will see mom!";
			link.l1 = "Оh...";
			link.l1.go = "mother_8";
		break;
		
		case "mother_8":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "OpenTheDoors", 5.0);
			DeleteAttribute(npchar, "pearl_date");
			// ставим Агнес Кристиансен и открываем ее дом в Мариго
			LocatorReloadEnterDisable("Marigo_town", "houseSp2", false);
			sld = GetCharacter(NPC_GenerateCharacter("Agnes", "women_18", "woman", "towngirl", 10, HOLLAND, -1, true, "quest"));
			SetFantomParamFromRank(sld, 10, true);
			sld.name = "Agnes";
			sld.lastname = "Christiansen";
			sld.dialog.FileName = "Quest\LSC\OtherNPC.c";
			sld.dialog.currentnode = "agnes";
			//sld.greeting = "";
			LAi_SetOwnerType(sld);
			LAi_SetImmortal(sld, true);
			ChangeCharacterAddressGroup(sld, "Marigo_houseSp2", "barmen", "stay");
			LAi_group_MoveCharacter(sld, "HOLLAND_CITIZENS");
		break;
		
		case "home":
			dialog.text = "Mother... Mother, mama! I am back!";
			link.l1 = "Son...";
			link.l1.go = "home_1";
		break;
		
		case "home_1":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_SetActorType(pchar);
			SetMusic("music_romantic");
			bDisableCharacterMenu = true;//лоченые интерфейсы
			locCameraRotateAroundHero(0.0, 2.0, 0.0, 0.005, 0.0, 2.0, 0.0, 1000);
			DoQuestFunctionDelay("LSC_OleReturnHome", 18.0);
		break;
		
		case "home_2":
			dialog.text = "Mama, I have brought you white beads! I have collected them all! You will have a necklace again. Are you still angry at me?";
			link.l1 = "God...(crying) Ole! Son, why? Why did you go away? I don't care about those pearls!";
			link.l1.go = "home_3";
		break;
		
		case "home_3":
			sld = characterFromId("Blaze");
			dialog.text = "Mama, here... take them. I have been collecting them for a long time. Good uncles have been helping me, especially uncle "+sld.name+". He took me on his big ship, helped to collect beads and has brought me home...";
			link.l1 = "Ole... You have really grown up, but you are still a kid... Let me hug you, son! I am sorry, please forgive me for that damn necklace! I will never leave you alone, never! We will live together and I will care about you... I will expiate, I promise!...";
			link.l1.go = "home_4";
		break;
		
		case "home_4":
			dialog.text = "Mama, I missed you... I want to stay with you. Are you still angry at me? Why are you crying?";
			link.l1 = "(crying) No, no... I am so sorry, please forgive me, son!...";
			link.l1.go = "home_5";
		break;
		
		case "home_5": // перекидываем pchar
			DialogExit();
			LAi_SetStayType(pchar);
			SetMainCharacterIndex(GetCharacterIndex("Blaze"));
			PChar = GetMainCharacter();			
			LAi_SetPlayerType(PChar);
			sld = characterFromId("Agnes");
			sld.dialog.currentnode = "agnes_11";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "final":
			dialog.text = "Uncle "+pchar.name+"! It is so good that you have come! Thanks for bringing me to my mom. It is so good to be here with her... Isn't that great to be home, isn't it, uncle "+pchar.name+"?";
			link.l1 = "Yes. Ole. It is. I am glad that you are happy.";
			link.l1.go = "exit";
			NextDiag.TempNode = "final";
		break;
		
//----------------------------------------- специальные реакции -----------------------------------------------
		//замечание по обнаженному оружию
		case "LSCNotBlade":
			dialog.text = LinkRandPhrase("Listen, you'd better take your weapon away. It makes me nervous.", "You know, running with blade is not tolerated here. Take it away.", "Listen, don't play a medieval knight running with a sword around. Take it away, it doesn't suit you...");
			link.l1 = LinkRandPhrase("Fine.", "Okay.", "As you say...");
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;	
		
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = NPCharSexPhrase(NPChar, "Listen, I am the citizen of the city and I'd ask you to hold down your blade.", "Listen, I am the citizen of the city and I'd ask you to hold down your blade.");
				link.l1 = LinkRandPhrase("Fine.", "Okay.", "As you say...");
			}
			else
			{
				dialog.text = NPCharSexPhrase(NPChar, "Be careful, pal, while running with a weapon. I can get nervous...", "I don't like when men are walking in front of me with their weapon ready. It scares me...");
				link.l1 = RandPhraseSimple("Got it.", "I am taking it away.");
			}
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;
// <-- специальные реакции
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}