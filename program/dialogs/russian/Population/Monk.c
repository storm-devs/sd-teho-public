//Jason общий диалог уличных монахов
#include "DIALOGS\russian\Rumours\Common_rumours.c"
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i, iTemp, iTest;
	string sTemp, sTitle;

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
	
	iTest = FindColony(NPChar.City);
    ref rColony;
	if (iTest != -1)
	{
		rColony = GetColonyByIndex(iTest);
	}
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			//--> диалог первой встречи
			if (npchar.quest.meeting == "0")
			{
				if (CheckAttribute(npchar, "quest.donation"))//пожертвования
				{
					dialog.text = "Good day to you, my son. I ask you to show some favor and to donate a few silver coins for a good deed.";
					link.l1 = "Well, I suppose that we all have to donate for good deeds... The Church learns us to help each other. And can you tell me any details about that deed of yours?";
					link.l1.go = "donation";
					link.l2 = "Forgive me, holy father, but my purse won't survive this.";
					link.l2.go = "exit";
					npchar.quest.meeting = "1";
					DeleteAttribute(npchar, "talker"); //снимаем говорилку
					break;
				}
				bool ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
				if (ok && sti(Pchar.Ship.Type) != SHIP_NOTUSED && CheckAttribute(npchar, "quest.passenger") && !CheckAttribute(pchar, "GenQuest.Monkpassenger") && 6-sti(RealShips[sti(Pchar.Ship.Type)].Class) > 0 && 6-sti(RealShips[sti(Pchar.Ship.Type)].Class) < 3)//монах-пассажир
				{
					dialog.text = "Good day to you, my son. I'd like to ask you to do a favor. It will be paid.";
					link.l1 = "I am listening to you, holy father. What do you need?";
					link.l1.go = "passenger";
					link.l2 = "I am so sorry, padre, but I have to go.";
					link.l2.go = "exit";
					npchar.quest.meeting = "1";
					DeleteAttribute(npchar, "talker"); //снимаем говорилку
					break;
				}
				if (sti(Pchar.Ship.Type) != SHIP_NOTUSED && CheckAttribute(npchar, "quest.capellan") && !CheckAttribute(pchar, "questTemp.ShipCapellan"))//корабельный капеллан
				{
					dialog.text = "Greetings, my son. I take it that you are a captain. So I have a proposal for you.";
					link.l1 = "I am listening, holy father.";
					link.l1.go = "capellan";
					npchar.quest.meeting = "1";
					DeleteAttribute(npchar, "talker"); //снимаем говорилку
					break;
				}
				dialog.text = PCharRepPhrase(LinkRandPhrase("Greetings, my son. What troubles have brought you to me?","Greetings, my son. See the head of church if you want to confess.","Greetings, my son. Face the God until it's too late."),LinkRandPhrase("Greetings, my son. What troubles have brought you to me?","Good day to you, my son, let your deeds be blessed by the God!","Good day to you, my son, may the God's blessings sign you!"));
				link.l1 = LinkRandPhrase("Same to you, holy father. How are you doing?","Good day to you, holy father. How is your parish?","How are you, holy father?");
				link.l1.go = "check";//на возможную выдачу квестов
				link.l2 = RandPhraseSimple("I have a question for you, holy father.", "I need information.");
				link.l2.go = "quests";//(перессылка в файл города)
				if (GetSquadronGoods(pchar, GOOD_SLAVES) > 0 && sti(pchar.money) >= GetSquadronGoods(pchar, GOOD_SLAVES)*10)
				{
					link.l3 = "Holy father, I've got people on my ship. They are enslaved Christians and non-baptized. I want you to baptize the non-baptized and to administer communion to Christians.  I will free them all after that for the glory of our Church.";
					link.l3.go = "slaves";
				}
				if (sti(Pchar.Ship.Type) != SHIP_NOTUSED && sti(pchar.reputation.nobility) > 41 && !CheckAttribute(pchar, "GenQuest.Shipshine") && 6-sti(RealShips[sti(Pchar.Ship.Type)].Class) > 0)
				{
					link.l4 = "Holy father, I want you to sanctify my ship. How much will it cost to me?";
					link.l4.go = "shipshine";
				}
				link.l10 = LinkRandPhrase("Pardon, holy father, but I have to go.","Sorry for troubling you, holy father.","I need to go to my ship, holy father. Farewell!");
				link.l10.go = "exit";
				npchar.quest.meeting = "1";
			}
			else
			{
				//--> диалог второй встречи
				dialog.text = LinkRandPhrase("You again, my son? What do you want?","Have anything more to tell me, my son?","It is good to see you again, my son.");
				link.l1 = LinkRandPhrase("Same to you, holy father. How are you doing?","Good day to you, holy father. How is your parish?","How are you, holy father?");
				link.l1.go = "check";//на возможную выдачу квестов
				link.l2 = RandPhraseSimple("I have a question for you, holy father.", "I need information.");
				link.l2.go = "quests";//(перессылка в файл города)
				if (GetSquadronGoods(pchar, GOOD_SLAVES) > 0 && sti(pchar.money) >= GetSquadronGoods(pchar, GOOD_SLAVES)*10 && !CheckAttribute(npchar, "quest.slaves"))
					{
						link.l3 = "Holy father, I've got people on my ship. They are enslaved Christians and non-baptized. I want you to baptize the non-baptized and to administer communion to Christians.  I will free them all after that for the glory of our Church.";
						link.l3.go = "slaves";
					}
				if (sti(Pchar.Ship.Type) != SHIP_NOTUSED && sti(pchar.reputation.nobility) > 41 && !CheckAttribute(pchar, "GenQuest.Shipshine") && 6-sti(RealShips[sti(Pchar.Ship.Type)].Class) > 0)
				{
					link.l4 = "Holy father, I want you to sanctify my ship. How much will it cost to me?";
					link.l4.go = "shipshine";
				}
				link.l10 = LinkRandPhrase("Pardon, holy father, but I have to go.","Sorry for troubling you, holy father.","I need to go to my ship, holy father. Farewell!");
				link.l10.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "check":
			if (sti(Pchar.Ship.Type) != SHIP_NOTUSED && rand(8) < 3 && !CheckAttribute(npchar, "quest.monkletter") && !CheckAttribute(pchar, "GenQuest.Monkletter") && !CheckAttribute(npchar, "quest.passenger")) //церковная депеша
			{
				pchar.GenQuest.Monkletter.City = FindFriendCityToMC(false);
				pchar.GenQuest.Monkletter.StartCity = npchar.city;//город квестодателя
				dialog.text = "I have an ask for you, my son. I need to deliver these papers to the head of church of  "+XI_ConvertString("Colony"+pchar.GenQuest.Monkletter.City+"Gen")+". Do you sail in that direction? The documents must be delivered in two weeks...";
				link.l1 = "Easy enough, holy father. Give me those papers and I will deliver them to "+XI_ConvertString("Colony"+pchar.GenQuest.Monkletter.City+"Gen")+".";
				link.l1.go = "Monkletter";
				link.l2 = "I'd be glad to do it, holy father, but I am sailing in another direction.";
				link.l2.go = "exit_monkletter";
				npchar.quest.monkletter = "true";
				break;
			}
			if (sti(Pchar.Ship.Type) != SHIP_NOTUSED && rand(8) > 5 && sti(pchar.rank < 11) && !CheckAttribute(npchar, "quest.churchbooks") && !CheckAttribute(pchar, "GenQuest.Churchbooks") && !CheckAttribute(npchar, "quest.passenger")) //привезти молитвенники
			{
				pchar.GenQuest.Churchbooks.StartCity = npchar.city;//город квестодателя
				pchar.GenQuest.Churchbooks.Nation = npchar.nation;
				dialog.text = "My son, would you agree to help me in an urgent matter? Our church is running low on prayer books which we giveaway to each who need them\nCould you sail to the nearest colony "+NationNameGenitive(sti(npchar.nation))+", to take a few prayer books from the local church and bring them here? And try to do that in one month, we don't have many our prayer books left.";
				link.l1 = "I'll help your church with pleasure. Can I get these books from any head of church?";
				link.l1.go = "Churchbooks";
				link.l2 = "I'd be glad to it, holy father, but I can't do it now.";
				link.l2.go = "exit_churchbooks";
				npchar.quest.churchbooks = "true";
				break;
			}
			
			dialog.text = RandPhraseSimple("It's alright, my son. Thank you for taking care about our church.", "Our parish is fine, my son. Thank you for your concerns.");
			link.l1 = "I have to go then. Holy father.";
			link.l1.go = "exit";
		break;
		
//-------------------------------------------------пожертвования------------------------------------------------
		case "donation":
			sTemp = DonationType();
			dialog.text = "Sure, my son. "+sTemp+"";
			link.l1 = "What donation would be considered as sufficient?";
			link.l1.go = "donation_1";
		break;
		
		case "donation_1":
			dialog.text = "It all depends on you purse and personal wish, my son. I'd be grateful for any donation.";
			link.l1 = "100 pesos";
			link.l1.go = "donation_rate_1";
			link.l2 = "1000 pesos";
			link.l2.go = "donation_rate_2";
			link.l3 = "5000 pesos";
			link.l3.go = "donation_rate_3";
			link.l4 = "10000 pesos";
			link.l4.go = "donation_rate_4";
		break;
		
		case "donation_rate_1"://никаких плюшек
			if (sti(pchar.money) >= 100)
			{
				AddMoneyToCharacter(pchar, -100);
				dialog.text = "Thank you for your coins, my son! They will go for a good cause!";
				link.l1 = "You're welcome, holy father.";
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = "God's retribution is waiting for you, the wicked! Mocking on the servant of the holy church is a blasphemy!";
				link.l1 = "Ha-ha! I don't do charity. Get lost!";
				link.l1.go = "donation_exit";
			}
		break;
		
		case "donation_rate_2":
			if (sti(pchar.money) >= 1000)
			{
				AddMoneyToCharacter(pchar, -1000);
				dialog.text = "I thank you, my son. This sum will really help in my holy initiatives. Bless on you!";
				link.l1 = "Good luck on your uneasy task, holy father!";
				link.l1.go = "exit";
				AddCharacterHealth(pchar, 5);
				AddCharacterExpToSkill(pchar, "Leadership", 20);
				AddCrewMorale(pchar, 2);
			}
			else
			{
				dialog.text = "God's retribution is waiting for you, the wicked! Mocking on the servant of the holy church is a blasphemy!";
				link.l1 = "Ha-ha! I don't do charity. Get lost!";
				link.l1.go = "donation_exit";
			}
		break;
		
		case "donation_rate_3":
			if (sti(pchar.money) >= 5000)
			{
				AddMoneyToCharacter(pchar, -5000);
				dialog.text = "I couldn't even hope that you would be that generous, my son. I bless you and accept your money gratefully.";
				link.l1 = "Money's no object until it can be used for good deeds. Good luck, holy father!";
				link.l1.go = "exit";
				AddCharacterHealth(pchar, 5);
				AddCharacterExpToSkill(pchar, "Leadership", 40);
				AddCrewMorale(pchar, 3);
				ChangeCharacterComplexReputation(pchar, "nobility", 1);
				ChangeCharacterNationReputation(pchar, sti(npchar.Nation), 1);
			}
			else
			{
				dialog.text = "God's retribution is waiting for you, the wicked! Mocking on the servant of the holy church is a blasphemy!";
				link.l1 = "Ha-ha! I don't do charity. Get lost!";
				link.l1.go = "donation_exit";
			}
		break;
		
		case "donation_rate_4":
			if (sti(pchar.money) >= 10000)
			{
				AddMoneyToCharacter(pchar, -10000);
				dialog.text = "Have I heard you right? Do you really donate ten thousands? I bless you and accept your money gratefully. This is a huge help for the holy deed!";
				link.l1 = "We all have to help the holy church. I can afford to spend such sum and I am gladly giving it to you. Good luck, holy father.";
				link.l1.go = "exit";
				AddCharacterHealth(pchar, 10);
				AddCharacterExpToSkill(pchar, "Leadership", 60);
				AddCrewMorale(pchar, 5);
				ChangeCharacterComplexReputation(pchar, "nobility", 1);
				ChangeCharacterNationReputation(pchar, sti(npchar.Nation), 2);
				ChangeCrewExp(pchar, "Sailors", 5);
				ChangeCrewExp(pchar, "Cannoners", 5);
				ChangeCrewExp(pchar, "Soldiers", 5);
			}
			else
			{
				dialog.text = "God's retribution is waiting for you, the wicked! Mocking on the servant of the holy church is a blasphemy!";
				link.l1 = "Ha-ha! I don't do charity. Get lost!";
				link.l1.go = "donation_exit";
			}
		break;
		
		case "donation_exit":
			DialogExit();
			ChangeCharacterComplexReputation(pchar, "nobility", -1);
			AddCharacterHealth(pchar, -5);
			LAi_CharacterDisableDialog(npchar);
		break;
		
//-------------------------------------------отпустить рабов---------------------------------------------------
		case "slaves":
			dialog.text = "Sure , my son. It's our duty to help the sufferers. I will do what you ask for.";
			link.l1 = "Thank you, holy father. I will donate ten silver coins for each baptized and administered prisoner.";
			link.l1.go = "slaves_1";
		break;
		
		case "slaves_1":
			AddMoneyToCharacter(pchar, -GetSquadronGoods(pchar, GOOD_SLAVES)*10);
			dialog.text = "It is great that you don't forget about some pecuniary thank. Your money will be used for a good cause. Let's go to your ship?";
			link.l1 = "Yes, padre. Follow me.";
			link.l1.go = "slaves_2";
		break;
		
		case "slaves_2":
			npchar.quest.slaves = "true";
			DialogExit();
			SetLaunchFrameFormParam("Two hours later"+ NewStr() +"Slaves were freed", "Monk_RemoveSlaves", 0, 4);
			LaunchFrameForm();
			WaitDate("", 0, 0, 0, 2, 10); //крутим время
			RecalculateJumpTable();
		break;
//<-- отпустить рабов

//----------------------------------------------освятить корабль------------------------------------------------
		case "shipshine":
			//поиск старшего класса
			iTemp = 6;
			for (i=0; i<COMPANION_MAX; i++)
			{
				int iIdx = GetCompanionIndex(GetMainCharacter(), i);
				if (iIdx >= 0)
				{
					sld = GetCharacter(iIdx);
					if (GetCharacterShipClass(sld) < iTemp) iTemp = GetCharacterShipClass(sld);
				}
			}
			switch (GetCompanionQuantity(pchar))
			{
				case 1: 
					sTemp = "I have only one ship in my squadron and it's "+iTemp+" rank.";
					pchar.GenQuest.Shipshine.Money = 5000*(6-iTemp);
				break;
				case 2:
					sTemp = "I have two ships in my squadron and the biggest one is "+iTemp+" rank.";
					pchar.GenQuest.Shipshine.Money = makeint(1.8*(5000*(6-iTemp)));
				break;
				case 3:
					sTemp = "I have three ships in my squadron and the biggest one is "+iTemp+" rank.";
					pchar.GenQuest.Shipshine.Money = makeint(2.6*(5000*(6-iTemp)));
				break;
				case 4:
					sTemp = "I have four ships in my squadron and the biggest one is "+iTemp+" rank.";
					pchar.GenQuest.Shipshine.Money = makeint(3.4*(5000*(6-iTemp)));
				break;
				case 5:
					sTemp = "I have five ships in my squadron and the biggest one is "+iTemp+" rank.";
					pchar.GenQuest.Shipshine.Money = makeint(4.2*(5000*(6-iTemp)));
				break;
			}
			dialog.text = "It all depends on the total amount of ships in your squadron and their size.";
			link.l1 = ""+sTemp+"";
			link.l1.go = "shipshine_1";
		break;
		
		case "shipshine_1":
			dialog.text = "It will cost you "+FindRussianMoneyString(sti(pchar.GenQuest.Shipshine.Money))+", my son.";
			if (sti(pchar.money) >= sti(pchar.GenQuest.Shipshine.Money))
			{
				link.l1 = "I can pay you this sum, padre. Take the money.";
				link.l1.go = "shipshine_2";
			}
			link.l2 = "Unfortunately, I don't have such a sum.";
			link.l2.go = "shipshine_exit";
		break;
		
		case "shipshine_2":
			AddMoneyToCharacter(pchar, -sti(pchar.GenQuest.Shipshine.Money));
			dialog.text = "Very well, my son. Let's don't waste time and go to the port.";
			link.l1 = "Follow me, holy father.";
			link.l1.go = "shipshine_3";
		break;
		
		case "shipshine_3":
			DialogExit();
			SetLaunchFrameFormParam("Several hours later"+ NewStr() +"Padre has committed a consecration", "Monk_Shipshine", 0, 4);
			LaunchFrameForm();
			WaitDate("", 0, 0, 0, GetCompanionQuantity(pchar), 10); //крутим время
			RecalculateJumpTable();
		break;
		
		case "shipshine_exit":
			DialogExit();
			DeleteAttribute(Pchar, "GenQuest.Shipshine");
		break;
//<-- освятить корабль

//------------------------------------------корабельный капеллан-----------------------------------------------
		case "capellan":
			dialog.text = "I am the ship's chaplain and I have some experience in this. I have retired from my last job because of my moral concerns. I am looking for a new ship to employ. Do you want to take me in your crew?";
			link.l1 = "Priest of the ship? Tell me, padre, what would be your job like on my ship?";
			link.l1.go = "capellan_1";
			pchar.questTemp.ShipCapellan = "true";
		break;
		
		case "capellan_1":
			dialog.text = "My son, it is quite obvious. I pray to the God for you and your crew, bless your sailors before fighting, my word grants strength to their hands and spirits. Your crew will have an opportunity to receive a communion and a confession on a regular basis, a sailor with a refined soul will survive the situation the impious one will not\nI ask not much for myself: a single payment of fifty thousand pesos, a bunk in a cabin and a board same to your officers have. That would be all.";
			if (sti(pchar.money) >= 50000)
			{
				link.l1 = "It's interesting... You are right, a good captain must carry about not only his crew's bodies but about their souls too. Welcome aboard, padre!";
				link.l1.go = "capellan_2";
			}
			link.l2 = "No, padre. I am sorry but I can't afford your services.";
			link.l2.go = "capellan_exit";
		break;
		
		case "capellan_exit":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
		break;
		
		case "capellan_2":
			AddMoneyToCharacter(pchar, -50000);
			chrDisableReloadToLocation = true;//закрыть локацию
			dialog.text = "Thank you for your trust, my son. You have spent your money wisely. But I warn you, I serve only worthy captains, either trader or caper, no matter. But I will never preach aboard of pirate ship!\nSo if you will ever raise Jolly Roger I will immediately leave your vessel in the very first port.";
			link.l1 = "I will consider that, holy father, and I'll try to not disappoint you. Now, would you be kindly to go aboard on my ship!";
			link.l1.go = "capellan_3";
		break;
		
		case "capellan_3":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "My_Campus", "rld", "loc1", "Monk_Capellan", -1);
			pchar.questTemp.ShipCapellan.id = npchar.id;
			DeleteAttribute(npchar, "LifeDay");
			DeleteAttribute(npchar, "CityType");//удалить признак фантома
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, false);
			pchar.questTemp.ShipCapellan.Yes = "true";//капеллан в команде
			ChangeCharacterComplexReputation(pchar, "authority", 5);
			npchar.reputation = 60;
		break;
		
		case "capellan_4":
			dialog.text = "Want anything, my son?";
			link.l1 = "No, it's nothing, holy father.";
			link.l1.go = "exit";
			link.l2 = "Padre, I'd like you to leave the ship in the next port. Let me not explain the reasons of my decision.";
			link.l2.go = "capellan_5";
			NextDiag.TempNode = "capellan_4";
		break;
		
		case "capellan_5":
			dialog.text = "It's alright, my son. You are in charge here. I will leave your ship in the next settlement.";
			link.l1 = "Thank you for your understanding, holy father.";
			link.l1.go = "capellan_6";
		break;
		
		case "capellan_6":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			ShipCapellan_Remove();
		break;
		
		case "capellan_7":
			dialog.text = "I have warned you, captain, that I would leave you if you raise the pirate flag! I'll leave your ship in the nearest port.";
			link.l1 = "Hm...";
			link.l1.go = "exit";
			NextDiag.TempNode = "capellan_7";
		break;
//<-- капеллан
	
//--------------------------------------------монах-пассажир---------------------------------------------------
		case "passenger":
			if (drand(19) < 15) SetPassengerParameter("Monkpassenger", false);
			else SetPassengerParameter("Monkpassenger", true);
			dialog.text = "My son, I have to get to " + XI_ConvertString("Colony"+pchar.GenQuest.Monkpassenger.City)+" it is on "+XI_ConvertString(GetIslandByCityName(pchar.GenQuest.Monkpassenger.City)+"Dat")+", for "+FindRussianDaysString(sti(pchar.GenQuest.Monkpassenger.DaysQty))+". I'll pay you "+FindRussianMoneyString(sti(pchar.GenQuest.Monkpassenger.Money))+" for that. What do you say?";
			link.l1 = "I agree, holy father.";
			link.l1.go = "passenger_1";
			link.l2 = "I am sorry, holy father, but I am sailing in a different direction. Can't help you.";
			link.l2.go = "passenger_exit";
			npchar.quest.passenger = true;
		break;
		
		case "passenger_exit":
			dialog.text = "It is the God's will for all, my son. I'll wait for another ship. Peace on you!";
			link.l1 = "Farewell, padre.";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "GenQuest.Monkpassenger");
		break;
		
		case "passenger_1":
			dialog.text = "I thank you. You will get your payment when we get the destination.";
			link.l1 = "Go to my ship, holy father. We are leaving soon.";
			link.l1.go = "passenger_2";
		break;
		
		case "passenger_2":
			DialogExit();
			pchar.GenQuest.Monkpassenger.id = npchar.id;
			DeleteAttribute(npchar, "LifeDay");
			LAi_RemoveLoginTime(npchar);
			DeleteAttribute(npchar, "CityType");//удалить признак фантома, иначе - пустые города
			LAi_SetImmortal(npchar, true);
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
			AddQuestUserDataForTitle(sTitle, "sType", "monk");
			AddQuestUserDataForTitle(sTitle, "sName", GetFullName(npchar));
			sTemp = XI_ConvertString("Colony" +pchar.GenQuest.Monkpassenger.City+"Gen") + ", which is on " + XI_ConvertString(GetIslandByCityName(pchar.GenQuest.Monkpassenger.City)+"Dat")+".";
			AddQuestUserDataForTitle(sTitle, "sCity", sTemp);
			AddQuestUserData(sTitle, "sName", GetFullName(npchar));
			AddQuestUserData(sTitle, "sCity", sTemp);
			AddQuestUserData(sTitle, "sDays", FindRussianDaysString(sti(pchar.GenQuest.Monkpassenger.DaysQty)));
            AddQuestUserData(sTitle, "sMoney", FindRussianMoneyString(sti(pchar.GenQuest.Monkpassenger.Money)));
			AddQuestUserData(sTitle, "sName", GetFullName(npchar));
			pchar.quest.Monkpassenger.win_condition.l1 = "location";
			pchar.quest.Monkpassenger.win_condition.l1.location = pchar.GenQuest.Monkpassenger.City+"_town";
			pchar.quest.Monkpassenger.function = "Monkpassenger_complete";
			SetFunctionTimerCondition("Monkpassenger_Over", 0, 0, sti(pchar.GenQuest.Monkpassenger.DaysQty), false);
		break;
		
		case "passenger_3":
			pchar.quest.Monkpassenger_Over.over = "yes"; //снять таймер
			dialog.text = "Thank you, my son. You have fulfilled your promise and it's my turn now. Take your money as I promised.";
			link.l1 = "Thank you. Good luck, holy father.";
			link.l1.go = "passenger_4";
		break;
		
		case "passenger_4":
			DialogExit();
			npchar.lifeday = 0;
			RemovePassenger(Pchar, npchar);
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload4_back", "none", "", "", "", 20.0);
			AddMoneyToCharacter(pchar, sti(pchar.GenQuest.Monkpassenger.Money));
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
			ChangeCharacterComplexReputation(pchar, "fame", 1);
			OfficersReaction("good");				
			AddCharacterExpToSkill(pchar, "Sailing", 80);
			AddCharacterExpToSkill(pchar, "Leadership", 20);
			if (CheckAttribute(pchar, "GenQuest.Monkpassenger.Enemycity")) AddCharacterExpToSkill(pchar, "Sneak", 50);
			sTitle = npchar.index+"Citizpassenger";
			AddQuestRecordEx(sTitle, "Citizpassenger", "3");
			CloseQuestHeader(sTitle);
			DeleteAttribute(Pchar, "GenQuest.Monkpassenger");
		break;
//<-- монах-пассажир
		
//---------------------------------------------церковная депеша-------------------------------------------------
		case "exit_monkletter":
			DialogExit();
			DeleteAttribute(pchar, "GenQuest.Monkletter");
		break;
		
		case "Monkletter":
			dialog.text = "Here. Take this package, my son. Remember that you have only two weeks to deliver it. The prior is really waiting for it. Go, and may God be with you!";
			link.l1 = "I won't fail you, holy father. Farewell.";
			link.l1.go = "Monkletter_1";
		break;
		
		case "Monkletter_1":
			DialogExit();
			GiveItem2Character(pchar, "letter_church");
			ReOpenQuestHeader("Monkletter");
			AddQuestRecord("Monkletter", "1");
			AddQuestUserData("Monkletter", "sCity", XI_ConvertString("Colony"+pchar.GenQuest.Monkletter.City+"Gen"));
			AddQuestUserData("Monkletter", "sStartCity", XI_ConvertString("Colony"+pchar.GenQuest.Monkletter.StartCity));
			SetFunctionTimerCondition("Monkletter_Over", 0, 0, 15, false);
			OfficersReaction("good");
		break;
//<-- Церковная депеша
		
//-------------------------------------------доставить молитвенники---------------------------------------------
		case "exit_churchbooks":
			DialogExit();
			DeleteAttribute(pchar, "GenQuest.Churchbooks");
		break;

		case "Churchbooks":
			dialog.text = "Yes. You can get them in any colony "+NationNameGenitive(sti(npchar.nation))+". Bring all books what you'll find to our holy father in the church. May God bless you!";
			link.l1 = "Thanks! You will receive prayer books soon.";
			link.l1.go = "Churchbooks_1";
		break;
		
		case "Churchbooks_1":
			DialogExit();
			ReOpenQuestHeader("Churchbooks");
			AddQuestRecord("Churchbooks", "1");
			AddQuestUserData("Churchbooks", "sNation", NationNameGenitive(sti(pchar.GenQuest.Churchbooks.Nation)));
			AddQuestUserData("Churchbooks", "sStartCity", XI_ConvertString("Colony"+pchar.GenQuest.Churchbooks.StartCity));
			SetFunctionTimerCondition("Churchbooks_Over", 0, 0, 30, false);
			pchar.GenQuest.Churchbooks = "go";
			switch (rand(4))
			{
				case 0: pchar.GenQuest.Churchbooks.Item = "amulet_2"; break;
				case 1: pchar.GenQuest.Churchbooks.Item = "amulet_3"; break;
				case 2: pchar.GenQuest.Churchbooks.Item = "amulet_6"; break;
				case 3: pchar.GenQuest.Churchbooks.Item = "amulet_7"; break;
				case 4: pchar.GenQuest.Churchbooks.Item = "amulet_10"; break;
			}
			OfficersReaction("good");
		break;
//<-- доставить молитвенники
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}

string DonationType()
{
	string sText;
	switch (drand(9))
	{
		case 0: sText = "I am gathering money for building "+LinkRandPhrase("a chapel","an almshouse","an infirmary")+". Local citizens give little in alms so I have to ask from prosperous people like you." break;
		case 1: sText = "I am gathering donations for our church. Sailors don't usually have much time to visit a temple of God, but everyone have to try in saving his own soul." break;
		case 2: sText = "I am gathering money to buy medicines for our asylum. It's for poor and infirm. Donate because all of us can end there." break;
		case 3: sText = "I am gathering money for new church utensils, the ones which was brought from Europe are almost out of use by now. It's a duty for every Christian to take care about his church." break;
		case 4: sText = "I am gathering money for the church's renovation, the roof can't hold a small rain and benches have to be repaired too. It's a duty for every Christian to take care about his church." break;
		case 5: sText = "I am gathering money to pay to the good artist who is able to paint the walls of our church and draw scenes from the Bible on them. It's a duty for every Christian to take care about his church." break;
		case 6: sText = "I am gathering money for a new iconostasis for our church. Our parish is poor and it's too difficult to do. I do hope for your help." break;
		case 7: sText = "There are a lot of wounded sailors from the warship in our infirmary. They need medicines and bandages. Help them, only you can really understand sufferings of the common sailors." break;
		case 8: sText = "I am trying to get money for cloth and food for our poorest citizens. The only hope they have is our holy church. Help them." break;
		case 9: sText = "I am going to go deep in our island for a missionary work to bring light for the lost souls. I am gathering funds for this expedition. Help our good deed!" break;
	}
	return sText;
}