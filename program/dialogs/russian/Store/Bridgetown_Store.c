// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{

	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat("Go ahead, what do you want?",
                          "We were just talking about that. You must have forgotten...", "This is the third time today you're talking about some question...",
                          "Listen, this is a store. People buy stuff here. Don't disturb me!", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("You know, " + NPChar.name + ", maybe next time.", "Right, I've forgotten for some reason...",
                      "Yes, it really is the third time...", "Hm, I wont...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			//Голландский гамбит
			if (CheckAttribute(pchar, "questTemp.HWIC.Eng") && pchar.questTemp.HWIC.Eng == "GotoBridgetown" && !CheckAttribute(npchar, "quest.HWICTalked"))
            {
                link.l1 = "Listen, a little bird told me that the prices for red wood and cocoa in Belize are going to shoot up pretty soon. I've made a good deal recently and fully stuffed my purse of doubloons, he-he... I'd like to acquire a batch of this merchandise. Can I count on a discount?";
                link.l1.go = "StoreDone";
            }
			if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "barbados1")
			{
				link.l1 = "A galleon named 'Admirable' have recently docked at your colony under the command of a captain Gaius Marchais. Tell me, could he have stocked up on ammunition here or merchandise to resell?";
                link.l1.go = "guardoftruth";
			}
		break;
		
		case "StoreDone":
			dialog.text = "Well, sir, if the batch is really large, then of course, we can discuss a discount.";
			link.l1 = "Wonderful! I heard that a new flute should come out for sale at the shipyard any day now. I'll wait up and buy that ship. The thing is even though I've taken off all the weapon of my brig, there's still not enough place in the hold. I'll stop by later!";
			link.l1.go = "exit";	
			npchar.quest.HWICTalked = "true";
			pchar.questTemp.HWIC.Eng.BridgeCounter = sti(pchar.questTemp.HWIC.Eng.BridgeCounter)+1;
			AddQuestRecord("Holl_Gambit", "2-11");
			if (sti(pchar.questTemp.HWIC.Eng.BridgeCounter) == 7) 
			{
				AddQuestRecord("Holl_Gambit", "2-6");
				pchar.questTemp.HWIC.Eng = "SeekVanBerg";
				pchar.quest.GotoBridgetownOver.over = "yes";//снять таймер
				pchar.quest.VanBergAttack_Check.win_condition.l1 = "MapEnter";
				pchar.quest.VanBergAttack_Check.function = "VanBergAttackCheck";
			}
		break;
		
		case "guardoftruth":
			dialog.text = "Ha! I remember that strange guy! He trusted stupid gossips that Guadeloupe will desperately need vanilla because some grand caravan of European merchants will make a stop there in order to buy as much spicery as they can\nI hear such bullshit every month, but Marchais took this most seriously. He had spent a week here, waiting me to gather enough vanilla to fill his cargo holds\nIt appears that he had spent every coin on this. I feel bad for that man, but I never forbid people to go mad if they want to.";
			link.l1 = "So, he might be in Guadeloupe right now?";
			link.l1.go = "guardoftruth_1";
		break;
		
		case "guardoftruth_1":
			dialog.text = "Most likely. Because he will continue waiting for his 'merchants' until Christ's second arrival and he'll only lose money selling vanilla. If he's smart, he'll stay in Basse-Terre until the demand for vanilla shoots up or until he finds out for sure another place where it's needed more.";
			link.l1 = "Okay. Thank you, you've helped me a lot!";
			link.l1.go = "guardoftruth_2";
		break;
		
		case "guardoftruth_2":
			DialogExit();
			AddQuestRecord("Guardoftruth", "14");
			pchar.questTemp.Guardoftruth = "guadeloupe";
			pchar.quest.GuardOT_guadeloupe.win_condition.l1 = "location";
			pchar.quest.GuardOT_guadeloupe.win_condition.l1.location = "guadeloupe";
			pchar.quest.GuardOT_guadeloupe.function = "GuardOT_CreateTwoShips";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);
}

