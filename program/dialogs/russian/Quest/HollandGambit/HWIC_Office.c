// НПС офиса ГВИК
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "Want something?";
			link.l1 = "No.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		// офицер
		case "HWIC_officer":
			if (LAi_grp_playeralarm > 0)
			{
				dialog.text = "Alarm! Enemy is here! To arms!";
				link.l1 = "Damn!";
				link.l1.go = "fight";
				break;
			}
			if (ChangeCharacterHunterScore(Pchar, "holhunter", 0) > 12)
			{
				dialog.text = "Aha! I think, I know who you are... Sure! You are wanted for your crimes! Lads, seize him!";
				link.l1 = "Damn!";
				link.l1.go = "fight";
				break;
			}
			chrDisableReloadToLocation = true;
			if (CheckAttribute(pchar, "questTemp.HWIC.CanTake") && !CheckAttribute(pchar, "questTemp.HWIC.CanTake.Holl") && !CheckAttribute(pchar, "questTemp.HWIC.Eng") && !CheckAttribute(pchar, "questTemp.HWIC.Self"))
			{
				dialog.text = "Good day. What do you want?";
				link.l1 = "I am here for trading matters. Licenses, navigation instruments and so on...";
				link.l1.go = "HWIC_officer_3";
				link.l2 = "I want to offer my services to the Company. In exchange for gold of course. Are you hiring?";
				link.l2.go = "HWIC_officer_1";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.HWIC.Eng"))
			{
				dialog.text = "Good day. What do you want?";
				link.l1 = "I am sorry, it seems, that I was mistaken. I am leaving.";
				link.l1.go = "HWIC_officer_exit";
				link.l2 = "I am here for trading matters. Licenses, navigation instruments and so on...";
				link.l2.go = "HWIC_officer_3";
				break;
			}
			dialog.text = "Good day. What do you want?";
			link.l1 = "I am here for trading matters. Licenses, navigation instruments and so on...";
			link.l1.go = "HWIC_officer_3";
			link.l2 = "I want to offer my services to the Company. In exchange for gold of course. Are you hiring?";
			link.l2.go = "HWIC_officer_2";
		break;
		
		case "HWIC_officer_1":
			dialog.text = "Then go upstairs to mynheer Rodenburg's office.";
			link.l1 = "Thanks, I am on my way.";
			link.l1.go = "HWIC_officer_exit";
			LocatorReloadEnterDisable("Villemstad_houseS3", "reload2", false);//кабинет откроем
		break;
		
		case "HWIC_officer_2":
			dialog.text = "The Company is not hiring at the moment.";
			link.l1 = "Too bad. Sorry for bothering you.";
			link.l1.go = "HWIC_officer_exit";
		break;
		
		case "HWIC_officer_3":
			dialog.text = "Talk to mynheer Gerritz. His table is to the right of you. He does business with captains.";
			link.l1 = "Thank you, officer...";
			link.l1.go = "HWIC_officer_exit";
		break;
		
		case "HWIC_officer_exit":
			DialogExit();
			LAi_ActorGoToLocation(npchar, "reload", "reload3", "Villemstad_houseS3", "reload", "reload3", "", 5);
			DoQuestCheckDelay("ReturnTalkerToOfficer", 5.0); // 140313
			NextDiag.TempNode = "HWIC_officer";
		break;
		
		// солдаты
		case "HWIC_soldier":
			if (LAi_grp_playeralarm > 0)
			{
				dialog.text = "Alarm! Enemy is here! To arms!";
				link.l1 = "Damn!";
				link.l1.go = "fight";
				break;
			}
			if (ChangeCharacterHunterScore(Pchar, "holhunter", 0) > 12)
			{
				dialog.text = "Aha! I think, I know who you are... Sure! You are wanted for your crimes! Lads, take him!";
				link.l1 = "Damn!";
				link.l1.go = "fight";
				break;
			}
			dialog.text = "Speak with our officers or with mynheer Gerritz. I have nothing to say to you. I am on duty.";
			link.l1 = "Fine, I got it.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "HWIC_soldier";
		break;
		
		// клерки
		case "HWIC_clerk":
			if (LAi_grp_playeralarm > 0)
			{
				dialog.text = "Alarm! Enemy is here! Soldiers!";
				link.l1 = "Damn!";
				link.l1.go = "fight";
				break;
			}
			dialog.text = "Talk with mynheer Gerritz.";
			link.l1 = "Fine, I got it.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "HWIC_clerk";
		break;
		
		// главный клерк - минхер Герритц
		case "HWIC_headclerk":
			if (LAi_grp_playeralarm > 0)
			{
				dialog.text = "Alarm! Enemy is here! Soldiers, take him!";
				link.l1 = "Damn!";
				link.l1.go = "fight";
				break;
			}
			if (ChangeCharacterHunterScore(Pchar, "holhunter", 0) > 12)
			{
				dialog.text = "Hm. I think that there is something wrong about you... Sure! You are wanted for numerous crimes against Holland! Soldiers, take him!";
				link.l1 = "Damn!";
				link.l1.go = "fight";
				break;
			}
			dialog.text = "Want something, mynheer?";
			if (!CheckCharacterItem(pchar, "HolTradeLicence"))
			{
				link.l1 = "I want to buy a trading license of your Company.";
				link.l1.go = "licence";	
			}
			if (!CheckAttribute(npchar, "quest.trade"))
			{
				link.l2 = "I heard that it is possible to buy here navigation instruments and other useful items. Is that so?";
				link.l2.go = "trade";	
			}
			else
			{
				link.l2 = "What are you selling today? Show me.";
				link.l2.go = "trade_1";	
			}
			if (CheckCharacterItem(pchar, "Cromvel_depeshe"))
			{
				link.l3 = "I have an interesting document for you, mynheer. Read its beginning. It concerns the security of Holland. I will give it to you in case you are interested. There are coordinates of meeting. Not for free of course.";
				link.l3.go = "depeshe";	
			}
			// калеуче
			if (CheckAttribute(pchar, "questTemp.Caleuche.Garpiya") && pchar.questTemp.Caleuche.Garpiya == "gwik")
			{
				link.l4 = "A captain by the name of Reginald Jackson must be working for you. He sails on a xebec called 'Harpy'. Could you tell me how can I meet him? I have important business with him.";
				link.l4.go = "caleuche";	
			}
			link.l9 = "No, it's nothing.";
			link.l9.go = "exit";			
			NextDiag.TempNode = "HWIC_headclerk";
		break;
		
		// торговые лицензии
		case "licence":
			if (!CheckAttribute(npchar, "quest.licence"))
			{
				dialog.text = "Well, you are free to buy it. But I must warn you that the Company values its reputation, therefore it is forbidden to attack any trade ships of any nation for every owner of the license\nIf we find out that such act was committed - we will annul your license. Also, if you come into conflict with Holland no matter what reason, you will lose your document too. Are we clear?";
				link.l1 = "Absolutely. I will remember that.";
				link.l1.go = "licence_0";
				npchar.quest.licence = true;
			}
			else
			{
				dialog.text = "Well, you are welcome to buy it. For what term?";
				link.l1.edit = 6;
				link.l1 = "";	
				link.l1.go = "licence_1";
			}
		break;
		
		case "licence_0":
			dialog.text = "The license grants a free passage to any port of any nation, it shows your peaceful intentions and explains your purpose - to trade. But it won't help if you have any problems with the law. They will simply take it from you in that case. Remember that\nDon't forget to raise a friendly flag before you sail into any port, patrols and forts' cannoneers prefer to shoot first and ask later\Right, almost forgot, according to our traditions, all deals involving licenses are paid in doubloons... This is it. Let's discuss terms. For how long are you willing to use the license?";
			link.l1.edit = 6;
			link.l1 = "";	
			link.l1.go = "licence_1";
			link.l2 = "I am sorry, but I have to think a bit more about it. See you later.";	
			link.l2.go = "exit";
		break;
		
		case "licence_1":
			float fQty = stf(dialogEditStrings[6]);
			npchar.quest.lcc_summ = makeint(sqrt(fQty)*10)*7;
			if (fQty < 1)
			{
				dialog.text = "Mynheer, please, speak loud and clear. I didn't hear you properly. So for how long?";
				link.l1 = "Let me think...";
				link.l1.go = "licence_r";
				break;
			}
			if (fQty > 0 && fQty < 20)
			{
				dialog.text = "The minimum term for the license is twenty days. So? Twenty days or more?";
				link.l1 = "Let me think...";
				link.l1.go = "licence_r";
				break;
			}
			if (fQty > 180)
			{
				dialog.text = "The maximum term for the license is half a year. One hundred and eighty days or less?";
				link.l1 = "Let me think...";
				link.l1.go = "licence_r";
				break;
			}
			dialog.text = "For "+FindRussianDaysString(sti(fQty))+"? Fine. It will cost you "+FindRussianDublonString(sti(npchar.quest.lcc_summ))+". Are you fine with that?";
			if (GetCharacterItem(pchar, "gold_dublon") >= sti(npchar.quest.lcc_summ))
			{
				link.l1 = "Sure, I am.";
				link.l1.go = "licence_2";
			}
			link.l2 = "Unfortunately, I don't have that much money with me now. I will be back for the license later.";
			link.l2.go = "exit";
		break;
		
		case "licence_r":
			dialog.text = "";
			link.l1.edit = 6;
			link.l1 = "";	
			link.l1.go = "licence_1";
			link.l2 = "I am sorry, but I still need to think about it. I will see you later.";	
			link.l2.go = "exit";
		break;
		
		case "licence_2":
			int iQty = sti(dialogEditStrings[6]);
			RemoveItems(pchar, "gold_dublon", sti(npchar.quest.lcc_summ));
			GiveNationLicence(HOLLAND, iQty);
			dialog.text = "So, wait a minute... Let us put a sign and a stamp here... Done. Take your document.";
			link.l1 = "Thanks! Goodbye, mynheer.";
			link.l1.go = "exit";
		break;
		
		case "trade":
			dialog.text = "We sell such things. You can buy navigation tools here, such as: compasses, astrolabes, chronometers and sand glasses. But we don't always have a full stock ready to buy. Except sand glasses, perhaps. They buy out other tools really quickly. So if you failed to find what you need - see us again in a week\nWe also sell maps and spyglasses. Want to see what we have to offer now?";
			link.l1 = "Yes, please.";
			link.l1.go = "trade_1";
			npchar.quest.trade = "true";
		break;
		
		case "trade_1":
			DialogExit();
			if (!CheckAttribute(npchar, "trade_date") || GetNpcQuestPastDayParam(npchar, "trade_date") >= 7)
			{
				GiveItemToTrader(npchar);
				SaveCurrentNpcQuestDateParam(npchar, "trade_date");
			}
			LaunchItemsTrade(npchar, 0);
		break;
		
		// депеша Кромвеля
		case "depeshe":
			dialog.text = "Hm, show me...(reading) Well, well... Cromwell's appetites in his best. Bastards! Isn't it enough for them what they did in England!? Where did you get this dispatch?";
			link.l1 = "I took it from one English courier. So would you like to buy it?";
			link.l1.go = "depeshe_1";
		break;
		
		case "depeshe_1":
			dialog.text = "Yes. Peter Stuyvesant will be really glad to read it, I am sure. And he will take effective measures... I can pay for it with gold or I can make you our license for a half a year term. What will you choose?";
			link.l1 = "I choose gold.";
			link.l1.go = "depeshe_dublon";
			link.l2 = "I want the license.";
			link.l2.go = "depeshe_licence";
		break;
		
		case "depeshe_dublon":
			TakeNItems(pchar, "gold_dublon", 700);
			Log_Info("You have received 700 doubloons");
			dialog.text = "Fine. Here are your seven hundred doubloons. I can't pay you more anyway.";
			link.l1 = "Here is your dispatch.";
			link.l1.go = "depeshe_exit";
		break;
		
		case "depeshe_licence":
			if (CheckCharacterItem(pchar, "HolTradeLicence")) TakeNationLicence(HOLLAND);
			GiveNationLicence(HOLLAND, 180);
			dialog.text = "Good. Here is your license for a half a year term.";
			link.l1 = "Thanks! And here is your dispatch.";
			link.l1.go = "depeshe_exit";
		break;
		
		case "depeshe_exit":
			RemoveItems(pchar, "Cromvel_depeshe", 1);
			pchar.quest.Terrapin_CromvelScuadron.over = "yes"; //снять прерывание
			ChangeCharacterNationReputation(pchar, HOLLAND, 15);
			ChangeCharacterComplexReputation(pchar, "authority", 3);
			ChangeCharacterComplexReputation(pchar, "nobility", 2);
			dialog.text = "Gratitude. It is good that you have shown your consciousness and loyalty to Holland. I will tell Matthias Beck and Peter Stuyvesant about your good deed.";
			link.l1 = "Good to know. Goodbye!";
			link.l1.go = "exit";
		break;
		
		// калеуче
		case "caleuche":
			dialog.text = "Mynheer Reginald Jackson is performing regular shipping operations between Port Royal and Philipsburg. Look for him on that route. But I must warn you in advance - if you're brewing trouble, you'd better not, because that captain is under our protection. I hope we have understood each other, mynheer?";
			link.l1 = "I just have business with him. A common trade. I don't mean to hurt him in absolutely any way.";
			link.l1.go = "caleuche_1";
		break;
		
		case "caleuche_1":
			dialog.text = "Excellent. Mynheer Jackson usually doesn't stay for long neither in Port Royal, nor in Philipsburg. After his ship is unloaded and loaded again, he usually sets sail at once. So I guess you'd have better luck meeting him at the sea.";
			link.l1 = "Thank you!";
			link.l1.go = "caleuche_2";
		break;
		
		case "caleuche_2":
			DialogExit();
			pchar.questTemp.Caleuche.Garpiya = "capitan";
			pchar.questTemp.Garpiya = "to_portroyal";
			AddQuestRecord("Caleuche", "19");
			DoQuestFunctionDelay("Caleuche_CreateGarpiyaInWorld", 1.0);
		break;
		
		// новый босс ГВИК
		case "HWIC_Boss":
			if (!CheckAttribute(npchar, "quest.silk_info") && sti(pchar.reputation.nobility) > 60)
			{
				dialog.text = "Aha, captain " + GetFullName(pchar) + "! It is good that you came here. I have a business proposal for you.";
				link.l1 = "Interesting! I am listening to you, mynheer.";
				link.l1.go = "silk_info";
				break;
			}
			dialog.text = "Good day, captain " + GetFullName(pchar) + "! How can I be of service?";
			if(CheckAttribute(npchar, "quest.silk")) // торговля шелком
			{
				if (GetDataDay() == 1 || GetDataDay() == 15)
				{
					link.l1 = "About that ship silk...";
					link.l1.go = "trade_silk";
				}
			}
			link.l2 = "Good day. No, I don't need anything, just wanted to greet you.";
			link.l2.go = "exit";			
			NextDiag.TempNode = "HWIC_Boss";
		break;
		
		case "silk_info":
			dialog.text = "I have recently established trading connections with one merchant from Lyons and had a deal with him about supplying to the Caribbean with ship silk. Do you know about it? The very best sails in the world are made from this silk, so you must be interested.";
			link.l1 = "Agreed, that is an interesting proposal. What are your terms?";
			link.l1.go = "silk_info_1";
		break;
		
		case "silk_info_1":
			dialog.text = "Small but regular supplies. I can save thirty rolls for you every two weeks. The cost of one roll is twenty doubloons. Let's make it this way: I will save thirty rolls for you every first and fifteenth day of month. If you don't come for them then, I sell rolls to another customer.";
			link.l1 = "No obligations then?";
			link.l1.go = "silk_info_2";
		break;
		
		case "silk_info_2":
			dialog.text = "Exactly! Buy the silk if you want. You pay for the whole batch - six hundred doubloons. I hope that you will be my regular customer.";
			link.l1 = "Thanks for your proposal, mynheer. Deal.";
			link.l1.go = "exit";
			NextDiag.TempNode = "HWIC_Boss";
			npchar.quest.silk_info = "true";
			npchar.quest.silk = "true";
			AddQuestRecord("Unique_Goods", "3");
		break;
		
		// торговля шелком
		case "trade_silk":
			dialog.text = "Sure, captain. Your silk is waiting for you. Are you ready to pay for it?";
			if (GetCharacterItem(pchar, "gold_dublon") >= 600)
			{
				link.l1 = "Sure! Here, take six hundred of doubloons.";
				link.l1.go = "trade_silk_1";
			}
			else
			{
				link.l1 = "Such a bad luck, I have forgotten money on my ship. I will bring it in a second!";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "HWIC_Boss";
		break;
		
		case "trade_silk_1":
			RemoveItems(pchar, "gold_dublon", 600);
			Log_Info("You have given 600 doubloons");
			PlaySound("interface\important_item.wav");
			dialog.text = "Pleasure doing business with you, captain. Your silk will be delivered to your ship on barque.";
			link.l1 = "Thanks!";
			link.l1.go = "trade_silk_2";
		break;
		
		case "trade_silk_2":
			dialog.text = "I hope to see you soon. Come back again.";
			link.l1 = "Sure. See you!";
			link.l1.go = "exit";
			AddCharacterGoods(pchar, GOOD_SHIPSILK, 30);
			DeleteAttribute(npchar, "quest.silk");
			SetFunctionTimerCondition("Silk_TraderAttrReturn", 0, 0, 1, false); // таймер
			AddCharacterExpToSkill(pchar, "Commerce", 150);
			NextDiag.TempNode = "HWIC_Boss";
		break;
		
		case "fight":
			DialogExit();
			sld = characterFromId("HWIC_officer");
			LAi_SetGuardianTypeNoGroup(sld);
			LAi_group_Attack(sld, Pchar);
			for (i=1; i<=6; i++)
			{	
				sld = characterFromId("HWIC_sold_"+i);
				LAi_group_Attack(sld, Pchar);
			}
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
