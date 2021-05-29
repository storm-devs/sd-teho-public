// полковник Фокс - бравый командир морской пехоты 'морские лисы'.
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (CheckAttribute(pchar, "questTemp.Terrapin_KathyReward"))
			{
				dialog.text = "Что вы хотели, сударь? Хм... Постойте! Кажется, я понимаю: вы тот самый французский капитан, который вытащил мою дочь из лап прихвостней проклятого мерзавца Левассера!";
				link.l1 = "Вижу, Кэтрин уже всё рассказала обо мне...";
				link.l1.go = "terrapin";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.Guardoftruth.Usurer") && !CheckAttribute(npchar, "quest.utensil"))
			{
				dialog.text = "Что вы хотели, сударь?";
				link.l1 = "Добрый день, полковник. Я к вам по несколько необычному делу. Уделите пару минут?";
				link.l1.go = "guardoftruth";
				break;
			}
			// Addon-2016 Jason, французские миниквесты (ФМК) Сент-Кристофер
			if (CheckAttribute(pchar, "questTemp.FMQN") && pchar.questTemp.FMQN == "eng_reward")
			{
				dialog.text = "Как я понимаю, вы - тот самый французский капитан, который помог моим людям выполнить задание на Синт-Маартене? "+TimeGreeting()+"!";
				link.l1 = TimeGreeting()+", полковник. Да, это именно я.";
				link.l1.go = "FMQN";
				break;
			}
			dialog.text = "Что вам угодно, сударь?";
			link.l1 = "Ничего. Я уже ухожу.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		case "guardoftruth":
			dialog.text = "Выкладывайте, что у вас там, раз уж пришли...";
			link.l1 = "Недавно вы захватили шхуну голландского пирата, Ролли Колпака, и доставили капитана в Сент-Джонс...";
			link.l1.go = "guardoftruth_1";
		break;
		
		case "guardoftruth_1":
			dialog.text = "Капитана? О нет! Главарь преступного отребья не может называться этим почётным званием. Я захватил проклятого пирата, вожака волчьей стаи, грабившей и убивавшей английских торговцев. И воздал мерзавцу и его выродкам по заслугам - весь Сент-Джонс наблюдал за тем, как их вздёрнули на пирсе!";
			link.l1 = "Ясно. Значит, побеседовать с этим прохвостом мне не удастся... Полковник, быть может, вы сможете мне помочь? У этого пирата была вещь, которая ему не принадлежала: золотое кадило. Вы не находили его при обыске?";
			link.l1.go = "guardoftruth_2";
		break;
		
		case "guardoftruth_2":
			dialog.text = "У этого скота не было ни одной вещи, принадлежавшей ему. Все они были отняты у добропорядочных негоциантов! Но касательно вашего вопроса: нет, не находили. И что могло делать кадило на пиратской посудине? Неужели вы считаете, что в команде был капеллан?";
			link.l1 = "Я так не считаю. Ролли Колпак купил это кадило у ростовщика в Виллемстаде, которое тому, в свою очередь, продал другой пират. Вещь красивая, дорогая. Думаю, Ролли просто позарился на неё, как сорока на блестящее...";
			link.l1.go = "guardoftruth_3";
		break;
		
		case "guardoftruth_3":
			dialog.text = "На самом деле, когда мы захватили шхуну Ролли у берегов Доминики, у него были пустые трюмы, а в сундуках - мешочек с песо да горсть дублонов. И всякий хлам. Никаких ценностей, и уж тем более золотого кадила. Я бы сразу обратил внимание на столь неподходящую пирату вещь\nУ меня есть предположение, что проклятый Колпак спрятал свои сбережения где-то на Доминике. Мы даже высадились на берег и провели рейд по окрестностям, но ничего не нашли. Задерживаться на острове, а также отправляться вглубь мы не стали - там полно дикарей.";
			link.l1 = "Хм. Значит, Колпак мог схоронить кадило вместе с прочим награбленным где-то на Доминике... Печально. Вы не допрашивали пирата перед казнью?";
			link.l1.go = "guardoftruth_4";
		break;
		
		case "guardoftruth_4":
			dialog.text = "Допрашивал, но он только смеялся мне в лицо. Однако меня, честно говоря, его схроны не интересуют. Ролли Колпак вздёрнут на виселице - и это главное.";
			link.l1 = "Понятно. Спасибо за рассказ и за то, что уделили время! До свидания...";
			link.l1.go = "guardoftruth_5";
		break;
		
		case "guardoftruth_5":
			DialogExit();
			npchar.quest.utensil = "true";
			AddQuestRecord("Guardoftruth", "24");
			Island_SetReloadEnableGlobal("Dominica", true);//patch-7
			// заполняем сундук
			pchar.GenQuestBox.Shore27 = true;
			pchar.GenQuestBox.Shore27.box1.money = 30000;
			pchar.GenQuestBox.Shore27.box1.items.gold_dublon = 100;
			pchar.GenQuestBox.Shore27.box1.items.chest = 1;
			pchar.GenQuestBox.Shore27.box1.items.icollection = 1;
			pchar.GenQuestBox.Shore27.box1.items.jewelry40 = 15;
			pchar.GenQuestBox.Shore27.box1.items.jewelry41 = 22;
			pchar.GenQuestBox.Shore27.box1.items.jewelry42 = 8;
			pchar.GenQuestBox.Shore27.box1.items.jewelry43 = 20;
			pchar.GenQuestBox.Shore27.box1.items.jewelry44 = 33;
			pchar.GenQuestBox.Shore27.box1.items.jewelry45 = 16;
			pchar.GenQuestBox.Shore27.box1.items.jewelry46 = 58;
			pchar.GenQuestBox.Shore27.box1.items.jewelry35 = 1; // кадило
			pchar.quest.GuardOT_finddominicachest.win_condition.l1 = "item";
			pchar.quest.GuardOT_finddominicachest.win_condition.l1.item = "jewelry35";
			pchar.quest.GuardOT_finddominicachest.function = "GuardOT_DominicaChest";
		break;
		
		case "terrapin":
			dialog.text = "И не один раз, капитан! Вы совершили поступок, который трудно было ожидать от француза. Я действительно вам крайне признателен, и как солдат, и как отец. Дороже дочери для меня нет ничего на свете...";
			link.l1 = "Я рад, что всё закончилось хорошо. Надеюсь, вы теперь измените своё мнение о французах.";
			link.l1.go = "terrapin_1";
		break;
		
		case "terrapin_1":
			dialog.text = "Одно то, что среди них есть такой благородный джентльмен, как вы, рискнувший жизнью ради спасения совершенно незнакомой вам английской девушки, и не искавший корыстных целей в этом, вызовет существенное потепление в моём отношении к вашим соотечественникам!";
			link.l1 = "Хорошие люди, как и мерзавцы, есть среди любой нации, полковник...";
			link.l1.go = "terrapin_2";
		break;
		
		case "terrapin_2":
			dialog.text = "И вы это доказали! Вас ждёт награда, капитан. Безусловно, жизнь моей дочери - бесценна, но Джонатан Фокс никогда не остаётся в долгу, клянусь честью! Вы настоящий солдат, поэтому и подарок у меня для вас что ни на есть солдатский. Вот, посмотрите\nЭто бландербуз, великолепный флотский мушкетон, пригодный для стрельбы одной рукой. Его можно заряжать специальными стрелами, которые гарантированно пробьют даже самую прочную кирасу. Также он стреляет картечью, а крепкая конструкция позволяет использовать также и жеребья. Держите, он ваш.";
			link.l1 = "Действительно, отличный подарок для солдата!";
			link.l1.go = "terrapin_3";
		break;
		
		case "terrapin_3":
			Log_Info("Вы получили бландербуз");
			Log_Info("Вы получили 10 стрел");
			Log_Info("Вы получили 10 ежовых зарядов");
			Log_Info("Вы получили инструкцию по изготовлению гарпунной стрелы");
			Log_Info("Вы получили инструкцию по изготовлению ежового заряда");
			GiveItem2Character(pchar, "pistol8");
			TakeNItems(pchar, "harpoon", 10);
			TakeNItems(pchar, "GunEchin", 10);
			GiveItem2Character(pchar, "recipe_harpoon"); 
			GiveItem2Character(pchar, "recipe_GunEchin"); 
			PlaySound("interface\important_item.wav");
			dialog.text = "Также к нему я прилагаю небольшой комплект боеприпасов и инстукции по изготовлению зарядов к нему. Негоже, чтобы вы не смогли реализовать его мощь на полную катушку!";
			link.l1 = "Спасибо, полковник. От такого презента я не откажусь, ни в коем случае, но хочу, чтобы вы знали: я вытаскивал Кэтрин из рук захвативших её негодяев не рассчитывая ни на какие выгоды. Я просто не мог оставить беззащитную девушку на растерзание этим ублюдкам.";
			link.l1.go = "terrapin_4";
		break;
		
		case "terrapin_4":
			dialog.text = "Я знаю, капитан. И это делает вам честь вдвойне. Кэтти была просто восхищена вами, а на неё не так-то просто произвести благоприятное впечатление. Ещё раз примите благодарности от неё и от меня за её вызволение.";
			link.l1 = "И вам спасибо за ваш подарок, полковник. Передайте Кэтрин мой поклон и пожелание впредь всегда строго слушаться своего отца.";
			link.l1.go = "terrapin_5";
		break;
		
		case "terrapin_5":
			dialog.text = "Обязательно передам, капитан! Всего доброго!";
			link.l1 = "До свидания, полковник.";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.Terrapin_KathyReward");
			ChangeCharacterComplexReputation(pchar, "nobility", 5);
			ChangeCharacterComplexReputation(pchar, "fame", 5);
			ChangeCharacterNationReputation(pchar, ENGLAND, 20);
		break;
		
		// Addon-2016 Jason, французские миниквесты (ФМК) Сент-Кристофер
		case "FMQN":
			dialog.text = "Я прочитал доклад. Ваши действия оценены весьма высоко, и вы должны получить награду. Таким образом, вам полагается тридцать тысяч песо наличными за экспедиционные услуги, и хорошее оружие - за проявленный солдатский героизм. Вот этот клинок и аркебуза теперь ваши. Получите!";
			link.l1 = "Спасибо, сэр.";
			link.l1.go = "FMQN_1";
		break;
		
		case "FMQN_1":
			dialog.text = "Само собой, попутной наградой вам явится почёт и уважение английских колонистов, властей и моё лично. Выражаю вам свою благодарность за то, что не бросили моих людей и помогли им!";
			link.l1 = "Всегда рад, полковник...";
			link.l1.go = "FMQN_2";
		break;
		
		case "FMQN_2":
			dialog.text = "А теперь прошу меня простить - дела ждут. Попутного ветра, капитан.";
			link.l1 = "До свидания, сэр.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("FMQN_EnglandComplete");
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}