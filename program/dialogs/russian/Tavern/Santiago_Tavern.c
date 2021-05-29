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
			// Jason Долго и счастливо
			if (CheckAttribute(pchar, "questTemp.LongHappy.Santiago"))
			{
				link.l1 = "I heard that the holy fathers arrived here from a French colony with some delegation, to agree on something? Probably, to exchange prisoners after that bloody bath in Martinique?";
				link.l1.go = "LH_tavern";
			}
		break;
		
		// Jason Долго и счастливо
		case "LH_tavern":
			dialog.text = "No senor, that story was settled a long time ago without any clerics. You see, you live completely under a palm tree, since you haven't heard that Pope Innocent X with Cardinal Mazarin finally agreed. Europe with its wars is one thing, but all Christians should fight together against pagan darkness at the end of the world\nAnd yes, frog-eaters came to us. But they just didn’t agree on anything - our honored guests sits in a governor's mansion, under the guard, drink coffee and warming a seat. Almost a month already! The people gossiped, had a long talk and got used to it - look, the French abbot serves a prayer service in the evenings in the church. Almost like a sight ahah!";
			link.l1 = "Interesting! I should look at that Frenchman, atleast it is more funny than staring at a mug.";
			link.l1.go = "LH_tavern_1";
		break;
		
		case "LH_tavern_1":
			DialogExit();
			LongHappy_SantiagoBenua();
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

