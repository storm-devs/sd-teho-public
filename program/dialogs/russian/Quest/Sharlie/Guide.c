// гид
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
			link.l1 = "No, nothing.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		case "guide_0":
			dialog.text = "Welcome to the colonies, monsieur! Let me introduce myself, I am "+GetFullName(npchar)+". You are a newcomer, right?";
			link.l1 = "Greeting, monsieur. My name is "+GetFullName(pchar)+". Yes, I am just off the ship. I don't recognize you... Do I know you?";
			link.l1.go = "guide_1";			
		break;
		
		case "guide_1":
			dialog.text = "No, monsieur, you don't. Though, I couldn't miss an opportunity to introduce myself to a nobleman like you\nOh, I remember my first day, the day of my arrival to the New World. Things are different here and the local lifestyle may damage your health and your wallet\nThat's why I offer you my modest help. Free of charge, which is rare here, ha-ha. I can make you a bit more familiar with our colony and the archipelago. Consider it as a little presentation.";
			link.l1 = "That's very kind of you, monsieur! Sure, I'd be glad to accept your offer. Knowledge is power.";
			link.l1.go = "guide_2";
			link.l2 = "I appreciate your offer, monsieur, I really do, but I'll pass.";
			link.l2.go = "guide_exit";	
		break;
		
		case "guide_exit":
			dialog.text = "As you wish, monsieur. Anyway, nice to meet you. Honourable people are rare guests here. I wish you luck!";
			link.l1 = "You too, "+GetFullName(npchar)+"!";
			link.l1.go = "guide_exit_1";			
		break;
		
		case "guide_exit_1":
			DialogExit();
			LAi_SetCitizenType(npchar);
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeday = 0;
		break;
		
		case "guide_2":
			dialog.text = "Glad to hear it. My pleasure. Well, let me tell you some basics. Most of colonies were built in the same manner: a settlement on the shore protected by a fort and walls with gates. Nobles, rich folks, soldiers, sailors, merchants, mercenaries and criminals - all of them live together\nSometimes you'll meet captains, monks, gypsies and beggars. You won't find any Indians on the streets though, people don't feel comfortable about their presence. Follow me, I will show you local establishments.";
			link.l1 = "";
			link.l1.go = "guide_3";			
		break;
		
		case "guide_3": // идем в таверну
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_SetActorType(pchar);
			LAi_ActorGoToLocator(npchar, "officers", "reload4_3", "Guide_tavern", -1);
			LAi_ActorFollow(pchar, npchar, "", -1);
			chrDisableReloadToLocation = true;//закрыть локацию
		break;
		
		case "guide_4":
			dialog.text = "So, this is the most important place in any colony - a tavern. Yes, in Europe such place may be considered a den of thieves, but everything is opposite here. A bartender can offer you a room to sleep, some rum, juicy gossips and a job\nIf you seek any information, try talking with people there. Buy a drink to a drunkard and you may get something interesting in return. Gambling is a popular way of entertainment here, but beware of cheaters. If you catch someone on cheating don't hesitate to kill. Nobody will judge you for that\nA tavern is also a place where you can hire crew and officers for your ship, in case you own one. Remember: information, job, crew, entertainment.";
			link.l1 = "";
			link.l1.go = "guide_5";
		break;
		
		case "guide_5": // к магазину
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_SetActorType(pchar);
			LAi_ActorGoToLocator(npchar, "officers", "reload6_3", "Guide_store", -1);
			LAi_ActorFollow(pchar, npchar, "", -1);
		break;
		
		case "guide_6":
			dialog.text = "A store is a trading centre of any colony. Captains visit this place as often as a shipyard. You can always purchase here munitions, supplies or goods to trade. Commerce is quite tricky\nFirst, it takes time to find the best places where to buy or to sell. Second, you need some decent skills in trading to compete with local merchants\nThat is why most of captains hire pursers to do business instead of themselves. So don't forget to hire such professional when... if you will get a ship of your own. This is critical, you don't want to waste a shitload of money without a purpose in this cruel world. One last thing. Merchants in stores often propose beneficial freight contracts, you may find this useful in the future.";
			link.l1 = "";
			link.l1.go = "guide_7";
		break;
		
		case "guide_7": // к тюрьме
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_SetActorType(pchar);
			LAi_ActorGoToLocator(npchar, "reload", "reload_jail", "Guide_prison", -1);
			LAi_ActorFollow(pchar, npchar, "", -1);
		break;
		
		case "guide_8":
			dialog.text = "And this is a prison. Filthy place. Real criminals end up into the noose fast, so they keep mostly little fish inside\nIf you want to chat with them - address to a guard officer. He will allow you to see the insides for a small fee or even for free in case you are persuasive enough. It may prove useful, but remember that lowlifes can not be trusted, though they always talk sweet when they are caged.";
			link.l1 = "";
			link.l1.go = "guide_9";
		break;
		
		case "guide_9": // на рынок
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_SetActorType(pchar);
			LAi_ActorGoToLocator(npchar, "merchant", "mrcActive4", "Guide_market", -1);
			LAi_ActorFollow(pchar, npchar, "", -1);
		break;
		
		case "guide_10":
			dialog.text = "Marketplace. Traders sell and buy everything you need. An armourer can provide you with blades, firearms, armours, munitions and so on. Good pieces are rare though, so don't hope to find a masterpiece sword here. Such things come with a great price and risk\nA herbalist can offer health potions, mixtures, antidotes, plants, ingredients and, if you are lucky, recipes. But why am I even telling you that, you are not an alchemist! Am I right? Gypsies offer pagan amulets and useless crap like bat corpses, some folks claim to know the true purpose of such things, but this is just a dangerous bragging\nMonks sell candles, holy talismans and other trinkets: crosses, rings, writing tools. And junkmen offer garbage. But if you possess special skills, you can make something useful of those tortoise combs, nails and ropes.";
			link.l1 = "";
			link.l1.go = "guide_19";
		break;
		
		case "guide_11": // к резиденции
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_SetActorType(pchar);
			LAi_ActorGoToLocator(npchar, "officers", "reload3_1", "Guide_townhall", -1);
			LAi_ActorFollow(pchar, npchar, "", -1);
		break;
		
		case "guide_12":
			dialog.text = "Behold the governor's palace. This is a home and an office of the most important man in a colony. Nobles visit the palace for balls and parties, people of business and captains come here to solve both official and personal matters. It is important to be a governor's friend, because he has a strong influence on the citizens of nation he represents\nPrivateers earn good money working for governors. They also buy war captives. If you are wealthy and want to establish a good relationship with His Excellency, then he may even honour you by gambling with you\nIt seems that you are impatient, my friend. Are you in a hurry?";
			link.l1 = "Well... I guess. Monsieur, I came here to find my brother, I was told that he must be somewhere here, in Saint-Pierre. He is an important man, the governor must know him...";
			link.l1.go = "guide_13";
		break;
		
		case "guide_13":
			dialog.text = "A-ha, I see. So you want to pay His Excellency a visit and ask him about your brother? Well, I won't delay you any further then. Our governor is called Jaques Dille du Parquets, I am sure he will do what he can.";
			link.l1 = "Tell me, who else can help me? Perhaps it is unwise to trouble His Excellency?";
			link.l1.go = "guide_14";
		break;
		
		case "guide_14":
			dialog.text = "You've said that your brother is well-known here. Ask around the streets. Eventually you will find someone who can help. What's your brother's name?";
			link.l1 = "Michel de Monper.";
			link.l1.go = "guide_15";
		break;
		
		case "guide_15":
			dialog.text = "Michel de Monper... Yes, I heard this name before, but I have never been introduced to the man, so I can not help you. Good luck, monsieur, I am sure that we will meet again.";
			link.l1 = "Gratitude, "+GetFullName(npchar)+"!";
			link.l1.go = "guide_16";
		break;
		
		case "guide_16":
			DialogExit();
			LAi_SetCitizenType(npchar);
			LAi_CharacterDisableDialog(npchar);//запрет диалога
			LAi_group_MoveCharacter(npchar, "FRANCE_CITIZENS"); // пока идем заниматься Мишелем
			chrDisableReloadToLocation = false;//открыть локацию
		break;
		
		case "guide_17": // к ростовщику
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_SetActorType(pchar);
			LAi_ActorGoToLocator(npchar, "officers", "reload8_1", "Guide_bank", -1);
			LAi_ActorFollow(pchar, npchar, "", -1);
		break;
		
		case "guide_18":
			dialog.text = "This is the house of a money-lender. Usurer, banker, their kind has many different names, often rude ones. You may think whatever you want of them, but their services can help you a lot. You can deposit money, exchange doubloons and pesos, sell or buy jewellery. If you have a positive reputation you can even loan some coins, but be careful\nUsurers offer best prices for gems, jewels and other valuable trinkets, always visit them to sell such things. They are powerful people, so don't cross them.";
			link.l1 = "";
			link.l1.go = "guide_11";
		break;
		
		case "guide_19": // к борделю
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_SetActorType(pchar);
			LAi_ActorGoToLocator(npchar, "officers", "reload9_1", "Guide_brothel", -1);
			LAi_ActorFollow(pchar, npchar, "", -1);
		break;
		
		case "guide_20":
			dialog.text = "A brothel. Every man visits such places, don't believe the opposite. Even the nobles, yet the reputation... suffers. Be aware of that. Be nice with the girls and they may tell you interesting things\nThere is no better cure for your mind and your body. If your health is damaged - visit the place. You may also drink a special potion to fix it, yet it's rare and much less fun. Oh, when I say 'health', I don't mean scratches on your skin. You will get hit. A lot. But if they hit you hard and often, if you drink too much strong health potions, eventually you will ruin your body. Watch your condition, take rest if needed be or suffer terrible consequences. Priests can almost literally resurrect you, but such last resorts are very expensive.";
			link.l1 = "";
			link.l1.go = "guide_17";
		break;
		
		case "guide_21":
			dialog.text = "Oh, you again, my friend! I see that they have let you inside Saint-Pierre's holy place - headquarters of the Order. You must be important. Found your brother?";
			link.l1 = "Yes, I did...";
			link.l1.go = "guide_22";
		break;
		
		case "guide_22":
			dialog.text = "Forgive me, monsieur, but your voice is absent joy...";
			link.l1 = "True. I was hoping to get the hell out of this shithole back to France in no time, yet my fate keeps mocking me. I will stay here for a bloody long time! And the best part is that I must become a sailor, imagine that!";
			link.l1.go = "guide_23";
		break;
		
		case "guide_23":
			dialog.text = "That is... a sudden change in your life. But don't be sad, to be a captain of your own ship is a very, very respected position here. You do intend to buy a ship, right?";
			link.l1 = "Yes, damn it, that's exactly what I must do... All I need is to find a shipyard and money as soon as possible. Problem is - I don't know where the hell is a shipyard, how to fly a vessel and where to get money!";
			link.l1.go = "guide_24";
		break;
		
		case "guide_24":
			dialog.text = "I wish I could to fill your pockets with gold, but I am broke just as you are. But I can fill your head with knowledge you so desperately need. Interested?";
			link.l1 = "Yes, it would be great.";
			link.l1.go = "guide_25";
		break;
		
		case "guide_25":
			dialog.text = "Follow me then. Let's start from the main thing - the ships.";
			link.l1 = "";
			link.l1.go = "guide_26";
		break;
		
		case "guide_26": // на верфь
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_SetActorType(pchar);
			LAi_ActorGoToLocator(npchar, "reload", "reload5", "Guide_shipyard", -1);
			LAi_ActorFollow(pchar, npchar, "", -1);
			chrDisableReloadToLocation = true;//закрыть локацию
		break;
		
		case "guide_27":
			dialog.text = "A shipyard. Every colony has one. A place to sell or buy a sea vessel and also to repair her. Know that our shipyards have nothing to do with famous shipyards of old good Europe. This is province, they don't build large trade and military ships here\nLocal masters build luggers, schooners, sloops. Rarely brigs and barkentines. But sometimes privateers bring prizes they captured, shipbuilders buy them for cheap, repair them and sell for a fortune\nI once saw a frigate in price list. Local made ships also have poor characteristics. Don't worry though, you must start to learn on small and poor vessels in order to master something better\nOh, and a shipyard is also a place to buy cannons. There are several types of guns you may get on your vessel, provided, of course, that she can carry them. Every vessel has limitations, you will never be able to put 24-pounders on a lugger. Remember that big calibres are rare and expensive. On the bright side, such guns can literally exterminate enemy's crew, sails and hull\nOne last thing. Shipyards also provide services for aesthetes: they can paint your sails and draw emblems or coats of arms. Won't speed up your beauty, but will make her look much fancier.";
			link.l1 = "Interesting...";
			link.l1.go = "guide_28";
		break;
		
		case "guide_28": // в порт
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_SetActorType(pchar);
			LAi_ActorGoToLocator(npchar, "quest", "quest1", "Guide_port", -1);
			LAi_ActorFollow(pchar, npchar, "", -1);
		break;
		
		case "guide_29":
			dialog.text = "This is a pier, a heart of any port. I used to sail in the past, so let me tell you more about seamanship\nFirst, remember the most important thing: don't even try to control a vessel if you don't have enough points in your navigation skill! If you do, then your other skills will suffer and so do your officers'\nYou will fight worse, shoot worse, trade worse and so on\nThat means that if you will attempt to control a man-of-war with your current skill of navigation, you will turn in a worthless pile of crap, unable to do anything.";
			link.l1 = "How do I learn this... navigation?";
			link.l1.go = "guide_30";
		break;
		
		case "guide_30":
			dialog.text = "Time and patience. At this moment you can control a tartane or a long boat. But you can always hire a navigator. Normally they can be found in taverns along with other mercenaries\nAlways check their skill first, in case it is not enough for your ship, you will experience the very same problems I mentioned before.";
			link.l1 = "How do I know how many points in navigation I need in order to control a particular ship?";
			link.l1.go = "guide_31";
		break;
		
		case "guide_31":
			dialog.text = "Ship's rank determines it. For example, I know enough (45 points) to control a 4th rank vessel without penalties. Brigs, barkentines, flutes. Xebec and corvette require more, so I won't be able to use them properly. Not mentioning second rank ships like frigates and heavy galleons\nAs for giant battleships or man-of-wars... only experts in navigation can control such monsters, it takes years to master the skill and don't forget the money. A battleship and her crew can waste your purse in a month if you are not as rich as king.";
			link.l1 = "I see...";
			link.l1.go = "guide_32";
		break;
		
		case "guide_32":
			dialog.text = "Take care of all officer positions. A boatswain trains your crew and makes boarding more effective, a purser will do financial activities instead of you and fight rats. A physician saves people, a ship joiner saves a ship and boarding officers save your ass\nPay attention to skills of candidates and watch their reputation.";
			link.l1 = "Reputation?";
			link.l1.go = "guide_33";
		break;
		
		case "guide_33":
			dialog.text = "Exactly. Everyone has it. It is made of the man's deeds and show everyone what is he really is\nIf you are an honourable man and you always try to do good, then look for officers who share you ideals. And if you prefer to act as a bandit... well, you have got the idea\nHonest folks will not work for scum, the opposite is also true.";
			link.l1 = "Got it.";
			link.l1.go = "guide_34";
		break;
		
		case "guide_34":
			dialog.text = "Now let's talk about types of ships. There are two types. Trade and military ships. Trade ships have large cargo holds and military ones have speed and strong guns. Barque, flute, carrack are the brightest examples of trade ships. As for military vessels... lugger, brig, corvette. There are mixes of course, the ships which have characteristics of both trade and military: snows, schooners, galleons\nShips also have different rigging arrangements, some are mostly square rig and some are mostly fore-and-aft rig, which form the ship's course angle.";
			link.l1 = "Course angle?";
			link.l1.go = "guide_35";
		break;
		
		case "guide_35":
			dialog.text = "Yes. It determines how your rigging is affected by wind and on which course your vessel will make the best speed she is capable of. Once you at the sea, find an arrow on the mini map, that will be your course angle.";
			link.l1 = "That's a bit hard to me. But I guess I shall learn in time.";
			link.l1.go = "guide_36";
		break;
		
		case "guide_36":
			dialog.text = "Crew. You and your ship are nothing without a manpower. Every sailor must know how to do three things. How to deal with rigging, to operate cannons and to fight. Every nation excels only in one of these three activities. For example, Spain has the best fighters in the world and their soldiers wear armour, so grapeshot, slices and stabs are not quite effective against them. I am talking about handguns, cannon grapeshot don't give a damn about body armour\nVisit taverns of Spain, England and France if you want to make a dream crew. Watch you men's morale, provide them with rum, whores and coin. Do that on a constant basis and your people will die for you. Fail to do so, and they will see you hanged. A motivated professional has worth of ten rookies in a fight, don't forget about a physician or take care of your own medicine skills in order to prevent extra casualties.";
			link.l1 = "I will remember this...";
			link.l1.go = "guide_37";
		break;
		
		case "guide_37":
			dialog.text = "Now a few words about naval battles. Our waters are dangerous, they are crawling with Spanish and pirates, so eventually you will engage them in the open sea. Ship cannons use four types of ammo. Cannon balls, grape shots, chain shots and bombs\nCannon balls are all-purpose and the cheapest to buy, they have the biggest effective fire range, they tear enemy's sails, destroy his hull and kill his crew\nChain shots have a decent range of fire, their purpose is to eliminate enemy's rigging in order to make him loose his speed. They are good to use when you want to chase or flee. If you are lucky you may even take down a whole mast\nBombs. Use them if you want to sink your opponent's vessel. Bombs do the biggest damage to the hull, but they have a second short range of fire, so you need to come closer first which may prove fatal. They also cost the most of all shells\nGrape shot is your best choice if you want to board and capture an enemy's ship. These little balls wipe out people, but the shortest fire range makes them risky to use. But it is worth it\nHold your fire if you are not sure that you can deal enough damage. Every volley comes with a price of gunpowder and cannons' condition. They explode sometimes, especially if you shoot too often. Always maneuver, try to take a better position to the wind. If the enemy is too dangerous and you can't flee, then try to provoke him to shoot you constantly from distance without any negative effect upon you. Such trick will eventually empty his gunpowder supplies. It may take days, so you'd better find a cover like rocks or a coastal line. Of course, such tactics will not work in the open sea\nMines. Also a fine way to sink them all. Make them to chase you and drop mines. Every mine require a decent amount of powder, but even one mine can almost destroy a lugger\nGet a spyglass and use it to observe your enemy. A good spyglass will provide you a fine tactical overview, a presence of musketeer unit on your opponent's vessel for instance. Such unit can mow down a lot of your men, in this case be sure to gift them a few volleys of grape shot before boarding.";
			link.l1 = "You scary me... but I guess, I must be ready for anything.";
			link.l1.go = "guide_38";
		break;
		
		case "guide_38":
			dialog.text = "You shall learn, I have no doubt in that. Since you are going to be a captain and a ship owner, I will show one more place of great importance to you. A harbour office. Follow me.";
			link.l1 = "";
			link.l1.go = "guide_39";
		break;
		
		case "guide_39": // к портовому управлению
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_SetActorType(pchar);
			LAi_ActorGoToLocator(npchar, "reload", "reload10", "Guide_portoffice", -1);
			LAi_ActorFollow(pchar, npchar, "", -1);
		break;
		
		case "guide_40":
			dialog.text = "There it is. In a harbour office you can find job offers. Freights for large trade ships and convoys for military ones. If you own a fast ship, they might offer you a courier job\nI recommend to earn some recommendations here, if you do your job well several times, they will give you more complicated and much better paid contracts\nYou may also ask here about other captains and leave your ships for safekeeping. Open ended, just don't forget to pay.";
			link.l1 = "Got it.";
			link.l1.go = "guide_41";
		break;
		
		case "guide_41":
			dialog.text = "Well, the city gates are close, so there is another topic I'd like to tell you about. These gates by the way lead to the jungles. Follow me and I will tell you about stealth actions and fencing. You mind?";
			link.l1 = "Not at all. Your help is invaluable to me.";
			link.l1.go = "guide_42";
		break;
		
		case "guide_42":
			dialog.text = "Follow me then!";
			link.l1 = "";
			link.l1.go = "guide_43";
		break;
		
		case "guide_43": // к воротам
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_SetActorType(pchar);
			LAi_ActorGoToLocator(npchar, "reload", "gate_back", "Guide_gate", -1);
			LAi_ActorFollow(pchar, npchar, "", -1);
		break;
		
		case "guide_44":
			dialog.text = "So, the city gates. Straight to the jungles. In daytime, guarded by two soldiers who check everyone entering the city. Therefore, there are two ways to get in the city. First, you can drop an anchor in port and disembark on a pier. Second, you may land on some distant bay and travel through the jungles to the city gates\nSometimes you will have to visit Spanish colonies, so remember: we are at war with the Spanish, so don't even think to sail into their port without a Spanish flag raised, otherwise a fort will open fire immediately\nYou need to master special skills and be careful in order to get inside hostile settlements. Know that the only way to safely drop an anchor in Spanish port is to learn a skill named 'raise the Spanish flag' or 'raise the Dutch flag'\nSuch tricks require time and experience to learn. 'Raising the flag' doesn't mean to raise some yellow-red piece of rag, but to conduct various masking measures\nA chance of successful deception depends on the level of your stealth skill, class and number of your ships. It is easy to make a single small sloop looking like a Spanish vessel, the same can not be said about five frigates\nIf you are unable to trick the fort guards and port officers, you should consider sneaking through the city gates I mentioned before. Wait until night to avoid gates guards and enter. Avoid any soldiers in the city, especially at night, find a tavern, rest there and do what you planned. Don't fight soldiers if you are compromised, find an empty house and stay there for half an hour. This will make them stop hunting you\nTricky isn't it? In order to avoid such complications, buy a trading license, it will save you a lot of nerves.";
			link.l1 = "A trading license? What is that?";
			link.l1.go = "guide_45";
		break;
		
		case "guide_45":
			dialog.text = "A document you can get in the headquarters of the Dutch West Indian Company. A sign of your peaceful intentions. This paper will allow you to enter any port until the terms are expired\nBut there are some downsides. First, the Company has special rules and demands which any captain willing to buy the license must follow. Second, it costs a lot. And the last and the worst, you still need a 'raising flag' skill to land at ports. Otherwise you will be shot on approach by fort's heavy cannons.";
			link.l1 = "Where is the Company's headquarters?";
			link.l1.go = "guide_46";
		break;
		
		case "guide_46":
			dialog.text = "Willemstad. Curacao. If you want to buy a license - go there, they will give you details.";
			link.l1 = "Things are so messed up here...";
			link.l1.go = "guide_47";
		break;
		
		case "guide_47":
			dialog.text = "Don't be upset, my friend. You shall learn. Now, let's do fencing practice.";
			link.l1 = "Sounds good. Let's move!";
			link.l1.go = "guide_48";
		break;
		
		case "guide_48": // телепортируем за городские ворота
			DialogExit();
			LAi_SetActorType(npchar);
			DoQuestReloadToLocation("FortFrance_ExitTown", "goto", "goto19", "Guide_ExitTown");
		break;
		
		case "guide_49":
			dialog.text = "My friend, I believe you know how to hold a sword?";
			link.l1 = "Ha! Sure, I know. I was taught by the very best fencing master of France and...";
			link.l1.go = "guide_50";
		break;
		
		case "guide_50":
			dialog.text = "Good for you. Let me tell you some theory first\nSo, there are three types of cold steel: rapiers and swords, sabres and cutlasses, broadswords and axes. Every type requires different skills and abilities to master, so you will have to learn them separately\nEvery class has it's own ups and downs. Rapiers are light, have low requirements of stamina, but they deal the least amount of damage. An axe is heavy, but it can kill with a single heavy blow, though it will take so much stamina from you, that you will have to rest for a while. Sabres are somewhere in the middle\nThere are several fencing moves and tricks in your disposal: thrust attack, chopping attack, heavy attack and group attack. You can also parry, feint and block\nThrust attack is the fastest move, requires a small amount of stamina to perform, excellent for rapiers and mostly useless for axes. Chopping attack is quite versatile, decent speed, significant loss of stamina, good for sabres, broadswords and axes, not that good for rapiers. Heavy attack is dealt from above, an excellent choice for axes, will work fine for sabres and cutlasses, yet rapiers are simply not designed for such moves. This attack will drain a huge amount of stamina, it is slow, but, it has maximum potential damage and it ignores blocking\nBlocking is not a panacea, it is useless against heavy attacks and decent opponents always have a chance to break your block. Parrying is much better, it makes your opponent open for your attacks, he also losses stamina. Several successful parries and your opponent completely losses his initiative and is forced to defend himself while you have a total advantage\nFeints are tricky and risky. Fooling your opponent and immediately dealing him a quick thrust requires a little loss of stamina, but you must be concentrated, attentive and to be in a rhythm of the fight. Mastering this move will demand a lot of practice from you, but it is rewarding - even professional duellists and masters of sword will fall by your hand\nThe last thing. In order to maximize damage from every type of attacks, you must use the right weapon for the each. Thrust attack will show it's best with long, heavy, straight rapier or sword with a balance from 0 to 0.5. Long, curved cutlasses or sabres with a balance from 1.5 to 2 are excellent for chopping and heavy attacks. A heavy axe with a balance of 2.0 is perfect for heavy attacks, but such weapon will require a lot of stamina and skill to use. Group attack isn't worth to be your primal move, it's rather defensive, but a curved, light, long cutlass with a balance around 1.25 will do great against groups of enemies around you\nFinally, the best weapon for feint is a dagger, think about it if you want to make this move your speciality. A weight of a weapon determines how much stamina it will require for any attack move and it also affects the damage. Remember, that finding your perfect weapon may take some time and working on your fighting style will take even more.";
			link.l1 = "And what if there are several enemies?";
			link.l1.go = "guide_51";
		break;
		
		case "guide_51":
			dialog.text = "This complicates things. A decent fighter can take down a few rookies at once in the open area, but if there are dozen of bad guys - avoid to be surrounded at all costs, run away, find yourself a corner, stairs, doorways, whatever, just make them fight you one on one, or two on one. They will slice you up in a second if you make a mistake, so force them to play on your terms, don't lose initiative and watch your stamina\nThough, I have heard about a special Indian potion which allowed masters of sword and axe to kill five or six enemies at once with a few swings of group attack.";
			link.l1 = "A potion?";
			link.l1.go = "guide_52";
		break;
		
		case "guide_52":
			dialog.text = "Ometochtli mixture or whatever they call it. An ancient Indian recipe. Ask merchants, someone may sell it to you someday. But you must learn alchemy first in order to use the recipe... Since we are already talking potions - let me tell about healing\nIf you need to fix a small wound, use a healing essence. Serious hits can be treated with a healing elixir. Mixture, rum and wine also restore your health\nAntidote and mixture will do fine if you are poisoned. I also recommend you a ginger root - it heals without any side effects, as distinct from essence and elixir.";
			link.l1 = "Side effects?";
			link.l1.go = "guide_53";
		break;
		
		case "guide_53":
			dialog.text = "Essences, elixirs and mixtures damages your health. As I mentioned in the beginning of our small tour, it's bad. Bad health will cause drops in your skills' level, it will decrease total amount of your health points and stamina.\nSleeping, sex and a rare potion 'Tears of Ish-Chel' restore health if it's not ruined completely. If it is too late, then attend to a priest, they will help for a fee.";
			link.l1 = "I see. What can you tell me about handguns?";
			link.l1.go = "guide_54";
		break;
		
		case "guide_54":
			dialog.text = "Not much to say. Point and shoot! Use grapeshot if there are several enemies. Get a musket or a rifle. Deadly damage and you can always hit people with a buttstock. I also heard about weapon which shoots grenades, but I have never seen it.";
			link.l1 = "I see. Practice time?";
			if (FindCharacterItemByGroup(pchar, BLADE_ITEM_TYPE) == "") link.l1.go = "guide_55a";
			else link.l1.go = "guide_55";
		break;
		
		case "guide_55a":
			dialog.text = "Hm. Just noticed. Where is your sword? I fear that our lesson must be delayed. How did you end up without a weapon, "+pchar.name+"?";
			link.l1 = "One dickhead in a fancy suit took it from me in advance of my brother's debt... Do you have an extra sword for me? I will return it after the lesson is over...";
			link.l1.go = "guide_55b";
		break;
		
		case "guide_55b":
			GiveItem2Character(pchar, "blade_05");
			EquipCharacterByItem(Pchar, "blade_05");
			npchar.quest.guide_blade = "true";
			dialog.text = "You are lucky. I do have an extra sword. I was going to sell it, but, lucky you, I was delayed.";
			link.l1 = "Thank you. Shall we?";
			link.l1.go = "guide_55";
		break;
		
		case "guide_55":
			dialog.text = "Begin! And don't waste potions if you have them, we are not going to kill each other.";
			link.l1 = "Fine...";
			link.l1.go = "guide_56";
			npchar.quest.guide_win = 0;
		break;
		
		case "guide_56": // махач
			LAi_SetCurHPMax(pchar); 
			LAi_GetCharacterMaxEnergy(pchar);
			LAi_SetCurHPMax(npchar); 
			LAi_GetCharacterMaxEnergy(npchar);
			LAi_SetImmortal(npchar, false);
			LAi_group_Delete("EnemyFight");
			DialogExit();
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			// ставим проверяльщики
			LAi_SetCheckMinHP(pchar, 1, true, "Guide_HeroFail");
			LAi_SetCheckMinHP(npchar, 1, true, "Guide_HeroWin");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
		case "guide_57": // побил гида с первого раза
			dialog.text = "This. This is the man who knows how to hold his sword. Well done, monsieur. You need more practice, but you have all chances to become the master of the sword.";
			link.l1 = "Thank you. What now?";
			link.l1.go = "guide_62"; // нода на выход
			AddComplexSelfExpToScill(50, 50, 50, 50);
			AddCharacterExpToSkill(pchar, "Leadership", 80);
		break;
		
		case "guide_58": // побил гида со второго или третьего раза
			dialog.text = "Much better! See, all you need is to concentrate. You need more practice, one day you will become a decent fencer.";
			link.l1 = "Thank you. What now?";
			link.l1.go = "guide_62"; // нода на выход
			AddComplexSelfExpToScill(20, 20, 20, 20);
			AddCharacterExpToSkill(pchar, "Leadership", 30);
		break;
		
		case "guide_59": // побили первый раз
			dialog.text = "I won, monseniour. Move faster, parry my stabs, jump back. A rematch?";
			link.l1 = "Sure! No mercy, monseniour!";
			link.l1.go = "guide_56";
			link.l2 = "No, I had enough. Let's finish the lesson. What now?";
			link.l2.go = "guide_62"; // нода на выход
		break;
		
		case "guide_60": // побили второй раз
			dialog.text = "I won again, "+pchar.name+"! Don't loose your initiative. Catch my hits, feint them. If you see that I am going to hit hard - jump away or parry, don't just guard. Again!";
			link.l1 = "Come, messere, I shall give you a lesson this time!";
			link.l1.go = "guide_56";
			link.l2 = "No, I had enough. Let's finish the lesson. What now?";
			link.l2.go = "guide_62"; // нода на выход
		break;
		
		case "guide_61": // побили третий раз
			dialog.text = "You need a lot to learn, "+pchar.name+". Don't worry, you still got a lot of time to master your fencing. But be careful, don't take any chances until you know how to hold a weapon.";
			link.l1 = "I will consider it, monsieur, but I have to say that you were just too fortunate! This blasted heat... the only reason why I didn't beat a heck out of you. Whatever, let's end our fencing lesson. What now?";
			link.l1.go = "guide_62"; // нода на выход
		break;
		
		case "guide_62":
			dialog.text = "Now it's time to say farewells, monsieur. It was a pleasure. I hope that my presentation and training did you some good and will prove useful in the future. Perhaps, we shall meet again one day\nAnd about the money - talk to important people of our city. Visit all places that I have shown you today and speak to their owners. Ask people around. Take a walk to the jungles and to the fort. Find a job or... well, I am not God or a judge, check people's houses and see what trinkets you can find in their chests. Just do it when they show their backs to you or you are screwed\nGood luck, "+pchar.name+", I have a strong feeling that you have a spark of greatness inside you, do your best to make it a fire.";
			link.l1 = "Gratitude, monsieur. Pleasure was mine. Godspeed!";
			link.l1.go = "guide_63";
			if (CheckAttribute(npchar, "quest.guide_blade"))
			{
				RemoveCharacterEquip(pchar, BLADE_ITEM_TYPE);
				RemoveItems(pchar, "blade_05", 1);
			}
		break;
		
		case "guide_63":
			LAi_SetCurHPMax(pchar); 
			LAi_GetCharacterMaxEnergy(pchar);
			DialogExit();
			chrDisableReloadToLocation = false;//открыть локацию
			npchar.lifeday = 0;
			DoQuestReloadToLocation("FortFrance_Town", "quest", "quest2", "");
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
