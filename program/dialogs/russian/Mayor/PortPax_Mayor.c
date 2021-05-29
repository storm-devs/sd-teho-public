// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("What do you want? Ask away.", "I am listening to you, what's the question?"), "It is the second time you are trying to ask...", "It is the third time you are again trying to ask...",
                          "When is it going to end?! I am a busy man, working on the colony's matters and you are still trying to ask something!", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("I have changed my mind...", "Not now. Wrong place and time."), "True... But later, not now...",
                      "I'll ask... But a bit later...", "I am sorry, " + GetAddress_FormToNPC(NPChar) + "...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			// Jason НСО
			if (CheckAttribute(pchar, "questTemp.Patria") && pchar.questTemp.Patria == "epizode_2" && !CheckAttribute(npchar, "quest.patria") && !CheckAttribute(pchar, "questTemp.Patria.Visiter_Late"))
			{
				link.l1 = TimeGreeting()+" monseigneur. I am here as ordered by the Governor General Chevalier da Poincy. My task is to deliver a baron by the name of Noel Forget to Tortuga, who arrived from the parent state with a task to inspect the colonies, his main purpose is establishing French West-Indies trading Company. Let me introduce him to you... He will explain all the details himself.";
                link.l1.go = "patria_portpax";
			}
		break;

		case "Cupture_after":
            dialog.text = RandPhraseSimple("You have taken everything already. What else do you want?", "Is there anything left that you didn't grab?");
            link.l1 = RandPhraseSimple("Just looking around...", "Just checking, I might forget to take something...");
            link.l1.go = "exit";
            NextDiag.TempNode = "Cupture_after";
		break;
		
		// Jason НСО
		case "patria_portpax":
			dialog.text = "I am very glad to meet you, Captain Charles de Maure, and with the Baron. I will do everything for being of Monsieur Forget in our colony was as comfortable as possible. And taking advantage of the fact that such high-ranking people paid me a visit, I will petition you for one matter.";
			link.l1 = "Most interesting! Tell us about your matter, your Grace.";
			link.l1.go = "patria_portpax_1";
		break;
		
		case "patria_portpax_1":
			dialog.text = "In recent months, our colony hasn't been visited by any representative of the Governor General, as if they completely forgot about us at St. Kitts! And in the meantime, the Spaniards, craving to make the whole of Hispaniola purely Spanish and to whom the French settlers and buccaneers at the west of the island are a major annoyance, are preparing an attack! My patrol officers, our trading captains and even ordinary fishermen have reported that a powerful Spanish squadron is gathering in Santiago, and that it is preparing to attack Port-au-Prince!";
			link.l1 = "Is the evidence clear enough, your Majesty?";
			link.l1.go = "patria_portpax_2";
		break;
		
		case "patria_portpax_2":
			dialog.text = "I don't have accurate intel, but such a plenty of information from completely random people can't be mere rumors. Our colony is very important for France, we have the best plantations here, which the Baron can personally see. To lose this colony or even expose it to the risk of being looted is unacceptable!";
			link.l1 = "I will take your evidence into account and inform chevalier de Poincy. I'm sure that he will take immediate measures.";
			link.l1.go = "patria_portpax_3";
		break;
		
		case "patria_portpax_3":
			dialog.text = "Thank you, captain...";
			link.l1 = "";
			link.l1.go = "patria_portpax_4";
		break;
		
		case "patria_portpax_4":
			DialogExit();
			sld = characterFromId("Noel");
			sld.dialog.currentnode = "noel_9";
			ChangeCharacterAddressGroup(sld, pchar.location, "goto", "governor1");
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
			npchar.quest.patria = "true";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

