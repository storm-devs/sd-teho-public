// Куранай - индеец
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
				dialog.text = "Я не желать с тобой общаться. Ты нападать без причины на мирных граждан. Уходи прочь!";
				link.l1 = "Гм...";
				link.l1.go = "exit";
				break;
			}
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "Что хотеть белый брат?";
				link.l1 = TimeGreeting()+". Белый брат? Вот скажи, почему у вас, индейцев, мы либо - белый брат, либо - бледнолицый собака, а?";
				link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "Куранай рад видеть бледнолицый брат.";
				link.l1 = LinkRandPhrase("Что-нибудь интересное мне расскажешь?", "Что нового произошло на острове в последнее время?", "Не расскажешь ли последние сплетни?");
				link.l1.go = "rumours_LSC";
				link.l2 = "Я хочу задать тебе пару вопросов об острове.";
				link.l2.go = "int_quests"; //информационный блок
				if (CheckAttribute(npchar, "quest.answer_2"))
				{
					link.l3 = "Покажи, что тебе удалось насобирать. Может, я куплю чего-нибудь...";
					link.l3.go = "trade";
				}
				link.l5 = "Да просто решил узнать как у тебя дела. Ещё увидимся!";
				link.l5.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting": // первая встреча
			dialog.text = "Здесь мы все жить в мире, белый брат. Куранай не называть белый брат бледнолицый собака. Не все бледнолицый - собака. А я про многий индеец могу сказать - краснокожий пёс.";
			link.l1 = "Хм. Да ты - философ, как я посмотрю...";
			link.l1.go = "meeting_1";
		break;
		
		case "meeting_1":
			dialog.text = "Куранай не понимать тебя, белый брат. Что значить - философ?";
			link.l1 = "Не обращай внимания, краснокожий брат. Мне просто понравился ход твоих мыслей. Ты сказал, тебя зовут Куранай? Ну а я - "+GetFullName(pchar)+". Будем знакомы.";
			link.l1.go = "meeting_2";
		break;
		
		case "meeting_2":
			dialog.text = "Куранай рад узнать имя бледнолицый брат.";
			link.l1 = "Ладно. Ещё увидимся!";
			link.l1.go = "exit";
			link.l3 = "Я хочу задать тебе пару вопросов об острове.";
			link.l3.go = "int_quests"; //информационный блок
			NextDiag.TempNode = "First time";
		break;
		
		case "trade":
			DialogExit();
			if (!CheckAttribute(npchar, "trade_date") || GetNpcQuestPastDayParam(npchar, "trade_date") >= 4)
			{
				GiveItemToTrader(npchar);
				SaveCurrentNpcQuestDateParam(npchar, "trade_date");
			}
			LaunchItemsTrade(npchar, 0);
		break;
		
		case "":
			dialog.text = "";
			link.l1 = "";
			link.l1.go = "";
		break;
		
//--------------------------------------- блок вопросов и ответов ---------------------------------------------
		case "int_quests":
			dialog.text = "Спрашивать, бледнолицый брат, Куранай отвечать.";
			if (!CheckAttribute(npchar, "quest.answer_1"))
			{
				link.l1 = "Как тебя-то угораздило попасть на Остров?";
				link.l1.go = "ansewer_1";
			}
			if (!CheckAttribute(npchar, "quest.answer_2"))
			{
				link.l2 = "Чем ты занимаешься здесь, на Острове?";
				link.l2.go = "ansewer_2";
			}
			if (!CheckAttribute(npchar, "quest.answer_3"))
			{
				link.l3 = "Ты хотел бы вернуться домой?";
				link.l3.go = "ansewer_3";
			}
			if (!CheckAttribute(npchar, "quest.answer_4"))
			{
				link.l4 = "Вы мирно здесь живёте на острове? Драк, ссор не бывает?";
				link.l4.go = "ansewer_4";
			}
			link.l10 = "Нет вопросов. Извини...";
			link.l10.go = "exit";
		break;
		
		case "ansewer_1":
			dialog.text = "Я с несколько воин мой племя решить доплыть до небольшой островок близко от наш земля, его было видать в ясный день. Мы сделать плот из бамбук и поплыть. Но нас внезапно подхватить волны и вынести в открытый море. Мы не успеть даже понять, как островок и наш земля исчезнуть за горизонт\nНас швырять по море много день, много ночь. Все мои братья погибнуть от жажда и голод. Я остаться один - духи сжалиться над Куранай и направить плот к этот остров. Я спастись.";
			link.l1 = "Да уж... Печальная история.";
			link.l1.go = "int_quests";
			npchar.quest.answer_1 = "true";
		break;
		
		case "ansewer_2":
			dialog.text = "Куранай ловить рыба. Куранай бить рыба гарпун. Иногда бить гарпун большой краб, но редко-редко. Тогда у Куранай праздник - краб вкусный, очень вкусный. Один клешня хватать на несколько день. А ещё Куранай нырять на дно в один место, когда там нет большой краб. Куранай доставать со дна жёлтый камень, голубой камень и чёрный камень, большой и малый жемчуг, и продавать бледнолицый.";
			link.l1 = "Понятно...";
			link.l1.go = "int_quests";
			npchar.quest.answer_2 = "true";
		break;
		
		case "ansewer_3":
			dialog.text = "Куранай хотеть вернуться домой. Но где мой дом? Куранай не знать, где его деревня, и как туда добраться. Даже если кто-то взяться отвезти Куранай, я не смочь сказать, куда плыть. Духи решить, что Куранай должен жить тут.";
			link.l1 = "Гм. Ну что тут ещё добавить...";
			link.l1.go = "int_quests";
			npchar.quest.answer_3 = "true";
		break;
		
		case "ansewer_4":
			dialog.text = "Нарвал и ривадос часто драться, один против один. Мы жить мирно, никого не трогать. Иногда бледнолицый напиваться огненный вода и ругаться, но никто никого не убивать. Есть на остров два офицер-воин - они ненавидеть друг друга. Однажды один убить одного, Куранай быть уверен.";
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