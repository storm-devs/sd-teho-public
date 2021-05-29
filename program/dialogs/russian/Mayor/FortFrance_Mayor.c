// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("What do you want? Ask away.", "I am listening to you, what's the question?"), "It is the second time you are trying to ask...", "It is the third time you are again trying to ask...",
                          "When is it going to end?! I am a busy man, working on the colony's matters and you are still trying to ask something!", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("I have changed my mind...", "Not now. Wrong place and time."), "True... But later, not now...",
                      "I'll ask... But a bit later...", "I am sorry, " + GetAddress_FormToNPC(NPChar) + "...", npchar, Dialog.CurrentNode);			  
			link.l1.go = "exit";
			//--> Бремя гасконца
			if (CheckAttribute(pchar, "questTemp.Sharlie.Junglejew"))
			{
				link.l1 = "Monsieur, I have found a bandit corpse in the jungle. He has been killed by the Indians. There were earrings on his body, looks like they were brought here from Europe. Maybe they belonged to one of the nobles in your town?";
                link.l1.go = "Sharlie_junglejew";
			}
			//<-- Бремя гасконца
			// Jason НСО
			if (CheckAttribute(pchar, "questTemp.Patria") && pchar.questTemp.Patria == "epizode_9_continue" && !CheckAttribute(npchar, "quest.frigate"))
			{
				link.l1 = "I arrived by the order of Governor General Philippe de Poincy to take command of your armed frigate.";
                link.l1.go = "patria";
			}
			if (CheckAttribute(npchar, "quest.frigate.wait") && GetCompanionQuantity(pchar) < 5)
			{
				link.l1 = "I'm ready to take the frigate into the squadron.";
                link.l1.go = "patria_2";
			}
			// Jason Дороже золота
			if (CheckAttribute(pchar, "questTemp.GoldenGirl") && pchar.questTemp.GoldenGirl == "message")
			{
				link.l1 = "I arrived at your invitation, monsignor...";
                link.l1.go = "goldengirl";
			}
			if (CheckAttribute(pchar, "questTemp.GoldenGirl") && pchar.questTemp.GoldenGirl == "girl_prisoner")
			{
				link.l1 = "There was a misfortune, monsignor!";
                link.l1.go = "goldengirl_10";
			}
		break;
		
		case "Sharlie_junglejew":
			dialog.text = "Let's see what you have... Incredible! It's just incredible, Charles! These are my wife's earrings. I had gifted them to her before I left Europe and came to colonies. They disappeared a few months ago under mysterious circumstances. I knew they were stolen!\nCharles, I'm very glad that you came directly to me, and didn't sell the thing that I hold so dear to the merchants. I'll repay you your favour. As I heard, you are going to buy a ship? Since you decided to partake in seafaring, you will undoubtedly need a map of our archipelago. Here, take it. I'm sure it will come in handy!";
			link.l1 = "Thank you, your Grace!";
			link.l1.go = "Sharlie_junglejew_1";
		break;
		
		case "Sharlie_junglejew_1":
			DialogExit();
			PlaySound("interface\important_item.wav");
			RemoveItems(pchar, "jewelry25", 1);
			GiveItem2Character(pchar, "map_bad"); 
			AddQuestRecord("SharlieE", "2");
			CloseQuestHeader("SharlieE");
			DeleteAttribute(pchar, "questTemp.Sharlie.Junglejew");
		break;
		
		// Jason НСО
		case "patria":
			if (GetCompanionQuantity(pchar) > 4)
			{
				dialog.text = "The ship is ready, but you don't have a free spot for it in your squadron. Captain, reduce your squadron and return, then I will immediately give you the frigate..";
				link.l1 = "Fine.";
				link.l1.go = "patria_1";
			}
			else
			{
				dialog.text = "Yes, of course, the ship is ready to sail. Its captain is aware and will follow all of your orders.";
				link.l1 = "Then we're setting out. Goodbye, Your Grace.";
				link.l1.go = "patria_3";
			}
		break;
		
		case "patria_1":
			DialogExit();
			npchar.quest.frigate.wait = "true";
		break;
		
		case "patria_2":
			DeleteAttribute(npchar, "quest.frigate.wait");
			dialog.text = "Excellent. Prepare to greet your new ship. Its captain is aware and will follow all of your orders.";
			link.l1 = "Then we're setting out. Goodbye, Your Grace.";
			link.l1.go = "patria_3";
		break;
		
		case "patria_3":
			DialogExit();
			npchar.quest.frigate = "true";
			Patria_BastionFrigateMrt(); // присоединяем фрегат
		break;
		
		// Jason Дороже золота
		case "goldengirl":
			dialog.text = "Captain Charles de Maure, at last! It's been a while since I've been waiting for you so eagerly! Please, come in, join me.";
			link.l1 = "Good day to you too, Your Excellence. There is always a reason behind such politeness of yours. What is it this time? Pirate, Spanish, Redskin cannibals?";
			link.l1.go = "goldengirl_1";
		break;
		
		case "goldengirl_1":
			dialog.text = "Don't go all ironic over me, Captain. It's not my fault that we always get in trouble, you and I. But please, don't be worry, there will no shooting this time… not likely.";
			link.l1 = "You intrigue me, go on. How can I be of help?";
			link.l1.go = "goldengirl_2";
		break;
		
		case "goldengirl_2":
			dialog.text = "Ever heard of Madame Botot's fine establishment? During the siege our… our brothel got burnt to ashes. One day a certain lady volunteered to rebuild it.";
			link.l1 = "A fire in a brothel and without me? By the way, I got shot by the Spanish too that day.";
			link.l1.go = "goldengirl_3";
		break;
		
		case "goldengirl_3":
			dialog.text = "Damn it, Charles what is wrong with you today? Your wit is inappropriate! Even though it is not a matter of State, it is still an important matter, for me, personally! I need your help! For God's sake, pull yourself together and hear me out!";
			link.l1 = "Forgive me, Your Excellence. I am feeling a huge relief, tis all. To be honest, I got tired of all this constant battling and fighting. I expected you to start dragging me intro another circle of violence. Please go on. Never heard of this Madame Botot.";
			link.l1.go = "goldengirl_4";
		break;
		
		case "goldengirl_4":
			dialog.text = "Right, so this honorable dame elevated the establishment to a totally new level. It is a place of high and noble society now, not a rat hole it used to be. A place of distinguished vices, expensive wine and unlimited gambling. You will see everything for yourself!";
			link.l1 = "Your Excellence, I am not a prude and your description was very colorful, but why are you telling me this?";
			link.l1.go = "goldengirl_5";
		break;
		
		case "goldengirl_5":
			dialog.text = "Because you are in the list, why else?! See, I am a bit guilty before marquise and promised to introduce you to her on one of her parties tomorrow night. Juliana doesn’t do this often so please be kindly to join us. No fighting, shooting and chasing this time, I promise. Everything will courteous and dignified: wine, gorgeous women, cards and other of nobility's enjoyments.";
			link.l1 = "Cards and whores. It’s been a while since the last time, in a different life. I still don't follow you though. Why me?";
			link.l1.go = "goldengirl_6";
		break;
		
		case "goldengirl_6":
			dialog.text = "Are you deaf? Juliana Botot, she… collects bright and famous faces. They make her parties special and fresh. You have made quite a name for yourself, marquise must had waited a long time to get you as her guest. My misstep gave her an opportunity and I won't make it if she will refuse to receive me again. This is all I am getting if I won't deliver you to her!";
			link.l1 = "Your Excellence, you are a handsome widower and governor… Why do you even care about some courtesan's opinion about you? It is them who should search for your good will, not the other way around.";
			link.l1.go = "goldengirl_7";
		break;
		
		case "goldengirl_7":
			dialog.text = "Marquise Botot is under protection of Count Henry de Levi-Vantadur - who, by His Majesty's grace, is the head of New France states of North America. Trust me, Charles, no one here wants to cross him.";
			link.l1 = "You almost had me here - I thought that all this is only about lust and amour. Now I see it was politics all along. Trivial, but expected. Very well, I will help you out. It will be sweet to return to the days of my youth just for one night.";
			link.l1.go = "goldengirl_8";
		break;
		
		case "goldengirl_8":
			dialog.text = "Captain, you are a seasoned man no doubt, however don't try to pretend to be an old man. It's not only about politics. I value Juliana's presence and I am grateful for your help. It is important for me personally, truly. Come to marquise Botot's place after tomorrow dusk. I promise you that politics will not spoil you the night.";
			link.l1 = "Wine, cards, women. Just like the good old times. Farewell, Your Excellence!";
			link.l1.go = "goldengirl_9";
		break;
		
		case "goldengirl_9":
			DialogExit();
			bDisableFastReload = true;//закрыть переход
			pchar.quest.GoldenGirl_bronca.win_condition.l1 = "location";
			pchar.quest.GoldenGirl_bronca.win_condition.l1.location = "FortFrance_town";
			pchar.quest.GoldenGirl_bronca.function = "GoldenGirl_GirlAngry";
			SetFunctionTimerCondition("GoldenGirl_TimeOver", 0, 0, 2, false); // таймер до завтрашней полуночи
			SetFunctionTimerCondition("GoldenGirl_BrothelDoor", 0, 0, 1, false); // таймер на закрытие дверей борделя
			pchar.quest.GoldenGirl_eventstart.win_condition.l1 = "Timer";
			pchar.quest.GoldenGirl_eventstart.win_condition.l1.date.hour  = 21.00;
			pchar.quest.GoldenGirl_eventstart.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.GoldenGirl_eventstart.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.GoldenGirl_eventstart.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.GoldenGirl_eventstart.win_condition.l2 = "location";
			pchar.quest.GoldenGirl_eventstart.win_condition.l2.location = "FortFrance_SecBrRoom"; // возможно закрыть бордель и вход только через боковую комнату
			pchar.quest.GoldenGirl_eventstart.function = "GoldenGirl_Party"; // таймер на начало вечеринки
			pchar.questTemp.GoldenGirl = "brothel";
			AddQuestRecord("GoldenGirl", "2");
		break;
		
		case "goldengirl_10":
			dialog.text = "Charles, what happened, you look like hell!";
			link.l1 = "Angerran, fucking, Chievous, Excellency. He stole his frigate last night. Put my prize crew to death and set sail in the mist.";
			link.l1.go = "goldengirl_11";
		break;
		
		case "goldengirl_11":
			dialog.text = "It's an unpleasant turn of events, I understand, but trust me - such outcome is quite satisfactory. You are not in dire need of ships and men, while de Levi Vantadur will pay a significant sum to conceal the truth behind a certain recent duel. Or he will remember our role in concealing it for free which is also worth quite a lot. De Chievous did dishonest things twice but he is far away now while we still have decent cards against him.";
			link.l1 = "Thrice, your Excellency. Angerran admitted his cheating during our card game. But he won't pay me off with money, if that's what you meant. He crossed the line. There was a certain person on that ship this morning… she... is very dear to me! I won't let the bastard to do her any wrong! You hear that, Jaques, I will not!";
			link.l1.go = "goldengirl_12";
		break;
		
		case "goldengirl_12":
			dialog.text = "I think I know who you are talking about - I recall seeing you with some… girl, dressed like a man and armed to the teeth like a pirate. Charles, don't be an idiot! You got lucky, you avoided huge troubles and what, you are trying to drag yourself into them again? Let it go. De Chievous is on the run - thank God! And regarding your... girlfriend in arms - take your friend's advice - go see Julianna and forget about all this.";
			link.l1 = "Out of the question, Excellency. Some things are just beyond your understanding, alright? Now tell me everything you know about the bastard. Where could he go from St. Pierre? I don't try to dissuade me again - I fucked with the Dutch Company, fucked with pirate barons, governor-general's even with Holy Inquisition! I am not an easy man to scare of. I will get her back whatever the cost!";
			link.l1.go = "goldengirl_13";
		break;
		
		case "goldengirl_13":
			dialog.text = "Charles, had you ever put a thought to a question of who appoints governor-general's? This is an absolutely different world! You barely touched it, it is beyond your understanding, you are like a child inside a gun powder storage. And you are asking me to pass you a lit candle. As for governor-general's: de Poincy himself never crosses the count neither in the matters of coin nor in the matters of politics. Vice King, the term so popular among the commoners, would suit Henri de Levi Vantadur just fine.";
			link.l1 = "And here I am, intending to skin his only male heir, I know what I am risking here. Now, just tell me: is there anything useful you know that could help me?";
			link.l1.go = "goldengirl_14";
		break;
		
		case "goldengirl_14":
			dialog.text = "In the other day, I would consider this move to your pistol as an end to our friendship, Charles. But I understand your current state of mind. This is why I am ready to forget about this. I know nothing of use to you, the frigate went West early morning. You should pay a visit to the marquise... Wait, not like that! Julianna knows a lot about your enemy and she was personally... acquainted to his father for a while. Ask her. Unlike me, she won't be stopping you.";
			link.l1 = "That's the plan. See you, Excellency. Thank you for your time.";
			link.l1.go = "goldengirl_15";
		break;
		
		case "goldengirl_15":
			DialogExit();
			LocatorReloadEnterDisable("FortFrance_town", "reload9_back", false); 
			LocatorReloadEnterDisable("FortFrance_town", "reload91", false);
			sld = characterFromId("Julianna");
			sld.dialog.currentnode = "Julianna_58";
			LAi_SetOwnerType(sld);
			LAi_group_MoveCharacter(sld, "FRANCE_CITIZENS");
			pchar.questTemp.GoldenGirl = "find_girl";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

