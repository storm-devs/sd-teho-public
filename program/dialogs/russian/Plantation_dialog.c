// диалоги обитателей плантаций
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int iTemp, i, n;
	string sTemp;
	bool bOk;
	
	DeleteAttribute(&Dialog,"Links");
	
	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	switch(Dialog.CurrentNode)
	{
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
        case "First time":
			dialog.text = "Do you need anything?";
			link.l1 = "No, I don't.";
			link.l1.go = "exit";
		break;
		
		case "fight":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_group_Attack(NPChar, Pchar);
			SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		// рабы
		case "plantation_slave":
			dialog.text = RandPhraseSimple(RandPhraseSimple("I am so tired, already falling down...", "Can't keep living like that!"), RandPhraseSimple("This work is killing me.", "Guards want us all dead!"));				
			link.l1 = RandPhraseSimple("What a pity.", "I am sorry.");
			link.l1.go = "exit";				
		break;
		
		// рабы-пираты по пиратской линейке
		case "pirate_slave":
			dialog.text = RandPhraseSimple(RandPhraseSimple("Listen, go away!", "Get lost!"), RandPhraseSimple("What do you want?!", "Get the hell out of here!"));				
			link.l1 = RandPhraseSimple("Hm...", "Well...");
			link.l1.go = "exit";				
		break;
		
		// охрана - солдаты
		case "plantation_soldier":
            dialog.text = RandPhraseSimple(RandPhraseSimple("Go bother the head of plantation", "Don't distract slaves, pal."), RandPhraseSimple("My job is to motivate these lazy bastards.", "Damn, too hot today. Actually, as always..."));
			link.l1 = RandPhraseSimple("I see...", "Understood...");
			link.l1.go = "exit";
		break;
		
		// охрана - протектор
		case "plantation_protector":
            if (GetNationRelation2MainCharacter(sti(NPChar.nation)) == RELATION_ENEMY && sti(NPChar.nation) != PIRATE)
			{
				if (sti(pchar.nation) == PIRATE)
				{
					PlaySound("VOICE\Russian\soldier_arest_1.wav");
    				dialog.text = RandPhraseSimple("Pirate?! Seize him!", "He is a pirate! Attack!");
					link.l1 = RandPhraseSimple("Pirate. So what?", "Heh, go ahead and try.");
					link.l1.go = "fight"; 
					break;
				}
				PlaySound("VOICE\Russian\soldier_arest_2.wav");
				dialog.text = RandPhraseSimple("Ho-ho, you are sailing under the flag of "+NationNameGenitive(sti(pchar.nation))+"! I think that our commandant will be glad to talk with you!", "Well-well, it's smelling of "+NationNameAblative(sti(pchar.nation))+" here! A spy?! It's time for you to talk with our commandant.");
				link.l1 = RandPhraseSimple("First, I'll send you in the Hell!", "It's time for you to talk with my blade!");
				link.l1.go = "fight"; 
			}
			else
			{
				if (GetNationRelation(sti(NPChar.nation), GetBaseHeroNation()) == RELATION_ENEMY && sti(NPChar.nation) != PIRATE)
				{
					if (sti(pchar.nation) == PIRATE)
					{
						PlaySound("VOICE\Russian\soldier_arest_1.wav");
						dialog.text = RandPhraseSimple("Pirate?! Seize him!", "He is a pirate! Attack!");
						link.l1 = RandPhraseSimple("Pirate. So what?", "Heh, go ahead and try.");
						link.l1.go = "fight"; 
						break;
					}
					PlaySound("VOICE\Russian\soldier_arest_4.wav");
					dialog.text = RandPhraseSimple("Who are you and what do you want here?", "Stop! What is your business here?");
					if (CheckNationLicence(HOLLAND))
					{
						link.l1 = "I want to see the head of this place to discuss business. I have a trading license.";
						link.l1.go = "Licence";
					}
					else
					{
						link.l1 = "I want to see the head of this place to discuss business.";
						if (GetSummonSkillFromName(pchar, SKILL_SNEAK) < (10+rand(50)+rand(50))) link.l1.go = "PegYou";
						else link.l1.go = "NotPegYou";
					}
				}
				else
				{
					PlaySound("VOICE\Russian\soldier_arest_4.wav");
					dialog.text = RandPhraseSimple("Who are you and what do you want here?", "Stop! What is your business here?");
					link.l1 = "I want to see the head of this place to discuss business.";
					link.l1.go = "NotPegYou";
				}
			}
		break;
		
		case "Licence":
			iTemp = GetDaysContinueNationLicence(HOLLAND);
			if (ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 0) <= -12)
			{
				PlaySound("VOICE\Russian\soldier_arest_2.wav");
				dialog.text = "A license? Wait a second... Ha-ha, this is funny! I know who you are. You are wanted, pal! And reward for your head is very big! Seize him!";
				link.l1 = RandPhraseSimple("Say hello to my blade", "Screw you.");
				link.l1.go = "fight";	
				break;
			}
			if (iTemp == -1)
			{
				PlaySound("VOICE\Russian\soldier_arest_1.wav");
				dialog.text = "Let's see... ha! You license is overdue. So follow me, I will bring you to the commandant...";
				link.l1 = RandPhraseSimple("Shit! Say hello to my blade, buddy.", "I don't think so...");
				link.l1.go = "fight";	
				TakeNationLicence(HOLLAND);
				break;
			}
			dialog.text = "Fine. You can come in. Behave yourself and don't bother the slaves.";
			link.l1 = "Don't worry, friend.";
			link.l1.go = "plantation_exit";
		break;
		
		case "PegYou":
			PlaySound("VOICE\Russian\soldier_arest_2.wav");
            dialog.text = "Business? Ha-ha! Well, this is funny! You smell of "+NationNameAblative(sti(GetBaseHeroNation()))+" from a thousand miles! It's time for you to meet our commandant.";
			link.l1 = "Nah, it's time for you to meet my blade.";
			link.l1.go = "fight";
		break;
		
		case "NotPegYou":
            dialog.text = "Fine. You can come in. Behave yourself and don't bother the slaves.";
			link.l1 = "Don't worry, friend.";
			link.l1.go = "plantation_exit";
		break;
		
		case "plantation_exit":
           DialogExit();
		   NextDiag.CurrentNode = "plantation_repeat";
		break;
		
		case "plantation_repeat":
            dialog.text = "Come on, move along!";
			link.l1 = "...";
			link.l1.go = "plantation_exit";
		break;
		
		// управляющий в Маракайбо // Addon 2016-1 Jason
		case "Plantator":
			if (CheckAttribute(pchar, "questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "plant_2" && GetSquadronGoods(pchar, GOOD_SLAVES) >= 50)
			{
				dialog.text = "What's your business here, senor?";
				link.l1 = TimeGreeting()+", senor. I have a business proposal to you. I have slaves to sell. "+FindRussianQtyString(sti(GetSquadronGoods(pchar, GOOD_SLAVES)))+". Interested?";
				link.l1.go = "mtraxx";
				break;
			}
            dialog.text = "What's your business here, senor?";
			link.l1 = "Just walking around, wanted to say hello.";
			link.l1.go = "plantator_x";
		break;
		
		case "plantator_x":
           DialogExit();
		   npchar.dialog.currentnode = "plantator";
		break;
		
		case "plantator_1":
			bOk = GetSquadronGoods(pchar, GOOD_COFFEE) >= 500 || GetSquadronGoods(pchar, GOOD_CINNAMON) >= 500 || GetSquadronGoods(pchar, GOOD_COPRA) >= 500;
			if (CheckAttribute(pchar, "questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "plant_6" && bOk)
			{
				dialog.text = "You again, senor. How are you?";
				link.l1 = "I have a business proposal to you. You produce sugar and cacao. I'd like to purchase your goods but not for money, I can offer my own goods in exchange. Perhaps, we could do a bargain?";
				link.l1.go = "mtraxx_5";
				break;
			}
            dialog.text = "You again, senor. How are you?";
			link.l1 = "Thanks, I am good.";
			link.l1.go = "plantator_1x";
		break;
		
		case "plantator_1x":
           DialogExit();
		   npchar.dialog.currentnode = "plantator_1";
		break;
		
		case "mtraxx":
            dialog.text = "I have to disappoint you, senor, but we don't need slaves at this moment. Captain Eduardo de Losada had already supplied us with pirates he captured in his last raid.";
			link.l1 = "Pirates here? How can you even sleep here?";
			link.l1.go = "mtraxx_1";
		break;
		
		case "mtraxx_1":
            dialog.text = "We have a good guard, so chances of riot are low. But you are right in some point: these bastards are terrible workers. I wouldn't had bought them if the governor wasn't asking me to show respect to don de Losada. Plus, he also didn't ask much for them.";
			link.l1 = "I see. I will have to sail to Los-Tekes then... Senor, may I walk around your plantation and explore it? Perhaps, I'd like to buy some of your production...";
			link.l1.go = "mtraxx_2";
		break;
		
		case "mtraxx_2":
            dialog.text = "Are you a merchant?";
			link.l1 = "In some degree, yes. I am not a professional trader but I'd never walk away from a promising deal.";
			link.l1.go = "mtraxx_3";
		break;
		
		case "mtraxx_3":
            dialog.text = "Interesting. Very well, you have my permission. Come back if you'll have any ideas.";
			link.l1 = "Thank you, senor. I believe I will.";
			link.l1.go = "mtraxx_4";
		break;
		
		case "mtraxx_4":
           DialogExit();
		   NextDiag.CurrentNode = "plantator_1";
		   pchar.questTemp.Mtraxx = "plant_3";
		   AddQuestRecord("Roger_3", "5");
		   Mtraxx_PlantSetMaxRocur();
		break;
		
		case "mtraxx_5":
            dialog.text = "Why not? What goods are you offering?";
			if (GetSquadronGoods(pchar, GOOD_COFFEE) >= 500)
			{
				link.l1 = "500 boxes of coffee.";
				link.l1.go = "mtraxx_coffee";
			}
			if (GetSquadronGoods(pchar, GOOD_CINNAMON) >= 500)
			{
				link.l2 = "500 boxes of vanilla.";
				link.l2.go = "mtraxx_cinnamon";
			}
			if (GetSquadronGoods(pchar, GOOD_COPRA) >= 500)
			{
				link.l3 = "500 boxes of copra.";
				link.l3.go = "mtraxx_copra";
			}
		break;
		
		case "mtraxx_coffee":
			i = drand(3)+1;
			n = 5 - i;
			pchar.questTemp.Mtraxx.PlantGood.Cargo = 11;
			pchar.questTemp.Mtraxx.PlantGood.Sugar = i * 100;
			pchar.questTemp.Mtraxx.PlantGood.Cocoa = n * 100;
            dialog.text = "Five hundred boxes of coffee? Well-well... Let's see... (counting) I am ready to exchange your coffee for "+sti(pchar.questTemp.Mtraxx.PlantGood.Sugar)+" sacks of sugar and "+sti(pchar.questTemp.Mtraxx.PlantGood.Cocoa)+"  boxes of cacao. Deal?";
			link.l1 = "M-m-m... I hoped for better terms. Well, who cares. Deal!";
			link.l1.go = "mtraxx_6";
		break;
		
		case "mtraxx_cinnamon":
			i = drand(3)+1;
			n = 5 - i;
			pchar.questTemp.Mtraxx.PlantGood.Cargo = 19;
			pchar.questTemp.Mtraxx.PlantGood.Sugar = i * 106;
			pchar.questTemp.Mtraxx.PlantGood.Cocoa = n * 106;
            dialog.text = "Five hundred boxes of vanilla? Well-well... Let's see... (counting) I am ready to exchange your vanilla for "+sti(pchar.questTemp.Mtraxx.PlantGood.Sugar)+" sacks of sugar and "+sti(pchar.questTemp.Mtraxx.PlantGood.Cocoa)+"  boxes of cacao. Deal?";
			link.l1 = "M-m-m... I hoped for better terms. Well, who cares. Deal!";
			link.l1.go = "mtraxx_6";
		break;
		
		case "mtraxx_copra":
			i = drand(3)+1;
			n = 5 - i;
			pchar.questTemp.Mtraxx.PlantGood.Cargo = 20;
			pchar.questTemp.Mtraxx.PlantGood.Sugar = i * 100;
			pchar.questTemp.Mtraxx.PlantGood.Cocoa = n * 100;
            dialog.text = "Five hundred boxes of copra? Well-well... Let's see...(counting) I am ready to exchange your copra for "+sti(pchar.questTemp.Mtraxx.PlantGood.Sugar)+" sacks of sugar and "+sti(pchar.questTemp.Mtraxx.PlantGood.Cocoa)+"  boxes of cacao. Deal?";
			link.l1 = "M-m-m... I hoped for better terms... Well, who cares. Deal!";
			link.l1.go = "mtraxx_6";
		break;
		
		case "mtraxx_6":
            dialog.text = "Splendid! It's a profitable deal for both of us! When will we execute the exchange?";
			link.l1 = "I should prepare the goods first. You too I believe. Let's begin tomorrow at four o'clock in the evening. My men will deliver the boxes before the sunset.";
			link.l1.go = "mtraxx_7";
		break;
		
		
		case "mtraxx_7":
            dialog.text = "Deal. See you tomorrow, senor!";
			link.l1 = "See you...";
			link.l1.go = "mtraxx_8";
		break;
		
		case "mtraxx_8":
            DialogExit();
			NextDiag.CurrentNode = "plantator_1";
			AddQuestRecord("Roger_3", "10");
			pchar.questTemp.Mtraxx = "plant_7";
			pchar.GenQuest.CannotWait = true;//запрет ожидания
			pchar.quest.mtraxx_plant_goods.win_condition.l1 = "ExitFromLocation";
			pchar.quest.mtraxx_plant_goods.win_condition.l1.location = pchar.location;
			pchar.quest.mtraxx_plant_goods.function = "Mtraxx_PlantFindRocurDay";
		break;
		
		case "mtraxx_9":
            dialog.text = "This is it, senor. If you'll ever need sugar or cacao, please come and see me. Anytime!";
			link.l1 = "If this bargain will prove to be profitable - we'll see each other again. I should go now, senor.";
			link.l1.go = "mtraxx_10";
		break;
		
		
		case "mtraxx_10":
            dialog.text = "Farewell, senor!";
			link.l1 = "";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_PlantAfterTrading");
		break;
	}
} 
