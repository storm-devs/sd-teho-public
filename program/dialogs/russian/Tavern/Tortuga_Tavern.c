// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat("All the rumors of "+ GetCityName(npchar.city) +" at your service. What would you like to find out?",
                          "We were just talking about that. You must have forgotten...", "This is the third time today you're talking about some question...",
                          "You're repeating all the same like a parrot...", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("You know, " + NPChar.name + ", maybe next time.", "Right, I've forgotten for some reason...",
                      "Yes, it really is the third time...", "Yup...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			if (pchar.questTemp.Slavetrader == "FindRatTortuga") // работорговец
            {
                link.l1 = "Listen, where can I find Francois Gontier? He was supposed to have arrived at Tortuga already.";
                link.l1.go = "Tortuga_ratT_1";
            }
			// суп из черепахи
			if (CheckAttribute(PChar, "questTemp.Terrapin") && pchar.questTemp.Terrapin == "tortuga")
			{
				link.l1 = "I'm looking for Henri Thibaut. Where can I find him?";
				link.l1.go = "terrapin";
			}
			if (CheckAttribute(PChar, "questTemp.Terrapin") && pchar.questTemp.Terrapin == "tortuga1")
			{
				link.l1 = "I'm looking for Henri Thibaut. Where can I find him?";
				link.l1.go = "terrapin_2";
			}
			if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "tortuga")
			{
				link.l1 = "Tell me, has a galleon by the name of 'Santa Margarita' stopped at your colony lately? Maybe as a privateer prize?";
                link.l1.go = "guardoftruth";
			}
			// Addon 2016-1 Jason Пиратская линейка
			if (CheckAttribute(pchar, "questTemp.Mtraxx.Jeweller"))
			{
				link.l1 = "Look pal, I am looking for Gaspard Parmentier. Where can I find him?";
                link.l1.go = "mtraxx_jew";
			}
        break;
        
		case "Tortuga_ratT_1":
			dialog.text = "Francois Gontier? Who is he? I don't know any man by that name.";
			link.l1 = "He's the captain of the corvette '" + pchar.questTemp.Slavetrader.ShipName + "'.";
			link.l1.go = "Tortuga_ratT_2";
        break;
		
		case "Tortuga_ratT_2":
			dialog.text = "I don't have the slightest clue, buddy. And no corvette by that name has docked at our port, I can say that for sure.";
			link.l1 = "Okay then, have you seen any outsiders lately in town?";
			link.l1.go = "Tortuga_ratT_3";
        break;
		
		case "Tortuga_ratT_3":
			dialog.text = "Good question! This is a port town, not a village. Strangers come every day. Though, I have heard about five odd lads, they always stay close together and keep their blades ready\nA patrol even run a check on them with no result. But I am sure that they didn't arrive here on a corvette, no such vessel was seen around, savvy?";
			link.l1 = "Hm... All right then, I see. Thank you, " + npchar.name + ".";
			link.l1.go = "exit";
			AddQuestRecord("Slavetrader", "21_8");
			pchar.questTemp.Slavetrader = "wait1";//затычка
        break;
		
		// суп из черепахи
		case "terrapin":
			dialog.text = "Well, Monsieur Thibaut is a famous individual on Tortuga. His mansion is located near the port authority. When leaving my tavern, head straight toward the port. Approaching the arch leading to the port, turn left on the crossroads and go all the way down to the end of the street where you'll run into a two-story stone building with a red roof. That is Monsieur Thibaut's mansion.";
			link.l1 = "Thank you! I'll go visit him...";
			link.l1.go = "terrapin_1";
		break;
		
		case "terrapin_1":
			DialogExit();
			pchar.questTemp.Terrapin = "house";
			sld = characterFromId("Tibo");
			ChangeCharacterAddressGroup(sld, "Tortuga_houseS2", "barmen", "stay");
			LAi_SetOwnerType(sld);
		break;
		
		case "terrapin_2":
			dialog.text = "Monsieur Thibaut is high in demand today, a messenger from the governor just ran over here. He was interested too. Is that too hard to find him? He's been renting a room from me on the second floor for quite some time, although he has a whole mansion to live in. I don't know what he needs it for, but he comes in a lot more often than he leaves. And he's only there during the evenings.";
			link.l1 = "Maybe, he's here right now.";
			link.l1.go = "terrapin_3";
		break;
		
		case "terrapin_3":
			if (stf(environment.time) < 20.0 && stf(environment.time) > 8.0)
			{
				dialog.text = "No. He said he wouldn't be back until eight in the evening today. You can try looking for him at home in his mansion, but I don't think you'll find him there. I saw his sailing of on a patrol lugger at the sea.";
				link.l1 = "Thank you! I'll stop by to see him later.";
				link.l1.go = "terrapin_4";
			}
			else
			{
				dialog.text = "Yes. If you want, you can come on up.";
				link.l1 = "Thank you! I'll got visit him...";
				link.l1.go = "terrapin_4";
			}
		break;
		
		case "terrapin_4":
			DialogExit();
			pchar.questTemp.Terrapin = "tavern";
			sld = characterFromId("Tibo");
			sld.dialog.currentnode = "tibo_9";
			LAi_SetLoginTime(sld, 20.0, 8.0);
			ChangeCharacterAddressGroup(sld, "Tortuga_tavern_upstairs", "goto", "goto1");
			LocatorReloadEnterDisable("Tortuga_tavern", "reload2_back", false); // откроем комнату
			LAi_LocationFightDisable(&Locations[FindLocation("Tortuga_tavern_upstairs")], true);//запретить драться
			LAi_SetStayType(sld);
			// Addon 2016-1 Jason Пиратская линейка
			if (GetCharacterIndex("Mary") != -1)
			{
				sld = characterFromId("Mary");
				if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && !IsOfficer(sld))
				{
					ChangeCharacterAddressGroup(sld, "none", "", "");
				}
			}
			if (GetCharacterIndex("Helena") != -1)
			{
				sld = characterFromId("Helena");
				if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && !IsOfficer(sld))
				{
					ChangeCharacterAddressGroup(sld, "none", "", "");
				}
			}
		break;
		
		case "guardoftruth":
			dialog.text = "No clue about the ship's name, was it 'Santa Margarita' or 'Castilian Whore' but they brought here a captured Spanish galleon. By the way, captured by a sloop! Gaius Marchais, a captain, had been bragging for two days in a tavern - first voyage and such prize!\nYeah, very heroic deed, to board a galleon filled with church rats absent soldiers. It seems that papists forgot what they say about those who help themselves...";
			link.l1 = "Yes, God helps him who helps himself, that's for sure. How do I get a glimpse of that lucky cap? Is he here, on Tortuga?";
			link.l1.go = "guardoftruth_1";
		break;
		
		case "guardoftruth_1":
			dialog.text = "Ah, who the hell knows. I haven't seen him in my saloon for a long time. As soon as he got sober he brought a trophy galleon to bay and ran around it like a mad man. I have no idea where Marchais is now. Maybe he's on Tortuga or maybe he's at sea.";
			link.l1 = "Alright. Well, thanks for the story, buddy!";
			link.l1.go = "guardoftruth_2";			
		break;
		
		case "guardoftruth_2":
			dialog.text = "Any time, Monsieur "+pchar.name+", any information for our beloved captain, savior of St. Pierre! Stop by later!";
			link.l1 = "...";
			link.l1.go = "exit";	
			AddQuestRecord("Guardoftruth", "8");
			pchar.questTemp.Guardoftruth = "tortuga1";
		break;
		
		// Addon 2016-1 Jason Пиратская линейка
		case "mtraxx_jew":
            dialog.text = "Seems like Gaspard is getting more and more popular among your kind. His house is by the wall. Turn left from the tavern and head to the port, but don't go there, turn left again, go straight and then turn right. A two-storied house.";
			link.l1 = "Thanks!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_WolfreekJewellerHouse");
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

