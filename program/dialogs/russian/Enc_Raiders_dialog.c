void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, Diag;
	int i;
	string sGroup;
	bool bOk, bOk1;
	
	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(Diag, NPChar.Dialog);
	int iTemp = sti(npchar.EncQty);
	string sTemp = "Gang" + locations[FindLocation(npchar.location)].index + "_";

	switch(Dialog.CurrentNode)
	{
		case "exit":
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();			
		break;

		case "exit_Robbed":
			int iMoney = makeint(makeint(Pchar.money)/20)*10;
			AddMoneyToCharacter(pchar, -iMoney);
			AddSimpleRumour(LinkRandPhrase("Have you heard? The local robber " + GetFullName(npchar) + " found a new victim. One captain has got scared and bought off. They say, he gave him " + FindRussianMoneyString(iMoney) + ", he-he... ", 
				"Yeah, captain " + GetFullName(pchar) + ", I already heard that you had to pay " + FindRussianMoneyString(iMoney) + ", to buy off a local bandit, " + GetFullName(npchar) + ". Now that's what I call bad luck! Ha-ha-ha!", 
				"Have you heard that the local bandits attacked one captain? He was totally robbed, he lost " + FindRussianMoneyString(iMoney) + "!"), sti(npchar.nation), 5, 1);
			for(i = 0; i < iTemp; i++)
			{
				sld = CharacterFromID(sTemp + i);
				sld.LifeDay = 0;
				LAi_SetWarriorTypeNoGroup(sld);
				sld.Dialog.CurrentNode = "OnceAgain";
				LAi_SetCheckMinHP(sld, LAi_GetCharacterHP(sld)-1, true, "LandEnc_RaidersBeforeDialog");
			}
			DialogExit();			
		break;

		case "exit_fight":
			sGroup = "RaidersGroup_" + locations[FindLocation(npchar.location)].index;
			for(i = 0; i < iTemp; i++)
			{
				sld = CharacterFromID(sTemp + i);
				LAi_SetWarriorTypeNoGroup(sld);
				LAi_group_MoveCharacter(sld, sGroup);
				LAi_RemoveCheckMinHP(sld);
				LAi_SetImmortal(sld, false);
			}
			LAi_group_SetRelation(sGroup, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups(sGroup, LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck(sGroup, "LandEnc_RaidersAfrer");
			DialogExit();	
			AddDialogExitQuest("MainHeroFightModeOn");
		break;

		case "exit_RunFight":
			AddSimpleRumour(LinkRandPhrase(RandPhraseSimple("Have you heard? That bandit " + GetFullName(npchar) + " has finally found justice. He and his boys tried to rob "+ GetSexPhrase("some captain, but he turned out to be","some lady captain, but she turned out to be") +" a tough nut. So our dear robber shited his pants, ha-ha! That will be a lesson for him! Robbing the local farmers is one thing, but a brave captain is a different story!", 
				"Thank you, captain " + GetFullName(pchar) + ", for finally dealing with the gang of that bandit " + GetFullName(npchar) + ". Those rascals were really a pain in everyone's ass. We were scared to even send couriers to the farm for milk, they could have intercepted them and rob of all the money."), 
				"Have you heard, "+ GetSexPhrase("finally, some captain","finally, some lady captain") +" stopped that rascal " + GetFullName(npchar) + ", who was at 'charge' in the jungle, terrorizing all the local farmers. I do hope, it will stop them from their dirty deeds for long enough...", 
				"Have you heard that local bandit " + GetFullName(npchar) + " and his boys attempted to rob "+ GetSexPhrase("some captain","some lady captain") +"? Bah! Nothing of the sort! That captain turned out to be a tough nut. They say, he chased on these robbers over all the jungle like a shark chases flock of sardines. Thank God that there are still people who can stand up for us at time when the authorities do nothing, too busy with their dark deeds..."), sti(npchar.nation), 5, 1);
			for(i = 0; i < iTemp; i++)
			{
				sld = CharacterFromID(sTemp + i);
				LAi_type_actor_Reset(sld);
				LAi_ActorAfraid(sld, Pchar, true);
				sld.Dialog.CurrentNode = "GetTheHellOut";
			}
			DialogExit();
		break;

		case "exit_noFight":
			for(i = 0; i < iTemp; i++)
			{
				sld = CharacterFromID(sTemp + i);
				sld.LifeDay = 0;
				LAi_SetWarriorTypeNoGroup(sld);
				sld.Dialog.CurrentNode = "GetLost";
				LAi_SetCheckMinHP(sld, LAi_GetCharacterHP(sld)-1, true, "LandEnc_RaidersBeforeDialog");
			}		
			DialogExit();			
		break;

		case "First Time":
			for(i = 0; i < iTemp; i++)
			{
				sld = CharacterFromID(sTemp + i);
				LAi_type_actor_Reset(sld);
				LAi_RemoveCheckMinHP(sld);
				LAi_SetImmortal(sld, false);
			}
			dialog.text = LinkRandPhrase(LinkRandPhrase("Stand where you are and drop your weapon! Your money or your life!",
				"Stand where you are, "+ GetSexPhrase("traveler","lass") +"!) Don't touch your weapon and no sudden moves!",
				"Stand where you are, "+ GetSexPhrase("traveler","lass") +"! This is a toll road. If you wanna pass - pay the toll."),
				LinkRandPhrase("Hey, "+ GetSexPhrase("buddy","lass") +"! Not so fast! I want to see how heavy your purse is.",
				"Would you come closer, friend. I want to hear the jingle of gold in your purse.",
				"Hold on, "+ GetSexPhrase("buddy","lass") +". Me and guys bet on how much gold will fit into your purse. Now we must check it before things get violent."),
				"Don't hurry, "+ GetSexPhrase("traveler","darling") +"! Let's have a heart-to-heart talk, will we?");				
			Link.l1 = LinkRandPhrase(LinkRandPhrase("Why are you saying this nonsense?","What's up?", "What are you talking about?"), "What do you mean?", "Just what are you implying?");
			Link.l1.go = "Node_2";
			Link.l2 = LinkRandPhrase(LinkRandPhrase("Brigands?! Excellent, I was longing for a fight!", 
				"Oh, you're brigands! Hiding from justice, I take it? Well, it seems that justice has just come for you...",
				"Haven't you been taught that bothering strangers with your nonsense is a sign of bad manners? Seems that I have to teach you that lesson..."),
				LinkRandPhrase("Oh, you're an insolent one, aren't you?! I hope that your blade is as sharp as your tongue.",
				"I see that you are a master of your tongue, I hope you are a master of your sword too.",
				"Oh, bandits! So many of your kind were hanged, but you still can't stop walking right to the gallows."),
				LinkRandPhrase(RandPhraseSimple("Oh, brigands! You know, I usually don't waste words with your kind!",
				"What an insolent fellow! Stinks like a steaming pile of shit and still dares to address a decent "+ GetSexPhrase("guy","girl") +"."),
				"I will not waste words with you, but you'll find my pistol quite talkative!",
				"Brigands again! Well, I will not promise you the gallows, but I can surely give you a couple of holes in your belly!"));
			Link.l2.go = "CheckSkills";	
			Link.l3 = LinkRandPhrase("And do you know that a patrolling party is following me closely? I can just give them a whistle and you are done.", 
				RandPhraseSimple("You know, I can call the patrol, aren't you afraid of that? They are nearby. I guess, looking for you.", 
				"A patrolling party has been recently dispatched to find you, and they will be here any moment. You're taking a great risk."),
				RandPhraseSimple("I would advise you to run as fast as you can. A patrolling party is heading this way, I've just talked with their officer.",
				"I would gladly continued our conversation, but I'm afraid the patrol unit that I've just met, won't let our acquaintance come into a close friendship."));
			Link.l3.go = "Node_3";
		break;
		
		case "Node_2":
			dialog.text = LinkRandPhrase(LinkRandPhrase("Don't play a fool! Cash on the nail and maybe then I will let you go!",
				"Haven't you heard about the travelling pay? If you don't part with your gold, you will part with a head!",
				"Heh, this ordinary adventure will cost you a purse... if I don't get angry."),
				RandPhraseSimple("It's very simple. You give us all your gold and then you are free to leave, or you stay here, and we take off all your gold, anyway. But I think that this way is not what you would like, he-he.",
				"Don't pretend you don't understand! Give me your purse if you don't want me to take it from your body!"),
				"I'll explain, if you're so slow-witted - give me all your money, if you cherish your life.");
			Link.l1 = "Goddammit, scoundrel! I only have " + makeint(makeint(Pchar.money)/20)*10 + " pesos.";
			Link.l1.go = "CheckMoney";
			Link.l2 = LinkRandPhrase(LinkRandPhrase("You want my money? Come and get it, and I will see how much you're worth!",
				"How dare you, boor! I'll teach you a lesson of good manners!",
				"What a self-assurance! Well, let's see how you stand against a real "+ GetSexPhrase("sea wolf","girl is old salt") +"!"),
				LinkRandPhrase("You should be flogged for such outrage!",
				"You scoundrels! Pray to your devils about a warm place in the hell!",
				"You should have been hanged long ago, gallows-birds! Well, it seems that I will have to stain my saber with your blood!"),
				RandPhraseSimple("And what makes you think that I will give you my money?",
				"And haven't you noticed that I am well-armed and came here not for a simple walk?"));
			Link.l2.go = "CheckSkills";	
		break;

		case "Node_3":
			bOk = makeint(pchar.reputation.nobility) < 11 || makeint(pchar.reputation.nobility) > 90;  
			if(bOk || GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) == 100 || CheckCharacterPerk(pchar, "Trustworthy") || CheckCharacterPerk(pchar, "SeaDogProfessional"))
			{
				dialog.text = RandPhraseSimple("Damn it! Alright, you may leave. But don't even think to make some noise while you are here!", 
					"This time you got lucky, but next time you'll owe us twice as much! Don't forget to remind us, he-he.");
				Link.l1 = RandPhraseSimple("But of course.", "Run already, while you still can.");
				Link.l1.go = "Exit_NoFight";
			}
			else
			{
				bOk = makeint(pchar.reputation.nobility) < 51 && makeint(pchar.reputation.nobility) > 41; // Captain Beltrop, 23.01.21 - жесть!!! Надо было всего лишь убрать единичку!
				if(!bOk || GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) < 35)
				{
					dialog.text = RandPhraseSimple("We'll slay you quietly, you won't even let out a squeak.", 
						"Goddammit! We'll have to slay you quickly before you will raise alarm.");
					Link.l1 = "Well, this is your funeral. I warned you.";
					Link.l1.go = "Exit_Fight";
				}
				else
				{
					dialog.text = RandPhraseSimple("And why should I care about your patrol? I am paying them. So, give me your purse and stop running your mouth.", 
						"You think you can scare me? I am myself 'the patrol' for those like you in this jungle. No one yet has left without a fee!");
					Link.l1 = "Goddammit, scoundrel! I only have " + makeint(makeint(Pchar.money)/20)*10 + " pesos.";
					Link.l1.go = "CheckMoney";	
					Link.l2 = RandPhraseSimple(LinkRandPhrase("He-h, I'm not gonna obey orders from such a wimp like you.", 
						"I'll make a couple of new holes in your skull 'cause of such impudence! Just to ventilate your brains a bit.",
						"Such impudence won't stay unpunished!"),
						"You should't have done that...");
					Link.l2.go = "CheckSkills";
				}
			}
		break;
		
		case "CheckSkills":
		    bool isStrong = (GetCharacterSkillToOld(Pchar, "FencingL") >= 7) || (GetCharacterSkillToOld(Pchar, "FencingS") >= 7) || (GetCharacterSkillToOld(Pchar, "FencingH") >= 7);
			bool z_ok = (isStrong) && (makeint(Pchar.Rank) >= 8) && (Makeint(PChar.reputation.nobility) <= 30); // Captain Beltrop & mitrokosta, 23.01.21 проверяем на оружие (новый вариант)
			if (z_ok || CheckCharacterPerk(pchar, "SeaDogProfessional"))
			{
				Diag.TempNode = "GetLost";
				dialog.text = LinkRandPhrase(RandPhraseSimple("Hey, don't get so excited, "+ GetSexPhrase("buddy","lass") +"! I was just joking! You can continue your way!",
					"Alright, I have changed my mind. You may go, if you're so formidable."),
					"What, a "+ GetSexPhrase("'gallant captain'","'militant lass'") +"? again? Alright, go in peace...",
					"Quiet, "+ GetSexPhrase("buddy","lass") +". You see, we were mistaken, "+ GetSexPhrase(" we thought you were a merchant","") +". You can go.");
				Link.l1 = LinkRandPhrase(LinkRandPhrase("Alright, until we meet again!",
					"You ought to quit robbering, while you still can.",
					"Alright, but if I ever see you again..."),
					RandPhraseSimple("Next time pay attention whom you are threatening, cur.",
					"Thank God that I am in a good mood today."),	
					RandPhraseSimple("This criminal trade will surely kill in the end. Farewell.",
					"That's a wise decision. Well, good luck!"));
				Link.l1.go = "Exit_NoFight";
				Link.l99 = LinkRandPhrase("No, buddy. Now I'll teach you good manners!",
					"Oh, got scared? Well, one should answer for his deeds, right?",
					"No! Now I will not calm down until I skin you alive!");
				Link.l99.go = "GetTheHellOut";
			}
			else 
			{
				dialog.text = LinkRandPhrase("But you could go in peace! Now blame only yourself!",
								"You shouldn't have started it, you rascal! Now you're gonna die like a dog!",
								"Ah well! I'll tear you to pieces! Cut out the liver and feed the dogs!");
				Link.l1 = RandPhraseSimple("I will stuff your words back into your throat!","Whom are you threatening, scum?!");
				Link.l1.go = "Exit_Fight";
			}
		break;

		case "CheckMoney":
			if(makeint(makeint(Pchar.money)/20)*10 >= makeint(Pchar.rank)*100)
			{
				Diag.TempNode = "OnceAgain";
				dialog.text = LinkRandPhrase(RandPhraseSimple("Alright! Give it to me and get lost!",
					"Not much, but still better than nothing. It's good to deal with a smart person! You're free to go."),
					"Now that's a different story! Like one my friend was saying 'it's always good to listen to someone smart, but talking to the fool is much better'! He-he!",
					"In exchange for your gold I will give you an advice, you should not walk in the jungle, if you're "+ GetSexPhrase("such a wimp. Drink your rum at the tavern, you and your purse will be safety!","a lass. You know, being robbed is not the worst that could have happened to you.") +".");
				Link.l1 = "Damned hanged!";
				Link.l1.go = "Exit_Robbed";				
			}
			else
			{
				dialog.text = "I guess, you're trying to cheat on me! No worry, I'll tickle you with my knife, and maybe something drops down.";
				Link.l1 = "Dammit!";
				Link.l1.go = "Exit_Fight";				
			}				
		break;

		case "OnceAgain":
			Diag.TempNode = "OnceAgain";
			dialog.text = LinkRandPhrase("You again? Run home to your mommy, before I am angry with you!",
				"What? You haven't given me all your gold yet? Ha-ha!",
				"Look, "+ GetSexPhrase("buddy","lass") +", I'm fed up with you! Go away of sight while you're still alive!");
			Link.l1 = "Yeah, I am already leaving.";
			Link.l1.go = "Exit";
			Link.l2 = "I thought that it wouldn't be fair. Therefore I decided to equalize the costs...";
			Link.l2.go = "Exit_Fight";
		break;
				
		case "GetLost":
			Diag.TempNode = "GetLost";
			dialog.text = LinkRandPhrase("What else do you need? We have already agreed that you're leaving!",
				"Leave me be, "+ GetSexPhrase("fellow","lass") +". I mind my own business, you have your own, and we shouldn't try to get along!",
				"Leave now, "+ GetSexPhrase("buddy","lass") +"! Goddammit, are you really willing to give away all your money?");
			Link.l1 = "Yeah, I am already leaving.";
			Link.l1.go = "Exit";
			Link.l2 = "I've remembered that you didn't say goodbye! So let's say - goodbye...";
			Link.l2.go = "Exit_Fight";
		break;

		case "GetTheHellOut":
			Diag.TempNode = "GetTheHellOut";
			dialog.text = LinkRandPhrase("Leave me be! Help me! I want to live!",
				"Help me! "+ GetSexPhrase("He is a maniac","She is a maniac") +"! Don't kill me!",
				"Spare me! I am just a humble brigand! I am too young to die!");
			Link.l1 = LinkRandPhrase(LinkRandPhrase("If you had stayed at home, you would have lived on!",
				"You should have thought about it before!",
				"You should have realized the consequences!"),
				"Sooner or later, this was bound to happen.",
				"Too late to repent - protect yourselves!");
			Link.l1.go = "exit_Fight";			
		break; 				
	}
}
