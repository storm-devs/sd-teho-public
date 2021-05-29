// Диалог начала игры (туториал) 03.10.06 boal
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	ref sld;
	
	switch(Dialog.CurrentNode)
	{
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "Finish_2":
            DoQuestFunctionDelay("Tut_locCamera_2", 0.1);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LAi_RemoveCheckMinHP(Pchar); // снимем проверки
			LAi_SetImmortal(pchar, false);
			LAi_SetPlayerType(pchar);
			InterfaceStates.Buttons.Save.enable = true;
			DoReloadCharacterToLocation(Pchar.HeroParam.Location, Pchar.HeroParam.Group, Pchar.HeroParam.Locator);
		break;
		
		case "ChangePIRATES":
            LAi_SetCitizenTypeNoGroup(NPChar);
            LAi_SetPlayerType(pchar);
			NextDiag.CurrentNode = "Node_5";
			DialogExit();
			pchar.SystemInfo.ChangePIRATES = true;
			LaunchCharacter(pchar);
		break;
		
		case "ChangePIRATES_Jess":
            LAi_SetCitizenTypeNoGroup(NPChar);
            LAi_SetPlayerType(pchar);
			NextDiag.CurrentNode = "Node_5_Jess";
			DialogExit();
			pchar.SystemInfo.ChangePIRATES = true;
			LaunchCharacter(pchar);
		break;
		
		case "Teach_battle_1":
		    LAi_SetPlayerType(pchar);
			NextDiag.CurrentNode = "Teach_6";
			AddDialogExitQuestFunction("Tut_TeachBattle");
			DialogExit();
		break;
		
		case "First time":
			NextDiag.TempNode = "First time";
			EndQuestMovie();
			InterfaceStates.Buttons.Save.enable = false;
			LAi_LockFightMode(Pchar, false);
			LAi_SetActorTypeNoGroup(Pchar);
			LAi_ActorTurnToCharacter(Pchar, NPChar);
			if (pchar.name == "Jessica")
			{
				dialog.text = "You are back, captain, at last! Thanks God, we have almost lost any hope.";
				if (bBettaTestMode)
				{
					link.l0 = "BetaTest - пропустить и начать игру";
					link.l0.go = "Finish_2";
				}
				link.l1 = "Sandro? What the hell has happened? And why I have got so terrible headache?";
				link.l1.go = "Node_1_Jess";
			}
			else
			{
				dialog.text = "Well, captain, now you look like yourself. How do you feel?";
				if (bBettaTestMode)
				{
					link.l0 = "BetaTest - пропустить и начать игру";
					link.l0.go = "Finish_2";
				}
				link.l1 = "Hm... and how was I looking before?";
				link.l1.go = "Node_1";
			}
		break;

        case "Node_1":
			dialog.text = "Like those red-skinned atheists, you were even speaking on their language.";
			link.l1     = "Damn it! Sandro, what the hell are talking about?!";
			link.l1.go  = "Node_2";
		break;
		
		case "Node_1_Jess":
			dialog.text = "You don't remember about that, do you? Sure, somebody else would die from a contusion like that or would be smiling and spoiling his trousers for the rest of his life but it seems that you are a tough one. Though you are weaken and it is a problem for you even to stay on your feet. It is been almost a half a year we were trying to heal you.";
			link.l1     = "Tell me about that contusion, see, I don't remember a thing.";
			link.l1.go  = "Node_2_Jess";
		break;
		
		case "Node_2":
			dialog.text = "Don't worry, you must not worry. Breath the fresh air and take a look at the sea, your head will be fine then. Doctor said that you won't remember anything if you will come around. So don't try to remember, you don't need that.";
			link.l1     = "I am curious about my other option.";
			link.l1.go  = "Node_3";
		break;
		
		case "Node_2_Jess":
			dialog.text = "The Mask ...";
			link.l1     = "Damn it! The Mask has tried to kill me... Nobody can be trusted... And what about Lawrence? Is he alive?";
			link.l1.go  = "Node_3_Jess";
		break;
		
		case "Node_3":
			dialog.text = "Doctor said that it would be an asylum for sure. The split personality he said. And Hopkins and me didn't see any other personality here but you ...";
			link.l1     = "Nonsense! Did it really happen to me?";
			link.l1.go  = "Node_4";
		break;
		
		case "Node_3_Jess":
			dialog.text = "No, thanks God. Oh, I am sorry... He was hanged by the order of the Mask. And the Mask was cut by the Shark so they say. I think that they have deserved it, they were bastards both of them. These scoundrels was a too big trouble for us.";
			link.l1     = "Don't talk dirty about the dead... We can't change the past. God will be there judge... Thank you, pals, for saving me, I won't forget it.";
			link.l1.go  = "Node_4_Jess";
		break;
		
		case "Node_4":
			dialog.text = "I swear you. We were scared too, we would have no idea what to do in case you are dead. And what did those red-ass beggars give you to drink! Well, thanks God, you are fine now. How do you feel?";
			link.l1     = "To drink, you say... looks familiar, I don't remember a thing... Let me to collect my thoughts.";
			link.l1.go  = "ChangePIRATES";
			link.l2     = "I feel fine. Just feels giddy it is just like being drunk...";
			link.l2.go  = "Node_5";
		break;
		
		case "Node_4_Jess":
			dialog.text = "...";
			link.l1     = "Hm... give me a minute, I need to collect my thoughts.";
			link.l1.go  = "ChangePIRATES_Jess";
			link.l2     = "Feeling fine now. Thanks for your concerns, Sandro.";
			link.l2.go  = "Node_5_Jess";
		break;
		
		case "Node_5":
			dialog.text = "Alcohol is forbidden for you now. We don't want your spit personality back. It would be fine to practice in fencing a bit. I bet that you have forgotten how to handle a blade.";
			link.l1     = "You know how to catch me. Well, let's try, I am feeling myself like a bear.";
			link.l1.go  = "Teach_1";
			link.l2     = "Don't worry, my hands are fine in opposite to my head. I'd better go to the port, I have gone too wild.";
			link.l2.go  = "Finish_1";
		break;
		
		case "Node_5_Jess":
			dialog.text = "See, I knew that it all will be well... But a wound in the head is not a joke, it will take time to restore your skills. Don't you like to practice in fencing?";
			link.l1     = "Good idea. Let's check my skills.";
			link.l1.go  = "Teach_1_Jess";
			link.l2     = "No, I don't want. I am sure in my skills.";
			link.l2.go  = "Finish_1";
		break;
		
		case "Finish_1":
			if (pchar.name == "Джессика")
			{
				dialog.text = "....";
				link.l1     = "Well, this means to the new dream! I won't let you down to disappoint you. It is all, I need to land.";
				link.l1.go  = "Finish_2";
				link.l2     = "One bastard less, one bastard more, life is it, Sandro. Will you give me a couple of advices before I land?";
				link.l2.go  = "Advice_1";
			}
			else
			{
				dialog.text = "...";
				link.l1     = "Splendid. Fine, I am going to land... Don't worry  and I won't get lost.";
				link.l1.go  = "Finish_2";
				link.l2     = "If you think that I am not ready?";
				link.l2.go  = "Advice_1";
			}
		break;
		
		case "Advice_1":
			dialog.text = "Well, captain... We need to repair the ship, hire more men and buy supplies. And let's find adventures! Of course, it will be nice to get a letter of marquee in case we are going to pirate. It will grant us all rights to do so and we will be able to tell our families that our job is completely legal. And you will be able to make a name for yourself ...";
			link.l1     = "What else should I know?";
			link.l1.go  = "Advice_2";
			link.l2     = "Splendid. Fine, I am going to land...";
			link.l2.go  = "Finish_2";
		break;
		
		case "Advice_2":
			dialog.text = "You have to know the current prices for goods in the archipelago's stores to trade with a profit. Visit stores personally, ask merchants or pick up gossips.";
			link.l1     = "Go on.";
			link.l1.go  = "Advice_3";
			link.l2     = "Splendid. Fine, I am going to land...";
			link.l2.go  = "Finish_2";
		break;
		
		case "Advice_3":
			dialog.text = "Cannons may got damaged and you will have to replace them. You can also take away the part of them to spare some room for the goods.";
			link.l1     = "Go on.";
			link.l1.go  = "Advice_4";
			link.l2     = "Splendid. Fine, I am going to land...";
			link.l2.go  = "Finish_2";
		break;
		
		case "Advice_4":
			dialog.text = "You have to know something in case we are going to become privateers... Ship masters buy captured ships for a very low prices but you can resell ships with a great profit.";
			link.l1     = "Go on.";
			link.l1.go  = "Advice_5";
			link.l2     = "Splendid. Fine, I am going to land...";
			link.l2.go  = "Finish_2";
		break;
		
		case "Advice_5":
			dialog.text = "Don't spoil your relations with the smugglers, they are able to provide you with a nice income even with a risk to your life.";
			link.l1     = "Go on.";
			link.l1.go  = "Advice_6";
			link.l2     = "Splendid. Fine, I am going to land...";
			link.l2.go  = "Finish_2";
		break;
		
		case "Advice_6":
			dialog.text = "Hire some officers, we don't have any. If your authority is low then you won't be able to hire a lot of officers. In that case you should find people who are able to work on two or tree positions in the same time. Only three know-alls will keep all positions on our ship.";
			link.l1     = "Go on.";
			link.l1.go  = "Advice_7";
			link.l2     = "Splendid. Fine, I am going to land...";
			link.l2.go  = "Finish_2";
		break;

		case "Advice_7":
			dialog.text = "Theft is a not a good deal but sometimes you really need to loot a chest in someone's home, bank or store. Try to wait until the master turns away and only then loot a chest. And remember that you will get troubles if someone notice you. So try to be more agile!";
			link.l1     = "Go on.";
			link.l1.go  = "Advice_8";
			link.l2     = "Splendid. Fine, I am going to land...";
			link.l2.go  = "Finish_2";
		break;

		case "Advice_8":
			dialog.text = "Perhaps, one day you will need to get into the enemy town. Remember well what I am going to say to you now! There are no soldiers on the gates or in the port at night. So you'd better enter the enemy town at night and just try to avoid patrols. Soldiers don't have eyes on their backs and they see things only in front of them and by sides. Sneak to the tavern and wait there until the morning comes and do your business. But stay away from the soldiers anyway.";
			link.l1     = "Go on.";
			link.l1.go  = "Advice_9";
			link.l2     = "Splendid. Fine, I am going to land...";
			link.l2.go  = "Finish_2";
		break;

		case "Advice_9":
			dialog.text = "You can also raise the enemy flag if you have got it and hope on your luck and stealth. The most reliable way is to buy a license of the national trading company and no one will stop you. Just don't forget to raise the right flag it would be silly to try show a Spanish license while your flag is English.";
			link.l1     = "Go on.";
			link.l1.go  = "Advice_10";
			link.l2     = "Splendid. Fine, I am going to land...";
			link.l2.go  = "Finish_2";
		break;

		case "Advice_10":
			dialog.text = "Know that casemates are located in forts so don't look for them in towns.";
			link.l1     = "Thanks. I have got to land.";
			link.l1.go  = "Finish_2";
		break;
		/////   фехт 
		case "Teach_1":
			dialog.text = "Well, let's start then. You were always good in that but I will remind you. There are three attacking moves - normal blow, longe and piercing blow. There is also a protective-attacking circle blow. And a pistol, of course, just to greet your opponent from distance.";
			link.l1     = "Fine, fine, lets get straight to business.";
			link.l1.go  = "Teach_2";
		break;
		
		case "Teach_1_Jess":
			dialog.text = "Well, let's start then. You were always good in that but I will remind you. There are three attacking moves - normal blow, longe and piercing blow. There is also a protective-attacking circle blow. And a pistol, of course, just to greet your opponent from distance.";
			link.l1     = "Go on.";
			link.l1.go  = "Teach_2";
		break;
		
		case "Teach_2":
			dialog.text = "...";
			link.l1     = "I see. Next?";
			link.l1.go  = "Teach_3";
			link.l2     = "What is the energy?";
			link.l2.go  = "Teach_2_1";
		break;
		
		case "Teach_2_1":
			dialog.text = "Energy is the indicator of your stamina in a fight. All attacking moves require some energy. You got tired during the fight and sometimes you need some rest to restore your stamina."+
						  "The maximum of your energy depends on the current value of your reaction.";
			link.l1     = "Go on.";
			link.l1.go  = "Teach_3";
		break;
		
		case "Teach_3":
			dialog.text = "Avoid fighting with the numerous enemies or you'd be dead in seconds. It is possible to fight with two of them but it is not that simple to deal with tree or more enemies at once. Watch their energy when it will be low they wills tart to parry or to feint. Be careful or your head will be cut off soon.";
			link.l1     = "Go on.";
			link.l1.go  = "Teach_4";
		break;
		
		case "Teach_4":
			dialog.text = "If you feint your enemy, he will get a fine damage more than from your longe. And if you will be able to parry, he will loose his energy and a rhythm.";
			link.l1     = "Go on.";
			link.l1.go  = "Teach_5";
		break;
		
		case "Teach_5":
			dialog.text = "All weapons are different. There are light, average and heavy types. The weigh determines the energy losses. You can fight for a long time with a small dagger but a heavy axe will help you to deal with a numerous opponents by one circle bow.";
			link.l1     = "Go on.";
			link.l1.go  = "Teach_6";
		break;
		
		case "Teach_6":
			pchar.HeroParam.Teach_battle = 1;
			Tut_RestoreState();
			dialog.text = "Let's practice a bit? I offer to you to warm up. We will fight for real but not to death. You can heal yourself with elixirs, potions or rum but don't waste them now, it is only a training.";
			link.l1     = "Let's go and don't expect mercy!";
			link.l1.go  = "Teach_battle_1";
			link.l2     = "No, thank, I got it already.";
			link.l2.go  = "Finish_1";
		break;
		
		case "Teach_battle_lose":
			Tut_RestoreState();
			dialog.text = LinkRandPhrase("Well... You are really weak now. Be attentive, block and parry more. Watch for the pierce attack, your block won't save you from it, use feint, parry or try to snap back.","Don't let to hit yourself, catch enemy's blow with you longes or try to parry. Be careful and watch for feints or your lunge will be catched and turned against you.", "Run or jump away if your energy is low. You can try to feint your opponent. Know that it is not easy to feint enemy's blow but you fool him. If you will succeed you will avoid his blow and hit him back.") +
										 "Let's try again?";
			if (sti(pchar.rank) < 3) // чтоб не качались до упора
			{
				link.l1     = "Sure!";
				link.l1.go  = "Teach_battle_1";
			}
			link.l2     = "No, I had enough. I got it.";
			link.l2.go  = "Finish_1";
		break;
		
		case "Teach_battle_win":
			pchar.HeroParam.Teach_battle = 2;
			Tut_RestoreState();
			dialog.text = "Good. Well done! I was fighting with no cheating but your opponents might have their own elixirs and they won't be that easy to be defeated. " +
						  "Well, let's make it a bit more difficult. How about to fight against two opponents at once?";
			link.l1     = "Let's try. Hey, Hopkins! Take your blade and go on board!";
			link.l1.go  = "Teach_battle_1";
			link.l2     = "No thanks, I had enough practice.";
			link.l2.go  = "Finish_1";
		break;
		
		case "Teach_battle_win_2":
			Tut_RestoreState();
			sld = characterFromID("Sailor_2");
			LAi_SetCitizenType(sld);
			if (pchar.name == "Джессика")
			{
				dialog.text = "Well done, captain! Beltrope's lessons was not wasted, he was a good teacher. Now, the last advice. Fighting with the one type of weapon will greatly raise your skill. If you want to restore your skills with every type of blades then change them more often.";
			}
			else
			{
				dialog.text = "Yes, your hands are alright, we were right to hide our blades. Now, the last advice. Fighting with the one type of weapon will greatly raise your skill. If you want to restore your skills with every type of blades then change them more often.";
			}
			link.l1     = "Thanks!";
			link.l1.go  = "Finish_1";
		break;
		
		case "Teach_battle_win_3":
			Tut_RestoreState();
			sld = characterFromID("Sailor_2");
			LAi_SetCitizenType(sld);
			dialog.text = "Well, not bad. You have got one opponent but there were two of them. It needs some practice. Enemies can attack by three or four at once. Lets try again?";
   			if (sti(pchar.rank) < 3) // чтоб не качались до упора
			{
				link.l1     = "Sure!";
				link.l1.go  = "Teach_battle_1";
			}
			link.l2     = "No, I had enough. I got it.";
			link.l2.go  = "Finish_1";
		break;
	}
}
