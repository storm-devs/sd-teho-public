// Абрахам Норман
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i, iTemp;
	string sTemp;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "Is there something you need?";
			link.l1 = "No, nothing.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		case "norman_us":
			if(CheckAttribute(pchar, "questTemp.Tieyasal") && pchar.questTemp.Tieyasal == "begin" && !CheckAttribute(npchar, "quest.Tieyasal"))
			{
				dialog.text = LinkRandPhrase("What do you need, buddy? Walk your path, take care of your business. Just leave me alone.","Hey, hey, pal. Going for a walk? Well you just keep on walking and leave mr. Abraham alone. He's going for a walk too. He's getting a breath of some fresh sea air.","Hello, friend. Wanna chat? There's just one problem: I'm not in the mood for conversation. So go look for somebody else to bother. Go kick back at the tavern. Have some rum...");
				link.l1 = "Listen, Abraham, did you happen to run into a man named Miguel Dichoso recently on Isla Tesoro? He's kind of a well-known cat around here.";
				link.l1.go = "tieyasal";
				break;
			}
			dialog.text = NPCStringReactionRepeat(LinkRandPhrase("What do you need, buddy? Walk your path, take care of your business. Just leave me alone.","Hey, hey, pal. Going for a walk? Well you just keep on walking and leave mr. Abraham alone. He's going for a walk to. He's getting a breath of some fresh sea air.","Hello, pal. Wanna chat? There's just one problem: I'm not in the mood for conversation. So go bother someone else. Go kick back at the tavern. Have some rum..."), LinkRandPhrase("Hey, sailor. What are you hard-headed or something? I thought I was pretty clear.","Pal, go get some rest. Otherwise, you seem to be a little hard of hearing.","Hey pal, what are you stupid or something? I pretty much spelled it out for you already."), "Buddy, don't make me angry. I've slaughtered so many landlubbers in my time, that one more or one less doesn't really make a difference.", "All right, you've pissed me off. Now either take out your rusty sword or run as fast as you can. I recommend the second option...", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("All right, friend. I'm not gonna bother you.", "Fine, fine. I got it...", "Whoa, well you look to be the thunder of the seas! All right, I'm out of here.", "What?!", npchar, Dialog.CurrentNode); 
			link.l1.go = DialogGoNodeRepeat("exit", "", "", "fight", npchar, Dialog.CurrentNode);
			NextDiag.TempNode = "norman_us";
		break;
		
		case "norman_fes":
			if(CheckAttribute(pchar, "questTemp.Tieyasal") && pchar.questTemp.Tieyasal == "begin" && !CheckAttribute(npchar, "quest.Tieyasal"))
			{
				dialog.text = LinkRandPhrase("What do you need, buddy? Walk your path, take care of your business. Just leave me alone.","Hey, hey, pal. Going for a walk? Well you just keep on walking and leave mr. Abraham alone. He's going for a walk to. He's getting a breath of some fresh sea air.","Hello, pal. Wanna chat? There's just one problem: I'm not in the mood for conversation. So go bother someone else. Go kick back at the tavern. Have some rum...");
				link.l1 = "Listen, Abraham, did you happen to run into a man named Miguel Dichoso recently on Isla Tesoro? He's kind of a well-known cat around here.";
				link.l1.go = "tieyasal";
				break;
			}
			switch (drand(5))
			{
				case 0:
					dialog.text = "Freeze! I'm the governor of this island. What, you don't believe me?!";
					link.l1 = "Of course I do! Who doesn't know the governor of Isla Tesoro...";
					link.l1.go = "norman_fes0_fight";
					link.l2 = "Ha, call yourself an admiral while your at it, I'll definitely buy that!";
					link.l2.go = "norman_fes0_peace";
				break;
				
				case 1:
					dialog.text = "Stand at attention! Behold - Admiral Barbarigo! Don't you recognize my famous cavalry sword?";
					link.l1 = "My apologies, sir admiral! From now on, I'll be more attentive.";
					link.l1.go = "norman_fes1_peace";
					link.l2 = "Your cavalry sword is widely known. Too bad, it has reached a fool.";
					link.l2.go = "norman_fes1_fight";
				break;
				
				case 2:
					dialog.text = "As you can see, I am here in exile. I am awaiting further notification from General Monk. I ask that you do not disseminate my concealed royal identity. Cromwell's intelligence has long ears.";
					link.l1 = "But of course, your Majesty. No one will ever learn that Karl the II is hiding in West India.";
					link.l1.go = "norman_fes2_fight";
					link.l2 = "Well, and I am Pope Innocent X then.";
					link.l2.go = "norman_fes2_peace";
				break;
				
				case 3:
					dialog.text = "What happened to you, Blaze? I've been looking for you for two days. You've completely forgotten your father Nicolas!";
					link.l1 = "I don't have time for you father! I'm swamped.";
					link.l1.go = "norman_fes3_peace";
					link.l2 = "You've mistaken, sir. My name is "+GetFullName(pchar)+".";
					link.l2.go = "norman_fes3_fight";
				break;
				
				case 4:
					dialog.text = "Sh-sh... I am Davy Jones. Tell me, are you afraid of death?";
					link.l1 = "Of course I am, mr. Jones. Especially after a hangover.";
					link.l1.go = "norman_fes4_fight";
					link.l2 = "One death is a tragedy, a thousand is just a statistic.";
					link.l2.go = "norman_fes4_peace";
				break;
				
				case 5:
					dialog.text = "I'm in a hurry to finish my new play. You must help me finish the phrase 'To be or not to be'?!";
					link.l1 = "That is the question! Shall we endure the offense and move on...";
					link.l1.go = "norman_fes5_fight";
					link.l2 = "A drink, for sure. But I won't be surprised when I catch a disease in a brothel!";
					link.l2.go = "norman_fes5_peace";
				break;
			}
		break;
		
		case "norman_fes0_fight":
			dialog.text = "What the hell are you talking about 'Tesoro'?! You might as well call it the Bermudas! This island is called Norman Island after me and don't forget it. I'm going to have to teach you geography...";
			link.l1 = "Huh! What do you mean?!";
			link.l1.go = "fight";
			NextDiag.TempNode = "norman_fight_again";
		break;
		
		case "norman_fes0_peace":
			dialog.text = "You're right, sailor. I really am Admiral Barbarigo, but that's strictly between us. Get ready to march. We're moving out soon. That'll come in handy for you.";
			link.l1 = "I'm extremely grateful!";
			link.l1.go = "norman_fes0_exit";
		break;
		
		case "norman_fes0_exit":
			DialogExit();
			NextDiag.CurrentNode = "norman_fes_again";
			PlaySound("interface\important_item.wav");
			if (GetDataDay() == 12)
			{
				GiveItem2Character(pchar, "pistol2");
				Log_Info("You've received a three-barreled shotgun");
			}
			else
			{
				if (GetDataDay() == 23 && GetDataMonth() == 2)
				{
					GiveItem2Character(pchar, "mushket1");
					Log_Info("You've received a match-lock musket");
				}
				else
				{
					GiveItem2Character(pchar, "cartridge");
					Log_Info("You've received a paper cartridge");
				}
			}
		break;
		
		case "norman_fes1_fight":
			dialog.text = "We'll see which of us is the fool now. On guard!";
			link.l1 = "Are you serious?!";
			link.l1.go = "fight";
			NextDiag.TempNode = "norman_fight_again";
		break;
		
		case "norman_fes1_peace":
			dialog.text = "What did I tell you! Here, drink for my health.";
			link.l1 = "Bottoms up, admiral!";
			link.l1.go = "norman_fes1_exit";
		break;
		
		case "norman_fes1_exit":
			DialogExit();
			NextDiag.CurrentNode = "norman_fes_again";
			PlaySound("interface\important_item.wav");
			if (GetDataDay() == 13)
			{
				GiveItem2Character(pchar, "gold_dublon");
				Log_Info("You've received a gold doubloon");
			}
			else
			{
				if (GetDataDay() == 1 && GetDataMonth() == 4)
				{
					GiveItem2Character(pchar, "chest");
					Log_Info("You've received a chest of doubloons");
				}
				else
				{
					AddMoneyToCharacter(pchar, 5);
				}
			}
		break;
		
		case "norman_fes2_fight":
			dialog.text = "I asked you not to disseminate my name! Now I'm going to have to do away with you as a dangerous witness...";
			link.l1 = "Oh, I've been waiting for this!";
			link.l1.go = "fight";
			NextDiag.TempNode = "norman_fight_again";
		break;
		
		case "norman_fes2_peace":
			dialog.text = "Forgive me, your Grace! I didn't recognize you in this image. Please, accept this modest gift from a true catholic.";
			link.l1 = "Insanity pipes up...";
			link.l1.go = "norman_fes2_exit";
		break;
		
		case "norman_fes2_exit":
			DialogExit();
			NextDiag.CurrentNode = "norman_fes_again";
			PlaySound("interface\important_item.wav");
			if (GetDataDay() == 14)
			{
				GiveItem2Character(pchar, "amulet_10");
				Log_Info("You've received the Wonderworker Amulet");
			}
			else
			{
				if (GetDataDay() == 25 && GetDataMonth() == 12)
				{
					GiveItem2Character(pchar, "totem_04");
					Log_Info("You've received the Talisman of the Accomplice");
				}
				else
				{
					GiveItem2Character(pchar, "Mineral3");
					Log_Info("You've received a wax candle");
				}
			}
		break;
		
		case "norman_fes3_fight":
			dialog.text = "Everyone's coming at me! I caught a spy that looks just like my son! I'm sure Thomas sent him to knock my second eye out!";
			link.l1 = "Buzz off, moron!";
			link.l1.go = "fight";
			NextDiag.TempNode = "norman_fight_again";
		break;
		
		case "norman_fes3_peace":
			dialog.text = "You're tired and you don't look so hot, sonny. Go on and get some treatment.";
			link.l1 = "Thanks!";
			link.l1.go = "norman_fes3_exit";
		break;
		
		case "norman_fes3_exit":
			DialogExit();
			NextDiag.CurrentNode = "norman_fes_again";
			PlaySound("interface\important_item.wav");
			if (GetDataDay() == 15)
			{
				GiveItem2Character(pchar, "potion4");
				Log_Info("You've received a potion");
			}
			else
			{
				if (GetDataDay() == 19 && GetDataMonth() == 6)
				{
					GiveItem2Character(pchar, "talisman8");
					Log_Info("You've received the Scorpion Amulet");
				}
				else
				{
					GiveItem2Character(pchar, "potion1");
					Log_Info("You've received remedial essence")
				}
			}
		break;
		
		case "norman_fes4_fight":
			dialog.text = "Don't be afraid, buddy. See, dying isn't scary at all...";
			link.l1 = "Looks like you aren't kidding!";
			link.l1.go = "fight";
			NextDiag.TempNode = "norman_fight_again";
		break;
		
		case "norman_fes4_peace":
			dialog.text = "Apparently you're not scared. I knew it. That's bravery!";
			link.l1 = "You are a funny old man...";
			link.l1.go = "norman_fes4_exit";
		break;
		
		case "norman_fes4_exit":
			DialogExit();
			NextDiag.CurrentNode = "norman_fes_again";
			PlaySound("interface\important_item.wav");
			if (GetDataDay() == 17)
			{
				GiveItem2Character(pchar, "cirass6");
				Log_Info("You've received a fire-eater waistcoat");
			}
			else
			{
				if (GetDataDay() == 1 && GetDataMonth() == 1)
				{
					GiveItem2Character(pchar, "cirass3");
					Log_Info("You've received a parade cuirass");
				}
				else
				{
					GiveItem2Character(pchar, "Mineral18");
					Log_Info("You've received some tobacco");
				}
			}
		break;
		
		case "norman_fes5_fight":
			dialog.text = "You're a crappy poet, sailor. Could it be that your blade is more agile than your tongue?";
			link.l1 = "Caramba! That cavalry sword of yours isn't a sham at all!";
			link.l1.go = "fight";
			NextDiag.TempNode = "norman_fight_again";
		break;
		
		case "norman_fes5_peace":
			dialog.text = "Dang! Things have gone pretty smoothly for you! How's that for your imagination!";
			link.l1 = "Come again.";
			link.l1.go = "norman_fes5_exit";
		break;
		
		case "norman_fes5_exit":
			DialogExit();
			NextDiag.CurrentNode = "norman_fes_again";
			PlaySound("interface\important_item.wav");
			PlaySound("interface\important_item.wav");
			if (GetDataDay() == 16)
			{
				GiveItem2Character(pchar, "potionrum");
				Log_Info("You've received a bottle of rum");
			}
			else
			{
				if (GetDataDay() == 28 && GetDataMonth() == 11)
				{
					GiveItem2Character(pchar, "totem_01");
					Log_Info("You've received a throat of cast iron");
				}
				else
				{
					GiveItem2Character(pchar, "Mineral17");
					Log_Info("You've received a glass flask");
				}
			}
		break;
		
		case "norman_fight_again":
			dialog.text = "Aha, I recognize you! Ha-ha!";
			link.l1 = "Again...";
			link.l1.go = "fight";
		break;
		
		case "norman_fes_again":
			dialog.text = "All right, pal, we've had our talk. Be on your way now.";
			link.l1 = "As you say...";
			link.l1.go = "exit";
			NextDiag.TempNode = "norman_fes_again";
		break;
		
		case "tieyasal":
			dialog.text = "Dichoso? What do you need him for, huh?";
			link.l1 = "Well, I need him. I just need him. So have you seen him?";
			link.l1.go = "tieyasal_1";
			link.l2 = "What do you mean what do I need him for? Miguel is my old buddy, a friend you could say. He's supposed to...";
			link.l2.go = "tieyasal_2";
			link.l3 = "I want him to haul along a new vessel for me just like he did once before for Shark Dodson.";
			link.l3.go = "tieyasal_3";
			if (CheckAttribute(pchar, "questTemp.Ksochitam.SQCapBookRead")) // прочел журнал Санта-Квитерии
			{
				link.l4 = "Miguel Dichoso has killed a man. That's why I'm searching for him.";
				link.l4.go = "tieyasal_4";
			}
			npchar.quest.Tieyasal = "true";
		break;
		
		case "tieyasal_1":
			dialog.text = "You just need him...You juuust need him! All you need is Miguel Dichoso! No, I haven't seen him. I haven't seen him for a long time. There's nothing I can help you with, sailor.";
			link.l1 = "Hm... All right, bye.";
			link.l1.go = "exit";
		break;
		
		case "tieyasal_2":
			dialog.text = "A friend, you say... He seems to have cultivated a whole heap of friends. He's about to have one less...";
			link.l1 = "Hey, old man. What's wrong with you?";
			link.l1.go = "fight";
			NextDiag.TempNode = "norman_fight_again";
		break;
		
		case "tieyasal_3":
			dialog.text = "Yes, Dichoso is a master of such trades either way you look at it. But I don't know where he is. He came and then he took off. So go on over to Alexus, sailor. He'll hammer together a wonderful tub for you.";
			link.l1 = "Hm... Thanks for the tip, buddy.";
			link.l1.go = "exit";
		break;
		
		case "tieyasal_4":
			dialog.text = "And who was it that ganked Dichoso for you to be conducting a search for him, huh buddy? ";
			link.l1 = "";
			Link.l1.edit = 8;
			link.l1.go = "tieyasal_5";
		break;
		
		case "tieyasal_4_1":
			dialog.text = "What do you mean? What Sharp exactly did he kill? There are a lot of Sharps, you know.";
			link.l1 = "";
			Link.l1.edit = 8;
			link.l1.go = "tieyasal_5";
		break;
		
		case "tieyasal_5":
			sTemp = GetStrSmallRegister(dialogEditStrings[8]);
			if (sTemp == "blaze sharp")
			{
				dialog.text = "Sh-sh-sh...(looking around) So you also think that Blaze Sharp was killed by Dichoso?";
				link.l1 = "Yes. I have not only suspicions, but a solid proof. Entries in his logbook...";
				link.l1.go = "tieyasal_6";
				break;
			}
			if (sTemp == "sharp")
			{
				dialog.text = "Go on, little sailor...";
				link.l1 = "What do you mean? Tell me more.";
				link.l1.go = "tieyasal_4_1";
				break;
			}
			dialog.text = "Ah...Well. He killed him and that's all there is to it. You know how many killers we've got running around here? Every other man! No sailor. I haven't seen Dichoso in a long time. I can't help you with anything.";
			link.l1 = "Pity...";
			link.l1.go = "exit";
		break;
		
		case "tieyasal_6":
			dialog.text = "Quiet down, buddy. What's your name, huh? It's somehow escaped my memory...";
			link.l1 = "Captain "+GetFullName(pchar)+".";
			link.l1.go = "tieyasal_7";
		break;
		
		case "tieyasal_7":
			dialog.text = "Listen, "+pchar.name+". Dichoso killed poor Blaze. I saw it with my own eyes, yes-yes. But they don't believe me. See, they think I am crazy. One of their own, but crazy. And I used to be the best boarding officer in a crew of Nicolas Sharp himself! Good times! But eventually I have lost my claws, hoof and lens and got grounded\nWhat? Ah, right! Everyone thought that the Shark was to blame, but he was not. No-no-no. There was a shark's tooth, a talisman of Dodson but it was Dichoso who planted it there\nHe must had stolen it from Steven when they were sailing together for a frigate Fortune. I didn't sleep well that day and went outside to walk. I saw Dichoso had sneaked inside Sharp's residence, heard someone screamed and then groaned. Soon Dichoso had left the residence and his hands were in blood\nThey didn't believe me, no-no. Because there was no Dichoso at the island that day, and Shark was. And they had found his tooth. But I saw Dichoso, I am sure. Nobody just knew that he was there that day. The Lucky is a very cunning and fearsome man...";
			link.l1 = "You're not the first one to call Dichoso 'the Lucky'. Why is that? Is it his nickname?";
			link.l1.go = "tieyasal_8";
		break;
		
		case "tieyasal_8":
			dialog.text = "Don't you know Spanish, guy? 'Dichoso' in the papist language means 'lucky'. Lucky Miguel, Miguel the Lucky. That's what his name is.";
			link.l1 = "Miguel the Lucky?... Hm. That reminds me of something. Hm. That phrase sounds so familiar...";
			link.l1.go = "tieyasal_9";
		break;
		
		case "tieyasal_9":
			dialog.text = "Well, be his last name Dichoso, I still don't think that he's Spanish. No, no. He isn't Spanish. Although he looks like a Spanish.";
			link.l1 = "Then who is he? English, French?";
			link.l1.go = "tieyasal_10";
		break;
		
		case "tieyasal_10":
			dialog.text = "That's not what I'm talking about sailor... Oh, forgive me, captain. Yes, Dichoso babbles French quite fabulously, no worse than you do. And in English as well. However in his veins flows Indian blood. I have seen many such people in my life. It's not clear to see, but he's a halfzee. I guarantee you.";
			link.l1 = "Does he speak Indian?";
			link.l1.go = "tieyasal_11";
		break;
		
		case "tieyasal_11":
			dialog.text = "Oh, hell knows. Maybe he does. Although, wait. He does! He used to constantly utter weird sentences in some bizarre language and he made a scary sage face and blew out his cheeks while he was pronouncing them. For example, he would say something like: kogito ergo sum! And then he would roll out his eyes and stare look for the reaction of the sailors. Or he would exclaim like this: aut cezar, aut nihil! He blurted out a lot of other things too. I don't remember everything he used to say.";
			link.l1 = "That's not Indian language. That's Latin. Latin... Latin?! Holy Fuck!";
			link.l1.go = "tieyasal_12";
		break;
		
		case "tieyasal_12":
			dialog.text = "Why you so jumpy, guy? What are you shouting for? Did you get bit by a snake or something? Where did it go?";
			link.l1 = "How didn't I guess it in the beginning! Everything was staring me right in the face! Latin! Miguel... Miguel the Lucky!!!";
			link.l1.go = "tieyasal_13";
		break;
		
		case "tieyasal_13":
			dialog.text = "Hey, pal. Would you stop hollering already. People are staring at us. What's eating you sailor... sorry captain?";
			link.l1 = "I know who Miguel Dichoso really is. He really isn't Spanish. He's French! Oh, I was so blind!";
			link.l1.go = "tieyasal_14";
		break;
		
		case "tieyasal_14":
			dialog.text = "Nah-uh, dummy. He's not French. He's a halfzee. His white daddy shaked boots with a little bitty Indian girl, one of those Arawaks or Miskito from the Caribbean or even an Itza, and that's how Holy Miguel Dichoso came on this Earth. You don't see this, but I do. It's written in his eyes...";
			link.l1 = "Let's leave the question of his origin aside for a moment. Where is he, Abraham?! Was he here?!";
			link.l1.go = "tieyasal_15";
		break;
		
		case "tieyasal_15":
			dialog.text = "Sh-sh... Yes, he was here. But he left. He's not on Isla Tesoro anymore.";
			link.l1 = "What did he come here for? What kind of ship does he have?";
			link.l1.go = "tieyasal_16";
		break;
		
		case "tieyasal_16":
			dialog.text = "His ship is a galleon. A big, war galleon. What he came here for... Well, he walked around and sniffed around asking questions. But I overheard his conversations, yes yes! He was looking for some Charles de Maure. Yes, that's it. Charles de Maure. Wait, that's you Charles de Maure! He was looking for you, buddy.";
			link.l1 = "Do you know what for?";
			link.l1.go = "tieyasal_17";
		break;
		
		case "tieyasal_17":
			dialog.text = "Well definitely not to visit a tavern and sip rum with you. He was prompting to capture you. Yes, yes! Capture you! You're in deep shit, captain!";
			link.l1 = "I don't doubt it...";
			link.l1.go = "tieyasal_18";
		break;
		
		case "tieyasal_18":
			dialog.text = "And you? Why are you searching for him? Oh, I get it, I get it: to kill him! Kill him, kill the bastard! Avenge Blaze Sharp! Blaze was a terrific guy. I remember him even as a child just like Nicholas.";
			link.l1 = "Where did Dichoso go?";
			link.l1.go = "tieyasal_19";
		break;
		
		case "tieyasal_19":
			dialog.text = "He was on his way to Blueweld. He said that Charles de Maure is to be sought under the wing of the Forest Devil. But he left his people here... Wait. I think you've already been noticed!";
			link.l1 = "Who's noticed me?";
			link.l1.go = "tieyasal_20";
		break;
		
		case "tieyasal_20":
			dialog.text = "Dichoso's men. He's ordered to put a watch on you here. Oh, I know, I know! Be alert, captain: the reefs of Isla Tesoro are surrounded by ships and they're sitting there for your head. The captain is sly as a fox. Don't let yourself be tricked.";
			link.l1 = "I'll try...";
			link.l1.go = "tieyasal_21";
		break;
		
		case "tieyasal_21":
			dialog.text = "And one more thing: here, take my cavalry sword. Take it, take it. You'll need it. This is captain Barbarigo's sword itself. It's an excellent blade. The best on the archipelago. Don't be shy, take it. Blaze Sharp shall be avenged!";
			link.l1 = "Thank you, Abraham.";
			link.l1.go = "tieyasal_22";
		break;
		
		case "tieyasal_22":
			RemoveCharacterEquip(npchar, BLADE_ITEM_TYPE);
			RemoveItems(npchar, "blade_29", 1);
			sTemp = GetBestGeneratedItem("blade_29");
			GiveItem2Character(pchar, sTemp);
			sld = ItemsFromID(sTemp);
			sld.Balance = 1.0;
			GiveItem2Character(npchar, "blade_19"); 
			EquipCharacterbyItem(npchar, "blade_19");
			Log_Info("You've received Barbarigo's sword");
			PlaySound("interface\important_item.wav");
			dialog.text = "Go now. Go, you are being watched. Make it looks like you're smart. Or stupid. It doesn't matter. Just be careful!";
			link.l1 = "Thanks, buddy. You don't even know how much you've helped me. Good luck!";
			link.l1.go = "tieyasal_23";
		break;
		
		case "tieyasal_23":
			DialogExit();
			pchar.questTemp.Tieyasal.MigelKnow = "true";
			AddQuestRecord("Tieyasal", "4");
			pchar.quest.Tieyasal_ITAttack.win_condition.l1 = "location";
			pchar.quest.Tieyasal_ITAttack.win_condition.l1.location = "Bermudes";
			pchar.quest.Tieyasal_ITAttack.function = "Tieyasal_CreateITShips";
			pchar.questTemp.Tieyasal = "islatesoro";
		break;
		
		case "fight":
			iTemp = 20-sti(GetCharacterItem(npchar, "potion2"));
			TakeNItems(npchar, "potion2", iTemp);
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
			LAi_group_Attack(NPChar, Pchar);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
