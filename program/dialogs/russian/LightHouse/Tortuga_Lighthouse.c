// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("What do you want?", "What would you like to know?"), "Tell me, what are you interested in, " + GetAddress_Form(NPChar) + "?", "It's the third time you try to ask...", "I had enough of you. Get out!", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("I have changed my mind...", "I have got nothing to say now."), "It seems I've forgotten, sorry...",
                      "You're right, it's the third time already. Pardon me.", "I am sorry...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
	}
	UnloadSegment(NPChar.FileDialog2); 
}

