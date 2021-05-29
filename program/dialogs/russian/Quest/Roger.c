// диалоги персонажей по пиратской линейке // Addon 2016-1 Jason пиратская линейка
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i;
	string sTemp, attrL;
	
	DeleteAttribute(&Dialog,"Links");
	
	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	attrL = Dialog.CurrentNode;
	
	if(HasSubStr(attrL, "ShipStockManBack_"))
 	{
        i = findsubstr(attrL, "_" , 0);
	 	NPChar.ShipToStoreIdx = strcut(attrL, i+1, strlen(attrL)-1); // индех в конце
 	    Dialog.CurrentNode = "ShipStockManBack";
 	}

	switch(Dialog.CurrentNode)
	{
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
        case "First time":
			dialog.text = "What do you want?";
			link.l1 = "I should go...";
			link.l1.go = "exit";
		break;
		
		// Лопе Монторо
		case "Mtr_officer":
			if (pchar.questTemp.Mtraxx != "fail" && pchar.questTemp.Mtraxx == "jewelry_5")
			{
				pchar.quest.Mtraxx_JewelryHavanaOver.over = "yes"; //снять таймер
				dialog.text = "For fuck's sake, who the hell are you?";
				link.l1 = "Good day, don Lope. Though we haven't been acquainted yet, now would be as good time as any. Especially now that I'm so eager to help you get out of this difficult situation...";
				link.l1.go = "Mtr_officer_1";
			}
			else
			{
				dialog.text = "What do you want?";
				link.l1 = "I should go...";
				link.l1.go = "exit";
			}
		break;
		
		case "Mtr_officer_1":
            dialog.text = "Help? Me? What a turn of events! Would you enlighten me, senior, where such generosity comes from?";
			link.l1 = "Certainly. I am looking for your former captain, Esberdo Cabanas, and I don't have much time... preferably, I would like to meet him in that place he keeps in a secret. Even better if I'd arrive there before he does.";
			link.l1.go = "Mtr_officer_2";
		break;
		
		case "Mtr_officer_2":
            dialog.text = "Ha-ha! I told this pathetic idiot to keep his mouth shut! The blue amber, right?";
			link.l1 = "Good thinking, my good sir.";
			link.l1.go = "Mtr_officer_3";
		break;
		
		case "Mtr_officer_3":
            dialog.text = "Then let us make haste. I would love to tell you every last detail if you find a way to get me out of here. You know how I ended up in this hole?";
			link.l1 = "In overall, yes.";
			link.l1.go = "Mtr_officer_4";
		break;
		
		case "Mtr_officer_4":
            dialog.text = "I was dead drunk when that happened. Fuck that bloody bartender! I don't remember a thing. I was told everything only when I woke up in a hold of the 'Cantavro'. It would all be behind us if we just sailed away, both the commandant and the alcalde were willing to turn the other way. But that damned don Esberdo simply put me in jail. You think he's done that 'to do the right thing'? If only, this scoundrel just wanted to keep my share of the ambers\nIt was me who mentioned there can be more ambers under water, than what we found on the beach. It was me, who found a way to get it. I was to receive a hefty cut, but... oh, that son of a whore! Ugh, enough about that. Neither the alcalde, nor the commandant, nor even don de Toledo are happy I am being kept here. If it wasn't for that peasant and his cow wife, who fluttered the dovecotes... either way, they won't object you helping me\nTalk to the governor, pretend to be my old friend from Europe - I will confirm that. What is your name, by the way?";
			link.l1 = ""+GetFullName(pchar)+".";
			link.l1.go = "Mtr_officer_5";
		break;
		
		case "Mtr_officer_5":
            dialog.text = ""+GetFullName(pchar)+", wonderful. Go see don Diego de Toledo and ask him for advice. Remember, you only have three days, chasing the 'Cantavro' would be pointless after that. Set me free and I will give you everything you need to deal with that bastard, Cabanas.";
			link.l1 = "I'll go see the governor at once, don Lope. I will do my best to resolve this situation for both our sakes.";
			link.l1.go = "Mtr_officer_6";
		break;
		
		case "Mtr_officer_6":
            DialogExit();
			pchar.questTemp.Mtraxx = "jewelry_6";
			LAi_CharacterDisableDialog(npchar);
			AddQuestRecord("Roger_1", "8");
			SetFunctionTimerCondition("Mtraxx_TimeclearPrison", 0, 0, 4, false); // таймер
		break;
		
		case "Mtr_officer_7":
			pchar.quest.Mtraxx_TimeclearPrison.over = "yes"; //снять таймер
            dialog.text = "So, the huckster and his clocking hen got their revenge, and I am done with this hole. You have my gratitude, senior, you have done your part. Now allow me to do mine.";
			link.l1 = "I am all ears!";
			link.l1.go = "Mtr_officer_8";
		break;
		
		case "Mtr_officer_8":
            dialog.text = "Good. During our previous patrol we got hit by a storm which made us abandon our course. We landed on the beach of Western Main, not far from Mosquitoes Coast to get some fresh water. We found a good deposit of blue amber there. I did some prospecting and found a pile of it under water. We needed equipment to gather it, that's why we decided to return later\nEsberdo had bought five long boats in Havana for Indians to dive and gather the amber. You know the rest of the story - the scum got rid of me and sailed away. Find him at Mosquitoes Coast and make haste - according to my calculations, all you have is about five days to get there. Hope you catch the fucker in the middle of the gathering, take away all his amber and stab his belly for numerous times. Be careful, my former captain is a skilled fighter and a seaman. Godspeed, senor.";
			link.l1 = "Same to you, Lope. Farewell!";
			link.l1.go = "Mtr_officer_9";
		break;
		
		case "Mtr_officer_9":
            DialogExit();
			pchar.questTemp.Mtraxx = "jewelry_10";
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeday = 0;
			AddQuestRecord("Roger_1", "12");
			SetFunctionTimerCondition("Mtraxx_TimeclearGulf", 0, 0, 5, false); // таймер
			pchar.quest.mtr_jewelry_gulf.win_condition.l1 = "location";
			pchar.quest.mtr_jewelry_gulf.win_condition.l1.location = "Santacatalina";
			pchar.quest.mtr_jewelry_gulf.function = "Mtraxx_JewelryGulf";
			DeleteAttribute(pchar, "GenQuest.PrisonQuestLock");
		break;
		
		// Росарио Гусман
		case "Mtr_rosario":
            dialog.text = "Want to ask anything, sir?";
			link.l1 = "Concerning don Montoro. We are old acquaintances and I was really upset when I learnt about his misfortunes. Don Diego de Toledo has sent me to you, said that you had already tried to set our mutual friend free...";
			link.l1.go = "Mtr_rosario_1";
		break;
		
		case "Mtr_rosario_1":
            dialog.text = "Hm... senor, this is a bit... unexpected, but I am glad to meet a friend of Lope! He has been unlucky for quite a while already and now this...";
			link.l1 = "What can we do for him? No way for a noble hidalgo to rot among the scum of the society!";
			link.l1.go = "Mtr_rosario_2";
		break;
		
		case "Mtr_rosario_2":
            dialog.text = "A man of business! It is both easy and difficult to help poor Lope. I had a talk with the profiteer poor Lope was unlucky to have an argument with. He is agree to meet us halfway for five hundred doubloons. Quite a sum for his and his wife's 'sufferings'. Alas, I have only managed to gather a half of the required sum - two hundred and fifty doubloons.";
			link.l1 = "So, if I get you another two hundred and fifty doubloons then don Lope will be set free?";
			link.l1.go = "Mtr_rosario_3";
		break;
		
		case "Mtr_rosario_3":
            dialog.text = "Yes. The greedy bastard promised me to spread the word that Lope compensated him all the damage. He will also ask the governor to pardon him.";
			if (GetCharacterItem(pchar, "gold_dublon") >= 250)
			{
				link.l1 = "I have the sum required with me right now. Here, let this greedy bourgeois choke on it.";
				link.l1.go = "Mtr_rosario_4";
			}
			link.l2 = "I'll do my best to get money as soon as possible.";
			link.l2.go = "Mtr_rosario_5";
		break;
		
		case "Mtr_rosario_4":
			RemoveItems(pchar, "gold_dublon", 250);
			Log_Info("You have given 250 doubloons");
			PlaySound("interface\important_item.wav");
            dialog.text = "I can't believe my own ears! Senor, you must have been sent by the Lord!";
			link.l1 = "When they will set our man free?";
			link.l1.go = "Mtr_rosario_8";
		break;
		
		case "Mtr_rosario_5":
            dialog.text = "Glad to hear it, senor. You are a true friend of Lope and a true nobleman.";
			link.l1 = "Goodbye!";
			link.l1.go = "Mtr_rosario_6";
		break;
		
		case "Mtr_rosario_6":
            DialogExit();
			AddQuestRecord("Roger_1", "10");
			npchar.dialog.currentnode = "Mtr_rosario_7";
		break;
		
		case "Mtr_rosario_7":
            dialog.text = "Did you bring the money?";
			if (GetCharacterItem(pchar, "gold_dublon") >= 250)
			{
				link.l1 = "I have the sum required with me right now. Here, let this greedy bourgeois choke on it.";
				link.l1.go = "Mtr_rosario_4";
			}
			link.l2 = "I am still on it.";
			link.l2.go = "Mtr_rosario_7_1";
		break;
		
		case "Mtr_rosario_7_1":
            DialogExit();
			npchar.dialog.currentnode = "Mtr_rosario_7";
		break;
		
		case "Mtr_rosario_8":
            dialog.text = "I'll bring the money to the sly bastard tonight. I believe they will have got an order of our friend's release by a midday. Hope we'll gather together to celebrate later?";
			link.l1 = "Sure thing, don Rosario. I should go now. See you!";
			link.l1.go = "Mtr_rosario_9";
		break;
		
		case "Mtr_rosario_9":
            DialogExit();
			AddQuestRecord("Roger_1", "11");
			npchar.lifeday = 1;
			npchar.dialog.currentnode = "Mtr_rosario_10";
			pchar.quest.mtr_prisoner.win_condition.l1 = "Timer";
			pchar.quest.mtr_prisoner.win_condition.l1.date.hour  = 12;
			pchar.quest.mtr_prisoner.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.mtr_prisoner.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.mtr_prisoner.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.mtr_prisoner.function = "Mtraxx_PrisonerFree";
		break;
		
		case "Mtr_rosario_10":
            dialog.text = "Soon our friend will be free!";
			link.l1 = "...";
			link.l1.go = "exit";
			npchar.dialog.currentnode = "Mtr_rosario_10";
		break;
		
		// Лысый Джеффри
		case "Jeffry":
			pchar.quest.Mtraxx_SilkCPVOver.over = "yes"; //снять прерывание
            dialog.text = "Hey, what the hell are you doing on my ship? I don't think you have got my invitation, huh?";
			link.l1 = "Quite, Geffrey. I am from Tyrex regarding the ship silk business.";
			link.l1.go = "Jeffry_1";
		break;
		
		case "Jeffry_1":
            dialog.text = "A-ah, let's talk then. What's he planning? I've had a talk with smugglers already, they offer a fine price for the goods...";
			link.l1 = "And how much, if I may ask?";
			link.l1.go = "Jeffry_2";
		break;
		
		case "Jeffry_2":
            dialog.text = "1300 pesos for a roll. I think it's a good price.";
			link.l1 = "Yeah, and Tyrex wants twenty golden pieces for a roll. Not a coin less. And I mean doubloons. He gave me a job to find a right buyer for that price.";
			link.l1.go = "Jeffry_3";
		break;
		
		case "Jeffry_3":
            dialog.text = "Ha-ha-ha, boy, lucky you! Marcus does have an appetite! Well, go find such a buyer then, it'd be glorious to watch you try.";
			link.l1 = "Yeah, this is all very fucking ridiculous. Do I look happy? I don't. So I suggest you stopping this laughing and help me out.";
			link.l1.go = "Jeffry_4";
		break;
		
		case "Jeffry_4":
            dialog.text = "Fine, fine, pal... Jesus, you are not very fond of jokes, huh? You are not to be blamed for Tyrex's fantasies, we will all get our share of this, trust me. But how can I possibly help you? You can't sell it in stores, customs are not an option either, only smugglers left. Who's else? Think of it.";
			link.l1 = "I've been thinking about it since Hispaniola... Whatever. I have only two months to find a regular buyer. Something must be done about this. Your orders are to land in the nearest bay and do repairs.";
			link.l1.go = "Jeffry_5";
		break;
		
		case "Jeffry_5":
            dialog.text = "Two months?! What the hell? Ah, screw this. The 'Snake' does need a repair and cleaning or she won't be able to chase down even a barque. Hey, French whores, Bald Geffrey's crew is staying in Capsterville for two months! Good luck to you, pal, in your pointless searches. If you find an idiot ready to pay Marcus's price for this damn silk - you know where to find me.";
			link.l1 = "Wait! Give me one roll of this silk. I need to show the goods to potential buyers.";
			link.l1.go = "Jeffry_6";
		break;
		
		case "Jeffry_6":
            dialog.text = "Sure, no problem. I'll send it to you on a longboat.";
			link.l1 = "Good. See you!";
			link.l1.go = "Jeffry_7";
		break;
		
		case "Jeffry_7":
            DialogExit();
			AddQuestRecord("Roger_2", "3");
			npchar.DeckDialogNode = "Jeffry_8";
			npchar.dialog.currentnode = "Jeffry_8";
			pchar.questTemp.Mtraxx = "silk_2";
			AddCharacterGoods(pchar, GOOD_SHIPSILK, 1);
			SetFunctionTimerCondition("Mtraxx_SilkTimeOver", 0, 0, 61, false); // таймер
		break;
		
		case "Jeffry_8":
            dialog.text = "Anything else, pal?";
			link.l1 = "Nothing at the moment...";
			link.l1.go = "Jeffry_8_1";
		break;
		
		case "Jeffry_8_1":
            DialogExit();
			npchar.DeckDialogNode = "Jeffry_8";
			npchar.dialog.currentnode = "Jeffry_8";
		break;
		
		case "Jeffry_9":
			pchar.quest.Mtraxx_SilkTimeOver.over = "yes";
            dialog.text = "How are you doing, pal?";
			link.l1 = "Doing great. I have found us a buyer. Twenty five doubloons for a roll. I believe Tyrex will like it.";
			link.l1.go = "Jeffry_10";
		break;
		
		case "Jeffry_10":
            dialog.text = "No way! You are the resourceful son of a devil! How did you manage that, huh?";
			link.l1 = "It's a long story, Geffrey. Now listen. You should arrive to Cape Negril of Jamaica between 10th and 15th. They will be waiting for you there at nights. Password is 'A merchant of Lyons'. Got it? Repeat.";
			link.l1.go = "Jeffry_11";
		break;
		
		case "Jeffry_11":
            dialog.text = "A merchant of Lyons. I got it. I should tell my purser to write it down, he is the only man here who can write. Ha-ha!";
			link.l1 = "Do you have one hundred rolls in a cargo hold?";
			link.l1.go = "Jeffry_12";
		break;
		
		case "Jeffry_12":
            dialog.text = "I've got even more.";
			link.l1 = "Splendid. It's time for you to set sails then. Don't let me down!";
			link.l1.go = "Jeffry_13";
		break;
		
		case "Jeffry_13":
            dialog.text = "Relax, pal, everything will be done as it should be done.";
			link.l1 = "Godspeed, Geffrey. Perhaps, we'll meet again.";
			link.l1.go = "Jeffry_14";
		break;
		
		case "Jeffry_14":
            DialogExit();
            AddQuestRecord("Roger_2", "22");
			pchar.questTemp.Mtraxx = "silk_14"; // к Тираксу
			sld = characterFromId("Terrax");
			sld.dialog.currentnode = "mtraxx_12";
			pchar.quest.mtraxx_hide_jeffry.win_condition.l1 = "MapEnter";
			pchar.quest.mtraxx_hide_jeffry.function = "Mtraxx_SilkHideJeffry";
		break;
		
		case "Jeffry_15":
            dialog.text = "Ho! Cunning Charley Prince, in flesh! Very nice!";
			link.l1 = "Bald Geffrey! Charley Prince you said? Ha!";
			link.l1.go = "Jeffry_15x";
		break;
		
		case "Jeffry_15x":
            dialog.text = "Never heard your second name before? That's how they call you in La Vega now.";
			link.l1 = "I see where Charley came from, but why Prince?";
			link.l1.go = "Jeffry_15y";
		break;
		
		case "Jeffry_15y":
            dialog.text = "You are the only noble son of the bitch in La Vega! Ha-ha! How are you doing? Have you been at Pasquale's shop? Bought supplies from the old scum?";
			link.l1 = "Never again!";
			link.l1.go = "Jeffry_16";
		break;
		
		case "Jeffry_16":
            dialog.text = "K-ha! Why, didn't you like him? Did he sell you salt beef for the price of rum?";
			link.l1 = "Worse! I got a lead from him on a Dutch caravan loaded with iron wood. It wasn't easy to find it, to board the merchant and then to protect that fucking wood from a few dozens of rats! And think what, the bastard paid me 150 pesos for a piece. For a piece of fucking iron wood, Geffrey!";
			link.l1.go = "Jeffry_17";
		break;
		
		case "Jeffry_17":
            dialog.text = "It happens all the time pal, I assure you. Lavoisier have already screwed a dozen of good lads like you. He actually paid you something which is rare for him. We don't take his 'leads' even if we are starving.";
			link.l1 = "Thank you friend, at least now I know that I wasn't the first and the only idiot! But this time the bastard have screwed himself. I'll make sure of it.";
			link.l1.go = "Jeffry_18";
		break;
		
		case "Jeffry_18":
            dialog.text = "Hey-hey! Prince you should calm down a bit. The huckster is untouchable here. Dare to plunder him - Marcus will be there for your ass. Tell me, was it Tyrex who senе you to Lavoisier?";
			link.l1 = "Hm. Yeah...";
			link.l1.go = "Jeffry_19";
		break;
		
		case "Jeffry_19":
            dialog.text = "Listen then... (lowering his voice) They say that the four-eyes shares with Marcus. See? This is why no pirate will ever dare to attack Lavoisier's ships .";
			link.l1 = "Noted. Thanks for warning Geffrey. Farewell and Godspeed!";
			link.l1.go = "Jeffry_20";
		break;
		
		case "Jeffry_20":
            dialog.text = "Same to you pal.";
			link.l1 = "...";
			link.l1.go = "Jeffry_21";
		break;
		
		case "Jeffry_21":
            DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload4_back", "none", "", "", "OpenTheDoors", 15.0);
			AddQuestRecord("Roger_4", "10");
			CloseQuestHeader("Roger_4");
			sld = characterFromId("Terrax");
		    sld.dialog.currentnode = "mtraxx_34";
			bDisableFastReload = false;
			pchar.questTemp.Mtraxx.CharleePrince = "true"; // атрибут - ГГ известный пират
		break;
		
		case "Jeffry_22":
            dialog.text = "Ho Prince! I was wondering who made the fireworks! Brought a squad of musketeers in case it was the Spanish.";
			link.l1 = "Geffrey? You are here too? But how? Did you buy the treasure map as well?";
			link.l1.go = "Jeffry_23";
		break;
		
		case "Jeffry_23":
            dialog.text = "Pal, I don't waste my money on shit like this. They delivered me a diary of some traveler who wrote about a safe passage to these dungeons.";
			link.l1 = "Who brought it to you?";
			link.l1.go = "Jeffry_24";
		break;
		
		case "Jeffry_24":
            dialog.text = "Some junkie. All he needed was a hundred pesos for a drink.";
			link.l1 = "Did it happen on Tortuga?";
			link.l1.go = "Jeffry_25";
		break;
		
		case "Jeffry_25":
            dialog.text = "Nah. It was Barbados? Prince why are you worried so much?";
			link.l1 = "I don't like this. I don't believe in coincidences like this. Could it be Camilla's father who wrote this diary?";
			link.l1.go = "Jeffry_26";
		break;
		
		case "Jeffry_26":
            dialog.text = "Who's Camilla?";
			link.l1 = "The wench who sold me a map to this place for two hundred pesos!";
			link.l1.go = "Jeffry_27";
		break;
		
		case "Jeffry_27":
            dialog.text = "Heh... Prince you think too much. Let's go treasure hunting.";
			link.l1 = "No need. I have found them already... They are below in dungeon, behind iron bars. We'll have to break them. Listen Bold, there's on more thing! Pelly the Cutlass was here too!";
			link.l1.go = "Jeffry_28";
		break;
		
		case "Jeffry_28":
            dialog.text = "Cutlass? Wow! And where is he?";
			link.l1 = "Below... dead. I met him near the treasure. He's got mad, were screaming of greed. Then he and his companions attacked me.";
			link.l1.go = "Jeffry_29";
		break;
		
		case "Jeffry_29":
            dialog.text = "Hm... Pelly always had a bad luck with money. He must had gone mad seeing the load of gold.";
			link.l1 = "Maybe... Geffrey you don't get it! All three of us got here! We all got the same lead? You think it was by chance?";
			link.l1.go = "Jeffry_30";
		break;
		
		case "Jeffry_30":
            dialog.text = "Did you see the gold?";
			link.l1 = "I did with my very own eyes. Several giant chests filled with coins and ingots.";
			link.l1.go = "Jeffry_31";
		break;
		
		case "Jeffry_31":
            dialog.text = "Then why do you worry Prince? Lead the way, let's take a look on these bars of yours.";
			link.l1 = "Whatever... Let's go.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_RetributionWithJeffry");
		break;
		
		case "Jeffry_32":
            dialog.text = "What a spectacular! A pile of gold! I can see now why Cutlass had gone mad. We are very fortunate Prince! How much is here, how do you think?";
			link.l1 = "Plenty. We'll know for sure when we take care of these bars.";
			link.l1.go = "Jeffry_33";
		break;
		
		case "Jeffry_33":
            dialog.text = "Yes, the lattice is strong, we won't break it with bare hands. You are right, mate - we need to find some tools. Heh! Come back!!";
			link.l1 = "...";
			link.l1.go = "Jeffry_34";
		break;
		
		case "Jeffry_34":
            DialogExit();
			LAi_SetActorType(pchar);
			DoQuestCheckDelay("Mtraxx_RetributionJeffryMushketer", 0.1);
		break;
		
		case "Jeffry_35":
            dialog.text = RandSwear()+"What a fucking muff!";
			link.l1 = "You bastard!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_RetributionJeffryFight");
		break;
		
		// Билли Сипатый
		case "Billy":
			pchar.quest.Mtraxx_BillySeaTimeOver.over = "yes"; //снять таймер
			PlaySound("VOICE\Russian\citizen\Moryaki v Gorode-10.wav");
            dialog.text = "Shark swallow me if it has happened on the 'Fly Fish' for this year... we have a guest here! What is so wrong in you life, pal, that you decided to pay a visit to my old tub?";
			link.l1 = "Greetings! You are the one who is called Husky Billy?";
			link.l1.go = "Billy_1";
		break;
		
		case "Billy_1":
            dialog.text = "Can't you guess by my voice, captain? Long ago it could make British and Spanish merchants to shit themselves. What a glorious times!... Now old Billy is waiting for his life to end near the shores of his favorite island on his precious long boat...";
			link.l1 = "I have a business to you, Billy. I was told that you know everything about what's going on here around Jamaica. Is that so?";
			link.l1.go = "Billy_2";
		break;
		
		case "Billy_2":
            dialog.text = "If you are told so, then it must be so, huh? Don't pull a crab by its balls, talk to me.";
			link.l1 = "Very well. There is shipbuilder in Port Royal. He provides his customers with special services, and he needs ship silk for his production. Since trading this merchandise is illegal here, he has found himself an illegal seller. I want to know who and how is providing him with ship silk.";
			link.l1.go = "Billy_3";
		break;
		
		case "Billy_3":
            dialog.text = "Ho-ho, look at this! Working for colonel Doyley, son?";
			link.l1 = "Here we go again! No, I work with Marcus Tyrex. He wants some share in ship silk market and this ship builder is sacred shitless to deal with unfamiliar people...";
			link.l1.go = "Billy_4";
		break;
		
		case "Billy_4":
            dialog.text = "Oh, you are working for the Code Keeper! This is great... if you are not lying of course. I don't give a damn about shipbuilders, arrest one - another will come. I do give a damn about my old girl. The 'Flying Fish' is in a bad shape. Do you understand me?\nBring me another long boat and a roll of ship silk you are talking about - Billy will make a decent sail of it so he could screw patrols, ha-ha! In return Billy will tell everything about the shipbuilder and his source of silk. Billy knows!";
			link.l1 = "A new long boat? How about I give you enough money to buy it yourself? I will add extra.";
			link.l1.go = "Billy_5";
		break;
		
		case "Billy_5":
            dialog.text = "He-eh, captain, old Billy is not welcome in the city. They remember me too well in Port Royal and I don't fancy the idea to be hanged among my old friends on that rock. So, son, I am waiting for you to deliver me a fresh new long boat. I'll be waiting you for three days at Negril Cape. Don't forget about the silk!";
			link.l1 = "Very well, Billy. You'll have your long boat and a roll of ship silk. I'll be back soon.";
			link.l1.go = "Billy_6";
		break;
		
		case "Billy_6":
            dialog.text = "Billy will be waiting for you on a shore, captain. See you soon!";
			link.l1 = "...";
			link.l1.go = "Billy_7";
		break;
		
		case "Billy_7":
            DialogExit();
			AddQuestRecord("Roger_2", "8");
			npchar.dialog.currentnode = "Billy_8";
			pchar.questTemp.Mtraxx = "silk_7";
			SetFunctionTimerCondition("Mtraxx_BillyTimeOver", 0, 0, 3, false); // таймер
			pchar.quest.mtr_billy_coast.win_condition.l1 = "ExitFromLocation";
			pchar.quest.mtr_billy_coast.win_condition.l1.location = pchar.location;
			pchar.quest.mtr_billy_coast.function = "Mtraxx_BillyOnCoast";
			locations[FindLocation("shore35")].DisableEncounters = true; //энкаутеры закрыть
			npchar.DontDeskTalk = true;
		break;
		
		case "Billy_8":
            dialog.text = "What? Have you brought me a long boat already?";
			link.l1 = "You are a joker boy, huh, Billy?";
			link.l1.go = "exit";
		break;
		
		case "Billy_9":
			PlaySound("VOICE\Russian\citizen\Moryaki v Gorode-07.wav");
            dialog.text = "So, captain, what about my fresh new long boat?";
			if(Companion_CheckShipType(SHIP_TARTANE) && GetSquadronGoods(pchar, GOOD_SHIPSILK) > 0)
			{
				link.l1 = "It's done, Husky. She is delivered along with a ship silk in her cargo hold. You are free to sink your old tub.";
				link.l1.go = "Billy_11";
			}
			else
			{
				link.l1 = "I am still on it. Wait.";
				link.l1.go = "Billy_10";
			}
		break;
		
		case "Billy_10":
			DialogExit();
			npchar.dialog.currentnode = "Billy_9";
		break;
		
		case "Billy_11":
			pchar.quest.Mtraxx_BillyTimeOver.over = "yes"; //снять прерывание
            dialog.text = "Fuck me! This is the very best news for the last five years of Billy's life! Heh, a good reason to crack this bottle...";
			link.l1 = "I'll pass. What about the silk supplier?";
			link.l1.go = "Billy_12";
		break;
		
		case "Billy_12":
            dialog.text = "Pity, we could drink for my fresh new 'Flying Fish'! Whatever... Pay some attention here, son\nA brigantine under the English flag arrives to Portland Bay in the middle of each month, let's say between 10th and 15th. No rum for me until I am dead if she is really English! Her name is the 'Utrecht' and she arrives from South-West where Curacao lies. It's Dutch, captain, you can see that\nAlways the same group of people meet them on the shore, lead by a head master of that sly shipbuilder. He is a receiver of ship silk the Dutch unloading there. I am sure it is a ship silk, since only the Dutch pack it like that.";
			link.l1 = "Every month you said?";
			link.l1.go = "Billy_13";
		break;
		
		case "Billy_13":
            dialog.text = "Yes, son, not a single month missed for the last year. If you want a chat with this gloomy bearded company I suggest you wait for them at Portland Bay from 10th to 15th every month at nights. I swear on this by the fresh new silk sail of my long boat!";
			link.l1 = "Heh! Looks like my money were spent for reason. Godspeed, Billy, make sure to keep your old ass safe from patrols, otherwise you will make me really upset.";
			link.l1.go = "Billy_14";
		break;
		
		case "Billy_14":
            dialog.text = "Ha, old Billy is about to make some real fun around the shores of Jamaica! Godspeed, captain! Good hunting!";
			link.l1 = "Same to you, Billy!";
			link.l1.go = "Billy_15";
		break;
		
		case "Billy_15":
            DialogExit();
			npchar.lifeday = 0;
			pchar.questTemp.Mtraxx = "silk_8";
			chrDisableReloadToLocation = true;//закрыть локацию
			locations[FindLocation("shore35")].DisableEncounters = false; //энкаутеры открыть
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "sea", "none", "", "", "OpenTheDoors", 20.0);
			AddDialogExitQuestFunction("Mtraxx_BillyTakeShip");
			AddQuestRecord("Roger_2", "9");
			// ставим прерывание на 10-15 число
			int month = 0;
			pchar.questTemp.Mtraxx.month = 0;
			if (GetDataDay() > 12)
			{
				month = 1;
				pchar.questTemp.Mtraxx.month = 1;
			}
			int hour = 1+rand(2);
			int day = 13+rand(2);
			pchar.quest.mtr_silk_smuggler.win_condition.l1 = "Timer";
			pchar.quest.mtr_silk_smuggler.win_condition.l1.date.hour  = hour;
			pchar.quest.mtr_silk_smuggler.win_condition.l1.date.day   = day;
			pchar.quest.mtr_silk_smuggler.win_condition.l1.date.month = GetAddingDataMonth(0, month, 0);
			pchar.quest.mtr_silk_smuggler.win_condition.l1.date.year  = GetAddingDataYear(0, month, 0);
			pchar.quest.mtr_silk_smuggler.win_condition.l2 = "location";
			pchar.quest.mtr_silk_smuggler.win_condition.l2.location = "Jamaica";
			pchar.quest.mtr_silk_smuggler.function = "Mtraxx_SilkCreateSmuggler";
			// таймер
			pchar.quest.mtr_silk_smuggler_over.win_condition.l1 = "Timer";
			pchar.quest.mtr_silk_smuggler_over.win_condition.l1.date.hour  = hour+2;
			pchar.quest.mtr_silk_smuggler_over.win_condition.l1.date.day   = day;
			pchar.quest.mtr_silk_smuggler_over.win_condition.l1.date.month = GetAddingDataMonth(0, month, 0);
			pchar.quest.mtr_silk_smuggler_over.win_condition.l1.date.year  = GetAddingDataYear(0, month, 0);
			pchar.quest.mtr_silk_smuggler_over.function = "Mtraxx_SilkSmugglerOver";
		break;
		
		// мастеровой с верфи Порт-Рояля
		case "Mtr_acceptor_fight":
            LAi_group_Delete("EnemyFight");
			DialogExit();
			chrDisableReloadToLocation = true;
			LAi_LocationFightDisable(&Locations[FindLocation("shore36")], false);
			for (i=1; i<=4; i++)
			{
				sld = characterFromId("Mtr_acceptor_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "Mtraxx_SilkWrongTalk");
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "Mtr_acceptor":
            dialog.text = "Hey, sailor, you are a newcomer here on Jamaica, right?";
			link.l1 = "Hm. Correct. What's the matter?";
			link.l1.go = "Mtr_acceptor_1";
		break;
		
		case "Mtr_acceptor_1":
            dialog.text = "Sound of a firefight can be heard from the sea, can't see shit in this darkness even through a spyglass. Have you seen what's going on there?";
			link.l1 = "Aye, I have. Some brigantine engaged into combat with English patrol corvette. Brits hit them hard, the Dutch got rid of their cargo in an attempt to flee.";
			link.l1.go = "Mtr_acceptor_2";
		break;
		
		case "Mtr_acceptor_2":
            dialog.text = "Why are you so certain she was a Dutch? No Dutch in sane mind will even think of approaching this close to Port Royal...";
			link.l1 = "She had English colors yet the name... The 'Utrecht'. Not very British, right? They are Dutch, perhaps even smugglers, their arrival must had been expected. Patrol's reaction was faster than flash.";
			link.l1.go = "Mtr_acceptor_3";
		break;
		
		case "Mtr_acceptor_3":
            dialog.text = "Fuck! ... Hm...";
			link.l1 = "Looks like you are not exactly happy about this...";
			link.l1.go = "Mtr_acceptor_4_1";
			link.l2 = "Had you been waiting for this brigantine here?";
			link.l2.go = "Mtr_acceptor_7";
		break;
		
		case "Mtr_acceptor_4_1":
            dialog.text = "Why would I?";
			link.l1 = "Come on. I know who you are. You are a head master of Port Royal's shipyard and you are waiting for the very special cargo to be delivered by the brigantine.";
			link.l1.go = "Mtr_acceptor_wrong";
			link.l2 = "You have it written on your face. Right there.";
			link.l2.go = "Mtr_acceptor_4_2";
		break;
		
		case "Mtr_acceptor_wrong":
            dialog.text = "Argh! Boys, this is a patrol in disguise! Finish them off and get the hell out of here!";
			link.l1 = "Shit! You are wr...";
			link.l1.go = "Mtr_acceptor_fight";
		break;
		
		case "Mtr_acceptor_4_2":
            dialog.text = "Being rude, 'sea wolf'? Watch your mouth or...";
			link.l1 = "Come on. You obviously look upset. Were you actually waiting for this Dutch to arrive?";
			link.l1.go = "Mtr_acceptor_4_3";
			link.l2 = "Or what? Will you teach me a life lesson?";
			link.l2.go = "Mtr_acceptor_6";
		break;
		
		case "Mtr_acceptor_4_3":
            dialog.text = "And what if I was? Why do you care?";
			if (GetSquadronGoods(pchar, GOOD_SHIPSILK) >= 20)
			{
				link.l1 = "I don't, really. You are the waiting party here, not me. You have an eternity ahead.";
				link.l1.go = "Mtr_acceptor_4_4";
			}
			link.l2 = "Oh, I have every reason to care. I know what was inside the brigantine's cargo hold. Ship silk. You are here because of it, right?";
			link.l2.go = "Mtr_acceptor_wrong";
		break;
		
		case "Mtr_acceptor_4_4":
            dialog.text = "Hm... Eternity?";
			link.l1 = "It takes eternity to come back from the bottom of the sea. Your brigantine was sunk by a patrol corvette, pal. Just like that. Although, war brings both prizes and losses. I will make a good coin on that sunk Dutch.";
			link.l1.go = "Mtr_acceptor_4_5";
		break;
		
		case "Mtr_acceptor_4_5":
            dialog.text = "And exactly how, I wonder?";
			link.l1 = "I will sell what they had thrown overboard while trying to flee. Almost everything is lost but precious ship silk was floating like... cork. I have salvaged most of it, so I am heading to the city tomorrow to find a buyer. One never knows where one will gain and where one will lose.";
			link.l1.go = "Mtr_acceptor_4_6";
		break;
		
		case "Mtr_acceptor_4_6":
            dialog.text = "Wait!";
			link.l1 = "Caramba! What else?";
			link.l1.go = "Mtr_acceptor_4_7";
		break;
		
		case "Mtr_acceptor_4_7":
            dialog.text = "How much silk did you manage to gather?";
			link.l1 = "And why do you care? This is my silk! Or are you the governor's dog? You are de...";
			link.l1.go = "Mtr_acceptor_4_8";
		break;
		
		case "Mtr_acceptor_4_8":
            dialog.text = "Keep your sword sheath, sailor. I am not a dog and I am not a snitch. We work at the local shipyard... This silk was for us and as far as I understand, you have it now. I will buy all of it from you, we need this silk, pal.";
			link.l1 = "Really? Interesting... How much?";
			link.l1.go = "Mtr_acceptor_4_9";
		break;
		
		case "Mtr_acceptor_4_9":
			i = GetSquadronGoods(pchar, GOOD_SHIPSILK);
            dialog.text = "Two thousands and a half for a roll. That's a good price, you won't find better.";
			link.l1 = "Looks like I got lucky! I have "+FindRussianQtyString(i)+". Show me the money and I will order to deliver it ashore right now.";
			if (i > 80) link.l1.go = "Mtr_acceptor_4_11";
			else link.l1.go = "Mtr_acceptor_4_10";
		break;
		
		case "Mtr_acceptor_4_10":
            dialog.text = "Deal!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_CargoSilk");
			AddCharacterExpToSkill(pchar, "Fortune", 300);//везение
			AddCharacterExpToSkill(pchar, "Sneak", 300);//скрытность
		break;
		
		case "Mtr_acceptor_4_11":
            dialog.text = "Hm... Joachim was supposed to deliver only eighty rolls - no way you could salvage that much... what means you are either trying to play a dirty game here or... you are a snitch! Boys, kill him and get the hell out of here!";
			link.l1 = "Fuck!";
			link.l1.go = "Mtr_acceptor_fight";
		break;
		
		case "Mtr_acceptor_5":
            dialog.text = "";
			link.l1 = "A splendid deal, pal! Why so gloomy? Worried about the Dutch at the bottom of the sea? Screw them!";
			link.l1.go = "Mtr_acceptor_5_1";
		break;
		
		case "Mtr_acceptor_5_1":
            dialog.text = "Yeah, right... They were our regular supplier. Where are we supposed to get silk now? We are always in shortage of it and the whole trade is under direct control of colonel Doyley. Meh...";
			link.l1 = "Hm... Listen, friend, I suppose I can help you with that.";
			link.l1.go = "Mtr_acceptor_5_2";
		break;
		
		case "Mtr_acceptor_5_2":
            dialog.text = "Or really? And how? Will you be delivering us a batch of hundred rolls every months?";
			link.l1 = "Me - probably, not, but Marcus Tyrex will. Have you heard about him?";
			link.l1.go = "Mtr_acceptor_5_3";
		break;
		
		case "Mtr_acceptor_5_3":
            dialog.text = "K-ha! Are you a pirate?";
			link.l1 = "No, I just do business with them on special occasions. I know for sure that Marcus receives batches of ship silk on a constant basis and sells it to anyone who can afford it. And I am not talking about 2500 pesos for a roll here, I'd say if you can pay him 25 doubloons in gold for every roll, he will drown you in them, you can count on that.";
			link.l1.go = "Mtr_acceptor_5_4";
		break;
		
		case "Mtr_acceptor_5_4":
            dialog.text = "This is interesting... Marcus Tyrex you say? In doubloons only?..";
			link.l1 = "Come on, pal, does it really matter to you from whom you get your silk? Money is money, you can always exchange pesos for doubloons in a bank. So what, should I whisper a word or two about you in the ears of the baron? I am going to La Vega anyway.";
			link.l1.go = "Mtr_acceptor_5_5";
		break;
		
		case "Mtr_acceptor_5_5":
            dialog.text = "Very well. Let's try to make a deal. Our terms: a batch of hundred rolls every month between 10th and 15th. We will be waiting here... wait, no, this place is compromised now. Cape Negril then, it's safer there. The password - 'A merchant of Lyons'.";
			link.l1 = "Deal, friend. Hell of voyage it was! Tyrex will pay me a doubloon or two for such a buyer! Ha-ha! Very well, I should go. Wait for Tyrex's vessel next month. Best of luck to you and to your family!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_CargoSilkWin");
		break;
		
		case "Mtr_acceptor_6":
            dialog.text = "You won't need any life lessons after we teach you of being polite.";
			link.l1 = "Acting tough, carpenter? Fine, keep waiting for that brigantine of your, though it will take a while.";
			link.l1.go = "Mtr_acceptor_6_1";
			if (GetSquadronGoods(pchar, GOOD_SHIPSILK) >= 20)
			{
				link.l2 = "Hey, teacher, I have a few lessons for you too!";
				link.l2.go = "Mtr_acceptor_6_2";
			}
		break;
		
		case "Mtr_acceptor_6_1":
            dialog.text = "Carpenter? Bloody hell, how do you know? K-ha! Fuck, boys, this is a patrol in disguise! Kill him and get the hell out of here!";
			link.l1 = "Shit!";
			link.l1.go = "Mtr_acceptor_fight";
		break;
		
		case "Mtr_acceptor_6_2":
            dialog.text = "Leave us be, you fish scale, we ain't got any time. Get lost!";
			link.l1 = "Are you busy waiting for the Dutch vessel? Good luck with that. You have an eternity ahead.";
			link.l1.go = "Mtr_acceptor_4_4";
		break;
		
		case "Mtr_acceptor_7":
            dialog.text = "Why would you think like that? We are just curious to see the battle...";
			link.l1 = "I see. But still if you are waiting for her, you all can go home. She ain't coming thanks to a patrol corvette. I saw through a spyglass the end of a fight.";
			link.l1.go = "Mtr_acceptor_7_1";
		break;
		
		case "Mtr_acceptor_7_1":
            dialog.text = "Again? We are not waiting for anything or anyone and...";
			link.l1 = "Look, I don't give a fuck really. I don't belong to the city patrol and don't care about your doings, I am no angel myself. If you are smuggling - it's your business. All I wanted is to warn you. Best of luck to you, pal.";
			link.l1.go = "Mtr_acceptor_7_2";
		break;
		
		case "Mtr_acceptor_7_2":
            dialog.text = "Wait... Are you sure the 'Utrecht' is sunk?";
			link.l1 = "Absolutely. She tried to flee, threw away everything she had in her cargo holds, they didn't even spare precious ship silk but such drastic measures couldn't help against a corvette's advantage in speed.";
			link.l1.go = "Mtr_acceptor_7_3";
		break;
		
		case "Mtr_acceptor_7_3":
            dialog.text = "What a pity... and what are we supposed to do without the silk? Damn it!";
			link.l1 = "Are you in a need of ship silk?";
			link.l1.go = "Mtr_acceptor_7_4";
		break;
		
		case "Mtr_acceptor_7_4":
            dialog.text = "Why are you asking, are you selling it?";
			link.l1 = "I am not, but I know a man who is. He is looking for a generous and regular buyer. Think you can fit in?";
			link.l1.go = "Mtr_acceptor_7_5";
		break;
		
		case "Mtr_acceptor_7_5":
            dialog.text = "What man?";
			link.l1 = "Marcus Tyrex, the baron of La Vega. He receives batches of ship silk on a constant basis, so he always has some to sell. I suppose he will consider selling it to you too if your price is hefty enough.";
			link.l1.go = "Mtr_acceptor_7_6";
		break;
		
		case "Mtr_acceptor_7_6":
            dialog.text = "So you are a pirate?";
			link.l1 = "Why do you care? I can arrange a deal between you and Tyrex if you got balls for that. If you don't - good bye then.";
			link.l1.go = "Mtr_acceptor_7_7";
		break;
		
		case "Mtr_acceptor_7_7":
            dialog.text = "Fine-fine, don't get angry. Sure, I do. I want to struck a deal with Tyrex. But what in it for you?";
			link.l1 = "If you offer a good price for the cargo, I will get from Marcus a decent sum for my assistance. So what will it be?";
			link.l1.go = "Mtr_acceptor_7_8";
		break;
		
		case "Mtr_acceptor_7_8":
            dialog.text = "Twenty five doubloons for a roll. That is the best price you can get, trust me on that.";
			link.l1 = "Twenty five golden coins? Hm. Not bad. I believe Tyrex owes me a great reward for such a buyer. Deal, I'll let him know. If you lied to me about the price then it's your ass on the line.";
			link.l1.go = "Mtr_acceptor_7_9";
		break;
		
		case "Mtr_acceptor_7_9":
            dialog.text = "Don't worry, we are an honest folks. Our terms: a batch of hundred rolls every month between 10th and 15th. We will be waiting here... wait, no, this place is compromised. Cape Negril then, it's safer there. The password - 'A merchant of Lyons'.";
			link.l1 = "Got it. Wait for the first batch next month.";
			link.l1.go = "Mtr_acceptor_7_10";
		break;
		
		case "Mtr_acceptor_7_10":
            dialog.text = "Let Tyrex know that he may bring more cargo this time, we are left without silk for this month.";
			link.l1 = "I will. Godspeed, friend.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_CargoSilkWin");
			AddCharacterExpToSkill(pchar, "Sneak", 300);//скрытность
		break;
		
		// Тесак Пелли
		case "Pelly":
            dialog.text = "Ahoy! What brought you aboard of my vessel, friend?";
			link.l1 = "Hey, Cutlass. Marcus Tyrex sent me. A march to Maracaibo awaits us.";
			link.l1.go = "Pelly_1";
		break;
		
		case "Pelly_1":
            dialog.text = "A-ah, at last. So you must be my boss for this voyage. Good. What's my new admiral's name?";
			link.l1 = "Captain "+GetFullName(pchar)+".";
			link.l1.go = "Pelly_2";
		break;
		
		case "Pelly_2":
            dialog.text = "Orders, admiral "+GetFullName(pchar)+"?";
			link.l1 = "We will sail to Maracaibo Lake apart. You should get there at night and secretly land at Guajira Bay. Wait for me there and in the meanwhile set up a small camp. I, myself, will land in the Spanish port.";
			link.l1.go = "Pelly_3";
		break;
		
		case "Pelly_3":
            dialog.text = "Aye-aye, sir!";
			link.l1 = "How long will it take for you to get there?";
			link.l1.go = "Pelly_4";
		break;
		
		case "Pelly_4":
            dialog.text = "Mh-hm... A week, admiral. A day less, a day more, depends on the wind.";
			link.l1 = "Good. Let's not waste time then. See you at Guajira Bay.";
			link.l1.go = "Pelly_5";
		break;
		
		case "Pelly_5":
            dialog.text = "Aye-aye, admiral!";
			link.l1 = "...";
			link.l1.go = "Pelly_6";
		break;
		
		case "Pelly_6":
            DialogExit();
			AddQuestRecord("Roger_3", "3");
			LAi_CharacterDisableDialog(npchar);
			npchar.DontDeskTalk = true;
			Mtraxx_PlantContinue();
		break;
		
		case "Pelly_7":
            dialog.text = "Orders, admiral?";
			link.l1 = "Nothing at the moment. I am busy with our operation.";
			link.l1.go = "Pelly_wait";
			if (pchar.questTemp.Mtraxx == "plant_3")
			{
				link.l1 = "Prepare a capacious chest on the shore. We will be collecting weapons for our prisoners in it.";
				link.l1.go = "Pelly_8";
			}
			if (pchar.questTemp.Mtraxx == "plant_8" && pchar.location.from_sea == "Shore37")
			{
				link.l1 = "Leave the camp and gather a storm squad. It's time to march, we will begin at three o'clock at night.";
				link.l1.go = "Pelly_11";
			}
		break;
		
		case "Pelly_wait":
             DialogExit();
			 npchar.dialog.currentnode = "Pelly_7";
		break;
		
		case "Pelly_8":
            dialog.text = "Ho! A rebellion on the plantation, am I right, admiral? Flames! We are to get some gold out of this!..";
			link.l1 = "I need a chest on the shore, Cutlass.";
			link.l1.go = "Pelly_9";
		break;
		
		case "Pelly_9":
            dialog.text = "At once, admiral!";
			link.l1 = "...";
			link.l1.go = "Pelly_10";
		break;
		
		case "Pelly_10":
            DialogExit();
			npchar.dialog.currentnode = "Pelly_7";
			pchar.questTemp.Mtraxx = "plant_4";
			pchar.questTemp.Mtraxx.Chest = "true";
			// подгружаем сундук в локу и меняем локаторы
			int n = Findlocation("Shore37");
			Locations[n].models.always.locators = "shore03_q_locators";
			locations[n].models.always.chest = "chest_quest";
			Locations[n].models.always.chest.locator.group = "box";
			Locations[n].models.always.chest.locator.name = "private1";
			Locations[n].models.always.chest.tech = "DLightModel";
			DoQuestReloadToLocation("Shore37", "goto", "goto5", "Mtraxx_PlantChestReady");
		break;
		
		case "Pelly_11":
            dialog.text = "At once, admiral!..";
			link.l1 = "";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_PlantPrepareMarch");
		break;
		
		case "Pelly_12":
            dialog.text = "Men are ready and prepared, admiral!";
			link.l1 = "Onward!";
			link.l1.go = "Pelly_13";
		break;
		
		case "Pelly_13":
            DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			chrDisableReloadToLocation = false;
		break;
		
		case "Pelly_14":
            dialog.text = "Admiral looks like the friend of Tyrex we were supposed to save is... kinda dead.";
			link.l1 = "Yeah but nothing could be done there. You saw the guards, we were lucky to stay alive.";
			link.l1.go = "Pelly_15";
		break;
		
		case "Pelly_15":
            dialog.text = "Admiral, Marcus will be mad at you. Don't go to him right now. I am leaving. You should too.";
			link.l1 = "Yeah...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_PlantFailFinal");
		break;
		
		case "Pelly_16":
            dialog.text = "Bad news admiral. There is a Spanish squadron coming at us from the East. We have no time to flee.";
			link.l1 = "How many of them?";
			link.l1.go = "Pelly_17";
		break;
		
		case "Pelly_17":
            dialog.text = "Three ships. Lots of guns. We are fucked."; // лесникПОСЛЕДНЕЕ
			link.l1 = "We'll see.";// Жан, ты отправляйся на борт к Тесаку. Тесак, поднимешь испанский флаг и на всех парусах прочь отсюда - глядишь, за торговца сойдёшь. А я пойду прямо на испанцев - отвлеку их от вас. Увидимся в Ла Веге у Тиракса.";
			link.l1.go = "Pelly_181";
		break;
		case "Pelly_181":
	    	DialogExit();
		   sld = characterFromId("Mrt_Rocur");
		   sld.Dialog.currentnode = "Pelly_182";
		LAi_SetActorType(sld);
		LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		case "Pelly_182":
		   dialog.text = ""; 
		   link.l1 = "Jean you go to Cutlass's ship.";
		   link.l1.go = "Pelly_183"; 
		break;
		case "Pelly_183":
		     DialogExit();
			sld = characterFromId("Pelly");
			sld.Dialog.currentnode = "Pelly_18";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		case "Pelly_18":
            dialog.text = "";//"Но...";
			link.l1 = "Cutlass you should rise the Spanish flag and get the hell out of here. I will distract them from you. See you all in La Vega.";//"Отставить! Тесак, за Жана Пикара отвечаешь головой перед Тираксом. Все на борт!";
			link.l1.go = "Pelly_19";
		break;
		
		case "Pelly_19":
            dialog.text = "But...";
			link.l1 = "No buts! Cutlass it's your ass on the line if Picard does not get to Tyrex's place. All aboard!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_PlantSeaEscape");
		break;
		
		case "Pelly_20":
            dialog.text = "Orders admiral?";
			link.l1 = "Get ready to fight. Engage them on my command!";
			link.l1.go = "Pelly_21";
		break;
		
		case "Pelly_21":
            dialog.text = "Aye, aye admiral - on your command!";
			link.l1 = "...";
			link.l1.go = "Pelly_22";
		break;
		
		case "Pelly_22":
            DialogExit();
			LAi_SetActorType(npchar);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			chrDisableReloadToLocation = false;
		break;
		
		case "Pelly_23":
            dialog.text = "Ho! Hello Prince. What brought you to Tortuga?";
			link.l1 = "Marcus's task again. Listen Paul, why the bastard living in this house is not letting me in?";
			link.l1.go = "Pelly_24";
		break;
		
		case "Pelly_24":
            dialog.text = "Gaspard Goldenteeth? He works only with trusted fellows. Others would need a recommendations to work with him. Wanna sell some shiny trinkets? I could vouch for you if you want...";
			link.l1 = "So he is a usurer? What is his interest?";
			link.l1.go = "Pelly_25";
		break;
		
		case "Pelly_25":
            dialog.text = "Brother you are missing something. Gaspard is no usurer, you should go to "+GetFullName(characterFromId("Tortuga_usurer"))+" if you need one. Goldenteeth is buying precious stones and jewelry of all kinds. By the way, he pays well and never asks dumb questions. Every pirate captain is a client of his.";
			link.l1 = "I see... I was told that some of them even trust their money to him...";
			link.l1.go = "Pelly_26";
		break;
		
		case "Pelly_26":
            dialog.text = "Ha-ha! It was a liar who told you that, go and spit in his shameless eyes. Gaspard works only with jewelry, he always did. Why would he needed problems with other people's money?";
			link.l1 = "I see. Thank you Cutlass, see you in the sea!";
			link.l1.go = "Pelly_27";
		break;
		
		case "Pelly_27":
            dialog.text = "See you, Prince.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_WolfreekReadLogbookThird");
		break;
		
		case "Pelly_28":
            dialog.text = "I have got three birds for you Prince. Found them hiding in wardrobes and beneath a bed. Pretty things, hey? Ha-ha!";
			link.l1 = "I say they indeed are. And they are well-groomed. Don Stubborn must care deeply of them.";
			link.l1.go = "Pelly_29";
		break;
		
		case "Pelly_29":
            DialogExit();
			sld = CharacterFromID("Mtr_CartahenaMayorClone");
			sld.dialog.currentnode = "CartahenaMayor_8";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "Pelly_30":
            dialog.text = "Alle hagel! What the fuck are you doing here Prince?";
			link.l1 = "Cutlass? I am surprised! Why are you here?";
			link.l1.go = "Pelly_31";
		break;
		
		case "Pelly_31":
            dialog.text = "No, why are you here! You are always around! Tyrex must had sent you for this treasure, right? Caramba, I am late, again...";
			link.l1 = "Tyrex? No... I bought a map from one wench. She probably had sold a copy to you, huh? On Tortuga? What a cunning bitch. She didn't lie though - look at this pile of gold!";
			link.l1.go = "Pelly_32";
		break;
		
		case "Pelly_32":
            dialog.text = "Hell yes it is a pile of gold! But it not yours or Tyrex's! I have found it first! It's mine! It doesn't matter how I have learnt of it! Not your business!";
			link.l1 = "Calm down Cutlass, why so mad? Look at this pile - must be a million there. Even more maybe! Enough for both of us!";
			link.l1.go = "Pelly_33";
		break;
		
		case "Pelly_33":
            dialog.text = "You always get a better slice of a pie, Prince! But not this time! The treasure is mine! I have found it first!";
			link.l1 = "Damn it, Paul, what's wrong with you? Can't we struck a deal here? Even a half of this gold is a fortune. You've never had such a sum in your hands before.";
			link.l1.go = "Pelly_34";
		break;
		
		case "Pelly_34":
            dialog.text = "Want to fuck me up, Prince? No way! I am not gonna give you a single coin, not a single guinea! You are late!\nA-ah, I see what you are up to! Now way you get the gold!!!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_RetributionPellyFight");
		break;
		
		// Жан Пикар
		case "rocur":
            dialog.text = "What do you want from me?";
			link.l1 = "My friend, I am looking for Jean Picard. Any chance you bear the same name?";
			link.l1.go = "rocur_1";
		break;
		
		case "rocur_1":
            dialog.text = "There is a chance. I don't recall your face though.";
			link.l1 = "Don't get too rough, Jean. I was sent here by Marcus Tyrex. My orders are to get you out of here.";
			link.l1.go = "rocur_2";
		break;
		
		case "rocur_2":
            dialog.text = "Marcus? Tsh-sh... Hush. I am sorry, friend, I didn't know that. But we shouldn't talk here, fucking guards are everywhere and they are always listening... I see you are a welcome guest among the Spanish, find me in one of the barracks at night and we'll talk. I'll be waiting for you, brother.";
			link.l1 = "...";
			link.l1.go = "rocur_3";
		break;
		
		case "rocur_3":
            DialogExit();
			AddQuestRecord("Roger_3", "6");
			LAi_CharacterDisableDialog(npchar);
			Mtraxx_PlantMakeMaxRocurClone();
		break;
		
		case "rocur_4":
            dialog.text = "Well, it's safe here... What's your name, brother?";
			link.l1 = "Captain "+GetFullName(pchar)+". Now tell me, how did you end up in this shit. Tyrex wants to know everything.";
			link.l1.go = "rocur_5";
		break;
		
		case "rocur_5":
            dialog.text = "I was approached by a stranger in a tavern of Willemstad... He offered a companionship to plunder some Dutch merchants. I had a brigantine, he had a polacre. Chased down a caravan not far from Caracas and plundered it. It was night, we were splitting the plunder when a Spanish heavy galleon appeared from the darkness\nMy companion fled and so did I. No way my damaged brigantine could escape from a heavy galleon. They had boarded us and sold all survivors to this place like a cattle.";
			link.l1 = "I see. You think it was an accident? I am talking about the galleon.";
			link.l1.go = "rocur_6";
		break;
		
		case "rocur_6":
            dialog.text = "Hell if I knew. They might have heard a gunfight, it was not far from the Main.";
			link.l1 = "Hm. It's possible. Did you meet your former companion before? Who is he?";
			link.l1.go = "rocur_7";
		break;
		
		case "rocur_7":
            dialog.text = "Never met him before. Said his name was Ignacio Marco, a privateer of England. He made an impression of a serious man, that's why I agreed to participate in this endeavor. He is a seasoned seaman, that's for sure, he has a dashing crew behind him and his polacre is a beauty, not every day you can see a ship like that one.";
			link.l1 = "Ignacio Marco? An English privateer? A Spanish?";
			link.l1.go = "rocur_8";
		break;
		
		case "rocur_8":
            dialog.text = "He is a Portuguese, not a Spanish. What's wrong with a British letter of marque? We have a plenty of the Spanish among our kind, you know that.";
			link.l1 = "I see. Fine, let's talk about your escape from here. Any ideas?";
			link.l1.go = "rocur_9";
		break;
		
		case "rocur_9":
            dialog.text = "What are your numbers?";
			link.l1 = "My ship, a barquentine and men of Pelly the Cutlass. My vessel is stationed in port of Maracaibo. Cutlass has landed at Guajira Bay and set up a camp there.";
			link.l1.go = "rocur_10";
		break;
		
		case "rocur_10":
            dialog.text = "Hm...";
			link.l1 = "What, did you expect Tyrex to send a ship of the line here?";
			link.l1.go = "rocur_11";
		break;
		
		case "rocur_11":
            dialog.text = "I didn't expect anything. Actually, I am surprised Marcus didn't forget about me.";
			link.l1 = "He didn't, obviously. So, any ideas?";
			link.l1.go = "rocur_12";
		break;
		
		case "rocur_12":
            dialog.text = "No chance to escape from here - this plantation is too well guarded and there are wild jungles around. No point to storm it either, you don't have enough men, plus there is a fort nearby.";
			link.l1 = "Perhaps, you and your boys can help us from inside? Hit them hard from behind.";
			link.l1.go = "rocur_13";
		break;
		
		case "rocur_13":
            dialog.text = "With what? Bare hands and rusty machetes?";
			link.l1 = "And what if you had weapons?";
			link.l1.go = "rocur_14";
		break;
		
		case "rocur_14":
            dialog.text = "In that case we would have given them hell. Of course! There is a problem though, they check everything you bring inside, no way you can smuggle weapons. So I suggest forgeting about this.";
			link.l1 = "And still, that is our best option at the moment. I will think of how to deliver you and your men weapons... Tell me, how many of you are capable of fighting?";
			link.l1.go = "rocur_15";
		break;
		
		case "rocur_15":
            dialog.text = "Thirty heads, I'd say.";
			link.l1 = "Thirty sabers then... Handguns would make a difference too, I believe.";
			link.l1.go = "rocur_16";
		break;
		
		case "rocur_16":
            dialog.text = "Captain, are you serious?";
			link.l1 = "I am. I have arrived here on purpose, joking around is not a part of it. What else could you use?";
			link.l1.go = "rocur_17";
		break;
		
		case "rocur_17":
            dialog.text = "Very well... Let's give it a try at least. We need simple cold steel - my boys are not trained to work with fancy rapiers and such. Same can be said about handguns, the cheapest will do just fine. If you get us a musket or two that would help us a lot too, I have a couple of boys who are good with muskets. Bullets, gunpowder. Healing potions are the most welcome.";
			link.l1 = "Got it. Blades and axes can be taken from the ship's arsenal. The rest is more tricky to get. I will let you know when I have it all.";
			link.l1.go = "rocur_18";
		break;
		
		case "rocur_18":
            dialog.text = "Please hurry up, brother. We don't have a half a year here, this fucking cattle work is killing us one by one. If you'll need me - come see me at nights.";
			link.l1 = "Got it, pal. Hold on, I'll try not to keep you waiting. Be careful.";
			link.l1.go = "rocur_19";
		break;
		
		case "rocur_19":
            DialogExit();
			AddQuestRecord("Roger_3", "7");
			npchar.dialog.currentnode = "rocur_wait";
			pchar.questTemp.Mtraxx = "plant_3";
			pchar.quest.Mtraxx_PlantPrepareTimeOver.over = "yes"; //снять таймер
			SetFunctionTimerCondition("Mtraxx_SeekWeaponOver", 0, 0, 30, false); // таймер
		break;
		
		case "rocur_wait":
            dialog.text = "Any news, pal? Have you gathered weapons?";
			if (pchar.questTemp.Mtraxx == "plant_5")
			{
				link.l1 = "Yes. A chest with munitions is at Guajira Bay. All that left is to find a way to sneak it inside the plantation.";
				link.l1.go = "rocur_20";
			}
			else
			{
				link.l1 = "I am on it. Wait.";
				link.l1.go = "rocur_wait_1";
			}
		break;
		
		case "rocur_wait_1":
            DialogExit();
			npchar.dialog.currentnode = "rocur_wait";
		break;
		
		case "rocur_20":
            dialog.text = "Very well, captain. I have been thinking on how to perform that already.";
			link.l1 = "Glad to hear it. What's on your mind?";
			link.l1.go = "rocur_21";
		break;
		
		case "rocur_21":
            dialog.text = "They produce sugar and grow cocoa beans on this plantation. Sometimes its head sells the goods himself, it's more profitable that way. Make him an offer. Pay him not with money but with goods. Something you can put into boxes like copra, vanilla or coffee. Put some effort in bargaining but don't overdo it\nStash weapons in one or two boxes and put marks on them. Arrange an exchange at evening so they will have to leave the boxes outside for a night\nAt night we will find your marked boxes, arms ourselves and make a hell to the Spanish. With your help of course.";
			link.l1 = "Nice thinking here, brother! Very good, I like this plan. Let's stick to it.";
			link.l1.go = "rocur_22";
		break;
		
		case "rocur_22":
            dialog.text = "One last thing - offer only one type of goods to exchange. More types of goods - more boxes checked by the guards.";
			link.l1 = "I agree. I'll pick only one type then. Coffee, vanil and copra, you said?";
			link.l1.go = "rocur_23";
		break;
		
		case "rocur_23":
            dialog.text = "Yes. This will sound like a good deal to the head of plantation.";
			link.l1 = "Got it. I'll let you know when the deal is stuck.";
			link.l1.go = "rocur_24";
		break;
		
		case "rocur_24":
            DialogExit();
			AddQuestRecord("Roger_3", "9");
			npchar.dialog.currentnode = "rocur_wait_2";
			pchar.questTemp.Mtraxx = "plant_6";
		break;
		
		case "rocur_wait_2":
            dialog.text = "Go, my friend, time is golden...";
			link.l1 = "";
			link.l1.go = "rocur_wait_3";
		break;
		
		case "rocur_wait_3":
            DialogExit();
			npchar.dialog.currentnode = "rocur_wait_2";
		break;
		
		case "rocur_25":
            dialog.text = "";
			link.l1 = "(quietly) The deal is struck. The boxes will be delivered to the plantation tomorrow evening. The boxes you need are marked with a 'W' letter. Others have the rest of the alphabet on them. Get you men ready. We shall attack before dawn at three o'clock.";
			link.l1.go = "rocur_25x";
		break;
		
		case "rocur_25x":
            dialog.text = "We will start with your signal...";
			link.l1 = "";
			link.l1.go = "rocur_26";
		break;
		
		case "rocur_26":
            DialogExit();
			LAi_CharacterDisableDialog(npchar);
			DoQuestFunctionDelay("Mtraxx_PlantWaitDay", 3.0);
		break;
		
		case "rocur_27":
            dialog.text = "Finally! I am about to see the sea again! I have already forgotten its look and its smell. Nicely done captain! I owe you.";
			link.l1 = "We'll settle it... Now let's embark and get out of here!";
			link.l1.go = "rocur_28";
		break;
		
		case "rocur_28":
            DialogExit();
			sld = characterFromId("Pelly");
			sld.Dialog.currentnode = "Pelly_16";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "rocur_29":
            dialog.text = "Greetings "+pchar.name+". Glad to see you again, also glad to have you as my companion in this adventure. This job is gonna be tough but I am sure we'll make it through.";
			link.l1 = "Hey Jean. I am all ears, tell me about this adventure.";
			link.l1.go = "rocur_30";
		break;
		
		case "rocur_30":
            dialog.text = "I've already told Marcus, now I am telling you. When I was a slave on the plantation in Maracaibo I learnt something from the Spanish. They are quite talkative when they are drunk... Listen, South-East from Maracaibo lake there is a small village. It's hidden between two mountains deep in the jungles. Hell of name it has: Santiago-de-Los-Caballeros-de-Merida. Let's call it Merida\nDoesn't sound very interesting yet, huh? The mountains surrounding the village turned out to be rich with gems. Emeralds, opals and legendary fire opals\nAs far as I understand, Merida's settlers didn't tell the general-governor about these gems. However soon he will learn about it, this is why we should visit Merida before the arrival of Spanish colonial officers.";
			link.l1 = "Do you wanna to plunder the settlement?";
			link.l1.go = "rocur_31";
		break;
		
		case "rocur_31":
            dialog.text = "Exactly. It is lost among jungles and mountains with a small garrison - an easy pray for a corsair unit. Besides, they are long away from the sea, they don't expect anybody to attack them except savages with spears and bows.";
			link.l1 = "How much are you sure that the settlement does have precious stones?";
			link.l1.go = "rocur_32";
		break;
		
		case "rocur_32":
            dialog.text = "If our adventures turns to be a false trace I myself will serve on your vessel as an officer or as a sailor, I will be cleaning decks and fight in countless boardings until my debt to you and Marcus is wiped away.";
			link.l1 = "I see... Do you know how to get to Merida?";
			link.l1.go = "rocur_33";
		break;
		
		case "rocur_33":
            dialog.text = "Of course I don't know the exact path through the jungles but we will hire a guide from Indian folk. We should land South of Maracaibo lake, find an Indian village and find those who know how to get there.";
			link.l1 = "...";
			link.l1.go = "rocur_34";
		break;
		
		case "rocur_34":
            DialogExit();
			sld = characterFromId("Terrax");
			sld.Dialog.currentnode = "mtraxx_38";
			LAi_SetActorType(sld);
			LAi_ActorSetSitMode(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;
		
		case "rocur_35":
            dialog.text = "Captain I am deeply sorry but why the fuck we are not in Merida yet? Huh? You had spit on our common cause! Leprechaun and I are leaving without you. I will explain everything to Tyrex and you should go. Here, take 50 000 pesos for your help in Maracaibo, I borrowed them from friends. Farewell, it's a shame, I thought better of you.";
			link.l1 = "Hm...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_MeridaTimeOverFail");
		break;
		
		case "rocur_36":
            dialog.text = "Here we are. Jungles ahead. First, we should find an Indian village and ask around for a guide.";
			link.l1 = "Let's do this. Luke, do you have anything to say... or perhaps an advice?";
			link.l1.go = "rocur_37";
		break;
		
		case "rocur_37":
            DialogExit();
			sld = characterFromId("Lepricon");
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;
		
		case "rocur_38":
            dialog.text = "Merida's garrison is finished. I don't expect any serious resistance inside the village. Now go!";
			link.l1 = "Charge!!!";
			link.l1.go = "rocur_39";
		break;
		
		case "rocur_39":
            DialogExit();
			chrDisableReloadToLocation = false;
			LocatorReloadEnterDisable("Merida_ExitTown", "reload1_back", true);
			pchar.quest.mtraxx_merida_town.win_condition.l1 = "location";
			pchar.quest.mtraxx_merida_town.win_condition.l1.location = "Merida_Town";
			pchar.quest.mtraxx_merida_town.function = "Mtraxx_MeridaTown";
			Mtraxx_MeridaCheckOurWarriors();
			AddQuestRecord("Roger_5", "16");
		break;
		
		case "rocur_40":
            dialog.text = "It's done! No heroes left. Now we should talk to a governor of this 'city'. I hope he is a persuadable type.";
			link.l1 = "Let's go!.. Leprechaun! Follow me!";
			link.l1.go = "rocur_41";
		break;
		
		case "rocur_41":
            DialogExit();
			chrDisableReloadToLocation = false;
			LocatorReloadEnterDisable("Merida_Town", "gate_back", true);
			pchar.quest.mtraxx_merida_townhall.win_condition.l1 = "location";
			pchar.quest.mtraxx_merida_townhall.win_condition.l1.location = "Merida_townhall";
			pchar.quest.mtraxx_merida_townhall.function = "Mtraxx_MeridaTownhall";
			sld = characterFromId("Mrt_Rocur");
			LAi_SetActorType(sld);
			LAi_ActorFollowEverywhere(sld, "", -1);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			sld = characterFromId("Lepricon");
			LAi_SetActorType(sld);
			LAi_ActorFollowEverywhere(sld, "", -1);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			AddQuestRecord("Roger_5", "17");
		break;
		
		case "rocur_42":
            dialog.text = ""+pchar.name+", everything's nice. A load of opals and emeralds. Just as I expected.";
			link.l1 = "Grab it all and let's leave. Time to get back.";
			link.l1.go = "rocur_43";
		break;
		
		case "rocur_43":
            DialogExit();
			chrDisableReloadToLocation = false;
			pchar.questTemp.Mtraxx = "merida_success";
			AddQuestRecord("Roger_5", "12");
			pchar.quest.mtraxx_merida_exit.win_condition.l1 = "location";
			pchar.quest.mtraxx_merida_exit.win_condition.l1.location = "Merida_Town";
			pchar.quest.mtraxx_merida_exit.function = "Mtraxx_MeridaExit";
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
		break;
		
		case "rocur_44":
            dialog.text = "Nicely done, "+pchar.name+"! Time to split shares. I already have the numbers. There were almost 2000 gems in the chest: 1050 emeralds, 732 opals and 189 fire opals. Your cut is the third: 350 emeralds, 244 opals and 63 fire opals. Here, take them.";
			link.l1 = "Nice!";
			link.l1.go = "rocur_45";
		break;
		
		case "rocur_45":
			PlaySound("interface\important_item.wav");
			TakeNItems(pchar, "jewelry4", 350);
			TakeNItems(pchar, "jewelry16", 244);
			TakeNItems(pchar, "jewelry14", 63);
            dialog.text = "Now let's talk my debt to you for my rescue. I understand you had serious expenses. What compensation will you consider to be fair? I am paying from my share of gems.";
			link.l1 = "A third of your share will suffice. You need money too - to buy and supply a ship, to pay your crew.";
			link.l1.go = "rocur_46";
		break;
		
		case "rocur_46":
			PlaySound("interface\important_item.wav");
			TakeNItems(pchar, "jewelry4", 116);
			TakeNItems(pchar, "jewelry16", 81);
			TakeNItems(pchar, "jewelry14", 21);
            dialog.text = "Thank you friend! I thought you would ask no less than a half. I do need money now. Here, take the gems.";
			link.l1 = "What a raid Jean! Let's head to Hispaniola, to Tyrex.";
			link.l1.go = "rocur_47";
		break;
		
		case "rocur_47":
            DialogExit();
			chrDisableReloadToLocation = false;
			pchar.questTemp.Mtraxx = "merida_gohome";
			AddQuestRecord("Roger_5", "18");
			sld = characterFromId("Mrt_Rocur");
			LAi_SetWarriorType(sld);
			LAi_CharacterDisableDialog(sld); // релиз-правка
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			AddPassenger(pchar, sld, false);
			SetCharacterRemovable(sld, false);
			sld = characterFromId("Lepricon");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			AddPassenger(pchar, sld, false);
			SetCharacterRemovable(sld, false);
			sld = characterFromId("Terrax");
			sld.dialog.currentnode = "mtraxx_40";
			pchar.quest.mtraxx_merida_lavega.win_condition.l1 = "location";
			pchar.quest.mtraxx_merida_lavega.win_condition.l1.location = "Hispaniola1";
			pchar.quest.mtraxx_merida_lavega.function = "Mtraxx_IgnasioKitty";
			// таймер на доплыть домой 40 дней
			SetFunctionTimerCondition("Mtraxx_MeridaReturnLate", 0, 0, 40, false);
			DeleteAttribute(pchar, "GenQuest.HunterLongPause");
		break;
		
		case "rocur_48":
            dialog.text = "Oh, what a meeting! Pleasure to see you, "+pchar.name+". How are you doing?";
			link.l1 = "Pretty good. Found Red Wolf's treasures just recently. Now heading to Martinique to meet one common friend of ours. You want to see Tyrex?";
			link.l1.go = "rocur_49";
		break;
		
		case "rocur_49":
            dialog.text = "Yeah. Want to talk with him regarding Pasquale Lavoisier. Marcus sent me to that half bandit-half merchant. I did what he asked and he paid with some shit claiming it to be a bloody good payment. I would kill the fucker right where he was standing but Marcus asked treat him with respect... then it is him to deal with this trouble.";
			link.l1 = "I'm sorry but Marcus will do nothing. Four-eyes is in business with him.";
			link.l1.go = "rocur_50";
		break;
		
		case "rocur_50":
            dialog.text = "What the fuck?";
			link.l1 = "Yeah, but I didn't tell you about this, okay? Lavoisier screwed me too not too long ago. Tyrex asked me to help him, just like he asked you. I was warned at Isla Tesoro that crossing the four-eyes is the same as crossing Marcus. So I suggest you forgeting about this. You are neither the first nor the last in this.";
			link.l1.go = "rocur_51";
		break;
		
		case "rocur_51":
            dialog.text = "I see. You too got screwed by those two then?";
			link.l1 = "Well yes. I was thinking to make some troubles to the four-eyes too before I learnt more about him. It doesn't worth it.";
			link.l1.go = "rocur_52";
		break;
		
		case "rocur_52":
            dialog.text = "Would you try to repay the bastard if you knew that no one will ever find out?";
			link.l1 = "Ha! Sure! Although I don't know how. Attack the flutes of Lavoisier and one shiny day your sailors will get drunk and blab everything. Don't you know how it works?";
			link.l1.go = "rocur_53";
		break;
		
		case "rocur_53":
            dialog.text = "Are you heading to Martinique now? When will you arrive to La Vega again?";
			link.l1 = "Marcus gave me three weeks.";
			link.l1.go = "rocur_54";
		break;
		
		case "rocur_54":
            dialog.text = "Try to make it in two. I'll think it through... Find me in Gonaives Bay in 14 days. Head right there, don't enter La Vega.";
			link.l1 = "I can see you are up to something, he-ha. Fine. I'll try.";
			link.l1.go = "rocur_55";
		break;
		
		case "rocur_55":
            dialog.text = "You'd better do that. See you!";
			link.l1 = "...";
			link.l1.go = "rocur_56";
		break;
		
		case "rocur_56":
            DialogExit();
			chrDisableReloadToLocation = false;
			bDisableFastReload = false;
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload3", "none", "", "", "", 10.0);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			ReOpenQuestHeader("Roger_4");
			AddQuestRecord("Roger_4", "11");
			pchar.quest.mtraxx_pasq_gonaiv.win_condition.l1 = "Timer";
			pchar.quest.mtraxx_pasq_gonaiv.win_condition.l1.date.hour  = 1.0;
			pchar.quest.mtraxx_pasq_gonaiv.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 14);
			pchar.quest.mtraxx_pasq_gonaiv.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 14);
			pchar.quest.mtraxx_pasq_gonaiv.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 14);
			pchar.quest.mtraxx_pasq_gonaiv.win_condition.l2 = "location";
			pchar.quest.mtraxx_pasq_gonaiv.win_condition.l2.location = "Shore34";
			pchar.quest.mtraxx_pasq_gonaiv.function = "Mtraxx_PasqualeJanGonaiv";
			SetFunctionTimerCondition("Mtraxx_PasqualeJanTimer", 0, 0, 10, false); // правки прогона 3
			SetFunctionTimerCondition("Mtraxx_PasqualeJanTimeOver", 0, 0, 15, false);
			pchar.questTemp.Mtraxx.Pasquale.Grabbing = "true";
		break;
		
		case "rocur_57":
			if (pchar.location.from_sea != "Shore34")
			{
				dialog.text = RandSwear()+"Where is your ship? Did you arrive here from La Vega? Merde! I asked you to come here unnoticed and in secret. My plan is ruined now. Damn it!..";
				link.l1 = "Hm...";
				link.l1.go = "rocur_58";
			}
			if (GetOfficersQuantity(pchar) > 0)
			{
				dialog.text = "There you are , "+pchar.name+". It's good you are here. Send your mates back to the ship. It's a private conversation.";
				link.l1 = "Very well.";
				link.l1.go = "rocur_59";
			}
			else
			{
				dialog.text = "There you are , "+pchar.name+". It's good you are here.  I have a business for you. Ready to hear it?";
				link.l1 = "Sure!";
				link.l1.go = "rocur_61";
			}
		break;
		
		case "rocur_58":
            DialogExit();
			Group_DelCharacter("RocurSeaGroup", "Mrt_Rocur");
			Group_DeleteGroup("RocurSeaGroup");
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "sea", "none", "", "", "OpenTheDoors", 10.0);
			AddQuestRecord("Roger_4", "14");
			CloseQuestHeader("Roger_4");
		break;
		
		case "rocur_59":
            DialogExit();
			LAi_SetStayType(npchar);
			npchar.dialog.currentnode = "rocur_60";
		break;
		
		case "rocur_60":
            if (GetOfficersQuantity(pchar) > 0)
			{
				dialog.text = "I told you already - send your officers away!";
				link.l1 = "Yes-yes, I got it.";
				link.l1.go = "rocur_59";
			}
			else
			{
				dialog.text = "Great. Now we can talk freely. I have a business for you. Ready to hear it out?";
				link.l1 = "Sure!";
				link.l1.go = "rocur_61";
			}
		break;
		
		case "rocur_61":
            dialog.text = "Do you know La Vega well?";
			link.l1 = "Well... I think I do. Why are you asking?";
			link.l1.go = "rocur_62";
		break;
		
		case "rocur_62":
            dialog.text = "Ever noticed the two-store house on the right from the store? The only big house among the shacks.";
			link.l1 = "The always closed one? Yeah, I know it. What about it?";
			link.l1.go = "rocur_63";
		break;
		
		case "rocur_63":
            dialog.text = "Nicely noticed - it's always closed. While you were on your mission at Martinique, our common friend Lavoisier had been here for a three days as guest of Marcus Tyrex. They were spending their time in this house drinking rum and having fun.";
			link.l1 = "Hm...";
			link.l1.go = "rocur_64";
		break;
		
		case "rocur_64":
            dialog.text = "Then Lavoisier's men dragged some boxes and packages to the house. Then he left. As for Marcus, he stays in the place every day for several hours.";
			link.l1 = "Any suggestions?";
			link.l1.go = "rocur_65";
		break;
		
		case "rocur_65":
            dialog.text = "What siggestions? I'm sure this house must be a base of Lavoisier in La Vega. I didn't see much through the windows but there are goods stored there. I think that the four-eyes has the means to repay what he owes us.";
			link.l1 = "Well-well... Do you want to break in? What about the closed door? It's heavy and sturdy, no way we are breaking it in quite.";
			link.l1.go = "rocur_66";
		break;
		
		case "rocur_66":
            dialog.text = ""+pchar.name+", do you think of me as an idiot? I have already sorted this out. I have made the key using a wax mask of the lock. Costed my quite a penny but it's my problem.";
			link.l1 = "Heh! Why wait for me then?";
			link.l1.go = "rocur_67";
		break;
		
		case "rocur_67":
            dialog.text = "It will be safer that way. One head is good, two heads are better. Four eyes are better than two.";
			link.l1 = "Well yeah, crossing Lavoisier will take as many eyes as he has, ha-ha-ha! But what of Tyrex? What if he enters the house while we are checking Pasquale's belongings?";
			link.l1.go = "rocur_68";
		break;
		
		case "rocur_68":
            dialog.text = "He won't. He is always back to his own house by the midnight. Ready to go to La Vega next night? They won't ever realize who fucked them up: you are still at Martinique and I left La Vega a week ago.";
			link.l1 = "I'd love to screw the four-eyed encul?. But tell me Jean, how are we supposed to carry barrels and chests from the house?";
			link.l1.go = "rocur_69";
		break;
		
		case "rocur_69":
            dialog.text = "I am sure we will find there more moveable valuable items than chests and barrels with goods. Are you in?";
			link.l1 = "Hell yeah!";
			link.l1.go = "rocur_70";
		break;
		
		case "rocur_70":
            dialog.text = "Great, glad I wasn't wrong about you. Let's take a rest now, we are heading to La Vega at midnight.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_PasqualeNight");
		break;
		
		case "rocur_71":
            dialog.text = "Time to go. We should rob the bastard and get the hell out of there before dawn.";
			link.l1 = "Onwards!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_PasqualeNightMarch");
		break;
		
		case "rocur_72":
            dialog.text = "Hush... Now move, quietly, to Pasquale's house. Follow me.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_PasqualeNightToHouse");
		break;
		
		case "rocur_73":
            dialog.text = "Look at this - so much stuff lying around. Let's begin. Check a chest near the door, then go upstairs and take of a room. I will stay here: I know the tricks of hiding valuables among junk. Keep your eyes and ears open and stay away from the windows.";
			link.l1 = "Alright...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_PasqualeNightInHouse");
		break;
		
		case "rocur_74":
            dialog.text = ""+pchar.name+", what do you have? Anything of interest?";
			link.l1 = "Come and look. This is something.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_PasqualeJanSeeGirl");
		break;
		
		case "rocur_75":
            dialog.text = "Damn it! Now I see why Tyrex comes to this place every day. It's not only the four-eyed's storehouse but also a brothel.";
			link.l1 = "Looks like she is a slave here.";
			link.l1.go = "rocur_76";
		break;
		
		case "rocur_76":
            dialog.text = "Sure thing. Look at her - she is an obvious port whore... Bad luck for us. Have to kill her.";
			link.l1 = "Really?";
			link.l1.go = "rocur_77";
		break;
		
		case "rocur_77":
            dialog.text = "She saw our faces and heard your name. She will tell everything to Tyrex.";
			link.l1 = "Hm...";
			link.l1.go = "rocur_78";
		break;
		
		case "rocur_78":
            dialog.text = "It's your choice. Her life may cost you yours.";
			link.l1 = "";
			link.l1.go = "rocur_79";
		break;
		
		case "rocur_79":
            DialogExit();
			sld = characterFromId("Mirabella");
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;
		
		case "rocur_80":
            dialog.text = "Don't even think of trusting this whore. Tomorrow Tyrex will know everything. Do you want to receive a black mark?";
			link.l1 = "No, I don't. Neither I want to kill the wench - I have a use for her. She is coming with me.";
			link.l1.go = "rocur_81";
		break;
		
		case "rocur_81":
            dialog.text = "Don't be an idiot! She will run away as soon as she gets a chance. Look at her forehead, do you see the brand? She is a thief.";
			link.l1 = "Hm. You are probably right, Jan. Finish her and let's get away from here.";
			link.l1.go = "rocur_82";
			link.l2 = "I am not planning to keep her on my ship. I have a place where she will never escape from and there no ears to hear her out too. She will also keep doing her line of work there... A personal whore, free of charge, he-he!";
			link.l2.go = "rocur_84";
		break;
		
		case "rocur_82":
            DialogExit();
			LAi_SetActorType(pchar);
			LAi_ActorGoToLocator(pchar, "goto", "goto6", "", 5);
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocator(npchar, "goto", "goto7", "Mtraxx_PasqualeJanKillGirl", 5);
		break;
		
		case "rocur_83":
			ChangeCharacterComplexReputation(pchar, "nobility", -10);
            dialog.text = "This is it, no way she telling Tyrex anything...";
			link.l1 = "Heh...";
			link.l1.go = "rocur_86";
		break;
		
		case "rocur_84":
            DialogExit();
			sld = characterFromId("Mirabella");
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;
		
		case "rocur_85":
            dialog.text = "You are a kind man, "+pchar.name+". Why do you wanna bother yourself with her? Whatever, it's your choice. Make sure she is quite when we are leaving.";
			link.l1 = "If she won't be - she is dead.";
			link.l1.go = "rocur_86";
		break;
		
		case "rocur_86":
			if (CheckAttribute(pchar, "questTemp.Mtraxx.Pasquale.Grabbing.Chest")) sTemp = "A bit. A chest full of doubloons, a handful of rubies, a map of Hispaniola and some rum.";
			else sTemp = "Nothing of value.";
            dialog.text = "What did you find?";
			link.l1 = sTemp;
			link.l1.go = "rocur_87";
		break;
		
		case "rocur_87":
			Log_Info("You have received two treasure collections.");
			PlaySound("interface\important_item.wav");
			TakeNItems(pchar, "icollection", 2);
            dialog.text = "More luck on my side. Here, take your cut. I would never manage to take it all with me to the shore. The four-eyes paid us in full.";
			link.l1 = "Splendid! Well done, Jean!";
			link.l1.go = "rocur_88";
		break;
		
		case "rocur_88":
            dialog.text = "Now go!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_PasqualeNightOutHouse");
		break;
		
		case "rocur_89":
            dialog.text = "Great. It's done. Nice and quite. Let's go to Gonaives Bay.";
			link.l1 = "On my way!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_PasqualeNightGulf");
		break;
		
		case "rocur_90":
            dialog.text = "Well, "+pchar.name+". It's time we part our ways. I am not sure we will ever meet again but know that it was a pleasure knowing you.";
			link.l1 = "We will see each other often in La Vega.";
			link.l1.go = "rocur_91";
		break;
		
		case "rocur_91":
            dialog.text = "No. I am done with Tyrex. This mess with Lavoisier was the last straw.";
			link.l1 = "Hm... Forget about it. We've got what was ours by right. Tyrex gives profitable leads, doesn't he? Last time I made more than a half a million from Red Wolf's treasure.";
			link.l1.go = "rocur_92";
		break;
		
		case "rocur_92":
            dialog.text = "Tell me, did you put a lot of effort in finding?";
			link.l1 = "Well... It wasn't easy. Did plenty of thinking, travelling and fighting. It was worth it, I think.";
			link.l1.go = "rocur_93";
		break;
		
		case "rocur_93":
            dialog.text = "How much did you pay to Tyrex?";
			link.l1 = "A third.";
			link.l1.go = "rocur_94";
		break;
		
		case "rocur_94":
            dialog.text = "What was his part in this business? What did Marcus do?";
			link.l1 = "Hm... He has given me Red Wolf's log...";
			link.l1.go = "rocur_95";
		break;
		
		case "rocur_95":
            dialog.text = "That's all? Right?";
			link.l1 = "Well... I would never had learnt about captain Wulfric otherwise...";
			link.l1.go = "rocur_96";
		break;
		
		case "rocur_96":
            dialog.text = ""+pchar.name+", don't you see that Tyrex makes others to do the dirty work? You think that he would give you a task to find that treasure if he could do it on his own? Hell no, I swear, he tried to do it himself first and when he fucked it up, he called you to do the job. While you were doing the thinking, spending weeks in the sea, fighting and risking your life, this bastard along his four-eyed friend were fucking up the whore in La Vega. And for this he also got a quarter of million pesos. Just like that\nYou think he sent his dog Leprechaun to help us in our raid for Merida? No, he wanted to make sure his interests are safe. Everything Marcus can do on his own, he does, either alone or with the help from Cutlasses, Bolds, Leprechauns and other dumb idiots who works for him for pennies. People like you and I get leads that Marcus is too stupid to execute on his own\nRemember all tasks you did for him? Count how much did he make on you. I had enough of this. Now I have money, a great corvette and loyal crew. From now own I am a freelancer. Heading to Jamaica, perhaps, I will receive a letter of marque there.";
			link.l1 = "I don't think you are quite right about Tyrex... But I wish you luck Jean! Hope you'll find success at Jamaica.";
			link.l1.go = "rocur_97";
		break;
		
		case "rocur_97":
            dialog.text = "I will. Best of luck to you too and think of what I've said. Being a Marcus's bitch is not the best role for you. Farewell, brother! Godspeed!";
			link.l1 = "Good hunting, Jean!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_PasqualeAddComplete");
		break;
		
		case "rocur_98":
            dialog.text = ""+pchar.name+", tell me, how did we spend so much time in the jungles? Now my plan is screwed. Eh... Bye, pal...";
			link.l1 = "Heh...";
			link.l1.go = "rocur_99";
		break;
		
		case "rocur_99":
            DialogExit();
		    LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(sld, "reload", "reload1", "none", "", "", "", 10.0);
			sld.lifeday = 0;
			Group_DeleteGroup("RocurSeaGroup");
			AddQuestRecord("Roger_4", "18");
			CloseQuestHeader("Roger_4");
		break;
		
		// Люк Лепрекон
		case "lepricon":
            dialog.text = "Greetings, captain "+GetFullName(pchar)+". Luke Lepricon is at your service! I've been told we are going to the jungles of Southern Main.";
			link.l1 = "Precisely. Embark on long boats, we are leaving at once.";
			link.l1.go = "lepricon_1";
		break;
		
		case "lepricon_1":
            dialog.text = "Let an old buccaneer to give you some advice, captain. Since we are heading to the selva - we will surely meet the Indians. Take presents for them with you. Indian warriors adore beautiful pistols, especially the duel ones. They also like compasses and spy glasses. It's magic items for them\nTheir women prefer cheap jewels and trinkets like mirrors and scallops. If we run into a fight with them use trombones and arquebuses: grapeshot is good versus unprotected enemy.";
			link.l1 = "Very good, Luke. Your words are noted. Welcome aboard.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_MeridaSail");
		break;
		
		case "lepricon_2":
            dialog.text = "See the chieftain as soon as we get to the village. And bring gifts, it's pointless otherwise. Make sure to ask about anyone among his people who knows secret passages in the jungles and who has no fear of travelling. I am coming with you, address me in case you face any difficulties.";
			link.l1 = "Let's go! Jean, Luke - follow me!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_MeridaSeekVillage");
		break;
		
		case "lepricon_3":
            dialog.text = "Any questions, captain?";
			link.l1 = "None for now, Luke.";
			link.l1.go = "lepricon_3x";
			if (pchar.questTemp.Mtraxx == "merida_advice")
			{
				link.l1 = "Yes! I had a talk with their chieftain, I gifted him and later he summoned his redskins for a meeting. There are those among them who know how to get to Merida yet nobody is eager to go - they fear another tribe called Capongs. Those scare the locals shitless. The redskin claims we have no chances to find the path on our own and there is no guide for us to hire. And what are we supposed to do now, huh?!";
				link.l1.go = "lepricon_4";
			}
			if (CheckAttribute(pchar, "questTemp.Mtraxx.Merida.Potion") && GetCharacterItem(pchar, "potion3") >= 12)
			{
				link.l2 = "I have antidotes with me.";
				if (GetCharacterItem(pchar, "potion3") > 42) link.l2.go = "lepricon_7";
				else link.l2.go = "lepricon_6";
			}
		break;
		
		case "lepricon_3x":
           DialogExit();
		   npchar.dialog.currentnode = "lepricon_3";
		break;
		
		case "lepricon_4":
            dialog.text = "Hm. Captain, a cowardness is often beaten by a greed. Promise a reward so generous that a man will take the job... You know what? Try a more cunning option - their women. Gift them and ask about their spouses and chances are - you find the guide we need. Promise her piles of beads and mirrors for her husband's assistance. Be generous and promise a lot, persuade them.";
			link.l1 = "Heh! I will try at least although I am not sure that will work...";
			link.l1.go = "lepricon_5";
		break;
		
		case "lepricon_5":
            dialog.text = "One more thing captain, according to the chief, we may face enemy Indians in the jungles. They poison their weapons so make sure to supply your men with antidotes\nMe and my people always have plenty of potions with us. As for your pirates... Bring me antidotes and I will see them distributed among your men. I need at least a dozen of potions for this. Make sure you bring some for you and your officers too.";
			link.l1 = "Fine. I'll have the antidotes.";
			link.l1.go = "lepricon_5x";
		break;
		
		case "lepricon_5x":
           DialogExit();
		   npchar.dialog.currentnode = "lepricon_3";
		   pchar.questTemp.Mtraxx = "merida_hayamee";
		   pchar.questTemp.Mtraxx.Merida.Women = "true";
		   pchar.questTemp.Mtraxx.Merida.Potion = "true";
		   AddQuestRecord("Roger_5", "8");
		   sld = characterFromId("Hayamee");
		   LAi_CharacterEnableDialog(sld);
		  // LocatorReloadEnterDisable("Shore_ship3", "boat", false); 
		   bQuestDisableMapEnter = false;
		   DeleteAttribute(pchar, "GenQuest.MapClosedNoBattle");// выпустим в море
		   SetFunctionTimerCondition("Mtraxx_MeridaPotionLate", 0, 0, 10, false); // таймер, чтобы не ходил долго
		break;
		
		case "lepricon_6":
			i = GetCharacterItem(pchar, "potion3");
			RemoveItems(pchar, "potion3", i);
			pchar.questTemp.Mtraxx.Merida.Antidote = i;
            dialog.text = "Very well. Give them to me. I'll do the rest.";
			link.l1 = "There...";
			link.l1.go = "lepricon_8";
		break;
		
		case "lepricon_7":
			RemoveItems(pchar, "potion3", 42);
			pchar.questTemp.Mtraxx.Merida.Antidote = 42;
            dialog.text = "Three and a half dozens would suffice. The rest you should keep to yourself.";
			link.l1 = "Alright...";
			link.l1.go = "lepricon_8";
		break;
		
		case "lepricon_8":
            DialogExit();
		    npchar.dialog.currentnode = "lepricon_3";
			DeleteAttribute(pchar, "questTemp.Mtraxx.Merida.Potion");
		break;
		
		case "lepricon_9":
            dialog.text = "Captain, your Indians - Hayami and Tagofa had been waiting for you to deliver the gifts you'd promised to them too long and left to another village to dance and drink kasheeri. I have a feeling that your manner of doing business will do us no good. I am sorry, but you are out of this. Picard will lead the expedition from this moment.";
			link.l1 = "Screw you all then!";
			link.l1.go = "exit";
			AddQuestRecord("Roger_5", "19");
			AddDialogExitQuestFunction("Mtraxx_MeridaHayameeFail");
		break;
		
		case "lepricon_10":
            dialog.text = "Captain, what the hell? We've lost too much time for nothing! I have a feeling that your manner of doing business will do us no good. I am sorry, but you are out of this. Picard will lead the expedition from this moment.";
			link.l1 = "Screw you all then!";
			link.l1.go = "exit";
			AddQuestRecord("Roger_5", "20");
			AddDialogExitQuestFunction("Mtraxx_MeridaHayameeFail");
		break;
		
		case "lepricon_11":
            dialog.text = "Captain what the hell? You had ten days to find leather and planks. There is Maracaibo town not far from here! I have a feeling that your manner of doing business will do us no good. I am sorry, but you are out of this. Picard will lead the expedition from this moment.";
			link.l1 = "Screw you all then!";
			link.l1.go = "exit";
			AddQuestRecord("Roger_5", "20");
			AddDialogExitQuestFunction("Mtraxx_MeridaHayameeFail");
		break;
		
		case "lepricon_12":
            dialog.text = "Captain, I am sorry but I was supposed to be in La Vega long ago as were you actually. You must had forgotten about the existence of me and Marcus, Anyways, I am leaving. You should keep doing whatever you are doing and I will explain everything to Marcus. Farewell, it's pity, I thought better of you.";
			link.l1 = "Hm...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_MeridaReturnFail");
		break;
		
		case "lepricon_13":
            dialog.text = "So, as far as I understand, you guys had a fight. Failed to split the booty, right Charlie Prince?";
			link.l1 = "Leprechaun? You are here... No big surprise though. Yeah the greedy bastards had spit on the Code and tried to kill me.";
			link.l1.go = "lepricon_14";
		break;
		
		case "lepricon_14":
            dialog.text = "Yeah, they did you quite a beating Prince. You look like shit\nWhat did you say about the Code? Let me enlighten you: I had been working with Marcus who is supposedly the Keeper of this Code, I have seen men spit on it so many times I wouldn't dare to count. Some of those men paid a terrible price. Some of them didn't\nYou can do anything if you want to it badly enough. Especially if no one is seeing it.";
			link.l1 = "You are here for the treasure too?";
			link.l1.go = "lepricon_15";
		break;
		
		case "lepricon_15":
            dialog.text = "Stupid question. What else could I do here so far from my homeland Hispaniola? Although after all I am smarter than you all: knowing yours rotten pirate nature, I just waited, letting you rats to tear each other apart leaving only one enemy alive but wounded and tired.";
			link.l1 = "Enemy? This is how you follow your patron's Code?! He kills people for this!";
			link.l1.go = "lepricon_16";
		break;
		
		case "lepricon_16":
            dialog.text = "I am not a subject to the Code, I am not a pirate. I don't even own a ship - I had to rent a tub to get here. I am nothing more but a buccaneer in a nutshell. I am a hunter, I hunt buffalos and make bucan. Fucking Spanish who claim that we, the French buccaneer, spoil their living, made me seek support and protection from Marcus. I help him in his business for that sometimes\nAlthough I am not a pirate, me and my men fight well, you have seen us in action.";
			link.l1 = "We were raiding and fighting together Leprechaun. We covered each others backs. Is it all but nothing to you?";
			link.l1.go = "lepricon_17";
		break;
		
		case "lepricon_17":
            dialog.text = "I'll be honest with you Prince: I never liked you. You are an upstart. An insolent youngster, a fan of drinks and fallen women, who did a few profitable jobs for Tyrex and thought of himself as a great pirate\nBesides, you are butcher by nature. You think Cartagena gave you more weight within the Brethren? No, only among the monsters such as you are.";
			link.l1 = "This is hilarious! Spoken by a true angel himself! You old bastard!";
			link.l1.go = "lepricon_18";
		break;
		
		case "lepricon_18":
            dialog.text = "I think we have cleared thing out by now. Time to end this comedy. Devils have been waiting for you too long in hell.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_RetributionLepriconFight");
		break;
		
		// Тагофа - проводник к Мериде
		case "tagofa":
            dialog.text = "Tagofa greets you, son of the sea. Do you want me to show you a way to the Spanish settlement at mountains?";
			link.l1 = "Correct. I see that you are good with our language unlike others of your people.";
			link.l1.go = "tagofa_1";
		break;
		
		case "tagofa_1":
            dialog.text = "Tagofa often had dealings with yalanaui... Most of our way we will make on a river. You will need long boats. Do you have them?";
			link.l1 = "Do you? We could borrow them for little while...";
			link.l1.go = "tagofa_2";
		break;
		
		case "tagofa_2":
            dialog.text = "Our village is small, we have got a very few longboats and all of them are usefull only for fishing. Now, we need good long boats, like the ones on your ships.";
			link.l1 = "Hm... We'll need six long boats then. The ship doesn't have that many.";
			link.l1.go = "tagofa_3";
		break;
		
		case "tagofa_3":
            dialog.text = "Build them then. You, white folk, can repair your giant vessels ashore, surely you can build a few long boats.";
			link.l1 = "Heh, seems like you are right, Tagofa. Get us to the river, I hope it is not far from here?";
			link.l1.go = "tagofa_4";
		break;
		
		case "tagofa_4":
            dialog.text = "It's not. Follow me.";
			link.l1 = "...";
			link.l1.go = "tagofa_5";
		break;
		
		case "tagofa_5":
           DialogExit();
		   npchar.dialog.currentnode = "tagofa_6";
		   LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "Mtraxx_MeridaGotoRiver", 5.0);
		break;
		
		case "tagofa_6":
            dialog.text = "Now that's the river. We will start our travel from here. Build boats and then we will begin.";
			link.l1 = "Got it, Tagofa. I will tell you when it's done.";
			link.l1.go = "tagofa_7";
		break;
		
		case "tagofa_7":
            DialogExit();
			LAi_CharacterDisableDialog(npchar);
			npchar.dialog.currentnode = "tagofa_8";
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			pchar.questTemp.Mtraxx = "merida_boats";
			pchar.questTemp.Mtraxx.Boats = "true";
			chrDisableReloadToLocation = false;
			DoQuestCheckDelay("TalkSelf_Quest", 2.0);
			// Лепрекона - гулять
			sld = characterFromId("Lepricon");
			sld.dialog.currentnode = "lepricon_3";
			LAi_SetWarriorType(sld);
			LAi_warrior_DialogEnable(sld, true);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			SetFunctionTimerCondition("Mtraxx_MeridaBoatLate", 0, 0, 10, false); // таймер, чтобы не ходил долго
		break;
		
		case "tagofa_8":
            dialog.text = "Are the boats ready, white chieftain?";
			link.l1 = "Yes. My men are about to get on them.";
			link.l1.go = "tagofa_9";
		break;
		
		case "tagofa_9":
            dialog.text = "Very good. Get on the first one along with me. Tagofa will show the way.";
			link.l1 = "";
			link.l1.go = "tagofa_10";
		break;
		
		case "tagofa_10":
            DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload2", "none", "", "", "Mtraxx_MeridaRiverTrip", -1);
			chrDisableReloadToLocation = true;
		break;
		
		case "tagofa_11":
            dialog.text = "The river part is done. It is not far from the Spanish settlement from here. A pathway starts here, stick to it and we won't get lost. We have managed to round a forest filled with Capongs hunters but here is also their land. Be careful.";
			link.l1 = "Don't worry. We'll wipe them out as soon as they show us their ugly painted faces.";
			link.l1.go = "tagofa_12";
		break;
		
		case "tagofa_12":
            DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			pchar.quest.mtraxx_merida_warning.win_condition.l1 = "locator";
			pchar.quest.mtraxx_merida_warning.win_condition.l1.location = "Serpentine2";
			pchar.quest.mtraxx_merida_warning.win_condition.l1.locator_group = "quest";
			pchar.quest.mtraxx_merida_warning.win_condition.l1.locator = "detector1";
			pchar.quest.mtraxx_merida_warning.function = "Mtraxx_MeridaWarning";
			chrDisableReloadToLocation = false;
		break;
		
		case "tagofa_13":
            dialog.text = "";
			link.l1 = "Hey! Tagofa! Look, what is it in the middle of the pathway? Some Indian thingy.";
			link.l1.go = "tagofa_14";
		break;
		
		case "tagofa_14":
            DialogExit();
			LAi_SetActorType(pchar);
			LAi_SetActorType(npchar);
			ChangeCharacterAddressGroup(npchar, "Serpentine2", "goto", "goto5");
			LAi_ActorGoToLocator(npchar, "quest", "quest1", "Mtraxx_MeridaWarning", -1);
		break;
		
		case "tagofa_15":
            dialog.text = "It is a sign of Capongs. A warning. It tells you to stop and go no further. Capongs have already spotted us.";
			link.l1 = "What if we go further? Will they attack us?";
			link.l1.go = "tagofa_16";
		break;
		
		case "tagofa_16":
            dialog.text = "Yes, white chieftain. You must be looking threatening to them since they didn't attack us already. And yet they put a sign for you.";
			link.l1 = "Fuck the sign. We are moving forward. If they step in our way, we kill them all. Squad! Listen to my orders! At arms! Make ready! Be alerted!";
			link.l1.go = "tagofa_17";
		break;
		
		case "tagofa_17":
            DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			pchar.quest.mtraxx_merida_capong.win_condition.l1 = "location";
			pchar.quest.mtraxx_merida_capong.win_condition.l1.location = "Merida_jungle_01";
			pchar.quest.mtraxx_merida_capong.function = "Mtraxx_MeridaPrepareCapongAttack";
		break;
		
		case "tagofa_18":
            dialog.text = "White chief and his men crushed the capongas. Spanish city is close. There is a valley further. Then you will see a waterfall. Tagofa will no go to the Spanish. I'll be waiting for you near the waterfall.";
			link.l1 = "Very well. Onwards!";
			link.l1.go = "tagofa_19";
		break;
		
		case "tagofa_19":
            DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			chrDisableReloadToLocation = false;
			pchar.quest.mtraxx_merida_exittown.win_condition.l1 = "location";
			pchar.quest.mtraxx_merida_exittown.win_condition.l1.location = "Merida_ExitTown";
			pchar.quest.mtraxx_merida_exittown.function = "Mtraxx_MeridaExitTown";
			Mtraxx_MeridaCheckOurWarriors();
			AddQuestRecord("Roger_5", "15");
		break;
		
		case "tagofa_20":
            dialog.text = "We have returned, white chief. Tagofa did what he promised.";
			link.l1 = "Gratitude, Tagofa. You did well.";
			link.l1.go = "tagofa_21";
		break;
		
		case "tagofa_21":
            dialog.text = "Tagofa should go. Hayami is waiting for me very much. Good bye son of the sea.";
			link.l1 = "Good luck son of the selva. Send my regards to your wife.";
			link.l1.go = "tagofa_22";
		break;
		
		case "tagofa_22":
            DialogExit();
			chrDisableReloadToLocation = false;
			npchar.lifeday = 0;
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "", 20.0);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			pchar.quest.mtraxx_merida_final.win_condition.l1 = "location";
			pchar.quest.mtraxx_merida_final.win_condition.l1.location = "Shore_ship3";
			pchar.quest.mtraxx_merida_final.function = "Mtraxx_MeridaFinal";
			ChangeIndianRelation(7.0);
		break;
		
		// дозорный у Мериды
		case "merida_guard":
            dialog.text = "Hey! Who are you and what do you want?";
			link.l1 = "We need to get to Merida and have a chat with your governor or whoever you have instead of him...";
			link.l1.go = "merida_guard_1";
		break;
		
		case "merida_guard_1":
            dialog.text = "We don't let strangers to Merida. Leave!";
			link.l1 = "Pal we were rowing hard for two days and then fighting hordes of Indians not to leave just like that. I repeat, I want to talk to your head of the village! Then, perhaps, you place will stay intact.";
			link.l1.go = "merida_guard_2";
		break;
		
		case "merida_guard_2":
            dialog.text = "Are you making threats ladron?";
			link.l1 = "How did figure that out? Oh yes, I am making threats. Either we are getting what we are here for with peace or by force.";
			link.l1.go = "merida_guard_3";
		break;
		
		case "merida_guard_3":
            dialog.text = "You will never enter Merida you fucking pirate! Alarm! Enemy at the gates!";
			link.l1 = "...";
			link.l1.go = "merida_guard_4";
		break;
		
		case "merida_guard_4":
            DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload2", "none", "", "", "", 10.0);
			DoQuestFunctionDelay("Mtraxx_MeridaHouseGuards", 5.0);
		break;
		
		// мэр Мериды
		case "merida_head":
            dialog.text = "Damned ladrones...";
			link.l1 = "Stop the swearing, senor. I was the one who offered to solve this matter peacefully but your officer decided otherwise. What happened on the streets of Merida is, in a great degree, his fault.";
			link.l1.go = "merida_head_1";
		break;
		
		case "merida_head_1":
            dialog.text = "What do you want from us, you scoundrels? Our town is small and poor. We don't have neither visitors nor gold and silver.";
			link.l1 = "Then how did you manage to build yourself such a fine residence, your Excellency? Actually, Merida itself doesn't make an impression of a poor village.";
			link.l1.go = "merida_head_2";
		break;
		
		case "merida_head_2":
            dialog.text = "The people of Merida put a lot of effort to build our town.";
			link.l1 = "Cut the bullshit! Enough of this. I am aware of the gems you've found. Emeralds and opals. Don't play the poor card, caballero. You are a rich bastard and you should share.";
			link.l1.go = "merida_head_3";
		break;
		
		case "merida_head_3":
            dialog.text = "Emeralds? Opals? There are lies and nothing more! Emeralds are mined far to the West from here and as for opals...";
			link.l1 = "Quite lying to me you Spanish dog. You probably have yet to realize what people have come to your doors. Either we get our stones or your fine town will turn into a burning ruins and the Capongas will eventually take care of survivors. You will get a special treat from us don't worry, you will tell us everything.";
			link.l1.go = "merida_head_4";
		break;
		
		case "merida_head_4":
            dialog.text = "";
			link.l1 = "Why are you so pale? Finally. So? Where are the gems?";
			link.l1.go = "merida_head_5";
		break;
		
		case "merida_head_5":
            dialog.text = "These gems are all what we the people of Merida have. We were mining them for a year, crushing stones in the mountains and fighting savages. It's a hard and dangerous work...";
			link.l1 = "So? Trying to make me feel bad for you? Give us the stones, now. We are waiting. Or your Merida and her citizens will be gone.";
			link.l1.go = "merida_head_6";
		break;
		
		case "merida_head_6":
            dialog.text = "No way you are getting away with this you wicked bandits. God sees everything and He will punish you...";
			link.l1 = "One more insult and I am sending my man for a brazier.";
			link.l1.go = "merida_head_7";
		break;
		
		case "merida_head_7":
            dialog.text = "I will surrender you the gems if you swear not to touch the town and its citizens who are still alive.";
			link.l1 = "I've told you already - I have no interest in your town. Bring the gems here and we are living.";
			link.l1.go = "merida_head_8";
		break;
		
		case "merida_head_8":
            DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocator(npchar, "goto", "goto2", "Mtraxx_MeridaOpenChest", -1);
		break;
		
		case "merida_head_9":
            dialog.text = "Grab your bloody prize and know that you are leaving a whole town to poverty.";
			link.l1 = "Are you serious? Just mine some more fucking gems, the mountains are still there! Jean go check the don's chests.";
			link.l1.go = "merida_head_10";
		break;
		
		case "merida_head_10":
            DialogExit();
			sld = characterFromId("Mrt_Rocur");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocator(sld, "goto", "goto2", "Mtraxx_MeridaGiveJewelry", -1);
		break;
		
		case "merida_head_sleep":
            dialog.text = "You promised to leave the town once you have the gems... You have them now and your ladrones had set our houses on fire! You are a liar and a wicked pirate! I hope the flames of hell will be this hot for you!!!";
			link.l1 = "";
			link.l1.go = "exit";
			AddDialogExitQuest("Mtraxx_RetributionSleep2");
		break;
		
		// капитан пинаса Китти
		case "kittycap":
            dialog.text = TimeGreeting()+", kind sir. What's your purpose here?";
			link.l1 = "I am from Tyrex. I was told to escort your vessel to Bridgetown. Are you ready?";
			link.l1.go = "kittycap_1";
		break;
		
		case "kittycap_1":
            dialog.text = "Well, finally! Yes, my crew is ready to set sail immediately!";
			link.l1 = "Splendid. Ready the sails. Get us underway!";
			link.l1.go = "kittycap_2";
		break;
		
		case "kittycap_2":
		    DialogExit();
            LAi_CharacterDisableDialog(npchar);
			Group_DelCharacter("Mtr_Kitty", "Mtr_KittyCap");
			SetCharacterRemovable(npchar, false);
			npchar.CompanionEnemyEnable = false; //всегда друзья
			LAi_SetImmortal(npchar, false);
			SetCompanionIndex(pchar, -1, sti(npchar.index));
			npchar.loyality = MAX_LOYALITY;
		    pchar.quest.mtraxx_ignasio_sail.win_condition.l1 = "location";
			pchar.quest.mtraxx_ignasio_sail.win_condition.l1.location = "Bridgetown_town";
			pchar.quest.mtraxx_ignasio_sail.function = "Mtraxx_IgnasioArrive";
			SetFunctionTimerCondition("Mtraxx_IgnasioTimeOver", 0, 0, 30, false);
			pchar.quest.mtraxx_ignasio_sinkkitty.win_condition.l1 = "NPC_Death";
			pchar.quest.mtraxx_ignasio_sinkkitty.win_condition.l1.character = "Mtr_KittyCap";
			pchar.quest.mtraxx_ignasio_sinkkitty.function = "Mtraxx_IgnasioKittySink";
			bQuestDisableMapEnter = false;//открыть карту
			DeleteAttribute(pchar, "GenQuest.MapClosedNoBattle");
		break;
		
		case "kittycap_3":
            dialog.text = "Thank you for helping me, captain! With you on my side I was as safe as behind a fort's walls.";
			link.l1 = "Don't mention it, pal. Everything is on Marcus. Good luck!";
			link.l1.go = "kittycap_4";
		break;
		
		case "kittycap_4":
            DialogExit();
			npchar.lifeday = 0;
			RemoveCharacterCompanion(pchar, npchar);
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload4_back", "none", "", "", "", 30.0);
			Mtraxx_IgnasioCreateMarko();
			AddCharacterExpToSkill(pchar, "Sailing", 200);
		break;
		
		// Игнасио Марко
		case "ignasio":
            dialog.text = "Greetings to the brave captain! Let me introduce myself - a privateer of England, Ignacio Marco of the Torero.";
			link.l1 = TimeGreeting()+", friend. Captain "+GetFullName(pchar)+" at your service. How can I help you?";
			link.l1.go = "ignasio_1";
		break;
		
		case "ignasio_1":
            dialog.text = "Oh, I know who you are! Monseniour "+GetFullName(pchar)+"! Rumors of your resources and patrons had been reaching me throughout the Archipelago. I believe my offer will be interesting for you.";
			link.l1 = "What offer?";
			link.l1.go = "ignasio_2";
		break;
		
		case "ignasio_2":
            dialog.text = "Let's go to a tavern for a drink. I will tell you everything. It's not a street talk.";
			link.l1 = "Very well... Let's go!";
			link.l1.go = "ignasio_3";
		break;
		
		case "ignasio_3":
            DialogExit();
			FreeSitLocator("Bridgetown_tavern", "sit_front2");
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload4_back", "Bridgetown_tavern", "sit", "sit_front2", "Mtraxx_IgnasioInTavern", -1);
		break;
		
		case "ignasio_4":
			LAi_SetSitType(pchar);
            dialog.text = "A round, captain?";
			link.l1 = "Sure!";
			link.l1.go = "ignasio_5";
		break;
		
		case "ignasio_5":
			LAi_Fade("", "");
            dialog.text = "Heh, they actually don't mix rum with water here...";
			link.l1 = "And don't treat customers with rotten fish, yes-yes. So what's the deal?";
			link.l1.go = "ignasio_6";
		break;
		
		case "ignasio_6":
            dialog.text = "I like your straightforwardness, monsieur. Tell me, are you aware of the trade war between England and Netherlands?";
			link.l1 = "I am. Had a pleasure to take a part in it.";
			link.l1.go = "ignasio_7";
		break;
		
		case "ignasio_7":
            dialog.text = "No need to explain it. Being an English privateer I am fighting this war on their side. You are a freelancer mostly. Which makes you indifferent in what side to fight against...";
			link.l1 = "Almost. I don't cross France, I am sorry.";
			link.l1.go = "ignasio_8";
		break;
		
		case "ignasio_8":
            dialog.text = "By all means, captain! So, straight to the point: there is a small inhabited island between Curacao and Trinidad, it's not on the maps. Since recent times, I'd say very recent time, the Dutch have started to use it as stop to resupply and repair. It seems that they believe only they are aware of this island. Wrong. He-he\nCouple of days ago a silver caravan was hit by a storm and now the Dutch are repairing their vessels on this island. The flagship lost her mast, so it will take some time to repair it. The Dutch are busy with repairing and the crews are mostly dispersed across the island...";
			link.l1 = "And then suddenly we are coming to save the day?";
			link.l1.go = "ignasio_9";
		break;
		
		case "ignasio_9":
            dialog.text = "Exactly, captain. I can't do this alone but with you - it's a total different business. Will you risk it? I have a great ship, the crew is great and I have a good amount of experience. Your skills... are commendable too.";
			link.l1 = "How much time do we have?";
			link.l1.go = "ignasio_10";
		break;
		
		case "ignasio_10":
            dialog.text = "Plenty if we are not wasting it and getting underway immediately.";
			link.l1 = "Then let's resupply with munitions and weapons, captain Ignacio Marco, and let's set sails. What's the island's exact coordinates?";
			link.l1.go = "ignasio_11";
		break;
		
		case "ignasio_11":
            dialog.text = "12'40 North, 64'11 West. Got it?";
			if (CheckAttribute(pchar, "questTemp.HWIC.Isladecoche")) link.l1 = "Ha! Deja vu... Got it.";
			else link.l1 = "Got it.";
			link.l1.go = "ignasio_12";
		break;
		
		case "ignasio_12":
            dialog.text = "Heading to the 'Torero'. Will be waiting for you, captain!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_IgnasioAddMarko");
		break;
		
		case "ignasio_13":
            dialog.text = "Hell of a fight right, captain? Now the pleasant part: let's split our shares. A half goes to me and my men.";
			link.l1 = "Let's do it...";
			link.l1.go = "ignasio_14";
		break;
		
		case "ignasio_14":
			LAi_Fade("", "");
			WaitDate("", 0, 0, 0, 3, 10); 
			pchar.questTemp.Mtraxx.Silver = GetSquadronGoods(pchar, GOOD_SILVER)-sti(pchar.questTemp.Mtraxx.Silver);
			pchar.questTemp.Mtraxx.Mahogany = GetSquadronGoods(pchar, GOOD_MAHOGANY)-sti(pchar.questTemp.Mtraxx.Mahogany);
			if (sti(pchar.questTemp.Mtraxx.Silver) < 100)
			{
				dialog.text = "Captain, what is it? Where is our silver? Did you sink our prize?";
				if (sti(pchar.questTemp.Mtraxx.Mahogany) < 200) 
				{
					link.l1 = "Hm...";
					link.l1.go = "ignasio_15_1";
				}
				else
				{
					link.l1 = "Silver was wasted somehow although we god some redwood. Let's split it.";
					link.l1.go = "ignasio_15_11";
				}
				break;
			}
			if (sti(pchar.questTemp.Mtraxx.Silver) < 300 && sti(pchar.questTemp.Mtraxx.Silver) > 100)
			{
				dialog.text = "Hm.. This is poor. I thought there'd be much more.";
				link.l1 = "We've got what we've got.";
				link.l1.go = "ignasio_15_2";
				break;
			}
			if (sti(pchar.questTemp.Mtraxx.Silver) < 700 && sti(pchar.questTemp.Mtraxx.Silver) > 300)
			{
				dialog.text = "Not bad, not bad. Although, I thought there'd be more.";
				link.l1 = "We've got what we've got.";
				link.l1.go = "ignasio_15_3";
				break;
			}
            dialog.text = "Nicely done, Monseniour. This is a fine prize...";
			link.l1 = "Can't disagree with you on this, captain.";
			link.l1.go = "ignasio_15_4";
		break;
		
		case "ignasio_15_1":
			dialog.text = "Looks like you have a serious trouble with your head. We are leaving! Boys!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_IgnasioEscape");
		break;
		
		case "ignasio_15_11":
			RemoveCharacterGoods(pchar, GOOD_MAHOGANY, makeint(sti(pchar.questTemp.Mtraxx.Mahogany)/2));
			dialog.text = "At least we get something from this... Boys! Let's go!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_IgnasioEscape");
		break;
		
		case "ignasio_15_2":
			RemoveCharacterGoods(pchar, GOOD_SILVER, makeint(sti(pchar.questTemp.Mtraxx.Silver)/2));
			RemoveCharacterGoods(pchar, GOOD_MAHOGANY, makeint(sti(pchar.questTemp.Mtraxx.Mahogany)/2));
            dialog.text = "It's something. Let's part our ways.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_IgnasioEscape");
		break;
		
		case "ignasio_15_3":
            RemoveCharacterGoods(pchar, GOOD_SILVER, makeint(sti(pchar.questTemp.Mtraxx.Silver)/2));
			RemoveCharacterGoods(pchar, GOOD_MAHOGANY, makeint(sti(pchar.questTemp.Mtraxx.Mahogany)/2));
            dialog.text = "It's something. Let's part our ways. It's a success after all, heh!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_IgnasioEscape");
		break;
		
		case "ignasio_15_4":
			RemoveCharacterGoods(pchar, GOOD_SILVER, makeint(sti(pchar.questTemp.Mtraxx.Silver)/2));
			RemoveCharacterGoods(pchar, GOOD_MAHOGANY, makeint(sti(pchar.questTemp.Mtraxx.Mahogany)/2));
            dialog.text = "We had a very profitable meeting. Perhaps, it's not the last time we do business together, captain!";
			link.l1 = "Call me if you find more fat traders, he-he!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_IgnasioEscape");
		break;
		
		case "ignasio_boarding":
            dialog.text = "I assume this is not an accident, captain?";
			link.l1 = "You are too smart to not seeing it. You owe me for the setup. You know what I am talking about. Also, you owe me for setting up my friend Jean Picard. He was sold to plantation after your scheme... You lost Ignacio. I am going to hang you but you can ease your punishment...";
			link.l1.go = "ignasio_boarding_1";
		break;
		
		case "ignasio_boarding_1":
            dialog.text = "I am wondering even - what is it I could do to make you pity me?";
			link.l1 = "I need information. I will put you into my cargo hold where we will talk about your agenda in Havana...";
			link.l1.go = "ignasio_boarding_2";
		break;
		
		case "ignasio_boarding_2":
            dialog.text = RandSwear()+" Didn't see it coming! Don't even think of it. Barbason will learn about my treason in no time. You better don't know what he does to people who betrayed him. I saw it.";
			link.l1 = "So being hanged is a better option?";
			link.l1.go = "ignasio_boarding_3";
		break;
		
		case "ignasio_boarding_3":
            dialog.text = "I'd rather die in combat!";
			link.l1 = "...";
			link.l1.go = "ignasio_boarding_4";
		break;
		
		case "ignasio_boarding_4":
            DialogExit();
			LAi_SetCurHPMax(npchar);
			LAi_GetCharacterMaxEnergy(npchar);
			QuestAboardCabinDialogFree();
			LAi_group_SetRelation(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, true);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "spy_sailor":
            dialog.text = "Captain! Captain! Hurry! The Spanish military squadron is after us!";
			link.l1 = RandSwear()+"I expected this... Same story happened to Picard. Did you see how many of them out there?";
			link.l1.go = "spy_sailor_1";
		break;
		
		case "spy_sailor_1":
            dialog.text = "Yes, captain. Three ships. Their flagship is a heavy galleon, the other two are a corvette and a xebec.";
			link.l1 = "All aboard. We might still be in position to flee.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_IgnasioOurEscape");
		break;
		
		// индей-кариб в гроте Порто-Белло
		case "grot_canib":
            dialog.text = "Haya! Damn yalanaui come our forest! Kill him! Haya!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_WolfreekGrotFight");
		break;
		
		// бандит у пещеры Панамы
		case "cave_bandit":
            dialog.text = "Hey! What the hell are you doing here? A-ah, stealing others' belongings? Well, cutie, you are screwed!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_WolfreekCaveFight");
		break;
		
		case "carpenter":
            dialog.text = "Hey! Everyone hold right there! Or I will take you all with a grapeshot volley! "+RandSwear()+"";
			link.l1 = "We are not moving anywhere right now. But listen to this pal - no way you'll kill all of in one shot. Some of us will cut you to pieces while you are reloading. We'd better have a talk right now.";
			link.l1.go = "carpenter_1";
		break;
		
		case "carpenter_1":
            dialog.text = "Are you in charge here? Answer me!";
			link.l1 = "I am captain "+GetFullName(pchar)+". And you must be Red Wolf's second in command while he is away from here, right?";
			link.l1.go = "carpenter_2";
		break;
		
		case "carpenter_2":
            dialog.text = "What are you doing here captain "+GetFullName(pchar)+"? We don't invite guests to this place!";
			link.l1 = "What's your name? I want to know who am I talking to.";
			link.l1.go = "carpenter_3";
		break;
		
		case "carpenter_3":
            dialog.text = "Name's Rodgar Janssen.";
			link.l1 = "I can see that you, Rodgar Janssen, is in dark here. You don't have a captain any more. And your corvette is gone too. The 'Freyja' was bombed the hell out by the Spanish not far from Hispaniola. Her crew was slain...";
			link.l1.go = "carpenter_4";
		break;
		
		case "carpenter_4":
            dialog.text = RandSwear()+" Wulfric... Ar-gh how can I know your are telling the truth?";
			link.l1 = "I have your ex-captain's log! We've got a few items from Freyja's wreckage. Thanks to the log I have found this island and this... gordes of yours.";
			link.l1.go = "carpenter_5";
		break;
		
		case "carpenter_5":
            dialog.text = "Heh! You still owe me an answer: why are you here on this unknown land?";
			link.l1 = "I'm not gonna lie, pal. They say Red Wolf possessed quite a fortune. I am here to find it since no such treasure was found on his ship. I believe they should belong to good people, they have no use to Wulfric now anyway.";
			link.l1.go = "carpenter_6";
		break;
		
		case "carpenter_6":
            dialog.text = "Ha! Buddy, I am going to disappoint you: neither me nor anyone else of the crew ever seen Wolf's treasures. It's was too risky to ask him.";
			link.l1 = "Then I should search for them in you village. Will you take away your gun or should I start storming the village? You have no chance Rodgar. I will bring guns and more men if I need.";
			link.l1.go = "carpenter_7";
		break;
		
		case "carpenter_7":
            dialog.text = "Before we die we will take along a plenty of you bastards to hell! Maybe you too!";
			link.l1 = "Are you sure? You have no captain, no ship and no one will come to save you. Even if I just leave, you all will starve to death soon enough!";
			link.l1.go = "carpenter_8";
		break;
		
		case "carpenter_8":
            dialog.text = "Have any suggestions?";
			link.l1 = "Yes, I do. Take a step back from the gun and keep your men in check. I swear I will not do any harm to you. If you want you can join my crew or we will take you to civilization.";
			link.l1.go = "carpenter_9";
		break;
		
		case "carpenter_9":
            dialog.text = "Swear it before your men loud and clear!";
			link.l1 = "I swear! You have my word: you and your men will not be harmed.";
			link.l1.go = "carpenter_10";
		break;
		
		case "carpenter_10":
            DialogExit();
			npchar.dialog.currentnode = "carpenter_11";
			LAi_SetActorType(npchar);
			LAi_ActorDialog(npchar, pchar, "", -1, 0);
			for (i=1; i<=2; i++) // 
			{
				sld = CharacterFromID("Islamona_fort_pirate_"+i);
				LAi_SetActorType(sld);
				LAi_ActorDialog(sld, pchar, "", -1, 0);
			}
		break;
		
		case "carpenter_11":
            dialog.text = "I hope you will keep your word, captain.";
			link.l1 = "I always do. How many of you are left?";
			link.l1.go = "carpenter_12";
		break;
		
		case "carpenter_12":
            dialog.text = "You see us all. Three. The rest died in the jungles attacking you. I told them not to but they didn't listen...";
			link.l1 = "I see...";
			link.l1.go = "carpenter_13";
		break;
		
		case "carpenter_13":
            dialog.text = "Food was running out. We started hunting parrots. The 'Freyja' was absent for too long. We had suspicions and they came true.";
			link.l1 = "Thank God for me deciding to go treasure hunting. Where might he stashed them?";
			link.l1.go = "carpenter_14";
		break;
		
		case "carpenter_14":
            dialog.text = "I told you already: no one has ever seen them. Wulfric was careful with his share, never let it go to waste. He was fair with us but everyone who tried to find his stash gone missing. You are free to search the village as you wish.";
			link.l1 = "That's my plan. Where is Red Wolf's house?";
			link.l1.go = "carpenter_15";
		break;
		
		case "carpenter_15":
            dialog.text = "Left from the fence. The only double-floored building we have here.";
			link.l1 = "Good. What's you occupation?";
			link.l1.go = "carpenter_16";
		break;
		
		case "carpenter_16":
            dialog.text = "I am a carpenter and these two are my assistances. We used to repair and crook the 'Freyja' before. We could be of use in your crew.";
			link.l1 = "I see. You are in, we'll talk details later. Get this gun from the entrance. Rodgar don't leave the village while I am searching for the stash.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_WolfreekInFort");
		break;
		
		case "carpenter_17":
            dialog.text = "Orders, captain?";
			if (CheckAttribute(pchar, "questTemp.Mtraxx.WolfreekGord"))
			{
				link.l1 = "Yes. Your captain's treasures have been found. He did hide them well but I have outsmarted him!";
				link.l1.go = "carpenter_18";
				break;
			}
			link.l2 = "Rodgar, my ship needs for repairs. Are you and your guys ready?";
			link.l2.go = "repair";
			link.l3 = "Rodgar, I'd like to leave one of my ships here.";
			if (CheckAttribute(npchar, "portman.info")) link.l3.go = "shipstock";
			else link.l3.go = "shipstock_info";
			if (sti(npchar.portman > 0))
			{
				link.l4 = "Rodgar, I'd like to take one of my ships back.";
				link.l4.go = "shipstockreturn";
			}
			if (!CheckAttribute(npchar, "storadge"))
			{
				link.l5 = "Look, is there any empty building I could use as a storehouse?";
				link.l5.go = "storadge";
			}
			if (CheckAttribute(npchar, "storadge"))
			{
				link.l5 = "Rodgar, I want to see a storehouse.";
				link.l5.go = "storadge_3";
			}
			link.l99 = "Nothing yet...";
			link.l99.go = "carpenter_exit";
		break;
		
		case "carpenter_exit":
            DialogExit();
			npchar.dialog.currentnode = "carpenter_17";
		break;
		
		case "carpenter_18":
            dialog.text = "Congratulations cap. What do we do next? Are we leaving?";
			link.l1 = "Have you been here for long?";
			link.l1.go = "carpenter_19";
		break;
		
		case "carpenter_19":
            dialog.text = "For too long. It's been a year since Wulfric put me in charge here.";
			link.l1 = "I have decided that this secret base is too good to be wasted. The village is mine now. I can leave you and your men here if you want. Rum, provisions, medicine - all yours.";
			link.l1.go = "carpenter_20";
		break;
		
		case "carpenter_20":
            dialog.text = "That would be great captain. I got used to life on this beach, this island.";
			link.l1 = "Splendid. By the way, what's the island's name?";
			link.l1.go = "carpenter_21";
		break;
		
		case "carpenter_21":
            dialog.text = "Isla Mona.";
			link.l1 = "Isla Mona... Perhaps one day we will build more houses and structures... But later. Right now you will keep the same role here but under different captain.";
			link.l1.go = "carpenter_22";
		break;
		
		case "carpenter_22":
            dialog.text = "Deal. You just take care of yourself captain and don't forget supplying us with provisions.";
			link.l1 = "Sure thing Rodgar. Good luck, I should sail to La Vega.";
			link.l1.go = "carpenter_exit";
			npchar.portman = 0;
			AddDialogExitQuestFunction("Mtraxx_WolfreekComplete");
		break;
		
		case "repair":
			if (CheckSelfRepairConditions())
			{
				dialog.text = "By all means, captain! All we need are planks and sailcloth. Go to you landing location and order the crew to prepare materials.";
				link.l1 = "On my way. Do it fast.";
				link.l1.go = "repair_1";
			}
			else
			{
				dialog.text = "Sure, captain, but as I see your ship doesn't need a repair now.";
				link.l1 = "Just asked...";
				link.l1.go = "carpenter_exit";
			}
		break;
		
		case "repair_1":
            DialogExit();
			npchar.dialog.currentnode = "carpenter_17";
			chrDisableReloadToLocation = true;
			DoQuestReloadToLocation(Pchar.location.from_sea, "reload", "sea", "Mtraxx_WolfreekRepairShore");
		break;
		
		case "shipstock_info":
			npchar.portman.info = "true";
            dialog.text = "It's possible, captain. A few limitations though: there are only two places on this island suitable for this.  Also you can't leave here anyone but a single officer to each ship. We simply don't have enough resources to keep crews here. Yet. Finally, there is no room for first ranked ships.";
			link.l1 = "Got it. I am ready to leave a ship here.";
			link.l1.go = "shipstock";
			link.l2 = "Very well, I will get her ready.";
			link.l2.go = "carpenter_exit";
		break;
		
		case "shipstock":
			if (sti(npchar.portman) == 2)
			{
				dialog.text = "Captain, there is no more room for another ship.";
				link.l1 = "Right...";
				link.l1.go = "carpenter_exit";
				break;
			}
			if (GetCompanionQuantity(pchar) < 2)
			{
				dialog.text = "Captain, you have only one ship.";
				link.l1 = "Hm... I should drink less...";
				link.l1.go = "carpenter_exit";
				break;
			}
            dialog.text = "What ship do you want to leave here?";
			for(i=1; i<COMPANION_MAX; i++)
			{
				int cn = GetCompanionIndex(PChar, i);
				if( cn > 0 )
				{
					ref chref = GetCharacter(cn);
					if (!GetRemovable(chref)) continue;

					attrL = "l"+i;
					Link.(attrL) = XI_ConvertString(RealShips[sti(chref.Ship.Type)].BaseName) + " '" + chref.Ship.Name + "'.";
					Link.(attrL).go = "ShipStockMan_" + i;
				}
			}
			Link.l9 = "Wait, I have changed my mind.";
			Link.l9.go = "carpenter_exit";
		break;
		
		case "ShipStockMan_1":
            NPChar.ShipToStoreIdx = GetCompanionIndex(PChar, 1);
			dialog.text = "Let's see...";
			Link.l1 = "Very good.";
			Link.l1.go = "ShipStock_2";
			Link.l2 = "Wait, I have changed my mind.";
			Link.l2.go = "carpenter_exit";
		break;

		case "ShipStockMan_2":
            NPChar.ShipToStoreIdx = GetCompanionIndex(PChar, 2);
			dialog.text = "Let's see...";
			Link.l1 = "Very good.";
			Link.l1.go = "ShipStock_2";
			Link.l2 = "Wait, I have changed my mind.";
			Link.l2.go = "carpenter_exit";
		break;

		case "ShipStockMan_3":
            NPChar.ShipToStoreIdx = GetCompanionIndex(PChar, 3);
			dialog.text = "Let's see...";
			Link.l1 = "Very good.";
			Link.l1.go = "ShipStock_2";
			Link.l2 = "Wait, I have changed my mind.";
			Link.l2.go = "carpenter_exit";
		break;
		
		case "ShipStockMan_4":
            NPChar.ShipToStoreIdx = GetCompanionIndex(PChar, 4);
			dialog.text = "Let's see...";
			Link.l1 = "Very good.";
			Link.l1.go = "ShipStock_2";
			Link.l2 = "Wait, I have changed my mind.";
			Link.l2.go = "carpenter_exit";
		break;
		
		case "ShipStock_2":
            chref = GetCharacter(sti(NPChar.ShipToStoreIdx));
			if (sti(RealShips[sti(chref.Ship.Type)].Class) < 2)
			{
				dialog.text = "Captain, first ranks are too big for our shores. I've told you that already.";
				Link.l1 = "Right.";
				Link.l1.go = "carpenter_exit";
				break;
			}
			if (sti(chref.Ship.Crew.Quantity) > 0)
			{
				dialog.text = "Captain, take all of her crew to your flagship except an officer.";
				Link.l1 = "Ah, right! I'll do that!";
				Link.l1.go = "carpenter_exit";
				break;
			}
			dialog.Text = "So, we are to keep here a"+XI_ConvertString(RealShips[sti(chref.Ship.Type)].BaseName+"Acc")+" named '"+chref.Ship.Name+"'. Right?";
			Link.l1 = "Right.";
			Link.l1.go = "ShipStock_3";
			Link.l2 = "Wait, I have changed my mind.";
			Link.l2.go = "carpenter_exit";
		break;
		
		case "ShipStock_3":
            chref = GetCharacter(sti(NPChar.ShipToStoreIdx));
            chref.ShipInStockMan = NPChar.id;
			chref.ShipInStockMan.MoneyForShip = 0;
            chref.ShipInStockMan.AltDate = GetQuestBookDataDigit();
            SaveCurrentNpcQuestDateParam(chref, "ShipInStockMan.Date");
            RemoveCharacterCompanion(pchar, chref);
            chref.location = "";
            chref.location.group = "";
            chref.location.locator = "";
            npchar.portman = sti(npchar.portman)+1;
            pchar.ShipInStock = sti(pchar.ShipInStock)+1;
			dialog.text = "Very well, we'll see her delivered to a safe harbor.";
			Link.l1 = "Excellent!";
			Link.l1.go = "carpenter_exit";
		break;
		
		case "shipstockreturn":
            if (GetCompanionQuantity(pchar) < COMPANION_MAX)
			{
				dialog.text = "Which ship are you going to take, captain?";
				cn = 1;
				for (i=1; i<MAX_CHARACTERS; i++)
				{
					makeref(chref, Characters[i]);
					if (CheckAttribute(chref, "ShipInStockMan"))
					{
						if (chref.ShipInStockMan == NPChar.id)
						{
							attrL = "l"+cn;
							Link.(attrL)    = XI_ConvertString(RealShips[sti(chref.Ship.Type)].BaseName) + " '" + chref.Ship.Name + "'.";
							Link.(attrL).go = "ShipStockManBack_" + i;
							cn++;
						}
					}
				}
				link.l9 = "Wait, I have changed my mind.";
				link.l9.go = "carpenter_exit";
			}
			else
			{
				dialog.text = "Captain, you don't have room in your squadron for one more ship.";
				link.l1 = "Hm. You're right.";
				link.l1.go = "carpenter_exit";
			}
		break;
		
		 case "ShipStockManBack":
            chref = GetCharacter(sti(NPChar.ShipToStoreIdx));
			dialog.Text = "Are you taking her?";
			link.l1 = "Yes.";
			link.l1.go = "ShipStockManBack2";
			link.l2 = "Wait, I have changed my mind.";
			link.l2.go = "carpenter_exit";
		break;
		
		case "ShipStockManBack2":
			DialogExit();
			npchar.dialog.currentnode = "carpenter_17";
			chref = GetCharacter(sti(NPChar.ShipToStoreIdx));
			DeleteAttribute(chref, "ShipInStockMan");
			SetCompanionIndex(pchar, -1, sti(NPChar.ShipToStoreIdx));
			npchar.portman = sti(npchar.portman)-1;
            pchar.ShipInStock = sti(pchar.ShipInStock)-1;
		break;
		
		case "storadge":
            dialog.text = "Here? No. But Wulfric had built a huge barn not far from here. A solid building, well covered with palm leaves and tarred sailcloth. It has a lock and a room for a cargo enough to fill a dozen of trade ships\nIt's empty now, but I have a key if you want to examine it. Shall we?";
			link.l1 = "Sure! By the way: what of rats on this island? Will they spoil my goods in the barn?";
			link.l1.go = "storadge_1";
		break;
		
		case "storadge_1":
            dialog.text = "Wolf had it covered it too: he brought two cats here from the mainland. He forgot about males though, so these crazy furred bitches make lousy sounds every time their season comes. But they hunt mice and rats pretty well. Don't worry about it, captain. Your goods will be safe from rats and winds.";
			link.l1 = "Great! I will make a use of it. Keep your key to yourself and show me this storehouse.";
			link.l1.go = "storadge_2";
		break;
		
		case "storadge_2":
			DialogExit();
			npchar.dialog.currentnode = "carpenter_17";
			npchar.city = "islamona";
			npchar.Storage.Activate = true;
			SaveCurrentNpcQuestDateParam(npchar, "Storage.Date");
			npchar.MoneyForStorage = 0;
			npchar.storadge = true;
			LaunchStorage(29);
		break;
		
		case "storadge_3":
            dialog.text = "Follow me, captain.";
			link.l1 = "...";
			link.l1.go = "storadge_4";
		break;
		
		case "storadge_4":
            DialogExit();
			npchar.dialog.currentnode = "carpenter_17";
			LaunchStorage(29);
		break;
		
		// Мирабель
		case "mirabelle":
			PlaySound("VOICE\Russian\Girl_Q.wav");
            dialog.text = "Ah...";
			link.l1 = "Well now... A girl... What are you doing here?";
			link.l1.go = "mirabelle_1";
		break;
		
		case "mirabelle_1":
			PlaySound("VOICE\Russian\Girl_Q.wav");
            dialog.text = "Oh...";
			link.l1 = "...";
			link.l1.go = "mirabelle_2";
		break;
		
		case "mirabelle_2":
            DialogExit();
			npchar.dialog.currentnode = "mirabelle_3";
			sld = characterFromId("Mrt_Rocur");
			sld.dialog.currentnode = "rocur_74";
			ChangeCharacterAddressGroup(sld, "LaVega_TwoFloorHouse", "goto", "goto8");
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.5);
		break;
		
		case "mirabelle_3":
			PlaySound("VOICE\Russian\other\RapersGirl-01.wav");
            dialog.text = "Senor! Senor "+pchar.name+" don't kill me please! I beg you! I will say Tyrex nothing! I hate that beast! I beg you, por favor!";
			link.l1 = "...";
			link.l1.go = "mirabelle_4";
		break;
		
		case "mirabelle_4":
			DialogExit();
            npchar.dialog.currentnode = "mirabelle_5";
			sld = characterFromId("Mrt_Rocur");
			sld.dialog.currentnode = "rocur_80";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;
		
		case "mirabelle_5":
            dialog.text = "";
			link.l1 = "Hey lass! Heard that? You will go with me or this tough bastard will kill you.";
			link.l1.go = "mirabelle_6";
		break;
		
		case "mirabelle_6":
            dialog.text = "I will go with you, senor, wherever you are taking me!";
			link.l1 = "Good then. Keep your mouth shut, I will kill you if you start yelling or calling for Tyrex. What's your name?";
			link.l1.go = "mirabelle_7";
		break;
		
		case "mirabelle_7":
            dialog.text = "Mirabelle...";
			link.l1 = "Behave well Mirabelle and this will end nice for you. Keep close to me and don't make any sound.";
			link.l1.go = "mirabelle_8";
		break;
		
		case "mirabelle_8":
            dialog.text = "I swear I won't, senor.";
			link.l1 = "...";
			link.l1.go = "mirabelle_9";
		break;
		
		case "mirabelle_9":
            DialogExit();
            npchar.dialog.currentnode = "mirabelle_10";
			LAi_SetImmortal(npchar, true);
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			sld = characterFromId("Mrt_Rocur");
			sld.dialog.currentnode = "rocur_85";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
			pchar.questTemp.Mtraxx.Mirabella = "true";
		break;
		
		case "mirabelle_10":
			PlaySound("VOICE\Russian\Girl_Q.wav");
            dialog.text = "Senor?";
			link.l1 = "You did well girl, I like you for that. Now we are going to my ship where you will be put in a small cabin for some time. I am sorry but I don't want you to run to Tyrex and tell him anything.";
			link.l1.go = "mirabelle_11";
		break;
		
		case "mirabelle_11":
            dialog.text = "No way senor! I would never go to Tyrex, este bastardo! I hate him! Lo odio!!!";
			link.l1 = "Woah! What did he do to you?";
			link.l1.go = "mirabelle_12";
		break;
		
		case "mirabelle_12":
            dialog.text = "A lot... I hate him, I hate him!";
			link.l1 = "I see. Once we arrive you will be living in quite a fancy house. Alone. Keep me in good mood and no one will ever hurt you. Go to a longboat now... Mirabelle.";
			link.l1.go = "mirabelle_13";
		break;
		
		case "mirabelle_13":
            DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "sea", "none", "", "", "OpenTheDoors", 20.0);
			pchar.quest.mtraxx_pasq_mirabella.win_condition.l1 = "location";
			pchar.quest.mtraxx_pasq_mirabella.win_condition.l1.location = "Shore75";
			pchar.quest.mtraxx_pasq_mirabella.function = "Mtraxx_PasqualeMirabella";
			pchar.quest.mtraxx_pasq_mirabella1.win_condition.l1 = "location";
			pchar.quest.mtraxx_pasq_mirabella1.win_condition.l1.location = "Shore77";
			pchar.quest.mtraxx_pasq_mirabella1.function = "Mtraxx_PasqualeMirabella";
			AddPassenger(pchar, npchar, false);//добавить пассажира
			SetCharacterRemovable(npchar, false);
			SetFunctionTimerCondition("Mtraxx_MirabellaSailOver", 0, 0, 30, false); // месяц на доплыть до Исла Моны
		break;
		
		case "mirabelle_14":
            dialog.text = "Have we arrived senor?";
			link.l1 = "Yes, sweetheart. This is my village and my house. I own the place. I am a rare guest though - too much work to do out there. Make sure you keep my house clean while you live in it or I will give you to Rodgar and his carpenters. Feel free to walk around the island, there is no escape from it anyway.";
			link.l1.go = "mirabelle_15";
		break;
		
		case "mirabelle_15":
            dialog.text = "I have nowhere to leave senor "+pchar.name+". I have no family and no use. I might end up in a brothel again.";
			link.l1 = "There a hatch to a dungeon, stay away from it. It's dark and dangerous down there.";
			link.l1.go = "mirabelle_16";
		break;
		
		case "mirabelle_16":
            dialog.text = "I will stay away senor.";
			link.l1 = "There is also a bedroom upstairs. Follow me.";
			link.l1.go = "mirabelle_17";
		break;
		
		case "mirabelle_17":
            DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			pchar.quest.mtraxx_islamona_mirabella1.win_condition.l1 = "location";
			pchar.quest.mtraxx_islamona_mirabella1.win_condition.l1.location = "IslaMona_TwoFloorRoom";
			pchar.quest.mtraxx_islamona_mirabella1.function = "Mtraxx_PasqualeMirabellaRoom";
		break;
		
		case "mirabelle_18":
            dialog.text = "";
			link.l1 = "There. I have shown you the whole house. It is not worse than Tyrex's place you lived in before. I hope you like it.";
			link.l1.go = "mirabelle_19";
		break;
		
		case "mirabelle_19":
            dialog.text = "Yes senor. You have a great house. I promise to look after it well in you absence.";
			link.l1 = "I am glad you are so cooperative towards me. I hope it's for real. Be honest with me or you'll regret being not. Be a good girl and don't make me sad and I will be good for you. Charlie Prince honors his word!";
			link.l1.go = "mirabelle_20";
		break;
		
		case "mirabelle_20":
            dialog.text = "Thank you senor "+pchar.name+". Thank you for not allowing your... compa?ero to kill me. You are very kind.";
			link.l1 = "Heh, you are a funny little sweetheart... A pretty face too despite the mark. Hope the rest is in place too.. Now show your captain what you can do.";
			link.l1.go = "mirabelle_21";
		break;
		
		case "mirabelle_21":
            DialogExit();
			pchar.GenQuest.FrameLockEsc = true;
			bDisableCharacterMenu = true;
			ResetSound();
			WaitDate("", 0, 0, 0, 2, 30);
			SetLaunchFrameFormParam("", "", 0, 12);
			SetLaunchFrameFormPic("loading\inside\censored1.tga");
			PlayStereoSound("sex\sex10.wav");
			LaunchFrameForm();
			AddCharacterHealth(pchar, 5);
			LAi_SetCurHPMax(pchar);
			DoQuestFunctionDelay("Mtraxx_PasqualeMirabellaSex", 12.0);
			ChangeCharacterAddressGroup(pchar, "IslaMona_TwoFloorRoom", "goto", "goto2");
			ChangeCharacterAddressGroup(npchar, "IslaMona_TwoFloorRoom", "goto", "goto4");
		break;
		
		case "mirabelle_22":
            dialog.text = "Senor "+pchar.name+" you are so sweet... You are a real gentleman. Must have arrived from Europe not long ago.";
			link.l1 = "Do flatter me you little liar, I am buying it. Heh, your are good, Mirabelle! Tyrex has a good taste, he-he...";
			link.l1.go = "mirabelle_23";
		break;
		
		case "mirabelle_23":
            dialog.text = "I don't. You are a gentleman. But you are pretending to be rude for some reason. Mh-m-m... I liked it very much. I'll be waiting to see you again.";
			link.l1 = "Ah yes, a gentleman... a gentleman of fortune, ha-ha! Very well sweetheart, settle down here for now.";
			link.l1.go = "mirabelle_24";
		break;
		
		case "mirabelle_24":
            dialog.text = "Goodbye, senor.";
			link.l1 = "...";
			link.l1.go = "mirabelle_25";
		break;
		
		case "mirabelle_25":
            DialogExit();
			npchar.InOurHouse = true;
		    npchar.dialog.currentnode = "mirabelle_26";
		    chrDisableReloadToLocation = false;
			pchar.quest.mtraxx_mirabella_setlife.win_condition.l1 = "MapEnter";
			pchar.quest.mtraxx_mirabella_setlife.function = "Mtraxx_MirabellaSetLife";
			bQuestDisableMapEnter = false;//открыть карту
			DeleteAttribute(pchar, "GenQuest.MapClosedNoBattle");
		break;
		
		case "mirabelle_26":
            dialog.text = TimeGreeting()+", senor "+pchar.name+"! I am very glad to see you. How are you?";
			link.l1 = RandSwear()+""+RandPhraseSimple("Shiver My Timbers, shiver My Soul!","Oh, better far to live and die. Under the brave black flag I fly!")+" Charlie Prince is fine, sweetheart.";
			link.l1.go = "mirabelle_26x";
			if (!CheckAttribute(npchar, "sex_date") || GetNpcQuestPastDayParam(npchar, "sex_date") >= 1)
			{
				link.l2 = "Sweetheart, how about you make a captain a bit happier?";
				link.l2.go = "mirabelle_sex";
			}
		break;
		
		case "mirabelle_26x":
            DialogExit();
		    npchar.dialog.currentnode = "mirabelle_26";
		break;
		
		case "mirabelle_sex":
            dialog.text = "Anything for you, senor!";
			link.l1 = RandPhraseSimple("Ready the grappels!","Board 'em!");
			link.l1.go = "mirabelle_sex_1";
		break;
		
		case "mirabelle_sex_1":
            DialogExit();
			LAi_SetActorType(npchar);
		    npchar.dialog.currentnode = "mirabelle_27";
			if (pchar.location == "IslaMona_TwoFloorRoom") DoQuestFunctionDelay("Mtraxx_MirabellaSex", 1.5);
			else DoQuestReloadToLocation("IslaMona_TwoFloorRoom", "goto", "goto2", "Mtraxx_MirabellaSex");
		break;
		
		case "mirabelle_27":
            dialog.text = "Mh-m... Senor you are a magician! I hope you liked it too? I was doing my best.";
			link.l1 = "You did great sweetheart.";
			link.l1.go = "mirabelle_28";
		break;
		
		case "mirabelle_28":
            DialogExit();
		    npchar.dialog.currentnode = "mirabelle_26";
			LAi_SetStayType(npchar);
			SaveCurrentNpcQuestDateParam(npchar, "sex_date");
		break;
		
		case "mirabelle_sleep":
            dialog.text = "This not true, not true! Senor "+pchar.name+" is good and kind! He is only pretending to be an evil pirate! You are, senor "+pchar.name+"?";
			link.l1 = "";
			link.l1.go = "exit";
			AddDialogExitQuest("Mtraxx_RetributionSleep6_1");
		break;
		
		case "mirabelle_29":
            dialog.text = TimeGreeting()+", senor "+pchar.name+"! I am very happy to see you. How are you doing? Why are you so sad?";
			link.l1 = "Hello, Mirabelle. Why do you think I am sad?";
			link.l1.go = "mirabelle_30";
		break;
		
		case "mirabelle_30":
            dialog.text = "Well, I can see that. You are not the usual you. Do you want me to cheer you up? Come on!";
			link.l1 = "Wait. I want to talk with you.";
			link.l1.go = "mirabelle_31";
		break;
		
		case "mirabelle_31":
            dialog.text = "Of course, senor, whatever you say. I am all ears";
			link.l1 = "Tell me how did you get into the hand of Tyrex and why there is mark of thief on your forehead. Don't be afraid, I will never hurt you. I only need to hear your story.";
			link.l1.go = "mirabelle_32";
		break;
		
		case "mirabelle_32":
            dialog.text = "Ah, senor! My story is brief and boring. I was born in Puerto Rico, my father was a white gentleman, my mother - an Indian. I've never seen my pa. When I was a kid I was a servant and when grew up I had make a folly to steal my master's jewelry. I have never had my own and I wanted so badly to try wearing it just for a day. Of course, they had found out everything\nThere was a trial, I was whipped, branded and put in jail in San Juan. I did stay there for too long: one of officers made a deal with a chief and I was sold to a brothel of Philipsburg for handful of golden doubloons\nI had spent there a year or so. One unfortunate day we were paid a visit by Tyrex and his lousy friend with glasses.";
			link.l1 = "Pasquale Lavoisier...";
			link.l1.go = "mirabelle_33";
		break;
		
		case "mirabelle_33":
            dialog.text = "Yes-yes, his name was senor Pasquale Lavoisier. I have no clue what did they see in me, but shortly after their visit, Tyrex had bought me from Madame Johanna and put me inside a locked house full of chests and goods. It was the worst time in my life, even worse then days spent in San Juan prison. Tyrex had been visiting me every day unless he was in the sea and I could breath freely, but every time senor Lavoisier came I... I.... It was the worst of all. Senor "+pchar.name+", please, may I not speak of this?\nI don't know how long I was there. And then you had come and taken me out from that awful house. I was very lucky that you were so kind.";
			link.l1 = "Kind? Mirabelle, but I did the very same thing to you: I took you to an island and locked inside a house.";
			link.l1.go = "mirabelle_34";
		break;
		
		case "mirabelle_34":
            dialog.text = "No, senor, it is not true. Am I locked in here? I take a walk around the island every day. It is a wonderful and peaceful place. Do I have to do a lot of house work? No, and I get used to it anyway. And you are not like Tyrex, not like his merchant friend. I am always happy to see you, you are so young and handsome. And a gentleman too...";
			link.l1 = "Mirabelle, do you want me to take you to any city? I will give you enough money. Where to? Choose any colony.";
			link.l1.go = "mirabelle_35";
		break;
		
		case "mirabelle_35":
            dialog.text = "Senor, do you want to shoo me away? Please don't, te lo ruego!";
			link.l1 = "Well... I thought you'd want to return back to normal life...";
			link.l1.go = "mirabelle_36";
		break;
		
		case "mirabelle_36":
            dialog.text = "Ah, senor "+pchar.name+", and what is for me there? How will I marry being a marked half-blood? I wi;; be sold to a brothel again, no doubt in that. Please, don't send me away. I like this place, I haven't felt so peaceful and secure anywhere but here. Rodgar and his boys are good guys, we are friends and they don't hurt me. I like spending time with them and it's fun! Sometimes we make a fire on a beach and I dance samba. Please, senor, I will do anything for you, just let me stay!";
			link.l1 = "Fine, Mirabelle, stay here since you like this place that much. Just know that you are not a prisoner here, you can always ask me to take you away from here.";
			link.l1.go = "mirabelle_37";
		break;
		
		case "mirabelle_37":
            dialog.text = "My dear good senor, thank you! I will never ask you for anything like this - I want to stay a prisoner of this island... and your prisoner, tee-hee... You are so kind but sad today! You don't sing and swear as you usually do.";
			link.l1 = "No more singing and swearing, Mirabelle. I am sorry for being rude with you.";
			link.l1.go = "mirabelle_38";
		break;
		
		case "mirabelle_38":
            dialog.text = "Will you be stern and strict just like an English lord?.. Ah... senor, do you want me to dance and sing tonight? Just for you. Now go with me! There is no a better cure for sadness than love. I have missed you.";
			link.l1 = "Good point, my dear girl... Let's go.";
			link.l1.go = "mirabelle_39";
		break;
		
		case "mirabelle_39":
            DialogExit();
			LAi_SetActorType(npchar);
		    npchar.dialog.currentnode = "mirabelle_40";
			if (pchar.location == "IslaMona_TwoFloorRoom") DoQuestFunctionDelay("Mtraxx_MirabellaSex", 1.5);
			else DoQuestReloadToLocation("IslaMona_TwoFloorRoom", "goto", "goto2", "Mtraxx_MirabellaSex");
		break;
		
		case "mirabelle_40":
            dialog.text = "Ah, senor "+pchar.name+", you were so gentle today, mh-m... Are you pleased with me, my dear captain?";
			link.l1 = "Everything was delightful, Mirabelle.";
			link.l1.go = "mirabelle_41";
		break;
		
		case "mirabelle_41":
            DialogExit();
		    npchar.dialog.currentnode = "mirabelle_42";
			LAi_SetStayType(npchar);
			SaveCurrentNpcQuestDateParam(npchar, "sex_date");
		break;
		
		case "mirabelle_42":
			bool bMary = GetCharacterIndex("Mary") != -1 && CheckAttribute(pchar, "questTemp.LSC.Mary_officer");
			bool bHelena = GetCharacterIndex("Helena") != -1 && CheckAttribute(pchar, "questTemp.Saga.Helena_officer");
            dialog.text = TimeGreeting()+", senor "+pchar.name+"! I am so happy to see you! How are you doing?";
			link.l1 = ""+LinkRandPhrase("Glad to see you too, my girl.", "Hi, Mirabelle. You are always the same - joyful and beautiful, what a pleasant sight.","Hello, pretty one. You look stunning!")+"I am doing just fine. Hope you too.";
			link.l1.go = "mirabelle_42x";
			if (!bMary && !bHelena) // прогона 3
			{
				if (!CheckAttribute(npchar, "sex_date") || GetNpcQuestPastDayParam(npchar, "sex_date") >= 1)
				{
					link.l2 = "Mirabelle, I have already missed you and your weasel. Will you kiss your sea wolf?";
					link.l2.go = "mirabelle_43";
				}
			}
		break;
		
		case "mirabelle_42x":
            DialogExit();
		    npchar.dialog.currentnode = "mirabelle_42";
		break;
		
		case "mirabelle_43":
            dialog.text = "Ah, my sweet captain, I have missed you too! Come on, I am at the edge!";
			link.l1 = "...";
			link.l1.go = "mirabelle_39";
		break;
		
		// губернатор Картахены
		case "CartahenaMayor":
            dialog.text = "Fucking ladrones! Whatever, our courier is already on the way to Porto Bello. Soon our squadron will arrive and...";
			link.l1 = TimeGreeting()+", your Highness. Pleasure to see you in good state. I hope you will keep it after we leave. If I were you I wouldn't count on the squadron, plus we are not staying here for more than three days. I bet you understand that noble dons of Porto Bello won't arrive here to help you that soon. Let's go straight to business, shall we?";
			link.l1.go = "CartahenaMayor_1";
		break;
		
		case "CartahenaMayor_1":
            dialog.text = "Talking business already? Look at the window! Look what your cutthroats are doing in the streets and in houses!";
			link.l1 = "Oh, your Highness, this is nothing compared to what they will be doing if you aren't cooperative enough. I hope you understand who are these men...";
			link.l1.go = "CartahenaMayor_2";
		break;
		
		case "CartahenaMayor_2":
            dialog.text = "I know what an arrant evil man and pirate Charley Prince is capable of! I know who is his boss! In time, we will burn out your bandit lair on Hispaniola! How much?";
			link.l1 = "Don't waste words, my dear governor. You'd better get me 250 000 pesos.";
			link.l1.go = "CartahenaMayor_3";
		break;
		
		case "CartahenaMayor_3":
            dialog.text = "What?! Your insolence is limitless! This is a robbery!";
			link.l1 = "It is robbery, of course. What else could it be? Gather your elites, your merchants and traders, gather gold into a big chest because otherwise... I will make it much worse for you and your people.";
			link.l1.go = "CartahenaMayor_4";
		break;
		
		case "CartahenaMayor_4":
            dialog.text = "Fucking pirate! Bastardo! Heretic! Vete a la mierda!";
			link.l1 = "Because of your dirty tongue I increase the ransom up to 300 000.";
			link.l1.go = "CartahenaMayor_5";
		break;
		
		case "CartahenaMayor_5":
            dialog.text = "QUEMAR EN EL INFIERNO, HIJO DE PUTA!!!";
			link.l1 = "350 000. Do you want to keep on?";
			link.l1.go = "CartahenaMayor_6";
		break;
		
		case "CartahenaMayor_6":
            dialog.text = "There are no such money in the city!";
			link.l1 = "You lie. It just can't be. We are able to gather at least a million here, but I am afraid we don't have enough time to do it. Therefore I will be kind and generous. You know the sum. Go get it.";
			link.l1.go = "CartahenaMayor_7";
		break;
		
		case "CartahenaMayor_7":
            dialog.text = "I am telling you again, Charley Prince: there is no such money in Cartagena!";
			link.l1 = "Oh... Boring. Cutlass! Search around and bring here everyone you will find. Search well! And we will wait here for now, you grace...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_CartahenaInResidence");
		break;
		
		case "CartahenaMayor_8":
            dialog.text = "";
			link.l1 = "Hey, senor 'Stubborn'! Haven't you changed your mind concerning the money gathering in good city Cartagena? Oh, why are you so pale?! Are you well? Should I bring you some water?";
			link.l1.go = "CartahenaMayor_9";
		break;
		
		case "CartahenaMayor_9":
            dialog.text = "";
			link.l1 = "As far I as I understand, these two ladies are you wife and daughter, am I right? The third girl looks like a servant, you seem to be not giving a shit about her so we won't do her any harm, but these two beauties may get some attention from my brother in arms, senor Cutlass. He seems to like them, senor. So what? Are you going to handle the ransom?";
			link.l1.go = "CartahenaMayor_10";
		break;
		
		case "CartahenaMayor_10":
            dialog.text = "I... I will need time.";
			link.l1 = "Aha! Now you are talking! So who is the bastardo here? You didn't give a fuck about my men terrorizing your citizens but your two women are a completely different matter, right? Did you dare to fucking bargain with me, jerk? I will show what it means to cross Charley Prince!";
			link.l1.go = "CartahenaMayor_10x";
		break;
		
		case "CartahenaMayor_10x":
            dialog.text = "";
			link.l1 = "Go and gather the fucking ransom. 350 000 and not a peso less. You have one day. We'll stay here to drink some wine and mingle with these sweet women... Be swift, maldito, or me and my friend Cutlass may fall in love with your beauties and then you will have to ransom them too. March!";
			link.l1.go = "CartahenaMayor_11";
		break;
		
		case "CartahenaMayor_11":
            DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "Mtraxx_CartahenaResidenceWait", 5.0);
		break;
		
		case "CartahenaMayor_12":
			AddMoneyToCharacter(pchar, 350000);
            dialog.text = "Take your blood money, Charley Prince!";
			link.l1 = "Did you gather a ransom? Splendid! But you are late for an hour, my dear governor. This extra hour gave me and the Cutlass an understanding that our lives will be way too boring without these beauties who were so kind and talkative with us...";
			link.l1.go = "CartahenaMayor_13";
		break;
		
		case "CartahenaMayor_13":
            dialog.text = "You... you!";
			link.l1 = "Ah, you are too nervous because of your work, my friend. I was joking... Cutlass! Follow me!";
			link.l1.go = "CartahenaMayor_14";
		break;
		
		case "CartahenaMayor_14":
            DialogExit();
			AddQuestRecord("Roger_9", "7");
			AddDialogExitQuestFunction("Mtraxx_CartahenaToFort");
		break;
		
		// Камилла
		case "camilla":
			PlaySound("VOICE\Russian\hambit\Girls_3.wav");
            dialog.text = "Oh, this is the Charley Prince, the famous pirate, the terror of the Spanish South Main!";
			link.l1 = RandSwear()+"Heh, I had no idea I am that popular in Tortuga. What's your name, sweet girl?";
			link.l1.go = "camilla_1";
		break;
		
		case "camilla_1":
            dialog.text = "My name is Camilla.";
			link.l1 = "Camilla... I used to know a girl with the same name back in France. It was so long ago!";
			link.l1.go = "camilla_2";
		break;
		
		case "camilla_2":
			PlaySound("ambient\tavern\orijka_003.wav");
            dialog.text = "";
			link.l1 = "(puking) ... fuck... I am sorry princess, but Prince is kinda drunk tonight. So... hum.. why did you come to me?";
			link.l1.go = "camilla_3";
		break;
		
		case "camilla_3":
            dialog.text = "For various reasons. Or maybe for no reason.";
			link.l1 = "God, this is too complicated. You seem to be a mystery, lass.";
			link.l1.go = "camilla_4";
		break;
		
		case "camilla_4":
            dialog.text = "Every lass must have a mystery.";
			link.l1 = "Seems like you want me to solve this mystery. No? I am a master of solving girls' mysteries, I swear it! Should we go to a tavern and drink some wine? I will get you the best treat!";
			link.l1.go = "camilla_5";
		break;
		
		case "camilla_5":
            dialog.text = "M-m-m... I like tough guys. But I won't be drinking wine downstairs close to drunk low lives. Get us a room, we will drink and talk there.";
			link.l1 = RandSwear()+"You are hot! Follow me!";
			link.l1.go = "camilla_6";
		break;
		
		case "camilla_6":
            DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			pchar.quest.mtraxx_retribution_tavern.win_condition.l1 = "locator";
			pchar.quest.mtraxx_retribution_tavern.win_condition.l1.location = "Tortuga_town";
			pchar.quest.mtraxx_retribution_tavern.win_condition.l1.locator_group = "reload";
			pchar.quest.mtraxx_retribution_tavern.win_condition.l1.locator = "reload4_back";
			pchar.quest.mtraxx_retribution_tavern.function = "Mtraxx_RetributionToTavern";
		break;
		
		case "camilla_7":
			PlaySound("VOICE\Russian\hambit\Gr_officiant_1.wav");
            dialog.text = "Come on... Pour it up, don't make lady waiting!";
			link.l1 = "Sure, my sweetie!";
			link.l1.go = "camilla_8";
		break;
		
		case "camilla_8":
			LAi_Fade("", "");
			PlaySound("ambient\tavern\krujki_005.wav");
			PlaySound("ambient\tavern\naliv_003.wav");
			PlaySound("ambient\tavern\glotok_001.wav");
			WaitDate("", 0, 0, 0, 1, 5);
            dialog.text = "M-m-m... Just to think of it, I am here all alone with Charley Prince, drinking an excellent wine...";
			link.l1 = "You are going to enjoy this ride with me, oh I promise! Charlie Prince is gentle and kind to ladies who submit themselves to him. Will you submit, baby?";
			link.l1.go = "camilla_9";
		break;
		
		case "camilla_9":
            dialog.text = "Tee-hee... Of course, sweetie! Your promises sound so tempting, you know...";
			link.l1 = "No wasting time then, beauty?";
			link.l1.go = "camilla_10";
		break;
		
		case "camilla_10":
            dialog.text = "Oh I love real men!..";
			link.l1 = "...";
			link.l1.go = "camilla_11";
		break;
		
		case "camilla_11":
            DialogExit();
			pchar.GenQuest.FrameLockEsc = true;
			bDisableCharacterMenu = true;
			ResetSound();
			WaitDate("", 0, 0, 0, 2, 30);
			SetLaunchFrameFormParam("", "", 0, 5.1);
			SetLaunchFrameFormPic("loading\inside\censored1.tga");
			PlayStereoSound("sex\sex2.wav");
			LaunchFrameForm();
			AddCharacterHealth(pchar, 3);
			LAi_SetCurHPMax(pchar);
			DoQuestCheckDelay("Mtraxx_RetributionRoomSex", 5.1);
		break;
		
		case "camilla_12":
            dialog.text = "M-m-m...";
			link.l1 = "Did you like it, my precious?";
			link.l1.go = "camilla_13";
		break;
		
		case "camilla_13":
            dialog.text = "Sure thing! Hope you liked it too.";
			link.l1 = "Heh! Even my head is crystal clear now!";
			link.l1.go = "camilla_14";
		break;
		
		case "camilla_14":
            dialog.text = "Prince, I have an ask for you. Will you help me?";
			link.l1 = "I will get a star from the sky for you, ha-ha! Go ahead.";
			link.l1.go = "camilla_15";
		break;
		
		case "camilla_15":
            dialog.text = "I need to get to La Vega, to see Tyrex. I am afraid of him, but you do business together. Please get me to him.";
			link.l1 = "Look at this! And why would such a sweet, fragile girl want to see the Code's Keeper?";
			link.l1.go = "camilla_16";
		break;
		
		case "camilla_16":
            dialog.text = "Sweet, fragile girl would like to make some coin. My late father and brothers didn't live me much cash. Tyrex can fix this.";
			link.l1 = "Oh really? And how? Want a lead to a Spanish galleon? Ha-ha!";
			link.l1.go = "camilla_17";
		break;
		
		case "camilla_17":
            dialog.text = "Plundering caravans and cities is a tough guys' business, just like you, honey. I have another business for Marcus. He buys and sells information, right? I have something... No chance I am can use it myself, but he could. I will be happy enough just to get a small interest out of it.";
			link.l1 = "Interesting! Tell me more.";
			link.l1.go = "camilla_18";
		break;
		
		case "camilla_18":
            dialog.text = "Hm...";
			link.l1 = "Oh, come on. Consider me a right hand of Tyrex and I did a lot of digging for him by now, trust me. If your information is worth it - I will buy it myself.";
			link.l1.go = "camilla_19";
		break;
		
		case "camilla_19":
            dialog.text = "Fine. I will tell you more, but no details until I receive the money. Deal, honey?";
			link.l1 = "Sure thing, pretty one. Charley Prince doesn't fuck his partners up, you know what I mean, ha-ha-ha! Go ahead, I am all ears.";
			link.l1.go = "camilla_20";
		break;
		
		case "camilla_20":
            dialog.text = "My pa was a skipper on a merchant schooner. One day he somehow learnt about an old Spanish mining settlement lying deep in Main's jungles. Twenty years ago it was destroyed by an earthquake. Miners abandoned it and secret passages were forgotten. Except one. My father found it\nHe took my brothers and a guide there and they had found the place filled with gold mined and smelted years ago. A lot of gold. One million pesos at least. Father had returned to a ship so he could get men to transport the gold but he was shocked to find out that she was gone. Seems like his first mate had started a mutiny and they left him and my brothers on deserted shores\nThey built a long boat and sailed along the shore desperately looking for an inhabited place, but... (sobs) a storm hit them and my (sobs) brothers died. Father made it alive but he didn't live long after he returned home - deaths of my brothers were slowly killing him day by day. Before he passed away, he'd made a map and gave it to me\nHe told me that when I got married, my husband would go there, get the gold and we shall live our lives like kings. Sure we will, but I will not let my man go inside those cursed jungles. Not again! One million pesos, my father said, but it's just not my league. Such prize can get only the best and toughest of men - men like Marcus Tyrex. This is why I'm going to meet him.";
			link.l1 = "How much do you want for the map?";
			link.l1.go = "camilla_21";
		break;
		
		case "camilla_21":
            dialog.text = "Two hundred golden doubloons. It's nothing compared to the prize. Tyrex will agree to this, I am sure. He is as rich as Crassus.";
			link.l1 = "Heh! And what if this is all a trickery?";
			link.l1.go = "camilla_22";
		break;
		
		case "camilla_22":
            dialog.text = "Do I look suicidal? Trying to cross Tyrex? Sweetie, better live in poverty than don't live at all. So will you take me there? Please...";
			link.l1 = "Where is the map? Will you show me it?";
			link.l1.go = "camilla_23";
		break;
		
		case "camilla_23":
            dialog.text = "My priest keep it safe. I will show it to you for 200 doubloons.";
			link.l1 = "Very well! I am buying it. Strangers in taverns sometimes ask much more for garbage.";
			link.l1.go = "camilla_24";
		break;
		
		case "camilla_24":
            dialog.text = "Are you? Is it true, honey? I am so happy I am not going to La Vega! To be honest, I fear Marcus. I fear you too, by the way, but a bit less.";
			link.l1 = "Such sweet little girl doesn't need to fear me. Where should I bring the money?";
			link.l1.go = "camilla_25";
		break;
		
		case "camilla_25":
            dialog.text = "Let's make a deal: find me in our church any day from ten o'clock in the morning till one o'clock in the afternoon. I will be feeling much safer under protection of this sacred place. We will conclude our deal there.";
			link.l1 = "Do you still fear me? Ha-ha! Don't, Camilla, I won't cheat on you. Charley Prince won't do such a low thing for pathetic two hundred doubloons.";
			link.l1.go = "camilla_26";
		break;
		
		case "camilla_26":
            dialog.text = "Wonderful. Very well then, honey, I will be waiting for you. Thank you for an amazing time we had together tonight! I am so happy that we have met!";
			link.l1 = "See you soon, pretty one.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_RetributionOutRoom");
		break;
		
		case "camilla_27":
			PlaySound("VOICE\Russian\hambit\Girls_3.wav");
            dialog.text = "So? Did you bring the money, sweetie?";
			if (GetCharacterItem(pchar, "gold_dublon") >= 200)
			{
				link.l1 = "Yes. Have your gold and give me the map.";
				link.l1.go = "camilla_28";
			}
			else
			{
				link.l1 = "I am right after it.";
				link.l1.go = "camilla_27x";
			}
		break;
		
		case "camilla_27x":
            DialogExit();
			npchar.dialog.currentnode = "camilla_27";
		break;
		
		case "camilla_28":
			RemoveItems(pchar, "gold_dublon", 200);
			Log_Info("You have given 200 doubloons");
			GiveItem2Character(pchar, "mapEnrico"); 
            dialog.text = "Thank you, honey... Here, have it. I swear by my father's memory - this map is not a fake.";
			link.l1 = "Good, sweetie. How about we celebrate our deal just like the last time?";
			link.l1.go = "camilla_29";
		break;
		
		case "camilla_29":
            dialog.text = "I'd like to, Prince, but I am preparing myself for a confession before my priest, therefore I am obliged to stay far from any temptations right now. Let's do it next time.";
			link.l1 = "Uh, you are teasing me, lass. Fine! No time to waste: we are about to set sails. I swear I will double your interest if your daddies map will indeed lead me to the gold.";
			link.l1.go = "camilla_30";
		break;
		
		case "camilla_30":
            dialog.text = "You are so generous, darling. Bon voyage!";
			link.l1 = "Yo-ho-ho!";
			link.l1.go = "camilla_31";
		break;
		
		case "camilla_31":
            DialogExit();
			npchar.lifeday = 0;
			LAi_CharacterDisableDialog(npchar);
			AddQuestRecord("Roger_10", "2");
			bQuestDisableMapEnter = false;//открыть карту
			DeleteAttribute(pchar, "GenQuest.MapClosedNoBattle");
			pchar.quest.mtraxx_retribution_carataska.win_condition.l1 = "location";
			pchar.quest.mtraxx_retribution_carataska.win_condition.l1.location = "shore10";
			pchar.quest.mtraxx_retribution_carataska.function = "Mtraxx_RetributionCarataska";
			pchar.questTemp.Mtraxx.Retribution = "carataska";
		break;
		
		case "camilla_sleep":
            dialog.text = "Your bastards slain my father and my brothers. Your attack on Cartagena has brought grief to every family there. I hope you are scared now, scared as much as were citizens of Cartagena when your brutes were enjoying themselves on the streets and in houses. You will burn in hell, Charley Prince.";
			link.l1 = "";
			link.l1.go = "exit";
			AddDialogExitQuest("Mtraxx_RetributionSleep4");
		break;
		
		// дон Энрико - народный мститель
		case "enrico":
			PlaySound("VOICE\Russian\OliverTrast01.wav");
            dialog.text = "So few things in this world joy me as much as watching rats in the box tearing each other!\nOnly the strongest and the most disgusting rat survives. Then all you have to do is to squeeze it...";
			link.l1 = "Argh! Who are you?!";
			link.l1.go = "enrico_1";
		break;
		
		case "enrico_1":
            dialog.text = "I am don Enrico. English scum call me Fox, Dutch call me Vos, French call me Renaud. But I prefer my Spanish home nickname - Zorro. I punish the evil which torture and terrorize the common folk, the least protected part of the people\nThis trial today will judge four pirates of Marcus Tyrex: Bold Jeffry, Pelly the Cutlass, Luke the Leprechaun and Charley Prince - these bandits are responsible for a massacre in Merida and Cartagena. The last bastard called Handsome Jean didn't show up here, he must be the smartest of you.";
			link.l1 = "What?!";
			link.l1.go = "enrico_2";
		break;
		
		case "enrico_2":
            dialog.text = "You are a scumbag, Charley Prince, but you are not an idiot. I have figured it out already, I think. It's a trap for you all set by me with a help of fake maps, documents, words and promises of gold and silver. I have lured you all into these dungeons where you destroyed each other driven by your disgusting traits: envy, greed, meanness and unscrupulousness. It was a truly just nemesis!";
			link.l1 = "Camilla... I should had known there was something wrong about this girl!";
			link.l1.go = "enrico_3";
		break;
		
		case "enrico_3":
            dialog.text = "A girl named Camilla had been living a peaceful life in Cartagena with her father and brothers, she was about to get married when you and your devils attacked the city. Your pirates had slain everyone close to her, so she swore to do whatever it takes to avenge them. It was a tough role to play for her. She even had to sleep with a bastard responsible for the deaths of her family. I fear to imagine what were she feeling during the act\nThe poor girl had spent days in church praying for forgiveness. She donated the blood doubloons you gave her to the victims who suffered most from your attack. She is now in a monastery, poor soul. You have broken her life, scum! Think about it! Think of how many Camillas, Isabelas, Rositas you had raped and made widows! How many Juans, Carloses, Pedros you bastards had slain and tortured!\nRemember Merida! Remember how you promised to the head of the town not to set it on fire and then burnt it to the ground!";
			link.l1 = "I never meant to do it! When I had left the residence the fire was already everywhere. I didn't order this...";
			link.l1.go = "enrico_4";
		break;
		
		case "enrico_4":
            dialog.text = "You are responsible for the acts of your pirates. Dead men are hanging on your neck and soon they will drag you to hell!";
			link.l1 = "Come here! Huh? Fight me! This is what you want, right?!";
			link.l1.go = "enrico_5";
		break;
		
		case "enrico_5":
            dialog.text = "No, Charley Prince. Don't grab for your weapon, it's pointless... I could kill you easily, however quick death is not enough for a bastard like you. You will stay in this dungeon forever. The door you used to enter here is blocked by a stone outside, the door behind me will be blocked too, besides there are also sturdy bars protecting it. This is it, there is no way out except for these two doors\nThere is water below, so you will have enough time to think about your deeds. All alone here, in the darkness, perhaps, you will repent what you have done before you starve to the death or go insane\nOne last thing - the treasure below is a fake. Golden ingots are nothing but a colored lead. Doubloons are real though, but there are only few of them enough to cover rocks inside chests. A worthy end for pirates, huh? You killed each other for a fake treasure, Prince. Farewell now. Pray for your sinner soul, Charley Prince, if you still remember how...";
			link.l1 = "Wait!..";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_RetributionEnricoGo");
		break;
		
		case "mishelle_sleep":
            dialog.text = "Tell me, brother - how did you turn into such abomination? When I told you to get familiar with pirates, I didn't mean burning cities, killing innocent civilians and torturing women. Even a war can be fought with honor and dignity\nYou are a shame of our family. It's good our father is not here: he would have died of shame knowing his son has become a pirate and bandit!";
			link.l1 = "";
			link.l1.go = "exit";
			AddDialogExitQuest("Mtraxx_RetributionSleep5");
		break;
		
		case "mishelle_sleep_1":
            dialog.text = "Brother! Brother!\nCan you hear me?\nThere is a passage behind one of two doors. The door can be opened. A key is close to you!\nFind it on the stairs. On the stairs!..";
			link.l1 = "";
			link.l1.go = "exit";
			AddDialogExitQuest("Mtraxx_RetributionSleep7");
		break;
		
		case "terrax_sleep":
            dialog.text = "Ha-ha-ha, hello there my brave cutthroat! Why are you so sad? The sea, gold, rum and women - what else do you lack? Remember our first meeting? I told you back then - I need men who don't fear to smell a gunpowder or to bleed red rivers. You have over exceed my every hope! You have become a real pirate, Charley Prince! Ha-ha-ha!";
			link.l1 = "";
			link.l1.go = "terrax_sleep_1";
		break;
		
		case "terrax_sleep_1":
            dialog.text = "A real fucking pirate! Ah-ah-ha-ha!";
			link.l1 = "";
			link.l1.go = "terrax_sleep_2";
		break;
		
		case "terrax_sleep_2":
			Mtraxx_RetributionSleepSkeletons();
            dialog.text = "Ua-ha-ha-ha-ha-ha!!!";
			link.l1 = "";
			link.l1.go = "exit";
			AddDialogExitQuest("Mtraxx_RetributionSleep6");
		break;
	}
} 
