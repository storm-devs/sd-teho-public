//#include "DIALOGS\convoy_traider.h"
void ProcessDialogEvent()
{
	ref NPChar, d;
	aref Link, Diag;
	string NPC_Meeting;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makeref(d, Dialog);
	makearef(Diag, NPChar.Dialog);

	switch(Dialog.CurrentNode)
	{
		case "exit":
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
		break;
		
		case "prepare_convoy_quest":
			if (isBadReputation(pchar, 40)) 
			{
				dialog.text = RandPhraseSimple("Ahhh, hell! I know who you are! Only a total idiot would hire you to escort his ship. Farewell!", "Oh, I know who you are! Hiring you as an escort, you say? I am no fool...");
				link.l1 = RandPhraseSimple("Heh, what a pity!", "People are certainly too easily scared these days!");
				link.l1.go = "convoy_refused";
			}
			else
			{
				dialog.text = TimeGreeting() + ", "+GetAddress_Form(NPChar) + "! I am "+ GetFullName(NPChar) + ", a merchant. I heard you were looking for a job?";
				link.l1 = "Something like that. And, you, as I heard, are looking for the captain, who will escort you and your ship to your destination?";
				link.l1.go = "prepare_convoy_quest_2";
			}
		break;
		
		case "prepare_convoy_quest_2":
			dialog.text = "Exactly. Moreover, I believe you're just the right person for my escorting. What would you say?";
			link.l1 = "Well, make me an offer, and perhaps, you'll get a deal.";
			link.l1.go = "prepare_convoy_quest_3";
		break;
		
		case "prepare_convoy_quest_3":
			LookShipConvoy();
			GenerateConvoyQuest(npchar);
			dialog.text = "I need to be escorted to " + XI_ConvertString("Colony" + pchar.quest.destination + "Gen") + ", that located on " + XI_ConvertString(GetIslandByCityName(pchar.quest.destination) + "Dat") +
				", for " + FindRussianDaysString(sti(pchar.ConvoyQuest.iDay)) +", and for that I'll pay you " + FindRussianMoneyString(sti(pchar.ConvoyQuest.convoymoney)) + ". So, your decision?";
			link.l1 = "I'm in.";
			link.l1.go = "convoy_agreeded";
			link.l2 = "I don't think it's an interesting proposition.";
			link.l2.go = "convoy_refused";
		break;
		
		case "convoy_refused":
			chrDisableReloadToLocation = false;
			npchar.LifeDay = 0;
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
			AddDialogExitQuest("convoy_refused");
		break;
		
		case "convoy_agreeded":
			chrDisableReloadToLocation = false;
		    pchar.convoy_quest = pchar.quest.destination;
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
			AddDialogExitQuest("convoy_agreeded");
		break;
		
		case "complete_convoy_quest":
			dialog.text = "Oh! Thank you. Under your protection I felt myself safety like never before. Here's your well-deserved reward.";
			Link.l1 = "You're welcome.";
			link.l1.go = "exit";
			//слухи
			AddSimpleRumour(LinkRandPhrase("A merchant captain by the name of " + GetFullName(npchar) + " says that captain " + GetMainCharacterNameDat() + " can be trusted when one needs an escort.", 
				"Negociant named " + GetFullName(npchar) + " says that captain " + GetMainCharacterNameDat() + " can be trusted. "+ GetSexPhrase("He","She") +" protected his ship in the best possible way while escorting him to " + XI_ConvertString("Colony" + pchar.quest.destination + "Gen") + ".", 
				"I heard that you keep the word given to trading captains which ask you for an escort. A trader named " + GetFullName(npchar) + " speaks well about you."), sti(npchar.nation), 40, 1);
			pchar.quest.generate_convoy_quest_progress = "completed";
			chrDisableReloadToLocation = false;
			npchar.LifeDay = 0;
			AddDialogExitQuest("convoy_refused");
		break;
	}
} 

// boal 03.05.04 квест сопроводить торговца -->
void GenerateConvoyQuest(ref npchar)
{
	int iTradeMoney, iNation;

	DeleteAttribute(NPChar, "Ship");
    SetShipToFantom(NPChar, "trade", true);

	iNation = GetRelation2BaseNation(sti(npchar.nation)); //если привезти нужно во вражеский город
	int daysQty = GetMaxDaysFromIsland2Island(GetArealByCityName(pchar.ConvoyQuest.City), GetArealByCityName(pchar.quest.destination));
	if (sti(daysQty) > 14) daysQty = 14;
	pchar.ConvoyQuest.iDay = makeint(sti(daysQty)*(frand(1.3)+0.7));
	iTradeMoney = (sti(daysQty)*600*sti(pchar.GenQuest.Convoy.Shipmod)+rand(100))*sti(daysQty)/sti(pchar.ConvoyQuest.iDay);
	if (iNation == RELATION_ENEMY && sti(npchar.nation != PIRATE)) iTradeMoney = makeint(iTradeMoney * 1.4); //то размер награды увеличивается
	pchar.ConvoyQuest.convoymoney = iTradeMoney;			


	//Log_Info(FindRussianDaysString(sti(daysQty)));
	//Log_Info(pchar.quest.destination);
	//Log_Info(pchar.ConvoyQuest.City);

	SetTimerCondition("generate_convoy_quest_timer", 0, 0, sti(pchar.ConvoyQuest.iDay), false);

	pchar.quest.generate_convoy_quest_progress = "begin";

	pchar.quest.generate_convoy_quest_failed.win_condition.l1 = "NPC_Death";
	pchar.quest.generate_convoy_quest_failed.win_condition.l1.character = "QuestTrader";
	pchar.quest.generate_convoy_quest_failed.win_condition = "generate_convoy_quest_failed";
}

void LookShipConvoy()
{
	switch(makeint(6-sti(RealShips[sti(Pchar.Ship.Type)].Class)))
	{
		case 0:
			pchar.GenQuest.Convoy.Shipmod = 0.7;
		break;
		case 1:
			pchar.GenQuest.Convoy.Shipmod = 1;
		break;
		case 2:
			pchar.GenQuest.Convoy.Shipmod = 1.2;
		break;
		case 3:
			pchar.GenQuest.Convoy.Shipmod = 1.5;
		break;
		case 4:
			pchar.GenQuest.Convoy.Shipmod = 2.2;
		break;
		case 5:
			pchar.GenQuest.Convoy.Shipmod = 3;
		break;
	}
}
