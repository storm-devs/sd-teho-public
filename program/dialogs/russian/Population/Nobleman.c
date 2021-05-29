//Jason общий диалог дворян
#include "DIALOGS\russian\Rumours\Common_rumours.c"
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int iTemp, iTest;
	string sTemp, sTitle;
	float locx, locy, locz;

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
	
	iTest = FindColony(NPChar.City); // 170712
    ref rColony;
	if (iTest != -1)
	{
		rColony = GetColonyByIndex(iTest);
	}
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			//--> проверка межнациональных отношений
				if (sti(NPChar.nation) != PIRATE && GetNationRelation2MainCharacter(sti(NPChar.nation)) == RELATION_ENEMY)
				{
				dialog.text = NPCStringReactionRepeat("Hm. You are sailing under the flag of "+NationNameGenitive(sti(pchar.nation))+", buddy. What the hell are you doing here, in our town? Get lost!", 
					"I don't want to be suspected as a friend of "+NationNameAblative(sti(pchar.nation))+"! Get lost or I will report to the guards!", 
					"It's your last chance to get away. Otherwise you'll have only yourself to blame.",
					"I have warned you. Now you will pay for you impudence, bastard!", "block", 1, npchar, Dialog.CurrentNode);
				link.l1 = HeroStringReactionRepeat("Such a patriot, ha!", 
					"Fine, fine, calm down. I am leaving.",
					"Don't make so much noise. I am leaving.", 
					"What?!", npchar, Dialog.CurrentNode);
				link.l1.go = DialogGoNodeRepeat("exit", "", "", "fight", npchar, Dialog.CurrentNode);
			break;
			}
			
			//--> проверка репутации - дворяне гнобят супернегодяев
			if (sti(pchar.reputation.nobility) < 10)
			{
				dialog.text = NPCStringReactionRepeat("Look at that! And how do our guards let such a bastard like you just walk around the town? Impossible...", 
					"Get lost, I don't even want to talk with you! Hangman...", 
					"It's your last chance to get away. Otherwise you'll have only yourself to blame.",
					"I have warned you. Now you will pay for you impudence, bastard!", "block", 1, npchar, Dialog.CurrentNode);
				link.l1 = HeroStringReactionRepeat("Hey hey! Show me more respect, sir!", 
					"Look at yourself, saint...",
					"Calm down...", 
					"What?!", npchar, Dialog.CurrentNode);
				link.l1.go = DialogGoNodeRepeat("exit", "", "", "fight", npchar, Dialog.CurrentNode);
			break;
			}
			
			//--> диалог первой встречи
            if(NPChar.quest.meeting == "0")
			{
				// проверка наличия корабля в порту
				bool ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
				if (ok && sti(Pchar.Ship.Type) != SHIP_NOTUSED && CheckAttribute(npchar, "quest.passenger") && !CheckAttribute(pchar, "GenQuest.Noblepassenger") && 4-sti(RealShips[sti(Pchar.Ship.Type)].Class) > 0)//дворянин-пассажир
				{
					dialog.text = "Greetings, "+GetAddress_Form(NPChar)+". I see that you are a captain of the solid ship. I want to ask you to do one thing. You can take it as a deal if you want...";
					link.l1 = "I am listening, "+GetAddress_FormToNPC(NPChar)+". What do you mean?";
					link.l1.go = "passenger";
					link.l2 = "Pardon me, "+GetAddress_FormToNPC(NPChar)+", but I am in a hurry.";
					link.l2.go = "exit";
					npchar.quest.meeting = "1";
					DeleteAttribute(npchar, "talker"); //снимаем говорилку
					break;
				}
				if (CheckAttribute(npchar, "quest.donation"))//клянчит деньги
				{
					dialog.text = "Aha, it's good to see such a decent man in our beyond! I am sure that you are just right from Europe. Listen, I want to ask you to help me as nobleman to nobleman. I hope that you will understand me correctly.";
					link.l1 = "Good day to you, sir. I am listening.";
					link.l1.go = "donation";
					npchar.quest.meeting = "1";
					break;
				}
				if (CheckAttribute(npchar, "quest.lombard") && !CheckAttribute(pchar, "GenQuest.Noblelombard"))//семейная реликвия
				{
					dialog.text = "Good day, "+GetAddress_Form(NPChar)+"! It's good to meet a nobleman at the streets of our town! Will you let me to take a few minutes from you?";
					link.l1 = "Sure, sir. I am listening.";
					link.l1.go = "lombard";
					npchar.quest.meeting = "1";
					break;
				}
				if (CheckAttribute(npchar, "quest.slaves") && !CheckAttribute(Colonies[FindColony(npchar.city)], "questslaves"))//привезти рабов
				{
					dialog.text = "Good day to you, captain! I am glad to see you because you look like a man who is able to solve my problem.";
					link.l1 = "Interesting, and how can I solve your problem, "+GetAddress_FormToNPC(NPChar)+"?";
					link.l1.go = "slaves";
					npchar.quest.meeting = "1";
					break;
				}
				dialog.text = RandPhraseSimple("Hello, "+GetAddress_Form(NPChar)+". Do you want anything from me?", "What do you want, sir?");
				link.l1 = TimeGreeting()+", "+GetAddress_FormToNPC(NPChar)+". I won't take much of your time, just want to ask...";
				link.l1.go = "question";
				link.l2 = RandPhraseSimple("I need information about your colony.", "I need information.");
				link.l2.go = "quests";//(перессылка в файл города)
				npchar.quest.meeting = "1";
			}
			else //--> повторные обращения
			{
				dialog.text = NPCStringReactionRepeat("What? Again? I don't have time for you. Look for someone else to talk. There are a lot of marginals walking around the streets. And I have to go, there will be a banquet tonight in the governor's residence and I have to prepare myself...", 
					"No, now it is really annoying! Don't you just get it? Or are you a slow minded?", 
					"Sir, I am beginning to suspect that you are not an idiot but a hick and a boor. I warn you, leave me alone or you'll regret for bothering me.",
					"Enough. I will teach you, an insolent fellow!", "block", 1, npchar, Dialog.CurrentNode);
				link.l1 = HeroStringReactionRepeat("I see. Farewell.", 
					"Yes-yes, just forgot what I wanted to ask...",
					"You have understood me wrong...", 
					"What?!", npchar, Dialog.CurrentNode);
				link.l1.go = DialogGoNodeRepeat("exit", "", "", "fight", npchar, Dialog.CurrentNode);
			}
			NextDiag.TempNode = "First time";
		break;

		case "question":
			dialog.text = LinkRandPhrase("Go on.","What do you want?","Questions? Fine, sailor, I am listening.");
			link.l1 = LinkRandPhrase("Won't you tell me the last gossip of your town?","Have anything interesting happened here recently?","Any news from the archipelago, sir?");
			link.l1.go = "rumours_nobleman";
			NextDiag.TempNode = "First time";
		break;

//--------------------------------------------дворянин-пассажир---------------------------------------------------
		case "passenger":
			if (drand(19) > 9) SetPassengerParameter("Noblepassenger", false);
			else SetPassengerParameter("Noblepassenger", true);
			dialog.text = "Sir, I need to get to the colony" + XI_ConvertString("Colony"+pchar.GenQuest.Noblepassenger.City)+", as soon as possible it is on "+XI_ConvertString(GetIslandByCityName(pchar.GenQuest.Noblepassenger.City)+"Dat")+", for "+FindRussianDaysString(sti(pchar.GenQuest.Noblepassenger.DaysQty))+". Your ship looks solid comparing with the majority of those small boats sailing here. I can pay you "+FindRussianMoneyString(sti(pchar.GenQuest.Noblepassenger.Money))+". What would you say?";
			link.l1 = "Hm. I am heading this way as well, so I am ready to take you aboard on these terms.";
			link.l1.go = "passenger_1";
			link.l2 = "I'm sorry, "+GetAddress_FormToNPC(NPChar)+", but I am sailing in the different direction. I can't help you.";
			link.l2.go = "passenger_exit";
		break;
		
		case "passenger_exit":
			dialog.text = "Too bad. Well, I'll wait for another ship. Farewell.";
			link.l1 = "See you.";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "GenQuest.Noblepassenger");
		break;
		
		case "passenger_1":
			dialog.text = "Great! I am tired of waiting. You will get your payment when we get there.";
			link.l1 = "Go to my ship, "+GetAddress_FormToNPC(NPChar)+". We are leaving soon.";
			link.l1.go = "passenger_2";
		break;
		
		case "passenger_2":
			DialogExit();
			pchar.GenQuest.Noblepassenger.id = npchar.id;
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
			AddQuestUserDataForTitle(sTitle, "sType", "nobleman");
			AddQuestUserDataForTitle(sTitle, "sName", GetFullName(npchar));
			sTemp = XI_ConvertString("Colony" +pchar.GenQuest.Noblepassenger.City+"Gen") + ", at " + XI_ConvertString(GetIslandByCityName(pchar.GenQuest.Noblepassenger.City)+"Dat")+".";
			AddQuestUserDataForTitle(sTitle, "sCity", sTemp);
			AddQuestUserData(sTitle, "sName", GetFullName(npchar));
			AddQuestUserData(sTitle, "sCity", sTemp);
			AddQuestUserData(sTitle, "sDays", FindRussianDaysString(sti(pchar.GenQuest.Noblepassenger.DaysQty)));
            AddQuestUserData(sTitle, "sMoney", FindRussianMoneyString(sti(pchar.GenQuest.Noblepassenger.Money)));
			AddQuestUserData(sTitle, "sName", GetFullName(npchar));
			pchar.quest.Noblepassenger.win_condition.l1 = "location";
			pchar.quest.Noblepassenger.win_condition.l1.location = pchar.GenQuest.Noblepassenger.City+"_town";
			pchar.quest.Noblepassenger.function = "Noblepassenger_complete";
			SetFunctionTimerCondition("Noblepassenger_Over", 0, 0, sti(pchar.GenQuest.Noblepassenger.DaysQty), false);
		break;
		
		case "passenger_3":
			pchar.quest.Noblepassenger_Over.over = "yes"; //снять таймер
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
			AddMoneyToCharacter(pchar, sti(pchar.GenQuest.Noblepassenger.Money));
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
			ChangeCharacterComplexReputation(pchar, "fame", 1);
			OfficersReaction("good");				
			AddCharacterExpToSkill(pchar, "Sailing", 80);
			AddCharacterExpToSkill(pchar, "Leadership", 20);
			if (CheckAttribute(pchar, "GenQuest.Noblepassenger.Enemycity")) AddCharacterExpToSkill(pchar, "Sneak", 50);
			sTitle = npchar.index+"Citizpassenger";
			AddQuestRecordEx(sTitle, "Citizpassenger", "3");
			CloseQuestHeader(sTitle);
			DeleteAttribute(Pchar, "GenQuest.Noblepassenger");
		break;
//<-- дворянин-пассажир

//-------------------------------------------------помощь деньгами------------------------------------------------
		case "donation":
			sTemp = DonationText();
			dialog.text = "I have a quite delicate business..."+sTemp+" I need money now or things will fall apart for me. I would never ask you for money but the situation is really bad.";
			link.l1 = "How much do you need?";
			link.l1.go = "donation_1";
		break;
		
		case "donation_1":
			iTemp = drand(4)+1;
			pchar.GenQuest.Nobledonation.Money = iTemp*1000+rand(iTemp)*150;
			dialog.text = "The sum is quite small, it's "+FindRussianMoneyString(sti(pchar.GenQuest.Nobledonation.Money))+". So what, can you help me?";
			if (sti(pchar.money) >= sti(pchar.GenQuest.Nobledonation.Money))
			{
				link.l1 = "Yes, sure. Take it.";
				link.l1.go = "donation_2";
			}
			link.l2 = "I'd be glad to help, but my pockets are empty as well - not a single spare peso.";
			link.l2.go = "donation_exit";
		break;
		
		case "donation_exit":
			DialogExit();
			ChangeOfficersLoyality("bad_all", 1);
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeday = 0;
			DeleteAttribute(pchar, "GenQuest.Nobledonation");
		break;
		
		case "donation_2":
			AddMoneyToCharacter(pchar, -sti(pchar.GenQuest.Nobledonation.Money));
			dialog.text = "My gratitude, "+GetAddress_Form(NPChar)+"! You have saved me! I have friends in governor's residence and I will tell them about your generosity. Thousand thanks again!";
			link.l1 = "You're welcome, sir. I am sure that you would do the same to me.";
			link.l1.go = "donation_3";
		break;
		
		case "donation_3":
			DialogExit();
			ChangeOfficersLoyality("good_all", rand(2)+1);
			ChangeCharacterNationReputation(pchar, sti(npchar.Nation), rand(1)+2);
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeday = 0;
			DeleteAttribute(pchar, "GenQuest.Nobledonation");
		break;
//<-- помощь деньгами

//-------------------------------------------------семейная реликвия---------------------------------------------
		case "lombard":
			LombardText();
			dialog.text = "I need your help. You are wealthy and nobleman, so I hope that you will understand. I had a strong need of money not long ago so I had to go to the banker and to pawn "+pchar.GenQuest.Noblelombard.Item+"\nHe offered good terms. Ten percents for each month, three months in total. But the time is off and I don't possess money to redeem the item due to unfortunate course of events\nNow he says that he has found a buyer for "+pchar.GenQuest.Noblelombard.Item+" and he's going to sell it if I don't repay my debt and percents immediately. But I don't have much money now, and my relic is very expensive...";
			link.l1 = "And how can I help you with that, "+GetAddress_FormToNPC(NPChar)+"?";
			link.l1.go = "lombard_1";
		break;
		
		case "lombard_1":
			dialog.text = "I'm asking you to talk with our banker. Offer him money, vouch for me... or do something else. Unfortunately, I have no one to ask, all of my buddies have suddenly gone 'bankrupt'. In three months "+pchar.GenQuest.Noblelombard.Text+", and I will repay you all of your costs, doubly repay. You have my word!";
			link.l1 = "Fine, I'll try to help you in this case.";
			link.l1.go = "lombard_2";
			link.l2 = "Unfortunately, I am a 'bankrupt' too right now. So I can't help you, I am so sorry!";
			link.l2.go = "lombard_exit";
		break;
		
		case "lombard_exit":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeday = 0;
			DeleteAttribute(pchar, "GenQuest.Noblelombard");
		break;
		
		case "lombard_2":
			dialog.text = "Thank you for your understanding. I'll be waiting for you in the tavern. Come there as soon as possible.";
			link.l1 = "...";
			link.l1.go = "lombard_3";
		break;
		
		case "lombard_3":
			DialogExit();
			pchar.GenQuest.Noblelombard = "true"
			pchar.GenQuest.Noblelombard.Name = GetFullName(npchar);
			pchar.GenQuest.Noblelombard.id = npchar.id;
			pchar.GenQuest.Noblelombard.City = npchar.city;
			pchar.GenQuest.Noblelombard.Money = 20000+drand(60)*500;
			pchar.GenQuest.Noblelombard.Percent = makeint(sti(pchar.GenQuest.Noblelombard.Money)*0.3);
			pchar.GenQuest.Noblelombard.Summ = sti(pchar.GenQuest.Noblelombard.Money)+sti(pchar.GenQuest.Noblelombard.Percent);
			pchar.GenQuest.Noblelombard.Chance = drand(9);
			chrDisableReloadToLocation = true;//закрыть локацию
			LAi_SetActorType(npchar);
			LAi_RemoveLoginTime(npchar);
			DeleteAttribute(npchar, "CityType");//удалить признак фантома
			FreeSitLocator(pchar.GenQuest.Noblelombard.City + "_tavern", "sit1");
			LAi_ActorRunToLocation(npchar, "reload", "reload4_back", pchar.GenQuest.Noblelombard.City+"_tavern", "sit", "sit1", "Nobleman_lombardTavern", 10);
			SetFunctionTimerCondition("Noblelombard_Over", 0, 0, 1, false); //таймер до конца суток
			ReOpenQuestHeader("Noblelombard");
			AddQuestRecord("Noblelombard", "1");
			AddQuestUserData("Noblelombard", "sCity", XI_ConvertString("Colony"+pchar.GenQuest.Noblelombard.City));
			AddQuestUserData("Noblelombard", "sName", pchar.GenQuest.Noblelombard.Name);
		break;
		
		case "lombard_4":
			if (CheckAttribute(pchar, "GenQuest.Noblelombard.Regard"))
			{
				pchar.quest.Noblelombard_Over.over = "yes"; //снять таймер
				dialog.text = "What can you say, "+GetAddress_Form(NPChar)+"? Have you been in the bank? Got good news or bad ones?";
				if (pchar.GenQuest.Noblelombard == "full") link.l1 = "I have. I have repaid all of your debt itself. You can go there and take back your relic.";
				if (pchar.GenQuest.Noblelombard == "maxpercent") link.l1 = "I have. I have repaid all of the interest for the last three months and although for the next three. You can serenely wait for your money. Just don't forget to repay your main debt in three months.";
				if (pchar.GenQuest.Noblelombard == "minpercent") link.l1 = "I have. I have repaid all of the interest for the last three months. Banker is agreed to wait three months more until you will get a whole sum.";
				link.l1.go = "lombard_5";
			break;
			}
			if (pchar.GenQuest.Noblelombard == "fail")
			{
				dialog.text = "What can you say, "+GetAddress_Form(NPChar)+"? Have you been in bank? Got good news or bad ones?";
				link.l1 = "I have. This miser has asked for the incredible sum. He has rejected any asks of concessions and I don't have the required sum. So I couldn't help you. Too bad!";
				link.l1.go = "lombard_fail";
			}
			else
			{
				dialog.text = "What can you say, "+GetAddress_Form(NPChar)+"? Have you been in bank? Got good news or bad ones?";
				link.l1 = "I am on it. Wait.";
				link.l1.go = "exit";
				NextDiag.TempNode = "lombard_4";
			}
		break;
		
		case "lombard_fail":
			pchar.quest.Noblelombard_Over.over = "yes"; //снять таймер
			dialog.text = "Meh, "+GetAddress_Form(NPChar)+"... Now you are also a witness of an irrepressible greed of these damned bloodthirsty usurers. Remember about that when you will be willing to borrow money from them like I did. Thank you for your trying at least...";
			link.l1 = "Never liked them. Well, who likes usurers? I am sorry, "+GetAddress_FormToNPC(NPChar)+". Farewell.";
			link.l1.go = "lombard_fail_1";
		break;
		
		case "lombard_fail_1":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeday = 0;
			AddQuestRecord("Noblelombard", "4");
			AddQuestUserData("Noblelombard", "sName", pchar.GenQuest.Noblelombard.Name);
			CloseQuestHeader("Noblelombard");
			sld = characterFromId(pchar.GenQuest.Noblelombard.City+"_usurer");
			DeleteAttribute(sld, "quest.noblelombard");
			DeleteAttribute(Pchar, "GenQuest.Noblelombard");
		break;
		
		case "lombard_5":
			dialog.text = "Incredible! You've just saved me, "+GetAddress_Form(NPChar)+"! I will never forget it. I assure you that all of your costs will be doubly repaid. Come to see our banker in three months. I will open a deposit for your name.";
			link.l1 = "Fine, I'll do as you say. See you!";
			link.l1.go = "lombard_6";
		break;
		
		case "lombard_6":
			dialog.text = "Thanks again, captain. Good luck!";
			link.l1 = "...";
			link.l1.go = "lombard_7";
		break;
		
		case "lombard_7":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeday = 0;
			ChangeCharacterComplexReputation(pchar, "authority", 2);
			ChangeOfficersLoyality("good_all", 1);
			AddQuestRecord("Noblelombard", "5");
			AddQuestUserData("Noblelombard", "sName", pchar.GenQuest.Noblelombard.Name);
			SetFunctionTimerCondition("Noblelombard_Regard", 0, 0, 90, false); //таймер
		break;
//<-- семейная реликвия

//------------------------------------------привезти рабов под заказ--------------------------------------------
		case "slaves":
			npchar.quest.slaves.price = 3+drand(1);//цена на рабов в дублонах
			npchar.quest.slaves.qty = 50+drand(5)*10;//количество
			npchar.quest.slaves.money = sti(npchar.quest.slaves.qty)*sti(npchar.quest.slaves.price);
			dialog.text = "I own a "+LinkRandPhrase("factory","mine","plantation")+" and I always need slaves. Right now I need "+sti(npchar.quest.slaves.qty)+" heads. I am willing to order a batch of them. I am paying in gold for each head "+sti(npchar.quest.slaves.price)+"\nNo rush, I don't limit you in time. Well, within reason of course, don't prolong it for more than a half a year. So what do you say? Deal?";
			link.l1 = "Deal! It's going to be a messy business, but it is worth the risk.";
			link.l1.go = "slaves_1";
			link.l2 = "Pardon me, but I'm not a slave trader. Not my type of work.";
			link.l2.go = "exit_slaves";
		break;
		
		case "exit_slaves":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeday = 0;
		break;
		
		case "slaves_1":
			dialog.text = "Very well then. I'll be waiting for you with the cargo. You can find me in a church from eleven AM till one PM every day. I am busy or away at the rest of the day.";
			link.l1 = "Fine. I'll remember that. See you, "+GetAddress_FormToNPC(NPChar)+".";
			link.l1.go = "slaves_2";
		break;
		
		case "slaves_2":
			DialogExit();
			sGlobalTemp = npchar.id;
			DeleteAttribute(npchar, "LifeDay");
			DeleteAttribute(npchar, "CityType");//удалить признак фантома, иначе - пустые города
			SaveCurrentNpcQuestDateParam(npchar, "slaves_date");//запоминаем дату
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload4_back", npchar.city+"_church", "sit", "sit"+(1+rand(5)), "Nobleslaves_Place", 10.0);
			chrDisableReloadToLocation = true;//закрыть локацию
			Colonies[FindColony(npchar.city)].questslaves = true;
			sTitle = npchar.city+"Nobleslaves";
			ReOpenQuestHeader(sTitle);
			AddQuestRecordEx(sTitle, "Nobleslaves", "1");
			AddQuestUserDataForTitle(sTitle, "sCity", XI_ConvertString("Colony"+npchar.city+"Gen"));
			AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony"+npchar.city+"Gen"));
			AddQuestUserData(sTitle, "sName", GetFullName(npchar));
			AddQuestUserData(sTitle, "sQty", sti(npchar.quest.slaves.qty));
			AddQuestUserData(sTitle, "sMoney", sti(npchar.quest.slaves.money));
		break;
		
		case "slaves_3":
			if (GetNpcQuestPastDayParam(npchar, "slaves_date") < 180)
			{
				dialog.text = "Have you brought "+sti(npchar.quest.slaves.qty)+" slaves as I've asked you, captain?";
				if (GetSquadronGoods(pchar, GOOD_SLAVES) >= sti(npchar.quest.slaves.qty))
				{
					link.l1 = "Yes. The whole batch is in my cargo. I am ready to tranfer them to you.";
					link.l1.go = "slaves_4";
				}
				else
				{
					link.l1 = "No, I am on it.";
					link.l1.go = "exit";
					NextDiag.TempNode = "slaves_3";
				}
			}
			else
			{
				dialog.text = "Captain, if you are about those slaves... I have already bought enough and I don't need more right now. You were working on my task too long.";
				link.l1 = "Such a pity! But you're right, I wasn't fast enough. Farewell!";
				link.l1.go = "slaves_8";
			}
		break;
		
		case "slaves_4":
			dialog.text = "Excellent. I will send a barque for them immediately.";
			link.l1 = "How about my payment?";
			link.l1.go = "slaves_5";
		break;
		
		case "slaves_5":
			dialog.text = "Don't worry, I remember about it. Here, take the sum, "+sti(npchar.quest.slaves.price)+" doubloons for a head.";
			link.l1 = "Thanks, sir. It was nice to have a business with you!";
			link.l1.go = "slaves_6";
		break;
		
		case "slaves_6":
			RemoveCharacterGoods(pchar, GOOD_SLAVES, sti(npchar.quest.slaves.qty));
			TakeNItems(pchar, "gold_dublon", sti(npchar.quest.slaves.money));
			Log_Info("You have received "+FindRussianDublonString(sti(npchar.quest.slaves.money))+"");
			PlaySound("interface\important_item.wav");
			dialog.text = "I should say so... Pardon me now, I have to go. See you!";
			link.l1 = "Good luck, "+GetAddress_FormToNPC(NPChar)+".";
			link.l1.go = "slaves_7";
		break;
		
		case "slaves_7":
			DialogExit();
			npchar.lifeday = 0;
			DeleteAttribute(Colonies[FindColony(npchar.city)], "questslaves");
			LAi_SetActorType(npchar);
			GetCharacterPos(pchar, &locx, &locy, &locz);
         	ChangeCharacterAddressGroup(npchar, npchar.city+"_church", "goto", LAi_FindNearestFreeLocator("goto", locx, locy, locz));
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "", 10.0);
			AddCharacterExpToSkill(pchar, "Commerce", 150);//торговля
			AddCharacterExpToSkill(pchar, "Sailing", 50);//навигация
			AddCharacterExpToSkill(pchar, "Fortune", 30);//везение
			ChangeCharacterComplexReputation(pchar, "nobility", -1);
			sTitle = npchar.city+"Nobleslaves";
			AddQuestRecordEx(sTitle, "Nobleslaves", "2");
			CloseQuestHeader(sTitle);
		break;

		case "slaves_8":
			DialogExit();
			npchar.lifeday = 0;
			LAi_CharacterDisableDialog(npchar);
			DeleteAttribute(Colonies[FindColony(npchar.city)], "questslaves");
			sTitle = npchar.city+"Nobleslaves";
			AddQuestRecordEx(sTitle, "Nobleslaves", "3");
			CloseQuestHeader(sTitle);
		break;
//<-- привезти рабов под заказ

		//замечание по обнаженному оружию от персонажей типа citizen
		case "CitizenNotBlade":
			dialog.text = NPCharSexPhrase(NPChar, "Listen, as a citizen of this town I'm asking you to sheathe your blade.", "Listen, as a citizen of this town I'm asking you to sheathe your blade.");
			link.l1 = LinkRandPhrase("Fine.", "As you wish.", "Okay.");
			link.l1.go = "exit";
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "fight":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_SetHP(NPChar, 400, 400);
			TakeNItems(NPChar, "potion2", 3);
			SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
			LAi_group_MoveCharacter(NPChar, "TempFight");
			LAi_group_Attack(NPChar, Pchar);
			AddDialogExitQuest("MainHeroFightModeOn");
			ChangeCharacterNationReputation(pchar, sti(npchar.nation), -3);
		break;
	}
}

string DonationText()
{
	string sText;
	switch (drand(5))
	{
		case 0: sText = "I've lost all my money in gambling yesterday and I don't have enough sum to wipe away the debt. Can you help me?" break;
		case 1: sText = "I had a nice time yesterday with one... whore, and now she is trying to blackmail me. I need to pay her first and then I will deal with her... Can you help me with a little sum?" break;
		case 2: sText = "I have pierced through one idiot with my rapier recently and now the commandant demands a bribe to hush up that event. I am short of money now. Can you help me?" break;
		case 3: sText = "I was unlucky to lose a bet and I don't have a trifling sum  to repay the debt of honor. Can you help me?" break;
		case 4: sText = "One bastard has known about my... spicy story with one lady. I don't have enough money to shut his mouth. Just a few golden coins are left... " break;
		case 5: sText = "One bastard has stolen important papers from my house and demanding a significant sum for them. I've almost got it, just a few more coins left. Can you help me?" break;
	}
	return sText;
}

void LombardText()
{
	switch (drand(5))
	{
		case 0:
			pchar.GenQuest.Noblelombard.Item = "my mother's diamond pendant made by a jeweler from Madrid";
			pchar.GenQuest.Noblelombard.Text = RandPhraseSimple("I will get my inheritance","my ship will return from Africa loaded with slaves");
		break;
		case 1: pchar.GenQuest.Noblelombard.Item = "an emerald necklace of my sister crafted by a jeweler of Paris";
				pchar.GenQuest.Noblelombard.Text = RandPhraseSimple("I will inherit a county in Europe","my ship will return from India loaded with spicery");
		break;
		case 2:
			pchar.GenQuest.Noblelombard.Item = "family ring with an emblem of our kin";
			pchar.GenQuest.Noblelombard.Text = RandPhraseSimple("my expedition will return from Main with gold ingots","I will get my heritage");
		break;
		case 3:
			pchar.GenQuest.Noblelombard.Item = "a ruby bracelet of my wife, a gift from her mother";
			pchar.GenQuest.Noblelombard.Text = RandPhraseSimple("I will get my investment with the interest from a European bank","I will get profits from my current business");
		break;
		case 4:
			pchar.GenQuest.Noblelombard.Item = "a necklace of gold and diamonds, piece work, a pride of my wife";
			pchar.GenQuest.Noblelombard.Text = RandPhraseSimple("I will get profits from my current business","my ship will be back from Africa with the cargo filled with slaves");
		break;
		case 5:
			pchar.GenQuest.Noblelombard.Item = "an ivory cane of semiprecious stones, a gift from my grandfather";
			pchar.GenQuest.Noblelombard.Text = RandPhraseSimple("my ship will be back from India with the cargo filled with spices","I will receive my interest from the European bank");
		break;
	}
}