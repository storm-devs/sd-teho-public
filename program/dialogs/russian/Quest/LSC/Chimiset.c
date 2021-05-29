// колдун ривадос - Чимисет
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
			link.l1 = "No, nevermind.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		//-------------------------------------в тюрьме на Тартарусе-----------------------------
		// вариант R
		case "KillChad":
			dialog.text = "Wait! Stop... I beg you to listen to me before you'd make a mistake.";
			link.l1 = "I am listening... I hope that you have a really weighty arguments to stop me from...";
			link.l1.go = "KillChad_1";
			LAi_RemoveCheckMinHP(npchar); //убираем проверяльщик, если еще есть
		break;
		
		case "KillChad_1":
			dialog.text = "From killing me, right? I have heard you talking with Chad upstairs and I don't blame you - anyone would likely do the same. But you are wrong to think that Chad will let you go after killing me.";
			link.l1 = "Hm... Interesting, and why won't he? The only thing I know is that my future is going to become very sad and dire, if I don't kill you.";
			link.l1.go = "KillChad_2";
		break;
		
		case "KillChad_2":
			dialog.text = "You won't have any future at all if you kill me. Listen, Narwhals and Chad are willing to get rid of me, but they are too scared of my abilities to do this themselves - my killer will be cursed forever. So they want you to do all the dirty work\nChad is aware that you are not Rivados, he is screwing you. Once you kill me - they will do the same thing to you and use your corpse in order to fool Shark.";
			link.l1 = "Shark? Steve Dodson? Is he actually here? And explain me at last - who the hell are those Rivados?";
			link.l1.go = "KillChad_3";
		break;
		
		case "KillChad_3":
			dialog.text = "Heh, it looks like you don't live here, indeed... But it is not the right time for telling stories. We have to save our lives. I can tell you how to do it.";
			link.l1 = "You know what, wizard, I have recently made a trip through some mystical portal and barely survived it, so your curses don't scare me. I have had enough of listening - it's time to finish you off.";
			link.l1.go = "KillChad_fightfail";
			link.l2 = "Fine, I trust you. What is the plan?";
			link.l2.go = "KillChad_4";
		break;
		
		case "KillChad_fightfail":
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
			LAi_SetActorType(npchar);
			LAi_ActorAnimation(npchar, "afraid", "", -1);
			LAi_SetImmortal(npchar, false);
			pchar.quest.LSC_fightfail.win_condition.l1 = "NPC_Death";
			pchar.quest.LSC_fightfail.win_condition.l1.character = "Chimiset";
			pchar.quest.LSC_fightfail.function = "LSC_Fightfail_Final";
		break;
		
		case "KillChad_4":
			dialog.text = "There is a chest over there. It contains decent weapons and potions. It is locked, but the lock is old and damaged, so find a crowbar to break it\nTake everything from the chest, arm yourself and go to the stairs. It is a good defensive position, they will be forced to fight you one on one, just be careful of musketeers\nI hope that you are good with swords, I am too old to help you with fighting. If you will manage to kill them all and to survive in the process - I guarantee you the protection of Rivados, my family...";
			link.l1 = "Good. Pray to your gods for me - the fight is going to be tough. Those lads upstairs look really serious.";
			link.l1.go = "KillChad_5";
		break;
		
		case "KillChad_5":
			DialogExit();
			pchar.quest.LSC_fightfail.over = "yes"; //снять прерывание
			LAi_SetImmortal(npchar, true);
			ref location = &Locations[FindLocation(pchar.location)];
			location.private1.key = "crowbar";
			location.private1.key.delItem = true;
			NextDiag.CurrentNode = "KillChad_6";
		break;
		
		case "KillChad_6":
			dialog.text = "Don't waste time! Force the lock quickly...";
			link.l1 = "Yes, yes, I am on my way.";
			link.l1.go = "exit";
			NextDiag.TempNode = "KillChad_6";
		break;
		
		case "Chad_die":
			dialog.text = "Well done! You are really the master of fencing. I owe you, stranger. Tell me, what is your name?";
			link.l1 = ""+pchar.name+". "+GetFullName(pchar)+". And what's yours?";
			link.l1.go = "Chad_die_1";
		break;
		
		case "Chad_die_1":
			dialog.text = "My name is Chimiset, I am a Rivados shaman and advisor of our chief - Black Eddie. He will be glad to know that you had set me free and saved my life. You are a friend of Chimiset, Black Eddie and all Rivados. From now on you will always be a welcome guest on our Protector...";
			link.l1 = "Wait... Chimiset, in case you still didn't understand, it has been only a few hours since I got here. Can you explain me where am I, who are Rivados and where I can find Shark Dodson?";
			link.l1.go = "Chad_die_2";
		break;
		
		case "Chad_die_2":
			dialog.text = "This place is called the Island of Justice. Or Justice Island. Though it sounds more like a mockery. You won't find justice here. This place is made of hundreds of dead ships. The central part is suitable for constant living. The Island is inhabited by people who survived shipwrecks\nRivados is a clan, a group of people who have been living together for a long time. There are also three other groups living here: Narwhal clan, they are enemies of ours, pirates of Shark Dodson and common people. Shark is basically a head of the island, he calls himself an admiral\nHe have arrived quite recently here and seized power in quite a violent manner. He captured the 'San Augustine' where we were storing our food supplies. Now we have to buy provisions at prices Shark says. It seems, that you have already been in that warehouse\nChad Kapper was Shark's boatswain and a head of the prison here. Layton Dexter used to be Shark's first mate, he has some influence too. These three and their pirates are a dominating force across the island facing both Rivados and Narwhals.";
			link.l1 = "Why that Chad Kapper ordered me to kill you?";
			link.l1.go = "Chad_die_3";
		break;
		
		case "Chad_die_3":
			dialog.text = "Chad had established contacts with Narwhal clan, our enemies. He was going to kill Shark with their help and take his place. Narwhals hold grudges against the admiral for the death of Alan Milrow, their ex leader. They believe that Shark is responsible for his death, but they are wrong. I know who did it. Chad did. I am the only witness of this crime\nThat is why Chad couldn't let me go free, yet he feared to harm me too. Pirates are fearless in battles, but they are afraid of magic. So he wanted to use you. Chad and Narwhals would have Shark killed and blamed Rivados for this.";
			link.l1 = "Is that so? Tell me why...";
			link.l1.go = "Chad_die_4";
		break;
		
		case "Chad_die_4":
			dialog.text = ""+pchar.name+", my friend, let's talk later. We have to hurry, before Shark's pirates will show up. Search Chad's body and take his keys. But first, check his desk, he might have interesting papers there\nGo to Shark Dodson, you will find him in the 'San Augustine', a large ship, standing in a distance from the others, there is a bridge leading to her from the ship named 'Pluto'. Tell him that Chad was plotting a betrayal, and say that Narwhals are behind all this, and we, Rivados, have nothing to do with it.\nI will gladly give you any information you need about Island, about my clan and others, once you arrive to our residence in the Protector. Let's get out of here!";
			link.l1 = "Fine, Chimiset. I will find you later at that... 'Protector'. Let's get out of here!";
			link.l1.go = "Chad_die_5";
		break;
		
		case "Chad_die_5":
			dialog.text = "One more thing. Our ships, including the 'Protector', are forbidden to visit for any stranger. You must be Rivados or know a password in order to enter. I would tell you it, but it changes every week and I've been here for too long and don't know a current password\nSo you should visit the 'San Augustine' first. I will tell our people who you are, while you are talking to Shark, and you will become our friend. But don't go to the 'Protector' now, first, have a talk with Shark, and let me meet my people first, in other case all Rivados will consider you as an enemy";
			link.l1 = "I see. I am heading to the 'San Augustine'. See you!";
			link.l1.go = "Chad_die_6";
		break;
		
		case "Chad_die_6":
			DialogExit();
			DeleteAttribute(pchar, "GenQuest.Notsearchbody");
			LAi_SetActorType(npchar);
			LAi_ActorFollow(npchar, pchar, "", -1);
			pchar.quest.LSC_LetterChad.win_condition.l1 = "item";
			pchar.quest.LSC_LetterChad.win_condition.l1.item = "letter_chad";
			pchar.quest.LSC_LetterChad.function = "LSC_LetterChad_Find";
			sld = characterFromId("SharkMush_17");
			sld.lifeday = 0;
			for (i=1; i<=2; i++)
			{
				sld = characterFromId("SharkSold_1"+(i+3));
				sld.lifeday = 0;
			}
			AddSimpleRumourCityTip("Ha, they say that you are a friend of clan Rivados. This is interesting. Congratulations...", "LostShipsCity", 5, 1, "LSC", "");
			AddSimpleRumourCityTip("They say that you have saved the Rivados wizard Chimiset from 'Tartarus'. Now you are a welcome guest on their ships.", "LostShipsCity", 5, 1, "LSC", "");
			AddSimpleRumourCityTip("So it was you who'd set Chimiset free! Interesting. Now you are a friend of Rivados but an enemy of Narwhals. I am not sure whether to congratulate you or sympathize...", "LostShipsCity", 5, 1, "LSC", "");
		break;
		
		// вариант N
		case "prisoner":
			dialog.text = "What do you want from me, stranger?";
			link.l1 = "Your name is Chimiset, right?";
			link.l1.go = "prisoner_1";
		break;
		
		case "prisoner_1":
			dialog.text = "Yes, it's me. Do you have a business with me or you just want to talk?";
			link.l1 = "I have some business for you. I came here from the Admiral, Shark Dodson. I have brought an order to set you free, but on one condition: you will answer several of my questions.";
			link.l1.go = "prisoner_2";
		break;
		
		case "prisoner_2":
			dialog.text = "Has Dodson decided to release me? I am glad to hear that. Ask your questions. I hope that there is no trickery in it, for otherwise my excitement has been premature.";
			link.l1 = "No tricks, I only need your help. Tell me, Chimiset, is there any strange stone idol on this Island? It turns into gold in the midnight. Don't think that I am crazy...";
			link.l1.go = "Friend_2";
		break;
		
		case "prisoner_3":
			dialog.text = "Any more questions?";
			link.l1 = "Yes. Do you know a man called the White Boy?";
			link.l1.go = "prisoner_4";
		break;
		
		case "prisoner_4":
			dialog.text = "White boy? Sure, I know him. This is the nickname of Olle Christiansen, our local idiot. He is an adult now and he doesn't look like a boy anymore, though his mind is still a childish.";
			link.l1 = "Is that so? Tell me, where can I find him?";
			link.l1.go = "prisoner_5";
		break;
		
		case "prisoner_5":
			dialog.text = "Anywhere in our city. He often could be found in the shop, tavern or walking on the streets. He has white hair, you will know him instantly.";
			link.l1 = "Excellent! One more question: have you met here a man by the name of Nathaniel Hawk? He must have shown up here some time ago, and he might be seriously ill.";
			link.l1.go = "prisoner_6";
		break;
		
		case "prisoner_6":
			dialog.text = "I can't help you with that, stranger. I don't know a man with such a name. I can assure you that he is not on Rivados' ships, neither should he be in the neutral area. I can't say the same about Narwhals' territories, though we, Rivados, don't visit them.";
			link.l1 = "Well, thanks anyway... You have helped me a lot, Chimiset!";
			link.l1.go = "prisoner_7";
		break;
		
		case "prisoner_7":
			dialog.text = "That's it? Will Shark set me free now?";
			link.l1 = "Yes. I have nothing else to ask you. Chad Kapper will free you. Well, I have to go...";
			link.l1.go = "prisoner_8";
		break;
		
		case "prisoner_8":
			dialog.text = "Stop! Wait... Come back.";
			link.l1 = "Got anything more to tell me?";
			link.l1.go = "prisoner_9";
		break;
		
		case "prisoner_9":
			dialog.text = "Not exactly... (lowering voice) I see that you are not one of Kapper's men. Do not trust him. He is a filthy scum. Not long ago, he dispassionately killed unarmed Alan Milrow with a broadsword. He was a leader of Narwhal clan. I didn't see it coming, Chad just came close to his cell and slaughtered him\Also, I have heard some talkings that Admiral's own men plan to assassinate him. Tell Shark about it. And tell him that I will say more when we talk face to face.";
			link.l1 = "Hm. Fine, I will tell Dodson about it. See you!";
			link.l1.go = "prisoner_10";
		break;
		
		case "prisoner_10":
			DialogExit();
			sld = characterFromId("Capper");
			sld.quest.chimiset_talk = "true"; // разговор с Чимисетом состоялся
			if (!CheckAttribute(npchar, "quest.capper_talk")) chrDisableReloadToLocation = true;//закрыть локацию
			else chrDisableReloadToLocation = false;//открыть локацию
			sld = characterFromId("Dodson");
			sld.dialog.currentnode = "entrance_10"; // ноду Акуле
			LSC_SetWhiteBoy(); // поставим белого мальчика
			NextDiag.CurrentNode = "prisoner_11";
			AddQuestRecord("SharkHunt", "20");
		break;
		
		case "prisoner_11":
			dialog.text = "Go to Shark and tell him everything I've told you. Eh, I wish they open this cage as soon as possible...";
			link.l1 = "Yeah, yeah. I am on my way.";
			link.l1.go = "exit";
			NextDiag.TempNode = "prisoner_11";
		break;
		
		//------------------------беседа на Протекторе, если был старт через Тартарус-----------------
		case "Friend":
			dialog.text = "There you are, my dear friend. Thanks again for saving me and trusting me, and not that bastard Kapper. I will give you these amulets to reward you. I am sure that you'll find them useful.";
			link.l1 = "Thank you! I didn't expect that...";
			link.l1.go = "Friend_1";
		break;
		
		case "Friend_1":
			GiveItem2Character(pchar, "indian_1");
			GiveItem2Character(pchar, "indian_11");
			GiveItem2Character(pchar, "amulet_1");
			PlaySound("interface\important_item.wav");
			dialog.text = "And now I am ready to listen to you. You wanted to ask me something, am I right?";
			link.l1 = "You are right, Chimiset. I need your help. First, I need to know, is there any strange stone idol on this Island? It turns into gold at midnight. Don't think that I am crazy...";
			link.l1.go = "Friend_2";
		break;
		
		// нода пересечения
		case "Friend_2":
			dialog.text = "I see what you mean, my friend. I have seen this statue of Indian gods with my own eyes. Though it turns gold only under the beams of morning sun, and not the moon... many times we had sacrificed the wicked Narwhals and the god devoured all of them. But it isn't on the Island anymore.";
			link.l1 = "How it isn't?! You wanna say it suddenly disappeared?!";
			link.l1.go = "Friend_3";
		break;
		
		case "Friend_3":
			dialog.text = "Not exactly like that. This statue was inside the 'San Geronimo'. This ship sunk with the statue several years ago.";
			link.l1 = "Such a bad luck! It looks like it is impossible to leave the Island now... And where was that ship?";
			link.l1.go = "Friend_4";
		break;
		
		case "Friend_4":
			dialog.text = "Not far from the Narwhal territories, near the wrecks of the ship named 'Phoenix'. You can see the ship rests on the seabed on a sunny day.";
			link.l1 = "Ha! So is it lying at the shoal? I can swim to it, then...";
			link.l1.go = "Friend_5";
		break;
		
		case "Friend_5":
			dialog.text = "You can't, my friend. First, it's too deep down there; second, there are many giant crabs. They will tear you apart before you get to the 'San Geronimo'.";
			link.l1 = "Hm. Fine, I'll think about it. At least, I know that the statue exists, and that is the most important thing.";
			if (CheckAttribute(npchar, "quest.chimiset_die")) link.l1.go = "prisoner_3";
			else
			{	
				if (CheckAttribute(pchar, "questTemp.LSC.Mary")) link.l1.go = "freedom_1";
				else link.l1.go = "Friend_6";
			}
			AddQuestRecord("LSC", "4");
		break;
		// нода пересечения
		
		case "Friend_6":
			dialog.text = "I see that you have more questions. Feel free to ask, my friend.";
			link.l1 = "Shark Dodson asked me to find Chad's accomplices in crime. I have found a letter in Chad's chest. There is something about some sniper and a gun. It looks like they want to shoot Shark from the large distance. Do you have any ideas?";
			link.l1.go = "Friend_7";
		break;
		
		case "Friend_7":
			dialog.text = "Hm. They are going to shoot the admiral? I need to think... Thing is that the admiral almost never leaves his residence, and when he does, he is protected by half a dozen of pirates. But he has one habit, he likes to walk around stern during late evenings\nThere are two positions for a sniper to shoot Admiral's residence - a bow of the 'Santa Florentina' and a mast pad of the 'Fury'. But a sniper still won't be able to kill the Admiral from those positions, he must be an eagle-eyed marksman at least. Also, he would need an excellent rifle. You should ask around the island about people who has access to such firearms.";
			link.l1 = "Heh, it looks like you are right, there is something about some gun in the letter... Have you seen anyone with such a gun?";
			link.l1.go = "Friend_8";
		break;
		
		case "Friend_8":
			dialog.text = "No. I haven't even seen any gun like that in my life. Ask people, perhaps, someone might tell you.";
			link.l1 = "Fine... Anyway, your information is valuable, thank you! Well, the last question now, though I don't expect you to answer... Do you know the White Boy?";
			link.l1.go = "Friend_9";
		break;
		
		case "Friend_9":
			dialog.text = "White boy? Sure, I know him. This is the nickname of Olle Christiansen, our local idiot. He is an adult now and he doesn't look like a boy anymore, though his mind is still a childish.";
			link.l1 = "Is that so? Tell me where can I find him?";
			link.l1.go = "Friend_10";
		break;
		
		case "Friend_10":
			dialog.text = "Anywhere in our city. He often could be found in the shop, tavern or walking on the streets. He has white hair - you will know him instantly.";
			link.l1 = "Great! Thanks, Chimiset, you have helped me a lot!";
			link.l1.go = "Friend_11";
		break;
		
		case "Friend_11":
			dialog.text = "I am always glad to help! Come and see me if you'll have more questions.";
			link.l1 = "Sure! I have to go now. See you!";
			if (CheckAttribute(pchar, "questTemp.LSC.Mary")) link.l1.go = "freedom_2";
			else link.l1.go = "Friend_12";
		break;
		
		case "Friend_12":
			DialogExit();
			NextDiag.CurrentNode = "Chimiset_wait";
			LSC_SetWhiteBoy(); // ставим Белого Мальчика в магазин
			pchar.questTemp.Saga.SharkHunt = "search_mush_1"; // флаг на магазин - поиск мушкета
			AddQuestRecord("SharkHunt", "11");
		break;
		
		case "freedom":
			dialog.text = "And there is my dear friend whom I owe my freedom and even my life, perhaps. Thank you for helping my brothers to save me from that filthy Kapper. I will give you these amulets to reward you. I am sure that you'll find them useful.";
			link.l1 = "Thank you! I didn't expect that...";
			link.l1.go = "Friend_1";
		break;
		
		case "freedom_1":
			dialog.text = "Have you got anything else to ask, white friend?";
			link.l1 = "Tell me, Chimiset, do you know the White Boy?";
			link.l1.go = "Friend_9";
		break;
		
		case "freedom_2":
			DialogExit();
			NextDiag.CurrentNode = "Chimiset_wait";
			LSC_SetWhiteBoy(); // ставим Белого Мальчика в магазин
		break;
		
		//--> информационный блок
		case "Chimiset_wait": // стал другом
			if (pchar.questTemp.LSC == "return" && !CheckAttribute(npchar, "quest.return_isl"))
			{
				dialog.text = "Oh! My white friend "+pchar.name+"! Didn't you drown? The spirits saved you, I know that...";
				link.l1 = "I am fine and alive, Chimiset. Spirits? Perhaps you are right, it all has happened because of Kukulcan...";
				link.l1.go = "exit";
				npchar.quest.return_isl = "true";
				break;
			}
			dialog.text = "What brings you here, my good friend?";
			/*if (!CheckAttribute(npchar, "quest.story"))
			{
				link.l1 = "Tell me how the leader of Narwhals died. You were the only one who saw that.";
				link.l1.go = "story";
			}*/
			if (!CheckAttribute(npchar, "quest.crab"))
			{
				link.l2 = "You have mentioned the crabs at the bottom near the 'San Geronimo'. Can you describe me those monsters?";
				link.l2.go = "crab";
			}
			link.l9 = "Nothing special, Chimiset. Just wanted to see you.";
			link.l9.go = "exit";
			NextDiag.TempNode = "Chimiset_wait";
		break;
		
		case "story":
			dialog.text = "A story of the death of Alan Milrow will be written here.";
			link.l1 = "Okay!";
			link.l1.go = "exit";
			npchar.quest.story = "true";
			NextDiag.TempNode = "Chimiset_wait";
		break;
		
		case "crab":
			dialog.text = "No one knows from where they came from, and why they have reached such a gigantic size. Actually, we don't know much about these beasts. They exist, a lot of people saw them. The gatherings of them can be found among ships' wrecks and at shallow water. They stalk at the bottom of the sea, hunting fish and eating all garbage we dump\nThey are a real threat. Their pincers can inflict serious wounds, also their jaws contain a fairly dangerous poison, similar to the poison of marine fish. Poisoned, left untreated, can meet the fatal consequences. Fortunately, the toxin can be neutralized by the antidote made of local herbs\nThere was a crab hunter among us. He used to bring their meat, helluva delicious dish. But the most important thing: he often brought the claws of these monsters and jaws with poison. I used them as ingredients for some potions. Pity, it's been a long since someone brought me that claws and jaws...";
			link.l1 = "And where is that hunter now?";
			link.l1.go = "crab_1";
		break;
		
		case "crab_1":
			dialog.text = "Can't you guess it? You have to be prepared to become a prey yourself while hunting those beasts. One day he just didn't come back. That is why I warn you to be careful and attentive with these creatures.";
			link.l1 = "I see...";
			link.l1.go = "exit";
			npchar.quest.crab = "true";
			NextDiag.TempNode = "Chimiset_wait";
		break;
		//<-- информационный блок
		
		case "":
			dialog.text = "";
			link.l1 = "";
			link.l1.go = "";
		break;
		
		case "":
			dialog.text = "";
			link.l1 = "";
			link.l1.go = "";
		break;
		
		case "":
			dialog.text = "";
			link.l1 = "";
			link.l1.go = "";
		break;
		
		case "":
			dialog.text = "";
			link.l1 = "";
			link.l1.go = "";
		break;
		
		case "":
			dialog.text = "";
			link.l1 = "";
			link.l1.go = "";
		break;
		
		case "":
			dialog.text = "";
			link.l1 = "";
			link.l1.go = "";
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
	}
}