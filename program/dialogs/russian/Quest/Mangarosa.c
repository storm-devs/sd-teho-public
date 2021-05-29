// диалоги персонажей по квесту Мангароса
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	string sTemp;
	
	DeleteAttribute(&Dialog,"Links");
	
	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	switch(Dialog.CurrentNode)
	{
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
        case "First time":
			dialog.text = "What do you want?";
			link.l1 = "Nothing.";
			link.l1.go = "exit";
		break;
		
		// Амелия - знахарка-цыганка
		case "amelia":
			dialog.text = "What do you want in my house?";
			if (CheckAttribute(pchar, "questTemp.Mangarosa") && pchar.questTemp.Mangarosa == "amelia")
			{
				link.l1 = "Your name is Amelia, right? I came to ask you about one plant. Manga Rosa.";
				link.l1.go = "amelia_1";
			}
			else
			{
				link.l1 = "I have nothing to tell you yet. But I will be back one day...";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "amelia";
		break;
		
		case "amelia_1":
			dialog.text = "Interesting! And who has told you about me, brave young man?";
			link.l1 = "One of your people. She said that you know the secrets of this plant and you can teach me how to make special potions of it...";
			link.l1.go = "amelia_2";
		break;
		
		case "amelia_2":
			dialog.text = "First, show me the plant you are talking about. Perhaps you don't know a thing about it and you're just wasting my time. Where is your Manga Rosa?";
			if (CheckCharacterItem(pchar, "cannabis7"))
			{
				link.l1 = "Here, take a look.";
				link.l1.go = "amelia_3";
			}
			else
			{
				link.l1 = "Hm...";
				link.l1.go = "amelia_exit";
			}
		break;
		
		case "amelia_exit":
			dialog.text = "And what were you going to show me? You don't have Manga Rosa. So get out, pal, until I get angry. The talk is over.";
			link.l1 = "But...";
			link.l1.go = "exit";
			NextDiag.TempNode = "amelia_wait";
		break;
		
		case "amelia_wait":
			dialog.text = "You again? Don't lead to trouble, boy...";
			if (CheckCharacterItem(pchar, "cannabis7"))
			{
				link.l1 = "Calm down, Amelia. I have dropped it somewhere last time. Here, I have brought you Manga Rosa. Take a look.";
				link.l1.go = "amelia_3";
			}
			else
			{
				link.l1 = "...";
				link.l1.go = "amelia_exit";
			}
			NextDiag.TempNode = "amelia_wait";
		break;
		
		case "amelia_3":
			dialog.text = "Let's see... It seems that you know something about it. And do you want me to tell you the secrets of my potions?";
			link.l1 = "Exactly. And not for free, as I understand...";
			link.l1.go = "amelia_4";
		break;
		
		case "amelia_4":
			dialog.text = "You understand it right, young man! You don't look like a complete idiot. Well, I can teach a man who seeks knowledge and who doesn't waste this rare plant on a useless smoking stuff...";
			link.l1 = "Amelia, before we start bargaining... would you be kindly to tell me some basic knowledge about potions I can make of Manga Rosa?";
			link.l1.go = "amelia_5";
		break;
		
		case "amelia_5":
			dialog.text = "No bargaining, pal. I will tell you the price and it would be your decision to pay it or not. Don't count on any bargain or discount, it is not a market. And concerning your question... You can make special potions of Manga Rosa which will fortify your physical abilities. They can make you stronger, more endurable, faster or do a complex influence to your body.";
			link.l1 = "Very interesting. Name your price.";
			link.l1.go = "amelia_6";
		break;
		
		case "amelia_6":
			dialog.text = "I can teach you three recipes. For every recipe I ask for one plant and three hundred golden coins.";
			link.l1 = "Tell me more about these potions. What each of them does?";
			link.l1.go = "amelia_7";
		break;
		
		case "amelia_7":
			dialog.text = "You must be a master of the art of alchemy if you want to make any potion. Every potion acts for two days or less, depends when you drink it\nFirst potion adds you strength and endurance. You will fight better, take less damage and carry more weight\nSecond potion will make you swifter, agile, tireless and it will also improve your aim\nThird potion has a twice weaker effects of both previous potions. But it also adds you charm, self-confidence and luck too\nAll Manga Rosa-based potions have a positive effect on your health. You must drink only one potion at time, never mix them, otherwise they will do you no good, on the contrary you will get a strong poisoning\nSo, handsome, are you ready to pay for the knowledge right now or you need time to think?";
			if (CheckCharacterItem(pchar, "cannabis7") && GetCharacterItem(pchar, "gold_dublon") >= 300)
			{
				link.l1 = "Yes, I am ready.";
				link.l1.go = "amelia_8";
			}
			link.l2 = "I need to think a bit. This is a big decision to make.";
			link.l2.go = "exit";
			NextDiag.TempNode = "amelia_next";
		break;
		
		case "amelia_next":
			if (CheckAttribute(npchar, "quest.recipe_all"))
			{
				dialog.text = "Ah, it's you, young man! So, do my potions help you?";
				link.l1 = "They really do, Amelia. Thank you!";
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = "Ah, it's you, young man! Want to buy some recipes?";
				if (CheckCharacterItem(pchar, "cannabis7") && GetCharacterItem(pchar, "gold_dublon") >= 300)
				{
					link.l1 = "Exactly. This is why I am here.";
					link.l1.go = "amelia_8";
				}
				link.l2 = "Not yet, Amelia. Just paying you a visit.";
				link.l2.go = "exit";
			}
			NextDiag.TempNode = "amelia_next";
		break;
		
		case "amelia_8":
			dialog.text = "Very well. What kind of recipe do you want to buy?";
			if (!CheckAttribute(npchar, "quest.recipe_power"))
			{
				link.l1 = "The recipe for potion of strength and endurance.";
				link.l1.go = "power";
			}
			if (!CheckAttribute(npchar, "quest.recipe_fast"))
			{
				link.l2 = "The recipe for potion of agility and tirelessness.";
				link.l2.go = "fast";
			}
			if (!CheckAttribute(npchar, "quest.recipe_total"))
			{
				link.l3 = "The recipe for a complex potion.";
				link.l3.go = "total";
			}
		break;
		
		case "power":
			dialog.text = "Fine. I have called it the 'Tidal Wave'. Here, take an instruction. Read it carefully. And don't forget how to use it correctly!";
			link.l1 = "Thanks, Amelia...";
			link.l1.go = "recipe_exit";
			AddQuestRecordInfo("Recipe", "mangarosapower");
			SetAlchemyRecipeKnown("mangarosapower");
			npchar.quest.recipe_power = true;
		break;
		
		case "fast":
			dialog.text = "Fine. I have called it the 'Squall'. Here, take an instruction. Read it carefully. And don't forget how to use it correctly!";
			link.l1 = "Thanks, Amelia...";
			link.l1.go = "recipe_exit";
			AddQuestRecordInfo("Recipe", "mangarosafast");
			SetAlchemyRecipeKnown("mangarosafast");
			npchar.quest.recipe_fast = true;
		break;
		
		case "total":
			dialog.text = "Fine. I have called it the 'Sea Hug'. Here, take an instruction. Read it carefully. And don't forget how to use it correctly!";
			link.l1 = "Thanks, Amelia...";
			link.l1.go = "recipe_exit";
			AddQuestRecordInfo("Recipe", "mangarosatotal");
			SetAlchemyRecipeKnown("mangarosatotal");
			npchar.quest.recipe_total = true;
		break;
		
		case "recipe_exit":
			DialogExit();
			NextDiag.CurrentNode = "amelia_next";
			RemoveItems(pchar, "gold_dublon", 300);
			RemoveItems(pchar, "cannabis7", 1);
			Log_Info("You have given 300 doubloons and one Manga Rosa");
			PlaySound("interface\important_item.wav");
			if (CheckAttribute(npchar, "quest.recipe_power") && CheckAttribute(npchar, "quest.recipe_fast") && CheckAttribute(npchar, "quest.recipe_total"))
			{
				npchar.quest.recipe_all = true;
				CloseQuestHeader("mangarosa");
			}
		break;
	}
} 
