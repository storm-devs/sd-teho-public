// Жоаким Мерриман - португальский сумрачный гений
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (CheckAttribute(pchar, "questTemp.HWIC.Holl"))
			{
				if (pchar.questTemp.HWIC.Holl == "AbbySeekIsland" && !CheckAttribute(npchar, "quest.HWICHoll.Task"))
				{
					dialog.text = "Good day! My name is Joachim Merriman. And you are captain " + GetFullName(pchar) + "?";
					link.l1 = "Yes, it is me. And how do you know my name? I don't remember meeting you before.";
					link.l1.go = "JoakimSeekSkull";
					break;
				}
				if (CheckCharacterItem(pchar, "SkullAztec"))
				{
					dialog.text = "I am glad to see you, captain. Your shining eyes tell me that you are about to make me happy. Do you have the Yum Cimil's skull?";
					link.l1 = "Yes, senor Merriman. I have the artifact you need. I think that this is it, it smells with antiquity and some hidden force.";
					link.l1.go = "JoakimFindSkull";
					break;
				}
				dialog.text = "Do you have anything else to say, captain?";
				link.l1 = "No, senor Merriman. I am leaving..";
				link.l1.go = "exit";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.HWIC.Self"))
			{
				if (pchar.questTemp.HWIC.Self == "JoakimMeeting" && !CheckAttribute(npchar, "quest.HWICHoll.Task"))
				{
					dialog.text = "Good day! My name is Joachim Merriman. And you are captain " + GetFullName(pchar) + "?";
					link.l1 = "Yes, it is me. And how do you know my name? I don't remember meeting you before.";
					link.l1.go = "JoakimSeekSkull";
					break;
				}
				if (CheckCharacterItem(pchar, "SkullAztec"))
				{
					dialog.text = "I am glad to see you, captain. Your shining eyes tell me that you are ready to make me happy. Do you have the Yum Cimil's skull?";
					link.l1 = "Yes, senor Merriman. I have the artifact you need. I think that this is it, it smells with antiquity and some hidden force.";
					link.l1.go = "JoakimFindSkull";
					break;
				}
				dialog.text = "Do you have anything else to say, captain?";
				link.l1 = "No, senor Merryman. I am leaving.";
				link.l1.go = "exit";
				break;
			}
			dialog.text = "Good day. Do you want anything from me?";
			link.l1 = "No. I am sorry but I am leaving already.";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;

		case "Landlady"://хозяйка дома
			dialog.text = "If you've come to see senor Joachim, then I have to tell you that he is not here. He doesn't live here anymore.";
			link.l1 = "I see.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Landlady";
		break;
		
		case "Landlady_1"://хозяйка дома
			dialog.text = "If you've come to see senor Joachim, then I have to tell you that he is not here. He is away and he didn't tell me when he will return.";
			link.l1 = "I see.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Landlady_1";
		break;
		
		case "Landlady_2"://хозяйка дома
			dialog.text = "If you've come to see senor Joachim, then I have to tell you that he is not here. He doesn't live here anymore.";
			link.l1 = "I see.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Landlady_2";
		break;
		
		case "JoakimSeekSkull":
			PlaySound("VOICE\Russian\hambit\Joakim Merriman-01.wav");
			dialog.text = "I have made inquiries about you, captain. See, I am a scientist and I work with Indian culture and ethnicity so I'd like to offer you an incredibly profitable business. Would you be so kind to walk with me to my house and discuss details of my proposal in a more private area?";
			link.l1 = "I never reject profitable business proposals. Let's go and have a talk.";
			link.l1.go = "JoakimSeekSkull_1";
		break;
		
		case "JoakimSeekSkull_1":
			dialog.text = "Thank you. My house is not far from here. Follow me!";
			link.l1 = "...";
			link.l1.go = "JoakimSeekSkull_2";
		break;
		
		case "JoakimSeekSkull_2":
			DialogExit();
			LAi_ActorGoToLocation(npchar, "reload", "houseSp1", "Villemstad_houseSp1_room", "goto", "goto1", "JoakimInRoom", -1);
		break;
		
		case "JoakimSeekSkull_3":
			PlaySound("VOICE\Russian\hambit\Joakim Merriman-01.wav");
			dialog.text = "Well, we can talk here. You have been recently visiting my neighbour Solomon Shneur. I was just walking by and, don't blame me for that, captain, became an unintentional witness of your talk with Solomon. It has really interested me, so I had the impudence to listen to it all.";
			link.l1 = "Go on.";
			link.l1.go = "JoakimSeekSkull_4";
		break;
		
		case "JoakimSeekSkull_4":
			dialog.text = "Solomon is my neighbour and he often visits me. I know about his misadventures... Well, everybody knows about them! He has already told about them to the whole Willemstad. But straight to the business. The old man must have told you already about some jade skull which is stashed along with his money on some unknown island. Did he tell you about it?";
			link.l1 = "Yes, he did. I didn't really get the part about the skull and a granddad... I had the impression that Abigail's dad is a bit out.";
			link.l1.go = "JoakimSeekSkull_5";
		break;
		
		case "JoakimSeekSkull_5":
			dialog.text = "No, captain, Solomon is fine, he is just odd. The skull does exist. This is an ancient artefact, I have no idea how the old Jew got it. The jade skull of Yum Cimil! I have been looking for it for a lot of years\nSearch for the island, where Solomon stashed his family money. The skull must be there. Deliver this item to me and I will pay you half a million pesos.";
			link.l1 = "Half of million?! Are you kidding me? I have never seen items which could cost so much in my life!";
			link.l1.go = "JoakimSeekSkull_6";
		break;
		
		case "JoakimSeekSkull_6":
			dialog.text = "You haven't seen much in your life yet, captain... So what? Are you in? You give me the skull and I will give you five hundred thousand in return. Deal?";
			link.l1 = "Heh, what question can there be! Sure, deal!";
			link.l1.go = "JoakimSeekSkull_7";
		break;
		
		case "JoakimSeekSkull_7":
			dialog.text = "Splendid, captain. It is always a pleasure to work with a man who understands his obvious profit. You will find me in my house. Good luck!";
			link.l1 = "Thank you, senor Merriman. I won't make you wait for too long.";
			link.l1.go = "exit";
			npchar.quest.HWICHoll.Task = "true";
			LAi_SetOwnerType(npchar);
			AddDialogExitQuestFunction("CheckIslandCoordinates");//вот тут-то мы и проверим, есть ли у нас координаты острова, и далее будем исходить из результата.
		break;
		
		case "JoakimFindSkull":
			PlaySound("VOICE\Russian\hambit\Joakim Merriman-02.wav");
			dialog.text = "Oh, yes! You are definitely right about the hidden force... But enough of words, let me see it, I am shaking with impatience.";
			link.l1 = "Here, please, take it. I hope that I wasn't mistaken?";
			link.l1.go = "JoakimFindSkull_1";
		break;
		
		case "JoakimFindSkull_1":
			RemoveItems(PChar, "SkullAztec", 1);
			dialog.text = "Ah, incredible! Yes, this is it. Excellent, captain, most excellent! I have it with me, at last! I have been waiting for this moment for so many years!";
			link.l1 = "What about the money you promised, senor Merriman?";
			link.l1.go = "JoakimFindSkull_2";
		break;
		
		case "JoakimFindSkull_2":
			AddMoneyToCharacter(pchar, 500000);
			dialog.text = "Oh, yes, sure! Half a million pesos. Take them, you have earned them for sure.";
			link.l1 = "Thanks... Though I couldn't imagine how can this little item cost so much.";
			link.l1.go = "JoakimFindSkull_3";
		break;
		
		case "JoakimFindSkull_3":
			dialog.text = "Little item? This is... whatever, I doubt that you will be interested to hear the story of this item. Truth to be told, I don't have time to spare anyway\nThank you, captain, for what you have done. Now it's time to say farewells. I should go.";
			link.l1 = "Farewell, senor Merriman. Perhaps, we will meet again...";
			link.l1.go = "JoakimFindSkull_4";
		break;
		
		case "JoakimFindSkull_4":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", -1);
			sld = characterFromId("Landlady");
			sld.Dialog.Filename = "Quest\HollandGambit\Joakim.c";
			sld.dialog.currentnode = "Landlady_2";
			SetFunctionTimerCondition("Caleuche_StartTotal", 0, 0, 180, false); // таймер на Калеуче
		break;
		
		case "JoakimSeekSkull_8":
			PlaySound("VOICE\Russian\hambit\Joakim Merriman-01.wav");
			dialog.text = "Well, we can talk here, captain, I know that you are a close friend of Abigail Shneur, a daughter of my neighbour Solomon. She has sailed away on your ship to her lover... but it doesn't matter really.";
			link.l1 = "Hm. And what are you getting at, senor... Merriman?";
			link.l1.go = "JoakimSeekSkull_9";
		break;
		
		case "JoakimSeekSkull_9":
			dialog.text = "If you know Solomon then you must know his story of the shipwreck and his lost treasures which he has stashed on some unknown island. He has already told this story to everyone in Willemstad.";
			link.l1 = "Well, let's suppose that I have heard something about that. And how can this story awake my interest? I don't care about the old Jew's misfortunes.";
			link.l1.go = "JoakimSeekSkull_10";
		break;
		
		case "JoakimSeekSkull_10":
			dialog.text = "Don't you like Solomon? I assure you that he is just a harmless odd man. Forget about him. Let's talk business\nI had a talk with Solomon several times. You can not even imagine how I felt when I found out that this old Jew is an owner of an ancient artifact I've been looking for years! The crazy old man stashed it along with his pathetic money on some island and he cannot recall its location\nI need this artifact. Bring it to me and I will pay you half a million pesos.";
			link.l1 = "Half of million?! Are you kidding me? I have never seen items which could cost so much in my life!";
			link.l1.go = "JoakimSeekSkull_11";
		break;
		
		case "JoakimSeekSkull_11":
			dialog.text = "You haven't seen much in your life yet, captain... So what? Are you in? You give me the skull and I will give you five hundred thousands in return. Besides, you can take Solomon's money. According to the old man's words there must be about two hundred thousands pesos... So it is seven hundred thousands for you to earn. Deal, captain?";
			link.l1 = "Heh, what question can there be! Sure, deal! But how am I supposed to find this island?";
			link.l1.go = "JoakimSeekSkull_12";
		break;
		
		case "JoakimSeekSkull_12":
			dialog.text = "Talk with Abigail. Perhaps she remembers something. Ask Solomon. See, if I'd knew where to find the island I wouldn't ask for you help.";
			link.l1 = "I see. Sorry for my stupid question. Sure, it is my problem how to find the island... The job is up for me and the payment is up for you.";
			link.l1.go = "JoakimSeekSkull_13";
		break;
		
		case "JoakimSeekSkull_13":
			dialog.text = "Exactly. I am glad that we understand each other, captain. Good luck with your searches. You can always find me here, in my house.";
			link.l1 = "I won't make you wait for too long, senor Merriman. Goodbye!";
			link.l1.go = "JoakimSeekSkull_14";
		break;
		
		case "JoakimSeekSkull_14":
			DialogExit();
			pchar.questTemp.HWIC.Self = "SeekAbiIsland";
			AddQuestRecord("Holl_Gambit", "3-55");
			LocatorReloadEnterDisable("SentJons_HouseF3", "reload3", true);//закроем комнату Аби
			npchar.quest.HWICHoll.Task = "true";
			LAi_SetOwnerType(npchar);
			NextDiag.CurrentNode = "First time";
		break;
		
		// калеуче
		case "caleuche":
			PlaySound("VOICE\Russian\LSC\Chymiset-03.wav");
			dialog.text = "The sacrificial stones are red with the blood of my enemies! Yum Cimil granted me his power over the dead! With this power in my hands I will soon rule the living!";
			link.l1 = "Great speech. And what the fuck are you gonna do, Merriman? Why do you need the army of dead? Are you gonna fight against all the world, or are you just insane bastard?";
			link.l1.go = "caleuche_1";
			CreateLocationParticles("large_smoke", "goto", "goto37", 0.5, 0, 0, "");
		break;
		
		case "caleuche_1":
			dialog.text = "Silence, you fool! My intentions will remain secret for you! My armies of darkness will occupy all dark caves and dungeons of the archipelago. My outposts will be located in every village, waiting for my signal. And when the time comes, my legions will march towards the final battle!\nPity that you won't live to see it, pitiful human, a hero wannabe! You have entered my sanctuary - and you will not get out of it alive!";
			link.l1 = "We'll see!";
			link.l1.go = "caleuche_2";
		break;
		
		case "caleuche_2":
			PlaySound("Types\warrior04.wav");
			dialog.text = "Ha-ha-ha! You would dare to challenge me and my servants?! Then behold, what I really am, and tremble with fear, you worm!";
			link.l1 = "...";
			link.l1.go = "caleuche_3";
		break;
		
		case "caleuche_3":
			npchar.model = "Meriman_2";
			Characters_RefreshModel(npchar);
			PlaySound("Ambient\Teno_inside\teleporter.wav");
			dialog.text = "";
			link.l1 = "Ahhh! Holy crap!";
			link.l1.go = "caleuche_4";
		break;
		
		case "caleuche_4":
			PlaySound("VOICE\Russian\hambit\Joakim Merriman-04.wav");
			dialog.text = "Now you understand who is standing in front of you, slime?! Yum Cimil himself favours me! I will rip your liver out and I will eat it!";
			link.l1 = "Thousand sharks! Alright, you damned witcher! I'll sever that green skull of yours from your body!";
			link.l1.go = "caleuche_5";
		break;
		
		case "caleuche_5":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "goto", "goto37", "none", "", "", "Caleuche_MerrimanTeleport", -1);
			LAi_SetActorType(pchar);
			LAi_ActorTurnToLocator(pchar, "goto", "goto37");
			pchar.questTemp.Caleuche.Merriman_hide = "true";
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
