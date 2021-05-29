//Jason диалог индейцев в джунглях
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;
	int iQty;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = NPCStringReactionRepeat(""+ GetSexPhrase("Paleface","White squaw") +" wants to talk?", 
				"You again, "+ GetSexPhrase("paleface","white squaw") +".", 
				""+ GetSexPhrase("Paleface likes talking. He looks like squaw.","White squaw likes talking.") +"",
                "Spirits brought me paleface "+ GetSexPhrase("brother.","sister") +".", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Yes.", 
				"Yea, me again.",
                "Very poetic.", 
				"I am also glad to see you.", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "Hail, white brother. You want speak with Indian?";
				link.l1 = "Greetings, son of the jungle. I am glad to meet you, but I must continue my journey.";
				link.l1.go = "exit";
				link.l2 = "Yes. I've heard that you sell interesting things. Do you have anything for sale?";
				link.l2.go = "select_trade";
				npchar.quest.meeting = "1";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "select_trade": //индейская торговля
			switch (drand(7))
			{
				case 0: // торговля через интерфейс
					dialog.text = "You are in luck, white brother. "+npchar.name+" has some stuff for sale. Look here.";
					link.l1 = "Show your goods...";
					link.l1.go = "torg";
					if (CheckCharacterItem(pchar, "cannabis7") && CheckAttribute(pchar, "questTemp.Mangarosa") && !CheckAttribute(npchar, "quest.mangarosa"))
					{
						if (pchar.questTemp.Mangarosa == "gipsy" || pchar.questTemp.Mangarosa == "gipsy_trade")
						{
							link.l9 = "Hold on. I have something for sale. It's a plant called Mangarosa. I heard that you're fond of this stuff...";
							link.l9.go = "mangarosa";
						}
					}
				break;
				
				case 1: // не торгует
					dialog.text = "No, white brother. "+npchar.name+" doesn't trade. "+npchar.name+"  is a warrior.";
					link.l1 = "I see. Alright, farewell, red-skinned brother.";
					link.l1.go = "exit";
				break;
				
				case 2: // жемчуг большой
					npchar.quest.item.qty = 25+drand(25);
					npchar.quest.item.price = 30+drand(10);
					dialog.text = ""+npchar.name+" has tears of gods. Big ones, white brother. In the amount of "+FindRussianQtyString(sti(npchar.quest.item.qty))+". You want buy them? I sell for "+FindRussianMoneyString(sti(npchar.quest.item.price))+" for one.";
					link.l1 = "No, I am not interested.";
					link.l1.go = "exit";
					link.l2 = "Of course! I'll gladly buy them for such price.";
					link.l2.go = "big_pearl";
					if (CheckCharacterItem(pchar, "cannabis7") && CheckAttribute(pchar, "questTemp.Mangarosa") && !CheckAttribute(npchar, "quest.mangarosa"))
					{
						if (pchar.questTemp.Mangarosa == "gipsy" || pchar.questTemp.Mangarosa == "gipsy_trade")
						{
							link.l9 = "Hold on. I have something for sale. It's a plant called Mangarosa. I heard that you're fond of this stuff...";
							link.l9.go = "mangarosa";
						}
					}
				break;
				
				case 3: // жемчуг малый
					npchar.quest.item.qty = 40+drand(40);
					npchar.quest.item.price = 10+drand(5);
					dialog.text = ""+npchar.name+" has tears of gods. Small ones, white brother. In the amount of "+FindRussianQtyString(sti(npchar.quest.item.qty))+". You want buy them? I sell for "+FindRussianMoneyString(sti(npchar.quest.item.price))+" for one.";
					link.l1 = "No, I am not interested.";
					link.l1.go = "exit";
					link.l2 = "Of course! I'll gladly buy them for such price.";
					link.l2.go = "small_pearl";
					if (CheckCharacterItem(pchar, "cannabis7") && CheckAttribute(pchar, "questTemp.Mangarosa") && !CheckAttribute(npchar, "quest.mangarosa"))
					{
						if (pchar.questTemp.Mangarosa == "gipsy" || pchar.questTemp.Mangarosa == "gipsy_trade")
						{
							link.l9 = "Hold on. I have something for sale. It's a plant called Mangarosa. I heard that you're fond of this stuff...";
							link.l9.go = "mangarosa";
						}
					}
				break;
				
				case 4: //золотые самородки
					npchar.quest.item.qty = 20+drand(20);
					npchar.quest.item.price = 90+drand(20);
					dialog.text = ""+npchar.name+" has yellow metal that you palefaces love a lot. In the amount of "+FindRussianQtyString(sti(npchar.quest.item.qty))+". I sell just for "+FindRussianMoneyString(sti(npchar.quest.item.price))+" for one.";
					link.l1 = "No, I am not interested.";
					link.l1.go = "exit";
					link.l2 = "Of course! I'll gladly buy them for such price.";
					link.l2.go = "gold";
					if (CheckCharacterItem(pchar, "cannabis7") && CheckAttribute(pchar, "questTemp.Mangarosa") && !CheckAttribute(npchar, "quest.mangarosa"))
					{
						if (pchar.questTemp.Mangarosa == "gipsy" || pchar.questTemp.Mangarosa == "gipsy_trade")
						{
							link.l9 = "Hold on. I have something for sale. It's a plant called Mangarosa. I heard that you're fond of this stuff...";
							link.l9.go = "mangarosa";
						}
					}
				break;
				
				case 5: // серебряные самородки
					npchar.quest.item.qty = 40+drand(40);
					npchar.quest.item.price = 40+drand(10);
					dialog.text = ""+npchar.name+" has white metal that you palefaces love a lot. In the amount of "+FindRussianQtyString(sti(npchar.quest.item.qty))+". I sell just for "+FindRussianMoneyString(sti(npchar.quest.item.price))+" for one.";
					link.l1 = "No, I am not interested.";
					link.l1.go = "exit";
					link.l2 = "Of course! I'll gladly buy them for such price.";
					link.l2.go = "silver";
					if (CheckCharacterItem(pchar, "cannabis7") && CheckAttribute(pchar, "questTemp.Mangarosa") && !CheckAttribute(npchar, "quest.mangarosa"))
					{
						if (pchar.questTemp.Mangarosa == "gipsy" || pchar.questTemp.Mangarosa == "gipsy_trade")
						{
							link.l9 = "Hold on. I have something for sale. It's a plant called Mangarosa. I heard that you're fond of this stuff...";
							link.l9.go = "mangarosa";
						}
					}
				break;
				
				case 6: // повтор через интерфейс
					dialog.text = "You are in luck, white brother. "+npchar.name+" has some stuff for sale. Look here.";
					link.l1 = "Show your goods...";
					link.l1.go = "torg";
					if (CheckCharacterItem(pchar, "cannabis7") && CheckAttribute(pchar, "questTemp.Mangarosa") && !CheckAttribute(npchar, "quest.mangarosa"))
					{
						if (pchar.questTemp.Mangarosa == "gipsy" || pchar.questTemp.Mangarosa == "gipsy_trade")
						{
							link.l9 = "Hold on. I have something for sale. It's a plant called Mangarosa. I heard that you're fond of this stuff...";
							link.l9.go = "mangarosa";
						}
					}
				break;
				
				case 7: // повтор не торгует
					dialog.text = "No, white brother. "+npchar.name+"  doesn't trade. "+npchar.name+" -  is a warrior.";
					link.l1 = "I see. Alright, farewell, red-skinned brother.";
					link.l1.go = "exit";
				break;
			}
		break;
		
		case "torg":
			DialogExit();
			if (CheckNPCQuestDate(npchar, "Torg_date"))
			{
                SetNPCQuestDate(npchar, "Torg_date");
				GiveItemToTrader(npchar);
			}
			NextDiag.CurrentNode = "First time";
			LaunchItemsTrade(NPChar, 0);
			ChangeIndianRelation(0.25);
		break;
		
		// большой жемчуг
		case "big_pearl":
			dialog.text = "How many tears you want buy?";
			link.l1 = "";
			Link.l1.edit = 4;
			link.l1.go = "big_pearl_qty";
		break;
		
		case "big_pearl_qty":
			iQty = sti(dialogEditStrings[4]);
			npchar.quest.item.Byeqty = iQty;
			if (iQty < 1)
			{
				dialog.text = "You joke, paleface? You need no tears of gods? Then bye.";
				link.l1 = "Hmm...";
				link.l1.go = "exit";
				break;
			}
			if (iQty > sti(npchar.quest.item.qty))
			{
				dialog.text = "I told you how many tears I have. You joke with Indian, paleface? Then bye.";
				link.l1 = "Hmm...";
				link.l1.go = "exit";
				break;
			}
			npchar.quest.item.Summ = iQty*sti(npchar.quest.item.price);
			dialog.text = ""+iQty+" tears? Alright. You give me " + FindRussianMoneyString(sti(npchar.quest.item.Summ))", white brother.";
			if (sti(Pchar.money) >= sti(npchar.quest.item.Summ))
			{
				link.l1 = "Here is your money, red-skinned brother.";
				link.l1.go = "big_pearl_1";
			}
			link.l2 = "I don't have enough money right now. I am sorry, I cannot buy your pearls.";
			link.l2.go = "exit";
		break;
		
		case "big_pearl_1":
			AddMoneyToCharacter(pchar, -sti(npchar.quest.item.Summ));
			TakeNItems(pchar, "jewelry52", sti(npchar.quest.item.Byeqty));
			PlaySound("interface\important_item.wav");
			dialog.text = "Take them, white brother. They yours now.";
			link.l1 = "Thanks!";
			link.l1.go = "exit";
			ChangeIndianRelation(0.5);
		break;
		
		// малый жемчуг
		case "small_pearl":
			dialog.text = "How many tears you want buy?";
			link.l1 = "";
			Link.l1.edit = 4;
			link.l1.go = "small_pearl_qty";
		break;
		
		case "small_pearl_qty":
			iQty = sti(dialogEditStrings[4]);
			npchar.quest.item.Byeqty = iQty;
			if (iQty < 1)
			{
				dialog.text = "You joke, paleface? You need no tears of gods? Then bye.";
				link.l1 = "Hmm...";
				link.l1.go = "exit";
				break;
			}
			if (iQty > sti(npchar.quest.item.qty))
			{
				dialog.text = "I told you how many tears I have. You joke with Indian, paleface? Then bye.";
				link.l1 = "Hmm...";
				link.l1.go = "exit";
				break;
			}
			npchar.quest.item.Summ = iQty*sti(npchar.quest.item.price);
			dialog.text = ""+iQty+" tears? Alright. You give me " + FindRussianMoneyString(sti(npchar.quest.item.Summ))", white brother.";
			if (sti(Pchar.money) >= sti(npchar.quest.item.Summ))
			{
				link.l1 = "Here is your money, red-skinned brother.";
				link.l1.go = "small_pearl_1";
			}
			link.l2 = "I don't have enough money right now. I am sorry, I cannot buy your pearls.";
			link.l2.go = "exit";
		break;
		
		case "small_pearl_1":
			AddMoneyToCharacter(pchar, -sti(npchar.quest.item.Summ));
			TakeNItems(pchar, "jewelry53", sti(npchar.quest.item.Byeqty));
			PlaySound("interface\important_item.wav");
			dialog.text = "Take them, white brother. They yours now.";
			link.l1 = "Thanks!";
			link.l1.go = "exit";
			ChangeIndianRelation(0.5);
		break;
		
		// золотые самородки
		case "gold":
			dialog.text = "How many you want buy?";
			link.l1 = "";
			Link.l1.edit = 4;
			link.l1.go = "gold_qty";
		break;
		
		case "gold_qty":
			iQty = sti(dialogEditStrings[4]);
			npchar.quest.item.Byeqty = iQty;
			if (iQty < 1)
			{
				dialog.text = "You joke, paleface? You need no metal? Then bye.";
				link.l1 = "Hmm...";
				link.l1.go = "exit";
				break;
			}
			if (iQty > sti(npchar.quest.item.qty))
			{
				dialog.text = "I told you how many I have. You joke with Indian, paleface? Then bye.";
				link.l1 = "Hmm...";
				link.l1.go = "exit";
				break;
			}
			npchar.quest.item.Summ = iQty*sti(npchar.quest.item.price);
			dialog.text = ""+iQty+" chunks? Well, from you " + FindRussianMoneyString(sti(npchar.quest.item.Summ))", white brother.";
			if (sti(Pchar.money) >= sti(npchar.quest.item.Summ))
			{
				link.l1 = "Here is your money, red-skinned brother.";
				link.l1.go = "gold_1";
			}
			link.l2 = "I don't have enough money right now. I am sorry, I cannot buy your gold.";
			link.l2.go = "exit";
		break;
		
		case "gold_1":
			AddMoneyToCharacter(pchar, -sti(npchar.quest.item.Summ));
			TakeNItems(pchar, "jewelry5", sti(npchar.quest.item.Byeqty));
			PlaySound("interface\important_item.wav");
			dialog.text = "Take them, white brother. They yours now.";
			link.l1 = "Thanks!";
			link.l1.go = "exit";
			ChangeIndianRelation(0.5);
		break;
		
		// серебряные самородки
		case "silver":
			dialog.text = "How many you want buy?";
			link.l1 = "";
			Link.l1.edit = 4;
			link.l1.go = "silver_qty";
		break;
		
		case "silver_qty":
			iQty = sti(dialogEditStrings[4]);
			npchar.quest.item.Byeqty = iQty;
			if (iQty < 1)
			{
				dialog.text = "You joke, paleface? You need no metal? Then bye.";
				link.l1 = "Hmm...";
				link.l1.go = "exit";
				break;
			}
			if (iQty > sti(npchar.quest.item.qty))
			{
				dialog.text = "I told you how many I have. You joke with Indian, paleface? Then bye.";
				link.l1 = "Hmm...";
				link.l1.go = "exit";
				break;
			}
			npchar.quest.item.Summ = iQty*sti(npchar.quest.item.price);
			dialog.text = ""+iQty+" chunks? Well, from you " + FindRussianMoneyString(sti(npchar.quest.item.Summ))", white brother.";
			if (sti(Pchar.money) >= sti(npchar.quest.item.Summ))
			{
				link.l1 = "Here is your money, red-skinned brother.";
				link.l1.go = "silver_1";
			}
			link.l2 = "I don't have enough money right now. I am sorry, I cannot buy your silver.";
			link.l2.go = "exit";
		break;
		
		case "silver_1":
			AddMoneyToCharacter(pchar, -sti(npchar.quest.item.Summ));
			TakeNItems(pchar, "jewelry6", sti(npchar.quest.item.Byeqty));
			PlaySound("interface\important_item.wav");
			dialog.text = "Take them, white brother. They yours now.";
			link.l1 = "Thanks!";
			link.l1.go = "exit";
			ChangeIndianRelation(0.5);
		break;
		
		// мангароса
		case "mangarosa":
			dialog.text = "Mangarosa? I want see it.";
			link.l1 = "Here, take a look...";
			link.l1.go = "mangarosa_1";
		break;
		
		case "mangarosa_1":
			npchar.quest.mangarosa = "indian_"+(drand(10)+1);
			dialog.text = "Yes. This is one name it has - Mangarosa. I give you amulet for it. Very good amulet, it has name - "+XI_ConvertString(npchar.quest.mangarosa)+". You trade?";
			link.l1 = "Listen, red-skinned brother, I would like to learn more about this plant. Will you tell me why do you need it so much?";
			link.l1.go = "mangarosa_2";
		break;
		
		case "mangarosa_2":
			dialog.text = ""+npchar.name+" not understand. If you want trade, I give you amulet for Mangarosa. If no, then I go.";
			link.l1 = "Oh, well. Let's trade.";
			link.l1.go = "mangarosa_3";
			link.l2 = "No. I will not give away this plant for an amulet.";
			link.l2.go = "exit";
		break;
		
		case "mangarosa_3":
			Log_Info("You have received an amulet");
			GiveItem2Character(pchar, npchar.quest.mangarosa);
			RemoveItems(pchar, "cannabis7", 1);
			dialog.text = "Take your "+XI_ConvertString(npchar.quest.mangarosa)+". It be useful.";
			link.l1 = "No doubt about it. Best of luck to you, red-skinned friend.";
			link.l1.go = "exit";
			ChangeIndianRelation(0.5);
		break;
		
		//замечание по обнаженному оружию от персонажей типа citizen
		case "CitizenNotBlade":
			dialog.text = NPCharSexPhrase(NPChar, "You not tempt fate, paleface! Put away your sword!", "Listen paleface, hide your weapon and let us talk, I need no problems.");
			link.l1 = LinkRandPhrase("Fine.", "Okay.", "As you say...");
			link.l1.go = "exit";
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
