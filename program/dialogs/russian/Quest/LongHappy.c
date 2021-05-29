// диалоги персонажей по квесту Долго и счастливо
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i;
	string sTemp;
	
	DeleteAttribute(&Dialog,"Links");
	
	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	switch(Dialog.CurrentNode)
	{
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "First time":
			dialog.text = "Что вам надо?";
			link.l1 = "Ничего.";
			link.l1.go = "exit";
		break;
		
		// вестовой капитан в порту
		case "cureer":
			dialog.text = "Monsieur de Maure, such a luck! I've been looking for you for mouths!";
			link.l1 = "My dear, I don't buy fake maps, dubious information and homemade rum - thank you! Or are you a bounty hunter? And how much is for my head now?";
			link.l1.go = "cureer_1";
		break;
		
		case "cureer_1":
			dialog.text = "Oh, monsieur, I... I don't trade junk and don't kill people - don't touch the sword, you will not need it! Everything is much more prosaic - I'm a captain of a courier ship. I distribute mail. And for you, I've got an important correspondence!";
			link.l1 = "A letter? Who is sender, may I ask?";
			link.l1.go = "cureer_2";
		break;
		
		case "cureer_2":
			dialog.text = "One abbot handed it to me, and asked to deliver to captain de Maure personally, from hand to hand. I already despaired of finding you and wanted to leave at at the the harbor office in Saint Pierre, but such a luck - here you are!";
			link.l1 = "Yes, here I am, I'm waiting - give me the letter.";
			link.l1.go = "cureer_3";
		break;
		
		case "cureer_3":
			dialog.text = "There is one moment... The abbot said that the delivery would be paid by the recipient. So you own nine thousand and two hundred pesos.";
			link.l1 = "For such money, it should have been brought to me in the open sea right to the cabin, along with morning coffee! You can leave the letter to yourself.";
			link.l1.go = "cureer_6";
			if (sti(pchar.money) >= 9200)
			{
				link.l2 = "And why didn't I do mail delivery?! This is more profitable than piracy! Here is your silver, my dear, give the envelope.";
				link.l2.go = "cureer_4";
			}
		break;
		
		case "cureer_4":
			AddMoneyToCharacter(pchar, -9200);
			dialog.text = "Nice to deal with you! Abbot Benoit sends you the best wishes.! Goodbye monsieur de Maure!";
			link.l1 = "";
			link.l1.go = "cureer_5";
		break;
		
		case "cureer_5":
			DialogExit();
			chrDisableReloadToLocation = false;
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "", 10.0);
			LongHappy_RecibeLetter();
		break;
		
		case "cureer_6":
			dialog.text = "As you wish. I will leave the envelope at the harbor office. But it will affect the price, I warn you. And yes - Abbot Benoit sends you the best wishes.";
			link.l1 = "The letter from Abbot Benoit? Why didn't you say it from the start! It must be important!";
			link.l1.go = "cureer_7";
		break;
		
		case "cureer_7":
			dialog.text = "So pick it up from the head of the port. Don't forget to take a loan in advance. Farewell, captain de Maure.";
			link.l1 = "I knew pirates more sincere than you. Good luck, my dear.";
			link.l1.go = "cureer_8";
		break;
		
		case "cureer_8":
			DialogExit();
			chrDisableReloadToLocation = false;
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "", 10.0);
			pchar.questTemp.LongHappy = "portman";
		break;
		
		// испанский офицер в Сантьяго
		case "spa_officer":
			dialog.text = "Holy Father, you are earlier than usual today. Please, your escort is waiting. And you, senor de Maure - father Vincento found out that you were in the city and urges you to join him for dinner.";
			link.l1 = "I'm afraid the Inquisitor will have a dinner alone. I hope this won't make his appetite worse. And Abbot Benoit will also deprive him of his society. You know who I am, so I recommend - let us pass without any conflict and say my best wishes to Father Palotti.";
			link.l1.go = "spa_officer_1";
		break;
		
		case "spa_officer_1":
			if(sti(pchar.reputation.nobility) > 80 || sti(pchar.reputation.nobility) < 20) // провести учет чести и известности
			{
				dialog.text = "Yes, I heard a lot about you, and I have clear instructions not to turn the city into a blood bath if you stubborn. You can go through. But father Vincento will be... dissatisfied. Keep this in mind.";
				link.l1 = "You acted reasonably, monsieur. I'll survive, somehow, the pain in my heart made with the dissatisfaction of the father-inquisitor. Have a nice evening!";
				link.l1.go = "spa_officer_2";
			}
			else
			{
				dialog.text = "Yes, I heard about you... a lot of interesting. However, rejecting such invitations is dangerous to health, senor. As well as kidnapping guests of father Vincento. Holde them!";
				link.l1 = "Everyone has made his choice. To arms, caballero!";
				link.l1.go = "spa_officer_3";
			}
		break;
		
		case "spa_officer_2":
			DialogExit();
			chrDisableReloadToLocation = false;
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешить драться
			for (i=1; i<=4; i++)
			{
				sld = characterFromId("LH_escort_"+i);
				LAi_SetActorType(sld);
				LAi_ActorGoToLocation(sld, "reload", "reload3_back", "none", "", "", "", 15.0);
			}
			ChangeCharacterComplexReputation(pchar, "authority", 3);
			pchar.quest.longhappy_santiago2.win_condition.l1 = "location";
			pchar.quest.longhappy_santiago2.win_condition.l1.location = "Cuba1";
			pchar.quest.longhappy_santiago2.function = "LongHappy_SantiagoSail";
			pchar.quest.longhappy_santiago3.win_condition.l1 = "location";
			pchar.quest.longhappy_santiago3.win_condition.l1.location = "Cuba2";
			pchar.quest.longhappy_santiago3.function = "LongHappy_SantiagoSail";
		break;
		
		case "spa_officer_3":
			DialogExit();
			chrDisableReloadToLocation = false;
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешить драться
			for (i=1; i<=4; i++)
			{
				sld = characterFromId("LH_escort_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "SPAIN_CITIZENS");
				LAi_group_Attack(sld, Pchar);
			}
			SetNationRelation2MainCharacter(SPAIN, RELATION_ENEMY);
			LAi_SetFightMode(pchar, true);
			ChangeCharacterNationReputation(pchar, SPAIN, -20);
			ChangeCharacterComplexReputation(pchar, "nobility", -3);
			pchar.quest.longhappy_santiago2.win_condition.l1 = "location";
			pchar.quest.longhappy_santiago2.win_condition.l1.location = "Cuba1";
			pchar.quest.longhappy_santiago2.function = "LongHappy_SantiagoSail";
			pchar.quest.longhappy_santiago3.win_condition.l1 = "location";
			pchar.quest.longhappy_santiago3.win_condition.l1.location = "Cuba2";
			pchar.quest.longhappy_santiago3.function = "LongHappy_SantiagoSail";
		break;
		
		case "Guests_block":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
		break;
		
		// Ян Свенсон патер
		case "Svenson":
			dialog.text = "Charles, congratulations! You know - I always liked you, and Helen for me like a daughter, so I'm happy for you both. Damn… to drop a tear in a church is all I've ever wanted, am I getting old or what?";
			link.l1 = "Everything is fine, Jan, I almost cried near the altar. Incense, probably?";
			link.l1.go = "Svenson_1";
		break;
		
		case "Svenson_1":
			dialog.text = "Right, camphor, damn it. I've been thinking - why my eyes are pinching and nose is itching! Fine, we'll have a talk in Sharptown, hug Gladys and go to others. They've got such faces like we're signing the Peace of Westphalia.";
			link.l1 = "Thanks for coming here, Jan. I am glad to see you, and it means a lot to Helen.";
			link.l1.go = "Guests_block";
		break;
		
		// Ян Свенсон на Исла Тесоро
		case "Svenson_2":
			pchar.questTemp.LongHappy.Count = sti(pchar.questTemp.LongHappy.Count)+1;
			dialog.text = "Here you are, finally, Charles! My corvette overtook you by almost a day - quite an occasion for pride.";
			link.l1 = "You're welcome Jan, but where's Gladys, and your wife?";
			link.l1.go = "Svenson_3";
		break;
		
		case "Svenson_3":
			dialog.text = "I sent Gladys back to Blueveld on a merchant ship - she doesn't approve of all these dashing parties. Джоанна (ЧЕК) couldn't arrive - oh, I had no time to tell you on Martinique! Just imagine - in my old age, I will become a legal father, what's about that? Look, if you hurry, our offsprings will be almost the same age, hahaha!";
			link.l1 = "Jan, my congratulations, that's the news!!! We should drink to it!";
			link.l1.go = "Svenson_4";
		break;
		
		case "Svenson_4":
			dialog.text = "Definitely! But first, to you and your better half! Hey, you are there, shut up!!! The old Forest Devil has a speech to push!\nKhe-khe... So, our dear Monsieur and Madame de Maure... Fuck it! I can't speak like this! Charles, Helen - you, to me, are like kids, and I know that in this room there is no one who wouldn't be happy for your union! So let's drink, Brethrens, for the happiness of our faithful friends, for the fair wind in their sails and the love of Lady Fortune, as strong as their feelings to each other!!! Cheer!";
			link.l1 = "Cheer! Thanks Jan... oh, this rum is much stronger than usuall… What did Nathan mix in it?";
			link.l1.go = "Svenson_5";
		break;
		
		case "Svenson_5":
			dialog.text = "I have no idea, but it srikes rightly. Old Hawk is generally an expert on drinks. Come on, go to the others, I need to make drunk a good hundred of souls greedy to drink.";
			link.l1 = "The Forest Devil pours a drink - such a view! Thank you for taking the organization on yourself. I will definitely be back, as soon as I get around everyone - maybe, someone need help.";
			link.l1.go = "Svenson_6";
		break;
		
		case "Svenson_6":
			DialogExit();
			npchar.dialog.currentnode = "Svenson_6_1";
			if (!CheckAttribute(pchar, "questTemp.LongHappy.Continue") && sti(pchar.questTemp.LongHappy.Count) >= sti(pchar.questTemp.LongHappy.CountNeed)) LongHappy_IslaTesoroToVine();
		break;
		
		case "Svenson_6_1":
			dialog.text = "Everything is fine, Charles?";
			link.l1 = "Perfect, Jan!";
			link.l1.go = "Svenson_6";
		break;
		
		case "Svenson_7":
			pchar.questTemp.LongHappy.Count = sti(pchar.questTemp.LongHappy.Count)+1;
			dialog.text = "And here you are, finally! How did it go on Martinique? Do you feel that your life has changed forever?";
			link.l1 = "It has changed much earlier, Jan. But everything went surprisingly sincerely. Where is Joahnna and...";
			link.l1.go = "Svenson_8";
		break;
		
		case "Svenson_8":
			dialog.text = "Helen? Girl set sail as soon as she found out what we were up to and flew to the horizon. She conveyed all sorts of warm congratulations to you, but still... you broke her heart, oh you really did that. However, everything will be fine, it's just a youth.";
			link.l1 = "Well, the heart wants what it wants, you understand it.";
			link.l1.go = "Svenson_9";
		break;
		
		case "Svenson_9":
			dialog.text = "I do. Well, Joahnna couldn't arrive, just imagine - in my old age, I will become a legal father, what's about that? Look, if you hurry, our offsprings will be almost the same age, hahaha!";
			link.l1 = "Jan, my congratulations, that's the news!!! We should drink to it!";
			link.l1.go = "Svenson_10";
		break;
		
		case "Svenson_10":
			dialog.text = "Definitely! But first, to you and your better half! Hey, you are there, shut up!!! The old Forest Devil has a speech to push!\nCharles and Mary, the entire Brethren is raising goblets in your honor now! The happiness of true friends pleases the soul of any sea wolf, almost as much as the splendor of Spanish gold, ha-ha! Sail well and fair wind on your family journey!!! Сheer!";
			link.l1 = "Cheer! Thanks Jan... oh, this rum is much stronger than usuall… What did Nathan mix in it?";
			link.l1.go = "Svenson_11";
		break;
		
		case "Svenson_11":
			dialog.text = "I have no idea, but it srikes rightly. Old Hawk is generally an expert on drinks. Come on, go to the others, I need to make drunk a good hundred of souls greedy to drink.";
			link.l1 = "This tavern definitely needs to be renamed - 'The Forest Devil himself was standing here behind the counter'! Thank you, Jan, I will definitely be back, as soon as I get around everyone - maybe, someone need help.";
			link.l1.go = "Svenson_6";
		break;
		
		case "Svenson_12":
			dialog.text = "How you're doing, Charles? How is wedding?";
			link.l1 = "Very heartwarming, Jan. I'm glad that we managed to bring all of us here. Looks like Hawk's barrels of rum are starting to show their bottom, aren't they?";
			link.l1.go = "Svenson_13";
		break;
		
		case "Svenson_13":
			dialog.text = "Yes, they are! So, it's time to open what you brought here. And thing - those guys that helped me at first got drunk in the back room. You seem to be still on your feet, bridegroom - can you drag a box of another sherry?";
			link.l1 = "Sure, just tell me where to go. Maybe I’ll find a few sober heads along the way to help me. Although, most of my guys are probably already drunk as a shunk.";
			link.l1.go = "Svenson_14";
		break;
		
		case "Svenson_14":
			dialog.text = "The wine was piled in the cellars under shipyard, remember them? Hawk said to keep it in the far corridor, ''to save until the holiday'' - he says. Also he says that there are perfect temperature and humidity, just like in your winery in the basement . Well, he is a big snob.";
			link.l1 = "He made a right desicion, Jan. I'll go, but first, tell me - did you see my wife?";
			link.l1.go = "Svenson_15";
		break;
		
		case "Svenson_15":
			dialog.text = "She and Dannie went somewhere. Let girls talk, Charles, and we have to start a real party. Go into the cellars while I deal with food. Cause it smells like soon we'll be eating coal instead of sheep ribs.";
			link.l1 = "Alright, go save the meat, I'll drag our wine.";
			link.l1.go = "Svenson_16";
		break;
		
		case "Svenson_16":
			DialogExit();
			npchar.dialog.currentnode = "Svenson_6_1";
			LongHappy_IslaTesoroToVineGo();
		break;
		
		case "Svenson_17":
			dialog.text = "Charles, Nathan, what happened, did you start a drunk fight?!";
			link.l1 = "No, Jan, we fought together againts some armed cutters in the dungeons. We dealt with them, but they were only scouts - the main squad is chasing us.";
			link.l1.go = "Svenson_18";
		break;
		
		case "Svenson_18":
			dialog.text = "Squad? What are you talking about?! Marcus, come here! Charles, come on, tell us everything.";
			link.l1 = "Like I said: there are some bastards in the dungeons under the shipyard. Well-armed. Nathan and I fought them and miraculously put everyone down. But there are more of them - I heard, one of them was sent for help. And yes, one of them remembered some Jacques.";
			link.l1.go = "Svenson_19";
		break;
		
		case "Svenson_19":
			DialogExit();
			sld = characterFromId("Terrax");
			sld.dialog.currentnode = "Terrax_7";
			ChangeCharacterAddressGroup(sld, "Pirates_tavern", "tables", "stay8");
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "Svenson_20":
			dialog.text = "I recognize their faces... this one, and that bastard lying around the door. They are thugs of Jacques the Kindman. Don't remember their names, but I know it for sure.";
			link.l1 = "So this is Barbazon's fault? He is out of mind or what?!";
			link.l1.go = "Svenson_21";
		break;
		
		case "Svenson_21":
			dialog.text = "I don’t know, but it seems that the Kindman decided to take advantage of the opportunity and arrange a radical rearrangement among the barons of the Brethren.";
			link.l1 = "In this case, I hope that he will appear himself - I've been dreaming so long to make a couple of holes in his body. Bastard, ruined my wedding, just think about it! Go to the street! Let's arrange a party for them!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LongHappy_TavernReload");
		break;
		
		case "Svenson_22":
			dialog.text = "And here is our tired hero! Hah, Charles, it was something! Jacques, such a rat! Look how he arranged everything - he almost succeeded!";
			link.l1 = "Yes, probably, we should have killed that bastard when we had finished with Jackman. However, it is over. Barbazon is dead.";
			link.l1.go = "Svenson_23";
		break;
		
		case "Svenson_23":
			if (CheckAttribute(pchar, "questTemp.LongHappy.SvensonsShipSink")) dialog.text = "Well, not to say it 's over at all - our life goes on! Although I feel myself completely wrecked. I am too old to jump into the sea from a poop covered with fire and swim a whole hour to the shore, looking out for sharks. I hope we still have rum...";
			else dialog.text = "Well, not to say it 's over at all - our life goes on! Damn it, I feel myself ten years younger! It was long time ago since I last time has fought like that! I hope your stocks of rum and wine weren't stolen during the mess - we need to drink for it well!";
			link.l1 = "Yup, I would drink too, but first I have to check the residence, I don't know have you been told or not...";
			link.l1.go = "Svenson_24";
		break;
		
		case "Svenson_24":
			if (CheckAttribute(pchar, "questTemp.LongHappy.Tichingitu_Victim"))
			{
				dialog.text = "It's about your Indian fellow? Yes, I heard, how it happened?";
				link.l1 = "Covered my wife and Dannielle from a bullet shot by one bastard. We should go, I'll tell you along the way.";
			}
			else
			{
				dialog.text = "It's about Nathan? Yes, I heard, just didn't get how it happened?";
				link.l1 = "Covered our wives from a bullet shot by one bastard. We should go, I'll tell you along the way.";
			}
			link.l1.go = "Svenson_25";
		break;
		
		case "Svenson_25":
			DialogExit();
			DoQuestReloadToLocation("Pirates_townhall", "goto", "goto4", "LongHappy_DannyInResidence");
		break;
		
		case "Svenson_26":
			if (CheckAttribute(pchar, "questTemp.LongHappy.Tichingitu_died") && CheckAttribute(pchar, "questTemp.LongHappy.Jino_died"))
			{
				dialog.text = "Stay strong, Charles. I'm really sorry for you boys. Today, many good guys have gone, and for each of them, in hell, Barbason will get more oil in his boiler.";
				link.l1 = "It has no sence... damn it! It's hard, Jan... I've already lost friends, but I can't get used to it.";
				link.l1.go = "Svenson_28";
			}
			else
			{
				if (CheckAttribute(pchar, "questTemp.LongHappy.Jino_died"))
				{
					dialog.text = "So that quiet guy-medic? I'm sorry, Charles, sincerely. He was a good guy.";
					link.l1 = "Yes, Jan, me too. But, I am afraid, the world of science has lost far more than me. He was a genius... sophisticated, like all of them, but... fuck...";
					link.l1.go = "Svenson_27";
				}
				else
				{
					if (CheckAttribute(pchar, "questTemp.LongHappy.Tichingitu_Victim")) sTemp = "your Indian guy";
					else sTemp = "Nathan";
					dialog.text = "Well, it seems to be over. Today, many good guys have gone, and for each of them, in hell, Barbason will get more oil in his boiler, but "+sTemp+" will be fine and this is the main thing.";
					link.l1 = "You're right, Jan, and it's a great weight off my mind. How are the other barons? Are they okay?";
					link.l1.go = "Svenson_32";
				}
			}
		break;
		
		case "Svenson_27":
			dialog.text = "The last filth of Jacques Barbason. You're right, if we had killed him before everything could have been otherwise.";
			link.l1 = "But what's the use of regretting the past? The past cannot be changed. How are the other barons? Did everyone survive?";
			link.l1.go = "Svenson_32";
		break;
		
		case "Svenson_28":
			dialog.text = "No one can get used to it. Let's dink for guys? I found a bottle in the table, it miraculously survived this mess.";
			link.l1 = "Pour, I... Damn, a thousand damnations!";
			link.l1.go = "Svenson_29";
		break;
		
		case "Svenson_29":
			dialog.text = "Tell me about them. This medic seemed smart. He expressed himself so wisely.";
			link.l1 = "He did. But, I am afraid, the world of science has lost far more than me. He was a genius... sophisticated, like all of them. The master of miracles!";
			link.l1.go = "Svenson_30";
		break;
		
		case "Svenson_30":
			dialog.text = "About Indian guy? Where did you find him?";
			link.l1 = "Rescued him from prison on Guadeloupe, almost immediately after my arrival. Really funny and stupid story. So, he stayed with me. From his own considerations -  I saved him and he owes me till the end of his life. Terse, dressed up strangely, but faithful as a knight, and from the musket hit the coin with fifty steps.";
			link.l1.go = "Svenson_31";
		break;
		
		case "Svenson_31":
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			dialog.text = "Well, he paid you the debt, what can I say. Saved "+sld.name+" and Dannielle from that bastard. It seems to me - this is a worthy end for a warrior.";
			link.l1 = "It is, Jan. Lets drink to the memory of the fallen... How are the other barons? Are they okay?";
			link.l1.go = "Svenson_32";
		break;
		
		case "Svenson_32":
			dialog.text = "This night cost us dearly. I don't even know when the Brethren will recover from this massacre. Kindman perfectly chose the time and place to hit. He almost succeeded - just a bit and all would be over. But we lost much less than we could.";
			link.l1 = "";
			if (!CheckAttribute(pchar, "questTemp.Saga.DodsonDie")) link.l1.go = "Svenson_33";
			else link.l1.go = "Svenson_35";
		break;
		
		case "Svenson_33":
			dialog.text = "The Shark is in the infirmary, his ship got a volley from twenty-four pounds. He flew overboard, broke a couple of ribs, swallowed sea water, but he is fine.";
			link.l1 = "";
			if (CheckAttribute(pchar, "questTemp.LongHappy.BigMarry")) link.l1.go = "Svenson_34"; // был Венсан
			else link.l1.go = "Svenson_36"; // на завершение
		break;
		
		case "Svenson_34":
			if (CheckAttribute(pchar, "questTemp.LongHappy.Vensan_alive")) dialog.text = "Bernard got just a couple of scratches - he was defending the shore and wiping out the catacombs. Now, he's in the harbor, organizing hospitals for the wounded and funerals for those who are unlucky.";
			else dialog.text = "Bernard was unlucky - was in house-to-house searches after the attack from the catacombs and ran into a bunch of these bastards in the storehouses. He caught a bullet. It is a pity, he was a good captain... Tyrax will be furious when he finds out.";
			link.l1 = "";
			link.l1.go = "Svenson_36"; // на завершение
		break;
		
		case "Svenson_35":
			if (CheckAttribute(pchar, "questTemp.LongHappy.Vensan_alive")) dialog.text = "Bernard got just a couple of scratches - he was defending the shore and wiping out the catacombs. Now, he's in the harbor, organizing hospitals for the wounded and funerals for those who are unlucky.";
			else dialog.text = "Bernard was unlucky - was in house-to-house searches after the attack from the catacombs and ran into a bunch of these bastards in the storehouses. He caught a bullet. It is a pity, he was a good captain... Tyrax will be furious when he finds out.";
			link.l1 = "";
			link.l1.go = "Svenson_36"; // на завершение
		break;
		
		case "Svenson_36":
			dialog.text = "About Hawk you know. Dannie won't allow him to leave the island atleast a month, that’s for sure. He had one business on our minds... oh, well.";
			link.l1 = "";
			if (CheckAttribute(pchar, "questTemp.LongHappy.Terrax.Prisoner")) link.l1.go = "Svenson_37";
			else link.l1.go = "Svenson_38";
		break;
		
		case "Svenson_37":
			if (CheckAttribute(pchar, "questTemp.LongHappy.Terrax.Free"))
			{
				dialog.text = "Marcus is fine as always. As soon as he went ashore, he immediately began to shake out the souls of the sentries that overlooked all this filth. He still manages to command the restoration of order in the town. Iron man, not otherwise.";
				link.l1 = "ron is softer. I guess, our baron made from metal that is unknown to science yet, haha!";
			}
			else
			{
				pchar.questTemp.LongHappy.Terrax.Lost = "true";
				dialog.text = "Only with Marcus is incomprehensible - his ship was boarded, but the survivors claim that he managed to jump overboard. I already sent the longboats to search the bay. I hope it comes out that our baron is too tough to give up so simple.";
				link.l1 = "That's bad, but it's to early to cry over him, Tyrax really wouldn't give us so easy. Let's wait for the result of searches.";
			}
			link.l1.go = "Svenson_39";
		break;
		
		case "Svenson_38":
			if (CheckAttribute(pchar, "questTemp.LongHappy.TerraxShipSink"))
			{
				dialog.text = "Marcus swam to shore after his ship was drown. Well, you know - Tyrax is not one of those who will drown from such a trifle. Now he's somewhere in the town. Probably shaking out the souls of the sentries that overlooked all this filth. Iron man, not otherwise.";
				link.l1 = "Iron would drown.  I guess, our baron made from metal that is unknown to science yet, haha!";
			}
			else
			{
				dialog.text = "Marcus is fine as always. As soon as he went ashore, he immediately began to shake out the souls of the sentries that overlooked all this filth. He still manages to command the restoration of order in the town. Iron man, not otherwise.";
				link.l1 = "Iron is softer. I guess, our baron made from metal that is unknown to science yet, haha!";
			}
			link.l1.go = "Svenson_39";
		break;
		
		case "Svenson_39":
			dialog.text = "That's all. Well, it could be worse. Даже свадьба у тебя, Шарль вышла... боевая. Главное - вы оба живы. Совет, в общем, да любовь!";
			link.l1 = "Thanks Jan. Thanks to all of you... I have to admit, I forgot that we started with a celebration.";
			link.l1.go = "Svenson_40";
		break;
		
		case "Svenson_40":
			dialog.text = "So, here is a reminder.";
			link.l1 = "Yeah, that was a party...";
			if (CheckAttribute(pchar, "questTemp.LongHappy.Tichingitu_Rum")) link.l1.go = "Svenson_41";
			else link.l1.go = "Svenson_43";
		break;
		
		case "Svenson_41":
			dialog.text = "Oh yup, wait a minute. There is such a thing - you seemed to have an Indian guy in your team. Funny dressed.";
			link.l1 = "Yes, Tichingitu, he disappeared at the very beginning of this mess, I'm starting to worry. Do you know anything?";
			link.l1.go = "Svenson_42";
		break;
		
		case "Svenson_42":
			pchar.questTemp.LongHappy.Tichingitu_Wife = "true";
			dialog.text = "Seems like. Our bartender was making noise that his niece had been abducted, only supposedly before the attack. He says they saw her with some kind of Indian, carried her on his shoulder along the shore east of the town. I didn’t notice among Kindman's scum any Indians, but I remembered about yours when I heard it. You should go, look for him or something, until he gets into trouble. Cause bartender threatens to kill him if he finds him first. He is a good fellow, but for his niece he will unscrew any head.";
			link.l1 = "Yup, thanks, Jan, I'll find him.";
			link.l1.go = "Svenson_43";
		break;
		
		case "Svenson_43":
			dialog.text = "Well, in general, something like this... Sorry, I am bad in speeches. And now even worse - this night has squeezed everyone dry. We all should rest atleast a day - then we will decide how to proceed.";
			link.l1 = "You're right, Jan. I should go, I need to fresh up my mind.";
			link.l1.go = "Svenson_44";
		break;
		
		case "Svenson_44":
			DialogExit();
			DoQuestReloadToLocation("Pirates_town", "reload", "reload3", "LongHappy_WifeInTown");
		break;
		
		case "Svenson_45":
			dialog.text = "Looking good, Charles. Had a good sleep?";
			link.l1 = "Yes, we were given a cozy house on the outskirts of the town. I even thought that I dreamed of all the madness that happened yesterday. And here you are Jan, looking bad. What else happened?";
			link.l1.go = "Svenson_46";
		break;
		
		case "Svenson_46":
			dialog.text = "No, I just haven't slept yet. You know - tidying up the city after everything that happened is a hard task.";
			link.l1 = "How are Dannie and Nathan? Where's everyone?";
			link.l1.go = "Svenson_47";
		break;
		
		case "Svenson_47":
			dialog.text = "Having rest. Don't disturb them, Dannie warned everyone that she has taken guns to bed today... Shark Dodson in the sea, others are burying the departed on north of the island.";
			link.l1 = "";
			link.l1.go = "Svenson_48";
		break;
		
		case "Svenson_48":
			if (CheckAttribute(pchar, "questTemp.LongHappy.Terrax.Prisoner") && !CheckAttribute(pchar, "questTemp.LongHappy.Terrax.Free")) dialog.text = "Marcus hasn't been found yet, but we can handle it, don’t worry. You have done so much for all of us, so don't bother yourself. Tyrax will return soon or later - we will find him.";
			else dialog.text = "Marcus finished here and sped off on someone's lugger to Hispaniola. It is necessary to solve some issues that arose after the death of Barbazon. He sent greetings and best wishes to you and your wife.";
			link.l1 = "";
			link.l1.go = "Svenson_49";
		break;
		
		case "Svenson_49":
			dialog.text = "Well, Brothren withstood this blow. Soon, we will rise even stronger than we were. Kindman and Jackman have been shaken our unity for so long, now they're gone and my heart feels - we will make the Caribbean flinch more than once. The Golden Age is coming for those to whom laws and kings are not nice, remember my words.";
			link.l1 = "Would be nice. I’m not sure that I will withstand now in the Old World. I didn’t think when I came here that I would fall in love with the freedom of the sea, these crazy colors of sunsets and sunrises, would find the best woman in the world and such a good friends.";
			link.l1.go = "Svenson_50";
		break;
		
		case "Svenson_50":
			dialog.text = "Well, you know the course, just make up your mind. In our homes you are always welcome.";
			link.l1 = "Thanks, Jan. It means a lot to me.";
			if (CheckAttribute(pchar, "questTemp.Mtraxx")) 
			{
				if (pchar.questTemp.Mtraxx == "full_complete_end" || pchar.questTemp.Mtraxx == "full_complete") link.l1.go = "Svenson_51";
				else link.l1.go = "Svenson_54";
			}		
			else link.l1.go = "Svenson_54";
		break;
		
		case "Svenson_51":
			pchar.questTemp.LongHappy.Baron = "true";
			dialog.text = "But first, there's something important left. Charles, while you were sleeping, we got together and that's what we decided\nSince Barbazon is dead, the Brethren needs a new baron. Since there was a clear majority of us here, and the decision was made unanimously, here it is. Congratulations - you are the new Baron of Le Francois. Wait ... I understand - you are a secular person, and you have no time to conduct business in this nice place, so put a trusted person, and do what you want. Just remember - your voice is in the Brethren now.";
			link.l1 = "Jan, I... have nothing to say... It's a great honor, I don't even know...";
			link.l1.go = "Svenson_52";
		break;
		
		case "Svenson_52":
			dialog.text = "C'mon! You have proven yourself perfectly back then with Tyrax, and then with all this story with the Sharp's legacy. It's the blessing of God himself. For you nothing will change - do as planned, and in your absence, your man will take charge of all affairs\nThere is one promising guy Jan David, he's one of the Buccaneers. Frenchman, like you. But it will take some time for me to find him - it seems he was captured by the Spaniards, but this can be solved, don't worry. I will make sure that he will send your part to you as soon as he gets comfortable with business.";
			link.l1 = "I really didn’t expect that everything would be like that. Well, since you really decided so then be it. The Pirate Baron Charles de Maure!";
			link.l1.go = "Svenson_53";
		break;
		
		case "Svenson_53":
			dialog.text = "Long live the baron! If anyone deserves it, it has to be you. Wear it with pride, and don't forget - you are one of us now, no matter how beautiful the uniform  you wear, here, right under it beats the heart of a real filibuster.";
			link.l1 = "I don’t know, maybe you are exaggerating... But I will do everything I can to justify your trust.";
			link.l1.go = "Svenson_54";
		break;
		
		case "Svenson_54":
			dialog.text = "What are you going to do now? Come back to Europe, back to father, to introduce him a young wife?";
			if (CheckAttribute(pchar, "questTemp.LongHappy.Tichingitu_died") || CheckAttribute(pchar, "questTemp.LongHappy.Jino_died"))
			{
				link.l1 = "Yes, but first I must say farewell… You know what I mean.";
				link.l1.go = "Svenson_56";
			}
			else	
			{
				link.l1 = "Maybe not so soon. Once again I’ll sail through the archipelago, want to breathe the fresh air for the last time.";
				link.l1.go = "Svenson_55";
			}
		break;
		
		case "Svenson_55":
			dialog.text = "Well, you've got a ship, you can sail home anytime you wish.";
			link.l1 = "I hope so. Thanks Jan, thanks to all of you and see you later, my old my friend! Say hello to the Hawks and Shark!";
			link.l1.go = "Svenson_58";
		break;
		
		case "Svenson_56":
			if (CheckAttribute(pchar, "questTemp.LongHappy.Tichingitu_died") && CheckAttribute(pchar, "questTemp.LongHappy.Jino_died")) sTemp = "They deserves";
			else sTemp = "He deserve";
			dialog.text = "Yes, it's hard, but we have to do this. To the sea?";
			link.l1 = "No, I will sail to Antigua. "+sTemp+" to rest in peace in a place that became our home for a while.";
			link.l1.go = "Svenson_57";
		break;
		
		case "Svenson_57":
			dialog.text = "Say a few kind words from me too. And don't worry - we can handle it on our own since now. All is going to be fine.";
			link.l1 = "Thanks Jan. See you soon my old friend! Give my best to the Hawks and Shark!";
			link.l1.go = "Svenson_58";
		break;
		
		case "Svenson_58":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "LongHappy_IslaMarryComplete", 10.0);
		break;
		
		case "Svenson_":
			dialog.text = "";
			link.l1 = "";
			link.l1.go = "Svenson_";
		break;
		
		// Глэдис
		case "Gladis":
			dialog.text = "Young man, you have grown even more in my eyes today. You have done so much for Helen, that no words of gratitude will be enough. I only do hope that you will take care of her further. If her father was alive and saw this, how happy he would've been... sorry.";
			link.l1 = "It's alright, Gladys. You crossed the archipelago to support Helen on this day. We both really appreciate your visit with Jan, thank you.";
			link.l1.go = "Guests_block";
		break;
		
		// Форже - патер Мэри
		case "forge":
			dialog.text = "Monsieur de Maure, I apologize for the familiarity, but I will say it this way - Charles, my friend, I am sincerely happy for you! If I can do something for you or your bride, just say it!";
			link.l1 = "I thank you, Baron, I am so happy, and the vineyards that my father wanted as a trousseau, I think I can redeem myself - fortunately, my financial situation during my being in the New World have considerably improved.";
			link.l1.go = "forge_1";
		break;
		
		case "forge_1":
			dialog.text = "Yes, I suppose you can afford just about anything you want, Charles. Excuse me, but  I will make my contribution as the representative father - Today, I am going to write to my good friend the Minister of Finance. Your chosen one will be granted the title of nobility, and, I think, we will find some good estate for her, let us say in Gascony, among those which were seized for debts, and assign it to her retroactively. So no one will dare to say that the Chevalier de Monper found a wife out of position!";
			link.l1 = "I don't think I am concerned about such gossips, but thanks, Baron. Still, you shouldn't";
			link.l1.go = "forge_2";
		break;
		
		case "forge_2":
			dialog.text = "I more than should! Now go, Charles, share your attention to the rest of the guests. And once again, accept my most sincere congratulations!";
			link.l1 = "Me and my wife thanks you. See you, Baron.";
			link.l1.go = "Guests_block";
		break;
		
		// Форже - патер ГГ
		case "forge_3":
			dialog.text = "Monsieur de Maure, I apologize for the familiarity, but I will say it this way - Charles, my friend, I am sincerely happy for you! If I can do something for you or your bride, just say it!";
			link.l1 = "Thank you, Baron, but you've already done a lot for me. It is enough for us that you have responded to the invitation.";
			link.l1.go = "forge_4";
		break;
		
		case "forge_4":
			dialog.text = "How could I haven't responded, Charles! But listen - I want to present you and your beautiful bride a worthy gift, but I can't come up with anything that you couldn't get for yourself with money or a sword. Therefore, I will write to my friend the Minister of Finance in Paris, and by the time you arrive in Europe, you will be waited to sign the royal rescript of the exaltation the name of de Monper in the title of Barons de Monper! No, not a word, this is the least I can do for you.";
			link.l1 = "I don't even know what to say, Baron... Father will be so happy. Sincerely thank you.";
			link.l1.go = "Guests_block";
		break;
		
		// Форже гость
		case "forge_5":
			dialog.text = "Charles, please, accept my sincere congratulations! Your chosen one is just a miracle! I think, today, colonial fashion has got a strong ... jab to a new direction. Your originality has always fascinated me! May you and your beautiful half live happily ever after!";
			link.l1 = "Thank you, Baron. You have honored us with your visit.";
			link.l1.go = "forge_6";
		break;
		
		case "forge_6":
			dialog.text = "How could I stay away my friend? We've come through a lot together and I'm proud to call you my friend, Charles. Remember - my doors are always open for you, no matter what happens.";
			link.l1 = "As the doors of de Monper family are open to you, Baron.";
			link.l1.go = "Guests_block";
		break;
		
		// Пуанси патер Мэри
		case "puancie":
			dialog.text = "Charles, my friend, this is a very important day, and I am glad that you invited me to share it with you. You and I have come a long and difficult way, and to become a made-up face of mademoiselle... please, forgive me - Madame de Maure, it is an honor for me, believe me. With all my heart I wish you happiness!\nAnd please, let me know when you are going to Europe - I, as the representative father of your chosen one, will send your father all the necessary wedding gifts. Believe me, no one will say that chevalier de Monper's bride is poor or unworthy!";
			link.l1 = "If I may ask, Chevalier, in a couple of miles, north of the estate de Monper, there are good vineyards, they belong to the La Brigne family and I...";
			link.l1.go = "puancie_1";
		break;
		
		case "puancie_1":
			dialog.text = "Not any word more, my friend, not any word! I will immediately write to my authorized representative in Lyon - by your arrival these vineyards will be given to your chosen one.";
			link.l1 = "Thank you, Chevalier. You are right - our... friendship, went through... a lot. But, I'm really glad that you shared this day with us. See you and thanks again!";
			link.l1.go = "Guests_block";
		break;
		
		// Пуанси патер ГГ
		case "puancie_2":
			dialog.text = "Charles, my friend, this is a very important day, and I am glad that you invited me to share it with you. We have come a long and difficult way, and to testify today at your wedding is an honor for me. With all my heart I wish you happiness! And let me know when you are going to Europe - I will send your father worthy wedding gifts.";
			link.l1 = "There is no need in this, Chevalier. Thank you for responding to my invitation.";
			link.l1.go = "puancie_3";
		break;
		
		case "puancie_3":
			Log_Info("You have got gems");
			PlaySound("interface\important_item.wav");
			TakeNItems(pchar, "jewelry2", 50);
			TakeNItems(pchar, "jewelry3", 50);
			TakeNItems(pchar, "jewelry4", 50);
			dialog.text = "As I said - it's an honor for me! But wait, my friend, I would like to present something to you on this occasion - I am sure this will please both you and your chosen one. Beautiful stones from our mines in New Guiana - pick them a decent frame and madame de Maure will bright even at the royal reception! If you convince her to wear a dress, of course...";
			link.l1 = "Oh, you really shouldn't, chevalier. Thank you again.";
			link.l1.go = "Guests_block";
		break;
		
		// Пуанси гость
		case "puancie_4":
			dialog.text = "Charles, my friend, let me congratulate you! We have come a long and difficult way, and I am sincerely glad to be here today. Our Lord is witness - you deserve your happiness! Keep it and protect it - wishing you many happy years to come!";
			link.l1 = "Thank you, Chevalier, me and my wife are very grateful.";
			link.l1.go = "Guests_block";
		break;
		
		// Фадей патер
		case "fadey":
			dialog.text = "Charles, such a celebration, and how many important persons! Let me wholeheartedly wish you happiness and good health, and children for joy! As we say - 'gor'ko'!";
			link.l1 = "Thank you, Fadey, you honored me by agreeing to come.";
			link.l1.go = "fadey_1";
		break;
		
		case "fadey_1":
			dialog.text = "But, I don't quite understand why there are so many people like we are not concluding a marriage, but a big trade deal, and still not enough bears and vodka for my taste here... haha! Well, I'm joking, Charles, why have you completely become pale? Give me a hug, you married captain!";
			link.l1 = "Wow... Fadey, you're strong like a bear!";
			if (CheckAttribute(pchar, "questTemp.Persian"))
			{
				if (pchar.questTemp.Persian == "time" || pchar.questTemp.Persian == "end") link.l1.go = "fadey_2";
				else link.l1.go = "Guests_block";
			}
			else link.l1.go = "Guests_block";
		break;
		
		case "fadey_2":
			GiveItem2Character(pchar, "blade_22");
			GiveItem2Character(pchar, "blade_23");
			GiveItem2Character(pchar, "blade_24");
			Log_Info("You got three Persian sabres");
			PlaySound("interface\important_item.wav");
			dialog.text = "Wait, Charles, don't go away - it's not worthy for the guest to come to the wedding without gifts. Here, take them. I know - you tried to find all these blades, and some, you obviously liked. So accept them - hang them in a family estate and remember Fadey Moskovit with a kind word!";
			link.l1 = "This is a real gift! Thank you, Fadey. These are indeed wonderful weapon, and they will take their rightful place in the estate de Monper, I promise!";
			link.l1.go = "Guests_block";
		break;
		
		// Фадей гость
		case "fadey_3":
			dialog.text = "Charles, such a celebration, and how many important persons! Let me wholeheartedly wish you happiness and good health, and children for joy! As we say - 'gor'ko'! Give me a hug, you married captain!";
			link.l1 = "Wow… Fadey, you're strong like a bear!";
			link.l1.go = "Guests_block";
		break;
		
		// Проспер Трубаль
		case "Prosper":
			dialog.text = "Charles, I couldn't miss it, I congratulate you and your chosen one with all of my heart! Be happy! You know, a couple of months ago I merried my daughter, for a good person and in love, but honestly, I was upset that it wasn't you... Well, okay... what am I even talking about - congratulations! May you live happily ever after!";
			link.l1 = "Thanks, Prosper, I'm glad you came.";
			link.l1.go = "Guests_block";
		break;
		
		// Тичингиту
		case "Tichingitu":
			dialog.text = "Congratulations, captain! A strange rite, but beautiful - Tichingitu liked it. Although, the captain should just abduct his squaw, and send a ransom to her relatives.";
			if (CheckAttribute(pchar, "questTemp.LongHappy.MarrySP")) link.l1 = "Well, in some way, I did, and it's just a formality. Thank you, my friend!";
			else link.l1 = "Well, in some way, I did, and it's just a formality. Thank you, my friend! You and I will talk more in Sharptown - there will be much less official and more sincere fun, I promise!";
			link.l1.go = "Tichingitu_1";
		break;
		
		case "Tichingitu_1":
			dialog.text = "Fire water again? Tichingitu can't say that he like it. Maybe, celebration boarding will do better, or at least dancing around a bonfire?";
			if (CheckAttribute(pchar, "questTemp.LongHappy.MarrySP")) link.l1 = "I do hope it will not come to dances around bonfires long before the end, and I would rather keep without boarding. Okay, be patient - just a bit left, and we immediately move to the tavern.";
			else link.l1 = "I'm afraid it will come to dances around bonfires long before the end, and I would rather keep without boarding. Okay, be patient - just a bit left, and we immediately sail to Sharptown.";
			link.l1.go = "Guests_block";
		break;
		
		case "Tichingitu_2":
			pchar.questTemp.LongHappy.Count = sti(pchar.questTemp.LongHappy.Count)+1;
			dialog.text = "Captain, congratulations again! Tichingitu likes this celebration more than the previous one. The captain knows how to choose friends - here is more sincerity, less hypocrisy and  false hair.";
			link.l1 = "Thank you, my friend! Just don't drink the fire water - it is very hard here.";
			link.l1.go = "Tichingitu_4";
			link.l2 = "Thank you, my friend! Let's have a drink? I know, you don't like it, but today, you should try it!";
			link.l2.go = "Tichingitu_3";
		break;
		
		case "Tichingitu_3":
			pchar.questTemp.LongHappy.Tichingitu_Rum = "true";
			dialog.text = "Tichingitu doesn't like fire water, but if the captain insists, today it is possible to do. To your happiness, and your squaw!";
			link.l1 = "And to you, Tichingitu! To your friendship and loyalty!";
			link.l1.go = "Tichingitu_4";
		break;
		
		case "Tichingitu_4":
			DialogExit();
			npchar.dialog.currentnode = "Tichingitu_4_1";
			if (CheckAttribute(pchar, "questTemp.LongHappy.MarrySP"))
			{
				sld = characterFromId("Mary");
				sld.dialog.currentnode = "LongHappy_57";
				LAi_SetActorType(sld);
				LAi_ActorDialog(sld, pchar, "", -1, 0);
			}
			else 
			{
				if (!CheckAttribute(pchar, "questTemp.LongHappy.Continue") && sti(pchar.questTemp.LongHappy.Count) >= sti(pchar.questTemp.LongHappy.CountNeed)) LongHappy_IslaTesoroToVine();
			}
		break;
		
		case "Tichingitu_4_1":
			dialog.text = "Nice party, captain.";
			link.l1 = "I'm glad you are satisfied.";
			link.l1.go = "Tichingitu_4";
		break;
		
		case "Tichingitu_5":
			dialog.text = "Captain, came out to look at the stars? The night promises to be very beautiful. Tichingitu loves the night over the sea.";
			link.l1 = "Glad to meet you! Me and Nathaniel need your help - guys at the tavern are out of drinks, we need to drag a few boxes of drinks from stock under the shipyard.";
			link.l1.go = "Tichingitu_6";
		break;
		
		case "Tichingitu_6":
			dialog.text = "Lead, captain. Tichingitu follows you, as always.";
			link.l1 = "Move!";
			link.l1.go = "Tichingitu_7";
		break;
		
		case "Tichingitu_7":
			DialogExit();
			chrDisableReloadToLocation = false;
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
		break;
		
		case "Tichingitu_8":
			dialog.text = "Captain, there are people, and they are armed, Tichingitu hears the rattling of their weapons. I don't like it. Let's hide.";
			link.l1 = "Come on, mate - this is Sharptown, here even to the restroom people go armed with pistols. Hey Nathan... well, damn it! If it goes like this, you’ll break up all the bottles!";
			link.l1.go = "Tichingitu_9";
		break;
		
		case "Tichingitu_9":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			LongHappy_SetBandosInDungeon();
		break;
		
		case "Tichingitu_10":
			dialog.text = "Captain… you… Tichingitu's head is wrecking like mast in the storm. What happened?";
			link.l1 = "I want to as the same! Where have you been all this time?!";
			link.l1.go = "Tichingitu_11";
		break;
		
		case "Tichingitu_11":
			dialog.text = "Tichingitu woke up an hour ago because of the cries of this girl. She ran along the beach almost naked and screamed something about the abductors and savages... But there is nobody here except us. Do you have water? Not fiery, ordinary?";
			link.l1 = "There was a flask somewhere, if I didn’t lose it in a battle... here you go. How did you manage to do this? Her uncle, a local bartender, is looking for Indian who has abducted his niece, and threatening to tear him off his feathered empty head. Who do you think he is talking about?";
			link.l1.go = "Tichingitu_12";
		break;
		
		case "Tichingitu_12":
			dialog.text = "Tichingitu remembered. She was helping the Forest Devil at the tavern with wedding. We drank fire water with you, and Tichingitu wanted more. And then, this squaw... she was so cute and... Captain, I think I remembered! Tichingitu wanted to marry her... He wanted to build a canoe and take her away... Spirits of mercy! Very bad people came up with fire water. Perhaps, the demons! Tichingitu will never again ...";
			link.l1 = "To take her away? Build a canoe?! Ahah, you are a romantic, my friend... oh, I can't... stop laughing!";
			link.l1.go = "Tichingitu_13";
		break;
		
		case "Tichingitu_13":
			dialog.text = "Captain, Tichingitu has stolen the squaw, yes... but, can we, well... not get married now? She is ... loud, like a papagallo bird, and... not so beautiful.";
			link.l1 = "Yes, my friend, the women, having fun all night long, are a miserable sight in the morning. Don't worry, the hero-lover, we'll come up with something. Come on, we have to go back to Sharptown, you missed your holiday board...";
			link.l1.go = "Tichingitu_14";
		break;
		
		case "Tichingitu_14":
			dialog.text = "A board? Captain has mentioned a battle before. Thoughts still don't obey Tichingitu. What happened in the town?";
			link.l1 = "A real battle on land and at sea. The guns were shooting all night, I guess, they was probably heard even in San Jose. However, you were busy with another 'battle', I understand... Come on, I'll tell you everything along the way.";
			link.l1.go = "Tichingitu_15";
		break;
		
		case "Tichingitu_15":
			DialogExit();
			chrDisableReloadToLocation = false;
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			sld = characterFromId("LH_waitress");
			LAi_SetActorType(sld);
			LAi_ActorFollowEverywhere(sld, "", -1);
			pchar.quest.longhappy_shoregirl1.win_condition.l1 = "location";
			pchar.quest.longhappy_shoregirl1.win_condition.l1.location = "Pirates_town";
			pchar.quest.longhappy_shoregirl1.function = "LongHappy_ReturnShoreGirl";
		break;
		
		case "Tichingitu_16":
			dialog.text = "Thanks, captain... Tichingitu will never...";
			link.l1 = "Yeah, 'the stallion from the distant plains' you definitely shouldn't drink anymore. Go get some sleep. I’m already falling from my feet too.";
			link.l1.go = "Tichingitu_17";
		break;
		
		case "Tichingitu_17":
			DialogExit();
			npchar.Dialog.Filename = "Quest\Sharlie\Tichingitu.c";
			LAi_SetImmortal(npchar, false);
			npchar.OfficerWantToGo.DontGo = true;
			npchar.CompanionDisable = true;
			npchar.loyality = MAX_LOYALITY;
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, true);
			LAi_SetOfficerType(npchar);
			npchar.Payment = true;
			npchar.DontClearDead = true;
			npchar.dialog.currentnode = "Tichingitu_officer";
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			SaveCurrentNpcQuestDateParam(npchar, "HiredDate");
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			sld.dialog.currentnode = "LongHappy_55";
			ChangeCharacterAddressGroup(sld, "Pirates_town", "goto", "goto2");
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "Tichingitu_18":
			dialog.text = "Captain, congratulations again! Tichingitu likes this celebration more than the previous one. The captain knows how to choose friends - here is more sincerity, less hypocrisy and false hair.";
			link.l1 = "And much more fire water. By the way, will you have a drink with me? I know that you don't like it, but we have an unusual occasion!";
			link.l1.go = "Tichingitu_19";
		break;
		
		case "Tichingitu_19":
			dialog.text = "Tichingitu doesn't like fire water, but if the captain insists, today it is possible to do. To your happiness, and your squaw!  Move along the same way, and let the sun and moon always illuminate it.";
			link.l1 = "Thank you, my friend. Cheers to you, Tichingitu! To your friendship and loyalty!";
			link.l1.go = "Tichingitu_4";
		break;
		
		// губернаторы
		// Сен Пьер
		case "FortFrance_Mayor":
			if (pchar.questTemp.GoldenGirl == "end")
			{
				dialog.text = "Great ... celebration, I'm very happy for you, Charles. Although, I still don't understand you... To hold a priceless rose in your hands and exchange it for... a wildflower. But the heart wants what it wants... Be happy my friend. May you live happily ever after!";
				link.l1 = "In the flower that you hold, the most beautiful thing is your feeling to it. Without it, it's just a lump of fading flesh. Glad you came in, Your Grace.";
				link.l1.go = "FortFrance_Mayor_1";
			}
			else
			{
				dialog.text = "A wonderful day, my friend, and a wonderful occasion! Accept my sincere congratulations! I was married three times, and each time trembled as in the first, ah, youth...";
				link.l1 = "Monsieur, you are still far from old age, don't be discouraged. Thanks for coming, Jacques!";
				link.l1.go = "Guests_block";
			}
		break;
		
		case "FortFrance_Mayor_1":
			dialog.text = "Wait, Charles. You misunderstood me, I am sincerely happy with all my heart! And yes... here, take it. One of our common... Friend, really requested that you get it exactly today.";
			link.l1 = "I suspect that I know from whom it is. Thank you and see you soon.";
			link.l1.go = "Guests_block";
			if (CheckAttribute(pchar, "questTemp.LongHappy.MarrySP"))
			{
				if (CheckAttribute(pchar, "questTemp.GoldenGirl.Julianna_Prisoner"))
				{
					if (CheckAttribute(pchar, "questTemp.GoldenGirl.JulianaSex")) AddQuestRecordInfo("Letter_Marquesa", "2-1");
					else AddQuestRecordInfo("Letter_Marquesa", "1-1");
				}
				else
				{
					if (CheckAttribute(pchar, "questTemp.GoldenGirl.JulianaSex")) AddQuestRecordInfo("Letter_Marquesa", "4-1");
					else AddQuestRecordInfo("Letter_Marquesa", "3-1");
				}
			}
			else
			{
				if (CheckAttribute(pchar, "questTemp.GoldenGirl.Julianna_Prisoner"))
				{
					if (CheckAttribute(pchar, "questTemp.GoldenGirl.JulianaSex")) AddQuestRecordInfo("Letter_Marquesa", "2");
					else AddQuestRecordInfo("Letter_Marquesa", "1");
				}
				else
				{
					if (CheckAttribute(pchar, "questTemp.GoldenGirl.JulianaSex")) AddQuestRecordInfo("Letter_Marquesa", "4");
					else AddQuestRecordInfo("Letter_Marquesa", "3");
				}
			}
		break;
		
		// Бас Тер
		case "BasTer_Mayor":
			dialog.text = "A delightful liturgy, isn't it, Charles? I am sincerely happy for you! From me personally and all the citizens of Basse-Terre - say our congratulations to your... charming wife. You are a wonderful couple! May you live happily ever after!";
			link.l1 = "Thank you, Your Grace. Glad you liked it.";
			link.l1.go = "Guests_block";
		break;
		
		// Порт Принс
		case "PortPax_Mayor":
			dialog.text = "Such a wonderful service, monsieur de Maure, just wonderful! And the bride is so... original in this outfit. On behalf of all the residents of our city - accept my most sincere congratulations! Wishing you many happy years to come!";
			link.l1 = "Thank you, Your Grace.";
			link.l1.go = "Guests_block";
		break;
		
		// Тортуга
		case "Tortuga_Mayor":
			dialog.text = "So cute - you and your bride, monsieur de Maure, looked so unusual! However, you are an unusual person. I wish you a long and happy family life. May you live happily ever after!";
			link.l1 = "I am very grateful to you, Your Grace.";
			link.l1.go = "Guests_block";
		break;
		
		// Дойли
		case "PortRoyal_Mayor":
			dialog.text = "For the sake of your wedding, it was worth crossing the Caribbean! Congratulations, captain, on behalf of the inhabitants of all English colonies! You and your bride, I'm sorry, already a wife, are a wonderful couple!";
			link.l1 = "Thanks for the visit and for the kind words, Colonel!";
			link.l1.go = "Guests_block";
		break;
		
		// Исла Тесоро
		// Тиракс
		case "Terrax":
			if (CheckAttribute(pchar, "questTemp.Mtraxx")) 
			{
				if (pchar.questTemp.Mtraxx == "full_complete_end" || pchar.questTemp.Mtraxx == "full_complete")
				{
					dialog.text = "And what is this married dandy doing on my pirate beach, huh?! Tell me, monsieur, what did you do with my old friend - the harsh captain Charlie Prince?";
					link.l1 = "Charlie Prince is dead, you remember it, Marcus. Ahoy, I'm glad to see you! How are you here, has everyone gathered?";
					link.l1.go = "Terrax_1_1";
				}
				else // 28-03-20
				{
					dialog.text = "And what is this married dandy doing on my pirate beach, huh?! Tell me, monsieur, what did you do with my old friend - the harsh captain Charles de Maure?";
					link.l1 = "Ahoy, Marcus, I'm glad to see you too! How are you here, has everyone gathered?";
					link.l1.go = "Terrax_1";
				}
			}
			else
			{
				dialog.text = "And what is this married dandy doing on my pirate beach, huh?! Tell me, monsieur, what did you do with my old friend - the harsh captain Charles de Maure?";
				link.l1 = "Ahoy, Marcus, I'm glad to see you too! How are you here, has everyone gathered?";
				link.l1.go = "Terrax_1";
			}
		break;
		
		case "Terrax_1":
			dialog.text = "Yes, the Forest Devil arrived just yesterday and immediately started commanding - so the guests are here and everything is ready for the celebration. Your vessel was noticed near the reefs, and guys couldn't stand it - they rushed into the tavern and, most likely, they have already opened that Hawk's barrel. Hurry up, maybe we still have a chance to drink a glass - Nathaniel boasted that this was some kind of special rum!";
			link.l1 = "This how we're doing - from the ship right to the party! I will wait for my best half and we are right behind you, Marcus!";
			link.l1.go = "Terrax_2";
		break;
		
		case "Terrax_1_1":
			dialog.text = "Yes, the Forest Devil arrived just yesterday and immediately started commanding - so the guests are here and everything is ready for the celebration. Your vessel was noticed near the reefs, and guys couldn't stand it - they rushed into the tavern and, most likely, they have already opened that Hawk's barrel. Hurry up, maybe we still have a chance to drink a glass - Nathaniel boasted that this was some kind of special rum!";
			link.l1 = "This how we're doing - from the ship right to the party! I will wait for my best half and we are right behind you, Marcus!";
			link.l1.go = "Terrax_2";
		break;
		
		case "Terrax_2":
			DialogExit();
			DoQuestReloadToLocation("Pirates_tavern", "reload", "reload1", "LongHappy_IslaTesoroTavern");
		break;
		
		case "Terrax_3":
			pchar.questTemp.LongHappy.Count = sti(pchar.questTemp.LongHappy.Count)+1;
			dialog.text = "Married Charles de Maure - still can't get used to it... First, Swanson, now you - then what? Pastor Marlow, or Jacques the Kindman?";
			link.l1 = "You forgot about the Hawks. And what about you, Marcus? Not tired of being a lone sea wolf?";
			link.l1.go = "Terrax_4";
		break;
		
		case "Terrax_4":
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer"))
			{
				dialog.text = "Dannie and Nathan are long-standing case - I have already come to terms with this, but you surprised me, there is nothing to say! However, the pupil of the Forest Devil is beautiful - there is nothing to say, anytime ready to use a word and a gun, and she can handle any storm. It is unlikely that you could find yourself a more worthy couple. You are lucky one, captain - take care of her!";
			}
			else
			{
				dialog.text = "Dannie and Nathan are long-standing case - I have already come to terms with this, but you surprised me, there is nothing to say! Although, as I heard, your Mary knows where the hilt of the saber is - my respect! A true fighting girlfriend. I'll tell you a secret, for the sake of such a girl, I myself could reconsider my convictions as bachelor. You are lucky one, captain - take care of her!";
			}
			link.l1 = "I know, she is a miracle and I am again in seventh heaven with happiness - just like those days when we first met!";
			link.l1.go = "Terrax_5";
		break;
		
		case "Terrax_5":
			dialog.text = "Well, then a toast! For love! But, not for the one that drives us across the threshold and to the horizon, but for the one that is waiting on this threshold. For the love to which we return even from the end of the world and from the golden mountains! Live with it and be happy!!!";
			link.l1 = "Great toast, Marcus, thanks!";
			link.l1.go = "Terrax_6";
		break;
		
		case "Terrax_6_1":
			dialog.text = "Drink to your wedding, buddy!";
			link.l1 = "Thanks, Marcus...";
			link.l1.go = "Terrax_6";
		break;
		
		case "Terrax_6":
			DialogExit();
			npchar.dialog.currentnode = "Terrax_6_1";
			if (!CheckAttribute(pchar, "questTemp.LongHappy.Continue") && sti(pchar.questTemp.LongHappy.Count) >= sti(pchar.questTemp.LongHappy.CountNeed)) LongHappy_IslaTesoroToVine();
		break;
		
		case "Terrax_7":
			dialog.text = "Jacques? This is definitely not good...";
			link.l1 = "Marcus, do you think...";
			link.l1.go = "Terrax_8";
		break;
		
		case "Terrax_8":
			dialog.text = "There's no time! They are behind the doors! Guys, to arms!";
			link.l1 = "Here we go!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LongHappy_TavernFight");
		break;
		
		case "Terrax_9":
			dialog.text = "I don't remember when I last time had such a lot of fun! It's not over yet! Do you hear that? Someone's shooting outside!";
			link.l1 = "Who the hell they are!? And what the fuck they want?!";
			link.l1.go = "Terrax_10";
		break;
		
		case "Terrax_10":
			DialogExit();
			sld = characterFromId("Svenson");
			sld.dialog.currentnode = "Svenson_20";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;

		// Натаниэль Хоук
		case "Nathaniel":
			pchar.questTemp.LongHappy.Count = sti(pchar.questTemp.LongHappy.Count)+1;
			dialog.text = "Married captain de Maure, infrequently I met more sincere reasons for a toast. Raise a glass - this is not an ordinary cabbage drink. It's infused with black tea from East India and seasoned with real Persian spices!";
			link.l1 = "And I've been thinking why it burns in my throat as if I drank molten lead. Well, Nathan, cheer...";
			link.l1.go = "Nathaniel_1";
		break;
		
		case "Nathaniel_1":
			dialog.text = "Wait, first a toast! Hey gentlemen, raise your mugs! Today, our friend and associate Charles de Maure is entering the path of family life. Accept from us the deepest condolen.. oh, Dannie, put down the gun! Congratulations, of course! Now, you are sails of the same ship, so lead her through any storms to the most fertile shores!";
			link.l1 = "Thank you, Nathan, sincerely. You and Danielle are an example for us to follow.";
			link.l1.go = "Nathaniel_2";
		break;
		
		case "Nathaniel_2":
			dialog.text = "Nice to hear. My wife and I may not be the best couple in the world, but we are happy together, and you have done so much for us, so you actually became a member of the family. Be happy, have a drink!";
			link.l1 = "Let's have a drink! Oh… this rum should have its place in the arsenal of the Holy Inquisition.";
			link.l1.go = "Nathaniel_3";
		break;
		
		case "Nathaniel_3":
			DialogExit();
			npchar.dialog.currentnode = "Nathaniel_3_1";
			if (!CheckAttribute(pchar, "questTemp.LongHappy.Continue") && sti(pchar.questTemp.LongHappy.Count) >= sti(pchar.questTemp.LongHappy.CountNeed)) LongHappy_IslaTesoroToVine();
		break;
		
		case "Nathaniel_3_1":
			dialog.text = "You look so much like me and Dannie twenty years ago! Oh!";
			link.l1 = "One more сup, Nathan!";
			link.l1.go = "Nathaniel_3";
		break;
		
		case "Nathaniel_4":
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			dialog.text = "What, Jan sent you into the cellars to bring wine? Let's have a walk, I will help you a bit, and fresh air will be useful.";
			link.l1 = "But where Dannie and "+sld.name+"? Jan told me that they had gone to have a talk.";
			link.l1.go = "Nathaniel_5";
		break;
		
		case "Nathaniel_5":
			dialog.text = "Yes, Dannie knows that presence of even the best girl-in-arms still will not give gentlemen of luck to relax to the fullest. So they listened to all the compliments they received and went to the residence to let the guys have fun.";
			link.l1 = "Well, then move! I managed to drink a couple of mugs, but damn me, now it's really time to get drunk as it should!";
			link.l1.go = "Nathaniel_6";
		break;
		
		case "Nathaniel_6":
			DialogExit();
			LAi_ActorFollowEverywhere(npchar, "", -1);
			chrDisableReloadToLocation = false;//открыть локацию
			bDisableFastReload = true;//закрыть переход
			pchar.quest.longhappy_isla_vine.win_condition.l1 = "location";
			pchar.quest.longhappy_isla_vine.win_condition.l1.location = "Pirates_town";
			pchar.quest.longhappy_isla_vine.function = "LongHappy_IslaTesoroToAlexus";
		break;
		
		case "Nathaniel_7":
			PlaySound("ambient\jail\jail_door2.wav");
			dialog.text = "So, here is the chest. We take as much as we can carry and go back, until this old grouch will lock us here.";
			link.l1 = "You exaggerate, Nathan. He's not so bad... Wait, did you hear that?";
			link.l1.go = "Nathaniel_8";
		break;
		
		case "Nathaniel_8":
			PlaySound("ambient\jail\jail_door2.wav");
			dialog.text = "Jan probably found more guys and sent them to help us. Fuck!";
			link.l1 = "Come on, the bottles break for fortunate. Take one more and let's go.";
			link.l1.go = "Nathaniel_9";
		break;
		
		case "Nathaniel_9":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], true);//запретить драться
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			if (!CheckAttribute(pchar, "questTemp.LongHappy.Tichingitu_Rum") && GetCharacterIndex("Tichingitu") != -1)
			{
				sld = characterFromId("Tichingitu");
				sld.dialog.currentnode = "Tichingitu_8";
				LAi_SetActorType(sld);
				LAi_ActorDialog(sld, pchar, "", -1, 0);
			}
			else LongHappy_SetBandosInDungeon();
		break;
		
		case "Nathaniel_10":
			dialog.text = "What the hell is going on, who are these bastards? Do you understand anything, Charles?";
			link.l1 = "I don't know, Nathan, but one of them has run to bring help, and it seems like I hear more steps. We have to return to the tavern!";
			link.l1.go = "Nathaniel_11";
		break;
		
		case "Nathaniel_11":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			chrDisableReloadToLocation = false;
			pchar.quest.longhappy_totavern.win_condition.l1 = "location";
			pchar.quest.longhappy_totavern.win_condition.l1.location = "Pirates_tavern";
			pchar.quest.longhappy_totavern.function = "LongHappy_TavernAlarm";
		break;
		
		case "Nathaniel_12":
			LongHappy_TownRepose();
			dialog.text = "We put these bastards down, but guns rumble from the sea, do you hear? We've got only two crews ready for battle, on Marcus' frigate and Jan's corvette. Me, Dannie and others have landed our guys - wedding after all - so Сenturion is out. What's about your ship? We have to decide what to do and quickly!";
			link.l1 = "I've landed a half of the crew, I hope the rest half is sober. But first, I have to find my wife and make sure she is okay.";
			link.l1.go = "Nathaniel_13";
		break;
		
		case "Nathaniel_13":
			dialog.text = "Yes, Dannie is also nowhere to be seen. Then we act like this - Tyrex and Swanson have already rushed to the harbor, they will reach their ships on boats. We are going to the residence for the wives, the rest - let them organize defense on the shore. Can you send officers to gather people on your ship? Help there obviously won't hurt.";
			link.l1 = "Go!";
			link.l1.go = "Nathaniel_14";
		break;
		
		case "Nathaniel_14":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			chrDisableReloadToLocation = false;
			LocatorReloadEnterDisable("Pirates_town", "reload3_back", false);
		break;
		
		case "Nathaniel_15":
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			dialog.text = "Faster, upstairs! Dannie and "+sld.name+" must be there! And if this bastards hurt them...";
			link.l1 = "Don't even think about it! Upstairs!";
			link.l1.go = "Nathaniel_16";
		break;
		
		case "Nathaniel_16":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			chrDisableReloadToLocation = false;
			LocatorReloadEnterDisable("Pirates_townhall", "reload1_back", true);
			pchar.quest.longhappy_isla_bedroom.win_condition.l1 = "location";
			pchar.quest.longhappy_isla_bedroom.win_condition.l1.location = "Location_reserve_04";
			pchar.quest.longhappy_isla_bedroom.function = "LongHappy_IslaTesoroBedroom";
		break;
		
		case "Nathaniel_17":
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			dialog.text = "Damn it! Your fellow, he rushed right to the gun so that bastard wouldn’t shoot girls!";
			link.l1 = "And got a bullet. Wait, Nathan... he's breathing! He is still alive! Damn it, I need Gino! "+sld.name+", honey, how are you?";
			link.l1.go = "Nathaniel_18";
		break;
		
		case "Nathaniel_18":
			DialogExit();
			npchar.dialog.currentnode = "Nathaniel_19";
			sld = characterFromId("Danielle");
			sld.dialog.currentnode = "Danielle_7_1";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;
		
		case "Nathaniel_18":
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			dialog.text = "We're fine, Charles! I'm going to untie her. I hear guns in the harbor - you and Nathan need to go there, otherwise Barbazon will destroy all our ships. Don't waste time!";
			link.l1 = "I will find Gino and send him here, he will help ... he must! "+sld.name+", dear, stay here, take a look with Dannie on Tichingitu.";
			link.l1.go = "Nathaniel_19";
		break;
		
		case "Nathaniel_19":
			dialog.text = "Charles, hurry up! whatever you decide, time is now worth its weight in gold! If Jacques' ships break through to the shore, everything will be in vain!";
			link.l1 = "Yes, I know. Fucking bastard!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LongHappy_OutOfBedroom");
		break;
		
		case "Nathaniel_20":
			dialog.text = "Faster, we have no time for talks!";
			link.l1 = "";
			link.l1.go = "Nathaniel_20_1";
		break;
		
		case "Nathaniel_20_1":
			DialogExit();
			npchar.dialog.currentnode = "Nathaniel_20";
		break;
		
		case "Nathaniel_21":
			dialog.text = "Crap! Forgive me Charles. We were stuck upstairs, there was a dozen of these bastards... It’s a pity I didn't get here in time, but I look, you dealt here in the best possible way.";
			link.l1 = "I can't say that it was easy, but, fuck, I received a great pleasure when killed that 'kind man'! It's time to go ashore, Nathan, Our people waiting for us there!";
			link.l1.go = "Nathaniel_22";
		break;
		
		case "Nathaniel_22":
			dialog.text = "Yes, we need to visit your Indian boy, finish here and go to Sharptown.";
			link.l1 = "You are right, I'm behind you.";
			if (CheckAttribute(pchar, "questTemp.LongHappy.Terrax.Prisoner")) link.l1.go = "Nathaniel_23";
			else link.l1.go = "Nathaniel_25";
		break;
		
		case "Nathaniel_23":
			dialog.text = "By the way, we found Marcus! He was in the cargo hold, bound and unconscious.";
			link.l1 = "He's alive?";
			link.l1.go = "Nathaniel_24";
		break;
		
		case "Nathaniel_24":
			dialog.text = "He's in rough shape, but he will be okay. Tyrax is stronger than a nail for a coffin, so don't worry, he has already been transferred to your ship.";
			link.l1 = "Finally, good news! Fine, let's finish here and get back.";
			link.l1.go = "Nathaniel_25";
		break;
		
		case "Nathaniel_25":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "LongHappy_BarbExit", -1);
		break;
		
		// Даниэль Хоук
		case "Danielle":
			dialog.text = "Hello, Charles. Let me look at you - became prettier, nothing to say! Almost like Nathan, about ten years ago! Come in, don't stand on the doorstep, everyone has just been waiting for you!";
			link.l1 = "Thank you, Dannie, I am very glad to see you! I will come to you and Nathan a little later and then we'll talk!";
			link.l1.go = "Danielle_1";
		break;
		
		case "Danielle_1":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocator(npchar, "tables", "stay1", "LongHappy_DannyNorm", -1); 
		break;
		
		case "Danielle_2":
			pchar.questTemp.LongHappy.Count = sti(pchar.questTemp.LongHappy.Count)+1;
			dialog.text = "Charles, take a seat - Nathan and I are so happy for you! Marcus, Jan and my husband have prepared something for you - but gifts will wait. For now, let me congratulate you and wish you happiness! Your chosen one is just a miracle! Tell me, you didn't  manage to get her to wear a white dress there on Martinique, did you?";
			link.l1 = "Thanks, Dannie. Yes, it turned out funny with the dress - I'm sure that in high society our wedding gave rise to many scandalous rumors. Everyone honestly averted their eyes and pretended that nothing out of the ordinary was happening. Manners and all of that kind - but I don't care about gossips, I love her and that's the most important.";
			link.l1.go = "Danielle_3";
		break;
		
		case "Danielle_3":
			dialog.text = "You're absolutely right! I, too, walked to the altar, with a sword and with a pair of pistols behind the sash. But it was in Port Royal, even before it became a dignified colonial residence. There was so much fun in those times, even more than on Tortuga under Levasser and no one was surprised... eh. However, I’m chatting all time - go around the guests, everyone has been waiting for you here, give me only a hug!";
			link.l1 = "Thank you, Dannie, you can't even imagine how me and my wife are glad to see you all!";
			link.l1.go = "Danielle_4";
		break;
		
		case "Danielle_4":
			DialogExit();
			npchar.dialog.currentnode = "Danielle_4_1";
			if (!CheckAttribute(pchar, "questTemp.LongHappy.Continue") && sti(pchar.questTemp.LongHappy.Count) >= sti(pchar.questTemp.LongHappy.CountNeed)) LongHappy_IslaTesoroToVine();
		break;
		
		case "Danielle_4_1":
			dialog.text = "You are a beautiful couple, Charles!";
			link.l1 = "Thanks, Dannie...";
			link.l1.go = "Danielle_4";
		break;
		
		case "Danielle_5":
			dialog.text = "Charles, he's right... you have no choice. I don't believe in the mercy of Jacques the Kindman, if he deals with Tyrax and the rest. You know what to do.";
			link.l1 = "";
			link.l1.go = "Danielle_6";
		break;
		
		case "Danielle_5_1":
			dialog.text = "Don't listen to him! If the Kindman decided to do such madness, he won't spare anyone!";
			link.l1 = "";
			link.l1.go = "Danielle_6_1";
		break;
		
		case "Danielle_6":
			DialogExit();
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			sld.Dialog.currentnode = "LongHappy_39";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;
		
		case "Danielle_6_1":
			DialogExit();
			sld = characterFromId("LH_Dussak");
			sld.dialog.currentnode = "Dussak_5";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;
		
		case "Danielle_7_1":
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			dialog.text = "We're fine, Charles! I will untie her. I hear cannons in the harbor, you and Nathan need to go there, otherwise Barbason will drawn our ships like ducklings in a barrel. You shouldn't lose any minute!";
			link.l1 = "I will find Gino and send him here, he will help ... he must, damn it! "+sld.name+", dear, stay here, look after Tichingitu.";
			link.l1.go = "Danielle_8_1";
		break;
		
		case "Danielle_7":
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			dialog.text = "Nathan, no!!!";
			link.l1 = "He seized the moment and rushed to the gun to cover you, Dannie... "+sld.name+", honey, how are you?";
			link.l1.go = "Danielle_8";
		break;
		
		case "Danielle_8":
			DialogExit();
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			sld.Dialog.currentnode = "LongHappy_41";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;
		
		case "Danielle_8_1":
			DialogExit();
			sld = characterFromId("Nathaniel");
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;
		
		case "Danielle_9":
			dialog.text = "Yes, Charles, he is alive! The heart is barely beating, but he is alive! What should we do?!";
			link.l1 = "We need Gino, immediately! I will find him and send him here, he will help... he must!";
			link.l1.go = "Danielle_10";
		break;
		
		case "Danielle_10":
			dialog.text = "Charles, we have no time! If Jacques' ships break through to the shore, everything will be in vain! My husband ... he did what he had to. Now it is your turn. I will stay with him.";
			link.l1 = "Yes, I know. Fucking bastard!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LongHappy_OutOfBedroom");
		break;
		
		case "Danielle_11":
			dialog.text = "Here you are at last! Is everyone okay?";
			if (CheckAttribute(pchar, "questTemp.LongHappy.Tichingitu_Victim"))
			{
				link.l1 = "We are fine, Dannie, don't worry. Jacques is dead, his ships are at the bottom. How is Nathan?";
				link.l1.go = "Danielle_17";
			}
			else
			{
				link.l1 = "We are fine, Dannie, don't worry. Jacques is dead, his ships are at the bottom. How is Tichingitu?";
				link.l1.go = "Danielle_12";
			}
		break;
		
		case "Danielle_12":
			if (CheckAttribute(pchar, "questTemp.LongHappy.Jino_alive"))
			{
				dialog.text = "He's fine! Your Italian doctor is a genius! Nathan is sleeping upstairs, but, according to Gino, nothing threatens him. A week or two in bed, red wine, and, as he said 'the visit of a lady well disposed to him' ahem... In general - everything is fine, you saved us again, Charles, how can I thank you?";
				link.l1 = "It was Nathaniel who saved my wife and you. And I'll forever owe him for this. You can't even imagine how glad I am to hear that he is recovering. Let him rest, I'll check you back later.";
				link.l1.go = "Danielle_13";
			}
			else
			{
				dialog.text = "He's fine, the bullet passed right through, and our surgeon from 'Centurion' was not far away. He was hiding from all this mess. So Nathan will live, a couple of weeks in bed - little trouble!";
				link.l1 = "Dannie, he covered my wife and you from a bullet and I'll forever owe him for this. You can't even imagine how glad I am to hear that he is recovering. Let him rest, I'll check you back later.";
				link.l1.go = "Danielle_14";
			}
		break;
		
		case "Danielle_13":
			dialog.text = "Of course! But, I must leave you, I have to go to my husband... Don't you mind if we lend your friend? When Nathan gets better, I myself will bring him to Antigua. Centurion somehow miraculously survived, she remains only to recruit a new team.";
			link.l1 = "Fine, Dannie, say hello to Gino and Nathan. I should go.";
			link.l1.go = "Danielle_23";
		break;
		
		case "Danielle_14":
			dialog.text = "Of course, Charles, but... I have bad news. That Italian, Guineili, that was at your wedding... His body was found in a room in the tavern. I'm... I'm sorry, Charles.";
			link.l1 = "What? Gino?! No! How?";
			link.l1.go = "Danielle_15";
		break;
		
		case "Danielle_15":
			dialog.text = "I don’t know, probably one of these bastards that went through the catacombs and attacked the town. Apparently, they were hiding there, looking for a moment to escape, and found him...";
			link.l1 = "Fuck! No, I don't believe it...";
			link.l1.go = "Danielle_16";
		break;
		
		case "Danielle_16":
			pchar.questTemp.LongHappy.Jino_died = "true";
			dialog.text = "I'm sorry, Charles. It was a goddamn bloodbath, and he wasn't a fighter… If you want, we will send his body to your ship, take him home and bury him as it should be. I'm really sorry...";
			link.l1 = "Thanks, Dannie. Give an order to load the body on a ship. I should go now... I need to think. And say hello to Nathan.";
			link.l1.go = "Danielle_23";
		break;
		
		case "Danielle_17":
			if (CheckAttribute(pchar, "questTemp.LongHappy.Jino_alive"))
			{
				dialog.text = "He's fine! Your Italian doctor is a genius! He is sleeping in the room upstairs, and Gino is looking after him. He says 'a week or two and he will be fine'.";
				link.l1 = "Great news! I suppose I can't visit him right now?";
				link.l1.go = "Danielle_18";
			}
			else
			{
				dialog.text = "'m so sorry, Charles. I found our surgeon from the Centurion, but he couldn’t do anything... Your friend died a couple of hours ago.";
				link.l1 = "Tichingitu?! No! I don't believe it!!!";
				link.l1.go = "Danielle_19";
			}
		break;
		
		case "Danielle_18":
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			dialog.text = "No, Italian strictly forbade disturbing him, let him rest, and Gino should rest after all the worries. I even told "+sld.name+" to go out for a walk when we found out that everything was going to be fine\nAnd one more thing... your man, he covered me from the bullet. I don’t even know how to thank him, and you - you saved us again, Charles!";
			link.l1 = "All is well that ends well, Dannie. Go to Nathan, he's been waiting for you, and I will take a little break here and look for my "+sld.name+".";
			link.l1.go = "Danielle_23";
		break;
		
		case "Danielle_19":
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			dialog.text = "Sorry, I did everything I could, and "+sld.name+", too. He covered us from that bullet, and I will never forget that, believe me.";
			link.l1 = "Where's "+sld.name+"? She's fine?";
			link.l1.go = "Danielle_20";
		break;
		
		case "Danielle_20":
			dialog.text = "I can't say so... I mean, physically yes. But… you know… She said she went out for a walk, to keep her mind clear. Probably, she saw you moored and will be back soon.";
			link.l1 = "Curse on you Jacques Barbason... We should've killed him before!";
			link.l1.go = "Danielle_21";
		break;
		
		case "Danielle_21":
			dialog.text = "Wait... that's not all yet. That Italian, Guineili, yes? That quiet young man. He was... his body was found in a tavern... I don’t know, probably one of these bastards who went through the catacombs and attacked the town. Apparently, they were hiding there, looking for a moment to escape, and found him...";
			link.l1 = "And Gino too?! Today is truly a rainy day...";
			link.l1.go = "Danielle_22";
		break;
		
		case "Danielle_22":
			pchar.questTemp.LongHappy.Tichingitu_died = "true";
			dialog.text = "I'm sorry, Charles… If you want, we will send their bodies to your ship, take guys home and bury them as it should be. I'm really sorry...";
			link.l1 = "Thanks Dannie. Do it... I should go… I need to think.";
			link.l1.go = "Danielle_23";
		break;
		
		case "Danielle_23":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload2", "none", "", "", "", 10.0);
			sld = characterFromId("Svenson");
			sld.dialog.currentnode = "Svenson_26";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;
		
		// Додсон
		case "Dodson":
			pchar.questTemp.LongHappy.Count = sti(pchar.questTemp.LongHappy.Count)+1;
			dialog.text = "Charles, can you even imagine how many girls' hearts you broke with this wedding of yours? Yes, half the girls of the archipelago must have mourned after your wedding, haha!";
			link.l1 = "What can I do - I only needed one and I got her. But it's too early for the girls to be upset, because they still have you, Stiven.";
			link.l1.go = "Dodson_1";
		break;
		
		case "Dodson_1":
			dialog.text = "And that is true! We'll finish here and I immediately take care of them, damn it! Come on, Charles, let's drink for your luck and family life. So, as they say, happily ever after!";
			link.l1 = "Happily ever after!";
			link.l1.go = "Dodson_2";
		break;
		
		case "Dodson_2":
			DialogExit();
			npchar.dialog.currentnode = "Dodson_2_1";
			if (!CheckAttribute(pchar, "questTemp.LongHappy.Continue") && sti(pchar.questTemp.LongHappy.Count) >= sti(pchar.questTemp.LongHappy.CountNeed)) LongHappy_IslaTesoroToVine();
		break;
		
		case "Dodson_2_1":
			dialog.text = "To a happy family life, ha-ha!";
			link.l1 = "Great toast!";
			link.l1.go = "Dodson_2";
		break;
		
		// Венсан
		case "Vensan":
			pchar.questTemp.LongHappy.Count = sti(pchar.questTemp.LongHappy.Count)+1;
			dialog.text = "Charles, can you even imagine how many girls' hearts you broke with this wedding of yours? Yes, half the girls of the archipelago must have mourned after your wedding, haha!";
			link.l1 = "What can I do - I only needed one and I got her. But it's too early for the girls to be upset, because they still have you, Bernar.";
			link.l1.go = "Vensan_1";
		break;
		
		case "Vensan_1":
			dialog.text = "And that is true! We'll finish here and I immediately take care of them, damn it! Come on, Charles, let's drink for your luck and family life. So, as they say, happily ever after!";
			link.l1 = "Happily ever after!";
			link.l1.go = "Vensan_2";
		break;
		
		case "Vensan_2":
			DialogExit();
			npchar.dialog.currentnode = "Vensan_2_1";
			if (!CheckAttribute(pchar, "questTemp.LongHappy.Continue") && sti(pchar.questTemp.LongHappy.Count) >= sti(pchar.questTemp.LongHappy.CountNeed)) LongHappy_IslaTesoroToVine();
		break;
		
		case "Vensan_2_1":
			dialog.text = "За счастливую семейную жизнь, ха-ха!";
			link.l1 = "Отличный тост!";
			link.l1.go = "Vensan_2";
		break;
		
		case "Vensan_3":
			pchar.questTemp.LongHappy.Count = sti(pchar.questTemp.LongHappy.Count)+1;
			dialog.text = "Ha, Charles, so you too have become married and boring, like our old Nathan! Hot affairs and everything else are now in the past, huh? Approximate family man!";
			link.l1 = "Keep waiting, Bernard! My wife is not one of those who will have bored sitting under the window of a family wreck! The only thing that will change is the fullness of purses of the brothel girls from here to Curacao!";
			link.l1.go = "Vensan_4";
		break;
		
		case "Vensan_4":
			dialog.text = "Not a big loss, I say! Better to have one gold coin than a bag of nickels. Let's have a drink! Let's cheers to you and your wife! Keep your gold safe and be happy!";
			link.l1 = "Thanks Bernard. Oh, this is really hard rum.";
			link.l1.go = "Vensan_5";
		break;
		
		case "Vensan_5":
			DialogExit();
			npchar.dialog.currentnode = "Vensan_5_1";
			if (!CheckAttribute(pchar, "questTemp.LongHappy.Continue") && sti(pchar.questTemp.LongHappy.Count) >= sti(pchar.questTemp.LongHappy.CountNeed)) LongHappy_IslaTesoroToVine();
		break;
		
		case "Vensan_5_1":
			dialog.text = "To your bride, I mean, already a wife!";
			link.l1 = "Thank you!";
			link.l1.go = "Vensan_5";
		break;
		
		case "Vensan_6":
			dialog.text = "You're just in time, Charles, thanks!";
			link.l1 = "What's the fun here? I thought you were already loading on the ships in the harbor.";
			link.l1.go = "Vensan_7";
		break;
		
		case "Vensan_7":
			dialog.text = "Marcus left me to organize a defense on the shore. We are short of people, guys in the port need gunpowder. Thought I'd drop in, take a couple of barrels ... and then these thugs. Hah, they hid, I guess, wanted to wait out or to rob someone. And I'm still full of Hawk's rum, so without you, I don’t know, would I do it or not.";
			link.l1 = "You're always welcome. Okay, Bernard, I should go, stay safe!";
			link.l1.go = "Vensan_8";
		break;
		
		case "Vensan_8":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "OpenTheDoors", 10.0);
			pchar.questTemp.LongHappy.Vensan_alive = "true";
		break;

		// Джино
		case "Jino":
			pchar.questTemp.LongHappy.Count = sti(pchar.questTemp.LongHappy.Count)+1;
			dialog.text = "Captain, let me heartily congratulate you and your beloved on this auspicious day! Be happy and take care of each other!";
			link.l1 = "Thanks, Gino. I'm glad you decided to come! I hope the local, hm ... color, does not bother you?";
			link.l1.go = "Jino_1";
		break;
		
		case "Jino_1":
			dialog.text = "This is... a very educational trip. I must say - I haven't been out of Antigua for a long time, and in this society it's not easy for me to feel comfortable. But, you always knew how to understand people, so I try to stay calm.";
			link.l1 = "Maybe you need to drink something stronger? Relax and find someone to talk to?";
			link.l1.go = "Jino_2";
		break;
		
		case "Jino_2":
			dialog.text = "Thank you, captain, I've got enough diluted wine. Alcohol, I must warn you, is not very good for the liver and possibly the heart. As for the conversations, I tried to discuss the healing properties of Chirik-Sanango with that gentleman, it is also called Manaka. Maine natives use it...";
			link.l1 = "Let me guess - that gentleman couldn't support the discuss? Gino, for my sake and only today - try the rum that spills Jan over there at the counter. If you can guess all the ingredients, Nathaniel Hawk, over there, will be extremely impressed.";
			link.l1.go = "Jino_3";
		break;
		
		case "Jino_3":
			DialogExit();
			npchar.dialog.currentnode = "Jino_3_1";
			if (CheckAttribute(pchar, "questTemp.LongHappy.MarrySP"))
			{
				if (CheckAttribute(pchar, "questTemp.LongHappy.HambitOfficer"))
				{
					sld = characterFromId(pchar.questTemp.LongHappy.HambitOfficer);
					LAi_SetActorType(sld);
					LAi_ActorDialog(sld, pchar, "", -1, 0);
				}
				else
				{
					if (GetCharacterIndex("Baker") != -1)
					{
						sld = characterFromId("Baker");
						LAi_SetActorType(sld);
						LAi_ActorDialog(sld, pchar, "", -1, 0);
					}
					else
					{
						if (GetCharacterIndex("Tichingitu") != -1)
						{
							sld = characterFromId("Tichingitu");
							LAi_SetActorType(sld);
							LAi_ActorDialog(sld, pchar, "", -1, 0);
						}
						else
						{
							sld = characterFromId("Mary");
							sld.dialog.currentnode = "LongHappy_57";
							LAi_SetActorType(sld);
							LAi_ActorDialog(sld, pchar, "", -1, 0);
						}
					}
				}
			}
			else (!CheckAttribute(pchar, "questTemp.LongHappy.Continue") && sti(pchar.questTemp.LongHappy.Count) >= sti(pchar.questTemp.LongHappy.CountNeed)) LongHappy_IslaTesoroToVine();
		break;
		
		case "Jino_3_1":
			dialog.text = "To your health and the health of your charming spouse!";
			link.l1 = "Thanks, friend!";
			link.l1.go = "Jino_3";
		break;
		
		case "Jino_4":
			dialog.text = "Captain, it's you, thanks God! Those masked people, I saw them and hid here, and they tried to break through the door...";
			link.l1 = "It's okay, Gino, nobody's gonna hurt you anymore. It's a great luck to find you, I need your help. My friend is injured - he has been shot, he has lost a lot of blood.";
			link.l1.go = "Jino_5";
		break;
		
		case "Jino_5":
			dialog.text = "Shot... blood... fine, captain. Going here, I grabbed my camping chest. Lead me to him, I will see what can be done. And these... masked, maybe they have lurked somewhere else?";
			link.l1 = "I'm sure, they were the last. Gino, there's battle in the harbor and I need to go there right now. You have to get to the residence on your own. The big house is around the corner - you won’t miss it. Don't be afraid - the streets are full of our people, and hurry up, I'm begging you!";
			link.l1.go = "Jino_6";
		break;
		
		case "Jino_6":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "OpenTheDoors", 7.0);
			LocatorReloadEnterDisable("Pirates_tavern", "reload1_back", false);
			pchar.questTemp.LongHappy.Jino_alive = "true";
			AddQuestRecord("LongHappy", "18");
			if (CheckAttribute(pchar, "questTemp.LongHappy.Tichingitu_Victim")) sld = characterFromId("Tichingitu");
			else sld = characterFromId("Nathaniel");
			sTemp = sld.name;
			AddQuestUserData("LongHappy", "sName1", sTemp);
		break;
		
		case "Jino_7":
			dialog.text = "Captain, let me heartily congratulate you and your beloved one on this auspicious day! Be happy and take care of each other.";
			link.l1 = "Thanks, Gino. I'm glad you decided to come! I hope the trip went smoothly?";
			link.l1.go = "Jino_8";
		break;
		
		case "Jino_8":
			dialog.text = "Everything is fine, captain, thanks for care. I must say - I haven't been out of Antigua for a long time, and among elite I... don't feel myself comfortable. But the reason to come did not leave me a choice. By the way - the service was excellent, I am very happy for both of you! The bride in this outfit is charming - is this a new fashion? It turns out that I fell behind life in my pharmacy, but I like it, really.";
			link.l1 = "Fashion... In some way yes, or atleast, will become soon. Okay, have fun, Gino, and if the noble interlocutors will become bore for you, then come to the port. The whole crew is in the tavern. Guys will be happy to see you.";
			link.l1.go = "Guests_block";
		break;
		
		case "Jino_9":
			dialog.text = "Captain, Once more, I congratulate you and your beautiful wife! Long and happy years to you together!";
			link.l1 = "Thanks, Gino. I'm glad you came!  I hope the local, hm ... color, does not bother you?";
			link.l1.go = "Jino_10";
		break;
		
		case "Jino_10":
			dialog.text = "This society it's not easy for me to feel comfortable. But, you always knew how to choose people, so I try to stay calm.";
			link.l1 = "Maybe you need to drink something stronger? Relax and find someone to talk to?";
			link.l1.go = "Jino_11";
		break;
		
		case "Jino_11":
			dialog.text = "Thank you, captain, I've got enough diluted wine. Alcohol, I must warn you, is not very good for the liver and possibly the heart. As for the conversations, I tried to discuss the healing properties of Chirik-Sanango with that gentleman, it is also called Manaka. Maine natives use it...";
			link.l1 = "Let me guess - that gentleman couldn't support the discuss? Gino, for my sake and only today - try the rum! And thank you for being with us on this very important day for me and Mary!";
			link.l1.go = "Jino_3";
		break;
		
		// Лонгвэй
		case "Longway":
			pchar.questTemp.LongHappy.Count = sti(pchar.questTemp.LongHappy.Count)+1;
			dialog.text = "'Alone now in a strange country, feeling myself a stranger, on this bright festival day I doubly pine for my kinsfolk'";
			link.l1 = "Longway, never thought you were a master of word!";
			link.l1.go = "Longway_1";
		break;
		
		case "Longway_1":
			dialog.text = "Sorry, Captain, I've been doing a lot of thinking. These are words of Wang Wei - a poet who lived in a period of Tang dynasty which ruled long time ago in my homeland.";
			link.l1 = "These words are so beautiful. I hope one day you'll see your native land again...";
			link.l1.go = "Longway_2";
		break;
		
		case "Longway_2":
			dialog.text = "''Is it possible to vouch and know that under the arch of mysterious slabs of stone it is impossible in trying to make it, to find a passage, beyond which the U-lin valley is located?'\nNo, Captain, you know it - Longway is not going to return home. Now, here is my home and we have a great event here today! I'm sending my best to you and your beautiful bride! Let your happiness be as long as the Yangtze river, studded with diamonds of stars, between the pearls of the lotus.";
			link.l1 = "Thank you my old friend.  Your words are no less beautiful than Wang Wei's.";
			link.l1.go = "Longway_3";
		break;
		
		case "Longway_3":
			dialog.text = "Let's have a drink, Captain! This rum takes away sadness and refreshes joy no worse than maotai.";
			link.l1 = "To your health, Longway!";
			link.l1.go = "Longway_4";
		break;
		
		case "Longway_4":
			DialogExit();
			npchar.dialog.currentnode = "Longway_4_1";
			if (CheckAttribute(pchar, "questTemp.LongHappy.MarrySP"))
			{
				if (GetCharacterIndex("Baker") != -1)
				{
					sld = characterFromId("Baker");
					LAi_SetActorType(sld);
					LAi_ActorDialog(sld, pchar, "", -1, 0);
				}
				else
				{
					if (GetCharacterIndex("Tichingitu") != -1)
					{
						sld = characterFromId("Tichingitu");
						LAi_SetActorType(sld);
						LAi_ActorDialog(sld, pchar, "", -1, 0);
					}
					else
					{
						sld = characterFromId("Mary");
						sld.dialog.currentnode = "LongHappy_57";
						LAi_SetActorType(sld);
						LAi_ActorDialog(sld, pchar, "", -1, 0);
					}
				}
			}
			else 
			{
				if (!CheckAttribute(pchar, "questTemp.LongHappy.Continue") && sti(pchar.questTemp.LongHappy.Count) >= sti(pchar.questTemp.LongHappy.CountNeed)) LongHappy_IslaTesoroToVine();
			}
		break;
		
		case "Longway_4_1":
			dialog.text = "Great wedding, captain!";
			link.l1 = "Drink and have fun!";
			link.l1.go = "Longway_4";
		break;
		
		// Книппель
		case "Knippel":
			pchar.questTemp.LongHappy.Count = sti(pchar.questTemp.LongHappy.Count)+1;
			if (CheckAttribute(pchar, "questTemp.LongHappy.MarrySP"))
			{
				dialog.text = "Hit me a chain-shot! All our guys congratulate you! How did the serve go?";
				link.l1 = "Everything is fine, Charlie! now I am officially married and respectable, and my first assistant is madame de Monper now.";
			}
			else
			{
				dialog.text = "Hit me with a chain shot, such an event, captain! Almost every baron of the Brethren here! I guess, every spanish puritan imagines the Hell like this! And rum, it is something special, chain shot to my barrel!";
				link.l1 = "Yup, people here are not the most law-abiding, but we ourselves are not angels, Charlie, and each of these people is dear to me in his own way.";
			}
			link.l1.go = "Knippel_1";
		break;
		
		case "Knippel_1":
			if (CheckAttribute(pchar, "questTemp.LongHappy.MarrySP"))
			{
				dialog.text = "It's wonderful, chain-shot to my butt! Captain, I mean, this celebarion is in your honor, well, I... I, congratulate, Il mean... also... Happiness and... this, I am not goodin speeches. But you must know that we all love both of you and will follow you even to hell.";
				link.l1 = "Thank you, old friend.";
			}
			else
			{
				dialog.text = "Wait, I mean... What do I even mean, chain shot to my butt?! Captain, I mean that this day is in your honor, well, I... I congratulate you, in outline... also... I wish you happiness and... oh, I am not good in speeches.";
				link.l1 = "Thank you, old friend.";
			}
			link.l1.go = "Knippel_2";
		break;
		
		case "Knippel_2":
			Log_Info("You have got gems");
			PlaySound("interface\important_item.wav");
			TakeNItems(pchar, "jewelry4", 20);
			dialog.text = "And yes, captain, accept this, please. For you and your sweetheart. I've kept these stones for a rainy day ... I understand that you have no shortage of gold, but they will not be superfluous, right?";
			link.l1 = "Charlie, you are truly a generous soul, and these emeralds will look great in madame de Monper's family earrings!";
			link.l1.go = "Knippel_3";
		break;
		
		case "Knippel_3":
			dialog.text = "Well, let's cheer to this, chain shot to my… hm. Just be happy, you and your beauty, captain!";
			link.l1 = "We will, Charlie!";
			link.l1.go = "Knippel_4";
		break;
		
		case "Knippel_4":
			DialogExit();
			npchar.dialog.currentnode = "Knippel_4_1";
			if (CheckAttribute(pchar, "questTemp.LongHappy.MarrySP"))
			{
				if (GetCharacterIndex("Baker") != -1)
				{
					sld = characterFromId("Baker");
					LAi_SetActorType(sld);
					LAi_ActorDialog(sld, pchar, "", -1, 0);
				}
				else
				{
					if (GetCharacterIndex("Tichingitu") != -1)
					{
						sld = characterFromId("Tichingitu");
						LAi_SetActorType(sld);
						LAi_ActorDialog(sld, pchar, "", -1, 0);
					}
					else
					{
						sld = characterFromId("Mary");
						sld.dialog.currentnode = "LongHappy_57";
						LAi_SetActorType(sld);
						LAi_ActorDialog(sld, pchar, "", -1, 0);
					}
				}
			}
			else 
			{
				if (!CheckAttribute(pchar, "questTemp.LongHappy.Continue") && sti(pchar.questTemp.LongHappy.Count) >= sti(pchar.questTemp.LongHappy.CountNeed)) LongHappy_IslaTesoroToVine();
			}
		break;
		
		case "Knippel_4_1":
			dialog.text = "Great wedding, captain!";
			link.l1 = "Drink and have fun!";
			link.l1.go = "Knippel_4";
		break;
		
		// Тонзаг
		case "Tonzag":
			pchar.questTemp.LongHappy.Count = sti(pchar.questTemp.LongHappy.Count)+1;
			dialog.text = "I never thought, captain, that I would see you married. Usually, the path that we have chosen leads along a lonely path right into a lonely grave. In my memory, you are the first who managed to get off of it. It's worth the extra toast, isn't it?";
			link.l1 = "This is it, buddy! And truly, I'm glad that this part of my life has left behind. Cheers!";
			link.l1.go = "Tonzag_1";
		break;
		
		case "Tonzag_1":
			dialog.text = "Cheers to you and your long and happy life together! Damn, looking at you, I recall that I myself was once married.";
			link.l1 = "You? Married? Surprisingly! But what happened?";
			link.l1.go = "Tonzag_2";
		break;
		
		case "Tonzag_2":
			dialog.text = "What, do you think I was always an old cyclop smelling with gunpowder and blood, yup captain? But no. Madame Tonzag... she loved me, I guess. But then, an unpleasant story happened. In which the Tonzag couple died and only Bald Gaston with set of scars managed to survive.";
			link.l1 = "Sorry, Hercule, I didn't know...";
			link.l1.go = "Tonzag_3";
		break;
		
		case "Tonzag_3":
			dialog.text = "Forget it, captain, that story happened long time ago. But now, looking at you, I think that my story still can have a good end. So, let us drink for it!";
			link.l1 = "Let us, buddy. Happiness to everyone and wish that no one will be left out.";
			link.l1.go = "Tonzag_4";
		break;
		
		case "Tonzag_4":
			DialogExit();
			npchar.dialog.currentnode = "Tonzag_4_1";
			if (CheckAttribute(pchar, "questTemp.LongHappy.MarrySP"))
			{
				if (GetCharacterIndex("Baker") != -1)
				{
					sld = characterFromId("Baker");
					LAi_SetActorType(sld);
					LAi_ActorDialog(sld, pchar, "", -1, 0);
				}
				else
				{
					if (GetCharacterIndex("Tichingitu") != -1)
					{
						sld = characterFromId("Tichingitu");
						LAi_SetActorType(sld);
						LAi_ActorDialog(sld, pchar, "", -1, 0);
					}
					else
					{
						sld = characterFromId("Mary");
						sld.dialog.currentnode = "LongHappy_57";
						LAi_SetActorType(sld);
						LAi_ActorDialog(sld, pchar, "", -1, 0);
					}
				}
			}
			else 
			{
				if (!CheckAttribute(pchar, "questTemp.LongHappy.Continue") && sti(pchar.questTemp.LongHappy.Count) >= sti(pchar.questTemp.LongHappy.CountNeed)) LongHappy_IslaTesoroToVine();
			}
		break;
		
		case "Tonzag_4_1":
			dialog.text = "Великолепное торжество, капитан!";
			link.l1 = "Пей и веселись вволю!";
			link.l1.go = "Tonzag_4";
		break;
		
		// Бейкер
		case "Baker":
			pchar.questTemp.LongHappy.Count = sti(pchar.questTemp.LongHappy.Count)+1;
			dialog.text = "Here's our captain! Congratulations, you and your wife are a beautiful couple! May you live happily ever after!";
			link.l1 = "Thank you, Raymond.";
			link.l1.go = "Baker_1";
		break;
		
		case "Baker_1":
			sTemp = "Sharptown";
			if (CheckAttribute(pchar, "questTemp.LongHappy.MarrySP")) sTemp = "Sent Pierre";
			dialog.text = "Looks like you are too sober for your own wedding, captain. Would you like to fix it? I've taken a bottle of excellent sherry at the bar. The mix with local rum goes just fine!";
			link.l1 = "I'd like to, but someone has to keep an eye on things here. Otherwise, in "+sTemp+" not only tavern will be missed when the morning comes.";
			link.l1.go = "Baker_2";
		break;
		
		case "Baker_2":
			DialogExit();
			npchar.dialog.currentnode = "Baker_2_1";
			if (CheckAttribute(pchar, "questTemp.LongHappy.MarrySP"))
			{
				if (GetCharacterIndex("Tichingitu") != -1)
				{
					sld = characterFromId("Tichingitu");
					LAi_SetActorType(sld);
					LAi_ActorDialog(sld, pchar, "", -1, 0);
				}
				else
				{
					sld = characterFromId("Mary");
					sld.dialog.currentnode = "LongHappy_57";
					LAi_SetActorType(sld);
					LAi_ActorDialog(sld, pchar, "", -1, 0);
				}
			}
			else 
			{
				if (!CheckAttribute(pchar, "questTemp.LongHappy.Continue") && sti(pchar.questTemp.LongHappy.Count) >= sti(pchar.questTemp.LongHappy.CountNeed)) LongHappy_IslaTesoroToVine();
			}
		break;
		
		case "Baker_2_1":
			dialog.text = "Excellent food and excellent rum, captain! Cheers to you and your young wife!";
			link.l1 = "Thanks!";
			link.l1.go = "Baker_2";
		break;
		
		// Алексус
		case "Alexus":
			dialog.text = "Young people, where are you breaking in, may I ask? The shipyard is closed, isn't it noticeable? Come back tomorrow.";
			link.l1 = "Master, I'm sorry for bothering you, we’ll just go through the dungeons. There are supplies for the wedding, the tavern is almost out of drinks.";
			link.l1.go = "Alexus_1";
		break;
		
		case "Alexus_1":
			dialog.text = "Oh, Charles de Maure and Nathan Hawk themselves! You kind of celebrate someone's wedding, right? Fine - go get your fuel. Young people should have fun - this is the law at any time. Just don't rattle the bottles on the way back - I'm going to sleep!";
			link.l1 = "Thank you, master, we're light-speed.";
			link.l1.go = "Alexus_2";
		break;
		
		case "Alexus_2":
			DialogExit();
			npchar.dialog.currentnode = "Alexus_2_1";
			LocatorReloadEnterDisable("Pirates_Shipyard", "reload2", false);
			pchar.GenQuestBox.Bermudes_Dungeon = true;
			pchar.GenQuestBox.Bermudes_Dungeon.box3.items.potionwine = 100;
			pchar.quest.longhappy_isla_box.win_condition.l1 = "locator";
			pchar.quest.longhappy_isla_box.win_condition.l1.location = "Bermudes_Dungeon";
			pchar.quest.longhappy_isla_box.win_condition.l1.locator_group = "box";
			pchar.quest.longhappy_isla_box.win_condition.l1.locator = "box3";
			pchar.quest.longhappy_isla_box.function = "LongHappy_IslaTesoroDungeon";
		break;
		
		case "Alexus_2_1":
			dialog.text = "C'mon, don't stand, go!Ну как, капитан, вы всем довольны? Отбор";
			link.l1 = "...";
			link.l1.go = "Alexus_2_2";
		break;
		
		case "Alexus_2_2":
			DialogExit();
			npchar.dialog.currentnode = "Alexus_2_1";
		break;
		
		// пиратус в подземелье
		case "DungeonPirate":
			dialog.text = "What the fuck?! Jacques said 'No one comes down here'! Hugo - run back, call the others, we will clear the way. Kill them guys!";
			link.l1 = "Shit!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LongHappy_BandosInDungeonFight");
		break;
		
		// киллеры
		case "killer":
			dialog.text = "Lads, forget about chests, we've got guests!";
			link.l1 = "I thought bastards like you had been killed with Jackman. Fine, let's finish this!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LongHappy_ResidenceFight");
		break;
		
		case "killer_1":
			dialog.text = "Fuck... We've been found! Alarm!";
			link.l1 = "Get out of my way, asshole!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LongHappy_TavernKillerFight");
		break;
		
		// Ангерран
		case "Shivo":
			dialog.text = "Monsieur de Maure, good evening, or is it almost morning already? Come in, have a seat.";
			link.l1 = "Angerran De Chievous! That's who I am not surprised to see! The insignificance, capable of fighting only with women! You also tied them up?! Now I'm going to finish what I started in that duel on Martinique!";
			link.l1.go = "Shivo_1";
		break;
		
		case "Shivo_1":
			dialog.text = "Calm down, young man, see this gun? There are two trunks. Maybe I’m bad in fencing, but I’m shooting quite accurately - put down your sword, or you will miss a couple of beautiful ladies, I assure you.";
			link.l1 = "Bastard... Damn you.";
			link.l1.go = "Shivo_2";
		break;
		
		case "Shivo_2":
			dialog.text = "And you, monsieur pirate, put down your weapon too, just like that, yes. And now - sit down, you can pour the wine - over there on the table. We will have to wait a bit until monsieur Barbazon finishes smashing the ships of your friends, the pirate barons. Then we’ll decide how you and I will settle our... hm, disagreements.";
			link.l1 = "Settle disagreements? And how? Do you want a duel?";
			link.l1.go = "Shivo_3";
		break;
		
		case "Shivo_3":
			dialog.text = "Don't be so funny, Charles. You and madame Botot have caused me a lot of troubles, and I intend to repay you in full. If you and the imposing monsieur pirate will sit quietly, then I give you a word of honor - your wives will stay alive. I think in the Spanish colonies on Maine such slaves are valued. Even unofficially. But this is still life, isn't it?";
			link.l1 = "Angerran, you are a coward, a bastard and ... Shit, there are no suitable words for you yet in any language!";
			link.l1.go = "Shivo_4";
		break;
		
		case "Shivo_4":
			dialog.text = "You know it, you have no choice. I can only promise that it will be fast. So, if you love these women - behave yourself, save their lives and ease your fate. And yes - lock the door if it doesn't hard for you. Thanks.";
			link.l1 = "";
			link.l1.go = "Shivo_5";
		break;
		
		case "Shivo_5":
			DialogExit();
			sld = characterFromId("Danielle");
			sld.dialog.currentnode = "Danielle_5";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;
		
		case "Shivo_6":
			dialog.text = "Such a warlike ladies. I will still ask you to be prudent. Never loved to kill women.";
			link.l1 = "";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LongHappy_BedroomShot");
		break;
		
		case "Shivo_7":
			dialog.text = "Fuck...";
			link.l1 = "Die bastard!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LongHappy_BedroomFight");
		break;
		
		// Дюссак
		case "Dussak":
			dialog.text = "Captain Charles de Maure, baron Hawk - what a pleasant surprise! Let me introduce myself - Mauritz Dussak, that's my name.";
			link.l1 = "Get out of my way, bastard! Where is my wife?!";
			link.l1.go = "Dussak_1";
		break;
		
		case "Dussak_1":
			dialog.text = "Calm down, gentlemen! See this gun? There are two trunks. I was nicknamed like that for a reason - I love sabers, sure... but I also shoot well, believe me. Lay down your swords, or you'll miss a couple of your ladies!";
			link.l1 = "I'm gonna slaughter you like a pig, scum...";
			link.l1.go = "Dussak_2";
		break;
		
		case "Dussak_2":
			dialog.text = "But you will already be a widower. Don't you want it? Then calm down and lay down your weapon. Baron Hawk, please, lock the door. And we will calm down and wait a bit while Jacques Barbazon there in the harbor will finish the leaders of the Brethren.";
			link.l1 = "And what's next? We'll hug and go to sunset together?";
			link.l1.go = "Dussak_3";
		break;
		
		case "Dussak_3":
			dialog.text = "I don't think so. For your captivity, Jacques will shower me with gold, with luck, maybe, I will become a baron. Regarding your women, maybe we will let them go, but regarding you - alas ... If you're lucky, I will ask for the right to kill you personally, captain. You are a famous fencer - it would be interesting to test you. You know, I also consider myself a master.";
			link.l1 = "A master of breaking into houses at night and tie half-asleep women? You are a worm, moreover - a funky worm!";
			link.l1.go = "Dussak_4";
		break;
		
		case "Dussak_4":
			DialogExit();
			sld = characterFromId("Danielle");
			sld.dialog.currentnode = "Danielle_5";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;
		
		case "Dussak_5":
			dialog.text = "Listen, madame, I've never killed women, don't make me start, okay? You are unnerving the captain and your husband... Damn!";
			link.l1 = "";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LongHappy_BedroomShot");
		break;
		
		case "Dussak_6":
			dialog.text = "Merdo...";
			link.l1 = "Die bastard!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LongHappy_BedroomFight");
		break;
		
		// Барбазон
		case "Barbazon_boarding":
			dialog.text = "Fucking frenchman, wasn't there any sabre or a bullet?!";
			link.l1 = "You know, Jacques, I have both for you. Honestly, I almost regret that I left you alive when I found out about your tricks with Jackman. But, now I am going to fix it.";
			link.l1.go = "Barbazon_boarding_1";
		break;
		
		case "Barbazon_boarding_1":
			dialog.text = "You're so brave only when you walk with a crowd of your guys? Let's change the situation! I'll deal with the barons later, but you won’t get out of here alive, rat!";
			link.l1 = "Expected...";
			link.l1.go = "Barbazon_boarding_2";
		break;
		
		case "Barbazon_boarding_2":
			DialogExit();
			LAi_SetCurHPMax(npchar);
			AddItems(npchar, "potion2", 1);
			QuestAboardCabinDialogFree();
			LAi_group_SetRelation(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck(LAI_GROUP_BRDENEMY, "LongHappy_BarbAfterFight");
			AddDialogExitQuest("MainHeroFightModeOn");
			// подкрепление
			sld = GetCharacter(NPC_GenerateCharacter("LH_BarbCabinHelper", "citiz_57", "man", "man", 35, PIRATE, 0, true, "quest"));
			FantomMakeCoolFighter(sld, 35, 70, 70, "blade_21", "pistol4", "bullet", 300);
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, LAI_GROUP_BRDENEMY);
			ChangeCharacterAddressGroup(sld, pchar.location, "reload", "reload1");
			AddItems(sld, "potion2", 2);
		break;
		
		// официантка
		case "waitress":
			dialog.text = "Captain, help, this savage, he abducted me! I... I need to go home - uncle probably already turn the whole town upside down!";
			link.l1 = "Calm down, beauty, everything will be fine. Step aside, I need to talk with your 'savage'.";
			link.l1.go = "waitress_1a";
		break;
		
		case "waitress_1a":
			DialogExit();
			sld = characterFromId("Tichingitu");
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "waitress_1":
			dialog.text = "Thank you, captain! You saved me! When I've woken up this morning on this beach, I... can't believe that I was going to marry this savage, he...";
			if (GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) > 94)
			{
				link.l1 = "Yes, morning is a stern hammer for the night's crystal of hope. Understand. But he is from the Muscogue tribe, and lives according to the harsh laws of his land. He stole you with your consent, and you spent the night together. So now, in the eyes of his Gods, you are husband and wife. Let's go and pack your things, and I'll settle the ransom issue with your uncle.";
				link.l1.go = "waitress_2";
			}
			link.l2 = "I'm sorry for this. Tichingitu lives by laws of his tribe, but he is a good person. Please, forget this abduction story.";
			link.l2.go = "waitress_5";
		break;
		
		case "waitress_2":
			dialog.text = "Wife? In the eyes of his Gods?! No, captain, I beg you, save me from this! It was just... an adventure, he was so gallant, not like these bumpkins... But marry? I am too young to move to a hut to a savage!";
			link.l1 = "He is my officer, so don't worry, I paid him well, and you will have the best hut you ever wanted. Tichingitu is a good hunter, he will procure food for you, and you will give birth and babysit children.";
			link.l1.go = "waitress_3";
		break;
		
		case "waitress_3":
			dialog.text = "Children? Procure food?! No captain, please don't do this to me, I beg you!";
			link.l1 = "Well, maybe I can convince him. But it won't be easy. Muskogue tribe is very serious about such things, if someone finds out that he stole a squaw and didn't get married...";
			link.l1.go = "waitress_4";
		break;
		
		case "waitress_4":
			dialog.text = "You have to try, please! I won’t tell anyone, no one will know! I'll lie to uncle, it's not for the first time!";
			link.l1 = "Okay, you should go, beauty squaw. I will try to keep my friend away.";
			link.l1.go = "waitress_7";
		break;
		
		case "waitress_5":
			dialog.text = "He stole me like... like a goat from a barn! I will tell everyone! Uncle will kill him! He is terrible in anger! He used to rob Spanish ships - jokes are bad with him!";
			link.l1 = "Alright, hush, beautiful lady, hush. Maybe twenty thousand 'reasons' to forgive him will be more eloquent than my words? Or should I give them to your uncle, like a ransom for a wife? After all, there are priests on the island, right? Tomorrow we'll organize a wedding... one more.";
			link.l1.go = "waitress_6";
		break;
		
		case "waitress_6":
			if (sti(Pchar.money) >= 20000) AddMoneyToCharacter(pchar, -20000); 
			dialog.text = "No no, captain, wait! You convinced me. I’ll come up with something so my uncle isn't angry. Farewell! And goodbye, my stallion from the distant plains!";
			link.l1 = "That's right. Glad we agreed. Run home, beauty.";
			link.l1.go = "waitress_7";
		break;
		
		case "waitress_7":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload4_back", "none", "", "", "", 10.0);
			npchar.lifeday = 0;
			sld = characterFromId("Tichingitu");
			sld.dialog.currentnode = "Tichingitu_16";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		// тавернщик Сен Пьер
		case "tavernkeeper":
			dialog.text = "Well, Captain, are you happy with everything? The finest rum, lamb ribs, pork hams and even excellent wine from my personal stocks for your scientist friend! And - my congratulations to you and your beautiful wife!";
			link.l1 = "Thanks! I must admit, you organized everything perfectly. I hope you have enough rum stocks in your cellars, morning is far.";
			link.l1.go = "tavernkeeper_1";
		break;
		
		case "tavernkeeper_1":
			dialog.text = "Don't worry about this, if the barrels show the bottom, I will send an assistant to the port warehouse. Have fun, monsignor, and don't worry about anything.";
			link.l1 = "Okay, "+npchar.name+". Then I will go to my guests.";
			link.l1.go = "tavernkeeper_2";
		break;
		
		case "tavernkeeper_2":
			DialogExit();
			npchar.dialog.currentnode = "tavernkeeper_3";
		break;
		
		case "tavernkeeper_3":
			dialog.text = "What do you wish, captain? Fried ribs, smoked ham or brisket? Maybe wine for your better half?";
			link.l1 = "";
			link.l1.go = "tavernkeeper_2";
		break;
		
		// моряки в таверне Сен Пьер
		case "sailor":
			dialog.text = RandPhraseSimple(LinkRandPhrase("To the health of the captain and his wife!","May you live happily ever after, captain!","Long life and happiness to you both!"), LinkRandPhrase("Hooray to the captain and his beauty!","May luck follow the captain and his spouse their whole life!","Fair wind to your family life, cap!"));
			link.l1 = LinkRandPhrase("Thanks!","Thank you!","Cheers!");
			link.l1.go = "sailor_1";
		break;
		
		case "sailor_1":
			DialogExit();
			npchar.dialog.currentnode = "sailor";
		break;
		
		// босс Ле Франсуа
		case "JanDavid":
			if (sti(pchar.GenQuest.Piratekill) > 20)
			{
				dialog.text = RandPhraseSimple("Are you insane? Wanted to play a butcher? All pirates are angry with you, pal, so you'd better leave this place.", "It seems, pal, that you got mad. Wanted to stretch your hands a bit? No offence, but you have nothing to do here. Get lost!");
				link.l1 = RandPhraseSimple("Listen, I want to fix the situation...", "Help me to solve the problem...");
				link.l1.go = "pirate_town";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.LongHappy.Baron"))
			{
				if (!CheckAttribute(npchar, "quest.Baron"))
				{
					dialog.text = "Ah, I've been waiting for your visit, boss. Jan Swanson warned that you would definitely come to check how things are going in Le Francois. I took everything into my own hands and swear by thunder, this village will live better than with the damned Kindman, may the devils  have fun on him in the darkest cellars of hell!";
					link.l1 = "You are Jean David, right? Swanson said something about my share...";
					link.l1.go = "JanDavid_2";
				}
				else
				{
					dialog.text = TimeGreeting()+" boss. Everything is fine in Le Francois, as always. Why have you come? Can I help you with something?";
					link.l1 = "Just dropped by to check how things are going.";
					link.l1.go = "JanDavid_1";
					if (sti(pchar.questTemp.LongHappy.BaronMoney) > 0)
					{
						link.l2 = "What about my share?";
						link.l2.go = "JanDavid_5";
					}
				}
			}
			else
			{
				dialog.text = TimeGreeting()+" buddy.Why have you come? Can I help you with something?";
				link.l1 = "Just dropped by to say hello.";
				link.l1.go = "JanDavid_1";
			}
		break;
		
		case "JanDavid_1":
			DialogExit();
			npchar.dialog.currentnode = "JanDavid";
		break;
		
		case "JanDavid_2":
			npchar.quest.Baron = "true";
			dialog.text = "At your service, boss! As for the share - on the fifth of every month, you will be deducted a part of the gold coins from the deeds of our guys, and it'll wait for you as much as you need. Since next month you can come for it.";
			link.l1 = "Nice!";
			link.l1.go = "JanDavid_3";
		break;
		
		case "JanDavid_3":
			dialog.text = "And I'll take care of the rest. The Forest Devil said that you wouldn't have the time to engage in such small things as Le Francois...";
			link.l1 = "You was told correctly. Okay, Jean, I rely on you, I hope you won't let me down.";
			link.l1.go = "JanDavid_4";
		break;
		
		case "JanDavid_4":
			dialog.text = "Be calm, boss. Everything is under control here, ha-ha, and may I not to drink rum until the end of days!";
			link.l1 = "Fine, see you!";
			link.l1.go = "JanDavid_1";
			// запуск отчисления доли
			pchar.questTemp.LongHappy.BaronPart = "true";
			pchar.questTemp.LongHappy.BaronMoney = 0;
		break;
		
		case "JanDavid_5":
			dialog.text = "Waiting for you, boss. During this time we have collected for you "+FindRussianMoneyString(sti(pchar.questTemp.LongHappy.BaronMoney))+". Take it.";
			link.l1 = "Ha, not bad. Well done, Jean.";
			link.l1.go = "JanDavid_6";
		break;
		
		case "JanDavid_6":
			AddMoneyToCharacter(pchar, sti(pchar.questTemp.LongHappy.BaronMoney));
			pchar.questTemp.LongHappy.BaronMoney = 0;
			dialog.text = "I do my best, boss. Come back next month or whenever you want - your money will be safe with me.";
			link.l1 = "Fine, see you, Jean.";
			link.l1.go = "JanDavid_1";
		break;
		
		case "pirate_town":
             dialog.text = "Solve the problem? Do you have any idea what you have done? Anyway, bring me a million pesos and I will persuade lads to forget your deed. If don't like the idea then you may go to hell.";
			if (sti(Pchar.money) >= 1000000)
			{
				link.l1 = "Fine, I am ready to pay.";
				link.l1.go = "pirate_town_pay";
			}
			link.l2 = "Got it. I am leaving.";
			link.l2.go = "pirate_town_exit";
		break;
		
		case "pirate_town_exit":
			DialogExit();
            bDisableFastReload = true;//закрыть переход
			pchar.quest.pirate_in_town.win_condition.l1 = "ExitFromLocation";
			pchar.quest.pirate_in_town.win_condition.l1.location = pchar.location;
			pchar.quest.pirate_in_town.function = "TownPirate_battle";
		break;
		
		case "pirate_town_pay":
            dialog.text = "Good! Consider yourself clean again. But I hope that you will not do such disgusting things again.";
			link.l1 = "I won't. Way too expensive for me. Farewell...";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, -1000000);
			pchar.GenQuest.Piratekill = 0;
		break;
	}
} 
