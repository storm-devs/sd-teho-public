// диалог индейцев в поселениях
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;
	int i, iTemp;
	string sTemp;
	bool bOk;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "We have nothing to talk about!";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		// ==> индейцы в поселении
		case "IndianMan":
			NextDiag.TempNode = "IndianMan";
			dialog.text = NPCStringReactionRepeat(""+ GetSexPhrase("Paleface","White squaw") +" wants to talk?", 
				"You again, "+ GetSexPhrase("Paleface","White squaw") +".", 
				""+ GetSexPhrase("Paleface likes talking. He looks like a squaw.","White squaw likes talking.") +"",
                "Spirits brought my paleface "+ GetSexPhrase("brother","sister") +" to me.", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Yes.", 
				"Yea, me again.",
                "Very poetic.", 
				"I am also happy to see you.", npchar, Dialog.CurrentNode);
			link.l1.go = "IndPearlMan_1";
		break;
		
		case "IndPearlMan_1":
			dialog.text = "Say, why have you come, paleface?";
			link.l1 = "Oh, nothing in particular, just wanted to listen to what you had to say...";
			link.l1.go = "exit";
		break;
		
		case "IndianWoman":
			NextDiag.TempNode = "IndianWoman";
			dialog.text = NPCStringReactionRepeat("White man wants talk?", 
				"You again, paleface?", 
				"Paleface likes talking.",
                "Spirits brought my paleface brother to me.", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Yes.", 
				"Yea, me again.",
                "Very poetic.", 
				"I am glad to see you too.", npchar, Dialog.CurrentNode);
			link.l1.go = "IndianWoman_1";
		break;
		
		case "IndianWoman_1":
			dialog.text = LinkRandPhrase(""+npchar.name+" listen to you, son of the sea.","What do you want from "+npchar.name+", paleface?","My ears are open for your words, stranger.");
			if (CheckIndianGift() && !CheckAttribute(npchar, "quest.gift"))
			{
				link.l1 = LinkRandPhrase("I have something for you. Wanna take a look?","Wanna take a look at something really interesting? You'll surely like it...","I have something which will please you, child of the jungle. Wanna take a look?");
				link.l1.go = "gift";
			}
			link.l9 = "Oh, nothing in particular, just wanted to listen to what you had to say...";
			link.l9.go = "exit";
		break;
		
		case "gift":
			iTemp = 2;
			dialog.text = RandPhraseSimple(""+npchar.name+" wants to look. Show it.", ""+npchar.name+" is interested. Show me.");
			if (CheckCharacterItem(pchar, "mineral6"))
			{
				link.l1 = "Give a mirror.";
				link.l1.go = "gift_1";
			}
			for (i=50; i>=47; i--)
			{
				if (CheckCharacterItem(pchar, "jewelry"+i))
				{
					sTemp = "l"+iTemp;
					link.(sTemp) = "Give"+XI_ConvertString("jewelry"+i)+".";
					link.(sTemp).go = "gift_"+i;
					iTemp++;				
				}
			}
		break;
		
		case "gift_1":
			RemoveItems(pchar, "mineral6", 1);
			PlaySound("interface\important_item.wav");
			dialog.text = "Oh! Now "+npchar.name+" can look at herself not only in river water! Thank you, kind stranger!";
			link.l1 = "Sure, now you can admire your face as much as you like...";
			link.l1.go = "gift_exit";
		break;
		
		case "gift_47":
			RemoveItems(pchar, "jewelry47", 1);
			PlaySound("interface\important_item.wav");
			dialog.text = "Oh! So beautiful! This bracelet is for "+npchar.name+"? Thank you, kind stranger!";
			link.l1 = "Put it on your swarthy hand, beauty, you'll look terrific...";
			link.l1.go = "gift_exit";
		break;
		
		case "gift_48":
			RemoveItems(pchar, "jewelry48", 1);
			PlaySound("interface\important_item.wav");
			dialog.text = "Oh! What a beautiful ring? It's for "+npchar.name+", yes? Thank you, kind stranger!";
			link.l1 = "Put it on your finger, and all you friends will be jealous...";
			link.l1.go = "gift_exit";
		break;
		
		case "gift_49":
			RemoveItems(pchar, "jewelry49", 1);
			PlaySound("interface\important_item.wav");
			dialog.text = "Oh! Those wonderful green beads are for "+npchar.name+"? So beautiful! Thank you, kind stranger!";
			link.l1 = "Adorn your neck with them, daughter of the selva. Everyone will admire you...";
			link.l1.go = "gift_exit";
		break;
		
		case "gift_50":
			RemoveItems(pchar, "jewelry50", 1);
			PlaySound("interface\important_item.wav");
			dialog.text = "Oh, what a beautiful green ring! This a gift for "+npchar.name+"? Thank you, kind stranger!";
			link.l1 = "It will look great on your hand, babe...";
			link.l1.go = "gift_exit";
		break;
		
		case "gift_exit":
			if (CheckAttribute(pchar, "questTemp.Mtraxx.Merida.Women")) // Addon 2016-1 Jason Пиратская линейка
			{
				dialog.text = "Wanted to ask "+npchar.name+" anything, son of the sea?";
				link.l1 = "You are right, pretty one. Me and my fearless warriors are going to selva, to the Spanish settlement among the mountains and we are looking for a guide. I will be generous to the man himself and also to his wife. I have many riches: beautiful guns, magic glasses, mirrors, necklaces, bracelets and rings. Perhaps your husband can be the guide we are looking for?";
				link.l1.go = "hayamee";
			}
			else
			{
				DialogExit();
			}
			ChangeIndianRelation(0.75);
			npchar.quest.gift = true;
		break;
		
		// Addon 2016-1 Jason Пиратская линейка
		// Кумвана, вождь деревни араваков
		case "cumvana":
			dialog.text = "Greetings, son of the sea. Me is Kumwana, chief of the Turtle clan of Locono people. What business brings you to my village?";
			if (GetCharacterFreeItem(pchar, "pistol5") > 0 || CheckCharacterItem(pchar, "compass1") || GetCharacterFreeItem(pchar, "spyglass1") > 0 || GetCharacterFreeItem(pchar, "spyglass2") > 0 || GetCharacterFreeItem(pchar, "spyglass3") > 0)
			{
				link.l1 = "I brought you a gift, chief. Take a look, you are going to like it.";
				link.l1.go = "cumvana_2";
			}
			else 
			{
				link.l1 = "Chief, I've come to ask for your assistance. I want to reach a Spanish settlement called Merida, it's located among the mountains in your selva, problem is I don't know how to get there.";
				link.l1.go = "cumvana_no";
			}
		break;
		
		case "cumvana_no":
			dialog.text = "What is very good for you, son of the sea, not knowing the road there. It leads through a forest, a land of fearless tribe of Capong. True jaguars, they are, oh-ey! Me never go that Spanish place. My people - peaceful people, we not go to land of Capong. Kumwana cannot give you an advice.";
			link.l1 = "But the Spanish found a way there! And I am not afraid of those Capongs...";
			link.l1.go = "cumvana_no_1";
		break;
		
		case "cumvana_no_1":
			dialog.text = "But you should. The are cruel people. They kill my people in woods. Kumwana said it all.";
			link.l1 = "Well, shit...";
			link.l1.go = "cumvana_no_2";
		break;
		
		case "cumvana_no_2":
			DialogExit();
			AddQuestRecord("Roger_5", "5");
			npchar.dialog.currentnode = "cumvana_1";
		break;
		
		case "cumvana_1":
			dialog.text = "Oh-ey! You again, son of the sea. What do you want to say to Kumwana?";
			if (GetCharacterFreeItem(pchar, "pistol5") > 0 || CheckCharacterItem(pchar, "compass1") || GetCharacterFreeItem(pchar, "spyglass1") > 0 || GetCharacterFreeItem(pchar, "spyglass2") > 0 || GetCharacterFreeItem(pchar, "spyglass3") > 0)
			{
				link.l1 = "I brought you a gift, chief. Take a look, you are going to like it.";
				link.l1.go = "cumvana_2";
			}
			else 
			{
				link.l1 = "A hope to find Merida is still with me...";
				link.l1.go = "cumvana_1_1";
			}
		break;
		
		case "cumvana_1_1":
			DialogExit();
			npchar.dialog.currentnode = "cumvana_1";
		break;
		
		case "cumvana_2":
			dialog.text = "Locono are always glad to see good friends.";
			if (GetCharacterFreeItem(pchar, "pistol5") > 0)
			{
				link.l1 = "Gift a handgun."; // 5
				link.l1.go = "cumvana_2_1";
			}
			if (CheckCharacterItem(pchar, "compass1")) // 3
			{
				link.l2 = "Gift a compass.";
				link.l2.go = "cumvana_2_2";
			}
			if (GetCharacterFreeItem(pchar, "spyglass1") > 0)
			{
				link.l3 = "Gift a cheap spy glass.";
				link.l3.go = "cumvana_2_3";
			}
			if (GetCharacterFreeItem(pchar, "spyglass2") > 0)
			{
				link.l4 = "Gift a common spy glass."; // 2
				link.l4.go = "cumvana_2_4";
			}
			if (GetCharacterFreeItem(pchar, "spyglass3") > 0)
			{
				link.l5 = "Gift a decent spy glass."; // 4
				link.l5.go = "cumvana_2_5";
			}
		break;
		
		case "cumvana_2_1":
			Log_Info("You have given a pistol");
			Log_Info("You have received amulets");
			PlaySound("interface\important_item.wav");
			RemoveItems(pchar, "pistol5", 1);
			GiveItem2Character(pchar, "obereg_9");
			GiveItem2Character(pchar, "indian_7");
			GiveItem2Character(pchar, "obereg_3");
			dialog.text = "Oh-ey! What a pretty paleface weapon! Kumwana accepts your gift! You too, son of the sea, accept a gift from Kumwana and Locono people.";
			link.l1 = "Gratitude, chief!..";
			link.l1.go = "cumvana_3";
		break;
		
		case "cumvana_2_2":
			Log_Info("You have given a compass");
			Log_Info("You have received amulets");
			PlaySound("interface\important_item.wav");
			RemoveItems(pchar, "compass1", 1);
			GiveItem2Character(pchar, "indian_10");
			GiveItem2Character(pchar, "indian_6");
			GiveItem2Character(pchar, "obereg_1");
			dialog.text = "Oh-ey! Magic amulet of palefaces! Kumwana accepts your gift! You too, son of the sea, accept a gift from Kumwana and Locono people.";
			link.l1 = "Gratitude, chief!..";
			link.l1.go = "cumvana_3";
		break;
		
		case "cumvana_2_3":
			Log_Info("You have given a cheap spy glass");
			Log_Info("You have received amulets");
			PlaySound("interface\important_item.wav");
			RemoveItems(pchar, "spyglass1", 1);
			GiveItem2Character(pchar, "obereg_2");
			GiveItem2Character(pchar, "indian_5");
			GiveItem2Character(pchar, "obereg_1");
			dialog.text = "Oh-ey! Magic tube of palefaces! Kumwana accepts your gift! You too, son of the sea, accept a gift from Kumwana and Locono people.";
			link.l1 = "Gratitude, chief!..";
			link.l1.go = "cumvana_3";
		break;
		
		case "cumvana_2_4":
			Log_Info("You have given a common spy glass");
			Log_Info("You have received amulets");
			PlaySound("interface\important_item.wav");
			RemoveItems(pchar, "spyglass2", 1);
			GiveItem2Character(pchar, "obereg_6");
			GiveItem2Character(pchar, "indian_6");
			GiveItem2Character(pchar, "obereg_1");
			dialog.text = "Oh-ey! Magic tube of palefaces! Kumwana accepts your gift! You too, son of the sea, accept a gift from Kumwana and Locono people.";
			link.l1 = "Gratitude, chief!..";
			link.l1.go = "cumvana_3";
		break;
		
		case "cumvana_2_5":
			Log_Info("You have given a decent spy glass");
			Log_Info("You have received amulets");
			PlaySound("interface\important_item.wav");
			RemoveItems(pchar, "spyglass3", 1);
			GiveItem2Character(pchar, "obereg_9");
			GiveItem2Character(pchar, "indian_7");
			GiveItem2Character(pchar, "obereg_5");
			dialog.text = "Oh-ey! Magic tube of palefaces! Kumwana accepts your gift! You too, son of the sea, accept a gift from Kumwana and Locono people.";
			link.l1 = "Gratitude, chief!..";
			link.l1.go = "cumvana_3";
		break;
		
		case "cumvana_3":
			dialog.text = "What brings you to our village, son of the sea?";
			link.l1 = "Chief, I've come to ask for your assistance. I want to reach a Spanish settlement called Merida, it's located among the mountains in your selva, problem is I don't know how to get there. Perhaps, you could provide me with a brave warrior who would show us the way there?";
			link.l1.go = "cumvana_4";
		break;
		
		case "cumvana_4":
			dialog.text = "Oh-ey! Dangerous road, dangerous. The way there leads through a forest, a land of fearless tribe of Capong. True jaguars, they are, oh-ey! Me never go that Spanish place. My people - peaceful people, we not go to land of Capong.";
			link.l1 = "I really have to get to Merida. Kumwana, ask your me please, perhaps, someone will agree to join my unit? My warriors are experienced, well-armed and fear nothing. We will protect the guide and reward him generously when it's over.";
			link.l1.go = "cumvana_5";
		break;
		
		case "cumvana_5":
			dialog.text = "Very well, son of the sea. I will assemble a circle of warriors and tell them about your wishes. See me after dawn tomorrow.";
			link.l1 = "Gratitude, chief!";
			link.l1.go = "cumvana_6";
		break;
		
		case "cumvana_6":
			DialogExit();
			npchar.dialog.currentnode = "cumvana_7";
			AddQuestRecord("Roger_5", "6");
			pchar.quest.mtraxx_merida_wait.win_condition.l1 = "Timer";
			pchar.quest.mtraxx_merida_wait.win_condition.l1.date.hour  = 7.0;
			pchar.quest.mtraxx_merida_wait.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.mtraxx_merida_wait.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.mtraxx_merida_wait.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.mtraxx_merida_wait.function = "Mtraxx_MeridaCumvanaTimer";
			AddCharacterExpToSkill(pchar, "Leadership", 150);
		break;
		
		case "cumvana_7":
			dialog.text = "Oh-ey! You again, son of the sea. What do you want to say to Kumwana?";
			link.l1 = "Nothing yet, chief.";
			link.l1.go = "cumvana_7x";
		break;
		
		case "cumvana_7x":
			DialogExit();
			npchar.dialog.currentnode = "cumvana_7";
		break;
		
		case "cumvana_8":
			dialog.text = "Son of the sea, it's you. Kumwana talked with warriors of the Locono.";
			link.l1 = "And? Do you have a volunteer?";
			link.l1.go = "cumvana_9";
		break;
		
		case "cumvana_9":
			dialog.text = "We have a few hunters around who has been there. But they fear Capongs, the jaguars are on warpath. They not go, they say Capong kill your unit. They fear not palefaces.";
			link.l1 = "My warriors are much better than any of them! Part of my unit has spent a lifetime in the jungle! We are not some amateurs!";
			link.l1.go = "cumvana_10";
		break;
		
		case "cumvana_10":
			dialog.text = "I am sorry, son of the sea. My hunters fear, Capongs are dangerous, very very.";
			link.l1 = "Fine, then perhaps, they can explain how to get there? In details.";
			link.l1.go = "cumvana_11";
		break;
		
		case "cumvana_11":
			dialog.text = "To get there you should sail on river and then disembark at the special place. If it is a wrong place, you will get into swamp and die. Our selva is full of danger. You won't find the place on your own, son of the sea.";
			link.l1 = RandSwear()+"And what should I do then? How to persuade your hunters?";
			link.l1.go = "cumvana_12";
		break;
		
		case "cumvana_12":
			dialog.text = "Kumwana say no more, son of the sea.";
			link.l1 = "Fine...";
			link.l1.go = "cumvana_13";
		break;
		
		case "cumvana_13":
			DialogExit();
			npchar.dialog.currentnode = "cumvana_7";
			AddQuestRecord("Roger_5", "7");
			pchar.questTemp.Mtraxx = "merida_advice";
		break;
		
		// Хайами
		case "hayamee":
			if (npchar.id == "Hayamee")
			{
				dialog.text = "My husband Tagofa is the best hunter of tribe. Oh-ey! "+npchar.name+" is proud of her husband. "+npchar.name+" often goes with Tagofa in Selva. Go far away. Tagofa knows where is Spanish settlement.";
				link.l1 = ""+npchar.name+", I will give a lot of gifts to you and Tagofa if he shows us the way there. Where can I find him?";
				link.l1.go = "hayamee_1";
			}
			else
			{
				dialog.text = RandPhraseSimple(RandPhraseSimple("My husband not go selva, son of the sea. He catches fish. Good fisher, oh-ey! ","My husband good hunter, oh-ey, but he now goes deep jungle."), RandPhraseSimple("Jaguar wounded my husband on hunt. Now he sits in village, makes arrows, oh-ey!","Six moons ago three Capongs attack my husband. Now he not go hunt far from village. Never! oh-ey!"));
				link.l1 = LinkRandPhrase("Pity...","Too bad...","What a pity..."));
				link.l1.go = "exit";
			}
		break;
		
		case "hayamee_1":
			dialog.text = "Tagofa went hunt a day ago. Promised come back tomorrow when the sun sleeps. Come tomorrow son of the sea, I be with Tagofa in that hut. I ask him he go or not go with you.";
			link.l1 = "Tell Tagofa that I will gift him with the prettiest handgun. And you, I will gift you with a lot of jewels.";
			link.l1.go = "hayamee_2";
		break;
		
		case "hayamee_2":
			dialog.text = "Oh-ey!";
			link.l1 = "...";
			link.l1.go = "hayamee_3";
		break;
		
		case "hayamee_3":
			DialogExit();
			AddQuestRecord("Roger_5", "9");
			DeleteAttribute(pchar, "questTemp.Mtraxx.Merida.Women");
			LAi_CharacterDisableDialog(npchar);
			pchar.quest.mtraxx_merida_wait1.win_condition.l1 = "Timer";
			pchar.quest.mtraxx_merida_wait1.win_condition.l1.date.hour  = 22.0;
			pchar.quest.mtraxx_merida_wait1.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.mtraxx_merida_wait1.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.mtraxx_merida_wait1.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.mtraxx_merida_wait1.function = "Mtraxx_MeridaHayameeTimer";
		break;
		
		case "hayamee_4":
			pchar.quest.Mtraxx_MeridaPotionLate.over = "yes";
			dialog.text = ""+npchar.name+" is glad see a son of the sea. Tagofa came back. But he has drunk too much kasheeri and sleeps. Not wake up him, Tagofa rests. I will talk.";
			link.l1 = "Very well, "+npchar.name+". Will your husband guide us to Merida?";
			link.l1.go = "hayamee_5";
		break;
		
		case "hayamee_5":
			dialog.text = "Tagofa agreed to guide your warriors through the selva to Spanish village. But there are terms...";
			link.l1 = "Which are?";
			link.l1.go = "hayamee_6";
		break;
		
		case "hayamee_6":
			dialog.text = "You protect Tagofa from Capong warriors. Tagofa not fight no Spanish, no Capong. If he faces danger, he will run away and no one find him, he is the best Locono hunter.";
			link.l1 = "I see. You worry about your man, this is understandable. I promise you that we will deal with all those Capongs on our own.";
			link.l1.go = "hayamee_7";
		break;
		
		case "hayamee_7":
			dialog.text = "Oh-ey! Tagofa wants gifts from son of the sea: one small to shoot bullets and one big to shoot small stones. Also he wants bullets for each gun: as many as fingers both hands three times.";
			link.l1 = "Whoa! Your man knows something about guns, huh? Very well. What else?";
			link.l1.go = "hayamee_8";
		break;
		
		case "hayamee_8":
			dialog.text = "Tagofa wants a magic eye of palefaces.";
			link.l1 = "A spy glass? Fine. Anything else?";
			link.l1.go = "hayamee_9";
		break;
		
		case "hayamee_9":
			dialog.text = "No more for Tagofa. "+npchar.name+" wants pretty things. Gold ring with big red stone and beads of many many green stones. "+npchar.name+" saw it on white Mary in Maracaibo.";
			link.l1 = "A golden ring with ruby and jade beads?";
			link.l1.go = "hayamee_10";
		break;
		
		case "hayamee_10":
			dialog.text = "Not jade. It's shiny and white men value it.";
			link.l1 = "Emerald? Emerald beads?";
			link.l1.go = "hayamee_11";
		break;
		
		case "hayamee_11":
			dialog.text = "Oh-ey!";
			link.l1 = "Heh, "+npchar.name+" knows something about jewels! Very well, you'll get it.";
			link.l1.go = "hayamee_12";
		break;
		
		case "hayamee_12":
			dialog.text = "Bring all things to "+npchar.name+" together, son of the sea. Then Tagofa will guide you and your warriors. Not waste time, in a half of moon Tagofa and me will go to neighbor village. For a high day. Now go, "+npchar.name+" wants to sleep.";
			link.l1 = "I won't make you wait for too long. See you.";
			link.l1.go = "hayamee_13";
		break;
		
		case "hayamee_13":
			DialogExit();
			AddQuestRecord("Roger_5", "10");
			LAi_CharacterDisableDialog(npchar);
			SetFunctionTimerCondition("Mtraxx_MeridaHayameeLate", 0, 0, 15, false); // таймер
			// Тагофу в сидячее положение
			pchar.quest.mtraxx_merida_wait2.win_condition.l1 = "Timer";
			pchar.quest.mtraxx_merida_wait2.win_condition.l1.date.hour  = 9.0;
			pchar.quest.mtraxx_merida_wait2.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.mtraxx_merida_wait2.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.mtraxx_merida_wait2.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.mtraxx_merida_wait2.function = "Mtraxx_MeridaTagofaHide";
		break;
		
		case "hayamee_14":
			bOk = GetCharacterFreeItem(pchar, "spyglass1") > 0 || GetCharacterFreeItem(pchar, "spyglass2") > 0 || GetCharacterFreeItem(pchar, "spyglass3") > 0;
			dialog.text = "You brought what "+npchar.name+" and Tagofa asked?";
			if (bOk && GetCharacterFreeItem(pchar, "pistol3") > 0 && GetCharacterFreeItem(pchar, "pistol5") > 0 && GetCharacterItem(pchar, "bullet") >= 30 && GetCharacterItem(pchar, "grapeshot") >= 30 && GetCharacterItem(pchar, "gunpowder") >= 60 && CheckCharacterItem(pchar, "jewelry41") && CheckCharacterItem(pchar, "jewelry42"))
			{
				link.l1 = "Yes. Everything is according to your list.";
				link.l1.go = "hayamee_15";
			}
			else
			{
				link.l1 = "No, I am still on it.";
				link.l1.go = "hayamee_14x";
			}
		break;
		
		case "hayamee_14x":
			DialogExit();
			npchar.dialog.currentnode = "hayamee_14";
		break;
		
		case "hayamee_15":
			pchar.quest.Mtraxx_MeridaHayameeLate.over = "yes";
			Mtraxx_MeridaRemoveGifts();
			dialog.text = ""+npchar.name+" is happy, son of the sea. I now call husband. He goes with you. But remember what you promised to "+npchar.name+"!";
			link.l1 = "Yes-yes, I remember everything.";
			link.l1.go = "hayamee_16";
		break;
		
		case "hayamee_16":
			DialogExit();
			chrDisableReloadToLocation = true;
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", 7.0);
			DoQuestFunctionDelay("Mtraxx_MeridaTagofaEnter", 20.0);
			AddCharacterExpToSkill(pchar, "Leadership", 100);
		break;
			
		case "CitizenNotBlade":
			dialog.text = "Put away your weapon, paleface, or we will force you to do it!";
			link.l1 = LinkRandPhrase("Fine.", "Okay.", "Don't worry, I am putting it away...");
			link.l1.go = "exit";
		break;  

	}
}
