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
			dialog.text = "Что вам надо?";
			link.l1 = "Ничего.";
			link.l1.go = "exit";
		break;
		
		// Амелия - знахарка-цыганка
		case "amelia":
			dialog.text = "Что тебе нужно в моём доме?";
			if (CheckAttribute(pchar, "questTemp.Mangarosa") && pchar.questTemp.Mangarosa == "amelia")
			{
				link.l1 = "Тебя зовут Амелия, верно? Я пришёл к тебе с вопросом, касательно одного растения. Мангаросы.";
				link.l1.go = "amelia_1";
			}
			else
			{
				link.l1 = "Пока, наверное, мне нечего тебе сказать. Но я ещё вернусь...";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "amelia";
		break;
		
		case "amelia_1":
			dialog.text = "Очень интересно! И кто же тебе обо мне понарассказывал, а, соколик?";
			link.l1 = "Да одна из ваших. Сказала, что ты знаешь секреты этого растения и можешь научить готовить из него какие-то особенные зелья...";
			link.l1.go = "amelia_2";
		break;
		
		case "amelia_2":
			dialog.text = "Ну, давай начнём с того, что ты мне покажешь растение, о котором ведёшь речь. Может, ты просто наслушался уличной болтовни, а теперь явился сюда и отвлекаешь меня от важных дел. Где твоя мангароса?";
			if (CheckCharacterItem(pchar, "cannabis7"))
			{
				link.l1 = "Вот она, смотри.";
				link.l1.go = "amelia_3";
			}
			else
			{
				link.l1 = "Гм...";
				link.l1.go = "amelia_exit";
			}
		break;
		
		case "amelia_exit":
			dialog.text = "Ну, и что ты тут мне пытаешься показать? Нет у тебя мангаросы. Так что топай отсюда, парень, пока я не рассердилась. Разговор окончен.";
			link.l1 = "Но...";
			link.l1.go = "exit";
			NextDiag.TempNode = "amelia_wait";
		break;
		
		case "amelia_wait":
			dialog.text = "Опять ты? Не доводи до греха, парень...";
			if (CheckCharacterItem(pchar, "cannabis7"))
			{
				link.l1 = "Не ругайся, Амелия. В прошлый раз я просто её где-то выронил. Вот, я принёс мангаросу. Смотри.";
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
			dialog.text = "Так... Похоже, ты все-таки что-то знаешь. И ты хочешь, чтобы я рассказала тебе секреты своих зелий из этого растения?";
			link.l1 = "Именно так. Ну, конечно, не бесплатно, я понимаю...";
			link.l1.go = "amelia_4";
		break;
		
		case "amelia_4":
			dialog.text = "Ещё бы ты этого не понимал, соколик! На дурня ты совсем не похож. Ну что же, я не против поделиться знаниями с человеком, который сам за ними пришёл, и который не переводит это редкое растение на дурманящее курево...";
			link.l1 = "Амелия, перед тем как торговаться, просвети меня хотя бы в общих чертах - что за зелья получаются из мангаросы?";
			link.l1.go = "amelia_5";
		break;
		
		case "amelia_5":
			dialog.text = "Торговаться, парень, мы с тобой не будем. Я назначаю цену - а ты решишь, будешь её платить, или нет. Ни на какие скидки и торг даже не рассчитывай, чай, не на рынке. Что же касается твоего вопроса: из мангаросы получаются зелья, воздействующие на физические способности. Они могут сделать тебя более сильным, выносливым и быстрым, либо оказать комплексное воздействие на твоё тело.";
			link.l1 = "Очень интересно! Назови свою цену.";
			link.l1.go = "amelia_6";
		break;
		
		case "amelia_6":
			dialog.text = "Я могу научить тебя рецептам трёх зелий. За каждый рецепт я прошу один стебель мангаросы и триста золотых монет.";
			link.l1 = "Расскажи об этих трёх зельях подробнее - что каждое делает?";
			link.l1.go = "amelia_7";
		break;
		
		case "amelia_7":
			dialog.text = "Чтобы изготовить любое зелье, ты должен владеть основами алхимии. Действие всех зелий временное и ограничивается приблизительно двумя днями\nПервое зелье придаёт тебе силы и выносливости. Ты становишься крепче, можешь успешнее противостоять врагам в бою и переносить больше тяжестей\nВторое зелье дарит тебе быстроту, ловкость, неутомимость, а также остроту глаза\nТретье зелье сочетает в себе эффекты первого и второго, но вдвое слабее. Однако оно также придаст тебе обаяния, уверенности в себе и сделает более удачливым\nТакже все зелья из мангаросы положительно влияют на здоровье. Употреблять их следует только по одному, и не раньше, чем закончится действие предыдущего - в противном случае не только не будет эффекта, но напротив - получишь отравление\nНу что, соколик, ты готов оплатить свои новые знания, или тебе нужно время на размышление?";
			if (CheckCharacterItem(pchar, "cannabis7") && GetCharacterItem(pchar, "gold_dublon") >= 300)
			{
				link.l1 = "Да, я готов.";
				link.l1.go = "amelia_8";
			}
			link.l2 = "Я хочу немного подумать. Это непростое решение.";
			link.l2.go = "exit";
			NextDiag.TempNode = "amelia_next";
		break;
		
		case "amelia_next":
			if (CheckAttribute(npchar, "quest.recipe_all"))
			{
				dialog.text = "А-а, это ты, соколик! Ну как, помогают тебе мои зелья?";
				link.l1 = "Даже очень, Амелия. Спасибо тебе!";
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = "А-а, это ты, соколик! Ты хочешь купить у меня рецептов зелий из мангаросы, так?";
				if (CheckCharacterItem(pchar, "cannabis7") && GetCharacterItem(pchar, "gold_dublon") >= 300)
				{
					link.l1 = "Именно. За этим я и пришёл.";
					link.l1.go = "amelia_8";
				}
				link.l2 = "Пока нет, Амелия. Просто заглянул проведать.";
				link.l2.go = "exit";
			}
			NextDiag.TempNode = "amelia_next";
		break;
		
		case "amelia_8":
			dialog.text = "Очень хорошо. Какой рецепт ты хочешь приобрести?";
			if (!CheckAttribute(npchar, "quest.recipe_power"))
			{
				link.l1 = "Рецепт зелья силы и выносливости.";
				link.l1.go = "power";
			}
			if (!CheckAttribute(npchar, "quest.recipe_fast"))
			{
				link.l2 = "Рецепт зелья ловкости и неутомимости.";
				link.l2.go = "fast";
			}
			if (!CheckAttribute(npchar, "quest.recipe_total"))
			{
				link.l3 = "Рецепт комплексного зелья.";
				link.l3.go = "total";
			}
		break;
		
		case "power":
			dialog.text = "Хорошо. Я назвала его 'Удар прибоя'. Вот, возьми инструкцию приготовления. Следуй строго по рецепту. Не забывай о правилах применения!";
			link.l1 = "Спасибо, Амелия...";
			link.l1.go = "recipe_exit";
			AddQuestRecordInfo("Recipe", "mangarosapower");
			SetAlchemyRecipeKnown("mangarosapower");
			npchar.quest.recipe_power = true;
		break;
		
		case "fast":
			dialog.text = "Хорошо. Я назвала его 'Шквал'. Вот, возьми инструкцию приготовления. Следуй строго по рецепту. Не забывай о правилах применения!";
			link.l1 = "Спасибо, Амелия...";
			link.l1.go = "recipe_exit";
			AddQuestRecordInfo("Recipe", "mangarosafast");
			SetAlchemyRecipeKnown("mangarosafast");
			npchar.quest.recipe_fast = true;
		break;
		
		case "total":
			dialog.text = "Хорошо. Я назвала его 'Ласка моря'. Вот, возьми инструкцию приготовления. Следуй строго по рецепту. Не забывай о правилах применения!";
			link.l1 = "Спасибо, Амелия...";
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
			Log_Info("Вы отдали 300 дублонов и стебель мангаросы");
			PlaySound("interface\important_item.wav");
			if (CheckAttribute(npchar, "quest.recipe_power") && CheckAttribute(npchar, "quest.recipe_fast") && CheckAttribute(npchar, "quest.recipe_total"))
			{
				npchar.quest.recipe_all = true;
				CloseQuestHeader("mangarosa");
			}
		break;
	}
} 
