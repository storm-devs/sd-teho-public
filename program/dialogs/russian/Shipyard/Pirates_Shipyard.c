// диалог по городам
// Это мастер тюнинга
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    string 	sTemp;
	int 	amount, iSan, iOil, iSil, iRop;
	int iTemp, iSum; // 280912
	ref 	shTo;
	string 	s1;
	
	int     Matherial1;
	int     Matherial2;
	int     Matherial3;
	int     Matherial4;
	int		HPPrice; 
	
	if ( sti(pchar.Ship.Type) != SHIP_NOTUSED)
	{
		int   	shipCurHP   = sti(RealShips[sti(pchar.Ship.Type)].HP);
		int   	shipBaseHP	= sti(RealShips[sti(pchar.Ship.Type)].BaseHP);
		int   	shipClass   = sti(RealShips[sti(pchar.Ship.Type)].Class);
	}	
 
	switch (Dialog.CurrentNode)
	{		
		// -----------------------------------Диалог первый - первая встреча
		case "First time":  // перехват основного диалога, только один раз
			if(NPChar.quest.meeting == "0")
			{
				Dialog.Text = "Phew... What kind of a terrible climate... My name is " + GetFullName(npchar) + ", and God damn me, I'm the best shipwright on these God-forgotten islands. But this humidity is just knocking me down...";
				Link.l1 = pcharrepphrase("A thousand sharks, I was just missing an old man's muttering. My name is " + GetFullName(pchar) + ", I believe you've heard about me.",
					"It's not humidity, it's old age, sir. My name is " + GetFullName(pchar) + ", I believe you've heard about me.");
				Link.l1.go = "node_1";
				npchar.quest.meeting = "1";
			}
			else // нужно, если по квестам будет сброс на  "First time"
			{
				dialog.text = "Oh, you again, always talking about your problems... (coughing).";
				link.l1 = pcharrepphrase("You're right, it's me again. But let's talk about business while you still haven't given God your soul away yet.",
					"Your memory serves you well, and now if you allow, let's get down to some more specific questions.");
				link.l1.go = "node_3";
				link.l2 = pcharrepphrase("I've grown tired of your muttering. Farewell.",
					"It's time for me to go. Sorry for bothering you");
				link.l2.go = "exit";
			}
			NextDiag.TempNode = "Master_Ship";
			Dialog.CurrentNode = "Master_Ship";
		break;
		
		case "Master_Ship":
		//Jason ----------------------------------- Хронометр Алекса ------------------------------------------
			if (CheckAttribute(npchar, "quest.sextant") && CheckAttribute(pchar, "questTemp.AlexClock") && pchar.location == "Pirates_shipyard" && !CheckAttribute(npchar, "quest.clock"))
			{
				dialog.text = "Aha, captain "+GetFullName(pchar)+"! How nice, that you've stopped by!";
				Link.l1 = "It looks like you need me for something, don't you? Usually you aren't quite as courteous.";
				Link.l1.go = "clock_begin";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.AlexClock") && pchar.questTemp.AlexClock == "clock" && pchar.location == "Pirates_shipyard")
			{
				dialog.text = "I see you've returned to me with empty hands, captain! What happened with the...guests?";
				Link.l1 = "They've gone. I asked them and they have gone.";
				Link.l1.go = "clock_complete";
				break;
			}
		//<-- хронометр Алекса
			dialog.text = "Oh, you again, always talking about your problems... (coughing)";
			link.l1 = pcharrepphrase("You're right, it's me again. But let's talk about business while you still haven't given God your soul away yet.",
	            "Your memory serves you well, and now if you allow, let's get down to some more specific questions.");
			link.l1.go = "node_3";
			link.l2 = pcharrepphrase("I've grown tired of your muttering. Farewell.",
				"It's time for me to go. Sorry for bothering you.");
			link.l2.go = "exit";
			NextDiag.TempNode = "Master_Ship";
		break;

		case "node_1":
			dialog.text = "Young people these days... You never have any respect. Hot heads, hard hands, what do you need?";
			link.l1 = pcharrepphrase("That's right. But sooner or later an ends comes to everything and looks like your time is near...",
				"Something tells me that during your young years, you didn't necessarily have much respect for elders too. Am I correct?");
			link.l1.go = "node_2";
		break;

		case "node_2":
			dialog.text = "Don't argue with olders, puppy";
			link.l1 = pcharrepphrase("Easy, now. Calm down. Don't overexert yourself otherwise you can get a heart attack. I don't want to be accused for the death of the best shipwright on the Caribbean. Let's get down to business.",
				"I forgive you for your rudeness, only out of respect for your age. And now, if you've finished, let's get down to business.");
			link.l1.go = "node_3";
			link.l2 = pcharrepphrase("All right, that's enough lecturing for me! Farewell!",
				"I see we're not going to see eye to eye. Farewell.");
			link.l2.go = "exit";
		break;

		case "node_3":
			dialog.text = "(coughing)... People won't leave an elder be. What do you need from me this time, " + GetAddress_Form(NPChar) + "? ";
			link.l1 = pcharrepphrase("I need to use the services of the shipyard.","I want to use the services of the shipyard.");
			link.l1.go = "shipyard_dlg";
            Link.l2 = "I have a question.";
			Link.l2.go = "quests"; //(пересылка в файл города)
			// -->
			if (CheckAttribute(pchar, "GenQuest.LoanChest.TakeChest") && sti(pchar.GenQuest.LoanChest.TargetIdx) == sti(NPChar.index))
			{
				link.l3 = "I'd like to talk about finance.";
				link.l3.go = "LoanForAll";//(перессылка в файл города)
			}
			link.l9 = pcharrepphrase("Shit, I have a couple of urgent matters to attend to, goodbye.", "It's time for me to go. Sorry.");
			link.l9.go = "exit";
			NextDiag.TempNode = "Master_Ship";
		break;
		
		case "shipyard_dlg":			
			if((shipBaseHP - shipCurHP > 0) && (shipClass < 6))
			{
				dialog.Text = "I can propose to you a capital repair of your hull's frame. People don't have a clue on how to build decent ships here - fall apart from one shot...";						
				Link.l1 = "Great! I happen to have a ship that needs repair. Maybe you'll have a look at what you can do?";
				Link.l1.go = "ship_repair_start";		
			}
			else
			{
				dialog.Text = "Come on, what do you want? Don't harass an old man...";
			}	
			link.l2 = "I just want to use the services of the shipyard.";
			link.l2.go = "shipyard";
			link.l3 = "I need weapons for the ship.";
			link.l3.go = "Cannons";
			if(RealShips[sti(Pchar.Ship.Type)].BaseType != SHIP_CURSED_FDM)
			{
					link.l4 = "I want to change the look of my sails.";
					link.l4.go = "SailsGerald";
			}
			if(RealShips[sti(Pchar.Ship.Type)].BaseType == SHIP_CURSED_FDM && !CheckAttribute(npchar, "quest.FDM_full"))
			{
					link.l50 = "My ship is quite... special. I'd like to make a few changes.";
					link.l50.go = "FDM";
			}
			if(RealShips[sti(Pchar.Ship.Type)].BaseType == SHIP_CURSED_FDM && CheckAttribute(npchar, "quest.FDM_full") && npchar.quest.FDM_full == "cabin" && GetCharacterItem(pchar, "Chest") > 0)
			{
					link.l50 = "I have more chests for cabin's reconstruction.";
					link.l50.go = "FDM_cabin_pay";
			}
			link.l9 = pcharrepphrase("Shit, I have a couple of urgent matters to attend to, goodbye.", "It's time for me to go. Sorry.");
			Link.l9.go = "ship_tunning_not_now";
		break;
		
		case "ship_repair_again":
			if((shipBaseHP - shipCurHP > 0) && (shipClass < 6))
			{
				dialog.Text = RandPhraseSimple("Ah... you again. Want to fix your vessel again?",
				RandPhraseSimple("Greetings, to a famous captain. What, do you need another capital repair?",
                                           "Sheesh... Not a minute of peace and quiet. You don't let an old man concentrate.. Another repair?"));
				Link.l1 = "Yes. Right you are. Will we have a look at what we can do?";
				Link.l1.go = "ship_repair_start";						   
			}
			else
			{
				dialog.Text = "What's happened this time? You just don't wanna let me be...";
			}				
			link.l2 = "I just want to use the services of the shipyard.";
			link.l2.go = "shipyard";
			link.l3 = "I need weapons for the ship.";
			link.l3.go = "Cannons";
			if(RealShips[sti(Pchar.Ship.Type)].BaseType != SHIP_CURSED_FDM)
			{
					link.l31 = "I want to change the look of my sails.";
					link.l31.go = "SailsGerald";
			}
			if(RealShips[sti(Pchar.Ship.Type)].BaseType == SHIP_CURSED_FDM && !CheckAttribute(npchar, "quest.FDM_full"))
			{
					link.l50 = "My ship is quite... special. I'd like to make a few changes.";
					link.l50.go = "FDM";
			}
			if(RealShips[sti(Pchar.Ship.Type)].BaseType == SHIP_CURSED_FDM && CheckAttribute(npchar, "quest.FDM_full") && npchar.quest.FDM_full == "cabin" && GetCharacterItem(pchar, "Chest") > 0)
			{
					link.l50 = "I have more chests for cabin's reconstruction.";
					link.l50.go = "FDM_cabin_pay";
			}
            Link.l4 = "I have a question.";
			Link.l4.go = "quests"; //(пересылка в файл города)
			// -->
			if (CheckAttribute(pchar, "GenQuest.LoanChest.TakeChest") && sti(pchar.GenQuest.LoanChest.TargetIdx) == sti(NPChar.index))
			{
				link.l5 = "I'd like to talk about finance.";
				link.l5.go = "LoanForAll";//(пересылка в файл города)
			}
			Link.l9 = "No. I'm happy with what I have.";
			Link.l9.go = "ship_tunning_not_now_2";
		break;
		
		case "ship_tunning_not_now_2":
			dialog.Text = "Oh, I see you're still thinking! You'll go far! Come back when you decide what you want and don't bother me with trifling nonsense.";
			Link.l1 = RandPhraseSimple("Thank you! All the best.", "Bye, master. And less sarcasm.");
			Link.l1.go = "ship_tunning_not_now";
		break;
		
		case "ship_repair_start":
            if ( sti(Pchar.Ship.Type) == SHIP_NOTUSED || Pchar.location.from_sea != "Pirates_town")
            {
                dialog.Text = "Where's the ship? What's all this hocus pocus?!";
			    Link.l1 = "Yes, you're right...I am... I apologize.";
			    Link.l1.go = "ship_tunning_not_now";
            }
            else
            {
			    if (GetHour() == 13)
			    {
					dialog.Text = "I may be a workaholic, but I've got a lunch time too. Come back later!";
			        Link.l1 = "Okay...";
			        Link.l1.go = "ship_tunning_not_now";
			    }
			    else
			    {
                    if( makefloat(shipCurHP)/makefloat(shipBaseHP) < 0.10)
                    {
						dialog.Text = "Sheesh... You're ship is completely wrecked. I won't do a capital repair, don't even ask me... If you had come a little bit earlier...";
    			        Link.l1 = "All right... That's too bad...";
    			        Link.l1.go = "ship_tunning_not_now";
    			        break;
                    }
					if( makefloat(shipCurHP)/makefloat(shipBaseHP) > 0.95)
                    {
						dialog.Text = "What's all this hocus pocus... Your ship looks good as new... The frame is practically shining bright. There's nothing to repair here.";
						Link.l1 = "Okay... Well, I'll come later...";
    			        Link.l1.go = "ship_tunning_not_now";
    			        break;
					}
                    s1 = "Okay, okay... What do we have here... Aha, " + XI_ConvertString(RealShips[sti(Pchar.Ship.Type)].BaseName) + ".";
    			    if (sti(RealShips[sti(Pchar.Ship.Type)].Stolen) == true && !CheckAttribute(&RealShips[sti(Pchar.Ship.Type)], "Tuning"))
    			    {
    			        s1 = s1 + " Bah! This ship's been in too many hands. Yeah and there are a lot of scuffs. Do you have a corsair patent? Just joking... anyway, back to the matter.";
    			    }
                    dialog.Text = s1;
					Link.l1 = "Let's have a look here at what we can do.";
    			    Link.l1.go = "ship_repair_HP";		    			    
    			    Link.l2 = "Stop! I've changed my mind.";
    			    Link.l2.go = "ship_tunning_not_now_2";
			    }
			}
		break;
		
		case "ship_repair_HP":
			HPPrice 	= GetMaterialQtyRepair( pchar, 0 ); 
			Matherial1	= GetMaterialQtyRepair( pchar, 1 );
			Matherial2	= GetMaterialQtyRepair( pchar, 2 );
			Matherial3	= GetMaterialQtyRepair( pchar, 3 );
			Matherial4	= GetMaterialQtyRepair( pchar, 4 );
			
			s1 = "Let's have a look here at what we can do. At the moment, the ship's frame is " + shipCurHP + ". . The highest possible value is " + shipBaseHP;			
			s1 = s1 + ". In order to make a full repair, I need: ironwood - "+ Matherial1 + ", resin - " + Matherial2 + ", ship silk - " + Matherial3 + " ropes - " + Matherial4 + ".";
			s1 = s1 + " For this work I will charge: "+ HPPrice + " doubloons for the labor... My grandchildren have been calling me back to Europe for a long time. I don't want to come back empty-handed you know... So, that'll be all. And oh yes - the money up front.";
            dialog.Text = s1;
			Link.l1 = "Sounds good. I'll accept the conditions. Everything will be delivered as agreed.";
			if(CheckItemMyCabin("gold_dublon") >= HPPrice)
			{
				Link.l1.go = "ship_repair_HP_start_0";
			}
			else
			{
				Link.l1.go = "ship_repair_HP_start";
			}			
			Link.l2 = "No. I'm not satisfied with that.";
			Link.l2.go = "ship_tunning_not_now";
		break;
		
		case "ship_repair_HP_start_0":
			dialog.Text = "Yes... The payment... You can pay right now or you can send an errand boy to the ship for the necessary amount... What would you like to do?";
			link.l1 = "I'll pay right now.";
			link.l1.go = "ship_repair_HP_start";
			link.l2 = "I'll send an errand boy. I believe I had a little bit of gold lying in my chests...";
			link.l2.go = "ship_repair_HP_start_1";
		break;
		
		case "ship_repair_HP_start":
		    amount = HPPrice;
		    if(GetCharacterItem(pchar,"gold_dublon") >= amount)
			{
				TakeNItems(pchar,"gold_dublon", -amount);				
			    NPChar.Repair.Money  		= amount;
			    NPChar.Repair.Matherial1 	= Matherial1; 
			    NPChar.Repair.Matherial2    = Matherial2;
				NPChar.Repair.Matherial3 	= Matherial3; 
			    NPChar.Repair.Matherial4    = Matherial4; 				 				
			    NPChar.Repair.ShipType      = Pchar.Ship.Type;
			    NPChar.Repair.ShipName      = RealShips[sti(Pchar.Ship.Type)].BaseName;
				NPChar.Repair.Delta         = shipBaseHP - shipCurHP;
			    			
				NextDiag.TempNode = "ship_repair_HP_again";
                dialog.text = "Splendid. I'll be waiting for the materials.";
			    link.l1 = "Going to gather 'em...";
			    link.l1.go = "Exit";
			    
			    ReOpenQuestHeader("ShipRepair");
			    AddQuestRecord("ShipRepair", "t1");
				AddQuestUserData("ShipRepair", "sText",  "For capital repairing measures of  " + XI_ConvertString(RealShips[sti(Pchar.Ship.Type)].BaseName) +
    " the shipmaster requires: ironwood - " + NPChar.Repair.Matherial1 + ", pitch - "+ NPChar.Repair.Matherial2 + ", ship silk - " + NPChar.Repair.Matherial3 + " ropes - " + NPChar.Repair.Matherial4 + 
				". As a deposit we handed in " + NPChar.Repair.Money + " doubloons... He says he's about to take off to Europe. I think that old devil's lying.");
			}
			else
			{
				NextDiag.TempNode = "ship_tunning_not_now";
                dialog.text = RandPhraseSimple("I don't see the deposit...","What's this hocus pocus...");
				link.l1 = "I'll be back later.";
				link.l1.go = "Exit";								
			}
		break;
		
		case "ship_repair_HP_start_1":
			AddTimeToCurrent(0, 30);
		    amount = HPPrice;
			GetItemMyCabin("gold_dublon", amount);
		    
			NPChar.Repair.Money  		= amount;
			NPChar.Repair.Matherial1 	= Matherial1; 
			NPChar.Repair.Matherial2    = Matherial2; 
			NPChar.Repair.Matherial3 	= Matherial3; 
			NPChar.Repair.Matherial4    = Matherial4; 				 							
			NPChar.Repair.ShipType      = Pchar.Ship.Type;
			NPChar.Repair.ShipName      = RealShips[sti(Pchar.Ship.Type)].BaseName;
			NPChar.Repair.Delta         = shipBaseHP - shipCurHP;
			    			
			NextDiag.TempNode = "ship_repair_HP_again";
			dialog.text = "Splendid. I'll be waiting for the material.";
			link.l1 = "Off I go...";
			link.l1.go = "Exit";
			
			ReOpenQuestHeader("ShipRepair");
			AddQuestRecord("ShipRepair", "t1");
			AddQuestUserData("ShipRepair", "sText",  "For capital repairing measures of  " + XI_ConvertString(RealShips[sti(Pchar.Ship.Type)].BaseName) +
    " the shipmaster requires: ironwood - " + NPChar.Repair.Matherial1 + ", resin - "+ NPChar.Repair.Matherial2 + ", ship silk - " + NPChar.Repair.Matherial3 + " ropes - " + NPChar.Repair.Matherial4 + 
				". As a deposit we handed in " + NPChar.Repair.Money + " doubloons... He says he's about to take off to Europe. I think that old devil's lying.");
			
		break;
		
		case "ship_repair_HP_again":
		    if (sti(NPChar.Repair.ShipType) == sti(Pchar.Ship.Type) && NPChar.Repair.ShipName == RealShips[sti(Pchar.Ship.Type)].BaseName)
		    {
                NextDiag.TempNode = "ship_repair_HP_again";
				dialog.Text = "Clock is ticking. Got what I asked?";
			    Link.l1 = "Yes. I managed to get some.";
			    Link.l1.go = "ship_repair_HP_again_2";
			    Link.l2 = "No. I'm still in my searches.";
			    Link.l2.go = "Exit";
			}
			else
			{
			    DeleteAttribute(NPChar, "Repair");
                NextDiag.TempNode = "ship_repair_again";
			    dialog.Text = "It seems to me, sir, that's you have changed you ship since the time of our last agreement. We'll have to recount everything all over again...";
			    Link.l1 = "Yes, that's true. What a pity that the deposit is gone...";
			    Link.l1.go = "Exit";		    
			    AddQuestRecord("ShipRepait", "Lose");
			    CloseQuestHeader("ShipRepair");
			}
		break;
		
		case "ship_repair_HP_again_2":
			checkMatherial_repair(Pchar, NPChar, GOOD_SANDAL, 	1);
			checkMatherial_repair(Pchar, NPChar, GOOD_OIL, 		2);
			checkMatherial_repair(Pchar, NPChar, GOOD_SHIPSILK, 3);
			checkMatherial_repair(Pchar, NPChar, GOOD_ROPES, 	4);
		    if(sti(NPChar.Repair.Matherial1) < 1 && 
			   sti(NPChar.Repair.Matherial2) < 1 &&
			   sti(NPChar.Repair.Matherial3) < 1 &&
			   sti(NPChar.Repair.Matherial4) < 1)
			{
                NextDiag.TempNode = "ship_repair_again";
                dialog.text = "Everything I needed. Good! Time to work...";
			    link.l1 = "I'm waiting.";
			    link.l1.go = "ship_repair_HP_complite";
			}
			else
			{
				NextDiag.TempNode = "ship_repair_HP_again";
				dialog.Text = "Now what you still have left to bring me is: "+ sti(NPChar.Repair.Matherial1) + " of ironwood, "+ sti(NPChar.Repair.Matherial2) + " resin, " + NPChar.Repair.Matherial3 + " of ship silk, " + NPChar.Repair.Matherial4 + "ropes.";
				link.l1 = "All right.";
				link.l1.go = "Exit";

                AddQuestRecord("ShipRepair", "t1");
				AddQuestUserData("ShipRepair", "sText", "Materials left: ironwood - "+ NPChar.Repair.Matherial1 + ", resin - "+ NPChar.Repair.Matherial2 + ", ship silk - " + NPChar.Repair.Matherial3 + " ropes - " + NPChar.Repair.Matherial4 + ".");
			}
		break;
		
		case "ship_repair_HP_complite":
		    AddTimeToCurrent(6, 30);
		    shTo = &RealShips[sti(Pchar.Ship.Type)];
			shTo.HP = sti(shTo.HP) + sti(NPChar.Repair.Delta);
		    DeleteAttribute(NPChar, "Repair");
			
			pchar.ship.hp = GetCharacterShipHP(pchar);
			DeleteAttribute(pchar, "ship.hulls");
			DeleteAttribute(pchar, "ship.blots");		
			
            NextDiag.TempNode = "node_3";
			dialog.Text = "... Well, that's all... I guarantee you it will be pretty hard to wreck this ship now!";
			Link.l1 = "Thank you! I'd rather not experiment with that.";
			Link.l1.go = "Exit";
			AddQuestRecord("ShipRepair", "End");
			CloseQuestHeader("ShipRepair");
		break;		
		
		///////////////////////////////  квестовые ветки
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("What questions do you have?", "How can I help you?"), "You tried to ask me a question a little while ago...", "I have never met people with such one-sided curiosity in my shipyard or anywhere else in this town.",
                          "What's with all the questions? My job is to build ships. Let's take care about that.", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("I've changed my mind...", "I've got nothing to talk about at the moment."), "Umph, where has my memory gone...",
                      "Hm, well...", "Okay, let us...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			if (!CheckAttribute(npchar, "Step_Door"))
			{
				link.l2 = "Listen, I'd like to pass through and the door is locked...";
				link.l2.go = "Step_Door_1";
			}

			if ((pchar.questTemp.different == "GiveShipLetters") && !CheckAttribute(pchar, "questTemp.different.GiveShipLetters.speakAlexus"))
			{
				link.l1 = "I'd like to propose a deal.";
				link.l1.go = "Al_ShipLetters_1";// генератор  "Найденные документы"
				pchar.questTemp.different.GiveShipLetters.speakAlexus = true;
			}
			if(CheckAttribute(pchar, "questTemp.AlexClock") && pchar.questTemp.AlexClock == "go") // 280912
			{
				link.l1 = "I'm here concerning the materials for the frigate.";
				link.l1.go = "clock";
			}
			if(CheckAttribute(pchar, "questTemp.Tieyasal") && pchar.questTemp.Tieyasal == "begin" && !CheckAttribute(npchar, "quest.Tieyasal"))
			{
				link.l1 = "Listen, "+npchar.name+", have you seen Miguel Dichoso on Isla Tesoro recently?";
				link.l1.go = "tieyasal";
			}
		break;
//*************************** Генератор - "Найденные судовые документы" **************
		
		case "Al_ShipLetters_1":
			dialog.text = "State you terms.";
			s1 = "I lucked into finding an absolutely legal ship's documents packet that hasn't been called for search yet.";
			s1 = s1 + "The ship is afloat and it hasn't been excluded from the registry, don't worry. Just a blind fool-owner had the misfortune of losing these papers...";
			link.l1 = s1;
			link.l1.go = "Al_ShipLetters_2";			
		break;
		case "Al_ShipLetters_2":
			s1 = "Let me take a look! It really looks to be freshly filled out. Well, luck is in your favor, sir! ";
			s1 = s1 + "I actually needed a packet just like this. I, in turn, will offer you " + sti(pchar.questTemp.different.GiveShipLetters.price5) + " pesos. What do you say?";
			dialog.text = s1;
			link.l1 = "True royal generosity! Of course I agree!";
			link.l1.go = "Al_ShipLetters_3";
			link.l2 = "No, I don't think so.";
			link.l2.go = "exit";
		break;
		case "Al_ShipLetters_3":
			TakeItemFromCharacter(pchar, "CaptainBook"); 
			addMoneyToCharacter(pchar, sti(pchar.questTemp.different.GiveShipLetters.price5)); 
			ChangeCharacterComplexReputation(pchar,"nobility", -1); 
			OfficersReaction("bad"); 
			pchar.questTemp.different = "free";
			pchar.quest.GiveShipLetters_null.over = "yes"; //снимаем таймер 
			AddQuestRecord("GiveShipLetters", "9");			
			CloseQuestHeader("GiveShipLetters");
			DeleteAttribute(pchar, "questTemp.different.GiveShipLetters");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit(); 
		break;
		

//*************************** Открывание двери ***************************
 		case "Step_Door_1":
			dialog.text = "That's correct. If you wanna pass through this door, you have to pay me 20000 pesos. If you don't pay, I won't open. This isn't a soup kitchen. And I don't advise you to go there anyway. It will be better for you if you don't...";
			if(sti(pchar.money) >= 20000)
			{
    			link.l1 = "Here's you money. Open up.";
    			link.l1.go = "Step_Door_2";
            }
            else
            {
    			link.l1 = "I don't have that much money.";
    			link.l1.go = "Step_Door_3";
            }
            link.l2 = "No way! I'd never pay for some door.";
    		link.l2.go = "exit";
		break;
		
 		case "Step_Door_2":
			npchar.Step_Door = true; // fix
			dialog.text = "Go in. The door is open. Don't worry about thanking me!";
			link.l1 = "No, why not. Thank you, " + npchar.name + "...";
			link.l1.go = "exit";
			LocatorReloadEnterDisable("Pirates_Shipyard", "reload2", false);
            AddMoneyToCharacter(pchar, -20000);
			pchar.quest.CloseBermudesDungeonDoor.win_condition.l1 = "MapEnter";
            pchar.quest.CloseBermudesDungeonDoor.win_condition = "CloseBermudesDungeonDoor";
		break;
		
 		case "Step_Door_3":
			dialog.text = "Well, when you have it, come back. Otherwise, don't try to convince me. It's useless...";
			link.l1 = "Argh, I'm completely speechless!";
			link.l1.go = "exit";
		break;
		
	// ------------------------------------------- хронометр Ђлекса ----------------------------------------------// Addon-2016 Jason замена дублонов на песо везде
		case "clock_begin":
			dialog.text = "Come on, don't be so strict with an old man... I really need your help, captain.";
			link.l1 = "Tell me, master. What happened to you?";
			link.l1.go = "clock_begin_1";
		break;
		
		case "clock_begin_1":
			sTotalTemp = "Steven Dodson";
			if (pchar.questTemp.Alex.Clock == "terrax") sTotalTemp = "Marcus Tyrex";
			dialog.text = "Our new leader of the Brethren of the Coast, "+sTotalTemp+", has ordered a new ship, a frigate. He also put quite difficult tasks: protected hull, fast speed and good maneuverability plus cannons of the biggest possible caliber\nI understand that admiral ship must be something special, but that means that I need special materials in order to build it. You must have heard of such. Ironwood, resin, ship silk and ropes...";
			link.l1 = "So tell about this the leader of the Brethren. Or are you leery that "+sTotalTemp+" will cut off your head for it?";
			link.l1.go = "clock_begin_2";
		break;
		
		case "clock_begin_2":
			dialog.text = "I told him... The thing is our new leader has not that time nor the opportunity to find and bring these materials. You have to know what kind of a rarity it is. And there's no way I'll be able to build a frigate with the known characteristics without them.";
			link.l1 = "And you probably propose that I have to find materials for the ship?";
			link.l1.go = "clock_begin_3";
		break;
		
		case "clock_begin_3":
			dialog.text = "Well, yes. You are a good friend of our leader. "+sTotalTemp+" says himself that he owes you a lot and that he demands all kind of respect for you... So I thought: since you're his friend, then maybe you wouldn't be against helping him? And that at the same time: you do realize what kind of an awkward position I'm in? All materials will be paid for, "+sTotalTemp+" isn't tight with his gold.";
			link.l1 = "I'm quite sorry, master, but I'm no less busy than "+sTotalTemp+". I'm afraid that collecting materials may take a whole eternity. So, you'd better ask somebody else.";
			link.l1.go = "clock_exit";
			link.l2 = "Well, if you're the ship orderer "+sTotalTemp+" - then of course I'll try to help. We are really friends, and friends have to help each other. How many materials do you need?";
			link.l2.go = "clock_begin_4";
		break;
		
		case "clock_exit":
			dialog.text = "That's too bad. That's really too bad. I was depending on you. Well, as they say, no means no...";
			link.l1 = "...";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.AlexClock");
		break;
		
		case "clock_begin_4":
			dialog.text = "I'm missing 100 unites of ironwood, 150 containers of resin, 110 rolls of ship silk, and 90 coils of hemp ropes. How do you think you, could you find me all of that in the course of four months? I don't think I have more time.";
			link.l1 = "I can at least try. And as for the payment?";
			link.l1.go = "clock_begin_5";
		break;
		
		case "clock_begin_5":
			dialog.text = "Here are my rates: ironwood at 4000 pesos per a piece, resins at 1400 pesos per a container, silk at 2500 pesos per roll, and ropes at 1500 pesos per coil. And if you bring all of that to me, you'll receive a useful gift from me.";
			link.l1 = "What is it, I wonder?";
			link.l1.go = "clock_begin_6";
		break;
		
		case "clock_begin_6":
			dialog.text = "Bring me the materials first. But I assure you: it'll come well in handy for you, and the thing is unique. there isn't another on the Caribbean, or in the whole world. I hope that little spark of curiosity fired your interest into gathering the materials for me.";
			link.l1 = "Well, you're slick as a leprechaun, master! All right, you've got yourself a deal.";
			link.l1.go = "clock_begin_7";
		break;
		
		case "clock_begin_7":
			dialog.text = "I'm very happy. I'll be looking forward to your return.";
			link.l1 = "I hope it won't take you too long...";
			link.l1.go = "clock_begin_8";
		break;
		
		case "clock_begin_8":
			DialogExit();
			pchar.questTemp.AlexClock = "go";
			npchar.quest.clock = "true";
			SetFunctionTimerCondition("AlexClock_Over", 0, 0, 122, false); // таймер
			AddQuestRecord("alex_clock", "1");
			// запоминаем переменные
			pchar.questTemp.AlexClock.Sandal = 100;
			pchar.questTemp.AlexClock.Oil = 150;
			pchar.questTemp.AlexClock.Shipsilk = 110;
			pchar.questTemp.AlexClock.Ropes = 90;
		break;
		
		case "clock":
			dialog.text = "Excellent! What have you brought me today?";
			if (GetSquadronGoods(pchar, GOOD_SANDAL) > 0 && !CheckAttribute(npchar, "quest.sandal"))
			{
				iSan = GetSquadronGoods(pchar, GOOD_SANDAL);
				link.l1 = "Ironwood, in the amount of "+FindRussianQtyString(iSan)+".";
				link.l1.go = "sandal";
			}
			if (GetSquadronGoods(pchar, GOOD_OIL) > 0 && !CheckAttribute(npchar, "quest.oil"))
			{
				iOil = GetSquadronGoods(pchar, GOOD_OIL);
				link.l2 = "Resins, in the amount of "+FindRussianQtyString(iOil)+".";
				link.l2.go = "oil";
			}
			if (GetSquadronGoods(pchar, GOOD_SHIPSILK) > 0 && !CheckAttribute(npchar, "quest.shipsilk"))
			{
				iSil = GetSquadronGoods(pchar, GOOD_SHIPSILK);
				link.l3 = "Ship silk, in the amount of "+FindRussianQtyString(iSil)+".";
				link.l3.go = "shipsilk";
			}
			if (GetSquadronGoods(pchar, GOOD_ROPES) > 0 && !CheckAttribute(npchar, "quest.ropes"))
			{
				iRop = GetSquadronGoods(pchar, GOOD_ROPES);
				link.l4 = "Hemp ropes, in the amount of "+FindRussianQtyString(iRop)+".";
				link.l4.go = "ropes";
			}
			link.l5 = "Nothing at the moment. I just wanted to make sure that we still have an agreement.";
			link.l5.go = "exit";
		break;
		
		case "clock_1":
			if (CheckAttribute(npchar, "quest.sandal") && CheckAttribute(npchar, "quest.oil") && CheckAttribute(npchar, "quest.shipsilk") && CheckAttribute(npchar, "quest.ropes")) // все привез
			{
				dialog.text = "Wonderful! I've got all the materials in the amount I need. Thanks a million for your help, captain. You've helped me out big time.";
				link.l1 = "Yes, any time, master. I'm quite pleased as well: I helped a friend out and I made some good money. And now let's get back to our conversation about your mysterious item that you promised me.";
				link.l1.go = "clock_2";
			}
			else
			{
				dialog.text = "Any more surprises for me, captain?";
				link.l1 = "Alas, that's all for now. Just keep waiting.";
				link.l1.go = "exit";
				link.l2 = "Yes, I've got one more thing...";
				link.l2.go = "clock";
			}
		break;
		
		case "sandal": // бакаут
			amount = sti(pchar.questTemp.AlexClock.Sandal);
			iTemp = amount-iSan;
			if (iTemp > 0) // ещё не все привез
			{
				iSum = 4000*iSan;
				dialog.text = "Okay, okay. I'm also going to need "+FindRussianQtyString(amount)+" of ironwood. You've brought me "+FindRussianQtyString(iSan)+". . So, what's left for you to bring me is "+FindRussianQtyString(iTemp)+". All right, at the rate of 4000 pesos per a piece, your reward totals at "+FindRussianMoneyString(iSum)+". Please, take it.";
				link.l1 = "Thank you! You'll have the rest soon.";
				link.l1.go = "clock_1";
				RemoveCharacterGoods(pchar, GOOD_SANDAL, iSan);
				pchar.questTemp.AlexClock.Sandal = iTemp; // столько осталось довезти
				AddQuestRecord("alex_clock", "2");
				AddQuestUserData("alex_clock", "sGood", "ironwood");
				AddQuestUserData("alex_clock", "sQty", FindRussianQtyString(iTemp));
			}
			else
			{
				iSum = 4000*amount;
				dialog.text = "Okay, okay. I'm also going to need "+FindRussianQtyString(amount)+"  of ironwood. You've brought me "+FindRussianQtyString(iSan)+". So, we've taken care of the ironwood now! All right, at the rate of 4000 pesos per a piece, your reward totals at "+FindRussianMoneyString(iSum)+". Please, take it.";
				link.l1 = "Thank you!";
				link.l1.go = "clock_1";
				RemoveCharacterGoods(pchar, GOOD_SANDAL, amount);
				npchar.quest.sandal = "true";
				AddQuestRecord("alex_clock", "3");
				AddQuestUserData("alex_clock", "sGood", "ironwood");
			}
			AddMoneyToCharacter(pchar, iSum);
		break;
		
		case "oil": // смолы
			amount = sti(pchar.questTemp.AlexClock.Oil);
			iTemp = amount-iOil;
			if (iTemp > 0) // еще не все привез
			{
				iSum = 1400*iOil;
				dialog.text = "Okay, okay. I'm also going to need "+FindRussianQtyString(amount)+" resins. You've brought me "+FindRussianQtyString(iOil)+". So, what's left for you to bring me is "+FindRussianQtyString(iTemp)+". All right, at the rate of 1400 pesos per a container, your reward totals at "+FindRussianMoneyString(iSum)+". Please, take it.";
				link.l1 = "Thank you! You'll have the rest soon.";
				link.l1.go = "clock_1";
				RemoveCharacterGoods(pchar, GOOD_OIL, iOil);
				pchar.questTemp.AlexClock.Oil = iTemp; // столько осталось довезти
				AddQuestRecord("alex_clock", "2");
				AddQuestUserData("alex_clock", "sGood", "resins");
				AddQuestUserData("alex_clock", "sQty", FindRussianQtyString(iTemp));
			}
			else
			{
				iSum = 1400*amount;
				dialog.text = "Okay, okay. I'm also going to need "+FindRussianQtyString(amount)+" resins. You've brought me "+FindRussianQtyString(iOil)+". So, we've taken care of the resins now! All right, at the rate of 1400 pesos per a container, your reward totals at "+FindRussianMoneyString(iSum)+". Please, take it.";
				link.l1 = "Thank you!";
				link.l1.go = "clock_1";
				RemoveCharacterGoods(pchar, GOOD_OIL, amount);
				npchar.quest.oil = "true";
				AddQuestRecord("alex_clock", "3");
				AddQuestUserData("alex_clock", "sGood", "resins");
			}
			AddMoneyToCharacter(pchar, iSum);
		break;
		
		case "shipsilk": // шёлк
			amount = sti(pchar.questTemp.AlexClock.Shipsilk);
			iTemp = amount-iSil;
			if (iTemp > 0) // еще не все привез
			{
				iSum = 2600*iSil;
				dialog.text = "Okay, okay. I'm also going to need "+FindRussianQtyString(amount)+" silk. You've brought me "+FindRussianQtyString(iSil)+". So, what's left for you to bring me is "+FindRussianQtyString(iTemp)+". All right, at the rate of 2600 pesos per a piece, your reward totals at "+FindRussianMoneyString(iSum)+". Please, take it.";
				link.l1 = "Thank you! You'll have the rest soon.";
				link.l1.go = "clock_1";
				RemoveCharacterGoods(pchar, GOOD_SHIPSILK, iSil);
				pchar.questTemp.AlexClock.Shipsilk = iTemp; // столько осталось довезти
				AddQuestRecord("alex_clock", "2");
				AddQuestUserData("alex_clock", "sGood", "silk");
				AddQuestUserData("alex_clock", "sQty", FindRussianQtyString(iTemp));
			}
			else
			{
				iSum = 2600*amount;
				dialog.text = "Okay, okay. I'm also going to need "+FindRussianQtyString(amount)+" silk. You've brought me "+FindRussianQtyString(iSil)+". So, we've taken care of the silk now! So, at the rate of 2600 pesos per a piece, your reward totals at "+FindRussianMoneyString(iSum)+". Please, take it.";
				link.l1 = "Thank you!";
				link.l1.go = "clock_1";
				RemoveCharacterGoods(pchar, GOOD_SHIPSILK, amount);
				npchar.quest.shipsilk = "true";
				AddQuestRecord("alex_clock", "3");
				AddQuestUserData("alex_clock", "sGood", "silk");
			}
			AddMoneyToCharacter(pchar, iSum);
		break;
		
		case "ropes": // канаты
			amount = sti(pchar.questTemp.AlexClock.Ropes);
			iTemp = amount-iRop;
			if (iTemp > 0) // еще не все привез
			{
				iSum = 1500*iRop;
				dialog.text = "Okay, okay. I'm also going to need "+FindRussianQtyString(amount)+" ropes. You've brought me "+FindRussianQtyString(iRop)+". So, what's left for you to bring me is "+FindRussianQtyString(iTemp)+". So, at the rate of 1500 pesos per a piece, your reward totals at "+FindRussianMoneyString(iSum)+". Please, take it.";
				link.l1 = "Thank you! You'll have the rest soon.";
				link.l1.go = "clock_1";
				RemoveCharacterGoods(pchar, GOOD_ROPES, iRop);
				pchar.questTemp.AlexClock.Ropes = iTemp; // столько осталось довезти
				AddQuestRecord("alex_clock", "2");
				AddQuestUserData("alex_clock", "sGood", "ropes");
				AddQuestUserData("alex_clock", "sQty", FindRussianQtyString(iTemp));
			}
			else
			{
				iSum = 1500*amount;
				dialog.text = "Okay, okay. I'm also going to need "+FindRussianQtyString(amount)+" ropes. You've brought me "+FindRussianQtyString(iRop)+". So, we've taken care of the ropes already. All right, at the rate of 1500 pesos per a piece, your reward totals at "+FindRussianMoneyString(iSum)+". Please, take it.";
				link.l1 = "Thank you!";
				link.l1.go = "clock_1";
				RemoveCharacterGoods(pchar, GOOD_ROPES, amount);
				npchar.quest.ropes = "true";
				AddQuestRecord("alex_clock", "3");
				AddQuestUserData("alex_clock", "sGood", "ropes");
			}
			AddMoneyToCharacter(pchar, iSum);
		break;
		
		case "clock_2":
			dialog.text = "Yes, yes... about my thing, of course. M-m-mmm...";
			link.l1 = "What is it master? You look quite worried. Is anything wrong? Some kind of problems?";
			link.l1.go = "clock_3";
		break;
		
		case "clock_3":
			dialog.text = "Precisely. Problems. Recent ones. Damn those treasure hunters...";
			link.l1 = "Calm down, calm down. It's not good at your age to be worrying like that. God forbid, you could be one beat away. Who would build the frigate for the head of the Brethren then? Calm down and explain to me who are these treasure hunters?";
			link.l1.go = "clock_4";
		break;
		
		case "clock_4":
			dialog.text = "Over there by my table is a door. It leads directly into an old vault. In this vault in one of the treasure chests, I keep my metal box with objects that were with me when I was pulled through that damn funnel twenty years ago and I ended up here...";
			link.l1 = "What funnel? What are you talking about?";
			link.l1.go = "clock_5";
		break;
		
		case "clock_5":
			dialog.text = "Ah, sorry for my fantasies. Being old is not easy, young man. Pardon. But it's irrelevant. What's relevant is that a box with a gift for you is in the chest which is lying in the dungeon currently occupied by some scums. They are not of us, not from Isla Tesoro\nTreasure hunters, someone must had told them that this place is full of treasures. They won't dare to show themselves right here, however I am too scared to visit them, see? Their faces...";
			link.l1 = "I see. Open your door. I'll beat out your uninvited guests.";
			link.l1.go = "clock_6";
		break;
		
		case "clock_6":
			dialog.text = "Just like that? You'll beat them out? Alone? Aren't you scared?";
			link.l1 = "Less talk, more action, master. Open this door and leave the rest to me. In what chest are you keeping your things?";
			link.l1.go = "clock_7";
		break;
		
		case "clock_7":
			dialog.text = "Right down the hallway is a whole collection of empty wooden barrels. Behind them on the floor in a secluded place is a small chest. I've pounded a lock on it, so I doubt those intruders would manage to get their dirty hands inside it even if they found it. Here, take the key.";
			link.l1 = "I'm glad you  think ahead. Wait here and don't go anywhere.";
			link.l1.go = "clock_8";
		break;
		
		case "clock_8":
			DialogExit();
			GiveItem2Character(pchar, "key3"); 
			bDisableFastReload = true;//закрыть переход
			LocatorReloadEnterDisable("Pirates_Shipyard", "reload1_back", true);
			LocatorReloadEnterDisable("Pirates_Shipyard", "reload2", false);
			LAi_LocationDisableOfficersGen("Bermudes_Dungeon", true);//офицеров не пускать
			pchar.quest.Alex_Chest.win_condition.l1 = "location";
			pchar.quest.Alex_Chest.win_condition.l1.location = "Bermudes_Dungeon";
			pchar.quest.Alex_Chest.function = "AlexClock_Chest";
			pchar.quest.AlexClock_Over.over = "yes"; //снять прерывание
			pchar.questTemp.AlexClock = "chest";
			AddQuestRecord("alex_clock", "3");
		break;
		
		case "clock_complete":
			dialog.text = "They just listened to you and left?";
			link.l1 = "That's right. They ended up being some polite guys. I explained to them that their presence is scaring the old famous shipwright and out of respect to you old age, they left the premises. You can come down without a fret.";
			link.l1.go = "clock_complete_1";
		break;
		
		case "clock_complete_1":
			dialog.text = "Oh, you're mocking an old man! All right. Give me my box and I'll open it up and give you the device you've earned fair and square.";
			link.l1 = "Please, take it...";
			link.l1.go = "clock_complete_2";
		break;
		
		case "clock_complete_2":
			RemoveItems(pchar, "alexs_chest", 1);
			dialog.text = "Gratitude! Let's open it. Here, take this. Automatic mechanical timer, no one makes such devices here and no one will for next three hundred years... huh, apologies, please forgive the old man. All I am saying that this thing is unique\nIt does all work itself, you won't need stupid sand clocks and so on. No errors! Just keep it safe from direct blows and water otherwise you will loose it. Even an ape can use this timer.";
			link.l1 = "Get a load of this! I've never seen anything so miraculous in my life! Thanks, master.";
			link.l1.go = "clock_complete_3";
		break;
		
		case "clock_complete_3":
			GiveItem2Character(pchar, "clock3");
			Log_Info("You've received an automatic mechanical timer");
			SetAlchemyRecipeKnown("sextant2");
			PlaySound("interface\important_item.wav");
			dialog.text = "You're welcome. Now you'll always know for sure what time it is. Don't ask me where I got it. I won't tell you.";
			link.l1 = "Everyone has their secrets, don't they master? Keep your secret and I won't bud into your business. Thanks for the gift!";
			link.l1.go = "clock_complete_4";
		break;
		
		case "clock_complete_4":
			dialog.text = "And thank you for your help, captain. Visit me sometimes. Don't forget an old shipwright.";
			link.l1 = "Like I could forget you... Anyway, I'll definitely do that, Alexus the Master. Goodbye!";
			link.l1.go = "clock_complete_5";
		break;
		
		case "clock_complete_5":
			DialogExit();
			bDisableFastReload = false;
			LocatorReloadEnterDisable("Pirates_Shipyard", "reload2", true);
			LocatorReloadEnterDisable("Pirates_Shipyard", "reload1_back", false);
			LocatorReloadEnterDisable("Bermudes_Dungeon", "reload2_back", false);
			LAi_LocationDisableOfficersGen("Bermudes_Dungeon", false);
			AddQuestRecord("alex_clock", "5");
			CloseQuestHeader("alex_clock");
			DeleteAttribute(pchar, "questTemp.AlexClock");
		break;
	// <-- хронометр Алекса
		
		// город майя
		case "tieyasal":
			dialog.text = "Aha, Miguel! My old acquaintance. I remember him. He asked me about every little detail over and over. But how was I going to explain to him how a radio was constructed inside when he hadn't even see a simple telegraph?";
			link.l1 = "What?.. What are you talking about, master?";
			link.l1.go = "tieyasal_1";
		break;
		
		case "tieyasal_1":
			dialog.text = "Oh, sorry, young man. Don't pay much attention to my talking... Our curious Michelle had satisfied his curiosity and disappeared. Only three days ago we had a chat.";
			link.l1 = "Where's Miguel right now if you don't mind my asking?";
			link.l1.go = "tieyasal_2";
		break;
		
		case "tieyasal_2":
			dialog.text = "Who knows. Maybe he's doing his business in Sharptown or maybe he's already departed from Isla Tesoro.";
			link.l1 = "I see. Thanks, master!";
			link.l1.go = "tieyasal_3";
		break;
		
		case "tieyasal_3":
			DialogExit();
			npchar.quest.tieyasal = "true";
		break;
		
		// Калеуче
		case "FDM":
			dialog.text = "A-ha, the ghost ship! Moms scares their bad kids with it. Why would you need this damned vessel! Sailors get frightened when they see her at the horizon... What do you want to do with her?";
			if (!CheckAttribute(npchar, "quest.FDM_cabin"))
			{
				link.l1 = "I like the idea of little cowards who scared shitless. But the interior makes me sad. Have you seen the cabin? It feels like a coffin. All these mold and dust. I want to fix it. Can you do that, master?";
				link.l1.go = "FDM_cabin";
			}
			if (!CheckAttribute(npchar, "quest.FDM_sails"))
			{
				link.l2 = "I am fed up with these torn black rags. I admit, they catch the wind as good as the normal sails but the view... Disgusting. I want ordinary snow white sails. Are you in, master?";
				link.l2.go = "FDM_sails";
			}
		break;
		
		case "FDM_cabin":
			dialog.text = "Why not? My hands are still straight. Your galleon is huge, so I can even make a royal cabin like they build in battleships and man-of-wars. Or we can keep a standard cabin. The choice is yours?";
			link.l1 = "Build the cabin of the line ship! They all will die of envy...";
			link.l1.go = "FDM_cabin_m";
			link.l2 = "No point in excessive luxuries. Keep the standard.";
			link.l2.go = "FDM_cabin_s";
		break;
		
		case "FDM_cabin_m":
			dialog.text = "Fine. Ten chests of doubloons and it will be done in five days.";
			link.l1 = "Deal!";
			link.l1.go = "FDM_cabin_m1";
			link.l2 = "Ten chests? Thousand and a half doubloons? Hm, I need time to consider such expenses...";
			link.l2.go = "exit";
		break;
		
		case "FDM_cabin_s":
			dialog.text = "Fine. Seven chests of doubloons and it will be done in five days.";
			link.l1 = "Deal!";
			link.l1.go = "FDM_cabin_s1";
			link.l2 = "Seven chests? More than a thousand doubloons? Hm, I need time to consider such expenses...";
			link.l2.go = "exit";
		break;
		
		case "FDM_cabin_m1":
			iTemp = GetCharacterItem(pchar, "Chest");
			npchar.quest.FDM_cabin = 10;
			npchar.quest.FDM_cabin.type = "Cabin_Huge";
			dialog.text = "Good, I will be waiting for a payment.";
			if (iTemp > 0)
			{
				link.l1 = "I have chests with me. Let's see. Here, "+FindRussianQtyString(iTemp)+".";
				link.l1.go = "FDM_cabin_pay";
			}
			else
			{
				link.l1 = "I have to go and put coins in the chests.";
				link.l1.go = "FDM_cabin_wait";
			}
		break;
		
		case "FDM_cabin_s1":
			iTemp = GetCharacterItem(pchar, "Chest");
			npchar.quest.FDM_cabin = 7;
			npchar.quest.FDM_cabin.type = "Cabin";
			dialog.text = "Good, I will be waiting for a payment.";
			if (iTemp > 0)
			{
				link.l1 = "I have chests with me. Let's see. Here, "+FindRussianQtyString(iTemp)+".";
				link.l1.go = "FDM_cabin_pay";
			}
			else
			{
				link.l1 = "I have to go and put coins in the chests.";
				link.l1.go = "FDM_cabin_wait";
			}
		break;
		
		case "FDM_cabin_wait":
			DialogExit();
			npchar.quest.FDM_full = "cabin";
		break;
		
		case "FDM_cabin_pay":
			iTemp = GetCharacterItem(pchar, "Chest");
			amount = sti(npchar.quest.FDM_cabin)-iTemp;
			Log_Info("You have given chests to Master Alexus");
			PlaySound("interface\important_item.wav");
			if (amount <= 0) // всё принес
			{
				RemoveItems(pchar, "chest", sti(npchar.quest.FDM_cabin));
				dialog.text = "So, you had to bring me "+FindRussianQtyString(sti(npchar.quest.FDM_cabin))+" chests, you have brought "+FindRussianQtyString(iTemp)+". I have the payment. Now it's my turn. Go and walk around. Don't worry, I'll do my best.";
				link.l1 = "Good...";
				link.l1.go = "FDM_cabin_do";
			}
			else
			{
				RemoveItems(pchar, "chest", iTemp);
				dialog.text = "So, you had to bring me "+FindRussianQtyString(sti(npchar.quest.FDM_cabin))+" chests, you have brought "+FindRussianQtyString(iTemp)+". "+FindRussianQtyString(amount)+" chests left.";
				link.l1 = "Very well, master.";
				link.l1.go = "FDM_cabin_wait";
				npchar.quest.FDM_cabin = amount;
			}
		break;
		
		case "FDM_cabin_do":
			DialogExit();
			SetLaunchFrameFormParam("Five days later..."+ NewStr() +"Master Alexus has done his job", "", 0, 5);
			WaitDate("", 0, 0, 5, 0, 10); //крутим время
			LaunchFrameForm();
			RefreshLandTime();
			RecalculateJumpTable();
			Whr_UpdateWeather();
			shTo = &RealShips[sti(Pchar.Ship.Type)];
			shTo.CabinType = npchar.quest.FDM_cabin.type;
			if (CheckAttribute(npchar, "quest.FDM_sails")) npchar.quest.FDM_full = "done";
			else DeleteAttribute(npchar, "quest.FDM_full");
		break;
		
		case "FDM_sails":
			dialog.text = "Sure, I can do that! Well-well... This means that we have to throw away every dirty old rag and place new and clear sails made of cotton. A lot of work to be done here. Hundred thousand pesos for work and materials. Deal?";
			if (sti(Pchar.money) >= 100000)
			{
				link.l1 = "Sure, I am fine with that. Deal!";
				link.l1.go = "FDM_sails_do";
			}
			link.l2 = "Hm. I suppose I need to think about it...";
			link.l2.go = "exit";
		break;
		
		case "FDM_sails_do":
			AddMoneyToCharacter(pchar, -100000);
			dialog.text = "Good. I have the coins, time to do my job. Walk around until it's done and don't worry.";
			link.l1 = "Good...";
			link.l1.go = "FDM_sails_done";
		break;
		
		case "FDM_sails_done":
			DialogExit();
			SetLaunchFrameFormParam("Two days later..."+ NewStr() +"Master Alexus has done his job", "", 0, 5);
			WaitDate("", 0, 0, 2, 0, 10); //крутим время
			LaunchFrameForm();
			RefreshLandTime();
			RecalculateJumpTable();
			Whr_UpdateWeather();
			SetShipSailsFromFile(pchar, "ships/parus_silk.tga");
			SetSailsColor(pchar, 0);//белый хлопковый парус
			npchar.quest.FDM_sails = "true";
			if (CheckAttribute(npchar, "quest.FDM_cabin")) npchar.quest.FDM_full = "done";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

void checkMatherial_repair(ref Pchar, ref NPChar, int good, int goodType)
{
	int amount;
	string Matherial = "Matherial" + goodType;
	amount = GetSquadronGoods(Pchar, good) - sti(NPChar.Repair.(Matherial));
	
	if (amount < 0)
    {
		amount = amount + sti(NPChar.Repair.(Matherial));
    }
    else
    {
		amount = sti(NPChar.Repair.(Matherial));
    }
    RemoveCharacterGoods(Pchar, good, amount);
    NPChar.Repair.(Matherial) = sti(NPChar.Repair.(Matherial)) - amount;
}

int GetMaterialQtyRepair( ref _chr, int MaterialNum )
{
	if ( sti(_chr.Ship.Type) == SHIP_NOTUSED) return 0;
	
	int   	shipCurHP   = sti(RealShips[sti(_chr.Ship.Type)].HP);
	int   	shipBaseHP	= sti(RealShips[sti(_chr.Ship.Type)].BaseHP);	
	int   	shipClass   = sti(RealShips[sti(_chr.Ship.Type)].Class);
	int     shipWeight  = CWT2Tonnes(sti(RealShips[sti(_chr.Ship.Type)].Weight));
	int     HPPrice     = shipWeight * (1.2 - makefloat(shipCurHP)/makefloat(shipBaseHP));
	int     modifier    = (2 * MOD_SKILL_ENEMY_RATE) + sti(RealShips[sti(_chr.Ship.Type)].MinCrew)/2 + 1;	

	float   fQuest 	= 1.0;
	if(CheckAttribute(&RealShips[sti(_chr.Ship.Type)], "QuestShip")) 
	{
		fQuest  = 1.3;
		HPPrice = HPPrice * 2;
	}					
	
	int     Matherial1 = makeint(fQuest * (10 + MOD_SKILL_ENEMY_RATE) * (6 - shipClass) / 2) + rand(modifier);
	int     Matherial2 = makeint(fQuest * (10 + MOD_SKILL_ENEMY_RATE) * (6 - shipClass) / 2) + rand(modifier);
	int     Matherial3 = makeint(fQuest * (10 + MOD_SKILL_ENEMY_RATE) * (6 - shipClass) / 2) + rand(modifier);
	int     Matherial4 = makeint(fQuest * (10 + MOD_SKILL_ENEMY_RATE) * (6 - shipClass) / 2) + rand(modifier);
		
	if(MaterialNum == 0) return HPPrice;	
	if(MaterialNum == 1) return Matherial1;
	if(MaterialNum == 2) return Matherial2;
	if(MaterialNum == 3) return Matherial3;
	if(MaterialNum == 4) return Matherial4;
	
	return 0;
}
