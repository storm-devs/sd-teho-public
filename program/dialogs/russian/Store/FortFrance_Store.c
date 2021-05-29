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
			//--> Бремя гасконца
			if (!CheckAttribute(npchar, "quest.storehelper") && pchar.questTemp.Sharlie == "ship")
			{
				Link.l1 = "Listen, monsieur, I'm looking for a job. Not like a full-time job or labor hauling bags of cargo, but more like running errands, so to speak. Do you happen to need an assistance?";
				Link.l1.go = "Sharlie_storehelper";
			}
			if (CheckAttribute(pchar, "questTemp.Sharlie.Storehelper") && pchar.questTemp.Sharlie.Storehelper == "return")
			{
				Link.l1 = "I've completed you errand. I was able to find Gralam Lavoie.";
				Link.l1.go = "Sharlie_storehelper_2";
			}
			if (CheckAttribute(pchar, "questTemp.Sharlie.Storehelper") && pchar.questTemp.Sharlie.Storehelper == "choise")
			{
				Link.l1 = "Meet your new assistant, monsieur.";
				Link.l1.go = "Sharlie_storehelper_11";
			}
			if (CheckAttribute(pchar, "questTemp.Sharlie.Storehelper") && pchar.questTemp.Sharlie.Storehelper == "final")
			{
				Link.l1 = "It's me again, monsieur. I've come for my reward.";
				Link.l1.go = "Sharlie_storehelper_13";
			}
			if (CheckAttribute(pchar, "questTemp.Sharlie.Junglejew") && !CheckAttribute(npchar, "quest.junglejew"))
			{
				link.l1 = "Take a look at these earrings, monsieur. I've found them on the body of a bandit that was killed in the jungle. This is clearly the work of a fine jeweler which, I'm sure, is not from this wilderness. Is there anything you can say about these earrings?";
                link.l1.go = "Sharlie_junglejew";
			}
			//<-- Бремя гасконца
		break;
		
		//--> Бремя гасконца
		case "Sharlie_storehelper":
			dialog.text = "A job? Hm. I suppose, I've got a job you might want. My assistant is missing, he used to work in my warehouse. He has been missing for a week already and this is bloody irritating, because I am forced to do his duties and I don't have time\nPlease, find this idiot and find out why the hell did he abandon his workplace. Or even better - bring him to me. I'll pay you a thousand pesos.";
			link.l1 = "Fine, I am in. Tell me his name and describe his looks. Do you have any ideas where to look for him?";
			link.l1.go = "Sharlie_storehelper_1";
			link.l2 = "Search for a man God knows where for a lousy thousand? You've got to be joking!";
			link.l2.go = "Sharlie_storehelper_exit";
			npchar.quest.storehelper = "true";
		break;
		
		case "Sharlie_storehelper_exit":
			dialog.text = "Hey, monsieur. Who's looking for a job, you or me? If you don't want to, I'm not forcing you. Have a nice day.";
			link.l1 = "Hm...";
			link.l1.go = "exit";
		break;
		
		case "Sharlie_storehelper_1":
			dialog.text = "Name's Gralam Lavois. His looks? Thirty five years old, beard and moustache, long brown coat, white shirt. Oh, and he always wears that fucking cocked hat, pretends to be an admiral, anchor up his arse\nHe is not in St. Pierre, I have checked the whole town. He must be in the jungles or in Les Francois.";
			link.l1 = "Okay. I'll get to searching. As soon as something comes up, I'll inform you right away.";
			link.l1.go = "exit";
			AddQuestRecord("SharlieA", "1");
			pchar.questTemp.Sharlie.Storehelper = "true";
			pchar.questTemp.Sharlie.Storehelper.Chance = rand(2);
			AddDialogExitQuestFunction("Sharlie_CreateStorehelper");
		break;
		
		case "Sharlie_storehelper_2":
			dialog.text = "Oh yeah? And where is he?";
			link.l1 = "I've found him in Le Francois. He isn't going to work for you anymore according to his own words. He also added a lot of things about you... Would you be interested in hearing it?";
			link.l1.go = "Sharlie_storehelper_3";
		break;
		
		case "Sharlie_storehelper_3":
			dialog.text = "No. Spare me of the details... What a pity! What am I going to do now without an assistant?";
			link.l1 = "Hire someone else. Or is it really as big of a problem as Gralam said it was?";
			link.l1.go = "Sharlie_storehelper_4";
		break;
		
		case "Sharlie_storehelper_4":
			dialog.text = "Rotten luck, indeed. And what did that loafer say?";
			link.l1 = "Well, for starters he's obviously not idling his time, he-he. He said that no one in all Saint Pierre would sign up for service for you because... you don't pay your workers enough. Yes, by the way, "+npchar.name+", you owe one thousand pesos as promised.";
			link.l1.go = "Sharlie_storehelper_5";
		break;
		
		case "Sharlie_storehelper_5":
			AddMoneyToCharacter(pchar, 1000);
			dialog.text = "Please, take your money. Ha! Don't pay enough! Of course, nobody wants to work for me. The bastard did his best to spread dirty talks. What can I do? I can't do everything alone!\nI can't go to sleep until I count every piece of cargo because those damn workers always steal some. After the last loading I'm short of five barrels of rum. I'm sure that the workers 'mistakenly' grabbed them...";
			link.l1 = "Well, I don't know what to advice. All right, all the best. It's time for me to go.";
			link.l1.go = "Sharlie_storehelper_6";
		break;
		
		case "Sharlie_storehelper_6":
			dialog.text = "Wait! I think you can help me. If you were able to search out that son of a gun, then you might well be able to...";
			link.l1 = "And what would I be able to do I wonder, if nobody in this town believes you? I'm a new guy here and...";
			link.l1.go = "Sharlie_storehelper_7";
		break;
		
		case "Sharlie_storehelper_7":
			dialog.text = "Let me finish, monseniour. You have been in Le Francois. I would like you to go there again and try to find an employee for me. Perhaps, Gralam didn't completely ruin my name in this pirate den\nThe job is easy - to count cargo and to watch over port workers to prevent stealing. Sometimes to do my job here instead of me while I am gone, for extra fee of course\nTell them that I offer a room in the store to live and five hundred pesos per week. Monseniour, I am going to expand business and things are finally going well, I need an assistant, see?";
			link.l1 = "Hm. I can try, although I'm not sure... How much will you pay me for the job?";
			link.l1.go = "Sharlie_storehelper_8";
		break;
		
		case "Sharlie_storehelper_8":
			dialog.text = "That will depend on what worker you'll be able to hire. The more adroit he turns out to be the more I'll pay you for your efforts. That's fair, isn't it?";
			link.l1 = "Don't you think you're forcing me to ride blind? How do I know how you're going to evaluate a worker? You could categorize anyone as bad or...";
			link.l1.go = "Sharlie_storehelper_9";
		break;
		
		case "Sharlie_storehelper_9":
			dialog.text = "Monsieur! It may very well be correct to call me a little stingy, but no one could call me dishonest! If I tell you I'll pay for your efforts depending on how it turns out, then I mean it. See it from my point of view as well. You just might bring me here some lazy ass that would not only walk around and do nothing, but even possibly rob me at night!";
			link.l1 = "All right. I agree. I'll take your word, "+npchar.name+". Let's not waste time any further. It is, as you know, money.";
			link.l1.go = "Sharlie_storehelper_10";
		break;
		
		case "Sharlie_storehelper_10":
			DialogExit();
			AddQuestRecord("SharlieA", "3");
			pchar.quest.storehelper.win_condition.l1 = "Timer";
			pchar.quest.storehelper.win_condition.l1.date.hour  = sti(GetTime());
			pchar.quest.storehelper.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 5);
			pchar.quest.storehelper.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 5);
			pchar.quest.storehelper.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 5);
			pchar.quest.storehelper.function = "StorehelperOver";
			pchar.questTemp.Sharlie.Storehelper = "hire";
			AddCharacterExpToSkill(pchar, "Leadership", 50);
			AddCharacterExpToSkill(pchar, "Fortune", 50);
		break;
		
		case "Sharlie_storehelper_11":
			dialog.text = "Have you found a worker for me? Wonderful. Allow me to have a talk with him, come back in an hour for your reward.";
			link.l1 = "All right. I'll come back in an hour.";
			link.l1.go = "Sharlie_storehelper_12";
		break;
		
		case "Sharlie_storehelper_12":
			chrDisableReloadToLocation = false;//открыть локацию
			pchar.questTemp.Sharlie.Storehelper = "wait";
			DialogExit();
			pchar.quest.storehelper5.win_condition.l1 = "Timer";
			pchar.quest.storehelper5.win_condition.l1.date.hour  = sti(GetTime()+1);
			pchar.quest.storehelper5.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 0);
			pchar.quest.storehelper5.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 0);
			pchar.quest.storehelper5.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 0);
			pchar.quest.storehelper5.function = "StorehelperFinal";
			AddQuestRecord("SharlieA", "5");
		break;
		
		case "Sharlie_storehelper_13":
			switch (sti(pchar.questTemp.Sharlie.Storehelper.Quality))
			{
				case 0:
					AddMoneyToCharacter(pchar, 3000);
					dialog.text = "I am quite happy with the worker you've found for me, although he talks the talk more than he walks the walk, but don't worry, I'll beat his chattering out of him in some time. Your reward is three thousand pesos. Here you go.";
					link.l1 = "Thank you! All the best, monsieur.";
					link.l1.go = "Sharlie_storehelper_14";
				break;
				
				case 1:
					AddMoneyToCharacter(pchar, 5000);
					dialog.text = "You've managed to find a truly valuable worker! He's even better that that scoundrel Gralam. I'm very, very pleased, sir. Here, take your reward - five thousand pesos.";
					link.l1 = "Thank you! All the best, monsieur.";
					link.l1.go = "Sharlie_storehelper_14";
				break;
				
				case 2:
					AddMoneyToCharacter(pchar, 4000);
					dialog.text = "You've found a good worker. And although he doesn't know all the tricks of the trade, I'm sure he get a handle on it without much trouble. I'm pleased with you, sir. Here, take your reward - four thousand pesos.";
					link.l1 = "Thank you! All the best, monsieur.";
					link.l1.go = "Sharlie_storehelper_14";
				break;
			}
		break;
		
		case "Sharlie_storehelper_14":
			DialogExit();
			DeleteAttribute(pchar, "questTemp.Sharlie.Storehelper");
			CloseQuestHeader("SharlieA");
		break;
		
		case "Sharlie_junglejew":
			dialog.text = "Well, what am I supposed to say, magnificent earrings. I can give you... let's see... four thousand pesos for them. I doubt anyone will offer you more. Do we have a deal?";
			link.l1 = "Deal! They are yours.";
			link.l1.go = "Sharlie_junglejew_1";
			link.l2 = "No. I think I'll leave these jewels to myself.";
			link.l2.go = "exit";
			npchar.quest.junglejew = "true";
		break;
		
		case "Sharlie_junglejew_1":
			DialogExit();
			PlaySound("interface\important_item.wav");
			Log_Info("You've given the earrings");
			RemoveItems(pchar, "jewelry25", 1);
			AddMoneyToCharacter(pchar, 4000);
			AddQuestRecord("SharlieE", "4");
			CloseQuestHeader("SharlieE");
			DeleteAttribute(pchar, "questTemp.Sharlie.Junglejew");
		break;
		//<-- Бремя гасконца
	}
	UnloadSegment(NPChar.FileDialog2);
}

