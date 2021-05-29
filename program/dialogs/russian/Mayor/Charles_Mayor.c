// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Что вы хотели? Спрашивайте.", "Я слушаю вас, что за вопрос?"), "Второй раз за день вы пытаетесь задать ворпос...", "В третий раз за день вы опять пытаетесь задать вопрос...",
                          "Да когда же это кончится?! У меня дел полно по управлению делами города, а ты все вопросы пытаешься задать!", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Я передумал"+ GetSexPhrase("","а") +"...", "Не сейчас, не место и не время..."), "Да, верно... Но не сейчас, позже...",
                      "Задам, задам... Только позже...", "Извините, " + GetAddress_FormToNPC(NPChar) + "...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			//--> Бремя гасконца
			if (CheckAttribute(pchar, "questTemp.Sharlie") && pchar.questTemp.Sharlie == "saga" && !CheckAttribute(npchar, "quest.saga"))
			{
				link.l1 = "Я хочу встретиться с шевалье де Пуанси, по поводу долга моего брата.";
                link.l1.go = "puancie";
			}
			//<-- Бремя гасконца
		break;
		
		case "puancie":
			dialog.text = "А-а, ну, я в курсе этого дела... У вас есть с собой требуемая сумма?";
			if (sti(pchar.money) >= 1000000)
			{
				link.l1 = "Конечно! А как же иначе?";
				link.l1.go = "puancie_1";
			}
			else
			{
				link.l1 = "Нет, таких денег у меня пока нет.";
				link.l1.go = "puancie_exit";
			}
		break;
		
		case "puancie_exit":
			dialog.text = "Тогда приходите, когда они у вас будут, и не беспокойте шевалье по пустякам.";
			link.l1 = "...";
			link.l1.go = "exit";
		break;
		
		case "puancie_1":
			dialog.text = "В таком случае проходите в дверь справа. Шевалье примет вас.";
			link.l1 = "Спасибо!";
			link.l1.go = "puancie_2";
		break;
		
		case "puancie_2":
			DialogExit();
			npchar.quest.saga = "true";
			bDisableFastReload = true;//закрыть переход
			LocatorReloadEnterDisable("Charles_townhall", "reload1_back", true);//чтобы не вышел
			LocatorReloadEnterDisable("Charles_townhall", "reload3", false);//откроем вход к Пуанси
			ref sld = characterFromId("Puancie");
			ChangeCharacterAddressGroup(sld, "Charles_Roomtownhall", "sit", "sit1");
			LAi_SetHuberType(sld);
			sld.dialog.currentnode = "saga";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

