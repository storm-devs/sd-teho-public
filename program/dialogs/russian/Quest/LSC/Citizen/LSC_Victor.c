// Виктор Кассель - бандит
#include "DIALOGS\russian\Rumours\Common_rumours.c"
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;

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
				dialog.text = "Я не желаю с тобой общаться. Ты нападаешь без причины на мирных граждан, провоцируешь их на драку. Уходи прочь!";
				link.l1 = "Гм...";
				link.l1.go = "exit";
				break;
			}
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "Хм... Что ты хотел, приятель? Если поболтать, то я тебя огорчу: у меня нет никакого желания трепать языком.";
				link.l1 = "Очень жаль... Я именно хотел поговорить. Я недавно тут, вот, знакомлюсь с людьми...";
				link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "А, "+GetFullName(pchar)+"! Чего надо?";
				link.l1 = LinkRandPhrase("Что-нибудь интересное мне расскажешь?", "Что нового произошло на острове в последнее время?", "Не расскажешь ли последние сплетни?");
				link.l1.go = "rumours_LSC";
				link.l2 = "Я хочу задать тебе пару вопросов об острове.";
				link.l2.go = "int_quests"; //информационный блок
				link.l5 = "Да просто решил узнать как у тебя дела. Ещё увидимся!";
				link.l5.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting": // первая встреча
			dialog.text = "Новичок? Хм. Ладно, раз такое дело. Я - Виктор Кассель, и лучше меня не злить, когда я в дурном расположении духа. Да и когда в хорошем - тоже. Ибо я не трачу время на ненужные разговоры, а за настырность могу и заехать кулаком по физиономии.";
			link.l1 = "Ну а я - "+GetFullName(pchar)+". Кстати, за удар по физиономии кулаком могу запросто ответить тем же. Но, надеюсь, до этого не дойдёт. Не буду тебя раздражать, раз ты такой нелюдимый. Пока.";
			link.l1.go = "exit";
			link.l2 = LinkRandPhrase("Что-нибудь интересное мне расскажешь?", "Что нового произошло на острове в последнее время?", "Не расскажешь ли последние сплетни?");
			link.l2.go = "rumours_LSC";
			link.l3 = "Я хочу задать тебе пару вопросов об острове.";
			link.l3.go = "int_quests"; //информационный блок
			NextDiag.TempNode = "First time";
		break;
		
//--------------------------------------- блок вопросов и ответов ---------------------------------------------
		case "int_quests":
			dialog.text = "Да? И что же я могу тебе рассказать?";
			if (!CheckAttribute(npchar, "quest.answer_1"))
			{
				link.l1 = "Как ты очутился на острове?";
				link.l1.go = "ansewer_1";
			}
			if (!CheckAttribute(npchar, "quest.answer_2"))
			{
				link.l2 = "Что из себя представляет жизнь на Острове?";
				link.l2.go = "ansewer_2";
			}
			if (!CheckAttribute(npchar, "quest.answer_3"))
			{
				link.l3 = "Кто из жителей острова наиболее... значительный?";
				link.l3.go = "ansewer_3";
			}
			if (!CheckAttribute(npchar, "quest.answer_4"))
			{
				link.l4 = "А где можно на Острове раздобыть денег?";
				link.l4.go = "ansewer_4";
			}
			link.l10 = "Нет вопросов. Извините...";
			link.l10.go = "exit";
		break;
		
		case "ansewer_1":
			dialog.text = "Прости, дружище, но тебе-то какое дело? Очутился и очутился. Я не хочу распространяться об этой истории, тем более обсуждать её с каждым встречным-поперечным.";
			link.l1 = "Ну извини...";
			link.l1.go = "int_quests";
			npchar.quest.answer_1 = "true";
		break;
		
		case "ansewer_2":
			dialog.text = "Скуку. Нудную, тупую, бессмысленную. Я вот сейчас собираюсь прибиться к пиратам Акулы - это достойные ребята. Я с удовольствием вступлю в их команду, только сначала немного... присмотрюсь. Уверен, что они найдут способ выбраться с Острова.";
			link.l1 = "Ты так считаешь? Понятно...";
			link.l1.go = "int_quests";
			npchar.quest.answer_2 = "true";
		break;
		
		case "ansewer_3":
			dialog.text = "Конечно - адмирал! Пираты держат в кулаке и нарвалов, и ривадос, и те не смеют против них даже пикнуть. Потом - лидеры кланов, Дональд Гринспи у нарвалов и Чёрный Эдди у ривадос. Аксель Йост - торговец нарвалов - тоже не последний человек. Ну и, конечно, бармен Санчо Карпентеро - свой парень...";
			link.l1 = "Ясно...";
			link.l1.go = "int_quests";
			npchar.quest.answer_3 = "true";
		break;
		
		case "ansewer_4":
			dialog.text = "В сундуках. Если, конечно, ты сумеешь их открыть, ибо никто тут друг другу не доверяет и все сундуки запираются. И то, дружище, скажу тебе, что ценные предметы лежат в сундуках внутри кораблей под надёжным присмотром их хозяев\nА кроме сундуков - плыви на внешнее кольцо и шарься по протухлым трюмам кораблей, и молись, чтобы не провалиться сквозь гнилые доски под воду, или ступай охотиться на крабов - за их мясистые клешни тут очень неплохо платят.";
			link.l1 = "Понятно...";
			link.l1.go = "int_quests";
			npchar.quest.answer_4 = "true";
		break;
// <-- блок вопросов и ответов
		
//----------------------------------------- специальные реакции -----------------------------------------------
		//обнаружение ГГ в сундуках
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("Что ты там копаешься, а? Да ты вор!", "Вот это да! Чуть я загляделся, а ты сразу в сундук с головой!", "По сундукам шарить вздумал?! Тебе это даром не пройдёт!");
			link.l1 = "А-ать, дьявол!!!";
			link.l1.go = "fight";
		break;
		
		case "Woman_FackYou":
			dialog.text = "Ах, вот, значит, как?! По сундукам шарить вздумал?! Тебе это даром не пройдёт!";
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
			dialog.text = LinkRandPhrase("Слушай, ты бы убрал оружие. А то нервируешь немного...", "Знаешь, у нас тут не принято сабелькой размахивать. Убери оружие.", "Слушай, что ты, как д'Артаньян, бегаешь тут, шпагой машешь? Убери оружие, не к лицу это серьёзному мужчине...");
			link.l1 = LinkRandPhrase("Хорошо.", "Ладно.", "Как скажешь...");
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;	
		
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = NPCharSexPhrase(NPChar, "Послушайте, я, как гражданин этого города, прошу вас не ходить у нас с обнажённым клинком.", "Знаете, я, как гражданка этого города, прошу вас не ходить у нас с обнажённым клинком.");
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