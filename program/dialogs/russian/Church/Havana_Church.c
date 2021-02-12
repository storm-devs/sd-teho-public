// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Какие вопросы, "+ GetSexPhrase("сын мой","дочь моя") +"?", "Спрашивай, я слушаю тебя..."), "Я слушаю тебя, говори, "+ GetSexPhrase("сын мой","дочь моя") +"...", "И в третий раз говорю тебе, "+ GetSexPhrase("сын мой","дочь моя") +": задавай свой вопрос.",
                          "Столько обязанностей у церковнослужителя, а тут ещё и ты донимаешь, "+ GetSexPhrase("сын мой","дочь моя") +"...", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Я "+ GetSexPhrase("передумал","передумала") +"...", "Не сейчас, падре..."), "Да, пока особо и нечего сказать...",
                      "Задам, задам... Только позже...", "Простите, святой отец...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			// калеуче
			if (CheckAttribute(pchar, "questTemp.Caleuche") && pchar.questTemp.Caleuche == "havana")
			{
				ref sld = characterFromId("Villemstad_Priest");
				link.l1 = "Меня прислал отец "+sld.name+", это настоятель церкви Виллемстада. Вы сообщили ему о том, что в пещере на Кубе были замечены...";
				link.l1.go = "caleuche";
			}
			if (CheckAttribute(pchar, "questTemp.Caleuche") && pchar.questTemp.Caleuche == "havana1")
			{
				link.l1 = "Я посетил пещеру в джунглях, святой отец.";
				link.l1.go = "caleuche_4";
			}
		break;
		
		case "caleuche":
			dialog.text = "Слава Богу, что он откликнулся на это! Едва слухи об оживших мертвецах достигли моих ушей, я поставил в известность Его Преподобие отца Винсенто, инквизитора Сантьяго. Он обещал разобраться, но до сих пор не было предпринято никаких действий! Боюсь, что у Его Святейшества более важные дела...";
			link.l1 = "Я займусь этим делом. Возможно, все эти слухи - не более, чем россказни подгулявших охотников, поэтому инквизиция и не восприняла их всерьёз. Я лично отправлюсь в джунгли и посмотрю на всё собственными глазами.";
			link.l1.go = "caleuche_1";
		break;
		
		case "caleuche_1":
			dialog.text = "Уверяю тебя, сын мой, это не шутки! Человек, который поведал мне о ходячих мертвецах, заслуживает самого полного доверия!";
			link.l1 = "Хорошо. Я буду готов к схватке. И если нечисть действительно угнездилась в пещере - я выбью её оттуда.";
			link.l1.go = "caleuche_2";
		break;
		
		case "caleuche_2":
			dialog.text = "Да пребудет с тобой сила Господа нашего! Вот, возьми этот освящённый оберег. Он поможет тебе в схватке. Уничтожь дьявольское отродье!";
			link.l1 = "До встречи, отец "+npchar.name+". По возвращении назад я немедленно приду к вам.";
			link.l1.go = "caleuche_3";
		break;
		
		case "caleuche_3":
			DialogExit();
			AddQuestRecord("Caleuche", "27");
			pchar.questTemp.Caleuche = "cave";
			Log_Info("Вы получили церковный оберег");
			PlaySound("interface\important_item.wav");
			GiveItem2Character(pchar, "amulet_7"); 
			if (GetCharacterIndex("cavehunter") != -1)
			{
				sld = characterFromId("cavehunter");
				sld.dialog.currentnode = "cavehunter_5";
				LAi_SetGuardianType(sld);
				sld.protector = true;
				LAi_group_MoveCharacter(sld, "SPAIN_CITIZENS");
			}
			LocatorReloadEnterDisable("Cuba_Jungle_07", "reload2_back", false);
			pchar.quest.Caleuche_cuba_caveentrance.win_condition.l1 = "location";
			pchar.quest.Caleuche_cuba_caveentrance.win_condition.l1.location = "Cuba_CaveEntrance";
			pchar.quest.Caleuche_cuba_caveentrance.function = "Caleuche_CubaCaveEntrance";
		break;
		
		case "caleuche_4":
			dialog.text = "Что ты там нашёл, сын мой? Быть может, наши страхи были напрасны?";
			link.l1 = "Увы, не напрасны. Пещера буквально кишела нечистью. С Божьей помощью я уничтожил всех оживших мертвецов. Больше они не будут беспокоить людей.";
			link.l1.go = "caleuche_5";
		break;
		
		case "caleuche_5":
			dialog.text = "Слава Всевышнему! Ты воистину карающий меч Господень, сын мой! Позволь выразить тебе глубокую признательность от всего прихода Гаваны, и прими мою награду: вот эти освящённые обереги. Они наверняка пригодятся тебе в твоих нелёгких странствиях.";
			link.l1 = "Спасибо, отец "+npchar.name+".";
			link.l1.go = "caleuche_6";
		break;
		
		case "caleuche_6":
			Log_Info("Вы получили церковные обереги");
			PlaySound("interface\important_item.wav");
			GiveItem2Character(pchar, "amulet_3"); 
			GiveItem2Character(pchar, "amulet_9"); 
			GiveItem2Character(pchar, "obereg_7"); 
			GiveItem2Character(pchar, "obereg_11"); 
			dialog.text = "Также я позабочусь, чтобы о твоём подвиге узнали и простые горожане, и власть придержащие. И буду неустанно молиться за тебя.";
			link.l1 = "Благодарю, святой отец. Но у меня есть ещё вопрос к вам.";
			link.l1.go = "caleuche_7";
		break;
		
		case "caleuche_7":
			dialog.text = "Спрашивай, сын мой.";
			link.l1 = "Скажите, отец "+npchar.name+", к вам в город не прибывал человек по имени Жоаким Мерриман? Немолодой сеньор, португалец, носит усы и эспаньолку, с пронзительным взглядом?";
			link.l1.go = "caleuche_8";
		break;
		
		case "caleuche_8":
			sld = characterFromId("Villemstad_Priest");
			dialog.text = "Это имя, как и описание, ничего не говорит мне. А кто он такой, этот человек?";
			link.l1 = "Мерриман - колдун, которого уже много лет преследует инквизиция. Я и отец "+sld.name+" подозреваем, что появление на Кубе оживших мертвецов - его рук дело. Он не так давно проживал в Виллемстаде, потом уехал, а женщина, сдававшая ему комнату, через некоторое время превратилась в ужасный ходячий скелет.";
			link.l1.go = "caleuche_9";
		break;
		
		case "caleuche_9":
			dialog.text = "Какой кошмар! Я немедленно сообщу в инквизицию, самому отцу Винсенто! Он должен знать, что у нас происходит! Скажи, сын мой, ты подозреваешь, что пропавшие в джунглях люди...";
			link.l1 = "Да! Я думаю, что мертвецы, нечисть в пещере - это то, во что превратились ваши исчезнувшие граждане. И хочу хорошенько поискать на Кубе этого португальца. Мерзавец заполучил в свои руки древний языческий артефакт, нефритовый череп Юм Симиля. Боюсь, что с его помощью и помощью индейского колдовства, Мерриман натворит ещё немало бед, если его не остановить.";
			link.l1.go = "caleuche_10";
		break;
		
		case "caleuche_10":
			dialog.text = "Ты хочешь сказать, что история с заселением пещеры нечистью может повториться?";
			link.l1 = "Я почти уверен в этом. Не знаю, что движет Жоакимом Мерриманом, но его замыслы далеки от благодетельных.";
			link.l1.go = "caleuche_11";
		break;
		
		case "caleuche_11":
			dialog.text = "Да смилуется над нами Всевышний! Ищи, сын мой, благословляю тебя и разрешаю любые действия во имя нашей Церкви! И я немедленно отправляю гонца в Сантьяго с депешей к отцу Винсенто.";
			link.l1 = "Отправляйте. Всего доброго, отец "+npchar.name+".";
			link.l1.go = "caleuche_12";
		break;
		
		case "caleuche_12":
			DialogExit();
			AddQuestRecord("Caleuche", "29");
			pchar.questTemp.Caleuche = "graveyard";
			AddCharacterMaxHealth(pchar, 3);
			ChangeCharacterComplexReputation(pchar, "nobility", 3);
			ChangeCharacterComplexReputation(pchar, "authority", 2);
			ChangeCharacterComplexReputation(pchar, "fame", 3);
			ChangeCharacterNationReputation(pchar, SPAIN, 10);
			AddCharacterExpToSkill(pchar, "Leadership", 500);
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}



