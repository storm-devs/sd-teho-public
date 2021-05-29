// полковник Фокс - бравый командир морской пехоты 'морские лисы'.
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (CheckAttribute(pchar, "questTemp.Terrapin_KathyReward"))
			{
				dialog.text = "What do you want, sir? Hm... wait! Now I see, you are that French captain who has saved my daughter from the dirty hands of servants of that damn bastard Levasseur!";
				link.l1 = "I see that Katherine has already told you about me...";
				link.l1.go = "terrapin";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.Guardoftruth.Usurer") && !CheckAttribute(npchar, "quest.utensil"))
			{
				dialog.text = "What do you want, sir?";
				link.l1 = "Good day, colonel. I came to you because of an uncommon business. Would you spare a bit time for me?";
				link.l1.go = "guardoftruth";
				break;
			}
			// Addon-2016 Jason, французские миниквесты (ФМК) Сент-Кристофер
			if (CheckAttribute(pchar, "questTemp.FMQN") && pchar.questTemp.FMQN == "eng_reward")
			{
				dialog.text = "As far as I understand, you are that French captain who had been assisting my men in their mission on Sint-Maarten? "+TimeGreeting()+"!";
				link.l1 = TimeGreeting()+", colonel. Yes, that's me.";
				link.l1.go = "FMQN";
				break;
			}
			dialog.text = "What do you want, sir?";
			link.l1 = "Nothing. I am already leaving.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		case "guardoftruth":
			dialog.text = "Lay out what you have there if you have already come here...";
			link.l1 = "You've recently boarded a schooner under the command of Rollie the Cap, the Holland pirate, and brought the captain here, to St. John's.";
			link.l1.go = "guardoftruth_1";
		break;
		
		case "guardoftruth_1":
			dialog.text = "Captain? Oh, no! The head of criminal scum has no rights to be called by this honorable rank. I have captured a damn pirate, head of wolf's herd, who had been robbing and murdering English traders. And I made sure that he and his degenerates got just what they deserved - the whole St. John's was watching their hanging on the pier!";
			link.l1 = "I see that I won't be able to have a talk with this scoundrel... Colonel, perhaps you could help me? The pirate could have a thing which didn't belong to him - the golden censer. Have you found it?";
			link.l1.go = "guardoftruth_2";
		break;
		
		case "guardoftruth_2":
			dialog.text = "There were no things belonging to that rascal, all of them were taken from honest traders! And what about your concern... no, we have not found it. And what could censer possibly do on the pirate vessel? Do you really think that there was a priest among them?";
			link.l1 = "I don't. Rollie the Cap bought it from the usurer in Willemstad, who had got it from another pirate before. The thing is fine and expensive. I suppose that Rollie had his eye on it like a magpie.";
			link.l1.go = "guardoftruth_3";
		break;
		
		case "guardoftruth_3":
			dialog.text = "To be honest, Rollie had empty holds and a few doubloons in chests when we captured his ship by boarding. Rubbish. No valuables, and of course no golden censer. I'd note such an inappropriate item for a pirate\nI have a supposition that damn Cap has hidden his savings at Dominica. We even landed there and raided the area but found nothing. We didn't stay at the island or explored its depths due to a large amount of savages there.";
			link.l1 = "Hm... The Cap could stash the censer with the rest of his stolen things somewhere at Dominica... Too bad. Had you interrogated the pirate before an execution?";
			link.l1.go = "guardoftruth_4";
		break;
		
		case "guardoftruth_4":
			dialog.text = "I had, but he was just laughing in my face. But I didn't really care about his stashes. Rollie the Cap was hung and that's the most important thing.";
			link.l1 = "I see. Thanks for your story and your time. Farewell...";
			link.l1.go = "guardoftruth_5";
		break;
		
		case "guardoftruth_5":
			DialogExit();
			npchar.quest.utensil = "true";
			AddQuestRecord("Guardoftruth", "24");
			Island_SetReloadEnableGlobal("Dominica", true);//patch-7
			// заполняем сундук
			pchar.GenQuestBox.Shore27 = true;
			pchar.GenQuestBox.Shore27.box1.money = 30000;
			pchar.GenQuestBox.Shore27.box1.items.gold_dublon = 100;
			pchar.GenQuestBox.Shore27.box1.items.chest = 1;
			pchar.GenQuestBox.Shore27.box1.items.icollection = 1;
			pchar.GenQuestBox.Shore27.box1.items.jewelry40 = 15;
			pchar.GenQuestBox.Shore27.box1.items.jewelry41 = 22;
			pchar.GenQuestBox.Shore27.box1.items.jewelry42 = 8;
			pchar.GenQuestBox.Shore27.box1.items.jewelry43 = 20;
			pchar.GenQuestBox.Shore27.box1.items.jewelry44 = 33;
			pchar.GenQuestBox.Shore27.box1.items.jewelry45 = 16;
			pchar.GenQuestBox.Shore27.box1.items.jewelry46 = 58;
			pchar.GenQuestBox.Shore27.box1.items.jewelry35 = 1; // кадило
			pchar.quest.GuardOT_finddominicachest.win_condition.l1 = "item";
			pchar.quest.GuardOT_finddominicachest.win_condition.l1.item = "jewelry35";
			pchar.quest.GuardOT_finddominicachest.function = "GuardOT_DominicaChest";
		break;
		
		case "terrapin":
			dialog.text = "Several times, captain! You have done such a deed which was hardly to expect from the French. I really appreciate you as a soldier and as a father. There is no such a valuable thing for me in this world as my daughter...";
			link.l1 = "I am glad that this story had a good ending. I hope that you'll change your mind about French now.";
			link.l1.go = "terrapin_1";
		break;
		
		case "terrapin_1":
			dialog.text = "The presence of such a honorable and unselfish gentleman like you, who has risked his life for saving an unfamiliar with him English girl, will cause an essential warming of my relation to your compatriots!";
			link.l1 = "There are honest people among with rats in any nation, colonel...";
			link.l1.go = "terrapin_2";
		break;
		
		case "terrapin_2":
			dialog.text = "And you have proven that! Reward is awaiting for you, captain. Surely, the life of daughter is priceless, but Jonathan Fox always pays his debts, I swear it! You are a real soldier, therefore, my gift for you is a soldier gift. Here, take a look\nThis is a blunderbuss, an excellent navy musket, can be used by one hand. You can load it with special arrows which will always pierce even the most durable cuirass. It also shoots grape and its solid construction allows to load it with charges of nails. Here, take it, it's yours now.";
			link.l1 = "Such an excellent gift for a soldier, I agree with you!";
			link.l1.go = "terrapin_3";
		break;
		
		case "terrapin_3":
			Log_Info("You have received a blunderbuss");
			Log_Info("You have received 10 arrows");
			Log_Info("You have received 10 charges of nails");
			Log_Info("You have received an instruction for creating the harpoon arrows");
			Log_Info("You have received an instruction for creating the charge of nails");
			GiveItem2Character(pchar, "pistol8");
			TakeNItems(pchar, "harpoon", 10);
			TakeNItems(pchar, "GunEchin", 10);
			GiveItem2Character(pchar, "recipe_harpoon"); 
			GiveItem2Character(pchar, "recipe_GunEchin"); 
			PlaySound("interface\important_item.wav");
			dialog.text = "I also present you a small bunch of ammo and instructions for creating it. It would be sad if you won't use its power at maximum!";
			link.l1 = "Thank you, colonel. I won't reject such a present but I want you to know that I had been saving Katherine from those bastards not for a reward. I just could not left the unprotected girl to them.";
			link.l1.go = "terrapin_4";
		break;
		
		case "terrapin_4":
			dialog.text = "I know that, captain. And it honors you in double. Katherine was really ravished by you and it's not an easy task to make a positive impression on her. And again, receive our gratitudes for her saving.";
			link.l1 = "Thank you for you present, colonel. Send Katherine my best regards and wish that she would listen her father next time.";
			link.l1.go = "terrapin_5";
		break;
		
		case "terrapin_5":
			dialog.text = "I will, captain! Goodbye!";
			link.l1 = "Goodbye, colonel.";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.Terrapin_KathyReward");
			ChangeCharacterComplexReputation(pchar, "nobility", 5);
			ChangeCharacterComplexReputation(pchar, "fame", 5);
			ChangeCharacterNationReputation(pchar, ENGLAND, 20);
		break;
		
		// Addon-2016 Jason, французские миниквесты (ФМК) Сент-Кристофер
		case "FMQN":
			dialog.text = "I read the report. Your actions were highly evaluated, therefore you must be rewarded. It's thirty thousand pesos for expedition services and weapons for heroism in soldiery. Accept this blade and this arquebus. There are all yours now!";
			link.l1 = "Thank you, sir.";
			link.l1.go = "FMQN_1";
		break;
		
		case "FMQN_1":
			dialog.text = "By all means, you are also rewarded with love and respect of British colonists, authorities and myself personally. Thank you for not abandoning my men and helping them in their mission!";
			link.l1 = "Always a pleasure, colonel...";
			link.l1.go = "FMQN_2";
		break;
		
		case "FMQN_2":
			dialog.text = "Now, please, excuse me - I have other business to attend to. Godspeed, captain.";
			link.l1 = "Farewell, sir.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("FMQN_EnglandComplete");
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}