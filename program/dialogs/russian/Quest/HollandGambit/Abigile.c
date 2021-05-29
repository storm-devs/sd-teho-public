// Абигайль Шнеур
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
				if (pchar.questTemp.HWIC.Holl == "AbbyInHouse")
				{
					dialog.text = "Good day, mynheer. I am glad to see you. What brings you to our home?";
					link.l1 = "Good day, Abigail. My name is " + GetFullName(pchar) + ". I am a captain and I serve for the good of the Dutch Republic and for the Dutch West Indian Company.";
					link.l1.go = "AbbyAndLucas";
					break;
				}
				if (pchar.questTemp.HWIC.Holl == "AbbyFindScull" && makeint(Pchar.money) >= 200000)
				{
					dialog.text = "Have you found my father's money? Is it true? Ah, I am so glad... Quickly go to my papa, he wants to talk with you. Go and see him!";
					link.l1 = "I am on my way, mistress.";
					link.l1.go = "exit";
					break;
				}
				if (pchar.questTemp.HWIC.Holl == "AbbyLeavesMarried")
				{
					dialog.text = "You have saved us from misery, captain! I am so grateful to you! Now the good name of the Shneurs is restored.";
					link.l1 = "It is my job, Abigail. I hope that there is nothing left to hold you from marrying my patron.";
					link.l1.go = "AbbyAndLucas_8";
					break;
				}
				dialog.text = "Wanted to tell me something, captain?";
				link.l1 = "No, mistress. I am leaving already.";
				link.l1.go = "exit";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.HWIC.Eng"))
			{
				if (pchar.questTemp.HWIC.Eng == "AbigileInChurch")
				{
					dialog.text = "I am glad to see you, mynheer. What brings you to the poor girl?";
					link.l1 = "Good day, Abigail. I am from Richard Fleetwood...";
					link.l1.go = "Seek_Island";
					break;
				}
				dialog.text = "Wanted to tell me something, captain?";
				link.l1 = "No, mistress. I am leaving already.";
				link.l1.go = "exit";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.HWIC.Self"))
			{
				if (pchar.questTemp.HWIC.Self == "toVillemstad")
				{
					dialog.text = "What is going on here? What is the noise? Papa, who is this?";
					link.l1 = "Good day, mistress. I take it that you are Abigail? I am really glad to see you! Forgive me my impudence, but I have to give you a letter from... but your father doesn't trust me and asks me to leave the house. I assure you that I really have a message for you.";
					link.l1.go = "Abigile_kidnapping";
					break;
				}
				if (pchar.questTemp.HWIC.Self == "AbigileNextDay")
				{
					dialog.text = "Ah, here you are, Charlie. I am ready to follow you.";
					link.l1 = "Let's go!";
					link.l1.go = "Abigile_kidnapping_7";
					break;
				}
				if (pchar.questTemp.HWIC.Self == "AbigileInCabin")
				{
					dialog.text = "Aren't we in St. John's already, Charlie? Will I see Richard soon?";
					link.l1 = "Yes, miss, we are in St. John's. But unfortunately Richard is not in the town at the moment, he was ordered to patrol Barbados's shores two days ago. But don't be sad, he should return in a week.";
					link.l1.go = "Abigile_kidnapping_8";
					break;
				}
				if (pchar.questTemp.HWIC.Self == "AbigileLie")
				{
					dialog.text = "Charlie! I am so glad to see you! Tell me, are there any news from Richard?";
					link.l1 = "Alas, my dear miss. Richard had to stay in Bridgetown for a while for a secret and important business, it is something about reconnaissance against Holland. I take it that Richard has told you about his job?";
					link.l1.go = "Abigile_kidnapping_13";
					break;
				}
				if (pchar.questTemp.HWIC.Self == "AbiReturnHome")
				{
					dialog.text = "Charlie! It is you! You are finally back!";
					link.l1 = "Greetings, dear miss. I am glad to see you.";
					link.l1.go = "Abigile_return";
					break;
				}
				if (pchar.questTemp.HWIC.Self == "AbiReturnHomeGo")
				{
					dialog.text = "Ah, I am home finally! I am so glad to see papa! Charlie, thank you for everything you have done for me!";
					link.l1 = "Please, there is no need for such expressions, dear miss...";
					link.l1.go = "Abigile_return_6";
					break;
				}
				if (pchar.questTemp.HWIC.Self == "SolomonHistoryNext")
				{
					dialog.text = "Papa, if you remember something, please say it! Charlie, he is... he can be trusted. Perhaps, he is the only one who can help us!";
					link.l1 = "";
					link.l1.go = "Abigile_return_12";
					pchar.questTemp.HWIC.Self = "SolomonHistoryAfter";
					break;
				}
				if (pchar.questTemp.HWIC.Self == "SolomonHistoryEnd")
				{
					dialog.text = "I will pray for you, Charlie! Tell me... tell me that you will do it! That you will find the island!";
					link.l1 = "I will do what I can, dear miss.";
					link.l1.go = "Abigile_return_13";
					break;
				}
				if (pchar.questTemp.HWIC.Self == "final" || pchar.questTemp.HWIC.Self == "VanbergDestroyed")
				{
					dialog.text = "Ah, Charlie! You are back! What will you say? Have you found the island?";
					if (makeint(Pchar.money) >= 200000)
					{
						link.l1 = "Yes, Abi. I have found the island and your father's money. I am here to return it to you.";
						link.l1.go = "Abigile_GiveMoney";
					}
					link.l2 = "Alas, miss. I have failed to find neither captain Keller nor the island. I did what I could.";
					link.l2.go = "Abigile_NoMoney";
				break;
				}
				dialog.text = "Ah, it is you , Charlie! Want to ask me something?";
				link.l1 = "No, it is nothing. I am leaving already.";
				link.l1.go = "exit";
				break;
			}
			dialog.text = "Good day. Want something?";
			link.l1 = "No, mistress. I beg your pardon. Farewell.";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

//-------------------------------------------------за Голландию-----------------------------------------------
		case "AbbyAndLucas":
			dialog.text = "Glad to meet you, captain " + GetFullName(pchar) + ". I've heard about you. It was you who has captured the pirate ghost-ship and brought it to Willemstad. Tell me, captain, is it true that this ship was under the command of... Richard Fleetwood?";
			link.l1 = "Precisely, mistress. We were really shocked. Just think about it, English royal officer who had been plundering merchants of his own nation... And that bastard was covering himself by the action of the ghost-ship. He used it to blame the Company and to attack the Holland ships as well!";
			link.l1.go = "AbbyAndLucas_1";
		break;
		
		case "AbbyAndLucas_1":
			dialog.text = "It is hard to hear such things, captain... I knew Richard Fleetwood personally and I'd have never thought that he...";
			link.l1 = "Mistress, I am informed by my patron Lucas Rodenburg about your voyage to Curacao from Recife. Now it is clear. Fleetwood had sunk your ship and then returned and 'saved' you and your father from the island. I read the pirate's journal, he wasn't afraid to trust this information to paper...";
			link.l1.go = "AbbyAndLucas_2";
		break;
		
		case "AbbyAndLucas_2":
			dialog.text = "Such a nightmare... It seems that my papa was right. He has been telling me that Richard was that pirate. It is good that it all got clear now and nothing fatal has happened... ah, I am sorry, captain. So what does such an important man like you want from a common girl?";
			link.l1 = "Abigail, I am here because of a very complicated and delicate matter. I ask you to listen to me.";
			link.l1.go = "AbbyAndLucas_3";
		break;
		
		case "AbbyAndLucas_3":
			dialog.text = "Of course, mynheer. I am all ears.";
			link.l1 = "As I have said, I serve to the Company and Lucas Rodenburg is not only my military commander, but a good friend too. And it would be the greatest happiness for him to get your consent to his proposal of marriage. I am here to ask you to marry my patron. He is ready to do everything for you.";
			link.l1.go = "AbbyAndLucas_4";
		break;
		
		case "AbbyAndLucas_4":
			dialog.text = "Ah, captain! I see now why mynheer Rodenburg wasn't ready to do that himself... My poor papa would be really glad for sure but...";
			link.l1 = "Mistress, I see, that something is bothering you. What matter has made you to doubt in my commander's sincerity? Perhaps, I am able to make you change your mind?";
			link.l1.go = "AbbyAndLucas_5";
		break;
		
		case "AbbyAndLucas_5":
			dialog.text = "Captain, I have no doubts in mynheer Rodenburg's sincerity. Lucas has done so much for me and my daddy, I don't know what would happen to us if it wasn't his patronage. But, please, understand my position!\nWe had never been poor, the Shneur family was always known for our fortune... this unfortunate thing with that pirate. I can not listen to these dirty talks behind my back, not any longer. All citizens believe that I am only interested in mynheer Rodenburg's money. Ah, I wish my dad remembered exact location of the island! He stashed all family's money there to save it from hands of pirates who murdered my sisters and my brother!\nBut my poor father is not a sailor, he simply doesn't know where this piece of land lies. Talk to my dad, captain! Maybe he will recall anything. I wish you find the island and our money!";
			link.l1 = "Fine, Abigail. I will speak with your father. Perhaps it is not over yet. I will do what I can.";
			link.l1.go = "AbbyAndLucas_6";
		break;
		
		case "AbbyAndLucas_6":
			dialog.text = "Thanks, mynheer. I will pray for you. May God speed you!";
			link.l1 = "Farewell, Abigail. Wait me with good news.";
			link.l1.go = "AbbyAndLucas_7";
		break;
		
		case "AbbyAndLucas_7":
			DialogExit();
			AddQuestRecord("Holl_Gambit", "1-27");
			pchar.questTemp.HWIC.Holl = "AbbyFather";
		break;
		
		case "AbbyAndLucas_8":
			dialog.text = "Oh, yes! Mynheer Rodenburg is the most honorable man. I give him my consent unhesitatingly and I will be happy to call him my husband.";
			link.l1 = "Then I consider my mission is complete. I have to go now to my commander and tell him the news. And, mistress, I sincerely wish you happiness!";
			link.l1.go = "AbbyAndLucas_9";
		break;
		
		case "AbbyAndLucas_9":
			DialogExit();
			AddQuestRecord("Holl_Gambit", "1-33");
			pchar.questTemp.HWIC.Holl = "AbbyAgreeMarried";//теперь к Лукасу
		break;
		
//-------------------------------------------------за Англию-----------------------------------------
		case "Seek_Island":
			dialog.text = "From Richard?! Ah, mynheer! I've heard that he was wounded. Is it true, tell me?! Is he alright?";
			link.l1 = "Richard is alive and mostly healthy. There are a few problems left with his sight, but he is doing well. Richard asks you to sail with him to England where you can marry. His mission is over and he is only waiting for your answer.";
			link.l1.go = "Seek_Island_1";
		break;
		
		case "Seek_Island_1":
			dialog.text = "Ah, my dear messenger, tell Richard that for our happiness I am ready to go with him wherever he wants. But I fear that my runaway will kill my poor father. I am desperate and I don't know what to do. I wish Richard could find that ill-fated island and the chest with our family gold... Perhaps it would somehow comfort my papa.";
			link.l1 = "I see... My mission was to deliver you to Antigua. So I should find the island and the chest, I will bring it to you and then you will go with me to St. John's to Richard.";
			link.l1.go = "Seek_Island_2";
		break;
		
		case "Seek_Island_2":
			dialog.text = "Ah, you are so generous! Thank you very much, captain! I will pray for you! Go and may God help you!";
			link.l1 = "I won't make you wait me for too long, mistress. See you soon!";
			link.l1.go = "Seek_Island_3";
		break;
		
		case "Seek_Island_3":
			DialogExit();
			AddQuestRecord("Holl_Gambit", "2-18");
			pchar.questTemp.HWIC.Eng = "SeekIsland";
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "Villemstad_houseSp2_bedroom", "goto", "goto1", "", -1);//Аби домой
			pchar.questTemp.HWIC_Coordinates = "true"; //атрибут координат на поиск острова через каюту
		break;
		
//--------------------------------------------против всех------------------------------------------------
		case "Abigile_kidnapping":
			dialog.text = "Oh... You have a letter from him... yes? Ah, papa, don't be that unbearable! You are always hunted by fears! Mynheer, please, follow me, I want to talk with you.";
			link.l1 = "Thank you, mistress.";
			link.l1.go = "Abigile_kidnapping_1";
		break;
		
		case "Abigile_kidnapping_1":
			DialogExit();
			npchar.greeting = "abigile_3";
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload2", "Villemstad_houseSp2_bedroom", "goto", "goto1", "Abigile_Stay", -1);
			NextDiag.CurrentNode = "Abigile_kidnapping_2";
			pchar.questTemp.HWIC.Self = "AbigileTalk";
		break;
		
		case "Abigile_kidnapping_2":
			dialog.text = "Forgive my father, mynheer. He is good and kind man just... our misfortunes have broken him.";
			link.l1 = "It is alright, mistress. Let me introduce myself, I am Charlie... the Knippel. I am here by the orders of Richard Fleetwood, he wants me to bring you to him. Here, please, read the letter.";
			link.l1.go = "Abigile_kidnapping_3";
		break;
		
		case "Abigile_kidnapping_3":
			RemoveItems(PChar, "NPC_Letter", 1);
			dialog.text = "Ah, Richard...(reading). Oh, God! He has decided... to grant to my father all of his lost money! Such generosity! Dear Richard! Mynheer, you are such a good herald! Richard, where is he? Is he on Curacao?";
			link.l1 = "No, mistress. There was an attempt on his life, he got a serious injury. He is on Antigua now... you haven't finished the letter.";
			link.l1.go = "Abigile_kidnapping_4";
		break;
		
		case "Abigile_kidnapping_4":
			dialog.text = "Oh, holy Lady! Tell me, is he safe? Is his wound bad?";
			link.l1 = "Don't worry like that, mistress! Richard is not a man who would let some bastards to kill him just like that. He is restoring now. And my mission is to take you to him. Then you two will sail to London... please, finish the letter, lady.";
			link.l1.go = "Abigile_kidnapping_5";
		break;
		
		case "Abigile_kidnapping_5":
			dialog.text = "Lady? Ah, yes...(reading). Charlie, I am ready to sail with you. I need one day to pack my things and to talk with my papa. Come here tomorrow and I will get on your ship.";
			link.l1 = "Alright, lady. I will be here tomorrow. And don't worry about yourself, me and my crew will protect you from any dangers during our voyage.";
			link.l1.go = "Abigile_kidnapping_6";
		break;
		
		case "Abigile_kidnapping_6":
			DialogExit();
			npchar.greeting = "abigile_2";
			NextDiag.CurrentNode = "First time";
			AddQuestRecord("Holl_Gambit", "3-22");
			pchar.quest.Abigile_Kidnap.win_condition.l1 = "Timer";
			pchar.quest.Abigile_Kidnap.win_condition.l1.date.hour  = 7.0;
			pchar.quest.Abigile_Kidnap.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.Abigile_Kidnap.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.Abigile_Kidnap.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.Abigile_Kidnap.win_condition.l2 = "location";
			pchar.quest.Abigile_Kidnap.win_condition.l2.location = "Villemstad_houseSp2";
			pchar.quest.Abigile_Kidnap.function = "AbigileGoToShip";
			pchar.questTemp.HWIC.Self = "AbigileWaitNextDay";
			SetFunctionTimerCondition("AbigileGoToShipOver", 0, 0, 3, false);//таймер 3 дня, ибо нефиг
		break;
		
		case "Abigile_kidnapping_7":
			DialogExit();
			chrDisableReloadToLocation = true;
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, false);
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "SetAbigileToCabin", -1);//Аби в каюту к ГГ поставим
			AddQuestRecord("Holl_Gambit", "3-23");
			pchar.questTemp.HWIC.Self = "AbigileOnShip";
			pchar.quest.AbigileGoToShipOver.over = "yes";//снять таймер
			SetFunctionTimerCondition("RemoveAbigileOver", 0, 0, 30, false);//таймер на 1 месяц, ибо нефиг
			pchar.quest.Abigile_died.win_condition.l1 = "NPC_Death";
			pchar.quest.Abigile_died.win_condition.l1.character = "Abigile";
			pchar.quest.Abigile_died.function = "AbigileDied";//специально для особо упоротых
		break;
		
		case "Abigile_kidnapping_8":
			dialog.text = "Ah, what a pity. But I think that I can wait a week more as I have been waiting before...";
			link.l1 = "Well said, miss. And to make your waiting easier I offer you to change this tight cabin for my friend's house. There will be a soft bed and a nice food prepared only for you.";
			link.l1.go = "Abigile_kidnapping_9";
		break;
		
		case "Abigile_kidnapping_9":
			dialog.text = "You are so caring, Charlie. Thank you. I really feel myself not so good after all of this regular tossing.";
			link.l1 = "Follow me, my dear lady!";
			link.l1.go = "Abigile_kidnapping_10";
		break;
		
		case "Abigile_kidnapping_10":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			pchar.questTemp.HWIC.Self = "AbigileInHouse";
		break;
		
		case "Abigile_kidnapping_11":
			dialog.text = "I am glad to meet you, John. Thank you for your hospitality, gentlemen!";
			link.l1 = "...";
			link.l1.go = "Abigile_kidnapping_12";
		break;
		
		case "Abigile_kidnapping_12":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload3", "SentJons_HouseF3_Room2", "barmen", "bar1", "ContinueWithMerdok", -1);
			pchar.questTemp.HWIC.Self = "AbigileInRoom";
			NextDiag.CurrentNode = "First time";
			RemovePassenger(Pchar, npchar);
			pchar.quest.RemoveAbigileOver.over = "yes";//снять таймер
			sld = characterFromId("Merdok");
			LAi_SetActorType(sld);//чтобы геймер сам с ним не заговорил
		break;
		
		case "Abigile_kidnapping_13":
			dialog.text = "Ah, Charlie, I have seen Richard just a few times and he didn't tell me much about himself.";
			link.l1 = "Well, I don't think that he would hide it from you... Miss, Richard is not just an ordinary captain. He is an agent of the English intelligence. A very important person who deal with missions received right from the English government, it is mostly all about destroying trading connections of Holland merchants at the archipelago.";
			link.l1.go = "Abigile_kidnapping_14"
		break;
		
		case "Abigile_kidnapping_14":
			dialog.text = "What are you talking about?!";
			link.l1 = "Yes, miss. Your beloved and my friend is a very important man. I was always proud to be his friend, but he has become very secretive even with me. It is obvious that he is on some secret mission. I am really upset that this mission doesn't let him to meet you.";
			link.l1.go = "Abigile_kidnapping_15";
		break;
		
		case "Abigile_kidnapping_15":
			dialog.text = "Charlie, you are scaring me. Are you sure that he is alright?";
			link.l1 = "I am totally sure in that. I just... I don't approve how he deals with you now, I understand though that the service is vital and he can't betray his duty even for you.";
			link.l1.go = "Abigile_kidnapping_16";
		break;
		
		case "Abigile_kidnapping_16":
			dialog.text = "Ah, my kind Charlie... I will be waiting Richard for as long as needed. Perhaps you can tell me where to stay in St. John's? I can't abuse John hospitality for that long.";
			link.l1 = "What are you saying, lady!? Your presence itself honours us and I won't be Charlie the Knippel if I will reject to give home and food for a bride of my friend and my patron!";
			link.l1.go = "Abigile_kidnapping_17";
		break;
		
		case "Abigile_kidnapping_17":
			dialog.text = "Charlie... I am really touched by your attitude towards me. I am only just a common girl and...";
			link.l1 = "Miss! Don't even think about taverns! I will never forgive myself if you would be unpleased with my service to Richard and to you.";
			link.l1.go = "Abigile_kidnapping_18";
		break;
		
		case "Abigile_kidnapping_18":
			dialog.text = "Thank you, Charlie. I am glad that you are such a... good man.";
			link.l1 = "It is my duty, miss. Now I am sorry, but I have to go. Yes, and you can freely walk around the town now, you must feel yourself lonely in this house, am I right?";
			link.l1.go = "Abigile_kidnapping_19";
		break;
		
		case "Abigile_kidnapping_19":
			dialog.text = "Well... John is a very interesting company. He can talk about his powders, mixtures and various diseases for hours. He is a polite and kind man. Also I visit church... but, of course, I really miss Richard.";
			link.l1 = "I think he will be back soon. Charlie the Knippel at your service in case you need anything.";
			link.l1.go = "Abigile_kidnapping_20";
		break;
		
		case "Abigile_kidnapping_20":
			DialogExit();
			pchar.questTemp.HWIC.Self = "MeetTonzag";
			pchar.quest.Meet_Tonzag.win_condition.l1 = "location";
			pchar.quest.Meet_Tonzag.win_condition.l1.location = "SentJons_TownCave";
			pchar.quest.Meet_Tonzag.function = "TonzagMeetingInDange";
		break;
		
		case "Abigile_return":
			dialog.text = "I heard rumours about Richard... he has disappeared. Do you know anything about it, Charlie?";
			link.l1 = "I do, Abigail. I am sorry... Richard Fleetwood has gone to Europe and he won't be back. He got a promotion or transfer, something like that... anyway, after what he has done to you, I don't want to know him.";
			link.l1.go = "Abigile_return_1";
		break;
		
		case "Abigile_return_1":
			dialog.text = "Ah, I knew that it would end like that.. I had to listen papa... At least, he would be glad if I'd married Lucas Rodenburg.";
			link.l1 = "Forgive me again, miss...";
			link.l1.go = "Abigile_return_2";
		break;
		
		case "Abigile_return_2":
			dialog.text = "For what, Charlie? You are not guilty at all.";
			link.l1 = "For me telling you another bad news: Lucas Rodenburg is arrested for the attempt of coup in Willemstad. He will be sent to Netherlands and judged. I've just returned from Curacao. He tried to kill a director of the Company Peter Stuyvesant and he's suspected in murdering of one person, so the sentence won't likely be soft.";
			link.l1.go = "Abigile_return_3";
		break;
		
		case "Abigile_return_3":
			dialog.text = "Oh, God! What a nightmare! Charlie, is it true? No, please say that it is not!";
			link.l1 = "Alas, my dear miss. I will add even more: it was revealed, during investigation of Lucas's actions, that the pirate who had sunk your flute was acting under Rodengburg's orders. I am so sorry, Abigail, that you have faced to liars and bastards right after your arrival here.";
			link.l1.go = "Abigile_return_4";
		break;
		
		case "Abigile_return_4":
			dialog.text = "Oh... I have nothing to say. I am completely ruined. Charlie... please... take me back home to Willemstad. I need my papa...";
			link.l1 = "Sure, dear miss. Unfortunately, there is nothing to do here for you in Bridgetown. Go, pack your things, say goodbye to John and we will set sail immediately.";
			link.l1.go = "Abigile_return_5";
		break;
		
		case "Abigile_return_5":
			DialogExit();
			AddQuestRecord("Holl_Gambit", "3-57");
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", -1);
			LocatorReloadEnterDisable("SentJons_HouseF3", "reload4", false);//откроем комнату Аби
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, false);
			pchar.questTemp.HWIC.Self = "AbiReturnHomeGo";
			pchar.quest.AbiReturn_Home.win_condition.l1 = "location";
			pchar.quest.AbiReturn_Home.win_condition.l1.location = "Villemstad_town";
			pchar.quest.AbiReturn_Home.function = "AbiGoInVillemstad";
		break;
		
		case "Abigile_return_6":
			dialog.text = "No, Charlie, I need to say thank you. If it wasn't you and John, I don't even know what would happen to me. You are the only honest men who I have met at the archipelago.";
			link.l1 = "Hm... you are making me blush, Abigail. I was glad to help you. And I am very sorry for all of this mess.";
			link.l1.go = "Abigile_return_7";
		break;
		
		case "Abigile_return_7":
			dialog.text = "You know, Charlie, I had been thinking a lot during our voyage to Curacao. Everything is clear now - Richard Fleetwood, mynheer Rodenburg - everything seems to be just a bad dream which has finally ended. I am with my dad again and we will continue our normal life\nIt won't be easy though - we don't have money. But we will get trought it, everything is going to be fine.";
			link.l1 = "Miss, I'd like to talk with you about it. I... well, understand me correctly I really want to help you.";
			link.l1.go = "Abigile_return_8";
		break;
		
		case "Abigile_return_8":
			dialog.text = "To help? But how, Charlie?";
			link.l1 = "Richard told me the story of your shipwreck and your rescue. Also, I know that your father has stashed his belongings on some mystic island. I want to try to find it.";
			link.l1.go = "Abigile_return_9";
		break;
		
		case "Abigile_return_9":
			dialog.text = "Ah, Charlie. Neither me nor my father are able to tell you where is that ill-fated island even roughly. We are not sailors. I was really scared then, so I don't remember a thing.";
			link.l1 = "Abigail, try to remember details even the smallest ones. Maybe something had happened before the attack? How does this island look like?";
			link.l1.go = "Abigile_return_10";
		break;
		
		case "Abigile_return_10":
			dialog.text = "Island... It looks like an island. A bay, jungles. Nothing special. Oh, I remember! Perhaps it will help you. Not long before the pirate attack we had met a flute of some merchant. He was invited to our ship and had a dinner with our captain. We were there too. Perhaps, he knows about this island.";
			link.l1 = "That is something! What were the names of the flute and her captain?";
			link.l1.go = "Abigile_return_11";
		break;
		
		case "Abigile_return_11":
			dialog.text = "I don't remember, Charlie. I really don't...";
			link.l1 = "Hm... Try to remember, Abi!";
			link.l1.go = "Abigile_return_12";
			pchar.questTemp.HWIC.Self = "SolomonHistory";
		break;
		
		case "Abigile_return_12":
			DialogExit();
			sld = characterFromId("Solomon");
			sld.greeting = "solomon_1";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "Abigile_return_13":
			dialog.text = "We will be waiting for you, Charlie. You are the last hope for us. I will pray for you! God speed!";
			link.l1 = "I am on my way. Farewell, Abi. Farewell, Solomon.";
			link.l1.go = "Abigile_return_14";
		break;
		
		case "Abigile_return_14":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload2", "Villemstad_houseSp2_bedroom", "goto", "goto1", "ReturnAbiNormal", -1);
			pchar.questTemp.HWIC.Self = "SeekFleut";
			AddQuestRecord("Holl_Gambit", "3-58");
		break;
		
		case "Abigile_NoMoney":
			dialog.text = "Ah, what a pity. We were hoping, but... thank you anyway, Charlie, for your try to help us. It seems this is my fate.";
			link.l1 = "Farewell, Abigail. I hope that you will be fine.";
			link.l1.go = "exit";
			npchar.dialog.currentnode = "Abigile_Poor";
		break;
		
		case "Abigile_GiveMoney":
			dialog.text = "Is it... is it true? Have you really brought the lost money to us? Oh, Charlie!";
			link.l1 = "Yes, it is true. I have it. I am ready to give this money to you right now. Here, take it. This is all yours.";
			link.l1.go = "Abigile_GiveMoney_1";
		break;
		
		case "Abigile_GiveMoney_1":
			AddMoneyToCharacter(pchar, -200000);
			pchar.quest.MakeAbiPoor.over = "yes"; //снять прерывание
			ChangeCharacterComplexReputation(pchar, "nobility", 10);
			dialog.text = "How should I thank you?! How?!";
			link.l1 = "I don't need any thanks, Abi. It is the smallest thing I could do for you. Now you will start a new life without any rodenburgs, fleetwoods and other strange people. I suppose that your father will find a way to enlarge this money.";
			link.l1.go = "Abigile_GiveMoney_2";
		break;
		
		case "Abigile_GiveMoney_2":
			dialog.text = "Charlie! You have done so much for me, for me and for my poor father. I has got accustomed to your presence in my life. I have been praying tirelessly for you everyday. You are my guardian angel. The Lord himself has sent you to our family, believe it or not\nBefore you go, I want you to know that the doors of our house will be always open for you any time. And... please, let me kiss you, my dear Charlie...";
			link.l1 = "Well... yes, sure... Abi.";
			link.l1.go = "Abigile_GiveMoney_3";
		break;
		
		case "Abigile_GiveMoney_3":
			DialogExit();
			npchar.greeting = "abigile_1";
			PlayStereoOGG("music_romantic");
			SetLaunchFrameFormParam("", "", 0, 7);
			SetLaunchFrameFormPic("loading\inside\kiss.tga");
			LaunchFrameForm();
			DoQuestFunctionDelay("GoFromAbiRoom", 7.0);
			npchar.dialog.currentnode = "Abigile_AllRight";
		break;
		
		case "Abigile_Poor":
			dialog.text = "Glad to see you, Charlie. Nothing has changed for us... poverty is so hard...";
			link.l1 = "Keep up, miss. Don't collapse.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Abigile_Poor";
		break;
		
		case "Abigile_AllRight":
			dialog.text = "Charlie, it is you! I am so glad to see you! Please, share a meal with us.";
			link.l1 = "I am glad to see you too, Abi. And I am glad that you are doing fine.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Abigile_AllRight";
		break;
		
		//--> блок реагирования на попытку залезть в сундук
		case "Woman_FackYou":
			dialog.text = "Ah, so that is just like that?! I have received you as my guest and you decided to loot chests?! Guards!!!";
			link.l1 = "Shut up, foolish girl...";
			link.l1.go = "exit";
			LAi_group_Attack(NPChar, Pchar);
		break;
		//<-- блок реагирования на попытку залезть в сундук
	}
}
