// Addon-2016 Jason, французские миниквесты (ФМК) Порт-о-Пренс
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
		
		case "officer":
			PlaySound("VOICE\Russian\z_arest_02.wav");
			dialog.text = "What's happening here, gentlemen? A fight?!";
			link.l1 = "Huh... Officer, I heard the waitress screaming and...";
			link.l1.go = "officer_1";
		break;
		
		case "officer_1":
			DialogExit();
			sld = CharacterFromID("FMQP_noble");
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "officer_2":
			dialog.text = "";
			link.l1 = ""+GetFullName(pchar)+". Captain "+GetFullName(pchar)+".";
			link.l1.go = "officer_3";
		break;
		
		case "officer_3":
			dialog.text = "You are free to go, captain. For now. I can see what happened here, we will summon you in case we have extra questions.";
			link.l1 = "Very well...";
			link.l1.go = "officer_4";
		break;
		
		case "officer_4":
			DialogExit();
			sld = CharacterFromID("FMQP_noble");
			sld.Dialog.currentnode = "noble_3";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "officer_5":
			PlaySound("VOICE\Russian\z_arest_02.wav");
			dialog.text = "What's happening here, gentlemen? A fight?!";
			link.l1 = "Uh-h.. Officer, I heard waitress's screaming for help and saw this nobleman being attacked by two thugs. I tried to save the poor sod but, alas, I failed. The bastards have killed him.";
			link.l1.go = "officer_6";
		break;
		
		case "officer_6":
			dialog.text = "Well-well... He is a Spanish! Why would he be here? Hm. And you are, monseniour?";
			link.l1 = ""+GetFullName(pchar)+". Captain "+GetFullName(pchar)+".";
			link.l1.go = "officer_7";
		break;
		
		case "officer_7":
			dialog.text = "Captain, you are free to go for now. Your words match to the waitress's. We will call you if need be.";
			link.l1 = "Very well...";
			link.l1.go = "officer_8";
		break;
		
		case "officer_8":
			DialogExit();
			DoQuestReloadToLocation("Portpax_town", "reload", "reload4", "");
		break;
		
		case "noble":
			PlaySound("VOICE\Russian\YoungMan03.wav");
			dialog.text = "Allow me to explain you everything, officer! My name is don Domingo Ortiz Albalate of Santo Domingo. I have arrived to Port-au-Prence on an invite from one young lass and made a stop in this establishment waiting for the appointed meeting. Less than in two hours I was attacked by dos maldita canalla, it would be quite tough for me if it wasn't for this kind senor who had shown a perfect timing by the way.";
			link.l1 = "Don Domingo Ortiz Albalate? Spanish?";
			link.l1.go = "noble_1";
		break;
		
		case "noble_1":
			dialog.text = "Precisely senor! Though I'd like to make a notion that my papers are in order. I am a Spanish of noble blood, I am not some pirata sucia!";
			link.l1 = "Don Domingo, you should come with me for investigation! We'll deal with everything. As for you...";
			link.l1.go = "noble_2";
		break;
		
		case "noble_2":
			DialogExit();
			sld = CharacterFromID("FMQP_off");
			sld.Dialog.currentnode = "officer_2";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "noble_3":
			PlaySound("VOICE\Russian\YoungMan01.wav");
			dialog.text = "Senor Captain! Senor Captain! I swear by my father's good name you are a noble man! I'd like to see you rewarded later when I will finish my business here. Please, honor me with a visit of my humble house in Santo Domingo! It's close to the city gates. I'll be waiting for you my buen caballero! Remember my name, it's don Domingo Ortiz Albalate!";
			link.l1 = "...";
			link.l1.go = "noble_4";
		break;
		
		case "noble_4":
			DialogExit();
			DoQuestReloadToLocation("Portpax_town", "reload", "reload4", "FMQP_AfterFightInTown");
		break;
		
		case "noble_5":
			PlaySound("VOICE\Russian\YoungMan03.wav");
			dialog.text = "Captain "+GetFullName(pchar)+"?! Oh! What a disaster! This is a massacre! What happened here, buen amigo? Who are these men?";
			link.l1 = "Glad to see you, don Domingo. These are... I came here to pay you a visit. See that guy over there? That's Ugo, your servant and he...";
			link.l1.go = "noble_6";
		break;
		
		case "noble_6":
			dialog.text = "Ugo?! Oh, no, you were tricked captain!";
			link.l1 = "I got it already. Three scumbags got inside your place, murdered your loyal Ugo - I have found his corpse already upstairs - and then set up an ambush for you. My arrival wasn't a part of their plan, I was going to stay here and wait for you, but... Had to put them down.";
			link.l1.go = "noble_7";
		break;
		
		case "noble_7":
			dialog.text = "Oh, Dios! You play your sword like a professional condottiere! It's good that you are on my side! Oh, my poor Ugo! He was nursing me since I was a child and now... to be murdered by some scum!";
			link.l1 = "Don Domingo, it looks like you are a trouble to someone. Your good servant knew about the danger, read this note. I've found it on a table.";
			link.l1.go = "noble_8";
		break;
		
		case "noble_8":
			ChangeItemDescribe("letter_parol", "itmdescr_letter_parol");
			RemoveItems(pchar, "letter_parol", 1);
			dialog.text = "Give me it... (reading) That can not be... oh, no! This is unbelievable! Uncle Luis... But...";
			link.l1 = "Got a clue already?";
			link.l1.go = "noble_9";
		break;
		
		case "noble_9":
			dialog.text = "Only suspicions... Dreadful suspicions senor! How could my mother's brother do such a thing to me?";
			link.l1 = "Mind to add a few more details to this? And, don Domingo, I am sorry, but relatives are often the worst enemies a human can have...";
			link.l1.go = "noble_10";
		break;
		
		case "noble_10":
			dialog.text = "You are right, mi buen amigo! I will tell you everything! You've saved me twice already and it seems that you are the only one I can trust right now! But let's leave this awful place, it makes me sick. I should note the alcaldo about this mess, they will do the cleaning and take care of poor Ugo. How about we share a few cups of best wine in the local tavern?";
			link.l1 = "By all means, senor! Let's go!";
			link.l1.go = "noble_11";
		break;
		
		case "noble_11":
			DialogExit();
			chrDisableReloadToLocation = false;
			DoQuestReloadToLocation("Santodomingo_tavern", "sit", "sit_base2", "FMQP_InSantoDomingoTavern");
		break;
		
		case "noble_12":
			LAi_SetSitType(pchar);
			PlaySound("VOICE\Russian\YoungMan02.wav");
			dialog.text = "So, my friend, allow me to tell you a short version of my family's story. My mother, donna Isabella Ortiz, married my father, marquis Ricardo Albalate, and took his family name as our customs tell us. Her brother, Luis Ortiz, used to be some sort of a commandant or a prison overseer in the colonies, but after the marriage he was appointed by my father to be a manager of a plantation not far from Portobello\nThis is a huge and wealthy plantation with a very serious income. After a tragic death of my parents in sea, I have inherited everything including the plantation. My uncle has kept his position and I was happy enough with the rent he paid me on a constant basis and always in time.";
			link.l1 = "Looks like your uncle...";
			link.l1.go = "noble_13";
		break;
		
		case "noble_13":
			dialog.text = "Yes. He is nothing but a manager. I own the facility, not him. If anything happens to me - it will become his property.";
			link.l1 = "You know, Domingo, I knew people who would have all their relatives murdered in cold blood for a prize much less juicy than yours.";
			link.l1.go = "noble_14";
		break;
		
		case "noble_14":
			dialog.text = "My loyal Ugo mentioned in his death note about my uncle's papers... This is a direct clue. Oh, I don't want to believe in this! But... my cousin, Margarita Ortiz, who lives in Spain was betrothed not long ago. Might it be the cause my good captain?";
			link.l1 = "Why not. Your kind uncle might be in a sudden need of money...";
			link.l1.go = "noble_15";
		break;
		
		case "noble_15":
			dialog.text = "Money?! But of course... but don't forget a title of marquis! This will make my cousin a proper match to her future husband! Oh heaven! How stupid I was!";
			link.l1 = "I assume, such title costs much more than the plantation...";
			link.l1.go = "noble_16";
		break;
		
		case "noble_16":
			dialog.text = "Wait my friend! It wasn't the first attempt on my life! I had an encounter with some beggar in the street a few weeks ago! The drunk bastard offended me in a manner I couldn't ignore. He turned out to be a very decent fencer, he even managed to wound me with his rapier... before I killed him.";
			link.l1 = "And how did you end up in a tavern of Port-au-Prence? You mentioned some young lass?";
			link.l1.go = "noble_17";
		break;
		
		case "noble_17":
			dialog.text = "(turning red) Right...Yes captain, there was a young and pretty lass on the scene... now I see that she was a part of the trap. Bastards, bastards are everywhere, can't trust anyone! Poor Ugo... and he is dead now.";
			link.l1 = "You should do something about it, senor Domingo. How about leaving to Spain in secret?";
			link.l1.go = "noble_18";
		break;
		
		case "noble_18":
			dialog.text = "To Spain? And to leave my plantation? No way, captain, my name is marquee Domingo Ortiz Albalate!";
			link.l1 = "But...";
			link.l1.go = "noble_19";
		break;
		
		case "noble_19":
			dialog.text = "My friend, may I ask for your help? With Ugo being dead I have no people by my side I can trust. You've saved me twice already! Twice! I owe you a great deal, I am forever in your debt and yet I dare ask you for another favor. I swear by my noble title, I will make it worth your while!";
			link.l1 = "What can I do for you, senor?";
			link.l1.go = "noble_20";
		break;
		
		case "noble_20":
			dialog.text = "Let's go to Portobello, to my plantation! I know that my uncle is in Cartagena at the moment. Ugo mentioned some papers, so let's check don Luis Ortiz's books and documents! We might find something which will help us to drag out his filthy nature. It's quite a distance to Portobello but I'll pay you in full for the voyage!!";
			link.l1 = "It would be absurd to reject you at this point, don Domingo. I am in.";
			link.l1.go = "noble_21";
		break;
		
		case "noble_21":
			AddMoneyToCharacter(pchar, 20000);
			dialog.text = "I knew you would help me out, cabaliero! Here, take these twenty thousand pesos as payment for the voyage to Portobello. When do we set sail? We should hurry before my uncle returns from Cartagena!";
			link.l1 = "Let's waste no time then.";
			if (CheckCharacterItem(pchar, "HolTradeLicence") && GetDaysContinueNationLicence(HOLLAND) >= 20) link.l1.go = "noble_22";
			else link.l1.go = "noble_22x";
		break;
		
		case "noble_22x":
			GiveNationLicence(HOLLAND, 20);
			dialog.text = "Here's a license of Dutch West Indian Company. I have a filled paper for twenty days, let's just put your name in it. Done. This should help you to avoid any troubles.";
			link.l1 = "Great!";
			link.l1.go = "noble_22";
		break;
		
		case "noble_22":
			dialog.text = "Am I now allowed to come on board of your ship, my friend?";
			link.l1 = "Sure. As soon as we get the right wind - we set sail.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("FMQP_OnBoard");
		break;
		
		case "noble_23":
			PlaySound("VOICE\Russian\YoungMan03.wav");
			dialog.text = "So, captain, here we are. Now we should find my uncle's house and check what's inside.";
			link.l1 = "I assume, I shouldn't expect any problems with the guard?";
			link.l1.go = "noble_24";
		break;
		
		case "noble_24":
			dialog.text = "No. Although... hm. There is a chance that Luis has turned them against me. At any rate, being cautious is never a bad idea. Let's find the house we need.";
			link.l1 = "Don't you know it already? It's your plantation.";
			link.l1.go = "noble_25";
		break;
		
		case "noble_25":
			dialog.text = "Hm.. To be completely honest, last time I've been here when I was a kid... Yet I intend to fix this as soon as possible!";
			link.l1 = "I see. Then let's start looking. Your uncle's house must be the biggest one here.";
			link.l1.go = "noble_26";
		break;
		
		case "noble_26":
			DialogExit();
			chrDisableReloadToLocation = false;
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			AddQuestRecord("FMQ_Portpax", "7");
		break;
		
		case "noble_27":
			dialog.text = "What do you have here, my friend?";
			link.l1 = "Take a look, Domingo. Looks like accounting records. This might be interesting.";
			link.l1.go = "noble_28";
		break;
		
		case "noble_28":
			ChangeItemDescribe("Almanac", "itmdescr_Almanac");
			RemoveItems(pchar, "Almanac", 1);
			dialog.text = "(reading) Hm... Yeah. Look at this... Oh! One hundred thousand pesos! And another one hundred and fifty thousand! And here... (turning over pages) My good uncle Luis!";
			link.l1 = "Anything of interest?";
			link.l1.go = "noble_29";
		break;
		
		case "noble_29":
			dialog.text = "Anything of interest! My precious uncle had an income five times bigger than he was telling me! Thief!";
			link.l1 = "Can't say I am surprised. You can't put a total trust in anyone without checking the actual state of business from time to time.";
			link.l1.go = "noble_30";
		break;
		
		case "noble_30":
			dialog.text = "You are right as always, captain! My scum relative is stealing from me! This is my fault only... but I will fix this. I own this plantation and my uncle is fired since today! He is no one!";
			link.l1 = "Don Domingo... Don't you think that your uncle might disagree with such decision?";
			link.l1.go = "noble_31";
		break;
		
		case "noble_31":
			dialog.text = "I don't give a damn whether he agree or don't! I am marquee Domingo Ortiz Albalate and Luis Ortiz is nothing but a manager! And he...";
			link.l1 = "Keep calm. You are an unfamiliar bird here and as for you uncle... he practically owns this place. Think of the guards. You sure they will choose your side?";
			link.l1.go = "noble_32";
		break;
		
		case "noble_32":
			dialog.text = "Hm... I get your point. Maybe... But soldiers will never dare to raise a hand on a Spanish grandee! My uncle can challenge me if he will dare!";
			link.l1 = "Still, I suggest going another path. How about the court of law?";
			link.l1.go = "noble_33";
		break;
		
		case "noble_33":
			dialog.text = "Ha! You are right, my friend. We are leaving this place to address proper authorities. My uncle made a mistake by making notes about his dealings with smugglers in his accounting books. He used to buy slaves from them for very cheap. These books will do us a great service, I doubt that the bastard will be able to harm me in any way while sitting in the dungeons. Let's go my caballero! To Portobello!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("FMQP_PrepareUncle");
		break;
		
		case "noble_34":
			dialog.text = "This is nothing but a filthy and insolent lie! How dare him to spoil a good memory of my parents with his unworthy tongue! Damn it, I will make him pay for this! Take your sword, you assassin-hiring-scum!";
			link.l1 = "";
			link.l1.go = "noble_35";
		break;
		
		case "noble_35":
			DialogExit();
			sld = CharacterFromID("FMQP_Uncle");
			sld.Dialog.currentnode = "uncle_3";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "noble_36":
			PlaySound("VOICE\Russian\YoungMan01.wav");
			dialog.text = "Uncle Luis is in the proper place for him - in hell... Caballero, you were sent to me by the very heavens! I am glad you didn't trust the word of this scum. To be honest, I feared that you will just leave me here alone to fight this bastard\nYes senor, I am not perfect myself but this... this filthy lie about me hiring pirates to murder my own parents! To blame me of this... this! Well, he had it coming after all. A well deserved fate.";
			link.l1 = "Glad we made it, don Domingo. What now? Hope we are not facing a charge for this?";
			link.l1.go = "noble_37";
		break;
		
		case "noble_37":
			dialog.text = "A charge? Ha-ha! Hell no, I will show any accusator this fine accounting book with all uncle's illegal operations in it. Plus, let's not forget about several attempts on my life, we've got a great number witnesses after the last one. Don't worry about it, mi buen amigo. This is my place, it's time to show them all!";
			link.l1 = "Please be a bit more soft on this, senor. Let them think better of you than they had thought about your late uncle.";
			link.l1.go = "noble_38";
		break;
		
		case "noble_38":
			dialog.text = "That's the plan, captain. But I will show no mercy to anyone who dares to oppose me. Let me express my sincere gratitude for you, caballero! Please, go to a tavern, take a rest, have a cup or two. I'd be glad to join you, but you were right. It's time to grow wiser and take control over plantation myself. Come see me here tomorrow, captain!";
			link.l1 = "Very well, don Domingo. See you tomorrow.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("FMQP_PlantatonPause");
		break;
		
		case "noble_39":
			PlaySound("VOICE\Russian\YoungMan02.wav");
			dialog.text = "Ah, here you are my good friend!";
			link.l1 = "How are you doing, don Domingo? How is your plantation?";
			link.l1.go = "noble_40";
		break;
		
		case "noble_40":
			dialog.text = "Plantation's great, can't say the same about the money - turns out that my dear uncle had been transferring all the money to the bank of Cartagena. It will take a lot of lawyers' time to get my gold back. But it's alright, I can do that. Don't be sad captain, I will keep my promises to reward you for your nobility, honesty and friendship!";
			link.l1 = "Never had a thought about a reward when I was fighting on your side, senor...";
			link.l1.go = "noble_41";
		break;
		
		case "noble_41":
			dialog.text = "I know that, captain, and this says a lot about your character! Any good deed must be rewarded. So, although I don't have money at the moment, I will give orders to load your vessel with goods of my plantation. I mean coffee, a great batch of it. You will be able to sell it with a great profit I am sure.";
			link.l1 = "Oh! This is nice..";
			link.l1.go = "noble_42";
		break;
		
		case "noble_42":
			dialog.text = "Moreover, I have a few items of small value for me, but of great value for any sailor like yourself. A fine spyglass and three amulets. Please accept these, it's all yours now.";
			link.l1 = "Gratitude!";
			link.l1.go = "noble_43";
		break;
		
		case "noble_43":
			Log_Info("You have received a good spyglass");
			Log_Info("You have received three amulets");
			PlaySound("interface\important_item.wav");
			dialog.text = "Finally, I gift you with my rapier as a token of my immeasurable gratitude to you. She served me well, now let her serve you even better. Look at her and remember your good Spanish friend - marquee Domingo Albalate!";
			link.l1 = "Thank you so much, senor! I didn't expect...";
			link.l1.go = "noble_44";
		break;
		
		case "noble_44":
			Log_Info("You have received the Smallsword");
			PlaySound("interface\important_item.wav");
			RemoveCharacterEquip(npchar, BLADE_ITEM_TYPE);
			dialog.text = "And now, alas, I have to say my farewells. I should go to Portobello to see the governor and then to Cartagena... To sum up, my carefree existence is over, time live as a grown up man.";
			link.l1 = "Well, you are much smarter now...";
			link.l1.go = "noble_45";
		break;
		
		case "noble_45":
			dialog.text = "That's true. It was a pleasure, my friend! Come visit me sometime. Godspeed in the sea!";
			link.l1 = "Same to you in your plantation business, don Domingo!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("FMQP_ReceiveReward");
		break;
		
		case "noble_46":
			PlaySound("VOICE\Russian\YoungMan02.wav");
			dialog.text = "Eh, we are late senor! What a pity, my good old uncle has already made a decent cleaning job among his papers. Looks like he was told him about Santo-Domingo and he took precaution measures... But I am not going to leave it like that! I should to see the governor of Portobello to initiate a legal procedure versus my uncle. I had enough of him managing my wealth.";
			link.l1 = "Good decision.";
			link.l1.go = "noble_47";
		break;
		
		case "noble_47":
			dialog.text = "I want to thank you, captain! It was a pleasure! I gift you with my rapier as token of my gratitude to you. She served me well, now let her serve you even better. Look at her and remember your good Spanish friend - marquee Domingo Albalate!";
			link.l1 = "Thank you so much senor! I didn't expect...";
			link.l1.go = "noble_48";
		break;
		
		case "noble_48":
			Log_Info("You have received the Smallsword");
			PlaySound("interface\important_item.wav");
			RemoveCharacterEquip(npchar, BLADE_ITEM_TYPE);
			GiveItem2Character(pchar, "blade_16");
			dialog.text = "And now, alas, I have to say my farewells. I should go to Portobello. My carefree existence is over, time live as a grown up man. Godspeed in the sea!";
			link.l1 = "Good luck with your uncle, don Domingo! I am sure you will prevail!";
			link.l1.go = "noble_49";
		break;
		
		case "noble_49":
			DialogExit();
			chrDisableReloadToLocation = false;
			LocatorReloadEnterDisable("PortoBello_Plantation", "reload2_back", false);
			npchar.lifeday = 0;
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", 40.0);
			pchar.questTemp.FMQP = "fail";
			AddQuestRecord("FMQ_Portpax", "13");
			CloseQuestHeader("FMQ_Portpax");
			sld = &Locations[FindLocation("PortoBello_Plantation")];
			sld.soldiers = true;
		break;
		
		case "uncle":
			PlaySound("VOICE\Russian\OliverTrast02.wav");
			dialog.text = "Looks like I made it in time. My carefree nephew and his guardian angel captain "+GetFullName(pchar)+". Don't look that surprised captain, I did my homework.";
			link.l1 = "Luis Ortiz, am I correct?";
			link.l1.go = "uncle_1";
		break;
		
		case "uncle_1":
			dialog.text = "You are correct in this, captain, but you are wrong in the rest. You should not poke your nose into other people's family matters. You even have no clue who you are protecting. My nephew Domingo is worthless rake, the number one visitor of taverns and brothels who screw or at least try to screw every non ugly girl on the horizon. I pay him his rent every month and he wastes it in days always demanding more and more. Again and again. His constant unworthy behavior made his mother and my sister mentally ill\nI heard rumors that this young naughty boy tried really hard to point English privateers to a ship of marquee Ricardo Albalate which they sank along with the marquee and my sister. Domingo really wanted the money of our family... Sadly, I failed to dig out enough evidences to send this lousy creature to the gallows.";
			link.l1 = "";
			link.l1.go = "uncle_2";
		break;
		
		case "uncle_2":
			DialogExit();
			sld = CharacterFromID("FMQP_noble");
			sld.Dialog.currentnode = "noble_34";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "uncle_3":
			dialog.text = "A usual behavior of my nephew. Typical. Too much yelling, sounds of swords and cups, yet not much sense. I wonder how much did he pay you, captain, for protection of such unworthy youngster...";
			link.l1 = "As far as I understand, after you've failed to dig out any evidence against your nephew, you started to send assassins after him? What was it, a some sort of the civil court?";
			link.l1.go = "uncle_4";
		break;
		
		case "uncle_4":
			dialog.text = "Oh, please! Your friend has made a limitless amount of enemies. I wonder how did he manage to survive that long. Ask him of how many weddings did he ruin? How many offended boys did he wound or even kill?";
			link.l1 = "Actually, his servant Ugo...";
			link.l1.go = "uncle_5";
		break;
		
		case "uncle_5":
			dialog.text = "Ah captain! Ugo loved this scum and all his master's crimes were nothing but a child's prank to him. Remember, caballero, family business is for the family only.";
			link.l1 = "What is it? A threat?";
			link.l1.go = "uncle_6";
		break;
		
		case "uncle_6":
			int icpy = GetOfficersQuantity(pchar);
			iTotalTemp = 10000+10000*icpy;
			dialog.text = "A warning. Look, captain, you've gone too far, but since I take you as a deluded victim and not as an enemy, hear my offer: turn around and walk away. I don't want to spill blood here. We don't need your help in our family matters. I am even ready to compensate troubles you've gone through because of my nephew - "+FindRussianMoneyString(iTotalTemp)+" in cash. Take it and leave us. Reject my offer and my guards will slice you.";
			link.l1 = "Hm... You have a family point. I am leaving. None of my business.";
			link.l1.go = "uncle_7";
			link.l2 = "Don Domingo might be no angel, but you, senor, are obviously a son of a bitch!";
			link.l2.go = "uncle_8";
		break;
		
		case "uncle_7":
			AddMoneyToCharacter(pchar, iTotalTemp);
			dialog.text = "I knew you are a reasonable man. Take your cash and good bye captain. Try not to roam through others' dirty laundry in the future - they never appreciate it.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("FMQP_UncleExit");
		break;
		
		case "uncle_8":
			dialog.text = "Well, then this son of a bitch will send you to hell!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuest("FMQP_UncleFight");
		break;
		
		case "ugo":
			pchar.quest.FMQP_SantoDomingoOver.over = "yes";
			PlaySound("VOICE\Russian\Serve_senior.wav");
			dialog.text = TimeGreeting()+" senor. How can I be of service?";
			link.l1 = "Greetings. Beg pardon, but is this the senor Domingo Albalate's residence?";
			link.l1.go = "ugo_1";
		break;
		
		case "ugo_1":
			dialog.text = "Yes, this is the Albalate mansion. It's very modest yet comfortable. Name's Ugo, I serve the young master. Are you here for him?";
			link.l1 = "Yes, senor. Don Domingo invited me to his place not long ago. He was very persuasive. May I see him?";
			link.l1.go = "ugo_2";
		break;
		
		case "ugo_2":
			dialog.text = "Alas, my good caballero, don Domingo is not home. Personally, I'd like to know myself where to find this naughty boy... eh, beg pardon, young senor. May I ask what do you need from him?";
			link.l1 = "Well... I helped don Domingo by pure chance. He was attacked by some two low-lifes in a tavern of Port-au-Prence. I assisted your master in eliminating those... how did he call them? Dos maldita canalla. Don Domingo had invited me to pay him a visit before he was detained by a French officer for investigation purposes. I thought it all should be settled by now already, so I expected to see him here.";
			link.l1.go = "ugo_3";
		break;
		
		case "ugo_3":
			dialog.text = "Oh, flames! What dreadful stories you telling here! I must see the commandant immediately - to warn him about the dangers don Domingo is facing right now! Senor, you should go and I should hurry!";
			link.l1 = "Take it easy, Ugo. Your young master's safe. He mentioned that his papers are in order, they were supposed to release him already, that's why I am here. I believe we should see him soon.";
			link.l1.go = "ugo_4";
		break;
		
		case "ugo_4":
			dialog.text = "Oh! How could you? My young master, this naive boy - and in the hands of frog eaters?! Not to mention some bandits threatening his life? No way, I must see the commandant! Sir, please go!";
			link.l1 = "Fine-fine, don't be that nervous. I am leaving.";
			link.l1.go = "ugo_exit";
			link.l2 = "Senor, why so nervous? I told you already that there is no danger to your master. Let me stay here and wait for senor Domingo's arrival, I am very tired and I could use a nap. Then you can go to the commandant and do whatever you want.";
			link.l2.go = "ugo_5";
		break;
		
		case "ugo_exit":
			DialogExit();
			LocatorReloadEnterDisable("Santodomingo_town", "houseSp4", true);
			DoQuestReloadToLocation("SantoDomingo_town", "reload", "houseSp4", "FMQP_SDMFail");
		break;
		
		case "ugo_5":
			dialog.text = "Senor, I ask you to leave this house at once!";
			link.l1 = "Ugo, I really doubt that a servant is allowed to talk to me in this manner. I also doubt that don Domingo will approve such treatment to a man who saved his life!";
			link.l1.go = "ugo_6";
		break;
		
		case "ugo_6":
			dialog.text = "Really? Lads! We've got a problem! Here, now!";
			link.l1 = "What the fuck?";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("FMQP_SantoDomingoFight");
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
