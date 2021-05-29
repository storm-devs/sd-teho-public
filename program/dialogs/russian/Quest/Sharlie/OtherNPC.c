// диалог прочих и малозначимых НПС
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	bool bOk;
	int i, n, iTemp;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "Is there something you needed?";
			link.l1 = "No, nothing.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		// --> матрос на корабле, прибытие в Сен-Пьер
		case "Startsailor":
			dialog.text = "Erm, first of all, as soon as I'll get down to the bay I'm getting drunk!... Wake up, monsieur... whatever your name is... We have arrived!";
			link.l1 = "A-ah! What, already? God damn heat!...";
			link.l1.go = "Startsailor_1";			
		break;
		
		case "Startsailor_1":
			dialog.text = "Get used to it, monsieur. This is the only weather we have here... At least it could be even worse.";
			link.l1 = "How could it get worse!? I'm wearing one linen shirt and I've got sweat streaming down my side like hail!";
			link.l1.go = "Startsailor_2";			
		break;
		
		case "Startsailor_2":
			dialog.text = "Don't forget your things... Hurry up, monsieur. The longboat isn't going to wait. You don't want to swim to the island, do you?";
			link.l1 = "Yes, I don't... Where's my sword? Ah, here it is...";
			link.l1.go = "Startsailor_3";			
		break;
		
		case "Startsailor_3":
			dialog.text = "Yes, this isn't Europe... Be careful, monsieur. Most people don't welcome those who ask too many questions here. These, as you know, are troubled times. They say that the island was sold to some religion fanatics. I still haven't noticed any change in the usual way of life of the Martinique inhabitants. But since I've been gone for a while, a lot could have changed.";
			link.l1 = "Religion fanatics? What a bullshit!";
			link.l1.go = "Startsailor_4";			
		break;
		
		case "Startsailor_4":
			dialog.text = "Whether it's bullshit or not, rumours are going around. There's already enough adversity as it is. Cannibals in the jungle, fever, pirates, bandits in the alleyways...";
			link.l1 = "Oh, here we go again... Right now the only kind of adversity that I've come across is heat and moskitos... All right, I'm ready. Shall we go?";
			link.l1.go = "Startsailor_5";			
		break;
		
		case "Startsailor_5":
			dialog.text = "Walk up top and step onto the longboat, monsieur. Welcome to the Caribbean!";
			link.l1 = "";
			link.l1.go = "Startsailor_6";			
		break;
		
		case "Startsailor_6":
			DialogExit();
			chrDisableReloadToLocation = false;
			i = FindLocation("Fortfrance_town");
			setCharacterShipLocation(pchar, GetCityFrom_Sea(locations[i].fastreload));
		    setWDMPointXZ(GetCityFrom_Sea(locations[i].fastreload));
			DoQuestReloadToLocation("Fortfrance_town", "reload", "reload1", "Sharlie_onLand");
		break;
		// <-- матрос на корабле, прибытие в Сен-Пьер
		
		// --> арест в резиденции
		case "Sharlie_arest":
			dialog.text = "Yield your weapons right away, monsieur, and follow us!";
			link.l1 = "Well, it seems I'm up the creek...";
			link.l1.go = "Sharlie_arest_1";			
		break;
		
		case "Sharlie_arest_1":
			DialogExit();
			chrDisableReloadToLocation = false;
			DoFunctionReloadToLocation("FortFrance_prison", "goto", "goto9", "");
			WaitDate("", 0, 0, 2, 0, 10); //крутим время
			RecalculateJumpTable();
			RemoveAllCharacterItems(PChar, true);
			sld = characterFromId("Puancie");
			sld.dialog.currentnode = "Puancie_Jail"; 
			LAi_SetActorTypeNoGroup(sld);
			ChangeCharacterAddressGroup(sld, "FortFrance_prison", "goto", "goto13");
			DoQuestFunctionDelay("Puancie_InJail", 10.0);
		break;
		// арест в резиденции
		
		// --> офицер базы
		case "Maltie_officer":
			ref location = &Locations[FindLocation(pchar.location)];
			if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "begin")
			{
				dialog.text = "I'm glad to see you, Monsieur de Maure. What's the occasion?";
				link.l1 = TimeGreeting()+", officer. I would like to speak with my brother, Michel de Monper. Off the record. I would like to find out a little bit more about his service here.";
				link.l1.go = "spanish";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "think")
			{
				dialog.text = "Well, how did the interrogation go? Did you find out a lot of new information?";
				link.l1 = "So much that I'm taking this Spaniard with me back on the ship. This is an important witness and he must be delivered to St. Christopher for further investigation.";
				link.l1.go = "spanish_10";
				break;
			}
			if (!CheckAttribute(location, "first_meeting"))
			{
				dialog.text = "Monsieur, how did you get here? What is your business here?";
				link.l1 = "I have come to see my brother, Michel de Monper.";
				link.l1.go = "Maltie_officer_1";
				location.first_meeting = true;
			}
			else
			{
				dialog.text = "Monsieur, I gently remind you that you are located inside a military object. So behave accordingly.";
				link.l1 = "Yes, officer. Of course.";
				link.l1.go = "exit";
				NextDiag.TempNode = "Maltie_officer";
			}
		break;
		
		case "Maltie_officer_1":
			dialog.text = "Michel de Monper is under watch in one of the cells and held under the personal order of chevalier Philippe de Poincy. Descend down to the lower tier. You will find the casemates there. I think you'll find your way.";
			link.l1 = "Thank you!";
			link.l1.go = "exit";
			NextDiag.TempNode = "Maltie_officer";
		break;
		// офицер базы
		
		// --> солдаты базы
		case "Maltie_soldier":
			dialog.text = "Hello, monsieur. Can I help you with anything?";
			link.l1 = "Thank you, soldier. Alas, you are not able to render me any assistance...";
			link.l1.go = "exit";
			NextDiag.TempNode = "Maltie_soldier";
		break;
		// --> солдаты базы
		
		// --> мальтиец-проводник
		case "Sharlie_maltie":
			dialog.text = "I'm here, monsieur. So you were searching for Michel de Monper? And you are his brother?";
			link.l1 = "Yes, that's correct. I am his brother Charles. I need to see him right away. He's got into trouble, hasn't he?";
			link.l1.go = "Sharlie_maltie_1";			
		break;
		
		case "Sharlie_maltie_1":
			dialog.text = "Unfortunately, he has, monsieur. Michel is under arrest and locked in our prison. Chevalier de Poincy the general-governor of French colonies himself given and signed the orders. All of us were shocked\nYour brother is an example of manhood, firmness and courage, a pride of our Order! The worst part is that we, his friends, have to lock his cell and guard him as a criminal! We do everything to ease his state, but... prison is a prison.";
			link.l1 = "So what is he being accused of? Has he committed a crime?";
			link.l1.go = "Sharlie_maltie_1_1";			
		break;
		
		case "Sharlie_maltie_1_1":
			dialog.text = "Nonsense! A pure nonsense! They have accused Michel of peculation and stealing money of the state. Ridiculous! All of us are sure that it is just a political game. Michel had been taking part in secret operations of the Order, perhaps, he learnt more than he should've\nOr something else. But stealing money! Nobody believes that. It is just a pretence, not a reason, such a rude and stupid pretence! But enough words. Your brother is looking forward to see you, I am sure he will tell you everything himself.";
			link.l1 = "Good. Where is the prison located?";
			link.l1.go = "Sharlie_maltie_1_2";
		break;
		
		case "Sharlie_maltie_1_2":
			dialog.text = "It's located in our underground base, here in the city. Follow me. I'll show you the way.";
			link.l1 = "...";
			link.l1.go = "Sharlie_maltie_2";
		break;
		
		case "Sharlie_maltie_2":
			DialogExit();
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "FortFrance_town", "reload", "reload7_back", "Maltie_GoTown", -1);
		break;
		
		case "Sharlie_maltie_3":
			dialog.text = "Here we are. This is our base - a military base of the Order of Malta. The dungeons are below us. Go by the dining hall and the chapel, find stairs and descend to the lowest level. Look for a corridor with cells. You will find your brother in one of those\nGo, Charles, and please help our Michel! He is blameless, everyone here is ready swear on it.";
			link.l1 = "That's the reason I came to this shithole to help my brother. I hope I'll be able to do at least something for him.";
			link.l1.go = "Sharlie_maltie_4";
		break;
		
		case "Sharlie_maltie_4":
			DialogExit();
			chrDisableReloadToLocation = false;//открыть локацию
			npchar.lifeday = 0;
			LAi_ActorGoToLocator(npchar, "goto", "goto1", "none", -1);
		break;
		// мальтиец-проводник
		
		// --> найм матросов
		case "Sharlie_sailor":
			dialog.text = "Good health, monsieur. Is there something you need?";
			link.l1 = "Yes. I have a ship in my property, but no crew. The bartender advised me to speak with you about this, you and your lads have supposedly been dismissed from some ship and you need work...";
			link.l1.go = "Sharlie_sailor_1";
		break;
		
		case "Sharlie_sailor_1":
			dialog.text = "Yes, that's correct. Would you like to hire us into service? What kind of ship do you have?";
			link.l1 = "A regular ship, "+GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(RealShips[sti(pchar.ship.type)].basetype), "Name")))+". Why do you even care?";
			link.l1.go = "Sharlie_sailor_2";
		break;
		
		case "Sharlie_sailor_2":
			dialog.text = "Well, monsieur, nobody wants to serve on a tartan or on a longboat, but "+GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(RealShips[sti(pchar.ship.type)].basetype), "Name")))+" will do just fine. But I warn you, captain, you can hire only all of us at once. See, we are a team...";
			link.l1 = "How many people do you have?";
			link.l1.go = "Sharlie_sailor_3";
		break;
		
		case "Sharlie_sailor_3":
			dialog.text = "Forty. We're experienced sailors, no landlubbers, and we've had to take a sniff of gun powder a time or two as well. And we'll be able to handle the sails, we'll take the cannons if the need arises, and we can work a sword if it's necessary.";
			link.l1 = "Nice. How much do you want?";
			link.l1.go = "Sharlie_sailor_4";
		break;
		
		case "Sharlie_sailor_4":
			dialog.text = "An advance of 200 pesos each and then standard rates. We won't ask too much, don't worry about that.";
			if (sti(Pchar.money) >= 8000)
			{
				link.l1 = "Here is your money.";
				link.l1.go = "Sharlie_sailor_5";
			}
			link.l2 = "Unfortunately, I don't have that much money.";
			link.l2.go = "Sharlie_sailor_nomoney";
		break;
		
		case "Sharlie_sailor_5":
			if (GetSquadronGoods(pchar, GOOD_FOOD) < 20 || GetSquadronGoods(pchar, GOOD_MEDICAMENT) < 30)
			{
				dialog.text = "Do you have foodstuffs in the hold, captain? And medicine? No? Well, then first buy at least a minimum and then come back and we'll talk. Go to the store.";
				link.l1 = "Hm. You're right. Okay, I'll do that.";
				link.l1.go = "exit";
				NextDiag.TempNode = "Sharlie_sailor_again";
			}
			else
			{
				AddMoneyToCharacter(pchar, -8000);
				dialog.text = "Great, captain! I'll gather guys together right away and we'll be off to your ship immediately.";
				link.l1 = "Wonderful. Prepare the ship for departure.";
				link.l1.go = "Sharlie_sailor_6";
			}
		break;
		
		case "Sharlie_sailor_6":
			DialogExit();
			LAi_SetStayType(npchar);
			GetCharacterPos(pchar, &locx, &locy, &locz);
			ChangeCharacterAddressGroup(npchar, "Fortfrance_tavern", "goto", LAi_FindNearestFreeLocator("goto", locx, locy, locz));
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "", "", "", "", 5);
			npchar.lifeday = 0;
			SetCrewQuantityOverMax(PChar, 40);
			pchar.Ship.Crew.Morale = 50;
			pchar.Ship.Crew.Exp.Sailors = 50;
			pchar.Ship.Crew.Exp.Cannoners = 50;
			pchar.Ship.Crew.Exp.Soldiers = 50;
			AddQuestRecord("Sharlie", "7");
			pchar.questTemp.Sharlie = "skiper";
			DeleteAttribute(pchar, "GenQuest.CannotWait");//снимаем запрет, если не был снят раньше
		break;
		
		case "Sharlie_sailor_nomoney":
			dialog.text = "Well, as soon as you find enough money, come back. I think you'll be able to find me here in the tavern. At the moment there aren't any ships around. We'll just carry on drinking our money, ha ha!";
			link.l1 = "All right. I'll try to be back as soon as possible.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Sharlie_sailor_again";
		break;
		
		case "Sharlie_sailor_again":
			dialog.text = "So, captain? Are you willing to hire me and my guys? We can't wait to go back out to sea again! And our pockets are getting windy at that...";
			if (sti(Pchar.money) < 8000)
			{
				link.l1 = "Not yet, I'm still preparing.";
				link.l1.go = "exit";
				NextDiag.TempNode = "Sharlie_sailor_again";
			}
			else
			{
				link.l1 = "Yes. Take your advance. Now you are at my service.";
				link.l1.go = "Sharlie_sailor_5";
			}
		break;
		// найм матросов
		
		// наводчик на штурмана
		case "skipertalker":
			dialog.text = LinkRandPhrase("Greetings, captain! What do you need?","Hello, sir. What can I do for you?","Good afternoon. What would you like?");
			link.l1 = RandPhraseSimple("I've got a question for you.", "I need information about this colony.");
			link.l1.go = "skipertalker_1";
			link.l2 = "Just decided to say hello. Tootles!";
			link.l2.go = "exit";
			NextDiag.TempNode = "skipertalker";
		break;
		
		case "skipertalker_1":
			dialog.text = RandPhraseSimple("What questions?", "What do you need?");
			link.l1 = "Listen, "+GetAddress_FormToNPC(NPChar)+", here's the thing... I'm looking for a navigator for my ship. Perhaps, you know somebody fit for the job in your town?";
			link.l1.go = "skipertalker_2";
		break;
		
		case "skipertalker_2":
			dialog.text = "A Nav-guy? Hm... Well, I know one... There's just one problem - he's in the jail at the moment. He's been put behind bars for his debt. He's probably been in the casemate for a month already. Poor sod.";
			link.l1 = "A debtor? Hm... What's his name, can you tell me?";
			link.l1.go = "skipertalker_3";
		break;
		
		case "skipertalker_3":
			dialog.text = "Name's Folke Deluc. Ask the commandant in the prison. But I don't think they'll let him free that easy, unless, of course, you pay his debt, ha-ha-ha!";
			link.l1 = "Maybe I will. Thanks for the information, you've been a big help!";
			link.l1.go = "exit";
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeday = 0;
			pchar.questTemp.Sharlie = "jailskiper";
			AddQuestRecord("Sharlie", "8");
		break;
		
		// --> штурман
		case "Folke":
			dialog.text = "Why do I own such an honour, monsieur?";
			link.l1 = "Hello, Folke. It's simple, I've got a ship, but no navigator. And I need one. So I've bought you out of your debt hole...";
			link.l1.go = "Folke_1";
		break;
		
		case "Folke_1":
			dialog.text = "You're saying that you've dragged me out of here to take me in your crew?";
			link.l1 = "Exactly. I think you'll quickly make up for the money I've spent on you. Well... we'll see how it goes.";
			link.l1.go = "Folke_2";
		break;
		
		case "Folke_2":
			dialog.text = "My gratitude, monsieur. I've grown sick and empty of these casemates. It would do me a great pleasure to climb on top of a deck once more. Ah, the sea, the sea...";
			link.l1 = "I'm glad we've reached an understanding, Folke. Yes and one more thing: do you have any other sea skills, besides steering a ship?";
			link.l1.go = "Folke_3";
		break;
		
		case "Folke_3":
			dialog.text = "A bit of everything, captain. I used to serve as a mercenary in the Dutch Navy, I learnt there how to aim and reload cannons. So I can take place at the gun deck if you need me there. But trading or boarding is not what I am about.";
			link.l1 = "I see. Now follow me to the ship. You'll watch with an experienced eye how, what, and where. Then, I want to depart to Guadeloupe as soon as possible.";
			link.l1.go = "Folke_4";
		break;
		
		case "Folke_4":
			dialog.text = "Aye, captain! I'll wait for you in the cabin. *Use the action menu in the sea in order to access the cabin*";
			link.l1 = "...";
			link.l1.go = "Folke_5";
		break;
		
		case "Folke_5":
			DialogExit();
			chrDisableReloadToLocation = false;//открыть локацию
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешить драться
			AddQuestRecord("Sharlie", "10");
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			pchar.quest.Sharlie_skiper.win_condition.l1 = "location";
			pchar.quest.Sharlie_skiper.win_condition.l1.location = "My_Cabin_Small";
			pchar.quest.Sharlie_skiper.function = "Sharlie_SkiperTalk";
			//прерывание на засаду пиратов - принудительный квест
			pchar.quest.Sharlie_seabattle.win_condition.l1 = "location";
			pchar.quest.Sharlie_seabattle.win_condition.l1.location = "Fortfrance_town";
			pchar.quest.Sharlie_seabattle.function = "SharlieSeabattle_agent";
		break;
		
		case "Folke_6":
			pchar.GenQuest.StoreGoods.StoreIdx = Fortfrance_STORE;
			pchar.GenQuest.StoreGoods.Starting = true; // заполняем магазин 250912
			dialog.text = "Great lugger, captain! Quite a decent ship. With a ship like this you're good not only to make it to Guadeloupe, but even across the whole Caribbean sea.";
			link.l1 = "Excellent. At least I didn't throw my money away for nothing... Will you have any advice before we set sail, Folke?";
			link.l1.go = "Folke_8";
		break;
		
		case "Folke_7":
			dialog.text = " Well, well. This sloop is tellingly damaged, captain, to cross over to Guadalupe. She's capable to do more, but to arrive at Basse-Terre she'll have to be submitted for repair immediately.";
			link.l1 = "I didn't have a choice, they offered only this vessel here at the shipyard. And they took a hefty sum for her. And as you know, we don't have any time to fix her at the moment... Do you have any advice before we set sail?";
			link.l1.go = "Folke_8";
		break;
		
		bOk = (GetSquadronGoods(pchar, GOOD_BALLS) >= 80) && (GetSquadronGoods(pchar, GOOD_GRAPES) >= 80) && (GetSquadronGoods(pchar, GOOD_KNIPPELS) >= 80) && (GetSquadronGoods(pchar, GOOD_BOMBS) >= 80) && (GetSquadronGoods(pchar, GOOD_POWDER) >= 180);
		case "Folke_8":
			if (bOk)
			{
				dialog.text = "Well, you've definitely stocked up on enough ammo, captain. This arsenal will be more than enough for us. Just don't forget to restock it in due time.";
				link.l1 = "Well, that goes without saying. Any other comments?";
				link.l1.go = "Folke_10";
			}
			else
			{
				dialog.text = "I have looked in the hold, captain. We don't have enough ammo. We need to have at least one hundred cannon balls, chain shots, and bombs as well as one hundred portions of grape-shot and 200 pieces of gunpowder. Buy up the necessary arsenal, captain it's all not going to cost a lot, but it'll save our lives in case we get attacked by pirates or the Spanish.";
				link.l1 = "All right. I'll follow your advice. I'm off to the shore.";
				link.l1.go = "Folke_9";
			}
		break;
		
		case "Folke_9":
			DialogExit();
			NextDiag.CurrentNode = "Folke_goods_1";
			LAi_SetStayType(npchar);
			AddQuestRecord("Sharlie", "12");
		break;
		
		case "Folke_goods_1":
			dialog.text = "Have you finished buying up ammunition, captain?";
			if (bOk)
			{
				link.l1 = "Yes, I have. Any other comments?";
				link.l1.go = "Folke_10";
			}
			else
			{
				link.l1 = "No, I'm still in the process.";
				link.l1.go = "exit";
				NextDiag.TempNode = "Folke_goods_1";
			}
		break;
		
		bOk = (GetSquadronGoods(pchar, GOOD_WEAPON) >= 50);
		case "Folke_10":
			if (bOk)
			{
				dialog.text = "Well done, you have bought enough weapons for your crew. The lack of weapons on board leads to a higher casualty rate during a hand-to-hand fighting. God save us from it. Don't forget to constantly check the amount in cargo hold\nAlso, keep a little extra of weapons, damn rats like gnawing at handles.";
				link.l1 = "Got it. I see there's still something you want to add?";
				link.l1.go = "Folke_11";
			}
			else
			{
				dialog.text = "We don't have enough of weapon for the crew. The lack of weapons on board leads to a higher casualty rate during a hand-to-hand fighting. God save us from it. As far as I understand, you have forty souls of crewmen\nBuy weapons for the each, or even buy a little extra, fifty sets should suffice. Damn rats like gnawing at handles.";
				link.l1 = "That's what we'll do. I'll be back soon.";
				link.l1.go = "Folke_10_1";
			}
		break;
		
		case "Folke_10_1":
			DialogExit();
			NextDiag.CurrentNode = "Folke_goods_2";
			LAi_SetStayType(npchar);
			AddQuestRecord("Sharlie", "13");
		break;
		
		case "Folke_goods_2":
			dialog.text = "Have you finished buying up weapons, captain?";
			if (bOk)
			{
				link.l1 = "The weapons are in the hold. I see there's still something you want to add?";
				link.l1.go = "Folke_11";
			}
			else
			{
				link.l1 = "No, I'm still in the process.";
				link.l1.go = "exit";
				NextDiag.TempNode = "Folke_goods_2";
			}
		break;
		
		bOk = (GetSquadronGoods(pchar, GOOD_FOOD) >= 100) && (GetSquadronGoods(pchar, GOOD_RUM) >= 10);
		case "Folke_11":
			if (bOk)
			{
				dialog.text = "No, I think that's it. We have enough rations, you've also taken care of rum for the crew. That's great, since there's no better medicine for any kind of ailments as a good old cup of rum after your shift. Sailors love and respect captains who provide them daily portions of rum...";
				link.l1 = "Well, I take it that we can now confidently set sail?";
				link.l1.go = "Folke_12";
			}
			else
			{
				dialog.text = "Yes. Provisions and rum. It is really bad if you don't have enough of provisions on board. You never know how long the voyage will last - a dead calm or a strong gale can ruin any plan. People die and mutiny when provisions are gone\nRum supplies however are not that critical, but I suggest you always keeping some on board, there is no better cure for any disease than a good glass of rum after the shift. Crewmen respect and love captains who provide daily portions of rum\nSo go and buy supplies we need - at least a hundred packages of provisions and ten barrels of rum.";
				link.l1 = "I guess you're right. I'll go revisit the merchant.";
				link.l1.go = "Folke_11_1";
			}
		break;
		
		case "Folke_11_1":
			DialogExit();
			NextDiag.CurrentNode = "Folke_goods_3";
			LAi_SetStayType(npchar);
			AddQuestRecord("Sharlie", "14");
		break;
		
		case "Folke_goods_3":
			dialog.text = "Have you finished buying up on rations and rum, captain?";
			if (bOk)
			{
				link.l1 = "Yes. I take it that we can now confidently set out to sea?";
				link.l1.go = "Folke_12";
			}
			else
			{
				link.l1 = "No, I'm still in the process.";
				link.l1.go = "exit";
				NextDiag.TempNode = "Folke_goods_3";
			}
		break;
		
		case "Folke_12":
			dialog.text = "Aye, cap. You can pull up the anchor and set course due north toward Guadalupe as you wanted. There is something extra I wanted to add\nYou can keep your stuff in cabin's chests. Your things will be perfectly safe there, and the crew will move them to another vessel in case you decide to change it in the future\nAlso, hire a purser as soon as possible, even a small ship can dry your wallet, it will take a lot of time for you to master personal skills of accounting and trading.";
			link.l1 = "Let's not waste any time! Full speed ahead!";
			link.l1.go = "Folke_13";
		break;
		
		case "Folke_13":
			dialog.text = "Then I'll return back to my place on the deck. Order me to unmoor, captain! *USE F2 MENU IN ORDER TO ASSIGN OFFICERS. MAKE FOLKE YOUR NAVIGATOR BEFORE SETTING SAIL";
			link.l1 = "...";
			link.l1.go = "Folke_14";
		break;
		
		case "Folke_14":
			DialogExit();
			LAi_SetImmortal(npchar, false);
			chrDisableReloadToLocation = true;
			LAi_SetActorType(npchar);
			AddQuestRecord("Sharlie", "15");
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "OpenTheDoors", -1);
			npchar.quest.OfficerPrice = 20;
			Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(npchar.id);
			npchar.loyality = 30;
			npchar.greeting = "Gr_Officer";
			npchar.Dialog.Filename = "Enc_Officer_dialog.c";
			npchar.quest.meeting = true;
			AddDialogExitQuestFunction("LandEnc_OfficerHired");
			pchar.questTemp.Sharlie = "seabattle";//в Ле Франсуа
			DeleteAttribute(pchar, "NoNavyPenalty"); // штрафуем за нехватку навигации
		break;
		// штурман
		
		// --> пират-обманщик
		case "Seabattle_pirate":
			dialog.text = "My apologies. "+GetFullName(pchar)+"?";
			link.l1 = "Correct. What do I owe for this occasion, sir?";
			link.l1.go = "Seabattle_pirate_1";
		break;
		
		case "Seabattle_pirate_1":
			dialog.text = "Allow me to introduce myself - "+GetFullName(npchar)+". I've been sent here to you by Cesar Craig. You must know him. He's the owner of Le Francois tavern. As far as he is informed, you are about to depart to Guadeloupe and he would like to offer you a nice way of making some extra money.";
			link.l1 = "Hm... Interesting! And how has Cesar Craig become so well-informed of my plans?";
			link.l1.go = "Seabattle_pirate_2";
		break;
		
		case "Seabattle_pirate_2":
			dialog.text = "Captain, it's simple. Your ship is the only ship in St. Pierre at the moment, so everyone is pretty much fully informed about you: who you are and where you're going. In this neck of the woods, rumours float around at about the speed of seagull. So are you interested in hearing what I have to offer?";
			link.l1 = "Sure. I never oppose to make some money.";
			link.l1.go = "Seabattle_pirate_3";
		break;
		
		case "Seabattle_pirate_3":
			dialog.text = "Now we are talking! I can always see a business spirit in people. So, Cesar urgently needs a batch of our wine to be delivered to Guadeloupe. Two hundred barrels, your ship's hold can take them easily\nTen thousand pesos for such an easy job - Cesar is in a hurry, and your ship is the only ship in the harbour right now. Do agree, such profitable proposals are rare.";
			link.l1 = "Ten thousands pesos? Well, we have a deal!";
			link.l1.go = "Seabattle_pirate_4";
		break;
		
		case "Seabattle_pirate_4":
			dialog.text = "Depart to Le Francois port and speak with Cesar. He will organize everything himself all you'll have to do is set your ship at bay. Don't let us down, cap: Craig has promised me a thousand pesos if I manage to convince you...";
			link.l1 = "Don't worry. You can consider me convinced. As soon as I'm ready to depart, I will move directly over to Le Francois.";
			link.l1.go = "Seabattle_pirate_5";
		break;
		
		case "Seabattle_pirate_5":
			dialog.text = "Creat! Then I'll go get my thousand. Thank you, cap!";
			link.l1 = "Not at all...";
			link.l1.go = "Seabattle_pirate_6";
		break;
		
		case "Seabattle_pirate_6":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "gate_back", "none", "", "", "Seabattle_pirate_open", -1);
			AddQuestRecord("Sharlie", "11");
		break;
		// пират-обманщик
		
		// офицер Гриффондора
		case "griffondor_officer":
			dialog.text = "";
			link.l1 = "";
			link.l1.go = "exit";
		break;
		
		// командир абордажной роты по защите Сен-Пьера
		case "rosetti":
			PlaySound("VOICE\Russian\EvilPirates01.wav");
			dialog.text = "Captain, the boarding squad is formed and in full military promptitude! Awaiting orders!";
			link.l1 = "";
			link.l1.go = "rosetti_1";
		break;
		
		case "rosetti_1":
			DialogExit();
			bDisableCharacterMenu = true;//лоченые интерфейсы
			ChangeShowIntarface();
			LAi_SetActorType(pchar);
			SetMainCharacterIndex(GetCharacterIndex("DefendSP_soldier_0"));
			PChar = GetMainCharacter();			
			LAi_SetPlayerType(PChar);
			sld = characterFromId("Blaze");
			sld.dialog.filename = "MainHero_dialog.c";
			sld.dialog.currentnode = "SP_defend";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;
		
		case "rosetti_2":
			PlaySound("interface\abordage_wining.wav");
			dialog.text = "Got it, captain! Squad, get ready! Moving out! Hip-hip-hurrah! Onward, follow the captain!";
			link.l1 = "";
			link.l1.go = "rosetti_3";
		break;
		
		case "rosetti_3":
			DialogExit();
			PlaySound("interface\abordage_wining.wav");
			bDisableCharacterMenu = false;//лоченые интерфейсы
			ChangeShowIntarface();
			for (i=0; i<=12; i++)
			{
				sld = CharacterFromID("DefendSP_soldier_"+i);
				LAi_SetActorType(sld);
				LAi_ActorFollowEverywhere(sld, "", -1);
				LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			}
			// прерывание на джунгли перед выходом из города
			pchar.quest.DefendSP_jungle1.win_condition.l1 = "location";
			pchar.quest.DefendSP_jungle1.win_condition.l1.location = "Martinique_jungle_01";
			pchar.quest.DefendSP_jungle1.function = "DefendSP_SpainPatrol";
		break;
		
		case "spain_patrol":
			dialog.text = "Frenchmen! Engage! Lorenzo, hurry into the camp! Give the alarm! Die, fuckers!";
			link.l1 = "...";
			link.l1.go = "spain_patrol_1";
		break;
		
		case "spain_patrol_1":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешить драться
			for (i=1; i<=4; i++)
			{
				sld = CharacterFromID("DefendSP_spapatrol_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
				LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
				LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
				LAi_group_SetCheck("EnemyFight", "DefendSP_SpaPatrolDie");
				AddDialogExitQuest("MainHeroFightModeOn");
			}
			sld = CharacterFromID("DefendSP_spapatrol_5");
			LAi_ActorRunToLocation(sld, "reload", "reload2_back", "none", "", "", "DefendSP_GateAlarm", -1);
		break;
		
		// страж истины
		case "spanish":
			dialog.text = "Do you understand that I am not authorized to disseminate such information?";
			link.l1 = "Do you understand that it's only thanks to my opportune assistance that St. Pierre wasn't ripped apart by the Spanish? My brother has hidden himself, leaving service to the Society. He did that for a reason. I, as a representative of Philippe de Poincy's interests, am obliged to investigate!";
			link.l1.go = "spanish_1";
		break;
		
		case "spanish_1":
			dialog.text = "All right, all right, monsieur de Maure. I will give you an answer to all of your questions. Just keep your cool. Now ask.";
			link.l1 = "What happened prior to Michel's being locked up under guard?";
			link.l1.go = "spanish_2";
		break;
		
		case "spanish_2":
			dialog.text = "Michel de Monper was negotiating with powerful pirate barons to call a political realignment on Tortuga.";
			link.l1 = "That I know. What else?";
			link.l1.go = "spanish_3";
		break;
		
		case "spanish_3":
			dialog.text = "He also had been planning an operation against the Spanish, to be more specific - a capture of one Spanish ship with a very valuable cargo. You brother was somehow supposed to lure the Spanish transport right to the cannons of light frigate 'Gryffondor'. Michel was taking part in some expedition over a long period of time, we didn't heard of him for a while\nBut something went wrong, because the Spanish transport didn't come and Michel himself was found by local fishermen at Le Marin bay. He was contused and barely alive. It seems that the operation was failed\nWar is war, he survived - that is quite an accomplishment itself, but chevalier de Poincy absolutely unexpectedly took up arms against Michel for no reason, he accused him of peculation and stealing the Order's money, and finally had him imprisoned\nOf course, we didn't believe in those accusations. Michel is an honest lad, only God knows why they're on edge with each other. Perhaps, monsieur de Poincy will tell you that himself?";
			link.l1 = "Possibly. Is that all you know?";
			link.l1.go = "spanish_4";
		break;
		
		case "spanish_4":
			dialog.text = "Unfortunately, there's nothing to be added to what's already been said. The details of all operations conducted by your brother were known only by him himself and chevalier de Poincy. We are officers and soldiers of the Society. We're just carrying out orders.";
			link.l1 = "If chevalier is so trusting of Michel, then weren't not all of his operations in vain? Were there fruitful ones as well?";
			link.l1.go = "spanish_5";
		break;
		
		case "spanish_5":
			dialog.text = "Most definitely. The last muff by Michel de Monper was also his first muff, which is why we were literally shocked by the reaction of the chevalier. Not particularly long before that with aid of Michel's thoroughly planned operation 'Gryffindor', a Spanish galleon was captured stacked all in silver. That alone could have compensated for dozens of muffs in the future. And yet, your brother was arrested.";
			link.l1 = "I see. Do you have any assumptions on why Michel so quickly hid away from St. Pierre?";
			link.l1.go = "spanish_6";
		break;
		
		case "spanish_6":
			dialog.text = "I suspect that an interpersonal conflict was the reason of the arrest. Obviously, your brother fears that the chevalier will continue persecutions against him even after the final release, so he took precautionary measures. And you know what, monsieur de Maure - nobody here blames him for his decision!\nThe man had been working hard and bravely for the good of the Order and yet they had, wounded and in a bad health, thrown him into the cell for the very first failure of him. The failure he could compensate without a problem!\nAnd by the way, this is an unofficial conversation and I won't repeat what I have just said under oath, are we clear on that, monsieur de Maure?";
			link.l1 = "Definitely, officer. We had arranged for that from the very beginning. Tell me, could the Spanish attack on St. Pierre have been provoked by the military operations of the Society against Spanish ships? That same Spanish galleon with silver that you mentioned? Those Castilians were painfully zealous in fitting out your base...";
			link.l1.go = "spanish_7";
		break;
		
		case "spanish_7":
			dialog.text = "Doubt it. A very few people know about our base here and all of our actions against the Spanish were accurate and well planned. Ask the Spanish officer we have captured, he is in our dungeons now. We have already interrogated him\nThe attack of Sent Pierre was an ordinary raid, organized by a Spanish grand, baron Ramon de Mendoza y Riba for the purpose of his own profit and an act of intimidation of French colonies. He also wanted to gain favour to Escorial.";
			link.l1 = "I will speak to your captive. Where can I find him?";
			link.l1.go = "spanish_8";
		break;
		
		case "spanish_8":
			dialog.text = "Downstairs, in the cell where your brother was held.";
			link.l1 = "Alright. I'll be back after I interrogate the Spaniard. Maybe I'll have additional questions.";
			link.l1.go = "spanish_9";
		break;
		
		case "spanish_9":
			DialogExit();
			NextDiag.CurrentNode = "Maltie_officer";
			AddQuestRecord("Guardoftruth", "2");
			pchar.questTemp.Guardoftruth = "prisoner";
			sld = characterFromId("spa_baseprisoner");
			LAi_CharacterEnableDialog(sld);
			chrDisableReloadToLocation = true;//закрыть локацию
		break;
		
		case "spanish_10":
			dialog.text = "Well isn't that news! But I can't release the captive. He was participating in the attack on St. Pierre...";
			link.l1 = "Officer, this is an important witness. The attack on St. Pierre was perpetuated not for theft. Don Ramon Mendosa was looking for something else. We need to get a definitive motive on this. So will you release this Spaniard to me or will I have to demand permission from de Poincy?";
			link.l1.go = "spanish_11";
		break;
		
		case "spanish_11":
			dialog.text = "All right, take him. I was about to publicly put this bastard to death anyway on St. Pierre square... But he's strictly under your own personal liability!";
			link.l1 = "Undoubtedly. I will answer for this Spaniard before de Poincy. Have this captive shackled and delivered to the port onto my longboat.";
			link.l1.go = "spanish_12";
		break;
		
		case "spanish_12":
			dialog.text = "Will do, captain.";
			link.l1 = "And one more thing, officer: does the name Miguel Dichoso ring a bell to you?";
			link.l1.go = "spanish_13";
		break;
		
		case "spanish_13":
			dialog.text = "No. I've never heard it before. Why are you asking?";
			link.l1 = "Are you sure? So you haven't met anyone by that name, neither on your base, nor in the governor's palace, nor anywhere in St. Pierre?";
			link.l1.go = "spanish_14";
		break;
		
		case "spanish_14":
			dialog.text = "No, I haven't. You know, we don't think too well of Spaniards where I'm from.";
			link.l1 = "Alright. Anyway, that's to be expected. It would have been too simple... Thank you officer! You've been very helpful.";
			link.l1.go = "spanish_15";
		break;
		
		case "spanish_15":
			dialog.text = "Oh, you are welcome... What do you think, monsieur de Maure, where is your brother now?";
			link.l1 = "I would like to know the answer to that question myself. And I will find out... sooner or later. Good luck!";
			link.l1.go = "spanish_16";
		break;
		
		case "spanish_16":
			DialogExit();
			NextDiag.CurrentNode = "Maltie_officer";
			AddQuestRecord("Guardoftruth", "3");
			pchar.questTemp.Guardoftruth = "toship";
			sld = characterFromId("spa_baseprisoner");
			sld.dialog.currentnode = "spa_prisoner_28";
			LAi_CharacterEnableDialog(sld);
		break;
		
		// монах-посланник от Винсенто
		case "monk_vinsento":
			dialog.text = TimeGreeting()+"! Are you captain "+GetFullName(pchar)+"?";
			link.l1 = "Yes, it is me. What can I do for you?";
			link.l1.go = "monk_vinsento_1";
		break;
		
		case "monk_vinsento_1":
			dialog.text = "I've been sent to you by father Vincento. I've got something for you...";
			link.l1 = "Father Vincento? I don't work with His Grace anymore. Not after he sent Alonso de Maldonado, Diego de Montoya's buddy, after me. He failed, you can pass this on to His Grace.";
			link.l1.go = "monk_vinsento_2";
		break;
		
		case "monk_vinsento_2":
			dialog.text = "Wait, captain. Father Vincento expected such a reaction from you and warned me of this. I assure you that His Grace does not wish you any ill. Please, read this letter. It's very, very important.";
			link.l1 = "He doesn't wish me any ill? Hm. Maybe he also failed to tell you anything about me and Don de Maldonado? I don't feel that way I could believe it.";
			link.l1.go = "monk_vinsento_3";
		break;
		
		case "monk_vinsento_3":
			dialog.text = "Take this letter, captain. Read it and make your own decision. Just remember that the fate of the entire Christian world is now in your hands. Don't take this lightly. May God bless you and send your feet on a righteous path!";
			link.l1 = "All right, give me the letter.";
			link.l1.go = "monk_vinsento_4";
		break;
		
		case "monk_vinsento_4":
			GiveItem2Character(pchar, "specialletter"); 
			ChangeItemDescribe("specialletter", "itmdescr_specialletter_vinsento");
			sld = ItemsFromID("specialletter");
			sld.text = "Letter_Vincento_last";
			dialog.text = "Here you go. I hope you'll make the right decision.";
			link.l1 = "...";
			link.l1.go = "monk_vinsento_5";
		break;
		
		case "monk_vinsento_5":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload4_back", "none", "", "", "", 30.0);
			ReOpenQuestHeader("Sharlie"); // patch-8
			AddQuestRecord("Sharlie", "40");
			CloseQuestHeader("Ksochitam");
		break;
		
		// падре Адриан
		case "adrian":
			dialog.text = "Greetings, my son. May the Lord bless all of your doings...";
			link.l1 = "Hello, father Adrian. His Grace has told me that you are can equip me with amulets and medicines...";
			link.l1.go = "adrian_1";
		break;
		
		case "adrian_1":
			dialog.text = "Yes, of course. This package, which I brought directly from Santiago is just for you. Here are sanctified amulets and health-giving decoctions. And even a rare, unique Ometochli tincture which fortifies combat qualities. This is all for you, my son.";
			link.l1 = "Thank you!";
			link.l1.go = "adrian_2";
		break;
		
		case "adrian_2":
			for(i=2; i<=10; i++)
			{
				if (i == 4 || i == 5 || i == 8 || i == 9) continue;
				TakeNItems(pchar, "amulet_"+i, 2);
			}
			TakeNItems(pchar, "potion2", 20);
			TakeNItems(pchar, "potion4", 10);
			TakeNItems(pchar, "potion7", 3);
			TakeNItems(pchar, "berserker_potion", 3);
			dialog.text = "If you do need any more health-giving herbs, you can acquire them from me, a vial of each every day. I will prepare as much of them as you need.";
			link.l1 = "All right, father Adrian. I'll keep that in mind.";
			link.l1.go = "exit";
			link.l2 = "Great. I would like to acquire some of them right now.";
			link.l2.go = "potion";
			NextDiag.TempNode = "adrian_3";
		break;
		
		case "adrian_3":
			dialog.text = "God bless you, my son. What would you like?";
			link.l1 = "I would like to purchase several health-giving elixirs.";
			link.l1.go = "potion";
			link.l2 = "Nothing at the moment. I'm preparing for a journey. Just stopped by to see how you are doing here.";
			link.l2.go = "exit";
			NextDiag.TempNode = "adrian_3";
		break;
		
		case "potion":
			dialog.text = "Of course, my son. What medicine would you like to acquire?";
			if (!CheckAttribute(npchar, "potion1_date") || GetNpcQuestPastDayParam(npchar, "potion1_date") >= 1)
			{
				link.l1 = "Just a remedial essence.";
				link.l1.go = "potion1";
			}
			if (!CheckAttribute(npchar, "potion2_date") || GetNpcQuestPastDayParam(npchar, "potion2_date") >= 1)
			{
				link.l2 = "A health-giving elixir.";
				link.l2.go = "potion2";
			}
			if (!CheckAttribute(npchar, "potion3_date") || GetNpcQuestPastDayParam(npchar, "potion3_date") >= 1)
			{
				link.l3 = "An antidote.";
				link.l3.go = "potion3";
			}
			if (!CheckAttribute(npchar, "potion4_date") || GetNpcQuestPastDayParam(npchar, "potion4_date") >= 1)
			{
				link.l4 = "An herbal mixture.";
				link.l4.go = "potion4";
			}
			link.l5 = "Forgive me, father Adrian. I've changed my mind.";
			link.l5.go = "exit";
		break;
		
		case "potion1":
			npchar.quest.price = 90;
			npchar.quest.type = 1;
			dialog.text = "A remedial essence? That'll be 90 pesos, my son.";
			if (sti(Pchar.money) >= 90)
			{
				link.l1 = "Here you go, father Adrian. Here's the money.";
				link.l1.go = "potion_pay";
			}
			else
			{
				link.l1 = "Unfortunately, I don't have sufficient funds... I'll return later.";
				link.l1.go = "exit";
			}
		break;
		
		case "potion2":
			npchar.quest.price = 500;
			npchar.quest.type = 2;
			dialog.text = "A health-giving elixir? That'll be 500 pesos, my son.";
			if (sti(Pchar.money) >= 500)
			{
				link.l1 = "Here you go, father Adrian. Here's the money.";
				link.l1.go = "potion_pay";
			}
			else
			{
				link.l1 = "Unfortunately, I don't have sufficient funds... I'll return later.";
				link.l1.go = "exit";
			}
		break;
		
		case "potion3":
			npchar.quest.price = 200;
			npchar.quest.type = 3;
			dialog.text = "An antidote? That'll be 200 pesos, my son.";
			if (sti(Pchar.money) >= 200)
			{
				link.l1 = "Here you go, father Adrian. Here's the money.";
				link.l1.go = "potion_pay";
			}
			else
			{
				link.l1 = "Unfortunately, I don't have sufficient funds... I'll return later.";
				link.l1.go = "exit";
			}
		break;
		
		case "potion4":
			npchar.quest.price = 900;
			npchar.quest.type = 4;
			dialog.text = "A herbal mixture? That'll be 900 pesos, my son.";
			if (sti(Pchar.money) >= 900)
			{
				link.l1 = "Here you go, father Adrian. Here's the money.";
				link.l1.go = "potion_pay";
			}
			else
			{
				link.l1 = "Unfortunately, I don't have sufficient funds... I'll return later.";
				link.l1.go = "exit";
			}
		break;
		
		case "potion_pay":
			AddMoneyToCharacter(pchar, -sti(npchar.quest.price));
			iTemp = sti(npchar.quest.type);
			GiveItem2Character(pchar, "potion"+iTemp);
			PlaySound("interface\important_item.wav");
			dialog.text = "Here you are. Take your medicine. May the Lord watch over you!";
			link.l1 = "Thank you, father Adrian.";
			link.l1.go = "exit";
			SaveCurrentNpcQuestDateParam(npchar, "potion"+iTemp+"_date");
			NextDiag.TempNode = "adrian_3";
		break;
		
		// посланец Дичозо
		case "Dichoso_agent":
			dialog.text = "Captain "+GetFullName(pchar)+"?";
			link.l1 = "Yes, it is me. What do I owe for this visit?";
			link.l1.go = "Dichoso_agent_1";
		break;
		
		case "Dichoso_agent_1":
			dialog.text = "I have a message for you from captain Miguel Dichoso. He says you know him.";
			link.l1 = "I haven't had the honour to know him in person, but yes I heard something of him.";
			link.l1.go = "Dichoso_agent_2";
		break;
		
		case "Dichoso_agent_2":
			dialog.text = "Captain Dichoso would like to meet with you. He has an offer for you concerning a hike into the depths of Main to the Indian city of Tayasal. He told me that your experience coupled with his knowledge would produce an excellent result.";
			link.l1 = "Those were his exact words?";
			link.l1.go = "Dichoso_agent_3";
		break;
		
		case "Dichoso_agent_3":
			dialog.text = "Yes! Captain Dichoso will be waiting for you on St. Christopher island. In order to avoid unneeded eyes and ears, Miguel proposes to hold a meeting with you in the large crypt of the Capsterville cemetery.";
			link.l1 = "Hm...";
			link.l1.go = "Dichoso_agent_4";
		break;
		
		case "Dichoso_agent_4":
			dialog.text = "Dichoso warned me that you would hesitate and authorized me to assure you that he guarantees a peaceful conclusion to your negotiation no mater what. And he also asked me to pass on to you that what you found on one island was just the tip of the iceberg considering what you would find in Tayasal.";
			link.l1 = "Is that so! Then that's very interesting. But why wouldn't captain Dichoso pay a visit to me himself and send a third party instead?";
			link.l1.go = "Dichoso_agent_5";
		break;
		
		case "Dichoso_agent_5":
			dialog.text = "Don Dichoso had been searching for you on Isla Tesoro, then here, and now has departed to St. Christopher in hope of finding you there. You are an officer of Philippe de Poincy himself, aren't you? I was supposed to wait for you here in case that you would arrive in Blueweld.";
			link.l1 = "Then it's all clear. Well, all right. I won't waste any time. I should go to Capsterville.";
			link.l1.go = "Dichoso_agent_6";
		break;
		
		case "Dichoso_agent_6":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload4_back", "none", "", "", "Tieyasal_PrepareDichosoTrap", -1);
		break;
		
		// агент Дичозо
		case "Dichoso_crypt_agent":
			dialog.text = "Well, finally we met, captain "+GetFullName(pchar)+"...";
			if (CheckAttribute(pchar, "questTemp.Tieyasal.MigelKnow")) 
			{
				link.l1 = "Where is Miguel Dichoso? And don't try to wheedle out of this. I know very well who he really is and I think you do too.";
				link.l1.go = "Dichoso_crypt_agent_2";
			}
			else
			{
				link.l1 = "I suppose this is Miguel Dichoso in the flesh right in front of me?";
				link.l1.go = "Dichoso_crypt_agent_1";
			}
		break;
		
		case "Dichoso_crypt_agent_1":
			dialog.text = "You suppose correctly, captain. We have been on each other's heals for a long time, haven't we?";
			if (CheckAttribute(pchar, "questTemp.Ksochitam.SQCapBookRead")) // прочел журнал Санта-Квитерии
			{
				link.l1 = "I look at you right now, buddy, and I can tell that you're lying. You're no Dichoso. I've read the stern notebook entries by the captain of the 'Santa Quiteria' and also asked around about his appearance. You don't really look like him. You don't even have a scar on your face from a cavalry sword.";
				link.l1.go = "Dichoso_crypt_agent_2";
			}
			else
			{
				link.l1 = "Exactly. As I understand, we're talking about Tayasal?";
				link.l1.go = "Dichoso_crypt_agent_7";
			}
		break;
		
		case "Dichoso_crypt_agent_2":
			dialog.text = "Hm. Well, there's no point in playing hide and seek then. Miguel warned that you are one hell of a sharp rascal...";
			link.l1 = "Where is Dichoso?";
			link.l1.go = "Dichoso_crypt_agent_3";
		break;
		
		case "Dichoso_crypt_agent_3":
			dialog.text = "He's not here. I am authorized to meet you and chat with you on his behalf.";
			link.l1 = "I have no desire to speak with a pawn. I need the queen. So where is he?";
			link.l1.go = "Dichoso_crypt_agent_4";
		break;
		
		case "Dichoso_crypt_agent_4":
			dialog.text = "This conversation isn't going to last very long, captain. You weren't invited here to go on raving, you know.";
			link.l1 = "I get it. A primitive ambush trap. Did I guess it right?";
			link.l1.go = "Dichoso_crypt_agent_5";
		break;
		
		case "Dichoso_crypt_agent_5":
			dialog.text = "Right on the dot, buddy. Right behind that door is a basement and my people are waiting in there. Besides that, I've hidden a retracted shooter into each grave. You're way back is completely cut off. So as primitive as this trap may be, you've climbed into it. Your desire to see Tayasal has outweighed your sense of caution, has it?";
			link.l1 = "You've picked a great place for an ambush, buddy. We're gonna bury you and your bandits right into the graves.";
			link.l1.go = "Dichoso_crypt_agent_6";
		break;
		
		case "Dichoso_crypt_agent_6":
			dialog.text = "I like your sense of humour. That you have in common with Michel. Say what you will, he's your flesh and blood... I'll do just as he requested - I'll send you into the other world as fast and painlessly as possible. Guys, prepare for action!";
			link.l1 = "Many have tried to do that, but their hands are yet short...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Tieyasal_StartCryptBattle");
		break;
		
		case "Dichoso_crypt_agent_7":
			dialog.text = "You really want to make it there? I get it. But I don't think it's a good idea.";
			link.l1 = "Then what were you about to discuss with me?";
			link.l1.go = "Dichoso_crypt_agent_8";
		break;
		
		case "Dichoso_crypt_agent_8":
			dialog.text = "I wasn't looking to enter a deep, long conversation with you. You're here and that for me is enough.";
			link.l1 = "I get it. A primitive ambush trap. Did I guess right?";
			link.l1.go = "Dichoso_crypt_agent_5";
		break;
		
		// командир абордажников
		case "newcastle_officer":
			dialog.text = "Awaiting your orders, captain!";
			link.l1 = "We move out through the jungle toward the St. Christopher cemetery. Don't enter the cemetery itself, assume your position along the trail and follow what goes on. In the case of danger, attack.";
			link.l1.go = "newcastle_officer_1";
		break;
		
		case "newcastle_officer_0":
			dialog.text = "Awaiting your orders, captain!";
			link.l1 = "We move out through the jungle toward the St. Christopher cemetery. Don't enter the cemetery itself, assume your position along the trail, surround the perimeter, and follow what goes on. The enemy is surely planning an ambush. As soon as you see the enemy, attack immediately.";
			link.l1.go = "newcastle_officer_1";
		break;
		
		case "newcastle_officer_1":
			dialog.text = "Yes, captain!  ";
			link.l1 = "All right. Onward!";
			link.l1.go = "newcastle_officer_2";
		break;
		
		case "newcastle_officer_2":
			DialogExit();
			chrDisableReloadToLocation = false;
			locations[FindLocation("Charles_exittown")].DisableEncounters = true; //энкаутеры закрыть
			locations[FindLocation("Charles_CaveEntrance")].DisableEncounters = true; //энкаутеры закрыть
			for(i=2; i<=4; i++)
			{
				locations[FindLocation("Charles_Jungle_0"+i)].DisableEncounters = true; //энкаутеры закрыть
			}
			LocatorReloadEnterDisable("Shore42", "boat", true);
			for(i=1; i<=iTotalTemp; i++)
			{
				sld = characterFromID("Tieyasal_Oursoldier_"+i);
				LAi_SetActorType(sld);
				LAi_ActorFollowEverywhere(sld, "", -1);
				LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			}
			// на локацию перед кладбищем
			pchar.quest.Tieyasal_newcastle.win_condition.l1 = "location";
			pchar.quest.Tieyasal_newcastle.win_condition.l1.location = "Charles_exittown";
			pchar.quest.Tieyasal_newcastle.function = "Tieyasal_NewcastleGoJungle";
			// на крипту
			pchar.quest.Tieyasal_graveyard.win_condition.l1 = "location";
			pchar.quest.Tieyasal_graveyard.win_condition.l1.location = "Charles_CryptBig2";
			pchar.quest.Tieyasal_graveyard.function = "Tieyasal_InGraveyardCrypt";
		break;
		
		case "Europe":
			PlaySound("VOICE\Russian\military01.wav");
			dialog.text = "Captain Hobart! According to the spy's information, runaway rebels are hiding out in this estate. There are five dragoons at your disposal search the building and seize the anybody hanging out inside there! Don't handle with kid gloves. You're acting in the name of the king!";
			link.l1 = "Yes, sir!";
			link.l1.go = "Europe_1";
		break;
		
		case "Europe_1":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_SetActorType(pchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "Europe_SharlieFinal_1", 5);
		break;
		
		//замечание по обнаженному оружию от персонажей типа citizen
		case "CitizenNotBlade":
			dialog.text = NPCharSexPhrase(NPChar, "Listen. I, as a citizen of this city, ask you to not walk around here with exposed blade.", "You know, I, as a citizen of this city, ask you to not walk around here with exposed blade.");
			link.l1 = LinkRandPhrase("All right.", "Fine.", "As you wish...");
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
			if (npchar.id == "GigoloMan") NextDiag.TempNode = "GigoloMan";
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
