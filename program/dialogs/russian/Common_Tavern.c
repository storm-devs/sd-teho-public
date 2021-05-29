#include "DIALOGS\russian\Rumours\Common_rumours.c"  //homo 25/06/06
#include "interface\ship.c"
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
    // вызов диалога по городам -->
    NPChar.FileDialog2 = "DIALOGS\" + LanguageGetLanguage() + "\Tavern\" + NPChar.City + "_Tavern.c";
    if (LoadSegment(NPChar.FileDialog2))
	{
        ProcessCommonDialog(NPChar, Link, NextDiag);
		UnloadSegment(NPChar.FileDialog2);
	}
    // вызов диалога по городам <--
	ProcessCommonDialogRumors(NPChar, Link, NextDiag);//homo 25/06/06
	
	int iTest, iTemp;
	string sTemp;
	string NPCCity = NPChar.City;
    iTest = FindColony(NPChar.City); // город 
    ref rColony;
	if (iTest != -1)
	{
		rColony = GetColonyByIndex(iTest);
	}
	bool ok;
	
	if(!CheckAttribute(pchar, "questTemp.TavernVisit."+(NPCCity) )) 
	{
		pchar.questTemp.TavernVisit.(NPCCity) = true;
		pchar.questTemp.TavernVisit.counter = sti(pchar.questTemp.TavernVisit.counter) + 1;
	}	
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			NextDiag.TempNode = "First time";
			if (LAi_grp_playeralarm > 0)
			{
       			dialog.text = NPCharRepPhrase(pchar,
					LinkRandPhrase("Alarm is raised in the town, and everyone is looking for you. If I were you, I wouldn't stay there.", "All the city guards are scouring the town looking for you. I am not a fool and I will not talk to you!", "Run, "+ GetSexPhrase("buddy","lass") +", before the soldiers turned you into a sieve..."),
					LinkRandPhrase("What do you need, "+ GetSexPhrase("scoundrel","stinker") +"?! The city guards have already hit your scent, you won't get far"+ GetSexPhrase(", filthy pirate!","") +"", "Murderer, leave my place at once! Guards!", "I am not afraid of you, "+ GetSexPhrase("scoundrel","rat") +"! Soon you will be hanged in our fort, you won't get far..."));
				link.l1 = NPCharRepPhrase(pchar,
					RandPhraseSimple("Heh, an alarm is never a problem for me...", "They will never get me."),
					RandPhraseSimple("Shut your mouth, " + GetWorkTypeOfMan(npchar, "") + ", or I'll rip your tongue!", "Heh, " + GetWorkTypeOfMan(npchar, "") + ", and all there - to catch pirates! That's what I tell you, buddy: sit quietly and you will not die..."));
				link.l1.go = "exit";
				break;
			}
			if (sti(pchar.GenQuest.Piratekill) > 20 && sti(npchar.nation) == PIRATE)
			{
				dialog.text = RandPhraseSimple("And it's you, bastard! You think you be poured rum here? Certainly not! Guys! To arms! Cut the psycho!", "Want a drink, you beast? But no! Now show you what's what! Guys, here sick crazy with weapons! Alert!");
				link.l1 = RandPhraseSimple("Huh? What?", "Uh, you of that!");
				link.l1.go = "fight";
				bDisableFastReload = true;//закрыть переход
				pchar.quest.pirate_in_town.win_condition.l1 = "ExitFromLocation";
				pchar.quest.pirate_in_town.win_condition.l1.location = pchar.location;
				pchar.quest.pirate_in_town.function = "TownPirate_battle";
				break;
			}
			//Jason, Бремя гасконца
			if (CheckAttribute(pchar, "questTemp.Sharlie") && pchar.questTemp.Sharlie == "crew" && npchar.city == "FortFrance")
			{
				dialog.text = "Did you want anything, monsieur?";
				Link.l1 = "Listen, I need to hire a crew for my ship. Can you help me with that?";
				Link.l1.go = "Sharlie_crew";
				break;
			}
			
			if (CheckAttribute(pchar, "questTemp.Sharlie") && pchar.questTemp.Sharlie == "skiper" && npchar.city == "FortFrance")
			{
				dialog.text = "What is it this time, monsieur?";
				Link.l1 = ""+npchar.name+", I realize that I am bothering you with my inquiries, but just one more question. I need a navigator - any idea where I can find one?";
				Link.l1.go = "Sharlie_skiper";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.Sharlie.Lock"))
			{
    			dialog.text = "What is it that you want, monsieur?";
				Link.l1 = "I hoped you could answer a couple of questions.";
				Link.l1.go = "quests";
				link.l2 = "I would like to rent a room.";
                link.l2.go = "room";
				break;
			}			
			//Бремя гасконца
			// Addon 2016-1 Jason пиратская линейка
			if (CheckAttribute(pchar, "questTemp.Mtraxx.Retribution") && pchar.questTemp.Mtraxx.Retribution == "tavern" && npchar.city == "Tortuga")
			{
				dialog.text = "I am delighted to see a dear guest! What would you like? Rum, brandy, Scottish whiskey?";
				Link.l1 = "I'd like a bottle of excellent French wine and room's key.";
				Link.l1.go = "mtraxx_tortuga";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.Mtraxx.Retribution") && pchar.questTemp.Mtraxx.Retribution == "room" && npchar.city == "Tortuga")
			{
				dialog.text = "You have already paid for everything, monseniour, your room is upstairs.";
				Link.l1 = "...";
				Link.l1.go = "exit";
				break;
			}
			
			if(NPChar.quest.meeting == "0")
			{
				dialog.Text = GetNatPhrase(npchar, LinkRandPhrase("Welcome to tavern '" + XI_ConvertString(NPChar.City + "TavernName") + "', sir. I'm glad to see you.","At your service, sir! In the tavern '" + XI_ConvertString(NPChar.City + "TavernName") + "' we are glad to welcome new visitors.","See you for the first time for me, sir? Do not hesitate, in the tavern '" + XI_ConvertString(NPChar.City + "TavernName") + "' you always feel at home!"), LinkRandPhrase("Come in, monsieur captain. This is your first time in tavern '" + XI_ConvertString(NPChar.City + "TavernName") + "'?","Never met you before, monsieur. Let's get acquainted: I'm "+GetFullName(npchar)+", the innkeeper of '" + XI_ConvertString(NPChar.City + "TavernName") + "'.","I'm glad to welcome the new guest, Monsieur Captain! In the tavern '" + XI_ConvertString(NPChar.City + "TavernName") + "' first drink is always at my expense! I am the owner of this place, "+GetFullName(npchar)+", will welcome you."), LinkRandPhrase("Senor Captain! Welcome to the tavern '" + XI_ConvertString(NPChar.City + "TavernName") + "'!","Oh, what a shining hidalgo's visited the tavern '" + XI_ConvertString(NPChar.City + "TavernName") + "'! Is it your first time here, sir?","Greetings, caballero! I'm "+GetFullName(npchar)+", innkeeper of '" + XI_ConvertString(NPChar.City + "TavernName") + "', glad to welcome you here!"),LinkRandPhrase("Hello, mynheer captain. I am the owner of tavern '" + XI_ConvertString(NPChar.City + "TavernName") + "'. First with us?","Good afternoon, mynheer. Welcome to the tavern '" + XI_ConvertString(NPChar.City + "TavernName") + "'.","Very nice mynheer Captain! Tavern '" + XI_ConvertString(NPChar.City + "TavernName") + "' greets you! Rum, wine, ale?"));
				Link.l1 = LinkRandPhrase("A cozy place you've got here... Allow me to introduce myself - "+GetFullName(pchar)+", it's a pleasure to meet you.",""+GetFullName(pchar)+", it's a pleasure to meet you. So, what are you going to offer me?","My name is "+GetFullName(pchar)+" and I am new to this place. So, what would you offer to your guest?");
				Link.l1.go = "meeting";
				NPChar.quest.meeting = "1";
			}
			else
			{
				// Квестовый генератор священника. Квест №1. Warship -->
				if(CheckAttribute(PChar, "GenQuest.ChurchQuest_1.NeedToDialogWithBarmen") && PChar.location == PChar.GenQuest.ChurchQuest_1.CurPortManColony + "_tavern")
		        {
		            if(CheckAttribute(PChar, "GenQuest.ChurchQuest_1.NoMoneyToBarmen"))
		            {
		            	iTemp = sti(PChar.GenQuest.ChurchQuest_1.MoneyToBarmen);
		            	dialog.Text = "So, cap, have you brought me " + FindRussianMoneyString(iTemp) + ".";
		            	if(sti(PChar.Money) >= iTemp)
		            	{
							link.l1 = "Yes, I have. Here they are...";
							link.l1.go = "Tavern_ChurchGenQuest1_Node_4_1";
						}
						else
						{
							link.l1 = "No, I haven't yet...";
							link.l1.go = "exit";
						}
		            }
		            else
		            {
		            	dialog.Text = "What would you like, gracious "+ GetSexPhrase("sir","lady") +"?";
						link.l1 = "A bottle of rum for my buddy at that table over there.";
						link.l1.go = "Tavern_ChurchGenQuest1_Node_1";
					}
					break;
				}
				// <-- Квестовый генератор священника. Квест №1.
				dialog.Text = pcharrepphrase(LinkRandPhrase(LinkRandPhrase("Oh, what honorable guests! Hey, you - make room for a gallant captain! And be quick about it, before he rushes you, ha-ha!","Oh! If it isn't "+GetFullName(pchar)+"! Not that we ordered a debauche, but please come in, cone in...","Oh, "+GetAddress_Form(NPChar)+", I see you're in a bad mood? Allow me to treat to you? Trust me, it's the best wine around..."),LinkRandPhrase("Oh, it's captain "+GetFullName(pchar)+"! Hey, you! Where are you going, ragamuffins?! Please excuse me, cap - they must have thought of some urgent things to do...","Oh, "+GetAddress_Form(NPChar)+" "+GetFullName(pchar)+"! That night surely is not going to be boring...","Good afternoon, "+GetFullName(pchar)+", I am glad to see you... But please - no scandals tonight, alright?"),LinkRandPhrase("Hello, captain. Suit yourself, but keep in mind that even captain Sharp himself kept up appearances in my establishment.","O-ho-ho! Look who's there? It's "+GetFullName(pchar)+"! himself! And we already started to get bored in your absence...","O-ho-ho! It's "+GetFullName(pchar)+" himself! I hope you're not going to scare away my patrons again with the stories of your adventures?")),LinkRandPhrase(LinkRandPhrase(""+GetFullName(pchar)+"! This old salt is always happy to see you in his establishment!","Please, captain, suit yourself! I am very happy to greet me favourite guest. What's your poison?","Glad to see you again, "+GetFullName(pchar)+"! Will you take a seat in the hall? Or shall I fill you a cup at the bar counter?"),LinkRandPhrase("Good afternoon, captain. Allow me to offer you excellent mulled wine!","Hello, captain "+GetFullName(pchar)+"! I am glad that you have come to visit again. What would you like?","I am glad to have you, "+GetAddress_Form(NPChar)+" "+GetFullName(pchar)+"! I see that you liked my establishment? I am doing everything I can to please you."),LinkRandPhrase("Sir captain! Welcome, welcome! I have got magnificent d'Anjou fit for kings - and saved it specially for you!",""+GetFullName(pchar)+"! I am so glad that you've come to visit. Shall I drive away all those ragmuffins or you would allow them to stay? Trust me, I would gladly clear the entire tavern only to please my best guest!","Once again we have captain "+GetFullName(pchar)+"! Hey, flirts - get the very best tablecloth to the captain's table!")));
				Link.l1 = pcharrepphrase(RandPhraseSimple(RandPhraseSimple("Oh, I see I am remembered here... Hey, fill my cup, buddy, while I take a look around...","Calm down, buddy, today I am in a very benign mood. Let's start with rum, shall we?..."),RandPhraseSimple("Oh... I take it, you are not too happy to have me here? I hope I misheard you?","I believe your wine is better than your greeting? Otherwise I can get angry, you know...")),RandPhraseSimple(RandPhraseSimple("Always glad to visit you, buddy. So, what do you have to warm up an old salt, frozen in the wind?","Hey, buddy, your establishment gets better with each coming day! Coming to visit here is always a pleasure..."),RandPhraseSimple("You haven't forgotten an old wanderer? Hey, I am flattered, buddy.","So nice to see an old friend again... You still have rum to drink here, I hope?")));
				Link.l1.go = "step_node";
			}
			break;
				
			case "step_node":
				dialog.Text = LinkRandPhrase("I am listening to you, captain.","Tavern '" + XI_ConvertString(NPChar.City + "TavernName") + "' at your service, Captain!","I listen, Cap'n! What will be your inquiry today?");
				Link.l1 = "Are there guys on the island ready to set sail?";
				Link.l1.go = "crew hire";
				Link.l2 = "I hoped you could answer a couple of questions.";
				Link.l2.go = "int_quests";
				if (CheckAttribute(pchar, "GenQuest.LoanChest.TakeChest") && sti(pchar.GenQuest.LoanChest.TargetIdx) == sti(NPChar.index))
				{
					link.l21 = "I would like to talk about financial affairs.";
					link.l21.go = "LoanForAll";//(перессылка в кредитный генератор)
				}
				
				// Квестовый генератор священника. Квест №2. Warship -->
				if(CheckAttribute(PChar, "GenQuest.ChurchQuest_2.AskBarmen") && PChar.location == PChar.GenQuest.ChurchQuest_2.QuestTown + "_tavern")
		            	{
					link.l10 = LinkRandPhrase("Can you tell me anything about the recent robbery in the church?", "What do you know about the recent robbery in the church?", "Have you heard anything about the recent robbery in the church?");
					link.l10.go = "Tavern_GenQuest_Church_2_1";
				}
				// <-- Квестовый генератор священника. Квест №2.
				
				//Jason --> генератор Неудачливый вор
				if (CheckAttribute(pchar, "GenQuest.Device.Shipyarder") && NPChar.location == pchar.GenQuest.Device.Shipyarder.City + "_tavern" && pchar.GenQuest.Device.Shipyarder == "begin" && !CheckAttribute(npchar, "quest.Device"))
				{
					link.l16 = "People say that you know just about everything in this colony. I want to buy "+pchar.GenQuest.Device.Shipyarder.Type+", and I was told that it had being sold in your town. Well, someone was selling it on the streets. Can you tell me anything about it?";
					link.l16.go = "Device_Tavern";
				}
				// <-- генератор Неудачливый вор
			
				//Jason --> генератор Место под солнцем
				if (CheckAttribute(pchar, "GenQuest.Sunplace.Trader") && pchar.GenQuest.Sunplace.Trader == "continue" && NPChar.location == pchar.GenQuest.Sunplace.Trader.CityT + "_tavern")
				{
					link.l17 = "Tell me about a profiteer by the name of "+pchar.GenQuest.Sunplace.Trader.Enemyname+". Where can I find him?";
					link.l17.go = "Sunplace_Tavern";
				}
				// <-- генератор Место под солнцем
			
				// --> Голландский гамбит
				if (CheckAttribute(pchar, "questTemp.HWIC.Holl") && pchar.questTemp.HWIC.Holl == "JacobOnMain" && NPChar.location == pchar.questTemp.HWIC.Holl.JacobCity + "_tavern")
				{
					link.l18 = "Hello, " + npchar.name + ". I need to find Jacob van Berg - where is he? I don't see him in your hall...";
					link.l18.go = "HWICHollJacob_Tavern";
				}
				if (CheckAttribute(pchar, "questTemp.HWIC.Self") && pchar.questTemp.HWIC.Self == "start" && NPChar.nation == SPAIN && !CheckAttribute(npchar, "quest.HWICTalked"))
				{
					link.l18 = "Hello, " + npchar.name + ". I am looking for a caballero by the name of Fernando Rodriguez. Did he show up in your town?";
					link.l18.go = "HWICSelfFernando_Tavern";
				}
				// <-- Голландский гамбит
			
				//Jason --> гонки на гидропланах
				if (CheckAttribute(pchar, "GenQuest.Racing.Go.Advantage") && NPChar.location == pchar.GenQuest.Racing.Go.StartCity + "_tavern")
				{
					link.l19 = "I came to collect my winnings, which are kept safe with you. " + npchar.name + ".";
					link.l19.go = "Race_Advantage";
				}
				// <-- гонки на гидропланах
			
				//Jason --> захват пассажиров
				if (CheckAttribute(pchar, "GenQuest.Marginpassenger") && pchar.GenQuest.Marginpassenger == "take" && NPChar.location == pchar.GenQuest.Marginpassenger.Targetcity+"_tavern")
				{
					link.l20 = "I was wondering where can a find a man by the name of "+pchar.GenQuest.Marginpassenger.q2Name+"? He lives in your town.";
					link.l20.go = "Marginpassenger";
				}
				// <-- захват пассажиров
			
				link.l3 = pcharrepphrase("Is there a free room in your bug-infested hovel?", "Have you got a free room, I would stay here for a while.");
				link.l3.go = "room";
				Link.l4 = "Alas, I am already leaving, " + NPChar.name + ". See you.";
				Link.l4.go = "exit";
		break;
		
		case "Meeting":
			// Квестовый генератор священника. Квест №1. Warship -->
			if(CheckAttribute(PChar, "GenQuest.ChurchQuest_1.NeedToDialogWithBarmen") && PChar.location == PChar.GenQuest.ChurchQuest_1.CurPortManColony + "_tavern")
	        {
	            dialog.Text = "What would you like, gracious "+ GetSexPhrase("sir","lady") +"?";
				link.l1 = "A bottle of rum for my buddy at that table over there.";
				link.l1.go = "Tavern_ChurchGenQuest1_Node_1";
				break;
			}
			// <-- Квестовый генератор священника. Квест №1.
			dialog.Text = LinkRandPhrase("I am listening to you, captain.","What can I offer you, captain?","So, cap, what are you going to order?");
			Link.l1 = "I need a crew, " + NPChar.name + ".";
			Link.l1.go = "crew hire";
			Link.l2 = NPChar.name + ", let's have a talk...";
			Link.l2.go = "int_quests";
			if (CheckAttribute(pchar, "GenQuest.LoanChest.TakeChest") && sti(pchar.GenQuest.LoanChest.TargetIdx) == sti(NPChar.index))
			{
				link.l21 = "I would like to talk about financial affairs.";
				link.l21.go = "LoanForAll";//(перессылка в кредитный генератор)
			}
			// Квестовый генератор священника. Квест №2. Warship -->
			if(CheckAttribute(PChar, "GenQuest.ChurchQuest_2.AskBarmen") && PChar.location == PChar.GenQuest.ChurchQuest_2.QuestTown + "_tavern")
	        {
				link.l10 = LinkRandPhrase("Can you tell me anything about the recent robbery in the church?", "What do you know about the recent robbery in the church?", "Have you heard anything about the recent robbery in the church?");
				link.l10.go = "Tavern_GenQuest_Church_2_1";
			}
			// <-- Квестовый генератор священника. Квест №2.
			
			//Jason --> генератор Неудачливый вор
			if (CheckAttribute(pchar, "GenQuest.Device.Shipyarder") && NPChar.location == pchar.GenQuest.Device.Shipyarder.City + "_tavern" && pchar.GenQuest.Device.Shipyarder == "begin" && !CheckAttribute(npchar, "quest.Device"))
			{
   				link.l16 = "People say that you know just about everything in this colony. I want to buy "+pchar.GenQuest.Device.Shipyarder.Type+", and I was told that it had being sold in your town. Well, someone was selling it on the streets. Can you tell me anything about it?";
				link.l16.go = "Device_Tavern";
			}
			// <-- генератор Неудачливый вор
			
			//Jason --> генератор Место под солнцем
			if (CheckAttribute(pchar, "GenQuest.Sunplace.Trader") && pchar.GenQuest.Sunplace.Trader == "continue" && NPChar.location == pchar.GenQuest.Sunplace.Trader.CityT + "_tavern")
			{
   				link.l17 = "Tell me about a profiteer by the name of "+pchar.GenQuest.Sunplace.Trader.Enemyname+". Where can I find him?";
				link.l17.go = "Sunplace_Tavern";
			}
			// <-- генератор Место под солнцем
			
			//--> Голландский гамбит
			if (CheckAttribute(pchar, "questTemp.HWIC.Holl") && pchar.questTemp.HWIC.Holl == "JacobOnMain" && NPChar.location == pchar.questTemp.HWIC.Holl.JacobCity + "_tavern")
				{
					link.l18 = "Hello, " + npchar.name + ". I need to find Jacob van Berg - where is he? I don't see him in your hall...";
					link.l18.go = "HWICHollJacob_Tavern";
				}
				if (CheckAttribute(pchar, "questTemp.HWIC.Self") && pchar.questTemp.HWIC.Self == "start" && NPChar.nation == SPAIN && !CheckAttribute(npchar, "quest.HWICTalked"))
				{
					link.l18 = "Hello, " + npchar.name + ". I am looking for a caballero by the name of Fernando Rodriguez. Did he show up in your town?";
					link.l18.go = "HWICSelfFernando_Tavern";
				}
				//<-- Голландский гамбит
				
				//Jason --> гонки на гидропланах
				if (CheckAttribute(pchar, "GenQuest.Racing.Go.Advantage") && NPChar.location == pchar.GenQuest.Racing.Go.StartCity + "_tavern")
				{
					link.l19 = "I came to collect my winnings, which are kept safe with you. " + npchar.name + ".";
					link.l19.go = "Race_Advantage";
				}
				// <-- гонки на гидропланах
				//Jason --> захват пассажиров
				if (CheckAttribute(pchar, "GenQuest.Marginpassenger") && pchar.GenQuest.Marginpassenger == "take" && NPChar.location == pchar.GenQuest.Marginpassenger.Targetcity+"_tavern")
				{
					link.l20 = "I was wondering where can a find a man by the name of "+pchar.GenQuest.Marginpassenger.q2Name+"? He lives in your town.";
					link.l20.go = "Marginpassenger";
				}
				// <-- захват пассажиров
				
			link.l3 = pcharrepphrase("Is there a free room in your bug-infested hovel?", "Have you got a free room, I would stay here for a while.");
			link.l3.go = "room";
			Link.l4 = "I guess I'll come back to you later.";
			Link.l4.go = "exit";
		break;
		
		case "crew hire":
			ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
			ok = sti(Pchar.Ship.Type) != SHIP_NOTUSED && ok;
			
			if (!ok)
			{
				Dialog.text = "And what would you need sailors for? I don't see your ship in the port.";
				link.l1 = RandPhraseSimple("Exactly... I had moored in the wrong place.", "Forgot to enter the port...");
				link.l1.go = "exit";
				break;
			}
			
            if (makeint(environment.time) > 22.0 || makeint(environment.time) < 7.0)
			{
				Dialog.text = "Usually there are many people looking to become sailors, but it's too late now - they will start to show up in the morning. Perhaps, you'd like to rent a room and wait for them?";
				link.l1 = "Alright. Do you have vacant rooms?";
				link.l1.go = "room";
				link.l2 = "I am not interested in a room at the moment. See you.";
				link.l2.go = "exit";
			}
			else
			{
                if (GetNationRelation2MainCharacter(sti(NPChar.nation)) == RELATION_ENEMY && sti(NPChar.nation) != PIRATE)
                {
                    Dialog.text = "You think that someone would approach you, while you're in hostility with us? Be thankful that I am not calling the guards.";
					link.l1 = "Thanks.";
					link.l1.go = "exit";
                }
                else
                {
					if (CheckAttribute(NPChar, "CrewHired.PGGId") && GetNpcQuestPastDayParam(NPChar, "CrewHired") < 3 && GetCrewQuantity(rColony) == 0)
					{
						Dialog.text = "I am sorry, but right now there's no one there. They all have left with gallant captain " + GetFullName(CharacterFromID(NPChar.CrewHired.PGGId)) + ".";
						link.l1 = "That's a pity!";
						link.l1.go = "exit_crew";
					}
					else
					{						
						if(bPartitionSet)
						{		
							if(GetPartitionAmount("CrewPayment") > 0)
							{
								if(IsEquipCharacterByArtefact(pchar, "totem_07"))
								{
									DeleteAttribute(NPChar, "CrewHired"); //на всяк случай.
									NextDiag.CurrentNode =  NextDiag.TempNode;
									DialogExit();
									LaunchHireCrew();							
								}
								else
								{
									dialog.text = "Captain, people say that you're quite stingy. I have no one here who'd like to join your crew.";
									link.l1 = "I see...";
									link.l1.go = "exit";
								}
							}
							else
							{
								DeleteAttribute(NPChar, "CrewHired"); //на всяк случай.
								NextDiag.CurrentNode =  NextDiag.TempNode;
								DialogExit();
								LaunchHireCrew();	
							}
						}	
						else
						{
							DeleteAttribute(NPChar, "CrewHired"); //на всяк случай.
							NextDiag.CurrentNode =  NextDiag.TempNode;
							DialogExit();
							LaunchHireCrew();							
						}						
					}
				}
			}
		break;
		
		case "exit_crew" :
			DeleteAttribute(NPChar, "CrewHired"); //на всяк случай.
			NextDiag.CurrentNode =  NextDiag.TempNode;
			DialogExit();
			LaunchHireCrew();
		break;
	////////////////////////////////////////////////////////=============================================///////////////////////////////////////////////////////	
        case "int_quests":
			dialog.text = "I am all ears.";
			//link.l1 = "I am looking for a job. Can you help me?";
			//link.l1.go = "work";
			//homo 15/06/06 слухи
			link.l2 = LinkRandPhrase("Can you tell me the latest news?","What's going on in these lands?",
                                    "What's new on land down there?");
			link.l2.go = "rumours_tavern";
			//homo
			link.l3 = "I came on a different business.";
			link.l3.go = "quests";
			if(CheckAttribute(pchar,"GenQuest.EncGirl"))
			{
				if(pchar.GenQuest.EncGirl == "EncGirlFack_fighted")
				{
					link.l5 = "Do you know where can I find " + pchar.GenQuest.EncGirl.name +"?";
					link.l5.go = "EncGirl_1";
				}	
				if(pchar.GenQuest.EncGirl == "toParents" || pchar.GenQuest.EncGirl == "FindLover")
				{
					link.l6 = "Can you tell me where should I look for " + pchar.GenQuest.EncGirl.sLoverId + "?";
					link.l6.go = "EncGirl_3";
				}
				if(pchar.GenQuest.EncGirl == "toLoverFather" && pchar.GenQuest.EncGirl.LoverFather == "tavern_keeper" && pchar.GenQuest.EncGirl.LoverCity == npchar.city)
				{
					link.l7 = "Hello, I came by your son's invitation."; 
					link.l7.go = "EncGirl_4";
					pchar.quest.EncGirl_GetLoverFather.over = "yes";
				}
			}
			if(CheckAttribute(pchar,"GenQuest.CaptainComission") && NPChar.city == pchar.GenQuest.CaptainComission.City && CheckAttribute(pchar,"GenQuest.CaptainComission.Speak_Tavern"))
			{
				if(pchar.GenQuest.CaptainComission.variant == "A0")
				{												
					if(pchar.GenQuest.CaptainComission.Speak_Tavern == true)
					{
						link.l9 = "So, have you seen  " + pchar.GenQuest.CaptainComission.Name + "?";
						link.l9.go = "CaptainComission_3";
					}
					else
					{
						link.l9 = "Can you tell me where should I look for  " + pchar.GenQuest.CaptainComission.Name + "?";
						link.l9.go = "CaptainComission_1";
					}
				}	

				if(pchar.GenQuest.CaptainComission.variant == "A2" && pchar.GenQuest.CaptainComission == "Begin_1")
				{
					link.l9 = "Do you know where can I find the captain of a patrol " + GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name") + "Acc")) + " " + pchar.GenQuest.CaptainComission.Name + "?";
					link.l9.go = "CaptainComission_Tavern7";					
				}				
				if(pchar.GenQuest.CaptainComission.variant == "A3" && pchar.GenQuest.CaptainComission == "Begin_1")
				{
					if(pchar.GenQuest.CaptainComission.Speak_Tavern == true)
					{
						link.l9 = "So, have you seen " + GetName( NAMETYPE_ORIG, pchar.GenQuest.CaptainComission.CanoneerName, NAME_NOM) + "?";
						link.l9.go = "CaptainComission_3";
					}
					else
					{					
						link.l9 = "Do you know anything about the captain of a patrol " + GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name") + "Acc")) + " " + pchar.GenQuest.CaptainComission.Name + "?";
						link.l9.go = "CaptainComission_Tavern1";
						if(!CheckAttribute(pchar,"GenQuest.CaptainComission.GetRumour"))
						{
							pchar.GenQuest.CaptainComission.GetRumour = true;
							SaveCurrentQuestDateParam("GenQuest.CaptainComission.GetRumour");
						}	
					}	
				}					
			}
			if(CheckAttribute(pchar,"GenQuest.Hold_GenQuest") && NPChar.city == pchar.GenQuest.Hold_GenQuest.City && pchar.GenQuest.Hold_GenQuest.Speak_Tavern == false )
			{
				link.l10 = "Could you tell me where can I find a man called " + pchar.GenQuest.Hold_GenQuest.Name + "?";
				link.l10.go = "hold_genquest1";
			}
			if (CheckCharacterItem(pchar, "CaptainBook") && CheckAttribute(pchar, "questTemp.different.GiveShipLetters") && !CheckAttribute(pchar, "questTemp.different.GiveShipLetters.speakTavern") && (pchar.questTemp.different.GiveShipLetters.city == npchar.city))
			{
				link.l11 = "I have found by chance not far from here the ship documents....";
				link.l11.go = "ShipLetters_4";			
			}

			// Jason --> квест губера на поиск дезертира
			if(CheckAttribute(pchar, "GenQuest.FindFugitive") && pchar.GenQuest.FindFugitive != "Late" && sti(NPChar.nation) == PIRATE)
			{
				link.l12 = "Listen, I am looking for an old friend of mine, "+pchar.GenQuest.FindFugitive.Name+" is his name. A skipper told me that he was heading to your settlement. Have you met him, by a chance?";
				link.l12.go = "FindFugitiveTav";
			}
			//<-- поиск дезертира

			link.l15 = "Thank you, nothing.";
			link.l15.go = "exit";
		break;
		
		case "hold_genquest1":
			switch(sti(pchar.GenQuest.Hold_GenQuest.TavernVariant))
			{
				case 0:
					dialog.text = LinkRandPhrase("What did you say? " + pchar.GenQuest.Hold_GenQuest.Name + "? Hmm... Never heard of him.",
						"Are you certain that he hails from our village? I've never heard of such a person.",
						"There wasn't anyone like that in our village. Never heard of him in all my time.");
					link.l1 = "Are you certain?";
					link.l1.go = "hold_genquest2";					
				break;
				
				case 1: 
					switch (drand(3))
					{
						case 0:
							pchar.GenQuest.Hold_GenQuest.foundStr = "the church";						
							pchar.GenQuest.Hold_GenQuest.found = "church";
						break;
						case 1:
							if (npchar.city != "Panama")
							{
							pchar.GenQuest.Hold_GenQuest.foundStr = "the shipyard";						
							pchar.GenQuest.Hold_GenQuest.found = "shipyard";
							}
							else
							{
								pchar.GenQuest.Hold_GenQuest.foundStr = "the church";						
								pchar.GenQuest.Hold_GenQuest.found = "church";
							}
						break;
						case 2:
							pchar.GenQuest.Hold_GenQuest.foundStr = "the usurer";												
							pchar.GenQuest.Hold_GenQuest.found = "bank";
						break;
						case 3:
							pchar.GenQuest.Hold_GenQuest.foundStr = "the shop";						
							pchar.GenQuest.Hold_GenQuest.found = "store";
						break;
					} 
					dialog.text = "Visit " + pchar.GenQuest.Hold_GenQuest.foundStr + ", he can be found there quite often.";
					link.l1 = "Thank you, I'll do just that.";
					link.l1.go = "hold_genquest3";				
				break;
				
				case 2:
					dialog.text = LinkRandPhrase(
						RandPhraseSimple("What did you say? " + pchar.GenQuest.Hold_GenQuest.Name + "? Hmm... Never heard of him. Are you certain that he hails from our village? I've never heard of such a person.",
						"He-he... Well, now only the Lord Himself knows where to look for him - in hell or in heavens. He died over a year ago, but people are still sniffing out about him... No rest for the poor guy..."),
						RandPhraseSimple("You will not find him there - in the land of the living at least. He died not so long ago - yellow fever... God rest his soul... What a stout man he used to be! When he was young, he was a great adventurer! But when death comes after you, there is not much you can do...",
						"Oh, have you missed him? He left these places long ago. No one knows where he went to - maybe to the kids, maybe went to Europe. He just gathered his belongings and made off."),
						"Oh, are you looking for that " + pchar.GenQuest.Hold_GenQuest.Name + " who suddenly grew rich and bought himself a house in New Albion? You know, there were times when I sold him rum in credit - he still owes me. People are so ungrateful, you know.");
					link.l1 = "I see. Well, thanks anyway.";	
					link.l1.go = "hold_genquest4";
				break;
				
				case 3:
					dialog.text = "Well, where else to look for him, if not at the tavern? He's a frequent visitor there - drowns his old sins in wine, he-he. Come back a bit later - if he shows up, I'll tell him to wait for you.";	
					link.l1 = "Thank you, I'll do that.";
					link.l1.go = "hold_genquest5";
				break;
			}
			pchar.GenQuest.Hold_GenQuest.Speak_Tavern = true;
		break;
		
		case "hold_genquest2":
			dialog.text = "How can't I be sure if I know everyone here personally. It's not the first year I am running the tavern here. "+
				"I have seen them all in all possible conditions. Sometimes a wife would come to pick her husband up, at times they would leave by themselves, and on some occasions I had to chuck them out. 'Am I sure?!' Of course, I am!";
			link.l1 = "Well, thanks anyway...";	
			link.l1.go = "exit";
			pchar.GenQuest.Hold_GenQuest = "prisoner_escaped";
			AddQuestRecord("HoldQuest", "7");
			AddQuestUserData("HoldQuest", "sName", pchar.GenQuest.Hold_GenQuest.CapName);
			AddDialogExitQuestFunction("Hold_GenQuest_PrisonerEscaped");
		break;
		
		case "hold_genquest3":
			Hold_GenQuest_GenerateChar();		
			AddQuestRecord("HoldQuest", "8");
			AddQuestUserData("HoldQuest", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.Hold_GenQuest.City + "Gen")); 			
			AddQuestUserData("HoldQuest", "sFoundChar", pchar.GenQuest.Hold_GenQuest.foundStr);
			AddQuestUserData("HoldQuest", "sName", pchar.GenQuest.Hold_GenQuest.Name);
			SetFunctionTimerConditionParam("Hold_GenQuest_FindCharTimeIsOver", 0, 0, 1, MakeInt(24 - GetHour()), false);
			DialogExit();
		break;
		
		case "hold_genquest4":
			AddQuestRecord("HoldQuest", "13");
			AddQuestUserData("HoldQuest", "sName", pchar.GenQuest.Hold_GenQuest.CapName);
			AddQuestUserData("HoldQuest", "sNameChar", pchar.GenQuest.Hold_GenQuest.Name);
			AddQuestUserData("HoldQuest", "sSex", GetSexPhrase("",""));
			CloseQuestHeader("HoldQuest");
			DeleteAttribute(pchar,"GenQuest.Hold_GenQuest");			
			DialogExit();
		break;
		
		case "hold_genquest5":
			SetFunctionTimerConditionParam("Hold_GenQuest_GetMapTimeIsOver", 0, 0, 1, MakeInt(24 - GetHour()), false);
			DialogExit();
			AddDialogExitQuestFunction("Hold_GenQuest_GenerateMapChar");			
		break;
		
		case "CaptainComission_1":
			dialog.text = LinkRandPhrase("He is a frequent visitor here, but right now he's not there. Come back from time to time - I will tell him to wait here for you if he shows up.","He is a frequent visitor here. If you come back later, you're certain to find him there.","Come back from time to time - he is a frequent visitor here. I will let him know that you were looking for him.");
			link.l1 = "Thank you, I'll come back later...";
			link.l1.go = "CaptainComission_2";
			pchar.GenQuest.CaptainComission.Speak_Tavern = true;
		break;
		
		case "CaptainComission_2":
			pchar.quest.CapComission_ExitFromTavern.win_condition.l1 = "ExitFromLocation";
			pchar.quest.CapComission_ExitFromTavern.win_condition.l1.location = pchar.location;
			pchar.quest.CapComission_ExitFromTavern.function = "CaptainComission_GenerateChar";

			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "CaptainComission_3":
			dialog.text = "He's already come here, so should be somewhere around...";
			link.l1 = "Thanks.";
			link.l1.go = "exit";
			DeleteAttribute(pchar,"GenQuest.CaptainComission.Speak_Tavern");
		break;
		
		case "CaptainComission_Tavern1":
			pchar.GenQuest.CaptainComission.Speak_Tavern = true;
			dialog.text = "Is there a man who doesn't know him? The entire settlement is talking about him for several days already.";
			link.l1 = "Could you tell me more?";
			link.l1.go = "CaptainComission_Tavern2";
		break;
		
		case "CaptainComission_Tavern2":
			dialog.text = "In general, the captain was executed, same can be said about some of his crewmen. The rest were scattered across the archipelago absent their ranks and positions… For what? According to a judge, he had sunken a vessel during a patrol and hidden a cargo for himself\n"+
				"But to believe in it with difficulty, because neither the owner of this vessel or goods have not been found ... So far all the bays are combing.";
			link.l1 = "What, no one of the crew did reveal the location of the cache?";	
			link.l1.go = "CaptainComission_Tavern3";	
		break;
		
		case "CaptainComission_Tavern3":
			dialog.text = "Not a single one!.. I still can't understand, why would the governor believe in that slander so eagerly. Captain " + pchar.GenQuest.CaptainComission.Name + " had a decent reputation, and his crew was so well-trained and disciplined, that any admiral would envy him.";
			link.l1 = "And where should I look for the surviving crew members?";
			link.l1.go = "CaptainComission_Tavern4";
		break;
		
		case "CaptainComission_Tavern4":
			dialog.text = "That I don't know - they all have been taken away... Although... there's still one of them remaining, but I doubt you would learn much from him. He was contused. You know, he served as a gunner under " + pchar.GenQuest.CaptainComission.Name + ". He was found unconscious in some cove two days after that accident. First he was sent to the hospital and treated like a hero, but as the plot thickened, they threw him into the dungeon and tried to interrogate him, but then decided that first he should be medically treated, anyway.";
			link.l1 = "So he's in the settlement right now?";
			link.l1.go = "CaptainComission_Tavern5";
		break;
		
		case "CaptainComission_Tavern5":
			pchar.GenQuest.CaptainComission.CanoneerName = "l" + rand(GetNamesCount(NAMETYPE_ORIG) - 1);
			dialog.text = "Yes, " + GetName( NAMETYPE_ORIG, pchar.GenQuest.CaptainComission.CanoneerName, NAME_NOM) + " is his name. He drops in from time to time, begging for rum. If I see him, I'll tell him to wait here for you.";
			link.l1 = "Thank you, I'll come back later.";
			link.l1.go = "CaptainComission_Tavern6";
		break;
		
		case "CaptainComission_Tavern6":
			AddQuestRecord("CaptainComission2", "39");
			AddQuestUserData("CaptainComission2", "sShipType", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name") + "Acc"))); 
			AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);
			AddQuestUserData("CaptainComission2", "sCharName", GetName( NAMETYPE_ORIG, pchar.GenQuest.CaptainComission.CanoneerName, NAME_ABL));
			AddQuestUserData("CaptainComission2", "sShipName", pchar.GenQuest.CaptainComission.ShipTypeName);			
			SetFunctionExitFromLocationCondition("CaptainComission_GenerateCanoneer", pchar.location, false);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "CaptainComission_Tavern7":
			DeleteAttribute(pchar,"GenQuest.CaptainComission.Speak_Tavern");
			dialog.text = "Do I know him? Of course, I do. And what do you need him for?";
			link.l1 = "I have business with him...";
			link.l1.go = "CaptainComission_Tavern8";
		break;
		
		case "CaptainComission_Tavern8":
			dialog.text = "You, " + GetAddress_Form(pchar) + ", should be cautious with that 'business'. " + pchar.GenQuest.CaptainComission.Name + " is detained on suspicion of a service crime, and the governor's sleuths are now scouring the island, searching for his accomplices.";
			link.l1 = "You don't say so! And what did he do?";
			link.l1.go = "CaptainComission_Tavern9";
		break;
		
		case "CaptainComission_Tavern9":
			dialog.text = "I don't know whether it's true or not, but they say that he had stashed away the cargo confiscated from a passing pirate ship. And still no one found neither that pirate, nor the cargo. I still can't understand, why would the governor believe in that slander so eagerly. Captain " + pchar.GenQuest.CaptainComission.CapName + "  had a decent reputation, and he was a great soldier, you can trust my word, " + GetAddress_Form(pchar) + ".";
			link.l1 = "Well, thanks for the warning. See you.";
			link.l1.go = "CaptainComission_Tavern10";
		break;
		
		case "CaptainComission_Tavern10":
			if(!CheckAttribute(pchar,"GenQuest.CaptainComission.GetRumour"))
			{
				pchar.GenQuest.CaptainComission.GetRumour = true;
				SaveCurrentQuestDateParam("GenQuest.CaptainComission.GetRumour");
				SetFunctionTimerConditionParam("CaptainComission_TimeIsOver", 0, 0, 2, MakeInt(24 - GetHour()), false);
				AddQuestRecord("CaptainComission2", "19");
				AddQuestUserData("CaptainComission2", "sShipType", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name") + "Acc"))); 
				AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);
			}			
			DialogExit();
		break;
				
		case "EncGirl_1":
			dialog.text = "And what do you need her for?";
			link.l1 = "I have business with her...";
			link.l1.go = "EncGirl_2";
		break;
		
		case "EncGirl_2":
			dialog.text = "Half the men in our settlement seem to have business with her. If our women had caught her, they would toss her beyond the town gates, naked.";
			link.l1 = "Oh well... "+ GetSexPhrase("It seems that I got into a long line, then. Well, if anyone else comes around asking for her, tell them to stand in line behind me.","I see") +"...";
			link.l1.go = "exit";
			pchar.quest.EncGirl_SpeakTavernKeeper.over = "yes";
			DeleteAttribute(pchar, "GenQuest.EncGirl");
		break;
		
		case "EncGirl_3":
			dialog.text = "He is a frequent visitor here - he usually comes over in search for a job, but right now he's not there. Come back from time to time - I will tell him to wait here for you if he shows up.";
			link.l1 = "Thank you, I'll come back later...";
			link.l1.go = "exit";
			pchar.GenQuest.EncGirl = "FindingLover";
			pchar.quest.EncGirl_ExitTavern.win_condition.l1 = "ExitFromLocation";
			pchar.quest.EncGirl_ExitTavern.win_condition.l1.location = pchar.location;
			pchar.quest.EncGirl_ExitTavern.function = "EncGirl_GenerateLover";
		break;
		
		case "EncGirl_4":
			if(sti(pchar.GenQuest.EncGirl.LoverFatherAngry) == 0)
			{
				dialog.text = "Oh, so you are "+ GetSexPhrase("that captain, who brought","that lass, who brought") +" my prodigal son with a young bride?";
				link.l1 = "Yes, it was me who had helped.";
				link.l1.go = "EncGirl_5";
			}
			else
			{
				dialog.text = "Oh, there "+ GetSexPhrase("he is, our benefactor","she is, our benefactress") +". Expecting a reward, I take it?";
				link.l1 = "Well, I'm fine without a reward, but just your thanks would do well.";
				link.l1.go = "EncGirl_6";			
			}
		break;
		
		case "EncGirl_5":
			dialog.text = "I am very grateful to you that you haven't abandoned my child in dire straits and helped him to find a way out of a delicate situation. Allow me to thank you and please accept this modest sum and a gift from me personally.";
			link.l1 = "Thanks. Helping out this young couple was my pleasure.";
			link.l1.go = "EncGirl_5_1";
		break;
		
		case "EncGirl_6":
			dialog.text = "Thanks? What thanks?! It's been a half a year since that blockhead was hanging around without a job - and look at him, he's got enough time for love affairs! When I was his age, I was already running my own business! Pfft! A governor has a marriageable daughter - and that dunce has brought a slut without kith or kin to my house and dared to ask for my blessing!";
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
			dialog.text = "What feelings? What kind of feelings are you talking about? Feelings... how can one be so light-minded at your age?! Shame on you to indulge the young in their caprices and act as a procurer! Not only have you taken a girl from her home, but you also ruined my greenhorn's life. There will be no thanks to you. Farewell.";
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
				
		case "ShipLetters_4":
			pchar.questTemp.different.GiveShipLetters.speakTavern = true;
			if(sti(pchar.questTemp.different.GiveShipLetters.variant) == 0)
			{
				dialog.text = "Let me take a look! Hmm... But you're a captain yourself. I think you should see the harbour master about this.";
				link.l1 = "Thank you for your advice.";
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = "Let me take a look! Oh! Judging by the name, this belongs to one of my patrons, quite a respected person. I myself can hand these documents over to the owner. Will you give them to me?";
				link.l1	= "Probably, not...";
				link.l1.go = "exit";
				link.l2 = "Take them. I'm happy I was able be useful to him.";
				link.l2.go = "ShipLetters_end";				
			}	
		break;
		
		case "ShipLetters_end":
			TakeItemFromCharacter(pchar, "CaptainBook"); 
			pchar.questTemp.different = "free";
			pchar.quest.GiveShipLetters_null.over = "yes"; //снимаем таймер 
			AddQuestRecord("GiveShipLetters", "3");			
			CloseQuestHeader("GiveShipLetters");
			DeleteAttribute(pchar, "questTemp.different.GiveShipLetters"); 
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		//zagolski. переделка
		case "work":
			if (sti(NPChar.nation) != PIRATE && GetNationRelation2MainCharacter(sti(NPChar.nation)) == RELATION_ENEMY)
			{
				dialog.text = RandPhraseSimple("I don't care whom to serve since money has no nationality. But I will not be helping you since you came under the flag of " + NationNameGenitive(sti(pchar.nation)) + ".", "I am just a simple tavern owner, but collaboration with " + NationNameAblative(sti(pchar.nation)) + " doesn't seem appealing to me.");
				link.l1 = RandPhraseSimple("Well, as you wish...", "Well, as you like...");
				link.l1.go = "exit";
				break;
			}
			if (isBadReputation(pchar, 40))
			{
				dialog.text = RandPhraseSimple("We usually have a lot of passengers here. Still, I don't think that there would be even one duffy among them, who might agree to travel on your ship. Your ill repute precedes you, and the reputation of an honest captain is yet to be won.", "I am quite frequently approached by merchants who need escorting. But your ill repute precedes you, and I will not recommend you to anyone. I care for my own reputation, you know.");
				link.l1 = RandPhraseSimple("Oh, really, you shouldn't believe all these gossips...", "I see. It's difficult to make everyone shut up.", "People are just too faint-hearted these days...");
				link.l1.go = "exit";
				break;
			}
			if (sti(Pchar.Ship.Type) == SHIP_NOTUSED)
        	{
				dialog.text = "And where is your ship? Or are you going to carry the passengers around your neck?";
				link.l1 = "Hmm, you got a point...";
				link.l1.go = "exit";
				break;
			}
			dialog.text = "I might have a job if you're not afraid to come to pirate settlements or to the ports of enemy nations. Are you looking for something in particular?";
			link.l1 = "That shouldn't be a problem. I guess I could provide escort.";
			link.l1.go = "work_1";
			link.l2 = "Do you have any passengers? I can take them wherever they want, if they pay for it.";
			link.l2.go = "work_2";
			link.l3 = "No, such work is not for me. Thanks.";
			link.l3.go = "exit";
		break;

		case "work_1":
				dialog.text = "They usually do not ask me about escorting. Ask the merchants in the tavern - perhaps they would need your services.";
				link.l1 = "Fine, as you say.";
                link.l1.go = "exit";
		break;

		case "work_2":
			if (!CheckAttribute(npchar, "work_date") || GetNpcQuestPastDayParam(npchar, "work_date") >= 2 || bBettaTestMode)
    		{					
				if (GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) < 5)//при низком авторитете не даем
				{
					dialog.text = "I am sorry, but I don't have anyone willing to travel with you.";
					link.l1 = "I see. Well, as you say.";
					link.l1.go = "exit";
					break;
				}
		         // пассажир
				if (drand(6) > 1)
				{
					dialog.Text = "There's one guy, who just came in - he was recently asking about a passing vessel. You can talk to him, if you like.";
					link.l1 = RandPhraseSimple("Who is he? Maybe he is a crook? Or, even worse, a wanted criminal?", "And who is he? Will there be any trouble with him?");
					Link.l1.go = "PassangerAreYouSure";
				}
				else
				{
					dialog.text = "No, today no one ha asked about it. Perhaps, another day.";
					link.l1 = RandPhraseSimple("Well, if it's not there, it's not...", "Just my luck... Oh, well, see you, then.");
					link.l1.go = "exit";
				}
            }
    		else
    		{
				dialog.text = "There's no one for today. Come back in a couple of days.";
				link.l1 = "Fine, as you say.";
                link.l1.go = "exit";
    		}
        break;

        case "ConvoyAreYouSure":
		    dialog.text = LinkRandPhrase("Who could know? You asked - I answered.", "Well, this to you most to solve. I would not vouch for anyone there.", "Solve itself, come to me all sorts. It's a tavern, and not the governor's residence.");
			Link.l1 = "Thanks, we'll bargain, then.";
			Link.l1.go = "exit";
			pchar.quest.destination = findTraderCity(npchar);
			pchar.ConvoyQuest.City = npchar.city;
			AddDialogExitQuest("prepare_for_convoy_quest");
			SaveCurrentNpcQuestDateParam(npchar, "work_date");
        break;

        case "PassangerAreYouSure":
		    dialog.text = LinkRandPhrase("Who could know? You asked - I answered.", "Well, this to you most to solve. I would not vouch for anyone there.", "Solve itself, come to me all sorts. It's a tavern, and not the governor's residence.");
			Link.l1 = "I see. Let's figure out, who is this guy.";
			Link.l1.go = "exit";
			sGlobalTemp = findPassangerCity(npchar);
			pchar.GenQuest.GetPassenger_City = npchar.city;
			AddDialogExitQuest("prepare_for_passenger_quest");
			SaveCurrentNpcQuestDateParam(npchar, "work_date");
        break;

		 case "fight":
			DialogExit();
            NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_group_Attack(NPChar, Pchar);
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "room":
   			if (chrDisableReloadToLocation || CheckAttribute(pchar, "questTemp.different.Church_NightGuard")) //кто-то должен подойти к ГГ.
			{
				dialog.text = "The room is occupied, " + GetAddress_Form(NPChar) + ", there's nothing I can do for you.";
				link.l1 = "Well, that's a pity...";
				link.l1.go = "exit";
				break;
			}
			// суп из черепахи
			if (CheckAttribute(pchar, "questTemp.Terrapin.Room_close") && npchar.location == "Tortuga_tavern")
			{
				dialog.text = "Monsieur Henri Thibaut is renting the room at the moment, and he paid for a month in advance, so there's nothing I can do for you, captain.";
				link.l1 = "Well, that's a pity...";
				link.l1.go = "exit";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.Terrapin") && pchar.questTemp.Terrapin == "cave" && npchar.location == "Tortuga_tavern")
			{
				dialog.text = "The room is occupied, " + GetAddress_Form(NPChar) + ", there's nothing I can do for you.";
				link.l1 = "Well, that's a pity...";
				link.l1.go = "exit";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "shore" && npchar.location == "Baster_tavern") // 070712
			{
				dialog.text = "The room is occupied, " + GetAddress_Form(NPChar) + ", there's nothing I can do for you.";
				link.l1 = "Well, that's a pity...";
				link.l1.go = "exit";
				break;
			}
			//-->> квест официантки
			if (pchar.questTemp.different == "FackWaitress_toRoom")
			{
				dialog.text = "You want to rent a room? No problem. 100 coins on the nail - and it's yours.";
				if (sti(pchar.money) >= 100)
				{
					link.l1 = "Here's your money. Show me to my room.";
					link.l1.go = "exit";
					AddMoneyToCharacter(pchar, -100);
					LocatorReloadEnterDisable(npchar.city + "_tavern", "reload2_back", false);
					pchar.questTemp.different = "FackWaitress_toRoomUp";
				}
				else
				{
					link.l1 = "Hmm... I guess I'll come back later...";
					link.l1.go = "exit";
				}
				break;
			}
			if (pchar.questTemp.different == "FackWaitress_toRoomUp")//квест официантки
			{
				dialog.text = "The room is all yours. Come in and relax.";
				link.l1 = "Thanks, buddy.";
				link.l1.go = "exit";
				break;
			}
			//<<-- квест официантки
			// --> квест "A damsel in the jungle"
			if(CheckAttribute(pchar,"GenQuest.EncGirl") && npchar.city == pchar.GenQuest.EncGirl.city)
			{
				if(pchar.GenQuest.EncGirl == "EncGirl_ToTavern")
				{
					dialog.text = "You want to rent a room? No problem. 100 coins on the nail - and it's yours.";
					if (sti(pchar.money) >= 100)
					{
						link.l1 = "Here's your money. Show me to my room.";
						link.l1.go = "exit";
						AddMoneyToCharacter(pchar, -100);
						LocatorReloadEnterDisable(npchar.city + "_tavern", "reload2_back", false);
						pchar.GenQuest.EncGirl = "EncGirl_toRoomUp";
					}
					else
					{
						link.l1 = "Hmm... I guess I'll come back later...";
						link.l1.go = "exit";
					}
					break;
				}
				if (pchar.GenQuest.EncGirl == "EncGirl_toRoomUp")//квест  по спасению тетки в пампасах
				{
					dialog.text = "The room is all yours. Come in and relax.";
					link.l1 = "Thanks, buddy.";
					link.l1.go = "exit";
					break;
				}
			}
			// <-- квест "A damsel in the jungle"
			dialog.text = "For how long are you planning to stay here?";
			if(!isDay())
			{
				link.l1 = "Till morning.";
				link.l1.go = "room_day";
			}
			else
			{
				link.l1 = "Till night.";
				link.l1.go = "room_night";
				link.l2 = "Till next morning.";
				link.l2.go = "room_day_next";
			}
		break;

		case "room_day":
			dialog.text = "That will cost you 5 pesos.";
			if (makeint(pchar.money) >= 5)
			{
				link.l1 = "Deal. Here you go.";
				link.l1.go = "room_day_wait";
			}
			link.l2 = pcharrepphrase("Are you renting royal chambers or what? No, I'd rather stay in a common room for free, then.",
            "Alas, the luxury of sleeping on a bed is beyond my purse, as it seems. Guess I'll have to sleep in a common room.");
			link.l2.go = "hall_day_wait";
			if (!CheckAttribute(pchar, "questTemp.Sharlie.Lock"))
			{
				link.l3 = "Not right now. Let's change the subject.";
				link.l3.go = "int_quests";
			}
		break;

		case "room_day_next":
			dialog.text = "That will cost you 10 pesos.";
			if (makeint(pchar.money) >= 10)
			{
				link.l1 = "Deal. Here you go.";
				link.l1.go = "room_day_wait_next";
			}
			link.l2 = pcharrepphrase("Are you renting royal chambers or what? No, I'd rather stay in a common room for free, then.",
            "Alas, the luxury of sleeping on a bed is beyond my purse, as it seems. Guess I'll have to sleep in a common room.");
			link.l2.go = "hall_day_wait";
			if (!CheckAttribute(pchar, "questTemp.Sharlie.Lock"))
			{
				link.l3 = "Not right now. Let's change the subject.";
				link.l3.go = "int_quests";
			}
		break;

		case "room_night":
			dialog.text = "That will cost you 5 pesos.";
			if (makeint(pchar.money) >= 5)
			{
				link.l1 = "Deal. Here you go.";
				link.l1.go = "room_night_wait";
			}
			link.l2 = pcharrepphrase("Are you renting royal chambers or what? No, I'd rather stay in a common room for free, then.",
            "Alas, the luxury of sleeping on a bed is beyond my purse, as it seems. Guess I'll have to sleep in a common room.");
			link.l2.go = "hall_night_wait";
			if (!CheckAttribute(pchar, "questTemp.Sharlie.Lock"))
			{
				link.l3 = "Not right now. Let's change the subject.";
				link.l3.go = "int_quests";
			}
		break;

		case "room_night_wait":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			AddMoneyToCharacter(pchar, -5);
			AddDialogExitQuest("sleep_in_tavern");
			TavernWaitDate("wait_night");
		break;

		case "hall_night_wait":
			if (cRand(3) == 1)
            {
                Dialog.text = "Get lost, ragamuffin! The common room is free - but there still are limits.";
				link.l1 = "Alright, alright, I am leaving.";
				link.l1.go = "exit";
            }
            else
            {
				DialogExit();
				NextDiag.CurrentNode = NextDiag.TempNode;
				TavernWaitDate("wait_night");
			}
		break;

		case "room_day_wait":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			AddMoneyToCharacter(pchar, -5);
			AddDialogExitQuest("sleep_in_tavern");
			if (CheckAttribute(pchar, "GenQuest.LigaAttack") && drand(1) == 1)
			{
				TavernWaitDate("wait_night");
				pchar.GenQuest.LigaAttack.Go = "true"; //атака киллеров
			}
			else TavernWaitDate("wait_day");
		break;

		case "room_day_wait_next":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			AddMoneyToCharacter(pchar, -10);
			AddDialogExitQuest("sleep_in_tavern");
			if (CheckAttribute(pchar, "GenQuest.LigaAttack") && drand(1) == 1)
			{
				TavernWaitDate("wait_night");
				pchar.GenQuest.LigaAttack.Go = "true"; //атака киллеров
			}
			else TavernWaitDate("wait_day");
		break;

		case "hall_day_wait":
			if (drand(1) == 1)
            {
                Dialog.text = "Get lost, ragamuffin! The common room is free - but there still are limits.";
				link.l1 = "Alright, alright, I am leaving.";
				link.l1.go = "exit";
            }
            else
            {
				DialogExit();
				NextDiag.CurrentNode = NextDiag.TempNode;
				TavernWaitDate("wait_day");
			}
		break;
		
		case "tavern_keeper":
			NextDiag.TempNode = "First time";

			dialog.text = "Stop this outrage in my tavern this instant - or I am calling the guards!";
			link.l1 = "Alright, alright, I am leaving.";
			link.l1.go = "exit_sit";
		break;

		case "exit_sit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			AddDialogExitQuest("exit_sit");
		break;
		
		//******************* ноды квеста священника. поиск грабителей (квест № 2)**********************
		case "Tavern_GenQuest_Church_2_1":
			dialog.text = "I don't know much about it... You'd better ask the patrons.";
			link.l1 = "I see, thanks.";
			link.l1.go = "exit";
			DeleteAttribute(PChar, "GenQuest.ChurchQuest_2.AskBarmen");
		break;
			
		//******************* ноды квеста священника. вернуть рукописи (квест № 1)**********************
		case "Tavern_ChurchGenQuest1_Node_1":
			dialog.text = "We don't provide services in debt, "+ GetSexPhrase("mister","miss") +".";
			link.l1 = "I used to pay with a ringing coin. Or is here no longer accept gold or silver?";
			link.l1.go = "Tavern_ChurchGenQuest1_Node_2";
		break;
			
		case "Tavern_ChurchGenQuest1_Node_2":
			dialog.text = "I am sorry, "+ GetSexPhrase("mister","miss") +" captain, but your friend had a debt, and I thought...";
			link.l1 = "Think less and work faster, buddy. Now, how much does my valiant friend owe you?";
			link.l1.go = "Tavern_ChurchGenQuest1_Node_3";
		break;
			
		case "Tavern_ChurchGenQuest1_Node_3":
			iTemp = (rand(3)+1)*100;
			PChar.GenQuest.ChurchQuest_1.MoneyToBarmen = iTemp;
			if(rand(1) == 0) // "If he's a simple one and pays right away"
			{
				dialog.text = FindRussianMoneyString(iTemp) + ", mis"+ GetSexPhrase("ter","s") +" captain, and he also pawned some church books - that's all he had on him, which had some value.";
				if(sti(PChar.money) >= iTemp)
				{
					link.l1 = "Here are your coins. Hand over the manuscripts. And careful with them - it's not an ale keg, but scriptures of righteous men!";
					link.l1.go = "Tavern_ChurchGenQuest1_Node_4_1";
				}
				else
				{
					link.l1 = "Wait a bit... I'll be back with the money";
					link.l1.go = "exit";
					PChar.GenQuest.ChurchQuest_1.NoMoneyToBarmen = true;
				}
			}
			else // "If he's not a simple one"
			{
				dialog.text = FindRussianMoneyString(iTemp) + ", mis"+ GetSexPhrase("ter","s") +" captain.";
				link.l1 = "I will pay back his debt and take whatever he left to secure it.";
				link.l1.go = "Tavern_ChurchGenQuest1_Node_4_2";
			}
		break;
			
		case "Tavern_ChurchGenQuest1_Node_4_1":
			DialogExit();
			AddMoneyToCharacter(PChar, -sti(PChar.GenQuest.ChurchQuest_1.MoneyToBarmen));
			AddItems(PChar, "Bible", 1);	// Даем рукописи
			items[FindItem("Bible")].Name = "itmname_ChurchGenQuest1Bible";	// Меняем имя. Потом поменять обратно!
			ChangeItemDescribe("Bible", "itmdescr_ChurchGenQuest1Bible"); // Меняем дескрайб. Потом поменять обратно!
			items[FindItem("Bible")].City = XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.QuestTown + "Gen"); // Переменная. Потом удалить!
			DeleteAttribute(PChar, "GenQuest.ChurchQuest_1.NeedToDialogWithBarmen");
			sQuestTitle = PChar.GenQuest.ChurchQuest_1.QuestTown + "ChurchGenQuest1";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest1", "8");
			AddQuestUserData(sQuestTitle, "sColony", XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.QuestTown + "Gen"));
			AddQuestUserData(sQuestTitle, "sName", GetFullName(CharacterFromID("ChurchGenQuest1_Cap")));
			PChar.GenQuest.ChurchQuest_1.Complete = true; // Квест выполнен
			SetFunctionTimerCondition("Church_GenQuest1_DeleteCapitan", 0, 0, 2, false);
		break;
			
		case "Tavern_ChurchGenQuest1_Node_4_2":
			dialog.text = "No, mis"+ GetSexPhrase("ter","s") +", that won't work like that.";
			link.l1 = "What do you mean - 'that won't work like that'? A captain's debt is paid - he's fine. You have your money back - you're fine. I take his pledge - I am fine. Everyone's fine - so why 'that won't work like that'?";
			link.l1.go = "Tavern_ChurchGenQuest1_Node_4_2_1";
		break;
			
		case "Tavern_ChurchGenQuest1_Node_4_2_1":
			dialog.text = "Because, mis"+ GetSexPhrase("ter","s") +" captain, I don't need that money. Because I know that captain all too well, so I never actually expected him to pay back and take these manuscripts from me.";
			link.l1 = "What do you mean - you don't need money? So you planned to keep these books right from the start? But why, in God's name?!";
			link.l1.go = "Tavern_ChurchGenQuest1_Node_4_2_2";
		break;
			
		case "Tavern_ChurchGenQuest1_Node_4_2_2":
			dialog.text = "In God's name - exactly, that's why, mis"+ GetSexPhrase("ter","s") +". My little son was very sick, and me and my wife gave a vow to make a donation to the temple, if the Creator cures the child of fever. Our Lord's mercy had no limits, the boy is alive and well, and now we must keep our vow. And just about time captain " + PChar.GenQuest.ChurchQuest_1.CapFullName + " shows up and pawns the church books. I could not allow such obscenity - paying for drinks with the Word - and therefore I decided to hand over this books to the priest of our parish.";
			link.l1 = "Well, certainly this is a good deed, but you should also know that these books actually belong to another priest - actually, not even a priest, but a bishop and my spiritual shepherd. And he might get angry and even accurse those who would encroach upon his books. I would like to buy them from you and bring it safely.";
			link.l1.go = "Tavern_ChurchGenQuest1_Node_4_2_3";
		break;
			
		case "Tavern_ChurchGenQuest1_Node_4_2_3":
			dialog.text = "Mis"+ GetSexPhrase("ter","s") +"... Mis"+ GetSexPhrase("ter","s") +" captain... Surely, I will give them back, and I will require no money in return. You just put in a word for us to the bishop - perhaps, he could bless us and relieve us of our vow...";
			link.l1 = "Of course, your vow will be considered kept - after all, you've given up your profit to return the books to their rightful owner. The particular church doesn't matter, for there is only one God. Alright, give them to me, and good luck to you...";
			link.l1.go = "Tavern_ChurchGenQuest1_Node_4_2_4";
		break;
			
		case "Tavern_ChurchGenQuest1_Node_4_2_4":
			DialogExit();
			AddItems(PChar, "Bible", 1);	// Даем рукописи
			items[FindItem("Bible")].Name = "itmname_ChurchGenQuest1Bible";	// Меняем имя. Потом поменять обратно!
			ChangeItemDescribe("Bible", "itmdescr_ChurchGenQuest1Bible"); // Меняем дескрайб. Потом поменять обратно!
			items[FindItem("Bible")].City = XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.QuestTown + "Gen"); // Переменная. Потом удалить!
			AddMoneyToCharacter(PChar, -sti(PChar.GenQuest.ChurchQuest_1.MoneyToBarmen));
			DeleteAttribute(PChar, "GenQuest.ChurchQuest_1.NeedToDialogWithBarmen");
			sQuestTitle = PChar.GenQuest.ChurchQuest_1.QuestTown + "ChurchGenQuest1";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest1", "9");
			AddQuestUserData(sQuestTitle, "sColony", XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.QuestTown + "Acc"));
			PChar.GenQuest.ChurchQuest_1.Complete = true; // Квест выполнен
			SetFunctionTimerCondition("Church_GenQuest1_DeleteCapitan", 0, 0, 2, false);
		break;
		
		//Jason --> генератор Неудачливый вор
		case "Device_Tavern":
			dialog.text = "Hmm, "+pchar.GenQuest.Device.Shipyarder.Type+"? Never heard of it before... Just what is it, actually? I've never heard about such a thing in all my time.";
			link.l1 = "Well, it's a shipwright's tool, "+pchar.GenQuest.Device.Shipyarder.Describe+". Was anyone offering to you anything like that?";
			link.l1.go = "Device_Trader_1";
			npchar.quest.Device = "true";
		break;
		
		case "Device_Trader_1":
			if (sti(pchar.GenQuest.Device.Shipyarder.Chance1) == 6)
			{
				dialog.text = "Hmm... Yes, one strange type had indeed brought that thing to me. He didn't tell me what it was, though - just tired to exchange it for booze. Of course, I refused - I had no need in that trinket.";
				link.l1 = "And what did he look like and where did he go? I need that instrument badly.";
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
		case "Sunplace_Tavern":
			if (makeint(environment.time) > 12.0 && makeint(environment.time) < 17.0)//в магазине
			{
				dialog.text = ""+pchar.GenQuest.Sunplace.Trader.Enemyname+"? He was recently there, and by now he should have come to his companion - the shopkeeper. Try to look for him at the shop - surely he must be there.";
				link.l1 = "Thanks! You've helped me out a lot!";
				link.l1.go = "Sunplace_Tavern_1";
			}
			else//ушел на рыбалку
			{
				dialog.text = ""+pchar.GenQuest.Sunplace.Trader.Enemyname+"? Today, early in the morning, he's sailed out on his lugger for a marine. I bet that he is standing now at the bulwark, admiring the view. If you need him, you can try to find him at sea or wait until he comes back in a couple of days...";
				link.l1 = "Thanks! I guess I will not be waiting - it's gonna be easier to find him at see. Good luck!";
				link.l1.go = "Sunplace_Tavern_2";
			}
		break;
		
		case "Sunplace_Tavern_1"://магазин
			pchar.quest.Sunplace_Store.win_condition.l1 = "location";
			pchar.quest.Sunplace_Store.win_condition.l1.location = pchar.GenQuest.Sunplace.Trader.CityT + "_store";
			pchar.quest.Sunplace_Store.function = "Sunplace_CreateTrader";
			AddQuestRecord("Sunplace", "6");
			AddQuestUserData("Sunplace", "sName", pchar.GenQuest.Sunplace.Trader.Enemyname);
			AddQuestUserData("Sunplace", "sCity", XI_ConvertString("Colony"+pchar.GenQuest.Sunplace.Trader.CityT+"Gen"));
			DialogExit();
			pchar.GenQuest.Sunplace.Trader = "hunt";
		break;
		
		case "Sunplace_Tavern_2"://рыбалка
			pchar.GenQuest.Sunplace.Trader.IslandID = GetCharacterCurrentIslandId(npchar);
			pchar.GenQuest.Sunplace.Trader.EnemyNation = npchar.nation;
			pchar.quest.Sunplace_Sea.win_condition.l1 = "location";
			pchar.quest.Sunplace_Sea.win_condition.l1.location = pchar.GenQuest.Sunplace.Trader.IslandID;
			pchar.quest.Sunplace_Sea.function = "Sunplace_CreateTraderLugger";
			AddQuestRecord("Sunplace", "7");
			AddQuestUserData("Sunplace", "sName", pchar.GenQuest.Sunplace.Trader.Enemyname);
			AddQuestUserData("Sunplace", "sCity", XI_ConvertString("Colony"+pchar.GenQuest.Sunplace.Trader.CityT+"Gen"));
			DialogExit();
			pchar.GenQuest.Sunplace.Trader = "hunt";
		break;
		// <-- генератор Место под солнцем	
		
		// Jason --> Голландский гамбит
		case "HWICHollJacob_Tavern":
			dialog.text = "Psssst... Why are you shouting? He's been waiting for you for quite some time. He already drank a full quart of rum. Go upstairs to the room, you will find him there.";
			link.l1 = "Oh, I see. Well, goodbye, then.";
			link.l1.go = "exit";
			LocatorReloadEnterDisable(pchar.questTemp.HWIC.Holl.JacobCity+"_tavern", "reload2_back", false);
			pchar.questTemp.HWIC.Holl = "JacobInRoom";
			AddDialogExitQuestFunction("Create_JacobVanBerg");
		break;
		
		case "HWICSelfFernando_Tavern":
			if (NPChar.location == pchar.questTemp.HWIC.Self.SpainCity +"_tavern")
			{
				if (makeint(environment.time) > 10.0 && makeint(environment.time) < 18.0)//на улице
				{
					dialog.text = "Yes, I know that noble man. He should be somewhere in the town - I have just recently seen him walking past my tavern.";
					link.l1 = "Thank you! I will go looking for him!";
					link.l1.go = "Fernando_Land";
				}
				else //в море
				{
					dialog.text = "Yes, he is now visiting our town. Right now he is not there, though - he sailed out on his brigantine. He's likely not far from here, within the waters of our island.";
					link.l1 = "Thanks! You've helped me out a lot!";
					link.l1.go = "Fernando_Sea";
				}
				pchar.questTemp.HWIC.Self = "KillFernando";
			}
			else
			{
				dialog.text = "Fernando Rodriguez? Never heard of him. No, I don't know anything about this man.";
				link.l1 = "I see... Well, the search continues....";
				link.l1.go = "exit";
			}
			npchar.quest.HWICTalked = "true";
		break;
		
		case "Fernando_Land":
			pchar.quest.HWIC_Fernando.win_condition.l1 = "location";
			pchar.quest.HWIC_Fernando.win_condition.l1.location = pchar.questTemp.HWIC.Self.SpainCity +"_town";
			pchar.quest.HWIC_Fernando.function = "CreateFernandoOnLand";
			AddQuestRecord("Holl_Gambit", "3-2");
			DialogExit();
		break;
		
		case "Fernando_Sea":
			pchar.questTemp.HWIC.Self.FernandoIslandID = GetCharacterCurrentIslandId(npchar);
			pchar.quest.HWIC_Fernando.win_condition.l1 = "location";
			pchar.quest.HWIC_Fernando.win_condition.l1.location = pchar.questTemp.HWIC.Self.FernandoIslandID;
			pchar.quest.HWIC_Fernando.function = "CreateFernandoOnSea";
			AddQuestRecord("Holl_Gambit", "3-3");
			DialogExit();
		break;
		//<-- Голландский гамбит
		
		//Jason --> гонки на гидропланах
		case "Race_Advantage":
			dialog.text = "Yes, of course. I am already aware of your victory. Here is your money.";
			link.l1 = "Thank you, " + npchar.name + ".";
			link.l1.go = "Race_Advantage_1";
		break;
		
		case "Race_Advantage_1":
			DialogExit();
			AddMoneyToCharacter(pchar, sti(pchar.GenQuest.Racing.Go.Money)*2);
			AddQuestRecord("Racing", "4");
			AddQuestUserData("Racing", "sStartCity", XI_ConvertString("Colony"+pchar.GenQuest.Racing.Go.StartCity+"Gen"));
			CloseQuestHeader("Racing");
			DeleteAttribute(pchar, "GenQuest.Racing.Go");
		break;
		//<-- гонки на гидропланах
		
		//Jason --> захват пассажиров
		case "Marginpassenger":
			if (CheckAttribute(pchar, "GenQuest.Marginpassenger.lose"))
			{
				dialog.text = "Errr, mister, "+pchar.GenQuest.Marginpassenger.q2Name+" died about "+LinkRandPhrase("a month","three weeks","two months")+" ago. "+LinkRandPhrase("Suddenly succumbed to fever","He was stabbed at the town gates - bandits or those red-skinned savages","He was shot on a duel")+". May the God rest his soul...";
				link.l1 = "Damn it!.. And what am I supposed do with his... Well, whatever. Thanks for the information. See you, " + npchar.name + ".";
				link.l1.go = "Marginpassenger_1";
			}
			else
			{
				dialog.text = ""+pchar.GenQuest.Marginpassenger.q2Name+"? Yeah, he should be somewhere in the town. Look for him on the streets. But keep in mind that every day till noon he is at the governor's office, and after nine in the evening he locks himself up in his house.";
				link.l1 = "Thanks! I'll go looking for him...";
				link.l1.go = "Marginpassenger_2";
			}
		break;
		
		case "Marginpassenger_1":
			DialogExit();
			AddQuestRecord("Marginpassenger", "7");
			AddQuestUserData("Marginpassenger", "sName2", pchar.GenQuest.Marginpassenger.q2Name);
			AddQuestUserData("Marginpassenger", "sCity", XI_ConvertString("Colony"+pchar.GenQuest.Marginpassenger.City));
			pchar.GenQuest.Marginpassenger = "cabin";
		break;
		
		case "Marginpassenger_2":
			DialogExit();
			AddQuestRecord("Marginpassenger", "8");
			AddQuestUserData("Marginpassenger", "sName2", pchar.GenQuest.Marginpassenger.q2Name);
			pchar.GenQuest.Marginpassenger = "street";
		break;
		//<-- захват пассажиров
		
		//Jason --> поиск дезертира
		case "FindFugitiveTav":
			if (NPChar.city == pchar.GenQuest.FindFugitive.City && sti(pchar.GenQuest.FindFugitive.Chance) == 0)
			{
				dialog.text = NPCStringReactionRepeat("It seems that your skipper was telling the truth. "+pchar.GenQuest.FindFugitive.Name+" has indeed recently arrived at our settlement. Look for him on the streets during the day time - he is usually loitering his time away.", "You have already asked me about that man, and I told you everything I knew!", "Are you kidding me or you're an idiot indeed?! You're asking all the same for a third time already!", "Just to think, how such an idiot could become captain...", "block", 1, npchar, Dialog.CurrentNode);
				link.l1 = HeroStringReactionRepeat("Thank you, friend, you've helped me out a lot!", "Yeah, yeah, fine.", "Wow, Wow, don't get so excited. I just forgot.", "Well, he did, as you can see...", npchar, Dialog.CurrentNode); 
				link.l1.go = DialogGoNodeRepeat("FindFugitiveTav_1", "exit", "", "", npchar, Dialog.CurrentNode);
			}
			else
			{
				dialog.text = NPCStringReactionRepeat("No, buddy, I've never heard that name before. Ask around - maybe someone knows him...", "You have already asked me about that man, and I told you: I don't know!", "Are you kidding me or you're an idiot indeed?! You're asking all the same for a third time already!", "Just to think, how such an idiot could become captain...", "block", 1, npchar, Dialog.CurrentNode);
				link.l1 = HeroStringReactionRepeat("I see. Well, thanks anyway.", "Yeah, yeah, fine.", "Wow, Wow, don't get so excited. I just forgot.", "Well, he did, as you can see...", npchar, Dialog.CurrentNode); 
				link.l1.go = DialogGoNodeRepeat("exit", "", "", "", npchar, Dialog.CurrentNode);	
			}
		break;
		
		case "FindFugitiveTav_1":
			DialogExit();
			AddQuestRecord("MayorsQuestsList", "12-1");
			sld = characterFromId("Fugitive");
			LAi_SetWarriorType(sld);
			LAi_warrior_DialogEnable(sld, true);
			sld.dialog.currentnode = "Fugitive_city";
			LAi_SetLoginTime(sld, 11.0, 18.0);
			ChangeCharacterAddressGroup(sld, pchar.GenQuest.FindFugitive.City+"_town", "goto", "goto"+(rand(9)+1));
		break;
		//<-- поиск дезертира
		
		//--> Бремя гасконца
		case "Sharlie_crew":
			dialog.text = "Unfortunately, I can't help you right now - nobody of the people I know would serve under you. But I can give you an advice - talk to that sailor who just took the table right behind you. He and his buddies have just left one merchant ship. Perhaps, they will agree to come with you.";
			link.l1 = "Alright, I'll do just that! Thank you very much!";
			link.l1.go = "exit";
			pchar.questTemp.Sharlie = "sailor";
			//усадим матроса
			sld = GetCharacter(NPC_GenerateCharacter("SharlieSailor" , "citiz_31", "man", "man", 10, FRANCE, -1, true, "quest"));
			FantomMakeCoolFighter(sld, 10, 20, 20, "blade_05", "", "", 10);
			sld.Dialog.Filename = "Quest\Sharlie\OtherNPC.c";
			sld.dialog.currentnode = "Sharlie_sailor";
			sld.greeting = "town_sailor";
			LAi_SetSitType(sld);
			LAi_SetImmortal(sld, true);
			FreeSitLocator("FortFrance_tavern", "sit7");
			ChangeCharacterAddressGroup(sld, "FortFrance_tavern", "sit", "sit7");
		break;
		
		case "Sharlie_skiper":
			dialog.text = "I cannot tell you anything specific, friend. At this moment no navigators are frequenting my place. Try to ask around in the port - perhaps, people would know more.";
			link.l1 = "I see. Alright, I'll go talk to the people.";
			link.l1.go = "exit";
			pchar.questTemp.Sharlie = "findskiper";
			//сгенерим наводчика
			sld = GetCharacter(NPC_GenerateCharacter("SharlieSkiperTalker", "citiz_"+(rand(19)+21), "man", "man", 10, FRANCE, -1, true, "marginal"));
			FantomMakeCoolFighter(sld, 10, 20, 20, RandPhraseSimple("blade_04","blade_06"), "", "", 10);
			sld.Dialog.Filename = "Quest\Sharlie\OtherNPC.c";
			sld.dialog.currentnode = "skipertalker";
			sld.greeting = "marginal";
			LAi_SetWarriorType(sld);
			LAi_SetImmortal(sld, true);
			LAi_group_MoveCharacter(sld, "FRANCE_CITIZENS");
			ChangeCharacterAddressGroup(sld, "FortFrance_town", "patrol", "patrol"+(rand(13)+1));
			LAi_SetLoginTime(sld, 6.0, 21.99);
		break;
		//<-- Бремя гасконца
		
		// Addon 2016-1 Jason пиратская линейка
		case "mtraxx_tortuga":
			sld = characterFromId("Tortuga_waitress");
            dialog.text = "At once, Monseniour!.. The very best French vine! "+sld.name+"! Go open the guest room, now!.. It`ll be 1000 pesos, Monseniour.";
			link.l1 = "Take it!";
			link.l1.go = "mtraxx_tortuga_1";
		break;
		
		case "mtraxx_tortuga_1":
			AddMoneyToCharacter(pchar, -1000);
            DialogExit();
			pchar.questTemp.Mtraxx.Retribution = "room";
			pchar.quest.mtraxx_retribution_room.win_condition.l1 = "locator";
			pchar.quest.mtraxx_retribution_room.win_condition.l1.location = "Tortuga_tavern";
			pchar.quest.mtraxx_retribution_room.win_condition.l1.locator_group = "reload";
			pchar.quest.mtraxx_retribution_room.win_condition.l1.locator = "reload2_back";
			pchar.quest.mtraxx_retribution_room.function = "Mtraxx_RetributionToRoom";
		break;
	}
}

string findTraderCity(ref NPChar)
{
	int n, nation;
    int storeArray[MAX_COLONIES];
    int howStore = 0;

	for(n=0; n<MAX_COLONIES; n++)
	{
		nation = GetNationRelation(sti(npchar.nation), sti(colonies[n].nation));
		if (colonies[n].id != "Panama" && colonies[n].nation != "none" && GetIslandByCityName(npchar.city) != colonies[n].islandLable) //не на свой остров
		{
			if (nation == RELATION_ENEMY || sti(npchar.nation) == PIRATE)
			{
				storeArray[howStore] = n;
				howStore++;
			}
		}
	}
	if (howStore == 0) return "none";
	nation = storeArray[cRand(howStore-1)];
	return colonies[nation].id;
}

string findPassangerCity(ref NPChar)
{
	int n, nation;
    int storeArray[MAX_COLONIES];
    int howStore = 0;

	for(n=0; n<MAX_COLONIES; n++)
	{
		nation = GetNationRelation(sti(npchar.nation), sti(colonies[n].nation));
		if (colonies[n].nation != "none" && colonies[n].id != "Panama" && GetIslandByCityName(npchar.city) != colonies[n].islandLable) //не на свой остров
		{
			if (nation == RELATION_ENEMY || sti(npchar.nation) == PIRATE)
			{
			storeArray[howStore] = n;
			howStore++;
		}
	}
	}
	if (howStore == 0) return "none";
	nation = storeArray[cRand(howStore-1)];
	return colonies[nation].id;
}
