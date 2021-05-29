// Орели Бертин - просто жительница
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
				dialog.text = "Здравствуйте, мистер. Что скажете?";
				link.l1 = TimeGreeting()+". Меня зовут "+GetFullName(pchar)+", я здесь недавно, вот, знакомлюсь с обитателями Острова.";
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
				link.l5 = "Да просто решил узнать как у вас дела. Ещё увидимся!";
				link.l5.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting": // первая встреча
			dialog.text = "Ясно. А меня зовут Орели Бертин. Каким ветром вас сюда занесло?";
			link.l1 = "Скажем так - захотелось посмотреть на сказочный Остров Справедливости.";
			link.l1.go = "meeting_1";
		break;
		
		case "meeting_1":
			dialog.text = "Значит, вы один из тех чудаков, что приплывают сюда по собственной воле... Ну что же, теперь у вас будет достаточно времени, чтобы и насмотреться на Остров, и наесться до отвала его 'справедливостью'.";
			link.l1 = "А что, здесь со справедливостью проблемы, раз такая ирония?";
			link.l1.go = "meeting_2";
		break;
		
		case "meeting_2":
			dialog.text = "Нет, что вы... всё в порядке. Вот только почему-то мы вынуждены платить пиратам за наше же продовольствие, которое раньше было бесплатным для всех. А когда кланы устраивают междоусобные побоища на нашей части Острова, мы почему-то должны прятаться по трюмам, чтобы не дай Бог не задело саблей или пулей\nТо есть на нашей территории они делают, что хотят, а мы на их корабли даже носа казать не можем. А в остальном - всё хорошо, всё хорошо...";
			link.l1 = "Понятно. Ладно, рад знакомству. Ещё встретимся!";
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
			dialog.text = "Слушаю вас.";
			if (!CheckAttribute(npchar, "quest.answer_1"))
			{
				link.l1 = "Вы давно живёте здесь?";
				link.l1.go = "ansewer_1";
			}
			if (!CheckAttribute(npchar, "quest.answer_2"))
			{
				link.l2 = "Что интересного есть на Острове?";
				link.l2.go = "ansewer_2";
			}
			if (!CheckAttribute(npchar, "quest.answer_3"))
			{
				link.l3 = "Как вы относитесь к кланам?";
				link.l3.go = "ansewer_3";
			}
			if (!CheckAttribute(npchar, "quest.answer_4"))
			{
				link.l4 = "Пираты вам проблем не доставляют?";
				link.l4.go = "ansewer_4";
			}
			link.l10 = "Нет вопросов. Извините...";
			link.l10.go = "exit";
		break;
		
		case "ansewer_1":
			dialog.text = "Очень. Уже даже и счёт потеряла. Наверное, что-то около семнадцати... нет, наверное, восемнадцать... или уже двадцать? А который сейчас год?";
			link.l1 = "Понятно... То есть вы - старожил?";
			link.l1.go = "ansewer_1_1";
		break;
		
		case "ansewer_1_1":
			dialog.text = "Относительно. Я ещё помню те времена, когда с нами торговали кубинские буканьеры, а самые отчаянные и ушлые обитатели из нарвалов возили на Большую землю товары из трюмов кораблей и меняли их на провиант. Но что я - тут полно людей, не видевших ничего, кроме этого Острова, поскольку родились здесь. Вот они - даже не старожилы, а коренные жители.";
			link.l1 = "Интересно...";
			link.l1.go = "int_quests";
			npchar.quest.answer_1 = "true";
		break;
		
		case "ansewer_2":
			dialog.text = "Да тут всё интересно. Походите, посмотрите сами. Поплавайте вокруг центральной части Острова. Сходите в таверну, в магазин, в церковь. Правда, через неделю интерес пропадёт, я вам это обещаю.";
			link.l1 = "Ясно...";
			link.l1.go = "int_quests";
			npchar.quest.answer_2 = "true";
		break;
		
		case "ansewer_3":
			dialog.text = "А как можно относиться к этим разбойникам? Держусь от них подальше, и всё. И если от нарвалов Острову ещё есть какой-то толк, за счёт того, что среди них имеются мастера с золотыми руками, то от этих язычников ривадос ничего, кроме порчи, ожидать не приходится\nОни так и живут по своим африканским обычаям, как и их предки двести лет назад. Разве что огнестрельным оружием пользоваться научились, а так - зверьё, а не люди. Говорят, что они даже практикуют ритуальный каннибализм!";
			link.l1 = "Кошмар какой-то...";
			link.l1.go = "int_quests";
			npchar.quest.answer_3 = "true";
		break;
		
		case "ansewer_4":
			dialog.text = "Если не считать того, что они заставляют нас платить за нашу же провизию, они никому из простых жителей не мешают. Скорее - наоборот: утихомирили ретивых клановцев, и за порядком немного присматривают\nНе так давно один из жителей начал не на шутку буянить и по каждому поводу за саблю хвататься, даже ранил двоих горожан. Так они его быстренько скрутили и отправили на 'Тартарус'. Он там посидел две недели - теперь тише воды, ниже травы, даже на улицах не видать. На внешнем кольце теперь постоянно обитает...";
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
			dialog.text = LinkRandPhrase("Слушай, ты бы убрал оружие. А то нервируешь немного...", "Знаешь, у нас тут не принято сабелькой размахивать. Убери оружие.", "Слушай, что ты, как д'Артаньян, бегаешь тут, шпагой машешь? Убери оружие, не к лицу это серьезному мужчине...");
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