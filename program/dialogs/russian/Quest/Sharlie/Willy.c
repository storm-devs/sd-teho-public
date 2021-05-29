// Вильям Патерсон
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
			dialog.text = "Is there something you want?";
			link.l1 = "No, nothing.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		case "catoche":
			dialog.text = "Hello, monsieur. God damn it, so you're the one that raised all the military strife around here?!";
			link.l1 = TimeGreeting()+", sir. Yes, it was my ship that landed the  descent. What's the matter anyway? Who are you? An Englishman, I suppose?";
			link.l1.go = "catoche_1";
		break;
		
		case "catoche_1":
			dialog.text = "A Scotsman, monsieur. Captain of the English Navy William Patterson. And this is my first mate and right hand, Archibald Calhoun. Thing is, that there is a Spanish fort in the jungles. My mission is to kick the cursed bastards out of the fort, which they has built in a dangerous close to English territory\nRecently we tried to storm it, but bastards have managed to hold out despite of their losses. I'd left for reinforces and...";
			link.l1 = "No need for that now. I've completed your unfinished business, the jungle fort is empty. Spanish commander Diego de Montoya is dead and his squadron has been wiped out as well.";
			link.l1.go = "catoche_2";
		break;
		
		case "catoche_2":
			dialog.text = "What kind of vigilantism is this? What's your motivation for raising up such military action on English territory?";
			link.l1 = "I dare remind you, captain Patterson, that this isn't Belize. What English possession? All this fuss got started due to Don Diego de Montoya and his risky decision to attack me and my ships.";
			link.l1.go = "catoche_3";
		break;
		
		case "catoche_3":
			dialog.text = "Ehem... and what reason did Don Diego have to attack you, huh captain?";
			link.l1 = "He and I have a longstanding feud... Ever since the day when the squadron he was leading attacked St. Pierre and a little bit later was eliminated with my direct participation.";
			link.l1.go = "catoche_4";
		break;
		
		case "catoche_4":
			dialog.text = "Shiver my timbers! I needed that venerable caballero alive! I was going to interrogate him on why he set up a military base in the jungle. It couldn't have been for no reason...";
			link.l1 = "I'm sorry, but he isn't able to tell you anything now. Anyway, the fort may contain wounded soldiers from the garrison. Is there a chance they could talk?";
			link.l1.go = "catoche_5";
		break;
		
		case "catoche_5":
			dialog.text = "Soldiers...Oh, what's the use of some hardheaded ramrods!... Where's Don Diego's corpse? He could've had important documents on him!";
			link.l1 = "I left Don Diego on the ground of the arms fort. If you need him so bad, you can find him there. I don't think he can run off.";
			link.l1.go = "catoche_6";
		break;
		
		case "catoche_6":
			dialog.text = "Eh. And who asked you to bud into someone else's business... You've caused me a bad enough headache...";
			link.l1 = "Captain, I don't understand why you reprimand me. I've done your job, put my own people into battle, risked my own life, and yet you're displeased. All you have to do now is inform Port Royal of your success in the mission and all of your affairs. I won't claim any credit for your glory, I assure you.";
			link.l1.go = "catoche_7";
		break;
		
		case "catoche_7":
			dialog.text = "Claim credit? What do you mean by glory?! You don't get it at all... Eh, fine. Farewell, sir.";
			link.l1 = "All the best to you as well!";
			link.l1.go = "catoche_8";
		break;
		
		case "catoche_8":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "GuardOT_OpenCatocheDoor", 10.0);
			sld = CharacterFromID("Archy");
			LAi_CharacterEnableDialog(sld);
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "reload1", "none", "", "", "", 7.0);
			AddQuestRecord("Guardoftruth", "57");
		break;
		
		case "isladevieques":
			PlaySound("VOICE\Russian\sharlie\Willie Paterson.wav");
			dialog.text = "Man, gossips don't lie that you have nine lives like a cat! "+TimeGreeting()+", monsieur de Maure. You don't look so well...";
			link.l1 = TimeGreeting()+", mr. Patterson. I have to say, you and your friend Archibald played your roles and fooled me pretty well, Fuck you all! I didn't even see it coming...";
			link.l1.go = "isladevieques_1";
		break;
		
		case "isladevieques_1":
			dialog.text = "Hey, don't swear before the gates of Holy Land. You didn't see it coming? I am flattered: I have fooled one of the most famous intrigant of the archipelago. The diary idea was brilliant, don't you think so?\nI had to lure you to some obscure place, killing you in open field would be a scandal, you are a close friend of Philippe de Poincy, am I correct? Now you are going to disappear without any trails left and no one will ever know how.";
			link.l1 = "So, everything that Calhoun told me... was a lie?";
			link.l1.go = "isladevieques_2";
		break;
		
		case "isladevieques_2":
			dialog.text = "Not at all. I had really found poor Archibald at this place. He didn't write any memoirs though, the diary you have found in his room was written at my bidding specially for you, monseniour de Maure\nI have been keeping my eye on you since we met at Cape Catoche. It was you who took the map of Two Appearances from don Diego's corpse? Don't deny it, I know it was you.";
			link.l1 = "You know about the Guardian of Truth as well?";
			link.l1.go = "isladevieques_3";
		break;
		
		case "isladevieques_3":
			dialog.text = "That's a stupid question. Of course, I do. And I know that you have the Chief's  Claw on you too. And soon you will give back those items, which do not belong to you.";
			link.l1 = "I'm glad you don't wobble like Don Diego. I appreciate honestly and directness. As I understand you have the compass, the Arrow of the Way?";
			link.l1.go = "isladevieques_4";
		break;
		
		case "isladevieques_4":
			dialog.text = "Haw-haw! Well, we'll be honest right down til the end... Do you really believe, sir, that I'm such an idiot, like you and Don Diego, that I would carry around such precious object with me? The compass is on Jamaica and not even in Port Royal, but in a place where no one would even think about looking and under a safe lock. But you won't need that information.";
			if (CheckAttribute(pchar, "questTemp.Guardoftruth.OfficerKill"))
			{
				link.l1 = "As I understand, you've already buried me, mr. Patterson? I dare proclaim that the cat has one life left!.. Where are my officers?";
				link.l1.go = "isladevieques_5_1";
			}
			else
			{
				link.l1 = "As I understand, you've already buried me, mr. Patterson? I dare proclaim that the cat has one life left!..";
				link.l1.go = "isladevieques_5_2";
			}
		break;
		
		case "isladevieques_5_1":
			if (CheckAttribute(pchar, "questTemp.Guardoftruth.GirlKill"))
			{
				dialog.text = "Worried for your lady friend, captain? Your woman is lying over there in the bushes with a hole in her forehead. She's laid out the way for you and you will soon join alongside her. I say, such a pretty girl she was! Hope you fucked her more than once?";
				link.l1 = "C'est un fils de pute! You will pay for that you encul?!";
				link.l1.go = "isladevieques_6";
			}
			else
			{
				dialog.text = "Your officers have laid out the road for you, monsieur de Maure. They're lying over there in the bushes. Soon you'll join alongside them.";
				link.l1 = "We'll see about that!";
				link.l1.go = "isladevieques_6";
			}
		break;
		
		case "isladevieques_5_2":
			dialog.text = "We'll make sure it really remains your last.";
			link.l1 = "We'll see about that!";
			link.l1.go = "isladevieques_6";
		break;
		
		case "isladevieques_6":
			dialog.text = "You make me laugh. One against a whole troop! Anyway, enough chatting... Aim your muskets! Fire!";
			link.l1 = "...";
			link.l1.go = "isladevieques_7";
		break;
		
		case "isladevieques_7":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешить драться patch-8
			LAi_ActorRunToLocation(npchar, "quest", "teleport", "IslaDeVieques_HouseEntrance", "quest", "mushketer", "GuardOT_WillyGetReady", 10.0);
			for(i=1; i<=5; i++)
			{
				sld = CharacterFromID("GuardOT_willymushketer_"+i);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "GuardOT_WillyMushketerDie");
			DoQuestFunctionDelay("Terrapin_SetMusic", 0.2);
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
	}
}
