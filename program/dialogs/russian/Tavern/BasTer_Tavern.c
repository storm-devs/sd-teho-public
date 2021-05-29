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
			//Jason, суп из черепахи
			if (CheckAttribute(PChar, "questTemp.Terrapin") && pchar.questTemp.Terrapin == "baster" && !CheckAttribute(npchar, "quest.terrapin"))
			{
				link.l1 = "I'm looking for my old buddy Fernand Luc. I've got a couple of questions for him. I've heard he really enjoyed himself here a week ago...";
				link.l1.go = "terrapin";
			}
		break;
		
		//суп из черепахи
		case "terrapin":
			dialog.text = "He might still be enjoying himself here, but in deep water. Your friend's kicked the bucket. So you're a tad late, captain. That man over there, sitting at the farthest table, paid for his funeral, although I get the feeling that he's the same man that caused it. He's got a hell of a shady face. His name is Robert Martene. If you want, you can walk over and ask him your questions. ";
			link.l1 = "Thanks, buddy. I'll go have a talk with monsieur Robert. We'll drink for the soul of poor old Luc that his soul may rest in peace...";
			link.l1.go = "terrapin_1";
			npchar.quest.terrapin = "true";
		break;
		
		case "terrapin_1":
			DialogExit();
			AddQuestRecord("Terrapin", "4");
			pchar.questTemp.Terrapin = "rober";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

