// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("What would you like?", "What do you want to know?"), "Tell me, what are you interested in, " + GetAddress_Form(NPChar) + "?", "It's the third time you try to ask...", "I had enough of you. Leave me alone!", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("I have changed my mind...", "I've got nothing to say to you"), "Oh, my bad. Indeed... I am sorry",
                      "You're right, it's the third time already. Pardon me...", "I'm sorry...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
	}
	UnloadSegment(NPChar.FileDialog2); 
}

