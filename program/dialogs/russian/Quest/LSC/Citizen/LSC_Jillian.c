// Джиллиан Стайнер - просто девушка
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
				dialog.text = "Ой... здравствуйте! Вы меня напугали. Подошли так неожиданно... Что вам угодно?";
				link.l1 = TimeGreeting()+". Меня зовут "+GetFullName(pchar)+". Я недавно попал на Остров, знакоммлюсь с его обитателями, и наконец решился подойти и поговорить со столь милой особой - с вами. Как ваше имя?";
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
				link.l5 = "Да просто решил узнать как у вас дела. Еще увидимся!";
				link.l5.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting": // первая встреча
			dialog.text = "Вы заставляете меня краснеть, сударь, но все равно приятно. Спасибо за комплимент. Меня зовут Джиллиан, Джиллиан Стайнер. Рада знакомству.";
			link.l1 = "Я тоже, Джиллиан.";
			link.l1.go = "meeting_1";
		break;
		
		case "meeting_1":
			dialog.text = "Вы недавно у нас? А как вы сюда попали, расскажите? Вы спаслись после крушения, так?";
			link.l1 = "Ну... вроде того. Я отправился сюда на баркасе, почти прошел через рифы, но неудачно налетел на обломок корабля и моя лодка перевернулась и пошла ко дну. Ну, а я вплавь добрался сюда.";
			link.l1.go = "meeting_2";
		break;
		
		case "meeting_2":
			dialog.text = "О! Так вы прибыли сюда по своему желанию? Удивительно!";
			link.l1 = "Да, вот такой я чудак. Решил найти пресловутый Остров Справедливости, и нашел его. Правда, не знаю теперь, как отсюда выбраться.";
			link.l1.go = "meeting_3";
		break;
		
		case "meeting_3":
			dialog.text = "Вы или очень храбры, или безрассудны. Отправиться сюда на баркасе... Теперь будете жить с нами, потому что как говорят - за последние десять лет еще никто не покидал пределов Острова.";
			link.l1 = "И все-таки я не теряю надежды. Ладно, Джиллиан, не буду больше отнимать ваше время. Еще увидимся!";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
//--------------------------------------- блок вопросов и ответов ---------------------------------------------
		case "int_quests":
			dialog.text = "Да, конечно, "+pchar.name+". Слушаю.";
			if (!CheckAttribute(npchar, "quest.answer_1"))
			{
				link.l1 = "Как вы попали на Остров?";
				link.l1.go = "ansewer_1";
			}
			if (!CheckAttribute(npchar, "quest.answer_2"))
			{
				link.l2 = "Вы бы хотели уплыть с Острова?";
				link.l2.go = "ansewer_2";
			}
			if (!CheckAttribute(npchar, "quest.answer_3"))
			{
				link.l3 = "А как проходит ваш день? Чем вы занимаетесь?";
				link.l3.go = "ansewer_3";
			}
			if (!CheckAttribute(npchar, "quest.answer_4"))
			{
				link.l4 = "Вы говорите - не замужем... Неужели у такой симпатичной девушки нет ухажеров здесь?";
				link.l4.go = "ansewer_4";
			}
			link.l10 = "Нет вопросов. Извините...";
			link.l10.go = "exit";
		break;
		
		case "ansewer_1":
			dialog.text = "Плыла из Англии в колонии вместе со своими родителями. Собирались начать новую жизнь, и... вот и начала, на этом Острове. Родители погибли, а я выжила лишь чудом. Я добралась до одного из кораблей внешнего кольца, и пролежала там день без сознания, где меня и нашел один из жителей Острова. Если бы не он - скорее всего, я бы там и умерла, на внешнем кольце.";
			link.l1 = "Ясно...";
			link.l1.go = "int_quests";
			npchar.quest.answer_1 = "true";
		break;
		
		case "ansewer_2":
			dialog.text = "А куда? Где и кому я нужна? У меня нет ни дома, ни родных, ни мужа, ни даже сколь бы то ни было значительных сбережений. Я нигде не была на свете, кроме лондонских трущоб и этого Острова. И знаете - здесь в сто раз лучше, чем в Лондоне. Видно, судьба моя жить тут...";
			link.l1 = "Вы так уверены?..";
			link.l1.go = "int_quests";
			npchar.quest.answer_2 = "true";
		break;
		
		case "ansewer_3":
			dialog.text = "В основном помогаю брату Юлиану в церкви. Но также иногда выполняю мелкую работу в магазине у Акселя. Тем и зарабатываю. Я же девушка, и мне не под силу лазить по корабельным обломкам внешнего кольца.";
			link.l1 = "Ну да...";
			link.l1.go = "int_quests";
			npchar.quest.answer_3 = "true";
		break;
		
		case "ansewer_4":
			dialog.text = "Хи-хи... ухажеры-то есть, да толку нет. Не люб мне из них никто, а жить с мужчиной, который не по нраву - это не для меня. А те, кто симпатичны мне, не замечают меня. Ну да, я ведь всего лишь простая бедная девушка...";
			link.l1 = "Все еще впереди...";
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