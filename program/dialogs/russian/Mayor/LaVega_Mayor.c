// заместитель Маркуса Тиракса в Ла Веге
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	string sLoc;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

// ------------------------------------------блок angry-----------------------------------------------
    if (CheckAttribute(npchar, "angry") && !CheckAttribute(npchar, "angry.ok"))
    {
        npchar.angry.ok = 1;
        if (!CheckAttribute(npchar, "angry.first")) //ловушка первого срабатывания
        {
            NextDiag.TempNode = NextDiag.CurrentNode;
            Dialog.CurrentNode = "AngryExitAgain";
            npchar.angry.first = 1;
        }
        else
        {
            switch (npchar.angry.kind) //сюда расписываем реакцию ангри. В npchar.angry.name пробелы удалены!!!
            {
                case "repeat":
                    if (npchar.angry.name == "Firsttime") Dialog.CurrentNode = "AngryRepeat_1";
                    if (npchar.angry.name == "I_know_you_good") Dialog.CurrentNode = "AngryRepeat_2";
                break;
            }
        }
    }
// ------------------------------------------блок angry-----------------------------------------------

	switch(Dialog.CurrentNode)
	{
		// ----------------------------------- Диалог первый - первая встреча
		case "First time":
            dialog.text = NPCStringReactionRepeat(""+ GetSexPhrase("У тебя дело ко мне? Нет? Тогда вали отсюда!","Ха, " + pchar.name + "! У тебя дело ко мне? Нет? Тогда не отвлекай меня.") +"",
                         "Я кажется ясно выразился.", "Хотя я выразился и ясно, но ты продолжаешь отвлекать меня!",
                         "Та-а-ак, это уже похоже на грубость, меня это утомило.", "repeat", 3, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Уже ухожу.",
                                               "Конечно "+npchar.name+"...",
                                               "Извини, "+npchar.name+"...",
                                               "Ой...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;

 		case "Exit":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
		break;

        case "I_know_you_good":
            dialog.text = NPCStringReactionRepeat(GetFullName(pchar) + ", рад тебя видеть! Зачем пожаловал"+ GetSexPhrase("","а") +" на этот раз?",
                         "Ну что тебе еще?", "Долго это будет продолжаться? Если тебе делать нечего, не отвлекай других!",
                         "Ты неплохой человек, я знаю. Но общаться и разговаривать с тобой я больше не желаю.", "repeat", 10, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Да, собственно, просто так заглянул проведать. Ничего по делу нет.",
                                               "Ничего, просто так...",
                                               "Хорошо, "+npchar.name+", извини...",
                                               "Вот черт возьми, доиграл"+ GetSexPhrase("ся","ась") +"!!!", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			NextDiag.TempNode = "I_know_you_good";
		break;

		// ============== Грабеж среди бела дня, попытка залезть в сундуки =========================
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("Грабеж среди бела дня!!! Это что же такое делается?! Ну, погоди, "+ GetSexPhrase("приятель","подруга") +"...", "Эй, ты чего это там копаешься?! Никак, вздумал"+ GetSexPhrase("","а") +" ограбить меня? Ну, тогда тебе конец...", "Постой, ты куда это полез"+ GetSexPhrase("","ла") +"? Да ты вор"+ GetSexPhrase("","овка") +", оказывается! Ну, считай, что ты приплыл"+ GetSexPhrase("","а") +", родн"+ GetSexPhrase("ой","ая") +"...");
			link.l1 = LinkRandPhrase("Дьявол!!", "Каррамба!!", "А-ать, черт!");
			link.l1.go = "PL_Q3_fight";
		break;
					
		// ======================== блок нод angry ===============>>>>>>>>>>>>>>>
		case "AngryRepeat_1":
            dialog.text = RandPhraseSimple(""+ GetSexPhrase("Пошел вон","Убирайся") +" отсюда!", "Вон из моего дома!");
			link.l1 = "Ай...";
		    link.l1.go = "AngryExitAgainWithOut";
            if (CheckAttribute(npchar, "angry.terms")) //примиряемся через 10 дней.
            {
                if (GetNpcQuestPastDayParam(npchar, "angry.terms") > sti(npchar.angry.terms))
                {
         			dialog.text = "Тебе не стоит отвлекать меня от дела пустыми обращениями. Впредь результат может быть более плачевным...";
        			link.l1 = "Я понял"+ GetSexPhrase("","а") +".";
        			link.l1.go = NextDiag.TempNode;
        			CharacterDelAngry(npchar);
                }
            }
    	break;
		case "AngryRepeat_2":
            dialog.text = RandPhraseSimple("Ты меня изрядно утомил"+ GetSexPhrase("","а") +", никакого общения.", "Я не хочу с тобой общаться, так что тебе лучше меня не беспокоить.");
			link.l1 = RandPhraseSimple("Ну как знаешь...", "Хм, ну что же...");
		    link.l1.go = "AngryExitAgain";
            if (CheckAttribute(npchar, "angry.terms")) //примиряемся через 10 дней.
            {
                if (GetNpcQuestPastDayParam(npchar, "angry.terms") > sti(npchar.angry.terms))
                {
         			dialog.text = "Надеюсь, впредь ты не будешь утомлять меня пустыми разговорами, иначе мне придется тебя убить. Признаюсь, мне это будет очень неприятно.";
        			link.l1 = ""+npchar.name+", ты можешь быть уверен - не буду...";
        			link.l1.go = NextDiag.TempNode;
        			CharacterDelAngry(npchar);
                }
            }
    	break;
		case "AngryExitAgain":
            DialogExit();
            DeleteAttribute(npchar, "angry.ok");
		break;
		case "AngryExitAgainWithOut":
            DialogExit();
            DeleteAttribute(npchar, "angry.ok");
            DoReloadCharacterToLocation("Lavega_town","reload","reload6");
		break;
		// <<<<<<<<<<<<============= блок нод angry =============================
	}
}
