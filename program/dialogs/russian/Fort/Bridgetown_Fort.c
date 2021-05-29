// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("What do you think about our fort? Looking good, yes? And the garrison is not worse, ha...", "The fort soldier's life is a quite dull... Guarding and patrolling, some rest and then all the same again. But it's all different in the town... What do you want, " + GetAddress_Form(NPChar) + "?"), "Bothering a soldier with stupid questions is not welcome, " + GetAddress_Form(NPChar) + "...", "It's the third time you try to ask...",
                          "It's not easy being a soldier and you are here again"+ GetSexPhrase(", jerk,  "," ") +" trying to piss me off. Be careful or you will end up in a basement of the fort...", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("I have changed my mind...", "I've got nothing to say to you..."), "Yeah, it isn't...",
                      "You're right, it's the third time already. Pardon me...", "Sorry...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

