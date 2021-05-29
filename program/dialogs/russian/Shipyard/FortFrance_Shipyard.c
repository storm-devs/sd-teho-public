// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("What questions do you have?", "How can I help you?"), "You tried to ask me a question a little while ago...", "I have never met people with such one-sided curiosity in my shipyard or anywhere else in this town.",
                          "What's with all the questions? My job is to build ships. Let's take care about that.", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("I've changed my mind...", "I've got nothing to talk about at the moment."), "Umph, where has my memory gone...",
                      "Hm, well...", "Go ahead...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			// Addon-2016 Jason ”ЊЉ-Њартиника
			if (CheckAttribute(pchar, "questTemp.FMQM") && pchar.questTemp.FMQM == "begin")
            {
                link.l1 = "Your man told me that you want to see me. I am all ears.";
                link.l1.go = "FMQM";
            }
			if (CheckAttribute(pchar, "questTemp.FMQM") && pchar.questTemp.FMQM == "oil" && GetSquadronGoods(pchar, GOOD_OIL) >= 50)
            {
                link.l1 = "I've done the job. "+FindRussianQtyString(GetSquadronGoods(pchar, GOOD_OIL))+" barrels of resin are inside my cargo holds.";
                link.l1.go = "FMQM_9";
            }
		break;
		
		// Addon-2016 Jason ”ЊЉ-Њартиника
		case "FMQM":
			pchar.quest.FMQM_Denial.over = "yes";
			dialog.text = "Yes-yes, captain "+GetFullName(pchar)+". I saw your vessel entering our port and immediately sent my worker to you. Straight to the business: you are a newcomer, but they say that you have already become a seasoned sailor and the fortune is on your side. This is why I have a business proposal to you.";
			link.l1 = "Interesting! Go on, tell me.";
			link.l1.go = "FMQM_1";
		break;
		
		case "FMQM_1":
			dialog.text = "Have you ever heard of special resin the Spaniards produce on the island of Trinidad? It is a rare resource of strategic value used to fortify the ship hull. Every barrel costs a hefty sum because the Spanish direct all the resin for the needs of their Navy. Every colonial authority keeps a trade of this good under control, to put it simple, it's a pure contraband\nI need this resin for a special order. Of course, our store doesn't have it, same can be said about our local military warehouses or they simply didn't want to sell it. It's irrelevant really. What is relevant is that I need the resin and I know where to get some. All I need is a captain who is comfortable about boardings.";
			link.l1 = "I think, I am starting to see your point...";
			link.l1.go = "FMQM_2";
		break;
		
		case "FMQM_2":
			dialog.text = "Splendid. There is a small trade convoy located in a harbor of Port-of-Spain. One ship is carrying a decent batch of the resin I am so in need of. I will tell more if you like the idea of plundering the enemies of our nation. What's your call?";
			link.l1 = "I like your proposal. Ready to give it a try.";
			link.l1.go = "FMQM_3";
			link.l2 = "I'll pass, monsieur. My ship and my crew are not in their brightest state at the moment.";
			link.l2.go = "FMQM_exit";
		break;
		
		case "FMQM_exit":
			dialog.text = "Okay, it's your right to do what you want. Sorry for taking your time, captain.";
			link.l1 = "Goodbye.";
			link.l1.go = "FMQM_exit_1";
		break;
		
		case "FMQM_exit_1":
			DialogExit();
			pchar.questTemp.FMQM = "fail";
			AddQuestRecord("FMQ_Martinique", "3");
			CloseQuestHeader("FMQ_Martinique");
		break;
		
		case "FMQM_3":
			string sTemp = "barquentine";
			if (MOD_SKILL_ENEMY_RATE < 7) sTemp = "barque";// Addon 2016-1 Jason пиратскаЯ линейка
			dialog.text = "Then listen: the convoy consists three ships, the resin will be among other goods on a "+sTemp+" called the 'Benseсho'. This is your target. As I've said before, the Spanish are sailing from Port-of-Spain, Trinidad, to San Juan, Puerto Rico. They will set sail tomorrow, so you are free to choose where to attack them.";
			link.l1 = "Got it. What about a reward?";
			link.l1.go = "FMQM_4";
		break;
		
		case "FMQM_4":
			dialog.text = "All I am interested in is the resin. I will pay fifteen golden doubloons for every barrel of stuff. According to my information, the 'Bensecho' carries around a hundred of barrels.";
			link.l1 = "Holy cow! This is a big sum!";
			link.l1.go = "FMQM_5";
		break;
		
		case "FMQM_5":
			dialog.text = "Yes. I told you already that this particular merchandise is very expensive and rare.";
			link.l1 = "You also told me that this is a contraband.";
			link.l1.go = "FMQM_6";
		break;
		
		case "FMQM_6":
			dialog.text = "Don't worry, there will be no need for you to bring it to the store or to smugglers. Come see me when the job's done, we will dock your vessel in my shipyard for repairing and then unload all the cargo secretly at night. No one will suspect anything.";
			link.l1 = "You think ahead, master. Very well. No wasting time them. I am on the way to set sail.";
			link.l1.go = "FMQM_7";
		break;
		
		case "FMQM_7":
			dialog.text = "Godspeed captain.";
			link.l1 = "...";
			link.l1.go = "FMQM_8";
		break;
		
		case "FMQM_8":
			DialogExit();
			pchar.questTemp.FMQM = "convoy";
			AddQuestRecord("FMQ_Martinique", "4");
			SetFunctionTimerCondition("FMQM_ConvoyStart", 0, 0, 1, false);
		break;
		
		case "FMQM_9":
			dialog.text = "Excellent! Let's put your ship in docks as we agreed before. We will unload her there tonight. Get back to you ship and let me prepare the money for you.";
			link.l1 = "Let's do this.";
			link.l1.go = "FMQM_10";
		break;
		
		case "FMQM_10":
			pchar.quest.FMQM_Late.over = "yes";
			DialogExit();
			InterfaceStates.Buttons.Save.enable = false;
			chrDisableReloadToLocation = true;
			pchar.GenQuest.FrameLockEsc = true;
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], true);
			pchar.questTemp.FMQM = "remove_oil";
			pchar.questTemp.FMQM.Oil = "true";
			pchar.questTemp.FMQM.Qty = GetSquadronGoods(pchar, GOOD_OIL);
			DoQuestFunctionDelay("FMQM_WaitTime", 1.0);
			RemoveCharacterGoods(pchar, GOOD_OIL, GetSquadronGoods(pchar, GOOD_OIL));
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

