// реплики солдат на палубе при разговоре в море
// форт-стража и комендант форта
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	switch(Dialog.CurrentNode)
	{
        case "exit":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
		break;
		
        case "First time":
			dialog.text = "Talk with our captain. I've got nothing to tell you.";
			Link.l1 = "Fine.";
			Link.l1.go = "exit";
			
			NextDiag.TempNode = "first time";
		break;
		//  на палубе -->
		case "On_Deck":
			dialog.text = "Talk with our captain. I've got nothing to tell you.";
			Link.l1 = "Fine.";
			Link.l1.go = "exit";

			NextDiag.TempNode = "On_Deck";
/*			
			// Первый церковный генератор
			if(CheckAttribute(PChar, "GenQuest.ChurchQuest_1.CapWaitOnTavern"))
			{
				if(CheckAttribute(PChar, "GenQuest.ChurchQuest_1.NeedToDialogWithSailors"))
				{
					dialog.text = "Sir, are you looking for somebody?";
					Link.l1 = "Yes, pal. Can I see the captain?";
					Link.l1.go = "ChurchQuest1_Node1";
				}
				else
				{
					dialog.text = "All questions to our captain. He has recently landed.";
					Link.l1 = "Fine";
					Link.l1.go = "exit";
				}
				break;
			}
*/			
			//--> eddy. квест мэра, закрываем выход с палубы и ноду даем нужную
			if (CheckAttribute(pchar, "GenQuest.DestroyPirate") && pchar.GenQuest.CaptainId == "MQPirate")
			{
	    		dialog.text = RandPhraseSimple("Oh, you've come here alone. Ha! In that case go to our captain. Tell him about your sad deeds...", "Wow, seems like you're insane, dude. Go to our captain and he will talk with you.");
				Link.l1 = "Too bad...";
				Link.l1.go = "exit";
			}
			//<-- eddy. квест мэра, закрываем выход с палубы
		break;
/*		
		case "ChurchQuest1_Node1":
			dialog.text = "You'd better look for him in the port.";
			Link.l1 = "Thank you, my friend.";
			Link.l1.go = "exit";
			NextDiag.TempNode = "On_Deck";
			PChar.GenQuest.ChurchQuest_1.CapWaitOnTavern = true; 
			DeleteAttribute(PChar, "GenQuest.ChurchQuest_1.NeedToDialogWithSailors"); // Не спрашиваем моряков
		break;
*/		
        //  на палубе <--
				
		// ugeen --> разговор с боцманом по генератору "Повод для спешки"
		case "On_MyShip_Deck":
			dialog.text = "Well, that was a serious mess, cap! We were in the tavern, drinking as we usually do when we heard screaming. We ran out of the tavern and saw that they were trying to arrest you. Fuck them! So we decided to leave this unfriendly harbour.";
			link.l1 = "Yeah, certainly some people have a bit strange perception of justice.";
			link.l1.go = "On_MyShip_Deck_1";
		break;
		
		case "On_MyShip_Deck_1":
		    if(pchar.questTemp.ReasonToFast == "speakSuccess_chain_A") 
			{
				// карты не было
				dialog.text = "Captain! Don't worry like that! It was clear that there was no way to flee in peace, so we have decided to visit the local banker in order to check his chests. Here is your share - " + sti(pchar.questTemp.ReasonToFast.p9) + " pesos...";
			}
			if(pchar.questTemp.ReasonToFast == "speakSuccess_chain_B")
			{
				// карту отобрали
				GiveItem2Character(pchar, pchar.questTemp.ReasonToFast.p6);
				dialog.text = "Captain! Don't worry like that! It was clear that there was no way to flee in peace, so we have decided to visit the local banker and to check his chests. There was also a fine sword in the pawn box. Here is your share - " + sti(pchar.questTemp.ReasonToFast.p9) + " pesos and a sword...";
			}		
			link.l1 = "That's my boys! Well done!";
			link.l1.go = "On_MyShip_Deck_End";
			AddMoneyToCharacter(pchar, sti(pchar.questTemp.ReasonToFast.p9));			
			pchar.Ship.Crew.Morale = MORALE_MAX;
			chrDisableReloadToLocation = false; // Откроем выход
			AddQuestRecord("ReasonToFast", "17");		
			AddQuestUserData("ReasonToFast", "sSex", GetSexPhrase("",""));		
			CloseQuestHeader("ReasonToFast");
			DeleteAttribute(pchar,"TownEscape");
			DeleteAttribute(pchar,"questTemp.ReasonToFast");
			QuestOpenSeaExit();
		break;
		
		case "On_MyShip_Deck_End":
			DialogExit();
			AddDialogExitQuest("CanEnterToMap");
		break;
		
		// разговор с боцманом по генератору 'Операция Галеон'
		case "CapComission_OnShipDeck":
			dialog.text = "Captain, your friend has escaped.";
			link.l1 = "What friend?";
			link.l1.go = "CapComission_OnShipDeck1";
		break;
		
		case "CapComission_OnShipDeck1":
			dialog.text = "Well, the friend who you have taken from the dungeons.";
			link.l1 = "How the fuck you managed to loose him?!";
			link.l1.go = "CapComission_OnShipDeck2";
		break;
		
		case "CapComission_OnShipDeck2":
			dialog.text = "It was not our fault, cap. He jumped away through the latrine to the sea... We tried to shoot him, but it was too dark there...";
			link.l1 = "Damn it! You really have got out of hand! All of you will be landed and sent to work with the sugarcane! To loose such a valuable bigwig!";
			link.l1.go = "CapComission_OnShipDeck3";
		break;
		
		case "CapComission_OnShipDeck3":
			chrDisableReloadToLocation = false; // Откроем выход
			AddQuestRecord("CaptainComission2", "25");	
			AddQuestUserData("CaptainComission2", "sSex", GetSexPhrase("","а"));			
			AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);
			CloseQuestHeader("CaptainComission2");	
			ChangeOfficersLoyality("bad_all", 1);
			ChangeCharacterComplexReputationABS(pchar, "authority", 1);
			DeleteAttribute(pchar,"TownEscape");
			DeleteAttribute(pchar,"GenQuest.CaptainComission.canSpeakBoatswain");
			DeleteAttribute(pchar, "GenQuest.CaptainComission");
			QuestOpenSeaExit();		
			DialogExit();
			AddDialogExitQuest("CanEnterToMap");
		break;
		// <-- ugeen
		
		// разговор с боцманом по ситуациям в трюме
		case "Hold_GenQuest_OnShipDeck":
			dialog.text = "Captain, forgive us, it was our fault - the prisoner has escaped.";
			link.l1 = "What prisoner? Who has escaped?";
			link.l1.go = "Hold_GenQuest_OnShipDeck1";
		break;
				
		case "Hold_GenQuest_OnShipDeck1":
			dialog.text = "Well, oh, forgot his name, " + pchar.GenQuest.Hold_GenQuest.CapName + ", right?";
			link.l1 = "Damn it! Where were you looking at?";
			link.l1.go = "Hold_GenQuest_OnShipDeck2";
		break;
		
		case "Hold_GenQuest_OnShipDeck2":
			dialog.text = "He got from the cargo hold and jumped from the bulwark. We didn't shoot him to avoid any noise and while we were preparing a longboat he was saved by fucking fishers.";
			link.l1 = "And why do I pay you money! Flog the head of watch and deprive him of rum for a week. Stand to! We are weighing anchor...";
			link.l1.go = "Hold_GenQuest_OnShipDeck3";
		break;
		
		case "Hold_GenQuest_OnShipDeck3":
			chrDisableReloadToLocation = false; // Откроем выход
			sld = characterFromId(pchar.GenQuest.Hold_GenQuest.CapId);
			ReleasePrisoner(sld);			
			CloseQuestHeader("HoldQuest");	
			DeleteAttribute(pchar, "TownEscape");
			DeleteAttribute(pchar, "GenQuest.Hold_GenQuest.canSpeakSailor");
			DeleteAttribute(pchar, "GenQuest.Hold_GenQuest");
			QuestOpenSeaExit();					
			DialogExit();
			AddDialogExitQuest("CanEnterToMap");
		break;
		
		case "Hold_GenQuest_OnShipDeck4":
			dialog.text = "Greeting, captain. There were no accidents during your...";
			link.l1 = "Fine, fine, I got it.... There is the prisoner in our cargo hold. His name is " + pchar.GenQuest.Hold_GenQuest.CapName + ". Take a few men and deliver him to the port. He is free now.";
			link.l1.go = "Hold_GenQuest_OnShipDeck5";
		break;
		
		case "Hold_GenQuest_OnShipDeck5":
			dialog.text = "Is he free for real? We are to deliver him via longboat?";
			link.l1 = "Via turtle... I thought I was clear enough. And hurry up! We need to weigh anchor by the start of an ebb.";
			link.l1.go = "Hold_GenQuest_OnShipDeck3";
		break;
		
		// Warship 09.07.09 Базар с нашим матросом на палубе Мэри Селест -->
		case "On_MaryCeleste_Deck":
			Dialog.text = "Captain, there are no people at all on the ship! Something is very wrong here... Tommy said that he had seen a cat in the cockpit and it was the one living soul...";
			Link.l1 = "Idiot, cats don't have souls. It looks like he has not visited a church for a long time already or he has never been there at all. Have you been in the captain's cabin? I need a logbook.";
			Link.l1.go = "On_MaryCeleste_Deck_1";
		break;
		
		case "On_MaryCeleste_Deck_1":
			Dialog.text = "No, they do have souls. There are no logbook and no any navigation instruments. Not even a single longboat...";
			Link.l1 = "They don't. Was it tired off by a storm?";
			Link.l1.go = "On_MaryCeleste_Deck_2";
		break;
		
		case "On_MaryCeleste_Deck_2":
			Dialog.text = "They do, cap. Cats have souls. Captain, the longboat was cut away and we have found a sword on the floor at the cockpit. It is rusty to bloody. Here, take a look...";
			Link.l1 = "Stop giving me this crap, throw it away, and stop talking about cats. Let's check the hold and leave... Oh, something is wrong here and I don't fucking like it...?";
			Link.l1.go = "On_MaryCeleste_Last";
			NextDiag.TempNode = "On_MaryCeleste_Deck_SailorLast";
		break;
		
		case "On_MaryCeleste_Last":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_SetCitizenType(NPChar); // Чтоб по палубе ходил
			
			NPChar = GetRealShip(GetCharacterShipType(CharacterFromID("MaryCelesteCapitan")));
			NPChar.TurnRate = sti(PChar.QuestTemp.MaryCeleste.TurnRate); // Вернем маневренность, для интерфейса
			
			chrDisableReloadToLocation = false; // Откроем выход
			
			LaunchTransferMain(PChar, CharacterFromID("MaryCelesteCapitan"), "MaryCelesteTransfer");
		break;
		
		case "On_MaryCeleste_Deck_SailorLast":
			switch(rand(2))
			{
				case 0:
					Dialog.text = "Captain, I've got a bad feeling about this place... Perhaps, it is time for us to leave?";
					Link.l1 = "Yes... Go to the ship's boat.";
					Link.l1.go = "exit";
				break;
				
				case 1:
					Dialog.text = "Captain, I am not going to stay on this strange ship if you are willing to take it to the port. I'd better jump in the sea myself.";
					Link.l1 = "I am not willing to do that... I am also a bit frightened...";
					Link.l1.go = "exit";
				break;
				
				case 2:
					Dialog.text = "Perhaps we should sink it, captain?";
					Link.l1 = "To let souls of the missed sailors who are living here to visit us in our nightmares?";
					Link.l1.go = "On_MaryCeleste_Deck_SailorLast_1";
				break;
			}
			
			NextDiag.TempNode = "On_MaryCeleste_Deck_SailorLast";
		break;
		
		case "On_MaryCeleste_Deck_SailorLast_1":
			Dialog.text = "Good God, no! Captain... why are you saying that?";
			Link.l1 = "Don't go pale, I was joking... Go to the ship's boat. And I guess you are right after all, perhaps cats really have souls...";
			Link.l1.go = "exit";
		break;
		// <-- Базар с нашим матросом на палубе Мэри Селест
		
        //  на палубе <--
        case "On_Fort":
			dialog.text = RandPhraseSimple("Talk with the boss. I've got nothing to say you.", "I am at my post. All questions go to the commandant of fort.");
			Link.l1 = "Fine.";
			Link.l1.go = "exit";

			NextDiag.TempNode = "On_Fort";
		break;
		
		case "On_Fort_Head":
			dialog.text = RandPhraseSimple("I am really busy now. Leave me alone.", "Don't distract me from my work. There is nothing to talk about.");
			Link.l1 = "Pity...";
			Link.l1.go = "exit";

			NextDiag.TempNode = "On_Fort_Head";
		break;
		
		case "Morgan_wait_you":
			Dialog.defAni = "dialog_stay1";
			Dialog.defCam = "1";
			Dialog.defSnd = "dialogs\0\017";
			Dialog.defLinkAni = "dialog_1";
			Dialog.defLinkCam = "1";
			Dialog.defLinkSnd = "dialogs\woman\024";
			Dialog.ani = "dialog_stay2";
			Dialog.cam = "1";
			Dialog.snd = "dialogs\0\009";

			dialog.text = RandPhraseSimple("Morgan wanted tell you 'a thing or two'... He is somewhere here, on the deck.", "Heh, find Morgan. Bad new are waiting for you...");
			Link.l1 = "Fine.";
			Link.l1.go = "exit";

			NextDiag.TempNode = "Morgan_wait_you";
		break;
	}
}
