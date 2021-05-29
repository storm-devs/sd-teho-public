// общий диалог ростовщиков
#include "DIALOGS\russian\Rumours\Common_rumours.c"  //homo 25/06/06
void ProcessDialogEvent()
{
	ref NPChar, chr, sld;
	aref Link, NextDiag;
	string NPC_Area, sTemp, sTitle, sDepositType1, sDepositType2;
	int LoanSum, LoanInterest, LoanPeriod, LoanResult, iPastMonths, DepositSum, DepositInterest, DepositResult, iNum, iTemp, iTotalDublonQty;
	int iRes, iPer, iDep;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	string iDay, iMonth, s1;
	iDay = environment.date.day;
	iMonth = environment.date.month;
	string lastspeak_date = iday + " " + iMonth;

	NPC_Area = Npchar.City;
	sDepositType1 = NPC_Area + "_Type1";
	sDepositType2 = NPC_Area + "_Type2";
 
	if(!CheckAttribute(npchar, "quest.item_date"))
	{
		npchar.quest.item_date = "";
	} 
 
	// вызов диалога по городам -->
    NPChar.FileDialog2 = "DIALOGS\" + LanguageGetLanguage() + "\Usurer\" + NPChar.City + "_Usurer.c";
    if (LoadSegment(NPChar.FileDialog2))
	{
        ProcessCommonDialog(NPChar, Link, NextDiag);
		UnloadSegment(NPChar.FileDialog2);
	}
    // вызов диалога по городам <--
	ProcessCommonDialogRumors(NPChar, Link, NextDiag);//homo 16/06/06

	if (!CheckAttribute(npchar, "quest.trade_date"))
    {
        npchar.quest.trade_date = "";
    }
    if (!CheckAttribute(npchar, "quest.FindCitizenNoShip"))
    {
        npchar.quest.FindCitizenNoShip = 0;
    }

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
		break;
		
		case "First time":
			if (LAi_group_GetPlayerAlarm() > 0)
			{
				//--> работорговец
				if(pchar.questTemp.Slavetrader == "After_enterSoldiers" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
				{
					dialog.text = " It's over. Now leave this place, " + pchar.name + ". I'll clean all this mess.";
					link.l1 = "I ship out!";
					link.l1.go = "exit";
					break;
				}
				//<-- работорговец
			
       			dialog.text = NPCharRepPhrase(pchar, 
					LinkRandPhrase("The town is on alarm and they are searching for you everywhere! If I were you I would not stay here for long.", "All guards are looking for you. I am not an idiot and won't risk talking to you!", "Run, "+ GetSexPhrase("pal","girl") +", until soldiers will make a sieve from you..."), 
					LinkRandPhrase("What do you want, vile creature?! Town guards are aware of your position and you won't run away, "+ GetSexPhrase("filthy pirate","") +"!", "Dirty murderer, get away from my place! Guards!", "I don't fear you, vile creature! Soon you'll be hanged in our for, you won't get away..."));
				link.l1 = NPCharRepPhrase(pchar,
					RandPhraseSimple("Heh, it's not a problem for me...", "They'll never get me."), 
					RandPhraseSimple("Shut your mouth, " + GetWorkTypeOfMan(npchar, "") + ", or I will cut you bloody tongue!", "Heh, , " + GetWorkTypeOfMan(npchar, "") + ", want to catch a pirate too? Listen, lad, sit here quietly and you will live…"));
				link.l1.go = "fight";
				break;
			}
		//Jason ---------------------------------------Бремя гасконца------------------------------------
			if (CheckAttribute(pchar, "questTemp.Sharlie.Lock") && pchar.location == "Fortfrance_bank")
			{
				dialog.text = "Need something, monsieur?";
				Link.l1 = "I need information... I want to ask you about something.";
				Link.l1.go = "quests";
				Link.l2 = "How about a small loan?";
				Link.l2.go = "sharlie_credit";
				Link.l3 = "No, I've changed my mind.";
				Link.l3.go = "exit";
				break;
			}			
		//<-- Бремя гасконца
			
			//--> работорговец
			if (pchar.questTemp.Slavetrader == "canTakeQuest" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				dialog.Text = "Well, at last a worthy captain visited my place, I got so tired of idiots who think that I simply plant their doubloons and guineas and gather harvest every month in order to pay them their interest\nThey watch every penny, while having no idea how the poor usurer resorts to various tricks to avoid dying of starvation himself and, in the same time, to provide them with an opportunity to buy a goose for Christmas.";
				Link.l1 = "I suppose that your clients won't be glad to hear such words from the man who own their savings.";
				Link.l1.go = "GiveTaskSlave";
				npchar.quest.slave = "current";//чтобы камнем не долбил
				break;
			}	
			
			if (pchar.questTemp.Slavetrader == "TakeShoreCap_end" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				dialog.Text = "...";
				Link.l1 = "Listen, old hamster, you've really to do your best now to explain me everything! There were no slaves in that ship's cargo but a company of soldiers! It was really tough mission to deal with them! I am very angry, so you'd better explain yourself!";
				Link.l1.go = "Slaveshore_5";
				break;
			}	
			if (pchar.questTemp.Slavetrader == "Win_HavanaFort" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				dialog.Text = "Ah, here you are at last! The whole archipelago is gossiping about your bold attack. Glad to see you!";
				Link.l1 = "I would prefer an obscurity than that kind of fame... It's too dangerous.";
				Link.l1.go = "Win_Havana_Fort";
				break;
			}	
			if (pchar.questTemp.Slavetrader == "Havana_seekslaves" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				dialog.Text = "Have you brought my five thousand slaves?";
				if (GetSquadronGoods(Pchar, GOOD_SLAVES) >= 5000)
				{
					Link.l1 = "I have. They are in my cargo hold.";
					Link.l1.go = "Havana_Fort_yesA";
				}
				else
				{
					Link.l1 = "No, I am still working on this.";
					Link.l1.go = "exit";
				}
				break;
			}	
			
			if (pchar.questTemp.Slavetrader == "End_quest_bad" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				dialog.Text = "Hm.. Are you still alive? Strange. But it won't last long. Soldiers! Help! I've got a bandit here!";
				link.l1 = "Such a bastard!";
				link.l1.go = "exit";
				LAi_group_Attack(NPChar, Pchar);
				break;
			}
			
			if(pchar.questTemp.Slavetrader == "wait_6" && GetQuestPastDayParam("pchar.questTemp.Slavetrader_wait_6") > 6 && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				dialog.Text = "Good day. My name is " + GetFullName(npchar) + ". How can be on service?";
				link.l1 = "Oh! What are you doing here, sir?";
				link.l1.go = "Usurer_Escape";
				break;
			}
			//<-- работорговец
			// ФМК-Гваделупа
			if(CheckAttribute(pchar, "questTemp.FMQG") && pchar.questTemp.FMQG == "killers" && npchar.location == "BasTer_bank")
			{
				dialog.Text = "...";
				link.l1 = "Hey there, you bastard. Did you have a bright idea? Hired thugs to kill me? Wanted to shut me? Speak, now!";
				link.l1.go = "FMQG_x";
				break;
			}
			
			if(NPChar.quest.meeting == "0")
			{
				dialog.Text = LinkRandPhrase(LinkRandPhrase("Good day to you, "+GetAddress_Form(NPChar)+". How can I help you? Do I know you?","Come in, captain. My name is "+GetFullName(npchar)+" and I'm the local banker.","Nice to meet you, "+GetAddress_Form(NPChar)+"! I am a local banker and if you've got a money matter then I can help you."), LinkRandPhrase("Have we met before, captain? I am "+GetFullName(npchar)+", and I'm a local banker.","Come in, captain. My name is "+GetFullName(npchar)+" and I'm the local banker.","Greetings, "+GetAddress_Form(NPChar)+". I am "+GetFullName(npchar)+", the local banker."), LinkRandPhrase("Nice to meet you, "+GetAddress_Form(NPChar)+", I am "+GetFullName(npchar)+" just a modest banker the one in this wonderful town.","It is your call, captain! Want to borrow some coin from me or lend money on interest?","Sir captain! I'm so glad that you've visited my modest office!"));
				link.l1 = RandPhraseSimple(LinkRandPhrase("My pleasure! I have just was walking along the town and decided to visit you.","My pleasure, I am "+GetFullName(pchar)+", nice to meet you.",""+GetFullName(pchar)+" , captain of the ship named "+pchar.ship.name+" , glad to meet you. It's a bank, right?"), RandPhraseSimple("Nice to meet you. I am "+GetFullName(pchar)+". A captain of the ship named "+pchar.ship.name+". I've just wanted to get to know you.","Aha, so it's a bank here, right? Glad to meet you, I am "+GetFullName(pchar)+", a captain of my own vessel."));
				link.l1.go = "next";
				NPChar.quest.meeting = "1";
			}
			else
			{
				dialog.Text = pcharrepphrase(LinkRandPhrase(LinkRandPhrase("It's you! What do you want, "+GetAddress_Form(NPChar)+"?","What's your business, captain? I'm sorry but your reputation doesn't make you my very desired client.","Aha, another client! I thought at first that you were a robber... ha-ha I'm just joking."),LinkRandPhrase("Oh! What do you want? It's a bank not a tavern.","Good day to you, captain. I must inform you that I'm quite selective in choosing my clients.","What do you want, "+GetFullName(pchar)+"? I hope that you remember that your renown won't let you to raise a large loan?"),LinkRandPhrase("I hope that you want to invest money, "+GetAddress_Form(NPChar)+"? It won't be easy to raise a loan for you.","Captain "+GetFullName(pchar)+" what do you want from the modest banker? I'm sorry but I won't be able to arrange a loan for you. You can only to lend money on interest.","Come in, "+GetAddress_Form(NPChar)+". I am sorry to inform you that you are not the most welcome client but I don't usually reject people immediately.")),LinkRandPhrase(LinkRandPhrase("Hello, sir "+GetFullName(pchar)+"! I am always ready to help you in business matters.","Hello, sir "+GetAddress_Form(NPChar)+". I am always ready to raise a loan or accept any investment.","Dear "+GetFullName(pchar)+"! Glad to see you! What do you wish?"),LinkRandPhrase("Captain "+GetFullName(pchar)+"! I am always at your service. Want to raise a loan or invest money on interest?","Greeting for you captain! You are always a desired client here. You have got an excellent business renown!","Good day, "+GetFullName(pchar)+". I am glad that you've visited me again. Hope that you came for a profitable business?"),LinkRandPhrase("Good day to you, captain! What do you want? Want to raise a loan or make an investment?","Captain "+GetFullName(pchar)+"! Do you want to lend money with a profitable terms? I am always glad to see such a respectable client.","Glad to see you again, captain! I am always ready to help you to raise a loan or making an investment.")));
				link.l1 = pcharrepphrase(RandPhraseSimple(LinkRandPhrase("No kidding, banker, I've got a business here.","Too much talking, pal. Let's get straight to business.","Have you heard that money have no smell? So close your nose and let's get to our business."), LinkRandPhrase("And this is how you meet your clients? Lucky for you that I am in a good mood today.","Ha! Don't you glad too see me, huh? And I'm not a golden doubloon to make a positive impression on you. By the way, let's do business, usurer.","Eh, I'd like to teach you some respect but I have no time for this. Let's talk about money business.")),
				RandPhraseSimple(LinkRandPhrase("Glad to see my old friend!","It is always a pleasure to come here, pal. Let's go straight to business.","I am very glad too. Let's talk business, friend."),LinkRandPhrase("Really glad to meet you. What's new in the financial seas?","Glad that you still remember me. I hurry so let's get straight to business.","Hello, old friend! Glad to see you again!")));
				link.l1.go = "next";
			}
			break;
			
			case "next":
			dialog.text = NPCStringReactionRepeat("How can I help you?", 
				"What do you want this time?", 
				"Hm... what are your concerns?",
                "Eh, " + GetAddress_Form(npchar) + ", you can't even imaging how bothering clients could be..." , "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("No thanks, I'm just walking around and talking.", 
				"Me again. Just want to talk with you.",
                "Yup, it's me again. Nothing serious, just want to talk with you.", 
				"Yes, being a banker is not that easy sometimes. Just wanted to talk...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			link.l2 = "I want to discuss our financial matters.";
			link.l2.go = "LoanUsurer";//(на кредитный генератор)
			link.l3 = "I am interested in jewels and unusual idols.";
			if (!isMultiObjectKnown("gold_dublon"))
			{
				link.l3.go = "items_0";
			}
			else
			{
				link.l3.go = "items_1";
			}	
			link.l4 = "I need some information. Well, I have something to ask you about.";
			link.l4.go = "quests";//(перессылка в файл города)
//Jason, генер почтового курьера 2 уровня
			if (CheckAttribute(PChar, "questTemp.WPU.Postcureer.LevelUp"))
			{
				if (pchar.questTemp.WPU.Postcureer.TargetPortmanID == npchar.id)
				{
					link.l12 = "I brought you the business papers from "+XI_ConvertString("Colony"+pchar.questTemp.WPU.Postcureer.StartCity+"Gen")+".";
					link.l12.go = "Postcureer_LevelUp_ForAll";
				}
			}
			//квесты мэра, проникновение во враждебный город
  			if (CheckAttribute(pchar, "GenQuest.Intelligence") && pchar.GenQuest.Intelligence.SpyId == npchar.id && pchar.GenQuest.Intelligence == "") //квест мэра - на связь с нашим шпионом
			{
				link.l7 = RandPhraseSimple("I am here by the orders of one man. He is a governor " + GetFullName(characterFromId(pchar.GenQuest.Intelligence.MayorId)) + ".", 
					GetFullName(characterFromId(pchar.GenQuest.Intelligence.MayorId)) + " sent me here. I have to get something from you.");
				link.l7.go = "IntelligenceForAll";
			}
			if(CheckAttribute(pchar,"GenQuest.EncGirl") && pchar.GenQuest.EncGirl == "toLoverFather" && pchar.GenQuest.EncGirl.LoverFather == "usurer_keeper")
			{
				link.l9 = "Good day, I was invited by your son."; 
				link.l9.go = "EncGirl_4";
				pchar.quest.EncGirl_GetLoverFather.over = "yes";
			}	
			if (CheckCharacterItem(pchar, "CaptainBook") && !CheckAttribute(pchar, "questTemp.different.GiveShipLetters.speakUsurer"))
			{
				link.l10 = "I am interested to know who is the document's owner.";
				link.l10.go = "ShipLetters_Usurer1";			
			}
			
			//--> семейная реликвия
			if (CheckAttribute(pchar, "GenQuest.Noblelombard") && npchar.city == pchar.GenQuest.Noblelombard.City && !CheckAttribute(npchar, "quest.noblelombard"))
			{
				link.l11 = "I want to talk about your client's debt. His name is "+pchar.GenQuest.Noblelombard.Name+". He pawned his family relic. I represent his interests here and I have rights to discuss with you its return.";
				link.l11.go = "Noblelombard";			
			}
			if (CheckAttribute(pchar, "GenQuest.Noblelombard.Giveregard") && npchar.city == pchar.GenQuest.Noblelombard.City)
			{
				link.l11 = "We had a meeting three month ago and talked about one man's relic. His name was "+pchar.GenQuest.Noblelombard.Name+". Remember that? He had to open a deposit for my name. The sum is  "+FindRussianMoneyString(sti(pchar.GenQuest.Noblelombard.Regard))+"...";
				link.l11.go = "Noblelombard_5";			
			}
			//<-- семейная реликвия
			
			//-->работорговец
			if (pchar.questTemp.Slavetrader == "Seek_slaves" && pchar.questTemp.Slavetrader.UsurerId == npchar.id) 
			{
				link.l8 = "It is about your slave's assignment.";
				link.l8.go = "Checkslaves";
				break;
			}
			if(pchar.questTemp.Slavetrader == "goaway" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "Good day, " + NPChar.name + ", let's talk about your assignment.";
				link.l8.go = "Takeslaves_4_lose";
				break;
			}
			if(pchar.questTemp.Slavetrader == "goaway_pinas" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "Good day, " + NPChar.name + ", let's talk about your assignment.";
				link.l8.go = "Pinas_lose";
				break;
			}
			if(pchar.questTemp.Slavetrader == "died" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "Good day, " + NPChar.name + ", let's talk about your assignment.";
				link.l8.go = "Takeslaves_4_win";
				break;
			}
			if(pchar.questTemp.Slavetrader == "wait" && GetQuestPastDayParam("pchar.questTemp.Slavetrader_wait") > 20 && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "I came, as we agreed. Got a job for me?";
				link.l8.go = "Takeslaves_3";
				break;
			}
			if(pchar.questTemp.Slavetrader == "waitship" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "I came as I promised. How about a job?";
				link.l8.go = "Takeslaves_3";
				break;
			}
			if(pchar.questTemp.Slavetrader == "wait_1" && GetQuestPastDayParam("pchar.questTemp.Slavetrader_wait_1") > 30 && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "Good day, " + npchar.name + ". How are you doing? Got a new assignment for me?";
				link.l8.go = "EscapeSlave";
				break;
			}
			if(pchar.questTemp.Slavetrader == "escapeslave_win" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "Your mission is done. I was able to find those runaways. It wasn't that easy though.";
				link.l8.go = "Escape_slaves_win";
				break;
			}
			if(pchar.questTemp.Slavetrader == "wait_2" && GetQuestPastDayParam("pchar.questTemp.Slavetrader_wait_2") > 30 && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "Good day, " + npchar.name + ". I came for a new profitable assignment.";
				link.l8.go = "Slaveshore";
				break;
			}			
			
			if(pchar.questTemp.Slavetrader == "goodbye" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "Bad news," + npchar.name + ". I failed to get the brigantine.";
				link.l8.go = "Brig_lose";
				break;
			}
			if(pchar.questTemp.Slavetrader == "goodbye_1" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "Look,  " + npchar.name + ". I have chased the brigantine down, but I found no papers. Are you sure that they were there?";
				link.l8.go = "Letter_lose";
				break;
			}
			if(pchar.questTemp.Slavetrader == "winbrig" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "Good news," + npchar.name + ". I was able to hunt down that brigantine and find the papers. Here they are.";
				link.l8.go = "Brig_win";
				break;
			}
			if(pchar.questTemp.Slavetrader == "wait_3" && GetQuestPastDayParam("pchar.questTemp.Slavetrader_wait_3") > 30 && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "Good day, " + npchar.name + ". Have you prepared a new assignment for me?";
				link.l8.go = "SlaveGalleon";
				break;
			}
			if(pchar.questTemp.Slavetrader == "wingalleon" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "" + npchar.name + ", I was able to intercourse that so called 'galleon'.";
				link.l8.go = "Wingalleon";
				break;
			}
			if(pchar.questTemp.Slavetrader == "lostgalleon" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "" + npchar.name + ", I am so sorry but I couldn't board this galleon.";
				link.l8.go = "Lostgalleon";
				break;
			}
			if(pchar.questTemp.Slavetrader == "wait_4" && GetQuestPastDayParam("pchar.questTemp.Slavetrader_wait_4") > 4 && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "Good day, " + npchar.name + ". I came for my money.";
				link.l8.go = "FindRat";
				break;
			}
			if(pchar.questTemp.Slavetrader == "wincorvette" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "" + npchar.name + ", your mission is complete. That bastard Gontier is dead and so is his crew.";
				link.l8.go = "Wincorvette";
				break;
			}
			if(pchar.questTemp.Slavetrader == "lostcorvette" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "" + npchar.name + ", I am sorry but I failed to catch Francois Gontier, although I was following him to Tortuga. He managed to escape on his corvette from me.";
				link.l8.go = "lostcorvette";
				break;
			}
			if(pchar.questTemp.Slavetrader == "wait_5" && GetQuestPastDayParam("pchar.questTemp.Slavetrader_wait_5") > 30 && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "Good day," + npchar.name + ". Tell me about that new mission you've prepared for me.";
				link.l8.go = "Havana_fort";
				break;
			}
			//<--работорговец
			NextDiag.TempNode = "First time";
		break;

		case "items_0":
			dialog.text = "Want to buy some golden doubloons or chests for them? Trust me, it is a very valuable investment.";
			link.l1 = "Yes, that's very interesting.";
			link.l1.go = "items";
			AddQuestRecordInfo("Recipe", "Gold_dublon");
			SetAlchemyRecipeKnown("gold_dublon");
			SetAlchemyRecipeKnown("Chest");
			npchar.quest.meeting = "1"; 			
		break;
		
		case "items_1":
			dialog.text = "Do you want to trade for pesos or doubloons?";
			link.l1 = "For pesos.";
			link.l1.go = "items";
			link.l2 = "For doubloons.";
			link.l2.go = "items_dub";
		break;
		
		case "items":
			if (npchar.quest.item_date != lastspeak_date)
			{
				GiveItemToTrader(npchar);
				npchar.quest.item_date = lastspeak_date;
			}
			Nextdiag.CurrentNode = Nextdiag.TempNode;
			DialogExit();
			LaunchItemsTrade(NPChar, 0);
		break;
		
		case "items_dub":
			if (npchar.quest.item_date != lastspeak_date)
			{
				GiveItemToTrader(npchar);
				npchar.quest.item_date = lastspeak_date;
			}
			Nextdiag.CurrentNode = Nextdiag.TempNode;
			DialogExit();
			LaunchItemsTrade(NPChar, 1);
		break;
		
		//<<<<----------генератор -"Shipping documents". ------		
		case "ShipLetters_Usurer1":
			pchar.questTemp.different.GiveShipLetters.speakUsurer = true;
			dialog.text = "It will take o lot of my time to read this papers and my time costs a lot.";
			link.l1 = "Perhaps, " + sti(pchar.questTemp.different.GiveShipLetters.price1) + " pesos will compensate your time?";
			link.l1.go = "ShipLetters_Usurer2";
			link.l2 = "As you wish. Farewell!";
			link.l2.go = "exit";
		break;
		
		case "ShipLetters_Usurer2":
			AddMoneyToCharacter(pchar, -sti(pchar.questTemp.different.GiveShipLetters.price1));
			pchar.questTemp.different.GiveShipLetters.speakUsurer_1 = true;
			if(sti(pchar.questTemp.different.GiveShipLetters.variant) == 0)
			{
				dialog.text = "Let me have a look! No, I've never seen this name before. Show them to our harbor master.";
				link.l1 = "I am sorry but we had a deal! You promised me to tell about this captain!";
				link.l1.go = "ShipLetters_Usurer2_1";
			}
			if(sti(pchar.questTemp.different.GiveShipLetters.variant) == 1)
			{
				s1 = "Well... I know the owner of this ship. He is not a very rich man, but he has quite a wealth.";
				dialog.text = s1 + " They say that he is a successful smuggler. Is that what you wanted to hear?";
				link.l1 = "It seems so...";
				link.l1.go = "ShipLetters_Usurer2_2";
			}
			if(sti(pchar.questTemp.different.GiveShipLetters.variant) == 2)
			{
				s1 = "Well... I am not sure that I can congratulate you for your found.";
				dialog.text = s1 + "This documents are signed for our colonial patrol ship and its captain is known for his strong principals.";
				link.l1 = "A patrol? Under the commandant's command?";
				link.l1.go = "ShipLetters_Usurer2_3";
			}
		break;
		
		case "ShipLetters_Usurer2_1":
			dialog.text = "I promised you to take a look on those papers and nothing more. You can go.";
			link.l1 = "Thanks... I guess.";
			link.l1.go = "exit";
		break;
		
		case "ShipLetters_Usurer2_2":
			dialog.text = "It's your call. Our commandant has been showing quite an 'interest' to one person for a long time. Got any ideas already? And here we have bills of lading with no marks on them...";
			link.l1 = "I see. My gratitude!";
			link.l1.go = "exit";		
		break;
		
		case "ShipLetters_Usurer2_3":
			s1 = "Exactly. Our smugglers are bearing a grudge against this captain by the way.";
			dialog.text = s1 + "And as I mentioned before, paper's owner is a man of principals and don't really like local crimes.";
			link.l1 = "I see. My gratitude!";
			link.l1.go = "exit";		
		break;

		case "EncGirl_4":
			if(sti(pchar.GenQuest.EncGirl.LoverFatherAngry) == 0)
			{
				dialog.text = "Ah, I take it that you are a captain who brought my prodigal son with his young bride?";
				link.l1 = "Yes, it was me who helped them to escape.";
				link.l1.go = "EncGirl_5";
			}
			else
			{
				dialog.text = "Ah, here you are, my benefactor. Waiting for a reward I suppose?";
				link.l1 = "Your thanks would be fine at least...";
				link.l1.go = "EncGirl_6";			
			}
		break;
		
		case "EncGirl_5":
			dialog.text = "I am really grateful for helping my kid and not leaving him in that troublefull situation. Please, allow me to thank you as I can. Accept this modest sum and a gift from me.";
			link.l1 = "My thanks. It was my pleasure to help this young couple.";
			link.l1.go = "EncGirl_5_1";
		break;
		
		case "EncGirl_6":
			dialog.text = "Thanks? For what? This blockhead was unemployed for the half of the year and he has found time to get himself a girl already! I ran my own business in his age. There is a marriageable governor's daughter and he brought this whore here, Lord, forgive me for saying it! And now he's looking for my blessing!";
			link.l1 = "I take it that you don't believe in feelings?";
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
			dialog.text = "Feelings? What kind of feelings? You are an adult man and you are talking about these feelings too? Such a shame on you to be a pander for youth. Took away the girl from her parents and broke my son's life. You won't get any thanks from me. Farewell.";
			link.l1 = "Bye...";
			link.l1.go = "EncGirl_6_2";
		break;
		
		case "EncGirl_6_2":
			ChangeCharacterComplexReputation(pchar,"nobility", -1);
			AddQuestRecord("JungleGirl", "19");
			AddQuestUserData("JungleGirl", "sSex", GetSexPhrase("saw","saw"));
			AddQuestUserData("JungleGirl", "sSex1", GetSexPhrase("",""));
			CloseQuestHeader("JungleGirl");
			DeleteAttribute(pchar, "GenQuest.EncGirl");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();		
		break;
		
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////		Кредитный генератор Loan
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		case "LoanUsurer": 
			dialog.text = "Let's discuss it. I'm listening.";
		//	link.l1 = "Do you have any assignment for me?";
		//	link.l1.go = "Loan_GiveWork"; //patch
			//найти должника
			if (CheckAttribute(pchar, "GenQuest.Loan.FindCitizen") && pchar.GenQuest.Loan.FindCitizenNpcharId == NPChar.id)
            {
                link.l2 = "About that debtor...";
                link.l2.go = "FindCitizen_1";
            }
			//доставить сундук
            if (CheckAttribute(pchar, "GenQuest.LoanChest.TakeChest") && pchar.GenQuest.LoanChest.ChestNpcharId == NPChar.id)
            {
                link.l3 = "About that credit's delivery...";
                link.l3.go = "TakeChest_1";
            }
            if (CheckAttribute(pchar, "GenQuest.LoanChest.TakeChest") && sti(pchar.GenQuest.LoanChest.TargetIdx) == sti(NPChar.index))
            {
                link.l4 = "I brought your credit.";
                link.l4.go = "TakeChest_2";
            }
			//кредиты
            if(CheckAttribute(Pchar, "Quest.Loans." + (NPC_Area)) && makeint(Pchar.Quest.Loans.(NPC_Area)) == true)
			{
				iPastMonths = GetPastTime("Month", makeint(Pchar.Quest.Loans.(NPC_Area).StartYear),makeint(Pchar.Quest.Loans.(NPC_Area).StartMonth),makeint(Pchar.Quest.Loans.(NPC_Area).StartDay), makefloat(Pchar.Quest.Loans.(NPC_Area).StartTime), getDataYear(),getDataMonth(),GetDataDay(), GetTime());
				Pchar.Quest.Loans.(NPC_Area).Result = makeint(Pchar.Quest.Loans.(NPC_Area).Sum) + ((makeint(Pchar.Quest.Loans.(NPC_Area).Sum)/100)*makeint(Pchar.Quest.Loans.(NPC_Area).Interest))*(iPastMonths+1);// boal 23.01.2004
				if(makeint(PChar.money) >= makeint(Pchar.Quest.Loans.(NPC_Area).Result))
				{
					Link.l5 = "I owe you "+ FindRussianMoneyString(sti(Pchar.Quest.Loans.(NPC_Area).Result)) + LinkRandPhrase(", I am ready to return your money", ". I want to repay the debt.", ".  At last, it's time to pay off.");
					Link.l5.go = "loan_return";	
					sTemp = "credit";
				}					
			}
			else
			{
				Link.l6 = LinkRandPhrase("I want to borrow some coins.", "I really need to get some pesos.", "How about a small lend?");
				Link.l6.go = "loan";					
				if(makeint(Pchar.money) >= 100)
				{
					Link.l7 = LinkRandPhrase("I would like to deposit my money for interest.","Would you accept to keep a few sacks of silver?", "May I leave you some silver for an unlucky day?"); // patch
					Link.l7.go = "deposit";				
				}			
				if(CheckUseDublons(NPChar))
				{
					Link.l8 = "Want to deposit doubloons for interest";
					Link.l8.go = "deposit_dub";				
				}
			}
			
			if(CheckAttribute(Pchar, "Quest.Deposits." + (sDepositType1)) && makeint(Pchar.Quest.Deposits.(sDepositType1)) == true)
			{
				iPastMonths = GetPastTime("Month", makeint(Pchar.Quest.Deposits.(sDepositType1).StartYear),makeint(Pchar.Quest.Deposits.(sDepositType1).StartMonth),makeint(Pchar.Quest.Deposits.(sDepositType1).StartDay), makefloat(Pchar.Quest.Deposits.(sDepositType1).StartTime), getDataYear(),getDataMonth(),GetDataDay(), GetTime());
				if(CheckAttribute(Pchar, "Quest.Deposits." + (sDepositType1)+ ".Rem"))
				{
					Pchar.Quest.Deposits.(sDepositType1).Result = makeint(Pchar.Quest.Deposits.(sDepositType1).Sum) + ((makeint(Pchar.Quest.Deposits.(sDepositType1).Sum)/100)*makeint(Pchar.Quest.Deposits.(sDepositType1).Interest))*iPastMonths+sti(Pchar.Quest.Deposits.(sDepositType1).Rem);
				}
				else
				{
					Pchar.Quest.Deposits.(sDepositType1).Result = makeint(Pchar.Quest.Deposits.(sDepositType1).Sum) + ((makeint(Pchar.Quest.Deposits.(sDepositType1).Sum)/100)*makeint(Pchar.Quest.Deposits.(sDepositType1).Interest))*iPastMonths;
				}
				Link.l9 = LinkRandPhrase("I'm here to get my investment back in pesos.", "It's time to get back my silver you own.", "I need back my investment in pesos with all of interest.");
				Link.l9.go = "Deposit_return";									
			}
			
			if(CheckAttribute(Pchar, "Quest.Deposits." + (sDepositType2)) && makeint(Pchar.Quest.Deposits.(sDepositType2)) == true)
			{
				iPastMonths = GetPastTime("Month", makeint(Pchar.Quest.Deposits.(sDepositType2).StartYear),makeint(Pchar.Quest.Deposits.(sDepositType2).StartMonth),makeint(Pchar.Quest.Deposits.(sDepositType2).StartDay), makefloat(Pchar.Quest.Deposits.(sDepositType2).StartTime), getDataYear(),getDataMonth(),GetDataDay(), GetTime());
				if(CheckAttribute(Pchar, "Quest.Deposits." + (sDepositType2)+ ".Rem"))
				{
					Pchar.Quest.Deposits.(sDepositType2).Result = makeint(Pchar.Quest.Deposits.(sDepositType2).Sum) + ((makeint(Pchar.Quest.Deposits.(sDepositType2).Sum)/100)*makeint(Pchar.Quest.Deposits.(sDepositType2).Interest))*iPastMonths+sti(Pchar.Quest.Deposits.(sDepositType2).Rem);
				}
				else
				{
					Pchar.Quest.Deposits.(sDepositType2).Result = makeint(Pchar.Quest.Deposits.(sDepositType2).Sum) + ((makeint(Pchar.Quest.Deposits.(sDepositType2).Sum)/100)*makeint(Pchar.Quest.Deposits.(sDepositType2).Interest))*iPastMonths;
				}
				Link.l10 = LinkRandPhrase("I want to take back my investment in doubloons.", "It's time to get back my gold you own.", "I need back my investment in doubloons with all of interest.");
				Link.l10.go = "Deposit_return_dub";									
			}
/*			
			
*/			
			//выход
			if (sTemp == "credit")
			{
				link.l11 = LinkRandPhrase("I remember of my debt, yet I am not ready to pay up...");
				link.l11.go = "Loan_Remind";
			}
			else
			{
				link.l11 = "My mistake, I don't have any financial matters with you. Farewell.";
				link.l11.go = "exit";
			}
		break;
		//даем или не даем работу - сундуки и должники
		case "Loan_GiveWork": 
            if (isBadReputation(pchar, 42))
            {
                dialog.text = RandSwear() + "Your name is " + GetFullName(pchar)+ ", right? You have " +
                              RandPhraseSimple("a bad reputation ","a bad reputation ") + "and I don't want to have any business with you.";
				link.l1 = RandPhraseSimple("Too bad... Can't a man make a mistake?", RandSwear() + "Don't even start!");
				link.l1.go = "exit";
                break;
            }
			if (GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) < 26)//при низком авторитете не даем
			{
				dialog.text = "No, thanks, I'm fine.";
				link.l9 = "Sorry, I have to go.";
				link.l9.go = "exit";
				break;
			}
            dialog.text = "No, thanks, I'm fine.";

			if (npchar.quest.trade_date != lastspeak_date || bBettaTestMode)
			{
                npchar.quest.trade_date = lastspeak_date;
                iNum = rand(1);
                if (sti(Pchar.Ship.Type) == SHIP_NOTUSED)
                {
                    iNum = 0; // всегда первый
                }
                switch (iNum)
                {
                    case 0 : // найти должника
                        if (CheckAttribute(pchar, "GenQuest.Loan.FindCitizen")) break;
                        
                        if (sti(Pchar.Ship.Type) == SHIP_NOTUSED && sti(npchar.quest.FindCitizenNoShip) < 2)
                        {
                            iNum = findCitizenMan(Npchar, true);
                            npchar.quest.FindCitizenNoShip = sti(npchar.quest.FindCitizenNoShip) + 1; // значит на суше без корабля
                        }
                        else
                        {
                            iNum = findCitizenMan(Npchar, false);
                        }
                        if (iNum > 0)
                        {
                            chr = &Characters[iNum];
                            pchar.GenQuest.Loan.FindCitizenMoney   = (7 + cRand(sti(PChar.rank)))*1000 * GetCharacterSPECIALSimple(PChar, SPECIAL_L) + cRand(20)*200 * GetCharacterSPECIALSimple(PChar, SPECIAL_L);
                            pchar.GenQuest.Loan.FindCitizenPercent = makeint(sti(pchar.GenQuest.Loan.FindCitizenMoney) / (3+rand(2)));
                            pchar.GenQuest.Loan.FindCitizenIdx  =  iNum;
							pchar.GenQuest.Loan.FindCitizenChance1 = rand(2);
							pchar.GenQuest.Loan.FindCitizenChance2 = rand(1);
							pchar.GenQuest.Loan.FindCitizenChance3 = rand(1);
							sTemp = "";
							if (npchar.city != chr.city)
							{
								sTemp = " on" + XI_ConvertString(GetIslandByCityName(chr.city)+"Dat");
							}
                            dialog.text = "You are just in time. I have a delicate matter to do."+
                                     GetFullName(chr) + " lives in " + XI_ConvertString("Colony"+chr.city+"Dat") + sTemp + " and owes me " + FindRussianMoneyString(sti(pchar.GenQuest.Loan.FindCitizenMoney)) +
                                     ". If you get me back the whole sum I'll let you to take all of the interest." + FindRussianMoneyString(sti(pchar.GenQuest.Loan.FindCitizenPercent)) + ".";
                            link.l1 = "I am on it!";
                			link.l1.go = "LoanUsurer_GiveWork_1";
            			}
                    break;

                    case 1: // доставить сундуки
                        if (CheckAttribute(pchar, "GenQuest.LoanChest.TakeChest")) break;
                        
                        iNum = findChestMan(Npchar);
                        if (iNum > 0)
                        {
                            chr = &Characters[iNum];
                            pchar.GenQuest.LoanChest.Chest      = 2 + drand(2);
                            pchar.GenQuest.LoanChest.Money      = (3 + cRand(sti(pchar.GenQuest.LoanChest.Chest)))*400 * GetCharacterSPECIALSimple(PChar, SPECIAL_L) + cRand(20)*250;
                            pchar.GenQuest.LoanChest.TargetIdx  =  iNum;
                            pchar.GenQuest.LoanChest.Time       = 20 + rand(15);
							sTemp = "";
							if (npchar.city != chr.city)
							{
								sTemp = " on" + XI_ConvertString(GetIslandByCityName(chr.city)+"Dat");
							}
                            dialog.text = "I need a trusted man for one mission. Need to deliver a credit - " + pchar.GenQuest.LoanChest.Chest + 
									" chests with gold to "+ XI_ConvertString("Colony"+chr.city+"Acc") + sTemp + " for a man named " +
									GetFullName(chr) + ". He is a local " + GetWorkTypeOfMan(chr, "") +
									". Your reward is" + FindRussianMoneyString(sti(pchar.GenQuest.LoanChest.Money)) + "This is have to be done for " + FindRussianDaysString(sti(pchar.GenQuest.LoanChest.Time)) + ".";
                            link.l1 = "I am ready!";
                			link.l1.go = "LoanUsurer_ChestWork_1";
            			}
                     break;
    			}
    		}
            else
            {
                dialog.text = "I've told you everything.";
            }
            link.l9 = "Excuse me, I have to go.";
		    link.l9.go = "exit";
		break;
		//============== boal нахождение должника ===============
		case "LoanUsurer_GiveWork_1":
            pchar.GenQuest.Loan.FindCitizen = true;
            pchar.GenQuest.Loan.FindCitizenNpcharId = Npchar.id;
            dialog.text = "Splendid! Looking forward to see you again!";
			link.l9 = "I won't let you down.";
			link.l9.go = "exit";			
            chr = &Characters[sti(pchar.GenQuest.Loan.FindCitizenIdx)];     
			sTemp = "";
			if (npchar.city != chr.city)
			{
				sTemp = " on" + XI_ConvertString(GetIslandByCityName(chr.city)+"Dat");
			}
			ReOpenQuestHeader("Gen_LoanFindCitizen");
            AddQuestRecord("Gen_LoanFindCitizen", "1");
            AddQuestUserData("Gen_LoanFindCitizen", "sName", GetFullName(chr));
            AddQuestUserData("Gen_LoanFindCitizen", "sCity", XI_ConvertString("Colony"+chr.city+"Dat") + sTemp);
			AddQuestUserData("Gen_LoanFindCitizen", "sFromCity", XI_ConvertString("Colony"+Npchar.city+"Gen"));
			AddQuestUserData("Gen_LoanFindCitizen", "sMoney", FindRussianMoneyString(sti(pchar.GenQuest.Loan.FindCitizenMoney)));
			AddQuestUserData("Gen_LoanFindCitizen", "sMyMoney", FindRussianMoneyString(sti(pchar.GenQuest.Loan.FindCitizenPercent)));
		break;

		case "FindCitizen_1": //проверка выполнения квеста
            dialog.text = "I am listening.";
            if (CheckAttribute(pchar, "GenQuest.Loan.FindCitizenDone"))
            {
                link.l1 = "Your mission is done!";
                link.l1.go = "finish_work";
                link.l2.go = "finish_work_lie";
            }

            if (CheckAttribute(pchar, "GenQuest.Loan.FindCitizenFalied"))
            {
                link.l1 = "I've found your debtor but I couldn't get money from him.";
                link.l1.go = "finish_work_bad";
            }
            link.l3 = "I have decided to cancel your order of debt collecting, it is not for me.";
            link.l3.go = "finish_work_cancel";
            
		break; 

		case "finish_work":
            if (sti(pchar.Money) >= sti(pchar.GenQuest.Loan.FindCitizenMoney))
            {
                dialog.text = "Splendid!";
    			link.l9 = "You are welcome!";
    			link.l9.go = "exit";
    			AddMoneyToCharacter(Pchar, -1*sti(pchar.GenQuest.Loan.FindCitizenMoney));
    			DeleteAttribute(pchar, "GenQuest.Loan");
    			DeleteAttribute(Pchar, "quest.LoanFindCitizenTimer");
    			AddCharacterExpToSkill(Pchar, "Commerce", makeint(Pchar.rank) * 3);
    			AddCharacterExpToSkill(Pchar, "Leadership", makeint(Pchar.rank) * 6);
    			ChangeCharacterComplexReputation(pchar,"nobility", 1);
    			OfficersReaction("good");    			
    			AddQuestRecord("Gen_LoanFindCitizen", "4");
                CloseQuestHeader("Gen_LoanFindCitizen");
			}
			else
			{
			    dialog.text = "Excellent! But what about my money? The clock is ticking.";
    			link.l9 = "I'll bring it soon!";
    			link.l9.go = "exit";
    		}
		break;
		
		case "finish_work_bad":
            dialog.text = "To bad! You are unable to do your job!";
			link.l9 = "This man was really insolvent but you are right it wasn't my kind of job.";
			link.l9.go = "exit";
			DeleteAttribute(pchar, "GenQuest.Loan");
			DeleteAttribute(Pchar, "quest.LoanFindCitizenTimer");
			ChangeCharacterComplexReputation(pchar,"nobility", -1);
			AddQuestRecord("Gen_LoanFindCitizen", "5");
			AddQuestUserData("Gen_LoanFindCitizen", "sSex", GetSexPhrase(" tried"," tried"));
            CloseQuestHeader("Gen_LoanFindCitizen");
		break;
		
		case "finish_work_cancel":
            if (CheckAttribute(pchar, "GenQuest.Loan.FindCitizenDone") || CheckAttribute(pchar, "GenQuest.Loan.FindCitizenFalied"))
            {
                dialog.text = "And I suspect that you are cheating on me! I know that you have a talk with him. Give my money back!";
                link.l1 = "Yes, you are right. Here, take it.";
    			link.l1.go = "finish_work";
    			link.l2 = "But he refused to pay!";
    			if (CheckAttribute(pchar, "GenQuest.Loan.FindCitizenFalied"))
                {
    			   link.l2.go = "finish_work_bad";
    			}
    			else
    			{
    			   link.l2.go = "finish_work_bad_2";
    			}
    			
			}
            else
            {
                ChangeCharacterComplexReputation(pchar,"nobility", -1);
                dialog.text = "Too bad, I was counting on you.";
                link.l1 = "You are right, but this is life.";
    			link.l1.go = "exit";
    			DeleteAttribute(pchar, "GenQuest.Loan");
    			DeleteAttribute(Pchar, "quest.LoanFindCitizenTimer");
    			AddQuestRecord("Gen_LoanFindCitizen", "6");
				AddQuestUserData("Gen_LoanFindCitizen", "sSex", GetSexPhrase("tried","tried"));
                CloseQuestHeader("Gen_LoanFindCitizen");
            }
		break;
		
		case "finish_work_bad_2":
			ChangeCharacterComplexReputation(pchar,"nobility", -3);
            dialog.text = "You've already shown me that you were a cheating type. Return me my money!";
			link.l1 = "I've already said that I didn't have it.";
    		link.l1.go = "finish_work_hanter";
			if (sti(pchar.Money) >= sti(pchar.GenQuest.Loan.FindCitizenMoney))
			{
				link.l2 = "You are right. Here, take it.";
				link.l2.go = "finish_work";
			}
		break;
		
		case "finish_work_lie":
            dialog.text = "Really?";
            link.l1 = "Sure!";
    		link.l1.go = "finish_work_cancel";
		break;

		case "finish_work_hanter":
            dialog.text = "Oh, you are serious, aren't you? And do you really think that I'll let it go just like that? I promise that you'll have troubles which will cost you much more than that money. Get away from here!";
            link.l1 = "Don't try to scare me. Have a nice day!";
    		link.l1.go = "exit";
			ChangeCharacterHunterScore(pchar, NationShortName(sti(npchar.Nation)) + "hunter", 40);
			DeleteAttribute(pchar, "GenQuest.Loan");
    		DeleteAttribute(Pchar, "quest.LoanFindCitizenTimer");
    		AddQuestRecord("Gen_LoanFindCitizen", "7");
            CloseQuestHeader("Gen_LoanFindCitizen");
		break;

		//============== boal доставка сундуков ===============
		case "LoanUsurer_ChestWork_1": 
            pchar.GenQuest.LoanChest.TakeChest = true;
            pchar.GenQuest.LoanChest.ChestNpcharId = Npchar.id;
            dialog.text = "I really count on you.";
			link.l9 = "I won't let you down.";
			link.l9.go = "exit";
			TakeNItems(pchar, "Chest", sti(pchar.GenQuest.LoanChest.Chest));
			SetTimerCondition("LoanChestTimer", 0, 0, sti(pchar.GenQuest.LoanChest.Time), false);
			// немного веселой жизни
            TraderHunterOnMap();
            chr  = &Characters[sti(pchar.GenQuest.LoanChest.TargetIdx)];
			sTemp = "";
			if (npchar.city != chr.city)
			{
				sTemp = " on" + XI_ConvertString(GetIslandByCityName(chr.city)+"Dat");
			}
			ReOpenQuestHeader("Gen_LoanTakeChest");
            AddQuestRecord("Gen_LoanTakeChest", "1");
            AddQuestUserData("Gen_LoanTakeChest", "sFromCity", XI_ConvertString("Colony"+Npchar.city+"Gen"));
			AddQuestUserData("Gen_LoanTakeChest", "sQty", pchar.GenQuest.LoanChest.Chest);
			AddQuestUserData("Gen_LoanTakeChest", "sCity", XI_ConvertString("Colony"+chr.city+"Acc") + sTemp);
			AddQuestUserData("Gen_LoanTakeChest", "sName", GetFullName(chr));
			AddQuestUserData("Gen_LoanTakeChest", "sType", GetWorkTypeOfMan(chr, ""));
			AddQuestUserData("Gen_LoanTakeChest", "sMoney", FindRussianMoneyString(sti(pchar.GenQuest.LoanChest.Money)));
			AddQuestUserData("Gen_LoanTakeChest", "sDay", FindRussianDaysString(sti(pchar.GenQuest.LoanChest.Time)));
		break;

		case "TakeChest_1":
            dialog.text = "I am listening.";
            link.l1 = "I have decided to cancel your order of credit delivering, it is not for me.";
            link.l1.go = "TakeChestFinish_work_cancel";
            link.l9 = "No, it's nothing.";
			link.l9.go = "exit";
		break;

		case "TakeChestFinish_work_cancel":
            if (GetCharacterItem(pchar, "Chest") >= sti(pchar.GenQuest.LoanChest.Chest))
            {
                ChangeCharacterComplexReputation(pchar,"nobility", -1);
                dialog.text = "Too bad I was counting on you.";
                link.l1 = "You are right, but this is life.";
    			link.l1.go = "exit";
    			TakeNItems(pchar, "Chest", -sti(pchar.GenQuest.LoanChest.Chest));
    			DeleteAttribute(pchar, "GenQuest.LoanChest");
    			DeleteAttribute(Pchar, "quest.LoanChestTimer");
                AddQuestRecord("Gen_LoanTakeChest", "5");
				AddQuestUserData("Gen_LoanTakeChest", "sSex", GetSexPhrase("tried","tried"));
                CloseQuestHeader("Gen_LoanTakeChest");
			}
			else
			{
                dialog.text = "Perhaps, I could abort your mission but only if you'd RETURN me all of my chests.";
                link.l1 = "See you later.";
    			link.l1.go = "Exit";
			}
		break;
		//============== кредиты ===============
		case "loan":
            if (sti(NPChar.nation) == PIRATE)
            {
                dialog.text = "No, I can't help you. I can only accept investments in this troublefull place. You can invest silver pesos or golden doubloons.";				
                if(makeint(Pchar.money) >= 100)
				{
	                Link.l1 = "I want to invest pesos and let's talk about the sum.";
	                Link.l1.go = "deposit";
				}				
				if(CheckUseDublons(NPChar))
				{
					Link.l2 = "I want to invest doubloons. Let's clarify the sum.";
					Link.l2.go = "deposit_dub";
				}
                Link.l3 = "Not interested.";
				link.l3.go = "exit";
                break;
            }
			// проверка на проф пригодность -->
            if (isBadReputation(pchar, 42))
            {
                dialog.text = RandSwear() + "Your name is " + GetFullName(pchar)+ ", right? You have " +
                              RandPhraseSimple("a bad reputation ","a bad reputation ") + " and I don't want to do business with you.";
				link.l1 = RandPhraseSimple("Can't a man make a mistake?", RandSwear() + "Whatever!");
				link.l1.go = "exit";
                break;
            }
            // проверка на проф пригодность <--
			Dialog.snd = "voice\USDI\USDI016";
			dialog.text = "Oh, you are always welcome. What sum do you need?";
			Link.l1 = "A small one.";
			Link.l1.go = "Small";
			Link.l2 = "Moderate.";
			Link.l2.go = "Medium";
			Link.l3 = "As big as possible.";
			Link.l3.go = "Large";
		break;

		case "small":
			Pchar.Quest.Loans.(NPC_Area).Sum = 500*makeint(Pchar.rank);
			Dialog.snd = "voice\USDI\USDI017";
			dialog.text = "Excellent! It's always much easier to deal with small sums - less risk. I can offer you " + FindRussianMoneyString(sti(Pchar.Quest.loans.(NPC_Area).sum)) + "...";
			Link.l1 = "Deal. What about your interest?";
			Link.l1.go = "Interest";
			Link.l2 = "It won't work for me. Let's change it.";
			Link.l2.go = "Loan";
			Link.l3 = "I suppose that it's better not to run into debt for me. Farewell.";
			Link.l3.go = "ExitDelLoan1";
			Pchar.Quest.Loans.(NPC_Area).Interest = 22 - makeint((GetSummonSkillFromName(pchar, "Commerce")+GetSummonSkillFromName(pchar, "Leadership"))/10);
		break;

		case "Medium":
			Pchar.Quest.Loans.(NPC_Area).Sum = 1500*makeint(Pchar.rank);
			Dialog.snd = "voice\USDI\USDI018";
			dialog.text = "No problem. I hope that " + FindRussianMoneyString(sti(Pchar.Quest.Loans.(NPC_Area).sum)) + " will help you to solve your problems. This is quite a substantial sum.";
			Link.l1 = "Deal. What about your interest?";
			Link.l1.go = "Interest";
			Link.l2 = "It won't work for me. Let's change it.";
			Link.l2.go = "Loan";
			Link.l3 = "I suppose that it's better not to run into debt for me. Farewell.";
			Link.l3.go = "ExitDelLoan1";
			Pchar.Quest.Loans.(NPC_Area).Interest = 27 - makeint((GetSummonSkillFromName(pchar, "Commerce")+GetSummonSkillFromName(pchar, "Leadership"))/10);
		break;

		case "Large":
			Pchar.Quest.Loans.(NPC_Area).Sum = 4000*makeint(Pchar.rank);
			Dialog.snd = "voice\USDI\USDI019";
			dialog.text = "Well... it's risky. Fine, I am ready to raise a loan for you for " + FindRussianMoneyString(sti(Pchar.Quest.Loans.(NPC_Area).sum)) + ". I hope that you understand, captain, this is a really substantial sum. I ask you to be serious about it.";
			Link.l1 = "Deal. What about your interest?";
			Link.l1.go = "Interest";
			Link.l2 = "It won't work for me. Let's change it.";
			Link.l2.go = "Loan";
			Link.l3 = "I suppose that it's better not to run into debt for me. Farewell.";
			Link.l3.go = "ExitDelLoan1";
			Pchar.Quest.Loans.(NPC_Area).Interest = 37 - makeint((GetSummonSkillFromName(pchar, "Commerce")+GetSummonSkillFromName(pchar, "Leadership"))/10);
		break;

		case "Interest":
			//Pchar.Quest.Loans.(NPC_Area).Interest = 16 - makeint(Pchar.skill.commerce);
			Dialog.snd = "voice\USDI\USDI020";
			dialog.text = Pchar.Quest.Loans.(NPC_Area).Interest + "% per month. I can't offer you better terms based on what I know about you."; 
			Link.l1 = "Works for me. Let talk about time.";
			Link.l1.go = "Period";
			Link.l3 = "I suppose that it's better to don't run into debt for me. Farewell.";
			Link.l3.go = "ExitDelLoan1";
		break;

		case "Period":
			Pchar.Quest.Loans.(NPC_Area).Period = makeint(makeint(Pchar.reputation.nobility)/20) + 1;			
			Dialog.snd = "voice\USDI\USDI021";
			dialog.text =  "Taking into account my information about you, " + Pchar.name + ", I'll wait for return this loan for " + FindRussianMonthString(sti(Pchar.Quest.Loans.(NPC_Area).Period)) + ". After that I will take measures. Hope that you understand that."; 
			Link.l1 = "I gladly accept your terms... and your coins.";
			Link.l1.go = "LoanGranted";
			Link.l3 = "Excuse me, but it won't work for me. Farewell.";
			Link.l3.go = "ExitDelLoan1";
		break;

		case "LoanGranted":
			Dialog.snd = "voice\USDI\USDI022";
			dialog.text = "I am sincerely glad. But let me warn you. I have been doing this for a long time and I know how to return my investments. So if you ever had any silly ideas, I suggest you leave them be\nNo offence, only warning.";
			Link.l1 = "Hm.. Well. Farewell.";
			Link.l1.go = "LoanGranted_exit";
		break;

		case "Loan_Remind":
			Dialog.snd = "voice\USDI\USDI023";
			dialog.text = "It's your choice, captain. My interest in growing and you don't have that much time.";
			Link.l1 = "Don't worry. See you.";
			Link.l1.go = "exit";
		break;

		case "loan_return":
			addMoneyToCharacter(Pchar, -(makeint(Pchar.Quest.Loans.(NPC_Area).Result)));
			// boal 27.01.2004 -->
            if (npchar.quest.trade_date != lastspeak_date) // дыра с прокачкой была
            {
    			AddCharacterExpToSkill(Pchar, "Commerce", makeint(Pchar.Quest.Loans.(NPC_Area).Result) / 350);
    			AddCharacterExpToSkill(Pchar, "Leadership", makeint(Pchar.Quest.Loans.(NPC_Area).Result) / 700);
			}
			// boal 27.01.2004 <--
			DeleteAttribute(PChar, "quest.Loans_" + NPC_Area); // bug fix
			DeleteAttribute(PChar, "quest.Loans." + NPC_Area);
			Dialog.snd1 = "voice\USDI\USDI024";
			Dialog.snd2 = "voice\USDI\USDI025";
			Dialog.snd3 = "voice\USDI\USDI026";
			dialog.text = LinkRandPhrase("Wonderful! Come to me when you need coins. I will be at your service anytime.", "My gratitude. Is always a pleasure to deal with a man who is able to return his debt in time. Things happen sometimes, you know...",  "Oh, I was right trusting you, " + GetAddress_Form(NPChar) + "! I hope that it's not the last time you use my services.");
			Link.l1 = LinkRandPhrase("I wont to borrow some money.", "I really need to get some pesos.", "How about a small lend?");
			Link.l1.go = "loan";			
			if(makeint(PChar.money) >= 100)
			{
				Link.l2 = LinkRandPhrase("I'd like to invest my money.","Will you keep pirate booty?", "May I leave you some silver for an unlucky day?");
				Link.l2.go = "deposit";				
			}		
			if(CheckUseDublons(NPChar))	
			{
				Link.l3 = "Want to invest some doubloons for interest";
				Link.l3.go = "deposit_dub";				
			}
			Link.l4 = "Farewell, " + NPchar.name + ".";
			Link.l4.go = "ExitDelLoan1";
		break;

		case "deposit":
			dialog.text = LinkRandPhrase("I sea the wise man! What sum would you like to invest?", "Fine. Trust me, this sum will wait you here in safety and with all of interest.", "I see that you know what's really important in this life. How much would you like to invest?");
			link.l1.edit = 3;
			link.l1 = "";	
			Link.l1.go = "result";
		break;
		
		case "result":
			Pchar.QuestTemp.Deposits.(sDepositType1).Interest = makeint((GetSummonSkillFromName(pchar, "Commerce")+GetSummonSkillFromName(pchar, "Leadership"))/10.0/4.0 + 0.66) + 1; 
			Pchar.QuestTemp.Deposits.(sDepositType1).Sum = dialogEditStrings[3];
			iTemp = sti(dialogEditStrings[3]);
			if (iTemp <= 0)
			{
				dialog.text = "Joking, huh?";
				link.l1 = "My mistake.";
				link.l1.go = "exit";
				break;
			}
			if (iTemp > sti(pchar.money))
			{
				dialog.text = "Hm, unfortunately you don't have that much money. Let's be serious...";
				link.l1 = "Fine.";
				link.l1.go = "exit";
				break;
			}
			dialog.text = "Alright. I can offer you... well..." + Pchar.QuestTemp.Deposits.(sDepositType1).Interest + " %. Per month, of course.";
			Link.l1 = "It works for me.";
			Link.l1.go = "Deposit_placed";
			Link.l2 = "I'd better change the sum.";
			Link.l2.go = "Deposit";
			Link.l3 = "Looks like it was a bad idea... Farewell.";
			Link.l3.go = "Exit";
		break;

		case "Deposit_placed":
			Dialog.snd = "voice\USDI\USDI033";
			if ( !CheckAttribute(Pchar, "Quest.Deposits." + (sDepositType1)+".Result"))
			{
			    Pchar.Quest.Deposits.(sDepositType1).Result = 0;//fix
			}
			// boal limit
			if ( (sti(Pchar.Quest.Deposits.(sDepositType1).Result) + sti(Pchar.QuestTemp.Deposits.(sDepositType1).Sum)) > sti(NPChar.UsurerDeposit)*1000)
			{
			    dialog.text = "Pardon me, captain, but this sum is too huge for my provincial bank. I won't be able to pay you your interest. And the lack of a reliable guard... I hope that I'd understand. Anyways, the maximum sum I can accept from you is " +
						FindRussianMoneyString(MakeMoneyShow(sti(NPChar.UsurerDeposit)*1000, MONEY_SIGN,MONEY_DELIVER)) + ".";
				Link.l1 = "Too bad, I have to find an another banker then.";
				Link.l1.go = "Exit";
			}
			else
			{
				dialog.text = "You can be confident now that even the strongest storm wouldn't leave you without a coin.";
				Link.l1 = "Alright. See you.";
				Link.l1.go = "Deposit_Exit";
			}
		break;
		
		case "Deposit_return":
			Dialog.snd = "voice\USDI\USDI034";
			dialog.text = "Considering promised interest and passed time, I owe you " + FindRussianMoneyString(sti(Pchar.Quest.Deposits.(sDepositType1).Result)) + "... Are you sure that you want to take the money?";
			Link.l1 = "Absolutely. Give it to me.";			
			Link.l1.go = "Deposit_return_1";		
			Link.l2 = "I want to take a part of my money.";			
			Link.l2.go = "Deposit_return_part";
			Link.l3 = "You are right. I'll let it to stay with you for a while. Good day.";			
			Link.l3.go = "Exit";		
		break;		
		
		case "Deposit_exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			if(CheckAttribute(Pchar, "Quest.Deposits." + (sDepositType1)+ ".Rem"))
			{
				DeleteAttribute(Pchar,"Quest.Deposits." + (sDepositType1)+ ".Rem");
			}
			Pchar.Quest.Deposits.(sDepositType1).Interest = sti(Pchar.QuestTemp.Deposits.(sDepositType1).Interest);
			Pchar.Quest.Deposits.(sDepositType1).Sum      = sti(Pchar.QuestTemp.Deposits.(sDepositType1).Sum);
			Pchar.Quest.Deposits.(sDepositType1).city 	  = NPC_Area;	

			AddMoneyToCharacter(Pchar, -(makeint(Pchar.Quest.Deposits.(sDepositType1).Sum)));
			// общий долг
			Pchar.Quest.Deposits.(sDepositType1).Sum = sti(Pchar.Quest.Deposits.(sDepositType1).Result) + sti(Pchar.Quest.Deposits.(sDepositType1).Sum);
			Pchar.Quest.Deposits.(sDepositType1) = true;
			Pchar.Quest.Deposits.(sDepositType1).StartDay 	= getDataDay();
			Pchar.Quest.Deposits.(sDepositType1).StartMonth = getDataMonth();
			Pchar.Quest.Deposits.(sDepositType1).StartYear 	= getDataYear();
			Pchar.Quest.Deposits.(sDepositType1).StartTime 	= getTime();
			DialogExit();
		break;
		
		//--> Jason забор денег по частям
		case "Deposit_return_part":
			dialog.text = "And how much?";
			link.l1.edit = 4;
			link.l1 = "";	
			Link.l1.go = "result_part";
		break;

		case "result_part":
			iTemp = sti(dialogEditStrings[4]);
			if (iTemp <= 0)
			{
				dialog.text = "That was such a stupid joke, sir!";			
				link.l1 = "Damn! I am so sorry... Let's change the sum.";	
				Link.l1.go = "Deposit_return_part";
				break;
			}
			if (iTemp > sti(Pchar.Quest.Deposits.(sDepositType1).Result))
			{
				dialog.text = "You don't have that much money on your account.";			
				link.l1 = "Damn! My mistake. Let's change the sum.";	
				Link.l1.go = "Deposit_return_part";
				break;
			}
			if (iTemp == sti(Pchar.Quest.Deposits.(sDepositType1).Result))
			{
				dialog.text = "All of it? Fine, as you say. Here is your money.";			
				link.l1 = "Gratitude!";	
				Link.l1.go = "Deposit_return_all";
				break;
			}
			dialog.text = "Fine. Take it. Here is your money.";			
			link.l1 = "Thanks!";	
			Link.l1.go = "result_part_1";
		break;
		
		case "result_part_1":
			DialogExit();
			iTemp = sti(dialogEditStrings[4]);
			addMoneyToCharacter(Pchar, iTemp);
			iRes = sti(Pchar.Quest.Deposits.(sDepositType1).Result)-iTemp; //остаток на счете
			iPer = sti(Pchar.Quest.Deposits.(sDepositType1).Interest);
			iDep = sti(Pchar.Quest.Deposits.(sDepositType1).Sum); //стартовая сумма
			if (iRes <= sti(Pchar.Quest.Deposits.(sDepositType1).Sum)) // стало меньше начальной суммы
			{
				DeleteAttribute(Pchar, "quest.Deposits." + (sDepositType1));
				Pchar.Quest.Deposits.(sDepositType1).Interest = iPer;
				Pchar.Quest.Deposits.(sDepositType1).Sum = iRes;
				Pchar.Quest.Deposits.(sDepositType1).Result = 0;
			}
			else // если остаток больше начальной суммы - проценты продолжаем считать с нее, а не с остатка, ибо нефиг, дельту приплюсуем к набежавшим процентам - банкир Jason :) 
			{
				DeleteAttribute(Pchar, "quest.Deposits." + (sDepositType1));
				Pchar.Quest.Deposits.(sDepositType1).Interest = iPer;
				Pchar.Quest.Deposits.(sDepositType1).Sum = iDep;
				Pchar.Quest.Deposits.(sDepositType1).Rem = iRes-iDep;
			}
			Pchar.Quest.Deposits.(sDepositType1).city 	  	= NPC_Area;	
			Pchar.Quest.Deposits.(sDepositType1) 			= true;
			Pchar.Quest.Deposits.(sDepositType1).StartDay 	= getDataDay();
			Pchar.Quest.Deposits.(sDepositType1).StartMonth = getDataMonth();
			Pchar.Quest.Deposits.(sDepositType1).StartYear 	= getDataYear();
			Pchar.Quest.Deposits.(sDepositType1).StartTime 	= getTime();
		break;
		
		case "Deposit_return_all":
			DialogExit();
			iTemp = sti(dialogEditStrings[4]);
			addMoneyToCharacter(Pchar, iTemp);
			DeleteAttribute(Pchar, "quest.Deposits." + (sDepositType1));
		break;
		//<-- забор денег по частям		
		
		case "Deposit_return_1":
			addMoneyToCharacter(Pchar, makeint(Pchar.Quest.Deposits.(sDepositType1).Result));
			Dialog.snd = "voice\USDI\USDI035";
			dialog.text = "Oh... It is too hard to lose it. I have really got used to this money. Come again anyway.";			
			Link.l1 = "I will if I need. Farewell.";			
			Link.l1.go = "Exit";
			DeleteAttribute(Pchar, "quest.Deposits." + (sDepositType1));
		break;
		
		//  ugeen -> вклады в дублонах	
		case "deposit_dub":
			dialog.text = LinkRandPhrase("I see the wise man! What sum would you like to invest?", "Fine. Trust me, this sum will wait you here in safety and with all of your interest.", "I see that you know what's really important in this life. How much would like to invest?");
			link.l1.edit = 3;
			link.l1 = "";	
			Link.l1.go = "result_dub";
		break;
		
		case "result_dub":		
			iTotalDublonQty = GetCharacterItem(pchar,"gold_dublon") + CheckItemMyCabin("gold_dublon");		
			Pchar.QuestTemp.Deposits.(sDepositType2).Interest = makeint((GetSummonSkillFromName(pchar, "Commerce")+GetSummonSkillFromName(pchar, "Leadership"))/20.0/4.0 + 0.66) + 1; 
			Pchar.QuestTemp.Deposits.(sDepositType2).Sum = dialogEditStrings[3];
			iTemp = sti(dialogEditStrings[3]);
			if (iTemp <= 0)
			{
				dialog.text = "Joking, huh?";
				link.l1 = "Hm, my mistake...";
				link.l1.go = "exit";
				break;
			}						
			if (iTemp > iTotalDublonQty)
			{
				dialog.text = "Hm, unfortunately you don't have that much money. Let's be serious...";
				link.l1 = "Hm... good.";
				link.l1.go = "exit";
				break;
			}
			dialog.text = "Alright. I can offer you... well..." + Pchar.QuestTemp.Deposits.(sDepositType2).Interest + " %. Per month, of course.";
			Link.l1 = "Works for me.";
			Link.l1.go = "Deposit_placed_dub";
			Link.l2 = "I'd better change the sum.";
			Link.l2.go = "Deposit_dub";
			Link.l3 = "I suppose that it's better not to lose my gold. Farewell.";
			Link.l3.go = "Exit";
		break;
		
		case "Deposit_placed_dub":
			Dialog.snd = "voice\USDI\USDI033";
			if ( !CheckAttribute(Pchar, "Quest.Deposits." + (sDepositType2)+".Result"))
			{
			    Pchar.Quest.Deposits.(sDepositType2).Result = 0;//fix
			}
			// boal limit
			if ( (sti(Pchar.Quest.Deposits.(sDepositType2).Result) + sti(Pchar.QuestTemp.Deposits.(sDepositType2).Sum)) > sti(NPChar.UsurerDeposit)*10)
			{
			    dialog.text = "Pardon me, captain, but this sum is too huge for my provincial bank. I won't be able to pay you your interest. And the lack of a reliable guard... I hope that I'd understand. Anyways, the maximum sum I can accept from you is " +
						FindRussianDublonString(MakeMoneyShow(sti(NPChar.UsurerDeposit)*10, MONEY_SIGN,MONEY_DELIVER)) + ".";
				Link.l1 = "Too bad, I have to find an another banker then.";
				Link.l1.go = "Exit";
			}
			else
			{
				dialog.text = "You can be confident now that even the strongest storm wouldn't leave you without a coin.";
				Link.l1 = "Nice. Farewell.";
				Link.l1.go = "Deposit_Exit_dub";
			}
		break;
		
		case "Deposit_return_dub":
			Dialog.snd = "voice\USDI\USDI034";
			dialog.text = "Considering promised interest and passed time, I owe you " + FindRussianDublonString(sti(Pchar.Quest.Deposits.(sDepositType2).Result)) + "... Are you sure that you want to take the money";
			Link.l1 = "Absolutely. Give it to me.";			
			Link.l1.go = "Deposit_return_dub_1";		
			Link.l2 = "I want to take a part of my money.";			
			Link.l2.go = "Deposit_return_dub_part";
			Link.l3 = "You are right. I'll let it to stay with you for a while. Good day.";			
			Link.l3.go = "Exit";		
		break;	

		case "Deposit_exit_dub":
			NextDiag.CurrentNode = NextDiag.TempNode;		
			if(CheckAttribute(Pchar, "Quest.Deposits." + (sDepositType2)+ ".Rem"))
			{
				DeleteAttribute(Pchar,"Quest.Deposits." + (sDepositType2)+ ".Rem");
			}	
			Pchar.Quest.Deposits.(sDepositType2).Interest = sti(Pchar.QuestTemp.Deposits.(sDepositType2).Interest);
			Pchar.Quest.Deposits.(sDepositType2).Sum      = sti(Pchar.QuestTemp.Deposits.(sDepositType2).Sum);
			Pchar.Quest.Deposits.(sDepositType2).city 	  = NPC_Area;	
			
			iTemp = GetCharacterItem(pchar,"gold_dublon");
			if(iTemp > sti(Pchar.Quest.Deposits.(sDepositType2).Sum))
			{
				TakeNItems(pchar,"gold_dublon", -sti(Pchar.Quest.Deposits.(sDepositType2).Sum));
			}
			else
			{
				TakeNItems(pchar,"gold_dublon", -iTemp));
				iTemp = sti(Pchar.Quest.Deposits.(sDepositType2).Sum) - iTemp;
				GetItemMyCabin("gold_dublon", iTemp);
			}
						
			// общий долг
			Pchar.Quest.Deposits.(sDepositType2).Sum = sti(Pchar.Quest.Deposits.(sDepositType2).Result) + sti(Pchar.Quest.Deposits.(sDepositType2).Sum);
			Pchar.Quest.Deposits.(sDepositType2) = true;
			Pchar.Quest.Deposits.(sDepositType2).StartDay 	= getDataDay();
			Pchar.Quest.Deposits.(sDepositType2).StartMonth = getDataMonth();
			Pchar.Quest.Deposits.(sDepositType2).StartYear 	= getDataYear();
			Pchar.Quest.Deposits.(sDepositType2).StartTime 	= getTime();
			DialogExit();
		break;	
		
		//-->забор дублонов по частям
		case "Deposit_return_dub_part":
			dialog.text = "And how much?";
			link.l1.edit = 4;
			link.l1 = "";	
			Link.l1.go = "result_dub_part";
		break;
		
		case "result_dub_part":
			iTemp = sti(dialogEditStrings[4]);
			if (iTemp <= 0)
			{
				dialog.text = "Such a stupid joke, sir!";			
				link.l1 = "Damn! I am so sorry... Let's change the sum...";	
				Link.l1.go = "Deposit_return_dub_part";
				break;
			}			
			if (iTemp > sti(Pchar.Quest.Deposits.(sDepositType2).Result))
			{
				dialog.text = "You don't have that much gold on your account, sir.";			
				link.l1 = "Damn! My mistake. Let's change the sum...";	
				Link.l1.go = "Deposit_return_dub_part";
				break;
			}			
			if (iTemp == sti(Pchar.Quest.Deposits.(sDepositType2).Result))
			{
				dialog.text = "All of it? Fine, as you say. Here is your money.";			
				link.l1 = "Thanks!";	
				Link.l1.go = "Deposit_return_dub_all";
				break;
			}
			dialog.text = "Fine. Take it. Here is your money.";			
			link.l1 = "Gratitude!";	
			Link.l1.go = "result_dub_part_1";
		break;
		
		case "result_dub_part_1":
			DialogExit();
			iTemp = sti(dialogEditStrings[4]);
			TakeNItems(pchar,"gold_dublon", iTemp);
			iRes = sti(Pchar.Quest.Deposits.(sDepositType2).Result)-iTemp; //остаток на счете
			iPer = sti(Pchar.Quest.Deposits.(sDepositType2).Interest);
			iDep = sti(Pchar.Quest.Deposits.(sDepositType2).Sum); //стартовая сумма
			if (iRes <= sti(Pchar.Quest.Deposits.(sDepositType2).Sum)) // стало меньше начальной суммы
			{
				DeleteAttribute(Pchar, "quest.Deposits." + (sDepositType2));
				Pchar.Quest.Deposits.(sDepositType2).Interest = iPer;
				Pchar.Quest.Deposits.(sDepositType2).Sum = iRes;
				Pchar.Quest.Deposits.(sDepositType2).Result = 0;
			}
			else // если остаток больше начальной суммы - проценты продолжаем считать с нее, а не с остатка, ибо нефиг, дельту приплюсуем к набежавшим процентам - банкир Jason :) 
			{
				DeleteAttribute(Pchar, "quest.Deposits." + (sDepositType2));
				Pchar.Quest.Deposits.(sDepositType2).Interest = iPer;
				Pchar.Quest.Deposits.(sDepositType2).Sum = iDep;
				Pchar.Quest.Deposits.(sDepositType2).Rem = iRes-iDep;
			}
			Pchar.Quest.Deposits.(sDepositType2).city 	  	= NPC_Area;	
			Pchar.Quest.Deposits.(sDepositType2) 			= true;
			Pchar.Quest.Deposits.(sDepositType2).StartDay 	= getDataDay();
			Pchar.Quest.Deposits.(sDepositType2).StartMonth = getDataMonth();
			Pchar.Quest.Deposits.(sDepositType2).StartYear 	= getDataYear();
			Pchar.Quest.Deposits.(sDepositType2).StartTime 	= getTime();
		break;
		
		case "Deposit_return_dub_all":
			DialogExit();
			iTemp = sti(dialogEditStrings[4]);
			TakeNItems(pchar,"gold_dublon", iTemp);
			DeleteAttribute(Pchar, "quest.Deposits." + (sDepositType2));
		break;
		//<-- забор денег по частям		
		
		case "Deposit_return_dub_1":
			TakeNItems(pchar,"gold_dublon", sti(Pchar.Quest.Deposits.(sDepositType2).Result));
			Dialog.snd = "voice\USDI\USDI035";
			dialog.text = "Oh... It is too hard to lose it. I have really got used to this money. Come again anyway.";			
			Link.l1 = "I will if I need. Farewell.";			
			Link.l1.go = "Exit";
			DeleteAttribute(Pchar, "quest.Deposits." + (sDepositType2));
		break;
		//  ugeen <- вклады в дублонах	
		
		case "DeadMotherfucker":
			Dialog.TempNode = "DeadMotherFucker_1";
			Dialog.snd = "voice\USDI\USDI035";
			dialog.text = "You are still alive? Want to return my money perhaps? Screw you! I've lost so much money that you would never repay me! And I won't find rest until I see your corpse";
            Link.l1 = "I just want to settle out things in a peaceful way.";
			Link.l1.go = "LoanRestore_1";
			Link.l2 = LinkRandPhrase("Let's see then! Know that you are not protected from being a corpse as well!", "A threat?! Let's see then what you're going to do...", "Money isn't the most important thing in our life. Don't grieve too much over it and kill people.");
			Link.l2.go = "ExitDelLoan2";
		break;

		case "DeadMotherFucker_1":			
			Dialog.snd = "voice\USDI\USDI035";
			dialog.text = "Get out! I wish I would never see you again.";			
			Link.l1 = "...";			
			Link.l1.go = "ExitDelLoan2";
            Dialog.TempNode = "DeadMotherFucker_1";
		break;
		// boal обратимость факапства -->
		case "LoanRestore_1":
            iPastMonths = GetPastTime("Month", makeint(Pchar.Quest.Loans.(NPC_Area).StartYear),makeint(Pchar.Quest.Loans.(NPC_Area).StartMonth),makeint(Pchar.Quest.Loans.(NPC_Area).StartDay), makefloat(Pchar.Quest.Loans.(NPC_Area).StartTime), getDataYear(),getDataMonth(),GetDataDay(), GetTime());
			Pchar.Quest.Loans.(NPC_Area).Result = makeint(Pchar.Quest.Loans.(NPC_Area).Sum) + ((makeint(Pchar.Quest.Loans.(NPC_Area).Sum)/100)*makeint(Pchar.Quest.Loans.(NPC_Area).Interest))*(iPastMonths+1);
			dialog.text = "Oh really? And what are your concerns?";
			Link.l1 = "For today I owe you " + FindRussianMoneyString(sti(Pchar.Quest.Loans.(NPC_Area).Result)) + ". And I offer this money to you.";
			Link.l1.go = "DeadMotherFucker_1";
            if (sti(Pchar.Money) >= 2*sti(Pchar.Quest.Loans.(NPC_Area).Result))
            {
    			Link.l2 = "I offer you my debt to re-establish good relations with you. It is " + FindRussianMoneyString(2*sti(Pchar.Quest.Loans.(NPC_Area).Result)) + ".";
    			Link.l2.go = "LoanRestore_2";
			}
		break;
		
		case "LoanRestore_2":
			dialog.text = "Now you are talking! I can do business with you after all.";
			Link.l1 = "Thanks. I won't let you down anymore.";
			Link.l1.go = "ExitDelLoan2";
			NextDiag.TempNode = "First time";			
			addMoneyToCharacter(Pchar, -2*sti(Pchar.Quest.Loans.(NPC_Area).Result));
			DeleteAttribute(PChar, "quest.Loans_" + NPC_Area);
			DeleteAttribute(PChar, "quest.Loans." + NPC_Area);
			ChangeCharacterHunterScore(PChar, NationShortName(sti(NPChar.nation)) + "hunter", -30);
			ChangeCharacterComplexReputation(pchar,"nobility", 2);
		break;

		case "ExitDelLoan1":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			DeleteAttribute(Pchar, "quest.Loans." + (NPC_Area));
		break;

		case "ExitDelLoan2":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			DeleteAttribute(Pchar, "quest.Loans." + (NPC_Area));
			DeleteAttribute(Pchar, "quest.Deposits." + (NPC_Area));
		break;
		
        case "LoanGranted_exit":
			NextDiag.CurrentNode = NextDiag.TempNode;

			AddMoneyToCharacter(Pchar, makeint(Pchar.Quest.Loans.(NPC_Area).Sum));
			Pchar.Quest.Loans.(NPC_Area) = true;
			Pchar.Quest.Loans.(NPC_Area).StartDay = getDataDay();
			Pchar.Quest.Loans.(NPC_Area).StartMonth = getDataMonth();
			Pchar.Quest.Loans.(NPC_Area).StartYear = getDataYear();
			Pchar.Quest.Loans.(NPC_Area).StartTime = getTime();

			sTemp = "Loans_" + NPC_Area;			
			SetTimerCondition(sTemp, 0, makeint(Pchar.Quest.Loans.(NPC_Area).Period), 0, false);
			pchar.quest.(sTemp).CityId = NPC_Area;
			pchar.quest.(sTemp).win_condition = "LoansForAll";
			
			DialogExit();
			npchar.quest.trade_date = lastspeak_date; // дыра с прокачкой была
		break;
        
		//работорговец
		int iSlaveMoney;
		int amount;
		case "GiveTaskSlave":
			pchar.questTemp.Slavetrader.iSlaveQuantity = 300 + rand(100);
			pchar.questTemp.Slavetrader.iSlaveMoney = sti(pchar.questTemp.Slavetrader.iSlaveQuantity) * 250;
			dialog.Text = "Ah, come on! We are serious people, you and I, we are better than those idiots who are ready to die for a single doubloon, yet never ever try to make two doubloons of it\nI am looking for a man to offer a serious business. A man brave and active, honest and punctual, but not burdened with... eh... too much of scrupulousness concerning moral dilemmas. And I hope that you are the man I am looking for.";
			Link.l1 = "It will depend on what kind of 'deal' you are going to offer me.";
			Link.l1.go = "GiveTaskSlave_1";
		break;
			
		case "GiveTaskSlave_1":
			dialog.Text = "Very well, listen then. Slavery is the most profitable business in the Caribbean now days. I am not a planter, but I have trustworthy clients\nSo, I need the following amount of slaves - " + pchar.questTemp.Slavetrader.iSlaveQuantity + " heads. I am ready to pay you 250 pesos per each. Trust me, that's a fine price. In total you will earn " + FindRussianMoneyString(sti(pchar.questTemp.Slavetrader.iSlaveMoney)) + " pesos.";
			Link.l1 = "No, I am not a slave trader. Find yourself another assistant who doesn't care about his conscience.";
			Link.l1.go = "exit_slaves";
			Link.l2 = "A tempting offer. I'd like to do that. How soon you'll need the slaves?";
			Link.l2.go = "GiveTaskSlave_2";
		break;
			
		case "exit_slaves":
			dialog.Text = "Meh, it seems that nobody is eager to move his butt and take a gold under his feet. I am disappointed. Farewell and don't even think to spread about our talk. I have a long reach...";
			Link.l1 = "Your reach is 'dirty'... just like your tongue. Farewell.";
			Link.l1.go = "exit";
			pchar.questTemp.Slavetrader = "End_quest";
			DeleteAttribute(npchar, "quest.slave");
		break;
			
		case "GiveTaskSlave_2":
			dialog.Text = "I won't limit your time but try to accomplish your mission as soon as possible. The demand for the 'black ivory' is huge. If you do your job well then I'll be giving you such kind of job very often in future.";
			Link.l1 = "Sounds nice. Wait for the positive news.";
			Link.l1.go = "exit";						
			pchar.questTemp.Slavetrader = "Seek_slaves"; // это ввод имени квеста и состояния квеста
			AddQuestRecord("Slavetrader", "1");
			AddQuestUserData("Slavetrader", "sName", GetFullName(npchar));
			AddQuestUserData("Slavetrader", "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData("Slavetrader", "sQty", makeint(pchar.questTemp.Slavetrader.iSlaveQuantity));
			AddQuestUserData("Slavetrader", "sSum", makeint(pchar.questTemp.Slavetrader.iSlaveMoney));
			LAi_LocationDisableOfficersGen(&Locations[FindLocation(pchar.location)], true); // блокируем вход офицеров 2015
		break;
			
		case "Checkslaves":
			amount = GetSquadronGoods(Pchar, GOOD_SLAVES) - sti(pchar.questTemp.Slavetrader.iSlaveQuantity);
			dialog.Text = "Have you succeeded in getting that shipment of 'black ivory'?";
            if (amount < 0)
			{
				Link.l1 = "Not yet. Just checking if our agreement is still active.";
            	Link.l1.go = "exit";
			}
			else
			{
				Link.l1 = "I have. There are all in my cargo.";
            	Link.l1.go = "Takeslaves";
			}
		break;
		
		case "Takeslaves":
			amount = sti(pchar.questTemp.Slavetrader.iSlaveQuantity);
			dialog.Text = "Splendid. My men will take them... Don't worry about customs and a commandant of the fort. I am running a huge operation here so don't expect any troubles and no one will accuse you in smuggling.";
			Link.l1 = "It seems that you've got a strong position here. How about my payment?";
            Link.l1.go = "Takeslaves_1";
			RemoveCharacterGoods(Pchar, GOOD_SLAVES, amount);
		break;
		
		case "Takeslaves_1":
			AddMoneyToCharacter(pchar, makeint(pchar.questTemp.Slavetrader.iSlaveMoney));
			dialog.Text = "Here it is. I don't speak idly. Stay with me, captain, and soon you will own so much gold that you would need a galleon to move it!";
			Link.l1 = "That would be great... What's next?";
            Link.l1.go = "Takeslaves_2";
		break;
		
		case "Takeslaves_2":
			dialog.Text = "Next? Come here again in three weeks. I am preparing a deal right now and it will be ready by this time.";
			Link.l1 = "Deal. Farewell.";
            Link.l1.go = "exit";
			AddQuestRecord("Slavetrader", "2");
			AddQuestUserData("Slavetrader", "sName", GetFullName(npchar));
			pchar.questTemp.Slavetrader = "wait";
			SaveCurrentQuestDateParam("pchar.questTemp.Slavetrader_wait");//запомнить дату
		break;
		
		case "Takeslaves_3":
			if (4-sti(RealShips[sti(pchar.ship.type)].Class) < 0)//проверка класса корабля
			{
				dialog.Text = "I've got a job but your ship is too weak. I don't want to fail the mission neither to send you to death. There is still time so get yourself a bigger ship like barkentine, brigantine, brig or flute at least. Don't waste the time!";
				Link.l1 = "I see, I'll handle it. See you.";
            	Link.l1.go = "Takeslaves_3_smallship";
			}
			else
			{
				dialog.Text = "At last! I was waiting for you. Now let's get straight to our deal. As you know there always are competitors in any business. And I have my own. These grasping and unscrupulous bastards are always eager to take away a client from me! Actually, I want to eliminate one of them and make a good coin.";
				Link.l1 = "I am listening.";
            	Link.l1.go = "Takeslaves_4";
			}
		break;
		
		case "Takeslaves_3_smallship":
			pchar.questTemp.Slavetrader = "waitship";
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "Takeslaves_4":
			Slavetrader_GetRandomShore();//выбор бухты
			pchar.questTemp.Slavetrader.ShipName = GenerateRandomNameToShip(sti(NPChar.nation));
			pchar.questTemp.Slavetrader.UnknownPirateName = "l" + rand(GetNamesCount(NAMETYPE_ORIG) - 1);
			dialog.text = "Most excellent. Now listen. This rogue called " + GetName( NAMETYPE_ORIG, pchar.questTemp.Slavetrader.UnknownPirateName, NAME_NOM) + ", brought slaves from Africa and dropped anchor at " + XI_ConvertString(pchar.questTemp.Slavetrader.Island.Shore + "Gen") + ", this is an island called " + XI_ConvertString(pchar.questTemp.Slavetrader.Island) + ". He is waiting for smugglers there. His galleon is called '" + pchar.questTemp.Slavetrader.ShipName + ". Their deal must be broken at any cost!";
			link.l1 = "And how about the slaves? It would be such a waste to sink them!";
			link.l1.go = "Takeslaves_5";
		break;
		
		case "Takeslaves_5":
			dialog.Text = "Why would you do that? There's no need in that. " + GetName( NAMETYPE_ORIG, pchar.questTemp.Slavetrader.UnknownPirateName, NAME_NOM) + " has a bad renown and no one will be upset about his disappearance. Board his galleon, kill the man, bring me the cargo and I will sell it. According to my sources there are about thousand and a half of slaves.";
			Link.l1 = "Wow. That's quite the number. What about my payment?";
            Link.l1.go = "Takeslaves_6";
			Link.l2 = "No, sir, this intrigues are not for me. Why should I spoil my relations with smugglers?";
            Link.l2.go = "exit_slaves_1";
		break;
		
		case "exit_slaves_1":
			dialog.Text = "Well.. It looks like I was mistaken about you... Farewell and forget about our talk. And don't spread about what you've heard here. I own this town. And if you are planning to board the '" + pchar.questTemp.Slavetrader.ShipName + " for yourself... I will make sure that you would be hanged. Consider it.";
			Link.l1 = "Don't worry, I won't report to the authorities and I don't need your galleon. Farewell.";
            Link.l1.go = "exit";
			AddQuestRecord("Slavetrader", "8");
			AddQuestUserData("Slavetrader", "sSex", GetSexPhrase(" agreed"," agreed"));
			CloseQuestHeader("Slavetrader");
			pchar.questTemp.Slavetrader = "End_quest";//конец квеста
		break;
		
		case "Takeslaves_6":
			dialog.Text = "Considering that I've given you a location of the cargo and you don't need to sail in a search for: a prize the payment is a bit lower - 200 pesos for a head. And still that would be a great sum - three hundred thousand pesos in case of success.";
			Link.l1 = "Deal. How much time do I have?";
            Link.l1.go = "Takeslaves_7";
			Link.l2 = "Ho-ho! You say that like those slaves would swim by themselves to my ship hoping to get inside my cargo as soon as possible! Do you really want my people to risk their heads for such a tiny sum? Increase my reward or I am out of the business.";
            Link.l2.go = "exit_slaves_1";
		break;
		
		case "Takeslaves_7":
			dialog.text = "You've got two weeks. Don't be late or he will transfer his cargo and all will be over.";
			link.l1 = "Have to hurry then. Expect me with the good news.";
			link.l1.go = "exit";
			AddQuestRecord("Slavetrader", "3");
			AddQuestUserData("Slavetrader", "sName", GetFullName(npchar));
			AddQuestUserData("Slavetrader", "sShipName", pchar.questTemp.Slavetrader.ShipName);
			AddQuestUserData("Slavetrader", "sShoreName", XI_ConvertString(pchar.questTemp.Slavetrader.Island.Shore + "Abl"));
			AddQuestUserData("Slavetrader", "sShoreType", XI_ConvertString(GetIslandByArealName(pchar.questTemp.Slavetrader.Island) + "Dat"));
			pchar.quest.Slavetrader_ShipsAttack.win_condition.l1 = "location";
            pchar.quest.Slavetrader_ShipsAttack.win_condition.l1.location = pchar.questTemp.Slavetrader.Island;
            pchar.quest.Slavetrader_ShipsAttack.function = "Slavetrader_CreateSlaveShips";//создание кораблей
			SetFunctionTimerCondition("Slavetrader_SlaveShipsOver", 0, 0, 15, false);	//таймер
			pchar.questTemp.Slavetrader = "wait1";	//это заглушка
		break;
		
		case "Takeslaves_4_lose":
			dialog.text = "Well, " + GetFullName(pchar) + ", what about our mission? Your cheerless face tells me that you've failed it.";
			link.l1 = "Damn, you are right... I... well, you know... I was late. It seemed that he had already left the place, because I found no one there. Had to sail by the wind the whole way, damn it... ";
			link.l1.go = "Takeslaves_5_lose";
		break;
		
		case "Takeslaves_4_win":
			dialog.text = "Well, " + GetFullName(pchar) + ", what's your catch for today? They told me that " + GetName( NAMETYPE_ORIG, pchar.questTemp.Slavetrader.UnknownPirateName, NAME_NOM) + " feeds the fish.";
			link.l1 = "Yes, I was just in time! " + GetName( NAMETYPE_ORIG, pchar.questTemp.Slavetrader.UnknownPirateName, NAME_NOM) + " was transferring slaves to the smuggler's ship. Had to sink them to Davy Jones as well, so you have less competitors now.";
			link.l1.go = "Takeslaves_5_win";
		break;
		
		case "Takeslaves_5_lose":
			dialog.text = "Yes, I guess I was wrong about you. You were late? Or were just too scared to fight? Whatever. It holds no meaning now. Get lost. I am done with you. Forget everything you saw or heard.";
			link.l1 = "Farewell then.";
			link.l1.go = "exit";
			AddQuestRecord("Slavetrader", "5_5");
			AddQuestUserData("Slavetrader", "sSex", GetSexPhrase("",""));
			AddQuestUserData("Slavetrader", "sName", GetFullName(npchar));
			CloseQuestHeader("Slavetrader");
			pchar.questTemp.Slavetrader = "End_quest";
		break;
		
		case "Takeslaves_5_win":
			pchar.questTemp.Slavetrader.Nation = npchar.nation;
			amount = 1600 - GetSquadronGoods(Pchar, GOOD_SLAVES);
			sTemp = GetSquadronGoods(Pchar, GOOD_SLAVES);
			iSlaveMoney = makeint(sTemp)*200;
			if (amount < 0)
			{
				dialog.text = "I was right about you - "+ GetSexPhrase(" you are a dashing thug"," you are a brave sailor") +" . I need a man like you. You have succeeded on your mission in the most excellent way - you have brought more than a thousand and a half slaves! Unfortunately, I can pay you only for one thousand and six hundred slaves. I don't have enough coin to pay you for the rest, so you have to sell them by yourself. Your reward is 320 000 pesos.";
				link.l1 = "Gratitude. Nice doing business with you, " + npchar.name + "!";
				link.l1.go = "Takeslaves_6_win";
				AddMoneyToCharacter(pchar, 320000);
				RemoveCharacterGoods(Pchar, GOOD_SLAVES, 1600);
				AddQuestRecord("Slavetrader", "6");
				AddQuestUserData("Slavetrader", "sName", GetFullName(npchar));
				AddQuestUserData("Slavetrader", "sQty", 1600);
				AddQuestUserData("Slavetrader", "sMoney", 320000);
				break;
			}
			if (amount >= 0 && amount < 200)
			{
				dialog.text = "I was right about you - "+ GetSexPhrase(" you are a dashing thug"," you are a brave sailor") +". I need a man like you. You have succeeded on your mission in the most excellent way - you have brought me "+ sTemp +" slaves. Your reward is " + FindRussianMoneyString(iSlaveMoney) + ".";
				link.l1 = "Gratitude. Nice doing business with you, " + npchar.name + "!";
				link.l1.go = "Takeslaves_6_win";
				AddMoneyToCharacter(pchar, makeint(iSlaveMoney));
				RemoveCharacterGoods(Pchar, GOOD_SLAVES, sTemp);
				AddQuestRecord("Slavetrader", "6");
				AddQuestUserData("Slavetrader", "sName", GetFullName(npchar));
				AddQuestUserData("Slavetrader", "sQty", sTemp);
				AddQuestUserData("Slavetrader", "sMoney", makeint(iSlaveMoney));
				break;
			}
			if (amount >= 200 && amount < 600)
			{
				dialog.text = "At least you've survived the most difficult situation with all honor. Though the prize is less than I have expected I am still satisfied. You have brought "+ sTemp +" slaves. Your reward is " + FindRussianMoneyString(iSlaveMoney) + "";
				link.l1 = "Gratitude. Nice doing business with you, " + npchar.name + "!";
				link.l1.go = "Takeslaves_6_win";
				AddMoneyToCharacter(pchar, makeint(iSlaveMoney));
				RemoveCharacterGoods(Pchar, GOOD_SLAVES, sTemp);
				AddQuestRecord("Slavetrader", "6");
				AddQuestUserData("Slavetrader", "sName", GetFullName(npchar));
				AddQuestUserData("Slavetrader", "sQty", sTemp);
				AddQuestUserData("Slavetrader", "sMoney", makeint(iSlaveMoney));
				break;
			}
			if (amount >= 600 && amount < 1100)
			{
				dialog.text = "I see... I can understand that but I was expecting for more. You've brought only "+ sTemp +" slave. At least you've destroyed my competitors and that costs something. Your reward is  " + FindRussianMoneyString(iSlaveMoney) + ".";
				link.l1 = "My thanks. Appreciate your understanding, " + npchar.name + "!";
				link.l1.go = "Takeslaves_6_win";
				AddMoneyToCharacter(pchar, makeint(iSlaveMoney));
				RemoveCharacterGoods(Pchar, GOOD_SLAVES, sTemp);
				AddQuestRecord("Slavetrader", "6");
				AddQuestUserData("Slavetrader", "sName", GetFullName(npchar));
				AddQuestUserData("Slavetrader", "sQty", sTemp);
				AddQuestUserData("Slavetrader", "sMoney", makeint(iSlaveMoney));
				break;
			}
			if (amount >= 1100 && amount < 1600)
			{
				dialog.text = "Sounds great but... hm. Looks like I was mistaken about you. What have you brought? "+ sTemp +" slaves? And what about the rest? And don't tell me that you have sunk them. I'm sure you've sold them to smugglers, or even worse - to that bastard Lavoisier. Get the fuck out, I don't want to have any business with you anymore!";
				link.l1 = "As you wish, bye.";
				link.l1.go = "node_hanter_1";
				break;
			}
			dialog.text = "Sounds great but... where are our slaves? Where is our cargo? And don't tell me that you have sunk it. You must have sold it to the smugglers or, worse, to that bastard Lavoisier. Get lost, I am done with you.";
			link.l1 = "As you wish, bye.";
			link.l1.go = "node_hanter_1";
		break;
		
		case "node_hanter_1":
			dialog.text = "This ain't over. No one dares to fool me! And you will pay for your try - I'll make sure that you'll have problems. Now get out from here!";
			link.l1 = "Fuck you and your slave trading!";
			link.l1.go = "exit";
			AddQuestRecord("Slavetrader", "9");
			CloseQuestHeader("Slavetrader");
			ChangeCharacterHunterScore(pchar, NationShortName(sti(pchar.questTemp.Slavetrader.Nation)) + "hunter", 30);
			pchar.questTemp.Slavetrader = "End_quest";
		break;
			
		case "Takeslaves_6_win":
			dialog.text = "It looks like we are doing well together, " + pchar.name + ". I am very glad. See me in a month and, perhaps, I'll find you job just for you. I have a few ideas already.";
			link.l1 = "Sure, I'll see you in a month. My work with you is very profitable.";
			link.l1.go = "Takeslaves_7_win";
		break;
			
		case "Takeslaves_7_win":
			dialog.text = "It will make you a fortune... One last question, " + pchar.name + ", have you found anything unusual in the galleon's cabin?";
			link.l1 = "Nothing special really... Did I miss anything?";
			link.l1.go = "Nostatue";
			if (CheckCharacterItem(pchar, "talisman8"))
			{
				link.l2 = "You mean this old buckle?";
				link.l2.go = "Yestatue";
			}
		break;
			
		case "Nostatue":
			dialog.text = "Maybe. Or maybe not... It doesn't matter now. See you in a month. Farewell!";
			link.l1 = "See you, " + npchar.name + ".";
			link.l1.go = "exit";
			SaveCurrentQuestDateParam("pchar.questTemp.Slavetrader_wait_1");
			pchar.questTemp.Slavetrader = "wait_1";
		break;
			
		case "Yestatue":
			dialog.text = "Exactly! This Medici fibula... have you ever heard about them? That means that it really was in the bastard's cabin... May I take a look?";
			link.l1 = "Sure, take it.";
			link.l1.go = "Yestatue_1";
			RemoveItems(PChar, "talisman8", 1);
		break;
			
		case "Yestatue_1":
			Log_Info("You gave a talisman");
			PlaySound("interface\important_item.wav");
			dialog.text = "Well-well... It really is. Listen, " + pchar.name + ", sell it to me. I am ready to pay one hundred thousands pesos.";
			link.l1 = "One hundred thousands? Hm.. I agree. Take it!";
			link.l1.go = "Buystatue";
			link.l2 = "No I won't sell it. The true price of this fibula can't be valued by silver or gold. I know how such things work.";
			link.l2.go = "Nobuystatue";
		break;
			
		case "Buystatue":
			dialog.text = "Perfect! I am glad that we had a deal. Take your money. Looking forward to see you in month.";
			link.l1 = "Farewell, " + npchar.name + ".";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, 100000);
			SaveCurrentQuestDateParam("pchar.questTemp.Slavetrader_wait_1");
			pchar.questTemp.Slavetrader = "wait_1";
		break;
			
		case "Nobuystatue":
			dialog.text = "You see, I desperately need this fibula! I completely agree with you, it can't be valued with money, any dumb salesman will not even pay you five thousand for it. But it seems that you really know arcane rites, since you refuse to sell it for such sum\nI offer you an exchange, if you don't want money. I have something you might find interesting. Here, take a look. An amazing light armor! See for yourself! I offer you it in exchange for the fibula\nIt is not unique by the way. You sailor, you can always find more for yourself and I can't. Do you agree now?";
			link.l1 = "Heh... I suppose. Give me my armor and take this fibula.";
			link.l1.go = "Nobuystatue_yes";
			link.l2 = "No, this fibula has a much greater price for me than this armor. I shall keep it to myself.";
			link.l2.go = "Nobuystatue_no";
		break;
			
		case "Nobuystatue_yes":
			dialog.text = "Splendid! Glad that we had a deal. This is your armor now. Take it. See you in a month. Farewell.";
			link.l1 = "See you, " + npchar.name + ".";
			link.l1.go = "exit";
			TakeNItems(pchar, "cirass7", 1);
			Log_Info("You have received a brigant");
			PlaySound("interface\important_item.wav");
			SaveCurrentQuestDateParam("pchar.questTemp.Slavetrader_wait_1");
			pchar.questTemp.Slavetrader = "wait_1";
		break;
			
		case "Nobuystatue_no":
			dialog.text = "Too bad.. Really bad. Well, take it. I don't judge you. See you in month. Farewell.";
			link.l1 = "Farewell.";
			link.l1.go = "exit";
			TakeNItems(pchar, "talisman8", 1);
			Log_Info("You have received a talisman");
			PlaySound("interface\important_item.wav");
			SaveCurrentQuestDateParam("pchar.questTemp.Slavetrader_wait_1");
			pchar.questTemp.Slavetrader = "wait_1";
		break;
			
		case "EscapeSlave":
			dialog.text = "You are just in time, " + pchar.name + ". I have a mission for you if you are ready to get it started.";
			link.l1 = "Sure, I am ready.";
			link.l1.go = "EscapeSlave_1";
		break;
			
		case "EscapeSlave_1":
			dialog.text = "Excellent! Now, straight to the point. Have you heard the last news?";
			link.l1 = "Hm, what do you mean? There are a lot of news coming every day.";
			link.l1.go = "EscapeSlave_2";
		break;
			
		case "EscapeSlave_2":
			dialog.text = "This one is all about our business. There was the greatest runaway of slaves in the New World's history! More than a thousand souls have escaped and in the meantime the have destroyed and burned a few Holland's outposts.";
			link.l1 = "Intriguing. Go on.";
			link.l1.go = "EscapeSlave_3";
		break;
			
		case "EscapeSlave_3":
			dialog.text = "But they didn't just run away, somehow they had managed to leave the island! No trails left. Mathias Beck is outraged. But it is not the point… Point is, that I ask you to sail to Curacao, learn what happened there, find the refugees and capture them\nAnd, of course, to save them from the hands of Dutch justice, which would be merciless to them. I will pay 300 pesos per a head - I have heard that they are very good slaves.";
			link.l1 = "Got it. I'm heading to Curacao. Wait me with the good news.";
			link.l1.go = "EscapeSlave_yes";
			link.l2 = "You know, I won't take the mission. I won't deprive that people of their freedom. They have put their life's at risk to get it. They have earned it.";
			link.l2.go = "EscapeSlave_no";
		break;
			
		case "EscapeSlave_no":
			dialog.text = "What a pity... I didn't expect that from you... and at the most inappropriate time. I suppose, it's clear for you that our partnership is over. Farewell.";
			link.l1 = "Have a nice day.";
			link.l1.go = "exit";
			AddQuestRecord("Slavetrader", "8");
			AddQuestUserData("Slavetrader", "sSex", GetSexPhrase("",""));
			CloseQuestHeader("Slavetrader");
			pchar.questTemp.Slavetrader = "End_quest";
		break;
			
		case "EscapeSlave_yes":
			Slavetrader_GetEscapeShore();
			pchar.questTemp.Slavetrader.ShipName = GenerateRandomNameToShip(HOLLAND);
			pchar.questTemp.Slavetrader = "EscapeSlave_Villemstad";
			AddQuestRecord("Slavetrader", "22_1");
			AddQuestUserData("Slavetrader", "sName", GetFullName(npchar));
			DialogExit();
		break;
			
		case "Escape_slaves_win":
			int iSlaveMoneyH;
			string sNum;
			amount = 1100 - GetSquadronGoods(Pchar, GOOD_SLAVES);
			sTemp = GetSquadronGoods(Pchar, GOOD_SLAVES);
			iSlaveMoney = makeint(sTemp)*300;
			sNum = GetSquadronGoods(Pchar, GOOD_SLAVES) - 1100;
			iSlaveMoneyH = makeint(sNum)*100;
			if (amount < 0)
			{
				dialog.text = "Ha! You've not only succeeded in your hard mission but you've brought more than slaves that I've requested - "+ sTemp +" slaves. But "+ sNum +" slaves didn't escape from Curacao. I pay you 100 pesos for a head. I suppose that will work for you. Your reward is 330 000 pesos and " + FindRussianMoneyString(iSlaveMoneyH) + " for an excess, ha-ha.";
				link.l1 = "Ha! You definitely can't be cheated. I agree, whatever you say, " + npchar.name + "!";
				link.l1.go = "Escape_slaves_win_1";
				AddMoneyToCharacter(pchar, 330000);
				AddMoneyToCharacter(pchar, makeint(iSlaveMoneyH));
				RemoveCharacterGoods(Pchar, GOOD_SLAVES, sTemp);
				AddQuestRecord("Slavetrader", "22_5");
				AddQuestUserData("Slavetrader", "sSex", GetSexPhrase("",""));
				AddQuestUserData("Slavetrader", "sName", GetFullName(npchar));
				AddQuestUserData("Slavetrader", "sQty", sTemp);
				AddQuestUserData("Slavetrader", "sMoney", makeint(iSlaveMoneyH));
				break;
			}
			if (amount < 101 && amount >= 0)
			{
				dialog.text = "You have finished that uneasy mission in the most excellent way and brought me "+ sTemp +" slaves. Your reward is " + FindRussianMoneyString(iSlaveMoney) + ".";
				link.l1 = "My thanks. Pleasure doing business with you, " + npchar.name + "!";
				link.l1.go = "Escape_slaves_win_1";
				AddMoneyToCharacter(pchar, makeint(iSlaveMoney));
				RemoveCharacterGoods(Pchar, GOOD_SLAVES, sTemp);
				AddQuestRecord("Slavetrader", "22_6");
				AddQuestUserData("Slavetrader", "sName", GetFullName(npchar));
				AddQuestUserData("Slavetrader", "sQty", sTemp);
				AddQuestUserData("Slavetrader", "sMoney", makeint(iSlaveMoney));
				break;
			}
			if (amount >= 100 && amount < 600)
			{
				dialog.text = "You have succeeded in that difficult mission. The prize is not that rich as I have expected but I am satisfied anyway. So you've brought here "+ sTemp +" slaves. Your reward is " + FindRussianMoneyString(iSlaveMoney) + ".";
				link.l1 = "Thanks. Nice doing business with you, " + npchar.name + "!";
				link.l1.go = "Escape_slaves_win_1";
				AddMoneyToCharacter(pchar, makeint(iSlaveMoney));
				RemoveCharacterGoods(Pchar, GOOD_SLAVES, sTemp);
				AddQuestRecord("Slavetrader", "22_6");
				AddQuestUserData("Slavetrader", "sName", GetFullName(npchar));
				AddQuestUserData("Slavetrader", "sQty", sTemp);
				AddQuestUserData("Slavetrader", "sMoney", makeint(iSlaveMoney));
				break;
			}
			if (amount >= 600 && amount < 1100)
			{
				dialog.text = "You've found them? Hm... what have you brought to me?"+ sTemp +" slaves? Where is the rest of the cargo? And don't even try to tell me that you have sunk it. You must have sold it to smugglers, or even worse - to that bastard Lavoisier from Isla-Tesoro. Get away from here, I have no wish to work with you anymore.";
				link.l1 = "Farewell.";
				link.l1.go = "node_hanter_1";
				break;
			}
			dialog.text = "Found them? What about the slaves? Where is our cargo? And don't even try to tell me that you have sunk it. You must have sold it to smugglers or even worse - to that bastard Lavoisier from Isla-Tesoro. Get away from here, I have no wish to work with you anymore.";
			link.l1 = "Farewell.";
			link.l1.go = "node_hanter_1";
		break;
		
		case "Escape_slaves_win_1":
			dialog.text = "I really appreciate you, " + pchar.name + ". Really. Come again here in a month and I will prepare a new business profitable for both of us.";
			link.l1 = "I am also satisfied with our partnership, " + npchar.name + ". See you in a month.";
			link.l1.go = "exit";
			SaveCurrentQuestDateParam("pchar.questTemp.Slavetrader_wait_2");
			pchar.questTemp.Slavetrader = "wait_2";
		break;
			
		case "Slaveshore":
			dialog.text = "You are just in time, " + pchar.name + ". I am looking for a brave and not scrupulous sailor, ha-ha. Are you ready to handle my job?";
			link.l1 = "I am listening.";
			link.l1.go = "Slaveshore_1";
		break;
			
		case "Slaveshore_1":
			pchar.questTemp.Slavetrader.Island = Islands[GetCharacterCurrentIsland(pchar)].id;
			pchar.questTemp.Slavetrader.Island.Shore = GetIslandRandomShoreId(pchar.questTemp.Slavetrader.Island);
			pchar.questTemp.Slavetrader.ShipName = GenerateRandomNameToShip(sti(NPChar.nation));
			pchar.questTemp.Slavetrader.Nation = NPChar.nation;
			dialog.text = "It is quite simple this time. Today, a pinnace '" + pchar.questTemp.Slavetrader.ShipName + "' under the flag of " + NationNameGenitive(sti(npchar.nation)) + " has dropped anchor at " + XI_ConvertString(pchar.questTemp.Slavetrader.Island.Shore + "Gen") + " bay. It was loaded with a large batch of 'ebony' with a help of the local smugglers. Two thousand heads, not less\nNo soldiers in a crew and a captain is a trader. Overall, no threat at all. Board the ship and bring me the cargo. 200 pesos per a head as usual.";
			link.l1 = "Hm... It is not the same as the last job. You suggest me attacking a ship of your own nation!";
			link.l1.go = "Slaveshore_2";
		break;
			
		case "Slaveshore_2":
			dialog.text = "I don get it, " + pchar.name + ". Does the ship's flag matters? Do you really care about that?";
			link.l1 = "Do I? No, I don't give a fuck, gold doesn't have a nationality. It just was a bit unexpected...";
			link.l1.go = "Slaveshore_3_yes";
			link.l2 = "I do care. I don't want to have " + NationNameAblative(sti(npchar.nation)) + " in my enemies.";
			link.l2.go = "Slaveshore_3_no";
		break;
			
		case "Slaveshore_3_no":
			dialog.text = "Are you serious? You are probably kidding me. In that case, go away. And forget about everything you saw or heard here!";
			link.l1 = "See ya," + npchar.name + ".";
			link.l1.go = "node_hanter_1";
		break;
			
		case "Slaveshore_3_yes":
			dialog.text = "Why are you surprised? Because I don't care about coins' nationality? I assure, that indeed, I don't. To be honest, patriotism is bad for a professional banker, unless he is eager to go broke one day\nBut enough of philosophy. Let's cut to the chase - the ship will stay here until the midnight, so you don't have much time left. Are you ready to proceed?";
			link.l1 = "Yes, " + npchar.name + ", I am on my way.";
			link.l1.go = "Slaveshore_4";
		break;
			
		case "Slaveshore_4":
			dialog.text = "Splendid. I have no doubt that you would succeed in our mission. Good luck." + pchar.name + ".";
			link.l1 = "Thanks! Farewell.";
			link.l1.go = "exit";
            AddQuestRecord("Slavetrader", "10");
			AddQuestUserData("Slavetrader", "sName", GetFullName(npchar));
			AddQuestUserData("Slavetrader", "sShip", pchar.questTemp.Slavetrader.ShipName);
			pchar.quest.Slavetrader_ShoreAttack.win_condition.l1 = "location";
            pchar.quest.Slavetrader_ShoreAttack.win_condition.l1.location = pchar.questTemp.Slavetrader.Island;//отправляем в локацию
            pchar.quest.Slavetrader_ShoreAttack.function = "Slavetrader_CreateShoreShips";//создание кораблей
			SetFunctionTimerCondition("Slavetrader_ShoreShipsOver", 0, 0, 1, false);	//таймер
			pchar.questTemp.Slavetrader = "wait1";	//заглушка
		break;
			
		case "Pinas_lose":
		dialog.text = "Well, " + GetFullName(pchar) + ", what about your mission? Your cheerless face tells me that you've failed it.";
			link.l1 = "You are damn right... I.. Well... I was too late. I was in the tavern and when I shipped out there was nobody in the sea.";
			link.l1.go = "Takeslaves_5_lose";
		break;
			
		case "Slaveshore_5":
			dialog.text = "" + pchar.name + ", please calm down. It is not my fault! Damn, I have received a report to late... That was a treachery! One of my trusted men has sold me out!";
			link.l1 = "Fine, I see that you are speaking the truth. Your luck that captain of the pinnace told me that our 'business' was uncovered. I'd have already killed you if he hasn't blabbed out. But you, fucking sack of money, were telling me all the time that you 'own this town'!";
			link.l1.go = "Slaveshore_6";
		break;
			
		case "Slaveshore_6":
			dialog.text = "The ambush was organized not by the local authorities, otherwise I would have known... " + pchar.name + ", it is not the right time for quarrels. Both of us are in danger, one of my ex contractors has set us up\nI managed to find out that all gathered proofs - a package of papers - are being transported to our governor-general. If he has them, we are finished! You will suffer the most, by the way.";
			link.l1 = "Now I see what that bastard captain has meant!";
			link.l1.go = "Slaveshore_7";
		break;
			
		case "Slaveshore_7": //выбор острова, куда бригантина пойдет
			switch (sti(NPChar.nation))
            {
                case HOLLAND :
					pchar.questTemp.Slavetraderbrig.Island = "Curacao";
                break;
                case FRANCE :
					pchar.questTemp.Slavetraderbrig.Island = "Nevis";
                break;
                case SPAIN :
					pchar.questTemp.Slavetraderbrig.Island = "Cuba2";  
                break;
                case ENGLAND :
					pchar.questTemp.Slavetraderbrig.Island = "Jamaica";     
                break;
			}
			pchar.questTemp.Slavetraderbrig.ShipName = GenerateRandomNameToShip(sti(NPChar.nation));//имя бригантины
			pchar.questTemp.Slavetrader.Nation = NPChar.nation;
			dialog.text = "Listen carefully. We have still got a chance. The package was sent on brigantine '" + pchar.questTemp.Slavetraderbrig.ShipName + ". That is the only thing I certain about. Papers are being delivered to governor-general to his residence on " + XI_ConvertString(pchar.questTemp.Slavetraderbrig.Island) + ". You've got to intercourse it, board it and find that discrediting evidences.";
			link.l1 = "Don't have much choice here. Pray for me, for yourself and hope that I will be able to catch it. We'll talk again about all of this when I'll be back. Don't think that I'll just let it go.";
			link.l1.go = "Slaveshore_8";
			AddQuestRecord("Slavetrader", "14");
			AddQuestUserData("Slavetrader", "sName", GetFullName(npchar));
			AddQuestUserData("Slavetrader", "sShipName", pchar.questTemp.Slavetraderbrig.ShipName);
			AddQuestUserData("Slavetrader", "sIsland", XI_ConvertString(GetIslandByArealName(pchar.questTemp.Slavetraderbrig.Island)));
			pchar.quest.Slavetrader_BrigAttack.win_condition.l1 = "location";
            pchar.quest.Slavetrader_BrigAttack.win_condition.l1.location = pchar.questTemp.Slavetraderbrig.Island;//отправляем в локацию
            pchar.quest.Slavetrader_BrigAttack.function = "Slavetrader_CreateBrig";//создание бригантины
			SetFunctionTimerCondition("Slavetrader_BrigOver", 0, 0, 15, false);	//таймер
			pchar.questTemp.Slavetrader = "wait1";	//это нода ожидания, пустая
		break;
		
		case "Slaveshore_8":
			dialog.text = "Getting this package is your main priority! I won't be sure in my safety until you deliver it to me... Damn..." + pchar.name + ", looks like we've got a problem here...";
			link.l1 = "What is it?";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Slavetrader_enterSoldiers");
			break;
			
		case "Brig_lose":
			dialog.text = "Damn... I was counting on you, " + pchar.name + ". Fine then. But we won't be doing any business anymore. If I am not able to bribe an investigator I'd have to run away. And I don't recommend you to stay here - soldiers may come here at any time. Farewell.";
			link.l1 = "Farewell, " + npchar.name + ".";
			link.l1.go = "exit";
			pchar.questTemp.Slavetrader = "End_quest";
		break;
			
		case "Letter_lose":
			dialog.text = "They were there. Well, we can't do any business together it's not safe anymore. Farewell.";
			link.l1 = "Farewell, " + npchar.name + ".";
			link.l1.go = "exit";
			CloseQuestHeader("Slavetrader");
			pchar.questTemp.Slavetrader = "End_quest";
		break;
			
		case "Brig_win":
			dialog.text = "Excellent! I had no doubt in you, " + pchar.name + ". Please give me that papers I am too nervous.";
			link.l1 = "Take them.";
			link.l1.go = "Brig_win_1";
		break;
			
		case "Brig_win_1":
			RemoveItems(PChar, "letter_1", 1);
			dialog.text = "Good... Now I am safe. Governor-general won't know a thing and I've already solved all problems with the local authorities but it was pricey I tell you.";
			link.l1 = "Sounds great, but don't you think that you have to compensate me my troubles because of your thoughtless actions?";
			link.l1.go = "Brig_win_2";
		break;
			
		case "Brig_win_2":
			dialog.text = "Sure, " + pchar.name + ". Even more, I owe you a lot. And I really expect to continue our business. But I ask you to understand me - I've spent a huge sum - governor's and commandant's loyalty cost a lot. And I had to deal with that murder of the whole patrol in my bank...";
			link.l1 = "You mean that you won't compensate my costs?!";
			link.l1.go = "Brig_win_3";
		break;
			
		case "Brig_win_3":
			dialog.text = "Don't be that harsh, " + pchar.name + ". I really do have trouble with money now so I offer you a different kind of payment.";
			link.l1 = "I am listening to you then.";
			link.l1.go = "Brig_win_4";
		break;
			
		case "Brig_win_4":
			dialog.text = "Me and my companion were caught by a storm close to southern shores of Main a year ago. Our ships had been thrown at the rocks of Boca de la Sierpe bay, although they sank soon, we managed to drag our cargo ashore. Chests filled with precious stones and jewelry. The bay seemed to be quite cozy, so we hid treasures without a trouble\nWe were attacked by the Indians the next morning as soon as the storm had ended. That's how the majority of survivors died, including my companion. Me and a few sailors managed to escape on a longboat\nWe had safely reached Cumana, yet I didn't risk to return for the treasures. I am sure that local savages are still protecting their shore as well as my chests. But you can deal with that bunch of redskins\nThe jewelry you'll find there is sufficient enough to cover all your expenses, including an expedition to southern Main.";
			link.l1 = "Hm... fine. Then I am heading to Cumana";
			link.l1.go = "Brig_win_5";
		break;
			
		case "Brig_win_5":
			dialog.text = "You can be confident, " + pchar.name + ", that all I've said was a truth. I expect to see you in a month. I have already got in mind one more deal and I should help my staggered business. Farewell.";
			link.l1 = "See you, " + npchar.name + ".";
			link.l1.go = "exit";
			SaveCurrentQuestDateParam("pchar.questTemp.Slavetrader_wait_3");
			pchar.questTemp.Slavetrader = "wait_3";
			Pchar.quest.Slavetrader_Bonanza.win_condition.l1 = "location";
            Pchar.quest.Slavetrader_Bonanza.win_condition.l1.location = "Shore18";
            Pchar.quest.Slavetrader_Bonanza.function = "Slavetrader_Bonanza";
		break;
			
		case "SlaveGalleon":
			dialog.text = "And here you are, " + pchar.name + ". Nice, you are just in time as always. I'd like to give you more information about the Caribbean slave market before I'll give you a next mission. Do you know what does the word 'repartimiento' mean?";
			link.l1 = "Hm, no, " + npchar.name + ", I don't. But I suppose that it is about taking away something from someone. Am I right?";
			link.l1.go = "SlaveGalleon_1";
		break;
			
		case "SlaveGalleon_end":
			dialog.text = "You surprise me. What have you expected from me? Go away!";
			link.l1 = "An illegal business is too tough for my morality. Especially the slave trade.";
			link.l1.go = "node_hanter_1";
		break;
			
		case "SlaveGalleon_1":
			dialog.text = "You've almost got it," + pchar.name + ". Taking away someone's freedom. Repartimiento is a tricky and legal way to enslave local Indians. So to speak. Spanish authorities use it against native people of Main. Are you interested in knowing more?";
			link.l1 = "Why not?";
			link.l1.go = "SlaveGalleon_2";
		break;
			
		case "SlaveGalleon_2":
			dialog.text = "Representatives of the Spanish crown visits Indian settlements. Using cynic deception and direct threats, they force Indians to buy all kinds of rubbish like rotten meat and old razors at fabulous prices. On credit\nSome time later, let's say a year, representatives return and demand a payment. If Indians can't pay off, which is what usually happens, the Spanish take a part of their men capable of working, supposedly for a time and to 'teach them how to cultivate land'\nAs you understand, they never return back to their settlements. That's how our trustful redskins get to sugar plantations and redwood factories.";
			link.l1 = "Heh... really... What Indians do about that? Do they resist when Spanish enslaves them? Or they simply don't understand that?";
			link.l1.go = "SlaveGalleon_3";
		break;
			
		case "SlaveGalleon_3":
			dialog.text = "I guess that they always see it coming, but only a few dare to openly oppose, especially when the Spanish show a paper with a fingerprint of the chieftain. Sure, such tactics is normally applied to the peaceful tribes like Arawaks or Miskitos. Such trick will not work with warlike Itza or Akawoys\nWell, let's talk about your mission.";
			link.l1 = "I already feel the smell of a lot of coins! I am listening to you, " + npchar.name + ".";
			link.l1.go = "SlaveGalleon_4";
		break;
			
		case "SlaveGalleon_4":
			Slavetrader_GetHispanShore();
			sTemp = pchar.questTemp.SlavetraderAreal.add; 
			pchar.questTemp.Slavetrader.ShipName = GenerateRandomNameToShip(SPAIN);
			dialog.text = "Soon " + sTemp + " a heavy galleon will ship out. It's named " + pchar.questTemp.Slavetrader.ShipName + ". It contains a huge amount of slaves - about 3000 men - Indians of Orinoco, captured according to the repartimentos tactics\The galleon is sailing to Santiago, sugar plantations of Cuba need a lot of workers. You must capture the galleon with her cargo. Pay rates stay usual - 200 pesos per a head. ";
			link.l1 = "Heh! Sounds good. I agree.";
			link.l1.go = "SlaveGalleon_5";
			link.l2 = "You know I don't like that repartimiento of yours. It's too cynical. I am not going to do this.";
			link.l2.go = "SlaveGalleon_end";
		break;
			
		case "SlaveGalleon_5":
			sTemp = pchar.questTemp.SlavetraderAreal.add; 
			dialog.text = "I wish you luck then. Know that the captain of this galleon is a very skilled and experienced war sailor. It won't be an easy fight so prepare yourself. Don't waste time, it will take fifteen or twenty days for him to reach " + sTemp + " Santiago. Try not to miss it, though this galleon is really hard to miss\nYes! Almost forgot! There are plenty of Indian trinkets on the ship, redskins often pay their debts with their cult items and craft. Bring to me anything special you find, I will pay you a great a deal for every valuable item.";
			link.l1 = "I understand.";
			link.l1.go = "exit";
			SlavetraderGalleonInWorld();
			SetFunctionTimerCondition("Slavetrader_SlaveGalleonOver", 0, 0, 20, false);
			pchar.questTemp.Slavetrader = "wait1";
			AddQuestRecord("Slavetrader", "18");
			AddQuestUserData("Slavetrader", "sSex", GetSexPhrase("",""));
			AddQuestUserData("Slavetrader", "sShipName", pchar.questTemp.Slavetrader.ShipName);
			AddQuestUserData("Slavetrader", "sAreal", sTemp);
		break;
			
		case "Lostgalleon":
			dialog.text = "Well, " + pchar.name + ", it was my very last hope... That's why I've offered this job to you. Nobody else but only you is able to do that... and I see that you are not too. Let's say goodbye then. After the last fail and all of that gossips, all of my clients are gone. And I am almost a bankrupt, perhaps, I have to leave this town. I don't blame you - this job was too tough. Eh... Farewell," + pchar.name + ".";
			link.l1 = "I am so sorry, " + npchar.name + ", that got too far. I am really sorry. Perhaps, it all will settle down. Goodbye.";
			link.l1.go = "exit";
			CloseQuestHeader("Slavetrader");
			pchar.questTemp.Slavetrader = "End_quest";
		break;
			
		case "Wingalleon":
			pchar.questTemp.Slavetrader.Nation = npchar.nation;
			amount = 3000 - GetSquadronGoods(Pchar, GOOD_SLAVES);
			sTemp = GetSquadronGoods(Pchar, GOOD_SLAVES);
			iSlaveMoney = makeint(sTemp)*200;
			if(amount < 1) 
			{
				dialog.text = "Fuh, I feel better now... I was right trusting you... Where did this irony come from? What's wrong?";
				link.l1 = "Dear sir, it wasn't a galleon... or a very a big galleon... Damn! It was a battleship! And you haven't even warned me! But I have managed to board her. I have "+ sTemp +" slaves and I'm ready to transfer them to you. According to our deal you owe me - " + FindRussianMoneyString(iSlaveMoney) + ". It would be great to get some compensation for your misinformation.";
				link.l1.go = "Wingalleon_1";
			}
			else
			{
			dialog.text = "Did you find the galleon? What about slaves? There are supposed to be three thousand of them and no less! Damn it, everyone is a rat and a traitor! I didn't expect it from you… you were my last hope\nVery well… I swear, I will spend every coin I have left to destroy you, to kill you! The whole fleet of " + NationNameGenitive(sti(npchar.nation)) + " will be hunting you! Get away from here!";
				link.l1 = "Well...";
				link.l1.go = "Wingalleon_goaway";
			}
		break;
			
		case "Wingalleon_goaway":
			AddQuestRecord("Slavetrader", "9");
			CloseQuestHeader("Slavetrader");
			ChangeCharacterHunterScore(pchar, NationShortName(sti(pchar.questTemp.Slavetrader.Nation)) + "hunter", 70);
			pchar.questTemp.Slavetrader = "End_quest";
			DialogExit();
		break;
			
		case "Wingalleon_1":
			dialog.text = "You don't say so! I swear, I had no idea. A heavy galleon was supposed to sail, not a bloody ship of the line! It seems that they changed their plans in the last moment… But yet you have succeeded!\nI completely agree with you about the money and compensation of your expenses, thing is that I don't possess such sum right now. You know about my recent troubles... But don't go angry, " + pchar.name + ", for God's sake. You give me the cargo and I'll sell it, my client is already waiting\nI will have the whole sum in five day, so you will get what you deserve. You may rely upon me. Here, take all cash I have right now.";
			link.l1 = "Hm... I expected to receive the money now. I wish you knew what kind of fight I had to go through! Ah, whatever… I will sympathize with you. But keep in mind that if you try to screw me, I will find you even in Europe!";
			link.l1.go = "Wingalleon_yes";
			link.l2 = "You know, " + npchar.name + ", screw you! It wasn't a deal. You can't even imagine what kind of fight I had to handle. I take all of slaves to myself and sell them without your agency.";
			link.l2.go = "Wingalleon_no";
		break;
			
		case "Wingalleon_no":
			dialog.text = "So, now you are talking! Looks like unsuspecting " + npchar.name + " was only a cow to milk, a simple delay is enough for you to screw me and to start an operation on your own. It seems that you have forgotten that I was the one who gave you the job and the tipping off about the booty\nVery well… I swear, I will spend every coin I have left to destroy you, to kill you! The whole fleet of " + NationNameGenitive(sti(npchar.nation)) + " will be hunting you! Get out of my sight!";
			link.l1 = "Don't dare to scare me, an empty money chest. I will sink all your fleet and feed crabs with it.";
			link.l1.go = "exit";
			AddQuestRecord("Slavetrader", "9");
			CloseQuestHeader("Slavetrader");
			ChangeCharacterHunterScore(pchar, NationShortName(sti(pchar.questTemp.Slavetrader.Nation)) + "hunter", 70);
			pchar.questTemp.Slavetrader = "End_quest";
		break;
			
		case "Wingalleon_yes":
			dialog.text = "Thank you for your understanding, " + pchar.name + ". I promise that everything will be fine, no need in your threats\nTake this as an advance. Fifteen chests. Five of them will serve as a compensation of moral damage. Come see me in five days to get the rest.\nDon't forget to bring all Indian items you have found on the ship... if you found them at all, of course. I have nothing to pay you for them anyway.";
			link.l1 = "In five days," + npchar.name + ". In five days...";
			link.l1.go = "Wingalleon_yes_1";
		break;
			
		case "Wingalleon_yes_1":
			TakeNItems(pchar, "chest", 15);
			Log_Info("You've received credit chests");
			PlaySound("interface\important_item.wav");
			SaveCurrentQuestDateParam("pchar.questTemp.Slavetrader_wait_4");
			pchar.questTemp.Slavetrader = "wait_4";
			AddQuestRecord("Slavetrader", "20");
			AddQuestUserData("Slavetrader", "sName", GetFullName(npchar));
			sTemp = GetSquadronGoods(Pchar, GOOD_SLAVES);
			pchar.questTemp.Slavetrader.iSlaveMoney = makeint(sTemp)*200-120000;
			RemoveCharacterGoods(Pchar, GOOD_SLAVES, sTemp);
			DialogExit();
		break;
	
		case "FindRat":
			dialog.text = "As I promised, " + pchar.name + ", I am ready to pay you. Slaves are sold, customer is happy and so are we. After deduction of an advance your reward is" + FindRussianMoneyString(sti(pchar.questTemp.Slavetrader.iSlaveMoney)) + ". Please take your money.";
			link.l1 = "Splendid, " + npchar.name + ". It's good to deal with a man who can keep his word...";
			link.l1.go = "FindRat_1";
		break;
			
		case "FindRat_1":
			AddMoneyToCharacter(pchar, makeint(pchar.questTemp.Slavetrader.iSlaveMoney));
			dialog.text = "You always can trust in my word, " + pchar.name + ". I have never given you any reason to doubt me. Partners must be honest with each other, that's the key of business\nLet's talk about Indian artifacts now. Show me what you have, don't make such collector like myself waiting.";
			link.l1 = "Hm... Take a look.";
			link.l1.go = "FindRat_2";
		break;
			
		case "FindRat_2":
			if (CheckCharacterItem(pchar, "jewelry30"))
			{
				dialog.text = "Yes! Excellent! A golden ritual knife! It is a rare thing. I've always wanted to have something like that in my collection. I offer you 30 000 for it or an amulet of 'Ehecatl' in exchange. I've got two of them anyway.";
				link.l1 = "I'd take money.";
				link.l1.go = "BG_money";
				link.l2 = "I'd take an amulet of 'Ehecatl' in exchange.";
				link.l2.go = "BG_change";
				link.l3 = "I'd better keep this knife with me.";
				link.l3.go = "BG_no";
			}
			else
			{
				dialog.text = "Let's see.. Unfortunately, you have nothing interesting for me.";
				link.l1 = "Whatever you say.";
				link.l1.go = "BG_PF";
			}
		break;
			
		case "BG_money":
			dialog.text = "Splendid. Take your 30 000 and this Indian knife is mine now.";
			link.l1 = "Good. And if that's all in what are you interested...";
			link.l1.go = "BG_PF";
			AddMoneyToCharacter(pchar, 30000);
			Log_Info("You've given a golden knife");
			PlaySound("interface\important_item.wav");
			RemoveItems(PChar, "jewelry30", 1);
		break;
			
		case "BG_change":
			dialog.text = "Splendid! Here is your amulet and this Indian knife is mine now.";
			link.l1 = "Good. And if that's all in what are you interested...";
			link.l1.go = "BG_PF";
			Log_Info("You've given a golden knife");
			Log_Info("You've received an amulet of 'Ehecatl'");
			PlaySound("interface\important_item.wav");
			RemoveItems(PChar, "jewelry30", 1);
			TakeNItems(pchar, "obereg_9", 1);
		break;
			
		case "BG_no":
			dialog.text = "Whatever. But it's such a pity anyway...";
			link.l1 = "Good. And if that's all in what are you interested...";
			link.l1.go = "BG_PF";
		break;
			
		case "BG_PF":
			dialog.text = "Wait! Let me take a look again...";
			link.l1 = "Sure. Come take a look and choose what you want.";
			link.l1.go = "PF_check";
		break;
			
		case "PF_check":
			if (CheckCharacterItem(pchar, "mineral31"))
			{
				dialog.text = "This! And I didn't notice it at first. I am interested in this bone with a ring made of copper. Such an interesting thing I'd tell you... I can pay you 20 000 pesos or give you an amulet of 'Cimaruta' in exchange.";
				link.l1 = "I'd take money.";
				link.l1.go = "PF_money";
				link.l2 = "I'd take an amulet of 'Cimaruta' in exchange.";
				link.l2.go = "PF_change";
				link.l3 = "I'd keep this artifact with me.";
			link.l3.go = "PF_no";
			}
			else
			{
				dialog.text = "No... You don't have things of my interest.";
				link.l1 = "Whatever!";
				link.l1.go = "FindRat_3";
			}
		break;
			
		case "PF_money":
			dialog.text = "Excellent! Here are your 20 000 pesos and this bone is mine now.";
			link.l1 = "Nice. I feel good for our deal.";
			link.l1.go = "FindRat_3";
			AddMoneyToCharacter(pchar, 20000);
			Log_Info("You've given a magic bone");
			PlaySound("interface\important_item.wav");
			RemoveItems(PChar, "mineral31", 1);
		break;
			
		case "PF_change":
			dialog.text = "Splendid! Here is your amulet and this bone is mine now.";
			link.l1 = "Nice. I feel good for our deal.";
			link.l1.go = "FindRat_3";
			Log_Info("You've given a magic bone");
			Log_Info("I've received an amulet of 'Cimaruta'");
			PlaySound("interface\important_item.wav");
			RemoveItems(PChar, "mineral31", 1);
			TakeNItems(pchar, "amulet_11", 1);
		break;
			
		case "PF_no":
			dialog.text = "Whatever. But it's such a pity anyway...";
			link.l1 = "I need that bone for myself, I am so sorry.";
			link.l1.go = "FindRat_3";
		break;
			
		case "FindRat_3":
			dialog.text = "Well... by boarding the galleon, oh I am sorry, the battleship you have saved me. I really appreciate our partnership, " + pchar.name + ". You are my best agent.";
			link.l1 = "I am flattered. You are quite overestimating my accomplishments...";
			link.l1.go = "FindRat_4";
		break;
			
		case "FindRat_4":
			dialog.text = "I am completely serious. And I am going to ask you to accomplish another mission because of your extraordinary skills and because I trust you.";
			link.l1 = "Heh! Surprising! I am listening. Where is another galleon with salves?";
			link.l1.go = "FindRat_5";
		break;
			
		case "FindRat_5":
			dialog.text = "The matter is not about slaves this time. Surprised? I'll pay you well for the mission... Very well.";
			link.l1 = "Get straight to business.";
			link.l1.go = "FindRat_6";
		break;
			
		case "FindRat_6":
			dialog.text = "This business is connected to the recent events you also had been a part of… So, as you may know, I do a quite illegal business - a slave trading. You may also know that I hire privateers like you for all sorts of assignments\nOne of my men betrayed me not long ago for unknown reasons. He gathered proofs and made a report to the authorities. You had a pleasure to see the consequences with your very own eyes. A ship with soldiers had arrived here... you know the rest\nIt took quite an effort from me to settle the situation. As you understand, I can not let this treachery to go unanswered. Besides, I can not live and work peacefully knowing that the rat is still alive. I have sent bounty hunters but there is no result yet\nI ask you to personally deal with this matter. All the more so, his actions affected you too.";
			link.l1 = "Hm... this bastard must be hanged on an yardarm! Tell me more about him and my payment for the job of course.";
			link.l1.go = "FindRat_7";
		break;
			
		case "FindRat_7":
			dialog.text = "Don't worry about that. I will pay a great deal for his elimination and I am talking not just about the money. I won't spare the best items of my collections. Let's talk about the man. His name is Francois Gontier\nHe is aware about my hunt, so he sold his frigate in order to hide his trails. My colleagues told me that he was seen in Panama. I believe that you should start your searches from there.";
			link.l1 = "Well, I am on my way then.";
			link.l1.go = "FindRat_8";
		break;
			
		case "FindRat_8":
			dialog.text = "I wish you luck then. Know that this Gontier is a very experienced sailor and he has a crew of the reckless cut-throats. He has got nothing to loose so he'll be fighting in a very desperate way.";
			link.l1 = "Not got scared of people like him but I'll consider what you've said. Farewell and be sure that I will get him even in the hell.";
			link.l1.go = "exit";
			pchar.questTemp.Slavetrader.ShipName = GenerateRandomNameToShip(SPAIN);
			AddQuestRecord("Slavetrader", "21");
			AddQuestUserData("Slavetrader", "sName", GetFullName(npchar));
			pchar.questTemp.Slavetrader = "FindRatPanama";
		break;
			
		case "Wincorvette":
			dialog.text = "Splendid! Now he can write his reports to the jellyfish. No one dares to mess with me. My thanks to you, " + pchar.name + ", you are an indispensable man.";
			link.l1 = "Thank you, " + npchar.name + ", for such a positive rating of my actions. What about my payment?";
			link.l1.go = "Wincorvette_1";
		break;
			
		case "Wincorvette_1":
			dialog.text = "Sure. I'd pay the right price for such a difficult job. First, I present you this excellent spyglass.";
			link.l1 = "Wow, such a gift!";
			link.l1.go = "Wincorvette_2";
		break;
			
		case "Wincorvette_2":
			dialog.text = "Besides, here are 100 000 pesos as your primary payment and 50 000 as a compensation for your own costs.";
			link.l1 = "Thanks, " + npchar.name + ". I say it again that it's a pleasure to deal with you.";
			link.l1.go = "Wincorvette_3";
			Log_Info("You've received an excellent spyglass");
			PlaySound("interface\important_item.wav");
			TakeNItems(pchar, "spyglass4", 1);
		break;
			
		case "Wincorvette_3":
			dialog.text = "I will be waiting for you in a month just as always. It's a very big deal on the row and you'll need a well equipped squadron. I ask to understand that and prepare yourself well. If my plan works, we will be reach.";
			link.l1 = "Good," + npchar.name + ". I'll come here when I'd be prepared.";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, 150000);
			AddQuestRecord("Slavetrader", "21_13");
			AddQuestUserData("Slavetrader", "sName", GetFullName(npchar));
			SaveCurrentQuestDateParam("pchar.questTemp.Slavetrader_wait_5");
			pchar.questTemp.Slavetrader = "wait_5";
		break;
			
		case "Lostcorvette":
			dialog.text = "Pity, what a shame... Well, don't feel upset, you are not the first man that scum fooled. I will nail him one day anyway\nAs for you, come and see me in a month. This is big, so gather a well equipped and armed squadron. Please, be serious about it and do you your best to prepare. If my plan works, we will be reach.";
			link.l1 = "Good, " + npchar.name + ". I'll come here when I'd be prepared.";
			link.l1.go = "exit";
			AddQuestRecord("Slavetrader", "21_14");
			AddQuestUserData("Slavetrader", "sSex", GetSexPhrase("",""));
			AddQuestUserData("Slavetrader", "sName", GetFullName(npchar));
			SaveCurrentQuestDateParam("pchar.questTemp.Slavetrader_wait_5");
			pchar.questTemp.Slavetrader = "wait_5";
		break;
		
		case "Havana_fort":
			dialog.text = "You are just in time, " + pchar.name + "! I was close to start worrying, I was going to send a man to find you\nLet's get started! Your mission is really big and risky now, but the reward is adequate. You will receive at least a million pesos after the job is done.";
			link.l1 = "Now you are talking! I am listening, " + npchar.name + ".";
			link.l1.go = "Havana_fort_1";
		break;
		
		case "Havana_fort_1":
			dialog.text = "The enslaved Indians were being moved by a small bunches to Havana from over the whole Main, also a few galleons came from Africa and were unloaded. By now there are almost a five thousand slaves behind the high walls of Havana's fort.";
			link.l1 = "I've got a feeling that the deal is about storming the Havana.";
			link.l1.go = "Havana_fort_2";
		break;
		
		case "Havana_fort_2":
			dialog.text = "You've got a right feeling, " + pchar.name + ". That is exactly what I want to ask you to do. You and only you. I doubt, that anyone else of my agents is capable of doing this\nI believe that you are in?";
			link.l1 = "To be honest, " + npchar.name + ", I am a bit dumbfounded now. I had no idea that your activity is so... large-scaled. Sure, I am in. " + RandSwear() + "";
			link.l1.go = "Havana_fort_3";
			link.l2 = "You know what, " + npchar.name + ", this is going too far. I had enough of that surprises of yours. Next time your greed will want me to declare a war to Spain. If you really need that slaves then storm Havana by yourself.";
			link.l2.go = "Havana_fort_not";
		break;
		
		case "Havana_fort_not":
			dialog.text = "Didn't expect that from you... Damn, what do I suppose to tell my customer? Fine. It's your call and I have to find a new partner. Farewell, " + pchar.name + ". And I will not use your services in the future. Remember that you have dropped the deal which could make your progenies reach to the seventh generation.";
			link.l1 = "You can't get all money in the world. You bite off more than you can chew. Farewell, " + npchar.name + ".";
			link.l1.go = "exit";
			AddQuestRecord("Slavetrader", "8");
			AddQuestUserData("Slavetrader", "sSex", GetSexPhrase("",""));
			CloseQuestHeader("Slavetrader");
			pchar.questTemp.Slavetrader = "End_quest";
		break;
		
		case "Havana_fort_3":
			dialog.text = "I knew that you'd agree. Now, hear the details. Havana's fort has always been a hard target but it is even harder now\nTwo ships of the line are guarding the shores of the island and you must deal with them first before you storm the fort…";
			link.l1 = "I see. It won't be the first time I fight battleships. How much time do I have?";
			link.l1.go = "Havana_fort_4";
		break;
		
		case "Havana_fort_4":
			dialog.text = "Not much. Three weeks not more and after that the slaves will be moved to Spanish outposts of Cuba. You have to hurry. ";
			link.l1 = "Let's don't waste our time than. I am on my way!";
			link.l1.go = "Havana_fort_5";
		break;
		
		case "Havana_fort_5":
			dialog.text = "One moment!" + pchar.name + ", you and I never had any misunderstandings and disagreements. Nevertheless, I want you to know what is going on here. I count on you, and the client counts on me\mWe have invested a lot of effort and money in this operation. Every single slave, all five thousands must be delivered to me\nOtherwise, we will take very radical measures against you. No offence, this only a notification. ";
			link.l1 = "Don't worry, " + npchar.name + ", I understand what business is. Farewell.";
			link.l1.go = "exit";
			AddQuestRecord("Slavetrader", "24");
			AddQuestUserData("Slavetrader", "sSex", GetSexPhrase("",""));
			AddQuestUserData("Slavetrader", "sName", GetFullName(npchar));
			pchar.quest.Slavetrader_HavanaAttack.win_condition.l1 = "location";
            pchar.quest.Slavetrader_HavanaAttack.win_condition.l1.location = "Cuba2";//отправляем в локацию
            pchar.quest.Slavetrader_HavanaAttack.function = "Slavetrader_CreateLineShips";//создание линейных кораблей
			SetFunctionTimerCondition("Slavetrader_HavanaOver", 0, 0, 20, false);	//таймер
			characters[GetCharacterIndex("Havana_Mayor")].dialog.captureNode = "Slavetrader_HavanaAttack"; //капитулянтская нода мэра
			pchar.questTemp.Slavetrader = "wait1";
		break;
		
		case "Win_Havana_Fort":
			pchar.quest.Slavetrader_FiveTSlavesOver.over = "yes";
			amount = 5000 - GetSquadronGoods(Pchar, GOOD_SLAVES);
			sTemp = GetSquadronGoods(Pchar, GOOD_SLAVES);
			if (amount < 1)
			{
				dialog.text = "Well.. And what about the prize of your victory?";
				link.l1 = "I have " + sTemp + " slaves.";
				link.l1.go = "Havana_Fort_yes";
				break;
			}
			if (amount < 4500 && amount >= 1)
			{
				dialog.text = "Well, well. Did you forget what I said? You had to bring me here not less than a five thousand slaves and you've got " + sTemp + ". Why is that?";
				link.l1 = "Hm.. Part of them haven't survived the road from Havana...";
				link.l1.go = "Havana_Fort_no";
				break;
			}
			dialog.text = "Well-well... Do you want to cheat on me? Did you forget what I said? Where are my slaves? I ask you, where are they?!";
			link.l1 = "Hm.. Well, you see...";
			link.l1.go = "Havana_Fort_no";
		break;
		
		case "Havana_Fort_no":
			dialog.text = "Fine. I don't need your explanations. We had a deal and I give you one week to get not less than a five thousand slaves. You would have a lot of problems otherwise.";
			link.l1 = "Fine, fine, just relax, I'll get them for you.";
			link.l1.go = "exit";
			AddQuestRecord("Slavetrader", "29");
			SetFunctionTimerCondition("Slavetrader_HavanaSeekOver", 0, 0, 7, false);
			pchar.questTemp.Slavetrader = "Havana_seekslaves";
		break;
		
		case "Havana_Fort_yes":
			dialog.text = "Splendid! You have accomplished my task just as always. I am very pleased by you.";
			link.l1 = "So am I... But I would be even more pleased when I'll receive my money for the cargo.";
			link.l1.go = "Havana_Fort_yes_1";
		break;
		
		case "Havana_Fort_yesA":
		dialog.text = "I am very glad for that. You were late but you've accomplished my task in the most excellent way.";
			link.l1 = "And now I want to get money for the cargo.";
			link.l1.go = "Havana_Fort_yes_1";
			pchar.quest.Slavetrader_HavanaSeekOver.over = "yes";
		break;
		
		case "Havana_Fort_yes_1":
			sTemp = GetSquadronGoods(Pchar, GOOD_SLAVES);
			iSlaveMoney = makeint(sTemp)*200;
			dialog.text = "Sure. I am going to sell the slaves to my client, he'll play and you'll get your coins. Just like the last time. Let's see, you've brought here " + sTemp + " slave. The sum is " + FindRussianMoneyString(iSlaveMoney) + ". Come here for the payment in a week.";
			link.l1 = "Fine, " + npchar.name + ", we have a deal. I'll be here in a week. But be careful...";
			link.l1.go = "Havana_Fort_yes_2";
			RemoveCharacterGoods(Pchar, GOOD_SLAVES, sTemp);
		break;
		
		case "Havana_Fort_yes_2":
			dialog.text = "" + pchar.name + ", please, don't. We are partners and there is no room for cheating and distrust between us. I promised you a lot of coins and you've got them. I promised you interesting tasks and you've got them too. I have always been compensating your costs even in the darkest days for my business. Haven't I ever keep my word?";
			link.l1 = "Hm.. No.";
			link.l1.go = "Havana_Fort_yes_3";
		break;
		
		case "Havana_Fort_yes_3":
			dialog.text = "See now..." + pchar.name + ", you are the best agent of mine and I am counting to do business with you in the future. ";
			link.l1 = "Fine, " + npchar.name + ". But you have to understand me as well - a million pesos is a huge sum.";
			link.l1.go = "Havana_Fort_yes_4";
		break;
		
		case "Havana_Fort_yes_4":
			dialog.text = "I understand you very well but I have to sell that slaves at first and only then I'll receive money.";
			link.l1 = "Fine. I think we understood each other.";
			link.l1.go = "Havana_Fort_yes_5";
		break;
		
		case "Havana_Fort_yes_5":
			dialog.text = "Splendid. See you in a week. And now I have to prepare the trade with my client.";
			link.l1 = "I won't bother you then. See you in a week, " + npchar.name + ".";
			link.l1.go = "exit";
			pchar.questTemp.Slavetrader.Name = npchar.name;
			AddQuestRecord("Slavetrader", "32");
			SaveCurrentQuestDateParam("pchar.questTemp.Slavetrader_wait_6");
			SetFunctionTimerCondition("Slavetrader_UsurerEscape", 0, 0, 8, false);
			pchar.questTemp.Slavetrader = "wait_6";
			pchar.questTemp.Slavetrader.Cityname = npchar.city +"_town";
			LocatorReloadEnterDisable(npchar.city +"_town", "reload8_back", true);//чтобы не ходил неделю сюда вообще
		break;

		case "Usurer_Escape":
			dialog.text = "What am I doing here? Well... it's my bank. I bought it two days ago. You are my first client and I can offer you a very tempting credit terms...";
			link.l1 = "Fuck that credits! Where is " + pchar.questTemp.Slavetrader.Name + "?";
			link.l1.go = "Usurer_Escape_1";
		break;

		case "Usurer_Escape_1":
			dialog.text = "Calm down, please! He ran away long time ago.";
			link.l1 = "How?";
			link.l1.go = "Usurer_Escape_2";
		break;
		
		case "Usurer_Escape_2":
			dialog.text = "Don't you know? He disappeared a week ago. Turned out that he has taken all his client's investments. They say that even the governor was suffered. This house was left and I bought it from the colony.";
			link.l1 = "Disappeared? How?";
			link.l1.go = "Usurer_Escape_3";
		break;
		
		case "Usurer_Escape_3":
			dialog.text = "I've heard that he has run away from our colony... I take it that he owes you too. A lot?";
			link.l1 = "More than a million! But I'll get this rat anyway! Where has he gone? Name of his ship?";
			link.l1.go = "Usurer_Escape_4";
		break;
		
		case "Usurer_Escape_4":
			dialog.text = "Nobody is aware. Seriously. He has just gone. The ship named 'Mauritius' or 'Maurdius' had been sailing away that day, perhaps, he used it to escape.";
			link.l1 = "Fuck! And I've trusted that bastard! He had a smell of traitor! And I was foolish enough to believe that we are true partners! But I will make him regret one day… Fine," + npchar.name + ", I apologize for my behavior… Farewell.";
			link.l1.go = "Usurer_Escape_5";
		break;
		
		case "Usurer_Escape_5":
			string sColony;
			sColony = npchar.city;
			SetNull2Deposit(sColony);
			dialog.text = "It is alright. I understand. If you'll need some money or you'll want to invest, I am always at your service.";
			link.l1 = "Thanks. But I'd better keep my money with myself. See you.";
			link.l1.go = "exit";
			AddQuestRecord("Slavetrader", "33");
			AddQuestUserData("Slavetrader", "sSex", GetSexPhrase("",""));
			CloseQuestHeader("Slavetrader");
			pchar.questTemp.Slavetrader = "wait1";
			LAi_LocationDisableOfficersGen(&Locations[FindLocation(pchar.location)], false); // разблокируем вход офицеров 2015
		break;
	//<--работорговец	

	//--> семейная реликвия
		case "Noblelombard":
			dialog.text = "Oh really? It seems that he doesn't want to talk to me by himself.... Fine, let's discuss the matter with you. "+pchar.GenQuest.Noblelombard.Name+" owes me "+FindRussianMoneyString(sti(pchar.GenQuest.Noblelombard.Summ))+": "+FindRussianMoneyString(sti(pchar.GenQuest.Noblelombard.Money))+" and also my interest - "+FindRussianMoneyString(sti(pchar.GenQuest.Noblelombard.Percent))+" for three month. If I don't see money in the nearest day then I will sell his relic and I don't care about its value to him. Business is a business.";
			if(sti(pchar.money) >= sti(pchar.GenQuest.Noblelombard.Summ))
			{
				link.l1 = "Splendid! In that case I am going to pay you the whole sum with all of the interest immediately - "+FindRussianMoneyString(sti(pchar.GenQuest.Noblelombard.Summ))+". He will take his relic by himself. Here is your money.";
				link.l1.go = "Noblelombard_1";
			}
			if(sti(pchar.money) >= sti(pchar.GenQuest.Noblelombard.Percent)*2)
			{
				link.l2 = "My client will have money in a three month. Let's make a deal, I'll pay you the interest for the last three months and for the next three months."+FindRussianMoneyString(sti(pchar.GenQuest.Noblelombard.Percent)*2)+". And the debt itself will be paid to you later.";
				link.l2.go = "Noblelombard_2";
			}
			if(sti(pchar.money) >= sti(pchar.GenQuest.Noblelombard.Percent))
			{
				link.l3 = "My client will have money in a three months. How about I'll pay you the interest for last three months and you'll wait until my client has enough money?";
				link.l3.go = "Noblelombard_3";
			}
			link.l4 = "This rarity costs a fortune! It looks like my client has to pay for it by himself.";
			link.l4.go = "Noblelombard_4";
			npchar.quest.noblelombard = "true";
		break;
		
		case "Noblelombard_1":
			dialog.text = "Excellent! It all turned well, I got my money and "+pchar.GenQuest.Noblelombard.Name+" will get back the relic.";
			link.l1 = "Nice doing business with you, "+npchar.name+"! Farewell now.";
			link.l1.go = "exit";
			pchar.GenQuest.Noblelombard.Regard = sti(pchar.GenQuest.Noblelombard.Summ)*2;
			AddMoneyToCharacter(pchar, -sti(pchar.GenQuest.Noblelombard.Summ));
			pchar.GenQuest.Noblelombard = "full";
			AddCharacterExpToSkill(pchar, "Leadership", 150);
		break;
		
		case "Noblelombard_2":
			if(sti(pchar.GenQuest.Noblelombard.Chance) < 7)
			{
				dialog.text = "Hm.. Fine. This works for me. But if "+pchar.GenQuest.Noblelombard.Name+" doesn't find money in three months then I won't make a delay again. Make him know that.";
				link.l1 = "I will! I am glad that we had a deal. Farewell now.";
				link.l1.go = "exit";
				pchar.GenQuest.Noblelombard.Regard = sti(pchar.GenQuest.Noblelombard.Percent)*4;
				AddMoneyToCharacter(pchar, -sti(pchar.GenQuest.Noblelombard.Percent)*2);
				pchar.GenQuest.Noblelombard = "maxpercent";
				AddCharacterExpToSkill(pchar, "Leadership", 50);
				AddCharacterExpToSkill(pchar, "Fortune", 70);
			}
			else
			{
				dialog.text = "No. It won't work. I need the whole sum and before the sunset. Make your 'client' know that. I have nothing more to tell you.";
				link.l1 = "Hm... fine. Too bad that you don't want to compromise.";
				link.l1.go = "Noblelombard_4";
				AddCharacterExpToSkill(pchar, "Fortune", 30);
			}
		break;
		
		case "Noblelombard_3":
			if(sti(pchar.GenQuest.Noblelombard.Chance) < 3)
			{
				dialog.text = "Hm.. Fine. I accept it just because of my respect to your client. But if "+pchar.GenQuest.Noblelombard.Name+" doesn't find money in three months then I won't make a delay again. Make him know that.";
				link.l1 = "I will! I am glad that we had a deal. Farewell now.";
				link.l1.go = "exit";
				pchar.GenQuest.Noblelombard.Regard = sti(pchar.GenQuest.Noblelombard.Percent)*2;
				AddMoneyToCharacter(pchar, -sti(pchar.GenQuest.Noblelombard.Percent));
				pchar.GenQuest.Noblelombard = "minpercent";
				AddCharacterExpToSkill(pchar, "Leadership", 50);
				AddCharacterExpToSkill(pchar, "Fortune", 150);
			}
			else
			{
				dialog.text = "No. It won't work. I need the whole sum and before the sunset. Make your 'client' know that. I have nothing more to tell you.";
				link.l1 = "Hm... fine. Too bad that you don't want to compromise.";
				link.l1.go = "Noblelombard_4";
				AddCharacterExpToSkill(pchar, "Fortune", 60);
			}
		break;
		
		case "Noblelombard_4":
			DialogExit();
			pchar.GenQuest.Noblelombard = "fail";
		break;
		
		case "Noblelombard_5":
			if(sti(pchar.GenQuest.Noblelombard.Chance) == 9)
			{
				dialog.text = "You don't say so! "+pchar.GenQuest.Noblelombard.Name+" hasn't opened a deposit for your name. He is not even in our colony - sailed away to the Europe. I tell you that I've never seen such a dishonest man. He wanted to cheat on me but failed - I have some my own tricks...";
				link.l1 = "Bastard! He has given me his word....";
				link.l1.go = "Noblelombard_6";
			}
			else
			{	// Addon-2016 Jason уменьшаем раздачу дублонов
				dialog.text = "Correct. "+pchar.GenQuest.Noblelombard.Name+" has made a deposit for your name. Please, take it...";
				link.l1 = "Splendid! Farewell, "+npchar.name+".";
				link.l1.go = "Noblelombard_9";
			}
		break;
		
		case "Noblelombard_6":
			dialog.text = "There is no such a thing for people like "+pchar.GenQuest.Noblelombard.Name+" because they don't have an honor and a conscience. I take it that he has cheated on you?";
			link.l1 = "He has, I suppose. Whatever, "+npchar.name+", I am not going to stay here for long either and Europe is small... Maybe, we will meet one day. Farewell!";
			link.l1.go = "Noblelombard_7";
		break;
		
		case "Noblelombard_7":
			DialogExit();
			AddQuestRecord("Noblelombard", "6");
			AddQuestUserData("Noblelombard", "sName", pchar.GenQuest.Noblelombard.Name);
			CloseQuestHeader("Noblelombard");
			DeleteAttribute(Pchar, "GenQuest.Noblelombard");
			DeleteAttribute(NPchar, "quest.noblelombard");
		break;
		
		case "Noblelombard_9":
			DialogExit();
			iTemp = sti(pchar.GenQuest.Noblelombard.Regard); // Addon-2016 Jason уменьшаем раздачу дублонов
			AddMoneyToCharacter(pchar, iTemp);
			PlaySound("interface\important_item.wav");
			AddQuestRecord("Noblelombard", "7");
			AddQuestUserData("Noblelombard", "sName", pchar.GenQuest.Noblelombard.Name);
			CloseQuestHeader("Noblelombard");
			DeleteAttribute(Pchar, "GenQuest.Noblelombard");
			DeleteAttribute(NPchar, "quest.noblelombard");
		break;
//<-- семейная реликвия

		// Бремя гасконца
		case "sharlie_credit":
			dialog.text = "Monsieur, I don't know you. I lend money only to the local citizens or to the captains. Pardon me...";
			link.l1 = "I see. Too bad though.";
			link.l1.go = "exit";
		break;
		// Бремя гасконца
		
		// Addon-2016 Jason, французские миниквесты (ФМК)
		// ФМК-Гваделупа
		case "FMQG_x":
			dialog.text = "Wh-what... What do you mean?";
			link.l1 = "You are a fucking rat! Now listen to me really carefully: I am not that stupid. Pinette had written two copies of the letter. I gave you one of them, the second is in a possession of my trusted agent. If anything happens to me - my guy will deliver it right to the hands of the governor...";
			link.l1.go = "FMQG_x1";
		break;
		
		case "FMQG_x1":
			dialog.text = "";
			link.l1 = "So I suggest you praying for my good health in church on every morning sermon instead of sending assassins for my life. One last warning: make a move against me and you are fucked up. Got it? Good. Take a deep breath and keep counting your doubloons.";
			link.l1.go = "FMQG_x2";
		break;
		
		case "FMQG_x2":
			DialogExit();
			pchar.questTemp.FMQG = "end";
			FMQ_Count();
			AddQuestRecord("FMQ_Guadeloupe", "27");
			CloseQuestHeader("FMQ_Guadeloupe");
			ChangeCharacterComplexReputation(pchar, "nobility", -2);
			ChangeCharacterComplexReputation(pchar, "authority", 3);
			AddCharacterExpToSkill(pchar, "Sneak", 400);
			AddCharacterExpToSkill(pchar, "Sailing", 200);
			bQuestDisableMapEnter = false;//открыть карту
			DeleteAttribute(pchar, "GenQuest.MapClosedNoBattle");
		break;
	}	
}

int findCitizenMan(ref NPChar, bool bCity)
{
    ref ch;
	int n, nation;
    int storeArray[MAX_COLONIES];
    int howStore = 0;

	if (bCity && sti(Pchar.Ship.Type) == SHIP_NOTUSED)
	{
		ch = GetCharacter(NPC_GenerateCharacter("LoanFindingMan", "citiz_"+(rand(9)+11), "man", "man", 10, sti(npchar.nation), -1, false, "citizen"));
		ch.dialog.filename = "Common_citizen.c";
		ch.city = npchar.city;
		ch.RebirthPhantom = true; 
		LAi_NoRebirthDisable(ch);
		LAi_SetCitizenType(ch);
		LAi_group_MoveCharacter(ch, GetNationNameByType(sti(npchar.nation)) + "_citizens");
		PlaceCharacter(ch, "goto", npchar.city + "_town");
	}
	else
	{		
		for(n=0; n<MAX_COLONIES; n++)
		{			
			nation = GetNationRelation(sti(npchar.nation), sti(colonies[n].nation));	
			if (nation != RELATION_ENEMY && colonies[n].nation != "none")
			{           
				storeArray[howStore] = n;
				howStore++;
			}
		}
		if (howStore == 0) return -1; 
		nation = storeArray[cRand(howStore-1)];
		ch = GetCharacter(NPC_GenerateCharacter("LoanFindingMan", "citiz_"+(rand(9)+11), "man", "man", 10, sti(colonies[nation].nation), -1, false, "citizen"));
		ch.dialog.filename = "Common_citizen.c";
		ch.city = colonies[nation].id;
		ch.RebirthPhantom = true; 
		LAi_NoRebirthDisable(ch);
		LAi_SetCitizenType(ch);
		LAi_group_MoveCharacter(ch, GetNationNameByType(sti(colonies[nation].nation)) + "_citizens");
		PlaceCharacter(ch, "goto", colonies[nation].id + "_town");
	}
	return sti(ch.index);
}

int findChestMan(ref NPChar)
{
    ref ch;
	int n;
    int storeArray[TOTAL_CHARACTERS];
    int howStore = 0;
	string sTemp, sCity;

	for(n=2; n<MAX_CHARACTERS; n++)
	{
		makeref(ch,Characters[n]);
		sTemp = ch.id;
		if (CheckAttribute(ch, "City") && ch.id != "Jackman") sCity = ch.City;
		else continue;
		sTemp = strcut(sTemp, strlen(sCity)+1, strlen(sTemp)-1);
		// магазины
		if (sTemp == "trader")
		{
            if (NPChar.city == ch.city) continue;
            if (ch.location == "none") continue;
            storeArray[howStore] = n;
            howStore++;
		}
        // мэры
		if (sTemp == "Mayor")
		{
            if (NPChar.city == ch.city) continue;
            if (sti(ch.nation) == PIRATE) continue; // пираты не имеют реплик
            if (ch.location == "none") continue;
			if (ch.location != ch.Default) continue; //захвачанных мэров не надо
            storeArray[howStore] = n;
            howStore++;
		}
        // верфисты
		if (sTemp == "shipyarder")
		{
            if (NPChar.city == ch.city) continue;
            if (ch.location == "none") continue;
            storeArray[howStore] = n;
            howStore++;
		}
		// тавернщики
		if (sTemp == "tavernkeeper")
		{
            if (NPChar.city == ch.city) continue;
            if (ch.location == "none") continue;
            storeArray[howStore] = n;
            howStore++;
		}
	    // церковники
		if (sTemp == "Priest")
		{
            if (NPChar.city == ch.city) continue;
            if (ch.location == "none") continue;
            storeArray[howStore] = n;
            howStore++;
		}		
		// ростовщики
		if (sTemp == "usurer")
		{
            if (NPChar.city == ch.city) continue;
            if (ch.location == "none") continue;
            storeArray[howStore] = n;
            howStore++;
		}
		// начальники портов
		if (sTemp == "PortMan")
		{
            if (NPChar.city == ch.city) continue;
            if (ch.location == "none") continue;
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
        return storeArray[cRand(howStore-1)];
    }
}

// ugeen -> проверка, можем ли мы использовать дублоны в качестве вклада
bool CheckUseDublons(ref NPChar)
{
	int iTest 	= FindColony(NPChar.City); // город банка
	if(iTest == -1) return false;
	
	ref rColony = GetColonyByIndex(iTest);
	 	 
	bool bOk1 = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea); 
	bool bOk2 = (GetCharacterItem(pchar,"gold_dublon") > 10) || (CheckItemMyCabin("gold_dublon") > 10);
	
	if(sti(Pchar.Ship.Type) != SHIP_NOTUSED && bOk1 && bOk2) return true;

	return false;
}

void SlavetraderGalleonInWorld()
{
	//создаем галеон с рабами
	ref sld;
	string sName;
	sName = pchar.questTemp.Slavetrader.ShipName;
	sld = GetCharacter(NPC_GenerateCharacter("GaleonCap", "", "man", "man", 45, SPAIN, 20, true, "quest"));
	FantomMakeCoolSailor(sld, SHIP_LINESHIP, sName, CANNON_TYPE_CANNON_LBS36, 100, 100, 100);
	FantomMakeCoolFighter(sld, 45, 100, 100, "blade_21", "pistol5", "bullet", 100);
	sld.Ship.Mode = "war";	
	SetCaptanModelByEncType(sld, "war");
	DeleteAttribute(sld, "SinkTenPercent");
	DeleteAttribute(sld, "SaveItemsForDead");
	DeleteAttribute(sld, "DontClearDead");
	DeleteAttribute(sld, "AboardToFinalDeck");
	sld.AlwaysSandbankManeuver = true;
	sld.AnalizeShips = true;
	sld.DontRansackCaptain = true;
	sld.WatchFort = true;
	sld.AlwaysEnemy = true;
	SetCharacterPerk(sld, "StormProfessional");
	SetCharacterPerk(sld, "SwordplayProfessional");
	SetCharacterPerk(sld, "AdvancedDefense");
	SetCharacterPerk(sld, "CriticalHit");
	SetCharacterPerk(sld, "MusketsShoot");
	SetCharacterPerk(sld, "Sliding");
	SetCharacterPerk(sld, "Tireless");
	SetCharacterPerk(sld, "HardHitter");
	SetCharacterPerk(sld, "GunProfessional");
	SetCharacterGoods(sld, GOOD_SLAVES, 3000 + rand(200));//положить в трюм рабов
	sld.ship.Crew.Morale = 100;
	ChangeCrewExp(sld, "Sailors", 100);
	ChangeCrewExp(sld, "Cannoners", 100);
	ChangeCrewExp(sld, "Soldiers", 100);
	//в морскую группу кэпа
	string sGroup = "SlaveGalleon";
	Group_FindOrCreateGroup(sGroup);
	Group_SetTaskAttackInMap(sGroup, PLAYER_GROUP);
	Group_LockTask(sGroup);
	Group_AddCharacter(sGroup, sld.id);
	Group_SetGroupCommander(sGroup, sld.id);
	SetRandGeraldSail(sld, sti(sld.Nation)); 
	pchar.quest.SlaveHalleon_AfterBattle.win_condition.l1 = "Group_Death";
	pchar.quest.SlaveHalleon_AfterBattle.win_condition.l1.group = "SlaveGalleon";
	pchar.quest.SlaveHalleon_AfterBattle.function = "Slavetrader_SlaveHalleon_AfterBattle";
	sld.city = pchar.questTemp.Slavetrader.Island; //определим колонию, из бухты которой выйдет
	sld.cityShore = pchar.questTemp.Slavetrader.Island.Shore;
	sld.quest.targetCity = "Santiago"; //определим колонию, в бухту которой он придет
	sld.quest.targetShore = GetIslandRandomShoreId(GetArealByCityName(sld.quest.targetCity));
	//Log_TestInfo("Captain of the galleon sailed away from " + sld.city + "and heading to " + sld.quest.targetShore);
	//==> на карту
	sld.mapEnc.type = "trade";
	//выбор типа кораблика на карте
	sld.mapEnc.worldMapShip = "quest_ship";
	sld.mapEnc.Name = "Galleon '" + sName + " '";
	int daysQty = 20; //дней доехать даем с запасом
	Map_CreateTrader(sld.cityShore, sld.quest.targetShore, sld.id, daysQty);//вот он, сам запуск энкаунтера
}		