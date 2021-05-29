// Джон Мердок, он же Йохан ван Мерден, соратник Роденбурга
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	string sTemp;
	int iTemp;
	bool bOk;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
		if (!CheckAttribute(pchar, "questTemp.HWIC.Self") && LAi_grp_playeralarm > 0)
		{
			dialog.text = "I don't think, mister, that you've chosen a good time for talking. The garrison is after you. You'd better get away...";
			link.l1 = "Don't worry. I will not stay at your place for long.";
			link.l1.go = "exit";
			break;
		}
		// продажа алхимического набора, если провалил гамбит
		if (CheckAttribute(pchar, "questTemp.HWIC.Detector") && !CheckAttribute(npchar, "quest.alchemy"))
		{
			bOk = (findsubstr(pchar.questTemp.HWIC.Detector, "_fail" , 0) != -1) || (pchar.questTemp.HWIC.Detector == "eng_win_half");
			if (bOk)
			{
				dialog.text = "Welcome, captain. Won't you be interested in one intriguing offer? ";
				link.l1 = "I've always been curious, so speak up. What kind of offer is it? ";
				link.l1.go = "alchemy";
				break;
			}
		}
		// Страж Истины
		if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "merdok1")
		{
			dialog.text = "Good afternoon. I am happy to welcome you in my drugstore. I have medicines to treat most diseases and infirmities. What can I offer you?";
			link.l1 = "Listen, John, there are rumours that somebody is living at your place on the second floor...";
			link.l1.go = "guardoftruth";
			break;
		}
//-----------------------------------------за Голландию------------------------------------------------
		if (CheckAttribute(pchar, "questTemp.HWIC.Holl"))
		{
			if (pchar.location.from_sea == "SentJons_town" && pchar.questTemp.HWIC.Holl == "toAntigua")
			{
				dialog.text = "Good afternoon. I am happy to see you in my drugstore. I have medicines to treat most diseases and infirmities. What can I offer you?";
				link.l1 = "Hello Mr. Murdock. I am here on behalf of Lucas Rodenburg. He sent me to you to discuss a matter regarding Richard Fleetwood.";
				link.l1.go = "Knippel_exit";
				break;
			}
			if (pchar.questTemp.HWIC.Holl == "toAntigua")
			{
				dialog.text = "Good afternoon. What kind of problem do you have? Cough mixture or diarrhoea powder?";
				link.l1 = "Hello, Mr. Murdock. I am here on behalf of Lucas Rodenburg. He sent me to you to discuss a matter regarding Richard Fleetwood.";
				link.l1.go = "Knippel";
				break;
			}
			if (pchar.questTemp.HWIC.Holl == "KillMerdok")
			{
				dialog.text = "Ha, here is the Rodenburg's top mercenary... Hercule, Longway - come here! To fight!";
				link.l1 = "Hup!";
				link.l1.go = "Merdok_fight";
				break;
			}
			dialog.text = "Good afternoon. I am happy to see you in my drugstore. I have medicines to treat most diseases and infirmities. What can I offer you?";
			link.l1 = "Nothing at the moment, thank you. I feel quite well.";
			link.l1.go = "exit";
			break;
		}
//----------------------------------------------за Англию---------------------------------------------------
			if (CheckAttribute(pchar, "questTemp.HWIC.Eng") && pchar.questTemp.HWIC.Eng == "MerdokMeeteng")
			{
			dialog.text = "Hello, uninvited guest. You do not cover your face with a mask and are not swift to attack. Therefore I come to a conclusion that you need something else from a poor druggist. Maybe, a diarrhoea mixture?";
			link.l1 = "Hail to you, too, Johan van Merden. I come to say hi from Hercule Tonzag. I see you know this name.";
			link.l1.go = "Merdok_talk";
			break;
			}
//--------------------------------------------против всех--------------------------------------------------
			if (CheckAttribute(pchar, "questTemp.HWIC.Self"))
			{
				if (pchar.questTemp.HWIC.Self == "HuntFleetwood")
				{
					dialog.text = "Ah, so here you are. Well, have you met Hercule? ";
					link.l1 = "Yes. We've talked and we've come to an agreement. John, I am going to help Hercule, and I have several questions for you regarding Richard Fleetwood.";
					link.l1.go = "About_Fleetwood";
					break;
				}
				if (GetQuestPastDayParam("questTemp.Wait_Fleetwood") > 6 && pchar.questTemp.HWIC.Self == "WaitFleetwood")
				{
					dialog.text = "Hello! I am glad to see you, " + pchar.name + "!";
					link.l1 = "Hello, John. Did you dig any dirt on Fleetwood?";
					link.l1.go = "About_Fleetwood_9";
					pchar.quest.Wait_FleetwoodOver.over = "yes"; //снять таймер
					break;
				}
				if (pchar.questTemp.HWIC.Self == "HWICSelf_fail")
				{
					dialog.text = "At last. When did I tell you to come? In general, there's no good news. Charlie Knippel had visited Willemstad and brought one girl from there for Richard, and now they are going to sail to England with a military squadron in a day or two. So... you will not be able to get him anymore.";
					link.l1 = "I see. Heh, I've been involved with some other things and totally forgotten about Richard. Fine. See you.";
					link.l1.go = "About_Fleetwood_17";
					break;
				}
				if (pchar.questTemp.HWIC.Self == "AbigileOnShip")
				{
					dialog.text = "Welcome back, " + pchar.name + "! So, what can you tell? There is no news about Fleetwood, and Charlie Knippel has not returned from Curacao yet...";
					link.l1 = "And he never will. Neither he, nor his brigantine.";
					link.l1.go = "Abigile";
					break;
				}
				if (pchar.questTemp.HWIC.Self == "AbigileInHouse")
				{
					dialog.text = "Ah, what guests we have! Hello, Charlie! Good afternoon, miss!";
					link.l1 = "Good afternoon, John! Let me introduce you our dear guest, Richard's fiancee, charming Abigail Shneur.";
					link.l1.go = "Abigile_7_1";
					break;
				}
				if (pchar.questTemp.HWIC.Self == "AbigileInRoom")
				{
					dialog.text = "Keep your voice down... What are you going to do next?";
					link.l1 = "Next? I'd rather have some rest, but unfortunately there is no time for that. I am going to pull Fleetwood out of his hole and finish Hercule's job.";
					link.l1.go = "Abigile_9";
					break;
				}
				if (pchar.questTemp.HWIC.Self == "LetterToFleetwood")
				{
					dialog.text = "Are you done writing? Let me see... Oh, you are quite a creepy type, aren't you! Maybe too creepy. I mean the part about Abi's finger, ear and head. Ha-ha-ha! You've got a talent, definitely!";
					link.l1 = "I am simply bluffing, John. I would never kill the girl in any case... Well, perhaps I could make her part with her finger... But nothing more.";
					link.l1.go = "Abigile_15";
					break;
				}
				if (pchar.questTemp.HWIC.Self == "FleetwoodAgree")
				{
					dialog.text = "Well, how did it go? I can see it in your eyes - you have succeeded!";
					link.l1 = "Yes. Fleetwood wrote a reply and accepted my terms. The trap sprung shut. Now there is not much left to do.";
					link.l1.go = "Abigile_23";
					break;
				}
				if (pchar.questTemp.HWIC.Self == "FleetwoodDied")
				{
					dialog.text = "Ah, welcome back, my friend! Well, what can you tell me?";
					link.l1 = "Fleetwood is dead. Everything went according to the plan. He arrived at the island, where I had organized an ambush on the beach. But, to be honest, he put up quite a fight... What a carnage it was! But all that matters is that I am still alive, and he will stay there forever.";
					link.l1.go = "Abigile_27";
					break;
				}
				if (pchar.questTemp.HWIC.Self == "MeetTonzag")
				{
					dialog.text = "" + pchar.name + ", I have a serious offer for you. The matter I am going to talk about is very dangerous, but, considering the way you got rid of Fleetwood, I am sure you can manage that. You really have a talent for such things.";
					link.l1 = "I am flattered, John. But go on.";
					link.l1.go = "Lucas";
					break;
				}
				if (pchar.questTemp.HWIC.Self == "SeekAbiIsland")
				{
					dialog.text = "Welcome back, " + pchar.name + "! Any good news for me?";
					link.l1 = "From now on you can sleep without a knife under the pillow, John. Lucas will no longer be a threat to you. He is under arrest and locked up, and he is about to be sent to Holland in the nearest future, where he will be judged for an attempt of take-over the power, murder attempt and for other misdeeds.";
					link.l1.go = "Lucas_10";
					break;
				}
				if (pchar.questTemp.HWIC.Self == "VanbergDestroyed")
				{
					dialog.text = "Glad to see you, " + pchar.name + "! You are alive - and that's a good thing. Any news?";
					link.l1 = "Yes. Van Berg is gone for good. Just as you'd said, he tracked me down and attacked at the most inconvenient moment. He was a hard nut to crack, but in the end I have prevailed.";
					link.l1.go = "Final";
					break;
				}
			dialog.text = "Do you want to ask anything else?";
			link.l1 = "No, John, nothing. I am leaving.";
			link.l1.go = "exit";
			break;
			}
			dialog.text = "Good afternoon. I am happy to see you in my drugstore. I have medicines to treat most diseases and infirmities. What can I offer you?";
			link.l1 = "Nothing at the moment, thank you. I feel quite well.";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;

//--------------------------------------------за Голландию-----------------------------------------------------
		case "Knippel_exit":
			dialog.text = "I have no idea what you are talking about, sir. What Lucas Rodenburg? I have no dealings with the Dutch. You must have been mistaken.";
			link.l1 = "What? Mynheer Rodenburg sent me to you...";
			link.l1.go = "Knippel_exit_1";
		break;
		
		case "Knippel_exit_1":
			dialog.text = "Let me tell you once again - I don't know any mynheer Rodenburg. I don't have any friends or chaps among the Dutch. So if you don't need any medicines, please, leave me to do my work.";
			link.l1 = "Now that's getting interesting...";
			link.l1.go = "exit";
		break;

		case "Knippel":
			dialog.text = "Well-well... Are you from mynheer Rodenburg? Alright. I am listening to you.";
			link.l1 = "I need to organize a meeting with captain Fleetwood... in a secluded place. I have borrowed from Jacob van Berg his famous 'Mirage', that Mr. Fleetwood needs to capture so much, and I would like to inform him by chance that the 'Mirage' will be off the coast of Dominica in the nearest future. ";
			link.l1.go = "Knippel_1";
		break;
		
		case "Knippel_1":
			dialog.text = "Did Jacob give you his ship? Very interesting... I take it, now you need someone to tell Mr. Fleetwood that the 'Mirage' will soon be sailing near the coasts of Dominica, since you can't tell Richard about that yourself for particular reasons...";
			link.l1 = "Exactly. Mynheer Rodenburg recommended that I should address myself to you with this matter.";
			link.l1.go = "Knippel_2";
		break;
		
		case "Knippel_2":
			dialog.text = "In this case, Charlie Knippel is the man you need. A big friend of Fleetwood and his spy. Talk to him and mention everything you want Richard to know. Be careful, Knippel is quite simple, yet he is not a complete moron.\nYou can find him in a small hut, not far from the sea. He must be there.";
			link.l1 = "I see. Thank you, Mr. Murdock. Farewell!";
			link.l1.go = "Knippel_3";
		break;
		
		case "Knippel_3":
			DialogExit();
			pchar.questTemp.HWIC.Holl = "toKnippel";
			AddQuestRecord("Holl_Gambit", "1-16");
		break;
		
		case "Merdok_fight":
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешим драться
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			sld = characterFromId("Tonzag");
			PlaySound("VOICE\Russian\hambit\Ercule Tongzag-04.wav");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			//а вот и китаец нарисовался
			sld = characterFromId("Longway");
			LAi_SetWarriorType(sld);
			FantomMakeCoolFighter(sld, 18, 40, 40, "blade_08", "pistol1", "bullet", 70);
			if (CheckAttribute(pchar, "questTemp.HWIC.Holl.LongwayEnemy"))//враг
			{
				ChangeCharacterAddressGroup(sld, "SentJons_TownCave", "monsters", "monster8");
				LAi_group_MoveCharacter(sld, "EnemyFight");
				PlaySound("VOICE\Russian\hambit\Longway-02.wav");
			}
			if (CheckAttribute(pchar, "questTemp.HWIC.Holl.LongwayFriend"))//друг
			{
				LAi_warrior_DialogEnable(sld, true);
				sld.Dialog.Filename = "Quest\HollandGambit\Longway.c";
				sld.dialog.currentnode = "Longway_hire";
				ChangeCharacterAddressGroup(sld, "SentJons_TownCave", "monsters", "monster8");
				LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
				PlaySound("VOICE\Russian\hambit\Longway-02.wav");
			}
			if (CheckAttribute(pchar, "questTemp.HWIC.Holl.LongwayNeutral")) sld.lifeday = 0;//нейтрал - просто нет
            LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
            LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
            LAi_group_SetCheck("EnemyFight", "Merdok_AfterBattle");
            DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
//-------------------------------------------------за Англию-----------------------------------------------------
		case "Merdok_talk":
			dialog.text = "Really? I thought that poor Gaston has been burning in hell for quite some time now.";
			link.l1 = "Could well be. I found his head in a chest of an old Jew on the secret island. But he still managed to say hi to you and he also mentioned that we both have a common enemy since quite recently. Namely, Mr. Rodenburg. Tonzag said that you might have papers important to Lucas, which could lure him out of Curacao.";
			link.l1.go = "Merdok_talk_1";			
		break;
		
		case "Merdok_talk_1":
			dialog.text = "He was right. This is my archive that still keeps Rodenburg restless. It looks like he is still hanging around only because of it. Thing is that he was promised a soft job in the Committee of Directors in the Company back in good old Europe. If the information in this archive, which contains a lot of interesting things about Lucas's past and present becomes widely known, his career will suddenly come to an end. In that case the best thing he could have hoped for is to be beheaded instead of being hanged.";
			link.l1 = "Give me the archive, and I will take care about our enemy.";
			link.l1.go = "Merdok_talk_2";			
		break;
		
		case "Merdok_talk_2":
			dialog.text = "I am still alive only because I still have it with me. How do I know that you are not working for Lucas now?";
			link.l1 = "You will have to take my word on it - or die.";
			link.l1.go = "Merdok_talk_3";			
		break;
		
		case "Merdok_talk_3":
			PlaySound("VOICE\Russian\hambit\John Mardock-07.wav");
			dialog.text = "I might die rather soon - but you will die here and now! Longway, to my side!";
			link.l1 = "Ah, the Chinese is here too...";
			link.l1.go = "Merdok_fightEng";			
		break;
		
		case "Merdok_fightEng":
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешим драться
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");	
			sld = characterFromId("Longway");
			FantomMakeCoolFighter(sld, 20, 50, 50, "blade_08", "pistol1", "bullet", 80);
			LAi_SetWarriorType(sld);
			ChangeCharacterAddressGroup(sld, "SentJons_TownCave", "monsters", "monster8");
			PlaySound("VOICE\Russian\hambit\Longway-02.wav");
			LAi_group_MoveCharacter(sld, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
            LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
            LAi_group_SetCheck("EnemyFight", "Merdok_AfterBattleEng");
            DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
//----------------------------------------против всех-------------------------------------------------------
		case "MC_InHouse":
			PlaySound("VOICE\Russian\hambit\John Mardock-02.wav");
			dialog.text = "Finally, you've got on your feet. I feared that it was not going to happen any time soon.";
			link.l1 = "Hmm... Good day to you too. Who are you? And where the hell am I? How did I get there?";
			link.l1.go = "MC_InHouse_1";	
		break;
		
		case "MC_InHouse_1":
			dialog.text = "Calm down, don't ask so many questions at once, it is not good for you to get too excited. My name is John Murdock, I am a pharmacist of St. John's. You had lost consciousness in a fight with Fleetwood's men. I must say that they had given you quite a beating... It was Hercule who brought you here to my drugstore, and, well, I have healed you wounds with my potions and medicines.";
			link.l1 = "Hercule? Who is it? The man who come to help me on the street? ";
			link.l1.go = "MC_InHouse_2";			
		break;
		
		case "MC_InHouse_2":
			dialog.text = "Yes. That's him. By the way, he would like to talk to you. You need to meet him in the town. Walk through the underpass at night - this underpass starts behind the door on the ground floor of my house. Don't go out until dark - Fleetwood's guys might have remembered you, we don't want them to identify you.";
			link.l1 = "I see... And where is my ship?";
			link.l1.go = "MC_InHouse_3";			
		break;
		
		case "MC_InHouse_3":
			if (pchar.Ship.Type == SHIP_NOTUSED)
			{
				dialog.text = "Your ship was arrested, and you crew has scattered. I am sorry.";
				link.l1 = "Well, shit...";
			}
			else
			{
				dialog.text = "She is at the port, at her usual place.";
				link.l1 = "That's good to hear. I thought that I'd lost her...";
			}
			link.l1.go = "MC_InHouse_4";			
		break;
		
		case "MC_InHouse_4":
			dialog.text = "You should meet Hercule. Go to the city at night through the underpass. He will approach you. Now have some rest, and I have to return to my work.";
			link.l1 = "Alright, John. And... thank you for your help and healing!";
			link.l1.go = "MC_InHouse_5";
		break;
		
		case "MC_InHouse_5":
			NextDiag.CurrentNode = "First time";
			DialogExit();
			npchar.greeting = "merdok_2";
			AddQuestRecord("Holl_Gambit", "3-12");
			pchar.questTemp.HWIC.Self = "MainBegin";//новый флаг квеста
			sld = characterFromId("Bridgetown_tavernkeeper");
			sld.model = "barmen_3";
			sld.greeting = "barmen_1";
			sld.name = "Harry";
			sld.lastname = "Fletcher";//перерисуем бармена Бриджтауна
			LocatorReloadEnterDisable("SentJons_HouseF3", "reload1", true);//закрыть выход из аптеки через дверь
			LocatorReloadEnterDisable("SentJons_HouseF3", "reload2", false);//открыть подземелье из дома
			LocatorReloadEnterDisable("SentJons_TownCave", "reload1_back", false);//открыть дом из подземелья
			pchar.quest.Tonzag_Meeting.win_condition.l1 = "location";
			pchar.quest.Tonzag_Meeting.win_condition.l1.location = "SentJons_town";
			pchar.quest.Tonzag_Meeting.win_condition.l2 = "Night";
			pchar.quest.Tonzag_Meeting.function = "TonzagMeeting";
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "SentJons_HouseF3", "goto", "goto1", "MC_TakeCloves", -1);	
		break;
		
		case "About_Fleetwood":
			dialog.text = "Fleetwood? What do you want to know about him?";
			link.l1 = "Everything. Tell me everything you know. It seems to me that it is no secret for you why Hercule had come to Antigua. I am also in the picture, and I am on his side.";
			link.l1.go = "About_Fleetwood_1";
		break;
		
		case "About_Fleetwood_1":
			dialog.text = "What can I tell you about Fleetwood... A good fighter, a seasoned seaman. He has in his disposal a brig called 'Valkyrie' - an excellent ship, I would like to mention, with a crew of selected marines. He is at war with Holland in general and with the Dutch West India Company in particular. He has pillaged countless Dutch merchant ships. The governor of Curacao has set a record-breaking bounty on his head.";
			link.l1 = "Hmm... It is a bit unusual for an officer of the Royal Navy...";
			link.l1.go = "About_Fleetwood_2";
		break;
		
		case "About_Fleetwood_2":
			dialog.text = "Yes, indeed. He is walking a tightrope. The authorities do not officially recognize his actions and refuse to have anything to do with it, but they actualy encourage him behind the scene. I have reasons to suppose that he is somehow connected with the British military intelligence, and those guys are not someone to be messed with.";
			link.l1 = "A serious man... Is this all? Hercule told me about one assistant of his... Charlie... what's his name... Canister or Cannonball?";
			link.l1.go = "About_Fleetwood_3";
		break;
		
		case "About_Fleetwood_3":
			dialog.text = "Knippel? Yes, there is such a fellow. Charlie Knippel used to be a sailor in the Navy, now retired. He served in the Navy as a cannoneer. Now he lives a quiet life on the shore. He is Fleetwood's eyes and ears in St. John's, so be careful with him and don't even think of questioning him about Richard - you will end up in prison in no time.";
			link.l1 = "I see. Can you tell me anything else worth mentioning about Fleetwood?";
			link.l1.go = "About_Fleetwood_4";
		break;
		
		case "About_Fleetwood_4":
			dialog.text = "An idol for all women on Antigua from sixteen to sixty. Seems that's all about him. Well I think you know what has happened to him now. He stays in bed and licks his wounds.";
			link.l1 = "Listen, John, perhaps, he has some peculiarities or weak points...";
			link.l1.go = "About_Fleetwood_5";
		break;
		
		case "About_Fleetwood_5":
			dialog.text = "What do you mean?";
			link.l1 = "Well, maybe he likes to gamble or drinks heavily or visits brothels a lot - something along these lines. Is he married?";
			link.l1.go = "About_Fleetwood_6";
		break;
		
		case "About_Fleetwood_6":
			dialog.text = "No, he's single. As for the things you mentioned - he is not known for either of these.";
			link.l1 = "I see. But, perhaps, there still is something special about him? Even a person like him must have some weak points!";
			link.l1.go = "About_Fleetwood_7";
		break;
		
		case "About_Fleetwood_7":
			dialog.text = "I don't know. Listen, let's do it this way. Come see me in a week, and I will try to dig some dirt on Fleetwood. Deal?";
			link.l1 = "Deal. Thank you, John! I will be here in a week.";
			link.l1.go = "About_Fleetwood_8";
		break;
		
		case "About_Fleetwood_8":
			DialogExit();
			pchar.questTemp.HWIC.Self = "WaitFleetwood";
			SaveCurrentQuestDateParam("questTemp.Wait_Fleetwood");
			SetFunctionTimerCondition("Wait_FleetwoodOver", 0, 0, 12, false);//чтобы не опаздывал
			LocatorReloadEnterDisable("SentJons_HouseF3", "reload1", false);//открыть выход из аптеки
			AddQuestRecord("Holl_Gambit", "3-14");
		break;
		
		case "About_Fleetwood_9":
			dialog.text = "Yes, but not much, unfortunately. And I am afraid it is of not much use, anyway.";
			link.l1 = "Spit it out! I am all ears. Every tiny detail is very important, if it has something to do with Fleetwood.";
			link.l1.go = "About_Fleetwood_10";
		break;
		
		case "About_Fleetwood_10":
			dialog.text = "Not so long ago Richard picked two Jewish refugees from an unknown island - a man and his daughter, sailing to Willemstad. The ship they had been sailing was sunk by some pirate. Fleetwood brought them to Curacao risking to be discovered. It's been several months since then. And now he sends his faithful dog Charlie Knippel to Willemstad...";
			link.l1 = "Hmm... How is it connected?";
			link.l1.go = "About_Fleetwood_11";
		break;
		
		case "About_Fleetwood_11":
			dialog.text = "I managed to learn that Charlie got an order to deliver here some girl from Willemstad, a Jew called Abigail Shneur. Yes, the girl from the island. It looks like Richard fell in love with her, since he sends his best agent for her.\nThis is it. Don't know if it helps at all.";
			link.l1 = "Hmm... But, John, that is wounderful! Ha-ha-ha! It means our warrior is in love... Well! I can't imagine anything better! Thank you! Now, John, when will this Knippel depart for Curacao?";
			link.l1.go = "About_Fleetwood_12";
		break;
		
		case "About_Fleetwood_12":
			dialog.text = "He already sailed there yesterday.";
			link.l1 = "Aha! What ship is he flying?";
			link.l1.go = "About_Fleetwood_13";
		break;
		
		case "About_Fleetwood_13":
			dialog.text = "I knew you'd ask that. Brigantine of Royal Fleet of England. Her name is 'Zeekalf'.";
			link.l1 = "'Zeekalf'? Since when are British ships given such names? Hold on, I got it!";
			link.l1.go = "About_Fleetwood_14";
		break;
		
		case "About_Fleetwood_14":
			dialog.text = "You are a quick thinker... Her real name is 'Royal Mary', but for this voyage she's  been named 'Zeekalf'. And she will fly the Dutch flag.";
			link.l1 = "Your help has been invaluable, John. I am setting off now. I will be back soon and I will need your room on the second floor, where you had healed me.";
			link.l1.go = "About_Fleetwood_15";
		break;
		
		case "About_Fleetwood_15":
			dialog.text = "What are you up to?";
			link.l1 = "I will tell you everything when I'm back. Wish me luck, John! Bye.";
			link.l1.go = "About_Fleetwood_16";
		break;
		
		case "About_Fleetwood_16":
			DialogExit();
			AddQuestRecord("Holl_Gambit", "3-16");
			pchar.questTemp.HWIC.Self = "HuntKnippel";
			SetFunctionTimerCondition("HuntKnippelOver", 0, 0, 10, false);
			pchar.quest.Hunt_Knippel.win_condition.l1 = "location";
			pchar.quest.Hunt_Knippel.win_condition.l1.location = "Curacao";
			pchar.quest.Hunt_Knippel.function = "CreateKnippelShip";
			LocatorReloadEnterDisable("SentJons_town", "houseH1", true);//закрыть хижину Чарли
		break;
		
		case "About_Fleetwood_17":
			DialogExit();
			AddQuestRecord("Holl_Gambit", "3-15");
			pchar.questTemp.HWIC.Self = "end";
			pchar.questTemp.HWIC.Detector = "self_fail";
			CloseQuestHeader("Holl_Gambit");
		break;
		
		case "Abigile":
			dialog.text = "Really? Why are you so sure?";
			link.l1 = "Since Charlie is at the seabed feeding the fish. I boarded 'Zeekalf' and sent Knippel to hell. Of course, I had questioned him before that... He had a letter on him, which allowed me to pass as Knippel when I talked to Abigail, the sweetheart of our brave Richard.";
			link.l1.go = "Abigile_1";
		break;
		
		case "Abigile_1":
			dialog.text = "Hmm...That's smart. So, you're saying that...";
			link.l1 = "Yes. I've brought her to Antigua. She is on board of my ship. Now I have an ace of trumps in my game versus Fleetwood! He will do everything for her...";
			link.l1.go = "Abigile_2";
		break;
		
		case "Abigile_2":
			dialog.text = "Are you sure? It could be that everything is not as rosy as you imply...";
			link.l1 = "I am absolutely sure. From the letter I have figured out that Abigail's father was against her union with Richard because of money. So he decided to pay her father some kind of ransom - 200000 pesos! Tell me now, how many girls in the world are worth such money?";
			link.l1.go = "Abigile_3";
		break;
		
		case "Abigile_3":
			dialog.text = "Heh! I have not met such a girl in my life yet, that's for sure. " + pchar.name + ", you are a real evil genius. What is your further plan?";
			link.l1 = "I will bring the girl here and we will keep her in your room. I will tell her that Richard has gone to voyage and has not returned yet, so she will have to be our guest for a week. Remember, she is still thinking that I am Charlie Knippel.";
			link.l1.go = "Abigile_4";
		break;
		
		case "Abigile_4":
			dialog.text = "That's interesting. So you decided to keep the girl in my house? Hmm...";
			link.l1 = "John, she is a Dutch subject. That means that she is a nobody in St. John's and no one knows her. Rest assured, she will not dare to say a word. She doesn't have a penny. And anyway it will not last long. I will lure Fleetwood out with her help, and after that there will be no need in her anymore.";
			link.l1.go = "Abigile_5";
		break;
		
		case "Abigile_5":
			dialog.text = "I hope you are not going to do the same to her as to Knippel, aren't you?";
			link.l1 = "No, of course not. Though I am evil genius, but I am not at war with beautiful girls. And neither with ugly ones. If she behaves herself, I will bring her to her father in Willemstad after it's all over.";
			link.l1.go = "Abigile_6";
		break;
		
		case "Abigile_6":
			dialog.text = "Hm... So will I have to look after her?";
			link.l1 = "John, I don't insist. If you are totally against this, she will stay on board of my ship. But then I will have to put her into irons for safety and keep her in the hold, with the rats. I wouldn't like to treat her like that, you know.";
			link.l1.go = "Abigile_7";
		break;
		
		case "Abigile_7":
			dialog.text = "No, I understand. Sure, bring her here. It is my duty to help you in your fight against Fleetwood. Bring her here, then I will prepare the room.";
			link.l1 = "Thank you John. I knew I could count on you.";
			link.l1.go = "exit";
			pchar.questTemp.HWIC.Self = "AbigileInCabin";
			DoQuestCheckDelay("SetAbigileToCabin", 1.0); // fix 180812
			AddQuestRecord("Holl_Gambit", "3-24");
			//поставим табурет
			sld = ItemsFromID("lcheer");
			sld.shown = true;
			sld.startLocation = "SentJons_HouseF3";
			sld.startLocator = "goto2";
		break;
		
		case "Abigile_7_1":
			dialog.text = "Oh! My pleasure. I am happy to welcome such an important and... such a beautiful person. Miss, could you go up to the second floor please. There is supper waiting for you and the bed is made. I am sure you will want to have good night's sleep after such a long trip.";
			link.l1 = "Yes. Abigail is surely tired after such a long voyage from Willemstad.";
			link.l1.go = "Abigile_8";
		break;
		
		case "Abigile_8":
			DialogExit();
			sld = characterFromId("Abigile");
			sld.dialog.currentnode = "Abigile_kidnapping_11";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "Abigile_9":
			dialog.text = "Do you have a plan already?";
			link.l1 = "I do. We need to write a threatening letter to Richard with ransom demand for Abigail. Arrange a meeting somewhere on an uninhabited island - on Turks, for example. And if he doesn't comply, then, we, hmm, will send his sweetheart to him in pieces.";
			link.l1.go = "Abigile_10";
		break;
		
		case "Abigile_10":
			dialog.text = "What's the need for such complications with an uninhabited island?";
			link.l1 = "It is safer. I am not going to bring Abigail there and exchange her for the money, anyway. I need Fleetwood himself. He will certainly prepare an ambush on Antigua, but on Turks he will have no such advantage over me.";
			link.l1.go = "Abigile_11";
		break;
		
		case "Abigile_11":
			dialog.text = "Fair enough. Who will hand over the letter? It is very dangerous.";
			link.l1 = "A stranger. For example, any drunkard from the tavern. They are willing to do whatever you ask them for some money or free drink. If Richard kills him in a fit of rage, we will simply send another one. And we'll enclose one of Abi's fingers in the letter. That will make him much more compliant.";
			link.l1.go = "Abigile_12";
		break;
		
		case "Abigile_12":
			dialog.text = "" + pchar.name + "...";
			link.l1 = "Don't worry, John. I am sure it will not come to this. We just have to find a drunkard, and I will compose the letter right away. Do you have some paper and ink?";
			link.l1.go = "Abigile_13";
		break;
		
		case "Abigile_13":
			dialog.text = "Yes, I do. And I happen to know a suitable drunkard as well. I recommend Jack Harrison. He spends every evening in the tavern, tanking up with rum. You'll find him easily enough.";
			link.l1 = "Great! Give me a pen and ink, then, and I will compose a threatening message for Richard.";
			link.l1.go = "Abigile_14";
		break;
		
		case "Abigile_14":
			DialogExit();
			LAi_SetActorType(pchar);
			LAi_ActorGoToLocator(pchar, "goto", "goto2", "MC_writeLetter", -1);
		break;
		
		case "Abigile_15":
			dialog.text = "When are you going to hand him the letter? Are you really going to watch the delivery in progress?";
			link.l1 = "Sure. Richard is not a fool, but I doubt that he will take chances. At least, I hope so. I don't want to hurt the girl. Well, it is time to find the drunkard you mentioned. Jack... what was his full name?";
			link.l1.go = "Abigile_20";
		break;
		
		case "Abigile_20":
			dialog.text = "His name is Jack Harrison. He usually visits the tavern in the evening. Be careful!";
			link.l1 = "Everything will be fine. Wait for me.";
			link.l1.go = "Abigile_22";
		break;
		
		case "Abigile_22":
			DialogExit();
			LAi_SetOwnerType(npchar);
			pchar.questTemp.HWIC.Self = "LetterToDrunkardGo";
			AddDialogExitQuestFunction("CreateDrunckardInTavern");
			AddQuestRecord("Holl_Gambit", "3-25");
		break;
		
		case "Abigile_23":
			dialog.text = "Well, I would not say so. Fleetwood is cunning and dangerous. Besides he is a master swordsman and a seasoned sailor. He is not an easy prey by no means.";
			link.l1 = "I am not looking for silver bridges in my life... Well, John, it is time for me to leave. By the way, you mentioned that our brave warrior has a good ship, hasn't he?";
			link.l1.go = "Abigile_24";
		break;
		
		case "Abigile_24":
			dialog.text = "He has the best brig I have ever seen. And I have seen quite a few.";
			link.l1 = "That's good. I like good ships. Well, time to raise the anchor!";
			link.l1.go = "Abigile_26";
		break;
		
		case "Abigile_26":
			DialogExit();
			pchar.questTemp.HWIC.Self = "FleetwoodToIsland";
			pchar.quest.Fleetwood_meetingShore.win_condition.l1 = "location";
			pchar.quest.Fleetwood_meetingShore.win_condition.l1.location = "Shore56";
			pchar.quest.Fleetwood_meetingShore.function = "InTerksShore";
			AddQuestRecord("Holl_Gambit", "3-28");
		break;
		
		case "Abigile_27":
			int iVal = 0;
			for(i = 0; i < COMPANION_MAX; i++)
			{
				iTemp = GetCompanionIndex(PChar, i);
				if(iTemp > 0)
				{
				sld = GetCharacter(iTemp);
				if(sti(RealShips[sti(sld.ship.type)].basetype) == SHIP_VALCIRIA) iVal = 1;
				}
			}//установили признак наличия Валькирии в эскадре.
			if (iVal != 0)
			{
				dialog.text = "I am speechless! An excellent combination, a great idea and masterful implementation! My congratulations, " + pchar.name + "! And you've also managed to take his brig as a prize!";
				link.l1 = "Thank you! And where is Hercule? I would like to see him. When we last met, he told me I'd be able to find him with your help.";
				link.l1.go = "Abigile_28";
			}
			else
			{
				dialog.text = "An excellent combination, a great idea and masterful implementation! My congratulations, " + pchar.name + "!";
				link.l1 = "Thank you! And where is Hercule? I would like to see him. When we last met, he told me I'd be able to find him with your help.";
				link.l1.go = "Abigile_28";
			}
		break;
		
		case "Abigile_28":
			dialog.text = "I am expecting him any moment now. He should come here through the underpass. And you should explain yourself to the girl. She's started worrying about Richard's absence.";
			link.l1 = "Alright. But is it not the time to send her home?";
			link.l1.go = "Abigile_29";
		break;
		
		case "Abigile_29":
			dialog.text = "Wait... I need to talk to you. But first wait for Hercule's arrival, also go and comfort Abigail. Tell her a story, make something up. Then come to the underground. Alright?";
			link.l1 = "Alright, John.";
			link.l1.go = "Abigile_30";
		break;
		
		case "Abigile_30":
			DialogExit();
			npchar.greeting = "merdok_4";
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload2", "SentJons_TownCave", "item", "berglar1", "", -1);
			pchar.questTemp.HWIC.Self = "AbigileLie";
			sld = characterFromId("Abigile");
			LAi_SetCitizenType(sld);
			AddQuestRecord("Holl_Gambit", "3-34");
		break;
		
		case "Lucas":
			dialog.text = "Well, time has come to lay the cards down. As you have already figured out, I am not just a plain druggist. My real name is Johan van Merden and until recently I've been an agent on special missions for the Dutch West India Company and the right hand of its vice president Lucas Rodenburg.";
			link.l1 = "Really! It is interesting...";
			link.l1.go = "Lucas_1";
		break;
		
		case "Lucas_1":
			dialog.text = "It's different now. Lucas is willing to leave the game, to return back to Holland, so he needs to bury everything and everyone connected to his past\nI think that I still breath only because of my archive which contains all information about Lucas's crimes like the story of the 'ghost ship' which is just an ordinary pirate vessel under command of reckless and unprincipled scum named Jacob van Berg. Rodenburg had hired the man to plunder and sink English trade ships\nVan Berg is also responsible for sinking a flute with Abigail and her dad aboard. Abigail is an important figure in this game, Rodenburg also wanted her hand and heart, just like Fleetwood did, so I was quite surprised when you brought her here...";
			link.l1 = "That's the son-in-law that eccentric Abigail's dad had been talking about!";
			link.l1.go = "Lucas_2";
		break;
		
		case "Lucas_2":
			dialog.text = "Yes, that is why I want her to stay here for a bit. She might be my last ace in the game against Rodenburg, though I would prefer not to use her any further, she is a good girl, I don't want her to suffer. I think that Lucas would choose my archive instead of her, if the choice would be presented.\nSo, I propose you to be my ally in the game against Lucas... get rid of him, no matter how, the reward will be substantial.";
			link.l1 = "Hmm... I don't think it's going to be more difficult than with Fleetwood. ";
			link.l1.go = "Lucas_3";
		break;
		
		case "Lucas_3":
			dialog.text = "No, you're wrong. In the end, Fleetwood was a lone wolf, acting on his own. Rodenburg is a vice-director of the Company, he is a very influential man, only governor of Curacao has more power. Jacob van Berg is his agent, a very dangerous man. Lucas is always sitting his ass in Willemstad under protection of the Company's guardsmen and they are as good as Fleetwood's men.\nSo this is not going to be easy.";
			link.l1 = "The rules of the game are the same - to lure a tiger out of its den to an open place... I already have got a plan. What else can you tell me about Lucas?";
			link.l1.go = "Lucas_4";
		break;
		
		case "Lucas_4":
			dialog.text = "Well, I have told you almost everything. More than that, he has a personal swift ship called 'Meifeng'. Her captain is a Chinese guy named Longway - he is his confidant and executor of orders. He, too, is an enemy you would not like to face. There are no amateurs in Lucas' crew. ";
			link.l1 = "We already had a trump card right from the start - your archive. If he values it more than the girl he wanted to marry, then he will do anything to keep the information in the archive confidential... But... does the archive really exist, John? Aren't you bluffing?";
			link.l1.go = "Lucas_5";
		break;
		
		case "Lucas_5":
			dialog.text = "The archive does exist. And Lucas knows about that. Have you come up with anything yet?";
			link.l1 = "I have. John, if you really were the company's agent, you should know something.";
			link.l1.go = "Lucas_6";
		break;
		
		case "Lucas_6":
			dialog.text = "What exactly? Ask me.";
			link.l1 = "I need to intercept a ship of the company. Preferably, an unescorted ship - a courier or something like that. Can you tell me anything in this regard?";
			link.l1.go = "Lucas_7";
		break;
		
		case "Lucas_7":
			dialog.text = "Hm... I don't posses such information. Wait! I know for sure that one military vessel of the Company is doing a fast voyage between Philipsburg and Willemstad one time in a month. She delivers business papers. A brigantine named 'Hoop'.\nShe will leave Philipsburg today or tomorrow.";
			link.l1 = "Great! All I'll need to go to the shores of Saint Christopher. The naval route to Curacao lies right there.";
			link.l1.go = "Lucas_8";
		break;
		
		case "Lucas_8":
			dialog.text = "Good luck, " + pchar.name + ". I won't ask you about the details of your plan. I will be waiting for you return!";
			link.l1 = "Everything will be fine, John. Take care about the girl and treat her well!";
			link.l1.go = "Lucas_9";
		break;
		
		case "Lucas_9":
			DialogExit();
			RemoveItems(PChar, "MC_Letter", 1);
			GiveItem2Character(pchar, "MC_Letter");
			ChangeItemDescribe("MC_Letter", "itmdescr_MC_Letter2");
			AddQuestRecordInfo("LetterToLucas", "1");
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "SentJons_HouseF3", "goto", "goto1", "MC_TakeCloves", -1);
			pchar.questTemp.HWIC.Self = "LetterToLucas";
			sld = characterFromId("Tonzag");
			sld.dialog.currentnode = "Tonzag_hired";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
			AddQuestRecord("Holl_Gambit", "3-36");
			//установим таймер на генерацию энкаунтера
			pchar.quest.HWIC_Cureer.win_condition.l1 = "Timer";
			pchar.quest.HWIC_Cureer.win_condition.l1.date.hour  = sti(GetTime());
			pchar.quest.HWIC_Cureer.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.HWIC_Cureer.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.HWIC_Cureer.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.HWIC_Cureer.function = "CreateHWICCureerOnMap";
			SetFunctionTimerCondition("HWICCureerOnMapOver", 0, 0, 16, false);//таймер
		break;
		
		case "Lucas_10":
			dialog.text = "Incredible! I cannot believe my ears! How did that happen?";
			link.l1 = "I captured a courier and on behalf of Fleetwood sent a letter to Lucas, in which I stated that I'd taken possession of an archive, which belonged to some druggist from St. John's, and that soon the evidence of his every misdeed shall become known both to the Dutch and the English. I expected him to start hunting me, but it turned out the other way.";
			link.l1.go = "Lucas_11";
		break;
		
		case "Lucas_11":
			dialog.text = "";
			link.l1 = "Lucas accused Matthias Beck of betrayal and dealings with the English, put him behind bars and stepped into governor's boots. He most likely eliminated the captain of the brigantine. Then he told his faithful Chinese of the Meifeng to sink the ship with the Company's director Peter Stuyvesant aboard!";
			link.l1.go = "Lucas_12";
		break;
		
		case "Lucas_12":
			dialog.text = "Rodenburg is a resolute and cruel person. But even I did not think he could go to such ends...";
			link.l1 = "I captured the Meifeng and questioned Longway. He told me everything. I found Stuyvesant and warned him about Rodenburg's intentions and we together sailed to Willemstad. Stuyvesant set Beck free and arrested Lucas. He is in prison now.";
			link.l1.go = "Lucas_13";
		break;
		
		case "Lucas_13":
			dialog.text = "Heh! You are a real talent, my friend... You should make a career in the Navy or as a politician - you've got every chance to become governor once. And what did you do to Longway?";
			link.l1 = "I let him go. He gave way to me so I didn't do him any harm.";
			link.l1.go = "Lucas_14";
		break;
		
		case "Lucas_14":
			dialog.text = "That's good. Longway is a good fellow unlike his former boss. Well, " + pchar.name + ", you've done a great job! I will prepare your reward, but I will need some time... In the meantime...";
			link.l1 = "John, to tell the truth, there is a fly in the ointment. Longway and then Rodenburg both told me that Jacob van Berg is hunting me. How bad is that?";
			link.l1.go = "Lucas_15";
		break;
		
		case "Lucas_15":
			dialog.text = "Jacob van Berg? Pal, this is serious. He is merciless pirate, a skillful sailor and fighter. A professional hunter, so to speak. He was the one who was destroying ships by the orders of Rodenburg.\nHe will find you, so you must prepare. I also should take precaution.";
			link.l1 = "How can I find this van Berg?";
			link.l1.go = "Lucas_16";
		break;
		
		case "Lucas_16":
			dialog.text = "I don't know. Lucas and Longway were the only two who knew where to find him. So just be careful and ready\nI am shutting the place down. Go through the dungeons if you want to see me. And take the girl away, it is too dangerous for her to stay here.";
			link.l1 = "Don't worry John. Let him show up and I'll deal with him. Where is Abigail?";
			link.l1.go = "Lucas_17";
		break;
		
		case "Lucas_17":
			dialog.text = "She's gone to church. I am sorry for her. She's been totally upset recently.";
			link.l1 = "Well...That is hardly surprising. Well, it is time to bring her back to her father.";
			link.l1.go = "Lucas_18";
		break;
		
		case "Lucas_18":
			dialog.text = "She wanted to see you very much. I think Abi will ask you to return her back home.";
			link.l1 = "Abi, huh?";
			link.l1.go = "Lucas_19";
		break;
		
		case "Lucas_19":
			dialog.text = "Well , I have to admit that we've become friends. I don't regret that she has been living in my house, and thank God she will never know why she has been brought here.";
			link.l1 = "I see. Alright, John, I will go to church to meet Abigail. Then I am heading for Willemstad.";
			link.l1.go = "Lucas_20";
		break;
		
		case "Lucas_20":
			DialogExit();
			sld = characterFromId("Abigile");
			ChangeCharacterAddressGroup(sld, "SentJons_church", "goto", "goto1");//Аби - в церковь
			AddQuestRecord("Holl_Gambit", "3-56");
			pchar.questTemp.HWIC.Self = "AbiReturnHome";
			LocatorReloadEnterDisable("SentJons_town", "HouseF3", true);//закрыть аптеку
		break;
		
		case "Final":
			dialog.text = "Phew! You did it! Congratulations!";
			link.l1 = "Thank you. So now you can breathe freely, John.";
			link.l1.go = "Final_1";
		break;
		
		case "Final_1":
			dialog.text = "Yes. I think it is better to give up all these political games and intrigues. Now it's time to speak about your reward for the job.";
			link.l1 = "Well, I don't mind.";
			link.l1.go = "Final_2";
		break;
		
		case "Final_2":
			dialog.text = "I am going to leave the Caribbean forever. As a way of thanking you for your help, actually for being rescued from Rodenburg, I am granting you the right of ownership of this house and my drugstore. They are all yours now. Take the keys.";
			link.l1 = "That is great! I am quite happy. You've got a very comfortable house and a cozy cellar...";
			link.l1.go = "Final_3";
		break;
		
		case "Final_3":
			GiveItem2Character(pchar, "Drugstore_keys");//ключ
			dialog.text = "And also please accept this modest sum of 100 000 pesos and this musket. It faithfully served me once, and it will serve you well, too.";
			link.l1 = "I am not rejecting such gifts!";
			link.l1.go = "Final_4";
			LocatorReloadEnterDisable("SentJons_town", "HouseF3", false);//открыть аптеку
			LocatorReloadEnterDisable("SentJons_HouseF3", "reload3", false); // открыть комнату
			pchar.quest.Jino_Door.win_condition.l1 = "locator";
			pchar.quest.Jino_Door.win_condition.l1.location = "SentJons_HouseF3";
			pchar.quest.Jino_Door.win_condition.l1.locator_group = "reload";
			pchar.quest.Jino_Door.win_condition.l1.locator = "reload4";
			pchar.quest.Jino_Door.function = "OpenRoomDoor";//на локатор комнаты Джино
			Achievment_SetStat(pchar, 10, 1);
		break;
		
		case "Final_4":
			AddMoneyToCharacter(pchar, 100000);
			GiveItem2Character(pchar, "mushket2");
			dialog.text = "In the room upstairs you will find a young scientist. He is the best apothecary I know. It was him who made these mixtures, which helped you to recover in a couple of days. Take care of his allowance, his knowledge will compensate all your costs with interest.";
			link.l1 = "Fine. I will take care of him.";
			link.l1.go = "Final_5";
		break;
		
		case "Final_5":
			dialog.text = "I have to say goodbye now. I am going to the cellar to pack up my belongings. Tomorrow I won't be here - I am sailing away from Antigua. I am happy that I've met you and I am happy that you were on my side in this game and not with my enemies.";
			link.l1 = "I am also happy to meet you, John. Perhaps, we'll meet again...";
			link.l1.go = "Final_6";
		break;
		
		case "Final_6":
			dialog.text = "I don't think so, my friend. Well, I am going to pack up. Goodbye, " + pchar.name + "!";
			link.l1 = "Goodbye, John! Good luck to you!";
			link.l1.go = "Final_7";
		break;
		
		case "Final_7":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload2", "none", "", "", "", -1);
			npchar.lifeday = 0;
			pchar.questTemp.HWIC.Self = "final";
			AddQuestRecord("Holl_Gambit", "3-64");
			CloseQuestHeader("Holl_Gambit");
			pchar.questTemp.HWIC.Detector = "self_win";
		break;
		
		// Страж Истины
		case "guardoftruth":
			dialog.text = "Ah, mister, don't listen to these foolish talks. There is nobody there. There is my laboratory, mixtures are being prepared, you know...";
			link.l1 = "All kidding aside, John. Does the name of Gino Gvineili ring a bell?";
			link.l1.go = "guardoftruth_1";
		break;
		
		case "guardoftruth_1":
			dialog.text = "Hmm...";
			link.l1 = "Aha! I can see it in your eyes - I am right... That's where he lives and whom he prepares his herbs for!";
			link.l1.go = "guardoftruth_2";
		break;
		
		case "guardoftruth_2":
			dialog.text = "Sir, I am telling you once again - there's nobody here.";
			link.l1 = "Let's put the excuses aside, John. I will not hurt your alchemist - but if padre Vincento of Santiago finds him, I can not be sure. The Inquisitor is already going to send his sleuthhounds to Antigua...";
			link.l1.go = "guardoftruth_3";
		break;
		
		case "guardoftruth_3":
			dialog.text = "What do you want from him?";
			link.l1 = "Just to talk. He has quite important information for me. I promise that I will not turn him into the Inquisition and will not hurt him in any way.";
			link.l1.go = "guardoftruth_4";
		break;
		
		case "guardoftruth_4":
			dialog.text = "Gino is a nice fellow. Don't believe anything padre Vincento had told you about him. And remember - I will stand up for my alchemist.";
			link.l1 = "I gave you my word. Isn't that enough for you?";
			link.l1.go = "guardoftruth_5";
		break;
		
		case "guardoftruth_5":
			dialog.text = "Go upstairs, then. The door is open. And hope that you will stay true to your word.";
			link.l1 = "Rest assured, I will.";
			link.l1.go = "guardoftruth_6";
		break;
		
		case "guardoftruth_6":
			DialogExit();
			pchar.questTemp.Guardoftruth = "jino1";
			AddQuestRecord("Guardoftruth", "36");
			LocatorReloadEnterDisable(pchar.location, "reload4", false);
		break;
		
		// алхимический набор
		case "alchemy":
			dialog.text = "Captain, wouldn't you like to become familiar with hermetic arts? This could come quite useful for you.";
			link.l1 = "I am sorry, but my occupation is somewhat different. I am used to holding a sword hilt in my hand - not flasks or test tubes.";
			link.l1.go = "alchemy_exit";
			link.l2 = "Hm. As my brother once said, do not shrink learning to do something with your own hands. Of course I would love to. What is needed for that?";
			link.l2.go = "alchemy_1";
			npchar.quest.alchemy = true;
		break;
		
		case "alchemy_exit":
			dialog.text = "As you wish. I just offered...";
			link.l1 = "...";
			link.l1.go = "exit";
		break;
		
		case "alchemy_1":
			dialog.text = "You should learn to mix herbs with your own hands. But you will not succeed without an alchemist's kit. Take a look at this handbag. There is everything a beginning alchemist needs - test tubes, flasks, a still, spatulas, glass tubes, a burner and a lot of similar stuff...";
			link.l1 = "It is very interesting! And what can I prepare with it?";
			link.l1.go = "alchemy_2";
		break;
		
		case "alchemy_2":
			dialog.text = "Well, you won't be able to turn lead into gold with it, but you will be able to mix ingredients according to various recipes and thus obtain potions and other useful things.";
			link.l1 = "Recipes?";
			link.l1.go = "alchemy_3";
		break;
		
		case "alchemy_3":
			dialog.text = "True. You must know a recipe in order to make a potion or an item. Recipes can be bought from merchants or be found anywhere. Once you have studied a recipe, you should collect every ingredient needed and do exactly what is written there\n Use your alchemy tools, find or buy mortar and pestle, look for a crucible, alas, I don't posses an extra one to give you. Herbs, spirits, potions, minerals, garbage - everything will do, providing you have right recipe and tools.";
			link.l1 = "Very interesting. And how much do you want for this kit?";
			link.l1.go = "alchemy_4";
		break;
		
		case "alchemy_4":
			dialog.text = "Twenty thousand pesos. This is a very good kit and it will cover its cost very quickly.";
			link.l1 = "You're laughing at me, aren't you? A handbag with glassware at the price of a lugger? No, I'll pass.";
			link.l1.go = "alchemy_exit";
			if (sti(pchar.money) >= 20000)
			{
				link.l2 = "I agree. I think it will be interesting to try to make something with my own hands.";
				link.l2.go = "alchemy_5";
			}
		break;
		
		case "alchemy_5":
			AddMoneyToCharacter(pchar, -20000);
			Log_Info("You've got the alchemist's kit.");
			GiveItem2Character(pchar, "alchemy_tool");
			PlaySound("interface\important_item.wav");
			dialog.text = "You won't regret this purchase, I am absolutely sure. Definitely, it is more profitable to make potions by yourself as you need them, rather than visiting herbalists' stalls to buy everything you need by a piece. Besides, it will not always be possible to buy everything you need. ";
			link.l1 = "Let's learn. I think I can do it!";
			link.l1.go = "alchemy_6";
		break;
		
		case "alchemy_6":
			DialogExit();
			PlaySound("interface\notebook.wav");
			Log_Info("In order to make your own herbs and amulets you must have the Alchemy skill!");
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		//--> блок реагирования на попытку залезть в сундук
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("You are a "+ GetSexPhrase("thief, mister! Guards, take him","thief, girl! Guards, take her") +"!!!", "Just look at that! As soon as I was lost in contemplation, you decided to check my chest! Take the thief!!!", "Guards! Robbery! Take the thief!!!");
			link.l1 = "Damn it!";
			link.l1.go = "exit";
			LAi_group_Attack(NPChar, Pchar);
		break;
		//<-- блок реагирования на попытку залезть в сундук
	}
}
