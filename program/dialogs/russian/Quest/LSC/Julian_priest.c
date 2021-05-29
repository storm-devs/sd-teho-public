// брат Юлиан - священник
#include "DIALOGS\russian\Rumours\Common_rumours.c"
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int iTemp;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	ProcessCommonDialogRumors(NPChar, Link, NextDiag);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (CheckAttribute(pchar, "GenQuest.CitizenConflict") && sti(pchar.GenQuest.CitizenConflict) > 3)
			{
				dialog.text = "Я не желаю с тобой общаться. Ты нападаешь без причины на мирных граждан, провоцируешь их на драку. Уходи прочь, безбожник!";
				link.l1 = "Гм...";
				link.l1.go = "exit";
				break;
			}
			if (pchar.questTemp.LSC == "return" && !CheckAttribute(npchar, "quest.return_isl"))
			{
				dialog.text = "Ты думаешь, почему меня не удивляет твое чудесное спасение? Неисповедимы пути Господни, и его промысел нам неведом. Жизнь и смерть - все в Его руках.";
				link.l1 = "Я совершенно с вами согласен, брат Юлиан.";
				link.l1.go = "exit";
				npchar.quest.return_isl = "true";
				break;
			}
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "Добро пожаловать в святую обитель нашего Острова, сын мой. Если ты желаешь помолиться или посетить службу - двери церкви открыты для тебя. Я, брат Юлиан, рад каждому, кто приходит сюда для того, чтобы обратить свой взор к Господу нашему.";
				link.l1 = TimeGreeting()+". Меня зовут "+GetFullName(pchar)+". Приятно познакомиться, брат Юлиан.";
				link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "А, "+GetFullName(pchar)+"! "+TimeGreeting()+"! Ты что-то хотел?";
				link.l1 = "Я хочу задать вам пару вопросов об острове.";
				link.l1.go = "int_quests"; //информационный блок
				link.l2 = "Могу ли я приобрести у вас лечебные зелья?";
				link.l2.go = "potion";
				link.l3 = "У вас нет на продажу освященных предметов, брат Юлиан?";
				link.l3.go = "amulet";
				link.l5 = "Просто зашел прочесть молитву и узнать, как у вас дела. Еще увидимся!";
				link.l5.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting": // первая встреча
			dialog.text = "Надеюсь, ты станешь посещать нашу церковь хотя бы изредка. Не забывай о душе, сын мой. Также я могу облегчить не только твои духовные, но и телесные страдания - на нашем острове я выполняю роль не только пастыря, но и лекаря.";
			link.l1 = "Я хочу задать вам пару вопросов об острове.";
			link.l1.go = "int_quests"; //информационный блок
			link.l2 = "Могу ли я приобрести у вас какие-нибудь лечебные зелья?";
			link.l2.go = "potion";
			link.l3 = "У вас нет на продажу освященных предметов, брат Юлиан?";
			link.l3.go = "amulet";
			link.l4 = "Мне пора, брат Юлиан. Еще увидимся!";
			link.l4.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
		case "potion":
			dialog.text = "Конечно, сын мой. Какое зелье ты желаешь приобрести?";
			if (!CheckAttribute(npchar, "potion1_date") || GetNpcQuestPastDayParam(npchar, "potion1_date") >= 1)
			{
				link.l1 = "Простую лечебную эссенцию.";
				link.l1.go = "potion1";
			}
			if (!CheckAttribute(npchar, "potion2_date") || GetNpcQuestPastDayParam(npchar, "potion2_date") >= 1)
			{
				link.l2 = "Целебный эликсир.";
				link.l2.go = "potion2";
			}
			if (!CheckAttribute(npchar, "potion3_date") || GetNpcQuestPastDayParam(npchar, "potion3_date") >= 1)
			{
				link.l3 = "Противоядие.";
				link.l3.go = "potion3";
			}
			if (!CheckAttribute(npchar, "potion4_date") || GetNpcQuestPastDayParam(npchar, "potion4_date") >= 1)
			{
				link.l4 = "Травяную микстуру.";
				link.l4.go = "potion4";
			}
			link.l5 = "Извините, брат Юлиан, я передумал.";
			link.l5.go = "exit";
		break;
		
		case "potion1":
			npchar.quest.price = 90;
			npchar.quest.type = 1;
			dialog.text = "Лечебную эссенцию? С тебя 90 песо, сын мой.";
			if (sti(Pchar.money) >= 90)
			{
				link.l1 = "Пожалуйста, брат Юлиан. Вот деньги.";
				link.l1.go = "potion_pay";
			}
			else
			{
				link.l1 = "К сожалению, у меня недостаточно средств... Я вернусь позже.";
				link.l1.go = "exit";
			}
		break;
		
		case "potion2":
			npchar.quest.price = 500;
			npchar.quest.type = 2;
			dialog.text = "Целебный эликсир? С тебя 500 песо, сын мой.";
			if (sti(Pchar.money) >= 500)
			{
				link.l1 = "Пожалуйста, брат Юлиан. Вот деньги.";
				link.l1.go = "potion_pay";
			}
			else
			{
				link.l1 = "К сожалению, у меня недостаточно средств... Я вернусь позже.";
				link.l1.go = "exit";
			}
		break;
		
		case "potion3":
			npchar.quest.price = 200;
			npchar.quest.type = 3;
			dialog.text = "Противоядие? С тебя 200 песо, сын мой.";
			if (sti(Pchar.money) >= 200)
			{
				link.l1 = "Пожалуйста, брат Юлиан. Вот деньги.";
				link.l1.go = "potion_pay";
			}
			else
			{
				link.l1 = "К сожалению, у меня недостаточно средств... Я вернусь позже.";
				link.l1.go = "exit";
			}
		break;
		
		case "potion4":
			npchar.quest.price = 900;
			npchar.quest.type = 4;
			dialog.text = "Микстуру? С тебя 900 песо, сын мой.";
			if (sti(Pchar.money) >= 900)
			{
				link.l1 = "Пожалуйста, брат Юлиан. Вот деньги.";
				link.l1.go = "potion_pay";
			}
			else
			{
				link.l1 = "К сожалению, у меня недостаточно средств... Я вернусь позже.";
				link.l1.go = "exit";
			}
		break;
		
		case "potion_pay":
			AddMoneyToCharacter(pchar, -sti(npchar.quest.price));
			iTemp = sti(npchar.quest.type);
			GiveItem2Character(pchar, "potion"+iTemp);
			PlaySound("interface\important_item.wav");
			dialog.text = "Пожалуйста. Держи свое лекарство. Да хранит тебя Господь!";
			link.l1 = "Спасибо, брат Юлиан.";
			link.l1.go = "exit";
			SaveCurrentNpcQuestDateParam(npchar, "potion"+iTemp+"_date");
		break;
		
		case "amulet":
			bool bOK = (!CheckAttribute(npchar, "amulet_date")) || (GetNpcQuestPastDayParam(npchar, "amulet_date") >= 3)
			if (bOk && GetSummonSkillFromName(pchar, SKILL_FORTUNE) > (10+drand(110)))
			{
				npchar.quest.amulet = SelectLSCChurchAmulet();
				dialog.text = "Да, у меня бывают освященные обереги, способные защитить тебя от ранений или недугов. Стоимость одинакова для всех - десять золотых дублонов. Сегодня могу предложить тебе "+XI_ConvertString(npchar.quest.amulet)+".";
				if (GetCharacterItem(pchar, "gold_dublon") >= 10)
				{
					link.l1 = "Да, я хочу купить этот оберег. Вот золото.";
					link.l1.go = "amulet_pay";
					link.l2 = "У меня уже есть такой оберег, брат Юлиан. Я подожду, пока у вас появится что-то еще.";
			link.l2.go = "exit";
					SaveCurrentNpcQuestDateParam(npchar, "amulet_date");
				}
				else
				{
					link.l1 = "К сожалению, у меня недостаточно средств... Возможно, позже.";
					link.l1.go = "exit";
				}
			}
			else
			{
				dialog.text = "Нет, сын мой, к сожалению, сейчас ничего нет. Зайди в другой день, возможно, у меня что-нибудь появится.";
				link.l1 = "Хорошо, брат Юлиан.";
				link.l1.go = "exit";
			}
		break;
		
		case "amulet_pay":
			RemoveItems(pchar, "gold_dublon", 10);
			GiveItem2Character(pchar, npchar.quest.amulet);
			Log_Info("Вы получили амулет");
			PlaySound("interface\important_item.wav");
			dialog.text = "Спасибо, сын мой. Твои деньги пойдут на благое дело. Возьми свою покупку, и да хранит тебя Господь!";
			link.l1 = "И вам спасибо, брат Юлиан.";
			link.l1.go = "exit";
		break;
		
		case "":
			dialog.text = "";
			link.l1 = "";
			link.l1.go = "";
		break;
		
		case "":
			dialog.text = "";
			link.l1 = "";
			link.l1.go = "";
		break;
		
//--------------------------------------- блок вопросов и ответов ---------------------------------------------
		case "int_quests":
			dialog.text = "Внимательно тебя слушаю.";
			if (!CheckAttribute(npchar, "quest.answer_1"))
			{
				link.l1 = "Как вы попали на остров, брат Юлиан?";
				link.l1.go = "ansewer_1";
			}
			if (!CheckAttribute(npchar, "quest.answer_2"))
			{
				link.l2 = "И много человек в вашем приходе?";
				link.l2.go = "ansewer_2";
			}
			if (!CheckAttribute(npchar, "quest.answer_3"))
			{
				link.l3 = "У кого, кроме вас, здесь можно что-нибудь приобрести?";
				link.l3.go = "ansewer_3";
			}
			if (!CheckAttribute(npchar, "quest.answer_4"))
			{
				link.l4 = "Как вы считаете, Острову не угрожает уничтожение, например, во время сильного шторма?";
				link.l4.go = "ansewer_4";
			}
			link.l10 = "Нет вопросов. Извините...";
			link.l10.go = "exit";
		break;
		
		case "ansewer_1":
			dialog.text = "Так же, как и многие другие, сын мой. Судно, на котором я плыл из Гаваны в Новую Испанию, затонуло во время шторма. Милостью Господа нашего я остался в живых, и теперь служу во благо Ему, наставляя на путь истинный жителей этого клочка суши.";
			link.l1 = "Понятно...";
			link.l1.go = "int_quests";
			npchar.quest.answer_1 = "true";
		break;
		
		case "ansewer_2":
			dialog.text = "Меньше, чем хотелось бы. Большинство из клана нарвал предпочитают насилие милосердию, а ривадос - бедные заблудшие овцы. В слепости своей они практикуют языческие обряды, подвергая опасности свои бессмертные души. Среди ривадос есть опасный колдун, слуга темных сил, которого давно уже было бы пора предать справедливому суду Священной Инквизиции.";
			link.l1 = "Ясно...";
			link.l1.go = "int_quests";
			npchar.quest.answer_2 = "true";
		break;
		
		case "ansewer_3":
			dialog.text = "У Санчо Карпентеро, владельца таверны на 'Флероне', вы найдете еду, питье и теплую постель, у Акселя Йоста на 'Эсмеральде' - широкий ассортимент разнообразных товаров. Также поспрашивай на улицах, сын мой - люди часто находят на погибших кораблях внешнего кольца ценные вещи, которые готовы продать.";
			link.l1 = "Спасибо!";
			link.l1.go = "int_quests";
			npchar.quest.answer_3 = "true";
		break;
		
		case "ansewer_4":
			dialog.text = "Все в руках Господа нашего, сын мой. Мы веруем в Него и уповаем на Него. До сих пор серьезные потрясения обходили нас стороной - штормы часто бушуют вокруг Острова, но на нем самом как правило тихо и солнечно.";
			link.l1 = "Благодарю. Вы меня успокоили.";
			link.l1.go = "int_quests";
			npchar.quest.answer_4 = "true";
		break;
// <-- блок вопросов и ответов
		
//----------------------------------------- специальные реакции -----------------------------------------------
		//обнаружение ГГ в сундуках
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("Что ты там копаешься, а? Да ты вор!", "Вот это да! Чуть я загляделся, а ты сразу в сундук с головой!", "По сундукам шарить вздумал?! Тебе это даром не пройдет!");
			link.l1 = "А-ать, дьявол!!!";
			link.l1.go = "fight";
		break;
		
		case "Woman_FackYou":
			dialog.text = "Ах, вот, значит, как?! По сундукам шарить вздумал?! Тебе это даром не пройдет!";
			link.l1 = "Вот дура!..";
			link.l1.go = "exit_setOwner";
			LAi_group_Attack(NPChar, Pchar);
		break;
		
		case "fight":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LAi_SetOwnerTypeNoGroup(npchar);
			LAi_group_Attack(NPChar, Pchar);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "exit_setOwner":
			LAi_SetOwnerTypeNoGroup(npchar);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		//замечание по обнаженному оружию
		case "LSCNotBlade":
			dialog.text = LinkRandPhrase("Слушай, ты бы убрал оружие. А то нервируешь немного...", "Знаешь, у нас тут не принято сабелькой размахивать. Убери оружие.", "Слушай, что ты, как д'Артаньян, бегаешь тут, шпагой машешь? Убери оружие, не к лицу это серьезному мужчине...");
			link.l1 = LinkRandPhrase("Хорошо.", "Ладно.", "Как скажешь...");
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;	
		
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = NPCharSexPhrase(NPChar, "Послушайте, я, как гражданин этого города, прошу вас не ходить у нас с обнаженным клинком.", "Знаете, я, как гражданка этого города, прошу вас не ходить у нас с обнаженным клинком.");
				link.l1 = LinkRandPhrase("Хорошо.", "Ладно.", "Как скажете...");
			}
			else
			{
				dialog.text = NPCharSexPhrase(NPChar, "Острожней на поворотах, приятель, когда бежишь с оружием в руках. Я ведь могу и занервничать...", "Мне не нравится, когда мужчины ходят передо мной с оружием на изготовку. Это меня пугает...");
				link.l1 = RandPhraseSimple("Понял.", "Убираю.");
			}
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;
// <-- специальные реакции
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}

string SelectLSCChurchAmulet();
{
	string sAmulet;
	switch (drand(3))
	{
		case 0: sAmulet = "amulet_2"; break;
		case 1: sAmulet = "amulet_3"; break;
		case 2: sAmulet = "amulet_6"; break;
		case 3: sAmulet = "amulet_7"; break;
	}
	return sAmulet;
}