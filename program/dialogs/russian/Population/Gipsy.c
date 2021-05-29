//Jason общий диалог цыганок
// ugeen <-- добавил продажу мышьяка из под полы
#include "DIALOGS\russian\Rumours\Common_rumours.c"
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;
	string sTemp;
	int poison_price;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	// вызов диалога по городам -->
    NPChar.FileDialog2 = "DIALOGS\" + LanguageGetLanguage() + "\Citizen\" + NPChar.City + "_Citizen.c";
    if (LoadSegment(NPChar.FileDialog2))
	{
        ProcessCommonDialog(NPChar, Link, NextDiag);
		UnloadSegment(NPChar.FileDialog2);
	}
    // вызов диалога по городам <--
	
	ProcessCommonDialogRumors(NPChar, Link, NextDiag);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "А-а, это опять ты, милок? Что ты хотел?";
			link.l1 = "Да нет, пожалуй, ничего.";
			link.l1.go = "exit";
			link.l2 = RandPhraseSimple("У меня есть вопрос к тебе.", "Мне нужна информация.");
			link.l2.go = "quests";//(перессылка в файл города)
			
			if (npchar.quest.meeting == "0")
			{
				dialog.text = LinkRandPhrase("Милок, позолоти ручку. Всю правду тебе расскажу.","Эй, морячок, не спеши! Хочешь узнать всю правду?","Угости табачком, соколик, и парой серебряных монет, а я загляну в твое будущее.");
				link.l1 = "Извини, мне пора идти.";
				link.l1.go = "exit";
				// --> мангароса
				if (CheckCharacterItem(pchar, "cannabis7") && CheckAttribute(pchar, "questTemp.Mangarosa") && pchar.questTemp.Mangarosa == "gipsy" && !CheckAttribute(npchar, "quest.mangarosa"))
				{
					link.l5 = "Послушай, любезная, я знаю, что вы - знатоки различных зелий. Мне тут шепнули на ушко, что вас здорово интересует вот эта травка. Посмотри.";
					link.l5.go = "mangarosa";
				}
				if (CheckCharacterItem(pchar, "cannabis7") && CheckAttribute(pchar, "questTemp.Mangarosa") && pchar.questTemp.Mangarosa == "gipsy_trade" && !CheckAttribute(npchar, "quest.mangarosa"))
				{
					link.l5 = "Чернобровая, у меня для тебя кое-что есть... Это мангароса. Будешь покупать?";
					link.l5.go = "mangarosa_trade1";
				}
				// <-- мангароса
				link.l2 = "Ты можешь мне погадать?";
				link.l2.go = "guess";
				link.l3 = RandPhraseSimple("У меня есть вопрос к тебе.", "Мне нужна информация.");
				link.l3.go = "quests";//(перессылка в файл города)
				npchar.quest.meeting = "1";
			}
			if (!CheckAttribute(npchar, "quest.poison_price") && !CheckAttribute(pchar, "questTemp.Sharlie.Lock") && rand(2) == 0)
			{
				link.l4 = "А что, чернобровая, не найдется ли у тебя отравы какой для крыс? Совсем от них житья не стало!";
				link.l4.go = "get_poison_1";
			}
			NextDiag.TempNode = "First time";
		break;

//-------------------------------------------------гадание-------------------------------------------------
		case "guess":
			dialog.text = "Конечно, милок. Дай несколько монет и покажи свою правую ладонь - поведаю о том, что ждет тебя впереди, без обману!";
			link.l1 = "Пожалуй, я передумал. Неохота что-то...";
			link.l1.go = "exit";
			link.l2 = "Сколько денег ты просишь?";
			link.l2.go = "guess_1";
		break;
		
		case "guess_1":
			dialog.text = "А, милок, это сколько позволит тебе твой кошель и твое желание.";
			link.l1 = "100 песо.";
			link.l1.go = "guess_rate_1";
			link.l2 = "500 песо.";
			link.l2.go = "guess_rate_2";
			link.l3 = "1000 песо.";
			link.l3.go = "guess_rate_3";
			link.l4 = "5000 песо.";
			link.l4.go = "guess_rate_4";
		break;
		
		sTemp = GuessText();
		case "guess_rate_1"://никаких плюшек
			if (sti(pchar.money) >= 100)
			{
				AddMoneyToCharacter(pchar, -100);
				dialog.text = "Ай, спасибо за эти несколько монет, соколик! Теперь слушай: "+sTemp+"";
				link.l1 = LinkRandPhrase("Хех! Это очень занятно! Учту...","Вот как? Приму к сведению...","Да ну? Ты серьезно? Ну что же, запомню...");
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = "Беда, злая и неминучая, ждет тебя. Горе, горе насмешнику! Сгустятся черные тучи над тобой и поразит тебя кара неизбежная!";
				link.l1 = "Ха-ха! Ты что, ведьма, думала, я денег тебе дам? Проваливай, покуда цела!";
				link.l1.go = "guess_exit";
			}
		break;
		
		case "guess_rate_2"://немного в везение или скрытность
			if (sti(pchar.money) >= 500)
			{
				AddMoneyToCharacter(pchar, -500);
				dialog.text = "Ай, спасибо, соколик! Теперь слушай: "+sTemp+"";
				link.l1 = LinkRandPhrase("Хех! Это очень занятно! Учту...","Вот как? Приму к сведению...","Да ну? Ты серьезно? Ну что же, запомню...");
				link.l1.go = "exit";
				if (drand(1) == 0) AddCharacterExpToSkill(pchar, "Fortune", 30+rand(10));//везение
				else AddCharacterExpToSkill(pchar, "Sneak", 30+rand(10));//скрытность
			}
			else
			{
				dialog.text = "Беда, злая и неминучая, ждет тебя. Горе, горе насмешнику! Сгустятся черные тучи над тобой и поразит тебя кара неизбежная!";
				link.l1 = "Ха-ха! Ты что, ведьма, думала, я денег тебе дам? Проваливай, покуда цела!";
				link.l1.go = "guess_exit";
			}
		break;
		
		case "guess_rate_3"://здоровье + везение или скрытность, харизма
			if (sti(pchar.money) >= 1000)
			{
				AddMoneyToCharacter(pchar, -1000);
				dialog.text = "Ай, спасибо за серебро, соколик! Теперь слушай: "+sTemp+"";
				link.l1 = LinkRandPhrase("Хех! Это очень занятно! Учту...","Вот как? Приму к сведению...","Да ну? Ты серьезно? Ну что же, запомню...");
				link.l1.go = "exit";
				AddCharacterHealth(pchar, 1);
				AddCharacterExpToSkill(pchar, "Leadership", 20);
				if (drand(1) == 0) AddCharacterExpToSkill(pchar, "Fortune", 50+rand(20));//везение
				else AddCharacterExpToSkill(pchar, "Sneak", 50+rand(20));//скрытность
			}
			else
			{
				dialog.text = "Беда, злая и неминучая, ждет тебя. Горе, горе насмешнику! Сгустятся черные тучи над тобой и поразит тебя кара неизбежная!";
				link.l1 = "Ха-ха! Ты что, ведьма, думала, я денег тебе дам? Проваливай, покуда цела!";
				link.l1.go = "guess_exit";
			}
		break;
		
		case "guess_rate_4"://умения в оружие, везение+скрытность, здоровье, харизма
			if (sti(pchar.money) >= 5000)
			{
				AddMoneyToCharacter(pchar, -5000);
				dialog.text = "Ай, спасибо за твою щедрость, соколик! Теперь слушай: "+sTemp+"";
				link.l1 = LinkRandPhrase("Хех! Это очень занятно! Учту...","Вот как? Приму к сведению...","Да ну? Ты серьезно? Ну что же, запомню...");
				link.l1.go = "exit";
				AddCharacterHealth(pchar, 2);
				AddCharacterExpToSkill(pchar, "Leadership", 40);
				AddCharacterExpToSkill(pchar, "Fortune", 50+rand(100));//везение
				AddCharacterExpToSkill(pchar, "Sneak", 50+rand(50));//скрытность
				AddComplexSelfExpToScill(20, 20, 20, 20);
			}
			else
			{
				dialog.text = "Беда, злая и неминучая, ждет тебя. Горе, горе насмешнику! Сгустятся черные тучи над тобой и поразит тебя кара неизбежная!";
				link.l1 = "Ха-ха! Ты что, ведьма, думала, я денег тебе дам? Проваливай, покуда цела!";
				link.l1.go = "guess_exit";
			}
		break;
		
		case "guess_exit":
			DialogExit();
			AddCharacterHealth(pchar, -10);
			LAi_CharacterDisableDialog(npchar);
		break;
//<-- гадание

// --> продажа мышьяка
		case "get_poison_1" :
			npchar.quest.poison_price = (drand(3) + 1) * 10;
			if(drand(10) == 3)
			{				
				dialog.text = LinkRandPhrase("Ой не знаю, красавец! Давеча один вот тоже просил крыс примучить, а потом кто-то солдат в форте потравил. Нас две недели на допрос таскали. Чуть из города не погнали, пока не нашли того душегуба. Лазутчиком вражеским оказался.",
				                             "А откуда мне знать, кого ты травить собрался? Может знатного соперника, с которым боишься на клинках сойтись в честном поединке? ",
											 "Сказывали мне, что в прошлом месяце кто-то отравил в таверне заезжего купца и обобрал до нитки. А купец тот еще долго мучился пока представился, весь пеной изошел и синий стал, как баклажан. Не твоих ли рук дело, яхонтовый мой?");
				link.l1 = "Вот значит, как ты обо мне подумала! Не волнуйся, людей травить не в моих привычках. Для людей у меня другие средства имеются, а вот против крыс ничего не помогает.";
				link.l1.go = "get_poison_2";
			}
			else
			{
				dialog.text = "Ишь, чего удумал! Нет у меня никакой отравы! Травы есть, отвары есть, а отравы нет.";
				link.l1 = "Ну да ладно..";
				link.l1.go = "exit";
			}	
		break;
		
		case "get_poison_2" :
			dialog.text = "Ну ладно, выручу я тебя. Только не говори никому, что это я тебе отраву продала. С тебя "+sti(npchar.quest.poison_price)+" дублонов.";
			if (GetCharacterItem(pchar, "gold_dublon") >= sti(npchar.quest.poison_price)) 
			{				
				link.l1 = "Дороговато, конечно... Ну да ладно, лишь бы помогло.";
				link.l1.go = "get_poison_4";
			}
			else
			{
				link.l1 = "Да ты что! Прошлый раз за пять золотых брал! Да за такие деньги я этих крыс сам руками переловлю!";
				link.l1.go = "get_poison_3";
			}
		break;
		
		case "get_poison_3" :
			dialog.text = "Вот и лови, а ко мне больше не лезь со всякими глупостями. В следующий раз позову солдат.";
			link.l1 = "Не нужно солдат, пойду я.";
			link.l1.go = "exit";
		break;
		
		case "get_poison_4" :
			PlaySound("interface\important_item.wav");
			RemoveItems(pchar, "gold_dublon", sti(npchar.quest.poison_price));
			TakeNItems(pchar, "rat_poison", 1);
			DialogExit();
		break;
// <-- продажа мышьяка

	// --> Мангароса
		case "mangarosa":
			dialog.text = LinkRandPhrase("Показывай, соколик, что там у тебя за травка... Хм... пожалуй, я куплю ее у тебя. Три сотни песо тебя устроит?","Покажи мне ее, дружок... Хе... ну, две с половиной сотни я тебе за нее, пожалуй, заплачу.","Давай посмотрим... О! Интересный экземпляр! Две сотни серебряных монет! По рукам?")"";
			link.l1 = LinkRandPhrase("Начинается... Чернобровая, я не какой-нибудь деревенский простачок. Я знаю, что это за травка. Это - мангароса...","Да что ты такое говоришь! Это же мангароса, причем отличный экземпляр. Не пытайся водить меня за нос.","Ага, вот прямо сейчас взял и отдал тебе мангаросу за эти гроши...");
			link.l1.go = "mangarosa_1";
		break;
		
		case "mangarosa_1":
			dialog.text = "Хорошо-хорошо, красавчик. Вижу, что тебе известно кое-что об этом растении. Пятьдесят дублонов. Давай ее сюда.";
			link.l1 = "Ох, да погоди ты! Я хочу узнать, где она применяется, что из нее можно приготовить. Ты можешь поведать мне это? Ведь недаром же вы готовы отваливать золото горстями за этот зеленый куст!";
			link.l1.go = "mangarosa_2";
		break;
		
		case "mangarosa_2":
			// тут работает харизма
			if (sti(pchar.questTemp.Mangarosa.g_count) == 5 || GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) > 10+drand(25)+drand(30))
			{
				dialog.text = "Хм... Ну, пожалуй, никакого страху не будет, если я тебе расскажу немного о ней. Все равно без специальных знаний у тебя ничего путного не выйдет.";
				link.l1 = "Я весь внимание!";
				link.l1.go = "mangarosa_3";
			}
			else
			{
				dialog.text = LinkRandPhrase("Золото, может, и готовы отваливать, а вот раскрывать свои тайны - не намерены. ","Золото - золотом, а секреты - секретами, соколик... ","Платить мы, конечно, готовы, а вот трепать языком почем зря - не станем. ")+"Ты будешь продавать мне свою мангаросу? Пятьдесят дублонов - это наша такса за нее, больше тебе никто не даст.";
				link.l1 = "Ох, ладно... Да, буду. Пятьдесят дублонов меня устраивает. Держи.";
				link.l1.go = "mangarosa_trade";
				link.l2 = "Пойми, я не хочу продавать ее. Я хочу узнать, почему она вам так нужна. Поделись знаниями, а я отдам тебе этот стебель бесплатно.";
				link.l2.go = "mangarosa_exit";
			}
		break;
		
		case "mangarosa_trade":
			RemoveItems(pchar, "cannabis7", 1);
			TakeNItems(pchar, "gold_dublon", 50);
			PlaySound("interface\important_item.wav");
			dialog.text = "Получи свои монеты, соколик. Если найдешь еще мангаросы - приноси нам. Правда, покупаем мы только по одному стеблю - большие суммы в дублонах с собой не носим. Уж больно любит к нам цепляться городская стража.";
			link.l1 = "Хорошо. Если встречу еще - обязательно принесу.";
			link.l1.go = "mangarosa_trade_exit";
		break;
		
		case "mangarosa_trade_exit":
			DialogExit();
			npchar.quest.mangarosa = "true";
			DeleteAttribute(pchar, "questTemp.Mangarosa.g_count");
			pchar.questTemp.Mangarosa = "gipsy_trade";
			AddQuestRecord("Mangarosa", "3");
		break;
		
		case "mangarosa_exit":
			dialog.text = LinkRandPhrase("Ишь, чего захотел! Не хочешь продавать - и не надо, а рассказывать тебе я ничего не буду.","Я не стану выдавать наши секреты посторонним. Не будешь продавать - и черт с тобой.","Дружок, это не для твоих ушей. Не хочешь продавать за полсотни дублонов - иди, продай лоточнице за пару сотен песо.");
			link.l1 = LinkRandPhrase("Ну и напрасно! Расскажет кто-нибудь другой из ваших. Он и получит мангаросу в подарок. Бывай!","Что за упрямство? Не расскажешь ты - расскажет другая. Ей я и подарю мангаросу. Прощай.","Что ты так ерепенишься? Я ведь все равно своего добьюсь. Кто-нибудь из ваших окажется сговорчивей и получит эту мангаросу бесплатно. Пока!");
			link.l1.go = "exit";
			npchar.quest.mangarosa = "true";
			pchar.questTemp.Mangarosa.g_count = sti(pchar.questTemp.Mangarosa.g_count)+1;
		break;
		
		case "mangarosa_trade1":
			dialog.text = "Спрашиваешь, соколик! Конечно! Давай ее мне.";
			link.l1 = "Давай пятьдесят дублонов.";
			link.l1.go = "mangarosa_trade1_1";
			link.l2 = "Ой! Кажется, я ее или потерял, или забыл на корабле. Какая досада! Извини...";
			link.l2.go = "exit";
			npchar.quest.mangarosa = "true";
		break;
		
		case "mangarosa_trade1_1":
			RemoveItems(pchar, "cannabis7", 1);
			TakeNItems(pchar, "gold_dublon", 50);
			PlaySound("interface\important_item.wav");
			dialog.text = "Не бойся, не обману. Получай свои монеты.";
			link.l1 = "Забирай свою мангаросу. Найду еще - принесу!";
			link.l1.go = "exit";
		break;
		
		case "mangarosa_3":
			dialog.text = "Мы измельчаем это растение особым способом, потом высушиваем, соблюдая определенные условия, а затем смешиваем с табаком в некотором соотношении, набиваем свои трубки и курим. Получаем от этого... незабываемый эффект. Одного стебля хватает на два десятка трубок.";
			link.l1 = "Вот как! А ты можешь научить меня этому? Я хорошо заплачу...";
			link.l1.go = "mangarosa_4";
		break;
		
		case "mangarosa_4":
			dialog.text = "Соколик, поверь - не стоит оно того. Не ввязывайся в это дело, сгубит оно тебя. Даже и не проси. Однако... смотрю я на тебя - бравый парень, с саблей, моряк... может, даже капитан?";
			link.l1 = "Ты не ошиблась.";
			link.l1.go = "mangarosa_5";
		break;
		
		case "mangarosa_5":
			dialog.text = "Тогда слушай сюда. Мангаросу можно использовать и для других целей, куда более благородных, и это может очень тебе пригодиться. Секреты этого растения досконально изучила одна наша знахарка. Вот она-то тебе и нужна\nЕсли ты отдашь мне свою мангаросу - я скажу тебе, как ее зовут и где искать. А там уже уговаривай ее сам, чтобы она с тобой поделилась рецептами своих зелий.";
			link.l1 = "Хорошо. Бери растение и рассказывай, как найти твою знахарку.";
			link.l1.go = "mangarosa_6";
		break;
		
		case "mangarosa_6":
			RemoveItems(pchar, "cannabis7", 1);
			PlaySound("interface\important_item.wav");
			dialog.text = "Зовут ее Амелия. Живет она уединенно, в домике в дюнах недалеко от моря, где-то на юго-западе Мэйна, как говорят ученые люди.";
			link.l1 = "Хм. А поточнее не можешь сказать, где ее дом?";
			link.l1.go = "mangarosa_7";
		break;
		
		case "mangarosa_7":
			dialog.text = "Ну ты же моряк, соколик, а я нет. Поищи хорошенько там, где я сказала. Ее дом совсем близко от берега. Там еще рядом есть какая-то бухта - моряки должны ее знать.";
			link.l1 = "Ладно, найду как-нибудь...";
			link.l1.go = "mangarosa_8";
		break;
		
		case "mangarosa_8":
			dialog.text = "Когда отправишься к ней - обязательно имей при себе мангаросу, иначе она даже не станет с тобой разговаривать, да и дублонов прихвати побольше - не думаешь же ты, что она будет учить тебя бесплатно!";
			link.l1 = "Я учту это. Спасибо за рассказ!";
			link.l1.go = "mangarosa_9";
		break;
		
		case "mangarosa_9":
			DialogExit();
			npchar.quest.mangarosa = "true";
			DeleteAttribute(pchar, "questTemp.Mangarosa.g_count");
			pchar.questTemp.Mangarosa = "amelia";
			pchar.questTemp.Mangarosa.Tell = "true"; // калеуче
			AddQuestRecord("Mangarosa", "4");
			// создаем и ставим Амелию
			sld = GetCharacter(NPC_GenerateCharacter("Amelia", "gipsy_3", "woman", "towngirl", 10, PIRATE, -1, true, "citizen"));
			SetFantomParamFromRank(sld, 10, true);
			sld.name = "Амелия";
			sld.lastname = "";
			sld.dialog.FileName = "Quest\Mangarosa.c";
			sld.dialog.currentnode = "amelia";
			//sld.greeting = "";
			LAi_SetOwnerType(sld);
			LAi_SetImmortal(sld, true);
			ChangeCharacterAddressGroup(sld, "Amelia_house", "barmen", "stay");
		break;
		
		//замечание по обнаженному оружию от персонажей типа citizen
		case "CitizenNotBlade":
			dialog.text = NPCharSexPhrase(NPChar, "Послушайте, я, как гражданин этого города, прошу вас не ходить у нас с обнаженным клинком.", "Знаете, я, как гражданка этого города, прошу вас не ходить у нас с обнаженным клинком.");
			link.l1 = LinkRandPhrase("Хорошо.", "Ладно.", "Как скажете...");
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}

string GuessText()
{
	string sText;
	switch (drand(19))
	{
		case 0: sText = "повезёт тебе соколик, завтра непременно в карты повезёт!" break;
		case 1: sText = "в загаданном деле тебя ожидает удача, капитан!" break;
		case 2: sText = "в открытом море неудача таится, именно тебя ждёт, подожди три дня!" break;
		case 3: sText = "вижу, необходимо тебе искать помощи близких людей, один в следующем бою не выжевешь!" break;
		case 4: sText = "сходи, поставь свечку в церкви, проклял тебя недруг. Без божьей помощи не справишься!" break;
		case 5: sText = "потеряешь вскоре многое, но все-таки отчаиваться не надо – надейся на собственные силы, ищи помощи друзей..." break;
		case 6: sText = "потеря тебя ожидает, в море, но вижу я - сумеете, капитан, если и не добиться желаемого, то возместить потраченные силы и средства при других обстоятельствах." break;
		case 7: sText = "ты вступил в полосу неудач, капитан! Сходи в бордель, развейся." break;
		case 8: sText = "твоё желание хоть и будет исполнено, однако же ничего хорошего ждать от этого не придется: то, чего ты так страстно хотел, кэп, принесет одни неприятности, и лучше отказаться от задуманного." break;
		case 9: sText = "вижу на челе твоём отблеск абсолютной удачи: сбудется даже больше того, на что рассчитывал, соколик!" break;
		case 10: sText = "тебе необходимо заново оценить свое желание и решить, необходимо ли его исполнение: судьба дает шанс подумать." break;
		case 11: sText = "это редкое везение – не так часто у нас есть шанс передумать. Просто отдохни денёк, ясноглазый, подумай о бренном. Не спеши на смерть!" break;
		case 12: sText = "хотя все затраченные вами усилия и не принесут ожидаемого результата, отчаиваться не стоит – в самый неожиданный момент тебя ждет удача, не пропусти её!" break;
		case 13: sText = "твой конкретный вопрос не будет решен положительно, но ты упрям, все равно получишь свое, но, может быть, вовсе не оттуда, откуда ожидал." break;
		case 14: sText = "лучше забудь о том деле, которым занят – удачи тебе в нем никогда не будет, а если продолжишь настаивать, то, возможно, пострадают или даже погибнут твои спутники." break;
		case 15: sText = "впереди тебя ожидает событие, капитан, которое настолько круто переменит твою жизнь, что всё сейчас происходящее не будет иметь никакого значения!" break;
		case 16: sText = "на пути к исполнению твоего желания тебя подстерегает опасность, и тебе очень повезет, если сумеешь добиться того, чего хотел, ничего не потеряв, капитан. Лучше, пока не поздно, свернуть с пути и забыть мечту недостижимую. Хотя, если прямо сейчас в кости или карты проиграть, то судьбу можно обмануть..." break;
		case 17: sText = "вижу силу в тебе могучую, как скала, и свет яркий, как звезды, что людей за собой поведет. Хороший знак и добрая весть тебя ждут." break;
		case 18: sText = "знак недобрый на твоем пути встанет, опасайся дурного глаза, и держи поближе верных людей." break;
		case 19: sText = "счастливый случай дожидается тебя чуть не за спиной. Ищи то, что само идет в руки, и не гонись за несбыточным." break;
	}
	return sText;
}
