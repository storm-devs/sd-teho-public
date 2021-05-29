// Соломон Шнеур - старый еврей
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
		case "First time":
//--------------------------------------за Голландию------------------------------------------------
			if (CheckAttribute(pchar, "questTemp.HWIC.Holl"))
			{
				if (pchar.questTemp.HWIC.Holl == "AbbyFather")
				{
					dialog.text = "What do you want from the old Jew, young man?";
					link.l1 = "Solomon, I need you to recall a location of the island. You have a stash there. I've talked with your daughter. My boss Lucas Rodenburg gives me a carte blanche to act for the good of your family. As I see it, the most important thing for you at this moment is retrieving your family capital. But I will hardly be able to do this without your help...";
					link.l1.go = "SolomonBonanza";
					break;
				}
				if (pchar.questTemp.HWIC.Holl == "AbbyFindScull" && makeint(Pchar.money) >= 200000)
				{
					dialog.text = "Oh, my young man, is that you? Can you tell me anything good? Or are you going to torment this poor old Jew with questions again?";
					if (CheckCharacterItem(pchar, "SkullAztec"))
					{
						link.l1 = "I have found the island, though it was quite difficult. I have also found your chest with the money and this skull. I take it this is the skull of your grandfather that you'd been talking about.";
						link.l1.go = "SolomonBonanza_2";
					}
					link.l2 = "I have found the island, though it was quite difficult. I have also found your chest with the money. But there were no skulls in that chest.";
					link.l2.go = "SolomonBonanza_3";
					link.l3 = "No, there will be no tidings or questions this time.";
					link.l3.go = "exit";
					break;
				}
				if (pchar.questTemp.HWIC.Holl == "GiveLucasMoney" && GetQuestPastDayParam("questTemp.HWIC.Holl.LucasMoney") > 7)
				{
					dialog.text = "Oh, my young man, is that you? Can you tell me anything good? Or are you going to torment this poor old Jew with questions again?";
					link.l1 = "I have found the island, though it was quite difficult. I have also found your chest with the money. Here you are.";
					link.l1.go = "SolomonBonanza_5";
					break;
				}
				dialog.text = "Hello, young man. Now, what do you want from this poor old Jew?";
				link.l1 = "Good afternoon. No, nothing, I've just come to say hello.";
				link.l1.go = "exit";
				break;
			}
//----------------------------------------за Англию-----------------------------------------------
			if (CheckAttribute(pchar, "questTemp.HWIC.Eng"))
			{
				if (pchar.questTemp.HWIC.Eng == "toAbigile")
				{
					dialog.text = "Good afternoon, young man. I see you've come for a purpose... What do you want? Am I getting something out of this or did I miss anything?";
					link.l1 = "Good afternoon. I would like to talk to Abigail.";
					link.l1.go = "Solomon_treasure";
					break;
				}
				dialog.text = "Hello, young man. Now, what do you want from this poor old Jew?";
				link.l1 = "Good afternoon. No, nothing, I've just come to say hello.";
				link.l1.go = "exit";
				break;
			}
//-----------------------------------------против всех-------------------------------------------------
			if (CheckAttribute(pchar, "questTemp.HWIC.Self"))
			{
				if (pchar.questTemp.HWIC.Self == "toVillemstad")
				{
					dialog.text = "Good afternoon, young man. I see you've come for a purpose... What do you want? Am I getting something out of this or did I miss anything?";
					link.l1 = "I need to talk to Abigail. I've got a letter for her.";
					link.l1.go = "Abigile_kidnap";
					break;
				}
				if (pchar.questTemp.HWIC.Self == "AbigileNextDayOver")
				{
					dialog.text = "Hello young man. What do you want? Another letter for my daughter?";
					link.l1 = "Hm... No. Where is Abigail?";
					link.l1.go = "Abigile_GoOver";
					break;
				}
				if (pchar.questTemp.HWIC.Self == "SolomonHistory")
				{
					dialog.text = "Hmm... Are you talking about my money, young man?";
					link.l1 = "Yes, mynheer. About the money you hid on some island and neither you nor Abigail remember its location and how it looks like.";
					link.l1.go = "Solomon_history";
					break;
				}
				if (pchar.questTemp.HWIC.Self == "SolomonHistoryAfter")
				{
					dialog.text = "Alright. I remember the flute and its captain. I had even seen him once in our port. The flute's name was 'Leiden' and the captain's name was Toff Keller, I guess.";
					link.l1 = "That's a start! I've got a lead now.";
					link.l1.go = "Solomon_history_3";
					pchar.questTemp.HWIC.Self = "SolomonHistoryEnd";
					break;
				}
				dialog.text = "What do you want from this poor old Jew this time?";
				link.l1 = "Good afternoon. No, nothing, I've just come to say hello.";
				link.l1.go = "exit";
				break;
			}
			dialog.text = "What do you want from this poor old Jew this time?";
			link.l1 = "Good afternoon. No, nothing, I've just come to say hello.";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;

//-----------------------------------------------За Голландию-----------------------------------
		case "SolomonBonanza":
			PlaySound("VOICE\Russian\hambit\Solomon Shneur-03.wav");
			dialog.text = "And what do you want from me? Do I look like a man who knows anything extra? How could I know in that scary-scary day that some piece of ground among the waves has fooditude and other goldinates? Or how those, who want to look smarter than an old Jew, call it?\nIsland. Not a single decent man there, except Abi and me. Not a single. No one at all. There was a grotto in the middle of it. I put my chest there to save it from that pirate fucker. Everything I had earned with a hard work is there. Plus, my granddad's skull... Trust me, that thingy saved us, yes-yes\nOh-ho-ho, an ancient thingy! God save us! It is difficult to start over in this age! I wish you knew, young man! Oh, I wish you knew!";
			link.l1 = "What? No help from you, huh? Who cares. I'll deal with it on my own. Bye!";
			link.l1.go = "SolomonBonanza_1";
		break;
		
		case "SolomonBonanza_1":
			DialogExit();
			pchar.questTemp.HWIC.Holl = "AbbySeekIsland";
			pchar.quest.Joakim_meeteng.win_condition.l1 = "location";
			pchar.quest.Joakim_meeteng.win_condition.l1.location = "Villemstad_town";
			pchar.quest.Joakim_meeteng.function = "Create_Joakim";
		break;
		
		case "SolomonBonanza_2"://отдаем всё
			dialog.text = "Oh, gratitude, young man! You have brought back not only my money - you have also cleansed the Shneur's name! Mynheer Rodenburg can be rightfully proud that he has captains like you under his command. I will give the skull to mynheer Rodenburg, he promised to pay a significant sum for it. And I also would like to thank you personally - please, accept this amulet as a memento.";
			link.l1 = "I am happy for you. Thank you for the gift!";
			link.l1.go = "SolomonBonanza_4";
			RemoveItems(PChar, "SkullAztec", 1);
			AddMoneyToCharacter(pchar, -200000);
			GiveItem2Character(pchar, "amulet_7"); 
			AddDialogExitQuestFunction("DeleteJoakimFromRoom");
			ChangeCharacterComplexReputation(pchar, "nobility", 5);
			SetFunctionTimerCondition("Caleuche_StartTotal", 0, 0, 180, false); // таймер на Калеуче
		break;
		
		case "SolomonBonanza_3":
			dialog.text = "Oh, gratitude, young man! You have brought back not only my money - you have cleansed the Shneur's name! As for the skull - oh, well, nevermind! Mynheer Rodenburg can be rightfully proud that he has captains like you under his command. I would like to thank you personally - please, accept this amulet as a memento.";
			link.l1 = "I am happy for you. Thank you for the gift!";
			link.l1.go = "SolomonBonanza_4";
			AddMoneyToCharacter(pchar, -200000);
			GiveItem2Character(pchar, "obereg_10");
			pchar.questTemp.HWIC.Holl.ScullnotReturn = "true";//признак для Лукаса
			ChangeCharacterComplexReputation(pchar, "nobility", -8);
		break;
		
		case "SolomonBonanza_4":
			DialogExit();
			pchar.questTemp.HWIC.Holl = "AbbyLeavesMarried";//теперь можно говорить с Аби
			AddQuestRecord("Holl_Gambit", "1-32");
		break;
		
		case "SolomonBonanza_5":
			dialog.text = "What? What are you saying, young man? Is this true? Let me have a look... ";
			link.l1 = "Here is your money. It belongs to you and Abigail. But alas, I haven't found the skull of your grandfather.";
			link.l1.go = "SolomonBonanza_6";
		break;
		
		case "SolomonBonanza_6":
			AddMoneyToCharacter(pchar, -200000);
			GiveItem2Character(pchar, "amulet_7"); 
			dialog.text = "Oh, money, yes, money... It doesn't look like my money, though... Doesn't smell like my shiny coins. But then again - money is all the same, young man, isn't it? Do not bother yourself to answer - I know. Thank you so much for returning my savings. I would like to thank you too, please, accept this amulet. Now go and tell Abi the good news!";
			link.l1 = "Thank you, Solomon.";
			link.l1.go = "SolomonBonanza_4";
			pchar.questTemp.HWIC.Holl.LucasMoney = "true";//признак для Лукаса
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
		break;

//-------------------------------------------за Англию------------------------------------------------
		
		case "Solomon_treasure":
			dialog.text = "Oh, don't tell me! Mynheer Rodenburg is a step away from being my son-in-law. Blow! I like him! All soldiers from the garrison will be here in a second, should I cry for help!";
			link.l1 = "Who are you, for fuck's sake?";
			link.l1.go = "Solomon_treasure_1";
		break;
		
		case "Solomon_treasure_1":
			dialog.text = "Listen to me, captain. I am her natural father Solomon. Do a shiny thing, bring me my coins and a skull of her grandpa. Old Jew is surely not as smart as you are, but even he knows that you want something from his daughter\nMaybe you were sent by someone, by some captain I know, I will tell Abi everything, don't worry. She is not at home now, she is praying for sinners like you.";
			link.l1 = "Fuck, you're a real piece of work... Bye, old miser.";
			link.l1.go = "Solomon_treasure_2";
		break;
		
		case "Solomon_treasure_2":
			DialogExit();
			AddQuestRecord("Holl_Gambit", "2-17");
			pchar.questTemp.HWIC.Eng = "AbigileInChurch";
			sld = characterFromId("Abigile");
			sld.greeting = "abigile_3";
			ChangeCharacterAddressGroup(sld, "Villemstad_church", "goto", "goto1");//Аби в церковь
		break;
		
//----------------------------------------------против всех---------------------------------------------	
		
		case "Abigile_kidnap":
			dialog.text = "A letter? You don't say so! Mynheer Rodenburg is a step away from being my son-in-law. Blow! I like him!";
			link.l1 = "Listen, I don't give a shit who your son-in-law is. I am obliged to give this letter to Abigail. Do you know where can I find her? And who are you?";
			link.l1.go = "Abigile_kidnap_1";
		break;
		
		case "Abigile_kidnap_1":
			dialog.text = "Who am I? I am her father Solomon... And I don't like you, young man.";
			link.l1 = "You know, I'd start worrying, if you say you like me... So, are you going to keep shitting on me, or will you just call Abigail? I repeat once again, I am a messenger! I have a letter for your daughter!";
			link.l1.go = "Abigile_kidnap_2";
		break;
		
		case "Abigile_kidnap_2":
			dialog.text = "Give this letter to me. I will hand it over to my daughter.";
			link.l1 = "Who has pissed in your porridge this morning? Sorry, but I have orders to give this message to her personally. I wasn't told a word about her father. So I am repeating myself - where can I find Abigail?";
			link.l1.go = "Abigile_kidnap_3";
		break;
		
		case "Abigile_kidnap_3":
			dialog.text = "As soon as I scream, young man, all soldiers will be here at once, don't be so stubborn.";
			link.l1 = "Jesus! Really? And then what? Since when delivering letters is a crime? Don't be ridiculous!";
			link.l1.go = "Abigile_kidnap_4";
		break;
		
		case "Abigile_kidnap_4":
			DialogExit();
			sld = characterFromId("Abigile");
			ChangeCharacterAddressGroup(sld, "Villemstad_houseSP2", "reload", "reload1");
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "Abigile_GoOver":
			dialog.text = "Are you kidding? You've excited my poor girl with that message... She decided to follow that rotten captain! She sailed away on a ship of opportunity. Ah, what shall this old Jew do now? Do me a favour, young man, leave my house at once.";
			link.l1 = "How about that! Apparently, she could not wait...";
			link.l1.go = "Abigile_GoOver_1";
		break;
		
		case "Abigile_GoOver_1":
			DialogExit();
			AddQuestRecord("Holl_Gambit", "3-69");
			CloseQuestHeader("Holl_Gambit");
			pchar.questTemp.HWIC.Self = "end";
			pchar.questTemp.HWIC.Detector = "self_fail";
		break;
		
		case "Solomon_history":
			PlaySound("VOICE\Russian\hambit\Solomon Shneur-03.wav");
			dialog.text = "How does it look like? It's just an island with no decent people but me and Abigail. There I have hidden my chest, prevented that pirate monster to take it. Everything I had honestly earned was there...";
			link.l1 = "Tell me, Solomon, perhaps, you could recall the name of the flute your daughter was talking about? And what was her captain's name?";
			link.l1.go = "Solomon_history_1";
		break;
		
		case "Solomon_history_1":
			dialog.text = "Hmm... Well, I do not know. And why are you asking, young man?";
			link.l1 = "I just want to help your daughter, Solomon. I cannot promise anything, but I'd like to try. My former boss had treated her badly, and after that I think I am obliged to help her to settle down somehow.";
			link.l1.go = "Solomon_history_2";
		break;
		
		case "Solomon_history_2":
			dialog.text = "Well, if it is so...";
			link.l1 = "";
			link.l1.go = "Solomon_history_3";
			pchar.questTemp.HWIC.Self = "SolomonHistoryNext";
		break;
		
		case "Solomon_history_3":
			DialogExit();
			sld = characterFromId("Abigile");
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "Solomon_thanks":
			dialog.text = "Young man! Wait!";
			link.l1 = "Yes?";
			link.l1.go = "Solomon_thanks_1";
		break;
		
		case "Solomon_thanks_1":
			dialog.text = "Young man! I would like to thank you for everything you've done for me and my daughter. You saved us. I am sorry for giving you a hard welcome the first time we met and for my doubts in your sincere desire to help. Please, forgive the old Jew. Now tell me, haven't you found anything else except my money in the grotto?";
			link.l1 = "No, Solomon. There was nothing but money. I had to fight with van Berg's cutthroats - it was him who sunk your ship months ago. It might be that they had already stolen something... And what else was supposed to be there?";
			link.l1.go = "Solomon_thanks_2";
		break;
		
		case "Solomon_thanks_2":
			dialog.text = "Nothing important... One ancient relic... Well, nevermind! Forget about this rarity! And... Just one more thing, young man... ";
			link.l1 = "Go on.";
			link.l1.go = "Solomon_thanks_3";
		break;
		
		case "Solomon_thanks_3":
			dialog.text = "You... well, I have found out something about you. Our governor holds you on a high esteem, and you are a notable captain. I'll tell you a secret... my daughter likes you a lot. She told me that herself. Maybe... you will think about this? Abigail is a very good girl, I assure you.";
			link.l1 = "Oh, boy... It's not that straight forward, Solomon. But your daughter is a rare jewel indeed. You take good care of her.";
			link.l1.go = "Solomon_thanks_4";
		break;
		
		case "Solomon_thanks_4":
			dialog.text = "Think it over, young man. Think again and come back!";
			link.l1 = "Bye, Solomon.";
			link.l1.go = "Solomon_thanks_5";
		break;
		
		case "Solomon_thanks_5":
			DialogExit();
			LocatorReloadEnterDisable("Villemstad_houseSp2", "reload1", false);
			AddQuestRecord("Holl_Gambit", "3-65");
			NextDiag.CurrentNode = "First time";
		break;
		
		case "Solomon_poor":
			dialog.text = "Heh... Sometimes it is impossible to start a new life, young man. To live in poverty - what can be worse for an old man?";
			link.l1 = "I am sorry, Solomon. Stand firm.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Solomon_poor";
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		//--> блок реагирования на попытку залезть в сундук
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("You are a "+ GetSexPhrase("thief, mister! Guards, take him","thief, girl! Guards, take her") +"!!!", "Just look at that! As soon as I was lost in contemplation, you decided to check my chest! Take the thief!!!", "Guards! Robbery! Take the thief!!!");
			link.l1 = "Damn it!";
			link.l1.go = "exit";
			LAi_group_Attack(NPChar, Pchar);
		break;
		//<-- блок реагирования на попытку залезть в сундук
	}
}
