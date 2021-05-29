#include "DIALOGS\russian\Rumours\Common_rumours.c" //Jason
void ProcessDialogEvent()
{
 	ref NPChar;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	// вызов диалога по городам -->
    NPChar.FileDialog2 = "DIALOGS\" + LanguageGetLanguage() + "\ItemTrader\" + NPChar.City + "_ItemTrader.c";
    if (LoadSegment(NPChar.FileDialog2))
	{
        ProcessCommonDialog(NPChar, Link, NextDiag);
		UnloadSegment(NPChar.FileDialog2);
	}
    // вызов диалога по городам <--
	ProcessCommonDialogRumors(NPChar, Link, NextDiag);
// ============================================================================
// ============================= блок angry ==========>>>>>>>>>>>>>>>>>>>>>>>>>
    if (CheckAttribute(npchar, "angry") && !CheckAttribute(npchar, "angry.ok"))
    {
        npchar.angry.ok = 1;
        if (!CheckAttribute(npchar, "angry.first")) //ловушка первого срабатывания
        {
            NextDiag.TempNode = NextDiag.CurrentNode;
            Dialog.CurrentNode = "AngryExitAgain";
            npchar.angry.first = 1;
        }
        else
        {
			
        }
    }
// <<<<<<<<<<<<<<<<<<<<<<======= блок angry ===================================
// ============================================================================	   
	switch(Dialog.CurrentNode)
	{
		// -----------------------------------Диалог первый - первая встреча
  		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "fight":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_group_Attack(NPChar, Pchar);
		break;

  		case "First time":
			dialog.text = NPCharSexPhrase(npchar, "Would you like to buy equipment for yourself or for your officers, captain? If so, you've come just to the right person!", "Oh, captain, I knew that you'd approach me! I can offer you equipment for you and your officers, and also many other useful things.");
			link.l1 = "Show me what you've got.";
			link.l1.go = "Trade_exit";
			
   			link.l2 = "I came on a different business.";
			link.l2.go = "quests";
			if (CheckCharacterItem(pchar, "cannabis7") && CheckAttribute(pchar, "questTemp.Mangarosa") && pchar.questTemp.Mangarosa == "find" && npchar.Merchant.type == "potion" && !CheckAttribute(npchar, "quest.mangarosa"))
			{
				link.l4 = "Hey, I've found one interesting plant around. Could you tell me can it be used to brew potions or decoctions? It just seems interesting to me. Can you take a look?";
				link.l4.go = "mangarosa";
			}
			link.l3 = "Thank you, not interested.";
			link.l3.go = "exit";

			//Jason --> мини-квест Дефицитный товар
			if (CheckAttribute(pchar, "questTemp.Wine.bottle") && NPChar.location == pchar.questTemp.Wine.City + "_town" && !CheckAttribute(pchar, "questTemp.Wine.fail"))
			{
   				link.l4 = "Say, can you sell me a bottle of fine European wine?";
				link.l4.go = "Wine_ItemTrader";
			}
			if (CheckAttribute(pchar, "questTemp.Wine.bottles") && NPChar.location == pchar.questTemp.Wine.City + "_town" && !CheckAttribute(pchar, "questTemp.Wine.fail"))
			{
   				link.l4 = "Listen, I know that you're selling European wine. I need sixty bottles.";
				link.l4.go = "Wine_Bottles";
			}
			if (CheckAttribute(pchar, "questTemp.Wine.Repeat1") && NPChar.location == pchar.questTemp.Wine.City + "_town" && npchar.id == pchar.questTemp.Wine.ItemTraderID && !CheckAttribute(pchar, "questTemp.Wine.fail"))
			{
   				link.l4 = "That's me again. What does it all mean, huh?";
				link.l4.go = "Wine_Repeat1";
			}
			// <-- мини-квест Дефицитный товар
			
			//Jason --> генератор Неудачливый вор
			if (CheckAttribute(pchar, "GenQuest.Device.Shipyarder") && NPChar.location == pchar.GenQuest.Device.Shipyarder.City + "_town" && pchar.GenQuest.Device.Shipyarder == "begin" && !CheckAttribute(npchar, "quest.Device"))
			{
   				link.l5 = "Listen, you're dealing in all sorts of goods... Yesterday or today - did anyone offer you to buy "+pchar.GenQuest.Device.Shipyarder.Type+"?";
				link.l5.go = "Device_ItemTrader";
			}
			//<-- генератор Неудачливый вор

			NextDiag.TempNode = "First time";
		break;

		case "Trade_exit":
            if (CheckNPCQuestDate(npchar, "Item_date"))
			{
				SetNPCQuestDate(npchar, "Item_date");
				GiveItemToTrader(npchar);
			}
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LaunchItemsTrade(npchar, 0);
		break;
		
		//Jason --> мини-квест Дефицитный товар
		case "Wine_ItemTrader":
			dialog.text = "Sure. Seven hundred pesos per bottle.";
			if (makeint(Pchar.money) >= 700)
			{
				link.l1 = "Excellent. Take money and give it to me.";
				link.l1.go = "Wine_ItemTrader_1";
			}
			link.l2 = "Excellent! I'll be back once I decide to buy some.";
			link.l2.go = "exit";
		break;
		
		case "Wine_ItemTrader_1":
			dialog.text = "Please, take your bottle.";
			link.l1 = "I thank you!";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, -700);
			TakeNItems(pchar, "potionwine", 1);
			PlaySound("interface\important_item.wav");
			DeleteAttribute(pchar, "questTemp.Wine.bottle");
		break;
		
		case "Wine_Bottles":
			dialog.text = "Ha! I'm just a retailer, not a wholesaler. I'd be selling that many bottles for over half a year - that wine is rare and expensive, and not just anyone can afford it, you know. I don't have that many.";
			link.l1 = "Alright, you don't have them - no problem. But you get it somewhere for yourself, don't you? Maybe you could tell me the name of your supplier, and I'd buy it directly from him. Or is wine delivered to you from Europe?";
			link.l1.go = "Wine_Bottles_1";
		break;
		
		case "Wine_Bottles_1":
			dialog.text = "No, it isn't. I get it here. But I won`t name you my supplier simple as that. But for a thousand peso... perhaps, I would...";
			if (makeint(Pchar.money) >= 1000)
            {
				link.l1 = "Fine. Here's your thousand - and now tell me, who your supplier is.";
				link.l1.go = "Wine_Bottles_2";
			}
			link.l2 = "Now you hucksters have gone too brazen! Wouldn't it be too good for you? I'll do fine without your supplier, thanks.";
			link.l2.go = "Wine_Bottles_fail";
		break;
		
		case "Wine_Bottles_2":
    		AddMoneyToCharacter(pchar, -1000);
			pchar.questTemp.Wine.TraderID = pchar.questTemp.Wine.City +"_trader";
			sld = characterFromId(pchar.questTemp.Wine.TraderID);
			pchar.questTemp.Wine.Name = GetFullName(sld);
			pchar.questTemp.Wine.ItemTraderID = npchar.id;
			dialog.text = "The name of my wine supplier is "+pchar.questTemp.Wine.Name+", he owns the local store.";
			link.l1 = "Got it! Thanks!";
			link.l1.go = "exit";
			pchar.questTemp.Wine.Trader = "true";
			DeleteAttribute(pchar, "questTemp.Wine.bottles");
			AddQuestRecord("Wine", "3");
			AddQuestUserData("Wine", "sName", pchar.questTemp.Wine.Name);
		break;
		
		case "Wine_Bottles_fail":
			dialog.text = "As you wish, captain. All the best to you.";
			link.l1 = "See you.";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.Wine.bottles");
			AddQuestRecord("Wine", "4");
		break;
		
		case "Wine_Repeat1":
			DeleteAttribute(pchar, "questTemp.Wine.Repeat1");
			dialog.text = "What do you mean by that? Explain yourself.";
			link.l1 = "You have tricked me, you rascal! I've just been at the store, "+pchar.questTemp.Wine.Name+" never  deals in wine, as he himself told me that! Give me my money back!";
			link.l1.go = "Wine_Repeat1_fail";
			link.l2 = "There was a misunderstanding... I came to the storekeeper, and "+pchar.questTemp.Wine.Name+" claimed that he'd never dealt in wine. How can you explain it?";
			link.l2.go = "Wine_Repeat1_1";
		break;
		
		case "Wine_Repeat1_1":
			dialog.text = "Heh! He deals in wine, that's for damn sure. He just doesn't sell wine to any first comer - like a few other goods, too. And there are several reasons to that... If you want to buy wine from him, I can write him a note. He knows me and my handwriting, so, after he's read it, he will sell you that wine. Of course, this favor is not free, either.";
			link.l1 = "That's an outrage! You've just taken a grand from me!";
			link.l1.go = "Wine_Repeat1_2";
		break;
		
		case "Wine_Repeat1_2":
			dialog.text = "I took thousand from you for information. And for a letter you have to pay separately two thousand pesos, and in any way not less than that.";
			if (makeint(Pchar.money) >= 2000)
			{
				link.l1 = "Oh... You traders are so damn greedy. No wonder that no one likes your kind. Oh well, here's your money, so go ahead and write the note.";
				link.l1.go = "Wine_Bottles_3";
			}
			link.l2 = "Now that's completely out of line! I'd rather abandon the whole affair, but I will not enrich such a cunning miser. And by that miser I mean you. Farewell.";
			link.l2.go = "Wine_Repeat1_goaway";
		break;
		
		case "Wine_Bottles_3":
			AddMoneyToCharacter(pchar, -2000);
			dialog.text = "You are a queer bird, captain! Sure, I realize that your purser does all the financials, but you should use your own head too sometimes. You will have an opportunity to buy a decent lot of wines wholesale without my price markup and make a considerable profit. So let's not prevent each other from making coin, because it is you who look greedy now\nRight...(writing) Here, take this letter - "+pchar.questTemp.Wine.Name+"  will sell you the wine without any questions.";
			link.l1 = "I do hope so... If anything goes wrong again, I will be back. See you!";
			link.l1.go = "Wine_Bottles_4";
		break;
		
		case "Wine_Bottles_4":
			pchar.questTemp.Wine.Repeat2 = "true";
			TakeNItems(pchar, "letter_1", 1);
			ChangeItemDescribe("letter_1", "itmdescr_letter_1");
			PlaySound("interface\important_item.wav");
			AddQuestRecord("Wine", "6");
			DialogExit();
		break;
		
		case "Wine_Repeat1_goaway":
			dialog.text = "As you wish, captain. Farewell.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddQuestRecord("Wine", "4");
		break;
		
		case "Wine_Repeat1_fail":
			dialog.text = "Oh, so you've come here to threaten me and be rude? I'll call the guards, then! Hey, guards! Right here!";
			link.l1 = "Oh, shut up! You won, I'm leaving! Curse you "+ NPCharSexPhrase(npchar, "","") +", cormorant, may you get ruined!";
			link.l1.go = "exit";
			AddQuestRecord("Wine", "7");
		break;
		// <-- мини-квест Дефицитный товар
		
		//Jason --> генератор Неудачливый вор
		case "Device_ItemTrader":
			dialog.text = "Hmm, "+pchar.GenQuest.Device.Shipyarder.Type+"? Never heard about it before... Just what is it, actually? I've never heard about such a thing in all my time"+ NPCharSexPhrase(npchar, "","") +".";
			link.l1 = "Well, it's a shipwright's tool, "+pchar.GenQuest.Device.Shipyarder.Describe+". Did anyone offer to you anything like that?";
			link.l1.go = "Device_ItemTrader_1";
			npchar.quest.Device = "true";
		break;
		
		case "Device_ItemTrader_1":
			if (sti(pchar.GenQuest.Device.Shipyarder.Chance1) > 0 && sti(pchar.GenQuest.Device.Shipyarder.Chance1) < 4 && npchar.location.group == "merchant" && npchar.location.locator == "merchant"+sti(pchar.GenQuest.Device.Shipyarder.Chance1))
			{
				dialog.text = "Hmm... Yeah, there was one strange guy. But he didn't tell me what that thing was, he just tried to sell it to me. But what would I need it for, if I had no idea what's it for? How would I resell it? So, I just refused"+ NPCharSexPhrase(npchar, "","") +" to him, and he went away";
				link.l1 = "And how did he look like and where did he go? I need that instrument badly.";
				link.l1.go = "Device_Common";
			}
			else
			{
				dialog.text = "No, nothing like that. Sorry, I can't help you. Ask around.";
				link.l1 = "I see. Well, it's time to ask around!";
				link.l1.go = "exit";
			}
		break;
		// <-- генератор Неудачливый вор
		
		// Мангароса
		case "mangarosa":
			// тут работает везение
			if (sti(pchar.questTemp.Mangarosa.m_count) == 5 || GetSummonSkillFromName(pchar, SKILL_FORTUNE) > 10+drand(30)+drand(40))
			{
				dialog.text = "Show it to me... Yes, that's an interesting plant. And a very, very rare one. It is called mangarosa. I don't know for what it is used, but there was an interesting fact relevant to it...";
				link.l1 = "What do you mean?";
				link.l1.go = "mangarosa_1";
			}
			else
			{
				dialog.text = LinkRandPhrase("Show it to me... Yes, that's an interesting plant. But, unfortunately, I can't tell you more than that. If it is indeed used for some purpose, it's unknown to me.","Let's see... Hmm... It looks like a medicinal plant, but I don't know anything about it. Sorry, I can't help you.","Where is it? Hmm... No, I've never seen this one before. It sure looks very interesting, but I have no clue what it's used for...");
				link.l1 = "I see. Well, I'll ask around some more. Sorry.";
				link.l1.go = "mangarosa_exit";
			}
		break;
		
		case "mangarosa_exit":
			DialogExit();
			pchar.questTemp.Mangarosa.m_count = sti(pchar.questTemp.Mangarosa.m_count)+1;
			npchar.quest.mangarosa = "true";
		break;
		
		case "mangarosa_1":
			dialog.text = "Nomadic gypsies and savages show great interest in these plants. I saw once a gypsy paying a hand full of gold for just one stem such as this one. But I have no idea why they need it.";
			link.l1 = "I see... Well, it's something at least! Now I know where to ask further. Thank you very much!";
			link.l1.go = "mangarosa_2";
		break;
		
		case "mangarosa_2":
			DialogExit();
			npchar.quest.mangarosa = "true";
			DeleteAttribute(pchar, "questTemp.Mangarosa.m_count");
			pchar.questTemp.Mangarosa = "gipsy";
			AddQuestRecord("Mangarosa", "2");
		break;
		
// ======================== блок нод angry ===============>>>>>>>>>>>>>>>

////////////////////////////////////////////////////////////////////////////////////////////////
		case "AngryExitAgain":
            DialogExit();
            DeleteAttribute(npchar, "angry.ok")
		break;

// <<<<<<<<<<<<============= блок нод angry =============================
	}
}
