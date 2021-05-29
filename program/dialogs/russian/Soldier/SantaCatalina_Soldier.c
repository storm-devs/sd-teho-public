// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("What questions do you have for a soldier?", "Soldier has his whole life planned out - guarding, hustling... How can I help you, " + GetAddress_Form(NPChar) + "?"), "You shouldn't bother a soldier with stupid questions, " + GetAddress_Form(NPChar) + "...", "This is the third time today that you've tried to ask me a question...",
                          "The fate of a soldier isn't easy, and now you, scum, driving me mad...", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("I've changed my mind...", "I've got nothing to talk about at the moment."), "Got it...",
                      "Yeah, you are right, the third time already...", "Sorry...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

