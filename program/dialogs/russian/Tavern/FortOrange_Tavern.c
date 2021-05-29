// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("What questions do you have?", "How can I help you, " + GetAddress_Form(NPChar) + "?"), "You tried to ask me some question not long ago, " + GetAddress_Form(NPChar) + "...", "Over this whole day, this is the third time you're talking about some question...",
                          "More questions, I presume?", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("I've changed my mind...", "I've got nothing to talk about at the moment."), "Umph, where has my memory gone...",
                      "Yes, it really is the third time...", "No, what questions?...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			if (pchar.questTemp.Slavetrader == "FindRatJamaica")
            {
                link.l1 = "Has a man named Francois Gontier stopped by in your town? I really need him.";
                link.l1.go = "Jamaica_ratF_1";
            }
			// Addon 2016-1 Jason пиратскаЯ линейка
			if (CheckAttribute(pchar, "questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "silk_4")
            {
                link.l1 = "Listen, mate, there's a ship builded in Port Royal who is purchasing some silk for his shipyard... some very special silk, you surely've heard of it. They say a seller of such silk is residing somewhere in this settlement. Do you have any clues on how to find him? I have a business proposal for him.";
                link.l1.go = "mtraxx";
			}
			if (CheckAttribute(pchar, "questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "silk_5" && GetCharacterItem(pchar, "gold_dublon") >= 50)
            {
                link.l1 = "I have fifty doubloon with me. Take them and start talking.";
                link.l1.go = "mtraxx_4_1";
			}
		break;

		case "Jamaica_ratF_1":
			dialog.text = "He has. He'd been renting a room for a few days. Not the most pleasant fellow, I'll tell you. Besides that, he was obsessively paranoid of being searched for. He was always afraid and looking around. Are you the man that he was so afraid of?";
			link.l1 = "No, it's not me. You know, privateers have a lot of enemies though. So, where can I find him? He and I decided to make an agreement, but seems like the ground has swallowed him up.";
			link.l1.go = "Jamaica_ratF_2";
		break;
		
		case "Jamaica_ratF_2":
			dialog.text = "He's departed to sea on his own ship. I don't know where to. He didn't fill me in on that.";
			link.l1 = "Ah, what a pity! Where am I going to look for him now?";
			link.l1.go = "Jamaica_ratF_3";
		break;
		
		case "Jamaica_ratF_3":
			dialog.text = "I don't know, buddy. I'd tell you if I knew.";
			link.l1 = "All right, I see. I'll go ask some other people...";
			link.l1.go = "exit";
			AddQuestRecord("Slavetrader", "21_4");
			pchar.questTemp.Slavetrader = "FindRatJamaica_H";
		break;
		
		// Addon 2016-1 Jason пиратскаЯ линейка
		case "mtraxx":
            dialog.text = "Huh, if you suspect our merchant, the one that keeps the store, I can tell it's not him, he doesn't deal in silk sailcloth. Smugglers don't come here neither, no need for them when there's no customs house. And besides no one else, except our merchant, trades here anyways. Have a look around, we aren't that sort of people, ha-ha!";
			link.l1 = "But someone is supplying the silk to Port Royal - that's irrefutable. Do you have any clue on who could be the supplier?";
			link.l1.go = "mtraxx_1";
		break;
		
		case "mtraxx_1":
            dialog.text = "Smugglers of Port Royal, maybe? Or rogue cappers? Must be unloading in some hidden cove... Ha! I have an idea, pal. There is one local, he knows all that's going on in these waters. If he won't have any assumptions then there are no merchants of silk.";
			link.l1 = "Splendid! What's the guy's name?";
			link.l1.go = "mtraxx_2";
		break;
		
		case "mtraxx_2":
            dialog.text = "Hm... I am trying to recall his name but it just doesn't come up for some reason...";
			link.l1 = "How 'bout a few coins to aid your memory?";
			link.l1.go = "mtraxx_3";
		break;
		
		case "mtraxx_3":
            dialog.text = "I guess that might help... Fifty gold doubloons will surely illuminate this old head.";
			if (GetCharacterItem(pchar, "gold_dublon") >= 50)
			{
				link.l1 = "I see. Here, take the coins.";
				link.l1.go = "mtraxx_4_1";
			}
			else
			{
				link.l1 = "I see. I'll be back...";
				link.l1.go = "mtraxx_4_2";
			}
		break;
		
		case "mtraxx_4_1":
			RemoveItems(pchar, "gold_dublon", 50);
			Log_Info("You have given 50 doubloons");
			PlaySound("interface\important_item.wav");
            dialog.text = "Husky Billy is the man you need. He has been living on Jamaica like forever, knows every dog on the streets. Used to be a pirate and a pain in the brits asses until he got wounded some three years ago. Now he mostly fishes, hunts sharks and gathers amber in Jamaica's bays. He leaves his old long boat only to buy more rum and crackers\nYou should look for him within waters around Jamaica. They say he's sailing at the northern side, all the way to the east-most point. But chasing a long boat is a fool's errand, you better stake out around a south-west corner, they say he's been seen near Cape Negril about once a week. His cockleboat is called 'The Fly Fish'.";
			link.l1 = "Thanks, pal. You've earned your gold.";
			link.l1.go = "mtraxx_5";
		break;
		
		case "mtraxx_5":
            dialog.text = "Good luck, mate! I hope you'll find what you are looking for!";
			link.l1 = "...";
			link.l1.go = "mtraxx_6";
		break;
		
		case "mtraxx_4_2":
            DialogExit();
			AddQuestRecord("Roger_2", "6");
			pchar.questTemp.Mtraxx = "silk_5";
		break;
		
		case "mtraxx_6":
            DialogExit();
			AddQuestRecord("Roger_2", "7");
			pchar.questTemp.Mtraxx = "silk_6";
			pchar.quest.mtr_negril.win_condition.l1 = "Timer";
			pchar.quest.mtr_negril.win_condition.l1.date.hour  = 12+rand(12);
			pchar.quest.mtr_negril.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 2+rand(3));
			pchar.quest.mtr_negril.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 2+rand(3));
			pchar.quest.mtr_negril.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 2+rand(3));
			pchar.quest.mtr_negril.function = "Mtraxx_CreateBilly";
			SetFunctionTimerCondition("Mtraxx_BillySeaTimeOver", 0, 0, 7, false);
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
