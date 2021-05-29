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
			if (pchar.questTemp.Slavetrader == "FindRatPanama")
            {
                link.l1 = "Listen, I hear, you've got a privateer by the name of Francois Gontier in your town. Would you happen to know where to find him?";
                link.l1.go = "Panama_rat_1";
            }
			// Addon-2016 Jason ”ЊЉ-ѓваделупа
			if (CheckAttribute(pchar, "questTemp.FMQG") && pchar.questTemp.FMQG == "headhunter_panama")
            {
                link.l1 = "Look, I am in a search of a man named Bertrand Pinette, have you heard about him? He arrived to Panama not long ago. An imposing gentleman in a curving wig. He might had been here...";
                link.l1.go = "FMQG";
            }
		break;

		//-->работорговец
		case "Panama_rat_1":
			dialog.text = NPCStringReactionRepeat("Yes, we've had a fellow like that in town. He was hiding around dark places... Then some of his buddies came and paid him a visit, looked like a bunch of cutthroats and he left the town with them.", "You've already asked about that and I've answered you.", "I told you, you'd already asked about that Gontier.", "Listen, walk away and stop bothering me! Have you completely lost your noggin?", "block", 0, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("And where did he go, do you know?", "Hm, I guess so...", "Yes, right, I've asked that...", "Sorry, " + npchar.name + "...", npchar, Dialog.CurrentNode);
			link.l1.go = "Panama_rat_2";
		break;
		
		case "Panama_rat_2":
			dialog.text = "Well, there is only one way out of here on foot - Porto Bello. And he hoofed it. So look for him there.";
			link.l1 = "Thanks, you've been a ton of help!";
			link.l1.go = "exit";
			pchar.questTemp.Slavetrader = "FindRatPortobello";
			AddQuestRecord("Slavetrader", "21_1");
		break;
		//<--работорговец
		
		// Addon-2016 Jason ”ЊЉ-ѓваделупа
		case "FMQG":
			dialog.text = "Bertrand Pinette? French? Never heard about him. No pal, we haven't seen French folk around in a while.";
			link.l1 = "What a pity... You sure? He is a friend of one important hidalgo named don Carlos de Milyar. They were supposed to arrive here together.";
			link.l1.go = "FMQG_1";
		break;
		
		case "FMQG_1":
			dialog.text = "Senor de Milyar? This hidalgo visited Panama a year ago. Actually, don Carlos de Milyar lives in Portobello. He is a big friend of the local governor.";
			link.l1 = "I see. There was no need to waste time and breath in the jungle. Anyway, thank you pal.";
			link.l1.go = "FMQG_2";
		break;
		
		case "FMQG_2":
			DialogExit();
			pchar.questTemp.FMQG = "headhunter_portobello";
			AddQuestRecord("FMQ_Guadeloupe", "8");
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

