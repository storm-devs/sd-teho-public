// Сесил Галард - бабулька
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
				dialog.text = "Вы что-то хотели, молодой человек?";
				link.l1 = TimeGreeting()+". Позвольте представиться - "+GetFullName(pchar)+". Я у вас недавно.";
				link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "А, "+GetFullName(pchar)+"! "+TimeGreeting()+"! Вы что-то хотели?";
				link.l1 = LinkRandPhrase("Что-нибудь интересное мне расскажете?", "Что нового произошло на острове в последнее время?", "Не расскажете ли последние сплетни?");
				link.l1.go = "rumours_LSC";
				link.l2 = "Я хочу задать вам пару вопросов об острове.";
				link.l2.go = "int_quests"; //информационный блок
				link.l5 = "Да просто решил узнать как у вас дела. Еще увидимся!";
				link.l5.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting": // первая встреча
			dialog.text = "А-а, так вы знакомитесь с нашим Островом и его обитателями, верно?";
			link.l1 = "Именно так, миссис?..";
			link.l1.go = "meeting_1";
		break;
		
		case "meeting_1":
			dialog.text = "Галард. Сесил Галард.";
			link.l1 = "Очень приятно, миссис Галард. Будем знакомы!";
			link.l1.go = "meeting_2";
		break;
		
		case "meeting_2":
			dialog.text = "Будем... И откуда же вас принесло, молодой человек? Кораблекрушений вроде как не было в последние дни...";
			link.l1 = "Принесло меня с Мэйна на баркасе... но у самых берегов Острова он перевернулся и утонул. Так я и остался без корабля.";
			link.l1.go = "meeting_3";
		break;
		
		case "meeting_3":
			dialog.text = "На баркасе? Что-то слабо верится... Ну тогда вам вообще повезло, что вы прошли путь до Острова на такой скорлупе и не угодили в шторм. У нас на Острове штормит редко, а вот за его пределами шквал может налететь буквально как гром среди ясного неба\nТак что считайте себя счастливчиком и приспосабливайтесь к жизни на Острове! Потому как боюсь вас расстроить, но попасть сюда легко, а выбраться - практически невозможно. И не считайте это брюзжанием - за последние десять лет еще никто не смог живым покинуть Остров.";
			link.l1 = "И все-таки я приберегу немного оптимизма для себя. Рад знакомству, еще увидимся!";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
		case "":
			dialog.text = "";
			link.l1 = "";
			link.l1.go = "";
		break;
		
//--------------------------------------- блок вопросов и ответов ---------------------------------------------
		case "int_quests":
			dialog.text = "Да, молодой человек?";
			if (!CheckAttribute(npchar, "quest.answer_1"))
			{
				link.l1 = "А как вы, миссис, попали на этот Остров?";
				link.l1.go = "ansewer_1";
			}
			if (!CheckAttribute(npchar, "quest.answer_2"))
			{
				link.l2 = "Вы давно тут живете, как я понимаю?";
				link.l2.go = "ansewer_2";
			}
			if (!CheckAttribute(npchar, "quest.answer_3"))
			{
				link.l3 = "Что вы можете сказать о местных жителях?";
				link.l3.go = "ansewer_3";
			}
			if (!CheckAttribute(npchar, "quest.answer_4"))
			{
				link.l4 = "Какие интересные личности живут на Острове?";
				link.l4.go = "ansewer_4";
			}
			link.l10 = "Нет вопросов. Извините...";
			link.l10.go = "exit";
		break;
		
		case "ansewer_1":
			dialog.text = "Это было так давно, что я уже и забыла толком, как это произошло. Кораблекрушение - вот и весь сказ...";
			link.l1 = "Ясно...";
			link.l1.go = "int_quests";
			npchar.quest.answer_1 = "true";
		break;
		
		case "ansewer_2":
			dialog.text = "Иногда мне кажется, что я родилась тут... Но это, конечно, не так. Просто я всю вторую половину своей долгой жизни прожила на Острове. И умру я здесь, поскольку покидать Остров не собираюсь.";
			link.l1 = "Понятно...";
			link.l1.go = "int_quests";
			npchar.quest.answer_2 = "true";
		break;
		
		case "ansewer_3":
			dialog.text = "А что тут скажешь, молодой человек... разные все. Кого у нас только нет - белые, черные, индейцы, бывшие рабы и господа, каторжники и солдаты. А сколько их было раньше - всех не упомнить. У каждого своя история и свои склонности. Кому-то уже на все наплевать, а кто-то горит ярым желанием уплыть назад. Так и живем...";
			link.l1 = "Интересно...";
			link.l1.go = "int_quests";
			npchar.quest.answer_3 = "true";
		break;
		
		case "ansewer_4":
			dialog.text = "Самые интересные - это механик нарвалов, самоучка-изобретатель, оружейник нарвалов - герр Шмидт, кузнец от Бога, Санчо Карпентеро - прирожденный бармен. Ну, теперь еще добавился адмирал пиратов и его старший помощник.";
			link.l1 = "Буду знать...";
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