// Филипп де Пуанси - генерал-губернатор французских колоний
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
			if (CheckAttribute(pchar, "questTemp.Terrapin") && pchar.questTemp.Terrapin == "done")
			{
				dialog.text = "Glad to see you, "+pchar.name+". I am informed about your accomplishments. And what the most important, you have perfectly succeeded in your mission! You have shown yourself from the best side and I am glad that I was not mistaken about you.";
				link.l1 = "Can I receive an order to release my brother in a written form from you now?";
				link.l1.go = "serve";
				AddCharacterExpToSkill(pchar, "Sneak", 500);
				break;
			}
			if (CheckAttribute(pchar, "questTemp.Sharlie.Hardcore_Tortuga") && CheckAttribute(pchar, "questTemp.Sharlie.LevasserDied"))
			{
				dialog.text = "Glad to see you, "+pchar.name+". I have heard about your deeds. And, what is the most important, your mission is completed! Though, I must say, I expected a smarter idea than a frontal attack. Pity for dead French soldiers\nBut war is a war, there are always casualties. You have fulfilled your duty, and I am glad that I was right about you.";
				link.l1 = "Can I receive an order to release my brother in written form from you now?";
				link.l1.go = "serve";
				DeleteAttribute(pchar, "questTemp.Sharlie.Hardcore_Tortuga");
				DeleteAttribute(pchar, "questTemp.Sharlie.LevasserDied");
				break;
			}
			// Jason НСО 
			if (CheckAttribute(pchar, "questTemp.Guardoftruth") && !CheckAttribute(pchar, "questTemp.Patria"))
			{
				if (CheckCharacterItem(pchar, "patent_fra"))
				{
					dialog.text = "Good to see you, Charles. First of all, allow me to congratulate you on the successfully completing a complex task of protecting the colony of Saint-Pierre from the Spanish invaders. Brilliant work, my friend!";
					link.l1 = "Thank you, Chevalier.";
					link.l1.go = "patria";
					Patria_SetInspector();
				}
				else
				{
					dialog.text = "Good to see you, Charles. First of all, allow me to congratulate you on the successfully completing a complex task of protecting the colony of Saint-Pierre from the Spanish invaders. Brilliant work, my friend! And I give you another opportunity to cooperate with the Navy. France is in dire need of officers like you. I hope this time you will be more sensible ... Take the patent, Captain Charles de Maure!";
					link.l1 = "Thank you, Chevalier. I'm glad to help the country and eager to continue serving it!";
					link.l1.go = "patria";
					if (!CheckCharacterItem(pchar, "suit1")) GiveItem2Character(pchar, "suit1");
					GiveItem2Character(pchar, "patent_fra");
					EquipCharacterbyItem(pchar, "patent_fra");
					Items[sti(pchar.EquipedPatentId)].TitulCur = 2; 
					Items[sti(pchar.EquipedPatentId)].TitulCurNext = 0;
					ChangeCharacterNationReputation(pchar, FRANCE, 100);
					Patria_SetInspector();
				}
				break;
			}
			if (CheckAttribute(pchar, "questTemp.Patria") && pchar.questTemp.Patria != "fail" && pchar.questTemp.Patria != "end")
			{
				if (!CheckCharacterItem(pchar, "patent_fra"))
				{
					dialog.text = "Charles, you disappointed me. As a result of your unwise actions, you lost your patent and the rank in the Royal Navy. There is no room for any further coopertaion. Dismissed.";
					link.l1 = "Hmm...";
					link.l1.go = "patria_patentfail";
					break;
				}
				if (pchar.questTemp.Patria == "epizode_1_return")
				{
					dialog.text = "Glad to see you, Charles. Report!";
					if (CheckAttribute(pchar, "questTemp.Patria.Ecliaton_Fail"))
					{
						link.l1 = "The job is done, the ransom from the colony of San Jose is received. But there are bad news: in battle with the fort 'Eclatant' was sunk. I warned the captain to watch out, but he didn't listen to me, and...";
						link.l1.go = "patria_8_1";
					}
					else
					{
						link.l1 = "The job is done, the ransom from the colony of San Jose is received.";
						link.l1.go = "patria_8";
					}
					break;
				}
				if (pchar.model != "Sharle_6")
				{
					dialog.text = "Monsieur, from this day onwards only enter my halls in an appropriate uniform!";
					link.l1 = "...";
					link.l1.go = "exit";
					break;
				}
				if (pchar.questTemp.Patria == "epizode_2_return" && pchar.model == "Sharle_6")
				{
					dialog.text = "Baron, captain! Glad to see you!";
					link.l1 = "The assignment is completed, Chevalier.";
					link.l1.go = "patria_14";
					break;
				}
				if (pchar.questTemp.Patria == "epizode_3_return" && pchar.model == "Sharle_6")
				{
					dialog.text = TimeGreeting()+", captain. What news do you bring?";
					if (CheckAttribute(pchar, "questTemp.Patria.Ecliaton_Fail"))
					{
						link.l1 = "The Spaniards did a plan of attack on Port-au-Prince. At the western end of Hispaniola we found a powerful enemy squadron. In battle, it was completely destroyed. However, in a severe and unequal battle, 'Eclatant' was sunk.";
						link.l1.go = "patria_26_1";
					}
					else
					{
						link.l1 = "The Spaniards did a plan of attack on Port-au-Prince. At the western end of Hispaniola we found a powerful enemy squadron. In battle, it was completely destroyed.";
						link.l1.go = "patria_26";
					}
					break;
				}
				if (pchar.questTemp.Patria == "epizode_4_return" && pchar.model == "Sharle_6")
				{
					dialog.text = TimeGreeting()+", Charles. How is mynheer Stuyvesant?";
					link.l1 = "Everything's fine, Chevalier. The delivery to the destination was successful, here's the answer to your letter.";
					link.l1.go = "patria_31";
					break;
				}
				if (pchar.questTemp.Patria == "epizode_5_return" && pchar.model == "Sharle_6")
				{
					dialog.text = "Charles, baron... You're already back?";
					link.l1 = "...";
					link.l1.go = "patria_36";
					break;
				}
				if (pchar.questTemp.Patria == "epizode_6_return" && pchar.model == "Sharle_6")
				{
					dialog.text = "I don't like your frown, Charles. What did Stuyvesant say, report!";
					if (pchar.questTemp.HWIC.Detector == "holl_win" || pchar.questTemp.HWIC.Detector == "self_win") link.l1 = "Literally, he said: 'tell Chevalier that he is no longer in charge of Sint Maarten. Enough of him. And regarding the inspection from the parent state - let him come up with something, It was never difficult for de Poincy to turn everything upside down'. After announcing this message, mynheer kicked me out of the residence. That was the end of our negotiations.";
					else link.l1 = "Literally, he said: 'you liege has been way too greedy on Sint Maarten as of late, so it's time to temper his insatiable hunger.' After this, he tried to arrest me. I had to clear my way to the ship with a blade. So much for Dutch diplomacy.";
					link.l1.go = "patria_43";
					break;
				}
				if (pchar.questTemp.Patria == "epizode_7_go" && pchar.model == "Sharle_6")
				{
					dialog.text = "Captain, we've been waiting for you. I explained current state of affairs to the baron, and he fully supported my decision. The Dutch will answer for their arrogance.";
					link.l1 = "It's a war then?";
					link.l1.go = "patria_51";
					break;
				}
				if (pchar.questTemp.Patria == "epizode_7_continue" && pchar.model == "Sharle_6" && pchar.location.from_sea == "Charles_town") // add-7
				{
					Patria_HunterShipChecker();
					if (CheckAttribute(pchar, "questTemp.Patria.Hunter.GiveShip"))
					{
						dialog.text = "So, my friend, I see you have a captured East Indian ship with the goods. Excellent!";
						link.l1 = "I'm handing over a ship to you, give orders to the port officials, Chevalier.";
						link.l1.go = "patria_55";
					}
					else
					{
						dialog.text = "Do you have any questions, Charles?";
						link.l1 = "Not at the moment, monsieur. I'll get going then...";
						link.l1.go = "exit";
					}
					break;
				}
				if (pchar.questTemp.Patria == "epizode_8" && pchar.model == "Sharle_6")
				{
					dialog.text = "Finally, you have arrived, captain! There is an emegency on Saint Christopher!";
					link.l1 = "A hostile squadron?";
					link.l1.go = "patria_59";
					break;
				}
				if (pchar.questTemp.Patria == "epizode_8_wait" && pchar.model == "Sharle_6" && GetCompanionQuantity(pchar) < 5)
				{
					dialog.text = "Are you ready to take in the squadron our courier lugger?";
					link.l1 = "I am.";
					link.l1.go = "patria_64";
					break;
				}
				if (pchar.questTemp.Patria == "epizode_8_return")
				{
					dialog.text = "Captain de Maure, sir Doily! Glad to see you! The whole city watched as you taught the Spanish-Dutch scoundrels who desired our colony a lesson!";
					link.l1 = "It was my duty, Chevalier.";
					link.l1.go = "patria_66";
					break;
				}
				if (pchar.questTemp.Patria == "epizode_9_start" && pchar.model == "Sharle_6")
				{
					dialog.text = TimeGreeting()+", Charles. Let's begin, shall we?";
					link.l1 = "Of course, Chevalier. That's why I'm here.";
					link.l1.go = "patria_69";
					break;
				}
				if (pchar.questTemp.Patria == "epizode_9_return" && pchar.model == "Sharle_6")
				{
					dialog.text = "I am glad to welcome in my office the Vice Admiral of the Royal Navy of France! Yes, my friend, you were not mistaken: I personally signed the order about your appointment. Formally, it still has to be approved in France, but you don't even have to doubt that it will happen. Congratulations!";
					link.l1 = "I serve my nation!";
					link.l1.go = "patria_76";
					break;
				}
				if (pchar.questTemp.Patria == "epizode_10_return" && pchar.model == "Sharle_6")
				{
					if (GetQuestPastDayParam("questTemp.Patria.Curacao.Date") < 30) sTemp = "It will be ready soon"; // в зависимости от времени сколько добирался
					else sTemp = "It is ready";
					dialog.text = "Have you been successful in your endeavours? Was colonel Doily satisfied?";
					link.l1 = "Everything went perfectly, Chevalier. The Stuyvesant's caravan was captured, all slaves brought to Jamaica, the squadron of the colonel "+sTemp+" on the way to Curacao.";
					link.l1.go = "patria_81";
					break;
				}
				if (pchar.questTemp.Patria == "epizode_11_return" && pchar.model == "Sharle_6")
				{
					dialog.text = "Glory to the victors! Congratulations, congratulations, my friend! You never cease to amaze.";
					link.l1 = "Thank you, Chevalier. Stuyvestant was punished and ready to pay indemnities, peace is restored, Sint Maarten solely belongs to France now.";
					link.l1.go = "patria_85";
					break;
				}
				if (pchar.questTemp.Patria == "epizode_12_continue")
				{
					dialog.text = "So, my friend, I'm glad to see you again. Did you have a good rest?";
					link.l1 = "Yes, Chevalier. This rest was one the best I've ever had. You talked about some delicate business?";
					link.l1.go = "patria_88";
					break;
				}
				if (pchar.questTemp.Patria == "epizode_12_baronalive")
				{
					dialog.text = "My friend, you must be a sorcerer! You managed to pull off a feat! Our baron no longer wants to create a Trading Company here.";
					link.l1 = "I believe his only wish right now is to be back in Paris.";
					link.l1.go = "patria_103";
					break;
				}
				if (pchar.questTemp.Patria == "epizode_12_barondie")
				{
					dialog.text = "Charles, have you heard about the baron? He was taken out by pirates...";
					link.l1 = "Yes, Chevalier. Alas, but the baron is dead. I know that for sure.";
					link.l1.go = "patria_112";
					break;
				}
				if (pchar.questTemp.Patria == "epizode_12_baronfail")
				{
					dialog.text = "Charles, how is your progress? I was told that the baron boarded your ship...";
					link.l1 = "Yes, Chevalier. He was on board, I was working on him, but ... he died of fever.";
					link.l1.go = "patria_x112";
					break;
				}
				if (pchar.questTemp.Patria == "epizode_12_baronkilled")
				{
					dialog.text = "Charles, how is your progress? I was told that the baron boarded your ship...";
					link.l1 = "Yes, Chevalier. He was on board, I was working on him, but ... he died in a battle.";
					link.l1.go = "patria_y112";
					break;
				}
				if (pchar.questTemp.Patria == "epizode_12_baronwin")
				{
					dialog.text = "My friend, you must be a sorcerer! You managed to pull off a feat! Our baron no longer wants to create a Trading Company here.";
					link.l1 = "Probably he's heading to Paris now.";
					link.l1.go = "patria_117";
					break;
				}
				dialog.text = "Do you have any questions, Charles?";
				link.l1 = "Not at this moment, monsieur. I'll get going then...";
				link.l1.go = "exit";
				break;
			}
			dialog.text = "What do you want? Monsieur?";
			link.l1 = "Nothing serious, just a courtesy visit. I am leaving now...";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		// в тюрьме при старте игры
		case "Puancie_Jail":
			dialog.text = "Good day to you, Charles. Let me introduce myself I am Philippe de Poincy and I...";
			link.l1 = "Why the hell have you put me in the prison? It's inappropriate! I am the French nobleman and...";
			link.l1.go = "Puancie_Jail_1";			
		break;
		
		case "Puancie_Jail_1":
			dialog.text = "Listen to me, young man, don't interrupt me! You are talking with the Governor General of the French colonies in Caribbean archipelago! I forgive your tone only because of your ignorance about who you were talking to. But I'd recommend you to be more restrained in the future.";
			link.l1 = "Hm... forgive me, your Excellency.";
			link.l1.go = "Puancie_Jail_2";			
		break;
		
		case "Puancie_Jail_2":
			dialog.text = "Better. Now, concerning your previous question - you were considered by mistake as a spanish spy and put under arrest until your status is clear. Blasted Castilians have become more active recently, therefore I ordered to detain all suspicious people\nBut we know who you are now - you are really Charles de Maure, a brother of Michelle de Monper, and I personally came down here in order to release you. And you are yelling at me like a little boy!";
			link.l1 = "Pardon me again, your Excellency. Am I free now?";
			link.l1.go = "Puancie_Jail_3";			
		break;
		
		case "Puancie_Jail_3":
			dialog.text = "Yes, you are. But I want to talk privately with you before a sergeant will open your cell. Do you know that your brother, one of the most worthiest warriors of the Maltese Order was arrested and put under guard?";
			link.l1 = "I only knew that my brother is in trouble and he needs help. That's why I came here from Paris.";
			link.l1.go = "Puancie_Jail_4";			
		break;
		
		case "Puancie_Jail_4":
			dialog.text = "Glad to hear that. I want you to know that monsieur de Monper is in the serious trouble. I have got all reasons to suspect him in an abuse of authority, a misappropriation of the property and in a perjury. But you really can help your brother.";
			link.l1 = "Monsieur, could you tell me more? I don't get it, Michel was the pride of the Order and...";
			link.l1.go = "Puancie_Jail_5";			
		break;
		
		case "Puancie_Jail_5":
			dialog.text = "I thought so. We all did! But his recent actions made us... unconfident in his loyalty to the Order. Too unconfident, so he was put under arrest. Michel will tell you the details himself. He will explain you how you could help him to take away accusations and to avoid a disgrace.";
			link.l1 = "Where is my brother now? You told me that he is in the prison, but I haven't seen him around...";
			link.l1.go = "Puancie_Jail_6";			
		break;
		
		case "Puancie_Jail_6":
			dialog.text = "Did I say imprisoned, young man? Are you even listening? I said, he is under arrest! It is not the same thing. Michelle de Monper is being kept under arrest in the underground base of Sent Pierre which is a property of the Order of Malta\nI allow you visiting the base unlimitedly and talking with your brother as often as you think you need. Officer and soldiers of the Order are aware of my instructions and they will not stop you.";
			link.l1 = "Where is that underground base?";
			link.l1.go = "Puancie_Jail_7";			
		break;
		
		case "Puancie_Jail_7":
			dialog.text = "It's here, in Sent Pierre of cource. Find the local prison and enter the door with symbols of the Order. Go downstairs to the casemate on the second level of a basement. Find there monsieur Monper. That's it. I hope that we will meet again, Charles. Sergeant!";
			link.l1 = "Please wait, your Excellency! And what about my... belongings? My sword and the rest?";
			link.l1.go = "Puancie_Jail_8";			
		break;
		
		case "Puancie_Jail_8":
			dialog.text = "Your things were confiscated for a repayment of your brother's debt. Farewell, monsieur de Maure.";
			link.l1 = "What the f...";
			link.l1.go = "Puancie_Jail_9";			
		break;
		
		case "Puancie_Jail_9":
			DialogExit();
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "Sharlie_GoFromPrison", 5);
			NextDiag.CurrentNode = "First time";
		break;
		
		// возвращаем деньги
		case "saga":
			bDisableFastReload = false;
			LocatorReloadEnterDisable("Charles_townhall", "reload1_back", false);
			dialog.text = "Aha, Charles de Maure himself! Glad to see you. I take it that you've come here to discuss your brother's fate with me?";
			link.l1 = "I am ready to repay what Michel de Monper owes to the Order and personally to you.";
			if (sti(pchar.money) >= 1000000) link.l1.go = "saga_1";
			else link.l1.go = "saga_exit";			
		break;
		
		case "saga_exit":
			dialog.text = "Hm.. But where is the money? You have a strange sense of humor, young man and I don't get it.";
			link.l1 = "Pardon me, Chevalier. I forgot money in my locker on the ship. I'll be back soon.";
			link.l1.go = "exit";
			NextDiag.TempNode = "saga_repeat";	
		break;
		
		case "saga_repeat":
			dialog.text = "Have you brought money, Charles?";
			if (sti(pchar.money) >= 1000000)
			{
				link.l1 = "Sure! I hope that this sum will completely repay all of your costs.";
				link.l1.go = "saga_1";
			}
			else
			{
				link.l1 = "Not yet...";
				link.l1.go = "exit";
				NextDiag.TempNode = "saga_repeat";
			}		
		break;
		
		case "saga_1":
			AddMoneyToCharacter(pchar, -1000000);
			dialog.text = "Splendid! I take them from you. You've shown yourself from your best side, Charles!";
			link.l1 = "When will I get an order for the release of Michel de Monper?";
			link.l1.go = "saga_2";			
		break;
		
		case "saga_2":
			dialog.text = "Don't be in a hurry, young man. I can only respect that you pay off debts and protect your family by putting your own life in danger. It is a rare nobleness these days... But money is not the main part in this sad story. Your brother got such a large sum on terms of doing a very delicate mission\nMichel de Monper, as a faithful Catholic, had sworn on the Book that he will find a way to punish one insolent heretic and to restore the justice he violated for the glory of the Order and Holy Church...";
			link.l1 = "But he won't be able to keep his word under arrest!";
			link.l1.go = "saga_3";			
		break;
		
		case "saga_3":
			dialog.text = "See, my friend, your brother has given me a strong reason not to trust in his decency. There are no guarantees that he won't escape and break his oath. So if you want to take away all accuses from him - perform the oath by yourself. Monsieur de Monper will tell you the details.";
			link.l1 = "Hm... I wasn't expecting that. But you don't leave me other choice. I'll make my final decision after a talk with my brother.";
			link.l1.go = "saga_4";			
		break;
		
		case "saga_4":
			dialog.text = "I am starting to really like you, Charles. One day, perhaps, we will become friends. Anyway, this is my last term of releasing your brother. I give you my word that your family reputation will not be harmed if you do what your brother didn't. And you will be able to count on my friendship in the future.";
			link.l1 = "I have understood you. Farewell!";
			link.l1.go = "saga_5";			
		break;
		
		case "saga_5":
			DialogExit();
			pchar.questTemp.Saga = "mishelle";//Сага - старт
			AddQuestRecord("Sharlie", "21");
			NextDiag.CurrentNode = "First time";
		break;
		
		case "serve":
			dialog.text = "Don't worry, "+pchar.name+", I will keep my word. You brother will be released and all accusations will be taken away from him. Your family reputation is out of danger now. I'd say that it is all by your merits and only yours. Your father can be proud for raising such a son.";
			link.l1 = "Thanks for kind words, Chevalier. I take it that I can head to Martinique immediately?";
			link.l1.go = "serve_1";	
			Island_SetReloadEnableGlobal("Tortuga", true);
			CloseQuestHeader("Terrapin");
			SetFunctionTimerCondition("Terrapin_SetFontene", 0, 0, 5, false); // таймер
		break;
		
		case "serve_1":
			dialog.text = "Wait a bit, my friend. I hope that I can call you my friend, can't I? I want to pay you my gratitude personally. I have been watching your progress since you arrived here and I know about most of your deeds. You have made a great fame for yourself in the Caribbean and, without a doubt, you are also well known and respected in some particular sections of society. France needs people like you\nCaptain "+GetFullName(pchar)+"! By power, given me by His Majesty, the King of France, I have an honor to offer you a patent of captain of the Royal Navy and to take under your command the vessel of French navy, a light frigate 'Gryffondor'!\nIts ex captain de Fontenot will be a governor of Tortuga thanks to you and the best light frigate in the Caribbean needs a captain. Do you accept the offer?";
			link.l1 = "Interesting. And what in return?";
			link.l1.go = "serve_2";		
		break;
		
		case "serve_2":
			dialog.text = "Just a bit. Tenth of your catch and accomplishing delicate missions sometimes. I am waiting for your decision.";
			link.l1 = "No one would reject such an offer, your Excellency! It is an honor to serve your own nation!";
			link.l1.go = "serve_3";
			link.l2 = "Forgive me for being immodest but I have to reject your offer for now. My family matters might demand an immediate return to the homeland.";
			link.l2.go = "serve_no";
		break;
		
		case "serve_no":
			ChangeCharacterComplexReputation(pchar, "fame", 7);
			dialog.text = "Pity. I hoped that you will agree... But, nevertheless, I am forced to ask you for one more favor, actually it is in your interests too. Martinique is under attack. There is a heavy fighting in the port and in the city itself\nAlas, I have no one to send there in order to help the garrison but you. I ask you as a patriot of your Fatherland to repulse an assault by any means necessary. I hope that you have enough resources to do that.\nBesides, your brother is still there, you can save his life.";
			link.l1 = "My brother is in danger? I am on my way!";
			link.l1.go = "serve_exit";			
		break;
		
		case "serve_3":
			dialog.text = "Such an honorable words! Words of the true soldier and loyal son of the Fatherland! Congratulations, monsieur "+GetFullName(pchar)+". You are awarded a rank of commander of the naval forces of France. Accept this uniform from me. Wear it proudly and be worth of it!";
			link.l1 = "I serve my nation!";
			link.l1.go = "serve_4";			
		break;
		
		case "serve_4":
			dialog.text = "The light frigate 'Gryffondor' is under you command now. From this moment this excellent ship is yours. Use it's high qualities for the glory of his Majesty and to strengthen a French influence on the Caribbean archipelago!";
			link.l1 = "At once!";
			link.l1.go = "serve_5";		
                        if(CheckAttribute (pchar, "IsMushketer")) SetMainCharacterToMushketer("", false);
                        // <--- belamour всегда снимаем мушкет, если какие либо операции с кирасам	
			RemoveCharacterEquip(pchar, CIRASS_ITEM_TYPE);
			GiveItem2Character(pchar, "suit1");
			EquipCharacterbyItem(pchar, "suit1");
			GiveItem2Character(pchar, "patent_fra");
			EquipCharacterbyItem(pchar, "patent_fra");
			Items[sti(pchar.EquipedPatentId)].TitulCur = 2; 
        	Items[sti(pchar.EquipedPatentId)].TitulCurNext = 0;
			Log_Info("You've received a uniform of royal naval forces of France");
			ChangeCharacterNationReputation(pchar, FRANCE, 100);
			ChangeCharacterComplexReputation(pchar, "fame", 12);
		break;
		
		case "serve_5":
			if (GetCompanionQuantity(pchar) > 4)
			{
				dialog.text = "But your squadron is too big already so come back to get the 'Gryffondor' when you will get rid of one ship.";
				link.l1 = "Fine. I'll do that.";
				link.l1.go = "serve_wait";		
			}
			else
			{
				dialog.text = "Along with the ship you'll get its acting captain and the crew. If you want, you can leave him under your command or post him from a ship and we will find him another position.";
				link.l1 = "Got it!";
				link.l1.go = "serve_6";
			}
		break;
		
		case "serve_6":
			dialog.text = "But I have bad news for you, captain. I was just informed that Martinique is under attack. There is a heavy fighting in the port and in the city itself\nAlas, I have no one to send there in order to help the garrison but you. Here is your first mission\n Protect Sent Pierre! Besides, your brother is still there, you can save his life.";
			link.l1 = "My brother is in danger? I am on my way!";
			link.l1.go = "serve_7";
		break;
		
		case "serve_7":
			DialogExit();
			CreateGriffondor();
			sld = characterFromId("GriffOfficer");
			SetCharacterRemovable(sld, true);
			SetCompanionIndex(pchar, -1, sti(sld.index));
			sld.loyality = MAX_LOYALITY;
			NextDiag.CurrentNode = "First time";
			DeleteAttribute(pchar, "questTemp.Terrapin");
			pchar.questTemp.Sharlie = "senpierbattle";
			pchar.questTemp.Sharlie.DefendSP = "true";
			AddQuestRecord("Sharlie", "24");
			pchar.quest.DefendSP_prepare.win_condition.l1 = "location";
			pchar.quest.DefendSP_prepare.win_condition.l1.location = "Martinique";
			pchar.quest.DefendSP_prepare.function = "DefendSP_PrepareMartinique";
			AddCharacterExpToSkill(pchar, "Leadership", 2000);
			AddCharacterExpToSkill(pchar, "Fortune", 500);
		break;
		
		case "serve_wait":
			DialogExit();
			NextDiag.CurrentNode = "serve_shipcheck";
		break;
		
		case "serve_shipcheck":
			dialog.text = "Are you ready to take a 'Gryffondor' under your command?";
			if (GetCompanionQuantity(pchar) > 4)
			{
				link.l1 = "Not yet, I am repositioning my ships in the squadron...";
				link.l1.go = "exit";
			}
			else
			{
				link.l1 = "I am.";
				link.l1.go = "serve_5a";
			}
			NextDiag.TempNode = "serve_wait";
		break;
		
		case "serve_5a":
			dialog.text = "Splendid! Along with the ship you'll get its acting captain and the crew. If you want you can leave him under your command or post him from a ship and we will find him another position.";
			link.l1 = "Got it!";
			link.l1.go = "serve_6";
		break;
		
		case "serve_exit":
			DialogExit();
			NextDiag.CurrentNode = "First time";
			DeleteAttribute(pchar, "questTemp.Terrapin");
			pchar.questTemp.Sharlie = "senpierbattle";
			pchar.questTemp.Sharlie.DefendSP = "true";
			AddQuestRecord("Sharlie", "23");
			pchar.quest.DefendSP_prepare.win_condition.l1 = "location";
			pchar.quest.DefendSP_prepare.win_condition.l1.location = "Martinique";
			pchar.quest.DefendSP_prepare.function = "DefendSP_PrepareMartinique";
			AddCharacterExpToSkill(pchar, "Leadership", 1000);
			AddCharacterExpToSkill(pchar, "Fortune", 250);
		break;
		
		// Jason НСО
		case "patria":
			dialog.text = "And this is only the beginning, monseigneur! I am sure that you will go far, with such military talents! And I already have another errand for an excellent naval officer, with whom, I am sure, you will manage just as well. Moreover, it is directly related to your previous mission.";
			link.l1 = "I'm all ears, monsiuer";
			link.l1.go = "patria_1";
		break;
		
		case "patria_1":
			dialog.text = "But let me first introduce you to the person that entered my office. Meet Baron Noel Forget, honorary member of the French West-Indies Trade Company. Arrived at the archipelago to inspect our colonies for expanding the organization of plantations of sugar cane and other crops, as well as exploring the possibility of developing trade ties in our region. From Paris it is prescribed to give him all kinds of support and assistance in these matters, which we undoubtedly will do. Baron, I present to you Monsieur Charles de Maure, one of the most talented captains in the service of France...";
			link.l1 = "";
			link.l1.go = "patria_2";
		break;
		
		case "patria_2":
			DialogExit();
			sld = characterFromId("Noel");
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "patria_3":
			dialog.text = "So, Charles, while me and the baron are inspecting Saint Christopher, I assign you the following task. No one can attack French settlements and expect to get away with it, and the Spaniards, even although they have already been taught a lesson for the aggression on Martinique, must answer for their crimes with their purses and compensate for the damage done to the colony\nTogether with the French baron, a squadron arrived consisting of a powerful 66-gun ship 'Eclatant'. The captain of the ship is an experienced sailor, but in the Caribbean for the first time, so he comes under your command. Together with 'Eclatant' you will go to the shores of the Spanish island of Trinidad, and demand from the Spaniards a monetary compensation in the size of three hundred thousand pesos for the attack on Saint Pierre.";
			link.l1 = "Chevalier, do you honestly believe that the Spaniards are going to agree?";
			link.l1.go = "patria_4";
		break;
		
		case "patria_4":
			dialog.text = "I am sure that yes - after the 'Eclatant' and your squadron have blasted Fort San Jose into pieces. Landing troops and seizing the city, losing soldiers, I think, won't be needed. Attack without warning, destroy the fort, and then signal to the commandant that you want to set the conditions. In this situation, the Spaniards will have nowhere to go, and they will prefer to pay. What would you do if you acted in the place of the governor of the city that was left without protection?";
			link.l1 = "Hm. Reasonably, Chevalier.";
			link.l1.go = "patria_5";
		break;
		
		case "patria_5":
			dialog.text = "Is it clear as to what you have to do?";
			link.l1 = "Yes, your Grace.";
			link.l1.go = "patria_6";
		break;
		
		case "patria_6":
			if (pchar.model == "Sharle_6")
			{
				dialog.text = " Then get to it. Here's a letter for Captain of 'Eclatant' with confirmation of your authority. This excellent ship with a well trained crew is now at your disposal. Charles, and don't forget that you now serve France, and to properly communicate with officials like me it is advised to wear a uniform. It suits you perfectly. Good luck, Captain de Maure!";
			}
			else
			{
				dialog.text = " Then get to it. Here's a letter for Captain of 'Eclatant' with confirmation of your authority. This excellent ship with a well trained crew is now at your disposal. Oh and Charles: put on a captain's uniform, I order you! Firstly, it is not worthy for an officer of the French Royal Navy to look like the traders and privateers, and secondly, your uniform suits you perfectly. Execute, Captain de Maure!";
			}
			link.l1 = "";
			link.l1.go = "patria_7";
		break;
		
		case "patria_7":
			DialogExit();
			npchar.dialog.currentnode = "First time";
			LAi_SetHuberType(npchar);
			AddQuestRecord("Patria", "1");
			pchar.questTemp.Patria = "epizode_1";
			Patria_SetEcliaton();
		break;
		
		case "patria_8_1":
			if (sti(pchar.money) >= 300000) AddMoneyToCharacter(pchar, -300000);
			else pchar.questTemp.Patria.NoMoney = "true";
			dialog.text = "'Eclatant' sank? Charles, this is a disaster! What will the minister say now? You let me down, Charles! I was sure I could rely on your experience, and you ... Alas, but you will be held responsible for this. I'll write a report, and you'd better disappear for a while. Your service in the Royal Navy is over.";
			link.l1 = "Hmm ... I'm sorry, monsieur. Seems that it is really better for me to vanish for a month or two, until the minister calms down his anger. Good-bye, and once again I'm very sorry for letting you down.";
			link.l1.go = "patria_8_2";
		break;
		
		case "patria_8_2":
			DialogExit();
			npchar.dialog.currentnode = "First time";
			pchar.questTemp.Patria = "fail";
			AddQuestRecord("Patria", "8");
			CloseQuestHeader("Patria");
			RemoveItems(pchar, "patent_fra", 1);
			if (CheckAttribute(pchar, "questTemp.Patria.NoMoney"))
			{
				ChangeCharacterComplexReputation(pchar, "nobility", -20);
				ChangeCharacterNationReputation(pchar, FRANCE, -30);
				DeleteAttribute(pchar, "questTemp.Patria.NoMoney");
			}
			else
			{
				ChangeCharacterComplexReputation(pchar, "nobility", -5);
				ChangeCharacterNationReputation(pchar, FRANCE, -5);
			}
			pchar.quest.Patria_SanJoseReturnOver.over = "yes"; // снять таймер
		break;
		
		case "patria_8":
			if (sti(pchar.money) >= 300000)
			{
				dialog.text = "Perfect!";
				link.l1 = "Here, please take these three hundred thousand.";
				link.l1.go = "patria_9";
			}
			else
			{
				dialog.text = "Perfect, but where is money, Charles?";
				link.l1 = "Huh, In the chest on the ship, I'll deliver it in a moment!";
				link.l1.go = "patria_8_3";
			}
		break;
		
		case "patria_8_3":
			DialogExit();
			npchar.dialog.currentnode = "patria_8_4";
		break;
		
		case "patria_8_4":
			dialog.text = "So, Charles, did you bring the ransom from Trinidad?";
			if (sti(pchar.money) >= 300000)
			{
				link.l1 = "Yes monsieur. Here it is.";
				link.l1.go = "patria_9";
			}
			else
			{
				link.l1 = "I'll bring it in a moment!";
				link.l1.go = "patria_8_3";
			}
		break;
		
		case "patria_9":
			AddMoneyToCharacter(pchar, -300000);
			dialog.text = "I am pleased with you, Charles, you never disappoint. The task was not easy, and you are granted a sum of 50,000 pesos out of the redemption amount as a reward. Take it, it's all yours.";
			link.l1 = "My thanks, Chevalier.";
			link.l1.go = "patria_10";
		break;
		
		case "patria_10":
			AddMoneyToCharacter(pchar, 50000);
			dialog.text = "There already is a new task for you. Monsieur Forget completed the inspection at Saint Christopher and now wishes to visit our northern colonies. I ask you to take the baron to Tortuga and Hispaniola, to help in every way in his affairs and to fulfill his requests. Is it clear, Charles?";
			link.l1 = "Of course, Chevalier.";
			link.l1.go = "patria_11";
		break;
		
		case "patria_11":
			dialog.text = "The Baron is short on time, so I ask you not to be distracted by other matters and not to delay the journey for longer than two months.";
			link.l1 = "Of course, monseigneur. The voyage between the islands does not take so much time, unless Monsieur Forget's affairs in the colonies are time-consuming";
			link.l1.go = "patria_12";
		break;
		
		case "patria_12":
			dialog.text = "Perfect. Then the baron will travel on your ship. Give him the best cabin there is.";
			link.l1 = "Of course, Chevalier!";
			if (pchar.model == "Sharle_6") link.l1.go = "patria_13";
			else link.l1.go = "patria_13_1";
		break;
		
		case "patria_13_1":
			dialog.text = "And one more thing, Charles: You're without your officer's uniform again! This is your last warning. From this moment onwards I ask you to come to me only in uniform, otherwise I just will not listen to you. You are on duty, and discipline should be in everything, especially in the appearance of a naval officer!";
			link.l1 = "Forgive me, Chevalier. This won't happen again.";
			link.l1.go = "patria_13";
		break;
		
		case "patria_13":
			DialogExit();
			npchar.dialog.currentnode = "First time";
			AddQuestRecord("Patria", "9");
			pchar.questTemp.Patria = "epizode_2";
			Patria_VisiterBegin();
			pchar.quest.Patria_SanJoseReturnOver.over = "yes"; // снять таймер
			ChangeCharacterNationReputation(pchar, FRANCE, 10);
			ChangeCharacterComplexReputation(pchar, "nobility", 3); // 14-add
			ChangeCharacterComplexReputation(pchar, "authority", 3);
			ChangeCharacterComplexReputation(pchar, "fame", 3);
		break;
		
		case "patria_14":
			sld = characterFromId("Noel");
			ChangeCharacterAddressGroup(sld, pchar.location, "goto", "goto4");
			dialog.text = "I had no doubt that your journey would be successful. Any news from Tortuga or from Port-au-Prince?";
			link.l1 = "...";
			link.l1.go = "patria_15";
		break;
		
		case "patria_15":
			DialogExit(); // переключение на инспектора
			LAi_SetActorType(pchar);
			SetMainCharacterIndex(GetCharacterIndex("Noel"));
			pchar = GetMainCharacter();			
			LAi_SetPlayerType(pchar);
			sld = characterFromId("Puancie");
			sld.dialog.currentnode = "patria_16";
			LAi_SetActorType(sld);
			LAi_ActorSetSitMode(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
			bDisableCharacterMenu = true;//лоченые интерфейсы
		break;
		
		case "patria_16":
			dialog.text = "";
			link.l1 = "Yes, Chevalier, I bring news but they are not very pleasant. First, the Governor of Port-au-Prince is sure that the Spaniards are preparing an attack on the colony and for this they are assembling a military squadron on ... em-m, how is it called ... on Santiago, yes. And this doesn't seem to be a gossip. I believe that we cannot leave this without attention, especially since the plantations of Port-au-Prince are one of the best I've ever seen.";
			link.l1.go = "patria_17";
		break;
		
		case "patria_17":
			dialog.text = "Are the Spaniards preparing to attack Port-au-Prince? Hmm... Alright. We will instruct you to deal with this captain Charles de Maure. 'Eclatant' is just repaired, equipped and ready to sail...";
			link.l1 = "And another thing monseigneur: in Paris, the island of Sint Maarten, which lies to the north from here, is considered to be a French colony but Captain Charles de Maure told me that the Dutch are in control there. Is that so, Chevalier?";
			link.l1.go = "patria_18";
		break;
		
		case "patria_18":
			dialog.text = "Mmm... That's right to some extent. Sint Maarten is a French colony. However, Baron, from an economic standpoint, this island is absolutely useless - the area is small, the soil there is meager, lean, fresh water is scarce, and the one that is in the wells is muddy and bitter. I was even told that rainwater was being collected there for drinking.\nTherefore, Sint Maarten was transferred to the Dutch West Indies Trading Company for long-term lease, which uses it as a northern transit point for the Company's ships from the region to the metropolis. The Dutch expanded the Phillipsburg settlement there, built a fort and a port, and for those who have arrived in the archipelago relatively recently, like Captain Charles de Maure, Sint Maarten seems like a Dutch colony.";
			link.l1 = "But de jure the island belongs to us?";
			link.l1.go = "patria_19";
		break;
		
		case "patria_19":
			dialog.text = "Of course. But as I said, it's more profitable to get money for rent than to use its scarce resources.";
			link.l1 = "It seems to me that this island would be very useful for the French West-Indies Trading Company when it appears in the Caribbean. The meaning of it you just announced - the northern outpost on the way to Europe. I need to visit this colony, and it is very likely that the rent of the island to the Dutch will be discontinued.";
			link.l1.go = "patria_20";
		break;
		
		case "patria_20":
			dialog.text = "First, you need to send an inquiry to Willemstad, the director of the Dutch West Indian Trading Company, the Mint of Peter Stuyvesant. He must give his permission for the inspection of the island - after all, the Dutch have been there for a long time.";
			link.l1 = "Then we need to send a curier to Willemstad.";
			link.l1.go = "patria_21";
		break;
		
		case "patria_21":
			dialog.text = "The problem is, mynheer Stuyvesant is rarely present in Willemstad, he is constantly travelling and taking care of Company's affairs on his galleon...";
			link.l1 = "But at least sometimes he's present there, I suppose? Anyway, the Dutch are obligated to ensure the island's inspection to its rightful owners. Why don't we send a letter to the Governor of Philipsburg?";
			link.l1.go = "patria_22";
		break;
		
		case "patria_22":
			dialog.text = "Mynheer Martin Thomas, with all due respect to him, he's just a simple employee, the real management is carried out by the Company. Baron, I will solve this problem, don't worry, It will take some time.";
			link.l1 = "Well, I have plenty of time. After all, we still have to visit the southern colonies, Guadeloupe and Martinique. It's a pity that Captain Charles de Maure won't accompany me this time - he must once again head to Hispaniola...";
			link.l1.go = "patria_23";
		break;
		
		case "patria_23":
			DialogExit();
			LAi_SetActorType(pchar); // 17-add
			SetMainCharacterIndex(GetCharacterIndex("Blaze"));
			pchar = GetMainCharacter();			
			LAi_SetPlayerType(pchar);
			bDisableCharacterMenu = false;//лоченые интерфейсы
			sld = characterFromId("Puancie");
			sld.dialog.currentnode = "patria_24";
			LAi_SetActorType(sld);
			LAi_ActorSetSitMode(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
			ChangeCharacterNationReputation(pchar, FRANCE, 10);
		break;
		
		case "patria_24":
			dialog.text = "Yes, yes, we are delaying our dear captain with our boring conversations! Charles, take the 'Eclatant' to the squadron, advance to Espanola and find out about any real threats to Port-au-Prince from the Spaniards. If there exist any of them then take care of it. However, it's not for me to teach you, you know everything better than I do. If you don't find anything, then you shouldn't waste your time, I need you here. I wait for you with the report no later than a month. Good luck, my friend!";
			link.l1 = "Thank you, Chevalier.  I am sailing now.";
			if (ChangeCharacterHunterScore(pchar, "holhunter", 0) > 10) link.l1.go = "patria_25_1";
			else link.l1.go = "patria_25_2";
		break;
		
		case "patria_25_1":
			dialog.text = "And one more thing, Charles: I heard you have problems with the Dutch authorities? Please, settle this issue as soon as possible, in the near future you will have to visit their colonies. As you understand, that would be impossible under fire from the forts.";
			link.l1 = "Fine, monsieur, it shall be done.";
			link.l1.go = "patria_25";
		break;
		
		case "patria_25_2":
			dialog.text = "And one more thing, Charles: I warn you: avoid any conflicts with the Dutch. In the near future you will have to visit their colonies. As you understand, that would be impossible under fire from the forts...";
			link.l1 = "Fine, monsier. No quarrels with the Dutch.";
			link.l1.go = "patria_25";
		break;
		
		case "patria_25":
			DialogExit();
			npchar.dialog.currentnode = "First time";
			LAi_SetHuberType(npchar);
			AddQuestRecord("Patria", "15");
			pchar.questTemp.Patria = "epizode_3";
			Patria_PortPaxBegin();
			ChangeCharacterComplexReputation(pchar, "nobility", 1); // 14-add
			ChangeCharacterComplexReputation(pchar, "authority", 1);
			ChangeCharacterComplexReputation(pchar, "fame", 1);
		break;
		
		case "patria_26_1":
			dialog.text = "'Eclatant' sank? Charles, this is a disaster! What will the minister say now? You let me down, Charles! I was sure I could rely on your experience, and you ... Alas, but you will be held responsible for this. I'll write a report, and you'd better disappear for a while. Your service in the Royal Navy is over.";
			link.l1 = "Hmm ... I'm sorry, monsieur. Seems that it is really better for me to vanish for a month or two, until the minister calms down his anger. Good-bye, and once again I'm very sorry for letting you down.";
			link.l1.go = "patria_26_2";
		break;
		
		case "patria_26_2":
			DialogExit();
			npchar.dialog.currentnode = "First time";
			pchar.questTemp.Patria = "fail";
			AddQuestRecord("Patria", "19");
			CloseQuestHeader("Patria");
			RemoveItems(pchar, "patent_fra", 1);
			ChangeCharacterComplexReputation(pchar, "nobility", -5);
			ChangeCharacterNationReputation(pchar, FRANCE, -5);
			pchar.quest.Patria_PortPaxOver.over = "yes"; // снять таймер
		break;
		
		case "patria_26":
			dialog.text = "Excellent! While we have captains in our navy like you, we shouldn't fear the trickery of the Castilians. I will send a courier to Port-au-Prince tomorrow with a dispatch and a mail from France, and at the same time I will leave a hint in a personal letter to monseigneur Jeremy Deschamps du Mussaca that it would be nice to thank you for the service, so I can assure that you, Charles, will get a well-deserved award\nA now let's move on to your next assignment. Yes, my friend, I have a new assignment for you, even this time not military but very delicate, and I would like you to do it.";
			link.l1 = "I'm all ears, Chevalier.";
			link.l1.go = "patria_27";
		break;
		
		case "patria_27":
			dialog.text = "I suppose you remember my discussion with Monsieur Forget about Sint-Maarten? We need to assure the baron that the colony has been inspected, and you will go to Curacao, to Willemstadt, to the Company director Peter Stuyvesant. He is there right now, and will be for three more weeks. Also, you'll need to escort the fluyt with the Company's goods to Curacao and give mynheer Stuyvesant a letter from me.";
			link.l1 = "Are these all the tasks?";
			link.l1.go = "patria_28";
		break;
		
		case "patria_28":
			dialog.text = "Yes, captain. Inform me about mynheer Stuyvesant's reply. We should be just in time before Monsieur Forget will return from his trip to Martinique and Guadelupa, and he will finally be able to visit Sint-Maarten, which he really wants to visit.";
			link.l1 = "Very well. May I go?";
			link.l1.go = "patria_29";
		break;
		
		case "patria_29":
			dialog.text = "You may, Charles. Don't take too long, the baron doesn't like waiting. And while visiting Peter Stuyvesant, make sure to wear an officer uniform! Everything has to look official, if you know what I mean.";
			link.l1 = "Of course, Chevalier. Goodbye!";
			link.l1.go = "patria_30";
		break;
		
		case "patria_30":
			DialogExit();
			npchar.dialog.currentnode = "First time";
			AddQuestRecord("Patria", "20");
			pchar.questTemp.Patria = "epizode_4";
			Patria_CureerBegin();
			pchar.quest.Patria_PortPaxOver.over = "yes"; // снять таймер
			GiveItem2Character(pchar, "Reserve_item_01");
			ChangeItemDescribe("Reserve_item_01", "itmdescr_Reserve_item_01_1");
			ChangeCharacterNationReputation(pchar, FRANCE, 10);
			ChangeCharacterComplexReputation(pchar, "nobility", 5); // 14-add
			ChangeCharacterComplexReputation(pchar, "authority", 5);
			ChangeCharacterComplexReputation(pchar, "fame", 5);
		break;
		
		case "patria_31":
			RemoveItems(pchar, "Reserve_item_01", 1);
			dialog.text = "Thank you, captain, give it to me... (reading)... Well then, excellent! Peter Stuyvesant says that Baron Forget will be able to visit Sint-Maarten for inspection and that the governor of Philipsburg will be notified about it and will cooperate. I think, after a visit the baron will make a right decision - to leave an island to be rented to the Dutch\nAnd now, the most heart-warming news, captain! I have a couple of thing to tell you. First: taking into account all of your military accomplishments, you are raised to the position of 'commodore'. Accept my congratulations, monseigneur!";
			link.l1 = "Serving the Motherland!";
			link.l1.go = "patria_32";
		break;
		
		case "patria_32":
			dialog.text = "And secondly: the governor of Port-au-Prince has sent us a trading ship full of goods for you: 500 large bags of coffee and 500 more bags of cocoa. These are all the harvest of plantations in Hispaniola, the ones you've protected from the Spanish raids. Also, an especially valuable cargo was meant for you - 50 units of lignum vitae. I don't think I need to explain to you what that is. Your goods are in the storage at the shop in Capsterville, and you can go and take them from the merchant at any time.";
			link.l1 = "Thank you, Chevalier! Fantastic news!";
			link.l1.go = "patria_33";
		break;
		
		case "patria_33":
			dialog.text = "And now, as for your next task: Baron Forget will come back to Saint-Christopher any day now. You will take him to Sint-Maarten and make sure he is well-guarded. And, so to speak, you will closely watch what will be going on in Philipsburg, and then report to me. Don't leave the city, captain, as soon as the baron arrives - my peon will find you and report.";
			link.l1 = "All is clear. May I go?";
			link.l1.go = "patria_34";
		break;
		
		case "patria_34":
			dialog.text = "You may. A few days of rest on land will be good and usefull for you.";
			link.l1 = "...";
			link.l1.go = "patria_35";
		break;
		
		case "patria_35":
			DialogExit();
			npchar.dialog.currentnode = "First time";
			AddQuestRecord("Patria", "25");
			pchar.questTemp.Patria = "epizode_5";
			pchar.quest.Patria_CureerBackOver.over = "yes"; // снять таймер
			Items[sti(pchar.EquipedPatentId)].TitulCur = 4; 
        	Items[sti(pchar.EquipedPatentId)].TitulCurNext = 0;
			pchar.quest.Patria_SanMartin_wait.win_condition.l1 = "Timer";
			pchar.quest.Patria_SanMartin_wait.win_condition.l1.date.hour  = 8+rand(2);
			pchar.quest.Patria_SanMartin_wait.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1+rand(1));
			pchar.quest.Patria_SanMartin_wait.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1+rand(1));
			pchar.quest.Patria_SanMartin_wait.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1+rand(1));
			pchar.quest.Patria_SanMartin_wait.win_condition.l2 = "Location_Type";
			pchar.quest.Patria_SanMartin_wait.win_condition.l2.location_type = "town";
			pchar.quest.Patria_SanMartin_wait.function = "Patria_SanMartinBaron";
			pchar.questTemp.Patria.Goods = "true"; // товары-призы
			bQuestDisableMapEnter = true;//закрыть карту
			pchar.GenQuest.MapClosedNoBattle = true;
			ChangeCharacterComplexReputation(pchar, "nobility", 1); // 14-add
			ChangeCharacterComplexReputation(pchar, "authority", 1);
			ChangeCharacterComplexReputation(pchar, "fame", 1);
		break;
		
		case "patria_36":
			DialogExit(); // переключение на инспектора
			LAi_SetActorType(pchar);
			SetMainCharacterIndex(GetCharacterIndex("Noel"));
			pchar = GetMainCharacter();			
			LAi_SetPlayerType(pchar);
			sld = characterFromId("Puancie");
			sld.dialog.currentnode = "patria_37";
			LAi_SetActorType(sld);
			LAi_ActorSetSitMode(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
			bDisableCharacterMenu = true;//лоченые интерфейсы
		break;
		
		case "patria_37":
			dialog.text = "";
			link.l1 = "Yes, Chevalier, back already! Your Dutch friends near Sint-Maarten have met us with fire from the fort's cannons and attacked us with a squadron of three ships. Only thanks to the skills of captain Charles de Maure and his crew we've managed to escape! It seems, mynheer Peter Stuyvesant doesn't actually want to see the French king's envoys in Philipsburg, don't you think, Chevalier?";
			link.l1.go = "patria_38";
		break;
		
		case "patria_38":
			dialog.text = "What?!! Here is a letter from Stuyvesant with his personal signature, where he guarantees...";
			link.l1 = "But the commandant of the Philipsburg fort obviously received a different letter from Stuyvesant, telling him to fire at will! And ambush us with a squadron! Was that an accident, Chevalier?! No! They were clearly waiting to meet us there! With cannonballs and buckshot!";
			link.l1.go = "patria_39";
		break;
		
		case "patria_39":
			dialog.text = "Baron, I beg you... I will deal with this. We will immediately send our dear captain, Charles de Maure, to Curacao again to meet with Stuyvesant. The captain has a long history of dealing with delicate situations... And now, I will ask the servants to prepare a bath and good lunch for you.";
			link.l1 = "...";
			link.l1.go = "patria_40";
		break;
		
		case "patria_40":
			DialogExit();
			LAi_SetActorType(pchar); // 14-add
			SetMainCharacterIndex(GetCharacterIndex("Blaze"));
			pchar = GetMainCharacter();			
			LAi_SetPlayerType(pchar);
			bDisableCharacterMenu = false;//лоченые интерфейсы
			sld = characterFromId("Puancie");
			sld.dialog.currentnode = "patria_41";
			LAi_SetActorType(sld);
			LAi_ActorSetSitMode(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "patria_41":
			dialog.text = "Charles, my friend, you need to hurry to Willemstad. Perhaps, Stuyvesant is still there. If not - find out where he is and find him. During the meeting, tell him about the incident and demand an explanation. I am relying on your experience and authority, and I entrust you to carry out the negotiations. Then, not wasting a single minute, come back and report to me about the results of the meeting.";
			link.l1 = "The task is clear, Chevalier. I will prepare the ship and depart immediately.";
			link.l1.go = "patria_42";
		break;
		
		case "patria_42":
			DialogExit();
			npchar.dialog.currentnode = "First time";
			LAi_SetHuberType(npchar);
			AddQuestRecord("Patria", "29");
			pchar.questTemp.Patria = "epizode_6";
			Patria_DiplomatBegin();
			ChangeCharacterComplexReputation(pchar, "nobility", 3); // 14-add
			ChangeCharacterComplexReputation(pchar, "authority", 3);
			ChangeCharacterComplexReputation(pchar, "fame", 3);
		break;
		
		case "patria_43":
			dialog.text = "I can't believe this...";
			link.l1 = "Moreover, on the way back I was attacked by a Dutch navy squadron. Please, explain to me, Chevalier, what is going on here?";
			link.l1.go = "patria_44";
		break;
		
		case "patria_44":
			dialog.text = "My friend, I'm aware of how perceptive you are, so I won't hide anything from you. The only thing I'll ask of you - what you will hear must not escape this room. Do you promise?";
			link.l1 = "Of course, Chevalier.";
			link.l1.go = "patria_45";
		break;
		
		case "patria_45":
			dialog.text = "Alright. I'm sure, a great career in the French navy awaits you. With my help, of course, you can rise to the rank of vice-admiral! But I digress... And now, as for the Dutch and Sint-Maarten\nLong before you came to Sint-Maarten, large deposits of salt had been found there. At first, nobody cared, but then the Spaniards in Cuba and Hispaniola expressed a big interest in it - to salt bulls' carcasses. As you, no doubt, understand, we cannot trade with Spain directly, therefore...";
			link.l1 = "... you've created a 'separator' in the form of the Dutch West-Indies trade Company...";
			link.l1.go = "patria_46";
		break;
		
		case "patria_46":
			dialog.text = "Definitely! You think quickly - and accurately, Charles! And now, knowing about the inspection from Paris, Stuyvesant decided to boldly take the salt business into his own hands entirely, counting on the fact that we aren't keen on telling everyone about our deal with the Spanish. But that's where he was wrong. Nobody can dare to take from the French Governor General's hands without punishment! And we'll show him just that.";
			link.l1 = "As I understand, Baron Forget can't know about this...";
			link.l1.go = "patria_47";
		break;
		
		case "patria_47":
			dialog.text = "My friend, you are absolutely correct, the baron doesn't need to know the details. Enough has already happened: an attempt to take the life of the French king's representative, the attack on the diplomatic mission's ships, that is to say - on you, and most importantly: the de facto annexation of the island of Sint-Maarten! This is enough to justify military action against the Netherlands.";
			link.l1 = "War?!";
			link.l1.go = "patria_48";
		break;
		
		case "patria_48":
			dialog.text = "Exactly! My friend, the position of vice-admiral is not so far for you, do you understand? Imagine yourself at the talks in the Louvre in an admiral's uniform, and Louis XIV himself will accept such an honourable guest... We have to put the Dutch in their place! Stuyvesant will regret what he's done. Do you agree?";
			link.l1 = "I agree, Chevalier. The Dutch have to answer for their outrageous and vile actions.";
			link.l1.go = "patria_49";
		break;
		
		case "patria_49":
			dialog.text = "Excellent. I will notify the baron of our decision and send couriers to the French colonies immediately! And you, my friend, can rest after a long road, and please visit me tomorrow after nine in the morning. I will prepare a combat task for you.";
			link.l1 = "Very well, monseigneur. Allow me to excuse myself.";
			link.l1.go = "patria_50";
		break;
		
		case "patria_50":
			DialogExit();
			npchar.dialog.currentnode = "First time";
			LAi_SetHuberType(npchar);
			AddQuestRecord("Patria", "33");
			pchar.questTemp.Patria = "epizode_7";
			Patria_HunterBegin();
			pchar.quest.Patria_DiplomatTimeOver.over = "yes"; // снять таймер
			ChangeCharacterComplexReputation(pchar, "nobility", 1); // 14-add
			ChangeCharacterComplexReputation(pchar, "authority", 1);
			ChangeCharacterComplexReputation(pchar, "fame", 1);
		break;
		
		case "patria_51":
			dialog.text = "I wouldn't call it a war, more like forcing a peace in fact. And if Stuyvesant changes his mind, it will only make us happier. That's why now we have to show him that by attempting to claim the island of Sint-Maarten, he will lose much more than he will gain. That's where you'll focus your task, Charles.";
			link.l1 = "I'm listening.";
			link.l1.go = "patria_52";
		break;
		
		case "patria_52":
			dialog.text = "Sint-Maarten is a transshipment base for the Dutch ships going to Europe. The Company's ships regularly stay at the bay in Philipsburg. Until now, the waters were quite safe for them. Until now, captain!.. You will depart for the shores of Sint-Maarten and will be patrolling them and capturing trade ships of the Company\nFor transporting valuable goods, the Company utilises the east indiamans - hard, well-armed ships with large holds. Those will be your targets. Capture five such ships along with their goods and bring them as prizes to Casterville. After that, we will continue the negotiations with Stuyvesant, and perhaps, after counting up the losses, he will change his mind.";
			link.l1 = "The task is clear. Can I go?";
			link.l1.go = "patria_53";
		break;
		
		case "patria_53":
			dialog.text = "Go, my friend, and may luck follow your every footstep.";
			link.l1 = "...";
			link.l1.go = "patria_54";
		break;
		
		case "patria_54":
			DialogExit();
			npchar.dialog.currentnode = "First time";
			AddQuestRecord("Patria", "34");
			pchar.questTemp.Patria = "epizode_7_continue";
			Patria_HunterContinue();
		break;
		
		case "patria_55":
			pchar.questTemp.Patria.Hunter = sti(pchar.questTemp.Patria.Hunter)+1;
			if (sti(pchar.questTemp.Patria.Hunter) > 4) // все собрал
			{
				dialog.text = "You have completed the task, captain. Thank you for your excellent service! You ought to receive a part of the income from selling the trophies - two hundred thousand pesos.";
				link.l1 = "Glad to hear it, monsieur!";
				link.l1.go = "patria_57";
			}
			else
			{
				dialog.text = "So, you have only "+FindRussianQtyString(5-sti(pchar.questTemp.Patria.Hunter))+" Dutch ships left to bring to our port.";
				link.l1 = "Yes, Chevalier!";
				link.l1.go = "patria_56";
			}
		break;
		
		case "patria_56":
			DialogExit();
			AddQuestRecord("Patria", "35");
			AddQuestUserData("Patria", "sQty", 5-sti(pchar.questTemp.Patria.Hunter));
			DeleteAttribute(pchar, "questTemp.Patria.Hunter.GiveShip");
		break;
		
		case "patria_57":
			AddMoneyToCharacter(pchar, 200000);
			dialog.text = "And now, rest a bit, Charles. You've deserved it. And I will take on the negotiations with Stuyvesant - perhaps, he has realised that fighting us harms him much more than being our friend. Don't leave the city, I'll need you in a day or two.";
			link.l1 = "Very well, monsieur. I will await your further commands.";
			link.l1.go = "patria_58";
		break;
		
		case "patria_58":
			DialogExit();
			AddQuestRecord("Patria", "36");
			pchar.questTemp.Patria = "epizode_7_end";
			pchar.quest.Patria_siege_begin.win_condition.l1 = "Timer";
			pchar.quest.Patria_siege_begin.win_condition.l1.date.hour  = 9.00;
			pchar.quest.Patria_siege_begin.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 2);
			pchar.quest.Patria_siege_begin.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 2);
			pchar.quest.Patria_siege_begin.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 2);
			pchar.quest.Patria_siege_begin.win_condition.l2 = "location";
			pchar.quest.Patria_siege_begin.win_condition.l2.location = "Charles_town";
			pchar.quest.Patria_siege_begin.function = "Patria_SiegeBegin";
			bQuestDisableMapEnter = true;//закрыть карту
			pchar.GenQuest.MapClosedNoBattle = true;
			ChangeCharacterNationReputation(pchar, FRANCE, 15);
			ChangeCharacterComplexReputation(pchar, "nobility", 5); // 14-add
			ChangeCharacterComplexReputation(pchar, "authority", 5);
			ChangeCharacterComplexReputation(pchar, "fame", 5);
		break;
		
		case "patria_59":
			dialog.text = "Yes. It seems, Stuyvesant has begun to respond with military action in an alliance with Spain. A joint Dutch-Spanish squadron has besieged Saint-Christopher. Sentry forts every hour report to me of every one of their movements.";
			link.l1 = "A siege?";
			link.l1.go = "patria_60";
		break;
		
		case "patria_60":
			dialog.text = "Obviously. They didn't go on for a direct assault, and that's actually good. We need to act quickly, captain, while the enemy hasn't managed to blockade the whole island.";
			link.l1 = "What do we need to do?";
			link.l1.go = "patria_61";
		break;
		
		case "patria_61":
			dialog.text = "In Saint-Jones, on Antigua, based the English Navy squadron of Colonel Doily. Right now, he is visiting Sir Jonathan Fox. You have to pass by the enemy ships and get to Antigua. There, you will meet the colonel, hand him my letter and ask him for help.";
			link.l1 = "Do you think the colonel will agree to help us?";
			link.l1.go = "patria_62";
		break;
		
		case "patria_62":
			dialog.text = "I hope so. The letter should convince him that the reward for his help will be quite sizeable... Also, we need to send a letter to the captain of the 'Eclatant', currently near the shores of Guadelupa, he has to hurry to Saint-Christopher. The firing power of the 'Eclatant' will help us in the battle considerably. As you can't be in two places at once, our courier lugger will join your squadron - you must pass it undamaged through the circle of enemies, and it will depart for Guadelupe, while the 'Eclatant' hasn't gone to the South...";
			link.l1 = "I see. Go through the siege, escort the courier lugger and hurry to Saint-Jones to Colonel Doily with your letter.";
			link.l1.go = "patria_63";
		break;
		
		case "patria_63":
			dialog.text = "Precisely. Are you ready to accept another ship in your squadron?";
			if (GetCompanionQuantity(pchar) > 4)
			{
				link.l1 = "I will get rid of one ship and come back to you.";
				link.l1.go = "patria_63_1";
			}
			else
			{
				link.l1 = "Yes.";
				link.l1.go = "patria_64";
			}
		break;
		
		case "patria_63_1":
			DialogExit();
			pchar.questTemp.Patria = "epizode_8_wait";
		break;
		
		case "patria_64":
			dialog.text = "Excellent. Take the letter, the lugger is ready and awaiting your commands.";
			link.l1 = "Let's waste no time, Chevalier!";
			link.l1.go = "patria_65";
		break;
		
		case "patria_65":
			DialogExit();
			AddQuestRecord("Patria", "38");
			pchar.questTemp.Patria = "epizode_8_continue";
			GiveItem2Character(pchar, "Reserve_item_01");
			ChangeItemDescribe("Reserve_item_01", "itmdescr_Reserve_item_01_3");
			Patria_SiegeCreateSquadron();
		break;
		
		case "patria_66":
			dialog.text = "Yes-yes, my friend, I know all about your modesty. You are a true officer! And you will receive the reward, I assure you! I suppose, after the heavy battle, you'll need some rest? You have a whole week. Come to my room to talk in seven days - the city will prepare a reward for its hero.";
			link.l1 = "Yes, monsieur. May I go?";
			link.l1.go = "patria_67";
		break;
		
		case "patria_67":
			dialog.text = "Go and rest well. Later we will need to deal with serious issues - As you can see, a peace with the Dutch is impossible at this point. For now, the colonel and I will discuss some important questions.";
			link.l1 = "Then we'll meet in a week, Chevalier.";
			link.l1.go = "patria_68";
		break;
		
		case "patria_68":
			DialogExit();
			AddQuestRecord("Patria", "45");
			pchar.questTemp.Patria = "epizode_8_end";
			Patria_SiegeEnd();
			ChangeCharacterNationReputation(pchar, FRANCE, 20);
			ChangeCharacterComplexReputation(pchar, "nobility", 10); // 14-add
			ChangeCharacterComplexReputation(pchar, "authority", 10);
			ChangeCharacterComplexReputation(pchar, "fame", 10);
		break;
		
		case "patria_69":
			pchar.quest.Patria_BastionTimeOver.over = "yes"; //снять таймер
			dialog.text = "We've had a discussion with Colonel Doily and he agreed to help me. England will help us in the war against the Dutch. You and I need to strike back and restore justice - the isle of Sint-Maarten has to be returned to France. I assign this task to the best navy captain - you, Charles de Maure! The enemy hasn't yet recovered from their squadron's defeat, we will attack Philipsburg and take it\nThe battle won't be easy. First, we need to destroy the fort, then break the garrison's defense...(whispering) You will also need to make a forced march through the jungle to the salt deposit I told you about, and kill the enemies encamped there...";
			link.l1 = "The task is quite hard, Chevalier...";
			link.l1.go = "patria_70";
		break;
		
		case "patria_70":
			dialog.text = "I perfectly understand you, my friend. Your squadron will be strengthened. The governors of Basse-Terre and Saint-Pierre should have prepared one ship each - a frigate - by that time. You will only need to visit Guadelupa and Martinique and take these frigates under your command. If, of course, you want them yourself - I will not insist on your choice of ships. I also give you a subsidy in the form of 20 000 peso to buy provision and equipment for your flagship. Here, take it...";
			link.l1 = "Very well, monsieur.";
			if (CheckAttribute(pchar, "questTemp.Patria.Ecliaton_Fail")) link.l1.go = "patria_71";
			else link.l1.go = "patria_71_1";
		break;
		
		case "patria_71_1":
			dialog.text = "Also, as usual, the ship 'Eclatant' is under your command. It has been repaired and equipped, waiting in the roadstead, and after talking to the captain, you will be able to take it at any moment.";
			link.l1 = "Excellent!";
			link.l1.go = "patria_71";
			pchar.questTemp.Patria.Ecliaton_Bastion = "true";
			sld = characterFromId("Ecliaton_Cap");
			sld.dialog.currentnode = "ecliaton_cap_7";
			sld.DeckDialogNode = "ecliaton_cap_7";
		break;
		
		case "patria_71":
			AddMoneyToCharacter(pchar, 20000);
			dialog.text = "We can't waste any time, captain. As my spies have informed me, the Dutch understand the danger to Sint-Maarten, and they intend to strengthen its defenses. But you still have two months. You have to finish the task in time!";
			link.l1 = "I will... (whispering) Where is the salt deposit on Sint-Maarten? It's not marked on any map of the island...";
			link.l1.go = "patria_72";
		break;
		
		case "patria_72":
			dialog.text = "(whispering) When you assault the city, interrogate the viceroy of Philipsburg, mynheer Martin Tomas, he'll tell you. That Dutchman is a coward and won't resist you, I guarantee it.";
			link.l1 = "I see. Then may I depart?";
			link.l1.go = "patria_73";
		break;
		
		case "patria_73":
			dialog.text = "Wait a minute, Charles. You haven't received your reward for saving Saint-Christopher yet. Take these chests of gold from the people of the city, as well as our sincerest gratitude, which no sum of money can express!";
			link.l1 = "Thank you, monsieur!";
			link.l1.go = "patria_74";
		break;
		
		case "patria_74":
			TakeNItems(pchar, "chest", 10);
			Log_Info("You've received 10 chests of doublons");
			PlaySound("interface\important_item.wav");
			dialog.text = "Now, you can go. Good luck, captain! We're all waiting for your victory!";
			link.l1 = "Goodbye, Chevalier.";
			link.l1.go = "patria_75";
		break;
		
		case "patria_75":
			DialogExit();
			sTemp = "";
			if (CheckAttribute(pchar, "questTemp.Patria.Ecliaton_Bastion")) sTemp = "The ship-of-the-line 'Eclatant' will also be under my command.";
			AddQuestRecord("Patria", "48");
			AddQuestUserData("Patria", "sText", sTemp);
			pchar.questTemp.Patria = "epizode_9_continue";
			SetFunctionTimerCondition("Patria_BastionSturmTimeOver", 0, 0, 62, false);
			// вернуть Синт-Маартен в норму
			int n = FindIsland("SentMartin");
			Islands[n].reload.l1.radius = 600.0;
			LocatorReloadEnterDisable("Marigo_ExitTown", "reload3", false); // открыть городские ворота
			sld = CharacterFromID("Marigo Fort Commander");
			LAi_SetImmortal(sld, false);
			Character_SetAbordageEnable(sld, true);
			// атрибут квестовой высадки десанта
			pchar.TempPerks.QuestTroopers = true;
		break;
		
		case "patria_76":
			dialog.text = "Who would have thought only a year ago that you would be promoted to the rank of vice-admiral, my friend? I can only guess how proud your father will be when news of this reach France!";
			link.l1 = "My dear dad will be most happy.";
			link.l1.go = "patria_77";
		break;
		
		case "patria_77":
			dialog.text = "You've earned your position in the fleet! Sint-Maarten has been returned to France, Stuyvesant has learned a hard lesson. That was a great victory! But we must not stop, we can't let the Dutch rest for a minute. They will be held responsible for their betrayal! Colonel Doily is in Port-Royale right now, preparing his navy squadron: we are going to break our enemy's spine by striking at Curacao. But that will be later, for now we have to kill two birds with one stone, Charles\nThe Company didn't earn all of their untold wealth with trade. The main source of the Dutch incomes in the region is the slave work in their plantations. If you're not aware, Charles: Holland is the biggest slave-owning and slave-trading nation. East-Indiamen carrying the 'black ivory' regularly come to Curacao from West Africa. And I happen to know something about it, unfortunately for Stuyvesant\nRight now two Dutch East-Indiamen are going to the Caribbean from Guinea. Their holds are full of black prisoners. In ten days or around that the caravan will be going around the isle of Trinidad in the direction of Curacao. Your task is to find the caravan and capture these two East-Indiamen and their cargo. You have to destroy escorting ships, and bring the slaves to our ally, Colonel Doily, in Jamaica. It is very important Charles, that way we'll earn his trust... I hope you understand\nI'm sorry not to leave you any time to rest, but this task is important and delicate, and I can only entrust you with it.";
			link.l1 = "Service is no sugar, Chevalier. I know it better than anyone. I will prepare my ship and depart as soon as I can.";
			link.l1.go = "patria_78";
		break;
		
		case "patria_78":
			dialog.text = "I wish you good winds and fair travel, vice-admiral. And when you return to Saint-Christopher, our mutual familiar, Monsieur Noel Forget, will have finished his inspection of Philipsburg, and I will make sure that part of the trophies they take from the Dutch will go to you personally.";
			link.l1 = "It will make me most thankful, Chevalier. May I go?";
			link.l1.go = "patria_79";
		break;
		
		case "patria_79":
			dialog.text = "Go. Best of luck to you, my friend!";
			link.l1 = "...";
			link.l1.go = "patria_80";
		break;
		
		case "patria_80":
			DialogExit();
			Items[sti(pchar.EquipedPatentId)].TitulCur = 5; 
        	Items[sti(pchar.EquipedPatentId)].TitulCurNext = 0;
			pchar.questTemp.Patria = "epizode_10_start";
			AddQuestRecord("Patria", "52");
			Patria_SlaveShipsStart();
			ChangeCharacterNationReputation(pchar, FRANCE, 15);
			ChangeCharacterComplexReputation(pchar, "nobility", 10); // 14-add
			ChangeCharacterComplexReputation(pchar, "authority", 10);
			ChangeCharacterComplexReputation(pchar, "fame", 10);
		break;
		
		case "patria_81":
			dialog.text = "Excellent! You don't know the word 'impossible', Charles. I used to think your brother was the best navy officer in the Caribbean, but he has much to learn from you, if you excuse me this crude comparison. I think you already know who will go to our dear colonel to take part in the assault on Willemstadt.";
			link.l1 = "Absolutely not, monseigneur! How could I know!";
			link.l1.go = "patria_82";
		break;
		
		case "patria_82":
			dialog.text = "Ah, your famous sense of humour, my dear friend! Ha-hah! Of course, it will be you, vice-admiral. The most worthy of all. Are you ready?";
			link.l1 = "Of course, Chevalier. All I need is some repair, some equipment - and I'm ready to go.";
			if (CheckAttribute(pchar, "questTemp.Patria.Ecliaton_Fail")) link.l1.go = "patria_83";
			else link.l1.go = "patria_83_1";
		break;
		
		case "patria_83_1":
			dialog.text = "Don't forget to take the 'Eclatant' under your command. It has been repaired and equipped, waiting for you in the docks. Marquis Uber Dasser is already growing impatient and waiting to go into battle with you again.";
			link.l1 = "Great. A mighty ship with long-range culverines is exactly what I need to bombard the fort.";
			link.l1.go = "patria_83";
			pchar.questTemp.Patria.Ecliaton_Curacao = "true";
			sld = characterFromId("Ecliaton_Cap");
			sld.dialog.currentnode = "ecliaton_cap_11";
			sld.DeckDialogNode = "ecliaton_cap_11";
		break;
		
		case "patria_83":
			dialog.text = "Wait a minute, Charles. Our friend, Baron Forget, has brought news for you from Sint-Maarten.";
			link.l1 = "...";
			link.l1.go = "patria_84";
		break;
		
		case "patria_84":
			DialogExit();
			sld = characterFromId("Noel");
			sld.dialog.currentnode = "noel_25";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.5);
			ChangeCharacterComplexReputation(pchar, "nobility", 2); // 14-add
			ChangeCharacterComplexReputation(pchar, "authority", 2);
			ChangeCharacterComplexReputation(pchar, "fame", 2);
		break;
		
		case "patria_85":
			dialog.text = "I have news for you from Paris. Your appointment for the position of vice-admiral has been signed by the King. You will receive the relevant papers. So, I congratulate you!";
			link.l1 = "Thank you, monsieur! Glad to serve France and the King!";
			link.l1.go = "patria_86";
		break;
		
		case "patria_86":
			dialog.text = "And now, I'm sure, you'll need to rest well. I give you a month, and make sure to spend it well. No work, no worries. Give all the work to your officers and rest well. You may use the rooms in my residence. The servants will make your vacation most comfortable. We will meet again in a month - and I will have a delicate matter to discuss.";
			link.l1 = "Very well, Chevalier. Goodbye!";
			link.l1.go = "patria_87";
		break;
		
		case "patria_87":
			DialogExit();
			AddQuestRecord("Patria", "65"); // далее коллизия Пуанси-Инспектор-Шарль
			pchar.questTemp.Patria = "epizode_12_start";
			ChangeCharacterNationReputation(pchar, FRANCE, 15);
			Patria_CondotierStart();
			ChangeCharacterComplexReputation(pchar, "nobility", 15); // 14-add
			ChangeCharacterComplexReputation(pchar, "authority", 15);
			ChangeCharacterComplexReputation(pchar, "fame", 15);
		break;
		
		case "patria_88":
			dialog.text = "Yes, Charles. I thought I would manage this myself, but... alas, I must ask to make use of your talents once again. But first, I need to give you something: three hundred thousand pesos and five chests of doublons. This is a large part of the contribution Stuyvesant paid me as per the deal. I suppose you've earned all of this, since you've done most of the work. Accept it. Are you satisfied, my friend?";
			link.l1 = "Money has never hurt anyone, monsieur, I've learned that lesson well.";
			link.l1.go = "patria_89";
		break;
		
		case "patria_89":
			AddMoneyToCharacter(pchar, 300000); 
			TakeNItems(pchar, "chest", 5);
			dialog.text = "Ah, vice-admiral, I hope you're not offended by what happened in the past?.. You are now a hero of your nation, did you know? How do you feel in this new position? Remember: many worthy officers spent decades climbing the rank ladder, but without an exprerienced hand... they are left in the position of commander. But you, my friend, have a unique ability to always accomplish the impossible! And you have a friend in the high places, who is also your guardian.";
			link.l1 = "Thank you for these kind words, your Excellency. I have the feeling I've achieved almost everything in this region. With your help, of course. I suppose, now I can deal with my own issues in peace? I must think about my family.";
			link.l1.go = "patria_90";
		break;
		
		case "patria_90":
			dialog.text = "You want to get married, Charles? Ah-ha-ha! Point at any beautiful woman in Paris - and she will be yours at once! But, alas, that will have to wait. I need you here, my friend, at least for now.";
			link.l1 = "It seems, France is stronger than ever in the Archipelago. An alliance with the English, a truce with the Company. There are no problematic... 'levasseurs' left. Right?";
			link.l1.go = "patria_91";
		break;
		
		case "patria_91":
			dialog.text = "Nations, much like people, always wish for more, no matter how much they have... And we indeed have a new 'levasseur', vice-admiral...";
			link.l1 = "Really? And who is it?";
			link.l1.go = "patria_92";
		break;
		
		case "patria_92":
			dialog.text = "It is our old mutual familiar, Baron Noel Forget. Do you remember why he came here?";
			link.l1 = "Hmm... You said something about the West-Indies trade Company. Paris decided to create the same organisation as the Dutch?";
			link.l1.go = "patria_93";
		break;
		
		case "patria_93":
			dialog.text = "Precisely. Analogous to the Dutch Company. But to make one from scratch is very hard. You see, Stuyvesant had decades of trade with different continents in his experience, a developed net of agents and a mighty fleet of trade ships. France doesn't have that, and, if you didn't know, Charles, the King is experiencing a serious lack of funds right now. They wish to fix the financial situation of the metropolis by steering trade here, but they don't understand what we'll have to face\nRivalry of both the English and the Dutch, the territorial ambitions of the Spanish, piracy flourishing like never before. Every trade fluyt needs to be escorted by a navy ship, or it will be risk to never get it to its destination. And we don't have a mighty fleet like the East-Indiamen of the Dutch, or the Galleons like those of the Spanish.";
			link.l1 = "But did you explain all of this to the baron? About pirates too?";
			link.l1.go = "patria_94";
		break;
		
		case "patria_94":
			dialog.text = "Of course I did. And about the banishment of pirates from Tortuga after your mission of removing Levasseur, which the pirates haven't forgotten and and always will hold a grudge on us. I've organised meetings with various people who confirmed my worries, but alas, that had no effect on the baron. He was sent here by the ministers, and he owes to them... That's just how it is.";
			link.l1 = "Huh...";
			link.l1.go = "patria_95";
		break;
		
		case "patria_95":
			dialog.text = "And let's not hide the fact that a trade company in the Archipelago, with direct control from Paris... you and I, vice-admiral... we don't it need here.";
			link.l1 = "I understand.";
			link.l1.go = "patria_96";
		break;
		
		case "patria_96":
			dialog.text = "You see, my friend, I am being extremely honest with you... So, I hoped with all my heart that Monsieur Forget would change his mind on creating this trade company, but... that didn't happen. I've wasted all of my influence on the baron, and now you need to enter the game.";
			link.l1 = "Hmm... Just like with Levasseur?..";
			link.l1.go = "patria_97";
		break;
		
		case "patria_97":
			dialog.text = "Oh, who do you take me for, Charles?! The baron is an influential figure, a friend of the Minister of Finance! And besides, physically removing him will achieve nothing: a new politician will simply be sent from Paris. We need to destroy the idea of organising such a company in the first place, do you understand, Charles? So that the baron would return to France and report that it would be financially risky, nonsensical...";
			link.l1 = "Do you have an idea, monsieur?";
			link.l1.go = "patria_98";
		break;
		
		case "patria_98":
			dialog.text = "Alas, no, Charles. I've tried everything. I've scared them with lack of ships and money, the Dutch, pirates... No effect.";
			link.l1 = "It seems, we need something more serious than mere words. Hm... Pirates, you say?..";
			link.l1.go = "patria_99";
		break;
		
		case "patria_99":
			dialog.text = "I see you have an idea, my friend? I had no doubts. You have a brilliant mind. Persuade this baron, and I will make sure your father has enough money to fill your entire house with riches worthy of the Louvre. I promise, Charles.";
			link.l1 = "Very well, Chevalier. The task is clear.";
			link.l1.go = "patria_100";
		break;
		
		case "patria_100":
			dialog.text = "I swear, Charles, you will not regret it if you succeed. You can be sure of that. Have I ever betrayed you, my friend?";
			link.l1 = "Absolutely not, monsieur. Where can I find the Baron?";
			link.l1.go = "patria_101";
		break;
		
		case "patria_101":
			dialog.text = "Right now, he's in Port-au-Prince. He finds the endless fields and valleys of Hispaniola very lovely, as he said...";
			link.l1 = "Great. Now, allow me to excuse myself.";
			link.l1.go = "patria_102";
		break;
		
		case "patria_102":
			DialogExit();
			AddQuestRecord("Patria", "67");
			pchar.questTemp.Patria = "epizode_12_pirates";
			Patria_CondotierSail();
		break;
		
		case "patria_103":
			dialog.text = "Precisely that. The baron told me everything. After everything he's been through... However, you can explain things clear, like no one else, vice-admiral! I should learn that from you!";
			link.l1 = "I've learned much from you, Chevalier.";
			link.l1.go = "patria_104";
		break;
		
		case "patria_104":
			dialog.text = "My friend, I owe you. I assure you that your dear father will have everything that he needs or ever will need in his life, and your family house will be the best in the province... and one of the best in France. Besides, I will pay you 100 000 pesos - I hope, it will cover your debt with the pirates...";
			link.l1 = "That's lovely to hear, monseigneur!";
			link.l1.go = "patria_105add";
		break;
		
		case "patria_105add":
			AddMoneyToCharacter(pchar, 100000); 
			dialog.text = "I also prepared a special present for you. I'm sure, you'll understand the value of this item and the sincerity of my gratitude for your loyal service! So, Vice-Admiral Charles de Maure, I give you my personal ceremonial sword of the Maltese Order! This precious weapon will fit your uniform, I should think! If you decide to return to Paris, Baron Noel Forget has promised to present you to the King - you should come to him in full parade: wearing your uniform and bearing this excellent weapon! Even more glorious career opportunities in the French navy await you!";
			link.l1 = "This sword is unmatched in its beauty! Thank you, monseigneur, I truly don't deserve this honour...";
			link.l1.go = "patria_105";
		break;
		
		case "patria_105":
			ref itm = ItemsFromID("blade_36");
			itm.picIndex = 16;
			itm.picTexture = "ITEMS_17";
			itm.price = 10000;
			itm.Weight = 3.0;
			itm.lenght = 1.05;
			itm.curve = 1.0;
			itm.Balance = 1.9;
			GiveItem2Character(pchar, "blade_36");
			Log_Info("You've received the Maltese Sword");
			PlaySound("interface\important_item.wav");
			dialog.text = "You do! And while you're here, big changes await you. Good changes. Vice-Admiral Charles de Maure, I appoint you the Governor of Sint-Maarten!";
			link.l1 = "Phah! Did I hear you correctly?";
			link.l1.go = "patria_106";
		break;
		
		case "patria_106":
			ChangeCharacterComplexReputation(pchar, "nobility", 12); // 14-add
			ChangeCharacterComplexReputation(pchar, "authority", 12);
			ChangeCharacterComplexReputation(pchar, "fame", 12);
			dialog.text = "Yes, my friend. You are now the governor of Sint-Maarten, which you've protected so diligently.";
			link.l1 = "Chevalier, allow me to refuse this honour. I don't wish to be tied to this one poor island! And all these domestic issues... That's not what I was meant to do!";
			link.l1.go = "patria_107";
		break;
		
		case "patria_107":
			dialog.text = "I don't accept the refusal. My friend, don't afraid: you will live as before. All the boring things will be dealt with by the current acting governor. You will be the de facto governor. Charles, don't you really understand why specifically you were appointed to govern Sint-Maarten? Now is the right moment for it, when nobody will ask any questions. I need one of MY men as the governor here, do you see what I mean?";
			link.l1 = "The salt mine?";
			link.l1.go = "patria_108";
		break;
		
		case "patria_108":
			dialog.text = "Of course! And the second bit of good news: from now, on the 15th of every month, you will receive part of the profit from the mine as well as from Doily's trade. Your passive income will be 100 000 peso per month.";
			link.l1 = "Hah! I'm glad to hear that! Thank you, chevalier. Well, if I won't be tied to sit here, I accept the governorship. And what if I decide to sail to France?";
			link.l1.go = "patria_109";
		break;
		
		case "patria_109":
			dialog.text = "When you decide - you will go, and I, although very disappointed, will find a replacement for you. But that's not all. I have a letter from your father here. Take a look.";
			link.l1 = "From my father? I'm thrilled!.. Very good, monsieur, deal. May I go now? I wish to read the letter... No new tasks for me?";
			link.l1.go = "patria_110";
		break;
		
		case "patria_110":
			dialog.text = "Not now, governor, but if I find some work, I know where to find you. Good luck, Charles!";
			link.l1 = "And to you, Chevalier!";
			if (pchar.questTemp.Patria == "epizode_12_baronwin") link.l1.go = "patria_119";
			else link.l1.go = "patria_111";
		break;
		
		case "patria_111":
			DialogExit();
			AddQuestRecord("Patria", "77");
			CloseQuestHeader("Patria");
			pchar.questTemp.Patria = "end"; // конец линейки
			pchar.questTemp.Patria.Governor = "true"; // Шарль губернатор
			AddQuestRecordInfo("Sharlie_Father_1", "1");
			sld = CharacterFromID(pchar.questTemp.Patria.SpanishID);
			SetCharacterRemovable(sld, true);
		break;
		
		case "patria_112":
			dialog.text = "God dammit, what a disaster! Now we have more issues to deal with. Are you responsible for this, Charles? Tell me the truth. Was this an accident?";
			link.l1 = "Well, something went wrong...";
			link.l1.go = "patria_113";
		break;
		
		case "patria_x112":
			dialog.text = "God dammit, what a disaster! Now we have more issues to deal with. The baron has chosen a very bad place to die! Are you sure you didn't help him depart this world?";
			link.l1 = "What are you saying, Chevalier?! Of course not!";
			link.l1.go = "patria_x113";
		break;
		
		case "patria_y112":
			dialog.text = "God dammit, what a disaster! Now we have more issues to deal with. Are you sure you didn't help him depart this world?";
			link.l1 = "What are you saying, Chevalier?! Of course not!";
			link.l1.go = "patria_y113";
		break;
		
		case "patria_x113":
			dialog.text = "Alright. Well then, my friend, maybe not everything is ruined. A fever is a fever, right? And until a new inspector from the ministry has arrived, we'll clear up here and will be waiting for our guests well-armed... And now, Charles, we need to close all our contacts. I hope you understand why?";
			link.l1 = "Of course.";
			link.l1.go = "patria_114";
		break;
		
		case "patria_y113":
			dialog.text = "Alright. Well then, my friend, maybe not everything is ruined. Battles in the Caribbean are to be expected, right? And until a new inspector from the ministry has arrived, we'll clear up here and will be waiting for our guests well-armed... And now, Charles, we need to close all our contacts. I hope you understand why?";
			link.l1 = "Of course.";
			link.l1.go = "patria_114";
		break;
		
		case "patria_113":
			dialog.text = "Alright. Well then, my friend, maybe not everything is ruined. Pirates are pirates, right? And until a new inspector from the ministry has arrived, we'll clear up here and will be waiting for our guests well-armed... And now, Charles, we need to close all our contacts. I hope you understand why?";
			link.l1 = "Of course.";
			link.l1.go = "patria_114";
		break;
		
		case "patria_114":
			dialog.text = "In any case, my friend, you've done everything you could. And that's better than nothing. I'm glad that fate has brought us together. You may keep your position, and I'm sure a great career awaits you in France. And, I think it is time for you to come back to Paris. Here, a letter from your father. Take it.";
			link.l1 = "My father? That is most welcome!.. Alright, monseigneur, I understand. No contacts, full secrecy, and as soon as I can - go to Paris. May I go now? I wish to read the letter...";
			link.l1.go = "patria_115";
		break;
		
		case "patria_115":
			dialog.text = "Go, Charles. Good luck!";
			link.l1 = "And to you, Chevalier!";
			link.l1.go = "patria_116";
		break;
		
		case "patria_116":
			DialogExit();
			AddQuestRecord("Patria", "78");
			CloseQuestHeader("Patria");
			pchar.questTemp.Patria = "end"; // конец линейки
			AddQuestRecordInfo("Sharlie_Father_1", "1");
			sld = CharacterFromID(pchar.questTemp.Patria.SpanishID);
			SetCharacterRemovable(sld, true);
		break;
		
		case "patria_117":
			dialog.text = "Precisely. You can explain things clear like no one else, vice-admiral! I should learn that from you!!";
			link.l1 = "I have learned much from you, chevalier.";
			link.l1.go = "patria_118";
		break;
		
		case "patria_118":
			dialog.text = "My friend, I owe you. I assure you that your dear father will have everything that he needs or ever will need in his life, and your family house will be the best in the province... and one of the best in France. Besides, I will pay you 100 000 pesos - I hope, it will cover your travel expenses, and will allow you to get a rest.";
			link.l1 = "That's lovely to hear, monseigneur!";
			link.l1.go = "patria_105add";
		break;
		
		case "patria_119":
			DialogExit();
			AddQuestRecord("Patria", "87");
			pchar.questTemp.Patria = "europe";
			pchar.questTemp.Patria.Governor = "true"; // Шарль губернатор
			AddQuestRecordInfo("Sharlie_Father_1", "1");
			SetFunctionTimerCondition("Patria_EuropeTime", 0, 0, 175+rand(10), false); // таймер
		break;
		
		case "patria_prison":
			dialog.text = "How could you, Charles! How could you... do this to me?!";
			link.l1 = "Ahem...";
			link.l1.go = "patria_prison_1";
		break;
		
		case "patria_prison_1":
			dialog.text = "I know it was you! You did that! Don't deny it! Without your help, Baron Forget would have never got neither the reports from the mine's manager, nor the location of the mine, nor even the documents of Peter Stuyvesant. Your name was not heard there, but let me tell you, I know for sure: it was you. Why, Charles?.. Just answer me... Why? Michel? A million pesos? Levasseur? Or perhaps the position of the Governor General?";
			link.l1 = "I can only repeat what I've already told you: I've learned much from you, Chevalier! Alas, you can teach me no more.";
			link.l1.go = "patria_prison_2";
		break;
		
		case "patria_prison_2":
			DialogExit();
			chrDisableReloadToLocation = false;
			bDisableFastReload = true;//закрыть переход
			LAi_SetActorType(npchar);
			SetFunctionTimerCondition("Patria_EuropePuancieClear", 0, 0, 5, false); // таймер
			pchar.quest.Patria_Europe_final.win_condition.l1 = "location";
			pchar.quest.Patria_Europe_final.win_condition.l1.location = "Charles_town";
			pchar.quest.Patria_Europe_final.function = "Patria_EuropeFinal";
		break;
		
		case "patria_patentfail":
			DialogExit();
			pchar.questTemp.Patria = "fail";
			CloseQuestHeader("Patria");
			// убрать Эклятон, если есть
			if (CheckAttribute(pchar, "questTemp.Patria.Ecliaton"))
			{
				sld = characterFromId("Ecliaton_Cap");
				RemoveCharacterCompanion(pchar, sld);
				sld.lifeday = 0;
				DeleteAttribute(pchar, "questTemp.Patria.Ecliaton");
			}
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}