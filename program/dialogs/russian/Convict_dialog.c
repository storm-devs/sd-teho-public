// диалог каторжников в шахте
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;
	string sTemp;
	bool bOk;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = NPCStringReactionRepeat("Сеньор, будет лучше для нас обоих, если мы не будем с вами разговаривать. Меня могут высечь, а вас попросят уйти.", "Я вам уже все сказал, сеньор. Или вы хотите, чтобы я из-за вас получил плетей?", "Я вас не слушаю...", "Стучи-ит лопа-ата, звени-ит кирка...", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Суровые тут у вас порядки...", "Нет, не хочу, конечно.", "Да ну!", "Гм...", npchar, Dialog.CurrentNode); 
			link.l1.go = DialogGoNodeRepeat("exit", "", "", "", npchar, Dialog.CurrentNode);
			NextDiag.TempNode = "First time";
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
			
		case "CitizenNotBlade":
			dialog.text = "Капитан, что за глупости! Уберите оружие, пока бед не наделали!";
			link.l1 = LinkRandPhrase("Хорошо.", "Ладно.", "Не переживай, уже убираю...");
			link.l1.go = "exit";
		break;  
	}
}
