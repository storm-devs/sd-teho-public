#include "DIALOGS\russian\Rumours\Common_rumours.c"
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	string sLoc;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	ProcessCommonDialogRumors(NPChar, Link, NextDiag);
	
	bool bLock = (CheckAttribute(pchar, "GenQuest.BrothelLock")) && (GetCharacterIndex("Mary") != -1);
	bool bLock1 = (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) && (IsOfficer(characterFromId("Helena")));

	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (LAi_grp_playeralarm > 0)
			{
       			dialog.text = NPCharRepPhrase(pchar,
					LinkRandPhrase("There's been an alarm raised in the town. Everyone's looking for you! I wouldn't wait around here for too long if I were you.", "The whole guard is scouring the town trying to find you. I'm not an idiot and I'm not about to talk to you!", "Run, buddy, before the soldiers make mincemeat out of you..."),
					LinkRandPhrase("What do you need, scum?! The town guard is already on your trails. You won't get far, dirty pirate!", "Dirty killer, get out of my house! Guards!!", "I'm not afraid of you, hoodlum! The noose is calling you, you won't get far..."));
				link.l1 = NPCharRepPhrase(pchar,
					RandPhraseSimple("Heh, I'm not worried about the alarm...", "They have no chance of catching me."),
					RandPhraseSimple("Shut your pie hole, " + GetWorkTypeOfMan(npchar, "") + ", or I will cut along your goddamn mouth.", "Heh, " + GetWorkTypeOfMan(npchar, "") + ", you too want to hunt a pirate! Listen, pal, keep calm and you'll live..."));
				link.l1.go = "exit";
				break;
			}
			if (npchar.quest.meeting == "0")
			{
				dialog.text = TimeGreeting() + "! Welcome, " + GetAddress_Form(NPChar) + " to Los-Teques mine saloon. Food, drinks and... girls. All at affordable prices! My name is "+GetFullName(npchar)+" and I am always at your service.";
				Link.l1 = "Let's see... I'm " + GetFullName(pchar) + ". Pleased to meet you, "+npchar.name+".";
				Link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "Aha, it's my old acquaintance, captain "+GetFullName(pchar)+"! Glad to see you, old man! Rum, girls?";
				if (makeint(pchar.money) >= 5)
				{
					link.l1 = "Pour me some rum, "+npchar.name+".";
					link.l1.go = "drink";
				}
				link.l2 = "I'd like to get some shut eye. Do you have a free room?";
				link.l2.go = "room";
				link.l3 = LinkRandPhrase("Do you have any current news?","What's new in these parts?","How's life coming along on dry land?");
				link.l3.go = "rumours_tavern";
				link.l4 = "No, I don't need anything, "+npchar.name+". I just stopped by to say hello to you.";
				link.l4.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting":
			dialog.text = "Oh, I'm so happy! New faces are a rarity in our city. How about I pour you some rum and we'll have a chat...";
			link.l1 = "This is my first time here and I'd like to find out a little bit more about this settlement.";
			link.l1.go = "info";
			if (makeint(pchar.money) >= 5)
			{
				link.l2 = "Pour me some rum, "+npchar.name+".";
				link.l2.go = "drink";
			}
			link.l3 = "I'd like to get some shut eye. Do you have a free room?";
			link.l3.go = "room";
		break;
		
		case "info":
			dialog.text = "Nothing interesting to tell. Same crap everyday: boredom, sun and dust. Only soldiers and Indians live here. You may also find a few adventures and bandits hungry for gold\nSometimes gentlemen, captains like yourself, visit us in order to sell slaves for ingots and to buy valuable metals. Our merchant is quite interesting man, he sells not only golden and silver nuggets, but also some gems. Not precious ones\n But he claims that people with special knowledge may find those cobblestones very useful. So check our store. The mine itself is located further beneath the mountain. You may attend it if you wish, but I recommend to avoid making guard upset\nDon't talk to convicts and God save you from stealing. Anyways, the best place in this settlement is my tavern, the only place to rest from this burning hell!";
			link.l1 = "Thanks for the information!";			
			link.l1.go = "exit";
		break;
		
		case "drink":
			if (CheckAttribute(pchar, "questTemp.Rum") && sti(pchar.questTemp.Rum) > 3)
			{
				dialog.text = "Captain, I think you'd be better off stopping. God forbid you raise hell while your under the influence of alcohol. We're really strict about that here even your authority won't help you.";
				link.l1 = "Hm... I suppose you're right –I've already had enough. Thanks for the concern!";			
				link.l1.go = "exit";
			}
			else
			{
				AddMoneyToCharacter(pchar, -5);
				if(!IsEquipCharacterByArtefact(pchar, "totem_01"))
				{
					if (CheckAttribute(pchar, "questTemp.Rum"))
					{
						pchar.questTemp.Rum = sti(pchar.questTemp.Rum) + 1;
					}
					else pchar.questTemp.Rum = 1;
				}
				else 
				{
					if(CheckAttribute(pchar, "questTemp.Rum")) DeleteAttribute(pchar, "questTemp.Rum");
				}				
				WaitDate("",0,0,0, 0, 30);
				
				dialog.text = "You're welcome, captain. Just five pesos for a pint of my best black Jamaican rum!";
				link.l1 = RandPhraseSimple(LinkRandPhrase("All right, to your health and the prosperity of your establishment, buddy!","All right, to those at sea!","All right, to the augmented well-being of your town!"), LinkRandPhrase("All right, to a gust of production, to a gust of luck, that we all live more light-hearted and wealthy!","All right, to the wind always blowing in our backs in all affairs!","All right, to happiness, luck, joy, and... women!"));		
				link.l1.go = "drink_1";
			}
		break;
		
		case "drink_1":
			DialogExit();
			LAi_Fade("", "");
			if (CheckAttribute(pchar, "questTemp.Rum"))
			{
				DeleteAttribute(pchar, "chr_ai.drunk");
				if (sti(pchar.questTemp.Rum) < 3) LAi_AlcoholSetDrunk(pchar, 51, 5600);
				else
				{
					LAi_AlcoholSetDrunk(pchar, 71, sti(pchar.questTemp.Rum)*2800);
					Pchar.GenQuest.CamShuttle = makeint(sti(pchar.questTemp.Rum)/2); // Jason
				}
			}
		break;
		
		case "room":
			if (CheckAttribute(pchar, "GenQuest.MinentownSex"))
			{
				dialog.text = "Senior, you've paid for a room and a girl. Go on upstairs, she's been waiting for you for a while.";
				link.l1 = "All right.";
				link.l1.go = "exit";
				break;
			}
			dialog.text = "We do. How long were you planning to stay?";
			if(!isDay())
			{
				link.l1 = "Till the morning.";
				link.l1.go = "room_day";
			}
			else
			{
				link.l1 = "Till the night time.";
				link.l1.go = "room_night";
				link.l2 = "Until the next morning.";
				link.l2.go = "room_day_next";
			}
		break;

		case "room_day":
			dialog.text = "That'll be ten pesos. Would you like a girl for the room along with it? Only a thousand pesos for the date.";
			if (makeint(pchar.money) >= 10)
			{
				link.l1 = "No, I don't need a girl. Here, take this for the room.";
				link.l1.go = "room_day_wait";
			}
			if (makeint(pchar.money) >= 1010)
			{
				if (IsOfficer(characterFromId("Mary")) || !bLock || !bLock1)
				{
					link.l2 = "Okay. Let's do the room and the girl. Here's the money.";
					link.l2.go = "room_girl";
					sTotalTemp = "wait_day";
				}
			}
			link.l3 = "Alas, I cannot afford the room.";
			link.l3.go = "exit";
		break;

		case "room_day_next":
			dialog.text = "That'll be ten pesos. Would you like a girl for the room along with it? Only a thousand pesos for the date.";
			if (makeint(pchar.money) >= 10)
			{
				link.l1 = "No, I don't need a girl. Here, take this for the room.";
				link.l1.go = "room_day_wait_next";
			}
			if (makeint(pchar.money) >= 1010)
			{
				if (IsOfficer(characterFromId("Mary")) || !bLock || !bLock1)
				{
					link.l2 = "Okay. Let's do the room and the girl. Here's the money.";
					link.l2.go = "room_girl";
					sTotalTemp = "wait_day";
				}
			}
			link.l3 = "Alas, I cannot afford the room.";
			link.l3.go = "exit";
		break;

		case "room_night":
			dialog.text = "That'll be ten pesos. Would you like a girl for the room along with it? Only a thousand pesos for the date.";
			if (makeint(pchar.money) >= 10)
			{
				link.l1 = "No, I don't need a girl. Here, take this for the room.";
				link.l1.go = "room_night_wait";
			}
			if (makeint(pchar.money) >= 1010)
			{
				if (IsOfficer(characterFromId("Mary")) || !bLock || !bLock1)
				{
					link.l2 = "Okay. Let's do the room and the girl. Here's the money.";
					link.l2.go = "room_girl";
					sTotalTemp = "wait_night";
				}
			}
			link.l3 = "Alas, I cannot afford the room.";
			link.l3.go = "exit";
		break;

		case "room_night_wait":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			AddMoneyToCharacter(pchar, -10);
			AddDialogExitQuest("sleep_in_tavern");
			TavernWaitDate("wait_night");
		break;

		case "room_day_wait":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			AddMoneyToCharacter(pchar, -10);
			AddDialogExitQuest("sleep_in_tavern");
			TavernWaitDate("wait_day");
		break;

		case "room_day_wait_next":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			AddMoneyToCharacter(pchar, -20);
			AddDialogExitQuest("sleep_in_tavern");
			TavernWaitDate("wait_day");
		break;
		
		case "room_girl":
			AddMoneyToCharacter(pchar, -1010);
			dialog.text = "Go on upstairs, senior. The girl will be waiting for you. Have a nice stay!";
			link.l1 = "Thanks, buddy...";
			link.l1.go = "room_girl_1";
		break;
		
		case "room_girl_1":
			DialogExit();
			pchar.GenQuest.CannotWait = true;
			pchar.GenQuest.MinentownSex = "true";
			LocatorReloadEnterDisable("Minentown_tavern", "reload1_back", true); //закрыть таверну
			LocatorReloadEnterDisable("Minentown_tavern", "reload2_back", false); //открыть комнату
			bDisableFastReload = true;//закрыть переход
			sld = GetCharacter(NPC_GenerateCharacter("MineFuckGirl" , "squaw_"+(rand(2)+1), "woman", "woman_B", 1, SPAIN, 1, true, "quest"));
			sld.dialog.FileName = "Tavern\Minentown_Tavern.c";
			sld.dialog.currentnode = "MineFuckGirl";
			//sld.greeting = "";
			sld.name = GetIndianName(WOMAN);
			sld.lastname = "";
			LAi_SetStayType(sld);
			ChangeCharacterAddressGroup(sld, "Minentown_tavern_upstairs", "goto", "goto1");
		break;
		
		case "MineFuckGirl":
			dialog.text = "Glad to see you, white senior. And don't look at "+npchar.name+" like that, "+npchar.name+" knows how to do everything no worse than white squaw from brothel. Ah, senior so cute... Promise, you be happy.";
			link.l1 = "All right, baby, let's see...";
			link.l1.go = "MineFuckGirl_sex";
		break;
		
		case "MineFuckGirl_sex":
			DialogExit();
			DoQuestCheckDelay("PlaySex_1", 0.1);
		break;

 		case "Exit":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
		break;

		// ============== Грабеж среди бела дня, попытка залезть в сундуки =========================
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("Robbery in broad day light!!! What's going on here?! Wait, hold on, buddy...", "Hey, what are doing there?! Trying to rob me? Now you are fucked up...", "Wait, what the hell are you doing? Turns out that you are a thief! Consider this the end of the line, arsehole...");
			link.l1 = LinkRandPhrase("Devil!", "Fuck!", "Ah, shit");
			link.l1.go = "PL_Q3_fight";
		break;
		
		case "fight":
            Pchar.quest.ArestInResidenceEnd.win_condition.l1          = "ExitFromLocation";
		    Pchar.quest.ArestInResidenceEnd.win_condition.l1.location = Pchar.location;
		    Pchar.quest.ArestInResidenceEnd.win_condition             = "ArestInResidenceEnd";
		    Pchar.quest.ArestInResidenceEnd.ResidenceLocation = Pchar.location;
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;

			LAi_LockFightMode(Pchar, true); // ножками путь убегает
		    LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
		    LAi_group_Attack(NPChar, Pchar); // не работает на бессмертного мера :(
			i = GetCharIDXByParam("CityType", "location", Pchar.location); // фантом солдат
			if (i != -1)
			{
			    LAi_group_Attack(&Characters[i], Pchar);
			}
		break;
	}
}
