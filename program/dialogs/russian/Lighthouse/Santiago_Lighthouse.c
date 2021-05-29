// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Что вам угодно?", "Что вы хотели узнать?"), "Так скажите, что же вас интересует, " + GetAddress_Form(NPChar) + "?", "Третий раз за сегодня вы пытаетесь задать вопрос...", "Всё, вы меня утомили. Покиньте мой дом!", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Я передумал"+ GetSexPhrase("","а") +"...", "Сейчас мне не о чем говорить"), "Ох, что-то я запамятовал. Простите...",
                      "Да уж, действительно в третий раз...", "Извиняюсь...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "mayak")
			{
				link.l1 = "Инквизитор Сантьяго, отец Винсенто, упомянул тебя в своем письме. Тебе известно про это?";
                link.l1.go = "guardoftruth";
			}
			if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "mayak_next")
			{
				link.l1 = "Есть ли новости от отца Винсенто, "+npchar.name+"?";
                link.l1.go = "guardoftruth_5";
			}
			if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "utensil" && CheckCharacterItem(pchar, "jewelry33") && CheckCharacterItem(pchar, "jewelry34") && CheckCharacterItem(pchar, "jewelry35"))
			{
				link.l1 = "Мне нужно увидеть отца Винсенто. Я нашел вещи, которые ему нужны.";
                link.l1.go = "guardoftruth_7";
			}
			if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "inquisition")
			{
				link.l1 = "Итак, "+npchar.name+", что сказал отец Винсенто?";
                link.l1.go = "guardoftruth_11";
			}
		break;
		
		case "guardoftruth":
			dialog.text = "Конечно, сеньор. Вы, видать, большая шишка, раз сам отец Винсенто ведет с вами дела...";
			link.l1 = "Прекрасно. Значит, ты - наш связной. Теперь слушай: вот этот человек - тот самый капер, которого так жаждет увидеть отец Винсенто. Я передаю его под твою ответственность - ты должен доставить его в Сантьяго, или привести сюда за ним кого-то...";
			link.l1.go = "guardoftruth_1";
		break;
		
		case "guardoftruth_1":
			dialog.text = "";
			link.l1 = "За пленника отвечаешь перед самим инквизитором. Не советую снимать кандалы - Гай Марше парень прыткий, да и силенка в руках имеется. Кроме того, передай отцу Винсенто это письмо и скажи, что я жду на него ответа через два дня. Думаю, этого будет достаточно...";
			link.l1.go = "guardoftruth_2";
		break;
		
		case "guardoftruth_2":
			Log_Info("Вы передали письмо");
			PlaySound("interface\important_item.wav");
			dialog.text = "Я вас понял, сеньор. Все будет сделано в лучшем виде, не сомневайтесь. Я не первый раз помогаю святому отцу.";
			link.l1 = "Это еще не все. К тебе должен был прибыть капитан каракки 'Сан-Грегорио', Карлос Геварра. Он привез ваниль для меня. Он передавал мое письмо?";
			link.l1.go = "guardoftruth_3";
		break;
		
		case "guardoftruth_3":
			dialog.text = "Ваш груз в полном порядке, сеньор, дожидается вас.";
			link.l1 = "Отлично. Я распоряжусь о его погрузке в мои трюмы. Через два дня я приду за ответом от отца Винсенто. Не прощаюсь, "+npchar.name+"!..";
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
			dialog.text = "Да, сеньор. Вот письмо от Его Преосвященства. Отец Винсенто очень доволен вами. Также он сказал, что вы все сами поймете из текста письма.";
			link.l1 = "Прекрасно. Думаю, мы скоро опять увидимся, "+npchar.name+". А пока - до свидания...";
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
			dialog.text = "Отлично. Давайте их мне, я передам святому отцу.";
			link.l1 = "Ну нет, дружище! Очень уж тяжелым трудом они мне достались, чтобы я с ними расстался. Я передам их только отцу Винсенто лично в руки.";
			link.l1.go = "guardoftruth_8";
		break;
		
		case "guardoftruth_8":
			dialog.text = "Но сеньор! Как мне узнать, что вы не лукавите?";
			link.l1 = "Погляди: вот золотое кадило, вот остензорий, а вот и крест с лазуритом... "+npchar.name+", ты за кого меня принимаешь? Неужели ты думаешь, что у меня хватит тупости отправиться прямиком в инквизицию, не имея на руках того, что нужно отцу Винсенто?";
			link.l1.go = "guardoftruth_9";
		break;
		
		case "guardoftruth_9":
			dialog.text = "Прошу меня простить, сеньор... Приходите завтра, я сообщу отцу Винсенто о вашем прибытии.";
			link.l1 = "Хорошо. Увидимся завтра утром!";
			link.l1.go = "guardoftruth_10";
		break;
		
		case "guardoftruth_10":
			DialogExit();
			pchar.questTemp.Guardoftruth = "mayak_wait";
			SetFunctionTimerCondition("GuardOT_MayakLastStage", 0, 0, 1, false);
		break;
		
		case "guardoftruth_11":
			dialog.text = "Его Преосвященство примет вас, сеньор. Не затягивайте с визитом. Вот, он передал для вас эту грамоту - покажите ее страже, и она не будет чинить вам препятствий. Но учтите, что на вашем корабле должен быть поднят флаг Испании, иначе солдаты по уставу будут обязаны арестовать вас.";
			link.l1 = "Я понял. Испанский флаг - значит, испанский. Спасибо, дружище! Немедленно отправляюсь в путь!";
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