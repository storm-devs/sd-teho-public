// Addon-2016 Jason, французские миниквесты (ФМК) Мартиника
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
		
		// квестодатель
		case "carpenter":
			dialog.text = TimeGreeting()+", captain. Allow me to introduce myself - "+GetFullName(npchar)+". Although we've already met not long ago, I doubt you remembered me.";
			link.l1 = "Greeting, monsieur. And where could I see you before?";
			link.l1.go = "carpenter_1";
		break;
		
		case "carpenter_1":
			sTemp = "lugger 'Adeline'";
			if (pchar.questTemp.Sharlie.Ship == "sloop") sTemp = "sloop 'Black Dog'";
			dialog.text = "Our shipyard. You have purchased "+sTemp+". Remember now? I am a carpenter there.";
			link.l1 = "Yeah, I really did buy that ship. So what do you want, monsieur "+GetFullName(npchar)+"?";
			link.l1.go = "carpenter_2";
		break;
		
		case "carpenter_2":
			sld = characterFromId("FortFrance_shipyarder");
			dialog.text = "Our ship-builder "+GetFullName(sld)+" wants to talk. I believe he has some sort of business proposal. He saw your ship in our port and sent me to find you. Would you kindly accept the invitation?";
			link.l1 = "Fine. I'll pay your boss a visit once I finish my business in town.";
			link.l1.go = "carpenter_3";
		break;
		
		case "carpenter_3":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload5_back", "none", "", "", "", 10.0);
			chrDisableReloadToLocation = false;
			pchar.questTemp.FMQM = "begin";
			AddQuestRecord("FMQ_Martinique", "1");
			SetFunctionTimerCondition("FMQM_Denial", 0, 0, 2, false);
		break;
		
		case "officer":
			PlaySound("VOICE\Russian\soldier_arest_4.wav");
			dialog.text = "Well-well... Fresh smugglers in my net!";
			link.l1 = "Eh...";
			link.l1.go = "officer_1";
		break;
		
		case "officer_1":
			dialog.text = "Cut the crap! There are several barrels of resin inside this shipyard. Captain, you have delivered them to your partner in crime. Both of you are under arrest and I am confiscating the cargo by the name of law!";
			link.l1 = "...";
			link.l1.go = "officer_2";
		break;
		
		case "officer_2":
			DialogExit();
			LAi_SetActorType(npchar);
			sld = characterFromId("FortFrance_shipyarder");
			LAi_SetActorType(sld);
			LAi_ActorDialogNow(sld, pchar, "", -1);
		break;
		
		case "officer_3":
			dialog.text = "Don't play stupid, master! What barrels? You know that I am talking about the very barrels you've recently unloaded from this sailor's vessel! You both will rot in the dungeons! Move, fuckers...";
			link.l1 = "";
			link.l1.go = "officer_4";
		break;
		
		case "officer_4":
			DialogExit();
			LAi_SetActorType(npchar);
			sld = characterFromId("FortFrance_shipyarder");
			LAi_SetActorType(sld);
			LAi_ActorDialogNow(sld, pchar, "", -1);
		break;
		
		case "officer_5":
			PlaySound("VOICE\Russian\soldier\soldier arest-02.wav");
			dialog.text = "This resin, my dear master shipbuilder, is a good of strategic value which is under direct control of our governor! Since you claim it to be all yours - have it your way. You are under arrest, you will spend this night in our comfortable dungeons and tomorrow you will give us a detailed report of how you got them and for what purpose. Don't worry, we'll learn everything eventually. You, captain, are free to go. It's your lucky day.";
			link.l1 = "";
			link.l1.go = "officer_6";
		break;
		
		case "officer_6":
			DialogExit();
			LAi_SetActorType(pchar);
			LAi_ActorTurnToCharacter(pchar, characterFromID("FMQM_officer"));
			sld = characterFromId("FortFrance_shipyarder");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload1", "FortFrance_town", "officers", "reload5_3", "FMQM_ArestContinue", 8);
		break;
		
		case "officer_7":
			PlaySound("VOICE\Russian\soldier_arest_2.wav");
			dialog.text = "I knew there was something wrong with this ship... Looks like I have underestimated you, captain.";
			link.l1 = "Exactly, lieutenant. I am not that stupid. Your jolly cooperation with the shipbuilder is compromised now.";
			link.l1.go = "officer_8";
		break;
		
		case "officer_8":
			dialog.text = "I see. Congratulations, you must be talented since you've managed to track me down and catch me by surprise. Now tell me what do you want.";
			link.l1 = "Isn't that clear? I need my resin back. The resin you and your pal have stolen from me.";
			link.l1.go = "officer_9";
		break;
		
		case "officer_9":
			dialog.text = "Fine. You can have it, but only a half of your batch. That's all I have stashed here. Hope you'll find it enough, since that is all I can offer.";
			link.l1 = "Are you still trying to screw me? Compensate me the other half with gold or with goods stashed behind you.";
			link.l1.go = "officer_10";
		break;
		
		case "officer_10":
			dialog.text = "Not an option. Address our mutual friend for the other half.";
			link.l1 = "Are you fucking kidding me? Do you really believe that "+GetFullName(characterFromId("FortFrance_shipyarder"))+" will give me my barrels back? That's ridiculous.";
			link.l1.go = "officer_11";
		break;
		
		case "officer_11":
			dialog.text = "Captain, take all the resin I have, have your life and get the hell out of here. I can add to this bargain my promise not to cause any troubles for you in St. Pierre. That's my final offer.";
			link.l1 = "Since when my life is a part of the bargain? Ha!";
			link.l1.go = "officer_12";
		break;
		
		case "officer_12":
			dialog.text = "Looks like you still feel yourself invincible after the fight, captain. Let me explain you this: those were rookies, untrained and unmotivated, you have no chance against my squad. I could have you killed right here without any bargaining, but I value the lives of my men. Someone of them might get injured or even killed in the process of killing you. So you either accept my generous offer or stay here forever. Time to choose.";
			link.l1 = "Screw you, lieutenant, but I am forced to accept your terms. I am heavily outmatched here.";
			link.l1.go = "officer_13";
			link.l2 = "Too overconfident, lieutenant? I suppose, I should teach you and your mercenaries a lesson. You fucking resin dog!";
			link.l2.go = "officer_15";
		break;
		
		case "officer_13":
			dialog.text = "You are a reasonable man, captain. Take you barrels and get lost. I should warn you, pointing fingers at me in front of the governor won't help. I will change a location of my stash today. Save your time.";
			link.l1 = "Wasn't going to. I understand a futility of addressing the authorities.";
			link.l1.go = "officer_14";
		break;
		
		case "officer_14":
			dialog.text = "Hurry, I don't have much time to spare.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("FMQM_PeaceExit");
		break;
		
		case "officer_15":
			DialogExit();
			AddDialogExitQuestFunction("FMQM_BattleExit");
		break;
		
		case "greguar":
			dialog.text = "Oh! What a meeting! Greeting, monseniour! Having a great night?";
			link.l1 = "Good night... ah, it's you! I remember you, we met in the very first day of my arrival to the Caribbean. Monseniour Gregoire Valinnie.";
			link.l1.go = "greguar_1";
		break;
		
		case "greguar_1":
			dialog.text = "Glad you still remember. I can see that you are a captain now. Captain "+GetFullName(pchar)+". Congratulations.";
			link.l1 = "Thanks...";
			link.l1.go = "greguar_2";
		break;
		
		case "greguar_2":
			dialog.text = "You look troubled, captain. What happened here? Something is wrong?";
			link.l1 = "Something is wrong...";
			link.l1.go = "greguar_3";
		break;
		
		case "greguar_3":
			dialog.text = "Monsieur, rather than standing in the middle of the street let's go to a tavern instead. You could use a pint or two. We can talk there. Come on!";
			link.l1 = "...";
			link.l1.go = "greguar_4";
		break;
		
		case "greguar_4":
			DialogExit();
			NextDiag.CurrentNode = "greguar_5"; 
			FreeSitLocator("Fortfrance_tavern", "sit_front4");
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload4_back", "Fortfrance_tavern", "sit", "sit_front4", "FMQM_InTavern", -1);
		break;
		
		case "greguar_5":
			LAi_SetSitType(Pchar);
			dialog.text = "Pour it up, captain...";
			link.l1 = "Go for it..";
			link.l1.go = "greguar_6";
		break;
		
		case "greguar_6":
			LAi_Fade("", "");
			WaitDate("",0,0,0,1,20);
			RecalculateJumpTable();
			dialog.text = "Wooh... Now please tell me what's wrong? You look like that guy they hanged last week. He had the very same face while standing on the gallows.";
			link.l1 = "See, monseniour Gregoire... Let's just say that I have troubles on work.";
			link.l1.go = "greguar_7";
		break;
		
		case "greguar_7":
			dialog.text = "Captain, you can share everything with me. I am not going to sell you out to the governor or the commandant, you can trust me on that. Don't you trust me?";
			link.l1 = "I trust you, monseniour.";
			link.l1.go = "greguar_8";
		break;
		
		case "greguar_8":
			dialog.text = "Then confess and put some ease on your soul. I might be in a position to help you.";
			link.l1 = "A local ship builder hired me to plunder a Spanish caravan of Port-au-Spain. He had a strong need in resin, that was my target and he promised to pay fifteen doubloons per barrel. I've tracked the caravan down, plundered it and brought the goods here. They had put my vessel under repairs and unshipped the barrels to the shipyard. We were about to finish our deal when that officer had shown up... I wonder how could he find out?";
			link.l1.go = "greguar_9";
		break;
		
		case "greguar_9":
			dialog.text = "";
			link.l1 = "That was it, they had us. I think I should give a credit to the shipbuilder - he thrown all the blame on himself, told them the resin is his property and I have nothing to do with it. In the end, he is arrested and my coin is gone. The mess with the Spanish caravan was a waste of time and money, though I was lucky not to end up in prison. Pour it up again, monseniour Gregoire.";
			link.l1.go = "greguar_10";
		break;
		
		case "greguar_10":
			dialog.text = "So, the ship builder is under arrest?";
			link.l1 = "Well, yeah. He was taken to prison by the very officer I was talking about. You should have seen them.";
			link.l1.go = "greguar_11";
		break;
		
		case "greguar_11":
			dialog.text = "Yes, I saw them both, though I had no idea that lieutenant Felicien Gronier could possibly arrest his old friend.";
			link.l1 = "Wh... what did you just say?";
			link.l1.go = "greguar_12";
		break;
		
		case "greguar_12":
			dialog.text = "You heard right. Lieutenant Felicien Gronier and shipbuilder "+GetFullName(characterFromId("FortFrance_shipyarder"))+" are old friends. They used to serve together in the army back in Europe. Gronier has stayed in the military and "+GetFullName(characterFromId("FortFrance_shipyarder"))+" has managed to start his own business.";
			link.l1 = "So they know each other... Now I see...";
			link.l1.go = "greguar_13";
		break;
		
		case "greguar_13":
			dialog.text = "My dear "+pchar.name+", it looks like you had been tricked. You are still a newcomer here and they had used it. I bet one hundred doubloons that monsieur "+GetFullName(characterFromId("FortFrance_shipyarder"))+" will be walking around his shipyard again in three days or less.";
			link.l1 = "It seems you are right, monsieur. They have screwed me. No way that officer could know about the resin. Perfect timing too.";
			link.l1.go = "greguar_14";
		break;
		
		case "greguar_14":
			dialog.text = "This is the Caribbean, monseniour"+pchar.name+". Get used to it. Forget about looks, the worst scum here always looks like an honored nobleman.";
			link.l1 = "I heard this line somewhere before... What should I do with them? Should I address the governor?";
			link.l1.go = "greguar_15";
		break;
		
		case "greguar_15":
			dialog.text = "I fear that in this case "+GetFullName(characterFromId("FortFrance_shipyarder"))+" will tell another story to them and you'll end up in prison.";
			link.l1 = "Figures. Very well then! Since the law is not on my side, I'll do it in my way damn it! I am not going to give up just like that.";
			link.l1.go = "greguar_16";
		break;
		
		case "greguar_16":
			dialog.text = "Please calm down "+pchar.name+". It's the anger and rum talking, not you. Have a sleep and then think about it again. Maybe it'd be best for you to let it go. Lieutenant Felicien Gronier and "+GetFullName(characterFromId("FortFrance_shipyarder"))+" are powerful people here, they are way above your league. Don't do anything stupid.";
			link.l1 = "We'll see. Thank you for enlightening me. It's good that met you.";
			link.l1.go = "greguar_17";
		break;
		
		case "greguar_17":
			dialog.text = "Be careful. Keep in mind what I've told you.";
			link.l1 = "I will. Now let's have one last drink!";
			link.l1.go = "exit";
			AddDialogExitQuest("FMQM_OutTavern");
		break;
		
		case "greguar_18":
			dialog.text = "Captain "+GetFullName(pchar)+"!";
			link.l1 = "Oh, monseniour Gregoire! You again!";
			link.l1.go = "greguar_19";
		break;
		
		case "greguar_19":
			dialog.text = "Yes. After our tavern talk I made inquiries regarding lieutenant Felicien Gronier. Turns out that he asked for a ten days leave not long ago. His petition was approved. I saw him today, he took a longboat to a tartane which soon sailed to Guadeloupe. She's called the Topaz\nI told you everything, it's your call now. I am sure that you can see the pattern in Gronier's sudden call to take a leave and sail away from the island on a fresh built tartane.";
			link.l1 = "Hell, it's crystal for me now, that's for sure! This tartane has my resin stored in a cargo hold! Monseniour Gregoire thank you, you really came through! Is there anything I could do for you in return?";
			link.l1.go = "greguar_20";
		break;
		
		case "greguar_20":
			dialog.text = "Oh, come on my friend. We are noblemen, we should be helping each other. This is how we live. I believe you would have done the same were I in your shoes. Don't waste a minute, sail North and find the officer. Do not engage into combat, just track him down and find out what he is up to. Hurry, captain!";
			link.l1 = "Thank you again!";
			link.l1.go = "exit";
			AddDialogExitQuest("FMQM_HurryToSea");
		break;
		
		case "pirate":
			dialog.text = "What are you looking at? What do you want here?";
			link.l1 = "Hey pal, I am after my goodies. See those barrels over there? It's my resin for which they didn't pay me a dime.";
			link.l1.go = "pirate_1";
		break;
		
		case "pirate_1":
			dialog.text = "Are you an idiot or something? Get lost while you still can!";
			link.l1 = "I put too much effort to get this resin to allow a few filthy scums to stop me.";
			link.l1.go = "pirate_2";
		break;
		
		case "pirate_2":
			dialog.text = "We will bury your fancy suit here!";
			link.l1 = "The number of bastards are about to decrease today!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("FMQM_ShoreFight");
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
