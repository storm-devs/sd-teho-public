// Addon-2016 Jason, французские миниквесты (ФМК) Последний урок
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
		
		case "greguar":
			PlaySound("VOICE\Russian\QuestMan03.wav");
			pchar.quest.FMQL_delete_guide.over = "yes";
			if (CheckAttribute(pchar, "questTemp.HWIC") || pchar.Ship.Type == SHIP_NOTUSED)
			{
				dialog.text = "Oh, "+GetFullName(pchar)+"! You look different and you are successful! They start talking about you, you know? You learn fast, monseniour, I feel really proud. I wish you more fortunes and luck in the future! Pleasure to meet you!";
				link.l1 = "Monseniour Gregoire Valinnie, what a meeting! I owe you a great deal for my humble achievements. Pleasure to meet you too! Good luck!";
				link.l1.go = "greguar_exit_1";
			}
			else
			{
				dialog.text = "Oh, "+GetFullName(pchar)+"! You look different and you are successful! They start talking about you, you know? You learn fast, monseniour, I feel really proud.";
				link.l1 = "Monseniour Gregoire Valinnie, what a meeting! I owe you a great deal for my humble achievements. Pleasure to meet you! Let me guess, you have a business proposal to me?";
				link.l1.go = "greguar_1";
			}
		break;
		
		case "greguar_1":
			dialog.text = "True. I'll be brief, time is money. So, a Dutch crown squadron sailing from Brazil to Curacao with a cargo of goods of strategic value was ambushed by the English between Trinidad and the mainland. One flute of the Company had managed to flee and to moor to Boca de la Serpienta Coast. Saved a part of the cargo yet not for long - they were attacked by a local Indian tribe\nAccording to my information, they had wiped out every Dutch on that coast and took the cargo to their village. The Indians also grabbed the Dutch firearms but had suffered heavy casualties. This is our chance! The Brits and the Dutch are still fighting in that region and too busy to care about the lost flute. For now... You have a ship and crew. We can sail there, land and finish off the Indians. The cargo is extremely valuable and there is a great deal of it there\nI have already sent a small expedition to do scouting - that was all I could afford, money problems, remember? I have a trustworthy buyer, you can count on my sword and my mercenaries. Fifty-fifty split, we have a week to get there. Are you in?";
			link.l1 = "Forgive me, monseniour, but I'll pass. I am just off a tough voyage, we don't have enough time to do repairs and recruitment. Even in this God forgotten place a man can not have everything.";
			link.l1.go = "greguar_exit";
			link.l2 = "It sounds like a serious business with a smell of decent profit. I am in. Let's not waste time!";
			link.l2.go = "greguar_2";
		break;
		
		case "greguar_exit":
			dialog.text = "Pity. It's your call then. Godspeed, monseniour, I will head there anyway. A man must try, huh?";
			link.l1 = "Godspeed, monseniour Valinnie!";
			link.l1.go = "greguar_exit_1";
		break;
		
		case "greguar_exit_1":
			DialogExit();
			npchar.lifeday = 0;
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload5_back", "none", "", "", "", 20.0);
		break;
		
		case "greguar_2":
			dialog.text = "Right choice, my friend! You can use extra money, correct? How's your brother by the way?";
			link.l1 = "I can always use extra money. Michel? My brother is in good health and he is bored. I envy him sometimes... Time to set sail!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("FMQL_Begin");
		break;
		
		case "greguar_3":
			PlaySound("VOICE\Russian\QuestMan02.wav");
			dialog.text = "Easy as pie! These were the rookies who survived the skirmish with the Dutch. We should head deeper in the mainland, my expedition must be there!";
			link.l1 = "Too easy... Too early to celebrate, monseniour Valinnie. Take a look over there...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("FMQL_SecondCoastBattle");
		break;
		
		case "greguar_4":
			dialog.text = "Damn these redskins! They almost had us! Now I am certain there are only women and children left in the village. Move out!";
			link.l1 = "I am not that certain.. Move!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("FMQL_GoToJungle");
		break;
		
		case "greguar_5":
			PlaySound("VOICE\Russian\MiddPirate04.wav");
			dialog.text = "Meaning? The Dutch and us must had killed them all!";
			link.l1 = "";
			link.l1.go = "greguar_6";
		break;
		
		case "greguar_6":
			DialogExit();
			if (CheckAttribute(pchar, "questTemp.Prosper_fmql")) sld = CharacterFromID("FMQL_Prosper");
			else sld = CharacterFromID("FMQL_mercen");
			sld.dialog.currentnode = "prosper_3";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "greguar_7":
			dialog.text = "To flee? Are you mad? We are almost there! Are you scared of a bunch of painted savages?";
			link.l1 = "";
			link.l1.go = "greguar_8";
		break;
		
		case "greguar_8":
			DialogExit();
			if (CheckAttribute(pchar, "questTemp.Prosper_fmql")) sld = CharacterFromID("FMQL_Prosper");
			else sld = CharacterFromID("FMQL_mercen");
			sld.dialog.currentnode = "prosper_5";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "greguar_9":
			dialog.text = "The lowest of the low things, captain. I am going back to Europe. I am disappointed! In you, in these cowards and in this fucking region!";
			link.l1 = "...";
			link.l1.go = "greguar_10";
		break;
		
		case "greguar_10":
			DialogExit();
			DoQuestReloadToLocation("shore18", "goto", "goto8", "FMQL_JungleExit");
		break;
		
		case "greguar_11":
			PlaySound("VOICE\Russian\MiddPirate04.wav");
			dialog.text = "Fuh! We did it!";
			link.l1 = "But for what price! Look! Almost everyone of our squad is dead. We should retreat, Gregoire, no guarantees that there are no more warriors waiting for us. Plus, we simply lack numbers to carry the loot.";
			link.l1.go = "greguar_12";
		break;
		
		case "greguar_12":
			dialog.text = "Damn it! It's sad, but you are right, "+pchar.name+": even if the savages are all dead meat, we won't be able to carry away the cargo before the Dutch or the English land here. We must leave now! Screw this damned coast!";
			link.l1 = "...";
			link.l1.go = "greguar_10";
		break;
		
		case "greguar_13":
			PlaySound("VOICE\Russian\QuestMan02.wav");
			dialog.text = "Fuh! We did it! Nicely done, "+pchar.name+"! Now let's move to the den of savages for our prize! Nothing can stop us now!";
			link.l1 = "We should hurry while the Brits and the Dutch are still busy with each other. Move!";
			link.l1.go = "greguar_14";
		break;
		
		case "greguar_14":
			DialogExit();
			DoQuestCheckDelay("FMQL_RunToGrabbing", 1.0);
		break;
		
		case "greguar_15":
			PlaySound("VOICE\Russian\QuestMan01.wav");
			dialog.text = "We did well, "+pchar.name+". Now all we need is to sell the cargo without causing any suspicions. I have a solid buyer, he will wait for us at Lamentin bay at midnight. Don't take any officers and avoid the place before the meeting, the client is a very nervous fellow.";
			link.l1 = "Business is business. The cargo must be sold and it must be done safely, otherwise my debt to Poincy will increase even higher. Fine, I will be there by midnight.";
			link.l1.go = "greguar_16";
		break;
		
		case "greguar_16":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload3_back", "none", "", "", "OpenTheDoors", 10.0);
			pchar.quest.FMQL_goods_timer.win_condition.l1 = "Timer";
			pchar.quest.FMQL_goods_timer.win_condition.l1.date.hour  = 0.0;
			pchar.quest.FMQL_goods_timer.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.FMQL_goods_timer.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.FMQL_goods_timer.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.FMQL_goods_timer.function = "FMQL_MeetingOnLamanten";
			AddQuestRecord("FMQ_Lesson", "7");
			LAi_LocationDisableOfficersGen("Shore38", true); // may-16
			LAi_LocationFightDisable(&Locations[FindLocation("Shore38")], true);
			locations[FindLocation("Shore38")].DisableEncounters = true;
		break;
		
		case "greguar_17":
			PlaySound("VOICE\Russian\Master_01.wav");
			pchar.quest.FMQL_goods_over.over = "yes";// лесник снято прерывание на встречу.
			dialog.text = "It is done. Cargo is unloaded, the client is here. Let's do the talking.";
			link.l1 = "...";
			link.l1.go = "greguar_18";
		break;
		
		case "greguar_18":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			for (i=1; i<=3; i++)
			{
				sld = CharacterFromID("FMQL_contra_"+i);
				if (i == 2) LAi_CharacterEnableDialog(sld);
			}
		break;
		
		case "greguar_19":
			dialog.text = "Surprise, you bastards!";
			link.l1 = "";
			link.l1.go = "exit";
			AddDialogExitQuest("FMQL_LookOnGuards");
		break;
		
		case "greguar_20":
			PlaySound("VOICE\Russian\OliverTrast01.wav");
			dialog.text = "Ah, Johnny, what a guy! Great! You have anything to say, "+pchar.name+"?";
			link.l1 = "No. Actually, yes! What the fuck?!";
			link.l1.go = "greguar_21";
		break;
		
		case "greguar_21":
			dialog.text = "Don't tease the dead man, monseniour. Where are your manners?.. Money is here, the cargo is taken care of by me and my friends. I didn't send them to the coast, it would had been a waste. Especially sending Johnny there. See that redskin fellow with a coulevrine in his hands? You know, Johnny never really liked his own tribe.";
			link.l1 = "I see... What now? Are you gonna kill me now?";
			link.l1.go = "greguar_22";
		break;
		
		case "greguar_22":
			dialog.text = "Well, I should. But I am sentimental. Leave and take a quarter of cash. The cargo and the rest of the money will stay here with me. Don't try to play hero, this is not the jungles of mainland. You stand no chance.";
			link.l1 = "And where are your nobility and manners, Gregoire? I didn't see this coming from you. I am leaving, but this was quite an instructive experience.";
			link.l1.go = "greguar_23";
			link.l2 = "I am not playing hero. I will simply kill you all. You first, then the ape with a grenade launcher and then these ladies.";
			link.l2.go = "greguar_25";
		break;
		
		case "greguar_23":
			dialog.text = "There are no neither nobles, nor thugs on this beach, monseniour. There are only five men, a big gun and a victim. This happens here all the time, but you've made the only right choice. Well done. Do you know that instead of you there could be two others in your shoes, standing right here, right now? They are almost just like you. But you are here and they are not, and I think they will perish because of it.";
			link.l1 = "I don't follow...";
			link.l1.go = "greguar_24";
		break;
		
		case "greguar_24":
			dialog.text = "One day you will. They didn't receive their final lesson. You did. You are welcome. Farewell, monseniour. Welcome to the Caribbean!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuest("FMQL_PeaceFinal");
		break;
		
		case "greguar_25":
			dialog.text = "You are not the brightest student. Very well... to each his own.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuest("FMQL_BattleOnBeach");
		break;
		
		case "mercen":
			PlaySound("VOICE\Russian\pirat_guard_4.wav");
			dialog.text = "Perfect timing! We barely fled from the horde of the Caribs, they were heading at your direction and, by your look, you have already met them. Their village is nearby but our problems are only about to begin.";
			link.l1 = "";
			link.l1.go = "prosper_2";
		break;
		
		case "prosper":
			PlaySound("VOICE\Russian\pirat_guard_4.wav");
			dialog.text = ""+GetFullName(pchar)+"! You are here! And why am I not surprised! Perfect timing, my friend. We barely fled from the horde of the Caribs, they were heading at your direction and, by your look, you have already met them.";
			link.l1 = "Prosper! And I am surprised! Making holes in the Indians again? Hope Selina's fine?";
			link.l1.go = "prosper_1";
		break;
		
		case "prosper_1":
			dialog.text = "It was foolish of me to join this expedition, I wonder if my daughter will ever see me again. Selina? She is sitting home and dreaming of you! Youngsters of Martinique have lost any hope by now... You know, I don't regret buying this musket anymore. A solid firearm. Reliable. Also an additional reason to take part in another suicide endeavor, although it is now a bit less suicidal since you have shown up. Their village is nearby but our problems are only about to begin.";
			link.l1 = "";
			link.l1.go = "prosper_2";
		break;
		
		case "prosper_2":
			DialogExit();
			sld = CharacterFromID("Guide_y");
			sld.dialog.currentnode = "greguar_5";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "prosper_3":
			dialog.text = "Not all of them. Our scout got shot but still managed to get to their lair. A chief himself is coming here with his guards. And they have Dutch muskets. They have an advantage in numbers and they are furious as hell. The chief is the best warrior of the tribe, his men are devils in flesh. We should decide quickly, here and right now. It's either we give them a fight or we flee. I like the latter more, to be honest...";
			link.l1 = "";
			link.l1.go = "prosper_4";
		break;
		
		case "prosper_4":
			DialogExit();
			sld = CharacterFromID("Guide_y");
			sld.dialog.currentnode = "greguar_7";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "prosper_5":
			dialog.text = "You haven't seen them, my good man! These 'savages' have muskets and they are surprisingly good with them. Someone had been giving them lessons, that's no doubt! So don't call me a coward!";
			link.l1 = "Let's calm down and decide what to do. There is still time.";
			link.l1.go = "prosper_6";
		break;
		
		case "prosper_6":
			int n = 0;
			for (i=1; i<=5; i++)
			{
				if (GetCharacterIndex("FMQL_sailor_"+i) != -1) n++;
			}
			dialog.text = "I am listening, "+pchar.name+".";
			if (n > 2 && GetSummonSkillFromName(pchar, SKILL_SNEAK) > 30)
			{
				link.l1 = "We will give them a fight, boys! There are goods and money right behind this hill! We are here for them and we are not leaving. No way some bunch of redskins, even with muskets, can stop us! Let's bury the fuckers and finish the job! We have enough men, there is a chance to ambush them. Four men will greet them with fire from flanks and the rest of us will take positions here. Cut their numbers and finish them off!";
				link.l1.go = "prosper_8";
			}
			else
			{
				if (n > 0)
				{
					link.l1 = "We will give them a fight, boys! There are goods and money right behind this hill! We are here for them and we are not leaving. No way some bunch of redskins, even with muskets, can stop us! Let's bury the fuckers and finish the job!";
					link.l1.go = "prosper_7";
				}
				else
				{
					link.l1 = "Chances are against us in every possible way. Don't forget about the Dutch right behind us.";
					link.l1.go = "prosper_9";
				}
			}
		break;
		
		case "prosper_9":
			DialogExit();
			sld = CharacterFromID("Guide_y");
			sld.dialog.currentnode = "greguar_9";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "prosper_7":
			DialogExit();
			pchar.questTemp.FMQL = "battle";
			AddDialogExitQuestFunction("FMQL_PrepareAttack");
		break;
		
		case "prosper_8":
			DialogExit();
			pchar.questTemp.FMQL = "sneak";
			AddDialogExitQuestFunction("FMQL_PrepareSneakAttack");
		break;
		
		case "prosper_9x":
			PlaySound("VOICE\Russian\pirat_guard_2.wav");
			dialog.text = "We are alive and we are home! I swear, I had enough of adventures... for the next few months, ha-ha! I should go to my daughter, please come visit us, "+pchar.name+". And please, be careful.";
			link.l1 = "No promises, Prosper. Godspeed!";
			link.l1.go = "prosper_10";
		break;
		
		case "prosper_10":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload4_back", "none", "", "", "OpenTheDoors", 10.0);
		break;
		
		case "prosper_11":
			pchar.quest.FMQL_prosper_dead.over = "yes";
			LAi_RemoveCheckMinHP(npchar);
			PlaySound("VOICE\Russian\pirat_guard_4.wav");
			dialog.text = "I've warned you, captain, to be careful! I had suspicions about this bastard.";
			link.l1 = "Prosper! Thank you! But how?";
			link.l1.go = "prosper_12";
		break;
		
		case "prosper_12":
			sTemp = "";
			if (CheckAttribute(pchar, "questTemp.FMQL.PirateDead")) sTemp = "Poor lad, even though he was a pirate.";
			dialog.text = "Johnny got too talkative. The redskin fellow on the sand. He came to a brothel and made an attempt to pick up a girl. They refused to service him, Johnny got furious, started shouting that he is going to be rich soon, once he and his pals will kill some captain in the jungles. I saw what was coming and ran to your officer who also managed to get some infamy in the town. "+sTemp+" I owe you a great deal, "+pchar.name+", so there is no need to thank me too hard.";
			link.l1 = "And still, thank you very much, Prosper! It was tough here... too tough. Want to join my crew? I need an officer like yourself. It's hard to find loyal men these days, especially sharpshooters.";
			link.l1.go = "prosper_13";
		break;
		
		case "prosper_13":
			dialog.text = "No, my friend. I have obligations to my daughters. She made me swear to leave my adventures behind. It was my last one. Dammit, what a pity, but I love my daughter more than anything in the world. Farewell, "+pchar.name+". And.. Selina is talking about you all the time. Perhaps, you could pay us a visit someday?";
			link.l1 = "Who knows, maybe I will... Farewell, Prosper! Peace to your home... (to oneself) Lesson learnt, monsieur Gregoire. What did you say? To each his own? I should remember this line.";
			link.l1.go = "prosper_14";
		break;
		
		case "prosper_14":
			DialogExit();
			LAi_SetActorType(npchar);
			npchar.lifeday = 0;
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", 15.0);
			chrDisableReloadToLocation = false;
			InterfaceStates.Buttons.Save.enable = true; // разрешим сохраняться
			AddQuestRecord("FMQ_Lesson", "15");
			CloseQuestHeader("FMQ_Lesson");
			pchar.questTemp.FMQL = "end";
		break;
		
		case "contra":
			dialog.text = "Who the hell you are?";
			link.l1 = "We have the cargo. Interested?";
			link.l1.go = "contra_1";
		break;
		
		case "contra_1":
			dialog.text = "Ha. Very interested. My client's especially. What's the take?";
			link.l1 = ""+FindRussianQtyString(sti(pchar.questTemp.FMQL.Sanl))+" of ironwood, "+FindRussianQtyString(sti(pchar.questTemp.FMQL.Silk))+" of ship silk, "+FindRussianQtyString(sti(pchar.questTemp.FMQL.Rope))+" of rope and "+FindRussianQtyString(sti(pchar.questTemp.FMQL.Oil))+" of resin.";
			link.l1.go = "contra_2";
		break;
		
		case "contra_2":// Addon 2016-1 Jason пиратская линейка
			iTotalTemp = 2200*sti(pchar.questTemp.FMQL.Sanl)+1600*sti(pchar.questTemp.FMQL.Silk)+1000*sti(pchar.questTemp.FMQL.Rope)+900*sti(pchar.questTemp.FMQL.Oil);
			dialog.text = "Very well. 2200 pesos for every piece of ironwood, 900 pesos for resin, 1600 pesos for ship silk and 1000 pesos for ropes. What do we have here... Well-well. "+iTotalTemp+" pesos. Deal?";
			link.l1 = "Deal!";
			link.l1.go = "contra_3";
		break;
		
		case "contra_3":
			LAi_Fade("", "");
			FMQL_CreateGuidesWarriors();
			dialog.text = "Splendid! Bring more. The Dutch never cease to be generous to the redskins... And who are these guests? What the fuck?!";
			link.l1 = "";
			link.l1.go = "contra_4";
		break;
		
		case "contra_4":
			DialogExit();
			sld = CharacterFromID("Guide_y");
			sld.dialog.currentnode = "greguar_19";
			AddMoneyToCharacter(sld, iTotalTemp);
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "FMQL_beach":
			pchar.quest.FMQL_pirate_dead.over = "yes";
			LAi_RemoveCheckMinHP(npchar);
			dialog.text = "Yeah, captain. I had over drunk the sailing for a reason.";
			link.l1 = "You? How?!";
			link.l1.go = "FMQL_beach_1";
		break;
		
		case "FMQL_beach_1":
			dialog.text = "I am sorry, captain. I had to drink a cup or two after that mess with the Indians. There was a girl, I took a room for a hundred pesos and she... she...";
			link.l1 = "Robbed you?";
			link.l1.go = "FMQL_beach_2";
		break;
		
		case "FMQL_beach_2":
			sld = CharacterFromID("FMQL_Prosper");
			dialog.text = "No! She fell in love! Damn it, I should had run away from there! But then your friend shows up, yelling at me about this scum, your former companion, who want to screw you and kill you.";
			if (LAi_GetCharacterHP(sld) > 0)
			{
				link.l1 = "Well done, Prosper...";
				link.l1.go = "FMQL_beach_3";
			}
			else
			{
				link.l1 = "Prosper... I am so sorry. I will take care of your daughter. Lesson learnt, monseniour Gregoire... What did you say? To each his own? I should remember this.";
				link.l1.go = "FMQL_beach_3";
			}
		break;
		
		case "FMQL_beach_3":
			dialog.text = "Shall we go, captain?";
			link.l1 = "Yeah. Thank you for your service. Stay away from a cup and we will save you from that beauty. Let's go.";
			if (CheckAttribute(pchar, "questTemp.FMQL.ProsperDead")) link.l1.go = "FMQL_beach_5";
			else link.l1.go = "FMQL_beach_4";
		break;
		
		case "FMQL_beach_4": // Проспер жив
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload_sea", "none", "", "", "FMQL_PirateNormal", 10.0);
			sld = CharacterFromID("FMQL_Prosper");
			sld.Dialog.currentnode = "prosper_11";
			sld.MusketerDistance = 20;
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0); 
		break;
		
		case "FMQL_beach_5":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "sea", "none", "", "", "FMQL_PirateNormal", 10.0);
			if (sti(pchar.money) >= 20000) DoQuestFunctionDelay("FMQL_MoneyForSelina", 0.5);
			else
			{
				pchar.quest.FMQL_money_20k.win_condition.l1 = "Money";
				pchar.quest.FMQL_money_20k.win_condition.l1.value = 20000;
				pchar.quest.FMQL_money_20k.win_condition.l1.operation = ">=";
				pchar.quest.FMQL_money_20k.function = "FMQL_MoneyForSelina";
			}
			chrDisableReloadToLocation = false;
			InterfaceStates.Buttons.Save.enable = true; // разрешим сохраняться
			AddQuestRecord("FMQ_Lesson", "10");
			CloseQuestHeader("FMQ_Lesson");
			pchar.questTemp.FMQL = "end";
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
