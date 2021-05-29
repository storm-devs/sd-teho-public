// лидер клана ривадос - Черный Эдди
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
			dialog.text = "What do you need on Rivados' territories, white man?";
			link.l1 = "Just getting to know the local people. Sorry if I have bothered you.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		case "Friend":
			dialog.text = "I am glad to greet a friend of Rivados and a good man also! Chimiset told me what you did for him. All Rivados, including me, are in your debt now. Allow me to introduce myself - Edward Black, also known as Black Eddie, the head of Rivados clan.";
			link.l1 = ""+GetFullName(pchar)+". Though I think that Chimiset has already told you about me. He promised to tell you...";
			link.l1.go = "Friend_1";
		break;
		
		case "Friend_1":
			dialog.text = "And he has. Now you can visit our ships freely. Guards won't stop you and we will always be glad to see you. Be careful with Narwhals, they must have already found out that you saved Chimiset, and they won't like it, since we are enemies.";
			link.l1 = "I will consider that. Thanks for the warm welcome, Eddie! Now please allow me to talk with Chimiset.";
			link.l1.go = "Friend_2";
		break;
		
		case "Friend_2":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocator(npchar, "goto", "goto1", "LSC_EddyStay", -1);
			AddSimpleRumourCityTip("They say that you are a close friend of Black Eddie, the head of Rivados. And how did you do this?", "LostShipsCity", 10, 1, "LSC", "");
			AddSimpleRumourCityTip("Rivados claim you as their friend. Is that so, mister?", "LostShipsCity", 10, 1, "LSC", "");
			AddSimpleRumourCityTip("They say that Narwhals don't like you due to your close relations with Rivados. Is that troubling you?", "LostShipsCity", 10, 1, "LSC", "");
		break;
		
		// --> информационный блок
		case "Total_info": // стал другом
			if (pchar.questTemp.LSC == "return" && !CheckAttribute(npchar, "quest.return_isl"))
			{
				dialog.text = "White brother? Alive? I am glad! So, Narwhals lied when they told everyone that you had drowned...";
				link.l1 = "I am also glad to see you, Eddie. And Narwhals were a bit wrong, I didn't plan to get drowned at all.";
				link.l1.go = "exit";
				npchar.quest.return_isl = "true";
				break;
			}
			dialog.text = "Glad to see you, "+pchar.name+"? Any news?";
			if (!CheckAttribute(npchar, "quest.natan"))
			{
				link.l1 = "Eddie, do you know a man by the name of Nathaniel Hawk? He must be here, as far as I know.";
				link.l1.go = "natan";
			}
			if (!CheckAttribute(npchar, "quest.rivados"))
			{
				link.l2 = "Tell me more about Rivados clan.";
				link.l2.go = "rivados";
			}
			link.l9 = "Nothing special, really. Just wanted to greet you.";
			link.l9.go = "exit";
		break;
		
		case "natan":
			dialog.text = "Nathaniel Hawk? No, I don't know this man. He is neither on the Rivados ships, nor within neutral territories. I can't say the same about Narwhal clan, we don't visit them.";
			link.l1 = "I see...";
			link.l1.go = "exit";
			npchar.quest.natan = "true";
			NextDiag.TempNode = "Total_info";
		break;
		
		case "rivados":
			dialog.text = "Rivados clan was founded many years ago and it was the very first clan of the Island. More than a fifty years ago, admiral Betancourt's expedition sailed across the Caribbean sea on a several large ships. Holds of the Tartarus were filled with hundreds of black slaves, captured back in Africa, their homeland. There was a man named Pedro Rivados\nHe managed to free a few dozens of slaves from their shackles and raised a mutiny. Alas, the rest of slaves failed to join him and his crew. A riot was quelled. Spanish dealt with Rivados in the most cruel manner - they tied him and left him in ship's hold to die from hunger and thirst. The weather went bad that evening and Betancourt's squadron was captured by a powerful storm.\nDays later, after fighting with the weather, the 'San Augustine' and the 'Tartarus', the only two ships stayed intact, were stuck in the middle of the Island. A lot of black and white men died during those events, but much more managed to survive. Ex slaves started a new life together and called themselves Rivados in honour of Pedro Rivados, the liberator.";
			link.l1 = "A very interesting story... Thank you!";
			link.l1.go = "exit";
			npchar.quest.rivados = "true";
			NextDiag.TempNode = "Total_info";
		break;
		// <-- информационный блок
		
		case "capper":
			dialog.text = "What do you need on Rivados' territories, white man?";
			link.l1 = "My name is "+GetFullName(pchar)+" and I am here by order of admiral Dodson. I must talk to Black Eddie. As I understand it is you.";
			link.l1.go = "capper_1";
		break;
		
		case "capper_1":
			dialog.text = "Yes, I am Edward Black also known as Black Eddie. Tell what does the admiral need from me.";
			link.l1 = "There is a man on the 'Tartarus' named Chimiset. Admiral is willing to free him.";
			link.l1.go = "capper_2";
		break;
		
		case "capper_2":
			dialog.text = "This is a very good news. Chimiset is our spiritual leader, and all Rivados miss him. But I understand that the admiral wants something in exchange for his freedom, right?";
			link.l1 = "Nothing. He just wants to free him as a gesture of good will. But there is a problem...";
			link.l1.go = "capper_3";
		break;
		
		case "capper_3":
			dialog.text = "Go on, white man.";
			link.l1 = "The ex boatswain of the admiral, the current jailer Chad Kapper joined Narwhals, turned rogue and now he is out of admiral's control. We know that Chad is planning to kill Chimiset. Admiral doesn't want it to happen. We offer you a combined operation in order to eliminate the traitor and to free your man.";
			link.l1.go = "capper_4";
		break;
		
		case "capper_4":
			dialog.text = "You words sound a bit odd, but go on. Is Chimiset in trouble?";
			link.l1 = "Yes. Chad is planning to kill him. Kapper is going to use Narwhals in order to seize control of the Island. We have to act quickly if we want to save Chimiset, since Chad doesn't suspect anything for now. Admiral has taken all guards from the 'Tartarus', the passage is free. Here is the key which opens the door inside the prison. Take it.";
			link.l1.go = "capper_5";
		break;
		
		case "capper_5":
			RemoveItems(pchar, "key_capper", 1);
			dialog.text = "";
			link.l1 = "Gather your men, go to the Tartarus and free Chimiset. All aces are yours.";
			link.l1.go = "capper_6";
		break;
		
		case "capper_6":
			dialog.text = "It smells like a trap... And what if there is an ambush? What if admiral decided to strike Rivados down? Why won't he deal with Kapper himself?";
			link.l1 = "Dodson said that you care about Chimiset's life... He did enough: there is a key and guards are off. You only need to get inside, deal with Chad and free your man. You have my word that there is no trap. Yeah, and one last thing: admiral wants Chad's head in exchange for Chimiset's life and freedom. Do we have an agreement?";
			link.l1.go = "capper_7";
		break;
		
		case "capper_7":
			dialog.text = "Chimiset's life is valued by Rivados beyond measure. We will move to the 'Tartarus' immediately. But you will stay here as our hostage. And if there is an admiral's ambush, you will face the rage of Rivados!\nZikomo! Stay near the door and watch our guest. Don't let him out. I will lead the attack on the 'Tartarus'!";
			link.l1 = "Good luck, Eddie. And remember: I need the head of Chad Kapper!";
			link.l1.go = "capper_8";
		break;
		
		case "capper_8":
			DialogExit();
			chrDisableReloadToLocation = true;//закрыть локацию
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "LSC_ZikomoNearDoor", 10.0);
			NextDiag.CurrentNode = "chimiset";
		break;
		
		case "chimiset":
			dialog.text = "Chimiset is set free! You weren't lying, white man, I am ready to call you a friend of Rivados!";
			link.l1 = "I am glad. Is Chad Kapper dead?";
			link.l1.go = "chimiset_1";
		break;
		
		case "chimiset_1":
			dialog.text = "I have to ask for your forgiveness, white friend: you did everything you could for us, but we have failed you... I have failed you! Damn Kapper escaped. There were two Narwhals with him. We killed them, but the filthy jailer swam away through the lower door to Narwhal territories.";
			link.l1 = "Fuck... Didn't you know that there were two exits from the 'Tartarus'?";
			link.l1.go = "chimiset_2";
		break;
		
		case "chimiset_2":
			dialog.text = "We didn't think about it. We attacked from the main entrance...";
			link.l1 = "Pity. I was counting on his head. Too bad. Now he will continue to act against us.";
			link.l1.go = "chimiset_3";
		break;
		
		case "chimiset_3":
			dialog.text = "I admit my guilt. But we couldn't follow him to hostile ships. You will have our friendship and respect instead of Chad's head. From now on, you are allowed to visit our territory freely. Chimiset's wisdom will serve you well too, talk to him if you need anything. Talk to him if you need. Also, tell the admiral my assurances that I appreciated his action.";
			link.l1 = "Fine.";
			link.l1.go = "chimiset_4";
		break;
		
		case "chimiset_4":
			dialog.text = "Wait! We have lost Chad, but I have found a few papers on his desk, which he was studying when we arrived. Here they are. You might find them useful, white brother.";
			link.l1 = "Ha! Perhaps... Chad puts a great trust in paper...";
			link.l1.go = "chimiset_5";
		break;
		
		case "chimiset_5":
			dialog.text = "You are always a welcome guest here, white friend. All Rivados will be informed about it. Good luck!";
			link.l1 = "Same to you, Eddie...";
			link.l1.go = "chimiset_6";
		break;
		
		case "chimiset_6":
			DialogExit();
			LAi_ActorGoToLocator(npchar, "goto", "goto1", "LSC_EddyStay", -1);
			sld = CharacterFromID("Zikomo");
            LAi_SetWarriorType(sld);
			LAi_warrior_SetStay(sld, true);
			LAi_warrior_DialogEnable(sld, true);
			GiveItem2Character(pchar, "letter_chad");
			ChangeItemDescribe("letter_chad", "itmdescr_letter_aeva");
			GiveItem2Character(pchar, "letter_chad_1");
			ChangeItemDescribe("letter_chad_1", "itmdescr_letter_axel");
			pchar.questTemp.LSC.rvd_friend = "true"; //флаг на проход по кораблям ривадос
			pchar.questTemp.Saga.SharkHunt = "dodson_whiskey"; // к Акуле
			sld = CharacterFromID("Dodson");
			sld.dialog.currentnode = "Chad_escape"; // ноду Акуле
			AddQuestRecord("SharkHunt", "33");
			LocatorReloadEnterDisable("LostShipsCity_town", "reload48", true); // закрыть вход к Дональду Гринспи
			AddSimpleRumourCityTip("Have you heard the last news? Rivados' insolence is off limits now, they have attacked admiral's prison and released their wizard!", "LostShipsCity", 3, 2, "LSC", "");
			AddSimpleRumourCityTip("Just think about it - Rivados dared to attack the 'Tartarus'! They say that the jailer, Chad Kapper, has escaped to Narwhals...", "LostShipsCity", 3, 2, "LSC", "");
			AddSimpleRumourCityTip("This is the height of impudence, isn't it? Attacking a military facility of the admiral! Yeah, looks like Black Eddie is getting stronger...", "LostShipsCity", 3, 2, "LSC", "");
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
	}
}