//Jason общий диалог уличных контриков
#include "DIALOGS\russian\Rumours\Common_rumours.c"
void ProcessDialogEvent()
{
	ref NPChar;
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
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "What do you want?";
			link.l1 = "Nothing.";
			link.l1.go = "exit";
			link.l2 = RandPhraseSimple("I've got a question for you.", "I need information.");
			link.l2.go = "quests";//(перессылка в файл города)
			
			if (npchar.quest.meeting == "0")
			{
				if (sti(Pchar.Ship.Type) != SHIP_NOTUSED && CheckAttribute(npchar, "quest.passenger") && !CheckAttribute(pchar, "GenQuest.Marginpassenger"))//захват пассажира
				{
					dialog.text = "Hey, sailor! Yes, you. Come closer I've got a deal for you...";
					link.l1 = "And what's the deal?";
					link.l1.go = "passenger";
					link.l2 = "I am in a hurry, friend. Next time perhaps.";
					link.l2.go = "exit_quest";
					npchar.quest.meeting = "1";
					DeleteAttribute(npchar, "talker"); //снимаем говорилку
					break;
				}
				dialog.text = LinkRandPhrase("Hey, sailor, I am busy actually. What do you need?","What do you want, sailor?","Cap, I am not in the right mood to talk. What do you want?");
				link.l1 = "Greeting, "+GetAddress_FormToNPC(NPChar)+". Wait a minute, I want you to tell me something.";
				link.l1.go = "question";
				link.l2 = RandPhraseSimple("I have a question for you.", "I need information.");
				link.l2.go = "quests";//(перессылка в файл города)
				link.l3 = "It's nothing, I am on a way to the tavern...";
				link.l3.go = "exit";
				npchar.quest.meeting = "1";
			}
			NextDiag.TempNode = "First time";
		break;

//----------------------------------------захват пассажиров для выкупа------------------------------------------
			case "passenger":
				DeleteAttribute(npchar, "talker");
				dialog.text = "Hm. You are a captain of the ship and you are not a trader. It looks like you have some coins in your pocket... How about to get some interesting information in exchange of a full hand of doubloons?";
				link.l1 = "First, prove that your information is worth paying at least a single silver peso.";
				link.l1.go = "passenger_1";
			break;
		
			case "passenger_1":
				dialog.text = "It is, cap, it is. It costs much more than I ask. You give me gold and I'll tell you when and on which ship one high flying person will sail. You will be able to ransom this one for a very good price... I'll even tell you the name of the buyer. Deal?";
				link.l1 = "No way! I don't ransom people. Get lost!";
				link.l1.go = "exit_quest";
				link.l2 = "And how can I know that you are telling the truth?";
				link.l2.go = "passenger_2";
			break;
		
			case "passenger_2":
				pchar.GenQuest.Marginpassenger.Dublon = 70+drand(5)*10;
				dialog.text = "I won't cheat on you, salty sailor. I live in this town and I don't need troubles. For just "+sti(pchar.GenQuest.Marginpassenger.Dublon)+" doubloons I'll give a complete information. You will make much more.";
				if (GetCharacterItem(pchar, "gold_dublon") >= sti(pchar.GenQuest.Marginpassenger.Dublon))
				{
					link.l1 = "You have a point. Take them. Don't even try to lie now...";
					link.l1.go = "passenger_4";
				}
				link.l2 = "I don't have enough coins with me now.";
				link.l2.go = "passenger_3";
				link.l3 = "Are you kidding me? Pay a lot of gold for I don't even know what? Get lost...";
				link.l3.go = "exit_quest";
			break;
		
			case "passenger_3":
				dialog.text = "Don't you? Fine, cap. I can wait for a few days more and this information can too. Find me when you'll get your gold. It won't be difficult to find me... today, ha-ha-ha!";
				link.l1 = "Don't show me your teeth like that. Fine, I'll bring you the gold... if I don't change my mind. ";
				link.l1.go = "passenger_wait";
			break;
			
			case "passenger_wait":
			DialogExit();
				SetFunctionTimerCondition("Marginpassenger_Over", 0, 0, 2, false);
				npchar.dialog.currentnode = "passenger_repeat";
			break;

			case "passenger_repeat":
				dialog.text = "Did you bring my gold?";
				if (GetCharacterItem(pchar, "gold_dublon") >= sti(pchar.GenQuest.Marginpassenger.Dublon))
				{
					link.l1 = "Yes. Take it. Don't even try to lie now...";
					link.l1.go = "passenger_4";
				}
				link.l2 = "Not yet. Maybe later...";
				link.l2.go = "exit";
				Nextdiag.Tempnode = "passenger_repeat";
			break;
			
			case "passenger_4"://установка параметров
				pchar.quest.Marginpassenger_Over.over = "yes"; //снять возможный таймер
				RemoveItems(pchar, "gold_dublon", sti(pchar.GenQuest.Marginpassenger.Dublon));
				pchar.GenQuest.Marginpassenger.Name = GetFullName(npchar);
				pchar.GenQuest.Marginpassenger.City = npchar.city;
				pchar.GenQuest.Marginpassenger.Targetcity = SelectAnyColony(npchar.city); 
				pchar.GenQuest.Marginpassenger.Nation = npchar.nation;
				pchar.GenQuest.Marginpassenger.Days = 10+drand(5);
				pchar.GenQuest.Marginpassenger.ShipName = GenerateRandomNameToShip(sti(npchar.nation));
				pchar.GenQuest.Marginpassenger.q2Name = GenerateRandomName(sti(npchar.nation), "man");
				pchar.GenQuest.Marginpassenger.Chance = 0.8+frand(0.4);
				SelectMarginpassengerParameter();
				log_testinfo(pchar.GenQuest.Marginpassenger.Targetcity);
				dialog.text = "Don't waste your gunpowder, you'll need it soon, cap. Now listen, in "+FindRussianDaysString(sti(pchar.GenQuest.Marginpassenger.Days))+" a ship will sail away from our colony, the ship is "+GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.Marginpassenger.ShipType), "Name")))+" named '"+pchar.GenQuest.Marginpassenger.ShipName+"' and it will be heading to "+XI_ConvertString("Colony"+pchar.GenQuest.Marginpassenger.Targetcity+"Gen")+". There will be a passenger -  "+pchar.GenQuest.Marginpassenger.Text+", named "+pchar.GenQuest.Marginpassenger.q1Name+"\nThe captain "+GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.Marginpassenger.ShipType), "Name")+"Gen"))+" is a coward chicken like all traders, ha-ha-ha! Perhaps, you will even avoid any fighting. Just scare a crap out of him and he will give you the client himself, he-he\nAs you understand, "+pchar.GenQuest.Marginpassenger.Text1+", you'll probably get your coins, yes, but the local authorities will hunt you to death after that. You'd better bring your pray to "+XI_ConvertString("Colony"+pchar.GenQuest.Marginpassenger.Targetcity)+". You'll find there a man named "+pchar.GenQuest.Marginpassenger.q2Name+"\n"+pchar.GenQuest.Marginpassenger.Text2+" and you won't be even need to tell your name. It's your decision to evaluate your prisoner, but don't bite off more then you can chew... But "+sti(pchar.GenQuest.Marginpassenger.Dublon)*4+" doubloons you can ask for sure. Got it?";
				link.l1 = "Yes. I am going to get back on my ship and write it in the log.";
				link.l1.go = "passenger_5";
			break;
		
			case "passenger_5":
				dialog.text = "Exactly! Right choice. Fine, cap, good luck in this easy task. Oh yes, I've almost forgotten: "+GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.Marginpassenger.ShipType), "Name")))+" will sail not from the port but from one of bays nearby. So watch it. Good luck and thanks for the gold!";
				link.l1 = "You're welcome. I hope that you're not going to waste all of it tonight in the tavern.";
				link.l1.go = "exit_quest";
				npchar.lifeday = 0;
				ReOpenQuestHeader("Marginpassenger");
				AddQuestRecord("Marginpassenger", "1");
				AddQuestUserData("Marginpassenger", "sCity", XI_ConvertString("Colony"+pchar.GenQuest.Marginpassenger.City));
				AddQuestUserData("Marginpassenger", "sTargetCity", XI_ConvertString("Colony"+pchar.GenQuest.Marginpassenger.Targetcity));
				AddQuestUserData("Marginpassenger", "sName", pchar.GenQuest.Marginpassenger.Name);
				AddQuestUserData("Marginpassenger", "sName1", pchar.GenQuest.Marginpassenger.q1Name);
				AddQuestUserData("Marginpassenger", "sName2", pchar.GenQuest.Marginpassenger.q2Name);
				AddQuestUserData("Marginpassenger", "sDay", FindRussianDaysString(sti(pchar.GenQuest.Marginpassenger.Days)));
				AddQuestUserData("Marginpassenger", "sShipType", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.Marginpassenger.ShipType), "Name")+"Voc")));
				AddQuestUserData("Marginpassenger", "sShipName", pchar.GenQuest.Marginpassenger.ShipName);
				AddQuestUserData("Marginpassenger", "sText", pchar.GenQuest.Marginpassenger.Text1);
				pchar.GenQuest.Marginpassenger = "begin";
				SetFunctionTimerCondition("Marginpassenger_InWorld", 0, 0, sti(pchar.GenQuest.Marginpassenger.Days), false);
			break;
			
		//замечание по обнаженному оружию от персонажей типа citizen
		case "CitizenNotBlade":
			dialog.text = NPCharSexPhrase(NPChar, "Listen buddy, calm down and sheathe your weapon.", "Listen buddy, calm down and sheathe your weapon.");
			link.l1 = LinkRandPhrase("Fine.", "Okay.", "As you wish.");
			link.l1.go = "exit";
		break;
		
		case "question":
			dialog.text = LinkRandPhrase("Don't beat around the bush, cap. Speak what you want!","Oh, fine. What do you want?","Questions? Fine, sailor, I am listening.");
			link.l1 = LinkRandPhrase("Can you tell me the last gossip of this town?","Has anything interesting happened here recently?","What's going on in the archipelago?");
			link.l1.go = "rumours_marginal";
		break;
		
		case "exit_quest":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}

void SelectMarginpassengerParameter()
{
	if (drand(1) == 0)
	{
		pchar.GenQuest.Marginpassenger.q1Name = GenerateRandomName(sti(pchar.GenQuest.Marginpassenger.Nation), "woman");
		pchar.GenQuest.Marginpassenger.model = "women_"+(rand(5)+11);
		pchar.GenQuest.Marginpassenger.sex = "woman";
		pchar.GenQuest.Marginpassenger.ani = "towngirl";
		pchar.GenQuest.Marginpassenger.Text2 = "He wants to marry her and will pay a significant sum for the girl.";
		switch (drand(4))
		{
			case 0: 
				pchar.GenQuest.Marginpassenger.Text = "store keeper's daughter";
				pchar.GenQuest.Marginpassenger.Text1 = "from her father, the store keeper";
				pchar.GenQuest.Marginpassenger.loc = pchar.GenQuest.Marginpassenger.City+"_store";
			break;
			case 1: 
				pchar.GenQuest.Marginpassenger.Text = "shipyard's master's daughter";
				pchar.GenQuest.Marginpassenger.Text1 = "from her father, the shipyard's master";
				pchar.GenQuest.Marginpassenger.loc = pchar.GenQuest.Marginpassenger.City+"_shipyard";
			break;
			case 2: 
				pchar.GenQuest.Marginpassenger.Text = "tavern keeper's daughter";
				pchar.GenQuest.Marginpassenger.Text1 = "from her father, the tavern keeper";
				pchar.GenQuest.Marginpassenger.loc = pchar.GenQuest.Marginpassenger.City+"_tavern";
			break;
			case 3: 
				pchar.GenQuest.Marginpassenger.Text = "banker's daughter";
				pchar.GenQuest.Marginpassenger.Text1 = "from her father, the banker";
				pchar.GenQuest.Marginpassenger.loc = pchar.GenQuest.Marginpassenger.City+"_bank";
			break;
			case 4: 
				pchar.GenQuest.Marginpassenger.Text = "harbor master's daughter";
				pchar.GenQuest.Marginpassenger.Text1 = "from her father, the harbor master";
				pchar.GenQuest.Marginpassenger.loc = pchar.GenQuest.Marginpassenger.City+"_portoffice";
			break;
		}
	}
	else
	{
		pchar.GenQuest.Marginpassenger.q1Name = GenerateRandomName(sti(pchar.GenQuest.Marginpassenger.Nation), "man");
		pchar.GenQuest.Marginpassenger.model = "citiz_"+(rand(9)+11);
		pchar.GenQuest.Marginpassenger.sex = "man";
		pchar.GenQuest.Marginpassenger.ani = "man";
		pchar.GenQuest.Marginpassenger.Text2 = "He has been planning to ingratiate himself with this family and he will pay a lot for the prisoner ";
		switch (drand(4))
		{
			case 0: 
				pchar.GenQuest.Marginpassenger.Text = "trader's relative, shipmaster's";
				pchar.GenQuest.Marginpassenger.Text1 = "from his relative, the shipmaster";
				pchar.GenQuest.Marginpassenger.loc = pchar.GenQuest.Marginpassenger.City+"_store";
			break;
			case 1: 
				pchar.GenQuest.Marginpassenger.Text = "shipyard's master's relative";
				pchar.GenQuest.Marginpassenger.Text1 = "from his relative, the shipyard's master";
				pchar.GenQuest.Marginpassenger.loc = pchar.GenQuest.Marginpassenger.City+"_shipyard";
			break;
			case 2: 
				pchar.GenQuest.Marginpassenger.Text = "tavern keeper's relative";
				pchar.GenQuest.Marginpassenger.Text1 = "from his relative, the tavern keeper";
				pchar.GenQuest.Marginpassenger.loc = pchar.GenQuest.Marginpassenger.City+"_tavern";
			break;
			case 3: 
				pchar.GenQuest.Marginpassenger.Text = "banker's relative";
				pchar.GenQuest.Marginpassenger.Text1 = "from his relative, the banker";
				pchar.GenQuest.Marginpassenger.loc = pchar.GenQuest.Marginpassenger.City+"_bank";
			break;
			case 4: 
				pchar.GenQuest.Marginpassenger.Text = "harbor master's relative";
				pchar.GenQuest.Marginpassenger.Text1 = "from his relative, the harbor master";
				pchar.GenQuest.Marginpassenger.loc = pchar.GenQuest.Marginpassenger.City+"_portoffice";
			break;
		}
	}
	if (sti(pchar.rank) < 4) pchar.GenQuest.Marginpassenger.ShipType = SHIP_BARQUE;
	if (sti(pchar.rank) >= 4 && sti(pchar.rank) < 7) pchar.GenQuest.Marginpassenger.ShipType = SHIP_BARKENTINE + rand(makeint(SHIP_FLEUT - SHIP_BARKENTINE));
	if (sti(pchar.rank) >= 7 && sti(pchar.rank) < 10) pchar.GenQuest.Marginpassenger.ShipType = SHIP_CARAVEL + rand(makeint(SHIP_CARACCA - SHIP_CARAVEL));
	if (sti(pchar.rank) >= 10 && sti(pchar.rank) < 16) pchar.GenQuest.Marginpassenger.ShipType = SHIP_GALEON_L;
	if (sti(pchar.rank) >= 16) pchar.GenQuest.Marginpassenger.ShipType = SHIP_NAVIO + rand(makeint(SHIP_GALEON_H - SHIP_NAVIO));
}
