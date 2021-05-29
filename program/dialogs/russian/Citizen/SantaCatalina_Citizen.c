// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
            dialog.text = RandPhraseSimple("What kind of questions?", "What would you like?");
			link.l1 = RandPhraseSimple("I have changed my mind...", " I have got nothing to say now");
		    link.l1.go = "exit";
		break;
		
		case "info":
			dialog.text = LinkRandPhrase("Who are you interested in?","Who do you need?","About who exactly?");
			if (CheckAttribute(pchar, "questTemp.Saga"))
			{
				link.l1 = "I want to know more about Jan Swanson.";
				link.l1.go = "svenson";
			}
			link.l2 = "Let's change the subject...";
			link.l2.go = "new question";
		break;
		
		case "town":
			dialog.text = LinkRandPhrase("Where do you want to get?","What are you looking for?","Where do you want to go?");
			if (CheckAttribute(pchar, "questTemp.Saga"))
			{
				link.l1 = "Where is Jan Swanson's house?";
				link.l1.go = "svenson_house";
			}
			link.l2 = "Let's change the subject...";
			link.l2.go = "new question";
		break;
		
		case "svenson":
			dialog.text = RandPhraseSimple("Oh, our Jan Swanson is a very important person. In past, he was the most dashing pirate of the Western Main, and he is still not rusty with now days though he is not that active than he was before. He owns a mansion and lives there with his young wife, he is always a welcome guest for the governor. A lot of guests come to Jan... pirates mostly.","Jan Swanson is the legend of Western Main! Forest Devil, that is how the Spanish called him when he was driving them away from here. He used to be a famous corsair, now he is a respected citizen of our colony\nThough he still does some secret business, but not with his own hands anymore. He rarely leaves his house, especially since he married a young beauty.");
			link.l1 = "Thanks!";
			link.l1.go = "exit";
		break;
		
		case "svenson_house":
			dialog.text = RandPhraseSimple("Go straight from the pier until you see the square, a house on the right near the fountain is the Swanson's mansion.","Go to the pier through the square from the governor's residence, a house on the left near the fountain is the Swanson's mansion.");
			link.l1 = "Thanks!";
			link.l1.go = "exit";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}