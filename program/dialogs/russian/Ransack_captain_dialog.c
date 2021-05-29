// BOAL диалог пленников - в трюме
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	ref offref;
    int i, cn;
    int qty;
    string attrLoc, sTmp;
    
	switch(Dialog.CurrentNode)
	{
		// -----------------------------------Диалог первый - первая встреча
		case "First time":
		//--> Jason, Ложный след
		if (CheckAttribute(pchar, "questTemp.FalseTrace.Prisoner") && GetFullName(npchar) == pchar.questTemp.FalseTrace.CapName)
		{
			dialog.text = "What do you want, captain? Discuss my ransom? I'd like you to know that I care about the girl's fate...";
			link.l1 = "You talk about Katerine Rayner? I am already informed about it, "+pchar.questTemp.FalseTrace.CapName+". She asked me to talk with you.";
			link.l1.go = "FalseTrace_Prisoner";
			break;	
		}
		//<-- Ложный след
		
		// Addon-2016 Jason ”ЊЉ-ѓваделупа
		if (CheckAttribute(pchar, "questTemp.FMQG") && pchar.questTemp.FMQG != "fail" && CheckAttribute(pchar, "questTemp.FMQG.Prisoner") && GetFullName(npchar) == pchar.questTemp.FMQG.Prisoner)
		{
			dialog.text = "";
			link.l1 = "See now, don Juan, treason is bad...";
			link.l1.go = "FMQG";
			break;	
		}
			if (sti(NPChar.nation) == PIRATE)
			{
				dialog.text = RandSwear() + "I am your prisoner, " + GetAddress_Form(NPChar) + ". But I want you to know that " + NationNameNominative(sti(NPChar.nation)) + " never pays for their people. We are all for ourselves.";
				link.l1 = "Well... I see that I won't make any profit on you. At least I can ransom you as a criminal in any colony.";
				link.l1.go = "offender";
				if (FindFreeRandomOfficer() > 0)
				{
					link.l2 = "Look, you are a skilled fighter and I need people like you. Would you like to serve under my command?";
					link.l2.go = "free_to_officer";
				}	
			}
			else
			{
				dialog.text = RandSwear() + "I am your prisoner, " + GetAddress_Form(NPChar) + ". " + NationNameNominative(sti(NPChar.nation)) + " will pay a good price for my freedom.";
				if(NPChar.EncType == "trade" && FindFreeRandomOfficer() > 0 && CheckAttribute(NPChar, "Back.Ship.Mode") && NPChar.Back.Ship.Mode == "trade")
				{
					link.l1 = "Look, you are a skilled sailor and I need people like you. Would you like to serve under my command?";
					link.l1.go = "free_to_officer_trader";
				}
			}
			attrLoc = Sea_FindNearColony();
			if (attrLoc != "none") 
			{
                link.l3 = "We are not far from " + GetConvertStr(attrLoc +" Town", "LocLables.txt") + ". And I could let you go here.";
			    link.l3.go = "free_withoutFee";
			}
			else
			{
                link.l3 = "Go to the boatswain, tell him to give you a locker. You can land in the next harbor.";
			    link.l3.go = "free_withoutFee_2";
			}			
			link.l4 = "I suppose I will make a great slave of you - strong and dutiful.";
			link.l4.go = "Slave_1";
			link.l5 = "You have ignored an order to lower your sails and resisted with force. You will be hanged for it. Boatswain have already received my orders.";
			link.l5.go = "PunishmentAction";
			link.l99 = "I know.";
			link.l99.go = "exit";
			NextDiag.TempNode = "second time"; 
		break;
		
		case "second time":
			if(CheckAttribute(NPChar,"Hold_GenQuest") && !CheckAttribute(pchar,"GenQuest.Hold_GenQuest"))
			{
				switch(sti(NPChar.Hold_GenQuest.variant))
				{				
					case 0: // "tip-off"
						dialog.text = RandPhraseSimple("Captain, would you like to hear my proposal about more profitable variant of my ransom?",
							"I understand that there is no room for barter in my place but would you like to hear my proposal?");
						link.l1 = "I am listening.";	
						link.l1.go = "free_tip_off";
					break;
					
					case 1:
						dialog.text = "Captain, why won't you just release me? I have no value for you. If you sell me to slavers you will only get a few coins and bad renown.";
						link.l1 = "And if I will simply release you I won't get a thing...";
						link.l1.go = "free_by_hoard";
						attrLoc = Sea_FindNearColony();
						if (attrLoc != "none") 
						{
							link.l2 = "You have ignored an order to lower your sails and resisted with force. You will be hanged for it. Boatswain have already received my orders.";
							link.l2.go = "PunishmentAction";							
						}
						else
						{
							link.l2 = "You are really insistent so I think I can give you what you want. You are free man now. Leave my ship.";
							link.l2.go = "free_in_sea";
						}
						link.l3 = LinkRandPhrase("Don't test my patience. You are already a lucky man to stay alive.",
							"I have got my own plans on you.","I suppose that you can still be useful for me in future.");
						link.l3.go = "exit";	
					break;
					
					case 2: // "ransom"
						dialog.text = "Captain, this uncertainty is killing me. May I know about your plans you have on me?";
						link.l1 = "Have you got anything to offer me?";
						link.l1.go = "free_buyout";
						link.l2 = RandPhraseSimple("I haven't got any ideas yet about you.",
							RandPhraseSimple("Plans? Cannonball on your neck? I am joking, ha!","You are my prisoner and I have all rights to do with you whatever I want. Your own opinion has no value here."));
						link.l2.go = "exit";
					break;										
				}
				NextDiag.TempNode = "second time"; 
			}
			else
			{
				if (sti(NPChar.nation) == PIRATE)
				{
					dialog.text = "Captain, why won't you just let me go? You don't need me. Choosing to be pirate was the only option for me because I have no valuable skills or education. My wish was to make some coin and retire then.";
					if (FindFreeRandomOfficer() > 0)
					{
						link.l2 = "Look, you are a skilled fighter and I need cut-throats like you. Would you like to be my officer?";
						link.l2.go = "free_to_officer";
					}				
					link.l3 = LinkRandPhrase("No mercy for you. There are a lot of thugs at sea. One less will be sailing there now at least.",
						" Any problems, 'sea wolf'? Stay here and be quiet.",
						"Gallows are waiting for all of your kind. I will sell you to the authorities and that will be a great lesson for any pirate.");	
					link.l3.go = "exit";
				}
				else
				{
					if(NPChar.EncType == "trade")
					{
						dialog.text = "Captain, I beg you... Release me. I've got family and kids and they won't make it without me.";
						if (FindFreeRandomOfficer() > 0 && CheckAttribute(NPChar, "Back.Ship.Mode") && NPChar.Back.Ship.Mode == "trade")
						{
							link.l2 = "Look, you are a skilled sailor and I need people like you. Would you like to serve under my command?";
							link.l2.go = "free_to_officer_trader";
						}
						link.l3 = LinkRandPhrase("I have got my own plans on you.","I suppose that you can still be useful for me in future.","You are my prisoner and I have all rights to do with you whatever I want.");
						link.l3.go = "exit";
					}
					if(NPChar.EncType == "war")
					{
						dialog.text = RandPhraseSimple("Captain, I have lost my fight and I beg you for your mercy. ",
							"Captain, I beg for your generosity. I understand that there is no reason for you to treat me like prisoner of war so I ask you to spare me. I give you my word that I will evade meeting you in the sea.");
						link.l2 = LinkRandPhrase("Don't test my patience. You are already a lucky man to stay alive.", 
							RandPhraseSimple("I have got my own plans on you.","I suppose that you can still be useful for me in future."),
							RandPhraseSimple("You are my prisoner and I have all rights to do with you whatever I want. Your own opinion has no value here.",
							"You are... well you was a captain of war ship and you were aware of risks. Don't try to represent yourself as a saint here."));
						link.l2.go = "exit";	
						if (isMainCharacterPatented() && sti(Items[sti(pchar.EquipedPatentId)].TitulCur) > 1)
						{
							if(sti(Items[sti(pchar.EquipedPatentId)].Nation) == sti(NPChar.nation) && FindFreeRandomOfficer() > 0)
							{
								link.l3 = "Look, you are a skilled fighter and I need cut-throats like you. Would you like to be my officer?";
								link.l3.go = "free_to_officer";
							}
						}
					}
				}
				attrLoc = Sea_FindNearColony();
				if (attrLoc != "none") 
				{
					link.l4 = "We are not far from " + GetConvertStr(attrLoc +" Town", "LocLables.txt") + ". And I could let you go here.";
					link.l4.go = "free_withoutFee";
				}
				else
				{
					if(NPChar.EncType == "trade" || NPChar.EncType == "pirate")
					{
						link.l4 = "Go to the boatswain, tell him to give you a locker. You can land in the next harbor.";
						link.l4.go = "free_withoutFee_4";			
					}	
					else
					{
						link.l4 = "Damn with you! Go to the boatswain, tell him to give you a locker. You can land in the next harbor. And remember that our next meeting will be the last one.";
						link.l4.go = "free_withoutFee_4";
					}
				}				
				link.l5 = "You have ignored an order to lower your sails and resisted with force. You will be hanged for it. Boatswain have already received my orders.";
				link.l5.go = "PunishmentAction";
				NextDiag.TempNode = "second time"; 
			}	
		break;
		
		case "offender":
			dialog.text = "Criminal? Are you kidding me," + GetAddress_Form(NPChar) + "!";
			link.l1 = "No kidding. You are a pirate.";
			link.l1.go = "exit";
		break;
		
		case "free_to_officer":
			if ((GetSummonSkillFromName(pchar, "Leadership") + 20) <= GetSummonSkillFromName(npchar, "Leadership"))
			{
				dialog.text = "Serving under your command? I'd better feed sharks!";
				link.l1 = "Watch your tongue or you will really feed them.";
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = "To be your officer, " + GetAddress_Form(NPChar) + "? I agree. I know my job and I tired to live in the shadow of the hallow.";
				link.l1 = "Deal! Go and do your job.";
				link.l1.go = "free_to_officer_Hire";
				link.l2 = "Wait a bit, I have changed my mind.";
				link.l2.go = "exit";
			}
		break;

		case "free_to_officer_trader":
			if (GetSummonSkillFromName(pchar, "Leadership") <= GetSummonSkillFromName(npchar, "Leadership"))
			{
				dialog.text = LinkRandPhrase("It is a tempting offer... but I have to reject it. On principle.",
					"Sorry but after what you have done with my friends... It is impossible.",
					"No, captain. After all of this terror I can't do this job anymore. I made a vow that if the Blessed Virgin will hear my prays and grant me a freedom I won't sail anymore.");
				link.l1 = "It is your choice. I won't be persistent.";	
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = "Why not? I am a bad captain, lost my ship and there is nothing left for me on the shore. Except bills and debts...";
				link.l1 = "Deal! Go to the boatswain and get your allowances. I will give you a position on my ship a bit later.";	
				link.l1.go = "free_to_officer_Hire";
				link.l2 = "Wait a bit, I have changed my mind.";
				link.l2.go = "exit";
			}
		break;
		
		case "free_to_officer_Hire":
            NPChar.Dialog.Filename = "Enc_Officer_dialog.c";
            NPChar.greeting = "Gr_Officer";
            NPChar.loyality = 5 + rand(10);
		    if (sti(NPChar.reputation) > 41)
		    {
		        NPChar.alignment = "good";
		    }
		    else
		    {
		        NPChar.alignment = "bad";
		    }
            ReleasePrisoner(NPChar); // освободили пленника
            DeleteAttribute(NPChar, "LifeDay") // постоянный
			Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(Npchar.id);
			// тут трем накопивщиеся сабли и корабли 290704 BOAL -->
			DeleteAttribute(Npchar, "Ship");
			Npchar.Ship.Type = SHIP_NOTUSED;
            DeleteAttribute(Npchar, "Fellows"); // его офицеры
            Npchar.Fellows.Passengers.id0 = Npchar.index; // свой пассажир

			Npchar.Fellows.Passengers.boatswain = "-1";
			Npchar.Fellows.Passengers.navigator = "-1";
			Npchar.Fellows.Passengers.doctor = "-1";
			Npchar.Fellows.Passengers.cannoner = "-1";
			Npchar.Fellows.Passengers.treasurer = "-1";
			Npchar.Fellows.Passengers.carpenter = "-1";
            
			if(CheckAttribute(NPChar,"Hold_GenQuest")) DeleteAttribute(NPChar, "Hold_GenQuest");
			
			AddDialogExitQuestFunction("LandEnc_OfficerHired");
			DialogExit();
        break;
				
		case "Slave_1":
			dialog.text = "But " + GetAddress_Form(NPChar) + ", you can't do that! I have surrendered.";
            link.l1 = "Shut your mouth! Bound him.";
			link.l1.go = "Slave_2";
			link.l99 = "Alright. Stay here until I decide...";
			link.l99.go = "exit";
		break;
		
		case "Slave_2":
			OfficersReaction("bad");		
			ChangeCharacterComplexReputation(pchar,"nobility", -2);
            if (rand(5) == 1)
            {
    			dialog.text = "No way! I'd better kill myself than become a slave!";
                link.l1 = "Stop that! It's an order!... Boatswain! Clean the cargo...";
    			link.l1.go = "free_in_sea_4";
			}			
			else
			{
                if (rand(1) == 1)
                {
                    if (GetPrisonerQty() > 1)
                    {
                        dialog.text = "Butcher! Guys, we have got nothing to loose!";
                        link.l1 = "Wrong choice, ladies. I deal with mutinies by myself and in a very fast way...";
            			link.l1.go = "free_in_sea_battle_all";
                    }
					else
					{
						dialog.text = "No way! I'd better die in fight!";
						link.l1 = "As you wish...";
						link.l1.go = "free_in_sea_battle_1";
					}	
    			}
    			else
    			{
					dialog.text = "Oh, I agree. I've got no choice.";
                    link.l1 = "Splendid. It's better to be a breathing slave than a dead hero.";
        			link.l1.go = "Slave_3";				
    			}			
			}
		break;

		case "Slave_3":
            ReleasePrisoner(NPChar); //  пленника в рабы
        	LAi_SetActorType(NPChar);
        	LAi_ActorRunToLocation(NPChar, "reload", "reload1", "none", "", "", "", 4.0);
        	ChangeCharacterComplexReputation(pchar,"nobility", -6);
        	DialogExit();
        	AddCharacterGoodsSimple(pchar, GOOD_SLAVES, 1);
        break;

		case "free_withoutFee":
			dialog.text = "Oh, " + GetAddress_Form(NPChar) + ", are you really that kind and releasing me without a ransom?";
            link.l1 = "Yes I do. You are free now," + GetFullName(NPChar);
			link.l1.go = "free_withoutFee_2";
			link.l99 = "Hm... You have a point! I need more time to decide.";
			link.l99.go = "exit";
		break;

		case "free_withoutFee_2":
			dialog.text = "Thank you, "+GetFullName(PChar) + "! I will pray for you.";
            link.l1 = "Go until I have changed my mind.";
			link.l1.go = "free_withoutFee_3";
			OfficersReaction("good");
		break;
		
		case "free_withoutFee_3":
            ReleasePrisoner(NPChar); // освободили пленника
        	LAi_SetActorType(NPChar);
        	LAi_ActorRunToLocation(NPChar, "reload", "reload1", "none", "", "", "", 4.0);
        	ChangeCharacterComplexReputation(pchar,"nobility", 2);
        	DialogExit();
        break;	

		case "free_withoutFee_4":	
			switch(NPChar.EncType)
			{
				case "pirate":
					dialog.text = RandPhraseSimple("Thank you, captain. I will never forget your kindness. I am going to leave this job and repair small boats in peaceful harbors. I can do that.",
						"Thank you, captain! I swear, I will give up this ungrateful occupation and become a fisher.");
					link.l1 = "I wish I believed...";	
				break;
				case "trade":
					dialog.text = "Don't even know how to thank you, captain. I have already lost my hope. I am going to tell everyone about your kindness. I give you my word that I will light a candle for you! Just let me get to a church.";
					link.l1 = "Farewell. And next time don't even try to resist. Shoot at me and this will be a death sentence for you and your crew.";
				break;
				case "war":
					dialog.text = "My thanks, captain. I will pray for you.";
					link.l1 = "Note that next time if we meet again. I won't be that kind.";
				break;
			}
			link.l1.go = "free_withoutFee_3";
		break;
		
		case "free_in_sea_battle_1":
            ReleasePrisoner(NPChar); // освободили пленника        	
        	LAi_LocationFightDisable(&Locations[FindLocation("My_Deck")], false);
            LAi_SetFightMode(Pchar, true);
            LAi_SetWarriorType(NPChar);
            LAi_group_MoveCharacter(NPChar, LAI_GROUP_TmpEnemy);
            LAi_group_SetHearRadius(LAI_GROUP_TmpEnemy, 100.0);
            LAi_group_FightGroupsEx(LAI_GROUP_TmpEnemy, LAI_GROUP_PLAYER, true, Pchar, -1, false, false);
            LAi_group_SetRelation(LAI_GROUP_TmpEnemy, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
            LAi_group_SetCheck(LAI_GROUP_TmpEnemy, "My_Deck_Battle_End");
            LAi_group_SetRelation(LAI_GROUP_TmpEnemy, "Prisoner", LAI_GROUP_NEITRAL);
        	DialogExit();
        break;		

		case "free_in_sea_battle_all":
			//ugeen --> привет Сиварду !!! после релиза пленников кол-во пассажиров уменьшается и цикл нихрена дальше не срабатывал
			for(int j = GetPassengersQuantity(pchar) - 1; j > -1; j--)
            {
                cn = GetPassenger(pchar, j);
                if(cn != -1)
                {
                    offref = GetCharacter(cn);
                    if (CheckAttribute(offref,"prisoned"))
                    {
        	            if(sti(offref.prisoned)==true && GetRemovable(offref)) // ставим только фантомов
        	            {
                        	ReleasePrisoner(offref); // освободили пленника
							LAi_SetWarriorType(offref);
							LAi_warrior_DialogEnable(offref, false);
                            LAi_group_MoveCharacter(offref, LAI_GROUP_TmpEnemy);
                        }
                    }
                }
            }
            LAi_LocationFightDisable(&Locations[FindLocation("My_Deck")], false);
            LAi_SetFightMode(Pchar, true);
			LAi_group_SetHearRadius(LAI_GROUP_TmpEnemy, 100.0);
            LAi_group_FightGroupsEx(LAI_GROUP_TmpEnemy, LAI_GROUP_PLAYER, true, Pchar, -1, false, false);
            LAi_group_SetRelation(LAI_GROUP_TmpEnemy, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
            LAi_group_SetCheck(LAI_GROUP_TmpEnemy, "My_Deck_Battle_End");
        	DialogExit();
        break;
		
		case "free_in_sea_4":
        	ReleasePrisoner(NPChar); // освободили пленника
            NPChar.location = "";
	        LAi_KillCharacter(NPChar);
        	DialogExit();
        break;

		case "PunishmentAction":
			dialog.text = "But " + GetAddress_Form(NPChar) + ", you can't do that! I have surrendered.";
			link.l1 = "Only after your men were gone. You betrayed them... Boatswain! Do it.";
			link.l1.go = "PunishmentAction1";
			link.l2 = "Well... I need time to think about it. Stay here.";
			link.l2.go = "exit";
        break;

		case "PunishmentAction1":
			OfficersReaction("bad");		
			ChangeCharacterComplexReputation(pchar,"nobility", -2);			
			AddCharacterExpToSkill(Pchar, "Leadership", -150);
			if (rand(1) == 1)
            {
                if (GetPrisonerQty() > 1)
                {
                    dialog.text = "Butcher! Guys, we have nothing to loose!";
                    link.l1 = "Wrong choice, ladies. I deal with mutinies by myself and in a very fast way...";
					link.l1.go = "free_in_sea_battle_all";
                }
				else
				{
					dialog.text = "No way! I'd better die in fight!";
					link.l1 = "As you wish...";
					link.l1.go = "free_in_sea_battle_1";
				}	
    		}
			else
    		{
				dialog.text = "At least give me some time to pray...";
                link.l1 = "Pray if you want.";
        		link.l1.go = "PunishmentAction2";				
    		}						
		break;
		
		case "PunishmentAction2":
        	ReleasePrisoner(NPChar); // освободили пленника
            NPChar.location = "";		
			NPChar.LifeDay = 0;
			LAi_CharacterDisableDialog(NPChar);
			DialogExit();
		break;
		
		case "free_tip_off":
			dialog.text = "I have got an interesting information which can be useful for a man like you. But I need your guarantees that I will get my freedom in exchange.";
			link.l1 = "How can I give you my guarantees if I don't even know your proposal? Doubtless your information can cost nothing.";
			link.l1.go = "free_tip_off_0";
			link.l2 = "I can only give you my word.";
			link.l2.go = "free_tip_off_1";
		break;
		
		case "free_tip_off_0":
			ChangeCharacterComplexReputation(pchar,"nobility", -2);			
			DeleteAttribute(NPChar, "Hold_GenQuest");
			DialogExit();
		break;
		
		case "free_tip_off_1":
			switch(NPChar.EncType)
			{
				case "trade":
					sTmp = "He proposed me a freight but this guy was too greedy and I rejected the offer.";  
				break;
				case "war":
					sTmp = "I have escorted him a few times as a commander of a convoy.";
				break;
				case "pirate":
					sTmp = "I had an idea to rob him once but I have never had a single chance to do that.";
				break;
			}
			dialog.text = "Fine. It's enough. Now straight to the business, in " + XI_ConvertString("Colony" + NPChar.Hold_GenQuest.City + "Dat") + " lives a wealthy merchant " + NPChar.Hold_GenQuest.Name + ". " + 
				"He made his fortune on his ship '" + NPChar.Hold_GenQuest.ShipName + " selling " + GetStrSmallRegister(XI_ConvertString(Goods[sti(NPChar.Hold_GenQuest.Goods)].Name + "Acc")) + " with route : " + XI_ConvertString("Colony" + NPChar.Hold_GenQuest.FromCity) + " - " + XI_ConvertString("Colony" + NPChar.Hold_GenQuest.ToCity) +". " + 
				"When he has too much cargo he pays for an escort." + sTmp + " I am sure that this information worth for you much more than a life of the single man.";
			link.l1 = "Doubt that this information can be useful for me. I won't hunt peaceful traders.";	
			link.l1.go = "free_tip_off_0";
			link.l2 = "Not sure that this information will work for me but I have given you my word. Boatswain will place you with my crew and will let you go in the closest harbor.";
			link.l2.go = "free_tip_off_2";			
		break;
		
		case "free_tip_off_2":
			dialog.text = "My thanks, captain! I had no doubt in your honesty!";
			link.l1 = RandPhraseSimple(RandPhraseSimple("I wish I could say the same about you","Sorry but I can't say the same about you."),
				RandPhraseSimple("Go and notice that next time I won't be that generous.","Go and never stay in my way. Next time I won't believe you so easily."));
			link.l1.go = "free_tip_off_3";
		break;
		
		case "free_tip_off_3":
			pchar.GenQuest.Hold_GenQuest.Goods 			= NPChar.Hold_GenQuest.Goods;			
			pchar.GenQuest.Hold_GenQuest.Nation 		= NPChar.Hold_GenQuest.Nation; 
			pchar.GenQuest.Hold_GenQuest.Name 			= NPChar.Hold_GenQuest.Name;
			pchar.GenQuest.Hold_GenQuest.ToCity 		= NPChar.Hold_GenQuest.ToCity;
			pchar.GenQuest.Hold_GenQuest.FromCity 		= NPChar.Hold_GenQuest.FromCity; 
			pchar.GenQuest.Hold_GenQuest.ShipName 		= NPChar.Hold_GenQuest.ShipName;				
			pchar.GenQuest.Hold_GenQuest.City 			= NPChar.Hold_GenQuest.City;
			pchar.GenQuest.Hold_GenQuest.CapName		= GetFullName(NPChar);
			pchar.GenQuest.Hold_GenQuest.Island			= GetArealByCityName(pchar.GenQuest.Hold_GenQuest.City); 
			pchar.GenQuest.Hold_GenQuest.Speak_Tavern 	= true;
			
			ReOpenQuestHeader("HoldQuest");
			AddQuestRecord("HoldQuest", "1");
			AddQuestUserData("HoldQuest", "sName", GetFullName(NPChar));
			AddQuestUserData("HoldQuest", "sGoods", GetStrSmallRegister(XI_ConvertString(Goods[sti(pchar.GenQuest.Hold_GenQuest.Goods)].Name + "Acc"))); 
			AddQuestUserData("HoldQuest", "sCityFrom", XI_ConvertString("Colony" + pchar.GenQuest.Hold_GenQuest.FromCity));
			AddQuestUserData("HoldQuest", "sCityTo", XI_ConvertString("Colony" + pchar.GenQuest.Hold_GenQuest.ToCity));
			AddQuestUserData("HoldQuest", "sShipName", pchar.GenQuest.Hold_GenQuest.ShipName);
			
			SetFunctionTimerCondition("Hold_GenQuest_SetMerchant_pre", 0, 0, 1+rand(2), false);
			SetFunctionTimerCondition("Hold_GenQuest_MerchantOver", 0, 0, 30, false);
			
            ReleasePrisoner(NPChar); // освободили пленника
        	LAi_SetActorType(NPChar);
			NPChar.LifeDay = 0;
        	LAi_ActorRunToLocation(NPChar, "reload", "reload1", "none", "", "", "", 4.0);
        	DialogExit();			
		break;
	
		case "free_buyout":
			dialog.text = "And I have a proposal for you. In " + XI_ConvertString("Colony" + NPChar.Hold_GenQuest.City + "Dat") + " lives my friend, " + NPChar.Hold_GenQuest.Name + " is his name. We had a business together once." +
				"Find him there. I am sure that he'll pay you a great sum. He owes me and I'll deal with him myself.";
			link.l1 = "Your friend, huh? Let's see him.";	
			link.l1.go = "free_buyout1";
			link.l2 = "Why should I look for your friend if I can get ransom in the very first harbor?";
			link.l2.go = "free_tip_off_0";
		break;
	
		case "free_buyout1":
			LAi_CharacterDisableDialog(NPChar);
			
			pchar.GenQuest.Hold_GenQuest.City 		= NPChar.Hold_GenQuest.City;			
			pchar.GenQuest.Hold_GenQuest.Nation 	= NPChar.Hold_GenQuest.Nation;
			pchar.GenQuest.Hold_GenQuest.Name 		= NPChar.Hold_GenQuest.Name;
			pchar.GenQuest.Hold_GenQuest.CapName	= GetFullName(NPChar);
			pchar.GenQuest.Hold_GenQuest.CapId		= NPChar.Id;
			pchar.GenQuest.Hold_GenQuest.TavernVariant = rand(1);
			pchar.GenQuest.Hold_GenQuest.Speak_Tavern = false;
			
			ReOpenQuestHeader("HoldQuest");
			AddQuestRecord("HoldQuest", "6");
			AddQuestUserData("HoldQuest", "sName", GetFullName(NPChar));
			AddQuestUserData("HoldQuest", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.Hold_GenQuest.City + "Dat")); 
			AddQuestUserData("HoldQuest", "sNameChar", NPChar.Hold_GenQuest.Name);
			DialogExit();
		break;

		case "free_by_hoard":
			dialog.text = "Actually I know one man who has a fine treasure but he doesn't have balls to use it.";
			link.l1 = "What do you mean?";
			link.l1.go = "free_by_hoard1";
			link.l2 = "Spare me of your stories. You'd better think about your soul.";
			link.l2.go = "free_tip_off_0";
		break;
		
		case "free_by_hoard1":
			dialog.text = "I'm telling you the story which leads to a great treasures. I need your word in return that you'll let me go in the next harbor.";
			link.l1 = "I will decide when and what to do with you by myself. From your inventions that will not depend.";
			link.l1.go = "free_tip_off_0";
			link.l2 = "I am listening. You have my word.";
			link.l2.go = "free_by_hoard2";
		break;
		
		case "free_by_hoard2":
			dialog.text = "I trust such a honorable "+ GetSexPhrase("man","woman") +". People like you always keep their word! Doesn't matter if the whole world is burning, you will keep your word! Am I right, captain?";
			link.l1 = "Tell me your story or I will let you go right now... overboard.";
			link.l1.go = "free_by_hoard4";
		break;
		
		case "free_by_hoard4":
			dialog.text = "Ha-ha, nice joke... Now listen. There is one pal in " + XI_ConvertString("Colony" + NPChar.Hold_GenQuest.City + "Dat") + 
				"named " + NPChar.Hold_GenQuest.Name + ", he was a really reckless guy in his youth. He had a lot of 'deals' those days..." + 
				"So once in the tavern he told me that he was a member of " + GetName( NAMETYPE_VIP, NPChar.Hold_GenQuest.PirateName, NAME_ACC) + " gang and saw how those pirates were burying a treasure." +
				" He had five his buddies killed over that treasure... There were gossips that he was catched and hanged, but truth is that he has withdrawn from business, started a family. He remembered the location of the treasure, even had drawn a map. He offered me to accompany him in finding the treasure. A superstitious man, the treasure was covered in blood, so he fears to go alone there. I admit, I didn't venture too. "+ 
                "He was ready to sell the map, but why would I need it if I will never go there anyway...\nThat's my story... I think that such a brave man like you will find it useful, and the map is quite cheap by the way.";
			link.l1 = "And do you really suggest me buying that? You story is not real so I break our deal.";
			link.l1.go = "free_tip_off_0";
			link.l2 = "Interesting story, though I don't really believe in it. But you have my word, go and tell boatswain to give you a locker. You are free.";
			link.l2.go = "free_by_hoard5";
		break;
		
		case "free_by_hoard5":
			dialog.text = "My thanks, captain! Now I see the price of the word of "+ GetSexPhrase("gentleman!","lady!");
			link.l1 = "Go and never stay in my way. Next time I won't let you go so easily.");
			link.l1.go = "free_by_hoard6";
		break;
		
		case "free_by_hoard6":
			pchar.GenQuest.Hold_GenQuest.City 		= NPChar.Hold_GenQuest.City;			
			pchar.GenQuest.Hold_GenQuest.Nation 	= NPChar.Hold_GenQuest.Nation;
			pchar.GenQuest.Hold_GenQuest.Name 		= NPChar.Hold_GenQuest.Name;
			pchar.GenQuest.Hold_GenQuest.PirateName	= NPChar.Hold_GenQuest.PirateName;
			pchar.GenQuest.Hold_GenQuest.CapName	= GetFullName(NPChar);
			pchar.GenQuest.Hold_GenQuest.TavernVariant = rand(1) + 2;
			pchar.GenQuest.Hold_GenQuest.Sum		= 10000 + rand(10000);
			pchar.GenQuest.Hold_GenQuest.Treasure	= rand(1);
			pchar.GenQuest.Hold_GenQuest.Speak_Tavern = false;
			
			ReOpenQuestHeader("HoldQuest");
			AddQuestRecord("HoldQuest", "12");
			AddQuestUserData("HoldQuest", "sName", GetFullName(NPChar));
			AddQuestUserData("HoldQuest", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.Hold_GenQuest.City + "Dat")); 
			AddQuestUserData("HoldQuest", "sNameChar", pchar.GenQuest.Hold_GenQuest.Name);
			AddQuestUserData("HoldQuest", "sPirateName", GetName( NAMETYPE_VIP, pchar.GenQuest.Hold_GenQuest.PirateName, NAME_ACC));
			
            ReleasePrisoner(NPChar); // освободили пленника
        	LAi_SetActorType(NPChar);
			NPChar.LifeDay = 0;
        	LAi_ActorRunToLocation(NPChar, "reload", "reload1", "none", "", "", "", 4.0);
        	DialogExit();					
		break;
		
		case "free_in_sea":
			dialog.text = "But, " + GetAddress_Form(NPChar) + ", we are in the open sea! It's the same as my execution!";
			link.l1 = "That's what you wanted. Farewell. Boatswain will make my order done.";
			link.l1.go = "PunishmentAction1";
			link.l2 = "Alright, I haven't decided yet.";
			link.l2.go = "exit";
		break;		
		
		//--> Jason, Ложный след
		case "FalseTrace_Prisoner":
			dialog.text = "Katerine! She really asked you to come here? Such a wonderful girl...";
			link.l1 = "Let's stay away from lyrics, captain, and talk about more serious things. I'm going to tell you about the current situation and I am expecting an answer from you. Your answer will determine your and Katerine's fate.";
			link.l1.go = "FalseTrace_Prisoner_1";
		break;
		
		case "FalseTrace_Prisoner_1":
			dialog.text = "I am listening, captain.";
			link.l1 = "I have boarded your galleon because Adam Rayner, Katerin's husband, told me that there were a lot of silver on your ship. This trick allowed him to return his wife who had escaped from him to you.";
			link.l1.go = "FalseTrace_Prisoner_2";
		break;
		
		case "FalseTrace_Prisoner_2":
			dialog.text = "Adam? That bastard? It was all his plan! Now I see... Yes, I helped Katrine to escape three month ago. Such a poor girl, you have no idea how he was treating her...";
			link.l1 = "She is his wife and it's not my business. I made a mistake boarding your galleon but it is too late to talk about it. Adam has promised me to pay for my help.";
			link.l1.go = "FalseTrace_Prisoner_3";
		break;
		
		case "FalseTrace_Prisoner_3":
			dialog.text = "Adam? Ha-ha! And you have trusted him? Captain, do you even know what kind of person he is? He...";
			link.l1 = "Katerine has already told me a lot about him and put a great effort in that. But his proposal make sense and though I have no reason to trust this bastard but maybe this time he is telling the truth. Now let's go straight to the point...";
			link.l1.go = "FalseTrace_Prisoner_4";
		break;
		
		case "FalseTrace_Prisoner_4":
			dialog.text = "";
			link.l1 = "I was going to ransom you to the authorities and to deliver Adam with Katerine to "+XI_ConvertString("Colony"+pchar.questTemp.FalseTrace.QuestCity+"Gen")+", then get from Adam information about gold of Squint-Eyed Solly and sail for it. But Katerine has persuaded me to talk with you first, she said that you might offer me something better and more reliable than Adam did, in exchange for your lives and freedom.";
			link.l1.go = "FalseTrace_Prisoner_5";
		break;
		
		case "FalseTrace_Prisoner_5":
			dialog.text = "";
			link.l1 = "That's why I am standing here and talking to you. I have finished. Now is your turn. Think about my words and words of Katerine and give me your ideas. You don't have much time.";
			link.l1.go = "FalseTrace_Prisoner_6";
		break;
		
		case "FalseTrace_Prisoner_6":
			dialog.text = "Captain! Though I don't think that you are a good man but you listened to pleading of a poor girl and came here. It shows me that you can be honorable and feel pity. I don't need time, I am ready to give you my proposal.";
			link.l1 = "Really? Excellent! I am listening.";
			link.l1.go = "FalseTrace_Prisoner_7";
		break;
		
		case "FalseTrace_Prisoner_7":
			dialog.text = "You will arrest Adam Rayner and put him in chains. Then you will take me and Katerine to "+XI_ConvertString("Colony"+pchar.questTemp.FalseTrace.TargetCity)+". Don't land in the city, after all, it was you who sank my galleon, drop all three of us at " + XI_ConvertString(pchar.questTemp.FalseTrace.TargetShore+"Gen") + "\nI would also ask you for a weapon. We will go to the city through the jungles and I'll make sure that the scum pays not only for his crimes but for yours too. He deserves it\nYou have my word that your name won't come up. In return, I will give you true information concerning a ship with gold of enemy state\nIt won't be big of a challenge, you will gain a fine booty. Much better than my ransom and 'so called' Squint-Eyed Solly's treasures. Do we have a deal?";
			link.l1 = "I don't like your plan. I think, that local authorities will organize a hunt for me as soon as I leave the shores of " + XI_ConvertString(pchar.questTemp.FalseTrace.TargetShore+"Gen") + ". No, captain, I am not going to risk my head. Our conversation is over.";
			link.l1.go = "FalseTrace_Prisoner_8";
			link.l2 = "Well, it looks like Katerine was right. I like your proposal. Adam Rayner will be arrested. I'll make it done right now. You will be released after we will arrest Adam. See you, captain!";
			link.l2.go = "FalseTrace_Prisoner_9";
		break;
		
		case "FalseTrace_Prisoner_8":
			DialogExit();
			AddQuestRecord("FalseTrace", "9");
			AddQuestUserData("FalseTrace", "sCity", XI_ConvertString("Colony"+pchar.questTemp.FalseTrace.QuestCity));
			AddDialogExitQuestFunction("SetCheckForSolly");
			bQuestDisableMapEnter = false;
			LAi_CharacterDisableDialog(npchar);
			DeleteAttribute(pchar, "GenQuest.DontSetCabinOfficer");
		break;
		
		case "FalseTrace_Prisoner_9":
			DialogExit();
			AddQuestRecord("FalseTrace", "10");
			pchar.quest.FalseTraceSollyOver.over = "yes"; //снять таймер
			AddDialogExitQuestFunction("SetCheckForGoldShip");
			LAi_CharacterDisableDialog(npchar);
			pchar.questTemp.FalseTrace.PrisonerID = npchar.id;
			Pchar.questTemp.FalseTrace.PrisonerIDX = GetCharacterIndex(npchar.id);
		break;
		//<-- Ложный след
		
		// Addon-2016 Jason ”ЊЉ-ѓваделупа
		case "FMQG":
			dialog.text = "You are here to preach or to do business?";
			link.l1 = "to do business. I need your partner in crime - Bertrand Pinette. I am in a deep shit because of him. Where can I find him, huh?";
			link.l1.go = "FMQG_1";
		break;
		
		case "FMQG_1":
			dialog.text = "Why do you think I'll tell you this?";
			link.l1 = "It's your ass on the line. I will take you to Basse-Terre, deliver you to the governor and receive a reward for capturing a deserter who arranged an escape of Carlos de Milyar. It's your call. Either you are telling me about Pinette's location or we both are heading to Guadeloupe.";
			link.l1.go = "FMQG_2";
		break;
		
		case "FMQG_2":
			dialog.text = "So you know everything... Fine, I'll tell you everything I know about Bertrand Pinette but you will set me free in return.";
			link.l1 = "Go tell me then. I will land you in Mosquito's bay, same as I did the last time. But lie to me and I will return and set that plantation you were gifted by don Carlos on fire, I will also inform Basse-Terre of your whereabouts.";
			link.l1.go = "FMQG_3";
		break;
		
		case "FMQG_3":
			dialog.text = "First, land me there. That will make me feel safer and I swear I'll tell you everything.";
			link.l1 = "Fine. It's not like you are going anywhere from here.";
			link.l1.go = "FMQG_4";
		break;
		
		case "FMQG_4":
			DialogExit();
			AddQuestRecord("FMQ_Guadeloupe", "16");
			LAi_CharacterDisableDialog(npchar);
			pchar.questTemp.FMQG.PrisonerID = npchar.id;
			Pchar.questTemp.FMQG.PrisonerIDX = GetCharacterIndex(npchar.id);
			pchar.quest.FMQG_SailMoskitos.win_condition.l1 = "location";
			pchar.quest.FMQG_SailMoskitos.win_condition.l1.location = "Shore47";
			pchar.quest.FMQG_SailMoskitos.function = "FMQG_ArriveMoskitos";
			pchar.questTemp.FMQG = "to_moskitos";
		break;
		
		case "Exit":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
		break;
		
	}
}
