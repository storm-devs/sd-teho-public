// шаман команчей Змеиный Глаз
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
			if (CheckAttribute(pchar, "questTemp.Tieyasal") && pchar.questTemp.Tieyasal == "calendar")
			{
				dialog.text = "Greetings, my pale friend.";
				link.l2 = "You too, redskin brother. I have an important business for you again.";
				link.l2.go = "calendar";
				break;
			}
			dialog.text = "Greetings, my pale friend.";
			link.l1 = "I am glad to see you too, Snake Eye.";
			link.l1.go = "exit";
			if (CheckAttribute(npchar, "quest.amulet") && CheckCharacterItem(pchar, pchar.questTemp.Saga.BaronReturn.Indian) && CheckCharacterItem(pchar, pchar.questTemp.Saga.BaronReturn.Amulet) && CheckCharacterItem(pchar, pchar.questTemp.Saga.BaronReturn.Obereg))
			{
				link.l2 = "I brought you the amulets you've asked. Let's trade.";
				link.l2.go = "SnakeEye_potion";
			}
			if (CheckAttribute(pchar, "questTemp.LSC")) // был в LSC
			{
				if (CheckAttribute(npchar, "quest.LSC_hello") && CheckCharacterItem(pchar, "buben"))
				{
					link.l2 = "I have found your tambourine, Snake Eye. Take a look at it.";
					link.l2.go = "LSC_buben";
				}
				if (CheckAttribute(npchar, "quest.LSC_tube") && CheckCharacterItem(pchar, "smoking_tube"))
				{
					link.l2 = "I have found an interesting Indian pipe, Snake Eye. Take a look.";
					link.l2.go = "LSC_tube";
				}
				if (!CheckAttribute(npchar, "quest.LSC_hello"))
				{
					link.l2 = "Hello, shaman. I have used the statue and had an incredible travel. You were totally right. I found the ship's cemetery, the white captain and even the cargo hold with supplies!";
					link.l2.go = "LSC_hello";
				}
				if (CheckAttribute(npchar, "quest.LSC_hello") && pchar.questTemp.Saga.BaronReturn == "shamane")
				{
					link.l3 = "Snake Eye, I need your help.";
					link.l3.go = "Saga_nathaniel";
				}
			}		
			NextDiag.TempNode = "First time";
		break;
		
	//---------------------------------------- первая встреча------------------------------------------------
		case "SnakeEye":
			dialog.text = "Greetings, my pale friend.";
			link.l1 = "Hello, shaman. And why do you think that I am your friend?";
			link.l1.go = "SnakeEye_1";
		break;
		
		case "SnakeEye_1":
			dialog.text = "I know a lot but not always know what exactly. You came here with purpose. Fate lead you here and I help you.";
			link.l1 = "Good to know! Cause I am here for your help, redskin friend. Well, I'll be straight: what did you mean by telling Hawk's wife about Kukulcan?";
			link.l1.go = "SnakeEye_2";
		break;
		
		case "SnakeEye_2":
			dialog.text = "Even dead fish can flow adrift. And living man is lead by fate from goal to goal. The goal of chained captain who was chased by bad people at selva could be Kukulcan statue. If he sacrificed himself, he can be far away from here.";
			link.l1 = "I didn't understand a thing. What the statue of your god is about and how Hawk was able to go on feet so far that nobody can't find him now?";
			link.l1.go = "SnakeEye_3";
		break;
		
		case "SnakeEye_3":
			dialog.text = "If Kukulcan eats Hawk then it could spit him out anywhere. Perhaps even to the other world. Kukulcan has eaten me three times. And each time I be in different places. Long ago I get here and decide no more to risk. I not go to Kukulcan's mouth and I do not know where he spits his victims out.";
			link.l1 = "Jesus, it is beyond my understanding! So do you wanna say that the stone idol can teleport people far away?";
			link.l1.go = "SnakeEye_4";
		break;
		
		case "SnakeEye_4":
			dialog.text = "Not only. Kukulcan rules not only the space but also the time. Or even something more. I tell chained captain about gold statue eats people. Perhaps, he decided to risk when he saw that chasing is close...";
			link.l1 = "Wait, statue is stony. And you are talking about a golden one...";
			link.l1.go = "SnakeEye_5";
		break;
		
		case "SnakeEye_5":
			dialog.text = "At midnight idol lives and becomes gold. This moment Kukulcan spirit lives in it. Fear to come close to him or you can meet sunrise in different place. Even stars can change their places at the sky. You meet those who weren't born yet or see the birth of those who died long ago or aren't born at all.";
			link.l1 = "What the... Riddles and riddles again... You are intriguing me, Snake Eye. But you have survived three meetings with Kukulcan which you believe in. So why don't I try to test my luck with the idol of the god I don't believe in?";
			link.l1.go = "SnakeEye_6";
		break;
		
		case "SnakeEye_6":
			dialog.text = "Pity. Pity that you not believe. Perhaps, Kukulcan himself calls you and makes you leave the land of your ancestors. But you not hear him yet. Everything good in its season. If you decided to risk then you must know that I survived each time only because I had wonderful Comanche potions.";
			link.l1 = "The Comanche? Who are they?";
			link.l1.go = "SnakeEye_7";
		break;
		
		case "SnakeEye_7":
			dialog.text = "That how enemies call my people I never see again. Potion restores strengths and endurance, also heals and saves from strong poisons. You may need several flasks but I have only three left\nThere was four flasks but I lost one in strange place, it look like cemetery of white men's canoes. There I start my journey in this world. Perhaps Kukulcan spit the captain out there. If so I not envy him.";
			link.l1 = "What is the place? Canoe cemetery? You mean ships?";
			link.l1.go = "SnakeEye_8";
		break;
		
		case "SnakeEye_8":
			dialog.text = "Strange place... It should not exist but it exists. People who kill because of skin tone live there. They keep their supplies inside big canoe where Kukulcan spat out me. Not go inside it's hold which they protect from thieves, not trusting neighbors. If you get there - find another exit, not go inside hold or trouble happen\nWhite Boy helps you find another statue if he still live. Give him this white bead. He rejoice.";
			link.l1 = "Hm. My head is going round and this is just getting more interesting. Go on, redskin brother.";
			link.l1.go = "SnakeEye_9";
		break;
		
		case "SnakeEye_9":
			Log_Info("You have received a white pearl");
			PlaySound("interface\important_item.wav");
			GiveItem2Character(pchar, "jewelry52");
			dialog.text = "If you find captain alive, he might be very ill. I had no time to give him a potion. Look for my tambourine there. I got it from my grandfather. There is a lot things in the bag I loose but I need only tambourine. It is difficult to talk with spirits without it.";
			link.l1 = "Well, this place sounds to be interesting! Let's hope that Hawk got to the other place... Will you give your potion?";
			link.l1.go = "SnakeEye_10";
		break;
		
		case "SnakeEye_10":
			dialog.text = "Give. You give me three local amulet in exchange: "+XI_ConvertString(pchar.questTemp.Saga.BaronReturn.Indian)+", "+XI_ConvertString(pchar.questTemp.Saga.BaronReturn.Amulet)+" and "+XI_ConvertString(pchar.questTemp.Saga.BaronReturn.Obereg)+". One flask for each. So be fair. Come when have all. Then exchange. Do not think I am greedy. Perhaps you will rethink while looking for amulets.";
			link.l1 = "I won't. Wait for me, Snake Eye, I'll be back soon.";
			link.l1.go = "SnakeEye_11";
		break;
		
		case "SnakeEye_11":
			DialogExit();
			NextDiag.CurrentNode = "First time";
			npchar.quest.amulet = "true";
			AddQuestRecord("BaronReturn", "3");
			AddQuestUserData("BaronReturn", "sItem1", XI_ConvertString(pchar.questTemp.Saga.BaronReturn.Indian));
			AddQuestUserData("BaronReturn", "sItem2", XI_ConvertString(pchar.questTemp.Saga.BaronReturn.Amulet));
			AddQuestUserData("BaronReturn", "sItem3", XI_ConvertString(pchar.questTemp.Saga.BaronReturn.Obereg));
			sld = characterFromId("Danielle");
			sld.quest.talk = "SnakeEye";
			pchar.quest.BaronReturn_out.win_condition.l1 = "ExitFromLocation";
			pchar.quest.BaronReturn_out.win_condition.l1.location = pchar.location;
			pchar.quest.BaronReturn_out.function = "Saga_DannyTalk";
		break;
		
		// дает зелья - идем на телепортацию
		case "SnakeEye_potion":
			dialog.text = "Good, my friend. You bring me amulets so you ready to go to Kukulcan?";
			link.l1 = "Yes. I am ready to do the same as Nathaniel, the chained captain, did.";
			link.l1.go = "SnakeEye_potion_1";
		break;
		
		case "SnakeEye_potion_1":
			RemoveItems(pchar, pchar.questTemp.Saga.BaronReturn.Indian, 1);
			RemoveItems(pchar, pchar.questTemp.Saga.BaronReturn.Amulet, 1);
			RemoveItems(pchar, pchar.questTemp.Saga.BaronReturn.Obereg, 1);
			TakeNItems(pchar, "Ultimate_potion", 3);
			Log_Info("You have given amulets");
			Log_Info("You have received three versatile potions");
			PlaySound("interface\important_item.wav");
			dialog.text = "Take these potions. Remember that you have to drink it immediately after Kukulcan spat you or you die or be very-very ill. Also remember not to go to cargo hold where palefaces keep their supplies. There is another way from canoe. Two ways in fact. Try to find red woman in night. That all I say you.";
			link.l1 = "I will remember that, redskin brother.";
			link.l1.go = "SnakeEye_potion_2";
		break;
		
		case "SnakeEye_potion_2":
			dialog.text = "Then go. At midnight touch Kukulcan and it eats you. I will call spirits to guide you.";
			link.l1 = "Thank you, Snake Eye. Don't worry about me, it will all be well. We will meet again!";
			link.l1.go = "SnakeEye_potion_3";
		break;
		
		case "SnakeEye_potion_3":
			DialogExit();
			NextDiag.CurrentNode = "First time";
			pchar.questTemp.Saga.BaronReturn = "first_teleport";
			pchar.questTemp.Dolly = true; // телепорты работают!
			LAi_LocationDisableOfficersGen("Pearl_jungle_03", true); // не пускать офицеров в локу телепорта
			DeleteAttribute(npchar, "quest.amulet");
			AddQuestRecord("BaronReturn", "4");
			sld = characterFromId("Danielle");
			sld.quest.talk = "teleport";
			pchar.quest.BaronReturn_out1.win_condition.l1 = "ExitFromLocation";
			pchar.quest.BaronReturn_out1.win_condition.l1.location = pchar.location;
			pchar.quest.BaronReturn_out1.function = "Saga_DannyTalk";
		break;
		
		// пришел из LSC
		case "LSC_hello":
			dialog.text = "I am glad, my friend. How you return back from canoe cemetery?";
			link.l1 = "I've found there the statue of Kukulcan as you've told me. White Boy has helped me - Ole Christiansen. The statue was sunk but I was able to reach it. It moved me to Carib village.";
			link.l1.go = "LSC_hello_1";
			npchar.quest.LSC_hello = "true";
		break;
		
		case "LSC_hello_1":
			dialog.text = "Monkitekuvri meet you there?";
			link.l1 = "Hm. Monkitekuvri? Who is it?";
			link.l1.go = "LSC_hello_2";
		break;
		
		case "LSC_hello_2":
			dialog.text = "He is a village chief.";
			link.l1 = "I didn't ask his name. Perhaps he was Monkitekuvri, perhaps not.";
			link.l1.go = "LSC_hello_3";
		break;
		
		case "LSC_hello_3":
			dialog.text = "Did he have a pompous headdress made of bird feather on his head?";
			link.l1 = "Sure, he had. A lot of feathers... It seems that he plucked all parrots in the wood.";
			link.l1.go = "LSC_hello_4";
		break;
		
		case "LSC_hello_4":
			dialog.text = "He. Monkitekuvri. It is not parrot feather. Eagle feather. This headdress is my headdress. I presented it to Monkitekuvri when Kukulcan spat me out back. Then they took me to another idol...";
			link.l1 = "Isn't that something! They have also 'sacrificed me' to Kukulcan! And I have found myself here, near the first statue.";
			link.l1.go = "LSC_hello_5";
		break;
		
		case "LSC_hello_5":
			dialog.text = "Yes, my pale friend. My path finished here too.";
			link.l1 = "Idols teleport in a circle... But what is the point of that? Have you got any ideas, Snake Eye?";
			link.l1.go = "LSC_hello_6";
		break;
		
		case "LSC_hello_6":
			dialog.text = "I suppose that statues don't work right. They move people to each but they must move them to one place. Something makes them broken.";
			link.l1 = "Why have you decided so?";
			link.l1.go = "LSC_hello_7";
		break;
		
		case "LSC_hello_7":
			dialog.text = "Because teleportation in circle has no point. Kukulcan must take all victims to one place and not move around.";
			link.l1 = "And what is that place?";
			link.l1.go = "LSC_hello_8";
		break;
		
		case "LSC_hello_8":
			dialog.text = "And this a great secret, white brother, even for me.";
			link.l1 = "I see. Fine, hell with idols. I won't come close to them ever. I have found white captain, there is no need to travel trough portals anymore.";
			link.l1.go = "LSC_hello_9";
			AddQuestRecord("BaronReturn", "12");
		break;
		
		case "LSC_hello_9":
			dialog.text = "You be at canoe cemetery. Find there my tambourine?";
			if (CheckCharacterItem(pchar, "buben"))
			{
				link.l1 = "I think so. Take a look.";
				link.l1.go = "LSC_buben";
			}
			else
			{
				link.l1 = "No. Unfortunately I haven't found it. But I know where is the Island and I can reach it. I will look for your tambourine.";
				link.l1.go = "LSC_hello_10";
			}
		break;
		
		case "LSC_hello_10":
			dialog.text = "Look for it, my pale friend. I very ask. Without my tambourine I not hear spirits well.";
			link.l1 = "All right, Snake Eye. See you!";
			link.l1.go = "exit";
		break;
		
		case "LSC_buben":
			RemoveItems(pchar, "buben", 1);
			PlaySound("interface\important_item.wav");
			dialog.text = "It is. Thank you, my pale friend. My repay you. I present you this weapon, your people not have it for a long time to go. This weapon is a weapon of palefaces of my time.";
			link.l1 = "Interesting! Show me it, redskin friend...";
			link.l1.go = "LSC_buben_1";
		break;
		
		case "LSC_buben_1":
			GiveItem2Character(pchar, "pistol7");
			Log_Info("You have received Colt revolver");
			PlaySound("interface\important_item.wav");
			TakeNItems(pchar, "shotgun_cartridge", 3);
			TakeNItems(pchar, "GunCap_colt", 3);
			dialog.text = "Take. Only three charges in it, rest I shoot but you perhaps will learn to make charge for it. I lost a few dozens of parts for charge at canoe cemetery, you can find them.";
			link.l1 = "Oho! That's a pistol! I've never seen anything like this before... what an odd machine? Some turning thing... Five charges! Nice!";
			link.l1.go = "LSC_buben_2";
		break;
		
		case "LSC_buben_2":
			dialog.text = "It call colt. No more such in your time. Easy to use, raise the cock and pull the trigger. It shoots good.";
			link.l1 = "Thank you! Thank you, Snake Eye! It will be a nice surprise for the enemies... Pity that there are only three charges...";
			link.l1.go = "LSC_buben_3";
		break;
		
		case "LSC_buben_3":
			dialog.text = "Try to teach yourself how to make charges for colt. Then you be great warrior of you time. Yes, my pale brother, I forget to ask you to find my pipe at canoe cemetery. It very pretty pipe.";
			if (CheckCharacterItem(pchar, "smoking_tube"))
			{
				link.l1 = "Ha! And I have been thinking for what is that painted pipe? Take a look.";
				link.l1.go = "LSC_tube";
			}
			else
			{
				link.l1 = "Fine. I will look for you pipe. See you!";
				link.l1.go = "exit";
			}
			npchar.quest.LSC_tube = "true";
		break;
		
		case "LSC_tube":
			RemoveItems(pchar, "smoking_tube", 1);
			PlaySound("interface\important_item.wav");
			dialog.text = "It is, my brother. I glad you find it. And I also make you a present. This clever book of palefaces from my time. I can't understand it. Try to find clever man who can read and understand this clever book.";
			link.l1 = "Thank you, Snake Eye. I will think where to find such a man.";
			link.l1.go = "LSC_tube_1";
		break;
		
		case "LSC_tube_1":
			GiveItem2Character(pchar, "chemistry");
			Log_Info("You have received a Lavoisier's chemistry textbook");
			PlaySound("interface\important_item.wav");
			dialog.text = "Look for it, white brother. This book have great secrets of paleface wisdom.";
			link.l1 = "Good. See you, Snake Eye!";
			link.l1.go = "exit";
		break;
		
		// лечение Натаниэля
		case "Saga_nathaniel":
			dialog.text = "I am listening to you, paleface brother.";
			link.l1 = "I have brought white captain who I was looking for. He is very ill. I know that only you can heal him...";
			link.l1.go = "Saga_nathaniel_1";
		break;
		
		case "Saga_nathaniel_1":
			dialog.text = "Kukulcan drank his health. I help him to heal. But it take not less than a one moon. Kukulcan ate captain long ago and illness is deep inside him.";
			link.l1 = "Will you heal him, shaman? I will bring all what you need!";
			link.l1.go = "Saga_nathaniel_2";
		break;
		
		case "Saga_nathaniel_2":
			dialog.text = "I try, white brother. Not bring anything. Me have all. Time makes illness stronger. I think I make it. White captain be healthy in one moon.";
			link.l1 = "Thank you, redskin brother. You are saving me again.";
			link.l1.go = "Saga_nathaniel_3";
		break;
		
		case "Saga_nathaniel_3":
			dialog.text = "Leave white captain my hut, white brother, and walk freely. Take his wife, no one must see my rites.";
			link.l1 = "Fine, Snake Eye. I will take Danielle with me. See you!";
			link.l1.go = "Saga_nathaniel_4";
		break;
		
		case "Saga_nathaniel_4":
			DialogExit();
			pchar.questTemp.Saga.BaronReturn = "treatment";
			sld = characterFromId("Nathaniel");
			RemovePassenger(Pchar, sld);
			LAi_SetStayType(sld);
			sld.location = "none";
			pchar.quest.Saga_NatanTreatment1.win_condition.l1 = "ExitFromLocation";
			pchar.quest.Saga_NatanTreatment1.win_condition.l1.location = pchar.location;
			pchar.quest.Saga_NatanTreatment1.function = "Saga_NatanTreatment";
		break;
		
		case "calendar":
			dialog.text = "I listen, my friend.";
			link.l1 = "Remember our talk about Kukulcan statues? You said 'they must move people to one special place'.";
			link.l1.go = "calendar_1";
		break;
		
		case "calendar_1":
			dialog.text = "I remember, white captain.";
			link.l1 = "I know where those statues must have moved people who were eaten by Kukulcan.";
			link.l1.go = "calendar_2";
		break;
		
		case "calendar_2":
			dialog.text = "Where to?";
			link.l1 = "To the old Maya city Tayasal. It is located deep in the Main.";
			link.l1.go = "calendar_3";
		break;
		
		case "calendar_3":
			dialog.text = "Very interesting. How do you know?";
			link.l1 = "It's a long story, Snake Eye. I also understood how you got here. You are not born yet, right?";
			link.l1.go = "calendar_4";
		break;
		
		case "calendar_4":
			dialog.text = "Even my father not born in your time. But I live in your time and that is a great mystery.";
			link.l1 = "It is quite easy. Itza priest named Kanek who is living in Tayasal called upon Kukulcan in this world to be born as a mortal and to absorb wisdom of pale race. He also created the time hole which dragged a few men from the future...";
			link.l1.go = "calendar_5";
		break;
		
		case "calendar_5":
			dialog.text = "To let Kukulcan to absorb wisdom of future people?";
			link.l1 = "Yes. And then Kukulcan will go to the past to bring knowledge for Maya people who died long ago. History will be changed then and Maya will rule America and perhaps not only it...";
			link.l1.go = "calendar_6";
		break;
		
		case "calendar_6":
			dialog.text = "";
			link.l1 = "But something has happened with portals and they started teleporting people on circle but not to Tayasal. And here I am, I need your advice, Snake Eye.";
			link.l1.go = "calendar_7";
		break;
		
		case "calendar_7":
			dialog.text = "Why me, white captain?";
			link.l1 = "Because you've been eaten by Kukulcan. And because the Kukulcan statue near your village has a strange mark on the map which has a strong connection to Kanek's rites.";
			link.l1.go = "calendar_8";
		break;
		
		case "calendar_8":
			dialog.text = "Show me this map?";
			link.l1 = "Here, take a look...";
			link.l1.go = "calendar_9";
		break;
		
		case "calendar_9":
			RemoveItems(pchar, "skinmap", 1);
			dialog.text = "(looking) This round sign, yes? And what it mean?";
			link.l1 = "I don't know, shaman. I only now that only one of three Kukulcan statues has the mark. And this statue is yours. I make a conclusion that it is a special one. Got any ideas?";
			link.l1.go = "calendar_10";
		break;
		
		case "calendar_10":
			dialog.text = "Give me time until tomorrow morning, white brother. Leave me this leather map. I need ask spirits. Come tomorrow.";
			link.l1 = "Fine, redskin brother. I will be here tomorrow. Thank you for helping me.";
			link.l1.go = "calendar_11";
		break;
		
		case "calendar_11":
			DialogExit();
			SetFunctionTimerCondition("Tieyasal_CalendarThink", 0, 0, 1, false);
			pchar.questTemp.Tieyasal = "calendar_think";
			NextDiag.CurrentNode = "calendar_wait";
		break;
		
		case "calendar_wait":
			dialog.text = "Come later, white brother. Not bother me now.";
			link.l1 = "Sure, shaman...";
			link.l1.go = "exit";
			NextDiag.TempNode = "calendar_wait";
		break;
		
		case "calendar_12":
			dialog.text = "I have something to tell you, white brother.";
			link.l1 = "Did you find anything? Or do you have a guess?";
			link.l1.go = "calendar_13";
		break;
		
		case "calendar_13":
			dialog.text = "Ancestor spirits gave me a vision and I go to Kukulcan with map. And searched. I fond. It must be what you look for, white brother.";
			link.l1 = "What did you find?";
			link.l1.go = "calendar_14";
		break;
		
		case "calendar_14":
			dialog.text = "Kukulcan statue has two iron clamps and a recess. The recess has round and smooth form. It orients to the round and flat item from your leather map.";
			link.l1 = "What is it?";
			link.l1.go = "calendar_15";
		break;
		
		case "calendar_15":
			dialog.text = "I not know. I know that it is round, flat, size like a small pumpkin and finger thick. You can go and look at recess and clamps for yourself. Clamp need to held it.";
			link.l1 = "Do you have any ideas? Guesses?";
			link.l1.go = "calendar_16";
		break;
		
		case "calendar_16":
			dialog.text = "Stone have a fire trace. I know what it is. Sky flame hit it.";
			link.l1 = "Lightning? Did lightning hit it?";
			link.l1.go = "calendar_17";
		break;
		
		case "calendar_17":
			dialog.text = "I am sure in that. I asked Miskito about this idol. One warrior said that long ago a few pretty painted things were found there. Like crocks. He tell that be a very pretty red crocks. One white man from white village bought it.";
			link.l1 = "Hm. As far as I understood, it seems that lightning hit this round 'something', broke it on crocks and then these crocks were sold to some white guy?";
			link.l1.go = "calendar_18";
		break;
		
		case "calendar_18":
			dialog.text = "Seems so.";
			link.l1 = "And who is that white man? Did your warrior tell you?";
			link.l1.go = "calendar_19";
		break;
		
		case "calendar_19":
			dialog.text = "Tell. It was a big friend of Miskito and he lives in Blueweld village. His name Forest Devil. I know him, you must know him too.";
			link.l1 = "Jan Swanson? Wait a second... Red painted crocks, you say? It looks like I am lucky. Now look here, shaman, see what red crocks I have! Forest Devil presented them to me.";
			link.l1.go = "calendar_20";
		break;
		
		case "calendar_20":
			Log_Info("You have given ornamental pattern fragments");
			RemoveItems(pchar, "splinter_js", 1);
			RemoveItems(pchar, "splinter_nh", 1);
			RemoveItems(pchar, "splinter_mt", 1);
			RemoveItems(pchar, "splinter_zm", 1);
			RemoveItems(pchar, "splinter_jb", 1);
			dialog.text = "Must be them. Five crocks. Take a look, white brother. If they place like that... (putting together)";
			link.l1 = "...";
			link.l1.go = "calendar_21";
		break;
		
		case "calendar_21":
			dialog.text = "... then we have round item. Look! They match. It used to be an item before.";
			link.l1 = "Damn it! And this thing has been lying in my pocket for so long... Listen, shaman, so if I put this shards in the flute...";
			link.l1.go = "calendar_22";
		break;
		
		case "calendar_22":
			dialog.text = "Kukulcan will spit the victim to the old Indian city as you say.";
			link.l1 = "It would be great! I need to get there! How do you think, will it work while being broken?";
			link.l1.go = "calendar_23";
		break;
		
		case "calendar_23":
			dialog.text = "I think that we need bring it together and then put it in cramp.";
			link.l1 = "Match? But how to bring together broken crocks?";
			link.l1.go = "calendar_24";
		break;
		
		case "calendar_24":
			dialog.text = "Leave it to me and ancestor spirits, white brother. It not just simple crocks. It miracle item. Come in three night, white brother. I call spirits, wisdom and skill of living and I try to unite shards.";
			link.l1 = "Incredible... How can I repay you, Snake Eye?";
			link.l1.go = "calendar_25";
		break;
		
		case "calendar_25":
			dialog.text = "Thank me later, white brother. Go. Come in three nights.";
			link.l1 = "Fine. I hope that you will succeed...";
			link.l1.go = "calendar_26";
		break;
		
		case "calendar_26":
			DialogExit();
			SetFunctionTimerCondition("Tieyasal_CalendarDone", 0, 0, 3, false);
			NextDiag.CurrentNode = "calendar_wait";
		break;
		
		case "calendar_28":
			dialog.text = "I can happy you, white brother.";
			link.l1 = "Were you able to bring the shards together?";
			link.l1.go = "calendar_29";
		break;
		
		case "calendar_29":
			dialog.text = "Yes. It was not easy and there are scars left on the calendar but it is complete now.";
			link.l1 = "Calendar? Why did you call it like that?";
			link.l1.go = "calendar_30";
		break;
		
		case "calendar_30":
			dialog.text = "Because this round thing is calendar. I study it carefully. There is a time count on it. Indians from ancient city count nights, moons, years and ages.";
			link.l1 = "Incredible... Though, concerning what Maya priests are able to do - there is not anything special about creation of this calendar.";
			link.l1.go = "calendar_31";
		break;
		
		case "calendar_31":
			GiveItem2Character(pchar, "calendar_maya");
			sld = ItemsFromID("calendar_maya");
			sld.shown = "0";
			Log_Info("You have received a Maya calendar");
			dialog.text = "Take it, white captain. Plant it in clamps of the statue. Then perhaps it spit you out in Indian city.";
			link.l1 = "How can I repay you, Snake Eye?";
			link.l1.go = "calendar_32";
		break;
		
		case "calendar_32":
			dialog.text = "Say 'Thank you'. Gods guide you on your path even you do not see it. White people say - fate. Kukulcan calls you, gods guide you. Go. Do your work and let good spirit guide you.";
			link.l1 = "Thank you, Snake Eye! I will never forget you.";
			link.l1.go = "calendar_33";
		break;
		
		case "calendar_33":
			TakeNItems(pchar, "Ultimate_potion", 4);
			Log_Info("You have received four versatile potions");
			PlaySound("interface\important_item.wav");
			dialog.text = "Wait. We have almost forgotten some important thing. Kukulcan eats man and drinks his life. I make our potion. Comanche potion. I give it to you, I have four flasks. You can take three loyal companions who be brave.";
			link.l1 = "You have done so much for me, redskin brother...";
			link.l1.go = "calendar_34";
		break;
		
		case "calendar_34":
			dialog.text = "Friend is not just a word for Indian of Comanche tribe. When back from Kukulcan city, visit our village. We cook a lot, a lot of saraiaka. I will be glad to see you.";
			link.l1 = "Sure, redskin brother! I will certainly visit you!";
			link.l1.go = "calendar_35";
		break;
		
		case "calendar_35":
			DialogExit();
			pchar.questTemp.Tieyasal = "calendar_place";
			NextDiag.CurrentNode = "First time";
			AddQuestRecord("Tieyasal", "17");
			sld = ItemsFromID("skinmap");
			sld.price = 100; // кожаную карту можно выкладывать 270912 
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}