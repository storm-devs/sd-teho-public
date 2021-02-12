// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    ref sld;
	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Какие вопросы, "+ GetSexPhrase("молодой человек","юная леди") +"?", "Чего ты хочешь, "+ GetSexPhrase("красавчик","красотка") +"? Ну хоть задай его."), "Опять вопросы?", "Хи-хи, третий раз на дню одно и то же - вопросы...",
                          ""+ GetSexPhrase("Хм, может ты выберешь какую-нибудь красотку себе? А то у меня уже складывается в отношении тебя вполне определённое мнение...","Хм, может ты выберешь какую-нибудь красотку себе? Мальчиков не держим, хи-хи...") +"", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Я передумал...", "Хм, да ничего..."), "Не могу... Нет вопросов...",
                      "Да уж, действительно в третий раз... Извини.", "Не сейчас... В другой раз...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			//Голландский гамбит
			if (CheckAttribute(pchar, "questTemp.HWIC.Eng") && pchar.questTemp.HWIC.Eng == "GotoBridgetown" && !CheckAttribute(npchar, "quest.HWICTalked"))
            {
                link.l1 = "Я тут закупился красным деревом на продажу и отправляюсь в Блювельд. Впереди - большой переход, команды у меня мало, ребята нервничают... Сколько будет стоить отдых для пяти десятков моих матросов?";
                link.l1.go = "BrothelDone";
            }
		break;
		
		case "BrothelDone":
			dialog.text = "Пять десятков - пятнадцать тысяч.";
			link.l1 = "Ого! Немало... Ладно, ещё подумаю над этим.";
			link.l1.go = "exit";	
			npchar.quest.HWICTalked = "true";
			pchar.questTemp.HWIC.Eng.BridgeCounter = sti(pchar.questTemp.HWIC.Eng.BridgeCounter)+1;
			AddQuestRecord("Holl_Gambit", "2-7");
			if (sti(pchar.questTemp.HWIC.Eng.BridgeCounter) == 7) 
			{
			AddQuestRecord("Holl_Gambit", "2-6");
			pchar.quest.GotoBridgetownOver.over = "yes";//снять таймер
			pchar.questTemp.HWIC.Eng = "SeekVanBerg";
				pchar.quest.VanBergAttack_Check.win_condition.l1 = "MapEnter";
				pchar.quest.VanBergAttack_Check.function = "VanBergAttackCheck";
				//if(sti(RealShips[sti(pchar.ship.type)].basetype) != SHIP_VALCIRIA || GetCompanionQuantity(pchar) > 1) AddDialogExitQuestFunction("FailVanBergInWorld");
				//else AddDialogExitQuestFunction("CreateVanBergInWorld");
			}
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

