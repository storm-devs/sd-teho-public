// официантка Наталия Бушелл
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
			if (pchar.questTemp.LSC == "return" && !CheckAttribute(npchar, "quest.return_isl"))
			{
				dialog.text = "Ой! А мне рассказывали, что вы утонули... Вот врунишки!";
				link.l1 = "Конечно, врунишки! Я жив и здоров!";
				link.l1.go = "exit";
				npchar.quest.return_isl = "true";
				break;
			}
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "Здравствуйте, "+GetAddress_Form(NPChar)+"! Вы впервые у нас? Что-то я вас раньше не видала... Надеюсь, теперь вы будете заходить к нам почаще - у Санчо превосходный выбор напитков. Да, меня зовут Натали и я помогаю Санчо вести дела таверны.";
				link.l1 = TimeGreeting()+". Меня зовут "+GetFullName(pchar)+". Приятно познакомиться. А раньше ты меня видеть и не могла - я недавно на Острове.";
				link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "А, "+GetFullName(pchar)+"! "+TimeGreeting()+"! Вы что-то хотели?";
				link.l1 = LinkRandPhrase("Что-нибудь интересное мне расскажешь?", "Что нового произошло на острове в последнее время?", "Не расскажешь ли последние сплетни?");
				link.l1.go = "rumours_LSC";
				link.l2 = "Я хочу задать тебе пару вопросов об острове.";
				link.l2.go = "int_quests"; //информационный блок
				link.l5 = "Да просто решил узнать как у тебя дела. Еще увидимся!";
				link.l5.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting": // первая встреча
			dialog.text = "Недавно? Неужели еще один корабль разбился? Что-то я ни о чем таком не слыхала... Или вы, как и месье Тьюрам, прибились сюда на обломке мачты? Ой, простите мое любопытство - женская натура, что поделать.";
			link.l1 = "Да нет, все в порядке, Натали. Я доплыл сюда на баркасе, но он утонул. Приятно было познакомиться. Еще увидимся!";
			link.l1.go = "exit";
			link.l2 = "Да нет, все в порядке, Натали. Я хочу задать тебе пару вопросов об острове.";
			link.l2.go = "int_quests"; //информационный блок
			NextDiag.TempNode = "First time";
		break;
		
		case "":
			dialog.text = "";
			link.l1 = "";
			link.l1.go = "";
		break;
		
//--------------------------------------- блок вопросов и ответов ---------------------------------------------
		case "int_quests":
			dialog.text = "Внимательно вас слушаю.";
			if (!CheckAttribute(npchar, "quest.answer_1"))
			{
				link.l1 = "Ты работаешь в этой таверне. Что расскажешь о ее хозяине?";
				link.l1.go = "ansewer_1";
			}
			if (!CheckAttribute(npchar, "quest.answer_2"))
			{
				link.l2 = "А как ты сюда попала?";
				link.l2.go = "ansewer_2";
			}
			if (!CheckAttribute(npchar, "quest.answer_3"))
			{
				link.l3 = "И много народу живет на Острове?";
				link.l3.go = "ansewer_3";
			}
			if (!CheckAttribute(npchar, "quest.answer_4"))
			{
				link.l4 = "Вы здесь совсем не удивляетесь новым людям?";
				link.l4.go = "ansewer_4";
			}
			link.l10 = "Нет вопросов. Извините...";
			link.l10.go = "exit";
		break;
		
		case "ansewer_1":
			dialog.text = "Только хорошее, "+GetAddress_Form(NPChar)+". У Санчо всегда большой ассортимент выпивки - от старых вин до простого рома и эля. В трюме одного из кораблей он несколько лет назад нашел огромный запас марочных вин. Санчо два месяца на своем горбу перетаскивал ящики с бутылками себе в кладовку\nЗато теперь мы надолго обеспечены таким спиртным, которое на Архипелаге подается только губернаторам. А что касается рома - так этого добра еще больше. Но кроме выпивки, вы всегда найдете у нашего Санчо добрый совет, свежие новости и постель для ночлега.";
			link.l1 = "Понятно...";
			link.l1.go = "int_quests";
			npchar.quest.answer_1 = "true";
		break;
		
		case "ansewer_2":
			dialog.text = "Ох, это грустная история. Семь лет назад я сбежала вместе со своим женихом из отчего дома и мы отправились из Сантьяго в Белиз. По пути штурман совершил ошибку и отклонился от курса на север, затем мы попали в шторм и наш корабль затонул у внешнего кольца\nМой жених погиб, как и многие на том корабле. А я и горстка выживших пополнили ряды жителей Острова.";
			link.l1 = "Ясно...";
			link.l1.go = "int_quests";
			npchar.quest.answer_2 = "true";
		break;
		
		case "ansewer_3":
			dialog.text = "Достаточно. Кланы ривадос и нарвалов многочисленны - это неудивительно, поскольку они живут здесь уже десятки лет. Простых граждан намного меньше, но по вечерам в таверне часто бывает многолюдно, да так, что я едва успеваю разносить ром.";
			link.l1 = "Вот как? Очень интересно...";
			link.l1.go = "int_quests";
			npchar.quest.answer_3 = "true";
		break;
		
		case "ansewer_4":
			dialog.text = "А чему удивляться? Пополнения у нас нередки. Да и я сама толком не знаю, кто здесь и сколько живет. Иногда вот вижу человека впервые - а он, оказывается, уже год как на Острове! Вот забавно, да?";
			link.l1 = "Да уж...";
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