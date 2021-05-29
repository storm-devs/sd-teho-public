// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("What kind of questions, "+ GetSexPhrase("my son","my daughter") +"?", "Ask, I am listening to you..."), "I am listening, speak, "+ GetSexPhrase("my son","my daughter") +"...", "And it's the third time I tell you, "+ GetSexPhrase("my son","my daughter") +", ask your question.",
                          "A clergyman has a lot of work... and you are bothering me, "+ GetSexPhrase("my son","my daughter") +"...", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("I've changed my mind...", "Not now, padre..."), "Have nothing to say, sorry...",
                      "I'll ask, I'll ask... but a bit later...", "Pardon me, holy father...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
