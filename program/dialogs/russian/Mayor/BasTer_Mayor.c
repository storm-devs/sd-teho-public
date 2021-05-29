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
			if (CheckAttribute(pchar, "questTemp.Guardoftruth.Baster_church") && !CheckAttribute(npchar, "quest.utensil"))
			{
				link.l1 = "I have a delicate matter to you. Not long ago one privateer has granted a golden cross with a lazurite on it to the parish of Basse-Terre. The problem is that the cross was stolen from the Santiago's parish and a clergyman was murdered during the theft...";
                link.l1.go = "guardoftruth";
			}
			// Jason НСО
			if (CheckAttribute(pchar, "questTemp.Patria") && pchar.questTemp.Patria == "epizode_9_continue" && !CheckAttribute(npchar, "quest.frigate"))
			{
				link.l1 = "I arrived by the order of Governor General Philippe de Poincy to take command of your armed frigate.";
                link.l1.go = "patria";
			}
			if (CheckAttribute(npchar, "quest.frigate.wait") && GetCompanionQuantity(pchar) < 5)
			{
				link.l1 = "I'm ready to take the frigate into the squadron.";
                link.l1.go = "patria_2";
			}
			// Jason Дороже золота
			if (CheckAttribute(pchar, "questTemp.GoldenGirl") && pchar.questTemp.GoldenGirl == "baster")
			{
				link.l1 = "I've got a meeting here with one person...";
                link.l1.go = "baster_goldengirl";
			}
		break;
		//************************** Квестовые штрумы ************************
		case "Cupture_after":
            dialog.text = RandPhraseSimple("You have taken everything already. What else do you want?", "Is there anything left that you didn't grab?");
            link.l1 = RandPhraseSimple("Just looking around...", "Just checking, I might forget to take something...");
            link.l1.go = "exit";
            NextDiag.TempNode = "Cupture_after";
		break;
		
		case "guardoftruth":
			dialog.text = "Hm. That's quite interesting. But why do you think that I care about problems of Spanish?";
			link.l1 = "It is not about the Spanish, monsieur. Religion doesn't divide people by nationality. There is an item which is covered in the holy servant's blood in your parish and there was a desecration made to the Santiago's parish...";
			link.l1.go = "guardoftruth_1";
		break;
		
		case "guardoftruth_1":
			dialog.text = "";
			link.l1 = "I ask you to show a justice and to order holy father to return the cross to it's owners.";
			link.l1.go = "guardoftruth_2";
		break;
		
		case "guardoftruth_2":
			dialog.text = "And since when have you become such a true and earnest believer, ha, "+pchar.name+"? Spanish are not our friends and I see no reason to push on the holy father in this matter. The cross was a gift and that's fine. Our priest has no connection to that theft and murder, so...";
			link.l1 = "And you can't help me, right?";
			link.l1.go = "guardoftruth_3";
		break;
		
		case "guardoftruth_3":
			dialog.text = "To be honest, "+pchar.name+", I don't feel that I have to. I have no love to those Papist's fanatics.";
			link.l1 = "I see. Sorry for troubling you, monsieur...";
			link.l1.go = "guardoftruth_4";
		break;
		
		case "guardoftruth_4":
			DialogExit();
			npchar.quest.utensil = "true";
			AddQuestRecord("Guardoftruth", "28");
		break;
		
		// Jason НСО
		case "patria":
			if (GetCompanionQuantity(pchar) > 4)
			{
				dialog.text = "The ship is ready, but you don't have a free spot for it in your squadron. Captain, reduce your squadron and return, then I will immediately give you the frigate.";
				link.l1 = "Fine.";
				link.l1.go = "patria_1";
			}
			else
			{
				dialog.text = "Yes, of course, the ship is ready to sail. Its captain is aware and will follow all of your orders.";
				link.l1 = "Then we're setting out. Goodbye, Your Grace.";
				link.l1.go = "patria_3";
			}
		break;
		
		case "patria_1":
			DialogExit();
			npchar.quest.frigate.wait = "true";
		break;
		
		case "patria_2":
			DeleteAttribute(npchar, "quest.frigate.wait");
			dialog.text = "Excellent. Prepare to greet your new ship. Its captain is aware and will follow all of your orders.";
			link.l1 = "Then we're setting out. Goodbye, Your Grace.";
			link.l1.go = "patria_3";
		break;
		
		case "patria_3":
			DialogExit();
			npchar.quest.frigate = "true";
			Patria_BastionFrigateGlp(); // присоединяем фрегат
		break;
		
		// Jason Дороже золота
		case "baster_goldengirl":
			dialog.text = "Ah, Monseniour Charles de Maure, perfect timing! My old friend is very eager to meet you and asked to let him know of your arrival. Please, come to a living room, I will let Angerran know immediately. How did you two get familiar by the way?";
			link.l1 = "Gambled together. He lost, we had a small fight. I suppose, Monseniour de Chievous would like to fix things between us.";
			link.l1.go = "baster_goldengirl_1";
		break;
		
		case "baster_goldengirl_1":
			dialog.text = "No doubt! I hope you will get things straight between us. Angerran might be not the most pleasant person to deal with, but his is clever and honorable, just like you are. It is a rare breed.";
			link.l1 = "You flatter me, Excellency. I will wait for him in the living room if you don't mind.";
			link.l1.go = "baster_goldengirl_2";
		break;
		
		case "baster_goldengirl_2":
			dialog.text = "But of course, suit yourself, be like at home. Perhaps you will have to wait a little. I will order to bring the drinks.";
			link.l1 = "Thank you, Excellency, but I'll pass. I will just sit and wait for our mutual... friend.";
			link.l1.go = "baster_goldengirl_3";
		break;
		
		case "baster_goldengirl_3":
			DialogExit();
			pchar.questTemp.GoldenGirl = "baster1";
			DoQuestReloadToLocation("CommonResidence_3", "reload", "reload1", "GoldenGirl_AngerranInResidence");
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

