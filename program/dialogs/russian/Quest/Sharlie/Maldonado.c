// Алонсо де Мальдонадо
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
			dialog.text = "Is there something you need?";
			link.l1 = "No, nothing.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		case "ksochitam":
			dialog.text = "Stop, captain "+GetFullName(pchar)+"...";
			link.l1 = "Somehow, I'm not even surprised by the Spanish soldiers' presence here... I guess I've just got used to somebody always on my tail. What are you looking for on this god-forsaken island, Castilian? Looking for a quick way to kick up your heels?";
			link.l1.go = "ksochitam_1";
		break;
		
		case "ksochitam_1":
			dialog.text = "My name is Alonso de Maldonado. That might not mean anything to you, but Diego de Montoya might ring a few bells. He was my best friend. He saved my life and now his blood is on your hands.";
			link.l1 = "I take it you've followed me here to seek out revenge?";
			link.l1.go = "ksochitam_2";
		break;
		
		case "ksochitam_2":
			dialog.text = "I'm not just looking for revenge. As I understand you have Kukulcan's mask?";
			link.l1 = "Well, I'll be dammed! Another treasure hunter! Come for some unfinished business started by Don Diego?";
			link.l1.go = "ksochitam_3";
		break;
		
		case "ksochitam_3":
			dialog.text = "I'm not interested in treasures. I've seen riches in Tayasal. Miguel Dichoso wasn't able to haul out much more than a morsel. The mask is what I want.";
			link.l1 = "You've been to Tayasal?  That's hard to believe.  As I remember, Dichoso was the one and only survivor of the expedition.";
			link.l1.go = "ksochitam_4";
		break;
		
		case "ksochitam_4":
			dialog.text = "I went to Tayasal twenty years before Dichoso ever got there. The same time that mad sorcerer Kanek used that despicable human sacrifice ritual to hide the mask on this island.";
			link.l1 = "I can't believe what I'm hearing! You're from the same band of conquistadors that was brought to sacrifice when the Guardian of Truth was being created? You were all dead!";
			link.l1.go = "ksochitam_5";
		break;
		
		case "ksochitam_5":
			dialog.text = "Not all of us. I survived.";
			link.l1 = "Why did the Itza decide to spare you? What makes you so different?";
			link.l1.go = "ksochitam_6";
		break;
		
		case "ksochitam_6":
			dialog.text = "You wouldn't understand. Hell, I didn't understand either. No one spared me. I remember it like it was yesterday... After that savage took a dagger and filleted a patch of skin off Casco's back right before putting him to death and then started howling like a maniac, I think I got sucked into the idol. I woke up far away from Tayasal twenty years later in what felt like a mere moment!";
			link.l1 = "A space-time funnel... God damn it, everything Ksatl Cha said was right on the dot! How did you find out about the mask? What do you need it for?";
			link.l1.go = "ksochitam_7";
		break;
		
		case "ksochitam_7":
			dialog.text = "I must stop a spawn of hell, summoned by a mad Indian sorcerer. This abomination aims to make a bonfire of our world!";
			link.l1 = "Hmm... You've spoken to father Vincento, haven't you? The Inquisitor is holding with the hare and running with the hounds. Surprise, surprise. He's sent you to track me down for a battle royale? Well done! You've completed your mission, Don Alonso!";
			link.l1.go = "ksochitam_8";
		break;
		
		case "ksochitam_8":
			dialog.text = "The lord fortifies my hand in battle against evil. I will return to Tayasal and use the mask to seal the gates shut forever. And no demon in human form will cross over into our world.";
			link.l1 = "There's just one little problem in your plan, Don Alonso. The demon is ALREADY among us. All we need to do is to not let him LEAVE through these gates. He won't be able to do that as long as you keep the mask away from him.  ";
			link.l1.go = "ksochitam_9";
		break;
		
		case "ksochitam_9":
			dialog.text = "It'll take more than that. Whoever of us is right, one thing is for sure: the gates must be closed forever. And there's only one way to do that: destroy the mask on the altar in Tayasal. At that moment, the demon will stripped of all its power.";
			link.l1 = "Hm. I agree that it's our best bet... How are you planning on making it to Tayasal? Do you know the way there?";
			link.l1.go = "ksochitam_10";
		break;
		
		case "ksochitam_10":
			dialog.text = "The easy path we used back then is no longer exists. Roads are buried with stones and lost in jungles. There is another way to the city, but it long and dangerous. The path starts at the Northerst bay of Yucatan\nWith a help of father Vincento and don Ramon de Mendoza I will gather a squad of elite soldiers and we will fight our way through selva protected by Itza savages. It won't be easy, but God will grant us strength and bravery for our fight for the name of our faith.";
			link.l1 = "Don Alonso, my aspirations happen to coincide with yours. Isn't it time we put the grudge aside for a moment and combine forces? Together we'd have a better chance of completing this crusade successfully.";
			link.l1.go = "ksochitam_11";
		break;
		
		case "ksochitam_11":
			dialog.text = "I am a Spanish soldier. I do not form alliances with heretics nor do I make deals with Frenchmen. Besides, I've already declared my vendetta to you for Don Diego. A life for a life!";
			link.l1 = "You're as stubborn as an ox, Don Alonso! There you stand preaching that the world is threatened by a great evil and yet you refuse my help in such an astronomical task!";
			link.l1.go = "ksochitam_12";
		break;
		
		case "ksochitam_12":
			dialog.text = "I make the decisions now, not father Vincento!  Say your prayers and prepare to die, French captain!..";
			link.l1 = "Oh, I've heard that so many times in the past few months! On guard, hard-headed caballero!";
			link.l1.go = "ksochitam_13";
		break;
		
		case "ksochitam_13":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			for (i=1; i<=2; i++)
			{
				sld = characterFromId("Maldonado_soldier_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			for (i=1; i<=2; i++)
			{
				sld = characterFromId("Maldonado_mushketer_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "Ksochitam_MaldonadoDie");
			AddDialogExitQuest("MainHeroFightModeOn");
			if (MOD_SKILL_ENEMY_RATE > 4) Ksochitam_CreateMaldonadoHelpers();
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
