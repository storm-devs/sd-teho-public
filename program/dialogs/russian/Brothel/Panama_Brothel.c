// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    ref sld;    
	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Какие вопросы, "+ GetSexPhrase("молодой человек","юная леди") +"?", "Чего ты хочешь, "+ GetSexPhrase("красавчик","красотка") +"? Ну хоть задай его."), "Опять вопросы?", "Хи-хи, третий раз на дню одно и то же - вопросы...",
                          ""+ GetSexPhrase("Хм, может ты выберешь какую-нибудь красотку себе? А то у меня уже складывается в отношении тебя вполне определенное мнение...","Хм, может ты выберешь какую-нибудь красотку себе? Мальчиков не держим, хи-хи...") +"", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Я передумал...", "Хм, да ничего..."), "Не могу... Нет вопросов...",
                      "Да уж, действительно в третий раз... Извини.", "Не сейчас... В другой раз...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

