//Jason общий диалог дворянок
#include "DIALOGS\russian\Rumours\Common_rumours.c"
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;

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
			//первая встреча
            if(NPChar.quest.meeting == "0")
			{
				if (sti(NPChar.nation) != PIRATE && GetNationRelation2MainCharacter(sti(NPChar.nation)) == RELATION_ENEMY)//проверка межнациональных отношений
				{
					dialog.text = "Хм. Вы ходите под флагом "+NationNameGenitive(sti(pchar.nation))+", капитан. У меня нет никакого желания общаться с врагом моей державы. Уходите прочь!";
					link.l1 = "Тоже мне, патриотка...";
					link.l1.go = "exit";
				}
				else
				{
					dialog.text = RandPhraseSimple("Что вы хотели от меня, "+GetAddress_Form(NPChar)+"? Не пристало морякам приставать с расспросами к знатной даме, но я всё же выслушаю вас.", "Ой, и что же может быть от меня нужно такому бравому капитану, а?");
					link.l1 = TimeGreeting()+", "+GetAddress_FormToNPC(NPChar)+". Я не задержу вас надолго, просто хочу спросить...";
					link.l1.go = "question";
					link.l2 = RandPhraseSimple("Мне нужна узнать, что творится в вашей колонии.", "Мне нужна информация.");
					link.l2.go = "quests";//(перессылка в файл города)
				}
				npchar.quest.meeting = "1";
			}
			else
			{
				//повторные обращения
				if (sti(NPChar.nation) != PIRATE && GetNationRelation2MainCharacter(sti(NPChar.nation)) == RELATION_ENEMY)
				{
					dialog.text = "Я что, непонятно выражаюсь? Я не желаю, чтобы меня заподозрили в связи с "+NationNameAblative(sti(pchar.nation))+"! Уходите, или я позову стражу! Они-то точно будут рады с вами побеседовать.";
					link.l1 = "Ладно-ладно, не кипятитесь. Ухожу.";
					link.l1.go = "exit";
				}
				else
				{
				dialog.text = NPCStringReactionRepeat("Что? Опять? Поищите для болтовни кого-нибудь другого. Тут полно бездельников, слоняющихся по улицам. А мне пора - вечером приём у губернатора, а у меня ещё причёска не готова...", 
					"Нет, это уже начинает действительно утомлять! Вы что, не понимаете с первого раза? Вы медленно соображаете?", 
					"Сударь, я начинаю подозревать, что вы не тупица, а деревенщина и хам. Предупреждаю: будете приставать с глупыми расспросами - позову мужа!",
					"Так, ещё одно слово - и я сообщу коменданту, чтобы в отношении вас были приняты меры!", "block", 1, npchar, Dialog.CurrentNode);
				link.l1 = HeroStringReactionRepeat("Понятно. Всего доброго.", 
					"Да-да, я помню, просто забыл спросить вот что...",
					"Вы меня неправильно поняли...", 
					"Не злитесь, сударыня, я уже ухожу.", npchar, Dialog.CurrentNode);
				link.l1.go = DialogGoNodeRepeat("exit", "", "", "", npchar, Dialog.CurrentNode);
				}
			}
			NextDiag.TempNode = "First time";
		break;

		//сюда вставляем любые проверки и направления на квесты
		case "question":
			dialog.text = LinkRandPhrase("Ну, давайте послушаем, так и быть.","Ох, ну хорошо. Что вы хотите?","Вопросы задавать будем? Ладно, моряк, слушаю.");
			link.l1 = LinkRandPhrase("Не расскажете последние новости вашего города?","Расскажите пожалуйста, что интересного в последнее время произошло?","Что интересного творится на архипелаге, сударыня, вы не в курсе?");
			link.l1.go = "rumours_noblegirl";
			NextDiag.TempNode = "First time";
		break;

		//замечание по обнаженному оружию от персонажей типа citizen
		case "CitizenNotBlade":
			dialog.text = NPCharSexPhrase(NPChar, "Послушайте, я, как гражданин этого города, прошу вас не ходить у нас с обнажённым клинком.", "Знаете, я, как гражданка этого города, прошу вас не ходить у нас с обнажённым клинком.");
			link.l1 = LinkRandPhrase("Хорошо.", "Ладно.", "Как скажете...");
			link.l1.go = "exit";
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
