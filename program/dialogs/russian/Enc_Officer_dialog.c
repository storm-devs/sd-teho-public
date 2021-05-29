// BOAL новый диалог офицера и компаньона 21/06/06
void ProcessDialogEvent()
{
	ref NPChar, d;
	aref Link, Diag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makeref(d, Dialog);
	makearef(Diag, NPChar.Dialog);
	
	ref    	sld, rItm, rItem;
	string 	attr, attrLoc, sGun, sBullet, attrL, sAttr;
	int    	iTemp, iTax, iFortValue, i;
	aref 	rType;
	
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
			if (LAi_grp_playeralarm > 0)
			{
       			dialog.text = RandPhraseSimple("Heh, captain, a half of the garrison is after you at the moment. Surely it's not the best time to get hired in your crew!", "And fighting our way through to the ship? No, cap, some other time...");
				link.l1 = RandPhraseSimple("As you wish...", "Actually, I wasn't going to hire you."); 
				link.l1.go = "exit";
				break;
			}
			Diag.TempNode = "OnceAgain";
			dialog.text = "Do you need an officer, captain?";
			if (FindFreeRandomOfficer() > 0)
			{
    			Link.l1 = "An officer? And what are you good at?";
    			Link.l1.go = "Node_2";
			}
			Link.l2 = "No, I've got full set.";
			Link.l2.go = "Exit";			
		break;
		
		case "CitizenNotBlade":
			dialog.text = "Captain, what are you doing? Put away your weapon, before you'll make a lot of trouble!";
			link.l1 = LinkRandPhrase("Fine.", "Okay.", "Don't worry, I am putting it away...");
			link.l1.go = "exit";
		break;
		
		case "hired":
			Diag.TempNode = "Hired";
			// только наняли -->
			if (IsCompanion(NPChar))
			{
				Dialog.text = "Today, we are finally setting sail!";
				link.l2 = "Yeah... I am glad.";
				link.l2.go = "Exit";
				break;
			}
			if (Npchar.location.group == "sit" && !isShipInside(pchar.location))
			{
				dialog.text = "I'll just finish my drink, captain, and then will go to the ship. Don't worry - I will be there in time.";
				Link.l1 = "Alright. If you're late, I'll make you swab the deck!";
				Link.l1.go = "Exit";
				break;
			}
			// только наняли <--
   			dialog.text = "What do you want, captain?";
			// диалог компаньона на корабле.
			if (CheckAttribute(NPChar, "IsCompanionClone"))
			{
				Link.l2 = "I need to issue several orders to you.";
				Link.l2.go = "Companion_Tasks";
				break;
			}
			
			// на Тайясаль
			if (CheckAttribute(pchar, "questTemp.Dolly_Tieyasal") && !CheckAttribute(npchar, "quest.Tieyasal"))
			{
				Link.l4 = ""+npchar.name+", I am going to an old Indian town of Tayasal. This is going to be a perilous and unusual journey - through a teleportation idol. Are you ready to follow your captain?";
				Link.l4.go = "tieyasal";
			}
			
			if (isOfficer(Npchar)) // проверка для кампуса, где слотовые офы
			{
				Link.l2 = "Now hear my order!";
				Link.l2.go = "stay_follow";
			}

           		// boal отчет о корабле
			if(CheckAttribute(NPChar, "treasurer") && NPChar.treasurer == 1)
			{
			    Link.l8 = "Give me a comprehensive ship report, " + GetStrSmallRegister(XI_ConvertString("treasurer")) + ".";
			    Link.l8.go = "QMASTER_1";
			        
			    // Warship. Автозакупка товара
			    if(!CheckAttribute(PChar, "TransferGoods.Enable"))
			    {
				    Link.l11 = "I want you to purchase goods while we are staying in the colony.";
				    Link.l11.go = "TransferGoodsEnable";
			    }
			    else
			    {
				    Link.l11 = "You know, we no longer need to purchase goods in colonies.";
				    Link.l11.go = "TransferGoodsDisable";
			    }
			}
			
			if (pchar.location != "My_Campus") // patch-5
			{
			Link.l4 = "Officer, your services are no longer needed.";
			Link.l4.go = "AsYouWish";
			}
			
			
			// по тек локации определим можно ли тут приказать  -->
			if(IsEntity(&loadedLocation))
			{
				if(CheckAttribute(loadedLocation, "fastreload"))
				{
					iTemp = FindColony(loadedLocation.fastreload);
					if(iTemp != -1)
					{
						sld = GetColonyByIndex(iTemp);
						if(sti(sld.HeroOwn) == true && !CheckAttribute(sld, "OfficerIdx"))
						{
							NPChar.ColonyIdx = iTemp;
							Link.l7 = "I make you a deputy of this town!";
							Link.l7.go = "Gover_Hire";
						}
					}
				}
			}
			
			Link.l9 = "Nothing. At ease!";
			Link.l9.go = "Exit";
		break;
		
		// Тайясаль
		case "tieyasal":
			dialog.text = LinkRandPhrase("Sorry, cap, but that's not what I'd signed for. Don't think that I'm a coward, but I am not willing to go and face certain death. I am not tired of living that much - not yet. You can fire me if you like.","Captain, I beg your pardon, but - no. Seas, boarding, enemy cities - that's perfectly fine, but I don't want to mess with that Indian witchcraft. If you're upset with my response, you can cancel our contract.","You want the impossible, captain, and you realize it. No one will come back alive, including you, so I'll pass. If you consider my refusal a violation of the terms of contract, you can cancel it.");
			link.l1 = LinkRandPhrase("I don't blame you, officer. I perfectly understand it.","A pity, but I can understand you. That's why I told you about it beforehand.","I was counting on you... But I can understand your position, officer.");
			link.l1.go = "tieyasal_1";
		break;
		
		case "tieyasal_1":
			DialogExit();
			npchar.quest.Tieyasal = "true";
		break;
		
		case "TransferGoodsEnable":
			if(sti(PChar.Ship.Type) == SHIP_NOTUSED)
	        {
				dialog.text = "Captain, what goods? We need to find ourselves a ship first!";
				Link.l1 = "Yes, you're right.";
				Link.l1.go = "Exit";
				Diag.TempNode = "Hired";
				break;
	        }
	        	
			PChar.TransferGoods.Enable = true;
		//	PChar.TransferGoods.TreasurerID = NPChar.id;
			Dialog.text = "It will be done, "+ GetSexPhrase("sir","miss") +" captain!";
			Link.l1 = "At ease.";
			Link.l1.go = "TransferGoodsEnable_2";
        break;
        	
		case "TransferGoodsEnable_2":
			Diag.CurrentNode = "Hired";
			DialogExit();
			LaunchTransferGoodsScreen(); // Интерфейс автозакупки товаров
		break;
		
		case "TransferGoodsDisable":
			DeleteAttribute(PChar, "TransferGoods.Enable");
			Dialog.text = "It will be done, "+ GetSexPhrase("sir","miss") +" captain!";
			Link.l1 = "At ease.";
			Link.l1.go = "exit";
			Diag.TempNode = "Hired";
		break;
        
		case "ShowParam_exit":
			Diag.CurrentNode = "OnceAgain";
			NPChar.quest.meeting = true;
			DialogExit();
			
			PChar.SystemInfo.OnlyShowCharacter = true;
            LaunchCharacter(NPChar);
		break;
		
		case "exit":
			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = true;
			DialogExit();			
		break;

		case "exit_hire":
			Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(Npchar.id);
			AddDialogExitQuestFunction("LandEnc_OfficerHired");
			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = true;
			DialogExit();
		break;

		case "exit_fire":
			//navy -->
			if (CheckAttribute(NPChar, "PGGAi"))
			{
				pchar.questTemp.FiringOfficerIDX = NPChar.index;
				AddDialogExitQuestFunction("PGG_FireOfficer");
				DialogExit();			
				break;
			}
			//navy <--
			Diag.TempNode = "Fired";
			Pchar.questTemp.FiringOfficerIDX = GetCharacterIndex(Npchar.id);
			AddDialogExitQuestFunction("LandEnc_OfficerFired");

			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = true;

			DialogExit();			
		break;
		
		// boal 29.05.04 офицер хочет свалить -->
        case "WantToGo":
			chrDisableReloadToLocation = false;
			Diag.TempNode = "Hired";
			dialog.text = LinkRandPhrase(LinkRandPhrase("Captain, you know, I... Well, I'd ask you to relieve me. It's time for me to settle, get married and make some kids. I still have no home of my own - when I get old, there will be no one to bring me a glass of water.","Captain, please, let me resign. For all these years I've been dangling all around the world - and still haven't really seen anything. I just want to live a new life, cast the anchor and see the world from a different perspective.","Captain, naval service is surely a fine thing - there's good profit and adventure, but time has come for me to think about myself. You know, cast an anchor in a quiet harbor, buy a home, have kids. Please, let me go."), LinkRandPhrase("Captain, you know, I am really sorry, but I am really fed up with all those duties, watches and discipline. You know, I just want to live a free life at least for a while, but I realize that you will not be waiting for me, so... Can you discharge me?","Captain, you know... There was a small vessel I could afford, so... I think it's probably time for me to start my own business. Please let me go.","Captain, I was just offered a position at the port. Actually, I've been longing to cast anchor and settle down to a married life for quite some time already. Please, allow me to go - I really can't miss such an opportunity."), LinkRandPhrase("Captain, I am really sick with sea. Doctors keep telling me that it's idiosyncrasy. Please, for God's sake - let me go, or I'll just jump overboard sometime.","Captain, I think it's time for me to settle down and find myself a quieter place. You know, I am afraid. Afraid of stray bullets, afraid to die during a boarding. I pray the Lord to keep me alive, and when I close my eyes, I see all the innocent souls I've killed - they are begging to spare them... Please, let me go, be kind to me.","Captain, my old wounds are aching, and the recent contusion reminds of itself each and every day. Soon you will dismiss me - and who will hire me after that? Please let me go - I'll patch myself up and find a quieter place."));
			Link.l1 = RandPhraseSimple(LinkRandPhrase("They all leave eventually. Fine, you are free to go.","Well, I can understand your reasoning. Sooner or later all things come to an end. Well, go then... and bear no grudge if I offended you.","This again? Have you purposely chosen the most inopportune moment possible to leave me, right? Whatever. Farewell."), LinkRandPhrase("Hard to believe in what you're telling me... Fine, pack your things and go.","You? Didn't expect... All this time back to back and now... Well, I'm not stopping you. Godspeed.","You sound serious. Good luck, I'll miss you."));				
			Link.l1.go = "WantToGo_free";
			if (sti(Pchar.money) >= sti(NPChar.rank)*250)
			{
				Link.l2 = LinkRandPhrase("I see... So that's how it is, eh? And I was counting on you... Well, if you have already made up your mind - let's part our ways, then. Take "+sti(NPChar.rank)*250+" pesos for your loyal service - and bear no grudge if I offended you.", "Well, I bear no grudge and remember no evil. If that's what you decided - then go. And take "+sti(NPChar.rank)*250+" pesos to get a fresh start, this will always come in handy.", "I see... Well, sooner or later that was bound to happen. I'll give you "+sti(NPChar.rank)*250+" pesos to settle your life. And take care for your health, too - naval service is full of hardships..."); 
				Link.l2.go = "Im_kind_A2_1";
			}
			Link.l3 = LinkRandPhrase("So you say... Don't you realize that by leaving now you're simply stabbing me in the back? I cannot let you go now - don't even think of it.", "Now that's a news! You know, people are supposed to notify of such things beforehand! So forget about your private life for a while. When the time comes, I'll suggest you retire.", "No resignations. I have everyone on account. I can't let everyone go just because of personal wish. Serve while I'll be thinking to make some decision.");	
			Link.l3.go = "WantToGo_Stay";
		break;
		
		case "Im_kind_A2_1":
			AddMoneyToCharacter(Pchar, -(makeint(sti(NPChar.rank)*250)));
			ChangeOfficersLoyality("good_all", 1);
			ChangeCharacterComplexReputation(pchar,"nobility", 1);
			ChangeCharacterComplexReputation(pchar,"authority", 0.5);
			dialog.text = "Thank you, captain! A really unexpected generosity... You know, I still have some of your things - maybe you'd like to have them back?";
			Link.l1 = "Perhaps... Finding a good blade is not so easy these days...";
			Link.l1.go = "Get_out_А2_chang";
			Link.l2 = "Oh, don't bother. Keep them as a memento of your service.";
			Link.l2.go = "WantToGo_free";
		break;
		
		case "WantToGo_Stay":
			dialog.text = RandPhraseSimple("But how so, captain? Even the slaves are eventually sent to the shore. And I am no slave, so I can decide my fate by myself!", "Captain, I have served you faithfully all this time. Didn't I deserve the right to decide my fate by myself?");
			Link.l1 = LinkRandPhrase("I see that I cannot keep you as it stands. Alright - how about financial support? This will never hurt - you can use that money to build yourself a cozy home in a quiet harbor - or take care of your health...", "Alright, let's put it this way. What sum could possibly make you reconsider?", "You're right. But what about one-time monetary allowance?");
			Link.l1.go = "WantToGo_Stay_2";
			Link.l2 = PCharRepPhrase(	
				RandPhraseSimple("Oh, no, my friend, here you are mistaken... While you were wearing your pants through at the tavern, you could decide for yourself, but once you stepped on board on my ship, you handed your fate into my hands.", "Hmm. Now, that's a serious statement. Apparently, you have forgotten how I found you - in a stinky tavern without a copper in your pocket. Hey, you can't even be shown just a single gold coin - you will immediately turn it to rum. 'Decide my fate...' Pfff!"),
				LinkRandPhrase("While you are in my service, it is me who makes decisions. And now would you please return to your duties, before you've angered me too much!", "Hmm. Now, that's a serious statement. But you haven't yet worked off all the money paid to you in advance. So your demarche can be considered an attempt of extortion, right?", "Oh, I see... What do the ship's regulations say? Here, paragraph two: 'Whoever attempts to take flight will be landed on a deserted shore with a powder bag, a flask of water, a rifle and a handful of bullets.' Now, how would you like that?"));	
			Link.l2.go = "WantToGo_Stay_force";
		break;
		
	case "WantToGo_Stay_2":
		dialog.text = LinkRandPhrase("Well, that's a different story. "+sti(NPChar.rank)*500+" pesos on the nail, and I'll stay with you.", "Well, perhaps for "+sti(NPChar.rank)*500+" pesos I could stay, I guess.", "Well, if you put it that way, for "+sti(NPChar.rank)*500+" pesos I could continue my service.");
		if (sti(Pchar.money) >= sti(NPChar.rank)*500)
		{
			Link.l1 = RandPhraseSimple("Alright, agreed.", "Alright. Although you could ask for less.", "You've got quite an appetite, I see! But well - I gave a promise, and I will stay true to my word.");	
			Link.l1.go = "WantToGo_Stay_ForMoney";
		}
		Link.l2 = LinkRandPhrase("That's just too much. I could hire two officers for such a price. Perhaps, it's simpler to just let you go.", "Well, you're certainly have a high opinion of yourself. Alright, I'll let you go. But you'll see for yourself, once you are footloose, that your life is not gonna be as unclouded as you expected.", "I am not going to pay such money. You can go, but don't even ask to return back - I don't forgive betrayal.");				
		Link.l2.go = "WantToGo_free";
	break;
	
	case "WantToGo_Stay_force":
		Npchar.loyality = makeint(Npchar.loyality) - 2;
		dialog.text = "Alright, if you put it this way, I'll stay. But know that by doing so I am going against my own will.";
		Link.l1 = LinkRandPhrase("Very good. Return to your duties, and we will continue this conversation later.", "Return to the ship - and next time think again before asking for retirement.", "Indeed. Duty is duty, and you should not be indulging in your fantasies.");
		Link.l1.go = "exit";
	break;
	
	case "WantToGo_Stay_ForMoney":
		Diag.TempNode = "Hired";
		NPChar.greeting = "Gr_Officer";
		ChangeCharacterComplexReputation(pchar,"authority", 0.2);
		AddMoneyToCharacter(Pchar, -(makeint(sti(NPChar.rank)*500)));
		Npchar.loyality = makeint(Npchar.loyality) + 1;    
		Diag.CurrentNode = Diag.TempNode;
		NPChar.quest.meeting = true;
		DialogExit();
		NPChar.location = "none";
		LAi_SetOfficerType(NPChar);
	break;
	
	case "WantToGo_free":
		//navy -->
		if (CheckAttribute(NPChar, "PGGAi"))
		{	
			pchar.questTemp.FiringOfficerIDX = NPChar.index;
			AddDialogExitQuestFunction("PGG_FireOfficer");
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();	
			break;
		}
		//navy <--
		Diag.TempNode = "WantToGo_free_Yet";
		Pchar.questTemp.FiringOfficerIDX = GetCharacterIndex(Npchar.id);
		AddDialogExitQuestFunction("LandEnc_OfficerFired");
		Diag.CurrentNode = Diag.TempNode;
		NPChar.quest.meeting = true;
		DialogExit();
	break;
	
	case "WantToGo_free_Yet":
		Diag.TempNode = "WantToGo_free_Yet";
		dialog.text = LinkRandPhrase ("You won't believe it, captain - it's such a great weight off my mind.", "Thank you, captain, for not trying to hold me. You know, I really want to try other things in life.", "Heh, now I'll have to get used to my newfound freedom. Only now I've begun to realize just how fed up I was with all that fleet service.");	
		Link.l1 = RandPhraseSimple("Well, best of luck to you.", "You are free now. Your service is over.");
		Link.l1.go = "exit";
	break;
	// boal 29.05.04 офицер хочет свалить <--
		
	// пассажир возмущен игроком и сваливает -->
	case "WantToRemove":
        chrDisableReloadToLocation = false;
		if (Npchar.alignment == "good")
		{
			dialog.text = RandPhraseSimple(LinkRandPhrase("Captain, I don't want to act against my conscience and partake in brigandage.","Captain, I no longer wish to partake in your riots. I am an officer, not a butcher.","Captain, your bandit ways of doing business make my stay in your crew impossible."), LinkRandPhrase("Captain, I must admit that my employment with you was a disappointing mistake. I am not willing to sacrifice my reputation for any money.","Captain, you've gathered on your ship all the most villainous cutthroats in the New World - it's disgusting for a decent man just to look at them. I don't want to continue serving in such a crew anymore.","Captain, you've hired a full crew of rascals - not a single decent man to chat with. I have a distaste for such service.")) + " Farewell.";
			Link.l1 = "What?! It's a military ship, not a finishing school! You can go to hell then!";
			Link.l1.go = "exit_fire_1";
			if (sti(Pchar.money) >= sti(NPChar.rank)*500)
			{
				Link.l2 = "I knew you would soon leave... this service is not for you. But you don't accuse me of anything. Here are "+sti(NPChar.rank)*500+" pesos - you will find them handy while you're looking for a job to your liking.";
				Link.l2.go = "Im_kind_A2";
			}
			Link.l3 = LinkRandPhrase("Oh, so that's the tune you're singing now. And what about your share from each and every heist - does it burn your hands? Or you're planning to retire to a monastery to pray for forgiveness of your sins? Put in a word for us as well, then! Mwa-ha-ha-ha-ha!", "Hmm. Now, that's a serious statement. And where was your virgin conscience looking at, while we were robbing merchants together? How are you going to wash it clean? Or are you going to squeal us - to hang on the gallows in a decent company?", "Oh, bravo! Apparently, you have forgotten how I found you - in a stinky tavern without a copper in your pocket. For your information, as an officer you're not worth a brass farthing. You're worthless!");
			Link.l3.go = "WantToGo_stop";
		}
		else
		{
            dialog.text = RandPhraseSimple(LinkRandPhrase("Captain, I really dislike your noble games and I am not going to abandon my habits for the sake of your serenity. Farewell.","Captain, I can no longer stay in your service. I've already wasted so much time - being a simple privateer would already win me a fortune. I am leaving.","Captain, your men disgust me. Not a single decent man - only fancy pants, not any to make a company to drink. I am leaving."), LinkRandPhrase("Captain, I am a veteran officer, and your ship looks more like a cargo barge. I am not fond of such service. Farewell.","Captain, your entire crew is all fancy pants - not a single man to drink with or talk to. I have a strong distaste for such service. Farewell.","Captain, I used to think that I was serving under a real corsair, but all we do is just charity! I don't want to keep wasting my time. I am leaving."));
			Link.l1 = RandPhraseSimple("I see. Considering your attitude, that should have happened sooner or later. Alright, I will not hold you.", "Your statement was not unexpected. Frankly, I've been unsatisfied with your attitude for quite some time.") + " Best of luck.";
			Link.l1.go = "exit_fire_1";
			if (sti(Pchar.money) >= sti(NPChar.rank)*500)
			{
				Link.l2 = "I knew you would soon leave ... this service is not for you. But you don't accuse me of anything. Here are "+sti(NPChar.rank)*500+" pesos - they will come in handy while you're looking for a new job.";
				Link.l2.go = "Im_kind_A2";
			}
			Link.l3 = RandPhraseSimple("Hmm. Now, that's a serious statement. But you haven't yet worked off all the money paid to you in advance. So your demarche can be considered an attempt of extortion, right?", "Oh, I see... What do the ship's regulations say? Here, paragraph two: 'Whoever attempts to take flight will be landed on a deserted shore with a powder bag, a flask of water, a rifle and a handful of bullets.' Now, how would you like that?");
			Link.l3.go = "WantToGo_stop";
		}
		break;
		
		case "WantToGo_stop":
			if (Npchar.alignment == "good")
			{
				dialog.text = LinkRandPhrase("Don't even try to insult me! I am working for money, but I still have the right to choose a job of my liking!", "I am a free man! And I have the right to take a new job whenever I want!", "I am not a slave to work for food, so my conscience is clear! But I will no longer partake in robbery!");
				Link.l1 = "Well, actually, you are mistaken... While you were drinking at the tavern - yes, you could pick whatever job you liked... But as soon as you'd stepped on board of my ship - that's it, the only way back is with a cannonball on your neck... And with a tongue ripped out - so that you don't blurt anything out in the next world...";
				if (makeint(Pchar.Rank) > makeint(NPchar.Rank))
				{
					Link.l1.go = "WantToGo_stop_stay";
				}
				else
				{
					Link.l1.go = "WantToGo_stop_fight";	
				}
				Link.l2 = "Alright. You can go... But God forbid you to meet me in the open sea. I swear, you will regret the moment you decided not to stay at my side.";
				Link.l2.go = "exit_fire_5";
			}
			else
			{
				dialog.text = LinkRandPhrase("Don't even try to intimidate me! I am working for money, but I still have the right to choose a job of my liking!", "I am a free man! And I have the right to take a new job whenever I want!", "I am not your slave! And I am not going to keep leading a miserable life on your old tub!");
				Link.l1 = "Well, actually, you are mistaken... While you were drinking at the tavern - yes, you could pick whatever job you liked... But as soon as you'd stepped on board of my ship - that's it, the only way back is with a cannonball on your neck... And with a tongue ripped out - so that you don't blurt anything out in the next world...";
				if (makeint(Pchar.Rank) > makeint(NPchar.Rank))
				{
					Link.l1.go = "WantToGo_stop_stay";
				}
				else
				{
					Link.l1.go = "WantToGo_stop_fight";	
				}
				Link.l2 = "Alright. You can go... But God forbid you to meet me in the open sea. I swear, you will regret the moment you decided not to stay at my side.";
				Link.l2.go = "exit_fire_5";
			}
		break;
		
		case "WantToGo_stop_stay":
			dialog.text = RandPhraseSimple("If you put it this way, I'll stay - I simply have no other choice. But keep in mind that I am doing this not of my own accord...", "Alright, if you put it this way, I'll stay. But know that by doing so I am going against my own will.");
			Link.l1 = RandPhraseSimple("That's okay... Serve till I decide when to let you go.", "That's good. Keep serving... I'll decide when to let you go.");
			Link.l1.go = "WantToGo_Munity"; //этот линк ведет к бегству
		break;
		
		case "WantToGo_stop_fight":
			dialog.text = NPCharRepPhrase(NPChar, "You will never force me to reconsider! You have no rights to keep me as a slave! I'm gonna leave, stay away or you're done.", "You think you can frighten a veteran officer?! More than once I have been within hair's breadth of death. And if you put it that way, it's much better to die in a fair battle rather that during a mean plunder!");
			Link.l1 = NPCharRepPhrase(NPChar, "Well... everyone chooses his own fate. I hope you had said your prayers before coming to me.", "If I knew that would happen when I picked you up at the tavern I would let you to get to scaffold. And now is not too late arrange it...");
			Link.l1.go = "WantToGo_stop_fight_1";
			Link.l2 = NPCharRepPhrase(NPChar, "Well, you can leave if you need your freedom so much. But I am not giving you any recommendations.", "Alright. You can go... But God forbid you to meet me in the open sea. I swear, you will regret the moment you decided not to stay at my side.");
			Link.l2.go = "exit_fire_5";	
		break;
		
		case "WantToGo_stop_fight_1":
			ChangeOfficersLoyality("bad_all", 1);
			ChangeCharacterComplexReputation(pchar,"nobility", -1);
			ChangeCharacterComplexReputation(pchar,"authority", -1);
			dialog.text = NPCharRepPhrase(NPChar, "Stop intimidating me already! Who of your suckers will dare to stand up to me? If I were captain, they would be rolling in money by now! And you engaged in all this charity - and now you fear that your crew will take my side?!", "Leave off your ways, you will not scare me! Farewell.");
			Link.l1 = NPCharRepPhrase(NPChar, "No, buddy, you'll not live long enough to get to the scaffold. Such luxury isn't for you...", "Not so fast, buddy, I still haven't given you calculation...");
			Link.l1.go = "Get_out_fight";
		break;	
		///////////////////////////////////////////////////////////////////////////////////
		case "WantToGo_Munity":	//zagolski. отыгрыш бегство офицера
			Diag.TempNode = "Hired";
			if (!CheckAttribute(pchar, "questTemp.MutinyOfficerIDX"))
			{
				pchar.questTemp.MutinyOfficerIDX = npchar.index;
				npchar.quest.Mutiny = true; // mitrokosta доп защита от багов
				SetFunctionTimerCondition("mOfficer_fc", 0, 0, 1, false);
			}
			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = true;
			NPChar.location = "none";
			LAi_SetOfficerType(NPChar);
			DialogExit();
		break;
		////////////////////////////////////////////////////////////////////
		// пассажир возмущен игроком и сваливает <--
		
		case "Node_2":
			dialog.text = NPCharRepPhrase(Npchar, RandSwear() + "I am the best "+ XI_ConvertString(Npchar.quest.officertype) + " within these waters. " + Npchar.quest.officertype_2 + "And I am ready to do you a favor and serve under you.",
                                    "Well, they say I am not bad " + XI_ConvertString(Npchar.quest.officertype) + ". " + Npchar.quest.officertype_2 + "You can take me on your ship, captain, and see for yourself.");
			Link.l1 = "And how much do you want?";
			Link.l1.go = "price";
			Link.l2 = "And what kind of specialist are you?";
			Link.l2.go = "ShowParam_exit";
			Link.l3 = "Alas, I already have a " + XI_ConvertString(Npchar.quest.officertype) + ".";
			Link.l3.go = "Exit";
		break;

		case "OnceAgain":
			if (LAi_grp_playeralarm > 0)
			{
       			dialog.text = RandPhraseSimple("Heh, captain, half the garrison is after you at the moment. Surely it's not the best time to get hired in your crew!", "And fighting our way through to the ship? No, cap, some other time...");
				link.l1 = RandPhraseSimple("As you wish...", "Actually, I wasn't going to hire you."); 
				link.l1.go = "exit";
				break;
			}
			Diag.TempNode = "OnceAgain";
			dialog.text = "Have you changed your mind, captain? Decided that a new " + XI_ConvertString(Npchar.quest.officertype) + " wouldn't hurt?";
			// boal -->
			if (FindFreeRandomOfficer() > 0)
			{
                Link.l1 = "Something like that. How much do you want?";
                Link.l1.go = "price";
			}
			Link.l2 = "And what are you capable of?";
			Link.l2.go = "ShowParam_exit";
			// boal <--
			Link.l3 = "I have a full set. See you.";
			Link.l3.go = "exit";
		break;

		case "price":
			dialog.text = "I think we can agree on " + Npchar.quest.OfficerPrice + " pesos.";
			Link.l1 = "Isn't that a bit much?";
			Link.l1.go = "trade";
			Link.l2 = "I agree. Consider yourself a part of the crew.";
			Link.l2.go = "hire";
			Link.l3 = "You're not worth this money.";
			Link.l3.go = "exit";
		break;

		case "trade":
			if (GetSummonSkillFromNameToOld(pchar, SKILL_COMMERCE) >= Rand(12) && (sti(Npchar.quest.OfficerPrice) - GetCharacterSkillToOld(Pchar, "commerce")*100) >= sti(Npchar.quest.OfficerLowPrice))// bug fix
			{
				Npchar.quest.OfficerPrice = makeint(makeint(Npchar.quest.OfficerPrice) - GetCharacterSkillToOld(Pchar, "commerce")*100); // пусть будет коммерция перса голой
				dialog.text = "Alright... I guess I could agree even on " + Npchar.quest.OfficerPrice + " pesos. What do you say?";
				Link.l1 = "Now that's better. You're in.";
				Link.l1.go = "hire";				
				Link.l2 = "I still think it's a bit too much. Bye.";
				Link.l2.go = "exit";
			}
			else
			{
				dialog.text = "I am sorry, captain, but I am worth exactly as mush as I asked for. If it's too much for you - go find someone else.";
				Link.l1 = "Alright, I agree. I'll take you.";
				Link.l1.go = "hire";				
				Link.l2 = "That's what I am going to do. Farewell.";
				Link.l2.go = "exit";
			}
		break;

		case "hire":
			if(makeint(Pchar.money) >= makeint(Npchar.quest.OfficerPrice))
			{
				AddMoneyToCharacter(Pchar, -(makeint(Npchar.quest.OfficerPrice)));
				Diag.TempNode = "OnboardSoon";
				dialog.text = "Thank you, captain. You will not regret your choice.";
				Link.l1 = "I hope so.";
				Link.l1.go = "Exit_hire";								
			}
			else
			{
				dialog.text = "I see you're short of cash, captain! I am sorry, but I don't work in credit.";
				Link.l1 = "Oh, devil!";
				Link.l1.go = "Exit";								
			}
		break;

		case "OnboardSoon":			
			Diag.TempNode = "OnboardSoon";
			dialog.text = "I'll just finish my drink, captain, and then will go to the ship. Don't worry, I will be there in time.";
			Link.l1 = "Alright. If you're late, I'll make you swab the deck!";
			Link.l1.go = "Exit";											
		break;
        
		case "QMASTER_1":
			if(sti(PChar.Ship.Type) == SHIP_NOTUSED)
			{
				dialog.text = "Captain, but you have no ship!";
				Link.l1 = "Thank you for reminding me...";
				Link.l1.go = "Exit";
				Diag.TempNode = "Hired";
				break;
			}
			
			dialog.text = "Maximum activity of rats in voyage " +
			FloatToString(50.0 / (2.0+GetSummonSkillFromNameToOld(PChar, SKILL_REPAIR) + GetSummonSkillFromNameToOld(PChar,SKILL_SNEAK)), 1) +
			"% of the total cargo amount. For "+GetCrewQuantity(PChar) + " sailors we will need " + makeint((GetCrewQuantity(PChar)+6) / 10) + " food per day. This is without accounting for slaves being transported.";
			Link.l1 = "Thanks.";
			Link.l1.go = "Exit";
			Diag.TempNode = "Hired";
		break;
        
        // boal 05.09.03 offecer need to go to abordage -->
        case "stay_follow":
            dialog.text = "What are your orders?";
            Link.l1 = "Stand here!";
            Link.l1.go = "Boal_Stay";
            Link.l2 = "Follow me and don't fall behind!";
            Link.l2.go = "Boal_Follow";
            // boal 05.09.03 offecer need to go to abordage <--
			if (npchar.id == "OffMushketer")
			{
				Link.l3 = "I want you to stay on certain distance from target.";
				Link.l3.go = "TargetDistance";
			}
			
			sGun = GetCharacterEquipByGroup(NPChar, GUN_ITEM_TYPE);
			if(sGun != "")
			{
				if(CheckAttribute(NPChar, "chr_ai.bulletNum") && sti(NPChar.chr_ai.bulletNum) > 1)
				{
					Link.l4 = "We need to change the ammunition type for your firearm.";
					Link.l4.go = "SetGunBullets";
				}	
			}						
		break;

		case "SetGunBullets":
			Dialog.Text = "Select ammunition type:";
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
			Diag.CurrentNode = Diag.TempNode;
			DeleteAttribute(NPChar,"SetGunBullets");
			DialogExit();
		break;		
		
		case "TargetDistance":
			dialog.text = "Which distance exactly, captain? Indicate in meters, but not more than 20.";
			link.l1 = "";
			Link.l1.edit = 3;
			link.l1.go = "TargetDistance_1";			
		break;
		case "TargetDistance_1":
			iTemp = sti(dialogEditStrings[3]);
			if (iTemp < 0)
			{
				dialog.text = "Captain, what a bad form!";
				link.l1 = "I am sorry, my bad...";
				link.l1.go = "exit";
				break;
			}
			if (iTemp == 0)
			{
				dialog.text = "I will stand in place without moving. Is that what you want from me, captain?";
				link.l1 = "Yes. That's exactly what's needed of you.";
				link.l1.go = "exit";
				npchar.MusketerDistance = 0;
				break;
			}
			if (iTemp > 20)
			{
				dialog.text = "I think I told you that I cannot stand more than 20 meters away from target.";
				link.l1 = "Alright, keep the distance of 20 meters.";
				link.l1.go = "exit";
				npchar.MusketerDistance = 20.0;
				break;
			}
			dialog.text = "Understood and taken into account.";
			link.l1 = "Fine.";
			link.l1.go = "exit";
			npchar.MusketerDistance = iTemp;
		break;

		case "AsYouWish":
			// проверка на море -->
			if (bSeaActive)
			{
				attr = Sea_FindNearColony();
				if (attr == "none")
				{
					dialog.text = "Captain, although I really don't understand your reasoning, can we go back to this on the shore? Or you decided to simply throw me overboard?";
					Link.l1 = "Hmm... No, that's not what I meant. Stay here until you arrive at the port.";
					Link.l1.go = "Exit";	
					break;	
				}
			}
			// проверка на море <--
			if (makeint(PChar.reputation.nobility) >= 41 && makeint(NPChar.reputation) < 41) //герой против злодея
			{
				dialog.text = RandPhraseSimple(LinkRandPhrase("Now this is new!","Why, in Heavens?","What's the reason?!"), RandPhraseSimple("Captain, are you insane? Telling such news a apropos of nothing!","Wow! And what have I done to displease you?"));
				Link.l1 = RandPhraseSimple(LinkRandPhrase("I decided to bring order in the crew. And as I do not like your relationships with colleagues","Your advantages were not so good as discussed in the hiring, so","Thugs and rascals in my team won't stay! So"), LinkRandPhrase("It came to my knowledge that you are stealing rum, secretly accustoming my crew to hard drinking and thus lowering its morale. Therefore","I am fed up with your bandit manners and I am not going to tolerate it. So,","Constantly spend your time into the central cabin for a game of cards or dice, distracting from the other officers of performance of duty. This can not continue indefinitely. So,")) + " pack your belongings and leave the ship.";
				if (makeint(Pchar.Rank) > makeint(NPchar.Rank))
				{
					Link.l1.go = "Get_out_A1_peace";
				}
				else
				{
					Link.l1.go = "Get_out_A1_strife";
				}
				break;	
			}
			if (makeint(PChar.reputation.nobility) >= 41 && makeint(NPChar.reputation) >= 41) // герой против героя
			{
				dialog.text = RandPhraseSimple(RandPhraseSimple("May I know the reason for such a decision?","Obviously, such a decision is well-reasoned?"), RandPhraseSimple("Explain yourself, captain","That's quite unexpected. But I'd still like to know the reason."));
				Link.l1 = RandPhraseSimple(LinkRandPhrase("I am totally dissatisfied with your attitude to your duties.","Unfortunately, you didn't make a good officer - and likely never will...","You're a good officer and your service was fair, but now our ways have parted. Don't ask me why."), LinkRandPhrase("I warned you that passion to the rum would destroy you. How can I trust a man in a fight that isn't even able to put his sword into the sheathe?","You are terrible sailor and officer... I think, you'll get on the shore more than in the sea.","I have not satisfied with your qualifications, but now I've finally found a decent replacement."));
				Link.l1.go = "Get_out_A2";
				break;	
			}
			if (makeint(PChar.reputation.nobility) < 41 && makeint(NPChar.reputation) >= 41) // злодей против героя 
			{		
				dialog.text = RandPhraseSimple(RandPhraseSimple("Hmm... May I know the reason?","That's a serious statement. May I know what in particular are you dissatisfied with?"), RandPhraseSimple("Explain yourself, captain.","Obviously, such a statement is well-reasoned?"));
				Link.l1 = RandPhraseSimple(LinkRandPhrase("I am totally dissatisfied with your qualification, therefore","Unfortunately, you didn't show yourself a decent officer. So,","I am fed up with your noble manners. I'm not going to tolerate them endlessly, so"), LinkRandPhrase("It came to my knowledge that you are instigating the crew to disobedience. There will be no disturbances on my ship! And don't thank me that I hadn't thrown you away before. So","Your noble principles do honor you, but they are contrary to robber life of free privateer. So","I don't like your relation to your duties. So")) + " pack your belongings and leave the ship.";
				if (makeint(Pchar.Rank) > makeint(NPchar.Rank))
				{
					Link.l1.go = "Get_out_A3_peace";
				}
				else
				{
					Link.l1.go = "Get_out_A3_strife";
				}	
				break;
	
			}
			if (makeint(PChar.reputation.nobility) < 41 && makeint(NPChar.reputation) < 41) // злодей против злодея
			{	
				dialog.text = RandPhraseSimple(LinkRandPhrase("Captain, I really didn't expect that! Maybe you would explain what's going on?","Captain, what's eating you?!","What do you mean by that, captain?!"), RandPhraseSimple("What the hell, captain?! All seemed just fine yesterday, but now - here we are, what happened?","Wow! Perhaps, you would explain yourself?"));
				Link.l1 = RandPhraseSimple(LinkRandPhrase("You're a total slacker and useless idiot - even a ship's boy on a coaster would do better. I've been suffering because of you for too long. So","I've been thinking to fire you for a while, and now I've finally found a decent replacement. So","It came to my knowledge that you are stealing rum, secretly accustoming my crew to hard drinking and thus lowering its morale. Therefore"), LinkRandPhrase("When I was hiring you, you were boasting that you were the best officer in the entire fleet, but it turned out that you were just a loafer, so","I warned you that your drinking habit would end badly. Why should I keep a useless drunkard my ship? So","Instead of serving you are constantly wandering somewhere or playing cards or dice. I hope you didn’t think that this could go on forever? So")) + " pack your belongings and leave the ship.";
				Link.l1.go = "Get_out_A4";
				break;
			}
		break;
	
		case "Get_out_A1_peace":
			dialog.text = RandPhraseSimple(LinkRandPhrase("So how you're talking now! Alright, as you wish. But rest assured: I will not come back to you, even if I am dying of starvation!","Frankly, I don't much like your noble games, either. So bye...", "Oh, go to hell! Stay with your lickspittles. A 'hero', indeed!"), LinkRandPhrase("Actually, I never liked serving you... You've got a cargo barge there, not a decent ship. A finishing school, more likely...","You know, I am sick with your sailors - all of them fancy pants, just a little kids, not a single reall man...","Alright, captain, as you say. But God knows, I had been doing my job well..."));
			Link.l1 = "Hold on. At the moment I cannot leave the vessel without an officer. But later we'll come back to this conversation.";
			Link.l1.go = "exit_bad";
			Link.l2 = "Then go in peace.";
			Link.l2.go = "Exit_Fire_1";
			if (sti(Pchar.money) >= sti(NPChar.rank)*500)
			{
				Link.l3 = "Don't get steamed up. I've prepared for you a severance pay - "+sti(NPChar.rank)*500+" pesos. I hope this will remove all questions.";
				Link.l3.go = "Get_out_А1_ForMoney";
			}
		break;

		case "Get_out_A1_strife":
			dialog.text = LinkRandPhrase("Excuse me! What do you mean - 'leave the ship'?! I didn't expose my head to grapeshot just so that you could toss me off whenever you like!", "Ha! 'Leave ship'! Do you seriously think that I will allow you to throw me away like a kitten?!", "Easy, captain, serious people don't settle matters in such a way. I won't be treated like a rookie.");
			Link.l1 = "Alright, you may stay for now - but only until I find a decent substitute." ;
			Link.l1.go = "exit_bad";
			Link.l2 = "I repeat - your service is over. You can pack your stuff.";
			Link.l2.go = "Get_out_A1_strife_1";
			if (sti(Pchar.money) >= sti(NPChar.rank)*500)
			{
				Link.l3 = "Don't get steamed up. I've prepared "+sti(NPChar.rank)*500+" pesos for you. I hope this will remove all questions.";
				Link.l3.go = "Get_out_А1_ForMoney";
			}
		break;

		case "Get_out_A1_strife_1":
			dialog.text = RandPhraseSimple("Actually, I am not burning with desire to stay here. But neither I'll leave without compensation!", "Now, I certainly will not stay on that old tub of yours - but first you will compensate me!") + " "+sti(NPChar.rank)*1000+" pesos, and we'll forget about each other.";
			Link.l1 = "I got worked up a bit... Please, accept my apologies and go back to your duties.";
			Link.l1.go = "exit_bad1";
			Link.l2 = "What money you're talking about if you've always received your fair share? This looks like extortion to me!";
			Link.l2.go = "Get_out_А1_strife_battle";
			if (sti(Pchar.money) >= sti(NPChar.rank)*1000)
			{
				Link.l3 = "Alright. Return the equipment, and then you will have what you asked for.";
				Link.l3.go = "Get_out_А1_chang";
			}
		break;

		case "Get_out_А1_ForMoney":
			AddMoneyToCharacter(Pchar, -(makeint(sti(NPChar.rank)*500)));
			ChangeCharacterComplexReputation(pchar,"nobility", 1);
			ChangeCharacterComplexReputation(pchar,"authority", 0.5);
			dialog.text = "Now that's a different story. Farewell!";
			Link.l1 = "I do hope that our paths will never cross again.";
			Link.l1.go = "Exit_Fire_1";
		break;

		case "Get_out_А1_strife_battle":
			dialog.text = LinkRandPhrase("Consider this a compensation of moral damage. I will not tolerate such treatment, and whoever dares to treat me like that will regret it!", "This is no extortion, but rather a compensation for this stupid waste of my time! And I'll get it, no matter the cost!", "I wasted too much time serving under such sissy as you. I could make a fortune pillaging merchant ships. So I just want to compensate my lost profit.");
			if (sti(Pchar.money) >= sti(NPChar.rank)*1000)
			{
				Link.l1 = "Alright. Here's your money... And now get lost!";
				Link.l1.go = "Get_out_А1_ForMoney_angry";
			}
			Link.l2 = "You seem to be forgetting who you are! I won't allow half-wits like you to shout at me!";
			Link.l2.go = "Get_out_А1_strife_death";
		break;

		case "Get_out_А1_strife_death":
			ChangeCharacterComplexReputation(pchar,"nobility", 1);
			ChangeCharacterComplexReputation(pchar,"authority", -1);
			OfficersReaction("good");
			dialog.text = "Go ahead, captain! Show yourself!";
			Link.l1 = "God knows, I didn't want it!";
			Link.l1.go = "Get_out_fight";
		break;
	
		case "Get_out_А1_ForMoney_angry":
			AddMoneyToCharacter(Pchar, -(makeint(sti(NPChar.rank)*1000)));
			ChangeCharacterComplexReputation(pchar,"nobility", -1);
			ChangeCharacterComplexReputation(pchar,"authority", 0.5);
			OfficersReaction("bad");
			dialog.text = "Now that's a different story. Farewell!";
			Link.l1 = "I do hope that our paths will never cross again.";
			Link.l1.go = "Exit_Fire_1";
		break;

		case "Get_out_A2":
			dialog.text = RandPhraseSimple(LinkRandPhrase("Well, it's decided, then. Farewell, captain, and hold no grudge...","A pity, captain. But God knows, I tried. Farewell.","Well, captain, you're certainly hard to please! Alright, best of luck to you."), LinkRandPhrase("A pity, captain. You know, I liked working for you.","Yeah, things happen... But I bear no grudge. Farewell.","You are unfair to me, captain. Still, I respect your decision. Farewell."));
			Link.l1 = "Hold on, I changed my mind. Let's back to this talk later.";
			Link.l1.go = "exit_good";
			Link.l2 = "Don't be upset. Good luck to you...";
			Link.l2.go = "exit_fire_2";
			Link.l3 = "Hold on... I equipped you nicely. Give things what I need to equip a horde...";
			Link.l3.go = "Return_items_A2";
			if (sti(Pchar.money) >= sti(NPChar.rank)*500)
			{
				Link.l4 = "Hold on... I don't want to let you go empty-handed. Here, take "+sti(NPChar.rank)*500+" pesos - it will come in handy, while you are looking for a new job.";
			}
			Link.l4.go = "Im_kind_A2";
		break;

		case "Return_items_A2":
			ChangeOfficersLoyality("bad_all", 1);
			dialog.text = "Oh, sure, take it all back...";
			Link.l1 = "I know you understand me right...";
			Link.l1.go = "Get_out_А2_chang";
		break;

		case "Im_kind_A2":
			AddMoneyToCharacter(Pchar, -(makeint(sti(NPChar.rank)*500)));
			ChangeOfficersLoyality("good_all", 1);
			ChangeCharacterComplexReputation(pchar,"nobility", 1);
			ChangeCharacterComplexReputation(pchar,"authority", 0.5);
			dialog.text = "Thank you, captain! A really unexpected generosity... You know, I still have some of your things - maybe you'd like to have them back?";
			Link.l1 = "Perhaps... Finding a good blade is not so easy these days...";
			Link.l1.go = "Get_out_А2_chang";
			Link.l2 = "Oh, don't worry. Keep them as a memento of your service.";
			Link.l2.go = "exit_fire_2";
		break;

		case "Get_out_A3_peace":
			dialog.text = RandPhraseSimple(LinkRandPhrase("Alright, as you wish. But rest assured: I will not come back to you, even if I am dying of starvation!!","Captain, your bandit ways of doing business make me sick as well. Sooner or later, this was bound to happen. And there is no need to make up any reasons.","Stay with your cutthroats, then. A decent man would not even show his face in the wardroom of your ship. What a brothel you have here, God forgive me!"), LinkRandPhrase("Frankly, I disliked my service under you as well. You've hired a full crew of rascals - not a single decent man to chat with.","Yeah, if you keep that attitude to your crew, soon you will be alone - and there will be no need to make up any reasons.","Our enmity is mutual, and that comforts me. Goodbye."));
			Link.l1 = "Hold on. Now it's not the best time for your retirement. But all claims stand.";
			Link.l1.go = "exit_bad";
			Link.l2 = "Go, go. I'll do fine without your lectures.";
			Link.l2.go = "exit_fire_3";
			if (sti(Pchar.money) >= sti(NPChar.rank)*500)
			{
				Link.l3 = "Hold on. I'll give you "+sti(NPChar.rank)*500+" pesos. I don't want you to die in the gutter, so that I would feel guilty of it.";
				Link.l3.go = "Get_out_А3_ForMoney";
			}
		break;

		case "Get_out_А3_ForMoney":
			AddMoneyToCharacter(Pchar, -(makeint(sti(NPChar.rank)*500)));
			ChangeCharacterComplexReputation(pchar,"nobility", 1);
			ChangeCharacterComplexReputation(pchar,"authority", 0.5);
			ChangeOfficersLoyality("good_all", 1);
			dialog.text = LinkRandPhrase("Well, thanks. Farewell...", "Thank you for your understanding. Best of luck.", "Now we're done. Best of luck...");
			Link.l1 = "I know you understand me right.";
			Link.l1.go = "exit_fire_3";
		break;
	
		case "Get_out_A3_strife":
			dialog.text = LinkRandPhrase("But, captain - in that case I am left aground. Are you really willing to send me from the ship straight to the parvis?", "You are unfair to me, captain. But I will hold no grudge if I receive decent compensation.", "And this is your gratitude for all my combat wounds? Well, I guess I can't do without monetary compensation.");
			Link.l1 = "Alright, I've chaged my mind. You can stay, but we'll return to this talk.";
			Link.l1.go = "exit_bad";
			if (sti(Pchar.money) >= sti(NPChar.rank)*500)
			{
				Link.l2 = "Oh, don't worry about it. Here - "+sti(NPChar.rank)*500+" pesos. That will compensate your time on my ship.";
				Link.l2.go = "Get_out_А3_ForMoney";
				Link.l3 = "I'll give you the money. Still, you got nicely equipped thanks to me - and I guess it's appropriate to return the stuff back to me.";
				Link.l3.go = "Return_items_A3";
			}
			Link.l4 = "Oh, really? And what about your share, which you had been regularly receiving?! I knew that all will end nagging and begging for premium.";
			Link.l4.go = "Get_out_A3_strife_1";
		break;

		case "Return_items_A3":
			dialog.text = "I knew that you would say that, but you'll get back your equipment only once I receive "+sti(NPChar.rank)*1000+" pesos. Or you can take it from my corpse.";
			Link.l1 = "Alright, take your money, then.";
			Link.l1.go = "Get_out_А3_chang";
			Link.l2 = "Are you insane or what?! Demanding such a sum for what had been given to you for free?! I now see that your greed has clearly won over your feigned well-doing.";
			Link.l2.go = "Get_out_A3_strife_1";
		break;

		case "Get_out_A3_strife_1":
			dialog.text = "Don't dare to insult me! I might be not the best in the Navy, but I am still a combatant officer. And I will be respected, even by such a churl as you are!";
			Link.l1 = "If you haven't got it yet, I will repeat it one more time: quit your begging, you won't get anything from me.";
			Link.l1.go = "Get_out_А3_strife_death";
		break;

		case "Get_out_А3_strife_death":
			ChangeCharacterComplexReputation(pchar,"nobility", -1);
			ChangeCharacterComplexReputation(pchar,"authority", -1);
			OfficersReaction("bad");
			dialog.text = "Well, I will still get a satisfaction!";
			Link.l1 = "Oh, so that's a challenge, isn't it? As you wish, then...";
			Link.l1.go = "Get_out_fight";
		break;

		case "Get_out_A4":
			dialog.text = RandPhraseSimple(LinkRandPhrase("That's my luck! I put my heart and soul into service - and get kicked out without even a service benefit!","What a misfortune?! I get hired - and then I get kicked almost right away. I have no clue to what saint to light a candle these days...","Gee whiz! Getting fired for the third time this year - all of them on Mondays. Perhaps, I shouldn't appear myself in captains presence, when I have a hangover."), LinkRandPhrase("Well, as you wish. Pray that we never meet again.","As you wish. Keep in mind, though, that you will never find a better officer.","Alright, captain, as you say. But God knows, I had been doing my job well..."));
			Link.l1 = "Hold on. Now it's not the best time for your retirement. But all claims stand.";
			Link.l1.go = "exit_good";
			Link.l2 = RandPhraseSimple("Get lost now. And thank God that I am in good mood today.", "Get lost now. You are as good an officer as shit is good for making bullets.");
			Link.l2.go = "exit_fire_4";
			if (sti(Pchar.money) >= sti(NPChar.rank)*500)
			{
				Link.l3 = "Hold on. I'll give you "+sti(NPChar.rank)*500+" pesos. I don't want you to die in the gutter, so that I would feel guilty of it.";
				Link.l3.go = "Get_out_А4_ForMoney";
			}
			Link.l4 = "Hold on... I equipped you nicely, give me my things back.";
			Link.l4.go = "Return_items_A4";
		break;

		case "Get_out_А4_ForMoney":
			AddMoneyToCharacter(Pchar, -(makeint(sti(NPChar.rank)*500)));
			ChangeCharacterComplexReputation(pchar,"nobility", 1);
			ChangeCharacterComplexReputation(pchar,"authority", 0.5);
			ChangeOfficersLoyality("good_all", 1);
			dialog.text = LinkRandPhrase("Oh, thanks, captain! That's really nice of you...", "Thank you for your understanding. Best of luck.", "Now we're done. Best of luck...");
			Link.l1 = "Good luck. I hope you don't waste it all in the first tavern.";
			Link.l1.go = "exit_fire_4";
		break;

		case "Return_items_A4":
			if (makeint(Pchar.Rank) > makeint(NPchar.Rank))
			{
				dialog.text = LinkRandPhrase("And now you're taking my equipment! Oh, my, to hell with it! I'll go fishing, I swear...", "I see that you've decided to totally clean me out. Oh, well. Now there's only one way for me - to the parvis...", "Oh, thank you very much! Now you've decided to rob me. Oh, what a cruel fate... Take it then - what can I do anyway...");
				Link.l1 = "Get lost now. You are as good an officer as shit is good for making bullets.";
				Link.l1.go = "Get_out_А4_chang_1";
			}
			else	
			{
				dialog.text = RandPhraseSimple("As you wish, captain, but first please be so kind to hand me "+sti(NPChar.rank)*1000+" pesos. Let this be a compensation of the moral damage.", "Alright. But I still want to receive "+sti(NPChar.rank)*1000+" pesos as a compensation of my hard and faithful service.");
				if (sti(Pchar.money) >= sti(NPChar.rank)*1000)
				{
					Link.l1 = "What a villain! Alright, here's your money.";
					Link.l1.go = "Get_out_А4_chang";
				}
				Link.l2 = "Aren't you crazy?! Dare you ask for so much money for what I gave you myself!";
				Link.l2.go = "Get_out_A4_strife";
				Link.l3 = "Ah-ha! I was joking! How can I kick out an old friend, as holey cap!";
				Link.l3.go = "exit_bad1";
			}
		break;

		case "Get_out_A4_strife":
			ChangeCharacterComplexReputation(pchar,"nobility", -1);
			ChangeCharacterComplexReputation(pchar,"authority", -1);
			ChangeOfficersLoyality("bad_all", 1);
			dialog.text = "Well, then you won't get anything! I will not make a step until I hear the jingle of my money!";
			Link.l1 = RandPhraseSimple("You will soon hear the jingle of my blade!", "Then you will be carried away feetfirst!");
			Link.l1.go = "Get_out_fight";
		break;

		case "Get_out_fight":
			CheckForReleaseOfficer(GetCharacterIndex(Npchar.id));
			RemovePassenger(Pchar, Npchar);
			LAi_CharacterDisableDialog(NPChar);
			LAi_SetWarriorType(Npchar);
			LAi_group_MoveCharacter(Npchar, "TmpEnemy");
			LAi_group_SetHearRadius("TmpEnemy", 100.0);
			LAi_group_FightGroupsEx("TmpEnemy", LAI_GROUP_PLAYER, true, Pchar, -1, false, false);
			if (PChar.location == Get_My_Cabin() || findsubstr(PChar.location, "_tavern" , 0) != -1 || findsubstr(PChar.location, "_store" , 0) != -1)
            {
				LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
				LAi_group_SetCheck("TmpEnemy", "CannotFightCurLocation");
				LAi_group_SetCheck("TmpEnemy", "MainHeroFightModeOff");
            }
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;

	    case "Get_out_А1_chang": // интерфейс обмена
			Diag.TempNode = "Fired_1";
			LAi_CharacterDisableDialog(NPChar);
			AddMoneyToCharacter(Pchar, -(makeint(sti(NPChar.rank)*1000)));
			ChangeCharacterComplexReputation(pchar,"nobility", -1);
			Pchar.questTemp.FiringOfficerIDX = GetCharacterIndex(Npchar.id);
			AddDialogExitQuestFunction("LandEnc_OfficerFired");
			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = true;
			NPChar.rank = 0;	
			DialogExit();
			LaunchCharacterItemChange(npchar);
			RemovePassenger(Pchar, npchar);
		break;

		case "Get_out_А2_chang": // интерфейс обмена
			Diag.TempNode = "Fired_2";
			LAi_CharacterDisableDialog(NPChar);
			Pchar.questTemp.FiringOfficerIDX = GetCharacterIndex(Npchar.id);
			AddDialogExitQuestFunction("LandEnc_OfficerFired");
			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = true;
			NPChar.rank = 0;
			DialogExit();
			LaunchCharacterItemChange(npchar);
			RemovePassenger(Pchar, npchar);
		break;

		case "Get_out_А3_chang": // интерфейс обмена
			Diag.TempNode = "Fired_3";
			LAi_CharacterDisableDialog(NPChar);
			AddMoneyToCharacter(Pchar, -(makeint(sti(NPChar.rank)*1000)));
			ChangeCharacterComplexReputation(pchar,"nobility", 1);
			Pchar.questTemp.FiringOfficerIDX = GetCharacterIndex(Npchar.id);
			AddDialogExitQuestFunction("LandEnc_OfficerFired");
			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = true;
			NPChar.rank = 0;
			DialogExit();
			LaunchCharacterItemChange(npchar);
			RemovePassenger(Pchar, npchar);
		break;

		case "Get_out_А4_chang_1": // интерфейс обмена
			Diag.TempNode = "Fired_4";
			LAi_CharacterDisableDialog(NPChar);
			ChangeCharacterComplexReputation(pchar,"nobility", -1);
			Pchar.questTemp.FiringOfficerIDX = GetCharacterIndex(Npchar.id);
			AddDialogExitQuestFunction("LandEnc_OfficerFired");
			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = true;
			NPChar.rank = 0;	
			DialogExit();
			LaunchCharacterItemChange(npchar);
			RemovePassenger(Pchar, npchar);
		break;

		case "Get_out_А4_chang": // интерфейс обмена
			Diag.TempNode = "Fired_4";
			LAi_CharacterDisableDialog(NPChar);
			AddMoneyToCharacter(Pchar, -(makeint(sti(NPChar.rank)*1000)));
			ChangeCharacterComplexReputation(pchar,"nobility", 1);
			ChangeCharacterComplexReputation(pchar,"authority", 0.5);
			Pchar.questTemp.FiringOfficerIDX = GetCharacterIndex(Npchar.id);
			AddDialogExitQuestFunction("LandEnc_OfficerFired");
			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = true;
			NPChar.rank = 0;	
			DialogExit();
			LaunchCharacterItemChange(npchar);
			RemovePassenger(Pchar, npchar);
		break;

	    case "exit_bad":
			Npchar.loyality = makeint(Npchar.loyality) - 3;
			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = true;
			DialogExit();
		break;

		case "exit_bad1":
			Npchar.loyality = makeint(Npchar.loyality) - 2;
			ChangeOfficersLoyality("bad_all", 1);
			ChangeCharacterComplexReputation(pchar,"nobility", -1);
			ChangeCharacterComplexReputation(pchar,"authority", -1);
			Diag.CurrentNode = Diag.TempNode;			
			NPChar.quest.meeting = true;
			DialogExit();
		break;

		case "exit_good":
			Npchar.loyality = makeint(Npchar.loyality) - 1;
			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = true;
			DialogExit();
		break;

		case "exit_fire_1":	//navy -->			
			if (CheckAttribute(NPChar, "PGGAi"))
			{				
				pchar.questTemp.FiringOfficerIDX = NPChar.index;
				AddDialogExitQuestFunction("PGG_FireOfficer");
				DialogExit();
				break;
			}	//navy <--		
			Diag.TempNode = "Fired_1";
			Pchar.questTemp.FiringOfficerIDX = GetCharacterIndex(Npchar.id);
			AddDialogExitQuestFunction("LandEnc_OfficerFired");			
			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = true;
			DialogExit();	
		break;

		case "exit_fire_2":	//navy -->		
			if (CheckAttribute(NPChar, "PGGAi"))
			{				
				pchar.questTemp.FiringOfficerIDX = NPChar.index;
				AddDialogExitQuestFunction("PGG_FireOfficer");	
				DialogExit();
				break;
			}	//navy <--	
			Diag.TempNode = "Fired_2";
			Pchar.questTemp.FiringOfficerIDX = GetCharacterIndex(Npchar.id);
			AddDialogExitQuestFunction("LandEnc_OfficerFired");			
			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = true;
			DialogExit();	
		break;

		case "exit_fire_3":	//navy -->		
			if (CheckAttribute(NPChar, "PGGAi"))
			{				
				pchar.questTemp.FiringOfficerIDX = NPChar.index;
				AddDialogExitQuestFunction("PGG_FireOfficer");
				DialogExit();
				break;
			}	//navy <--	
			Diag.TempNode = "Fired_3";
			Pchar.questTemp.FiringOfficerIDX = GetCharacterIndex(Npchar.id);
			AddDialogExitQuestFunction("LandEnc_OfficerFired");			
			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = true;
			DialogExit();	
		break;

		case "exit_fire_4":	//navy -->		
			if (CheckAttribute(NPChar, "PGGAi"))
			{				
				pchar.questTemp.FiringOfficerIDX = NPChar.index;
				AddDialogExitQuestFunction("PGG_FireOfficer");	
				DialogExit();
				break;
			}	//navy <--		
			Diag.TempNode = "Fired_4";
			Pchar.questTemp.FiringOfficerIDX = GetCharacterIndex(Npchar.id);
			AddDialogExitQuestFunction("LandEnc_OfficerFired");			
			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = true;
			DialogExit();	
		break;

		case "exit_fire_5":	//navy -->		
			if (CheckAttribute(NPChar, "PGGAi"))
			{				
				pchar.questTemp.FiringOfficerIDX = NPChar.index;
				AddDialogExitQuestFunction("PGG_FireOfficer");
				DialogExit();
				break;
			}	//navy <--	
			Diag.TempNode = "Fired_1";
			OfficersReaction("good");
			Pchar.questTemp.FiringOfficerIDX = GetCharacterIndex(Npchar.id);
			AddDialogExitQuestFunction("LandEnc_OfficerFired");			
			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = true;
			DialogExit();	
		break;

		case "Fired_1":
			Diag.TempNode = "Fired_1";      
			dialog.text = "What now?! We have already talked about everything! Never again I will set foot on your ship.";
			Link.l1 = RandPhraseSimple("Get lost now. Not a big loss, after all.", "Alright, go, then. I will not hold you.");	
			Link.l1.go = "Exit";
		break;

		case "Fired_2":
			Diag.TempNode = "Fired_2"; 
			dialog.text = "Anything else, captain? I thought we had discussed everything already...";
			Link.l1 = "No, nothing. Just wanted to say goodbye...";	 
			Link.l1.go = "Exit";
		break;

		case "Fired_3":
			Diag.TempNode = "Fired_3"; 
			dialog.text = "Captain, we have discussed everything and expressed our claims. You're not going to say that you have changed your mind, are you?";
			Link.l1 = "Alright, go, then. Not a big loss, after all.";	 
			Link.l1.go = "Exit";
		break;

		case "Fired_4":
			Diag.TempNode = "Fired_4"; 
			dialog.text = "Captain, what other questions could there be? Just to tell you, I’m very offended, and I don’t have any desire to return...";
			Link.l1 = "Alright, go, then. Not that I needed you that much.";	 
			Link.l1.go = "Exit";
		break;
		
		// boal 05.09.03 offecer need to go to abordage -->
	    case "Boal_Stay":
            //SetCharacterTask_Stay(Characters[Npchar.index]); // it's a mistic but here doesn't work :(
            //Log_SetStringToLog(Npchar.id +" "+Npchar.index);
            Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(Npchar.id);
            AddDialogExitQuestFunction("LandEnc_OfficerStay");
		    Diag.TempNode = "Hired";
		    dialog.text = "Got it - change of disposition!";
		    Link.l1 = "At ease.";
		    Link.l1.go = "Exit";
		    Npchar.chr_ai.tmpl = LAI_TMPL_STAY;
	    break;
		
	    case "Boal_Follow":
		    SetCharacterTask_FollowCharacter(Npchar, PChar); // it works here!!!
		    Diag.TempNode = "Hired";
		    dialog.text = "Got it - change of disposition!";
		    Link.l1 = "At ease.";
		    Link.l1.go = "Exit";
	    break;
        // boal 05.09.03 offecer need to go to abordage <--

		//////////////////////////////    офицер-наместник -->
		case "Gover_Hire":
            dialog.Text = "That would be an honor!";
            Link.l1 = "Keep order and make the city prosper, and I will be sailing in from time to time to collect the tariffs.";
			Link.l1.go = "Exit_Gover_Hire";
            Link.l2 = "I've changed my mind.";
            Link.l2.go = "Exit";
            Diag.TempNode = "Hired";
        break;

        case "Exit_Gover_Hire":
            sld = GetColonyByIndex(sti(NPChar.ColonyIdx));
            attr = sld.id + "_townhall";

            // снимем пассажира -->
			CheckForReleaseOfficer(sti(NPChar.index));
			RemovePassenger(pchar, NPChar);
			// снимем пассажира <--
		    sld.OfficerIdx = sti(NPChar.index);
			ChangeCharacterAddressGroup(NPChar, attr, "sit", "sit1");
			LAi_SetHuberTypeNoGroup(NPChar);
            SaveCurrentNpcQuestDateParam(NPChar, "StartTaxDate");
            SaveCurrentNpcQuestDateParam(NPChar, "GoverTalkDate");
            LAi_LoginInCaptureTown(NPChar, true);
			//  СЖ -->
			ReOpenQuestHeader("Gen_CityCapture");
            AddQuestRecord("Gen_CityCapture", "t3_1");
			AddQuestUserData("Gen_CityCapture", "sSex", GetSexPhrase("",""));
			AddQuestUserData("Gen_CityCapture", "sCity", XI_ConvertString("colony" + sld.id));
			AddQuestUserData("Gen_CityCapture", "sName", GetFullName(NPChar));
			//  СЖ <--
			Diag.CurrentNode = "Gover_Main";
            DialogExit();
        break;

        case "Gover_Main":
            iTemp = GetNpcQuestPastDayParam(NPChar, "GoverTalkDate");
            if (iTemp > 0)
            {
				dialog.Text = "What are your orders? Last time you visited me " + FindRussianDaysString(iTemp) + " ago.";
			}
			else
			{
			    dialog.Text = "What are your orders?";
			}

            Link.l1 = "How much tax money have you " + NPCharSexPhrase(NPChar, "collected", "collected") + " at this point?";
        	Link.l1.go = "Gover_Tax";
            Link.l8 = "You are needed on the ship, I relieve you from town duty.";
            Link.l8.go = "Gover_Fire";
			Link.l9 = "All the best.";
            Link.l9.go = "Exit";
            Diag.TempNode = "Gover_Main";
            SaveCurrentNpcQuestDateParam(NPChar, "GoverTalkDate");
        break;

        case "Gover_Tax":
            iTemp = GetNpcQuestPastDayParam(NPChar, "StartTaxDate");
            iTax  = makeint((GetCharacterSkillSimple(NPChar, SKILL_COMMERCE) + GetCharacterSkillSimple(NPChar, SKILL_LEADERSHIP)) / 2);
            sld = GetColonyByIndex(sti(NPChar.ColonyIdx));
			if (CheckAttribute(sld, "FortValue"))
			{
			    iFortValue = sti(sld.FortValue);
			}
			else
			{
			    iFortValue = 20;
			}
			NPChar.Gover_Tax_Sum = iFortValue*iTax*iTemp;
			dialog.Text = "My skills allow for collecting " + FindRussianMoneyString(iFortValue*iTax) + " Per day. Over " + FindRussianDaysString(iTemp) + " I " + NPCharSexPhrase(NPChar, "collected", "collected") + " " + FindRussianMoneyString(sti(NPChar.Gover_Tax_Sum)) + ".";
			if (sti(NPChar.Gover_Tax_Sum) > 0)
			{
			    Link.l1 = "I want to take all the collected tax money.";
            	Link.l1.go = "Gover_Tax_Get";
			}
			Link.l2 = "Thanks for the service!";
            Link.l2.go = "Exit";
        break;

        case "Gover_Tax_Get":
            SaveCurrentNpcQuestDateParam(NPChar, "StartTaxDate");
            AddMoneyToCharacter(Pchar, sti(NPChar.Gover_Tax_Sum));

			Diag.CurrentNode = "Gover_Main";
            DialogExit();
        break;

        case "Gover_Fire":
            dialog.Text = "Great! I am no landlubber, you know.";
            Link.l8 = "That's good.";
            Link.l8.go = "exit_hire";
            Diag.TempNode = "Hired";
            sld = GetColonyByIndex(sti(NPChar.ColonyIdx));
            DeleteAttribute(sld, "OfficerIdx");
            //  СЖ -->
			ReOpenQuestHeader("Gen_CityCapture");
            AddQuestRecord("Gen_CityCapture", "t3_2");
			AddQuestUserData("Gen_CityCapture", "sCity", XI_ConvertString("colony" + sld.id));
			AddQuestUserData("Gen_CityCapture", "sName", GetFullName(NPChar));
			//  СЖ <--
        break;
        //////////////////////////////    офицер-наместник <--

		//Указания для компаньона 19.02.08 -->
		case "Companion_Tasks":
			dialog.Text = "I am listening to you.";
			Link.l1 = "This is about boarding.";
			Link.l1.go = "Companion_TaskBoarding";
			Link.l2 = "This is about your ship.";
			Link.l2.go = "Companion_TaskChange";
			if(bBettaTestMode) // Только при бета-тесте
			{
			    Link.l3 = "I want you to leave my squadron for a while and seek fortune on your own.";
			    Link.l3.go = "CompanionTravel";
			}
			Link.l8 = "Nothing so far.";
			Link.l8.go = "exit";
		break;
		
		case "Companion_TaskBoarding":
			dialog.Text = "So what is your wish.";
			Link.l1 = "Don't board enemy ships. Take care of yourself and the crew.";
			Link.l1.go = "Companion_TaskBoardingNo";
			Link.l2 = "I want you to board enemy ships.";
			Link.l2.go = "Companion_TaskBoardingYes";
		break;
		
		case "Companion_TaskChange":
			dialog.Text = "So what is your wish.";
			Link.l1 = "I would like you not to swap your ship for another one after boarding. It's too valuable.";
			Link.l1.go = "Companion_TaskChangeNo";
			Link.l2 = "When you are boarding enemy ships, you can take them for yourself, if they happen to be decent.";
			Link.l2.go = "Companion_TaskChangeYes";
		break;
		
		case "Companion_TaskBoardingNo":
			dialog.Text = "Aye-aye.";
			Link.l1 = "At ease.";
			Link.l1.go = "exit";
			NPChar.Tasks.CanBoarding = false;
		break;
		
		case "Companion_TaskBoardingYes":
			dialog.Text = "It will be done.";
			Link.l1 = "At ease.";
			Link.l1.go = "exit";
			NPChar.Tasks.CanBoarding = true;
		break;
		
		case "Companion_TaskChangeNo":
			dialog.Text = "Aye-aye.";
			Link.l1 = "It will be done.";
			Link.l1.go = "exit";
			NPChar.Tasks.CanChangeShipAfterBoarding = false;
		break;
		
		case "Companion_TaskChangeYes":
			dialog.Text = "It will be done.";
			Link.l1 = "At ease.";
			Link.l1.go = "exit";
			NPChar.Tasks.CanChangeShipAfterBoarding = true;
		break;
		//<--
	
		// Самостоятельное плавание компаньона -->
		case "CompanionTravel":
			if(GetAttrValue(PChar, "CompanionTravel") == 3) // Если уже троих отпустил
			{
				dialog.Text = "Captain, I will not leave your squadron, because you have already dismissed three ships.";
					Link.l1 = "Yes, perhaps, you're right.";
					Link.l1.go = "exit";
				break;
			}
		
			dialog.Text = "No problem, cap. In what town shall we meet?";
			for(iTemp=0; iTemp<MAX_COLONIES; iTemp++)
			{
				sld = &colonies[iTemp];
				attr = sld.ID;
				if(sld.nation == "none" || sld.nation == PIRATE || attr == "Panama" || attr == "FortOrange") continue;
				attrLoc = "l" + iTemp;
				Link.(attrLoc) = "In the " + XI_ConvertString("Colony" + attr + "Dat");
				Link.(attrLoc).go = "CompanionTravelToColony_" + attr;
			}
				Link.l99 = "I have changed my mind.";
				Link.l99.go = "exit";
		break;
			
		case "CompanionTravel_EnemyColony":
			dialog.Text = "Captain, but I can't wait for you in the colony, which is hostile to us!";
				Link.l1 = "You know, forget about all these travels...";
				Link.l1.go = "exit";
		break;
			
		case "CompanionTravel_NoCrew":
			dialog.Text = "Cap, we have almost no sailors in the crew! What journey you're talking about?!";
				Link.l1 = "That's right, we're really short of sailors...";
				Link.l1.go = "exit";
		break;
			
		case "CompanionTravel_NoFood":
			dialog.Text = "Cap, I don't have enough provision on board for such a journey.";
				Link.l1 = "Yeah, you're right. The journey can wait...";
				Link.l1.go = "exit";
		break;
			
		case "CompanionTravel_NoHP":
			dialog.Text = "Cap, but my ship is in a bad condition. It would be unwise for me to set sail alone under such circumstances!";
				Link.l1 = "Yes, you're right. Your ship needs repair.";
				Link.l1.go = "exit";
		break;
		
		case "CompanionTravel_PrepareStart":
			dialog.Text = "I see. Till " + XI_ConvertString("Colony" + characters[sti(NPChar.realcompanionidx)].CompanionTravel.ToColonyID + "Gen") + " to go " + sti(characters[sti(NPChar.realcompanionidx)].CompanionTravel.Days) + " days, what do I do upon arrival?";
				Link.l1 = "Lie off at the port of the colony for a month.";
				Link.l1.go = "CompanionTravel_PrepareStart_2";
				Link.l2 = "You know, I have crossed my mind. Stay with me...";
				Link.l2.go = "exit";
		break;
		
		case "CompanionTravel_PrepareStart_2":
			dialog.Text = "I see, captain. I'll depart at once.";
				Link.l1 = "Yes, please do.";
				Link.l1.go = "CompanionTravel_Start";
		break;
			
		case "CompanionTravel_Start":
			Diag.CurrentNode = "CompanionTravel_LastNode";
			NPChar.quest.meeting = true;
			CompanionTravel_SetTraveller(NPChar);
			DialogExit();
		break;
			
		case "CompanionTravel_LastNode":
			Dialog.text = RandPhraseSimple("Today, I will set sail again...",
			"Don't forget about our meeting in " + XI_ConvertString("Colony" + characters[sti(NPChar.realcompanionidx)].CompanionTravel.ToColonyID + "Dat") + ".");
				link.l2 = "...";
				link.l2.go = "Exit";
				Diag.TempNode = "CompanionTravel_LastNode";
		break;
			
		case "CompanionTravel_ToSquadron":
			if(GetCompanionQuantity(PChar) < COMPANION_MAX)
			{
				dialog.text = "I'd like it, too. From now on, my ship once again is under your command, cap.";
					Link.l1 = "Fine.";
					Link.l1.go = "exit";
					Diag.TempNode = "hired";
					CompanionTravel_DeleteSpecialShipAttributes(NPChar);
					Group_DeleteAtEnd(NPChar.CompanionTravel.GroupID); // Потрем группу
					SetCompanionIndex(PChar, -1, sti(NPChar.index));
					PChar.CompanionTravel = sti(PChar.CompanionTravel) - 1; // Этого компаньона взяли обратно в эскадру
					DeleteAttribute(NPChar, "CompanionTravel");
			}
			else
			{
				dialog.text = "Cap, you already have five ships in your squadron - what are you going to do with the sixth one? Well, I think I'd rather wait for you here on my ship. Your new companions don't seem reliable to me. Their ships will soon sink, and you will come back for me.";
					Link.l1 = "Hey, aren't you smart? You should be an admiral, not just a captain!";
					Link.l1.go = "exit";
					Diag.TempNode = "CompanionTravel_ToSquadron_2";
					NPChar.DeckDialogNode = "CompanionTravel_ToSquadron_2"; // ставим снова эту ноду
			}
		break;
			
		case "CompanionTravel_ToSquadron_2":
			dialog.text = "Oh, captain, you've come back, just as I said. So, is there now a vacant spot in your squadron?";
			if(GetCompanionQuantity(PChar) < COMPANION_MAX)
			{
				Link.l1 = "Yes, " + NPChar.name + ", there is one. Welcome to the squadron.";
				Link.l1.go = "exit";
				Diag.TempNode = "hired";
				CompanionTravel_DeleteSpecialShipAttributes(NPChar);
				Group_DeleteAtEnd(NPChar.CompanionTravel.GroupID);
				SetCompanionIndex(PChar, -1, sti(NPChar.index));
				PChar.CompanionTravel = sti(PChar.CompanionTravel) - 1; // Этого компаньона взяли обратно в эскадру
				DeleteAttribute(NPChar, "CompanionTravel");
			}
			else
			{
				Link.l1 = "Not yet, unfortunately.";
				Link.l1.go = "exit";
				Diag.TempNode = "CompanionTravel_ToSquadron_2";
				NPChar.DeckDialogNode = "CompanionTravel_ToSquadron_2";
			}
		break;
		// <-- Самостоятельное плавание компаньона
	}
}