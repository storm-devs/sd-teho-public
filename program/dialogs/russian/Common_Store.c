// boal 08/04/04 общий диалог торговцев
#include "DIALOGS\russian\Rumours\Common_rumours.c"  //homo 25/06/06

void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	

	string iDay, iMonth, sTemp, sMoney, attrL;
	
	iDay = environment.date.day;
	iMonth = environment.date.month;
	string lastspeak_date = iday + " " + iMonth;
	
	int iMoney, iQuantityGoods, iTradeGoods, iTmp;
	
	bool  ok;

	int iTest, cn, i;
	iTest = FindColony(NPChar.City); // город магазина
	ref rColony, chref;
	
	if (iTest != -1)
	{
		rColony = GetColonyByIndex(iTest);
	}
	
	int iSeaGoods = LanguageOpenFile("ShipEatGood.txt"); // нужно заменить на GetGoodsNameAlt(idx)

	if(!CheckAttribute(npchar, "quest.trade_date"))
	{
		npchar.quest.trade_date = "";
	}
    
	// вызов диалога по городам -->
	NPChar.FileDialog2 = "DIALOGS\" + LanguageGetLanguage() + "\Store\" + NPChar.City + "_Store.c";
	if(LoadSegment(NPChar.FileDialog2))
	{
		ProcessCommonDialog(NPChar, Link, NextDiag);
		UnloadSegment(NPChar.FileDialog2);
	}
	
	// вызов диалога по городам <--
	ProcessCommonDialogRumors(NPChar, Link, NextDiag);//homo 25/06/06
	
	string attrLoc   = Dialog.CurrentNode;
	
	if(HasSubStr(attrLoc, "TransferGoodsTo_"))
	{
		NPChar.CharToTransferGoodsID = FindStringAfterChar(attrLoc, "_");
		Dialog.CurrentNode = "TransferGoods_Start";
	}
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (LAi_grp_playeralarm > 0)
			{
				dialog.text = NPCharRepPhrase(pchar, 
					LinkRandPhrase("Alarm is raised in the town, and everyone is looking for you. If I were you, I wouldn't stay there.", "All the city guards are scouring the town looking for you. I am not a fool and I will not talk to you!", "Run, "+ GetSexPhrase("buddy","lass") +", before the soldiers turned you into a sieve..."), 
					LinkRandPhrase("What do you need, "+ GetSexPhrase("scoundrel","rascal") +"?! The city guards have already hit your scent, you won't get far, "+ GetSexPhrase("filthy pirate","murderous filth") +"!", "Filthy murderer, leave my house at once! Guards!", "I don't fear you, "+ GetSexPhrase("creep","stinker") +"! Soon you will be hanged in our fort, you won't get far..."));
				link.l1 = NPCharRepPhrase(pchar,
					RandPhraseSimple("Heh, an alarm is never a problem for me...", "They will never get me."), 
					RandPhraseSimple("Shut your fucking mouth, " + GetWorkTypeOfMan(npchar, "") + ", or I'll rip your filthy tongue!!", "Heh, " + GetWorkTypeOfMan(npchar, "") + ", and all there - to catch pirates! That's what I tell you, buddy: sit quietly and you will not die..."));
				link.l1.go = "fight";
				break;
			}
			if (sti(pchar.GenQuest.Piratekill) > 20 && sti(npchar.nation) == PIRATE)
			{
				dialog.text = RandPhraseSimple("And it's you, bastard! Do you think you are here looking forward to? Certainly not! Guys! To arms! Cut the psycho!", "Buy something you want, you beast? But no! Now show you what's what! Guys, here sick crazy weapons! Alert!");
				link.l1 = RandPhraseSimple("Huh? What?", "Uh, why are you doing this?");
				link.l1.go = "fight";
				bDisableFastReload = true;//закрыть переход
				pchar.quest.pirate_in_town.win_condition.l1 = "ExitFromLocation";
				pchar.quest.pirate_in_town.win_condition.l1.location = pchar.location;
				pchar.quest.pirate_in_town.function = "TownPirate_battle";
				break;
			}
			//--> Jason Бремя гасконца
			if (CheckAttribute(pchar, "questTemp.Sharlie.Lock"))
			{
				//Jason --> мини-квест Дефицитный товар
				if (CheckAttribute(pchar, "questTemp.Wine.Trader") && NPChar.location == pchar.questTemp.Wine.City + "_store" && !CheckAttribute(pchar, "questTemp.Wine.fail"))
				{
					link.l13 = "I'd like to purchase from you a batch of European wine - fifty-sixty bottles. I was told that you had enough of it in stock."; 
					link.l13.go = "Wine_Trader";
				}
				if (CheckAttribute(pchar, "questTemp.Wine.Repeat2") && NPChar.location == pchar.questTemp.Wine.City + "_store" && CheckCharacterItem(pchar, "letter_1") && !CheckAttribute(pchar, "questTemp.Wine.fail"))
				{
					link.l13 = "Hello again. Please take a look at this letter - perhaps, you would reconsider your position regarding selling wine to me?"; 
					link.l13.go = "Wine_Repeat2";
				}
				if (CheckAttribute(pchar, "questTemp.Wine.wait") && NPChar.location == pchar.questTemp.Wine.City + "_store" && !CheckAttribute(pchar, "questTemp.Wine.fail"))
				{
					link.l13 = "That's me again. Can we resume our interrupted wine deal? I managed to raise enough money."; 
					link.l13.go = "Wine_Price";
				}
				// <-- мини-квест Дефицитный товар
				dialog.text = "Did you want to buy something, monsieur?";
				Link.l1 = "Of course, I did - what else the stores are for? Show me your wares.";
				Link.l1.go = "trade_1";
				Link.l2 = "I come for a particular business purpose...";
				Link.l2.go = "quests";
				Link.l3 = "I am sorry, but I have to go.";
				Link.l3.go = "exit";
				break;
			}			
			//<-- Бремя гасконца
			
			// Warship, 29.05.11. Дело чести - трусливый фехтовальщик.
			if(CheckAttribute(PChar, "QuestTemp.AffairOfHonor.CowardFencer.CanTraderTalk"))
			{
				dialog.text = "Captain, thanks for saving me.";
				Link.l1 = "Oh, you're welcome.";
				Link.l1.go = "exit";
				DeleteAttribute(PChar, "QuestTemp.AffairOfHonor.CowardFencer.CanTraderTalk");
				break;
			}
			// Карибские нравы
			if(CheckAttribute(npchar, "quest.trial_usurer"))
			{
				dialog.text = "What's up, captain? Have you lost something? Why are you running around in my shop like that?";
				Link.l1 = "Well, imagine that - I actually have! Where is that cursed Gerard LeCroix? I have fulfilled all tasks given to me by Florian Shoke, and, may the shark swallow me whole, I had a damn hard time doing that! And now, when I come to collect my reward, it turns out that this bird is flown!";
				Link.l1.go = "trial";
				break;
			}
			
            dialog.Text = GetNatPhrase(npchar, LinkRandPhrase("Nice to meet you, sir! Are you new to these places?","Welcome, captain! My store is at your service, sir.","Sir, please come in! I am happy to offer you the very best wares you can buy on this archipelago."), LinkRandPhrase("Oh, monsieur captain! The best wares in all the French colonies - right here and now and exclusively for you!","What a nice meeting, monsieur! The best shop offering the best French wares - at your service!","Have we met before, monsieur captain? You know, my shop is as fine as the best stores in the mother country!"), LinkRandPhrase("Oh! Senor captain! I am so glad to see you in my store!","I am happy to greet such a brilliant caballero in the best store of all Spanish colonies!","Oh, noble hidalgo! Fate itself has brought you to my humble shop! Here you will find whatever you might want!"),LinkRandPhrase("Good afternoon, mynheer captain. Is this your first visit here?","Hello, mynheer. Have you come here for the first time? I assure you that the quality of our Dutch goods will pleasantly surprise you!","Please come in, mynheer captain! The very best wares at the lowest prices available - that's the Dutch way of commerce!"));
			Link.l1 = LinkRandPhrase("Nice to meet you, too. My name is "+GetFullName(pchar)+" and I am rather new to these places. Well, show me the riches of the archipelago!","Nice to meet you, too. I am "+GetFullName(pchar)+". captain of the ship '"+pchar.ship.name+"'. So, what are the hot deals?",""+GetFullName(pchar)+", captain of ship '"+pchar.ship.name+"', nice meeting you. So, what can you offer me?");
			link.l1.go = "node_1";
			NextDiag.TempNode = "Second time";
		break;

		case "second time":
			if (LAi_group_GetPlayerAlarm() > 0)
			{
       			dialog.text = NPCharRepPhrase(pchar, 
					LinkRandPhrase("Alarm is raised in the town, and everyone is looking for you. If I were you, I wouldn't stay there.", "All the city guards are scouring the town looking for you. I am not a fool and I will not talk to you!", "Run, "+ GetSexPhrase("buddy","lass") +", before the soldiers turned you into a sieve..."), 
					LinkRandPhrase("What do you need, "+ GetSexPhrase("scoundrel","rascal") +"?! The city guards have already hit your scent, you won't get far, "+ GetSexPhrase("filthy pirate","murderous filth") +"!", "Filthy murderer, leave my house at once! Guards!", "I don't fear you, "+ GetSexPhrase("creep","stinker") +"! Soon you will be hanged in our fort, you won't get far..."));
				link.l1 = NPCharRepPhrase(pchar,
					RandPhraseSimple("Heh, an alarm is never a problem for me...", "They will never get me."), 
					RandPhraseSimple("Shut your mouth, " + GetWorkTypeOfMan(npchar, "") + ", or I'll rip your filthy tongue!", "Heh, " + GetWorkTypeOfMan(npchar, "") + ", and all there - to catch pirates! That's what I tell you, buddy: sit quietly and you will not die..."));
				link.l1.go = "fight";
				break;
			}
            
			//--> Jason, Сомнительное предложение
			if (CheckAttribute(pchar, "GenQuest.Contraoffer.Trader.busy"))
			{
				dialog.text = "Please, excuse me, but I have no time for you now.";
				link.l1 = "Yes, sure. I'll drop in some other time, then.";
				link.l1.go = "exit";
				break;
			}
			//<-- Сомнительное предложение
            
			// Warship, 29.05.11. Дело чести - трусливый фехтовальщик.
			if(CheckAttribute(PChar, "QuestTemp.AffairOfHonor.CowardFencer.CanTraderTalk"))
			{
				dialog.text = "Captain, thanks for saving me.";
				Link.l1 = "Oh, you're welcome.";
				Link.l1.go = "exit";
				DeleteAttribute(PChar, "QuestTemp.AffairOfHonor.CowardFencer.CanTraderTalk");
				break;
			}
			// Карибские нравы
			if(CheckAttribute(npchar, "quest.trial_usurer"))
			{
				dialog.text = "What's up, captain? Have you lost something? Why are you running around in my shop like that?";
				Link.l1 = "Well, imagine - I actually have! Where is that cursed Gerard LeCroix? I have fulfilled all tasks given to me by Florian Shoke, and, may the shark swallow me in whole, I had a damn hard time doing that! And now, when I come to collect my reward, it turns out that this bird is flown!";
				Link.l1.go = "trial";
				break;
			}
            
			dialog.Text = pcharrepphrase(LinkRandPhrase(LinkRandPhrase("Oh, look who's there! Well, as they say, money has no smell, so come in, captain, and let's trade...","I cannot say that I am glad to see you, "+GetFullName(pchar)+"... But I can still trade with you.","He-he... Well, I would not invite you to my home, captain - but my shop is still at your service."),LinkRandPhrase("Oh, look who's there! Isn't that "+GetFullName(pchar)+"! Wanna trade or just take some stuff for free? Hey, just kidding...","Can't say that I am glad to see you here, "+GetAddress_Form(NPChar)+". But if you have money to spend - come in, come in...","Wanna trade, captain "+GetFullName(pchar)+"? If so, could you please be quick about it? Other customers are shunning you, and this is bad for my business,"),LinkRandPhrase("Wanna trade, mynheer? Just a second, I will cash up - you know, there are dubious types around... Of course, I don't mean you, captain!","If I saw you in the open sea, "+GetAddress_Form(NPChar)+", I would likely order to add sails... But here, in my shop, I can offer you to trade.","Cap, I will warn you right away: if the fabric is stained with blood and coffee stinks with gunpowder, I won't take it. Otherwise take a look and make your pick.")),LinkRandPhrase(LinkRandPhrase("And I am glad to greet you again, "+GetAddress_Form(NPChar)+"! Buying or seling - I am always happy to help you.","I beg you, "+GetAddress_Form(NPChar)+", come in! I am always happy to see my favourite customer here. What will it be this time - buying or selling?","Oh, "+GetAddress_Form(NPChar)+" "+GetFullName(pchar)+"! I am so happy to see you again! What will it be this time - buying or selling?"),LinkRandPhrase("Do you like our wares, "+GetAddress_Form(NPChar)+" "+GetFullName(pchar)+"? I am always at your service - take a look and make your pick.","Hello, "+GetAddress_Form(NPChar)+" "+GetFullName(pchar)+". I am glad to see you again! Wanna take a look at the assortment of our wares?","Glad to see you, captain! I knew that you would like our quality goods. Wanna take a look at what's new?"),LinkRandPhrase("Oh, "+GetAddress_Form(NPChar)+" "+GetFullName(pchar)+"! Please come in! All the wares just for you - and with great discounts on that occasion!","Captain "+GetFullName(pchar)+", once again you've made me happy with your visit! Please, make your pick, whatever you like!","What would you like this time, captain? I am glad that you still remember how to find me. We have all the wares you might need - the very best quality!")));
			Link.l1 = pcharrepphrase(RandPhraseSimple(RandPhraseSimple("That's how you're welcoming me, buddy? Well, I'll remember that if we meet at the sea... Stop trembling, I was just kidding. Show me what you've got.","Alright, buddy. I might need your wares, but I positively don't need your tongue. Can you hold it or you will need help with that? Shut up and show me your wares."),RandPhraseSimple("Let's get closer to business, huckster. I have no time to discuss morale issues with you, so let's just trade like decent people.","Hold your horses, buddy. Kidding is fine, but keep in mind that I can get angry... So stop irritating me and just show me your wares.")),RandPhraseSimple(RandPhraseSimple("Always happy to visit you, buddy. What do you have in stock that would be worth my attention?","Always good to see you, buddy. So, what's new is there for sea wanderers who hadn't been on dry land for months?"),RandPhraseSimple("And once again I am in "+XI_ConvertString("Colony"+npchar.City+"Acc")+"! Glad I was not here to forget. But left in your warehouses or something for me everything is sorted out?","How could you not come? You always pleases me than that. Well, what have you got there?")));
			link.l1.go = "node_1";
			NextDiag.TempNode = "Second time";
		break;

		case "node_1":
			dialog.text = NPCStringReactionRepeat(NPCharRepPhrase(npchar,
			                                         pcharrepphrase(RandPhraseSimple("All hands on deck! ","Hold inspection! ") +LinkRandPhrase("What does a "+ GetSexPhrase("gentleman","gentleman, oh, pardon me - a lady") +" of fortune need in my store, he-he?",
													                                 "What a surprise for a poor old shopkeeper! He-he!", "So, what fair wind has brought you to my shop?"),
            														LinkRandPhrase("Open the ports!", "Hooks to the side!","Sail straight ahead!")+RandPhraseSimple(" Here you will find"," My shop has")
																	+LinkRandPhrase(" the best prices on the entire island."," excellent assortment of goods."," goods of the best quality available.")
																	+RandPhraseSimple(" I am at your service"," Whatever you want")+", captain!"),
													 pcharrepphrase(RandPhraseSimple("Any goods for "+ GetSexPhrase("gentlemen","gentlemen and ladies") +" of fortune! He-he! Until they are hanged to dry in the sun!",
													                                 "The wind swings the hanged in the port and carries the clank of the chains. But money has no smell, has it?"),
                 												"Would you like to " +LinkRandPhrase("buy the best wares of " + NationNameGenitive(sti(NPChar.nation)),"buy or sell your cargo", "get a profitable freight?")
																	+RandPhraseSimple("? I am at your service!","? My store is at your service!")
																	+RandPhraseSimple(" Glad to see you"," Suit yourself") +", captain!")),
				                                  NPCharRepPhrase(npchar,
												  	 pcharrepphrase("If you want my advice, cap - don't spare money on grapeshot. You know, the dead are much easier to search!",
													                "I have noticed right away that you're an "+ GetSexPhrase("artful buddy","artful lass") +". " +RandPhraseSimple("But now I can see that you're a real "+ GetSexPhrase("hero","daredevil") +".", "You're young, but "
																	+RandPhraseSimple("you keep your wits with you.", "you certainly cannot be tricked easily."))),
													 pcharrepphrase("I am willing to buy from you all cargo from the captured prizes. Whaa by silver or gold? That stuff is always pricey.",
													                "Commercial seafaring is a profitable business, captain " + GetFullName(pchar)+", isn't it?")),
												  NPCharRepPhrase(npchar,
												     RandPhraseSimple("We wrapped 'em all in a mains'l tight With twice ten turns of a hawser's bight And we heaved 'em over and out of sight! " ,
													   RandPhraseSimple("Fifteen men on a dead man's chest!","Drink and the devil had done for the rest!") +" Yo ho ho and a bottle of rum! ")
													   +RandPhraseSimple("What's up, cap?", "Looking to buy something, captain?"),
													 pcharrepphrase("I see you're quite a haggler, captain " + GetFullName(pchar)+". Since you are a returning customer, I am offering you very good prices!",
													                "Alright, captain " + GetFullName(pchar)+", out of deference to you I can bate just a little bit more! What would you like?")),
												  NPCharRepPhrase(npchar,
												     "I swear, talking to you is sickening me. "
													 +LinkRandPhrase("Buy a couple of peanuts. Pigs are fond of that stuff. ","You expect someone to polish your boots with rum here? ",
													 pcharrepphrase("I know your type. Get loaded with rum - and straight to the gallows.","I wonder how you mother allowed you to become a sailor! A sailor! You would make a much better tailor...")),
													 pcharrepphrase(RandPhraseSimple("I thought that ","I hoped that ")+RandPhraseSimple("you had left our island for good.","I would never see you again.")
													 +RandPhraseSimple(" The dead are handing on your neck like millstones..."," Just how many sailors have you left t rot among the corals?!"),
													 "Captain " + GetFullName(pchar)+", your passion for commerce has exceeded all my expectations!"
													 +RandPhraseSimple(" Wanna make last-minute purchases before setting sail?", " Are you looking for something special?"))),
										"cycle", 10, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(NPCharRepPhrase(npchar,
			                                        pcharrepphrase("Show me what you've got, you old pirate!",
													               "I just wanted to take a look at your wares, my good man."),
													pcharrepphrase("I swear by the gallows, " +GetFullName(npchar)+", I will not let you to put me on! Show me your wares right now!",
													               "Let's take a look at your goods, " +GetAddress_FormToNPC(NPChar)+ ".")),
											   NPCharRepPhrase(npchar,
											        pcharrepphrase("That's for sure! The dead ones won't bite! Now, what do you have in your hold?",
													               "You better get to your business, my good man. What kind of wares can you offer me?"),
												    pcharrepphrase("There will come a day when you become my prize, he-he. Just kidding. Show me your wares.",
													               "Let's discuss our commercial affairs, " +GetAddress_FormToNPC(NPChar)+ " " +GetFullName(npchar)+ "")),
											   NPCharRepPhrase(npchar,
											        pcharrepphrase("What do I want? I want to buy something!",
													               "Drinking will bring you to your grave, " +GetFullName(npchar)+ ". I want to take a look at your wares."),
												    pcharrepphrase("I know your discounts! Two pounds of cacao at the price of three! Now show me your wares.",
													               "That's always good. Let's haggle, then.")),
											  "Show me your wares. Least said, soonest mended. I am in a hurry.",
											  npchar, Dialog.CurrentNode);
			link.l1.go = "market";
			link.l2 = HeroStringReactionRepeat(NPCharRepPhrase(npchar,
			                                        pcharrepphrase("Oh, I'd really like to stab someone, Alright, let's get down to business.",
													               "Let's get down to other business, my good man."),
													pcharrepphrase("Caramba! I am here with a different business!",
													               "I want to talk to you about a particular business, "+GetAddress_FormToNPC(NPChar)+" " +GetFullName(npchar)+".")),
											   NPCharRepPhrase(npchar,
											        pcharrepphrase("I have business with you, old pirate!",
													               "Let's get down to business, buddy!"),
													pcharrepphrase("I swear by devil, you will not trick me, rascal! I have different business with you!",
													               "I absolutely agree, " +GetAddress_FormToNPC(NPChar)+ " " +GetFullName(npchar)+ ", I wanted to discuss other affairs with you.")),
											   NPCharRepPhrase(npchar,
											        pcharrepphrase("Loaded up already? I have business with you.",
													               "I Came here not for trading, my good man. I have other business."),
													pcharrepphrase("May the thunder strike you down for prices like those! I have business with you.",
													               "Discounts are always nice, " + GetAddress_FormToNPC(NPChar)+ " " +GetFullName(npchar)+ ", but I have different business with you.")),
											   NPCharRepPhrase(npchar,
											        pcharrepphrase("Hold your tongue, you old drunkard, I have business with you",
													               "You're sickened because of rum, I guess. Not that I am fond of yourself, either. Let's get down to business."),
													pcharrepphrase("You have already ripped me off, rascal! I have business with you.",
													               "Your irony is inappropriate. I have other business with you.")),
											   npchar, Dialog.CurrentNode);
			link.l2.go = "business";
			link.l3 = HeroStringReactionRepeat(NPCharRepPhrase(npchar,
			                                        pcharrepphrase("First business, then merry-making. I want to ask you something.",
													               "Not right now. I need information."),
													pcharrepphrase("To hell with your prices! First you're gonna tell me everything I need.",
													               "With pleasure. I wanted to ask something.")),
											   NPCharRepPhrase(npchar,
											        pcharrepphrase("Thanks for the advice, old murderer. I wanted to ask you something.",
													               "I had a particular question."),
												    pcharrepphrase("Gold can wait. I wanted to ask you something.",
													               "Yes, I agree. I wanted to ask you something.")),
											   NPCharRepPhrase(npchar,
											        pcharrepphrase("I do believe that you know, what I was going to ask.",
													               "I hope you will answer my question."),
													pcharrepphrase("Can you think of anything besides your price tags? 'Cause that's what I was going to ask you about.",
													               "That doesn't interest me. I need information.")),
											   NPCharRepPhrase(npchar,
											        pcharrepphrase("Don't get too excited, pal! I was just going to ask you a question.",
													               "Don't get too excited, or you can have a stroke. Just answer one question, and I shall leave"),
													pcharrepphrase("I don't expect you to say something smart, since you have a brain of a roach. But surely you must know something.",
													               "I will not delay you for long. Just one question.")),
											   npchar, Dialog.CurrentNode);
			link.l3.go = "quests";
			// --> Jason, генер почтового курьера 2 уровня
			if (CheckAttribute(PChar, "questTemp.WPU.Postcureer.LevelUp"))
			{
				if (pchar.questTemp.WPU.Postcureer.TargetPortmanID == npchar.id)
				{
					link.l12 = "I have brought you a price list from the town of "+XI_ConvertString("Colony"+pchar.questTemp.WPU.Postcureer.StartCity+"Gen")+".";
					link.l12.go = "Postcureer_LevelUp_ForAll";
				}
			}
			//<--генер почтового курьера 2 уровня	
						
			//Jason --> мини-квест Дефицитный товар
			if (CheckAttribute(pchar, "questTemp.Wine.Trader") && NPChar.location == pchar.questTemp.Wine.City + "_store" && !CheckAttribute(pchar, "questTemp.Wine.fail"))
			{
				link.l13 = "I'd like to purchase from you a batch of European wine - fifty-sixty bottles. I was told that you had enough of it in stock.."; 
				link.l13.go = "Wine_Trader";
			}
			if (CheckAttribute(pchar, "questTemp.Wine.Repeat2") && NPChar.location == pchar.questTemp.Wine.City + "_store" && CheckCharacterItem(pchar, "letter_1") && !CheckAttribute(pchar, "questTemp.Wine.fail"))
			{
				link.l13 = "Hello again. Please, take a look at this letter - perhaps, you would reconsider your position regarding selling wine to me?"; 
				link.l13.go = "Wine_Repeat2";
			}
			if (CheckAttribute(pchar, "questTemp.Wine.wait") && NPChar.location == pchar.questTemp.Wine.City + "_store" && !CheckAttribute(pchar, "questTemp.Wine.fail"))
			{
				link.l13 = "That's me again. Can we resume our interrupted wine deal? I managed to raise enough money."; 
				link.l13.go = "Wine_Price";
			}
			// <-- мини-квест Дефицитный товар
						
			if(CheckAttribute(pchar,"GenQuest.EncGirl"))
			{
				if(pchar.GenQuest.EncGirl == "toLoverFather" && pchar.GenQuest.EncGirl.LoverFather == "store_keeper" && pchar.GenQuest.EncGirl.LoverCity == npchar.city)
				{
					link.l9 = "Hello, I came by your son's invitation."; 
					link.l9.go = "EncGirl_4";
					pchar.quest.EncGirl_GetLoverFather.over = "yes";
				}
				if(pchar.GenQuest.EncGirl == "toParents" || pchar.GenQuest.EncGirl == "FindLover")
				{
					if(pchar.GenQuest.EncGirl.Father == "store_keeper" && npchar.city == pchar.GenQuest.EncGirl.city)
					{
						link.l9 = "This is about your daughter...";
						link.l9.go = "EncGirl_1";
					}
				}				
			}			
			link.l5 = HeroStringReactionRepeat(NPCharRepPhrase(npchar,
			                                        pcharrepphrase("See you, old drunkard.",
													               "Have a nice day, "+GetAddress_FormToNPC(NPChar)+" " +GetFullName(npchar)+"."),
													pcharrepphrase("Caramba! Don't leave anywhere, I'll come back again.",
													               "It was nice having you here, "+GetAddress_FormToNPC(NPChar)+" " +GetFullName(npchar)+"! Goodbye!")),
											   NPCharRepPhrase(npchar,
											        pcharrepphrase("Cast off!",
													               "Goodbye, my good man."),
													pcharrepphrase("Hey! What are you hiding there? Rum? No?! Alright, I'll go moisten my throat.",
													               "I am sorry, but I have urgent business in town.")),
											   NPCharRepPhrase(npchar,
											        pcharrepphrase("Heh! Well, see ya!",
													               "I have to go. Farewell, "+GetAddress_FormToNPC(NPChar)+" " +GetFullName(npchar)+"!"),
													pcharrepphrase("And don't even think to argue with me! I have no time for this!",
													               "Perhaps, I need to go and check, what's up on my ship. Farewell, "+GetAddress_FormToNPC(NPChar)+" " +GetFullName(npchar)+"!")),
											   NPCharRepPhrase(npchar,
											        pcharrepphrase("What's up, old chap? It's me - " +GetFullName(pchar)+ "! Sleep yourself sober, I'll come back later.",
													               "I am afraid your liver will finish you off before I get a chance to come to you again."),
													pcharrepphrase("Keep counting your guineas and doubloons, you old fox! I will be back.",
													               "I was happy to see you, " + GetAddress_FormToNPC(NPChar)+" " +GetFullName(npchar)+"!")),
											  npchar, Dialog.CurrentNode);
			link.l5.go = "exit";
		break;

		case "market":
//navy -->
			//занят ПГГ
			if (CheckFreeServiceForNPC(NPChar, "Store") != -1)	 // to_do имя сунуть
			{
				dialog.text = "Sorry, but I am too busy right now. So many customers! Come back tomorrow.";
				link.l1 = "Oh, really? Well, I'll come back later, then.";
				link.l1.go = "exit";
				break;
			}
//navy <--
			dialog.text = RandPhraseSimple("I have cannonballs, sailcloth, medicine, precious lumber and other goods! What are you interested in?", "Wanna buy sugar and spices? Or, perhaps, rum and gunpowder?");
			link.l1 = pcharrepphrase(LinkRandPhrase("I have a lot of loot in my hold! Money has no smell, has it?",
			                         "I need to dump the loot in my hold and fill it with your gold. Ha-ha!",
									 "Oh, I know that you would sell your mother for a sack of full-weight doubloons! But I just need to replenish my supplies."),
									 LinkRandPhrase("I want to sell my cargo and replenish the supplies.",
			                         "I want to purchase goods for sale.",
									 "Show me the cannonballs, bombs and stuff like that."));
			link.l1.go = "trade_1";

			if(CheckFunctionalTreasurer() && CheckAttribute(PChar, "TransferGoods.Enable")) // Автозакупка товаров
			{
				link.l5 = "My purser will make all necessary purchases...";
				link.l5.go = "TransferGoods";
			}
			
			link.l3 = pcharrepphrase(RandPhraseSimple("I am leaving without a trade. See ya!",
			                                          "I'll go moisten my throat. You stay there!"),
									 RandPhraseSimple("No, I don't have time for trading at the moment. Farewell.",
									                  "I am sorry, I have urgent business to do. Goodbye!"));
			link.l3.go = "exit";
		break;
		
		case "EncGirl_1":
			dialog.text = "I am all ears.";
			link.l1 = "I've brought your fugitive.";
			link.l1.go = "EncGirl_2";
		break;
		
		case "EncGirl_2":
			dialog.text = "Oh, captain, thank you very much! How is she? Is she hurt? It's been a day since she ran away, bad girl. Does it look that I am going to do her any harm? I have found her a husband. Arranged a marriage. A rich, young fiance. He may has a bad looks, but who gives a damn about face features. No! She always tries to everything in her own way. Same as her mother always did, flames!\nAlthough, she would not had been born if her mum didn't run away with some promising idiot long ago... well, whatever... Youth is naive, stupid and cruel.";
			link.l1 = "Of course, you're the father and it's up to you to decide, but I wouldn't hurry with the wedding...";
			link.l1.go = "EncGirl_3";
		break;
		
		case "EncGirl_3":
			dialog.text = "What do you know? Do you have kids of your own? No? Talk to me when you do…\nYes… I promised a reward to the man who will bring her back, here, take it.";
			link.l1 = "Thanks. And keep an eye on her. I have a hunch that she wouldn't stop at that.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("EncGirl_ToLoverParentsExit");
		break;
		
		case "EncGirl_4":
			if(sti(pchar.GenQuest.EncGirl.LoverFatherAngry) == 0)
			{
				dialog.text = "Oh, so you are "+ GetSexPhrase("that captain, who brought","that lass, who brought") +" my prodigal son with a young bride?";
				link.l1 = "Yes, I helped them escape.";
				link.l1.go = "EncGirl_5";
			}
			else
			{
				dialog.text = "Oh, there "+ GetSexPhrase("he is, our benefactor","she is, our benefactress") +". Expecting a reward, I take it?";
				link.l1 = "Well, I'm fine without a reward, but just your thanks would do.";
				link.l1.go = "EncGirl_6";			
			}
		break;
		
		case "EncGirl_5":
			dialog.text = "I am very grateful to you that you haven't abandoned my child in dire straits and helped him to find a way out of a delicate situation. Allow me to thank you and please accept this modest sum and a gift from me personally.";
			link.l1 = "Thanks. Helping out this young couple was my pleasure.";
			link.l1.go = "EncGirl_5_1";
		break;
		
		case "EncGirl_6":
			dialog.text = "Thanks? What thanks?! It's been a half a year since that blockhead has been hanging around without a job - and look at him, he's got enough time for love affairs! When I was his age, I was already running my own business! Pff! A governor has a marriageable daughter - and that dunce has brought a slut without kith or kin to my house and dared to ask for my blessing!";
			link.l1 = "Hmm... Apparently, you don't believe in sincere feelings?";
			link.l1.go = "EncGirl_6_1";		
		break;
		
		case "EncGirl_5_1":
			AddMoneyToCharacter(pchar, sti(pchar.GenQuest.EncGirl.sum));
			GiveItem2Character(pchar, pchar.GenQuest.EncGirl.item);
			AddQuestRecord("JungleGirl", "18");
			CloseQuestHeader("JungleGirl");
			DeleteAttribute(pchar, "GenQuest.EncGirl");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "EncGirl_6_1":
			dialog.text = "What feelings? What kind of feelings are you talking about? Feelings... how can one be so light-minded at your age?! Shame on you to indulge the young in their caprices and act as a procurer! You not only have taken a girl from her home, but you also ruined my greenhorn's life. There will be no thanks to you. Farewell.";
			link.l1 = "Alright, and all the same to you...";
			link.l1.go = "EncGirl_6_2";
		break;
		
		case "EncGirl_6_2":
			ChangeCharacterComplexReputation(pchar,"nobility", -1);
			AddQuestRecord("JungleGirl", "19");
			AddQuestUserData("JungleGirl", "sSex", GetSexPhrase("",""));
			AddQuestUserData("JungleGirl", "sSex1", GetSexPhrase("",""));
			CloseQuestHeader("JungleGirl");
			DeleteAttribute(pchar, "GenQuest.EncGirl");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();		
		break;
		
		// Warship. Автозакупка товаров -->
		case "TransferGoods":
			ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
			
			if(sti(Pchar.Ship.Type) != SHIP_NOTUSED && ok)
			{
				dialog.text = LinkRandPhrase("...Already done. Now all that's left is deciding, which ship to load.",
					"Your treasurer had already done that. Let's decide now, which ship is to be loaded.",
					"Yes, " + PChar.name + ", I know. He already paid me a visit. Now, which ship are we going to load?");
					
				for(i=0; i<COMPANION_MAX; i++)
				{
					cn = GetCompanionIndex(PChar, i);
					if(cn > 0)
					{
						chref = GetCharacter(cn);
						if(!GetRemovable(chref)) continue;
						
						attrL = "l"+i;
						Link.(attrL)    = "It will be " + XI_ConvertString(RealShips[sti(chref.Ship.Type)].BaseName) + " '" + chref.Ship.Name + "'.";
						Link.(attrL).go = "TransferGoodsTo_" + chref.id;
					}
				}
				
				Link.l99    = "I've crossed my mind, nothing needs.";
				Link.l99.go = "exit";
			}
			else // Корабля нету
			{
				dialog.text = NPCharRepPhrase(npchar, pcharrepphrase("Are you kidding me? Where is your ship? O don't see her at the pier!",
					"I swear to devil, you will not trick me! Your ship is not at the pier!"),
					pcharrepphrase("I don't see your ship in the port, captain " +GetFullName(pchar)+ ". I do hope she's not the 'Flying Dutchman'?",
					"Captain, it's much easier to load the cargo from the pier. And I prefer to do it that way. Bring your ship fast and come back."));
				link.l1 = NPCharRepPhrase(npchar, pcharrepphrase("" +RandSwear()+"What a trouble! Alright, old slyboots, see you soon!",
					"I did not want to deceive you, " +GetFullName(npchar)+ ", a ship is on the other side of the island."),
					pcharrepphrase("No. My ship is called the 'Black Pearl'. Why did you turn pale? Haha! Just kidding!",
					"Thanks for the advice, necessarily I'll use it."));
				link.l1.go = "exit";
			}
			break;
			
		case "TransferGoods_2": // Тут уже не проверяем, есть корабль или нету (выбрали корабль, в который груз не помещается)
			dialog.text = LinkRandPhrase("So, cap, which ship are we going to load?",
				"So, which ship is to be loaded, then?",
				PChar.name + ", the hold of which ship is to be loaded with goods?");
				
			for(i=0; i<COMPANION_MAX; i++)
			{
				cn = GetCompanionIndex(PChar, i);
				if(cn > 0)
				{
					chref = GetCharacter(cn);
					if(!GetRemovable(chref)) continue; // Если квестовый - пропускаем
					
					attrL = "l"+i;
					Link.(attrL)    = "It will be " + XI_ConvertString(RealShips[sti(chref.Ship.Type)].BaseName) + " '" + chref.Ship.Name + "'.";
					Link.(attrL).go = "TransferGoodsTo_" + chref.id;
				}
			}
			
			Link.l99    = "I've change my mind, I do not need anything.";
			Link.l99.go = "exit";
			break;
			
		case "TransferGoods_Start":
			chref = CharacterFromID(NPChar.CharToTransferGoodsID);
			
			iQuantityGoods = TransferGoods_CalculateWeight(chref);
			
			if(GetCargoFreeSpace(chref) >= iQuantityGoods)
			{
				if(TransferGoods_StartTransfer(chref, NPChar.City) != 0)
				{
					dialog.text = LinkRandPhrase("Everything is ready! The loading of the selected ship has begun.", 
						"Alright, the loading of goods on the selected ship has begun.",
						"Cap, the loading of goods on the selected ship has begun.");
					link.l1 = "Thank you. Pleasure doing business with you.";
					link.l1.go = "exit";
          SetPriceListByStoreMan(rColony); // mitrokosta обновляем список цен
					WaitDate("", 0, 0, 0, 1, 0); // Крутим время
				}
				else
				{
					dialog.text = LinkRandPhrase("Captain, all goods requested by your treasurer, are already present on board of the ship you indicated!", 
						"Cap, all the goods are already present on board of the ship you indicated!",
						"Cap, that ship doesn't require servicing, since all the goods are already there.");
					link.l1 = "Yeah, right.";
					link.l1.go = "exit";
					link.l2 = "Guess I'll need to pick another ship, then.";
					link.l2.go = "TransferGoods_2";
				}
			}
			else
			{
				dialog.text = LinkRandPhrase("I am afraid, the ship of that type simply cannot hold that much.", 
					"Cap, your ship will not hold that much cargo!",
					"Captain, the hold of your ship cannot take that much cargo!");
				link.l1 = "Yeah, you're right. I'll need to pick another ship.";
				link.l1.go = "TransferGoods_2";
				link.l2 = "I've been thinking... I don't need to buy anything.";
				link.l2.go = "exit";
			}
			break;
		// <-- Автозакупка товаров

		case "trade_1":
            ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
		    if (sti(Pchar.Ship.Type) != SHIP_NOTUSED && ok)
			{
			    NextDiag.CurrentNode = NextDiag.TempNode;
			    DialogExit();
			    Pchar.PriceList.StoreManIdx = rColony.index; // boal 27.02.05
			    LaunchStore(sti(rColony.StoreNum));
			}
			else
			{
			    dialog.text = NPCharRepPhrase(npchar, pcharrepphrase("Are you kidding me? Where is your ship? O don't see her at the pier!",
					"I swear to devil, you will not trick me! Your ship is not at the pier!"),
					pcharrepphrase("I don't see your ship in the port, captain " +GetFullName(pchar)+ ". I do hope she's not the 'Flying Dutchman'?",
					"Captain, it's much easier to load the cargo from the pier. The preferred item to be loaded from a pier. Bring your ship fast and come back."));
				link.l1 = NPCharRepPhrase(npchar, pcharrepphrase("" +RandSwear()+"What a trouble! Alright, old slyboots, see you soon!",
					"I did not want to deceive you, " +GetFullName(npchar)+ ", a ship is on the other side of the island."),
					pcharrepphrase("No. My ship is called the 'Black Pearl'. Why did you turn pale? Haha! Just kidding!",
					"Thanks for the advice, necessarily they use it."));
			    link.l1.go = "exit";//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			}
		break;

		case "storage_0":
			NPChar.MoneyForStorage = GetNpcQuestPastMonthParam(NPChar, "Storage.Date") * sti(NPChar.Storage.MoneyForStorage); 
			if(sti(NPChar.MoneyForStorage) > 0) 
			{
				dialog.text = "And for the rent, you still owe me " + FindRussianMoneyString(sti(NPChar.MoneyForStorage)) + ".";
				if(sti(pchar.money) >= sti(NPChar.MoneyForStorage))
				{
					link.l1 = "Alright, I'll pay for the rent now.";
					link.l1.go = "storage_3";
				}
				else
				{
					link.l1 = "I'll come back later.";
					link.l1.go = "exit";
				}
			}		
			else
			{
				dialog.text = "Come.";
				link.l1 = "Thanks.";
				link.l1.go = "storage_2";
			}
			link.l2 = "No, I've changed my mind.";
			link.l2.go = "exit"; 						
		break;
		
		case "storage_01":
			NPChar.MoneyForStorage = GetStoragePriceExt(NPChar, pchar); 
			dialog.text = "Yeah, I have a warehouse in the port - it can hold 50000 centners of cargo. For " + FindRussianMoneyString(sti(NPChar.MoneyForStorage)) + " per month I can provide safekeeping of your goods. "+
				"This includes guarding, protection from waterlogging and fighting the rats. What will you say? Also... I'll need a month's payment in advance.";	
			link.l1 = "Suit. Can I take a look at it? Do you have many rats there?";
			link.l1.go = "storage_1";
			link.l2 = "No, I'm just asking. I can use it when necessary...";
			link.l2.go = "exit";
		break;
		
		case "storage_1":
			NPChar.MoneyForStorage = GetStoragePriceExt(NPChar, pchar); 
			dialog.text = "As I said, I require payment for a month in advance. And no rats!";
			if(sti(pchar.money) >= sti(NPChar.MoneyForStorage))
			{
				link.l1 = "You are... quite mercantile, I must say. Here's your money - I'll rent this shed.";
				link.l1.go = "storage_11";
			}
			else
			{
				link.l1 = "You are... quite mercantile, I must say. Alright, I will soon be back with the money.";
				link.l1.go = "exit";
			}
		break;
		
		case "storage_11":
			AddMoneyToCharacter(pchar, -makeint(NPChar.MoneyForStorage)); 
			NPChar.Storage.MoneyForStorage = NPChar.MoneyForStorage;
			NPChar.Storage.Activate = true;
			Achievment_SetStat(pchar, 67, 1); // ugeen 2016
			SaveCurrentNpcQuestDateParam(NPChar, "Storage.Date");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LaunchStorage(sti(rColony.StoreNum));			
		break;
				
		case "storage_2":			
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LaunchStorage(sti(rColony.StoreNum));			
		break;
		
		case "storage_3":			
			AddMoneyToCharacter(pchar, -sti(NPChar.MoneyForStorage)); 
			NPChar.MoneyForStorage = GetStoragePriceExt(NPChar, pchar);
			NPChar.Storage.MoneyForStorage = NPChar.MoneyForStorage;
			SaveCurrentNpcQuestDateParam(NPChar, "Storage.Date");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LaunchStorage(sti(rColony.StoreNum));			
		break;		

		case "storage_04":
			dialog.text = "Leaving already? What a pity - that's really an excellent place on great terms. I assure you that you won't be getting a deal like this one nowhere in the Caribbean.";
			link.l1 = "I said - absolve. Or are you suggesting me paying for storage of air? Look for another renter.";
			link.l1.go = "storage_4";
			link.l2 = "Nowhere in the Caribbean, you say? Alright, I'll bag it for a while, then.";
			link.l2.go = "exit";
		break;
		
		case "storage_4":
			NPChar.MoneyForStorage = GetNpcQuestPastMonthParam(NPChar,"Storage.Date") * sti(NPChar.Storage.MoneyForStorage); 
			if(sti(NPChar.MoneyForStorage) > 0) 			
			{
				dialog.text = "And for the rent, you still owe me " + FindRussianMoneyString(sti(NPChar.MoneyForStorage)) + ".";
				if(sti(pchar.money) >= sti(NPChar.MoneyForStorage))			
				{
					link.l1 = "Fine.";
					link.l1.go = "storage_5";
				}
			}
			else
			{
				dialog.text = "Collect your goods, and I will close the warehouse.";
				link.l1 = "Fine.";
				link.l1.go = "storage_6";
			}
		break;
		
		case "storage_5":
			SetStorageGoodsToShip(&stores[sti(rColony.StoreNum)]);
			AddMoneyToCharacter(pchar, -sti(NPChar.MoneyForStorage)); 
			NPChar.Storage.NoActivate = true;
			DeleteAttribute(NPChar,"Storage.Activate");
			DialogExit();
		break;
		
		case "storage_6":
			SetStorageGoodsToShip(&stores[sti(rColony.StoreNum)]);
			DeleteAttribute(NPChar,"Storage.Activate");
			NPChar.Storage.NoActivate = true;
			DialogExit();
		break;		

		case "business":
			iTest = 0;			
			
//Jason --> ----------------------------------мини-квест Бесчестный конкурент------------------------------------
			if (!CheckAttribute(pchar, "questTemp.Shadowtrader") && sti(npchar.nation) != PIRATE && sti(pchar.rank) < 6 && drand(2) == 0) 
			{
				dialog.text = "Captain, I wanted to ask you about a favor. Will you help me?";
				link.l1 = "What can I do for you?"; 
				link.l1.go = "Shadowtrader_begin";
				break;
			}
			
			if (CheckAttribute(pchar, "questTemp.Shadowtrader"))
			{
				if(pchar.questTemp.Shadowtrader == "begin" && GetNpcQuestPastDayParam(npchar, "Shadowtrader_date") < 5 && NPChar.location == pchar.questTemp.Shadowtrader.City + "_store")
				{
					dialog.text = "Thank you, captain, for fulfilling my request. Now, when "+pchar.questTemp.Shadowtrader.Guardername+" is here, I can at least feel a bit more relaxed.";
					link.l1 = "Hmm... I wouldn't want to appear obtrusive, but it seems to me that you are having troubles. Can you tell me what's the deal - perhaps, I could help you?"; 
					link.l1.go = "Shadowtrader_fort";
					break;
				}
				if(CheckAttribute(pchar, "questTemp.Shadowtrader.Trouble") && NPChar.location == pchar.questTemp.Shadowtrader.City + "_store")
				{
					dialog.text = "So? Have you handed over my letter?";
					link.l1 = "I have. The commandant replied by word of mouth that the evidence in your letter is insufficient for the city guard to take any measures."; 
					link.l1.go = "Shadowtrader_trouble";
				pchar.quest.ShadowtraderTimeFort_Over.over = "yes";
					break;
				}
				if(CheckAttribute(pchar, "questTemp.Shadowtrader.End.Fort") && NPChar.location == pchar.questTemp.Shadowtrader.City + "_store" && GetQuestPastDayParam("pchar.questTemp.Shadowtrader.EndFort") > 0)
				{
					dialog.text = "I have already heard the news - tonight guards discovered an illegal trading post of smugglers and arrested them all. It was under command of one rare piece of scum, it's alright now, he won't be able to do bad thing to other for a while\nCommandant told me about your role in all of this, gratitude! You have kept your word! Here, take the money - 15 000 pesos. You have saved me. Nothing is threatening my business now!";
					link.l1 = "You're welcome. It was easy."; 
					link.l1.go = "Shadowtrader_complete";
					break;
				}
				if(CheckAttribute(pchar, "questTemp.Shadowtrader.End.Escape") && NPChar.location == pchar.questTemp.Shadowtrader.City + "_store")
				{
					dialog.text = "So, any good news, " + pchar.name + "?";
					link.l1 = "I have located your rival. He will not be a pain in your butt again - I managed to convince him... to leave this island. His 'shop' was in a house near the city gates. It's up to you to decide what to do with the cargo that was abandoned. You can turn it in to the authorities or attempt to collect it for yourself."; 
					link.l1.go = "Shadowtrader_Escape_complete";
					break;
				}
				if(CheckAttribute(pchar, "questTemp.Shadowtrader.End.Free") && NPChar.location == pchar.questTemp.Shadowtrader.City + "_store")
				{
					dialog.text = "I have already heard the news - tonight the guards have discovered in one of the houses underground outlet of smugglers. Two villains found dead. Great job, " + pchar.name + ", I admire you! Here, take the reward - 15 000 pesos. You just saved me! Now I'll trade for real!\nSatisfy my curiosity - their leader... also among the two dead?";
					link.l1 = "No. But he will never show his face in your town again. I believe he should be several dozen miles away from this island, while we're talking."; 
					link.l1.go = "Shadowtrader_complete";
					break;
				}
				if(CheckAttribute(pchar, "questTemp.Shadowtrader.End.Kill") && NPChar.location == pchar.questTemp.Shadowtrader.City + "_store")
				{
					dialog.text = "I have already heard the news - this night the guards have located in one of the houses a secret smuggler shop. Three villains were found dead. Excellent work, " + pchar.name + ", I admire you! Here, take the award - 15,000 pesos. You just saved me! Now I'll trade for real!\nSatisfy my curiosity - their leader... also among the two dead?";
					link.l1 = "Yes. You've got rid of your rival forever. He will never trouble you again."; 
					link.l1.go = "Shadowtrader_complete";
					break;
				}
			}
			//<-- мини-квест Бесчестный конкурент
	
			//Jason --> генератор Сомнительное предложение
			/*if (drand(3) == 1 && !CheckAttribute(pchar, "GenQuest.Contraoffer.Trader") && !CheckAttribute(pchar, "GenQuest.Contraoffer.Slaves.Yes") && sti(npchar.nation) != PIRATE && 7-sti(RealShips[sti(pchar.ship.type)].Class) > 0) 
			{
				if (!CheckAttribute(npchar, "Contraoffer") || GetNpcQuestPastDayParam(npchar, "Contraoffer") >= 30) 
				{
					dialog.text = "Oh! You're just in time, captain. I would like to ask you to do me a favor.";
					link.l1 = "Let's listen."; 
					link.l1.go = "Contraoffer";
					break;
				}
			}
		
			if (CheckAttribute(pchar, "GenQuest.Contraoffer.Trader") && NPChar.location == pchar.GenQuest.Contraoffer.Trader.City + "_store") 
			{
				dialog.text = "I'm all ears, captain.";
				link.l5 = "I have brought your order."; 
				link.l5.go = "Contraoffer_check";
			}
			
			if (!CheckAttribute(pchar, "GenQuest.Contraoffer.Slaves") && sti(npchar.quest.Contraoffer.chance) == 2 && GetNpcQuestPastDayParam(npchar, "Contraoffer") >= 30) //единичный вариант за всю игру, ака 'пасхалка'
			{
				dialog.text = "Oh! You're just in time, captain. I require a special favor.";
				link.l5 = "Let's listen."; 
				link.l5.go = "Contraoffer_slaves";
				break;
			}
			
			if (CheckAttribute(pchar, "GenQuest.Contraoffer.Slaves.Yes") && NPChar.location == pchar.GenQuest.Contraoffer.Slaves.City + "_store") 
			{
				dialog.text = "I'm all ears, captain.";
				link.l5 = "I have brought you the slaves."; 
				link.l5.go = "Contraoffer_slaves_check";
			}*/
			// <-- генератор Сомнительное предложение
	
			//Jason --> генератор Неудачливый вор
			if (CheckAttribute(pchar, "GenQuest.Device.Shipyarder") && NPChar.location == pchar.GenQuest.Device.Shipyarder.City + "_store" && pchar.GenQuest.Device.Shipyarder == "begin" && !CheckAttribute(npchar, "quest.Device"))
			{
   				link.l16 = "Listen, you're dealing in all sorts of goods... Yesterday or today - did anyone offer you to buy "+pchar.GenQuest.Device.Shipyarder.Type+"?";
				link.l16.go = "Device_Trader";
			}
			// <-- генератор Неудачливый вор
			
			//Jason --> генератор Место под солнцем
			if (!CheckAttribute(pchar, "GenQuest.Sunplace.Trader") && !CheckAttribute(npchar, "quest.Sunplace") && sti(npchar.nation) != PIRATE && sti(pchar.rank) < 20 && drand(4) == 4) 
			{
				dialog.text = "Captain, I would like to ask you for a favor, and I am willing to pay you handsomely, should you agree.";
				link.l1 = "Interesting. Well, what's the trouble?"; 
				link.l1.go = "Sunplace_begin";
				break;
			}
			
			if (CheckAttribute(pchar, "GenQuest.Sunplace.Trader") && pchar.GenQuest.Sunplace.Trader == "complete" && npchar.location == pchar.GenQuest.Sunplace.Trader.City + "_store") 
			{
				dialog.text = "Captain, I am glad to see you. I already know that you have fulfilled my request regarding "+pchar.GenQuest.Sunplace.Trader.Enemyname+".";
				link.l1 = "Heh! That's for sure. "+GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.Sunplace.Trader.ShipType), "Name")))+" "+pchar.GenQuest.Sunplace.Trader.ShipName+" and the cargo - " + GetGoodsNameAlt(sti(pchar.GenQuest.Sunplace.Trader.Goods))+ ", no longer belong to your rival."; 
				link.l1.go = "Sunplace_complete";
				break;
			}
			
			if (CheckAttribute(pchar, "GenQuest.Sunplace.Trader") && pchar.GenQuest.Sunplace.Trader == "complete_murder" && npchar.location == pchar.GenQuest.Sunplace.Trader.City + "_store") 
			{
				dialog.text = "My Lord, captain... Why did you kill him? I only asked you to sink his ship! Holy Virgin, I now have the blood of an innocent man on my hands...";
				link.l1 = "Heh! What's the matter with you, " + npchar.name + "? Who cares - he will never bother you again, and that's what matters!"; 
				link.l1.go = "Sunplace_complete_murder";
				break;
			}
			// <-- генератор Место под солнцем
			
//navy -->
			//занят ПГГ
			iTmp = CheckAvailableTaskForNPC(NPChar, PGG_TASK_WORKONSTORE);
			if (iTmp != -1)
			{
				dialog.text = "I had a job, but " + GetFullName(&Characters[iTmp]) + " has already undertaken to do it for me.";
				link.l1 = "Oh, really? Well, I'll come back later, then.";
				link.l1.go = "exit";
				break;
			}
//navy <--
			dialog.text = NPCharRepPhrase(npchar,"What business?! Tell me everything!","I am listening. What's that deal you're talking about?");
            ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
            if (sti(Pchar.Ship.Type) != SHIP_NOTUSED && ok)
			{
    			if (CheckQuestAttribute("generate_trade_quest_progress", "begin") || CheckQuestAttribute("generate_trade_quest_progress",  "failed"))
    			{
    				if (pchar.CargoQuest.TraderID == npchar.id )
    				{
    					link.l1 = RandPhraseSimple("I have a batch of goods for your store in the hold of my ship.", "My ship was chartered to deliver the goods to your store. The wares are being unloaded now.");
    					link.l1.go = "generate_quest_2";
    				}
    				else
    				{
                        if (!CheckQuestAttribute("generate_trade_quest_progress",  "failed") && pchar.CargoQuest.GiveTraderID == npchar.id && GetNationRelation2MainCharacter(sti(characters[GetCharacterIndex(pchar.CargoQuest.TraderID)].nation)) == RELATION_ENEMY)
                        {
                            link.l1 = "Unfortunately, I am forced to abandon their commitments. The political situation does not allow me to deliver the goods.";
            				link.l1.go = "generate_quest_cannot_done";
                        }
                        else
                        {
                            if (rand(1) == 1)
                            {
                                link.l1 = RandPhraseSimple("I can offer you to charter my ship for shipping cargo.",
								                           "I have a great ship and I can deliver any cargo wherever you might need.");
            				    link.l1.go = "generate_quest_not_closed";
        				    }
    				    }
    				}
    			}
    			else
    			{
    				link.l1 = "Would you like to charter a ship, " +GetAddress_FormToNPC(NPChar)+ "? I have a reliable vessel and experienced crew.";
    				link.l1.go = "generate_quest";
    			}
    			// --> на кредитный генератор
    			if (CheckAttribute(pchar, "GenQuest.LoanChest.TakeChest") && sti(pchar.GenQuest.LoanChest.TargetIdx) == sti(NPChar.index))
    			{
	                link.l3 = pcharrepphrase(RandPhraseSimple("Oh, I was really drained in the sea... Well, buddy, money is a real issue for me right now.",
	                                                          "Alright, old fox, let's discuss our financial affairs."),
	                                        RandPhraseSimple("I would like to discuss with you the financial issues.",
	                                                         "Let's discuss financial matters, we have to talk about."));,
	
	                link.l3.go = "LoanForAll";
                }
				//квест мэра - на связь с нашим шпионом
  				if (CheckAttribute(pchar, "GenQuest.Intelligence") && pchar.GenQuest.Intelligence.SpyId == npchar.id && pchar.GenQuest.Intelligence == "") 
				{
					link.l4 = RandPhraseSimple("I am here on request of one man. His name is governor " + GetFullName(characterFromId(pchar.GenQuest.Intelligence.MayorId)) + ".", 
						GetFullName(characterFromId(pchar.GenQuest.Intelligence.MayorId)) + " sent me to you. I am supposed to pick up something...");
					link.l4.go = "IntelligenceForAll";
				}	
				
				//homo 25/06/06 слухи
                link.l6 = pcharrepphrase(RandPhraseSimple("Can you tell me the latest gossips? You're hanging around here all day, anyway.",
                                                          "Make no fuss, you old fraud - better tell me what's new on the dry land?"),
                                        RandPhraseSimple("It seems that I spent forever at sea. What's new in your region?",
                                                         "You probably know all the latest news? What important happened?"));,

    		    link.l6.go = "rumours_trader";

				// ugeen --> склад товаров для ГГ
				if(CheckAttribute(NPChar,"Storage") && Pchar.location.from_sea == "Pirates_town")
				{
					if(CheckAttribute(NPChar,"Storage.Activate"))
					{
						link.l7 = "Take me to the warehouse. I want to see, what condition it is in.";
						link.l7.go = "storage_0";
						link.l8 = "I decided to release the warehouse. I don't need it now.";
						link.l8.go = "storage_04";
					}
					else
					{
						if(!CheckAttribute(NPChar,"Storage.NoActivate"))
						{
							link.l7 = "Excuse me, my good man - aren't you renting warehouses, by a chance?";
							link.l7.go = "storage_01";
						}	
					}
				}				
				// <-- ugeen
				// Jason --> квест губера на поиск дезертира
				if(CheckAttribute(pchar, "GenQuest.FindFugitive") && sti(NPChar.nation) == PIRATE)
				{
					link.l8 = "You see, I am trying to find my companion, "+pchar.GenQuest.FindFugitive.Name+" is his name. In Port-Royal, people at the tavern told me that he was heading to your settlement. Have you met him, by a chance?";
					link.l8.go = "FindFugitiveSt";
				}
				//<-- поиск дезертира
				
				// <-- homo
				link.l99 = "But there's no time for talks now.";
    			link.l99.go = "no_quests";
			}
			else
			{
                link.l1 = NPCharRepPhrase(npchar, pcharrepphrase("" +RandSwear()+"I left the ship on the other side of the island. I'll come back later!", "I beg your pardon, " +GetFullName(npchar)+ ", I'll come later. My ship has not yet approached the pier."), pcharrepphrase("Devil! These idiots didn't prepare the ship for loading! I'll come back later!", "Excuse me, I must give orders to moor my ship at the pier!"));
                link.l1.go = "exit";
    			// --> на кредитный генератор
    			if (CheckAttribute(pchar, "GenQuest.LoanChest.TakeChest") && sti(pchar.GenQuest.LoanChest.TargetIdx) == sti(NPChar.index))
    			{
	                link.l3 = pcharrepphrase(RandPhraseSimple("Oh, I was really drained in the sea... Well, buddy, money is a real issue for me right now.",
	                                                          "Alright, old fox, let's discuss our financial affairs."),
	                                        RandPhraseSimple("I would like to discuss with you the financial issues.",
	                                                         "Let's discuss financial matters, we have to talk about."));,
	
	                link.l3.go = "LoanForAll";
                }
				//квест мэра - на связь с нашим шпионом
  				if (CheckAttribute(pchar, "GenQuest.Intelligence") && pchar.GenQuest.Intelligence.SpyId == npchar.id && pchar.GenQuest.Intelligence == "") 
				{
					link.l7 = RandPhraseSimple("I am here on request of one man. His name is governor " + GetFullName(characterFromId(pchar.GenQuest.Intelligence.MayorId)) + ".", 
						GetFullName(characterFromId(pchar.GenQuest.Intelligence.MayorId)) + " sent me to you. I am supposed to pick up something...");
					link.l7.go = "IntelligenceForAll";
				}	
			}
		break;
		
		case "generate_quest":
			if (npchar.quest.trade_date != lastspeak_date || bBettaTestMode)
			{
				npchar.quest.trade_date = lastspeak_date;
				//проверка враждебности нам страны торговца
				if (sti(NPChar.nation) != PIRATE && GetNationRelation2MainCharacter(sti(NPChar.nation)) == RELATION_ENEMY)
				{
					dialog.text = "No, I don't need your services! At least, while you're enemies with " + NationNameAblative(sti(NPChar.nation)) + ".";
					link.l1 = "In that case, farewell.";
					link.l1.go = "exit";
				}
				else
				{
                    // проверка на проф пригодность -->
                    if (isBadReputation(pchar, 42))
                    {
                        dialog.text = RandSwear() + "You're " + GetFullName(pchar)+ ", aren't you? They say " +
                                      RandPhraseSimple("a lot of scary things about you","a lot of ugly things about you") + ", and I don't want to deal with you.";
						link.l1 = RandPhraseSimple("Of course - you make a mistake once, and everybody will gladly spit at you.",
						                           RandSwear()+ "Well, there are better things to do at sea, "+GetFullName(npchar)+".");
						link.l1.go = "exit";
                        break;
                    }
                    // проверка на проф пригодность <--
                    int iTradeNation = GenerateNationTrade(sti(NPChar.nation));

					if (iTradeNation < 0)
					{
						dialog.text = NPCharRepPhrase(npchar, "Heh, "+GetAddress_Form(NPChar)+", I don't have time for freights today. Come back tomorrow.","Come back tomorrow. Perhaps, I will make you an advantageous offer.");
						link.l1 = "Alright, I'll come back tomorrow.";
						link.l1.go = "exit";
					}
					else
					{
                        int storeMan = findStoreMan(NPChar, iTradeNation);
                        if (storeMan > 0)
                        {
                            //проверяем импорт/экспорт
							iTradeGoods = GOOD_COFFEE + drand(sti(GOOD_PAPRIKA - GOOD_COFFEE)); //Jason
    						//проверяем свободное место (при этом должно вмещаться по меньшей мере 100 единиц выбранного груза
    						RecalculateSquadronCargoLoad(pchar); // fix неверное место
    						iQuantityGoods = GetSquadronFreeSpace(pchar, iTradeGoods);
							if (sti(Goods[iTradeGoods].Weight)/sti(Goods[iTradeGoods].Units)*sti(iQuantityGoods) > 1500) iQuantityGoods = makeint(1500/(sti(Goods[iTradeGoods].Weight)/sti(Goods[iTradeGoods].Units))); //Jason: больше 1500 массы не дадим - большие фрахты только через ПУ
    						if (iQuantityGoods < 100)// это в шт. товара
    						{
    							dialog.text = NPCharRepPhrase(npchar, "Your pitiful old tub cannot hold the entire batch, so there will be no deal today.","Unfortunately, captain "+GetFullName(pchar)+", I will need more capacious ship for my delivery.");
    							link.l1 = NPCharRepPhrase(npchar, "My ship is decent, but I got your point. Goodbye.","I can see your point, business is business. Farewell.");
    							link.l1.go = "exit";
    						}
    						else
    						{
    							iQuantityGoods = iQuantityGoods - rand(makeint(iQuantityGoods/3)) - 10;
    							iMoney = makeint((iQuantityGoods * sti(Goods[iTradeGoods].Weight) / sti(Goods[iTradeGoods].Units)) * (4+rand(3) + GetSummonSkillFromNameToOld(pchar, SKILL_COMMERCE)) + 0.5);

    							pchar.CargoQuest.iTradeGoods = iTradeGoods;
    							pchar.CargoQuest.iQuantityGoods = iQuantityGoods;
    							pchar.CargoQuest.iMoney = iMoney;
    							pchar.CargoQuest.iTradeNation = iTradeNation;
    							pchar.CargoQuest.iDaysExpired = 25 + rand(5);
    							
    							pchar.CargoQuest.iTradeColony = Characters[storeMan].city;
    							pchar.CargoQuest.iTradeIsland = GetIslandByCityName(Characters[storeMan].city);
    							pchar.CargoQuest.TraderID     = Characters[storeMan].id;
    							pchar.CargoQuest.GiveTraderID = NPChar.id;
                                SaveCurrentQuestDateParam("CargoQuest");
    							string sNation = XI_ConvertString("Colony"+Characters[storeMan].city);
                                sTemp = "";
                                if (pchar.CargoQuest.iTradeIsland != Characters[storeMan].city)
								{
                                    sTemp = ", which is on " + XI_ConvertString(pchar.CargoQuest.iTradeIsland+"Dat");
                                }
                                dialog.text =  "Oh! I was just about to ask you for a favor. You see, I need to deliver the cargo of " +
                                               GetGoodsNameAlt(iTradeGoods)+ " in amount of " + FindRussianQtyString(iQuantityGoods) + " to the town of " +
                                           sNation + sTemp + ", and the sooner the better. If you manage to do it for " +  FindRussianDaysString(makeint(pchar.CargoQuest.iDaysExpired)) +
                                           ", then upon arrival you will receive " +
                                           FindRussianMoneyString(iMoney) + " as your reward. What do you say?";
    							link.l1 = "I think I agree.";
    							link.l1.go = "exit_trade";
    							link.l2  = "This is probably not for me.";
    							link.l2.go = "exit";
    						}
                        }
                        else
                        {
                            dialog.text = "Political realities in the archipelago do not allow me to trade. "+
                                          XI_ConvertString(NationShortName(sti(NPChar.nation))+"hunter") + " is in hostility with all and left the store just me.";
    						link.l1 = "Oh! I am sorry. Best of luck.";
    						link.l1.go = "exit";
                        }
					}
				}
			}
			else
			{
				dialog.text = NPCharRepPhrase(npchar, "Get lost, I have no time for idle chatter!","I have already told you that I don't have anything for you.");
				link.l1 = NPCharRepPhrase(npchar, "You must be courteous, or I'll teach you to be polite!", "Oh, I am sorry!");
				link.l1.go = "exit";
			}
		break;

		case "exit_trade":
			AddDialogExitQuest("trade_quest_open");
			Nextdiag.CurrentNode = Nextdiag.TempNode;
			DialogExit();
		break;

		case "generate_quest_2":
			if (pchar.quest.generate_trade_quest_progress == "failed")
			{
				dialog.text = RandSwear() + "Don't you think that you remembered about that deal a bit too late? I had to order the goods again. Farewell.";
				link.l1 = "Forgive me, but I was in a hurry. Maybe if I will cover your losses, this will restore my reputation?";
				link.l1.go = "generate_quest_failed";
				link.l9 = "All the best.";
				link.l9.go = "exit";
				ChangeCharacterComplexReputation(pchar,"nobility", -1);
			}
			else
			{
                iTradeGoods    =  makeint(pchar.CargoQuest.iTradeGoods);
                iQuantityGoods =  makeint(pchar.CargoQuest.iQuantityGoods);
                
                dialog.text = "Indeed! I've been waiting for it quite some time. You have to deliver me a cargo of " +
                GetGoodsNameAlt(iTradeGoods) + " in amount of " + FindRussianQtyString(iQuantityGoods) + " and receive for it " +
                FindRussianMoneyString(sti(pchar.CargoQuest.iMoney)) + ".";
				link.l1 = "Exactly.";
				link.l1.go = "generate_quest_ready";
			}
		break;
		
		case "generate_quest_ready":
            iTradeGoods    =  makeint(pchar.CargoQuest.iTradeGoods);
            iQuantityGoods =  makeint(pchar.CargoQuest.iQuantityGoods);
            // блок кидалова нас на бабки -->
            if (rand(8) == 1 && sti(Goods[iTradeGoods].Cost) <= 44 && GetQuestPastDayParam("CargoQuest") > 5)
            {
                dialog.text = RandSwear() + "I must apologize to you, "+GetAddress_Form(NPChar)+
                              ".  You see, The problem is that I was " + RandPhraseSimple("in an embarrassing situation and I won't be able to pay you"," already purchased that cargo from a different vendor for a better price")+
                              ". As a payment for your charter I suggest you keeping all the cargo you were delivering.";
				link.l1 = RandSwear() + RandPhraseSimple("And I've been protecting that damn cargo from all dangerous! I killed two hundred rats because of it!",
                                                         "You put me in a stalemate, and I will have to agree.");
				link.l1.go = "exit";
				ChangeCharacterComplexReputation(pchar,"nobility", 2);
				AddCharacterExpToSkill(pchar, "Sailing", 60);
				AddCharacterExpToSkill(pchar, "Leadership", 20);
				AddCharacterExpToSkill(pchar, "COMMERCE", 15);

				pchar.quest.generate_trade_quest_progress = "";
				pchar.quest.generate_trade_quest.over = "yes";
                
                AddQuestRecord("DELIVERY_TRADE_QUEST", "4");
                AddQuestUserData("DELIVERY_TRADE_QUEST", "sGoodGen", GetGoodsNameAlt(iTradeGoods));
			    AddQuestUserData("DELIVERY_TRADE_QUEST", "sTargetColony",XI_ConvertString("Colony"+pchar.CargoQuest.iTradeColony+"Dat"));
                CloseQuestHeader("DELIVERY_TRADE_QUEST");
                break;
            }
            // блок кидалова нас на бабки <--
			if (GetSquadronGoods(pchar, iTradeGoods) < iQuantityGoods)
			{
                iTmp = iQuantityGoods - GetSquadronGoods(pchar, iTradeGoods);
                dialog.text = "That's not the entire batch! According to our deal I need "
                              + FindRussianQtyString(iTmp) + " units more.";
				link.l9 = RandPhraseSimple("Yes, indeed. I'll have to compensate the shortage then. See you later.",
                                           RandSwear() +"These cursed rats have spoiled the cargo. I will compensate the shortage and come back again.");
				link.l9.go = "exit";
                AddQuestRecord("DELIVERY_TRADE_QUEST", "8");
                AddQuestUserData("DELIVERY_TRADE_QUEST", "sHaveNotQty", iTmp);
                AddQuestUserData("DELIVERY_TRADE_QUEST", "sGoodGen", GetGoodsNameAlt(iTradeGoods));
			}
			else
			{
                dialog.text = "Excellent! Here's your reward, captain "+GetFullName(pchar)+".";
				link.l1 = "It was a pleasure working with you.";
				link.l1.go = "exit";
				ChangeCharacterComplexReputation(pchar,"nobility", 3);
				AddCharacterExpToSkill(pchar, "Sailing", 100);
				AddCharacterExpToSkill(pchar, "Leadership", 30);
				AddCharacterExpToSkill(pchar, "COMMERCE", 100);

				AddMoneyToCharacter(pchar, makeint(pchar.CargoQuest.iMoney));
				pchar.quest.generate_trade_quest_progress = "";
				pchar.quest.generate_trade_quest.over = "yes";
				RemoveCharacterGoods(pchar, makeint(pchar.CargoQuest.iTradeGoods), makeint(pchar.CargoQuest.iQuantityGoods));
				
                OfficersReaction("good");
                
                AddQuestRecord("DELIVERY_TRADE_QUEST", "2");
                AddQuestUserData("DELIVERY_TRADE_QUEST", "sGoodGen", GetGoodsNameAlt(iTradeGoods));
			    AddQuestUserData("DELIVERY_TRADE_QUEST", "sTargetColony",XI_ConvertString("Colony"+pchar.CargoQuest.iTradeColony+"Gen"));
                CloseQuestHeader("DELIVERY_TRADE_QUEST");
			}
		break;
		
		case "generate_quest_failed":
            iTradeGoods    =  makeint(pchar.CargoQuest.iTradeGoods);
            iQuantityGoods =  makeint(pchar.CargoQuest.iQuantityGoods);
            iMoney =  3*makeint(iQuantityGoods * sti(Goods[iTradeGoods].Cost) / sti(Goods[iTradeGoods].Units));
			dialog.text = "Alright... The sum of " + FindRussianMoneyString(iMoney) + " will just cover the damages caused by the violation of the terms of our deal.";
			link.l1 = "Wow! No, that won't do! Never again shall I be delivering any cargo! There's enough of that crap at sea!";
			link.l1.go = "exit";
            if (sti(pchar.Money) >= iMoney)
            {
    			link.l2 = "Here's the required amount";
    			link.l2.go = "generate_quest_failed_2";
			}
            else
            {
                AddQuestRecord("DELIVERY_TRADE_QUEST", "7");
                AddQuestUserData("DELIVERY_TRADE_QUEST", "sMoney", FindRussianMoneyString(iMoney));
    		    AddQuestUserData("DELIVERY_TRADE_QUEST", "sTargetColony",XI_ConvertString("Colony"+pchar.CargoQuest.iTradeColony+"Gen"));
            }
		break;
		
		case "generate_quest_failed_2":
            iTradeGoods    =  makeint(pchar.CargoQuest.iTradeGoods);
            iQuantityGoods =  makeint(pchar.CargoQuest.iQuantityGoods);
            iMoney =  3*makeint(iQuantityGoods * sti(Goods[iTradeGoods].Cost) / sti(Goods[iTradeGoods].Units));
			dialog.text = "Excellent. Now I can tell my colleagues that you're still reasonable to deal with.";
			link.l1 = "Thank you! I will not fail you again.";
			link.l1.go = "exit";
			ChangeCharacterComplexReputation(pchar,"nobility", 10);
			AddCharacterExpToSkill(pchar, "Sailing", -100);
			AddCharacterExpToSkill(pchar, "Leadership", -50);
			AddCharacterExpToSkill(pchar, "COMMERCE", -100);

			AddMoneyToCharacter(pchar, -iMoney);
			pchar.quest.generate_trade_quest_progress = "";
			pchar.quest.generate_trade_quest.over = "yes";

            AddQuestRecord("DELIVERY_TRADE_QUEST", "5");
            AddQuestUserData("DELIVERY_TRADE_QUEST", "sMoney", FindRussianMoneyString(iMoney));
            AddQuestUserData("DELIVERY_TRADE_QUEST", "sGoodGen", GetGoodsNameAlt(iTradeGoods));
		    AddQuestUserData("DELIVERY_TRADE_QUEST", "sTargetColony",XI_ConvertString("Colony"+pchar.CargoQuest.iTradeColony+"Gen"));
            CloseQuestHeader("DELIVERY_TRADE_QUEST");
		break;
		
		case "generate_quest_not_closed":
            iTradeGoods    =  makeint(pchar.CargoQuest.iTradeGoods);
            iQuantityGoods =  makeint(pchar.CargoQuest.iQuantityGoods);

            dialog.text = "Hmm. I heard that you haven't fulfilled your obligations stated in the previous contract - and you are asking for another? You had to deliver the cargo of " +
            LanguageConvertString(iSeaGoods, "seg_" + Goods[iTradeGoods].Name)+ " to " + XI_ConvertString("Colony"+pchar.CargoQuest.iTradeColony) + ".";
			link.l1 = "Yes, indeed! You're correct!";
			link.l1.go = "exit";
		break;
		
		case "generate_quest_cannot_done":
            dialog.text = RandSwear() + GetAddress_Form(NPChar) +", you're letting me down!!! Perhaps, you will do something to resolve this issue?";
			link.l1 = "Alright. I will do my best to deliver the shipment.";
			link.l1.go = "exit";
			link.l2 = "No, I can't. I am sorry";
			link.l2.go = "generate_quest_cannot_done_2";
			
		break;
		
		case "generate_quest_cannot_done_2":
		    iTradeGoods    =  makeint(pchar.CargoQuest.iTradeGoods);
            iQuantityGoods =  makeint(pchar.CargoQuest.iQuantityGoods);
            if (GetSquadronGoods(pchar, iTradeGoods) < iQuantityGoods)
			{
				dialog.text = "Hold on! There are not enough goods on board of your ship! You don't have "
                              + FindRussianQtyString(iQuantityGoods - GetSquadronGoods(pchar, iTradeGoods)) + " units of cargo.";
				link.l9 = RandPhraseSimple("Yes, indeed. I'll have to compensate the shortage then.",
                                           RandSwear() +"The rats have spoiled the cargo. I will buy the missing amount and come back again.");
				link.l9.go = "exit";
			}
			else
			{
                dialog.text = "I see, I see... I'll accept the shipment back.";
    			link.l1 = "Thank you! I will not fail you again!";
    			link.l1.go = "exit";
    			ChangeCharacterComplexReputation(pchar,"nobility", -3);

				pchar.quest.generate_trade_quest_progress = "";
				pchar.quest.generate_trade_quest.over = "yes";
				RemoveCharacterGoods(pchar, makeint(pchar.CargoQuest.iTradeGoods), makeint(pchar.CargoQuest.iQuantityGoods));
                
                AddQuestRecord("DELIVERY_TRADE_QUEST", "6");
                AddQuestUserData("DELIVERY_TRADE_QUEST", "sGoodQty", FindRussianQtyString(sti(pchar.CargoQuest.iQuantityGoods)));
                AddQuestUserData("DELIVERY_TRADE_QUEST", "sGoodGen", GetGoodsNameAlt(iTradeGoods));
    		    AddQuestUserData("DELIVERY_TRADE_QUEST", "sTargetColony",XI_ConvertString("Colony"+pchar.CargoQuest.iTradeColony+"Dat"));
                CloseQuestHeader("DELIVERY_TRADE_QUEST");
            }
		break;

		//Jason --> -------------------мини-квест Бесчестный конкурент-------------------------------------------
		case "Shadowtrader_begin":
			pchar.questTemp.Shadowtrader = "true";
			pchar.questTemp.Shadowtrader.Guardername = GenerateRandomName_Generator(sti(npchar.nation), "man");
			dialog.text = "Could you please go to the tavern, find there a man by the name of "+pchar.questTemp.Shadowtrader.Guardername+" and tell him to come here as soon as possible? I cannot leave the store, and this blockhead sits in the tavern, loading up with rum, and surely he will not even think to come here, despite being on duty.";
			link.l1 = "I'm always happy to help, buddy - all the more so that I was going to visit the tavern anyway.";
			link.l1.go = "Shadowtrader_begin_1";
			link.l2 = "Are you laughing at me? Do I look like your errand boy? The tavern is just a couple steps away from here - you can go there yourself.";
			link.l2.go = "exit";
		break;
		
		case "Shadowtrader_begin_1":
			dialog.text = "Thank you! Please tell him to come here right now. Oh my, why does he have to be such a nuisance...";
			link.l1 = "Don't worry. I will send him your way.";
			link.l1.go = "exit";
			pchar.questTemp.Shadowtrader.City = npchar.City;
			pchar.questTemp.Shadowtrader.nation = sti(npchar.nation);
			//создаем охранника
			sld = GetCharacter(NPC_GenerateCharacter("ShadowGuarder" , "officer_7", "man", "man", 10, sti(npchar.nation), 5, true, "quest"));
			FantomMakeCoolFighter(sld, 20, 50, 50, "topor_2", "pistol3", "bullet", 50);
			sld.name = pchar.questTemp.Shadowtrader.Guardername;
			sld.lastname = "";
			sld.dialog.FileName = "Quest\LineMiniQuests\ShadowTrader.c";
			sld.dialog.currentnode = "ShadowGuarder";
			sld.greeting = "pirat_common";
			LAi_SetSitType(sld);
			LAi_SetImmortal(sld, true);
			FreeSitLocator(pchar.questTemp.Shadowtrader.City + "_tavern", "sit_front1");
			ChangeCharacterAddressGroup(sld, pchar.questTemp.Shadowtrader.City + "_tavern", "sit", "sit_front1");
			SaveCurrentNpcQuestDateParam(npchar, "Shadowtrader_date");
		break;
		
		case "Shadowtrader_fort":
			dialog.text = "To help? Oh, captain, I would really like your help. Could you please deliver this letter to the commandant as soon as possible? I would pay you 300 coins for that trivial deal - as I have already said, I cannot leave my shop.";
			link.l1 = "No problem. Give me that letter.";
			link.l1.go = "Shadowtrader_fort_1";
			link.l2 = "No, my good man, I have no more time for that bullshit.";
			link.l2.go = "Shadowtrader_fort_end";
		break;
		
		case "Shadowtrader_fort_1":
			dialog.text = "Here you go. Please hand it to him today and deliver me his reply.";
			link.l1 = "Don't worry, I'll do it.";
			link.l1.go = "exit";
			GiveItem2Character(pchar, "letter_1");
			ChangeItemDescribe("letter_1", "itmdescr_letter_1"); // 240912
			pchar.questTemp.Shadowtrader.Tradername = GetFullName(npchar);
			SetFunctionTimerCondition("ShadowtraderTimeFort_Over", 0, 0, 1, false);
			pchar.questTemp.Shadowtrader = "current"
			pchar.questTemp.Shadowtrader.Fort = "true";
			AddQuestRecord("Shadowtrader", "1");
			AddQuestUserData("Shadowtrader", "sCity", XI_ConvertString("Colony"+pchar.questTemp.Shadowtrader.City+"Gen"));
		break;
		
		case "Shadowtrader_fort_end":
			dialog.text = "Well, apparently I'll have to ask someone else. Sorry to have bothered you, captain.";
			link.l1 = "No problem. Goodbye!";
			link.l1.go = "exit";
			pchar.questTemp.Shadowtrader = "true";
		break;
		
		case "Shadowtrader_trouble":
			dialog.text = "That's what he said? What evidence does he need from me, then?! My corpse? Well, there soon will be one, if it keeps going like that!..";
			link.l1 = "Wow, wow, " + npchar.name + ", calm down, or you will suffer a stroke. Here, drink some water... Now tell me, what's the matter - perhaps, I'd be able to help you?";
			link.l1.go = "Shadowtrader_trouble_1";
			DeleteAttribute(pchar, "questTemp.Shadowtrader.Trouble");
		break;
		
		case "Shadowtrader_trouble_1":
			dialog.text = "Oh, captain! Please take your 300 pesos - I've almost forgotten... Of course, I'll tell you, but I am not sure how you'd be able to help me. My business is nearly ruined - all because of those cursed smugglers and that unknown bastard who leads them.";
			link.l1 = "Smugglers?";
			link.l1.go = "Shadowtrader_trouble_2";
			AddMoneyToCharacter(pchar, 300);
		break;
		
		case "Shadowtrader_trouble_2":
			dialog.text = "That's it! These rascals have obviously decided to kick me out of town! Until then everything was as usual - they resold prohibited items, patrol catched them if they succeeded, they hid and paid off. But recently they have opened somewhere in a backstreet shop and began selling the most popular goods at incredibly low prices!\nI can not afford that luxury - in fact I have to pay taxes - I progressively impoverished myself and seamen almost don't want my goods - all goods they buy from these rogues.";
			link.l1 = "But you should've appealed to the authorities! After all, it's their job - stopping such lawlessness.";
			link.l1.go = "Shadowtrader_trouble_3";
		break;
		
		case "Shadowtrader_trouble_3":
			dialog.text = "Last appeal result you saw yourself. The governor is too busy and the commandant did not believe that smugglers organized backstreet store, or pretends he does not believe - and, I suppose, that's the case\nOf course, why would they do that? And I say: I'm sure it all came up with some rascal who wants to destroy and expel me out of town, and then he will quietly tidy up my business to clean their dirty little hands.";
			link.l1 = "Hm... your opinion is not unfounded. It's in the nature of merchants - making a cat's paw out of someone... Oh, I am sorry, I didn't mean you, of course. ";
			link.l1.go = "Shadowtrader_trouble_4";
		break;
		
		case "Shadowtrader_trouble_4":
			dialog.text = "Oh, nothing... And recently some ragamuffin came to me and brazenly said that if I continued to making noise, they would burn my shop\nSo I hired a bodyguard. "+pchar.questTemp.Shadowtrader.Guardername+" does not come cheap, but he's a professional and under his protection I can feel a little calmer.";
			link.l1 = "I see... An unpleasant story, indeed. Apparently, you were right - there's nothing I can do for you. But still, I am certain that things will work themselves out - such shady establishments usually do not last for long. Well, best of luck!";
			link.l1.go = "Shadowtrader_end";
			link.l2 = "I see. Well, perhaps I'd still be able to help you out...";
			link.l2.go = "Shadowtrader_trouble_5";
		break;
		
		case "Shadowtrader_trouble_5":
			dialog.text = "You're offering me your help anyway? But what are you going to do?";
			link.l1 = "I will try to find that 'colleague' of yours and... persuade him to get off your back. You know, I have certain skills at persuading people.";
			link.l1.go = "Shadowtrader_trouble_6";
		break;
		
		case "Shadowtrader_trouble_6":
			dialog.text = "Are you serious? May the Lord bless your just cause! If you rid me of that filth, I will not be in your debt.";
			link.l1 = "Alright, consider it a deal. I will start searching, then.";
			link.l1.go = "exit";
			pchar.questTemp.Shadowtrader.seeksmugglers = "true";
			AddQuestRecord("Shadowtrader", "2");
			AddQuestUserData("Shadowtrader", "sCity", XI_ConvertString("Colony"+pchar.questTemp.Shadowtrader.City+"Gen"));
		break;
		
		case "Shadowtrader_end":
			pchar.questTemp.Shadowtrader = "true";
			CloseQuestHeader("Shadowtrader");
			DialogExit();
		break;
		
		case "Shadowtrader_Escape_complete":
			dialog.text = "Is that true? I can now do business without any fear? Oh, thank you so much! Here's your reward - 15000 pesos. As for the goods in their house, I guess it's best to hand them over to the commandant. Thank you again!";
			link.l1 = "You're welcome. It wasn't too hard. I told you I was good at persuasion.";
			link.l1.go = "Shadowtrader_complete";
		break;
		
		case "Shadowtrader_complete":
			dialog.text = "Come visit me again, captain - I will always be happy to see you.";
			link.l1 = "Of course! And now allow me to take my leave - I have things to do! Goodbye and good luck in your trade, " + npchar.name + "!";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.Shadowtrader.End");
			AddMoneyToCharacter(pchar, 15000);
			pchar.questTemp.Shadowtrader = "complete";
			AddQuestRecord("Shadowtrader", "11");
			CloseQuestHeader("Shadowtrader");
		break;
	// <-- мини-квест Бесчестный конкурент
	
//Jason --> мини-квест Дефицитный товар
		case "Wine_Trader":
			dialog.text = "What are you talking about? Clearly, you were misled - I never dealt in European wine in such amounts. One-two bottles, not more. But the local wine is a different story - I have enough of that stuff, and it is sold by demijohns, not bottles!";
			link.l1 = "Dash it! But I was told...";
			link.l1.go = "Wine_Trader_1";
		break;
		
		case "Wine_Trader_1":
			dialog.text = "I have no idea what you've been told, but I'll say it again: I have no European wine in stock. That's all I have to say regarding this matter.";
			link.l1 = "Alright... I`ll go sort it out then, then!";
			link.l1.go = "exit";
			AddQuestRecord("Wine", "5");
			AddQuestUserData("Wine", "sName", pchar.questTemp.Wine.Name);
			DeleteAttribute(pchar, "questTemp.Wine.Trader");
			pchar.questTemp.Wine.Repeat1 = "true";
		break;
		
		case "Wine_Repeat2":
			RemoveItems(PChar, "letter_1", 1);
			PlaySound("interface\important_item.wav");
			dialog.text = "Now that's a different story. You know, various types are coming here, asking unnecessary questions. So, let's bargain, then?";
			link.l1 = "Sure!";
			link.l1.go = "Wine_Price";
			pchar.questTemp.Wine.wait = "true";
			DeleteAttribute(pchar, "questTemp.Wine.Repeat2");
			SetFunctionTimerCondition("Wine_wait", 0, 0, 7, false);
		break;
		
		case "Wine_Price":
			dialog.text = "How many bottles you need? The price of one bottle is 500 pesos, and the minimum batch is 20 bottles.";
			link.l1 = "";
			Link.l1.edit = 4;
			link.l1.go = "Wine_Qty";
			link.l2 = "I don't have enough money right now. I'll come back later.";
			link.l2.go = "Wine_Qty_exit";
		break;
		
		case "Wine_Qty":
			int iQty = sti(dialogEditStrings[4]);
			pchar.questTemp.Wine.Qty = sti(iQty);
			if (iQty < 20)
			{
				dialog.text = "I am not a peddler, captain. As I can recall, you were talking about a larger batch?";
				link.l1 = "I am sorry... Let's reconsider the amount, then.";
				link.l1.go = "Wine_Price";
				break;
			}
			if (iQty > 70)
			{
				dialog.text = "Unfortunately, I don't have that much.";
				link.l1 = "Pity... Let's reconsider the amount, then.";
				link.l1.go = "Wine_Price";
				break;
			}
			pchar.questTemp.Wine.Summ = sti(iQty)*500;
			dialog.text = ""+sti(iQty)+" Bottles? Fine. That will cost you " + FindRussianMoneyString(sti(pchar.questTemp.Wine.Summ))".";
			if (makeint(Pchar.money) >= sti(pchar.questTemp.Wine.Summ))
			{
				link.l1 = "Here you go.";
				link.l1.go = "Wine_Qty_1";
			}
			link.l2 = "I don't have enough money right now. I'll come back later.";
			link.l2.go = "Wine_Qty_exit";
		break;
		
		case "Wine_Qty_exit":
			dialog.text = "That's okay, but try not to take too long. This stuff is quite popular here.";
			link.l1 = "I'll be back soon!";
			link.l1.go = "exit";
		break;
		
		case "Wine_Qty_1":
			AddMoneyToCharacter(pchar, -sti(pchar.questTemp.Wine.Summ));
			dialog.text = "Let's see... Everything seems okay. You can collect your purchase.";
			link.l1 = "Thank you! Best of luck!";
			link.l1.go = "Wine_Qty_2";
		break;
		
		case "Wine_Qty_2":
			pchar.quest.Wine_wait.over = "yes";//снять прерывание
			DeleteAttribute(pchar, "questTemp.Wine.wait");
			TakeNItems(pchar, "potionwine", sti(pchar.questTemp.Wine.Qty));
			PlaySound("interface\important_item.wav");
			Log_Info ("You have received wine");
			AddQuestRecord("Wine", "8");
			DialogExit();
		break;
		// <-- мини-квест Дефицитный товар
		
// Jason --> -------------------------генератор Сомнительное предложение----------------------------------------
		int iCGood, amount;
		case "Contraoffer":
			pchar.GenQuest.Contraoffer.Trader.Goods = SelectContrabandGoods(pchar);
			while (sti(pchar.GenQuest.Contraoffer.Trader.Goods) == -1)
			{
				pchar.GenQuest.Contraoffer.Trader.Goods = SelectContrabandGoods(pchar);
			}
			iCGood = sti(pchar.GenQuest.Contraoffer.Trader.Goods);
			pchar.GenQuest.Contraoffer.Trader.Qty = makeint(15*(sti(pchar.rank)+30)/(sti(Goods[iCGood].Weight)/sti(Goods[iCGood].Units))*(7-sti(RealShips[sti(pchar.ship.type)].Class)));//количество
			pchar.GenQuest.Contraoffer.Trader.Price = sti(Goods[iCGood].Cost)/sti(Goods[iCGood].Units)*3;//цена единицы товара
			pchar.GenQuest.Contraoffer.Trader.Summ = sti(pchar.GenQuest.Contraoffer.Trader.Price)*sti(pchar.GenQuest.Contraoffer.Trader.Qty);//сумма
			pchar.GenQuest.Contraoffer.Trader.Days = 30+drand(20);//срок
			pchar.GenQuest.Contraoffer.Trader.Chance = rand(5);//17% вероятности, что патруль накроет
			dialog.text = "I planned to strike a good bargain, but I still need for it a particular merchandise - " + GetGoodsNameAlt(iCGood)+ ". The problem is that this merchandise in our colony is a contraband, so I can't count on buying it from trading captains\nAll I need are " + FindRussianQtyString(sti(pchar.GenQuest.Contraoffer.Trader.Qty)) + " units of it. Perhaps, you could deliver it to me? I will pay you well, " + FindRussianMoneyString(sti(pchar.GenQuest.Contraoffer.Trader.Price)) + " per unit, which will amount to " + FindRussianMoneyString(sti(pchar.GenQuest.Contraoffer.Trader.Summ)) + ". Oh, and I need it no later than in "+FindRussianDaysString(sti(pchar.GenQuest.Contraoffer.Trader.Days))+". So, will you help me?";
			link.l1 = "Hmm... Sounds interesting. I agree!";
			link.l1.go = "Contraoffer_1";
			link.l2 = "Delivering smuggled goods? Sorry, not interested.";
			link.l2.go = "exit";
			SaveCurrentNpcQuestDateParam(npchar, "Contraoffer");
		break;
		
		case "Contraoffer_1":
			dialog.text = "Excellent. I am glad that you agreed. So, I'll be waiting for your return with the goods.";
			link.l1 = "I will soon be back!";
			link.l1.go = "exit";
			rColony = GetColonyByIndex(FindColony(npchar.city));
			SetNull2StoreGood(rColony, sti(pchar.GenQuest.Contraoffer.Trader.Goods));//нулим товар
			pchar.GenQuest.Contraoffer = "begin";
			pchar.GenQuest.Contraoffer.Trader = "true";
			pchar.GenQuest.Contraoffer.Trader.City = npchar.city;
			pchar.GenQuest.Contraoffer.Trader.Nation = npchar.nation;
			iCGood = pchar.GenQuest.Contraoffer.Trader.Goods;
			ReOpenQuestHeader("Contraoffer");
			AddQuestRecord("Contraoffer", "1");
			AddQuestUserData("Contraoffer", "sGoods", GetGoodsNameAlt(iCGood));
			AddQuestUserData("Contraoffer", "sGoodQty", FindRussianQtyString(sti(pchar.GenQuest.Contraoffer.Trader.Qty)));
			AddQuestUserData("Contraoffer", "sMoney", FindRussianMoneyString(sti(pchar.GenQuest.Contraoffer.Trader.Summ)));
			AddQuestUserData("Contraoffer", "sCity", XI_ConvertString("Colony"+pchar.GenQuest.Contraoffer.Trader.City+"Gen"));
			AddQuestUserData("Contraoffer", "sDays", FindRussianDaysString(sti(pchar.GenQuest.Contraoffer.Trader.Days)));
			SetFunctionTimerCondition("Contraoffer_Over", 0, 0, sti(pchar.GenQuest.Contraoffer.Trader.Days), false);
		break;
		
		case "Contraoffer_check":
			iCGood = sti(pchar.GenQuest.Contraoffer.Trader.Goods);
			amount = sti(pchar.GenQuest.Contraoffer.Trader.Qty) - GetSquadronGoods(pchar, sti(pchar.GenQuest.Contraoffer.Trader.Goods));
			if (amount > 0)
			{
				dialog.text = "Are you joking? You don't have the full amount of goods I need!";
				link.l1 = "I am sorry, my bad...";
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = "Let's see, then. You were supposed to deliver a load of " + GetGoodsNameAlt(iCGood)+ " in amount of " + FindRussianQtyString(pchar.GenQuest.Contraoffer.Trader.Qty) + ". Correct?";
				link.l1 = "Exactly, " + GetAddress_FormToNPC(NPChar) + ".";
				link.l1.go = "Contraoffer_pay";
			}
		break;
		
		case "Contraoffer_pay":
			dialog.text = "Thanks for your work. Please, take your payment - " + FindRussianMoneyString(sti(pchar.GenQuest.Contraoffer.Trader.Summ)) + ".";
		link.l1 = "Thank you! Pleasure doing business with you.";
		link.l1.go = "Contraoffer_complete";
		break;
		
		case "Contraoffer_complete":
			pchar.quest.Contraoffer_Over.over = "yes";
			RemoveCharacterGoods(pchar, sti(pchar.GenQuest.Contraoffer.Trader.Goods), sti(pchar.GenQuest.Contraoffer.Trader.Qty));
			AddMoneyToCharacter(pchar, sti(pchar.GenQuest.Contraoffer.Trader.Summ));
			SaveCurrentNpcQuestDateParam(npchar, "Contraoffer");
			npchar.quest.Contraoffer.chance = rand(2);//личный шанс торговца для 'пасхалки'
			AddCharacterExpToSkill(pchar, "Sailing", 100);//навигация
			AddCharacterExpToSkill(pchar, "Commerce", 100);//торговля
			AddCharacterExpToSkill(pchar, "Leadership", 50);//авторитет
			AddCharacterExpToSkill(pchar, "Fortune", 100);//везение
			ChangeCharacterComplexReputation(pchar,"nobility", -1);
			if (pchar.GenQuest.Contraoffer.Trader.Chance == 3)
			{
				dialog.text = "Oops... Captain, seems like we have a problem here...";
				link.l1 = "What is it again?";
				link.l1.go = "exit";
				AddDialogExitQuestFunction("Contraoffer_Patrol");
				pchar.GenQuest.Contraoffer.Trader.busy = "true";
				pchar.quest.Contraoffer_busy.win_condition.l1 = "ExitFromLocation";
				pchar.quest.Contraoffer_busy.win_condition.l1.location = pchar.location;
				pchar.quest.Contraoffer_busy.function = "Trader_free";
			}
			else
			{
				DialogExit();
				AddQuestRecord("Contraoffer", "3");
				CloseQuestHeader("Contraoffer");
				DeleteAttribute(pchar, "GenQuest.Contraoffer.Trader");
			}
		break;
		
		case "Contraoffer_slaves"://единичный вариант за всю игру, ака 'пасхалка'
			pchar.GenQuest.Contraoffer.Slaves.Name = GetFullName(npchar);
			pchar.GenQuest.Contraoffer.Slaves.Price = 300;//цена на рабов, пока фиксированная, можно подставить формулу
			pchar.GenQuest.Contraoffer.Slaves.Qty = 300+rand(50);//количество
			pchar.GenQuest.Contraoffer.Slaves.Days = 14+rand(6);//срок
			pchar.GenQuest.Contraoffer.Slaves.Money = sti(pchar.GenQuest.Contraoffer.Slaves.Qty)*sti(pchar.GenQuest.Contraoffer.Slaves.Price);
			dialog.text = "I urgently need a batch of slaves - "+sti(pchar.GenQuest.Contraoffer.Slaves.Qty)+" heads. I am ready to pay "+sti(pchar.GenQuest.Contraoffer.Slaves.Price)+" coins per soul, which will amount to "+sti(pchar.GenQuest.Contraoffer.Slaves.Money)+" pesos in total; term - "+FindRussianDaysString(sti(pchar.GenQuest.Contraoffer.Slaves.Days))+".";
			link.l1 = "I think I am going to agree. It's bothersome, but very profitable business.";
			link.l1.go = "Contraoffer_slaves_1";
			link.l2 = "I am not interested.";
			link.l2.go = "exit";
			pchar.GenQuest.Contraoffer.Slaves = "begin";
		break;
		
		case "Contraoffer_slaves_1":
			dialog.text = "Exactly - it's very profitable indeed. Well, then I will be waiting for your return with my slaves.";
			link.l1 = "I will not keep you waiting for long. See you!";
			link.l1.go = "exit";
			pchar.GenQuest.Contraoffer.Slaves.Yes = "begin";
			pchar.GenQuest.Contraoffer.Slaves.City = npchar.city;
			ReOpenQuestHeader("Contraoffer");
			AddQuestRecord("Contraoffer", "4");
			AddQuestUserData("Contraoffer", "sDays", FindRussianDaysString(sti(pchar.GenQuest.Contraoffer.Slaves.Days)));
			AddQuestUserData("Contraoffer", "sGoodQty", FindRussianQtyString(sti(pchar.GenQuest.Contraoffer.Slaves.Qty)));
			AddQuestUserData("Contraoffer", "sMoney", FindRussianMoneyString(sti(pchar.GenQuest.Contraoffer.Slaves.Money)));
			AddQuestUserData("Contraoffer", "sCity", XI_ConvertString("Colony"+pchar.GenQuest.Contraoffer.Slaves.City+"Gen"));
			SetFunctionTimerCondition("Contraoffer_Over", 0, 0, sti(pchar.GenQuest.Contraoffer.Slaves.Days), false);
		break;
		
		case "Contraoffer_slaves_check":
			amount = sti(pchar.GenQuest.Contraoffer.Slaves.Qty) - GetSquadronGoods(pchar, GOOD_SLAVES);
			if (amount > 0)
			{
				dialog.text = "Are you joking? You don't have all the slaves I need!";
				link.l1 = "I am sorry, my bad...";
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = "Let's see, then. You were going to deliver to me a batch of slaves in the amount of " + FindRussianQtyString(pchar.GenQuest.Contraoffer.Slaves.Qty) + ". Correct?";
				link.l1 = "Exactly, " + GetAddress_FormToNPC(NPChar) + ".";
				link.l1.go = "Contraoffer_slaves_pay";
			}
		break;
		
		case "Contraoffer_slaves_pay":
			dialog.text = "Thanks for your work. Please take your payment - " + FindRussianMoneyString(sti(pchar.GenQuest.Contraoffer.Slaves.Money)) + ". Also, please accept this. I am certain you will find it useful.";
			link.l1 = "Thank you! Pleasure doing business with you.";
			link.l1.go = "Contraoffer_slaves_complete";
		break;
		
		case "Contraoffer_slaves_complete":
			DialogExit();
			pchar.quest.Contraoffer_Over.over = "yes";
			RemoveCharacterGoods(pchar, GOOD_SLAVES, sti(pchar.GenQuest.Contraoffer.Slaves.Qty));
			AddMoneyToCharacter(pchar, sti(pchar.GenQuest.Contraoffer.Slaves.Money));
			AddQuestRecord("Contraoffer", "5");
			CloseQuestHeader("Contraoffer");
			SaveCurrentNpcQuestDateParam(npchar, "Contraoffer");
			AddCharacterExpToSkill(pchar, "Sailing", 150);//навигация
			AddCharacterExpToSkill(pchar, "Commerce", 200);//торговля
			AddCharacterExpToSkill(pchar, "Leadership", 50);//авторитет
			AddCharacterExpToSkill(pchar, "Fortune", 150);//везение
			TakeNItems(pchar, "cirass3", 1);
			ChangeCharacterComplexReputation(pchar,"nobility", -3);
			DeleteAttribute(pchar, "GenQuest.Contraoffer.Slaves.Yes");
		break;
		// <-- генератор Сомнительное предложение
		
		//Jason --> генератор Неудачливый вор
		case "Device_Trader":
			dialog.text = "Hmm, "+pchar.GenQuest.Device.Shipyarder.Type+"? Never heard of it before... Just what is it, actually? I've never heard about such a thing in all my time.";
			link.l1 = "Well, it's a shipwright's tool, "+pchar.GenQuest.Device.Shipyarder.Describe+". Was anyone offering to you anything like that?";
			link.l1.go = "Device_Trader_1";
			npchar.quest.Device = "true";
		break;
		
		case "Device_Trader_1":
			if (sti(pchar.GenQuest.Device.Shipyarder.Chance1) == 0)
			{
				dialog.text = "Hmm... Yeah, there was one strange guy. But he didn't tell me what that thing was, he just tried to sell it to me. But what would I need it for, if I have no idea what's it for? How will I resell it? So, I just refused.";
				link.l1 = "And how did he look like and where did he go? I need that instrument badly.";
				link.l1.go = "Device_Common";
			}
			else
			{
				dialog.text = "No, nothing like that. Sorry, I can't help you. Ask around.";
				link.l1 = "I see. Well - time to ask around!";
				link.l1.go = "exit";
			}
		break;
		// <-- генератор Неудачливый вор

		//Jason --> генератор Место под солнцем
		case "Sunplace_begin":
			dialog.text = "Competition... There's no business without it. Greedy bastards and strive to break into your a cozy business and acting all sorts of nefarious methods to entice clientele to themselves\nBut it's the lyrics. And in fact, I would like to ask you to help me get rid of one of those of my competitors. No, kill it is not necessary. Simply capture or sink his ship with cargo.";
			link.l1 = "Hmm... well, if you are paying well, I can arrange this.";
			link.l1.go = "Sunplace_1";
			link.l2 = "No, I am not interfering in your mercantile quarrels. Go sink your rival without my aid.";
			link.l2.go = "Sunplace_exit";
		break;
		
		case "Sunplace_exit"://если отказал - этот непись больше никогда не даст
			npchar.quest.Sunplace = "true";
			DialogExit();
		break;
		
		case "Sunplace_1":
			GetSunplaceShore();//бухта и остров
			pchar.GenQuest.Sunplace.Trader.Enemyname = GenerateRandomName_Generator(sti(npchar.nation), "man");//имя конкурента
			pchar.GenQuest.Sunplace.Trader.Nation = npchar.nation;//нация общая для торговца и конкурента
			pchar.GenQuest.Sunplace.Trader.City = npchar.City;//город квестодателя
			pchar.GenQuest.Sunplace.Trader.CityT = findSunplaceCity(NPChar);//город конкурента
			pchar.GenQuest.Sunplace.Trader.Shiptype = Sunplace_Shiptype();//тип корабля
			pchar.GenQuest.Sunplace.Trader.ShipName = GenerateRandomNameToShip(sti(NPChar.nation));//имя корабля
			pchar.GenQuest.Sunplace.Trader.DaysQty = 5 + drand(5);//дни
			pchar.GenQuest.Sunplace.Trader.Money = sti(pchar.GenQuest.Sunplace.Trader.Shiptype)*3000;//оплата
			pchar.GenQuest.Sunplace.Trader.Goods = GOOD_COFFEE + drand(sti(GOOD_PAPRIKA - GOOD_COFFEE));//товар
			dialog.text = "Very well. So, the name of your man is "+pchar.GenQuest.Sunplace.Trader.Enemyname+". Recently he had sent out "+GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.Sunplace.Trader.ShipType), "Name") + "Acc"))+" '"+pchar.GenQuest.Sunplace.Trader.ShipName+"' with a cargo of " + GetGoodsNameAlt(sti(pchar.GenQuest.Sunplace.Trader.Goods))+ ". He paid quite a decent sum for this cargo, so losing it will be quite a hit at his purse.";
			link.l1 = "And could you tell me, where exactly to look for that 'friend' of yours?";
			link.l1.go = "Sunplace_2";
		break;
		
		case "Sunplace_2":
			dialog.text = "My 'friend' is currently at his home in "+XI_ConvertString("Colony"+pchar.GenQuest.Sunplace.Trader.CityT+"Abl")+". You don't need him - you need his ship, which, as I found out after about "+FindRussianDaysString(sti(pchar.GenQuest.Sunplace.Trader.DaysQty))+" will be passing near " + XI_ConvertString(pchar.GenQuest.Sunplace.Trader.Shore+"Gen") + ". You can sink it, can take for the boarding - does not matter. The main thing to make the ship and the cargo being no longer the property of "+pchar.GenQuest.Sunplace.Trader.Enemyname +". And I don't care, who's gonna claim it - you or the sea. For that job I will pay you " + FindRussianMoneyString(sti(pchar.GenQuest.Sunplace.Trader.Money))".";
			link.l1 = "I got it. Well, time to depart then!";
			link.l1.go = "Sunplace_3";
		break;
		
		case "Sunplace_3":
			DialogExit();
			pchar.GenQuest.Sunplace.Trader = "true";
			if (sti(pchar.GenQuest.Sunplace.Chance) == 1 && sti(pchar.rank) > 9) pchar.GenQuest.Sunplace.Bonus = "true";
			ReOpenQuestHeader("Sunplace");
			AddQuestRecord("Sunplace", "1");
			AddQuestUserData("Sunplace", "sGoods", GetGoodsNameAlt(sti(pchar.GenQuest.Sunplace.Trader.Goods)));
			AddQuestUserData("Sunplace", "sDay", FindRussianDaysString(sti(pchar.GenQuest.Sunplace.Trader.DaysQty)));
			AddQuestUserData("Sunplace", "sMoney", FindRussianMoneyString(sti(pchar.GenQuest.Sunplace.Trader.Money)));
			AddQuestUserData("Sunplace", "sCity", XI_ConvertString("Colony"+pchar.GenQuest.Sunplace.Trader.City+"Gen"));
			AddQuestUserData("Sunplace", "sType", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.Sunplace.Trader.ShipType), "Name") + "Acc")));
			AddQuestUserData("Sunplace", "sSName", pchar.GenQuest.Sunplace.Trader.ShipName);
			AddQuestUserData("Sunplace", "sName", GetFullName(npchar));
			AddQuestUserData("Sunplace", "sShore", XI_ConvertString(pchar.GenQuest.Sunplace.Trader.Shore+"Gen"));
			SetFunctionTimerCondition("Sunplace_Over", 0, 0, sti(pchar.GenQuest.Sunplace.Trader.DaysQty), false);
			pchar.quest.Sunplace_Trader.win_condition.l1 = "location";
			pchar.quest.Sunplace_Trader.win_condition.l1.location = pchar.GenQuest.Sunplace.Trader.Island;
			pchar.quest.Sunplace_Trader.win_condition.l2 = "Timer";
			pchar.quest.Sunplace_Trader.win_condition.l2.date.hour  = sti(GetTime());
			pchar.quest.Sunplace_Trader.win_condition.l2.date.day   = GetAddingDataDay(0, 0, makeint(sti(pchar.GenQuest.Sunplace.Trader.DaysQty)-2));
			pchar.quest.Sunplace_Trader.win_condition.l2.date.month = GetAddingDataMonth(0, 0, makeint(sti(pchar.GenQuest.Sunplace.Trader.DaysQty)-2));
			pchar.quest.Sunplace_Trader.win_condition.l2.date.year  = GetAddingDataYear(0, 0, makeint(sti(pchar.GenQuest.Sunplace.Trader.DaysQty)-2));
			pchar.quest.Sunplace_Trader.function = "Sunplace_CreateTraderShip";
		break;
		
		case "Sunplace_complete":
			dialog.text = "Excellent! I knew that I could count on you. I guess I will not be asking about the whereabouts of that ship and the cargo. It's not my business, after all. And my friend will need quite some time to recover from such a blow, he-he. Here, please take your money - and thank you for a great job.";
			link.l1 = "You're welcome... See you, " + npchar.name + "!";
			link.l1.go = "Sunplace_complete_1";
		break;
		
		case "Sunplace_complete_1":
			AddMoneyToCharacter(pchar, sti(pchar.GenQuest.Sunplace.Trader.Money));
			AddQuestRecord("Sunplace", "12");
			CloseQuestHeader("Sunplace");
			pchar.GenQuest.Sunplace.Chance = rand(2);
			AddComplexSeaExpToScill(50, 50, 50, 50, 50, 0, 0);
			AddComplexSelfExpToScill(20, 20, 20, 20);
			AddCharacterExpToSkill(pchar, "Fortune", 100);//везение
			DeleteAttribute(pchar, "GenQuest.Sunplace.Trader");
			DialogExit();
		break;
		
		case "Sunplace_complete_murder":
			dialog.text = "Poor "+pchar.GenQuest.Sunplace.Trader.Enemyname+", what a gruesome fate! And though indirect, I am the cause of his demise! You don't understand, captain! Did I ask you to kill him? I planned that after the loss of money spent on the cargo he would again have to... well, nevermind... You...";
			link.l1 = "Hey, listen - stop your whining, alright? You asked me to rid you of a rival - I did it. Even better - having lost the cargo, he still could become rich again and continue harming your business. Now there is not much he can do being a dead man.";
			link.l1.go = "Sunplace_complete_murder_1";
		break;
		
		case "Sunplace_complete_murder_1":
			dialog.text = "That's it! Enough! I don't want to hear these blasphemous speeches no more! Take your bloody money and leave my shop at once!";
			link.l1 = "Hey, " + npchar.name + ", calm down, will you? Or I will cool your temper down myself - my saber is always at my side! Alright, don't get scared, I was just kidding. Listen, I am sorry it turned out like this - but it was you who had misled me in the first place. Farewell.";
			link.l1.go = "Sunplace_complete_murder_2";
		break;
		
		case "Sunplace_complete_murder_2":
			AddMoneyToCharacter(pchar, sti(pchar.GenQuest.Sunplace.Trader.Money));
			AddQuestRecord("Sunplace", "13");
			AddQuestUserData("Sunplace", "sName", GetFullName(npchar));
			CloseQuestHeader("Sunplace");
			npchar.quest.Sunplace = "true";//этот непись повторно квест больше не даст
			AddComplexSeaExpToScill(50, 50, 50, 50, 50, 0, 0);
			AddComplexSelfExpToScill(30, 30, 30, 30);
			AddCharacterExpToSkill(pchar, "Fortune", 50);//везение
			DeleteAttribute(pchar, "GenQuest.Sunplace.Trader");
			DialogExit();
		break;
		
		//Jason --> поиск дезертира
		case "FindFugitiveSt":
			if (NPChar.city == pchar.GenQuest.FindFugitive.City && sti(pchar.GenQuest.FindFugitive.Chance) == 1)
			{
				dialog.text = NPCStringReactionRepeat(""+pchar.GenQuest.FindFugitive.Name+"? Yeah, I know him. He purchased provisions for his long boat from me. During the day he is usually fishing somewhere in secluded coves, but every evening he can be found in the tavern.", "You have already asked me about that man, and I told you everything I knew!", "Are you kidding me or you're an idiot indeed?! You're asking all the same for a third time already!", "Just to think, how such an idiot became captain...", "block", 1, npchar, Dialog.CurrentNode);
				link.l1 = HeroStringReactionRepeat("Thank you, you've helped me immensely!", "Yeah, yeah, fine.", "Now, now, don't get so excited. I just forgot.", "Well, he did, as you can see...", npchar, Dialog.CurrentNode); 
				link.l1.go = DialogGoNodeRepeat("FindFugitiveSt_1", "exit", "", "", npchar, Dialog.CurrentNode);
			}
			else
			{
				dialog.text = NPCStringReactionRepeat("I don't know what people were saying at the tavern of Port Royal, but I never met that man in my shop. Actually, I've never seen him anywhere. Ask around in the village - perhaps, someone will tell you...", "You have already asked me about that man, and I told you: I don't know!", "Are you kidding me or you're an idiot indeed?! You're asking all the same for a third time already!", "Just to think, how such an idiot became captain...", "block", 1, npchar, Dialog.CurrentNode);
				link.l1 = HeroStringReactionRepeat("I see. Well, thanks anyway.", "Yeah, yeah, fine.", "Now, now, don't get so excited. I just forgot.", "Well, he did, as you can see...", npchar, Dialog.CurrentNode); 
				link.l1.go = DialogGoNodeRepeat("exit", "", "", "", npchar, Dialog.CurrentNode);	
			}
		break;
		
		case "FindFugitiveSt_1":
			DialogExit();
			AddQuestRecord("MayorsQuestsList", "12-2");
			sld = characterFromId("Fugitive");
			LAi_SetSitType(sld);
			sld.dialog.currentnode = "Fugitive_tavern";
			LAi_SetLoginTime(sld, 20.0, 23.99);
			FreeSitLocator(pchar.GenQuest.FindFugitive.City + "_tavern", "sit_front1");
			ChangeCharacterAddressGroup(sld, pchar.GenQuest.FindFugitive.City+"_tavern", "sit", "sit_front1");
		break;
		//<-- поиск дезертира
		
		// --> Карибские нравы - временное завершение
		case "trial":
			dialog.text = "My Lord, what's the matter with you, young man! Please, be more restraint and choose your words carefully when talking about respected people! Gerard LeCroix left Guadeloupe with an expedition to the mainland, but he left your reward here for you. Are you satisfied now?";
			link.l1 = "Hm... Please, excuse me, monsieur. I got heated up a bit...";
			link.l1.go = "trial_1";
		break;
		
		case "trial_1":
			dialog.text = "Very good. Next time try to ask first, and then crying out loud. Here you go - 400 golden doubloons. I believe you're satisfied with your reward?";
			link.l1 = "Absolutely. Once again, I beg your pardon. Now please excuse me.";
			link.l1.go = "trial_2";
		break;
		
		case "trial_2":
			TakeNItems(pchar, "gold_dublon", 400);
			Log_Info("You have received 400 doubloons");
			PlaySound("interface\important_item.wav");
			dialog.text = "Best regards, monsieur.";
			link.l1 = "...";
			link.l1.go = "trial_3";
		break;
		
		case "trial_3":
			DialogExit();
            NextDiag.CurrentNode = NextDiag.TempNode;
			DeleteAttribute(pchar, "questTemp.Trial");
			DeleteAttribute(npchar, "quest.trial_usurer");
			CloseQuestHeader("Trial");
		break;
		
		/*case "trial":
			dialog.text = "God, why are you so loud, young man! Calm down, and watch your tongue while talking about respected people! Gerard LeCroix left Guadeloupe with an expedition to the mainland, but for you he left a message\nDid you calm down, sir? Ready to listen to me?";
			link.l1 = "Hm... Please, excuse me, monsieur. I got heated up a bit. I am listening.";
			link.l1.go = "trial_1";
		break;
		
		case "trial_1":
			dialog.text = "Very good. Next time try to ask first, and then crying out loud. Alright... Do you know a man by the name Simon Maurois?";
			link.l1 = "Ha! Everyone has heard of Simon Maurois! Or course I know him.";
			link.l1.go = "trial_2";
			link.l2 = "Never heard about him. Who is he?";
			link.l2.go = "trial_3";
		break;
		
		case "trial_2":
			dialog.text = "Excellent. Go to him, then. It was him who financed the expedition of monsieur Shoke, so you can collect your reward from him. So, was it really necessary to get so steamed up?";
			link.l1 = "Once again, I beg for your pardon... Thanks for your help, monsieur. I will see monsieur Maurois at once!";
			link.l1.go = "trial_exit";
		break;
		
		case "trial_3":
			dialog.text = "He is the owner of Maurois banking house and the head of the branch in Capsterville. So you'll have to go to Saint-Christopher and visit the bank of Capsterville. It was monsieur Maurois who financed the expedition of monsieur Shoke, so you can collect your reward from him. So, was it really necessary to get so steamed up?";
			link.l1 = "Once again, I beg for your pardon... Thanks for your help, monsieur. I will see monsieur Maurois at once!";
			link.l1.go = "trial_exit";
		break;
		
		case "trial_exit":
			DialogExit();
            NextDiag.CurrentNode = NextDiag.TempNode;
			DeleteAttribute(npchar, "quest.trial_usurer");
			pchar.questTemp.Trial = "usurer";
			AddQuestRecord("Trial", "22");
		break;*/
		
		case "no_quests":
			dialog.text = "At the moment I have no need of your services.";
			link.l1 = "Pity. Let's change the subject.";
			link.l1.go = "node_1";
		break;
		
        case "fight":
			DialogExit();
            NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_group_Attack(NPChar, Pchar);
		break;
		
		case "Exit":			
			Nextdiag.CurrentNode = Nextdiag.TempNode;
			DialogExit();			
		break;
	}
	LanguageCloseFile(iSeaGoods);
}

int findStoreMan(ref NPChar, int iTradeNation)
{
    ref ch;
	int n;
    int storeArray[30];
    int howStore = 0;

	for(n=0; n<MAX_CHARACTERS; n++)
	{
		makeref(ch,Characters[n]);
        if (CheckAttribute(ch, "Dialog.Filename") && ch.Dialog.Filename == "Common_Store.c") // магазин
		{
            if (sti(ch.nation) !=  iTradeNation) continue;
            if (NPChar.id == ch.id) continue;
            if (NPChar.id == "Panama_trader" || ch.id == "Panama_trader") continue; //нельзя доплыть
			if (NPChar.id == "SanAndres_trader") continue;			
            if (ch.location == "none") continue; // фикс для новых, невидимых до поры островов
            if (GetIslandByCityName(ch.city) == GetIslandByCityName(NPChar.city)) continue; // хрен вам, а не читы!
            storeArray[howStore] = n;
            howStore++;
		}
    }
    if (howStore == 0)
    {
        return -1;
    }
    else
    {
        return storeArray[rand(howStore-1)];
    }
}

int Sunplace_Shiptype() // new
{
	int i;
	
	if (sti(pchar.rank) >= 1 && sti(pchar.rank) < 6) i = SHIP_SCHOONER;
	if (sti(pchar.rank) >= 6 && sti(pchar.rank) < 11) i = SHIP_FLEUT;
	if (sti(pchar.rank) >= 11 && sti(pchar.rank) < 18) i = SHIP_PINNACE;
	if (sti(pchar.rank) >= 18) i = SHIP_GALEON_L;
	
	return i;
}

string findSunplaceCity(ref NPChar) // new
{
	int n, nation;
    int storeArray[MAX_COLONIES];
    int howStore = 0;

	for(n=0; n<MAX_COLONIES; n++)
	{
		nation = GetNationRelation(sti(pchar.nation), sti(colonies[n].nation));
		if (nation != RELATION_ENEMY && colonies[n].id != "Panama" && colonies[n].id != "Minentown" && colonies[n].id != "SanAndres" && colonies[n].nation != "none" && GetIslandByCityName(npchar.city) != colonies[n].islandLable) //на свой остров
		{
			storeArray[howStore] = n;
			howStore++;
		}
	}
	if (howStore == 0) return "none";
	nation = storeArray[dRand(howStore-1)];
	return colonies[nation].id;
}