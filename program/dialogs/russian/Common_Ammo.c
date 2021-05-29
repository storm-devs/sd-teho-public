// диалог коменданта форта
void ProcessDialogEvent()
{
	int amount, iGunQty, iGunGoods, iGunPrice, iTemp;
	int iTest;
	ref NPChar, sld, location;
	ref arItem;
	ref rColony;
	aref Link, NextDiag;
	string sTemp;
	float locx, locy, locz;
	bool  ok;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

    // вызов диалога по городам -->
   /*NPChar.FileDialog2 = "DIALOGS\" + LanguageGetLanguage() + "\Prison\" + NPChar.City + "_Prison.c";
    if (LoadSegment(NPChar.FileDialog2))
	{
        ProcessCommonDialog(NPChar, Link, NextDiag);
		UnloadSegment(NPChar.FileDialog2);
	}*/
    // вызов диалога по городам <--

	switch(Dialog.CurrentNode)
	{
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	
		case "fight":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_group_Attack(NPChar, Pchar);
			if (rand(3) != 1) SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;

		case "NoMoreTalkExit":
			LAi_CharacterDisableDialog(npchar);
			DialogExit();
		break;
		
		case "First time":
			location = &Locations[FindLocation(pchar.location)];
			if (rand(4) == 4 && GetNpcQuestPastDayParam(location, "gun_date") > 365 && !CheckAttribute(pchar, "questTemp.PrisonGun"))
			{
				dialog.text = RandPhraseSimple(RandPhraseSimple("Listen, I have an important business to you. I do hope you'd be able to help.","Captain, may I interest you with one quite a profitable offer?"), RandPhraseSimple("I think that you could help us in one important affair.","Captain, I have a delicate offer for you, which could be quite profitable for both of us."));					
				link.l1 = "Well, speak your mind, and we'll see...";
				link.l1.go = "GiveTaskGun";
				location.quest.PrisonGun = "Target"; 
				SaveCurrentNpcQuestDateParam(location, "gun_date");
				break;
			}
		
			dialog.text = RandPhraseSimple("I am the commandant of the fort. What do you need here?", "What do you need? Why have you come here?");
			link.l1 = "Oh, nothing, just looking around the town and its vicinity. I came here just by a lucky chance.";
			link.l1.go = "exit";
			//Jason --> мини-квест Дефицитный товар
			if (CheckAttribute(pchar, "questTemp.Wine.bottle") && NPChar.location == pchar.questTemp.Wine.City + "_ammo" && GetQuestPastDayParam("questTemp.Wine_bottle") < 5)
			{
				link.l11 = "I have one interesting information for you, officer. One of your soldiers, "+pchar.questTemp.Wine.SName+" asked me to purchase wine in the town through my mediation. Considering your orders...";
				link.l11.go = "Wine_prison";
			}
			// <-- мини-квест Дефицитный товар
			// Карибские нравы
			if (CheckAttribute(pchar, "questTemp.Trial") && pchar.questTemp.Trial == "fraht" && NPChar.location == "portpax_ammo")
			{
				link.l11 = "Hello, officer. I came from the colony of Basse-Terre, from a man by the name of Gerard LeCroix. There is a cargo of gunpowder and bombs for you in my hold...";
				link.l11.go = "trial";
			}
			// Опасный груз -->
			if (pchar.location == "Cumana_Ammo")
			{
				if (pchar.questTemp.zpq != "begin" && pchar.questTemp.zpq != "failed" && pchar.questTemp.zpq != "completed")
				{
					link.l1 = "You look worried, officer. How can I help you?";
					link.l1.go = "zpq_prs1";
				}
				if (pchar.questTemp.zpq == "begin" && GetSquadronGoods(pchar, GOOD_POWDER) >= 50000 && GetQuestPastDayParam("pchar.questTemp.zpq") >= 7)
				{
					link.l2 = "I'm ready to report that the whole load of gunpowder is delivered. My ship is ready for unloading.";
					link.l2.go = "zpq_ex";
				}
				if (pchar.questTemp.zpq == "begin")
				{
					link.l3 = "I want to reject our gunpowder deal. This is too troublous.";
					link.l3.go = "zpq_fld2";
				}
			}
			// <-- Опасный груз
			NextDiag.TempNode = "First time";
		break;

		// --> Орудия для форта
		case "GiveTaskGun":
			dialog.Text = LinkRandPhrase("You see, the fort cannons are quite worn out. The treasury assigned funds to replace them, but I simply have no idea, where to purchase the new ones: there's simply no way to find them in our colony in the amount required. So, I thought that the guns from ships you'd boarded could be quite useful for us here.","I need to replace the gun battery of the fort. The funds have already been allocated, but, you know... It's just impossible to purchase the necessary amount in our colony.","I was tasked with the replacement of the worn fort cannons, but I just don't seem to be able to find enough anywhere.");
			Link.l1 = "Hmm... Can you go into a little bit more detail? Calibre, amount, price?";
			Link.l1.go = "GiveTaskGun_1";
			pchar.questTemp.PrisonGun = true;
			SaveCurrentQuestDateParam("pchar.questTemp.PrisonGun");
		break;
			
		case "GiveTaskGun_1":
			GetGunType();
			pchar.questTemp.PrisonGun.Sum = makeint(sti(pchar.questTemp.PrisonGun.Price)*sti(pchar.questTemp.PrisonGun.Qty));
			pchar.questTemp.PrisonGun.Luck = rand(4);
			pchar.questTemp.PrisonGun.Id = npchar.location;
			dialog.Text = "I need "+ pchar.questTemp.PrisonGun.Text +", in the amount of " + sti(pchar.questTemp.PrisonGun.Qty) + "  units exactly. I'll be paying in golden doubloons, "+ sti(pchar.questTemp.PrisonGun.Price) +" for a piece. That will amount to " + FindRussianDublonString(sti(pchar.questTemp.PrisonGun.Sum)) + " in total. What will you say? Oh, and one more thing - I will accept the entire batch, but no sooner than in a month - the money has not arrived yet.";
			Link.l1 = RandPhraseSimple("No, officer, your offer didn't interest me at all... I am sorry.","It's tempting, but I think I'm out. Allow me to keep my reasoning to myself.");
			Link.l1.go = "exit_gun";
			Link.l2 = RandPhraseSimple("Well, that offer is certainly an interesting one. Consider it a deal.","I guess I'll take it. It's not that hard and clearly profitable.");
			Link.l2.go = "GiveTaskGun_2";
		break;
			
		case "exit_gun":
			dialog.Text = "Such a pity, captain, I was counting on you. And... I do hope that this conversation stays inside the fort?";
			Link.l1 = "You don't have to remind me about that. Best  regards.";
			Link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.PrisonGun");
			NextDiag.TempNode = "First time";
		break;
			
		case "GiveTaskGun_2":
			dialog.Text = "Well, then that's a deal!  I am not restricting you to certain terms, but please, try not to prolong it over a half a year. And I hope, you understand that this is strictly confidential?";
			Link.l1 = "Of course I do. See you, commandant.";
			Link.l1.go = "exit";	
			ReOpenQuestHeader("PrisonGun");
			AddQuestRecord("PrisonGun", "1");
			AddQuestUserData("PrisonGun", "sSex", GetSexPhrase("",""));
			AddQuestUserData("PrisonGun", "sName", GetFullName(npchar));
			AddQuestUserData("PrisonGun", "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData("PrisonGun", "sQty", makeint(pchar.questTemp.PrisonGun.Qty));
			AddQuestUserData("PrisonGun", "sSum", makeint(pchar.questTemp.PrisonGun.Sum));
			AddQuestUserData("PrisonGun", "sText", pchar.questTemp.PrisonGun.Text);
			NextDiag.TempNode = "First time";
		break;	
		
		case "CheckGun":
			if (GetQuestPastDayParam("pchar.questTemp.PrisonGun") < 30)
			{
				dialog.Text = "I told you not to come sooner than in a month!";
				Link.l1 = "Damn it! I was so busy"+ GetSexPhrase("","") +", that I lost a"+ GetSexPhrase("","") +" track of time ... Sorry, I will come later, as agreed.";
				Link.l1.go = "exit";
				NextDiag.TempNode = "First time";
				break;
			}
			if (GetQuestPastDayParam("pchar.questTemp.PrisonGun") > 180)
			{
				dialog.Text = "Hmm... You know, it's been over half a year since the day we've stricken our 'deal'. I have already purchased the cannons. Did you really think that I'd be waiting for you forever?";
				Link.l1 = "Damn it! And what am I supposed to do with them now?";
				Link.l1.go = "TakeGun_late";
				break;
			}
			iGunGoods = pchar.questTemp.PrisonGun.Goods;
			amount = GetSquadronGoods(Pchar, iGunGoods) - sti(pchar.questTemp.PrisonGun.Qty);
			sTemp = sti(pchar.questTemp.PrisonGun.Qty);
			iTest = FindColony(NPChar.City); // город
			
			if (iTest != -1)
			{
				rColony = GetColonyByIndex(iTest);
			}
			ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
			if(sti(Pchar.Ship.Type) != SHIP_NOTUSED && ok)
			{
				dialog.Text = "Yes, are you ready to please me?";
				if (amount < 0)
				{
					Link.l1 = "No, still in progress. Just wanted to make sure that our deal still stands.";
					Link.l1.go = "exit";
				}
				else
				{
					Link.l1 = "I am. The entire batch is in the hold - "+ sTemp +" units, as was agreed upon.";
					Link.l1.go = "TakeGun";
				}
			}
			else 
			{
				dialog.text = "I don't see your ship in the harbor. Are you suggesting dragging those cannons through the jungle? Make fast to our harbor and come back.";
				link.l1 = "My ship is at the other side of the island. I'll take it to the port.";
				link.l1.go = "exit";
			}
		break;
		
		case "TakeGun":
			if (pchar.questTemp.PrisonGun.Luck == 4)
			{
				dialog.Text = RandPhraseSimple("You know, it's really awkward, but I have to denounce our deal. We've just had a financial inspection, and you know how scrupulous they are in such things. I just can't do anything. Sorry.","Captain, you know... Well, cannons have been sent to us from the metropolis, and I was forced to buy them out, of course. Extortionate prices, but... I am really sorry that I let you down... I don't feel good about it, either.");
				Link.l1 = "Damn it! And what am I supposed to do with them now?";
				Link.l1.go = "TakeGun_no";
			}
			else
			{
				dialog.Text = RandPhraseSimple("Excellent. I will sent a squad from the garrison to unload them.","Excellent. My soldiers will help you to unload the cannons.");
				Link.l1 = "Have you prepared the payment?";
				Link.l1.go = "TakeGun_1";
			}
		break;
		
		case "TakeGun_no":
			dialog.Text = "I don't know. Sell them at the shipyard, equip a trading vessel, sink them... I really have no idea. And please, don't tell anyone about this deal.";
			Link.l1 = "Oh, you say so! I just have no words!";
            Link.l1.go = "exit";
			AddQuestRecord("PrisonGun", "3");
			CloseQuestHeader("PrisonGun");
			DeleteAttribute(pchar, "questTemp.PrisonGun");
			NextDiag.TempNode = "First time";
		break;
		
		case "TakeGun_late":
			dialog.Text = "I have no idea. It's your problem. Sell them, throw them away, sink them - I really don't care.";
			Link.l1 = "Oh, that was simply a waste of time...";
            Link.l1.go = "exit";
			AddQuestRecord("PrisonGun", "4");
			AddQuestUserData("PrisonGun", "sSex", GetSexPhrase("ся","ась"));
			AddQuestUserData("PrisonGun", "sName", GetFullName(npchar));
			CloseQuestHeader("PrisonGun");
			DeleteAttribute(pchar, "questTemp.PrisonGun");
			NextDiag.TempNode = "First time";
		break;
		
		case "TakeGun_1":
			iGunGoods = pchar.questTemp.PrisonGun.Goods;
			amount = sti(pchar.questTemp.PrisonGun.Qty);
			iTemp = sti(pchar.questTemp.PrisonGun.Sum);
			dialog.Text = "Of course. Here is your gold - suit yourself.";
			Link.l1 = "Thanks! It was a pleasure doing business with you!";
            Link.l1.go = "TakeGun_2";
			TakeNItems(pchar, "gold_dublon", iTemp);
			Log_Info("You have received "+FindRussianDublonString(sti(pchar.questTemp.WPU.Escort.Money))+"");
			PlaySound("interface\important_item.wav");
			RemoveCharacterGoods(Pchar, iGunGoods, amount);
		break;
		
		case "TakeGun_2":
			dialog.Text = "The feeling is mutual. You've been very helpful. And, I beg you, keep that deal in this room.";
			Link.l1 = "Of course. Best wishes to you.";
            Link.l1.go = "exit";
			AddQuestRecord("PrisonGun", "2");
			AddQuestUserData("PrisonGun", "sSex", GetSexPhrase("","а"));
			CloseQuestHeader("PrisonGun");
			DeleteAttribute(pchar, "questTemp.PrisonGun");
			NextDiag.TempNode = "First time";
		break;
		// <-- орудия для форта

		//Jason --> мини-квест Дефицитный товар
		case "Wine_prison":
			dialog.text = "What?! I have strictly prohibited any drinking on the territory of the fort! Well, he will have to pay for this. I will deduct 1000 pesos from his payment and will hand them to you as a reward for your vigilance. And this guy will sit in detention for three days.";
			link.l1 = "Thank you, " + GetAddress_FormToNPC(NPChar) + ". Stopping such violations is our common duty.";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, 1000);
			ChangeCharacterComplexReputation(pchar,"nobility", -1); 
			DeleteAttribute(pchar, "questTemp.Wine.bottle");
			pchar.quest.Wine_Exchange.over = "yes";//снять прерывание
			sld = characterFromId(pchar.questTemp.Wine.id);
			sld.lifeday = 0;
			CloseQuestHeader("Wine");
			NextDiag.TempNode = "First time";
		break;
		// <-- мини-квест Дефицитный товар
		
		// Карибские нравы
		case "trial":
			iTest = FindColony(NPChar.City); // город
			if (iTest != -1)
			{
				rColony = GetColonyByIndex(iTest);
			}
			ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
			if(sti(Pchar.Ship.Type) != SHIP_NOTUSED && ok)
			{
				if (GetSquadronGoods(pchar, GOOD_BOMBS) < 2500 || GetSquadronGoods(pchar, GOOD_POWDER) < 2500)
				{
					dialog.text = "Hmm. But this batch is not full! How did it happen?";
					link.l1 = "Damn it! Please pardon me, it's my fault. I will immediately purchase the missing amount and will hand you in the entire batch, as we agreed.";
					link.l1.go = "exit";
				}
				else
				{
					dialog.text = "So you are our courier? Fine. Let's sort the things out with the cargo, and then you will receive further instructions.";
					link.l1 = "Okay.";
					link.l1.go = "trial_1";
				}
			}
			else
			{
				dialog.text = "I don't see your ship in the harbor. Are you suggesting dragging the cargo through the jungle? Make fast to our harbor and come back.";
				link.l1 = "My ship is at the other side of the island. I'll take it to the port.";
				link.l1.go = "exit";
			}
		break;
		
		case "trial_1":
			pchar.quest.Trial_FrahtFail.over = "yes"; //снять таймер
			dialog.text = "Alright, bombs and gunpowder, 2500 units each... Good. The soldiers will unload the cargo, your men can take a break. Here's your payment for the freight - five thousand pesos.";
			link.l1 = "Thanks! What should I do next? Monsieur LeCroix said...";
			link.l1.go = "trial_2";
		break;
		
		case "trial_2":
			AddMoneyToCharacter(pchar, 5000);
			RemoveCharacterGoods(pchar, GOOD_BOMBS, 2500);
			RemoveCharacterGoods(pchar, GOOD_POWDER, 2500);
			dialog.text = "Yes, yes, you will receive your instructions now. Are you ready to pay attention?";
			link.l1 = "Sure, officer.";
			link.l1.go = "trial_3";
		break;
		
		case "trial_3":
			dialog.text = "So. Our military ship 'Warlike' cruising near Spanish colony Porto Bello, it's the Southern part of Spanish Main. This vessel is under command of Florian Shoke. He is preparing an ambush of Spanish heavy galleon which is supposed to leave Porto Bello in two weeks\nProblem is, that our frigate's cannons are suffering from casting defect, we need to replace fifteen cannons in order to save the mission, otherwise the galleon will outnumber 'Warlike' in guns and men\nWithout the replacement, Florian Shoke will be forced to sail away with no result. Such cause of events is highly undesirable. Your task is to save the mission by delivering fifteen cannons in fourteen days.";
			link.l1 = "So, I need to take aboard fifteen cannons, head to Portobello, seek out frigate 'Militant' and hand over the cannons to captain Florian Shoke?";
			link.l1.go = "trial_4";
		break;
		
		case "trial_4":
			dialog.text = "Exactly. You got it right. Are you ready to take on this mission?";
			link.l1 = "What about payment?";
			link.l1.go = "trial_5";
			link.l2 = "I am sorry, officer, but I just don't want to get involved. Please excuse me.";
			link.l2.go = "trial_exit";
		break;
		
		case "trial_exit":
			dialog.text = "You're in your own right, but I was counting on your agreement. Now I'll have to find another courier, although I don't have much time left... Well, I am not keeping you any longer, captain.";
			link.l1 = "Best regards.";
			link.l1.go = "trial_exit_1";
		break;
		
		case "trial_exit_1":
			DialogExit();
			AddQuestRecord("Trial", "6");
			CloseQuestHeader("Trial");
			DeleteAttribute(pchar, "questTemp.Trial");
		break;
		
		case "trial_5":
			dialog.text = "Don't worry about that. Florian Shoke will pay you two hundred golden doubloons from the ship's treasury. Besides, I am certain that he'd want to use you and your ship for his own goals - with your consent, of course.";
			link.l1 = "Alright, I am on this mission! Where are the cannons?";
			link.l1.go = "trial_6";
		break;
		
		case "trial_6":
			dialog.text = "I will give an order to the soldiers to load them onto your ship immediately. Set sail as soon as you can, monsieur! Best of luck!";
			link.l1 = "Thanks. Luck will surely not hurt, and neither will tail wind...";
			link.l1.go = "trial_7";
		break;
		
		case "trial_7":
			DialogExit();
			AddQuestRecord("Trial", "7");
			pchar.questTemp.Trial = "cannon";
			SetFunctionTimerCondition("Trial_CannonFail", 0, 0, 14, false); // таймер
			SetCharacterGoods(pchar, GOOD_CANNON_24, GetCargoGoods(pchar, GOOD_CANNON_24)+15);
			EnemyNationHunterOnMap(true);//запуск перехватчиков
			pchar.quest.Trial_cannon.win_condition.l1 = "location";
			pchar.quest.Trial_cannon.win_condition.l1.location = "Portobello";
			pchar.quest.Trial_cannon.function = "Trial_CreateFlorianFrigate";
		break;
		
		// Опасный груз -->
		case "zpq_prs1":
			if(!isBadReputation(pchar, 70))
			{
				dialog.text = "Hm, perhaps. Well, because of your good reputation, I'll take my chances to trust you. In other case I wouldn't even talk about it with you. Thing is, that we need a quite large batch of a special cargo, so you will need a large load vessel and a will to risk. Also, you must give me a word not to tell anybody about it\nIf you find it embarrassing then tell me about it right now. I thing that I have made my point...";
				link.l1 = "Sounds intriguing. I am in if the payment is fine, though I have no idea what cargo you are talking about. You have my word anyway.";
				link.l1.go = "zpq_prs2";
				link.l2 = "I'd say no, I suppose... if I would give you my word I had to do work which seems quite troublous. I won't do this.";
				link.l2.go = "zpq_fld";
			}
			else
			{
				dialog.text = "Your reputation is unacceptable for me. I ask you to leave the room. We are able to solve our problems by ourselves.";
				link.l1 = "Whatever, solve them then...";
				link.l1.go = "exit";
			}		
		break;
		
		case "zpq_fld":
			dialog.text = "Well, at least you've rejected in honest way... I'm not keeping you anymore.";
			link.l1 = "Farewell.";
			link.l1.go = "exit";
			pchar.questTemp.zpq = "failed";
		break;
		
		case "zpq_fld2":
			dialog.text = "Hm, actually I didn't expect that from you. I have to ask you to leave... And remember about your promise to not divulge any information.";
			link.l1 = "I am sorry...";
			link.l1.go = "exit";
    		ChangeCharacterComplexReputation(pchar,"nobility", -10);
			if (pchar.questTemp.zpq == "begin")
			{
				AddQuestRecord("zpq", "6");
				AddQuestUserData("zpq", "sSex", GetSexPhrase("","а"));
				CloseQuestHeader("zpq");
			}
			pchar.questTemp.zpq = "failed";
		break;
		
		case "zpq_prs2":
			dialog.text = "Splendid. The problem is that the recent storm has damaged our gun powder's supply in our fort's arsenal. I hope that I don't need to explain you that we have a delicate trouble here. In case of a long siege the fort won' be able to do anything. We won't last long.";
			link.l1 = "Now I see. What cargo do you need. And what the amount?";
			link.l1.go = "zpq_prs3";
		break;
		
		case "zpq_prs3":
			dialog.text = "We need 50 000 gunpowder barrels. I will pay you 300 000 pesos... You must understand that it's a very good price. Our current state forces me to go with such costs though it was troubling to convince the governor's purser to that... The storm season won't allow us to use our own supply lines and we don't want everyone to know about this trouble...";
			link.l1 = "I see... the price is really nice. You've mentioned risks...";
			link.l1.go = "zpq_prs4";
		break;
		
		case "zpq_prs4":
			dialog.text = "I meant that such a large amount of gunpowder can be very dangerous while the transportation. I have seen a few explosions with my own eyes, sometimes a single spark can do the job. But if you face the storm... The whole convoys usually keep a distance from the potential brander. If it explodes, then everyone is dead!";
			link.l1 = "I see... But I always keep my word, consider it's done.";
			link.l1.go = "zpq_prs5";
			link.l2 = "Well, senor... You've been telling me such terrible things so I have lost any wish to do that job.";
			link.l2.go = "zpq_fld2";
		break;
		
		case "zpq_prs5":
			dialog.text = "Good, I am very glad that we made a deal. I will pay you as soon as you bring me the cargo\nI will have money in a week, not earlier, so take your time but I'd ask you to try not to delay too much.";
			link.l1 = "I understand, senor. I am on it.";
			link.l1.go = "zpq_prs5_ok";
		break;
		
		case "zpq_prs5_ok":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			pchar.questTemp.zpq = "begin";
			pchar.questTemp.zpq.time = 20;
			AddQuestRecord("zpq", "1");
			AddQuestUserData("zpq", "sSex", GetSexPhrase("","а"));
			SaveCurrentQuestDateParam("pchar.questTemp.zpq");
		break;
		
		case "zpq_ex":
			dialog.text = "At last! I thought that you've already forgotten about our deal. I will immediately order my soldiers to start unloading your ship. Working with gunpowder is a very delicate business, ha-ha!";
			link.l1 = "It is great, senor, but I have to remind of payment.";
			link.l1.go = "zpq_ex2";
			RemoveCharacterGoods(pchar, GOOD_POWDER, 50000);
			AddCharacterExpToSkill(pchar, "Sailing", 500);
			AddCharacterExpToSkill(pchar, "Fortune", 500);

            pchar.quest.zpq_sld1_fc.win_condition.l1 = "location";
            pchar.quest.zpq_sld1_fc.win_condition.l1.location = "Cumana_ExitTown";
            pchar.quest.zpq_sld1_fc.function = "zpq_sld1_fc";
		break;
		
		case "zpq_ex2":
			dialog.text = "Yes, of course. You will be paid 150 000 pesos as we agreed.";
			link.l1 = "You're probably kidding me, senor?! We had a deal on 300 000 pesos!";
			link.l1.go = "zpq_ex3";
			link.l2 = "I am starting to think that you are going to cheat on me so I won't go away from here without my 450 000 pesos!";
			link.l2.go = "zpq_ex4";
			link.l3 = "Hm.. I see that the circumstances have changed. Well, I'd better take money and leave...";
			link.l3.go = "zpq_ex5";
		break;
		
		case "zpq_ex3":
			if (GetSummonSkillFromName(pchar, "Leadership") > 50)
			{
				dialog.text = "Ah, yes... Exactly! 300 000 pesos. I have forgotten, pardon me. It's my age to be blamed, sclerosis you know... Sure, here are your coins. It was a pleasure to have a business with you, captain. Now I am sorry but I've got a lot of work to do...";
				link.l1 = "The same to you, senor. See you.";
				link.l1.go = "exit";
				pchar.questTemp.zpq = "completed";
            	AddQuestRecord("zpq", "2");
				AddQuestUserData("zpq", "sSex", GetSexPhrase("","а"));
				CloseQuestHeader("zpq");
				pchar.questTemp.zpq.sum = 300000;
				AddMoneyToCharacter(pchar, makeint(pchar.questTemp.zpq.sum));
			}
			else
			{
				dialog.text = "What?! Take your money and get lost or you will rot in this casemate!";
				link.l1 = "You are such a liar, senor! I advice you to give me my money in a good way or I will take away the cargo!";
				link.l1.go = "zpq_ex_agry";
				link.l2 = "Pardon me... Fine, I'll take the sum you offer and we are done.";
				link.l2.go = "zpq_ex5";
			}
		break;
		
		case "zpq_ex4":
				dialog.text = "Such a rudeness! I am not mentally diseased and I precisely remember offering 300 000 pesos\nЕDamn it! I'm not gonna play your games!";
				link.l1 = "Calm down. Think about the ready brander filled with gunpowder right in front of your fort. If say just a word, your fort will turn into the ruins.";
				link.l1.go = "zpq_ex6";
		break;
		
		case "zpq_ex6":
			if (GetSummonSkillFromName(pchar, "Leadership") > 75)
			{
				dialog.text = "Hm-Hm... strong argument. 450 000 pesos, you say? Here take them and pardon me now but I have a work to do...";
				link.l1 = "Farewell, senor. See you.";
				link.l1.go = "exit";
				pchar.questTemp.zpq = "completed";
            	AddQuestRecord("zpq", "5");
				CloseQuestHeader("zpq");
				pchar.questTemp.zpq.sum = 450000;
				AddMoneyToCharacter(pchar, makeint(pchar.questTemp.zpq.sum));
			}
			else
			{
				dialog.text = "What?! I am a military officer! You thought that you can scare me, kid?! Guards, take "+ GetSexPhrase("him","her") +"!";
				link.l1 = "Good luck in trying, rats of casemates...";
				link.l1.go = "zpq_ex_war";
			}
		break;
		
		case "zpq_ex5":
			dialog.text = "Splendid! You have made the right choice. Take you coins and goodbye. It was a pleasure!";
			link.l1 = "Farewell...";
			link.l1.go = "exit";
			pchar.questTemp.zpq = "completed";
            AddQuestRecord("zpq", "3");
			AddQuestUserData("zpq", "sSex", GetSexPhrase("","а"));
			CloseQuestHeader("zpq");
			pchar.questTemp.zpq.sum = 150000;
			AddMoneyToCharacter(pchar, makeint(pchar.questTemp.zpq.sum));
		break;
		
		case "zpq_ex_agry":
			dialog.text = "Ah you bastard! Guards, take "+ GetSexPhrase("him","her") +"!";
			link.l1 = "Argh! It seems that I have to take my money from your breathless body...";
			link.l1.go = "zpq_ex_war";
		break;
		
        case "zpq_ex_war":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_SetFightMode(PChar, true);
			Flag_PIRATE();
			pchar.questTemp.zpq = "failed";
            AddQuestRecord("zpq", "4");
			CloseQuestHeader("zpq");
			pchar.questTemp.zpq.sum = 150000;
			AddMoneyToCharacter(npchar, makeint(sti(pchar.questTemp.zpq.sum)*2 + rand(5000)));
			GiveItem2Character(npchar, "blade_21");
			EquipCharacterbyItem(npchar, "blade_21");
			npchar.SaveItemsForDead  = true;
			npchar.DontClearDead = true;
			npchar.cirassId = Items_FindItemIdx("cirass3");
			chrDisableReloadToLocation = true;
			string slai_group = GetNationNameByType(sti(npchar.nation))  + "_citizens";
			LAi_group_AttackGroup(slai_group, LAI_GROUP_PLAYER);
			LAi_group_SetCheck(slai_group, "OpenTheDoors");
			AddSimpleRumour("Such things happen here!! They say that some prisoner has escaped from the casemates! He slaughtered all the guards, stole the treasury, and just went away! Wow!", SPAIN, 5, 1);
		break;
		// <-- Опасный груз
	}
}

void GetGunType()
{
	int iGunType;
	if(makeint(pchar.rank) < 6) iGunType = rand(1);	//18&&24
	if(makeint(pchar.rank) >= 6 && makeint(pchar.rank) < 15) iGunType = rand(2); //24&&32	
	if(makeint(pchar.rank) >= 15 && makeint(pchar.rank) < 24) iGunType = rand(2)+2; //32&&36&&42
	if(makeint(pchar.rank) >= 24) iGunType = 5-rand(1); //36clv&&42
	int iAdd = makeint(GetSummonSkillFromName(pchar, SKILL_COMMERCE)/20);
	
	switch (iGunType)
	{
		case 0:  
			pchar.questTemp.PrisonGun.Goods = GOOD_CANNON_24;     					
			pchar.questTemp.PrisonGun.Price = 28 + iAdd;
			pchar.questTemp.PrisonGun.Qty = sti(pchar.rank)*5+25+rand(sti(pchar.rank));
			pchar.questTemp.PrisonGun.Text = "24 calibre cannons";
		break; 
		case 1:  
			pchar.questTemp.PrisonGun.Goods = GOOD_CULVERINE_18;     					
			pchar.questTemp.PrisonGun.Price = 25 + iAdd;
			pchar.questTemp.PrisonGun.Qty = sti(pchar.rank)*5+25+rand(sti(pchar.rank));
			pchar.questTemp.PrisonGun.Text = "couleuvrines";
		break; 
		case 2:  
			pchar.questTemp.PrisonGun.Goods = GOOD_CANNON_32;     					
			pchar.questTemp.PrisonGun.Price = 32 + iAdd;
			pchar.questTemp.PrisonGun.Qty = sti(pchar.rank)*3+15+rand(sti(pchar.rank));
			pchar.questTemp.PrisonGun.Text = "32 calibre cannons";
		break; 
		case 3:  
			pchar.questTemp.PrisonGun.Goods = GOOD_CANNON_36;     					
			pchar.questTemp.PrisonGun.Price = 36 + iAdd;
			pchar.questTemp.PrisonGun.Qty = sti(pchar.rank)*3+15+rand(sti(pchar.rank));
			pchar.questTemp.PrisonGun.Text = "36 calibre cannons";
		break;
		case 4:  
			pchar.questTemp.PrisonGun.Goods = GOOD_CULVERINE_36;     					
			pchar.questTemp.PrisonGun.Price = 49 + iAdd;
			pchar.questTemp.PrisonGun.Qty = sti(pchar.rank)+15+rand(sti(pchar.rank));
			pchar.questTemp.PrisonGun.Text = "full couleuvrines";
		break; 
		case 5:  
			pchar.questTemp.PrisonGun.Goods = GOOD_CANNON_42;     					
			pchar.questTemp.PrisonGun.Price = 40 + iAdd;
			pchar.questTemp.PrisonGun.Qty = sti(pchar.rank)+20+rand(sti(pchar.rank));
			pchar.questTemp.PrisonGun.Text = "42 calibre cannons";
		break; 
	}
}
