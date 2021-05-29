// городские тюрьмы
void ProcessDialogEvent()
{
	int amount, iGunQty, iGunGoods, iGunPrice, iTemp;
	int iTest;
	ref NPChar, sld, location;
	ref arItem;
	ref rColony;
	aref Link, NextDiag;
	string sTemp;
	float locx, locy, locz;
	bool  ok;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

    // вызов диалога по городам -->
    NPChar.FileDialog2 = "DIALOGS\" + LanguageGetLanguage() + "\Prison\" + NPChar.City + "_Prison.c";
    if (LoadSegment(NPChar.FileDialog2))
	{
        ProcessCommonDialog(NPChar, Link, NextDiag);
		UnloadSegment(NPChar.FileDialog2);
	}
    // вызов диалога по городам <--

	switch(Dialog.CurrentNode)
	{
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	
		case "fight":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_group_Attack(NPChar, Pchar);
			if (rand(3) != 1) SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;

		case "NoMoreTalkExit":
			LAi_CharacterDisableDialog(npchar);
			DialogExit();
		break;
		//---------------- Начальник тюрьмы ------------------
		case "First_officer":
			dialog.text = RandPhraseSimple("I am the prison warden. What do you need here?", "What do you need? Why have you come to the prison?");
			link.l1 = "Oh, nothing special, you know, just looking around the city so wandered here on occasion.";
			link.l1.go = "exit";
			link.l2 = "I wanted to talk about some business.";
			if (CheckCharacterItem(pchar, "CaptainBook") && !CheckAttribute(pchar, "questTemp.different.GiveShipLetters.speakFort"))
			{
				if((pchar.questTemp.different.GiveShipLetters.city == npchar.city) && CheckAttribute(pchar, "questTemp.different.GiveShipLetters"))
				{
					link.l2.go = "F_ShipLetters_1";
				}
				else
				{
					link.l2.go = "quests";
				}		
			}
			else
			{
				if(CheckAttribute(pchar,"questTemp.ReasonToFast") && !CheckAttribute(pchar,"questTemp.ReasonToFast.SpeakOther") && !CheckAttribute(pchar, "questTemp.ReasonToFast.cantSpeakOther") && (pchar.questTemp.ReasonToFast.city == NPChar.city))
				{
					link.l2.go = "ReasonToFast_Prison1";
				}
				else
				{
					link.l2.go = "quests";
				}	
			}
			if (!sti(pchar.questTemp.jailCanMove))
			{
				link.l4 = "I want to come inside the prison.";
				link.l4.go = "ForGoodMove";		
			}
			if (CheckAttribute(pchar, "questTemp.jailCanMove.City") && npchar.city == pchar.questTemp.jailCanMove.City)
			{
				link.l5 = "Hey, could you tell me, for what crime is serving his time a convict by the name of " + GetFullName(characterFromId(pchar.questTemp.jailCanMove.prisonerId)) + "?";
				link.l5.go = "KnowAboutPrisoner";	
			}
			
			if(CheckAttribute(pchar,"GenQuest.CaptainComission") && (pchar.GenQuest.CaptainComission.variant == "A2") && (pchar.GenQuest.CaptainComission.City == NPChar.city))
			{
				if(!CheckAttribute(pchar,"GenQuest.CaptainComission.PrisonFree"))
				{
					bool zMsm = (CheckAttribute(pchar,"GenQuest.CaptainComission.GetRumour")) && (!CheckAttribute(pchar,"GenQuest.CaptainComission.SpeakMayor"));
					if(pchar.GenQuest.CaptainComission == "MayorTalkBad" || zMsm) //говорил с губером и отказался или узнал слухи, но не говорил с губером
					{
						link.l6 = "I've heard that former captain of a patrol " + GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name") + "Acc")) + " " + pchar.GenQuest.CaptainComission.Name + " is contained there in custody. Can I talk to him?";
						link.l6.go = "CapComission_PrisonBad1";
					}
					if(pchar.GenQuest.CaptainComission == "MayorTalkGood")
					{
						link.l6 = "I " + GetFullName(pchar) + ", acting on behalf and on order of governor " + XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Gen") + ". I need to speak with former captain " + pchar.GenQuest.CaptainComission.Name + ".";
						link.l6.go = "CapComission_PrisonGood1";
					}
				}	
			}
			if(CheckAttribute(pchar,"GenQuest.EncGirl"))
			{
				if(pchar.GenQuest.EncGirl == "toParents" || pchar.GenQuest.EncGirl == "FindLover")
				{
					if(pchar.GenQuest.EncGirl.Father == "fort_keeper"  && npchar.city == pchar.GenQuest.EncGirl.city)
					{
						link.l9 = "This is about your daughter...";
						link.l9.go = "EncGirl_1";
					}
				}
			}
			//Jason --> Бесчестный конкурент
			if (CheckAttribute(pchar, "questTemp.Shadowtrader.Fort") && NPChar.location == pchar.questTemp.Shadowtrader.City + "_prison")
			{
				link.l10 = "I have come to you on request of the local store owner, his name is "+pchar.questTemp.Shadowtrader.Tradername+". He asked me to give you this letter.";
				link.l10.go = "Shadowtrader_prison";
			}
			
			if (CheckAttribute(pchar, "questTemp.Shadowtrader.SeekTrader") && NPChar.location == pchar.questTemp.Shadowtrader.City + "_prison")
			{
				link.l10 = "That's me again. I have substantional evidence that "+pchar.questTemp.Shadowtrader.Tradername+" is right.";
				link.l10.go = "Shadowtrader_prison2";
			}
			//Jason <-- Бесчестный конкурент
			
			if (CheckAttribute(pchar, "GenQuest.Marginpassenger") && pchar.GenQuest.Marginpassenger == "begin" && NPChar.location == pchar.GenQuest.Marginpassenger.City + "_prison")
			{
				link.l12 = "I have business with you, officer. I think it would be interesting to you since it's connected to your duties.";
				link.l12.go = "Marginpassenger";
			}
			
			// Warship, 16.05.11. Генер "Justice for sale".
			if(CheckAttribute(PChar, "GenQuest.JusticeOnSale.PrisonWait") && CheckAttribute(PChar, "GenQuest.JusticeOnSale.CityId") && NPChar.location == PChar.GenQuest.JusticeOnSale.CityId + "_prison")
			{
				link.l13 = "I want to talk to you about one certain man - " + PChar.GenQuest.JusticeOnSale.SmugglerName + ". He is your prisoner, if I am not mistaken.";
				link.l13.go = "JusticeOnSale_1";
			}
			
			NextDiag.TempNode = "First_officer";
		break;

		//Jason --> мини-квест Бесчестный конкурент
		case "Shadowtrader_prison":
			dialog.text = "Again that "+pchar.questTemp.Shadowtrader.Tradername+" with his complaints! Alright, let's see what it is this time... (reads through)";
			link.l1 = "...";
			link.l1.go = "Shadowtrader_prison_1";
			RemoveItems(PChar, "letter_1", 1);
			DeleteAttribute(pchar, "questTemp.Shadowtrader.Fort");
		break;
		
		case "Shadowtrader_prison_1":
			dialog.text = "Once again, absurd guessworks and not a single strong evidence! Alright. Tell him that this is simply not enough for me to alert the guards and order them to scour the town.";
			link.l1 = "You want me to tell him that?";
			link.l1.go = "Shadowtrader_prison_2";
		break;
		
		case "Shadowtrader_prison_2":
			dialog.text = "Exactly - and, preferrably, word-for-word. He will understand what I mean. I will not waste paper to write a reply to this annoying one.";
			link.l1 = "I see. Farewell, then.";
			link.l1.go = "exit";
			pchar.questTemp.Shadowtrader.Trouble = "true";
			NextDiag.TempNode = "First_officer";
		break;
		
		case "Shadowtrader_prison2":
			dialog.text = "And what is this 'substantial' evidence that you claim to have gathered?";
			link.l1 = "I struck a deal with the smugglers regarding the purchase of goods through their unofficial store. Their agent will come today at night to the port authority office to take me to their so-called 'store'.";
			link.l1.go = "Shadowtrader_prison2_1";
			DeleteAttribute(pchar, "questTemp.Shadowtrader.SeekTrader");
			pchar.quest.ShadowtraderTimeSmugglers_Over.over = "yes";
			pchar.quest.Shadowtrader_SMG.over = "yes";//снять оба прерывания
			sld = characterFromID("ShadowAgent_1");
			sld.lifeday = 0;
		break;
		
		case "Shadowtrader_prison2_1":
			dialog.text = "Hhm... Well, excellent work, captain! Then we will act further. We'll send our man to their meeting, locate their hideout and arrest all of them. Thanks for your initiative!";
			link.l1 = "Always glad to help. I am sure that your operation will be successful.";
			link.l1.go = "exit";
			pchar.questTemp.Shadowtrader.End.Fort = "true";
			AddQuestRecord("Shadowtrader", "7");
			SaveCurrentQuestDateParam("pchar.questTemp.Shadowtrader.EndFort");
			AddCharacterExpToSkill(pchar, "Leadership", 50);//авторитет
			AddCharacterExpToSkill(pchar, "Fortune", 100);//везение
			AddCharacterExpToSkill(pchar, "Sneak", 100);//скрытность
			NextDiag.TempNode = "First_officer";
		break;
		// <-- мини-квест Бесчестный конкурент
		
		// --> Jason Похититель
		case "Marginpassenger":
			dialog.text = "Yes? What is it that you're willing to tell me?";
			link.l1 = "Recently I've been stopped on the street by "+pchar.GenQuest.Marginpassenger.Name+" who offered me to arrange a dirty deed: capturing and then ransoming a person by the name of "+pchar.GenQuest.Marginpassenger.q1Name+". It's "+pchar.GenQuest.Marginpassenger.Text+"...";
			link.l1.go = "Marginpassenger_1";
		break;
		
		case "Marginpassenger_1":
			dialog.text = "Hmm... That's very intriguing - please go on!";
			link.l1 = "He knew the name of the ship, on which "+pchar.GenQuest.Marginpassenger.q1Name+" was planning to sail. It's "+GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.Marginpassenger.ShipType), "Name")))+" called '"+pchar.GenQuest.Marginpassenger.ShipName+"'. Also, he told me the time when that ship was supposed to set sail.";
			link.l1.go = "Marginpassenger_2";
		break;
	
		case "Marginpassenger_2":
			dialog.text = "And he suggested you capturing the passenger and then demanding ransom for him?";
			link.l1 = "Exactly. To collect ransom, I would go to "+XI_ConvertString("Colony"+pchar.GenQuest.Marginpassenger.Targetcity)+", to a certain person by the name of "+pchar.GenQuest.Marginpassenger.q2Name+". I paid him for this information, but of course, I wasn't going to kidnap that person.";
			link.l1.go = "Marginpassenger_3";
		break;
		
		case "Marginpassenger_3":
			dialog.text = "So you decided to come see me and let me know?";
			link.l1 = "Exactly. I am certain that the actions of that scoundrel are threatening the citizens of your town, and I hope that you would take adequate measures.";
			link.l1.go = "Marginpassenger_4";
		break;
		
		case "Marginpassenger_4":
			dialog.text = "You were quite right when came to me, "+GetAddress_Form(NPChar)+"! This rascal, "+pchar.GenQuest.Marginpassenger.Name+", has long been under our tracking. I'll investigate, and if all that you said is confirmed, we'll throw this bastard behind bars for half a year. That'll teach him not to build all sorts of machinations against respected citizens\nWell, for your honesty and willingness to serve a good cause, I certainly will report our governor, which, of course, will affect his attitude towards you... as you know, in a positive way. Thanks for your help, captain!";
			link.l1 = "Hmm... You're welcome, it was a pleasure to help. Goodbye!";
			link.l1.go = "Marginpassenger_5";
		break;
		
		case "Marginpassenger_5":
			DialogExit();
			NextDiag.CurrentNode = "First_officer";
			AddQuestRecord("Marginpassenger", "20");
			AddQuestUserData("Marginpassenger", "sName", pchar.GenQuest.Marginpassenger.Name);
			CloseQuestHeader("Marginpassenger");
			pchar.quest.Marginpassenger_InWorld.over = "yes"; //снять таймер
			DeleteAttribute(Pchar, "GenQuest.Marginpassenger");
			ChangeCharacterComplexReputation(pchar, "nobility", 3);
			ChangeCharacterNationReputation(pchar, sti(npchar.Nation), 5);
			AddCharacterExpToSkill(pchar, "Leadership", 100);//авторитет
			ChangeContrabandRelation(pchar, -25);
			if (GetCharacterIndex("MarginCap") != -1)
			{
				sld = characterFromId("MarginCap");
				sld.lifeday = 0;
				Map_ReleaseQuestEncounter(sld.id);
				Group_DeleteGroup("Sea_MarginCap1");
			}
		break;
		//<-- Похититель

		case "EncGirl_1":
			dialog.text = "I am all ears.";
			link.l1 = "I've brought your fugitive.";
			link.l1.go = "EncGirl_2";
		break;
		
		case "EncGirl_2":
			dialog.text = "Oh, captain, thank you so much! How is she? Is she hurt? Why did she run away? Why?\nDoesn't she understand? The groom is a wealthy and important man! Youth is naive and foolish... cruel even. Remember that!";
			link.l1 = "Well, you are her father and the final decision is yours, but I would not hurry with the wedding...";
			link.l1.go = "EncGirl_3";
		break;
		
		case "EncGirl_3":
			dialog.text = "What do you know? Do you have your own children? No? When you've got one, come to see me and we will talk\nI promised a reward to anyone who'd take her back to her family.";
			link.l1 = "Thanks. You should keep an eye on her. I have a hunch that she won't stop at that.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("EncGirl_ToLoverParentsExit");
		break;
		
		// ------------------------- Повод для спешки -----------------------------
		case "ReasonToFast_Prison1":
			pchar.questTemp.ReasonToFast.SpeakOther = true;
			dialog.text = "I am all ears, captain.";
			link.l1 = "I want to tell you about a criminal collusion between an officer of your garrison and pirates (explains the matter).";
			if(makeint(pchar.reputation.nobility) < 41)
			{
				link.l1.go = "ReasonToFast_Prison_BadRep";			
			}
			else
			{
				link.l1.go = "ReasonToFast_Prison_GoodRep";	
			}
		break;
		case "ReasonToFast_Prison_GoodRep":
			if(pchar.questTemp.ReasonToFast == "PatrolSuccess_1") 
			{ 
				// вилка_А
				dialog.text = "Thank you,"+ GetSexPhrase("mister","miss") +"! I will immediately give the order to arrest the villain.\nHowever, you have incurred costs and municipal coffers, alas, are empty...";
				link.l1 = "Your Highness! I did it not for the money...";
				link.l1.go = "ReasonToFast_Prison_GoodRep_11";
				
				if(pchar.questTemp.ReasonToFast.chain == "A0") ReasonToFast_RemoveVictim();
				if(pchar.questTemp.ReasonToFast.chain == "A1") pchar.quest.ReasonToFast_ClearLakey.over = "yes";
			}
			if(pchar.questTemp.ReasonToFast == "PatrolSuccess_2") 
			{ 
				// получена карта
				dialog.text = "Thank you, "+ GetSexPhrase("mister","miss") +"! I will immediately give the order to arrest the villain.\nThink of it! We wanted to reward him with personal weapon for the excellent service. How nice that all cleared up, and I got nothing to shame!";
				link.l1 = "Always glad to serve justice.";
				link.l1.go = "ReasonToFast_Prison_GoodRep_21";			
			}
			if(pchar.questTemp.ReasonToFast == "PatrolDied") 
			{ 
				// патруль перебит
				dialog.text = "Mi"+ GetSexPhrase("ster","ss") +"! We had been suspecting that officer and his scum-lads for quite some time in dirty deeds, but I think that you made a rash move when dealt with them without witnesses.";
				link.l1 = "Your Highness! But I had to defend myself...";
				link.l1.go = "ReasonToFast_Prison_GoodRep_31";	
				pchar.questTemp.ReasonToFast.speakAfterPatrolDied = true;	
				pchar.quest.ReasonToFast_SpeakMayor.over = "yes";	
			}
		break;
		
		case "ReasonToFast_Prison_BadRep":
			if(pchar.questTemp.ReasonToFast == "PatrolSuccess_1") 
			{ 
				// вилка_А
				dialog.text = "Captain, do you realize what you've done?!! We've been attempting to set up this trap for over a month! And now, just for your entertainment, you've wrecked the meeting of our patrol with messenger " + GetName( NAMETYPE_MAIN, pchar.questTemp.ReasonToFast.p3, NAME_GEN) + " and now you're coming here to boast?!! Perhaps, you can tell me now, how should I explain all expenses and costs of this operation?!";
				link.l1 = "Your Grace! You're just refusing to see the point...";
				link.l1.go = "ReasonToFast_Prison_BadRep1";
				pchar.questTemp.ReasonToFast = "speakSuccess_chain_A";
				
				if(pchar.questTemp.ReasonToFast.chain == "A0") ReasonToFast_RemoveVictim();
				if(pchar.questTemp.ReasonToFast.chain == "A1") pchar.quest.ReasonToFast_ClearLakey.over = "yes";
			}
			if(pchar.questTemp.ReasonToFast == "PatrolSuccess_2") 
			{ 
				// получена карта
				dialog.text = "Let me look at this map\nAre you kidding me? This tattered piece of parchment is a proof?";
				link.l1 = "Your Grace! You're just refusing to see the point...";
				link.l1.go = "ReasonToFast_Prison_BadRep1";
				TakeItemFromCharacter(pchar, "mapQuest");	
				pchar.questTemp.ReasonToFast = "speakSuccess_chain_B";	
			}
			if(pchar.questTemp.ReasonToFast == "PatrolDied") 
			{ 
				// патруль перебит
				dialog.text = "Now that's an original justification of the destruction of the entire patrolling group. Well, at least by coming here you spared us the need to look for the murderer.";
				link.l1 = "Your Grace! You're just refusing to see the point...";
				link.l1.go = "ReasonToFast_Prison_BadRep1";			
				pchar.questTemp.ReasonToFast = "speakSuccess_chain_A";
				pchar.quest.ReasonToFast_SpeakMayor.over = "yes";
			}		
		break;
		
		case "ReasonToFast_Prison_GoodRep_11":
			dialog.text = "Nonetheless I think that your efforts should still be rewarded. Here - take this map; it was found in the belongings of one pirate, who have recently gone to the gallows. God willing, perhaps you will actually find that treasure, although I find it quite unlikely...";
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
		case "ReasonToFast_Prison_GoodRep_21":
			dialog.text = "Your zeal is commendable. Please, accept this blade as a reward - it's the least I can do for you. Oh, and you can keep this map for yourself. I am certain that there's a lot of such fakes on the Archipelago.";
			link.l1 = "Thank you, that's very generous of you!";
			link.l1.go = "exit";
			AddQuestRecord("ReasonToFast", "14");
			ChangeCharacterComplexReputation(pchar,"nobility", 1); 
			GiveItem2Character(pchar, pchar.questTemp.ReasonToFast.p6);
			pchar.questTemp.ReasonToFast.state = "chain_B"; // была получена карта
			pchar.questTemp.ReasonToFast = "GetMap";			
			ReasonToFast_SetHunterCoastal();
		break;
		case "ReasonToFast_Prison_GoodRep_31":
			dialog.text = "Might be, might be... Well, let's just say that this deal was decided by divine justice and by our Lord's will.";
			link.l1 = "Thank you, that's very generous of you!";
			link.l1.go = "exit";
			ChangeCharacterComplexReputation(pchar,"nobility", 1); 
			AddQuestRecord("ReasonToFast", "16");
			CloseQuestHeader("ReasonToFast");
			DeleteAttribute(pchar,"ReasonToFast");			
		break;
		
		case "ReasonToFast_Prison_BadRep1":
			dialog.text = "Don't dare lecturing me! To me, it is obvious that you are in collaboration with these scoundrels! Guards, seize "+ GetSexPhrase("this 'well-wisher'","this 'well-wisher'") +"!";
			link.l1 = "No way!";
			link.l1.go = "fight";
			
			pchar.quest.ReasonToFast_ExitFromTown.win_condition.l1			= "EnterToSea";           	
            pchar.quest.ReasonToFast_ExitFromTown.function    				= "ReasonToFast_ExitFromTownFight";
			pchar.questTemp.ReasonToFast.canSpeakSailor = true;			
			pchar.TownEscape = true;
			Flag_PIRATE();
		break;
		// ------------------------- Повод для спешки -----------------------------
		
		// -------------------------- Операция 'Галеон' ----------------------------
		case "CapComission_PrisonBad1":
			dialog.text = "And what business do you have with him?";
			link.l1 = "I have several private affairs to discuss with him.";
			link.l1.go = "CapComission_PrisonBad2";
		break;
		
		case "CapComission_PrisonBad2":
			dialog.text = "Captain, I have a direct order to detain and send to the residence for further interrogation anyone asking about " + pchar.GenQuest.CaptainComission.Name + ".";
			link.l1 = "Nice setup have you here! Having prisoners themselves come to you to be arrested!";
			link.l1.go = "CapComission_PrisonBad3";
		break;
		
		case "CapComission_PrisonBad3":
			dialog.text = "And nevertheless I would request that you surrender your weapons!";
			link.l1 = "Screw you! Take it away from me by force, then!";
			link.l1.go = "fight";
			AddDialogExitQuest("CaptainComission_GenerateCapJail");
		break;
		
		case "CapComission_PrisonGood1":
			dialog.text = "Yes, of course. I have orders from the governor to render you assistance in this affair. You can now visit the prisoner.";
			link.l1 = "Thank you...";
			link.l1.go = "exit";
			pchar.questTemp.jailCanMove = true;
			AddDialogExitQuest("CaptainComission_GenerateCapJail");
		break;
		
		case "CapComission_PrisonFree1":
			dialog.text = "Ehm, captain, I don't have direction to discharge this prisoner from custody. You must request a permission from the governor.";
			link.l1 = "Officer, I am acting for the good of the inquest. The prisoner agreed to cooperate with the authorities and reveal the cache. Time is on the essence - the smugglers can find the precious cargo, and then it will be lost for the populace.";
			link.l1.go = "CapComission_PrisonFree2";
		break;
		
		case "CapComission_PrisonFree2":
			dialog.text = "But I could assign escort to him.";
			link.l1 = "There's no need to - I have enough guards. Besides, I wouldn't want the location of the cache to be made public.";
			link.l1.go = "CapComission_PrisonFree3";
		break;
		
		case "CapComission_PrisonFree3":
			dialog.text = "Hmm... oh, well. But you'll be answering for him with your head.";
			link.l1 = "Of course.";
			link.l1.go = "exit";
			NextDiag.TempNode = "First_officer";
			NextDiag.CurrentNode = NextDiag.TempNode; 
			AddDialogExitQuest("OpenTheDoors");
		break;
		// -------------------------- Операция 'Галеон' ----------------------------
		
		case "F_ShipLetters_1":
			dialog.text = "Speak now, I'm listening.";
			link.l1 = "I have some ship documentation with me. Its owner must have lost it, and I believe it might be of some interest to you.";
			link.l1.go = "F_ShipLetters_2";
			pchar.questTemp.different.GiveShipLetters.speakFort = true;
		break;
		
		case "F_ShipLetters_2":			
			if(sti(pchar.questTemp.different.GiveShipLetters.variant) == 0)
			{
				dialog.text = "Bullshit! Don't distract me from my work! Go to the port authorities, if you care!";
				link.l1 = "Well, thanks, I guess...";
				link.l1.go = "exit";
			}
			else
			{
				if(!CheckAttribute(pchar, "questTemp.different.GiveShipLetters.speakUsurer_1"))
				{
					dialog.text = "Yes, it's the local owner. Perhaps, a prize of " + sti(pchar.questTemp.different.GiveShipLetters.price2) + " pesos will serve as a deserving reward for your vigilance, captain.";
					link.l1 = "Perhaps not.";
					link.l1.go = "F_ShipLetters_3";	
					link.l2 = "A generous offer. The documents are yours, then!";
					link.l2.go = "F_ShipLetters_4";
				}
				else
				{
					if(sti(pchar.questTemp.different.GiveShipLetters.variant) == 1)
					{
						dialog.text = "Oh, now that's really interesting! I believe the city treasury will gladly pay you "+ sti(pchar.questTemp.different.GiveShipLetters.price4) +" pesos for your contribution in fighting illegal trade.";
						link.l1 = "Perhaps not.";
						link.l1.go = "F_ShipLetters_3";
						link.l2 = "A generous offer. The documents are yours, then!";
						link.l2.go = "F_ShipLetters_4";
					}
					if(sti(pchar.questTemp.different.GiveShipLetters.variant) == 2)
					{
						dialog.text = "Oh Lord! What a good chance that you've come to me. I guess my ill-starred colleague will gladly pay you " + sti(pchar.questTemp.different.GiveShipLetters.price3) + " pesos in order to avoid publicity of this affair.";
						link.l1 = "Perhaps not.";
						link.l1.go = "F_ShipLetters_3";
						link.l2 = "A generous offer. The documents are yours, then!";
						link.l2.go = "F_ShipLetters_4";
					}
				}
			}
		break;
		
		case "F_ShipLetters_3":
			dialog.text = "This is my city, captain.";
			link.l1 = "I'll remember that.";
			link.l1.go = "exit";
		break;
		
		case "F_ShipLetters_4":
			TakeItemFromCharacter(pchar, "CaptainBook"); 
			if(sti(pchar.questTemp.different.GiveShipLetters.variant) == 1)
			{
				if(!CheckAttribute(pchar, "questTemp.different.GiveShipLetters.speakUsurer_1"))
				{
					addMoneyToCharacter(pchar, sti(pchar.questTemp.different.GiveShipLetters.price2)); 
				}
				else
				{
					addMoneyToCharacter(pchar, sti(pchar.questTemp.different.GiveShipLetters.price4)); 
				}
			}
			if(sti(pchar.questTemp.different.GiveShipLetters.variant) == 2)
			{
				if(!CheckAttribute(pchar, "questTemp.different.GiveShipLetters.speakUsurer_1"))
				{
					addMoneyToCharacter(pchar, sti(pchar.questTemp.different.GiveShipLetters.price2)); 
				}
				else
				{
					addMoneyToCharacter(pchar, sti(pchar.questTemp.different.GiveShipLetters.price3)); 
				}
			}
						
			if((sti(pchar.questTemp.different.GiveShipLetters.variant) == 0) || (sti(pchar.questTemp.different.GiveShipLetters.variant) == 2))
			{	
				ChangeCharacterComplexReputation(pchar,"nobility", -1); 
				OfficersReaction("bad"); 
			}	
			pchar.questTemp.different = "free";
			pchar.quest.GiveShipLetters_null.over = "yes"; //снимаем таймер 
			AddQuestRecord("GiveShipLetters", "8");			
			CloseQuestHeader("GiveShipLetters");
			DeleteAttribute(pchar, "questTemp.different.GiveShipLetters");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		
        case "ForGoodMove":
			dialog.text = NPCStringReactionRepeat("But why do you need it? Trust me, there is nothing worth any interest, save for thieves and bandits.", "We had already discussed that wish of yours.", 
				"Again? We had already talked about it twice!", "Hmm, again...", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Nevertheless, I would like to spend your tour of the casemates. I'm very interested!", "Yes, exactly. But I wanted to talk about it.", 
				"Well, maybe the third time...", "Hope to see your prisoners doesn't leave me.", npchar, Dialog.CurrentNode);
			link.l1.go = "ForGoodMove_1";
		break;
		
        case "ForGoodMove_1":
			pchar.questTemp.jailCanMove.money = 20+drand(3)*10;
			if (sti(colonies[FindColony(npchar.city)].jail) && GetCharacterItem(pchar, "gold_dublon") >= sti(pchar.questTemp.jailCanMove.money))
			{
				dialog.text = "Well, I see no reason to refuse. " + FindRussianDublonString(sti(pchar.questTemp.jailCanMove.money)) + " - and until you leave the prison, you can freely walk along the corridors and even converse with the inmates.";
				link.l1 = "I agree, here are your coins!";
				link.l1.go = "ForGoodMove_agree";
				link.l2 = "That won't work. It's too much for aimless wandering along the corridors.";
				link.l2.go = "exit";
			}
			else
			{
				dialog.text = RandPhraseSimple("No, this is strictly prohibited by the regulations. What? Do you think we have there a circus? Get lost and don't distract me from my duties.", "I cannot allow strange people to walk around in my prison. Please, stop bothering me!");
				link.l1 = "Alright, as you say...";
				link.l1.go = "exit";
			}
		break;
		
        case "ForGoodMove_agree":
            dialog.text = "All right, you can start your excursion now...";
			link.l1 = "Thank you, officer.";
			link.l1.go = "exit";
			pchar.questTemp.jailCanMove = true;
			RemoveItems(pchar, "gold_dublon", sti(pchar.questTemp.jailCanMove.money));
			Log_Info("You have given " + FindRussianDublonString(sti(pchar.questTemp.jailCanMove.money)) + "");
		break;
		
        case "KnowAboutPrisoner":
			switch (pchar.questTemp.jailCanMove.ownerPrison)
			{
				case "0": sTemp = "For murder."; break;
				case "1": sTemp = "He is accused of piracy."; break;
				case "2": sTemp = "For banditry and robbery."; break;
				case "3": sTemp = "For thievery."; break;
				case "4": sTemp = "For petty thieving."; break;
				case "5": sTemp = "For sharp practice."; break;
				case "6": sTemp = "For vagrancy and begging."; break;
			}
			dialog.text = sTemp;
			link.l1 = "I see... And is there a possibility of a buyout, bail... or releasing him in some other way?";
			link.l1.go = "KnowAboutPrisoner_" + pchar.questTemp.jailCanMove.ownerPrison;
			DeleteAttribute(pchar, "questTemp.jailCanMove.City");
		break;
		
        case "KnowAboutPrisoner_0":
			dialog.text = "Of course, not. That gallows-bird will go straight to hell. Governor has his cause on a special control!";
			link.l1 = "Heh, I see...";
			link.l1.go = "notFree_exit";
		break;	
		
		case "KnowAboutPrisoner_1":
			dialog.text = "Are you joking? He must have gone to the gallows long ago! He will surely wed a rope soon. Just forget it.";
			link.l1 = "Got it. And already forgotten...";
			link.l1.go = "notFree_exit";
		break;
		
        case "KnowAboutPrisoner_2":
			dialog.text = "I don't think so. He's caused a lot of trouble to our townsfolk. So don't ask for it.";
			link.l1 = "Hmm, I see.";
			link.l1.go = "notFree_exit";
		break;
		
        case "KnowAboutPrisoner_3":
			dialog.text = "Probably not. He's a thief, and a thief must stay in a jail.";
			link.l1 = "Oh! Well said, lieutenant!";
			link.l1.go = "notFree_exit";
		break;
		
        case "KnowAboutPrisoner_4":
			dialog.text = "I don't know, really. He's stolen just a petty thing. I cannot set him free, but leaving him rotting in jail certainly isn't right.";
			link.l1 = "Well, then give him to me, lieutenant. I will pay bail for him - a reasonable amount, of course.";
			link.l1.go = "KnowAboutPrisoner_free";
		break;
		
        case "KnowAboutPrisoner_5":
			dialog.text = "Releasing? That seems probable. In my opinion, there is no point in detaining that petty crook here.";
			link.l1 = "Well, then give him to me, lieutenant. I will pay bail for him - a reasonable amount, of course.";
			link.l1.go = "KnowAboutPrisoner_free";
		break;
		
		case "KnowAboutPrisoner_6":
			dialog.text = "Hmm... There 's reason in your words. This tramp doesn't belong here - he only spreading filth and flees...";
			link.l1 = "Well, then give him to me, lieutenant. I will pay bail for him - a reasonable amount, of course.";
			link.l1.go = "KnowAboutPrisoner_free";
		break;
		
        case "KnowAboutPrisoner_free":
			pchar.questTemp.jailCanMove.ownerPrison.money = 50+drand(10)*10;
			dialog.text = "Alright, we have a deal. " + FindRussianDublonString(sti(pchar.questTemp.jailCanMove.ownerPrison.money)) + " on the nail, and you can take him away right now.";
			if (GetCharacterItem(pchar, "gold_dublon") >= sti(pchar.questTemp.jailCanMove.ownerPrison.money))
			{
				link.l1 = LinkRandPhrase("Excellent! I agree!","You have a bargain, officer!","Excellent. I am ready to pay that contribution.");
				link.l1.go = "KnowAboutPrisoner_agree";
			}
			link.l2 = "No, that's too expensive. I think I'll pass.";
			link.l2.go = "KnowAboutPrisoner_exit";
		break;
		
        case "KnowAboutPrisoner_agree":
			dialog.text = "Fine, you can proceed to his cell and take that ragamuffin with you.";
			link.l1 = "Thanks.";
			link.l1.go = "exit";
			pchar.questTemp.jailCanMove = true;
			RemoveItems(pchar, "gold_dublon", sti(pchar.questTemp.jailCanMove.ownerPrison.money));
			Log_Info("You have given " + FindRussianDublonString(sti(pchar.questTemp.jailCanMove.ownerPrison.money)) + "");
			DeleteAttribute(pchar, "questTemp.jailCanMove.ownerPrison");
			sld = characterFromId(pchar.questTemp.jailCanMove.prisonerId)
			LAi_CharacterEnableDialog(sld);
			sld.dialog.currentnode = "ToPrisonHead_canMove";
		break;
		
        case "KnowAboutPrisoner_exit":
			dialog.text = "Well, it's your choice. I am not giving you another chance...";
			link.l1 = "No need to.";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.jailCanMove.ownerPrison");
			sld = characterFromId(pchar.questTemp.jailCanMove.prisonerId);
			LAi_CharacterEnableDialog(sld);
			sld.dialog.currentnode = "ToPrisonHead_expansive";
		break;
		
        case "notFree_exit":
			sld = characterFromId(pchar.questTemp.jailCanMove.prisonerId);
			LAi_CharacterEnableDialog(sld);
			sld.dialog.currentnode = "ToPrisonHead_notFree";
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		//---------------- Протектор ------------------
        case "First_protector":
			if (sti(pchar.questTemp.jailCanMove))
			{
				dialog.text = RandPhraseSimple("You can pass, the warden gave his permission.", "I've received an order from the prison warden. You may pass freely.");
				link.l1 = "Very good.";
				link.l1.go = "exit";
				DeleteAttribute(pchar, "questTemp.jailCanMove.ownerPrison.money");
			}
			else
			{
				dialog.text = RandPhraseSimple("You may go no further without specific permission from the prison warden!", "I answer to the prison warden only! If you attempt to go further without his permission, you're done for!");
				link.l1 = RandPhraseSimple("I see", "Alright") + ", soldier.";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "First_protector";
		break;
		//---------------- Солдаты ------------------
        case "First_soldier":
            dialog.text = RandPhraseSimple("I am on duty, don't bother me.", "Come along, I am not allowed to talk to you.");
			link.l1 = "Fine, soldier.";
			link.l1.go = "exit";
			NextDiag.TempNode = "First_soldier";
		break;
		//---------------- Заключенные ------------------
        case "First_prisoner": 
			if (GetNationRelation2MainCharacter(sti(npchar.nation)) == RELATION_ENEMY)
			{
				dialog.text = LinkRandPhrase("Ho-ho, isn't that a great time!", "Cut them, "+ GetSexPhrase("buddy","lass") +", cut!!!", "Oh, hell! I have lost all hope to see the corpse of my jailer!");
				link.l1 = RandPhraseSimple("Heh!", "Arrgh!");
				link.l1.go = "NoMoreTalkExit";
				if (rand(10) > 6 && !CheckAttribute(pchar, "questTemp.Sharlie.Lock") && !CheckAttribute(pchar, "GenQuest.PrisonQuestLock") && !CheckAttribute(pchar, "quest.GivePrisonFree") && !CheckAttribute(pchar, "quest.GivePrisonFree_Over") && !CheckAttribute(pchar, "quest.DeliverToBander")) // Addon 2016-1 Jason пиратская линейка
				{
					dialog.text = RandPhraseSimple("Hold on, "+ GetSexPhrase("buddy","lass") +"!! Release me!", "Listen, "+ GetSexPhrase("buddy","lass") +", kindly open the cell.");
					link.l1 = "For what reason?";
					link.l1.go = "Prisoner_1"; // на квест освобождения заключенного
				}
			}
			else
			{
				dialog.text = LinkRandPhrase("I am accused of robbery, but I'm not guilty!", "Arrgh, you well-groomed scum... Would you like to sit in my cell a bit?! Kheh-heh-heh...", "I am not guilty!");
				link.l1 = RandPhraseSimple("Shut up!", "I don't give a shit about you...");
				link.l1.go = "NoMoreTalkExit";
				if (rand(10) > 6 && !CheckAttribute(pchar, "questTemp.Sharlie.Lock") && !CheckAttribute(pchar, "GenQuest.PrisonQuestLock") && !CheckAttribute(pchar, "quest.GivePrisonFree_Over") && !CheckAttribute(pchar, "quest.GivePrisonFree") && !CheckAttribute(pchar, "quest.DeliverToBander") && !sti(colonies[FindColony(npchar.city)].HeroOwn)) // Addon 2016-1 Jason пиратская линейка
				{
					dialog.text = RandPhraseSimple("Hold on, "+ GetSexPhrase("buddy","lass") +", don't come by so fast!", "Don't hurry, "+ GetSexPhrase("buddy","lass") +", let's talk.");
					link.l1 = "For what reason?";
					if (rand(1))
					{
						link.l1.go = "Prisoner_1"; // на квест освобождения заключенного
					}
					else
					{
						link.l1.go = "Deliver_1"; // на квест передачу весточки
					}
				}
			}
		break;
		// -------------------- освобождение заключенного --------------------
        case "Prisoner_1":
            dialog.text = "Listen to me, buddy. Don't think that I'm not looking good and stuff. I just need to get out of here...";
			link.l1 = "What?!";
			link.l1.go = "Prisoner_2";
			GetChestPlaceName();
			pchar.questTemp.jailCanMove.prisonerId = npchar.id; //запомним Id
			pchar.questTemp.jailCanMove.IsTrue = rand(4); //вид клада
			pchar.questTemp.jailCanMove.Item1 = GenQuestPrison_GenerateArtefact();
			pchar.questTemp.jailCanMove.Item2 = GenQuestPrison_GenerateBlade();
			pchar.questTemp.jailCanMove.Name = GetFullName(npchar); //имя перца
		break;
        case "Prisoner_2":
            dialog.text = "What you heard! Help me out, and I'll be able to repay...";
			link.l1 = "Now that's interesting. Who are you and what can you offer me?";
			link.l1.go = "Prisoner_3";
		break;
        case "Prisoner_3":
            dialog.text = "My name is " + GetFullName(npchar) + ". I have some stuff stashed at a safe place. Just get me out of here and take me to " + XI_ConvertString(pchar.questTemp.jailCanMove.islandId + "Acc") + ". There, in a grotto, I have the treasure. We'll get it and share!";
			link.l1 = "And what do you have in your stash? And how can I know that you're telling the truth?";
			link.l1.go = "Prisoner_4";
		break;
        case "Prisoner_4":
            dialog.text = "I swear I am telling the truth! As for the stash -there is treasure and money...";
			link.l1 = "No, buddy. I am not risking my hide for a questionable stash. I am sorry...";
			link.l1.go = "Prisoner_5";
			if (GetNationRelation2MainCharacter(sti(npchar.nation)) != RELATION_ENEMY)
			{			
				link.l2 = "Well, it might be worth taking a risk... I suggest the following: I can eliminate the guards in the prison and take you to my ship. If everything works out, I want you to stay at my side all the time until we get to the grotto on  " + XI_ConvertString(pchar.questTemp.jailCanMove.islandId + "Dat") + ". Deal?";
				link.l2.go = "Prisoner_agree"; //силовой способ вызволения
				link.l3 = "Alright, I'll try to help you. I'll speak to the prison warden. Perhaps, I'll be able to bail you out.";
				link.l3.go = "ToPrisonHead_agree"; //мирный способ вызволения
			}
			else
			{
				link.l2 = "Okay, I'll believe you and open your cell. I want you to stay at my side all the time until we get to the grotto on " + XI_ConvertString(pchar.questTemp.jailCanMove.islandId + "Dat") + ". Deal?";
				link.l2.go = "Prisoner_agree_3"; //силовой способ вызволения, когда тюремщики убиты
			}
		break;
        case "Prisoner_5":
            dialog.text = RandPhraseSimple("Damn you, you rascal!", "Damn you ripped, scum...");
			link.l1 = RandPhraseSimple("And all the best to you, too. Farewell...", "The moon doesn't need the barking of dogs...");
			link.l1.go = "NoMoreTalkExit";
		break;
        case "Prisoner_agree":
            dialog.text = "Fine. I am not in a position to be picky.";
			link.l1 = "Alright. I will break your lock now to get you out, and we will break through. Are you ready?";
			link.l1.go = "Prisoner_agree_1";
		break;
        case "Prisoner_agree_1":
            dialog.text = "Yes, "+ GetSexPhrase("buddy","lass") +", I am ready!";
			link.l1 = "Then let's get to it!";
			link.l1.go = "Prisoner_agree_2";
		break;
        case "Prisoner_agree_2":
			string slai_group = GetNationNameByType(sti(npchar.nation))  + "_citizens";
			LAi_group_AttackGroup(slai_group, LAI_GROUP_PLAYER);
			if (rand(3) != 1) SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
			ReOpenQuestHeader("GivePrisonFree");
			AddQuestRecord("GivePrisonFree", "1");
            AddQuestUserData("GivePrisonFree", "sCity", XI_ConvertString("Colony"+npchar.city+"Gen"));
            AddQuestUserData("GivePrisonFree", "sName", pchar.questTemp.jailCanMove.Name);
            AddQuestUserData("GivePrisonFree", "sIsland", XI_ConvertString(pchar.questTemp.jailCanMove.islandId+"Dat"));
			pchar.quest.GivePrisonFree_Death.win_condition.l1 = "NPC_Death";
			pchar.quest.GivePrisonFree_Death.win_condition.l1.character = npchar.id;
			pchar.quest.GivePrisonFree_Death.win_condition = "GivePrisonFree_Death";
			Pchar.quest.GivePrisonFree.win_condition.l1 = "location";
			Pchar.quest.GivePrisonFree.win_condition.l1.location = pchar.questTemp.jailCanMove.placeId;
			Pchar.quest.GivePrisonFree.win_condition = "GivePrisonFree";			
			DeleteAttribute(npchar, "LifeDay");
			GiveItem2Character(npchar, "unarmed");
			EquipCharacterbyItem(npchar, "unarmed");
			GetCharacterPos(npchar, &locx, &locy, &locz);	
			ChangeCharacterAddressGroup(npchar, npchar.location, "reload", LAi_FindNearestFreeLocator("reload", locx, locy, locz));
			LAi_SetActorType(npchar);
			LAi_group_Register("DeliveQuest_Prison");
			LAi_group_SetRelation("DeliveQuest_Prison", LAI_GROUP_PLAYER, LAI_GROUP_FRIEND);
			//LAi_group_SetAlarmReaction(LAI_GROUP_PLAYER, "DeliveQuest_Prison", LAI_GROUP_ENEMY, LAI_GROUP_FRIEND);
			LAi_group_MoveCharacter(npchar, "DeliveQuest_Prison");
			LAi_ActorFollowEverywhere(npchar, "", -1);
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;

        case "Prisoner_agree_3":
            dialog.text = "Fine. I am not in a position to be picky.";
			link.l1 = "Alright. Follow me as quickly as you can - we still need to get to my ship. Don't delay!";
			link.l1.go = "Prisoner_agree_4";
		break;
        case "Prisoner_agree_4":
			ReOpenQuestHeader("GivePrisonFree");
			AddQuestRecord("GivePrisonFree", "1");
            AddQuestUserData("GivePrisonFree", "sCity", XI_ConvertString("Colony"+npchar.city+"Gen"));
            AddQuestUserData("GivePrisonFree", "sName", pchar.questTemp.jailCanMove.Name);
            AddQuestUserData("GivePrisonFree", "sIsland", XI_ConvertString(pchar.questTemp.jailCanMove.islandId+"Dat"));
			pchar.quest.GivePrisonFree_Death.win_condition.l1 = "NPC_Death";
			pchar.quest.GivePrisonFree_Death.win_condition.l1.character = npchar.id;
			pchar.quest.GivePrisonFree_Death.win_condition = "GivePrisonFree_Death";
			Pchar.quest.GivePrisonFree.win_condition.l1 = "location";
			Pchar.quest.GivePrisonFree.win_condition.l1.location = pchar.questTemp.jailCanMove.placeId;
			Pchar.quest.GivePrisonFree.win_condition = "GivePrisonFree";
			DeleteAttribute(npchar, "LifeDay");
			GiveItem2Character(npchar, "unarmed");
			EquipCharacterbyItem(npchar, "unarmed");
			GetCharacterPos(npchar, &locx, &locy, &locz);	
			ChangeCharacterAddressGroup(npchar, npchar.location, "reload", LAi_FindNearestFreeLocator("reload", locx, locy, locz));
			LAi_SetActorType(npchar);
			LAi_group_Register("DeliveQuest_Prison");
			LAi_group_SetRelation("DeliveQuest_Prison", LAI_GROUP_PLAYER, LAI_GROUP_FRIEND);
			//LAi_group_SetAlarmReaction(LAI_GROUP_PLAYER, "DeliveQuest_Prison", LAI_GROUP_ENEMY, LAI_GROUP_FRIEND);
			LAi_group_MoveCharacter(npchar, "DeliveQuest_Prison");
			LAi_ActorFollowEverywhere(npchar, "", -1);
			DialogExit();
		break;

        case "ToPrisonHead_agree":
            dialog.text = "Well, you can try. Hope we'll pull it through! But don't waste time - in a couple of days I will be out of here...";
			link.l1 = "Wait here, I'll arrange everything.";
			link.l1.go = "NoMoreTalkExit";
			pchar.questTemp.jailCanMove.City = npchar.City; //город
			pchar.questTemp.jailCanMove.ownerPrison = rand(6); //характер преступления
			SetTimerCondition("GivePrisonFree_Over", 0, 0, 2, false);
			AddQuestRecord("GivePrisonFree", "5");
			AddQuestUserData("GivePrisonFree", "sSex", GetSexPhrase("",""));
            AddQuestUserData("GivePrisonFree", "sCity", XI_ConvertString("Colony"+npchar.city+"Gen"));
            AddQuestUserData("GivePrisonFree", "sName", pchar.questTemp.jailCanMove.Name);
		break;

        case "ToPrisonHead_canMove":
            dialog.text = "Well, what do you say, "+ GetSexPhrase("buddy","lass") +"?";
			link.l1 = "Everything has been arranged, and I can take you from here.";
			link.l1.go = "ToPrisonHead_canMove_1";
		break;
        case "ToPrisonHead_canMove_1":
            dialog.text = "Then let's get out of here! Oh, Lord, how happy I am!";
			link.l1 = "Let's sum it up. I want you to stay at my side all the time until we get to the grotto on " + XI_ConvertString(pchar.questTemp.jailCanMove.islandId + "Dat") + ", you won't leave me farther a single step. Just in case. Do you agree?";
			link.l1.go = "ToPrisonHead_canMove_2";
		break;
        case "ToPrisonHead_canMove_2":
            dialog.text = "Of course, I agree! All the more that I am not in a position to choose.";
			link.l1 = "Then you are free.";
			link.l1.go = "ToPrisonHead_canMove_exit";
		break;
        case "ToPrisonHead_canMove_exit":
			pchar.quest.GivePrisonFree_Over.over = "yes";
			ReOpenQuestHeader("GivePrisonFree");
			AddQuestRecord("GivePrisonFree", "1");
            AddQuestUserData("GivePrisonFree", "sCity", XI_ConvertString("Colony"+npchar.city+"Gen"));
            AddQuestUserData("GivePrisonFree", "sName", pchar.questTemp.jailCanMove.Name);
            AddQuestUserData("GivePrisonFree", "sIsland", XI_ConvertString(pchar.questTemp.jailCanMove.islandId+"Dat"));
			pchar.quest.GivePrisonFree_Death.win_condition.l1 = "NPC_Death";
			pchar.quest.GivePrisonFree_Death.win_condition.l1.character = npchar.id;
			pchar.quest.GivePrisonFree_Death.win_condition = "GivePrisonFree_Death";
			Pchar.quest.GivePrisonFree.win_condition.l1 = "location";
			Pchar.quest.GivePrisonFree.win_condition.l1.location = pchar.questTemp.jailCanMove.placeId;
			Pchar.quest.GivePrisonFree.win_condition = "GivePrisonFree";			
			DeleteAttribute(npchar, "LifeDay");
			GiveItem2Character(npchar, "unarmed");
			EquipCharacterbyItem(npchar, "unarmed");
			GetCharacterPos(npchar, &locx, &locy, &locz);	
			ChangeCharacterAddressGroup(npchar, npchar.location, "reload", LAi_FindNearestFreeLocator("reload", locx, locy, locz));
			LAi_SetActorType(npchar);
			LAi_group_Register("DeliveQuest_Prison");
			LAi_group_SetRelation("DeliveQuest_Prison", LAI_GROUP_PLAYER, LAI_GROUP_FRIEND);
			//LAi_group_SetAlarmReaction(LAI_GROUP_PLAYER, "DeliveQuest_Prison", LAI_GROUP_ENEMY, LAI_GROUP_FRIEND);
			LAi_group_MoveCharacter(npchar, "DeliveQuest_Prison");
			LAi_ActorFollowEverywhere(npchar, "", -1);
			DialogExit();
		break;

        case "ToPrisonHead_notFree":
			switch (pchar.questTemp.jailCanMove.ownerPrison)
			{
				case "0": sTemp = "murder"; break;
				case "1": sTemp = "piracy"; break;
				case "2": sTemp = "brigandry"; break;
				case "3": sTemp = "thievery"; break;
			}
            dialog.text = "Well, what do you say, "+ GetSexPhrase("buddy","lass") +"?";
			link.l1 = "I couldn't arrange your release. You are accused of " + sTemp + ", so you cannot be bailed out.";
			link.l1.go = "ToPrisonHead_notFree_1";
			DeleteAttribute(pchar, "questTemp.jailCanMove.ownerPrison");
		break;
		
        case "ToPrisonHead_notFree_1":
            dialog.text = "But I was slandered! Oh devil! And what will I do now? I'll rot there alive!";
			link.l1 = "I am sorry, buddy, but there is nothing I can do for you.";
			link.l1.go = "ToPrisonHead_notFree_2";
			link.l2 = "There is only one chance left - to free you with force. I will break your lock now to get you out, and we will break through. Are you ready?";
			link.l2.go = "Prisoner_agree_1";
			pchar.quest.GivePrisonFree_Over.over = "yes";
		break;
		
        case "ToPrisonHead_notFree_2":
            dialog.text = RandPhraseSimple("Curse you!", "Damn you ripped, bitch...");
			link.l1 = "And all the best to you, too. Farewell...";
			link.l1.go = "NoMoreTalkExit";
			AddQuestRecord("GivePrisonFree", "7");
            AddQuestUserData("GivePrisonFree", "sName", pchar.questTemp.jailCanMove.Name);
			DeleteAttribute(pchar, "questTemp.jailCanMove.islandId");	
			DeleteAttribute(pchar, "questTemp.jailCanMove.placeId");
			DeleteAttribute(pchar, "questTemp.jailCanMove.prisonerId");
			DeleteAttribute(pchar, "questTemp.jailCanMove.IsTrue");
			DeleteAttribute(pchar, "questTemp.jailCanMove.Sum");
			DeleteAttribute(pchar, "questTemp.jailCanMove.Name");
		break;

        case "ToPrisonHead_expansive":
			dialog.text = "So, any good news, "+ GetSexPhrase("buddy","lass") +"?";
			link.l1 = "The bail for your release is too high, I don't have such money. I have to stop helping you.";
			link.l1.go = "ToPrisonHead_notFree_2";
			pchar.quest.GivePrisonFree_Over.over = "yes";
		break;
		//==> в месте, где клад припрятан
        case "PrisonerInPlace":
			switch (sti(pchar.questTemp.jailCanMove.IsTrue))
			{
				case 0:
					dialog.text = "Listen, I've checked everything, but found no treasure. A pity it turned out this way. Someone must have dug it out before us.";
					link.l1 = "And how can that be?!";
					link.l1.go = "PrisonerInPlace_1";
				break;
				case 1:
					dialog.text = "I have found it! The treasure is still where I had left it.";
					link.l1 = "Excellent. Well, let's split, then?";
					link.l1.go = "Node_1";
				break;
				case 2:
					dialog.text = "Well, here it is, my stash. Nothing much, but this is everything I have. As we agreed, a half is yours.";
					link.l1 = "Yeah, the treasure is modest, indeed. Well, still better than nothing.";
					link.l1.go = "Node_2";
				break;
				case 3:
					dialog.text = "Captain, I am sorry, but... There is no treasure.";
					link.l1 = "What?! You've tricked me, you scoundrel! I got you out to that island - and what for? You will not get away with this!";
					link.l1.go = "Node_3";
				break;
				case 4:
					dialog.text = "Goddammit... How could that be? It cannot be!";
					link.l1 = "What's up, buddy? Where is the treasure? Don't tell me that there is none!";
					link.l1.go = "Node_4";
				break;
			}
		break;
			
		case "Node_1":
			dialog.text = "Of course, as was agreed. Half of the treasure is yours.";
			link.l1 = "Holy Lord, now there's surely a lot of precious stuff!";
			link.l1.go = "PrisonerInPlace_3";
			Log_Info("You have received your share of the treasure");
			PlaySound("interface\important_item.wav");
			TakeNItems(pchar, "icollection", 1+drand(1));
			TakeNItems(pchar, "chest", 4+drand(4));
			TakeNItems(pchar, "jewelry1", 70+rand(15));
			TakeNItems(pchar, "jewelry2", 50+rand(15));
			TakeNItems(pchar, "jewelry3", 60+rand(15));
			TakeNItems(pchar, "jewelry4", 40+rand(10));
			TakeNItems(pchar, "jewelry5", 10+rand(10));
			TakeNItems(pchar, "jewelry46", 60+rand(20));
			TakeNItems(pchar, "jewelry47", 40+rand(15));
			TakeNItems(pchar, "jewelry40", 60+rand(20));
			AddQuestRecord("GivePrisonFree", "3_1");
			AddQuestUserData("GivePrisonFree", "sName", pchar.questTemp.jailCanMove.Name);
			CloseQuestHeader("GivePrisonFree");
			DeleteAttribute(pchar, "questTemp.jailCanMove.Item1");
			DeleteAttribute(pchar, "questTemp.jailCanMove.Item2");
		break;
			
		case "Node_2":
			dialog.text = "Captain, there's also that Indian item among other things. You can have it in addition to your share.";
			link.l1 = "Well, at least something valuable for your release! Give it to me.";
			link.l1.go = "PrisonerInPlace_3";
			Log_Info("You have received your share of the treasure");
			PlaySound("interface\important_item.wav");
			sTemp = pchar.questTemp.jailCanMove.Item1;
			TakeNItems(pchar, sTemp, 1);
			TakeNItems(pchar, "jewelry5", 40+rand(10));
			TakeNItems(pchar, "jewelry6", 20+rand(20));
			TakeNItems(pchar, "jewelry17", 80+rand(20));
			TakeNItems(pchar, "jewelry13", 10+rand(10));
			TakeNItems(pchar, "jewelry10", 20+rand(20));
			TakeNItems(pchar, "jewelry12", 50+rand(20));
			TakeNItems(pchar, "jewelry11", rand(2)+1);
			AddQuestRecord("GivePrisonFree", "3_2");
			AddQuestUserData("GivePrisonFree", "sName", pchar.questTemp.jailCanMove.Name);
			CloseQuestHeader("GivePrisonFree");
			DeleteAttribute(pchar, "questTemp.jailCanMove.Item1");
			DeleteAttribute(pchar, "questTemp.jailCanMove.Item2");
		break;
			
		case "Node_3":
			dialog.text = "Wait, Captain, don't get excited, let me say. I am also a sailor, just like you. I was thrown in jail by mistake, I swear. You were my only chance to escape, and I had to lie to you about the treasure\nNo treasure, but I hid there one good thing. Take it, and let me go in peace. Perhaps, in a battle one day, it will help you to survive.";
			link.l1 = "Alright, I didn't expect much from you anyway. Thank the God that I am not bearing grudges.";
			link.l1.go = "PrisonerInPlace_3";
			Log_Info("You have received equipment");
			PlaySound("interface\important_item.wav");
			sTemp = pchar.questTemp.jailCanMove.Item2;
			TakeNItems(pchar, sTemp, 1);
			AddQuestRecord("GivePrisonFree", "3_3");
			AddQuestUserData("GivePrisonFree", "sName", pchar.questTemp.jailCanMove.Name);
			CloseQuestHeader("GivePrisonFree");
			DeleteAttribute(pchar, "questTemp.jailCanMove.Item1");
			DeleteAttribute(pchar, "questTemp.jailCanMove.Item2");
		break;
			
		case "Node_4":
			dialog.text = "No!!! It's not there! Damned scrap... Captain, I was absolutely sure I'd find it here! But, apparently, I was mistaken! What on that scrap of paper is really unclear...";
			link.l1 = "Oh well... You're in some serious trouble, buddy. But I'd still like to listen to your explanation.";
			link.l1.go = "Node_4_1";
		break;
			
		case "Node_4_1":
			dialog.text = "I had a scrap of the map. That was a real map, I swear! But it's very difficult to tell, what island was shown on it... I thought it was here... But, as you see now, I was wrong.";
			link.l1 = "What scrap of paper? Give it to me right now!";
			link.l1.go = "Node_4_2";
		break;
			
		case "Node_4_2":
			if (CheckCharacterItem(pchar, "map_part1"))
			{
				GiveItem2Character(pchar, "map_part2");
			}
			else
			{
				GiveItem2Character(pchar, "map_part1");
			}
			dialog.text = "Of course, take it. Captain, release me... please? I really thought that the treasure was there. Perhaps, you'll figure out, where it is, and take it for yourself. I beg you.";
			link.l1 = "I see... Indeed, it's hard to figure anything out by that scrap. A second half of the map is needed. Alright, get lost. I can see now it was not your fault.";
			link.l1.go = "PrisonerInPlace_4";
		break;
			
		case "PrisonerInPlace_1":
			dialog.text = "Very simple, "+ GetSexPhrase("buddy","lass") +". Everything in life happens\nWell, you're here, if you want, stay, look for more. Well, I have to go!\nFarewell, "+ GetSexPhrase("my friend","lass") +", thank you for saving my life. I will always remember you!";
			link.l1 = "Scoundrel! You think I'll let you get a way with that?! Hey! Hold on, coward!";
			link.l1.go = "PrisonerInPlace_2";
			AddQuestRecord("GivePrisonFree", "4");
			AddQuestUserData("GivePrisonFree", "sName", pchar.questTemp.jailCanMove.Name);
			CloseQuestHeader("GivePrisonFree");
			DeleteAttribute(pchar, "questTemp.jailCanMove.Item1");
			DeleteAttribute(pchar, "questTemp.jailCanMove.Item2");
		break;
			
        case "PrisonerInPlace_2":
			LAi_group_Delete("EnemyFight");
			DeleteAttribute(pchar, "questTemp.jailCanMove.islandId");	
			DeleteAttribute(pchar, "questTemp.jailCanMove.placeId");
			DeleteAttribute(pchar, "questTemp.jailCanMove.prisonerId");
			DeleteAttribute(pchar, "questTemp.jailCanMove.IsTrue");
			DeleteAttribute(pchar, "questTemp.jailCanMove.Sum");
			DeleteAttribute(pchar, "questTemp.jailCanMove.Name");
			chrDisableReloadToLocation = false;
			LAi_LocationDisableMonstersGen(pchar.location, false);
			npchar.lifeDay = 0;
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_SetActorType(npchar);
            LAi_ActorRunToLocation(NPChar, "reload", "reload1_back", "none", "", "", "", -1);
			DialogExit();

            Pchar.quest.DeletePrisonGroup.win_condition.l1 = "ExitFromLocation";
            Pchar.quest.DeletePrisonGroup.win_condition.l1.location = pchar.location;
            Pchar.quest.DeletePrisonGroup.win_condition = "DeletePrisonGroup";
		break;
		
        case "PrisonerInPlace_3":
			dialog.text = "Here you go. Thank you!";
			link.l1 = "Farewell...";
			link.l1.go = "PrisonerInPlace_2";
		break;
		
        case "PrisonerInPlace_4":
			dialog.text = "Thank you, captain! I will be praying for you till the rest of my days!";
			link.l1 = "Oh, shut up! Go in peace...";
			link.l1.go = "PrisonerInPlace_2";
			AddQuestRecord("GivePrisonFree", "3_4");
            AddQuestUserData("GivePrisonFree", "sName", pchar.questTemp.jailCanMove.Name);
			AddQuestUserData("GivePrisonFree", "sSex", GetSexPhrase("","а"));
			CloseQuestHeader("GivePrisonFree");
			DeleteAttribute(pchar, "questTemp.jailCanMove.Item1");
			DeleteAttribute(pchar, "questTemp.jailCanMove.Item2");
		break;
        
		// -------------------- освобождение заключенного --------------------
		// ------------------------ передать маляву --------------------------
        case "Deliver_1":
			dialog.text = "I am called " + GetFullName(npchar) + ". I have a request to you, he-he...";
			link.l1 = "What's up?";
			link.l1.go = "Deliver_2";
		break;
        case "Deliver_2":
			dialog.text = "I need a missive to be sent out of prison. Will you do it?";
			link.l1 = "And what's in it for me?";
			link.l1.go = "Deliver_3";
		break;
        case "Deliver_3":
			dialog.text = "The pals will not disappoint you, promise... So? Are you in?";
			link.l1 = "No, I am not interested.";
			link.l1.go = "Prisoner_5";
			link.l2 = "Well, if it doesn't require too much effort from me, I can do it.";
			link.l2.go = "Deliver_agree";
		break;
        case "Deliver_agree":
			dialog.text = "Fine. Now listen to me carefully. Two pals are waiting for my missive in a house, so that they won't get seized during a raid. But I have no clue, which house exactly it is. You'll need to search.";
			link.l1 = "What do you mean - search?";
			link.l1.go = "Deliver_4";
		break;
        case "Deliver_4":
			dialog.text = "Search as in search. You'll run around the town, peer into the houses. When you get to the right place, they will not let you out without a talk. But keep in mind that I would stay there for two more days at most. So don't delay.";
			link.l1 = "I see. Well, hand your missive, then.";
			link.l1.go = "Deliver_5";
		break;
        case "Deliver_5":
			pchar.questTemp.jailCanMove.Deliver.locationId = GetBanderLocation(npchar); //Id коммона
			if (pchar.questTemp.jailCanMove.Deliver.locationId == "none")
			{
				dialog.text = "Hmm, you know, I just don't like you. I crossed my mind. Come along, don't stand there!";
				link.l1 = "Look at you! Well, as you wish...";
				link.l1.go = "NoMoreTalkExit";
				DeleteAttribute(pchar, "questTemp.jailCanMove.Deliver");
			}
			else
			{
				dialog.text = "Here. Thank you, "+ GetSexPhrase("buddy","lass") +"!";
				link.l1 = "Not at all.";
				link.l1.go = "NoMoreTalkExit";
				GiveItem2Character(Pchar, "Malyava");
				pchar.questTemp.jailCanMove.Deliver.Id = npchar.id; //Id зэка
				pchar.questTemp.jailCanMove.Deliver.name = GetFullName(npchar); //имя зэка
				pchar.questTemp.jailCanMove.Deliver.City = npchar.city; //город (Id колонии)
				pchar.questTemp.jailCanMove.Deliver.good = rand(3); //опрокинут или нет
				pchar.questTemp.jailCanMove.Deliver.price = rand(6)*500+500; //цена услуги
				pchar.quest.DeliverToBander.win_condition.l1 = "location";
				pchar.quest.DeliverToBander.win_condition.l1.location = pchar.questTemp.jailCanMove.Deliver.locationId;
				pchar.quest.DeliverToBander.win_condition = "DeliverToBander";
				pchar.quest.DeliverToBander.again = true; 
				SetTimerCondition("DeliverToBander_over", 0, 0, 2, false);
				ReOpenQuestHeader("GivePrisonFree");
				AddQuestRecord("GivePrisonFree", "8");
				AddQuestUserData("GivePrisonFree", "sSex", GetSexPhrase("",""));
				AddQuestUserData("GivePrisonFree", "sCity", XI_ConvertString("Colony"+npchar.city+"Gen"));
				AddQuestUserData("GivePrisonFree", "sName", pchar.questTemp.jailCanMove.Deliver.name);
			}
		break;
		
		// Warship, 16.05.11. Генер "Justice for sale".
		case "JusticeOnSale_1":
			dialog.text = "Yes, he was arrested on a charge of smuggling. But why do you care about that gallows-bird, " + GetAddress_Form(NPChar) + "?";
			link.l1 = "His gang is planning to arrange his escape and continue their dirty deeds.";
			link.l1.go = "JusticeOnSale_2";
			link.l2 = "I've heard that he was not guilty.";
			link.l2.go = "JusticeOnSale_3";
			
			DeleteAttribute(PChar, "GenQuest.JusticeOnSale.PrisonWait");
		break;
		
		case "JusticeOnSale_2":
			dialog.text = "You must notify the governor, " + GetAddress_Form(NPChar) + ", these scoundrels must be all caught!";
			link.l1 = "I'll do just that.";
			link.l1.go = "exit";
			NextDiag.TempNode = "First_officer";
		break;
		
		case "JusticeOnSale_3":
			dialog.text = "Listen, " + GetFullName(PChar) + ", that type was seized while attempting to sell forbidden goods, right in the town! How can you claim that he is not guilty?";
			link.l1 = "I heard that the accusation was unfounded and you have no evidence, isn't that correct? You just can't detain a man who was wronged.";
			link.l1.go = "JusticeOnSale_4";
		break;
		
		case "JusticeOnSale_4":
			dialog.text = "We have neither witnesses nor the goods, but that doesn't change anything, captain " + GetFullName(PChar) + "! That person is definitely guilty - and perhaps not only of illegal trade. Either way - why would you care about the prisoner?";
			link.l1 = "Perhaps, my word can be the bail for that unfortunate prisoner?";
			link.l1.go = "JusticeOnSale_5_WithoutMoney";
			
			if(sti(PChar.money) >= 5000)
			{
				link.l2 = "Perhaps, these 5000 pesos can be the bail for that unfortunate prisoner?";
				link.l2.go = "JusticeOnSale_5";
			}
		break;
		
		case "JusticeOnSale_5_WithoutMoney":
			if(GetCharacterSkill(PChar, SKILL_LEADERSHIP) > dRand(100) || sti(PChar.money) < 5000)
			{
				dialog.text = "Alright, " + GetAddress_Form(NPChar) + ", take that rascal and leave, before I change my mind.";
				link.l1 = "It's great to see the triumph of justice, don't you think?";
				link.l1.go = "JusticeOnSale_6";
			}
			else
			{
				dialog.text = "No, " + GetAddress_Form(NPChar) + ", that won't do.";
				link.l1 = "Then, perhaps, these 5000 pesos can be are the more weighty argument?";
				link.l1.go = "JusticeOnSale_5";
			}
		break;
		
		case "JusticeOnSale_5":
			dialog.text = "Alright, " + GetAddress_Form(NPChar) + ", take that rascal and leave, before I change my mind.";
			link.l1 = "It's great to see the triumph of justice, don't you think?";
			link.l1.go = "JusticeOnSale_6";
			AddMoneyToCharacter(PChar, -5000);
			PChar.GenQuest.JusticeOnSale.PrisonMoney = true;
		break;
		
		case "JusticeOnSale_6":
			DialogExit();
			sld = GetCharacter(NPC_GenerateCharacter("JusticeOnSale_Smuggler", "mercen_"+(rand(9)+1), "man", "man", sti(PChar.rank)+5, PIRATE, -1, true, "marginal"));
			SetFantomParamFromRank(sld, sti(PChar.rank)+5, true);
			sld.name = PChar.GenQuest.JusticeOnSale.SmugglerName;
			sld.lastName = "";
			sld.dialog.filename = "GenQuests_Dialog.c";
			sld.dialog.currentnode = "First time";
			sld.greeting = "Enc_Raiders"; 
			AddPassenger(PChar, sld, false);
			SetCharacterRemovable(sld, false);
			PChar.GenQuest.JusticeOnSale.SmugglerModel = sld.model;
			DeleteAttribute(PChar, "GenQuest.JusticeOnSale.MayorWait");
			sld = &Locations[FindLocation(PChar.GenQuest.JusticeOnSale.ShoreId)];
			sld.DisableEncounters = true;
			PChar.Quest.JusticeOnSale_ShoreEnterWithSmuggler.win_condition.l1  = "location";
			PChar.Quest.JusticeOnSale_ShoreEnterWithSmuggler.win_condition.l1.location = PChar.GenQuest.JusticeOnSale.ShoreId;
			PChar.Quest.JusticeOnSale_ShoreEnterWithSmuggler.function = "JusticeOnSale_ShoreEnterWithSmuggler";
			Log_Info("Smuggler's captain on a board");
			PlaySound("interface\notebook.wav");
			LAi_Fade("", "");
			WaitDate("",0,0,0,2,5); // 280313
		break;
	}
}

void GetChestPlaceName()
{
	string islandId;
	int iTemp = rand(3);
	switch (iTemp)
	{
		case 0: 
			pchar.questTemp.jailCanMove.islandId = "Bermudes";
			pchar.questTemp.jailCanMove.placeId = "Bermudes_Cavern";
		break;
		case 1: 
			pchar.questTemp.jailCanMove.islandId = "Caiman";
			pchar.questTemp.jailCanMove.placeId = "Caiman_Grot";
		break;
		case 2: 
			pchar.questTemp.jailCanMove.islandId = "Dominica";
			pchar.questTemp.jailCanMove.placeId = "Dominica_Grot";
		break;
		case 3: 
			pchar.questTemp.jailCanMove.islandId = "Terks";
			pchar.questTemp.jailCanMove.placeId = "Terks_Grot";
		break;
	}
}

string GetBanderLocation(ref npchar)
{
    aref	arCommon, arRld, arRld2;
    int	i, n, Qty, Qty2;
	string LocId; 
	string	storeArray [50];
	int howStore = 0;
    makearef(arRld, Locations[FindLocation(npchar.city + "_town")].reload);
	Qty = GetAttributesNum(arRld);
    if (CheckAttribute(pchar, "GenQuest.SeekSpy.Location")) //если взят квест мэра по поиску шпиона
	{
		for (i=0; i<Qty; i++)
		{
    		arCommon = GetAttributeN(arRld, i);
			LocId = arCommon.go;
    		if (findsubstr(LocId, "Common" , 0) != -1 && LocId != pchar.GenQuest.SeekSpy.Location)
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
					if (findsubstr(LocId, "Common" , 0) != -1 && LocId != pchar.GenQuest.SeekSpy.Location)
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
					if (findsubstr(LocId, "Common" , 0) != -1)
    				{
						storeArray[howStore] = LocId;
						howStore++; 
					}
				}
			}	
		}
	}
	if (howStore == 0) return "none";
	LocId = storeArray[rand(howStore-1)];
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

string GenQuestPrison_GenerateArtefact() // артефакты
{
	string itemID;
	switch(rand(7))
	{
		case 0:
			itemID = "indian_5";
		break;
		case 1:
			itemID = "indian_7"; 
		break;
		case 2:
			itemID = "indian_8"; 
		break;
		case 3:
			itemID = "indian_9"; 
		break;
		case 4:
			itemID = "indian_10"; 
		break;
		case 5:
			itemID = "indian_11"; 
		break;
		case 6:
			itemID = "indian_3"; 
		break;
		case 7:
			itemID = "indian_6"; 
		break;
	}
	return itemID;
}

string GenQuestPrison_GenerateBlade() // клинки и другое
{
	string itemID;
	switch(rand(8))
	{
		case 0:
			itemID = GetGeneratedItem("blade_16");
		break;
		case 1:
			itemID = GetGeneratedItem("blade_15"); 
		break;
		case 2:
			itemID = GetGeneratedItem("blade_13"); 
		break;
		case 3:
			itemID = "cirass2"; 
		break;
		case 4:
			itemID = GetGeneratedItem("blade_10"); 
		break;
		case 5:
			itemID = "spyglass3"; 
		break;
		case 6:
			itemID = "cirass6"; 
		break;
		case 7:
			itemID = "cirass7"; 
		break;
		case 8:
			itemID = "cirass1"; 
		break;	
		
	}
	return itemID;
}