#include "DIALOGS\russian\Rumours\Common_rumours.c" //Jason
// Jason общий диалог смотрителей маяков
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;	

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

    // вызов диалога по городам -->
    NPChar.FileDialog2 = "DIALOGS\" + LanguageGetLanguage() + "\Lighthouse\" + NPChar.City + "_Lighthouse.c";
    if (LoadSegment(NPChar.FileDialog2))
	{
        ProcessCommonDialog(NPChar, Link, NextDiag);
		UnloadSegment(NPChar.FileDialog2);
	}
    // вызов диалога по городам <--
	ProcessCommonDialogRumors(NPChar, Link, NextDiag);
	
    int iTest, iTemp;
	string sTemp;
	bool ok;
    iTest = FindColony(NPChar.City); // город
    ref rColony;
	if (iTest != -1)
	{
		rColony = GetColonyByIndex(iTest);
	}
	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (LAi_grp_playeralarm > 0)
			{
       			dialog.text = PCharRepPhrase(LinkRandPhrase("Alarm is raised in the town. Apparently, it's time for me to take up arms as well...", "Aren't the town guards running after you, by the chance?", "You won't find a shelter here, but you may find several inches of cold steel under your rib!"), 
					LinkRandPhrase("What do you need, "+ GetSexPhrase("scoundrel","rascal") +"?! The guards are tracking you down, you won't get far, "+ GetSexPhrase("filthy pirate","stinker") +"!", ""+ GetSexPhrase("Filthy","Filthy") +" murderer! Guards!!!", "I don't fear you, "+ GetSexPhrase("creep","stinker") +"! Soon you will be hanged in our fort, you won't get far..."));
				link.l1 = PCharRepPhrase(RandPhraseSimple("I see you're tired of living...", "So it seems, there is no peaceful people in " + XI_ConvertString("Colony" + npchar.city + "Gen") + ", everyone wants to be a hero!"), 
					RandPhraseSimple("Go to hell!", "Heh, these will be the last few seconds of your life..."));
				link.l1.go = PCharRepPhrase("exit_setOwner", "fight");
				break;
			}
			if (npchar.quest.meeting == "0")
			{
				dialog.text = RandPhraseSimple("Good afternoon, sailor! My name is "+GetFullName(npchar)+", and I am the keeper of this lighthouse. What wind has brought you here?", "Hi there! It's been quite a while I last time saw new faces at my lighthouse... Allow me to introduce myself - "+GetFullName(npchar)+", and this lighthouse is my home and my job. What can I do for you?");
				link.l1 = "Hello there, "+npchar.name+"! My name is "+GetFullName(pchar)+", I am a ship captain. I was taking a walk in this wonderful cove and decided to stop by and take a look who lives there...";
				link.l1.go = "Lightman_meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "Oh, my old friend, captain "+GetFullName(pchar)+"! Come in, come in! What has brought you here this time?";
				link.l1 = "Hail to you, old salt! Aren't you wailing in solitude here at your lighthouse?";
				link.l1.go = "Lightman_talk";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "Lightman_meeting":
			dialog.text = "Now you know. I used to be a sailor, just like you, but it's been long ago since I last set foot on a ship's deck. Now this lighthouse is in my care, and I am also selling some stuff...";
			link.l1 = "And what exactly are you selling?";
			link.l1.go = "trade_info";
			NextDiag.TempNode = "First time";
		break;
		
		case "Lightman_talk":
			dialog.text = " What has brought you here this time?";
			link.l1 = RandPhraseSimple("Can you tell me, if anything interesting has recently happened in your colony?","I haven't been on land for quite a while... What's going on here?");
			link.l1.go = "rumours_lighthouse";
			link.l2 = "Let's see what you have for sale.";
			link.l2.go = "Trade_lighthouse";
			if (CheckAttribute(npchar, "artefact"))
			{
				if (CheckAttribute(npchar, "quest.art"))
				{
					link.l3 = "So, "+npchar.name+", has my amulet arrived already?";
					link.l3.go = "Trade_artefact_3";
				}
				else
				{
					link.l3 = ""+npchar.name+", I want to order an amulet from you.";
					link.l3.go = "Trade_artefact_1";
				}
				// калеуче
				if (CheckAttribute(pchar, "questTemp.Caleuche") && pchar.questTemp.Caleuche == "amulet" && !CheckAttribute(npchar, "quest.Caleuche"))
				{
					link.l5 = "Listen, "+npchar.name+", I know that you engage in delivery of amulets to order. So, you certainly know a lot about them. Look, please, at this little thing - what can you tell me about it?";
					link.l5.go = "Caleuche";
				}
//				if (npchar.id == pchar.questTemp.Caleuche.Amuletmaster && CheckAttribute(pchar, "questTemp.Caleuche") && pchar.questTemp.Caleuche == "mayak")
				if (CheckAttribute(pchar, "questTemp.Caleuche") && npchar.id == pchar.questTemp.Caleuche.Amuletmaster && pchar.questTemp.Caleuche == "mayak")
				{
					link.l5 = "Friend, I'm here again to ask you about those strange amulets";
					link.l5.go = "Caleuche_9";
				}
			}
			link.l4 = "There is something I was going to ask you...";
			link.l4.go = "quests";
			NextDiag.TempNode = "First time";
		break;
		
		case "trade_info":
			dialog.text = "Sometimes I go to the shore and collect shells, there is one pretty place not far from here, so you can always buy pearls from me. Every storm brings amber, I sell it too, although it will cost you a lot\nSometimes the waves bring all kinds of interesting trinkets from sunken ships and my old buddies bring me special items. I am interested in enchanted amulets, wise men pay good coin for those\nI also offer weapons on special occasion, don't ask me where I get it. A town merchant buys all the crap from me, good stuff I sell myself after I repair and clean it\nI am interested in rum. I am not talking about the piss they serve in local tavern for two pesos per mug. I am talking about real bottled Jamaican rum. It heals and resurrects people. I will pay ten times more for every bottle you bring. Think about it.";
			link.l1 = "Listen, "+npchar.name+", you said that you had old sailor friends, who bring you ensorcelled amulets. Is it possible to order a certain amulet from you? I will pay for it handsomely.";
			link.l1.go = "Trade_artefact";
		break;
		
		case "Trade_lighthouse":
			//иногда продает корабельные товары // Addon-2016 Jason
			npchar.quest.goods = GOOD_COFFEE + drand(sti(GOOD_PAPRIKA - GOOD_COFFEE));
			npchar.quest.goodsqty = 50+drand(100);
			if (sti(npchar.quest.goods) == GOOD_EBONY || sti(npchar.quest.goods) == GOOD_MAHOGANY) npchar.quest.goodsqty = 25+drand(50);
			npchar.quest.goodsprice = makeint(sti(Goods[sti(npchar.quest.goods)].Cost)/4);//цена единицы товара
			npchar.quest.goodscost = sti(npchar.quest.goodsprice)*sti(npchar.quest.goodsqty);//стоимость товара
			ok = (!CheckAttribute(npchar, "goods_date")) || (GetNpcQuestPastDayParam(npchar, "goods_date") >= 10)
			if (drand(2) == 1 && makeint(GetCharacterFreeSpace(pchar, sti(npchar.quest.goods))) > sti(npchar.quest.goodsqty) && sti(pchar.money) >= sti(npchar.quest.goodscost) && ok)
			{
				dialog.text = "Captain, an amount of goods was recently washed ashore - " + GetGoodsNameAlt(sti(npchar.quest.goods)) + ". Some part was spoiled by salty water, but " + FindRussianQtyString(sti(npchar.quest.goodsqty)) + " I managed to save in great state. Want to buy some? I'll give them away cheaply, just for "+FindRussianMoneyString(sti(npchar.quest.goodsprice))+" per unit.";
				link.l1 = "Nah. Show me you recent gatherings.";
				link.l1.go = "Trade_lighthouse_double";
				link.l2 = "Hm... An honest offer, I agree. I guess I could resell it for some profit. Let's see... That will amount to "+FindRussianMoneyString(sti(npchar.quest.goodscost))+". Is that correct?";
				link.l2.go = "Trade_goods";
				SaveCurrentNpcQuestDateParam(npchar, "goods_date");
			}
			else
			{
				DialogExit();
				if (!CheckAttribute(npchar, "trade_date") || GetNpcQuestPastDayParam(npchar, "trade_date") >= 10)
				{
					GiveItemToTrader(npchar);
					SaveCurrentNpcQuestDateParam(npchar, "trade_date");
				}
				LaunchItemsTrade(npchar, 0);
			}
		break;
		
		case "Trade_lighthouse_double":
			DialogExit();
			if (!CheckAttribute(npchar, "trade_date") || GetNpcQuestPastDayParam(npchar, "trade_date") >= 10)
			{
				GiveItemToTrader(npchar);
				SaveCurrentNpcQuestDateParam(npchar, "trade_date");
			}
			LaunchItemsTrade(npchar, 0);
		break;
		
		case "Trade_goods":
			AddCharacterGoods(pchar, sti(npchar.quest.goods), sti(npchar.quest.goodsqty));
			AddMoneyToCharacter(pchar, -sti(npchar.quest.goodscost));
			AddMoneyToCharacter(npchar, sti(npchar.quest.goodscost));
			dialog.text = "You've got it right, captain. A great bargain! We both made decent profit of it...";
			link.l1 = "Alright, then. I'll send the sailors to take the cargo to my ship. Now show me what you've gathered for sale.";
			link.l1.go = "Trade_lighthouse_double";
		break;
//------------------------------------------------заказ артефактов------------------------------------------------
		case "Trade_artefact":
			if (CheckAttribute(npchar, "artefact")) // Addon-2016 Jason за дублоны
			{
				dialog.text = "Well, not all of them, but several trinkets are brought often that others, so I guess I'd be able to help you. But I warn you: all amulets you order in this way will cost you 100 doubloons. You should understand...";
				link.l1 = "Price is not a problem. What amulets can you deliver?";
				link.l1.go = "Trade_artefact_1";
				link.l2 = "Pff! One could buy a ship for such money. That's too expensive. I guess I'll do fine by myself...";
				link.l2.go = "exit_artefact";
			}
			else
			{
				dialog.text = "No, captain. Such things can be found purely by chance, so it's impossible to place orders for them in advance. And also you'd have to wait for them a bit less than forever...";
				link.l1 = "Well, if that's the case, there's nothing to be done.";
				link.l1.go = "exit_artefact";
			}
		break;
		
		case "exit_artefact":
			if (CheckAttribute(npchar, "artefact")) dialog.text = "As you wish. Come see me if you change your mind.";
			else dialog.text = "Would you like to see what I have for sale today, captain? If you don't find anything worthy, come again soon - I might have something else up for sale.";
			link.l1 = "Show me your items.";
			link.l1.go = "Trade_lighthouse";
			link.l2 = "Just tell me, what interesting things have happened in your colony recently?";
			link.l2.go = "rumours_lighthouse";
			link.l3 = "Trade is trade, but I wanted to ask something.";
			link.l3.go = "quests";
			link.l4 = "Have a nice day, "+npchar.name+"! It was nice to meet you! I'll drop in some other time...";
			link.l4.go = "exit";
		break;
		
		case "Trade_artefact_1":
			dialog.text = "Make your pick.";
			iTemp = 1;
			string sArt;
			if (CheckAttribute(npchar, "artefact.indian")) sArt = "indian_";
			if (CheckAttribute(npchar, "artefact.amulet")) sArt = "amulet_";
			if (CheckAttribute(npchar, "artefact.obereg")) sArt = "obereg_";
			for (i=11; i>=1; i--)
			{
				sTemp = "l"+iTemp;
				link.(sTemp) = XI_ConvertString(sArt+i);
				link.(sTemp).go = sArt+i;
				iTemp++;
			}
			link.l12 = "Unfortunately, nothing from this list interests me so far.";
			link.l12.go = "exit";
		break;
		
		//группа indian
		case "indian_1":
			dialog.text = "A voodoo doll? You're fond of firearms? Good...";
			link.l1 = "When should I come back to pick up my order?";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "indian_1";
		break;
		
		case "indian_2":
			dialog.text = "A gunpowder tester? Sharpshooting is a key to success in any skirmish. Nice...";
			link.l1 = "When should I come back to pick up my order?";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "indian_2";
		break;
		
		case "indian_3":
			dialog.text = "A ritual knife? You like slashing your enemies with powerful swings of a heavy broadsword? That's for you, then. Good... ";
			link.l1 = "When should I come back to pick up my order?";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "indian_3";
		break;
		
		case "indian_4":
			dialog.text = "A pole axe? A top-down strike of a huge axe will crush any enemy! Good...";
			link.l1 = "When should I come back to pick up my order?";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "indian_4";
		break;
		
		case "indian_5":
			dialog.text = "A tsantsa? Now that thing can scare even the most reckless pirate. Good...";
			link.l1 = "When should I come back to pick up my order?";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "indian_5";
		break;
		
		case "indian_6":
			dialog.text = "A coral head? The grapeshot of your cannons will fly straight to the target! Good...";
			link.l1 = "When should I come back to pick up my order?";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "indian_6";
		break;
		
		case "indian_7":
			dialog.text = "Humpback? Tirelessness is warrior's best friend. Good...";
			link.l1 = "When should I come back to pick up my order?";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "indian_7";
		break;
		
		case "indian_8":
			dialog.text = "Xiuhtecuhtli? Let the enemy ship's hull crumble to dust! Good...";
			link.l1 = "When should I come back to pick up my order?";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "indian_8";
		break;
		
		case "indian_9":
			dialog.text = "Baldo? Put Baldo on - and all cannonballs will fly straight to the target! Good...";
			link.l1 = "When should I come back to pick up my order?";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "indian_9";
		break;
		
		case "indian_10":
			dialog.text = "Cascavella? Snake's venom is the most dangerous thing. Good...";
			link.l1 = "When should I come back to pick up my order?";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "indian_10";
		break;
		
		case "indian_11":
			dialog.text = "Ngombo mask? Put down vigilance of your enemies, ha-ha! Good...";
			link.l1 = "When should I come back to pick up my order?";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "indian_11";
		break;
		
		//группа amulet
		case "amulet_1":
			dialog.text = "Ngombo shield? If you didn't manage to dodge a bullet, this amulet can save your live. Good...";
			link.l1 = "When should I come back to pick up my order?";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "amulet_1";
		break;
		
		case "amulet_2":
			dialog.text = "Euchologion? A good pray can even divert a bullet. Good...";
			link.l1 = "When should I come back to pick up my order?";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "amulet_2";
		break;
		
		case "amulet_3":
			dialog.text = "A crucifix? This one will greatly aid a Christian in close combat. Good...";
			link.l1 = "When should I come back to pick up my order?";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "amulet_3";
		break;
		
		case "amulet_4":
			dialog.text = "El Trozo? This one will make a mortal wound just a scratch. Good...";
			link.l1 = "When should I come back to pick up my order?";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "amulet_4";
		break;
		
		case "amulet_5":
			dialog.text = "Sogbo? And let the cannons always be ready for battle! Good...";
			link.l1 = "When should I come back to pick up my order?";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "amulet_5";
		break;
		
		case "amulet_6":
			dialog.text = "Madonna? The visage of the Most Holy Virgin possesses powerful healing properties. Good...";
			link.l1 = "When should I come back to pick up my order?";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "amulet_6";
		break;
		
		case "amulet_7":
			dialog.text = "Holy water? Even a weakling sprinkled with holy water will become an epic hero! Good...";
			link.l1 = "When should I come back to pick up my order?";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "amulet_7";
		break;
		
		case "amulet_8":
			dialog.text = "An anchor? And may your ship stay afloat even under a volley of cannonballs, ha-ha! Good...";
			link.l1 = "When should I come back to pick up my order?";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "amulet_8";
		break;
		
		case "amulet_9":
			dialog.text = "Encolpion? You sails shall fear no wind, while you possess this amulet. Good...";
			link.l1 = "When should I come back to pick up my order?";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "amulet_9";
		break;
		
		case "amulet_10":
			dialog.text = "Wonderworker? May the Lord watch over you crew both on land and at sea! Good...";
			link.l1 = "When should I come back to pick up my order?";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "amulet_10";
		break;
		
		case "amulet_11":
			dialog.text = "Cimaruta? Musket bullets shall fly over your head, causing no harm! Good...";
			link.l1 = "When should I come back to pick up my order?";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "amulet_11";
		break;
		
		//группа obereg
		case "obereg_1":
			dialog.text = "Teredo? Every shipwright dreams of that one. Good...";
			link.l1 = "When should I come back to pick up my order?";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "obereg_1";
		break;
		
		case "obereg_2":
			dialog.text = "Xochipilli? That will save some time darning the sails. Good...";
			link.l1 = "When should I come back to pick up my order?";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "obereg_2";
		break;
		
		case "obereg_3":
			dialog.text = "A monkey? A pack mule, I'd say! Good...";
			link.l1 = "When should I come back to pick up my order?";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "obereg_3";
		break;
		
		case "obereg_4":
			dialog.text = "Gypsy's fan? Put the blinkers on a patroller's eyes! Good...";
			link.l1 = "When should I come back to pick up my order?";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "obereg_4";
		break;
		
		case "obereg_5":
			dialog.text = "A jade turtle? That's your ace in a deck of cards! Good...";
			link.l1 = "When should I come back to pick up my order?";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "obereg_5";
		break;
		
		case "obereg_6":
			dialog.text = "A monkey's fist? As they say - make them respect you! Good...";
			link.l1 = "When should I come back to pick up my order?";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "obereg_6";
		break;
		
		case "obereg_7":
			dialog.text = "A fisherman? That's every navigator's dream. Good...";
			link.l1 = "When should I come back to pick up my order?";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "obereg_7";
		break;
		
		case "obereg_8":
			dialog.text = "Merchant's beads? Money likes being counted, doesn't it? Good...";
			link.l1 = "When should I come back to pick up my order?";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "obereg_8";
		break;
		
		case "obereg_9":
			dialog.text = "Ehecatl? Any low-speed old tub will fly faster than wind! Good...";
			link.l1 = "When should I come back to pick up my order?";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "obereg_9";
		break;
		
		case "obereg_10":
			dialog.text = "Seafarer's earring? Give that one to your helmsman! Good...";
			link.l1 = "When should I come back to pick up my order?";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "obereg_10";
		break;
		
		case "obereg_11":
			dialog.text = "Pilgrim? Head wind becomes tail wind. Good...";
			link.l1 = "When should I come back to pick up my order?";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "obereg_11";
		break;
		
		case "Trade_artefact_2":
			dialog.text = "In two months, no sooner. I think by that time they will have brought it to me. So I'll be waiting for you with the money in two months.";
			link.l1 = "Great! I'll be there! Thank you, "+npchar.name+"!";
			link.l1.go = "exit";
			SaveCurrentNpcQuestDateParam(npchar, "art_date");
			npchar.quest.artday = rand(20)+50;
			sTemp = "Amulet_"+npchar.location;
			AddQuestRecord(sTemp, "1");
			ReOpenQuestHeader(sTemp);
			AddQuestUserData(sTemp, "sAml", XI_ConvertString(npchar.quest.art)); // dlc
		break;
		
		case "Trade_artefact_3":
			if (CheckAttribute(npchar, "art_date") && GetNpcQuestPastDayParam(npchar, "art_date") >= sti(npchar.quest.artday))
			{
			dialog.text = "Yeah, I have it. Have you prepared 100 doubloons, captain?"; // Addon-2016 Jason
				if(GetCharacterItem(pchar, "gold_dublon") >= 100)
				{
					link.l1 = "Sure! Here you go, as agreed.";
					link.l1.go = "Trade_artefact_4";
				}
				else
				{
					link.l1 = "Oh, I've forgotten the money on the ship! I'll bring it soon.";
					link.l1.go = "exit";
				}
			}
			else
			{
			dialog.text = "Not yet. Come see me later. And don't you worry - your amulet will surely arrive.";
			link.l1 = "Fine.";
			link.l1.go = "exit";
			}
		break;
		
		case "Trade_artefact_4":
			RemoveItems(pchar, "gold_dublon", 100); // Addon-2016 Jason
			Log_Info("You have given 100 doubloons");
			dialog.text = "Everything seems fine. Here is your amulet. Good luck with it!";
			link.l1 = "Thank you, "+npchar.name+"!";
			link.l1.go = "Trade_artefact_5";
		break;
		
		case "Trade_artefact_5":
			DialogExit();
			Log_Info("You have received "+XI_ConvertString(npchar.quest.art)+"");
			PlaySound("interface\important_item.wav");
			TakeNItems(pchar, npchar.quest.art, 1);
			DeleteAttribute(npchar, "quest.art");
			sTemp = "Amulet_"+npchar.location;
			AddQuestRecord(sTemp, "2");
			CloseQuestHeader(sTemp);
		break;
		
		// --> калеуче
		case "caleuche":
			PlaySound("interface\important_item.wav");
			dialog.text = "Show what you have there.";
			link.l1 = "Here, it looks like an ancient Indian amulet. But I have no idea how to use it or its hidden power.";
			link.l1.go = "caleuche_1";
			npchar.quest.caleuche = "true";
		break;
		
		case "caleuche_1":
			if (npchar.id == pchar.questTemp.Caleuche.Amuletmaster)
			{
				dialog.text = "Well-well. You are already the third man who shows me such thing. Buddy, this amulet was brought here from the wild selva of Southern Main. There are Indians, not far from Panama, who wear trinkets like this one. The red-skin say that this is a legacy of their 'great ancestors'\nI have no idea who were their ancestors and what kind of legacy they left. But I can give you an advice where to ask. Interested?";
				link.l1 = "Certainly!";
				link.l1.go = "caleuche_2";
			}
			else
			{
				dialog.text = "Hmm... I've held a lot of amulets in my hands, but this one I see for the first time in the Caribbean. Sorry, buddy, I cannot help you, I don't know this kind of stuff. But it is not a simple thing that's a fact. Ask somebody else, I know for sure that there are other lighthouse keepers like me who know about amulets not less.";
				link.l1 = "Pardon me... I will continue asking then.";
				link.l1.go = "exit";
			}
		break;
		
		case "caleuche_2":
			dialog.text = "There is Carib village on Dominica, local chief is named Moknitekuvri. They have a shaman named Tuttuathapak, highly respected Indian. He's not one of the Caribs, he's from that place about which I've told you already. He can tell you more about this amulet than me. But be careful - Tuttuathapak hates white people. Very hates. After all, they once enslaved him and took him away from his home...";
			link.l1 = "I take it he's got to the Caribbean that way?";
			link.l1.go = "caleuche_3";
		break;
		
		case "caleuche_3":
			dialog.text = "Yes. This is quite an interesting story. The ship, which carried Indian slaves, was trapped by a dead calm near Marie Galante and half of a crew died from sudden fever. Yet not a single Indian got ill!\nAfterwards, a captain got mad and set his vessel on fire. As a result, the imprisoned Indian started a riot and slaughtered the crew. Do you guess who was their leader?";
			link.l1 = "I do...";
			link.l1.go = "caleuche_4";
		break;
		
		case "caleuche_4":
			dialog.text = "That's it. I bet it was a spell of shaman that made the sea as calm as deadman, and infected the crew with deadly disease. This Indian is very smart and very dangerous. If you go to him - behave politely and watch your tongue - otherwise there will be a lot of troubles for you. Also, he won't even talk to you without an offering for him.";
			link.l1 = "And what kind of offering might he demand?";
			link.l1.go = "caleuche_5";
		break;
		
		case "caleuche_5":
			dialog.text = "You won't bribe him with some crap. As I know, he sends his Carib soldiers to settlements of white to buy firearm weapon. Bring him a musket as a gift and then, I think, he will be pleased and will give you a bit of his attention.";
			link.l1 = "Thank you! I'll do as you say... Say, buddy, how do you know all of this?";
			link.l1.go = "caleuche_6";
		break;
		
		case "caleuche_6":
			dialog.text = "My friend was a sailor on the ill-fated ship. Fortunately, he managed to survive in that hell... I saw on him such an amulet as yours, seems like late captain also grabbed Indian's belongings. I am sure that your amulet is from his collection - when the captain got crazy and set on fire his ship, his sailors killed him and then looted the chests in the cabin.";
			link.l1 = "Understood. Then I just have to go with a gift to Dominica. Thanks for your help and for the interesting story!";
			link.l1.go = "caleuche_7";
		break;
		
		case "caleuche_7":
			dialog.text = "Good luck, my friend, and be careful with this red-skin devil...";
			link.l1 = "...";
			link.l1.go = "caleuche_8";
		break;
		
		case "caleuche_8":
			DialogExit();
			AddQuestRecord("Caleuche", "2");
			pchar.questTemp.Caleuche = "dominica"; 
			Caleuche_CreateShamane();
		break;
		
		case "caleuche_9":
			dialog.text = "Yes? You've had a talk with Tuttuathapak, am I right?";
			link.l1 = "Exactly. And now I want to find two more amulets. You said I was the third, who showed you this artifact. And who were the other two?";
			link.l1.go = "caleuche_10";
		break;
		
		case "caleuche_10":
			dialog.text = "One is my friend, the sailor from that ship which brought Tuttuathapak to Caribbean isles. Since that incident, he hasn't laid a foot on any ship's deck. I have not seen him for a while, but I know where he lives. Look for him in the West Main, in Belize - he is a hunter and now and wanders around jungles. Name's Fergus Hooper.";
			link.l1 = "Okay. And the second?";
			link.l1.go = "caleuche_11";
		break;
		
		case "caleuche_11":
			dialog.text = "I know about the second just a bit. Whether his name is Jack, or Jackson, and whether he is a privateer, or small businessman, or simply an adventurer. He owns xebec with a strange name... hmm... her name is... Damn, I've forgotten! But the name is some kind of demonic. I asked him what it meant, and he said it was a bird-woman, born by sea gods. Pah! Godless...";
			link.l1 = "Nerd... So don't you remember her name?";
			link.l1.go = "caleuche_12";
		break;
		
		case "caleuche_12":
			dialog.text = "No, may thunder strike me, I do not remember. Oh, and when he introduced himself, he mentioned that he was from Barbados.";
			link.l1 = "That's something! Okay, I'll try to find this lover of feathered women until he will be found by someone else... Thanks, buddy, you helped me a lot!";
			link.l1.go = "caleuche_13";
		break;
		
		case "caleuche_13":
			dialog.text = "You're welcome, cap, drop by sometimes.";
			link.l1 = "Sure!";
			link.l1.go = "caleuche_14";
		break;
		
		case "caleuche_14":
			DialogExit();
			AddQuestRecord("Caleuche", "7");
			pchar.questTemp.Caleuche = "hunting"; 
			pchar.questTemp.Caleuche.Belizterms = rand(4)+3;
			pchar.quest.caleuche_prepare_beliz.win_condition.l1 = "location";
			pchar.quest.caleuche_prepare_beliz.win_condition.l1.location = "Beliz";
			pchar.quest.caleuche_prepare_beliz.function = "Caleuche_PrepareBeliz";
		break;
		
		case "fight":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_group_Attack(NPChar, Pchar);
			if (rand(3) != 1) SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "exit_setOwner":
			LAi_SetOwnerTypeNoGroup(npchar);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "Man_FackYou"://реакция на попытку залезть в сундук
			dialog.text = LinkRandPhrase("You're "+ GetSexPhrase(" a thief, my dear! Guards, seize him"," thief! Guards seize her") +"!!!", "Wow! I gazed away a little, and you're right in the chest with your head already! Hold the thief!", "Guards! Robbery! Stop the thief!");
			link.l1 = "Argh, shit!";
			link.l1.go = "fight";
		break;
	}
}
