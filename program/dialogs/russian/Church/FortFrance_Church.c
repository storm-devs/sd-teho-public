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
			// Jason Долго и счастливо
			if (CheckAttribute(pchar, "questTemp.LongHappy") && pchar.questTemp.LongHappy == "choose" && !CheckAttribute(npchar, "quest.LongHappy"))
			{
				link.l1 = "Holy Father, I am looking for Abbot Benoit, I have an important and urgent matter to him. Can you tell me where he can be?";
				link.l1.go = "LH_church";
			}
		break;
		
		// Jason Долго и счастливо
		case "LH_church":
			dialog.text = "The abbot has left the city for church affairs with representatives of the Spanish Catholic mission in the New World. I don't know the details, but  father Benoit is absent long enough to suspect that the negotiations have extended, or something happened along the way. We are all little excited, but we can only pray and wait for the news.";
			link.l1 = "I didn't think that everything would be easy. Holy father, tell me where exactly in the Spanish colonies the abbot went to. I need to find him as quickly as possible.";
			link.l1.go = "LH_church_1";
		break;
		
		case "LH_church_1":
			dialog.text = "Sorry, my son, but I don't know. As far as I know, the abbot went on negotiations with the bishop of New Spain and the prelate of the Inquisition, Father Vincento Palotti, but he didn't specified where the meeting would be to the simple servants of the Lord.";
			link.l1 = "That's enough, Holy Father, thank you. I know... in some way, father Palotti. I'll try to find out something in Santiago.";
			link.l1.go = "LH_church_2";
		break;
		
		case "LH_church_2":
			DialogExit();
			npchar.quest.LongHappy = "true";
			LongHappy_GoToSantiago();
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}



