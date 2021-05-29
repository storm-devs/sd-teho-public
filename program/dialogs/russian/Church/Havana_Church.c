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
			if (CheckAttribute(pchar, "questTemp.Caleuche") && pchar.questTemp.Caleuche == "havana")
			{
				ref sld = characterFromId("Villemstad_Priest");
				link.l1 = "Father superior "+sld.name+" from the church of Willemstad sent me. You told him that in a cave on Cuba, strange things have been seen...";
				link.l1.go = "caleuche";
			}
			if (CheckAttribute(pchar, "questTemp.Caleuche") && pchar.questTemp.Caleuche == "havana1")
			{
				link.l1 = "I have visited the cave in the jungle, Father.";
				link.l1.go = "caleuche_4";
			}
		break;
		
		case "caleuche":
			dialog.text = "Thank God he paid heed to it! Once the gossips about the living dead had reached my ears, I immediately notified His Reference father Vincento, the inquisitor of Santiago. He promised to look into it, but so far no action was undertaken! I am afraid, His Reverence has more important things to do...";
			link.l1 = "I'll look into it by myself. Perhaps, all these gossips are nothing but the ramblings of drunken hunters - therefore the Inquisition hasn't taken them seriously. I'll head into the jungle to see it all with my own eyes.";
			link.l1.go = "caleuche_1";
		break;
		
		case "caleuche_1":
			dialog.text = "I assure you, my son, it's very serious. The man who told me about the walking dead, deserves my full trust.";
			link.l1 = "Alright. I'll be ready for battle, and if the unholy creatures have indeed taken root in the cavern, I'll purge it of them.";
			link.l1.go = "caleuche_2";
		break;
		
		case "caleuche_2":
			dialog.text = "May our Lord be with you! Here, take this sanctified amulet. It will help you in your battle. Destroy the spawns of the devil!";
			link.l1 = "See you soon, Father "+npchar.name+". Once I am done with that, I'll return to you immediately.";
			link.l1.go = "caleuche_3";
		break;
		
		case "caleuche_3":
			DialogExit();
			AddQuestRecord("Caleuche", "27");
			pchar.questTemp.Caleuche = "cave";
			Log_Info("You have received a church amulet");
			PlaySound("interface\important_item.wav");
			GiveItem2Character(pchar, "amulet_7"); 
			if (GetCharacterIndex("cavehunter") != -1)
			{
				sld = characterFromId("cavehunter");
				sld.dialog.currentnode = "cavehunter_5";
				LAi_SetGuardianType(sld);
				sld.protector = true;
				LAi_group_MoveCharacter(sld, "SPAIN_CITIZENS");
			}
			LocatorReloadEnterDisable("Cuba_Jungle_07", "reload2_back", false);
			pchar.quest.Caleuche_cuba_caveentrance.win_condition.l1 = "location";
			pchar.quest.Caleuche_cuba_caveentrance.win_condition.l1.location = "Cuba_CaveEntrance";
			pchar.quest.Caleuche_cuba_caveentrance.function = "Caleuche_CubaCaveEntrance";
		break;
		
		case "caleuche_4":
			dialog.text = "What have you found there, my son? Perhaps, our fears were unfounded?";
			link.l1 = "Unfortunately, not. The cave was crawling with undead. With God's help I destroyed all the living dead there. They will not bother anyone anymore.";
			link.l1.go = "caleuche_5";
		break;
		
		case "caleuche_5":
			dialog.text = "Praise the Lord! You're indeed His chastising sword, my son! Please allow me to express my deepest gratitude on behalf of the entire parish of Havana. Please accept these sanctified amulets as your reward. Surely, you will find them useful in your perilous journeys.";
			link.l1 = "Thank you, Father "+npchar.name+".";
			link.l1.go = "caleuche_6";
		break;
		
		case "caleuche_6":
			Log_Info("You have received church amulets");
			PlaySound("interface\important_item.wav");
			GiveItem2Character(pchar, "amulet_3"); 
			GiveItem2Character(pchar, "amulet_9"); 
			GiveItem2Character(pchar, "obereg_7"); 
			GiveItem2Character(pchar, "obereg_11"); 
			dialog.text = "Also I'll make sure that both common people and those in power will know about your heroic deed. And I will pray tirelessly for you day and night.";
			link.l1 = "Thank you, Father. I have one more question for you.";
			link.l1.go = "caleuche_7";
		break;
		
		case "caleuche_7":
			dialog.text = "Ask, my son.";
			link.l1 = "Tell me, Father "+npchar.name+", has a man by the name of Joachim Merriman recently arrived at your town? A middle-aged senor, Portuguese, with moustache, imperial beard and piercing eyes?";
			link.l1.go = "caleuche_8";
		break;
		
		case "caleuche_8":
			sld = characterFromId("Villemstad_Priest");
			dialog.text = "That name or description didn't ring a bell, I am sorry. Who is this man?";
			link.l1 = "Merriman is a warlock. The Inquisition has been hunting him for a very long time already. Me and Father "+sld.name+" suspect that the emergence of the living dead on Cuba is his work. Not long ago he had been living in Willemstad, then he suddenly disappeared, and the woman who had rented him a room was turned into the walking skeleton shortly thereafter.";
			link.l1.go = "caleuche_9";
		break;
		
		case "caleuche_9":
			dialog.text = "What a nightmare! I will immediately tell that to the inquisitors, to Father Vincento himself! He must know what's happening here! Tell me, son, you think that people who were gone missing in the jungle...";
			link.l1 = "Yes, I'm almost certain that those living dead in the cavern were your former missing citizens. And I want to look for that Portuguese on Cuba and find him! That scoundrel managed to get a hold of an old heathen relic - a jade skull of Yum Cimil. I am afraid, with that artifact and Indian witchery Merriman will cause even more troubles if nobody stops him anytime soon.";
			link.l1.go = "caleuche_10";
		break;
		
		case "caleuche_10":
			dialog.text = "You think that the story with the undead in the cave can repeat once more?";
			link.l1 = "Almost certainly. I am not sure what drives him, but surely his aspirations are far from being virtuous.";
			link.l1.go = "caleuche_11";
		break;
		
		case "caleuche_11":
			dialog.text = "May the Almighty show mercy on us! Seek him out, my son! I allow you to take any measures against him in the name of our Holy Church! And I will immediately dispatch a messenger to Santiago with a report for Father Vincento.";
			link.l1 = "Good idea! Farewell, Father "+npchar.name+".";
			link.l1.go = "caleuche_12";
		break;
		
		case "caleuche_12":
			DialogExit();
			AddQuestRecord("Caleuche", "29");
			pchar.questTemp.Caleuche = "graveyard";
			AddCharacterMaxHealth(pchar, 3);
			ChangeCharacterComplexReputation(pchar, "nobility", 3);
			ChangeCharacterComplexReputation(pchar, "authority", 2);
			ChangeCharacterComplexReputation(pchar, "fame", 3);
			ChangeCharacterNationReputation(pchar, SPAIN, 10);
			AddCharacterExpToSkill(pchar, "Leadership", 500);
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}



