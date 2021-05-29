//Jason общий диалог уличных матросов
#include "DIALOGS\russian\Rumours\Common_rumours.c"
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;
	string sTemp;
	int iTemp;

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
			if (npchar.quest.meeting == "0")
			{
				if (sti(Pchar.Ship.Type) != SHIP_NOTUSED && CheckAttribute(npchar, "quest.crew"))//найм в команду
				{
					dialog.text = "Good day, "+GetAddress_Form(NPChar)+". I am aware that you are a captain of your own ship. I've got a deal for you.";
					link.l1 = "I am listening, "+GetAddress_FormToNPC(NPChar)+". What kind of deal?";
					link.l1.go = "crew";
					link.l2 = "Sorry, "+GetAddress_FormToNPC(NPChar)+", but I am in a hurry.";
					link.l2.go = "exit";
					npchar.quest.meeting = "1";
					DeleteAttribute(npchar, "talker"); //снимаем говорилку
					break;
				}
				dialog.text = LinkRandPhrase("Hey, captain! What do you want from a common sailor?","Good day, sir. How can I help you?","Good day, sir. Do you want anything?");
				link.l1 = "Glad to meet you, pal! My name is "+GetFullName(pchar)+". Got a minute to talk?";
				link.l1.go = "question";
				link.l2 = RandPhraseSimple("I've got a question for you.", "I need some information about this colony.");
				link.l2.go = "quests";//(перессылка в файл города)
				link.l3 = "Just wanted to say hi. See you!";
				link.l3.go = "exit";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "You again, sir? What else do you want?";
				link.l1 = "Got a minute to talk?";
				link.l1.go = "question";
				link.l2 = RandPhraseSimple("I've got a question for you.", "I need some information about this colony.");
				link.l2.go = "quests";//(перессылка в файл города)
				link.l3 = "No, pal, it's nothing. Good luck!";
				link.l3.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;

		case "question":
			dialog.text = NPCStringReactionRepeat(""+GetFullName(npchar)+" at your service, good sir! What do you want to know?", 
				"Glad to talk with you, captain!", 
				"Well... I suppose I still have some more time to talk...",
                "Unfortunately, I have to go now. Farewell!", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Got anything interesting to tell me?", 
				"Got anything interesting to tell me?",
                "Got anything interesting to tell me?", 
				"Sure. Good luck!", npchar, Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("rumours_sailor", "rumours_sailor", "rumours_sailor", "exit", npchar, Dialog.CurrentNode);
		break;

		case "crew":
			switch (drand(2))
			{
				case 0: sTemp = "Me and my fellows were posted from a ship due to our injuries. But we are all healthy now and want to employ as sailors again. Do you want to replenish your crew?"; break;
				case 1: sTemp = "Me and a few guys were posted from a trading ship due to the end of our contracts. We have been without a single coin for a long time already so we want to employ as sailors again. Do you need skillful sailors for your crew?"; break;
				case 2: sTemp = "Me and my pals were back from our voyage two weeks ago. Master has dismissed us and we've been having a great fun during these weeks. But our pockets are empty now so it's time to sail again. Do you want to hire us, captain?"; break;
			}
			dialog.text = sTemp;
			link.l1 = "Well, I am ready to discuss your proposal. How many of you and what are you good at?";
			link.l1.go = "crew_1";
			link.l2 = "I am sorry, sailor, but I've got enough men already. You should find yourself another captain.";
			link.l2.go = "exit";
		break;
		
		case "crew_1":
			switch (sti(npchar.quest.crew.type))
			{
				case 0: sTemp = "We are the best in working with sails and tackles. Not being too modest, I'd say that we are pro's in that, so don't worry, we won't let you down even in the strongest storm."; break;
				case 1: sTemp = "But most of all we like to be on the gun deck. We are able to deal with cannons in the way no one in your crew is. You can count on us in every hard fight!"; break;
				case 2: sTemp = "But our favorite is the boarding fight. Glitter of sabers, smell of a gunpowder and blood. That's our calling. It's not easy to defeat us in a fight, so you can always count on our blades, captain!"; break;
			}
			dialog.text = "There are "+sti(npchar.quest.crew.qty)+" of us and we will hire only together. We are able to do anything the sailor must do."+sTemp+"";
			if (GetFreeCrewQuantity(pchar) >= sti(npchar.quest.crew.qty))
			{
				link.l1 = "Sounds tempting. What about your advance?";
				link.l1.go = "crew_2";
				link.l2 = "Sorry, sailor, but I was expecting something... different. You should find yourself another captain.";
				link.l2.go = "exit";
			}
			else
			{
				link.l1 = "Sorry, sailor, but I don't have enough spare place on my ship. You should find yourself another captain.";
				link.l1.go = "exit";
			}
		break;
		
		case "crew_2":
			iTemp = sti(npchar.quest.crew.money)*sti(npchar.quest.crew.qty);
			dialog.text = ""+FindRussianMoneyString(sti(npchar.quest.crew.money))+" for each. And then the common sailor's wage per month. We won't ask anything excessive, captain.";
			if (sti(pchar.money) >= iTemp)
			{
				link.l1 = "Deal! Take your coins. Now go to my ship, it is called '"+pchar.ship.name+"', right in the harbor. Boatswain will give you your places in the crew's quarters and assign your jobs.";
				link.l1.go = "crew_3";
			}
			link.l2 = "Unfortunately, I can't afford to pay for your services. You should find yourself another captain.";
			link.l2.go = "exit";
		break;
		
		case "crew_3":
			iTemp = sti(npchar.quest.crew.money)*sti(npchar.quest.crew.qty);
			AddMoneyToCharacter(pchar, -iTemp);
			dialog.text = "We are on our way, captain! I will gather folks and we will be off immediately.";
			link.l1 = "Hurry up, I am not going to stay here for along time.";
			link.l1.go = "crew_4";
		break;
		
		case "crew_4":
			DialogExit();
			AddCharacterCrew(pchar, sti(npchar.quest.crew.qty));
			//увеличиваем опыт
			iTemp = makeint(sti(npchar.quest.crew.qty)*50/sti(pchar.ship.crew.quantity));
			switch (sti(npchar.quest.crew.type))
			{
				case 0: ChangeCrewExp(pchar, "Sailors", iTemp); break;
				case 1: ChangeCrewExp(pchar, "Cannoners", iTemp); break;
				case 2: ChangeCrewExp(pchar, "Soldiers", iTemp); break;
			}
			//увеличиваем мораль
			iTemp = makeint(sti(npchar.quest.crew.qty)/10)+1;
			AddCrewMorale(pchar, iTemp);
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "", 20.0);
			npchar.lifeday = 0;
		break;

		//замечание по обнаженному оружию от персонажей типа citizen
		case "CitizenNotBlade":
			dialog.text = NPCharSexPhrase(NPChar, "Hey, sheathe your sword, cap. None of us needs problems, right?", "Hey, sheathe your sword, cap. None of us needs problems, right?");
			link.l1 = LinkRandPhrase("Fine.", "As you wish.", "As you say.");
			link.l1.go = "exit";
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
