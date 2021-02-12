// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Какие вопросы?", "Что вам угодно, " + GetAddress_Form(NPChar) + "?"), "Совсем недавно вы пытались задать мне вопрос, " + GetAddress_Form(NPChar) + "...", "В течение этого дня вы уже третий раз говорите о каком-то вопросе...",
                          "Опять вопросы будем задавать?", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Я "+ GetSexPhrase("передумал","передумала") +"...", "Сейчас мне не о чем говорить"), "Хм, что-то с памятью моей стало...",
                      "Да уж, действительно в третий раз...", "Да нет, какие вопросы...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			//Jason, суп из черепахи
			if (CheckAttribute(PChar, "questTemp.Terrapin") && pchar.questTemp.Terrapin == "baster" && !CheckAttribute(npchar, "quest.terrapin"))
			{
				link.l1 = "Я ищу своего старого приятеля Фернана Люка. У меня к нему есть пара вопросов. Слышал, он тут неплохо проводил время неделю назад...";
				link.l1.go = "terrapin";
			}
		break;
		
		//суп из черепахи
		case "terrapin":
			dialog.text = "Возможно, он и сейчас его неплохо проводит, только в окружении чертей. Склеил ласты твой приятель. Так что ты малость припоздал, капитан. Вон тот господин, за самым дальним столиком, оплатил его похороны, хотя сдается мне, что он и стал их причиной. Уж больно рожа у него бандитская. Его зовут Робер Мартэн, если хочешь, можешь задать ему свои вопросы. ";
			link.l1 = "Спасибо, приятель. Пойду, потолкую с месье Робером. Выпьем за упокой души несчастного Люка...";
			link.l1.go = "terrapin_1";
			npchar.quest.terrapin = "true";
		break;
		
		case "terrapin_1":
			DialogExit();
			AddQuestRecord("Terrapin", "4");
			pchar.questTemp.Terrapin = "rober";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

