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
			if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "utensil" && !CheckAttribute(npchar, "quest.utensil"))
			{
				link.l1 = "I came here because of an unusual matter, holy father. A privateer named Guy Marchais has presented a very valuable item to your parish not long ago. It was a golden pectoral cross with a lazurite on it. Is that true?";
                link.l1.go = "guardoftruth";
			}
		break;
		
		case "guardoftruth":
			dialog.text = "Oh yes, my son!  It is the best item in our parish. I haven't seen such a magnificence in my whole life! And what's wrong, my son? Why are you so interested in this cross?";
			link.l1 = "Holy father, I know that you won't like it but I have to tell you that this cross was stolen from another parish and the clergyman was murdered during that theft. That man who has presented this item to you is a criminal.";
			link.l1.go = "guardoftruth_1";
		break;
		
		case "guardoftruth_1":
			dialog.text = "We all have sins, my son, but murdering a clergyman is a serious accusation. Do you have any proof? And from which parish was this cross stolen?";
			link.l1 = "Couldn't my word be a proof? This cross was stolen from the Santiago's parish and it must be returned.";
			link.l1.go = "guardoftruth_2";
		break;
		
		case "guardoftruth_2":
			dialog.text = "Santiago? Spanish? My son, you are surprising me...";
			link.l1 = "Holy father, everyone is equal under the God. Spanish are Christians just like us and disagreements between the nations must not apply to believers' feelings. I beg you to return this cross to the Santiago's parish.";
			link.l1.go = "guardoftruth_3";
		break;
		
		case "guardoftruth_3":
			dialog.text = "My son, don't you understand that this cross is a gift from the believing Christian to our parish?! No, my son, I can't do what you ask for.";
			link.l1 = "And don't you care that blood was spilled for this cross? The blood of clergyman, even if he is spanish.";
			link.l1.go = "guardoftruth_4";
		break;
		
		case "guardoftruth_4":
			dialog.text = "My son, you have not given any proof. The cross will stay in our parish. This is my final decision. Besides, your effort in helping Spanish in this matter really concerns me.";
			link.l1 = "I see, Farewell then, holy father...";
			link.l1.go = "guardoftruth_5";
		break;
		
		case "guardoftruth_5":
			DialogExit();
			npchar.quest.utensil = "true";
			pchar.questTemp.Guardoftruth.Baster_church = "seek";
			AddQuestRecord("Guardoftruth", "27");
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

