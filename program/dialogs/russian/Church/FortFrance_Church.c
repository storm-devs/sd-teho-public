// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Какие вопросы, "+ GetSexPhrase("сын мой","дочь моя") +"?", "Спрашивай, я слушаю тебя..."), "Я слушаю тебя, говори, "+ GetSexPhrase("сын мой","дочь моя") +"...", "И в третий раз говорю тебе, "+ GetSexPhrase("сын мой","дочь моя") +": задавай свой вопрос.",
                          "Столько обязанностей у церковнослужителя, а тут ещё и ты донимаешь, "+ GetSexPhrase("сын мой","дочь моя") +"...", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Я "+ GetSexPhrase("передумал","передумала") +"...", "Не сейчас, падре..."), "Да, пока особо и нечего сказать...",
                      "Задам, задам... Только позже...", "Простите, святой отец...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			// Jason Долго и счастливо
			if (CheckAttribute(pchar, "questTemp.LongHappy") && pchar.questTemp.LongHappy == "choose" && !CheckAttribute(npchar, "quest.LongHappy"))
			{
				link.l1 = "Святой отец, я ищу аббата Бенуа, у меня к нему важное и срочное дело. Не подскажете, где он может быть?";
				link.l1.go = "LH_church";
			}
		break;
		
		// Jason Долго и счастливо
		case "LH_church":
			dialog.text = "Аббат уехал по делам церкви к представителям Испанской Католической миссии в Новом Свете. Подробностей я не знаю, но отца Бенуа нет достаточно долго, чтобы заподозрить, что переговоры затянулись, или - случилось что-то в пути. Мы все немного взволнованы, но нам остается лишь молиться и ждать вестей.";
			link.l1 = "Я и не думал, что все будет легко. Святой отец, скажите, куда именно в испанских колониях отправился аббат. Мне необходимо его найти как можно быстрее.";
			link.l1.go = "LH_church_1";
		break;
		
		case "LH_church_1":
			dialog.text = "Извини, сын мой, но я не знаю. Насколько мне известно - аббат отправился на переговоры с епископом Новой Испании и прелатом инквизиции отцом Винсенто Палотти, но где будет происходить встреча простым слугам Господа никто не уточнял.";
			link.l1 = "Этого достаточно, святой отец, спасибо. Я знаком... в некотором роде с отцом Палотти. Попробую разузнать что-нибудь в Сантьяго.";
			link.l1.go = "LH_church_2";
		break;
		
		case "LH_church_2":
			DialogExit();
			npchar.quest.LongHappy = "true";
			LongHappy_GoToSantiago();
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}



