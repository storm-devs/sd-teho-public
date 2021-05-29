// диалог освобожденных каторжников рудника
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = NPCStringReactionRepeat("Опять вы, сеньор?", 
				"Слушайте, сударь, шли бы вы своей дорогой...", 
				"Отстаньте, сударь! По-хорошему прошу.",
                "Ох, сил моих нет... На руднике и то легче было.", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Да, опять я.", 
				"Не указывай мне, что делать.",
                "А если по-плохому?", 
				"Ну так вернись в шахты!", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "Что вы хотели, сеньор?";
				link.l1 = "От тебя? Пожалуй, ничего. Просто поздоровался.";
				link.l1.go = "exit";
				npchar.quest.meeting = "1";
			}
			NextDiag.TempNode = "First time";
		break;

		//замечание по обнаженному оружию от персонажей типа citizen
		case "CitizenNotBlade":
			dialog.text = NPCharSexPhrase(NPChar, "Не искушай судьбу, приятель! Убери свою саблю!", "Знаете, я, как гражданка этого города, прошу вас не ходить у нас с обнажённым клинком.");
			link.l1 = LinkRandPhrase("Хорошо.", "Ладно.", "Как скажешь...");
			link.l1.go = "exit";
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
