// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Questions, " + GetAddress_Form(NPChar) + "?", "How can I help you, " + GetAddress_Form(NPChar) + "?"), ""+ GetSexPhrase("Hm, what's the big idea, " + GetAddress_Form(NPChar) + "? ","Again with the strange questions? Toots, go have some rum or something...") +"", "Over this whole day, this is the third time you're talking about some question..."+ GetSexPhrase(" Are these some signs of attention?","") +"",
                          "More questions, I presume, " + GetAddress_Form(NPChar) + "?", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("I've changed my mind", "I've got nothing to talk about at the moment."), "No, no beautiful...",
                      "No way, dear, sclerosis...", "No, what questions?...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
		break;


	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

