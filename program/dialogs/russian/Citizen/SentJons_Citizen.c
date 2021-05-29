// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
            dialog.text = RandPhraseSimple("Какие вопросы?", "Что вам угодно?");
			link.l1 = RandPhraseSimple("Я "+ GetSexPhrase("передумал","передумала") +"...", "Сейчас мне не о чем говорить");
		    link.l1.go = "exit";
			//Jason, суп из черепахи
			if (CheckAttribute(PChar, "questTemp.Terrapin") && pchar.questTemp.Terrapin == "baster" && !CheckAttribute(npchar, "quest.terrapin") && CheckAttribute(PChar, "questTemp.Terrapin.SJ_count"))
			{
				link.l1 = "Я ищу господина Джонса. Не знаете такого?";
				link.l1.go = "terrapin";
			}
		break;
		
		case "terrapin":
			if (sti(pchar.questTemp.Terrapin.SJ_count) == 5 || rand(9) == 1) // 10% или числом
			{
				dialog.text = "Вообще-то Джонсов у нас тут много. Но самый известный из тех, кого я знаю – денщик полковника Фокса, Бенджамин Джонс. Он обычно встречает посетителей в штабе полка.";
				link.l1 = "А у него есть сестра Молли?";
				link.l1.go = "terrapin_yes";
			}
			else
			{
				dialog.text = LinkRandPhrase("Какой именно Джонс вам нужен? Я знаю не менее двух десятков.","У нас Джонсов, как грибов поганых. Поточнее можете сказать?","Да тут Джонсов не меньше, чем Джонсонов или Джексонов. Может, примету какую назовете?");
				link.l1 = "У него есть взрослая сестра Молли. Говорят, редкая красавица...";
				link.l1.go = "terrapin_no";
			}
			npchar.quest.terrapin = "true";
		break;
		
		case "terrapin_no":
			dialog.text = RandPhraseSimple(LinkRandPhrase("Хм. Боюсь, ничем не смогу помочь.","Не знаю такого.","Ну, если ту Молли Джонс, которую я знаю, считать красавицей, то нашего полковника Фокса можно считать настоятелем церкви."), LinkRandPhrase("Я знаю несколько Молли Джонс. У одной из них действительно есть братец, но это не те, кого вы ищете. Назвать Молли красавицей может только человек, всю жизнь проведший среди обезьян.","Увы, но все мои знакомые Джонсы сестер не имеют.","Жаль, но подсказать не могу. Спросите у кого-нибудь еще."));
			link.l1 = "Извините за беспокойство...";
			link.l1.go = "exit";
			pchar.questTemp.Terrapin.SJ_count = sti(pchar.questTemp.Terrapin.SJ_count)+1;
		break;
		
		case "terrapin_yes":
			dialog.text = "Есть, но лучше бы ей было родиться парнем. С такой рожей этой верзиле вряд ли удастся найти себе жениха.";
			link.l1 = "Спасибо за помощь!";
			link.l1.go = "terrapin_yes_1";
		break;
		
		case "terrapin_yes_1":
			DialogExit();
			AddQuestRecord("Terrapin", "2");
			pchar.questTemp.Terrapin.Benjamin = true;
			DeleteAttribute(pchar, "questTemp.Terrapin.SJ_count");
		break;
		
		case "info":
        // заменить на описание неких НПС, по квестам
			dialog.text = "Я что, работаю на тайную агентурную сеть для "+NationNameGenitive(sti(NPChar.nation))+"?";
			link.l1 = "Ну ладно... тогда пока.";
			link.l1.go = "exit";
			link.l2 = "Тогда другой вопрос";
			link.l2.go = "new question";
		break;
		
		case "town":
        // заменить на описание как пройти, по квестам
			dialog.text = "Я вам что справочная? Не знаю. Ничего не ведаю.";

            link.l1 = "Вот бестолочь! Пока.";
			link.l1.go = "exit";
			link.l2 = "Тогда другой вопрос";
			link.l2.go = "new question";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

