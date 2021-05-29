// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("What do you want? Ask away.", "I am listening to you, what's the question?"), "It is the second time you are trying to ask...", "It is the third time you are again trying to ask...",
                          "When is it going to end?! I am a busy man, working on the colony's matters and you are still trying to ask something!", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("I have changed my mind...", "Not now. Wrong place and time."), "True... But later, not now...",
                      "I'll ask... But a bit later...", "I am sorry, " + GetAddress_FormToNPC(NPChar) + "...", npchar, Dialog.CurrentNode);			  
			link.l1.go = "exit";
			//Jason, Португалец
			if (CheckAttribute(PChar, "questTemp.Portugal") && pchar.questTemp.Portugal == "ToGovernor")
			{
				link.l1 = "Your Grace, I have absolutely excellent and urgent news for you! I have captured Bartolomeo the Portuguese, the bastard is under guard and looking for a fair trial! And I am looking for a modest gratitude of the Company...";
				link.l1.go = "Portugal";
			}
			//Португалец
			
			// Addon-2016 Jason ФМК-Сент-Кристофер
			if (CheckAttribute(PChar, "questTemp.FMQN") && pchar.questTemp.FMQN == "governor")
			{
				link.l1 = "You insisted on seeing me, mynheer governor...";
				link.l1.go = "FMQN";
			}
			if (CheckAttribute(PChar, "questTemp.FMQN") && pchar.questTemp.FMQN == "hol_battle_complete")
			{
				link.l1 = "I am here because of matter about the English spies, mynheer governor...";
				link.l1.go = "FMQN_7";
			}
		break;

		case "Cupture_after":
            dialog.text = RandPhraseSimple("You have taken everything already. What else do you want?", "Is there anything left that you didn't grab?");
            link.l1 = RandPhraseSimple("Just looking around...", "Just checking, I might forget to take something...");
            link.l1.go = "exit";
            NextDiag.TempNode = "Cupture_after";
		break;
		
		//Jason, Португалец
		case "Portugal":
			dialog.text = "Bartolomeo... Bart the Portuguese is in my town?! Alive?!!";
			link.l1 = "He is, your Grace and he is under the reliable guard. I will hand him to you after I receive a bill for Bart's head which was promised by the Company. Golden doubloons would be fine too...";
			link.l1.go = "Portugal_1";
		break;
		
		case "Portugal_1":
			dialog.text = "Bill, doubloons? Are you crazy?! What were you thinking about while taking this beast to my town?! If he is here than his frigate is not far from the island and its crew can be in the town itself, just right now!";
			link.l1 = "I have killed those who were with him, don't know about others, but it doesn't really matter I suppose because Bartolomeo is...";
			link.l1.go = "Portugal_2";
		break;
		
		case "Portugal_2":
			dialog.text = "It does! Don't you really understand what you have done?! The 'Albatross' is near the island and you have captured the pirate whose brutality scares even his own bloodthirsty people! Get away from here! Get away from the island! And take this monster with you!";
			link.l1 = "But listen, what about the promised reward and...";
			link.l1.go = "Portugal_3";
		break;
		
		case "Portugal_3":
			dialog.text = "I don't want to watch my city burning because of your greed and the Company's vengefulness! There are only fresh recruits in my fort and half of them will run away as soon they learn who and why is attacking their ravelins! And then the slaughter will start... I am not going to risk it, do you hear me?! Get lost and deliver him to Curacao yourself if the Company wants his head that bad!\nDo it immediately before it's too late! And you may do with him whatever you want, even throw him out of your ship deck, just don't do it in my city!\nHans! Hans, where are you, you lazy idiot! Fetch me a valerian potion or something and anyone, for the God's sake, please turn this adventurer out of my residence!";
			link.l1 = "But your Grace...";
			link.l1.go = "Portugal_4";
		break;
		
		case "Portugal_4":
			DialogExit();
			DoQuestReloadToLocation("Marigo_town", "reload", "reload3_back", "PortugalOutResidence");
		break;
		
		// Addon-2016 Jason ФМК-Сент-Кристофер
		case "FMQN":
			dialog.text = "Very well! Tell me captain, did you encounter any English military or trade vessels on you approach to our island?";
			link.l1 = "No, mynheer. I saw neither military, nor trade vessels under English flag within your waters.";
			link.l1.go = "FMQN_1";
		break;
		
		case "FMQN_1":
			dialog.text = "I see. For how long do you expect to stay here?";
			link.l1 = "Three days or so...";
			link.l1.go = "FMQN_2";
		break;
		
		case "FMQN_2":
			dialog.text = "In that case, I have an offer for you. According to our intelligence, there is a risk of sending the English spies here. I will give ten thousand pesos as an award for any information regarding suspicious vessels and people within the island, in the town, its vicinity, on the shores, etc. The award will be significally increased in case of assisting the authorities in detaining or eliminating an enemy\nEvery civilian captain is welcome to take a part in investigation and to raid the local shores and jungle in a searching of the spies\nIt's possible that you'll encounter our military corvette, the Zeepard, don't be afraid, it is on the patrol. You are free to address its captain in case you find the Brits.";
			link.l1 = "Alas, your Excellence, but I am here with only peaceful trading intentions. I will have to leave this island as soon as I resupply and finish my business here.";
			link.l1.go = "FMQN_3";
			link.l2 = "A tempting offer! I think, I'll take a part and raid the waters and shores of your island. I might even stay here for a while.";
			link.l2.go = "FMQN_5";
		break;
		
		case "FMQN_3":
			dialog.text = "It's just information for noting, captain. No pressure. You know who to address to in case you see anything suspicious.";
			link.l1 = "Very well, mynheer, I got it. Farewell!";
			link.l1.go = "FMQN_4";
		break;
		
		case "FMQN_4":
			DialogExit();
			pchar.questTemp.FMQN = "way_eng_1";
			AddQuestRecord("FMQ_Nevis", "8");
			chrDisableReloadToLocation = false;
			FMQN_SetSoldiersInCave();
		break;
		
		case "FMQN_5":
			dialog.text = "Splendid, captain! Since you are that serious, make sure to talk to our commandant too. He is responsible for catching the spies and he could give you an additional information.";
			link.l1 = "Fine, mynheer. I'll go see him.";
			link.l1.go = "FMQN_6";
		break;
		
		case "FMQN_6":
			DialogExit();
			pchar.questTemp.FMQN = "way_div";
			AddQuestRecord("FMQ_Nevis", "9");
			chrDisableReloadToLocation = false;
		break;
		
		case "FMQN_7":
			dialog.text = "We've been waiting for you, mynheer "+GetFullName(pchar)+". Let me express our gratitude for your actions in eliminating a dangerous English raiding party. Accept these ten thousand pesos and a very special reward - the half a year license of the Dutch West Indian Company. This is an extremely valuable document, I hope you know that?";
			link.l1 = "Of course! Half a year license - this is big for sure.";
			link.l1.go = "FMQN_8";
		break;
		
		case "FMQN_8":
			dialog.text = "Please, take your reward. Besides, you can count on a gratitude of all Dutch citizens and authorities. You are a sensation in Philipsburg, we'd be glad to see you again.";
			link.l1 = "Hearing such warm words is valuable more than license. Thank you, it was a pleasure. And now, I should keep my way. Goodbye!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("FMQN_HollandBattleComplete");
		break;
		
		// Jason НСО
		case "tomas":
			dialog.text = "We surrender! In the name of all that is holy, I beg you, don't loot and maraud Philipsburg and its citizens! I'm ready to listen to your demands!";
			link.l1 = "Do not worry about the citizens, mynheer. Subjects of the French Crown should'n afraid of French soldiers.";
			link.l1.go = "tomas_1";
		break;
		
		case "tomas_1":
			dialog.text = "The French Crown?";
			link.l1 = "Exactly. This island belongs to France, and you are only renters here. Impudent renters, who believed this island could be their property. From today, Dutch authority in Sint Maarten has come to an end. Is it clear?";
			link.l1.go = "tomas_2";
		break;
		
		case "tomas_2":
			dialog.text = "But ... But what will happen to us, with the Dutch soldiers who surrendered to you, and the wounded? And what...";
			link.l1 = "And that will depend only on you, mynheer Thomas. If you do me a favour, then I will allow all those who gave up to take their wounded and depart from here on a ship or ships that we will find in the docks, to Curacao, to mynheer Stuyvesant. Otherwise, you are will be kept in the holds of my ships and casemates of Saint Kitts. Also, some important Dutch officials will have to be hanged, just to make sure that Stuyvesant will lose his interest in conquering our colonies...";
			link.l1.go = "tomas_3";
		break;
		
		case "tomas_3":
			dialog.text = "(stuttering) Wha... What... about wh...at k-kind of  f-fa... vour?";
			link.l1 = "In the depths of the island lays a bone of contention - a salt mine. I know that there are not only miners and slaves, but also Dutch soldiers, armed to the teeth. They must be from the Company Guard, aren't they, mynheer? I must either offer them to surrender, or to use force in case of refusal. I need a guide who will show the way to the mine. Find me such a guide.";
			link.l1.go = "tomas_4";
		break;
		
		case "tomas_4":
			dialog.text = "S-Salt....m-mine?";
			link.l1 = "Exactly. Don't be afraid, mynheer Thomas, if the guards of the mine are wise enough to give up their arms, I will give them an opportunity to leave the island. I don't need unnecessary bloodshed. Don't worry, your conscience will be clear: even if you don't tell me where the mine is, the island of Sint Maarten is small enough that I can find the mine without your help, I just don't want to waste my time, rambling over thickets and marshes. So this deal is more profitable to you than it is to me.";
			link.l1.go = "tomas_5";
		break;
		
		case "tomas_5":
			dialog.text = "F-fi...ne, I will tell you how to get to the mine, b-but you must g-gi...ve me your word that all... all of us will leave this island!";
			link.l1 = "I give you a word of an officer and a nobleman.";
			link.l1.go = "tomas_6";
		break;
		
		case "tomas_6":
			dialog.text = "In Grand Case bay, by... at its far edge, near the water, there are ... there are stones. There ... there, behind them, along the shoreline, there is a passage along the water, there ... it is shallow there, waist-deep or less. You need to go around the rock and you will get to a big beach, where ... where you can't dock your ship because of the reefs around it. From this beach there is a path directly ... to ... to the mine.";
			link.l1 = "Excellent. I'm setting off. And you, Mynher, will remain here under diligent watch of my soldiers until I'll return.";
			link.l1.go = "tomas_7";
		break;
		
		case "tomas_7":
			DialogExit();
			SetReturn_Gover_Dialog_Exit(NPChar);
			LAi_SetActorType(npchar);
			pchar.quest.Patria_BastionGate.win_condition.l1 = "location";
			pchar.quest.Patria_BastionGate.win_condition.l1.location = "Shore40";
			pchar.quest.Patria_BastionGate.function = "Patria_BastionShore";
			AfterTownBattle();
			AddQuestRecord("Patria", "50_1");
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

