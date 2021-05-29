#include "DIALOGS\russian\Rumours\Common_rumours.c"  //homo 25/06/06
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag, arCapBase, arCapLocal;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	// доп повека
	if (!CheckAttribute(NPChar, "Portman")) NPChar.Portman = 0;
	if (!CheckAttribute(NPChar, "PortManPrice")) NPChar.PortManPrice = (0.06 + frnd()*0.1);

    // вызов диалога по городам -->
    NPChar.FileDialog2 = "DIALOGS\" + LanguageGetLanguage() + "\PortMan\" + NPChar.City + "_PortMan.c";
    if (LoadSegment(NPChar.FileDialog2))
	{
        ProcessCommonDialog(NPChar, Link, NextDiag);
		UnloadSegment(NPChar.FileDialog2);
	}
    // вызов диалога по городам <--
	ProcessCommonDialogRumors(NPChar, Link, NextDiag);//homo 25/06/06

    int i, cn, iTemp;
    ref chref;
	ref rRealShip;
    string attrL, sTitle, sCapitainId, s1;
	string sColony;
    
	String sLastSpeakDate = LastSpeakDate();
	
	// Warship 25.07.09 Генер "Сгоревшее судно". Даты отказа ГГ - если отказал, то предложит снова только на след сутки
	if(CheckAttribute(NPChar, "Quest.BurntShip.LastQuestDate") && NPChar.Quest.BurntShip.LastQuestDate != sLastSpeakDate)
	{
		DeleteAttribute(NPChar, "Quest.BurntShip");
	}
    
    bool ok;
    int iTest = FindColony(NPChar.City); // город магазина
    ref rColony;
    string sFrom_sea = "";
	npchar.quest.qty = CheckCapitainsList(npchar); //для списка кэпов

	if (iTest != -1)
	{
		rColony = GetColonyByIndex(iTest);
		sFrom_sea = rColony.from_sea;
	}
	
	attrL = Dialog.CurrentNode;
	
	if(HasSubStr(attrL, "ShipStockManBack_"))
 	{
        i = findsubstr(attrL, "_" , 0);
	 	NPChar.ShipToStoreIdx = strcut(attrL, i+1, strlen(attrL)-1); // индех в конце
 	    Dialog.CurrentNode = "ShipStockManBack";
 	}
    
	if(HasSubStr(attrL, "BurntShip19_"))
	{
		i = findsubstr(attrL, "_" , 0);
	 	NPChar.Quest.BurntShip.ShipCompanionIndex = strcut(attrL, i + 1, strlen(attrL) - 1); // индех в конце
 	    Dialog.CurrentNode = "BurntShip19";
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
			NextDiag.TempNode = "First time";
			if (LAi_grp_playeralarm > 0)
			{
       			dialog.text = NPCharRepPhrase(pchar, 
					LinkRandPhrase("Alarm is raised in the town, and everyone is looking for you. If I were you, I wouldn't stay there.", "All the city guards are scouring the town looking for you. I am not a fool and I will not talk to you!", "Run, "+ GetSexPhrase("buddy","lass") +", before the soldiers turned you into a sieve..."), 
					LinkRandPhrase("What do you need, "+ GetSexPhrase("scoundrel","stinker") +"?! The city guards have already hit your scent, you won't get far filthy pirate!", "murderer, leave my house at once! Guards!!!", "I am not afraid of you, "+ GetSexPhrase("scoundrel","rat") +"! Soon you will be hanged in our fort, you won't get far..."));
				link.l1 = NPCharRepPhrase(pchar,
					RandPhraseSimple("Heh, an alarm is never a problem for me...", "They will never get me."), 
					RandPhraseSimple("Shut your mouth, " + GetWorkTypeOfMan(npchar, "") + ", and I will not rip your filthy tongue!", "Heh, " + GetWorkTypeOfMan(npchar, "") + ", and all there - catch pirates! That's what I tell you, buddy: be quiet and you will live..."));
				link.l1.go = "fight";
				break;
			}
			//Jason, фрахт
			if (CheckAttribute(pchar, "questTemp.WPU"))
			{
				if (pchar.questTemp.WPU.Fraht == "fail" && pchar.questTemp.WPU.Fraht.Nation == npchar.nation)
				{
					dialog.text = "Oh, I know, who you are. You contracted to deliver the cargo, but you stole it! Guards, guards!";
					Link.l1 = "Aaargh!";
					Link.l1.go = "exit";
					LAi_group_Attack(NPChar, Pchar);
					break;
				}
			}
			//фрахт
			//--> Jason Бремя гасконца
			if (CheckAttribute(pchar, "questTemp.Sharlie.Lock"))
			{
				dialog.text = "What can I do for you, monsieur?";
				Link.l1 = "I have business with you...";
				Link.l1.go = "quests";
				Link.l2 = "I am sorry, but I have to go.";
				Link.l2.go = "exit";
				NPChar.quest.meeting = "1"; // patch-6
				break;
			}			
			//<-- Бремя гасконца
			if(NPChar.quest.meeting == "0")
			{
				NPChar.quest.meeting = "1";
				dialog.text = "Greetings, " + GetAddress_Form(NPChar) + ". I don't think we've met before. I am "  + GetFullName(npchar)+ " - the harbor master.";
				Link.l1 = "Hello, " + GetFullName(NPChar) + ". I am " + GetFullName(PChar) + ", captain of ship '" + PChar.ship.name + "'.";
			}
			else
			{
				dialog.text = LinkRandPhrase("Greetings, " + GetAddress_Form(NPChar) + ". Do you have business with me?",
                                    "Hello, " + GetFullName(Pchar) + ". I've seen your ship coming to our port, and I was sure that you'd come to see me.",
                                    "Oh, captain " + GetFullName(Pchar) + ". What brought you to me?");
				Link.l1 = "Hello, " + GetFullName(NPChar) + ". I wanted to talk to you.";
			}
			Link.l1.go = "node_2";
		break;
		
		case "node_2":
			// Церковный генератор 1
			if(CheckAttribute(PChar, "GenQuest.ChurchQuest_1.AskPortMan") && PChar.GenQuest.ChurchQuest_1.AskPortMan_InColony == NPChar.city)
			{
				dialog.text = "Excellent. I am at your service, " + GetFullName(PChar) + ".";
				if(!CheckAttribute(PChar, "GenQuest.ChurchQuest_1.CapFullInfo"))	// Получаем полную инфу
				{
					if(CheckAttribute(PChar, "GenQuest.ChurchQuest_1.NoMoneyToPortMan"))
					{
						dialog.text = "So, what's the deal with the money? Have you brought me at least a thousand pesos?";
						if(sti(PChar.Money) >= 1000)
						{
							link.l1 = "Yes, I have"+ GetSexPhrase("","") +". That's exactly a thousand pesos. Now the information!";
							link.l1.go = "Church_GenQuest1_Node_FillFullInfo_3";
						}
						else
						{
							link.l1 = LinkRandPhrase("No, not yet...", "not yet...", "not yet, but will bring soon...");
							link.l1.go = "exit";
						}
					}
					else
					{
						link.l1 = "Please, allow me to explain the heart of the problem. Me and my old friend, captain  " + PChar.GenQuest.ChurchQuest_1.CapFullName + ", missed each other just by a couple of hours, and I had urgent business with him. Now I'll have to catch up with him, but I am not aware"+ GetSexPhrase("","") +", where to he departed.";
						link.l1.go = "Church_GenQuest1_Node_FillFullInfo";
					}
				}
				else	// Полная инфа уже есть
				{
					link.l1 = "Mister harbor master, I need information about ship '" + PChar.GenQuest.ChurchQuest_1.CapShipName + "', belonging to captain " + PChar.GenQuest.ChurchQuest_1.CapFullName + ".";
					if(CheckAttribute(PChar, "GenQuest.ChurchQuest_1.NextColonyIsLast")) // Он здесь, в этой колонии!		
						link.l1.go = "Church_GenQuest1_Node_CapOnThisColony_1";
					else // Отправляет в рандомную колонию
						link.l1.go = "Church_GenQuest1_Node_FillInfoOfCapColony_1";
				}				
				break;
			}		
//-------------------------------------------//Jason, фрахт---------------------------------------------------
				if (CheckAttribute(PChar, "questTemp.WPU.Fraht.TargetPortmanID") && CheckAttribute(PChar, "questTemp.WPU.Fraht.LevelUp") && pchar.questTemp.WPU.Fraht.TargetPortmanID == npchar.id)
				{
					dialog.text = "Excellent. I am at your service, " + GetFullName(PChar) + ".";
					Link.l1 = "The cargo for your colony is in the hold of my ship.";
					Link.l1.go = "Fraht_completeLevelUp";
					break;
				}
				if (CheckAttribute(PChar, "questTemp.WPU.Fraht.TargetPortmanID") && pchar.questTemp.WPU.Fraht != "lost" && pchar.questTemp.WPU.Fraht.TargetPortmanID == npchar.id)
				{
					dialog.text = "Excellent. I am at your service, " + GetFullName(PChar) + ".";
					Link.l1 = "The cargo for your colony is in the hold of my ship.";
					Link.l1.go = "Fraht_complete";
					break;
				}
			
				if (CheckAttribute(PChar, "questTemp.WPU.Fraht.TargetPortmanID") && pchar.questTemp.WPU.Fraht == "lost" && pchar.questTemp.WPU.Fraht.Nation == npchar.nation)
				{
					if (pchar.questTemp.WPU.Fraht.TargetPortmanID == npchar.id)
					{
						dialog.text = "Oh, so you've come at last. Frankly, I didn't expect you to come back. We have already petitioned the authorities to mark you as a wanted person. So, what do you have to say?";
						Link.l1 = "I failed to deliver the cargo in time due to unforeseen circumstances. But I want to settle this conflict in a peaceful manner. I have brought your cargo and I hope that we'd be able to come to an agreement.";
						Link.l1.go = "Fraht_complete_bad";
					}
					else
					{
						dialog.text = "Oh, I know, who you are. You contracted to deliver the cargo, but you stole it! Guards, guards!";
						Link.l1 = "Aaargh!";
						Link.l1.go = "exit";
						LAi_group_Attack(NPChar, Pchar);
					}
				}
// <-- фрахт
//-------------------------------------------//Jason, почта---------------------------------------------------	
		
				if (CheckAttribute(PChar, "questTemp.WPU.Postcureer.TargetPortmanID") && pchar.questTemp.WPU.Postcureer != "lost" && pchar.questTemp.WPU.Postcureer.TargetPortmanID == npchar.id)
				{
					dialog.text = "Excellent. I am at your service, " + GetFullName(PChar) + ".";
					Link.l1 = "I delivered the mail for your colony.";
					Link.l1.go = "Postcureer_complete";
					break;
				}
			
				if (CheckAttribute(PChar, "questTemp.WPU.Postcureer.TargetPortmanID") && pchar.questTemp.WPU.Postcureer == "lost" && pchar.questTemp.WPU.Postcureer.TargetPortmanID == npchar.id)
				{
					dialog.text = "Oh, so you've come at last. Frankly, we already thought you were dead... Well, it's a good thing you are just a dunderhead, but still not a dead man.";
					Link.l1 = "I failed to deliver the mail in time due to unforeseen circumstances. But here it is.";
					Link.l1.go = "Postcureer_complete_bad";
					break;
				}
			
				if (CheckAttribute(PChar, "questTemp.WPU.Postcureer.fail") && pchar.questTemp.WPU.Postcureer.StartCity == npchar.city)
				{
					dialog.text = "What's happened? You look like death warmed up.";
					Link.l1 = "" + GetAddress_FormToNPC(NPChar) + ", you were right when you'd warned me about the danger. Right at the exit from the port authority office I was attacked by two men in black, and... well, they took the package away from me.";
					Link.l1.go = "Postcureer_complete_fail";
					break;
				}
// <-- почта
//-------------------------------------------//Jason, эскорт---------------------------------------------------	
				if(CheckAttribute(PChar, "questTemp.WPU.Escort.TargetPortmanID") && CheckAttribute(pchar, "questTemp.WPU.Escort.LevelUp_0") && pchar.questTemp.WPU.Escort.TargetPortmanID == npchar.id)
				{
					dialog.text = "Excellent. I am at your service, " + GetFullName(PChar) + ".";
					Link.l1 = "I was sent here by harbor master "+XI_ConvertString("Colony"+pchar.questTemp.WPU.Escort.StartCity+"Gen")+". I have to escort a ship with a cargo of arms and ammunition worth at you on the roads. Here are my papers.";
					Link.l1.go = "Escort_LUGo_0";
					break;
				}
				if(CheckAttribute(PChar, "questTemp.WPU.Escort.TargetPortmanID") && CheckAttribute(pchar, "questTemp.WPU.Escort.LevelUpGo_0") && npchar.location == pchar.questTemp.WPU.Escort.StartCity +"_portoffice")
				{
					dialog.text = "Excellent. I am at your service, " + GetFullName(PChar) + ".";
					Link.l1 = "I escorted the ship with the weapons, just as we agreed.";
					Link.l1.go = "Escort_LUGo_complete";
					break;
				}
				if(CheckAttribute(PChar, "questTemp.WPU.Escort.TargetPortmanID") && CheckAttribute(pchar, "questTemp.WPU.Escort.LevelUp_1WM") && pchar.questTemp.WPU.Escort == "current" && npchar.location == pchar.questTemp.WPU.Escort.StartCity +"_portoffice")
				{
					dialog.text = "Excellent. I am at your service, " + GetFullName(PChar) + ".";
					Link.l1 = "I have found the missing vessel and brought it to your port. Its captain should have already reported that to you.";
					Link.l1.go = "Escort_LU1WM_complete";
					break;
				}
				if(CheckAttribute(PChar, "questTemp.WPU.Escort.TargetPortmanID") && CheckAttribute(pchar, "questTemp.WPU.Escort.LevelUp_1VSP") && pchar.questTemp.WPU.Escort == "win" && npchar.location == pchar.questTemp.WPU.Escort.StartCity +"_portoffice")
				{
					dialog.text = "Excellent. I am at your service, " + GetFullName(PChar) + ".";
					Link.l1 = "I have found the missing vessel and brought it to your port. Its captain should have already reported that to you.";
					Link.l1.go = "Escort_LU1VSP_complete";
					break;
				}
				if(CheckAttribute(PChar, "questTemp.WPU.Escort.TargetPortmanID") && CheckAttribute(pchar, "questTemp.WPU.Escort.LevelUp_1VSP") && pchar.questTemp.WPU.Escort == "sink" && npchar.location == pchar.questTemp.WPU.Escort.StartCity +"_portoffice")
				{
					dialog.text = "Excellent. I am at your service, " + GetFullName(PChar) + ".";
					Link.l1 = "I have found the missing vessel at the shores of the island of "+XI_ConvertString(pchar.questTemp.WPU.Current.TargetIslandID)+". Its captain was engaged in unequal combat with a superior pirate force. I helped you in any way I could, but all my efforts were in vain: damn scoundrels have sunk the ship. All I could do at that point was to avenge it.";
					Link.l1.go = "Escort_LU1VSP_completeSink";
					break;
				}
				if(CheckAttribute(PChar, "questTemp.WPU.Escort.TargetPortmanID") && CheckAttribute(pchar, "questTemp.WPU.Escort.LevelUp_1S") && pchar.questTemp.WPU.Escort == "win" && npchar.location == pchar.questTemp.WPU.Escort.StartCity +"_portoffice")
				{
					dialog.text = "Excellent. I am at your service, " + GetFullName(PChar) + ".";
					Link.l1 = "I have found the missing vessel at the shores of the island of "+XI_ConvertString(pchar.questTemp.WPU.Current.TargetIslandID)+". Well, not the ship itself, actually, but rather about half a hundred men of its crew and the captain. They are safe now - the crew is on my ship, and the captain is in your town now - I take it he had already paid you a visit.";
					Link.l1.go = "Escort_LU1S_complete";
					break;
				}
				if(CheckAttribute(PChar, "questTemp.WPU.Escort.TargetPortmanID") && CheckAttribute(pchar, "questTemp.WPU.Escort.LevelUp_2") && pchar.questTemp.WPU.Escort == "win" && npchar.location == pchar.questTemp.WPU.Escort.StartCity +"_portoffice")
				{
					dialog.text = "Excellent. I am at your service, " + GetFullName(PChar) + ".";
					Link.l1 = "I have fulfilled your assignment. Pirate squadron, which attacked the trading convoy, has been destroyed.";
					Link.l1.go = "Escort_LU2_complete";
					break;
				}
				if (CheckAttribute(PChar, "questTemp.WPU.Escort.TargetPortmanID") && CheckAttribute(pchar, "questTemp.WPU.Escort.Bonus") && pchar.questTemp.WPU.Escort.Bonus != "fail" && pchar.questTemp.WPU.Escort.TargetPortmanID == npchar.id)
				{
					dialog.text = "Excellent. I am at your service, " + GetFullName(PChar) + ".";
					Link.l1 = "I am the captain of the escort vessel. I brought the trading ships to the port and want to make a report about it.";
					Link.l1.go = "Escort_complete";
					break;
				}
				if (CheckAttribute(PChar, "questTemp.WPU.Escort.TargetPortmanID") && CheckAttribute(pchar, "questTemp.WPU.Escort.Bonus") && pchar.questTemp.WPU.Escort.Bonus == "fail" && pchar.questTemp.WPU.Escort.TargetPortmanID == npchar.id)
				{
					dialog.text = "Excellent. I am at your service, " + GetFullName(PChar) + ".";
					Link.l1 = "I am the captain of the escort vessel. I had to bring two trading ships and cargo to the port, but, unfortunately, both escorted ships sank during a battle with an enemy convoy. But I still managed to deliver the cargo.";
					Link.l1.go = "Escort_fail";
					break;
				}
				if (CheckAttribute(PChar, "questTemp.WPU.Escort.TargetPortmanID") && pchar.questTemp.WPU.Escort.TargetPortmanID == npchar.id && !CheckAttribute(PChar, "questTemp.WPU.Escort.LevelUp"))
				{
					dialog.text = "Excellent. I am at your service, " + GetFullName(PChar) + ".";
					Link.l1 = "I am the captain of the escort vessel. I brought the trading ships to the port and want to make a report about it.";
					Link.l1.go = "Escort_complete";
					break;
				}
// <-- эскорт
		
			dialog.text = "Excellent. I am at your service, " + GetFullName(PChar) + ".";
			if (npchar.city != "Panama") // Captain Beltrop, 24.12.2020, запрет брать задания и ставить корабли в ПУ Панамы
			{
				Link.l2 = "Can I find any job here? Or a contract, perhaps?";
				Link.l2.go = "Work_check"; //фрахты-почта-эскорт
				Link.l14 = "Maybe there's a job which requires foreign help? I could offer my services.";
				Link.l14.go = "node_4"; //на мини-квесты
				Link.l3 = "Can I leave one of my ships there for some time?";
				Link.l3.go = "ShipStock_1";
			}
			if (sti(NPChar.Portman) > 0)
			{
                Link.l4 = "I want to take my ship back.";
    			Link.l4.go = "ShipStockReturn_1";
			}
			if (CheckAttribute(pchar, "GenQuest.LoanChest.TakeChest") && sti(pchar.GenQuest.LoanChest.TargetIdx) == sti(NPChar.index))
			{
				link.l5 = "I came to discuss financial business.";
				link.l5.go = "LoanForAll";//(перессылка в кредитный генератор)	
			}
  			if (CheckAttribute(pchar, "GenQuest.Intelligence") && pchar.GenQuest.Intelligence.SpyId == npchar.id && pchar.GenQuest.Intelligence == "") //квест мэра - на связь с нашим шпионом
			{
				link.l7 = RandPhraseSimple("I am here on request of one man. His name is governor " + GetFullName(characterFromId(pchar.GenQuest.Intelligence.MayorId)) + ".", 
					GetFullName(characterFromId(pchar.GenQuest.Intelligence.MayorId)) + " sent me to you. I am supposed to pick up something...");
				link.l7.go = "IntelligenceForAll";
			}
			link.l6 = "I would like to know about captains, who registered at your port authority.";
			link.l6.go = "CapitainList";
			
			link.l8 = "I'm on another matter.";
			// Warship 26.07.09 Генер "Сгоревшее судно"
			if(CheckAttribute(NPChar, "Quest.BurntShip") && !CheckAttribute(NPChar, "Quest.BurntShip.LastQuestDate"))
			{
				if(CheckAttribute(NPChar, "Quest.BurntShip.TimeIsOver")) // Просрочено
				{
					link.l8.go = "BurntShip10";
				}
				else
				{
					if(CheckAttribute(NPChar, "Quest.BurntShip.TwoDaysWait"))
					{
						if(GetNpcQuestPastDayParam(NPChar, "Quest.BurntShip.TwoDaysWait") >= 2)
						{
							link.l8.go = "BurntShip17";
						}
						else
						{
							link.l8.go = "quests";
						}
					}
					else
					{
						link.l8.go = "BurntShip12";
					}
				}
			}
			else
			{
				link.l8.go = "quests";
			}
			if(CheckAttribute(pchar,"GenQuest.EncGirl"))
			{
				if(pchar.GenQuest.EncGirl == "toLoverFather" && pchar.GenQuest.EncGirl.LoverFather == "portman_keeper" && pchar.GenQuest.EncGirl.LoverCity == npchar.city)
				{
					link.l9 = "Hello, I came by your son's invitation."; 
					link.l9.go = "EncGirl_4";
					pchar.quest.EncGirl_GetLoverFather.over = "yes";
				}	
				if(pchar.GenQuest.EncGirl == "toParents" || pchar.GenQuest.EncGirl == "FindLover")
				{
					if(pchar.GenQuest.EncGirl.Father == "portman_keeper" && npchar.city == pchar.GenQuest.EncGirl.city)
					{
						link.l9 = "This is about your daughter...";
						link.l9.go = "EncGirl_1";
					}
				}
			}
			if (CheckCharacterItem(pchar, "CaptainBook"))
			{
				if(pchar.questTemp.different == "free")
				{
					link.l10 = "I have found by chance this package of ship documents.";
					link.l10.go = "ShipLetters_out1";				
				}
				else
				{
					if(pchar.questTemp.different.GiveShipLetters.city == npchar.city)
					{
						link.l10 = "I have found by chance this package of ship documents, which must have been lost by someone.";
						if(!CheckAttribute(pchar, "questTemp.different.GiveShipLetters.speakPortman"))
						{
							link.l10.go = "ShipLetters_Portman1_1";						
						}
						else
						{
							link.l10.go = "ShipLetters_Portman2";
						}
					}
				}		
			}												
			Link.l15 = "Thank you. Goodbye.";
			Link.l15.go = "exit";
		break;

		case "Church_GenQuest1_Node_FillFullInfo":
			dialog.text = "Your problem can be easily solved. You can see any official of the navigation service, and he will provide you with all information regarding the route of your friend's ship.";
			link.l1 = "Unfortunately, it's not all that easy. My friend has renamed his ship in your port... for religious reasons.";
			link.l1.go = "Church_GenQuest1_Node_FillFullInfo_2";
		break;
			
		case "Church_GenQuest1_Node_FillFullInfo_2":
			dialog.text = "I see. That makes things a bit more difficult. I need to rummage through the records in the ship's register, and that will take some time. And time is money, as you should know.";
			if(sti(pchar.money) >= 1000)
			{
				link.l1 = "I perfectly realize it, mister " + GetFullName(NPChar) + ", and adequately prepared to evaluate your time ... in the amount of, say, 1,000 pesos.";
				link.l1.go = "Church_GenQuest1_Node_FillFullInfo_3";
			}
			else
			{
				DeleteAttribute(pchar, "GenQuest.ChurchQuest_1.CurPortManColony"); // Можно будет спросить.
				link.l1 = "That's too bad, since I don't have any money on myself at the moment... I'll come back later...";
				link.l1.go = "exit";
			}
		break;
			
		case "Church_GenQuest1_Node_FillFullInfo_3":
			sColony = GetColonyExpect2Colonies(NPChar.city, PChar.GenQuest.ChurchQuest_1.QuestTown);
			PChar.GenQuest.ChurchQuest_1.CapGoToColony = sColony;
			if(CheckAttribute(pchar, "GenQuest.ChurchQuest_1.NoMoneyToPortMan"))
			{
				dialog.text = "Perfect! Let's see now... just a minute... here... right. The renaming of the ship was registered, and the ship, which from now on shall be known as '" + PChar.GenQuest.ChurchQuest_1.CapShipName + "' commanded by captain " + PChar.GenQuest.ChurchQuest_1.CapFullName + " has set sail today towards " + XI_ConvertString("Colony" + sColony + "Gen") + ".";
				DeleteAttribute(pchar, "GenQuest.ChurchQuest_1.NoMoneyToPortMan");
			}
			else
				dialog.text = "Oh! You really understand that I am a very busy man, and I am glad that you appreciated it! Let's see now... just a minute... here... right. The renaming of the ship was registered, and the ship, which from now on shall be known as '" + PChar.GenQuest.ChurchQuest_1.CapShipName + "' commanded by captain " + PChar.GenQuest.ChurchQuest_1.CapFullName + " has set sail today towards " + XI_ConvertString("Colony" + sColony + "Gen") + ".";			
				link.l1 = "Thank you, sir, you gave me a really big favor.";
				link.l1.go = "Church_GenQuest1_Node_FillFullInfo_4";
				AddMoneyToCharacter(pchar, -1000);
		break;
			
		case "Church_GenQuest1_Node_FillFullInfo_4":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			sQuestTitle = PChar.GenQuest.ChurchQuest_1.QuestTown + "ChurchGenQuest1";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest1", "4");
			AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("",""));
			AddQuestUserData(sQuestTitle, "sColony", XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.CapGoToColony + "Gen"));
			AddQuestUserData(sQuestTitle, "sShipName", PChar.GenQuest.ChurchQuest_1.CapShipName);	
			PChar.GenQuest.ChurchQuest_1.AskPortMan_InColony = PChar.GenQuest.ChurchQuest_1.CapGoToColony;
			PChar.GenQuest.ChurchQuest_1.CapFullInfo = true;
		break;
			
		case "Church_GenQuest1_Node_FillInfoOfCapColony_1":
			dialog.text = "What exactly did you want to know?";
			link.l1 = "Can you tell me, if that captain's ship visited your port?";
			link.l1.go = "Church_GenQuest1_Node_FillInfoOfCapColony_2";
		break;
						
		case "Church_GenQuest1_Node_FillInfoOfCapColony_2":
			PChar.GenQuest.ChurchQuest_1.CapGoToColony = GetColonyExpect2Colonies(NPChar.city, PChar.GenQuest.ChurchQuest_1.QuestTown);
			dialog.text = "Hmm... And may I know, why are you asking?";
			link.l1 = "I have business with him. But if he didn't call at your port or you don't...";
			link.l1.go = "Church_GenQuest1_Node_FillInfoOfCapColony_3";
		break;
			
		case "Church_GenQuest1_Node_FillInfoOfCapColony_3":
			dialog.text = "He did. But praise to all the Saints, just this morning he rid us of his company and headed to " + XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.CapGoToColony + "Acc") + ". And I confess sincerely sorry anyone who will have to deal with him.";
			link.l1 = "In that case wish me luck - and thank you for your help.";
			link.l1.go = "Church_GenQuest1_Node_FillInfoOfCapColony_4";
		break;
			
		case "Church_GenQuest1_Node_FillInfoOfCapColony_4":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			sQuestTitle = PChar.GenQuest.ChurchQuest_1.QuestTown + "ChurchGenQuest1";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest1", "5");
			AddQuestUserData(sQuestTitle, "sColony", XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.CapGoToColony + "Dat"));
			AddQuestUserData(sQuestTitle, "sName", PChar.GenQuest.ChurchQuest_1.CapFullName);
			PChar.GenQuest.ChurchQuest_1.AskPortMan_InColony = PChar.GenQuest.ChurchQuest_1.CapGoToColony; // Спрашиваем портмана в колонии, куда отправился кэп.
			if(rand(2) == 1) 
			{
				Log_TestInfo("The next colony is the last");
				PChar.GenQuest.ChurchQuest_1.NextColonyIsLast = true; // Флаг - следующая колония будет последней
			}
		break;
			
		case "Church_GenQuest1_Node_CapOnThisColony_1":
			dialog.text = "What do you want to know, "+ GetSexPhrase("mister","miss") +" " + GetFullName(PChar) + "?";
			link.l1 = "Could you tell we whether this captain called at your port or not?";
			link.l1.go = "Church_GenQuest1_Node_CapOnThisColony_2";
		break;
			
		case "Church_GenQuest1_Node_CapOnThisColony_2":
			dialog.text = "Hmm, he sure did. And I must say that I am impatiently waiting for that blessed moment when he finally leaves this long-suffered port.";
			link.l1 = "You mean to say that his ship is still here?";
			link.l1.go = "Church_GenQuest1_Node_CapOnThisColony_3";
		break;
			
		case "Church_GenQuest1_Node_CapOnThisColony_3":
			dialog.text = "Yes, gracious "+ GetSexPhrase("sir","lady") +". The entire port, starting with the worst of the loaders and ending with the head of the pilot service, is praying for his swift departure. His ship has just left the dry dock, where it was promptly repaired, but by that time its gallant captain already fell out with every carpenter and rejected three batches of selected planks for the ship's skin. But tomorrow our most gracious and all-seeing Lord shall rid us of that... of that plague, of that sore in the aspect of man!";
			link.l1 = "Now, calm down, mister " + NPChar.Name + ", and think about that someone's going to have a harder time still. You have already passed this trial, while I have yet to meet that captain of yours. And now, if you excuse me...";
			link.l1.go = "Church_GenQuest1_Node_CapOnThisColony_4";
		break;
			
		case "Church_GenQuest1_Node_CapOnThisColony_4":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			sQuestTitle = PChar.GenQuest.ChurchQuest_1.QuestTown + "ChurchGenQuest1";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest1", "6");
			AddQuestUserData(sQuestTitle, "sColony", XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.QuestTown));
//			PChar.GenQuest.ChurchQuest_1.NeedToDialogWithSailors = true; // Спрашиваем моряков
			PChar.GenQuest.ChurchQuest_1.NeedToDialogWithCap = true; // Говорим с капитаном
//			SetFunctionLocationCondition("Church_GenQuest1_ChangeCapitanLocation", "Deck_Near_Ship", true);
			PChar.GenQuest.ChurchQuest_1.CurPortManColony = NPChar.city;
			Group_SetAddress("ChurchGenQuest1_CapGroup", colonies[FindColony(NPChar.City)].Island, "IslandShips1", "Ship_1"); // Ставим кэпа в порту колонии
			Characters[GetCharacterIndex("ChurchGenQuest1_Cap")].Nation = sti(NPChar.Nation); // Сменим нацию, чтоб вражды не было
			DeleteAttribute(PChar, "GenQuest.ChurchQuest_1.AskPortMan"); // Больше не спрашиваем
//			if(rand(1) == 0) PChar.GenQuest.ChurchQuest_1.CapWaitOnTavern = true;
			sld = CharacterFromID("ChurchGenQuest1_Cap");
			sld.DeckDialogNode = "ChurchGenQuest_1_DeckDialog_1";
		break;
						
		case "ShipLetters_out1":
			dialog.text = "Let me take a look! Yes, indeed, in my documents this set is labeled as void. It's very kind of you that you've found a moment to come see me and hand me these papers. Off the wind, captain!";
			link.l1 = "Thanks!";
			link.l1.go = "exit";
			TakeItemFromCharacter(pchar, "CaptainBook"); 			
			pchar.questTemp.different = "free";
			pchar.quest.GiveShipLetters_null.over = "yes"; //снимаем таймер 
			AddQuestRecord("GiveShipLetters", "10");			
			CloseQuestHeader("GiveShipLetters");
			DeleteAttribute(pchar, "questTemp.different.GiveShipLetters");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit(); 
		break;
				
		case "ShipLetters_Portman1_1":
			pchar.questTemp.different.GiveShipLetters.speakPortman = true;
			s1 = "Let me take a look! Yes, this vessel and its captain are both registered in my documents. ";
			s1 = s1 + "Your conscientiousness, captain, reflects credit upon yourself! Of course, your efforts must not go without a reward.  ";
			dialog.text = s1 + "Say, will you consider a sum of " + sti(pchar.questTemp.different.GiveShipLetters.price1) + " pesos a deserving reward?";
			link.l1 = "Of course not!";
			link.l1.go = "exit";
			link.l2 = "Well, a modest sum, but then again it was no big deal, either. Yes, I accept your offer, "  + npchar.name +".";
			link.l2.go = "ShipLetters_Portman1_2";
		break;
		
		case "ShipLetters_Portman1_2" :
			TakeItemFromCharacter(pchar, "CaptainBook"); 
			addMoneyToCharacter(pchar, sti(pchar.questTemp.different.GiveShipLetters.price1)); 			
			pchar.questTemp.different = "free";
			pchar.quest.GiveShipLetters_null.over = "yes"; //снимаем таймер 
			AddQuestRecord("GiveShipLetters", "5");			
			CloseQuestHeader("GiveShipLetters");
			DeleteAttribute(pchar, "questTemp.different.GiveShipLetters");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit(); 
		break;
		
		case "ShipLetters_Portman2":
			dialog.text = "Will you accept my offer?";
			link.l1 = "Of course, not!";
			link.l1.go = "exit";
			link.l2 = "Perhaps. Although I'm sure that these papers are more expensive.";
			link.l2.go = "ShipLetters_Portman2_1";
		break;
		
		case "ShipLetters_Portman2_1":
			TakeItemFromCharacter(pchar, "CaptainBook"); 
			addMoneyToCharacter(pchar, sti(pchar.questTemp.different.GiveShipLetters.price1)); 			
			pchar.questTemp.different = "free";
			pchar.quest.GiveShipLetters_null.over = "yes"; //снимаем таймер 
			AddQuestRecord("GiveShipLetters", "6");			
			CloseQuestHeader("GiveShipLetters");
			DeleteAttribute(pchar, "questTemp.different.GiveShipLetters");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit(); 		
		break;

		case "EncGirl_1":
			dialog.text = "I am all ears.";
			link.l1 = "I've brought your fugitive.";
			link.l1.go = "EncGirl_2";
		break;
		
		case "EncGirl_2":
			dialog.text = "Oh, captain, thank you so much! How is she? Is she hurt? Why did she run away? Why?\nDoesn't she understand? The groom is a wealthy and important man! Youth is naive and foolish... cruel even. Remember that!";
			link.l1 = "Well, you are her father and the final decision is yours, but I would not hurry with the wedding...";
			link.l1.go = "EncGirl_3";
		break;
		
		case "EncGirl_3":
			dialog.text = "What do you know? Do you have your own children? No? When you've got one, come to see me and we will talk\nI promised a reward to anyone who take her back to the family.";
			link.l1 = "Thanks. You should keep an eye on her. I have a hunch that she won't stop at that.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("EncGirl_ToLoverParentsExit");
		break;
		
		case "EncGirl_4":
			if(sti(pchar.GenQuest.EncGirl.LoverFatherAngry) == 0)
			{
				dialog.text = "Oh, you're that "+ GetSexPhrase("captain who brought","young lady, who brought") +" my prodigal son with a young bride?";
				link.l1 = "Yes, I helped their escape.";
				link.l1.go = "EncGirl_5";
			}
			else
			{
				dialog.text = "Oh, come, benefactor. Likely, waiting for reward?";
				link.l1 = "Well, I'm fine without a reward, but just your thanks would do.";
				link.l1.go = "EncGirl_6";			
			}
		break;
		
		case "EncGirl_5":
			dialog.text = "I am very grateful to you that you haven't abandoned my child in dire straits and helped him to find a way out of a delicate situation. Allow me to thank you and please, accept this modest sum and a gift from me personally.";
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
		
		case "node_4":
			//--> проверка миниквестов начальника порта. 
			if (npchar.quest == "PortmansJornal") //взят квест на судовой журнал
			{
				dialog.text = "You were supposed to locate captain " + npchar.quest.PortmansJornal.capName + " and return his ship's log to him. Have you done it?";
				link.l1 = "No, I haven't yet...";
				link.l1.go = "PortmanQuest_NF";
				break;
			}
			if (npchar.quest == "PortmansSeekShip" || npchar.quest == "SeekShip_sink") //взят квест на поиски украденного корабля
			{
				dialog.text = "You committed yourself to seeking out a stolen " + GetStrSmallRegister(XI_ConvertString(npchar.quest.PortmansSeekShip.shipTapeName)) + " '" + npchar.quest.PortmansSeekShip.shipName + "'. There will be no other assignments for you until you're done with that one.";
				link.l1 = "I will continue my search, just wait.";
				link.l1.go = "exit";
				link.l2 = "I want to give up your assignment.";
				link.l2.go = "SeekShip_break";
				break;
			}
			if (npchar.quest == "SeekShip_success") //украденный корабль взят на абордаж
			{
				dialog.text = "You promised me to seek out stolen " + GetStrSmallRegister(XI_ConvertString(npchar.quest.PortmansSeekShip.shipTapeName)) + " '" + npchar.quest.PortmansSeekShip.shipName + "'. Have you done it?";
				bool bOk = false;
				for (i=0; i<=COMPANION_MAX; i++)
				{
					cn = GetCompanionIndex(pchar, i);
					if(cn != -1)
					{
						sld = &characters[cn];
						if (sld.ship.name == npchar.quest.PortmansSeekShip.shipName && 
							RealShips[sti(sld.ship.type)].BaseName == npchar.quest.PortmansSeekShip.shipTapeName &&
							RealShips[sti(sld.Ship.Type)].basetype == npchar.quest.PortmansSeekShip.shipTape)
						{
							if (i == 0)
							{	//если нужный корабль - у ГГ
								sld.Ship.Type = GenerateShip(SHIP_TARTANE, true);
								SetBaseShipData(sld);
								SetCrewQuantityFull(sld);
							}
							else
							{
								RemoveCharacterCompanion(pchar, sld);
								AddPassenger(pchar, sld, false);
							}
							bOk = true;
						}
					}
				}				
				if (bOk)
				{
					link.l1 = "Yes, I found it, it is now in port. You can take it.";
					link.l1.go = "SeekShip_good";
				}
				else
				{
					link.l1 = "I will continue my search, just wait.";
					link.l1.go = "exit";
				}
				link.l2 = "I want to give up your assignment.";
				link.l2.go = "SeekShip_break";
				break;
			}
			//<-- проверка миниквестов начальника порта. 

			//--> дача миниквестов начальника порта. 
			if (rand(2) < 2 && pchar.questTemp.different == "free" && GetNpcQuestPastDayWOInit(npchar, "quest.meeting") > 7)
			{
				dialog.text = LinkRandPhrase("Yes, goddammit! I have a job for you!", 
					"Ha! You're just in time! I have an issue to be resolved.", 
					"But of course! Of course I have work for you! You know, I am just overrun with problems lately...");
				link.l1 = "Then please get to the point, " + GetAddress_FormToNPC(NPChar) + ".";
				link.l1.go = "PortmanQuest";
				SaveCurrentNpcQuestDateParam(npchar, "quest.meeting");
				break;
			}
			
			// Warship 25.07.09 Генер "Сгоревшее судно"
			if(dRand(4) == 2 && !CheckAttribute(NPChar, "Quest.BurntShip"))
			{
				dialog.text = "God! Captain " + GetFullName(PChar) + ", you're just in time! Such a misfortune happened, such a calamity... The ship has burned at roadstead, left in the care of the Port Authority! Because of carelessness of security the ship burned... burned to the waterline...\n" + "Lord, for what did I get such a punishment? After so many years faithfully served.";
				link.l1 = "So, what's the big deal? A ship burned down? And what are insurance contracts for? Or you decided not to insure it to save your money and now you're eating your heart out?";
				link.l1.go = "BurntShip4";
				link.l2 = "With such questions for help you need the shipyard, not me. In a couple of months they will restore the old one, or even build a new one. I am not a shipbuilder, so sorry...";
				link.l2.go = "BurntShip2";
				break;
			}
			//<-- дача миниквестов начальника порта.

			dialog.text = "The governor cares for the well-being of his city, so he always has jobs. There can be interested merchants at the tavern, and the store is freighting captains as well.";
			Link.l1 = "I have one more question.";
			Link.l1.go = "node_2";
			Link.l2 = "Thank you. Goodbye.";
			Link.l2.go = "exit";
		break;

///Jason-----------------------новые генераторы накопительного типа для портмана----------------------------
		int iTime, idaysQty, iGoods, iGoodsQty, amount;
		case "Work_check"://фейс-контроль - общая проверка профпригодности ГГ и выбор задания
			ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
			if(sti(Pchar.Ship.Type) != SHIP_NOTUSED && ok)//проверка на наличие корабля в порту
			{
				if (!CheckAttribute(npchar, "work_date") || GetNpcQuestPastDayParam(npchar, "work_date") >= 2)//проверка повтора
				{
					if (sti(NPChar.nation) != PIRATE && GetNationRelation2MainCharacter(sti(NPChar.nation)) == RELATION_ENEMY)//проверка межнациональных отношений
					{
						dialog.text = RandPhraseSimple("There is no job for those who sail under the flag of " + NationNameGenitive(sti(pchar.nation)) + "! Leave my office at once!", "I will not collaborate with " + NationNameAblative(sti(pchar.nation)) + ". Begone!");
						link.l1 = RandPhraseSimple("Well, as you wish...", "Well, as you like...");
						link.l1.go = "exit";
						break;
					}
					if (makeint(PChar.reputation.nobility) < 41) // проверка репутации ГГ
					{
						dialog.text = "Your reputation doesn't inspire confidence in me. I am not going to collaborate with you. Farewell.";
						link.l1 = "What! It's all lies.";
						link.l1.go = "exit";
						break;
					}
					if (GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) < 5)//при низком авторитете не даем
					{
						dialog.text = "I don't want to insult you, captain, but... I am afraid you would not be able to fulfill my assignment - you simply have a lack of experience. I cannot sign a contract with you.";
						link.l1 = "I see. Well, as you say.";
						link.l1.go = "exit";
						break;
					}
					dialog.Text = "Hmm... Well, that depends on the job you're interested in.";
					link.l1 = "I could offer you to charter my vessel for shipping cargo.";
					Link.l1.go = "Fraht_begin";
					link.l2 = "Well, perhaps you could offer something?";
					Link.l2.go = "Check_other";
				}
				else
				{
					dialog.Text = "There's nothing left for today. Come another day.";
					link.l1 = "Fine.";
					Link.l1.go = "exit";
				}
			}
			else
			{
				dialog.text = "I don't see your ship in the port. Lie off and then come see me again - we'll try to find something for you.";
				link.l1 = "Alright, I'll do just that.";
				link.l1.go = "exit";
			}
		break;
	
		case "Check_other"://выбор между почтовым курьером, эскортом и ничем
		SaveCurrentNpcQuestDateParam(npchar, "work_date"); // mitrokosta безусловно сохраняем
		int nTask = 0;
		string tasks[10]; // mitrokosta сделал выбор задания расширяемым на тот случай если задания добавятся
		if (stf(RealShips[sti(pchar.Ship.Type)].SpeedRate) >= 15) {
			tasks[nTask] = "cureer";
			nTask++;
		}
		if (GetCompanionQuantity(pchar) < 3 && sti(RealShips[sti(pchar.Ship.Type)].BaseType) >= SHIP_BRIG && sti(RealShips[sti(pchar.Ship.Type)].BaseType) != SHIP_GALEON_L && sti(RealShips[sti(pchar.Ship.Type)].BaseType) != SHIP_PINNACE) {
			tasks[nTask] = "escort";
			nTask++;
		}
		if (nTask > 0 && drand(5) > 1) {
			string sTask = tasks[drand(nTask - 1)];
			switch (sTask) {
				case "cureer":
					if (pchar.questTemp.WPU.Postcureer == "begin" || pchar.questTemp.WPU.Postcureer == "late" || pchar.questTemp.WPU.Postcureer == "lost" || pchar.questTemp.WPU.Postcureer == "fail" || CheckAttribute(pchar, "questTemp.WPU.Postcureer.LevelUp")) { // если заняты
						dialog.text = "Unfortunately, I can't offer you anything of that kind. Drop in again in a couple of days.";
						link.l1 = "Alright, I'll do just that.";
						link.l1.go = "exit";
					} else { // если не заняты
						if (sti(pchar.questTemp.WPU.Postcureer.count) > 3 && drand(1) == 1) { //если 2 уровень
							dialog.text = "So... You have already taken several jobs as a courier and were quite successful at it, to the best of my knowledge. Probably you would manage the task I am going to assign to you.";
							link.l1 = "I am all ears, " + GetAddress_FormToNPC(NPChar) + ".";
							link.l1.go = "Postcureer_LevelUp";
						} else { // первый уровень
							dialog.text = "I see you have a fast ship. I can offer you a courier job - delivering mail and commercial papers.";
							link.l1 = "This is interesting. I agree. Where do I need to go?";
							link.l1.go = "Postcureer";
							link.l2 = "Thank you, but that's just not my kind of work.";
							link.l2.go = "exit";
						}
					}
				break;

				case "escort":
					if (pchar.questTemp.WPU.Escort == "begin" || pchar.questTemp.WPU.Escort == "late" || pchar.questTemp.WPU.Escort == "win" || CheckAttribute(pchar, "questTemp.WPU.Escort.LevelUp")) { // если заняты
						dialog.text = "Unfortunately, I can't offer you anything of that kind. Drop in again in a couple of days.";
						link.l1 = "Alright, I'll do just that.";
						link.l1.go = "exit";
					} else { // если не заняты
						if (sti(pchar.questTemp.WPU.Escort.count) > 3 && drand(1) == 1) { // 2 уровень
							dialog.text = "You have already successfully escorted merchant vessels several times. I guess I have an assignment specifically for you.";
							link.l1 = "I am all ears.";
							link.l1.go = "Escort_LevelUp";
						} else { // 1 уровень
							if (sti(RealShips[sti(pchar.Ship.Type)].BaseType) == SHIP_GALEON_H && 2500 - makeint(GetCharacterFreeSpace(pchar, GOOD_RUM)) < 0 && !CheckAttribute(pchar, "questTemp.WPU.Fraht.TargetPortmanID")) { // если на ТГ
								dialog.text = "I have a job, just for you. In our raid on the port are two merchant ships. They should've already hit the road, but escort ship has got damage and stands in the port waiting for repair and won't be able to depart soon\nSo your ship is ideal for escort these ships, as I still need to place additional consignment in your hold. Payment will certainly be a double - for freight and for support.";
								link.l1 = "An interesting offer! I'll take it!";
								link.l1.go = "escort_bonus";
								link.l2 = "Thank you, but that's just not my kind of work.";
								link.l2.go = "exit";
							} else { // просто эскорт
								dialog.text = "I have a job just for you. Two merchant ships are lying off in our port at the moment - they need escort. I am offering you to escort these ships to their destination. Will you do that?";
								link.l1 = "An interesting offer! I'll take it!";
								link.l1.go = "escort";
								link.l2 = "Thank you, but that's just not my kind of work.";
								link.l2.go = "exit";
							}
						}
					}
				break;
			}
			break;
		}
		//ничего не подошло
		dialog.text = "Unfortunately, I can't offer you anything of that kind. Drop in again in a couple of days.";
		link.l1 = "Alright, I'll do just that.";
		link.l1.go = "exit";
		break;

///--> ------фрахт со свободным выбором пункта назначения, оплаты и вида груза из предложенного списка---------

		case "Fraht_begin":
			if (drand(4) < 4)
			{
				if (pchar.questTemp.WPU.Fraht == "begin" || pchar.questTemp.WPU.Fraht == "late" || pchar.questTemp.WPU.Fraht == "lost" || CheckAttribute(pchar, "questTemp.WPU.Escort.Bonus"))//проверка на занятость
				{
					dialog.Text = "But I have heard that your ship was already chartered. I cannot give you any more freights. Fulfill the commitments you have already taken.";
					link.l1 = "Yes, you're probably right.";
					Link.l1.go = "exit";
					break;
				}
				if (1500 - makeint(GetCharacterFreeSpace(pchar, GOOD_RUM)) > 0)//мало места - не даем
				{
					dialog.text = "You have too little space in your hold. I need more capacious ship for a freight. I suggest you checking at the store - the local merchant is frequently chartering vessels to deliver small batches of cargo.";
					link.l1 = "I see. Well, as you say.";
					link.l1.go = "exit";
					break;
				}
				if (pchar.questTemp.WPU.Fraht.count > 3 && rand(1) == 0)
				{
					dialog.text = "I don't have anything suitable at the moment. But you have already done several successful deliveries. I have a certain job which I'd like to assign specifically to you.";
					link.l1 = "I am listening. What kind of job?";
					link.l1.go = "Fraht_LevelUp";
					break;
				}
				dialog.Text = "Well, I can offer you several chartering opportunities.";
				link.l1 = "Let's see, then...";
				Link.l1.go = "Fraht_choise";
			}
			else
			{
				dialog.Text = "There are no more freights left for today. Come another day.";
				link.l1 = "Oh well.";
				Link.l1.go = "exit";
			}
		break;
	
		int iFrahtGoods1, iFrahtGoods2, iFrahtGoods3, iFrahtGoods;
		int iFrahtGoodsQty1, iFrahtGoodsQty2, iFrahtGoodsQty3;
		case "Fraht_choise":
			//выбираем города
			pchar.questTemp.WPU.Fraht.City1 = findCurrentCity1(npchar);
			pchar.questTemp.WPU.Fraht.City2 = findCurrentCity2(npchar);
			pchar.questTemp.WPU.Fraht.City3 = findCurrentCity3(npchar);
			//выбираем товары
			iFrahtGoods1 = drand(GOOD_PAPRIKA);
			iFrahtGoods2 = drand(GOOD_PAPRIKA-3);
			iFrahtGoods3 = drand(GOOD_PAPRIKA-7);
			pchar.questTemp.WPU.Fraht.Goods1 = iFrahtGoods1;
			pchar.questTemp.WPU.Fraht.Goods2 = iFrahtGoods2;
			pchar.questTemp.WPU.Fraht.Goods3 = iFrahtGoods3;
			//определим количество
			iFrahtGoodsQty1 = makeint(GetCharacterFreeSpace(pchar, iFrahtGoods1))/(1+frand(0.5));
			iFrahtGoodsQty2 = makeint(GetCharacterFreeSpace(pchar, iFrahtGoods2))/(1+frand(0.5));
			iFrahtGoodsQty3 = makeint(GetCharacterFreeSpace(pchar, iFrahtGoods3))/(1+frand(0.5));
			if (sti(iFrahtGoodsQty1) > 10000) iFrahtGoodsQty1 = 10000 + rand(500);
			if (sti(iFrahtGoodsQty2) > 10000) iFrahtGoodsQty2 = 10000 + rand(500);
			if (sti(iFrahtGoodsQty3) > 10000) iFrahtGoodsQty3 = 10000 + rand(500);
			pchar.questTemp.WPU.Fraht.GoodsQty1 = iFrahtGoodsQty1;
			pchar.questTemp.WPU.Fraht.GoodsQty2 = iFrahtGoodsQty2;
			pchar.questTemp.WPU.Fraht.GoodsQty3 = iFrahtGoodsQty3;
			pchar.questTemp.WPU.Fraht.StartCity = npchar.city;//город квестодателя
			pchar.questTemp.WPU.Fraht.Chance = rand(4);//форс-мажор
			//определим сроки с учетом рандома
			int daysQty1 = GetMaxDaysFromIsland2Island(GetArealByCityName(pchar.questTemp.WPU.Fraht.StartCity), GetArealByCityName(pchar.questTemp.WPU.Fraht.City1));
			int daysQty2 = GetMaxDaysFromIsland2Island(GetArealByCityName(pchar.questTemp.WPU.Fraht.StartCity), GetArealByCityName(pchar.questTemp.WPU.Fraht.City2));
			int daysQty3 = GetMaxDaysFromIsland2Island(GetArealByCityName(pchar.questTemp.WPU.Fraht.StartCity), GetArealByCityName(pchar.questTemp.WPU.Fraht.City3));
			pchar.questTemp.WPU.Fraht.DaysQty1 = makeint(sti(daysQty1)*(frand(1.3)+0.7));
			pchar.questTemp.WPU.Fraht.DaysQty2 = makeint(sti(daysQty2)*(frand(1.3)+0.7));
			pchar.questTemp.WPU.Fraht.DaysQty3 = makeint(sti(daysQty3)*(frand(1.3)+0.7));
			//установим цену исходя из объема груза, дальности и сроков
			pchar.questTemp.WPU.Fraht.Money1 = (makeint((sti(iFrahtGoodsQty1) * sti(Goods[iFrahtGoods1].Weight) / sti(Goods[iFrahtGoods1].Units))))*(sti(daysQty1)*2)*sti(daysQty1)/sti(pchar.questTemp.WPU.Fraht.DaysQty1);
			pchar.questTemp.WPU.Fraht.Money2 = (makeint((sti(iFrahtGoodsQty2) * sti(Goods[iFrahtGoods2].Weight) / sti(Goods[iFrahtGoods2].Units))))*(sti(daysQty2)*2)*sti(daysQty2)/sti(pchar.questTemp.WPU.Fraht.DaysQty2);
			pchar.questTemp.WPU.Fraht.Money3 = (makeint((sti(iFrahtGoodsQty3) * sti(Goods[iFrahtGoods3].Weight) / sti(Goods[iFrahtGoods3].Units))))*(sti(daysQty3)*2)*sti(daysQty3)/sti(pchar.questTemp.WPU.Fraht.DaysQty3);
			if (drand(5) < 4)//три варианта
			{
				dialog.text = "There are such variants:\n" +
					"cargo " + GetGoodsNameAlt(iFrahtGoods1)+ " in amount of " + FindRussianQtyString(iFrahtGoodsQty1) + " to the town of " + XI_ConvertString("Colony" + pchar.questTemp.WPU.Fraht.City1) + ", in " +  FindRussianDaysString(pchar.questTemp.WPU.Fraht.DaysQty1) + ". Payment - " + FindRussianMoneyString(sti(pchar.questTemp.WPU.Fraht.Money1)) + "\ncargo " + GetGoodsNameAlt(iFrahtGoods2)+ " in amount of " + FindRussianQtyString(iFrahtGoodsQty2) + " to the town of " + XI_ConvertString("Colony" + pchar.questTemp.WPU.Fraht.City2) + ", in " +  FindRussianDaysString(pchar.questTemp.WPU.Fraht.DaysQty2) + ". Payment - " + FindRussianMoneyString(sti(pchar.questTemp.WPU.Fraht.Money2)) + "\ncargo " + GetGoodsNameAlt(iFrahtGoods3)+ " in amount of " + FindRussianQtyString(iFrahtGoodsQty3) + " to the town of " + XI_ConvertString("Colony" + pchar.questTemp.WPU.Fraht.City3) + ", in " +  FindRussianDaysString(pchar.questTemp.WPU.Fraht.DaysQty3) + ". Payment - " + FindRussianMoneyString(sti(pchar.questTemp.WPU.Fraht.Money3)) + "\nWhat is your choice?";
				Link.l1 = "I will pick the second variant - charter to the town of " + XI_ConvertString("Colony" + pchar.questTemp.WPU.Fraht.City1) + " loaded with " + GetGoodsNameAlt(iFrahtGoods1)+ ".";
				Link.l1.go = "Fraht_Choise_1";
				Link.l2 = "I will pick the third variant - charter to the town of " + XI_ConvertString("Colony" + pchar.questTemp.WPU.Fraht.City2) + " loaded with " + GetGoodsNameAlt(iFrahtGoods2)+ ".";
				Link.l2.go = "Fraht_Choise_2";
				Link.l3 = "I will pick the third variant - charter to the town of " + XI_ConvertString("Colony" + pchar.questTemp.WPU.Fraht.City3) + " loaded with " + GetGoodsNameAlt(iFrahtGoods3)+ ".";
				Link.l3.go = "Fraht_Choise_3";
			}
			else //два варианта
			{
				dialog.text = "There are such variants:\n" +
					"cargo " + GetGoodsNameAlt(iFrahtGoods1)+ " in amount of " + FindRussianQtyString(iFrahtGoodsQty1) + " to the town of " + XI_ConvertString("Colony" + pchar.questTemp.WPU.Fraht.City1) + ", in " +  FindRussianDaysString(pchar.questTemp.WPU.Fraht.DaysQty1) + ". Payment - " + FindRussianMoneyString(sti(pchar.questTemp.WPU.Fraht.Money1)) + "\ncargo " + GetGoodsNameAlt(iFrahtGoods2)+ " in amount of " + FindRussianQtyString(iFrahtGoodsQty2) + " to the town of " + XI_ConvertString("Colony" + pchar.questTemp.WPU.Fraht.City2) + ", in " +  FindRussianDaysString(pchar.questTemp.WPU.Fraht.DaysQty2) + ". Payment - " + FindRussianMoneyString(sti(pchar.questTemp.WPU.Fraht.Money2)) + "\nWhat is your choice?";
				Link.l1 = "I will pick the first variant - charter to the town of " + XI_ConvertString("Colony" + pchar.questTemp.WPU.Fraht.City1) + " loaded with " + GetGoodsNameAlt(iFrahtGoods1)+ ".";
				Link.l1.go = "Fraht_Choise_1";
				Link.l2 = "I will pick the second variant - charter to the town of " + XI_ConvertString("Colony" + pchar.questTemp.WPU.Fraht.City2) + " loaded with " + GetGoodsNameAlt(iFrahtGoods2)+ ".";
				Link.l2.go = "Fraht_Choise_2";
			}
			Link.l4 = "Unfortunately, there's nothing suitable for me.";
			Link.l4.go = "exit";
			SaveCurrentNpcQuestDateParam(npchar, "work_date");
		break;
	
		case "Fraht_Choise_1":
			dialog.text = "Well, great! I'll process the necessary documents, and you can prepare your ship for loading.";
			link.l1 = "I will do my best!";
			link.l1.go = "Fraht_Forcemajor";
			AddCharacterGoods(pchar, sti(pchar.questTemp.WPU.Fraht.Goods1), sti(pchar.questTemp.WPU.Fraht.GoodsQty1));
			iFrahtGoods1 = pchar.questTemp.WPU.Fraht.Goods1;
			ReOpenQuestHeader("Fraht");
			AddQuestRecord("Fraht", "1");
			AddQuestUserData("Fraht", "sGoods", GetGoodsNameAlt(iFrahtGoods1));
			AddQuestUserData("Fraht", "sGoodQty", FindRussianQtyString(sti(pchar.questTemp.WPU.Fraht.GoodsQty1)));
			AddQuestUserData("Fraht", "sDay", FindRussianDaysString(sti(pchar.questTemp.WPU.Fraht.DaysQty1)));
			AddQuestUserData("Fraht", "sMoney", FindRussianMoneyString(sti(pchar.questTemp.WPU.Fraht.Money1)));
			AddQuestUserData("Fraht", "sStartCity", XI_ConvertString("Colony"+pchar.questTemp.WPU.Fraht.StartCity+"Gen"));
			AddQuestUserData("Fraht", "sTargetColony",XI_ConvertString("Colony"+pchar.questTemp.WPU.Fraht.City1+"Gen"));
			SetFunctionTimerCondition("FrahtTime_Over", 0, 0, sti(pchar.questTemp.WPU.Fraht.DaysQty1), false);
			pchar.questTemp.WPU.Fraht.TargetPortmanID = pchar.questTemp.WPU.Fraht.City1+"_portman";
			pchar.questTemp.WPU.Fraht.GoodsAverigePrice = sti(Goods[iFrahtGoods1].Cost);//цена единицы товара
			pchar.questTemp.WPU.Fraht.GoodsAverigeCost = sti(Goods[iFrahtGoods1].Cost)*sti(pchar.questTemp.WPU.Fraht.GoodsQty1);//средняя стоимость товара
			pchar.questTemp.WPU.Fraht.Goods = sti(pchar.questTemp.WPU.Fraht.Goods1);
			pchar.questTemp.WPU.Fraht.GoodsQty = sti(pchar.questTemp.WPU.Fraht.GoodsQty1);
			pchar.questTemp.WPU.Fraht.Money = sti(pchar.questTemp.WPU.Fraht.Money1);
		break;
	
		case "Fraht_Choise_2":
			dialog.text = "Well, great! I'll process the necessary documents, and you can prepare your ship for loading.";
			link.l1 = "I will do my best!";
			link.l1.go = "Fraht_Forcemajor";
			AddCharacterGoods(pchar, sti(pchar.questTemp.WPU.Fraht.Goods2), sti(pchar.questTemp.WPU.Fraht.GoodsQty2));
			iFrahtGoods2 = pchar.questTemp.WPU.Fraht.Goods2;
			ReOpenQuestHeader("Fraht");
			AddQuestRecord("Fraht", "1");
			AddQuestUserData("Fraht", "sGoods", GetGoodsNameAlt(iFrahtGoods2));
			AddQuestUserData("Fraht", "sGoodQty", FindRussianQtyString(sti(pchar.questTemp.WPU.Fraht.GoodsQty2)));
			AddQuestUserData("Fraht", "sDay", FindRussianDaysString(sti(pchar.questTemp.WPU.Fraht.DaysQty2)));
			AddQuestUserData("Fraht", "sMoney", FindRussianMoneyString(sti(pchar.questTemp.WPU.Fraht.Money2)));
			AddQuestUserData("Fraht", "sStartCity", XI_ConvertString("Colony"+pchar.questTemp.WPU.Fraht.StartCity+"Gen"));
			AddQuestUserData("Fraht", "sTargetColony",XI_ConvertString("Colony"+pchar.questTemp.WPU.Fraht.City2+"Gen"));
			SetFunctionTimerCondition("FrahtTime_Over", 0, 0, sti(pchar.questTemp.WPU.Fraht.DaysQty2), false);
			pchar.questTemp.WPU.Fraht.TargetPortmanID = pchar.questTemp.WPU.Fraht.City2+"_portman";
			pchar.questTemp.WPU.Fraht.GoodsAverigePrice = sti(Goods[iFrahtGoods2].Cost);//цена единицы товара
			pchar.questTemp.WPU.Fraht.GoodsAverigeCost = sti(Goods[iFrahtGoods2].Cost)*sti(pchar.questTemp.WPU.Fraht.GoodsQty2);//средняя стоимость товара
			pchar.questTemp.WPU.Fraht.Goods = sti(pchar.questTemp.WPU.Fraht.Goods2);
			pchar.questTemp.WPU.Fraht.GoodsQty = sti(pchar.questTemp.WPU.Fraht.GoodsQty2);
			pchar.questTemp.WPU.Fraht.Money = sti(pchar.questTemp.WPU.Fraht.Money2);
		break;
	
		case "Fraht_Choise_3":
			dialog.text = "Well, great! I'll process the necessary documents, and you can prepare your ship for loading.";
			link.l1 = "I will do my best!";
			link.l1.go = "Fraht_Forcemajor";
			AddCharacterGoods(pchar, sti(pchar.questTemp.WPU.Fraht.Goods3), sti(pchar.questTemp.WPU.Fraht.GoodsQty3));
			iFrahtGoods3 = pchar.questTemp.WPU.Fraht.Goods3;
			ReOpenQuestHeader("Fraht");
			AddQuestRecord("Fraht", "1");
			AddQuestUserData("Fraht", "sGoods", GetGoodsNameAlt(iFrahtGoods3));
			AddQuestUserData("Fraht", "sGoodQty", FindRussianQtyString(sti(pchar.questTemp.WPU.Fraht.GoodsQty3)));
			AddQuestUserData("Fraht", "sDay", FindRussianDaysString(sti(pchar.questTemp.WPU.Fraht.DaysQty3)));
			AddQuestUserData("Fraht", "sMoney", FindRussianMoneyString(sti(pchar.questTemp.WPU.Fraht.Money3)));
			AddQuestUserData("Fraht", "sStartCity", XI_ConvertString("Colony"+pchar.questTemp.WPU.Fraht.StartCity+"Gen"));
			AddQuestUserData("Fraht", "sTargetColony",XI_ConvertString("Colony"+pchar.questTemp.WPU.Fraht.City3+"Gen"));
			SetFunctionTimerCondition("FrahtTime_Over", 0, 0, sti(pchar.questTemp.WPU.Fraht.DaysQty3), false);
			pchar.questTemp.WPU.Fraht.TargetPortmanID = pchar.questTemp.WPU.Fraht.City3+"_portman";
			pchar.questTemp.WPU.Fraht.GoodsAverigePrice = sti(Goods[iFrahtGoods3].Cost);//цена единицы товара
			pchar.questTemp.WPU.Fraht.GoodsAverigeCost = sti(Goods[iFrahtGoods3].Cost)*sti(pchar.questTemp.WPU.Fraht.GoodsQty3);//средняя стоимость товара
			pchar.questTemp.WPU.Fraht.Goods = sti(pchar.questTemp.WPU.Fraht.Goods3);
			pchar.questTemp.WPU.Fraht.GoodsQty = sti(pchar.questTemp.WPU.Fraht.GoodsQty3);
			pchar.questTemp.WPU.Fraht.Money = sti(pchar.questTemp.WPU.Fraht.Money3);
		break;
	
		case "Fraht_Forcemajor":
			pchar.questTemp.WPU.Fraht = "begin";
			sld = characterFromId(pchar.questTemp.WPU.Fraht.TargetPortmanID);
			pchar.questTemp.WPU.Fraht.Nation = sld.nation;//нация получателя
			pchar.questTemp.WPU.Current.TargetIslandID = GetCharacterCurrentIslandId(sld);//ИД целевого ареала
			pchar.questTemp.WPU.Fraht.TargetCity = FindTownOnIsland(pchar.questTemp.WPU.Current.TargetIslandID);
			pchar.questTemp.WPU.Fraht.count = sti(pchar.questTemp.WPU.Fraht.count)+1;//считаем сделанные фрахты
			if (pchar.questTemp.WPU.Fraht.Chance > 3) TraderHunterOnMap();//запуск ДУ на глобалке
			if (pchar.questTemp.WPU.Fraht.Chance == 2) FrahtHunterOnSea();//создание ДУ в акватории
			DialogExit();
		break;
	
		case "Fraht_complete":
		ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
		if(sti(Pchar.Ship.Type) != SHIP_NOTUSED && ok)//проверка на наличие корабля в порту
		{
			iFrahtGoods = makeint(pchar.questTemp.WPU.Fraht.Goods);
			amount = sti(pchar.questTemp.WPU.Fraht.GoodsQty) - GetSquadronGoods(pchar, sti(pchar.questTemp.WPU.Fraht.Goods));
			if (amount > 0)
			{
				dialog.text = "Let's see, then. You were supposed to deliver a load of " + GetGoodsNameAlt(iFrahtGoods)+ " in amount of " + FindRussianQtyString(pchar.questTemp.WPU.Fraht.GoodsQty) + ". But I see that you've delivered not the entire shipment - you are " + FindRussianQtyString(sti(amount)) + " short.";
				link.l1 = "A thousand sharks! It must be those cursed rats! But don't you worry, " + GetAddress_FormToNPC(NPChar) + ", I will purchase the missing amount and turn in the entire batch.";
				link.l1.go = "Fraht_complete_3";
				break;
			}
			dialog.text = "Let's see, then. You were supposed to deliver a load of " + GetGoodsNameAlt(iFrahtGoods)+ " in amount of " + FindRussianQtyString(pchar.questTemp.WPU.Fraht.GoodsQty) + ". Correct?";
			link.l1 = "Absolutely correct, " + GetAddress_FormToNPC(NPChar) + ".";
			link.l1.go = "Fraht_complete_1";
		}
		else
		{
			dialog.text = "I don't see your ship in the port. Lie off and then come see me again - then we will talk.";
			link.l1 = "Alright, I'll do just that.";
			link.l1.go = "exit";
		}
		break;
	
		case "Fraht_complete_1":
			if (pchar.questTemp.WPU.Fraht == "late")//опоздали
			{
				iTime = makeint(GetQuestPastDayParam("questTemp.Fraht.Late"))+1;
				pchar.questTemp.WPU.Fraht.DayLate = iTime;
				pchar.questTemp.WPU.Fraht.PercentLate = iTime/0.2;
				pchar.questTemp.WPU.Fraht.Money = makeint(sti(pchar.questTemp.WPU.Fraht.Money) - sti(pchar.questTemp.WPU.Fraht.Money)*sti(pchar.questTemp.WPU.Fraht.PercentLate)/100);//снижаем оплату согласно числа дней опоздания
				dialog.text = "Hm... But you were " + FindRussianDaysString(iTime)+ " late. Therefore I must cut your payment for the freight. According to the contract, your fine is five percent of the entire some per each day of delay. Now please take your " + FindRussianMoneyString(sti(pchar.questTemp.WPU.Fraht.Money)) + ", and try to stick to the contract in the future.";
				link.l1 = "Well, it's something at least.";
				link.l1.go = "Fraht_complete_2";
				break;
			}
			dialog.text = "Thanks for your work. Please, take your payment - " + FindRussianMoneyString(sti(pchar.questTemp.WPU.Fraht.Money)) + ".";
			link.l1 = "Thanks!";
			link.l1.go = "Fraht_complete_2";
		break;
	
		case "Fraht_complete_2":
			if (pchar.questTemp.WPU.Fraht == "begin")
			{
				pchar.quest.FrahtTime_Over.over = "yes";
				AddQuestRecord("Fraht", "2");
			}
			else
			{
				pchar.quest.FrahtTime_FullOver.over = "yes";//снять второй таймер
				pchar.questTemp.WPU.Fraht.count = sti(pchar.questTemp.WPU.Fraht.count)-1;//опоздавший рейс не засчитываем
				AddQuestRecord("Fraht", "4");
				AddQuestUserData("Fraht", "sDay", FindRussianDaysString(pchar.questTemp.WPU.Fraht.DayLate));
				AddQuestUserData("Fraht", "sMoney", FindRussianMoneyString(sti(pchar.questTemp.WPU.Fraht.Money)));
			}
			RemoveCharacterGoods(pchar, sti(pchar.questTemp.WPU.Fraht.Goods), sti(pchar.questTemp.WPU.Fraht.GoodsQty));
			AddMoneyToCharacter(pchar, sti(pchar.questTemp.WPU.Fraht.Money));
			CloseQuestHeader("Fraht");
			DeleteAttribute(pchar, "questTemp.WPU.Fraht.TargetPortmanID");
			DeleteAttribute(pchar, "questTemp.WPU.Current.TargetIslandID");
			pchar.questTemp.WPU.Fraht = "complete";
			SaveCurrentNpcQuestDateParam(npchar, "work_date");
			AddCharacterExpToSkill(pchar, "Sailing", 100);//навигация
			AddCharacterExpToSkill(pchar, "Commerce", 100);//торговля
			AddCharacterExpToSkill(pchar, "Leadership", 50);//авторитет
			AddCharacterExpToSkill(pchar, "Fortune", 50);//везение
			ChangeCharacterComplexReputation(pchar,"nobility", 2);
			ChangeCharacterNationReputation(pchar, sti(pchar.questTemp.WPU.Fraht.Nation), 2);
			Group_DeleteGroup("Fraht_Attack");
			DialogExit();
		break;
	
		case "Fraht_complete_bad":
			dialog.text = "Have you delivered the cargo? Pretty. Actually, we had to purchase it by ourselves to turn in to the recipient! And it was quite costly, mind you. So, if you want to re-establish your goodwill, you will have to compensate our expenses and also pay the penalty. As for the cargo, you can keep it - we have no need of it anymore.";
			link.l1 = "Yes, sure. How much?";
			link.l1.go = "Fraht_complete_bad_1";
		break;
	
		case "Fraht_complete_bad_1":
			pchar.questTemp.WPU.Fraht.GoodsAverigeCost = sti(pchar.questTemp.WPU.Fraht.GoodsAverigeCost)*3;
			dialog.text = "Three times the cost of the goods. This amounts to " + FindRussianMoneyString(sti(pchar.questTemp.WPU.Fraht.GoodsAverigeCost)) + ".";
			if (sti(Pchar.money) >= sti(pchar.questTemp.WPU.Fraht.GoodsAverigeCost))
			{
				link.l1 = "That's quite a bit. But business is business. Fine, here's your money.";
				link.l1.go = "Fraht_complete_pay";
			}
			link.l2 = "Are you crazy? Demanding such an outrageous sum is the limit of greed! You won't get anything from me!";
			link.l2.go = "Fraht_complete_fail";
		break;
	
		case "Fraht_complete_pay":
			AddMoneyToCharacter(pchar, -sti(pchar.questTemp.WPU.Fraht.GoodsAverigeCost));
			dialog.text = "A wise decision. Now I can see that you're indeed a serious person. I guess we can still work together in the future.";
			link.l1 = "Thanks, and now I have to go.";
			link.l1.go = "exit";
			ChangeCharacterComplexReputation(pchar,"nobility", 12);
			ChangeCharacterNationReputation(pchar, sti(pchar.questTemp.WPU.Fraht.Nation), 30);
			if (CheckAttribute(pchar, "questTemp.WPU.Escort.Bonus"))
			{
				AddQuestRecord("Escort", "8");
				AddQuestUserData("Escort", "sMoney", FindRussianMoneyString(sti(pchar.questTemp.WPU.Fraht.GoodsAverigeCost)));
				CloseQuestHeader("Escort");
				pchar.questTemp.WPU.Escort = "complete";
				DeleteAttribute(pchar, "questTemp.WPU.Escort.TargetPortmanID");
				DeleteAttribute(pchar, "questTemp.WPU.Escort.Bonus");
			}
			else
			{
				AddQuestRecord("Fraht", "6");
				AddQuestUserData("Fraht", "sMoney", FindRussianMoneyString(sti(pchar.questTemp.WPU.Fraht.GoodsAverigeCost)));
				CloseQuestHeader("Fraht");
				pchar.questTemp.WPU.Fraht = "complete";
				DeleteAttribute(pchar, "questTemp.WPU.Fraht.TargetPortmanID");
			}
			DeleteAttribute(pchar, "questTemp.WPU.Current.TargetIslandID");
			SaveCurrentNpcQuestDateParam(npchar, "work_date");
			AddCharacterExpToSkill(pchar, "Sailing", 100);//навигация
			AddCharacterExpToSkill(pchar, "Commerce", 50);//торговля
			AddCharacterExpToSkill(pchar, "Leadership", 70);//авторитет
			AddCharacterExpToSkill(pchar, "Fortune", 70);//везение
		break;
	
		case "Fraht_complete_fail":
			dialog.text = "Oh, I see... Well, in that case you should never show your face again at any port authority of " + NationNameGenitive(sti(pchar.questTemp.WPU.Fraht.Nation)) + "! Get lost!";
			link.l1 = "I surely didn't miss much...";
			link.l1.go = "exit";
			if (CheckAttribute(pchar, "questTemp.WPU.Escort.Bonus"))
			{
				AddQuestRecord("Escort", "9");
				AddQuestUserData("Escort", "sMoney", FindRussianMoneyString(sti(pchar.questTemp.WPU.Fraht.GoodsAverigeCost)));
				CloseQuestHeader("Escort");
				pchar.questTemp.WPU.Escort = "complete";
				DeleteAttribute(pchar, "questTemp.WPU.Escort.TargetPortmanID");
				DeleteAttribute(pchar, "questTemp.WPU.Escort.Bonus");
			}
			else
			{
				AddQuestRecord("Fraht", "7");
				CloseQuestHeader("Fraht");
				DeleteAttribute(pchar, "questTemp.WPU.Fraht.TargetPortmanID");
			}
			DeleteAttribute(pchar, "questTemp.WPU.Current.TargetIslandID");
			pchar.questTemp.WPU.Fraht = "fail";
			ChangeCharacterComplexReputation(pchar,"nobility", -10);
		break;
	
		case "Fraht_complete_3":
			dialog.text = "Hurry up, the recipient already knows that your ship has arrived and he worries about his cargo.";
			link.l1 = "In that case I will not waste any more time!";
			link.l1.go = "exit";
		break;
	//фрахт <--
	
/// -------------------------------работа курьером по доставке почты-------------------------------------

		case "Postcureer":
			pchar.questTemp.WPU.Postcureer.City = findCurrentCity2(npchar);
			pchar.questTemp.WPU.Postcureer.StartCity = npchar.city;//город квестодателя
			pchar.questTemp.WPU.Postcureer.Chance = rand(4);//форс-мажор
			idaysQty = GetMaxDaysFromIsland2Island(GetArealByCityName(pchar.questTemp.WPU.Postcureer.StartCity), GetArealByCityName(pchar.questTemp.WPU.Postcureer.City));
			pchar.questTemp.WPU.Postcureer.DaysQty = makeint(sti(idaysQty)*(frand(0.3)+0.7)); 
			if (sti(pchar.questTemp.WPU.Postcureer.DaysQty) == 1) pchar.questTemp.WPU.Postcureer.DaysQty = 2;
			pchar.questTemp.WPU.Postcureer.Money = (sti(idaysQty)*1000)*sti(idaysQty)/sti(pchar.questTemp.WPU.Postcureer.DaysQty)*(1+frand(0.2));
			dialog.text = "This package must be delivered to the port authority in the city of " + XI_ConvertString("Colony" + pchar.questTemp.WPU.Postcureer.City) + ", for " +  FindRussianDaysString(pchar.questTemp.WPU.Postcureer.DaysQty) + ", and as soon as possible. Payment - " + FindRussianMoneyString(sti(pchar.questTemp.WPU.Postcureer.Money))".";
			link.l1 = "I agree!";
			link.l1.go = "Postcureer_1";
			link.l2 = "Hmm... But I'm not going that way. Sorry, but I have to refuse.";
			link.l2.go = "exit";
		break;
	
		case "Postcureer_1":
			dialog.text = "Excellent! I am counting on you. Here's the package.";
			link.l1 = "I will set sail at once!";
			link.l1.go = "exit";
			GiveItem2Character(pchar, "PostLetters");
			pchar.questTemp.WPU.Postcureer = "begin";
			pchar.questTemp.WPU.Postcureer.TargetPortmanID = pchar.questTemp.WPU.Postcureer.City +"_portman";//ИД портмана
			sld = characterFromId(pchar.questTemp.WPU.Postcureer.TargetPortmanID);
			pchar.questTemp.WPU.Postcureer.Nation = sld.nation;//нация получателя
			pchar.questTemp.WPU.Current.TargetIslandID = GetCharacterCurrentIslandId(sld);//ИД целевого ареала
			pchar.questTemp.WPU.Postcureer.EnemyNation = GetEnemyNationToMainCharacter();//вражеская нация
			while (sti(pchar.questTemp.WPU.Postcureer.EnemyNation) == PIRATE)
			{
				pchar.questTemp.WPU.Postcureer.EnemyNation = GetEnemyNationToMainCharacter();
			}
			pchar.questTemp.WPU.Postcureer.count = sti(pchar.questTemp.WPU.Postcureer.count)+1;//считаем сделанные доставки
			//запустить регату при счетчике > 4
			if (!CheckAttribute(pchar, "questTemp.RegataGo") && sti(pchar.questTemp.WPU.Postcureer.count) > 4)
			{
				pchar.questTemp.RegataGo = "true";
				pchar.questTemp.Regata.CureerCity = FindFriendCityToMC(true);//город, в котором вестовой подойдет
				if (pchar.questTemp.Regata.CureerCity == "PortRoyal") pchar.questTemp.Regata.CureerCity = "SentJons";
				pchar.quest.Regata_Cureer.win_condition.l1 = "location";
				pchar.quest.Regata_Cureer.win_condition.l1.location = pchar.questTemp.Regata.CureerCity+"_town";
				pchar.quest.Regata_Cureer.function = "PrepareToRegata";
				log_testinfo(pchar.questTemp.Regata.CureerCity);
			}
			if (pchar.questTemp.WPU.Postcureer.Chance > 3) EnemyNationHunterOnMap(false);//запуск перехватчиков на глобалке
			if (pchar.questTemp.WPU.Postcureer.Chance == 2) FrahtHunterOnSea();//создание перехватчиков в акватории
			ReOpenQuestHeader("Postcureer");
			AddQuestRecord("Postcureer", "1");
			AddQuestUserData("Postcureer", "sDay", FindRussianDaysString(sti(pchar.questTemp.WPU.Postcureer.DaysQty)));
			AddQuestUserData("Postcureer", "sMoney", FindRussianMoneyString(sti(pchar.questTemp.WPU.Postcureer.Money)));
			AddQuestUserData("Postcureer", "sStartCity", XI_ConvertString("Colony"+pchar.questTemp.WPU.Postcureer.StartCity+"Gen"));
			AddQuestUserData("Postcureer", "sTargetColony",XI_ConvertString("Colony"+pchar.questTemp.WPU.Postcureer.City+"Gen"));
			SetFunctionTimerCondition("PostcureerTime_Over", 0, 0, sti(pchar.questTemp.WPU.Postcureer.DaysQty), false);
		break;
	
		case "Postcureer_complete":
			if (pchar.questTemp.WPU.Postcureer == "late")//опоздали
			{
				iTime = makeint(GetQuestPastDayParam("questTemp.Postcureer.Late"))+1;
				pchar.questTemp.WPU.Postcureer.DayLate = iTime;
				pchar.questTemp.WPU.Postcureer.PercentLate = iTime/0.1;
				pchar.questTemp.WPU.Postcureer.Money = makeint(sti(pchar.questTemp.WPU.Postcureer.Money) - sti(pchar.questTemp.WPU.Postcureer.Money)*sti(pchar.questTemp.WPU.Postcureer.PercentLate)/100);//снижаем оплату согласно числа дней опоздания
				dialog.text = "Hm... But you were " + FindRussianDaysString(iTime)+ " late. Therefore I must cut your payment for the job. According to the contract, your fine is ten percent of the entire some per each day of delay. Now please, take your " + FindRussianMoneyString(sti(pchar.questTemp.WPU.Postcureer.Money)) + ", and try to stick to the contract in the future.";
				link.l1 = "Well, it's something at least.";
				link.l1.go = "Postcureer_complete_1";
				break;
			}
			dialog.text = "Thanks for your work. Please, take your payment - " + FindRussianMoneyString(sti(pchar.questTemp.WPU.Postcureer.Money)) + ".";
			link.l1 = "Thanks!";
			link.l1.go = "Postcureer_complete_1";
		break;
	
		case "Postcureer_complete_1":
			if (pchar.questTemp.WPU.Postcureer == "begin")
			{
				pchar.quest.PostcureerTime_Over.over = "yes";
				AddQuestRecord("Postcureer", "2");
			}
			else
			{
				pchar.quest.PostcureerTime_FullOver.over = "yes";//снять второй таймер
				pchar.questTemp.WPU.Postcureer.count = sti(pchar.questTemp.WPU.Postcureer.count)-1;//опоздавший рейс не засчитываем
				AddQuestRecord("Postcureer", "4");
				AddQuestUserData("Postcureer", "sDay", FindRussianDaysString(pchar.questTemp.WPU.Postcureer.DayLate));
				AddQuestUserData("Postcureer", "sMoney", FindRussianMoneyString(sti(pchar.questTemp.WPU.Postcureer.Money)));
			}
			RemoveItems(PChar, "PostLetters", 1);
			AddMoneyToCharacter(pchar, sti(pchar.questTemp.WPU.Postcureer.Money));
			CloseQuestHeader("Postcureer");
			DeleteAttribute(pchar, "questTemp.WPU.Postcureer.TargetPortmanID");
			DeleteAttribute(pchar, "questTemp.WPU.Current.TargetIslandID");
			pchar.questTemp.WPU.Postcureer = "complete";
			AddCharacterExpToSkill(pchar, "Sailing", 100);//навигация
			AddCharacterExpToSkill(pchar, "Sneak", 100);//скрытность
			AddCharacterExpToSkill(pchar, "Leadership", 100);//авторитет
			AddCharacterExpToSkill(pchar, "Fortune", 100);//везение
			ChangeCharacterComplexReputation(pchar,"nobility", 2);
			ChangeCharacterNationReputation(pchar, sti(pchar.questTemp.WPU.Postcureer.Nation), 2);
			Group_DeleteGroup("Fraht_Attack");
			SaveCurrentNpcQuestDateParam(npchar, "work_date");
			DialogExit();
		break;
	
		case "Postcureer_complete_bad":
			dialog.text = "And what shall we do with it now? People were waiting for it god knows when, and you've brought it just today. Alright, give it to me - perhaps, there will yet be some use out of it. And I hope you understand that no payment at all is due now.";
			link.l1 = "Of course, I do. Take your bundle. Farewell.";
			link.l1.go = "exit";
			RemoveItems(PChar, "PostLetters", 1);
			CloseQuestHeader("Postcureer");
			DeleteAttribute(pchar, "questTemp.WPU.Postcureer.TargetPortmanID");
			DeleteAttribute(pchar, "questTemp.WPU.Current.TargetIslandID");
			Group_DeleteGroup("Fraht_Attack");
			pchar.questTemp.WPU.Postcureer = "fail";
		break;
	
/// ---------------------------работа в качестве эскорта для торговых кораблей----------------------------

		case "escort":
			pchar.questTemp.WPU.Escort.ShipName1 = GenerateRandomNameToShip(sti(npchar.nation));//имена кораблей
			pchar.questTemp.WPU.Escort.ShipName2 = GenerateRandomNameToShip(sti(npchar.nation));
			pchar.questTemp.WPU.Escort.Goods1 = rand(GOOD_PAPRIKA);
			pchar.questTemp.WPU.Escort.Goods2 = rand(GOOD_PAPRIKA);
			pchar.questTemp.WPU.Escort.City = findCurrentCity1(npchar);//целевой город
			pchar.questTemp.WPU.Escort.StartCity = npchar.city;//город квестодателя
			pchar.questTemp.WPU.Escort.Chance = rand(4);//форс-мажор
			idaysQty = GetMaxDaysFromIsland2Island(GetArealByCityName(pchar.questTemp.WPU.Escort.StartCity), GetArealByCityName(pchar.questTemp.WPU.Escort.City));
			pchar.questTemp.WPU.Escort.DaysQty = makeint(sti(idaysQty)*(frand(0.5)+1)); 
			pchar.questTemp.WPU.Escort.Money = (sti(idaysQty)*2000)*sti(idaysQty)/sti(pchar.questTemp.WPU.Escort.DaysQty)*(1+frand(0.2));
			dialog.text = "So, you will need to escort ships '" + pchar.questTemp.WPU.Escort.ShipName1 + "' and '" + pchar.questTemp.WPU.Escort.ShipName2 + "' to the city of " + XI_ConvertString("Colony" + pchar.questTemp.WPU.Escort.City) + ", for " +  FindRussianDaysString(pchar.questTemp.WPU.Escort.DaysQty) + ". Payment - " + FindRussianMoneyString(sti(pchar.questTemp.WPU.Escort.Money))". Both ships must reach their destination safe and sound. You will turn in the ships to the official of the local port authority. He will also be the one to pay you for the job.";
			link.l1 = "Everything seems clear. Shall I proceed?";
			link.l1.go = "escort_1";
			link.l2 = "Hmm... But I'm not going that way. Sorry, but I have to refuse.";
			link.l2.go = "exit";
		break;
	
		case "escort_1":
			dialog.text = "Go ahead. Those ships are at your command at this point.";
			link.l1 = "I am setting sail, then!";
			link.l1.go = "escort_add_ships";
			pchar.questTemp.WPU.Escort = "begin";
			pchar.questTemp.WPU.Escort.ShipNation = npchar.nation;//нация отправителя
			pchar.questTemp.WPU.Escort.TargetPortmanID = pchar.questTemp.WPU.Escort.City +"_portman";//ИД портмана
			sld = characterFromId(pchar.questTemp.WPU.Escort.TargetPortmanID);
			pchar.questTemp.WPU.Escort.Nation = sld.nation;//нация получателя
			pchar.questTemp.WPU.Current.TargetIslandID = GetCharacterCurrentIslandId(sld);//ИД целевого ареала
			pchar.questTemp.WPU.Escort.EnemyNation = GetEnemyNationToMainCharacter();//вражеская нация
			while (sti(pchar.questTemp.WPU.Postcureer.EnemyNation) == PIRATE)
			{
				pchar.questTemp.WPU.Escort.EnemyNation = GetEnemyNationToMainCharacter();
			}
			pchar.questTemp.WPU.Escort.count = sti(pchar.questTemp.WPU.Escort.count)+1;//считаем сделанные эскорты
			if (pchar.questTemp.WPU.Escort.Chance > 3) EnemyNationHunterOnMap(false);//запуск перехватчиков на глобалке
			if (pchar.questTemp.WPU.Escort.Chance == 3) TraderHunterOnMap();//запуск ДУ на глобалке
			if (pchar.questTemp.WPU.Escort.Chance < 2) FrahtHunterOnSea();//создание перехватчиков в акватории
			ReOpenQuestHeader("Escort");
			AddQuestRecord("Escort", "1");
			AddQuestUserData("Escort", "sDay", FindRussianDaysString(sti(pchar.questTemp.WPU.Escort.DaysQty)));
			AddQuestUserData("Escort", "sMoney", FindRussianMoneyString(sti(pchar.questTemp.WPU.Escort.Money)));
			AddQuestUserData("Escort", "sStartCity", XI_ConvertString("Colony"+pchar.questTemp.WPU.Escort.StartCity+"Gen"));
			AddQuestUserData("Escort", "sTargetColony",XI_ConvertString("Colony"+pchar.questTemp.WPU.Escort.City+"Gen"));
			SetFunctionTimerCondition("EscortTime_Over", 0, 0, sti(pchar.questTemp.WPU.Escort.DaysQty), false);
		break;
	
		case "escort_add_ships":
			int iGoods1, iGoods2, iSpace1, iSpace2, ShipType, Rank;
			int iNation = pchar.questTemp.WPU.Escort.ShipNation;
			int iLifeday = sti(pchar.questTemp.WPU.Escort.DaysQty)+10;
			string sTemp;
	        for (i=1; i<=2; i++)
	        {
				switch (rand(2))
				{
					case 0:  
						ShipType = SHIP_FLEUT;     					
						Rank = 10 + rand(5);
					break; 		
					case 1:  
						ShipType = SHIP_GALEON_L;			
						Rank = 15 + rand(5);
					break; 
					case 2: 
						ShipType = SHIP_PINNACE; 				
						Rank = 20 + rand(5);
					break;
				}
				if (i == 1) sTemp = pchar.questTemp.WPU.Escort.ShipName1;
				if (i == 2) sTemp = pchar.questTemp.WPU.Escort.ShipName2;
				if (i == 2) ShipType = SHIP_FLEUT;//один всегда флейт
	            sld = GetCharacter(NPC_GenerateCharacter("EscortCaptain_"+i, "trader_"+(rand(15)+1), "man", "man", Rank, iNation, iLifeday, true, "citizen"));
				FantomMakeSmallSailor(sld, ShipType, sTemp, CANNON_TYPE_CANNON_LBS16, 10+rand(10), 10+rand(10), 10+rand(10), 10+rand(10), 10+rand(10));
				DeleteAttribute(sld, "SaveItemsForDead");
				DeleteAttribute(sld, "DontClearDead");
				SetCharacterGoods(sld, GOOD_FOOD, 400+rand(200));
				SetCharacterGoods(sld, GOOD_MEDICAMENT, 60+rand(30));
	            iGoods1 = sti(pchar.questTemp.WPU.Escort.Goods1);
				iSpace1 = GetCharacterFreeSpace(sld, iGoods1);
				iSpace1 = makeint(iSpace1/2 + rand(iSpace1/2));
				iGoods2 = sti(pchar.questTemp.WPU.Escort.Goods2);
				iSpace2 = GetCharacterFreeSpace(sld, iGoods2);
				iSpace2 = makeint(iSpace2/2 + rand(iSpace2/2));
				if (i == 1) SetCharacterGoods(sld, iGoods1, iSpace1);
				if (i == 2) SetCharacterGoods(sld, iGoods2, iSpace2);
				sld.CompanionEnemyEnable = false; //всегда друзья
	            SetCompanionIndex(pchar, -1, sti(sld.index));
				sld.loyality = MAX_LOYALITY;
				SetCharacterRemovable(sld, false);
				sld.Dialog.Filename = "Common_portman.c";
				sld.dialog.currentnode = "Escort_companion";
				pchar.quest.Escort_fail.win_condition.l1 = "NPC_Death";
				pchar.quest.Escort_fail.win_condition.l1.character = "EscortCaptain_1";
				pchar.quest.Escort_fail.win_condition.l2 = "NPC_Death";
				pchar.quest.Escort_fail.win_condition.l2.character = "EscortCaptain_2";
				pchar.quest.Escort_fail.function = "Escort_failed";
	        }
			if (pchar.questTemp.WPU.Escort.Chance > 3) EnemyNationHunterOnMap(false);//запуск перехватчиков на глобалке
			if (pchar.questTemp.WPU.Escort.Chance == 3) TraderHunterOnMap();//запуск ДУ на глобалке
			if (pchar.questTemp.WPU.Escort.Chance < 2) FrahtHunterOnSea();//создание перехватчиков в акватории
			DialogExit();
		break;
	
		case "Escort_complete":
		ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
		if(sti(Pchar.Ship.Type) != SHIP_NOTUSED && ok)//проверка на наличие корабля в порту
		{
			//проверяем, все ли корабли
			if (GetCharacterIndex("EscortCaptain_1") == -1 || GetCharacterIndex("EscortCaptain_2") == -1)
			{
				dialog.text = "Hmm... I only see one ship in your escort. Is this correct?";
				link.l1 = "Yes, " + GetAddress_FormToNPC(NPChar) + ". Another one was sunk in a battle with an enemy squadron.";
				if (CheckAttribute(pchar, "questTemp.WPU.Escort.Bonus")) 
				{
					link.l1.go = "EscortBonus_complete_fail";
				}
				else
				{
					link.l1.go = "Escort_complete_fail";
				}
				break;
			}
			iGoods = pchar.questTemp.WPU.Escort.Goods;
			if (CheckAttribute(pchar, "questTemp.WPU.Escort.Bonus")) 
			{
				//pchar.questTemp.WPU.Escort.Money = sti(pchar.questTemp.WPU.Escort.Money)+sti(pchar.questTemp.WPU.Escort.BonusMoney);
				pchar.questTemp.WPU.Escort.Money = sti(pchar.questTemp.WPU.Escort.TotalMoney);
				amount = sti(pchar.questTemp.WPU.Escort.GoodsQty) - GetSquadronGoods(pchar, sti(pchar.questTemp.WPU.Escort.Goods));
				if (amount > 0)
				{
					dialog.text = "Alright, then. You were supposed to escort ships and deliver the cargo of " + GetGoodsNameAlt(iGoods)+ " in amount of " + FindRussianQtyString(sti(pchar.questTemp.WPU.Escort.GoodsQty)) + ". But I see that you've delivered not the entire shipment - you are " + FindRussianQtyString(sti(amount)) + " short.";
					link.l1 = "A thousand sharks! It must be those cursed rats! But don't you worry, " + GetAddress_FormToNPC(NPChar) + ", I will purchase the missing amount and turn in the entire batch.";
					link.l1.go = "Fraht_complete_3";
					break;
				}
			}
			if (pchar.questTemp.WPU.Escort == "late")//опоздали
			{
				iTime = makeint(GetQuestPastDayParam("questTemp.Escort.Late"))+1;
				pchar.questTemp.WPU.Escort.DayLate = iTime;
				pchar.questTemp.WPU.Escort.PercentLate = iTime/0.1;
				pchar.questTemp.WPU.Escort.Money = makeint(sti(pchar.questTemp.WPU.Escort.Money) - sti(pchar.questTemp.WPU.Escort.Money)*sti(pchar.questTemp.WPU.Escort.PercentLate)/100);//снижаем оплату согласно числа дней опоздания
				dialog.text = "Hm... But you were " + FindRussianDaysString(iTime)+ " late. Therefore I must cut your payment for the job. According to the contract, your fine is ten percent of the entire some per each day of delay. Now please, take your " + FindRussianMoneyString(sti(pchar.questTemp.WPU.Escort.Money)) + ", and try to stick to the contract in the future.";
				link.l1 = "Well, it's something at least.";
				link.l1.go = "Escort_complete_1";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.WPU.Escort.Bonus")) 
			{
				dialog.text = "Alright, then. You were supposed to escort ships and deliver the cargo of " + GetGoodsNameAlt(iGoods)+ " in amount of " + FindRussianQtyString(sti(pchar.questTemp.WPU.Escort.GoodsQty)) + ". Thanks for your work. Please, take your payment - " + FindRussianMoneyString(sti(pchar.questTemp.WPU.Escort.Money)) + ".";
			}
			else
			{
				dialog.text = "Thanks for your work. Please, take your payment - " + FindRussianMoneyString(sti(pchar.questTemp.WPU.Escort.Money)) + ".";
			}
			link.l1 = "Thanks!";
			link.l1.go = "Escort_complete_1";
		}
		else
		{
			dialog.text = "I don't see your ship in the port. Lie off and then come see me again - then we will talk.";
			link.l1 = "Alright, I'll do just that.";
			link.l1.go = "exit";
		}
		break;
	
		case "Escort_complete_1":
			pchar.quest.Escort_fail.over = "yes";//снять прерывание
			if (pchar.questTemp.WPU.Escort == "begin")
			{
				pchar.quest.EscortTime_Over.over = "yes";//снять таймер
				AddQuestRecord("Escort", "2");
			}
			else
			{
				pchar.questTemp.WPU.Escort.count = sti(pchar.questTemp.WPU.Escort.count)-1;//опоздавший рейс не засчитываем
				pchar.quest.EscortTime_FullOver.over = "yes";//снять второй таймер
				if (CheckAttribute(pchar, "questTemp.WPU.Escort.Bonus"))
				{
					pchar.questTemp.WPU.Fraht.count = sti(pchar.questTemp.WPU.Fraht.count)-1;//опоздавший рейс не засчитываем
				}
				AddQuestRecord("Escort", "4");
				AddQuestUserData("Escort", "sDay", FindRussianDaysString(pchar.questTemp.WPU.Escort.DayLate));
				AddQuestUserData("Escort", "sMoney", FindRussianMoneyString(sti(pchar.questTemp.WPU.Escort.Money)));
			}
			RemoveCharacterCompanion(Pchar, characterFromID("EscortCaptain_1"));//удалим компаньонов
			RemoveCharacterCompanion(Pchar, characterFromID("EscortCaptain_2"));
			AddMoneyToCharacter(pchar, sti(pchar.questTemp.WPU.Escort.Money));
			if (CheckAttribute(pchar, "questTemp.WPU.Escort.Bonus")) RemoveCharacterGoods(pchar, sti(pchar.questTemp.WPU.Escort.Goods), sti(pchar.questTemp.WPU.Escort.GoodsQty));
			CloseQuestHeader("Escort");
			DeleteAttribute(pchar, "questTemp.WPU.Escort.TargetPortmanID");
			DeleteAttribute(pchar, "questTemp.WPU.Current.TargetIslandID");
			DeleteAttribute(pchar, "questTemp.WPU.Escort.Bonus");
			pchar.questTemp.WPU.Escort = "complete";
			SaveCurrentNpcQuestDateParam(npchar, "work_date");
			AddCharacterExpToSkill(pchar, "Sailing", 100);//навигация
			AddCharacterExpToSkill(pchar, "Defence", 100);//защита
			AddCharacterExpToSkill(pchar, "Leadership", 100);//авторитет
			AddCharacterExpToSkill(pchar, "Fortune", 100);//везение
			ChangeCharacterComplexReputation(pchar,"nobility", 2);
			ChangeCharacterNationReputation(pchar, sti(pchar.questTemp.WPU.Escort.Nation), 2);
			Group_DeleteGroup("Fraht_Attack");
			DialogExit();
		break;
	
		case "escort_bonus":
			pchar.questTemp.WPU.Escort.ShipName1 = GenerateRandomNameToShip(sti(npchar.nation));//имена кораблей
			pchar.questTemp.WPU.Escort.ShipName2 = GenerateRandomNameToShip(sti(npchar.nation));
			pchar.questTemp.WPU.Escort.Goods = 	drand(GOOD_PAPRIKA);//для ГГ
			pchar.questTemp.WPU.Escort.Goods1 = drand(GOOD_PAPRIKA-3);
			pchar.questTemp.WPU.Escort.Goods2 = drand(GOOD_PAPRIKA-5);
			iGoods = pchar.questTemp.WPU.Escort.Goods;
			iGoodsQty = makeint(GetCharacterFreeSpace(pchar, iGoods))-(50+rand(100));//количество груза
			pchar.questTemp.WPU.Escort.GoodsQty = iGoodsQty;
			pchar.questTemp.WPU.Escort.City = findCurrentCity1(npchar);//целевой город
			pchar.questTemp.WPU.Escort.StartCity = npchar.city;//город квестодателя
			pchar.questTemp.WPU.Escort.Chance = rand(4);//форс-мажор
			idaysQty = GetMaxDaysFromIsland2Island(GetArealByCityName(pchar.questTemp.WPU.Escort.StartCity), GetArealByCityName(pchar.questTemp.WPU.Escort.City));
			pchar.questTemp.WPU.Escort.DaysQty = makeint(sti(idaysQty)*(frand(0.5)+1));//дни
			pchar.questTemp.WPU.Escort.Money = (sti(idaysQty)*2000)*sti(idaysQty)/sti(pchar.questTemp.WPU.Escort.DaysQty)*(1+frand(0.2));//оплата за сопровождение
			pchar.questTemp.WPU.Escort.BonusMoney = (makeint((sti(iGoodsQty) * sti(Goods[iGoods].Weight) / sti(Goods[iGoods].Units))))*(sti(idaysQty)*2)*sti(idaysQty)/sti(pchar.questTemp.WPU.Escort.DaysQty);//оплата за фрахт
			pchar.questTemp.WPU.Escort.TotalMoney = sti(pchar.questTemp.WPU.Escort.Money)+sti(pchar.questTemp.WPU.Escort.BonusMoney); // общая сумма
			dialog.text = "So, you will need to escort ships '" + pchar.questTemp.WPU.Escort.ShipName1 + "' and '" + pchar.questTemp.WPU.Escort.ShipName2 + "' to the city of " + XI_ConvertString("Colony" + pchar.questTemp.WPU.Escort.City) + ", for " +  FindRussianDaysString(pchar.questTemp.WPU.Escort.DaysQty) + ". Payment - " + FindRussianMoneyString(sti(pchar.questTemp.WPU.Escort.Money))+ "\nAlso on your ship, I place the load of " + GetGoodsNameAlt(iGoods)+ " in amount of " + FindRussianQtyString(iGoodsQty) + ". Payment for the delivery - " + FindRussianMoneyString(sti(pchar.questTemp.WPU.Escort.BonusMoney))+".";
			link.l1 = "Everything seems clear. Shall I proceed?";
			link.l1.go = "escort_bonus_1";
			link.l2 = "Hmm... But I'm not going that way. Sorry, but I have to refuse.";
			link.l2.go = "exit";
		break;
	
		case "escort_bonus_1":
			dialog.text = "Excellent! Take command of the squadron.";
			link.l1 = "I am setting sail, then!";
			link.l1.go = "escort_add_ships";
			iGoods = pchar.questTemp.WPU.Escort.Goods;
			AddCharacterGoods(pchar, sti(pchar.questTemp.WPU.Escort.Goods), sti(pchar.questTemp.WPU.Escort.GoodsQty));
			pchar.questTemp.WPU.Escort = "begin";
			pchar.questTemp.WPU.Escort.Bonus = "true";
			pchar.questTemp.WPU.Escort.ShipNation = npchar.nation;//нация отправителя
			pchar.questTemp.WPU.Escort.TargetPortmanID = pchar.questTemp.WPU.Escort.City +"_portman";//ИД портмана
			sld = characterFromId(pchar.questTemp.WPU.Escort.TargetPortmanID);
			pchar.questTemp.WPU.Escort.Nation = sld.nation;//нация получателя
			pchar.questTemp.WPU.Current.TargetIslandID = GetCharacterCurrentIslandId(sld);//ИД целевого ареала
			pchar.questTemp.WPU.Escort.EnemyNation = GetEnemyNationToMainCharacter();//вражеская нация
			while (sti(pchar.questTemp.WPU.Postcureer.EnemyNation) == PIRATE)
			{
				pchar.questTemp.WPU.Escort.EnemyNation = GetEnemyNationToMainCharacter();
			}
			pchar.questTemp.WPU.Escort.count = sti(pchar.questTemp.WPU.Escort.count)+1;//считаем сделанные эскорты
			pchar.questTemp.WPU.Fraht.count = sti(pchar.questTemp.WPU.Fraht.count)+1;//считаем сделанные фрахты
			if (pchar.questTemp.WPU.Escort.Chance > 3) EnemyNationHunterOnMap(false);//запуск перехватчиков на глобалке
			if (pchar.questTemp.WPU.Escort.Chance == 3) TraderHunterOnMap();//запуск ДУ на глобалке
			if (pchar.questTemp.WPU.Escort.Chance < 3) FrahtHunterOnSea();//создание перехватчиков в акватории
			ReOpenQuestHeader("Escort");
			AddQuestRecord("Escort", "6");
			AddQuestUserData("Escort", "sDay", FindRussianDaysString(sti(pchar.questTemp.WPU.Escort.DaysQty)));
			AddQuestUserData("Escort", "sMoney", FindRussianMoneyString(sti(pchar.questTemp.WPU.Escort.Money)));
			AddQuestUserData("Escort", "sStartCity", XI_ConvertString("Colony"+pchar.questTemp.WPU.Escort.StartCity+"Gen"));
			AddQuestUserData("Escort", "sTargetColony",XI_ConvertString("Colony"+pchar.questTemp.WPU.Escort.City));
			AddQuestUserData("Escort", "sGoods", GetGoodsNameAlt(iGoods));
			AddQuestUserData("Escort", "sGoodQty", FindRussianQtyString(sti(pchar.questTemp.WPU.Escort.GoodsQty)));
			AddQuestUserData("Escort", "sMoney1", FindRussianMoneyString(sti(pchar.questTemp.WPU.Escort.BonusMoney)));
			pchar.questTemp.WPU.Fraht.GoodsAverigePrice = sti(Goods[iGoods].Cost);//цена единицы товара
			pchar.questTemp.WPU.Fraht.GoodsAverigeCost = sti(Goods[iGoods].Cost)*sti(pchar.questTemp.WPU.Escort.GoodsQty);//средняя стоимость товара
			SetFunctionTimerCondition("EscortTime_Over", 0, 0, sti(pchar.questTemp.WPU.Escort.DaysQty), false);
		break;
	
		case "Escort_complete_fail":
			dialog.text = "Unbelievable! And what did we need you for? How could you allow this to happen?! I hope you understand that a reward is now out of question.";
			link.l1 = "Of course, I do... Well, best regards.";
			link.l1.go = "exit";
			pchar.quest.Escort_fail.over = "yes";//снять прерывание
			pchar.quest.EscortTime_Over.over = "yes";//снять прерывание // patch-2
			if (GetCharacterIndex("EscortCaptain_1") == -1) RemoveCharacterCompanion(pchar, characterFromID("EscortCaptain_2"));
			else RemoveCharacterCompanion(pchar, characterFromID("EscortCaptain_1"));
			AddQuestRecord("Escort", "11");
			CloseQuestHeader("Escort");
			pchar.questTemp.WPU.Escort.count = sti(pchar.questTemp.WPU.Escort.count)-1;//рейс не засчитываем
			DeleteAttribute(pchar, "questTemp.WPU.Escort.TargetPortmanID");
			DeleteAttribute(pchar, "questTemp.WPU.Current.TargetIslandID");
			pchar.questTemp.WPU.Escort = "complete";
			SaveCurrentNpcQuestDateParam(npchar, "work_date");
			AddCharacterExpToSkill(pchar, "Sailing", 50);//навигация
			AddCharacterExpToSkill(pchar, "Defence", 150);//защита
			AddCharacterExpToSkill(pchar, "Fortune", 50);//везение
			Group_DeleteGroup("Fraht_Attack");
		break;
	
		case "EscortBonus_complete_fail":
			if (GetCharacterIndex("EscortCaptain_1") == -1) RemoveCharacterCompanion(pchar, characterFromID("EscortCaptain_2"));
			else RemoveCharacterCompanion(pchar, characterFromID("EscortCaptain_1"));//удалим компаньона
			pchar.quest.Escort_fail.over = "yes";//снять прерывание
			amount = sti(pchar.questTemp.WPU.Escort.GoodsQty) - GetSquadronGoods(pchar, sti(pchar.questTemp.WPU.Escort.Goods));
			pchar.questTemp.WPU.Escort.GoodsQty = GetSquadronGoods(pchar, sti(pchar.questTemp.WPU.Escort.Goods));
			if (pchar.questTemp.WPU.Escort == "begin")
			{
				pchar.quest.EscortTime_Over.over = "yes";//снять таймер
				pchar.questTemp.WPU.Escort.MinusMoney = makeint(sti(pchar.questTemp.WPU.Escort.BonusMoney) - sti(pchar.questTemp.WPU.Fraht.GoodsAverigePrice)*sti(amount));
				if (sti(pchar.questTemp.WPU.Escort.MinusMoney) < 0) amount = 101;
				if (amount > 0 && amount <= 100)
				{
					pchar.questTemp.WPU.Escort.BonusMoney = sti(pchar.questTemp.WPU.Escort.MinusMoney);
					dialog.text = "Unbelievable! And what did we need you for? How could you allow this to happen?! I hope you understand that a reward for the escort is now out of question... Not only that, but you're short of cargo as well - " + FindRussianQtyString(sti(amount)) + "\nIn general, I pay you a fee only for the freight, less the value of the missing items, for what you have ever taken the goods in acceptable condition. Get your " + FindRussianMoneyString(sti(pchar.questTemp.WPU.Escort.BonusMoney))+ " and you can go wherever you like.";
					link.l1 = "Well, it's something at least.";
					link.l1.go = "EscortBonus_complete_fail_1";
					break;
				}
				if (amount > 100)
				{
					dialog.text = "Incredible! And what did we need you for? How could you allow this to happen?! I think you understand that about any remuneration for maintenance can be no question ... Yes, and you load a huge loss\nI do not have time to wait until you are acquiring the missing amount. So you have to offset the cost of shipping the money in full - " + FindRussianMoneyString(sti(pchar.questTemp.WPU.Fraht.GoodsAverigeCost))+ ". Cargo itself leave for yourself.";
					if (sti(pchar.money) >= sti(pchar.questTemp.WPU.Fraht.GoodsAverigeCost))
					{
						link.l1 = "Alright, don't get too steamed up. Here's your money.";
						link.l1.go = "EscortBonus_complete_fail_2";
					}
					link.l2 = "Have you all gone crazy? This is literal extortion! I won't give you anything!";
					link.l2.go = "EscortBonus_complete_fail_3";
					break;
				}
				dialog.text = "Incredible! And what did we need you for? How could you allow this to happen?! I think you understand that about any remuneration for maintenance can be no question\nIn general, I pay you a fee only for the freight for the goods that you have ever taken. Get your " + FindRussianMoneyString(sti(pchar.questTemp.WPU.Escort.BonusMoney))+ " and you can go wherever you like.";
				link.l1 = "Well, it's something at least.";
				link.l1.go = "EscortBonus_complete_fail_1";
				break;
			}
			if (pchar.questTemp.WPU.Escort == "late")
			{
				pchar.quest.EscortTime_FullOver.over = "yes";//снять второй таймер
				iTime = makeint(GetQuestPastDayParam("questTemp.Escort.Late"))+1;
				pchar.questTemp.WPU.Escort.DayLate = iTime;
				pchar.questTemp.WPU.Escort.PercentLate = iTime/0.1;
				pchar.questTemp.WPU.Escort.BonusMoney = makeint(sti(pchar.questTemp.WPU.Escort.BonusMoney) - sti(pchar.questTemp.WPU.Escort.BonusMoney)*sti(pchar.questTemp.WPU.Escort.PercentLate)/100);//снижаем оплату согласно числа дней опоздания
				if (amount > 0)
				{
					dialog.text = "Unbelievable! And what did we need you for? How could you allow this to happen?! I hope you understand that a reward for the escort is now out of question... You've lost a ship, you arrived " + FindRussianDaysString(iTime)+ " late, and not only that, but you're short of cargo as well - " + FindRussianQtyString(sti(amount)) + "\nI do not have time to wait until you are acquiring the missing amount. So you have to offset the cost of shipping the money in full " + FindRussianMoneyString(sti(pchar.questTemp.WPU.Fraht.GoodsAverigeCost))+ ". As for the cargo, you can keep it.";
					if (sti(pchar.money) >= sti(pchar.questTemp.WPU.Fraht.GoodsAverigeCost))
					{
						link.l1 = "Alright, don't get too steamed up. Here's your money.";
						link.l1.go = "EscortBonus_complete_fail_2";
					}
					link.l2 = "Have you all gone crazy? This is literal extortion! I won't give you anything!";
					link.l2.go = "EscortBonus_complete_fail_3";
					break;
				}
				dialog.text = "Unbelievable! And what did we need you for? How could you allow this to happen?! I hope you understand that a reward for the escort is now out of question... Besides, you delayed by " + FindRussianDaysString(iTime)+ "\nSo I had to reduce the amount of payment for the freight. Under the agreement, the penalty is 10 percent of the amount for each day of delay. Now, please, your " + FindRussianMoneyString(sti(pchar.questTemp.WPU.Escort.BonusMoney)) + ", and you can go.";
				link.l1 = "Well, it's something at least.";
				link.l1.go = "EscortBonus_complete_fail_1";
				break;
			}
		break;
	
		case "EscortBonus_complete_fail_1"://потеряли корабль, время и груз в норме или частично
			AddQuestRecord("Escort", "12");
			AddQuestUserData("Escort", "sMoney", FindRussianMoneyString(sti(pchar.questTemp.WPU.Escort.BonusMoney)));
			CloseQuestHeader("Escort");
			AddMoneyToCharacter(pchar, sti(pchar.questTemp.WPU.Escort.BonusMoney));
			RemoveCharacterGoods(pchar, sti(pchar.questTemp.WPU.Escort.Goods), sti(pchar.questTemp.WPU.Escort.GoodsQty));
			pchar.questTemp.WPU.Escort.count = sti(pchar.questTemp.WPU.Escort.count)-1;//рейс не засчитываем
			DeleteAttribute(pchar, "questTemp.WPU.Escort.TargetPortmanID");
			DeleteAttribute(pchar, "questTemp.WPU.Current.TargetIslandID");
			DeleteAttribute(pchar, "questTemp.WPU.Escort.Bonus");
			pchar.questTemp.WPU.Escort = "complete";
			SaveCurrentNpcQuestDateParam(npchar, "work_date");
			AddCharacterExpToSkill(pchar, "Sailing", 50);//навигация
			AddCharacterExpToSkill(pchar, "Defence", 150);//защита
			AddCharacterExpToSkill(pchar, "Fortune", 50);//везение
			AddCharacterExpToSkill(pchar, "Commerce", 100);//торговля
			Group_DeleteGroup("Fraht_Attack");
			DialogExit();
		break;
	
		case "EscortBonus_complete_fail_2"://потеряли корабль и груз, время норма или нет, мир
			AddQuestRecord("Escort", "13");
			AddQuestUserData("Escort", "sMoney", FindRussianMoneyString(sti(pchar.questTemp.WPU.Fraht.GoodsAverigeCost)));
			CloseQuestHeader("Escort");
			AddMoneyToCharacter(pchar, -sti(pchar.questTemp.WPU.Fraht.GoodsAverigeCost));
			pchar.questTemp.WPU.Escort.count = sti(pchar.questTemp.WPU.Escort.count)-1;//рейс не засчитываем
			pchar.questTemp.WPU.Escort.count = sti(pchar.questTemp.WPU.Fraht.count)-1;//рейс не засчитываем
			DeleteAttribute(pchar, "questTemp.WPU.Escort.TargetPortmanID");
			DeleteAttribute(pchar, "questTemp.WPU.Current.TargetIslandID");
			DeleteAttribute(pchar, "questTemp.WPU.Escort.Bonus");
			pchar.questTemp.WPU.Escort = "complete";
			SaveCurrentNpcQuestDateParam(npchar, "work_date");
			AddCharacterExpToSkill(pchar, "Sailing", 50);//навигация
			AddCharacterExpToSkill(pchar, "Defence", 150);//защита
			AddCharacterExpToSkill(pchar, "Fortune", 50);//везение
			AddCharacterExpToSkill(pchar, "Commerce", 50);//торговля
			Group_DeleteGroup("Fraht_Attack");
			DialogExit();
		break;
	
		case "EscortBonus_complete_fail_3"://потеряли корабль и груз, время норма или нет, война
			dialog.text = "Oh, I see... Well, in that case you should never show your face again at any port authority of " + NationNameGenitive(sti(pchar.questTemp.WPU.Escort.Nation)) + "! Get lost!";
			link.l1 = "I surely didn't miss much...";
			link.l1.go = "exit";
			AddQuestRecord("Escort", "14");
			AddQuestUserData("Escort", "sMoney", FindRussianMoneyString(sti(pchar.questTemp.WPU.Fraht.GoodsAverigeCost)));
			CloseQuestHeader("Escort");
			pchar.questTemp.WPU.Escort.count = 0;//счетчик в ноль
			pchar.questTemp.WPU.Escort.count = 0;//счетчик в ноль
			DeleteAttribute(pchar, "questTemp.WPU.Escort.TargetPortmanID");
			DeleteAttribute(pchar, "questTemp.WPU.Current.TargetIslandID");
			DeleteAttribute(pchar, "questTemp.WPU.Escort.Bonus");
			pchar.questTemp.WPU.Escort = "complete";
			pchar.questTemp.WPU.Fraht = "fail";
			ChangeCharacterComplexReputation(pchar,"nobility", -10);
			ChangeCharacterHunterScore(pchar, NationShortName(sti(pchar.questTemp.WPU.Escort.Nation)) + "hunter", 30);
			pchar.questTemp.WPU.Fraht.Nation = pchar.questTemp.WPU.Escort.Nation;
			SaveCurrentNpcQuestDateParam(npchar, "work_date");
			Group_DeleteGroup("Fraht_Attack");
		break;
	
		case "Escort_fail"://потеряли 2 корабля
			dialog.text = "This is very, very bad! What have we hired you for, can you tell me? To guard the ships? Or just to hang around?";
			link.l1 = "I understand. The enemy was simply too strong, and... but what's the point of arguing - what had happened, had already happened. But the cargo - the cargo is still there! So let's sort it out.";
			link.l1.go = "Escort_fail_complete";
		break;
	
		case "Escort_fail_complete":
			iFrahtGoods = makeint(pchar.questTemp.WPU.Escort.Goods);
			amount = sti(pchar.questTemp.WPU.Escort.GoodsQty) - GetSquadronGoods(pchar, sti(pchar.questTemp.WPU.Escort.Goods));
			if (amount > 0)
			{
				dialog.text = "Let's see, then. You were supposed to deliver a load of " + GetGoodsNameAlt(iFrahtGoods)+ " in amount of " + FindRussianQtyString(pchar.questTemp.WPU.Escort.GoodsQty) + ". But I see that you've delivered not the entire shipment - you are " + FindRussianQtyString(sti(amount)) + " short.";
				link.l1 = "A thousand sharks! It must be those cursed rats! But don't you worry, " + GetAddress_FormToNPC(NPChar) + ", I will purchase the missing amount and turn in the entire batch.";
				link.l1.go = "Fraht_complete_3";
				break;
			}
			dialog.text = "Let's see, then. You were supposed to deliver a load of " + GetGoodsNameAlt(iFrahtGoods)+ " in amount of " + FindRussianQtyString(pchar.questTemp.WPU.Escort.GoodsQty) + ". Correct?";
			link.l1 = "Absolutely correct, " + GetAddress_FormToNPC(NPChar) + ".";
			link.l1.go = "Escort_fail_complete_1";
		break;
	
		case "Escort_fail_complete_1":
			DeleteAttribute(pchar, "questTemp.WPU.Escort.Bonus");
			pchar.questTemp.WPU.Escort.Money = makeint(sti(pchar.questTemp.WPU.Escort.BonusMoney)/2);
			if (pchar.questTemp.WPU.Escort == "late")//опоздали
			{
				iTime = makeint(GetQuestPastDayParam("questTemp.Escort.Late"))+1;
				pchar.questTemp.WPU.Escort.DayLate = iTime;
				pchar.questTemp.WPU.Escort.PercentLate = iTime/0.1;
				pchar.questTemp.WPU.Escort.Money = makeint(sti(pchar.questTemp.WPU.Escort.Money) - sti(pchar.questTemp.WPU.Escort.Money)*sti(pchar.questTemp.WPU.Escort.PercentLate)/100);//снижаем оплату согласно числа дней опоздания
				dialog.text = "Hmm... You not only lost the ships which were entrusted to you, but you also delayed by " + FindRussianDaysString(iTime)+ ". So I had to reduce the amount of payment for the freight. Since you were not able to save the caravan, pay for the freight I halved, and this is the most that I can pay you\nIn addition, according to the contract, the penalty is 10 percent of the amount for each day of delay. Now, please, your " + FindRussianMoneyString(sti(pchar.questTemp.WPU.Escort.Money)) + ", and you can go.";
				link.l1 = "Well, it's something at least.";
				link.l1.go = "Escort_fail_complete_2";
				break;
			}
			dialog.text = "Well, even though I am extremely upset that you could not protect entrusted ships, at least you delivered the goods. Since you were not able to save the caravan pay for the freight I halved, and this is the most that I can pay you\nGet your payment - " + FindRussianMoneyString(sti(pchar.questTemp.WPU.Escort.Money)) + " and you can go wherever you like.";
			link.l1 = "Well, it's something at least.";
			link.l1.go = "Escort_fail_complete_2";
		break;
	
		case "Escort_fail_complete_2":
			if (pchar.questTemp.WPU.Escort == "begin")
			{
				pchar.quest.EscortTime_Over.over = "yes";
				AddQuestRecord("Escort", "17");
				AddQuestUserData("Escort", "sMoney", FindRussianMoneyString(sti(pchar.questTemp.WPU.Escort.Money)));
			}
			else
			{
				pchar.quest.EscortTime_FullOver.over = "yes";//снять второй таймер
				AddQuestRecord("Escort", "18");
				AddQuestUserData("Escort", "sDay", FindRussianDaysString(pchar.questTemp.WPU.Escort.DayLate));
				AddQuestUserData("Escort", "sMoney", FindRussianMoneyString(sti(pchar.questTemp.WPU.Escort.Money)));
			}
			pchar.questTemp.WPU.Fraht.count = sti(pchar.questTemp.WPU.Fraht.count)-1;//фейловый рейс не засчитываем
			RemoveCharacterGoods(pchar, sti(pchar.questTemp.WPU.Escort.Goods), sti(pchar.questTemp.WPU.Escort.GoodsQty));
			AddMoneyToCharacter(pchar, sti(pchar.questTemp.WPU.Escort.Money));
			CloseQuestHeader("Escort");
			DeleteAttribute(pchar, "questTemp.WPU.Escort.TargetPortmanID");
			DeleteAttribute(pchar, "questTemp.WPU.Current.TargetIslandID");
			pchar.questTemp.WPU.Escort = "complete";
			SaveCurrentNpcQuestDateParam(npchar, "work_date");
			AddCharacterExpToSkill(pchar, "Sailing", 50);//навигация
			AddCharacterExpToSkill(pchar, "Commerce", 50);//торговля
			AddCharacterExpToSkill(pchar, "Fortune", 50);//везение
			Group_DeleteGroup("Fraht_Attack");
			DialogExit();
		break;
	
//-------------------------------------задания 2 уровня для курьера---------------------------------------------
		case "Postcureer_LevelUp":
			pchar.questTemp.WPU.Postcureer.City = findCurrentCity2(npchar);//целевой город
			pchar.questTemp.WPU.Postcureer.StartCity = npchar.city;//город квестодателя
			idaysQty = GetMaxDaysFromIsland2Island(GetArealByCityName(pchar.questTemp.WPU.Postcureer.StartCity), GetArealByCityName(pchar.questTemp.WPU.Postcureer.City));
			pchar.questTemp.WPU.Postcureer.DaysQty = makeint(sti(idaysQty)*(frand(0.3)+0.6));//дни
			pchar.questTemp.WPU.Postcureer.Money = (sti(idaysQty)*3000)*sti(idaysQty)/sti(pchar.questTemp.WPU.Postcureer.DaysQty)*(1+frand(0.2));//оплата
			pchar.questTemp.WPU.Postcureer.Chance = rand(4);//форс-мажор
			pchar.questTemp.WPU.Postcureer.StartNation = npchar.nation;//нация отправителя
			pchar.questTemp.WPU.Postcureer.TargetPortmanID = pchar.questTemp.WPU.Postcureer.City +"_portman";//ИД портмана
			sld = characterFromId(pchar.questTemp.WPU.Postcureer.TargetPortmanID);
			pchar.questTemp.WPU.Postcureer.Nation = sld.nation;//нация получателя
			pchar.questTemp.WPU.Current.TargetIslandID = GetCharacterCurrentIslandId(sld);//ИД целевого ареала
			pchar.questTemp.WPU.Postcureer.EnemyNation = GetEnemyNationToMainCharacter();//вражеская нация
			while (sti(pchar.questTemp.WPU.Postcureer.EnemyNation) == PIRATE)
			{
				pchar.questTemp.WPU.Postcureer.EnemyNation = GetEnemyNationToMainCharacter();
			}

			switch (rand(3))
			{
				case 0:
					dialog.text = "You will need to deliver an urgent official dispatch for the governor of the town of "+XI_ConvertString("Colony"+pchar.questTemp.WPU.Postcureer.City+"Gen")+" not later than "+FindRussianDaysString(sti(pchar.questTemp.WPU.Postcureer.DaysQty))+". Be very careful - our enemies might be hunting that dispatch as well. Payment for the delivery - "+FindRussianMoneyString(sti(pchar.questTemp.WPU.Postcureer.Money))+".";
					link.l1 = "I agree!";
					link.l1.go = "Postcureer_LevelUp_Go";
					link.l2 = "No, I guess I'll pass.";
					link.l2.go = "Postcureer_LevelDown";
					pchar.questTemp.WPU.Postcureer.TargetPortmanID = pchar.questTemp.WPU.Postcureer.City +"_Mayor";//ИД губера
					if (pchar.questTemp.WPU.Postcureer.TargetPortmanID == "Villemstad_Mayor") pchar.questTemp.WPU.Postcureer.TargetPortmanID = "hol_guber"; // фикс Матиаса Бека #717
					pchar.questTemp.WPU.Current.Add = "a dispatch for the governor";
					pchar.questTemp.WPU.Current.Item = "letter_2";//предмет
					pchar.questTemp.WPU.Current.Itemdescr = "itmdescr_letter_2_PortmanLevelUp1";//описание
				break;
			
				case 1:
					dialog.text = "You will need to deliver these papers for the store owner of "+XI_ConvertString("Colony"+pchar.questTemp.WPU.Postcureer.City+"Gen")+" not later than "+FindRussianDaysString(sti(pchar.questTemp.WPU.Postcureer.DaysQty))+". This is the latest summary of the prices in stores all over the archipelago - a valuable commercial document. Care should be taken - competitors may well arrange a hunt. Payment for the delivery - "+FindRussianMoneyString(sti(pchar.questTemp.WPU.Postcureer.Money))+".";
					link.l1 = "I agree!";
					link.l1.go = "Postcureer_LevelUp_Go";
					link.l2 = "No, I guess I'll pass.";
					link.l2.go = "Postcureer_LevelDown";
					pchar.questTemp.WPU.Postcureer.TargetPortmanID = pchar.questTemp.WPU.Postcureer.City +"_trader";//ИД торговца
//					pchar.questTemp.WPU.Current.Add = "сводку цен для хозяина магазина";
					pchar.questTemp.WPU.Current.Add = "a price list for the store owner";     // LDH 23Jan17 translated
					pchar.questTemp.WPU.Current.Item = "letter_2";//предмет
					pchar.questTemp.WPU.Current.Itemdescr = "itmdescr_letter_2_PortmanLevelUp2";//описание
				break;
			
				case 2:
					dialog.text = "You will need to deliver this bundle of documents for the usurer in the town of "+XI_ConvertString("Colony"+pchar.questTemp.WPU.Postcureer.City+"Gen")+" no later than "+FindRussianDaysString(sti(pchar.questTemp.WPU.Postcureer.DaysQty))+". Here is a very important information about currency exchange rates and stock prices. Be very careful - this package is already interested in some shady characters. Payment fro the delivery - "+FindRussianMoneyString(sti(pchar.questTemp.WPU.Postcureer.Money))+".";
					link.l1 = "I agree!";
					link.l1.go = "Postcureer_LevelUp_Go";
					link.l2 = "No, I guess I'll pass.";
					link.l2.go = "Postcureer_LevelDown";
					pchar.questTemp.WPU.Postcureer.TargetPortmanID = pchar.questTemp.WPU.Postcureer.City +"_usurer";//ИД ростовщика
//					pchar.questTemp.WPU.Current.Add = "пакет с деловой информацией для ростовщика";
					pchar.questTemp.WPU.Current.Add = "a packet of information for the moneylender";   // LDH 23Jan17 translated
					pchar.questTemp.WPU.Current.Item = "letter_2";//предмет
					pchar.questTemp.WPU.Current.Itemdescr = "itmdescr_letter_2_PortmanLevelUp3";//описание
				break;
			
				case 3:
					dialog.text = "You should deliver this bundle to the dock master in the town of "+XI_ConvertString("Colony"+pchar.questTemp.WPU.Postcureer.City+"Gen")+" no later than "+FindRussianDaysString(sti(pchar.questTemp.WPU.Postcureer.DaysQty))+". It contains blueprints for the new "+RandPhraseSimple(LinkRandPhrase("brig","corvette","frigate"), LinkRandPhrase("flute","pinnace","galleon"))+", employing unique technological designs. I hope you do understand that there are other... interested parties, so you'll have to act discreetly. Payment for the delivery - "+FindRussianMoneyString(sti(pchar.questTemp.WPU.Postcureer.Money))+".";
					link.l1 = "I agree!";
					link.l1.go = "Postcureer_LevelUp_Go";
					link.l2 = "No, I guess I'll pass.";
					link.l2.go = "Postcureer_LevelDown";
					pchar.questTemp.WPU.Postcureer.TargetPortmanID = pchar.questTemp.WPU.Postcureer.City +"_shipyarder";//ИД верфиста
					pchar.questTemp.WPU.Current.Add = "the draft of a new ship for the owner of the shipyard";
					pchar.questTemp.WPU.Current.Item = "ShipyardsMap";//предмет
					pchar.questTemp.WPU.Current.Itemdescr = "itmdescr_ShipyardsMap_PortmanLevelUp4";//описание
				break;
			}
		break;
	
		case "Postcureer_LevelUp_Go":
			dialog.text = "Then take the documents and set sail. Best of luck... and may the Almighty be watching over you.";
			link.l1 = "Thanks!";
			link.l1.go = "Forsmajor_choose";
			pchar.questTemp.WPU.Postcureer = "begin";
			pchar.questTemp.WPU.Postcureer.LevelUp = "true";
			pchar.questTemp.WPU.Postcureer.count = sti(pchar.questTemp.WPU.Postcureer.count) + 1;
			//запустить регату при счетчике > 4
			if (!CheckAttribute(pchar, "questTemp.RegataGo") && sti(pchar.questTemp.WPU.Postcureer.count) > 4)
			{
				pchar.questTemp.RegataGo = "true";
				pchar.questTemp.Regata.CureerCity = FindFriendCityToMC(true);//город, в котором вестовой подойдет
				if (pchar.questTemp.Regata.CureerCity == "PortRoyal") pchar.questTemp.Regata.CureerCity = "SentJons";
				pchar.quest.Regata_Cureer.win_condition.l1 = "location";
				pchar.quest.Regata_Cureer.win_condition.l1.location = pchar.questTemp.Regata.CureerCity+"_town";
				pchar.quest.Regata_Cureer.function = "PrepareToRegata";
				log_testinfo(pchar.questTemp.Regata.CureerCity);
			}
			GiveItem2Character(pchar, pchar.questTemp.WPU.Current.Item);
			ChangeItemDescribe(pchar.questTemp.WPU.Current.Item, pchar.questTemp.WPU.Current.Itemdescr);
			ReOpenQuestHeader("Postcureer");
			AddQuestRecord("Postcureer", "6");
			AddQuestUserData("Postcureer", "sDay", FindRussianDaysString(sti(pchar.questTemp.WPU.Postcureer.DaysQty)));
			AddQuestUserData("Postcureer", "sMoney", FindRussianMoneyString(sti(pchar.questTemp.WPU.Postcureer.Money)));
			AddQuestUserData("Postcureer", "sStartCity", XI_ConvertString("Colony"+pchar.questTemp.WPU.Postcureer.StartCity+"Gen"));
			AddQuestUserData("Postcureer", "sTargetColony",XI_ConvertString("Colony"+pchar.questTemp.WPU.Postcureer.City+"Gen"));
			AddQuestUserData("Postcureer", "sText", pchar.questTemp.WPU.Current.Add);
			SetFunctionTimerCondition("PostcureerTime_Over", 0, 0, sti(pchar.questTemp.WPU.Postcureer.DaysQty), false);
		break;
	
		case "Postcureer_LevelDown":
			dialog.text = "Pity, indeed... Actually, offers of that kind are usually not tossed up. But it's your call, anyway.";
			link.l1 = "Yes, that's my call, " + GetAddress_FormToNPC(NPChar) + ".";
			link.l1.go = "exit";
			pchar.questTemp.WPU.Postcureer.count = sti(pchar.questTemp.WPU.Postcureer.count) - 1;//за отказ от спецзадания счетчик скрутим
		break;
	
		case "Forsmajor_choose":
			switch (sti(pchar.questTemp.WPU.Postcureer.Chance))
			{
				case 0://охотники в городе прибытия + ДУ
					pchar.quest.Postcureer_Hunter.win_condition.l1 = "Location";
					pchar.quest.Postcureer_Hunter.win_condition.l1.location = pchar.questTemp.WPU.Postcureer.City + "_town";
					pchar.quest.Postcureer_Hunter.function = "PostcureerGopHuntersOnLand";
					TraderHunterOnMap();
				break;
		
				case 1://создание скоростного перехватчика на глобалке
					EnemyNationHunterOnMap(true);
				break;
		
				case 2://запуск ДУ на глобалке и в порту прибытия
					TraderHunterOnMap();
					FrahtHunterOnSea();
				break;
		
				case 3://наемники в стартовом городе
					pchar.quest.Postcureer_Hunter.win_condition.l1 = "Location";
					pchar.quest.Postcureer_Hunter.win_condition.l1.location = pchar.questTemp.WPU.Postcureer.StartCity + "_town";
					pchar.quest.Postcureer_Hunter.function = "PostcureerProfHuntersOnLand";
				break;
		
				case 4://агент
					pchar.quest.Postcureer_Hunter.win_condition.l1 = "Location";
					pchar.quest.Postcureer_Hunter.win_condition.l1.location = pchar.questTemp.WPU.Postcureer.StartCity + "_town";
					pchar.quest.Postcureer_Hunter.function = "PostcureerAgent";
				break;
			}
			DialogExit();
		break;

		case "Postcureer_complete_fail":
			dialog.text = "Damn it! So they've tracked you, after all. A pity you're not a soldier, captain - in that case things might have turned out differently... What did they look like?";
			link.l1 = "Two strong stout men in black with half-masks on their faces, armed with poleaxes and double-barreled guns...";
			link.l1.go = "Postcureer_complete_fail_1";
		break;

		case "Postcureer_complete_fail_1":
			dialog.text = "I will notify the governor immediately to start looking for them. Alright, see you, " + GetAddress_Form(NPChar) + ". Again, it's a pity you're not a soldier...";
			link.l1 = "I am really sorry, " + GetAddress_FormToNPC(NPChar) + ", for what's happened. Well, farewell.";
			link.l1.go = "exit";
			if (pchar.questTemp.WPU.Postcureer == "begin") pchar.quest.PostcureerTime_Over.over = "yes";//снять таймер
			if (pchar.questTemp.WPU.Postcureer == "late") pchar.quest.PostcureerTime_FullOver.over = "yes";//снять второй таймер
			CloseQuestHeader("Postcureer");
			ChangeCharacterComplexReputation(pchar,"nobility", -2);
			pchar.questTemp.WPU.Postcureer.count = sti(pchar.questTemp.WPU.Postcureer.count)-3;//скрутим счетчик
			DeleteAttribute(pchar, "questTemp.WPU.Postcureer.TargetPortmanID");
			DeleteAttribute(pchar, "questTemp.WPU.Current");
			DeleteAttribute(pchar, "questTemp.WPU.Postcureer.LevelUp");
			DeleteAttribute(pchar, "questTemp.WPU.Postcureer.fail");
			pchar.questTemp.WPU.Postcureer = "complete";
		break;
	
//----------------------------------------задания 2 уровня фрахт------------------------------------------

	case "Fraht_LevelUp":
		rColony = GetColonyByIndex(FindColony(npchar.city));
		pchar.questTemp.WPU.Fraht.StartCity = npchar.city;//город квестодателя
		pchar.questTemp.WPU.Fraht.Nation = npchar.nation;//нация получателя
		switch (rand(4))//для тестов
		{
			case 0:
				pchar.questTemp.WPU.Fraht.Goods = GOOD_CHOCOLATE + drand(makeint(GOOD_TOBACCO - GOOD_CHOCOLATE));
				iGoods = pchar.questTemp.WPU.Fraht.Goods;
				iGoodsQty = 3000 + sti(pchar.rank)*30*(drand(9)+1);
				pchar.questTemp.WPU.Fraht.GoodsQty = iGoodsQty;
				pchar.questTemp.WPU.Fraht.GoodsAverigePrice = sti(Goods[iGoods].Cost)*2;//двойная цена единицы товара
				pchar.questTemp.WPU.Fraht.Money = sti(Goods[iGoods].Cost)*sti(pchar.questTemp.WPU.Fraht.GoodsQty)*2;//двойная стоимость товара
				pchar.questTemp.WPU.Current.Add = "double";
				// 08Mar17 "month" was "moths"
				dialog.text = "A demand for a certain merchandise has recently dramatically increased in our colony. It's none at the stores anymore. I would like to ask you to deliver to me " + GetGoodsNameAlt(iGoods)+ " in amount of " + FindRussianQtyString(iGoodsQty) + ", and I am willing to pay double - " + FindRussianMoneyString(sti(pchar.questTemp.WPU.Fraht.GoodsAverigePrice)) + " per item. This will amount to " + FindRussianMoneyString(sti(pchar.questTemp.WPU.Fraht.Money)) + ". Oh, and try to meet the deadline of one month - I won't be able to wait for it any longer.";
				link.l1 = "Alright, I'll accept this mission.";
				link.l1.go = "Fraht_LevelUp_Go";
				link.l2 = "I am sorry to disappoint you, but I cannot do it at this moment.";
				link.l2.go = "Fraht_LevelDown";
				SetNull2StoreGood(rColony, sti(pchar.questTemp.WPU.Fraht.Goods));
			break;
		
			case 1:
				pchar.questTemp.WPU.Fraht.Goods = GOOD_EBONY + drand(makeint(GOOD_CINNAMON - GOOD_EBONY));
				iGoods = pchar.questTemp.WPU.Fraht.Goods;
				iGoodsQty = 1500 + sti(pchar.rank)*20*(drand(9)+1);
				pchar.questTemp.WPU.Fraht.GoodsQty = iGoodsQty;
				pchar.questTemp.WPU.Fraht.GoodsAverigePrice = sti(Goods[iGoods].Cost)*2;//двойная цена единицы товара
				pchar.questTemp.WPU.Fraht.Money = sti(Goods[iGoods].Cost)*sti(pchar.questTemp.WPU.Fraht.GoodsQty)*2;//двойная стоимость товара
				pchar.questTemp.WPU.Current.Add = "double";
				// 08Mar17 "month" was "moths"
				dialog.text = "A demand for a certain merchandise has recently dramatically increased in our colony. It's none at the stores anymore. I would like to ask you to deliver to me " + GetGoodsNameAlt(iGoods)+ " in amount of " + FindRussianQtyString(iGoodsQty) + ", and I am willing to pay double - " + FindRussianMoneyString(sti(pchar.questTemp.WPU.Fraht.GoodsAverigePrice)) + " per item. This will amount to " + FindRussianMoneyString(sti(pchar.questTemp.WPU.Fraht.Money)) + ". Oh, and try to meet the deadline of one month - I won't be able to wait for it any longer.";
				link.l1 = "Alright, I'll accept this mission.";
				link.l1.go = "Fraht_LevelUp_Go";
				link.l2 = "I am sorry to disappoint you, but I cannot do it at this moment.";
				link.l2.go = "Fraht_LevelDown";
				SetNull2StoreGood(rColony, sti(pchar.questTemp.WPU.Fraht.Goods));
			break;
		
			case 2:
				pchar.questTemp.WPU.Fraht.Goods = GOOD_BOMBS + drand(makeint(GOOD_POWDER - GOOD_BOMBS));
				iGoods = pchar.questTemp.WPU.Fraht.Goods;
				iGoodsQty = 15000 + sti(pchar.rank)*300*(drand(9)+1);
				pchar.questTemp.WPU.Fraht.GoodsQty = iGoodsQty;
				pchar.questTemp.WPU.Fraht.GoodsAverigePrice = sti(Goods[iGoods].Cost)*3;//тройная цена единицы товара
				pchar.questTemp.WPU.Fraht.Money = makeint((sti(Goods[iGoods].Cost)*sti(pchar.questTemp.WPU.Fraht.GoodsQty)*3)/20);//тройная стоимость товара
				pchar.questTemp.WPU.Current.Add = "triple";
				// 08Mar17 "month" was "moths"
				dialog.text = "The arsenal of our colony drastically lacks of " + GetGoodsNameAlt(iGoods)+ ". It's none at the stores anymore. I would like to ask you to deliver to me " + GetGoodsNameAlt(iGoods)+ " in amount of " + FindRussianQtyString(iGoodsQty) + ", and I am willing to pay triple - " + FindRussianMoneyString(sti(pchar.questTemp.WPU.Fraht.GoodsAverigePrice)) + " per item. This will amount to " + FindRussianMoneyString(sti(pchar.questTemp.WPU.Fraht.Money)) + ". Oh, and try to meet the deadline of one month - I won't be able to wait for it any longer.";
				link.l1 = "Alright, I'll accept this mission.";
				link.l1.go = "Fraht_LevelUp_Go";
				link.l2 = "I am sorry to disappoint you, but I cannot do it at this moment.";
				link.l2.go = "Fraht_LevelDown";
				SetNull2StoreGood(rColony, sti(pchar.questTemp.WPU.Fraht.Goods));
			break;
		
			case 3:
				pchar.questTemp.WPU.Fraht.Goods = GOOD_MEDICAMENT;
				iGoods = pchar.questTemp.WPU.Fraht.Goods;
				iGoodsQty = 7000 + sti(pchar.rank)*300*(drand(9)+1);
				pchar.questTemp.WPU.Fraht.GoodsQty = iGoodsQty;
				pchar.questTemp.WPU.Fraht.GoodsAverigePrice = sti(Goods[iGoods].Cost)*3;//тройная цена единицы товара
				pchar.questTemp.WPU.Fraht.Money = makeint((sti(Goods[iGoods].Cost)*sti(pchar.questTemp.WPU.Fraht.GoodsQty)*3)/30);//тройная стоимость товара
				pchar.questTemp.WPU.Current.Add = "triple";
				// 08Mar17 "month" was "moths"
				dialog.text = "After the recent outbreak of fever in our colony we are lacking medicinal supplies - and there are already none even at the stores. The governor fears for the safety of the town. I would like to ask you to deliver to me " + GetGoodsNameAlt(iGoods)+ " in amount of " + FindRussianQtyString(iGoodsQty) + ", and I am willing to pay triple - " + FindRussianMoneyString(sti(pchar.questTemp.WPU.Fraht.GoodsAverigePrice)) + " per pack. This will amount to " + FindRussianMoneyString(sti(pchar.questTemp.WPU.Fraht.Money)) + ". Oh, and try to meet the deadline of one month - I won't be able to wait for it any longer.";
				link.l1 = "Alright, I'll accept this mission.";
				link.l1.go = "Fraht_LevelUp_Go";
				link.l2 = "I am sorry to disappoint you, but I cannot do it at this moment.";
				link.l2.go = "Fraht_LevelDown";
				SetNull2StoreGood(rColony, sti(pchar.questTemp.WPU.Fraht.Goods));
			break;
		
			case 4:
				pchar.questTemp.WPU.Fraht.Goods = GOOD_FOOD;
				iGoods = pchar.questTemp.WPU.Fraht.Goods;
				iGoodsQty = 15000 + sti(pchar.rank)*300*(drand(9)+1);
				pchar.questTemp.WPU.Fraht.GoodsQty = iGoodsQty;
				pchar.questTemp.WPU.Fraht.GoodsAverigePrice = sti(Goods[iGoods].Cost)*2;//двойная цена единицы товара
				pchar.questTemp.WPU.Fraht.Money = makeint((sti(Goods[iGoods].Cost)*sti(pchar.questTemp.WPU.Fraht.GoodsQty)*2)/10);//двойная стоимость товара
				pchar.questTemp.WPU.Current.Add = "double";
				// 08Mar17 "month" was "moths"
				dialog.text = "After a bad harvest our colony is in constant need of imported food. At this time our stock is almost empty, and everything has been wiped from the shelves of the stores quite some time ago. I would like to ask you to deliver to me " + GetGoodsNameAlt(iGoods)+ " in amount of " + FindRussianQtyString(iGoodsQty) + ", and I am willing to pay double - " + FindRussianMoneyString(sti(pchar.questTemp.WPU.Fraht.GoodsAverigePrice)) + " per pack. This will amount to " + FindRussianMoneyString(sti(pchar.questTemp.WPU.Fraht.Money)) + ". Oh, and try to meet the deadline of one month - I won't be able to wait for it any longer.";
				link.l1 = "Alright, I'll accept this mission.";
				link.l1.go = "Fraht_LevelUp_Go";
				link.l2 = "I am sorry to disappoint you, but I cannot do it at this moment.";
				link.l2.go = "Fraht_LevelDown";
				SetNull2StoreGood(rColony, sti(pchar.questTemp.WPU.Fraht.Goods));
			break;
		}
	break;
		
	case "Fraht_LevelDown":
		DialogExit();
		pchar.questTemp.WPU.Fraht.count = sti(pchar.questTemp.WPU.Fraht.count)-1;//скрутим счетчик
	break;
		
	case "Fraht_LevelUp_Go":
		dialog.text = "Excellent! I am very glad that you agreed. I hope to see you again soon.";
		link.l1 = "Of course, " + GetAddress_FormToNPC(NPChar) + ".";
		link.l1.go = "exit";
		pchar.questTemp.WPU.Fraht = "begin";
		pchar.questTemp.WPU.Fraht.LevelUp = "true";
		pchar.questTemp.WPU.Fraht.count = sti(pchar.questTemp.WPU.Fraht.count) + 1;
		pchar.questTemp.WPU.Fraht.TargetPortmanID = pchar.questTemp.WPU.Fraht.StartCity +"_portman";//ИД портмана
		iGoods = pchar.questTemp.WPU.Fraht.Goods;
		ReOpenQuestHeader("Fraht");
		AddQuestRecord("Fraht", "8");
		AddQuestUserData("Fraht", "sMoney", FindRussianMoneyString(sti(pchar.questTemp.WPU.Fraht.Money)));
		AddQuestUserData("Fraht", "sStartCity", XI_ConvertString("Colony"+pchar.questTemp.WPU.Fraht.StartCity+"Gen"));
		AddQuestUserData("Fraht", "sGoods", GetGoodsNameAlt(iGoods));
		AddQuestUserData("Fraht", "sGoodQty", FindRussianQtyString(sti(pchar.questTemp.WPU.Fraht.GoodsQty)));
		AddQuestUserData("Fraht", "sText", pchar.questTemp.WPU.Current1.Add);
		SetFunctionTimerCondition("FrahtTimeLevelUp_Over", 0, 0, 30, false);
	break;
	
	case "Fraht_completeLevelUp":
	ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
	if(sti(Pchar.Ship.Type) != SHIP_NOTUSED && ok)//проверка на наличие корабля в порту
	{
		iGoods = makeint(pchar.questTemp.WPU.Fraht.Goods);
		amount = sti(pchar.questTemp.WPU.Fraht.GoodsQty) - GetSquadronGoods(pchar, sti(pchar.questTemp.WPU.Fraht.Goods));
		if (amount > 0)
		{
			dialog.text = "Are you joking? You don't have the full amount of goods I'd ordered!";
			link.l1 = "I am sorry, my bad...";
			link.l1.go = "exit";
		}
		else
		{
			dialog.text = "Alright, you were supposed to deliver a cargo of " + GetGoodsNameAlt(iGoods)+ " in amount of " + FindRussianQtyString(pchar.questTemp.WPU.Fraht.GoodsQty) + ". Excellent, thank you very much. Here is your payment - "+FindRussianMoneyString(sti(pchar.questTemp.WPU.Fraht.Money))+".";
			link.l1 = "Pleasure doing business with you, " + GetAddress_FormToNPC(NPChar) + "!";
			link.l1.go = "Fraht_completeLevelUp_1";
		}
	}
	else
	{
		dialog.text = "I don't see your ship in the port. Lie off and then come see me again - then we will talk.";
		link.l1 = "Alright, I'll do just that.";
		link.l1.go = "exit";
	}
	break;
	
	case "Fraht_completeLevelUp_1":
		pchar.quest.FrahtTimeLevelUp_Over.over = "yes";//снять таймер
		AddQuestRecord("Fraht", "2");
		CloseQuestHeader("Fraht");
		RemoveCharacterGoods(pchar, sti(pchar.questTemp.WPU.Fraht.Goods), sti(pchar.questTemp.WPU.Fraht.GoodsQty));
		AddMoneyToCharacter(pchar, sti(pchar.questTemp.WPU.Fraht.Money));
		DeleteAttribute(pchar, "questTemp.WPU.Fraht.TargetPortmanID");
		DeleteAttribute(pchar, "questTemp.WPU.Current1"); // лесник  Current1 вместо Current
		DeleteAttribute(pchar, "questTemp.WPU.Fraht.LevelUp");
		pchar.questTemp.WPU.Fraht = "complete";
		AddCharacterExpToSkill(pchar, "Sailing", 100);//навигация
		AddCharacterExpToSkill(pchar, "Commerce", 200);//торговля
		AddCharacterExpToSkill(pchar, "Leadership", 150);//авторитет
		AddCharacterExpToSkill(pchar, "Fortune", 100);//везение
		ChangeCharacterComplexReputation(pchar,"nobility", 2);
		ChangeCharacterNationReputation(pchar, sti(pchar.questTemp.WPU.Fraht.Nation), 2);
		DialogExit();
	break;
	
//----------------------------------------задания 2 уровня эскорт ------------------------------------------

	case "Escort_LevelUp":
		pchar.questTemp.WPU.Escort.LevelUp = "true";//установим атрибут
		pchar.questTemp.WPU.Escort.StartCity = npchar.city;//город квестодателя
		pchar.questTemp.WPU.Escort.Nation = npchar.nation;//нация квестодателя
		pchar.questTemp.WPU.Escort.EnemyNation = GetEnemyNationToMainCharacter();//вражеская нация
		while (pchar.questTemp.WPU.Escort.EnemyNation == PIRATE)
		{
			pchar.questTemp.WPU.Escort.EnemyNation = GetEnemyNationToMainCharacter();
		}
		switch (drand(2))
		{
			case 0://приключения на необитаемых островах
				pchar.questTemp.WPU.Current.TargetIslandID = DesIsland();//выбор необитайки
				while (!isLocationFreeForQuests(pchar.questTemp.WPU.Current.TargetIslandID)) pchar.questTemp.WPU.Current.TargetIslandID = DesIsland();
				pchar.questTemp.WPU.Escort.ShipType = Escort_ShipType();//выбор корабля
				pchar.questTemp.WPU.Escort.ShipName = GenerateRandomNameToShip(sti(pchar.nation));//имя корабля
				pchar.questTemp.WPU.Escort.TargetPortmanID = pchar.questTemp.WPU.Escort.StartCity +"_portman";//ИД портмана
				pchar.questTemp.WPU.Escort.ShipBaseName = GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.questTemp.WPU.Escort.ShipType), "Name") + "Gen"));
				dialog.text = "This calamity occurred ten days ago... trade caravan bound for our colony was attacked by pirates. Gust storm forced the pirates to retreat, but the ships were dispersed caravan where and who lost each other. After all, all the ships arrived at different ports, except one\n"+pchar.questTemp.WPU.Escort.ShipBaseName+" '"+pchar.questTemp.WPU.Escort.ShipName+"' had disappeared, her fate remained unknown. Presumably the ship disappeared near the uninhabited island of "+XI_ConvertString(pchar.questTemp.WPU.Current.TargetIslandID)+". I ask you to go there to find ship and bring her into our port. or have proof of her death. Define the size of your payment after work, but I can say that the payment will be big enough.";
				link.l1 = "Of course, I agree!";
				link.l1.go = "Escort_LevelUp_1";
				link.l2 = "I am sorry, but this work isn't suitable for me. Sorry, but I'll pass.";
				link.l2.go = "Escort_LevelUp_exit";
			break;
			case 1://защитить конвой вблизи текущего острова от пиратов
				pchar.questTemp.WPU.Current.TargetIslandID = Islands[GetCharacterCurrentIsland(PChar)].id;//текущий остров
				pchar.questTemp.WPU.Escort.TargetPortmanID = pchar.questTemp.WPU.Escort.StartCity +"_portman";//ИД портмана
				dialog.text = "A trade caravan was supposed to arrive to our colony, but just at the very port it had been attacked by daring pirates. The battle is currently taking place far from the reach of the fort's cannons, and I don't have any escort ships available at the moment, so I cannot provide any help to poor merchants stick in these dire straits. You're a gallant captain, so I am asking you to interfere and help the merchants to repel the attack! Will you do that?";
				link.l1 = "Of course! It's a matter of honor!";
				link.l1.go = "Escort_LevelUp_2";
				link.l2 = "I am sorry, but this work isn't suitable for me. Sorry, but I'll pass.";
				link.l2.go = "Escort_LevelUp_exit";
			break;
			case 2://встретить и довести
				pchar.questTemp.WPU.Escort.ShipName = GenerateRandomNameToShip(sti(pchar.nation));
				pchar.questTemp.WPU.Escort.ShipType = Escort_ShipType();
				pchar.questTemp.WPU.Escort.City = findCurrentCity1(npchar);//город, откуда забрать
				pchar.questTemp.WPU.Escort.TargetPortmanID = pchar.questTemp.WPU.Escort.City +"_portman";//ИД портмана
				sld = characterFromId(pchar.questTemp.WPU.Escort.TargetPortmanID);
				pchar.questTemp.WPU.Escort.Nation = sld.nation;//нация получателя
				pchar.questTemp.WPU.Current.TargetIslandID = GetCharacterCurrentIslandId(npchar);//ИД целевого ареала
				pchar.questTemp.WPU.Escort.DaysQty = GetMaxDaysFromIsland2Island(GetArealByCityName(pchar.questTemp.WPU.Escort.StartCity), GetArealByCityName(pchar.questTemp.WPU.Escort.City));//расстояние в днях
				pchar.questTemp.WPU.Escort.Money = sti(pchar.questTemp.WPU.Escort.DaysQty)*2000+20000;
				pchar.questTemp.WPU.Escort.Chance = rand(1);
				dialog.text = "In the colony "+XI_ConvertString(pchar.questTemp.WPU.Escort.City)+" arrived the ship with weapons and ammunition for our colony. Escort ship hit the reef, was badly damaged and will not be able to depart to the sea soon. We can not risk sending a ship with an arsenal alone\nI suggest you implementing it to escort to our colony. Payment for the work set at "+FindRussianMoneyString(sti(pchar.questTemp.WPU.Escort.Money))+".";
				link.l1 = "Of course, I agree!";
				link.l1.go = "Escort_LevelUp_0";
				link.l2 = "I am sorry, but this work isn't suitable for me. Sorry, but I'll pass.";
				link.l2.go = "Escort_LevelUp_exit";
			break;
		}
	break;
	
	case "Escort_LevelUp_exit":
		dialog.text = "A pity, indeed. I was actually counting on you...";
		link.l1 = "I am sorry, too. Well, until we meet again, " + GetAddress_FormToNPC(NPChar) + ".";
		link.l1.go = "exit";
		pchar.questTemp.WPU.Escort.count = sti(pchar.questTemp.WPU.Escort.count)-1;//скрутим счетчик
		DeleteAttribute(pchar, "questTemp.WPU.Escort.LevelUp");
		DeleteAttribute(pchar, "questTemp.WPU.Escort.TargetPortmanID");
	break;
	
	case "Escort_LevelUp_0":
		dialog.text = "Excellent! I knew I could count on you. Please try to be as quick as possible I think, "+FindRussianDaysString(pchar.questTemp.WPU.Escort.DaysQty)+" will be enough to get to "+XI_ConvertString("Colony"+pchar.questTemp.WPU.Escort.City+"Gen")+". Here, take this credentials to verify your identity. Tailwind, captain!";
		link.l1 = "Don't worry, I will not let you down.";
		link.l1.go = "Escort_LevelUp_0_go";
	break;
	
	case "Escort_LevelUp_0_go":
		ReOpenQuestHeader("Escort");
		AddQuestRecord("Escort", "19");
		AddQuestUserData("Escort", "sMoney", FindRussianMoneyString(sti(pchar.questTemp.WPU.Escort.Money)));
		AddQuestUserData("Escort", "sStartCity", XI_ConvertString("Colony"+pchar.questTemp.WPU.Escort.StartCity+"Gen"));
		AddQuestUserData("Escort", "sTargetColony",XI_ConvertString("Colony"+pchar.questTemp.WPU.Escort.City));
		AddQuestUserData("Escort", "sDay", FindRussianDaysString(pchar.questTemp.WPU.Escort.DaysQty));
		SetFunctionTimerCondition("EscortArsenalShip_Over", 0, 0, sti(pchar.questTemp.WPU.Escort.DaysQty)+1, false);
		DialogExit();
		pchar.questTemp.WPU.Escort = "begin";
		pchar.questTemp.WPU.Escort.LevelUp_0 = "true";
		pchar.questTemp.WPU.Escort.count = sti(pchar.questTemp.WPU.Escort.count)+1;
	break;
	
	case "Escort_LUGo_0":
	ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
	if(sti(Pchar.Ship.Type) != SHIP_NOTUSED && ok)//проверка на наличие корабля в порту
	{
		pchar.quest.EscortArsenalShip_Over.over = "yes";
		dialog.text = "Finally! That ship had long been an eyesore to me. Take command, then. The name of the ship is "+pchar.questTemp.WPU.Escort.ShipName+", and its captain will be immediately notified of your arrival.";
		link.l1 = "Tell him to get his ship ready to sail - I am going to leave at the earliest opportunity.";
		link.l1.go = "Escort_LUGo_01";
	}
	else
	{
		dialog.text = "I don't see your ship in the port. Lie off and then come see me again - then we will talk.";
		link.l1 = "I'll do just that.";
		link.l1.go = "exit";
	}
	break;
	
	case "Escort_LUGo_01"://добавляем компаньона
		int iShipType = sti(pchar.questTemp.WPU.Escort.ShipType);
		sTemp = pchar.questTemp.WPU.Escort.ShipName;
		sld = GetCharacter(NPC_GenerateCharacter("ArsenalShipCaptain", "citiz_41", "man", "man", 15, sti(pchar.nation), -1, true, "quest"));
		FantomMakeSmallSailor(sld, iShipType, sTemp, CANNON_TYPE_CANNON_LBS16, 65, 22, 24, 35, 33);
		SetFantomParamFromRank(sld, 15, true); 
		SetCaptanModelByEncType(sld, "war");
		SetCharacterGoods(sld, GOOD_FOOD, 500);
		SetCharacterGoods(sld, GOOD_BALLS, 5000);
		SetCharacterGoods(sld, GOOD_GRAPES, 3000);
		SetCharacterGoods(sld, GOOD_KNIPPELS, 3000);
		SetCharacterGoods(sld, GOOD_BOMBS, 5000);
		SetCharacterGoods(sld, GOOD_POWDER, 10000);
		SetCharacterGoods(sld, GOOD_WEAPON, 3000);
		sld.CompanionEnemyEnable = false; //всегда друзья
		SetCompanionIndex(pchar, -1, sti(sld.index));
		SetCharacterRemovable(sld, false);
		sld.loyality = MAX_LOYALITY;
		sld.Dialog.Filename = "Common_portman.c";
		sld.dialog.currentnode = "Escort_companion";
		DialogExit();
		AddQuestRecord("Escort", "20");
		AddQuestUserData("Escort", "sSName", pchar.questTemp.WPU.Escort.ShipName);
		pchar.quest.Escort_fail.win_condition.l1 = "NPC_Death";//прерывание на потопление сопровождаемого
		pchar.quest.Escort_fail.win_condition.l1.character = "ArsenalShipCaptain";
		pchar.quest.Escort_fail.function = "EscortArsenalShip_failed";
		SetFunctionTimerCondition("EscortArsenalShipGo_Over", 0, 0, sti(pchar.questTemp.WPU.Escort.DaysQty)+6, false);
		DeleteAttribute(pchar, "questTemp.WPU.Escort.LevelUp_0");
		pchar.questTemp.WPU.Escort.LevelUpGo_0 = "true";
		if (sti(pchar.questTemp.WPU.Escort.Chance) == 0) EnemyNationHunterOnMap(true);//скоростной перехватчик
		else FrahtHunterOnSea();
	break;
	
	case "Escort_LUGo_complete":
	ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
	if(sti(Pchar.Ship.Type) != SHIP_NOTUSED && ok)//проверка на наличие корабля в порту
	{
		pchar.quest.Escort_fail.over = "yes";
		pchar.quest.EscortArsenalShipGo_Over.over = "yes";
		dialog.text = "Excellent! Once again, you've demonstrated that you can be relied upon. Thank you for a job well done. Please, accept your payment - "+FindRussianMoneyString(sti(pchar.questTemp.WPU.Escort.Money))+". And don't forget to visit me occasionally - there's always a job or two for a captain like you.";
		link.l1 = "Nice to hear that, " + GetAddress_FormToNPC(NPChar) + "! Of course, our collaboration shall continue. Best regards!";
		link.l1.go = "Escort_LUGo_complete_1";
	}
	else
	{
		dialog.text = "I don't see your ship in the port. Lie off and then come see me again - then we will talk.";
		link.l1 = "Alright, I'll do just that.";
		link.l1.go = "exit";
	}
	break;
	
	case "Escort_LUGo_complete_1":
		RemoveCharacterCompanion(Pchar, characterFromID("ArsenalShipCaptain"));
		sld = characterFromId("ArsenalShipCaptain");
		sld.lifeday = 0;//на всякий случай
		AddMoneyToCharacter(pchar, sti(pchar.questTemp.WPU.Escort.Money));
		ChangeCharacterComplexReputation(pchar,"nobility", 2);
		ChangeCharacterNationReputation(pchar, sti(pchar.questTemp.WPU.Escort.Nation), 2);
		AddQuestRecord("Escort", "24");
		AddQuestUserData("Escort", "sSName", pchar.questTemp.WPU.Escort.ShipName);
		CloseQuestHeader("Escort");
		DialogExit();
		pchar.questTemp.WPU.Escort = "complete";
		DeleteAttribute(pchar, "questTemp.WPU.Escort.LevelUpGo_0");
		DeleteAttribute(pchar, "questTemp.WPU.Escort.LevelUp");
		DeleteAttribute(pchar, "questTemp.WPU.Escort.TargetPortmanID");
		AddComplexSeaExpToScill(100, 100, 100, 0, 100, 0, 0);
		AddComplexSelfExpToScill(30, 30, 30, 30);
		AddCharacterExpToSkill(pchar, "Leadership", 100);//авторитет
		SaveCurrentNpcQuestDateParam(npchar, "work_date");
	break;
	
	case "Escort_LevelUp_1":
		dialog.text = "Then I wish you safe journey. And please, don't delay with your search! The sailors of that vessel might be in need of immediate help.";
		link.l1 = "I got it. I am going to set sail today!";
		link.l1.go = "Escort_LevelUp_1_select";
	break;
	
	case "Escort_LevelUp_1_select"://выберем приключение
		switch (rand(2))
		{
			case 0://весь побитый и остался без мачты
				pchar.quest.DisasterShip_WM.win_condition.l1 = "location";
				pchar.quest.DisasterShip_WM.win_condition.l1.location = pchar.questTemp.WPU.Current.TargetIslandID;
				pchar.quest.DisasterShip_WM.function = "CreateDisasterShip_WithoutMasts";
				pchar.questTemp.WPU.Escort.LevelUp_1WM = "true";
			break;
			case 1://ведет бой с пиратусами в шторме
				pchar.quest.DisasterShip_VSP.win_condition.l1 = "location";
				pchar.quest.DisasterShip_VSP.win_condition.l1.location = pchar.questTemp.WPU.Current.TargetIslandID;
				pchar.quest.DisasterShip_VSP.function = "CreateDisasterShip_VSPirate";
				for (i=0; i<MAX_ISLANDS; i++)//устроим шторм
				{				
					if (Islands[i].id == pchar.questTemp.WPU.Current.TargetIslandID)
					{
					Islands[i].alwaysStorm = true; 
					Islands[i].storm = true;
					Islands[i].tornado = true; 
					}
				}
				pchar.questTemp.WPU.Escort.LevelUp_1VSP = "true";
			break;
			case 2://потонул
				pchar.questTemp.WPU.Current.TargetIslandID.Shore = SelectQuestShoreLocationFromSea(pchar.questTemp.WPU.Current.TargetIslandID);
				pchar.quest.DisasterShip_S.win_condition.l1 = "location";
				pchar.quest.DisasterShip_S.win_condition.l1.location = pchar.questTemp.WPU.Current.TargetIslandID.Shore;
				pchar.quest.DisasterShip_S.function = "CreateDisasterShip_Crew";
				pchar.questTemp.WPU.Escort.LevelUp_1S = "true";
			break;
		}
		ReOpenQuestHeader("Escort");
		AddQuestRecord("Escort", "25");
		AddQuestUserData("Escort", "sStartCity", XI_ConvertString("Colony"+pchar.questTemp.WPU.Escort.StartCity+"Gen"));
		AddQuestUserData("Escort", "sIsland", XI_ConvertString(pchar.questTemp.WPU.Current.TargetIslandID));
		AddQuestUserData("Escort", "sSName", pchar.questTemp.WPU.Escort.ShipName);
		AddQuestUserData("Escort", "sTargetColony",XI_ConvertString("Colony"+pchar.questTemp.WPU.Escort.City));
		SetFunctionTimerCondition("DesIsland_Over", 0, 0, 15, false);
		DialogExit();
		pchar.questTemp.WPU.Escort = "begin";
		pchar.questTemp.WPU.Escort.count = sti(pchar.questTemp.WPU.Escort.count)+1;
	break;
	
	case "Escort_LU1WM_complete":
	ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
	if(sti(Pchar.Ship.Type) != SHIP_NOTUSED && ok)//проверка на наличие корабля в порту
	{
		dialog.text = "Yes, I was already notified. Excellent job, " + GetAddress_Form(NPChar) + "! You have once again proved that you are the one I can rely on. Get your reward - 30,000 pesos\nDo not forget to look up to me - people like you can be considered the essential and I always find a job for you.";
		link.l1 = "Glad to hear that, " + GetAddress_FormToNPC(NPChar) + "! Of course, we will cooperate further. All the best!";
		link.l1.go = "Escort_LU1WM_complete_1";
	}
	else
	{
		dialog.text = "I don't see your ship in the port. Lie off and then come see me again - then we will talk.";
		link.l1 = "Alright, I'll do just that.";
		link.l1.go = "exit";
	}
	break;
	
	case "Escort_LU1WM_complete_1":
		sld = characterFromId("WMCaptain");
		sld.lifeday = 0;
		DialogExit();
		AddMoneyToCharacter(pchar, 30000);
		ChangeCharacterComplexReputation(pchar,"nobility", 5);
		ChangeCharacterNationReputation(pchar, sti(pchar.questTemp.WPU.Escort.Nation), 5);
		AddQuestRecord("Escort", "32");
		AddQuestUserData("Escort", "sStartCity", XI_ConvertString("Colony"+pchar.questTemp.WPU.Escort.StartCity+"Gen"));
		AddQuestUserData("Escort", "sMoney", 30000);
		CloseQuestHeader("Escort");
		pchar.questTemp.WPU.Escort = "complete";
		DeleteAttribute(pchar, "questTemp.WPU.Escort.LevelUp_1WM");
		DeleteAttribute(pchar, "questTemp.WPU.Escort.LevelUp");
		DeleteAttribute(pchar, "questTemp.WPU.Escort.TargetPortmanID");
		AddCharacterExpToSkill(pchar, "Sailing", 100);//навигация
		AddCharacterExpToSkill(pchar, "Repair", 300);//починка
		AddCharacterExpToSkill(pchar, "Commerce", 100);//торговля
		AddCharacterExpToSkill(pchar, "Leadership", 100);//авторитет
		AddCharacterExpToSkill(pchar, "Fortune", 100);//везение
		SaveCurrentNpcQuestDateParam(npchar, "work_date");
	break;
	
	case "Escort_LU1VSP_complete":
	ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
	if(sti(Pchar.Ship.Type) != SHIP_NOTUSED && ok)//проверка на наличие корабля в порту
	{
		dialog.text = "Yeah, he already told me that you had been defending his vessel in that battle with the pirates, like a hero. Excellent job, " + GetAddress_Form(NPChar) + "! You have once again proved that you are the one I can rely on. Get your reward - 50,000 pesos\nDo not forget to look up to me - people like you can be considered the essential and I always find a job for you.";
		link.l1 = "Nice to hear that, " + GetAddress_FormToNPC(NPChar) + "! Of course, our collaboration shall continue. Best regards!";
		link.l1.go = "Escort_LU1VSP_complete_1";
	}
	else
	{
		dialog.text = "I don't see your ship in the port. Lie off and then come see me again - then we will talk.";
		link.l1 = "Alright, I'll do just that.";
		link.l1.go = "exit";
	}
	break;
	
	case "Escort_LU1VSP_complete_1":
		sld = characterFromId("WMCaptain");
		sld.lifeday = 0;
		DialogExit();
		AddMoneyToCharacter(pchar, 50000);
		ChangeCharacterComplexReputation(pchar,"nobility", 10);
		ChangeCharacterNationReputation(pchar, sti(pchar.questTemp.WPU.Escort.Nation), 6);
		AddQuestRecord("Escort", "32");
		AddQuestUserData("Escort", "sStartCity", XI_ConvertString("Colony"+pchar.questTemp.WPU.Escort.StartCity+"Gen"));
		AddQuestUserData("Escort", "sMoney", 50000);
		CloseQuestHeader("Escort");
		pchar.questTemp.WPU.Escort = "complete";
		DeleteAttribute(pchar, "questTemp.WPU.Escort.LevelUp_1VSP");
		DeleteAttribute(pchar, "questTemp.WPU.Escort.LevelUp");
		DeleteAttribute(pchar, "questTemp.WPU.Escort.TargetPortmanID");
		AddComplexSeaExpToScill(100, 150, 150, 100, 0, 0, 0);
		AddComplexSelfExpToScill(50, 50, 50, 50);
		AddCharacterExpToSkill(pchar, "Leadership", 100);//авторитет
		AddCharacterExpToSkill(pchar, "Fortune", 100);//везение
		SaveCurrentNpcQuestDateParam(npchar, "work_date");
	break;
	
	case "Escort_LU1VSP_completeSink":
		dialog.text = "What a tragic end... God rest their souls.";
		link.l1 = "I've done everything I could, " + GetAddress_FormToNPC(NPChar) + ". The situation was made even worse by the storm.";
		link.l1.go = "Escort_LU1VSP_completeSink_1";
	break;
	
	case "Escort_LU1VSP_completeSink_1":
		dialog.text = "I do believe, " + GetAddress_Form(NPChar) + ", that you had undertaken everything you could to save the ship and those unfortunate sailors. But alas... Well, please take your reward - 10000 pesos - and thank you for your service.";
		link.l1 = "Nothing to thank me for, " + GetAddress_FormToNPC(NPChar) + ". I am really sorry. Well, goodbye.";
		link.l1.go = "Escort_LU1VSP_completeSink_2";
	break;
	
	case "Escort_LU1VSP_completeSink_2":
		DialogExit();
		AddMoneyToCharacter(pchar, 10000);
		ChangeCharacterComplexReputation(pchar,"nobility", 1);
		AddQuestRecord("Escort", "32");
		AddQuestUserData("Escort", "sStartCity", XI_ConvertString("Colony"+pchar.questTemp.WPU.Escort.StartCity+"Gen"));
		AddQuestUserData("Escort", "sMoney", 10000);
		CloseQuestHeader("Escort");
		pchar.questTemp.WPU.Escort = "complete";
		DeleteAttribute(pchar, "questTemp.WPU.Escort.LevelUp_1VSP");
		DeleteAttribute(pchar, "questTemp.WPU.Escort.LevelUp");
		DeleteAttribute(pchar, "questTemp.WPU.Escort.TargetPortmanID");
		AddComplexSeaExpToScill(50, 50, 50, 50, 0, 0, 0);
		AddCharacterExpToSkill(pchar, "Fortune", 50);//везение
		SaveCurrentNpcQuestDateParam(npchar, "work_date");
	break;
	
	case "Escort_LU1S_complete":
		dialog.text = "Yeah, he already told me that you had been fighting with the red-skinned pagans and then with a pirate ship, like a hero. Excellent job, " + GetAddress_Form(NPChar) + "! You have once again proved that you are the one I can rely on\nGet your reward - 40,000 pesos. Do not forget to look up to me - people like you can be considered the essential and I always find a job for you..";
		link.l1 = "Nice to hear that, " + GetAddress_FormToNPC(NPChar) + "! Of course, our collaboration shall continue. Best regards!";
		link.l1.go = "Escort_LU1S_complete_1";
	break;
	
	case "Escort_LU1S_complete_1":
		sld = characterFromId("WMCaptain");
		sld.lifeday = 0;
		DialogExit();
		AddMoneyToCharacter(pchar, 40000);
		ChangeCharacterComplexReputation(pchar,"nobility", 8);
		ChangeCharacterNationReputation(pchar, sti(pchar.questTemp.WPU.Escort.Nation), 3);
		AddQuestRecord("Escort", "32");
		AddQuestUserData("Escort", "sStartCity", XI_ConvertString("Colony"+pchar.questTemp.WPU.Escort.StartCity+"Gen"));
		AddQuestUserData("Escort", "sMoney", 40000);
		CloseQuestHeader("Escort");
		pchar.questTemp.WPU.Escort = "complete";
		DeleteAttribute(pchar, "questTemp.WPU.Escort.LevelUp_1S");
		DeleteAttribute(pchar, "questTemp.WPU.Escort.LevelUp");
		DeleteAttribute(pchar, "questTemp.WPU.Escort.TargetPortmanID");
		AddComplexSeaExpToScill(100, 150, 150, 100, 0, 0, 0);
		AddComplexSelfExpToScill(100, 100, 100, 100);
		AddCharacterExpToSkill(pchar, "Leadership", 100);//авторитет
		AddCharacterExpToSkill(pchar, "Fortune", 100);//везение
		SaveCurrentNpcQuestDateParam(npchar, "work_date");
	break;
	
	case "Escort_LevelUp_2":
		dialog.text = "I knew that I could count on you. Best of luck to you, captain! The entire colony wishes you a sound of victory!";
		link.l1 = "I will try to live up to your expectations. Now I am going to set sail, and may God help us!";
		link.l1.go = "Escort_LevelUp_2_go";
	break;
	
	case "Escort_LevelUp_2_go":
		ReOpenQuestHeader("Escort");
		AddQuestRecord("Escort", "41");
		AddQuestUserData("Escort", "sStartCity", XI_ConvertString("Colony"+pchar.questTemp.WPU.Escort.StartCity+"Gen"));
		SetFunctionTimerCondition("CaravanNearIsland_Over", 0, 0, 2, false);
		pchar.questTemp.WPU.Escort.count = sti(pchar.questTemp.WPU.Escort.count)+1;
		pchar.quest.CaravanNearIsland_Start.win_condition.l1 = "location";
		pchar.quest.CaravanNearIsland_Start.win_condition.l1.location = pchar.questTemp.WPU.Current.TargetIslandID;
		pchar.quest.CaravanNearIsland_Start.function = "CreateCaravanNearIsland";
		pchar.questTemp.WPU.Escort.LevelUp_2 = "true";
		pchar.questTemp.WPU.Escort = "begin";
		DialogExit();
	break;
	
	case "Escort_LU2_complete":
		switch (sti(pchar.questTemp.WPU.Escort.LevelUp_2.Qty))
		{
			case 1:
				pchar.questTemp.WPU.Escort.LevelUp_2.Money = 10000;
				dialog.text = "Yes, the entire town was watching your battle. Poor merchants, I do feel sorry for them. Well, at least you managed to save one ship, so your reward of 10000 pesos is well deserved. Please, accept it - and thank you for your aid.";
				link.l1 = "Nothing to thank me for... It is unfortunate that I haven't won that combat decisively, but I've done everything I could. Farewell, " + GetAddress_FormToNPC(NPChar) + ".";
				link.l1.go = "Escort_LU2_complete_1";
			break;
			case 2:
				pchar.questTemp.WPU.Escort.LevelUp_2.Money = 25000;
				dialog.text = "Yes, the entire town was watching the battle you waged - and you did it very skillfully, I must say. That poor merchant, I feel so sorry for him... But if not for you, none of them would escape alive, so your reward of 25000 pesos is very well deserved. Please accept it - and thank you for your aid.";
				link.l1 = "Well, thanks for a complimentary assessment of my actions, but I don't think that was my best battle - I still lost one ship. Well, fate is fate, and there's nothing to do about it. Goodbye, " + GetAddress_FormToNPC(NPChar) + ".";
				link.l1.go = "Escort_LU2_complete_1";
			break;
			case 3:
				pchar.questTemp.WPU.Escort.LevelUp_2.Money = 50000;
				dialog.text = "Yes, the entire town was watching the battle you waged - you were absolutely magnificent! You just trashed the entire squadron of those filthy pirates! Now they've learned their lesson - pity that they will not come in handy for them anymore. Your reward constitutes 50000 pesos - please, accept it.";
				link.l1 = "Thanks for a complimentary assessment of my actions! Always a pleasure to help. And now, " + GetAddress_FormToNPC(NPChar) + ", please, allow me to take my leave.";
				link.l1.go = "Escort_LU2_complete_1";
			break;
		}
	break;
	
	case "Escort_LU2_complete_1":
		iTemp = sti(pchar.questTemp.WPU.Escort.LevelUp_2.Qty);
		DialogExit();
		Group_DeleteGroup("CaravanShip");
		AddMoneyToCharacter(pchar, sti(pchar.questTemp.WPU.Escort.LevelUp_2.Money));
		ChangeCharacterComplexReputation(pchar,"nobility", iTemp*2);
		ChangeCharacterNationReputation(pchar, sti(pchar.questTemp.WPU.Escort.Nation), iTemp);
		AddQuestRecord("Escort", "32");
		AddQuestUserData("Escort", "sStartCity", XI_ConvertString("Colony"+pchar.questTemp.WPU.Escort.StartCity+"Gen"));
		AddQuestUserData("Escort", "sMoney", sti(pchar.questTemp.WPU.Escort.LevelUp_2.Money));
		CloseQuestHeader("Escort");
		AddCharacterExpToSkill(pchar, "Sailing", iTemp*35);//навигация
		AddCharacterExpToSkill(pchar, "Accuracy", iTemp*50);//меткость
		AddCharacterExpToSkill(pchar, "Cannons", iTemp*50);//орудия
		AddCharacterExpToSkill(pchar, "Grappling", iTemp*35);//абордаж
		AddCharacterExpToSkill(pchar, "Leadership", iTemp*40);//авторитет
		AddCharacterExpToSkill(pchar, "Fortune", iTemp*35);//везение
		AddCharacterExpToSkill(pchar, "FencingLight", iTemp*35);//легкое оружие
		AddCharacterExpToSkill(pchar, "Fencing", iTemp*35);//среднее оружие
		AddCharacterExpToSkill(pchar, "FencingHeavy", iTemp*35);//тяжелое оружие
		AddCharacterExpToSkill(pchar, "Pistol", iTemp*35); //пистоли
		pchar.questTemp.WPU.Escort = "complete";
		DeleteAttribute(pchar, "questTemp.WPU.Escort.LevelUp_2");
		DeleteAttribute(pchar, "questTemp.WPU.Escort.LevelUp");
		DeleteAttribute(pchar, "questTemp.WPU.Escort.TargetPortmanID");
		SaveCurrentNpcQuestDateParam(npchar, "work_date");
	break;
	
		case "PortmanQuest_NF":
			dialog.text = "Hmm, that's bad. In that case your further work for me is out of question.";
			link.l1 = "Understood. Here is what I wanted to say...";
			link.l1.go = "node_2";
		break;
		
		//сгоревшее судно
		case "BurntShip2":
			dialog.text = "A pity, captain... It's a pity that you are not willing to help me.";
			link.l1 = "That's not a matter of my will, my good man. You must understand. Farewell.";
			link.l1.go = "exit";
			NPChar.Quest.BurntShip.LastQuestDate = sLastSpeakDate;
		break;
		
		case "BurntShip4":
			dialog.text = "What's up with you, captain?! Aren't you ashamed?! How could I?! I know my shit, I've been on service for many years. There are insurance contracts, and the insurance company is willing to pay, and I assure you that the sum insured is quite decent.";
			link.l1 = "What's your problem, mister? A gunpowder room detonated of fire, and there were casualties, and now you have to stand trial for your negligence?";
			link.l1.go = "BurntShip5";
		break;
		
		case "BurntShip5":
			sCapitainId = GenerateRandomName(sti(NPChar.nation), "man");
			
			dialog.text = "No! Of course no! Lord save my soul, otherwise I would lose my head. The cargo hold was absolutely empty, thank you Lord, the Blessed Virgin Mary!\n" +
				"And the problem is that the ship belongs to... or rather belonged to known to all Caribbean Mr. " + sCapitainId + ". And it was built in Europe by special order, with extraordinary characteristics. " +
				"And this ship owner was very proud and boasted everywhere, a kind of blockhead, God forgive me... What do I have to tell him now? I'd better kill myself, I swear...";
			link.l1 = "Oh, now I see that's a problem, indeed. And what was so special about it? What specialties did that ship have that its owner was so proud of?";
			link.l1.go = "BurntShip6";
			
			NPChar.Quest.BurntShip.ShipOwnerName = sCapitainId;
		break;
		
		case "BurntShip6":
			BurntShipQuest_FillStartParams(NPChar);
			
			attrL = NPChar.Quest.BurntShip.ShipAttribute;
			iTest = sti(NPChar.Quest.BurntShip.ShipType);
			
			switch(attrL)
			{
				case "speedrate":
					attrL = "His " + GetStrSmallRegister(XI_ConvertString(ShipsTypes[iTest].Name + "Acc")) + "'s wind speed was more than " + NPChar.Quest.BurntShip.ShipNeededValue + " knots. That was the privateer's pride... And now he'd just tell his boys to hang me on a yard. What devil has brought him to our harbor together with that pirate tub...";
				break;
				
				case "turnrate":
					attrL = "His " + GetStrSmallRegister(XI_ConvertString(ShipsTypes[iTest].Name + "Acc")) + "'s maneuverability was more than " + NPChar.Quest.BurntShip.ShipNeededValue + " units. That was the soldier's pride... And now he'd just have me flogged to death. What devil advised him to leave his tub there...";
				break;
				
				case "capacity":
					attrL = "His " + GetStrSmallRegister(XI_ConvertString(ShipsTypes[iTest].Name + "Acc")) + "' had a deadweight of over " + NPChar.Quest.BurntShip.ShipNeededValue + " units. Greed is bad, I'll tell ya. And now he'd just have me quartered in court. What devil advised him to leave his tub there...";
				break;
			}
			
			dialog.text = attrL;
			link.l1 = "And what do people at the docks say? Is it really impossible to build another one here?";
			link.l1.go = "BurntShip7";
		break;
		
		case "BurntShip7":
			dialog.text = "No one can. I even went to a nearby island for the request. They say that there is a notable master on Isla Tesoro, who is able to do almost everything in shipbuilding. But where we are and where is Isla Tesoro. All I left to do is counting on help of free captains like you. Maybe, it won't be difficult for you to find such ship for me. And I will take care of the rest\n" +
				"I will thank you generously, and the insurance company will do the same as well. The matter is extraordinary, you know. Who would ever want to upset such a powerful man?";
			link.l1 = "Yeah, that's not going to be easy. And how much time do I have?";
			link.l1.go = "BurntShip8";
			link.l2 = "No, pal, I cannot be involved in such affair. Not to mention that there are no warranties that a vessels with such parameters exists at all. I am sorry...";
			link.l2.go = "BurntShip2";
		break;
		
		case "BurntShip8":
			dialog.text = "Thanks God, there is still time. The owner sailed off to Europe and will be back no sooner than in half a year.";
			link.l1 = "Well, guess I'll manage it. I'll bring you a similar vessel. But keep in mind - if you choose to be too scant, I'll burn it right in fron of your ears!";
			link.l1.go = "BurntShip9";
		break;
		
		case "BurntShip9":
			dialog.text = "What are you saying, captain? Surely, I understand that you would need time - it's not to find some kind of tub in the nearest puddle... You just bring us the vessel, and we'll do our best, you can be sure of it...";
			link.l1 = "I hope so... Well, wait for me and for the good news. Farewell.";
			link.l1.go = "BurntShip9_exit";
		break;
		
		case "BurntShip9_exit":
			attrL = "BurntShipQuest_TimeIsOver_" + NPChar.Id;
			PChar.Quest.(attrL).win_condition.l1 = "Timer";
			PChar.Quest.(attrL).win_condition.l1.date.day = GetAddingDataDay(0, 6, 0);
			PChar.Quest.(attrL).win_condition.l1.date.month = GetAddingDataMonth(0, 6, 0);
			PChar.Quest.(attrL).win_condition.l1.date.year = GetAddingDataYear(0, 6, 0);
			PChar.Quest.(attrL).function = "BurntShipQuest_TimeIsOver";
			PChar.Quest.(attrL).PortmanId = NPChar.id;
			
			attrL = NPChar.Quest.BurntShip.ShipAttribute;
			
			iTest = sti(NPChar.Quest.BurntShip.ShipType);
			
			switch(attrL)
			{
				case "speedrate":
					attrL = "speed. The wind speed of the " + GetStrSmallRegister(XI_ConvertString(ShipsTypes[iTest].name + "Gen")) + " must be at least " + NPChar.Quest.BurntShip.ShipNeededValue;
				break;
				
				case "turnrate":
					attrL = "manoeuvrability. Manoeuvrability of the " + GetStrSmallRegister(XI_ConvertString(ShipsTypes[iTest].name + "Gen")) + " must be not less than " + NPChar.Quest.BurntShip.ShipNeededValue;
				break;
				
				case "capacity":
					attrL = "hold. Hold of the " + GetStrSmallRegister(XI_ConvertString(ShipsTypes[iTest].name + "Gen")) + " has to be not less than " + NPChar.Quest.BurntShip.ShipNeededValue;
				break;
			}
			
			sTitle = "BurntShipQuest" + NPChar.location;
			ReOpenQuestHeader(sTitle);
			AddQuestRecordEx(sTitle, "BurntShipQuest", "1");
			AddQuestUserDataForTitle(sTitle, "cityName", XI_ConvertString("Colony" + NPChar.city + "Dat"));
			AddQuestUserData(sTitle, "portmanName", GetFullName(NPChar));
			AddQuestUserData(sTitle, "cityName", XI_ConvertString("Colony" + NPChar.city + "Gen"));
			AddQuestUserData(sTitle, "text", attrL);
			
			NPChar.Quest.BurntShip.LastPortmanName = GetFullName(NPChar); // Запомнм имя
			
			DialogExit();
		break;
		
		// Вариант, когда не уложились в сроки
		case "BurntShip10":
			dialog.text = "What were you going to talk about?";
			link.l1 = "And where is the former harbour master, mister " + NPChar.Quest.BurntShip.LastPortmanName + "? I have business with him.";
			link.l1.go = "BurntShip11";
		break;
		
		case "BurntShip11":
			dialog.text = "He's no longer around. Imagine - he burnt down a vessel belonging to one well-known person and pocketed the insurance money. While the authorities were sorting this all out, he resigned and slipped away to Europe. Quite a swindler, isn't he?";
			link.l1 = "Yeah, I've heard that story. I am sorry, but I have to go.";
			link.l1.go = "BurntShip11_exit";
		break;
		
		case "BurntShip11_exit":
			AddCharacterExpToSkill(pchar, "Sailing", 100);
			AddCharacterExpToSkill(pchar, "Fortune", 100);
			sTitle = "BurntShipQuest" + NPChar.location;
			AddQuestRecordEx(sTitle, "BurntShipQuest", "2");
			AddQuestUserData(sTitle, "portmanName", NPChar.Quest.BurntShip.LastPortmanName);
			CloseQuestHeader(sTitle);
			
			DeleteAttribute(NPChar, "Quest.BurntShip");
			NPChar.Quest.BurntShip.LastQuestDate = sLastSpeakDate;
			
			DialogExit();
		break;
		
		// Не просрочено - проверяем корабль
		case "BurntShip12":
			dialog.text = "What were you going to talk about?";
			link.l1 = "I brought you a ship with an extraordinary response. I am waiting for the promised reward.";
			link.l1.go = "BurntShip14";
			link.l2 = "You know, " + GetFullName(NPChar) + ", I still haven't found a single ship similar to what you need. I guess I'll abandon this job. Sorry if I let you down...";
			link.l2.go = "BurntShip13";
		break;
		
		case "BurntShip13":
			dialog.text = "A pity, captain... It's a pity that you are not willing to help me.";
			link.l1 = "That's not a matter of my will, my good man. You must understand. Farewell.";
			link.l1.go = "BurntShip13_exit";
		break;
		
		case "BurntShip13_exit":
			sTitle = "BurntShipQuest" + NPChar.location;
			CloseQuestHeader(sTitle);
			
			ChangeCharacterComplexReputation(pchar,"nobility", -5);
			DeleteAttribute(NPChar, "Quest.BurntShip");
			NPChar.Quest.BurntShip.LastQuestDate = sLastSpeakDate;
			
			DialogExit();
		break;
		
		case "BurntShip14":
			dialog.text = "Oh, really! And what's the name of our new ship?";
			
			sTitle = NPChar.Quest.BurntShip.ShipAttribute;
			ok = (sFrom_sea == "") || (Pchar.location.from_sea == sFrom_sea);
			
			if(sti(Pchar.Ship.Type) != SHIP_NOTUSED && ok)
			{
				for(i = 1; i < COMPANION_MAX; i++)
				{
					cn = GetCompanionIndex(PChar, i);
					
					if(cn > 0)
					{
						chref = GetCharacter(cn);
						
						sld = &RealShips[sti(chref.ship.type)];
						
						if(GetRemovable(chref) && sti(sld.basetype) == sti(NPchar.Quest.BurntShip.ShipType) &&
							stf(sld.(sTitle)) >= stf(NPChar.Quest.BurntShip.ShipNeededValue))
						{
							attrL = "l" + i;
							Link.(attrL) = chref.Ship.Name;
							Link.(attrL).go = "BurntShip15";
						}
					}
				}
			}
			
			link.l99 = "Excuse me, I'll come again later.";
			link.l99.go = "exit";
		break;
		
		case "BurntShip15":
			AddCharacterExpToSkill(pchar, "Leadership", 100);
			AddCharacterExpToSkill(pchar, "Sailing", 100);
			AddCharacterExpToSkill(pchar, "Fortune", 100);
			dialog.text = "Oh, captain, I am so happy that you didn't let me down! What a "+ GetSexPhrase("fine young man","fine young lady") +" you are, you literally saved my life... Please, could you come to collect your money in a couple of days? You know, I'll need to settle the formalities with the insurance... And meanwhile you could make minor repairs of the ship - you know, renew the sails, patch up the holes, careening wouldn't hurt, either...";
			link.l99 = "Haven't you forgotten what I promised that I'd do something bad with the ship if you tried to cheat on me?";
			link.l99.go = "BurntShip16";
		break;
		
		case "BurntShip16":
			dialog.text = "No, no, of course, not! I will stay true to my word, don't you worry. You see, due to the upcoming expenses with the disuising of the ship I had lent the insurance money on interest. I hope you understand...";
			link.l1 = "I'll understand it when the money is in my chest. Until we meet again.";
			link.l1.go = "BurntShip16_exit";
		break;
		
		case "BurntShip16_exit":
			sTitle = "BurntShipQuest" + NPChar.location;
			AddQuestRecordEx(sTitle, "BurntShipQuest", "3");
			
			NPChar.Quest.BurntShip.TwoDaysWait = true;
			SaveCurrentNpcQuestDateParam(NPChar, "Quest.BurntShip.TwoDaysWait"); // Запомним дату
			
			sTitle = "BurntShipQuest" + NPChar.Id;
			PChar.Quest.(sTitle).over = "yes"; // Завершаем прерывание на время
			
			DialogExit();
		break;
		
		case "BurntShip17":
			dialog.text = "What were you going to talk about?";
			link.l1 = "I came to collect my reward. I still have the vessel you need.";
			link.l1.go = "BurntShip18";
		break;
		
		case "BurntShip18":
			dialog.text = "Would you please remind me its name? My memory is not like it used to be - you know, all that hassle...";
			
			sTitle = NPChar.Quest.BurntShip.ShipAttribute;
			ok = (sFrom_sea == "") || (Pchar.location.from_sea == sFrom_sea);
			
			if(sti(Pchar.Ship.Type) != SHIP_NOTUSED && ok)
			{
				for(i = 1; i < COMPANION_MAX; i++)
				{
					cn = GetCompanionIndex(PChar, i);
					
					if(cn > 0)
					{
						chref = GetCharacter(cn);
						
						sld = &RealShips[sti(chref.ship.type)];
						
						if(GetRemovable(chref) && sti(sld.basetype) == sti(NPchar.Quest.BurntShip.ShipType) &&
							stf(sld.(sTitle)) >= stf(NPChar.Quest.BurntShip.ShipNeededValue))
						{
							attrL = "l" + i;
							Link.(attrL) = chref.Ship.Name;
							Link.(attrL).go = "BurntShip19_" + i;
						}
					}
				}
			}
			
			link.l99 = "Excuse me, I'll come again later.";
			link.l99.go = "exit";
		break;
		
		case "BurntShip19":
			sld = &Characters[GetCompanionIndex(PChar, sti(NPChar.Quest.BurntShip.ShipCompanionIndex))];
			cn = GetShipSellPrice(sld, CharacterFromID(NPChar.city + "_shipyarder")) * 2;
			rRealShip = GetRealShip(GetCharacterShipType(sld));
			if (sti(rRealShip.Stolen)) cn *= 3;
			
			dialog.text = "Yes, perfect. I am ready to hand you your reward, " + FindRussianMoneyString(cn) + ". That's how the insurance company appraised the burned vessel. The insurance sum is paid in credit chests - no money in cash, sorry.";
			link.l1 = "Oh no, such sum doesn't suit me. I am sure that this ship is much more expensive.";
			link.l1.go = "BurntShip21";
			link.l2 = "That's right. I'm glad I could help you. See you.";
			link.l2.go = "BurntShip20_exit";
			NPChar.Quest.BurntShip.Money = cn;
		break;
		
		case "BurntShip20_exit":
			TakeNItems(pchar, "chest", makeint(sti(NPChar.Quest.BurntShip.Money)/12000));
			Log_Info("You have received credit chests");
			PlaySound("interface\important_item.wav");
			sTitle = "BurntShipQuest" + NPChar.location;
			AddQuestRecordEx(sTitle, "BurntShipQuest", "4");
			AddQuestUserData(sTitle, "sSex", GetSexPhrase("","а"));
			AddQuestUserData(sTitle, "money", NPChar.Quest.BurntShip.Money);
			CloseQuestHeader(sTitle);
			
			ChangeCharacterComplexReputation(pchar,"nobility", 3);
			
			sld = &Characters[GetCompanionIndex(PChar, sti(NPChar.Quest.BurntShip.ShipCompanionIndex))];
			RemoveCharacterCompanion(PChar, sld);
			AddPassenger(PChar, sld, false);
			
			DeleteAttribute(NPChar, "Quest.BurntShip");
			NPChar.Quest.BurntShip.LastQuestDate = sLastSpeakDate;
			
			DialogExit();
		break;
		
		case "BurntShip21":
			dialog.text = "What are you saying, captain?! Trust me, I know what I am talking about. You could have bought two such ships for that money!";
			link.l1 = "I guess I will keep it. You know, I just took a liking in it... Farewell.";
			link.l1.go = "BurntShip21_exit";
		break;
		
		case "BurntShip21_exit":
			ChangeCharacterComplexReputation(pchar,"nobility", -5);
			
			sTitle = "BurntShipQuest" + NPChar.location;
			AddQuestRecordEx(sTitle, "BurntShipQuest", "5");
			AddQuestUserData(sTitle, "sSex", GetSexPhrase("","а"));
			AddQuestUserData(sTitle, "money", NPChar.Quest.BurntShip.Money);
			CloseQuestHeader(sTitle);
			
			DeleteAttribute(NPChar, "Quest.BurntShip");
			NPChar.Quest.BurntShip.LastQuestDate = sLastSpeakDate;
			
			DialogExit();
		break;
		
		//--> миниквесты портмана
		case "PortmanQuest":
			if (cRand(5) == 2)
			{	//квест догнать и передать судовой журнал
				dialog.text = "One captain has forgotten his ship's log at my office. What a scatterbrain! So, I need you to catch up with him and return it to him.";
				link.l1 = "Oh, that's gonna be easy... I'll take that!";
				link.l1.go = "PortmanQuest_1";
				link.l2 = "No, I will not take it up. It's his own problem, actually.";
				link.l2.go = "node_2";
			}
			else
			{	//квест разыскать украденный корабль
				dialog.text = "A ship was stolen from the mooring there. I want you to seek out the stolen vessel and bring it back.";
				link.l1 = "Hmm, well, I'm ready to take up the investigation.";
				link.l1.go = "SeekShip_1";
				link.l2 = "I am sorry, but I do not engage in searching for stolen ships.";
				link.l2.go = "node_2";
			}
		break;
//-------------------------------- квест доставки судового журнала до рассеяного кэпа ---------------------
		case "PortmanQuest_1":
			dialog.text = "Excellent, here's his ship's log... You've really taken a weight off my mind! The loss of a ship's log is a very nasty thing. I always felt sorry for those captains...";
			link.l1 = "Well, that's really something to be worry about! Now, tell me more of that absent-minded captain.";
			link.l1.go = "PortmanQuest_2";
			pchar.questTemp.different = "PortmansJornal";
			SetTimerFunction("SmallQuests_free", 0, 0, 1); //освобождаем разрешалку на миниквесты
			SetJornalCapParam(npchar);
			GiveItem2Character(pchar, "PortmansBook");
			pchar.questTemp.PortmansJornal.gem = GenQuestPortman_GenerateGem();
		break;
		case "PortmanQuest_2":
			dialog.text = "Yes, sure! His name is " + npchar.quest.PortmansJornal.capName + ", he's a captain of " + GetStrSmallRegister(XI_ConvertString(npchar.quest.PortmansJornal.shipTapeName + "Gen")) + " named '" + npchar.quest.PortmansJornal.shipName + "'. He set sail not long ago and went to " + XI_ConvertString("Colony" + npchar.quest.PortmansJornal.city + "Acc") + ".";
			link.l1 = "I see. Alright, I will find him. Now what about payment?";
			link.l1.go = "PortmanQuest_3";
		break;
		case "PortmanQuest_3":
			dialog.text = npchar.quest.PortmansJornal.capName + " himself will pay you, it's in his best interest. You just try to find him as soon as you can, and everything will be fine.";
			link.l1 = "I see. Well, I'll go, then...";
			link.l1.go = "exit";
			sTitle = npchar.id + "PortmansBook_Delivery";
			ReOpenQuestHeader(sTitle);
			AddQuestRecordEx(sTitle, "PortmansBook_Delivery", "1");
			AddQuestUserDataForTitle(sTitle, "sCapName", npchar.quest.PortmansJornal.capName);
			AddQuestUserDataForTitle(sTitle, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(sTitle, "sShipTypeName", GetStrSmallRegister(XI_ConvertString(npchar.quest.PortmansJornal.shipTapeName + "Gen")));
			AddQuestUserData(sTitle, "sShipName", npchar.quest.PortmansJornal.shipName);
			AddQuestUserData(sTitle, "sCapName", npchar.quest.PortmansJornal.capName);
			AddQuestUserData(sTitle, "sCapName2", npchar.quest.PortmansJornal.capName);
			AddQuestUserData(sTitle, "sTargetCity", XI_ConvertString("Colony" + npchar.quest.PortmansJornal.city + "Acc"));
			if (GetIslandByCityName(npchar.quest.PortmansJornal.city) != npchar.quest.PortmansJornal.city)
			{
				AddQuestUserData(sTitle, "sAreal", ", which is on " + XI_ConvertString(GetIslandByCityName(npchar.quest.PortmansJornal.city) + "Dat"));
			}			
		break;
		// -------------------------------- квест розыска украденного корабля ----------------------------------
		case "SeekShip_1":
			dialog.text = "Excellent! You know, the stolen ship belongs to an influential person, so this is very important to me. I will pay you handsomely for this job...";
			link.l1 = "I see. Tell me more about the ship and in what circumstances it has been stolen.";
			link.l1.go = "SeekShip_2";
			pchar.questTemp.different = "PortmansSeekShip";
			SetTimerFunction("SmallQuests_free", 0, 0, 1); //освобождаем разрешалку на миниквесты
			SetSeekShipCapParam(npchar);
		break;
		case "SeekShip_2":
			dialog.text = XI_ConvertString(npchar.quest.PortmansSeekShip.shipTapeName) + " by the name of '" + npchar.quest.PortmansSeekShip.shipName + "' was stolen at night " + FindRussianDaysString(rand(5)+10) + " ago. The watchman was slain.";
			link.l1 = "Hmm... They must have gone far by now. No way we'll catch them on a hot scent.";
			link.l1.go = "SeekShip_3";
		break;
		case "SeekShip_3":
			dialog.text = "True, but I still saw no point in raising alarm right away. The military ship could have caught up with them, but it would just blow the ship to pieces - and that's not exactly the thing I need.";
			link.l1 = "I see. Well, I am starting my search. Hope I'll get lucky.";
			link.l1.go = "exit";
			sTitle = npchar.id + "Portmans_SeekShip";
			ReOpenQuestHeader(sTitle);
			AddQuestRecordEx(sTitle, "Portmans_SeekShip", "1");
			AddQuestUserDataForTitle(sTitle, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(sTitle, "sShipTypeName", GetStrSmallRegister(XI_ConvertString(npchar.quest.PortmansSeekShip.shipTapeName+"Acc")));
			AddQuestUserData(sTitle, "sShipName", npchar.quest.PortmansSeekShip.shipName);
		break;

		case "SeekShip_break":
			dialog.text = "A pity - but we could hardly count on success.";
			link.l1 = "Yes, it's been too long since the ship was stolen.";
			link.l1.go = "SeekShip_break_1";
		break;
		case "SeekShip_break_1":
			dialog.text = "Well, thank you for your help anyway, even though your efforts were not as fruitful as we could hope.";
			link.l1 = "I did everything I could...";
			link.l1.go = "exit";
			sTemp = "SeekShip_checkAbordage" + npchar.index;
			pchar.quest.(sTemp).over = "yes"; //снимаем прерывание на абордаж
			cn = GetCharacterIndex("SeekCap_" + npchar.index);
			//если кэп-вор еще жив - убираем его
			if (cn > 0)
			{
				characters[cn].LifeDay = 0; 
				Map_ReleaseQuestEncounter(characters[cn].id);
				group_DeleteGroup("SeekCapShip_" + characters[cn].index);
			}
			sTitle = npchar.id + "Portmans_SeekShip";
			AddQuestRecordEx(sTitle, "Portmans_SeekShip", "7");
			CloseQuestHeader(sTitle);
			DeleteAttribute(npchar, "quest.PortmansSeekShip");
			npchar.quest = ""; //освобождаем личный флаг квеста для портмана
			ChangeCharacterComplexReputation(pchar,"nobility", -7);
		break;	

		case "SeekShip_good":
			if (npchar.quest == "SeekShip_sink")
			{
				dialog.text = "Excellent! Although I suspect that this is not exactly the ship which had been stolen... Oh, who cares! I'm taking it.";
				link.l1 = "Yes, indeed...";
				//npchar.quest.money = makeint(sti(npchar.quest.money) / 4); //снижаем оплату
				ChangeCharacterComplexReputation(pchar,"nobility", 5);
				ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 10);
                AddCharacterExpToSkill(GetMainCharacter(), "Leadership", 10);
                AddCharacterExpToSkill(GetMainCharacter(), "Sailing", 10);
                AddCharacterExpToSkill(GetMainCharacter(), "Commerce", 50);
                AddCharacterExpToSkill(GetMainCharacter(), "Cannons", 20);
			}
			else
			{
				dialog.text = "Excellent! You've helped me out a lot. I can't imagine how hard it was.";
				link.l1 = "Yes, indeed...";
				ChangeCharacterComplexReputation(pchar,"nobility", 10);
				ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 20);
                AddCharacterExpToSkill(GetMainCharacter(), "Leadership", 100);
                AddCharacterExpToSkill(GetMainCharacter(), "Sailing", 150);
                AddCharacterExpToSkill(GetMainCharacter(), "Grappling", 100);
			}
			link.l1.go = "SeekShip_good_1";
		break;
		case "SeekShip_good_1":
			dialog.text = "I am ready to pay you your reward. In constitutes of " + FindRussianMoneyString(makeint(sti(npchar.quest.chest)*15000)) + " in chests. Unfortunately, I cannot pay you more than that.";
			link.l1 = "Well, that's enough. Thank you and warm regards.";
			link.l1.go = "exit";
			TakeNItems(pchar, "chest", sti(npchar.quest.chest));
			sTitle = npchar.id + "Portmans_SeekShip";
			AddQuestRecordEx(sTitle, "Portmans_SeekShip", "6");
			CloseQuestHeader(sTitle);
			DeleteAttribute(npchar, "quest.PortmansSeekShip");
			npchar.quest = ""; //освобождаем личный флаг квеста для портмана
		break;

		//------------------------------> инфа по базе квествых кэпов
		//ВНИМАНИЕ. в квестбук должна заносится типовая строка по примеру   PortmansBook_Delivery  #TEXT   5
		//в список портмана заносим тайтл, заголовок и номер строки из quest_text.txt
		//ПРИМЕР: в конце метода  void SetCapitainFromCityToSea(string qName)
		case "CapitainList":
			if (sti(npchar.quest.qty) > 0)
			{
				dialog.text = "There are several registered captains. Are you interested in someone in particular?";
				makearef(arCapBase, npchar.quest.capitainsList); 
				for (i=0; i<sti(npchar.quest.qty); i++)
				{
    				arCapLocal = GetAttributeN(arCapBase, i);
					sCapitainId = GetAttributeName(arCapLocal);
					sld = characterFromId(sCapitainId);
					attrL = "l" + i;
					link.(attrL) = GetFullName(sld) + ", captain of " + GetStrSmallRegister(XI_ConvertString(RealShips[sti(sld.Ship.Type)].BaseName + "Acc")) + " '" + sld.Ship.name + "'.";
					link.(attrL).go = "CapList_"+attrL;
				}
			}
			else
			{
				dialog.text = "I have no captains on my list that could be of interest to you.";
				link.l1 = "I see. Well, thanks for the information.";
				link.l1.go = "node_2";
			}
		break;
		case "CapList_l0":
			makearef(arCapBase, npchar.quest.capitainsList);
    		arCapLocal = GetAttributeN(arCapBase,  0);
			sCapitainId = GetAttributeName(arCapLocal);
			sld = characterFromId(sCapitainId);
			dialog.text = LinkRandPhrase("Well, let's see... A-ha! There! ", "Ah-ha... A-ha! There! ", "Alright, then. ") +
				"Captain " + GetFullName(sld) + " " + arCapLocal.date + " year left our port and sailed to " + XI_ConvertString("Colony" + arCapLocal + "Acc") + ".";
			link.l1 = "Thank you. I'd like to look further through the list...";
			link.l1.go = "CapitainList";
			link.l2 = "Okay, that's all. I am not interested in any more captains.";
			link.l2.go = "node_2";
			//заносим запись в СЖ
			AddQuestRecordEx(arCapLocal.QBString1, arCapLocal.QBString2, arCapLocal.QBQty);
			AddQuestUserData(arCapLocal.QBString1, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(arCapLocal.QBString1, "sCapName", GetFullName(sld));
			AddQuestUserData(arCapLocal.QBString1, "sShipTypeName", GetStrSmallRegister(XI_ConvertString(RealShips[sti(sld.Ship.Type)].BaseName + "Voc")));
			AddQuestUserData(arCapLocal.QBString1, "sShipName", sld.Ship.name);
			AddQuestUserData(arCapLocal.QBString1, "sDate", arCapLocal.date);
			AddQuestUserData(arCapLocal.QBString1, "sTargetCity", XI_ConvertString("Colony" + arCapLocal + "Acc"));
			if (GetIslandByCityName(arCapBase.(sCapitainId)) != arCapBase.(sCapitainId))
			{
				AddQuestUserData(arCapLocal.QBString1, "sAreal", " that is in " + XI_ConvertString(GetIslandByCityName(arCapBase.(sCapitainId)) + "Dat"));
			}
			//убираем из списка
			DeleteAttribute(arCapBase, sCapitainId); 
		break;
		case "CapList_l1":
			makearef(arCapBase, npchar.quest.capitainsList);
    		arCapLocal = GetAttributeN(arCapBase,  1);
			sCapitainId = GetAttributeName(arCapLocal);
			sld = characterFromId(sCapitainId);
			dialog.text = LinkRandPhrase("Well, let's see... A-ha! There! ", "Ah-ha... A-ha! There! ", "Alright, then. ") +
				"Captain " + GetFullName(sld) + " " + arCapLocal.date + " year left our port and sailed to " + XI_ConvertString("Colony" + arCapLocal + "Acc") + ".";
			link.l1 = "Thank you. I'd like to look further through the list...";
			link.l1.go = "CapitainList";
			link.l2 = "Okay, that's all. I am not interested in any more captains.";
			link.l2.go = "node_2";
			//заносим запись в СЖ
			AddQuestRecordEx(arCapLocal.QBString1, arCapLocal.QBString2, arCapLocal.QBQty);
			AddQuestUserData(arCapLocal.QBString1, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(arCapLocal.QBString1, "sCapName", GetFullName(sld));
			AddQuestUserData(arCapLocal.QBString1, "sShipTypeName", GetStrSmallRegister(XI_ConvertString(RealShips[sti(sld.Ship.Type)].BaseName + "Dat")));
			AddQuestUserData(arCapLocal.QBString1, "sShipName", sld.Ship.name);
			AddQuestUserData(arCapLocal.QBString1, "sDate", arCapLocal.date);
			AddQuestUserData(arCapLocal.QBString1, "sTargetCity", XI_ConvertString("Colony" + arCapLocal + "Acc"));
			if (GetIslandByCityName(arCapBase.(sCapitainId)) != arCapBase.(sCapitainId))
			{
				AddQuestUserData(arCapLocal.QBString1, "sAreal", " that is in " + XI_ConvertString(GetIslandByCityName(arCapBase.(sCapitainId)) + "Dat"));
			}
			//убираем из списка
			DeleteAttribute(arCapBase, sCapitainId); 
		break;
		case "CapList_l2":
			makearef(arCapBase, npchar.quest.capitainsList);
    		arCapLocal = GetAttributeN(arCapBase,  2);
			sCapitainId = GetAttributeName(arCapLocal);
			sld = characterFromId(sCapitainId);
			dialog.text = LinkRandPhrase("Well, let's see... A-ha! There! ", "Ah-ha... A-ha! There! ", "Alright, then. ") +
				"Captain " + GetFullName(sld) + " " + arCapLocal.date + " year left our port and sailed to " + XI_ConvertString("Colony" + arCapLocal + "Acc") + ".";
			link.l1 = "Thank you. I'd like to look further through the list...";
			link.l1.go = "CapitainList";
			link.l2 = "Okay, that's all. I am not interested in any more captains.";
			link.l2.go = "node_2";
			//заносим запись в СЖ
			AddQuestRecordEx(arCapLocal.QBString1, arCapLocal.QBString2, arCapLocal.QBQty);
			AddQuestUserData(arCapLocal.QBString1, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(arCapLocal.QBString1, "sCapName", GetFullName(sld));
			AddQuestUserData(arCapLocal.QBString1, "sShipTypeName", GetStrSmallRegister(XI_ConvertString(RealShips[sti(sld.Ship.Type)].BaseName + "Dat")));
			AddQuestUserData(arCapLocal.QBString1, "sShipName", sld.Ship.name);
			AddQuestUserData(arCapLocal.QBString1, "sDate", arCapLocal.date);
			AddQuestUserData(arCapLocal.QBString1, "sTargetCity", XI_ConvertString("Colony" + arCapLocal + "Acc"));
			if (GetIslandByCityName(arCapBase.(sCapitainId)) != arCapBase.(sCapitainId))
			{
				AddQuestUserData(arCapLocal.QBString1, "sAreal", " that is in " + XI_ConvertString(GetIslandByCityName(arCapBase.(sCapitainId)) + "Dat"));
			}
			//убираем из списка
			DeleteAttribute(arCapBase, sCapitainId); 
		break;
		case "CapList_l3":
			makearef(arCapBase, npchar.quest.capitainsList);
    		arCapLocal = GetAttributeN(arCapBase,  3);
			sCapitainId = GetAttributeName(arCapLocal);
			sld = characterFromId(sCapitainId);
			dialog.text = LinkRandPhrase("Well, let's see... A-ha! There! ", "Ah-ha... A-ha! There! ", "Alright, then. ") +
				"Captain " + GetFullName(sld) + " " + arCapLocal.date + " year left our port and sailed to " + XI_ConvertString("Colony" + arCapLocal + "Acc") + ".";
			link.l1 = "Thank you. I'd like to look further through the list...";
			link.l1.go = "CapitainList";
			link.l2 = "Okay, that's all. I am not interested in any more captains.";
			link.l2.go = "node_2";
			//заносим запись в СЖ
			AddQuestRecordEx(arCapLocal.QBString1, arCapLocal.QBString2, arCapLocal.QBQty);
			AddQuestUserData(arCapLocal.QBString1, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(arCapLocal.QBString1, "sCapName", GetFullName(sld));
			AddQuestUserData(arCapLocal.QBString1, "sShipTypeName", GetStrSmallRegister(XI_ConvertString(RealShips[sti(sld.Ship.Type)].BaseName + "Dat")));
			AddQuestUserData(arCapLocal.QBString1, "sShipName", sld.Ship.name);
			AddQuestUserData(arCapLocal.QBString1, "sDate", arCapLocal.date);
			AddQuestUserData(arCapLocal.QBString1, "sTargetCity", XI_ConvertString("Colony" + arCapLocal + "Acc"));
			if (GetIslandByCityName(arCapBase.(sCapitainId)) != arCapBase.(sCapitainId))
			{
				AddQuestUserData(arCapLocal.QBString1, "sAreal", " that is in " + XI_ConvertString(GetIslandByCityName(arCapBase.(sCapitainId)) + "Dat"));
			}
			//убираем из списка
			DeleteAttribute(arCapBase, sCapitainId); 
		break;
		case "CapList_l4":
			makearef(arCapBase, npchar.quest.capitainsList);
    		arCapLocal = GetAttributeN(arCapBase,  4);
			sCapitainId = GetAttributeName(arCapLocal);
			sld = characterFromId(sCapitainId);
			dialog.text = LinkRandPhrase("Well, let's see... A-ha! There! ", "Ah-ha... A-ha! There! ", "Alright, then. ") +
				"Captain " + GetFullName(sld) + " " + arCapLocal.date + " year left our port and sailed to " + XI_ConvertString("Colony" + arCapLocal + "Acc") + ".";
			link.l1 = "Thank you. I'd like to look further through the list...";
			link.l1.go = "CapitainList";
			link.l2 = "Okay, that's all. I am not interested in any more captains.";
			link.l2.go = "node_2";
			//заносим запись в СЖ
			AddQuestRecordEx(arCapLocal.QBString1, arCapLocal.QBString2, arCapLocal.QBQty);
			AddQuestUserData(arCapLocal.QBString1, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(arCapLocal.QBString1, "sCapName", GetFullName(sld));
			AddQuestUserData(arCapLocal.QBString1, "sShipTypeName", GetStrSmallRegister(XI_ConvertString(RealShips[sti(sld.Ship.Type)].BaseName + "Dat")));
			AddQuestUserData(arCapLocal.QBString1, "sShipName", sld.Ship.name);
			AddQuestUserData(arCapLocal.QBString1, "sDate", arCapLocal.date);
			AddQuestUserData(arCapLocal.QBString1, "sTargetCity", XI_ConvertString("Colony" + arCapLocal + "Acc"));
			if (GetIslandByCityName(arCapBase.(sCapitainId)) != arCapBase.(sCapitainId))
			{
				AddQuestUserData(arCapLocal.QBString1, "sAreal", " that is in " + XI_ConvertString(GetIslandByCityName(arCapBase.(sCapitainId)) + "Dat"));
			}
			//убираем из списка
			DeleteAttribute(arCapBase, sCapitainId); 
		break;
		//<--------------------------- инфа по базе квествых кэпов

		case "ShipStock_1":
			if (CheckAttribute(pchar, "questTemp.HWIC.Holl") && pchar.questTemp.HWIC.Holl == "JacobTakeShip" && !CheckAttribute(npchar, "quest.HWICHoll"))
			{
			dialog.text = "I am listening - which ship, for what term?";
    		Link.l1 = "Lucas Rodenburg sent me. He said that I can moor my ship here for free.";
    		Link.l1.go = "ShipStock_HWICHoll";
			break;
			}
			if (CheckAttribute(pchar, "questTemp.HWIC.Eng") && pchar.questTemp.HWIC.Eng == "GotoPortoffice" && !CheckAttribute(npchar, "quest.HWICEng"))
			{
			dialog.text = "I am listening - which ship, for what term?";
    		Link.l1 = "Richard Fleetwood sent me. He said that I can moor my flagship here for 10000 pesos.";
    		Link.l1.go = "ShipStock_HWICEng";
			break;
			}
            if (sti(NPChar.Portman) >= 3 || CheckAttribute(pchar, "questTemp.HWIC.TakeQuestShip"))
			{
                dialog.text = "Well, that is correct. But unfortunately, I cannot accept your ship at the moment. No dock space available.";
    			Link.l1 = "That's a pity.";
    			Link.l1.go = "exit";
			}
            else
            {
    			ok = (sFrom_sea == "") || (Pchar.location.from_sea == sFrom_sea);
			    if (sti(Pchar.Ship.Type) != SHIP_NOTUSED && ok)
				{
					dialog.text = "And which particular ship are you going to leave here?";
	    			for(i=1; i<COMPANION_MAX; i++)
	                {
	        	        cn = GetCompanionIndex(PChar, i);
	        	        if( cn >0 )
	        	        {
	        		        chref = GetCharacter(cn);
	                        if (!GetRemovable(chref)) continue;
	
	        		        attrL = "l"+i;
	        		        Link.(attrL)    = XI_ConvertString(RealShips[sti(chref.Ship.Type)].BaseName) + " '" + chref.Ship.Name + "'.";
	        		        Link.(attrL).go = "ShipStockMan_" + i;
	        		    }
	        	    }
	    			Link.l9 = "Nevermind, thank you.";
	    			Link.l9.go = "exit";
    			}
    			else
    			{
					dialog.text = "Hmm... I don't see any of your ships.";
	    			Link.l1 = "I just wanted to know about the possibility of parking.";
	    			Link.l1.go = "exit";
				}
			}
		break;

		case "ShipStockMan_1":
            NPChar.ShipToStoreIdx = GetCompanionIndex(PChar, 1);
			dialog.text = "Let's take a look at that ship.";
			Link.l1 = "Fine.";
			Link.l1.go = "ShipStock_2";
			Link.l2 = "No, I've changed my mind.";
			Link.l2.go = "exit";
		break;

		case "ShipStockMan_2":
            NPChar.ShipToStoreIdx = GetCompanionIndex(PChar, 2);
			dialog.text = "Let's take a look at that ship.";
			Link.l1 = "Fine.";
			Link.l1.go = "ShipStock_2";
			Link.l2 = "No, I've changed my mind.";
			Link.l2.go = "exit";
		break;

		case "ShipStockMan_3":
            NPChar.ShipToStoreIdx = GetCompanionIndex(PChar, 3);
			dialog.text = "Let's take a look at that ship.";
			Link.l1 = "Fine.";
			Link.l1.go = "ShipStock_2";
			Link.l2 = "No, I've changed my mind.";
			Link.l2.go = "exit";
		break;
		
		case "ShipStockMan_4":
            NPChar.ShipToStoreIdx = GetCompanionIndex(PChar, 4);
			dialog.text = "Let's take a look at that ship.";
			Link.l1 = "Fine.";
			Link.l1.go = "ShipStock_2";
			Link.l2 = "No, I've changed my mind.";
			Link.l2.go = "exit";
		break;

		case "ShipStock_2":
            chref = GetCharacter(sti(NPChar.ShipToStoreIdx));
			NPChar.MoneyForShip = GetPortManPriceExt(NPChar, chref);
			dialog.Text = XI_ConvertString(RealShips[sti(chref.Ship.Type)].BaseName) + " '" + chref.Ship.Name + "', class " + RealShips[sti(chref.Ship.Type)].Class +
                     ", mooring cost is " + FindRussianMoneyString(sti(NPChar.MoneyForShip)) + " per a month, payment for one month is ahead.";
			Link.l1 = "Yes, that suits me.";
			if (sti(Pchar.Money) >= sti(NPChar.MoneyForShip))
			{
			    Link.l1.go = "ShipStock_3";
			}
			else
			{
                Link.l1.go = "ShipStock_NoMoney";
			}
			Link.l2 = "No, I've changed my mind.";
			Link.l2.go = "exit";
		break;

		case "ShipStock_NoMoney":
			dialog.text = "And it will suit me, too, as soon as you raise the necessary sum.";
			Link.l1 = "Oops... I'll come back later.";
			Link.l1.go = "exit";
		break;

		case "ShipStock_3":
            AddMoneyToCharacter(pchar, -makeint(NPChar.MoneyForShip));
            chref = GetCharacter(sti(NPChar.ShipToStoreIdx));
            chref.ShipInStockMan = NPChar.id;
			// Warship 22.03.09 fix Не перенеслось с КВЛ 1.2.3
			chref.ShipInStockMan.MoneyForShip = NPChar.MoneyForShip;
            chref.ShipInStockMan.AltDate = GetQuestBookDataDigit(); // для печати
            SaveCurrentNpcQuestDateParam(chref, "ShipInStockMan.Date"); // для расчета
            chref.Ship.Crew.Quantity  = 0;
            RemoveCharacterCompanion(pchar, chref);
            chref.location = "";
            chref.location.group = "";
            chref.location.locator = "";

            NPChar.Portman    = sti(NPChar.Portman) + 1;
            pchar.ShipInStock = sti(pchar.ShipInStock) + 1;

			dialog.text = "Alright. You can take your ship back anytime you need.";
			Link.l1 = "Thanks.";
			Link.l1.go = "exit";
		break;

		case "ShipStockReturn_1":
            ok = (sFrom_sea == "") || (Pchar.location.from_sea == sFrom_sea);
		    if (sti(Pchar.Ship.Type) != SHIP_NOTUSED && ok)
			{
				if (GetCompanionQuantity(pchar) < COMPANION_MAX)
	            {
	                dialog.text = "Which particular ship are you going to take?";
	                cn = 1;
	                for(i=1; i<MAX_CHARACTERS; i++)
	            	{
	            		makeref(chref, Characters[i]);
	            		if (CheckAttribute(chref, "ShipInStockMan"))
	            		{
	                        if (chref.ShipInStockMan == NPChar.id)
	        		        {
	                            attrL = "l"+cn;
	            		        Link.(attrL)    = XI_ConvertString(RealShips[sti(chref.Ship.Type)].BaseName) + " '" + chref.Ship.Name + "'.";
	            		        Link.(attrL).go = "ShipStockManBack_" + i;
	            		        cn++;
	        		        }
	            		}
	                }
	
	    			Link.l9 = "No, I've changed my mind.";
	    			Link.l9.go = "exit";
				}
				else
				{
	                dialog.text = "Do you have space for another ship?";
	    			Link.l1 = "Oh, right. Thank you.";
	    			Link.l1.go = "exit";
				}
			}
			else
			{
				dialog.text = "Hmm. I don't see your flagship in the port. And you can only take your ships back here.";
    			Link.l1 = "Alright, I'll come for them later.";
    			Link.l1.go = "exit";
			}
		break;

        case "ShipStockManBack":
            chref = GetCharacter(sti(NPChar.ShipToStoreIdx));
			// --> mitrokosta сюрприз для хитрецов поставивших бунтовщика в ПУ
			if (CheckAttribute(chref, "quest.Mutiny.date")) {
				dialog.text = "Let's see... This ship left the port at " + chref.quest.Mutiny.date + ".";
				link.l1 = "What do you mean by 'left'? She must be here, in the docks!";
				link.l1.go = "ShipStockManMutiny";
				break;
			}
			// <--
            NPChar.MoneyForShip =  GetNpcQuestPastMonthParam(chref, "ShipInStockMan.Date") * sti(chref.ShipInStockMan.MoneyForShip);
			if (sti(NPChar.MoneyForShip) > 0)
			{
			    dialog.Text = "Wanna pick your ship up? For the mooring, you still owe " + FindRussianMoneyString(sti(NPChar.MoneyForShip)) + ".";
			}
			else
			{
				dialog.Text = "Picking up?";
			}
			if (sti(NPChar.MoneyForShip) <= sti(pchar.Money))
			{
				Link.l1 = "Yes.";
				Link.l1.go = "ShipStockManBack2";
			}
			Link.l2 = "No, I've changed my mind.";
			Link.l2.go = "exit";
		break;
		
		case "ShipStockManBack2":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
            AddMoneyToCharacter(Pchar, -sti(NPChar.MoneyForShip));
			chref = GetCharacter(sti(NPChar.ShipToStoreIdx));
			DeleteAttribute(chref, "ShipInStockMan");
			SetCompanionIndex(pchar, -1, sti(NPChar.ShipToStoreIdx));
			NPChar.Portman    = sti(NPChar.Portman) - 1;
            pchar.ShipInStock = sti(pchar.ShipInStock) - 1;
		break;
		
		//--> Jason Голландский гамбит
		case "ShipStock_HWICHoll":
			if (GetCompanionQuantity(pchar) > 1)
			{
				dialog.text = "Yes, yes, I know. But I can only take one ship for the free mooring. So, please, sort out the things with your squadron and then come back again.";
				link.l1 = "Alright, I'll bring just the flagship.";
				link.l1.go = "exit";	
			}
			else
			{
				dialog.text = "Yes, yes, I know. By the order of mynheer Rodenburg we accept your vessel for storage and we will provide an officer of the watch for the entire time your ship stays here. Please sign here... and here...";
				link.l1 = "Alright... I believe, all formalities are now settled?";
				link.l1.go = "ShipStock_HWICHoll_1";	
			}
		break;
		
		case "ShipStock_HWICHoll_1":
			dialog.text = "Yes. Now there's no need for you to worry about your ship - we'll take care of her. You can return to mynheer Rodenburg.";
			link.l1 = "Thank you. Goodbye.";
			link.l1.go = "exit";	
			npchar.quest.HWICHoll = "done";
			pchar.Ship.Type = SHIP_NOTUSED;//все одно сгорит
		break;
		
		case "ShipStock_HWICEng":
			if (GetCompanionQuantity(pchar) > 1)
			{
				dialog.text = "Yes, yes, I know. But I can only take one ship for the free mooring. So, please, sort out the things with your squadron and then come back again.";
				link.l1 = "Alright, I'll bring just the flagship.";
				link.l1.go = "exit";	
			}
			else
			{
				dialog.text = "Yes, of course. Do you have the money on you?";
				if(makeint(Pchar.money) >= 10000)
				{
					link.l1 = "Sure. Here you go.";
					link.l1.go = "ShipStock_HWICEng_1";	
				}
				else
				{
					link.l1 = "No. I'll be back in a moment.";
					link.l1.go = "exit";	
				}
			}
		break;
		
		case "ShipStock_HWICEng_1":
			dialog.text = "Alright. We will take care of your vessel and provide an officer of the watch for the entire time your ship stays here.";
			link.l1 = "Thanks!";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, -10000);
			npchar.quest.HWICEng = "done";
			pchar.Ship.Type = SHIP_NOTUSED;//все одно сгорит
		break;
		//<-- Голландский гамбит
		case "Escort_companion":
			dialog.text = "Did you want anything, cap?";
			link.l1 = "No, nothing.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Escort_companion";
		break;
		
		// --> mitrokosta сюрприз для хитрецов поставивших бунтовщика в ПУ
		case "ShipStockManMutiny":
			chref = GetCharacter(sti(NPChar.ShipToStoreIdx));
			DeleteAttribute(chref, "ShipInStockMan");
			NPChar.Portman    = sti(NPChar.Portman) - 1;
            pchar.ShipInStock = sti(pchar.ShipInStock) - 1;
			dialog.text = "Your officer " + GetFullName(chref) + " informed" + NPCharSexPhrase(chref, "", "") + " me that " + NPCharSexPhrase(chref, "he", "she") + " had to go to sea by your order. I did not object " + NPCharSexPhrase(chref, "him", "her") + ".";
			link.l1 = "Fuck! There was no such order! Should not have entrusted my shipt to the bastard! Eh, whatever, nothing I can do about my loss anyway.";
			link.l1.go = "ShipStockManMutiny1";
			// вот тут можно микроквестик сделать
			//link.l2 = "What a surprise... Did " + NPCharSexPhrase(chref, "he", "she") + " tell you, where they went, by any chance?";
			//link.l2.go = "ShipStockManMutiny2";
		break;
		
		case "ShipStockManMutiny1":
			chref = GetCharacter(sti(NPChar.ShipToStoreIdx));
			chref.lifeday = 0;

			dialog.text = "I'm sorry, " + GetAddress_Form(NPChar) + ". You should be more careful with your subordinates.";
			link.l1 = "I know, I'm an idiot. Goodbye, " + GetAddress_Form(NPChar) + ".";
			link.l1.go = "exit";
		break;
		// <--
	}
}

float BurntShipQuest_GetMaxNeededValue(int iShipType, string _param)
{
	float NeededValue = makefloat(GetBaseShipParamFromType(iShipType, _param));
	switch (_param)
	{
		case "speedrate":
			NeededValue += ((0.72 + frandSmall(0.30)) * (NeededValue/10.0)); 
		break;
		case "turnrate":
			NeededValue += ((0.72 + frandSmall(0.30)) * (NeededValue/10.0)); 
		break;
		case "capacity":
			NeededValue += ((0.72 + frandSmall(0.30)) * (NeededValue/8.0)); 
		break;
	}
	return NeededValue;
}

// Warship 25.07.09 Генер "A burnt vessel". Начальные иниты для портмана - тип разыскиваемого судна, выдающаяся характеристика и т.д.
void BurntShipQuest_FillStartParams(ref _npchar)
{
	int rank = sti(PChar.rank);
	int shipType, temp;
	float neededValue;
	String shipAttribute;
	
	// TODO Пересмотреть зависимость от ранга
	if(rank <= 5)
	{
		shipType = SHIP_LUGGER + rand(1);
		
		switch(shipType)
		{
			case SHIP_LUGGER:
				shipAttribute = "speedrate";
			break;
			
			case SHIP_SLOOP:
				temp = rand(2);
				
				if(temp == 2)
				{
					shipAttribute = "speedrate";
				}
				else
				{
					if(temp == 1)
					{
						shipAttribute = "turnrate";
					}
					else
					{
						shipAttribute = "capacity";
					}
				}
			break;
		}
	}
	
	if(rank > 5 && rank <= 15)
	{
		shipType = SHIP_SCHOONER + rand(2);
		
		switch(shipType)
		{
			case SHIP_SCHOONER:
				if(rand(1) == 0)
				{
					shipAttribute = "speedrate";
				}
				else
				{
					shipAttribute = "turnrate";
				}
			break;
			
			case SHIP_BARKENTINE:
				shipAttribute = "capacity";
			break;
			
			case SHIP_SHNYAVA:
				shipAttribute = "capacity";
			break;
		}
	}
	
	if(rank > 15 && rank <= 25)
	{
		shipType = SHIP_FLEUT + rand(3);
		
		switch(shipType)
		{
			case SHIP_FLEUT:
				shipAttribute = "turnrate";
			break;
			
			case SHIP_CARAVEL:
				if(rand(1) == 1)
				{
					shipAttribute = "speedrate";
				}
				else
				{
					shipAttribute = "turnrate";
				}
			break;
			
			case SHIP_PINNACE:
				shipAttribute = "capacity";
			break;
			
			case SHIP_CARACCA:
				if(rand(1) == 1)
				{
					shipAttribute = "speedrate";
				}
				else
				{
					shipAttribute = "turnrate";
				}
			break;
			
		}
	}
	
	if(rank > 25 && rank <= 35)
	{
		shipType = SHIP_SCHOONER_W + rand(2);
		
		switch(shipType)
		{
			case SHIP_SCHOONER_W:
				if(rand(1) == 1)
				{
					shipAttribute = "speedrate";
				}
				else
				{
					shipAttribute = "turnrate";
				}
			break;
			
			case SHIP_GALEON_L:
				shipAttribute = "capacity";
			break;
			
			case SHIP_CORVETTE:
				if(rand(1) == 1)
				{
					shipAttribute = "speedrate";
				}
				else
				{
					shipAttribute = "capacity";
				}
			break;
		}
	}
	
	if(rank > 35)
	{
		shipType = SHIP_GALEON_H + rand(1);
		
		switch(shipType)
		{
			case SHIP_GALEON_H:
				temp = rand(2);
				
				if(temp == 0)
				{
					shipAttribute = "speedrate";
				}
				else
				{
					if(temp == 1)
					{
						shipAttribute = "turnrate";
					}
					else
					{
						shipAttribute = "capacity";
					}
				}
			break;
			
			case SHIP_FRIGATE:
				shipAttribute = "turnrate";
			break;
		}
	}
	
	neededValue = BurntShipQuest_GetMaxNeededValue(shipType, shipAttribute);
	
	Log_TestInfo("shipType == " + shipType);
	Log_TestInfo("ShipAttribute == " + shipAttribute);
	Log_TestInfo("ShipNeededValue == " + neededValue);
	
	_npchar.Quest.BurntShip.ShipType = shipType;
	_npchar.Quest.BurntShip.ShipAttribute = shipAttribute;
	
	if(shipAttribute != "capacity") // Чтобы трюм с десятичными не писался
	{
		_npchar.Quest.BurntShip.ShipNeededValue = FloatToString(neededValue, 2);
	}
	else
	{
		_npchar.Quest.BurntShip.ShipNeededValue = MakeInt(neededValue);
	}
}

void SetJornalCapParam(ref npchar)
{
	//созадем рассеянного кэпа
	ref sld = GetCharacter(NPC_GenerateCharacter("PortmansCap_" + npchar.index, "", "man", "man", 20, sti(npchar.nation), -1, true, "citizen"));
	SetShipToFantom(sld, "trade", true);
	sld.Ship.Mode = "trade";
	SetCaptanModelByEncType(sld, "trade");
	sld.dialog.filename = "Quest\ForAll_dialog.c";
	sld.dialog.currentnode = "PortmansCap";
	sld.DeckDialogNode = "PortmansCap_inDeck";
	DeleteAttribute(sld, "SinkTenPercent");
	DeleteAttribute(sld, "SaveItemsForDead");
	DeleteAttribute(sld, "DontClearDead");
	DeleteAttribute(sld, "AboardToFinalDeck");
	DeleteAttribute(sld, "SinkTenPercent");
	DeleteAttribute(sld, "DontRansackCaptain");
	sld.AlwaysSandbankManeuver = true;
	sld.AnalizeShips = true;  //анализировать вражеские корабли при выборе таска
	sld.DontRansackCaptain = true; //не сдаваться
	SetCharacterPerk(sld, "ShipTurnRateUp");
	SetCharacterPerk(sld, "ShipTurnRateUp");
	LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER_OWN);
	//в морскую группу кэпа
	string sGroup = "PorpmansShip_" + sld.index;
	Group_FindOrCreateGroup(sGroup);
	Group_SetType(sGroup,"trade");
	Group_SetTaskAttackInMap(sGroup, PLAYER_GROUP);
	Group_LockTask(sGroup);
	Group_AddCharacter(sGroup, sld.id);
	Group_SetGroupCommander(sGroup, sld.id);
	SetRandGeraldSail(sld, sti(sld.Nation)); 
	//записываем данные в структуры портмана и кэпа
	npchar.quest = "PortmansJornal"; //личный флаг квеста для портмана
	npchar.quest.PortmansJornal.capName = GetFullName(sld); //имя кэпа
	npchar.quest.PortmansJornal.shipName = sld.Ship.name; //имя корабля
	npchar.quest.PortmansJornal.shipTapeName = RealShips[sti(sld.Ship.Type)].BaseName; //название корабля
	npchar.quest.PortmansJornal.city = SelectNotEnemyColony(npchar); //определим колонию, куда ушел кэп
	sld.quest = "InMap"; //личный флаг рассеянного кэпа
	sld.quest.targetCity = npchar.quest.PortmansJornal.city; //продублируем колонию-цель в структуру кэпа
	sld.quest.firstCity = npchar.city; //капитану знать откуда вышел в самом начале
	sld.quest.stepsQty = 1; //количество выходов в море
	sld.quest.money = ((sti(RealShips[sti(sld.Ship.Type)].basetype)+1) * 150) + (sti(pchar.rank)*150); //вознаграждение
	Log_TestInfo("The absent-minded cap " + sld.id + " went to: " + sld.quest.targetCity);
	//определим бухту, куда ставить энкаунтер. чтобы сразу не генерился перед ГГ у города
	string sTemp = GetArealByCityName(npchar.city);
	sld.quest.baseShore = GetIslandRandomShoreId(sTemp);
	//на карту
	sld.mapEnc.type = "trade";
	sld.mapEnc.worldMapShip = "ranger";
	sld.mapEnc.Name = XI_ConvertString(npchar.quest.PortmansJornal.shipTapeName) + " '" + npchar.quest.PortmansJornal.shipName + "'";
	int daysQty = GetMaxDaysFromIsland2Island(sTemp, GetArealByCityName(sld.quest.targetCity))+5; //дней доехать даем с запасом
	Map_CreateTrader(sld.quest.baseShore, sld.quest.targetCity, sld.id, daysQty);
	//заносим Id кэпа в базу нпс-кэпов
	sTemp = sld.id;
	NullCharacter.capitainBase.(sTemp).quest = "jornal"; //идентификатор квеста
	NullCharacter.capitainBase.(sTemp).questGiver = "none"; //запомним Id квестодателя для затирки в случае чего
	NullCharacter.capitainBase.(sTemp).Tilte1 = npchar.id + "PortmansBook_Delivery"; //заголовок квестбука
	NullCharacter.capitainBase.(sTemp).Tilte2 = "PortmansBook_Delivery"; //имя квеста в квестбуке
	NullCharacter.capitainBase.(sTemp).checkTime = daysQty + 5;
    NullCharacter.capitainBase.(sTemp).checkTime.control_day = GetDataDay();
    NullCharacter.capitainBase.(sTemp).checkTime.control_month = GetDataMonth();
    NullCharacter.capitainBase.(sTemp).checkTime.control_year = GetDataYear();
}
//проверить список отметившихся квестовых кэпов
int CheckCapitainsList(ref npchar)
{
	int bResult = 0;
	if (!CheckAttribute(npchar, "quest.capitainsList")) return bResult;
	aref arCapBase, arCapLocal;
    makearef(arCapBase, npchar.quest.capitainsList);
    int	Qty = GetAttributesNum(arCapBase);
	if (Qty < 1) return bResult;
	string sCapitainId; 
	for (int i=0; i<Qty; i++)
    {
    	arCapLocal = GetAttributeN(arCapBase, i);
        sCapitainId = GetAttributeName(arCapLocal);
    	if (GetCharacterIndex(sCapitainId) > 0) //если еще жив
    	{
			bResult++;			
    	}
		else
		{
			DeleteAttribute(arCapBase, sCapitainId);
			i--;
			Qty--;
		}
    }
	if (bResult > 5) bResult = 5;
	return bResult;
}

void SetSeekShipCapParam(ref npchar)
{
	//создаем кэпа-вора
	int Rank = sti(pchar.rank) + 5;
	if (Rank > 30) Rank = 30;
	ref sld = GetCharacter(NPC_GenerateCharacter("SeekCap_" + npchar.index, "", "man", "man", Rank, PIRATE, -1, true, "soldier"));
	SetShipToFantom(sld, "pirate", true);
	sld.Ship.Mode = "pirate";
	SetCaptanModelByEncType(sld, "pirate");
	sld.dialog.filename = "Quest\ForAll_dialog.c";
	sld.dialog.currentnode = "SeekCap";
	sld.DeckDialogNode = "SeekCap_inDeck";
	DeleteAttribute(sld, "SinkTenPercent");
	DeleteAttribute(sld, "SaveItemsForDead");
	DeleteAttribute(sld, "DontClearDead");
	DeleteAttribute(sld, "AboardToFinalDeck");
	DeleteAttribute(sld, "SinkTenPercent");
	DeleteAttribute(sld, "DontRansackCaptain");
	sld.AlwaysSandbankManeuver = true;
	sld.AnalizeShips = true;  //анализировать вражеские корабли при выборе таска
	sld.DontRansackCaptain = true; //не сдаваться
	SetCharacterPerk(sld, "FastReload");
	SetCharacterPerk(sld, "HullDamageUp");
	SetCharacterPerk(sld, "SailsDamageUp");
	SetCharacterPerk(sld, "CrewDamageUp");
	SetCharacterPerk(sld, "CriticalShoot");
	SetCharacterPerk(sld, "LongRangeShoot");
	SetCharacterPerk(sld, "CannonProfessional");
	SetCharacterPerk(sld, "ShipDefenseProfessional");
	SetCharacterPerk(sld, "ShipTurnRateUp");
	SetCharacterPerk(sld, "ShipTurnRateUp");
	SetCharacterPerk(sld, "StormProfessional");
	SetCharacterPerk(sld, "SwordplayProfessional");
	SetCharacterPerk(sld, "AdvancedDefense");
	SetCharacterPerk(sld, "CriticalHit");
	SetCharacterPerk(sld, "Sliding");
	SetCharacterPerk(sld, "Tireless");
	SetCharacterPerk(sld, "HardHitter");
	SetCharacterPerk(sld, "GunProfessional");
	//в морскую группу кэпа
	string sGroup = "SeekCapShip_" + sld.index;
	Group_FindOrCreateGroup(sGroup);
	Group_SetTaskAttackInMap(sGroup, PLAYER_GROUP);
	Group_LockTask(sGroup);
	Group_AddCharacter(sGroup, sld.id);
	Group_SetGroupCommander(sGroup, sld.id);
	SetRandGeraldSail(sld, sti(sld.Nation)); 
	//записываем данные в структуры портмана и кэпа
	npchar.quest = "PortmansSeekShip"; //личный флаг квеста для портмана
	npchar.quest.PortmansSeekShip.capName = GetFullName(sld); //имя кэпа-вора
	npchar.quest.PortmansSeekShip.shipName = sld.Ship.name; //имя украденного корабля
	npchar.quest.PortmansSeekShip.shipTapeName = RealShips[sti(sld.Ship.Type)].BaseName; //название украденного корабля
	npchar.quest.PortmansSeekShip.shipTape = RealShips[sti(sld.Ship.Type)].basetype; //тип украденного корабля
	//npchar.quest.money = ((sti(RealShips[sti(sld.Ship.Type)].basetype)+1) * 1000) + (sti(pchar.rank)*500); //вознаграждение
	npchar.quest.chest = 7-sti(RealShips[sti(sld.Ship.Type)].Class); //в сундуках
	sld.quest = "InMap"; //личный флаг кэпа-вора
	sld.city = SelectAnyColony(npchar.city); //определим колонию, откуда кэп-вор выйдет
	sld.quest.targetCity = SelectAnyColony2(npchar.city, sld.city); //определим колонию, куда он придет
	//Log_TestInfo("Thieving cap " + sld.id + " sailed out of: " + sld.city + " and went to: " + sld.quest.targetCity);
	sld.quest.cribCity = npchar.city; //город, откуда кэп-вор спер корабль
	//на карту
	sld.mapEnc.type = "trade";
	sld.mapEnc.worldMapShip = "Galleon_red";
	sld.mapEnc.Name = XI_ConvertString(npchar.quest.PortmansSeekShip.shipTapeName) + " '" + npchar.quest.PortmansSeekShip.shipName + "'";
	int daysQty = GetMaxDaysFromIsland2Island(GetArealByCityName(sld.quest.targetCity), GetArealByCityName(sld.city))+3; //дней доехать даем с запасом
	Map_CreateTrader(sld.city, sld.quest.targetCity, sld.id, daysQty);
	//прерывание на абордаж
	string sTemp = "SeekShip_checkAbordage" + npchar.index;
	pchar.quest.(sTemp).win_condition.l1 = "Character_Capture";
	pchar.quest.(sTemp).win_condition.l1.character = sld.id;
	pchar.quest.(sTemp).function = "SeekShip_checkAbordage";
	pchar.quest.(sTemp).CapId = sld.id;
	//прерывание на потопление без абордажа
	sTemp = "SeekShip_checkSink" + npchar.index;
	pchar.quest.(sTemp).win_condition.l1 = "Character_sink";
	pchar.quest.(sTemp).win_condition.l1.character = sld.id;
	pchar.quest.(sTemp).function = "SeekShip_checkSink";
	pchar.quest.(sTemp).CapId = sld.id;
	//заносим Id кэпа в базу нпс-кэпов
	sTemp = sld.id;
	NullCharacter.capitainBase.(sTemp).quest = "robber"; //идентификатор квеста
	NullCharacter.capitainBase.(sTemp).questGiver = "none"; //запомним Id квестодателя для затирки в случае чего
	NullCharacter.capitainBase.(sTemp).Tilte1 = npchar.id + "Portmans_SeekShip"; //заголовок квестбука
	NullCharacter.capitainBase.(sTemp).Tilte2 = "Portmans_SeekShip"; //имя квеста в квестбуке
	NullCharacter.capitainBase.(sTemp).checkTime = daysQty + 5;
    NullCharacter.capitainBase.(sTemp).checkTime.control_day = GetDataDay();
    NullCharacter.capitainBase.(sTemp).checkTime.control_month = GetDataMonth();
    NullCharacter.capitainBase.(sTemp).checkTime.control_year = GetDataYear();
}

string GenQuestPortman_GenerateGem() // камни
{
	string itemID;
	switch(rand(5))
	{
		case 0:
			itemID = "jewelry1";	
		break;
		case 1:
			itemID = "jewelry2"; 
		break;
		case 2:
			itemID = "jewelry3"; 
		break;
		case 3:
			itemID = "jewelry3"; 
		break;
		case 4:
			itemID = "jewelry5"; 
		break;
		case 5:
			itemID = "jewelry6"; 
		break;
	}
	return itemID;
}

string findTraderCity_PU(ref NPChar)
{
	int n, nation;
    int storeArray[MAX_COLONIES];
    int howStore = 0;

	for(n=0; n<MAX_COLONIES; n++)
	{
		nation = GetNationRelation(sti(npchar.nation), sti(colonies[n].nation));
		if (nation != RELATION_ENEMY && colonies[n].id != "Panama" && colonies[n].id != "Minentown" && colonies[n].id != "SanAndres" && colonies[n].nation != "none" && GetIslandByCityName(npchar.city) != colonies[n].islandLable) //на свой остров
		{
			storeArray[howStore] = n;
			howStore++;
		}
	}
	if (howStore == 0) return "none";
	nation = storeArray[cRand(howStore-1)];
	return colonies[nation].id;
}

string findPassangerCity_PU(ref NPChar)
{
	int n, nation;
    int storeArray[MAX_COLONIES];
    int howStore = 0;

	for(n=0; n<MAX_COLONIES; n++)
	{
		nation = GetNationRelation(sti(npchar.nation), sti(colonies[n].nation));
		if (nation != RELATION_ENEMY && colonies[n].nation != "none" && colonies[n].id != "Panama" && colonies[n].id != "Minentown" && colonies[n].id != "SanAndres" && GetIslandByCityName(npchar.city) != colonies[n].islandLable) //на свой остров
		{
			storeArray[howStore] = n;
			howStore++;
		}
	}
	if (howStore == 0) return "none";
	nation = storeArray[cRand(howStore-1)];
	return colonies[nation].id;
}

// --> Jason, новые мини-квесты
string findCurrentCity1(ref NPChar)//выбираем целевой город 1
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

string findCurrentCity2(ref NPChar)//выбираем целевой город 2
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
	nation = storeArray[abs(dRand(howStore-1)-3)];
	return colonies[nation].id;
}

string findCurrentCity3(ref NPChar)//выбираем целевой город 3
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
	nation = storeArray[abs(dRand(howStore-1)-7)];
	return colonies[nation].id;
}

int Escort_ShipType()
{
	int iShipType;
	switch (rand(2))
	{
		case 0: iShipType = SHIP_FLEUT; 	break;
		case 1: iShipType = SHIP_GALEON_L; 	break;
		case 2: iShipType = SHIP_PINNACE;	break;
	}
	return iShipType;
}

//<-- новые мини-квесты