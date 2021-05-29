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
			if (CheckAttribute(pchar, "questTemp.Guardoftruth.Trinidad") && pchar.questTemp.Guardoftruth.Trinidad == "begin")
			{
				link.l1 = "Listen, here was a frigate under the command of Miguel Dichoso in April 1654. It disappeared then. Can you tell me about this frigate? Maybe you saw what happened with it and where it went then? Remember?";
				link.l1.go = "guardoftruth";
			}
		break;
		
		case "guardoftruth":
			dialog.text = "Oh-ho... Sure, senor, it would be difficult to forget, such things happened then!";
			link.l1 = "Tell me, I am very interested to hear your story!";
			link.l1.go = "guardoftruth_1";
		break;
		
		case "guardoftruth_1":
			dialog.text = "Senior's Dichoso frigate casted anchor in San Jose's harbor. I had a good chance to watch it all. I'll tell you that it was an excellent frigate, a pure masterpiece, I swear! The crew was bragging that it could speed up to sixteen knots\nSo, they had spent a day here, then set sail and sailed away right to Tobago island. Suddenly some strange things started to happen with the weather as soon as they had disappeared behind the horizon. The weather had been fine for days back then. Not a single cloud\nAnd yet the terrible storm came out from nowhere. Looked like Neptune himself paid us a visit. I went up to the top of lighthouse in order to light it, but then I saw her... Santa Quiteria was rushing upon huge waves accompanied by a giant tornado\nThe frigate flew near my lighthouse like a spark and then was driven by the storm to North West. No one has seen Santa Quiteria since then. And an hour later the wind and the rain clouds were gone and the sun was shining, not a single sign of the storm! Never seen such miracles before that! Although I collected so much amber from my bay that day...";
			link.l1 = "So, the storm has driven that frigate back to the Caribbean sea?";
			link.l1.go = "guardoftruth_2";
		break;
		
		case "guardoftruth_2":
			dialog.text = "It has, yes. Way to Martinique. I doubt that Dichoso could survive that storm, he was doing his best though, the frigate wasn't sinking but 'Santa-Quiteria' must be on the bottom of the sea among corals by now... Actually, you are not the first person who has asked me about Dichoso and his frigate.";
			link.l1 = "Really? Who else was interested in Miguel?";
			link.l1.go = "guardoftruth_3";
		break;
		
		case "guardoftruth_3":
			dialog.text = "Some dashing captain of the Spanish fleet. He has introduced himself as...oh.. I have clean forgotten it... Ah! Senor Diego. His name was Diego, but his surname... de Montagna or de Montoya. Something like that. He was listening me just like you were, thanked me and gone away. Never seen him since then.";
			if (sti(Pchar.money) >= 5000)
			{
				link.l1 = "I see. Thank you very much for your story, you've helped me a lot. And this is my gratitude in coins. Farewell.";
				AddMoneyToCharacter(pchar, -5000);
				AddCharacterExpToSkill(pchar, "Leadership", 250);
			}
			else
			{
				link.l1 = "I see. Thank you very much for your story, you've helped me a lot. Farewell.";
			}
			link.l1.go = "guardoftruth_4";
		break;
		
		case "guardoftruth_4":
			DialogExit();
			AddQuestRecord("Guardoftruth", "41");
			pchar.questTemp.Guardoftruth.Trinidad = "mayak";
			pchar.quest.GuardOT_setDiego.win_condition.l1 = "ExitFromLocation";
			pchar.quest.GuardOT_setDiego.win_condition.l1.location = pchar.location;
			pchar.quest.GuardOT_setDiego.function = "GuardOT_SetDiegoOnMayak";
		break;
	}
	UnloadSegment(NPChar.FileDialog2); 
}