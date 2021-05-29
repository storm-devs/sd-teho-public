// Джессика Роуз - нежить и супербосс
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i;
	string sTemp;
	float locx, locy, locz;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "Want something?";
			link.l1 = "No, it's nothing.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		// бой на рифе
		case "reef":
			PlaySound("VOICE\Russian\saga\Jessica Rose-06.wav");
			dialog.text = "You! You have brought her here! She is his flesh and blood! She is her flesh and blood! The daughter of whore has come to her mother's grave! She'll die! And you won't stop it! Don't stay in Jessica's way! Let the vengeance commit!";
			link.l1 = "...";
			link.l1.go = "reef_1";
		break;
		
		case "reef_1":
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			DialogExit();
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "stage_1":
			PlaySound("VOICE\Russian\saga\Jessica Rose-07.wav");
			dialog.text = "Ha! You cannot hurt me!\n The air, the water, the earth, the fire - I order you to assist me!\n Let the dead rise, let the fire burn, let the water guard the bridge, let the wind take you on its wings and throw you down to the ground!\nHave fun!!!";
			link.l1 = "...";
			link.l1.go = "stage_1_exit";
		break;
		
		case "stage_1_exit":
			DialogExit();
			LAi_SetActorType(pchar);
			CreateLocationParticles("blast_inv", "quest", "top", 1.6, 0, 0, "");
			PlaySound("Sea Battles_01\Bomb_Explosion_03.wav");
			PlaySound("People Fight\Death_NPC_08.wav");
			GetCharacterPos(pchar, &locx, &locy, &locz);
			ChangeCharacterAddressGroup(pchar, "shore67", "goto", LAi_FindFarFreeLocator("goto", locx, locy, locz));
			LAi_ActorAnimation(Pchar, "Ground_sitting", "", 3.5);
			DoQuestCheckDelay("Saga_JessikaFirstKick_2", 3.5);
		break;
		
		case "stage_2":
			PlaySound("VOICE\Russian\saga\Jessica Rose-08.wav");
			dialog.text = "Ha! You cannot hurt me!\nLet more of the dead rise and attack, let the fire burn the stone, let the wind take you up and let the earth absorb your strengths!\nEnjoy!!!";
			link.l1 = "...";
			link.l1.go = "stage_2_exit";
		break;
		
		case "stage_2_exit":
			DialogExit();
			LAi_SetActorType(pchar);
			CreateLocationParticles("blast_inv", "quest", "rock", 1.6, 0, 0, "");
			PlaySound("Sea Battles_01\Bomb_Explosion_03.wav");
			PlaySound("People Fight\Death_NPC_08.wav");
			pchar.GenQuest.BladePenalty = 30;
			GetCharacterPos(pchar, &locx, &locy, &locz);
			ChangeCharacterAddressGroup(pchar, "shore67", "goto", LAi_FindNearestFreeLocator("goto", locx, locy, locz));
			LAi_ActorAnimation(Pchar, "Ground_sitting", "", 3.5);
			DoQuestCheckDelay("Saga_JessikaSecondKick_2", 3.5);
		break;
		
		case "stage_3":
			PlaySound("VOICE\Russian\saga\Jessica Rose-07.wav");
			dialog.text = "Ha! You cannot hurt me!\nLet the poison to cover my flame-bladed sword, let the wind take you in its hugs, let the water drink away your agility!\nDie! Ha-ha-ha!";
			link.l1 = "...";
			link.l1.go = "stage_3_exit";
		break;
		
		case "stage_3_exit":
			DialogExit();
			npchar.viper = true;
			TakeNItems(npchar, "potion2", 3);
			LAi_SetActorType(pchar);
			PlaySound("Sea Battles_01\Bomb_Explosion_03.wav");
			PlaySound("People Fight\Death_NPC_08.wav");
			pchar.GenQuest.EnergyPenalty = 2;
			GetCharacterPos(pchar, &locx, &locy, &locz);
			ChangeCharacterAddressGroup(pchar, "shore67", "quest", "bridge2");
			LAi_ActorTurnToLocator(pchar, "quest", "bridge1");
			LAi_ActorAnimation(Pchar, "Ground_sitting", "", 3.5);
			DoQuestCheckDelay("Saga_JessikaThirdKick_2", 3.5);
		break;
		
		case "stage_4":
			PlayStereoOGG("music_shore");
			sld = characterFromId("Svenson");
			dialog.text = "Enough... I am tired. I am defeated... Take pity upon the fate of unfortunate Jessica!";
			link.l1 = "Sure... I will spare your poor soul from the weigh of this dead body!";
			link.l1.go = "exit_battle";
			if (CheckAttribute(sld, "quest.jessika_peace")) // выслушал историю Джессики
			{
				link.l2 = "I know your story, Jessica. And I am sorry that your life was so sad and ended that silly. You want to talk to me, right? Well, I'll try to forget that you've recently tried to kill me and I'll listen to you, though it won't be easy for me...";
				link.l2.go = "exit_talk";
			}
		break;
		
		case "exit_battle":
			DialogExit();
			SetMusic("music_teleport");
			DeleteAttribute(npchar, "viper");
			LAi_SetImmortal(npchar, false);
			npchar.chr_ai.hp = stf(npchar.chr_ai.hp)+100;
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "Saga_JessikaDie");
			AddDialogExitQuest("MainHeroFightModeOn");
			pchar.questTemp.Saga.JessSeekTreatment = 0;
			LAi_LocationDisableOfficersGen(pchar.location, false);//офицеров пускать
		break;
		
		case "exit_talk":
			dialog.text = "Thank you... You already know about Beatrice Sharp and Lawrence... my Lawrence. I have killed her unhesitatingly, but I couldn't kill him. I couldn't do it, but he could. Jessica died...";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuest("Video_Reef");
			NextDiag.TempNode = "exit_talk_0";
		break;
		
		case "exit_talk_0":
			dialog.text = "... but the blood vow, bonded by a terrible oath is still unperformed. Power of this vow is strengthen by Indian magic. It has risen the corpse from it's grave\nHatred turned my soul into a desert. Everyone who came to this reef were slain by my hand and their dead bodies became my puppets. I can ask for help no one, but the one who has vanquished me...";
			link.l1 = "And what can I do for you? The only thing I can is to spare you from suffering...";
			link.l1.go = "exit_talk_1";
		break;
		
		case "exit_talk_1":
			PlaySound("VOICE\Russian\saga\Jessica Rose-03.wav");
			dialog.text = "Help me... Take me to him.";
			link.l1 = "To Lawrence Beltrope? And how am I supposed to do that? My crew will either run away as soon as they see you or they will burn you with no regret. By the way, you are still able to butcher my men and 'control' them...";
			link.l1.go = "exit_talk_2";
		break;
		
		case "exit_talk_2":
			dialog.text = "They won't see me. But you will. You must have already understood that I posses powers unavailable for the living. But I cannot get aboard your ship without your permission. Take me to him\nI won't stay with you for long. And I won't hurt you people. Land me at Portland Cove at midnight, the next night we'll meet again and you will get what you wanted to find here.";
			link.l1 = "How do you know why am I here?";
			link.l1.go = "exit_talk_3";
		break;
		
		case "exit_talk_3":
			PlaySound("VOICE\Russian\saga\Jessica Rose-01.wav");
			dialog.text = "I know a lot. More then the living do. I saw her... You need a document for her and you will get it. You will get even more, I will give you something extra. Take me to him...";
			link.l1 = "Hm. I don't like your bloodthirsty intentions towards Helen. Don't even dare to touch her. After all, she is not responsible for her mother's actions.";
			link.l1.go = "exit_talk_4";
		break;
		
		case "exit_talk_4":
			dialog.text = "You have defeated me. I won't harm her... I promise.";
			link.l1 = "It is not over yet. Are you going to take your numerous curses away from me? I admit, I don't like the idea to live with them forever...";
			link.l1.go = "exit_talk_5";
		break;
		
		case "exit_talk_5":
			dialog.text = "It is not that simple... When we'll meet at Portland Cove after I... I'll tell you how to heal yourself.";
			link.l1 = "After you what?.. What do you mean?";
			link.l1.go = "exit_talk_6";
		break;
		
		case "exit_talk_6":
			dialog.text = "After my meeting with him.";
			link.l1 = "Oh, he won't be happy. I can imagine. Fine, let's summarize: first, you promise that no one will see you, second, you won't harm my crew, third, you will not even think about Helen, fourth, you will give me what I am looking for and, fifth, you will heal me from your curses. Am I right?";
			link.l1.go = "exit_talk_7";
		break;
		
		case "exit_talk_7":
			dialog.text = "Almost. I won't heal you, but I will tell you how to. You will have to do it yourself.";
			link.l1 = "Fine. Deal then. I allow you to go to my ship.";
			link.l1.go = "exit_talk_8";
		break;
		
		case "exit_talk_8":
			PlaySound("Ambient\Teno_inside\teleporter.wav");
			ChangeCharacterAddressGroup(npchar, "none", "", "");
			dialog.text = "";
			link.l1 = "Hey! Where are you? Just disappeared...";
			link.l1.go = "exit_talk_9";
		break;
		
		case "exit_talk_9":
			DialogExit();
			LAi_group_Delete("EnemyFight");
			pchar.quest.Saga_JessFire.over = "yes"; 
			pchar.quest.Saga_JessFire1.over = "yes"; 
			pchar.quest.Saga_JessFire2.over = "yes";
			ref chr = &Locations[FindLocation(pchar.location)];
			DeleteAttribute(chr, "hell_fire_1");
			DeleteAttribute(chr, "hell_fire_2");
			DeleteAttribute(chr, "hell_fire_3");
			chrDisableReloadToLocation = false;//открыть локацию
			DeleteAttribute(pchar, "GenQuest.CannotWait");//можно мотать время
			AddQuestRecord("Shadows", "9");
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, false);
			pchar.questTemp.Saga.JessOnShip = "true"; // атрибут на отрицательные последствия
			pchar.quest.Saga_Jessika_Travel.win_condition.l1 = "Hour";
			pchar.quest.Saga_Jessika_Travel.win_condition.l1.start.hour = 0.00;
			pchar.quest.Saga_Jessika_Travel.win_condition.l1.finish.hour = 2.00;
			pchar.quest.Saga_Jessika_Travel.win_condition.l2 = "location";
			pchar.quest.Saga_Jessika_Travel.win_condition.l2.location = "shore36";
			pchar.quest.Saga_Jessika_Travel.function = "Saga_JessikaOnJamaica";
			NextDiag.CurrentNode = "shore";
			npchar.greeting = "jessika_2";
			LAi_LocationDisableOfficersGen(pchar.location, false);//офицеров пускать
			LAi_LocationDisableOfficersGen("shore36", true);//офицеров не пускать в бухту Портленд
		break;
		
		case "shore":
			dialog.text = "You have kept your word - we are on Jamaica. Come here tomorrow at night and I will fulfill my promise. Farewell.";
			link.l1 = "Farewell...";
			link.l1.go = "shore_1";
		break;
		
		case "shore_1":
			DialogExit();
			DeleteAttribute(pchar, "questTemp.Saga.JessOnShip");
			DeleteAttribute(npchar, "SaveItemsForDead");
			DeleteAttribute(npchar, "DontClearDead");
			LAi_SetActorType(npchar);
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешить драться
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "OpenTheDoors", -1);
			AddQuestRecord("Shadows", "10");
			SetFunctionTimerCondition("Saga_JessikaShoreWait", 0, 0, 1, false);
			NextDiag.CurrentNode = "shore_2";
			npchar.greeting = "jessika_3";
		break;
		
		case "shore_2":
			dialog.text = "It's over, "+pchar.name+"...";
			link.l1 = "What do you mean?";
			link.l1.go = "shore_3";
		break;
		
		case "shore_3":
			dialog.text = "It's over... Here, take it, this is what you were looking for. This is the letter of my rival, it was buried with her. It was preserved well. I have forgiven her and there is no more hatred in my soul.";
			link.l1 = "Did you... meet with him? With Lawrence?";
			link.l1.go = "shore_4";
		break;
		
		case "shore_4":
			GiveItem2Character(pchar, "letter_beatriss"); // дать письмо
			AddQuestRecordInfo("Letter_beatriss", "1");
			dialog.text = "Yes. The last thing he felt in his life was a horror. I'm not sorry for him.";
			link.l1 = "May God forgive his sinful soul... It seems that I will never meet him.";
			link.l1.go = "shore_5";
		break;
		
		case "shore_5":
			dialog.text = "You've lost nothing. He was a very bad man. Now, we should say goodbye to each other, there is nothing more left for me here. My vow was fulfilled and the magic has lost its power. I have promised you a present. Here. This is my flamberge. I don't need it anymore. This blade is unique, you won't find better anywhere in the world.";
			link.l1 = "Thanks...";
			link.l1.go = "shore_6";
		break;
		
		case "shore_6":
			RemoveAllCharacterItems(npchar, true);
			GiveItem2Character(pchar, "blade_25");
			PlaySound("interface\important_item.wav");
			dialog.text = "Now about you. Go to Bridgetown, to the local church in order to take off my curses. You will find a priest there. He knew me personaly. Talk to him and he will tell you what to do. Prepare twenty candles, you will need them.";
			link.l1 = "Are you sure that he will heal me?";
			link.l1.go = "shore_7";
		break;
		
		case "shore_7":
			dialog.text = "You will do it by yourself. God will guide you. Be sure. All will be fine.";
			link.l1 = "Okay, I will sail to Barbados immediately. And what now?";
			link.l1.go = "shore_8";
		break;
		
		case "shore_8":
			PlaySound("VOICE\Russian\saga\Jessica Rose-04.wav");
			dialog.text = "And now I have one last wish to you. Bury my body here at this cove near the sea. I want that. Perhaps, one day you will visit a grave of poor Jessica. Farewell, "+pchar.name+", and pray for me...";
			link.l1 = "Jess?..";
			link.l1.go = "shore_9";
		break;
		
		case "shore_9":
			DialogExit();
			LAi_KillCharacter(npchar);
			bQuestDisableMapEnter = false;
			DeleteAttribute(pchar, "GenQuest.MapClosedNoBattle");
			chrDisableReloadToLocation = false;
			LAi_LocationDisableOfficersGen("shore36", false);
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			AddQuestRecord("Shadows", "11");
			pchar.questTemp.Saga.JessTreatment = "true";
			// вытираем Белтропа
			sld = characterFromId("Beltrop");
			sld.lifeday = 0;
			pchar.questTemp.Saga.Beltrop_die = "true"; // Белтроп убит
			sld = ItemsFromID("letter_jess");
			sld.price = 1; // страницу можно выкладывать 270912 
		break;
		
		case "soul":
			dialog.text = "Did you recognize me, captain?";
			link.l1 = "Is it... is it you? But how?";
			link.l1.go = "soul_1";
		break;
		
		case "soul_1":
			dialog.text = "Yes, "+pchar.name+", it is me, it's Jessica! At least, I was looking like that twenty years ago.";
			link.l1 = "So... did I die? But when? How?";
			link.l1.go = "soul_2";
		break;
		
		case "soul_2":
			dialog.text = "You are not dead, "+pchar.name+". You are in the church of Bridgetown now. You are just... sleeping.";
			link.l1 = "Is it just a dream? Things look too real...";
			link.l1.go = "soul_3";
		break;
		
		case "soul_3":
			dialog.text = "It happens sometimes, "+pchar.name+". God has heard you. Your prays have not only healed you, but also have purified my soul. Thank you very much, "+pchar.name+"! And I want to ask you to forgive me for what has happened at the reef. It's... well, just forgive me. I couldn't leave without asking for your forgiveness.";
			link.l1 = "I forgive you, Jessica. Am I really alive?";
			link.l1.go = "soul_4";
		break;
		
		case "soul_4":
			dialog.text = "You are... Don't worry. Soon, you will wake up. I just wanted to say goodbye.";
			link.l1 = "You are so... beautiful!";
			link.l1.go = "soul_5";
		break;
		
		case "soul_5":
			dialog.text = "Do you like me? Yes, there was a time when the best of suitors from Lesser Antilles had been courting me and every third pirate of Isla Tesoro was ready to duel for me.";
			link.l1 = "But you have always needed only one... Eh, ginger talisman! Just tell me why did you end up like this?";
			link.l1.go = "soul_6";
		break;
		
		case "soul_6":
			dialog.text = "Because of my anger. of hatred. For inability to understand, forgive and forget. I could start a new life, but I preferred to devote myself to the stupid and pointless vengeance. You have released me. Thank you, "+pchar.name+"...";
			link.l1 = "I feel really sorry for your life...";
			link.l1.go = "soul_7";
		break;
		
		// здесь проверяем Мэри
		case "soul_7":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{ // Мэри-офицер
				dialog.text = "Don't... You also have a ginger talisman...";
				link.l1 = "Yes? Who is it?";
				link.l1.go = "mary_1";
				break;
			}
			if (!CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && CheckAttribute(pchar, "questTemp.LSC.marywait"))
			{ // Мэри осталась на острове
				dialog.text = "Don't... You also have a ginger talisman...";
				link.l1 = "Yes? Who is it?";
				link.l1.go = "mary_3";
				break;
			}
			dialog.text = "Don't... Consider my sad experience and don't repeat any of my mistakes. And don't let the people you love do it too.";
			link.l1 = "I will consider that and I won't do the same mistakes for sure...";
			link.l1.go = "soul_8";
		break;
		
		case "mary_1":
			dialog.text = "Think a bit. She is on you ship.";
			link.l1 = "Mary?!";
			link.l1.go = "mary_2";
		break;
		
		case "mary_2":
			dialog.text = "Yes. She is the best you will ever have in your life. Remember that. Her love is clear, her devotion is infinite. She is brave, desperate, but young and inexperienced. She doesn't understand a lot. Take care of her, protect her and don't let anyone stand between you both. She is your talisman...";
			link.l1 = "I... I'll never leave her and will protect her from any danger.";
			link.l1.go = "soul_8";
		break;
		
		case "mary_3":
			dialog.text = "She is on the strange island which is made of dead ships... She is not alone there, but she is lonely. Every morning of hers begins with a thought of you, every day she prays for you, every night there is a light in her cabin and her pillow is wet because of her tears...";
			link.l1 = "Mary...";
			link.l1.go = "mary_4";
		break;
		
		case "mary_4":
			dialog.text = "There is a daughter between you both. The daughter of the woman who once stood between me and Lawrence. Your talisman's fate is in your hands. They can't coexist together just like me and Beatrice couldn't.";
			link.l1 = "How do you know that?";
			link.l1.go = "mary_5";
		break;
		
		case "mary_5":
			dialog.text = "The other side... It shows a lot... It's you choice, but remember: Mary is the best you will ever have in your life. Her love is clear, her devotion is infinite. She is brave, desperate, but young and inexperienced. She doesn't understand a lot. She needs your protection, your care and your love. She is your talisman.";
			link.l1 = "I will consider that. I will do that for sure...";
			link.l1.go = "soul_8";
		break;
		
		case "soul_8":
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_friend")) sTemp = "";
			else sTemp = "And about a daughter of Beatrice, know that your noble actions in her behalf will be left unvalued. Soon you will see that by yourself. Be careful with her. Well\n";
			dialog.text = ""+sTemp+"I have to go. It is time to say goodbye... For real this time. Don't forget about Jessica and try to visit her grave sometimes... Only you know where it is.";
			link.l1 = "Sure, Jess. I will visit it and I will pray for you.";
			link.l1.go = "soul_9";
		break;
		
		case "soul_9":
			dialog.text = "Thank you. Goodbye, "+pchar.name+"! Goodbye!";
			link.l1 = "Goodbye, Jessica...";
			link.l1.go = "soul_10";
		break;
		
		case "soul_10":
			DialogExit();
			LAi_SetActorType(pchar);
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "Saga_JessikaSoul_4", -1);
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}