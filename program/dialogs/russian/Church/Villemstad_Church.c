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
			// калеуче
			if (CheckAttribute(pchar, "questTemp.Caleuche") && pchar.questTemp.Caleuche == "priest")
			{
				link.l1 = "One of the clergymen of your parish asked me to investigate the house, where Joachim Merriman was renting a room...";
				link.l1.go = "caleuche";
			}
		break;
		
		// калеуче
		case "caleuche":
			dialog.text = "So? Have you been there, my son? Tell me!";
			link.l1 = "Yes, I have. But honestly, It would've been better if I hadn't visited that place. In the upper room I was attacked by a skeleton with a huge axe. I managed to come out victorious, although it certainly wasn't easy.";
			link.l1.go = "caleuche_1";
		break;
		
		case "caleuche_1":
			dialog.text = "Oh Lord, show mercy on us! My worst fears have come true!";
			link.l1 = "And that's not all. When I finally put it down, it cried out loud like a woman. Then I looked through the bones and found some pieces of jewelry. I would assume that it was the landlady who had gone missing.";
			link.l1.go = "caleuche_2";
		break;
		
		case "caleuche_2":
			dialog.text = "(crosses himself)... Poor God's servant, may He put her soul to rest ...";
			link.l1 = "It looks like that Merriman is a warlock indeed. I have no idea how one can turn a living man into an abomination like that.";
			link.l1.go = "caleuche_3";
		break;
		
		case "caleuche_3":
			dialog.text = "Joachim Merriman is a very fearsome warlock, my son, I knew him in Europe, but at those times he wasn't capable of anything like that. Here, In the Caribbean, he managed to get something which gave him supernatural powers.";
			link.l1 = "You knew Merriman, Father?";
			link.l1.go = "caleuche_4";
		break;
		
		case "caleuche_4":
			dialog.text = "I did. Back then I was just a humble canon in one of Lisbon's parishes. Joachim Merriman was a wealthy nobleman. At some point he became interested in old manuscripts and scrolls brought by the sailors from the distant lands. Also he began to study an alchemy. After some time he went into seclusion\nPeople saw flashes of light in his house; sometimes they also could smell something strange. Then they saw him in the cemetery at nights. Once they saw him digging out a fresh corpse and bringing it to his home. And the patience ran out, the father superior contacted the Inquisition\nWhen the guards breached the door of Merriman's house, Joachim was not there - he had escaped through a secret passage. They found a lab in the basement, and even the seasoned soldiers were deeply shocked by what they saw. Rotting whole and dismembered bodies, human and animal skeletons, strange things... Fear and hatred for Merriman were so great that his house was demolished completely\nMerriman disappeared without a trace. The Inquisition began to search for him, sentencing him in his absence to burning at a stake as a dangerous warlock. But they never found him. And now, after all these years, I saw him again on the streets of Willemstad.";
			link.l1 = "And why didn't you tell the inquisitors?";
			link.l1.go = "caleuche_5";
		break;
		
		case "caleuche_5":
			dialog.text = "My son, don't you know that our church is at odds with the Inquisition? I'd prefer to stay clear of Father Vincento and his sidekicks.";
			link.l1 = "I see. Father, I think I know, where from Merriman drew his power. He's got a hold of an ancient artifact, a jade skull of Yum Cimil, ancient god of death worshipped by the Indians of the Chavin tribe.";
			link.l1.go = "caleuche_6";
		break;
		
		case "caleuche_6":
			dialog.text = "Merriman was known for performing sorcerous rituals and experiments on corpses, so it very well might be true. I thank God that this terrible man has left Willemstad, and you have destroyed the devilish seeds he attempted to plant here. We're indebted to you, my son. Please accept these sanctified items as your reward.";
			link.l1 = "Thank you, Father";
			link.l1.go = "caleuche_7";
		break;
		
		case "caleuche_7":
			Log_Info("You have received church amulets");
			PlaySound("interface\important_item.wav");
			GiveItem2Character(pchar, "amulet_2"); 
			GiveItem2Character(pchar, "amulet_6"); 
			GiveItem2Character(pchar, "amulet_8"); 
			GiveItem2Character(pchar, "amulet_10"); 
			ref sld = characterFromId("Havana_Priest");
			dialog.text = "But that was not the end of our troubles, my son. Recently I have received a letter from "+sld.name+", father superior of a church in Havana. He is telling terrible news. In a cave, in the jungle of Cuba, hunters have seen frightening abominations, the walking dead. And it's all more bothersome considering the fact that recently people have gone missing in Havana after going into the jungle on their business.";
			link.l1 = "Hmm... You imply that this is Merriman's work, too?";
			if (CheckCharacterItem(pchar, "HolTradeLicence") && GetDaysContinueNationLicence(HOLLAND) >= 30) link.l1.go = "caleuche_8_1";
			else link.l1.go = "caleuche_8";
		break;
		
		case "caleuche_8":
			sld = characterFromId("Havana_Priest");
			dialog.text = "I don't know what to think, my son. But if that black witcher became so powerful, all inhabitants of the archipelago are in grave danger. Only God knows, what this servant of devil could have in mind\nI do hope that Father "+sld.name+" was wrong, but anyway - please go to Havana and talk to him. I have prepared a trading license for you, which is valid for a month. With it, you'll be able to enter the port of Havana without any difficulties.";
			link.l1 = "Alright, Father. I'll head to Havana.";
			link.l1.go = "caleuche_9";
			npchar.quest.givelicence = true;
		break;
		
		case "caleuche_8_1":
			sld = characterFromId("Havana_Priest");
			dialog.text = "I don't know what to think, my son. But if that black witcher became so powerful, all inhabitants of the archipelago are in grave danger. Only God knows, what this servant of devil could have in mind\nI do hope that Father "+sld.name+" was wrong, but anyway - please go to Havana and talk to him.";
			link.l1 = "Alright, Father. I'll head to Havana.";
			link.l1.go = "caleuche_9";
		break;
		
		case "caleuche_9":
			dialog.text = "I am glad that you're a true son of the Church. I will pray for your health and well-being day and night. Go with my blessing. May the Lord strengthen you in your struggle against unholy powers.";
			link.l1 = "Goodbye, Father.";
			link.l1.go = "caleuche_10";
		break;
		
		case "caleuche_10":
			DialogExit();
			AddQuestRecord("Caleuche", "26");
			AddCharacterMaxHealth(pchar, 1);
			if (CheckAttribute(npchar, "quest.givelicence")) GiveNationLicence(HOLLAND, 30);
			ChangeCharacterComplexReputation(pchar, "nobility", 2);
			ChangeCharacterComplexReputation(pchar, "authority", 1);
			ChangeCharacterComplexReputation(pchar, "fame", 3);
			ChangeCharacterNationReputation(pchar, HOLLAND, 5);
			AddCharacterExpToSkill(pchar, "Leadership", 300);
			pchar.questTemp.Caleuche = "havana";
			Caleuche_PrepareCubaGrot();
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

