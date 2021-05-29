// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
 	switch(Dialog.CurrentNode)
	{
        case "quests":
            dialog.text = "Говорите, я слушаю.";
			link.l1 = "Я "+ GetSexPhrase("ошибся","ошиблась") +". Прощайте.";
			link.l1.go = "Exit";
			//Португалец
			if (CheckAttribute(pchar, "questTemp.Portugal") && pchar.questTemp.Portugal == "PortugalInPrison")
            {
                link.l1 = "Офицер, у вас содержится пленник - Бартоломео Португалец...";
                link.l1.go = "Portugal";
            }
		break;
		
		//Португалец
		case "Portugal":
			dialog.text = "Содержится. А вам какое дело? К нему допускаются только представители Голландской Вест-Индской Компании, и то - только с письменного разрешения губернатора. Один из офицеров Компании как раз допрашивает этого пирата. Так что если вы явились, чтобы его увидеть - вам лучше уйти, и побыстрее.";
			link.l1 = "Я явился не для того, чтобы его увидеть.";
			link.l1.go = "Portugal_1";
		break;
		
		case "Portugal_1":
			dialog.text = "А для чего же, позвольте спросить?";
			link.l1 = "Для того, чтобы забрать его!";
			link.l1.go = "fight";
			chrDisableReloadToLocation = true;
			pchar.quest.InMarigoResidenceOver.over = "yes"; //снять таймер
			InterfaceStates.Buttons.Save.enable = false;//запретить сохраняться
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
