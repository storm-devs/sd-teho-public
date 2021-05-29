//Jason общий диалог мещан
#include "DIALOGS\russian\Rumours\Common_rumours.c"
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

    // вызов диалога по городам -->
    NPChar.FileDialog2 = "DIALOGS\" + LanguageGetLanguage() + "\Citizen\" + NPChar.City + "_Citizen.c";
    if (LoadSegment(NPChar.FileDialog2))
	{
        ProcessCommonDialog(NPChar, Link, NextDiag);
		UnloadSegment(NPChar.FileDialog2);
	}
    // вызов диалога по городам <--
    ProcessCommonDialogRumors(NPChar, Link, NextDiag);
    int iTest, iTemp;
    iTest = FindColony(NPChar.City);
    ref rColony;
    string sTemp, sCity, sTitle;
	if (iTest != -1)
	{
		rColony = GetColonyByIndex(iTest);
	}
	
	String attrLoc = Dialog.CurrentNode;
	
	if(HasSubStr(attrLoc, "RumourAboutOwners_"))
	{
		NPChar.RumourOwnerType = FindStringAfterChar(attrLoc, "_");
		Dialog.CurrentNode = "RumourAboutOwners_TakeRumour";
	}
	
	switch(Dialog.CurrentNode)
	{
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "fight":
            LAi_group_Attack(NPChar, Pchar);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "First time":
			if (sti(NPChar.nation) == PIRATE)
			{
				if (sti(rColony.HeroOwn) == true) // наш горожанин
				{
				    dialog.text = RandPhraseSimple("They say that you own this town, "+ GetSexPhrase("sir","miss") + ".", "Such a nice meeting, "+ GetSexPhrase("sir","miss") + "!");
					link.l1 = RandPhraseSimple("I've changed my mind. Good luck!", "Just walking around the town. Goodbye.");
					link.l1.go = "exit";
					link.l2 = RandPhraseSimple("I've got a question for you.", "I need some information.");
					link.l2.go = "quests";//(перессылка в файл города)
					if (CheckAttribute(pchar, "GenQuest.Loan.FindCitizen") && !CheckAttribute(pchar, "GenQuest.Loan.FindCitizenDone") && !CheckAttribute(pchar, "GenQuest.Loan.FindCitizenFalied"))
		            {
		                if (Characters[sti(pchar.GenQuest.Loan.FindCitizenIdx)].id == Npchar.id)
		                {
							link.l3 = RandPhraseSimple("I want to discuss financial matters.", "About financials...");
							link.l3.go = "LoanForAll";//(перессылка в кредитный генератор)
						}
					}
					break;
				}
				else
				{ // пираты, не наши
					if (sti(pchar.GenQuest.Piratekill) > 20)
					{
						dialog.text = RandPhraseSimple("Alarm! An armed loony here! To arms!", "To arms! An armed loony here!");
						link.l1 = RandPhraseSimple("What?!", "What are you doing?!");
						link.l1.go = "pirate_fight";
					}
					else
					{
				    dialog.text = RandPhraseSimple("What do you want? Move along.", "Stop blocking my way, get lost.");
					link.l1 = RandPhraseSimple("You know what? Don't bark!", "Calm yourself down. Or I will do it myself!");
					link.l1.go = "exit";
					link.l2 = RandPhraseSimple("I want to ask you.", "Just a minute of your attention, please. One question.");
					link.l2.go = "quests";//(перессылка в файл города)
					if (CheckAttribute(pchar, "GenQuest.Loan.FindCitizen") && !CheckAttribute(pchar, "GenQuest.Loan.FindCitizenDone") && !CheckAttribute(pchar, "GenQuest.Loan.FindCitizenFalied"))
		            {
		                if (Characters[sti(pchar.GenQuest.Loan.FindCitizenIdx)].id == Npchar.id)
		                {
							link.l3 = RandPhraseSimple("I want to discuss financial matters.", "About financials...");
							link.l3.go = "LoanForAll";//(перессылка в кредитный генератор)
						}
					}
					}
				}
				break;
			}
            if(NPChar.quest.meeting == "0")
			{
				NPChar.quest.meeting = "1";
				// проверка наличия корабля в порту
				bool ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
				if (ok && sti(Pchar.Ship.Type) != SHIP_NOTUSED && CheckAttribute(npchar, "quest.passenger") && !CheckAttribute(pchar, "GenQuest.Townpassenger") && 6-sti(RealShips[sti(Pchar.Ship.Type)].Class) > 0)//горожанин-пассажир
				{
					dialog.text = "Good day, "+GetAddress_Form(NPChar)+". I see that you are a captain of your own ship. I want to ask you about a favour...";
					link.l1 = "I am listening, "+GetAddress_FormToNPC(NPChar)+". What do you want?";
					link.l1.go = "passenger";
					link.l2 = "I am sorry, "+GetAddress_FormToNPC(NPChar)+", but I am in a hurry.";
					link.l2.go = "exit";
					npchar.quest.meeting = "1";
					DeleteAttribute(npchar, "talker"); //снимаем говорилку
					break;
				}

                // homo 05/08/06
				dialog.Text =NPCharRepPhrase(npchar,
				LinkRandPhrase("I am ", "My name is ", "You can call me ")
				+GetFullName(npchar)
				+LinkRandPhrase(". What do you want?", ". I have not seen you before. Who are you?", ". Who are you and what do you want from me?"),

				LinkRandPhrase("Greetings, " + GetAddress_Form(NPChar) + ". My name is " + GetFullName(npchar) + ". And what's your name?",
				 "Hello, " + GetAddress_Form(NPChar) + "! I am " + GetFullName(npchar) + ". Can I know your name?",
				 "Yes, " + GetAddress_Form(NPChar) + ". What do you want? And by the way my name is " + GetFullName(npchar) + ". And what's your name?"));

				Link.l1 = pcharrepphrase(
				LinkRandPhrase("Damn me! ", "Damn! ", "Damn you! ") + "Yes I am the captain "+ GetFullName(Pchar)+ LinkRandPhrase(", haven't you ever heard "+NPCharSexPhrase(NPChar,", bastard?","?"), " and "+ GetSexPhrase("the most famous pirate","the most famous girl-pirate") +" in the sea!", " and damn me if I am wrong!"),
				LinkRandPhrase("I am " + GetFullName(Pchar) + ", captain.", "My name is " + GetFullName(Pchar) + ".", "You can call me captain "+GetFullName(Pchar)+"."));
				Link.l1.go = "Meeting";
			}
			else
			{
				link.l1 = PCharRepPhrase("I just wanna ask something about this hole you call 'the town'.", "I want to ask you something about this town.");
				link.l1.go = "new question";
 				link.l2 = RandPhraseSimple("I've got a question for you.", "I need some information.");
				if (CheckCharacterItem(pchar, "CaptainBook"))				
				{
					if((pchar.questTemp.different.GiveShipLetters.city == npchar.city) && CheckAttribute(pchar, "questTemp.different.GiveShipLetters"))
					{
						link.l2.go = "ShipLetters_7";// генератор  "Найденные документы"
					}
					else
					{
						link.l2.go = "quests";
					}	
				}
				else
				{
					link.l2.go = "quests";//(перессылка в файл города)
				}	
				if (CheckAttribute(pchar, "GenQuest.Loan.FindCitizen") && !CheckAttribute(pchar, "GenQuest.Loan.FindCitizenDone") && !CheckAttribute(pchar, "GenQuest.Loan.FindCitizenFalied"))
	            {
	                if (Characters[sti(pchar.GenQuest.Loan.FindCitizenIdx)].id == Npchar.id)
	                {
						link.l3 = RandPhraseSimple("I want to discuss financial matters.", "About financials...");
						link.l3.go = "LoanForAll";//(перессылка в кредитный генератор)
					}
				}
				
				//Jason --> генератор Неудачливый вор
				if (CheckAttribute(pchar, "GenQuest.Device.Shipyarder") && NPChar.location == pchar.GenQuest.Device.Shipyarder.City + "_town" && pchar.GenQuest.Device.Shipyarder == "begin" && !CheckAttribute(npchar, "quest.Device"))
				{
					link.l16 = "Listen, I hope that you can help me. I want to buy a "+pchar.GenQuest.Device.Shipyarder.Type+", and I've been told that this thing was been sold in your town. Well, someone was selling it on streets. Do you know something?";
					link.l16.go = "Device_Citizen";
				}
				// <-- генератор Неудачливый вор
				
				// Квестовый генератор священника. Квест №2. Warship -->
				if(CheckAttribute(PChar, "GenQuest.ChurchQuest_2.AskPeople") && !CheckAttribute(NPChar, "GenQuest.ChurchQuest_2.AskedPeople") && NPChar.location == PChar.GenQuest.ChurchQuest_2.QuestTown + "_town")
	            {
					link.l5 = LinkRandPhrase("Do you know ", "Are you aware ", "Have you heard ") + " that the local church has been robbed recently?";
					link.l5.go = "Citiz_GenQuest_Church_2_1";
				}
				// <-- Квестовый генератор священника. Квест №2.
				
				dialog.Text = NPCharRepPhrase(npchar,
		                PCharRepPhrase(LinkRandPhrase("Ah, it's you "+GetFullName(Pchar)
                        +" "+ GetSexPhrase("- old friend!","- pretty one!") +"", "I'm glad to see you, "+ GetSexPhrase("old friend!","pretty one!") +" "
                        + Pchar.name, "Oh, that's the "+ GetSexPhrase("captain himself","captain herself") +" "
                         +GetFullName(Pchar))
						+RandPhraseSimple(". I thought that you are dead!", ". And perhaps "+ GetSexPhrase("drunk as always.","a bit drunk.") )
						+LinkRandPhrase(" Go on, what do you need?", " What's this time?", " Bothering me again?"),
						LinkRandPhrase(TimeGreeting() + ", captain ", "Good day to you, "+GetAddress_Form(NPChar)+" ", "Greeting, captain ")+GetFullName(Pchar)
						+LinkRandPhrase(". How can I help to "+ GetSexPhrase("such a worthy man","such a worthy girl") +", like you?", ". Why are you here?", ". What do you want to know this time?")),             
                        PCharRepPhrase(LinkRandPhrase("Hello, captain ", "Greetings, ah, it's you "+GetAddress_Form(NPChar)+" ", "Ah, captain ")
						+GetFullName(Pchar)
						+LinkRandPhrase(", I thought we will never meet again, and",
										 ", I won't say that I'm glad to see you but", ", I see that you are still alive, what a shame and")
						+LinkRandPhrase(" what do you want?", " why are you here?", " how can I help you?"),
						LinkRandPhrase(TimeGreeting() + ", captain " + GetFullName(Pchar) + ". How can I help you?",
						"Oh, that's the captain " + GetFullName(Pchar) + "! How can I help you?",
						"Greetings, " + GetAddress_Form(NPChar) + " " + Pchar.lastname + ". Do you want anything?"))
						);  
	   			link.l6 = PCharRepPhrase(RandPhraseSimple("Your ears deceive you. I have to go.", "No, it's nothing, I was on my way to the tavern."),
						RandPhraseSimple("Fine, whatever. Good luck!", "Just walking around the city. Farewell."));
				link.l6.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "ShipLetters_7":
			dialog.text = "Questions?";
			link.l1 = "Does the name on this papers mean anything for you?";
			link.l1.go = "ShipLetters_8";
		break;
		
		case "ShipLetters_8":
			dialog.text = LinkRandPhrase("I don't give a damn about unknown paper and I don't know how to read. Go to the usurer, they say that he knows how to read those devil's letters.",
			"I don't know what you are talking about, ask other citizens of the town, captain" + GetFullName(Pchar) + ".", 
			"I don't even know how to help you, captain " + GetFullName(Pchar) + ". Try to talk with the usurer, he might know.");
			link.l1 = "I will follow your advice with a great pleasure!";
			link.l1.go = "exit";
		break;
		
		case "Meeting":
		    dialog.Text  = NPCharRepPhrase(npchar, LinkRandPhrase("Aren't you lying, captain " + GetFullName(Pchar)+"?",
				"So what " + PChar.name+"?",
				"I will remember you, " + GetFullName(Pchar)+".")
				 + " Now tell me what do you want?",
				LinkRandPhrase("Nice to meet you, captain " + PChar.name,
				"Glad our meeting, " + GetAddress_Form(NPChar) + " " + PChar.lastname,
				 "It's a pleasure, captain " + PChar.name) + ". But I doubt that you were only willing to know my name, right?");
            link.l1 = PCharRepPhrase("I just wanna ask something about this hole you call 'the town'.", "I want to ask you something about this town.");
			link.l1.go = "new question";
            Link.l2 = RandPhraseSimple("I've got a question for you.", "I need some information.");
			if (CheckCharacterItem(pchar, "CaptainBook"))				
			{
				if((pchar.questTemp.different.GiveShipLetters.city == npchar.city) && CheckAttribute(pchar, "questTemp.different.GiveShipLetters"))
				{
					link.l2.go = "ShipLetters_7";// генератор  "Найденные документы"
				}
				else
				{
					Link.l2.go = "quests";
				}	
			}
			else
			{
					link.l2.go = "quests";//(перессылка в файл города)
			}			
			if (CheckAttribute(pchar, "GenQuest.Loan.FindCitizen") && !CheckAttribute(pchar, "GenQuest.Loan.FindCitizenDone") && !CheckAttribute(pchar, "GenQuest.Loan.FindCitizenFalied"))
            {
                if (Characters[sti(pchar.GenQuest.Loan.FindCitizenIdx)].id == Npchar.id)
                {
					link.l3 = RandPhraseSimple("I want to discuss financial matters.", "About financials...");
					link.l3.go = "LoanForAll";//(перессылка в кредитный генератор)
				}
			}
			
			//Jason --> генератор Неудачливый вор
			if (CheckAttribute(pchar, "GenQuest.Device.Shipyarder") && NPChar.location == pchar.GenQuest.Device.Shipyarder.City + "_town" && pchar.GenQuest.Device.Shipyarder == "begin" && !CheckAttribute(npchar, "quest.Device"))
			{
   				link.l16 = "Listen, I hope that you can help me. I want to buy a "+pchar.GenQuest.Device.Shipyarder.Type+", and I've been told that this thing has been sold in your town. Well, someone was selling it on streets. Do you know anything about it?";
				link.l16.go = "Device_Citizen";
			}
			// <-- генератор Неудачливый вор
			
			// Квестовый генератор священника. Квест №2. Warship -->
			if(CheckAttribute(PChar, "GenQuest.ChurchQuest_2.AskPeople") && !CheckAttribute(NPChar, "GenQuest.ChurchQuest_2.AskedPeople") && NPChar.location == PChar.GenQuest.ChurchQuest_2.QuestTown + "_town")
	        {
				link.l5 = LinkRandPhrase("Do you know ", "Are you aware ", "Have you heard ") + " that the local church was robbed recently?";
				link.l5.go = "Citiz_GenQuest_Church_2_1";
			}
			// <-- Квестовый генератор священника. Квест №2.
			
			Link.l6 = PCharRepPhrase(RandPhraseSimple("Your ears deceive you. I have to go.", "No, it's nothing, I was on my way to the tavern."),
                                        RandPhraseSimple("Well, it's nothing, Good luck!", "Just walking around the city. Goodbye."));
			Link.l6.go = "exit";
		break;
		
		case "new question":
            dialog.text = NPCharRepPhrase(npchar,
				PCharRepPhrase(LinkRandPhrase("Oh, and I am glad to see you like I'm glad for a booze, ask whatever you want.", "Like talking, captain? So do I... Especially with a cup of rum.", "Yes, " + PChar.name + "?"),
				LinkRandPhrase("What else do you want?", "I take it, captain "+PChar.name+", that you are fond of chatting?")),
		        PCharRepPhrase(LinkRandPhrase("What else do you want, "+ GetAddress_Form(NPChar) + "?", "I am listening, captain.", "I need to go, so ask me quickly, captain."),
                LinkRandPhrase("I am always glad for a  pleasant company, " + GetAddress_Form(NPChar) + " " + PChar.lastname + ". Speak.",
                "Yes, " + GetAddress_Form(NPChar) + "?",
                "Like talking, captain? So do I... ")));
			link.l1 = LinkRandPhrase ("What rumors are around in this town?","Any news in this land?","How is going the land life?");
			link.l1.go = "rumours_townman";
			link.l2 = LinkRandPhrase("Can you show me the road?", "I can't find the road to one place...", "Help me to get one place...");
			link.l2.go = "town";  //(перессылка в файл города)
			link.l3 = RandPhraseSimple("I want to know what people say about one person.", "Do you know what people say about one person?");
			link.l3.go = "info"; //(перессылка в файл города)
			link.l4 = RandPhraseSimple("I want to know more about the locals.", "Can you tell me anything about the locals?");
			link.l4.go = "RumourAboutOwners";
			link.l5 = PCharRepPhrase(RandPhraseSimple("Your ears deceive you. I have to go.", "No, it's nothing, I was on my way to the tavern."),
            RandPhraseSimple("Well, it's nothing. Good luck!", "Just walking around the town. Goodbye."));
			link.l5.go = "exit";
		break;
		
		case "RumourAboutOwners":
			Dialog.Text = "Who are you interested in?";
			if(GetCharacterIndex(NPChar.city + "_Mayor") != -1)
			{
				link.l1 = "Want to know more about the governor.";
				link.l1.go = "RumourAboutOwners_Mayor";
			}
			if(GetCharacterIndex(NPChar.city + "_TavernKeeper") != -1)
			{
				link.l2 = "Want to know more about the local tavern's owner.";
				link.l2.go = "RumourAboutOwners_TavernKeeper";
			}
			if(GetCharacterIndex(NPChar.city + "_ShipYarder") != -1)
			{
				link.l3 = "Want to know more about the local shipyard's master.";
				link.l3.go = "RumourAboutOwners_ShipYarder";
			}
			if(GetCharacterIndex(NPChar.city + "_Trader") != -1)
			{
				link.l4 = "Want to know more about the local shop's owner.";
				link.l4.go = "RumourAboutOwners_Trader";
			}
			link.l9 = "It's nothing. Forget about it.";
			link.l9.go = "exit";
			break;
			
		case "RumourAboutOwners_TakeRumour":
			sTemp = sRumourAboutOwners_CityRumour(NPChar.City, NPChar.RumourOwnerType);
			Dialog.Text = sTemp;
			link.l1 = "Thanks.";
			link.l1.go = "exit";
			// Здесь можно делать проверка по квестам, какой слух выпал
			DeleteAttribute(PChar, "QuestTemp.RumoursAboutOwners");
		break;
		
		//Jason --> генератор Неудачливый вор
		case "Device_Citizen":
           dialog.text = "Hm, "+pchar.GenQuest.Device.Shipyarder.Type+"? Never heard about it... I've been living for a long time here and have never seen anything like that.";
			link.l1 = "Well, that is a shipbuilding tool, "+pchar.GenQuest.Device.Shipyarder.Describe+". Have anyone been selling anything like that in the town? Or perhaps carrying it around and you've noticed?";
			link.l1.go = "Device_Citizen_1";
			npchar.quest.Device = "true";
		break;
		
		case "Device_Citizen_1":
			if (sti(pchar.GenQuest.Device.Shipyarder.Chance1) > 3 && sti(pchar.GenQuest.Device.Shipyarder.Chance1) < 6 && npchar.sex != "woman")
			{
				dialog.text = "Hm... Yes, I saw a man with that thing several hours ago. He was walking along the streets. An interesting tool it was.";
				link.l1 = "How did he look like and where was he heading to? I really need that tool.";
				link.l1.go = "Device_Common";
			}
			else
			{
				dialog.text = "No, I haven't seen anything like that.";
				link.l1 = "I see. I'll keep asking then.";
				link.l1.go = "exit";
			}
		break;
		
		//=================== ноды квеста священника. поиск грабителей (квест №2)==================
		case "Citiz_GenQuest_Church_2_1":
			if(rand(3) != 1)
			{
				dialog.text = LinkRandPhrase("No, I don't know anything about that.", "No, I should go.", "I don't know a thing.");
					link.l1 = LinkRandPhrase("Fine, thanks.", "I see, thanks.", "Alright, excuse me.");
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = LinkRandPhrase("I don't know anything about that, but you may try to ask frequenters in the tavern, the will definitely tell you more.", "I can't tell you anything, ask somebody in the tavern.");
				link.l1 = "Thanks for that.";
				link.l1.go = "exit";
			}
			
			NPChar.GenQuest.ChurchQuest_2.AskedPeople = true;
		break;		
		
		//-------------------------------горожанин-пассажир----------------------------------------------
		case "passenger":
			if (crand(19) > 9) SetPassengerParameter("Townpassenger", false);
			else SetPassengerParameter("Townpassenger", true);
			dialog.text = "Captain, I need to get to the colony named " + XI_ConvertString("Colony"+pchar.GenQuest.Townpassenger.City)+", as soon as possible, it is on "+XI_ConvertString(GetIslandByCityName(pchar.GenQuest.Townpassenger.City)+"Dat")+", in "+FindRussianDaysString(sti(pchar.GenQuest.Townpassenger.DaysQty))+". Your ship looks solid comparing with the majority of those small boats sailing here. I can pay you "+FindRussianMoneyString(sti(pchar.GenQuest.Townpassenger.Money))+". What do you say?";
			link.l1 = "Hm. I am heading this way as well, so I am ready to take you aboard on these terms.";
			link.l1.go = "passenger_1";
			link.l2 = "I am sorry,  "+GetAddress_FormToNPC(NPChar)+", but I am sailing in the different direction. I can't help you.";
			link.l2.go = "passenger_exit";
		break;
		
		case "passenger_exit":
			dialog.text = "Too bad. Well, I'll wait for another ship. Farewell.";
			link.l1 = "See you.";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "GenQuest.Townpassenger");
		break;
		
		case "passenger_1":
			dialog.text = "Great, because I am tired of waiting. You will get your payment when we will be there.";
			link.l1 = "Go to my ship, "+GetAddress_FormToNPC(NPChar)+". We are leaving soon.";
			link.l1.go = "passenger_2";
		break;
		
		case "passenger_2":
			DialogExit();
			pchar.GenQuest.Townpassenger.id = npchar.id;
			LAi_SetImmortal(npchar, true);
			DeleteAttribute(npchar, "LifeDay");
			LAi_RemoveLoginTime(npchar);
			DeleteAttribute(npchar, "CityType");//удалить признак фантома, иначе - пустые города
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "", 20.0);
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, false);
			sTitle = npchar.index+"Citizpassenger";

// LDH 13Sep17 - do not add to an existing Citizpassenger record -->
// "Rename" the quest record by copying it to a new name and deleting the old record
			if (CheckAttribute(pchar, "questinfo."+sTitle))
			{
				string sTempLDH = frand(1);
				sTempLDH = strcut(sTempLDH, 2, 5);    // 4 random digits
				string sTitle1 = sTitle+sTempLDH;

				aref arTo, arFrom;
				makearef(arFrom, pchar.questinfo.(sTitle));
				makearef(arTo,   pchar.questinfo.(sTitle1));
				CopyAttributes(arTo, arFrom);
				pchar.questinfo.(sTitle1) = "";

				DeleteAttribute(pchar, "questinfo."+sTitle);

				Trace("Duplicate Citizpassenger record "+sTitle+" copied to "+sTitle1+" **");
			}
// <--

			AddQuestRecordEx(sTitle, "Citizpassenger", "1");
			AddQuestUserDataForTitle(sTitle, "sType", "citizen");
			AddQuestUserDataForTitle(sTitle, "sName", GetFullName(npchar));
			sTemp = XI_ConvertString("Colony" +pchar.GenQuest.Townpassenger.City+"Gen") + ", which is on " + XI_ConvertString(GetIslandByCityName(pchar.GenQuest.Townpassenger.City)+"Dat")+".";
			AddQuestUserDataForTitle(sTitle, "sCity", sTemp);
			AddQuestUserData(sTitle, "sName", GetFullName(npchar));
			AddQuestUserData(sTitle, "sCity", sTemp);
			AddQuestUserData(sTitle, "sDays", FindRussianDaysString(sti(pchar.GenQuest.Townpassenger.DaysQty)));
            AddQuestUserData(sTitle, "sMoney", FindRussianMoneyString(sti(pchar.GenQuest.Townpassenger.Money)));
			pchar.quest.Townpassenger.win_condition.l1 = "location";
			pchar.quest.Townpassenger.win_condition.l1.location = pchar.GenQuest.Townpassenger.City+"_town";
			pchar.quest.Townpassenger.function = "Townpassenger_complete";
			SetFunctionTimerCondition("Townpassenger_Over", 0, 0, sti(pchar.GenQuest.Townpassenger.DaysQty), false);
		break;
		
		case "passenger_3":
			pchar.quest.Townpassenger_Over.over = "yes"; //снять таймер
			dialog.text = "Here we are, most excellent! This travel on your ship was quite satisfying. My thanks. Take your money, sir.";
			link.l1 = "Good luck, "+GetAddress_FormToNPC(NPChar)+"! Farewell.";
			link.l1.go = "passenger_4";
		break;
		
		case "passenger_4":
			chrDisableReloadToLocation = false;//открыть локацию
			DialogExit();
			npchar.lifeday = 0;
			RemovePassenger(Pchar, npchar);
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload4_back", "none", "", "", "", 20.0);
			AddMoneyToCharacter(pchar, sti(pchar.GenQuest.Townpassenger.Money));
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
			ChangeCharacterComplexReputation(pchar, "fame", 1);
			OfficersReaction("good");				
			AddCharacterExpToSkill(pchar, "Sailing", 80);
			AddCharacterExpToSkill(pchar, "Leadership", 20);
			if (CheckAttribute(pchar, "GenQuest.Townpassenger.Enemycity")) AddCharacterExpToSkill(pchar, "Sneak", 50);
			sTitle = npchar.index+"Citizpassenger";
			AddQuestRecordEx(sTitle, "Citizpassenger", "3");
			CloseQuestHeader(sTitle);
			DeleteAttribute(Pchar, "GenQuest.Townpassenger");
		break;
//<-- горожанин-пассажир
		
		//замечение по обнаженному оружию
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = NPCharSexPhrase(NPChar, "Listen, as a citizen of this town I'm asking you to sheathe your blade.", "Listen, as a citizen of this town I'm asking you to sheathe your blade.");
				link.l1 = LinkRandPhrase("Fine.", "As you wish.", "As you say...");
			}
			else
			{
				dialog.text = NPCharSexPhrase(NPChar, "Be careful while running with a weapon. I can get nervous...", "I don't like when some unknown man is walking in front of me with unsheathed weapon. It scares me...");
				link.l1 = RandPhraseSimple("I got it.", "Don't worry.");
			}
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;

		case "pirate_fight":
			DialogExit();
			SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
			LAi_group_Attack(NPChar, Pchar);
			DoQuestFunctionDelay("TownPirate_battle", 0.5);
		break;

	}
}