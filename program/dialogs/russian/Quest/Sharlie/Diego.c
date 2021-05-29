// Диего де Монтойя
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
			dialog.text = "Is there something want?";
			link.l1 = "No, nothing.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		case "patrol":
			dialog.text = TimeGreeting()+", "+GetFullName(npchar)+", chief of San Jose patrol. We've received a message concerning suspicious behaviour in the outskirts of this town. Would you be so kind as to explain to us who you are and what you're up to?";
			link.l1 = "Captain "+GetFullName(pchar)+", senor officer. I am here under the authority and direct instructions of inquisitor Father Vincento. Here is a document confirming my authorization.";
			link.l1.go = "patrol_1";
		break;
		
		case "patrol_1":
			dialog.text = "All right... Everything looks fine. It's filled out properly with the signature of the Inquisitor. My apologies for my suspicion. What are you doing at the lighthouse?";
			link.l1 = "I'm not authorized to answer such questions. If you are genuinely interested as to the purpose of my work for the Inquisitor, you would better refer directly to him in Santiago for clarification. You are an officer, surely you have knowledge of military and service secrets. The only thing I can tell you is that I am investigating the circumstances of a wrecked Spanish ship.";
			link.l1.go = "patrol_2";
		break;
		
		case "patrol_2":
			dialog.text = "My apologies once again, monsieur. I won't dare to delay you any further... ah, one moment! Did I just see that or was it just my imagination? What an interesting dagger you have! Can you show it to me?";
			link.l1 = "Make sure you won't forget to give it back. It's very  to me.";
			link.l1.go = "patrol_3";
		break;
		
		case "patrol_3":
			dialog.text = "Gosh! I know this dagger, I saw it drawn in once of the library books! This is the dagger of Cortes himself! It's branded right here... Monsieur, please don't refuse. Let me have this dagger! I collect ancient and personalized weaponry and this is simply and incredible specimen. I'll pay well for it.";
			link.l1 = "Senor, this dagger is not for sale. I received it as a gift and I'm not bent on selling it off to anyone. Give it back, please.";
			link.l1.go = "patrol_4";
		break;
		
		case "patrol_4":
			dialog.text = "You won't even be happy with five hundred gold doubloons? That's a whole heap of money. You could buy a ship with it!";
			link.l1 = "No. I have a ship already and the dagger is a one of a kind. I will not sell it.";
			link.l1.go = "patrol_5";
		break;
		
		case "patrol_5":
			dialog.text = "Eh, that's too bad... All right, take your valuable. I won't dare disturb you any longer. Good luck!";
			link.l1 = "All the best, officer.";
			link.l1.go = "patrol_6";
		break;
		
		case "patrol_6":
			DialogExit();
			AddQuestRecord("Guardoftruth", "42");
			LAi_ActorGoToLocation(npchar, "reload", "reload2", "none", "", "", "GuardOT_ClearMayakPatrol", 12.0);
			for(i=1; i<=3; i++)
			{
				sld = characterFromId("GOT_spamayaksold_"+i);
				sld.lifeday = 0;
				LAi_SetActorType(sld);
				LAi_ActorGoToLocation(sld, "reload", "reload2", "none", "", "", "", 10.0);
			}
		break;
		
		case "shore":
			PlaySound("VOICE\Russian\Sharlie\Diego De Montoya.wav");
			dialog.text = "Enough! I want to have a talk with him...";
			link.l1 = "So, I see Diego de Montoya himself right in front of me... But pardon me, senor. We've met before, haven't we? Oh yes, that's right. Trinidad, at local lighthouse. But I am sure that there you called yourself something else...";
			link.l1.go = "shore_1";
		break;
		
		case "shore_1":
			dialog.text = "Your memory serves you well, sir. Well, you're not the only one capable of sparking intrigue and waging wars behind the scenes. I am well informed of your undying desire to see me. Well, looks like your wish has come true.";
			link.l1 = "This wasn't exactly the type of encounter I was hoping for, senor.";
			link.l1.go = "shore_2";
		break;
		
		case "shore_2":
			dialog.text = "Well, it is what it is. But I will give you a chance to get out of here alive if you give me your dagger.";
			link.l1 = "Has your passion for collecting really sent you that far down the pipes, caballero, that you've prepared such a well thought out trap for me?  Oh, I don't think so. The Guardian of Truth keeping you the trot, am I far off?";
			link.l1.go = "shore_3";
		break;
		
		case "shore_3":
			dialog.text = "I have no idea what you're talking about. The dagger must return to where it belongs and that's all you need to know. You didn't want to give it up for gold, so now you're going to give it up for your own life.";
			link.l1 = "Do you really think, senor, that I'm going to believe in what you' just told me? You've already decided that I'm not leaving this bay, haven't you?";
			link.l1.go = "shore_4";
		break;
		
		case "shore_4":
			dialog.text = "And what if I'll give you my word?";
			link.l1 = "The word for a 'frog eater'? Hm...";
			link.l1.go = "shore_5";
		break;
		
		case "shore_5":
			dialog.text = "Monsieur, I'm giving you one last chance. Either you hand over the dagger I'm interested in or I'll be looting your dead body in a few minutes. Resistance is futile we've got an overwhelming advantage in numbers.";
			if (CheckAttribute(pchar, "questTemp.Guardoftruth.SanAntonio")) link.l1 = "You have surprised me, senor, that's for sure. Do you really think that I'm such a bullheaded imbecile that I've just put my head in the jaws of a shark without bothering to snag my harpoon? Guys, kill them!";
			else link.l1 = "Real power is not in numbers, but in skills, senior!";
			link.l1.go = "shore_6";
		break;
		
		case "shore_6":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "goto", "goto5", "none", "", "", "", 10.0);
			if (CheckAttribute(pchar, "questTemp.Guardoftruth.SanAntonio"))
			{
				PlaySound("interface\abordage_wining.wav");
				PlaySound("interface\abordage_wining.wav");
				for(i=1; i<=10; i++)
				{
					sld = characterFromId("GuardOT_Oursoldier_"+i);
					LAi_SetWarriorType(sld);
					ChangeCharacterAddressGroup(sld, "Shore15", "reload", "reload1_back");
					LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
				}
			}
			sld = CharacterFromID("spa_baseprisoner");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			for(i=1; i<=13; i++)
			{
				sld = characterFromId("GOT_spashore_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "GuardOT_DiegoShoreGuardDie");
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
	}
}
