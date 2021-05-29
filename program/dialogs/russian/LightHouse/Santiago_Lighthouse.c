// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("What do you want?", "What would you like to know?"), "Tell me, what are you interested in, " + GetAddress_Form(NPChar) + "?", "It's the third time you try to ask...", "I had enough of you. Get out!", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("I have changed my mind...", "I have got nothing to say now."), "It seems I've forgotten, sorry...",
                      "You're right, it's the third time already. Pardon me.", "I am sorry...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "mayak")
			{
				link.l1 = "The inquisitor of Santiago, padre Vincento has mentioned you in his letter. Do you know that?";
                link.l1.go = "guardoftruth";
			}
			if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "mayak_next")
			{
				link.l1 = "Any news from padre Vincento, "+npchar.name+"?";
                link.l1.go = "guardoftruth_5";
			}
			if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "utensil" && CheckCharacterItem(pchar, "jewelry33") && CheckCharacterItem(pchar, "jewelry34") && CheckCharacterItem(pchar, "jewelry35"))
			{
				link.l1 = "I need to see padre Vincento. I have found the items which he is interested in.";
                link.l1.go = "guardoftruth_7";
			}
			if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "inquisition")
			{
				link.l1 = "So, "+npchar.name+", what has padre Vincento told you?";
                link.l1.go = "guardoftruth_11";
			}
		break;
		
		case "guardoftruth":
			dialog.text = "Sure, senor. You must be a man of a high fly if padre Vincento himself does business with you...";
			link.l1 = "Splendid. You are our runner then. Now listen, this man is the one who need padre Vincento. He is under your responsibility now, you have to transfer him to Santiago or find anyone to do the same...";
			link.l1.go = "guardoftruth_1";
		break;
		
		case "guardoftruth_1":
			dialog.text = "";
			link.l1 = "You are responsible to the Inquisitor himself for the prisoner. Also, I don't advise you to remove the shackles from him, Gaius Marchais is a strong guy. Give this letter to padre Vincento and tell him that I wait for an answer from him in two days. This should be enough, I suppose...";
			link.l1.go = "guardoftruth_2";
		break;
		
		case "guardoftruth_2":
			Log_Info("You have given the letter");
			PlaySound("interface\important_item.wav");
			dialog.text = "I've understood you, senor. I'll do it in the best way I could. It's not the first time I'm helping holy father.";
			link.l1 = "That's not all. The captain of carraca 'San Gregorio' Carlos Guevarra must have been here. He brought vanilla for me. Has he given you my letter?";
			link.l1.go = "guardoftruth_3";
		break;
		
		case "guardoftruth_3":
			dialog.text = "Your cargo is fine, senor, waiting for you.";
			link.l1 = "Good, I'll order to put it in my ship. I'll be here in two days for the padre Vincento's answer. I am not saying goodbye, "+npchar.name+"!..";
			link.l1.go = "guardoftruth_4";
		break;
		
		case "guardoftruth_4":
			DialogExit();
			LocatorReloadEnterDisable("mayak9", "boat", false);
			ref sld = characterFromId("GOT_Marshe");
			LAi_SetStayType(sld);
			LAi_CharacterDisableDialog(sld);
			sld.lifeday = 0;
			pchar.questTemp.Guardoftruth = "mayak_wait";
			SetFunctionTimerCondition("GuardOT_MayakNextStage", 0, 0, 2, false);
			SetCharacterGoods(pchar, GOOD_CINNAMON, GetCargoGoods(pchar, GOOD_CINNAMON) + sti(pchar.questTemp.Guardoftruth.VanilleQty));
			AddQuestRecord("Guardoftruth", "21");
		break;
		
		case "guardoftruth_5":
			dialog.text = "Yes, senor. Here is the letter from padre Vincento. He is very pleased by you. He said that you'd know the rest from the letter.";
			link.l1 = "Splendid. See you soon, "+npchar.name+". And for now - farewell...";
			link.l1.go = "guardoftruth_6";
		break;
		
		case "guardoftruth_6":
			DialogExit();
			pchar.questTemp.Guardoftruth = "mayak_exit";
			GiveItem2Character(pchar, "specialletter");
			sld = ItemsFromID("specialletter");
			sld.text = "Letter_Vincento_next";
		break;
		
		case "guardoftruth_7":
			dialog.text = "Fine. Give them to me and I will take them to holy father.";
			link.l1 = "No way, buddy! It wasn't easy to get those items and I don't want to loose them just like that. I will give them only to padre Vincento personally.";
			link.l1.go = "guardoftruth_8";
		break;
		
		case "guardoftruth_8":
			dialog.text = "But senor! How can I know that you are not cheating on me?";
			link.l1 = "Take a look: the censer, the chalice and the cross with a lazurite... "+npchar.name+", who do you think I am? Do you really think I am that stupid to go to the Inquisition without those items?";
			link.l1.go = "guardoftruth_9";
		break;
		
		case "guardoftruth_9":
			dialog.text = "Forgive me, senor... Come tomorrow and I'll tell padre Vincento about your arrival.";
			link.l1 = "Fine. See you tomorrow.";
			link.l1.go = "guardoftruth_10";
		break;
		
		case "guardoftruth_10":
			DialogExit();
			pchar.questTemp.Guardoftruth = "mayak_wait";
			SetFunctionTimerCondition("GuardOT_MayakLastStage", 0, 0, 1, false);
		break;
		
		case "guardoftruth_11":
			dialog.text = "His Grace will receive you, senor. Don't delay your visit. Here is the document, show it to the guards and they will let you in. But raise a Spanish flag at first or soldiers will have to arrest you.";
			link.l1 = "Got it. Spanish then. Thanks, pal! I am on my way!";
			link.l1.go = "guardoftruth_12";
		break;
		
		case "guardoftruth_12":
			DialogExit();
			GiveItem2Character(pchar, "VerifyPaper");
			ChangeItemDescribe("VerifyPaper", "itmdescr_VincentoPaper");
			pchar.questTemp.Guardoftruth = "santiago";
			AddQuestRecord("Guardoftruth", "34");
			AddCharacterExpToSkill(pchar, "Fortune", 200);//везение
			AddCharacterExpToSkill(pchar, "Sneak", 400);//скрытность
			GuardOT_SetPadreVincento();
		break;
	}
	UnloadSegment(NPChar.FileDialog2); 
}