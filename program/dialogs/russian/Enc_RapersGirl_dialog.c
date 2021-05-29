void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, Diag;
	int i, iRnd, iRnd1;
	string sTemp, sGems;
	
	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(Diag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "exit_1":
			AddDialogExitQuest("LandEnc_RapersTalk");
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();			
		break;
		
		case "exit":
			LAi_SetCitizenTypeNoGroup(NPChar);
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
		break;

		case "Begin_1":
			LAi_RemoveCheckMinHP(npchar);
			for(i = 1; i <= 3; i++)
			{
				if (GetCharacterIndex("GangMan_" + i) == -1) continue;
				sld = CharacterFromID("GangMan_" + i);
				LAi_type_actor_Reset(sld);
			}
			dialog.text = RandPhraseSimple(""+ GetSexPhrase("Captain","Lady") +"! Please, be merciful! Protect me, I'm begging you!","Help! "+ GetSexPhrase("Stranger","Young lady") +", save me, I'm begging you!");
			link.l1 = LinkRandPhrase("What happened?","What's up?",RandPhraseSimple("What's the trouble?","What's happening?"));
			link.l1.go = "Begin_11";
		break;

		case "Begin_2":
			LAi_RemoveCheckMinHP(NPChar);
			for(i = 1; i <= 3; i++)
			{
				if (GetCharacterIndex("GangMan_" + i) == -1) continue;
				sld = CharacterFromID("GangMan_" + i);
				LAi_type_actor_Reset(sld);
			}
			dialog.text = RandPhraseSimple(""+ GetSexPhrase("Captain! Captain","Lass! Lass") +", please hold on!","Hold on, "+ GetSexPhrase("Captain","young lady") +"! Please.");
			link.l1 = LinkRandPhrase("What happened?","What's up?",RandPhraseSimple("What's the trouble?","What's happening?"));
			link.l1.go = "Begin_21";
		break;

		case "Begin_3":
			LAi_RemoveCheckMinHP(NPChar);
			for(i = 1; i <= 3; i++)
			{
				if (GetCharacterIndex("GangMan_" + i) == -1) continue;
				sld = CharacterFromID("GangMan_" + i);
				LAi_type_actor_Reset(sld);
			}
			dialog.text = "Oh, m"+ GetSexPhrase("ister","iss") +"! Please, help a poor girl, I'm begging you! Those people want do to something terrible to me!";
			link.l1 = LinkRandPhrase("What happened?","What's up?",RandPhraseSimple("What's the trouble?","What's happening?"));
			link.l1.go = "Begin_31";
		break;
		
		case "Begin_11":
			dialog.text = RandPhraseSimple("These villains are going to rape me! For all that is good, do not let them!","For God's sake, protect me from these monsters! They are going to dishonor me!");
			link.l1 = "Stop panicking"+ GetSexPhrase(", beauty","") +". What happened here?";
			link.l1.go = "exit_1";
		break;

		case "Begin_21":
			dialog.text = RandPhraseSimple("Rapists are chasing me!"+ GetSexPhrase(" Would you stand up for a lady's honor?","") +"","Captain, "+ GetSexPhrase("be a man","you're a woman, too") +" - save this girl from disgrace!");
			link.l1 = "Stop panicking"+ GetSexPhrase(", beauty","") +". What happened here?";
			link.l1.go = "exit_1";
		break;
		
		case "Begin_31":
			dialog.text = "They are running me down! The bandits! Tell them to leave me alone!";
			link.l1 = "Stop panicking"+ GetSexPhrase(", beauty","") +". What happened here?";
			link.l1.go = "exit_1";
		break;
		
		case "First time":
			LAi_RemoveCheckMinHP(npchar);
			for(i = 1; i <= 3; i++)
			{
				if (GetCharacterIndex("GangMan_" + i) == -1) continue;
				sld = CharacterFromID("GangMan_" + i);
				LAi_type_actor_Reset(sld);
			}
			dialog.text = LinkRandPhrase("Help! Help! They are chasing me! Save me!",
				"Aaah! Help, "+ GetSexPhrase("stranger","young lady") +"! Save me from these scoundrels!",
				"Show mercy and protect me from these scoundrels! Please!");
			Link.l1 = LinkRandPhrase("What's happening?", "What's up?", "What happened?");
			Link.l1.go = "Node_2";			
		break;        

		case "Node_2":
			dialog.text = LinkRandPhrase("They... they are going to rape me! For all that is good, do not let them! Please!",
				"These beasts... they are planning something horrible... Protect me from them, please!",
				"In the name of our Lord - save me from these lustful beasts! They want to dishonor me!");
			Link.l1 = "Let's figure it all out, then.";
			Link.l1.go = "exit_1";			
		break;

		case "ThanksForHelp":
			if(pchar.GenQuest.EncGirl == "Begin_11")
			{
				if(rand(1) == 0)
				{
					dialog.text = RandPhraseSimple("Thank you, "+ GetSexPhrase("Captain","young lady") +". I was so frightened!","Thank you for saving me! I am so grateful to you!");
					link.l1 = "Alright, "+ GetSexPhrase("beauty","deary") +", calm down, it's all in the past.";
					link.l1.go = "Node_11";
				}
				else
				{
					dialog.text = "Oh, thank you, "+ GetSexPhrase("noble man! You are a real gentleman!","lady! You've saved me!") +"";
					link.l1 = "I could not do otherwise.";
					link.l1.go = "Node_12";
				}
			}
			if(pchar.GenQuest.EncGirl == "Begin_22")
			{
				if(rand(1) == 0)
				{
					dialog.text = "Oh, thank you, "+ GetSexPhrase("noble man! You are a real gentleman!","stranger! You've saved me!") +"";
					link.l1 = "I could not do otherwise.";
					link.l1.go = "Node_12";	
				}
				else
				{
					dialog.text = "What have you done? Why have you killed them?! Now they will look for me! My God, what have I done to deserve this!";
					link.l1 = "Now that's a gratitude!";
					link.l1.go = "Node_22";
				}
			}
			if(pchar.GenQuest.EncGirl == "Begin_33")
			{
				dialog.text = "What have you done, "+ GetSexPhrase("captain","young lady") +"?! Why have you killed them? They've been actually sent by my father... Oh my, now he's gonna kill me for sure...";
				link.l1 = "That's the news! And what were you thinking crying out that you were chased by bandits?!";
				link.l1.go = "Node_31";
			}
		break;
		
		case "Node_11":
			Diag.TempNode = "Node_1Next";
			addMoneyToCharacter(pchar, makeint((sti(pchar.rank))*25 + frand(2)*500));
			dialog.text = "I have some money - please, accept it as a token of my gratitude. I will now tell everyone, "+ GetSexPhrase("what a good and noble man you are","what a good and noble woman you are") +".";
			link.l1 = "Sure you will. Thanks... Now just go home.";
			link.l1.go = "exit";
			pchar.GenQuest.EncGirl = "close";
			sGlobalTemp = "Saved_CangGirl";
			Diag.CurrentNode = Diag.TempNode;
		break;
		
		case "Node_12":
			dialog.text = "I still cannot put myself together. Could you please bring "+ GetSexPhrase("a lady","me") +" to the settlement of " + XI_ConvertString("Colony" + pchar.GenQuest.EncGirl.city) + "? You know, now rapists are seem to me behind in every bush.";
			link.l1 = RandPhraseSimple("Don't worry so much, really... Alright, let's get going.","You're such a coward, aren't you? Alright, I'll bring you there.");
			link.l1.go = "Node_121Next";
			link.l2 = "I am sorry, darling, but I simply have no time - too busy.";
			link.l2.go = "Node_3End";
		break;
						
		case "Node_22":
			dialog.text = "I was thinking you'd just scare them off! Now you must take me to the tavern in the settlement of " + XI_ConvertString("Colony" + pchar.GenQuest.EncGirl.city) + ", I have no one else but you whom I could ask for help.";
			link.l1 = "Oh, damn! Alright, let's go. Just don't fall behind.";
			link.l1.go = "Node_122Next";
			link.l2 = "No, that's it, "+ GetSexPhrase("beauty","deary") +"! I've had enough surprises for today. Look for somebody else to help you.";
			link.l2.go = "Node_3End";
		break;
		
		case "Node_31":
			dialog.text = "And what did I have to do?! My father wants me to marry the usurer's son, that milksop... just because his daddy has a crapload of money in his coffers! But I love another man! Take me to him, please...";
			link.l1 = "What a burden you are! Well, alright, let's go - I cannot just leave you here now, can I?.. What's the name of your chosen one, where shall I take you to?";
			link.l1.go = "Node_32";
			link.l2 = "No, that's it, "+ GetSexPhrase("beauty","deary") +"! I've had enough surprises for today. Look for somebody else to help you.";
			link.l2.go = "Node_3End";
		break;
		
		case "Node_32":
			pchar.GenQuest.EncGirl.sLoverId = GenerateRandomName(sti(npchar.nation), "man"); 
			dialog.text = "His name is " + pchar.GenQuest.EncGirl.sLoverId + ", he's a newcomer. Right now he stays at the settlement of " + XI_ConvertString("Colony" + pchar.GenQuest.EncGirl.city) + ", tried to find a job there, but these are hard times. Everybody keeps talking about a crisis... And now there is no coming back home for me, anyway.";
			link.l1 = "A crisis? Ha... For a real pirate, a crisis is when there is a trade caravan at the horizon - and no wind whatsoever to fill the sails...";
			link.l1.go = "Node_12Next";
		break;
		
		case "Node_12Next":
			pchar.quest.LandEnc_RapersBadExit.over = "yes";
			Diag.TempNode = "Node_12End";
			Diag.CurrentNode = Diag.TempNode;
			pchar.GenQuest.EncGirl = "FindLover";
			pchar.GenQuest.EncGirl.MeetSoldiers = 2;
			AddDialogExitQuestFunction("EncGirl_GirlFollow");
			DialogExit();
		break;
		
		case "Node_121Next":
			pchar.quest.LandEnc_RapersBadExit.over = "yes";
			Diag.TempNode = "Node_253";
			pchar.GenQuest.EncGirl = "FindCoins";
			pchar.GenQuest.EncGirl.MeetSoldiers = 1;
			Diag.CurrentNode = Diag.TempNode;
			pchar.quest.EncGirl_DeliveBack.win_condition.l1 = "location";
			pchar.quest.EncGirl_DeliveBack.win_condition.l1.location = pchar.GenQuest.EncGirl.city + "_town";
			pchar.quest.EncGirl_DeliveBack.function = "EncGirl_DeliveBack";
			AddDialogExitQuestFunction("EncGirl_GirlFollow");
			DialogExit();
		break;
		
		case "Node_122Next":
			pchar.quest.LandEnc_RapersBadExit.over = "yes";
			Diag.TempNode = "Node_12End";
			pchar.GenQuest.EncGirl = "HorseToTavern";
			pchar.GenQuest.EncGirl.MeetSoldiers = 1;
			Diag.CurrentNode = Diag.TempNode;
			pchar.quest.EncGirl_DeliveBack.win_condition.l1 = "location";
			pchar.quest.EncGirl_DeliveBack.win_condition.l1.location = pchar.GenQuest.EncGirl.city + "_tavern";
			pchar.quest.EncGirl_DeliveBack.function = "EncGirl_DeliveBack";		
			AddDialogExitQuestFunction("EncGirl_GirlFollow");
			DialogExit();
		break;
		
		case "Node_12End":
			Diag.TempNode = "Node_12End";
			dialog.text = RandPhraseSimple("You know, "+ GetSexPhrase("captain","young lady") +"? I was so scared - my pins are still a little wobbly.","Oh, you know, I was so frightened. It's great that God had sent you my way.");
			link.l1 = RandPhraseSimple("Thank God you're still alive.","Don't take that to heart. It's good that it ended up like this, you know.");
			link.l1.go = "exit";
		break;
		
		case "Node_1Next":
			dialog.text = RandPhraseSimple("Thank you, "+ GetSexPhrase("captain","young lady") +", once again. Really, I am so indebted to you.","Thank you so much, "+ GetSexPhrase("captain","young lady") +". I have no idea what would I do without your help.");
			link.l1 = RandPhraseSimple("That should be a lesson to you. Alright, best of luck...","Next time you should be more careful... Now, run home, and I've got things to do.");
			link.l1.go = "Node_1End";
			link.l2 = "How could you be so careless? Why have you headed into the jungle alone?";
			link.l2.go = "Node_13";
		break;
		
		case "Node_1End":
			sTemp = LAi_FindNearestFreeLocator2Pchar("reload");
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", sTemp, "none", "", "","OpenTheDoors", -1.0);
			pchar.GenQuest.EncGirl = "close";
			sGlobalTemp = "Saved_CangGirl";
			DialogExit();
			AddDialogExitQuest("pchar_back_to_player");			
		break;
		
		case "Node_3End":
			Diag.TempNode = "Node_3Final";
			sTemp = LAi_FindNearestFreeLocator2Pchar("reload");
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", sTemp, "none", "", "","OpenTheDoors", -1.0);
			pchar.GenQuest.EncGirl = "close";
			sGlobalTemp = "Saved_CangGirl";
			ChangeCharacterComplexReputation(pchar,"nobility", -3);
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
		break;
		
		case "Node_3Final":
			Diag.TempNode = "Node_3Final";
			dialog.text = RandPhraseSimple("Have you changed your mind?","Captain, it's great that you have changed your mind!");
			link.l1 = RandPhraseSimple("No-no, darling, I'll pass.","Have no false hopes...");
			link.l1.go = "exit";
		break;
		
		case "Node_13":
			if(pchar.GenQuest.EncGirl == "FindCoins") 
			{
				pchar.quest.LandEnc_RapersBadExit.win_condition.l1 = "ExitFromLocation";
				pchar.quest.LandEnc_RapersBadExit.win_condition.l1.location = pchar.location;
				pchar.quest.LandEnc_RapersBadExit.win_condition = "LandEnc_RapersBadExit";
			}
			pchar.GenQuest.EncGirl = "Begin_11";
			switch(sti(pchar.GenQuest.EncGirl.variant))
			{
				case 0:
					if(rand(1) == 0)
					{
						dialog.text = "You will probably laugh at me, but... I was collecting a love potion... A witch told me there was a root which can help in love affairs.";
						link.l1 = "Oh my god! What "+ GetSexPhrase("are these women thinking of","were you thinking of") +"?! Apparently, you have collected a lot - there were quite some suitors chasing you, I've had a hard time beating them all off. Ha-ha-ha-ha... Goodbye.";
						link.l1.go = "Node_1End";
					}
					else
					{
						dialog.text = "I just went out for a stroll to collect some herbs and get some fresh air. Apparently, it was not the best time for walking.";
						link.l1 = "What a carelessness?! Thank God it ended up like that. Well, best of luck to you.";
						link.l1.go = "Node_1End";
					}
				break;
				case 1:
					dialog.text = "My mistress spilled the pearls of here necklace somewhere here, when she was on a promenade. As she came home, she shouted at me and ordered to go out and collect them. 'Don't even show your face here until you collect them all,' - that's what she said... And I don't even know the exact place. Besides - how am I supposed to find them anyway in this thick grass? The pearls are so small... So, I am just wandering here without a clue what to do...";
					link.l1 = "And what kind of a necklace was it? Perhaps, it'd be easier to simply buy a new one rather that wandering in the jungle? How many pearls has your mistress lost?";
					link.l1.go = "Node_131";
				break;
				case 2:
					dialog.text = "My late father left me a map, and his companions wanted to take it from me. While he was alive, they were all trembling before him, but just as I had buried him, troubled times began. First they attempted to buy this map from me, but I refused, and they started to intimidate me.";
					link.l1 = "And why didn't you just sell it? What's so special about this map, that pirate gangs are looking for it?";
					link.l1.go = "Node_132";
				break;
			}	
		break;
		
		case "Node_131":
			pchar.GenQuest.EncGirl.SmallCoins = rand(25) + 20;
			pchar.GenQuest.EncGirl.BigCoins = rand(15) + 5;
			dialog.text = "That necklace was composed of select pearls - those cannot be bought for cheap. There were " + sti(pchar.GenQuest.EncGirl.BigCoins) + " large pearls and " + sti(pchar.GenQuest.EncGirl.SmallCoins) + " smaller ones. If those pearls were found, we could commission another necklace like that one.";
			link.l1 = "Surely this will not be an easy job... Well, if your mistress gave you an order - there's not much you can do. Try to find the pearls. Good luck.";
			link.l1.go = "Node_131End";
			link.l2 = "It's useless. It'd be easier to find a needle in the haystack than the pearls in this thick grass. Not to mention that you don't even know the place where the pearls were lost...";
			link.l2.go = "Node_133";
		break;
		
		case "Node_131End":
			Diag.TempNode = "Node_12End";
			pchar.GenQuest.EncGirl = "close";
			sGlobalTemp = "Saved_CangGirl";
			ChangeCharacterComplexReputation(pchar,"nobility", -2);
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
			pchar.quest.LandEnc_RapersBadExit.win_condition.l1 = "ExitFromLocation";
			pchar.quest.LandEnc_RapersBadExit.win_condition.l1.location = pchar.location;
			pchar.quest.LandEnc_RapersBadExit.win_condition = "LandEnc_RapersBadExit";
			AddDialogExitQuest("pchar_back_to_player");			
		break;
		
		case "Node_132":
			pchar.GenQuest.EncGirl.mapOwner = "l" + rand(GetNamesCount(NAMETYPE_ORIG) - 1); 
			dialog.text = "My father marked a place on it where he had hidden his treasure. Have you heard about famous pirate " + GetName( NAMETYPE_ORIG, pchar.GenQuest.EncGirl.mapOwner, NAME_VOC) + "?";
			link.l1 = "No, never heard of him.";
			link.l1.go = "Node_132_1";
		break;
		
		case "Node_132_1":
			dialog.text = "Well, " + GetName( NAMETYPE_ORIG, pchar.GenQuest.EncGirl.mapOwner, NAME_NOM) + " was my father. Everyone was scared of him, no one would dare to utter a word. Now they've become brazen, of course. When I refused to sell the map to them, they claimed that they, too, must have their share of the treasure. I wanted to hide the map, but they'd still tracked me down...";
			link.l1 = "And why would you hide it, in the first place? Charter a ship and go claim your treasure. Your parent would not have hidden it all for nothing.";
			link.l1.go = "Node_132_2";
		break;
		
		case "Node_132_2":
			dialog.text = "Easier to say than do. I have no money to charter a ship, and... I am afraid... How am I supposed to dig it all out, carry it to the ship... And where would I take the treasure afterwards? Anybody will make an easy prey of me along the way...";
			link.l1 = "That's a point... Alright, go ahead and hide your map, then. Just remember the place well.";
			link.l1.go = "Node_132_2End";
			if(GetCharacterItem(pchar, "map_full") == 0)
			{
				link.l2 = "Hmm... That's probably true. All the more so, you should have sold it.";
				link.l2.go = "Node_132_3";
			}
			link.l3 = "Have you tried to find a companion?";
			link.l3.go = "Node_132_8";	
		break;
		
		case "Node_132_2End":
			Diag.TempNode = "Node_12End";
			pchar.GenQuest.EncGirl = "close";
			sGlobalTemp = "Saved_CangGirl";
			sTemp = LAi_FindNearestFreeLocator2Pchar("reload");
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", sTemp, "none", "", "","OpenTheDoors", -1.0);
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
			AddDialogExitQuest("pchar_back_to_player");			
		break;
		
		case "Node_132_3":
			dialog.text = "It grieves me to lose such an opportunity... Dad told me about the treasures he'd hidden there. No one would pay me that much...";
			link.l1 = "Well, don't sell it for too cheap. And, anyway, gold is not worth losing one's head for it. Not to mention that this is the easiest way for you - you just collect your money and rid yourself of all troubles...";
			link.l1.go = "Node_132_4";
		break;
		
		case "Node_132_4":
			pchar.GenQuest.EncGirl.mapPrice = 20000 + 500 * sti(pchar.rank);
			dialog.text = "That sounds tempting... And how much can you offer me for it?";
			link.l1 = "I don't think it can be worth more than " + sti(pchar.GenQuest.EncGirl.mapPrice) + " pesos.";
			link.l1.go = "Node_132_5";
		break;
		
		case "Node_132_5":
			if((GetSummonSkillFromName(pchar, SKILL_COMMERCE) + GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) + GetSummonSkillFromName(pchar, SKILL_FORTUNE)) > (rand(220) + 100) && (makeint(pchar.money) >= sti(pchar.GenQuest.EncGirl.mapPrice)))
			{
				dialog.text = "Heh, a woman's lot is never light... Alright, I agree. Finally this nightmare will be over... Perhaps, it's best that this map belongs to you"+ GetSexPhrase(" - a noble gentleman","") +", than to that rascals.";
				link.l1 = "Good. Here's your money - just try not to spend it all at once.";
				link.l1.go = "Node_132_6";
			}
			else
			{
				dialog.text = "No, "+ GetSexPhrase("captain","young lady") +". I will not sell it. I will marry a good man, and then we'll claim the treasure together.";
				link.l1 = "Well, that's up to you to decide. Your piece of paper is not worth more, anyway.";
				link.l1.go = "Node_132_2End";
			}	
		break;
		
		case "Node_132_6":
			AddMoneyToCharacter(pchar, -makeint(sti(pchar.GenQuest.EncGirl.mapPrice))); 
			ref rMap = ItemsFromID("map_full"); // mitrokosta фикс пустой карты
			FillMapForTreasure(rMap);
			GiveItem2Character(pchar, "map_full");
			Diag.TempNode = "Node_12End";
			pchar.GenQuest.EncGirl = "close";
			sGlobalTemp = "Saved_CangGirl";
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
			AddDialogExitQuest("pchar_back_to_player");			
		break;
		
		case "Node_132_8":
			dialog.text = "And where will I find them? The young ones are not reliable, and they don't care much for treasures. And I fear the older ones - they all look too much like my dad's pals. So cunning and treacherous - you would never know what to expect of them.";
			link.l1 = "Ha-ha-ha... Alright, but will you take me with you?";
			link.l1.go = "Node_132_9";
		break;
		
		case "Node_132_9":
			dialog.text = "You? And would you go? But then you'll have to bring me back here, to the settlement of " + XI_ConvertString("Colony" + pchar.GenQuest.EncGirl.city) + ", alright?";
			link.l1 = "Fine. Just show me the way.";
			link.l1.go = "Node_132_10";
		break;
		
		case "Node_132_10":
			EncGirl_GenQuest_GetChestPlaceName();
			dialog.text = "The treasure is hidden in the cave on " + XI_ConvertString(pchar.GenQuest.EncGirl.islandId + "Acc") + ", we need to land at " + XI_ConvertString(pchar.GenQuest.EncGirl.shoreId + "Gen") + ", the place I'll show myself... But don't forget, you will get only a half!";
			link.l1 = "Alright, I won't cheat on you, I promise. Follow me and don't fall back.";
			link.l1.go = "Node_132_11";
		break;
		
		case "Node_132_11":
			ReOpenQuestHeader("JungleGirl");
			AddQuestRecord("JungleGirl", "4");
			AddQuestUserData("JungleGirl", "sName", pchar.GenQuest.EncGirl.name);
			AddQuestUserData("JungleGirl", "sPirateName", GetName( NAMETYPE_ORIG, pchar.GenQuest.EncGirl.mapOwner, NAME_GEN));
			AddQuestUserData("JungleGirl", "sTreasureLoc", XI_ConvertString(pchar.GenQuest.EncGirl.islandId));
			AddQuestUserData("JungleGirl", "sShore", XI_ConvertString(pchar.GenQuest.EncGirl.shoreId + "Gen"));
			AddQuestUserData("JungleGirl", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.EncGirl.city));
			pchar.quest.EncGirl_Death.win_condition.l1 = "NPC_Death";
			pchar.quest.EncGirl_Death.win_condition.l1.character = npchar.id;
			pchar.quest.EncGirl_Death.function = "EncGirl_Death";
			pchar.quest.EncGirl_FindChest.win_condition.l1 = "location";
			pchar.quest.EncGirl_FindChest.win_condition.l1.location = pchar.GenQuest.EncGirl.placeId;
			pchar.quest.EncGirl_FindChest.function = "EncGirl_FindChest";
			SetFunctionExitFromLocationCondition("EncGirl_AddPassenger", pchar.location, false);
			SetFunctionLocationCondition("EncGirl_DialogAtShore", pchar.GenQuest.EncGirl.shoreId, false);
			Diag.TempNode = "Node_12End";
			pchar.GenQuest.EncGirl = "GetChest";
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
			AddDialogExitQuest("pchar_back_to_player");			
		break;
		
		case "Node_132_11_1":
			dialog.text = "Captain, now we must find the cave.";
			link.l1 = "Alright, let's take a look now.";
			link.l1.go = "exit";
			Diag.TempNode = "Node_132_11_2";
			Diag.CurrentNode = Diag.TempNode;
			AddDialogExitQuestFunction("EncGirl_GirlFollow");
		break;
		
		case "Node_132_11_2":
			Diag.TempNode = "Node_132_11_2";
			dialog.text = "Captain, we must find the cave.";
			link.l1 = "Alright, let's take a look now.";
			link.l1.go = "exit";
		break;
		
		case "Node_132_12":
			dialog.text = "Here! I found it! Just like my father said - a huge pile of treasure! A half is yours - as per our deal.";
			link.l1 = "See? That wasn't hard, so there was nothing to fear.";
			link.l1.go = "Node_132_13";
		break;
		
		case "Node_132_13":
			dialog.text = "Ha-ha-ha! I am rich now! Will you take your share now?";
			link.l1 = "I guess.";
			link.l1.go = "Node_132_15";
		break;
		
		case "Node_132_15":
			dialog.text = "Then take it and please help me in carrying all that stuff to the ship. Do you still remember that you promised to take me back home?";
			link.l1 = "I haven't forgotten! Sure, I'll take you.";
			link.l1.go = "Node_132_16";
		break;
		
		case "Node_132_16":
			pchar.quest.EncGirl_DeathSimple.over = "yes";
			PChar.quest.EncGirl_DialogAtShore.over = "yes";// лесник . снял прерывание  , если не с той бухты зашел.		
			LAi_LocationDisableMonstersGen(pchar.location, false);
			chrDisableReloadToLocation = false;
			Log_Info("You have received your share of the treasure");
			PlaySound("interface\important_item.wav");
			TakeNItems(pchar, "icollection", 1+drand(1));
			TakeNItems(pchar, "chest", 2+drand(6));
			TakeNItems(pchar, "jewelry1", 30+drand(15));
			TakeNItems(pchar, "jewelry2", 30+drand(15));
			TakeNItems(pchar, "jewelry3", 30+drand(15));
			TakeNItems(pchar, "jewelry4", 30+drand(15));
			TakeNItems(pchar, "jewelry5", 30+rand(10));
			TakeNItems(pchar, "jewelry6", 10+rand(10));
			TakeNItems(pchar, "jewelry42", 20+rand(10));
			TakeNItems(pchar, "jewelry44", 30+rand(10));
			TakeNItems(pchar, "jewelry46", 50+rand(20));
			AddQuestRecord("JungleGirl", "6");
			AddQuestUserData("JungleGirl", "sSex", GetSexPhrase("",""));
			AddQuestUserData("JungleGirl", "sPirateName", GetName( NAMETYPE_ORIG, pchar.GenQuest.EncGirl.mapOwner, NAME_GEN));
			AddQuestUserData("JungleGirl", "sName", pchar.GenQuest.EncGirl.name);
			AddQuestUserData("JungleGirl", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.EncGirl.city));		
			pchar.GenQuest.EncGirl = "ChestGetted";
			pchar.quest.EncGirl_DeliveBack.win_condition.l1 = "location";
			pchar.quest.EncGirl_DeliveBack.win_condition.l1.location = pchar.GenQuest.EncGirl.city + "_town";
			pchar.quest.EncGirl_DeliveBack.function = "EncGirl_DeliveBack";
			pchar.quest.EncGirl_DeathAgain.win_condition.l1 = "NPC_Death";
			pchar.quest.EncGirl_DeathAgain.win_condition.l1.character = npchar.id;
			pchar.quest.EncGirl_DeathAgain.function = "EncGirl_DeathAgain";
			Diag.TempNode = "Node_132_17";
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
			AddDialogExitQuestFunction("EncGirl_GirlFollow");
			pchar.quest.EncGirl_AddPassenger.win_condition.l1 = "location";// лесник на корабль девицу. 
			pchar.quest.EncGirl_AddPassenger.win_condition.l1.location = pchar.location.from_sea;
			pchar.quest.EncGirl_AddPassenger.function = "EncGirl_AddPassenger";
		break;
		
		case "Node_132_17":
			Diag.TempNode = "Node_132_17";
			dialog.text = "Being rich is simply great! I feel so different now."; 
			link.l1 = "I am glad for you.";
			link.l1.go = "exit";
		break;
		
		case "Node_132_18":
			dialog.text = "Alright, captain. My journey is over now. Thanks for your help.";
			link.l1 = "You're welcome... So, what are you planning to do with your newfound riches? Buying a plantation with slaves?";
			link.l1.go = "Node_132_19";
		break;
		
		case "Node_132_19":
			dialog.text = "I don't know, I haven't decided yet. Perhaps, I'll move to Europe...";
			link.l1 = "Alright, good luck to you.";
			link.l1.go = "Node_132_20";
		break;
		
		case "Node_132_20":
			dialog.text = "Hold on... That trinket was among my father's treasures. I have no use for it, but you might like it. Please, accept it as my personal gratitude for what you've done for me. That's from my share, ha-ha-ha!";
			link.l1 = "Wow, now that's a really nice gift. Thank you"+ GetSexPhrase(", beauty","") +". Find a nice groom for yourself...";
			link.l1.go = "Node_132_21";
		break;
		
		case "Node_132_21":
			chrDisableReloadToLocation = false;		
			RemovePassenger(pchar, npchar);			
			GiveItem2Character(pchar, pchar.GenQuest.EncGirl.item); 
			AddQuestRecord("JungleGirl", "8");
			AddQuestUserData("JungleGirl", "sSex", GetSexPhrase("",""));
			AddQuestUserData("JungleGirl", "sName", pchar.GenQuest.EncGirl.name);
			CloseQuestHeader("JungleGirl");
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeDay = 0;
			DeleteAttribute(pchar, "GenQuest.EncGirl");
			DialogExit();
			AddDialogExitQuest("pchar_back_to_player");			
            LAi_SetActorType(npchar); // отправил восвояси чтоб не стояла. лесник.
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "OpenTheDoors", -1.0);
            pchar.quest.EncGirl_EnterToSea.over = "yes";// лесник . снял прерывание  , если не с той бухты зашел.	
            PChar.quest.EncGirl_DialogAtShore.over = "yes";// лесник . снял прерывание  , если не с той бухты зашел.						
		break;
		
		case "Node_133":
			dialog.text = "But what can I do? I cannot ignore orders of my mistress - she will skin me alive.";
			link.l1 = "Wait for me in the church of the settlement of " + XI_ConvertString("Colony" + pchar.GenQuest.EncGirl.city) + ", I'll bring you the pearls to make a new necklace.";
			link.l1.go = "Node_133_1";
			if(sti(pchar.money) >= 15000)
			{
				link.l2 = "Here. Take these 15000 pesos. That should be more than enough to select the pearls for the necklace, or to buy a new one.";
				link.l2.go = "Node_135";
			}							
		break;
		
		case "Node_133_1":
			pchar.GenQuest.EncGirl = "GetCoins";
			pchar.quest.EncGirl_Coins.win_condition.l1 = "ExitFromLocation";
			pchar.quest.EncGirl_Coins.win_condition.l1.location = pchar.location;
			pchar.quest.EncGirl_Coins.function = "EncGirl_toChurch";
			pchar.quest.EncGirl_GetCoins.win_condition.l1 = "Timer";
			pchar.quest.EncGirl_GetCoins.win_condition.l1.date.day = GetAddingDataDay(0, 0, 10);
			pchar.quest.EncGirl_GetCoins.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 10);
			pchar.quest.EncGirl_GetCoins.win_condition.l1.date.year = GetAddingDataYear(0, 0, 10);
			pchar.quest.EncGirl_GetCoins.function = "EncGirl_GenQuest_GetCoins";	
            sTemp = LAi_FindNearestFreeLocator2Pchar("reload");// лесник - девица убегает если ГГ сказал ждать в цервки
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", sTemp, "none", "", "","OpenTheDoors", -1.0);			
			Diag.TempNode = "Node_134"; 
			Diag.CurrentNode = Diag.TempNode;
			ReOpenQuestHeader("JungleGirl");
			AddQuestRecord("JungleGirl", "1"); 
			AddQuestUserData("JungleGirl", "sSex", GetSexPhrase("","")); 
			AddQuestUserData("JungleGirl", "sName", pchar.GenQuest.EncGirl.name); 
			AddQuestUserData("JungleGirl", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.EncGirl.city));
			AddQuestUserData("JungleGirl", "sText1", sti(pchar.GenQuest.EncGirl.BigCoins)); 
			AddQuestUserData("JungleGirl", "sText2", sti(pchar.GenQuest.EncGirl.SmallCoins)); 		
			DialogExit();
			AddDialogExitQuest("pchar_back_to_player");			
		break;
		
		case "Node_134":
			dialog.text = RandPhraseSimple(""+ GetSexPhrase("Captain","Young lady") +", I am so happy to see you again! Have you managed to collect pearls for the necklace?","Hello, captain! Have you brought me the pearls? You know, my mistress is getting so nervous...");
			if (GetCharacterItem(pchar, "jewelry52") >= sti(pchar.GenQuest.EncGirl.BigCoins) && GetCharacterItem(pchar, "jewelry53") >= sti(pchar.GenQuest.EncGirl.SmallCoins))
			{
				link.l1 = "Yes. Here are you pearls. Take them to your mistress and tell her to be more careful next time.";
				link.l1.go = "Node_134_1";
			}
			else
			{
				link.l1 = "Not yet. It's not so easy, you know... But I'll bring them - you just wait.";
				link.l1.go = "Node_134_2";
			}	
		break;
		
		case "Node_134_1":
			TakeNItems(pchar, "jewelry52", -sti(pchar.GenQuest.EncGirl.BigCoins)); 
			TakeNItems(pchar, "jewelry53", -sti(pchar.GenQuest.EncGirl.SmallCoins)); 
			pchar.quest.EncGirl_GetCoins.over = "yes";
			pchar.quest.EncGirl_DeathSimple.over = "yes";
			dialog.text = "Oh, "+ GetSexPhrase("Captain","young lady") +", I am so happy that I met you! As a token of my gratitude for everything you've done for me, I want to give you this trinket and these gems. I do hope that you would find them useful.";
			link.l1 = "Wow! Well, thank you, too"+ GetSexPhrase(", beauty","") +", did not expect... Goodbye, and be happy.";
			link.l1.go = "Node_134_End";
		break;
		
		case "Node_134_2":
			dialog.text = "Oh, "+ GetSexPhrase("captain","young lady") +", I am counting on you.";
			link.l1 = "That's a right thing to do...";
			link.l1.go = "exit";
			LAi_SetStayType(NPChar);
		break;
		
		case "Node_134_End":
			GiveItem2Character(pchar, pchar.GenQuest.EncGirl.item); 
			TakeNItems(pchar, "jewelry1", 15+drand(8));
			AddQuestRecord("JungleGirl", "2");
			AddQuestUserData("JungleGirl", "sSex", GetSexPhrase("",""));
			AddQuestUserData("JungleGirl", "sName", pchar.GenQuest.EncGirl.name); 
			CloseQuestHeader("JungleGirl");
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeDay = 0;
			DeleteAttribute(pchar, "GenQuest.EncGirl");
			DialogExit();
		break;
		
		case "Node_135":
			addMoneyToCharacter(pchar, -15000);
			ChangeCharacterComplexReputation(pchar,"nobility", 10);
			dialog.text = "Oh, "+ GetSexPhrase("captain","young lady") +", you've helped me out for a second time today. Thank you so much. I will never forget your kindness.";
			link.l1 = "You're welcome. Say 'hi' to your mistress...";
			link.l1.go = "Node_135End";
		break;
		
		case "Node_135End":
			pchar.quest.LandEnc_RapersBadExit.over = "yes";
			NPChar.lifeDay = 0;
			sTemp = LAi_FindNearestFreeLocator2Pchar("reload");
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", sTemp, "none", "", "","OpenTheDoors", -1.0);
			DeleteAttribute(pchar, "GenQuest.EncGirl");
			DialogExit();		
			AddDialogExitQuest("pchar_back_to_player");			
		break;	
		
		case "ThanksForSave":
			if (npchar.city == "Bridgetown" || npchar.city == "Charles" || npchar.city == "FortFrance" || npchar.city == "Marigo" || npchar.city == "Panama" || npchar.city == "PortRoyal" || npchar.city == "SantoDomingo" || npchar.city == "Tortuga") 
			{
				if(CheckAttribute(pchar, "GenQuest.EncGirl.Horse")) 
				{
					iRnd = 2;
					pchar.GenQuest.EncGirl.BrothelCity = true;
				}	
				else
				{	
					iRnd = 1;
				}	
			}
			else
			{
				iRnd = 1;
			}
			switch(rand(iRnd))
			{
				case 0:
					dialog.text = RandPhraseSimple("You shouldn't have given them any money. They were lying.","Don't believe them. They're liars. And you shouldn't have given them any money.");
					link.l1 = "Should I have killed them?";
					link.l1.go = "Node_200";
				break;
				case 1:
					dialog.text = "Oh, what a noble deed! I could tell right away that you were "+ GetSexPhrase("a real gentleman","a noble lady") +"! Please, accept my most sincere gratitude. I hope you didn't believe what these rascals were saying?";
					link.l1 = "That doesn't matter. A girl and a band of ragamuffins in the jungle - it's so natural...";
					link.l1.go = "Node_210";
					link.l2 = "What are you talking about, "+ GetSexPhrase("beauty","deary") +"? How could I?";
					link.l2.go = "Node_211";
				break;
				case 2:
					dialog.text = "Thank you, captain. I am sorry to get you entangled in this unpleasant affair, but I simply had no other choice.";
					link.l1 = "Well, I see that you're quite stuck as well. How did it come to this?";
					link.l1.go = "Node_220";		
				break;
			}
		break;
		
		case "Node_200":
			if(rand(1) == 0)
			{
				dialog.text = "Perhaps... They will never leave me alone now.";
				link.l1 = "Oh, come on! Just go home - you have nothing to fear now.";
				link.l1.go = "Node_200End";
				link.l2 = "Wow! Why do you such aversion for men?";
				link.l2.go = "Node_201";
			}
			else
			{
				dialog.text = "Of course, not! But they will not leave me be, anyway. Would you bring me to the settlement of " + XI_ConvertString("Colony" + pchar.GenQuest.EncGirl.city) + ", please?";
				link.l1 = "Just go home, they will not touch you. They should be going to the tavern right now to waste their easy money.";
				link.l1.go = "Node_200End";
				link.l2 = RandPhraseSimple("Don't worry so much, really... Alright, let's get going.","You're such a coward, aren't you? Alright, I'll bring you there..");
				link.l2.go = "Node_121Next";
			}
		break;
		
		case "Node_201":
			dialog.text = "Oh no, what are you saying? I know these scoundrels all too well. They are former pals of my father. They are trying to locate the spot where he had hidden his treasures.";
			link.l1 = "And what's the deal with your father?";
			link.l1.go = "Node_202";
		break;
		
		case "Node_202":
			dialog.text = "He used to be a captain of a pirate ship. Recently he died... They all were so courteous during the burial, but as time passed, they have forgotten him - and all honesty, too. It's good that I had noticed them. As soon as they learn where the treasure is, I am done for.";
			link.l1 = "That's a sad story. So, are you planning to keep hiding from them?";
			link.l1.go = "Node_203";
		break;
		
		case "Node_203":
			dialog.text = "I can not keep jewels at home, I have no one to protect me. So I go at night in the cave, when money runs out...\nTake me, please, to the cave, and I'll give you the money you've given to them ... I think, the pirates would not risk following us while you're with me.";
			link.l1 = "Sorry, darling, but I have different plans. You will collect your treasure some other time.";
			link.l1.go = "Node_200End";
			link.l2 = "Alright, let's go, if you're not afraid of me.";
			link.l2.go = "Node_204";
		break;
		
		case "Node_204":
			dialog.text = "You know, for some reason, I am not...";
			link.l1 = "Well, that's a good thing.";
			link.l1.go = "Node_205";
		break;
		
		case "Node_205":
			Diag.TempNode = "Node_206";
			EncGirl_GenerateChest(npchar);
			Diag.CurrentNode = Diag.TempNode;
			AddDialogExitQuestFunction("EncGirl_GirlFollow");
			DialogExit();
		break;
		
		case "Node_206":
			Diag.TempNode = "Node_206";
			dialog.text = "Captain, you promised to bring me to the cave.";
			link.l1 = "Let's go...";
			link.l1.go = "exit";
		break;
		
		case "Node_207":
			dialog.text = "Alright, captain, I've taken as much as I needed. We can now return.";
			link.l1 = "Your buddies are not around, I see.";
			link.l1.go = "Node_208";
		break;
		
		case "Node_208":
			dialog.text = "Thanks God. I don't need more trouble... Here, take these ingots - that should be enough to cover your expenses. Go alone, I'll take a different path...";
			link.l1 = "Alright, good luck to you, if you're not afraid.";
			link.l1.go = "Node_209";
		break;
		
		case "Node_209":
			LAi_LocationDisableMonstersGen(pchar.location, false);
			i = makeint(sti(pchar.GenQuest.EncGirl.price)/100.0);
			TakeNItems(pchar, "jewelry6", i);
			sTemp = LAi_FindNearestFreeLocator2Pchar("reload");
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", sTemp, "none", "", "","OpenTheDoors", -1.0);
			npchar.lifeDay = 0;
			pchar.quest.EncGirl_RapersExit.win_condition.l1 = "ExitFromLocation";
			pchar.quest.EncGirl_RapersExit.win_condition.l1.location = pchar.location;
			pchar.quest.EncGirl_RapersExit.function = "EncGirl_MeetRapers";
			DialogExit();
		break;
		
		case "Node_200End":
			pchar.quest.LandEnc_RapersBadExit.over = "yes";
			AddDialogExitQuestFunction("EncGirl_GirlGoAway");
			DialogExit();
		break;
		
		case "Node_210":
			dialog.text = "Hmm, "+ GetSexPhrase("captain","young lady") +", I don't like your irony.";
			link.l1 = "You're good to go, "+ GetSexPhrase("beauty","deary") +". And you'd rather hurry to the town, before they chase you again.";
			link.l1.go = "Node_1End";
		break;
		
		case "Node_211":
			dialog.text = "I was so agitated! Could you please bring me to the tavern in the settlement of " + XI_ConvertString("Colony" + pchar.GenQuest.EncGirl.city) + "? Otherwise, I am afraid, they are going to chase me again.";
			link.l1 = "Perhaps, you're right. Let's go...";
			link.l1.go = "Node_122Next";
			ChangeCharacterComplexReputation(pchar,"nobility", 1);
		break;
		
		case "Node_220":
			dialog.text = "Oh, captain, that's a long story, and I am not certain that you would find it interesting. Although... I will still not do it without your help now. Could you please bring me to the tavern in the settlement of " + XI_ConvertString("Colony" + pchar.GenQuest.EncGirl.city) + "? I am afraid they'd just not leave me alone.";
			link.l1 = "Sorry, darling, I have no time for that. I've got things to do.";
			link.l1.go = "Node_221";
			link.l2 = "Why are you so secretive?";
			link.l2.go = "Node_222";
		break;
		
		case "Node_221":
			ChangeCharacterComplexReputation(pchar,"nobility", -2);
			AddDialogExitQuestFunction("EncGirl_GirlGoAway");
			DialogExit();
		break;
		
		case "Node_222":
			dialog.text = "And how can I not be secretive, if everyone is trying to make a profit of my misfortune?";
			link.l1 = "Alright, then...";
			link.l1.go = "Node_223";
		break;
		
		case "Node_223":
			Diag.TempNode = "Node_224";
			pchar.GenQuest.EncGirl = "HorseToTavern";
			pchar.quest.EncGirl_DeliveBack.win_condition.l1 = "location";
			pchar.quest.EncGirl_DeliveBack.win_condition.l1.location = pchar.GenQuest.EncGirl.city + "_tavern";
			pchar.quest.EncGirl_DeliveBack.function = "EncGirl_DeliveBack";		
			Diag.CurrentNode = Diag.TempNode;
			AddDialogExitQuestFunction("EncGirl_GirlFollow");
			DialogExit();		
		break;
		
		case "Node_224":
			dialog.text = "Captain, you promised to bring me to the tavern in the settlement of " + XI_ConvertString("Colony" + pchar.GenQuest.EncGirl.city) + ".";
			link.l1 = RandPhraseSimple("I remember.","Don't you worry, I'll see you there.");
			link.l1.go = "exit";
		break;
		
		case "Node_225":
			chrDisableReloadToLocation = false;
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") || CheckAttribute(pchar, "questTemp.LSC.Mary_officer"))
			{
				if (CheckAttribute(pchar, "GenQuest.EncGirl.BrothelCity") && sti(pchar.rank) > 15)
				{
					dialog.text = "There are too many people there. Let's go to the private room. I need to tell you something.";
					link.l1 = LinkRandPhrase("I've done too much for you already, so farewell to you now.","You should not be abusing my favor. See you, darling.","I have no need for your stories from now on, you can figure it all out by yourself.");
					link.l1.go = "Node_226";
					link.l2 = "Hmm, alright. I'll take the keys from the bartender then.";
					link.l2.go = "Node_227";
				}
				else
				{
					dialog.text = "Thanks a lot for your help, captain. I will not forget it.";
					link.l1 = "Oh, don't bother yourself. Just try to be more careful in the future.";
					link.l1.go = "Node_226_1";
				}
			}
			else
			{
				if (CheckAttribute(pchar, "questTemp.FMQP") && pchar.questTemp.FMQP == "begin") // Addon-2016 Jason, французские миниквесты (ФМК)
				{
					dialog.text = "Thanks a lot for your help, captain. I will not forget it.";
					link.l1 = "Oh, don't bother yourself. Just try to be more careful in the future.";
					link.l1.go = "Node_226_1";
				}
				else
				{
					dialog.text = "There are too many people there. Let's go to the private room. I need to tell you something.";
					link.l1 = LinkRandPhrase("I've done too much for you already, so farewell to you now.","You should not be abusing my favor. See you, darling.","I have no need for your stories from now on, you can figure it all out by yourself.");
					link.l1.go = "Node_226";
					link.l2 = "Hmm, alright. I'll take the keys from the bartender then.";
					link.l2.go = "Node_227";
				}
			}
		break;
		
		case "Node_226":
			ChangeCharacterComplexReputation(pchar,"nobility", -1);
			sTemp = LAi_FindNearestFreeLocator2Pchar("reload");
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", sTemp, "none", "", "","OpenTheDoors", -1.0);
			npchar.lifeDay = 0;
			DeleteAttribute(pchar, "GenQuest.EncGirl");
			DialogExit();		
			AddDialogExitQuest("pchar_back_to_player");			
		break;
		
		case "Node_226_1":
			ChangeCharacterComplexReputation(pchar,"nobility", 3);
			sTemp = LAi_FindNearestFreeLocator2Pchar("reload");
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", sTemp, "none", "", "","OpenTheDoors", -1.0);
			npchar.lifeDay = 0;
			DeleteAttribute(pchar, "GenQuest.EncGirl");
			DialogExit();		
			AddDialogExitQuest("pchar_back_to_player");			
		break;
		
		case "Node_227":
			pchar.GenQuest.EncGirl = "EncGirl_ToTavern";
			pchar.quest.EncGirl_inRoom.win_condition.l1 = "location";
			pchar.quest.EncGirl_inRoom.win_condition.l1.location = npchar.city + "_tavern_upstairs";
			pchar.quest.EncGirl_inRoom.function = "EncGirl_SpeakInRoom";
			DialogExit();
			AddDialogExitQuest("pchar_back_to_player");			
		break;
		
		case "Node_228":
			if(CheckAttribute(pchar, "GenQuest.EncGirl.Horse") && CheckAttribute(pchar,"GenQuest.EncGirl.BrothelCity") && sti(pchar.rank) > 15) // душещипательная история о невинной девочке попавшей в бордель
			{
				DeleteAttribute(pchar, "GenQuest.EncGirl.BrothelCity");
				dialog.text = "So do you still want to hear out my story?";
				link.l1 = "Hmm... I guess, it's time for me to leave. Bye!";
				link.l1.go = "Node_232";
				link.l2 = "Well, spit it out, then.";
				link.l2.go = "Node_233";	
			}
			else						
			{
				dialog.text = "Oh, my noble savior, finally I can thank you enough in that way only a woman can thank\nWhen I saw you in the jungle, everything changed inside me. I forgot about the rapists and sharp palm leaves that whipped down my cheeks. Forgot where to run, why run ... I only saw you. And just wanted to you ... And after what you've done for me...";
				link.l1 = "Wow! What a temper! Your pursuers surely knew whom to chaise...";
				link.l1.go = "Node_229"; // ГГ допрыгался - щас его попросту трахнут
				link.l2 = "Listen, beauty, I can perfectly understand it, but please, keep your temper to yourself.";
				link.l2.go = "Node_230"; // Послал в пешее эротическое путешествие
			}
		break;
		
		case "Node_229":
			dialog.text = "Come to me now, my hero...";
			link.l1 = "Oh, darling...";
			link.l1.go = "exit";
			pchar.GenQuest.EncGirl = "EncGirl_facking";
			DoQuestCheckDelay("PlaySex_1", 3.0);
		break;
		
		case "Node_230":
			dialog.text = "Oh! How... How dare you?! What a redneck! A girl thanked you with all her heart and soul, and you...";
			link.l1 = "Well, if you weren't flirting as much and making a dead set at the first man you met, you surely would've had fewer troubles. I am no longer rescuing such flirts in the jungle...";
			link.l1.go = "Node_231";
		break;
		
		case "Node_231":
			dialog.text = "I've never heard such words from anyone before! And I will not forgive them! You will yet remember me!";
			link.l1 = "Go already, alright? And try to freshen yourself up, unless you want to be rescued again...";
			link.l1.go = "Node_231_1";
		break;
		
		case "Node_231_1":
			ChangeCharacterComplexReputation(pchar,"nobility", 1);
			sTemp = LAi_FindNearestFreeLocator2Pchar("reload");
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", sTemp, "none", "", "","", -1.0);
			npchar.lifeDay = 0;
			DoQuestFunctionDelay("EncGirl_SetBerglar", 5.0);
			DialogExit();		
		break;
		
		case "Node_232":
			ChangeCharacterComplexReputation(pchar,"nobility", -3);
			sTemp = LAi_FindNearestFreeLocator2Pchar("reload");
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", sTemp, "none", "", "","OpenTheDoors", -1.0);
			npchar.lifeDay = 0;
			DeleteAttribute(pchar, "GenQuest.EncGirl");
			DialogExit();
		break;
		
		case "Node_233":
			pchar.GenQuest.EncGirl.Parents_City = GetQuestNationsCity(sti(pchar.GenQuest.EncGirl.nation));
			dialog.text = "My family lives in the settlement of " + XI_ConvertString("Colony" + pchar.GenQuest.EncGirl.Parents_City) + ". I got here by chance - the ship, on which my groom was taking me to his parents, was captured by pirates. The ship was taken away, and the passengers were landed at the bay not far from here. My groom was killed during boarding of the ship, and I was seriously ill during the transition through the jungle\nMa'am of the local brothel has treated me, and when I got on my feet, she demanded to work money spent on treatment. I was a whore but I did not succeed out, and Ma'am sold me to some bandits to earn at least some money. The other part of story you know.";
			link.l1 = "So just quit and return home! Why are you allowing them to treat you like a slave?!";
			link.l1.go = "Node_234";
		break;
		
		case "Node_234":
			dialog.text = "I can't! All my belongings - decent clothing, money, documents - it's all in the brothel in my travelling bag. I've hidden it in the dating room. And while I am dressed like that, all sailors in the port will be running after me. And who will take me on board without documents or money? And now I can't even show my face in the town, or I'll be thrown behind bars...";
			link.l1 = "Shouldn't be a problem. Let's go. I'll take you home myself.";
			link.l1.go = "Node_235";
			link.l2 = "Wait here. I'll bring you your travelling bag.";
			link.l2.go = "Node_236";													
			if(sti(pchar.money) >= 5000) 
			{
				link.l3 = "Who cares for your papers? How much money do you need to get home?";
				link.l3.go = "Node_237";							
			}			
		break;
		
		case "Node_235":
			dialog.text = "Oh, thank you, captain... But... you know, I don't have anything to pay you with.";
			link.l1 = "What payment are you talking about? Let's go before they are missing you...";
			link.l1.go = "Node_240";				
		break;
		
		case "Node_240":
			ReOpenQuestHeader("JungleGirl");
			AddQuestRecord("JungleGirl", "20");
			AddQuestUserData("JungleGirl", "sSex", GetSexPhrase("",""));
			AddQuestUserData("JungleGirl", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.EncGirl.Parents_City));
			AddQuestUserData("JungleGirl", "sBrothelCity", XI_ConvertString("Colony" + pchar.GenQuest.EncGirl.city + "Gen"));
			AddQuestUserData("JungleGirl", "sName", pchar.GenQuest.EncGirl.name);
		
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, false);
			OfficersReaction("bad");
			chrDisableReloadToLocation = false;
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "OpenTheDoors", 3.0);
			pchar.quest.EncGirl_DeliveToParents.win_condition.l1 = "location";
			pchar.quest.EncGirl_DeliveToParents.win_condition.l1.location = pchar.GenQuest.EncGirl.Parents_City + "_town";
			pchar.quest.EncGirl_DeliveToParents.function = "EncGirl_DeliveToParents";
			DialogExit(); 		
		break;
		
		case "Node_236":
			dialog.text = "Oh, captain, you know, I would never dare to ask...";
			link.l1 = "Have no fear. Soon I will be back.";
			link.l1.go = "Node_239";				
		break;		
		
		case "Node_239":
			ReOpenQuestHeader("JungleGirl");
			AddQuestRecord("JungleGirl", "21");
			AddQuestUserData("JungleGirl", "sSex", GetSexPhrase("",""));
			AddQuestUserData("JungleGirl", "sName", pchar.GenQuest.EncGirl.name);

			pchar.quest.EncGirl_GenerateBag.win_condition.l1 = "location";
			if(GetSummonSkillFromName(pchar, SKILL_FORTUNE) > rand(100))
			{
				pchar.GenQuest.EncGirl = "Bag_BrothelRoomUp";
				pchar.quest.EncGirl_GenerateBag.win_condition.l1.location = pchar.GenQuest.EncGirl.city + "_Brothel_room";
			}
			else
			{
				pchar.GenQuest.EncGirl = "Bag_BrothelRoom";
				pchar.quest.EncGirl_GenerateBag.win_condition.l1.location = pchar.GenQuest.EncGirl.city + "_SecBrRoom";
			}
			pchar.quest.EncGirl_GenerateBag.function = "EncGirl_GenerateLeatherBag";

			pchar.quest.EncGirl_GetBagFail.win_condition.l1 = "Timer";
			pchar.quest.EncGirl_GetBagFail.win_condition.l1.date.day = GetAddingDataDay(0, 0, 1);
			pchar.quest.EncGirl_GetBagFail.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.EncGirl_GetBagFail.win_condition.l1.date.year = GetAddingDataYear(0, 0, 1);
			pchar.quest.EncGirl_GetBagFail.function = "EncGirl_GenQuest_GetBag";
						
			pchar.quest.EncGirl_ExitRoom.win_condition.l1 = "ExitFromLocation";
			pchar.quest.EncGirl_ExitRoom.win_condition.l1.location = pchar.location;
			pchar.quest.EncGirl_ExitRoom.function = "EncGirl_ExitTavernRoom";

			AddDialogExitQuest("OpenTheDoors");
			DialogExit();
		break;
		
		case "Node_240_1":
			pchar.quest.EncGirl_GetBagFail.over = "yes";
			dialog.text = "Oh, I was already worrying that something might have happened to you.";
			if(CheckCharacterItem(pchar, "leather_bag"))
			{
				link.l1 = "What could possibly happen? Here, take your stuff.";
				link.l1.go = "Node_241";
			}	
			else
			{
				link.l1 = "Listen, I haven't found anything there. Are you certain that you had left your travelling bag in the dating room?";
				link.l1.go = "Node_242";			
			}	
		break;
		
		case "Node_241":
			TakeNItems(pchar, "leather_bag", -1);
			dialog.text = "Thank you, "+ GetSexPhrase("noble captain","noble girl") +". I'll never forget what you've done for me. I don't have much, but please accept this amulet. Perhaps, it was that trinket that saved my life during the pirate attack.";
			link.l1 = "Thank you and good journey! Farewell now...";
			link.l1.go = "Node_243";
		break;
		
		case "Node_242":
			dialog.text = "Did they really found my cache?";
			if(sti(pchar.money) >= 5000)
			{
				link.l1 = "How much money do you need to get home?";
				link.l1.go = "Node_237";
			}
			link.l2 = "Perhaps, they did. Anyway, our roads part here now. Farewell!";
			link.l2.go = "Node_244";
		break;
		
		case "Node_243":
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "OpenTheDoors", -1.0);
			npchar.lifeDay = 0;
			TakeNItems(pchar, pchar.GenQuest.EncGirl.item, 1);
			AddQuestRecord("JungleGirl", "23");
			AddQuestUserData("JungleGirl", "sSex", GetSexPhrase("",""));
			AddQuestUserData("JungleGirl", "sSex1", GetSexPhrase("",""));
			AddQuestUserData("JungleGirl", "sName", pchar.GenQuest.EncGirl.name);
			CloseQuestHeader("JungleGirl");
			ChangeCharacterComplexReputation(pchar,"nobility", 1);
			DeleteAttribute(pchar, "GenQuest.EncGirl");
			DialogExit();
		break;
		
		case "Node_244":
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "OpenTheDoors", -1.0);
			npchar.lifeDay = 0;
			AddQuestRecord("JungleGirl", "23");
			AddQuestUserData("JungleGirl", "sName", pchar.GenQuest.EncGirl.name);
			CloseQuestHeader("JungleGirl");
			ChangeCharacterComplexReputation(pchar,"nobility", -5);
			DeleteAttribute(pchar, "GenQuest.EncGirl");
			DialogExit();
		break;
		
		case "Node_245":
			dialog.text = "Thanks, captain. You know, it's hard to believe that I am finally home. Please, come with me, I'll introduce you to my parents.";
			link.l1 = "Listen, "+ GetSexPhrase("beauty","deary") +", I really have no time for that. Some other time perhaps?";
			link.l1.go = "Node_246";
		break;
		
		case "Node_246":
			dialog.text = "What a pity... Well, farewell then, and may the Lord watch over you. I don't have anything to repay you with, but please accept this amulet.";
			link.l1 = "Thanks! Run home now, make your parents feel happy!";
			link.l1.go = "Node_247";
		break;
		
		case "Node_247":
			sTemp = LAi_FindNearestFreeLocator2Pchar("reload");
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", sTemp, "none", "", "","OpenTheDoors", -1.0);		
			TakeNItems(pchar, pchar.GenQuest.EncGirl.item, 1);
			AddQuestRecord("JungleGirl", "24");
			AddQuestUserData("JungleGirl", "sSex", GetSexPhrase("",""));
			AddQuestUserData("JungleGirl","sName", pchar.GenQuest.EncGirl.name);
			AddQuestUserData("JungleGirl","sCity", XI_ConvertString("Colony" + pchar.GenQuest.EncGirl.Parents_City));
			CloseQuestHeader("JungleGirl");
			npchar.lifeDay = 0;
			DeleteAttribute(pchar, "GenQuest.EncGirl");
			DialogExit();			
		break;
		
		case "Node_248":
		break;
		
		case "Node_237":
			dialog.text = "Well, I don't know... Perhaps, I'll have to wait for a passing ride. But I cannot ask you for money.";
			if(makeint(pchar.money)>=5000)
			{
				link.l1 = "I see. Alright, take 5000 pesos. That should be enough.";
				link.l1.go = "Node_237_1";
			}
			if(makeint(pchar.money)>=25000)
			{
				link.l2 = "I see. Alright, take 25000 pesos and go home.";
				link.l2.go = "Node_237_2";
			}
			if(makeint(pchar.money)>=35000)
			{
				link.l3 = "I see. Alright, take 35000 pesos. That should be enough to buy the best cabin on the ship.";
				link.l3.go = "Node_237_3";
			}
		break;
		
		case "Node_237_1":
			AddMoneyToCharacter(pchar, -5000);
			ChangeCharacterComplexReputation(pchar,"nobility", -5);
			dialog.text = "Thank you, "+ GetSexPhrase("noble captain","noble girl") +". I'll never forget what you've done for me.";
			link.l1 = "Bon voyage, then. Farewell...";
			link.l1.go = "Node_238";
			pchar.GenQuest.EncGirl = "EncGirlFack_GetMoney";
		break;
		
		case "Node_237_2":
			AddMoneyToCharacter(pchar, -25000);
			ChangeCharacterComplexReputation(pchar,"nobility", 1);
			dialog.text = "Thank you, "+ GetSexPhrase("noble captain","noble girl") +". I'll never forget what you've done for me.";
			link.l1 = "Bon voyage, then. Farewell...";
			link.l1.go = "Node_238";
		break;
		
		case "Node_237_3":
			AddMoneyToCharacter(pchar, -35000);
			ChangeCharacterComplexReputation(pchar,"nobility", 2);
			dialog.text = "Thank you, "+ GetSexPhrase("noble captain","noble girl") +". I'll never forget what you've done for me.";
			link.l1 = "Bon voyage, then. Farewell...";
			link.l1.go = "Node_238";
		break;
		
		case "Node_238":
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "OpenTheDoors", -1.0);
			npchar.lifeDay = 0;
			if(pchar.GenQuest.EncGirl == "EncGirlFack_GetMoney") 
			{
				AddSimpleRumour(RandPhraseSimple("Have you heard? A whore was trying to sneak on board of a ship without documents, but she was caught and taken back to the brothel. They say she owed the madam quite a sum.",  
				"Have you heard? A whore without documents was caught at the port. They say she had cleaned out madam's coffers before attempting to flee from the brothel. I say, that source of filth and thievery must have been closed off long ago. Our kids are seeing this - and what can they learn from such an example?"), sti(pchar.GenQuest.EncGirl.nation), 3, 1);
			}
			DeleteAttribute(pchar, "GenQuest.EncGirl");
			DialogExit();
		break;
		
		case "Node_250":
			dialog.text = "Don't ruin my life, captain! My father wants me to marry the usurer's son, that filthy milksop... just because his daddy had a crapload of money in his coffers! Well, I'd rather stay in the jungle to be devoured by wild beasts rather than take a life sentence with him!";
			link.l1 = "What's the problem with your marriage, "+ GetSexPhrase("beauty","deary") +"? Hold the one who seeks to marry you, and be happy. After some time you would be happy to marry that milksop, but it might be too late...";
			link.l1.go = "Node_251";
		break;
		
		case "Node_251":
			pchar.GenQuest.EncGirl.sLoverId = GenerateRandomName(sti(npchar.nation), "man"); 
			dialog.text = "No! No, captain, I love " + pchar.GenQuest.EncGirl.sLoverId + " and I will marry no other man! And my father doesn't want to hear anything! He says that " + XI_ConvertString("Colony" + pchar.GenQuest.EncGirl.city) + " is just a visitor here, so he will never find a job here, and he is destined to die in poverty, and me too! And I would go with him to the world's end, just to be at his side! Take me to him, I'm begging you!";
			link.l1 = "Alright, let's go. I guess I'll figure out what to do with you...";
			link.l1.go = "Node_252";
		break;
		
		case "Node_252":
			Diag.TempNode = "Node_253";
			ReOpenQuestHeader("JungleGirl");
			AddQuestRecord("JungleGirl", "9");
			AddQuestUserData("JungleGirl","sText", pchar.GenQuest.EncGirl.FatherGen);
			AddQuestUserData("JungleGirl","sCity", XI_ConvertString("Colony" + pchar.GenQuest.EncGirl.city));
			AddQuestUserData("JungleGirl", "sLover", pchar.GenQuest.EncGirl.sLoverId); 
			pchar.GenQuest.EncGirl.MeetSoldiers = 2;
			Diag.CurrentNode = Diag.TempNode;
			AddDialogExitQuestFunction("EncGirl_GirlFollow");
			DialogExit();
		break;
		
		case "Node_253":
			Diag.TempNode = "Node_253";
			dialog.text = "Captain, you promised to bring me to the settlement of " + XI_ConvertString("Colony" + pchar.GenQuest.EncGirl.city) +".";
			link.l1 = RandPhraseSimple("I remember.","Don't worry, I'll bring you there.");
			link.l1.go = "exit";			
		break;
		
		case "Node_260":
			chrDisableReloadToLocation = false;
			if(rand(1) == 0)
			{
				dialog.text = RandPhraseSimple("Thank you, "+ GetSexPhrase("captain","young lady") +", once again. Really, I am so indebted to you.","Thank you so much, "+ GetSexPhrase("captain","young lady") +". I have no idea what would I do without your help.");
				link.l1 = RandPhraseSimple("That should be a lesson to you. Alright, best of luck...","Next time you should be more careful... Now run home, and I've got things to do.");
				link.l1.go = "Node_260End";
				link.l2 = "How could you be so careless? Why have you headed into the jungle alone?";
				link.l2.go = "Node_13";
			}
			else
			{
				dialog.text = "Oh, "+ GetSexPhrase("captain","young lady") +", I really have no idea how to thank you.";
				link.l1 = "It was nothing. Always happy to help...";
				link.l1.go = "Node_261";
			}
		break;
		
		case "Node_260End":
			sTemp = LAi_FindNearestFreeLocator2Pchar("reload");
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", sTemp, "none", "", "","OpenTheDoors", -1.0);
			npchar.lifeDay = 0;
			DeleteAttribute(pchar, "GenQuest.EncGirl");			
			DialogExit();
			AddDialogExitQuest("pchar_back_to_player");			
		break;
		
		case "Node_261":
			dialog.text = "Can you take me to the tavern? I need to wait for my auntie and take a rest - I was so alarmed...";
			link.l1 = "No, "+ GetSexPhrase("beauty","deary") +", that's certainly enough for me. I have a lot to do.";
			link.l1.go = "Node_262";
			link.l2 = ""+ GetSexPhrase("Oh, women! Is there anything they can do without a man's help?","Why are you so helpless?") +" Let's go...";
			link.l2.go = "Node_263";
		break;
		
		case "Node_262":
			sTemp = LAi_FindNearestFreeLocator2Pchar("reload");
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", sTemp, "none", "", "", "", -1.0);
			npchar.lifeday = 0;
			DeleteAttribute(pchar, "GenQuest.EncGirl");
			DialogExit();
			AddDialogExitQuest("pchar_back_to_player");			
		break;
		
		case "Node_263":
			Diag.TempNode = "Node_224";
			pchar.GenQuest.EncGirl = "HorseToTavern";
			pchar.quest.EncGirl_DeliveBack.win_condition.l1 = "location";
			pchar.quest.EncGirl_DeliveBack.win_condition.l1.location = pchar.GenQuest.EncGirl.city + "_tavern";
			pchar.quest.EncGirl_DeliveBack.function = "EncGirl_DeliveBack";					
			Diag.CurrentNode = Diag.TempNode;
			AddDialogExitQuestFunction("EncGirl_GirlFollow");
			DialogExit();
			AddDialogExitQuest("pchar_back_to_player");			
		break;
				
		case "ThanksForHelp_1":
			Diag.TempNode = "ThanksAgain";
			if(makeint(Pchar.reputation.nobility) >= 80)
			{
				dialog.text = "I have some money... Please, accept is as a token of my gratitude!";
				Link.l1 = "Thanks. Try to be more careful next time.";
				Link.l1.go = "exit";
			}
			else 
			{
				if(drand(1) == 0)
				{
					dialog.text = "I will tell everybody that you have saved me! Let everybody know, "+ GetSexPhrase("what a brave and courageous person you are","what a brave and courageous person you are") +"!";
					Link.l1 = "Thank you. And now you should go home.";
					Link.l1.go = "exit";
				}
				else
				{
					addMoneyToCharacter(Pchar, makeint(PChar.rank)*100);
					dialog.text = "I have some money... Please, accept is as a token of my gratitude!";
					Link.l1 = "Thanks. Try to be more careful next time.";
					Link.l1.go = "exit";
				}
			}
		break;

		case "ThanksAgain":
            Diag.TempNode = "ThanksAgain";
            dialog.text = "I will tell everybody that you have saved me! Let everybody know, "+ GetSexPhrase("what a brave and courageous person you are","what a brave and courageous person you are") +"!";
			Link.l1 = "Thank you. And now you should go home.";
			Link.l1.go = "exit";
		break;
	}
}
