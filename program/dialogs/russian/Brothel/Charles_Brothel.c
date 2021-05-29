// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    ref sld;
	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("What kind of questions, "+ GetSexPhrase("young man","young lady") +"?", "What do you want, "+ GetSexPhrase("handsome","pretty one") +"? Ask it."), "Questions again?", "Tee-hee, it's all the same for the third time today - questions...",
                          ""+ GetSexPhrase("Hm, why don't you pick up any beauty for yourself? I am starting to get suspicions about you...","Hm, why don't you pick up any beauty for yourself? We don't have boys here, sorry, tee-hee...") +"", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("I've changed my mind...", "Well, nevermind..."), "I just... have no questions...",
                      "You're right, it's the third time already. Pardon me.", "Not now... maybe next time...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

