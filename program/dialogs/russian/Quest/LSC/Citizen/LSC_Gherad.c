// Гхерад Смиитс - матрос
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
				dialog.text = "Здорово, старина, ха-ха! Какими судьбами тут?";
				link.l1 = TimeGreeting()+". Разве мы с вами знакомы?";
				link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "А, "+GetFullName(pchar)+"! "+TimeGreeting()+"! Вы что-то хотели?";
				link.l1 = LinkRandPhrase("Что-нибудь интересное мне расскажете?", "Что нового произошло на острове в последнее время?", "Не расскажете ли последние сплетни?");
				link.l1.go = "rumours_LSC";
				link.l2 = "Я хочу задать тебе пару вопросов об острове.";
				link.l2.go = "int_quests"; //информационный блок
				link.l5 = "Да просто решил узнать как у вас дела. Ещё увидимся!";
				link.l5.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting": // первая встреча
			dialog.text = "Нет, конечно, но ведь за этим дело не станет? Я - Гхерад Смиитс, моряк, матрос из Роттердама. А судя по тебе, дружище, ты никак не ниже квартирмейстера...";
			link.l1 = "Вроде того. Меня зовут - "+GetFullName(pchar)+". Будем знакомы.";
			link.l1.go = "meeting_1";
		break;
		
		case "meeting_1":
			dialog.text = "Ты больше похож на судовладельца, или казначея... Но одно видно - человек образованный. Рад познакомиться. Как тебя сюда занесло?";
			link.l1 = "Решил исследовать незнакомую местность. Буканьеры с Кубы рассказали, что тут что-то есть, вот и решил проверить...";
			link.l1.go = "meeting_2";
		break;
		
		case "meeting_2":
			dialog.text = "Ты один остался после крушения? Где затонул твой корабль? У кольца?";
			link.l1 = "Один. А моя тартана лежит на дне, даже до кольца не дотянула.";
			link.l1.go = "meeting_3";
		break;
		
		case "meeting_3":
			dialog.text = "Ясно. Ну, обживайся, теперь ты тут надолго. Заходи к Санчо на кружку рому - это хорошее дело...";
			link.l1 = "Обязательно. Ещё увидимся!";
			link.l1.go = "exit";
			link.l2 = LinkRandPhrase("Что-нибудь интересное мне расскажешь?", "Что нового произошло на острове в последнее время?", "Не расскажешь ли последние сплетни?");
			link.l2.go = "rumours_LSC";
			link.l3 = "Я хочу задать тебе пару вопросов об острове.";
			link.l3.go = "int_quests"; //информационный блок
			NextDiag.TempNode = "First time";
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
		
		case "":
			dialog.text = "";
			link.l1 = "";
			link.l1.go = "";
		break;
		
//--------------------------------------- блок вопросов и ответов ---------------------------------------------
		case "int_quests":
			dialog.text = "Конечно, дружище. Слушаю тебя.";
			if (!CheckAttribute(npchar, "quest.answer_1"))
			{
				link.l1 = "Расскажи, как ты оказался на Острове?";
				link.l1.go = "ansewer_1";
			}
			if (!CheckAttribute(npchar, "quest.answer_2"))
			{
				link.l2 = "Ты хотел бы покинуть Остров и вернуться к прежней жизни?";
				link.l2.go = "ansewer_2";
			}
			if (!CheckAttribute(npchar, "quest.answer_3"))
			{
				link.l3 = "А кланы не мешают вам жить?";
				link.l3.go = "ansewer_3";
			}
			if (!CheckAttribute(npchar, "quest.answer_4"))
			{
				link.l4 = "А как образовался этот Остров - ты не думал об этом?";
				link.l4.go = "ansewer_4";
			}
			link.l10 = "Нет вопросов. Извини...";
			link.l10.go = "exit";
		break;
		
		case "ansewer_1":
			dialog.text = "Я попал сюда вместе с этим надутым индюком Эбботом. Я служил матросом на его корабле. Скажу тебе - такие, как он, никогда не должны ступать на палубу корабля, потому что приносят несчастья. Дёрнула его нелёгкая самому отправиться в плавание\nНадо было дойти всего лишь от Ямайки до Белиза, сущий пустяк. Но словно злой рок преследовал нас: боцман упал за борт, штурман ошибся, вычисляя координаты, да ещё эти чёртовы испанцы, а потом - шторм. Так и оказались здесь.";
			link.l1 = "Интересно...";
			link.l1.go = "int_quests";
			npchar.quest.answer_1 = "true";
		break;
		
		case "ansewer_2":
			dialog.text = "Чёрт его знает, приятель. Раньше хотел, а теперь что-то и не очень. Жизнь здесь неплоха, полно рома и вина, разносолы, правда, не всегда в изобилии, но и то еда намного лучше, чем та, которой нас кормили на кораблях, где я служил\nДа и люди здесь есть нормальные, есть с кем выпить и поговорить. Мне здесь нравится. Так что даже и не знаю, что сказать... Пожалуй - нет, не хочу. Раньше я был постоянно голоден и зол, а теперь - посмотри, какое брюхо отъел, ха-ха!";
			link.l1 = "Здорово! Рад за тебя.";
			link.l1.go = "int_quests";
			npchar.quest.answer_2 = "true";
		break;
		
		case "ansewer_3":
			dialog.text = "Нет, не мешают. Главное - не ругаться с ними и не лезть на их территорию без спроса. Этого они страсть как не любят. А нарвалы - очень неплохие ребята, почти все они родились тут, на Острове, и другой жизни и не видели. Многие из них мастера на все руки, например, Юрген Шмидт. Он кузнец от Бога!";
			link.l1 = "Понятно...";
			link.l1.go = "int_quests";
			npchar.quest.answer_3 = "true";
		break;
		
		case "ansewer_4":
			dialog.text = "А чего здесь думать? Тут мелководье и рифы. Внешнее кольцо состоит сплошь из кораблей, до самого дна. Корабли попадают в шторм, налетают на рифы или прямиком на внешнее кольцо. Так Остров и растёт. А вот как внутренние корабли остались на плаву - мне неведомо.";
			link.l1 = "Ясно...";
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