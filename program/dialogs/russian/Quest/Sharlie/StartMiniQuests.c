
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	bool bOk;
	int i;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "What do you want?";
			link.l1 = "No, nothing.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		//Найти помощника в магазин
		case "Storehelper":
			dialog.text = "Is there anything you need, monsieur?";
			link.l1 = "Are you Gralam Lavoie. Am I correct?";
			link.l1.go = "Storehelper_1";
		break;
		
		case "Storehelper_1":
			dialog.text = "Yes. Why are you asking? Don't bother me while I'm drinking rum, sir. I'm not in the mood for conversation.";
			link.l1 = "I won't take much of your time. I've been sent here by a merchant from St.Pierre. You were his employee. He's searching for you and...";
			link.l1.go = "Storehelper_2";
		break;
		
		case "Storehelper_2":
			dialog.text = "Ha, searching for me! Fucking scrooge! Did he really think that I would spend my whole life working for such little coin? He is the greediest merchant in the Caribbean! I had been working for him restless for five years and he never paid me even a smallest bonus, never bought a drink!\nHe may count his wares himself now, I had enough. No one in Saint-Pierre will work for the skinflint, oh, I know that. He has only one concern - earn more and pay less.";
			link.l1 = "So I take it you're not going back to work in his store?";
			link.l1.go = "Storehelper_3";
		break;
		
		case "Storehelper_3":
			dialog.text = "No, strike me dead! I'll wait here in Le Francois for some ship to arrive and I'll enlist in a crew as purser, and if it doesn't work out then position of a common sailor will do just fine. I can't even bare to set my eyes on that money grubber...";
			link.l1 = "I understand. That's all I needed to know. Good luck, Gralam!";
			link.l1.go = "Storehelper_12";
		break;
		
		case "Storehelper_4":
			dialog.text = "Sir, step aside. You're in my way!";
			link.l1 = "Just one question, monsieur. Are you Gralam Lavoie?";
			link.l1.go = "Storehelper_5";
		break;
		
		case "Storehelper_5":
			dialog.text = "Ha! Yeah, it's me. What do you want?";
			link.l1 = "You're being searched by a merchant from St. Pierre. You used to work for him, didn't you?";
			link.l1.go = "Storehelper_6";
		break;
		
		case "Storehelper_6":
			dialog.text = "Ha-ha! And what does he need from me? Has he decided to pay me my missing salary for my last two weeks of work? Or is he having troubles counting his barrels and fooling his customers at the same time, huh? Ha-ha-ha!";
			link.l1 = "He asked me to look for you and to clarify why you aren't coming to his store to work any more.";
			link.l1.go = "Storehelper_7";
		break;
		
		case "Storehelper_7":
			dialog.text = "Why? Because he is a fucking scrooge! A miser, the one of the thousand! I am a part of the Brethren of the Coast now and I am really enjoying myself, damn it!\nSoon I will set sail and count pesos and doubloons taken from the Spanish instead of crates of bananas! And about that skinflint - I doubt that he will find anyone to replace me. No one in Saint-Pierre is stupid enough to work for him, his reputation smells way too bad, ha-ha!";
			link.l1 = "I understand. That's all I needed to know. Good luck, Gralam!";
			link.l1.go = "Storehelper_12";
		break;
		
		case "Storehelper_8":
			dialog.text = "How can I help you?";
			link.l1 = "Good afternoon. Gralam Lavoie, I presume?";
			link.l1.go = "Storehelper_9";
		break;
		
		case "Storehelper_9":
			dialog.text = "Yes. What do you want, monsieur?";
			link.l1 = "You're being searched by a merchant from Saint-Pierre. You used to work for him, didn't you?";
			link.l1.go = "Storehelper_10";
		break;
		
		case "Storehelper_10":
			dialog.text = "Well, let him keep on searching. I don't owe him anything. He's the one still indebted to me for two weeks of service, but I'm not even going to try praying my money from him. I hope he gags.";
			link.l1 = "Hm. So you've left him for good, I take it?";
			link.l1.go = "Storehelper_11";
		break;
		
		case "Storehelper_11":
			dialog.text = "You got everything right, serah. My ex employer is a rare specimen of scrooges. I work here now and my talents are well evaluated. I get twice as much, plus bonuses\nI doubt that the miser will find anyone to replace me. His greed is well-known to the people of Saint-Pierre, no one there is stupid enough to work for him.";
			link.l1 = "I got it. That's all I needed to know. Good luck, Gralam!";
			link.l1.go = "Storehelper_12";
		break;
		
		case "Storehelper_12":
			DialogExit();
			npchar.lifeday = 0;
			AddQuestRecord("SharlieA", "2");
			pchar.questTemp.Sharlie.Storehelper = "return";
			LAi_CharacterDisableDialog(npchar);
			pchar.quest.StorehelperOver.over = "yes"; //снять таймер
		break;
		
		case "Newstorehelper_1":
			dialog.text = "Hello, monsieur. I don't mean to be cocky, but I believe that my candidacy will be quite a fit for the position you are offering.";
			link.l1 = "Good afternoon. And why do you suppose that?";
			link.l1.go = "Newstorehelper_1_1";
		break;
		
		case "Newstorehelper_2":
			dialog.text = "Greetings, sir! Allow me to tell you a little bit about myself.";
			link.l1 = "I'm all ears.";
			link.l1.go = "Newstorehelper_2_1";
		break;
		
		case "Newstorehelper_3":
			dialog.text = "Good health to you, dear sir. Are you offering a merchant vacancy?";
			link.l1 = "Yes, I am. What can you tell me about yourself?";
			link.l1.go = "Newstorehelper_3_1";
		break;
		
		case "Newstorehelper_1_1":
			dialog.text = "Because I had served as a quartermaster under the command of Francis Dubois himself. He was quite pleased with me. I was injured, so I had to leave the service - a treatment took long, I am fine now, completely healthy, but the only thought of rolling makes me sick. No, I want to stay on the solid earth\n(whispering) And if you choose me, I will pay five hundred pesos and twenty five golden doubloons extra.";
			link.l1 = "I see. I'll think about it.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Newstorehelper_1_2";
		break;
		
		case "Newstorehelper_2_1":
			dialog.text = "I used to be a petty trader, but got broken and went to the sea. Was serving as a purser on a trade ship. Fate has brought me to this village. I didn't like the sailor's life much anyway, and I'd be glad to accept your offer\n(whispering) And if you choose me, I will give you not only five hundred pesos, but also this heavy packet of amber.";
			link.l1 = "I see. I'll think about it.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Newstorehelper_2_2";
		break;
		
		case "Newstorehelper_3_1":
			dialog.text = "I had been working as a clerk in one of warehouses of Glasgow's port. I came to the Caribbean in search of wealth and I managed to earn enough money to live through my old age with dignity. But I got tired of sea voyages and I'd like to live a calm life on the shore close to the sea\n(whispering) And if you choose me, I will give you in addition to five hundred pesos five times of five hundred extra.";
			link.l1 = "I see. I'll think about it.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Newstorehelper_3_2";
		break;
		
		case "Newstorehelper_1_2":
			dialog.text = "Monsieur, make the right choice. And don't forget about doubloons...";
			link.l1 = "I have decided in your favor. Get yourself together. We're going to Saint-Pierre.";
			link.l1.go = "Newstorehelper_1_3";
			link.l2 = "I still haven't decided yet...";
			link.l2.go = "exit";
			NextDiag.TempNode = "Newstorehelper_1_2";
		break;
		
		case "Newstorehelper_2_2":
			dialog.text = "I hope your decision falls onto my candidacy. And amber is also quite a valuable, useful thing...";
			link.l1 = "I have decided in your favor. Get yourself together. We're going to Saint-Pierre.";
			link.l1.go = "Newstorehelper_2_3";
			link.l2 = "I still haven't decided yet...";
			link.l2.go = "exit";
			NextDiag.TempNode = "Newstorehelper_2_2";
		break;
		
		case "Newstorehelper_3_2":
			dialog.text = "The merchant will not be disappointed by my work. And don't forget about your bonus.";
			link.l1 = "I have decided in your favor. Get yourself together. We're going to Saint-Pierre.";
			link.l1.go = "Newstorehelper_3_3";
			link.l2 = "I still haven't decided yet...";
			link.l2.go = "exit";
			NextDiag.TempNode = "Newstorehelper_3_2";
		break;
		
		case "Newstorehelper_1_3":
			dialog.text = "Just let me put my things together! I'll be waiting for you at the entrance of the tavern.";
			link.l1 = "...";
			link.l1.go = "Newstorehelper_exit";
			pchar.questTemp.Sharlie.Storehelper.Quality = 0;
		break;
		
		case "Newstorehelper_2_3":
			dialog.text = "I'll be right there in a moment, monsieur! I'll be waiting for you at the entrance of the tavern.";
			link.l1 = "...";
			link.l1.go = "Newstorehelper_exit";
			pchar.questTemp.Sharlie.Storehelper.Quality = 1;
		break;
		
		case "Newstorehelper_3_3":
			dialog.text = "I'll get my old valise and I'll be waiting for you at the entrance to the tavern, sir!";
			link.l1 = "...";
			link.l1.go = "Newstorehelper_exit";
			pchar.questTemp.Sharlie.Storehelper.Quality = 2;
		break;
		
		case "Newstorehelper_exit":
			DialogExit();
			chrDisableReloadToLocation = false;//открыть локацию
			pchar.questTemp.Sharlie.Storehelper.id = npchar.id;
			DeleteAttribute(npchar, "LifeDay")
			chrDisableReloadToLocation = true;
			for (i=1; i<=3; i++)
			{
				sld = characterFromId("Newstorehelper_"+i);
				LAi_SetActorType(sld);
				LAi_ActorGoToLocation(sld, "reload", "reload1_back", "none", "", "", "OpenTheDoors", 10.0);
			}
			pchar.quest.storehelper2.win_condition.l1 = "location";
			pchar.quest.storehelper2.win_condition.l1.location = "LeFransua_town";
			pchar.quest.storehelper2.function = "NewstorehelperAdd";
			AddQuestRecord("SharlieA", "4");
			pchar.questTemp.Sharlie.Storehelper = "choise";
			pchar.quest.storehelper.over = "yes"; //снять прерывание
		break;
		
		case "Newstorehelper_regard":
			dialog.text = "Well, I take it this is where I work since now? Thank you, monsieur, for choosing me. Here are your five hundred pesos and the bonus on top as promised.";
			link.l1 = "My gratitude... Let me introduce you to your employer.";
			link.l1.go = "Newstorehelper_regard_1";
		break;
		
		case "Newstorehelper_regard_1":
			DialogExit();
			npchar.lifeday = 0;
			switch (sti(pchar.questTemp.Sharlie.Storehelper.Quality))
			{
				case 0:
					AddMoneyToCharacter(pchar, 500);
					TakeNItems(pchar, "gold_dublon", 25);
				break;
				
				case 1:
					AddMoneyToCharacter(pchar, 500);
					TakeNItems(pchar, "jewelry8", 10);
					TakeNItems(pchar, "jewelry7", 1);
				break;
				
				case 2:
					AddMoneyToCharacter(pchar, 3000);
				break;
			}
		break;
		
		//контрабанда рома
		case "Rum_Cap_Over":
			dialog.text = "Monsieur, I ask you to leave my ship immediately. I am rising my anchor and drifting off any minute!";
			link.l1 = "Okay...";
			link.l1.go = "exit";
			NextDiag.TempNode = "Rum_Cap_Over";
			chrDisableReloadToLocation = false;
			npchar.DontDeskTalk = true;
			LAi_LocationFightDisable(&Locations[FindLocation("Deck_Near_Ship")], false);
		break;
		
		case "Rum_Cap":
			pchar.quest.Sharlie_rum2.over = "yes"; //снять таймер
			chrDisableReloadToLocation = false; // patch-4
			dialog.text = "Well? Who are you, buddy?";
			link.l1.edit = 1;			
			link.l1 = "";
			link.l1.go = "Rum_Cap_1";
		break;
		
		case "Rum_Cap_1":
			if(GetStrSmallRegister(pchar.questTemp.Sharlie.Rum.Pass) == GetStrSmallRegister(dialogEditStrings[1]))
			{
				dialog.text = "Have a sip of rum, sailor! Ha-ha! Welcome on board of my lugger. So, you've come for the product as I understand?";
				link.l1 = "Yes. What else for?";
				link.l1.go = "Rum_Cap_2";
			}
			else
			{
				dialog.text = "What a vile brat! Guys this one looks like a sowbelly! Let's send him overboard!";
				link.l1 = "Hup!";
				link.l1.go = "Rum_Cap_getout";
			}
		break;
		
		case "Rum_Cap_getout":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation("Deck_Near_Ship")], false);
			setCharacterShipLocation(pchar, "Shore38"));
			setWDMPointXZ("Shore38");
			DoQuestReloadToLocation("Shore38", "goto", "goto1", "Rum_RemoveBarkas");
		break;
		
		case "Rum_Cap_2":
			dialog.text = "Guys! Load the boxes onto the launch!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Rum_CarrierEnter");
		break;
		
		case "Rum_Cap_3":
			dialog.text = "All the rum boxes are on your launch. Port Le Francois is located due south from here. Make haste. It's time for me to pull in my anchor too!";
			link.l1 = "Let's not waste any time, gentlemen! Good luck!";
			link.l1.go = "Rum_Cap_4";
		break;
		
		case "Rum_Cap_4":
			dialog.text = "Same to you, buddy...";
			link.l1 = "...";
			link.l1.go = "Rum_Cap_5";
		break;
		
		case "Rum_Cap_5":
			DialogExit();
			chrDisableReloadToLocation = false;
			LAi_LocationFightDisable(&Locations[FindLocation("Deck_Near_Ship")], false);
			npchar.DontDeskTalk = true;
			NextDiag.CurrentNode = "Rum_Cap_Over";
			pchar.quest.Sharlie_rum4.win_condition.l1 = "Ship_location";
			pchar.quest.Sharlie_rum4.win_condition.l1.location = "LeFransua_port";
			pchar.quest.Sharlie_rum4.function = "Rum_RemoveRum";
			AddQuestRecord("SharlieB", "4");
			i = FindIsland("Martinique");
			Islands[i].EffectRadius = 3000;
		break;
		
		case "Rum_Carrier":
			dialog.text = "We've been waiting for you, monsieur. How did everything go? Are the boxes with you?";
			link.l1 = "Everything went spectacular. The rum boxes are on the launch.";
			link.l1.go = "Rum_Carrier_1";
		break;
		
		case "Rum_Carrier_1":
			dialog.text = "Great. We'll take care of it from here. You take off to St. Pierre to the tavern for the payment.";
			link.l1 = "All the best, gentlemen.";
			link.l1.go = "Rum_Carrier_2";
		break;
		
		case "Rum_Carrier_2":
			DialogExit();
			for (i=1; i<=3; i++)
			{
				
				sld = characterFromId("Rum_Carrier2_"+i);
				LAi_SetActorType(sld);
				LAi_ActorRunToLocation(sld, "goto", "goto8", "none", "", "", "OpenTheDoors", 10.0);
			}
			pchar.questTemp.Sharlie.Rum = "regard";
			i = FindLocation("Fortfrance_town");
			setCharacterShipLocation(pchar, GetCityFrom_Sea(locations[i].fastreload));
		    setWDMPointXZ(GetCityFrom_Sea(locations[i].fastreload));
		break;
		
		//доставить девочку из борделя
		case "GigoloMan":
			dialog.text = "Good afternoon, monsieur! I swear you don't look like these raggedy appleknockers hanging around here in our colony. And as I see, you must've come a long way... Arrived from Europe, didn't you?";
			link.l1 = "Exactly, monsieur. "+GetFullName(pchar)+", at your service. What do you need?";
			link.l1.go = "GigoloMan_1";
		break;
		
		case "GigoloMan_1":
			dialog.text = "Allow me to introduce myself - "+GetFullName(npchar)+". I have arrived to this dreadful place from France a few years ago. But let's cut to the chase. I have a very delicate matter for you\nIf I wasn't sure in your noble state, I would never ask you for such favour. But I believe you will understand me as a nobleman.";
			link.l1 = "Please, state the crux of your request, monsieur. If it is within my capabilities, then of course I will try to help.";
			link.l1.go = "GigoloMan_2";
		break;
		
		case "GigoloMan_2":
			dialog.text = "I am glad to hear that, monsieur de Maure. There is a brothel in this village. A new girl appeared there recently, young, white skin blonde. I've been watching her for weeks and... got a very strong desire to spend some time with her in private\nBut my estate and status disallow me to visit that place of the sin. No, my friend, surely you understand that I'd like to, but the reputation costs very much\nThat is why I am appealing to you. You are a newcomer, people don't know you and they don't care about what you do... yet. You will do me a great favour, monsieur.";
			link.l1 = "And what could I do for you?";
			link.l1.go = "GigoloMan_3";
		break;
		
		case "GigoloMan_3":
			dialog.text = "Easy as pie. I can't show up in the brothel, so the girl must visit my house. I ask you to go to the brothel and arrange a deal with the madame so she would grant 'a carry-out' of the blonde for one night\nAurora won't refuse, she provides such services, though for a bigger price. Then you should bring the girl to my house. I will give you six thousand pesos, Aurora usually takes three thousands or three and five hundred for a night with the girl. You can keep the rest as a compensation for your troubles.";
			link.l1 = "I don't see anything too complicated about that. I'll carry out your request with no problem.";
			link.l1.go = "GigoloMan_4";
			link.l2 = "Monsieur, I take my reputation just as seriously as you do. So I ask you to forgive me, but I can't fulfil your request. Allow me to refuse.";
			link.l2.go = "GigoloMan_exit";
		break;
		
		case "GigoloMan_exit":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeday = 0;
		break;
		
		case "GigoloMan_4":
			dialog.text = "Glad to hear it. Now listen, the girl's name is Lucille. I ask you to deliver her to my place when it's dark, not earlier than eleven p.m. in order to avoid any unwanted attention. Knock the door and I will let her in\nMy house is over there, to the left of the governor's residence - a two-storeyed mansion with a red roof. You will find it easily. Here, take six thousands pesos. I will be waiting!";
			link.l1 = "I understood. We've got a deal. Your blond will be at your doorstep later tonight.";
			link.l1.go = "GigoloMan_5";
		break;
		
		case "GigoloMan_5":
			DialogExit();
			AddMoneyToCharacter(pchar, 6000);
			AddQuestRecord("SharlieC", "1");
			AddQuestUserData("SharlieC", "sName", GetFullName(npchar));
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "houseSp1", "none", "", "", "", -1);
			LocatorReloadEnterDisable("Fortfrance_town", "houseSp1", true);
			npchar.lifeday = 0;
			pchar.questTemp.Sharlie.Gigolo = "start";
			pchar.questTemp.Sharlie.Gigolo.Rand1 = rand(1);
			pchar.questTemp.Sharlie.Gigolo.Rand2 = rand(1);
		break;
		
		case "GigoloGirl":
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "Hello, monsieur. Is it you that paid me out for the night? Hee-hee, I've got to say, I'm one lucky girl, such a handsome and well-groomed gentleman, nothing like these raggedy appleknockers...";
				link.l1 = "It's not like that at all, Lucille. You're going to spend the night not with me, but with my good friend, who for a multitude of reasons is not able to visit the brothel. But don't be upset, he's quite a solid man, noble, and he likes you. I think you will be happy at the end of it.";
				link.l1.go = "GigoloGirl_1";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "Monsieur, I hope you understand that I can't walk around with you during the night time? Let's do it this way - you take me to your friend's house and go. Otherwise, madame's going to lose her cool and you're going to waste your money.";
				link.l1 = "All right, I got it. After me!";
				link.l1.go = "GigoloGirl_2";
			}
		break;
		
		case "GigoloGirl_1":
			dialog.text = "That's too bad... I liked you right away, monsieur. I would've loved to spend the night with you. Well, no worries. Shall we go?";
			link.l1 = "Yes. Follow me!";
			link.l1.go = "GigoloGirl_2";
		break;
		
		case "GigoloGirl_2":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			pchar.quest.Sharlie_Gigolo.win_condition.l1 = "locator";
			pchar.quest.Sharlie_Gigolo.win_condition.l1.location = "Fortfrance_town";
			pchar.quest.Sharlie_Gigolo.win_condition.l1.locator_group = "reload";
			pchar.quest.Sharlie_Gigolo.win_condition.l1.locator = "houseSp1";
			pchar.quest.Sharlie_Gigolo.function = "Sharlie_GiveGigoloGirl";
			pchar.quest.Sharlie_Gigolo1.win_condition.l1 = "Timer";
			pchar.quest.Sharlie_Gigolo1.win_condition.l1.date.hour  = sti(GetTime() + 2);
			pchar.quest.Sharlie_Gigolo1.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 0);
			pchar.quest.Sharlie_Gigolo1.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 0);
			pchar.quest.Sharlie_Gigolo1.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 0);
			pchar.quest.Sharlie_Gigolo1.function = "Sharlie_GigoloGirlOver";
		break;
		
		case "GigoloGirl_3":
			dialog.text = "This is the place?";
			link.l1 = "Yes. Come in. Don't be afraid, my friend is a good man.";
			link.l1.go = "GigoloGirl_4";
		break;
		
		case "GigoloGirl_4":
			dialog.text = "Heh... I'm not afraid. I've seen a lot of things in this world. Anyway, monsieur, farewell. Maybe some time later you can pay the madam for a night with me? I promise it'll be the best night in your life!";
			link.l1 = "Anything's possible, Lucille. Maybe we'll meet each other again. Bye!";
			link.l1.go = "GigoloGirl_5";
		break;
		
		case "GigoloGirl_5":
			pchar.quest.Sharlie_Gigolo1.over = "yes";
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "houseSp1", "none", "", "", "GigoloGirl_Remove", 5.0);
		break;
		
		//пираты с пленным испанцем
		case "CaptivePirate":
			pchar.quest.Captive_CreatePiratesOver.over = "yes";//снять таймер
			dialog.text = "Who are you? What do you want here? Come on, get the hell out of here!";
			link.l1 = "You're not very polite, sir.";
			link.l1.go = "CaptivePirate_1";
		break;
		
		case "CaptivePirate_1":
			dialog.text = "Listen, hot shot, I wasn't raised to be polite, just like I didn't learn to read and write, but zonking a cavalry sword onside your head or poking a couple new holes in you that's easy as a-b-c. And I swear on my grave that if you don't get out of here this minute, you won't make it out. You got that?";
			link.l1 = "Now you listen here, blockhead. Your scheme's been blown up. I need this captive. Resistance is futile. There's a group of French soldiers in the jungle. If you run pretty fast, then maybe you'll manage to save your pathetic lives.";
			link.l1.go = "CaptivePirate_3";
			link.l2 = "All right, all right, calm down. I'm leaving.";
			link.l2.go = "CaptivePirate_2";
		break;
		
		case "CaptivePirate_2":
			chrDisableReloadToLocation = false;
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			DialogExit();
			n = makeint(MOD_SKILL_ENEMY_RATE/2);
			if (n <= 1) n = 2;
			for (i=1; i<=n; i++)
			{
				sld = characterFromId("CaptivePirate_"+i);
				LAi_CharacterDisableDialog(sld);
				LAi_SetImmortal(sld, true);
				sld.lifeday = 0;
			}
			sld = characterFromId("CaptiveSpain");
			LAi_SetImmortal(sld, true);
			sld.lifeday = 0;
			pchar.quest.Sharlie_captive1.over = "yes";
			pchar.quest.Sharlie_captive2.over = "yes";//снять прерывание
			AddQuestRecord("SharlieD", "5");
			CloseQuestHeader("SharlieD");
			DeleteAttribute(pchar, "questTemp.Sharlie.Captive");
			pchar.questTemp.Sharlie = "bankskipermoney";
		break;
		
		case "CaptivePirate_3":
			dialog.text = "Wha-at? You're bluffing, buddy! But either way you're the one dying first! Guys, to arms!";
			link.l1 = "Come on, hang in there, bastards...";
			link.l1.go = "CaptivePirate_4";
		break;
		
		case "CaptivePirate_4":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			int n = makeint(MOD_SKILL_ENEMY_RATE/2);
			if (n <= 1) n = 2;
			for (i=1; i<=n; i++)
			{
				sld = characterFromId("CaptivePirate_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "Captive_PiratesDead");
			AddDialogExitQuest("MainHeroFightModeOn");	
			sld = characterFromId("CaptiveSpain");
			LAi_SetCitizenType(sld);
		break;
		
		//пленный испанец
		case "CaptiveSpain":
			dialog.text = "Mierda! You're a Frenchman? You fended off those scumbags in style. But don't think that I'll give up just like that!";
			link.l1 = "Stop... Listen, I didn't...";
			link.l1.go = "CaptiveSpain_1";
		break;
		
		case "CaptiveSpain_1":
			dialog.text = "I've got nothing to look forward to from the French, but jail. I took a sabre from one of the dead bodies while you were fighting the last pirate... On guard, frog eater!";
			link.l1 = "Oh, you're as stubborn as an ox!";
			link.l1.go = "CaptiveSpain_2";
		break;
		
		case "CaptiveSpain_2":
			DialogExit();
			LAi_SetPlayerType(pchar);
			NextDiag.currentnode = "CaptiveSpain_3";
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_SetCheckMinHP(npchar, 10.0, true, "CaptiveSpain_capture");
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
		case "CaptiveSpain_3":
			dialog.text = "Argh... You won. I give up, damn Frenchman. Now do with me what you wish, I'm at your disposal.";
			link.l1 = "I want you to throw aside your weapon and give me an edge in wordwise, you obstinate Castilian! I don't need you to die! And I'm not sending you to jail either!";
			link.l1.go = "CaptiveSpain_4";
			RemoveCharacterEquip(npchar, BLADE_ITEM_TYPE);
		break;
		
		case "CaptiveSpain_4":
			dialog.text = "Then what do you need so badly from me? Why did you kill the pirates then? And where are your soldiers?";
			link.l1 = "There are no soldiers. I tried to spook the scumbags, but as you can see, it didn't work. I was operating solo, according to your old friend's request. His name is "+pchar.questTemp.Sharlie.Captive.Name+", he's a banker in St. Pierre.";
			link.l1.go = "CaptiveSpain_5";
		break;
		
		case "CaptiveSpain_5":
			dialog.text = ""+pchar.questTemp.Sharlie.Captive.Name+"? I don't know anyone by that name. I've never even heard it before!";
			link.l1 = "Nor have I heard a thing about you or your captivity and I became aware of your transfer to an English ship from him. My task is to deliver you to him and I swear I will fulfil that! So if staying alive is within your interests then follow me and no monkey business.";
			link.l1.go = "CaptiveSpain_6";
		break;
		
		case "CaptiveSpain_6":
			dialog.text = "I don't have a choice anyway... Maybe this banker of yours will be something better than English dogs after all...";
			link.l1 = "You've finally started to show reason. That's enough talking for now, though we're departing to St. Pierre. Keep close to me and don't even think about running away: I'll catch you anyway!";
			link.l1.go = "CaptiveSpain_7";
		break;
		
		case "CaptiveSpain_7":
			chrDisableReloadToLocation = false;
			DeleteAttribute(pchar, "GenQuest.Notsearchbody"); // 170712
			DialogExit();
			AddQuestRecord("SharlieD", "6");
			LAi_group_Register("TempFriends");
			LAi_group_SetRelation("TempFriends", LAI_GROUP_PLAYER, LAI_GROUP_FRIEND);
			LAi_group_MoveCharacter(npchar, "TempFriends");
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			SetNationRelation2MainCharacter(FRANCE, RELATION_ENEMY);
			pchar.quest.Sharlie_captive3.win_condition.l1 = "locator";
			pchar.quest.Sharlie_captive3.win_condition.l1.location = "Fortfrance_town";
			pchar.quest.Sharlie_captive3.win_condition.l1.locator_group = "reload";
			pchar.quest.Sharlie_captive3.win_condition.l1.locator = "reload8_back";
			pchar.quest.Sharlie_captive3.win_condition.l2 = "Night";
			pchar.quest.Sharlie_captive3.win_condition.l3 = "Alarm";
			pchar.quest.Sharlie_captive3.win_condition.l3.value = 0;
			pchar.quest.Sharlie_captive3.win_condition.l3.operation = "=";
			pchar.quest.Sharlie_captive3.function = "CaptiveSpain_reload";//вход ночью
			pchar.questTemp.Sharlie = "bankskipercaptive";
		break;
		
		//горожанин с пропавшей дочерью
		case "Prosper":
			pchar.quest.Sharlie_RescueDaughter.over = "yes"; //снять прерывание
			dialog.text = "What do you need, monsieur? I've got absolutely no time for conversation, so be brief.";
			link.l1 = "You are Prosper Trubal, aren't you?";
			link.l1.go = "Prosper_1";
		break;
		
		case "Prosper_1":
			dialog.text = "Yes, it is me. But I have no idea who you are. Please inform me of who you are and what the hell do you want from me.";
			link.l1 = "My name is "+GetFullName(pchar)+". I've been sent to you by "+GetFullName(characterFromId("Fortfrance_portman"))+", harbour master. He said that you needed help urgently...";
			link.l1.go = "Prosper_2";
		break;
		
		case "Prosper_2":
			dialog.text = "Strike me dead if it isn't so! That rascal of a commandant didn't even hear me out to the end. He's too lazy to lift his butt of his seat and give his dumb soldiers an order! Have you really come here to help me? If it is so, I won't leave you unrewarded!";
			link.l1 = "Prosper, I've definitely come to help you. Tell me in order what happened and what I have to do. I've heard that your daughter disappeared...";
			link.l1.go = "Prosper_3";
		break;
		
		case "Prosper_3":
			dialog.text = "Yes, my daughter Celene has been missing for two days. She was supposed to go to the fort not far from here. But she did not return, so I went to the fort myself and soldiers told me that she had never been there!\nNow, the interesting part starts. I was attacked but two coloured Indians on my return. They ambushed and tried to stun me with their clubs\nI am not a kitten, so I  punched one in the face, got my pistol and shot. I missed but scared them away. I managed to reach the city gates and told guards about the attackers. They ran immediately to the jungles, but the redskins were already gone\nI am sure that they are responsible for Celene's disappearance. Besides, two more people have disappeared for the last week - Cesar Blanchet and Gilbert Courcy. One was heading to the bay and another to Le Francois. They've never returned.";
			link.l1 = "So the Indians have been attacking townsfolk right at the city gates? Unbelievable...";
			link.l1.go = "Prosper_4";
		break;
		
		case "Prosper_4":
			dialog.text = "My reconnaissance gave some results. There is a cave north to the city. The bastards are sitting there. I saw several Indians at the entrance, also some of them must be inside\nI heard a girl screaming in that cave. It was my Celene, I am sure of that, it was her voice! I barely managed not to rush there immediately - the odds were not in my favour and my death wouldn't save Celene.";
			link.l1 = "But why are they attacking and taking townspeople hostage?";
			link.l1.go = "Prosper_5";
		break;
		
		case "Prosper_5":
			dialog.text = "I don't know. Maybe to sell them to pirates or to turn into slavery. Maybe they're just gonna eat them alive, they're savages.";
			link.l1 = "What, are they cannibals? What a bunch of balderdash... Although I've heard something of that before...";
			link.l1.go = "Prosper_6";
		break;
		
		case "Prosper_6":
			dialog.text = "Nonsense? Well, some thought the same until Caribs had them cooked on a fire and eaten... So, I had immediately addressed the commandant and requested a punitive raid. Think what, he refused. He said that when girls are missing, one should suspect local boys, not Indians. He suggested I search for her admirers\nAnd as for two others... one of them is under suspicion for having connections with smugglers, and another must be drinking to death in Le Francois' tavern. To sum up, I have achieved nothing and decided to act on my own.";
			link.l1 = "What are you intending on doing?";
			link.l1.go = "Prosper_7";
		break;
		
		case "Prosper_7":
			dialog.text = "I will go there and kill all of the scum. I hope that Celene still lives. As you can see, I bought a musket - a very destructive thing and I know how to shoot. Paid a lot of coins for it, but I don't give a damn\nMy mission will be much easier if you will accompany me, together we can finish the bastards without trouble. Watching my back while I am reloading is critical. Will you go with me to save my daughter?";
			link.l1 = "Of course! It's a matter of honour! I can't just allow a girl to die by the knife of some savage.";
			link.l1.go = "Prosper_8";
			link.l2 = "Hm. You know, I think commandant's words make sense. Maybe we should still follow his advice first?";
			link.l2.go = "Prosper_exit";
		break;
		
		case "Prosper_exit":
			dialog.text = "What, are you kidding? No! Get the hell out of here! Coward...";
			link.l1 = "Hey, hey. Easy!";
			link.l1.go = "Prosper_exit_1";
		break;
		
		case "Prosper_exit_1":
			DialogExit();
			npchar.lifeday = 0;
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "gate_back", "none", "", "", "", 10.0);
			CloseQuestHeader("SharlieF");
		break;
		
		case "Prosper_8":
			dialog.text = "I'm glad there at least one rational, courageous man in this town. Here, take these three vials. This is a health-giving herb, I bought it from our herbalist. It can be a substantial help to you in battle.";
			link.l1 = "What about you?";
			link.l1.go = "Prosper_9";
		break;
		
		case "Prosper_9":
			TakeNItems(pchar, "potion1", 3);
			PlaySound("interface\important_item.wav");
			dialog.text = "Don't worry, I've got more. Are you ready?";
			link.l1 = "Yes, let's not waste any time. It's valuable as gold. Onward!";
			link.l1.go = "Prosper_10";
		break;
		
		case "Prosper_10":
			DialogExit();
			LAi_SetImmortal(npchar, true);
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			AddQuestRecord("SharlieF", "3");
			pchar.quest.Sharlie_RescueDaughter1.win_condition.l1 = "location";
			pchar.quest.Sharlie_RescueDaughter1.win_condition.l1.location = "Martinique_jungle_04";
			pchar.quest.Sharlie_RescueDaughter1.function = "RescueDaughter_NearCave";
			pchar.quest.Sharlie_RescueDaughter2.win_condition.l1 = "Timer";
			pchar.quest.Sharlie_RescueDaughter2.win_condition.l1.date.hour  = sti(GetTime()+2);
			pchar.quest.Sharlie_RescueDaughter2.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 0);
			pchar.quest.Sharlie_RescueDaughter2.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 0);
			pchar.quest.Sharlie_RescueDaughter2.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 0);
			pchar.quest.Sharlie_RescueDaughter2.function = "RescueDaughter_CaveOver";
			NextDiag.CurrentNode = "Prosper_11";
			pchar.questTemp.Sharlie.RescueDaughter = "true";
		break;
		
		case "Prosper_11":
			dialog.text = "We're almost in position, "+pchar.name+". Beyond this turn is the entrance into the cave. Now I'd like to tell you my plan on how we'll move forward from here.";
			link.l1 = "I'm all ears, Prosper.";
			link.l1.go = "Prosper_12";
		break;
		
		case "Prosper_12":
			dialog.text = "I don't miss a shot, but for an accurate shot I need to get a nice steady aim. If I have to engage in hand-to-hand combat, forget about firing, I'll only be able to fend people off with my barrel as a club. So a lot is going to depend on your manliness and your agility.";
			link.l1 = "What are you trying to say?";
			link.l1.go = "Prosper_13";
		break;
		
		case "Prosper_13":
			dialog.text = "All you need is to distract their attention in order to let me shoot them all. Running is no good for the accuracy, so I will stick to one certain location. There are three bastards close to the cave's entrance. You should rush them as fast as you can with your blade in a hand\nHit one of them and make them chase you, prevent them from attacking me, move aside and lure them away from me. If all three will focus on you, I will shoot them all like birds. But if all those savages swoop down upon me then our chances will be bad. Are you scared?";
			link.l1 = "This won't be the first time I've handled a sword. So don't worry about that for a minute.";
			link.l1.go = "Prosper_14";
		break;
		
		case "Prosper_14":
			dialog.text = "Then prepare for action. Go first, I'll be behind you. Remember: you can't let them get within a close distance to me!";
			link.l1 = "I remember. I'll do everything I can. Onward!";
			link.l1.go = "Prosper_15";
		break;
		
		case "Prosper_15":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			LocatorReloadEnterDisable("Martinique_jungle_04", "reload2_back", false);
			NextDiag.CurrentNode = "Prosper_16";
		break;
		
		case "Prosper_16":
			dialog.text = "Well done, "+pchar.name+"! This bunch of redskin scumbags is dead. Now the main part - the cave. I believe that there are three or four of them inside, but I can't know for sure. Now listen\nI've been there ten years ago. So, there is a narrow cavern inside the cave. It leads to a small grotto, divided by a wall with a hole in the middle of it. Let's repeat our scheme. I stand still close to the entrance and you rush in\nProvoke them, don't try to fight all of them at once, just prevent them from attacking me. Take position at the hole I mentioned, it is narrow, so only one or two of them will be able to fight you at the same time\nI will shoot at their backs while they are busy with you. Ready?";
			link.l1 = "Onward! Let's finish off this nest of savages!";
			link.l1.go = "Prosper_17";
		break;
		
		case "Prosper_17":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			LocatorReloadEnterDisable("Martinique_CaveEntrance", "reload1_back", false);
			AddComplexSelfExpToScill(20, 20, 20, 20);
			pchar.quest.Sharlie_RescueDaughter2.win_condition.l1 = "location";
			pchar.quest.Sharlie_RescueDaughter2.win_condition.l1.location = "Martinique_Grot";
			pchar.quest.Sharlie_RescueDaughter2.function = "RescueDaughter_CreateIndiansGrot";
			NextDiag.CurrentNode = "Prosper_18";
		break;
		
		case "Prosper_18":
			dialog.text = "My daughter is alive! Thank God! We've got here in time, "+pchar.name+". I'm indebted to you. You're a brave man and a good fighter. I'm awe struck!";
			link.l1 = "I'm glad, Prosper, that it ended fruitfully. That was quite a task taking out those scumbags.";
			link.l1.go = "Prosper_19";
		break;
		
		case "Prosper_19":
			DialogExit();
			sld = characterFromId("RD_Selina");
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", 0, 0);
			AddComplexSelfExpToScill(30, 30, 30, 30);
		break;
		
		case "Prosper_20":
			dialog.text = "Huge thanks once again, "+pchar.name+"! Now let's make our way back to town. The life of my daughter is priceless, immeasurable by any amount of money, but I want to thank you by leaving your with what's left of my savings. As soon as we get to Saint-Pierre, I will gladly give them to you. And don't even think of refusing!";
			link.l1 = "I won't refuse, Prosper. Although I wasn't helping you for money at all.";
			link.l1.go = "Prosper_21";
		break;
		
		case "Prosper_21":
			dialog.text = "You're a noble man, "+pchar.name+"! Now let's not meddle around here. Let's make our way back home.";
			link.l1 = "...";
			link.l1.go = "Prosper_22";
		break;
		
		case "Prosper_22":
			chrDisableReloadToLocation = false;
			DialogExit();
			LAi_SetImmortal(npchar, true);
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			sld = characterFromId("RD_Selina");
			LAi_SetActorType(sld);
			LAi_ActorFollowEverywhere(sld, "", -1);
			sld = characterFromId("RD_Jilberte");
			LAi_SetActorType(sld);
			LAi_ActorFollowEverywhere(sld, "", -1);
		break;
		
		case "Prosper_23":
			SelectPresentAmulet();
			dialog.text = "Here we are. Charles, I thank you once again for your help and I tie this modest sum of pesos and sack of gold doubloons to my words. I suggest you don't waste doubloons and keep them for special occasions. It's not a lot for a favour like that, but it's from the bottom of my heart. Also take this amulet, "+pchar.questTemp.SMQ.Text+"";
			link.l1 = "Thank you. Farewell, Prosper. I wish happiness to you and to your dear daughter!";
			link.l1.go = "Prosper_24";
		break;
		
		case "Prosper_24":
			AddMoneyToCharacter(pchar, 5000);
			TakeNItems(pchar, "gold_dublon", 15);
			TakeNItems(pchar, pchar.questTemp.SMQ.Amulet, 1);
			Log_Info("You've received 15 doubloons");
			Log_Info("You've received an amulet");
			PlaySound("interface\important_item.wav");
			dialog.text = "A husband like you would do her well. Otherwise, all she does is get chased by a bunch of skinny-legged fops. Once a pity has come upon us that everyone of them disappeared somewhere... Eh, all right. Good luck, Charles!";
			link.l1 = "...";
			link.l1.go = "Prosper_25";
		break;
		
		case "Prosper_25":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload10_back", "none", "", "", "", 10.0);
			sld = characterFromId("RD_Selina");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload10_back", "none", "", "", "", 10.0);
			ChangeCharacterComplexReputation(pchar, "nobility", 3);
			ChangeCharacterComplexReputation(pchar,"authority", 2);
			AddCharacterExpToSkill(pchar, "Leadership", 120);//авторитет
			AddCharacterExpToSkill(pchar, "Fortune", 70);//везение
			AddCharacterExpToSkill(pchar, "Sneak", 70);//скрытность
			AddQuestRecord("SharlieF", "7");
			CloseQuestHeader("SharlieF");
			DeleteAttribute(pchar, "questTemp.SMQ");
			pchar.questTemp.Prosper_fmql = "true"; // Addon-2016 Jason, французские миниквесты (ФМК)
		break;
		
		case "Selina":
			dialog.text = "Ah! (crying) You...you can't even imagine the horror that's going on here! These... these people have dragged us here to kill us and eat us! Cesar Blanchet was here...They took him... They performed some sinister ritual and then... Lord, I can't even speak of it! I was supposed to be next! They were going to slaughter me... tomorrow!";
			link.l1 = "Calm down, Celine. It's all over. Those scumbags have got what they deserved and they won't cause anybody any more harm.";
			link.l1.go = "Selina_1";
		break;
		
		case "Selina_1":
			dialog.text = "Gilbert Coursie is here too. Over there he uh...he still hasn't recovered yet. Speak with him... And let's hurry up and get out of here!";
			link.l1 = "There, there. It's all right, little girl. Enough crying. Everything's fine. You've got a wonderful father. He wouldn't let anybody harm you... Go outside, I'll help...uh... Gilbert out of here and I'll catch up with you later.";
			link.l1.go = "Selina_2";
		break;
		
		case "Selina_2":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "Martinique_CaveEntrance", "officers", "reload1_2", "", 5.0);
			sld = characterFromId("RD_Prosper");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload1_back", "Martinique_CaveEntrance", "officers", "reload1_1", "", 5.0);
			AddQuestRecord("SharlieF", "5");
			sld = characterFromId("RD_Jilberte");
			LAi_SetStayType(sld);
		break;
		
		case "Selina_3":
			dialog.text = "The heavens have heard my prayers! Have you come to save us?";
			link.l1 = "You... Your name is Celine, isn't it?";
			link.l1.go = "Selina_4";
		break;
		
		case "Selina_4":
			dialog.text = "Yes... (crying) You...you can't even imagine the horror that's going on here! These... these people have dragged us here to kill us and eat us! Cesar Blanchet was here...They took him... They performed some freaky ritual and then... Lord, I can't even speak of it! I'm supposed to be next! They were going to slaughter me... tomorrow!";
			link.l1 = "Calm down, little girl... I'm sorry but I bring you bad news. I have come here together with your father. But he's perished in a tussle with those redskinned maggots. He has given his life to save you.";
			link.l1.go = "Selina_5";
		break;
		
		case "Selina_5":
			dialog.text = "What?! My father... Oh Lord! I... I...(sobbing)";
			link.l1 = "My condolences, Celine. There is some one left here, am I right?";
			link.l1.go = "Selina_6";
		break;
		
		case "Selina_6":
			dialog.text = "(through tears) Yes... Gilbert Coursie. He's in there... He still hasn't recovered yet. Go speak to him... And let's hurry out of here!";
			link.l1 = "Yes, of course. We can't waste one minute standing around here.";
			link.l1.go = "Selina_7";
		break;
		
		case "Selina_7":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "Martinique_CaveEntrance", "officers", "reload1_2", "", 5.0);
			AddQuestRecord("SharlieF", "6");
			sld = characterFromId("RD_Jilberte");
			LAi_SetStayType(sld);
			AddComplexSelfExpToScill(20, 20, 20, 20);
		break;
		
		case "Selina_8":
			dialog.text = "My father... My poor father! Ah, monsieur, I haven't even thanked you for saving me...";
			link.l1 = "I'm just glad, Selina, that you and Gilbert came out of there alive. In any case, the heroic death of your father was not in vain.";
			link.l1.go = "Selina_9";
		break;
		
		case "Selina_9":
			dialog.text = "(crying) Please, monsieur, take us with you to the town. We have to send for the soldiers to come here and carry the body of my father, so that he will have a proper Christian burial...";
			link.l1 = "Of course, Celine. Follow me!";
			link.l1.go = "Selina_10";
		break;
		
		case "Selina_10":
			chrDisableReloadToLocation = false;
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			sld = characterFromId("RD_Jilberte");
			LAi_SetActorType(sld);
			LAi_ActorFollowEverywhere(sld, "", -1);
		break;
		
		case "Selina_11":
			dialog.text = "Thank you, monsieur, for accompanying my poor father... Thank you for saving me from imminent death. I... I... Here, take this bag of doubloons. I found it at home in my father's chest. And don't even think about refusing!";
			link.l1 = "Alright, Celine. I'm glad we've managed to save you. And my sincere condolences about the loss of your father.";
			link.l1.go = "Selina_12";
		break;
		
		case "Selina_12":
			TakeNItems(pchar, "gold_dublon", 15);
			PlaySound("interface\important_item.wav");
			dialog.text = "You are a noble man, monsieur. I will never forget you. Farewell!";
			link.l1 = "Farewell, Celine.";
			link.l1.go = "Selina_13";
		break;
		
		case "Selina_13":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload10_back", "none", "", "", "", 10.0);
			npchar.lifeday = 0;
			ChangeCharacterComplexReputation(pchar, "nobility", 3);
			ChangeCharacterComplexReputation(pchar,"authority", 1);
			AddCharacterExpToSkill(pchar, "Leadership", 100);//авторитет
			AddCharacterExpToSkill(pchar, "Fortune", 50);//везение
			AddCharacterExpToSkill(pchar, "Sneak", 50);//скрытность
			AddQuestRecord("SharlieF", "8");
			CloseQuestHeader("SharlieF");
		break;
		
		case "Jilberte":
			PlaySound("Voice\Russian\other\robinzons-08.wav");
			dialog.text = "Oh Lord, is it really all behind us? I can't even believe it... You've saved both me and Celine. If it weren't for you, the same ill fate of the unfortunate Cesar would've called upon her tomorrow and the same would be prepared for me in a few days.";
			link.l1 = "These Indians, what are they really cannibals?!";
			link.l1.go = "Jilberte_1";
		break;
		
		case "Jilberte_1":
			dialog.text = "Are you having doubts? If you want, have a look into the cinders of their fire. I think you'll find there something remaining from poor old Cesar. Like a couple gnawed up bones for example...";
			link.l1 = "Oooh... No, I'm good. I've just recently arrived here from Europe and I couldn't even imagine that such disgusting things take place on our Earth.";
			link.l1.go = "Jilberte_2";
		break;
		
		case "Jilberte_2":
			dialog.text = "A lot of things happen in the Caribbean, things that you never heard of in your Europe... Indian wizards, shamans, secret rituals. Stay here longer and you will see all kinds of strangeness. But forgive me, I haven't thanked you for saving me - I am still in a shock\nYou saved my life and I am going to express my gratitude not only in words, but also in good gold. Escort Celine and me to the city. There I will be able to thank you as you deserve, monsieur.";
			link.l1 = "All right. Step outside. I'm gonna have a little look around here.";
			link.l1.go = "Jilberte_3";
		break;
		
		case "Jilberte_3":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "Martinique_CaveEntrance", "officers", "reload1_3", "OpenTheDoors", 10.0);
			pchar.quest.Sharlie_RescueDaughter5.win_condition.l1 = "location";
			pchar.quest.Sharlie_RescueDaughter5.win_condition.l1.location = "Martinique_CaveEntrance";
			pchar.quest.Sharlie_RescueDaughter5.function = "RescueDaughter_GoHome";
		break;
		
		case "Jilberte_4":
			dialog.text = "Let me express to you my profound gratitude once more for saving me, monsieur! As promised, I add to my verbal gratitude material gratitude in the form of silver pesos and gold doubloons.";
			link.l1 = "I am glad that everything turned out okay, Gilbert.";
			link.l1.go = "Jilberte_5";
		break;
		
		case "Jilberte_5":
			AddMoneyToCharacter(pchar, 3000);
			TakeNItems(pchar, "gold_dublon", 20);
			Log_Info("You've received 20 doubloons");
			PlaySound("interface\important_item.wav");
			dialog.text = "You can't even imagine how happy I am about this! Thank you once again and allow me to take my leave, monsieur.";
			link.l1 = "Good luck, Gilbert!";
			link.l1.go = "Jilberte_6";
		break;
		
		case "Jilberte_6":
			chrDisableReloadToLocation = false;
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload4_back", "none", "", "", "", 10.0);
			npchar.lifeday = 0;
			DeleteAttribute(pchar, "questTemp.Sharlie.RescueDaughter");
		break;
		
		//замечание по обнаженному оружию от персонажей типа citizen
		case "CitizenNotBlade":
			dialog.text = NPCharSexPhrase(NPChar, "Listen, I, as a citizen of this city, ask you not to walk around with your blade exposed.", "You know, I, as a citizen of this city, ask you not to walk around with your blade exposed.");
			link.l1 = LinkRandPhrase("All right.", "Okay.", "As you wish...");
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

void SelectPresentAmulet()
{
	switch (pchar.HeroParam.HeroType)
	{        
		case "HeroType_1":
			pchar.questTemp.SMQ.Amulet = "indian_7";
			pchar.questTemp.SMQ.Text = "it adds endurance and opens up a second wind.";
		break;
		
		case "HeroType_2":
			pchar.questTemp.SMQ.Amulet = "amulet_7";
			pchar.questTemp.SMQ.Text = "it heightens resilience to battle wounds.";
		break;
		
		case "HeroType_3":
			pchar.questTemp.SMQ.Amulet = "indian_4";
			pchar.questTemp.SMQ.Text = "it raises your weapons' attack force.";
		break;
		
		case "HeroType_4":
			pchar.questTemp.SMQ.Amulet = "indian_1";
			pchar.questTemp.SMQ.Text = "it makes fire weaponry much more lethal.";
		break;
	}
}
