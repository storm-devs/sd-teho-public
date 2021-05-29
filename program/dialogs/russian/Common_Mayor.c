// boal 25/04/04 общий диалог мэры
#include "DIALOGS\russian\Rumours\Common_rumours.c"  //homo 25/06/06
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref aData;
	aref Link, NextDiag, arName;

	DeleteAttribute(&Dialog,"Links");

	ref FortChref; // фортовый командер
	ref arItem;
	
	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

    // вызов диалога по городам -->
    NPChar.FileDialog2 = "DIALOGS\" + LanguageGetLanguage() + "\Mayor\" + NPChar.City + "_Mayor.c";
    if (LoadSegment(NPChar.FileDialog2))
	{
        ProcessCommonDialog(NPChar, Link, NextDiag);
		UnloadSegment(NPChar.FileDialog2);
	}
    // вызов диалога по городам <--
    ProcessCommonDialogRumors(NPChar, Link, NextDiag);//homo 25/06/06

    FortChref = GetFortCommander(NPChar.City); // будет или фортовик или сам губернатор

    ref offref;
    int i, cn, iRank, iDay;
    int qty;
    string attrLoc, QuestName, sTemp;
	bool   bOk;
	
    if (CheckNPCQuestDate(npchar, "Card_date"))
	{
		SetNPCQuestDate(npchar, "Card_date");
		npchar.money = 5000 + (rand(10)+1) * makeint(100 * sti(PChar.rank) * (10.0 / MOD_SKILL_ENEMY_RATE));
	}
	// генератор ИДХ по кейсу -->
	attrLoc   = Dialog.CurrentNode;
  	if (findsubstr(attrLoc, "GetPrisonerIdx_" , 0) != -1)
 	{
        i = findsubstr(attrLoc, "_" , 0);
	 	pchar.GenQuest.GetPrisonerIdx = strcut(attrLoc, i+1, strlen(attrLoc)-1); // индех в конце
 	    Dialog.CurrentNode = "sell_prisoner_2";
 	}
 	// генератор ИДХ по кейсу <--
 	
	switch (Dialog.CurrentNode)
	{
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOff");
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
		
		case "First time":
            NextDiag.TempNode = "First time";
			if (LAi_grp_playeralarm > 0)
			{
       			dialog.text = NPCharRepPhrase(pchar, 
					LinkRandPhrase("You dared to show your face at the governor's office?! Very brave of you...", "How did these lazybones let an enemy break into my place? This is beyond me...", "Surely, my guards aren't worth a copper, if some loafer is running around in my residence..."), 
					LinkRandPhrase("What do you need, "+ GetSexPhrase("scoundrel","stinker") +"?! My soldiers have already been set on your trail"+ GetSexPhrase(", filthy pirate","") +"!", +"Murderer, leave my residence at once! Guards!", "I am not afraid of you, "+ GetSexPhrase("scoundrel","rat") +"! Soon you will be hanged in our fort, you won't get far..."));
				link.l1 = NPCharRepPhrase(pchar,
					RandPhraseSimple("Soldiers aren't worth a crap...", "They will never get me."), 
					RandPhraseSimple("Shut up, " + GetWorkTypeOfMan(npchar, "") + ", or I'll rip your mouth!", "That's what I tell you, buddy: be quiet, and you will stay alive..."));
				link.l1.go = "fight";
				break;
			} 
			if (sti(NPChar.nation) == PIRATE)
            {
				if (CheckAttribute(pchar, "GenQuest.CaptainComission") && CheckAttribute(pchar, "GenQuest.CaptainComission.PiratesCity") && NPChar.city == pchar.GenQuest.CaptainComission.PiratesCity)
				{
					dialog.text = "What do you need?";
					link.l1 = "I was going to talk to you about one important affair.";
					link.l1.go = "quests";
					break;
				}
				if (CheckAttribute(pchar, "GenQuest.Marginpassenger") && pchar.GenQuest.Marginpassenger == "cabin" && NPChar.city == "LeFransua")
				{
					dialog.text = "What do you need?";
					link.l1 = "I was going to talk to you about one important affair.";
					link.l1.go = "quests";
					break;
				}
					dialog.text = "There's nothing to talk about, I am busy.";
					link.l1 = "Nevermind.";
					link.l1.go = "Exit";
            }
			if (sti(NPChar.nation) != PIRATE && ChangeCharacterHunterScore(Pchar, NationShortName(sti(NPChar.nation)) + "hunter", 0) > 10)
            {
				iTotalTemp = ChangeCharacterHunterScore(Pchar, NationShortName(sti(NPChar.nation)) + "hunter", 0);
                dialog.text = "Oh, look who's there! It is"+ GetSexPhrase("","") +" " + GetFullName(pchar) + ". You know, we have just recently sent out the bounty hunters to bring you here - and, for your information, it cost us a lot.";
                if (sti(pchar.Money) >= iTotalTemp*6000)
                {
                    link.l1 = "I was just about to settle our disputes.";
				    link.l1.go = "arestFree_1";
                }
				link.l2 = "Uhh... I guess, it is time for me to go.";
				link.l2.go = "arest_1";
				break;
            }
			if (GetNationRelation2MainCharacter(sti(NPChar.nation)) == RELATION_ENEMY && sti(NPChar.nation) != PIRATE)
			{
    			dialog.text = "An enemy in the residence! Alarm!";
				link.l1 = "Aaah, devil!";
				link.l1.go = "fight"; 
				break;
			}			
			//--> Jason, Бремя гасконца
			if (CheckAttribute(pchar, "questTemp.Sharlie.Citcount") && npchar.city == "FortFrance")
			{
    			dialog.text = "What is it that you want, monsieur?";
				link.l1 = "Hello, Your Grace. I've just arrived from Paris. I am looking for Michel de Monper. Perhaps, you could aid me in my search?";
                link.l1.go = "Sharlie";
				npchar.quest.meeting = "1"; // patch-6
				break;
			}
			
			if (CheckAttribute(pchar, "questTemp.Sharlie.Lock") && npchar.city == "FortFrance")
			{
				if (CheckAttribute(pchar, "questTemp.Sharlie.Pardon"))
				{
					dialog.text = "Oh, it's you, sir... I guess I must apologize for treating you so sternly. But you must understand - I must take care of our national security...";
					link.l1 = "Of course, Your Grace. In the end, things eventually settled up.";
					link.l1.go = "Sharlie_2";
				}
				else
				{
					dialog.text = "Did you want anything, Charles?";
					link.l1 = "I have a question to you...";
					link.l1.go = "quests";
					link.l2 = "No, nothing.";
					link.l2.go = "exit";
				}
				npchar.quest.meeting = "1"; // patch-6
				break;
			}			
			//<-- Бремя гасконца
			// Jason НСО
			if (CheckAttribute(pchar, "questTemp.Patria.Governor") && npchar.city == "Marigo" && pchar.model == "Sharle_6")
			{
    			dialog.text = "It's good to see you, sir Governor. How are you doing? Everything is under control on Sint Maarten.";
				link.l1 = "I didn't come here for long. Glad, that everything is fine.";
				link.l1.go = "exit";
				link.l2 = "I was going to talk to you about one important affair.";
				link.l2.go = "quests";   //(перессылка в файл города)
				link.l8 = "Perhaps, you'd like to rest a bit? I propose to play a game.";
				link.l8.go = "Play_Game";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.Patria.GenGovernor") && npchar.nation == FRANCE && pchar.model == "Sharle_6")
			{
    			dialog.text = "Glad to see you, Governor-General! Everything's great in my colony! Rest a bit, I'll order the servants to lay the table...";
				link.l1 = "There's no need to. I didn't come here for long. Glad, that everything is fine.";
				link.l1.go = "exit"; 
				link.l2 = "I was going to talk to you about one important affair.";
				link.l2.go = "quests";   //(перессылка в файл города)
				link.l8 = "Perhaps, you'd like to rest a bit? I propose to play a game.";
				link.l8.go = "Play_Game";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.Patria.GenGovernor") && pchar.model == "Sharle_6")
			{
    			dialog.text = "Who do we have here! Monsieur Governor-General of the French Colonies! What would you like, your Grace? Sit down, I'll order my servants to bring wine and fruits.";
				link.l1 = "Don't worry, I only came here because I was visiting the island, and I couldn't just pass by.";
				link.l1.go = "exit"; 
				link.l2 = "I was going to talk to you about one important affair.";
				link.l2.go = "quests";   //(перессылка в файл города)
				link.l8 = "Perhaps, you'd like to rest a bit? I propose to play a game.";
				link.l8.go = "Play_Game";
				break;
			}		
			//--> Jason, Португалец
			if (CheckAttribute(pchar, "questTemp.Portugal") && pchar.questTemp.Portugal == "MartiniqueGovernor" && npchar.city == "FortFrance")
			{
    			dialog.text = "Oh, here you are, captain! I must say, you took your time.";
				link.l1 = "I arrived at the earliest opportunity, Your Excellency. I was told there was a pressing business, can I do you a favor, perhaps?";
				link.l1.go = "Portugal"; 
				break;
			}			
			//<-- Португалец
            
            if (npchar.quest.meeting == "0")
			{
				dialog.text = "I've heard that you were very persistent at requesting an audience. My name is " + GetFullName(npchar) +
                              ". I am the governor of the town of "+ GetCityName(NPChar.city) + ", subject of " + NationKingsName(npchar)+
                              ". And now, please, deign to tell me the goal of your visit, " + GetAddress_Form(NPChar) + ".";
				link.l1 = "My name is " + GetFullName(pchar) + ".";
				link.l1.go = "node_1";
				npchar.quest.meeting = "1";
			}
			else
			{
               	//ОСАДЫ homo
				if (CheckAttribute(Colonies[FindColony(npchar.City)],"Siege"))
                {

                    makearef(aData, NullCharacter.Siege);
                    
                    if (CheckAttribute(aData, "HelpColony") && sti(aData.HelpColony) == true )
                    {
                        dialog.text = "We have already discussed everything, haven't we?";
                        link.l1 = "Correct. I do not delay you any further.";
                        link.l1.go = "exit";

                    }
                    else
                    {
                        dialog.text = "I am sorry to upset you, but I have no time to speak with you at the moment. As you should know, our colony was attacked by "+NationNamePeople(sti(aData.nation))+". I will need to set up the town's defenses.";
                        link.l1 = "So I just wanted to offer my assistance in the defense of the fort.";
                        link.l1.go = "siege_task";
                        link.l2 = "Then I will not delay you any further.";
            			link.l2.go = "exit";
                    }
                }
                else
                {//->
                    makearef(aData, NullCharacter.Siege);
                    if (CheckAttribute(aData, "PlayerHelpMayor") && sti(aData.PlayerHelpMayor) == true
                    && CheckAttribute(aData, "HelpColony") && sti(aData.HelpColony) == true )
                    {
                        AddMoneyToCharacter(Pchar,(sti(aData.iSquadronPower)*1500));
                        ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 20);
                        ChangeCharacterComplexReputation(pchar,"nobility", 10);
                        AddCharacterExpToSkill(GetMainCharacter(), "Leadership", 80);
                        AddCharacterExpToSkill(GetMainCharacter(), "Sailing", 100);
                        AddCharacterExpToSkill(GetMainCharacter(), "Accuracy", 100);
                        AddCharacterExpToSkill(GetMainCharacter(), "Cannons", 100);
                        //--> слухи
                        SiegeRumour("They say that you had helped us to repel the "+NationNameSK(sti(aData.nation))+" squadron and to defend our colony! We are so grateful to you, "+ GetAddress_Form(NPChar)+".", aData.Colony, sti(aData.conation), -1, 15, 3);
			            //<-- слухи
                        DeleteAttribute(aData, "PlayerHelpMayor");
                        DeleteAttribute(aData, "HelpColony");
                        dialog.text = "Oh, that's you, "+GetAddress_Form(NPChar)+" "+GetFullName(pchar)+", I'm glad to see you. Good news for our colony - we managed to repel the "+NationNameSK(sti(aData.nation))+" invaders. You did your part in this as well, and here is your reward - "+(sti(aData.iSquadronPower)*1500)+" pesos. Here you go.";
                        link.l1 = "Thank you, " + GetAddress_FormToNPC(NPChar) + ", pleasure to do business with you!";
                        link.l1.go = "exit";
                    }
                    else
                    {
   						//--> дача квеста найти кольцо в борделе
						if (rand(4) == 4 && pchar.questTemp.different == "free" && GetNpcQuestPastDayWOInit(npchar, "questTakeRing") > 365 && sti(pchar.questTemp.HorseQty) > 10)
						{// Addon-2016 Jason
							if (npchar.city == "Bridgetown" || npchar.city == "Charles" || npchar.city == "FortFrance" || npchar.city == "Marigo" || npchar.city == "Panama" || npchar.city == "PortRoyal" || npchar.city == "SantoDomingo" || npchar.city == "Tortuga")
							{
        						dialog.text = "Listen, I have task for you, but it's of somewhat unusual sort.";
								link.l1 = "I am all ears.";
        						link.l1.go = "TakeRing_1";
								SaveCurrentNpcQuestDateParam(npchar, "questTakeRing");
								break;
							}
						}
						//<-- дача квеста найти кольцо в борделе    				
						dialog.text = RandPhraseSimple("Oh, that's you again? What is it that you want from me this time?",
                                      "Once again you are distracting me from the affairs of my city? What do you want, " +GetAddress_Form(NPChar)+"?");
        				link.l1 = "I want to talk to you about work in the name of the Crown of " + NationNameGenitive(sti(NPChar.nation))+".";
							link.l1.go = "work";
						
						// Warship Генер "Пираты на необитайке" - сдаем пиратов властям
						if(CheckAttribute(PChar, "Quest.PiratesOnUninhabited_OnShore") || CheckAttribute(PChar, "Quest.PiratesOnUninhabited_ShipSink"))
						{
							link.l11 = XI_ConvertString(PChar.GenQuest.PiratesOnUninhabited.StartShore + "Dat") + " I met pirates. All " + PChar.GenQuest.PiratesOnUninhabited.PiratesCount + " are on board at the moment. I want to turn them to the authorities.";
							link.l11.go = "PiratesOnUninhabited_1";
						}
						
        				link.l2 = "I was going to talk to you about one important affair.";
						if(CheckAttribute(pchar,"questTemp.ReasonToFast") && !CheckAttribute(pchar,"questTemp.ReasonToFast.SpeakOther") && !CheckAttribute(pchar, "questTemp.ReasonToFast.cantSpeakOther") && (pchar.questTemp.ReasonToFast.city == NPChar.city))
						{
							link.l2.go = "ReasonToFast_Mayor1";
						}
						else
						{
							link.l2.go = "quests";   //(перессылка в файл города)
						}	
						if(CheckAttribute(pchar,"GenQuest.CaptainComission") && (pchar.GenQuest.CaptainComission.variant == "A2") && (pchar.GenQuest.CaptainComission.City == NPChar.city))
						{
							if(pchar.GenQuest.CaptainComission == "Begin_1" && !CheckAttribute(pchar,"GenQuest.CaptainComission.SpeakMayor")) 
							{
								link.l12 = "There is a captain of the patrol " + GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name") + "Acc")) + " named " + pchar.GenQuest.CaptainComission.Name + ", how can I see him?";
								link.l12.go = "CapComission_Mayor1";
							}	
							if(CheckAttribute(pchar,"GenQuest.CaptainComission.PrisonFree"))
							{
								link.l12 = "Former captain of the patrol " + GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name") + "Acc")) + " " + pchar.GenQuest.CaptainComission.Name + " agreed to reveal his cache to the authorities.";
								link.l12.go = "CapComission_Mayor9";
							}
							if(pchar.GenQuest.CaptainComission == "GetGoodsSuccess")
							{
								link.l12 = "Former captain of the patrol " + GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name") + "Acc")) + " " + pchar.GenQuest.CaptainComission.Name + " revealed his cache to me.";
								link.l12.go = "CapComission_Mayor13";
							}
						}
						if(CheckAttribute(pchar,"GenQuest.ShipWreck") && pchar.GenQuest.ShipWreck == "SailorsOnShore" && GetQuestPastDayParam("GenQuest.ShipWreck") < 25  && sti(npchar.nation) == sti(pchar.GenQuest.ShipWreck.Nation))
						{
							if(!CheckAttribute(pchar,"GenQuest.ShipWreck.SpeakMayor"))
							{
								iDay = GetQuestPastDayParam("GenQuest.ShipWreck");
								if(CheckAttribute(pchar, "GenQuest.ShipWreck.Mutiny"))
								{
									link.l13 = UpperFirst(XI_ConvertString(pchar.GenQuest.ShipWreck.Shore + "Dat")) + " I met captain " + pchar.GenQuest.ShipWreck.Name + " and his sailors who were put ashore by pirate " + pchar.GenQuest.ShipWreck.BadName + ". " +
										"Unfortunately, I already had too many men on my ship and therefore I could not take them on board. But I left them with provisions and weapons. If the expedition ship don't pick them up within " + (30 - iDay) + " days, then I don't know it'll find them still alive or not.";
									link.l13.go = "ShipWreck1";
								}
								else
								{
									link.l13 = UpperFirst(XI_ConvertString(pchar.GenQuest.ShipWreck.Shore + "Dat")) + " I met sailors from the wrecked ship '" + pchar.GenQuest.ShipWreck.ShipTypeName + "' with their captain. " + 
										"Unfortunately, I already had too many men on my ship therefore I could not take them on board. But I left them with provisions and weapons. If the expedition ship don't pick them up within " + (30 - iDay) + " days, then I don't know it'll find them still alive or not.";
									link.l13.go = "ShipWreck1";							
								}
							}	
						}
        				if (GetPrisonerQty() > 0)
        				{
                            link.l3 = "I need to turn the captive captain to the authorities.";
        				    link.l3.go = "sell_prisoner";
        				}
        				if (npchar.Default  == npchar.location) // если не в тюрьме
        				{
        					if (CheckAttribute(pchar, "GenQuest.LoanChest.TakeChest") && sti(pchar.GenQuest.LoanChest.TargetIdx) == sti(NPChar.index))
        					{
        						link.l4 = "I need to sort out several financial issues with you.";
        						link.l4.go = "LoanForAll";//(перессылка в кредитный генератор)
        					}
        				}
						//-->> сдача найденного в борделе кольца
						if (CheckCharacterItem(pchar, "MayorsRing"))
						{
							if (pchar.questTemp.different.TakeMayorsRing == "toBrothel")
							{
        						link.l5 = "I managed to find your ring. Here you go.";
        						link.l5.go = "TakeRing_S1";
							}
							else
							{
        						link.l5 = "I have your wedding ring. It turns out that you've given it as present to one of the whores in the brothel.";
        						link.l5.go = "TakeRing_S3";
							}
						}
						//<<-- сдача найденного в борделе кольца 
						
						//--> Jason, генер почтового курьера 2 уровня
						if (CheckAttribute(PChar, "questTemp.WPU.Postcureer.LevelUp"))
						{
							if (pchar.questTemp.WPU.Postcureer.TargetPortmanID == npchar.id)
							{
							link.l14 = "I have delivered you a message from the town of "+XI_ConvertString("Colony"+pchar.questTemp.WPU.Postcureer.StartCity+"Gen")+".";
							link.l14.go = "Postcureer_LevelUp_ForAll";
							}
						}
						//<-- генер почтового курьера 2 уровня
						
						// Warship, 16.05.11. Квест "Правосудие на продажу" -->
						if(CheckAttribute(PChar, "GenQuest.JusticeOnSale.MayorWait") && CheckAttribute(PChar, "GenQuest.JusticeOnSale.CityId") && NPChar.location == PChar.GenQuest.JusticeOnSale.CityId + "_townhall")
						{
							link.l15 = UpperFirst(GetAddress_FormToNPC(NPChar)) + ", I have located a gang of smugglers, whose ringleader had been recently caught by the guards. Now they are planning to arrange his escape. Their ship '" + PChar.GenQuest.JusticeOnSale.ShipName + "' is moored at " + XI_ConvertString(PChar.GenQuest.JusticeOnSale.ShoreId + "Dat") + ".";
							link.l15.go = "JusticeOnSale_1";
						}
						
						if(CheckAttribute(PChar, "GenQuest.JusticeOnSale.ShipSink") && CheckAttribute(PChar, "GenQuest.JusticeOnSale.CityId") && NPChar.location == PChar.GenQuest.JusticeOnSale.CityId + "_townhall")
						{
							link.l15 = UpperFirst(GetAddress_FormToNPC(NPChar)) + ", the gang of smugglers was eliminated!";
							link.l15.go = "JusticeOnSale_7";
						}
						// <--Правосудие на продажу
						//Jason --> Регата
						if (CheckAttribute(pchar, "questTemp.Regata.ToPortRoyal") && NPChar.location == "Portroyal_townhall")
						{
							link.l16 = "I arrived at the invitation to participate in the regatta. Here's my invitation.";
							link.l16.go = "Regata";
						}
        				//link.l7 = "I would like to know where is the Governor-General " + NationNameGenitive(sti(NPChar.nation)) + ".";
        				link.l8 = "Perhaps, you want to take a break? Maybe we can spend some time on a game?";
        			    link.l8.go = "Play_Game";
        				link.l10 = "Please excuse me, but duty calls.";
        				link.l10.go = "exit";
                    }
                }//<-
			}
		break;
		
		// Warship Генер "Пираты на необитайке"
		case "PiratesOnUninhabited_1":
			offref = CharacterFromID("PirateOnUninhabited_0");
			qty = makeint(sti(PChar.GenQuest.PiratesOnUninhabited.PiratesCount) * (sti(offref.rank) * (800 + GetCharacterSPECIALSimple(NPChar, SPECIAL_L) * 100) + GetCharacterSkillToOld(offref, "Leadership") * 500 + GetCharacterSkillToOld(PChar, "commerce") * 500) / 20);
			
			PChar.GenQuest.PiratesOnUninhabited.MoneyForPirates = qty;
			
			dialog.text = "This is a very commendable decision. This is how we must fight this plague - with our concerted efforts. I will immediately dispatch a convoy to pick them up. Rest assured that they will be hanging on the gallows in less than a week. Oh, and a reward is due, of course - " + FindRussianMoneyString(qty) + ".";
			link.l1 = "Thank you, Your Grace. Always a pleasure. ";
			link.l1.go = "PiratesOnUninhabited_2";
			link.l2 = "No. That won't do.";
			link.l2.go = "exit";
		break;
		
		case "PiratesOnUninhabited_2":
			offref = CharacterFromID("PirateOnUninhabited_0");
			
			AddMoneyToCharacter(PChar, sti(PChar.GenQuest.PiratesOnUninhabited.MoneyForPirates));
			
			RemovePassenger(PChar, offref);
			RemoveCharacterCrew(PChar, sti(PChar.GenQuest.PiratesOnUninhabited.PiratesCount) - 1);
			
			sTemp = "PiratesOnUninhabited" + PChar.GenQuest.PiratesOnUninhabited.StartShore;
			AddQuestRecordEx(sTemp, "PiratesOnUninhabited", "12");
			AddQuestUserData(sTemp, "sSex", GetSexPhrase("","а"));
			AddQuestUserData(sTemp, "mayorName", GetFullName(NPChar));
			CloseQuestHeader(sTemp);
			
			PChar.Quest.PiratesOnUninhabited_OnShore.over = "yes";
			PChar.Quest.PiratesOnUninhabited_OnMayak.over = "yes";
			
			if(CheckAttribute(PChar, "Quest.PiratesOnUninhabited_ShipSink"))
			{
				PChar.Quest.PiratesOnUninhabited_ShipSink.over = "yes";
				
				PChar.GenQuest.PiratesOnUninhabited.ClearShip = true;
				Map_ReleaseQuestEncounter("PiratesOnUninhabited_BadPirate"); // Убираем с глобалки
			}
			
			DeleteAttribute(PChar, "GenQuest.PiratesOnUninhabited");
			
			DialogExit();
		break;
		
		// ------------------------- Повод для спешки -----------------------------
		case "ReasonToFast_Mayor1":
			dialog.text = "I am all ears, captain.";
			link.l1 = "I wanted to tell you about a criminal collusion between an officer of your garrison and pirates... (explains the matter).";
			if(sti(pchar.reputation.nobility) < 41)
			{
				link.l1.go = "ReasonToFast_BMayor";			
			}
			else
			{
				link.l1.go = "ReasonToFast_GMayor";	
			}
			pchar.questTemp.ReasonToFast.SpeakOther = true;			
		break;
		
		case "ReasonToFast_GMayor":
			if(pchar.questTemp.ReasonToFast == "PatrolSuccess_1") 
			{ 
				// вилка_А
				dialog.text = "Thank you, "+ GetSexPhrase("mister","miss") +"! I will immediately order to arrest the scum.\nYou must had spent a lot of money, alas, our treasury is empty...";
				link.l1 = "Your Lightness! I did it not for the sake of money...";
				link.l1.go = "ReasonToFast_GMayor_11";				
				if(pchar.questTemp.ReasonToFast.chain == "A0") ReasonToFast_RemoveVictim();
				if(pchar.questTemp.ReasonToFast.chain == "A1") pchar.quest.ReasonToFast_ClearLakey.over = "yes";
			}			
			if(pchar.questTemp.ReasonToFast == "PatrolSuccess_2") 
			{ 
				// получена карта
				dialog.text = "I thank you! I immediately will give order to detain a scoundrel.\nOnly think! We wanted to reward him with nominal weapon for blameless service. As well, that all cleared up, and such embarrassment didn't go out!";
				link.l2 = "Always a pleasure to serve justice...";
				link.l2.go = "ReasonToFast_GMayor_21";			
			}
			if(pchar.questTemp.ReasonToFast == "PatrolDied") 
			{ 
				// патруль перебит
				dialog.text = "Mis"+ GetSexPhrase("ter","s") +"! We had been suspecting that officer and his scum for quite some time, but I think that you made a rash move, having dealt with them without witnesses.";
				link.l3 = "Your Lightness! But I was forced to protect my life...";
				link.l3.go = "ReasonToFast_GMayor_31";
				pchar.questTemp.ReasonToFast.speakAfterPatrolDied = true;	
				pchar.quest.ReasonToFast_SpeakMayor.over = "yes";
			}			
		break;
		
		case "ReasonToFast_BMayor":
			if(pchar.questTemp.ReasonToFast == "PatrolSuccess_1") 
			{ 				
				dialog.text = "Captain, do you realize what you've done?!! We've been attempting to set up this trap for over a month! And now, just for your entertainment, you've wrecked the meeting of our patrol with messenger " + GetName( NAMETYPE_MAIN, pchar.questTemp.ReasonToFast.p3, NAME_GEN) + " and now you're coming here to boast?!! Perhaps, you can tell me now, how should I explain all expenses and costs of this operation?!";
				link.l1 = "Your Grace! You're just refusing to see the point...";
				link.l1.go = "ReasonToFast_BMayor_1";
				pchar.questTemp.ReasonToFast = "speakSuccess_chain_A";				
				if(pchar.questTemp.ReasonToFast.chain == "A0") ReasonToFast_RemoveVictim();
				if(pchar.questTemp.ReasonToFast.chain == "A1") pchar.quest.ReasonToFast_ClearLakey.over = "yes";
			}
			if(pchar.questTemp.ReasonToFast == "PatrolSuccess_2") 
			{ 
				// получена карта
				dialog.text = "Let me see this map\nYou must be kidding me? This rubbish piece of paper is a proof?";
				link.l2 = "Your Grace! You're just refusing to see the point...";
				link.l2.go = "ReasonToFast_BMayor_1";
				TakeItemFromCharacter(pchar, "mapQuest");				
				pchar.questTemp.ReasonToFast = "speakSuccess_chain_B";
			}
			if(pchar.questTemp.ReasonToFast == "PatrolDied") 
			{ 
				// патруль перебит
				dialog.text = "Now that's an interesting justification of the destruction of the entire patrolling party. Well, at least by coming here you spared us the need to look for the murderer.";
				link.l3 = "Your Grace! You're just refusing to see the point...";
				link.l3.go = "ReasonToFast_BMayor_1";			
				pchar.questTemp.ReasonToFast = "speakSuccess_chain_A";
				pchar.quest.ReasonToFast_SpeakMayor.over = "yes";
			}		
		break;
		
		case "ReasonToFast_GMayor_11":
			dialog.text = "Nonetheless I think that your efforts should still be rewarded. Here - take this map; it was found in the belongings of one pirate, who had recently went to the gallows. God willing, perhaps you will actually find that treasure, although I find it quite unlikely...";
			link.l1 = "Thank you, that's very generous of you!";
			link.l1.go = "exit";
			AddQuestRecord("ReasonToFast", "15");
			ChangeCharacterComplexReputation(pchar,"nobility", 1); 
			GiveItem2Character(pchar, "mapQuest"); 
			arItem = ItemsFromID("mapQuest");
			ReasonToFast_GenerateTreasureMap(arItem);
			pchar.questTemp.ReasonToFast.state = "chain_A"; // вилка_А, наводки не генерим
			pchar.questTemp.ReasonToFast = "GetMap";			
			ReasonToFast_SetHunterCoastal();
		break;
		
		case "ReasonToFast_GMayor_21":
			dialog.text = "Your zeal is commendable. Please accept this blade as a reward - it's the least I can do for you. Oh, and you can keep this map for yourself. I am certain that there's a lot of such fakes on the Archipelago.";
			link.l1 = "Thank you, that's very generous of you!";
			link.l1.go = "exit";
			AddQuestRecord("ReasonToFast", "14");
			ChangeCharacterComplexReputation(pchar,"nobility", 1); 
			GiveItem2Character(pchar, pchar.questTemp.ReasonToFast.p6);
			pchar.questTemp.ReasonToFast.state = "chain_B"; // была получена карта
			pchar.questTemp.ReasonToFast = "GetMap";			
			ReasonToFast_SetHunterCoastal();
		break;
		case "ReasonToFast_GMayor_31":
			dialog.text = "Might be, might be... Well, let's just say that this deal was decided by divine justice and by our Lord's will.";
			link.l1 = "Thank you, that's very generous of you!";
			link.l1.go = "exit";
			ChangeCharacterComplexReputation(pchar,"nobility", 1); 
			AddQuestRecord("ReasonToFast", "16");
			CloseQuestHeader("ReasonToFast");
			DeleteAttribute(pchar,"ReasonToFast");
		break;
		
		case "ReasonToFast_BMayor_1":
			dialog.text = "Don't dare lecturing me! To me, it is obvious that you are in a collaboration with these scoundrels! Guards, seize this 'well-wisher'!";
			link.l1 = "Go fuck yourself!";
			link.l1.go = "fight";
		
			pchar.quest.ReasonToFast_ExitFromTown.win_condition.l1			= "EnterToSea";           	
            pchar.quest.ReasonToFast_ExitFromTown.function    				= "ReasonToFast_ExitFromTownFight";						
			pchar.questTemp.ReasonToFast.canSpeakSailor = true;
			pchar.TownEscape = true;
			Flag_PIRATE();
		break;
		
		// ------------------------- Повод для спешки -----------------------------
		
		// --------------------------Операция 'Галеон'-----------------------------
		case "CapComission_Mayor1":
			dialog.text = "Right now this is not possible. He is under arrest, waiting for the trial.";
			link.l1 = "Is he? And what is he suspected of?";			
			link.l1.go = "CapComission_Mayor2";
		break;
		
		case "CapComission_Mayor2":
			dialog.text = "Unfortunately, it's not a suspicion, but rather a proven fact. We have information that he was raiding vessels under the guise of patrolling. He confiscated goods from merchants and then sold them on black market. To think that he was once considered one of the best captains in the patrol squadron...";
			link.l1 = "And who provided you with evidence?";
			link.l1.go = "CapComission_Mayor3";				
		break;
		
		case "CapComission_Mayor3":
			dialog.text = "One of his victims wrote a report, where he described the incident in detail, including the date, the name of the raided ship and the amounts of goods confiscated. " +
				"Trust me, the numbers are quite impressive. On that day patrol " + GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name"))) + " captain " + pchar.GenQuest.CaptainComission.Name + " was indeed on duty. The captain described this incident as an encounter with a pirate ship in his report, but didn't mention any cargo at all.";
			link.l1 = "But was there any cargo at all?";
			link.l1.go = "CapComission_Mayor4";
			pchar.GenQuest.CaptainComission.SpeakMayor = true;
		break;
		
		case "CapComission_Mayor4":
			dialog.text = "There's no doubt about it. The aggrieved party is a very well-known person, and he would not debase himself with petty slander. Right now patrolling parties are looking for captain's cache. " +
				"Once it is found, the captain appeared in court\nIf you render us assistance in this matter, the authorities of the city in my face will be very grateful to you.";
			link.l1 = "Probably not. I don't know the local area well enough to be searching for a cache. Excuse me, I have to go.";
			link.l1.go = "CapComission_Mayor5";
			link.l2 = "Perhaps, I am ready to agree. How many time do I have?";
			link.l2.go = "CapComission_Mayor6";	
		break;
		
		case "CapComission_Mayor5":
			AddQuestRecord("CaptainComission2", "49");
			AddQuestUserData("CaptainComission2", "sShipType", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name") + "Acc")));
			AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);
			ChangeCharacterComplexReputation(pchar,"nobility", -2);
			pchar.GenQuest.CaptainComission = "MayorTalkBad";
			CaptainComission_GenerateCaptainInPrison();
			DialogExit();
		break;
		
		case "CapComission_Mayor6":
			dialog.text = "I believe that in two days the patrols will locate the cache without your aid, so you should hurry up."; 
			link.l1 = "Alright, I am on it. But I will need to pay a visit to captain " + pchar.GenQuest.CaptainComission.Name + ". Can this be arranged?";
			link.l1.go = "CapComission_Mayor7";
		break;
		
		case "CapComission_Mayor7":
			dialog.text = "Sure, no problem. I will tell the fort's commandant about your visit.";
			link.l1 = "Thanks a lot. Now, please excuse me.";
			link.l1.go = "CapComission_Mayor8";
		break;
		
		case "CapComission_Mayor8":
			AddQuestRecord("CaptainComission2", "50");
			AddQuestUserData("CaptainComission2", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission2", "sSex1", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission2", "sShipType", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name") + "Acc")));
			AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);			
			AddQuestUserData("CaptainComission2", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Gen"));
			OfficersReaction("good");
			pchar.GenQuest.CaptainComission.MayorTalkGood = true;
			pchar.GenQuest.CaptainComission = "MayorTalkGood";
			pchar.quest.CaptainComission_TimeIsOver.over = "yes";
			SetFunctionTimerConditionParam("CaptainComission_GetSecretTimeIsOut", 0, 0, 2, MakeInt(24 - GetHour()), false);
			CaptainComission_GenerateCaptainInPrison();
			DialogExit();
		break;
		
		case "CapComission_Mayor9":
			dialog.text = "Excellent! And where are we going to look for his treasure?";
			link.l1 = "I have no idea yet. He didn't point me to the exact location.";
			link.l1.go = "CapComission_Mayor10";
		break;
		
		case "CapComission_Mayor10":
			dialog.text = "Hmm, what a coincidence! You know, he 'didn't point' me to the exact location, either...";
			link.l1 = "But I am working on it.";
			link.l1.go = "CapComission_Mayor11";
		break;
		
		case "CapComission_Mayor11":
			dialog.text = "Not anymore\nGuards! Take the prisoner back to the chambers\nYou are free to go, " + GetFullName(pchar) + ".";
			link.l1 = "But mister governor...";
			link.l1.go = "CapComission_Mayor12";
		break;
		
		case "CapComission_Mayor12":
			sld = CharacterFromID("CapComission_1");
			sld.lifeDay = 0;
			LAi_group_MoveCharacter(sld, "EnemyFight");
			LAi_SetActorType(sld);
            LAi_ActorRunToLocation(sld, "reload", "reload1_back", "none", "", "", "", -1);			
			pchar.quest.CapComission_DeletePrisonGroup.win_condition.l1 = "ExitFromLocation";
            pchar.quest.CapComission_DeletePrisonGroup.win_condition.l1.location = pchar.location;
            pchar.quest.CapComission_DeletePrisonGroup.win_condition = "CaptainComission_DeletePrisonGroup";									
			ChangeOfficersLoyality("bad_all", 1);
			ChangeCharacterComplexReputation(pchar,"nobility", -4);			
			AddQuestRecord("CaptainComission2", "23");
			AddQuestUserData("CaptainComission2", "sSex", GetSexPhrase("",""));
			CloseQuestHeader("CaptainComission2");
			DeleteAttribute(pchar, "GenQuest.CaptainComission");
			DialogExit();
		break;
		
		case "CapComission_Mayor13":
			pchar.quest.CaptainComission_SpeakMayorGoods.over = "yes";
			dialog.text = "Excellent! And where are we going to look for his treasure?";
			link.l1 = "In the " + RandPhraseSimple(RandPhraseSimple("northern","western"),RandPhraseSimple("eastern","southern")) + " end of " + XI_ConvertString(pchar.GenQuest.CaptainComission.ConvoyShore + "Gen") + " at the foot of the cliff there is a large niche, the entrance to which is littered with stones. This is a hiding-place.";
			link.l1.go = "CapComission_Mayor14";
		break;
		
		case "CapComission_Mayor14":
			dialog.text = "Excellent job! And where is " + pchar.GenQuest.CaptainComission.Name + " himself? I was told that you took him from the fort's dungeons.";
			link.l1 = "Unfortunately, he perished in a skirmish with the smugglers.";
			link.l1.go = "CapComission_Mayor15";
		break;
		
		case "CapComission_Mayor15":
			dialog.text = "This is bad... This is very bad, "+ GetSexPhrase("mister","miss") +" " + GetFullName(pchar) + ". I was going to execute him in public, for other officers' edification. " + 
				"Anyway, he would've not avoided the gallows\nSo, as you technically violated the law, illegally releasing a prisoner, but still did not save him, I can not fix this in the report. Therefore, you do not get rewards ... But I would like to personally thank you from myself. Accept my gift - a very useful thing for a fighting captain. ";
			link.l1 = "Thank you. Always glad to serve you.";	
			link.l1.go = "CapComission_Mayor16";
		break;
		
		case "CapComission_Mayor16":
			AddQuestRecord("CaptainComission2", "30");
			AddQuestUserData("CaptainComission2", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Gen"));
			CloseQuestHeader("CaptainComission2");
			GiveItem2Character(pchar, pchar.GenQuest.CaptainComission.Prize);
			ChangeCharacterComplexReputation(pchar,"nobility", 4);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 10);
			OfficersReaction("good");
			DeleteAttribute(pchar,"GenQuest.CaptainComission.MayorTalkGood");
			DeleteAttribute(pchar, "GenQuest.CaptainComission");
			DialogExit();
		break;
		// --------------------------Операция 'Галеон'-----------------------------
		
		// -------------------------- Генератор "Кораблекрушенцы" ------------
		case "ShipWreck1":
			if(iDay > 15)
			{
				dialog.text = RandPhraseSimple("How do you conceive it? It takes at least fifteen days to get to that place even when sailing free!","Captain " + GetFullName(pchar) + ", your irresponsibility astounds me! Why hadn't you told me about it earlier?");
				link.l1 = "Well, I don't even know what to say...";
				link.l1.go = "ShipWreck2";
			}
			else
			{
				dialog.text = "This is great news! We already lost hope to see " + pchar.GenQuest.ShipWreck.Name + "  alive again. I will dispatch a rescue party immediately. Oh, and please, accept this reward for your efficiency and participation in their rescue.";
				link.l1 = "Thank you, Your Grace. I am glad that he was able to help you and your people. I'm sure that the expedition will get there in time.";
				link.l1.go = "ShipWreck3";	
			}
			pchar.GenQuest.ShipWreck.SpeakMayor = true;
			pchar.quest.ShipWreck_MeetInShore.over = "yes";
		break;
		
		case "ShipWreck2":
			dialog.text = "What is there to say? Go and study Naval service regulations! Anyway, I will do my best to save these people.";
			link.l1 = "Your Grace, but I left them with enough provisions. You have time, I assure you ...";
			link.l1.go = "ShipWreck4";
		break;
		
		case "ShipWreck3":
			addMoneyToCharacter(pchar, sti(pchar.rank) * 300 + 3000 + rand(3000));
			ChangeCharacterComplexReputation(pchar,"nobility", 2);
			AddQuestRecord("ShipWrecked", "14");
			AddQuestUserData("ShipWrecked", "sSex", GetSexPhrase("",""));
			AddQuestUserData("ShipWrecked", "sCity", XI_ConvertString(NPChar.city + "Gen"));
			AddQuestUserData("ShipWrecked", "ShoreName", XI_ConvertString(pchar.GenQuest.ShipWreck.Shore + "Dat"));
			CloseQuestHeader("ShipWrecked");
			DeleteAttribute(pchar, "GenQuest.ShipWreck.SpeakMayor");		
			DialogExit();
			AddDialogExitQuest("ShipWreck_RemoveSailorsFromShore");
		break;		
		
		case "ShipWreck4":
			ChangeCharacterComplexReputation(pchar,"nobility", -5);
			AddQuestRecord("ShipWrecked", "13");
			AddQuestUserData("ShipWrecked", "sSex", GetSexPhrase("",""));
			AddQuestUserData("ShipWrecked", "sCity", XI_ConvertString(NPChar.city + "Gen"));
			AddQuestUserData("ShipWrecked", "ShoreName", XI_ConvertString(pchar.GenQuest.ShipWreck.Shore + "Dat"));
			CloseQuestHeader("ShipWrecked");
			DeleteAttribute(pchar, "GenQuest.ShipWreck.SpeakMayor");		
			DialogExit();
			AddDialogExitQuest("ShipWreck_RemoveSailorsFromShore");
		break;
		// -------------------------- Генератор "Кораблекрушенцы" ------------
		
		// ---------------------- найти кольцо в борделе ----------------------------
		case "TakeRing_1":
			dialog.text = "I am aware that you, how to say it... "+ GetSexPhrase("are a frequenter of brothels","use to visit brothels from time to time") +". And therefore decided to address you for the help\n"+
				"You know, ashamed to admit it, but I was there recently...";
			link.l1 = "And what's wrong with it? Passion and stuff, you know...";
			link.l1.go = "TakeRing_2";
		break;
		case "TakeRing_2":
			dialog.text = "Oh, no, I am not preaching, no. The thing is that I had drunk too much on one occasion and lost my wedding ring...";
			link.l1 = "Oh, now that's a problem. I am sorry.";
			link.l1.go = "TakeRing_3";
		break;
		case "TakeRing_3":
			dialog.text = "Hm. I don't need anyone to be sorry for me. I need my ring back. If you manage to seek it out before midnight, I will be very generous. If you fail, I am done for.";
			link.l1 = "I see... And where exactly might you have lost it? Do you remember anything in particular?";
			link.l1.go = "TakeRing_4";
		break;
		case "TakeRing_4":
			dialog.text = "Unfortunately, no. Not a thing.";
			link.l1 = "I see. Well, let's look for it, then.";
			link.l1.go = "TakeRing_5";
			link.l2 = "You know, " + GetAddress_FormToNPC(NPChar) + ", I think I'll pass on this one. Please, excuse me...";
			link.l2.go = "TakeRing_6";
		break;	
		case "TakeRing_5":
			dialog.text = "Excellent! But remember - you must find it before midnight.";
			link.l1 = "I remember. Wait for my return with the news.";
			link.l1.go = "exit";
			pchar.questTemp.different = "TakeMayorsRing";
			pchar.questTemp.different.TakeMayorsRing = "toBrothel";
			pchar.questTemp.different.TakeMayorsRing.Id = GetFullName(npchar);
			pchar.questTemp.different.TakeMayorsRing.city = npchar.city;	
			pchar.questTemp.different.TakeMayorsRing.price = sti(pchar.rank)*100+1000;
			sld = ItemsFromID("MayorsRing");
			sld.CityName = XI_ConvertString("Colony" + npchar.city + "Gen");
			//ложим кольцо в итем
			if (rand(3) != 2)
			{				
				switch (rand(2))
				{
					case 0: sTemp = "_Brothel_room";  break;
					case 1: sTemp = "_Brothel";  break;
					case 2: sTemp = "_SecBrRoom";  break;
				}
				sld.shown = true;
				sld.startLocation = pchar.questTemp.different.TakeMayorsRing.city + sTemp;
				sld.startLocator = "item" + (rand(4)+1);
				pchar.questTemp.different.TakeMayorsRing.item = true; //флаг кольцо валяется в итемах
				Log_QuestInfo("The ring is in location " + sld.startLocation + ", in locator " + sld.startLocator);
			}
			SetTimerFunction("TakeMayorsRing_null", 0, 0, 1); //освобождаем разрешалку на миниквесты 
			ReOpenQuestHeader("SeekMayorsRing");
			AddQuestRecord("SeekMayorsRing", "1");
			AddQuestUserData("SeekMayorsRing", "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData("SeekMayorsRing", "sName", pchar.questTemp.different.TakeMayorsRing.Id);
		break;	
		case "TakeRing_6":
			dialog.text = "Oh? Well, that was really unexpected... Well, best of luck to you, then, captain.";
			link.l1 = "Farewell.";
			link.l1.go = "exit";
			ChangeCharacterComplexReputation(pchar,"nobility", -2);
		break;

		case "TakeRing_S1":
			dialog.text = "Excellent! It's my ring indeed! You've saved my life!";
			link.l1 = "Oh, but really...";
			link.l1.go = "TakeRing_S2";
			TakeItemFromCharacter(pchar, "MayorsRing");
		break;
		case "TakeRing_S2":
			dialog.text = "Here's your money for a job, well done! I am very grateful to you!";
			link.l1 = "Hmm... I'll keep that in mind...";
			link.l1.go = "exit";
			ChangeCharacterComplexReputation(pchar,"nobility", 5);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 10);
			AddCharacterExpToSkill(pchar, "Leadership", 20);
			AddCharacterExpToSkill(pchar, "Fortune", 20);
			AddMoneyToCharacter(pchar, sti(pchar.questTemp.different.TakeMayorsRing.price));
			pchar.questTemp.different = "free";
			pchar.quest.TakeMayorsRing_null.over = "yes"; //снимаем таймер
			AddQuestRecord("SeekMayorsRing", "7");
			AddQuestUserData("SeekMayorsRing", "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			CloseQuestHeader("SeekMayorsRing");
			DeleteAttribute(pchar, "questTemp.different.TakeMayorsRing");
		break;
		case "TakeRing_S3":
			dialog.text = "Holy Lord! I should really stop drinking that much...";
			link.l1 = "That's for damn sure! Well, here's your ring.";
			link.l1.go = "TakeRing_S4";
		break;
		case "TakeRing_S4":
			dialog.text = "Yes, yes, thanks a lot. I am in your debt! Here's your money for a job, well done!";
			link.l1 = "Thanks " + GetAddress_FormToNPC(NPChar) + ".";
			link.l1.go = "exit";
			TakeItemFromCharacter(pchar, "MayorsRing");
			ChangeCharacterComplexReputation(pchar,"nobility", 5);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 10);
			AddCharacterExpToSkill(pchar, "Leadership", 20);
			AddMoneyToCharacter(pchar, sti(pchar.questTemp.different.TakeMayorsRing.price));
			pchar.questTemp.different = "free";
			pchar.quest.TakeMayorsRing_null.over = "yes"; //снимаем таймер
			AddQuestRecord("SeekMayorsRing", "7");
			AddQuestUserData("SeekMayorsRing", "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			CloseQuestHeader("SeekMayorsRing");
			DeleteAttribute(pchar, "questTemp.different.TakeMayorsRing");
		break;
		// ---------------------- найти кольцо в борделе ----------------------------

		case "node_1":
            //ОСАДЫ homo
			if (CheckAttribute(Colonies[FindColony(npchar.City)],"Siege"))
            {

                makearef(aData, NullCharacter.Siege);
                

                if (CheckAttribute(aData, "HelpColony") && sti(aData.HelpColony) == true )
                {
                    dialog.text = "We have already discussed everything - haven't we?";
                    link.l1 = "Correct. I don't delay you any further.";
                    link.l1.go = "exit";

                }
                else
                {
                    dialog.text = "I am sorry to upset you, but I have no time to talk with you at the moment. As you should know, our colony was attacked by "+NationNamePeople(sti(aData.nation))+". I will need to set up the town's defenses.";
                    link.l1 = "Well, I just wanted to offer my assistance in the defense of the fort.";
                    link.l1.go = "siege_task";
                    link.l2 = "Then I will not delay you any further.";
        			link.l2.go = "exit";
                }
            }
            else
            {//->
                makearef(aData, NullCharacter.Siege);
                if (CheckAttribute(aData, "PlayerHelpMayor") && sti(aData.PlayerHelpMayor) == true
                && CheckAttribute(aData, "HelpColony") && sti(aData.HelpColony) == true )
                {
                    AddMoneyToCharacter(Pchar,(sti(aData.iSquadronPower)*3000));
                    ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 20);
                    ChangeCharacterComplexReputation(pchar,"nobility", 10);
                    AddCharacterExpToSkill(GetMainCharacter(), "Leadership", 80);
                    AddCharacterExpToSkill(GetMainCharacter(), "Sailing", 100);
                    AddCharacterExpToSkill(GetMainCharacter(), "Accuracy", 100);
                    AddCharacterExpToSkill(GetMainCharacter(), "Cannons", 100);
                    //--> слухи
                    SiegeRumour("They say that you had helped us to repel the "+NationNameSK(sti(aData.nation))+" squadron and defend our colony! We are so grateful to you, "+ GetAddress_Form(NPChar)+".", aData.Colony, sti(aData.conation), -1, 15, 3);
		            //<-- слухи
                    DeleteAttribute(aData, "PlayerHelpMayor");
                    DeleteAttribute(aData, "HelpColony");
                    dialog.text = "Oh, that's you, "+GetAddress_Form(NPChar)+" "+GetFullName(pchar)+", I'm glad to see you. Good news for our colony - we managed to repel the "+NationNameSK(sti(aData.nation))+" invaders. You did your part in this as well, and here is your reward - "+(sti(aData.iSquadronPower)*1500)+" pesos. Here you go.";
                    link.l1 = "Thank you, " + GetAddress_FormToNPC(NPChar) + ", pleasure to do business with you!";
                    link.l1.go = "exit";
                }
                else
                {
                    if (CheckAttribute(aData, "PlayerHelpMayor")) DeleteAttribute(aData, "PlayerHelpMayor");
                    dialog.text = "So what was the reason for you to come here and distract me from important affairs of state?";
        			link.l1 = "I wanted to talk to you about work in the name of the Crown of " + NationNameGenitive(sti(NPChar.nation))+".";
						link.l1.go = "work";
					
					// Warship Генер "Пираты на необитайке" - сдаем пиратов властям
					if(CheckAttribute(PChar, "Quest.PiratesOnUninhabited_OnShore") || CheckAttribute(PChar, "Quest.PiratesOnUninhabited_ShipSink"))
					{
						link.l11 = XI_ConvertString(PChar.GenQuest.PiratesOnUninhabited.StartShore + "Dat") + " I met pirates. All " + PChar.GenQuest.PiratesOnUninhabited.PiratesCount + " are on board at the moment. I want to turn them to the authorities.";
						link.l11.go = "PiratesOnUninhabited_1";
					}
					
        			link.l2 = "I was going to talk to you about one important affair.";
					if(CheckAttribute(pchar,"questTemp.ReasonToFast") && !CheckAttribute(pchar,"questTemp.ReasonToFast.SpeakOther") && !CheckAttribute(pchar, "questTemp.ReasonToFast.cantSpeakOther") && (pchar.questTemp.ReasonToFast.city == NPChar.city))
					{
						link.l2.go = "ReasonToFast_Mayor1";
					}
					else
					{					
						link.l2.go = "quests";
					}	
					if(CheckAttribute(pchar,"GenQuest.CaptainComission") && (pchar.GenQuest.CaptainComission.variant == "A2") && (pchar.GenQuest.CaptainComission.City == NPChar.city))
					{
						if(pchar.GenQuest.CaptainComission == "Begin_1" && !CheckAttribute(pchar,"GenQuest.CaptainComission.SpeakMayor")) 
						{
							link.l12 = "There is a captain of the patrol " + GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name") + "Acc")) + " named " + pchar.GenQuest.CaptainComission.Name + ", how can I meet him?";
							link.l12.go = "CapComission_Mayor1";
						}	
						if(CheckAttribute(pchar,"GenQuest.CaptainComission.PrisonFree"))
						{
							link.l12 = "Former captain of patrol " + GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name") + "Acc")) + " " + pchar.GenQuest.CaptainComission.Name + " agreed to reveal his cache to the authorities.";
							link.l12.go = "CapComission_Mayor9";
						}
						if(pchar.GenQuest.CaptainComission == "GetGoodsSuccess")
						{
							link.l12 = "Former captain of patrol  " + GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name") + "Acc")) + " " + pchar.GenQuest.CaptainComission.Name + " revealed his cache to me.";
							link.l12.go = "CapComission_Mayor13";
						}
					}
					if(CheckAttribute(pchar,"GenQuest.ShipWreck") && pchar.GenQuest.ShipWreck == "SailorsOnShore" && GetQuestPastDayParam("GenQuest.ShipWreck") < 25 && sti(npchar.nation) == sti(pchar.GenQuest.ShipWreck.Nation))
					{
						if(!CheckAttribute(pchar,"GenQuest.ShipWreck.SpeakMayor"))
						{
							iDay = GetQuestPastDayParam("GenQuest.ShipWreck");
							if(CheckAttribute(pchar, "GenQuest.ShipWreck.Mutiny"))
							{
								link.l13 = UpperFirst(XI_ConvertString(pchar.GenQuest.ShipWreck.Shore + "Dat")) + " I met a captain " + pchar.GenQuest.ShipWreck.Name + " and his sailors who were put ashore by pirate " + pchar.GenQuest.ShipWreck.BadName + ". " +
									"Unfortunately, I already had too many men on my ship and therefore could not take them on board. But I left food and weapon to them. If the expedition ship don't pick them up within " + (30 - iDay) + " days, then I don't know it'll find them still alive or not.";
								link.l13.go = "ShipWreck1";
							}
							else
							{
								link.l13 = UpperFirst(XI_ConvertString(pchar.GenQuest.ShipWreck.Shore + "Dat")) + " I met sailors from a victim shipwreck of ship '" + pchar.GenQuest.ShipWreck.ShipTypeName + "' with their captain. " + 
									"Unfortunately, I already had too many men on my ship and therefore could not take them on board. But I left food and weapon to them. If the expedition ship don't pick them up within " + (30 - iDay) + " days, then I don't know it'll find them still alive or not.";
								link.l13.go = "ShipWreck1";							
							}	
						}	
					}					
					//--> Jason, генер почтового курьера 2 уровня
						if (CheckAttribute(PChar, "questTemp.WPU.Postcureer.LevelUp"))
						{
							if (pchar.questTemp.WPU.Postcureer.TargetPortmanID == npchar.id)
							{
							link.l14 = "I have delivered you a message from the town of "+XI_ConvertString("Colony"+pchar.questTemp.WPU.Postcureer.StartCity+"Gen")+".";
							link.l14.go = "Postcureer_LevelUp_ForAll";
							}
						}
					//<-- генер почтового курьера 2 уровня
					
					// --> Warship, 16.05.11. Квест "Правосудие на продажу".
					if(CheckAttribute(PChar, "GenQuest.JusticeOnSale.MayorWait") && CheckAttribute(PChar, "GenQuest.JusticeOnSale.CityId") && NPChar.location == PChar.GenQuest.JusticeOnSale.CityId + "_townhall")
					{
						link.l15 = "Milord, I have located a gang of smugglers, whose ringleader have been recently caught by the guards. Now they are planning to arrange his escape. Their ship '" + PChar.GenQuest.JusticeOnSale.ShipName + "' is moored at " + XI_ConvertString(PChar.GenQuest.JusticeOnSale.ShoreId + "Dat") + ".";
						link.l15.go = "JusticeOnSale_1";
					}
					//<-- Правосудие на продажу
					
        			if (GetPrisonerQty() > 0)
        			{
                        link.l3 = "I need to turn the captive captain to the authorities.";
        			    link.l3.go = "sell_prisoner";
        			}
					//Jason --> Регата
					if (CheckAttribute(pchar, "questTemp.Regata.ToPortRoyal") && NPChar.location == "Portroyal_townhall")
					{
						link.l4 = "I came on an invitation to participate in the regatta. Here's my invitation.";
						link.l4.go = "Regata";
					}
        			link.l5 = "Maybe you'd like to take a break?";
        			link.l5.go = "Play_Game";
        			link.l10 = "It was just a courtesy visit and nothing more, " + GetAddress_FormToNPC(NPChar) + ".";
        			link.l10.go = "node_2";
                }
    		}//<-
		break;
		
		case "Play_Game":
			dialog.text = "Hmm, and what kind of games do you prefer?";
			link.l1 = "Want to play a game of cards for some serious money?";
			link.l1.go = "Card_Game";
   			link.l2 = "How about rolling some dice in poker-joker?";
			link.l2.go = "Dice_Game";
			link.l10 = "Please excuse me, but duty calls.";
			link.l10.go = "exit";
		break;
		
		//  карты -->
        case "Card_Game":
            if (!CheckNPCQuestDate(npchar, "Card_date_Yet") || sti(PChar.rank) < 4 || isBadReputation(pchar, 50) || GetCharacterSkillToOld(pchar, SKILL_LEADERSHIP) < rand(5))
            {
                SetNPCQuestDate(npchar, "Card_date_Yet");
                dialog.text = "I will not gamble with crooks!";
    			link.l1 = "As you wish.";
    			link.l1.go = "exit";
			}
			else
			{
				if (CheckNPCQuestDate(npchar, "Card_date_begin"))
				{
					dialog.text = "Why not! Relaxing is always good for health... but not for the purse...";
	    			link.l1 = "Excellent.";
	    			link.l1.go = "Cards_begin";
	    			link.l2 = "What are the rules of our game?";
	    			link.l2.go = "Cards_Rule";
    			}
    			else
    			{
					dialog.text = "No, I am done for today. I've got things to do.";
	    			link.l1 = "As you wish.";
	    			link.l1.go = "exit";
				}
			}
		break;

		case "Cards_Rule":
   			dialog.text = CARDS_RULE;
			link.l1 = "Well, let's begin, then!";
			link.l1.go = "Cards_begin";
			link.l3 = "No, it's not for me...";
			link.l3.go = "exit";
		break;

		case "Cards_begin":
			dialog.text = "Let's agree on the bet, first.";
			link.l1 = "Let's play for 1000 pesos.";
			link.l1.go = "Cards_Node_100";
			link.l2 = "Let's play for 5000 pesos.";
			link.l2.go = "Cards_Node_500";
			link.l3 = "I guess I have to go.";
			link.l3.go = "exit";
		break;

		case "Cards_Node_100":
            if (!CheckCardsGameSmallRate())
		    {
                dialog.text = "You are a notorious cheater. I will not gamble with you.";
                link.l1 = "It's all lies! Well, whatever.";
			    link.l1.go = "exit";
			    break;
		    }

			if (sti(pchar.Money) < 3000)
		    {
                dialog.text = "Are you joking, " + GetAddress_Form(NPChar) + "? You have no money!";
                link.l1 = "It happens.";
			    link.l1.go = "exit";
			    break;
		    }
		    if (sti(npchar.Money) < 3000)
		    {
                dialog.text = "That's it! I am done with cards - before they'll call me a peculator and force me to leave my post.";
                link.l1 = "Pity.";
			    link.l1.go = "exit";
			    break;
		    }
   			dialog.text = "Fine, let's play for 1000 coins.";
			link.l1 = "Let's begin!";
			link.l1.go = "Cards_begin_go";
			pchar.GenQuest.Cards.npcharIdx = npchar.index;
            pchar.GenQuest.Cards.iRate     = 1000;
            pchar.GenQuest.Cards.SitType   = false;
		break;

		case "Cards_Node_500":
            if (!CheckCardsGameSmallRate())
		    {
                dialog.text = "You are a notorious cheater. I will not gamble with you.";
                link.l1 = "It's all lies! Well, whatever.";
			    link.l1.go = "exit";
			    break;
		    }
			if (!CheckCardsGameBigRate())
		    {
                dialog.text = "They say you're a very good player. I won't be playing high stakes with you.";
                link.l1 = "Shall we lower the bet, maybe?";
			    link.l1.go = "Cards_Node_100";
				link.l2 = "I am sorry, but I have to go.";
			    link.l2.go = "exit";
			    break;
		    }

			if (sti(pchar.Money) < 15000)
		    {
                dialog.text = "Are you joking, " + GetAddress_Form(npchar) + "? You don't have 15000 pesos!";
                link.l1 = "I'll raise them!";
			    link.l1.go = "exit";
			    break;
		    }
		    if (sti(npchar.Money) < 15000)
		    {
                dialog.text = "No, these bets will certainly empty the city treasury.";
                link.l1 = "As you wish.";
			    link.l1.go = "exit";
			    break;
		    }
   			dialog.text = "Fine, let's play for 5000 coins.";
			link.l1 = "Let's begin!";
			link.l1.go = "Cards_begin_go";
			pchar.GenQuest.Cards.npcharIdx = npchar.index;
            pchar.GenQuest.Cards.iRate     = 5000;
            pchar.GenQuest.Cards.SitType   = false;
		break;

		case "Cards_begin_go":
            SetNPCQuestDate(npchar, "Card_date_begin");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
            LaunchCardsGame();
		break;
	    // карты <--

	    //  Dice -->
        case "Dice_Game":
            if (!CheckNPCQuestDate(npchar, "Dice_date_Yet") || sti(PChar.rank) < 4 || isBadReputation(pchar, 50) || GetCharacterSkillToOld(pchar, SKILL_LEADERSHIP) < rand(5))
            {
                SetNPCQuestDate(npchar, "Dice_date_Yet");
                dialog.text = "I will not gamble with crooks!";
    			link.l1 = "As you wish.";
    			link.l1.go = "exit";
			}
			else
			{
				if (CheckNPCQuestDate(npchar, "Dice_date_begin"))
				{
					dialog.text = "Why not! Relaxing is always good for health... but not for the purse...";
	    			link.l1 = "Excellent.";
	    			link.l1.go = "Dice_begin";
	    			link.l2 = "What are the rules of our game?";
	    			link.l2.go = "Dice_Rule";
    			}
    			else
    			{
					dialog.text = "No, I am done for today. I've got things to do.";
	    			link.l1 = "As you wish.";
	    			link.l1.go = "exit";
				}
			}
		break;

		case "Dice_Rule":
   			dialog.text = DICE_RULE;
			link.l1 = "Well, let's begin, then!";
			link.l1.go = "Dice_begin";
			link.l3 = "No, it's not for me...";
			link.l3.go = "exit";
		break;

		case "Dice_begin":
			dialog.text = "Let's agree on the bet, first.";
			link.l1 = "Let's play for 500 pesos per die.";
			link.l1.go = "Dice_Node_100";
			link.l2 = "Let's play for 2000 pesos per die.";
			link.l2.go = "Dice_Node_500";
			link.l3 = "I guess I have to go.";
			link.l3.go = "exit";
		break;

		case "Dice_Node_100":
            if (!CheckDiceGameSmallRate())
		    {
                dialog.text = "You are a notorious cheater. I will not gamble with you.";
                link.l1 = "It's all lies! Well, whatever.";
			    link.l1.go = "exit";
			    break;
		    }

			if (sti(pchar.Money) < 3000)
		    {
                dialog.text = "Are you joking, " + GetAddress_Form(NPChar) + "? You have no money!";
                link.l1 = "It happens.";
			    link.l1.go = "exit";
			    break;
		    }
		    if (sti(npchar.Money) < 3000)
		    {
                dialog.text = "That's it! I am done with gambling - before they'll call me a peculator and force me to leave my post...";
                link.l1 = "Pity.";
			    link.l1.go = "exit";
			    break;
		    }
   			dialog.text = "Fine, let's play for 500 coins.";
			link.l1 = "Let's begin!";
			link.l1.go = "Dice_begin_go";
			pchar.GenQuest.Dice.npcharIdx = npchar.index;
            pchar.GenQuest.Dice.iRate     = 500;
            pchar.GenQuest.Dice.SitType   = false;
		break;

		case "Dice_Node_500":
            if (!CheckDiceGameSmallRate())
		    {
                dialog.text = "You are a notorious cheater. I will not gamble with you.";
                link.l1 = "It's all lies! Well, whatever.";
			    link.l1.go = "exit";
			    break;
		    }
			if (!CheckDiceGameBigRate())
		    {
                dialog.text = "They say you're a very good player. I won't be playing high stakes with you.";
                link.l1 = "Shall we lower the bet, maybe?";
			    link.l1.go = "Dice_Node_100";
				link.l2 = "I am sorry, but I have to go.";
			    link.l2.go = "exit";
			    break;
		    }

			if (sti(pchar.Money) < 15000)
		    {
                dialog.text = "Are you joking, " + GetAddress_Form(NPChar) + "? You don't have 15000 pesos!";
                link.l1 = "I'll raise them!";
			    link.l1.go = "exit";
			    break;
		    }
		    if (sti(npchar.Money) < 15000)
		    {
                dialog.text = "No, these bets will certainly empty the city treasury.";
                link.l1 = "As you wish.";
			    link.l1.go = "exit";
			    break;
		    }
   			dialog.text = "Fine, let's play for 2000 pesos per die.";
			link.l1 = "Let's begin!";
			link.l1.go = "Dice_begin_go";
			pchar.GenQuest.Dice.npcharIdx = npchar.index;
            pchar.GenQuest.Dice.iRate     = 2000;
            pchar.GenQuest.Dice.SitType   = false;
		break;

		case "Dice_begin_go":
            SetNPCQuestDate(npchar, "Dice_date_begin");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
            LaunchDiceGame();
		break;
	    // Dice <--
		case "node_2":
			dialog.text = "In that case I would ask you to leave my study and stop distracting me from my work";
			link.l1 = "Yes, yes, of course. Sorry about bothering you.";
			link.l1.go = "exit";
		break;

		//---------------------------- генератор квестов мэра -------------------------------
		case "work": 
            dialog.text = "This is a bug. Notify devs about it.";
        	link.l1 = "Alright, buddy!";
        	link.l1.go = "exit";

			//==> взят ли какой-либо квест
			if (CheckAttribute(pchar, "GenQuest.questName"))
			{		 				
				//--> Федот, да не тот
				QuestName = pchar.GenQuest.questName;
				if (pchar.GenQuest.(QuestName).MayorId != npchar.id) 
				{					
					dialog.text = RandPhraseSimple("As far as I can tell, you already have a mission given to you by governor of " + XI_ConvertString("Colony"+characters[GetCharacterIndex(pchar.GenQuest.(QuestName).MayorId)].city+"Gen") + ". Finish the job you already have and we will talk.", 
						"Hmm, weren't that you in " + XI_ConvertString("Colony"+characters[GetCharacterIndex(pchar.GenQuest.(QuestName).MayorId)].city+"Dat") + " where you've taken certain orders from the local governor? Yes, that is correct. Finish your mission first.");
					link.l1 = RandPhraseSimple("I see...", "Understood..."+ GetSexPhrase("","") +", "+ GetAddress_FormToNPC(NPChar) + ".");
					link.l1.go = "exit";					
					break;
				}
				//<--Федот, да не тот
				//-------- взят квест уничтожения банды ---------->>
				if (QuestName == "DestroyGang")
				{
					switch (pchar.GenQuest.DestroyGang)
					{
						makearef(arName, pchar.GenQuest.DestroyGang);
						case "":
							dialog.text = LinkRandPhrase("A mission to locate bandit " + GetFullName(arName) + " has already been issued to you. Now fulfill it!", 
								"You already have a mission to locate the bandit by the name of " + GetFullName(arName) + ". I am waiting for the results!", 
								"While you are wasting your time away at my residence, " + GetFullName(arName) + " is robbing our colonists! Immediately proceed with the mission that has been entrusted to you!");
							link.l1 = RandPhraseSimple("Alright, " + GetAddress_FormToNPC(NPChar) + ".", "I am busy with it, "+ GetAddress_FormToNPC(NPChar) + ".");
							link.l1.go = "exit";		
						break;
						case "Late":
							dialog.text = RandPhraseSimple("The time given to you to locate and eliminate that bandit is over. And what kind of reports I am receiving, how do you think? And I'll tell you - " + GetFullName(arName) + " is still alive and kicking! Now deign to explain yourself, " + GetAddress_Form(NPChar) + ".",
								"All terms given to you to eliminate that scoundrel by the name of " + GetFullName(arName) + ", have run out. Still, I am being told that no progress at all has been made. What's up?");
							link.l1 = "I was not able to perform your job to the designated time, " + GetAddress_FormToNPC(NPChar) + ".";
							link.l1.go = "All_Late";		
						break;
						case "Found":
							dialog.text = RandPhraseSimple("So, what do you say? Did you manage to eliminate the mentioned bandit? " + GetFullName(arName) + " is finally dead?", "Tell me just one thing - is " + GetFullName(arName) + " dead or alive?");
							link.l1 = "Unfortunately, still alive, " + GetAddress_FormToNPC(NPChar) + ". I managed to seek him out, but I was outmatched and was forced to retreat. That bandit is a really hard nut. I am sorry.";
							link.l1.go = "All_Found";		
						break;
						case "Execute":
							dialog.text = RandPhraseSimple("So, what do you say? Did you manage to eliminate the mentioned bandit? " + GetFullName(arName) + " is finally dead?", "Tell me just one thing - is " + GetFullName(arName) + " dead or alive?");
							link.l1 = "He is dead, " + GetAddress_FormToNPC(NPChar) + ".";
							link.l1.go = "All_Execute";		
							AddCharacterExpToSkill(PChar, "Leadership", 80);
							ChangeCharacterComplexReputation(pchar,"authority", 1);
						break;
					}
				}
				//-------- контркурьер ---------->>
				if (QuestName == "TakePostcureer")
				{
					switch (pchar.GenQuest.TakePostcureer)
					{
						case "":
							dialog.text = LinkRandPhrase("A mission to capture a courier ship has already been issued to you. Now fulfill it!", 
								"You already have a mission to capture a courier ship! I am waiting for the results!", 
								"While you are wasting your time away at my residence, the documents I need are slipping right into our enemy's hands! Immediately proceed with the mission that has been entrusted to you!");
							link.l1 = RandPhraseSimple("Alright, " + GetAddress_FormToNPC(NPChar) + ".", "I am busy with it, "+ GetAddress_FormToNPC(NPChar) + ".");
							link.l1.go = "exit";		
						break;
						case "Late":
							dialog.text = RandPhraseSimple("The time given to you to locate and capture that courier ship is over. And what kind of reports I am receiving, how do you think? And I'll tell you - the documents I was expecting fell right into our enemy's hands! Now deign to explain yourself, " + GetAddress_Form(NPChar) + ".",
								"All terms given to you to capture the documents from the courier's vessel, have run out. Still, no progress at all has been made. What's up?");
							link.l1 = "I was not able to perform your job to the designated time, " + GetAddress_FormToNPC(NPChar) + ".";
							link.l1.go = "All_Late";		
						break;
						case "Found":
							dialog.text = RandPhraseSimple("So, what do you say? Did you manage to capture the documents?", "Tell me just one thing - have you managed to secure the correspondence?");
							link.l1 = "Unfortunately, no, " + GetAddress_FormToNPC(NPChar) + ". I have located the ship, but the documents eluded me.";
							link.l1.go = "All_Found";		
						break;
						case "Execute":
							dialog.text = RandPhraseSimple("So, what do you say? Did you manage to capture the documents?", "Tell me just one thing - have you managed to secure the correspondence?");
							link.l1 = "Yes, " + GetAddress_FormToNPC(NPChar) + ". I am ready to hand it over to you. Here you go.";
							link.l1.go = "All_Execute";		
							AddCharacterExpToSkill(PChar, "Leadership", 100);
							AddCharacterExpToSkill(PChar, "Fortune", 200);
							AddCharacterExpToSkill(PChar, "Sneak", 50);
							RemoveItems(pchar, "ContraPostLetters", 1);
							ChangeCharacterComplexReputation(pchar,"authority", 1);
						break;
					}
				}
				//-------- контрфрахт - арсенал ---------->>
				if (QuestName == "TakeArsenalship")
				{
					switch (pchar.GenQuest.TakeArsenalship)
					{
						case "":
							dialog.text = LinkRandPhrase("A mission to destroy a military transport has already been issued to you. Now fulfill it!", 
								"You already have a mission to destroy a military transport! I am waiting for the results!", 
								"While you are wasting your time away at my residence, gunpowder and ammunition are being delivered straight to enemy cannons! Immediately proceed with the mission that has been entrusted to you!");
							link.l1 = RandPhraseSimple("Alright, " + GetAddress_FormToNPC(NPChar) + ".", "I am busy with it, "+ GetAddress_FormToNPC(NPChar) + ".");
							link.l1.go = "exit";		
						break;
						case "Late":
							dialog.text = RandPhraseSimple("The time given to you to locate and destroy that military transport is over. And what kind of reports I am receiving, how do you think? And I'll tell you - the enemy convoy has successfully reached its destination! Now deign to explain yourself, " + GetAddress_Form(NPChar) + ".",
								"All terms given to you to destroy the enemy military transport, have run out. Still, no progress at all has been made. What's up?");
							link.l1 = "I was not able to execute your task in aforesaid time, " + GetAddress_FormToNPC(NPChar) + ".";
							link.l1.go = "All_Late";		
						break;
						case "Found":
							dialog.text = RandPhraseSimple("So, what do you say? Did you manage to destroy enemy transport?", "Tell me just one thing - is enemy arsenal resting on the seabed?");
							link.l1 = "Unfortunately, no, " + GetAddress_FormToNPC(NPChar) + ". I have located the convoy, but failed to sink the required vessel.";
							link.l1.go = "All_Found";		
						break;
						case "Execute":
							dialog.text = RandPhraseSimple("So, what do you say? Did you manage to destroy enemy transport?", "Tell me just one thing - is enemy arsenal resting on the seabed?");
							link.l1 = "Yes, " + GetAddress_FormToNPC(NPChar) + ". Our enemy will not receive that gunpowder and ammunition.";
							link.l1.go = "All_Execute";		
							AddCharacterExpToSkill(PChar, "Leadership", 120);
							AddCharacterExpToSkill(PChar, "Fortune", 200);
							AddCharacterExpToSkill(PChar, "Sneak", 50);
							ChangeCharacterComplexReputation(pchar,"authority", 1);
						break;
					}
				}
				//-------- ОЗГ - пират ---------->>
				if (QuestName == "TakePirateship")
				{
					switch (pchar.GenQuest.TakePirateship)
					{
						case "":
							dialog.text = LinkRandPhrase("A mission to eliminate the pirate has already been issued to you. Now fulfill it!", 
								"You already have a mission to destroy a pirate ship! I am waiting for the results!", 
								"While you are wasting your time away at my residence, that filthy pirate is picking yet another victim! Immediately proceed with the mission that has been entrusted to you!");
							link.l1 = RandPhraseSimple("Alright, " + GetAddress_FormToNPC(NPChar) + ".", "I am busy with it, "+ GetAddress_FormToNPC(NPChar) + ".");
							link.l1.go = "exit";		
						break;
						case "Late":
							dialog.text = RandPhraseSimple("The time given to you to locate and eliminate the pirate is over. And what kind of reports I am receiving, how do you think? And I'll tell you - that filthy pirate is still raiding our ships! Now deign to explain yourself, " + GetAddress_Form(NPChar) + ".",
								"All terms given to you to destroy the pirate ship, have run out. Still, no progress at all has been made. What's up?");
							link.l1 = "I was not able to perform your job to the designated time, " + GetAddress_FormToNPC(NPChar) + ".";
							link.l1.go = "All_Late";		
						break;
						case "Found":
							dialog.text = RandPhraseSimple("So, what do you say? Did you manage to destroy the pirate ship?", "Tell me just one thing - is that filthy pirate finally resting on the seabed?");
							link.l1 = "Unfortunately, no, " + GetAddress_FormToNPC(NPChar) + ". I managed to seek that scoundrel out, but I failed to sink his ship.";
							link.l1.go = "All_Found";		
						break;
						case "Execute":
							dialog.text = RandPhraseSimple("So, what do you say? Did you manage to destroy the pirate ship?", "Tell me just one thing - is that filthy pirate finally resting on the seabed?");
							link.l1 = "Yes, " + GetAddress_FormToNPC(NPChar) + ". That scoundrel will no longer trouble our peaceful merchant vessels.";
							link.l1.go = "All_Execute";		
							AddCharacterExpToSkill(PChar, "Leadership", 150);
							AddCharacterExpToSkill(PChar, "Fortune", 200);
							AddCharacterExpToSkill(PChar, "Sneak", 50);
							ChangeCharacterComplexReputation(pchar,"authority", 1);
						break;
					}
				}
					//-------- ОЗГ - пассажир ---------->>
				if (QuestName == "TakePassenger")
				{
					switch (pchar.GenQuest.TakePassenger)
					{
						case "":
							dialog.text = LinkRandPhrase("A mission to seek out the criminal has already been issued to you. Now fulfill it!", 
								"You already have a mission to seek out the criminal! I am waiting for the results!", 
								"While you are wasting your time away at my residence, that filthy villain keeps sailing around! Immediately proceed with the mission that has been entrusted to you!");
							link.l1 = RandPhraseSimple("Alright, " + GetAddress_FormToNPC(NPChar) + ".", "I am busy with it, "+ GetAddress_FormToNPC(NPChar) + ".");
							link.l1.go = "exit";		
						break;
						case "Late":
							dialog.text = RandPhraseSimple("The time given to you to locate that scoundrel is over. And what kind of reports I am receiving, how do you think? And I'll tell you - he successfully arrived at his destination and then disappeared into thin air! Now deign to explain yourself, " + GetAddress_Form(NPChar) + ".",
								"All terms given to you to find the criminal, have run out. Still, no progress at all has been made. What's up?");
							link.l1 = "I was not able to execute your task in aforesaid time, " + GetAddress_FormToNPC(NPChar) + ".";
							link.l1.go = "All_Late";		
						break;
						case "Found":
							dialog.text = RandPhraseSimple("So, what do you say? Have you captured the villain?", "Tell me just one thing - is that filthy villain in your hold, gagged and manacled?");
							link.l1 = "Unfortunately, no, " + GetAddress_FormToNPC(NPChar) + ". I failed to capture the villain. He went down with the ship he was on.";
							link.l1.go = "All_Found";		
						break;
						case "Execute":
							dialog.text = RandPhraseSimple("So, what do you say? Have you captured the villain?", "Tell me just one thing - is that filthy villain in your hold, gagged and manacled?");
							link.l1 = "Yes, " + GetAddress_FormToNPC(NPChar) + ". Please send your soldiers to the pier, and I will hand him to you.";
							link.l1.go = "All_Execute";		
							AddCharacterExpToSkill(PChar, "Leadership", 150);
							AddCharacterExpToSkill(PChar, "Fortune", 200);
							AddCharacterExpToSkill(PChar, "Sneak", 100);
							ChangeCharacterComplexReputation(pchar,"authority", 1);
							sld = &Characters[sti(Pchar.GenQuest.TakePassenger.PrisonerIDX)];
							ReleasePrisoner(sld); //освободили пленника
							sld.lifeday = 0;
						break;
					}
				}
				//-------- таможенный патруль ---------->>
				if (QuestName == "CustomPatrol")
				{
					switch (pchar.GenQuest.CustomPatrol)
					{
						case "":
							dialog.text = LinkRandPhrase("A mission to seek out the smugglers has already been issued to you. Now fulfill it!", 
								"You already have a mission to seek out the smugglers! I am waiting for the results!", 
								"While you are wasting your time away at my residence, those smugglers are preparing to strike another deal! Immediately proceed with the mission that has been entrusted to you!");
							link.l1 = RandPhraseSimple("Alright, " + GetAddress_FormToNPC(NPChar) + ".", "I am busy with it, "+ GetAddress_FormToNPC(NPChar) + ".");
							link.l1.go = "exit";		
						break;
						case "Late":
							dialog.text = RandPhraseSimple("The time given to you to locate the smugglers is over. And what kind of reports I am receiving, how do you think? And I'll tell you - they have happily sold all their goods! Now deign to explain yourself, " + GetAddress_Form(NPChar) + ".",
								"All terms given to you to find the smugglers, have run out. Still, no progress at all has been made. What's up?");
							link.l1 = "I was not able to execute your task in aforesaid time, " + GetAddress_FormToNPC(NPChar) + ".";
							link.l1.go = "All_Late";		
						break;
						case "Found":
							dialog.text = RandPhraseSimple("So, what do you say? Have you dealt with the smugglers?", "Tell me just one thing - have you wrecked the deal of those smugglers?");
							link.l1 = "Unfortunately, no, " + GetAddress_FormToNPC(NPChar) + ". I failed to foil the plans of those villains.";
							link.l1.go = "All_Found";		
						break;
						case "Execute":
							dialog.text = RandPhraseSimple("So, what do you say? Have you dealt with the smugglers?", "Tell me just one thing - have you wrecked the deal of those smugglers?");
							link.l1 = "Yes, " + GetAddress_FormToNPC(NPChar) + ". I caught up with them and eliminated the ships of both parties, buyer and seller alike.";
							link.l1.go = "All_Execute";		
							AddCharacterExpToSkill(PChar, "Leadership", 100);
							AddCharacterExpToSkill(PChar, "Fortune", 200);
							AddCharacterExpToSkill(PChar, "Sneak", 200);
							ChangeCharacterComplexReputation(pchar,"authority", 1);
						break;
					}
				}
				//-------- Дезертир ---------->>
				if (QuestName == "FindFugitive")
				{
					switch (pchar.GenQuest.FindFugitive)
					{
						case "":
							dialog.text = LinkRandPhrase("A mission to seek out the deserter has already been issued to you. Now fulfill it!", 
								"You already have a mission to seek out the deserter! I am waiting for the results!", 
								"While you are wasting your time away at my residence, that deserter could be betraying our state secrets! Immediately proceed with the mission that has been entrusted to you!");
							link.l1 = RandPhraseSimple("Alright, " + GetAddress_FormToNPC(NPChar) + ".", "I am busy with it, "+ GetAddress_FormToNPC(NPChar) + ".");
							link.l1.go = "exit";		
						break;
						case "Late":
							dialog.text = RandPhraseSimple("The time given to you to locate the deserter is over. And what kind of reports I am receiving, how do you think? And I'll tell you - no result, none at all! Now deign to explain yourself, " + GetAddress_Form(NPChar) + ".",
								"All terms given to you to find the deserter, have run out. Still, no progress at all has been made. What's up?");
							link.l1 = "I was not able to perform your job to the designated time, " + GetAddress_FormToNPC(NPChar) + ".";
							link.l1.go = "All_Late";		
						break;
						case "Found":
							dialog.text = RandPhraseSimple("So, what do you say? Have you captured the deserter?", "Tell me just one thing - is that deserter in your hold, gagged and manacled?");
							link.l1 = "Unfortunately, no, " + GetAddress_FormToNPC(NPChar) + ". I failed to capture that scoundrel. I found his trail in the settlement of "+XI_ConvertString("Colony"+pchar.GenQuest.FindFugitive.City)+", but just on the day before my arrival he went south on a pirate ship. I guess he's with those gentlemen of fortune now.";
							link.l1.go = "All_Found";		
						break;
						case "Execute":
							dialog.text = RandPhraseSimple("Oh well... Here's our "+pchar.GenQuest.FindFugitive.Name+"... Great job, captain! Have you had a hard time searching?", "Oh, what guests we have! Hello, "+pchar.GenQuest.FindFugitive.Name+"! Great job, captain! Have you spent a lot of effort on your search?");
							link.l1 = "How to say, " + GetAddress_FormToNPC(NPChar) + ". Whatever it was - your mission has been fulfilled.";
							link.l1.go = "All_Execute";		
							AddCharacterExpToSkill(PChar, "Leadership", 200);
							AddCharacterExpToSkill(PChar, "Fortune", 200);
							AddCharacterExpToSkill(PChar, "Sneak", 100);
							ChangeCharacterComplexReputation(pchar, "authority", 1);
							sld = &Characters[sti(Pchar.GenQuest.FindFugitive.PrisonerIDX)];
							ReleasePrisoner(sld); //освободили пленника
							LAi_SetActorType(sld);
							sld.lifeday = 0;
							pchar.quest.FindFugitive_Over.over = "yes"; //снимаем таймер
							chrDisableReloadToLocation = false;//открыть локацию
						break;
					}
				}
				//------ проникновение во враждебный город ------------>>
				if (QuestName == "Intelligence")
				{
					switch (pchar.GenQuest.Intelligence)
					{
						case "":
							if (GetQuestPastDayParam("GenQuest.Intelligence") > sti(pchar.GenQuest.Intelligence.Terms))
							{
								dialog.text = RandPhraseSimple("The time given to you to deliver the letter is over. And I take it that you have failed.",
									"All terms given to you to deliver the letter, have run out. Still, no progress at all has been made. What's up?");
								link.l1 = "I was not able to perform your job, " + GetAddress_FormToNPC(NPChar) + ".";
								link.l1.go = "All_Late";	
							}
							else
							{
								dialog.text = LinkRandPhrase("A mission to deliver a letter to me has already been issued to you. Now fulfill it!", 
									"You already have a mission to deliver a letter straight to me! I am waiting for the results, I need that letter as soon as possible!", 
									"While you are wasting your time away at my residence, the information I badly need is still in the hands of the person who is supposed to send it to me! Immediately proceed with the mission that has been entrusted to you!");
								link.l1 = RandPhraseSimple("Alright, " + GetAddress_FormToNPC(NPChar) + ".", "I will get to it right away, "+ GetAddress_FormToNPC(NPChar) + ".");
								link.l1.go = "exit";	
							}
						break;
						case "Execute":
							dialog.text = RandPhraseSimple("Have you delivered the letter I am expecting?", "Tell me now - do you have it?!");
							link.l1 = "Yes, I do. As we agreed - delivered to you, personally.";
							if (GetQuestPastDayParam("GenQuest.Intelligence") > sti(pchar.GenQuest.Intelligence.Terms))
							{
								link.l1.go = "Intelligence_ExecuteLate";
								AddCharacterExpToSkill(PChar, "Sneak", 200);
							}
							else
							{
								link.l1.go = "All_Execute";		
								AddCharacterExpToSkill(PChar, "Leadership", 100);
								AddCharacterExpToSkill(PChar, "Sneak", 200);
							}
							TakeItemFromCharacter(pchar, "sicretLetter");
							DeleteAttribute(ItemsFromID("sicretLetter"), "City");
							DeleteAttribute(ItemsFromID("sicretLetter"), "Mayor");
						break;
					}
				}
				break;
			}
			sTemp = npchar.city;
			//занят ПГГ
			i = CheckAvailableTaskForNPC(NPChar, PGG_TASK_WORKONMAYOR);
			if (i != -1)
			{
				dialog.text = "Alas, today I don't have a job anymore. The last one has been done by " + GetFullName(&Characters[i])
					+ ". Come tomorrow, maybe something will appear.";
				link.l1 = "Oh, damn! No luck...";
				link.l1.go = "exit";
				break;
			}
//navy <--
			if (!CheckAttribute(npchar, "work_date") || GetNpcQuestPastDayParam(npchar, "work_date") > 2 || bBettaTestMode)
    		{	
				SaveCurrentNpcQuestDateParam(npchar, "work_date");
				if (rand(5) > 4 && !bBettaTestMode && pchar.location == "Panama_townhall") // patch-5
				{
					dialog.text = LinkRandPhrase("For now I don't have work for people like you. Come tomorrow, I suppose...", 
						"Alas, I have no work for you today. Please, check back in a day or two.", 
						"Today there is nothing that I could propose to you. I will be glad to see you the other day.");
					link.l1 = "I understand, " + GetAddress_FormToNPC(NPChar) + ".";
					link.l1.go = "exit";
				}
				else 
				{
					i = dRand(7);
					switch (i)
					{					
						//========== квест уничтожения банды ============ //Jason: оставляем, как классику
						case 0:
							pchar.GenQuest.DestroyGang.Terms = dRand(2) + 2; //сроки выполнения задания
							pchar.GenQuest.DestroyGang.Money = ((dRand(6)+4)*250)+(sti(pchar.rank)*300+2000); //вознаграждение
							makearef(arName, pchar.GenQuest.DestroyGang);
							arName.nation = PIRATE;
							arName.sex = "man";
							SetRandomNameToCharacter(arName); //имя бандита в структуру квеста	
							dialog.text = "Just now I happened to have a mission for you. In the jungle near " + XI_ConvertString("Colony"+npchar.city+"Gen") + " the band of robbers have appeared, and I know that a ringleader of it is some " + GetFullName(arName) + ". Locate and eliminate this gang of thugs.";
							link.l1 = "Am I somehow limited in terms?";
							link.l1.go = "DestroyGang";
						break;
						//========== пробраться во вражеский город ============//Jason: оставляем, как годный
						case 1:
							pchar.GenQuest.Intelligence.Terms = dRand(10) + (42 - MOD_SKILL_ENEMY_RATE); //сроки выполнения задания
							pchar.GenQuest.Intelligence.Money = ((dRand(4) + 6) * 1000) + (sti(pchar.rank) * 1000 + 10000); //вознаграждение
							pchar.GenQuest.Intelligence.City = GetSpyColony(npchar); //враждебная колония
                            sTemp = ", which is on " + XI_ConvertString(colonies[FindColony(pchar.GenQuest.Intelligence.City)].islandLable+"Dat");                         
							dialog.text = "I have a mission for you, which entails some serious risks. I need you to sneak into " + XI_ConvertString("Colony"+pchar.GenQuest.Intelligence.City+"Acc") + sTemp + ", meet a certain person there and then deliver to me whatever he would you.";
							link.l1 = "Hmm, I don't think that in " + XI_ConvertString("Colony"+pchar.GenQuest.Intelligence.City+"Dat") + " I will be a welcome guest...";
							link.l1.go = "Intelligence";
						break;
						
						//========== контркурьер - отобрать почту ============
						case 2:
							dialog.text = "Yes, I have a mission for you. To fulfill it, you'd have to demonstrate maximum quickness and also some decent skill in naval combat. Are you ready to show your worth?";
							link.l1 = "Your Grace, can you reveal more details about the forthcoming mission?";
							link.l1.go = "TakePostcureer";
						break;
						
						//========== контрфрахт - потопить корабль с боеприпасами ============
						case 3:
							dialog.text = "Yes, I have a mission for you. To fulfill it, you'd have to demonstrate outstanding gallantry and also some decent skill in naval combat. Are you ready to show your worth?";
							link.l1 = "Your Grace, can you reveal more details about the forthcoming mission?";
							link.l1.go = "TakeArsenalship";
						break;
						//========== ОЗГ - охотник на пирата ============
						case 4:
							dialog.text = "Yes, I have an important mission for you. To fulfill it, you'd have to use all your naval skills. This involves pirates...";
							link.l1 = "Pirates? Can you tell me in more details what is expected of me, then?";
							link.l1.go = "TakePirateship";
						break;
						//========== ОЗГ - охотник на пассажира ============
						case 5:
							dialog.text = "You're just in time, sir. I have an urgent mission, which, I guess, will suit you just fine. It involves seeking out and capturing one certain person...";
							link.l1 = "Search of man? Can you tell me in more details what is expected of me, then?";
							link.l1.go = "TakePassenger";
						break;
						//========== Патруль - таможенник ============
						case 6:
							dialog.text = "You're just in time, captain. I have to deal with one urgent problem connected to smuggling goods to our colony. I suppose your ship is seaworthy and ready for battle.";
							link.l1 = "My ship is always seaworthy and ready for battle. Please, tell me more about the upcoming mission, your grace.";
							link.l1.go = "CustomPatrol";
						break;
							//========== Найти дезертира ============
						case 7:
							dialog.text = "I have a mission for you, which entails visiting several settlements on the archipelago. Are you ready for a long journey?";
							link.l1 = "Yes, me and my men are ready to depart right away? What exactly will I have to do?";
							link.l1.go = "FindFugitive";
						break;
					}
				}
			}
			else
			{
				dialog.text = LinkRandPhrase("Today I cannot offer you any jobs.", "Today there are no more jobs left for you.", "No more jobs for today, sorry. Come again tomorrow, and we'll see...");
				link.l1 = RandPhraseSimple("Pity...", "Ah, what a pity, "+ GetAddress_FormToNPC(NPChar) + ". ");
        		link.l1.go = "exit";
			}
		//---------------------------- генератор квестов мэра -------------------------------
		break;

		case "sell_prisoner":
            dialog.text = "Whom would you like to ransom?";

            qty = 1;
            for(i=0; i < GetPassengersQuantity(pchar); i++)
            {
                cn = GetPassenger(pchar,i);
                if(cn != -1)
                {
                    offref = GetCharacter(cn);
                    if(CheckAttribute(offref,"prisoned"))
                    {
        	            if(sti(offref.prisoned)==true && GetRemovable(offref)) // ставим только фантомов
        	            {
                            attrLoc = "l"+qty;
                            link.(attrLoc)    = GetFullName(offref) + " - " + NationNameMan(sti(offref.nation)) + ".";
                            link.(attrLoc).go = "GetPrisonerIdx_" + offref.index;
                            qty++;
                        }
                    }
                }
            }
			link.l99 = "Nobody.";
			link.l99.go = "exit";
		break;
		
		case "sell_prisoner_2":
            offref = GetCharacter(sti(pchar.GenQuest.GetPrisonerIdx));
            attrLoc =  "So, this is captain " + GetFullName(offref) + ", " + NationNameMan(sti(offref.nation))+ ".";
            // цена зависит от губернатора
            qty = makeint(sti(offref.rank)*(800 + GetCharacterSPECIALSimple(NPChar, SPECIAL_L)*100) + GetCharacterSkillToOld(offref, "Leadership")*500 + GetCharacterSkillToOld(pchar, "commerce")*500);
            if (sti(offref.nation) == sti(NPChar.nation))
            {
                attrLoc = attrLoc + " I am ready to pay ransom for my compatriot in the amount of  " + FindRussianMoneyString(qty) + ".";
            }
            else
            {
                if (sti(offref.nation) == PIRATE)
                {
                    qty = qty / 5;
                    attrLoc = attrLoc + " I can give for this gallows " + FindRussianMoneyString(qty) + ". And then we'll execute the scoundrel at once.";

                }
                else
                {
                    qty = qty / 2;
                    attrLoc = attrLoc + " For that man I can pay no more than " + FindRussianMoneyString(qty) + ".";
                }
            }
			dialog.text = attrLoc;
			pchar.PrisonerSellPrice =  qty;
			link.l1 = "Deal. He's yours, " + GetAddress_FormToNPC(NPChar) + ".";
			link.l1.go = "sell_prisoner_3";
			link.l3 = "No. That won't do.";
			link.l3.go = "exit";
		break;


		case "sell_prisoner_3":
			dialog.text = "That's good.";
			link.l1 = "All the best.";
			link.l1.go = "exit";
			OfficersReaction("bad");

			offref = GetCharacter(sti(pchar.GenQuest.GetPrisonerIdx));
			AddMoneyToCharacter(pchar, sti(pchar.PrisonerSellPrice));
			if (sti(offref.nation) == sti(NPChar.nation))
            {
                AddCharacterExpToSkill(pchar, "Commerce", 25);
            }
            else
            {
                if (sti(offref.nation) == PIRATE)
                {
                    ChangeCharacterComplexReputation(pchar,"nobility", -2);
                }
                else
                {
                    AddCharacterExpToSkill(pchar, "Commerce", 5);
                }
            }

        	offref.location = "";
        	ReleasePrisoner(offref); // освободили пленника
		break;
		////   CAPTURE //////////
		case "CAPTURE_Main":
            NextDiag.TempNode = "CAPTURE_Main";
			AfterTownBattle();  // все, все свободны
			
			// --> Левассер
			if (pchar.location == "Tortuga_townhall" && CheckAttribute(pchar, "questTemp.Sharlie.Hardcore_Tortuga"))
			{
                dialog.Text = "Arrgh! What's the deal with all that outrage, de Maure? Since when do the French attack their own compatriots?!";
                Link.l1 = "By the order of Francois Longvillier de Poincy you, Levasseur, are removed from the post of the governor of Tortuga and sentenced to death! And I am the one who shall carry out this sentence!";
                Link.l1.go = "levasser";
				break;
			}
			// <-- Левассер
            // fix от грабежа 5 раз на дню -->
            if (!CheckNPCQuestDate(npchar, "GrabbingTownDate"))
			{
                dialog.Text = "You have already taken everything. What else do you need?";
                Link.l1 = "Yeah, right, wrong city.";
                Link.l1.go = "Exit_City";

                NPChar.NoGiveMoney = true;

            	ChangeCharacterHunterScore(GetMainCharacter(), NationShortName(sti(NPChar.nation)) + "hunter", 20);
                // вернем диалог после разговора и спрячем
                SetReturn_Gover_Dialog_Exit(NPChar);
				break;
			}
			SetNPCQuestDate(npchar, "GrabbingTownDate");
			// fix от грабежа 5 раз на дню <--

            if (CheckAttribute(FortChref, "Fort.Mode") && sti(FortChref.Fort.Mode) != FORT_DEAD)
            { // а форт-то ЖИВ, значит с суши прошли
                dialog.Text = "Unprecedented insolence! The reinforcements from the fort will arrive soon, and you'll have to pay for this!";
                Link.l2 = "I am not going to stick here until they will arrive. You just pay me, and we will leave this town.";
                Link.l2.go = "Summ";
                Pchar.HalfOfPaymentByCity = true; // токо половина денег
            }
            else
            {
				dialog.Text = "You won this time, but know that our squadron will arrive soon and it will leave nothing of you!";
	            if (!bWorldAlivePause || bBettaTestMode)
	            {
	                int iColony = FindColony(npchar.city);
					if (!CheckAttribute(&colonies[iColony], "notCaptured")) //незахватываемые города
					{
						if (CheckAttribute(FortChref, "Default.Prison"))
	    				{
	    					Link.l1 = "Shut up! This town belongs to me from now on; as for your squadron - I'll send it straight to the sea devil. Hey, guys, grab that pig and put it behind bars.";
	    				}
	    				else
	    				{
	    					Link.l1 = "This city now belongs to me, and how to defend it I will decide myself. Hey, guys, remove this upstart.";
	    				}
	    				Link.l1.go = "City";
					}
				}
				if (!isCityHasFort(NPChar.City))
	            {
	                Link.l2 = "A landing party? Hmm... Just pay me, and we will leave your town.";
				}
				else
				{
	            	Link.l2 = "A squadron? Hmm... Just pay me, and we will leave your town.";
	            }
				Link.l2.go = "Summ";

                bOk = !bWorldAlivePause || bBettaTestMode;
	            if (isMainCharacterPatented() && bOk && !CheckAttribute(&colonies[iColony], "notCaptured")) //не даем захватить колонию
	            {
					// восстановим нацию патента
					PChar.nation = GetBaseHeroNation();
					
					dialog.Text = "Unprecedented insolence! How dare you to attack the colony belonging to " + NationNameGenitive(sti(NPChar.nation)) + "?! You will pay dearly for the blood you've spilled and for the damage you inflicted upon our state.";
	                Link.l1 = "From this point on this colony belongs to me. Whoever decides to dispute my authority goes straight to hell.";
	                Link.l1.go = "City_patent";
	                Link.l2 = "I am acting in the name of " + NationNameGenitive(sti(PChar.nation)) + " and I make an official statement that from this point on this colony belongs to " + NationKingsCrown(PChar) + "!";
	                Link.l2.go = "City_nation";
	                Link.l3 = "We should discuss the size of ransom. And if you keep being stubborn, we well reduce your wonderful town to ashes and hang you on the town square.";
	                Link.l3.go = "Summ_patent";
	            }
            }
        break;
		
		// --> Левассер
		case "levasser":
            dialog.Text = "Poincy?! Damn this old fart! Alright, I'll deal with him myself, and you are done for, scoundrel! You will not make it out of here alive - I will personally deal with you!";
			Link.l1 = "Spare me your words, old rake! To battle!";
			Link.l1.go = "levasser_1";
        break;
		
		case "levasser_1":
			chrDisableReloadToLocation = true;//закрыть локацию
            DialogExit();
			LAi_SetImmortal(npchar, false);
			ChangeCharacterAddressGroup(npchar, pchar.location, "goto", "goto6");
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "LevasserDiedResidence");
			AddDialogExitQuest("MainHeroFightModeOn");	
        break;
		// <-- Левассер
        
        case "City":
            ChangeCharacterHunterScore(GetMainCharacter(), NationShortName(sti(NPChar.nation)) + "hunter", 40);
            AddCharacterExpToSkill(GetMainCharacter(), "Leadership", 300);

            Pchar.GenQuestFort.fortCharacterIdx = FortChref.index;
            AddDialogExitQuest("Residence_Captured_Any");

            Statistic_AddValue(Pchar, NationShortName(sti(NPChar.nation)) + "_TakeTown", 1);
            // ремонт
            RepairAllShips();
            Log_Info("All ships have been repaired.");
            //  СЖ -->
			ReOpenQuestHeader("Gen_CityCapture");
	        AddQuestRecord("Gen_CityCapture", "t3");
			AddQuestUserData("Gen_CityCapture", "sSex", GetSexPhrase("",""));
			AddQuestUserData("Gen_CityCapture", "sCity", XI_ConvertString("colony" + NPChar.City));
			//  СЖ <--
            NextDiag.CurrentNode = "Prison";
			DialogExit();
        break;

        case "City_patent":
            ChangeCharacterComplexReputation(GetMainCharacter(),"nobility", -20); // пираты мы, но у нас патент
            dialog.Text = "You won this time, but but know that our squadron will arrive soon and it will leave nothing of you!";
			Link.l1 = "Shut up! This town belongs to me from now on; as for your squadron - I'll send it straight to the sea devil. Hey, guys, grab that pig and put it behind bars.";
			Link.l1.go = "City";
        break;

        case "Exit_for_pay":
			dialog.Text = "What else do you need from me?";
            Link.l1 = "Just checking if I missed something...";
            Link.l1.go = "exit";

            NextDiag.TempNode = "Exit_for_pay";
		break;

        case "Exit_City":
		    NextDiag.CurrentNode = "Exit_for_pay";
		    Pchar.GenQuestFort.fortCharacterIdx = FortChref.index;
		    if (sti(NPChar.NoGiveMoney) == false) // себе берем
		    {
				// вернем диалог после разговора и спрячем
				SetReturn_Gover_Dialog_Exit(NPChar);
				AddDialogExitQuestFunction("TWN_ExitForPay");
            }
            DialogExit();
        break;

        case "Summ":
            dialog.Text = "I have no other choice than to agree to your terms. Take your bloody money and leave the waters of our colony at once.";
            Link.l1 = "Allow me to take my leave.";
            Link.l1.go = "Exit_City";
            NPChar.NoGiveMoney = false;

            ChangeCharacterHunterScore(GetMainCharacter(), NationShortName(sti(NPChar.nation)) + "hunter", 30);
            AddCharacterExpToSkill(GetMainCharacter(), SKILL_FORTUNE, 200);
            AddCharacterExpToSkill(GetMainCharacter(), "Commerce", 200);

            Statistic_AddValue(Pchar, NationShortName(sti(NPChar.nation)) + "_GrabbingTown", 1);
            //  СЖ -->
			ReOpenQuestHeader("Gen_CityCapture");
	        AddQuestRecord("Gen_CityCapture", "t2");
			AddQuestUserData("Gen_CityCapture", "sSex", GetSexPhrase("","а"));
			AddQuestUserData("Gen_CityCapture", "sCity", XI_ConvertString("colony" + NPChar.City));
			//  СЖ <--
        break;

        case "Summ_patent":
            dialog.Text = "Alright, you can dictate your terms...";
            Link.l1 = "Yes, by the right of the strongest. Now, where is my money?";
            Link.l1.go = "Summ";
            ChangeCharacterComplexReputation(GetMainCharacter(),"nobility", -10); // не на службе
        break;

        case "City_nation":
			dialog.Text = "Alright, we surrender to the mercy of the winners.";
			Link.l1 = "I would advise you to leave the town as soon as you can - the upcoming changes may be quite harmful to you. Farewell.";
			Link.l1.go = "Exit_City";
			NPChar.NoGiveMoney = true;

            ChangeCharacterComplexReputation(GetMainCharacter(),"nobility", 5);
            AddCharacterExpToSkill(GetMainCharacter(), "Leadership", 500);
            AddCharacterExpToSkill(GetMainCharacter(), "Sneak", 300);
            SetNationRelationBoth(sti(PChar.nation), sti(NPChar.nation), RELATION_ENEMY);

            PChar.questTemp.DontSetNewDialogToMayor = true; // иначе может сменить диалог и сбойнуть
            PChar.questTemp.DontNullDeposit = true;    // чтоб не нулили ростовщика
            SetCaptureTownByNation(NPChar.City, sti(PChar.nation));
            DeleteAttribute(PChar, "questTemp.DontSetNewDialogToMayor");
            AddDialogExitQuestFunction("LaunchColonyInfoScreen"); // табличка
            //  СЖ -->
	    	sTemp =  GetNationNameByType(sti(PChar.nation));
			ReOpenQuestHeader("Gen_CityCapture");
	        AddQuestRecord("Gen_CityCapture", "t1");
			AddQuestUserData("Gen_CityCapture", "sCity", XI_ConvertString("colony" + NPChar.City));
			AddQuestUserData("Gen_CityCapture", "sNation", XI_ConvertString(sTemp + "Gen"));
			//  СЖ <--
			AddTitleNextRate(sti(PChar.nation), 1);  // счетчик звания
            SetCharacterRelationBoth(sti(FortChref.index), GetMainCharacterIndex(), RELATION_FRIEND);// нечего не дает, тк работает OtherChar - а это губер, но он и так друг
            UpdateRelations();

            // 22.03.05  fix вернем диалог после разговора и спрячем
            //  внутри диалога не работало
            SetReturn_Gover_Dialog_Exit(NPChar);

            Statistic_AddValue(Pchar, NationShortName(sti(NPChar.nation)) + "_TakeTown", 1);
	    break;
	    
	    case "Prison":
			dialog.Text = "What else do you need from me, scoundrel?";
            Link.l3 = "Looked like your excellency still lives. Well, now I have to go!";
            Link.l3.go = "exit";
            NextDiag.TempNode = "Prison";
		break;
		
		case "arestFree_1":
			dialog.text = "Settle? And how do you imagine that?";
            link.l1 = "I think a sum of " + iTotalTemp*6000 + " pesos can yet save me, can't it?";
			link.l1.go = "arestFree_2";
			link.l2 = "Nowise. And it's time for me to leave. Best regards.";
			link.l2.go = "arest_1";
		break;

		case "arestFree_2":
            if (GetCharacterSkillToOld(PChar, SKILL_FORTUNE) >= drand(7) && iTotalTemp < 21)
            {
    			dialog.text = "I guess we could settle our incident in such a manner. You haven't yet gone too far to make the situation irreparable.";
    		    link.l1 = "Excellent. I am very glad. Please, accept my donation.";
    		    link.l1.go = "Exit";
    		    AddMoneyToCharacter(pchar, -iTotalTemp*6000);
    		    ChangeCharacterHunterScore(Pchar, NationShortName(sti(NPChar.nation)) + "hunter", -iTotalTemp);
    		    AddCharacterExpToSkill(pchar, "Fortune", 100);
            }
            else
            {
    			dialog.text = "Are you offering me a bribe? Oh no! Your evil deeds can be atoned for in only one way... Guards! Put "+ GetSexPhrase("him","her") +" in prison!";
    		    link.l1 = "Hold on!";
    		    link.l1.go = "arest_2";
    		    AddCharacterExpToSkill(pchar, "Fortune", 10);
            }
		break;

		case "arest_1":
			dialog.text = "Of course, it's time. We'll see you off. Guards! Seize "+ GetSexPhrase("him","her") +"!";
		    link.l1 = "No way!";
		    link.l1.go = "fight";
		break;

		case "arest_2":
			dialog.text = "You've had plenty of time to think! Guards!";
			link.l1 = "Screw you! You will not get me easily!";
		    link.l1.go = "fight";
		break;    
		/////////////////////////////////////////////////////////////////////////////////////////////////
		//	Уничтожение банды
		/////////////////////////////////////////////////////////////////////////////////////////////////
		case "DestroyGang":
			dialog.text = "Of course. To fulfill this mission, I am giving you " + FindRussianDaysString(sti(pchar.GenQuest.DestroyGang.Terms)) + ", and your reward in case of success will be " + FindRussianMoneyString(sti(pchar.GenQuest.DestroyGang.Money)) + ".";
			link.l1 = "Fine, I accept this task.";
		    link.l1.go = "DestroyGang_agree";
			link.l2 = "Hmm... No, I think I'll pass.";
		    link.l2.go = "All_disagree";
		break;
		case "DestroyGang_agree":
			npchar.greeting = NationShortName(sti(npchar.nation)) + "_gov_complete";
			pchar.GenQuest.questName = "DestroyGang"; //тип квеста
			pchar.GenQuest.DestroyGang.Location = GetGangLocation(npchar); //определяем локацию,где банда
			pchar.GenQuest.DestroyGang.MayorId  = npchar.id; //Id мэра, чтобы знать, кто дал квест
			if (pchar.GenQuest.DestroyGang.Location == "none") //на всякий случай
			{
				dialog.text = "Hold on, I just forgot about yesterday's report. The point is that this gang has already left our island. So I have to cancel this mission.";
				link.l1 = "I see. A pity, I must say.";
				link.l1.go = "exit";
				DeleteAttribute(pchar, "GenQuest." + pchar.GenQuest.questName);
				DeleteAttribute(pchar, "GenQuest.questName");
			}
			else
			{
				dialog.text = "Well, great! I'll be waiting at my residence for you and your reports.";
				link.l1 = "I will not keep you waiting for long, " + GetAddress_FormToNPC(NPChar) + ".";
				link.l1.go = "exit";
				pchar.quest.DestroyGang.win_condition.l1 = "location";
				pchar.quest.DestroyGang.win_condition.l1.location = pchar.GenQuest.DestroyGang.Location;
				pchar.quest.DestroyGang.win_condition = "DestroyGang_fight";
				pchar.quest.DestroyGang.again = true; //тупо дожидаться своего часа бандиты не будут
				SetTimerCondition("AllMayorsQuests_Late", 0, 0, sti(pchar.GenQuest.DestroyGang.Terms), false);
				//==> энкаунтеров в квестовой локации не будет 
				locations[FindLocation(pchar.GenQuest.DestroyGang.Location)].DisableEncounters = true;
				ReOpenQuestHeader("MayorsQuestsList");
				AddQuestRecord("MayorsQuestsList", "1");
				AddQuestUserData("MayorsQuestsList", "ColonyName", XI_ConvertString("Colony"+npchar.city+"Gen"));
				AddQuestUserData("MayorsQuestsList", "MayorName", GetFullName(npchar));
				makearef(arName, pchar.GenQuest.DestroyGang);
				AddQuestUserData("MayorsQuestsList", "GangName", GetFullName(arName));
				AddQuestUserData("MayorsQuestsList", "sDay", FindRussianDaysString(sti(pchar.GenQuest.DestroyGang.Terms)));
				AddQuestUserData("MayorsQuestsList", "sMoney", FindRussianMoneyString(sti(pchar.GenQuest.DestroyGang.Money)));
			}
		break;
		/////////////////////////////////////////////////////////////////////////////////////////////////
		//	Контркурьер
		/////////////////////////////////////////////////////////////////////////////////////////////////
		case "TakePostcureer":
			//установка параметров
			pchar.GenQuest.questName = "TakePostcureer"; //тип квеста
			pchar.GenQuest.TakePostcureer.Nation = GetEnemyNationToMainCharacter();//вражеская нация
			while (sti(pchar.GenQuest.TakePostcureer.Nation) == PIRATE) pchar.GenQuest.TakePostcureer.Nation = GetEnemyNationToMainCharacter();
			pchar.GenQuest.TakePostcureer.City = FindEnemyCityToMC(false);
			pchar.GenQuest.TakePostcureer.Island = GetArealByCityName(pchar.GenQuest.TakePostcureer.City);
			pchar.GenQuest.TakePostcureer.Terms = GetMaxDaysFromIsland2Island(Islands[GetCharacterCurrentIsland(PChar)].id, pchar.GenQuest.TakePostcureer.Island)+5;
			pchar.GenQuest.TakePostcureer.LoginDay = sti(pchar.GenQuest.TakePostcureer.Terms)-1;
			pchar.GenQuest.TakePostcureer.ShipType = SelectCureerShipType();
			pchar.GenQuest.TakePostcureer.ShipName = GenerateRandomNameToShip(sti(pchar.GenQuest.TakePostcureer.Nation));
			pchar.GenQuest.TakePostcureer.Cannon = SelectLevelCannonParameter(sti(pchar.GenQuest.TakePostcureer.ShipType));
			pchar.GenQuest.TakePostcureer.Money = ((dRand(5)+drand(6)+4)*1000)+(sti(pchar.rank)*500);
			dialog.text = "Of course. You will need to locate a courier ship of "+NationNameGenitive(sti(pchar.GenQuest.TakePostcureer.Nation))+" by the name of '"+pchar.GenQuest.TakePostcureer.ShipName+"', board it and bring me the papers, which you should be able to find in captain's cabin. This vessel will be passing near "+XI_ConvertString("Colony"+pchar.GenQuest.TakePostcureer.City+"Gen")+" approximately in "+FindRussianDaysString(pchar.GenQuest.TakePostcureer.Terms)+".";
			link.l1 = "Alright, I accept this mission. And what kind of papers am I to look for?";
		    link.l1.go = "TakePostcureer_agree";
			link.l2 = "Hmm... No, I think I'll pass.";
		    link.l2.go = "All_disagree";
		break;
		
		case "TakePostcureer_agree":
			npchar.greeting = NationShortName(sti(npchar.nation)) + "_gov_complete";
			pchar.GenQuest.TakePostcureer.MayorId  = npchar.id; //Id мэра, чтобы знать, кто дал квест
			dialog.text = "Mail. There are very important papers for me. But there is no need for you to search among documents, just bring the whole package to me. I will pay you "+FindRussianMoneyString(sti(pchar.GenQuest.TakePostcureer.Money))+"\nSo, I will be waiting for you and the result of your work at my residence.";
			link.l1 = "I will not keep you waiting for long, " + GetAddress_FormToNPC(NPChar) + ".";
			link.l1.go = "exit";
			pchar.quest.TakePostcureer.win_condition.l1 = "location";
			pchar.quest.TakePostcureer.win_condition.l1.location = pchar.GenQuest.TakePostcureer.Island;
			pchar.quest.TakePostcureer.win_condition.l2 = "Timer";
			pchar.quest.TakePostcureer.win_condition.l2.date.hour  = sti(GetTime());
			pchar.quest.TakePostcureer.win_condition.l2.date.day   = GetAddingDataDay(0, 0, sti(pchar.GenQuest.TakePostcureer.LoginDay));
			pchar.quest.TakePostcureer.win_condition.l2.date.month = GetAddingDataMonth(0, 0, sti(pchar.GenQuest.TakePostcureer.LoginDay));
			pchar.quest.TakePostcureer.win_condition.l2.date.year  = GetAddingDataYear(0, 0, sti(pchar.GenQuest.TakePostcureer.LoginDay));
			pchar.quest.TakePostcureer.function = "TakePostcureer_CreateShip";
			SetTimerCondition("AllMayorsQuests_Late", 0, 0, sti(pchar.GenQuest.TakePostcureer.Terms), false);
			ReOpenQuestHeader("MayorsQuestsList");
			AddQuestRecord("MayorsQuestsList", "3");
			AddQuestUserData("MayorsQuestsList", "ColonyName", XI_ConvertString("Colony"+npchar.city+"Gen"));
			AddQuestUserData("MayorsQuestsList", "MayorName", GetFullName(npchar));
			AddQuestUserData("MayorsQuestsList", "sCity", XI_ConvertString("Colony"+pchar.GenQuest.TakePostcureer.City+"Gen"));
			AddQuestUserData("MayorsQuestsList", "sDay", FindRussianDaysString(sti(pchar.GenQuest.TakePostcureer.Terms)));
			AddQuestUserData("MayorsQuestsList", "sMoney", FindRussianMoneyString(sti(pchar.GenQuest.TakePostcureer.Money)));
			AddQuestUserData("MayorsQuestsList", "sNation", NationNameGenitive(sti(pchar.GenQuest.TakePostcureer.Nation)));
			AddQuestUserData("MayorsQuestsList", "sShipName", pchar.GenQuest.TakePostcureer.ShipName);
		break;
		
		/////////////////////////////////////////////////////////////////////////////////////////////////
		//	Контрфрахт - уничтожить корабль с арсеналом
		/////////////////////////////////////////////////////////////////////////////////////////////////
		case "TakeArsenalship":
			//установка параметров
			pchar.GenQuest.questName = "TakeArsenalship"; //тип квеста
			pchar.GenQuest.TakeArsenalship.Nation = GetEnemyNationToMainCharacter();//вражеская нация
			while (sti(pchar.GenQuest.TakeArsenalship.Nation) == PIRATE) pchar.GenQuest.TakeArsenalship.Nation = GetEnemyNationToMainCharacter();
			pchar.GenQuest.TakeArsenalship.City = FindEnemyCityToMC(false);
			pchar.GenQuest.TakeArsenalship.Island = GetArealByCityName(pchar.GenQuest.TakeArsenalship.City);
			pchar.GenQuest.TakeArsenalship.Terms = GetMaxDaysFromIsland2Island(Islands[GetCharacterCurrentIsland(PChar)].id, pchar.GenQuest.TakeArsenalship.Island)+5;
			pchar.GenQuest.TakeArsenalship.LoginDay = sti(pchar.GenQuest.TakeArsenalship.Terms)-1;
			pchar.GenQuest.TakeArsenalship.ShipType = SelectArsenalShipType();
			pchar.GenQuest.TakeArsenalship.ShipTypeA = SelectCureerShipType();
			pchar.GenQuest.TakeArsenalship.ShipName = GenerateRandomNameToShip(sti(pchar.GenQuest.TakeArsenalship.Nation));
			pchar.GenQuest.TakeArsenalship.Cannon = SelectLevelCannonParameter(sti(pchar.GenQuest.TakeArsenalship.ShipType));
			pchar.GenQuest.TakeArsenalship.CannonA = SelectLevelCannonParameter(sti(pchar.GenQuest.TakeArsenalship.ShipTypeA)); // Addon 2016-1 Jason пиратская линейка
			pchar.GenQuest.TakeArsenalship.Money = ((dRand(5)+drand(6)+4)*900)+(sti(pchar.rank)*500);
			dialog.text = "Of course. You will need to locate a military transport of "+NationNameGenitive(sti(pchar.GenQuest.TakeArsenalship.Nation))+", with gunpowder and ammunition on board; the name of the vessel is '"+pchar.GenQuest.TakeArsenalship.ShipName+"', find and destroy it. We'll damage the enemy power by doing that\nMentioned transport will sail with escort to the colony "+XI_ConvertString("Colony"+pchar.GenQuest.TakeArsenalship.City)+", and will be approximately in "+FindRussianDaysString(pchar.GenQuest.TakeArsenalship.Terms)+", so you should hurry.";
			link.l1 = "Alright, I accept this mission. Do I have to sink the ship with the arsenal or should I attempt to capture it?";
		    link.l1.go = "TakeArsenalship_agree";
			link.l2 = "Hmm... No, I think I'll pass.";
		    link.l2.go = "All_disagree";
		break;
		
		case "TakeArsenalship_agree":
			npchar.greeting = NationShortName(sti(npchar.nation)) + "_gov_complete";
			pchar.GenQuest.TakeArsenalship.MayorId  = npchar.id; //Id мэра, чтобы знать, кто дал квест
			dialog.text = "I don't care, this is up to you. The important thing is that this cargo must not reach its destination. If you succeed, I will pay you "+FindRussianMoneyString(sti(pchar.GenQuest.TakeArsenalship.Money))+"... I am no longer delaying you, captain.";
			link.l1 = "I will not keep you waiting for long, " + GetAddress_FormToNPC(NPChar) + ".";
			link.l1.go = "exit";
			pchar.quest.TakeArsenalship.win_condition.l1 = "location";
			pchar.quest.TakeArsenalship.win_condition.l1.location = pchar.GenQuest.TakeArsenalship.Island;
			pchar.quest.TakeArsenalship.win_condition.l2 = "Timer";
			pchar.quest.TakeArsenalship.win_condition.l2.date.hour  = sti(GetTime());
			pchar.quest.TakeArsenalship.win_condition.l2.date.day   = GetAddingDataDay(0, 0, sti(pchar.GenQuest.TakeArsenalship.LoginDay));
			pchar.quest.TakeArsenalship.win_condition.l2.date.month = GetAddingDataMonth(0, 0, sti(pchar.GenQuest.TakeArsenalship.LoginDay));
			pchar.quest.TakeArsenalship.win_condition.l2.date.year  = GetAddingDataYear(0, 0, sti(pchar.GenQuest.TakeArsenalship.LoginDay));
			pchar.quest.TakeArsenalship.function = "TakeArsenalship_CreateShip";
			SetTimerCondition("AllMayorsQuests_Late", 0, 0, sti(pchar.GenQuest.TakeArsenalship.Terms), false);
			ReOpenQuestHeader("MayorsQuestsList");
			AddQuestRecord("MayorsQuestsList", "8");
			AddQuestUserData("MayorsQuestsList", "ColonyName", XI_ConvertString("Colony"+npchar.city+"Gen"));
			AddQuestUserData("MayorsQuestsList", "MayorName", GetFullName(npchar));
			AddQuestUserData("MayorsQuestsList", "sCity", XI_ConvertString("Colony"+pchar.GenQuest.TakeArsenalship.City));
			AddQuestUserData("MayorsQuestsList", "sDay", FindRussianDaysString(sti(pchar.GenQuest.TakeArsenalship.Terms)));
			AddQuestUserData("MayorsQuestsList", "sMoney", FindRussianMoneyString(sti(pchar.GenQuest.TakeArsenalship.Money)));
			AddQuestUserData("MayorsQuestsList", "sNation", NationNameGenitive(sti(pchar.GenQuest.TakeArsenalship.Nation)));
			AddQuestUserData("MayorsQuestsList", "sShipName", pchar.GenQuest.TakeArsenalship.ShipName);
		break;
		
		/////////////////////////////////////////////////////////////////////////////////////////////////
		//	ОЗГ - уничтожить корабль пиратов
		/////////////////////////////////////////////////////////////////////////////////////////////////
		case "TakePirateship":
			//установка параметров
			pchar.GenQuest.questName = "TakePirateship"; //тип квеста
			pchar.GenQuest.TakePirateship.City = FindEnemyCityToMC(false);
			pchar.GenQuest.TakePirateship.Island = GetArealByCityName(pchar.GenQuest.TakePirateship.City);
			pchar.GenQuest.TakePirateship.Terms = GetMaxDaysFromIsland2Island(Islands[GetCharacterCurrentIsland(PChar)].id, pchar.GenQuest.TakePirateship.Island)+5;
			pchar.GenQuest.TakePirateship.ShipType = SelectCureerShipType();
			pchar.GenQuest.TakePirateship.ShipName = GenerateRandomNameToShip(PIRATE);
			pchar.GenQuest.TakePirateship.Name = GenerateRandomName(PIRATE, "man");
			pchar.GenQuest.TakePirateship.Cannon = SelectLevelCannonParameter(sti(pchar.GenQuest.TakePirateship.ShipType));
			pchar.GenQuest.TakePirateship.Money = ((dRand(5)+drand(6)+4)*1200)+(sti(pchar.rank)*500);
			dialog.text = "Of course. I am really maddened by active action of one pirate captain, whose name is "+pchar.GenQuest.TakePirateship.Name+". That scoundrel fell into the habit of raiding our merchant ships, which hurts the trade between colonies immensely. Now it's the perfect time to rid of that bastard, because I just happened to know, where he is hiding at the moment. Are you ready to put the enemy of our crown to his end?";
			link.l1 = "I'd be honored! Where can I find this apostate?";
		    link.l1.go = "TakePirateship_agree";
			link.l2 = "Hmm... No, I think I'll pass.";
		    link.l2.go = "All_disagree";
		break;
		
		case "TakePirateship_agree":
			npchar.greeting = NationShortName(sti(npchar.nation)) + "_gov_complete";
			pchar.GenQuest.TakePirateship.MayorId  = npchar.id; //Id мэра, чтобы знать, кто дал квест
			dialog.text = "In the nearest "+FindRussianDaysString(pchar.GenQuest.TakePirateship.Terms)+" his ship by the name of '"+pchar.GenQuest.TakePirateship.ShipName+"' will be cruising at the shores near "+XI_ConvertString("Colony"+pchar.GenQuest.TakePirateship.City+"Gen")+". Find him and kill. Send to feed the fish with the ship, board the ship - I do not care. I only care that damned pirate will stop defiling the land with his presence\nFor this task I am willing to pay you "+FindRussianMoneyString(sti(pchar.GenQuest.TakePirateship.Money))+". Do not waste time, captain: this scoundrel will not be waiting for you at "+XI_ConvertString("Colony"+pchar.GenQuest.TakePirateship.City+"Gen")+". Go, and may God help you!";
			link.l1 = "Raising an anchor already, " + GetAddress_FormToNPC(NPChar) + "! You will not be waiting for the good news for too long!";
			link.l1.go = "exit";
			pchar.quest.TakePirateship.win_condition.l1 = "location";
			pchar.quest.TakePirateship.win_condition.l1.location = pchar.GenQuest.TakePirateship.Island;
			pchar.quest.TakePirateship.function = "TakePirateship_CreateShip";
			SetTimerCondition("AllMayorsQuests_Late", 0, 0, sti(pchar.GenQuest.TakePirateship.Terms), false);
			ReOpenQuestHeader("MayorsQuestsList");
			AddQuestRecord("MayorsQuestsList", "9");
			AddQuestUserData("MayorsQuestsList", "ColonyName", XI_ConvertString("Colony"+npchar.city+"Gen"));
			AddQuestUserData("MayorsQuestsList", "MayorName", GetFullName(npchar));
			AddQuestUserData("MayorsQuestsList", "sCity", XI_ConvertString("Colony"+pchar.GenQuest.TakePirateship.City+"Gen"));
			AddQuestUserData("MayorsQuestsList", "sDay", FindRussianDaysString(sti(pchar.GenQuest.TakePirateship.Terms)));
			AddQuestUserData("MayorsQuestsList", "sMoney", FindRussianMoneyString(sti(pchar.GenQuest.TakePirateship.Money)));
			AddQuestUserData("MayorsQuestsList", "sName", pchar.GenQuest.TakePirateship.Name);
			AddQuestUserData("MayorsQuestsList", "sShipName", pchar.GenQuest.TakePirateship.ShipName);
		break;
		
		/////////////////////////////////////////////////////////////////////////////////////////////////
		//	ОЗГ - захватить пассажира
		/////////////////////////////////////////////////////////////////////////////////////////////////
		case "TakePassenger":
			//установка параметров
			pchar.GenQuest.questName = "TakePassenger"; //тип квеста
			pchar.GenQuest.TakePassenger.City = FindEnemyCityToMC(false);
			pchar.GenQuest.TakePassenger.CityA = SelectAnyColony(pchar.GenQuest.TakePassenger.City);
			pchar.GenQuest.TakePassenger.Nation = GetEnemyNationToMainCharacter();//вражеская нация
			while (sti(pchar.GenQuest.TakePassenger.Nation) == PIRATE) pchar.GenQuest.TakePassenger.Nation = GetEnemyNationToMainCharacter();
			pchar.GenQuest.TakePassenger.Terms1 = GetMaxDaysFromIsland2Island(Islands[GetCharacterCurrentIsland(PChar)].id, GetArealByCityName(pchar.GenQuest.TakePassenger.City));
			pchar.GenQuest.TakePassenger.Terms2 = GetMaxDaysFromIsland2Island(GetArealByCityName(pchar.GenQuest.TakePassenger.City), GetArealByCityName(pchar.GenQuest.TakePassenger.CityA))+1;
			pchar.GenQuest.TakePassenger.Terms = sti(pchar.GenQuest.TakePassenger.Terms1)+sti(pchar.GenQuest.TakePassenger.Terms2);
			pchar.GenQuest.TakePassenger.ShipType = SelectCureerShipType();
			pchar.GenQuest.TakePassenger.ShipName = GenerateRandomNameToShip(sti(pchar.GenQuest.TakePassenger.Nation));
			pchar.GenQuest.TakePassenger.Name = GenerateRandomName(sti(pchar.GenQuest.TakePassenger.Nation), "man");
			pchar.GenQuest.TakePassenger.Cannon = SelectLevelCannonParameter(sti(pchar.GenQuest.TakePassenger.ShipType));
			pchar.GenQuest.TakePassenger.Money = ((dRand(5)+drand(6)+4)*1100)+(sti(pchar.rank)*500);
			string sText = SelectPassText();
			dialog.text = "Of course. I am talking about a scoundrel by the name of "+pchar.GenQuest.TakePassenger.Name+". "+sText+" I had been looking for him for quite some time, and now I finally obtained reliable information, where he can be found. I need you to bring that man to me, by all means alive. I want to hang him in public on our town square. Are you ready to undertake this mission?";
			link.l1 = "I am ready, " + GetAddress_FormToNPC(NPChar) + ". Where can I find that scoundrel?";
		    link.l1.go = "TakePassenger_agree";
			link.l2 = "Hmm... No, I think I'll pass.";
		    link.l2.go = "All_disagree";
		break;
		
		case "TakePassenger_agree":
			npchar.greeting = NationShortName(sti(npchar.nation)) + "_gov_complete";
			pchar.GenQuest.TakePassenger.MayorId  = npchar.id; //Id мэра, чтобы знать, кто дал квест
			dialog.text = "Just in "+FindRussianDaysString(pchar.GenQuest.TakePassenger.Terms1)+", he, as a passenger on a ship by the name of '"+pchar.GenQuest.TakePassenger.ShipName+"', will sail out of "+XI_ConvertString("Colony"+pchar.GenQuest.TakePassenger.City+"Gen")+" and go to "+XI_ConvertString("Colony"+pchar.GenQuest.TakePassenger.CityA+"Acc")+". You have "+FindRussianDaysString(pchar.GenQuest.TakePassenger.Terms)+" to find this ship on the specified path segment, to board and seize already known to you bastard prisoner. If you follow this instruction, I'll pay you "+FindRussianMoneyString(sti(pchar.GenQuest.TakePassenger.Money))+". Good luck to you, captain!";
			link.l1 = "I will not waste any more time, " + GetAddress_FormToNPC(NPChar) + "! I will set sail immediately.";
			link.l1.go = "exit";
			SetFunctionTimerCondition("TakePassenger_CreateShip", 0, 0, sti(pchar.GenQuest.TakePassenger.Terms1), false);
			SetTimerCondition("AllMayorsQuests_Late", 0, 0, sti(pchar.GenQuest.TakePassenger.Terms), false);
			ReOpenQuestHeader("MayorsQuestsList");
			AddQuestRecord("MayorsQuestsList", "10");
			AddQuestUserData("MayorsQuestsList", "ColonyName", XI_ConvertString("Colony"+npchar.city+"Gen"));
			AddQuestUserData("MayorsQuestsList", "MayorName", GetFullName(npchar));
			AddQuestUserData("MayorsQuestsList", "sCity", XI_ConvertString("Colony"+pchar.GenQuest.TakePassenger.City+"Gen"));
			AddQuestUserData("MayorsQuestsList", "sCityA", XI_ConvertString("Colony"+pchar.GenQuest.TakePassenger.CityA+"Acc"));
			AddQuestUserData("MayorsQuestsList", "sDay1", FindRussianDaysString(sti(pchar.GenQuest.TakePassenger.Terms1)));
			AddQuestUserData("MayorsQuestsList", "sDay2", FindRussianDaysString(sti(pchar.GenQuest.TakePassenger.Terms)));
			AddQuestUserData("MayorsQuestsList", "sMoney", FindRussianMoneyString(sti(pchar.GenQuest.TakePassenger.Money)));
			AddQuestUserData("MayorsQuestsList", "sName", pchar.GenQuest.TakePassenger.Name);
			AddQuestUserData("MayorsQuestsList", "sShipName", pchar.GenQuest.TakePassenger.ShipName);
		break;
		
		/////////////////////////////////////////////////////////////////////////////////////////////////
		//	Таможенный патруль
		/////////////////////////////////////////////////////////////////////////////////////////////////
		case "CustomPatrol":
			//установка параметров
			pchar.GenQuest.questName = "CustomPatrol"; //тип квеста
			pchar.GenQuest.CustomPatrol.Nation = sti(npchar.nation);//нация
			pchar.GenQuest.CustomPatrol.Island = Islands[GetCharacterCurrentIsland(PChar)].id;
			pchar.GenQuest.CustomPatrol.LoginDay = rand(4)+1;
			pchar.GenQuest.CustomPatrol.Loginlocator = rand(3)+4;
			pchar.GenQuest.CustomPatrol.ShipType = SelectCureerShipType();
			pchar.GenQuest.CustomPatrol.ShipTypeA = SelectCureerShipType();
			pchar.GenQuest.CustomPatrol.Cannon = SelectLevelCannonParameter(sti(pchar.GenQuest.CustomPatrol.ShipType));
			pchar.GenQuest.CustomPatrol.Money = ((dRand(5)+drand(6)+4)*700)+(sti(pchar.rank)*300);
			dialog.text = "I got reliable information that some captain arranged about a transaction with scoundrels-contrabandists about the sale of party of slaves. As it must be known to you, such transactions by private persons in our colonies are characterized as contraband goods\nA problem consists in that I know neither exact time, nor date nor place, where contrabandists will meet. It is known only that a criminal transaction will be accomplished during the nearest five days on our island. As for spite, all my patrol ships now either on repair or involved for other tasks and can not find scoundrels\nI suggest you dealing with this task - to track down smugglers and deal with them with the most radical methods, make them an example for others. Are you ready to do this mission?";
			link.l1 = "I am ready, " + GetAddress_FormToNPC(NPChar) + ". Tell me, do you have any additional information? Like the captain's name, the name or the type of his ship?";
		    link.l1.go = "CustomPatrol_agree";
			link.l2 = "Hmm... No, I think I'll pass.";
		    link.l2.go = "All_disagree";
		break;
		
		case "CustomPatrol_agree":
			npchar.greeting = NationShortName(sti(npchar.nation)) + "_gov_complete";
			pchar.GenQuest.CustomPatrol.MayorId  = npchar.id; //Id мэра, чтобы знать, кто дал квест
			dialog.text = "My source just told me that a deal is being prepared and will be completed. That's it. So you just take a closer look at all suspicious ships within our waters. If you succeed, I will pay you a sum of "+FindRussianMoneyString(sti(pchar.GenQuest.CustomPatrol.Money))+"\nFurthermore, given the circumstances, I authorize you to pick up a whole load of contraband, which you can find. Unofficially, of course, provided that you will not sell it in our city.";
			link.l1 = "Alright, I'll get to the patrolling of the waters of your colony, " + GetAddress_FormToNPC(NPChar) + ".";
			link.l1.go = "exit";
			SetTimerCondition("AllMayorsQuests_Late", 0, 0, 6, false);
			pchar.quest.CustomPatrol.win_condition.l1 = "location";
			pchar.quest.CustomPatrol.win_condition.l1.location = pchar.GenQuest.CustomPatrol.Island;
			pchar.quest.CustomPatrol.win_condition.l2 = "Timer";
			pchar.quest.CustomPatrol.win_condition.l2.date.hour  = sti(GetTime()+rand(8));
			pchar.quest.CustomPatrol.win_condition.l2.date.day   = GetAddingDataDay(0, 0, sti(pchar.GenQuest.CustomPatrol.LoginDay));
			pchar.quest.CustomPatrol.win_condition.l2.date.month = GetAddingDataMonth(0, 0, sti(pchar.GenQuest.CustomPatrol.LoginDay));
			pchar.quest.CustomPatrol.win_condition.l2.date.year  = GetAddingDataYear(0, 0, sti(pchar.GenQuest.CustomPatrol.LoginDay));
			pchar.quest.CustomPatrol.function = "CustomPatrol_CreateShip";
			ReOpenQuestHeader("MayorsQuestsList");
			AddQuestRecord("MayorsQuestsList", "11");
			AddQuestUserData("MayorsQuestsList", "ColonyName", XI_ConvertString("Colony"+npchar.city+"Gen"));
			AddQuestUserData("MayorsQuestsList", "MayorName", GetFullName(npchar));
			AddQuestUserData("MayorsQuestsList", "sMoney", FindRussianMoneyString(sti(pchar.GenQuest.CustomPatrol.Money)));
		break;
		
		/////////////////////////////////////////////////////////////////////////////////////////////////
		//	Найти дезертира
		/////////////////////////////////////////////////////////////////////////////////////////////////
		case "FindFugitive":
			//установка параметров
			pchar.GenQuest.questName = "FindFugitive"; //тип квеста
			pchar.GenQuest.FindFugitive.Startcity = npchar.city;
			pchar.GenQuest.FindFugitive.City = SelectFugitiveCity();
			pchar.GenQuest.FindFugitive.Chance = rand(2);
			pchar.GenQuest.FindFugitive.Name = GenerateRandomName(sti(npchar.Nation), "man");
			pchar.GenQuest.FindFugitive.Money = ((dRand(5)+drand(6)+4)*1300)+(sti(pchar.rank)*600);
			sText = SelectFugitiveText();
			log_testinfo(pchar.GenQuest.FindFugitive.City);
			log_testinfo(FindRussianDaysString(sti(pchar.GenQuest.FindFugitive.Chance)));
			dialog.text = "I'll tell you everything in details. A very ugly story has occured - "+sText+". Interviewing his colleagues and friends, we believe, not without reason, that the deserter took refuge among the pirates in one of their settlements\nI suggest you visiting the pirate nest, find a fugitive, arrest and deliver here: desertion - a grave offense, and can not go unpunished. Are you ready to take this mission?";
			link.l1 = "I am ready, " + GetAddress_FormToNPC(NPChar) + ". Can you tell me the name of the deserter?";
		    link.l1.go = "FindFugitive_agree";
			link.l2 = "Hmm... No, I think I'll pass.";
		    link.l2.go = "All_disagree";
		break;
		
		case "FindFugitive_agree":
			npchar.greeting = NationShortName(sti(npchar.nation)) + "_gov_complete";
			pchar.GenQuest.FindFugitive.MayorId  = npchar.id; //Id мэра, чтобы знать, кто дал квест
			dialog.text = "Yes, of course. His name is "+pchar.GenQuest.FindFugitive.Name+". I highly doubt that he'd be wearing his uniform, so take a closer look at all sorts of scum. I give you one month for the search, because, I'm afraid, it would make no sense to search for him after that. If you succeed, I will pay you a sum of "+FindRussianMoneyString(sti(pchar.GenQuest.FindFugitive.Money))+".";
			link.l1 = "I will not waste any more time, " + GetAddress_FormToNPC(NPChar) + "! I will set sail immediately.";
			link.l1.go = "exit";
			SetTimerCondition("AllMayorsQuests_Late", 0, 0, 30, false);
			ReOpenQuestHeader("MayorsQuestsList");
			AddQuestRecord("MayorsQuestsList", "12");
			AddQuestUserData("MayorsQuestsList", "ColonyName", XI_ConvertString("Colony"+npchar.city+"Gen"));
			AddQuestUserData("MayorsQuestsList", "MayorName", GetFullName(npchar));
			AddQuestUserData("MayorsQuestsList", "sMoney", FindRussianMoneyString(sti(pchar.GenQuest.FindFugitive.Money)));
			AddQuestUserData("MayorsQuestsList", "sName", pchar.GenQuest.FindFugitive.Name);
			//создаем дезертира
			sld = GetCharacter(NPC_GenerateCharacter("Fugitive", "citiz_"+(21+rand(9)), "man", "man", sti(pchar.rank)+MOD_SKILL_ENEMY_RATE, sti(npchar.nation), 30, true, "soldier"));
			SetFantomParamFromRank(sld, sti(pchar.rank)+MOD_SKILL_ENEMY_RATE, true);
			sld.name = pchar.GenQuest.FindFugitive.Name;
			sld.lastname = "";
			sld.dialog.FileName = "MayorQuests_dialog.c";
			sld.greeting = "marginal";
		break;
		/////////////////////////////////////////////////////////////////////////////////////////////////
		//	Проникновение во враждебный город
		/////////////////////////////////////////////////////////////////////////////////////////////////
		case "Intelligence":
			dialog.text = "I see. Perhaps, a reward of " + FindRussianMoneyString(sti(pchar.GenQuest.Intelligence.Money)) + " will be a good incentive for you.";
			link.l1 = "Yeah, it's decent money... I'll accept this mission.";
		    link.l1.go = "Intelligence_agree";
			link.l2 = "Hmm... No, I think I'll refuse. It's too dangerous.";
		    link.l2.go = "All_disagree";
		break;
		case "Intelligence_agree":
			if (pchar.GenQuest.Intelligence.City == "none" || isBadReputation(pchar, 30)) //на всякий случай
			{
				dialog.text = "Although, I cannot say that I can trust you completely... I think I will not give you this mission.";
				link.l1 = "Oh well... It's a pity, but there's nothing I can do.";
				link.l1.go = "exit";
				DeleteAttribute(pchar, "GenQuest." + pchar.GenQuest.questName);
			}
			else
			{
				npchar.greeting = NationShortName(sti(npchar.nation)) + "_gov_complete";
				pchar.GenQuest.questName = "Intelligence"; //тип квеста
				sTemp = pchar.GenQuest.Intelligence.City;
				switch (rand(4))
				{
					case 0:	sTemp += "_Priest";		break;
					case 1:	sTemp += "_trader";		break;
					case 2:	sTemp += "_shipyarder"; break;
					case 3:	sTemp += "_usurer";	    break;
					case 4:	sTemp += "_PortMan";	break;
				}
				pchar.GenQuest.Intelligence.SpyId = sTemp; //Id нашего шпиона в городе
				dialog.text = "Great! Now down to business. In " + XI_ConvertString("Colony"+pchar.GenQuest.Intelligence.City+"Dat") + " you need to find a local " + GetWorkTypeOfMan(&characters[GetCharacterIndex(sTemp)], "Gen") + 
					", his name is " + GetFullName(&characters[GetCharacterIndex(sTemp)]) + ". You will tell him my name and he will give you a package of documents. For delivering this package into my hands I give you " + FindRussianDaysString(sti(pchar.GenQuest.Intelligence.Terms)) + ". And keep in mind that everything has to be done secretly. If your cover is blown, the agent will not risk attempting to make contact. Is that clear?";
				link.l1 = "Yes, I got it, " + GetAddress_FormToNPC(NPChar) + ". I will start immediately.";
				link.l1.go = "exit";
				pchar.GenQuest.Intelligence.MayorId  = npchar.id; //Id мэра, чтобы знать, кто дал квест
				SaveCurrentQuestDateParam("GenQuest.Intelligence"); //запись даты получения квеста
				ReOpenQuestHeader("MayorsQuestsList");
				AddQuestRecord("MayorsQuestsList", "6");
				AddQuestUserData("MayorsQuestsList", "ColonyName", XI_ConvertString("Colony"+npchar.city+"Gen"));
				AddQuestUserData("MayorsQuestsList", "MayorName", GetFullName(npchar));
				AddQuestUserData("MayorsQuestsList", "sCity", XI_ConvertString("Colony"+pchar.GenQuest.Intelligence.City+"Acc"));
				AddQuestUserData("MayorsQuestsList", "sIsland", XI_ConvertString(colonies[FindColony(pchar.GenQuest.Intelligence.City)].islandLable+"Dat"));
				AddQuestUserData("MayorsQuestsList", "sWho", GetWorkTypeOfMan(&characters[GetCharacterIndex(sTemp)], "Gen"));
				AddQuestUserData("MayorsQuestsList", "SpyName", GetFullName(&characters[GetCharacterIndex(sTemp)]));			
				AddQuestUserData("MayorsQuestsList", "sDay", FindRussianDaysString(sti(pchar.GenQuest.Intelligence.Terms)));
				AddQuestUserData("MayorsQuestsList", "sMoney", FindRussianMoneyString(sti(pchar.GenQuest.Intelligence.Money)));
				AddQuestUserData("MayorsQuestsList", "sCity2", XI_ConvertString("Colony"+pchar.GenQuest.Intelligence.City+"Dat"));
			}
		break;
		case "Intelligence_ExecuteLate":
			QuestName = pchar.GenQuest.questName;
			pchar.GenQuest.(QuestName).Money = sti(pchar.GenQuest.(QuestName).Money) / 2);
			dialog.text = RandPhraseSimple("Not bad. But you failed to meet the deadline, and therefore I have to cut your reward down a bit. Now your fee will be " + FindRussianMoneyString(sti(pchar.GenQuest.(QuestName).Money)) + ". Here you go.", 
				"That's good. But you failed to meet the deadline, and I've been waiting for these letters. You've spoiled my plans, and therefore I am forced to cut your reward down a bit. Still, I am happy to hand you your due reward - " + FindRussianMoneyString(sti(pchar.GenQuest.(QuestName).Money))  + ". Here you go.");
			link.l1 = "I would not say that it's nice to me, but in the end, deadlines were indeed violated. So I have no complaints, " + GetAddress_FormToNPC(NPChar) + ".";
		    link.l1.go = "All_Execute_1";
			//--> слухи
			AddSimpleRumour(RandPhraseSimple("You know, governor " + GetFullName(npchar) + " are not very pleased with the quickness of a captain " + GetMainCharacterNameGen() + ".", 
				"Governor " + GetFullName(npchar) + " is not very pleased with captain " + GetMainCharacterNameDat() + ", "+ GetSexPhrase("who","who") +" complied with his orders, but did not in due time..."), sti(npchar.nation), 5, 1);
			//<-- слухи
		break;
		
		// -------------- общий набор для всех квестов мэра ------------------
		case "All_disagree":
			dialog.text = "You're disappointing me!";
			link.l1 = "I am sorry, " + GetAddress_FormToNPC(NPChar) + ", but I can't accept this job.";
		    link.l1.go = "exit";
			ChangeCharacterComplexReputation(pchar,"nobility", -2);
			
			if (CheckAttribute(pchar, "GenQuest.questName"))
			{
				QuestName = pchar.GenQuest.questName;
				DeleteAttribute(pchar, "GenQuest." + QuestName);
				DeleteAttribute(pchar, "GenQuest.questName");
			}
		break;
		case "All_Late":
			QuestName = pchar.GenQuest.questName;
			dialog.text = RandPhraseSimple("Well, very bad - what else can I say. I counted on you - and it turns out that I've just wasted my time. I am disappointed.", 
				"Well, I must say that I am totally disappointed in you... There's a lot of folks at my residence always ready to run such errands for me - and I had wasted my time on you. Oh well...");
			link.l1 = "I am sorry, " + GetAddress_FormToNPC(NPChar) + ", I did everything I could.";
		    link.l1.go = "exit";
			//--> слухи
			AddSimpleRumour(LinkRandPhrase("You know, governor " + GetFullName(npchar) + " is very displeased with captain " + GetMainCharacterNameDat() + ". Just imagine - he failed to fulfill his assignment in time!", 
				"Governor " + GetFullName(npchar) + " is slightly annoyed that a captain " + GetFullName(pchar) + " put his shoulder to the wheel, but fail to fulfill his assignment in time. That's too bad...", 
				"I heard that governor " + GetFullName(npchar) + " is very displeased with you, captain " + GetFullName(pchar) + ", since you failed to meet the deadline while trying to fulfill his assignment."), sti(npchar.nation), 5, 1);
			//<-- слухи
			ChangeCharacterComplexReputation(pchar,"nobility", -4);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), -1);
			DeleteAttribute(pchar, "GenQuest." + QuestName);
			DeleteAttribute(pchar, "GenQuest.questName");
			npchar.greeting = NationShortName(sti(npchar.nation)) + "_gov_common"; //реплику вертаем
			SaveCurrentNpcQuestDateParam(npchar, "work_date"); //сразу еще один не даем
			CloseQuestHeader("MayorsQuestsList");
		break;
		case "All_Found":
			QuestName = pchar.GenQuest.questName;
			dialog.text = RandPhraseSimple("I am simply shocked! You've managed to locate your target but didn't care about means of ensuring your superiority - that's extreme recklessness. I am disappointed!", 
				"Well, I must say that I am disappointed in you... Finding your target is not enough - you must have means to destroy it. There are many cutthroats at my residence always ready to run such errands for me. Just what was I thinking when I turned to you?");
			link.l1 = "I am sorry, " + GetAddress_FormToNPC(NPChar) + ", but I am just not willing to recklessly risk my own life.";
		    link.l1.go = "exit";
			//--> слухи
			AddSimpleRumour(LinkRandPhrase("You know, governor " + GetFullName(npchar) + " is very displeased with captain " + GetMainCharacterNameDat() + ". Imagine, "+ GetSexPhrase("he turned out to be a downright coward","she turned out to be a downright coward") +"!", 
				"Governor " + GetFullName(npchar) + " is slightly annoyed that a captain " + GetFullName(pchar) + " took the job, but failed to carry it out because of their own indecision. Hee-hee, what wilt captains!", 
				"I heard that Governor " + GetFullName(npchar) + " very displeased with you, Captain " + GetFullName(pchar) + ". They say you're nothing but a coward"+ GetSexPhrase("","") +"..."), sti(npchar.nation), 5, 1);
			//<-- слухи
			ChangeCharacterComplexReputation(pchar,"nobility", -6);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), -1);
			DeleteAttribute(pchar, "GenQuest." + QuestName);
			DeleteAttribute(pchar, "GenQuest.questName");
			npchar.greeting = NationShortName(sti(npchar.nation)) + "_gov_common"; //реплику вертаем
			SaveCurrentNpcQuestDateParam(npchar, "work_date"); //сразу еще один не даем
			CloseQuestHeader("MayorsQuestsList");
			AddQuestRecord("MayorsQuestsList", "21");
			AddQuestUserData("MayorsQuestsList", "ColonyName", XI_ConvertString("Colony"+npchar.city+"Gen"));
			AddQuestUserData("MayorsQuestsList", "MayorName", GetFullName(npchar));
		break;
		case "All_Execute":
			QuestName = pchar.GenQuest.questName;
			dialog.text = RandPhraseSimple("Excellent news! Well, it's time to sum it all up. Your fee will be " + FindRussianMoneyString(sti(pchar.GenQuest.(QuestName).Money)) + ". Here you go.", 
				"Excellent! This way is best for everyone... Well, I am happy to hand you your due reward - " + FindRussianMoneyString(sti(pchar.GenQuest.(QuestName).Money))  + ". Here you go.");
			link.l1 = "Thank you, " + GetAddress_FormToNPC(NPChar) + ", " + RandPhraseSimple("pleasure doing business with you!", "I'm pleasantly surprised by the clarity of settlements.");
		    link.l1.go = "All_Execute_1";
			//--> слухи
			AddSimpleRumour(LinkRandPhrase("You know, governor " + GetFullName(npchar) + "  was praising for diligence"+ GetSexPhrase("a captain","a young lady") +" " + GetMainCharacterNameGen() + ".", 
				"Governor " + GetFullName(npchar) + " is praising captain " + GetMainCharacterNameGen() + ", "+ GetSexPhrase("he","she") +" is always a flawless performer when it comes to governor's assignments. An irreplaceable person for the governor, I say...", 
				"I heard that governor " + GetFullName(npchar) + " is very much pleased with you, captain " + GetFullName(pchar) + ". He defines you as a very careful and thorough officer. That's very nice to hear, captain..."), sti(npchar.nation), 5, 1);
			//<-- слухи
		break;
		case "All_Execute_1":
			QuestName = pchar.GenQuest.questName;
			dialog.text = RandPhraseSimple("Very good. You can come to see me again - perhaps, I'll find another job for you.", "Well, great! I guess I'll be offering you such jobs again.");
			link.l1 = RandPhraseSimple("Great.", "Fine.");
		    link.l1.go = "exit";
			AddMoneyToCharacter(pchar, sti(pchar.GenQuest.(QuestName).Money));
			CloseQuestHeader("MayorsQuestsList");
			ChangeCharacterComplexReputation(pchar,"nobility", 4);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 1);
			AddCharacterExpToSkill(PChar, "Leadership", 80);
			OfficersReaction("good"); // dlc
			
			DeleteAttribute(pchar, "GenQuest." + QuestName);
			DeleteAttribute(pchar, "GenQuest.questName");
			npchar.greeting = NationShortName(sti(npchar.nation)) + "_gov_common"; //реплику вертаем
			SaveCurrentNpcQuestDateParam(npchar, "work_date"); //сразу еще один не даем
			// инкремент в базу заданий мэров
			sTemp = npchar.City;
			if (!CheckAttribute(pchar, "GenQuest.MayorQuestsList." + sTemp)) pchar.GenQuest.MayorQuestsList.(sTemp) = 0;
			pchar.GenQuest.MayorQuestsList.(sTemp) = sti(pchar.GenQuest.MayorQuestsList.(sTemp)) + 1;
		break;
//<-- осады homo
		case "siege_task":
            makearef(aData, NullCharacter.Siege);
            aData.HelpColony = true;
			dialog.text = "In these dire times any help would be very welcome. We accept your aid - help us to defend the colony, and you will be rewarded.";
			link.l1 = "Then let's not waste time.";
		    link.l1.go = "exit";
		break;
		
		//Jason --> Бремя гасконца
		case "Sharlie":
			dialog.text = "You're looking for Michel de Monper? Interesting... And what do you need him for?";
			link.l1 = "I am his brother. My father told me that Michel is in trouble and needs help, so I...";
			link.l1.go = "Sharlie_1";			
		break;
		
		case "Sharlie_1":
			dialog.text = "Are you? I don't remember monsieur de Monper having any brothers... You know, monsieur, you look very suspicious to me, so I am arresting you for further investigation. Lieutenant! Detain this man!";
			link.l1 = "But Your Lordship!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Sharlie_enterSoldiers");
		break;
		
		case "Sharlie_2":
			dialog.text = "And still I would like to make amends. Here - please take this sword, this pistol and this light armour - it's my gift to you. I believe you'll find these things quite useful.";
			link.l1 = "Thank you, monsieur. Considering that they bled me white, that would come in very handy.";
			link.l1.go = "Sharlie_3";			
		break;
		
		case "Sharlie_3":
			DialogExit();
			Log_Info("You have received equipment");
			PlaySound("interface\important_item.wav");
			TakeNItems(pchar, "blade_08", 1);
			TakeNItems(pchar, "pistol1", 1);
			TakeNItems(pchar, "cirass5", 1);
			pchar.quest.Sharlie_PardonOver.over = "yes";
			DeleteAttribute(pchar, "questTemp.Sharlie.Pardon");
		break;
		//<-- Бремя гасконца
		
		//Jason --> Португалец
		case "Portugal":
			dialog.text = "Sure you can, captain! That's why I bothered you.";
			link.l1 = "Then I am all ears.";
			link.l1.go = "Portugal_1";
		break;
		
		case "Portugal_1":
			dialog.text = "Local fishermen have seen a strange vessel near the island yesterday night. As they told, it was a huge warship, without any flags or signal fires. I don't think that this ship could actually be larger than a frigate, but even that would be too much already!";
			link.l1 = "Fear takes molehills for mountains, that's for sure... but what's the point?";
			link.l1.go = "Portugal_2";
		break;
		
		case "Portugal_2":
			dialog.text = "I just turn to you, captain. My trading partners are scared by these rumors - they believe it to be pirates or Spanish raider, and it is bad for trade. Worst of all else - currently there aren't warships in the colony, only a couple of sloops for protection, and the old schooner, suitable for hunting smugglers\nAnd I can not leave it unattended... Anyway, now that the rumor about the mysterious ship is known by half of the city! Please, join with your ship to patrol - I know you as a decent captain, and even if there really is just a frigate, your guns can convince it to look for prize elsewhere!";
			link.l1 = "Monsieur... Actually, I had different plans...";
			link.l1.go = "Portugal_3";
		break;
		
		case "Portugal_3":
			dialog.text = "Please, captain! Just for a couple of days, until these uneasy gossips calm down! And you will be paid for your raid, of course. Will a sum of 10000 pesos suit you?";
			link.l1 = "Hmm... but, your Excellency, I...";
			link.l1.go = "Portugal_4";
		break;
		
		case "Portugal_4":
			dialog.text = "And we will double it, should you actually enter combat with this ship, and triple it if you sink it! Now, what do you say?";
			link.l1 = "Alright, I was planning to stay here for a couple of days anyway.";
			link.l1.go = "Portugal_5";
		break;
		
		case "Portugal_5":
			dialog.text = "Excellent, I never really doubted you, monsieur captain! Remember - just two days in our waters - and the money is yours. And if you are forced to enter battle, you will be paid according to the outcome.";
			link.l1 = "I got it, your Excellency. We have a deal, and I am returning to my ship now.";
			link.l1.go = "Portugal_6";
		break;
		
		case "Portugal_6":
			dialog.text = "I'll be waiting for your return with good news, captain!";
			link.l1 = "Allow me to take my leave.";
			link.l1.go = "Portugal_7";
		break;
		
		case "Portugal_7":
			DialogExit();
			AddQuestRecord("Portugal", "10");
			NextDiag.CurrentNode = "Portugal_8";
			LocatorReloadEnterDisable("Fortfrance_town", "reload1_back", false);
			LocatorReloadEnterDisable("Fortfrance_town", "reload2_back", false);
			LocatorReloadEnterDisable("Fortfrance_town", "gate_back", false);//открыть выходы из города
			bDisableFastReload = true;//закрыть быстрый переход
			pchar.GenQuest.CannotWait = true;//запрет ожидания
			pchar.quest.Portugal_Seapatrol.win_condition.l1 = "location";
			pchar.quest.Portugal_Seapatrol.win_condition.l1.location = "Martinique";
			pchar.quest.Portugal_Seapatrol.function = "PortugalSeapatrolGo";
			pchar.quest.Portugal_SeapatrolAvendel.win_condition.l1 = "location";
			pchar.quest.Portugal_SeapatrolAvendel.win_condition.l1.location = "Fortfrance_town";
			pchar.quest.Portugal_SeapatrolAvendel.function = "AvendelSpeach";
		break;
		
		case "Portugal_8":
			dialog.text = "Captain, I believe we had a deal that you'd be patrolling our coastal waters for two days!";
			link.l1 = "Yes, of course. I remember that.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Portugal_8";
		break;
		
		case "Portugal_9":
			dialog.text = "Well, you've done your part of the bargain. Here is your reward - 10 000 pesos, as we agreed.";
			link.l1 = "Thanks! As you can see, your apprehensions were without reason. Best of luck to you!";
			link.l1.go = "Portugal_10";
		break;
		
		case "Portugal_10":
			DialogExit();
			AddMoneyToCharacter(pchar, 10000);
			NextDiag.CurrentNode = "First time";
			pchar.quest.MartiniqueGovernorOver.over = "yes"; //снять таймер
		break;
		//<-- Португалец
		
		// Warship, 16.05.11. Генер "Правосудие на продажу".
		case "JusticeOnSale_1":
			dialog.text = "Оh " + GetAddress_Form(NPChar) + ", you've surprised me! Did those scoundrels really become so impudent? We must notify the guards immediately and send a coastal patrol there!";
			link.l1 = "I was happy to help. Can I take my leave now?";
			link.l1.go = "JusticeOnSale_2";
			
			DeleteAttribute(PChar, "GenQuest.JusticeOnSale.MayorWait");
			DeleteAttribute(PChar, "GenQuest.JusticeOnSale.PrisonWait");
			
			DeleteQuestCondition("JusticeOnSale_MapEnter");
		break;
		
		case "JusticeOnSale_2":
			dialog.text = "Of course, captain. Here - please, accept this modest reward personally from me.";
			link.l1 = "Thank you.";
			link.l1.go = "JusticeOnSale_3";
		break;
		
		case "JusticeOnSale_3":
			AddQuestRecord("JusticeOnSale", "5");
			CloseQuestHeader("JusticeOnSale");
			
			AddMoneyToCharacter(PChar, 1000 + sti(PChar.rank) * 30 * dRand(10));
			
			DeleteAttribute(PChar, "GenQuest.JusticeOnSale");
			
			DialogExit();
		break;
		
		case "JusticeOnSale_4":
			dialog.text = "You're correct, captain! We just can't leave it like that! I would ask you to head to " + XI_ConvertString(PChar.GenQuest.JusticeOnSale.ShoreId + "Acc") + ", find their ship and take their whole gang under arrest! If they resist - use force, do not hesitate!";
			link.l1 = "Allow me to take my leave.";
			link.l1.go = "JusticeOnSale_5";
		break;
		
		case "JusticeOnSale_5":
			dialog.text = "Now go. Sail there and make sure that no one will escape justice. I think that first you will need to disembark on the shore, and then you can take care of the ship.";
			link.l1 = "...";
			link.l1.go = "JusticeOnSale_6";
		break;
		
		case "JusticeOnSale_6":
			sld = GetCharacter(NPC_GenerateCharacter("JusticeOnSale_ShipPirate", "", "man", "man", sti(PChar.rank) + 5, PIRATE, -1, true, "quest"));
			sld.Ship.Type = GenerateShipExt(sti(PChar.GenQuest.JusticeOnSale.ShipType), true, sld);
			sld.Ship.Name = PChar.GenQuest.JusticeOnSale.ShipName;
			SetBaseShipData(sld);
			SetCrewQuantityFull(sld);
			Fantom_SetCannons(sld, "pirate");
			Fantom_SetBalls(sld, "pirate");
			Fantom_SetUpgrade(sld, "pirate");
			SetCaptanModelByEncType(sld, "pirate");
			SetRandGeraldSail(sld, PIRATE);
			
			Character_SetAbordageEnable(sld, false);
			
			Group_FindOrCreateGroup("JusticeOnSaleGroup");
			Group_AddCharacter("JusticeOnSaleGroup", "JusticeOnSale_ShipPirate");
			Group_SetGroupCommander("JusticeOnSaleGroup", "JusticeOnSale_ShipPirate");
			Group_SetAddress("JusticeOnSaleGroup", PChar.curislandid, "reload", Island_GetLocationReloadLocator(PChar.curislandid, PChar.GenQuest.JusticeOnSale.ShoreId));
			Group_SetTaskNone("JusticeOnSaleGroup");
			Group_LockTask("JusticeOnSaleGroup");
			
			sld.AlwaysFriend = true;
			SetCharacterRelationBoth(sti(sld.index), GetMainCharacterIndex(), RELATION_FRIEND);
			
			SetCharacterShipLocation(sld, PChar.GenQuest.JusticeOnSale.ShoreId);

			DeleteAttribute(sld, "SinkTenPercent");
			DeleteAttribute(sld, "SaveItemsForDead");
			DeleteAttribute(sld, "DontClearDead");
			DeleteAttribute(sld, "AboardToFinalDeck");
			
			sld.AlwaysSandbankManeuver = true;
			sld.AnalizeShips = true;
			sld.DontRansackCaptain = true;
			
			sld = &Locations[FindLocation(PChar.GenQuest.JusticeOnSale.ShoreId)];
			sld.DisableEncounters = true;
			
			PChar.Quest.JusticeOnSale_ShoreEnterFromMayor.win_condition.l1  = "location";
			PChar.Quest.JusticeOnSale_ShoreEnterFromMayor.win_condition.l1.location = PChar.GenQuest.JusticeOnSale.ShoreId;
			PChar.Quest.JusticeOnSale_ShoreEnterFromMayor.function = "JusticeOnSale_ShoreEnterFromMayor";
			
			PChar.Quest.JusticeOnSale_PirateShip_Sink.win_condition.l1 = "Character_sink";
			PChar.Quest.JusticeOnSale_PirateShip_Sink.win_condition.l1.character = "JusticeOnSale_ShipPirate";
			PChar.Quest.JusticeOnSale_PirateShip_Sink.function = "JusticeOnSale_PirateShip_Sink";
			
			DialogExit();
		break;
		
		case "JusticeOnSale_7":
			dialog.text = "Thank you for your help. Those scoundrels got their due. Please, allow me to present you this modest reward personally from me. I am greatly appreciating order and peace in my town.";
			link.l1 = "...";
			link.l1.go = "JusticeOnSale_8";
		break;
		
		case "JusticeOnSale_8":
			AddMoneyToCharacter(PChar, sti(PChar.rank) * 300 + dRand(1000));
			DeleteAttribute(PChar, "GenQuest.JusticeOnSale");
			DialogExit();
		break;
		//<-- Правосудие на продажу
		
			//--> Jason регата
		case "Regata":
			dialog.text = "Oh, great, glad to see you, captain! You've arrived just in time - the regatta is about to start in a few days. Have you read through the rules of the regatta, which must have been handed to you by an orderly?";
			link.l1 = "Yes, sir, I did.";
			link.l1.go = "Regata_1";
			RemoveItems(PChar, "letter_open", 1);//уберем письмо
			TakeNationLicence(HOLLAND);//уберем лицензию
			DeleteAttribute(pchar, "questTemp.Regata.ToPortRoyal"); // patch-5
		break;
		
		case "Regata_1":
			dialog.text = "And have you prepared 50000 pesos - your entrance fee, which will contribute to the prize money?";
			if (makeint(Pchar.money) >= 50000)
			{
				link.l1 = "Yes, of course. Please accept my fee.";
				link.l1.go = "Regata_2";
			}
			link.l2 = "I am a bit short of money at the moment. But I will definitely raise the required amount.";
			link.l2.go = "Regata_nomoney";
		break;
		
		case "Regata_2":
			dialog.text = "Very good. If you win - your money will back to you, and fivefold. Now you need to get better acquainted with the rules of the regatta\nAll details you can learn from Sir Henry Stivenson, he should be in a room of the residence. Go to him - he'll explain everything.";
			link.l1 = "Alright. I'll do just that.";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, -50000);
			pchar.quest.Regata_Guber.win_condition.l1 = "location";
			pchar.quest.Regata_Guber.win_condition.l1.location = "Portroyal_Roomtownhall";
			pchar.quest.Regata_Guber.function = "PrepareToRegataInPortroyal";
			pchar.questTemp.Regata.Begin = "true";
			NextDiag.TempNode = "First time";
		break;
		
		case "Regata_nomoney":
			dialog.text = "Fine, but please, don't take too long, captain. The regatta starts very soon.";
			link.l1 = "I see. I will try to bring you the money as soon as I can.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Regata_1";
			pchar.questTemp.Regata.nomoney = "true";
		break;
		
		//регата-финал
		case "Regata_Final":
			dialog.text = "And here we have the winner of the regatta! Hi, captain " + GetFullName(pchar) + "! Allow me to congratulate you on this well-deserved success! The winners of the regatta have always been popular in English colonies - and for good reason.";
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
			if (sti(pchar.rank) < 11) iGift = 0;
			if (sti(pchar.rank) >= 11 && sti(pchar.rank) < 25) iGift = 1;
			if (sti(pchar.rank) >= 25) iGift = 2;
			switch (iGift)
			{
				case 0:
					sItem1 = "blade_27"; //саксенфедер
					sItem2 = "cirass7"; //бригант
					sItem3 = "bussol";
					sAdd = "saksenfeder, brigante and boussole";
				break;
				
				case 1:
					sItem1 = "blade_20"; //мадонна
					sItem2 = "grape_mushket"; //склопетта
					sItem3 = "bussol";
					sAdd = "'Madonna', sklopetta and boussole";
				break;
				
				case 2:
					sItem1 = "blade_26"; //асоледа
					sItem2 = "cirass4"; //миланский панцирь
					sItem3 = "bussol";
					sAdd = "asoleda, Milanese cuirass and boussole";
				break;
			}
			GiveItem2Character(pchar, sItem1);
			GiveItem2Character(pchar, sItem2);
			GiveItem2Character(pchar, sItem3);
			dialog.text = "Also, you're eligible for a set of valuable prizes: "+sAdd+". Now it's all yours.";
			link.l1 = "I am very glad, sir. Really, I could not have expected it.";
			link.l1.go = "Regata_complete_2";
		break;
		
		case "Regata_complete_2":
			dialog.text = "On behalf of all subjects of the English colonies I that your for participating in the regatta and once again congratulate you on your victory! If you made a bet, it is just the time to go see sir Henry Stevenson and receive your winnings, if you hadn't done so already. Best of luck to you, captain!";
			link.l1 = "Thank you for your kind words, sir! In turn, allow me to thank you for providing me with the opportunity to participate in such grand event. And now please allow me to take my leave.";
			link.l1.go = "Regata_complete_3";
		break;
		
		case "Regata_complete_3":
			DialogExit();
			NextDiag.CurrentNode = "First time";
		break;
		//<-- регата
	}
}

string GetGangLocation(ref npchar)
{
    int n;
	string island = GetArealByCityName(npchar.city);
	string LocationId, sAreal;
	int storeArray[MAX_LOCATIONS];
    int howStore = 0;

	for(n=0; n<MAX_LOCATIONS; n++)
	{				
		if (GiveArealByLocation(&locations[n]) == island)
		{			
			//==> на всякий случай
			if (CheckAttribute(&locations[n], "DisableEncounters") && locations[n].DisableEncounters == true) continue;
			LocationId = locations[n].id;
			if (findsubstr(LocationId, "jungle" , 0) != -1 || findsubstr(LocationId, "Shore" , 0) != -1 || findsubstr(LocationId, "CaveEntrance" , 0) != -1)
			{
				storeArray[howStore] = n;
				howStore++;
			}
		}
	}
	if (howStore == 0) return "none";
	n = storeArray[dRand(howStore-1)];
	return locations[n].id;
}

string GetSpyLocation(ref npchar)
{
    aref	arCommon, arRld, arRld2;
    int	i, n, Qty, Qty2;
	string LocId; 
	string	storeArray [50];
	int howStore = 0;
    makearef(arRld, Locations[FindLocation(npchar.city + "_town")].reload);
	Qty = GetAttributesNum(arRld);
    if (CheckAttribute(pchar, "questTemp.jailCanMove.Deliver.locationId")) //если взят квест по доставке малявы
	{
		for (i=0; i<Qty; i++)
		{
    		arCommon = GetAttributeN(arRld, i);
			LocId = arCommon.go;
    		if (findsubstr(LocId, "Common" , 0) != -1 && LocId != pchar.questTemp.jailCanMove.Deliver.locationId)
    		{			
				storeArray[howStore] = LocId;
				howStore++; 
			}
			if (arCommon.label != "Sea")
			{	
				makearef(arRld2, Locations[FindLocation(LocId)].reload);
				Qty2 = GetAttributesNum(arRld2);
				for (n=0; n<Qty2; n++)
				{
    				arCommon = GetAttributeN(arRld2, n);
					LocId = arCommon.go;
					if (findsubstr(LocId, "Common" , 0) != -1 && LocId != pchar.questTemp.jailCanMove.Deliver.locationId && LocId != "CommonPackhouse_1" && LocId != "CommonPackhouse_2")
    				{
						storeArray[howStore] = LocId;
						howStore++; 					
					}
				}
			}	
		}
	}
	else
	{
		for (i=0; i<Qty; i++)
		{
    		arCommon = GetAttributeN(arRld, i);
			LocId = arCommon.go;
    		if (findsubstr(LocId, "Common" , 0) != -1)
    		{			
				storeArray[howStore] = LocId;
				howStore++; 
			}
			if (arCommon.label != "Sea")
			{	
				makearef(arRld2, Locations[FindLocation(LocId)].reload);
				Qty2 = GetAttributesNum(arRld2);
				for (n=0; n<Qty2; n++)
				{
    				arCommon = GetAttributeN(arRld2, n);
					LocId = arCommon.go;
					if (findsubstr(LocId, "Common" , 0) != -1 && LocId != "CommonPackhouse_1" && LocId != "CommonPackhouse_2")
    				{
						storeArray[howStore] = LocId;
						howStore++; 					
					}
				}
			}	
		}
	}
	if (howStore == 0) return "none";
	LocId = storeArray[dRand(howStore-1)];
	SetOpenDoorCommonLoc(npchar.city, LocId); //открываем дверь
	for(n=0; n<MAX_CHARACTERS; n++)
	{
		if (CheckAttribute(&characters[n], "locations") && characters[n].locations == LocId) 
		{			
			characters[n].lifeDay = 0;
		}
	}
	return LocId;
}

string GetSpyColony(ref NPChar)
{
    int storeArray[MAX_COLONIES];
    int howStore = 0;
	string sChrId;

	for(int n=0; n<MAX_COLONIES; n++)
	{
		if (colonies[n].nation != "none" && sti(colonies[n].nation) != PIRATE && GetRelation2BaseNation(sti(colonies[n].nation)) == RELATION_ENEMY && colonies[n].id != "Panama" && colonies[n].id != "Minentown" && colonies[n].id != "SanAndres" && colonies[n].id != npchar.City)
		{
			storeArray[howStore] = n;
			howStore++;
		}
	}
	if (howStore == 0) return "none";
	return colonies[storeArray[Rand(howStore-1)]].id;
}

int SelectCureerShipType()
{
	int iShipType;
	if(sti(pchar.rank) >= 14)
	{
		iShipType = SHIP_CORVETTE + rand(makeint(SHIP_POLACRE - SHIP_CORVETTE));
	}
	if(sti(pchar.rank) >= 6 && sti(pchar.rank) < 14)
	{
		iShipType = SHIP_BRIGANTINE + rand(makeint(SHIP_SCHOONER_W - SHIP_BRIGANTINE));
	}
	if(sti(pchar.rank) < 6)
	{
		iShipType = SHIP_CAREERLUGGER + rand(makeint(SHIP_SLOOP - SHIP_CAREERLUGGER));
	}
	return iShipType;
}

int SelectArsenalShipType()
{
	int iShipType;
	if(sti(pchar.rank) >= 18)
	{
		iShipType = SHIP_GALEON_H;
	}
	if(sti(pchar.rank) >= 14 && sti(pchar.rank) < 18)
	{
		iShipType = SHIP_GALEON_L;
	}
	if(sti(pchar.rank) >= 8 && sti(pchar.rank) < 14)
	{
		iShipType = SHIP_CARAVEL + rand(makeint(SHIP_CARACCA - SHIP_CARAVEL));
	}
	if(sti(pchar.rank) >= 4 && sti(pchar.rank) < 8)
	{
		iShipType = SHIP_SCHOONER + rand(makeint(SHIP_FLEUT - SHIP_SCHOONER));
	}
	if(sti(pchar.rank) < 4)
	{
		iShipType = SHIP_BARQUE;
	}
	return iShipType;
}

string SelectPassText()
{
	string sText;
	switch (drand(5))
	{
		case 0: sText = "That Judas, using his position, sold an important state secret to an enemy power."; break;
		case 1: sText = "That foul scoundrel killed his relative, a well-known and noble man, in order to inherit his fortune."; break;
		case 2: sText = "That foul scoundrel insulted my family and me personally."; break;
		case 3: sText = "This thieving rogue stole a decent sum of money from our city's treasury."; break;
		case 4: sText = "That villain is guilty of deaths of nearly a dozen of our citizens."; break;
		case 5: sText = "That rogue used his connection to take possession of a merchant vessel, and then he stole it and sold at the neighboring shipyard."; break;
	}
	return sText;
}

string SelectFugitiveCity()
{
	string sCity;
	switch (rand(3))
	{
		case 0: sCity = "LaVega"; break;
		case 1: sCity = "PuertoPrincipe"; break;
		case 2: sCity = "LeFransua"; break;
		case 3: sCity = "FortOrange"; break;
	}
	return sCity;
}

string SelectFugitiveText()
{
	string sText;
	switch (drand(5))
	{
		case 0: sText = "one of the junior officers in our garrison has thrown up his service and left the colony on board of a merchant ship."; break;
		case 1: sText = "one of our officers deserted right on duty and escaped on board of a smuggler ship."; break;
		case 2: sText = "one of our naval officers serving on a patrol brig deserted for unknown reason, hijacked a long boat and disappeared on it."; break;
		case 3: sText = "one of our prison guards threw up his service for  unknown reason and left our colony on board of a private vessel."; break;
		case 4: sText = "one of the soldiers in our garrison abandoned his post while keeping guard, went to the cove and left this place on board of an unknown vessel."; break;
		case 5: sText = "one of our military officers, captain of a patrol lugger, abandoned his ship at the open sea and went south on a fishing long boat."; break;
	}
	return sText;
}
