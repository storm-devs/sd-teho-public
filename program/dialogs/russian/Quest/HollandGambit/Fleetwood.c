// Ричард Флитвуд - английский капитан
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (CheckAttribute(pchar, "questTemp.HWIC.Eng"))
			{
				if (pchar.questTemp.HWIC.Eng == "Start_main")
				{
					dialog.text = "Greetings, captain! Don't get distracted by my looks, I am fine, almost blind, but I am fine. Let me introduce myself, I am Richard Fleetwood.";
					link.l1 = "Good day. And I am captain " + GetFullName(pchar) + ".";
					link.l1.go = "First_Task";
					break;
				}
				if (pchar.questTemp.HWIC.Eng == "GotoPortoffice")
				{
					if (sti(Pchar.Ship.Type) != SHIP_NOTUSED)
					{
						dialog.text = "I have asked you to moor your ship. Do you even listen to me?";
						link.l1 = "Yes, yes, I got it, I am on my way.";
						link.l1.go = "exit";
					}
					else
					{
						dialog.text = "So, you are here again. Take command of the 'Valkyrie' - my crew is warned about details - and sail to Bridgetown. Visit every person of interest in the city and spread the gossips we talked about. Then be ready for the bastard to attack. Don't change the vessel and don't make a squadron, he will suspect a trap otherwise and won't show up\nYou must board his ship and deliver her to St. John's, find the pirate's logbook, the only evidence we will ever have of Lucas Rodenburg's involvement. I am sure that you will handle this. Godspeed, captain.";
						link.l1 = "Gratitude! I will do the job according to our plan.";
						link.l1.go = "First_Task_3";
					}
					break;
				}
				if (pchar.questTemp.HWIC.Eng == "MirageTake")//а вот теперь начинается перебор кораблей
				{
					pchar.quest.ToAntiguaMirageOver.over = "yes"; //снять таймер
					int iMir = 0;
					int iVal = 0;
					for(i = 0; i < COMPANION_MAX; i++)
					{
						iTemp = GetCompanionIndex(PChar, i);
						if(iTemp > 0)
						{
							sld = GetCharacter(iTemp);
							pchar.questTemp.HWIC.Eng.CompanionIndex = sld.Index;
							if(sti(RealShips[sti(sld.ship.type)].basetype) == SHIP_MIRAGE)
							{
							iMir = 1;
							RealShips[sti(sld.Ship.Type)].ship.upgrades.hull = 1;//чистый корпус
							SetShipSailsFromFile(sld, "ships/parus_silk.tga");
							SetSailsColor(sld, 0);//белый хлопковый парус
							DeleteAttribute(sld, "ship.sails");//починить паруса
							DeleteAttribute(sld, "ship.masts");//вернуть мачты
							}
							if(sti(RealShips[sti(sld.ship.type)].basetype) == SHIP_VALCIRIA) iVal = 1;
						}
					}//установили признак наличия кораблей в эскадре.
					if (iMir == 1 && iVal == 0)//потеряли Валькирию
					{
						dialog.text = "You are back, captain... I already know everything about your voyage.";
						link.l1 = "Do you? So you must know that...";
						link.l1.go = "Fleetwood_lostVal";
						break;
					}
					if (iMir == 0 && iVal == 1)//потеряли Мираж
					{
						dialog.text = "You are back, captain... I already know everything about your voyage.";
						link.l1 = "Do you? So you must know that...";
						link.l1.go = "Fleetwood_lostMir";
						break;
					}
					if (iMir == 0 && iVal == 0)//а это вообще плохо
					{
						dialog.text = "You are back, captain... I already know everything about your voyage.";
						link.l1 = "Do you? So you must know that...";
						link.l1.go = "Fleetwood_lostFull";
						break;
					}
						dialog.text = "You are back, captain... I already know everything about your voyage.";
						link.l1 = "Do you? So you must know that...";
					link.l1.go = "Fleetwood_complete";
					break;
				}
				if (pchar.questTemp.HWIC.Eng == "toAntigua")
				{
					dialog.text = "Greetings, my friend! Glad to see you! Do you have Abigail on you ship?";
					link.l1 = "Unfortunately, I don't, Richard. She refused to go with me, because her departure would be a heavy blow to her father who has already lost every single coin. I have decided to deal with the problem and to find Solomon's money and that island...";
					link.l1.go = "Fleetwood_LastTask";
					break;
				}
				dialog.text = "Anything else, captain?";
				link.l1 = "No, I am leaving already.";
				link.l1.go = "exit";		
				NextDiag.TempNode = "First time";
			}
				dialog.text = "Anything else, captain?";
				link.l1 = "No, I am leaving, already.";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "Fleetwood_abordage":
			PlaySound("VOICE\Russian\hambit\Richard Flitwood-03.wav");
			dialog.text = "Damn pirate! You have won the boarding fight, but I will fulfil my duty anyway. I have fired ginpowder room and soon my vessel will explode and so will your 'ghost ship'. You won't sink a single English ship anymore. I will die with honour!";
			link.l1 = "Actually, you are wrong, Fleetwood. There are no pirates on my ship, I have dealt with them before. I needed you and this ship served as a nice trap. Enough of words, I still have to kill you and get away from your flaming tub!";
			link.l1.go = "Fleetwood_abordage_1";
		break;
		
		case "Fleetwood_abordage_1":
			LAi_SetCurHPMax(NPChar);
			LAi_GetCharacterMaxEnergy(NPChar);			
			QuestAboardCabinDialogExitWithBattle("PrepareToBoom"); 
			DialogExit();	
			AddDialogExitQuest("MainHeroFightModeOn");
			pchar.questTemp.HWIC.Holl = "FleetwoodCapture";
			pchar.GenQuest.Detonation = true; // patch-4
		break;
		
		case "First_Task":
			dialog.text = "Charlie told me about you. About you and your successful interception of the enemy's trade caravan. I am glad to meet you, England needs such brave captains. Now, let me tell you something of great importance.";
			link.l1 = "I am listening, mister Fleetwood.";
			link.l1.go = "First_Task_1";			
		break;
		
		case "First_Task_1":
			dialog.text = "One pirate commits acts of violence throughout the archipelago. He pretends to be the 'Flying Dutchman', a legendary ghost ship. I am sure that he is a Dutchman, but he cannot fly. I tend to believe that this is a mercenary of Lucas Rodenburg, a vice-director of Dutch West India Company\nRodenburg has declared a shadow trade war against England - this 'ghost ship' attacks only trading vessel under English flag. It is vital for the company to weaken our influence in this area without fighting a real war\nI've been hunting this ghost ship for a while, but her captain is a very experienced sailor and his ship is swift and shifty\nSince it's impossible to catch the jackal in the open fight, then we should act cunningly and the recent attempt on my life will do us a great favour. How do you feel about it, captain? Scared?";
			link.l1 = "Not a chance. I am ready to help you to find and destroy this bastard. You are going to ask me to do that, am I right?";
			link.l1.go = "First_Task_2";	
		break;
		
		case "First_Task_2":
			dialog.text = "You are correct. Now, let's discuss details. My men will spread the rumors that I am almost dead and sold my ship the 'Valkyrie' to you. Next, we will move on with our little deception. You will pretend to be a merchant who bought the brig from me and got rid of most cannons\nTherefore, your task is to sail to Barbados and to tell everyone there that your holds are filled with valuable cargo and your pockets are filled with coins. Tell them that you are going to set sail soon. Play a role of a greedy, simple yet rich merchant\nOur damn pirate gets information about trading ship from Bridgetown, but it is unknown who exactly supplies him with it. Everyone is under suspicion - from a local merchant to a governor, though the last possibility is quite terrifying\nTake command of my 'Valkyrie' and her crew\nBut first, you should leave all your ships here, I have already spoken to the local harbour master, it will cost 10 000 pesos per month for your flagship\nOnce it's done, return to me and I will make arrangements. Ah, captain, don't forget to take your cut for capturing the silver caravan and ten thousands for harbour master, the money in in the chest of drawers.";
			link.l1 = "I got it, mister Fleetwood. I am going to see the harbour master.";
			link.l1.go = "exit";	
			pchar.questTemp.HWIC.Eng = "GotoPortoffice";
			bDisableFastReload = false;//откроем быстрый переход
			DeleteAttribute(pchar, "questTemp.HWIC.CanTake");//иные варианты более невозможны
		break;
		
		case "First_Task_3":
			DialogExit();
			pchar.questTemp.HWIC.TakeQuestShip = "true";//все ПУ недоступны для стоянки до поры, также корабль нельзя продать
			pchar.questTemp.HWIC.EngEquip = "true"; //форма солдат
			pchar.questTemp.HWIC.Eng = "GotoBridgetown";
			GetValckiriaToCharacter(pchar);
			pchar.quest.Knippel_Officer.win_condition.l1 = "location";
			pchar.quest.Knippel_Officer.win_condition.l1.location = "SentJons_houseSP3";
			pchar.quest.Knippel_Officer.function = "KnippelToOfficer";
			pchar.questTemp.HWIC.Eng.BridgeCounter = 0;//счетчик посещений неписей Бриджтауна по квесту
			AddQuestRecord("Holl_Gambit", "2-5");
		break;
		
		//изымаем корабль
		case "Fleetwood_lostMir":
			dialog.text = "Yes, I am aware that you have failed your mission to capture the pirate vessel. All my plans are ruined. I am taking away 'Valkyrie' from you. You can go now, I don't need your services.";
			link.l1 = "I am so sorry for that. Farewell, mister Fleetwood.";
			link.l1.go = "Fleetwood_RemoveShip";
			pchar.questTemp.HWIC.Eng.ShipType = SHIP_VALCIRIA;
		break;
		
		case "Fleetwood_lostVal":
			dialog.text = "Yes, I am aware that you have lost 'Valkyrie'. It was the most unacceptable... I am going to take away the captured pirate vessel. You can go now, I don't need your services.";
			link.l1 = "I am so sorry for that. Farewell, mister Fleetwood.";
			link.l1.go = "Fleetwood_RemoveShip";
			pchar.questTemp.HWIC.Eng.ShipType = SHIP_MIRAGE;
		break;
		
		case "Fleetwood_lostFull":
			dialog.text = "Yes, I am aware that you are a rare muddler and bungler. You didn't capture the pirate vessel and lost my 'Valkyrie'. I am really disappointed at you. Get out!";
			link.l1 = "I am so sorry for that. Farewell, mister Fleetwood.";
			link.l1.go = "exit";
			Pchar.questTemp.FiringOfficerIDX = GetCharacterIndex("Knippel");
			AddDialogExitQuestFunction("LandEnc_OfficerFired");//Книппеля из офицеров
			sld = characterFromId("Knippel");
			ChangeCharacterAddressGroup(sld, "SentJons_houseH1", "goto", "goto1");//Книппеля домой
			pchar.questTemp.HWIC.Eng = "end";
			CloseQuestHeader("Holl_Gambit");
			DeleteAttribute(pchar, "questTemp.HWIC.TakeQuestShip");//ПУ откроем
			DeleteAttribute(pchar, "questTemp.HWIC.EngEquip");
			pchar.questTemp.HWIC.Detector = "eng_fail";
			AddSimpleRumourCity("They say that you have failed some secret assignment of Richard Fleetwood. Well, you have got nothing to do on Antigua now...", "SentJons", 20, 3, "");
		break;
		
		case "Fleetwood_RemoveShip":
			DialogExit();
			AddDialogExitQuestFunction("Fleetwood_RemoveShip");
			pchar.questTemp.HWIC.Eng = "end";
			CloseQuestHeader("Holl_Gambit");
			DeleteAttribute(pchar, "questTemp.HWIC.TakeQuestShip");//ПУ откроем
			DeleteAttribute(pchar, "questTemp.HWIC.EngEquip");
			pchar.questTemp.HWIC.Detector = "eng_fail";
			AddSimpleRumourCity("They say that you have failed some secret assignment of Richard Fleetwood. Well, you have got nothing to do on Antigua now...", "SentJons", 20, 3, "");
		break;
		
		case "Fleetwood_complete":
			pchar.questTemp.HWIC.Eng.ShipType = SHIP_VALCIRIA;
			AddDialogExitQuestFunction("Fleetwood_RemoveShip");	
			if (CheckCharacterItem(pchar, "JacobJournal"))//проверяем журнал
			{
				dialog.text = "Yes, I am aware that you have succeeded in our plan. You have eliminated the insolent pirate and captured his ship. By the way, what is the real name of her?";
				link.l1 = "Mirage.";
				link.l1.go = "Abigile";
			}
			else//нет журнала - нет продолжения квеста
			{
				dialog.text = "Yes, I am aware that you have succeeded in our plan. You have eliminated the insolent pirate and captured his ship. I am going to take my 'Valkyrie' from you and you can keep the pirate vessel as a prize... she will also serve as some sort of a compensation, there was a fire in the docks and you ship got burned. I am sorry, " + pchar.name + "... I hope the ghost ship will serve you better\nI have ordered to clean your new vessel from that masquerade dirt and seaweeds. They will also dress your beauty in new sails of best cotton\nFinally, accept your reward - 100 000 pesos and this navigation tool, I always wanted to present it to a worthy sailor... You did a good job out there and I am proud of you! Well, the time has come to say farewells, I have done my business here, I should return to Europe. Good fortune to you, captain!";
				link.l1 = "Same to you, Richard!";
				link.l1.go = "exit";
				LocatorReloadEnterDisable("SentJons_houseSP3", "reload2", true);//закроем Флитвуда в комнате и пусть там сидит
				pchar.questTemp.HWIC.Eng = "end";
				pchar.questTemp.HWIC.Detector = "eng_win_half";
				CloseQuestHeader("Holl_Gambit");
			}
			AddMoneyToCharacter(pchar, 100000);
			GiveItem2Character(pchar, "bussol");
			DeleteAttribute(pchar, "questTemp.HWIC.TakeQuestShip");//ПУ откроем
			DeleteAttribute(pchar, "questTemp.HWIC.EngEquip");
			AddSimpleRumourCity("They say that you and Richard Fleetwood has planned some military operation and you have personally destroyed that elusive pirate who has been robbing our trade ships. You are a real hero, captain!", "SentJons", 20, 3, "");
		break;
		
		case "Abigile":
			dialog.text = "Mirage? A very suitable name, I say... I am going to take my 'Valkyrie' from you and you can keep the pirate vessel as a prize... she will also serve as some sort of a compensation, there was a fire in docks and you ship got burned. I am sorry, " + pchar.name + "... I hope the  ghost ship will serve you better\nI have ordered to clean your new vessel from that masquerade dirt and seaweeds. They will also dress your beauty in new sails of best cotton\nFinally, accept your reward - 100 000 pesos and this navigation tool, I always wanted to present it to a worthy sailor... You did a good job out there and I am proud of you! Do you have the bastard's logbook?";
			link.l1 = "Yes, sure. Here, take it. And I want to ask you something, is there any... Asian among the Lucas Rodenburg's hirelings?";
			link.l1.go = "Abigile_1";			
		break;
		
		case "Abigile_1":
			RemoveItems(PChar, "JacobJournal", 1);
			dialog.text = "There is. Chinese Longway, a captain of his private ship 'Meifeng'. Did you read that from the pirate's log? Let me see it...(reading) Well, well. As I have expected Lucas Rodenburg was behind all of that! Well, whatever, it is not our concern now... Our governor-general will deal with this bastard. Lucas Rodenburg will have to answer for all he has done!";
			link.l1 = "Hm. Interesting, and how the English governor-general will be able to 'deal' with a subject of Holland?";
			link.l1.go = "Abigile_2";			
		break;
		
		case "Abigile_2":
			dialog.text = "There are always political strings to pull, my dear friend... Holland will have to admit that it was them who started a trade war against England. But it's unlikely that they will, they will blame Rodenburg for everything. Lucas might lose his position, or not. Anyway, his career will suffer a heavy blow\nNevermind, it's not our business now, captain. You did your part of the job and you did it well. That is I why I have another very delicate matter for you.";
			link.l1 = "I am listening, Richard. Who will be the next enemy of English crown to be destroyed this time?";
			link.l1.go = "Abigile_3";			
		break;
		
		case "Abigile_3":
			dialog.text = "No, I want to ask you to deal with more personal and peaceful matter this time. Let me tell you a short story which concerns by the way your 'Mirage'.";
			link.l1 = "I am listening.";
			link.l1.go = "Abigile_4";			
		break;
		
		case "Abigile_4":
			dialog.text = "I was on a raid, hunting the ghost ship a month before you and I met. It was South of Martinique, not far from longitude 64 dg. 41'. We heard a fight going on somewhere in a distance, but the wind was too weak, so we didn't make it in time. An English flute was sunk by a ghost ship close to some small island which isn't even put on the map\nI failed to catch the pirate and decided to visit that island, hoping to find any survivors. And I found them. A couple of Jewish refugees, father and daughter. The girl was called Abigail and she was beautiful! A living miracle... I took them aboard and delivered them to Curacao, though her father, Solomon, didn't show much sympathy to me\nAs far as I understood, he thought that I was the pirate who sunk their vessel, old man don't know much about ships and the differences between them. During that little voyage me and Abigail became friends, or, to be completely honest, fell in love to each other. Isn't that a story?\nAnd I've recently found out that bastard Rodenburg has been courting my Abigail for a while, just think about it! I was going to take her here, once I solve the matter concerning her dad's lost money, he stashed every single coin he had on that island, I mentioned. I failed to find its location. We cannot wait any longer\nSince my health still doesn't allow me to set sail myself, I am asking you to go to Willemstad, find Abigail and bring her here. Mention my name and she will trust you.";
			link.l1 = "Don't see any problems in this matter. I am ready to set sail now.";
			link.l1.go = "Abigile_5";			
		break;
		
		case "Abigile_5":
			PlaySound("VOICE\Russian\hambit\Richard Flitwood-02.wav");
			dialog.text = "Excellent! I am glad that I can count on you, " + pchar.name + ". Your work will be paid well, don't worry about that.";
			link.l1 = "I won't make you wait for too long. See you soon, Richard!";
			link.l1.go = "Abigile_6";			
		break;
		
		case "Abigile_6":
			DialogExit();
			npchar.greeting = "fleetwood_2";
			LocatorReloadEnterDisable("Villemstad_town", "houseSP2", false);//откроем дом Аби
			LocatorReloadEnterDisable("Villemstad_houseSp2", "reload2", true);//закроем спальню Аби
			AddQuestRecord("Holl_Gambit", "2-16");
			pchar.questTemp.HWIC.Eng = "toAbigile";
			sld = characterFromId("Bridgetown_tavernkeeper");
			sld.model = "barmen_3";
			sld.name = "Harry";
			sld.lastname = "Fletcher";//перерисуем бармена Бриджтауна
			sld.greeting = "barmen_1";
			sld = characterFromId("Solomon");
			sld.greeting = "solomon_2";
		break;
		
		case "Fleetwood_LastTask":
			dialog.text = "" + pchar.name + ", did you really decide to find the island? I am impressed with your generosity. Have you found it?";
			link.l1 = "Yes, I have. But unfortunately, this is where the bad news are coming. I barely escaped that damned place alive... I still tremble when I think about it...";
			link.l1.go = "Fleetwood_LastTask_1";
		break;
		
		case "Fleetwood_LastTask_1":
			dialog.text = "What has happened there? Tell me, my friend, don't keep me in suspense!";
			link.l1 = "I came to the island and headed to the grotto where Solomon had likely stashed his chest. It was really there. But when I touched it, some unknown power tossed me up. I heard an explosion and was thrown on the ground in ten feet from the chest...";
			link.l1.go = "Fleetwood_LastTask_2";
		break;
		
		case "Fleetwood_LastTask_2":
			dialog.text = "Incredible!";
			link.l1 = "I barely survived it - I got some painful damage. When I was coming to consciousness some creepy sounds happened and the awful creature appeared right from the ground... oh, God, that monster!";
			link.l1.go = "Fleetwood_LastTask_3";
		break;
		
		case "Fleetwood_LastTask_3":
			dialog.text = "" + pchar.name + "...";
			link.l1 = "Richard, I am not insane. It really happened though I hardly believe in this myself. It was completely dried-up and painted corpse of an Indian with a bunch of feathers on its head. This monster has rumbled something, then drew a huge Indian club and attacked me!";
			link.l1.go = "Fleetwood_LastTask_4";
		break;
		
		case "Fleetwood_LastTask_4":
			dialog.text = "";
			link.l1 = "Good Lord... I still don't get it how was I able to deal with that thing... I hit it so many times that it would be enough to kill a dozen men and it was still standing... After I had recovered my breath I opened that ill-fated chest and found there no money. But there was something inside instead. Take a look, a very intriguing item!";
			link.l1.go = "Fleetwood_LastTask_5";
		break;
		
		case "Fleetwood_LastTask_5":
			RemoveItems(PChar, "GastonHead", 1);
			dialog.text = "B-r-r... terrible..." + pchar.name + ", wait... sure it is him! It is a head of the bastard who had tried to kill me by blinding me with pepper!";
			link.l1 = "You know, who is he? Name's Gaston, Bridgetown's bartender and a helper of van Berg, a captain of the ghost ship. I have recognized him immediately. But I don't know who has killed him and how his cut head ended in the Solomon's chest on the unknown island!";
			link.l1.go = "Fleetwood_LastTask_6";
		break;
		
		case "Fleetwood_LastTask_6":
			dialog.text = "You are right, it is a really creepy and obscure story. Mystic...";
			link.l1 = "Exactly. There was no point in returning back to Abigail due to the money's absence. So I am here to tell you about it. Perhaps, you, Richard will understand something in this mess...";
			link.l1.go = "Fleetwood_LastTask_7";
		break;
		
		case "Fleetwood_LastTask_7":
			dialog.text = "Me? I don't get a thing here just like you... But I can tell you something for sure - I have a bad feeling about it..." + pchar.name + ", listen to me now. Go and check Bridgetown to be sure that... Gaston is gone for good. Then, I ask you to come to Blanca Lagoon of Curacao in 20 days. Charlie Knippel will be waiting for you there. I will collect money for Abigail's father. I will give it to Charlie, and you will take it to Solomon and deliver Abigail to Antigua. This time there will be no obstacles, you must understand that. Go, my friend!";
			link.l1 = "Fine, Richard. I am on my way.";
			link.l1.go = "Fleetwood_LastTask_8";
		break;
		
		case "Fleetwood_LastTask_8":
			DialogExit();
			pchar.questTemp.HWIC.Eng = "toBarbados";
			AddQuestRecord("Holl_Gambit", "2-21");
			SetFunctionTimerCondition("HWICEng_toBarbadosOver", 0, 0, 20, false);//чтобы не тянули
			AddSimpleRumourCity("Oh, captain, I have heard that Richard Fleetwood really admires you. Trust me, his praise costs a lot. You must be a very important person...", "SentJons", 20, 3, "");
		break;
		
//---------------------------------------------против всех-----------------------------------------------
		
		case "InTerksShore":
			pchar.quest.Fleetwood_ShoreOver.over = "yes";//снять таймер
			dialog.text = "I take it that you are the bastard who has kidnapped my Abigail. Charlie didn't return to me so it also must be you to be blamed.";
			link.l1 = "You are right, mister Fleetwood. It is me. Charlie has helped to worm me into Abigail's confidence thanks to the letter you wrote to her. But straight to the business... Have you brought the money?";
			link.l1.go = "InTerksShore_1";
		break;
		
		case "InTerksShore_1":
			dialog.text = "I have. But I want to see Abigail first. I must be confident that she is alive and untouched, since I am not going to trust the word of bastard.";
			link.l1 = "Don't you think, mister, that you are not in position to dictate your terms?";
			link.l1.go = "InTerksShore_2";
		break;
		
		case "InTerksShore_2":
			dialog.text = "I understand that, but I am not a fool either. No money talk until I see Abigail. So what? I am waiting.";
			link.l1 = "Good. Now it is time to lay my cards on the table, captain Fleetwood. I have organized  our meeting here not because of money. Well, sure, I'd like to take it, but I need you first.";
			link.l1.go = "InTerksShore_3";
		break;
		
		case "InTerksShore_3":
			dialog.text = "Me? This is getting most interesting... I think, I am starting to understand what is truly going on here. Tell me, is Abigail alive? She lives or have you murdered her, bastard?";
			link.l1 = "I suppose, I will leave you ignorant about her fate. Only one thing for you to know - she is not here. She has played her part well, you are here in my hands. Love is such a wonderful thing... How else could I lure a fox out of its hole to the open grounds? Ha-ha-ha!";
			link.l1.go = "InTerksShore_4";
		break;
		
		case "InTerksShore_4":
			dialog.text = "Don't be glad that soon, rascal. I have organized a fine greeting for you on this island and it is unknown who is in whose hands! So prepare yourself, you have a lot of things to tell me - about Abigail, about Charlie, you will pay for hurting them!";
			link.l1 = "I am shaking with fear already! Time to end our conversation, mister. Prepare to go to hell, because there is no room for you on heavens.";
			link.l1.go = "InTerksShore_5";
		break;
		
		case "InTerksShore_5"://массовая драка на необитаемом острове
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешим драться
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			for (i=1; i<=3; i++)//офицеры Флитвуда
			{
				sld = characterFromId("FlOfficer_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			for (i=1; i<=7; i++)//засада Флитвуда
			{
				sld = GetCharacter(NPC_GenerateCharacter("EnemySailor_"+i, "sold_eng_"+i, "man", "man", 18, ENGLAND, -1, false, "soldier"));
				FantomMakeCoolFighter(sld, 18, 30, 30, "blade_19", "pistol2", "bullet", 40);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
				if (i >= 1 && i < 3) ChangeCharacterAddressGroup(sld, "Shore56", "goto", "goto2");
				else ChangeCharacterAddressGroup(sld, "Shore56", "goto", "goto9");
			}
			for (i=1; i<=7; i++)//наши - к бою!
			{
				sld = characterFromId("OwrSailor_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
            LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
            LAi_group_SetCheck("EnemyFight", "FleetwoodDiedInShore");
            DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
	}
}
