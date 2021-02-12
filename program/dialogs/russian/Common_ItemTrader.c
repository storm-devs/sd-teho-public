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
			dialog.text = NPCharSexPhrase(npchar, "Хотите прикупить снаряжение для себя или своих офицеров, капитан? Тогда вы обратились по адресу!", "Ой, капитан, я так и знала, что вы подойдёте именно ко мне!.. Могу предложить снаряжение для вас и ваших офицеров, а также множество других необходимых вещей.");
			link.l1 = "Покажи, что там у тебя есть.";
			link.l1.go = "Trade_exit";
			
   			link.l2 = "Я по другому делу.";
			link.l2.go = "quests";
			if (CheckCharacterItem(pchar, "cannabis7") && CheckAttribute(pchar, "questTemp.Mangarosa") && pchar.questTemp.Mangarosa == "find" && npchar.Merchant.type == "potion" && !CheckAttribute(npchar, "quest.mangarosa"))
			{
				link.l4 = "Послушай, я тут нашёл одно интересное растение. Не подскажешь, употребляется ли оно для приготовления каких-нибудь зелий, или отваров? Уж больно интересное. Можешь взглянуть?";
				link.l4.go = "mangarosa";
			}
			link.l3 = "Спасибо, не интересует.";
			link.l3.go = "exit";

			//Jason --> мини-квест Дефицитный товар
			if (CheckAttribute(pchar, "questTemp.Wine.bottle") && NPChar.location == pchar.questTemp.Wine.City + "_town" && !CheckAttribute(pchar, "questTemp.Wine.fail"))
			{
   				link.l4 = "Скажи, у тебя можно приобрести бутылочку хорошего европейского вина?";
				link.l4.go = "Wine_ItemTrader";
			}
			if (CheckAttribute(pchar, "questTemp.Wine.bottles") && NPChar.location == pchar.questTemp.Wine.City + "_town" && !CheckAttribute(pchar, "questTemp.Wine.fail"))
			{
   				link.l4 = "Послушай, я знаю, что вы торгуете европейским вином. Мне нужно приобрести шестьдесят бутылок.";
				link.l4.go = "Wine_Bottles";
			}
			if (CheckAttribute(pchar, "questTemp.Wine.Repeat1") && NPChar.location == pchar.questTemp.Wine.City + "_town" && npchar.id == pchar.questTemp.Wine.ItemTraderID && !CheckAttribute(pchar, "questTemp.Wine.fail"))
			{
   				link.l4 = "Это опять я. Как всё это понимать, а?";
				link.l4.go = "Wine_Repeat1";
			}
			// <-- мини-квест Дефицитный товар
			
			//Jason --> генератор Неудачливый вор
			if (CheckAttribute(pchar, "GenQuest.Device.Shipyarder") && NPChar.location == pchar.GenQuest.Device.Shipyarder.City + "_town" && pchar.GenQuest.Device.Shipyarder == "begin" && !CheckAttribute(npchar, "quest.Device"))
			{
   				link.l5 = "Послушай, ты вот торгуешь всякой всячиной... Тебе вчера или сегодня, никто не предлагал купить "+pchar.GenQuest.Device.Shipyarder.Type+"?";
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
			dialog.text = "Есть. Семьсот песо за бутылку.";
			if (makeint(Pchar.money) >= 700)
			{
				link.l1 = "Отлично. Давай её сюда.";
				link.l1.go = "Wine_ItemTrader_1";
			}
			link.l2 = "Очень хорошо! Как надумаю прикупить - вернусь.";
			link.l2.go = "exit";
		break;
		
		case "Wine_ItemTrader_1":
			dialog.text = "Пожалуйста, получите.";
			link.l1 = "Благодарствую!";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, -700);
			TakeNItems(pchar, "potionwine", 1);
			PlaySound("interface\important_item.wav");
			DeleteAttribute(pchar, "questTemp.Wine.bottle");
		break;
		
		case "Wine_Bottles":
			dialog.text = "Эка хватил! У меня здесь не оптовая база, а розничный лоток! Я столько бутылок полгода продавать буду - знаешь ли, товар редкий и дорогой, не каждому по карману. Нет у меня такого количества.";
			link.l1 = "Ладно, нет так нет. Но ты-то откуда его берёшь? Может, назовёшь своего поставщика - я у него и купил бы. Или ты сам"+ NPCharSexPhrase(npchar, "","а") +" из Европы возишь?";
			link.l1.go = "Wine_Bottles_1";
		break;
		
		case "Wine_Bottles_1":
			dialog.text = "Нет, сам"+ NPCharSexPhrase(npchar, "","а") +" не вожу. Беру здесь. Но просто так я тебе своего поставщика не назову. А вот за тысчонку песо... пожалуй, скажу.";
			if (makeint(Pchar.money) >= 1000)
            {
				link.l1 = "Хорошо. Держи свою тысячу и говори, у кого затариваешься.";
				link.l1.go = "Wine_Bottles_2";
			}
			link.l2 = "Ну совсем торгаш"+ NPCharSexPhrase(npchar, "и","ки") +" обнаглели! А жирно тебе не будет? Обойдусь и без твоего поставщика.";
			link.l2.go = "Wine_Bottles_fail";
		break;
		
		case "Wine_Bottles_2":
    		AddMoneyToCharacter(pchar, -1000);
			pchar.questTemp.Wine.TraderID = pchar.questTemp.Wine.City +"_trader";
			sld = characterFromId(pchar.questTemp.Wine.TraderID);
			pchar.questTemp.Wine.Name = GetFullName(sld);
			pchar.questTemp.Wine.ItemTraderID = npchar.id;
			dialog.text = "Моего поставщика вина зовут "+pchar.questTemp.Wine.Name+", он хозяин местного магазина.";
			link.l1 = "Всё понял. Спасибо!";
			link.l1.go = "exit";
			pchar.questTemp.Wine.Trader = "true";
			DeleteAttribute(pchar, "questTemp.Wine.bottles");
			AddQuestRecord("Wine", "3");
			AddQuestUserData("Wine", "sName", pchar.questTemp.Wine.Name);
		break;
		
		case "Wine_Bottles_fail":
			dialog.text = "Как знаете, капитан. Всего доброго.";
			link.l1 = "Бывай.";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.Wine.bottles");
			AddQuestRecord("Wine", "4");
		break;
		
		case "Wine_Repeat1":
			DeleteAttribute(pchar, "questTemp.Wine.Repeat1");
			dialog.text = "Что понимать? Объясните внятно, пожалуйста.";
			link.l1 = "Ты обманул"+ NPCharSexPhrase(npchar, "","а") +" меня, проклят"+ NPCharSexPhrase(npchar, "ый","ая") +" мерзав"+ NPCharSexPhrase(npchar, "ец","ка") +"! Я только что был в магазине, "+pchar.questTemp.Wine.Name+" никогда вином не торговал - он сам мне это сказал! Гони назад мои деньги!";
			link.l1.go = "Wine_Repeat1_fail";
			link.l2 = "Тут ерунда какая-то вышла... Прихожу я в магазин, а "+pchar.questTemp.Wine.Name+" заявляет, что никогда вином не торговал. Как вы объясните это?";
			link.l2.go = "Wine_Repeat1_1";
		break;
		
		case "Wine_Repeat1_1":
			dialog.text = "Хех! Он торгует вином, уверяю вас. Вот только каждому встречному он это вино, как и некоторые другие товары, не продает. И причины на это имеются... Если хотите, чтобы он продал вам вино - я могу написать записку - меня он знает, мой почерк тоже, так что прочитав её, продаст вам вина, как вы и хотите. Конечно, эта услуга с моей стороны тоже не бесплатная.";
			link.l1 = "Вот так номер! Но вы же только что взяли с меня тысячу!";
			link.l1.go = "Wine_Repeat1_2";
		break;
		
		case "Wine_Repeat1_2":
			dialog.text = "Тысячу я с вас взял"+ NPCharSexPhrase(npchar, "","а") +" за информацию. А за письмо вам надо заплатить отдельно - две тысячи песо, и никак не меньше.";
			if (makeint(Pchar.money) >= 2000)
			{
				link.l1 = "Ох... Ну до чего же вы, торгаш"+ NPCharSexPhrase(npchar, "и","ки") +", жадные. Недаром вас, барыг, не любят. Держите ваши деньги и пишите записку.";
				link.l1.go = "Wine_Bottles_3";
			}
			link.l2 = "Ну это уже ни в какие ворота не лезет. Да я лучше брошу всем этим заниматься, но не стану обогощать так"+ NPCharSexPhrase(npchar, "ого","ую") +" хитр"+ NPCharSexPhrase(npchar, "ого","ую") +" скрягу. Я имею в виду вас. Прощайте.";
			link.l2.go = "Wine_Repeat1_goaway";
		break;
		
		case "Wine_Bottles_3":
			AddMoneyToCharacter(pchar, -2000);
			dialog.text = "Вы странный человек, капитан! Я конечно, понимаю, что всеми финансами у вас на корабле ведает казначей, но вы могли бы и сами думать иногда. Вы сейчас пойдёте и купите приличную партию вина без моей торговой наценки, по оптовой цене, и получите немалый барыш. Так что давайте не будем мешать зарабатывать друг другу - ибо жадным сейчас выглядите именно вы\nТак...(пишет)... Вот, возьмите это письмо - теперь "+pchar.questTemp.Wine.Name+" продаст вам вино без всяких лишних вопросов.";
			link.l1 = "Буду на это надеятся... Если что - я вернусь! До свидания!";
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
			dialog.text = "Как знаете, капитан. Прощайте.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddQuestRecord("Wine", "4");
		break;
		
		case "Wine_Repeat1_fail":
			dialog.text = "Ах, вы хамить и угрожать мне тут вздумали? Я сейчас стражу позову! Стра-ажа!! Сюда!";
			link.l1 = "Да заткнись ты! Ладно, я ухожу! Будь ты проклят"+ NPCharSexPhrase(npchar, "","а") +", сквалыга, чтоб тебе по миру пойти!";
			link.l1.go = "exit";
			AddQuestRecord("Wine", "7");
		break;
		// <-- мини-квест Дефицитный товар
		
		//Jason --> генератор Неудачливый вор
		case "Device_ItemTrader":
			dialog.text = "Гм, "+pchar.GenQuest.Device.Shipyarder.Type+"? Впервые слышу... Хоть что это за вещь такая - сколько живу на свете, ничего подобного в глаза не видел"+ NPCharSexPhrase(npchar, "","а") +".";
			link.l1 = "Ну, это судостроительный инструмент, "+pchar.GenQuest.Device.Shipyarder.Describe+". Никто ничего подобного тебе не предлагал?";
			link.l1.go = "Device_ItemTrader_1";
			npchar.quest.Device = "true";
		break;
		
		case "Device_ItemTrader_1":
			if (sti(pchar.GenQuest.Device.Shipyarder.Chance1) > 0 && sti(pchar.GenQuest.Device.Shipyarder.Chance1) < 4 && npchar.location.group == "merchant" && npchar.location.locator == "merchant"+sti(pchar.GenQuest.Device.Shipyarder.Chance1))
			{
				dialog.text = "Хм... Да, приносил мне такую вещь один странный тип. Только он её никак не назвал, а просто пытался мне продать. Да только зачем она мне, если я даже не знаю, для чего она нужна? Как я её потом продать сумею? В общем, отказал"+ NPCharSexPhrase(npchar, "","а") +" я ему, и он ушёл.";
				link.l1 = "А как выглядел этот человек и куда пошёл? Мне очень нужен этот инструмент.";
				link.l1.go = "Device_Common";
			}
			else
			{
				dialog.text = "Нет, никто не приносил. Так что помочь ничем не могу. Поспрашивай ещё у кого.";
				link.l1 = "Ясно. Пойду спрашивать!";
				link.l1.go = "exit";
			}
		break;
		// <-- генератор Неудачливый вор
		
		// Мангароса
		case "mangarosa":
			// тут работает везение
			if (sti(pchar.questTemp.Mangarosa.m_count) == 5 || GetSummonSkillFromName(pchar, SKILL_FORTUNE) > 10+drand(30)+drand(40))
			{
				dialog.text = "Покажите... Да, растение интересное. И, что главное - очень, очень редкое. Его называют мангароса. Для чего его используют - я не знаю, но с ним связан один любопытный факт...";
				link.l1 = "Что ты имеешь в виду?";
				link.l1.go = "mangarosa_1";
			}
			else
			{
				dialog.text = LinkRandPhrase("Покажите... Да, растение интересное. Но подсказать вам ничего определенного не могу. Область его применения, если таковая и есть, мне неведома.","Давайте посмотрим... Хм. Похоже на лекарственное, но оно мне незнакомо. Так что ничем не могу помочь.","Где оно? Так-так... нет, не встречалось мне такое никогда. На вид очень занятное, но для чего его можно использовать - не представляю...");
				link.l1 = "Ясно. Буду спрашивать ещё. Извини...";
				link.l1.go = "mangarosa_exit";
			}
		break;
		
		case "mangarosa_exit":
			DialogExit();
			pchar.questTemp.Mangarosa.m_count = sti(pchar.questTemp.Mangarosa.m_count)+1;
			npchar.quest.mangarosa = "true";
		break;
		
		case "mangarosa_1":
			dialog.text = "Этим растением интересуются бродячие цыганки и дикари. Мне доводилось видеть, как цыганка отсыпала целую пригоршню золотых всего за один вот такой стебель. Зачем оно им нужно - я не знаю.";
			link.l1 = "Так-так... Ну, уже что-то! По крайней мере, я знаю, у кого дальше выспрашивать. Спасибо огромное!";
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
