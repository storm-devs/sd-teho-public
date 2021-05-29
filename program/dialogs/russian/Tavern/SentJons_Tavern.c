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
			//Jason, Сага, Тени прошлого
			if (CheckAttribute(PChar, "questTemp.Saga.Shadows") && pchar.questTemp.Saga.Shadows == "sentjons")
			{
				link.l1 = "I'm looking for a Raymond Baker, a former executioner. Do you know if he's alive and where I can find him?";
				link.l1.go = "baker";
			}
			//Jason, суп из черепахи
			if (CheckAttribute(PChar, "questTemp.Terrapin") && pchar.questTemp.Terrapin == "baster" && !CheckAttribute(npchar, "quest.terrapin"))
			{
				link.l1 = "I'm looking for Mr. Jones. Can you help my in my search, pal?";
				link.l1.go = "terrapin";
			}
			// Страж Истины
			if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "merdok")
			{
				link.l1 = "Listen, has there been an alchemist that arrived here in this town, a physician? He's Italian, about thirty years old, his name is Gino Gvineili. Have you heard anything about that?";
				link.l1.go = "guardoftruth";
			}
		break;
		
		//Сага, Тени прошлого
		case "baker":
			dialog.text = "Our fatso has become more popular than Colonel Fox! He's alive, the poor guy. But he's not in town right now. After Raymond found out that serious people like you are taking an interest in him, he hurried up and sold his hovel for peanuts and was gone with the wind.";
			link.l1 = "Gone with the wind where?";
			link.l1.go = "baker_1";
		break;
		
		case "baker_1":
			dialog.text = "Oh, who knows. He went to serve a ship's doctor on the first vessel that came by. Only that vessel has come back today and nobody has seen Baker come out to the shore.";
			link.l1 = "How can I find the captain?";
			link.l1.go = "baker_2";
		break;
		
		case "baker_2":
			dialog.text = "Why do you think you need to look for him? I'm sure he's already drunk off usual in his cabin. His trough is called 'Callow Meggy'. Such is the captain, such is the name...";
			link.l1 = "Thanks for the help, buddy!";
			link.l1.go = "baker_3";
		break;
		
		case "baker_3":
			DialogExit();
			AddQuestRecord("Shadows", "2");
			pchar.questTemp.Saga.Shadows = "baldmaggy";
			pchar.quest.Saga_ShadowsMaggy.win_condition.l1 = "location";
			pchar.quest.Saga_ShadowsMaggy.win_condition.l1.location = "Antigua";
			pchar.quest.Saga_ShadowsMaggy.function = "Saga_SetBaldMaggy";
		break;
		
		//суп из черепахи
		case "terrapin":
			dialog.text = "Mr. Jones? You're taking it a little far, buddy. I don't really recall a Mr. Jones, but simple Joneses – solicitors, hunkies, and soldiers we have up to our necks. Tell me, who is it specifically that you need?";
			link.l1 = "He's got an adult sister Molly. They say she's amazingly beautiful.";
			link.l1.go = "terrapin_1";
		break;
		
		case "terrapin_1":
			dialog.text = "No. Nothing like that comes to mind. Sorry, buddy...";
			link.l1 = "Alright, if you don't know, you don't know...";
			link.l1.go = "exit";
			npchar.quest.terrapin = "true";
		break;
		
		case "guardoftruth":
			dialog.text = "No, I haven't heard. And we've only got one alchemist in the town, pharmacist John Murdock. He's got remarkable potions – they heal any ailments.";
			link.l1 = "Do you think he brews these potions himself?";
			link.l1.go = "guardoftruth_1";
		break;
		
		case "guardoftruth_1":
			dialog.text = "Good question. I ask myself that every now and then John looks nothing like a connoisseur of medicine glasses, herbs, and powders. He kind of resembles an ex-soldier, a mercenary... that's closer to the truth.";
			link.l1 = "Well, I guess the man's overqualified...";
			link.l1.go = "guardoftruth_2";
		break;
		
		case "guardoftruth_2":
			dialog.text = "Maybe, he is. But I there's one thing I know for sure, somebody lives on his second floor. The window is constantly draped off. Even when John's downstairs, a clinking sound escapes this window resembling glass vials and bottle as well as what seems to be the odor of boiling herbs, and in the night time the light doesn't go out. That's why I'm suspicious that the inhabitant of that room is the one who's preparing John's medicine's for sale.";
			link.l1 = "Hm. Interesting observation. Thanks, buddy!";
			link.l1.go = "exit";
			pchar.questTemp.Guardoftruth = "merdok1";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}