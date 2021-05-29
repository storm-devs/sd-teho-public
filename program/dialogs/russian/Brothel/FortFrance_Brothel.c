// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    ref sld;   
	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("What kind of questions, "+ GetSexPhrase("young man","young lady") +"?", "What do you want, "+ GetSexPhrase("handsome","pretty one") +"? Ask it."), "Questions again", "Tee-hee, it's all the same for the third time today - questions...",
                          ""+ GetSexPhrase("Hm, why don't you pick up any beauty for yourself? I am starting to get suspicions about you...","Hm, why don't you pick up any beauty for yourself? We don't have boys here, sorry, tee-hee...") +"", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("I've changed my mind...", "Well, nevermind."), "I just... have no questions...",
                      "You're right, it's the third time already. Pardon me.", "Not now... next time...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			//--> Бремя гасконца
			if (CheckAttribute(pchar, "questTemp.Sharlie.Gigolo") && pchar.questTemp.Sharlie.Gigolo == "start")
			{
				link.l1 = "Listen, Aurora, I need a girl for this night. And I want to take her to my home. Can you help me with that?";
                link.l1.go = "Gigolo";
			}	
			//<-- Бремя гасконца
		break;
		
		//--> Бремя гасконца
		case "Gigolo":
			dialog.text = "Sure, dear. What kind of girl do you need? Have you already found the girl for yourself or you don't care?";
			link.l1 = "I do care. I need a girl named Lucille.";
			link.l1.go = "Gigolo_1";
		break;
		
		case "Gigolo_1":
			dialog.text = "Are you talking about Lucille Montaigne?";
			link.l1 = "To be honest, I didn't ask her surname. I only know that she is young and hot blonde named Lucille.";
			link.l1.go = "Gigolo_2";
		break;
		
		case "Gigolo_2":
			dialog.text = "Very well... Tell me, why have you chosen her? Aren't you interested in other girls?";
			link.l1 = "Hm.. She has been working for you for a short time and I think that she is not the best girl in this job and can't cost a lot.";
			link.l1.go = "Gigolo_2_1";
			link.l2 = "I like blondes with fair skin. That is why I have chosen Lucille";
			link.l2.go = "Gigolo_2_2";
		break;
		
		case "Gigolo_2_1":
			if (sti(pchar.questTemp.Sharlie.Gigolo.Rand1) == 0)
			{
				pchar.questTemp.Sharlie.Gigolo.Money = 5000;
				dialog.text = "You are wrong. She is young, pretty, experienced and my clients like her. She will cost you a lot. You have to pay five thousands pesos for a night with her, not a single centime less.";
				if (sti(pchar.money) >= 5000)
				{
					link.l1 = "Hm... Expensive. But I never turn away from my wishes. Here, take your coins.";
					link.l1.go = "Gigolo_3";
				}
				else
				{
					link.l1 = "Heh! I don't have that much money now. Let's get back to this talk later.";
					link.l1.go = "exit";
				}
			}
			else
			{
				pchar.questTemp.Sharlie.Gigolo.Money = 2500;
				dialog.text = "Well, it's true. She has a lack of experience and my clients don't usually notice her, that was the reason why I asked. But if you are really fond of modest girls then I say it's a good choice. You need to pay two thousands and five hundred pesos for a night with her.";
				if (sti(pchar.money) >= 2500)
				{
					link.l1 = "It's no problem. Take the money.";
					link.l1.go = "Gigolo_3";
				}
				else
				{
					link.l1 = "Heh! I don't have that much money now. Let's get back to this talk later.";
					link.l1.go = "exit";
				}
			}
		break;
		
		case "Gigolo_2_2":
			if (sti(pchar.questTemp.Sharlie.Gigolo.Rand2) == 0)
			{
				pchar.questTemp.Sharlie.Gigolo.Money = 4500;
				dialog.text = "Yes, and you are not alone in that, handsome. My clients stand in a queue for her sometimes. She is a very different from the dark-skinned daughters of our islands. You have to pay four thousands and five hundred pesos for a night with Lucille";
				if (sti(pchar.money) >= 4500)
				{
					link.l1 = "Hm... Expensive. But I never turn away from my wishes. Here, take your coins.";
					link.l1.go = "Gigolo_3";
				}
				else
				{
					link.l1 = "Heh! I don't have that much money now. Let's get back to this talk later.";
					link.l1.go = "exit";
				}
			}
			else
			{
				pchar.questTemp.Sharlie.Gigolo.Money = 3000;
				dialog.text = "Really? Feel a nostalgia for Europe perhaps? My creoles, and especially mulattos are more passionate than this daughter of Paris ghettos. But I would be glad if you really like her. It will cost you three thousands pesos.";
				if (sti(pchar.money) >= 3000)
				{
					link.l1 = "It's no problem. Take the money.";
					link.l1.go = "Gigolo_3";
				}
				else
				{
					link.l1 = "Heh! I don't have that much money now. Let's get back to this talk later.";
					link.l1.go = "exit";
				}
			}
		break;
		
		case "Gigolo_3":
			AddMoneyToCharacter(pchar, -sti(pchar.questTemp.Sharlie.Gigolo.Money));
			dialog.text = "Very well, dear. The girl is going to free herself at eleven o'clock in the evening. She will be waiting for you. Remember, she must return not later than seven o'clock in the morning. If you don't take Lucille before midnight, another client will, and then you will have to wait for the next evening to take her\nAnd don't even try to... hurt her or I guarantee problems for you. Don't think of it as a threat, I am only warning you.";
			link.l1 = "Don't worry. I am going to take this girl for love, not for anything else. I'll take her at eleven o'clock. Farewell!";
			link.l1.go = "Gigolo_4";
		break;
		
		case "Gigolo_4":
			DeleteAttribute(pchar, "GenQuest.CannotWait");
			DialogExit();
			AddQuestRecord("SharlieC", "2");
			pchar.questTemp.Sharlie.Gigolo = "girl";
			Sharlie_CreateGigoloGirl();
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

