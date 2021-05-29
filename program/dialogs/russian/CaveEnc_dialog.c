// пещерные энкаунтеры
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i;
	string sTemp, sGroup;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	sTemp = "CaveBandos" + locations[FindLocation(npchar.location)].index + "_";
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "Do you want anything?";
			link.l1 = "No, nothing.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		case "CaveBanditosSit":
			if (drand(2) == 1) 
			{
				dialog.text = NPCStringReactionRepeat("Whoa-ho, look who's there! Well, today is your lucky day, buddy. We're good guys, see, cooking some food and stuff... I am not inviting you to our dinner, but you should get lost while you still can.", "Get lost now and don't bother us. Come back tomorrow - and don't forget to bring your purse with you, ha-ha-ha!", "Don't make me mad, sailor! Do you still remember where the entrance to the cave is? There you should go now, very, very quick...", "Well, now you've crossed the line, buddy! Guess I'll have to tear myself away from my affairs and deal with you, asshole!", "block", 1, npchar, Dialog.CurrentNode);
				link.l1 = HeroStringReactionRepeat("So very kind of you, buddy...", "I see you're quite a joker...", "Alright, keep frying your flat cakes, then...", "Now we're talking, ha-ha!", npchar, Dialog.CurrentNode); 
				link.l1.go = DialogGoNodeRepeat("exit_talk", "exit", "exit", "fight", npchar, Dialog.CurrentNode);
			}
			else
			{
				dialog.text = LinkRandPhrase("Whoa, good heavens! No need to go hunting the prey - it's already here... Hey, guys - let's shake this fop, will we?","No one invited you here, buddy... But it's so good that you are here, anyway. Let's see now, just how hefty your purse is!","No one dragged you here by force, he-he... But if you're already here, guess we'll tickle you a bit to see what drops out of your pockets...");
				link.l1 = LinkRandPhrase("Now I will make shorter your tongue a bit...","I hope your skills with a saber match your wits, flapjaw!","Well, seems that it's time to make a couple more holes in your perishable body...");
				link.l1.go = "fight";
			}
			NextDiag.TempNode = "CaveBanditosSit";
		break;
		
		case "CaveBanditosStay":
			dialog.text = LinkRandPhrase("Whoa, good heavens! No need to go hunting the prey - it's already here... Hey, guys - let's shake this fop, will we?","No one invited you here, buddy... But it's so good that you are here, anyway. Let's see now, just how hefty your purse is!","No one dragged you here by force, he-he... But if you're already here, guess we'll tickle you a bit to see what drops out of your pockets...");
			link.l1 = LinkRandPhrase("Now I will make shorter your tongue a bit...","I hope your skills with a saber match your wits, flapjaw!","Well, seems that it's time to make a couple more holes in your perishable body...");
			link.l1.go = "fight";
		break;
		
		case "CaveBanditosTreasure":
			dialog.text = NPCStringReactionRepeat("Get lost, buddy. It's nothing to do for you here!", "Hey, I am asking in a friendly way: get lost. You never know what can happen...", "Last warning: if you don't get lost right now, you'll regret you came here.", "That's it, buddy, you asked for troubles.", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Don't tell me what to do, alright?", "And what's so special down there? Just a cave, nothing more...", "Oh, come on now...", "Ha! Well, let's see who's better, maggot!", npchar, Dialog.CurrentNode); 
			link.l1.go = DialogGoNodeRepeat("exit", "exit", "exit", "fight", npchar, Dialog.CurrentNode);
			NextDiag.TempNode = "CaveBanditosTreasure";
		break;
		
		case "CaveCaribSit":
			if (drand(2) == 2) 
			{
				dialog.text = NPCStringReactionRepeat("Paleface go away. He be happy that "+npchar.name+"  kind. Gods take pity on you today.", "Get out from my cave, before me and my brothers not angry!", "Get out, paleface dog!", "Your luck and life is over, white dog!", "block", 1, npchar, Dialog.CurrentNode);
				link.l1 = HeroStringReactionRepeat("Well, thank you, buddy, very kind of you...", "This cave is not yours, and I go where I want.", "Take it down a notch, swamp spawn.", "Now I'm gonna stuff these words back into your throat, animal...", npchar, Dialog.CurrentNode); 
				link.l1.go = DialogGoNodeRepeat("exit_talk", "exit", "exit", "fight", npchar, Dialog.CurrentNode);
			}
			else
			{
				dialog.text = LinkRandPhrase("Cursed paleface has come to our campfire! Wheppee! You're done!","Silly paleface has come to the jaguar's lair. I will fry your liver!","Insolent paleface dares come to my cave? Then he never makes it out alive!");
				link.l1 = LinkRandPhrase("Now I will tear out your tongue...","Now the world will become several cannibals less...","Well, seems that it's time to make a couple more holes in your perishable body, you red-faced ape.");
				link.l1.go = "fight";
			}
			NextDiag.TempNode = "CaveCaribSit";
		break;
		
		case "CaveCaribStay":
			dialog.text = LinkRandPhrase("Foul paleface has come to our cave! Whe-hee! I will cut out your tongue and fry it!","Stupid paleface has come to the jaguar's lair. Brothers, cut this cursed white cur!","Insolent paleface dares come to my cave? Then he never makes it out alive!");
			link.l1 = LinkRandPhrase("I will cut off your freaking head...","Now the world will become several cannibals less...","Well, prepare to meet your ancestors, red-skin. In the Hell!");
			link.l1.go = "fight";
		break;
		
		case "exit_talk":
			DialogExit();
			sGroup = "CaveGroup_" + locations[FindLocation(pchar.location)].index;
			for(i=0; i<4; i++)
			{
				sld = CharacterFromID(sTemp + i);
				LAi_CharacterDisableDialog(sld);
			}
			LAi_CharacterEnableDialog(npchar);
		break;
		
		case "fight":
			DialogExit();
			sGroup = "CaveGroup_" + locations[FindLocation(pchar.location)].index;
			for(i=0; i<4; i++)
			{
				sld = CharacterFromID(sTemp + i);
				LAi_SetWarriorTypeNoGroup(sld);
				LAi_group_MoveCharacter(sld, sGroup);
				LAi_RemoveCheckMinHP(sld);
				LAi_SetImmortal(sld, false);
			}
			LAi_group_SetRelation(sGroup, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups(sGroup, LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck(sGroup, "CaveEnc_RaidersAfrer");
			chrDisableReloadToLocation = true;
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
