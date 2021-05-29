void ProcessDialogEvent()
{
	ref sld, NPChar;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "Bug. Let the devs know.";
			link.l1 = "I will!";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
		case "RedChieftain":
			dialog.text = "Greetings, white man. I see that you are captain of big canoe. Me Kanauri and I am chief of Cayman the mighty Arawak tribe. Me want to talk with you.";
			link.l1 = "I am listening, chief. What troubles have brought you to me?";
			link.l1.go = "RedChieftain_0";
			link.l2 = "What do you want from me, red-skinned ape? Go to your jungles and don't bother me with your requests.";
			link.l2.go = "RedChieftain_exit";
		break;
		
		case "RedChieftain_exit":
			dialog.text = "Gu-u! Gu-u! Wasn't white captain educated to be polite? I want offer you earn a lot money but now I go. Farewell, paleface.";
			link.l1 = "Go, get lost...";
			link.l1.go = "RedChieftain_exit_1";
		break;
		
		case "RedChieftain_exit_1":
			DialogExit();
			LAi_ActorRunToLocation(npchar, "reload", "reload4_back", "none", "", "", "", -1);
			npchar.lifeday = 0;
			DeleteAttribute(pchar, "questTemp.RedChieftain");
			chrDisableReloadToLocation = false;
			ChangeIndianRelation(-3.0);
		break;
		
		case "RedChieftain_0":
			dialog.text = "White brother is insightful like a serpent. Trouble happen with my kind. Big-big canoe of white men come to my village. They capture many men of my kind, put them on their canoe and take them to sea...";
			link.l1 = "Wait... do you say that your people were enslaved by white men from the ship?";
			if (sti(pchar.Basenation) == SPAIN) link.l1.go = "RedChieftain_2";
			else link.l1.go = "RedChieftain_1";
		break;
		
		case "RedChieftain_1":
			dialog.text = "True, white brother. I know those people are not friends to you. Spanish. They take away my people and I find them. Spanish make Indian work from dawn to dusk, dive water, find shells with tears of gods.";
			link.l1 = "Pearl divers... This is a tough work.";
			link.l1.go = "RedChieftain_3";
			pchar.questTemp.RedChieftain.Spa = "true";
			pchar.questTemp.RedChieftain.AttackNation = SPAIN;
		break;
		
		case "RedChieftain_2":
			dialog.text = "True, white brother. I know those people are not friends to you. English. They take away my people and I find them. English make Indian work from dawn to dusk, dive water, find shells with tears of gods.";
			link.l1 = "Pearl divers... This is a tough work.";
			link.l1.go = "RedChieftain_3";
			pchar.questTemp.RedChieftain.Eng = "true";
			pchar.questTemp.RedChieftain.AttackNation = ENGLAND;
		break;
		
		case "RedChieftain_3":
			dialog.text = "Indian ill and die of tough work. White people no pity for Indian. Lash and pistol is law of white for Indian. Me old and no men for fight. Arawaks are peaceful people. I ask you, white brother, to unsheathe lash and pistol against our common enemy.";
			link.l1 = "Hm. I don't understand what do you want from me. Do I need to declare a war?";
			link.l1.go = "RedChieftain_4";
		break;
		
		case "RedChieftain_4":
			dialog.text = "Free my men. We give you all tears of gods from boats. Kill evil white, help Indian, get tears of Gods, sell them for much-much gold.";
			link.l1 = "Ah, I see now. No, Canauri, I can't help you. I can't do it now - my ship is in need to be repaired, no supplies left...";
			link.l1.go = "RedChieftain_wait";
			link.l2 = "It will be my pleasure to do that. Let's discuss details. Where are your people? You said that you'd already found them...";
			link.l2.go = "RedChieftain_5";
		break;
		
		case "RedChieftain_wait":
			dialog.text = "Gu-u! I can wait, white brother... I be in this port one more moon, look for protector of my kind. You find me here.";
			link.l1 = "...";
			link.l1.go = "RedChieftain_wait_1";
		break;
		
		case "RedChieftain_wait_1":
			DialogExit();
			LAi_ActorGoToLocator(npchar, "quest", "quest1", "RedChieftainStay", -1);
			chrDisableReloadToLocation = false;
			bDisableFastReload = false;
			SetFunctionTimerCondition("RedChieftainDelete", 0, 0, 30, false);
		break;
		
		case "RedChieftain_wait_2":
			dialog.text = "You back, white brother? Will you help me to punish evil people and save Indian?";
			link.l1 = "Yes, I suppose I can do that...";
			link.l1.go = "RedChieftain_wait_4";
			link.l2 = "I still need to get prepared.";
			link.l2.go = "RedChieftain_wait_3";
		break;
		
		case "RedChieftain_wait_3":
			dialog.text = "I will be here, white brother.";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.Tempnode = "RedChieftain_wait_2";
		break;
		
		case "RedChieftain_wait_4":
			dialog.text = "I am very glad that you agreed, white brother!";
			link.l1 = "Let's talk about the details, Canauri. Where are your people? You said that you'd already found them...";
			link.l1.go = "RedChieftain_5";
			pchar.quest.RedChieftainDelete.over = "yes"; //снять таймер
		break;
		
		case "RedChieftain_5":
			if (CheckAttribute(pchar, "questTemp.RedChieftain.Spa"))
			{
				pchar.questTemp.RedChieftain.Island = "Cumana";
				pchar.questTemp.RedChieftain.Shore = "Shore19";
				pchar.questTemp.RedChieftain.Add1 = "Spanish";
				pchar.questTemp.RedChieftain.Add2 = "Carupano Cove, not far from Cumana";
				dialog.text = "They are in camp at Carupano Cove near Spanish settlement Cumana. Every day they sail on boats at the sea, dive water, deep-deep...";
				link.l1 = "I see. And, of course, the Spanish are watching over them?";
				link.l1.go = "RedChieftain_6";
			}
			else
			{
				pchar.questTemp.RedChieftain.Island = "SantaCatalina";
				pchar.questTemp.RedChieftain.Shore = "Shore54";
				pchar.questTemp.RedChieftain.Add1 = "English";
				pchar.questTemp.RedChieftain.Add2 = "Cape Perlas, not far from Blueweld";
				dialog.text = "They are in camp at Cape Perlas near English settlement Blueweld. Every day they sail on boats at the sea, dive water, deep-deep...";
				link.l1 = "I see. And, of course, the English are watching over them?";
				link.l1.go = "RedChieftain_6";
			}
		break;
		
		case "RedChieftain_6":
			dialog.text = "Yes, two canoe of palefaces with soldiers. Camp on the shore is also guarded - Indian can not escape.";
			link.l1 = "What kind of ships? Can you describe them? How big are they? What kind of sails?";
			link.l1.go = "RedChieftain_7";
		break;
		
		case "RedChieftain_7":
			dialog.text = "Canoe is big, but there are bigger. Front sail is very-very fore-and-aft, three angles. Top of behind is narrow, bottom is wide.";
			link.l1 = "Sounds like a schooner...";
			link.l1.go = "RedChieftain_8";
		break;
		
		case "RedChieftain_8":
			dialog.text = "Canauri not know. Paleface dogs very careful if they see other canoe - they land Indian and wait until other canoe sail away.";
			link.l1 = "Too bad. And how can I get close to them?";
			link.l1.go = "RedChieftain_9";
		break;
		
		case "RedChieftain_9":
			dialog.text = "If paleface brother take small canoe then he can sneak near the shore. I show the way. But only one small canoe or paleface dog see and drive Indian from boat to jungles...";
			link.l1 = "Got it. I need a lugger or a sloop for this operation. Hm. A sloop against two schooners... So much for Paris life!";
			link.l1.go = "RedChieftain_10";
		break;
		
		case "RedChieftain_10":
			dialog.text = "Do we go, white brother? We have less than a moon.";
			link.l1 = "Yes. Get on my ship, chief. Let's not waste time!";
			link.l1.go = "RedChieftain_11";
		break;
		
		case "RedChieftain_11":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "", -1);
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, false);
			chrDisableReloadToLocation = false;
			bDisableFastReload = false;
			pchar.quest.Red_Chieftain_2.win_condition.l1 = "location";
			pchar.quest.Red_Chieftain_2.win_condition.l1.location = pchar.questTemp.RedChieftain.Island;
			pchar.quest.Red_Chieftain_2.function = "RedChieftain_CreateShooner";
			SetFunctionTimerCondition("RedChieftainOver", 0, 0, 30, false);
			AddQuestRecord("RedChieftain", "1");
			AddQuestUserData("RedChieftain", "sText1", pchar.questTemp.RedChieftain.Add1);
			AddQuestUserData("RedChieftain", "sText2", pchar.questTemp.RedChieftain.Add2);
		break;
		
		case "RedChieftain_pearl":
			dialog.text = "Thank you, white brother. You saved my kind and Indian owe you. Path is free of paleface dog and Indian can go in jungles. We give you all tears of gods left on boats.";
			link.l1 = "Well, let's see what you've got...";
			link.l1.go = "RedChieftain_pearl_1";
		break;
		
		case "RedChieftain_pearl_1":
			DialogExit();
			pchar.questTemp.RedChieftain.Ind = 1;
			AddDialogExitQuest("RedChieftain_Pearl");
		break;
		
		case "RedChieftain_pearl_give":
			int iSmallPearl = rand(200)+rand(250)+rand(200)+250;
			int iBigPearl = rand(100)+rand(100)+rand(50)+150;
			TakeNItems(pchar, "jewelry52", iBigPearl);
			TakeNItems(pchar, "jewelry53", iSmallPearl);
			PlaySound("interface\important_item.wav");
			Log_SetStringToLog("Indian has given to you "+iSmallPearl+" small and "+iBigPearl+" big pearls.");
			dialog.text = LinkRandPhrase("I glad that tears of gods are yours!","Indian thank you, brave paleface!","Take our catch, white brother!");
			link.l1 = LinkRandPhrase("Glad to help you!","Thanks, red-skinned brother!","Great!");
			link.l1.go = "exit";
			pchar.questTemp.RedChieftain.Ind = sti(pchar.questTemp.RedChieftain.Ind)+1;
			AddDialogExitQuest("RedChieftain_Pearl");
		break;
		
		case "RedChieftain_final":
			chrDisableReloadToLocation = false;//открыть локацию
			dialog.text = "Canauri thank you again, paleface brother! I hope that tears of gods will be enough reward for life of Indians. Now goodbye, we go to native village.";
			link.l1 = "Good luck, Cunauri! Never fall into slavery again!";
			link.l1.go = "RedChieftain_final_1";
		break;
		
		case "RedChieftain_final_1":
			DialogExit();
			RemovePassenger(Pchar, npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "", -1);
			npchar.lifeday = 0;
			int n = pchar.questTemp.RedChieftain.Tartane;
			for (i=1; i <=n; i++)
			{
				sld = characterFromId("RC_Indian_"+i);
				LAi_ActorRunToLocation(sld, "reload", "reload1_back", "none", "", "", "", -1);
			}
			InterfaceStates.Buttons.Save.enable = true;//разрешить сохраняться
			locations[FindLocation(pchar.questTemp.RedChieftain.Shore)].DisableEncounters = false; //энкаутеры открыть
			AddComplexSelfExpToScill(50, 50, 50, 50);
			AddCharacterExpToSkill(pchar, "Fortune", 50);//везение
			AddQuestRecord("RedChieftain", "8");
			CloseQuestHeader("RedChieftain");
			DeleteAttribute(pchar, "questTemp.RedChieftain");
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
