// Элен Мак Артур - сомнительная любовь и офицер
void ProcessDialogEvent()
{
	ref NPChar, sld, rItm, rItem;
	aref Link, NextDiag, rType;
	int i;
	string 	sAttr, sGun, sBullet, attrL;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	sAttr = Dialog.CurrentNode;
	if (findsubstr(sAttr, "SetGunBullets1_" , 0) != -1)
 	{
        i = findsubstr(sAttr, "_" , 0);
	 	NPChar.SetGunBullets = strcut(sAttr, i + 1, strlen(sAttr) - 1); // индекс в конце
 	    Dialog.CurrentNode = "SetGunBullets2";
 	}
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "Want something?";
			link.l1 = "No, it's nothing.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		case "After_boarding":
			dialog.text = "Thanks for you help, captain!";
			link.l1 = "Hm... You are even more beautiful than I imagined!";
			link.l1.go = "After_boarding_1";
		break;
		
		case "After_boarding_1":
			dialog.text = "To hell with my beauty! It nearly got me killed. He wouldn't let me leave the corvette alive, because I know too much about the bastard. Yesterday he told me that he was tired of waiting and going to get my favour against my will\nSo you have shown a perfect timing, captain! Let's get acquainted. My name is Helen McArthur. My dad used to call me Rumba for my cheerful temper, so that's how they call me now.";
			link.l1 = "Well and my name is "+GetFullName(pchar)+". I have been looking for you across all of archipelago for several days because miss Gladys asked me to do so.";
			link.l1.go = "After_boarding_2";
		break;
		
		case "After_boarding_2":
			dialog.text = "How is she?";
			link.l1 = "She really worries about you. Anyway, soon you will see her, we are sailing to Blueweld now. And while sailing you will tell me everything what happened with you.";
			link.l1.go = "After_boarding_3";
		break;
		
		case "After_boarding_3":
			dialog.text = "To be honest, "+pchar.name+", I'd like to have some meal and a nap right now. I am so tired due to all of these days I have spent on the ship of that monster...";
			link.l1 = "No problem, Helen. I will order to serve you a meal and prepare a bed for you. Be my guest.";
			link.l1.go = "After_boarding_4";
		break;
		
		case "After_boarding_4":
			DialogExit();
			LAi_SetActorType(npchar);
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, false);
			npchar.greeting = "helena_2";
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", 10.0);
			pchar.questTemp.Saga = "returntoblueveld";
			Island_SetReloadEnableGlobal("Antigua", true);//на остров можно
			bQuestDisableMapEnter = false;//открыть карту
			AddQuestRecord("Saga", "11");
			pchar.quest.Saga_returnBlueveld.win_condition.l1 = "location";
			pchar.quest.Saga_returnBlueveld.win_condition.l1.location = "Santacatalina_town";
			pchar.quest.Saga_returnBlueveld.function = "Saga_returnBlueveld";
			SetFunctionTimerCondition("Helena_ReturnOver", 0, 0, 45, false);
			sld = characterFromId("gladis");
			sld.greeting = "gladis_3";
		break;
		
		case "Return_blueveld":
			pchar.quest.Helena_ReturnOver.over = "yes";
			dialog.text = "My captain, I thank you again from the bottom of my heart for my rescue. You must visit me and my mother. Our house is not far from here. Here it is, on the left from the pier. And know, "+pchar.name+", I will never forgive you if you disappear without saying goodbye, know that!";
			link.l1 = "Sure, I will visit you!";
			link.l1.go = "Return_blueveld_1";
		break;
		
		case "Return_blueveld_1":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "houseSp3", "SantaCatalina_houseSp3_bedroom", "goto", "goto1", "OpenTheDoors", -1);
			AddQuestRecord("Saga", "13");
			LocatorReloadEnterDisable("SantaCatalina_houseS1", "reload2", false); // открыть кабинет Свенсона
			pchar.questTemp.Saga = "svenson";//идем к Свенсону
			sld = characterFromId("JS_girl");
			sld.dialog.currentnode = "js_girl";
			npchar.dialog.currentnode = "Helena_wait";
			sld = characterFromId("Gladis");
			sld.dialog.currentnode = "Gladis_regard";
			LocatorReloadEnterDisable("SantaCatalina_houseSp3", "reload2", true);//закрыть спальню Элен
			// закрыть город до беседы с Глэдис
			LocatorReloadEnterDisable("SantaCatalina_town", "reload1_back", true);
			LocatorReloadEnterDisable("SantaCatalina_town", "reload2_back", true);
			LocatorReloadEnterDisable("SantaCatalina_town", "gate_back", true);
		break;
		
		case "Helena_wait":
			dialog.text = "Ah, there you are, my captain! I am so glad, "+pchar.name+", that you have finally decided to visit me. I have got a lot to discuss you.";
			link.l1 = "We will delay this conversation a bit. I need to get some more information before I'll able to answer your questions. And now I'm asking you to not show yourself on the streets. I hope that your waiting will not last long. Trust me and wait.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Helena_wait";
		break;
		
		case "Helena_hire":
			dialog.text = "Ah, there you are, my captain! Your eyes tell me that you've got news for me!";
			link.l1 = "Swanson told me that you are really eager to become my officer. I appreciate your wish, Gladys mentioned that you have missed the sea. Welcome to my crew, officer Helen McArthur!";
			link.l1.go = "Helena_hire_1";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_friend"))
			{
				link.l2 = "Swanson told me that you were really eager to become my officer. I appreciate your wish, Gladys mentioned that you have missed the sea. Welcome to my crew, officer Helen Sharp!";
			link.l2.go = "Helena_hire_2";
			}
		break;
		
		case "Helena_hire_1":
			DeleteAttribute(pchar, "questTemp.Saga.Helena_friend");
			dialog.text = "Aye-aye, my captain! But know that I am a proud girl, I can stand up for myself and I won't tolerate any liberties.";
			link.l1 = "Don't worry, there is an unshakable discipline on my ship. Besides, I want you to know something extra...";
			link.l1.go = "Helena_hire_1_1";
		break;
		
		case "Helena_hire_1_1":
			dialog.text = "And what is it?";
			link.l1 = "Jan Swanson and I have found out that you have rights to inherit Isla Tesoro. Yes, yes, it is true even if it seems impossible. I have a half of the map which can prove your rights. It won't be easy, but me and mister Swanson will do our best to help you to become a rightful ruler of the island.";
			link.l1.go = "Helena_hire_1_2";
		break;
		
		case "Helena_hire_1_2":
			dialog.text = ""+pchar.name+", are you serious? No, you are kidding the poor girl! How can I have rights to the whole island?";
			link.l1 = "I am absolutely serious, Helen. And what is more, I am going to help you to arrange your life. And let's sail now!";
			link.l1.go = "Helena_hire_6";
		break;
		
		case "Helena_hire_2":
			dialog.text = "What did you say? Helen Sharp? Why Sharp?";
			link.l1 = "Helen, you are a daughter of Beatrice Sharp and the only heir of the Sharp family line. This is a half of the map which had been kept by Gladys for all last years. It's an evidence of your rights to Isla Tesoro. It won't be easy, but me and mister Swanson will do our best to help you to become a rightful heir of your grandfather.";
			link.l1.go = "Helena_hire_3";
		break;
		
		case "Helena_hire_3":
			dialog.text = "Ah... My poor mother! I wish I could find her grave one day and take care about it. But... wait! Impossible!";
			link.l1 = "What is it, Helen?";
			link.l1.go = "Helena_hire_4";
		break;
		
		case "Helena_hire_4":
			dialog.text = "The Gypsy's prophecy has just come true... I understand it now.";
			link.l1 = "What prophecy? What are you talking about?";
			link.l1.go = "Helena_hire_5";
		break;
		
		case "Helena_hire_5":
			dialog.text = ""+pchar.name+", you might call me naive, but I will share it with you anyway. Several years ago a gypsy told me 'Your fate will be in the hands of the man who won't take the widow's coin, who will return the dead man's gold and who will name the mother'\nI thought that it was a nonsense back then, but somehow you've managed to fulfil every part of the prophecy, you couldn't know about before!";
			link.l1 = "A fate, you say... Well, perhaps you are right. I'll do my best to not disappoint you and we will look for your mother's grave together. And for now... Officer Helen Sharp! Get yourself ready and don't be late!";
			link.l1.go = "Helena_hire_6";
		break;
		
		case "Helena_hire_6":
			dialog.text = "Aye-aye, captain!";
			link.l1 = "...";
			link.l1.go = "Helena_hire_add";
		break;
		
		case "Helena_hire_add":
			LAi_SetImmortal(npchar, false);
			chrDisableReloadToLocation = true;//закрыть локацию
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "Saga_HireHelena", -1);
			LocatorReloadEnterDisable("SantaCatalina_town", "reload1_back", false);
			LocatorReloadEnterDisable("SantaCatalina_town", "reload2_back", false);
			LocatorReloadEnterDisable("SantaCatalina_town", "gate_back", false);//открыть выходы из города
			pchar.questTemp.Saga = "svenson_wait";
			AddQuestRecord("Saga", "24");
			SetFunctionTimerCondition("Saga_BaronsQuestsGo", 0, 0, 2+rand(2), false);
			AddCharacterExpToSkill(pchar, "Leadership", 100);
		break;
		
		//-->  консультации по морским сражениям в искушении барбазона
		case "sea_bomb":
			dialog.text = ""+pchar.name+"! I have got an idea...";
			link.l1 = ""+npchar.name+"? If you didn't notice it's not safe here. I told you to stay on the ship...";
			link.l1.go = "sea_bomb_1";
		break;
		
		case "sea_bomb_1":
			dialog.text = ""+pchar.name+", there are too much gunpowder in this old tub so if it blows up then the whole island will fly sky high. There is no difference where to stay now. Listen to me!";
			link.l1 = "So? What do you want to tell me?";
			link.l1.go = "sea_bomb_2";
		break;
		
		case "sea_bomb_2":
			dialog.text = "The corvette and the frigate. They believe that we are... Knive. This could be an opportunity for us. Let's take a few barrels of gunpowder, a fuse and will sail to the ships\nAfter they let us close, we'll light the fuse, drop the barrel to one of them and sail away as fast as we can. And then we'll watch a spectacular explosion... What do you say?";
			link.l1 = "Tricky! Though, your plan might work... Only in case they won't recognize us.";
			link.l1.go = "sea_bomb_3";
		break;
		
		case "sea_bomb_3":
			dialog.text = "Let's just risk it, "+pchar.name+"? It won't be easy to fight two ships at once but we'll get a chance...";
			link.l1 = "Fine. We will do that! Lads! Take three barrels with gunpowder! And we are going to get away from here! You are very imaginative, "+npchar.name+"... I would have never come to this idea myself.";
			link.l1.go = "sea_bomb_4";
		break;
		
		case "sea_bomb_4":
			chrDisableReloadToLocation = false;
			DialogExit();
			LAi_SetOfficerType(npchar);
			npchar.dialog.currentnode = "Helena_officer";
			pchar.questTemp.Saga.BarbTemptation.Bomb = "true";
			pchar.questTemp.Saga.BarbTemptation.adviser = "Helena";
		break;
		
		case "fugas":
			dialog.text = "Yes, sure. What is the matter?";
			link.l1 = "There is a Jackman's ship at Sabo-Matila Cove, heavy frigate 'Centurion'. This ship was a property of the Hawkes, besides there must be important items and documents in Jackman's cabin... anyway, we must board it.";
			link.l1.go = "fugas_1";
		break;
		
		case "fugas_1":
			dialog.text = "I see. And how are you going to do that on our polacre? They have more men and cannons.";
			link.l1 = "You are right. Jackman has at least twice more men than we have and all of them are perfectly skilled selected mercenaries. It would be madness to attack them without any preparatory bombardment. The protracted fighting is not the best option too. So I've been thinking about what to do with that.";
			link.l1.go = "fugas_2";
		break;
		
		case "fugas_2":
			dialog.text = "You won't believe, "+pchar.name+", but I have an idea! They haven't recognized us as an enemy yet like those two idiots back on Turks... We can repeat our trick...";
			link.l1 = "Helen, I have just told you that we must board the frigate, sinking it is not an option.";
			link.l1.go = "fugas_3";
		break;
		
		case "fugas_3":
			dialog.text = "I know that, "+pchar.name+". We will not sink her. Listen, we are going to take a few empty rum barrels, gunpowder, grapeshot and short fuse. Then we will sail closer to their frigate and throw barrels with our fire rum at their deck.";
			link.l1 = "Ha! You think that it is going to work?";
			link.l1.go = "fugas_4";
		break;
		
		case "fugas_4":
			dialog.text = "And why not? Their boards are higher than ours but two men will be able to throw a barrel easily. We'll shout them - 'catch some rum from the Knave'! Barrels will explode even before they start thinking.";
			link.l1 = "The grapeshot will spread and eliminate everybody around the explosion... Damn, it sounds tempting. There are hordes of mercenaries walking around at the deck! They are the main threat.";
			link.l1.go = "fugas_5";
		break;
		
		case "fugas_5":
			dialog.text = "Let's throw five barrels at different places. "+pchar.name+", we've got a great advantage - a surprise. They don't suspect of anything! And then we will immediately sail away from them before they have a chance to board us.";
			link.l1 = "Well, let's try. They must not identify us before we throw barrels... Damn it, it wont' be easy to get close to them. Jackman is not that idiotic like the Ghoul was.";
			link.l1.go = "fugas_6";
		break;
		
		case "fugas_6":
			dialog.text = "Let's risk it, "+pchar.name+"! It won't get worse anyway.";
			link.l1 = "It won't, that is for sure... Prepare the fougasses and get ready to fight!";
			link.l1.go = "fugas_7";
		break;
		
		case "fugas_7":
			DialogExit();
			npchar.dialog.currentnode = "Helena_officer";
			pchar.questTemp.Saga.BarbTemptation.Fugas = "true";
			AddQuestRecord("BarbTemptation", "21");
			DeleteAttribute(npchar, "quest.fugas");
		break;
		//<--  консультации по морским сражениям
		
	// --> разговор по итогам Саги
		case "result":
			if (!CheckAttribute(pchar, "questTemp.Saga.Helena_friend")) // не друзья
			{
				dialog.text = "Well, my captain... It is time for us to say goodbye to each other. My service is getting over and it's time to get used to a role of the mistress of Isla Tesoro. I hope that I will be a worthy successor of my uncle. Thank you for your help.";
				link.l1 = "Sure, it's a pity to part with you, but there is nothing I can do. You have got more important things to do than to serve on my ship.";
				link.l1.go = "result_1";
			}
			else
			{
				dialog.text = "It's so strange, "+pchar.name+"! I have just become an owner of the whole island but I don't feel myself as a mistress of Isla Tesoro... I suppose that a new head of the Brethren will manage the colony better than I would. The rent will be enough for me.";
				link.l1 = "Hm. Are you sure, Helen? Think about it, you own the whole island!";
				link.l1.go = "result_9";
			}
		break;
		
		case "result_1":
			dialog.text = "You are right... I was able to collect some gold while sailing on your ship. Take it and don't even try to reject my offer - I don't want to be in your debt.";
			link.l1 = "Hm. Actually...";
			link.l1.go = "result_2";
		break;
		
		case "result_2":
			dialog.text = "I know what you are going to say. Sure, you help was much more significant than this chest with coins. But this is almost all I have got in my possesion right now and I have to repay you. Take it, if you don't take it yourself I will leave it in your cabin.";
			link.l1 = "Are you going to sail on your own now? Perhaps I could take you to Isla Tesoro?";
			link.l1.go = "result_3";
		break;
		
		case "result_3":
			GiveItem2Character(pchar, "chest");
			Log_Info("You have received a chest with doubloons");
			PlaySound("interface\important_item.wav");
			dialog.text = "No need for that, "+pchar.name+". I will get to the island myself. I have got some cash on me, it will suffice for a while... I am sure that the mistress of Isla Tesoro doesn't need to worry about an income.";
			link.l1 = "Whatever you say. I wish you luck in your new life.";
			if (!CheckAttribute(pchar, "questTemp.Saga.Beltrop_die")) link.l1.go = "result_4";
			else link.l1.go = "result_7";
		break;
		
		case "result_4":
			dialog.text = "Thanks. But that is not all I wanted to say. I have found my father again, though it was a bit strange. He has basically paid with his good name of English nobleman for my inheritance and that bothers me. They have declared a hunt for his head and I don't want you, "+pchar.name+", to participate in it.";
			link.l1 = "Come to your senses, Helen! He is a bandit and a pirate!";
			link.l1.go = "result_5";
		break;
		
		case "result_5":
			dialog.text = "Pirate? And who the fuck are you? He is my father and that is the most important! And I, the daughter of a bandit and a pirate, don't give a fuck what the English justice thinks of him. If you try to harm my father in any way, I will forget everything good you have done to me, know that. Consider this as a warning.";
			link.l1 = "Is that so? Actually, girl, you'd better be more polite. I didn't notice any complains from you about my pirate's attitude while I was saving your pretty ass from the hands of Donovan!";
			link.l1.go = "result_6";
		break;
		
		case "result_6":
			dialog.text = "I am sorry. I have gone into a passion. But still, I'd like to stay your friend which would be impossible if you play against my father.";
			link.l1 = "Understood. But don't ever dare to threat me, Helen... Beltrope. You had to come to understanding, while sailing on my ship, that I don't fear anyone and anything. I won't be scared of you, trust me. Farewell now. Nevertheless, I wish you luck.";
			link.l1.go = "result_8";
		break;
		
		case "result_7":
			dialog.text = "Thanks. Perhaps we will meet again, "+pchar.name+"...";
			link.l1 = "And why not? I will visit Isla Tesoro more than once in future. See you there... Bye, Helen!";
			link.l1.go = "result_8";
		break;
		
		case "result_8": // Элен уходит, но ее не затираем
			DialogExit();
			RemovePassenger(pchar, npchar);
			//chrDisableReloadToLocation = true;//закрыть локацию  // уже не надо.
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "goto", "goto24", "", "", "", "", 7);//OpenTheDoors лесник . чтобы бежала и исчезла а не стояла.
			AddQuestRecord("Testament", "11");
			CloseQuestHeader("Testament");
			LocatorReloadEnterDisable("PortRoyal_town", "reload1_back", false); // лесник . пирс. 
			LocatorReloadEnterDisable("PortRoyal_town", "gate_back", false); // ворота.
			InterfaceStates.Buttons.Save.enable = true;//можно сохраняться		
		break;
		
		case "result_9": // вот тут - ключевой момент, если игрок нашел Мэри - выбирай, какая девушка милее
			dialog.text = "I am sure. "+pchar.name+", I'd like to stay on your ship if you let me. To stay with you...";
			if (CheckAttribute(pchar, "questTemp.LSC.Mary") && pchar.questTemp.LSC.Mary == "alive")
			{
				link.l1 = "(choose Mary) Helen! It looks like you don't understand. All your future is secured now and there is nothing for you to worry about. And I have got a war, political intrigues and the total uncertainty ahead of me. You must to arrange a life of your own, there is no room for such an adventurer like me in it.";
				link.l1.go = "result_10";
				link.l2 = "(choose Helen) It's more than I could hope for, Helen. Of course, I don't want to loose you, but perhaps it will better for you to go to Isla Tesoro. Who knows where my fate will lead me to. I have a war, political intrigues and the total uncertainty ahead of me.";
				link.l2.go = "result_15";
			}
			else
			{
				link.l1 = "It's more than I could hope for, Helen. Of course I don't want to loose you but perhaps it will better for you to go to Isla Tesoro. Who knows where my fate will lead me to. I have a war, political intrigues and the total uncertainty ahead of me.";
				link.l1.go = "result_15";
			}
		break;
		
		case "result_10":
			dialog.text = ""+pchar.name+"! Don't lie to me. You just don't want to... Tell me, who is she? That ginger girl from the Island of Abandoned Ships? Am I right?";
			link.l1 = "Helen! It is you who I carry about in first place! How don't you understand that?!";
			link.l1.go = "result_11";
		break;
		
		case "result_11":
			dialog.text = "I knew that... And how was she able to charm you, huh? Is she really that good? Eh, "+pchar.name+"... Well, it's your decision, I have nothing left, but to go to my island. I won't stand between you both\nAnyways, thank you for everything you've done for me. You are the best man I've ever met. I hope that we will stay friends?";
			link.l1 = "Sure... Helen, we will meet several times again on Isla Tesoro. Do you want me to take you there?";
			link.l1.go = "result_12";
		break;
		
		case "result_12":
			dialog.text = "No need in that. I will buy a new ship. I have collected the sum enough to buy and to equip a schooner while serving under your command. I will sail on my 'Rainbow' again.";
			link.l1 = "I am really glad, Helen, that you were so... practical. But sailing on a schooner doesn't suit to the mistress of Isla Tesoro. Soon, I believe, you will get a frigate to yourself.";
			link.l1.go = "result_13";
		break;
		
		case "result_13":
			dialog.text = "Perhaps, "+pchar.name+". Fine. I will go to the shipyard but first... kiss me goodbye. Please...";
			link.l1 = "Helen...";
			link.l1.go = "result_14";
		break;
		
		case "result_14": // прощальный поцелуй
			DialogExit();
			SetMusic("music_romantic");
			SetLaunchFrameFormParam("", "", 0, 12);
			SetLaunchFrameFormPic("loading\inside\kiss.tga");
			LaunchFrameForm();
			WaitDate("", 0, 0, 0, 0, 20); //крутим время
			RecalculateJumpTable();
			DoQuestCheckDelay("Saga_HelenaBye", 12.0);
			pchar.questTemp.LSC.Mary = "return"; // к Мэри
			LocatorReloadEnterDisable("PortRoyal_town", "reload1_back", false); // лесник . пирс. 
			LocatorReloadEnterDisable("PortRoyal_town", "gate_back", false); // ворота.
			InterfaceStates.Buttons.Save.enable = true;//можно сохраняться																					   
		break;
		
		case "result_15":
			dialog.text = "My fate has become your fate since we met. Don't you understand that? "+pchar.name+"? I will follow you at the back of beyond!";
			link.l1 = "And what of your father? Laurence Beltrope? He has become my enemy...";
			link.l1.go = "result_16";
		break;
		
		case "result_16":
			dialog.text = "My father is Sean McArthur. I loved him and mourned the loss of him. He was my only father. And that pirate... I don't even want to talk about him.";
			link.l1 = "Helen... My dear Helen!";
			link.l1.go = "result_17";
		break;
		
		case "result_17":
			dialog.text = ""+pchar.name+", I have always wanted to tell you that you are incredible, you are the best! You have done so much to me that I will never be able to repay you. I want to stay with you. Forever. I will marry you if you want... I love you.";
			link.l1 = "We will be together. I promise!"; // а куда же ты теперь денешься :)
			link.l1.go = "result_18";
		break;
		
		case "result_18":
			dialog.text = ""+pchar.name+", dear... Embrace me! I have been waiting for this moment for too long!";
			link.l1 = "Helen, my girl...";
			link.l1.go = "result_19";
		break;
		
		case "result_19": // романтик-сцена
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_SetActorType(pchar);
			StartQuestMovie(true, true, true);
			PlayStereoOGG("music_romantic");
			bDisableCharacterMenu = true;//лоченые интерфейсы
			InterfaceStates.Buttons.Save.enable = false;//запретить сохраняться
			locCameraRotateAroundHero(0.0, 2.0, 0.0, 0.01, 0.0, 2.0, 0.0, 580);
			DoQuestCheckDelay("Saga_HelenaRomantic", 20.0);
			pchar.GenQuest.MusicContinue = true;
			AddCharacterExpToSkill(pchar, "Leadership", 100);
			DeleteAttribute(pchar, "questTemp.LSC.MaryWait");
			LocatorReloadEnterDisable("PortRoyal_town", "reload1_back", false); // лесник . пирс. 
			LocatorReloadEnterDisable("PortRoyal_town", "gate_back", false); // ворота.																					   
		break;
		
		case "happy":
			dialog.text = ""+pchar.name+"! That was... incredible! I don't want to go anywhere else... Let's stay here until morning. The world can wait!";
			link.l1 = "We'll let it wait, Helen!";
			link.l1.go = "happy_1";
		break;
		
		case "happy_1":
			DialogExit();
			LSC_MaryLoveWaitTime();
			SetLaunchFrameFormParam("Next morning...", "", 0, 4);
			LaunchFrameForm();
			DoQuestCheckDelay("Saga_HelenaRomantic_5", 4.0);
			pchar.questTemp.Saga.Helena_officer = "true"; // показатель, что Элен - наша навсегда
		break;
		
	// -------------------------------------------- провалы саги ------------------------------------
		case "failcenturion":
			dialog.text = "Captain! Jackman is eliminated... So it seems that my family is safe, isn't it?";
			link.l1 = "Yes, Helen, it is safe. But 'Centurion' was sunk and so were all documents and things which could help us to find your mother's grave and prove your rights to claim Isla Tesoro... Eh... Now I will have to storm Tortuga for my own...";
			link.l1.go = "failcenturion_1";
		break;
		
		case "failcenturion_1":
			dialog.text = ""+pchar.name+", don't worry to much. There is nothing we can do now. Don't worry about me either, I will live fine without that island. Thank you for you've done for me!";
			link.l1 = "It sounds like you are going to... leave me, right?";
			link.l1.go = "failcenturion_2";
		break;
		
		case "failcenturion_2":
			dialog.text = "Yes, my captain. I was able to collect enough money to buy and to equip a schooner. I will sail on my 'Rainbow' again. We will meet again in Blueweld, won't we? I am going back home.";
			link.l1 = "Well... good luck, Helen!";
			link.l1.go = "failcenturion_3";
		break;
		
		case "failcenturion_3":
			DialogExit();
			RemovePassenger(pchar, npchar);
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "OpenTheDoors", 5.0);
			if (CheckAttribute(pchar, "questTemp.LSC.Mary") && GetCharacterIndex("Mary") != -1 && !CheckAttribute(pchar, "questTemp.LSC.Mary_officer")) // patch-6
			{
				pchar.questTemp.LSC.Mary = "return"; // к Мэри
			}
		break;
		
		case "late_l1":
			dialog.text = "Well, my captain... It seems that we have failed. Farewell. I am going back home. I have earned enough money under your command to buy a new schooner for myself so we will meet again at the sea!";
			link.l1 = "Good luck, Helen. I am sorry for all of that. Farewell.";
			link.l1.go = "failcenturion_3";
		break;
		
		case "late_l2":
			dialog.text = "Captain! Jackman is eliminated... So it seems that my family is safe, isn't it?";
			link.l1 = "Yes, Helen, it is safe. But I am not happy, I have lost too much time and Isla Tesoro is now the English colony. You were left without any inheritance, so I'll have to storm Tortuga myself...";
			link.l1.go = "failcenturion_1";
		break;
		
		case "late_l3":
			dialog.text = ""+pchar.name+", what did lawyer tell to you?";
			link.l1 = "Eh! I have lost too much time and Isla Tesoro is now the English colony. You were left without any inheritance, so I'll have to storm Tortuga myself... Alas, we've lost.";
			link.l1.go = "failcenturion_1";
		break;
	// <-- провалы Саги
		
		// секс - Элен соглашается не всегда (голова болит, а что вы хотели? :)) и сама не требует секса
		case "cabin_sex":
			if (drand(4) == 0)// вероятность отказа 20%
			{
				dialog.text = RandPhraseSimple(""+pchar.name+", I am not feeling well today. Don't feel bad, please. Let's not do it today...",""+pchar.name+", dear, I have been so tired for the last few days. To be honest, I only want to sleep. Forgive me. Let's do it another time.");
				link.l1 = RandPhraseSimple("Fine...","That's alright. As you wish...");
				link.l1.go = "exit";
				SaveCurrentNpcQuestDateParam(npchar, "sex_go"); // лесник = так же . но в корабле . отказ сохраняем . 
				npchar.quest.daily_sex_cabin = true; // на случай если в самый первый раз откажет чтоб по 10000 раз не приставал .. в кабине
			}
			else
			{
				dialog.text = RandPhraseSimple(""+pchar.name+", I gladly approve your idea! Let's go!",""+pchar.name+", sure, no questions asked! Let's go!");
				link.l1 = RandPhraseSimple("You are my good girl...","You are so charming, Helen...");
				link.l1.go = "cabin_sex_go";
			}
		break;
		
		
		case "cabin_sex_go":
			DialogExit();
			npchar.quest.daily_sex_cabin = true; // для первого раза в каюте перед счетчиком. лесник
			npchar.quest.daily_sex_room = true; // для первого раза в таверне чтобы счетчик запустить . лесник
			chrDisableReloadToLocation = true;//закрыть локацию
			DoQuestCheckDelay("Helena_LoveSex", 1.0);
			NextDiag.CurrentNode = "sex_after";
		break;
		
		case "sex_after":
			dialog.text = RandPhraseSimple("It was wonderful, "+pchar.name+"!..","You were great as always, dear...");
			link.l1 = RandPhraseSimple("I am glad that you were satisfied...","It is always good to be with you, Helen...");
			//DeleteAttribute(npchar, "sex_go");
			link.l1.go = "exit";
			NextDiag.TempNode = "Helena_officer";
			chrDisableReloadToLocation = false;//открыть локаци.
			//SetFunctionTimerCondition("Helena_SexReady", 0, 0, 1, false); // лесник . уже не надо.
			SaveCurrentNpcQuestDateParam(npchar, "sex_go"); // вот тут теперь сохраняются параметры времени . 
		break;
		
		case "room_sex":
			if (CheckAttribute(pchar, "questTemp.Terrapin") && pchar.questTemp.Terrapin == "tavern")
			{
				dialog.text = ""+pchar.name+", I always glad to... But it's not the right time now - we have to catch that scum Thibaut before he escapes.";
				link.l1 = "You are right as always, my girl...";
				link.l1.go = "exit";
				break;
			}
			if (drand(4) == 0) // вероятность отказа 20%
			{
				dialog.text = RandPhraseSimple(""+pchar.name+", I am not feeling well today. Don't feel hurt, please. Let's not do it today...",""+pchar.name+", dear, I have been so tired for the last few days. To be honest, I only want to sleep. Forgive me. Let's do it another time.");
				link.l1 = RandPhraseSimple("Fine...","That's alright. As you wish...");
				link.l1.go = "exit";
				SaveCurrentNpcQuestDateParam(npchar, "sex_go"); // лесник - если отказала , сохраним . чтоб не приставал по 100 раз.
				npchar.quest.daily_sex_room = true; // сли первый раз в таверне отказала. лесник
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = RandPhraseSimple(""+pchar.name+", I gladly approve your idea! Let's go!",""+pchar.name+", sure, no questions asked! Let's go!");
				link.l1 = RandPhraseSimple("You are my good girl...","You are so charming, Helen...");
				link.l1.go = "room_sex_go";
			}
		break;
		
		case "room_sex_go":
			DialogExit();
			npchar.quest.daily_sex_room = true; // для первого раза в таверне чтобы счетчик запустить . лесник
			npchar.quest.daily_sex_cabin = true;
			if (sti(pchar.money) >= 10) AddMoneyToCharacter(pchar, -10);
			chrDisableReloadToLocation = true;//закрыть локацию // лесник - добавил закрцтие локи в таверне, чтоб поговорил после траханья с ней.
			DoQuestReloadToLocation(pchar.location+"_upstairs", "quest", "quest4", "");
			ChangeCharacterAddressGroup(npchar, pchar.location+"_upstairs", "quest", "quest3");
			DoQuestCheckDelay("Helena_LoveSex", 2.5);
			NextDiag.CurrentNode = "sex_after";
		break;
		
		//--> ----------------------------------- офицерский блок ------------------------------------------
		case "Helena_officer":
			ref rLoc = &Locations[FindLocation(pchar.location)];
			dialog.text = LinkRandPhrase("Yes, "+pchar.name+"?","Yes, my captain?","I am listening, "+pchar.name+"...");
			if (CheckAttribute(pchar, "questTemp.Dolly_Tieyasal") && !CheckAttribute(npchar, "quest.Tieyasal"))
			{
				Link.l4 = "Helen, I am going to visit the old Indian city Tayasal. I won't lie to you: this trip is very dangerous and even more - it includes teleportation through the idol. Will you... follow me?";
				Link.l4.go = "tieyasal";
			}
       ////////////////////////казначей///////////////////////////////////////////////////////////
           		// boal отчёт о корабле
			if(CheckAttribute(NPChar, "treasurer") && NPChar.treasurer == 1)
			{
			    Link.l11 = "Helen, give me a full ship report.";
			    Link.l11.go = "QMASTER_1";
			        
			    // Warship. Автозакупка товара
				Link.l12 = "I want you to purchase certain goods every time we are docked.";
				Link.l12.go = "QMASTER_2";
			}
			
            /////////////////////////////////////казначей////////////////////////////////////////////////////////////     			
			if (CheckAttribute(NPChar, "IsCompanionClone"))//////////////////компаньон//////////////////////////////////////////////
			{
				//dialog.text = "Я прибыл по вашему распоряжению, капитан.";
				Link.l2 = "Helen, I need to issue several orders to you.";
				Link.l2.go = "Companion_Tasks";
				NextDiag.TempNode = "Helena_officer";// не забыть менять в зависисомости от оффа
				break;
			}																															
			if (CheckAttribute(npchar, "quest.fugas"))
			{
				Link.l3 = "Helen, I need your advice.";
				Link.l3.go = "fugas";
			}
			Link.l1 = "Helen, I have an order for you...";
            Link.l1.go = "stay_follow";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && pchar.location == Get_My_Cabin() && GetNpcQuestPastDayParam(npchar, "sex_go") >= 1 || !CheckAttribute(npchar, "quest.daily_sex_cabin") && pchar.location == Get_My_Cabin()) // лесник - ждем 1 день и снова трах предлагать можно.
			{
				Link.l2 = RandPhraseSimple("Helen, let's stay in the cabin together alone... for a few hours? Are you okay with that?","Darling, let's spend next few hours tete-a-tete? Do you like this idea?");
				Link.l2.go = "cabin_sex";
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && rLoc.type == "tavern" && sti(pchar.money) >= 10 && GetNpcQuestPastDayParam(npchar, "sex_go") >= 1 || !CheckAttribute(npchar, "quest.daily_sex_room") && rLoc.type == "tavern")//  лесник - так же ждем 1 день и снова предлогать можно.
			{
				Link.l2 = RandPhraseSimple("Helen, why won't we rent a room and stay there in private... for a next few hours? How do you feel about that?","Darling, let's spend next few hours tete-a-tete? We'll rent a room... Will you stay?");
				Link.l2.go = "room_sex";
			}
			link.l9 = "It's nothing so far, Helen.";
			link.l9.go = "exit";
			NextDiag.TempNode = "Helena_officer";
		break;
		
		/////////////////////////// ответы для казнаячея - Элен ..(элен казначей - ужас!))///////////////////////////////////
		case "QMASTER_1":
			dialog.Text = "Charles, dear, are you ill or something? What, you expect me to go down below, sweep the hold and start counting rats?";
			Link.l1 = "Right, sorry darling, my bad...";
			Link.l1.go = "exit";
		break;	

		case "QMASTER_2":
			dialog.text = "And I want my very own frigate, with a hundred guns and 20 knots fast. I had been a captain like you all my life. Go get yourself a purser and bother him with it.";
			link.l1 = "Yup, you probably right, my dear. Sorry about that.";
			link.l1.go = "exit";
		break;
		//Указания для компаньона 19.02.08 -->/////////////////////////////////////////////////////////////////////////////////////////
		case "Companion_Tasks":
			dialog.Text = "I am all ears.";
			Link.l1 = "About our boarding policy...";
			Link.l1.go = "Companion_TaskBoarding";
			Link.l2 = "About the ship you command...";
			Link.l2.go = "Companion_TaskChange";
			Link.l8 = "Nothing so far.";
			Link.l8.go = "exit";
			 
		break;
		
		case "Companion_TaskBoarding":
			dialog.Text = "What is your wish, my captain?";
			Link.l1 = "I don't want you to board anything. Keep yourself and your men safe.";
			Link.l1.go = "Companion_TaskBoardingNo";
			Link.l2 = "I want you to board enemy ships at the first opportunity.";
			Link.l2.go = "Companion_TaskBoardingYes";
		break;
		
		case "Companion_TaskChange":
			dialog.Text = "Что желает мой капитан?";
			Link.l1 = "I'd appreciate it if you abstained from swapping ships after boarding. She's too valuable for me.";
			Link.l1.go = "Companion_TaskChangeNo";
			Link.l2 = "If you happen to board anyone, take a good look at the prize vessel. If she's any good, feel free to take her for yourself.";
			Link.l2.go = "Companion_TaskChangeYes";
		break;
		
		case "Companion_TaskBoardingNo":
			dialog.Text = "Okay, I'll think about it.";
			Link.l1 = "She'll think... Right, like I can give her orders anyway.";
			Link.l1.go = "exit";
			NPChar.Tasks.CanBoarding = false;
		break;
		
		case "Companion_TaskBoardingYes":
			dialog.Text = "Okay, I'll think about it.";
			Link.l1 = "She'll think... Right, like I can give her orders anyway.";
			Link.l1.go = "exit";
			NPChar.Tasks.CanBoarding = true;
		break;
		
		case "Companion_TaskChangeNo":
			dialog.Text = "Okay, I'll think about it.";
			Link.l1 = "She'll think... Right, like I can give her orders anyway.";
			Link.l1.go = "exit";
			NPChar.Tasks.CanChangeShipAfterBoarding = false;
		break;
		
		case "Companion_TaskChangeYes":
			dialog.Text = "Okay, I'll think about it.";
			Link.l1 = "She'll think... Right, like I can give her orders anyway.";
			Link.l1.go = "exit";
			NPChar.Tasks.CanChangeShipAfterBoarding = true;
		break;
	//	<========//////////////////////////////////////																																			  
		
		case "stay_follow":
            dialog.Text = "Orders?";
            Link.l1 = "Stand here!";
            Link.l1.go = "Boal_Stay";
            Link.l2 = "Follow me and keep up!";
            Link.l2.go = "Boal_Follow";
			sGun = GetCharacterEquipByGroup(NPChar, GUN_ITEM_TYPE);
			if(sGun != "")
			{
				rItm = ItemsFromID(sGun);
				if(CheckAttribute(NPChar, "chr_ai.bulletNum") && sti(NPChar.chr_ai.bulletNum) > 1)
				{
					Link.l3 = "Change the type of ammo for your firearms.";
					Link.l3.go = "SetGunBullets";
				}	
			}		
		break;
		
		case "SetGunBullets":
			Dialog.Text = "Choosing the type of ammo:";
			sGun = GetCharacterEquipByGroup(NPChar, GUN_ITEM_TYPE);
			rItm = ItemsFromID(sGun);
			makearef(rType, rItm.type);	
			for (i = 0; i < sti(NPChar.chr_ai.bulletNum); i++)
			{
				sAttr = GetAttributeName(GetAttributeN(rType, i));
				sBullet = rItm.type.(sAttr).bullet;
				rItem = ItemsFromID(sBullet);								
				attrL = "l" + i;
				Link.(attrL) = GetConvertStr(rItem.name, "ItemsDescribe.txt");;
				Link.(attrL).go = "SetGunBullets1_" + i;
			}
		break;	

		case "SetGunBullets2":
			i = sti(NPChar.SetGunBullets) + 1; 
			sGun = GetCharacterEquipByGroup(NPChar, GUN_ITEM_TYPE);
			rItm = ItemsFromID(sGun);
			sAttr = "t" + i;
			sBullet = rItm.type.(sAttr).bullet;
			LAi_SetCharacterUseBullet(NPChar, sBullet);
			LAi_GunSetUnload(NPChar);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DeleteAttribute(NPChar,"SetGunBullets");
			DialogExit();
		break;		
		
        case "Boal_Stay":
            Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(Npchar.id);
            AddDialogExitQuestFunction("LandEnc_OfficerStay");
            dialog.Text = "At once, captain!";
            Link.l1 = "...";
            Link.l1.go = "Exit";
            Npchar.chr_ai.tmpl = LAI_TMPL_STAY;
        break;
        
        case "Boal_Follow":
            SetCharacterTask_FollowCharacter(Npchar, PChar);
            dialog.Text = "At once, captain!";
            Link.l1 = "...";
            Link.l1.go = "Exit";
        break;
		//<-- ----------------------------------- офицерский блок ----------------------------------------
		
		// --> суп из черепахи
		case "terrapin_grot":
			dialog.text = "There you are! I have barely found you... That was something, my captain! I have never seen such a roof run and a jump from such a breathtaking height! My heart was ready to explode! One day you will kill me with these tricks of yours, dear... Oh, ain't you alone here? Who is that girl?";
			link.l1 = "This is Catherine Fox, a daughter of colonel Fox, commander of 'sea foxes' marines. We will take her to Antigua.";
			link.l1.go = "terrapin_grot_1";
		break;
		
		case "terrapin_grot_1":
			dialog.text = "Intriguing! Welcome aboard miss Fox... And now lets get to the longboat - we need to get out here.";
			link.l1 = "You are the best, Helen! And what would I do without you?.. Catherine, follow me!";
			link.l1.go = "terrapin_grot_2";
		break;
		
		case "terrapin_grot_2":
			DialogExit();
			npchar.dialog.currentnode = "Helena_officer";
			LAi_SetOfficerType(npchar);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			Terrapin_GotoShip();
		break;
		// <-- суп из черепахи
		
		// --> калеуче
		case "on_coast":
			dialog.text = "Finally you woke up, dear. How do you feel? You have really scared me";
			link.l1 = "Helen, what happened? My head is splitting...";
			link.l1.go = "on_coast_1";
		break;
		
		case "on_coast_1":
			dialog.text = "When we entered the captain's cabin, you were lying on the floor still. My heart has almost stopped beating! The guys picked you up and dragged you to our ship - and just in time, since the dead men lying on the deck began to rise again.\nThat was a real nightmare! They were totally impervious! We quickly cut the ropes and tried to sail away, but a volley from their ship quickly turned our old tub into splinters. And then they hoisted sails and were gone in blink of an eye.\nOur ship sank, and everyone who managed to survive, have reached the shore in a boat. I managed to take your chest from the cabin. I know you keep many important things in there...";
			link.l1 = "You're a smart girl, Helen. What would I do without you?";
			link.l1.go = "on_coast_2";
		break;
		
		case "on_coast_2":
			dialog.text = "I dragged you into the boat and then got you to the shore. You seemed dead, only your heart was beating very faintly. My hands are still shaking";
			link.l1 = "Thank you, love. I am indebted to you. How long had I been lying there, unconscious?";
			link.l1.go = "on_coast_3";
		break;
		
		case "on_coast_3":
			dialog.text = "For an entire day. I washed and bound your wounds, gave you medicine and poured some rum into you. Now you must get well!";
			link.l1 = "I promise I will not die this time, darling. Although I don't feel really well...";
			link.l1.go = "on_coast_4";
		break;
		
		case "on_coast_4":
			dialog.text = "That's for sure... Was it the 'Flying Dutchman', cap? Why did they attack us? And why didn't they shoot at us before the boarding, but sank the ship with just one volley later?";
			link.l1 = "Their captain needed the amulet, about which I had talked to Tuttuathapak, an Indian shaman. That's why they haven't sunk us immediately, but as soon as their leader got the amulet, they quickly disposed of us... What a nightmare! A ship manned by the dead! Impossible to believe...";
			link.l1.go = "on_coast_5";
		break;
		
		case "on_coast_5":
			dialog.text = "Yeah, now it was our turn to encounter the 'Flying Dutchman'. When I have the chance, I'll go to church, light the candle for our miraculous delivery, and pray to our Lord";
			link.l1 = "Me too, Helen, I guess. But first I'll go back to that village. I need to tell Tuttuathapak everything about it. That accursed ship attacked us because of the amulet! I hope that red-skinned devil has some ideas, why the hell those living dead might have needed it.";
			link.l1.go = "on_coast_6";
		break;
		
		case "on_coast_6":
			dialog.text = "Alright. But you must be careful - your wounds have barely healed.";
			link.l1 = "But you will help me to heal, won't you? And Helen, I love you...";
			link.l1.go = "on_coast_7";
		break;
		
		case "on_coast_7":
			chrDisableReloadToLocation = false;//открыть локацию
			dialog.text = "I love you too, my darling...";
			link.l1 = "...";
			link.l1.go = "on_coast_8";
		break;
		
		case "on_coast_8":
			DialogExit();
			npchar.dialog.currentnode = "Helena_officer";
			LAi_SetOfficerType(npchar);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			AddQuestRecord("Caleuche", "5");
		break;
		// <-- калеуче
		
		// на Тайясаль
		case "tieyasal":
			dialog.text = ""+pchar.name+", I have told you once that we share our fates together now. Your fate is my fate. When are we going there?";
			link.l1 = "You said yes, my darling... I am very glad. I will tell you a bit later when we go there. We need to prepare ourselves.";
			link.l1.go = "tieyasal_1";
		break;
		
		case "tieyasal_1":
			dialog.text = "I am ready, my captain! I will follow you at the back of beyond!";
			link.l1 = "Thank you, my love...";
			link.l1.go = "tieyasal_2";
		break;
		
		case "tieyasal_2":
			DialogExit();
			AddQuestRecord("Tieyasal", "20");
			npchar.quest.Tieyasal = "teleport";
		break;
		
		// на Исла Тесоро
		case "islatesoro":
			dialog.text = "Oh, "+pchar.name+"! Glad to see you! What are you doing here, on Isla Tesoro?";
			link.l1 = "Same as always - business matters. And of course I wanted to see you, Helen...";
			link.l1.go = "islatesoro_1";
		break;
		
		case "islatesoro_1":
			DialogExit();
			NextDiag.CurrentNode = "islatesoro";
		break;
		
		// Jason „ороже золота
		case "GoldenGirl":
			dialog.text = "What's the matter with our dearest governor again, Captain? Whose arse are we kicking this time? Spanish, pirates or someone worse?";
			link.l1 = "It's worse, Helen, much worse. The governor is intending to pay a visit to an extremely expensive courtesan and I am supposed to accompany him as a curiosity, promised to the mistress. Boring talks, overpriced wine and dull nobles.";
			link.l1.go = "GoldenGirl_1";
			link.l2 = "Quite the opposite, an invitation to burden less social event, run by a noble lady. His Excellency took me by surprise by asking me to accompany him, but to be honest, I am glad to get my mind off things.";
			link.l2.go = "GoldenGirl_5";
		break;
		
		case "GoldenGirl_1":
			dialog.text = "Right, so you will jump like a pet monkey for good-for-nothings' amusement? How sweet! How about we dump them? Let's make sail and get the hell out here. If you are in the mood for a long deserved vacation, let's sail to Isla Tesoro. We are always welcome there. Sunbathing, old friends, getting our minds off things - you name it.";
			link.l1 = "Look, all this sounds fantastic, and I'd love to... but later. I gave a promise to the governor, this thing is important for the old man and...";
			link.l1.go = "GoldenGirl_2";
		break;
		
		case "GoldenGirl_2":
			dialog.text = "And what? You think your noble blood means a single damn for them? I know all about this 'high society' and for them, Charles de Maure is not a Captain you follow and trust with your life. Not an equal nobleman, equals to them don't fight in a powder fog. He is not even a human being! He is just an curious additions to a meal. Like a pet leopard or a two-headed freak! A fancy toy! Since when do you agree to be treated like a toy?!";
			link.l1 = "Helen please don't freak out. I am sure I can handle a few uncomfortable glances for the governor's satisfaction.  It is easier than boarding, so I will do just fine. And these 'good-for-nothings' are not always like that. Even high societies have worthy people in their ranks... at least I think they are supposed to.";
			link.l1.go = "GoldenGirl_3";
		break;
		
		case "GoldenGirl_3":
			dialog.text = "Whatever. But be ye warned - no way I am squeezing myself in a fancy dress. I don't give a damn if they will start fainting and disapproving.";
			link.l1 = "I wasn't going to make you. No point for both of us to suffer there. I will live through this party and then we will sail to Isla Tesoro. I recon we had a crate of excellent Spanish madeira wine in cargo hold...";
			link.l1.go = "GoldenGirl_4";
		break;
		
		case "GoldenGirl_4":
			dialog.text = "Are you saying that I am no good for such esteemed company? Two monkeys would ruin all the fun? How interesting. Fine, but don't forget to dress yourself with fashion, Captain. Monkeys in fancy dresses can touch even a courtesan's heart. Happy performance!";
			link.l1 = "Helen, wait! Fuck...";
			link.l1.go = "GoldenGirl_8";
		break;
		
		case "GoldenGirl_5":
			dialog.text = "Yeah, we earned some rest alright. But damn me if I am squeezing myself in a fancy dress for this. How far gossips about your woman dressed like a man and a sailor will travel do you think?";
			link.l1 = "I don't think that's a great idea. This marquise runs events men don't take their dames to. Respected dames.";
			link.l1.go = "GoldenGirl_6";
		break;
		
		case "GoldenGirl_6":
			dialog.text = "Just wonderful - whores and high society's depravity! So why you just didn't fucking say so? I am not some jealous idiot and won't shoot you where you stand. At least not right now.";
			link.l1 = "Helen, all I will be doing is accompanying our governor, he asked me to and he was very persistent about it. There will be no... courtesans. I mean there will be but... damn it! I am just paying my respects!";
			link.l1.go = "GoldenGirl_7";
		break;
		
		case "GoldenGirl_7":
			dialog.text = "I suggest you dress yourself in fashion for such an occasion, Captain. High society and all. It's a pure scandal showing up there without a collar and сuffs. Even for a courtesan. Have... fun.";
			link.l1 = "Helen, wait! Fuck...";
			link.l1.go = "GoldenGirl_9";
		break;
		
		case "GoldenGirl_8":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "GoldenGirl_GirlExit", 15.0);
			pchar.questTemp.GoldenGirl.Angry1 = "true";
		break;
		
		case "GoldenGirl_9":
			DialogExit();
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "GoldenGirl_GirlExit", 15.0);
			pchar.questTemp.GoldenGirl.Angry2 = "true";
		break;
		
		case "GoldenGirl_10":
			dialog.text = "Cuffs and a collar, Captain. And perhaps, lace. I heard they are in fashion again.";
			link.l1 = "Helen oh, come on!";
			link.l1.go = "GoldenGirl_11";
		break;
		
		case "GoldenGirl_11":
			DialogExit();
			NextDiag.CurrentNode = "GoldenGirl_10";
		break;
		
		case "GoldenGirl_12":
			dialog.text = "Look at this! Our lost in high society captain!";
			link.l1 = "...";
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.Angry1")) link.l1.go = "GoldenGirl_13";
			else link.l1.go = "GoldenGirl_18";
		break;
		
		case "GoldenGirl_13":
			dialog.text = "Did the local fancy gentlemen approved the new monkey of theirs? They say that its performance last night was legendary! Gambling over ships and courtesans, challenging for a duel high born bastards? Would you kindly explain what the hell is going on with you?";
			link.l1 = "Helen, it's not that simple. Damn it, I am sorry, but I never thought I'd have to stay the night at madam Botot's place. I only slept there, alone, I swear! And yes, I won a freaking frigate in cards. Imagine that?";
			link.l1.go = "GoldenGirl_14";
		break;
		
		case "GoldenGirl_14":
			dialog.text = "Great! I am starting to think that you are either a saint or a fool. We will discuss courtesans and ships you won later - now tell me everything about the duel and why everyone is gossiping that you had challenged some sort of a crown prince?";
			link.l1 = "This man is a bastard of a very influential nobleman, Count de Levi Vantadur. It was he who challenged me in the first place, and I must win the duel without hurting him to much to avoid his father's wrath.";
			link.l1.go = "GoldenGirl_15";
		break;
		
		case "GoldenGirl_15":
			dialog.text = "Blast! And how are we supposed to do this? What if he plays dirty? Happens to us all the time!";
			link.l1 = "This is why Excellency has provided me with noble seconds. I will take only them with me - if things will go down south, at least I will be able to prove that everything went according to the duel codex and the law. I am asking you to watch over the frigate while I am gone.";
			link.l1.go = "GoldenGirl_16";
		break;
		
		case "GoldenGirl_16":
			dialog.text = "LetХs make sure that I got it right. You had been gone for a whole day and a night, won in a card game an extremely expensiveЙ dame for yourself. And now, you are about to fight a powerful noble whoreson who you are not allowed to kill, while IЙ we are supposed to sit tight and just wait? How am I supposed to feel about all this? Tell me.";
			link.l1 = "Helen, listen, you have every right to be mad at me and I am very sorry, but it is just...";
			link.l1.go = "GoldenGirl_17";
		break;
		
		case "GoldenGirl_17":
			dialog.text = "You know what, I had enough of this. Just go and do your thing! It looks like there is no room for me here and we will talk about this when this is over. Now I'll take my leave to get properly drunk! I'll take care of your new frigate, Captain, don't you worry. And, Cap, try not to die... for I will kill you myself.";
			link.l1 = "Helen, just let me explain! Fuck... Here we go again?!";
			link.l1.go = "GoldenGirl_23";
		break;
		
		case "GoldenGirl_18":
			dialog.text = "They say nowadays fashion demands to win ships and courtesans in card games rather than buy them! Moreover, if one want to make a good impression of himself, he has to challenge their previous owners to a duel. What the sick mess you got yourselves into again?!";
			link.l1 = "Helen, it's not that simple. Damn it, I am sorry, but I never thought I'd have stay the night at madam Botot's place! Last night turned into an exhausting and brutal card battle. And yes, I won a freaking frigate in cards. Imagine that?";
			link.l1.go = "GoldenGirl_19";
		break;
		
		case "GoldenGirl_19":
			dialog.text = "Lovely. Meaning that you won a courtesan too? And the frigate you wonЙ what did you stake against it? It can't be our...";
			link.l1 = "I had to. It's a long story but in the end, I won. My opponent challenged me for a duel and accused me of cheating. He is a bastard of an extremely influential nobleman, Count de Levi Vantadur. Which effectively means that I will have to do my best not to kill him.";
			link.l1.go = "GoldenGirl_20";
		break;
		
		case "GoldenGirl_20":
			dialog.text = "Will he do the same? Did you bust your nuts, Cap? To risk your ship, to risk your life because of some... Madame?! Is she really worth it?";
			link.l1 = "Helen, there is no reason to be jealous, I swear. It just happened. I had to do it and the governor provided me with noble officers as my seconds in order to erase any doubt and suspicions which will come afterwards. I can't take neither you nor my other guys with me. Please take care of the frigate while I am gone.";
			link.l1.go = "GoldenGirl_21";
		break;
		
		case "GoldenGirl_21":
			dialog.text = "Just great! First, you go to party with courtesans and show back only next and I even didn't clip you for that. Second, you tell me that nearly lost our ship, but won a courtesan! And now you about to fight for her against some highborn whoreson who you are not even allowed to kill! How am I supposed to feel about all this? Tell me.";
			link.l1 = "Helen, listen, you have every right to be mad at me, but it is just...";
			link.l1.go = "GoldenGirl_22";
		break;
		
		case "GoldenGirl_22":
			dialog.text = "You know what, I had enough of this. Just go and do your thing! It looks like there is no room for me here and we will talk about this when this is over. Now I'll take my leave to get properly drunk! I'll take care of your new frigate, Captain, don't you worry. But if something happens to you, I swear to God, I will rain hellfire upon this town and I will bury this brothel and our beloved Excellency's palace!";
			link.l1 = "Helen, it'll be alright, trust me. Wait, where are you going?! FuckЙ Here we go again...";
			link.l1.go = "GoldenGirl_23";
		break;
		
		case "GoldenGirl_23":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "GoldenGirl_GirlToFregat", 15.0);
		break;
		
		case "GoldenGirl_24":
			dialog.text = "Charles, would you kindly explain to me what the hell happened? Some brigands assaulted the ship. Then that filthy scum started asking me how far would you go to rescue me. In the end, they locked me and lost count of the days!";
			link.l1 = "That bastard wanted to repay me for the shame I brought on him. I feared he'd do something to you! Thank God, you are alright!";
			link.l1.go = "GoldenGirl_25";
		break;
		
		case "GoldenGirl_25":
			dialog.text = "I take it you had to do something to get me back? Something bad, right?";
			link.l1 = "All that matters is you are back with me. I failed you, Helen. I am so sorry! I hope you can find it in your heart to forgive me!";
			link.l1.go = "GoldenGirl_26";
		break;
		
		case "GoldenGirl_26":
			dialog.text = "Already did. I am sorry too, Charles. If only I didn't took your dealings with that marquise too personalЙ I would had set a proper watch that night. So silly of me!";
			link.l1 = "Past is the past. I love you and I will never leave you back. I promise!";
			link.l1.go = "GoldenGirl_27";
		break;
		
		case "GoldenGirl_27":
			dialog.text = "I guess, I'd better not know what exactly you did, right? Okay, we are together again and that's the main thing.";
			link.l1 = "I have no secrets from you. I will tell you...";
			link.l1.go = "GoldenGirl_28";
		break;
		
		case "GoldenGirl_28":
			DialogExit();
			SetLaunchFrameFormParam("Little time has passed...", "", 0.1, 3.0);
			LaunchFrameForm();
			WaitDate("", 0, 0, 0, 1, 0);
			npchar.dialog.currentnode = "GoldenGirl_28_1";
			LAi_SetActorType(npchar);
			LAi_ActorDialogDelay(npchar, pchar, "", 4.0);
		break;
		
		case "GoldenGirl_28_1":
			if (pchar.questTemp.GoldenGirl == "alarm_fin")
			{
				dialog.text = "What a mess... I know you had no choice, but how to explain this to Di Lu Parkes and his friends? I mean, you became a criminal and all?";
				link.l1 = "I chose to pay that price, but yeah, I hade no choice either. Don't you worry, I'll see a way to fix it and to restore my good name. If not, then we will always be welcome at Isla Tesoro! I will manage if you are with me.";
			}
			else
			{
				dialog.text = "What a story to tell... I believe you had no choice in the matter but what comes next? Will that Brit make things right and is it a war? You sure you don't want to come to Basse-Terre and to witness they chaining the bastard?";
				link.l1 = "You know Helen, two weeks ago I would never miss it. But today I say to hell with him! I don't even care anymore about the retribution. We are together again, that is all that matters!";
			}
			link.l1.go = "GoldenGirl_29";
		break;
		
		case "GoldenGirl_29":
			if (pchar.questTemp.GoldenGirl == "alarm_fin")
			{
				dialog.text = "You know that I will always be with you. It's not like it the first time you and I neck deep in mess. We'll make it again.";
				link.l1 = "True. Let's set sails, dear! Life goes on!";
			}
			else
			{
				dialog.text = "I like your thinking, Charles! French, British, Spaniards - whatever. I think we earned a vacation!";
				link.l1 = "Agreed. Only you and me! No more governors and highborn bastards!";
			}
			link.l1.go = "GoldenGirl_30";
		break;
		
		case "GoldenGirl_30":
			if (pchar.questTemp.GoldenGirl == "alarm_fin")
			{
				dialog.text = "Aye, aye, Captain!";
				link.l1 = "";
			}
			else
			{
				dialog.text = "Sounds lovely! I will go to tell boys it's time to weigh anchor! And Charles...";
				link.l1 = "I know Helen, I know. I will join you in a moment.";
			}
			link.l1.go = "GoldenGirl_31";
		break;
		
		case "GoldenGirl_31":
			DialogExit();
			npchar.dialog.currentnode = "Helena_officer";
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "sea", "none", "", "", "GoldenGirl_GirlGoOnBoard", 10.0);
		break;
		
		case "GoldenGirl_32":
			dialog.text = "Charles, you've made it! The Portuguese told me everything! What a story!";
			link.l1 = "Thank god, you live, Helen! You have no idea how glad I am too see you again!";
			link.l1.go = "GoldenGirl_33";
		break;
		
		case "GoldenGirl_33":
			dialog.text = "Speaking of which. You promised to tell me something, remember? Something big and complicated. This is your chance, Captain. What the hell happened with us?!";
			link.l1 = "IЙ I love you, Helen. The rest is irrelevant.";
			link.l1.go = "GoldenGirl_34";
		break;
		
		case "GoldenGirl_34":
			dialog.text = "Yeah, this was helpful, butЙ Damn, me too, Charles. I love you too. God, I've missed you so much!";
			link.l1 = "Me too. Come with me, I won't leave you tonight even if the sky will start falling on this miserable town. I will never leave you again. Ever.";
			link.l1.go = "GoldenGirl_35";
		break;
		
		case "GoldenGirl_35":
			dialog.text = "I guess, I'd better not know what exactly you did, right? Okay, we are together again and that's the main thing.";
			link.l1 = "I have no secrets from you. I will tell you...";
			link.l1.go = "GoldenGirl_36";
		break;
		
		case "GoldenGirl_36":
			DialogExit();
			SetLaunchFrameFormParam("Little time has passed...", "", 0.1, 3.0);
			LaunchFrameForm();
			WaitDate("", 0, 0, 0, 1, 0);
			npchar.dialog.currentnode = "GoldenGirl_36_1";
			LAi_SetActorType(npchar);
			LAi_ActorDialogDelay(npchar, pchar, "", 4.0);
		break;
		
		case "GoldenGirl_36_1":
			dialog.text = "Unbelievable! Did you just say that France and England are at the brink of war with each other because of me?";
			link.l1 = "No, Helen. Because of my stupidity more like. I had to bring you back and fix everything.";
			link.l1.go = "GoldenGirl_37";
		break;
		
		case "GoldenGirl_37":
			dialog.text = "This all is very touching and romantic, I am even ready to forget about how it all had started in the first place. Almost ready. Ah, whatever! They arrested you because the Portuguese gave a wrong name of the damned brigantine?";
			link.l1 = "Quite the contrary, he gave me the right one! I wish I knew how he managed to pull this off and whyЙ By the way, where is the man himself?!";
			link.l1.go = "GoldenGirl_38";
		break;
		
		case "GoldenGirl_38":
			dialog.text = "He's gone. Right after he brought me here. I didn't want to use the hospitality from the courtesan you won, so I had Bartholomew to rent a room for me. He paid for it and disappeared without saying a word. Actually, wait, no, he did leave a letter for you though!";
			link.l1 = "A letter? From Bartholomew the Portuguese? This is something new. I don't like where this is going...";
			link.l1.go = "GoldenGirl_39";
		break;
		
		case "GoldenGirl_39":
			dialog.text = "Right, I will leave you to read it here while I go and say hello to the boys. They must be worrying. I never thought I would ever miss those gloomy faces! In the meantime try not to get yourself into another mess!";
			link.l1 = "Damn it... I still can't believe I've brought you back!";
			link.l1.go = "GoldenGirl_40";
		break;
		
		case "GoldenGirl_40":
			DialogExit();
			npchar.dialog.currentnode = "Helena_officer";
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "GoldenGirl_SPGirlReturn", 10.0);
		break;
		
		// Jason „олго и счастливо
		case "LongHappy":
			RemoveItems(pchar, "potionwine", 2);
			dialog.text = "The beatch, you, me, and good wine - Charles, it is so romantic! We should often have a walk like this together, alright!";
			link.l1 = "Glad you like it. I think we will have more time for this since now and generally for each other.";
			link.l1.go = "LongHappy_1";
		break;
		
		case "LongHappy_1":
			dialog.text = "Charles, what are you up to and why are you on your knees? Isn't it...";
			link.l1 = "Helen, I love you. And I want to live with you every day that is alloted to me from above. Therefore, here and now, in front of this sea and sky, I ask you - Helen Beatrice Sharp -  to give me the honor to stand with me before people and God until death do us part. I, Charles de Maure, chevalier de Monper, ask you - will you become my wife?";
			link.l1.go = "LongHappy_2";
		break;
		
		case "LongHappy_2":
			if (pchar.location == "Shore_ship1")
			{
				dialog.text = "You know, I never liked these formalities, but I'm with you till the end of the line. And as for your question, the answer is... oh, sorry!";
				link.l1 = "Nevermind, this is just wine and I never loved this shirt...";
				link.l1.go = "LongHappy_3";
			}
			else
			{
				dialog.text = "Charles, of course yes! Yes, yes, and one more yes!!! ButЙI do hope we will not go to a dusty family castle to grow turnips until the end of our days?";
				link.l1 = "Well, there will be a castle and it is quite dusty, but we won't stay there. Our life is freedom and the horizon at the rate. And with you I would like to live forever!";
				link.l1.go = "LongHappy_4";
			}
		break;
		
		case "LongHappy_3":
			DialogExit();
			chrDisableReloadToLocation = true;//закрыть локацию
			DoQuestCheckDelay("Helena_LoveSex", 1.0);
			npchar.dialog.currentnode = "LongHappy_5";
			LAi_SetStayType(npchar);
		break;
		
		case "LongHappy_4":
			dialog.text = "Than drink to you, my captain, my husband, and to my wedding!";
			link.l1 = "To you, my love! And to our future together, there's so much waiting us further!";
			link.l1.go = "LongHappy_6";
		break;
		
		case "LongHappy_5":
			dialog.text = "Than drink to you, my captain, my husband, and to my wedding!";
			link.l1 = "To you, my love! And to our future together, there's so much waiting us further!";
			link.l1.go = "LongHappy_6";
		break;
		
		case "LongHappy_6":
			DialogExit();
			chrDisableReloadToLocation = false;
			npchar.dialog.currentnode = "Helena_officer";
			LongHappy_MarryToSenPierre();
		break;
		
		case "LongHappy_7":
			dialog.text = "So, Abbot Benoit returned to his church and is ready to marry us. But I won't wear a dress even for such an occasion! Do you think it will be another sensation around local elite?";
			link.l1 = "Helen, I love you in any outfit, and they have to accept it, not the first time. But, I just wanted to consult with you about the guests and the ceremony.";
			link.l1.go = "LongHappy_8";
		break;
		
		case "LongHappy_8":
			dialog.text = "Yup, there's one problem - most of those, with whom we would gladly share this day, won't be allowed to enter even this city, I'm not talking about a church. Therefore - let's get married here with all the important people, as expected, and then we'll sail to Isla Tessoro and properly celebrate with real friends, what do you think?";
			link.l1 = "Sounds nice! So let's do it. I'll talk to Abbot Benoit, but we need to send out invitations and more...";
			link.l1.go = "LongHappy_9";
		break;
		
		case "LongHappy_9":
			dialog.text = "Calm down, captain. Your future wife will pick up part of your burden! I will arrange everything on Isla Tessoro and write to our friends, just tell me: how do you see this wedding?";
			link.l1 = "My ideal is you, me and our closest friends. After all the official faces here in Martinique, we will want some sincerity.";
			link.l1.go = "LongHappy_10";
			link.l2 = "We must remember this day. Call everyone! No one will be left out!";
			link.l2.go = "LongHappy_11";
		break;
		
		case "LongHappy_10":
			pchar.questTemp.LongHappy.SmallMarry = "true";
			dialog.text = "Cozy and friendly - you read my mind! We will have to visit Sharptown, and I will prepare everything. I already wondered - I think fifty barrels of rum and a couple of dozen barrels of wine will be enough. Also, for food and entertainment we will need three hundred thousand pesos.";
			link.l1 = "Remind me - why don't you manage all the ship finances? I'll get it all. Just gonna drop by the abbot and we set sail for Sharptown.";
			link.l1.go = "LongHappy_12";
		break;
		
		case "LongHappy_11":
			pchar.questTemp.LongHappy.BigMarry = "true";
			dialog.text = "So, want to have fun like a real sea wolves - we will do it! We will have visit Sharptown, and I will prepare everything. But we have to seriously stock up - I think a hundred barrels of rum and fifty barrels of wine will be enough. And other expenses will take at least five hundred thousand pesos.";
			link.l1 = "Well, I didnХt mean the whole Brethren of the Coast... But, you know - come on, do it! I will get supplies. Just gonnad drop by the abbot and we set sail for Sharptown.";
			link.l1.go = "LongHappy_12";
		break;
		
		case "LongHappy_12":
			DialogExit();
			npchar.dialog.currentnode = "Helena_officer";
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "LongHappy_GirlNorm", 5.0);
			AddQuestRecord("LongHappy", "10");
			AddQuestUserData("LongHappy", "sName", "Helen");
			LongHappy_MarryGoToBenua();
		break;
		
		case "LongHappy_13":
			dialog.text = "Charles, I'll deal with the loading, and then I'll hand the the invitations to the baron and come to agree with the tavern. Is that enough of time for you to get bored?";
			link.l1 = "I guess, I'll find what to do! Or just have a rest on the sand... I didn't think that it would be easier to prepare for the assault of Tortuga than for the wedding.";
			link.l1.go = "LongHappy_14";
		break;
		
		case "LongHappy_14":
			DialogExit();
			SetLaunchFrameFormParam("Several hours have passed...", "", 0.1, 3.0);
			LaunchFrameForm();
			WaitDate("", 0, 0, 0, 4, 0);
			LongHappy_IslaTesoroRemoveGoods();
			npchar.dialog.currentnode = "LongHappy_15";
			LAi_SetActorType(npchar);
			LAi_ActorDialogDelay(npchar, pchar, "", 4.0);
		break;
		
		case "LongHappy_15":
			dialog.text = "Did you get some rest, Charles? Imagine, the local guys had fun so much a week ago and, by accident, burned the 'Old Woodpecker', but the baron promised that by our arrival it would be rebuilt more and better than it was. I agreed on the rest, so you can set sail.";
			link.l1 = "I hope our wedding won't leave more couple of ashes here. Oh, but I liked the local hangout - cozy, entourage! Oh well, honey, you're right - time doesn't wait.";
			link.l1.go = "LongHappy_16";
		break;
		
		case "LongHappy_16":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "LongHappy_GirlNorm", 5.0);
			AddQuestRecord("LongHappy", "12");
			pchar.questTemp.LongHappy = "marry_wait";
			pchar.questTemp.LongHappy.DrinkReady = "true";
		break;
		
		case "LongHappy_17":
			dialog.text = "Jan is already in town, with him Gladys, can you imagine? I didn't think that these old would ever celebrate at my wedding! Oh, thunder and lightning! In that nightmarish Indian temple-city, I was not so... scared.";
			link.l1 = "All is fine, honey, all is fine. I'm worried too - that's normal. Since the guests have already come, I should go to father Benoit and find out when the service will begin.";
			link.l1.go = "LongHappy_18";
		break;
		
		case "LongHappy_18":
			dialog.text = "I feel it will be a damn long and difficult day. Okay, you should go, Charles, and I'm going to see Jan and Gladys.";
			link.l1 = "I'm glad they were able to come. Old man Svensson loves you as his own daughter, and madame McArthur even more. It's good that they will be here today. Go and don't worry - everything will be fine.";
			link.l1.go = "LongHappy_19";
		break;
		
		case "LongHappy_19":
			DialogExit();
			pchar.GenQuest.CannotWait = true;//запрет ожиданиЯ
			LAi_ActorRunToLocation(npchar, "reload", "reload4_back", "none", "", "", "OpenTheDoors", 5.0);
			AddQuestRecord("LongHappy", "14");
			AddQuestUserData("LongHappy", "sName", "Helen");
		break;
		
		case "LongHappy_20":
			dialog.text = "Yes.";
			link.l1 = "";
			link.l1.go = "LongHappy_21";
		break;
		
		case "LongHappy_21":
			DialogExit();
			sld = characterFromId("Benua");
			sld.dialog.currentnode = "LH_abbat_27";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "LongHappy_22":
			dialog.text = "Yes.";
			link.l1 = "";
			link.l1.go = "LongHappy_23";
		break;
		
		case "LongHappy_23":
			DialogExit();
			sld = characterFromId("Benua");
			sld.dialog.currentnode = "LH_abbat_29";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "LongHappy_24":
			dialog.text = "Yes.";
			link.l1 = "";
			link.l1.go = "LongHappy_25";
		break;
		
		case "LongHappy_25":
			DialogExit();
			sld = characterFromId("Benua");
			sld.dialog.currentnode = "LH_abbat_31";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "LongHappy_26":
			dialog.text = "";
			link.l1 = "I, Charles Henry de Maure, chevalier de Monper, take you, Helen Beatrice Sharp, to be my wife, to have and to hold, from this day forward, for better and for worse, for richer and for poorer, in sickness and in health, until death do us apart. According to God's Holy Law, in the presence of God, I make this vow.";
			link.l1.go = "LongHappy_27";
		break;
		
		case "LongHappy_27":
			dialog.text = "I, Helen Beatrice Sharp, take you, Charles Henry de Maure, to be my husband, to have and to hold, from this day forward, for better and for worse, for richer and for poorer, in sickness and in health, until death do us apart. According to God's Holy Law, in the presence of God, I make this vow.";
			link.l1 = "";
			link.l1.go = "LongHappy_28";
		break;
		
		case "LongHappy_28":
			DialogExit();
			sld = characterFromId("Benua");
			sld.dialog.currentnode = "LH_abbat_33";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "LongHappy_29":
			dialog.text = "Amen.";
			link.l1 = "";
			link.l1.go = "LongHappy_30";
		break;
		
		case "LongHappy_30":
			DialogExit();
			sld = characterFromId("Benua");
			sld.dialog.currentnode = "LH_abbat_35";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "LongHappy_31":
			dialog.text = "Helen Beatrice de Maure, madame de Monper - sounds good, yes, my husband?";
			link.l1 = "Haven't heard anything better, my wife!";
			link.l1.go = "LongHappy_32";
		break;
		
		case "LongHappy_32":
			dialog.text = "You know - I thought, that this would not change anything, and probably it didn't - I loved you before and wanted to live with you the rest of the days, but this day, this service... I am happy, Charles! Happy as never before, and look at Gladys and Jan - they are shining! There are so many happy faces around! By the way - it's time for you to walk around the guests and accept congratulations. Come back when you finish, don't forget - we are being waited in Sharptown.";
			link.l1 = "I'll do it right away, sweetheart. One kiss and I go!";
			link.l1.go = "LongHappy_33";
		break;
		
		case "LongHappy_33":
			DialogExit();
			LongHappy_MarryKiss();
		break;
		
		case "LongHappy_34":
			dialog.text = "Oh, my husband, have you already talked to the guests?";
			link.l1 = "Not yet, be patient, sweetheart, I'll back soon.";
			link.l1.go = "LongHappy_34_1";
			link.l2 = "Yes, I've never listened to so many congratulations at once. And you know what - most of them spoke sincerely!";
			link.l2.go = "LongHappy_35";
		break;
		
		case "LongHappy_34_1":
			DialogExit();
			npchar.dialog.currentnode = "LongHappy_34";
		break;
		
		case "LongHappy_35":
			dialog.text = "Yes, this elite is surprisingly sincere - to admit, I expected more falsehood and hypocrisy. Or I'm just so happy that I don't notice anything. But after all, our friends are waiting for us in Sharptown! When do we sail?";
			link.l1 = "Right now. We'll fly like on wings and right to a friendly feast. I hope my wife, you don't mind of spending this night in our cabin?";
			link.l1.go = "LongHappy_36";
		break;
		
		case "LongHappy_36":
			dialog.text = "Oh yes, my husband, you know a lot about romance! And don't twitch like that, now I have the right to kiss you in public... Okay, we can go now!";
			link.l1 = "The main thing is not to forget to order to set sail for Sharptown...";
			link.l1.go = "LongHappy_37";
		break;
		
		case "LongHappy_37":
			DialogExit();
			npchar.dialog.currentnode = "LongHappy_38";
			LongHappy_MarryComplete();
		break;
		
		case "LongHappy_38":
			dialog.text = "Oh my dear, I'm so happy! Today is a wonderful day...";
			link.l1 = "";
			link.l1.go = "LongHappy_38_1";
		break;
		
		case "LongHappy_38_1":
			DialogExit();
			npchar.dialog.currentnode = "LongHappy_38";
		break;
		
		case "LongHappy_39":
			dialog.text = "Come on Charles. This liar will not hit even the wall!";
			link.l1 = "";
			link.l1.go = "LongHappy_40";
		break;
		
		case "LongHappy_40":
			DialogExit();
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.Angerran")) // fix 02-04-20
			{
				sld = characterFromId("Angerran");
				sld.dialog.currentnode = "Shivo_6";
			}
			else 
			{
				sld = characterFromId("LH_Dussak");
				sld.dialog.currentnode = "Dussak_5";
			}
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;
		
		case "LongHappy_41":
			dialog.text = "I'm fine, Charles, it's okay. How is Nathan?";
			link.l1 = "So much blood... Dannie, is he breathing? I see him breathing!";
			link.l1.go = "LongHappy_42";
		break;
		
		case "LongHappy_42":
			DialogExit();
			sld = characterFromId("Danielle");
			sld.dialog.currentnode = "Danielle_9";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;
		
		case "LongHappy_43":
			dialog.text = "Faster, dear, do not waste time!";
			link.l1 = "";
			link.l1.go = "LongHappy_43_1";
		break;
		
		case "LongHappy_43_1":
			DialogExit();
			npchar.dialog.currentnode = "LongHappy_43";
		break;
		
		case "LongHappy_44":
			dialog.text = "Charles, are you okay? Such a bloodbathЙ Sorry, we were stuck upstairs, there was a dozen of these bastards, so we had to deal with them!";
			link.l1 = "It's fine, I handled it. I'm happy I was able to finish that story with Jacques... finally. He's got what he deserved.";
			link.l1.go = "LongHappy_45";
		break;
		
		case "LongHappy_45":
			dialog.text = "Fine, my dear, let's finish here and get back. I can't stop thinking about Nathan, how is he? He covered me from that bullet.";
			link.l1 = "You're right, sweet, I worry too. Go, I'm right behind you.";
			if (CheckAttribute(pchar, "questTemp.LongHappy.Terrax.Prisoner")) link.l1.go = "LongHappy_46";
			else link.l1.go = "LongHappy_48";
		break;
		
		case "LongHappy_46":
			dialog.text = "By the way, we found Marcus. He was in the cargo hold, bound and unconscious.";
			link.l1 = "He's alive?";
			link.l1.go = "LongHappy_47";
		break;
		
		case "LongHappy_47":
			dialog.text = "Don't worry, love, baron Tyrax will live even longer than us. He's just woken up and is already buzzing, he requires a saber and the bridge.";
			link.l1 = "That's our old Marcus! Let hem rest a bit while we finish here and then go back to the shore.";
			link.l1.go = "LongHappy_48";
		break;
		
		case "LongHappy_48":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "LongHappy_BarbExit", -1);
		break;
		
		case "LongHappy_49":
			if (CheckAttribute(pchar, "questTemp.LongHappy.Tichingitu_died") && CheckAttribute(pchar, "questTemp.LongHappy.Jino_died"))
			{
				dialog.text = "I'm so sorry, love. First, our faithful friend Tichingitu, then Gino... Barbason should've been killed a dozen times for all he'd done!";
				link.l1 = "Alas I did it just once. I feel bad too... But we won, and the Kindman won't hurt anyone once again.";
				link.l1.go = "LongHappy_50";
			}
			else
			{
				if (CheckAttribute(pchar, "questTemp.LongHappy.Jino_died"))
				{
					dialog.text = "I feel so bad about Gino, Charles! When I found out, I didnХt believe it! How are you, love?";
					link.l1 = "I can't believe it too... it turned out so stupid, I didn't imagine this day like that.";
				}
				else
				{
					dialog.text = "Interesting, will chroniclers write about the battle ne Privatir Bay, what do you think? Barons of the Brethren of the Coast met in open battle - the Spanish authorities are wiping away a tear of tenderness! But, we won again! Friends are alive, and enemies are dead - a glorious wedding gift!";
					link.l1 = "Yeah, such a celebration, but we made it, my love. We made it.";
				}
				link.l1.go = "LongHappy_50";
			}
		break;
		
		case "LongHappy_50":
			dialog.text = "We shoul drink after all of this. Come on, Dannie found us a house here on the outskirts, I donХt want to return to the ship now. We'll sit and drink to those who didn't make it.";
			link.l1 = "Yes, Helen, let's go.";
			link.l1.go = "LongHappy_51";
		break;
		
		case "LongHappy_51":
			DialogExit();
			LongHappy_LogBook();
			DoQuestCheckDelay("LongHappy_MarryFinalizing", 0.5);
		break;
		
		case "LongHappy_52":
			if (CheckAttribute(pchar, "questTemp.LongHappy.Jino_died"))
			{
				dialog.text = "I feel so bad about Gino, Charles, alright! When I found out, I didnХt believe it! How are you?";
				link.l1 = "I can't believe it too... it turned out so stupid, I didn't imagine this day like that.";
			}
			else
			{
				dialog.text = "Have you seen Hawk, or Dannie didn't let you come in? She put me out when Gino said 'the danger is over'. I'm glad that everything is fine now. Friends are alive, and enemies are dead - a glorious wedding gift!";
				link.l1 = "Me too, darling. And we won. Barbason is dead, barons are gathering what's left of their crews. The fight is over.";
			}
			link.l1.go = "LongHappy_53";
		break;
		
		case "LongHappy_53":
			dialog.text = "Charles, I see you barely standing on your feet, but I visited the tavern and you won't believe what I listened to from local bartender.";
			link.l1 = "Yup, I heard it from Jan, he's been there too. It seems to me that our harsh maskogue went on the razzle-dazzle. LetХs take a walk to Sabo-Matila Cove, a few people saw him leaving in that direction.";
			link.l1.go = "LongHappy_54";
		break;
		
		case "LongHappy_54":
			DialogExit();
			LongHappy_LogBook();
			chrDisableReloadToLocation = false;
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			pchar.quest.longhappy_shoregirl.win_condition.l1 = "location";
			pchar.quest.longhappy_shoregirl.win_condition.l1.location = "Shore_ship1";
			pchar.quest.longhappy_shoregirl.function = "LongHappy_SetShoreGirl";
		break;
		
		case "LongHappy_55":
			dialog.text = "Tichingitu, that's the spirit! I was laughing my ass off! Why does such a nice custom not in use now, ha? Okay - you're already sleepingo, my love. Come on, Dannie found for us a house here on the outskirts - you need to have a rest.";
			link.l1 = "Lead ... I think I fell asleep on that beach before.";
			link.l1.go = "LongHappy_56";
		break;
		
		case "LongHappy_56":
			DialogExit();
			DoQuestCheckDelay("LongHappy_MarryFinalizing", 0.5);
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
	}
}