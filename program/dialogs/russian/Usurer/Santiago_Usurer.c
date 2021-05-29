// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Какие вопросы?", "Что вам угодно?"), "Совсем недавно вы пытались задать мне вопрос...", "М-да, позвольте угадаю... Опять ничего существенного?",
                          "Послушайте, я финансами оперирую, а не на вопросы отвечаю...", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Я "+ GetSexPhrase("передумал","передумала") +"...", "Сейчас мне не о чем говорить"), "Хм, что-то с памятью моей стало...",
                      "Вы угадали, простите...", "Я понимаю...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			//Голландский гамбит, Голландия
			if (CheckAttribute(pchar, "questTemp.HWIC.Holl") && pchar.questTemp.HWIC.Holl == "SantiagoTripBegin")
			{
				link.l1 = "Сеньор, я капитан " + GetFullName(pchar) + ", и нахожусь здесь по поручению Лукаса Роденбурга. У меня для вас пакет от него.";
				link.l1.go = "SantiagoTripBank";	
			}
			if (CheckAttribute(pchar, "questTemp.HWIC.Holl") && pchar.questTemp.HWIC.Holl == "SantiagoTripReturn")
			{
				link.l1 = "Я пришел за ответом сеньору Лукасу Роденбургу.";
				link.l1.go = "SantiagoTripBank_3";	
			}
			//Голландский гамбит, Голландия
		break;
		
		case "SantiagoTripBank":
			if (GetCharacterItem(pchar, "Chest") >= 5)
			{
			dialog.text = "Подумать только... пакет! Ну, давайте его сюда, сeньор.";
			link.l1 = "Также сеньор Роденбург  просил передать вам это...";
			link.l1.go = "SantiagoTripBank_1";
			RemoveItems(PChar, "NPC_Letter", 1);
			RemoveItems(PChar, "Chest", 5);
			}
			else
			{
			dialog.text = "Насколько мне известно, кроме пакета должно было быть еще кое-что, капитан. Так где же... это? Вы поняли, о чем я говорю?";
			link.l1 = "Конечно! Сундуки под надежной охраной у меня на корабле. Сейчас я прикажу их доставить.";
			link.l1.go = "exit";
			}
		break;
		
		case "SantiagoTripBank_1":
			dialog.text = "Хм-м... интересно. Значит он, видите ли, 'сожалеет'. Так-так. Впрочем, сожаления сeньора Роденбурга весьма убедительны, тут сложно спорить. Сеньор, мне потребуется время для написания ответа – вас не затруднит зайти ко мне завтра днем, и забрать письмо? Переночуйте в таверне, погуляйте по городу... у нас в Сантьяго есть на что посмотреть.";
			link.l1 = "Хорошо, я зайду завтра днем. До встречи, сeньор.";
			link.l1.go = "SantiagoTripBank_2";
		break;
		
		case "SantiagoTripBank_2":
			DialogExit();
			pchar.quest.SantiagoTripOver.over = "yes"; //снять таймер
			bDisableFastReload = true;
			pchar.quest.Santiago_Trip.win_condition.l1 = "location";
			pchar.quest.Santiago_Trip.win_condition.l1.location = "Santiago_town";
			pchar.quest.Santiago_Trip.function = "SantiagoTrip_Attack";
			pchar.questTemp.HWIC.Holl = "SantiagoTripAttack";
			LAi_LocationDisableOfficersGen("Santiago_town", true);//офицеров не пускать // 291112
		break;
		
		case "SantiagoTripBank_3":
			dialog.text = "Да, конечно... но, я думаю, мы можем обойтись и без письменных условностей. Просто передайте ему на словах - 'этот человек должен умереть'. Это будет честно, и мы не будем иметь никаких претензий, в виду полученного извинения в звонкой форме. А инцидент будем считать исчерпанным в полной мере.";
			link.l1 = "Хорошо, я запомню, сeньор. Что-нибудь еще?";
			link.l1.go = "SantiagoTripBank_4";
		break;
		
		case "SantiagoTripBank_4":
			dialog.text = "Да, конечно. Сказанное мною - это воля семьи Джеральди. И, конечно, передайте мои наилучшие пожелания сеньору Лукасу. Попутного вам ветра, капитан " + GetFullName(pchar) + ".";
			link.l1 = "Я понял. Прощайте, сеньор "+npchar.name+".";
			link.l1.go = "SantiagoTripBank_5";
		break;
		
		case "SantiagoTripBank_5":
			DialogExit();
			pchar.questTemp.HWIC.Holl = "SantiagoTripFinal";
			LAi_LocationDisableOfficersGen("Santiago_town", false);//офицеров пускать // 291112
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

