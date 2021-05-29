// boal 25/04/04 общий диалог Governor
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

    // вызов диалога по городам -->
    NPChar.FileDialog2 = "DIALOGS\" + LanguageGetLanguage() + "\Governor\" + NationShortName(sti(NPChar.nation)) + "_Governor.c";
    if (LoadSegment(NPChar.FileDialog2))
	{
        ProcessCommonDialog(NPChar, Link, NextDiag);
		UnloadSegment(NPChar.FileDialog2);
	}
    // вызов диалога по городам <--
    
    ref offref, sld;
    int i, cn;
    int qty;
    int iSumm;
    string attrLoc;

    /// выкуп колонии
    ref CaptGovenor, FortColony;
    int f, colony_money;

    int k = 1000;
    if (CheckAttribute(Nations[sti(NPChar.nation)], "Fort"))
    {
        k = (300 - sti(Nations[sti(NPChar.nation)].Fort)*10);
    }
	bool ok;
	
	attrLoc = Dialog.CurrentNode;
	if (findsubstr(attrLoc, "CityGive_" , 0) != -1)
 	{
        i = findsubstr(attrLoc, "_" , 0);
	 	NPChar.quest.CityIdx = strcut(attrLoc, i+1, strlen(attrLoc)-1); // индех в конце
 	    Dialog.CurrentNode = "ColonyGive";
 	}
 	
	switch (Dialog.CurrentNode)
	{
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOff");
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
					LinkRandPhrase("You dare to show your face at governor-general's office?! You're insane, indeed...", "How did these lazybones let an enemy break into my residence? This is beyond my mind...", "Surely, my guards aren't worth a coin if "+ GetSexPhrase("some tramp","some tramp") +" is running around in my residence..."), 
					LinkRandPhrase("What do you need, "+ GetSexPhrase("creep","stinker") +"?! My soldiers have already been set on your trail, "+ GetSexPhrase("filthy pirate","stinker") +"!", ""+ GetSexPhrase("Filthy","Filthy") +" murderer, leave my residence immediately! Guards!", "I am not afraid of you, "+ GetSexPhrase("scoundrel","rascal") +"! Soon you will be hung in our fort, you won't get far..."));
				link.l1 = NPCharRepPhrase(pchar,
					RandPhraseSimple("Soldiers aren't worth a crap...", "You will never get me."), 
					RandPhraseSimple("Shut up, buddy, or I'll rip out that foul tongue of yours!", "I'm telling you, buddy: sit quietly or I will cut off your head and throw it through that door to your guardian dogs..."));
				link.l1.go = "fight";
				break;
			}
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "I've heard that you were very persistent at requesting an audience. My name is " + GetFullName(npchar) +
                              ". I am the governor-general of the colonies of " + NationNameGenitive(sti(NPChar.nation))+ ", deputy of the Crown of " + NationKingsName(npchar)+
                              " in these waters. Now, please be so kind to tell me, what is the purpose of your visit, " + GetAddress_Form(NPChar) + ".";
				link.l1 = "My name is " + GetFullName(pchar) + ".";
				link.l1.go = "node_1";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = RandPhraseSimple("Oh, that's you again? Well, what do you want from the governor-general " + NationNameGenitive(sti(NPChar.nation))+ " this time?",
                              "And once again, you are distracting me from important affairs of state? What do you want, " +GetAddress_Form(NPChar)+"?");
				link.l1 = "I want to talk with you about work in the name of the Crown of " + NationNameGenitive(sti(NPChar.nation));
				link.l1.go = "work";
				link.l2 = "I need to talk with you about one important affair.";
				link.l2.go = "quests"; // файл нации
				//Jason --> Регата
				if (CheckAttribute(pchar, "questTemp.Regata.ToPortRoyal") && NPChar.location == "Portroyal_townhall")
				{
					link.l3 = "I came on an invitation to participate in the regatta. Here's my invitation.";
					link.l3.go = "Regata";
				}
				//<-- Регата
				link.l10 = "I am sorry, but I have some business to do.";
				link.l10.go = "exit";
			}
		break;
		
		case "node_1":
			dialog.text = "So what was the reason for you to come here and distract me from important affairs of state?";
			link.l1 = "I wanted to talk to you about work in the name of the Crown of " + NationNameGenitive(sti(NPChar.nation));
			link.l1.go = "work";
			link.l2 = "I was going to talk to you bout one important affair.";
			link.l2.go = "quests";
			//Jason --> Регата
			if (CheckAttribute(pchar, "questTemp.Regata.ToPortRoyal") && NPChar.location == "Portroyal_townhall")
			{
				link.l3 = "I came here for participating in the regatta. Here's my invitation.";
				link.l3.go = "Regata";
			}
			//<-- Регата
			link.l10 = "It is just a courtesy visit and nothing more, "+GetAddress_FormToNPC(NPChar);
			link.l10.go = "node_2";
		break;

		case "node_2":
			dialog.text = "In that case I would ask you to leave my office and stop distracting me from my work.";
			link.l1 = "Yes, yes, of course. Sorry about bothering you.";
			link.l1.go = "exit";
		break;
		
		case "work":
            dialog.text = "If you are looking for work, talk with the governors of colonies. They are often in need for smart and brave captains.";
			link.l1 = "I'll keep that in mind. Thank you.";
			link.l1.go = "exit";
		break;
		
		//--> Jason регата
		case "Regata":
			dialog.text = "Oh, great, glad to see you, captain! You've arrived just in time - the regatta is about to start in a few days. Did you read the rules of the regatta in the letter which must have been handed to you by messenger?";
			link.l1 = "Yes, sir, I did.";
			link.l1.go = "Regata_1";
			RemoveItems(PChar, "letter_open", 1);//уберем письмо
			TakeNationLicence(HOLLAND);//уберем лицензию
			DeleteAttribute(pchar, "questTemp.Regata.ToPortRoyal"); // patch-5
		break;
		
		case "Regata_1":
			dialog.text = "And did you prepare 50000 pesos - your entrance fee, which will contribute to the prize money?";
			if (makeint(Pchar.money) >= 50000)
			{
				link.l1 = "Yes, of course. Please accept my fee.";
				link.l1.go = "Regata_2";
			}
			link.l2 = "I am a bit short of money at the moment. But I will definitely bring it as fast as I can.";
			link.l2.go = "Regata_nomoney";
		break;
		
		case "Regata_2":
			dialog.text = "Very well. If you win - your money will return to your fivefold more. Now, you should now how to not break the rules of the regatta\nDiscuss details with Henry Stevenson, he must be in residence's room. Meet with him, he will explain everything.";
			link.l1 = "Alright. I'll do as you say.";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, -50000);
			pchar.quest.Regata_Guber.win_condition.l1 = "location";
			pchar.quest.Regata_Guber.win_condition.l1.location = "Portroyal_Roomtownhall";
			pchar.quest.Regata_Guber.function = "PrepareToRegataInPortroyal";
			pchar.questTemp.Regata.Begin = "true";
			NextDiag.TempNode = "First time";
		break;
		
		case "Regata_nomoney":
			dialog.text = "Fine, but please don't take it too long, captain. The regatta is about to start soon.";
			link.l1 = "I see. I will try to bring you money before the regatta starts.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Regata_1";
			pchar.questTemp.Regata.nomoney = "true";
		break;
		
		//регата-финал
		case "Regata_Final":
			dialog.text = "And here we have the winner of the regatta! Hello, captain " + GetFullName(pchar) + "! Allow me to congratulate you with this well-deserved success! The winners of the regatta are always popular in English colonies, deservedly popular.";
			link.l1 = "Thank you, sir!";
			link.l1.go = "Regata_complete";
		break;
		
		case "Regata_complete":
			dialog.text = "Now let's skip to the most pleasant part for you - the reward ceremony. The first prize in money is 250000 pesos. Here you go!";
			link.l1 = "Thanks!";
			link.l1.go = "Regata_complete_1";
		break;
		
		case "Regata_complete_1":
			AddMoneyToCharacter(pchar, 250000);
			int iGift;
			string sItem1, sItem2, sItem3, sAdd;
			if (sti(pchar.rank) < 6) iGift = 0;
			if (sti(pchar.rank) >= 6 && sti(pchar.rank) < 13) iGift = 1;
			if (sti(pchar.rank) >= 13 && sti(pchar.rank) < 20) iGift = 2;
			if (sti(pchar.rank) > 20) iGift = 3;
			switch (iGift)
			{
				case 0:
					sItem1 = "blade_10";//корд
					sItem2 = "cirass6";
					sItem3 = "bussol";
					sAdd = "cord, duelist's vest and boussole";
				break;
				
				case 1:
					sItem1 = "blade_15";//маринера
					sItem2 = "cirass2";//рейтарский панцирь
					sItem3 = "bussol";
					sAdd = "marinera, reiter's armour and boussole";
				break;
				
				case 2:
					sItem1 = "blade_17";//бретта
					sItem2 = "cirass7";//карацена
					sItem3 = "bussol";
					sAdd = "bretta, karacena and boussole";
				break;
				
				case 3://
					sItem1 = "blade_20";//мадонна
					sItem2 = "cirass2";//офицерская кираса
					sItem3 = "bussol";
					sAdd = "'Madonna', officer's cuirass and boussole";
				break;
			}
			GiveItem2Character(pchar, sItem1);
			GiveItem2Character(pchar, sItem2);
			GiveItem2Character(pchar, sItem3);
			dialog.text = "Also, you're eligible for a set of valuable prizes: "+sAdd+". Now it's all yours.";
			link.l1 = "I am very glad, sir! Really, I could't have expected it.";
			link.l1.go = "Regata_complete_2";
		break;
		
		case "Regata_complete_2":
			dialog.text = "From the name of all English colonies, I am glad to thank you for participating in the regatta and once again congratulate you with your victory! If you made a bet, it is just the time to see sir Henry Stevenson and receive your winnings, if you hadn't done it already. Best of luck to you, captain!";
			link.l1 = "Thank you for your kind words, sir! In turn, allow me to thank you for providing me with the opportunity to participate in such a grand event. And now, please allow me to say farewell and leave.";
			link.l1.go = "Regata_complete_3";
		break;
		
		case "Regata_complete_3":
			DialogExit();
			NextDiag.CurrentNode = "First time";
		break;
		//<-- регата
	}
}
