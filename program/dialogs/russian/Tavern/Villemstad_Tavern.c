// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat("All the rumors of "+ GetCityName(npchar.city) +" at your service. What would you like to find out?",
                          "We were just talking about that. You must have forgotten...", "This is the third time today you're talking about some question...",
                          "You're repeating all the same like a parrot...", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("You know, " + NPChar.name + ", maybe next time.", "Right, I've forgotten for some reason...",
                      "Yes, it really is the third time...", "Yup...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			//работорговец
			if (pchar.questTemp.Slavetrader == "EscapeSlave_Villemstad")
            {
                link.l1 = "I heard that there was a serious mess on the island... Slaves?";
                link.l1.go = "EscapeSlaveVillemstad_T1";
            }
			//Португалец
			if (CheckAttribute(pchar, "questTemp.Portugal") && pchar.questTemp.Portugal == "SeekPortVillemstad")
            {
                link.l1 = "I've heard that distasteful scoundrel Bart the Portuguese has finally met justice! Is he in prison? When will his execution be, do you know? I'd come watch, I have a bone to pick with that scumbag...";
                link.l1.go = "Portugal";
            }
 		break;

		//работорговец
		case "EscapeSlaveVillemstad_T1":
			dialog.text = "Yep, there ain't ever been such a mess... More than a thousand slaves have participated in a mutiny. Two plantations have been burnt down to the ground and almost each of their masters were murdered. The commandant was worried that they'd come attack the city, so he has enforced martial law. And it all started because of the story of two slaves Tamango and Isauri...";
			link.l1 = "Wow! Tell me the whole story! Who are they?";
			link.l1.go = "EscapeSlaveVillemstad_T2";
		break;
		
		case "EscapeSlaveVillemstad_T2":
				dialog.text = "Tamango and Izaura - slaves of Blenheim plantation, the first plantation burnt. They loved each other. But a son of planter, Leonsio, arrived from Europe. He wanted to make Izaura his personal concubine. Tamango didn't like the idea and so did Izaura, she really did loved the black devil\nI must say that Tamango was some sort of war chief back in Africa... A giant with deadly skills of fighting with an axe, slaves respected him. So they attacked the guards at night, killed every Dutch in Blenheim\nThen Izaura had opened the mansion's gates and they slayed everyone there. Blenburg was burnt to the ground too. Then they fled to the jungles and disappeared...";
			link.l1 = "Well, how's that for a story! Sounds like a plot for a novel! How did you find all that out, by the way?";
			link.l1.go = "EscapeSlaveVillemstad_T3";
		break;
		
		case "EscapeSlaveVillemstad_T3":
			dialog.text = "Rumors, mynheer, the Earth is teeming with rumors. Rum loosens tongues, all you have to do is listen...";
			link.l1 = "And how did that all end? Did they find those darkies?";
			link.l1.go = "EscapeSlaveVillemstad_T4";
		break;
		
		case "EscapeSlaveVillemstad_T4":
				dialog.text = "Not a chance! Until the reinforcements finally managed to arrive, nobody took a step into the jungle. Then a warship arrived with a unit of soldiers and they searched the island and none of them ever came back.";
			link.l1 = "Well, how about that! A thousand men and they all vanished into thin air!";
			link.l1.go = "EscapeSlaveVillemstad_T5";
		break;
		
		case "EscapeSlaveVillemstad_T5":
			dialog.text = "Actually water.";
			link.l1 = "What are you talking about, " + npchar.name + "? I don't get it...";
			link.l1.go = "EscapeSlaveVillemstad_T6";
		break;
		
		case "EscapeSlaveVillemstad_T6":
			dialog.text = "He-he... I bet they swam off the island. The thing is the next night after the mutiny a bark went missing from the docks. You can slap me silly and call me Diana if it wasn't at the hands of Tamango and his brethren! That's why they're not on the island.";
			link.l1 = "All right, thanks for the intriguing story, " + npchar.name + ". Although I can't even picture negros being about to handle sails.";
			link.l1.go = "EscapeSlaveVillemstad_T7";
		break;
		
		case "EscapeSlaveVillemstad_T7":
			dialog.text = "Well, I believe they can. Maybe one of them used to serve as a sailor. Stop by and visit me again, " + pchar.name + ", I'll get some more stories for you next time.";
			link.l1 = "Thanks!! Well, it's time for me to get going.";
			link.l1.go = "exit";
			AddQuestRecord("Slavetrader", "22_2");
			pchar.questTemp.Slavetrader = "EscapeSlaveVillemstad_P";
		break;						

		case "Portugal":
			dialog.text = "Yes, that's correct. They caught that pirate. And can you believe how? He was picked up on a cockboat alone in the middle of the sea. He didn't even make a peep before he was sent into the hold for the rats. It is really amusing, you know, such a dangerous pirate got caught like such a dummy!";
			link.l1 = "And why was he all alone in the sea?";
			link.l1.go = "Portugal_1";
		break;
		
		case "Portugal_1":
			dialog.text = "He probably decided to part ways with his henchmen, no doubt... They couldn't split something. Now he's in the hands of the Company itself and those guys don't take well to jokes. They say he took possession of one of the Company's boats with something valuable. Apparently, it's just because they want to squeeze some information out of him, he's still not dangling on a noose already.";
			link.l1 = "So, when will his execution be, do you know?";
			link.l1.go = "Portugal_2";
		break;
		
		case "Portugal_2":
			dialog.text = "Nobody knows. I think once the Company finds out what it wants, they'll fasten a hemp tie around his neck. The Portuguese is in the prison right now under a reliable guard\nRecently they brought his boatswain over here as well. His story was even more surprising, he turned himself in to the Dutch in Philipsburg. So, they've set him up in a cell right next to his ex-captain, so they are neighbors now, he-he...";
			link.l1 = "Miracles do happen! All right, I'll be watching out for news. I don't want to miss that image. Bye, "+npchar.name+"!";
			link.l1.go = "Portugal_3";
		break;
		
		case "Portugal_3":
			DialogExit();
			pchar.questTemp.Portugal = "PortugalInPrison";
			AddQuestRecord("Portugal", "32");
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

