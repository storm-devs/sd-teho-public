// диалоги НПС по квесту НСО
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;
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
			dialog.text = "What are you looking for?";
			link.l1 = "Nothing.";
			link.l1.go = "exit";
		break;
		
		// инспектор Ноэль Форже
		case "noel":
			dialog.text = "Nice to meet you, captain!";
			link.l1 = "I'm glad to meet you too, monsieur Forget. It's a rare occasion to meet a guest from the metropolis here in the wilderness...";
			link.l1.go = "noel_1";
		break;
		
		case "noel_1":
			DialogExit();
			sld = characterFromId("Puancie");
			sld.dialog.currentnode = "patria_3";
			LAi_SetActorType(sld);
			LAi_ActorSetSitMode(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "noel_2":
			dialog.text = "I'm pleased that during this journey I will be on your ship, captain. Chevalier de Poincy told me a lot of interesting stories about you. I'm sure that after dinner in the messroom we will have plenty of topic to discuss. A glass of wine could also come in handy.";
			link.l1 = "I'm all for a cosy talk, especially when I'm full. I'd be glad to be your companion, Baron. ";
			link.l1.go = "noel_3";
		break;
		
		case "noel_3":
			dialog.text = "Perfect. When we go to a colony, I'd ask you to gide me to the governor, and I'll personally explain to him what needs to be done. You'll just wait until I finish my affairs. Deal?";
			link.l1 = "Aye, monsieur Forget. Welcome aboard!";
			link.l1.go = "noel_4";
		break;
		
		case "noel_4":
			DialogExit();
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "OpenTheDoors", 12.0);
		break;
		
		case "noel_5":
			dialog.text = "Tortuga is a small colony captain. I estimate that it will take me about three days to inspect all I need on this Island.";
			link.l1 = "Understood, Baron. So in three days time I'll come here to pick you up. Good luck!";
			link.l1.go = "noel_6";
		break;
		
		case "noel_6":
			DialogExit();
			DoQuestReloadToLocation("Tortuga_town", "reload", "reload3", "Patria_VisiterTortuga");
		break;
		
		case "noel_7":
			dialog.text = "My work on Tortuga is done, it's time to raise the anchor.";
			link.l1 = "Understood, Baron. We are heading off immediately.";
			link.l1.go = "noel_8";
		break;
		
		case "noel_8":
			DialogExit();
			Patria_VisiterTortugaSail();
		break;
		
		case "noel_9":
			dialog.text = "Yes-yes, we will definitely report on this in Capsterville. The threat of such an important colony being conquered unthinkable, I will personally make sure that Philippe de Poincy takes strict and ruthless measures! Captain, I will remain for a week on this island, there are a lot of plantations here, it will take some time.";
			link.l1 = "Got it, Baron. So in a week time I will be waiting for you by the governors palace. Have fun and don't overwork yourself!";
			link.l1.go = "noel_10";
		break;
		
		case "noel_10":
			DialogExit();
			DoQuestReloadToLocation("PortPax_town", "reload", "reload3", "Patria_VisiterPortPax");
		break;
		
		case "noel_11":
			dialog.text = "There you are, captain. My work on Hipaniola is done, It's time to raise the anchor.";
			link.l1 = "Understood, Baron. We are heading off immediately.";
			link.l1.go = "noel_12";
		break;
		
		case "noel_12":
			DialogExit();
			Patria_VisiterPortPaxSail();
		break;
		
		case "noel_13":
			dialog.text = "Captain, this island seems familiar to me. Isn't it Saint Christopher?";
			link.l1 = "Yes, baron, precisely. We are almost there.";
			link.l1.go = "noel_14";
		break;
		
		case "noel_14":
			dialog.text = "Almost there? Weren't we supposed to visit Sint Maarten too? It also belongs to the French colonies.";
			link.l1 = "Sint Maarten? It's a Dutch colony, monsieur Forget.";
			link.l1.go = "noel_15";
		break;
		
		case "noel_15":
			dialog.text = "Is it? In Paris it was considered to be French. How come?";
			link.l1 = "No idea, Baron. Ever since I first set foot in the archipelago, Sint Maarten was a Dutch colony. Perhaps I don't know something. You should consider talking to Chevalier de Poincy on this matter.";
			link.l1.go = "noel_16";
		break;
		
		case "noel_16":
			dialog.text = "Fine, captain, let it be this way. We are almost at Capsterville anyway.";
			link.l1 = "...";
			link.l1.go = "noel_17";
		break;
		
		case "noel_17":
			DialogExit();
			Island_SetReloadEnableGlobal("Nevis", true);
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "OpenTheDoors", 5.0);
			pchar.quest.Patria_visiter_fin.win_condition.l1 = "location";
			pchar.quest.Patria_visiter_fin.win_condition.l1.location = "Charles_Roomtownhall";
			pchar.quest.Patria_visiter_fin.function = "Patria_VisiterFin";
			pchar.questTemp.Patria = "epizode_2_return";
		break;
		
		case "noel_18":
			dialog.text = TimeGreeting()+", captain. I'm glad to see you. I have heard that you were promoted, please accept my congratulations! To tell you the truth, you really are one of the most sensible and gifted officers in de Poincy's service.";
			link.l1 = "Thank you, monsieur.";
			link.l1.go = "noel_19";
		break;
		
		case "noel_19":
			dialog.text = "Finally, there is only one colony left - Sint Maarten. To be honest, I've grown tired of these trips. I'll be glad to finish this inspection and start arranging the next French West-Indies trade campaign. Are we ready to call away the anchor?";
			link.l1 = "Aye, Baron. Get on board.";
			link.l1.go = "noel_20";
		break;
		
		case "noel_20":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "Patria_SanMartinBaron", 5.0);
		break;
		
		case "noel_21":
			dialog.text = "Captain, could you tell me what just happened? Does this mean a war? Why in hell's name were we almost sunk by the Dutch?";
			link.l1 = "Baron, I don't understand anything myself! This is some kind of misunderstanding, no doubt.";
			link.l1.go = "noel_22";
		break;
		
		case "noel_22":
			dialog.text = "Captain, I can bet that this 'misunderstanding' has a name and a surname! Peter Stuyvesant, so called 'renter' of Sint Maarten and a partner of our dear Chevalier de Poincy!";
			link.l1 = "No idea, Baron. We better hurry to the Capsterville and report on this matter to the Governor General.";
			link.l1.go = "noel_23";
		break;
		
		case "noel_23":
			dialog.text = "Without a doubt, that's exactly what we will do! And I will demand explanations! I knew that renting an island to the Dutch was a big mistake! Let's leave this place as quick as we can, captain, before someone decides to chase us!";
			link.l1 = "Precisely, monsieur ...";
			link.l1.go = "noel_24";
		break;
		
		case "noel_24":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "Patria_SanMartinBack", 5.0);
		break;
		
		case "noel_25":
			dialog.text = "Monsieur, first let me congratulate you on your promotion! I eagerly supported the decision of monseigneur de Poincy to grant you the rank of Vice Admiral. You deserve this title! Well, and I have recently returned from Sint Maarten. At the warehouses of Philipsburg, we conducted a revision, all Dutch goods were confiscated and now belong to the treasury of France. You, as the commander of a combat operation, have been granted a share of the trophies. I agree with the Chevalier that this is fair. Your goods have been transferred to the warehouse of the St. Christopher store, and you can pick them up whenever you want.";
			link.l1 = "Thank you, Baron. Let the goods stay there for a while. Upon my return from Curacao, I will take them.";
			link.l1.go = "noel_26";
		break;
		
		case "noel_26":
			dialog.text = "Good luck in your next campaign, Vice Admiral! I am confident that you will return with victory and justly punish this scoundrel Stuyvesant.";
			link.l1 = "...";
			link.l1.go = "noel_27";
		break;
		
		case "noel_27":
			DialogExit();
			pchar.questTemp.Patria = "epizode_11_start";
			AddQuestRecord("Patria", "58");
			pchar.questTemp.Patria.GoodsSM = "true";
		break;
		
		case "noel_28":
			dialog.text = "Who do we have here! Vice Admiral Charles de Maure! Glad to see you! What's your business in Port-au-Prince?";
			link.l1 = "I'm pleased to meet you too, Baron. I'm here because of my duty, I had to pay monsieur Jeremy Deschamps du Mussaca a visit of politeness...";
			link.l1.go = "noel_29";
		break;
		
		case "noel_29":
			dialog.text = "This encounter is very fortunate indeed, because I have been waiting for a long time to meet with you personally. I want to talk to you, but not here.";
			link.l1 = "Let's go to the tavern then, shall we?";
			link.l1.go = "noel_30";
		break;
		
		case "noel_30":
			DialogExit();
			FreeSitLocator("PortPax_tavern", "sit_base1");
			DoQuestReloadToLocation("PortPax_tavern", "sit", "sit_base1", "Patria_CondotierTavern");
		break;
		
		case "noel_31":
			LAi_SetSitType(pchar);
			dialog.text = "There are no unwanted ears here, we can talk safely...";
			link.l1 = "I'm all ears, Baron.";
			link.l1.go = "noel_32";
		break;
		
		case "noel_32":
			dialog.text = "Vice Admiral, you seem to be a man of honour. Such a valiant naval officer just has to be like that...";
			link.l1 = "Hmm... I don't think I fully understand you, monsieur...";
			link.l1.go = "noel_33";
		break;
		
		case "noel_33":
			dialog.text = "Monsieur de Maure, I want to ask you: what do you think of your liege, Governor General Philippe de Poincy?";
			link.l1 = "Officer's duty is not to think about his commander, but to follow his orders.";
			link.l1.go = "noel_34";
		break;
		
		case "noel_34":
			dialog.text = "Oh, leave it, Vice Admiral, we're not in the barracks, and not in the de Poincy's hall. I will say it this way: don't you think, that monsieur de Poincy... abuses his power? I still can't forget how we almost went down the drain under the guns of Fort Sint Maarten. I am sure that the treachery of the Dutch had a reason.";
			link.l1 = "They wanted to conquer the island.";
			link.l1.go = "noel_35";
		break;
		
		case "noel_35":
			dialog.text = "Yes, yes, but why exactly at the same moment as when I decided to inspect it? Why not a month earlier? Or two months later? I do not believe that this was coincidence, monseigneur. Don't you have any suspicions? We both had our lives at the stake there.";
			link.l1 = "I risk my life every day, monsieur Forget. I think you understand that...";
			link.l1.go = "noel_36";
		break;
		
		case "noel_36":
			dialog.text = "Your courage is beyond doubt. But that's not what I wanted to say. You see... When I was doing my job on the Sint Maarten that was liberated by you, I repeatedly heard whisperings from locals about some mine in the depths of the island. I tried to ask people about it, but they just acted foolish. They were afraid... It was obvious that I didn't seem very trustwothy, but this only strengthened my suspicions: could this misterious mine be the reason for all this, Monsieur de Maure? Wars are waged because of gold, am I right?";
			link.l1 = "There are numerous mines in the archipelago. Most of them are exhauseted and became worthless. I know of one major operating gold mine, it is owned by the Spaniards on South Main. But I've never heard of gold mining in Sint Maarten.";
			link.l1.go = "noel_37";
		break;
		
		case "noel_37":
			dialog.text = "You are skilled in the art of speechcraft, Vice Admiral! I understand: you do not trust me. I'm a new here... Monsieur de Maure, I'm an infulential person in Paris. The Minister of Finance is my close friend. I visit the King regularly. My authority is much greater than the authority of Philippe de Poincy, formally, of course, because here the Governor General is the most entitled person. But truth be told, here, in the colonies, the rule of the stongest is the only rule.";
			link.l1 = "That's is absolutely right";
			link.l1.go = "noel_38";
		break;
		
		case "noel_38":
			dialog.text = "But not in Paris. There, the most influencial people are the King and the Minister of Finance... my close friend. Monsieur de Maure, you are a brilliant military man, but I believe that Phillip de Poincy is using you for his own personal purposes. You are intelligent, so you must have suspicions. You can trust me. I guarantee you complete anonimity and support of the authorities of Paris. I swear by my title.";
			link.l1 = "***REMAIN LOYAL TO POINCY***";
			link.l1.go = "noel_39"; // развилка
			link.l2 = "***SIDE WITH BARON FORGET***";
			link.l2.go = "noel_53";
		break;
		
		case "noel_39":
			dialog.text = "";
			link.l1 = "I understand you, Monsieur Forger. To a man unfamiliar with local mentalities, de Poinsy's actions may indeed seem strange. When I first arrived at the Archipelago, I was literally shocked by what was happening here. I still remember the words: 'if you meet an unprotected Spanish ship, you can try to board it.' Betrayal, treachery, deception - they are present here at every step. Piracy, pillaging, robbery...";
			link.l1.go = "noel_40";
		break;
		
		case "noel_40":
			dialog.text = "";
			link.l1 = "We are at peace with Spain in Europe. But here we are fierce enemies. The Dutch today see friendly and harmless, and tomorrow the Company official confiscates your goods just because they suddenly announced it was banned from importation even though you could not know it. The English officer is openly pirating, sinking the Company's ships, and the Company hires a cutthroat who disguises as a ghost ship, and terrifies British traders...";
			link.l1.go = "noel_41";
		break;
		
		case "noel_41":
			dialog.text = "";
			link.l1 = "In this wolf's den, we sometimes have to make strange decisions that are not quite obvious to someone unfamiliar with all this. And what seems suspicious to you is in fact the only correct action. It is difficult to sit on several chairs at once and still manage to send profits to the parent state. Chevalier de Poincy copes with this perfectly, he is an experienced manager and visionary politician. Of course, he can make mistakes, but we all make them at some point in our lives...";
			link.l1.go = "noel_42";
		break;
		
		case "noel_42":
			dialog.text = "";
			link.l1 = "And you need to reckon with everything and everyone. With the ambitions of the Spaniards who believe that the whole New World belongs to them, with the greed of the Dutch traders, with cold prudence and ruthless brutality of the English. And even with pirates.";
			link.l1.go = "noel_43";
		break;
		
		case "noel_43":
			dialog.text = "With pirates?!";
			link.l1 = "Yes, you heard right. The Dutch and the British are actively cooperating with pirates... unofficially, of course. The Brethren of the Coast is a serious force that can challenge any nation in the region. The only thing that makes them slightly less dangerous is the fact that they are scattered and act on their own behalf. Do you know that the former governor of Tortuga, Levasseur, actually created a state in the state, relying on pirates?";
			link.l1.go = "noel_44";
		break;
		
		case "noel_44":
			dialog.text = "I believe I've heard something about it...";
			link.l1 = "A few powerful privateer ships that protected the island were constantly docked in the port of Tortuga. Levasseur betrayed France, becoming a sort of local authority. And now, after the destruction of the pirate nest on Tortuga together with their master, the pirates are very, very angry at the French...";
			link.l1.go = "noel_45";
		break;
		
		case "noel_45":
			dialog.text = "No way!";
			link.l1 = "Yes. We had to do it, although the result is not the best. No trading French ship can feel safe in the Caribbean now. The Spaniards, who also do not have agreements with pirate barons, at least have a fleet of strong galleons and powerful military warships capable of repelling the filibusters. Like the Dutch with their East Indies. But we can not boast of such a thing, alas. And French pirates often rob French merchants.";
			link.l1.go = "noel_46";
		break;
		
		case "noel_46":
			dialog.text = "This is madness! Is there no way to put an end to this?";
			link.l1 = "Many have tried. In the end, instead of fighting, they buy the pirates' loyalty with gold. Issue privateer patents, I mean.";
			link.l1.go = "noel_47";
		break;
		
		case "noel_47":
			dialog.text = "Hmm...";
			link.l1 = "And you, Monsieur Forget, want to organize a trading company here on the Archipelago. Do you understand now what difficulties you will have to face? How many bastards want to get their share of income here? And they are not going to let go it easily. And that pirates are capable of erasing all efforts? In order to protect merchant ships, you would have to maintain a military fleet, but will that be profitable from a financial standpoint?";
			link.l1.go = "noel_48";
		break;
		
		case "noel_48":
			dialog.text = "But French traders manage here somehow?";
			link.l1 = "Exactly, somehow. Especially now, when Levasseur's pirate fortress on Tortuga has been siezed...";
			link.l1.go = "noel_49";
		break;
		
		case "noel_49":
			dialog.text = "Your words fall in line with what de Poincy said.";
			link.l1 = "Because that's how it is here, in the archipelago.";
			link.l1.go = "noel_50";
		break;
		
		case "noel_50":
			dialog.text = "You're so eager in what you say. Even I did not know a lot of this and, you are right: I still don't. I guess my suspicions of Puacie were invalid. You opened my eyes. Thank you, Vice Admiral. But the French minister is counting on the creation of the Company. The King needs money ...";
			link.l1 = "I understand. But please take what I just said into consideration.";
			link.l1.go = "noel_51";
		break;
		
		case "noel_51":
			dialog.text = "Your grace is truly admirable, Vice Admiral! Such a noble temper! I'm not surprised that you've been here so long and do not hurry back home. But we will see each other again and again: I will return here in half a year. The French Trading Company shall rise. And with pirates, I think you're exaggerating a bit. All in all, we do have warships and brave captains, such as you.";
			link.l1 = "Not even a 48-pound can save you from a backstab... When will you be heading off to the parent state?";
			link.l1.go = "noel_52";
		break;
		
		case "noel_52":
			dialog.text = "In two weeks I will return to Saint Christopher, and from there I'll be heading home. Monsieur de Poincy gave me a good ship - a brig called 'Favory' and a glorious captain. The ship is fast and the captain is experienced, but, of course, I was safer with you. I remember with warmth our travels through the archipelago, Vice Admiral.";
			link.l1 = "Thank you for your kind words, Baron. Well, it's time for us part...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Patria_CondotierToPirates");
		break;
		
		case "noel_53":
			dialog.text = "";
			link.l1 = "Here everyone uses each other. Chevalier used me in his doings long before I became an officer of the navy.";
			link.l1.go = "noel_54";
		break;
		
		case "noel_54":
			dialog.text = "And is it acceptable? What do you think?";
			link.l1 = "No. But the Chevalier left me no choice: either follow his orders, or my brother would remain behind bars until the end of his days, and the good name of my family would be ruined.";
			link.l1.go = "noel_55";
		break;
		
		case "noel_55":
			dialog.text = "Horrible! This is straight up terrorism! Did he have any reason for such threats?";
			link.l1 = "My brother had the misfortune of being his entrusted man. Just like me right now.";
			link.l1.go = "noel_56";
		break;
		
		case "noel_56":
			dialog.text = "Where is your brother now?";
			link.l1 = "In exile. After the spanish raid on St. Pierre he vanished.";
			link.l1.go = "noel_57";
		break;
		
		case "noel_57":
			dialog.text = "I knew that Poincy was not who he said he was! Wolf in sheep's skin! Vice Admiral, you can trust me. I am a man of honour. And I will save you from the yoke of your 'patron' if we can find tangible evidence of his criminal activities. Do you know anything about this dull story with Stuyvesant? Speak openly, don't worry: you are only a military man, and you were obliged to carry out orders.";
			link.l1 = "I know. There indeed is a mine at Sint Maarten. Only they get there not gold, but salt. It is in great demand from the Spaniards. Poincy could not trade with the Spaniards directly, so Stuyvesant acted as an middleman.";
			link.l1.go = "noel_58";
		break;
		
		case "noel_58":
			dialog.text = "So Poincy and Stuyvesant are business partners?";
			link.l1 = "Used to be. After you expressed a desire to inspect Sint Maarten, the Stuyvesant decided to knock Poincy out of the game, taking all the profits from the salt mine himself. Poincy could not tell anyone... But Stuyvesant miscalculated, as evidenced.";
			link.l1.go = "noel_59";
		break;
		
		case "noel_59":
			dialog.text = "Do you think that the mine continues to operate?";
			link.l1 = "I'm sure of it. It seems that Poincy has a new trade ally. It's no one other that Colonel Doily ";
			link.l1.go = "noel_60";
		break;
		
		case "noel_60":
			dialog.text = "Can we present any evidence to the ministry?";
			link.l1 = "Hmm. During the storming of the mine, which, by the way, was conducted by Spaniards, not the Dutch, we captured the owner. He is now on my ship. You can talk to him. There is a chance that in exchange for freedom he will tell a lot of interesting things.";
			link.l1.go = "noel_61";
		break;
		
		case "noel_61":
			dialog.text = "Let's go to your ship immediately. Order your prisoner to be delivered to your cabin. I will interrogate him.";
			link.l1 = "Fine, let's go.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Patria_CondotierToCabin");
		break;
		
		case "noel_62":
			dialog.text = "Great, Vice Admiral. I'll have a talk with him. Stay here, please.";
			link.l1 = "Of course...";
			link.l1.go = "noel_63";
		break;
		
		case "noel_63":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocator(npchar, "rld", "aloc1", "", -1);
			DoQuestFunctionDelay("Patria_CondotierInCabinTalk", 3.0);
		break;
		
		case "noel_64":
			dialog.text = "I wrote down all the evidence of your captive, and he signed under them. Now we must fulfill what I promised him: whenever there is a convenient opportunity stop by Cartagena and let him disembark. But you yourself heard everything\nNow what a scoundrel our Poincy is! Rented an island to the Dutch, conducted illegal activities there and allowed the Spaniards to go there and manage the mine! I'm afraid to imagine how much money the King's treasury is missing!";
			link.l1 = "Will that evidence be enough to charge Poincy?";
			link.l1.go = "noel_65";
		break;
		
		case "noel_65":
			dialog.text = "Unfortunately, I'm afraid it won't. The evidence is very important, but it's not enough. But I don't want you to be involved in all this for reasons we both understand.";
			link.l1 = "The Spaniard agreed to testify before your commission when it will arrive here.";
			link.l1.go = "noel_66";
		break;
		
		case "noel_66":
			dialog.text = "This will happen no sooner than six months, and who knows what will become of this Spaniard, and will we be able to find him later in Cartagena ... We need to have even more valuable evidence. Namely - confirmation that the mine continues its secret activities to in pursuit of increasing Poincy's personal gains.";
			link.l1 = "So you're offering me to travel to Sint Maarten?";
			link.l1.go = "noel_67";
		break;
		
		case "noel_67":
			dialog.text = "Yes. Do you know how to get to the mine?";
			link.l1 = "Yes.";
			link.l1.go = "noel_68";
		break;
		
		case "noel_68":
			dialog.text = "Then, at night, you and I will sneak in there, quietly, so that no one will see, and will check what is going on there.";
			link.l1 = "Good.";
			link.l1.go = "noel_69";
		break;
		
		case "noel_69":
			dialog.text = "But what about the Chevalier, huh? Now I understand why he hinted to me with such courage that the creation of the French Trading Company on the Archipelago would be unprofitable ... Of course, it would be very unprofitable for him!";
			link.l1 = "Since we are now allies, Baron, I will tell you all the truth: Poincy asked me ... to convince you that you to not create the Trade Company here.";
			link.l1.go = "noel_70";
		break;
		
		case "noel_70":
			dialog.text = "So that's how it is! I hope that at least he didn't ask you to eliminate me with a sword or a pistol?";
			link.l1 = "No. You had to be convinced is some other way.";
			link.l1.go = "noel_71";
		break;
		
		case "noel_71":
			dialog.text = "Poincy will pay for this, but now we need to immediately go to Sint Maarten. Spaniard will be delivered to Main then. We're leaving, Vice Admiral!";
			link.l1 = "It will seem a bit strange that you will be leaving the island on my ship, don't you think?";
			link.l1.go = "noel_72";
		break;
		
		case "noel_72":
			dialog.text = "Don't think so. Weren't you supposed to convince me? That's exactly what you did, haha! Yes, before sailing to Europe, I'll tell the Chevalier that I agree with his points and the Trading Company won't be created. Let him live in blissful peace for the time being ... Let's go!";
			link.l1 = "...";
			link.l1.go = "noel_73";
		break;
		
		case "noel_73":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "Patria_CondotierToSMartin", 5.0);
		break;
		
		case "noel_74":
			dialog.text = "Lead the way, Vice Admiral. The night will conceal us with it's shroud of darkness.";
			link.l1 = "Follow me...";
			link.l1.go = "noel_75";
		break;
		
		case "noel_75":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			pchar.quest.Patria_Condotier_inMine.win_condition.l1 = "location";
			pchar.quest.Patria_Condotier_inMine.win_condition.l1.location = "Location_reserve_03";
			pchar.quest.Patria_Condotier_inMine.function = "Patria_CondotierInMine";
		break;
		
		case "noel_76":
			dialog.text = "(whispering) I saw it! I saw it! Did you see it? Redcoats! Those are english soldiers!";
			link.l1 = "I told you - Poincy now conducts business with colonel Doily.";
			link.l1.go = "noel_77";
		break;
		
		case "noel_77":
			dialog.text = "You were right. I've seen enough. Now let's get out of here as fast as we can before we're spotted!";
			link.l1 = "...";
			link.l1.go = "noel_78";
		break;
		
		case "noel_78":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_SetActorType(pchar);
			LAi_ActorRunToLocator(pchar, "reload", "reload2_back", "Patria_CondotierToBeach", -1);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
		break;
		
		case "noel_79":
			dialog.text = "You see what the 'commercial projects' of our dear Chevalier lead to! The English behave like hosts on a French island! It's unthinkable!";
			link.l1 = "We need to move, or someone will most definitely come here. We can't afford to be recognised.";
			link.l1.go = "noel_80";
		break;
		
		case "noel_80":
			dialog.text = "Vice Admiral, I've been thinking all the time during our travel to Sint Maarten, and I decided on something: can you arrange me a meeting with Peter Stuyvesant?";
			link.l1 = "With Stuyvesant? But why?";
			link.l1.go = "noel_81";
		break;
		
		case "noel_81":
			dialog.text = "A former business partner might have some serious clues. I'm sure that Stuyvesant is not very happy with Poincy, especially after recent events...";
			link.l1 = "I believe so, Baron. I personally will not dare to go to the Stuyvesant's palace. Too risky for me...";
			link.l1.go = "noel_82";
		break;
		
		case "noel_82":
			dialog.text = "I already thought about it. We will go to Curacao, disembark in a bay far from the city and send our captive Spaniard from the mine with a letter to Stuyvesant. I will not mention you there, instead I will inform him that I'm leading an investigation against Poincy or something along the lines. I think the Dutchman will come for the rendezvous.";
			link.l1 = "Hmm. I don't think that this is a good idea. The Stuyvesant is not a fool, he takes what he can. Well, if you so want, let's try.";
			link.l1.go = "noel_83";
		break;
		
		case "noel_83":
			DialogExit();
			chrDisableReloadToLocation = false;
			LocatorReloadEnterDisable("Shore40", "reload1_back", false);
			LocatorReloadEnterDisable("Shore40", "boat", false);
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			LAi_LocationDisableOfficersGen("shore40", false);
			LAi_LocationDisableOfficersGen("Location_reserve_01", false);
			LAi_LocationDisableOfficersGen("Location_reserve_03", false);
			pchar.quest.Patria_CondotierCuracao.win_condition.l1 = "location";
			pchar.quest.Patria_CondotierCuracao.win_condition.l1.location = "shore22";
			pchar.quest.Patria_CondotierCuracao.function = "Patria_CondotierOnCuracao";
			AddQuestRecord("Patria", "81");
		break;
		
		case "noel_84":
			dialog.text = "Monsieur de Maure, please forgive my foolishness. You were right about Stuyvesant. I should have guessed that only an even bigger scoundrel could have challenged de Poincy!";
			link.l1 = "A million... Poincy wanted a million, Stuyvesant wants a million... We're going in circles...";
			link.l1.go = "noel_85";
		break;
		
		case "noel_85":
			dialog.text = "What are you talking about Vice Admiral?";
			link.l1 = "When I arrived to the Carribean, Poincy wanted me to pay a million as a ransom for my brother.";
			link.l1.go = "noel_86";
		break;
		
		case "noel_86":
			dialog.text = "And you paid that much?";
			link.l1 = "I earned it and I paid it. Not in a month, of course. Truth be told, I was just a landlubber back then. Still Chevalier didn't let Michel go.";
			link.l1.go = "noel_87";
		break;
		
		case "noel_87":
			dialog.text = "And after that you enlisted to work for Poincy? I honestly don't understand you.";
			link.l1 = "I enlisted into the service of the King of France.";
			link.l1.go = "noel_88";
		break;
		
		case "noel_88":
			dialog.text = "Excuse me, Monsieur de Maure. Of course, you serve the King! Poincy must answer for everything! Including all the pain that he caused you.";
			link.l1 = "I'll find a million, Baron. Go on board... I will solve this problem.";
			link.l1.go = "noel_89";
		break;
		
		case "noel_89":
			DialogExit();
			//chrDisableReloadToLocation = false; //17-add
			LAi_LocationFightDisable(&Locations[FindLocation("shore22")], false);
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "sea", "none", "", "", "", 10.0);
			pchar.questTemp.Patria = "epizode_12_stivesant";
			AddQuestRecord("Patria", "83");
			SetFunctionTimerCondition("Patria_CondotierStivesantTimeOver", 0, 0, 30, false); // таймер на месяц
		break;
		
		case "noel_90":
			dialog.text = "You wanted to meet me, Vice Admiral?";
			link.l1 = "Yes. I had a meeting with Stuyvesant. Here is his ledger.";
			link.l1.go = "noel_91";
		break;
		
		case "noel_91":
			RemoveItems(pchar, "Reserve_item_01", 1);
			dialog.text = "No way! Hmm, let's see... (reading)";
			link.l1 = "...";
			link.l1.go = "noel_92";
		break;
		
		case "noel_92":
			LAi_Fade("", "");
			dialog.text = "That's it! Our dear Chevalier is doomed. As soon as all this accounting will be seen by the Minister of Finance ... I can't even imagine what will happen. We won't even have to look for the Spaniard from Cartagena. Monsieur de Maure, did you really pay million for this book?";
			link.l1 = "Yeah. Stuyvesant is not one for messing around.";
			link.l1.go = "noel_93";
		break;
		
		case "noel_93":
			dialog.text = "I will not ask where you got it. But I swear to you that you will get it back. I am sure that we will find a hefty sum of money in Poincy's chests and at usurers. I only ask you to wait six months until I return from Europe with a commission.";
			link.l1 = "And don't forget to bring a regiment of well trained and armed soldiers. And a ship like 'Eclatant'.";
			link.l1.go = "noel_94";
		break;
		
		case "noel_94":
			dialog.text = "Don't doubt it. I realized moral values play a major role in the making of your decisions. You did a great job, that you trusted me and exposed this state criminal. Now take me to Capsterville, where I will report to Poincy about the success of your mission - you managed to convince me abandon creating a trading company. Perhaps Poincy will reward you for this - take the reward with a clear conscience and do not think about anything. You will not be dragged into this, and your name will not be mentioned anywhere. Baron Forget is a man of honor and his word.";
			link.l1 = "I'm glad, baron. Let's set out!";
			link.l1.go = "noel_95";
		break;
		
		case "noel_95":
			DialogExit();
			chrDisableReloadToLocation = false;
			bQuestDisableMapEnter = false;//открыть карту
			Island_SetReloadEnableGlobal("Curacao", true);
			DeleteAttribute(pchar, "GenQuest.MapClosedNoBattle");
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", 5.0);
			pchar.questTemp.Patria = "epizode_12_baronwin";
			AddQuestRecord("Patria", "85");
			pchar.quest.Patria_CondotierBaron_win.win_condition.l1 = "location";
			pchar.quest.Patria_CondotierBaron_win.win_condition.l1.location = "Charles_town";
			pchar.quest.Patria_CondotierBaron_win.function = "Patria_CondotierBaronWin";
		break;
		
		case "noel_96":
			dialog.text = "So, Vice Admiral, have finally arrived. Your mission is over, now it's up to me. Be conduct your own affairs, defend the interests of France, as you have done before. About six months later, this vile story will come to an end. I'll send the courier to find you when you will be needed. Farewell, Monsieur de Maure, I was very glad to meet you! The minister and the King will hear of you, I promise. And they will hear all the best.";
			link.l1 = "Thank you, Baron. Bon Voyage!";
			link.l1.go = "noel_97";
		break;
		
		case "noel_97":
			DialogExit();
			AddQuestRecord("Patria", "86");
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload3_back", "none", "", "", "OpenTheDoors", 15.0);
			SetFunctionTimerCondition("Patria_CondotierPuancieFinal", 0, 0, 1, false); // таймер
		break;
		
		case "noel_98":
			dialog.text = "Glad to see you, Vice Admiral. I am here again, as promised. And with me - the first assistant of Minister of Finance, Baron Olivier Bourdin.";
			link.l1 = "Where's Chevalier de Poincy?";
			link.l1.go = "noel_99";
		break;
		
		case "noel_99":
			dialog.text = "Where he's supposed to be: in prison. He was arrested and will be brought to France for investigation and trial. Given his position, he will certainly avoid the execution, but he can't avoid a huge fine, demotion and, probably, imprisonment.";
			link.l1 = "Was the arrest peaceful?";
			link.l1.go = "noel_100";
		break;
		
		case "noel_100":
			dialog.text = "Not really. The Chevalier had here, in the residence, a whole guard of loyal soldiers. But we were ready for such escalation in advance.";
			link.l1 = "Well then, I congratulate you, baron! Perhaps now you will deal with the French trading Company?";
			link.l1.go = "noel_101";
		break;
		
		case "noel_101":
			dialog.text = "Me? Yes. His grace monsieur Bourdin - will come back to France together with Chevalier de Poincy. And you, vice-admiral, should also expect change. Now you have a new position. His grace will tell you more.";
			link.l1 = "...";
			link.l1.go = "noel_102";
		break;
		
		case "noel_102":
			DialogExit();
			LAi_SetActorType(npchar);
			sld = characterFromId("Finansist");
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "noel_103":
			dialog.text = "Monsieur de Maure! Wait a minute!";
			link.l1 = "Yes, Baron. I'm listening.";
			link.l1.go = "noel_104";
		break;
		
		case "noel_104":
			dialog.text = "As for the million that you paid to the Stuyvesant... I did not tell the ministry about this, so as to... avoid questions, like how a French officer came into possession of so much money. This may have been harmful to us.";
			link.l1 = "I understand.";
			link.l1.go = "noel_105";
		break;
		
		case "noel_105":
			dialog.text = "All the money that was found in possession of Poincy in Casterville was confiscated by baron Bourdin. But, as it turns out, Poincy also had a stash that the English moneylenders were hiding for him. I will talk to him about returning the investments, and then I will find a way to compensate your requests.";
			link.l1 = "I'm afraid it won't be easy for you to take something from the hands of the English moneylenders.";
			link.l1.go = "noel_106";
		break;
		
		case "noel_106":
			dialog.text = "I agree. But we will work on it, and I will keep you updated on the results.";
			link.l1 = "As you wish.";
			link.l1.go = "noel_107";
		break;
		
		case "noel_107":
			dialog.text = "Vice-admiral, you aren't looking so good, or is it just me? You've only just received the highest position in the colonies!";
			link.l1 = "No-no, not at all... It's just that everything happened so unexpectedly, and I'm a bit lost.";
			link.l1.go = "noel_108";
		break;
		
		case "noel_108":
			dialog.text = "Don't worry. You will get used to your new position. And besides, you were quite successful at being the governor of Sint-Maarten for half a year, so it will be nothing new to you.";
			link.l1 = "Oh, I'm sure I'll get used to it. I've managed many a position in all my time here in the Caribbean. I'll manage this one as well.";
			link.l1.go = "noel_109";
		break;
		
		case "noel_109":
			dialog.text = "That is lovely to hear. And now, allow me to excuse myself, your Grace, Governor General! We will meet shortly!";
			link.l1 = "Goodbye, monsieur Forget. I wish you the best of luck in your trade deals!";
			link.l1.go = "noel_110";
		break;
		
		case "noel_110":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload3_back", "none", "", "", "OpenTheDoors", 20.0);
			bDisableFastReload = false;//открыть переход
			AddQuestRecord("Patria", "90");
			CloseQuestHeader("Patria");
			pchar.questTemp.Patria = "end"; // конец линейки
			pchar.questTemp.Patria.GenGovernor = "true"; // Шарль генерал-губернатор
		break;
		
		case "noel_final":
			dialog.text = "Allow me to express my sincerest appreciation for you, vice-admiral! You have saved my life by freeing me from those damned outlaws' captivity. I thank you, as well as Philippe de Poincy. I must admit, I was absolutely wrong in my judgement of him, and I ask you to forgive me for that. You and the Chevalier were right: the French trading Company will have a lot of troubles here, and it looks like we will only lose money here\nOnly experienced people, like Poincy, and such brave soldiers as you, can withstand these wolves that live on every island here. I need to go to the palace, and after that I will leave to Europe as soon as possible, and forget this nightmare.";
			link.l1 = "I'm glad everything ended well, Baron. Goodbye!";
			link.l1.go = "noel_final_1";
		break;
		
		case "noel_final_1":
			DialogExit();
			AddQuestRecord("Patria", "76");
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload3_back", "none", "", "", "OpenTheDoors", 15.0);
			SetFunctionTimerCondition("Patria_CondotierPuancieFinal", 0, 0, 1, false); // таймер
		break;
		
		// капитан Эклятона
		case "ecliaton_cap":
			dialog.text = TimeGreeting()+", monsieur. What brings you onto the deck of the 'Eclatant'?";
			link.l1 = TimeGreeting()+", monsieur. Allow me to introduce myself - Captain Charles de Maure, I come from the Governor General of the French colonies in the Archipelago, Chevalier de Poincy. I was ordered to take your ship into my squadron under my command. Here is the letter...";
			if (pchar.model == "Sharle_6") link.l1.go = "ecliaton_cap_1";
			else link.l1.go = "ecliaton_cap_no";
		break;
		
		case "ecliaton_cap_no":
			dialog.text = "It's some sort of mistake, monsieur. You are standing on a ship-of-the-line of the French navy, and I only listen to orders issued by those who are in service to the Royal navy. And you do not seem to have any signs of belonging to that fleet. Perhaps, you mistake our ship for another one.";
			link.l1 = "But...";
			link.l1.go = "ecliaton_cap_no_1";
		break;
		
		case "ecliaton_cap_no_1":
			DialogExit();
			npchar.dialog.currentnode = "ecliaton_cap_no_2";
		break;
		
		case "ecliaton_cap_no_2":
			if (pchar.model == "Sharle_6")
			{
				dialog.text = "Huh, I didn't even recognize you in this uniform, Captain. Well then, let me see your letter, I wish to look through the contents.";
				link.l1 = "Here.";
				link.l1.go = "ecliaton_cap_1";
			}
			else
			{
				dialog.text = "We've already discussed everything, monseigneur...";
				link.l1 = "Hmm...";
				link.l1.go = "ecliaton_cap_no_1";
			}
		break;
		
		case "ecliaton_cap_1":
			RemoveItems(pchar, "Reserve_item_01", 1);
			dialog.text = "Well, let's see... (reading) Uh-huh. So, me and my ship are to be under your command, Captain de Maure?";
			link.l1 = "That is the order of the Governor General.";
			link.l1.go = "ecliaton_cap_2";
		break;
		
		case "ecliaton_cap_2":
			dialog.text = "Yes-yes, orders are not to be questioned. Alright. Let us introduce ourselves: I am Marquis Hubert Dassier, Captain of the 66-cannon ship-of-the-line of the French navy named 'Eclatant', along with this well-trained crew, and I swear on my honour, it is one of the best ships that France has ever had.";
			link.l1 = "Glad to hear it, as the task we were assigned by the Governor General will require good working knowledge of navigation and artillery.";
			link.l1.go = "ecliaton_cap_3";
		break;
		
		case "ecliaton_cap_3":
			dialog.text = "Will you tell me the details of this upcoming operation?";
			link.l1 = "Of course. We will be moving to the Spanish island of Trinidad, located about a week's travel South from here. We will abruptly attack the fort guarding the San Jose colony and run it into the ground. Then, we will talk with the Spanish about our compensation for the recent attack on the French settlement of Saint-Pierre.";
			link.l1.go = "ecliaton_cap_4";
		break;
		
		case "ecliaton_cap_4":
			dialog.text = "I see. When will we depart?";
			link.l1 = "As soon as possible. We have to complete this task in a month, so we have more than enough time.";
			if (GetCompanionQuantity(pchar) > 4) link.l1.go = "ecliaton_cap_5_1";
			else link.l1.go = "ecliaton_cap_5";
		break;
		
		case "ecliaton_cap_5":
			dialog.text = "Alright, Captain de Maure. We will depart at your command.";
			link.l1 = "";
			link.l1.go = "ecliaton_cap_6";
		break;
		
		case "ecliaton_cap_6":
			DialogExit();
			npchar.dialog.currentnode = "ecliaton_cap_wait";
			npchar.DeckDialogNode = "ecliaton_cap_wait";
			Patria_AddEcliaton();
		break;
		
		case "ecliaton_cap_wait":
			dialog.text = "Do you have any orders, or perhaps questions, Captain de Maure?";
			link.l1 = "Not yet...";
			link.l1.go = "ecliaton_cap_wait_1";
		break;
		
		case "ecliaton_cap_wait_1":
			DialogExit();
			npchar.dialog.currentnode = "ecliaton_cap_wait";
			npchar.DeckDialogNode = "ecliaton_cap_wait";
		break;
		
		case "ecliaton_cap_5_1":
			dialog.text = "But, Captain de Maure, first you have to make your squadron smaller - my ship cannot join you, or it will be too large squadron.";
			link.l1 = "Huh. You're right. I will leave one ship here in the harbour.";
			link.l1.go = "ecliaton_cap_5_2";
		break;
		
		case "ecliaton_cap_5_2":
			DialogExit();
			npchar.dialog.currentnode = "ecliaton_cap_5_3";
		break;
		
		case "ecliaton_cap_5_3":
			if (GetCompanionQuantity(pchar) > 4)
			{
				dialog.text = "Haven't you yet made the squadron smaller, monsieur?";
				link.l1 = "Yes-yes, I remember, I'm working on it.";
				link.l1.go = "ecliaton_cap_5_2";
			}
			else
			{
				dialog.text = "So, the 'Eclatant' is ready to join your squadron, monsieur.";
				link.l1 = "Then I will go to my ship, and you should prepare to enter the sea.";
				link.l1.go = "ecliaton_cap_5";
			}
		break;
		
		case "ecliaton_cap_7":
			dialog.text = "Greetings, Commodore. Waiting for another battle campaign?";
			link.l1 = "Yes. The 'Eclatant' is once again under my command. We are going to storm Philipsburg. The Governor General has tasked us with clearing out the Dutch from Sint-Maarten.";
			link.l1.go = "ecliaton_cap_9";
			link.l2 = "Yes, Captain, but a bit later. I will tell you when. The 'Eclatant' has to be ready to enter the sea at any minute.";
			link.l2.go = "ecliaton_cap_8";
		break;
		
		case "ecliaton_cap_8":
			DialogExit();
			npchar.dialog.currentnode = "ecliaton_cap_7";
			npchar.DeckDialogNode = "ecliaton_cap_7";
		break;
		
		case "ecliaton_cap_9":
			dialog.text = "Everything is clear. It will be a hard mission, eh, monseigneur?";
			link.l1 = "I'm sure of it. Prepare to enter the sea, we are departing soon.";
			link.l1.go = "ecliaton_cap_10";
		break;
		
		case "ecliaton_cap_10":
			DialogExit();
			npchar.dialog.currentnode = "ecliaton_cap_wait";
			npchar.DeckDialogNode = "ecliaton_cap_wait";
			Patria_BastionAddEcliaton();
		break;
		
		case "ecliaton_cap_11":
			dialog.text = "Glad to see you on the deck of the 'Eclatant', vice-admiral! What are your orders?";
			link.l1 = "Prepare the 'Eclatant' for departure. First, we will sail to the coast of Jamaica, and then, together with Colonel Doyley's squadron, we will attack Curacao.";
			link.l1.go = "ecliaton_cap_13";
			link.l2 = "There will be orders, Captain, but later. I will tell you when. The 'Eclatant' has to be ready to enter the sea at any minute.";
			link.l2.go = "ecliaton_cap_12";
		break;
		
		case "ecliaton_cap_12":
			DialogExit();
			npchar.dialog.currentnode = "ecliaton_cap_11";
			npchar.DeckDialogNode = "ecliaton_cap_11";
		break;
		
		case "ecliaton_cap_13":
			dialog.text = "The 'Eclatant' and its crew are ready, Vice Admiral!";
			link.l1 = "Excellent. Then we will depart immmediately.";
			link.l1.go = "ecliaton_cap_14";
		break;
		
		case "ecliaton_cap_14":
			DialogExit();
			npchar.dialog.currentnode = "ecliaton_cap_wait";
			npchar.DeckDialogNode = "ecliaton_cap_wait";
			Patria_CuracaoAddEcliaton();
		break;
		
		// Дойли на Антигуа
		case "doily":
			if (CheckAttribute(pchar, "questTemp.Saga") && pchar.questTemp.Saga == "end" && colonies[FindColony("Pirates")].nation == PIRATE)
			{
				dialog.text = "Oh, what an acquaintance! Isn't it Captain Charles de Maure himself?! I've heard, you now have a position in the French navy. What a surprise, considering who you were, let's say, 'working' for previously...";
				link.l1 = "Greetings, sir. Are you talking about the affair with Isla Tesoro? Oh, but it wasn't me who wrote the English laws, according to which the island was passed down to the heir of the explorer who found it, according to his will. So, I am not guilty of that, I only helped Miss Sharpe get what was hers by rights.";
				link.l1.go = "doily_1";
			}
			else
			{
				dialog.text = TimeGreeting()+", Captain. I suppose, the representative of the French navy has arrived at Antigua with an important goal in mind?";
				link.l1 = "Indeed, sir. I was sent here by the Governor General of the French colonies, Philippe de Poincy. Saint-Christopher has been besieged by the Spanish and Dutch navy squadrons. The Chevalier asked for help from you and sir Jonathan Fox as well. Here is his letter to you, colonel.";
				link.l1.go = "doily_3";
			}
		break;
		
		case "doily_1":
			dialog.text = "I'm wondering, Captain, how much money did you make off of this? I suppose, quite a lot, since you've managed to pay for the services of the rogue Loxley, which are not cheap at all. I'm sure, the pirate barons pay you deductions regularly for keeping the island in their possession. We both know perfectly well that Ellen Sharpe is only a mask.";
			link.l1 = "Colonel, we both also know that the pirate barons mostly operate in the interests of England, not officially, mind you... Without them, it would be quite hard to resist the hegemony of the Spanish in the region, don't you agree? So, from the point of view of the politicians, the fact that the Brethren of the Coast has kept the island to themselves, was, perhaps, even more profitable then if Isla Tesoro had become an English naval base...";
			link.l1.go = "doily_2";
		break;
		
		case "doily_2":
			dialog.text = "This is arguably true, Captain, but... be that as it is. You've arrived at Antigua with some important goal, I suppose? Perhaps it has to do with the fact that the relations of two former allies - France and Holland, have worsened considerably?";
			link.l1 = "Quite right. I was sent by the governor-general of the French colonies, Philippe de Poincy. Saint-Christopher has been besieged by the Spanish and Dutch navy. The Chevalier asks for your help. Here is his letter to you, colonel.";
			link.l1.go = "doily_3";
		break;
		
		case "doily_3":
			RemoveItems(pchar, "Reserve_item_01", 1);
			dialog.text = "Let me see... (reading)";
			link.l1 = "";
			link.l1.go = "doily_3_1";
		break;
		
		case "doily_3_1":
			LAi_Fade("", "");
			dialog.text = "Hmm... very intriguing! Captain, your commander knows how to pique my interest, it isn't that unusual for people to call him a cunning fox. We should have done this long ago, instead of trying to befriend the Dutch. As we know very well what the Dutch Company and their Director stand for. Well then, I think that in this situation we really shouldn't deny helping to the besieged Casterville, and we have more than enough troops to allow it.\nWhat are the numbers and types of ships in the squadron, Captain?";
			link.l1 = "I've counted six ships: one eighty-cannon ship-of-the-line of the third rank and five ships of the fourth. They might also have frigates.";
			link.l1.go = "doily_4";
		break;
		
		case "doily_4":
			dialog.text = "Seriously. We can put forward our squadron, consisting of a hundred-cannon ship of the first rank, two ships of the fourth and a heavy frigate, against theirs.";
			if (!CheckAttribute(pchar, "questTemp.Patria.FailLugger"))
			{
				link.l1 = "Sir, we also have a 66-cannon ship-of-the-line, the 'Eclatant', sailing to the help of Saint-Christopher from the coast of Guadelupa.";
				link.l1.go = "doily_5";
			}
			else
			{
				link.l1 = "A ship of the first rank will be of great help in our fight.";
				link.l1.go = "doily_5_1";
			}
		break;
		
		case "doily_5":
			dialog.text = "Perfect. In that case, we are well above our enemies' firing capability. The victory shall be ours.";
			link.l1 = "And let us not forget of my own ship, sir.";
			link.l1.go = "doily_6";
		break;
		
		case "doily_5_1":
			dialog.text = "That is true. Including the help from the fort of Casterville, the victory shall be ours.";
			link.l1 = "And let us not forget of my own ship, sir.";
			link.l1.go = "doily_6";
		break;
		
		case "doily_6":
			dialog.text = "Of course, monsieur de Maure. Whatever the case may be, tales of your talents in sailing can be heard throughout the archipelago. Your flagman will lead the squadron.";
			if (GetCompanionQuantity(pchar) > 1)
			{
				link.l1 = "I will put the rest of the ships from my squadron on hold, then come back to you, and we will rush to the help of the besieged.";
				link.l1.go = "doily_7_1";
			}
			else
			{
				link.l1 = "I will prepare my ship shortly, and we will rush to the help of the besieged.";
				link.l1.go = "doily_8";
			}
		break;
		
		case "doily_7_1":
			DialogExit();
			npchar.dialog.currentnode = "doily_7_2";
		break;
		
		case "doily_7_2":
			dialog.text = "So, are you ready for departure?";
			if (GetCompanionQuantity(pchar) > 1)
			{
				link.l1 = "Wait just a little bit, sir.";
				link.l1.go = "doily_7_1";
			}
			else
			{
				link.l1 = "Yes, sir.";
				link.l1.go = "doily_8";
			}
		break;
		
		case "doily_8":
			dialog.text = "Then let us begin, and may God help us!";
			link.l1 = "...";
			link.l1.go = "doily_9";
		break;
		
		case "doily_9":
			DialogExit();
			npchar.dialog.currentnode = "doily_10";
			chrDisableReloadToLocation = true;
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "OpenTheDoors", -1);
			AddQuestRecord("Patria", "42");
			Patria_SiegeAddEngSquadron();
		break;
		
		case "doily_10":
			dialog.text = "Do you have any further questions, sir?";
			link.l1 = "No, colonel...";
			link.l1.go = "doily_11";
		break;
		
		case "doily_11":
			DialogExit();
			npchar.dialog.currentnode = "doily_10";
			npchar.DeckDialogNode = "doily_10";
		break;
		
		case "doily_12":
			dialog.text = "Get the letter for the Stuyvesant, sir. If you're not aware of who I am, let me introduce myself: Colonel Edward Doily, governor of Port-Royale and commander of this expedition!\nTo tell you the truth, I have a great urge to run the bandit hideout known as Willemstadt into the ground. The most vile, two-faced and despicable organisation in the Caribbean, known as the Dutch West-Indies trading Company who think that all trade in the Archipelago is exclusively their right, and who hire the likes of Jacob van Berg and other pirates to capture and sink the ships of English merchants...";
			link.l1 = "...";
			link.l1.go = "doily_13";
		break;
		
		case "doily_13":
			dialog.text = "I am here to put an end to these outrageous acts, and, luckily for you, I propose a diplomatic way. For now... But if the director of this abominable organisation doesn't arrive here for the talks, I will run his business into the ground. After we storm the city, I will leave only cinders behind, and any powder that we find, we will put into the basement of your fort, and blow it up. The same fate will await your plantations, and the Stuyvesant himself will hang on the yardarm of my ship...";
			link.l1 = "...";
			link.l1.go = "doily_14";
		break;
		
		case "doily_14":
			dialog.text = "You will need more than a year to rebuild your colony, and then you will have no time for your schemes and plots. Tell your 'Mynheer Director' everything that I've just said, and don't think these are jokes and empty promises. I've run out of patience, you must understand. Do you understand, Officer?";
			link.l1 = "Everything is perfectly clear, sir Colonel.";
			link.l1.go = "doily_15";
		break;
		
		case "doily_15":
			dialog.text = "Great. Then leave. I give you exactly one day to think this over. If after twenty-four hours Peter Stuyvesant will not be standing here like you are right now, let him blame that on himself.";
			link.l1 = "...";
			link.l1.go = "doily_16";
		break;
		
		case "doily_16":
			DialogExit();
			LAi_SetStayType(pchar);
			SetMainCharacterIndex(GetCharacterIndex("Blaze"));
			pchar = GetMainCharacter();			
			LAi_SetPlayerType(pchar);
			bDisableCharacterMenu = false;//лоченые интерфейсы
			sld = characterFromId("Doily_land");
			sld.dialog.currentnode = "doily_17";
			LAi_SetActorType(sld);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "doily_17":
			dialog.text = "I think that ratchet dog Stuyvesant will come here. And if not - that's his problem!";
			link.l1 = "...";
			link.l1.go = "doily_17_1";
		break;
		
		case "doily_17_1":
			DialogExit();
			npchar.dialog.currentnode = "doily_17";
			AddQuestRecord("Patria", "63");
			Patria_CuracaoParlamenterGo();
		break;
		
		case "doily_18": // Дойли на берегу
			dialog.text = "You've done a good job with the fort, monsieur de Maure. Now we will approach the city gates by land. I will take the cannons from here, the path here is shorter and easier, and you will disembark the company of marines on the Santa-Maria Cape and move to Willemstadt. If you meet enemies on the way, you know what to do. Nobody can be left behind us.";
			link.l1 = "Of course, colonel. I will meet you at the gates!";
			link.l1.go = "doily_19";
		break;
		
		case "doily_19":
			DialogExit();
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			AddQuestRecord("Patria", "61");
			npchar.dialog.currentnode = "doily_10";
			Patria_CuracaoGotoMarch();
		break;
		
		case "doily_20":
			dialog.text = "Well then, it seems like our mission has ended quite successfully. Congratulations, Captain! Oh, excuse me - Vice Admiral! Let's go back on the ships. I will tell my men to stand guard - that fool Stuyvesant will likely not risk attacking us while we retreat, but it won't hurt to be careful.";
			link.l1 = "I'm sure the Dutch will not dare break a treaty that was just signed.";
			link.l1.go = "doily_21";
		break;
		
		case "doily_21":
			dialog.text = "It was a pleasure working with you, monsieur de Maure. I think we will meet once again in Port-Royale or Casterville.";
			link.l1 = "Without a doubt, colonel. Now, let's tell our men to retreat.";
			link.l1.go = "doily_22";
		break;
		
		case "doily_22":
			DialogExit();
			AddQuestRecord("Patria", "64");
			Patria_CuracaoClear();
		break;
		
		case "doily_23":
			dialog.text = "It seems, the Dutch have finally learned that they have no way to approach us from the fort by that narrow path under our artillery fire. And the ones stuck in the city will likely not risk a sortie, unless they are completely mad. Now we will sow some panic: let's bomb the city with our cannons. The men on my ship will see it and they'll make it look like they're preparing to disembark. After an hour or two, Stuyvesant will shit his pants and will be ready to send the truce envoys.";
			link.l1 = "Everything is going according to our plan, colonel! Let's do it!";
			link.l1.go = "doily_24";
		break;
		
		case "doily_24":
			DialogExit();
			Patria_CuracaoTownBombing();
		break;
		
		// голландский парламентер под стенами Виллемстада
		case "holoff":
			dialog.text = "I've arrived here to begin the negotiations. What are your demands?";
			link.l1 = "We demand a meeting with the Company's Director, Peter Stuyvesant. Specifically, we want to talk about the fact that due to his company's fault, as well as his own, Willemstad is currently under threat of destruction.";
			link.l1.go = "holoff_1";
		break;
		
		case "holoff_1":
			dialog.text = "Very well, I'll tell mynheer Stuyvesant about this, and we will arrange a safe route into the city for your delegation...";
			link.l1 = "And what about a safe exit?";
			link.l1.go = "holoff_2";
		break;
		
		case "holoff_2":
			dialog.text = "I don't understand, mynheer?";
			link.l1 = "I said: will you arrange a safe exit from the city for us? I'm not sure about that. I'm afraid, mynheer Stuyvesant may just decide to take our envoys into captivity. For this reason, I invite mynheer Stuyvesant to appear right here for the negotiations.";
			link.l1.go = "holoff_3";
		break;
		
		case "holoff_3":
			dialog.text = "But...";
			link.l1 = "Officer, we dictate the conditions here. Your fleet is destroyed, the garrison cut off from the city, and we will penetrate Willemstad's defense like a fregate penetrates a rowboat if we decide to storm the city. Now, you will receive a letter for mynheer Stuyvesant, and you will give it to him along with our invitation...";
			link.l1.go = "holoff_4";
		break;
		
		case "holoff_4": // перекидываем pchar на офицера и говорим с Дойли
			DialogExit();
			LAi_SetActorType(pchar);
			SetMainCharacterIndex(GetCharacterIndex("Curacao_parlamenter_1"));
			pchar = GetMainCharacter();			
			LAi_SetPlayerType(pchar);
			sld = characterFromId("Doily_land");
			sld.dialog.currentnode = "doily_12";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
			bDisableCharacterMenu = true;//лоченые интерфейсы
		break;
		
		// офицер-испанец на маяке Тринидада
		case "SanJoseSpanish":
			dialog.text = "So, Captain, you've called the truce envoys because you wanted to dictate your demands?";
			link.l1 = "You are absolutely correct, senor. Let me briefly explain to you my reason for arriving in Trinidad – this is our answer for your recent attack on Saint-Pierre. You've damaged the city considerably, and now you will be forced to compensate it. The price of compensation is three hundred thousand Peso. And that is not so much, considering the vile acts your soldiers have committed on Martinique.";
			link.l1.go = "SanJoseSpanish_1";
		break;
		
		case "SanJoseSpanish_1":
			dialog.text = "Excuse me, senor, but what does San Jose have to do with Saint-Pierre? Why does our colony have to pay?";
			link.l1 = "Because the attackers were Spanish, not Dutch or English. Then you will put the bill on Providence for Don de Mendose, along with my sincerest greetings. As you understand, in case you refuse to pay the compensation, I will order my men to disembark, and then San Jose will lose much more. I'm sure your colony's governor will make the right decision. You have one day to respond. I wish you all the best, senores.";
			link.l1.go = "SanJoseSpanish_2";
		break;
		
		case "SanJoseSpanish_2":
			DialogExit();
			npchar.dialog.currentnode = "SanJoseSpanish_3";
			Patria_SanJoseMayakSpanishGo();
		break;
		
		case "SanJoseSpanish_3":
			dialog.text = "";
			link.l1 = "So, as I understand, the governor has made the right decision?";
			link.l1.go = "SanJoseSpanish_4";
		break;
		
		case "SanJoseSpanish_4":
			AddMoneyToCharacter(pchar, 300000);
			dialog.text = "Get your three hundred thousand and get out of our colony.";
			link.l1 = "Excellent, senores. I assure you – this was the simpler way. I hope this will discourage the Dons of Mendos and others from attacking our colonies. Don't forget to send the message to Providence. I wish you well, gentlemen.";
			link.l1.go = "SanJoseSpanish_5";
		break;
		
		case "SanJoseSpanish_5":
			DialogExit();
			Patria_SanJoseMayakSpanishFin();
		break;
		
		// вестовой на 5 задание
		case "fraofficer":
			dialog.text = "Captain Charles de Maure, allow me to report: Chevalier Philippe de Poincy wanted to notify you that Baron Noel Forget is ready to depart for Sint-Maarten and will await you on the pier.";
			link.l1 = "Excellent! Thank you, monsieur.";
			link.l1.go = "fraofficer_1";
		break;
		
		case "fraofficer_1":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload3_back", "none", "", "", "", 10.0);
			Patria_SanMartinSetBaron();
		break;
		
		case "fraofficer_2":
			dialog.text = "Captain Charles de Maure! The Governor General is calling for you right now. A mighty enemy squadron has appeared at the coast of Saint-Christopher!";
			link.l1 = "Then let us waste no time!";
			link.l1.go = "fraofficer_3";
		break;
		
		case "fraofficer_3":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload3_back", "none", "", "", "", 10.0);
			chrDisableReloadToLocation = false;
			Patria_SiegeHovernor();
		break;
		
		// патруль у рудника
		case "engofficer":
			dialog.text = "Who are you? What are you doing here?";
			link.l1 = "Uhh...";
			link.l1.go = "engofficer_1";
		break;
		
		case "engofficer_1":
			dialog.text = "No strangers are allowed to enter here! Who are you, spies? I'll bring you to the commandant's office, they'll deal with you.";
			link.l1 = "But we can't go to the commandant's office...";
			link.l1.go = "engofficer_2";
		break;
		
		case "engofficer_2":
			dialog.text = "If you won't go yourself - we'll just have to drag you by force! Hand over you weapons!";
			link.l1 = "No deal...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Patria_CondotierBeachFight");
		break;
		
		// бывший управляющий рудника
		case "miner":
			dialog.text = "";
			link.l1 = "So, is everything clear?";
			link.l1.go = "miner_1";
		break;
		
		case "miner_1":
			dialog.text = "Yes, sir. The letter is to be handed personally to mynheer Peter Stuyvesant or Mathias Beck.";
			link.l1 = "I'm sure you won't have trouble finding a ship from Willemstad to Cartagena. We gave you all the necessary funds to pay for the trip and for accommodation. And in case you need to - you will confirm your reports in front of the French commission half a year from now?";
			link.l1.go = "miner_2";
		break;
		
		case "miner_2":
			dialog.text = "Sir, I'm loyal to my word.";
			link.l1 = "Very well. Then I wish you luck. This path leads to Willemstad, follow it. It's not far from here.";
			link.l1.go = "miner_3";
		break;
		
		case "miner_3":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "Patria_CondotierOnCuracaoWait", 15.0);
			AddQuestRecord("Patria", "82");
			ReleasePrisoner(npchar);
		break;
		
		// курьер в Капстервиль
		case "cureer":
			dialog.text = "Vice-admiral Charles de Maure, right?";
			link.l1 = "Precisely. Who do I have the honour of speaking with?";
			link.l1.go = "cureer_1";
		break;
		
		case "cureer_1":
			dialog.text = "I have a message to you from Baron Noel Forget. He told you to come to the governor's palace at Casterville as soon as possible.";
			link.l1 = "Oh! Great news! Thank you, I will depart immediately!";
			link.l1.go = "cureer_2";
		break;
		
		case "cureer_2":
			DialogExit();
			chrDisableReloadToLocation = false;
			Patria_EuropePrepare();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload4_back", "none", "", "", "", 10.0);
		break;
		
		case "burden":
			dialog.text = "Greetings, vice-admiral. Baron Forget told me stories about you. A lot of stories. I give you my sincerest thanks for your loyal and brilliant service for the good of France in the colonies, as well as for your help in uncovering the schemes of the swindler de Poincy. Now, me and the Minister of Finance will deal with him personally, and you will take the place of your former commander. At least, for the time being.";
			link.l1 = "But...";
			link.l1.go = "burden_1";
		break;
		
		case "burden_1":
			dialog.text = "No 'buts', vice-admiral! This decision has already been made and approved by the King. I have here an order signed by him personally about assigning you as the de facto Governor General of the French colonies in the Archipelago. We have no better candidates for this position. Your outstanding experience in warfare, your knowledge of the region and the people that are responsible for everything here, your skills and talents are all worthy of this high and respectable position. Let me tell you: I expect that after some time you will be assigned to this position once again, without the 'de facto' part.";
			link.l1 = "But I dreamed of coming back to Paris...";
			link.l1.go = "burden_2";
		break;
		
		case "burden_2":
			dialog.text = "France needs you here! The Minister of Finance is gathering a navy in Europe right now, and our presence here, in the Archipelago, will also not go unnoticed. Your main task will be to strengthen and fortify the colonies and increase the military power of our fleet, while Baron Forget and the French West-Indies trade Company will focus on the trading and domestic development! And who else, if not you, can help prepare the French navy?\nSo, start working, Governor General! I know you don't like sitting in a room all day, but your task doesn't even require it!";
			link.l1 = "At once, your Grace! Orders are not to be questioned!";
			link.l1.go = "burden_3";
		break;
		
		case "burden_3":
			dialog.text = "I'm glad you've understood me correctly. And I will also ask you to pay a visit to the Chevalier de Poincy: he insisted on meeting you. We can't deny him such pleasure before his departure for Paris, can we? You will find him in the prison.";
			link.l1 = "Very well, your Grace...";
			link.l1.go = "burden_4";
		break;
		
		case "burden_4":
			DialogExit();
			DoQuestReloadToLocation("Charles_prison", "goto", "goto19", "Patria_EuropePuancieInPrison");
		break;
	}
} 
