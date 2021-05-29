// Addon-2016 Jason, французские миниквесты (ФМК) Тортуга
void ProcessDialogEvent()
{
	ref sld, NPChar;
	aref Link, NextDiag;
	int i;
	string sTemp;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "An obvious bug. Tell the devs about it.";
			link.l1 = "Oh, I will.";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
		case "girl":
			PlaySound("VOICE\Russian\Girls_1.wav");
			dialog.text = "Oh, hello monsieur! Welcome to Tortuga! Such noble captains like you are rare guests here...";
			link.l1 = "Greetings, mademoiselle. Thank you for a warm welcome. But how so? I thought that such important port was always a place of interest for people much more noble than me.";
			link.l1.go = "girl_1";
		break;
		
		case "girl_1":
			dialog.text = "Ah monsieur... You are a newcomer, am I right? You'll see it by yourself. You have no idea how hard it is to find worthy men for a dancing party in the governor's palace. Perhaps you...";
			link.l1 = "How can I be of service to such a beautiful woman?";
			link.l1.go = "girl_2";
		break;
		
		case "girl_2":
			dialog.text = "(giggle) Perhaps, you could pay us a visit by six o'clock tonight? Our governor's wife is regularly hosting informal parties in the servant's room. It's rare chance to get an intriguing company for such events. Will you pay us a visit? Please come, we'd be so delighted.";
			link.l1 = "I'd be honored mademoiselle. I will pay you a visit tonight.";
			link.l1.go = "girl_3";
			link.l2 = "Forgive me mademoiselle, but I have an urgent business to attend to. Another time, perhaps?";
			link.l2.go = "girl_exit";
		break;
		
		case "girl_exit":
			dialog.text = "Pity. I'll have to find another... company. Farewell.";
			link.l1 = "Farewell.";
			link.l1.go = "girl_exit_1";
		break;
		
		case "girl_exit_1":
			DialogExit();
			chrDisableReloadToLocation = false;
			LAi_ActorGoToLocation(npchar, "reload", "reload3_back", "none", "", "", "", 40.0);
			npchar.lifeday = 0;
			FMQT_ClearChest();
		break;
		
		case "girl_3":
			dialog.text = "It will be our pleasure! Thank you! I promise you, this is going to be interesting. (giggles) See you tonight!";
			link.l1 = "See you...";
			link.l1.go = "girl_4";
		break;
		
		case "girl_4":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload3_back", "none", "", "", "", 40.0);
			npchar.lifeday = 0;
			pchar.questTemp.FMQT = "begin_serveroom";
			FMQT_Begin();
			AddQuestRecord("FMQ_Tortuga", "1");
		break;
		
		case "girl_5":
			PlaySound("VOICE\Russian\Girls_1.wav");
			dialog.text = "Hey there, handsome! We rarely have such fine men arriving to our port.";
			link.l1 = "Hey to you too, pretty one. One fine man has arrived to your port after all. Got a lot of things to do, but I hope that this island can offer enough entertainment options for a sea wolf such as me.";
			link.l1.go = "girl_6";
		break;
		
		case "girl_6":
			dialog.text = "(giggle) Oh yes. Tortuga always has something to offer. As have I. One sailor, no - one captain even, has told me about how he managed to avoid a certain death in sea by making a raft of sea turtles. What a man! Could you?";
			link.l1 = "Could I what?";
			link.l1.go = "girl_7";
		break;
		
		case "girl_7":
			dialog.text = "(giggle) Could you lash sea turtles?";
			link.l1 = "Sure. I am a captain. I can do that. Want me to show you?";
			link.l1.go = "girl_8";
		break;
		
		case "girl_8":
			dialog.text = "Later maybe. I work as a servant in our governor's palace. Come there by six o'clock tonight and find me and my friend in a bower. You will tell us about your adventures, will you?";
			link.l1 = "He-he. Sure, pretty one. I will tell and show. See you by six tonight.";
			link.l1.go = "girl_9";
			link.l2 = "A bower? In a governor's palace? I'll pass, dear. Find me in a tavern if you'll want company.";
			link.l2.go = "girl_exit_2";
		break;
		
		case "girl_exit_2":
			dialog.text = "Ph-f. Whatever, I'll find a more intriguing man for us. Farewell, stallion.";
			link.l1 = "Good luck in finding...";
			link.l1.go = "girl_exit_1";
		break;
		
		case "girl_9":
			dialog.text = "Looking forward to this!";
			link.l1 = "...";
			link.l1.go = "girl_10";
		break;
		
		case "girl_10":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload3_back", "none", "", "", "", 40.0);
			npchar.lifeday = 0;
			pchar.questTemp.FMQT = "begin_bedroom";
			FMQT_Begin();
			AddQuestRecord("FMQ_Tortuga", "2");
		break;
		
		case "wife":
			PlaySound("VOICE\Russian\Dama03.wav");
			dialog.text = "Ah there you are! Captain "+GetFullName(pchar)+"! I am so glad to meet you, it's been a while since I had a visitor of your nobility and stature!";
			link.l1 = "It is a great honor and pleasure for me to be here in your company. But what about the rest of the guests? Am I too early?";
			link.l1.go = "wife_1";
		break;
		
		case "wife_1":
			dialog.text = "No need for others today. Let's drink wine and talk. Ah, if you'd only knew how boring and lonely I feel here! This is a village inhabited by pirates! Pirates! And, at last, a worthy man in my house! I wish my husband were doing business with people of your class and talents! Pirates, pirates everywhere! Have you heard about that new fashion growing popular in Paris and in His Majesty's Royal Court? What is your opinion about this?";
			link.l1 = "I am sorry, about what exactly? Pirates? Or fashion?";
			link.l1.go = "wife_2";
		break;
		
		case "wife_2":
			dialog.text = "You understand me so well! I can't even believe this. My husband gives me pennies while he makes MILLIONS on his pirates, imagine that! Pirates! I have to order dresses here, in this dirty hole, but how a woman of my status can wear such rags? Oh, I so want to see and wear these fashions of Paris! Do you think I'd be looking lovely in those?";
			link.l1 = "Madame, you look lovely. You don't need fashions from Paris for this, it's already obvious for every man of this beautiful island.";
			link.l1.go = "wife_3";
		break;
		
		case "wife_3":
			dialog.text = "You are too kind to me... Captain, I must to confess, I am in a great trouble. But you will help a poor woman, won't you?";
			link.l1 = "Sure, madame. Anything you wish.";
			link.l1.go = "wife_4";
		break;
		
		case "wife_4":
			PlaySound("VOICE\Russian\Dama02.wav");
			dialog.text = "Careful there, monsieur captain, or I will loose my head. (giggle) My husband doesn't give me a single centime lately, this dog brings courtesans to our house and pays me no attention!\nI know where he keeps a pathetic share of his treasures, it's in a chest in his office. This is my money as well by the right of a wife and a woman. Help me to get what he owes me and you'll be rewarded... With gold and... who knows.";
			link.l1 = "This... is an interesting offer. Very well, madame, I will help you. Where is this chest and how to open it?";
			link.l1.go = "wife_5";
			link.l2 = "Very well, pretty one, I will get you the chest's contents. We will get the money and have a very pleasant time together. What man can decline such an offer? Where is this chest and how to open it?";
			link.l2.go = "wife_6";
			link.l3 = "I am sorry, madame, but my honor demands to decline your offer. You have my sympathies, you deserve better, but you'll have to find yourself another performer for this play.";
			link.l3.go = "wife_exit";
		break;
		
		case "wife_exit":
			dialog.text = "Pity. We have nothing more to talk about then, monsieur. Leave me and remember: you will regret telling my husband about this!";
			link.l1 = "Farewell.";
			link.l1.go = "wife_exit_1";
		break;
		
		case "wife_exit_1":
			DialogExit();
			chrDisableReloadToLocation = false;
			DeleteAttribute(pchar, "questTemp.FMQT.Common");
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeday = 0;
			pchar.questTemp.FMQT = "huber";
			pchar.quest.FMQT_late1.win_condition.l1 = "Timer";
			pchar.quest.FMQT_late1.win_condition.l1.date.hour  = 18.0;
			pchar.quest.FMQT_late1.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.FMQT_late1.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.FMQT_late1.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.FMQT_late1.function = "FMQT_HuberTime";
			AddQuestRecord("FMQ_Tortuga", "4");
		break;
		
		case "wife_5":
			pchar.questTemp.FMQT.Honour = "true"; // вар 1
			dialog.text = "I didn't expect this from you... The chest... Leave it for later, first, we should return a duplicate key which was stolen by some filthy pirate. He is having a good time in a local den, drinking like a pig. Make haste and bring the duplicate to me. I will be waiting for you.";
			link.l1 = "No wasting time then!";
			link.l1.go = "wife_7";
		break;
		
		case "wife_6":
			pchar.questTemp.FMQT.Bed = "true"; // вар 2 
			dialog.text = "You won't regret this, captain. And you are right, what man can decline such an offer? First, we should return a duplicate key which was stolen by some filthy pirate. He is having a good time in a local den, drinking like a pig. Make haste and bring the duplicate to me. I will be waiting for you.";
			link.l1 = "No wasting time then!";
			link.l1.go = "wife_7";
		break;
		
		case "wife_7":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "FMQT_PirateInTavern", 10.0);
			pchar.quest.FMQT_late2.win_condition.l1 = "Timer";
			pchar.quest.FMQT_late2.win_condition.l1.date.hour  = 0.0;
			pchar.quest.FMQT_late2.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.FMQT_late2.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.FMQT_late2.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.FMQT_late2.function = "FMQT_TavernTime";
			AddQuestRecord("FMQ_Tortuga", "6");
		break;
		
		case "wife_8":
			PlaySound("VOICE\Russian\Dama03.wav");
			dialog.text = "Captain "+GetFullName(pchar)+"! What a man in my bower! Are you surprised? You are the only guest here tonight. (giggle)";
			link.l1 = "I am surprised, madame. But I don't mind at all. Shall we enjoy ourselves? Or do you have a business proposal to me?";
			link.l1.go = "wife_9";
		break;
		
		case "wife_9":
			dialog.text = "What a direct approach! I like men like you. I have a business proposal to you, captain. I will find a way to compensate your efforts if you succeed.";
			link.l1 = "Go on.";
			link.l1.go = "wife_10";
		break;
		
		case "wife_10":
			dialog.text = "Ah... My husband have a chest full of money and jewelry. I hate him and I want a better wife's share.";
			link.l1 = "Madame, you look lovely. You don't need fashions from Paris for this, it's already obvious for every man of this beautiful island.";
			link.l1.go = "wife_11";
		break;
		
		case "wife_11":
			dialog.text = "You are too kind to me... Captain, I must to confess, I am in a great trouble. But you will help a poor woman, will you?";
			link.l1 = "Sure, madame. Anything you wish.";
			link.l1.go = "wife_12";
		break;
		
		case "wife_12":
			PlaySound("VOICE\Russian\Dama02.wav");
			dialog.text = "Careful there, monsieur captain, or I will loose my head. (giggle) My husband doesn't give me a single centime lately, this dog brings courtesans to our house and pays me no attention!\nI know where he keeps a pathetic share of his treasures, it's in a chest in his office. This is my money as well by the right of a wife and by the of a woman. Help me get what he owes me and you will be rewarded... With gold and... who knows.";
			link.l1 = "Fine. I will do it. Where is this chest and how to open it?";
			link.l1.go = "wife_13";
			link.l2 = "Ha! No questions there, I can do that for such a woman like you. You won't regret it, beauty. We will get the money and have a very pleasant time together. Where is this chest and how to open it?";
			link.l2.go = "wife_14";
			link.l3 = "No way, pretty one. To clean out a governor? I won't do that. Not in this manner anyway. Find yourself another performer for this play.";
			link.l3.go = "wife_exit_2";
		break;
		
		case "wife_13":
			pchar.questTemp.FMQT.Honour = "true"; // вар 1
			dialog.text = "Oh... I like you more and more... First, we should return a duplicate key which was stolen by some filthy pirate. He is having a good time in a local den, drinking like a pig. Make haste and bring the duplicate to me. I will be waiting for you.";
			link.l1 = "No wasting time then!";
			link.l1.go = "wife_7";
		break;
		
		case "wife_14":
			pchar.questTemp.FMQT.Bed = "true"; // вар 2 
			dialog.text = "Keep your cool, sweetie. (giggle) First, we should return a duplicate key which was stolen by some filthy pirate. He is having a good time in a local den, drinking like a pig. Make haste and bring the duplicate to me. I will be waiting for you. You sure you can manage that?";
			link.l1 = "Have any doubt? Don't! I am already on my way.";
			link.l1.go = "wife_7";
		break;
		
		case "wife_exit_2":
			dialog.text = "Brat! Get out of my sight! And don't even think to tell my husband about this! Or you'll regret it!";
			link.l1 = "Bye, sweetheart.";
			link.l1.go = "wife_exit_1";
		break;
		
		case "wife_15":
			PlaySound("VOICE\Russian\Dama03.wav");
			pchar.quest.FMQT_late3.over = "yes";
			dialog.text = "Captain! Did you get the duplicate?";
			link.l1 = "Yes, I have it. Where is the chest?";
			link.l1.go = "wife_16";
		break;
		
		case "wife_16":
			dialog.text = "Oh my! Is this vile creature actually going to get what he deserves? You are an incredible man, captain! You have a great future ahead, do you know that? Forget the chest. I'll do it myself. Come see me tomorrow to get your reward. You won't regret it, captain...";
			link.l1 = "Fine. Have it you way. Looking forward to see you tomorrow.";
			link.l1.go = "wife_17";
			link.l2 = "No, I am a busy man and I don't want to waste time waiting. Why wait? Tell me what has to be done and I will do it. I can't let such a beautiful woman to spoil her pretty little hands.";
			link.l2.go = "wife_18";
		break;
		
		case "wife_17":
			RemoveItems(pchar, "kaleuche_key", 1);
			ChangeItemDescribe("kaleuche_key", "itmdescr_kaleuche_key");
			dialog.text = "Come see me by six o'clock, my knight...";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("FMQT_Deceive");
		break;
		
		case "wife_18":
			dialog.text = "Are you sure? It might be dangerous for you. Why do you want to put your life at risk, captain? Change you mind, please, I am begging you!";
			link.l1 = "Fine. Have it you way. Looking forward to see you tomorrow.";
			link.l1.go = "wife_17";
			link.l2 = "I've made my decision already. What should I do exactly?";
			link.l2.go = "wife_19";
		break;
		
		case "wife_19":
			dialog.text = "A lion heart!... Go to my husband's office and find a proper chest for the duplicate. No one is going to be there, so take your time. There are.. diamonds inside that chest. A great number of them. Take them all and return to me. I will be waiting. You will not trick the poor woman, I know that...";
			link.l1 = "I'll be back soon.";
			link.l1.go = "wife_20";
		break;
		
		case "wife_20":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			AddQuestRecord("FMQ_Tortuga", "11");
			sld = &Locations[FindLocation("Tortuga_townhallRoom")];
			sld.private2.key = "kaleuche_key"; // допуск к сундуку
			pchar.questTemp.FMQT = "chest";
		break;
		
		case "wife_21":
			pchar.quest.FMQT_GemsTimeOver.over = "yes";
			PlaySound("VOICE\Russian\Dama01.wav");
			dialog.text = "Oh, captain! I...You... Is it done? Oh and who is this?! A-ah!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("FMQT_MercenAttackRoom");
		break;
		
		case "wife_22":
			dialog.text = "Oh my! Captain you've saved me! You.. you are the man! It was my husband's thug, he wanted to kill you! I begged him not to! Are you hurt? Did you bring the diamonds?";
			link.l1 = "Ha. Really? Your husband is an extremely delicate man... Fuck him. I have the stones.";
			link.l1.go = "wife_23";
		break;
		
		case "wife_21x":
			pchar.quest.FMQT_GemsTimeOver.over = "yes";
			PlaySound("VOICE\Russian\Dama01.wav");
			dialog.text = "Oh captain! I... You... Is it done?";
			link.l1 = "There was a minor complication, but it's settled now. Why are you pale, madame? Are you alright? I have the stones, this news will cheer you up, am I right?";
			link.l1.go = "wife_23";
		break;
		
		case "wife_23":
			dialog.text = "Thank God! I am avenged! My knight! How many diamonds were there?";
			if (GetCharacterItem(pchar, "jewelry2") >= 100)
			{
				link.l1 = "Your knight is back from his adventure with a full sack of loot. He will leave a half of it to his dame so she could buy the very best fashions from Paris. I kept my promise to you.";
				if (CheckAttribute(pchar, "questTemp.FMQT.Honour")) link.l1.go = "wife_25";
				else link.l1.go = "wife_26";
			}
			else
			{
				link.l1 = "There were plenty of diamonds but you will get nothing. You hired an assassin to kill me, whore! Do you really believe that I will share with you after all of this? Try to open your mouth and your husband will learn about your plan to rob him. So keep it shut.";
				link.l1.go = "wife_24";
			}
		break;
		
		case "wife_24":
			dialog.text = "Scoundrel! Bastard! You won't get away with this!";
			link.l1 = "Yeah, yeah...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("FMQT_FinalNoJewelry");
		break;
		
		case "wife_25":
			RemoveItems(pchar, "jewelry2", 100);
			Log_Info("You have given diamonds");
			PlaySound("interface\important_item.wav");
			dialog.text = "You are not like... the rest of them. You get what you want. You have a bright future ahead of you, you are a busy man but... Will you stay with me for a bit? No one will disturb us, I promise.";
			link.l1 = "I always have time for such woman like you. Shall we open wine?";
			link.l1.go = "wife_sex";
		break;
		
		case "wife_sex":
			DialogExit();
			pchar.questTemp.HorseQty = sti(pchar.questTemp.HorseQty) + 1;
			DoQuestCheckDelay("PlaySex_1", 1.0);
		break;
		
		case "wife_26":
			RemoveItems(pchar, "jewelry2", 100);
			Log_Info("You have given diamonds");
			PlaySound("interface\important_item.wav");
			dialog.text = "I think I can live without them. There are plenty of options to spend money here. So many handsome and worthy men on Tortuga... Thank you for everything captain. Keep quite about this or my husband will bury you in a ditch, although he is not a bad man, do you that? Farewell.";
			link.l1 = "Just like that? That was an instructive experience. Farewell, madame, I suggest you keep quite about this too, I am not a good man. But you already know that, right?";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("FMQT_FinalNoSex");
		break;
		
		case "wife_27":
			PlaySound("VOICE\Russian\Girls_2.wav");
			dialog.text = "Who are you and what are you doing here?";
			link.l1 = "Hm... We had a deal...";
			link.l1.go = "wife_28";
		break;
		
		case "wife_28":
			dialog.text = "What deal, monsieur? I am a married woman, I don't do business with other men! Leave my bower now or I am calling my husband and his guards!";
			link.l1 = "Just like that, huh? Very well, I am gonna enlighten your good husband in no time!";
			link.l1.go = "wife_29";
		break;
		
		case "wife_29":
			dialog.text = "Leave now, you insolent fellow, or they will throw you into the most wet and dark chamber of fort La Roche! I don't care about your threats! Get out!";
			link.l1 = "...";
			link.l1.go = "wife_30";
		break;
		
		case "wife_30":
			DialogExit();
			DoQuestReloadToLocation("Tortuga_town", "reload", "reload3", "FMQT_FinalFail");
		break;
		
		case "pirate":
			PlaySound("VOICE\Russian\tavern\Pyanici-03.wav");
			pchar.quest.FMQT_late2.over = "yes";
			FreeSitLocator("Tortuga_tavern", "sit_base2");
			dialog.text = "Who are you? Ah, whatever. Don't trust women, pal. Even the dumbest of them can drag you to the bottom with their man-mani-ipulations. Take a sit, let's have a drink!";
			link.l1 = "With pleasure!";
			link.l1.go = "pirate_1x";
		break;
		
		case "pirate_1x":
			DialogExit();
			LAi_Fade("", "");
			ChangeCharacterAddressGroup(pchar, "Tortuga_tavern", "sit", "sit_base2");
			LAi_SetSitType(pchar);
			npchar.Dialog.currentnode = "pirate_1";
			LAi_SetActorType(npchar);
			LAi_ActorSetSitMode(npchar);
			LAi_ActorDialogDelay(npchar, pchar, "", 2.0);
		break;
		
		case "pirate_1":
			PlaySound("VOICE\Russian\tavern\Pyanici-05.wav");
			dialog.text = "What are you staring at? Pour it up!!";
			link.l1 = "Here's to you!.. Hey friend, I am not going to waste time here. I need the duplicate key, you know what I am talking about. Give it to me and we'll part our ways: you will keep drinking and I will keep helping damsels in distress.";
			link.l1.go = "pirate_2";
		break;
		
		case "pirate_2":
			dialog.text = "Funny, but you look smarter than you really are. You work for that bitch? You know who is her husband? I used to think I know. Just recently, Levasseur has sent his loyal slave Kampacho to beat to death a respected merchant. This merchant had shown some sort of minor disrespect to the governor's wife during a ball or something. And this woman seduced me with her features and his doubloons\nThe duplicate key exists. I used to be a decent safebreaker back in France, so it was a child play. If it wasn't for a daughter of Lyons's commandant... I'd never gone pirate. Fuck it!";
			link.l1 = "This is all very sad, but let's talk business. Where is the duplicate key?";
			link.l1.go = "pirate_3";
		break;
		
		case "pirate_3":
			dialog.text = "Are you listening? I am out of this! I was smart enough to see what's coming! I am leaving this place forever as soon as my ship is ready to set sail. Do you want the key? Pay for it. Don't be greedy here, but I think you won't need any money pretty soon.";
			link.l1 = "You know, you are right. I don't want to be a woman's plaything. Thank you for an advice and be safe at sea!";
			link.l1.go = "pirate_4";
			link.l2 = "Pay for it? To you? You are a pathetic thief and a coward. You'd better had stayed in that shithole Lyons. Who knows, maybe the local commandant would had taken pity on you and allowed you to have fun with his daughter. I am not going to take pity on you, that's for sure. Give me the key or you will get hurt.";
			link.l2.go = "pirate_5";
			link.l3 = "How much?";
			link.l3.go = "pirate_6";
		break;
		
		case "pirate_4":
			dialog.text = "You have a bright head. It was a right decision, friend. Good luck. Hope you will find a true loving woman one day.";
			link.l1 = "Farewell pal...";
			link.l1.go = "pirate_exit";
		break;
		
		case "pirate_exit":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			LAi_Fade("", "");
			ChangeCharacterAddressGroup(pchar, "Tortuga_tavern", "tables", "stay3");
			LAi_SetPlayerType(pchar);
			pchar.questTemp.FMQT = "huber";
			pchar.quest.FMQT_late1.win_condition.l1 = "Timer";
			pchar.quest.FMQT_late1.win_condition.l1.date.hour  = 18.0;
			pchar.quest.FMQT_late1.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.FMQT_late1.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.FMQT_late1.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.FMQT_late1.function = "FMQT_HuberTime";
			AddQuestRecord("FMQ_Tortuga", "9");
		break;
		
		case "pirate_5":
			dialog.text = "Wh-at?! Die!";
			link.l1 = "Aargh!";
			link.l1.go = "pirate_duel";
		break;
		
		case "pirate_duel":
			DialogExit();
			LAi_SetSitType(npchar);
			// ключ квестовый от Калеуче - вернуть назад
			GiveItem2Character(npchar, "kaleuche_key");
			ChangeItemDescribe("kaleuche_key", "itmdescr_kaleuche_key_FMQT");
			i = makeint(MOD_SKILL_ENEMY_RATE/4);
			pchar.questTemp.FMQT = "duel";
			PChar.questTemp.duel.enemy = NPChar.id;
			if (MOD_SKILL_ENEMY_RATE > 2) PChar.questTemp.duel.enemyQty = i;
			AddDialogExitQuestFunction("Duel_Prepare_Fight");
		break;
		
		case "pirate_6":
			dialog.text = "You are a man of business, I'll give you that. You may actually make it through. Fifty doubloons. On the table.";
			link.l1 = "Fifty pieces? For you? Bite me. The key. On the table.";
			link.l1.go = "pirate_7";
			if (GetCharacterItem(pchar, "gold_dublon") >= 50)
			{
				link.l2 = "Quite the price... Fine. Take them.";
				link.l2.go = "pirate_8";
			}
			else
			{
				link.l2 = "Quite the price... Fine. I will bring them soon. Stay here.";
				link.l2.go = "pirate_wait";
			}
		break;
		
		case "pirate_wait":
			DialogExit();
			LAi_SetSitType(npchar);
			npchar.Dialog.currentnode = "pirate_dublon";
			LAi_Fade("", "");
			ChangeCharacterAddressGroup(pchar, "Tortuga_tavern", "tables", "stay3");
			LAi_SetPlayerType(pchar);
		break;
		
		case "pirate_dublon":
			NextDiag.TempNode = "pirate_dublon"; // mitrokosta правка явного бага
			dialog.text = "Did you bring fifty doubloons?";
			link.l1 = "You know, I think that you can live without them. The key. On the table.";
			link.l1.go = "pirate_7";
			if (GetCharacterItem(pchar, "gold_dublon") >= 50)
			{
				link.l2 = "Yeah. Take them.";
				link.l2.go = "pirate_8";
			}
			else
			{
				link.l2 = "In progress!";
				link.l2.go = "exit";
			}
		break;
		
		case "pirate_7":
			dialog.text = "Shall we dance?";
			link.l1 = "...";
			link.l1.go = "pirate_duel";
		break;
		
		case "pirate_8":
			RemoveItems(pchar, "gold_dublon", 50);
			//Log_Info("Вы отдали 50 дублонов");
			PlaySound("interface\important_item.wav");
			dialog.text = "Good. Use your brains and you might get out of this alive and with profit. Take the key and hear an advice. Free of charge. The Levasseur's girl is dumb as a fish yet she believes herself to be cunning. Don't trust her. Keep your balls under control and watch your pockets. She is not much of an opponent, just be careful and avoid bringing her husband into this\nOne last thing - there is a chest in her bower where she keeps her trinkets, easy to lock pick. She will bring her cut there. You heard me. Be safe at sea brother.";
			link.l1 = "See you pal...";
			link.l1.go = "pirate_9";
		break;
		
		case "pirate_9":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			LAi_Fade("", "");
			ChangeCharacterAddressGroup(pchar, "Tortuga_tavern", "tables", "stay3");
			LAi_SetPlayerType(pchar);
			pchar.questTemp.FMQT = "key";
			pchar.questTemp.FMQT.Caution = "true";
			FMQT_KeyNextDay();
			pchar.quest.FMQT_late3.win_condition.l1 = "Timer";
			pchar.quest.FMQT_late3.win_condition.l1.date.hour  = sti(GetTime());
			pchar.quest.FMQT_late3.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.FMQT_late3.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.FMQT_late3.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.FMQT_late3.function = "FMQT_KeyTime";
			AddQuestRecord("FMQ_Tortuga", "10");
			// ключ квестовый от Калеуче - вернуть назад
			GiveItem2Character(pchar, "kaleuche_key");
			ChangeItemDescribe("kaleuche_key", "itmdescr_kaleuche_key_FMQT");
		break;
		
		case "mercen":
			PlaySound("VOICE\Russian\EvilPirates10.wav");
			dialog.text = "Damn it! I didn't expect... Hell with the women! My master told me to avoid her kind. But job is job. I will get you after all.";
			link.l1 = "Well-well, pal... Looks like she wanted to screw me too, can't say I am surprised. Why should we keep fighting? Want a job? I got one. You have skill, I need people like you in my crew. Meal, bunk, wage and a fair share of plunder. What will you say?";
			if (sti(pchar.rank) > 5 && GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) > 25 && GetSummonSkillFromName(pchar, SKILL_FORTUNE) > 25) link.l1.go = "mercen_1";
			else link.l1.go = "mercen_4";
		break;
		
		case "mercen_1":
			dialog.text = "Can you afford this, huh, captain? You have got a tongue of silver, I'll give you that. Fine, I am in. What's you ship's name?";
			link.l1 = ""+pchar.ship.name+". Welcome aboard!";
			link.l1.go = "mercen_2";
		break;
		
		case "mercen_2":
			dialog.text = "He-he. This job just got better. Give the bitch a kick for me.";
			link.l1 = "...";
			link.l1.go = "mercen_3";
		break;
		
		case "mercen_3":
			DialogExit();
			LAi_group_Delete("EnemyFight");
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "FMQT_MercenHire", 10.0);
			AddQuestRecord("FMQ_Tortuga", "17");
		break;
		
		case "mercen_4":
			dialog.text = "You talk sweet. But not sweet enough if you want professionals to join your ranks. Keep that in mind in the future. If you'll have one.";
			link.l1 = "Give it a try. Be swift, I have a date with a dame.";
			link.l1.go = "mercen_5";
			link.l2 = "No second chances today. I am terribly busy so let's not spoil the carpet any longer? You are not being paid enough to die for some local whore. Did they pay you at all?";
			link.l2.go = "mercen_6";
		break;
		
		case "mercen_5":
			DialogExit();
			LAi_SetCurHPMax(npchar);
			LAi_GetCharacterMaxEnergy(npchar);
			LAi_SetImmortal(npchar, false);
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "FMQT_MercenDie");
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
		case "mercen_6":
			dialog.text = "You are right. No one has paid me YET but I'll fix this right now. Do whatever you want...";
			link.l1 = "...";
			link.l1.go = "mercen_7";
		break;
		
		case "mercen_7":
			DialogExit();
			LAi_SetCurHPMax(npchar); 
			LAi_GetCharacterMaxEnergy(npchar);
			LAi_group_Delete("EnemyFight");
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "OpenTheDoors", 10.0);
			AddQuestRecord("FMQ_Tortuga", "18");
			pchar.questTemp.FMQT.Roomfight = "true";
			FMQT_WifeFinalTalk();
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
