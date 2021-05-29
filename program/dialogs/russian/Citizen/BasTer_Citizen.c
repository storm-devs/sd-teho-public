// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
            dialog.text = RandPhraseSimple("What kind of questions?", "What would you like?");
			link.l1 = RandPhraseSimple("I have changed my mind...", "I have got nothing to say now.");
		    link.l1.go = "exit";
		break;
		
		case "info":
			dialog.text = LinkRandPhrase("Who are you interested in?","Who do you need?","About who exactly?");
			link.l1 = "I want to know more about Fadey the Muscovite.";
			link.l1.go = "fadey";
			link.l2 = "Let's change the subject...";
			link.l2.go = "new question";
		break;
		
		case "town":
			dialog.text = LinkRandPhrase("Where do you want to get?","What are you looking for?","Where do you want to go?");
            link.l1 = "Where is Fadey's house?";
			link.l1.go = "fadey_house";
			link.l2 = "Let's talk about something else...";
			link.l2.go = "new question";
		break;
		
		case "fadey":
			dialog.text = RandPhraseSimple("An important man. He rules the local factory and he is on close with the high life in Basse-Terre. He has a strong accent and he really likes drinking... but he never gets drunk.","He is a big shot and a friend of governor. Fadey rules a local factory. Came from a northern country far far away from here... I don't even know the name of it. He has strong hands and He's really able to drink the whole barrel of rum and won't get drunk.");
			link.l1 = "My thanks!";
			link.l1.go = "exit";
		break;
		
		case "fadey_house":
			dialog.text = RandPhraseSimple("Go straight from the pier until you see the square, a house on the left is the Fadey's mansion.","Go to the pier through the square from the governor's residence, a house on the right is the Fadey's mansion.");
			link.l1 = "My thanks!";
			link.l1.go = "exit";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

