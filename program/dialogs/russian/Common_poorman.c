#include "DIALOGS\russian\Rumours\Common_rumours.c"
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	ProcessCommonDialogRumors(NPChar, Link, NextDiag);//homo 25/06/06

	switch(Dialog.CurrentNode)
	{
		case "First time":
			// --> калеуче
			if (CheckAttribute(pchar, "questTemp.Caleuche.SeekAmulet") && drand(1) == 0 && sti(Pchar.money) >= 2000) 
			{
				dialog.text = "Look, sir, don't you want to buy one amusing little thing? Take inexpensive, just some few thousand pesos...";
				link.l1 = "Hmm. Probably stole this 'little thing', and now you're trying to shake off it?";
				link.l1.go = "caleuche";
				break;
			}
			// <-- калеуче
			if (npchar.quest.meeting == "0")
			{
				dialog.text = LinkRandPhrase("Hello. My name is " + GetFullName(npchar) + ". I don't hope that you're glad to meet me, but, perhaps, you will at least remember my name...", 
					"Greetings, " + GetAddress_Form(NPChar) +  ". My name is " + GetFullName(npchar) + ".", 
					"My name is " + GetFullName(npchar) + ", " + GetAddress_Form(NPChar) + ". Nice to meet you.");
				link.l1 = RandPhraseSimple("Greetings.", "Hello.");
				link.l1.go = "First time";
				// карибские нравы
				if (CheckAttribute(pchar, "questTemp.Trial") && pchar.questTemp.Trial == "spy_drink" && pchar.location == "portobello_town")
				{
					link.l2 = "Hey, listen, would you like to earn a couple thousand pesos instead of this pathetic alms?";
					link.l2.go = "trial";
				}
				npchar.quest.meeting = "1";
			}			
			else
			{
				dialog.text = NPCStringReactionRepeat("Look how low I fell...", 
					"Living on alms is not easy...", 
					"I'd give everything to break out of this poverty!",
					"You again?..", "block", 1, npchar, Dialog.CurrentNode);

				link.l1 = HeroStringReactionRepeat("I see. Well, no big deal.", 
					"Of course. Well, you know, the greatest man in history was the poorest.",
					"Then you should start to do something, but not sitting here a whole day.", 
					"Ah-ha. Annoying you already?", npchar, Dialog.CurrentNode);
				link.l1.go = DialogGoNodeRepeat("exit", "exit", "exit", "pester", npchar, Dialog.CurrentNode);
				link.l2 = RandPhraseSimple("What do you need?", "What do you want?");
				link.l2.go = "Whants";
				// карибские нравы
				if (CheckAttribute(pchar, "questTemp.Trial") && pchar.questTemp.Trial == "spy_drink" && pchar.location == "portobello_town")
				{
					link.l2 = "Hey, listen, would you like to earn a couple thousand pesos instead of this pathetic alms?";
					link.l2.go = "trial";
				}
				link.l3 = LinkRandPhrase("Can you tell me anything interesting?", 
					"What's new in the town?", "Oh, I'd like to hear the latest gossips...");
				link.l3.go = "rumours_poor";
			}
			NextDiag.TempNode = "First time";
		break;
		case "pester":
			dialog.text = RandPhraseSimple("No, why already annoying? I'm not particularly busy, as you can see...", 
				"Just make me tired. Though I am poor, but still a man.");
			link.l1 = "Heh, I see...";
			link.l1.go = "exit";
		break;
		//выходы
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		//милостыня
		case "Whants":
			if (!CheckAttribute(npchar, "wants_date") || GetNpcQuestPastDayParam(npchar, "wants_date") >= 1 || bBettaTestMode)
    		{
				dialog.text = PCharRepPhrase("Hmm, " + GetAddress_Form(NPChar) +  ", people say a lot of ugly things about you. But I keep believing in people - even in those like you. Please, give me alms for bread and water, have mercy on me.",
					"I beg you, " + GetAddress_Form(NPChar) + "! Please, don't turn awaw from a poor man, give alms for a meal...");
				link.l1 = RandPhraseSimple("I won't give you anything.", "You'll make it without money.");
				link.l1.go = "exit";
				Link.l2 = "Alright, and just how much do you need?";
				Link.l2.go = "Whants_1";
			}
			else
			{
				dialog.text = PCharRepPhrase("From you? Nothing.", "I don't need anything, " + GetAddress_Form(NPChar) + ", thanks.");
				link.l1 = RandPhraseSimple("Hmm, alright.", "Apparently, your life is not nearly as bad, buddy.");
				link.l1.go = "exit";
			}
		break;
		case "Whants_1":
			dialog.text = "I wouldn't reject even a petty copper, " + GetAddress_Form(NPChar) + ". As much as your purse and your mercy can give...";
			Link.l1.edit = 2;			
			link.l1 = "";
			link.l1.go = "Whants_2";
		break;
		case "Whants_2":
			SaveCurrentNpcQuestDateParam(npchar, "wants_date");
			int iTemp = sti(dialogEditStrings[2]);
			if (iTemp <= 0 || sti(pchar.money) < iTemp)
			{
				dialog.text = "Mocking at the weak and weary is a sin...";
				link.l1 = "Ha-ha-ha! You thought for a moment I'd give you money, you deranged beggar?!";
				link.l1.go = "exit";
				ChangeCharacterComplexReputation(pchar,"nobility", -2);
				break;
			}
			if (iTemp > 0 && iTemp <= 100)
			{
				dialog.text = "Thank you for " + FindRussianMoneyString(iTemp) + ", " + GetAddress_Form(NPChar) + ". Now I can buy some bread with that money...";
				link.l1 = "Here, tramp - go fortify yourself a bit.";
				link.l1.go = "exit";
				pchar.money = sti(pchar.money) - iTemp;
				Achievment_SetStat(pchar, 41, 1);
			}
			if (iTemp > 100 && iTemp <= 500)
			{
				dialog.text = "Thank you, " + GetAddress_Form(NPChar) + ". I can now live a week on that money!";
				link.l1 = "It was a pleasure to help.";
				link.l1.go = "exit";
				OfficersReaction("good");
				pchar.money = sti(pchar.money) - iTemp;
				Achievment_SetStat(pchar, 41, 1);
			}
			if (iTemp > 500 && iTemp <= 1000)
			{
				dialog.text = "Thank you, " + GetAddress_Form(NPChar) + ". I will tell everyone about your kindness!";
				link.l1 = "This is not really necessary.";
				link.l1.go = "exit";
				ChangeCharacterComplexReputation(pchar,"nobility", iTemp/2000.0+0.5);
				pchar.money = sti(pchar.money) - iTemp;
				Achievment_SetStat(pchar, 41, 1);
			}
			if (iTemp > 1000 && iTemp <= 5000)
			{
				dialog.text = "Thank you, respected "+ GetSexPhrase("sir","lady") +" " + GetAddress_Form(NPChar) + ". May the Lord watch over you...";
				link.l1 = "Yeah, His protection would certainly not hurt!";
				link.l1.go = "exit";
				ChangeCharacterNationReputation(pchar, sti(NPChar.nation), iTemp/10000.0+0.5);
				pchar.money = sti(pchar.money) - iTemp;
				Achievment_SetStat(pchar, 41, 1);
			}
			if (iTemp > 5000 && iTemp <= 10000)
			{
				dialog.text = "Thank you, "+ GetSexPhrase("most esteemed sir","most esteemed lady") +" " + GetAddress_Form(NPChar) + ". I wish you all the best!";
				link.l1 = "Thank you, buddy.";
				link.l1.go = "exit";
				AddCharacterExpToSkill(pchar, "Leadership", iTemp/5000.0);
				AddCharacterExpToSkill(pchar, "Fortune", iTemp/5000.0);
				pchar.money = sti(pchar.money) - iTemp;
				Achievment_SetStat(pchar, 41, 1);
			}
			if (iTemp > 10000)
			{
				dialog.text = "Listen, " + GetAddress_Form(NPChar) + ", are you crazy or what? You're giving me " + FindRussianMoneyString(iTemp) + "! I cannot take such money, surely there must be a catch... Leave me be!";
				link.l1 = "Well, as you wish...";
				link.l1.go = "exit";
			}
		break;
		
		case "trial":
			dialog.text = "A silly question, senor! Of course, I would! But... what will I have to do? Certainly you aren't gonna give me that money just for my beautiful smile.";
			link.l1 = "Of course, not. Listen now. I am acting on behalf of the governor himself. His grace suspects that someone at the shipyard is deliberately sabotaging the launch of 'Alacantara', his galleon. And his suspicions just grew stronger after a French spy have been caught recently...";
			link.l1.go = "trial_1";
		break;
		
		case "trial_1":
			dialog.text = "";
			link.l1 = "His grace already heard the excuses of the shipwright, but he's not sure he was telling the truth. We need to find out, who is sabotaging the work and why. Go to the docks, take a look around and ask the workers, why the hell 'Alacantara' is still not ready to sail...";
			link.l1.go = "trial_2";
		break;
		
		case "trial_2":
			dialog.text = "";
			link.l1 = "No one will suspect you, you even might get hold of a pile of tobacco. As for me, no one will tell me anything. Everyone will know who I am working for. If you manage to learn anything worthy, you will receive three thousand pesos. Enough to abandon your 'job' for a month at least.";
			link.l1.go = "trial_3";
		break;
		
		case "trial_3":
			dialog.text = "Three thousand pesos? But, esteemed senor...";
			link.l1 = "Are you haggling with me or what? Oh, and if you find out, who's behind all this stalling, you'll get another two thousand. Deal?";
			link.l1.go = "trial_4";
		break;
		
		case "trial_4":
			dialog.text = "Alright, senor. Shouldn't be too difficult - many of my old buddies are working at the docks these days. Hey, I was a sailor too long time ago. Like, ten years ago...";
			link.l1 = "You will be able tell me your life story later. Meet me on the pier at night after eleven. Now go.";
			link.l1.go = "trial_5";
		break;
		
		case "trial_5":
			chrDisableReloadToLocation = true;//закрыть локацию
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload5_back", "none", "", "", "OpenTheDoors", 10.0);
			LAi_RemoveLoginTime(npchar);
			pchar.questTemp.Trial = "spy_poorman";
			pchar.quest.trial_spy_poorman.win_condition.l1 = "Timer";
			pchar.quest.trial_spy_poorman.win_condition.l1.date.hour  = 23.00;
			pchar.quest.trial_spy_poorman.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 0);
			pchar.quest.trial_spy_poorman.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 0);
			pchar.quest.trial_spy_poorman.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 0);
			pchar.quest.trial_spy_poorman.function = "Trial_SetPoormanInPort";
			SetTimerCondition("Trial_ReturnPoormanNorm", 0, 0, 1, false);
			AddQuestRecord("Trial", "15");
		break;
		
		case "trial_6":
			dialog.text = "Good evening, senor...";
			link.l1 = "So? Did you find out anything?";
			link.l1.go = "trial_7";
		break;
		
		case "trial_7":
			dialog.text = "I did, senor, I did. Not sure how does it all agree with what you told me... Have you brought the money? Five thousand pesos.";
			if (sti(pchar.money) >= 5000)
			{
				link.l1 = "Don't worry. Here's your money. Now spit it out.";
				link.l1.go = "trial_8";
			}
			else
			{
				link.l1 = "Information first, and then the money. Come on, don't waste my time!";
				link.l1.go = "trial_fail";
			}
		break;
		
		case "trial_fail":
			dialog.text = "You're trying to cheat on me, senor! If you're not going to pay - go and ask someone else around yourself. And don't even think of reaching for your sword or I'll call the guards!";
			link.l1 = "...";
			link.l1.go = "trial_fail_1";
		break;
		
		case "trial_fail_1":
			chrDisableReloadToLocation = true;//закрыть локацию
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload4_back", "none", "", "", "OpenTheDoors", 10.0);
			pchar.questTemp.Trial = "spy_fail";
			AddQuestRecord("Trial", "16");
			sld = characterFromId("Florian");
			sld.DeckDialogNode = "florian_failspy_5";
		break;
		
		case "trial_8":
			AddMoneyToCharacter(pchar, -5000);
			dialog.text = "So how it goes. 'Alcantara' has been ready to sail since long time, but it didnt't get loaded intentionally, and by order of the governor himself. Well, so I was told. And carpenters are now doing all kinds of different minor work, which does not affect vessel departure\nEveryone is waiting for the arrival of some bark from Cartagena. Thing is 'Alcantara' has, in her captain's opinion, an insufficient stock of gunpowder. So ship has been staying here and waiting for whole days when 'Puebla' will bring gunpowder\nBut everyone thinks that all this waiting is just a wasting of time, so if 'Puebla' doesn't arrive in three days, 'Alcantara' will hit the road without the gunpowder...";
			link.l1 = "Is that so? And who told you that? Name?";
			link.l1.go = "trial_9";
		break;
		
		case "trial_9":
			dialog.text = "One of the sailors from 'Alacantara' - Felipe Dabinho... But that's actually no secret at all, and His Grace governor himself had ordered...";
			link.l1 = "I see. That's what I expected. French spies are in town, but these idiots are blabbing like tradegirls, unbelievable! Any first comer can find out whatever he wants about the plans of His Grace. Oh, that Felipe Dabinho is in serious trouble now! And the boatswain of 'Alacantara' too! It's only his fault that his crew doesn't know a thing about discipline!";
			link.l1.go = "trial_10";
		break;
		
		case "trial_10":
			dialog.text = "Oh... So, you knew it from the start? But why... It's not my fault! You told me to do that!";
			link.l1 = "It wasn't your fault, you shouldn't worry about it, no one's gonna punish you. Now we know that the crew of 'Alacantara' can blab out any information to an enemy - even what's supposed to be kept in a secret. Alright, you can go now. Thanks for your help. Go spend your money.";
			link.l1.go = "trial_11";
		break;
		
		case "trial_11":
			chrDisableReloadToLocation = true;//закрыть локацию
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload4_back", "none", "", "", "OpenTheDoors", 10.0);
			pchar.questTemp.Trial = "spy_win";
			AddQuestRecord("Trial", "17");
			sld = characterFromId("Florian");
			sld.DeckDialogNode = "florian_12";
		break;
		
		// --> калеуче
		case "Caleuche":
			dialog.text = "Pardon me, good sir... I won it in a game of dices against some stranger, I thought that it was charmed healing amulet, but I was wrong... It doesn't cure illnesses, and market traders aren't interested in it. And here you are - the sailor, captain, a learned man, check and you may find it useful\nYes, and for you this couple of thousand is a little sum, but for me it's a piece of bread and a sip of rum for a month. Look, mister...";
			link.l1 = "Okay, show...";
			link.l1.go = "Caleuche_1";
		break;
		
		case "Caleuche_1":
			Log_Info("You got a strange amulet");
			PlaySound("interface\important_item.wav");
			dialog.text = "Here...";
			link.l1 = "So-so... Interesting thing, I agree. I'm sure, it was stolen from the Indian settlements. Okay, I'll take it. Here's your money";
			link.l1.go = "Caleuche_2";
		break;
		
		case "Caleuche_2":
			AddMoneyToCharacter(pchar, -2000);
			dialog.text = "Thank you, sir! I hope, this thing will bring you luck! May Lord protect you!";
			link.l1 = "Good luck, buddy. Don't spend all the money at once in the tavern.";
			link.l1.go = "Caleuche_3";
		break;
		
		case "Caleuche_3":
			DialogExit();
			GiveItem2Character(pchar, "kaleuche_amulet1"); 
		break;
		// <-- калеуче
	}
}
