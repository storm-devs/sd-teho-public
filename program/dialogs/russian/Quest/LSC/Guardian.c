// диалог протекторов, солдат и мушкетеров кланов LSC
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	string sTemp;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "What the hell do you want?";
			link.l1 = "No, it's nothing.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
//------------------------------------- фразы гардов нарвалов --------------------------------------------
		// пост нарвалов на проход на Сан-Габриэль
		case "Narval_warning":
			if (CheckAttribute(pchar, "GenQuest.NarvalConflict"))
			{
				dialog.text = LinkRandPhrase("Lads, careful, there is the psycho! To arms!","Enemy is here! To arms!","Ah, you are bastard! Now we will teach you a lesson!");
				link.l1 = "Fuck!";
				link.l1.go = "check_parol_fight";
				break;
			}
			ref location = &Locations[FindLocation(pchar.location)];
			if (!CheckAttribute(location, "nrv_parolinfo"))
			{
				if (!CheckAttribute(pchar, "questTemp.LSC.nrv_friend")) 
				{
					dialog.text = "Stop, pal. Narwhal's territories ahead, an entry is prohibited for strangers. You can pass only by an invitation. Do you know the password?";
					link.l1 = "Yes.";
					link.l1.go = "Narval_warning_yes";
					link.l2 = "No.";
					link.l2.go = "Narval_warning_no";
				}
				else // если друг нарвалам
				{
					dialog.text = "A-ah, "+GetFullName(pchar)+"! Hello, friend, we are warned that you can walk freely here. Welcome!";
					link.l1 = "Thanks, friend!";
					link.l1.go = "exit";
				}
				location.nrv_parolinfo = "true";
			}
			else
			{
				if (!CheckAttribute(pchar, "questTemp.LSC.nrv_friend")) 
				{
					dialog.text = "I hope that you didn't forget a password...";
					link.l1 = "Don't worry...";
					link.l1.go = "exit";
				}
				else // если друг нарвалам
				{
					dialog.text = TimeGreeting()+", "+pchar.name+"! How are you doing?";
					link.l1 = "Fine, thanks!";
					link.l1.go = "exit";
				}
			}
			NextDiag.TempNode = "Narval_warning_repeat";
			DeleteAttribute(npchar, "protector.CheckAlways");
		break;
		
		case "Narval_warning_yes":
			dialog.text = "Then go and tell that to the tough guy over there. Don't try to cheat on him, our boys with muskets know what to do. So if you are planning any tricks - you'd better turn and leave. Now. I warned you.";
			link.l1 = "Fine, friend. I got it.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Narval_warning_repeat";
		break;
		
		case "Narval_warning_no":
			dialog.text = "Then you have got nothing to do here if you are not going to end your life, of course. Or you're just joking, huh? Are you kidding me? Actually, I don't care. Go down, my job is to warn but not to stop. You won't make it back if you don't know a password.";
			link.l1 = "Fine, pal. I got it.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Narval_warning_repeat";
		break;
		
		case "Narval_warning_repeat":
			if (!CheckAttribute(pchar, "questTemp.LSC.nrv_friend")) 
			{
				dialog.text = "What else do you need? Go down to the 'San Gabriel' or get lost!";
				link.l1 = "...";
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = "I am sorry, "+pchar.name+", but I am on duty. Don't bother me, pal. Move along!";
				link.l1 = "...";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "Narval_warning_repeat";
		break;
		
		case "Narval_parol":
			if (CheckAttribute(pchar, "GenQuest.NarvalConflict"))
			{
				dialog.text = LinkRandPhrase("Lads, careful, there is the psycho! To arms!","Enemy is here! To arms!","Ah, you are bastard! Now we will teach you a lesson!");
				link.l1 = "Fuck!";
				link.l1.go = "check_parol_fight";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.LSC.nrv_friend")) 
			{
				dialog.text = "I am sorry, "+pchar.name+", but I am on duty. Don't bother me, pal. Move along!";
				link.l1 = "...";
				link.l1.go = "exit";
				NextDiag.TempNode = "Narval_parol";
				break;
			}
			dialog.text = "Stand right where you are! You are not one of us!";
			link.l1 = "I am standing, standing.";	
			link.l1.go = "check_parol";
		break;
		
		case "check_parol":
			dialog.text = "Say a password and do it clear and loud.";
			link.l1.edit = 3;
			link.l1 = "";	
			link.l1.go = "check_parol_1";
		break;
		
		case "check_parol_1":
			sTemp = GetStrSmallRegister(dialogEditStrings[3]);
			if (sTemp == sNrvParol && CheckAttribute(pchar, "questTemp.LSC.NParol_bye"))
			{
				dialog.text = "Fine, you may proceed.";
				link.l1 = "Thanks, pal...";
				link.l1.go = "exit";
				NextDiag.TempNode = "Narval_parol_repeat";
				LAi_SetGuardianType(NPChar);
				LAi_group_MoveCharacter(NPChar, "LSC_NARVAL");
				pchar.questTemp.LSC.parol_nrv = "true";
			}
			else
			{
				dialog.text = "Hm... Lads! We have got a company!";
				link.l1 = "Shit!";
				link.l1.go = "check_parol_fight";
			}
		break;
		
		case "check_parol_fight":
			DialogExit();
			LAi_SetGuardianType(NPChar);
			LAi_group_MoveCharacter(NPChar, "LSC_NARVAL");
			LAi_group_Attack(NPChar, Pchar);
		break;
		
		case "Narval_parol_repeat":
			if (CheckAttribute(pchar, "GenQuest.NarvalConflict"))
			{
				dialog.text = LinkRandPhrase("Lads, careful, there is the psycho! To arms!","Enemy is here! To arms!","Ah, you are bastard! Now we will teach you a lesson!");
				link.l1 = "Fuck!";
				link.l1.go = "check_parol_fight";
				break;
			}
			dialog.text = "Move along! Don't stand here!";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "Narval_parol_repeat";
		break;
		
		// у резиденции
		case "Narval_residence":
			if (CheckAttribute(pchar, "GenQuest.NarvalConflict"))
			{
				dialog.text = LinkRandPhrase("Lads, careful, there is the psycho! To arms!","Enemy is here! To arms!","Ah, you are bastard! Now we will teach you a lesson!");
				link.l1 = "Fuck!";
				link.l1.go = "check_parol_fight";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.LSC.nrv_friend")) 
			{
				if (stf(environment.time) >= 6.00 && stf(environment.time) < 21.00) // диалог от времени суток. лесник
			    {
					dialog.text = TimeGreeting()+", "+pchar.name+"! The door is open, in case you want to see the boss.";
					link.l1 = "Fine...";
					link.l1.go = "exit";
					NextDiag.TempNode = "Narval_residence";
					DeleteAttribute(npchar, "protector.CheckAlways");
				}
				else
				{
                    dialog.text = TimeGreeting()+", "+pchar.name+"! In case you want to see the boss, he is asleep by now. Come back in the morning.";
					link.l1 = "Fine...";
					link.l1.go = "exit";
					NextDiag.TempNode = "Narval_residence";
					DeleteAttribute(npchar, "protector.CheckAlways");	
                }					
				break;	
			}
			if (!CheckAttribute(pchar, "questTemp.LSC.nrv_friend") && CheckAttribute(pchar, "questTemp.LSC.rvd_friend")) 
			{
				dialog.text = "Friends of black ones have nothing to do here. A straight order from the boss!";
				if (CheckAttribute(pchar, "questTemp.LSC.Donald_enter"))
				{
					link.l1 = "He will have to see me. You have got real troubles, guys. I am here by the official orders of the admiral. So open the damn door!";
					link.l1.go = "negotiations";
				}
				else
				{
				link.l1 = "I can't say I want to see him either...";
				link.l1.go = "exit";
				}
				NextDiag.TempNode = "Narval_residence";
				DeleteAttribute(npchar, "protector.CheckAlways");
				break;
			}
			if (stf(environment.time) >= 6.00 && stf(environment.time) < 21.00) // лесник . диалог от времени суток .
			{
			dialog.text = "Want to see the boss? Hm, well, move along then.";
			link.l1 = "Thanks for allowing to...";
			link.l1.go = "exit";
			NextDiag.TempNode = "Narval_residence";
			DeleteAttribute(npchar, "protector.CheckAlways");
			}
			else
			{
            dialog.text = "Want to see the boss? No more visits today. Come back in the morning.";
			link.l1 = "Alright...";
			link.l1.go = "exit";
			NextDiag.TempNode = "Narval_residence";
			DeleteAttribute(npchar, "protector.CheckAlways");
            }			
		break;
		
		case "Narval_soldier":
			if (CheckAttribute(pchar, "GenQuest.NarvalConflict"))
			{
				dialog.text = LinkRandPhrase("Lads, careful, there is the psycho! To arms!","Enemy is here! To arms!","Ah, you are bastard! Now we will teach you a lesson!");
				link.l1 = "Fuck!";
				link.l1.go = "check_parol_fight";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.LSC.nrv_friend")) 
			{
				dialog.text = TimeGreeting()+", "+pchar.name+"! How are you doing?";
				link.l1 = "I am fine, thanks...";
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = "Listen, pal, I am not in a mood to talk. Move along...";
				link.l1 = "Fine.";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "Narval_soldier";
		break;
		
		case "negotiations":
			dialog.text = "Well-well... Calm down. You should have said that you were from the admiral in the first place. See, there are different people wandering around...";
			link.l1 = "Are you finally going to let me through? Thanks!";
			link.l1.go = "negotiations_1";
		break;
		
		case "negotiations_1":
			DialogExit();
			NextDiag.CurrentNode = "negotiations_2";
			LocatorReloadEnterDisable("LostShipsCity_town", "reload48", false); // открыть вход к Дональду Гринспи
		break;
		
		case "negotiations_2":
			dialog.text = "Move along, you are allowed to...";
			link.l1 = "Oh, really? Can't believe it.";
			link.l1.go = "exit";
			NextDiag.TempNode = "negotiations_2";
		break;
		
//------------------------------------- фразы гардов ривадос --------------------------------------------
		// пост ривадос на проход на Фурию и Веласко
		case "Rivados_warning":
			if (CheckAttribute(pchar, "GenQuest.RivadosConflict"))
			{
				dialog.text = LinkRandPhrase("Lads, careful, there is the aggressive psycho! To arms!","Enemy is here! To arms!","Ah, you are a sick bastard! Now we will teach you a lesson!");
				link.l1 = "Fuck!";
				link.l1.go = "Rcheck_parol_fight";
				break;
			}
			location = &Locations[FindLocation(pchar.location)];
			if (!CheckAttribute(location, "rvd_parolinfo"))
			{
				if (!CheckAttribute(pchar, "questTemp.LSC.rvd_friend")) 
				{
					dialog.text = "Stop! The territories behind me belong to Rivados clan, no strangers like you are allowed to pass through without an invitation. Do you know the password?";
					link.l1 = "Yes.";
					link.l1.go = "Rivados_warning_yes";
					link.l2 = "No.";
					link.l2.go = "Rivados_warning_no";
				}
				else // если друг ривадос
				{
					dialog.text = "Ah, "+GetFullName(pchar)+"! Glad to see you! We were informed that you can walk freely here. Welcome!";
					link.l1 = "Thanks, friend!";
					link.l1.go = "exit";
				}
				location.rvd_parolinfo = "true";
			}
			else
			{
				if (!CheckAttribute(pchar, "questTemp.LSC.rvd_friend")) 
				{
					dialog.text = "I hope that you didn't forget a password...";
					link.l1 = "Don't worry...";
					link.l1.go = "exit";
				}
				else // если друг ривадос
				{
					dialog.text = TimeGreeting()+", "+pchar.name+"! How are you doing?";
					link.l1 = "I am fine, thanks...";
					link.l1.go = "exit";
				}
			}
			NextDiag.TempNode = "Rivados_warning_repeat";
			DeleteAttribute(npchar, "protector.CheckAlways");
		break;
		
		case "Rivados_warning_yes":
			dialog.text = "You can go then. This lad will demand a password from you. You'd better leave now if your have any thoughts about tricking us. I have warned you.";
			link.l1 = "Fine, pal. I got it.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Rivados_warning_repeat";
		break;
		
		case "Rivados_warning_no":
			dialog.text = "Ho-ho! Either you are very brave or a very silly if you are going to visit us without a password. Or are you just joking? Go on then. I am here to warn, not to stop. Beware if you really don't know the password!";
			link.l1 = "Fine, pal. I got it.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Rivados_warning_repeat";
		break;
		
		case "Rivados_warning_repeat":
			if (!CheckAttribute(pchar, "questTemp.LSC.rvd_friend")) 
			{
				dialog.text = "Well, what do you want? Move along or get lost!";
				link.l1 = "...";
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = "I am sorry, "+pchar.name+", but I am on duty. Eddie don't want me to talk too much.";
				link.l1 = "...";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "Rivados_warning_repeat";
			DeleteAttribute(npchar, "protector.CheckAlways");
		break;
		
		case "Rivados_parol":
			if (CheckAttribute(pchar, "GenQuest.RivadosConflict"))
			{
				dialog.text = LinkRandPhrase("Lads, careful, there is the aggressive psycho! To arms!","Enemy is here! To arms!","Ah, you are a sick bastard! Now we will teach you a lesson!");
				link.l1 = "Fuck!";
				link.l1.go = "Rcheck_parol_fight";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.LSC.rvd_friend")) 
			{
				dialog.text = "I am sorry, "+pchar.name+", but I am on duty. Eddie don't want me to talk too much.";
				link.l1 = "...";
				link.l1.go = "exit";
				NextDiag.TempNode = "Rivados_parol";
				DeleteAttribute(npchar, "protector.CheckAlways");
				break;
			}
			dialog.text = "Stop right where you are! You are not Rivados!";
			link.l1 = "I want to pass through.";	
			link.l1.go = "Rcheck_parol";
		break;
		
		case "Rcheck_parol":
			dialog.text = "Then say a password and do it loud and clear.";
			link.l1.edit = 3;
			link.l1 = "";	
			link.l1.go = "Rcheck_parol_1";
		break;
		
		case "Rcheck_parol_1":
			sTemp = GetStrSmallRegister(dialogEditStrings[3]);
			if (sTemp == sRvdParol && CheckAttribute(pchar, "questTemp.LSC.RParol_bye"))
			{
				dialog.text = "Correct. Move along.";
				link.l1 = "Thanks, pal...";
				link.l1.go = "exit";
				NextDiag.TempNode = "Rivados_parol_repeat";
				LAi_SetGuardianType(NPChar);
				LAi_group_MoveCharacter(NPChar, "LSC_RIVADOS");
				pchar.questTemp.LSC.parol_rvd = "true";
			}
			else
			{
				dialog.text = "Ha-ha! We have a guest here! Let's show him who we are!";
				link.l1 = "Shit!";
				link.l1.go = "Rcheck_parol_fight";
			}
		break;
		
		case "Rcheck_parol_fight":
			DialogExit();
			LAi_SetGuardianType(NPChar);
			LAi_group_MoveCharacter(NPChar, "LSC_RIVADOS");
			LAi_group_Attack(NPChar, Pchar);
		break;
		
		case "Rivados_parol_repeat":
			if (CheckAttribute(pchar, "GenQuest.RivadosConflict"))
			{
				dialog.text = LinkRandPhrase("Lads, careful, there is the aggressive psycho! To arms!","Enemy is here! To arms!","Ah, you are a sick bastard! Now we will teach you a lesson a lesson!");
				link.l1 = "Fuck!";
				link.l1.go = "Rcheck_parol_fight";
				break;
			}
			dialog.text = "Don't stand here, move along!";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "Rivados_parol_repeat";
		break;
		
		// у резиденции
		case "Rivados_residence":
			if (CheckAttribute(pchar, "GenQuest.RivadosConflict"))
			{
				dialog.text = LinkRandPhrase("Lads, careful, there is the aggressive psycho! To arms!","Enemy is here! To arms!","Ah, you are a sick bastard! Now we will teach you!");
				link.l1 = "Fuck!";
				link.l1.go = "Rcheck_parol_fight";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.LSC.rvd_friend")) 
			{
				if (stf(environment.time) >= 6.00 && stf(environment.time) < 21.00) // лесник . диалог от времени суток .
				{
				dialog.text = TimeGreeting()+", "+pchar.name+"! The door is open, in case you want to see Eddie and Chimiset. They will be glad to see you.";
				link.l1 = "Fine...";
				link.l1.go = "exit";
				NextDiag.TempNode = "Rivados_residence";
				DeleteAttribute(npchar, "protector.CheckAlways");
				}
				else // лесник - режим пропуска 
				{	
				dialog.text = TimeGreeting()+", "+pchar.name+"! In case you want to see Eddie and Chimiset, they resting already. Come back in the morning, they will be glad to see you.";
				link.l1 = "Fine...";
				link.l1.go = "exit";
				NextDiag.TempNode = "Rivados_residence";
				DeleteAttribute(npchar, "protector.CheckAlways");
				}
				break;
			}
			if (CheckAttribute(pchar, "questTemp.LSC.nrv_friend") && !CheckAttribute(pchar, "questTemp.LSC.rvd_friend")) 
			{
				dialog.text = "There is nothing for friends of Narwhal to do inside Eddie's cabin! This is his direct order. Get lost!";
				link.l1 = "I didn't want to see him either...";
				link.l1.go = "exit";
				NextDiag.TempNode = "Rivados_residence";
				DeleteAttribute(npchar, "protector.CheckAlways");
				break;
			}
			if (GetCharacterIndex("Chimiset") == -1) // Чимисет убит
			{
				dialog.text = "There is nothing for you to do inside Eddie's cabin! This is his direct order. Get lost!";
				link.l1 = "I didn't want to see him either...";
				link.l1.go = "exit";
				NextDiag.TempNode = "Rivados_residence";
				DeleteAttribute(npchar, "protector.CheckAlways");
				break;
			}
			if (stf(environment.time) >= 6.00 && stf(environment.time) < 21.00) // лесник . диалог от времени суток .
			{
			dialog.text = "Do you want to see Eddie? Fine, move along, I suppose he will spare a minute for you.";
			link.l1 = "Thanks for allowing to...";
			link.l1.go = "exit";
			NextDiag.TempNode = "Rivados_residence";
			DeleteAttribute(npchar, "protector.CheckAlways");
			}
			else // лесник режим пропуска.
			{
            dialog.text = "Do you want to see Eddie? No more visits today, come back in the morning and he will spare a minute for you.";
			link.l1 = "Alright...";
			link.l1.go = "exit";
			NextDiag.TempNode = "Rivados_residence";
			DeleteAttribute(npchar, "protector.CheckAlways");
            }			
		break;
		
		case "Rivados_soldier":
			if (CheckAttribute(pchar, "GenQuest.RivadosConflict"))
			{
				dialog.text = LinkRandPhrase("Lads, careful, there is the aggressive psycho! To arms!","Enemy is here! To arms!","Ah, you are a sick bastard! Now we will teach you a lesson!");
				link.l1 = "Fuck!";
				link.l1.go = "Rcheck_parol_fight";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.LSC.rvd_friend")) 
			{
				dialog.text = TimeGreeting()+", "+pchar.name+"! How are you doing?";
				link.l1 = "I am fine, thanks...";
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = "Listen, pal, I am not in a mood to talk. Move along...";
				link.l1 = "Fine.";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "Rivados_soldier";
		break;
//------------------------------------- фразы гардов пиратов --------------------------------------------	
		// у склада
		case "Shark_storage":
			if (CheckAttribute(pchar, "GenQuest.SharkConflict"))
			{
				dialog.text = LinkRandPhrase("Lads, careful, there is the armed psycho! To arms!","Enemy is here! To arms!","Ah, you are bastard! Now we will kick your ass!");
				link.l1 = "Damn!";
				link.l1.go = "shark_guard_fight";
				break;
			}
			dialog.text = "Stop! This is a restricted area!";
			link.l1 = "Fine, as you say...";
			link.l1.go = "exit";
			NextDiag.TempNode = "Shark_storage";
		break;
		
		// у резиденции
		case "Shark_residence":
			if (CheckAttribute(pchar, "GenQuest.SharkConflict"))
			{
				dialog.text = LinkRandPhrase("Lads, careful, there is the armed psycho! To arms!","Enemy is here! To arms!","Ah, you are bastard! Now we will kick your ass!");
				link.l1 = "Damn!";
				link.l1.go = "shark_guard_fight";
				break;
			}
			if (stf(environment.time) >= 6.00 && stf(environment.time) < 21.00)
			{
				if (pchar.questTemp.LSC == "begin" || pchar.questTemp.LSC == "mary") // тока прибыл
				{
					dialog.text = "Stop! You are not one of ours... Is Shark waiting for you or are you just walking around with no purpose?";
					link.l1 = "Shark? Steve Dodson?";
					link.l1.go = "first_talk_day";
				}
				else
				{
				dialog.text = "Admiral will accept you. Move along.";
				link.l1 = "Thanks!";
				link.l1.go = "exit";
			}
			}
			else
			{
				if (pchar.questTemp.LSC == "begin" || pchar.questTemp.LSC == "mary") // тока прибыл
				{
					dialog.text = "Where are you rushing to? It is night, don't you see! Or are you really thinking that the admiral will wake up to greet you personally? Come in the morning.";
					link.l1 = "As you say. And where can I have a rest?";
					link.l1.go = "first_talk_night";
				}
			else
			{
				dialog.text = "It's late, admiral is not recepting now. Come back tomorrow.";
				link.l1 = "Fine...";
				link.l1.go = "exit";
			}
			}
			NextDiag.TempNode = "Shark_residence";
		break;
		
		case "Shark_soldier":
			if (CheckAttribute(pchar, "GenQuest.SharkConflict"))
			{
				dialog.text = LinkRandPhrase("Lads, careful, there is the armed psycho! To arms!","Enemy is here! To arms!","Ah, you are bastard! Now we will kick your ass!");
				link.l1 = "Damn!";
				link.l1.go = "shark_guard_fight";
				break;
			}
			dialog.text = "Admiral won't be glad if he sees me talking. Move along.";
			link.l1 = "Okay...";
			link.l1.go = "exit";
			NextDiag.TempNode = "Shark_soldier";
		break;
		
		case "first_talk_night":
			dialog.text = NPCStringReactionRepeat("Are you drunk? Turn back and walk through the bridge, pass two ships and then you will find another bridge which will take you to the tavern. Sleep there.", 
				"Are you trying to piss me off? I have just told you what to do. Get lost!", 
				"Go and have a sleep, drunk face...",
				"Go away!!", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Thanks, sir. You could be more polite, actually...", 
				"I am sorry, I forgot...",
				"I am not drunk!", 
				"What?!", npchar, Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("exit", "", "", "", npchar, Dialog.CurrentNode);
		break;
		
		case "first_talk_day":
			dialog.text = "Don't make round eyes, lad. Everybody knows that Steve Shark is our admiral. Do you have any business for him?";
			link.l1 = "Yes, damn it! I have business for him and it is urgent.";
			link.l1.go = "first_talk_day_1";
		break;
		
		case "first_talk_day_1":
			dialog.text = "And what kind of business?";
			link.l1 = "I will tell about it only to Shark in private. I am working for Jan Swanson, do you know him?";
			link.l1.go = "first_talk_day_2";
		break;
		
		case "first_talk_day_2":
			dialog.text = "Forest Devil? Ha! Half of Main knows that man. Listen, lad, don't be stubborn. Either explain yourself or get lost before I get angry. Shark said to spare him from useless people and I am just doing as he ordered.";
			link.l1 = "Fine. Here, take a look at this letter, it's written by Forest Devil to Shark.";
			link.l1.go = "first_talk_day_3";
		break;
		
		case "first_talk_day_3":
			PlaySound("interface\important_item.wav");
			dialog.text = "(looking)... Fine. I suppose, Steve will find it interesting. Move along.";
			link.l1 = "Oh, really? Give the letter back if it won't be too hard for you, please.";
			if (pchar.questTemp.LSC == "mary") link.l1.go = "first_talk_day_5";
			else link.l1.go = "first_talk_day_4";
		break;
		
		case "first_talk_day_4":
			PlaySound("interface\important_item.wav");
			npchar.dialog.currentnode = "First time";
			DialogExit();
			LSC_OpenSanAvgustinDoors(); // открываем Сан-Августин
			LocatorReloadEnterDisable("LostShipsCity_town", "reload2", true); //закрываем кладовку со стороны моря
			pchar.quest.LSC_entry_pantry.over = "yes"; //снять прерывание на арест
			pchar.quest.LSC_findMary.over = "yes"; //снять прерывание на Мэри
			pchar.questTemp.LSC = "entrance"; //меняем флаг
			sld = characterFromId("Dodson");
			sld.dialog.currentnode = "entrance";
			// закрываем вход к Мэри
			LocatorReloadEnterDisable("LostShipsCity_town", "reload60", true);
			LocatorReloadEnterDisable("LostShipsCity_town", "reload61", true);
		break;
		
		case "first_talk_day_5":
			PlaySound("interface\important_item.wav");
			npchar.dialog.currentnode = "First time";
			DialogExit();
			LSC_OpenSanAvgustinDoors(); // открываем Сан-Августин
			sld = characterFromId("Dodson");
			sld.dialog.currentnode = "entrance";
		break;
		
		case "shark_guard_fight":
			DialogExit();
			LAi_SetGuardianType(NPChar);
			LAi_group_MoveCharacter(NPChar, "LSC_SHARK");
			LAi_group_Attack(NPChar, Pchar);
		break;
		
		case "":
			dialog.text = "";
			link.l1 = "";
			link.l1.go = "";
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
	}
}