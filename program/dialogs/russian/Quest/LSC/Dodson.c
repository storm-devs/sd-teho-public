// Акула: Стивен Додсон
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	string sTemp;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			// Jason НСО
			if(CheckAttribute(pchar, "questTemp.Patria.DodsonFail"))
			{
				dialog.text = "Charles, what the hell!";
				link.l1 = "Steven, there was an overlap. I could neither come nor inform you about my abscence...";
				link.l1.go = "patria_33";
				break;
			}
			if(CheckAttribute(pchar, "questTemp.Patria.DodsonAgain"))
			{
				dialog.text = "Glad to see you, pal! How can I help you? ";
				link.l1 = "Glad to see you too. I wanted to thank you for the perfectly conducted spectacle!";
				link.l1.go = "patria_29";
				break;
			}
			if(CheckAttribute(pchar, "questTemp.Patria.Saga.Shark") && pchar.questTemp.Patria == "epizode_12_pirates")
			{
				dialog.text = "Glad to see you, pal! How can I help you?";
				link.l1 = "I have a proposal for you. Piratical one, you know!";
				link.l1.go = "patria";
				break;
			}
			if(CheckAttribute(pchar, "questTemp.Patria.Saga.Shark") && pchar.questTemp.Patria == "epizode_12_talk")
			{
				dialog.text = "That's our customer! The job is done, your baron is sitting in a well-guarded dungeon. Perhaps you'd like to take a look, he-he?!";
				link.l1 = "I will have plenty of time to do that, ha-ha. Is he well-treated?";
				link.l1.go = "patria_10";
				break;
			}
			if(CheckAttribute(pchar, "questTemp.Tieyasal") && pchar.questTemp.Tieyasal == "begin" && !CheckAttribute(npchar, "quest.Tieyasal"))
			{
				dialog.text = "Glad to see you, pal! How can I help you?";
				link.l1 = "I've come again to ask for your help.";
				link.l1.go = "tieyasal";
				break;
			}
			if(CheckAttribute(pchar, "questTemp.Guardoftruth.Archy") && pchar.questTemp.Guardoftruth.Archy == "islatesoro")
			{
				dialog.text = "Glad to see you, pal! How can I help you?";
				link.l1 = "Steven, I've got something for you.";
				link.l1.go = "guardoftruth";
				break;
			}
			if(CheckAttribute(pchar, "questTemp.Saga.Shadows") && pchar.questTemp.Saga.Shadows == "islatesoro")
			{
				dialog.text = "Glad to see you, pal! How can I help you?";
				link.l1 = "Steven, I have to ask you something. You might not like it, but I need your help.";
				link.l1.go = "shadows";
				break;
			}
			if(CheckAttribute(pchar, "questTemp.Terrapin") && pchar.questTemp.Terrapin == "islatesoro")
			{
				dialog.text = "Ha, here you are, "+pchar.name+". I was expecting your arrival. Forest Devil told me about your trouble with Tortuga...";
				link.l1 = "He also told me that you had already found a solution. Is it true?";
				link.l1.go = "terrapin";
				break;
			}
			if(CheckAttribute(pchar, "questTemp.Terrapin.Catherina") && pchar.questTemp.Terrapin == "tortuga")
			{
				dialog.text = "How are we doing, "+pchar.name+"?";
				link.l1 = "Secrets everywhere... I need your advice, Steven.";
				link.l1.go = "terrapin_8";
				break;
			}
			dialog.text = "A-ah, my friend "+GetFullName(pchar)+"! Come in, I am glad to see you! What do you want?";
			link.l1 = "I just wanted to pay you a short visit.";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
		// --------------------------------------вариант R-----------------------------------------------
		case "Chad_die":
			dialog.text = "Ha! I take it that you are our night visitor? I was informed about this accident too late. I checked you belongings and found a letter from Forest Devil. Hell, it almost smelled of Main's jungles\nYour name is "+GetFullName(pchar)+"? Don't be surprised, I read it from the letter. My name is Steven Dodson. Or simply Shark. The Shark. I think, that you have already heard about me. I currently occupy a position of admiral in this city or island, whatever\nI apologize for the actions of my men last night. It was my order to capture everyone who sneaks inside the hold. Too many thieves among Narwhals and Rivados\nChad let you go, I assume? Odd. I was only going to send him an order to release you. Where is your ship? I hope she is fine?";
			link.l1 = "Chad? As far as I understand, your boatswain would never let me leave the prison alive. I did it myself and I also set free one black guy of these... Rivados.";
			link.l1.go = "Chad_die_1";
		break;
		
		case "Chad_die_1":
			dialog.text = "You are telling me interesting things, pal. And how did you make it out of 'Tartarus'? It looks like I will have a nice chat with Chad and his prison guards...";
			link.l1 = "You won't have any chat with them. They will never be talking again, I'm afraid. Chad threatened to keep me in the cage forever. He blamed me for being Rivados and he demanded that I prove it otherwise by killing the black wizard Chimiset...";
			link.l1.go = "Chad_die_2";
		break;
		
		case "Chad_die_2":
			dialog.text = "What the hell?! Such a foolish self-will! We need Chimiset alive, and Chad perfectly knew that! And why would he assume that you were Rivados, if all of them are black? What is he up for, damn him?";
			link.l1 = "He is up for something you surely won't like, Steven. Chad gave me a machete and sent me downstairs to kill Chimiset. But the old Black has told me something important, and I realized that if I kill Chimiset, I'll be the next...";
			link.l1.go = "Chad_die_3";
		break;
		
		case "Chad_die_3":
			dialog.text = "";
			link.l1 = "Instead of killing the old man I have opened a chest with ammunition and fought with Chad and his buddies. Do you see now why you can't talk to them anymore? They are all dead.";
			link.l1.go = "Chad_die_4";
		break;
		
		case "Chad_die_4":
			dialog.text = "Fuck! The news just gets more and more terrifying! And what should I do with all of that mess?";
			link.l1 = "Listen to me, Steve. Chimiset told me that Chad had a deal with some Narwhals - this is the other clan as far as I understand. Chad was planning to kill you and take your position. Narwhals are eager to see you dead, because they are certain that you had killed their leader Allen... or Alan, I don't remember.";
			link.l1.go = "Chad_die_5";
		break;
		
		case "Chad_die_5":
			dialog.text = "Bullshit! I didn't kill Alan! Someone else did that, even Narwhals, perhaps. I think that their current leader - Donald Greenspen - killed Alan!";
			link.l1 = "No. Chad murdered him. Chimiset had witnessed the crime - that is why they wanted to kill him, too. Chad didn't want to do that himself for some reason - it looks like he was afraid of a curse of some sort. That is why he wanted me to do the job.";
			link.l1.go = "Chad_die_6";
		break;
		
		case "Chad_die_6":
			dialog.text = "I can't believe it... Chad killed Alan? But why?";
			link.l1 = "To leave you the blame and to make you enemies with Narwhals. I suppose that he was the one spreading rumours, because why would Narwhals blame you and you only? Steven, they are planning to kill you. And the Rivados clan would be blamed for that - I don't know how they are going to do it though. Chimiset told me about that.";
			link.l1.go = "Chad_die_7";
		break;
		
		case "Chad_die_7":
			dialog.text = "";
			link.l1 = "Besides, I have found this letter in Chad's chest. Read it. It looks like a solid proof, though it is indirect.";
			link.l1.go = "Chad_die_8";
		break;
		
		case "Chad_die_8":
			RemoveItems(pchar, "letter_chad", 1);
			dialog.text = "...(reading)... heh! I am not surprised of Chad's betrayal. Son of a bitch always wanted power on this island. But Narwhals! To seriously believe that it was me who killed Alan! This will cost them a double price for provisions\nI was planning to release Chimiset anyway, it's high time to make peace with them. You have shocked me, buddy, to be honest...";
			link.l1 = "I understand, Steven. I don't like it, either, I got in the middle of some political mess since I have reached the Island. I came here only to find you and Nathaniel Hawk...";
			link.l1.go = "Chad_die_9";
		break;
		
		// ноды пересечения
		case "Chad_die_9":
			dialog.text = "What? Hawk? Isn't he on Jamaica? He is a baron of Maroon town, why would he be here?";
			link.l1 = "No. Jackman is in command there now. I was able to find out that Hawk had gotten there the same way I did - through the portal of Kukulcan.";
			link.l1.go = "Chad_die_10";
		break;
		
		case "Chad_die_10":
			dialog.text = "What's all this nonsense? What portal? And you still haven't answered - where is your ship?";
			link.l1 = "There is no ship. I understand, Steve, that it is difficult to believe, but I really got here through the Indian idol from the Main... don't look at me like that - I am not crazy! I myself don't understand how is it possible, but it is!";
			link.l1.go = "Chad_die_11";
		break;
		
		case "Chad_die_11":
			dialog.text = "";
			link.l1 = "The shaman in Miskito village has seen how Nathaniel Hawk, who was escaping from the chasers, ran to the Indian idol, which is known as a statue of Kukulcan, and suddenly disappeared. This shaman told me that he had been on this Island himself, and that he went there the same way through the statue...";
			link.l1.go = "Chad_die_12";
		break;
		
		case "Chad_die_12":
			dialog.text = "";
			link.l1 = "I'm looking for Nathan, so that is why I had to walk in his footsteps. I came to the statue at midnight, just as the shaman told me. You won't believe it, but the top of stone statue was golden that night, and a mysterious light was glowing above it!";
			link.l1.go = "Chad_die_13";
		break;
		
		case "Chad_die_13":
			dialog.text = "";
			link.l1 = "As soon as I had touched the statue, a circle of light formed around the idol, fire blazed up, and then I was drawned into the statue. I was thrown out here, in your ship's cargo hold, downstairs near the bow, at the breach...";
			link.l1.go = "Chad_die_14";
		break;
		
		case "Chad_die_14":
			dialog.text = "";
			link.l1 = "I barely survived that, thanks to the shaman, who had given me a special potion. In the end I was attacked by some monster - a giant crab. I hope that now you trust me?";
			link.l1.go = "Chad_die_15";
		break;
		
		case "Chad_die_15":
			dialog.text = "You mean the part about crab? I believe you in that. There are lot of these monsters around the island. We bait them with a dead fish, so they often guard our back door. Scares thieves shitless. And what you've told about the idol - I am not crazy yet\nBut I will not reject you story either, locals have been gossiping about such things for several dozens of years, plus I saw strange things myself long ago at Rivados' ships... nevermind.";
			link.l1 = "I swear that it is all truth.";
			link.l1.go = "Chad_die_16";
		break;
		
		case "Chad_die_16":
			dialog.text = "Fine. So be it. Tell me, why have you been looking for me and Nathan? According to Jan's letter, you wanted me to become the head of the Brethren of the Coast?";
			link.l1 = "Exactly. Many things have changed after your and Hawk's disappearance. Jackman is trying to play the central role among the pirates. He is planning to become their leader, and he will succeed, if Jan and me don't stop him.";
			link.l1.go = "Chad_die_17";
		break;
		
		case "Chad_die_17":
			dialog.text = "";
			link.l1 = "Jackman is up for a serious and bloody game. I am sure that it was him, who had organized the ambush and hunt for Nathaniel. I also think that he killed Blaze. Making you the leader of the Brethren of the Coast is the only way to stop him.";
			link.l1.go = "Chad_die_18";
		break;
		
		case "Chad_die_18":
			dialog.text = "Look, I'd be glad, but we need to leave this island first. I had enough of it. All the more so that I can leave Dexter here, he can manage doing business in my absence. I didn't intend to stay here for that long, but my ship was burnt down in a fight against the clans\nI am not going to travel through those portals, don't even try to persuade me, I need a ship.";
			link.l1 = "I won't... Steven, the Miskito shaman told me that there was a statue of Kukulcan here, on the Island. It looks like an ordinary stone idol. Do you know where I can find it?";
			link.l1.go = "Chad_die_19";
		break;
		
		case "Chad_die_19":
			dialog.text = "I don't. I have never seen any statues like that. Ask somebody else.";
			link.l1 = "See, if I find this statue, I will be able to get away from this island without a ship. The trip doesn't scare me anymore. And then I would return here in a normal way and take you from here.";
			if (pchar.questTemp.LSC == "entrance" || pchar.questTemp.LSC == "mary") link.l1.go = "entrance_4";
			else link.l1.go = "Chad_die_20";
		break;
		// ноды пересечения
		
		case "Chad_die_20":
			dialog.text = "I understand, but I can not help you. Plus, this assassination thing is quite disturbing. Chad is dead, but I doubt that Narwhals will drop their plan. I do not want to live expecting to be shot in the back every day. Since you need me alive and you are already involved in this mess, I offer you to investigate this conspiracy\nYour are a newcomer, it's an advantage. Find Chad's partners and bring them to me or kill them where they stand, I don't care. Talk to Chimiset, old black knows more than he's told us already\nBe careful with Narwhals, don't cross their borders unless you have got a password. They change passwords every week.\nOnce the threat is eliminated, I will provide you with sailing directions and all information you need\nGo and find those who responsible. Restore order. I will make sure they clean prison after you. And we need a new jailer. And I need some rum, I don't feel well.";
			link.l1 = "Fine, Steven. Let's do that...";
			link.l1.go = "Chad_die_21";
		break;
		
		case "Chad_die_21":
			DialogExit();
			NextDiag.CurrentNode = "Total_wait";
			pchar.questTemp.LSC.rvd_friend = "true"; //флаг на проход по кораблям ривадос
			sld = characterFromId("Chimiset");
			sld.dialog.currentnode = "Friend"; //ноду Чимисету
			pchar.quest.LSC_Eddy.win_condition.l1 = "location";
			pchar.quest.LSC_Eddy.win_condition.l1.location = "ProtectorFisher";
			pchar.quest.LSC_Eddy.function = "LSC_EddyTalk"; //на разговор с Эдди
			AddQuestRecord("SharkHunt", "10");
			sld = characterFromId("Facio");
			sld.quest.parol = true;
			AddSimpleRumourCityTip("Just imagine: someone has killed the admiral's jailer, Chad Kapper. Impossible! No doubt, that was the Rivados wizard's job...", "LostShipsCity", 7, 2, "LSC", "");
			AddSimpleRumourCityTip("I heard that Chad Kapper is dead. There was no official statement; his body was never found, either. Perhaps, the admiral had simply given him a secret mission?", "LostShipsCity", 7, 2, "LSC", "");
			AddSimpleRumourCityTip("I don't see our jailer Chad Kapper. Some people say that he was killed and some disagree. Anyway, no one has seen him dead.", "LostShipsCity", 7, 2, "LSC", "");
			AddSimpleRumourCityTip("They say that the admiral has doubled provision prices for Narwhals! That pirate is truly reckless!", "LostShipsCity", 7, 3, "LSC", "");
		break;
		
			case "Mary_Die":
			dialog.text = "Well, what do you have, "+pchar.name+"? Any news about Narwhals?";
			link.l1 = "Yes. You will be glad to know, Steve, that the conspiracy was unveiled and the plotters are dead. I have all the proofs.";
			link.l1.go = "Mary_Die_1";
		break;
		
		case "Mary_Die_1":
			if (CheckAttribute(pchar, "questTemp.Saga.SharkHunt.TownAttack")) dialog.text = "I thought so when I heard the gunfight... Tell me more, I am listening.";
			else dialog.text = "Is that so? I am really glad to hear that! Tell me more, I am listening.";
			link.l1 = "It was all planned by your boatswain, Chad Kapper. He killed Alan Milrow in the 'Tartarus' prison, and he was spreading gossips about your involvement. I think that Narwhals were really angry, and it was a hard blow for Alan's girlfriend, Red Mary...";
			link.l1.go = "Mary_Die_2";
		break;
		
		case "Mary_Die_2":
			dialog.text = "";
			link.l1 = "Mary was eager to take vengeance and Chad Kapper used it for his own ends. They made a cunning plan of an attempt on your life. Everyone here knows about your habit of walking around on the stern of the 'San Augustine' every evening.";
			link.l1.go = "Mary_Die_3";
		break;
		
		case "Mary_Die_3":
			dialog.text = "Heh! I will reconsider my habits... Go on.";
			link.l1 = "They needed a long-range and accurate musket to perform their plan, and so some Adolf Barbier provided it. But his stutzen was pawned to Giuseppe Fazio, so Mary and Chad gave him enough money to buy it back. Adolf got it out of pawn...";
			link.l1.go = "Mary_Die_4";
		break;
		
		case "Mary_Die_4":
			dialog.text = "";
			link.l1 = "They hired Cyclops Marcello, an ex royal huntsman, to kill you. He had to receive the rifle and shoot you dead. After that Mary would have killed him and used his corpse and rifle as a proof that Rivados were responsible for the attack. Cyclops Marcello is a mulatto, you know...";
			link.l1.go = "Mary_Die_5";
		break;
		
		case "Mary_Die_5":
			dialog.text = "Such a smart bastard!";
			link.l1 = "After that, Narwhals and pirates would attack Rivados and destroyed them. Chad would become an admiral and Mary would be his lover. Perhaps, though, he would have cut her throat instead, since she knew too much. Quite probably...";
			if (CheckAttribute(pchar, "questTemp.Saga.SharkHunt.TownAttack")) link.l1.go = "Mary_Die_6a";
			else link.l1.go = "Mary_Die_6";
		break;
		
		case "Mary_Die_6":
			dialog.text = "";
			link.l1 = "Anyway, it is over now. Adolf wasn't talkative enough, and I had to kill him right in his cabin. I also had to deal with Mary and Cyclops, who had come to get the stutzen from Adolf. They realized, who I was at once, and attacked me immediately.";
			link.l1.go = "Mary_Die_7";
		break;
		
		case "Mary_Die_7":
			dialog.text = "So they are lying down inside 'Santa Florentina', right?";
			link.l1 = "Yes. All three of them.";
			link.l1.go = "Mary_Die_8";
		break;
		
		case "Mary_Die_8":
			dialog.text = "That is good that no witnesses were involved in this mess. I will take care of the bodies. You did a good job, "+pchar.name+"! Were you in my crew, I'd definitely have made you my first mate.";
			link.l1 = "Thanks for such a high response! And, finally, take a look at these letters. I took them from the bodies of Cyclops and poor Mary...";
			link.l1.go = "Mary_Die_9";
			AddSimpleRumourCityTip("Have you heard that? Our squabbler and madcap Red Mary has disappeared. I won't be surprised if she is dead...", "LostShipsCity", 10, 1, "LSC", "");
			AddSimpleRumourCityTip("They say that Red Mary has disappeared. Have you heard about it?", "LostShipsCity", 10, 1, "LSC", "");
			AddSimpleRumourCityTip("Mary Casper has vanished. Some people say that she is still inside her cabin but I don't believe it. It's been too long since there last was light in it.", "LostShipsCity", 10, 1, "LSC", "");
			AddSimpleRumourCityTip("They say that Red Mary was murdered. Poor girl! Yes, she had tough character, but everybody loved her. Who could have done such a terrible thing?", "LostShipsCity", 10, 1, "LSC", "");
		break;
		
		case "Mary_Die_6a":
			dialog.text = "";
			link.l1 = "Anyway, it is over now. Adolf wasn't talkative enough, and I had to kill him right in his cabin. I also had to deal with Mary and Cyclops, who had come to get the stutzen from Adolf. They realized, who I was, at once, and attacked me immediately.";
			link.l1.go = "Mary_Die_7a";
		break;
		
		case "Mary_Die_7a":
			dialog.text = "Too bad that you have started a fight on 'Eva'. Now Narwhals are aware that you are responsible for killing their men, such actions won't improve your reputation. Same can be said about mine. Don't pay them a visit until you fix this conflict\nIn general, you did good, "+pchar.name+"! Were you in my crew, I'd definitely have made you my first mate.";
			link.l1 = "Thanks for such a high response! And, finally, take a look at these letters. I took them from the bodies of Cyclops and poor Mary...";
			link.l1.go = "Mary_Die_9";
			AddSimpleRumourCityTip("Such a massacre you have performed here! Narwhals won't forget about it!", "LostShipsCity", 5, 2, "LSC", "");
			AddSimpleRumourCityTip("I understand killing Cyclops and two Narwhal bandits... But the girl, why have you killed the girl? Poor Mary...", "LostShipsCity", 7, 5, "LSC", "");
		break;
		
		case "Mary_Die_9":
			RemoveItems(pchar, "letter_chad", 1);
			RemoveItems(pchar, "letter_chad_1", 1);
			dialog.text = "Poor Mary? Are you feeling sorry for that whore?";
			link.l1 = "I really am. See, Chad deceived her and used her. She couldn't resist her feelings and natural hotheadedness... and that's where it got her.";
			link.l1.go = "Mary_Die_10";
		break;
		
		case "Mary_Die_10":
			TakeNItems(pchar, "gold_dublon", 500);
			Log_Info("You have received 500 doubloons");
			PlaySound("interface\important_item.wav");
			CloseQuestHeader("SharkHunt");
			dialog.text = "Well, go see brother Julian and light a candle... I won't do that myself, though. Alright, let's drop the subject. I am grateful to you, "+pchar.name+", for your help. You can count on my support now. I want to pay you for your excellent work. Here, take five hundred doubloons.";
			link.l1 = "Nice, thanks!";
			link.l1.go = "LSC_navy";
			AddSimpleRumourCityTip("They say that the admiral respects you, mister...", "LostShipsCity", 15, 2, "LSC", "");
			AddSimpleRumourCityTip("They say that you are the admiral's loyal friend. Is that true?", "LostShipsCity", 15, 2, "LSC", "");
		break;
		
		// ----------------------------------------вариант N---------------------------------------------------
		case "entrance":
			dialog.text = "What do you want? I don't remember you...";
			link.l1 = "Of course, you don't - we have never met before, and I've come here just recently. Hello, Steven. Such a rare luck! I have found you after all, I've been looking for you though I didn't expect to find you here!";
			link.l1.go = "entrance_1";
		break;
		
		case "entrance_1":
			dialog.text = "Wait, pal, calm down. Looking for me? I don't like it. Why the hell have you been looking for me?";
			link.l1 = "I see. Let's try again then. Here, take the letter. It is written by Jan Swanson for you. I suppose that all your suspicions will be wiped away after you read it.";
			link.l1.go = "entrance_2";
		break;
		
		case "entrance_2":
			RemoveItems(pchar, "letter_svenson", 1);
			PlaySound("interface\important_item.wav");
			dialog.text = "(reading)... Hm. That explains a lot. And I thought that you were going to give me a black mark for Blaze's death. You know, recently there have been many guys eager to do that. Did you leave your ship at the outer ring? And how did you know that I was here?";
			link.l1 = "I didn't. That was a lucky chance. And about Blaze... Jan and me think that you are not responsible for his death.";
			link.l1.go = "entrance_3";
		break;
		
		case "entrance_3":
			dialog.text = "And you are right. I am not. Someone is trying to blame me, that is true. But I didn't kill him.";
			link.l1 = "That is good. Interesting, I came here to find Nathaniel Hawk, but I have found you instead, ha-ha!";
			link.l1.go = "Chad_die_9";
		break;
		
		case "entrance_4":
			dialog.text = "I understand but I can't help you. You have to talk about it with the old-timers of this Island. Talk to Rivados wizard Chimiset. The old black man knows much more than he says.";
			link.l1 = "And where can I find this wizard?";
			if (pchar.questTemp.LSC == "mary") link.l1.go = "mary";
			else link.l1.go = "entrance_5";
		break;
		
		case "entrance_5":
			dialog.text = "In my prison, on 'Tartarus'. I was planning to release him anyway, it's time to improve our relations with Rivados. Right! Go to the prison, tell Chad Kapper, he is a jailer, that I have ordered to release Chimiset\nTell the black man why I sent you, tell him that I will release him if he is talkative enough. I am sure this will make him talk.";
			link.l1 = "Hm... I am a newbie here. Where is the prison?";
			link.l1.go = "entrance_6";
		break;
		
		case "entrance_6":
			dialog.text = "Keep the following in mind. Leave my residence, cross the bridge, turn left, go through frigate Carolina to galleon Gloria and you will get to Esmeralda. Look for a sign of store and enter the doors beneath it. Get through the door in the bow part of the ship and you will reach Tartarus\nBe careful at Esmeralda, it is a property of Narwhals clan, even though, others can visit it. Do not cross their fighters and avoid any troubles.";
			link.l1 = "Who are these Rivados and Narwhals?";
			link.l1.go = "entrance_7";
		break;
		
		case "entrance_7":
			dialog.text = "The clans have been living here for a very long time. They represent offsprings of first settlers. Narwhals are mostly English, Dutch and French, Rivados are all Negro. Every clan has a leader, they hold several ships and don't let others into their territory\nYou must know passwords in order to visit them. They change passwords every week.";
			link.l1 = "Fine. I will deal with that. Will they let me get inside the prison?";
			link.l1.go = "entrance_8";
		break;
		
		case "entrance_8":
			dialog.text = "They will. Here is the key, so Chad will know that I have sent you there. Take it.";
			link.l1 = "Fine. Then I will talk with that... Chimiset and then I will be back with the results.";
			link.l1.go = "entrance_9";
		break;
		
		case "entrance_9":
			DialogExit();
			GiveItem2Character(pchar, "key_capper");
			NextDiag.CurrentNode = "Total_wait";
			sld = characterFromId("Chimiset");
			sld.dialog.currentnode = "prisoner"; //даем ноду Чимисету
			sld.quest.chimiset_die = "true";
			ChangeCharacterAddressGroup(sld, "Tartarusprison", "quest", "prison2"); // в закрытую клетку
			LAi_SetGroundSitTypeNoGroup(sld);
			sld = characterFromId("Capper");
			sld.dialog.currentnode = "prisoner"; //даем ноду Капперу
			LAi_LocationFightDisable(&Locations[FindLocation("Tartarusprison")], true);//запретить драться
			// прерывания на локаторы тартаруса
			pchar.quest.LSC_TartarusEntrance1.win_condition.l1 = "locator";
			pchar.quest.LSC_TartarusEntrance1.win_condition.l1.location = "LostShipsCity_town";
			pchar.quest.LSC_TartarusEntrance1.win_condition.l1.locator_group = "reload";
			pchar.quest.LSC_TartarusEntrance1.win_condition.l1.locator = "reload51";
			pchar.quest.LSC_TartarusEntrance1.win_condition.l2 = "item";
			pchar.quest.LSC_TartarusEntrance1.win_condition.l2.item = "key_capper";
			pchar.quest.LSC_TartarusEntrance1.function = "LSC_TartarusEntrance1_Open";
			pchar.quest.LSC_TartarusEntrance2.win_condition.l1 = "locator";
			pchar.quest.LSC_TartarusEntrance2.win_condition.l1.location = "LostShipsCity_town";
			pchar.quest.LSC_TartarusEntrance2.win_condition.l1.locator_group = "reload";
			pchar.quest.LSC_TartarusEntrance2.win_condition.l1.locator = "reload52";
			pchar.quest.LSC_TartarusEntrance2.win_condition.l2 = "item";
			pchar.quest.LSC_TartarusEntrance2.win_condition.l2.item = "key_capper";
			pchar.quest.LSC_TartarusEntrance2.function = "LSC_TartarusEntrance2_Open";
			AddQuestRecord("SharkHunt", "19");
		break;
		
		case "entrance_10":
			dialog.text = "So, have you been on 'Tartarus'?";
			link.l1 = "Yes. I have given your orders to Chad and I had a talk with the black man.";
			link.l1.go = "entrance_11";
		break;
		
		case "entrance_11":
			dialog.text = "Did the wizard tell you anything interesting?";
			link.l1 = "Oh, yes. He told me where to find the teleportation idol of Kukulcan. It was on 'San Geronimo' ship, which had sunk at the shoal near the Narwhals' territory.";
			link.l1.go = "entrance_12";
		break;
		
		case "entrance_12":
			dialog.text = "Ha-ha-ha, great! So your 'portal' is at the bottom now? Well, pal, I'm afraid that you are locked up on this island. So join me and my men...";
			link.l1 = " I will figure out a way to get to the idol. I will find the way. Now. Chimiset told me that you should not trust Kapper, because he saw Chad killing some Alan Milrow, the head of Narwhals, with his own eyes.";
			link.l1.go = "entrance_13";
		break;
		
		case "entrance_13":
			dialog.text = "What?! Chad killed Alan? That wizard is insane! It simply cannot be true!";
			link.l1 = "You know, Steve, Chimiset is really scared. I don't think that he was lying to me.";
			link.l1.go = "entrance_14";
		break;
		
		case "entrance_14":
			dialog.text = "Damn it, now that is really bad news! Alan's murder has already spoiled my reputation among Narwhals - some of them decided that I was responsible for it, and now it turns out that one of my officers could have done that!";
			link.l1 = "It seems that people like blameing you for the sins which are not yours...";
			link.l1.go = "entrance_15";
		break;
		
		case "entrance_15":
			dialog.text = "Yeah, that is troubling...";
			link.l1 = "And now, the 'nicest' news for you - the old man told me that he had overheard several conversations and figured out that some of your men were planning to kill you. He will tell you more only after you release him, and in private.";
			link.l1.go = "entrance_16";
		break;
		
		case "entrance_16":
			dialog.text = "Great! And all of this because of you! No offence, I am just joking. My head is going round: Chad killed Alan, my men are planning an attempt on my life... Has the old black man told you any details?";
			link.l1 = "No. He fears Chad too much, as far as I understood.";
			link.l1.go = "entrance_17";
		break;
		
		case "entrance_17":
			dialog.text = "Fine. I will tell Rivados that I want to meet with Chimiset. We'll see what he tells me. And concerning the attempt... fine, I will be careful. So, what are you going to do now, "+pchar.name+"?";
			link.l1 = "Nothing in particular yet. I will walk around the Island and get to know the locals - perhaps I will come up with an idea how to get out of this place. And I need to find Nathan Hawk first, he is the reason why I am here.";
			link.l1.go = "entrance_18";
		break;
		
		case "entrance_18":
			dialog.text = "I see. Don't forget to visit me when you find a way out of this island - I will give you the sailing directions, you won't be able to get back here without them. I will also tell you some important details.";
			link.l1 = "Fine. I will visit you for sure, Steve!";
			link.l1.go = "entrance_19";
		break;
		
		case "entrance_19":
			DialogExit();
			NextDiag.CurrentNode = "Total_wait";
			sld = characterFromId("Facio");
			sld.quest.parol = true;
			// прерывание на вызов к Акуле
			pchar.quest.LSC_GotoShark.win_condition.l1 = "Timer";
			pchar.quest.LSC_GotoShark.win_condition.l1.date.hour  = 9.00;
			pchar.quest.LSC_GotoShark.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.LSC_GotoShark.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.LSC_GotoShark.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.LSC_GotoShark.win_condition.l2 = "location";
			pchar.quest.LSC_GotoShark.win_condition.l2.location = "LostShipsCity_town";
			pchar.quest.LSC_GotoShark.function = "LSC_GotoShark";
			AddQuestRecord("SharkHunt", "21");
		break;
		
		case "entrance_20":
			dialog.text = "It is good that you have come, "+pchar.name+". I have been waiting for you. Bad news. Chimiset is dead, Chad Kapper has vanished without a trace.";
			link.l1 = "Fuck... I am sure that Chad has killed Chimiset! The old black man was so scared not without a reason.";
			link.l1.go = "entrance_21";
		break;
		
		case "entrance_21":
			dialog.text = "I have no doubt in that. Crap, the situation is getting worse every hour. I have almost arranged solid and straight contacts with Black Eddie and now this. Well, we can forget about friendship with Rivados\nThey know that you were talking to Chimiset before he died, and they consider you as one of my men, so avoid contacting them.";
			link.l1 = "Yeah, what a pity...";
			link.l1.go = "entrance_22";
		break;
		
		case "entrance_22":
			dialog.text = "I have asked you to come not only to tell news. I have received a letter from our mediator and diplomat, Giuseppe Fazio, he invites me to visit his cabin in Carolina at midnight. He also mentions that I must come alone, because this is my life at stake and no one can be trusted\nThis makes sense, Chimiset warned us about a traitor close to me. Yet it smells too suspicious... alone, at midnight... Normally, the fat man himself comes to me. Anyway, I am going to ask for your help\nTechnically, you are not one of my men and you are new here. Jan characterized you as a resourceful and brave man with good skills in fencing. I want you to escort me to the meeting at midnight...";
			link.l1 = "You don't need to ask me, Steven. I'm in. I don't like this invitation either - it smells like a trap.";
			link.l1.go = "entrance_23";
		break;
		
		case "entrance_23":
			dialog.text = "Perhaps, I am wrong and there is no trap, but I'd better be ready. I am glad that you have agreed. Come at the deck of the 'San Augustine' at midnight, and we will go see Fazio, his old tub is not far from here.";
			link.l1 = "Deal. I will be at the deck of 'San Augustine' at midnight and well-armed.";
			link.l1.go = "entrance_24";
		break;
		
		case "entrance_24":
			DialogExit();
			NextDiag.CurrentNode = "Total_wait";
			pchar.quest.LSC_GotoShark.win_condition.l1 = "Timer";
			SetFunctionTimerCondition("LSC_MeetingSharkAugustine", 0, 0, 1, false); // таймер
			AddQuestRecord("SharkHunt", "22");
		break;
		
		case "caroline":
			dialog.text = "Glad to see you, "+pchar.name+". Let's not waste time and see, what that fat man Fazio has to say. Follow me!";
			link.l1 = "Let's go, Steve. Keep your weapon ready...";
			link.l1.go = "caroline_1";
		break;
		
		case "caroline_1":
			DialogExit();
			sld = characterFromId("Dodson");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload25", "CarolineBank", "barmen", "bar2", "LSC_CarolineOpen", -1);
		break;
		
		case "caroline_2":
			dialog.text = "And where is that fucking fat man? Where did he go? We are his guests and he is not welcoming us. Do you see him, "+pchar.name+"? Perhaps, we should check his chests, he might be in them...";
			link.l1 = "He won't be able to get inside any chest in the world anyway. Hush! Steven! There's noise outside...";
			link.l1.go = "caroline_3";
		break;
		
		case "caroline_3":
			dialog.text = "Fuck! You are right. It seems that we are in trouble."+pchar.name+".";
			link.l1 = "...";
			link.l1.go = "caroline_4";
		break;
		
		case "caroline_4":
			DialogExit();
			LAi_SetPlayerType(pchar);
			// запускаем Мэри, Чада и нарвалов - будет лютое рубилово
			sld = characterFromId("Capper");
			sld.cirassId = Items_FindItemIdx("cirass1");
			LAi_SetActorType(sld);
			ChangeCharacterAddressGroup(sld, "CarolineBank", "reload", "reload3");
			sld = characterFromId("Mary");
			sld.greeting = "mary_4";
			int iScl = MOD_SKILL_ENEMY_RATE*10 + 2*sti(pchar.rank);
			LAi_SetHP(sld, 250+iScl, 250+iScl); // усилим
			sld.dialog.currentnode = "caroline";
			ChangeCharacterAddressGroup(sld, "CarolineBank", "reload", "reload2");
			LAi_SetActorType(sld);
			LAi_ActorDialogNow(sld, pchar, "", -1);
		break;
		
		case "caroline_5":
			dialog.text = "Argh! We did it... To be honest, I thought that we were dead for sure.";
			link.l1 = "I've been in troubles worse than this. But I admit, those bastards were tough. Chimiset was right to warn us - Chad is a traitor. Who was the girl commanding them?";
			link.l1.go = "caroline_6";
		break;
		
		case "caroline_6":
			dialog.text = "Her name is Mary Casper, also known as Red Mary, the ex girlfriend of late Alan Milrow. I understand why Chad  has come here, he wanted to gain my position but what was she doing here?";
			link.l1 = "It's clear enough. You said that she was his lover, her intentions are clear - revenge. Poor girl didn't know that she was fighting on the same side with her boyfriend's murderer.";
			link.l1.go = "caroline_7";
		break;
		
		case "caroline_7":
			dialog.text = "Makes sense. Well, now they will pay for everything! I will stop selling them supplies and provision - let them starve to death. My men can stand any siege, in case Narwhals try to storm the San Augustine, we will shoot them like dogs\nThey are going to regret for acting against me in such low manner. I will nail Fazio's fat ass to the wall behind by chair!";
			link.l1 = "Wait, Steve. It seems that it is not that clear. Give me one day and I will try to investigate this mess. I am sure that Chad is the only man responsible. He killed Milrow, spread the rumour that it was you, used Alan's girlfriend...";
			link.l1.go = "caroline_8";
		break;
		
		case "caroline_8":
			dialog.text = "Fine. Investigate. Perhaps, we haven't found all the plotters yet. And I will go and have some rum. And, "+pchar.name+": I owe you. You can count on me in everything. You would get a position of boatswain if you would have been in my crew.";
			link.l1 = "Thanks for such a high response! We will work together when you become head of Brethren of the Coast anyway. Go and have some rest and I will check this cabin, perhaps I will find something useful.";
			link.l1.go = "caroline_9";
		break;
		
		case "caroline_9":
			dialog.text = "Good. I will send my men here to clean up before morning - we don't want to scare people with dead bodies. Well, crabs will get a fine meal tonight! See you!";
			link.l1 = "See you...";
			link.l1.go = "caroline_10";
		break;
		
		case "caroline_10":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "SanAugustineResidence", "sit", "sit1", "LSC_SharkReturnSit", 10.0);
			AddQuestRecord("SharkHunt", "24");
		break;
		
		case "narval":
			dialog.text = "Well, "+pchar.name+", I take it that your investigation was fruitful?";
			link.l1 = "You can say so. Narwhals are not involved in the attempt on your life. Except for Mary and those guys who had met us 0n the 'Carolina'. I think that she instigated them to attack us. Fazio was forced to send you the invitation. I have found the letter in his cabin which explains a lot. Read it.";
			link.l1.go = "narval_1";
		break;
		
		case "narval_1":
			RemoveItems(pchar, "letter_chad_1", 1);
			dialog.text = "(reading)... Hm. That looks like a Fazio's type. Sure, what could he do against Chad... he was saving his fat skin. It seems that it was all because of my boatswain...";
			link.l1 = "You see it for yourself now. The motives are clear, and we know why Chad killed Chimiset and Alan. Kapper wanted to become the admiral of the island. I have visited the head of Narwhals - Donald Greenspen. He swore that neither him, nor anyone of his men were plotting against you.";
			link.l1.go = "narval_2";
		break;
		
		case "narval_2":
			dialog.text = "Do you trust him?";
			link.l1 = "I do. Donald will clear your name of accusations of Alan's death. He is ready to visit you personally and to bring you official excuses. You were blamed for nothing too, remember?";
			link.l1.go = "narval_3";
		break;
		
		case "narval_3":
			dialog.text = "Fine, declaring a war would be a bit too much. We are not in position to start a bloodshed. Plus, it looks like only a few scums are responsible for this, not the whole clan\nYou say that Donald is ready to apologize? Fine, let's use it to establish positive relations with Narwhals, Rivados are lost to us anyway.";
			link.l1 = "That is a good point, Steven. Now it's a perfect time for it.";
			link.l1.go = "narval_4";
		break;
		
		case "narval_4":
			dialog.text = "Fine. Tell Donald that I am ready to see him and make peace.";
			link.l1 = "I am on my way.";
			link.l1.go = "narval_5";
		break;
		
		case "narval_5":
			dialog.text = "Wait, "+pchar.name+". You did well and I want to pay you with fine coin. Here, take these five hundred doubloons.";
			link.l1 = "Thank you!";
			link.l1.go = "LSC_navy";
			TakeNItems(pchar, "gold_dublon", 500);
			Log_Info("You have received 500 doubloons");
			PlaySound("interface\important_item.wav");
			AddQuestRecord("SharkHunt", "27");
			pchar.questTemp.Saga.SharkHunt = "find"; //флаг - покушение предотвращено
			sld = characterFromId("Grinspy");
			sld.dialog.currentnode = "shark_16"; // ноду Дональду Гринспи
			SetFunctionTimerCondition("LSC_FacioReturn", 0, 0, 1, false); // вертаем на место Фацио через сутки
			AddSimpleRumourCityTip("They say that admiral respects you, mister...", "LostShipsCity", 15, 2, "LSC", "");
			AddSimpleRumourCityTip("They say that you are the admiral's loyal friend. Is that true?", "LostShipsCity", 15, 2, "LSC", "");
		break;
		
		// ----------------------------------------вариант M----------------------------------------------------
		case "mary":
			dialog.text = "In my prison 'Tartarus'. You can go there and see him. I will give you the key and Chad Kapper won't put obstacles in your way...";
			link.l1 = "Wait, Steven. I think that I shouldn't go to Chad Kapper yet...";
			link.l1.go = "mary_1";
		break;
		
		case "mary_1":
			dialog.text = "And why shouldn't you? What, don't you like him?";
			link.l1 = "Actually, it's you whom he doesn't like. I've got bad news for you. Chad Kapper is planning to make an attempt on your life.";
			link.l1.go = "mary_2";
		break;
		
		case "mary_2":
			dialog.text = "What?! Explain yourself. Who said that?";
			link.l1 = "Let me tell you the whole story. That would be better.";
			link.l1.go = "mary_3";
		break;
		
		case "mary_3":
			dialog.text = "Well, tell me, then...";
			link.l1 = "After I had found myself in the drowned cargo hold, I got out through the hole and swam among the ship wrecks to find a safe place. Finally, I climbed on the old flute and got inside the ship. There was a fight between some girl in red jacket and two big guys...";
			if (pchar.questTemp.LSC.Mary == "alive") link.l1.go = "mary_4"; // Мэри жива
			else link.l1.go = "mary_15";
		break;
		
		case "mary_4":
			dialog.text = "Heh, it seems that Red Mary has finally pissed someone off.";
			link.l1 = "I helped her and we finished those bastards. We had an interesting chat after that... Tell me, Steve, who are these Narwhals and Rivados, she was using these words so often that I was too shy to ask her what did they actually mean.";
			link.l1.go = "mary_5";
		break;
		
		case "mary_5":
			dialog.text = "The groups of local inhabitants who have been living here for a long time. They are the offsprings of the very first settlers of the Island. Narwhals are mostly English, Dutch and French, Rivados are all black. These clans have their own leaders, their own several ships and they don't let others on their territories. You have to know their passwords in case you want to visit clans' ships. They change them every week.";
			link.l1 = "I see now. I take it that Mary is with Narwhals?";
			link.l1.go = "mary_6";
		break;
		
		case "mary_6":
			dialog.text = "Yes, that expressive girl is from their clan. So what did she tell you?";
			link.l1 = "Chad Kapper killed Alan Milrow, her lover, who was captured by you. After that, he spread gossips about your involvement in this. Chad deceived Mary and tried to use her craving for revenge.";
			link.l1.go = "mary_7";
		break;
		
		case "mary_7":
			dialog.text = "Damn it! He killed Alan? But why? To leave me the blame?";
			link.l1 = "To make Narwhals hostile to you and to gain their trust. Kapper's final goal is to eliminate you and take your position. Mary has refused to take part in his plan and to become his lover - that is why he ordered Narwhals to kill her.";
			link.l1.go = "mary_8";
		break;
		
		case "mary_8":
			dialog.text = "Did she tell you that?";
			link.l1 = "Yes. And it didn't look like she was lying. Besides, she gave me a letter from Chad Kapper. I have already read it so you should do the same.";
			link.l1.go = "mary_9";
		break;
		
		case "mary_9":
			RemoveItems(pchar, "letter_chad_1", 1);
			dialog.text = "Hm. Yes, these are Chad's writings. I am very familiar with his peasant handwriting (reading) Argh! Unbelievable! Bastard! Traitor! Well, I am going to hang him on his own guts! Layton! Gather five men! On the second thought, Layton, wait, dismissed!\nWe will do it in a smart way. I have been planning to improve our relations with Rivados, this is a chance. Their wizard Chimiset is being held in Tartarus. A prison. We are going to let Rivados free their man themselves and in the act, they will kill the traitor\nLayton! Go to Tartarus and take all our guards from her upper deck! "+pchar.name+", you will also take part in this and I am about to assign a very important role to you. Find the leader of Rivados, Black Eddie, and negotiate with him...";
			link.l1 = "Me? Hm. But I don't know anyone here!";
			link.l1.go = "mary_10";
		break;
		
		case "mary_10":
			dialog.text = "So you will get to know some people soon - actually you will get to know the very first man of the entire Rivados clan. You are the most suitable candidate to perform the diplomatic part of my plan. My pirates won't be able to come through Rivados territories easily; also I don't have men with decent oratory skills.";
			link.l1 = "Well, fine. I am on it. What should I do?";
			link.l1.go = "mary_11";
		break;
		
		case "mary_11":
			GiveItem2Character(pchar, "key_capper");
			Log_Info("You have received 50 doubloons");
			PlaySound("interface\important_item.wav");
			TakeNItems(pchar, "gold_dublon", 50);
			dialog.text = "Take this key. It opens every door on 'Tartarus'. Also, take these fifty doubloons. First you should go to 'Carolina', buy a password in order to access Rivados territory. Talk to Fazio, he is our mediator, a password will cost you fifty doubloons. Then you should go to the 'Protector'\nIt's a residence of Black Eddie. Tell him that Chad Kapper is on the side of Narwhals, stopped following my orders and going to murder Chimiset. Give him the key, tell him to take a decent number of his fighters and to attack 'Tartarus'\nWe will kill two birds with one stone: Rivados will consider us their allies and Kapper will die by the hands of Negros. Can't say I envy the man. Got it?";
			if (pchar.questTemp.LSC.Mary == "alive")// Мэри жива
			{
				link.l1 = "I understand - but where to find 'Protector' and 'Carolina'?";
				link.l1.go = "mary_12";
			}
			else
			{
				link.l1 = "Listen, Steve, tell me who are those Rivados and Narwhals. You are talking about them all the time, but I still have no idea, who they are.";
				link.l1.go = "mary_12_1";
			}
		break;
		
		case "mary_12_1":
			dialog.text = "Narvals and Rivados are the local clans. The clans have been living here for a very long time. They represent offsprings of first settlers. Narvals are mostly English, Dutch and French, Rivados are all Negro. Every clan has a leader, they hold several ships and don't let others into their territory\nYou must know passwords in order to visit them. They change passwords every week.";
			link.l1 = "Now I see. Tell me - where to find 'Protector' and 'Carolina'?";
			link.l1.go = "mary_12";
		break;
		
		case "mary_12":
			dialog.text = "Easy as pie. Leave my residence, pass a bridge and turn left. This will be Carolina. Finding Protector is a bit trickier: after you have passed a bridge, turn right and go to Santa Florentina over boards\nFind Rivados soldiers there. They will ask for a password. Say it loud and clear. Then go inside Fury and enter Protector through the stern.";
			link.l1 = "Well, I see now. I think that I won't miss them.";
			link.l1.go = "mary_13";
		break;
		
		case "mary_13":
			dialog.text = "Very well, then. Get to it, friend!";
			link.l1 = "See you!";
			link.l1.go = "mary_14";
		break;
		
		case "mary_14":
			DialogExit();
			NextDiag.CurrentNode = "dodson_warwait";
			AddQuestRecord("SharkHunt", "32");
			sld = characterFromId("Eddy");
			sld.dialog.currentnode = "capper"; // ноду Эдди
			sld = characterFromId("Facio");
			sld.quest.parol = true;
			pchar.questTemp.LSC = "mary_go"; //меняем флаг
		break;
		
		case "dodson_warwait":
			dialog.text = "Are you still here? Go to Rivados now!";
			link.l1 = "I am on my way!";
			link.l1.go = "exit";
			NextDiag.TempNode = "dodson_warwait";
		break;
		
		case "mary_15":
			dialog.text = "Heh, it seems that Red Mary has finally pissed someone off.";
			link.l1 = "Yes. She pissed Chad Kapper off. I had joined the fight, but, unfortunately, I wasn't able to save the girl, one of the attacker has cut her with his saber.";
			link.l1.go = "mary_16";
		break;
		
		case "mary_16":
			dialog.text = "I am sorry for her, sure, but it was her fault no doubt. Mary had always been looking for trouble. And what about Chad Kapper? This is my boatswain, actually.";
			link.l1 = "Your boatswain? He-he... Here, read this letter. I have found it on the girl's body. You will see now, who had ordered to kill her and for what. Kapper is planning an attempt on your life.";
			link.l1.go = "mary_9";
		break;
		
		// Каппер сбежал
		case "Chad_escape":
			dialog.text = "Where have you been for so long? I've been told that Rivados freed their wizard...";
			link.l1 = "I was held as a hostage on 'Protector' to ensure their safety from an ambush. They have freed Chimiset, yes, but Chad managed to escape.";
			link.l1.go = "Chad_escape_1";
		break;
		
		case "Chad_escape_1":
			dialog.text = "Shit! Never deal with black, they say... They were unable to do even such a simple task! Fuck those Rivados!";
			link.l1 = "Chad has hidden among the Narwhals...";
			link.l1.go = "Chad_escape_2";
		break;
		
		case "Chad_escape_2":
			dialog.text = "Sure, he has! He is not a fool and he realized that Rivados couldn't have got inside Tartarus without my help. Now he will hide and attack from the shadows. Layton! Fortify the posts! Keep your eyes open all the time! I will pay a fortune to the man who will deal with Kapper!";
			link.l1 = "Fine, Steven. I need to think about it. Perhaps, I will be able to track Chad down. See you.";
			link.l1.go = "Chad_escape_3";
			NextDiag.TempNode = "Total_wait";
		break;
		
		case "Chad_escape_3":
			DialogExit();
			if (pchar.questTemp.LSC.Mary == "alive") 
			{
				pchar.questTemp.Saga.SharkHunt = "mary_whiskey"; // к Мэри
				AddQuestRecord("SharkHunt", "34");
			}
			else
			{ // не уберег Мэри - допетривай сам, куда идти
				pchar.questTemp.Saga.SharkHunt = "trader_whiskey"; // флаг на магазин - поиск виски
			}
			NextDiag.CurrentNode = "Total_wait";
			// добавим немного атмосферы - уберем Акселя до утра
			sld = characterFromId("Axel");
			LAi_SetStayType(sld);
			ChangeCharacterAddressGroup(sld, "EsmeraldaStoreBig", "goto", "goto5");
			sld = GetCharacter(NPC_GenerateCharacter("AxelHelper", "citiz_52", "man", "man", 35, PIRATE, 1, true, "quest"));
			FantomMakeCoolFighter(sld, 35, 100, 100, "blade_21", "pistol4", "bullet", 200);
			sld.dialog.Filename = "Quest\LSC\OtherNPC.c";
			sld.dialog.currentnode = "AxelHelper";
			LAi_SetOwnerType(sld);
			ChangeCharacterAddressGroup(sld, "EsmeraldaStoreBig", "barmen", "stay");
			LAi_group_MoveCharacter(sld, "LSC_NARVAL");
			SetFunctionTimerCondition("LSC_AxelReturnStore", 0, 0, 1, false); // таймер на возврат Акселя
		break;
		
		case "whiskey":
			dialog.text = "What happened, "+pchar.name+"? You look like you're being chased by Lucefer himself.";
			link.l1 = "Have they brought you a barrel of whiskey?";
			link.l1.go = "whiskey_1";
		break;
		
		case "whiskey_1":
			dialog.text = "What barrel?";
			link.l1 = "HAVE THEY BROUGHT YOU A BARREL OF WHISKEY?!";
			link.l1.go = "whiskey_2";
		break;
		
		case "whiskey_2":
			dialog.text = "Why are you shouting like that, pal? No, they haven't. What is the matter?";
			link.l1 = "Thank God I've come in time... Chad Kapper bought a barrel of Bushmills from Axel Yost...";
			link.l1.go = "whiskey_3";
		break;
		
		case "whiskey_3":
			dialog.text = "Bushmills? This is my favorite one! I haven't drunk it for ages!";
			link.l1 = "Yes-yes. And Kapper knows that, too. He also asked his pal, Marcello Cyclops, to buy some arsenic from Sancho Carpentero. See why?";
			link.l1.go = "whiskey_4";
		break;
		
		case "whiskey_4":
			dialog.text = "Do you think that he is going to poison me?";
			link.l1 = "No doubt! That is why I was in such a hurry. If they bring you a barrel of whiskey - don't drink it. It is poisoned.";
			link.l1.go = "whiskey_5";
		break;
		
		case "whiskey_5":
			dialog.text = "Heh, thanks for the warning! I will be careful. Wait, where are you going now?";
			link.l1 = "I need to find Kapper and Cyclops. I have an idea where to find them. See you!";
			link.l1.go = "whiskey_6";
		break;
		
		case "whiskey_6":
			DialogExit();
			pchar.questTemp.LSC.Dodson_warning = "true"; // Акула предупрежден
			LAi_CharacterDisableDialog(npchar);//запрещаем диалог
			AddQuestRecord("SharkHunt", "45");
		break;
		
		case "whiskey_7":
			dialog.text = "Ha! I am glad to see you, pal! It looks like I owe you my life.";
			link.l1 = "Have they brought whiskey?";
			link.l1.go = "whiskey_8";
		break;
		
		case "whiskey_8":
			dialog.text = "They have! Bushmills, just as you said. Our dear Fazio was so kind... I have arrested him to investigate...";
			link.l1 = "Has he confessed?";
			link.l1.go = "whiskey_9";
		break;
		
		case "whiskey_9":
			dialog.text = "Yes. He says that Kapper forced him to do that. He was scared and... brought me the barrel as a present from Narwhals.";
			link.l1 = "Kapper is dead. I have eliminated him and his Narwhal friends. Now there's just one bastard left - Cyclops Marcello... I am confident that this fat pig is aware of his whereabouts. Let me push him a bit!";
			link.l1.go = "whiskey_10";
		break;
		
		case "whiskey_10":
			dialog.text = "Sure. Just try not to kill him, our poor Fazio is in rather poor health.";
			link.l1 = "I will be gentle... very gentle, damn it!";
			link.l1.go = "whiskey_11";
		break;
		
		case "whiskey_11":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);//запрещаем диалог
			chrDisableReloadToLocation = true;//закрыть локацию
			sld = CharacterFromID("Facio");
			LAi_CharacterEnableDialog(sld);
		break;
		
		case "poison":
			pchar.questTemp.LSC.Dodson_poison = "true"; // разговор состоялся
			dialog.text = "Argh... "+pchar.name+", friend, something is very wrong with me..";
			link.l1 = "Steven! Did you drink the whiskey? Fuck, did you really drink it?!";
			link.l1.go = "poison_1";
		break;
		
		case "poison_1":
			dialog.text = "Yes... This is the best Irish whiskey... Giuseppe Fazio brought it for me today. He said that it was a present from Narwhal leader... a token of peace... oh, that hurts... Looks like it is the end of me.";
			link.l1 = "Damn it! The whiskey was poisoned with arsenic! Chad Kapper and Marcello Cyclops did that!";
			link.l1.go = "poison_2";
		break;
		
		case "poison_2":
			dialog.text = "Argh... boatswain has finally got me... fuck!";
			if (CheckCharacterItem(pchar, "ultimate_potion"))
			{
				link.l1 = "You are not going to die! Hear me? You won't die! Quickly, take this flask. This is the most powerful healing potion in the world, it cures everything. Drink it... now!";
				link.l1.go = "poison_3";
			}
			else
			{
				link.l1 = "Steven!";
				link.l1.go = "dodson_poison";
			}
		break;
		
		case "dodson_poison": // Акула умирает
			DialogExit();
			LAi_SetImmortal(npchar, false);
			LAi_KillCharacter(npchar);
			SetFunctionTimerCondition("LSC_SetDexterAdmiral", 0, 0, 1, false); // через день Декстера в адмиралы
			if (CheckAttribute(pchar, "questTemp.LSC.CapperDie_Aeva"))
			{
				AddQuestRecord("SharkHunt", "41");
				sld = CharacterFromID("Facio");
				sld.dialog.currentnode = "whiskey";
				sld.greeting = "facio_2";
				sld.quest.poisonnode = 1;
			}
			else AddQuestRecord("SharkHunt", "42");
			pchar.questTemp.Saga.DodsonDie = "true"; // атрибут Саге что Акула погиб
		break;
		
		case "poison_3":
			RemoveItems(pchar, "ultimate_potion", 1);
			Log_Info("Comanche potion was used");
			Log_Info("Poison was cured!");
			PlaySound("interface\notebook.wav");
			dialog.text = "Oh... "+pchar.name+", it really helped. Still feeling sick a bit, but the pain is almost gone...";
			link.l1 = "This potion neutralizes even the most lethal poisons. Drink it all! Yes...";
			link.l1.go = "poison_4";
		break;
		
		case "poison_4":
			LAi_SetStayType(npchar);
			dialog.text = "A miracle... I am fine now. Thank you, friend, I will never forget it...";
			if (CheckAttribute(pchar, "questTemp.LSC.CapperDie_Aeva"))
			{
				link.l1 = "You'd better rest now. You look like a dead man. That bastard Kapper won't be able to threat us anymore - I have dealt with him and with a few Narwhals, too. Only Marcello Cyclops is left. You said that Fazio brought you the whiskey, right?";
				link.l1.go = "poison_5";
			}
			else
			{
				link.l1 = "You'd better rest now. You look like a dead man. You said that Fazio had brought you the whiskey, right?";
				link.l1.go = "poison_7";
			}
		break;
		
		case "poison_5":
			dialog.text = "Yes. I really had to have paid attention to his pale face and shaking hands...";
			link.l1 = "It seems that he was forced to do that. Fine, I am going to visit that fat pig and get the information from him. I am sure that he knows what I need. Get well!";
			link.l1.go = "poison_6";
		break;
		
		case "poison_6":
			DialogExit();
			sld = CharacterFromID("Facio");
			sld.dialog.currentnode = "whiskey";
			sld.greeting = "facio_2";
			sld.quest.poisonnode = 1;
			LAi_CharacterDisableDialog(npchar);//запрещаем диалог
			AddQuestRecord("SharkHunt", "40");
		break;
		
		case "poison_7":
			dialog.text = "Yes. I really had to have paid attention to his pale face and shaking hands...";
			link.l1 = "It seems that he was forced to do that. Fine, I will get that fat pig eventually, but now I have to deal with Kapper and Cyclops. I know where they are hiding. Get well!";
			link.l1.go = "poison_8";
		break;
		
		case "poison_8":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);//запрещаем диалог
			AddQuestRecord("SharkHunt", "43");
		break;
		
		case "clear":
			dialog.text = "What do you say, "+pchar.name+"? I already know that you have dealt with Kapper on 'Eva'. And you haven't even cleaned up there, ha-ha! To be honest, I am admired! To kill Chad and his men, isn't that something! Yes, Jan was right to praise you.";
			link.l1 = "Not only have I dealt with Kapper, but I also prevented an attempt on your life. You were going to be poisoned, Steven, but I have stopped the bastards from doing that.";
			link.l1.go = "clear_1";
		break;
		
		case "clear_1":
			dialog.text = "To poison me? But how?";
			link.l1 = "Chad bought a barrel of Irish Bushmills whiskey from Axel...";
			link.l1.go = "clear_2";
		break;
		
		case "clear_2":
			dialog.text = "Bushmills? This is my favorite one! I haven't drunk it for ages!";
			link.l1 = "Yes-yes. And Kapper knows that, too. He also asked his pal, Marcello Cyclops, to buy some arsenic from Sancho Carpentero.  Then he and his pals took Fazio and went down the cargo hold of 'Eva'. He was going to poison the whiskey and force Fazio to bring it to you as a gift from Narwhals.";
			link.l1.go = "clear_3";
		break;
		
		case "clear_3":
			dialog.text = "Ha! Of course, I would have drink a pint of the whiskey immediately...";
			if (CheckCharacterItem(pchar, "cask_whisky"))
			{
				link.l1 = "Chad was counting on that. But he failed - he didn't even have time to put an arsenic in it. Yes, and I took the barrel with me. You can have it as a gift.";
				link.l1.go = "clear_4";
			}
			else
			{
				link.l1 = "Chad was counting on that. But he failed - he didn't even have time to put an arsenic in it.";
				link.l1.go = "clear_7";
			}
		break;
	
		case "clear_4":
			RemoveItems(pchar, "cask_whisky", 1);
			PlaySound("interface\notebook.wav");
			dialog.text = "Show me... "+pchar.name+", this is a real Bushmills! The best Irish whiskey! Argh, I've been a dreaming of it for years! You, you.. Damn it! You have eliminated Chad and you found such lovely whiskey!\nI will give you one of my best talismans. This is Thor's Hammer, it's everlasting. Your cannoneer is going to love it!";
			link.l1 = "Thanks! I am very glad, too.";
			link.l1.go = "clear_5";
		break;
		
		case "clear_5":
			GiveItem2Character(pchar, "talisman3"); 
			PlaySound("interface\notebook.wav");
			Log_Info("You have received a 'Thor's hammer' amulet");
			dialog.text = "I am looking forward to drink a pint of this magnificent whiskey... "+pchar.name+", we will have a party tonight! And you come and see me tomorrow. In the meantime, I will think about your words and Chad's actions...";
			link.l1 = "Fine, Steven, I won't bother you from... relaxing, ha-ha!";
			link.l1.go = "clear_6";
			AddQuestRecord("SharkHunt", "53");
		break;
		
		case "clear_6":
			DialogExit();
			NextDiag.CurrentNode = "Total_wait";
			DeleteAttribute(pchar, "questTemp.LSC.Whiskey_clear");
			if (CheckAttribute(pchar, "questTemp.LSC.CyclopDie"))
			{
				SetFunctionTimerCondition("LSC_WhiskeyStoryFinal_1", 0, 0, 1, false); // адмирал зовет
				DeleteAttribute(pchar, "questTemp.LSC.CyclopDie");
			}
		break;
		
		case "clear_7":
			dialog.text = "You have told me something very important. I will think about your words and Chad's actions... and then I will call you.";
			link.l1 = "Fine, Steven. I will be waiting!";
			link.l1.go = "clear_6";
			AddQuestRecord("SharkHunt", "54");
		break;
		
		case "whyskey_final":
			dialog.text = "Ha, there you are, "+pchar.name+". Now everybody is here and we can start. I have summoned you and Layton to discuss the situation and to decide what to do with Narwhals.";
			link.l1 = "What do you mean - what to do with Narwhals?";
			link.l1.go = "whyskey_final_1";
		break;
		
		case "whyskey_final_1":
			dialog.text = "An attempt on my life was organized by Chad who had a direct support from Narwhals. I recognize it as an open act of aggression. Considering the fact, that we have a short-term alliance with Rivados, I offer the following\nWe form an alliance with Rivados, prepare an operation and wipe out Narwhal clan once and for all. I had enough of their bandit attitude. You, "+pchar.name+", are going to play a role of diplomat once again\nTalk to Black Eddie and Chimiset, convince them to join us in battle against our mutual enemy. I think that they will listen to you, they believe you to be their ally\nDexter will develop a plan of attack, he knows everything about the Island's geography. Layton, do you have any thoughts already?";
			link.l1 = "";
			link.l1.go = "whyskey_final_2";
		break;
		
		case "whyskey_final_2": // перекидываем ноду Декстеру
			DialogExit();
			sld = characterFromId("Dexter");
			sld.greeting = "";
			LAi_SetActorType(sld);
			LAi_ActorSetSitMode(sld);
			LAi_CharacterEnableDialog(sld);
			LAi_ActorDialogNow(sld, pchar, "", -1);
		break;
		
		case "whyskey_final_3":
			dialog.text = "A wise idea. Forced to retreat to the San Gabriel, Narwhals, perhaps, won't yield to our troops too soon - but they will die quickly without any provision supply or they will be forced to launch a desperate attack. What do you say, "+pchar.name+"?";
			link.l1 = "What do I say... I say that declaring a war against Narwhals is a politically wrong step.";
			link.l1.go = "whyskey_final_4";
		break;
		
		case "whyskey_final_4":
			dialog.text = "And you say that after you have killed all Chad's men? Don't forget that all of them were Narwhals!";
			link.l1 = "Not all of them. One of the first of those bastards, Marcello Cyclops, wasn't a Narwhal. Actually, he was loyal to Rivados and, perhaps, he was planning to join them. He is a mulatto, after all. I think that Narwhals are not responsible for an attempt on your life - only a few bastards, who were recruited by Kapper.";
			link.l1.go = "whyskey_final_5";
		break;
		
		case "whyskey_final_5":
			dialog.text = "And what do you suggest? Ignore all this?";
			link.l1 = "I suggest keeping me to my role of being a diplomat - but this time I will negotiate with the leader of Narwhals, Donald. Besides, let me tell you my point of view concerning the possible outcome of attacking Narwhals.";
			link.l1.go = "whyskey_final_6";
		break;
		
		case "whyskey_final_6":
			dialog.text = "Go on.";
			link.l1 = "As far as I see, the peace on the Island is possible only because of rivalry between two clans who are almost equal in their strengths. Your fighters are the third power, and they can help either of them to achieve victory. But both Rivados and Narwhals are strong and a victory will cost the winner too much in any case.";
			link.l1.go = "whyskey_final_7";
		break;
		
		case "whyskey_final_7":
			dialog.text = "";
			link.l1 = "The price for the destruction of the Narwhals will be many lives of your and Rivados men. Besides, Layton said that the siege of San Gabriel will take a long time, and also we may face possible aggression from Rivados in case we loose to many men...";
			link.l1.go = "whyskey_final_8";
		break;
		
		case "whyskey_final_8":
			dialog.text = "";
			link.l1 = "Don't forget that both clans are eager to dominate on the Island and not long ago they were your enemies. So, in my opinion, the slaughter would be a real plague for the common inhabitants.";
			link.l1.go = "whyskey_final_9";
		break;
		
		case "whyskey_final_9":
			dialog.text = "Hm. Your words sound wise, but you haven't persuaded me yet.";
			link.l1 = "I also need to leave the Island somehow, so I have to reach the statue of Kukulcan at the bottom of the sea. Rivados are unable to help me - perhaps, Narwhals are? Fighting them will not help me either.";
			link.l1.go = "whyskey_final_10";
		break;
		
		case "whyskey_final_10":
			if (pchar.questTemp.LSC.Mary != "die") sTemp = "Ha! And I guess that there is one more reason why you don't want to make Narwhals our enemies. That red-haired girl of Ceres Smithy, right, friend? Am I right? Don't worry about her, "+pchar.name+", since you care about her this much - we will take her in the safe place before fighting starts.\n";
			else sTemp = "";
			dialog.text = ""+sTemp+" But I agree if you are so determined. Go and see Donald Greenspen, the head of Narwhals. His residence is in the rear of Esmeralda. Let's see what that scoundrel will tell us.";
			link.l1 = "Good. I am on my way.";
			link.l1.go = "whyskey_final_11";
		break;
		
		case "whyskey_final_11":
			DialogExit();
			sld = characterFromId("Grinspy");
			sld.dialog.currentnode = "negotiations"; // ноду Гринспи
			sld = characterFromId("Dexter");
			LAi_SetHuberType(sld);
			LAi_SetHuberType(npchar);
			NextDiag.CurrentNode = "negotiations_wait";
			pchar.questTemp.LSC.Donald_enter = "true";
			AddQuestRecord("SharkHunt", "55");
		break;
		
		case "negotiations_wait":
			dialog.text = "Go to Donald, pal, and make him lick your boots, ha-ha! I will be waiting for you.";
			link.l1 = "I am on my way.";
			link.l1.go = "exit";
			NextDiag.TempNode = "negotiations_wait";
		break;
		
		case "peace":
			dialog.text = "So what, have you spoken to Donald? I see that you have...";
			link.l1 = "Yes. He didn't order his men to harm you. All Narwhals, who had participated in the attempt, were recruited by Chad Kapper. He is very upset and he assures us that Narwhals have no bad intentions towards you. He is ready to bring you his personal apologies for this attempt on your life and for suspecting you of Alan's murder.";
			link.l1.go = "peace_1";
		break;
		
		case "peace_1":
			dialog.text = "Is he ready to come here and say all these things?";
			link.l1 = "He swore on the Bible.";
			link.l1.go = "peace_2";
		break;
		
		case "peace_2":
			dialog.text = "Heh, perhaps, that will do. It seems that the only one bastard to be blamed is my ex boatswain.";
			link.l1 = "I am completely sure of that, Steven. We don't need this war. Nobody needs it.";
			link.l1.go = "peace_3";
		break;
		
		case "peace_3":
			dialog.text = "Fine! Deal. I am ready to accept Donald with his apologies, but he'd better hurry up. Go and tell him that.";
			link.l1 = "At once, Steven.";
			link.l1.go = "peace_4";
		break;
		
		case "peace_4":
			if (pchar.questTemp.LSC.Mary == "alive") sTemp = "Take your Mary there and live your lives together, there is plenty of free space.";
			else sTemp = "";
			dialog.text = "Wait! "+pchar.name+", I am very glad that you've shown up here, on the Island. Jan holds you on a very high esteem, but you have surpassed all expectations. If you were in my crew... actually, I offer you Kapper's position, while you are here. You will command my garrison on 'Tartarus'. "+sTemp+".";
			if (pchar.questTemp.LSC.Mary == "alive") link.l1 = "No, Steven, thanks a lot, but I am not going to stay here for a long time. Find someone else for it. And concerning Mary - we are doing fine on 'Ceres Smithy'.";
			else link.l1 = "No, Steven, thanks a lot, but I am not going to stay here for a long time. Find someone else for it.";
			link.l1.go = "peace_5";
		break;
		
		case "peace_5":
			TakeNItems(pchar, "gold_dublon", 500);
			Log_Info("You have received 500 doubloons");
			PlaySound("interface\important_item.wav");
			dialog.text = "Whatever, friend. So be it. Please accept this present from me. I think that you will find these five hundred doubloons useful.";
			link.l1 = "Thanks!";
			link.l1.go = "LSC_navy";
			AddQuestRecord("SharkHunt", "57");
			pchar.questTemp.Saga.SharkHunt = "find"; //флаг - покушение предотвращено
			sld = characterFromId("Grinspy");
			sld.dialog.currentnode = "negotiations_17"; // ноду Дональду Гринспи
			AddSimpleRumourCityTip("They say that admiral respects you, mister...", "LostShipsCity", 15, 2, "LSC", "");
			AddSimpleRumourCityTip("They say that you are the admiral's loyal friend. Is that true?", "LostShipsCity", 15, 2, "LSC", "");
		break;
		
		case "LSC_navy":
			dialog.text = "Let's talk about our business... Take these sailing directions. Use them to return here on ship and in one piece\nWithout it you will either fail to find a passage here because of reefs and storms around Island, so your ship will probably join her sisters here. Remember that you must use relatively small vessel in order to pass the reefs. Lugger, schooner, brigantine, brig... Fourth class, not bigger\nYour goal is to leave this place with these sailing directions in a pocket and then to return back for me on a ship. Once I am back, I will join you and Swanson in your game. I have no idea how you can leave the island, though. Only you can help yourself in this matter, and, perhaps, that Kukulcan of yours...";
			link.l1 = "Funny, but I am actually counting on its help. Thanks for the sailing instructions, Steven. I will yet find the way out of this island.";
			link.l1.go = "LSC_navy_1";
		break;
		
		case "LSC_navy_1":
			GiveItem2Character(pchar, "LSC_navigation_map");
			dialog.text = "I wish you luck, then. Hurry up if you can, my storehouses are running low quite fast, and soon there will be no provision at all. You know what hungry and armed men are capable of, don't you?";
			link.l1 = "I do. Now I have to go. See you!";
			link.l1.go = "exit";
			NextDiag.TempNode = "Dodson_wait";
			AddQuestRecord("LSC", "5");
			// убираем квестовые предметы
			sld = ItemsFromID("key_capper");
			sld.price = 10;
			if (CheckCharacterItem(pchar, "letter_chad")) RemoveItems(pchar, "letter_chad", 1);
		break;
		
		case "Dodson_wait":
			dialog.text = "Have you found the way out from the island, "+pchar.name+"?";
			link.l1 = "Not yet, Steven. I am still on it.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Dodson_wait";
		break;
		
		// --> информационный блок
		case "Total_wait":
			dialog.text = "Well, what do you have, "+pchar.name+"? Got any interesting news?";
			
			if (!CheckAttribute(npchar, "quest.items") && CheckAttribute(npchar, "quest.takeitems"))
			{
				link.l1 = "Steven, I'd like to ask you to give me back my confiscated belongings.";
				link.l1.go = "Items";
			}
			if (!CheckAttribute(npchar, "quest.story"))
			{
				link.l2 = "Steven, tell me more about this island.";
				link.l2.go = "Story_island";
			}
			if (!CheckAttribute(npchar, "quest.natan"))
			{
				link.l3 = "Are you sure that Hawk is not on the island? He came through the portal, so he must be here.";
				link.l3.go = "Natan";
			}
			if (!CheckAttribute(npchar, "quest.whiteboy"))
			{
				link.l4 = "Do you know a man nicknamed White Boy?";
				link.l4.go = "Whiteboy";
			}
			if (!CheckAttribute(npchar, "quest.ships"))
			{
				link.l5 = "What territories here belong to Narwhals and Rivados?";
				link.l5.go = "ships";
			}
			if (!CheckAttribute(npchar, "quest.parol"))
			{
				link.l6 = "How can I learn the passwords to get on board the clan ships?";
				link.l6.go = "parol";
			}
			if (!CheckAttribute(npchar, "quest.map"))
			{
				link.l7 = "Listen, is there any map of the Island?";
				link.l7.go = "map";
			}
			if (!CheckAttribute(npchar, "quest.blade"))
			{
				link.l8 = "You have got such an interesting broadsword. I have never seen anything like it before...";
				link.l8.go = "blade";
			}
			link.l9 = "No questions yet. But I may have some soon...";
			link.l9.go = "exit";
			NextDiag.TempNode = "Total_wait";
		break;
		
		case "Items":
			dialog.text = "Ah, yes, sure! I have completely forgotten about it... Your things are upstairs in the chest. You can take them. Layton won't stop you.";
			link.l1 = "Thanks!";
			link.l1.go = "exit";
			npchar.quest.items = "true";
			NextDiag.TempNode = "Total_wait";
			ref location = &Locations[FindLocation(pchar.location)];
			DeleteAttribute(location, "private1.key");
			for (i=1; i<=10; i++) // можно лезть в сундук
			{
				sld = characterFromId("SharkSoldInside_"+i);
				DeleteAttribute(sld, "watchBoxes");
			}
		break;
		
		case "Story_island":
			dialog.text = "This Island must be very old. I've seen old caravels at the outer ring, they are more than a hundred years old. Its existence is possible because of a large shallow waters and strong current which brings ship frames here. People has been living here for a long time. There are those who were born here and never left.\nClans were formed right after de Betancourt's expedition ended up here. By the way, the San Augustine and the Tartarus were part of that expedition. The Tartarus had a lot of black salves in her holds. They founded Rivados clan in honour of Pedro Rivados, their leader. He had started an uprising and tried to capture Tartarus, but they failed. The man was sentenced to a slow death\nSlaves got their freedom here and immediately opposed themselves to the rest of locals. Their request for dominance and African traditions made most of the Christians to unite, forming a Narwhal clan\nNarwhal clan had a lot of mercenaries, soldiers, officers and adventurers within it's ranks, they were gathering supplies and building a small, professional army ready to fight Rivados with their advantage in numbers. Since then Narwhals has become very selective in accepting new recruits and Rivados has limited their ambitions. You can see the results now.";
			link.l1 = "Were there any connections between the Island and the outer world?";
			link.l1.go = "Story_island_1";
		break;
		
		case "Story_island_1":
			dialog.text = "There have been no connections for the last ten years. The locals had been trading with Cuba at one time, exchanging gold and valuable goods for food. But they don't do it anymore.";
			link.l1 = "Hm. So it seems that Swanson and Black Pastor were both right... And why didn't people leave the Island, while they still had the opportunity?";
			link.l1.go = "Story_island_2";
		break;
		
		case "Story_island_2":
			dialog.text = "Some people did, but the majority decided to stay. A lot of them have found home here, many others were born here. They don't want to return. This place seems to be much better for them... Some folks are too scared to travel through the zone of storms on old boats. As for Rivados - they have no choice but to stay here.";
			link.l1 = "And why did you come here? You abandoned your excellent frigate, picking a brig instead...";
			link.l1.go = "Story_island_3";
		break;
		
		case "Story_island_3":
			dialog.text = "I was blamed in a murder of Blaze Sharp. I have no clue why. Obviously, someone is playing dirty. Number of my enemies started to grow rapidly, so I had to leave Isla Tesoro and wait here. I have been knowing about this place for a very long time. I have left my frigate, because she was too big to bypass local reefs\nI was attacked by Narwhals and Rivados as soon as I got here. They didn't appreciate my arrival. They came close to my ship at night on longboats and set her on fire. We have crushed their tubs with our cannons and muskets. But the fire did it's work - my brig was burnt down\nWe got mad as hell, invaded the Island, stormed the San Augustine and showed them how corsairs fight. They could not bear our pressure and soon shown their backs like cowards. We had captured San Augustine, turned out that these morons used her as provision warehouse. Now they have to buy it from me for a price I name\nWe also captured local leaders: a head of Narwhals Alan Milrow and a spiritual leader of Rivados Chimiset. Layton had spent next few days to scout the area and we attacked Tartarus - a weak spot in their defences\nNow we hold two of these ships and clans have to get used to our presence. Now days, we have got some sort of peace here. As for the other locals, they seem to like the idea of third force.";
			link.l1 = "Now I see. Thanks for the story!";
			link.l1.go = "exit";
			npchar.quest.story = "true";
			NextDiag.TempNode = "Total_wait";
		break;
		
		case "Natan":
			dialog.text = "I can't say for sure, but I haven't seen him here, anyway. Not at the streets, neither in the tavern nor on clan ships. You are the first man who told me that Hawk should be somewhere around. But as I have already said - I doubt it.";
			link.l1 = "I see...";
			link.l1.go = "exit";
			npchar.quest.natan = "true";
			NextDiag.TempNode = "Total_wait";
		break;
		
		case "Whiteboy":
			dialog.text = "White boy? Hm... No, I haven't heard about him before. But it doesn't mean that he is not here. I don't have to know all the local scum, do you agree?";
			link.l1 = "I do. Fine, I'd ask someone else.";
			link.l1.go = "exit";
			npchar.quest.whiteboy = "true";
			NextDiag.TempNode = "Total_wait";
		break;
		
		case "ships":
			dialog.text = "The Island is divided by Narwhals, Rivados and my men. There is also a neutral area. I control San Augustine and Tartarus\nRivados hold Protector which is their residence, Fury - barracks, Velasco - warehouse. Strangers are forbidden to pass, you must say a special password in order to get there\nNarwhals has a lot of ships in their possession. Esmeralda is a residence of their leader and a store. So called 'Science centre San Gabriel' and a Phoenix platform. Last but not least, Ceres Smithy - their workshop. Every ship except of Esmeralda is a restricted area, you must say a password before they let you in\nThe rest of ships are considered to be neutral, local citizens live inside them. Sancho's tavern is located in caravel Fleron and brother Julian is a head of local church in galleon Gloria.";
			link.l1 = "Thanks for the information!";
			link.l1.go = "exit";
			npchar.quest.ships = "true";
			NextDiag.TempNode = "Total_wait";
			AddQuestRecord("LSC", "2");
		break;
		
		case "parol":
			dialog.text = "Actually, they give them to people they take interest in themselves. Alas, you are not one of them. But it is hardly an issue. Go to an old frigate named Carolinea. That's where a fat sly dog Giuseppe Fazio live. He is some sort of diplomat here. I don't know what did he do before he got here, but the man has skill\nHe does business with everyone. Clans use him as a mediator. Greedy. Ready to eat himself for a single doubloon, but he never shows it. Ask him for a current password, though it will cost you.";
			link.l1 = "Thanks! I will remember that.";
			link.l1.go = "exit";
			npchar.quest.parol = "true";
			NextDiag.TempNode = "Total_wait";
			AddQuestRecord("LSC", "3");
		break;
		
		case "map":
			dialog.text = "Dexter owns one. He is my second in command. He had made a detailed map right after our arrival. Go upstairs and talk to him in case you need it.";
			link.l1 = "Got it. Thanks!";
			link.l1.go = "exit";
			npchar.quest.map = "true";
			NextDiag.TempNode = "Total_wait";
			sld = characterFromId("Dexter");
			sld.quest.map = "true";
		break;
		
		case "blade":
			dialog.text = "Ha! A fine broadsword. A unique blade of some sort.. A trophy from Alan Milrow, head of Narwhal clan. That is how I named it. Jurgen, a Narwhal gunsmith, made it from some amazing metal they found at the bottom of the sea\nIt doesn't rust, never grow blunt and cut everything and everyone at once. I am very pleased with this weapon and I am not going to leave it behind.";
			link.l1 = "I am curious, if Jurgen is able to make another broadsword like this? For good money, of course...";
			link.l1.go = "blade_1";
		break;
		
		case "blade_1":
			dialog.text = "Well, he can make another one for sure. But he won't. Jurgen is Narwhal, he is loyal to his clan and he will never make anything for outsiders. Besides, you will need very special iron to make the second sword. This iron can be found only at the bottom - and how can anyone get there? So forget about it.";
			link.l1 = "I see. Pity.";
			link.l1.go = "exit";
			npchar.quest.blade = "true";
			NextDiag.TempNode = "Total_wait";
			if (CheckAttribute(pchar, "questTemp.LSC.Mary") && pchar.questTemp.LSC.Mary == "alive")
			{
				sld = characterFromId("Schmidt");
				sld.quest.narval_blade = "begin"; // возможность сделать 'Нарвал' для Мэри
			}
		break;
		// <-- информационный блок
		
		case "return":
			chrDisableReloadToLocation = true;//закрыть локацию
			dialog.text = "Ha, I saw your sails on the horizon, "+pchar.name+". Glad to see you, friend! How was the trip?";
			link.l1 = "It was fine.";
			link.l1.go = "return_1";
		break;
		
		case "return_1":
			dialog.text = "Good. Well, I am ready to get on your ship and sail to Jan Swanson. Layton will stay here as admiral, he has already taken the chair, ha-ha! It looks like he is not going to leave the Island, he likes this place.";
			link.l1 = "You said once that he is doing really well.";
			link.l1.go = "return_2";
		break;
		
		case "return_2":
			dialog.text = "Yes, he certainly is. Well, I am ready. Let's go?";
			link.l1 = "Get on my ship, Steven. We will set sail as soon as I finish my business here.";
			link.l1.go = "return_3";
		break;
		
		case "return_3":
			dialog.text = "Deal! Eh, it's been too long since I was feeling the deck of a decent ship under my feet!";
			link.l1 = "...";
			link.l1.go = "return_4";
		break;
		
		case "return_4":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "LSC_SetDodsonPassenger", -1);
		break;
		
		case "return_5":
			dialog.text = "Here we are, friend. Well, I will go and see Swanson. You should also see him and discuss our future plans. Ha-ha! Hot days await us, eh?";
			link.l1 = "No doubt. See you, Steven!";
			link.l1.go = "return_6";
		break;
		
		case "return_6":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "houseS1", "none", "", "", "OpenTheDoors", -1);
			sld = ItemsFromID("LSC_navigation_map");
			sld.price = 1000; // лоцию можно выкладывать 270912
			sld = ItemsFromID("keys_skel");
			sld.price = 3000; // отмычки можно выкладывать 270912 
			pchar.questTemp.LSC.Dios = "true"; // можно отдать лоцию Диосу
			CloseQuestHeader("LSC"); // 280313
		break;
		
		// Тени прошлого
		case "shadows":
			dialog.text = "Sure, I'll do what I can! Go on.";
			link.l1 = "Steve, take a look... A shark's tooth. Don't tell me that it's unfamiliar to you!";
			link.l1.go = "shadows_1";
		break;
		
		case "shadows_1":
			RemoveItems(pchar, "shark_teeth", 1);
			dialog.text = "Ha! You are smart! Yes, it is my tooth. Well, it's the tooth of a shark which I killed to impress one beauty. They call me Shark since then. Only a few were able to do so underwater with a simple saber, but I was young and foolish, and Beatrice Sharp was the most beautiful girl in the Caribbean... How did you get it?";
			link.l1 = "The former executioner of St. John's gave it to me. A man was butchered with it. His name was... Joshua Leadbeater.";
			link.l1.go = "shadows_2";
		break;
		
		case "shadows_2":
			dialog.text = "Yes, I did it. I cut his throat with this tooth. I was horrified by the death of Beatrice and I believed Leadbeater to be the only responsible who left alive. I read papers that I found on him later. Well, he had every right for the revenge\nBlaze's sister was just at the wrong place in the wrong time. Mask is not to be blamed for her death, he didn't want it, only Butcher was his target. I regret murdering him. Truth is, that bitch Jessica set the whole thing up.";
			link.l1 = "Have you saved those papers?";
			link.l1.go = "shadows_3";
		break;
		
		case "shadows_3":
			dialog.text = "Why should I? Of course, I haven't. I didn't need them. But I can tell you why Mask had been chasing Butcher, if you have time.";
			link.l1 = "I have. Know that it is not some curiosity, I am really interested. I am even ready to write your story down.";
			link.l1.go = "shadows_4";
		break;
		
		case "shadows_4":
			dialog.text = "I know, you never waste your time. Listen then. Joshua Leadbeater was an ordinary British Navy captain and he was commanding frigate 'Neptune', which has become a legend later...";
			link.l1 = "...";
			link.l1.go = "shadows_5";
		break;
		
		case "shadows_5":
			DialogExit();
			SetLaunchFrameFormParam("One hour later...", "Saga_FinalLedbitterStory", 0, 4);
			LaunchFrameForm();
			WaitDate("", 0, 0, 0, 1, 10); //крутим время
			RecalculateJumpTable();
		break;
		
		case "shadows_6":
			AddQuestRecordInfo("Mask", "1");
			dialog.text = "... However Leadbeater survived and he was saved by a passing ship. His wounds made his face ugly, and he had been wearing a mask since then. Finding and punishing the culprit of all his missfortunes had become his life's meaning.";
			link.l1 = "I see... I have it written down. I think I should read it to see what I got. It is a very sad story. Have you seen that Jessica?";
			link.l1.go = "shadows_7";
		break;
		
		case "shadows_7":
			dialog.text = "Sure! She accompanied Butcher in all his voyages until he dumped her for Beatrice. Jess couldn't forgive him that. They called her the Butcher's talisman, because he always had luck while she was there with him\nBelieve it or not, but as soon as he got rid of her on Barbados, his business went bad, booty got poor and the 'Neptune' became an often guest at the shipyard of Isla Tesoro. Though it can be explained by the fact that Butcher had been spending most of his time with Beatrice in the cabin rather then at the quarterdeck\nBeatrice was not like Jessica, she wasn't addicted to adventures and war, although Nicolas taught her fencing and seamanship. Yes, she was fond of sea romance but she didn't have enough hardness of character. Butcher's 'Neptune' wasn't the right place for her. In the end, she killed her.";
			link.l1 = "And what about Jessica?";
			link.l1.go = "shadows_8";
		break;
		
		case "shadows_8":
			dialog.text = "Oh, she was something. Every sailor of the 'Neptune' obeyed her orders and not just because she was a captain's girlfriend. Jess had mastered fencing and seamanship, Butcher's efforts were not wasted. She was tough and reckless, and also was gifted with a good look\nA lot of men wanted to have sex with her, but she wanted Butcher only, bothering her was really risky - many tested the results on their own backs literally, and for the most persistent her fencing lessons turned to be the last in their lives\nJess owned a very special sword, the only of it's kind in the Caribbean, I have no clue where did she get it. Flame-bladed sword. No one can grab it's blade and even the slightest touch leaves a terrible wound\nJess was an adventurer not by birth, but by vocation. By the way, if you need to learn more about her, you can talk to an acquaintance of yours. He can tell you about her much more than I can.";
			link.l1 = "Really? And who is that man?";
			link.l1.go = "shadows_9";
		break;
		
		case "shadows_9":
			dialog.text = "Jan Swanson. Forest Devil will never admit it, but he had plans about Jessica. That was the time when he had already taken Western Main for himself and his fame was something to envy for, so the tigress was as good as him\nAfter Butcher got rid of Jess, Jan started to visit Barbados suspiciously often giving a shake to English garrison. As you know, Jessica was a daughter of Bridgetown's planter\nAll in all, his plans were well known in private circles, yet no one dared to speak one's mind about it, Jan may sit on his backsides in Blueweld now days, but back then any wrong word in his address could result badly\nIn the end, it didn't work out for them. Jess couldn't live with the way Butcher treated her and she had her revenge a year later with a help of the Mask. This vengeance ended terrible for everyone: for Butcher, for Beatrice, for the Mask and for herself. They all died.";
			link.l1 = "Not all of them. Butcher is still alive.";
			link.l1.go = "shadows_10";
		break;
		
		case "shadows_10":
			dialog.text = "What? Have I misheard you? He is alive?!";
			link.l1 = "Yes. Captain Butcher wasn't executed. Well, he should have been, but he survived thanks to Jacob Jackman and Henry the Hangeman, who had intimidated the executioner. The execution was a fake. I have got evidence.";
			link.l1.go = "shadows_11";
		break;
		
		case "shadows_11":
			dialog.text = "Impossible! And where is he now?";
			link.l1 = "He is known as Lawrence Beltrope and he lives in Port Royal. He is still dangerous though. Jackman, who caused that much trouble among the Brethren of the Coast, had been acting under his command.";
			link.l1.go = "shadows_12";
		break;
		
		case "shadows_12":
			dialog.text = "Damn it! The quartermaster had found his captain after so long! Beltrope, you say... wait! Now I see why there was a strange record of interrogation among Blaze's papers... It looks like Blaze had also found out about Butcher-Beltrope...";
			link.l1 = "What are you talking about?";
			link.l1.go = "shadows_13";
		break;
		
		case "shadows_13":
			dialog.text = "After I had taken this residence, I rummaged through old Blaze's papers. I have found an interrogation record of some Samuel Brooks. There was a lot about adventures of Thomas Beltrope and that he is known as a pirate and a close friend of Nicolas Sharp. It seems that he was Butcher's father.";
			link.l1 = "Interesting. It looks like Sharp's and Beltrope's kids continued their parents' line of work...";
			link.l1.go = "shadows_14";
		break;
		
		case "shadows_14":
			dialog.text = "It seems so... But tell me, friend, why are you so interested in late people's deeds? What is your concern?";
			link.l1 = "I need papers, which would confirm that Helen McArthur is the daughter of Beatrice Sharp and that she has all rights to this surname. I don't care that she is also Beltrope.";
			link.l1.go = "shadows_15";
		break;
		
		case "shadows_15":
			dialog.text = "There is nothing about Helen McArthur neither in Leadbeater's papers nor in Blaze's archives. It is strange that Beatrice didn't tell Blaze about the birth of his niece. It doesn't look like her.";
			link.l1 = "Listen, perhaps, there is something else in Sharp's papers? I need every detail!";
			link.l1.go = "shadows_16";
		break;
		
		case "shadows_16":
			dialog.text = "Hm, I guess. According to Blaze's notes, he had been trying to find the island where his sister died. There are papers concerning Leadbeater's punitive expedition. Nothing interesting, except for a few numbers of latitude\nThis parallel crosses Caribbean sea in it's Northern part. But there is no sign of longitude. Obviously, Blaze's searches failed, you can not even imaging how many small islands at that latitude.";
			link.l1 = "And what is it?";
			link.l1.go = "shadows_17";
		break;
		
		case "shadows_17":
			dialog.text = "Let's see... here: latitude 21 degrees 32' North. I don't know how it can help you.";
			link.l1 = "It will. Fine, Steven, thank you very much for your honest story. See you!";
			link.l1.go = "shadows_18";
		break;
		
		case "shadows_18":
			DialogExit();
			pchar.questTemp.Saga.Shadows = "jessika";
			AddQuestRecord("Shadows", "6");
			LAi_SetHuberType(npchar);
			NextDiag.CurrentNode = "First time";
			sld = characterFromId("Svenson");
			sld.quest.jessika = "true";
			// рифы доступны для посещения
			i = FindIsland("RockIsland");
			Islands[i].visible = true;
			Islands[i].reload_enable = true;
			// для любителей самостоятельно добавлять локаторы
			LAi_LocationDisableOfficersGen("Shore67", true);//офицеров не пускать
			// и сразу прерывание
			pchar.quest.Saga_Jess_Island.win_condition.l1 = "location";
			pchar.quest.Saga_Jess_Island.win_condition.l1.location = "Shore67";
			pchar.quest.Saga_Jess_Island.function = "Saga_JessikaIsland"; 
			// активируем квест хронометра Алекса
			pchar.questTemp.AlexClock = "dodson"; // 280912
		break;
		
		// суп из черепахи
		case "terrapin":
			dialog.text = "You could say that. Now, about Tortuga\nThe island was named like this because it looks almost like a turtle. Levasseur had been thickening turtle's shell for twelve years - fort La Roche. A frontal attack is suicidal, fort's heavy cannons will leave no chance. So, cooking a soup of this beauty won't be easy. Spanish have been trying for a very long time and they never succeeded.";
			link.l1 = "That is why I went to Swanson. So what is your plan? Come on, Steven!";
			link.l1.go = "terrapin_1";
		break;
		
		case "terrapin_1":
			dialog.text = "My men had done decent work on Tortuga for the last few weeks, and they obtained a lot of interesting information. So I have good news for you, pal! It seems that you don't have to deal with the cannons of La Roche, since we are not the only ones fed up with Levasseur. There are people among his friends, who want him dead, too.";
			link.l1 = "Go on...";
			link.l1.go = "terrapin_2";
		break;
		
		case "terrapin_2":
			dialog.text = "It is known that Levasseur is fond of young colonist girls. They disappear after he finishes having fun with them. The main slave supplier of Tortuga is called Robert Marten of galleon Voltigeur\nHis buddy, Levasseur's nephew Henri Thibaut picks the prettiest white girls right in the port for his patron. So, not long ago, Marten got into his hands on a very beautiful girl from English brig. Name's Molly Jones. He delivered her not to Levasseur, but to his nephew, at night to some secret grotto on Tortuga\nThe crew was told that the girl died of heart attack and her 'body' was thrown aboard. Looks like our buddies decided to leave a pretty thing to themselves. If Levasseur will find out about Molly, these two will have problems.";
			link.l1 = "And how can we trust that information? It is obvious that both of them understand that they are playing with fire...";
			link.l1.go = "terrapin_3";
		break;
		
		case "terrapin_3":
			dialog.text = "True. But every chain has a weak spot. And have found such for you. Three days ago, an ex sailor of 'Voltigeur' named Fernand Lucas drank too much and told a lot of interesting thing in Basse-Terre's tavern\nTurned out that Molly Jones had asked him to ask her brother in St John's for help. But Lucas never reached the goal, he escaped from his captain and he is sitting his ass in Guadeloupe and drowning his cowardliness in rum\nAntigua is not a safe place for French pirates. Remember that! Colonel Fox is ready to hang them on every palm of the island after his wife died by the hand of French corsair. And his fearsome marines will do everything their commander orders.";
			link.l1 = "I don't yet understand how it is connected with our business... Let's talk about our guys, Marten and Thibaut. What is the point of such a risk? Was the woman's charm that strong or did these slavers show mercy?";
			link.l1.go = "terrapin_4";
		break;
		
		case "terrapin_4":
			dialog.text = "I know that scum Marten very well. If he is taking risks, that means that there is either gold involved or fear for his skin. I don't know what our prisoner has to do with this\nMaybe Robert is expecting to get a huge ransom for her, which is unlikely, the girl was looking like a servant. Or maybe... Ha! I wonder who might be more frightful for Marten than Levasseur!";
			link.l1 = "And why do you think that miss Jones is still being hidden from the governor? Perhaps they had got what they wanted from her and delivered her to Levasseur? Yes, do you have anything specific to tell about this Thibaut?";
			link.l1.go = "terrapin_5";
		break;
		
		case "terrapin_5":
			dialog.text = "Don't know much about the man. I only know that the uncle trusts this pup enough to make him his heir. He still has a girl, otherwise why would they need all this conspiracy?\nIt's unclear where the girl is held and why Thibaut allows Marten to take lead. There is a mystery which can help us to win this game without storming Tortuga. You are French, so I guess, you would prefer it that way\nBut you should hurry, Lucas's drunk talks could be heard by agents of Marten and Levasseur, you can imagine the consequences!";
			link.l1 = "I get it. So, Thibaut is an heir of Levasseur? And he hides a slave girl from his uncle? Damn, I guess the young man is eager to see uncle dead as soon as possible!";
			link.l1.go = "terrapin_6";
		break;
		
		case "terrapin_6":
			dialog.text = "True. According to Lucas's words, this Molly is a rare piece of beauty, our brave Thibaut might fall in love with her. You know what people can do for the sake of love. Go to Basse-Terre\nFind this drunken idiot and make him speak. Plus, you should also learn anything about Molly and her brother. You might want visit Antigua first, Molly had sent Lucas there for purpose. But what's the purpose?";
			link.l1 = "I see. Let's not waste time. Thank you, Steven.";
			link.l1.go = "terrapin_7";
		break;
		
		case "terrapin_7":
			DialogExit();
			AddQuestRecord("Terrapin", "1");
			pchar.questTemp.Terrapin = "baster";
			pchar.questTemp.Terrapin.SJ_count = 0;
			// прячем Фокса
			sld = characterFromId("Fox");	
			ChangeCharacterAddressGroup(sld, "none", "", "");
			// садим в таверну Робера Мартэна
			float fMft = MOD_SKILL_ENEMY_RATE/10;
			sld = GetCharacter(NPC_GenerateCharacter("Rober", "Marten", "man", "man", 30, FRANCE, -1, true, "quest"));
			FantomMakeCoolSailor(sld, SHIP_GALEON_L, "Voltigeur", CANNON_TYPE_CANNON_LBS20, 90, 90, 90);
			FantomMakeCoolFighter(sld, 30, 80, 80, "blade_19", "pistol5", "bullet", 150);
			sld.name = "Rober";
			sld.lastname = "Marten";
			sld.dialog.FileName = "Quest\Sharlie\Terrapin.c";
			sld.dialog.currentnode = "Rober";
			sld.greeting = "pirat_common";
			TakeNItems(sld, "potion2", 1);
			TakeNItems(sld, "potion3", 2);
			SetCharacterPerk(sld, "Energaiser");
			SetCharacterPerk(sld, "BasicDefense");
			SetCharacterPerk(sld, "AdvancedDefense");
			SetCharacterPerk(sld, "CriticalHit");
			SetCharacterPerk(sld, "Tireless");
			SetCharacterPerk(sld, "HardHitter");
			SetCharacterPerk(sld, "Sliding");
			SetCharacterPerk(sld, "BladeDancer");
			SetCharacterPerk(sld, "SwordplayProfessional");
			SetCharacterPerk(sld, "Gunman");
			SetCharacterPerk(sld, "GunProfessional");
			SetCharacterPerk(sld, "MusketsShoot");
			SetCharacterPerk(sld, "LongRangeGrappling");
			SetCharacterPerk(sld, "GrapplingProfessional");
			SetCharacterPerk(sld, "HullDamageUp");
			SetCharacterPerk(sld, "SailsDamageUp");
			SetCharacterPerk(sld, "CrewDamageUp");
			SetCharacterPerk(sld, "CriticalShoot");
			SetCharacterPerk(sld, "LongRangeShoot");
			SetCharacterPerk(sld, "BasicBattleState");
			SetCharacterPerk(sld, "AdvancedBattleState");
			SetCharacterPerk(sld, "ShipDefenseProfessional");
			SetCharacterPerk(sld, "ShipSpeedUp");
			SetCharacterPerk(sld, "ShipTurnRateUp");
			SetCharacterPerk(sld, "WindCatcher");
			SetCharacterPerk(sld, "SailsMan");
			SetCharacterPerk(sld, "Doctor1");
			SetCharacterPerk(sld, "Doctor2");
			sld.MultiFighter = 1.0+fMft; // мультифайтер
			LAi_SetSitType(sld);
			UpgradeShipParameter(sld, "SpeedRate");//апгрейдить скорость
			UpgradeShipParameter(sld, "TurnRate");//маневренность
			FreeSitLocator("Baster_tavern", "sit1");
			ChangeCharacterAddressGroup(sld, "Baster_tavern", "sit", "sit1");
			SetFunctionTimerCondition("Terrapin_LateBaster", 0, 0, 10, false); // таймер
		break;
		
		case "terrapin_8":
			dialog.text = "Go on!";
			link.l1 = "I have found Molly's brother in St. John's. It is Fox's batman. But there is something strange. His sister Molly is a well known ugly hag about as tall as you. She is the maid of Fox's daughter, Catherine, and she had been in England with her until recently...";
			link.l1.go = "terrapin_9";
		break;
		
		case "terrapin_9":
			dialog.text = "";
			link.l1 = "As for Catherine, she indeed is known for her beauty and she was going to visit her father on his birthday, but she was late due to the squadron's delay in London...";
			link.l1.go = "terrapin_10";
		break;
		
		case "terrapin_10":
			dialog.text = "";
			link.l1 = "Her father, who took hard the death of his wife due the French corsair's attack, strictly has forbidden her from leaving England on a solitary ship. So Molly Jones can't be Thibaut's prisoner. Then who is she?";
			link.l1.go = "terrapin_11";
		break;
		
		case "terrapin_11":
			dialog.text = "Hm... Damn if I know. Perhaps she is some other Molly Jones, not the one you've been asking about. Though... there are too many coincidences. I don't believe that it is all just an accident! I've got some unclear suspicions but... though many strange things can happen!";
			link.l1 = "What do you mean? Tell me!";
			link.l1.go = "terrapin_12";
		break;
		
		case "terrapin_12":
			dialog.text = "And what if the daughter disobeyed father's orders and set sail without an escort? Last month was quite stormy, Albatross could get damaged and became an easy pray for Marten. I suspect that Catherine didn't tell her real name, you should understand why, and she is being kept in Tortuga under Molly's name\nYou know what awaits her if her true name is compromised. This is starting to make sense!";
			link.l1 = "Damn it! I would have never thought about it! Molly... Catherine... But it is all coinciding!";
			link.l1.go = "terrapin_13";
		break;
		
		case "terrapin_13":
			dialog.text = "That is what I am talking about, pal. Not sure that we are right, but...";
			link.l1 = "But it changes everything! Perhaps we should ask the English for support? To let the bayonets of the marines clear the way for us!";
			link.l1.go = "terrapin_14";
		break;
		
		case "terrapin_14":
			dialog.text = "Calm down, "+pchar.name+"! We need more solid proofs. We can not know for sure. Real Catherine might be in London, waiting for a squadron to set sail. Brits have got problems of their own, they won't risk attacking La Roche. But if our suspicions are true and colonel Fox will find out what has happened to his daughter...\n He will set up a blockade around the island and will wait for the squadron's arrival. Then he will attack the city. Sea foxes are a fearsome force in close quarters fighting. I am sure that he will raise the English flag above ruins of Tortuga in three days. Do you really want this?";
			link.l1 = "No, it is not our way. Now I see what ransom Marten is talking about.";
			link.l1.go = "terrapin_15";
		break;
		
		case "terrapin_15":
			dialog.text = "We must act carefully. We are not even sure that Marten is aware of true Molly's true identity. Blackmailing colonel Fox would be a suicidal idea. Especially when Cromwell's squadron is arriving shortly\nIf Catherine dies, we shall loose too. Our Brotherhood is not interested to make colonel Fox more angry than usual. This man can cause a lot of troubles. If Catherine has to die after all, we must make sure she dies not by our hands and after she plays her role in our game\nBut it would be much better to deliver poor girl to her father. Her saviour will be rewarded. If not in this world, than in the other.";
			link.l1 = "For God's will... Steven, you are genius! I am going to Tortuga immediately! I will find out, who that Molly Jones is! I am damn sure that she is Catie Fox!";
			link.l1.go = "terrapin_16";
		break;
		
		case "terrapin_16":
			dialog.text = "Perhaps... Don't waste time, "+pchar.name+". And if I was right - make sure she stays alive.";
			link.l1 = "I will do what I can. See you!";
			link.l1.go = "terrapin_17";
		break;
		
		case "terrapin_17":
			DialogExit();
			AddQuestRecord("Terrapin", "7");
			pchar.questTemp.Terrapin = "tortuga1";
			pchar.questTemp.Terrapin.Room_close = "true": // не пускать в комнату таверны
		break;
		
		case "guardoftruth":
			dialog.text = "Ho-Ho! Spit it out, friend! We will solve any problem for damn sure!";
			link.l1 = "I will get straight to the point, then. Do you know Miguel Dichoso?";
			link.l1.go = "guardoftruth_1";
		break;
		
		case "guardoftruth_1":
			dialog.text = "I know him. That Spanish don sold me a great ship - a frigate. Eh, what a vessel she was, just imagine...";
			link.l1 = "Let me guess, a unique hull, sixteen knots max speed? 'Santa Quiteria'?";
			link.l1.go = "guardoftruth_2";
		break;
		
		case "guardoftruth_2":
			dialog.text = "You are right about her hull and speed, but the name was different - 'San Martin'. I paid him a huge amount of gold, it was everything I had. All my savings went straight into that rogue's pockets.";
			link.l1 = "Are you sure that her name was San Martin and not Santa Quiteria? And when did you buy it? And why are you calling him a rogue?";
			link.l1.go = "guardoftruth_3";
		break;
		
		case "guardoftruth_3":
			dialog.text = "So many questions! I will answer them all in the order: I am sure that it was San Martin. I personally had helped Alexus's workers to get rid of a plank with that papist name from the stern. I named her 'Fortune' - a much more suitable name for such princess\nI bought her not long before Blaze Sharp was murdered in winter 1654. Why did I call Miguel like that? Because that son of a bitch had managed to steal the ship from Spanish military base of Providence. We had arranged quite a show for them, right in front of San Juan's fort. I sacrificed two half-dead luggers in order to make the fight more trustworthy. we burned and flooded the ships, simulating the battle with the frigate. And as the darkness descended - we drove the San Martin to Isla Tesoro.. I got the ship and Dichoso got money. He told his high command that the frigate was sunk in a battle with pirates, San Juan's commandant verified that.";
			link.l1 = "So that is how Spanish dons fill their pockets! What a scoundrel! Tell me, had it really happened in winter 1654? Maybe in spring? And was the frigate damaged by storms?";
			link.l1.go = "guardoftruth_4";
		break;
		
		case "guardoftruth_4":
			dialog.text = "In winter... Damn it, I am not totally sure - could be in spring, too. I don't remember really. The frigate wasn't damaged, she was all new. She looked newly built. When I think of her, I just want to cry with vexation...";
			link.l1 = "Why? Yeah, and where is your beautiful frigate now?";
			link.l1.go = "guardoftruth_5";
		break;
		
		case "guardoftruth_5":
			dialog.text = "Because she is gone from me. They set me up, put my talisman on Blaze's corpse and spread the word that I was the murderer. Then I heard that Marcus Tyrex - our code keeper - is going to hand me a black mark. So I decided to escape from that mess for a while at the Island of Justice, where you had found me\nI couldn't get there on a frigate, so I pledged her to Black Pastor in exchange for a brig filled with provision, I didn't have much coin after my deal with that sly Dichoso. I was hoping to sell provision and to return to Isla Tesoro in a month or two... Well, you know the rest.";
			link.l1 = "And Black Pastor didn't wait for you, so he sold her";
			link.l1.go = "guardoftruth_6";
		break;
		
		case "guardoftruth_6":
			dialog.text = "Precisely. She was bought by one English, or to be more specific, by one Scot, William Patterson. I could try to return the girl, sure, but this highlander is a serious bird, a captain of Royal Navy, a good friend of colonel Fox. Besides, he was doing business with Jackman same way you were with Swanson\nThe Scot has a squadron... screw it, I will not see my ship again.";
			link.l1 = "I see. Don't you know where is that Dichoso now?";
			link.l1.go = "guardoftruth_7";
		break;
		
		case "guardoftruth_7":
			dialog.text = "I have no idea. I have never seen him after I bought my Fortune.";
			link.l1 = "And why didn't Miguel offer to buy it to someone else? How about Tyrex, Barbazon, Sharp? Or Patterson?";
			link.l1.go = "guardoftruth_8";
		break;
		
		case "guardoftruth_8":
			dialog.text = "I have no idea. Patterson wasn't here that time as far as I remember. Zachariah, Jaques and Marcus would have never agreed and I... I really liked the frigate!";
			link.l1 = "I understand that... I don't understand a thing. Puzzles everywhere...";
			link.l1.go = "guardoftruth_9";
		break;
		
		case "guardoftruth_9":
			dialog.text = "Delving in the past again? What island do you want to take this time? Ha-ha-ha!";
			link.l1 = "There is one island... Though I can't find a way to it yet. Fine, Steven, thanks for your information! Farewell!";
			link.l1.go = "guardoftruth_10";
		break;
		
		case "guardoftruth_10":
			dialog.text = "Good luck, "+pchar.name+"!";
			link.l1 = "...";
			link.l1.go = "guardoftruth_11";
		break;
		
		case "guardoftruth_11":
			DialogExit();
			AddQuestRecord("Guardoftruth", "60");
			pchar.questTemp.Guardoftruth.Archy = "guadeloupe";
			// маленькая развлекуха
			pchar.quest.GuardOT_cabinattack.win_condition.l1 = "EnterToSea";
			pchar.quest.GuardOT_cabinattack.function = "GuardOT_PrepareCreateBandosInCabin";
		break;
		
		case "tieyasal":
			dialog.text = "And I am glad to help you, as always. What do you want this time, "+pchar.name+"?";
			link.l1 = "It's again about your old friend Miguel Dichoso. I am aware that he was seen on Isla Tesoro again. Can't you help me to find him?";
			link.l1.go = "tieyasal_1";
		break;
		
		case "tieyasal_1":
			dialog.text = "Ho, friend, I didn't know that, actually. I haven't seen him here. I haven't seen him since I bought 'Fortune' from him. And why do you need that Spanish don?";
			link.l1 = "I need him. Miguel knows the way to an old Indian city. I am really eager to get there.";
			link.l1.go = "tieyasal_2";
		break;
		
		case "tieyasal_2":
			dialog.text = "Just as always, my friend, you are going to drag yourself into the mess. Alas, I can't help you. I advice you to walk around the settlement and ask people, perhaps someone had seen him. He is a famous man here, you know.";
			link.l1 = "Hey, Steven, can you at least tell me how he looks like?";
			link.l1.go = "tieyasal_3";
		break;
		
		case "tieyasal_3":
			dialog.text = "Well, he is twenty five - twenty eight years old, about as tall as you, dark eyes, no wig. There is a saber scar on his right cheek.";
			link.l1 = "Hm. You know, there are many people who would fit that description.";
			link.l1.go = "tieyasal_4";
		break;
		
		case "tieyasal_4":
			dialog.text = "There are no other unique details about him. He is self-confident, insolent and very dangerous. There were gossips about him...";
			link.l1 = "I see. Fine, I will ask around about him. Good luck, Steven!";
			link.l1.go = "tieyasal_5";
		break;
		
		case "tieyasal_5":
			DialogExit();
			AddQuestRecord("Tieyasal", "2");
			npchar.quest.tieyasal = "true";
		break;
		
		// Jason НСО
		case "patria":
			dialog.text = "Ho-ho! You've come to the right place! Spit it out!";
			link.l1 = "There is a fella that has no fear of pirates. He doesn't take them seriously. He needs to be taught a lesson om respect. Remember, don't kill him.";
			link.l1.go = "patria_1";
		break;
		
		case "patria_1":
			dialog.text = "Huh! It's noone else than the old man Charles! I bet you got yourself into some affair again! Let's get to the details, who's the target this time and what shall we teach him";
			link.l1 = "A guest from Europe, an inspector of the French Ministry of Finance - baron Noel Forget. He wants to establish a French Trading Company here, but me and a close friend of mine object against it. We tried to convince the Baron, that trading here would be very risky because of the Dutch, English and especially pirates after Levasseur was defeated, but he didn't listen. We need to strike fear into him, to make him feel it on his own skin.";
			link.l1.go = "patria_2";
		break;
		
		case "patria_2":
			dialog.text = "Yes-yes... An actual baron!.. Will we assault his ship?";
			link.l1 = "Here's the plan: his vessel will depart to Capsterville from Port-au-Prince soon. You have to intercept the Baron after his departing and take him as a hostage. It would be better if you didn't sink the ship and avoided killing crew. The French are our friends, after all. Will you be able handle that?";
			link.l1.go = "patria_3";
		break;
		
		case "patria_3":
			dialog.text = "Well, I can't promise anything. But I'll try. What ship is it?";
			link.l1 = "A brig called 'Favory'.";
			link.l1.go = "patria_4";
		break;
		
		case "patria_4":
			dialog.text = "A brig is no match for my frigate. We'll easily deal with them. If it surrenders, I'll let everyone live.";
			link.l1 = "Perfect. Strike fear and offer them to yield. Afterwards, send the Baron to the rat-infested hold. Try to find the filthiest place you can, but keep him there no longer than a day, or else he could get sick and die. Then accomodate him in the cabin, go to the Isla Tesoro, and lock in some secluded place. Dress some of your men as captured French merchants and make them to act like ones. For three days straight, they should tell him all about how the ruthless pirates chase them, rob them, demand ransoms, torture them... with all the details required.";
			link.l1.go = "patria_5";
		break;
		
		case "patria_5":
			dialog.text = "Ha-ha-ha! This must be the funniest job I've ever taken on since a very long time! Well then, I will find such actors, pal. Have no doubt, after their stories your baron will crap his pants! They will show him scars from cutlasses and heated ramrods... ";
			link.l1 = "Nailed it. Then you will force him to write a letter to Poincy, asking for ransom. Thirty five hundred thousand for such a big shot is not that much.";
			link.l1.go = "patria_6";
		break;
		
		case "patria_6":
			dialog.text = "Good. What will we do next?";
			link.l1 = "And then you'll bring the Baron to Turks. There you will take the ransom, and you will give me the Baron. And additionally you should mention, that all French will answer for Tortuga and Levasseur.";
			link.l1.go = "patria_7";
		break;
		
		case "patria_7":
			dialog.text = "Ha-ha-ha! That's one hell of a trick! We personally, well, you know what we did to Levasseur, and now... ha-ha-ha!.. Fine, pal. It will be done! You say that the ship will arrive soon?";
			link.l1 = "Soon. We need to be on lookout.";
			link.l1.go = "patria_8";
		break;
		
		case "patria_8":
			dialog.text = "Don't be bothered , I won't let you down. I will handle this personally. When you hear rumor that this baron was captured, come to me.";
			link.l1 = "Good. My thanks, Steven.";
			link.l1.go = "patria_9";
		break;
		
		case "patria_9":
			DialogExit();
			AddQuestRecord("Patria", "70");
			pchar.questTemp.Patria = "epizode_12_wait";
			pchar.questTemp.Patria.Condotier.Success = "true";
			LocatorReloadEnterDisable("Pirates_town", "reload3_back", true);
		break;
		
		case "patria_10":
			dialog.text = "Of course, pal. As agreed. Scary tales about evil pirates, slaughtering innocent French merchants, The sounds of a whip, moans and screams. Brazier with coal and scorched handcuffs. Just like it should be.";
			link.l1 = "Well now! Hold your horses. I need him alive.";
			link.l1.go = "patria_11";
		break;
		
		case "patria_11":
			dialog.text = "Don't worry, he will stay live. He wrote that letter with a shaky hand. Here it is.";
			link.l1 = "What is written there? Is he begging Poincy to get him out of this?";
			link.l1.go = "patria_12";
		break;
		
		case "patria_12":
			dialog.text = "Spot on, pal! He's begging!";
			link.l1 = "Throw this letter away, or better - burn it. We'll meet on Turks in a week. It must look as if we need time to collect the ransom.";
			link.l1.go = "patria_13";
		break;
		
		case "patria_13":
			dialog.text = "Got it. In a week time, Northern gulf. Don't forget to take the money: this must look pretty. Afterwards, come to me, well settle this.";
			link.l1 = "Of course, I bet even the echinus would have figured that out. See you later! ";
			link.l1.go = "patria_14";
		break;
		
		case "patria_14":
			DialogExit();
			AddQuestRecord("Patria", "73");
			pchar.questTemp.Patria = "epizode_12_terks";
			SetFunctionTimerCondition("Patria_CondotierTerks", 0, 0, 7, false);
			SetFunctionTimerCondition("Patria_CondotierTerksOver", 0, 0, 14, false);
		break;
		
		case "patria_15":
			pchar.quest.Patria_CondotierTerksOver.over = "yes"; //снять таймер
			dialog.text = "Hey, frog eater! Halt!";
			link.l1 = "I'm not moving.";
			link.l1.go = "patria_16";
		break;
		
		case "patria_16":
			dialog.text = "Here's your baron. A bit worn, but in one piece. Is it him?";
			link.l1 = "Yes.";
			link.l1.go = "patria_17";
		break;
		
		case "patria_17":
			dialog.text = "Perfect. Now, hand over the money or he is done! And don't try to trick us, we've got you in the sights!";
			if (sti(pchar.money) >= 350000)
			{
				link.l1 = "Here.";
				link.l1.go = "patria_18";
			}
			else
			{
				link.l1 = "Damn! I forot it on the ship...";
				link.l1.go = "patria_22";
			}
		break;
		
		case "patria_18":
			AddMoneyToCharacter(pchar, -350000);
			dialog.text = "Ha-ha-ha! You're a smart kid, frenchie. Take thine holiness. And tell Poincy that he should prepare the money: all French bastards will have to pay up for what you did to Levasseur and Tortuga. And your traders will pay us with their, goods and ships. Ha-ha-ha! Don't forget to bring us some more barons to the archipelago, they bring us a lot of profit! Ha-ha-ha!";
			link.l1 = "Please go to my boat, Baron.";
			link.l1.go = "patria_19";
		break;
		
		case "patria_19":
			sld = CharacterFromID("Noel");
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "reload1_back", "none", "", "", "", 10.0);
			dialog.text = "And don't even think about chasing us, captain. You know who I am. I hold more frog eater captives, and if I don't return home in time, they all be killed by my men. Got it?";
			link.l1 = "The time will come and we'll deal with you, cursed blasphemers!";
			link.l1.go = "patria_20";
		break;
		
		case "patria_20":
			dialog.text = "Ha-ha-ha-ha!";
			link.l1 = "...";
			link.l1.go = "patria_21";
		break;
		
		case "patria_21":
			DialogExit();
			LAi_SetPlayerType(pchar);
			AddQuestRecord("Patria", "74");
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "Patria_CondotierDodsonNorm", 10.0);
			sld = CharacterFromID("Terks_pirat");
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "reload1", "none", "", "", "", 8.0);
			pchar.questTemp.Patria = "epizode_12_baronalive";
			pchar.questTemp.Patria.DodsonAgain = "true";
			Island_SetReloadEnableGlobal("Bermudes", false); // закрыть остров до отвоза барона
			sld = CharacterFromID("Noel");
			AddPassenger(pchar, sld, false);//добавить пассажира
			SetCharacterRemovable(sld, false);
			pchar.quest.Patria_Condotier_toPuancie.win_condition.l1 = "location";
			pchar.quest.Patria_Condotier_toPuancie.win_condition.l1.location = "Charles_town";
			pchar.quest.Patria_Condotier_toPuancie.function = "Patria_CondotierEnCapstervil";
			// Теркс в норму
			LAi_LocationFightDisable(&Locations[FindLocation("Shore56")], false);
			LAi_LocationDisableOfficersGen("Shore56", false);
		break;
		
		case "patria_22":
			dialog.text = "Are you messing with me?";
			link.l1 = "One minute, I'll bring it...";
			link.l1.go = "patria_23";
		break;
		
		case "patria_23":
			DialogExit();
			LAi_SetPlayerType(pchar);
			sld = CharacterFromID("Terks_pirat");
			LAi_SetActorType(sld);
			LAi_ActorAnimation(sld, "Shot", "Patria_CondotierBaronDie", 1.0);
		break;
		
		case "patria_24":
			dialog.text = "";
			link.l1 = "Argh, Steven, what has your dullard done!";
			link.l1.go = "patria_25";
		break;
		
		case "patria_25":
			dialog.text = "Charles, what were you doing? Where's the money? I didn't tell my boys that this wasn't real... and so this idiot decided that you wanted to trick them...";
			link.l1 = "What a pity! Baron is dead... What will Poincy do now?";
			link.l1.go = "patria_26";
		break;
		
		case "patria_26":
			dialog.text = "Well, pal, It's your fault, I hope you understand that. Perhaps, it will be all the better for you.";
			link.l1 = "What an idiot I am! Messed everything up. Fine, I'll go to Poincy... Forgive me for being a fool, Steven, see you.";
			link.l1.go = "patria_27";
		break;
		
		case "patria_27":
			dialog.text = "You need to rest, you're losing your touch. Come to me sometime, I'll get you some rum and fine maidens.";
			link.l1 = "Thank you, I'll play you a visit when I can.";
			link.l1.go = "patria_28";
		break;
		
		case "patria_28":
			DialogExit();
			AddQuestRecord("Patria", "75");
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "Patria_CondotierDodsonNorm", 10.0);
			sld = CharacterFromID("Terks_pirat");
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "reload1", "none", "", "", "", 8.0);
			pchar.questTemp.Patria = "epizode_12_barondie";
			// Теркс в норму
			LAi_LocationFightDisable(&Locations[FindLocation("Shore56")], false);
			LAi_LocationDisableOfficersGen("Shore56", false);
		break;
		
		case "patria_29":
			dialog.text = "You're welcome, pal. For me this was the most fun I've had this year! We laughed so much, me and my lads!.. So I'd like to thank you for this. Here's your money.";
			link.l1 = "You should keep yourself a share.";
			link.l1.go = "patria_30";
		break;
		
		case "patria_30":
			AddMoneyToCharacter(pchar, 350000);
			dialog.text = "Forget it. I did this for the sake of our friendship. The Brotherhood of the Coast owes you much more, yet you didn't ask for a single dubloon.";
			link.l1 = "Still, take at least fifty thousand for the services and compensation. Thank you, Steven! I'm glad that I once met you on that strange island of the lost ships.";
			link.l1.go = "patria_31";
		break;
		
		case "patria_31":
			AddMoneyToCharacter(pchar, -50000);
			dialog.text = "And so am I. Charles, pay me a visit whenever you have some time!";
			link.l1 = "With pleasure!";
			link.l1.go = "patria_32";
		break;
		
		case "patria_32":
			DialogExit();
			DeleteAttribute(pchar, "questTemp.Patria.DodsonAgain");
		break;
		
		case "patria_33":
			dialog.text = "You're late by a week! I didn't tell my boys that this wasn't real... ! They refused to wait any longer, and decided to end your baron!";
			link.l1 = "What an idiot I am! Messed everything up! What am I going to tell Poincy?";
			link.l1.go = "patria_34";
		break;
		
		case "patria_34":
			dialog.text = "Well, pal, It's your fault, I hope you understand that. Perhaps, it will be all the better for you.";
			link.l1 = "Fine, I'll go to Poincy... Forgive me for being a fool, Steven, see you..";
			link.l1.go = "patria_35";
		break;
		
		case "patria_35":
			dialog.text = "You need to rest, you're losing your touch. Come to me sometime, I'll get you some rum and fine maidens";
			link.l1 = "Thank you, I'll play you a visit when I can.";
			link.l1.go = "patria_36";
		break;
		
		case "patria_36":
			DialogExit();
			AddQuestRecord("Patria", "75");
			pchar.questTemp.Patria = "epizode_12_barondie";
			DeleteAttribute(pchar, "questTemp.Patria.DodsonFail");
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}