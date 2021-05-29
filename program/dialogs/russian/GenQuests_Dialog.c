void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;
	
	DeleteAttribute(&Dialog,"Links");
	
	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	ref rItem, rChar, sld, MerPrm;
	aref arTemp1, arTemp2;
	bool bTemp;
	int iBanditsCount, i, iMoney, iNation, iTmp, iGoods;
	String sTitle, sGroup, sTemp;
	float locx, locy, locz;
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "This is a bug. Contact with devs and let them know about how and where you've found it";
					link.l1 = RandSwear() + "I will let them know!";
					link.l1.go = "exit";
					
			if(HasSubStr(NPChar.id, "ContraMeetManQuest_Soldier_")) // Солдеры по квесту "встреча в бухте"
			{
				dialog.text = "I am not authorized to deal with you. Talk to our officer.";
					link.l1 = LinkRandPhrase("Of course...", "I see.", "Certainly!");
					link.l1.go = "exit";
				break;
			}
			
			if(HasSubStr(NPChar.id, "ContraMeetManQuest_Officer_")) // Офицер по квесту "встреча в бухте"
			{
				dialog.text = "Introduce yourself! I wanna know whom I am talking to!";
					link.l1 = "My name is " + GetFullName(PChar) + ". What's going on here?";
					link.l1.go = "ContraMeetManQuest_Sold_1";
				break;
			}
					
			if(NPChar.id == "ContraMeetManQuest_QuestMan" && PChar.location == PChar.GenQuest.ContraMeetMan.ShoreID) // Квестовый чел по генеру "meeting in the cove" 
			{
				dialog.text = "Cap, your name is " + GetFullName(PChar) + ", isn't it?";
					link.l1 = "Yes, you're correct.";
					link.l1.go = "ContraMeetManQuest_1";
					link.l2 = "No. You've mistaken me for someone else.";
					link.l2.go = "exit";
					break;
			}
			
			if(NPChar.id == "ContraMeetManQuest_QuestMan" && CheckAttribute(PChar, "GenQuest.ContraMeetMan.ContraIsDead")) // В комнате таверны после убицства контриков
			{
				LAi_LocationFightDisable(LoadedLocation, false);
				dialog.text = PChar.name + ", thank you so much! If it wasn't you, my fate would be unenviable... How can I thank you?";
					link.l1 = "I don't need anything...";
					link.l1.go = "ContraMeetManQuest_7";
					link.l2 = "I would not reject a small reward.";
					link.l2.go = "ContraMeetManQuest_8";
					break;
			}
			
			if(NPChar.id == "ContraMeetManQuest_Contrick_0") // Контрик в комнате по квесту "встреча в бухте"
			{
				iMoney = (rand(3)+2)*500;
				PChar.GenQuest.ContraMeetMan.Money = iMoney;
				if(!CheckAttribute(PChar, "GenQuest.ContraMeetMan.ManIsTraitor")) // Просто платят деньги
				{
					dialog.text = "...Hmm, that's him, indeed... Thank you, "+ GetSexPhrase("fellow","lass") +", without your aid we would have had a hard time - there is no way for us to get out of town. Here, take " + FindRussianMoneyString(iMoney) + " and you can get lost. And we will have a talk with our friend...";
						link.l1 = "...";
						link.l1.go = "ContraMeetManQuest_3";
				}
				else
				{
					dialog.text = "...Hmm, that's him, indeed... Thank you, "+ GetSexPhrase("fellow","lass") +", without your aid we would have had a hard time - there is no way for us to get out of town. Here, take " + FindRussianMoneyString(iMoney) + " and you can get lost. We will gut this filthy traitor now!";
						link.l1 = "Of course. Until we meet again, gentlemen...";
						link.l1.go = "ContraMeetManQuest_4";
						link.l2 = "What?! No, I will not allow you to murder a man, no matter who he is... And I don't need your bloody money!";
						link.l2.go = "ContraMeetManQuest_5";
				}
					break;
			}
			
			if(NPChar.id == "ContraDeliverQuest_Soldier_0") // Солдер в комнате
			{
				dialog.text = "So... What do we have here? Pirates?! You will have to come with us to the commandant's office for investigation...";
					link.l1 = "We are not pirates at all! I don't even know this man! He has just rent and moved in this room and I had no time to pack my belongings and leave!";
					link.l1.go = "ContraDeliverQuest_Sold1";
					break;
			}
				
			if(CheckAttribute(PChar, "GenQuest.ContraDeliver.WaitOnRoom") && NPChar.id == "ContraDeliverQuest_Contra_1")
			{
				dialog.text = "So what were you saying? You have a message for me?! I am waiting!";
					link.l1 = "Here you go...";
					link.l1.go = "ContraDeliverQuest_1";
					DeleteAttribute(PChar, "GenQuest.ContraDeliver.WaitOnRoom");
					DeleteAttribute(PChar, "GenQuest.ContraDeliver.GoToTavern");
					break;
			}
			
			if(CheckAttribute(PChar, "GenQuest.ChurchQuest_2.BanditsInShore") && NPChar.id == "Church_GenQuest2_Bandit_0")
			{
				dialog.text = "Hey, you! Yes, you. I see that you are a decent and wealthy man.";
					link.l1 = "Can't say the same about you.";
					link.l1.go = "Church_GenQuest_2_ShoreBandit_1";
					break;
			}
					
			if(CheckAttribute(PChar, "GenQuest.ChurchQuest_2.WayOfShortVariant") && NPChar.id == "Church_GenQuest2_Bandit_0")
			{
				dialog.text = "Hold on! Hey, "+ GetSexPhrase("buddy","lass") +", show us just how heavy your purse is!";
					link.l1 = "So, have you already wasted all the church money?";
					link.l1.go = "Church_GenQuest_2_1";
					break;
			}
			
			if(NPChar.id == "ReasonToFast_Hunter")
			{
				if(GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) > sti(pchar.questTemp.ReasonToFast.p2))
				{
					dialog.text = "Hey, in a boat! Hic... Clear the fairway - I need to talk to the guys...";
					link.l1 = "Aren't you a bit woozy, buddy? Go sleep it off.";
					link.l1.go = "ReasonToFast_Hunter1";
				}
				else
				{
					dialog.text = "Hey, cap! Drop the anchor!";
					link.l1 = "And why the hell should I....";
					link.l1.go = "ReasonToFast_Hunter2";
				}
				link.l2 = "Aren't you much too rude!?";
				link.l2.go = "ReasonToFast_Hunter3";	
			}
			
			if(NPChar.id == "PirateOnUninhabited_0")
			{
				dialog.text = RandPhraseSimple("Hail to you! Finally, the Lord has taken heed to our prayers and sent a gallant captain to this abandoned shore!",
					"Thank the Providence! Now the local scavengers will not feed on our rotten bones!");
				link.l1 = "Hello, good man, I am captain " + GetFullName(PChar) + ". I see you're quite in a trouble here.";
				link.l1.go = "PiratesOnUninhabited_3";
				link.l2 = "Good man, I have my own business to attend to and I have no time to spare on your troubles.";
				link.l2.go = "PiratesOnUninhabited_1";
			}
			
			if(NPChar.id == "ShipWreck_0")
			{
				dialog.text = RandPhraseSimple("Oh, captain! It's just a good fortune that God has sent you fair wind and led you to this deserted place!",
					"Captain! Thank the Providence that you decided to drop anchor at this desert shore!");
				link.l1 = "Hello, good man, I am captain " + GetFullName(pchar) + ". I see you're in serious trouble here.";	
				link.l1.go = "ShipWreck_2";
				link.l2 = "Good man, I have my own business to attend to and I have no time to spare on your troubles.";
				link.l2.go = "ShipWreck_1";
			}
			
			if(NPChar.id == "Convict_0")
			{
				dialog.text = LinkRandPhrase("Hold on, "+ GetAddress_Form(pchar) +"! Would you spare us a minute of your precious time?","Would a noble mis"+ GetSexPhrase("ter","s") +" listen to a humble request of these unworthy men?","Noble mis"+ GetSexPhrase("ter","s") +", please give just a bit of your precious time to speak with the hapless.");
				link.l1 = LinkRandPhrase("I don't have time for this.", "Get lost, I have much to do without you.", "Leave me be, I have no time for you.");
				link.l1.go = "Convict_0End";
				link.l2 = LinkRandPhrase("What do you want?", "What do you need?", "What's the trouble?");
				link.l2.go = "Convict_Begin";
			}
			
			// Warship, 15.05.11. Генер "Justice for sale".
			if(HasSubStr(NPChar.id, "JusticeOnSale_Jungle_"))
			{
				dialog.text = "Hi, cap! Are you interested in Indian trinkets and goods which cannot be bought at the ordinary stores. Or cash, perhaps?";
					link.l1 = "Ragamuffins like you usually demand - not offer anything. Why are you so strangely courteous?";
					link.l1.go = "JusticeOnSale_1";
					link.l2 = "My pistol usually talks to the bastards like you!";
					link.l2.go = "JusticeOnSale_2";
			}
		break;
		
		// Генератор "Situation in the hold - Ransom"
		case "Hold_GenQuest1":
			pchar.quest.Hold_GenQuest_FindCharTimeIsOver.over = "yes";
			dialog.text = "I am listening to you, captain. Are you here on business?";
			link.l1 = "I am looking for mister " + pchar.GenQuest.Hold_GenQuest.Name + "?";
			link.l1.go = "Hold_GenQuest2";
		break;
		
		case "Hold_GenQuest2":
			dialog.text = RandPhraseSimple("I am mister " + pchar.GenQuest.Hold_GenQuest.Name + ". To whom do I owe the honor?","You have found him. What can I do for you?");
			link.l1 = "I am captain " + GetFullName(pchar) + ", I wanted to talk to you regarding " + pchar.GenQuest.Hold_GenQuest.CapName + ".";
			link.l1.go = "Hold_GenQuest3";
		break;
		
		case "Hold_GenQuest3":
			sld = characterFromId(pchar.GenQuest.Hold_GenQuest.CapId);
			pchar.GenQuest.Hold_GenQuest.RansomSum = makeint(3 * sti(sld.rank) * (800 + GetCharacterSPECIALSimple(NPChar, SPECIAL_L) * 100) + GetCharacterSkillToOld(sld, "Leadership")*500 + GetCharacterSkillToOld(pchar, "commerce")*500); 
						
			switch(drand(3))
			{
				case 0:
					dialog.text = "And who is it?";
					link.l1 = "Hold on... You're " + pchar.GenQuest.Hold_GenQuest.Name + ", and you don't know about " + pchar.GenQuest.Hold_GenQuest.CapName + "?";
					link.l1.go = "Hold_GenQuest40";
				break;
				case 1:
					dialog.text = "Wow! It's been quite a while I last time heard about that old fox? What's happened to him this time?";
					link.l1 = "This time he is in serious trouble... He is being held captive, and he needs your help.";
					link.l1.go = "Hold_GenQuest50";
				break;
				case 2:
					dialog.text = "Alright, I am all ears.";
					link.l1 = "His vessel was attacked by the pirates, and he is being held captive now. He advised that I see you regarding the ransom.";
					link.l1.go = "Hold_GenQuest60";
				break;
				case 3:
					dialog.text = "Yeah, I am glad to hear about an old friend. How is he going?";
					link.l1 = "His situation is so dire that it is hard to imagine.";
					link.l1.go = "Hold_GenQuest70";
				break;				
			}	
		break;
		
		case "Hold_GenQuest40":
			dialog.text = "Indeed, I am " + pchar.GenQuest.Hold_GenQuest.Name + "! But why should I know anything about that " + pchar.GenQuest.Hold_GenQuest.CapName + "?!";
			link.l1 = "I am sorry. Perhaps I was mistaken...";
			link.l1.go = "Hold_GenQuest41";
		break;
		
		case "Hold_GenQuest41":
			AddQuestRecord("HoldQuest", "10");
			AddQuestUserData("HoldQuest", "sName", pchar.GenQuest.Hold_GenQuest.CapName);
			pchar.GenQuest.Hold_GenQuest = "prisoner_escaped";
			LAi_CharacterDisableDialog(NPChar);
			NPChar.LifeDay = 0;
			DialogExit();
			AddDialogExitQuestFunction("Hold_GenQuest_PrisonerEscaped");
		break;
		
		case "Hold_GenQuest50":
			dialog.text = "Wow! And how am I expected to help him? Freeing him by killing all his enemies or what? Ha-ha-ha!";
			link.l1 = "No-no, that is not necessary. You only need to hand over " + pchar.GenQuest.Hold_GenQuest.RansomSum + " pesos as ransom.";
			link.l1.go = "Hold_GenQuest51";
		break;		
		
		case "Hold_GenQuest51":
			dialog.text = "What an impudence! And why should I pay ransom for him?! He's neither my relative nor friend!";
			link.l1 = "Hmm... He told me you were his only hope. And he also mentioned some debt of yours...";
			link.l1.go = "Hold_GenQuest52";
		break;		
		
		case "Hold_GenQuest52":
			dialog.text = LinkRandPhrase("What an insolent guy! It's him who owes me money, for your information! But that's not a reason for me to ransom him in hopes that he'd pay off both debts.",
				"What a scoundrel! He ripped me off when we were dividing our business - and now he's got the nerve to ask me to pay ransom for him!",
				"That's a surprise! Why should I be paying ransom for him?! We are not that close.");
			link.l1 = "So, I can tell him that you refused to pay his ransom and didn't acknowledge your debt?";	
			link.l1.go = "Hold_GenQuest53";
		break;
		
		case "Hold_GenQuest53":
			dialog.text = "Oh my! What debt are you talking about? I have already explained you everything! And if you have no other questions beside this silly story, then allow me to take my leave.";
			link.l1 = "I see. Well, I have no more questions to you - but quite a few to that buddy of yours.";
			link.l1.go = "Hold_GenQuest54";
		break;
		
		case "Hold_GenQuest54":
			AddQuestRecord("HoldQuest", "10");
			AddQuestUserData("HoldQuest", "sName", GetFullName(NPChar));
			pchar.GenQuest.Hold_GenQuest = "prisoner_escaped";
			LAi_CharacterDisableDialog(NPChar);
			NPChar.LifeDay = 0;
			DialogExit();
			AddDialogExitQuestFunction("Hold_GenQuest_PrisonerEscaped");
		break;
		
		case "Hold_GenQuest60":
			dialog.text = "Hmm... And you, as I take it, are the one, who is holding him... Well, I guess I'll help him out.";
			link.l1 = "Very good. The ransom will be " + pchar.GenQuest.Hold_GenQuest.RansomSum + " pesos.";
			link.l1.go = "Hold_GenQuest61";
		break;
		
		case "Hold_GenQuest61":
			dialog.text = "You misunderstood me: I am a member of city council. We watch for observance of the charter.\n" + 
				"Guards!!! Guards! Arrest him on suspicion in slave trading and pillaging ships of " + NationNameGenitive(sti(pchar.GenQuest.Hold_GenQuest.Nation)) + "!";
			link.l1 = "Well, 'buddy', just let me get to you...";
			link.l1.go = "Hold_GenQuest62";
		break;
		
		case "Hold_GenQuest62":
			LAi_SetImmortal(NPChar, false);
			AddQuestRecord("HoldQuest", "10");
			AddQuestUserData("HoldQuest", "sName", GetFullName(NPChar));
			pchar.GenQuest.Hold_GenQuest = "prisoner_escaped";
			LAi_SetWarriorTypeNoGroup(NPChar);
   	        LAi_warrior_DialogEnable(NPChar, false);
            LAi_group_MoveCharacter(NPChar, "TmpEnemy");			
			LAi_group_Attack(NPChar, Pchar);
			LAi_group_SetRelation("TmpEnemy", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_SetCheckFunction("TmpEnemy", "Hold_GenQuest_AfterBattle");
			chrDisableReloadToLocation = true; 
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);  
			AddDialogExitQuest("MainHeroFightModeOn"); 
			AddDialogExitQuestFunction("Hold_GenQuest_PrisonerEscaped");
			DialogExit();
		break;
		
		case "Hold_GenQuest70":
			dialog.text = "What are you saying?! And how can I help him?";
			link.l1 = "He is being held captive and he asked me to talk to you regarding ransoming him.";
			link.l1.go = "Hold_GenQuest71";
		break;		
		
		case "Hold_GenQuest71":
			dialog.text = "Of course, of course. I'll do everything I can. Where do they hold them? And what is the amount of the ransom?";
			link.l1 = "The pirates demand " + pchar.GenQuest.Hold_GenQuest.RansomSum + " pesos. I must deliver the money to the port, and then your friend will be set free.";
			link.l1.go = "Hold_GenQuest72";
		break;
		
		case "Hold_GenQuest72":
			dialog.text = "Here's the money. Fortunately, I had enough on me.";
			link.l1 = "Yeah, that's fortunate, indeed. Go to the port, then, and soon you will see your buddy again.";
			link.l1.go = "Hold_GenQuest73";
		break;
		
		case "Hold_GenQuest73":
			addMoneyToCharacter(pchar, sti(pchar.GenQuest.Hold_GenQuest.RansomSum));
			AddQuestRecord("HoldQuest", "11");
			AddQuestUserData("HoldQuest", "sName", GetFullName(NPChar));
			AddQuestUserData("HoldQuest", "sNameChar", NPChar.Hold_GenQuest.Name);
			AddQuestUserData("HoldQuest", "sSum", pchar.GenQuest.Hold_GenQuest.RansomSum);
			pchar.GenQuest.Hold_GenQuest = "prisoner_ransom";
			LAi_CharacterDisableDialog(NPChar);
			NPChar.LifeDay = 0;
			DialogExit();
			AddDialogExitQuestFunction("Hold_GenQuest_PrisonerEscaped");
		break;				
		// Генератор "Situation in the hold - Ransom"
		
		// Генератор "Situation in the hold - Partner in crime"
		case "Hold_GenQuest80":
			dialog.text = "Hello, captain, sorry that I didn't have the honor to be introduced. They said you were looking for me.";
			link.l1 = "Indeed, if you are mister " + pchar.GenQuest.Hold_GenQuest.Name + ". I am captain " + GetFullName(pchar) + ", I wanted to speak with you.";
			link.l1.go = "Hold_GenQuest81";
		break;
		
		case "Hold_GenQuest81":
			dialog.text = "And what kind of business is it, captain " + GetFullName(pchar) + "?";
			link.l1 = "I heard that you had a thing, of which you would not mind to get rid of.";
			link.l1.go = "Hold_GenQuest82";
		break;
		
		case "Hold_GenQuest82":
			dialog.text = "Just what are you implying?";
			link.l1 = "Don't be so stubborn, my good man, I know very well about your shadowy past and about a makeshift map, on which the location of the treasure" + GetName( NAMETYPE_VIP, pchar.GenQuest.Hold_GenQuest.PirateName, NAME_ACC) + " is indicated.";
			link.l1.go = "Hold_GenQuest83";
		break;
		
		case "Hold_GenQuest83":
			dialog.text = "Goddammit! I always knew that that scoundrel" + pchar.GenQuest.Hold_GenQuest.CapName + " would blab this out sooner or later! What was I thinking when I was offering this deal to him?";
			link.l1 = "Stop whining already. I mean no harm... Just sell this map to me and lead a life you've been used to.";
			link.l1.go = "Hold_GenQuest84";
		break;
		
		case "Hold_GenQuest84":
			dialog.text = "If only I could be so sure of that... And how much are you going to offer me for it? Surely you must know that there was a lot of gold in the chest. It was carried by four men, may the Lord rest their souls...";
			link.l1 = "But " + GetName( NAMETYPE_VIP, pchar.GenQuest.Hold_GenQuest.PirateName, NAME_NOM) + " could have already claimed his treasure...";
			link.l1.go = "Hold_GenQuest85";
		break;
		
		case "Hold_GenQuest85":
			dialog.text = "True as well... Alright - I am willing to sell it to you for " + pchar.GenQuest.Hold_GenQuest.Sum + " pesos. I will not dare to disturb the dead anyway.";
			if(sti(pchar.money) >= sti(pchar.GenQuest.Hold_GenQuest.Sum) && !CheckCharacterItem(pchar,"mapQuest") && !CheckCharacterItem(pchar,"map_full"))
			{
				link.l1 = "Fine. You've got yourself a deal.";
				link.l1.go = "Hold_GenQuest86";
			}	
			link.l2 = "No, my good man, that scrap of paper is not worth this money. Farewell...";
			link.l2.go = "Hold_GenQuest87";
			pchar.quest.Hold_GenQuest_GetMapTimeIsOver.over = "yes";
		break;
		
		case "Hold_GenQuest86":		
			AddMoneyToCharacter(pchar, -sti(pchar.GenQuest.Hold_GenQuest.Sum));
			GiveItem2Character(pchar, "mapQuest"); 
			rItem = ItemsFromID("mapQuest");
			Hold_GenQuest_GenerateTreasureMap(rItem);
			AddQuestRecord("HoldQuest", "15");
			AddQuestUserData("HoldQuest", "sPirateName", GetName( NAMETYPE_VIP, pchar.GenQuest.Hold_GenQuest.PirateName, NAME_ACC));
			AddQuestUserData("HoldQuest", "sSex", GetSexPhrase("",""));
			AddQuestUserData("HoldQuest", "sSum", pchar.GenQuest.Hold_GenQuest.Sum);						
			NPChar.LifeDay = 0;
			LAi_CharacterDisableDialog(NPChar);			
			DialogExit();
			AddDialogExitQuest("OpenTheDoors");
		break;	
		
		case "Hold_GenQuest87":
			NPChar.LifeDay = 0;
			LAi_CharacterDisableDialog(NPChar);
			AddQuestRecord("HoldQuest", "16");
			AddQuestUserData("HoldQuest", "sSex", GetSexPhrase("",""));
			AddQuestUserData("HoldQuest", "sName", pchar.GenQuest.Hold_GenQuest.Name);
			AddQuestUserData("HoldQuest", "sSum", pchar.GenQuest.Hold_GenQuest.Sum);			
			CloseQuestHeader("HoldQuest");
			DeleteAttribute(pchar,"GenQuest.Hold_GenQuest");				
			DialogExit();
			AddDialogExitQuest("OpenTheDoors");
		break;
		// Генератор "Situation in the hold - Partner in crime"
		
		// Генератор "Shipwrecked"
		case "ShipWreck_1":
			dialog.text = "How can this be possible, captain?! God will never forgive you such a sin.";
			link.l1 = "It's up to Him to decide.";
			link.l1.go = "exit";
			ChangeCharacterComplexReputation(pchar,"nobility", -1);
			AddDialogExitQuestFunction("ShipWreck_DialogDisable");
		break;
		
		case "ShipWreck_2":
			pchar.GenQuest.ShipWreck.StartShipType = PiratesOnUninhabited_GenerateShipType(); 		
			pchar.GenQuest.ShipWreck.ShipTypeName = GenerateRandomNameToShip(sti(pchar.GenQuest.ShipWreck.Nation));			
			
			if(rand(1) == 0)
			{
				dialog.text = RandPhraseSimple("Hello, I am " + pchar.GenQuest.ShipWreck.Name + ", captain of the " + GetStrSmallRegister(XI_ConvertString(ShipsTypes[sti(pchar.GenQuest.ShipWreck.StartShipType)].Name + "Acc")) + " '" + pchar.GenQuest.ShipWreck.ShipTypeName + ", my ship crashed at the reefs not far from the coast." + 
					"Only a few sailors of the entire crew managed to survive. The tide has washed us onto this desolate shore. We had been starving and thirsting for " + (5 + dRand(7)) + " weeks by now",
					"Hello, I am " + pchar.GenQuest.ShipWreck.Name + ", captain of the " + GetStrSmallRegister(XI_ConvertString(ShipsTypes[sti(pchar.GenQuest.ShipWreck.StartShipType)].Name + "Gen")) + " '" + pchar.GenQuest.ShipWreck.ShipTypeName + ". Our ship crashed not far from here." + 
					"We managed to get to this shore on the shipwrecks - but this place seems uninhabited. We were forced to survive on shellfish and palm fruits for " + (5 + dRand(7)) + " weeks by now.");
				link.l1 = RandPhraseSimple("And how many of you left?", "And how many of you managed to survive?");
				link.l1.go = "ShipWreck_3";
			}
			else
			{						
				pchar.GenQuest.ShipWreck.Mutiny = true;
				pchar.GenQuest.ShipWreck.BadName = GenerateRandomName_Generator(sti(pchar.GenQuest.ShipWreck.Nation), "man");
				pchar.GenQuest.ShipWreck.City = GetQuestNationsCity(sti(pchar.GenQuest.ShipWreck.Nation));
				dialog.text = "Oh, captain, our casualties are really terrible... Hello, I am " + pchar.GenQuest.ShipWreck.Name + ", captain and owner of " + GetStrSmallRegister(XI_ConvertString(ShipsTypes[sti(pchar.GenQuest.ShipWreck.StartShipType)].Name + "Gen")) + " '" + pchar.GenQuest.ShipWreck.ShipTypeName + ". Or, should I say, former captain and owner. " + 
					"This bastard " + pchar.GenQuest.ShipWreck.BadName + " who I hired in " + XI_ConvertString("Colony" + pchar.GenQuest.ShipWreck.City + "Dat") + " had provoked my crew to mutiny. In the end, we were landed at this lost place. It happened " + (5 + dRand(7)) + " weeks ago.";
				link.l1 = "And then what? Your entire crew joined the mutineers?";
				link.l1.go = "ShipWreck_4";			
			}
		break;
		
		case "ShipWreck_3":
			dialog.text = RandPhraseSimple("From the entire crew, only " + ShipWreck_GetStringQty(sti(pchar.GenQuest.ShipWreck.Qty)) + " survived. Other's have perished; several of them died already here of wounds and fever",
				"Only " + ShipWreck_GetStringQty(sti(pchar.GenQuest.ShipWreck.Qty)) + " were lucky enough. Others have met their end - either in the deep or in the dunes of this coast...");
			link.l1 = LinkRandPhrase("Yeah, that's an unenviable fate. But such is the lot of the sailor - anyone could end up in your place.",
				"I see... God holds every life - it's that He's just too busy to remember everyone.",
				"Indeed. Man proposes, but God disposes.");
			link.l1.go = "ShipWreck_5";	
		break;
		
		case "ShipWreck_4":
			dialog.text = "Of course, not! Those who refused to join the mutineers were many, but these villains have captured the arsenal, and it's good that we didn't put up resistance, or we would be outright killed. Many have already succumbed here to fever and venomous insects, only " + ShipWreck_GetStringQty(sti(pchar.GenQuest.ShipWreck.Qty)) + " survived. Thank God, our trials are finally over.";
			link.l1 = RandPhraseSimple("Yeah, that surely was a stroke of bad luck.","Oh well, many strange things can happen in these God-forsaken places.");
			link.l1.go = "ShipWreck_5";			
			link.l2 = "Hold on, friend. And how should I know that you were not put ashore as the instigators of a mutiny?";
			link.l2.go = "ShipWreck_6";			
		break;
		
		case "ShipWreck_5":
			dialog.text = RandPhraseSimple("Captain, I do hope that you have several free lockers on your ship. All of us have families, and they are probably mourning our loss while we're talking. We would be very grateful to you.",
				"Captain, we are totally despaired, you're our only hope. Please, don't deny us your help, take us from this god-forsaken land.");
			if(GetFreeCrewQuantity(pchar) >= sti(pchar.GenQuest.ShipWreck.Qty) && GetPassengersQuantity(pchar) < PASSENGERS_MAX)
			{
				link.l1 = "Ohh... and where would you want me to take you?";
				link.l1.go = "ShipWreck_7";			
			}
			link.l2 = RandPhraseSimple(RandPhraseSimple("I am really sorry, but there is not even a single free hammock, not to mention the cabins. Sailors are sleeping on the deck, they cannot even take a good night's rest after a watch...",
				"I would really hate to disappoint you, but the ship is overloaded, and people have to sleep in the weather. Should there be an outbreak of disease, I will lose half the crew."), 
				RandPhraseSimple("I am really sorry, but there is absolutely no spare crew space on my ship. I cannot take on board any more passengers.",
				"Have to disappoint you but my ship is overloaded. I fear the epidemic."));
			link.l2.go = "ShipWreck_8";	
			if(stf(pchar.reputation.nobility) <= REPUTATION_NEUTRAL)
			{
				link.l3 = "You're a seasoned sailor and you should know that the presence of someone, who had suffered a shipwreck, is very bad sign. My sailors will just toss you all overboard.";
				link.l3.go = "ShipWreck_9";
			}
		break;
		
		case "ShipWreck_6":
			dialog.text = "What are you saying, " + GetAddress_Form(npchar) + " " + pchar.lastname + "?! Have a heart! I am a negotiant, well-known in the Caribbean! Well... I guess I used to be one. Not now - without a ship or money...";
			link.l1 = "How so... I bet you were the actual instigators of the mutiny - and you've got what you deserved.";
			link.l1.go = "ShipWreck_18";
			if(GetPassengersQuantity(pchar) < PASSENGERS_MAX)
			{
				link.l2 = "But what a scoundrel is that " + pchar.GenQuest.ShipWreck.BadName + "! Are you really going to let him get away with that and submit to your fate?";
				link.l2.go = "ShipWreck_19";
			}	
		break;		
		
		case "ShipWreck_7":
			if(rand(1) == 0)
			{
				if(rand(100) < 90)
				{
					pchar.GenQuest.ShipWreck.variant = "1";
					dialog.text = "To any settlement of " + NationNameGenitive(sti(pchar.GenQuest.ShipWreck.Nation)) + ".";
					link.l1 = "Well, I've got enough free lockers and hammocks. Load yourself into the boat.";
					link.l1.go = "ShipWreck_10";
					link.l2 = "Hmm... We have battles ahead of us, and I don't know where you're going to be more safe - on board of my ship or in this cozy cove.";
					link.l2.go = "ShipWreck_11";
				}
				else
				{				
					dialog.text = "To Dunkirk! My mom lives there...";
					link.l1 = "Are you crazy or what?! I take it you took too many blows to the head...";
					link.l1.go = "ShipWreck_12";					
					pchar.GenQuest.ShipWreck.Crazy = true; // получите психа на борт :-)
					
				}				
			}
			else
			{
				pchar.GenQuest.ShipWreck.variant = "2";
				dialog.text = "Wherever you want - it doesn't really matter. We have nothing to pay you with, anyway...";
				link.l1 = "Well, I've got enough free lockers and hammocks. Load yourself into the boat.";
				link.l1.go = "ShipWreck_10_1";
				link.l2 = "Hmm... We have battles ahead of us, and I don't know where you're going to be more safe - on board of my ship or in this cozy cove.";
				link.l2.go = "ShipWreck_11";		
			}						
		break;		

		case "ShipWreck_8":
			pchar.GenQuest.ShipWreck.FoodQty = sti(pchar.GenQuest.ShipWreck.Qty) * 10 + rand(10);
			pchar.GenQuest.ShipWreck.MedicamentQty = sti(pchar.GenQuest.ShipWreck.Qty) * 5 + rand(10);
			pchar.GenQuest.ShipWreck.AmunitionQty = sti(pchar.GenQuest.ShipWreck.Qty) * 3 + rand(5);
			pchar.GenQuest.ShipWreck.RumQty = sti(pchar.GenQuest.ShipWreck.Qty) * 7 + rand(10);
			if(GetFreeCrewQuantity(pchar) < sti(pchar.GenQuest.ShipWreck.Qty))
			{
				if(GetSquadronGoods(pchar, GOOD_FOOD) < sti(pchar.GenQuest.ShipWreck.FoodQty) || GetSquadronGoods(pchar, GOOD_MEDICAMENT) < sti(pchar.GenQuest.ShipWreck.MedicamentQty))
				{
					dialog.text = "But by refusing you will certainly doom us to death! Well, we will try to break our way to the ship, even if it costs us our lives!";
					link.l1 = "What? Look at yourselves - you are hardly standing on your feet...";
					link.l1.go = "ShipWreck_8_1";
					link.l2 = "You may try...";
					link.l2.go = "ShipWreck_16";
				}
				else
				{
					dialog.text = "But you just cannot leave us there! Without your help we will all soon perish!";
					if(GetSquadronGoods(pchar, GOOD_WEAPON) < sti(pchar.GenQuest.ShipWreck.AmunitionQty) || GetSquadronGoods(pchar, GOOD_RUM) < sti(pchar.GenQuest.ShipWreck.RumQty))
					{			
						link.l1 = "The only thing I can do for you is leave you enough provisions and medicines and give you a boat. At least you are not going to die of starvation and thirst; as for seafaring, I need not teach you that.";
						link.l1.go = "ShipWreck_8_2";
					}
					else
					{
						if(rand(1) == 0)
						{
							link.l1 = "The only thing I can do for you is leave you enough provisions and medicines and give you a boat. At least you are not going to die of starvation and thirst; as for seafaring, I need not teach you that.";
							link.l1.go = "ShipWreck_8_2";
						}
						else
						{
							link.l1 = "I can leave you enough medicine, ammunition, rum and provisions for a month. I will either come back myself or send someone for you.";
							link.l1.go = "ShipWreck_8_4";
						}
					}
				}
			}
			else
			{
				if(stf(pchar.reputation.nobility) <= REPUTATION_NEUTRAL) // плохиш
				{
					if(GetSquadronGoods(pchar, GOOD_FOOD) < sti(pchar.GenQuest.ShipWreck.FoodQty) || GetSquadronGoods(pchar, GOOD_MEDICAMENT) < sti(pchar.GenQuest.ShipWreck.MedicamentQty))				
					{
						dialog.text = "But by refusing you will certainly doom us to death! Well, we will try to break our way to the ship, even if it costs us our lives!";
						link.l1 = "What? Look at yourselves - you are hardly standing on your feet...";
						link.l1.go = "ShipWreck_8_1";
						link.l2 = "You may try...";
						link.l2.go = "ShipWreck_16";					
					}
					else
					{
						link.l1 = "The only thing I can do for you is leave you enough provisions and medicines and give you a boat. At least you are not going to die of starvation and thirst; as for seafaring, I need not teach you that.";
						link.l1.go = "ShipWreck_8_2";					
					}
				}
				else // кибальчиш
				{
					if(GetSquadronGoods(pchar, GOOD_FOOD) < sti(pchar.GenQuest.ShipWreck.FoodQty) || GetSquadronGoods(pchar, GOOD_MEDICAMENT) < sti(pchar.GenQuest.ShipWreck.MedicamentQty))				
					{
						if(rand(1) == 0)
						{
							dialog.text = "But by refusing you will certainly doom us to death! Well, we will try to break our way to the ship, even if it costs us our lives!";
							link.l1 = "What? Look at yourselves - you are hardly standing on your feet...";
							link.l1.go = "ShipWreck_8_1";
							link.l2 = "You may try...";
							link.l2.go = "ShipWreck_16";						
						}
						else
						{
							dialog.text = "How could you do this to us?!.. You've not only disregarded the Sea Code - you've sullied your honor!";
							link.l1 = "Surely you're not the one to speak about my honor, shrimp!";
							link.l1.go = "ShipWreck_16";
						}	
					}
					else
					{
						link.l1 = "The only thing I can do for you is leave you enough provisions and medicines and give you a boat. At least you are not going to die of starvation and thirst; as for seafaring, I need not teach you that.";
						link.l1.go = "ShipWreck_8_2";											
					}						
				}
			}			
		break;				
	
		case "ShipWreck_8_1":
			dialog.text = "You're right, we have no chance. Alright, may the God be your judge, and may everyone be given his due.";
			link.l1 = "Well, I can deal with it myself...";
			link.l1.go = "exit";
			ChangeCharacterComplexReputation(pchar,"nobility", -5);
			AddDialogExitQuestFunction("ShipWreck_DialogDisable");
		break;
	
		case "ShipWreck_8_2":
			dialog.text = "Well... You leave us with no choice... We will pray those storms and thirst not take our lives before we get to inhabited places...";
			link.l1 = "Farewell. May the Lord watch over you...";
			link.l1.go = "ShipWreck_8_3";
		break;
		
		case "ShipWreck_8_3":
			ChangeCharacterComplexReputation(pchar,"nobility", -2);
			AddCharacterExpToSkill(pchar, "Leadership", 25);
			RemoveCharacterGoods(pchar, GOOD_FOOD, sti(pchar.GenQuest.ShipWreck.FoodQty));
			RemoveCharacterGoods(pchar, GOOD_MEDICAMENT, sti(pchar.GenQuest.ShipWreck.MedicamentQty));			
			Log_SetStringToLog("You have spent " + pchar.GenQuest.ShipWreck.FoodQty + " units of provision.");
			Log_SetStringToLog("You have spent " + pchar.GenQuest.ShipWreck.MedicamentQty + "units of medicine.");
			DialogExit();
			NextDiag.TempNode = "ShipWreck_8_7";
			NextDiag.CurrentNode = NextDiag.TempNode;			
		break;
	
		case "ShipWreck_8_4":	
			dialog.text = "Apparently, we have no choice... But I beg you, captain - please return as soon as you can or send us an expeditionary vessel.";
			link.l1 = "I will come up with something. Just wait.";
			link.l1.go = "ShipWreck_8_5";
		break;
	
		case "ShipWreck_8_5":		
			pchar.quest.ShipWreck_LocationExit.over = "yes";
			AddCharacterExpToSkill(pchar, "Leadership", 50); 
			RemoveCharacterGoods(pchar, GOOD_FOOD, sti(pchar.GenQuest.ShipWreck.FoodQty));
			RemoveCharacterGoods(pchar, GOOD_MEDICAMENT, sti(pchar.GenQuest.ShipWreck.MedicamentQty));			
			RemoveCharacterGoods(pchar, GOOD_WEAPON, sti(pchar.GenQuest.ShipWreck.AmunitionQty));
			RemoveCharacterGoods(pchar, GOOD_RUM, sti(pchar.GenQuest.ShipWreck.RumQty));			
			Log_SetStringToLog("You have spent " + pchar.GenQuest.ShipWreck.FoodQty + " units of provision.");
			Log_SetStringToLog("You have spent " + pchar.GenQuest.ShipWreck.MedicamentQty + "units of medicine.");		
			Log_SetStringToLog("You have spent " + pchar.GenQuest.ShipWreck.AmunitionQty + " units of arms.");
			Log_SetStringToLog("You have spent " + pchar.GenQuest.ShipWreck.RumQty + " units of rum");	
			ReOpenQuestHeader("ShipWrecked");
			if(CheckAttribute(pchar, "GenQuest.ShipWreck.Mutiny"))
			{
				AddQuestRecord("ShipWrecked", "11");
				AddQuestUserData("ShipWrecked", "sSex", GetSexPhrase("","а"));
				AddQuestUserData("ShipWrecked", "ShoreName", UpperFirst(XI_ConvertString(pchar.location + "Dat")));
				AddQuestUserData("ShipWrecked", "sBadName", pchar.GenQuest.ShipWreck.BadName);			
				AddQuestUserData("ShipWrecked", "sNation", NationNameGenitive(sti(pchar.GenQuest.ShipWreck.Nation)));
			}
			else
			{
				AddQuestRecord("ShipWrecked", "10");
				AddQuestUserData("ShipWrecked", "sSex", GetSexPhrase("","а"));
				AddQuestUserData("ShipWrecked", "ShoreName", UpperFirst(XI_ConvertString(pchar.location + "Dat")));
				AddQuestUserData("ShipWrecked", "sNation", NationNameGenitive(sti(pchar.GenQuest.ShipWreck.Nation)));
			}
			DialogExit();
			NextDiag.TempNode = "ShipWreck_8_6";
			NextDiag.CurrentNode = NextDiag.TempNode;	
			pchar.GenQuest.ShipWreck = "SailorsOnShore";
			SetFunctionTimerCondition("ShipWreck_SaveSailors", 0, 0, 30, false);
			pchar.GenQuest.ShipWreck.Shore = pchar.location;
			SaveCurrentQuestDateParam("GenQuest.ShipWreck");
			SetFunctionLocationCondition("ShipWreck_MeetInShore", pchar.GenQuest.ShipWreck.Shore, true);
		break;
	
		case "ShipWreck_8_6":			
			dialog.text = RandPhraseSimple("Captain, please remember that you're our only hope...","Why are you lingering? Every minute spent here is unbearable for us...");
			link.l1 = "I will do everything I can. Farewell...";
			link.l1.go = "exit";
			NextDiag.TempNode = "ShipWreck_8_6";		
		break;

		case "ShipWreck_8_7":			
			dialog.text = RandPhraseSimple("Farewell, captain... We must ready ourselves for the journey.","Farewell... And light the candles for saving our souls...");
			link.l1 = "Farewell. May the Lord watch over you...";
			link.l1.go = "exit";
			NextDiag.TempNode = "ShipWreck_8_7";		
		break;
		
		case "ShipWreck_9":
			dialog.text = "How could you do this to us?! You've not only disregarded the Sea Code - you've sullied your honor!";
			link.l1 = "Surely you're not the one to speak about my honor, shrimp!";
			link.l1.go = "ShipWreck_16";
		break;					
		
		case "ShipWreck_10":
			dialog.text = "Thank you, captain! The loading should not take up too much time. God, how had we prayed for that moment to come!";
			link.l1 = "That's great. I hope that your trials will soon be over.";
			link.l1.go = "ShipWreck_13";
			pchar.quest.ShipWreck_DeliveToCity.win_condition.l1 = "Nation_City";
			pchar.quest.ShipWreck_DeliveToCity.win_condition.l1.nation = sti(pchar.GenQuest.ShipWreck.Nation);
			pchar.quest.ShipWreck_DeliveToCity.function = "ShipWreck_DeliveToCity";
			ReOpenQuestHeader("ShipWrecked");
			if(CheckAttribute(pchar, "GenQuest.ShipWreck.Mutiny"))
			{
				AddQuestRecord("ShipWrecked", "2");
				AddQuestUserData("ShipWrecked", "ShoreName", UpperFirst(XI_ConvertString(pchar.location + "Dat")));
				AddQuestUserData("ShipWrecked", "count", pchar.GenQuest.ShipWreck.Qty);
				AddQuestUserData("ShipWrecked", "sBadName", pchar.GenQuest.ShipWreck.BadName);
				AddQuestUserData("ShipWrecked", "sNation", NationNameGenitive(sti(pchar.GenQuest.ShipWreck.Nation)));
			}
			else
			{
				AddQuestRecord("ShipWrecked", "1");
				AddQuestUserData("ShipWrecked", "ShoreName", UpperFirst(XI_ConvertString(pchar.location + "Dat")));
				AddQuestUserData("ShipWrecked", "count", pchar.GenQuest.ShipWreck.Qty);
				AddQuestUserData("ShipWrecked", "ShipType", GetStrSmallRegister(XI_ConvertString(ShipsTypes[sti(pchar.GenQuest.ShipWreck.StartShipType)].Name + "Acc")));
				AddQuestUserData("ShipWrecked", "ShipName", pchar.GenQuest.ShipWreck.ShipTypeName);
				AddQuestUserData("ShipWrecked", "sNation", NationNameGenitive(sti(pchar.GenQuest.ShipWreck.Nation)));
			}
			
		break;							

		case "ShipWreck_10_1":
			dialog.text = "Thank you, captain! The loading should not take up too much time. God, how had we prayed for that moment to come!";
			link.l1 = "That's great. I hope that your trials will soon be over.";
			link.l1.go = "ShipWreck_13";
			pchar.quest.ShipWreck_DeliveToCity.win_condition.l1 = "Location_Type";
			pchar.quest.ShipWreck_DeliveToCity.win_condition.l1.location_type = "town";
			pchar.quest.ShipWreck_DeliveToCity.function = "ShipWreck_DeliveToCity";
			ReOpenQuestHeader("ShipWrecked");
			if(CheckAttribute(pchar,"GenQuest.ShipWreck.Mutiny"))
			{
				AddQuestRecord("ShipWrecked", "4");
				AddQuestUserData("ShipWrecked", "ShoreName", UpperFirst(XI_ConvertString(pchar.location + "Dat")));
				AddQuestUserData("ShipWrecked", "count", pchar.GenQuest.ShipWreck.Qty);
				AddQuestUserData("ShipWrecked", "sBadName", pchar.GenQuest.ShipWreck.BadName);
			}
			else
			{
				AddQuestRecord("ShipWrecked", "3");
				AddQuestUserData("ShipWrecked", "ShoreName", UpperFirst(XI_ConvertString(pchar.location + "Dat")));
				AddQuestUserData("ShipWrecked", "count", pchar.GenQuest.ShipWreck.Qty);
				AddQuestUserData("ShipWrecked", "ShipType", GetStrSmallRegister(XI_ConvertString(ShipsTypes[sti(pchar.GenQuest.ShipWreck.StartShipType)].Name + "Acc")));
				AddQuestUserData("ShipWrecked", "ShipName", pchar.GenQuest.ShipWreck.ShipTypeName);
			}			
		break;							
				
		case "ShipWreck_11":
			dialog.text = "Come one! Really, captain?! Are we afraid of death?! We have fooled it once, we can do it again. We just don't want to loose our lives like this. To rot here, alone\nWe'd gladly join your crew and fight under your flag bravely. Just don't leave us here...";
			link.l1 = "I see you're ready to do anything only to get out of here. But you just look at yourselves - what kind of sailors can you be?";
			link.l1.go = "ShipWreck_14";
			if(GetFreeCrewQuantity(pchar) >= sti(pchar.GenQuest.ShipWreck.Qty))
			{
				link.l2 = "That's a good idea. I suppose, I can hire you.";
				link.l2.go = "ShipWreck_15";
			}	
		break;									
		
		case "ShipWreck_12":
			dialog.text = "No-no, I am not kidding! Please, take me away from this Caribbean slaughterhouse... out of this hell! You know, I am a rich man... a very rich man. Even a Pope himself hadn't seen that much gold in all his time. I will shower you with gold...";
			link.l1 = "Oh my... Alright, get into the boat...";
			link.l1.go = "ShipWreck_13";
			pchar.quest.ShipWreck_DeliveToCity.win_condition.l1 = "Location_Type";
			pchar.quest.ShipWreck_DeliveToCity.win_condition.l1.location_type = "town";
			pchar.quest.ShipWreck_DeliveToCity.function = "ShipWreck_DeliveToCity";			
			ChangeOfficersLoyality("bad_all", 1);
			ReOpenQuestHeader("ShipWrecked");
			AddQuestRecord("ShipWrecked", "5");
			AddQuestUserData("ShipWrecked", "sSex", GetSexPhrase("","а"));
			AddQuestUserData("ShipWrecked", "ShoreName", UpperFirst(XI_ConvertString(pchar.location + "Dat")));
			AddQuestUserData("ShipWrecked", "count", pchar.GenQuest.ShipWreck.Qty);
			AddQuestUserData("ShipWrecked", "ShipType", GetStrSmallRegister(XI_ConvertString(ShipsTypes[sti(pchar.GenQuest.ShipWreck.StartShipType)].Name + "Acc")));
			AddQuestUserData("ShipWrecked", "ShipName", pchar.GenQuest.ShipWreck.ShipTypeName);	
		break;							

		case "ShipWreck_13": // берем пассажирами
			pchar.GenQuest.ShipWreck = "SailorsSaved";			
			if(CheckAttribute(pchar,"GenQuest.ShipWreck.variant"))
			{
				if(pchar.GenQuest.ShipWreck.variant == "1") ChangeCharacterComplexReputation(pchar,"nobility", 1);			
				if(pchar.GenQuest.ShipWreck.variant == "2") ChangeCharacterComplexReputation(pchar,"nobility", 2);			
			}	
			for(i = 0; i < sti(pchar.GenQuest.ShipWreck.Qty); i++)
			{
				rChar = CharacterFromID("ShipWreck_" + i);
				if(i == 0) 
				{
					AddPassenger(pchar, rChar, false);
					SetCharacterRemovable(rChar, false);	
				}
				LAi_SetWarriorTypeNoGroup(rChar);
				rChar.Dialog.currentnode = "ShipWreck_13_again";
			}
			DialogExit();
		break;
		
		case "ShipWreck_13_again":
			dialog.text = LinkRandPhrase("Why are you lingering, captain? Order to weigh anchor.","We are sorry, captain, but we must get ready for setting sail.","We are so lucky that you've decided to come here!");
			link.l1 = "Hurry up. The ship will not be waiting for anyone.";
			link.l1.go = "exit";
			NextDiag.TempNode = "ShipWreck_13_again";		
		break;
		
		case "ShipWreck_14":
			dialog.text = "Captain, we have nothing to lose. Death is already following us in our footsteps... We would rather die in a fair fight than be devoured by stinky coyotes...";
			link.l1 = "Oh, it's a challenge, then?! Alright, let's settle our disputes"+ GetSexPhrase(", like men","") +"!";
			link.l1.go = "ShipWreck_16";
			AddDialogExitQuest("MainHeroFightModeOn"); 
		break;		
		
		case "ShipWreck_15":
			dialog.text = "I swear, captain, you will not regret it. We will be the best sailors in the entire archipelago.";
			link.l1 = "Great! Get into the boat...";
			link.l1.go = "ShipWreck_17";			
		break;				
		
		case "ShipWreck_16":
			ChangeCharacterComplexReputation(pchar,"nobility", -3);
			for(i = 0; i < sti(pchar.GenQuest.ShipWreck.Qty); i++)
			{
				rChar = CharacterFromID("ShipWreck_" + i);
				LAi_SetImmortal(rChar, false);
				if(CheckPassengerInCharacter(pchar, "ShipWreck_" + i)) 
				{
					RemovePassenger(pchar, rChar);
				}
				LAi_SetWarriorType(rChar);
				LAi_group_MoveCharacter(rChar, "ShipWreckGroup");
			}

			LAi_Group_SetRelation("ShipWreckGroup", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_Group_FightGroups("ShipWreckGroup", LAI_GROUP_PLAYER, true);
			if(pchar.GenQuest.ShipWreck == "fight")
			{
				LAi_group_SetCheck("ShipWreckGroup", "OpenTheDoors"); 
				LAi_group_SetCheckFunction("ShipWreckGroup", "ShipWreck_AfterBattle");
			}	
			DialogExit();		
		break;
		
		case "ShipWreck_17": // принимаем в команду
			if(pchar.GenQuest.ShipWreck.variant == "1") ChangeCharacterComplexReputation(pchar,"nobility", 1);			
			if(pchar.GenQuest.ShipWreck.variant == "2") ChangeCharacterComplexReputation(pchar,"nobility", 2);			
			for(i = 0; i < sti(pchar.GenQuest.ShipWreck.Qty); i++)
			{
				rChar = CharacterFromID("ShipWreck_" + i);
				LAi_SetWarriorTypeNoGroup(rChar);
				rChar.LifeDay = 0;			
				rChar.Dialog.currentnode = "ShipWreck_17_again";
			}
			AddCharacterCrew(pchar, sti(pchar.GenQuest.ShipWreck.Qty));
			Log_Info("Your crew was increased by " + pchar.GenQuest.ShipWreck.Qty + " men.");
			Achievment_SetStat(pchar, 29, sti(pchar.GenQuest.ShipWreck.Qty));
			pchar.quest.ShipWreck_LocExit.over = "yes"; // Снимаем прерывание на выход из локации			
			DeleteAttribute(pchar, "GenQuest.ShipWreck");			
			AddCharacterExpToSkill(pchar, "Leadership", 50); 			
			DialogExit();
		break;

		case "ShipWreck_17_again":
			dialog.text = LinkRandPhrase("I swear, captain, you won't regret it.", "You've made the right choice, captain.", "Captain, rest assured that you were in luck as much as ourselves!");
			link.l1 = RandPhraseSimple("I hope so.", "Hurry up. The ship will not be waiting for anyone.");
			link.l1.go = "exit";
			NextDiag.TempNode = "ShipWreck_17_again";
		break;
		
		case "ShipWreck_18":
			dialog.text = "Captain, why would you offend honest people with your distrust? Just look at their faces - are you really thinking they are mutineers?";
			link.l1 = "Alright, but what am I supposed to do with you now?";
			link.l1.go = "ShipWreck_20";
		break;
		
		case "ShipWreck_19":
			dialog.text = "And what can I do? At least, at the moment... I thank God I made it out alive! But if you help me to get my ship back and exact revenge for my humiliation, I am willing to give you whatever this scoundrel will have robbed and stashed in the hold.";
			link.l1 = "Alright, you have a deal.";
			link.l1.go = "ShipWreck_13";
			ShipWreck_SetCapToMap();
			ReOpenQuestHeader("ShipWrecked");
			AddQuestRecord("ShipWrecked", "16");
			AddQuestUserData("ShipWrecked", "ShoreName", UpperFirst(XI_ConvertString(pchar.location + "Dat")));
			AddQuestUserData("ShipWrecked", "sName", pchar.GenQuest.ShipWreck.Name);
			AddQuestUserData("ShipWrecked", "count", pchar.GenQuest.ShipWreck.Qty);
			AddQuestUserData("ShipWrecked", "sBadName", pchar.GenQuest.ShipWreck.BadName);
			AddQuestUserData("ShipWrecked", "ShipName", pchar.GenQuest.ShipWreck.ShipTypeName);	
		break;
		
		case "ShipWreck_20":
			dialog.text = "We aren't in the position to issue orders. It's up to you - bring us to a settlement or accept us into your crew.";
			if(GetFreeCrewQuantity(pchar) >= sti(pchar.GenQuest.ShipWreck.Qty))
			{
				link.l1 = "Alright, I'll take you into my crew. But no fooling around! I have strict discipline on my ship!";
				link.l1.go = "ShipWreck_17";
			}
			link.l2 = "I am not taking you anywhere. I already have enough thugs in my crew.";	
			link.l2.go = "ShipWreck_22";
			link.l3 = "Alright, get into the boat, I'll take you somewhere.";
			link.l3.go = "ShipWreck_10_1";
		break;		
		
		case "ShipWreck_22":
			dialog.text = "Oh well... You don't leave us a choice... We will pray that the Providence show mercy for us and let us get out of this perilous place. God willing, we might yet get to the inhabited land...";
			link.l1 = "Farewell. May the Lord watch over you...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("ShipWreck_DialogDisable");
		break;		
		
		case "ShipWreck_30":
			if(pchar.GenQuest.ShipWreck == "SailorsSaved")
			{
				dialog.text = "Thank you so much, captain " + GetFullName(pchar) + "! You've done so much for us that no gratitude could be sufficient to repay you. And while all our belongings aren't worth a copper, allow me to present you this amulet. It would be very useful to a captain who is frequently engaged in naval battles.";
				link.l1 = "Thank you for your gift! This trinket is very useful, indeed! Farewell, captain " + pchar.GenQuest.ShipWreck.Name + " and good luck to you in your journeys.";
				link.l1.go = "ShipWreck_47";
			}
			else
			{
				dialog.text = "Captain, thank you very much. You've done much for us, and any reward would be inferior compared to our thankfulness. Please, accept this modest gift as a token of our gratitude.";
				link.l1 = "Really, you shouldn't have bothered... You're in much greater need of money than me. Still, it's very nice of you. Thank you - and farewell.";
				link.l1.go = "ShipWreck_31";
			}	
		break;
		
		case "ShipWreck_31":
			//addMoneyToCharacter(pchar, sti(pchar.rank) * 200 + rand(2000));
			AddCharacterExpToSkill(pchar, "Commerce", 50);
			AddCharacterExpToSkill(pchar, "Sailing", 100);
			TakeNItems(pchar, "jewelry2", 15+drand(10));
			AddQuestRecord("ShipWrecked", "6");
			AddQuestUserData("ShipWrecked", "sSex", GetSexPhrase("","а"));
			AddQuestUserData("ShipWrecked", "sName", pchar.GenQuest.ShipWreck.Name);
			AddQuestUserData("ShipWrecked", "sCity", XI_ConvertString("Colony"+ Locations[FindLocation(PChar.location)].townsack + "Acc"));
			CloseQuestHeader("ShipWrecked");
			DialogExit();
			AddDialogExitQuestFunction("ShipWreck_GoOut");
		break;
		
		case "ShipWreck_32":	
			dialog.text = "Captain, be aware that there are people who would go to the world's end for you from now on. It's a pity I don't have anything to thank you with. Still... Please, accept this trinket - I have found it in that ill-fated cove. I hope it will bring you luck.";
			link.l1 = "Anyone would have done the same in my place. Farewell.";
			link.l1.go = "ShipWreck_33";
		break;
		
		case "ShipWreck_33":
			GiveItem2Character(pchar, pchar.GenQuest.ShipWreck.Prize);
			AddCharacterExpToSkill(pchar, "Fortune", 100);
			AddCharacterExpToSkill(pchar, "Sailing", 100);
			AddQuestRecord("ShipWrecked", "6");
			AddQuestUserData("ShipWrecked", "sSex", GetSexPhrase("",""));
			AddQuestUserData("ShipWrecked", "sName", pchar.GenQuest.ShipWreck.Name);
			AddQuestUserData("ShipWrecked", "sCity", XI_ConvertString(pchar.location + "Acc"));
			CloseQuestHeader("ShipWrecked");		
			DialogExit();
			AddDialogExitQuestFunction("ShipWreck_GoOut");
		break;
		
		case "ShipWreck_34":
			dialog.text = RandPhraseSimple(RandPhraseSimple("Captain, is it Dunkirk already?","Are we really in Dunkirk, captain?"),RandPhraseSimple("Captain, is it Europe?","Have we sailed to Europe that fast?"));
			bTemp = !GetCharacterItem(pchar, "map_part1") || !GetCharacterItem(pchar, "map_part2");
			if(rand(100) > 75 && !isDay() && bTemp)
			{
				link.l1 = "A-ha...";
				link.l1.go = "ShipWreck_40";
			}
			else
			{
				link.l1 = LinkRandPhrase("Not yet...","What Dunkirk? What Europe? Look around!","Oh my God!");
				link.l1.go = "ShipWreck_35";
			}
		break;
		
		case "ShipWreck_35":
			dialog.text = LinkRandPhrase("But, captain, you made a promise!","How could you have broken your word, captain?","And when do we get to Europe?");
			if(rand(100) < 70)
			{
				link.l1 = "Alright. Mister, gather your men and your possession and go wherever you choose.";
				link.l1.go = "ShipWreck_36";
			}
			link.l2 = RandPhraseSimple(LinkRandPhrase("Are you certain that we really need to get to Dunkirk?","You know, my ship is not meant for sailing across the ocean.","Captain, and what's wrong with the Caribbean?"), 
					LinkRandPhrase("But I had different plans...","Why do you want to go to Europe in the first place...","Just think of all those seductive mulatto women! You will never meet them in Europe..."));
			link.l2.go = "ShipWreck_37";	
		break;
		
		case "ShipWreck_36":
			pchar.quest.ShipWreck_DeliveToCity.over = "yes";
			pchar.GenQuest.ShipWreck = "fight";
			dialog.text = "But how?.. How dare you?! What kind of treachery is this?! I'll teach you how to stay true to your word!";
			link.l1 = "Well, you asked for it...";
			link.l1.go = "ShipWreck_16";
			AddCharacterExpToSkill(pchar, "Sneak", 100);
			AddDialogExitQuest("MainHeroFightModeOn"); 
		break;
		
		case "ShipWreck_37":
			dialog.text = LinkRandPhrase(RandPhraseSimple("No! I need to get to Dunkirk!","Instead of teaching me geography you should rather fulfill your obligation!"), 
				RandPhraseSimple("I don't want to hear anything about it! You promised me to bring me to Europe!","No, captain, that won't do. We are sailing to Europe."),"I am not going to lead a wretched life for the rest of my days in this hole!");
			link.l1 = "Oh, I don't know if this is going to end...";
			link.l1.go = "ShipWreck_38";
		break;		
		
		case "ShipWreck_38":
			chrDisableReloadToLocation = false;			
			SetFunctionExitFromLocationCondition("ShipWreck_ExitFromTown", pchar.location, false);				
			if(!CheckAttribute(pchar,"GenQuest.CaptainComission.CrazyRec"))
			{
				pchar.GenQuest.CaptainComission.CrazyRec = true;
				AddQuestRecord("ShipWrecked", "7");
			}
			DialogExit();
		break;
		
		case "ShipWreck_40":
			pchar.quest.ShipWreck_DeliveToCity.over = "yes";
			if(CheckAttribute(pchar,"GenQuest.CaptainComission.CrazyRec")) DeleteAttribute(pchar,"GenQuest.CaptainComission.CrazyRec");
			dialog.text = "See! That's a decent man! Europe! Bloody old Europe! Yes-yes-yes!\nOh, yes! You have fulfilled your part of the bargain and so will I. Here, take this half of the map. The other half my partner had. Rest in peace, or rest in water? Whatever. He was the one who persuaded me to take part in this adventure.";
			link.l1 = "Hold on - so you're no sailor? You're buddy was a captain?";
			link.l1.go = "ShipWreck_41";
		break;
		
		case "ShipWreck_41":
			dialog.text = "Oh my!.. Of course, not! Well, yes - I am not a sailor. And he was washed overboard by a huge wave, when he decided to sail further from the shore. Then I assumed command and ordered to sail into the cove... And we did well making our way through the reefs, until everything was decided by a fatal accident. The ship hit a fragment of rock and went down...";
			link.l1 = "Now that was a real display of incompetence...";
			link.l1.go = "ShipWreck_42";
		break;
		
		case "ShipWreck_42":
			dialog.text = "Listen, is this really Dunkirk? Just think about it - it's been only six months and the whole place has changed\nHere, take the map, or its part, to be more specific. The treasure is inside a cave! No idea what the island, but you are an experienced sailor, you will find the exact location one day... I guarantee that there are countless riches of the pirate named aaarrrrrhg...";
			link.l1 = "Thank you, my good man. Even if there is no treasure at all, I'll not be too upset. Farewell, and I do hope that we will never see each other again...";
			link.l1.go = "ShipWreck_43";
		break;
		
		case "ShipWreck_43":
			sld = CharacterFromID("ShipWreck_0");
			RemovePassenger(pchar, sld);
			AddCharacterExpToSkill(pchar, "Fortune", 200);
			if (!GetCharacterItem(pchar, "map_part1")) 	GiveItem2Character(pchar, "map_part1");
			else 										GiveItem2Character(pchar, "map_part2");
			AddQuestRecord("ShipWrecked", "9");
			AddQuestUserData("ShipWrecked", "sSex", GetSexPhrase("","а"));
			CloseQuestHeader("ShipWrecked");	
			AddSimpleRumourCity(LinkRandPhrase(RandPhraseSimple("They say some loony recently showed up on the island. He is telling everyone that he had lost his documents, and no he's attempting to apply for a captain on a ship to Dunkirk.",
				"They say some maniac recently showed up on the island. He stole a spade at the local shop and now is digging a pit past the town gates..."),
				RandPhraseSimple("Just imagine - recently some visiting European in worn and dirty clothes attempted to get an audience with the governor! He claimed that he needed to see the governor of Dunkirk ass soon as possible.",
				"There was a scandal at the town hall recently. Some vagrant was caught - he claimed that he personally knew the governor of Dunkirk."),
				"Some psycho was looking for you recently. He claimed that you owed him money..."), pchar.location, 5, 3,"");
			DialogExit();
			AddDialogExitQuestFunction("ShipWreck_GoOut");
		break;
		
		case "ShipWreck_44":
			dialog.text = RandPhraseSimple("Captain, it's just great that you had not forgotten us! We all had been praying for you!","Captain, is our salvation near? How had we been praying for it to come! Some people already began to get desperate...");
			link.l1 = "Greetings, " + pchar.GenQuest.ShipWreck.Name + "! How could I leave my colleagues in such state? Where to?";
			link.l1.go = "ShipWreck_45";
			link.l2 = "Greetings, " + pchar.GenQuest.ShipWreck.Name + "! I am afraid I have bad news for you. There was a change of plans, and I will not be able to take you on board.";
			link.l2.go = "ShipWreck_9";
		break;
		
		case "ShipWreck_45":
			dialog.text = "We don't care where to go - as long as it's far enough from this accursed place... Would you allow us to begin loading ourselves?";
			link.l1 = "Yeah, go ahead with that. Soon your trials will be over.";
			link.l1.go = "ShipWreck_46";
		break;

		case "ShipWreck_46":
			ChangeCharacterComplexReputation(pchar,"nobility", 4);			
			for(i = 0; i < sti(pchar.GenQuest.ShipWreck.Qty); i++)
			{
				rChar = CharacterFromID("ShipWreck_" + i);
				if(i == 0) 
				{
					AddPassenger(pchar, rChar, false);
					SetCharacterRemovable(rChar, false);	
				}
				LAi_SetWarriorTypeNoGroup(rChar);
				rChar.dialog.currentnode = "ShipWreck_13_again";
			}			
			pchar.quest.ShipWreck_DeliveToCity.win_condition.l1 = "Location_Type";
			pchar.quest.ShipWreck_DeliveToCity.win_condition.l1.location_type = "town";
			pchar.quest.ShipWreck_DeliveToCity.function = "ShipWreck_DeliveToCity";			
			pchar.GenQuest.ShipWreck = "SailorsSaved";
			if(CheckAttribute(pchar,"GenQuest.ShipWreck.Mutiny")) DeleteAttribute(pchar,"GenQuest.ShipWreck.Mutiny"));
			SetFunctionExitFromLocationCondition("ShipWreck_LocationExit", pchar.location, false);				
			DialogExit();			
		break;

		case "ShipWreck_47":
			AddCharacterExpToSkill(pchar, "Fortune", 50);
			AddCharacterExpToSkill(pchar, "Sailing", 100);
			GiveItem2Character(pchar, "indian_10");
			AddQuestRecord("ShipWrecked", "15");
			AddQuestUserData("ShipWrecked", "sSex", GetSexPhrase("",""));
			AddQuestUserData("ShipWrecked", "sName", pchar.GenQuest.ShipWreck.Name);
			CloseQuestHeader("ShipWrecked");				
			DialogExit();
			AddDialogExitQuestFunction("ShipWreck_GoOut");
		break;
		
		case "ShipWreck_48":
			dialog.text = "Thank you, captain. We have already begun to get desperate - but you've literally brought us back to life.";
			link.l1 = "It was nothing... Farewell.";
			link.l1.go = "ShipWreck_49";
		break;
		
		case "ShipWreck_49":
			AddQuestRecord("ShipWrecked", "17");
			AddQuestUserData("ShipWrecked", "sSex", GetSexPhrase("",""));
			CloseQuestHeader("ShipWrecked");								
			DialogExit();
			AddDialogExitQuestFunction("ShipWreck_GoOut");
		break;
		
		case "ShipWreck_50":
			dialog.text = "What the hell do you want from me?";
			link.l1 = "I came to say hi on behalf of " + pchar.GenQuest.ShipWreck.Name + ". I take it you know him?";
			link.l1.go = "ShipWreck_51";
		break;
		
		case "ShipWreck_51":
			dialog.text = "It's a pity I didn't strangle that scoundrel before. Well, then, I guess, time has come to pay for my benevolence...";
			link.l1 = "Indeed... And this time has just run out...";
			link.l1.go = "ShipWreck_52";
		break;
		
		case "ShipWreck_52":
			LAi_SetCurHPMax(NPChar);
			LAi_GetCharacterMaxEnergy(NPChar);			
			QuestAboardCabinDialogFree(); // важный метод
			LAi_group_SetRelation(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, true);
			LAi_group_SetCheckFunction(LAI_GROUP_BRDENEMY, "ShipWreck_afterCabinFight");
			DialogExit();	
			AddDialogExitQuest("MainHeroFightModeOn");				
		break;

		case "ShipWreck_53":
			AddCharacterExpToSkill(pchar, "Leadership", 100);
			pchar.quest.ShipWreck_ShipSink.over = "yes";
			dialog.text = "Great job, captain! Everything as we agreed, then? We get the ship and you get the cargo?";
			link.l1 = "Sure. Take the ship and make good use of it.";
			link.l1.go = "exit";
			LAi_SetPlayerType(pchar);
			NextDiag.TempNode = "ShipWreck_53_again";		
			AddDialogExitQuestFunction("ShipWreck_SetShipNew");
		break;
		
		case "ShipWreck_53_again":
			dialog.text = "I greet you, captain " + GetFullName(pchar) + ".";
			link.l1 = "So, how do you like your ship?";
			link.l1.go = "ShipWreck_53_again1";
		break;
		
		case "ShipWreck_53_again1":
			dialog.text = "Heh - it's squeaking and creaking, just as myself. I think we both have got not much time left to sail the high seas...";
			link.l1 = "Good luck, then...";
			link.l1.go = "exit";
			NextDiag.TempNode = "ShipWreck_53_again";		
		break;
		// Генератор "Shipwrecked"
		
		// Генератор "State convicts"
		case "Convict_0End":
			DialogExit();
			pchar.GenQuest.Convict = "close";
			chrDisableReloadToLocation = false;
			ChangeCharacterComplexReputation(pchar,"nobility", -1);
			AddDialogExitQuestFunction("Convict_DialogDisable");
		break;
		
		case "Convict_Begin":					
			switch(sti(pchar.GenQuest.Convict.var))
			{
				case 0:
					dialog.text = "Captain, please help us to get a ship - a long boat, a tartan, whatever - it really doesn't matter. We are in such circumstances that we must flee this inhospitable place - but we cannot show up in the settlement.";
					link.l1 = "And just what kind of circumstances are those?";
					link.l1.go = "Convict_11";
				break;
				case 1:
					dialog.text = "Captain, would you please lend us a couple hundred pesos? We would not be asking, but we really are in dire need.";
					link.l1 = "In dire need, you say? I bet you've just run out of rum - that's surely a dire need.";
					link.l1.go = "Convict_12";			
				break;
				case 2:
					pchar.GenQuest.Convict.ToCity = FindColonyWithMayakExceptIsland(GetCharacterCurrentIslandId(pchar));	
					pchar.GenQuest.Convict.Mayak = GetMayakByCityName(pchar.GenQuest.Convict.ToCity);
					dialog.text = "Captain, could you be so kind to get our humble company to the lighthouse of " + XI_ConvertString("Colony" + pchar.GenQuest.Convict.ToCity + "Gen") + ".";
					link.l1 = "By looking at you I wouldn't say that you're too humble.";
					link.l1.go = "Convict_13";								
				break;
			}						
			link.l2 = LinkRandPhrase("I am not giving alms on Fridays.","I don't have time for this nonsense.","I am not helping strange people.");
			link.l2.go = "Convict_14";
			Convict_GetMineType();
			pchar.GenQuest.Convict.ShoreLocation = SelectQuestShoreLocation();
		break;
		
		case "Convict_11":
			dialog.text = "We are fugitives... from " + GetStrSmallRegister(XI_ConvertString("MineType" + pchar.GenQuest.Convict.MineType + "Dat")) + ". Soon the ex master will notice... and then we are dead for sure.";
			if(GetFreeCrewQuantity(pchar) >= sti(pchar.GenQuest.Convict.ConvictQty))
			{
				link.l1 = "So you know how to manage the sails?";
				link.l1.go = "Convict_11_1";
			}	
			link.l2 = "And what are you going to pay with?";
			link.l2.go = "Convict_11_2";
		break;
		
		case "Convict_12":
			dialog.text = "It's not a good time for us to think about rum. It's been a week since we escaped, now we are hiding in jungles and starving.";
			if(sti(pchar.money) >= 3000)
			{
				link.l1 = "Well, suppose, I can give you money - and then what? You're going to stay in hiding, until you're eventually discovered by a patrol?";
				link.l1.go = "Convict_12_1";		
				link.l2 = "Alright, how much do you need?";
				link.l2.go = "Convict_12_2";
			}	
			link.l3 = "I have a short talk with the likes of you - heads on the executioner's block, and that's it!";
			link.l3.go = "Convict_12_3";
		break;		
		
		case "Convict_12_1":
			if(drand(1) == 0 && GetFreeCrewQuantity(pchar) >= sti(pchar.GenQuest.Convict.ConvictQty))
			{
				dialog.text = "And what else can we do? We would gladly get a job as sailors - but since we're fugitives, who's going to hire us?";
				link.l1 = "I'll hire you if you know how to manage with the sails and will not cower under fire.";
				link.l1.go = "Convict_12_1_1";
			}
			else
			{
				dialog.text = "We have already come to an agreement with the local sailors. To get out of here, we're only three thousand short.";
				link.l1 = "Well, here are your three thousand - if that's really gonna help you.";
				link.l1.go = "Convict_12_1_2";
			}
			link.l2 = "Well, I don't know... These are your own problems, and I am not gonna help you solving them.";
			link.l2.go = "Convict_12_1_End"; // выход из локи с закрытием квеста
		break;
		
		case "Convict_12_1_1":
			pchar.GenQuest.Convict.PirateName = "l" + rand(GetNamesCount(NAMETYPE_NICK) - 1);
			dialog.text = "Please, captain, hire us - surely you won't regret it! We'd been pirating with " + GetName( NAMETYPE_NICK, pchar.GenQuest.Convict.PirateName, NAME_ABL) + " in Adriatics, until he finally was hanged and we, " + pchar.GenQuest.Convict.ConvictQty + " men, were banished to this place.";
			link.l1 = "Alright. There's a place nearby, known as " + XI_ConvertString(pchar.GenQuest.Convict.ShoreLocation) + ". Around midnight I'll pick you up there. I do hope you're not going to get lost.";
			link.l1.go = "Convict_11_6";
			pchar.GenQuest.Convict = "ToShore";		
		break;

		case "Convict_12_1_2":
			addMoneyToCharacter(pchar, -3000);
			AddCharacterExpToSkill(pchar, "Leadership", 30);
			AddCharacterExpToSkill(pchar, "Commerce", 60);
			iTmp = drand(3);
			if(iTmp <= 1)
			{
				dialog.text = "Of course, it's gonna help us greatly! We'll be setting sail today, if wind is favorable and the fishermen don't let us down. Thank you, captain, and may God help you...";
				link.l1 = "Good luck to you, too.";
				link.l1.go = "exit";
				pchar.GenQuest.Convict = "close";
				AddDialogExitQuestFunction("Convict_DialogDisable");
				AddDialogExitQuest("OpenTheDoors");
			}
			if(iTmp == 2)
			{
				dialog.text = "Now that's a stroke of luck! We couldn't even hope to get the money so quickly. Captain, allow me to present you one trinket that we've taken from our former boss. Perhaps, it will bring good luck to you, too.";
				link.l1 = "Thank you, that's a decent thing, for sure. Good luck to you.";
				link.l1.go = "exit";
				pchar.GenQuest.Convict = "close";
				GiveItem2Character(pchar, pchar.GenQuest.Convict.Item);
				AddDialogExitQuestFunction("Convict_DialogDisable");
				AddDialogExitQuest("OpenTheDoors");
				AddCharacterExpToSkill(pchar, "Fortune", 30);
			}
			if(iTmp == 3)
			{
				pchar.GenQuest.Find_Merchant.lastspeak_date = LastSpeakDate();
				GenerateMerchant();
				makeref(MerPrm, MerchantParam);
				dialog.text = "Now, there is a generous man who doesn't fear to spend the coin, because he knows how to earn it!\nLast night we saw the local smugglers loading " + MerPrm.QuestGoodsIdx + ". It was dark, but we managed to discern the name of the ship on the side of one of the boats - '" + MerPrm.ShipName + "... That ship is sailing under the flag of " + MerPrm.nation + ". Perhaps, you would find this information useful, he-he.";			
				link.l1 = "Mmm? Well, perhaps I will. Farewell to you, trackers.";
				link.l1.go = "exit";
				pchar.GenQuest.Convict = "close";
				AddQuestRecord("Convict", "7");
				AddQuestUserData("Convict", "sShipName", MerPrm.ShipName);
				AddQuestUserData("Convict", "sGoodName", MerPrm.QuestGoodsIdx);
				CloseQuestHeader("Convict");
				SetFunctionExitFromLocationCondition("Convict_LocExit", pchar.location, false);
				AddDialogExitQuestFunction("Convict_DialogDisable");			
				AddDialogExitQuest("OpenTheDoors");
				AddCharacterExpToSkill(pchar, "Sneak", 30);
			}
		break;
		
		case "Convict_12_2":
			dialog.text = "Oh my, we're not in the position to make demands. Whatever you can spare, we'll be grateful for anything.";
			link.l1 = "300 pesos.";
			link.l1.go = "Convict_12_2_1";
			link.l2 = "1000 pesos.";
			link.l2.go = "Convict_12_2_2";
			link.l3 = "3000 pesos.";
			link.l3.go = "Convict_12_2_3";
		break;
		
		case "Convict_12_2_1":
			addMoneyToCharacter(pchar, -300);
			AddCharacterExpToSkill(pchar, "Leadership", 30);
			AddCharacterExpToSkill(pchar, "Commerce", 20);
			dialog.text = "Thank you, captain, and may the God watch over you...";
			link.l1 = "Good luck to you, too.";
			link.l1.go = "exit";
			pchar.GenQuest.Convict = "close";
			AddDialogExitQuestFunction("Convict_DialogDisable");
			AddDialogExitQuest("OpenTheDoors");
		break;

		case "Convict_12_2_2":
			addMoneyToCharacter(pchar, -1000);
			AddCharacterExpToSkill(pchar, "Leadership", 30);
			AddCharacterExpToSkill(pchar, "Commerce", 40);
			if(drand(1) == 0)
			{
				GiveItem2Character(pchar, pchar.GenQuest.Convict.Item);
				dialog.text = "Now that's a stroke of luck! We couldn't even hope to get the money so quickly. Captain, allow me to present you one trinket that we've taken from our former boss. Perhaps, it will bring good luck to you, too.";
				link.l1 = "Thank you, that's a decent thing, for sure. Good luck to you.";
				AddCharacterExpToSkill(pchar, SKILL_FORTUNE, 20);
			}
			else
			{
				dialog.text = "Thank you, captain, and may the God watch over you...";
				link.l1 = "Good luck to you, too.";
			}
			link.l1.go = "exit";
			pchar.GenQuest.Convict = "close";
			AddDialogExitQuestFunction("Convict_DialogDisable");
			AddDialogExitQuest("OpenTheDoors");
		break;

		case "Convict_12_2_3":
			addMoneyToCharacter(pchar, -3000);
			AddCharacterExpToSkill(pchar, "Leadership", 30);
			AddCharacterExpToSkill(pchar, "Commerce", 60);
			if(drand(1) == 0)
			{
				dialog.text = "Now that's a stroke of luck! We couldn't even hope to get the money so quickly. Captain, allow me to present you one trinket that we've taken from our former boss. Perhaps, it will bring good luck to you, too.";
				link.l1 = "Thank you, that's a decent thing, for sure. Good luck to you.";
				link.l1.go = "exit";
				pchar.GenQuest.Convict = "close";
				GiveItem2Character(pchar, pchar.GenQuest.Convict.Item);
				AddDialogExitQuestFunction("Convict_DialogDisable");
				AddDialogExitQuest("OpenTheDoors");
				AddCharacterExpToSkill(pchar, "Fortune", 30);
			}
			else
			{
				pchar.GenQuest.Find_Merchant.lastspeak_date = LastSpeakDate();
				GenerateMerchant();
				makeref(MerPrm, MerchantParam);
				dialog.text = "Now, there is a generous man who doesn't fear to spend the coin, because he knows how to earn it!\nLast night we saw the local smugglers loading " + MerPrm.QuestGoodsIdx + ". It was dark, but we managed to discern the name of the ship on the side of one of the boats - '" + MerPrm.ShipName + "... That ship is sailing under the flag of " + MerPrm.nation + ". Perhaps, you would find this information useful, he-he.";
				link.l1 = "Mmm? Well, perhaps I will. Farewell to you, trackers.";
				link.l1.go = "exit";
				pchar.GenQuest.Convict = "close";
				AddQuestRecord("Convict", "7");
				AddQuestUserData("Convict", "sShipName", MerPrm.ShipName);
				AddQuestUserData("Convict", "sGoodName", MerPrm.QuestGoodsIdx);				
				CloseQuestHeader("Convict");
				SetFunctionExitFromLocationCondition("Convict_LocExit", pchar.location, false);
				AddDialogExitQuestFunction("Convict_DialogDisable");
				AddDialogExitQuest("OpenTheDoors");
				AddCharacterExpToSkill(pchar, "Sneak", 30);
			}			
		break;
		
		case "Convict_12_1_End":
			ChangeCharacterComplexReputation(pchar,"nobility", -2);
			OfficersReaction("bad");	
			pchar.GenQuest.Convict = "close";
			DialogExit();
			AddDialogExitQuestFunction("Convict_DialogDisable");
			AddDialogExitQuest("OpenTheDoors");
		break;
		
		case "Convict_12_3":
			if(drand(1) == 0)
			{
				dialog.text = "Don't spell doom on us, captain! We have a decent trinket - please, accept it as ransom and let us go...";
				link.l1 = "Hand it over, then, and get lost, while you still can.";
				link.l1.go = "exit";
				pchar.GenQuest.Convict = "close";
				GiveItem2Character(pchar, pchar.GenQuest.Convict.Item);
				AddDialogExitQuestFunction("Convict_DialogDisable");
				AddDialogExitQuest("OpenTheDoors");
			}
			else
			{
				dialog.text = "Now we have no other choice - a man still will not die twice. To the last battle, boys!";
				link.l1 = "Now that's a different story!";
				link.l1.go = "Convict_Fight";
			}			
		break;
		
		case "Convict_13":
			dialog.text = "Well, we certainly are no saints, but we're not looking for a quarrel over nothing... We're fugitives, and we need to get out of here as soon as we can.";
			link.l1 = "Do you have anything to pay for passage?";
			link.l1.go = "Convict_13_1";		
			link.l2 = "Oh, I see... No, I will not stain my reputation because of you. Farewell.";
			link.l2.go = "Convict_11_5";
		break;
		
		case "Convict_11_1":
			pchar.GenQuest.Convict.PirateName = "l" + rand(GetNamesCount(NAMETYPE_NICK) - 1);
			dialog.text = "Sure thing! We're quite used to boardings and stuff. For almost two years we and the late " + GetName( NAMETYPE_NICK, pchar.GenQuest.Convict.PirateName, NAME_ABL) + " were terrorizing the local merchants, but alas! He was hanged, and " + pchar.GenQuest.Convict.ConvictQty + " men of us were condemned to penal servitude.";
			link.l1 = "How about joining my crew? I am generous"+ GetSexPhrase("","а") +", but I don't promise you a peaceful life.";
			link.l1.go = "Convict_11_3";			
		break;
		
		case "Convict_11_2":
			dialog.text = "We have managed to get some trinkets, so we will pay double. Don't even think to call the guards. We don't excuse people...";
			link.l1 = "Alright, wait for me at " + XI_ConvertString(pchar.GenQuest.Convict.ShoreLocation + "Dat") + ". You'll have your ship by the midnight. And don't try to fool me!";
			link.l1.go = "Convict_11_4";
			link.l2 = "No, my friends. What if I give you the ship and you stab me in the back? No, I am not helping you in this affair.";
			link.l2.go = "Convict_11_5";
		break;
		
		case "Convict_11_3":
			dialog.text = "With great pleasure, "+ GetSexPhrase("mister","miss") +" captain. We're quite acquainted with that, and we certainly are not going to be admitted in the Navy with such recommendations, anyway, he-he.";
			link.l1 = "Alright. There's a place nearby, known as " + XI_ConvertString(pchar.GenQuest.Convict.ShoreLocation) + ". After midnight I'll pick you up there. I do hope you're not going to get lost.";
			link.l1.go = "Convict_11_6";
		break;
		
		case "Convict_11_4":
			dialog.text = "But, "+ GetSexPhrase("mister","miss") +" captain, we're taking even a greater risk? What if you decide to turn us in to the commandant?";
			link.l1 = "That's true... Alright - if I am not there by daybreak, then the deal is cancelled.";
			link.l1.go = "Convict_11_7";			
		break;
		
		case "Convict_11_5":
			if(makeint(pchar.reputation.nobility) < 11 || makeint(pchar.reputation.nobility) > 79) //макс. репутатция 90
			{
				dialog.text = "Oh, captain, we were counting on you...";
				link.l1 = "Not an issue. If you have money, you'll find passage. Farewell.";
				link.l1.go = "exit";
				pchar.GenQuest.Convict = "close";
				ChangeCharacterComplexReputation(pchar,"nobility", -2);
				AddDialogExitQuestFunction("Convict_DialogDisable");
				AddDialogExitQuest("OpenTheDoors");
			}
			else
			{
				dialog.text = "You're a smart one, captain, as I can see. I am sure you're going to run straight to the commandant, aren't you? And you think you'd get away with that?";
				link.l1 = "And you're planning to stop me, as I can see?! Then you'll get what you deserve!";
				link.l1.go = "Convict_Fight";
				pchar.GenQuest.Convict = "fight";
			}	
		break;
		
		case "Convict_11_6":
			pchar.GenQuest.Convict = "ToShore";
			ReOpenQuestHeader("Convict");
			AddQuestRecord("Convict", "1");
			AddQuestUserData("Convict", "sSex", GetSexPhrase("",""));
			AddQuestUserData("Convict", "sIslandType", XI_ConvertString(GetIslandByCityName(pchar.GenQuest.Convict.city) + "Gen"));
			AddQuestUserData("Convict", "sConvictNum", pchar.GenQuest.Convict.ConvictQty);
			AddQuestUserData("Convict", "sShoreName", XI_ConvertString(pchar.GenQuest.Convict.ShoreLocation + "Dat"));							
			SetFunctionTimerCondition("Convict_SetTimerMeet", 0, 0, 1, false);	
			locations[FindLocation(pchar.GenQuest.Convict.ShoreLocation)].DisableEncounters = true;			
			DialogExit();
			AddDialogExitQuestFunction("Convict_DialogDisable");
			AddDialogExitQuest("OpenTheDoors");
		break;
		
		case "Convict_11_7":
			pchar.GenQuest.Convict = "GetShip";
			ReOpenQuestHeader("Convict");
			AddQuestRecord("Convict", "2");		
			AddQuestUserData("Convict", "sSex", GetSexPhrase("",""));		
			AddQuestUserData("Convict", "sIslandType", XI_ConvertString(GetIslandByCityName(pchar.GenQuest.Convict.city) + "Gen"));
			AddQuestUserData("Convict", "sShoreName", XI_ConvertString(pchar.GenQuest.Convict.ShoreLocation + "Acc"));					
			SetFunctionTimerCondition("Convict_SetTimerMeet", 0, 0, 1, false);
			locations[FindLocation(pchar.GenQuest.Convict.ShoreLocation)].DisableEncounters = true;			
			DialogExit();		
			AddDialogExitQuestFunction("Convict_DialogDisable");		
			AddDialogExitQuest("OpenTheDoors");
		break;
		
		case "Convict_13_1":
			pchar.GenQuest.Convict.Sum = (sti(pchar.rank)+10)*100+1000;
			dialog.text = "There is something. We rummaged through the coffers of our boss, but then there was a fuss about it, and we had to break through with a fight. Only " + PChar.GenQuest.Convict.ConvictQty + " men managed to survive.";
			link.l1 = "Considering the circumstances, I will not give you passage cheaper than for " + FindRussianMoneyString(sti(pchar.GenQuest.Convict.Sum)) + " per person.";
			link.l1.go = "Convict_13_2";
			if(GetFreeCrewQuantity(pchar) >= sti(pchar.GenQuest.Convict.ConvictQty) && GetPassengersQuantity(pchar) < PASSENGERS_MAX)
			{
				link.l2 = "I see that you're no cowards. Would you join my crew?";
				link.l2.go = "Convict_13_3";
			}
		break;
		
		case "Convict_13_2":
			dialog.text = "And do we have a choice? Alright, " + FindRussianMoneyString(sti(pchar.GenQuest.Convict.Sum)) + "...";
			link.l1 = "Then go " + XI_ConvertString(pchar.GenQuest.Convict.ShoreLocation + "Acc") + ". I'll send a longboat for you around the midnight.";
			link.l1.go = "Convict_13_4";
			pchar.GenQuest.Convict = "ToMayak";
			pchar.GenQuest.Convict.Sum = sti(pchar.GenQuest.Convict.Sum) * sti(pchar.GenQuest.Convict.ConvictQty);
		break;
		
		case "Convict_13_3":
			pchar.GenQuest.Convict.PirateName = "l" + rand(GetNamesCount(NAMETYPE_NICK) - 1);
			dialog.text = "And why not? We know that stuff, we'd been pirating with " + GetName( NAMETYPE_NICK, pchar.GenQuest.Convict.PirateName, NAME_ABL) + " to " + RandPhraseSimple("Gibraltar","English Channel") + " before we got stuck here.";
			link.l1 = "Alright. There's a place nearby, known as " + XI_ConvertString(pchar.GenQuest.Convict.ShoreLocation) + ". Around midnight I'll pick you up there. I do hope you're not going to get lost.";
			link.l1.go = "Convict_11_6";
			pchar.GenQuest.Convict = "ToShore";
		break;
		
		case "Convict_13_4":
			ReOpenQuestHeader("Convict");
			AddQuestRecord("Convict", "8");					
			AddQuestUserData("Convict", "sSex", GetSexPhrase("",""));		
			AddQuestUserData("Convict", "sIslandType", XI_ConvertString(GetIslandByCityName(pchar.GenQuest.Convict.city) + "Gen"));
			AddQuestUserData("Convict", "sConvictNum", pchar.GenQuest.Convict.ConvictQty);
			AddQuestUserData("Convict", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.Convict.ToCity + "Gen"));
			AddQuestUserData("Convict", "sSum", pchar.GenQuest.Convict.Sum);
			AddQuestUserData("Convict", "sShoreName", XI_ConvertString(pchar.GenQuest.Convict.ShoreLocation + "Acc"));			
			SetFunctionTimerCondition("Convict_SetTimerMeet", 0, 0, 1, false);
			locations[FindLocation(pchar.GenQuest.Convict.ShoreLocation)].DisableEncounters = true;			
			DialogExit();
			AddDialogExitQuestFunction("Convict_DialogDisable");
			AddDialogExitQuest("OpenTheDoors");
		break;
				
		case "Convict_14":
			dialog.text = RandPhraseSimple(RandPhraseSimple("Eh, captain, you were also poor once, had your pockets empty. And now you despise simple folk like us."), 
											RandPhraseSimple("Heh, people are really getting too unfeeling these days. You're living like you have two centuries still ahead of you.","Oh, I see that you've just arrived from Europe - you hadn't yet smelled the stench of our tropical dump."));
			link.l1 = LinkRandPhrase("Are you trying to put me to shame? I'll make your tongue a couple inches shorter!","Are you intimidating me? Hold on to your hat now!","Are you a philosopher or what? I'll beat some sense into you!");
			link.l1.go = "Convict_Fight";	
			pchar.GenQuest.Convict = "fight";
		break;
		
		case "Convict_Fight":
			LAi_SetPlayerType(pchar);
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);	 
			LAi_LockFightMode(pchar, false); 
			LAi_SetFightMode(pchar, true);
			chrDisableReloadToLocation = true;
			iTemp = sti(PChar.GenQuest.Convict.ConvictQty);
			for(i = 0; i < iTemp; i++)
			{
				rChar = CharacterFromID("Convict_" + i);
				DeleteAttribute(rChar, "City");
				LAi_SetWarriorType(rChar);
				LAi_group_MoveCharacter(rChar, "ConvictGroup");
				LAi_SetImmortal(rChar, false);
			}
			LAi_group_SetRelation("ConvictGroup", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("ConvictGroup", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("ConvictGroup", "OpenTheDoors"); 
			DialogExit();	
			AddDialogExitQuest("MainHeroFightModeOn");		
		break;
		
		case "Convict_15":
			dialog.text = LinkRandPhrase("So, captain? Have you fetched us a ship?","Greetings, captain. So, what about our deal?","Hello, captain. We already began to worry. Everything went fine, I assume?");
			if(Convict_CheckShipType(SHIP_TARTANE) || Convict_CheckShipType(SHIP_WAR_TARTANE))
			{
				link.l1 = "Yeah, here's your tub. And don't forget about payment. I paid " + pchar.GenQuest.Convict.ShipPrice + " coins for it, so you owe me " + sti(pchar.GenQuest.Convict.ShipPrice) * 2 + ", just as we agreed.";
				link.l1.go = "Convict_15_1";
			}	
			link.l2 = "No, I've changed my mind. Find yourself another helper. Bye...";
			link.l2.go = "Convict_15_2";
		break;
		
		case "Convict_15_1":
			switch(sti(pchar.GenQuest.Convict.variant))
			{
				case 1:
					dialog.text = "But of course! They took our freedom, but not our conscience! Please accept your money together with our limitless gratitude. You've really helped us out. Do you mind if we pay you in silver ingots?";
					link.l1 = "Sure I don't. Good luck to you in your journey. And pray that I don't meet you in the open sea - I'll make short work of you.";
					link.l1.go = "Convict_15_1_1End";
					AddCharacterExpToSkill(pchar, "Leadership", 30);
					AddCharacterExpToSkill(pchar, "Commerce", 30);
					TakeNItems(pchar, "jewelry6", makeint(sti(pchar.GenQuest.Convict.ShipPrice)/50));
				break;
				case 2:
					dialog.text = "Captain, you know, we thought that money really isn't that important in life. And, frankly, we need it much more than you at this point. But we have one thing we had stolen from our former boss. Perhaps it would interest you a lot more than gold. Wanna take a look?...";
					link.l1 = "Yeah, you're right. That's a marvelous thing, indeed. Alright - thanks and farewell.";
					link.l1.go = "Convict_15_1_2End";
					AddCharacterExpToSkill(pchar, "Leadership", 30);
					AddCharacterExpToSkill(pchar, "Fortune", 30);
					GiveItem2Character(pchar, pchar.GenQuest.Convict.Item);
				break;
				case 3:
					pchar.GenQuest.Convict = "FightInShore";
					SetFunctionExitFromLocationCondition("Convict_LocExit", pchar.location, false);				
					dialog.text = "Why at all would you need that much money, captain? You're rich, anyway, and we are doomed if we don't get this ship. So... we're going to simply take it from you. No hard feelings.";
					link.l1 = "That was your last mistake. Without a ship you could still swim away - but now you're going to stay here forever.";
					link.l1.go = "Convict_Fight";
					AddCharacterExpToSkill(pchar, "Leadership", 30);
					AddCharacterExpToSkill(pchar, "Sneak", 30);
				break;
			}
		break;
	
		case "Convict_15_1_1End":
			AddQuestRecord("Convict", "4");
			AddQuestUserData("Convict", "sSex", GetSexPhrase("",""));
			AddQuestUserData("Convict", "sShoreName", XI_ConvertString(pchar.GenQuest.Convict.ShoreLocation + "Acc"));
			CloseQuestHeader("Convict");
			AddDialogExitQuestFunction("Convict_DialogDisable");
			AddDialogExitQuestFunction("Convict_SetConvictToShip");
			AddDialogExitQuest("OpenTheDoors");
			DialogExit();
		break;
	
		case "Convict_15_1_2End":
			AddQuestRecord("Convict", "5");
			AddQuestUserData("Convict", "sSex", GetSexPhrase("","а"));
			AddQuestUserData("Convict", "sShoreName", XI_ConvertString(pchar.GenQuest.Convict.ShoreLocation + "Acc"));
			CloseQuestHeader("Convict");
			AddDialogExitQuestFunction("Convict_DialogDisable");
			AddDialogExitQuestFunction("Convict_SetConvictToShip");
			AddDialogExitQuest("OpenTheDoors");
			DialogExit();
		break;	
	
		case "Convict_15_2":
			AddQuestRecord("Convict", "3");
			AddQuestUserData("Convict", "sSex", GetSexPhrase("",""));
			CloseQuestHeader("Convict");
			for(i = 0; i < sti(pchar.GenQuest.Convict.ConvictQty); i++)
			{
				sld = CharacterFromID("Convict_" + i);
				sld.LifeDay = 0;
			}	
			ChangeCharacterComplexReputation(pchar,"nobility", -2);	
			LAi_group_Delete("ConvictGroup");
			DeleteAttribute(pchar, "GenQuest.Convict");
			DialogExit();
			AddDialogExitQuestFunction("Convict_DialogDisable");
			AddDialogExitQuest("OpenTheDoors");
		break;
		
		case "Convict_16":
			dialog.text = RandPhraseSimple("So, captain? Can we start loading ourselves?","Finally! We have already begun to worry - we thought that you have changed your mind.");
			link.l1 = "Sorry, I've got a change of plans. You'll have to look for a different captain now.";
			link.l1.go = "Convict_16_1";
			if(pchar.GenQuest.Convict == "ToMayak")
			{
				link.l2 = "Load up into the boat, I don't have much time.";
				link.l2.go = "Convict_16_2";			
			}			
			if(pchar.GenQuest.Convict == "ToShore" && GetFreeCrewQuantity(pchar) >= sti(pchar.GenQuest.Convict.ConvictQty))
			{
				link.l2 = "Load up into the boat, I don't have much time.";
				link.l2.go = "Convict_16_2";			
			}			
		break;
		
		case "Convict_16_1":
			if(rand(1) == 0)
			{
				dialog.text = "Damn you! Surely you have already sent a patrol after us?! You won't get away with this!";
				link.l1 = "What are you talking about?! You wanna die or what?!";
				link.l1.go = "Convict_Fight";
				pchar.GenQuest.Convict = "ShoreFight";
				SetFunctionExitFromLocationCondition("Convict_LocExit", pchar.location, false);
			}
			else
			{
				dialog.text = "Captain "+ GetSexPhrase(", are you a man of your word or what","?") +" Or are you just a fucking babbler...";
				link.l1 = "You'd better watch your tongue...";
				link.l1.go = "Convict_16_3";
			}
		break;
		
		case "Convict_16_2":
			if(pchar.GenQuest.Convict == "ToShore")
			{
				AddCharacterExpToSkill(pchar, "Leadership", 30);
				AddCharacterCrew(pchar, sti(pchar.GenQuest.Convict.ConvictQty));
				OfficersReaction("bad");
				pchar.GenQuest.Convict = "close";
				AddQuestRecord("Convict", "10");
				CloseQuestHeader("Convict");				
				SetFunctionExitFromLocationCondition("Convict_LocExit", pchar.location, false);
			}
			if(pchar.GenQuest.Convict == "ToMayak")
			{
				AddQuestRecord("Convict", "10");
				sld = characterFromId("Convict_0");
				AddPassenger(pchar, sld, false);
				SetCharacterRemovable(sld, false); 
				SetFunctionExitFromLocationCondition("Convict_LocExit", pchar.location, false);
				SetFunctionLocationCondition("Convict_OnMayak", pchar.GenQuest.Convict.Mayak, true);
				locations[FindLocation(pchar.GenQuest.Convict.Mayak)].DisableEncounters = true;			
			}
			DialogExit();
			AddDialogExitQuestFunction("Convict_DialogDisable");
			AddDialogExitQuest("OpenTheDoors");
		break;
		
		case "Convict_16_3":
			ChangeCharacterComplexReputation(pchar,"nobility", -2);
			OfficersReaction("bad");
			pchar.GenQuest.Convict = "close";
			AddQuestRecord("Convict", "3");
			AddQuestUserData("Convict", "sSex", GetSexPhrase("",""));
			CloseQuestHeader("Convict");				
			SetFunctionExitFromLocationCondition("Convict_LocExit", pchar.location, false);
			AddDialogExitQuestFunction("Convict_DialogDisable");			
			DialogExit();
			AddDialogExitQuest("OpenTheDoors");
		break;
						
		case "Convict_17":
			dialog.text = LinkRandPhrase("Oh, thank you, "+ GetSexPhrase("kind man","fair lass") +".","Thank you, captain - you've really taken me out of the noose.","Much appreciate such a fine voyage.");
			link.l1 = LinkRandPhrase("That's all fine and good, but I am waiting for the money.","It's time to pay, you know.","Cash on the nail, as we agreed.");
			link.l1.go = "Convict_17_1";
		break;
		
		case "Convict_17_1":
			switch(sti(pchar.GenQuest.Convict.variant))
			{
				case 1:
					dialog.text = "Of course, what questions! Here's your money in gold ingots and please accept our most sincere gratitude.";
					link.l1 = "Good luck to you, too. Farewell.";
					link.l1.go = "Convict_17_1_1End";
					AddCharacterExpToSkill(pchar, "Sailing", 80);
					AddCharacterExpToSkill(pchar, "Commerce", 80);
					TakeNItems(pchar, "jewelry5", makeint(sti(pchar.GenQuest.Convict.Sum)/200));
					break;
				case 2:
					dialog.text = "Captain, you know, we thought that money really isn't that important in life. And, frankly, we need it much more than you at this point. But we have one thing we had stolen from our former boss. Perhaps, it would interest you a lot more than gold. Wanna take a look?...";
					link.l1 = "Yeah, you're right. That's a marvelous thing, indeed. Alright - thanks and farewell.";
					link.l1.go = "Convict_17_1_2End";
					AddCharacterExpToSkill(pchar, "Sailing", 80);
					AddCharacterExpToSkill(pchar, "Fortune", 80);
					GiveItem2Character(pchar, pchar.GenQuest.Convict.Item);
					break;
				case 3:
					dialog.text = "Why do you need that much money? You're rich anyway. You've helped us - we'll help you to on another occasion.";
					link.l1 = "There won't be such an occasion. Say your prayers, scoundrels, I am not condoning debts.";
					link.l1.go = "Convict_Fight";
					pchar.GenQuest.Convict = "MayakFight";
					SetFunctionExitFromLocationCondition("Convict_LocExit", pchar.location, false);				
					AddCharacterExpToSkill(pchar, "Sailing", 80);
					AddCharacterExpToSkill(pchar, "Sneak", 80);			
					break;
			}
		break;
		
		
		case "Convict_17_1_1End":
			AddQuestRecord("Convict", "11");
			AddQuestUserData("Convict", "sSex", GetSexPhrase("",""));
			AddQuestUserData("Convict", "sMayak", XI_ConvertString(pchar.GenQuest.Convict.Mayak + "Abl"));		
			AddQuestUserData("Convict", "sSum", makeint(pchar.GenQuest.Convict.Sum));
			CloseQuestHeader("Convict");
			pchar.GenQuest.Convict = "close";
			SetFunctionExitFromLocationCondition("Convict_LocExit", pchar.location, false);
			DialogExit();
			AddDialogExitQuest("OpenTheDoors");
		break;
		
		case "Convict_17_1_2End":
			AddQuestRecord("Convict", "12");
			AddQuestUserData("Convict", "sSex", GetSexPhrase("",""));
			AddQuestUserData("Convict", "sMayak", XI_ConvertString(pchar.GenQuest.Convict.Mayak + "Abl"));		
			CloseQuestHeader("Convict");
			pchar.GenQuest.Convict = "close";
			SetFunctionExitFromLocationCondition("Convict_LocExit", pchar.location, false);
			DialogExit();
			AddDialogExitQuest("OpenTheDoors");
		break;		
		// <-- Генератор "State convicts"
		
		// Генератор "A reason to hurry" -->
		// Встреча с ОЗГ на берегу
		case "ReasonToFast_Hunter1":
			dialog.text = "I was sent here by "  + GetName( NAMETYPE_MAIN, pchar.questTemp.ReasonToFast.p3, NAME_NOM) + " himself...";
			link.l1 = GetName( NAMETYPE_MAIN, pchar.questTemp.ReasonToFast.p3, NAME_NOM) + " is waiting for you with a reply for a couple of hours already. He sent me immediately after you.";
			link.l1.go = "ReasonToFast_Hunter4";
		break;
		
		case "ReasonToFast_Hunter2":
			dialog.text = "I've been following you in your wake for quite some time, but you're just too quick.";
			link.l1 = "And so what?";
			link.l1.go = "ReasonToFast_Hunter6";		
		break;
		
		case "ReasonToFast_Hunter3":
			dialog.text = "Better tell me how much does the governor pay his underlings?";
			link.l1 = "Dammit!";
			link.l1.go = "ReasonToFast_Fight";		
		break;
		
		case "ReasonToFast_Hunter4":
			dialog.text = "I haven't been drinking! I was looking for the bosun...";
			link.l1 = "Go now... I'll tell "  + GetName( NAMETYPE_MAIN, pchar.questTemp.ReasonToFast.p3, NAME_DAT) + ", that you were lost in the jungle.";
			link.l1.go = "ReasonToFast_Hunter5";		
			AddQuestRecord("ReasonToFast", "5");
			AddQuestUserData("ReasonToFast", "sName", GetName( NAMETYPE_MAIN, pchar.questTemp.ReasonToFast.p3, NAME_GEN));
		break;
		
		case "ReasonToFast_Hunter5":
			LAi_SetPlayerType(pchar);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			AddDialogExitQuest("ReasonToFast_HunterGoOut");
		break;
		
		case "ReasonToFast_Hunter6":
			pchar.questTemp.ReasonToFast = "MeetHunterFail";
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			AddDialogExitQuest("ReasonToFast_PatrolAngry");
		break;
		
		case "ReasonToFast_Fight":
			LAi_SetPlayerType(pchar);
			pchar.questTemp.ReasonToFast = "PatrolAngry";
			pchar.questTemp.ReasonToFast.relation = GetNationRelation2MainCharacter(sti(pchar.questTemp.ReasonToFast.GuardNation));
			SetNationRelation2MainCharacter(sti(pchar.questTemp.ReasonToFast.GuardNation), RELATION_ENEMY); 
			pchar.GenQuest.HunterScore2Pause = 1; //НЗГ не начисляются
			pchar.GenQuest.ReputationNotChange = 1; //репутацию не менять
			sTemp = "Patrol" + pchar.questTemp.ReasonToFast.LocIdx + "_";
			sGroup = "PatrolGroup_" + pchar.questTemp.ReasonToFast.LocIdx;
			LAi_LocationFightDisable(&locations[FindLocation(pchar.questTemp.ReasonToFast.PatrolLocation)], false);	
			iTemp = sti(pchar.questTemp.ReasonToFast.PatrolNum);
			chrDisableReloadToLocation = true;
			rChar = CharacterFromID("ReasonToFast_Hunter");
			LAi_SetWarriorType(rChar);
			LAi_group_MoveCharacter(rChar, sGroup);
			for(i = 0; i < iTemp; i++)
			{
				rChar = CharacterFromID(sTemp + i);
				LAi_SetWarriorType(rChar);
				LAi_group_MoveCharacter(rChar, sGroup);
			}			
			LAi_group_SetRelation(sGroup, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups(sGroup, LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck(sGroup, "OpenTheDoors"); 
			LAi_group_SetCheck(sGroup, "ReasonToFast_PatrolDied");
			DialogExit();	
			AddDialogExitQuest("MainHeroFightModeOn");		
		break;
		
		// бой с кэпом пиратского корабля
		case "ReasonToFast_FightCap": 
			dialog.text = "And you are a smart one. Pray to the God that your tricks won't become known to " + GetName( NAMETYPE_MAIN, pchar.questTemp.ReasonToFast.p3, NAME_NOM) + ".";
			link.l1 = "He will not know if you don't tell him... And you will not, will you?";
			link.l1.go = "ReasonToFast_FightCap_1";
		break;
		
		case "ReasonToFast_FightCap_1":
			dialog.text = "Why? Surely, I will, and with great pleasure!";
			link.l1 = "He will hang you anyway for that folly. So let's not waste time, and I will help you to escape the gallows.";
			link.l1.go = "ReasonToFast_FightCap_2";
		break;
		
		case "ReasonToFast_FightCap_2":
			dialog.text = "Hmm... And how are you going to do that?";
			link.l1 = "I will kill you myself...";
			link.l1.go = "ReasonToFast_FightCap_Last";
		break;
		
		case "ReasonToFast_FightCap_Last":
			LAi_SetCurHPMax(NPChar);
			LAi_GetCharacterMaxEnergy(NPChar);
			QuestAboardCabinDialogExitWithBattle(""); 
			DialogExit();	
			AddDialogExitQuest("MainHeroFightModeOn");		
		break;		
		
		// встреча с лакеем в резиденции
		case "ReasonToFast_Lakey":
			dialog.text = "Do you have business here, "+ GetSexPhrase("monsieur","mademoiselle") +"?";
			link.l1 = "No-no, I am here by invitation of the governor's charming wife, seeing round this truly luxurious residence.";
			link.l1.go = "ReasonToFast_Lakey1";
			link.l2 = "I have a message from people you know.";
			link.l2.go = "ReasonToFast_Lakey2";
			link.l3 = "Yes. I want to bring you to justice!";
			link.l3.go = "ReasonToFast_Lakey3";
			pchar.questTemp.ReasonToFast = "MeetLakey";
			pchar.questTemp.ReasonToFast.SpeakOther = true;			
		break;
		
		case "ReasonToFast_Lakey1":
			NextDiag.TempNode = "ReasonToFast_Lakey11";
			dialog.text = "Oh yeah, I was really lucky to serve in such a beautiful house.";
			link.l1 = "No wonder...";
			link.l1.go = "ReasonToFast_Lakey11";
		break;

		case "ReasonToFast_Lakey11":
			NextDiag.TempNode = "ReasonToFast_Lakey11";
			dialog.text = "Don't forget to take a look at our garden!";
			link.l1 = "Thank you, good man!";
			link.l1.go = "exit";			
			bDisableFastReload = false;
		break;
		
		case "ReasonToFast_Lakey2":
			dialog.text = "Ehh... " + pchar.questTemp.ReasonToFast.password + "?";
			link.l1.edit = 1;			
			link.l1 = ""; 
			link.l1.go = "ReasonToFast_Lakey21";
		break;

		case "ReasonToFast_Lakey3":
			dialog.text = "You will not get away with this, Judas!";
			link.l1 = "Hold still, scoundrel!!!";
			link.l1.go = "ReasonToFast_Lakey_exit";
			pchar.questTemp.ReasonToFast = "LakeyExitFail";
			bDisableFastReload = false;			
		break;

		case "ReasonToFast_Lakey21":
			if(GetStrSmallRegister(pchar.questTemp.ReasonToFast.ShipName) == GetStrSmallRegister(dialogEditStrings[1]))
			{
				dialog.text = "Quick now! Take everything valuable and take flight!";
				link.l1 = "I think you should take flight, too.";
				link.l1.go = "ReasonToFast_Lakey_exit";
				TakeNItems(pchar,"icollection", sti(pchar.questTemp.ReasonToFast.p8));
				TakeNItems(pchar,"Chest", sti(pchar.questTemp.ReasonToFast.p7));
				pchar.questTemp.ReasonToFast = "LakeyExitSuccess";					
				bDisableFastReload = true;		
				//chrDisableReloadToLocation = true;			
			}
			else
			{
				dialog.text = "Mmm, excuse me, I must take my leave.";
				link.l1 = "Hold still, scoundrel!!!";
				link.l1.go = "ReasonToFast_Lakey_exit";
				pchar.questTemp.ReasonToFast = "LakeyExitFail";
				bDisableFastReload = false;
			}			 
		break;

		case "ReasonToFast_Lakey_exit":
			DialogExit();	
			DeleteAttribute(pchar, "GenQuest.CannotWait");
			pchar.quest.ReasonToFast_ClearLakey.over = "yes"; //снимаем таймер
			ReasonToFast_SetHunterCoastal();
			AddDialogExitQuest("ReasonToFast_LakeyGoOut");
		break;		
		
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("You're "+ GetSexPhrase("a thief, I see! Guards, seize him","a thief, I see! Guards, seize her") +"!!!", "I can't believe it! I turned away for a second - and you're diving into my chest! Stop thief!!!", "Guards! Robbery! Stop thief!!!");
			link.l1 = "Aaaah, devil!!!";
			link.l1.go = "ReasonToFast_Lakey_exit";
			pchar.questTemp.ReasonToFast = "LakeyExitFail";
			bDisableFastReload = false;
		break; 
		// Генератор "A reason to hurry" <--
		
		// ситуации с капитаном захваченного корабля
		// взрыв на корабле
		case "ShipSituation11": // пираты или ДУ
			dialog.text = RandPhraseSimple("Hi, "+ GetSexPhrase("buddy","lass") +"! I've prepared a surprise for you - I ignited the cord to the powder chamber. It's gonna blow up to kingdom come!","Why are you standing there? There is a fire in the powder chamber! It's gonna blow, and the fireworks will be seen in Europe!");
			link.l1 = RandPhraseSimple("You scoundrel, you will not trick me! Fight, you coward!","I see the rats abandoning ship - and you are among the first?");
			link.l1.go = "ShipSituation12";
		break;
		
		case "ShipSituation12":
			dialog.text = RandPhraseSimple("You should run too, if you cherish your life... Oh, well, I have no time - a boat is waiting for me. Have a nice time fishing!","I don't have time for playing a hero - boys in the boat are waiting for me. Have a nice time fishing, winner!");
			link.l1 = RandPhraseSimple("Damn it! Cut the fenders! Go off!","Oh, god, how could we get into such mess! Open the sea inlets! Pull off!");
			link.l1.go = "ShipSituation_End";
		break;
		
		case "ShipSituation21": // военный корабль (не флагман)
			dialog.text = "So what?! You think, you won the fight?! No way. I have set a powder-room on fire, you won't get away from this ship alive.";
			link.l1 = RandPhraseSimple("You scoundrel, you will not trick me! Fight, you coward!","I see the rats abandoning ship - and you are among the first?");
			link.l1.go = "ShipSituation22";
		break;
		
		case "ShipSituation22":
			dialog.text = RandPhraseSimple("I am bound by an oath, but that doesn't mean I have to die to no good. Sorry for not offering you a place in the boat - the sailors will not understand.","The ships are bound to each other in the boarding, so your fate is sealed. Excuse me, but my boat is waiting...");
			link.l1 = RandPhraseSimple("Damn it! Cut the fenders! Go off!","Oh, god, how could we get into such mess! Open the sea inlets! Pull off!");
			link.l1.go = "ShipSituation_End";
		break;
		
		case "ShipSituation31": // ОЗГ
			dialog.text = RandPhraseSimple("You are victorious! Welcome to hell! I have set a powder-room on fire.","Here you are, my good man! You are done - I have set a powder-room on fire.");
			link.l1 = RandPhraseSimple("You scoundrel, you will not trick me! Fight, you coward!","I see the rats abandoning ship - and you are among the first?");
			link.l1.go = "ShipSituation32";
		break;
		
		case "ShipSituation32":
			dialog.text = RandPhraseSimple("I'd been tracking you for quite some time. A pity that I had to sacrifice my ship, but your head is worth two new ones, anyway. Have a nice time fishing!","See how you are going to go? With fireworks, like an Indian prin"+ GetSexPhrase("ce","cess") +". But I will not come off as a loser - your head is worth a lot more than my ship. Farewell now, my boat is not going to wait for too long...");
			link.l1 = RandPhraseSimple("Damn it! Cut the fenders! Go off!","Oh, god, how could we get into such mess! Open the sea inlets! Pull off!");
			link.l1.go = "ShipSituation_End";			
		break;
		
		case "ShipSituation_End":
			AddCharacterExpToSkill(pchar, "Sneak", 200);
			DialogExit();
			LAi_SetActorType(NPChar); 
			LAi_ActorRunToLocation(NPChar, "reload", "reload1", "none", "", "", "", -1);
			NPChar.LifeDay = 0;
			LAi_LockFightMode(pchar, false);	
			Log_Info(XI_ConvertString("Ship can explode"));
			pchar.GenQuest.ShipSituation.Explosion = ShipSituation_4;	
			pchar.GenQuest.ShipSituation.Explosion.CapId = NPChar.CaptanId;
			LAi_EnableReload();
			Log_SetActiveAction("Reload");
		break;
		
		// эпидемия
		case "ShipEpidemy1":
			AddCharacterExpToSkill(pchar, "Fortune", 200);
			dialog.text = RandPhraseSimple("Hold on, captain! For a couple of words.","Hold on, captain! I think this could be interesting for you.");
			link.l1 = LinkRandPhrase("Why talking during a fight?!","And what is it that I should talk about with a dead man?","What's the deal? You want to make a will in my name?");
			link.l1.go = "ShipEpidemy2";
		break;
		
		case "ShipEpidemy2":
			dialog.text = "There's an outbreak of disease on board. I've lost a quarter of my crew during the journey. You are all doomed...";
			link.l1 = RandPhraseSimple("You rotten scumbag! Why didn't you display a signal that there's a disaster on your ship?!","Have you forgotten the sea code? You should have displayed a signal on the mast that there's a disaster on your ship!");
			link.l1.go = "ShipEpidemy3";
		break;
		
		case "ShipEpidemy3":
			dialog.text = "We were about to die, anyway. That's why we haven't given up - we wanted to take you and your minions to the next world with us! Now I am fully satisfied. You may finish your foul deed.";
			link.l1 = RandPhraseSimple("I'll make you answer for that!..","I like the idea of you dying first. And I will watch it.");
			link.l1.go = "ShipEpidemy31";
			link.l2 = RandPhraseSimple("I will not stain my blade with your foul blood - you may live, although... what for? I am taking my crew away from that rotten old tub.","You should be sent to the gallows for that, but there's no need for that now. I am taking my men away... You may live, although your time should be short...");
			link.l2.go = "ShipEpidemy32";
			pchar.GenQuest.ShipSituation.Epidemy.CapId = NPChar.CaptanId;
			pchar.GenQuest.ShipSituation.Epidemy = ShipSituation_4;
		break;
		
		case "ShipEpidemy31":
			pchar.GenQuest.QuestAboardCabinDialogIdx = NPChar.index;
			pchar.GenQuest.ShipSituation.Epidemy.CapState = "Died"; // вражеский кэп на волосок от смерти от переизбытка стали и свинца в организме
			LAi_LockFightMode(pchar, false);
			QuestAboardCabinDialogExitWithBattle(""); 
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "ShipEpidemy32":
			DialogExit();
			LAi_SetActorType(NPChar); 
			LAi_ActorGoToLocation(NPChar, "reload", "reload1", "none", "", "", "", -1);
			LAi_LockFightMode(pchar, false);	
			pchar.GenQuest.ShipSituation.Epidemy.CapState = "Live"; // вражеский кэп остался в живых
			LAi_EnableReload();
			Log_SetActiveAction("Reload");
		break;
		// ситуации с капитаном захваченного корабля
		
		// Генератор "A damsel in the jungle"
		case "EncGirl_Lover":
			dialog.text = "Hello, captain, I was told that you were looking for me.";
			link.l1 = "I am - if you are " + pchar.GenQuest.EncGirl.sLoverId + ".";
			link.l1.go = "EncGirl_Lover1";
		break;
		
		case "EncGirl_Lover1":
			dialog.text = "That I am. Anything important?";
			link.l1 = "I don't know if that's important to you, but I've brought " + pchar.GenQuest.EncGirl.name +". She ran away from home and is now waiting for you not far from the tavern.";
			link.l1.go = "EncGirl_Lover2";
		break;
		
		case "EncGirl_Lover2":
			dialog.text = "Oh my... I knew it all would end up like that... And why did she run away? Did she tell you?";
			link.l1 = "Her father wants to marry her off to the usurer's son.";
			link.l1.go = "EncGirl_Lover3";
		break;
		
		case "EncGirl_Lover3":
			pchar.GenQuest.EncGirl.LoverCity = GetQuestNationsCity(sti(pchar.GenQuest.EncGirl.nation));
			pchar.GenQuest.EncGirl.LoverIsland = GetIslandByCityName(pchar.GenQuest.EncGirl.LoverCity);
			dialog.text = "Oh no, we cannot allow that to happen! Captain, you know, I am in such a stupid situation... I wanted to ask you to take us to " + XI_ConvertString(pchar.GenQuest.EncGirl.LoverIsland + "Acc") + " to town called " + XI_ConvertString("Colony" + pchar.GenQuest.EncGirl.LoverCity) + ", but right now I don't have any money - I still haven't found a job. I have a wealthy family and a promising career in " + XI_ConvertString("Colony" + pchar.GenQuest.EncGirl.LoverCity) + "…\nI assure you, my parents will be glad to see me with a young fiancee and they will reward you well. So, are you in?";
			link.l1 = "...Listen now, I have totally different plans. I can give you an advice to get a job as a sailor and rent a cabin for your bride for your wage. People get to Europe in such a manner, and that settlement of yours is in a bird's night flight.";
			link.l1.go = "EncGirl_Lover4";
			link.l2 = "Oh, the youth... Do you realize what you're asking about? Taking a girl away from her parents without their blessing? Sure, I'll do that!";
			link.l2.go = "EncGirl_Lover5";
		break;
		
		case "EncGirl_Lover4":
			npchar.lifeDay = 0;
			AddDialogExitQuestFunction("EncGirl_LoverExit");	
			DialogExit();
		break;
		
		case "EncGirl_Lover5":
			AddDialogExitQuestFunction("EncGirl_ToLoverParents");	
			DialogExit();
		break;
		
		case "EncGirl_Lover6":
			AddSimpleRumourCityTip(RandPhraseSimple("Have you heard, " + pchar.GenQuest.EncGirl.name + " ran off with her lover. She decided not to bind her life to an invalid. That's surely the fault of her parents - they should not have become tempted with the money of her fiance and try to give such a beauty in marriage to a fright.",  
				"Have you heard?" + pchar.GenQuest.EncGirl.name + " tricked both her dad and her would-be fiance. They say one noble captain helped her and her lover to get to another island, where her lover's parents lived... Imagine that - there still are people, who had not yet forgotten the taste of passion!"), pchar.GenQuest.EncGirl.LoverCity, 3, 2, "citizen,habitue", "");
			dialog.text = "Thank you, captain. We will remember your help for the rest of our days.";
			link.l1 = "It was nothing. I hope everything will play well for you.";
			link.l1.go = "EncGirl_Lover7";
		break;
		
		case "EncGirl_Lover7":
			switch (rand(4))
			{
				case 0:
					sTemp = "the shop";
					pchar.GenQuest.EncGirl.LoverFather = "store_keeper";
				break;
				case 1:
					sTemp = "the shipyard";					
					pchar.GenQuest.EncGirl.LoverFather = "shipyard_keeper";
				break;
				case 2:
					sTemp = "the port office";					
					pchar.GenQuest.EncGirl.LoverFather = "portman_keeper";
				break;
				case 3:
					sTemp = "the tavern";					
					pchar.GenQuest.EncGirl.LoverFather = "tavern_keeper";
				break;
				case 4:
					sTemp = "the bank";					
					pchar.GenQuest.EncGirl.LoverFather = "usurer_keeper";
				break;
			}	
			pchar.GenQuest.EncGirl.FatherLoc = sTemp;
			dialog.text = "I promised to introduce you to my parents. If you happen to have a free minute, please come to " + sTemp + ", my father works there, and I'll tell him what you have done for us. I am sure he will be delighted to see you.";
			link.l1 = "Alright, I'll drop in once I have a moment. Be happy, you both...";
			link.l1.go = "EncGirl_Lover8";
		break;
		
		case "EncGirl_Lover8":
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "", 5.0);
			npchar.lifeday = 0;
			AddQuestRecord("JungleGirl", "16");
			AddQuestUserData("JungleGirl", "sSex", GetSexPhrase("","а"));
			AddQuestUserData("JungleGirl", "sText", pchar.GenQuest.EncGirl.FatherLoc);
			if((GetSummonSkillFromName(pchar, SKILL_FORTUNE) + GetSummonSkillFromName(pchar, SKILL_LEADERSHIP)) < 175)
			{
				pchar.GenQuest.EncGirl.LoverFatherAngry = 0; // папочка жениха счастлив за сына :)
			}
			else
			{
				pchar.GenQuest.EncGirl.LoverFatherAngry = 1; // папочка жениха разъярен за то что сын притащил в дом шалаву :)
			}
			chrDisableReloadToLocation = false; 
			pchar.GenQuest.EncGirl = "toLoverFather";
			pchar.quest.EncGirl_GetLoverFather.win_condition.l1 = "Timer";
			pchar.quest.EncGirl_GetLoverFather.win_condition.l1.date.day = GetAddingDataDay(0, 0, 2);
			pchar.quest.EncGirl_GetLoverFather.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 2);
			pchar.quest.EncGirl_GetLoverFather.win_condition.l1.date.year = GetAddingDataYear(0, 0, 2);
			pchar.quest.EncGirl_GetLoverFather.function = "EncGirl_GenQuest_GetLoverFather";
			DialogExit();	
		break;
		// Генератор "A damsel in the jungle"
		
		// Генератор "Captain's request"
		case "CaptainComission_1":
			dialog.text = RandPhraseSimple("Hold on! Hold on, captain! Please.","Captain, please, wait, I beg you...");
			link.l1 = LinkRandPhrase("What? Lost your breath?","Raise your blade, you coward!","What's up? You forgot to make up a will?");
			link.l1.go = "CaptainComission_2";
		break;
		
		case "CaptainComission_2":
			dialog.text = "Wait... I am wounded and I am to weak to keep fighting... I am not asking for mercy, but I have an unfinished business. Please, promise me that you'd fulfill the last will of a dying man.";
			link.l1 = RandPhraseSimple("Don't be a milksop, captain, accept death like a man is supposed to!","Captain, what a sentimentality? A battle is raging around, so let's finish what we'd started.");
			link.l1.go = "CaptainComission_21";
			link.l2 = "Speak now and be quick.";
			link.l2.go = "CaptainComission_22";
		break;
		
		case "CaptainComission_21":
			LAi_SetCurHPMax(NPChar);
			LAi_GetCharacterMaxEnergy(NPChar);
			ChangeCharacterComplexReputation(pchar,"nobility", -2);
			DeleteAttribute(pchar,"GenQuest.CaptainComission");
			QuestAboardCabinDialogExitWithBattle(""); 
			DialogExit();	
			AddDialogExitQuest("MainHeroFightModeOn");		
		break;
		
		case "CaptainComission_22":		
			if(rand(1) == 0) // "Ransom"
			{
				CaptainComission_Init(NPChar);
				dialog.text = "Tell " + pchar.GenQuest.CaptainComission.Name + " from the settlement of " + XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City) + ", that I failed to fulfill his request... before I had time to... May he forgive me...";
				link.l1 = RandPhraseSimple("And that's it?! Fine, I can do it. Hey, friend...","Alright, I'll tell him if I have time. Hey, friend...");
				link.l1.go = "CaptainComission_22_1";
				link.l2 = "I don't think so. I have no time for such nonsense. Let's finish what we'd started.";
				link.l2.go = "CaptainComission_22_2";
			}
			else // "Operation 'Galleon'"
			{			
				CaptainComission_GaleonInit(NPChar);
				dialog.text = "Please, tell the captain of a patrol " + GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType), "Name") + "Acc")) + " '" + pchar.GenQuest.CaptainComission.ShipTypeName + "' " + pchar.GenQuest.CaptainComission.Name + ", that he shouldn't show his face in " + XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Dat") + "... " +
							"The authorities are aware of his death's true circumstances " + GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipTypeVictim), "Name") + "Acc")) + " '" + pchar.GenQuest.CaptainComission.VictimShipName + "... time is short, he's going to be arrested... sailing to " + XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Acc") + " from " + XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City1 + "Gen") +", the voyage will take almost fifteen days... should hurry...";
				link.l1 = RandPhraseSimple("I don't promise anything, but I'll try on the occasion. Hey, friend...","Alright, I'll tell him if I have time. Hey, friend...");
				link.l1.go = "CaptainComission_300";
			}						
		break;
		
		case "CaptainComission_22_1":
			ReOpenQuestHeader("CaptainComission1");
			AddQuestRecord("CaptainComission1", "1");
			AddQuestUserData("CaptainComission1", "sShipName", pchar.GenQuest.CaptainComission.ShipName);
			AddQuestUserData("CaptainComission1", "sCapName", pchar.GenQuest.CaptainComission.CapName);
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City));	
			SetFunctionTimerCondition("CaptainComission_Speak", 0, 0, 30, false);
			SetFunctionTimerCondition("CaptainComission_SellSlave", 0, 0, 15 + rand(5), false);
			LAi_KillCharacter(NPChar);
			LAi_SetPlayerType(pchar); 
			pchar.GenQuest.CaptainComission = "Begin_1";
			LAi_EnableReload();
			Log_SetActiveAction("Reload");
			DialogExit();	
		break;
		
		case "CaptainComission_22_2":
			dialog.text = "Such a cruelty! I hope you will answer for that.";
			link.l1 = "And for a lot more...";
			link.l1.go = "CaptainComission_22_3";
		break;
		
		case "CaptainComission_22_3":
			ReOpenQuestHeader("CaptainComission1");
			AddQuestRecord("CaptainComission1", "1");
			AddQuestUserData("CaptainComission1", "sShipName", pchar.GenQuest.CaptainComission.ShipName);
			AddQuestUserData("CaptainComission1", "sCapName", pchar.GenQuest.CaptainComission.CapName);
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City));
			SetFunctionTimerCondition("CaptainComission_Speak", 0, 0, 30, false);
			SetFunctionTimerCondition("CaptainComission_SellSlave", 0, 0, 15 + rand(5), false);
			LAi_SetCurHPMax(NPChar);
			LAi_GetCharacterMaxEnergy(NPChar);
			ChangeCharacterComplexReputation(pchar,"nobility", -3);
			pchar.GenQuest.CaptainComission = "Begin_2";
			QuestAboardCabinDialogExitWithBattle(""); 
			DialogExit();	
			AddDialogExitQuest("MainHeroFightModeOn");		
		break;
		
		case "CaptainComission_3":
			dialog.text = LinkRandPhrase("I am listening to you, " + GetAddress_Form(pchar) + ".","What did you want?","How may I help you?");
			link.l1 = "Are you " + pchar.GenQuest.CaptainComission.Name + "? I have business with you. Captain " + pchar.GenQuest.CaptainComission.CapName + " asked me to pass you an important information.";
			link.l1.go = "CaptainComission_4";
		break;
		
		case "CaptainComission_4":
			dialog.text = "Did he? Alright. So, what is it that captain " + pchar.GenQuest.CaptainComission.CapName + "wanted me to know?";
			link.l1 = "He asked me to tell you that he would not be able to fulfill your request.";
			link.l1.go = "CaptainComission_5";
		break;
		
		case "CaptainComission_5":
			dialog.text = "What are you talking about?! I've known him for ages, he's a very honest man. He simply couldn't have told you that!";
			link.l1 = "Let's say, it was for reasons beyond his control. In other words - he died.";
			link.l1.go = "CaptainComission_6";
		break;
		
		case "CaptainComission_6":
			CaptainComission_GetPirateIsland();
			CaptainComission_GetFamilyType();
			if(pchar.GenQuest.CaptainComission == "Begin_1")
			{
				dialog.text = "Ah, this is completely out of place! So much time wasted\n"
					+ "Captain, in that case, I have to ask you to help me. Pirates of  " + XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.PiratesCity + "Gen") + " have captured my relative " + pchar.GenQuest.CaptainComission.SlaveName + " and are demanding ransom for him. Could you undertake this mission? The reward should be quite generous.";
				link.l1 = "Unfortunately, I have other plans.";
				link.l1.go = "CaptainComission_6_1";
				link.l2 = "I will try to help you if you explain it in more detail.";
				link.l2.go = "CaptainComission_6_2";
			}
			if(pchar.GenQuest.CaptainComission == "Begin_2")
			{
				dialog.text = "Ah, this is completely out of place! So much time wasted\nAnd what about the chests?";
				link.l1 = "Mmm... what chests?";
				link.l1.go = "CaptainComission_6_3";
				pchar.GenQuest.CaptainComission.CanFindChest = true;
			}	
		break;
		
		case "CaptainComission_6_1":
			dialog.text = "A pity, captain... It's a pity that you are not willing to help me.";
			link.l1 = "That's not a matter of my will, my dear. You must understand. Farewell.";
			link.l1.go = "CaptainComission_6_1End";
		break;
		
		case "CaptainComission_6_2":
			dialog.text = "Yesterday I received a letter from " + ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_ACC) + ", in which he was notifying me that the ransom is going to be higher, and he is also threatening to sell him into slavery. The late captain should have notified " + ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_ACC) + ", that I agree with the former conditions, and make an advance payment. But now I see why the pirates have raised the stakes.";
			link.l1 = "And what are you suggesting?";
			link.l1.go = "CaptainComission_6_21";
		break;
		
		case "CaptainComission_6_3":
			dialog.text = "Oh, "+ GetSexPhrase("buddy","lass") +", I sense foul play here. I am warning you that this is very dangerous and can cause dire consequences. Captain " + pchar.GenQuest.CaptainComission.CapName + " had three chests full of gold, which he should have handed to " + ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_DAT) + " on " + XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.PiratesCity + "Acc") + " as a ransom for one man -  " + pchar.GenQuest.CaptainComission.SlaveName + ". And if he wanted you to come to us, he could not have forgotten to tell you about the chests.";
			link.l1 = "Perhaps, he just didn't have time for that?";
			link.l1.go = "CaptainComission_6_31";
		break;
		
		case "CaptainComission_6_1End":
			AddQuestRecord("CaptainComission1", "3");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			AddQuestUserData("CaptainComission1", "sCharType", GetStrSmallRegister(XI_ConvertString("Family" + pchar.GenQuest.CaptainComission.FamilyType + "Gen")));
			CloseQuestHeader("CaptainComission1");
			DeleteAttribute(pchar,"GenQuest.CaptainComission");
			ChangeCharacterComplexReputation(pchar,"nobility", -2);
			DialogExit();	
		break;
		
		case "CaptainComission_6_21":
			dialog.text = "I am left with no choice... I have already gathered the required sum - 150 000 pesos. I ask you to deliver it to " + XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.PiratesCity + "Acc") + " and bring my relative here. I will pay you 40 000 as soon as it is done.";
			link.l1 = "Alright, I am ready.";
			link.l1.go = "CaptainComission_6_22";
			link.l2 = "Unfortunately, I have other plans.";
			link.l2.go = "CaptainComission_6_1";			
		break;
		
		case "CaptainComission_6_22":
			dialog.text = "Then take the money and may our Lord bless you. But please, hurry up - I am afraid that " + ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_NOM) + " will not be waiting and will sell the poor soul into slavery.";
			link.l1 = "Wait for me here. I don't think it's gonna take too much time.";
			link.l1.go = "CaptainComission_6_22End";
		break;
		
		case "CaptainComission_6_22End":
			AddQuestRecord("CaptainComission1", "4");
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City));
			AddQuestUserData("CaptainComission1", "sPirateName", ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_DAT));
			AddQuestUserData("CaptainComission1", "sPirateCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.PiratesCity + "Acc"));
			AddQuestUserData("CaptainComission1", "sFamilyType", GetStrSmallRegister(XI_ConvertString("Family" + pchar.GenQuest.CaptainComission.FamilyType + "Gen")));
			AddQuestUserData("CaptainComission1", "sSlaveName",pchar.GenQuest.CaptainComission.SlaveName);
			addMoneyToCharacter(pchar, 150000);
			pchar.GenQuest.CaptainComission = "Begin_11";
			pchar.GenQuest.CaptainComission.AfterTavernSpeak = "goodSpeak";
			pchar.GenQuest.CaptainComission.GetSlave = "NoSlave";
			pchar.GenQuest.CaptainComission.toMayor = true;
			SetFunctionTimerCondition("CaptainComission_30DaysIsLeft", 0, 0, 30, false);
			NextDiag.TempNode = "CaptainComission_7";
			NextDiag.CurrentNode = NextDiag.TempNode; 
			DialogExit();
		break;
		
		case "CaptainComission_6_31":
			dialog.text = "It doesn't matter\nPeople who gathered the ransom won't care. They only need the result, breathing and in one peace - " + pchar.GenQuest.CaptainComission.SlaveName + ". So don't waste time.";
			link.l1 = "And what if I refuse?";
			link.l1.go = "CaptainComission_6_32";
		break;
						
		case "CaptainComission_6_32":
			dialog.text = "Actually, I don't need your consent. I am just notifying you that if you don't deliver " + pchar.GenQuest.CaptainComission.SlaveName + " alive and kicking to the tavern, I will send bounty hunters after you...";
			link.l1 = "Hmm... That's serious. And if I do?";
			link.l1.go = "CaptainComission_6_33";
		break;
		
		case "CaptainComission_6_33":
			dialog.text = "Then we shall discuss it further.";
			link.l1 = "Alright... Let's see how it works out.";
			link.l1.go = "CaptainComission_6_33End";
		break;
		
		case "CaptainComission_6_33End":
			AddQuestRecord("CaptainComission1", "5");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("","а"));
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("","ла"));
			AddQuestUserData("CaptainComission1", "sCapName",pchar.GenQuest.CaptainComission.CapName);
			AddQuestUserData("CaptainComission1", "sPirateName", ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_DAT));
			AddQuestUserData("CaptainComission1", "sPirateCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.PiratesCity + "Acc"));
			AddQuestUserData("CaptainComission1", "sSlaveName",pchar.GenQuest.CaptainComission.SlaveName);
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Gen"));
			pchar.GenQuest.CaptainComission = "Begin_22";
			pchar.GenQuest.CaptainComission.AfterTavernSpeak = "badSpeak";
			pchar.GenQuest.CaptainComission.GetSlave = "NoSlave";
			pchar.GenQuest.CaptainComission.toMayor = true;
			SetFunctionTimerCondition("CaptainComission_30DaysIsLeft", 0, 0, 30, false);
			NextDiag.TempNode = "CaptainComission_7";
			NextDiag.CurrentNode = NextDiag.TempNode; 
			DialogExit();
		break;
		
		case "CaptainComission_7":
			if(pchar.GenQuest.CaptainComission.GetSlave == "NoSlave")
			{
				if(pchar.GenQuest.CaptainComission.AfterTavernSpeak == "goodSpeak")
				{
					dialog.text = LinkRandPhrase("Hello, captain " + GetFullName(pchar) + ". Any news?","So, captain, have you already delivered the ransom?","Hello, I hope you've come with the good news?");
					if(makeint(pchar.money)>=150000)
					{
						link.l1 = "Unfortunately, my plans have changed, so I have to break our deal.";
						link.l1.go = "CaptainComission_7_1";
					}
					link.l2 = "Not yet. I am still busy with that.";
					link.l2.go = "CaptainComission_7_2";
				}
				if(pchar.GenQuest.CaptainComission.AfterTavernSpeak == "badSpeak")
				{
					dialog.text = LinkRandPhrase("Oh, glad to greet you, captain " + GetFullName(pchar) + ". Any good news?","So, captain, have you rescued our suffering friend?","Glad to see you alive and kicking, captain. What's the status of our mutual affair?");
					link.l1 = "No news so far, but  I am on it.";
					link.l1.go = "CaptainComission_7_3";
					link.l2 = "Listen, friend, and why are you trying to make me responsible for that deal?";
					link.l2.go = "CaptainComission_7_4";
				}
			}
			if(pchar.GenQuest.CaptainComission.GetSlave == "GetSlave")
			{
				if(pchar.GenQuest.CaptainComission.AfterTavernSpeak == "goodSpeak")
				{
					dialog.text = LinkRandPhrase("Hello, captain " + GetFullName(pchar) + ". Any news?","So, captain, have you already delivered the ransom?","Hello, I hope you've come with the good news?");
					link.l1 = "Yes. Your request was fulfilled, " + pchar.GenQuest.CaptainComission.SlaveName + " is on the board on my ship and is getting ready to come to the shore.";
					link.l1.go = "CaptainComission_30";
				}
				else
				{
					dialog.text = LinkRandPhrase("Oh, glad to greet you, captain " + GetFullName(pchar) + ". Any good news?","So, captain, have you rescued our suffering friend?","Glad to see you alive and kicking, captain. What's the status of our mutual affair?");	
					link.l1 = "I have brought a man, we talked about. He is onboard of my ship.";
					link.l1.go = "CaptainComission_32";
				}
			}
			if(pchar.GenQuest.CaptainComission.GetSlave == "SlaveDied")
			{
				if(pchar.GenQuest.CaptainComission.AfterTavernSpeak == "goodSpeak")
				{
					dialog.text = LinkRandPhrase("Hello, captain " + GetFullName(pchar) + ". Any news?","So, captain, have you already delivered the ransom?","Hello, I hope you've come with the good news?");
					link.l1 = "Greetings, " + pchar.GenQuest.CaptainComission.Name + ", I have to upset you.";
					link.l1.go = "CaptainComission_50";
				}
				else
				{
					dialog.text = LinkRandPhrase("Oh, glad to greet you, captain " + GetFullName(pchar) + ". Any good news?","So, captain, have you rescued our suffering friend?","Glad to see you alive and kicking, captain. What's the status of our mutual affair?");
					link.l1 = "The man, whom you were interceding for, died.";
					link.l1.go = "CaptainComission_60";
				}
			}
		break;
		
		case "CaptainComission_30":
			dialog.text = "Thank you, captain, you've done a great favor to our family. Here's your reward... There are three chests - that equals to 40 000 pesos exactly. Please, excuse me - I'll hurry to meet him now.";
			link.l1 = "Of course, have a warm meeting and good luck to you both.";
			link.l1.go = "CaptainComission_30_1";
			if(CheckAttribute(pchar, "GenQuest.CaptainComission.SlaveAddMoney"))
			{
				link.l2 = "I perfectly understand your impatience, but there have been unforeseen circumstances, which forced me to bear additional costs.";
				link.l2.go = "CaptainComission_31";
			}	
		break;
		
		case "CaptainComission_30_1":
			//addMoneyToCharacter(pchar, 25000);
			TakeNItems(pchar, "chest", 3);
			Log_Info("You have received credit chests");
			PlaySound("interface\important_item.wav");
			AddQuestRecord("CaptainComission1", "14");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission1", "sName", pchar.GenQuest.CaptainComission.SlaveName);
			CloseQuestHeader("CaptainComission1");
			ChangeCharacterComplexReputation(pchar,"nobility", 2);
			DialogExit();
			AddDialogExitQuestFunction("CaptainComission_EndTavern");
		break;
		
		case "CaptainComission_31":
			//addMoneyToCharacter(pchar, 25000);
			TakeNItems(pchar, "chest", 2);
			Log_Info("You have received credit chests");
			PlaySound("interface\important_item.wav");
			dialog.text = "I don't understand... We have already agreed on the sum of your payment, haven't we?";
			link.l1 = "We have, but instead of 150000 pesos I was forced to pay 200000, not to mention travelling to Barbados.";
			link.l1.go = "CaptainComission_31_1";
		break;
		
		case "CaptainComission_31_1":
			dialog.text = "Captain, this is only a result of your own sluggishness. Pirates didn't make any additional demands with me. What a strange manner - attempting to gain something at the cost of others' hardships?";
			link.l1 = "Alright, I see that it's futile to try and explain you anything...";
			link.l1.go = "CaptainComission_31_1End";
		break;
		
		case "CaptainComission_31_1End":
			AddQuestRecord("CaptainComission1", "15");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission1", "sName", pchar.GenQuest.CaptainComission.SlaveName);
			CloseQuestHeader("CaptainComission1");			
			DialogExit();
			AddDialogExitQuestFunction("CaptainComission_EndTavern");
		break;

		case "CaptainComission_32":
			dialog.text = "Excellent! And you've had your doubts that we'd work well together.";
			link.l1 = "But I had to spend a lot on this affair.";
			link.l1.go = "CaptainComission_32_1";
		break;
		
		case "CaptainComission_32_1":
			GetSlaveSpeciality();
			dialog.text = "I know, I know... But there's your fault in that as well. How could you have sunk three chests with gold, which we had to literally shake out of the treasury, so that " + NationNameNominative(sti(pchar.GenQuest.CaptainComission.Nation)) + " could have such a specialist " + pchar.GenQuest.CaptainComission.SlaveSpeciality + "?";
			link.l1 = "Know, that I won't give him to you without a proper compensation.";
			link.l1.go = "CaptainComission_32_2";
		break;
		
		case "CaptainComission_32_2":
			dialog.text = "Well, you are a smart man, surely, you understand that it is too late for bargaining. We could have arrested your vessel with her cargo.\nBut the compensation was provided before. Therefore, the government of " + NationNameGenitive(sti(pchar.GenQuest.CaptainComission.Nation)) + " congratulates you for a successful operation and presents you this valuable gift and a modest reward.";
			link.l1 = "Hmm... Well, still better than nothing. Take your precious specialist.";
			link.l1.go = "CaptainComission_32_2End";
		break;
		
		case "CaptainComission_32_2End":
			AddQuestRecord("CaptainComission1", "16");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("","а"));
			AddQuestUserData("CaptainComission1", "sSpeciality", pchar.GenQuest.CaptainComission.SlaveSpeciality);
			AddQuestUserData("CaptainComission1", "sNation", NationNameNominative(sti(pchar.GenQuest.CaptainComission.Nation)));
			CloseQuestHeader("CaptainComission1");			
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 15);			
			GiveItem2Character(pchar, pchar.GenQuest.CaptainComission.Item); 
			TakeNItems(pchar, "jewelry5", 100);
			PlaySound("interface\important_item.wav");
			DialogExit();
			AddDialogExitQuestFunction("CaptainComission_EndTavern");
		break;
		
		case "CaptainComission_7_1":
			dialog.text = "Oh, what a pity! I have lost too much time already. You've really put me down, captain!";
			link.l1 = "I understand, but the circumstances could not have been overcome. Here is your money.";
			link.l1.go = "CaptainComission_7_1End";
		break;
		
		case "CaptainComission_7_1End":
			AddQuestRecord("CaptainComission1", "8");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			CloseQuestHeader("CaptainComission1");
			rChar = characterFromId("CapComission_1");
			rChar.lifeDay = 0; 
			pchar.quest.CaptainComission1_30DaysIsLeft.over = "yes";
			addMoneyToCharacter(pchar, -150000);
			ChangeCharacterComplexReputation(pchar,"nobility", -4);
			LAi_CharacterDisableDialog(NPChar);
			DialogExit();
			AddDialogExitQuestFunction("CaptainComission_EndTavern");
		break;
		
		case "CaptainComission_7_2":
			dialog.text = "Could you please hurry? I fear that the pirates will change the terms of the deal once again.";
			link.l1 = "Don't worry, we'll manage.";
			link.l1.go = "exit";
			NextDiag.TempNode = "CaptainComission_7";
		break;
		
		case "CaptainComission_7_3":
			dialog.text = "I hope you realize that you are working against the clock?";
			link.l1 = "Once again - I am on it. Have patience.";
			link.l1.go = "exit";
			NextDiag.TempNode = "CaptainComission_7";
		break;
		
		case "CaptainComission_7_4":
			dialog.text = "God save us! No pressure, simply a help from the modest Puritan\nIt's your own fault. You killed captain " + pchar.GenQuest.CaptainComission.CapName + ", lost our gold and failed the ransom of a very valuable man. It's you pain in the butt now and your responsibility. Don't even think that you are forgiven... You will pay for everything.";
			link.l1 = "Screw you!";
			link.l1.go = "exit";
			NextDiag.TempNode = "CaptainComission_7";
		break;
		
		// диалоги с управляющим на плантации
		case "CaptainComission_10":
			dialog.text = "Hello, did you want anything?";
			link.l1 = "May I see the owner of this plantation?";
			link.l1.go = "CaptainComission_10_1";
		break;
		
		case "CaptainComission_10_1":
			dialog.text = "He is not here - looking for one runaway slave, Blade, or Blood, I don't remember... And I am the local steward " + npchar.name + " and I am authorized to settle all matters while the boss is on leave.";
			link.l1 = "Are you? That's good... And selling slaves is in your competence, too?";
			link.l1.go = "CaptainComission_10_2";
		break;
		
		case "CaptainComission_10_2":
			dialog.text = "Of course. How many you wanna buy?";
			link.l1 = "Just one.";
			link.l1.go = "CaptainComission_10_3";
		break;
		
		case "CaptainComission_10_3":
			dialog.text = "Ehh... Are you sure that you need only one slave?";
			link.l1 = "Of course, I am. His name is " + pchar.GenQuest.CaptainComission.SlaveName + ".";
			link.l1.go = "CaptainComission_10_4";
		break;
		
		case "CaptainComission_10_4":
			if(rand(1) == 0)
			{
				dialog.text = "But certainly you realize that the price of one slave will be higher compared to the price of one slave in a larger batch?";
				link.l1 = "Of course. Can you name the price?";
				link.l1.go = "CaptainComission_11";
			}
			else
			{
				if(rand(100) < makeint(sti(pchar.rank) + 0.75 * GetSummonSkillFromName(pchar, SKILL_FORTUNE)))
				{
					dialog.text = "Hmm... I hope you know whom you're interceding for?";
					link.l1 = "What do you mean?";
					link.l1.go = "CaptainComission_12";
				}
				else
				{
					dialog.text = "Oh, that loafer. I would not give a copper for him. Since the time he was brought here, he never did any actual work. I have no idea why the colonel would waste money on these state convicts. Now the black guys are a different story. They are great workers, it's in their blood. And trust me, they can do absolutely any job. Sugarcane harvesting or serving as a steward - they will do it in the best way possible...";
					link.l1 = "My friend, I could not care less about your black guys. I am only interested in that loafer you were talking about.";
					link.l1.go = "CaptainComission_13";
				}
			}
		break;
		
		case "CaptainComission_11":
			dialog.text = "Sure, sure. Let me see the pricing\nOh!!! 150000 pesos.";
			link.l1 = "Wow...";
			link.l1.go = "CaptainComission_11_1";
		break;
		
		case "CaptainComission_11_1":
			dialog.text = "The price should be in the price list. Here. You know, I don't quite get it. Other slaves are sold at reasonable prices, but that one is being sold for a fortune...";
			if(sti(pchar.money) >= 150000)
			{
				link.l1 = "I think I understand what's the deal here... Alright, here's the money, and I am taking him with me.";
				link.l1.go = "CaptainComission_14";
			}	
			link.l2 = "Hmm... But I am not ransoming a hostage - I want to buy an ordinary slave. Don't you think that one could buy a decent fully equipped ship for such sum?";
			link.l2.go = "CaptainComission_15";
		break;
		
		case "CaptainComission_12":
			dialog.text = "That's not an ordinary slave. Colonel Bishop has even ordered to guard him.";
			link.l1 = "So I cannot even buy him?";
			link.l1.go = "CaptainComission_12_1";
		break;
		
		case "CaptainComission_12_1":
			dialog.text = "Why, you certainly can. Colonel has set a price for him - 200000 pesos, according to the price list.";
			if(sti(pchar.money) >= 200000)
			{
				link.l1 = "Wow! Well, surely that colonel must be aware what kind of person that slave is...";
				link.l1.go = "CaptainComission_16";
			}	
			link.l2 = "Hmm... But I am not ransoming a hostage - I want to buy an ordinary slave. Don't you think that one could buy a decent fully equipped ship for such sum?";
			link.l2.go = "CaptainComission_15";	
		break;
		
		case "CaptainComission_13":
			dialog.text = "Ah, yes. Pardon me. Let me see the pricing Bishop has left.\nAha, here it is. Well. Oh!.. 150 000 pesos!..";
			if(sti(pchar.money) >= 15000)
			{
				link.l1 = "Apparently it's some kind of mistake. You certainly realize that no slave can possibly cost that much. I suppose there is one extra zero, and the sum should be 15000 pesos. And it's still too much, considering that he's an idler.";
				link.l1.go = "CaptainComission_17";
			}	
			link.l2 = "Hmm... But I am not ransoming a hostage - I want to buy an ordinary slave. Don't you think that one could buy a decent fully equipped ship for such sum?";
			link.l2.go = "CaptainComission_15";
		break;
		
		case "CaptainComission_14":
			addMoneyToCharacter(pchar, -150000);
			pchar.GenQuest.CaptainComission.SlaveMoney = 150000;
			dialog.text = "Great! That's great! They will bring him here right now... Ehh... Tea, perhaps?";
			link.l1 = "No, thanks... Say hi to colonel Bishop...";
			link.l1.go = "CaptainComission_14_1";
		break;
		
		case "CaptainComission_14_1":
			dialog.text = "And from whom, might I know?";
			link.l1 = "Mmm... Nevermind, don't bother. Goodbye.";
			link.l1.go = "CaptainComission_14_1End";
		break;
		
		case "CaptainComission_14_1End":
			NextDiag.TempNode = "CaptainComission_18";
			NextDiag.CurrentNode = NextDiag.TempNode;
			pchar.GenQuest.CaptainComission.GetSlave = "GetSlave";
			DialogExit();
			AddDialogExitQuestFunction("CaptainComission_GetSlave");
		break;
		
		case "CaptainComission_15":
			dialog.text = "I am sorry, but there is nothing I can do. Here's the price list.";
			link.l1 = "Oh stop it already - price list, price list... You all cannot decide a simplest thing without Bishop. Tell him... Nevermind, don't tell him anything.";
			link.l1.go = "CaptainComission_15_1";
		break;
		
		case "CaptainComission_15_1":
			dialog.text = "So you are not going to buy that slave.";
			link.l1 = "No. Goodbye.";
			link.l1.go = "CaptainComission_15_1End";
		break;
		
		case "CaptainComission_15_1End":
			OfficersReaction("bad");
			AddQuestRecord("CaptainComission1", "30");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("",""));
			NextDiag.TempNode = "CaptainComission_19";
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			AddDialogExitQuestFunction("CaptainComission_GetSlave");
		break;
		
		case "CaptainComission_16":
			dialog.text = "I don't know anything about it. I only have specific instructions regarding selling that particular slave.";
			link.l1 = "Nonsense... Alright, whatever. Here's the money. Bring the slave.";
			link.l1.go = "CaptainComission_16_1"; 
		break;
		
		case "CaptainComission_16_1":
			addMoneyToCharacter(pchar, -200000);
			pchar.GenQuest.CaptainComission.SlaveMoney = 200000;
			dialog.text = "Of course. He will be delivered here in an instant.";
			link.l1 = "Farewell.";
			link.l1.go = "CaptainComission_16_1End";
		break;
		
		case "CaptainComission_16_1End":
			NextDiag.TempNode = "CaptainComission_18";
			NextDiag.CurrentNode = NextDiag.TempNode;
			pchar.GenQuest.CaptainComission.GetSlave = "GetSlave";
			DialogExit();
			AddDialogExitQuestFunction("CaptainComission_GetSlave");
		break;
		
		case "CaptainComission_17":
			dialog.text = "Hmm... Yeah, perhaps you're right. Should be a mistake.";
			link.l1 = "Well, if we have agreed on the price, can I take him with me now?";
			link.l1.go = "CaptainComission_17_1";
		break;
		
		case "CaptainComission_17_1":
			dialog.text = "Yes, of course. He will be brought here in a moment.";
			link.l1 = "Very good. Here is your money... Goodbye.";
			link.l1.go = "CaptainComission_17_1End";
		break;
		
		case "CaptainComission_17_1End":
			addMoneyToCharacter(pchar, -15000);
			pchar.GenQuest.CaptainComission.SlaveMoney = 15000;
			NextDiag.TempNode = "CaptainComission_18";
			NextDiag.CurrentNode = NextDiag.TempNode;
			pchar.GenQuest.CaptainComission.GetSlave = "GetSlave";
			DialogExit();
			AddDialogExitQuestFunction("CaptainComission_GetSlave");
		break;
		
		case "CaptainComission_18":
			dialog.text = "Want some tea, captain?";
			link.l1 = "No, thanks.";
			link.l1.go = "exit";
		break;
		
		case "CaptainComission_19":
			dialog.text = "Have you decided to buy him.";
			link.l1 = "No. Goodbye.";
			link.l1.go = "exit";
		break;
		
		// диалоги с рабом
		case "CaptainComission_20":
			if(pchar.GenQuest.CaptainComission.AfterTavernSpeak == "goodSpeak")
			{
				dialog.text = "Hello, captain. How can I help you? I can't believe this torment is finally over.";
				link.l1 = "You should thank not me, but rather your relative " + pchar.GenQuest.CaptainComission.Name + " from " + XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Gen") + ". He has gathered the ransom.";
				link.l1.go = "CaptainComission_201";
			}
			else
			{
				dialog.text = "Hello, captain. I was told that you paid the ransom for me. I must thank you for that, although I realize that you were just a courier.";
				link.l1 = "You don't look so happy with your newly regained freedom. Are you worried with something?";
				link.l1.go = "CaptainComission_202";
			}
		break;
		
		case "CaptainComission_201":
			dialog.text = "Please, if it doesn't interfere with your plans too much - take me to him. I'd like to thank him personally.";
			link.l1 = "Of course, I will. Come - I'll bring you to the ship.";
			link.l1.go = "CaptainComission_201_1";
		break;
		
		case "CaptainComission_201_1":
			AddQuestRecord("CaptainComission1", "11");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("","а"));
			AddQuestUserData("CaptainComission1", "sName", pchar.GenQuest.CaptainComission.SlaveName);
			AddQuestUserData("CaptainComission1", "sSum", pchar.GenQuest.CaptainComission.SlaveMoney);
			AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Gen"));
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, false);
			LAi_SetActorType(NPChar);
			LAi_ActorGoToLocation(NPChar, "reload", "reload2_back", "none", "", "", "OpenTheDoors", -1.0);
			DialogExit();
		break;
		
		case "CaptainComission_202":
			dialog.text = "To be sure of my freedom, I need to know the names of those who have paid for it.";
			link.l1 = "Well, I was the one who paid, though it wasn't of my own will.";
			link.l1.go = "CaptainComission_202_1";
		break;
		
		case "CaptainComission_202_1":
			dialog.text = "So, my suspicions were confirmed. You were forced to do so by " + NationNamePeople(sti(pchar.GenQuest.CaptainComission.Nation)) + "?";
			link.l1 = "Yes, it's " + pchar.GenQuest.CaptainComission.Name + " from " + XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Gen") + ".";
			link.l1.go = "CaptainComission_202_2";
		break;
		
		case "CaptainComission_202_2":
			iNation = FindEnemyNation2Nation(sti(pchar.GenQuest.CaptainComission.Nation));	
			if(iNation == -1) iNation(rand(3));
			pchar.GenQuest.CaptainComission.SlaveCity = FindAlliedColonyForNation(iNation, true);
			pchar.GenQuest.CaptainComission.EnemyNation = iNation;
			dialog.text = "I see. I have no idea what they had promised you, but here is the deal: take me to the tavern of " + XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.SlaveCity + "Gen") + ", I will be safe there for real. In return, I will share some information I possess with you.";
			link.l1 = "That's fine - all the more so that they haven't promised anything so far. Come with me, I'll bring you to my ship.";
			link.l1.go = "CaptainComission_202_3";
			link.l2 = "I am not risking to summon troubles upon myself because of some questionable information.";
			link.l2.go = "CaptainComission_203";
		break;
		
		case "CaptainComission_202_3":
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, false);
			rChar = characterFromId("CapComission_1");
			ChangeCharacterAddress(rChar, "none", ""); 
			rChar.lifeDay = 0; 
			AddQuestRecord("CaptainComission1", "12");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission1", "sSex1", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission1", "sName", pchar.GenQuest.CaptainComission.SlaveName);
			AddQuestUserData("CaptainComission1", "sSum", pchar.GenQuest.CaptainComission.SlaveMoney);
			AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.SlaveCity + "Gen"));
			pchar.quest.CapComission_DeliveSlave.win_condition.l1 = "location";
			pchar.quest.CapComission_DeliveSlave.win_condition.l1.location = pchar.GenQuest.CaptainComission.SlaveCity + "_tavern";
			pchar.quest.CapComission_DeliveSlave.function = "CaptainComission_DeliveSlave";
			DialogExit();
		break;
		
		case "CaptainComission_203":
			dialog.text = "Unfortunately, I cannot reveal it to you as of now. This can mean trouble for both of us.";
			link.l1 = "All the more so... Follow me and no stupid things, please. Consider yourself under arrest once again.";
			link.l1.go = "CaptainComission_203_1";
		break;
		
		case "CaptainComission_203_1":
			AddQuestRecord("CaptainComission1", "13");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission1", "sName", pchar.GenQuest.CaptainComission.SlaveName);
			AddQuestUserData("CaptainComission1", "sSum", pchar.GenQuest.CaptainComission.SlaveMoney);
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, false);
			DialogExit();
		break;
		
		case "CaptainComission_50":
			dialog.text = "What?! The pirates have altered the deal again? But I cannot take anymore money out of business! That way I will soon be bankrupt!";
			link.l1 = "No... Your relative has perished on the plantations of Barbados during an unsuccessful escape attempt.";
			link.l1.go = "CaptainComission_51";
		break;
		
		case "CaptainComission_51":
			ChangeCharacterComplexReputation(pchar,"nobility", -3);
			dialog.text = "Oh... I am totally crushed... How did that happen?";
			link.l1 = "The pirates hadn't waited for the ransom and sold him into slavery. I went for him to Barbados, but failed to save him...";
			link.l1.go = "CaptainComission_52";
		break;
		
		case "CaptainComission_52":
			dialog.text = "Jesus! What is going on?\nFine, captain, thank you for your participation. And please, return the money I have given you.";
			link.l1 = "My expenses exceeded all expectations, so I will keep your money... Farewell.";
			link.l1.go = "CaptainComission_53";
			if(sti(pchar.money) >= 150000)
			{
				link.l2 = "Sure, take it... Sorry that I have failed to help you... Farewell.";
				link.l2.go = "CaptainComission_54";
			}
		break;
		
		case "CaptainComission_53":
			ChangeCharacterComplexReputation(pchar,"nobility", -5);
			OfficersReaction("bad");			
			AddQuestRecord("CaptainComission1", "22");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			AddQuestUserData("CaptainComission1", "sName", pchar.GenQuest.CaptainComission.SlaveName);
			CloseQuestHeader("CaptainComission1");
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeDay = 0; 			
			DeleteAttribute(pchar,"GenQuest.CaptainComission");
			DialogExit();
		break;
		
		case "CaptainComission_54":
			OfficersReaction("good");
			addMoneyToCharacter(pchar, -150000);
			AddQuestRecord("CaptainComission1", "23");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			AddQuestUserData("CaptainComission1", "sName", pchar.GenQuest.CaptainComission.SlaveName);
			CloseQuestHeader("CaptainComission1");
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeDay = 0; 			
			DeleteAttribute(pchar,"GenQuest.CaptainComission");
			DialogExit();
		break;
		
		case "CaptainComission_60":
			dialog.text = "That's too bad. You have no idea how bad it really is...";
			link.l1 = "There's nothing I can do about it. I am even glad that all of that happened this way. Farewell.";
			link.l1.go = "CaptainComission_61";
		break;
		
		case "CaptainComission_61":
			ChangeCharacterComplexReputation(pchar,"nobility", -2);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), -15);
			AddQuestRecord("CaptainComission1", "32");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission1", "sName", pchar.GenQuest.CaptainComission.Name);
			CloseQuestHeader("CaptainComission1");
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeDay = 0; 			
			DeleteAttribute(pchar,"GenQuest.CaptainComission");			
			DialogExit();
		break;
		
		// диалог с рабом в колодках
		case "CaptainComission_70":
			dialog.text = "Drink... captain, bring some water...";
			link.l1 = "Hey, buddy, aren't you " + pchar.GenQuest.CaptainComission.SlaveName + "?";
			link.l1.go = "CaptainComission_71";
		break;
		
		case "CaptainComission_71":
			dialog.text = "Yeah... That's me...";
			link.l1 = "Listen - if you don't want to perish here, like a flatfish on a shoal - gather yourself and listen to me. Do you know where the Lighthouse of Barbados is located?";
			link.l1.go = "CaptainComission_72";
		break;
		
		case "CaptainComission_72":
			dialog.text = "I do...";
			link.l1 = "Once you have the chance, run there. I'll try to arrange such chance for you.";
			link.l1.go = "CaptainComission_73";			
		break;
		
		case "CaptainComission_73":	
			LAi_SetPlayerType(pchar); 
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			LAi_LockFightMode(pchar, false);			
			sTemp = GetNationNameByType(GetCityNation("Bridgetown"))  + "_citizens";
			for(i = 0; i < 3; i++)
			{
				if (GetCharacterIndex("SlaveGuard_" + i) == -1) continue;
				sld = CharacterFromID("SlaveGuard_" + i);			
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "SlaveGuards");
			}
						
			LAi_group_SetRelation("SlaveGuards", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_SetRelation("SlaveGuards", sTemp, LAI_GROUP_NEITRAL);			
			LAi_group_SetAlarmReaction("SlaveGuards", sTemp, LAI_GROUP_NEITRAL, LAI_GROUP_FRIEND);
			LAi_group_FightGroups("SlaveGuards", LAI_GROUP_PLAYER, true);
			LAi_group_SetAlarm("SlaveGuards", LAI_GROUP_PLAYER, 0);
			LAi_group_SetCheck("SlaveGuards", "OpenTheDoors");
			LAi_group_SetCheckFunction("SlaveGuards", "CaptainComission_GuardsAfter");
			
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn"); 
		break;
		
		// диалог охранников раба
		case "CaptainComission_80":
			dialog.text = RandPhraseSimple("Go ahead and ask, captain, but be quick - I am on duty.","Speak, but be quick about it and don't bother me with petty things.");
			link.l1 = RandPhraseSimple("Can you tell me how can I find a certain slave? His name is " + pchar.GenQuest.CaptainComission.SlaveName + ".","Somewhere on this plantation there should be a slave by the name of " + pchar.GenQuest.CaptainComission.SlaveName + ". Can you tell me how could talk to him?");
			link.l1.go = "CaptainComission_81";			
		break;
		
		case "CaptainComission_81":
			dialog.text = "Today he is punished and under guard.";
			link.l1 = "Thanks.";
			link.l1.go = "exit";
			NextDiag.TempNode = "CaptainComission_80";
			NextDiag.CurrentNode = NextDiag.TempNode;
		break;
		
		case "CaptainComission_85":
			dialog.text = "Thank you... captain, you've saved my life...";
			link.l1 = "Run to the lighthouse of Barbados and wait for me there.";
			link.l1.go = "CaptainComission_86";
		break;
		
		case "CaptainComission_86":
			LAi_SetActorType(NPChar);
			LAi_ActorRunToLocation(NPChar, "reload", "reload2_back", "none", "", "", "OpenTheDoors", -1.0);
			sTemp = GetNationNameByType(GetCityNation("Bridgetown"))  + "_citizens";
			LAi_group_AttackGroup(sTemp, LAI_GROUP_PLAYER);
			DialogExit();
		break;
		
		case "CaptainComission_90":
			if(pchar.GenQuest.CaptainComission.AfterTavernSpeak == "goodSpeak")
			{
				dialog.text = "Captain, how can I thank you? I still can't believe that this torment is finally over.";
				link.l1 = "I was already thanked by your relative " + pchar.GenQuest.CaptainComission.Name + " from " + XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Gen") + ". I act on his instructions.";
				link.l1.go = "CaptainComission_91";
			}
			if(pchar.GenQuest.CaptainComission.AfterTavernSpeak == "badSpeak")
			{
				dialog.text = "Thank you, captain. I don't know on whose behalf you are acting, but even a bad freedom is better than a good slavery.";
				link.l1 = "What do you mean?";
				link.l1.go = "CaptainComission_92";
			}
		break;
		
		case "CaptainComission_91":
			dialog.text = "If it doesn't hurt your plans too much, please take me to him. I am just too tired of all that.";
			link.l1 = "Of course, I'll do - if we manage to get out of here alive.";
			link.l1.go = "CaptainComission_91End";
		break;
		
		case "CaptainComission_91End":
			pchar.GenQuest.CaptainComission = "toOurTavern";
			rChar = CharacterFromID("CapComission_Slave");
			LAi_SetWarriorType(rChar);
			LAi_group_MoveCharacter(rChar, LAI_GROUP_PLAYER);
			DialogExit();
			AddDialogExitQuestFunction("CaptainComission_GeneratePatrol");
		break;
		
		case "CaptainComission_92":
			dialog.text = "And may I know the names of people who paid for my freedom?";
			link.l1 = "Well, actually, I was not paid. They had left me no choice.";
			link.l1.go = "CaptainComission_93";
		break;
		
		case "CaptainComission_93":
			dialog.text = "So, my suspicions were confirmed. You were forced to do so by " + NationNamePeople(sti(pchar.GenQuest.CaptainComission.Nation)) + "?";
			link.l1 = "Yes, it's " + pchar.GenQuest.CaptainComission.Name + " from " + XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Gen") + ".";
			link.l1.go = "CaptainComission_94";
		break;		
		
		case "CaptainComission_94":
			iNation = FindEnemyNation2Nation(sti(pchar.GenQuest.CaptainComission.Nation));	
			if(iNation == -1) iNation(rand(3));
			pchar.GenQuest.CaptainComission.SlaveCity = FindAlliedColonyForNation(iNation, true);
			pchar.GenQuest.CaptainComission.EnemyNation = iNation;
			dialog.text = "I have no idea what they have promised you, but here is the deal: take me to the tavern of " + XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.SlaveCity + "Gen") + ", I will be safe there for real. In return, I will share some information I possess with you.";
			link.l1 = "That's fine - all the more so that they haven't promised anything so far. Come with me, I'll see you to my ship.";
			link.l1.go = "CaptainComission_95";
			link.l2 = "I am not risking to summon troubles upon myself because of some questionable information.";
			link.l2.go = "CaptainComission_96";
		break;	
		
		case "CaptainComission_95":
			pchar.GenQuest.CaptainComission = "toEnemyTavern";
			DialogExit();
			AddDialogExitQuestFunction("CaptainComission_GeneratePatrol");
		break;
		
		case "CaptainComission_96":
			dialog.text = "Unfortunately, I cannot reveal it to you as of now. This can mean trouble for both of us.";
			link.l1 = "All the more so... Follow me and no stupid things, please. Consider yourself under arrest once again.";
			link.l1.go = "CaptainComission_97";
		break;
		
		case "CaptainComission_97":		
			pchar.GenQuest.CaptainComission = "toTavern";
			DialogExit();
			AddDialogExitQuestFunction("CaptainComission_GeneratePatrol");
		break;
		
		case "CaptainComission_100":		
			dialog.text = "Thank you, captain. Now I am finally safe. I am not offering you money, for I am sure that knowledge and its skillful application are worth much more than perishable metal.";
			link.l1 = "I am waiting for the information";
			link.l1.go = "CaptainComission_101";
		break;
		
		case "CaptainComission_101":
			GetSlaveSpeciality();
			dialog.text = "The thing is that I am a scientist, specialist of " + pchar.GenQuest.CaptainComission.SlaveSpeciality + " and " + NationNamePeople(sti(pchar.GenQuest.CaptainComission.EnemyNation)) + " had been offering me cooperation for quite some time," + 
				"but I am a military engineer and I keep my oaths of allegiance. They tried to steal me, though the real problems had started when pirates learnt my true identity and importance\n"+
				"In the end, they had managed to capture me, yet the gold was the only thing they wanted, they never needed my knowledge. My friends and enemies failed to ransom me in time and I was sold to plantations. You know the rest.";
			link.l1 = "Yeah, woe to wit, as they say, indeed.";	
			link.l1.go = "CaptainComission_102";
		break;
		
		case "CaptainComission_102":
			switch(sti(pchar.GenQuest.CaptainComission.Speciality))
			{
				case 0:
					sTemp = "protecting your ship and its crew during combat.";
				break;	
				case 1:
					sTemp = "quickly reloading your cannons and firing aimed shot under conditions of dusting. ";
				break;					
				case 2:
					sTemp = "quickly managing the sails and maneuvering in combat.";
				break;					
			}
			dialog.text = "Well, you could say that. So, if you pay attention to what I can tell you, you will become much more proficient in the skill of " + sTemp;
			link.l1 = "Thank you, that information is very useful, indeed.";
			link.l1.go = "CaptainComission_103";
		break;
		
		case "CaptainComission_103":
			dialog.text = "Well, farewell and thanks for everything.";
			link.l1 = "Thanks to you as well. Farewell, and try not to get caught next time.";
			link.l1.go = "CaptainComission_104";
		break;
		
		case "CaptainComission_104":
			AddQuestRecord("CaptainComission1", "21");
			CloseQuestHeader("CaptainComission1");
			// а теперь раздача слонов !!!!!!!
			switch(sti(pchar.GenQuest.CaptainComission.Speciality))
			{
				case 0:
					if(drand(1) == 0) 
					{
						AddCharacterSkill(pchar, SKILL_DEFENCE, 10);
					}
					else
					{
						AddCharacterSkill(pchar, SKILL_REPAIR, 10);
					}					
				break;
				case 1:
					if(drand(1) == 0) 
					{
						AddCharacterSkill(pchar, SKILL_CANNONS, 10);
					}
					else
					{
						AddCharacterSkill(pchar, SKILL_ACCURACY, 10);
					}	
				break;
				case 2:
					AddCharacterSkill(pchar, SKILL_SAILING, 10);
				break;
			}
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "","OpenTheDoors", -1.0);
			NPChar.lifeDay = 0;
			DeleteAttribute(pchar,"GenQuest.CaptainComission");
			DialogExit();
		break;
		// Генератор "Captain's request"
		
		// Генератор "Operation 'Galleon'"
		case "CaptainComission_300":
			ReOpenQuestHeader("CaptainComission2");
			AddQuestRecord("CaptainComission2", "1");
			AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.CapName);
			AddQuestUserData("CaptainComission2", "sShipType", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name") + "Acc"))); 
			AddQuestUserData("CaptainComission2", "sShipName", pchar.GenQuest.CaptainComission.ShipTypeName);
			AddQuestUserData("CaptainComission2", "sCapName",  pchar.GenQuest.CaptainComission.Name);
			AddQuestUserData("CaptainComission2", "sCity1", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Dat"));
			AddQuestUserData("CaptainComission2", "sShipTypeNom", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name"))));
			AddQuestUserData("CaptainComission2", "sCity2", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City1 + "Gen"));
			AddQuestUserData("CaptainComission2", "sCity11", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Gen"));			
			SetFunctionLocationCondition("CaptainComission_GenerateQuestContinuation", GetArealByCityName(pchar.GenQuest.CaptainComission.City), false);
			SetFunctionTimerCondition("CaptainComission_TimeIsOver", 0, 0, 15, false);
			SaveCurrentQuestDateParam("GenQuest.CaptainComission");
			LAi_KillCharacter(NPChar);
			LAi_SetPlayerType(pchar); 
			pchar.GenQuest.CaptainComission = "Begin_1";
			LAi_EnableReload();
			Log_SetActiveAction("Reload");
			DialogExit();			
		break;
		
		// диалог с кэпом на палубе
		case "CaptainComission_301":
			pchar.quest.CaptainComission_TimeIsOver.over = "yes";
			dialog.text = RandPhraseSimple("Ahoy, I am captain " + GetFullName(NPChar) + ", what brought you to the deck of my ship '" + pchar.GenQuest.CaptainComission.ShipTypeName + "'?","Ahoy, I am always happy to have guests on my ship. Captain " + GetFullName(NPChar) + " at your service.");
			link.l1 = "Hello, I am captain " + GetFullName(pchar) +", acting on behalf of some captain " + pchar.GenQuest.CaptainComission.CapName +". He asked me to tell you that you would be arrested in " + XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Dat") + ". The authorities know about " + GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipTypeVictim),"Name") + "Acc")) + ".";
			link.l1.go = "CaptainComission_302";
		break;
		
		case "CaptainComission_302":
			dialog.text = "Ah, what a pity! Let me think\nAnd where is captain " + pchar.GenQuest.CaptainComission.CapName + "?";
			link.l1 = "He died.";
			link.l1.go = "CaptainComission_303";
		break;
		
		case "CaptainComission_303":
			dialog.text = "Damn it! Things just getting worse... Listen, " + GetFullName(pchar) + ", I am not ready to face such turn of events. Captain " + pchar.GenQuest.CaptainComission.CapName + " and I agreed to meet at " + XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Dat") + ". The plan was to load some cargo in his vessel. Now the captain is dead, I can't show up in the settlement\nIt seems that I have nothing left but to ask you for a favor.";
			link.l1 = "My consent will depend on the sort of help that you need.";
			link.l1.go = "CaptainComission_304";
		break;
		
		case "CaptainComission_304":
			pchar.GenQuest.CaptainComission.ShoreLocation = SelectQuestShoreLocationFromSea(GetArealByCityName(pchar.GenQuest.CaptainComission.City));
			dialog.text = "Help me with men and longboats. I need the cargo to be taken away from " + XI_ConvertString(pchar.GenQuest.CaptainComission.ShoreLocation + "Gen") + ". You can keep the late captain's cut of the cargo.";
			link.l1 = "Hmm... Apparently, you've bitten off more than you could chew. I need more information.";
			link.l1.go = "CaptainComission_305";
			link.l2 = "Unfortunately, I am not in the position to waste time on that.";
			link.l2.go = "CaptainComission_306";
		break;
		
		case "CaptainComission_305":
			sTemp = GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipTypeVictim),"Name") + "Gen"));
			dialog.text = "Fine, I will give you details\n" +
				"During one of regular patrols I met a vessel under the flag of " + NationNameGenitive(sti(pchar.GenQuest.CaptainComission.Nation)) + ". They had ignored my orders to surrender." +
				"When after a short chase we had caught up with " + sTemp + " '" + pchar.GenQuest.CaptainComission.VictimShipName + "' after a short chase and they raised the black flag. The fort was quite far away, so we had to fight on our own. They destroyed our jib-boom, that's why we couldn't avoid boarding.\n" + 
				"It was close, but we managed to kill them all  thanks to Holy Mary and a musketeer unit. Imagine our happiness when we found out that " + sTemp + " was filled with. " +
				"We have decided that this is a decent reward for our wounds and deaths of our comrades\nIt was dark already, we took " + sTemp +" to the closest bay and hide the cargo ashore. Then we had exploded " + sTemp +" and I reported about the sunken pirate vessel. Of course, I didn't mention the cargo.";
			link.l1 = "Apparently, someone has still blabbed it out...";	
			link.l1.go = "CaptainComission_307";
		break;
		
		case "CaptainComission_306":
			dialog.text = "A pity, captain... It's a pity that you are not willing to help me.";
			link.l1 = "That's not a matter of my will, my dear. You must understand. Farewell.";
			link.l1.go = "CaptainComission_306End";			
		break;
		
		case "CaptainComission_306End":
			AddQuestRecord("CaptainComission2", "3");
			AddQuestUserData("CaptainComission2", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.CapName);
			CloseQuestHeader("CaptainComission2");
			GetCharacterPos(pchar, &locx, &locy, &locz);
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", LAi_FindNearestLocator("reload", locx, locy, locz), "none", "", "", "", 1.5);			
			pchar.GenQuest.CaptainComission = "close";
			SetFunctionExitFromLocationCondition("CaptainComission_ExitFromLoc", pchar.location, false);
			DialogExit();
		break;
		
		case "CaptainComission_307":
			dialog.text = "I don't think that it was my men. Most likely, the owner of the cargo is eager to ease the pain of the loss\nSo? Can I count on your assistance?";
			link.l1 = "Yes, sounds good.";
			link.l1.go = "CaptainComission_308";
			link.l2 = "No, my friend. First: I don't know, how much cargo will go to my hold; second - there is no guarantee that the authorities hadn't found it yet and taken away, while leaving an ambush party at the cache.";
			link.l2.go = "CaptainComission_309";
		break;
		
		case "CaptainComission_308":
			dialog.text = "Let's meet at " + XI_ConvertString(pchar.GenQuest.CaptainComission.ShoreLocation + "Dat") + " then, right after the midnight. My current position requires to be secretive. We must avoid patrols.";
			link.l1 = "Alright, wait for me there.";
			link.l1.go = "CaptainComission_313";
//			bQuestDisableMapEnter = true;
		break;
		
		case "CaptainComission_309":
			dialog.text = "Pity, but you don't leave me a choice. One ship is not enough to take all of the cargo. I risked for it with my career and my own life. Surely, your crew will gladly help me in return for a decent cut.";
			link.l1 = "And what are you suggesting?";
			link.l1.go = "CaptainComission_310";
		break;
		
		case "CaptainComission_310":
			dialog.text = "I will take your vessel and leave you at " + XI_ConvertString(pchar.GenQuest.CaptainComission.ShoreLocation + "Dat") + ".";
			link.l1 = "Your success seems unlikely to me. I will return to mu ship even if I have to cut down your entire crew.";
			link.l1.go = "CaptainComission_311";
			link.l2 = "It seems, that I have no choice. Well, I will submit to the violence...";
			link.l2.go = "CaptainComission_312";
		break;
		
		case "CaptainComission_311":
			pchar.GenQuest.CaptainComission.FightAfterDeck = true; //после резни на палубе - драка в море		
			GetCharacterPos(pchar, &locx, &locy, &locz);
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", LAi_FindNearestLocator("reload", locx, locy, locz), "none", "", "", "CaptainComission_FightInDeck", 3.5);
			DialogExit();
		break;
		
		case "CaptainComission_312":
			DialogExit();
			AddDialogExitQuestFunction("CaptainComission_toShore");
		break;
		
		case "CaptainComission_313":			
			NextDiag.TempNode = "CaptainComission_314";
			NextDiag.CurrentNode = NextDiag.TempNode;
			AddQuestRecord("CaptainComission2", "7");
			AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);
			AddQuestUserData("CaptainComission2", "sGoods", GetStrSmallRegister(XI_ConvertString(Goods[sti(pchar.GenQuest.CaptainComission.Goods)].Name + "Gen")));
			AddQuestUserData("CaptainComission2", "sShoreName", XI_ConvertString(pchar.GenQuest.CaptainComission.ShoreLocation + "Gen"));
			AddQuestUserData("CaptainComission2", "sShoreNameDat", XI_ConvertString(pchar.GenQuest.CaptainComission.ShoreLocation + "Dat"));
			SetFunctionTimerCondition("CaptainComission_SailToShore", 0, 0, 1, false);
			DialogExit();			
		break;
		
		case "CaptainComission_314":
			NextDiag.TempNode = "CaptainComission_314";
			dialog.text = "Captain, we must hurry. I fear that a patrol might spot us.";
			link.l1 = "Alright, let's hurry up.";
			link.l1.go = "exit";
		break;
		
		case "CaptainComission_315":
			dialog.text = "Captain, order to launch all lifeboats. We'll have to go several times, and I am afraid that a patrol might come to the cove. ";
			link.l1 = "Don't worry, everything should be fine. The boats are already coming to the shore.";
			link.l1.go = "CaptainComission_316";
		break;
		
		case "CaptainComission_316":
			dialog.text = "Oh, damn it. Now we've got company...";
			link.l1 = "Truly, if you mention some fool, he will show up right away...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("CaptainComission_GenerateShorePatrol");
		break;
		
		// диалог с патрулем на берегу
		case "CaptainComission_317":
			dialog.text = "Captain, we are looking for war criminal " + pchar.GenQuest.CaptainComission.Name + ", who has concealed a valuable cargo from the authorities. Your documents, please.";
			link.l1 = "What documents, officer? We have disembarked to replenish our supplies of fresh water.";
			link.l1.go = "CaptainComission_318";
		break;
		
		case "CaptainComission_318":
			dialog.snd = "Voice\COGU\COGU004"; 
			dialog.text = "And here he is, " + pchar.GenQuest.CaptainComission.Name + " himself . Surrender your weapons and follow me - both of you.";
			link.l1 = "That was a really bad timing, officer...";
			link.l1.go = "CaptainComission_319";
		break;
		
		case "CaptainComission_319":
			DialogExit();
			for (i = 1; i <= sti(pchar.GenQuest.CaptainComission.SoldierQty); i++)
			{
    			sTemp = "SoldierIDX" + i;
				sld = GetCharacter(sti(pchar.GenQuest.CaptainComission.(sTemp)));
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "CoastalGuards");
            }
			
			LAi_group_SetHearRadius("CoastalGuards", 100.0);			
			sld = characterFromId("CapComission_1");
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);		
			LAi_group_SetRelation("CoastalGuards", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("CoastalGuards", LAI_GROUP_PLAYER, true);
            LAi_SetFightMode(Pchar, true);
		break;
		
		case "CaptainComission_320":
			pchar.GenQuest.CaptainComission.GoodsQty = makeint((sti(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipTypeVictim),"Capacity")) - sti(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Capacity")) + rand(250)) / sti(Goods[sti(pchar.GenQuest.CaptainComission.Goods)].Weight));	
			pchar.GenQuest.CaptainComission.GoodsQtyNorm = sti(pchar.GenQuest.CaptainComission.GoodsQty);
			dialog.text = "We must hurry before reinforcements have arrived here. The loading is about to finish, and your share is " + pchar.GenQuest.CaptainComission.GoodsQty + " units of " + GetStrSmallRegister(XI_ConvertString(Goods[sti(pchar.GenQuest.CaptainComission.Goods)].Name + "Gen")) +".";
			link.l1 = "Excellent. Time to leave now. Nice doing business with you.";
			link.l1.go = "CaptainComission_321";
		break;
		
		case "CaptainComission_321":		
			iTmp = FindNonEnemyColonyForAdventure(sti(pchar.GenQuest.CaptainComission.Nation),pchar.GenQuest.CaptainComission.City, true);			
			sTemp = Colonies[iTmp].id;
			pchar.GenQuest.CaptainComission.ConvoyIsland = GetArealByCityName(sTemp);
			pchar.GenQuest.CaptainComission.ConvoyShore = SelectQuestShoreLocationFromSea(pchar.GenQuest.CaptainComission.ConvoyIsland);
			pchar.GenQuest.CaptainComission.ConvoyCity = sTemp;
			dialog.text = "And just one more request. The authorities are sure to chase us - could you please escort my ship to " + XI_ConvertString(pchar.GenQuest.CaptainComission.ConvoyShore + "Gen") + ", which is on " + XI_ConvertString(GetIslandByCityName(sTemp) + "Dat") + "?";
			link.l1 = "No, my friend, from now on every man for himself. Farewell...";
			link.l1.go = "CaptainComission_322";
			if (GetCompanionQuantity(pchar) < COMPANION_MAX)
			{
				link.l2 = "Of course, I could do that for a good reward.";
				link.l2.go = "CaptainComission_323";
			}				
		break;
		
		case "CaptainComission_322":
			Group_DeleteGroup("Sea_CapComission_1"); 
			sld = characterFromId("CapComission_1");
			GetCharacterPos(pchar, &locx, &locy, &locz);
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", LAi_FindNearestFreeLocator("reload", locx, locy, locz), "none", "", "", "OpenTheDoors", 5.0);
			sld.lifeDay = 0; 	
			CaptainComission_GenerateCoastalPatrol();
			iGoods = GetSquadronFreeSpace(pchar, sti(pchar.GenQuest.CaptainComission.Goods)); 
			if(iGoods < sti(pchar.GenQuest.CaptainComission.GoodsQty)) pchar.GenQuest.CaptainComission.GoodsQty = iGoods;
			SetCharacterGoods(pchar, sti(pchar.GenQuest.CaptainComission.Goods), GetCargoGoods(pchar, sti(pchar.GenQuest.CaptainComission.Goods)) + sti(pchar.GenQuest.CaptainComission.GoodsQty));// перегруз
			AddQuestRecord("CaptainComission2", "10");
			AddQuestUserData("CaptainComission2", "sGoodsQuantity", pchar.GenQuest.CaptainComission.GoodsQty);
			AddQuestUserData("CaptainComission2", "sGoods", GetStrSmallRegister(XI_ConvertString(Goods[sti(pchar.GenQuest.CaptainComission.Goods)].Name + "Gen")));
			CloseQuestHeader("CaptainComission2");	
			DeleteAttribute(pchar, "GenQuest.CaptainComission");		
			DialogExit();
		break;
		
		case "CaptainComission_323":
			sld = characterFromId("CapComission_1");
			Fantom_SetCharacterGoods(sld, sti(pchar.GenQuest.CaptainComission.Goods), GetCargoFreeSpace(sld), 1);
			pchar.GenQuest.CaptainComission.ConvoyMoney = makeint((sti(pchar.rank)*100 + sti(NPChar.rank)*170 + cRand(30)*20) * 2.5);
			pchar.GenQuest.CaptainComission.iDay  = 15 + cRand(10);
			iGoods = GetSquadronFreeSpace(pchar, sti(pchar.GenQuest.CaptainComission.Goods)); 
			if(iGoods < sti(pchar.GenQuest.CaptainComission.GoodsQty)) pchar.GenQuest.CaptainComission.GoodsQty = iGoods;
			SetCharacterGoods(pchar, sti(pchar.GenQuest.CaptainComission.Goods), GetCargoGoods(pchar, sti(pchar.GenQuest.CaptainComission.Goods)) + sti(pchar.GenQuest.CaptainComission.GoodsQty));// перегруз
			dialog.text = "Of course. For the escort I am willing to pay  " + pchar.GenQuest.CaptainComission.ConvoyMoney + " pesos. But there's one more condition - it should not take more than " + pchar.GenQuest.CaptainComission.iDay + " days. It's important.";	
			link.l1 = "Deal. Let's depart immediately.";
			link.l1.go = "CaptainComission_324";
			NextDiag.TempNode = "CaptainComission_325";
			NextDiag.CurrentNode = NextDiag.TempNode;
		break;
		
		case "CaptainComission_324":
			pchar.GenQuest.CannotWait = 1; // лочим интерфейс отдыха 
			sld = characterFromId("CapComission_1");
			sTemp = LAi_FindNearestFreeLocator2Pchar("reload");
			LAi_SetActorType(sld);
			LAi_ActorSetStayMode(sld);
			CharacterIntoCompanionAndGoOut(pchar, sld, "reload", sTemp, 5, false);
			SetShipRemovable(sld, false);
			SetCharacterRemovable(sld, false);
			Group_ChangeCharacter(PLAYER_GROUP, "CapComission_1");
			AddQuestRecord("CaptainComission2", "11");
			AddQuestUserData("CaptainComission2", "sSex", GetSexPhrase("","а"));
			AddQuestUserData("CaptainComission2", "sGoodsQuantity", pchar.GenQuest.CaptainComission.GoodsQty);
			AddQuestUserData("CaptainComission2", "sGoods", GetStrSmallRegister(XI_ConvertString(Goods[sti(pchar.GenQuest.CaptainComission.Goods)].Name + "Gen")));		
			AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);
			AddQuestUserData("CaptainComission2", "sShoreName", XI_ConvertString(pchar.GenQuest.CaptainComission.ConvoyShore + "Gen"));
			AddQuestUserData("CaptainComission2", "sShoreType", XI_ConvertString(GetIslandByCityName(pchar.GenQuest.CaptainComission.ConvoyCity) + "Dat"));
			AddQuestUserData("CaptainComission2", "sSum", pchar.GenQuest.CaptainComission.ConvoyMoney);
			CaptainComission_GenerateCoastalPatrol();
			pchar.quest.CaptainComission_MapEnter.win_condition.l1 = "MapEnter";
			pchar.quest.CaptainComission_MapEnter.function = "CaptainComission_MapEnter"; 
			pchar.quest.CaptainComission_CapShip_Sink.win_condition.l1 = "Character_sink";
			pchar.quest.CaptainComission_CapShip_Sink.win_condition.l1.character = "CapComission_1";
			pchar.quest.CaptainComission_CapShip_Sink.function = "CaptainComission_CapShip_Sink";
			DialogExit();
		break;
		
		case "CaptainComission_325":
			NextDiag.TempNode = "CaptainComission_314";
			dialog.text = LinkRandPhrase("Captain, we're wasting time. They could find us any moment.","Captain, we're racing against the clock. Don't forget that they are looking for me.","Captain, we must not linger. My ship is too big to avoid patrol's attention.");
			link.l1 = LinkRandPhrase("Yes, you're right. We have to hurry.","Then load yourselves into the boats without further delay.","That's it... Gather your men. We're leaving.");
			link.l1.go = "exit";
		break;
		
		case "CaptainComission_326_0":
			dialog.text = "Captain, I need to talk to my men.";
			link.l1 = "Go ahead.";
			link.l1.go = "exit";
			InterfaceStates.Buttons.Save.enable = false; 
			AddDialogExitQuestFunction("CaptainComission_DialogInShore");
		break;
		
		case "CaptainComission_326":
			sld = characterFromId("Blaze");
			dialog.text = "I greet you, captain " + pchar.CaptainComission.Name + ". So, have you brought the entire cargo? And where's captain " + pchar.CaptainComission.CapName + "?";
			link.l1 = pchar.CaptainComission.CapName + " died. I had to ask "+ NPCharSexPhrase(sld, "this gentleman","this lady") +" for help. Let me introduce him, captain " + pchar.CaptainComission.FullName + ".";
			link.l1.go = "CaptainComission_327";
		break;
		
		case "CaptainComission_327":
			sld = characterFromId("Blaze");
			dialog.text = "And "+ NPCharSexPhrase(sld, "who is he? Is he","who is she? Is she") +" aware of our affairs?";
			link.l1 = "Generally, yes. But there's one nuance -"+ NPCharSexPhrase(sld, "he is certain","she is certain") +", that half the cargo belongs to "+ NPCharSexPhrase(sld, "him","her") +". We must convince "+ NPCharSexPhrase(sld, "him","her") +", that this is not exactly the case.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("CaptainComission_GangDialog");
		break;
		
		case "CaptainComission_328":
			dialog.text = "My friend " + GetFullName(pchar) +", you have already heard whatever you needed to know. We need to access your hold.";
			link.l1 = "And you think that my boys will just stand there and watch, as some ragamuffins are clearing out their hold?";
			link.l1.go = "CaptainComission_329";
		break;
		
		case "CaptainComission_329":
			pchar.GenQuest.CaptainComission.GoodsSum = 2 * sti(pchar.GenQuest.CaptainComission.GoodsQtyNorm) * sti(Goods[sti(pchar.GenQuest.CaptainComission.Goods)].Cost);
			dialog.text = "You've got a point. Cash money in the amount, say, " + pchar.GenQuest.CaptainComission.GoodsSum + " pesos, will relieve us from the necessity to clash with your crew. Keep in mind that this covers half of our cargo, so everything is fair. If you agree to this, then no one will get hurt.";
			link.l1 = "And what if I refuse?";
			link.l1.go = "CaptainComission_330";
		break;
		
		case "CaptainComission_330":
			dialog.text = "In that case violence is inevitable. You will be the first victim and you shall find peace in this cozy cove - and your crew will just be unable to come to your aid... How would you like that?";
			link.l1 = "You are leaving me with no choice. I have to join the fight.";
			link.l1.go = "CaptainComission_331";
			if(sti(pchar.money) >= sti(pchar.GenQuest.CaptainComission.GoodsSum))
			{
				link.l2 = "I think I have no choice. Alright, here's your money.";
				link.l2.go = "CaptainComission_332";
			}	
		break;
		
		case "CaptainComission_331":
			dialog.text = "Well, that's a fitting decision for "+ GetSexPhrase("a noble gentleman","a gallant lady") +".";
			link.l1 = "Stop philosophizing! Let's get down to business!";
			link.l1.go = "CaptainComission_334";
			CaptainComission_ChangeCaptain();
		break;
		
		case "CaptainComission_332":
			dialog.text = "A wise decision. Best of luck to you.";
			link.l1 = "May you choke on it...";
			link.l1.go = "CaptainComission_333";
		break;
		
		case "CaptainComission_333":
			addMoneyToCharacter(pchar, -sti(pchar.GenQuest.CaptainComission.GoodsSum));
			AddQuestRecord("CaptainComission2", "17");
			AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);
			AddQuestUserData("CaptainComission2", "sShoreName", UpperFirst(XI_ConvertString(pchar.GenQuest.CaptainComission.ConvoyShore + "Gen")));
			AddQuestUserData("CaptainComission2", "sSum", pchar.GenQuest.CaptainComission.GoodsSum);
			CloseQuestHeader("CaptainComission2");	
			ChangeOfficersLoyality("bad_all", 1);
			DialogExit();
			AddDialogExitQuestFunction("CaptainComission_GangExit");
		break;

		case "CaptainComission_334":
			LAi_SetPlayerType(pchar);
			sTemp = "Gang_";
			sGroup = "GangGroup_0";			
			LAi_LocationFightDisable(&locations[FindLocation(pchar.GenQuest.CaptainComission.ConvoyShore)], false);	
			iTemp = sti(pchar.GenQuest.CaptainComission.GangNum);
			chrDisableReloadToLocation = true;
			rChar = CharacterFromID("CapComission_1");
			LAi_SetWarriorType(rChar);
			LAi_group_MoveCharacter(rChar, sGroup);
			for(i = 0; i < iTemp; i++)
			{
				rChar = CharacterFromID(sTemp + i);
				LAi_SetWarriorType(rChar);
				LAi_group_MoveCharacter(rChar, sGroup);
				LAi_SetImmortal(rChar, false);
			}			
			LAi_group_SetRelation(sGroup, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups(sGroup, LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck(sGroup, "OpenTheDoors"); 
			LAi_group_SetCheckFunction(sGroup, "CaptainComission_GangDied");
			DialogExit();	
			AddDialogExitQuest("MainHeroFightModeOn");		
		break;

		case "CaptainComission_340":
			dialog.text = "Captain " + GetFullName(pchar) + ", we're late. I hope you understand that you are now not eligible for a reward.";
			link.l1 = "Sure I do. I've made a good coin already, thanks to you. Farewell...";
			link.l1.go = "CaptainComission_341";
		break;
		
		case "CaptainComission_341":
			Group_DeleteGroup("Sea_CapComission_1");			
			LAi_SetImmortal(NPChar, true);
			GetCharacterPos(pchar, &locx, &locy, &locz);
			LAi_SetActorType(NPChar);
			LAi_ActorGoToLocation(NPChar, "reload", LAi_FindNearestLocator("reload", locx, locy, locz), "none", "", "", "OpenTheDoors", 5.0);
			NPChar.lifeDay = 0; 						
			AddQuestRecord("CaptainComission2", "15");
			AddQuestUserData("CaptainComission2", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission2", "sSex1", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission2", "sShipType", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name")))); 
			AddQuestUserData("CaptainComission2", "sShipName", pchar.GenQuest.CaptainComission.ShipTypeName);
			AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);
			CloseQuestHeader("CaptainComission2");	
			DeleteAttribute(pchar, "GenQuest.CaptainComission");					
			DialogExit();
		break;
		
		case "CaptainComission_Canoneer":
			dialog.text = "Would you buy some rum for an old soldier who had suffered greatly in the battles for the glory of the Crown?";
			link.l1 = "Bartender - rum for us!";
			link.l1.go = "exit";
			NextDiag.TempNode = "CaptainComission_Canoneer1";
			NextDiag.CurrentNode = NextDiag.TempNode;
			AddDialogExitQuest("CaptainComission_TalkCanoneer");
		break;
		
		case "CaptainComission_Canoneer1":
			dialog.text = "Oh, thank you, " + GetAddress_Form(pchar) + ", very nice of you to treat an invalid who had completely lost his memory...";
			link.l1 = "Completely, you say?";
			link.l1.go = "CaptainComission_Canoneer2";
		break;
		
		case "CaptainComission_Canoneer2":
			dialog.text = "Absolutely, mis"+ GetSexPhrase("ter","s") +" captain - totally. I don't remember anything but a knippel flying straight into my head. Look what a hole it made in it - I guess all my memory must have leaked through it.";
			link.l1 = "Pal, keep your pathetic stories for house wives. I saw people who suffered a straight hit of grape shots, their memory was completely washed away... with their heads... And here you are talking about some imaginary chain-shot. Let's better talk about captain " + pchar.GenQuest.CaptainComission.Name +". ";
			link.l1.go = "CaptainComission_Canoneer3";
		break;
		
		case "CaptainComission_Canoneer3":
			dialog.text = "Oh, well, you know - I have to earn my living somehow. As for captain " + pchar.GenQuest.CaptainComission.Name + ", there's no profit for me in blabbering... If I were charging a hundred coins for every question about him, I would have more gold by now than the governor collects from his subjects in a year... ";
			link.l1 = "And have you tried to sell cargo, stashed away by that captain?";
			link.l1.go = "CaptainComission_Canoneer4";
		break;
		
		case "CaptainComission_Canoneer4":
			dialog.text = "What? Another sleuthhound? I am telling you once again - I don't remember any captain " + pchar.GenQuest.CaptainComission.Name + "! I am contused, and I have the doctor's certificate confirming that! What else do you need?!";
			link.l1 = "Wow, Wow, don't get so excited. You know... He was too late. Captain " + pchar.GenQuest.CaptainComission.CapName + " asked me to tell that " + pchar.GenQuest.CaptainComission.Name + " should not show his face in that settlement - the authorities know about the circumstances of destruction of " + GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipTypeVictim),"Name") + "Acc")) + " '" + pchar.GenQuest.CaptainComission.VictimShipName + ", and he was going to be arrested.";
			link.l1.go = "CaptainComission_Canoneer5";
		break;
		
		case "CaptainComission_Canoneer5":
			dialog.text = "Phew. You should have told that right away and not be talking in circles. It was me who asked captain " + pchar.GenQuest.CaptainComission.CapName + " to intercept our ship on her return. " +
				"It was moved at the docks right after that bloody fight. What that damn pirate was doing there with his goods?! So many lads are dead because of him.";
			link.l1 = "And how did you manage to survive?";
			link.l1.go = "CaptainComission_Canoneer6";	
		break;
		
		case "CaptainComission_Canoneer6":
			dialog.text = "By mistake. To honest, by my own damn mistake. I wasn't fast enough, so our longboat didn't make it from the danger area. I was the only one who suffered though. Got hit by some wreck and thrown into the water. I didn't remember how I reached the shore.";
			link.l1 = "And how did you manage to wriggle out of the inquest?";
			link.l1.go = "CaptainComission_Canoneer7";
		break;
		
		case "CaptainComission_Canoneer7":
			dialog.text = "I told them that I was contused during boarding and I didn't know anything about no cargo. I also pretended to be weak-minded - you know, I have just recently got to my feet, right before arriving of " + GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name") + "Acc")) + ". Couldn't move properly, my coordination was screwed.";
			link.l1 = "Hey, but who had blurted out the secret about the cargo, anyway?";
			link.l1.go = "CaptainComission_Canoneer8";
		break;
		
		case "CaptainComission_Canoneer8":
			dialog.text = "The pirates have sent a letter to the governor - allegedly on behalf of the injured merchant. They decided to take vengeance on the captain for his persistence. It was his fault, his dumb stubbornness lead us into this mess.";
			link.l1 = "But how did you encounter that pirate in the first place?";
			link.l1.go = "CaptainComission_Canoneer9";
		break;
		
		case "CaptainComission_Canoneer9":
			dialog.text = "I don't know. It was an ordinary patrol and there was an ordinary ship sailing under the flag of " + NationNameGenitive(sti(pchar.GenQuest.CaptainComission.Nation)) + ". I have no idea why the captain decided to inspect it, but they paid no heed to a warning shot, and as we caught up with them, they raised a 'Jolly Roger'. " +
				"We didn't have the fort's support, so the fight wasn't easy. Then the boarding part. I still can not realize how we had them beaten.\n" + 
				"Well, and we saw all that precious cargo. The devil himself must had given it to us. We had to hid the cargo ashore and blow the captured ship sky high. She was too damaged.";
			link.l1 = "Aren't you afraid that all your efforts and sacrifices would be in vain, if the governor's men discover the cache?";	
			link.l1.go = "CaptainComission_Canoneer10";
		break;
		
		case "CaptainComission_Canoneer10":
			iTmp = FindNonEnemyColonyForAdventure(sti(pchar.GenQuest.CaptainComission.Nation),pchar.GenQuest.CaptainComission.City, true);			
			pchar.GenQuest.CaptainComission.CanoneerCity = Colonies[iTmp].id;			
			pchar.GenQuest.CaptainComission.Sum = 20000 + 2000 * sti(pchar.rank);
			dialog.text = "They won't find it. I have blasted the cave's entrance well, after all, I was the best explosives expert in the whole squadron. Only smugglers can find my stash, they know every inch of this place.\n" + 
				"Look, I myself have no clue what to do with the booty. I can't neither sell nor move it away on my own. Besides, no one will do business with a cracked skull. I don't want to make money on deaths of my crew comrades, but I can tell you location of the stash for " + pchar.GenQuest.CaptainComission.Sum + "  pesos if you take me to " + XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.CanoneerCity) + ".";
			if(sti(pchar.money) >= sti(pchar.GenQuest.CaptainComission.Sum))	
			{
				link.l1 = "I agree. Here's your money. Now it's your word.";	
				link.l1.go = "CaptainComission_Canoneer11";
			}
			else
			{
				link.l1 = "Damn it! Alright, wait here, I'll fetch the money.";
				link.l1.go = "CaptainComission_Canoneer12";				
			}	
			link.l2 = "That's too much, buddy. Besides, I don't have a suitable ship. Well, good luck to you and farewell...";
			link.l2.go = "CaptainComission_Canoneer13";
		break;
		
		case "CaptainComission_Canoneer11":
			addMoneyToCharacter(pchar, -sti(pchar.GenQuest.CaptainComission.Sum));
			pchar.GenQuest.CaptainComission.ConvoyShore = SelectQuestShoreLocationFromSea(GetArealByCityName(pchar.GenQuest.CaptainComission.City));
			pchar.GenQuest.CaptainComission.GoodsQty = makeint(sti(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipTypeVictim),"Capacity")) / sti(Goods[sti(pchar.GenQuest.CaptainComission.Goods)].Weight));
			dialog.text = "Fine, then. Meet me at midnight. Take care of your holds and make sure that they have enough room for " + pchar.GenQuest.CaptainComission.GoodsQty + " pieces of " + GetStrSmallRegister(XI_ConvertString(Goods[sti(pchar.GenQuest.CaptainComission.Goods)].Name + "Gen")) + ".  It would be a pity to loose such hard won prize... ";
			link.l1 = "I'll take care of that. See you in the cove...";
			link.l1.go = "CaptainComission_Canoneer14";
		break;
		
		case "CaptainComission_Canoneer12":
			AddQuestRecord("CaptainComission2", "41");
			AddQuestUserData("CaptainComission2", "sShipType", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name") + "Acc"))); 
			AddQuestUserData("CaptainComission2", "sShipName", pchar.GenQuest.CaptainComission.ShipTypeName);			
			AddQuestUserData("CaptainComission2", "sSum", pchar.GenQuest.CaptainComission.Sum);
			AddQuestUserData("CaptainComission2", "sName", GetName( NAMETYPE_ORIG, pchar.GenQuest.CaptainComission.CanoneerName, NAME_NOM));
			SetFunctionTimerCondition("CaptainComission_CanoneerWaitMoney", 0, 0, 1, false);
			NextDiag.TempNode = "CaptainComission_Canoneer15";
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			AddDialogExitQuest("CaptainComission_exit_sit");
		break;
		
		case "CaptainComission_Canoneer13":
			AddQuestRecord("CaptainComission2", "40");
			AddQuestUserData("CaptainComission2", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission2", "sShipType", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name") + "Acc"))); 
			AddQuestUserData("CaptainComission2", "sShipName", pchar.GenQuest.CaptainComission.ShipTypeName);			
			AddQuestUserData("CaptainComission2", "sName", GetName( NAMETYPE_ORIG, pchar.GenQuest.CaptainComission.CanoneerName, NAME_NOM));
			AddQuestUserData("CaptainComission2", "sShipTypeQuest", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipTypeVictim),"Name") + "Acc")));
			AddQuestUserData("CaptainComission2", "sShipNameQuest", pchar.GenQuest.CaptainComission.VictimShipName);
			CloseQuestHeader("CaptainComission2");
			LAi_CharacterDisableDialog(NPChar);
			pchar.GenQuest.CaptainComission = "close";
			SetFunctionExitFromLocationCondition("CaptainComission_ExitFromLoc", pchar.location, false);
			DialogExit();
			AddDialogExitQuest("CaptainComission_exit_sit");
		break;
		
		case "CaptainComission_Canoneer14":
			AddQuestRecord("CaptainComission2", "43");
			AddQuestUserData("CaptainComission2", "sShipType", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name") + "Acc"))); 
			AddQuestUserData("CaptainComission2", "sShipName", pchar.GenQuest.CaptainComission.ShipTypeName);			
			AddQuestUserData("CaptainComission2", "sName", GetName( NAMETYPE_ORIG, pchar.GenQuest.CaptainComission.CanoneerName, NAME_NOM));
			AddQuestUserData("CaptainComission2", "sShipTypeQuest", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipTypeVictim),"Name") + "Acc")));
			AddQuestUserData("CaptainComission2", "sShipNameQuest", pchar.GenQuest.CaptainComission.VictimShipName);
			AddQuestUserData("CaptainComission2", "sSum", pchar.GenQuest.CaptainComission.GoodsQty);
			AddQuestUserData("CaptainComission2", "sGoods", GetStrSmallRegister(XI_ConvertString(Goods[sti(pchar.GenQuest.CaptainComission.Goods)].Name + "Gen")));
			AddQuestUserData("CaptainComission2", "sShoreName", XI_ConvertString(pchar.GenQuest.CaptainComission.ConvoyShore + "Acc"));			
			LAi_CharacterDisableDialog(NPChar);
			SetFunctionTimerConditionParam("CaptainComission_TimeIsOver", 0, 0, 1, MakeInt(24 - GetHour()), false);
			SetFunctionTimerCondition("CaptainComission_MeetCanoneerInShoreTimer", 0, 0, 1, false);
			DialogExit();
			AddDialogExitQuest("CaptainComission_exit_sit");
		break;
		
		case "CaptainComission_Canoneer15":
			if(sti(pchar.money) >= sti(pchar.GenQuest.CaptainComission.Sum))	
			{
				dialog.text = "And here you are, at last. I already started to worry. I thought you would just turn me to the authorities.";
				link.l1 = "I haven't gone crazy yet. Here's your money. Now it's your word.";
				link.l1.go = "CaptainComission_Canoneer11";
			}	
			else
			{
				dialog.text = "So, where is the money?";	
				link.l1 = "Damn it! Alright, wait here, I'll fetch it.";
				link.l1.go = "exit";
				NextDiag.TempNode = "CaptainComission_Canoneer15";
				NextDiag.CurrentNode = NextDiag.TempNode;
			}
		break;
		
		case "CaptainComission_350":
			dialog.text = "Captain, apparently, we are late. The smugglers have found the cache.";
			link.l1 = "I am not going to give up on my booty, even the devil himself won't take it from me.";
			link.l1.go = "CaptainComission_351";
			link.l2 = "I quit, deal with your competitors by yourself.";	
			link.l2.go = "CaptainComission_352";
		break;
		
		case "CaptainComission_351":
			DialogExit();
			AddDialogExitQuest("CaptainComission_GangDialog_1");
		break;
		
		case "CaptainComission_352":
			DialogExit();
			SetFunctionExitFromLocationCondition("CaptainComission_NoGangDialog", pchar.location, false);
		break;
		
		case "CaptainComission_360":
			dialog.text = "Captain, we have a serious affair here. I advise you to take your squadron away, before our ships arrive.";
			link.l1 = "Gentlemen, it looks like you're trying to take that doesn't belong to you.";
			link.l1.go = "CaptainComission_361";
		break;
		
		case "CaptainComission_361":
			dialog.text = "Oh, really?! Do you have an idea whom you are talking to?";
			link.l1 = "I am talking to you, friend. That cargo, which you are going to appropriate, has a rightful owner, and I am representing him.";
			link.l1.go = "CaptainComission_362";
		break;
		
		case "CaptainComission_362":
			dialog.text = "We will not allow you to interfere with our affairs, even if you were our God's Messiah! Clear the fairway, if you cherish your life?";
			link.l1 = "Didn't I make myself clear? That cargo is mine, and I am not leaving without it!";
			link.l1.go = "CaptainComission_363";
		break;
		
		case "CaptainComission_363":
			dialog.text = "Fuck you! Then you will stay here forever!";
			link.l1 = "We'll see who's gonna stay here forever, jerk.";
			link.l1.go = "CaptainComission_364";
		break;
				
		case "CaptainComission_364":
			LAi_SetPlayerType(pchar);
			sTemp = "Gang_";
			sGroup = "GangGroup_0";			
			LAi_LocationFightDisable(&locations[FindLocation(pchar.GenQuest.CaptainComission.ConvoyShore)], false);	
			iTemp = sti(pchar.GenQuest.CaptainComission.GangNum);
			chrDisableReloadToLocation = true;
			if(pchar.GenQuest.CaptainComission.variant == "A2")
			{
				rChar = CharacterFromID("CapComission_1");
				LAi_SetWarriorType(rChar);
				LAi_group_MoveCharacter(rChar, LAI_GROUP_PLAYER);						
			}
			if(pchar.GenQuest.CaptainComission.variant == "A3")
			{
				rChar = CharacterFromID("CapComission_Canoneer");
				LAi_SetWarriorType(rChar);
				LAi_group_MoveCharacter(rChar, LAI_GROUP_PLAYER);			
			}	
			for(i = 0; i < iTemp; i++)
			{
				rChar = CharacterFromID(sTemp + i);
				LAi_SetWarriorType(rChar);
				LAi_group_MoveCharacter(rChar, sGroup);
				LAi_SetImmortal(rChar, false);
			}			
			LAi_group_SetRelation(sGroup, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups(sGroup, LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck(sGroup, "OpenTheDoors"); 
			if(pchar.GenQuest.CaptainComission.variant == "A2")
			{
				LAi_group_SetCheckFunction(sGroup, "CaptainComission_CheckCaptainAfterBattle");
			}
			if(pchar.GenQuest.CaptainComission.variant == "A3")
			{
				LAi_group_SetCheckFunction(sGroup, "CaptainComission_CheckGangAfterBattle");
			}	
			DialogExit();	
			AddDialogExitQuest("MainHeroFightModeOn");						
		break;
		
		case "CaptainComission_365":
			dialog.text = "Captain, order your men to hurry - a patrol may arrive anytime. Besides, the smugglers were obviously waiting for their transports as well.";
			link.l1 = "Yeah, we need to hurry... Load the cargo into the holds, and let's get out of here.";
			link.l1.go = "exit";
			NextDiag.TempNode = "CaptainComission_365";
			NextDiag.CurrentNode = NextDiag.TempNode;
		break;
		
		case "CaptainComission_366":
			dialog.text = "Thank you, captain " + GetFullName(pchar) + ". If it wasn't you, the smugglers would have got our cargo, and those guys who had fallen defending it would have died in vain...";
			link.l1 = "Thanks to you for believing me, actually.";
			link.l1.go = "CaptainComission_367";
		break;
		
		case "CaptainComission_367":
			dialog.text = "I have one trinket - perhaps, I owe my life to it. Please, accept it - it might be your lucky charm. Thank you again - and farewell.";
			link.l1 = "Thanks for the present, I didn't expect it. You'd better take care of your health while you have coins in your pockets.";
			link.l1.go = "CaptainComission_368";
		break;
		
		case "CaptainComission_368":
			LAi_SetActorType(NPChar);
			LAi_SetImmortal(NPChar, true);
			GetCharacterPos(pchar, &locx, &locy, &locz);
			LAi_SetActorType(NPChar);
			LAi_ActorGoToLocation(NPChar, "reload", LAi_FindNearestLocator("reload", locx, locy, locz), "none", "", "", "OpenTheDoors", 5.0);			
			NPChar.LifeDay = 0;
			GiveItem2Character(pchar, pchar.GenQuest.CaptainComission.Prize);
			AddQuestRecord("CaptainComission2", "48");
			AddQuestUserData("CaptainComission2", "sShipType", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name") + "Acc")));
			AddQuestUserData("CaptainComission2", "sShipName", pchar.GenQuest.CaptainComission.ShipTypeName);
			AddQuestUserData("CaptainComission2", "sCharName", GetName( NAMETYPE_ORIG, pchar.GenQuest.CaptainComission.CanoneerName, NAME_ABL));
			AddQuestUserData("CaptainComission2", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.CanoneerCity + "Gen"));
			CloseQuestHeader("CaptainComission2");
			DeleteAttribute(pchar, "GenQuest.CaptainComission");
			DialogExit();
		break;
		
		case "CaptainComission_370":
			if(pchar.GenQuest.CaptainComission == "MayorTalkBad")
			{
				pchar.quest.CaptainComission_TimeIsOver.over = "yes";
			}	
			dialog.text = "Apparently, today is my visiting day. Do you need me?";
			link.l1 = "If you are captain " + pchar.GenQuest.CaptainComission.Name + ", then yes.";
			link.l1.go = "CaptainComission_371";
		break;
		
		case "CaptainComission_371":
			dialog.text = "...former captain" + pchar.GenQuest.CaptainComission.Name + "...";
			link.l1 = "I am " + GetFullName(pchar) + ", and I have a couple of questions to you.";
			link.l1.go = "CaptainComission_372";
		break;
		
		case "CaptainComission_372":
			dialog.text = "And why do you think that I would answer them?";
			link.l1 = "Captain " + pchar.GenQuest.CaptainComission.CapName + " asked me to warn you that the circumstances of destruction of " + GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipTypeVictim),"Name") + "Acc")) + " '" + pchar.GenQuest.CaptainComission.VictimShipName + " became known to the authorities, " +
				"but I didn't catch you ship on the voyage from " + XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City1 + "Gen") + ".";
			link.l1.go = "CaptainComission_373";	
		break;
		
		case "CaptainComission_373":
			dialog.text = "And where is captain " + pchar.GenQuest.CaptainComission.CapName + "?";
			link.l1 = "He died.";
			link.l1.go = "CaptainComission_374";
		break;
		
		case "CaptainComission_374":
			dialog.text = "I see... So that's how it is, eh? Many things are now put into place. So, someone has blabbed out that we had pillaged " + GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipTypeVictim),"Name") + "Gen")) + ". " +
				"Sooner or later, they will find the cargo and hang me. Captain " + pchar.GenQuest.CaptainComission.CapName + " is dead, it means no one can help me\nExept you\n " + GetFullName(pchar) + ", get me out of here and I will make it worth you while.";
			if(!CheckAttribute(pchar,"GenQuest.CaptainComission.GetRumour"))
			{
				if(CheckAttribute(pchar,"GenQuest.CaptainComission.SpeakMayor"))
				{
					link.l1 = "The governor received a message from the owner of the cargo. And the numbers in it are quite impressive, you know.";
					link.l1.go = "CaptainComission_375";
				}
				else
				{
					link.l1 = "But surely you don't think that I'll be helping you blindfolded?";
					link.l1.go = "CaptainComission_375";
				}
			}			
			else
			{
				if(CheckAttribute(pchar,"GenQuest.CaptainComission.SpeakMayor"))
				{
					link.l1 = "The governor received a message from the owner of the cargo. And the numbers in it are quite impressive, you know.";
					link.l1.go = "CaptainComission_375";				
				}
				else
				{
					link.l1 = "There are gossips in the colony that you have dealings with the smugglers...";
					link.l1.go = "CaptainComission_375";				
				}
			}
		break;
		
		case "CaptainComission_375":
			sTemp = GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipTypeVictim),"Name") + "Gen"));
			dialog.text = "Looks like I'll have to tell you the whole story.\n" +
				"During one of regular patrols I met a vessel under the flag of " + NationNameGenitive(sti(pchar.GenQuest.CaptainComission.Nation)) + ". They had ignored my orders to surrender. " +
				"We had reached " + sTemp + " '" + pchar.GenQuest.CaptainComission.VictimShipName + "' after a short chase and they raised the black flag. The fort was quite far away, so we had to fight on our own. They destroyed our jib-boom, that's why we couldn't avoid boarding.\n" + 
				"It was close, but we managed to kill them all  thanks to Holy Mary and a musketeer unit. Imagine our happiness when we found out that " + sTemp + " was filled with valuables. " +
				"We have decided that this is a decent reward for our wounds and deaths of our men\nIt was dark already, we managed to take " + sTemp +" to the closest bay and hide the cargo ashore. Then we burnt " + sTemp +" and I reported about a sunken pirate vessel. Of course, I didn't mention the cargo.";		
			link.l1 = "I think there is no point for you in tricking me. So, I am proposing a deal - you show me the cache, and I'll bring you to whatever place in the archipelago you want.";
			link.l1.go = "CaptainComission_376";
		break;
		
		case "CaptainComission_376":
			dialog.text = "Ha-ha-ha... No, captain, I will not leave the settlement without my share - even if I have to hang on the gallows.";
			link.l1 = "Alright. You will get your half.";
			link.l1.go = "CaptainComission_377";
			link.l2 = "Hmm... You know, I am not willing to risk my had for your well-being. Farewell...";
			link.l2.go = "CaptainComission_378";
		break;
		
		case "CaptainComission_377":
			dialog.text = "Now you are talking. I am ready\nFirst, you should hide me onboard of your vessel. I will show you the bay where the stash is hidden.";
			link.l1 = "Then let's act quickly and coordinated. I will open your cell, and you follow me. Don't fall back and no questions until we're out of the fort.";
			link.l1.go = "CaptainComission_379";
		break;
		
		case "CaptainComission_378":
			pchar.quest.CaptainComission_GetSecretTimeIsOut.over = "yes";
			sld = CharacterFromID("CapComission_1");
			sld.LifeDay = 0;
			ChangeCharacterComplexReputation(pchar,"nobility", -5);			
			AddQuestRecord("CaptainComission2", "8");
			AddQuestUserData("CaptainComission2", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);
			CloseQuestHeader("CaptainComission2");
			DeleteAttribute(pchar, "GenQuest.CaptainComission");
			DialogExit();
		break;
		
		case "CaptainComission_379":
			AddQuestRecord("CaptainComission2", "21");
			AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);
			pchar.quest.CaptainComission_PrisonFree_Death.win_condition.l1 = "NPC_Death";
			pchar.quest.CaptainComission_PrisonFree_Death.win_condition.l1.character = "CapComission_1";
			pchar.quest.CaptainComission_PrisonFree_Death.win_condition = "CaptainComission_PrisonFree_Death";
			GetCharacterPos(npchar, &locx, &locy, &locz);	
			ChangeCharacterAddressGroup(npchar, npchar.location, "reload", LAi_FindNearestFreeLocator("reload", locx, locy, locz));
			LAi_group_Register("CapComission_Prison");
			LAi_group_SetRelation("CapComission_Prison", LAI_GROUP_PLAYER, LAI_GROUP_FRIEND);
			LAi_group_SetAlarmReaction(LAI_GROUP_PLAYER, "CapComission_Prison", LAI_GROUP_ENEMY, LAI_GROUP_FRIEND);
			LAi_group_MoveCharacter(npchar, "CapComission_Prison");
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			LAi_CharacterDisableDialog(npchar);
			pchar.GenQuest.CaptainComission.PrisonFree = true;
			if(pchar.GenQuest.CaptainComission == "MayorTalkGood") 
			{
				chrDisableReloadToLocation = true;	
				sld = CharacterFromId(pchar.GenQuest.CaptainComission.City + "JailOff");	
				sld.dialog.currentnode = "CapComission_PrisonFree1";
			}	
			pchar.quest.CapComission_ExitFromPrison.win_condition.l1 = "ExitFromLocation";
            pchar.quest.CapComission_ExitFromPrison.win_condition.l1.location = pchar.location;
            pchar.quest.CapComission_ExitFromPrison.win_condition = "CaptainComission_ExitFromPrison"; 
			DialogExit();
		break;		
		
		case "CaptainComission_380":
			pchar.quest.CaptainComission_GetSecretTimeIsOut.over = "yes";
			pchar.quest.CaptainComission_PrisonFree_Death.over = "yes";
			DeleteAttribute(pchar,"GenQuest.CaptainComission.canSpeakCaptain");
			DeleteAttribute(pchar,"GenQuest.CaptainComission.PrisonFree");
			pchar.GenQuest.CaptainComission = "CanGetGoods";
			pchar.GenQuest.CaptainComission.ConvoyShore = SelectQuestShoreLocationFromSea(GetArealByCityName(pchar.GenQuest.CaptainComission.City));
			dialog.text = "Thanks for the rescue. Let's move to " + XI_ConvertString(pchar.GenQuest.CaptainComission.ConvoyShore + "Acc") + ", I will point the location of the stash. We should hurry until savages find the place.";			
			link.l1 = "Are you sure that we'll be able to pick up the entire cargo?";
			link.l1.go = "CaptainComission_381";
		break;
		
		case "CaptainComission_381":
			pchar.GenQuest.CaptainComission.GoodsQty = makeint(sti(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipTypeVictim),"Capacity")) / sti(Goods[sti(pchar.GenQuest.CaptainComission.Goods)].Weight));
			dialog.text = "You are right, make sure that you have enough room for " + pchar.GenQuest.CaptainComission.GoodsQty + " pieces of " + GetStrSmallRegister(XI_ConvertString(Goods[sti(pchar.GenQuest.CaptainComission.Goods)].Name + "Gen")) + ". It would be a pity to loose such valuable booty with so much blood on it. They won't give us a second chance.";
			link.l1 = "I'll take care of that.";
			link.l1.go = "CaptainComission_382";
		break;
		
		case "CaptainComission_382":
			AddQuestRecord("CaptainComission2", "24");
			AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);
			AddQuestUserData("CaptainComission2", "sShoreName", XI_ConvertString(pchar.GenQuest.CaptainComission.ConvoyShore + "Dat"));
			AddQuestUserData("CaptainComission2", "sGoodsQuantity", pchar.GenQuest.CaptainComission.GoodsQty);
			AddQuestUserData("CaptainComission2", "sGoods", GetStrSmallRegister(XI_ConvertString(Goods[sti(pchar.GenQuest.CaptainComission.Goods)].Name + "Gen")));
			SetFunctionLocationCondition("CaptainComission_MeetInShore", pchar.GenQuest.CaptainComission.ConvoyShore, false); 
			SetFunctionTimerConditionParam("CaptainComission_CapEscapeTimer", 0, 0, 1, MakeInt(24 - GetHour()), false);
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, false);
			chrDisableReloadToLocation = false; // Откроем выход
			DeleteAttribute(pchar,"TownEscape");
			QuestOpenSeaExit();
			DialogExit();
			AddDialogExitQuest("CanEnterToMap");
		break;
		
		case "CaptainComission_383":
			dialog.text = "Captain, we don't need witnesses. Please, try to persuade these people to leave the cove.";
			link.l1 = "Fine, let's do that.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("CaptainComission_GangDialogGetGoods");
		break;
		
		case "CaptainComission_384":
			dialog.text = "Captain, I am sorry, but this is not the best place for your exercises. That dock is already occupied.";
			link.l1 = "Gentlemen, I came here not for sightseeing. I have business here.";
			link.l1.go = "CaptainComission_385";
		break;
		
		case "CaptainComission_385":
			dialog.text = "Well, we aren't catching jellyfish here, either - turn your ships around and get the hell out of here.";
			link.l1 = "I don't want to waste my time persuading you to leave. Either you do it willingly and live - or you stay here for good.";
			link.l1.go = "CaptainComission_386";
		break;
		
		case "CaptainComission_386":
			dialog.text = "I see that you have trouble in understanding my words. Alright, if's your funeral...";
			link.l1 = "That's better!";
			link.l1.go = "CaptainComission_364";
		break;
		
		case "CaptainComission_387":
			LAi_LocationDisableOfficersGen(pchar.GenQuest.CaptainComission.ConvoyShore, false);
			pchar.GenQuest.CaptainComission.MaxGoodsQty = GetSquadronFreeSpace(pchar, sti(pchar.GenQuest.CaptainComission.Goods));
			if(sti(pchar.GenQuest.CaptainComission.MaxGoodsQty) > sti(pchar.GenQuest.CaptainComission.GoodsQty)) pchar.GenQuest.CaptainComission.MaxGoodsQty = pchar.GenQuest.CaptainComission.GoodsQty;
			dialog.text = "We're here. The cache is in a niche in that crag. The entrance is blocked with rocks. In the cache, there is " + pchar.GenQuest.CaptainComission.GoodsQty +" units of " + GetStrSmallRegister(XI_ConvertString(Goods[sti(pchar.GenQuest.CaptainComission.Goods)].Name + "Gen")) +". Remember that one half is mine?";
			link.l1 = "I sure do. We have got some time while my men are loading goods. Let's talk where you and your cargo must be taken to.";
			link.l1.go = "CaptainComission_388";
			link.l2 = "Very good. Now tell me - is there any reason for me to share?";
			link.l2.go = "CaptainComission_389";
			if(CheckAttribute(pchar,"GenQuest.CaptainComission.MayorTalkGood"))
			{
				link.l3 = "Captain " + pchar.GenQuest.CaptainComission.Name + ", I have to tell you something unpleasant. I do work for the governor. And I intend to deliver him all  the cargo you have hidden. You should return to a prison and wait there for your fate.";
				link.l3.go = "CaptainComission_389";
			}	
		break;
		
		case "CaptainComission_388":
			iTmp = FindNonEnemyColonyForAdventure(sti(pchar.GenQuest.CaptainComission.Nation),pchar.GenQuest.CaptainComission.City, true);			
			sTemp = Colonies[iTmp].id;
			pchar.GenQuest.CaptainComission.ConvoyIsland = GetArealByCityName(sTemp);
			pchar.GenQuest.CaptainComission.ConvoyShore = SelectQuestShoreLocationFromSea(pchar.GenQuest.CaptainComission.ConvoyIsland);
			pchar.GenQuest.CaptainComission.ConvoyCity = sTemp;			
			pchar.GenQuest.CaptainComission.iDay  = 20 + cRand(10);
			iGoods = GetSquadronFreeSpace(pchar, sti(pchar.GenQuest.CaptainComission.Goods)); 
			if(iGoods < sti(pchar.GenQuest.CaptainComission.GoodsQty)) pchar.GenQuest.CaptainComission.GoodsQty = iGoods;
			SetCharacterGoods(pchar, sti(pchar.GenQuest.CaptainComission.Goods), GetCargoGoods(pchar, sti(pchar.GenQuest.CaptainComission.Goods)) + sti(pchar.GenQuest.CaptainComission.GoodsQty));// перегруз
			dialog.text = "I need to get to " + XI_ConvertString(pchar.GenQuest.CaptainComission.ConvoyShore + "Gen") + ", at " + XI_ConvertString(GetIslandByCityName(sTemp) + "Dat") + " for " + pchar.GenQuest.CaptainComission.iDay + " days. My people there must have had prepared the cargo for selling.";
			link.l1 = "Alright. It's time to leave, then.";
			link.l1.go = "CaptainComission_391";
		break;
		
		case "CaptainComission_389":
			dialog.text = "Right. One always should trust the mind not the heart. Watch and learn\nEven though I didn't expected this, but I am always ready for a fight. You will answer for your betrayal.";
			link.l1 = "I am at your service...";
			link.l1.go = "CaptainComission_390";
		break;
		
		case "CaptainComission_390":
			LAi_SetPlayerType(pchar);
			LAi_group_Delete("EnemyFight");
			chrDisableReloadToLocation = true;
			rChar = CharacterFromID("CapComission_1");
			LAi_SetWarriorType(rChar);
			LAi_group_MoveCharacter(rChar, "EnemyFight");		
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "OpenTheDoors"); 			
			if(pchar.GenQuest.CaptainComission == "CapDuel")
			{
				LAi_group_SetCheckFunction("EnemyFight", "CaptainComission_CaptainDiedDuel");
			}
			else
			{
				LAi_group_SetCheckFunction("EnemyFight", "CaptainComission_CheckCaptainDied");
			}	
			DialogExit();	
			AddDialogExitQuest("MainHeroFightModeOn");						
		break;
		
		case "CaptainComission_391":
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, false);
			GetCharacterPos(NPChar, &locx, &locy, &locz);
			LAi_SetActorType(NPChar);
			LAi_ActorGoToLocation(NPChar, "reload", LAi_FindNearestLocator("reload", locx, locy, locz), "none", "", "", "OpenTheDoors", 5.0);			
			pchar.GenQuest.CaptainComission.CapGoodsQty = sti(pchar.GenQuest.CaptainComission.GoodsQty)/2;
			if(sti(pchar.GenQuest.CaptainComission.CapGoodsQty) > sti(pchar.GenQuest.CaptainComission.MaxGoodsQty)) pchar.GenQuest.CaptainComission.CapGoodsQty = pchar.GenQuest.CaptainComission.MaxGoodsQty;
			AddQuestRecord("CaptainComission2", "26");
			AddQuestUserData("CaptainComission2", "sGoodsQuantity", pchar.GenQuest.CaptainComission.MaxGoodsQty);
			AddQuestUserData("CaptainComission2", "sGoods", GetStrSmallRegister(XI_ConvertString(Goods[sti(pchar.GenQuest.CaptainComission.Goods)].Name + "Gen")));
			AddQuestUserData("CaptainComission2", "sSum1", pchar.GenQuest.CaptainComission.CapGoodsQty);
			AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);
			AddQuestUserData("CaptainComission2", "sDays", pchar.GenQuest.CaptainComission.iDay);
			AddQuestUserData("CaptainComission2", "sShoreName", XI_ConvertString(pchar.GenQuest.CaptainComission.ConvoyShore + "Acc"))
			AddQuestUserData("CaptainComission2", "sShoreType", XI_ConvertString(pchar.GenQuest.CaptainComission.ConvoyIsland + "Dat"));
			OfficersReaction("bad");
			if(CheckAttribute(pchar,"GenQuest.CaptainComission.MayorTalkGood"))
			{
				ChangeCharacterComplexReputation(pchar,"nobility", -5);
				ChangeCharacterNationReputation(pchar, sti(NPChar.nation), -10);
			}
			CaptainComission_GenerateCoastalPatrol();
			pchar.GenQuest.CaptainComission = "GetGoodsEscape";
			SetFunctionLocationCondition("CaptainComission_CapMeetInShore", pchar.GenQuest.CaptainComission.ConvoyShore, false);
			SaveCurrentQuestDateParam("GenQuest.CaptainComission.DeleiveCapShore");	
			DialogExit();
		break;
		
		case "CaptainComission_392":
			dialog.text = "Apparently, we were late... The customers didn't wait, and I have no opportunity to organize the storage and sales of the cargo by myself...";
			link.l1 = "Do you have any particular propositions in this regard?";
			link.l1.go = "CaptainComission_393";
		break;
		
		case "CaptainComission_393":
			pchar.GenQuest.CaptainComission.GoodsPrice = makeint(sti(pchar.GenQuest.CaptainComission.CapGoodsQty) * 0.75 * sti(Goods[sti(pchar.GenQuest.CaptainComission.Goods)].Cost));
			dialog.text = "Captain " + GetFullName(pchar) + ", I know it's a bit awkward, but... could you give me a monetary equivalent of my share? I suppose, " + pchar.GenQuest.CaptainComission.GoodsPrice + " pesos could be a good compromise.";
			if(sti(pchar.money) >= sti(pchar.GenQuest.CaptainComission.GoodsPrice))
			{
				link.l1 = "Yeah, it's a fair price. I don't mind. Here's your money - and farewell.";
				link.l1.go = "CaptainComission_394";
			}
			link.l2 = "Oh, no, my friend, that won't do. I cannot be nursing you forever. If you don't want to pick up your cargo - I'll just keep it. Rest assured, I'll find ways to store it and eventually sell it off.";
			link.l2.go = "CaptainComission_395";
		break;
		
		case "CaptainComission_394":
			addMoneyToCharacter(pchar, -sti(pchar.GenQuest.CaptainComission.GoodsPrice));
			dialog.text = "Hold on, captain. I want to thank you for my rescue. You know, I had almost lost hope... Here - I am sure you'll find this trinket quite useful in many difficult situations... Farewell now.";
			link.l1 = "Thanks. I didn't expect. Pleasure doing business with you.";
			link.l1.go = "CaptainComission_395";
		break;
		
		case "CaptainComission_395":
			dialog.text = "I didn't expect that from you... Apparently, I have no other choice rather than challenging you to a duel.";
			link.l1 = "I am at your service...";
			link.l1.go = "CaptainComission_390";
			pchar.GenQuest.CaptainComission = "CapDuel";
		break;
		
		case "CaptainComission_395":
			GiveItem2Character(pchar, pchar.GenQuest.CaptainComission.Prize);
			AddQuestRecord("CaptainComission2", "32");
			AddQuestUserData("CaptainComission2", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission2", "sShoreName", XI_ConvertString(pchar.GenQuest.CaptainComission.ConvoyShore + "Dat"));
			AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);
			AddQuestUserData("CaptainComission2", "sSum", pchar.GenQuest.CaptainComission.GoodsPrice);
			CloseQuestHeader("CaptainComission2");	
			GetCharacterPos(pchar, &locx, &locy, &locz);
			LAi_SetActorType(NPChar);
			LAi_ActorGoToLocation(NPChar, "reload", LAi_FindNearestLocator("reload", locx, locy, locz), "none", "", "", "OpenTheDoors", 5.0);
			NPChar.lifeDay = 0; 						
			DeleteAttribute(pchar, "GenQuest.CaptainComission");
			DialogExit();
		break;

		case "CaptainComission_396_0":
			dialog.text = "Captain, I need to talk to my men.";
			link.l1 = "Go ahead.";
			link.l1.go = "exit";
			InterfaceStates.Buttons.Save.enable = false; 
			AddDialogExitQuestFunction("CaptainComission_DialogInShore");
		break;
		
		case "CaptainComission_396":
			sld = characterFromId("Blaze");
			dialog.text = "I greet you, captain " + GetFullName(pchar) + ". So, have you brought the entire cargo? And where's captain " + pchar.CaptainComission.CapName + "?";
			link.l1 =  pchar.CaptainComission.CapName + " died, and I was arrested on a denunciation. And if captain " + pchar.CaptainComission.FullName + " didn't help me out, you wouldn't have seen neither me nor the cargo.";
			link.l1.go = "CaptainComission_397";
		break;
		
		case "CaptainComission_397":
			sld = characterFromId("Blaze");
			dialog.text = "And "+ NPCharSexPhrase(sld, "who is he? Is he","who is she? Is she") +" aware of our affairs?";
			link.l1 = "Of course. "+ NPCharSexPhrase(sld, "He extracted","She extracted") +" me from the jail and undertook to deliver half of the cargo here; the other half I promised "+ NPCharSexPhrase(sld, "him","her") +" as a compensation.";
			link.l1.go = "CaptainComission_398";
		break;
		
		case "CaptainComission_398":
			sld = characterFromId("Blaze");
			dialog.text = "Eh, captain, no way. It is your problems! I suggested we take the ship away, but you were caring too much about your bloody career. And here you are, your beloved governor has you in prison." +
				" Your cut was much smaller than a half! We didn't put our heads under grape shots to let you steal the whole half for yourself!";
			link.l1 = "Listen, boatswain, don't you remember that the ship was completely broken? That it was almost underwater? Don't you understand that if I didn't give this man a half, you would have never seen even a small piece of the cargo again?";	
			link.l1.go = "CaptainComission_399";
		break;
		
		case "CaptainComission_399":
			dialog.text = "You will not put me on! How shall we know that you are not in collusion? What if there was no arrest at all? What if you were just too greedy and decided to pocket our property? Or are you thinking that we have forgotten how to wield a blade?!";
			link.l1 = "I see you've gone crazy. You don't hear anything else than jingling of coins in your ears.";
			link.l1.go = "CaptainComission_400";
		break;
		
		case "CaptainComission_400":
			sld = characterFromId("Blaze");
			dialog.text = "Boys! Look how our captain is talking now! Indeed, greed has totally consumed him! He sold our share to "+ NPCharSexPhrase(sld, "a rascal","an adventuress") +"!!";
			link.l1 = "Shut up your foul mouth now - or I'll silence you for good!";
			link.l1.go = "exit";
			AddDialogExitQuest("CaptainComission_ShoreGangDialog");
		break;
		
		case "CaptainComission_401":
			dialog.text = "I am sorry, captain, that you had to witness this ridiculous scene and even take part in it. It's hard to believe that just a month ago we were a united crew, and every one of us would gladly sacrifice his life to save a friend.";
			link.l1 = "I must admit, I can't imagine that, no offense.";
			link.l1.go = "CaptainComission_402";
		break;
		
		case "CaptainComission_402":
			dialog.text = "Unfortunately, I have no opportunity to organize the storage and sales of the cargo by myself...";
			link.l1 = "Do you have any particular propositions in this regard?";
			link.l1.go = "CaptainComission_403";
		break;
		
		case "CaptainComission_403":
			pchar.GenQuest.CaptainComission.GoodsPrice = makeint(sti(pchar.GenQuest.CaptainComission.CapGoodsQty) * 0.75 * sti(Goods[sti(pchar.GenQuest.CaptainComission.Goods)].Cost));
			dialog.text = "Captain " + GetFullName(pchar) + ", I know it's a bit awkward, but... could you give me a monetary equivalent of my share? I suppose, " + pchar.GenQuest.CaptainComission.GoodsPrice + " pesos could be a good compromise.";
			if(sti(pchar.money) >= sti(pchar.GenQuest.CaptainComission.GoodsPrice))
			{
				link.l1 = "Alright, I don't mind. Here's your money - and farewell.";
				link.l1.go = "CaptainComission_404";
			}	
			link.l2 = "No, that will not work. You can take your cargo or leave it in the hold, but I won't give you any single coin.";
			link.l2.go = "CaptainComission_405";
		break;
		
		case "CaptainComission_404":
			bTemp = false;
			if(drand(1) == 0)
			{
			    NPChar.reputation = 60 + rand(20); 
				NPChar.alignment = "good"; 
			}	
			else
			{
			    NPChar.reputation = 10 + rand(20); 
				NPChar.alignment = "bad"; 			
			}
			if (NPChar.alignment == "good" && sti(pchar.reputation.nobility) > 50) bTemp = true; 
			if (NPChar.alignment == "bad" && sti(pchar.reputation.nobility) <= 50) bTemp = true;
			
			addMoneyToCharacter(pchar, -sti(pchar.GenQuest.CaptainComission.GoodsPrice));
			
			if(!bTemp || FindFreeRandomOfficer() < 0)
			{
				dialog.text = "Hold on, captain. I want to thank you for my rescue. You know, I had almost lost hope... Here - I am sure you'll find this trinket quite useful in many difficult situations... Farewell now.";
				link.l1 = "Thanks. I didn't expect. Pleasure doing business with you.";
				link.l1.go = "CaptainComission_406";
			}
			else
			{
				dialog.text = "Wait... I just thought... You know, my career is over now, I have no crew and I am exile in my homeland. Certainly you should be needing trusted men with a steady hand, who can keep their mouth shut. Please accept me in your crew - I promise that you won't regret it.";
				if(!CaptainComission_CheckAllPassengersHired())
				{
					link.l1 = "To be honest, I've been looking forward for your agreement for a while. Sure. See me onboard.";
					link.l1.go = "CaptainComission_407";
				}	
				link.l2 = "Hmm... you know, it seems to me that you're just too smart to be serving under anyone. Farewell...";
				link.l2.go = "CaptainComission_408";
			}
		break;
		
		case "CaptainComission_405":
			dialog.text = "Well, apparently, today is clearly not my lucky day... Alright captain - let's unsheathe our blades and be done with all of it at once...";
			link.l1 = "I am at your service...";
			link.l1.go = "CaptainComission_390";
			pchar.GenQuest.CaptainComission = "CapDuel";
			pchar.GenQuest.CaptainComission.Duel = true;
		break;
		
		case "CaptainComission_406":
			GiveItem2Character(pchar, pchar.GenQuest.CaptainComission.Prize);
			AddQuestRecord("CaptainComission2", "34");
			AddQuestUserData("CaptainComission2", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);
			AddQuestUserData("CaptainComission2", "sSum", pchar.GenQuest.CaptainComission.GoodsPrice);
			CloseQuestHeader("CaptainComission2");
			GetCharacterPos(pchar, &locx, &locy, &locz);
			LAi_SetActorType(NPChar);
			LAi_ActorGoToLocation(NPChar, "reload", LAi_FindNearestLocator("reload", locx, locy, locz), "none", "", "", "OpenTheDoors", 5.0);			
			NPChar.lifeDay = 0; 						
			DeleteAttribute(pchar, "GenQuest.CaptainComission");
			DialogExit();
		break;
		
		case "CaptainComission_407":				
			AddQuestRecord("CaptainComission2", "36");
			AddQuestUserData("CaptainComission2", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);
			AddQuestUserData("CaptainComission2", "sSum", pchar.GenQuest.CaptainComission.GoodsPrice);
			CloseQuestHeader("CaptainComission2");		
			npchar.CaptainComission = true;
			SetCharacterRemovable(Npchar, true);
			DeleteAttribute(pchar, "GenQuest.CaptainComission");
			NPChar.Dialog.Filename = "Enc_Officer_dialog.c";
			NPChar.Dialog.CurrentNode = "hired";
            NPChar.greeting = "Gr_Officer"; 			
			NPChar.quest.OfficerPrice = sti(pchar.rank)*500;	
			NPChar.loyality = MAX_LOYALITY;
			DeleteAttribute(NPChar, "LifeDay");
			pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(NPChar.id);
			AddDialogExitQuestFunction("LandEnc_OfficerHired"); 
			NPChar.quest.meeting = true; 
			DialogExit();
		break;		
		
		case "CaptainComission_408":
			AddQuestRecord("CaptainComission2", "35");
			AddQuestUserData("CaptainComission2", "sSex", GetSexPhrase("","а"));
			AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);
			AddQuestUserData("CaptainComission2", "sSum", pchar.GenQuest.CaptainComission.GoodsPrice);
			CloseQuestHeader("CaptainComission2");
			GetCharacterPos(pchar, &locx, &locy, &locz);
			LAi_SetActorType(NPChar);
			LAi_ActorGoToLocation(NPChar, "reload", LAi_FindNearestLocator("reload", locx, locy, locz), "none", "", "", "OpenTheDoors", 5.0);						
			NPChar.lifeDay = 0; 						
			DeleteAttribute(pchar, "GenQuest.CaptainComission");		
			DialogExit();
		break;		
		// Генератор "Operation 'Galleon'"
		
		// Квест "meeting in the cove" -->
		// Офицер
		case "ContraMeetManQuest_Sold_1":
			dialog.text = "None of your business. Now tell me what are you sniffing out here? Aren't you looking for a man who was just detained?!";
				link.l1 = "A man?! No...";
				link.l1.go = "ContraMeetManQuest_Sold_2";
			break;
			
		case "ContraMeetManQuest_Sold_2":
			dialog.text = "Good for you. Otherwise you would get in prison too, along with him. So don't mess around here, sailor. Get lost!";
				link.l1 = "Yeah, I'd better go...";
				link.l1.go = "ContraMeetManQuest_Sold_3";
			break;
			
		case "ContraMeetManQuest_Sold_3":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			DeleteQuestCondition("ContraMeetManQuest_TimeIsLeft"); // Время больше не роляет
			sQuestTitle = PChar.GenQuest.ContraMeetMan.QuestTown + "ContraMeetManQuest";
			AddQuestRecordEx(sQuestTitle, "ContraMeetManQuest", "8");
			PChar.GenQuest.ContraMeetMan.ToTavernPatrolInShore = true;
			LAi_CharacterDisableDialog(NPChar);
			DeleteAttribute(&Locations[FindLocation(PChar.GenQuest.ContraMeetMan.ShoreID)], "DisableEncounters"); // Включаем случайки
			ContraMeetManQuest_DeletePatrolFromShore(); // По выходу потрем всех из локации
			break;
			
		// Сам чел
		case "ContraMeetManQuest_1":
			dialog.text = "Great! We should head to the tavern to that smuggler now - I wouldn't want to linger here!";
				link.l1 = "No problem with that. Let's go...";
				link.l1.go = "ContraMeetManQuest_2";
			break;
			
		case "ContraMeetManQuest_2":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LAi_SetActorType(NPChar);
			LAi_ActorFollowEverywhere(NPChar, "", -1);
			sQuestTitle = PChar.GenQuest.ContraMeetMan.QuestTown + "ContraMeetManQuest";
			AddQuestRecordEx(sQuestTitle, "ContraMeetManQuest", "3");
			AddQuestUserData(sQuestTitle, "sDestination", XI_ConvertString(PChar.GenQuest.ContraMeetMan.ShoreID + "Dat"));
			PChar.GenQuest.ContraMeetMan.ToTavernWithMan = true;
			DeleteAttribute(&Locations[FindLocation(PChar.GenQuest.ContraMeetMan.ShoreID)], "DisableEncounters"); // Включаем случайки
			break;
		
		// Контрики в комнате таверны	
		case "ContraMeetManQuest_3":
			ContraMeetManQuest_ContersGoQut();
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			AddMoneyToCharacter(PChar, sti(PChar.GenQuest.ContraMeetMan.Money));
			sQuestTitle = PChar.GenQuest.ContraMeetMan.QuestTown + "ContraMeetManQuest";
			AddQuestRecordEx(sQuestTitle, "ContraMeetManQuest", "4");
			AddQuestUserData(sQuestTitle, "sMoney", FindRussianMoneyString(sti(PChar.GenQuest.ContraMeetMan.Money)));
			CloseQuestHeader(sQuestTitle);
			ChangeContrabandRelation(PChar, 5);
			DeleteAttribute(PChar, "GenQuest.ContraMeetMan");
			break;
			
		case "ContraMeetManQuest_4":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			AddMoneyToCharacter(PChar, sti(PChar.GenQuest.ContraMeetMan.Money));
			sQuestTitle = PChar.GenQuest.ContraMeetMan.QuestTown + "ContraMeetManQuest";
			AddQuestRecordEx(sQuestTitle, "ContraMeetManQuest", "5");
			AddQuestUserData(sQuestTitle, "sMoney", FindRussianMoneyString(sti(PChar.GenQuest.ContraMeetMan.Money)));
			CloseQuestHeader(sQuestTitle);
			ContraMeetManQuest_ContraBeatMan();
			ChangeContrabandRelation(PChar, 5);
			ChangeCharacterComplexReputation(pchar,"nobility", -5);
			DeleteAttribute(PChar, "GenQuest.ContraMeetMan");
			break;
			
		case "ContraMeetManQuest_5":
			dialog.text = "He-he... It seems, "+ GetSexPhrase("fellow","lass") +", you will go to hell with him very soon... Hey, buddy - let's gut them both!";
				link.l1 = "You filthy pig! Defend yourself!";
				link.l1.go = "ContraMeetManQuest_6";
			break;
			
		case "ContraMeetManQuest_6":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			ContraMeetManQuest_PlayerBeatContra();
			break;
			
		case "ContraMeetManQuest_7":
			dialog.text = "Thank you once again, " + PChar.name + ". Farewell...";
				link.l1 = "...";
				link.l1.go = "ContraMeetManQuest_9";
			break;
			
		case "ContraMeetManQuest_8":
			iMoney = (rand(3)+2)*500;
			PChar.GenQuest.ContraMeetMan.Money = iMoney;
			dialog.text = "A reward?! Oh, sure. Here - take " + FindRussianMoneyString(iMoney) + " and farewell...";
				link.l1 = "Goodbye...";
				link.l1.go = "ContraMeetManQuest_10";
			break;
			
		case "ContraMeetManQuest_9":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			ChangeCharacterComplexReputation(pchar,"nobility", 10);
			sQuestTitle = PChar.GenQuest.ContraMeetMan.QuestTown + "ContraMeetManQuest";
			AddQuestRecordEx(sQuestTitle, "ContraMeetManQuest", "6");
			AddQuestUserData(sQuestTitle, "sMoney", FindRussianMoneyString(iMoney));
			AddQuestUserData(sQuestTitle, "sDestination", XI_ConvertString(PChar.GenQuest.ContraMeetMan.ShoreID + "Dat"));
			CloseQuestHeader(sQuestTitle);
			ContraMeetManQuest_ContersGoQut();
			DeleteAttribute(PChar, "GenQuest.ContraMeetMan");
			break;
			
		case "ContraMeetManQuest_10":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			AddMoneyToCharacter(PChar, sti(PChar.GenQuest.ContraMeetMan.Money));
			sQuestTitle = PChar.GenQuest.ContraMeetMan.QuestTown + "ContraMeetManQuest";
			AddQuestRecordEx(sQuestTitle, "ContraMeetManQuest", "7");
			AddQuestUserData(sQuestTitle, "sMoney", FindRussianMoneyString(sti(PChar.GenQuest.ContraMeetMan.Money)));
			AddQuestUserData(sQuestTitle, "sDestination", XI_ConvertString(PChar.GenQuest.ContraMeetMan.ShoreID + "Dat"));
			CloseQuestHeader(sQuestTitle);
			ContraMeetManQuest_ContersGoQut();
			DeleteAttribute(PChar, "GenQuest.ContraMeetMan");
			break;
		// <-- Квест "meeting in the cove"
			
		// Квест на доставку письма контрику -->
		case "ContraDeliverQuest_Sold1":
			dialog.text = "Heh! You expect us to believe that bullshit?! Guys, seize these two gallows-birds!";
			//if(80 > rand(100) || sti(PChar.skill.Fortune) > rand(100)) // Попытка отмазаться
			//{
				link.l1 = "Officer, you're making a serious mistake by attempting to detain two innocent people. Believe me, I don't know that man and I could not care less about him."
				+ " I am certain that your commandant will be quite displeased with you, if you detain two law-abiding citizens...";
				link.l1.go = "ContraDeliverQuest_Sold2_Liberty";
			//}
			/*else // Тюрьма
			{
				link.l1 = "";
				link.l1.go = "ContraDeliverQuest_Sold2_Prison";
			}*/
			break;
			
		case "ContraDeliverQuest_Sold2_Liberty":
			dialog.text = "Hmm... Yes, perhaps you're right. The commandant will surely be displeased with that. You know what - let's just forget about this little incident.";
				link.l1 = "Thank you, officer, you've saved us time. I'd like to ask you to be more careful next time - surely you wouldn't want to be demoted, would you?";
				link.l1.go = "ContraDeliverQuest_Sold2_Liberty1";
			break;
			
		case "ContraDeliverQuest_Sold2_Liberty1":
			dialog.text = "No, by no means. In that case, please disperse. See you...";
				link.l1 = "That's better!";
				link.l1.go = "ContraDeliverQuest_Sold2_Liberty2";
			break;
			
		case "ContraDeliverQuest_Sold2_Liberty2":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			ContraDeliverQuest_SoldiersGoOut();
			break;
		
		case "ContraDeliverQuest_1":
			iMoney = (rand(3)+2)*500;
			if(rand(1) == 0) // Денег не дает
			{
				dialog.text = "Excellent! And now you can get lost!";
					link.l1 = "What?! And what about the money? We had a deal...";
					link.l1.go = "ContraDeliverQuest_NoMon";
			}
			else // Деньги или патруль
			{
				if(rand(2) == 1) // Патруль
				{
					dialog.text = "Thanks for the delivery. Now you may get lo... Hm, someone's coming...";
						link.l1 = "What?!";
						link.l1.go = "ContraDeliverQuest_Patrol";
				}
				else // Просто отдает деньги
				{
					dialog.text = "Great. Thanks for the delivery. Here, take " + FindRussianMoneyString(iMoney) ". And keep in mind that smugglers will always remember good people...";
					link.l1 = "I do hope so. Farewell.";
					link.l1.go = "ContraDeliverQuest_GoWithMoney";
					PChar.GenQuest.ContraDeliver.Money = iMoney;
				}
			}
			
			ChangeContrabandRelation(PChar, 5); // Письмо доставили - повышаем отношение у контриков
			ChangeCharacterComplexReputation(pchar,"nobility", -5); // Помогли контрикам - репу понижаем
			RemoveItems(PChar, "letter_1", 1);
			BackItemDescribe("letter_1");
			DeleteAttribute(&Items[FindItem("letter_1")], "City");
			rChar = &Characters[GetCharacterIndex(Locations[FindLocation(PChar.location)].townsack + "_Smuggler")];
			SaveCurrentNpcQuestDateParam(rChar, "work_date");
			break;
			
		case "ContraDeliverQuest_Patrol":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LAi_LocationFightDisable(LoadedLocation, true); // Чтоб не поубивали кого-нить
			ContraDeliverQuest_GeneratePatrolToRoom();
			break;
			
		case "ContraDeliverQuest_NoMon":
			dialog.text = "Listen - me and you had no deal between us whatsoever. Claim your money from whoever struck that deal with you.";
				link.l1 = "Well, that's certainly not my lucky day, what else can I say?! Alright, see ya...";
				link.l1.go = "ContraDeliverQuest_GoWithoutMoney";
				link.l2 = RandSwear() + "You will answer for that! Prepare to die!";
				link.l2.go = "ContraDeliverQuest_PrepareToFight";
			break;
			
		case "ContraDeliverQuest_GoWithoutMoney": // Уходим без денег
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			chrDisableReloadToLocation = false;
			bDisableFastReload         = false;
			PChar.GenQuest.ContraDeliver.Complete.WithoutMoney = true;
			sQuestTitle = PChar.GenQuest.ContraDeliver.QuestTown + "ContraDeliverQuest";
			AddQuestRecordEx(sQuestTitle, "ContraDeliverQuest", "4");
			AddQuestUserData(sQuestTitle, "sColony", XI_ConvertString("Colony" + PChar.GenQuest.ContraDeliver.QuestTown));
			LAi_ActorGoToLocation(NPChar, "reload", "reload1_back", "none", "", "", "", 3.0);
			break;
			
		case "ContraDeliverQuest_PrepareToFight":
			dialog.text = "You dared to challenge me, "+ GetSexPhrase("whelp","filth") +"? Well, you surely have no idea what's good for you. I will gut you!";
				link.l1 = "...";
				link.l1.go = "ContraDeliverQuest_Fight";
			break;
			
		case "ContraDeliverQuest_Fight": // Бой
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LAi_SetImmortal(NPChar, false);
			LAi_ActorAttack(NPChar, PChar, "");
			LAi_SetFightMode(PChar, true);
			SetFunctionNPCDeathCondition("ContraDeliverQuest_ContraIsDead", NPChar.ID, false);
			break;
			
		case "ContraDeliverQuest_GoWithMoney": // Уходим с деньгами
			AddMoneyToCharacter(PChar, sti(PChar.GenQuest.ContraDeliver.Money));
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			chrDisableReloadToLocation = false;
			bDisableFastReload         = false;
			sQuestTitle = PChar.GenQuest.ContraDeliver.QuestTown + "ContraDeliverQuest";
			AddQuestRecordEx(sQuestTitle, "ContraDeliverQuest", "3");
			AddQuestUserData(sQuestTitle, "sMoney", FindRussianMoneyString(sti(PChar.GenQuest.ContraDeliver.Money)));
			CloseQuestHeader(sQuestTitle);
			DeleteAttribute(PChar, "GenQuest.ContraDeliver"); // Квест пройден - атрибуды потрем
			LAi_ActorGoToLocation(NPChar, "reload", "reload1_back", "none", "", "", "", 3.0);
			break;
		// <-- Квест на доставку письма контрику
			
		// Церковеый генератор. Квест № 1. Диалог кэпа, которого ищем -->
		case "ChurchGenQuest_1_DeckDialog_1":
			if(CheckAttribute(PChar, "GenQuest.ChurchQuest_1.NeedToDialogWithCap"))
			{
				if(CheckAttribute(PChar, "GenQuest.ChurchQuest_1.CapWaitOnTavern")) // Если ждет в таверне
				{
					dialog.text = RandPhraseSimple("Half thousand men! And a dead man chest! Hic!", "Drink! Hic! And the devil had done for the - Hic! - rest!");
						link.l1 = "Ohh... Well. Hello, mister " + GetFullname(NPChar) + ".";
						link.l1.go = "ChurchGenQuest1_DialogInTavernWithCap_2";
						PChar.Quest.Church_GenQuest1_Timer.over = "yes";
				}
				else // на палубе своего шипа
				{
					if(!CheckAttribute(PChar, "GenQuest.ChurchQuest_1.Complete"))
					{
						dialog.text = "Alright, let's see now... Three pieces of sailcloth, planks for the ship's skin, replacing the betings and ropes on the braces...";
							link.l1 = "Hello, mister " + GetFullName(NPChar) + ". I am captain " + PChar.name + ".";
							link.l1.go = "ChurchGenQuest1_DialogShip_1";
					}
					else
					{
						dialog.text = LinkRandPhrase("Leave my ship immediately - I have much to do without you!", "You have received your books - what else do you want?!", "I did whatever you wanted - what else do you want from me?!");
							link.l1 = "Don't get so excited or you'll have a heart attack!";
							link.l1.go = "exit";
					}					
				}
			}
			else
			{
				dialog.text = RandPhraseSimple("Rum, rum! Give me rum... Hic!", "It's been a while... hic... when I last got drunk like that...");
					link.l1 = "Yeah, your hold is full - maybe it's time to head for a cove?";
					link.l1.go = "exit";
			}			
			NextDiag.TempNode = "ChurchGenQuest_1_DeckDialog_1";
			break;
			
		case "ChurchGenQuest1_DialogInTavernWithCap_2":
			dialog.text = RandPhraseSimple("Please have a seat, cap-hic-tain! What's your poison?", "Have a seat, cap! What would you like to drink? Hic...");
					link.l1 = "Thanks, but I'd prefer a nice conversation with a decent person.";
					link.l1.go = "ChurchGenQuest1_DialogInTavernWithCap_3";
			break;
			
		case "ChurchGenQuest1_DialogInTavernWithCap_3":
			dialog.text = "Are you trying - hic! - to insult me?.. There's not a single decent man in that tavern! Hic! Only bandits and cutthroats! All of them extortionists, and that one - first among them! Their ringleader, a moray down his throat!";
				link.l1 = "I meant you. You are the one, I wish to talk to. And who is the bandit leader and why would he...";
				link.l1.go = "ChurchGenQuest1_DialogInTavernWithCap_4";
			break;
			
		case "ChurchGenQuest1_DialogInTavernWithCap_4":
			dialog.text = "Mis"+ GetSexPhrase("ter","s") +"! My dear! What was your name, once again? I respect you! Non a soul has called an old salt a decent man so far! I'd do anything for you! I'd give you all my money, to the last peso!.. Oh, just forgot. I'm out of money. I don't even have any roolies left. That bastard, that racketeer just took the last scrolly from me, may the imps load their cannons with his guts in hell!";
				link.l1 = "Mister captain? Are you alright? Do you realize you are delirious? What scrollies?";
				link.l1.go = "ChurchGenQuest1_DialogInTavernWithCap_5";
			break;
			
		case "ChurchGenQuest1_DialogInTavernWithCap_5":
			dialog.text = "No, no! This old cap might be drunk, but he still keeps his wits with him. The books and the scrollies were given to me by Father " + PChar.GenQuest.ChurchQuest_1.ToName + ", I was taking them to " + XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.QuestTown) + ". And in the morning I've gone to the local church and mentioned about these books to the local padre. Of course, he wanted to see them - you know their kind, they are just crazy about their saints' lives and all that stuff. So, I sent a cabin boy to fetch the chest with them. And while I was waiting, I decided to gamble a bit - and lost all my money. Everything! Nothing to pay for the booze with! So, the tavern owner took the books on pledge, and then I also gave him the scrolls...";
				link.l1 = "So, you sold books, the holy books entrusted to you by priest  " + XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.ToColony + "Gen") + "?";
				link.l1.go = "ChurchGenQuest1_DialogInTavernWithCap_6";
			break;
			
		case "ChurchGenQuest1_DialogInTavernWithCap_6":
			dialog.text = "I know, I know... I will be burning in Hell for all eternity. I now cannot show my face neither to the Father, who gave me that errand, neither to one who was delivering the papers, neither to the local... Who will now pray for my soul? And what if they excommunicate me? Oh, woe to me... I need a drink... ";
				link.l1 = "Wow, Wow, it's not that bad. Your actions were lousy and impious, and yet I am ready to help you. I will pay your debt and buy these manuscripts. Besides, since I already know both mentioned priests, I will sail directly to  "+ XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.QuestTown) + " in order to deliver the papers there. Deal?";
				link.l1.go = "ChurchGenQuest1_DialogInTavernWithCap_7";
			break;
			
		case "ChurchGenQuest1_DialogInTavernWithCap_7":
			dialog.text = "Savior! God's Angel... Of course, I agree! I'd give you everything... everything! If only I could have another drink...";
				link.l1 = "I guess you already have had enough... Oh, whatever. I'll buy you some more rum from the bartender.";
				link.l1.go = "ChurchGenQuest1_DialogInTavernWithCap_8";
			break;
			
		case "ChurchGenQuest1_DialogInTavernWithCap_8":
			DialogExit();
			DeleteAttribute(PChar, "GenQuest.ChurchQuest_1.NeedToDialogWithCap");
			PChar.GenQuest.ChurchQuest_1.NeedToDialogWithBarmen = true;
			sQuestTitle = PChar.GenQuest.ChurchQuest_1.QuestTown + "ChurchGenQuest1";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest1", "7_2");
			AddQuestUserData(sQuestTitle, "sColony", XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.QuestTown));
			AddQuestUserData(sQuestTitle, "sCapName", GetFullName(NPChar));
			NextDiag.CurrentNode = "ChurchGenQuest_1_DeckDialog_1";
			break;
			
		case "ChurchGenQuest1_DialogShip_1":
			dialog.text = "...and the sheets! We need to replace the sheets, too!.. Oh, hi. Please don't be offended, mis"+ GetSexPhrase("ter","s") +" what-is-your-name, but right now, as you can see, I am quite busy, so if you have business with me, please be quick about it.";
				link.l1 = "As far as I know, father " + PChar.GenQuest.ChurchQuest_1.ToName + " gave you some holy papers in " + XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.ToColony + "Dat") + ". You promised to deliver them to " + XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.QuestTown) + " because you were sailing in that direction anyway.";
				link.l1.go = "ChurchGenQuest1_DialogShip_2";
			break;
			
		case "ChurchGenQuest1_DialogShip_2":
			dialog.text = "I was heading in that direction - until that accursed storm nearly destroyed my old tub, and I got stuck here for hell knows how long! These swindlers in the docks keep trying to slip me rotten planks washed ashore by the tide for the ship's hull, and for the sails - some old sackcloth, on which their grandmas were sleeping when they were still young.";
				link.l1 = "Sir, next time I will gladly listen your magnificent stories but now I'd like to learn more about a fate of the books and manuscripts you have received at " + XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.ToColony + "Dat") + ".";
				link.l1.go = "ChurchGenQuest1_DialogShip_3";
			break;
			
		case "ChurchGenQuest1_DialogShip_3":
			dialog.text = "No one - do you hear me? - no one dares to blame me for the delay with the delivery of these accursed papers!";
				link.l1 = "Oh, no, I certainly didn't mean that. I only wanted to ease your burden. Thing is, that " + PChar.GenQuest.ChurchQuest_1.ToName + " is quite concerned about books and papers to be delivered to " + XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.QuestTown) + ". Actually, I am going to sail there right now.";
				link.l1.go = "ChurchGenQuest1_DialogShip_4";
			break;
			
		case "ChurchGenQuest1_DialogShip_4":
		if(rand(3) != 1)
		{
			dialog.text = "It seems to me, mis"+ GetSexPhrase("ter","s") +", that you have a spiritual counselor in every port. Although that's none of my concern. If you care for that crap that much, grab your books and get lost! Good riddance!";
				link.l1 = "Thank you, mister captain. Good luck with your repairs.";
				link.l1.go = "ChurchGenQuest1_DialogShip_5_1";
		}
		else // Свитки не отдает
		{
			dialog.text = "Don't worry about that, mis"+ GetSexPhrase("ter","s") +", and travel to " +  XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.QuestTown) + " lightly, since it was me who undertook to deliver those papers, and it will be me who is going to do this at all costs, so that no one would cry out on every corner that captain " + NPChar.name + " did not stay true to his word!";
				link.l1 = "But mister captain, the point actually is...";
				link.l1.go = "ChurchGenQuest1_DialogShip_5_2";
		}
			break;
			
		case "ChurchGenQuest1_DialogShip_5_1":
			DialogExit();
			AddItems(PChar, "Bible", 1);	// Даем рукописи
			items[FindItem("Bible")].Name = "itmname_ChurchGenQuest1Bible";	// Меняем имя. Потом поменять обратно!
			ChangeItemDescribe("Bible", "itmdescr_ChurchGenQuest1Bible"); // Меняем дескрайб. Потом поменять обратно!
			items[FindItem("Bible")].City = XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.QuestTown + "Gen"); // Переменная. Потом удалить!
			sQuestTitle = PChar.GenQuest.ChurchQuest_1.QuestTown + "ChurchGenQuest1";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest1", "10");
			AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("","а"));
			AddQuestUserData(sQuestTitle, "sColony", XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.QuestTown));
			AddQuestUserData(sQuestTitle, "sCapName", GetFullName(NPChar));
			PChar.GenQuest.ChurchQuest_1.Complete = true; // Квест выполнен
			SetFunctionTimerCondition("Church_GenQuest1_DeleteCapitan", 0, 0, 1, false); // Трем судно кэпа
			break;
			
		case "ChurchGenQuest1_DialogShip_5_2":
			dialog.text = "Actually, the point is that I have no business with you at all. Holy Father gave me a task - deliver the books to " + XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.QuestTown) + " and hand them over to the local priest. I don't see you there. Not at all! Best of luck.";
//				link.l1 = "Fine, then. You're a very responsible man, although it's your only merit. Good luck to you, my discourteous friend";
//				link.l1.go = "ChurchGenQuest1_DialogShip_5_2_1"; // Сваливаем, поверили ему
				link.l2 = "I had enough of your insolent behavior. Your dumb mouth can force even an angel to do violence. I must fulfill the will of my holy father and I will use my weapon if I must!";
				link.l2.go = "ChurchGenQuest1_DialogShip_5_2_2"; // 
			break;
			
		case "ChurchGenQuest1_DialogShip_5_2_1":
			DialogExit();
			sQuestTitle = PChar.GenQuest.ChurchQuest_1.QuestTown + "ChurchGenQuest1";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest1", "11");
			AddQuestUserData(sQuestTitle, "sColony", XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.QuestTown));
			AddQuestUserData(sQuestTitle, "sCapName", GetFullName(NPChar));
			PChar.GenQuest.ChurchQuest_1.Complete.NoManuscripts = true; // Квест выполнен без манускриптов
			SetFunctionTimerCondition("Church_GenQuest1_DeleteCapitan", 0, 0, 1, false); // Трем судно кэпа
			break;
			
		case "ChurchGenQuest1_DialogShip_5_2_2":
			dialog.text = "Quiet, quiet, captain " + PChar.name + "! What's up with you? Oh, well, I see that if you don't bring these papers, all those Holy Fathers would be quite angry with you, not to mention our Father in Heaven. Alright, take you theological valuables and go with God's blessing.";
				link.l1 = "Glad that you have not only understood my position but also remembered my name. I suggest you recall it every time you are about to do something foolish.";
				link.l1.go = "ChurchGenQuest1_DialogShip_5_2_3"; // Сваливаем, поверили ему
			break;
			
		case "ChurchGenQuest1_DialogShip_5_2_3":
			DialogExit();
			AddItems(PChar, "Bible", 1);	// Даем рукописи
			items[FindItem("Bible")].Name = "itmname_ChurchGenQuest1Bible";	// Меняем имя. Потом поменять обратно!
			ChangeItemDescribe("Bible", "itmdescr_ChurchGenQuest1Bible"); // Меняем дескрайб. Потом поменять обратно!
			items[FindItem("Bible")].City = XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.QuestTown + "Gen"); // Переменная. Потом удалить!
			sQuestTitle = PChar.GenQuest.ChurchQuest_1.QuestTown + "ChurchGenQuest1";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest1", "10");
			AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("",""));
			AddQuestUserData(sQuestTitle, "sColony", XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.QuestTown + "Dat"));
			AddQuestUserData(sQuestTitle, "sCapName", GetFullName(NPChar));
			PChar.GenQuest.ChurchQuest_1.Complete = true; // Квест выполнен
			SetFunctionTimerCondition("Church_GenQuest1_DeleteCapitan", 0, 0, 1, false); // Трем судно кэпа
			break;
			
		// <-- Церковеый генератор. Квест № 1. Диалог кэпа, которого ищем
			
		case "Left_Time_Case":
			dialog.text = RandPhraseSimple("Get lost...", "Don't disturb me!");
				link.l1 = "...";
				link.l1.go = "exit";
				NextDiag.TempNode = "Left_Time_Case";
			break;
			
		case "Church_GenQuest_2_1":
			if(sti(PChar.GenQuest.ChurchQuest_2.BanditsCount) == 1)
			{
				dialog.text = RandSwear() + "You shouldn't have said that! Now I'll have to send you to the Lord to pray for the forgiveness of my sins!";
			}
			
			if(sti(PChar.GenQuest.ChurchQuest_2.BanditsCount) == 2)
			{
				dialog.text = RandSwear() + "You shouldn't have said that! Now I'll have to send you to the Lord to pray for the forgiveness of our sins!";
			}
			
			if(sti(PChar.GenQuest.ChurchQuest_2.BanditsCount) > 2)
			{
				dialog.text = RandSwear() + "You shouldn't have said that! Now I'll have to send you to the Lord to pray for the forgiveness of all our sins!";
			}
			
				link.l1 = "Hardly, buddy. Everyone will answer for themselves to the God!";
				link.l1.go = "exit";
				NPChar.money = sti(PChar.GenQuest.ChurchQuest_2.MoneyCount);
				LAi_LocationFightDisable(LoadedLocation, false);
				AddDialogExitQuest("Church_GenQuest2_BanditsIsEnemies");
			break;
			
		case "Church_GenQuest_2_ShoreBandit_1":
			dialog.text = "Hey, why swearing? What if I have business with you.";
				link.l1 = "Now that's news! You know, I have short talks with the likes of you!";
				link.l1.go = "Church_GenQuest_2_ShoreBandit_2";
				LAi_LocationFightDisable(LoadedLocation, false);
			break;
			
		case "Church_GenQuest_2_ShoreBandit_2":
			dialog.text = "Well, I am not going to have long talks with you, either. But, perhaps, you'd be interested in buying a couple of trinkets for a good price?";
				link.l1 = "Do I look like a bloody receiver of stolen goods?!";
				link.l1.go = "Church_GenQuest_2_ShoreBandit_3";
			break;
			
		case "Church_GenQuest_2_ShoreBandit_3":
			if(rand(1) == 0)
			{
				dialog.text = "Easy, easy, there are no thieves among us! This vase was given to us for honest work! Just look - pure gold, adorned with pearls. But the point is that we have no need of it. So we just want to sell it and split the money.";
					link.l1 = "Let me take a closer look... Oh my! This is the communion cup!!! So, you are those blasphemers who had pillaged the church of " + XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_2.QuestTown + "Gen") + "?! There you are!";
					link.l1.go = "Church_GenQuest_2_ShoreBandit_4";
					break;
			}
		
			dialog.text = "Quiet, mis"+ GetSexPhrase("ter","s") +" hypocrite! You know, we are a bit short of money, so we decided to sell something. Take a look at this vase - pure gold, adorned with pearls. Special price for you - say, a thousand coins.";
				link.l1 = "Let me take a closer look... Oh my! This is the communion cup!!! So, you are those blasphemers who had pillaged the church of " + XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_2.QuestTown + "Gen") + "?! There you are!";
				link.l1.go = "Church_GenQuest_2_ShoreBandit_Real_Band_1";
			break;
			
		case "Church_GenQuest_2_ShoreBandit_4":
			dialog.text = "Hold your horses, mis"+ GetSexPhrase("ter","s") +"!.. Damn, I told that blockhead not to kick up a fuss until the time is right...";
				link.l1 = "What are you blabbering? Alright, make your choice: either you give me your stolen loot willingly, or I am calling the guards.";
				link.l1.go = "Church_GenQuest_2_ShoreBandit_5";
			break;
			
		case "Church_GenQuest_2_ShoreBandit_5":
			dialog.text = "Listen, "+ GetSexPhrase("good man","young lady") +", we don't need any quarrels, so let's resolve this matter peacefully. You must believe us - we didn't actually pillage that church; neither do we have any money. Yes, we have received several pesos and that golden trinket for imitating the robbery. And this golden cup was the only thing we had left after we had paid the smugglers...";
				link.l1 = "So, you're trying to say that...";
				link.l1.go = "Church_GenQuest_2_ShoreBandit_6";
			break;
			
		case "Church_GenQuest_2_ShoreBandit_6":
			dialog.text = "That accursed priest hired us - that's what I am saying! But why did he have to send you our way?.. Well, we're even now. Take this vase and show it to that hypocrite - you'd see for yourself that he'd be wiggling like a squid on the shoal!";
				link.l1 = "Give me the cup and get lost, before I change my mind.";
				link.l1.go = "Church_GenQuest_2_ShoreBandit_7";
				link.l2 = "You're talking smoothly, but I am not that easy to deceive. If you want to convince me - convince my blade first.";
				link.l2.go = "Church_GenQuest_2_ShoreBandit_8";
				// Тут давать чашу, если будет
				ChurchGenQuest2_GiveCup();
				PChar.GenQuest.ChurchQuest_2.Complete.PriestIsThief = true;
			break;
			
		case "Church_GenQuest_2_ShoreBandit_7":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			iBanditsCount = PChar.GenQuest.ChurchQuest_2.BanditsCount;
			for(i=0; i<iBanditsCount; i++)
			{
				rChar = CharacterFromID("Church_GenQuest2_Bandit_" + i);
				LAi_Type_Actor_Reset(rChar);
				LAi_CharacterDisableDialog(rChar);
				rChar.LifeDay = 0;
				LAi_ActorRunToLocation(rChar, "reload", "reload1_back", "none", "", "", "", -1);
			}
			
			// Разрешим генерацию энкаунтеров, откроем выходы
			DeleteAttribute(LoadedLocation, "DisableEncounters");
			chrDisableReloadToLocation = false;
			
			sQuestTitle = PChar.GenQuest.ChurchQuest_2.QuestTown + "ChurchGenQuest2";
			AddQuestrecordEx(sQuestTitle, "ChurchGenQuest2", "10_1");
			AddQuestUserData(sQuestTitle, "sName", PChar.GenQuest.ChurchQuest_2.QuestTown.PriestName);
			break;
			
		case "Church_GenQuest_2_ShoreBandit_8":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			AddDialogExitQuest("Church_GenQuest2_BanditsIsEnemies");
			sQuestTitle = PChar.GenQuest.ChurchQuest_2.QuestTown + "ChurchGenQuest2";
			AddQuestrecordEx(sQuestTitle, "ChurchGenQuest2", "10_2");
			break;
			
		case "Church_GenQuest_2_ShoreBandit_Real_Band_1":
			if(PChar.GenQuest.ChurchQuest_2.BanditsCount == 1)
			{
				dialog.text = RandSwear() + "Didn't I tell those shags: hold your grabby paws and don't take anything but money from the priest!";
			}
			else
			{
				dialog.text = RandSwear() + "Didn't I tell those insatiable shags: hold your grabby paws and don't take anything but money from the priest!";
			}
			
					link.l1 = "What are you blabbering? Alright, make your choice: either you give me your stolen loot willingly, or I am calling the guards.";
					link.l1.go = "Church_GenQuest_2_ShoreBandit_Real_Band_2";
			break;
			
		case "Church_GenQuest_2_ShoreBandit_Real_Band_2":
			dialog.text = "I am making a different choice - you shut your blabbing mouth and give me your purse - and I spare your life.";
				link.l1 = "I will help you to get audience with our Lord now!";
				link.l1.go = "Church_GenQuest_2_ShoreBandit_Real_Band_2_1";
				link.l2 = "Alright, I'll give you some money - but only of my own accord, so that you and your friends could lead an honest life and didn't have to debase yourselves with robbery.";
				link.l2.go = "Church_GenQuest_2_ShoreBandit_Real_Band_2_2";
				link.l3 = "Ehh... Alright, let's put our disagreements aside and go back to the beginning of our conversation. So how much did you want for that thing?";
				link.l3.go = "Church_GenQuest_2_ShoreBandit_Real_Band_2_3";
			break;
			
		case "Church_GenQuest_2_ShoreBandit_Real_Band_2_1":
			// Не забыть чашу!
			ChurchGenQuest2_GiveCup();
			PChar.GenQuest.ChurchQuest_2.Complete.With_All = true;
			NPChar.money = ((rand(3) + 6) * 1000);
			PChar.GenQuest.ChurchQuest_2.MoneyCount = NPChar.money;
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			AddDialogExitQuest("Church_GenQuest2_BanditsIsEnemies");
			sQuestTitle = PChar.GenQuest.ChurchQuest_2.QuestTown + "ChurchGenQuest2";
			AddQuestrecordEx(sQuestTitle, "ChurchGenQuest2", "11_1");
			AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("ел","ла"));
			AddQuestUserData(sQuestTitle, "sSex1", GetSexPhrase("","а"));
			break;
			
		case "Church_GenQuest_2_ShoreBandit_Real_Band_2_2":
			AddMoneyToCharacter(PChar, -sti(PChar.money)/2); // Забираем половину денег
			PChar.GenQuest.ChurchQuest_2.Complete.Without_All = true; // Полностью проигрышный вариант. Остаемся ни с чем
			iBanditsCount = PChar.GenQuest.ChurchQuest_2.BanditsCount;
			for(i=0; i<iBanditsCount; i++)
			{
				rChar = CharacterFromID("Church_GenQuest2_Bandit_" + i);
				LAi_SetCitizenType(rChar);
				rChar.LifeDay = 0;
				rChar.Dialog.Currentnode = "First time";
			}
			
			DeleteAttribute(PChar, "GenQuest.ChurchQuest_2.BanditsInShore");
			sQuestTitle = PChar.GenQuest.ChurchQuest_2.QuestTown + "ChurchGenQuest2";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest2", "11_2");
			AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("",""));
			AddQuestUserData(sQuestTitle, "sSex1", GetSexPhrase("",""));
			DeleteAttribute(LoadedLocation, "DisableEncounters");
			chrDisableReloadToLocation = false;
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			break;
			
		case "Church_GenQuest_2_ShoreBandit_Real_Band_2_3":
			iMoney = makeint(makeint(Pchar.money)/20)*10;
			dialog.text = "I don't need any problems, either, " + GetAddress_Form(pchar) + ", but now the price has gone higher. For that precious cup I will require everything you have with you.";
			if(iMoney >= makeint(Pchar.rank)*300)
			{
				link.l1 = "You greedy scum! I only have " + FindRussianMoneyString(iMoney) + " with me. Take it and get lost!";
				link.l1.go = "Church_GenQuest_2_ShoreBandit_Real_Band_2_3_1";
			}
			else
			{
				link.l1 = "Wrong choice, greedy rat - you will not make any good at my expense!"+ GetSexPhrase(" I am free as the wind - now here, the next day there, today I am poor - tomorrow I shall be rich...","") +"";
				link.l1.go = "Church_GenQuest_2_ShoreBandit_Real_Band_2_3_2";
			}
			break;
			
		case "Church_GenQuest_2_ShoreBandit_Real_Band_2_3_1":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			ChurchGenQuest2_GiveCup();	// Даем чашу
			AddMoneyToCharacter(PChar, -(makeint(makeint(Pchar.money)/20)*10));
			PChar.GenQuest.ChurchQuest_2.Complete.Only_With_Cup = true;
			iBanditsCount = PChar.GenQuest.ChurchQuest_2.BanditsCount;
			for(i=0; i<iBanditsCount; i++)
			{
				rChar = CharacterFromID("Church_GenQuest2_Bandit_" + i);
				LAi_SetCitizenType(rChar);
				rChar.LifeDay = 0;
				rChar.Dialog.Currentnode = "Left_Time_Case"; // Диалог не забыть поменять.
			}
			
			DeleteAttribute(LoadedLocation, "DisableEncounters");
			chrDisableReloadToLocation = false;
			sQuestTitle = PChar.GenQuest.ChurchQuest_2.QuestTown + "ChurchGenQuest2";
			AddQuestrecordEx(sQuestTitle, "ChurchGenQuest2", "11_3");
			AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("","а"));
			DeleteAttribute(PChar, "GenQuest.ChurchQuest_2.BanditsInShore");
			break;

		case "Church_GenQuest_2_ShoreBandit_Real_Band_2_3_2":
			dialog.text = "Aren't you trying to say that particularly today "+ GetSexPhrase("you are poor","you have no money") +"?!";
				link.l1 = "Exactly, my greedy friend - to your great disappointment. And now I must excuse myself - I've got much to do.";
				link.l1.go = "Church_GenQuest_2_ShoreBandit_Real_Band_2_3_3";	
			break;
			
		case "Church_GenQuest_2_ShoreBandit_Real_Band_2_3_3":
			dialog.text = "Stop! We are going to check that, and if you have not spoken the truth, I will put your lying tongue inside an ant colony!";
				link.l1 = "After saying that you're done for!";
				link.l1.go = "Church_GenQuest_2_ShoreBandit_Real_Band_2_3_4";
			break;
			
		// Можно этот кэйс - Church_GenQuest_2_ShoreBandit_Real_Band_2_1
		case "Church_GenQuest_2_ShoreBandit_Real_Band_2_3_4":
				// ГГ как-бы может обыскать трупики и забрать все барахло...
				PChar.GenQuest.ChurchQuest_2.Complete.With_All = true;
				NPChar.money = ((rand(3) + 6) * 1000);
				PChar.GenQuest.ChurchQuest_2.MoneyCount = NPChar.money;
				DialogExit();
				NextDiag.CurrentNode = NextDiag.TempNode;
				AddDialogExitQuest("Church_GenQuest2_BanditsIsEnemies");
				sQuestTitle = PChar.GenQuest.ChurchQuest_2.QuestTown + "ChurchGenQuest2";
				AddQuestrecordEx(sQuestTitle, "ChurchGenQuest2", "11_4");
				AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("As a real gentleman, I am honest","I am honest"));
			break;
			
		///////////////////////////////////////////////////////////////////////////////////////////////////
		// ГЕНЕР "PIRATES ON AN UNINHABITED ISLAND"
		///////////////////////////////////////////////////////////////////////////////////////////////////
		
		case "PiratesOnUninhabited_1":
			dialog.text = "Oh, there's nothing to decide. We can decide everything by ourselves. But we'll take your ship to get out of here.";
			link.l1 = "On one condition - first you'll have to take my blade from me...";
			link.l1.go = "PiratesOnUninhabited_2";
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "PiratesOnUninhabited_2":
			for(i = 0; i < sti(PChar.GenQuest.PiratesOnUninhabited.PiratesQty); i++)
			{
				LAi_SetImmortal(CharacterFromID("PirateOnUninhabited_" + i), false);
			}
			
			LAi_Group_SetRelation("PiratesOnUninhabitedGroup", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_Group_FightGroups("PiratesOnUninhabitedGroup", LAI_GROUP_PLAYER, true);
			DialogExit();
		break;
		
		case "PiratesOnUninhabited_3":
			PChar.GenQuest.PiratesOnUninhabited.MainPirateName = GetRandName(NAMETYPE_NICK, NAME_GEN);
			PChar.GenQuest.PiratesOnUninhabited.BadPirateName = GetRandName(NAMETYPE_ORIG, NAME_NOM);
			
				i = PiratesOnUninhabited_GenerateShipType();
				PChar.GenQuest.PiratesOnUninhabited.StartShipType = i;
			
			if(dRand(1) == 0)
			{
				PChar.GenQuest.PiratesOnUninhabited.Shipwrecked = true;
				
				dialog.text = "Hello, captain! Apparently, the Providence itself sent you to save  " + PChar.GenQuest.PiratesOnUninhabited.MainPirateName + " and his boys. We are in dire need here." +
					"Our " + GetStrSmallRegister(XI_ConvertString(ShipsTypes[i].Name)) + " crashed in the storm at the local reefs, and the waves washed ashore the survivors of the crew." +
					"For " + (5 + dRand(7)) + " weeks we had been peering at the horizon hoping to see a sail of a ship that would come to rescue us.";
				link.l1 = RandPhraseSimple(RandPhraseSimple("Yeah, that's an unenviable fate. But such is the lot of the sailor - anyone could end up in your place.", "I see... God holds every life - it's that He's just too busy to remember everyone."),
					RandPhraseSimple("Indeed. Man proposes, but God disposes.", "Yeah, that surely was a stroke of bad luck."));
				link.l1.go = "PiratesOnUninhabited_4";
			}
			else
			{
				dialog.text = "It was very serious! That scoundrel " + PChar.GenQuest.PiratesOnUninhabited.BadPirateName + " couldn't think of a punishment other than leaving " + ChangeNameCase(NAMETYPE_NICK, PChar.GenQuest.PiratesOnUninhabited.MainPirateName, NAME_ACC) + " on an uninhabited island, like a scabby cur! " +
					"He hoped that sun and thirst would parch us like a dried mackerel on a fisherman's stand! But he was wrong, for Providence itself was on our side, as It sent you here to rescue us...";
				link.l1 = RandPhraseSimple("Not so fast, friend. As far as I can say, you are men of a free profession, and you ended up here not by accident.", "Already talking about salvation? As far as I understand you are here because of some special achievements.");
				link.l1.go = "PiratesOnUninhabited_41";
			}
		break;
		
		case "PiratesOnUninhabited_4":
			PChar.GenQuest.PiratesOnUninhabited.PiratesCount = 5 + dRand(5);
			
			dialog.text = RandPhraseSimple("Captain, please be a kind soul and help  " + PiratesOnUninhabited_GetStringNum(sti(PChar.GenQuest.PiratesOnUninhabited.PiratesCount)) + " destitute men. You are our only hope save for our most gracious Lord.",
				"Captain, would you have free lockers on your ship for " + PiratesOnUninhabited_GetStringNum(sti(PChar.GenQuest.PiratesOnUninhabited.PiratesCount)) + " destitute men?");
			
			if(GetFreeCrewQuantity(PChar) >= sti(PChar.GenQuest.PiratesOnUninhabited.PiratesCount) && GetPassengersQuantity(PChar) < PASSENGERS_MAX)
			{
				link.l1 = "Ohh... and where would you want me to take you?";
				link.l1.go = "PiratesOnUninhabited_5";
			}
			
			link.l2 = RandPhraseSimple(RandPhraseSimple("I am really sorry, but there is not even a single free hammock, not to mention the cabins. Sailors are sleeping on the deck, they cannot even take a good night's rest after a watch...",
				"I would really hate to disappoint you, but the ship is overloaded, and people have to sleep in the weather. Should there be an outbreak of disease, I will lose half the crew."),
				RandPhraseSimple("I am really sorry, but there is absolutely no spare crew space on my ship. I cannot take on board any more passengers.", "I have to disappoint you, but my ship is overloaded with crew men. I fear the epidemic..."));
			link.l2.go = "PiratesOnUninhabited_21";
			
			if(stf(PChar.reputation.nobility) <= REPUTATION_NEUTRAL)
			{
				link.l3 = "You're a seasoned sailor and you should know that the presence of someone, who had suffered a shipwreck, is very bad sign. My sailors will just toss you all overboard.";
				link.l3.go = "PiratesOnUninhabited_7";
			}
		break;
		
		case "PiratesOnUninhabited_5":
			dialog.text = "Mmm... You know, for several reasons we would like to stay as far from authorities as possible... Please, deliver us to any cove on an inhabited island or in the Main, and then we'd be able to provide for ourselves.";
			link.l1 = "Well, I've got enough free lockers and hammocks. Load yourself into the boat.";
			link.l1.go = "PiratesOnUninhabited_10";
			link.l2 = "Hmm... Ill luck... We have battles ahead of us, and I don't know where you're going to be more safe - on board of my ship or in this cozy cove.";
			link.l2.go = "PiratesOnUninhabited_6";
		break;
		
		case "PiratesOnUninhabited_6":
			dialog.text = "Oh, captain! These are the times when one cannot feel safe even in a bed with his wife - even less so in the sea... Look at these thugs - every one of them is ready to fight bare-handed against cannons. They do not crave for safety and comfort - you can read that on their faces!";
			link.l1 = "On their faces, I can only read the willingness to stab their foolish benefactor in the back.";
			link.l1.go = "PiratesOnUninhabited_7";
			link.l2 = "Hmm... That, actually, is a good idea. Tell me friend - are your thugs willing to serve in my crew?";
			link.l2.go = "PiratesOnUninhabited_8";
		break;
		
		case "PiratesOnUninhabited_7":
			dialog.text = "A pity, captain... I see that we cannot figure it out in a friendly way. I guess I'll have to remind you the sea code. And keep in mind - when it gets to a boarding, we are second to none...";
			link.l1 = "Well, now I can finally see you for what you actually are...";
			link.l1.go = "PiratesOnUninhabited_2";
			AddDialogExitQuest("MainHeroFightModeOn");
			ChangeCharacterComplexReputation(pchar,"nobility", -3.0);
		break;
		
		// Берем их в команду
		case "PiratesOnUninhabited_8":
			dialog.text = "But of course! They would be happy to become part of your boarding party! None will best them in a fight, save for maybe Davy Jones himself!";
			link.l1 = "Fine, then. Load yourselves into the boats...";
			link.l1.go = "PiratesOnUninhabited_9";
		break;
		
		case "PiratesOnUninhabited_9":
			bTemp = CheckAttribute(PChar, "GenQuest.PiratesOnUninhabited.Shipwrecked");
			
			for(i = 0; i < sti(PChar.GenQuest.PiratesOnUninhabited.PiratesQty); i++)
			{
				rChar = CharacterFromID("PirateOnUninhabited_" + i);
				LAi_SetWarriorTypeNoGroup(rChar);
				rChar.LifeDay = 0;
				
				if(bTemp)
				{
					rChar.Dialog.currentnode = "PiratesOnUninhabited_11_Again";
				}
				else
				{
					rChar.Dialog.currentnode = "PiratesOnUninhabited_43_again";
				}
			}
			
			AddCharacterCrew(PChar, sti(PChar.GenQuest.PiratesOnUninhabited.PiratesCount));
			
			Log_Info("Your crew was increased by " + PChar.GenQuest.PiratesOnUninhabited.PiratesCount + " men.");
			OfficersReaction("bad");
			
			//PChar.Quest.PiratesOnUninhabited_LocExit.over = "yes"; // Снимаем прерывание на выход из локации
			
			//DeleteAttribute(PChar, "GenQuest.PiratesOnUninhabited");
			
			DialogExit();
			
			// Конец квеста
		break;
		
		case "PiratesOnUninhabited_10":
			dialog.text = "Thank you, captain! The loading should not take up too much time. God, how had we prayed for that moment to come!";
			link.l1 = "Very good, then.";
			link.l1.go = "PiratesOnUninhabited_11";
		break;
		
		// Берем их в пассажирами - держать курс на населенный остров
		case "PiratesOnUninhabited_11":
			for(i = 0; i < sti(PChar.GenQuest.PiratesOnUninhabited.PiratesQty); i++)
			{
				rChar = CharacterFromID("PirateOnUninhabited_" + i);
				LAi_SetWarriorTypeNoGroup(rChar);
				rChar.Dialog.currentnode = "PiratesOnUninhabited_11_Again";
			}
			
			Log_Info("Your crew was increased by " + PChar.GenQuest.PiratesOnUninhabited.PiratesCount + " men.");
			
			ChangeCharacterComplexReputation(pchar,"nobility", 3.0);
			
			AddCharacterCrew(PChar, sti(PChar.GenQuest.PiratesOnUninhabited.PiratesCount) - 1);
			OfficersReaction("good");
			PChar.Quest.PiratesOnUninhabited_LocExit.over = "yes"; // Снимаем прерывание на выход из локации
			
			AddPassenger(PChar, NPChar, false); // Главного в пассажиры
			SetCharacterRemovable(NPChar, false);
			
			sTemp = XI_ConvertString(PChar.location + "Dat");
			
			sTitle = "PiratesOnUninhabited" + PChar.location;
			ReOpenQuestHeader(sTitle);
			
			if(!CheckAttribute(PChar, "GenQuest.PiratesOnUninhabited.TreasureMap"))
			{
				if(CheckAttribute(PChar, "GenQuest.PiratesOnUninhabited.Shipwrecked"))
				{
				AddQuestRecordEx(sTitle, "PiratesOnUninhabited", "1");
					AddQuestUserData(sTitle, "shipTypeName", GetStrSmallRegister(XI_ConvertString(ShipsTypes[sti(PChar.GenQuest.PiratesOnUninhabited.StartShipType)].name + "Acc")));
			}
			else
			{
					AddQuestRecordEx(sTitle, "PiratesOnUninhabited", "11");
					AddQuestUserData(sTitle, "pirateName", ChangeNameCase(NAMETYPE_ORIG, PChar.GenQuest.PiratesOnUninhabited.BadPirateName, NAME_ABL));
				}
			}
			else
			{
				AddQuestRecordEx(sTitle, "PiratesOnUninhabited", "5");
				AddQuestUserData(sTitle, "shipTypeName", GetStrSmallRegister(XI_ConvertString(ShipsTypes[sti(PChar.GenQuest.PiratesOnUninhabited.StartShipType)].name + "Acc")));
			}
			
			AddQuestUserDataForTitle(sTitle, "shoreName", sTemp);
			AddQuestUserData(sTitle, "shoreName", sTemp);
			AddQuestUserData(sTitle, "count", PChar.GenQuest.PiratesOnUninhabited.PiratesCount);
			
			PChar.GenQuest.PiratesOnUninhabited.StartShore = PChar.location;
			
			PChar.Quest.PiratesOnUninhabited_LocExitGood.win_condition.l1 = "ExitFromLocation";
			PChar.Quest.PiratesOnUninhabited_LocExitGood.win_condition.l1.location = PChar.location;
			PChar.Quest.PiratesOnUninhabited_LocExitGood.function = "PiratesOnUninhabited_LocationExit_Good";
			
			PChar.Quest.PiratesOnUninhabited_OnShore.win_condition.l1 = "Location_Type";
			PChar.Quest.PiratesOnUninhabited_OnShore.win_condition.l1.location_type = "seashore";
			PChar.Quest.PiratesOnUninhabited_OnShore.again = true;
			PChar.Quest.PiratesOnUninhabited_OnShore.function = "PiratesOnUninhabited_OnShore";
			
			PChar.Quest.PiratesOnUninhabited_OnMayak.win_condition.l1 = "Location_Type";
			PChar.Quest.PiratesOnUninhabited_OnMayak.win_condition.l1.location_type = "mayak";
			PChar.Quest.PiratesOnUninhabited_OnMayak.again = true;
			PChar.Quest.PiratesOnUninhabited_OnMayak.function = "PiratesOnUninhabited_OnShore";
			
			DialogExit();
		break;
		
		case "PiratesOnUninhabited_11_Again":
			dialog.text = LinkRandPhrase("Why are you lingering, captain? Order to weigh anchor.", "We are sorry, captain, but we must get ready for setting sail.", "We are so lucky that you've decided to come here!");
			link.l1 = "Hurry up. The ship will not be waiting for anyone.";
			link.l1.go = "exit";
			NextDiag.TempNode = "PiratesOnUninhabited_11_Again";
		break;
		
		// Базар с главарем уже в другой бухте на обитаемом острове
		case "PiratesOnUninhabited_12":
			if(dRand(1) == 0)
			{
				// Успешное завершение квеста - даст награду
				dialog.text = "Thank you, captain. Indeed, we were right to believe in our luck... Please, accept this emerald - I have found it at that ill-fated cove. I hope it will bring you luck.";
				link.l1 = "I didn't expect such present.";
				link.l1.go = "PiratesOnUninhabited_13";
			}
			else
			{
				// Требуют денег
				dialog.text = "Captain, please, don't think that we're too impudent, but we're really short of money. You know, we've lost everything we had. Could you please lend us a couple handfuls of pesos? We will pay you back for sure... when the opportunity shows itself...";
				link.l1 = "Wow! Indeed, impudence knows no limits. Well, the only thing I could do for you now after everything I've already done - not telling the authorities about you.";
				link.l1.go = "PiratesOnUninhabited_15";
				link.l2 = "You don't say so... And how much do you want?";
				link.l2.go = "PiratesOnUninhabited_17";
			}
			
			RemovePassenger(PChar, NPChar);
			RemoveCharacterCrew(PChar, sti(PChar.GenQuest.PiratesOnUninhabited.PiratesCount) - 1);
		break;
		
		case "PiratesOnUninhabited_13":
			AddItems(PChar, "jewelry4", 1);
			
			for(i = 0; i < sti(PChar.GenQuest.PiratesOnUninhabited.PiratesQty); i++)
			{
				rChar = CharacterFromID("PirateOnUninhabited_" + i);
				LAi_SetWarriorTypeNoGroup(rChar);
				LAi_SetImmortal(rChar, false);
				rChar.LifeDay = 0;
				
				rChar.Dialog.currentnode = "PiratesOnUninhabited_14";
			}
			
			sTitle = "PiratesOnUninhabited" + PChar.GenQuest.PiratesOnUninhabited.StartShore;
			AddQuestRecordEx(sTitle, "PiratesOnUninhabited", "2");
			AddQuestUserData(sTitle, "sSex", GetSexPhrase("","а"));
			AddQuestUserData(sTitle, "toShore", LowerFirst(XI_ConvertString(PChar.location + "Acc")));
			CloseQuestHeader(sTitle);
			
			DeleteAttribute(PChar, "GenQuest.PiratesOnUninhabited");
			
			DialogExit();
			
			// Конец квеста
		break;
		
		case "PiratesOnUninhabited_14":
			dialog.text = LinkRandPhrase("Thank you, captain.", "Captain, we are so thankful to you.", "We will pray for you, captain " + PChar.name + "!");
			link.l1 = "Good luck to you. Farewell...";
			link.l1.go = "exit";
			NextDiag.TempNode = "PiratesOnUninhabited_14";
		break;
		
		case "PiratesOnUninhabited_15":
			dialog.text = "Heh, captain... You know, we got along nicely... It would really be a pity to kill you...";
			link.l1 = "You may try!";
			link.l1.go = "PiratesOnUninhabited_16";
			AddDialogExitQuest("MainHeroFightModeOn");
			ChangeCharacterComplexReputation(pchar,"nobility", 2.0);
		break;
		
		case "PiratesOnUninhabited_16":
			for(i = 0; i < sti(PChar.GenQuest.PiratesOnUninhabited.PiratesQty); i++)
			{
				rChar = CharacterFromID("PirateOnUninhabited_" + i);
				
				LAi_SetImmortal(rChar, false);
				rChar.LifeDay = 0;
			}
			
			LAi_Group_SetRelation("PiratesOnUninhabitedGroup", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_Group_FightGroups("PiratesOnUninhabitedGroup", LAI_GROUP_PLAYER, true);
			
			sTitle = "PiratesOnUninhabited" + PChar.GenQuest.PiratesOnUninhabited.StartShore;
			AddQuestRecordEx(sTitle, "PiratesOnUninhabited", "3");
			AddQuestUserData(sTitle, "sSex", GetSexPhrase("",""));
			AddQuestUserData(sTitle, "toShore", LowerFirst(XI_ConvertString(PChar.location + "Acc")));
			CloseQuestHeader(sTitle);
			
			DeleteAttribute(PChar, "GenQuest.PiratesOnUninhabited");
			
			DialogExit();
			
			// Конец квеста
		break;
		
		case "PiratesOnUninhabited_17":
			iMoney = sti(PChar.rank) * 500;
			PChar.GenQuest.PiratesOnUninhabited.Money = iMoney * sti(PChar.GenQuest.PiratesOnUninhabited.PiratesCount);
			
			dialog.text = "Well, say, " + iMoney + " pesos to each of us would do nicely... Of course, if you don't think that this compensation for all our pain and suffering is too small, he-he...";
			link.l1 = RandPhraseSimple("On the contrary, I am certain that it's way too much... A noose on the neck for every one of you would be best.", "I will hang you like apes on palms for such money by myself!");
			link.l1.go = "PiratesOnUninhabited_18";
			
			if(sti(PChar.money) >= iMoney * sti(PChar.GenQuest.PiratesOnUninhabited.PiratesCount))
			{
				link.l2 = "Alright, take it. I do hope I don't owe you anything else?";
				link.l2.go = "PiratesOnUninhabited_19";
			}
		break;
		
		case "PiratesOnUninhabited_18":
			dialog.text = "What generosity! Frankly, I was thinking that you already had a chance to see that we are always getting what we desire. And this time we aren't going to step back, either...";
			link.l1 = "You may try!";
			link.l1.go = "PiratesOnUninhabited_16";
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "PiratesOnUninhabited_19":
			dialog.text = "Oh no, captain, what are you saying?! We will definitely light a candle in your name - if we ever get to a church...";
			link.l1 = "I hope so...";
			link.l1.go = "PiratesOnUninhabited_20";
			
			iMoney = sti(PChar.GenQuest.PiratesOnUninhabited.Money);
			
			AddMoneyToCharacter(PChar, -iMoney);
			AddMoneyToCharacter(NPChar, iMoney);
		break;
		
		case "PiratesOnUninhabited_20":
			for(i = 0; i < sti(PChar.GenQuest.PiratesOnUninhabited.PiratesQty); i++)
			{
				rChar = CharacterFromID("PirateOnUninhabited_" + i);
				
				LAi_SetWarriorTypeNoGroup(rChar);
				LAi_CharacterDisableDialog(rChar);
				LAi_SetImmortal(rChar, false);
				rChar.LifeDay = 0;
			}
			
			ChangeCharacterComplexReputation(pchar,"nobility", 2.0);
			OfficersReaction("good");
			
			sTitle = "PiratesOnUninhabited" + PChar.GenQuest.PiratesOnUninhabited.StartShore;
			AddQuestRecordEx(sTitle, "PiratesOnUninhabited", "4");
			AddQuestUserData(sTitle, "sSex", GetSexPhrase("","а"));
			AddQuestUserData(sTitle, "sSex1", GetSexPhrase("",""));
			AddQuestUserData(sTitle, "toShore", LowerFirst(XI_ConvertString(PChar.location + "Acc")));
			CloseQuestHeader(sTitle);
			
			NPChar.SaveItemsForDead = true; // сохранять на трупе вещи
			NPChar.DontClearDead = true;  // не убирать труп через 200с
			
			DeleteAttribute(PChar, "GenQuest.PiratesOnUninhabited");
			
			DialogExit();
			
			// Конец квеста
		break;
		
		case "PiratesOnUninhabited_21":
			if(GetFreeCrewQuantity(PChar) >= sti(PChar.GenQuest.PiratesOnUninhabited.PiratesCount))
			{
				// Игрок врет - свободное место есть
				dialog.text = "Oh no, captain, what are you saying?! We will definitely light a candle in your name - if we ever get to a church...";
				link.l1 = "I hope so...";
				link.l1.go = "PiratesOnUninhabited_23";
			}
			else
			{
				dialog.text = "Heh, captain, you know, that's not much of a problem. Me and my boys are willing to free a dozen hammocks on your ship from those who are currently occupying them...";
				link.l1 = "Hmm... that sounds like a threat...";
				link.l1.go = "PiratesOnUninhabited_22";
			}
		break;
		
		case "PiratesOnUninhabited_22":
			dialog.text = "Well, actually, it is a threat. I need your ship, and I will get out of this place - with your consent or without it!";
			link.l1 = "Well, now I can finally see you for what you actually are...";
			link.l1.go = "PiratesOnUninhabited_2";
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "PiratesOnUninhabited_23":
			dialog.text = "I understand you, captain. I perfectly understand you... Who would want to be nursing poor pirates, who had been asking for a noose?.. But... what if I offer you an exchange? You deliver us to any cove on an inhabited island or in the Main, and I give you a treasure map for it. Deal?";
			link.l1 = "Hmm... And how can you guarantee that this map is not a forgery?";
			link.l1.go = "PiratesOnUninhabited_25";
			link.l2 = "Ha, I am sure that your map costs as much as the piece of paper it's drawn at...";
			link.l2.go = "PiratesOnUninhabited_24";
		break;
		
		case "PiratesOnUninhabited_24":
			dialog.text = "Well... You leave us without a choice... Still, we are going to get out of this place anyway - with your consent or without it!";
			link.l1 = "Well, now I can finally see you for what you actually are...";
			link.l1.go = "PiratesOnUninhabited_2";
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "PiratesOnUninhabited_25":
			dialog.text = "And how you can guarantee that you do not turn us in to the authorities in the nearest port? We both are playing without seeing each other's cards...";
			link.l1 = "Alright, you have a deal.";
			link.l1.go = "PiratesOnUninhabited_11";
			PChar.GenQuest.PiratesOnUninhabited.TreasureMap = true;
		break;
		
		// Базар с главарем уже в другой бухте на обитаемом острове. Вариант, когда нам обещали карту сокровищ
		case "PiratesOnUninhabited_26":
			// PChar.GenQuest.PiratesOnUninhabited.MainPirateName - имя в родительном падеже
			
			dialog.text = "Thank you, captain " + PChar.name + ". You have fulfilled"+ GetSexPhrase("","а") +" your decision, it's time " + ChangeNameCase(NAMETYPE_NICK, PChar.GenQuest.PiratesOnUninhabited.MainPirateName, NAME_DAT) + " to fulfill mine. I don't have the map with me, but I will tell you where the treasure is. Go to the cove...";
			link.l1 = "Oh, so that's how you put it now! I see you were going to trick me right from the start...";
			link.l1.go = "PiratesOnUninhabited_27";
			link.l2 = "I knew right away that you couldn't' be trusted...";
			link.l2.go = "PiratesOnUninhabited_30";
			link.l3 = "That's what happens when you trust a pirate. What kind of people are you? Nothing is sacred to you!";
			link.l3.go = "PiratesOnUninhabited_33";
			
			RemovePassenger(PChar, NPChar);
			RemoveCharacterCrew(PChar, sti(PChar.GenQuest.PiratesOnUninhabited.PiratesCount) - 1);
		break;
		
		case "PiratesOnUninhabited_27":
			dialog.text = "Don't make a fuss... I am no saint, but I keep my word!";
			link.l1 = "And you expect me to believe you once again - so that tomorrow the entire archipelago would make fun of me?";
			link.l1.go = "PiratesOnUninhabited_28";
		break;
		
		case "PiratesOnUninhabited_28":
			dialog.text = "Hmm... Apparently, there will not be a peaceful resolution. But, God knows, I didn't want it...";
			link.l1 = "Unsheathe your blade - or I'll crush you like a rat you are!";
			link.l1.go = "PiratesOnUninhabited_29";
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "PiratesOnUninhabited_29":
			for(i = 0; i < sti(PChar.GenQuest.PiratesOnUninhabited.PiratesQty); i++)
			{
				rChar = CharacterFromID("PirateOnUninhabited_" + i);
				
				LAi_SetImmortal(rChar, false);
				rChar.LifeDay = 0;
			}
			
			LAi_Group_SetRelation("PiratesOnUninhabitedGroup", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_Group_FightGroups("PiratesOnUninhabitedGroup", LAI_GROUP_PLAYER, true);
			
			sTitle = "PiratesOnUninhabited" + PChar.GenQuest.PiratesOnUninhabited.StartShore;
			AddQuestRecordEx(sTitle, "PiratesOnUninhabited", "6");
			CloseQuestHeader(sTitle);
			
			DeleteAttribute(PChar, "GenQuest.PiratesOnUninhabited");
			
			DialogExit();
			
			// Конец квеста
		break;
		
		case "PiratesOnUninhabited_30":
			sTitle = PiratesOnUninhabited_GenerateTreasureShore(&sTemp);
			PChar.GenQuest.PiratesOnUninhabited.TreasureShore = sTitle;
			PChar.GenQuest.PiratesOnUninhabited.TreasureBox = sTemp;
			
			dialog.text = "And what else could I have done? Stay in that stinky puddle with my boys and rot to death? You better hear me out..." + XI_ConvertString(sTitle + "Dat") + " captain " + ChangeNameCase(NAMETYPE_ORIG, PChar.GenQuest.PiratesOnUninhabited.BadPirateName, NAME_GEN) + " there is a cache where he is keeping his loot. But be careful"+ GetSexPhrase("","") +", he is frequently visiting there. Finding the cache will not be hard, if you keep your wits with you...";
			link.l1 = "And you expect me to believe you once again - so that tomorrow the entire archipelago would make fun of me?";
			link.l1.go = "PiratesOnUninhabited_28";
			link.l2 = "Alright. But if you put me on one more time - I'll find you.";
			link.l2.go = "PiratesOnUninhabited_31";
		break;
		
		case "PiratesOnUninhabited_31":
			for(i = 0; i < sti(PChar.GenQuest.PiratesOnUninhabited.PiratesQty); i++)
			{
				rChar = CharacterFromID("PirateOnUninhabited_" + i);
				
				LAi_SetWarriorTypeNoGroup(rChar);
				LAi_SetImmortal(rChar, false);
				rChar.LifeDay = 0;
				rChar.Dialog.currentnode = "PiratesOnUninhabited_32";
			}
			
			sTitle = "PiratesOnUninhabited" + PChar.GenQuest.PiratesOnUninhabited.StartShore;
			AddQuestRecordEx(sTitle, "PiratesOnUninhabited", "7");
			AddQuestUserData(sTitle, "capName", ChangeNameCase(NAMETYPE_ORIG, PChar.GenQuest.PiratesOnUninhabited.BadPirateName, NAME_NOM));
			AddQuestUserData(sTitle, "toShore", LowerFirst(XI_ConvertString(PChar.GenQuest.PiratesOnUninhabited.TreasureShore + "Acc")));
			
			// Таймер для клада. По прошествии 10 дней в кладе будут всякие бакланы и т.д.
			PChar.Quest.PiratesOnUninhabited_TreasureLose.win_condition.l1 = "Timer";
			PChar.Quest.PiratesOnUninhabited_TreasureLose.win_condition.l1.date.day = GetAddingDataDay(0, 0, 10);
			PChar.Quest.PiratesOnUninhabited_TreasureLose.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 10);
			PChar.Quest.PiratesOnUninhabited_TreasureLose.win_condition.l1.date.year = GetAddingDataYear(0, 0, 10);
			PChar.Quest.PiratesOnUninhabited_TreasureLose.win_condition = "PiratesOnUninhabited_TreasureLose";
			
			PChar.Quest.PiratesOnUninhabited_InTreasureLoc.win_condition.l1 = "Location";
			PChar.Quest.PiratesOnUninhabited_InTreasureLoc.win_condition.l1.Location = PChar.GenQuest.PiratesOnUninhabited.TreasureShore;
			PChar.Quest.PiratesOnUninhabited_InTreasureLoc.function = "PiratesOnUninhabited_InTreasureLoc";
			
			DialogExit();
			
			// Курс в бухту, которую назвал пират. У нас сроку 10 дней, котом клад пропадет
		break;
		
		case "PiratesOnUninhabited_32":
			sTemp = ChangeNameCase(NAMETYPE_NICK, PChar.GenQuest.PiratesOnUninhabited.MainPirateName, NAME_ACC);
			
			dialog.text = LinkRandPhrase("Listen to " + sTemp + ", he's talking sense.", "Don't be angry with " + sTemp + ", he simply had no other choice.", "Thank you, captain.");
			link.l1 = "Good luck to you...";
			link.l1.go = "exit";
			NextDiag.TempNode = "PiratesOnUninhabited_32";
		break;
		
		case "PiratesOnUninhabited_33":
			sTitle = PiratesOnUninhabited_GenerateTreasureShore(&sTemp);
			PChar.GenQuest.PiratesOnUninhabited.TreasureShore = sTitle;
			PChar.GenQuest.PiratesOnUninhabited.TreasureBox = sTemp;
			
			dialog.text = "And what else could I have done? Stay in that stinky puddle with my boys and rot to death? You better hear me out..." + XI_ConvertString(sTitle + "Dat") + " captain " + ChangeNameCase(NAMETYPE_ORIG, PChar.GenQuest.PiratesOnUninhabited.BadPirateName, NAME_GEN) + " there is a cache where he is keeping his loot. But be careful, he is frequently visiting there. Finding the cache will not be hard, if you keep your wits with you...";
			link.l1 = "And you expect me to believe you once again - so that tomorrow the entire archipelago would make fun of me?";
			link.l1.go = "PiratesOnUninhabited_28";
		break;
		
		// Пираты в бухте с сокровищем
		case "PiratesOnUninhabited_34":
			dialog.text = "Who are you,"+ GetSexPhrase(" buddy"," lass") +"? And what has brought you to this deserted place?";
			link.l1 = "I stopped to replenish my supply of fresh water.";
			link.l1.go = "PiratesOnUninhabited_35";
			link.l2 = "I am here on behalf of " + ChangeNameCase(NAMETYPE_NICK, PChar.GenQuest.PiratesOnUninhabited.MainPirateName, NAME_GEN) + ".";
			link.l2.go = "PiratesOnUninhabited_38";
			NextDiag.TempNode = "PiratesOnUninhabited_34";
		break;
		
		case "PiratesOnUninhabited_35":
			dialog.text = "You've picked a poor place for that... Fine, take your time.";
			link.l1 = "A-ha...";
			link.l1.go = "exit";
			link.l2 = "And who are you to tell me what to do?";
			link.l2.go = "PiratesOnUninhabited_36";
		break;
		
		case "PiratesOnUninhabited_36":
			dialog.text = "I am telling everyone what to do. And those who think themselves too smart will be hanging on the palm tree.";
			link.l1 = "I'll cut your tongue, cur.";
			link.l1.go = "PiratesOnUninhabited_37";
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "PiratesOnUninhabited_37":
			DialogExit();
			LAi_Group_SetRelation("PiratesOnUninhabited_ShoreGroup", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
		break;
		
		case "PiratesOnUninhabited_38":
			dialog.text = "And why didn't he come by himself?";
			link.l1 = "He didn't want to, stayed at " + LowerFirst(XI_ConvertString(PChar.GenQuest.PiratesOnUninhabited.StartShore + "Dat")) + " and waiting for me.";
			link.l1.go = "PiratesOnUninhabited_39";
		break;
		
		case "PiratesOnUninhabited_39":
			dialog.text = "That old scoundrel! He tries to put us on once again, doesn't he? That won't do. Tell him that he can collect the money only together with us!";
			link.l1 = "He told me to not come back without money and not take anyone on board...";
			link.l1.go = "PiratesOnUninhabited_40";
		break;
		
		case "PiratesOnUninhabited_40":
			dialog.text = "Well, if you trust him so much, you can stay here. But we will take your ship, your money and head to " + LowerFirst(XI_ConvertString(PChar.GenQuest.PiratesOnUninhabited.StartShore + "Acc")) + ". We're dying to look at the face of " + PChar.GenQuest.PiratesOnUninhabited.MainPirateName + ".";
			link.l1 = "If you miss him so much, you can swim there... or you can die here.";
			link.l1.go = "PiratesOnUninhabited_37";
			AddDialogExitQuest("MainHeroFightModeOn");
			PChar.GenQuest.PiratesOnUninhabited.UseMainPiratename = true;
		break;
		
		// Ветка из PiratesOnUninhabited_3
		case "PiratesOnUninhabited_41":
			iBanditsCount = 5 + dRand(5);
			iMoney = GetFreeCrewQuantity(PChar);
			
			PChar.GenQuest.PiratesOnUninhabited.PiratesCount = iBanditsCount;
			
			dialog.text = "You are a shrewd person. But allow me to assure you that our conflict with captain " + ChangeNameCase(NAMETYPE_ORIG, PChar.GenQuest.PiratesOnUninhabited.BadPirateName, NAME_ABL) + " is purely of ideological nature. I have warned him, that his dirty operations would be punished one day and now me and my  " + iBanditsCount + " buddies are suffering because of our love for God and justice.";
			link.l1 = "How so... I bet you were the actual instigators of the mutiny - and you've got what you deserved.";
			link.l1.go = "PiratesOnUninhabited_42";
			
			if(iMoney >= iBanditsCount - 1 && GetPassengersQuantity(PChar) < PASSENGERS_MAX)
			{
				link.l2 = "Of course... It'd be nice though to hear the opinion of captain " + ChangeNameCase(NAMETYPE_ORIG, PChar.GenQuest.PiratesOnUninhabited.BadPirateName, NAME_GEN) + " himself regarding your disagreements.";
				link.l2.go = "PiratesOnUninhabited_44";
			}
		break;
		
		case "PiratesOnUninhabited_42":
			dialog.text = "Captain, why would you offend honest people with your distrust? Just look at their faces - do you really think they are mutineers? They are as humble as men can get... But they are second to none in a fight for just cause under good command! I can personally vouch for each and every one of them.";
			link.l1 = "Alright, but what shall I do with you now?";
			link.l1.go = "PiratesOnUninhabited_43";
		break;
		
		case "PiratesOnUninhabited_43":
			iBanditsCount = sti(PChar.GenQuest.PiratesOnUninhabited.PiratesCount);
			iMoney = GetFreeCrewQuantity(PChar);
			
			dialog.text = "Whatever you desire. It's up to you - bring us to a settlement or accept us into your crew.";
			
			if(iMoney >= iBanditsCount)
			{
				link.l1 = "Alright, I'll take you into my crew. But no fooling around! I have strict discipline on my ship!";
				link.l1.go = "PiratesOnUninhabited_9"; // Берем в команду
			}
			
			link.l2 = "I am not taking you anywhere. I already have enough thugs in my crew.";
			link.l2.go = "PiratesOnUninhabited_24"; // Рубилово и конец квеста
			
			if(iMoney >= iBanditsCount - 1 && GetPassengersQuantity(PChar) < PASSENGERS_MAX)
			{
				link.l3 = "Alright, get into the boat, I'll take you somewhere.";
				link.l3.go = "PiratesOnUninhabited_11"; // В пассажиры и на остров
			}
		break;
		
		case "PiratesOnUninhabited_43_again":
			dialog.text = LinkRandPhrase("I swear, captain, you won't regret it.", "You've made the right choice, captain.", "Captain, rest assured that you were in luck as much as ourselves!");
			link.l1 = RandPhraseSimple("I hope so.", "Hurry up. The ship will not be waiting for anyone.");
			link.l1.go = "exit";
			NextDiag.TempNode = "PiratesOnUninhabited_43_again";
		break;
		
		case "PiratesOnUninhabited_44":
			sTitle = GenerateRandomNameToShip(PIRATE);
			PChar.GenQuest.PiratesOnUninhabited.StartShipName = sTitle;
			
			dialog.text = "That can be easily arranged. He sails on  " + GetStrSmallRegister(XI_ConvertString(ShipsTypes[sti(PChar.GenQuest.PiratesOnUninhabited.StartShipType)].Name + "Dat")) + " '" + sTitle + " and is dealing in slave trade... Let's do it this way: if we find him, you get the cargo - we get the ship. Oh, and you can also ask him, whether he knows about " + ChangeNameCase(NAMETYPE_NICK, PChar.GenQuest.PiratesOnUninhabited.MainPirateName, NAME_ACC) + ". I hope he doesn't poop his pants when he hears that name - because it's my ship...";
			link.l1 = "Alright, you have a deal.";
			link.l1.go = "PiratesOnUninhabited_45";
		break;
		
		case "PiratesOnUninhabited_45":
			for(i = 0; i < sti(PChar.GenQuest.PiratesOnUninhabited.PiratesQty); i++)
			{
				rChar = CharacterFromID("PirateOnUninhabited_" + i);
				LAi_SetWarriorTypeNoGroup(rChar);
				rChar.Dialog.currentnode = "PiratesOnUninhabited_11_Again";
				NPChar.location = "none"; // Убираем из локации при выходе
				NPChar.location.locator = "";
			}
			
			Log_Info("Your crew was increased by " + PChar.GenQuest.PiratesOnUninhabited.PiratesCount + " men.");
			
			ChangeCharacterComplexReputation(pchar,"nobility", 3.0);
			
			AddCharacterCrew(PChar, sti(PChar.GenQuest.PiratesOnUninhabited.PiratesCount) - 1)
			AddPassenger(PChar, NPChar, false); // Главного в пассажиры
			SetCharacterRemovable(NPChar, false);
			
			PChar.Quest.PiratesOnUninhabited_LocExit.over = "yes"; // Снимаем прерывание на выход из локации
			
			sTemp = XI_ConvertString(PChar.location + "Dat");
			
			sTitle = "PiratesOnUninhabited" + PChar.location;
			ReOpenQuestHeader(sTitle);
			AddQuestRecordEx(sTitle, "PiratesOnUninhabited", "13");
			AddQuestUserDataForTitle(sTitle, "shoreName", sTemp);
			AddQuestUserData(sTitle, "shoreName", sTemp);
			AddQuestUserData(sTitle, "count", PChar.GenQuest.PiratesOnUninhabited.PiratesCount);
			AddQuestUserData(sTitle, "badCapName", ChangeNameCase(NAMETYPE_ORIG, PChar.GenQuest.PiratesOnUninhabited.BadPirateName, NAME_ABL));
			AddQuestUserData(sTitle, "ship", GetStrSmallRegister(XI_ConvertString(ShipsTypes[sti(PChar.GenQuest.PiratesOnUninhabited.StartShipType)].name + "Dat")) + " '" + PChar.GenQuest.PiratesOnUninhabited.StartShipName + "'");
			
			PChar.GenQuest.PiratesOnUninhabited.StartShore = PChar.location;
			
			PiratesOnUninhabited_SetCapToMap(); // Ставим корабль на карту
			
			DialogExit();
		break;
		
		// Диалог с кэпом в каюте
		case "PiratesOnUninhabited_46":
			dialog.text = "What the hell do you want from me?";
			link.l1 = "I came to say hi on behalf of " + ChangeNameCase(NAMETYPE_NICK, PChar.GenQuest.PiratesOnUninhabited.MainPirateName, NAME_GEN) + ". I take it you know him?";
			link.l1.go = "PiratesOnUninhabited_47";
			
			PChar.Quest.PiratesOnUninhabited_ShipSink.over = "yes";
			PChar.GenQuest.PiratesOnUninhabited.ClearShip = true;
			Map_ReleaseQuestEncounter("PiratesOnUninhabited_BadPirate"); // Убираем с глобалки
		break;
		
		case "PiratesOnUninhabited_47":
			dialog.text = "It's a pity I didn't strangle that scoundrel before. Well, then I guess time has come to pay for my benevolence...";
			link.l1 = "Indeed... And this time has just run out...";
			link.l1.go = "PiratesOnUninhabited_48";
		break;
		
		case "PiratesOnUninhabited_48":
			LAi_CharacterDisableDialog(NPChar);
			LAi_Group_Attack(NPChar, Pchar);
			
			LAi_SetCurHPMax(NPChar);
			QuestAboardCabinDialogFree(); // важный метод
			
			LAi_Group_SetRelation(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_Group_FightGroups(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, true);
			LAi_Group_SetCheckFunction(LAI_GROUP_BRDENEMY, "PiratesOnUninhabited_CapDeath");
			
			AddDialogExitQuest("MainHeroFightModeOn");
			
			DialogExit();
		break;
		
		case "PiratesOnUninhabited_49":
			dialog.text = "Great job, captain! Everything as we agreed, then? We get the ship and you get the cargo?";
			link.l1 = "Sure. Take the ship and make good use of it.";
			link.l1.go = "PiratesOnUninhabited_50";
		break;
		
		case "PiratesOnUninhabited_50":
			NPChar.LifeDay = 0;
			NPChar.location = "none"; // Убираем из каюты
			NPChar.location.locator = "";
			
			RemovePassenger(PChar, NPChar);
			RemoveCharacterCrew(PChar, sti(PChar.GenQuest.PiratesOnUninhabited.PiratesCount) - 1);
			
			sTitle = "PiratesOnUninhabited" + PChar.GenQuest.PiratesOnUninhabited.StartShore;
			AddQuestRecordEx(sTitle, "PiratesOnUninhabited", "14");
			AddQuestUserData(sTitle, "ship", GetStrSmallRegister(XI_ConvertString(ShipsTypes[sti(PChar.GenQuest.PiratesOnUninhabited.StartShipType)].name)) + " '" + PChar.GenQuest.PiratesOnUninhabited.StartShipName + "'");
			CloseQuestHeader(sTitle);
			
			DeleteAttribute(PChar, "GenQuest.PiratesOnUninhabited");
			
			ChangeAttributesFromCharacter(CharacterFromID("PiratesOnUninhabited_BadPirate"), NPChar, true);
			DialogExit();
			
		break;
		
		// На палубе, когда корабль с нашим пиратом отпустили
		case "PiratesOnUninhabited_50_Deck1":
			dialog.text = "I greet you, captain " + PChar.name + ".";
			link.l1 = "So, how do you like your ship?";
			link.l1.go = "PiratesOnUninhabited_50_Deck2";
		break;
		
		case "PiratesOnUninhabited_50_Deck2":
			dialog.text = "Heh - it's squeaking and creaking, just as myself. I think we both have got not much time left to sail the high seas...";
			link.l1 = "Good luck, then...";
			link.l1.go = "exit";
			NextDiag.TempNode = "PiratesOnUninhabited_50_Deck1";
		break;
		
		// В бухте, вариант, когда корабль, который нужно было захватить, утопили
		case "PiratesOnUninhabited_51":
			dialog.text = "Why have you sunk my ship?! Do you remember the deal?";
			link.l1 = "What, I didn't want him to sink me instead. Can't you see that I barely made it?";
			link.l1.go = "PiratesOnUninhabited_52";
		break;
		
		case "PiratesOnUninhabited_52":
			if(dRand(1) == 1)
			{
				dialog.text = "Who fights like that? You have lost such a ship! What the hell kid like yourself is doing here?";
				link.l1 = "I'll cut your tongue, cur.";
				link.l1.go = "PiratesOnUninhabited_53";
			}
			else
			{
				iMoney = sti(ShipsTypes[sti(PChar.GenQuest.PiratesOnUninhabited.StartShipType)].Price);
				iMoney = MakeInt((iMoney / 1.2 + dRand(iMoney - (iMoney / 1.2))) * 1.2);
				dialog.text = "Who fights like that? You have lost such a ship! Do you have any idea how much did it cost to me? " + FindRussianMoneyString(iMoney) + "! You owe me now...";
				link.l1 = "Wouldn't it bee too much for you? Don't forget that I have already done you one favor.";
				link.l1.go = "PiratesOnUninhabited_54";
				
				if(sti(PChar.money) >= iMoney)
				{
					link.l2 = "God damn you with that accursed ship! Take your money and don't fall under my eye anymore!";
					link.l2.go = "PiratesOnUninhabited_55";
				}
			}
		break;
		
		case "PiratesOnUninhabited_53":
			for(i = 0; i < sti(PChar.GenQuest.PiratesOnUninhabited.PiratesQty); i++)
			{
				rChar = CharacterFromID("PirateOnUninhabited_" + i);
				LAi_SetImmortal(rChar, false);
				rChar.LifeDay = 0;
			}
			
			LAi_Group_SetRelation("PiratesOnUninhabitedGroup", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_Group_FightGroups("PiratesOnUninhabitedGroup", LAI_GROUP_PLAYER, true);
			
			sTitle = "PiratesOnUninhabited" + PChar.GenQuest.PiratesOnUninhabited.StartShore;
			AddQuestRecordEx(sTitle, "PiratesOnUninhabited", "15");
			AddQuestUserData(sTitle, "ship", GetStrSmallRegister(XI_ConvertString(ShipsTypes[sti(PChar.GenQuest.PiratesOnUninhabited.StartShipType)].name)) + " '" + PChar.GenQuest.PiratesOnUninhabited.StartShipName + "'");
			CloseQuestHeader(sTitle);
			
			DeleteAttribute(PChar, "GenQuest.PiratesOnUninhabited");
			
			AddDialogExitQuest("MainHeroFightModeOn");
			
			DialogExit();
		break;
		
		case "PiratesOnUninhabited_54":
			dialog.text = "And what good is that favor to me now?! If captain " + ChangeNameCase(NAMETYPE_ORIG, PChar.GenQuest.PiratesOnUninhabited.BadPirateName, NAME_NOM) + " is on the seabed now with my ship! Now I neither get my share, nor my ship back! What a fate - to die in the gutter, like a vagrant!!!";
			link.l1 = "But why? I can arrange a spectacular funeral for you. Right here, if that's fine with you...";
			link.l1.go = "PiratesOnUninhabited_53";
		break;
		
		case "PiratesOnUninhabited_55":
			for(i = 0; i < sti(PChar.GenQuest.PiratesOnUninhabited.PiratesQty); i++)
			{
				rChar = CharacterFromID("PirateOnUninhabited_" + i);
				LAi_SetWarriorTypeNoGroup(rChar);
				LAi_SetImmortal(rChar, false);
				LAi_CharacterDisableDialog(rChar);
				rChar.LifeDay = 0;
			}
			
			sTitle = "PiratesOnUninhabited" + PChar.GenQuest.PiratesOnUninhabited.StartShore;
			AddQuestRecordEx(sTitle, "PiratesOnUninhabited", "16");
			AddQuestUserData(sTitle, "sSex", GetSexPhrase("",""));
			AddQuestUserData(sTitle, "ship", GetStrSmallRegister(XI_ConvertString(ShipsTypes[sti(PChar.GenQuest.PiratesOnUninhabited.StartShipType)].name)) + " '" + PChar.GenQuest.PiratesOnUninhabited.StartShipName + "'");
			CloseQuestHeader(sTitle);
			
			DeleteAttribute(PChar, "GenQuest.PiratesOnUninhabited");
			
			DialogExit();
		break;
		
		// КОНЕЦ
		
		// Warship, 15.05.11. Генер "Justice for sale".
		case "JusticeOnSale_1":
			dialog.text = "I thought we might... come to an agreement, perhaps? If you do us a favor, we'll repay it, he-he.";
			link.l1 = "A favor? And what's the deal and what are you offering in return?";
			link.l1.go = "JusticeOnSale_3";
		break;
		
		case "JusticeOnSale_2":
			LAi_Group_SetRelation("JusticeOnSaleGroup_" + LoadedLocation.index, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_Group_FightGroups("JusticeOnSaleGroup_" + LoadedLocation.index, LAI_GROUP_PLAYER, true);
			
			DialogExit();
			LAi_SetFightMode(PChar, true);
		break;
		
		case "JusticeOnSale_3":
			dialog.text = "Our captain " + PChar.GenQuest.JusticeOnSale.SmugglerName + " was caught by the local patrol of  " + XI_ConvertString("Colony" + PChar.GenQuest.JusticeOnSale.CityId) + ". They have him imprisoned but they don't have enough evidence to hang him. We can't drag him out ourselves\n" +
				"You are a respected man. Folks know you. Perhaps, you could negotiate, bail out or simply buy him out? Trust us, we will leave the island as soon as we have our man, so your renown will not suffer!";
			link.l1 = "Let's say that I can help you. But what about my payment?";
			link.l1.go = "JusticeOnSale_4";
			link.l2 = "Go to hell, devilish spawn! I will have no dealings with you!";
			link.l2.go = "JusticeOnSale_5";
		break;
		
		case "JusticeOnSale_4":
			dialog.text = "Would you like several Indian trinkets and talismans? They are rather rare... Or do you prefer cash on the nail? Several thousand pesos, I say?";
			link.l1 = "Go to hell, devilish spawn! I will have no dealings with you!";
			link.l1.go = "JusticeOnSale_5";
			link.l2 = "I am interested in Indian trinkets. I guess I'll agree.";
			link.l2.go = "JusticeOnSale_6";
			link.l3 = "Cash is sailor's best friend. Money has no smell, as we all know. I agree.";
			link.l3.go = "JusticeOnSale_7";
		break;
		
		case "JusticeOnSale_5":
			for(i = 0; i < sti(PChar.GenQuest.JusticeOnSale.EncQty); i++)
			{
				rChar = CharacterFromID("JusticeOnSale_Jungle_" + i);
				LAi_CharacterDisableDialog(rChar);
			}
			DialogExit();
		break;
		
		case "JusticeOnSale_6":
			PChar.GenQuest.JusticeOnSale.ShipName = GenerateRandomNameToShip(PIRATE);
			PChar.GenQuest.JusticeOnSale.ShipType = PiratesOnUninhabited_GenerateShipType();
			PChar.GenQuest.JusticeOnSale.RewardType = 0; // Подрякушки.
			dialog.text = "Thank you, cap. We will compensate you the sum of the bail in addition to your reward. I guess you should talk to the commandant about our captain. Perhaps, you'll be able to persuade him. Once you get him out, come to " + XI_ConvertString(PChar.GenQuest.JusticeOnSale.ShoreId + "Acc") + ", that's where our ship has dropped an anchor - " + LowerFirst(XI_ConvertString(ShipsTypes[sti(PChar.GenQuest.JusticeOnSale.ShipType)].name)) + " '" + PChar.GenQuest.JusticeOnSale.ShipName + "'. We will be waiting for you on the shore.";
			link.l1 = "...";
			link.l1.go = "JusticeOnSale_8";
		break;
		
		case "JusticeOnSale_7":
			PChar.GenQuest.JusticeOnSale.ShipName = GenerateRandomNameToShip(PIRATE);
			PChar.GenQuest.JusticeOnSale.ShipType = PiratesOnUninhabited_GenerateShipType();
			PChar.GenQuest.JusticeOnSale.RewardType = 1; // Монеты.
			
			dialog.text = "Thank you, cap. We will compensate you the sum of the bail in addition to your reward. I guess you should talk to the commandant about our captain. Perhaps, you'll be able to persuade him. Once you get him out, come to " + XI_ConvertString(PChar.GenQuest.JusticeOnSale.ShoreId + "Acc") + ", that's where our ship has dropped an anchor - " + LowerFirst(XI_ConvertString(ShipsTypes[sti(PChar.GenQuest.JusticeOnSale.ShipType)].name)) + " '" + PChar.GenQuest.JusticeOnSale.ShipName + ". We will be waiting for you on the shore.";
			link.l1 = "...";
			link.l1.go = "JusticeOnSale_8";
		break;
		
		case "JusticeOnSale_8":
			for(i = 0; i < sti(PChar.GenQuest.JusticeOnSale.EncQty); i++)
			{
				rChar = CharacterFromID("JusticeOnSale_Jungle_" + i);
				LAi_CharacterDisableDialog(rChar);
			}
			ReOpenQuestHeader("JusticeOnSale");
			AddQuestRecord("JusticeOnSale", "1");
			AddQuestUserData("JusticeOnSale", "cityName", XI_ConvertString("Colony" + PChar.GenQuest.JusticeOnSale.CityId));
			PChar.GenQuest.JusticeOnSale.MayorWait = true;
			PChar.GenQuest.JusticeOnSale.PrisonWait = true;
			
			DialogExit();
		break;
		
		case "JusticeOnSale_9":
			if(dRand(1) == 0)
			{
				if(sti(PChar.GenQuest.JusticeOnSale.RewardType) == 0)
				{
					// Награда побрякушками.
					dialog.text = "We're here, captain! You did a great job tricking these pot-bellied bureaucrats! Here's your reward. Boys, fetch the trinkets!";
				}
				else
				{
					// Награда золотом.
					dialog.text = "We're here, captain! You did a great job tricking these pot-bellied bureaucrats! Here's your reward. Boys, fetch the chest!";
				}
				
				link.l1 = "Give me my share and get lost!";
				link.l1.go = "JusticeOnSale_10";
			}
			else
			{
				// Массакра.
				dialog.text = "We're there, captain! I see that you've arranged it all nicely. But you see... we don't need any witnesses, so... Let's thank the captain, boys!";
				link.l1 = RandSwear() + "I should have shot you right when I had met you!";
				link.l1.go = "JusticeOnSale_11";
			}
			chrDisableReloadToLocation = false;
		break;
		
		case "JusticeOnSale_10":
			DialogExit();
			if(sti(PChar.GenQuest.JusticeOnSale.RewardType) == 0)
			{
				if(CheckAttribute(PChar, "GenQuest.JusticeOnSale.PrisonMoney"))
				{
					AddItems(PChar, "indian_"+(1+dRand(10)), 1);
				}
				else
				{
					AddItems(PChar, "obereg_"+(1+dRand(10)), 1);
				}
			}
			else
			{
				if(CheckAttribute(PChar, "GenQuest.JusticeOnSale.PrisonMoney"))
				{
					AddMoneyToCharacter(PChar, sti(PChar.rank) * 700 + dRand(2000));
				}
				else
				{
					AddMoneyToCharacter(PChar, sti(PChar.rank) * 500 + dRand(1000));
				}
			}
			for(i = 0; i < sti(PChar.GenQuest.JusticeOnSale.EncQty); i++)
			{
				rChar = CharacterFromID("JusticeOnSale_ShorePirate_" + i);
				LAi_Type_Actor_Reset(rChar);
				LAi_ActorGoToLocation(rChar, "reload", LAi_FindNearestFreeLocator2Pchar("reload"), "none", "", "", "", 3.0);
			}
			AddQuestRecord("JusticeOnSale", "3");
			CloseQuestHeader("JusticeOnSale");
		break;
		
		case "JusticeOnSale_11":
			AddQuestRecord("JusticeOnSale", "4");
			CloseQuestHeader("JusticeOnSale");
			for(i = 0; i < sti(PChar.GenQuest.JusticeOnSale.EncQty); i++)
			{
				rChar = CharacterFromID("JusticeOnSale_ShorePirate_" + i);
				LAi_SetWarriorTypeNoGroup(rChar);
				LAi_Group_MoveCharacter(rChar, "JusticeOnSale_ShoreGroup");
			}
			
			LAi_Group_SetRelation("JusticeOnSale_ShoreGroup", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			AddDialogExitQuest("MainHeroFightModeOn");
			DialogExit();
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			break;
	}
}

void ChurchGenQuest2_GiveCup()
{
	AddItems(PChar, "Bible", 1);
	ref rItem = ItemsFromID("Bible");
	rItem.Name = "itmname_ChurchGenQuest2Cup"; // rItem.Name = "itmname_bible";
	rItem.City = XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_2.QuestTown + "Gen");
	rItem.Weight = 15.0; // rItem.Weight = 2;
	rItem.picIndex = 13; // itm.picIndex = 6;
	rItem.picTexture = "ITEMS_31"; // itm.picTexture = "ITEMS_9";
	ChangeItemDescribe("Bible", "itmdescr_ChurchGenQuest2Cup");
}

// Для генера "Пираты на необитаемом острове"
String PiratesOnUninhabited_GetStringNum(int _num)
{
	String retValue = "";
	
	switch(_num)
	{
		case 5: retValue = "five"; break;
		case 6: retValue = "six"; break;
		case 7: retValue = "seven"; break;
		case 8: retValue = "eight"; break;
		case 9: retValue = "nine"; break;
		case 10: retValue = "ten"; break;
	}
	
	return retValue;
}

int PiratesOnUninhabited_GenerateShipType()
{
	int rank = sti(PChar.rank);
	int retShipType;
	
	if(rank < 5)
	{
		switch(dRand(1))
		{
			case 0: retShipType = SHIP_LUGGER; break;
			case 1: retShipType = SHIP_SLOOP; break;
		}
	}
	
	if(rank >= 5 && rank < 20)
	{
		switch(dRand(3))
		{
			case 0: retShipType = SHIP_SLOOP; break;
			case 1: retShipType = SHIP_BRIGANTINE; break;
			case 2: retShipType = SHIP_SCHOONER_W; break;
			case 3: retShipType = SHIP_BRIG; break;
		}
	}
	
	if(rank >= 20)
	{
		switch(dRand(2))
		{
			case 0: retShipType = SHIP_CORVETTE; break;
			case 1: retShipType = SHIP_GALEON_H; break;
			case 2: retShipType = SHIP_FRIGATE; break;
		}
	}
	
	return retShipType;
}

String PiratesOnUninhabited_GenerateTreasureShore(ref _boxId)
{
	String retShoreId;
	
	switch(dRand(4))
	{
		case 0:
			retShoreId = "Shore9";
			_boxId = "box1";
		break;
		
		case 1:
			retShoreId = "Shore55";
			_boxId = "box" + (1 + rand(1)); // Сундук пусть рандомится и при с/л
		break;
	
		case 2:
			retShoreId = "Shore_ship1";
			_boxId = "box" + (1 + rand(1)); // Сундук пусть рандомится и при с/л
		break;
		
		case 3:
			retShoreId = "Shore_ship2";
			_boxId = "box" + (1 + rand(1)); // Сундук пусть рандомится и при с/л
		break;
		
		case 4:
			retShoreId = "Shore_ship3";
			_boxId = "box" + (1 + rand(1)); // Сундук пусть рандомится и при с/л
		break;
	}
	
	return retShoreId;
}

void PiratesOnUninhabited_SetCapToMap()
{
	int temp;
	String group = "PiratesOnUninhabited_SeaGroup";
	ref character = GetCharacter(NPC_GenerateCharacter("PiratesOnUninhabited_BadPirate", "", "man", "man", sti(pchar.rank) + 5, PIRATE, -1, true, "soldier"));		
	character.Ship.Type = GenerateShipExt(sti(PChar.GenQuest.PiratesOnUninhabited.StartShipType), true, character);
	character.Ship.Name = PChar.GenQuest.PiratesOnUninhabited.StartShipName;
    SetBaseShipData(character);
    SetCrewQuantityFull(character);
    Fantom_SetCannons(character, "pirate");
    Fantom_SetBalls(character, "pirate");
	Fantom_SetUpgrade(character, "pirate");
	
	character.Ship.Mode = "pirate";	
	SetCaptanModelByEncType(character, "pirate");

	DeleteAttribute(character, "SinkTenPercent");
	DeleteAttribute(character, "SaveItemsForDead");
	DeleteAttribute(character, "DontClearDead");
	DeleteAttribute(character, "AboardToFinalDeck");
	DeleteAttribute(character, "SinkTenPercent");
	
	character.AlwaysSandbankManeuver = true;
	character.AnalizeShips = true;  //анализировать вражеские корабли при выборе таска
	character.DontRansackCaptain = true; //не сдаваться
	
	SelAllPerksToChar(character, false);
	
	Group_FindOrCreateGroup(group);
	Group_SetTaskAttackInMap(group, PLAYER_GROUP);
	Group_LockTask(group);
	Group_AddCharacter(group, character.id);
	Group_SetGroupCommander(group, character.id);
	SetRandGeraldSail(character, PIRATE);
	
	character.fromCity = SelectAnyColony(""); // Колония, из бухты которой выйдет
	character.fromShore = GetIslandRandomShoreId(GetArealByCityName(character.fromCity));
	character.toCity = SelectAnyColony(character.fromCity); // Колония, в бухту которой придет
	character.toShore = GetIslandRandomShoreId(GetArealByCityName(character.toCity));
	
	character.mapEnc.type = "trade";
	character.mapEnc.worldMapShip = "quest_ship";
	character.mapEnc.Name = LowerFirst(XI_ConvertString(ShipsTypes[sti(PChar.GenQuest.PiratesOnUninhabited.StartShipType)].name)) + " '" + PChar.GenQuest.PiratesOnUninhabited.StartShipName + "'";
	
	Map_CreateTrader(character.fromShore, character.toShore, "PiratesOnUninhabited_BadPirate", GetMaxDaysFromIsland2Island(GetArealByCityName(character.toCity), GetArealByCityName(character.fromCity)) + 3);
	
	temp = GetCharacterFreeSpace(character, GOOD_SLAVES); // Сколько влезет рабов
	AddCharacterGoodsSimple(character, GOOD_SLAVES, makeint(temp / 2 + dRand(temp / 2)) - 1);
	
	PChar.Quest.PiratesOnUninhabited_ShipSink.win_condition.l1 = "Character_sink";
	PChar.Quest.PiratesOnUninhabited_ShipSink.win_condition.l1.character = "PiratesOnUninhabited_BadPirate";
	PChar.Quest.PiratesOnUninhabited_ShipSink.function = "PiratesOnUninhabited_ShipSink";
	
	Log_TestInfo("Pirates on an uninhabited island: cap left " + character.fromCity + " and went to: " + character.toShore);
}
