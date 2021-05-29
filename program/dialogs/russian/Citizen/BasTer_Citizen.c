// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
            dialog.text = RandPhraseSimple("Какие вопросы?", "Что вам угодно?");
			link.l1 = RandPhraseSimple("Я "+ GetSexPhrase("передумал","передумала") +"...", "Сейчас мне не о чем говорить");
		    link.l1.go = "exit";
		break;
		
		case "info":
			dialog.text = LinkRandPhrase("Кто вас интересует?","Кто вам нужен?","О ком пойдет речь?");
			link.l1 = "Я хочу узнать о Фадее Московите.";
			link.l1.go = "fadey";
			link.l2 = "Лучше давайте поговорим о чем-нибудь другом...";
			link.l2.go = "new question";
		break;
		
		case "town":
			dialog.text = LinkRandPhrase("Куда вам нужно попасть?","Что вы ищете?","Куда вы хотите пройти?");
            link.l1 = "Где находится дом Фадея Московита?";
			link.l1.go = "fadey_house";
			link.l2 = "Лучше давайте поговорим о чем-нибудь другом...";
			link.l2.go = "new question";
		break;
		
		case "fadey":
			dialog.text = RandPhraseSimple("Важный человек. Управляет факторией, знается с высшим светом Бас-Тера. Но вот разговаривает как-то странно, и выпить любит... но никогда не пьянеет.","Большая шишка, друг самого губернатора. Управляющий факторией. Прибыл из какой-то далекой северной страны, я даже названия такой не знаю. Силищи в руках на трех здоровяков, а выпить может целый жбан рома и не опьянееет!");
			link.l1 = "Спасибо!";
			link.l1.go = "exit";
		break;
		
		case "fadey_house":
			dialog.text = RandPhraseSimple("Идете от пирса прямо, пока не увидите площадь, дом слева и есть особняк Фадея.","От резиденции губернатора пересекаете площадь по пути к пирсу, справа - дом Фадея.");
			link.l1 = "Спасибо!";
			link.l1.go = "exit";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

