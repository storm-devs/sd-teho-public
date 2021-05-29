// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("What would you like?", "What do you want to know?"), "Tell me, what are you interested in, " + GetAddress_Form(NPChar) + "?", "It's the third time you try to ask...", "I had enough of you. Leave me alone!", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("I have changed my mind...", "I've got nothing to say to you"), "Oh, my bad. Indeed... I am sorry",
                      "You're right, it's the third time already. Pardon me...", "I'm sorry...", npchar, Dialog.CurrentNode);		
			link.l1.go = "exit";
			// калеуче
			if (CheckAttribute(pchar, "questTemp.Caleuche") && pchar.questTemp.Caleuche == "graveyard" && !CheckAttribute(npchar, "quest.caleuche"))
			{
				link.l1 = "Listen, have you met in Havana or in its vicinity a man by the name Joachim Merriman. A middle-aged senor, Portuguese, with moustache, imperial beard and piercing eyes? In a cove or in the jungle? Have you seen him?";
				link.l1.go = "caleuche";
			}
		break;
		
		// калеуче
		case "caleuche":
			dialog.text = "N-no, sailor, c-certainly not. Um, this place is rarely visited by anyone, and I... I h-haven't seen anyone like the man you described, so...";
			link.l1 = "Oh, really? And why are you stuttering and hiding your eyes, buddy? You know, I think that you're lying to me. Now, tell me the truth - have you seen that man?";
			link.l1.go = "caleuche_1";
		break;
		
		case "caleuche_1":
			dialog.text = "I-I am telling y-you, senor, I h-haven't seen anyone! I've been s-stuttering s-since I w-was a child...";
			link.l1 = "You're lying. I can see it in your eyes. Where is Merriman?! Tell me!";
			link.l1.go = "caleuche_2";
		break;
		
		case "caleuche_2":
			dialog.text = "I don't know any Merriman! And if you hurt me, the commandant will hang you in the fort, just so that you know!";
			link.l1 = "Oh, do you think so? Alright. Listen to me now and pay attention: Joachim Merriman is a warlock. The Holy Inquisition is looking for him. Many years ago, in Europe, he was sentenced to burning at the stake for grave digging, defilement of the dead and witchcraft. And I know for certain that now he's hiding somewhere in the vicinity of Havana...";
			link.l1.go = "caleuche_3";
		break;
		
		case "caleuche_3":
			dialog.text = "";
			link.l1 = "...recently I have cleared the nearby cave of zombies. And I know whose work it is! Ha! Surely, where else would Merriman go, if not to the cemetery! You know where he is. Alright, I won't even touch you with a finger, but I'll go to the inquisitors in Santiago and tell Father Vincento, that Joachim Merriman is hiding in Havana's cemetery, and the local watchman is his accomplice...";
			link.l1.go = "caleuche_4";
		break;
		
		case "caleuche_4":
			dialog.text = "";
			link.l1 = "... Why have you turned white in an instant? I give you a nobleman's word: in a day after my report everything will be crawling with Spanish soldiers here, and you, stretched on the rack, will be telling them, where that warlock is hiding. And after that you'd be burnt at the stake as his accomplice, while I will be watching the auto-da-fe. How would you like that?";
			link.l1.go = "caleuche_5";
		break;
		
		case "caleuche_5":
			dialog.text = "Please, senor! I am not partaking in any of this, I swear! I... I just couldn't do anything... How could I stand against him?! He's a terrible man, he can... you have no idea what he can do! Mercy!";
			link.l1 = "I know what he can do. I've seen it with my own eyes. So? Where is he? Tell me, and I promise that I will not get you entangled in this affair.";
			link.l1.go = "caleuche_6";
		break;
		
		case "caleuche_6":
			dialog.text = "He... He is hiding in a cave below the cemetery. One can get there only through the chapel's door. When he gets out, I hide in my house and sit there. You have no idea, how much I'd like to get rid of that horror!\nBut I don't dare to even approach. I... I have seen him digging a fresh grave, and then... then the dead man arose and walked around the cemetery in the moonlight! I almost lost my sanity then. But Merriman forbade me to leave. He told me that if I left my house without his permission even for half a day, he would find me and turn into that abomination... a walking skeleton!";
			link.l1 = "How often does he leave his hiding place?";
			link.l1.go = "caleuche_7";
		break;
		
		case "caleuche_7":
			dialog.text = "I am bringing him food and healing potions from town... and whatever else he demands. He gets out once or twice in a month... when the moon is full. He leaves a note at the door where he tells me what he needs, I bring it from town and put it at the door, and he takes it.";
			link.l1 = "I see. And that door to his lair - is it locked?";
			link.l1.go = "caleuche_8";
		break;
		
		case "caleuche_8":
			dialog.text = "Always locked. It's very sturdy, and the lock is massive and safe.";
			link.l1 = "Hm... Merriman is not a fool, and surely he must have another exit from his lair, like in his house in Europe. If we start to force the door open, he'd sneak away, and we'll never find him. Hmmm...";
			link.l1.go = "caleuche_9";
		break;
		
		case "caleuche_9":
			dialog.text = "Senor, will you swear that you don't turn me in to the Inquisition?";
			link.l1 = "I gave you my word, and the word of a nobleman is sacred. I swear that I won't betray you.";
			link.l1.go = "caleuche_10";
		break;
		
		case "caleuche_10":
			dialog.text = "I know how to get there. There is another key... I have it. Merriman didn't know that there were two keys to that lock. I would never dare to enter, but you..";
			link.l1 = "Give me that key, and I will relieve you from that nightmare!";
			link.l1.go = "caleuche_11";
		break;
		
		case "caleuche_11":
			GiveItem2Character(pchar, "kaleuche_key");
			ChangeItemDescribe("kaleuche_key", "itmdescr_kaleuche_key_crypt");
			dialog.text = "Here you go, senor. Are you seriously going to enter his lair?";
			link.l1 = "Exactly. Lock yourself up in your house and sit there, when I go inside. If I don't return, cut and run as fast as you can.";
			link.l1.go = "caleuche_12";
		break;
		
		case "caleuche_12":
			dialog.text = "Be very careful, senor. Frightening sounds are coming from his cave, and I fear to even think, who could inhabit it. But Merriman is not alone there - that's for certain.";
			link.l1 = "I'll take all measures I can.";
			link.l1.go = "caleuche_13";
		break;
		
		case "caleuche_13":
			DialogExit();
			AddQuestRecord("Caleuche", "30");
			pchar.questTemp.Caleuche = "merriman";
			pchar.quest.caleuche_merriman_cave.win_condition.l1 = "locator";
			pchar.quest.caleuche_merriman_cave.win_condition.l1.location = "Havana_CryptBig2";
			pchar.quest.caleuche_merriman_cave.win_condition.l1.locator_group = "reload";
			pchar.quest.caleuche_merriman_cave.win_condition.l1.locator = "reload2";
			pchar.quest.caleuche_merriman_cave.function = "Caleuche_OpenMerrimanCave";
			pchar.quest.caleuche_merriman_cave1.win_condition.l1 = "location";
			pchar.quest.caleuche_merriman_cave1.win_condition.l1.location = "Havana_CryptDungeon";
			pchar.quest.caleuche_merriman_cave1.function = "Caleuche_InMerrimanCave";
			SetFunctionTimerCondition("Caleuche_MerrimanCaveOver", 0, 0, 3, false); // таймер
			npchar.quest.caleuche = "true";
			// логово Мерримана
			int n = Findlocation("Havana_CryptDungeon");
			locations[n].id.label = "Merrimancave";
		break;
	}
	UnloadSegment(NPChar.FileDialog2); 
}

