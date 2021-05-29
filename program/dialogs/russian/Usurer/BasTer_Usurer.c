// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("What questions do you have?", "How can I help you?"), "You tried to ask me that question not long ago...", "Yup, let me guess... Once again going around in circles?",
                          "Listen, I do the finances here, I don't answer questions...", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("I've changed my mind...", "I've got nothing to talk about at the moment."), "Umph, where has my memory gone...",
                      "You've guessed it, I'm sorry...", "I understand...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			// Addon-2016 Jason ФМК-Гваделупа
			if (CheckAttribute(pchar, "questTemp.FMQG") && pchar.questTemp.FMQG == "continue")
            {
                link.l1 = "I am captain "+GetFullName(pchar)+". Your man told me that you wanted to see me. I am all ears.";
                link.l1.go = "FMQG";
            }
			if (CheckAttribute(pchar, "questTemp.FMQG") && pchar.questTemp.FMQG == "sucsess")
            {
                link.l1 = "Me again, monseniour "+GetFullName(pchar)+". I brought you Bertrand Pinette. He is in my cargo hold.";
                link.l1.go = "FMQG_14";
            }
			if (CheckAttribute(pchar, "questTemp.FMQG") && pchar.questTemp.FMQG == "letter")
            {
                link.l1 = "Me again, monseniour "+GetFullName(pchar)+". Let's have a talk.";
                link.l1.go = "FMQG_17";
            }
			if (CheckAttribute(pchar, "questTemp.FMQG") && pchar.questTemp.FMQG == "killers")
            {
                link.l1 = "Me again, monseniour "+GetFullName(pchar)+". Let's have a talk.";
                link.l1.go = "FMQG_17";
            }
			if (CheckAttribute(pchar, "questTemp.FMQG.Letter"))
            {
                link.l1 = "Me again, monseniour "+GetFullName(pchar)+". I assume you didn't expect to see me again.";
                link.l1.go = "FMQG_23";
            }
		break;
		
		// Addon-2016 Jason ФМК-Гваделупа
		case "FMQG":
			dialog.text = "A-ah, captain "+GetFullName(pchar)+"! I am so glad to see you! I've been waiting for you for quite a while... Good. I have a question to ask. Some time ago, a man named Bertrand Pinette approached you in the port in order to get onboard of your ship. Wealthy looking fellow in a luxury wig. Does it ring a bell?";
			link.l1 = "Yes, it does. He really approached me with this exact purpose.";
			link.l1.go = "FMQG_1";
		break;
		
		case "FMQG_1":
			Log_Info("You have received a heavy purse");
			PlaySound("interface\important_item.wav");
			GiveItem2Character(pchar, "purse3");
			dialog.text = "Did he want to hire you and your ship? Captain, you'd do me a great favor by telling me all details of this case. I'll make it worth you while. Here, take this purse filled with coins. It's yours, now please tell me about Bertrand Pinette.";
			link.l1 = "Very well. Monsieur Pinette hired my ship to deliver him and two of his friends from Guadeloupe to the Spanish Maine. More specifically, Mosquitoes Bay of Portobello. I did the job, they left my ship and walked to the jungle.";
			link.l1.go = "FMQG_2";
		break;
		
		case "FMQG_2":
			dialog.text = "I see. And did monsieur Pinette mention his final destination? And what about his companions?";
			link.l1 = "According to his own words, they were heading to Panama. His friends were quite intriguing: two officers, a Spanish and a French. Still can't realize what united them but I wasn't paid to ask questions.";
			link.l1.go = "FMQG_3";
		break;
		
		case "FMQG_3":
			dialog.text = "A Spanish officer? And a French officer? Oh! Isn't that something! Nice one, monsieur Pinette! What a sly dog! Even here found the way to earn money! Panama, you said?";
			link.l1 = "Yeah, and I told you everything I knew. May I take my leave?";
			link.l1.go = "FMQG_4";
		break;
		
		case "FMQG_4":
			dialog.text = "Wait, captain. I have a business proposal for you. Don't you mind of earning some coins? But, first, let me tell you something about your passengers.";
			link.l1 = "Well, let's hear it.";
			link.l1.go = "FMQG_5";
		break;
		
		case "FMQG_5":
			dialog.text = "Monsieur Bertrand Pinette showed up in our colony two years ago and immediately started doing business with captains. Business, yeah, and dark one too... They were delivering him goods of great shortage in this place, valuables, smuggling, even slaves sometimes... He was systematically taking up loans for his illegal operations in my office, but always paid back with all the interest\nBefore leaving the island with your good help, he had taken up a big loan, much bigger than usual. He is... was a trusted client with an impeccable credit history, that's why I had provided him with a loan. Big mistake. Monsieur Pinette has run away and obviously he is not going to pay my coins back.";
			link.l1 = "How big is the sum, if I may ask?";
			link.l1.go = "FMQG_6";
		break;
		
		case "FMQG_6":
			dialog.text = "It's big. Around one hundred and fifty thousand pesos in doubloons. Ten chests, each with one hundred fifty doubloons. And not to mention all the interest.";
			link.l1 = "Hm... He'd been paying you for two years, made you get used to it, took up a substantial loan and then went rogue. Smart.";
			link.l1.go = "FMQG_7";
		break;
		
		case "FMQG_7":
			dialog.text = "Precisely, captain. That is why I'd like to hire you for a job: find the scum and bring him here. Me, the governor and the commandant will find a way to make him wipe away his debt. You've seen that man, he was your passenger, that means you have better chances to find monsieur Pinette than anyone else. Sure, I'll also hire a professional bounty hunter for his sorry ass, but I have a feeling that your help will turn more effective.";
			link.l1 = "What about a reward?";
			link.l1.go = "FMQG_8";
		break;
		
		case "FMQG_8":
			dialog.text = "For doing the job, I'll give you a chest full of doubloons, one hundred and fifty coins.";
			link.l1 = "I say this would be quite a pathetic reward for tracking down and kidnapping a living soul in the Spanish town.";
			link.l1.go = "FMQG_9";
		break;
		
		case "FMQG_9":
			dialog.text = "Captain, I assume that monsieur Pinette had paid you well with my money since you evaluate my proposal so cheap. I assure you that it's worth the effort. Of course, you have every right to refuse... but I have something to tell you and it will surely make you change your mind.";
			link.l1 = "And what is it?";
			link.l1.go = "FMQG_10";
		break;
		
		case "FMQG_10":
			dialog.text = "A few days before Pinette's escape from Guadeloupe, one prisoner had run away from the prison of Basse-Terre. His name is don Carlos de Milyar, a Spanish grandee and an officer. He made it thanks to a treason of a French officer, a lieutenant of the Marines... Do you understand what I mean?";
			link.l1 = "Hm... And how that concerns me? I was doing a transportation of passengers, nothing more.";
			link.l1.go = "FMQG_11";
		break;
		
		case "FMQG_11":
			dialog.text = "Sure, you were! Personally, I have no doubt that you have nothing to do with organizing the escape of don de Milyar. But that is not how our governor along with our commandant might think of it. A charge of complicity if you are lucky and if you are not... I don't want to continue really. See by yourself, you took a runaway Spanish officer onboard, most likely at some hidden cove... am I right, captain?";
			link.l1 = "I get it. You are blackmailing me. I made a mistake coming here...";
			link.l1.go = "FMQG_12";
		break;
		
		case "FMQG_12":
			dialog.text = "What do you say, captain?! I am not blackmailing you! All I ask is to help me out for a good reward. Would you be kind to find monsieur Pinette and to deliver him to Basse-Terre? I will be waiting for your return. I believe that two months is enough to sail to Panama and back.";
			link.l1 = "You leave me no choice. Though I doubt that such business approach will do any good in making us friends. Farewell, monsieur.";
			link.l1.go = "FMQG_13";
		break;
		
		case "FMQG_13":
			DialogExit();
			LocatorReloadEnterDisable("Baster_town", "reload1_back", false);
			LocatorReloadEnterDisable("Baster_town", "reload2_back", false);
			LocatorReloadEnterDisable("Baster_town", "gate_back", false);//открыть выходы из города
			pchar.questTemp.FMQG = "headhunter_panama";
			ReOpenQuestHeader("FMQ_Guadeloupe");
			AddQuestRecord("FMQ_Guadeloupe", "7");
			SetFunctionTimerCondition("FMQG_UsurerTimeOut", 0, 0, 61, false);
		break;
		
		case "FMQG_14":
			dialog.text = "Excellent news, captain! I will send my men to pick up this bastard from your ship at once. This birdie isn't going to fly away from me this time... You deserved your reward, take this chest. Please, don't feel angry about me, here is an amulet for you. It's a gift.";
			link.l1 = "Gratitude. I assume that your silence is also a part of my reward?";
			link.l1.go = "FMQG_15";
		break;
		
		case "FMQG_15":
			Log_Info("You have received a chest full of doubloons");
			Log_Info("You have received a 'Fisherman' amulet");
			PlaySound("interface\important_item.wav");
			GiveItem2Character(pchar, "chest");
			GiveItem2Character(pchar, "obereg_7");
			dialog.text = "Silence? About what? I'd be glad to see you among my clients. You know what they say about silence and gold?";
			link.l1 = "It worth much more than gold sometimes, monsieur. Lesson learnt. Farewell!";
			link.l1.go = "FMQG_16";
		break;
		
		case "FMQG_16":
			DialogExit();
			pchar.quest.FMQG_UsurerTimeOut.over = "yes";
			ref sld = characterFromId("FMQG_pass_1");
			RemovePassenger(pchar, sld);
			sld.lifeday = 0;
			pchar.questTemp.FMQG = "end";
			FMQ_Count();
			AddQuestRecord("FMQ_Guadeloupe", "23");
			CloseQuestHeader("FMQ_Guadeloupe");
			ChangeCharacterNationReputation(pchar, FRANCE, 5);
			ChangeCharacterComplexReputation(pchar, "nobility", 5);
			ChangeCharacterComplexReputation(pchar, "authority", 3);
			AddCharacterExpToSkill(pchar, "Leadership", 400);
			AddCharacterExpToSkill(pchar, "Sailing", 200);
		break;
		
		case "FMQG_17":
			dialog.text = "I am listening. Bertrand Pinette is on your ship, I assume?";
			link.l1 = "No. Though I have something much better for you. Read this.";
			link.l1.go = "FMQG_18";
		break;
		
		case "FMQG_18":
			RemoveItems(pchar, "letter_baker", 1);
			dialog.text = "What is this?";
			link.l1 = "Keep reading, monsieur. We will continue later.";
			link.l1.go = "FMQG_19";
		break;
		
		case "FMQG_19":
			LAi_Fade("", "");
			dialog.text = "(reading) Ahem ... What is this nonsense of a febrile patient?";
			link.l1 = "Are you serious? Fine, I'll take this 'nonsense' to the governor. I believe that he will show a great interest in learning the truth about the disappearance of the 'Courage' and her consignment of diamonds. Why have you become so pale?";
			if (CheckAttribute(pchar, "questTemp.FMQG.Letter")) link.l1.go = "FMQG_24";
			else link.l1.go = "FMQG_20";
		break;
		
		case "FMQG_20":
			dialog.text = "So, you found Pinette after all...";
			link.l1 = "Yes. So I propose a deal to you. Forget about Carlos de Milyar, Jean Deno and other good gentlemen, do that and I will forget about this letter.";
			link.l1.go = "FMQG_21";
		break;
		
		case "FMQG_21":
			dialog.text = "Very well, captain... I agree to your terms.";
			link.l1 = "Lovely. I hope you are not angry with me, we are done now, I think. Farewell.";
			link.l1.go = "FMQG_22";
		break;
		
		case "FMQG_22":
			DialogExit();
			pchar.quest.FMQG_UsurerTimeOut.over = "yes";
			pchar.questTemp.FMQG = "cave";
			bQuestDisableMapEnter = true;//закрыть карту
			pchar.GenQuest.MapClosedNoBattle = true;
			pchar.quest.FMQG_cave.win_condition.l1 = "location";
			pchar.quest.FMQG_cave.win_condition.l1.location = "Guadeloupe_Cave";
			pchar.quest.FMQG_cave.function = "FMQG_InCave";
			// заполним сундук
			pchar.GenQuestBox.Guadeloupe_Cave = true;
			pchar.GenQuestBox.Guadeloupe_Cave.box3.items.purse1 = 5;
			pchar.GenQuestBox.Guadeloupe_Cave.box3.items.purse2 = 2;
			pchar.GenQuestBox.Guadeloupe_Cave.box3.items.purse3 = 1;
			SetFunctionTimerCondition("FMQG_ClearBox", 0, 0, 3, false);
			if (CheckAttribute(pchar, "questTemp.FMQG.Letter"))
			{
				SetFunctionTimerCondition("FMQG_RemoveHunterScore", 0, 0, 1, false);
				AddQuestRecord("FMQ_Guadeloupe", "29");
				DeleteAttribute(pchar, "questTemp.FMQG.Letter");
			}
			else AddQuestRecord("FMQ_Guadeloupe", "25");
		break;
		
		case "FMQG_23":
			dialog.text = "Ha... You are right, captain.";
			link.l1 = "I have something for you. Take this and read.";
			link.l1.go = "FMQG_18";
		break;
		
		case "FMQG_24":
			dialog.text = "So, you found Pinette after all...";
			link.l1 = "Yes. So I propose a deal to you. Restore my good name within French colonies and I will forget about this letter.";
			link.l1.go = "FMQG_25";
		break;
		
		case "FMQG_25":
			dialog.text = "But...";
			link.l1 = "I don't give a shit about how you will do it. If the hunt after my head don't end tomorrow, the governor will learn about everything.";
			link.l1.go = "FMQG_21";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

