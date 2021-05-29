// пещерные энкаунтеры
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i;
	string sTemp, sGroup;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	sTemp = "CaveBandos" + locations[FindLocation(npchar.location)].index + "_";
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "Ты что-то хотел?";
			link.l1 = "Да нет, ничего.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		case "CaveBanditosSit":
			if (drand(2) == 1) 
			{
				dialog.text = NPCStringReactionRepeat("Хо-хо, кто к нам пожаловал! Сегодня твой счастливый день, дружок. Мы добрые, вот, кушать готовим... Присоединиться не приглашаю, а вот унести ноги побыстрее - эта возможность у тебя есть.", "Давай-давай, топай отсюда, не мешай нам. Завтра приходи, и кошель не забудь, ха-ха!", "Не зли меня, морячок. Надеюсь, запомнил, где выход из пещеры? Туда и вали, да поживее!", "Ну все, ты меня достал. Придется оторваться от дел насущных и заняться тобой!", "block", 1, npchar, Dialog.CurrentNode);
				link.l1 = HeroStringReactionRepeat("Какой ты добрый, приятель...", "Ты, посмотрю, шутник, однако...", "Ладно, сиди, жарь свои лепешки...", "Вот это деловой разговор!", npchar, Dialog.CurrentNode); 
				link.l1.go = DialogGoNodeRepeat("exit_talk", "exit", "exit", "fight", npchar, Dialog.CurrentNode);
			}
			else
			{
				dialog.text = LinkRandPhrase("Хо-хо, ну надо же! Даже искать добычу не надо - сама явилась... Ну-ка, ребята, порастрясем этого пижона!","Приятель, тебя никто сюда не звал... но раз пришел - мы очень рады! Ну-ка, поглядим, тяжел ли твой кошель!","А ведь тебя никто сюда не тянул, хе-хе... Но раз явился - то мы тебя малость пощекочем, посмотрим, что высыпется из карманов...");
				link.l1 = LinkRandPhrase("Сейчас я тебе язычок-то подкорочу...","Надеюсь, саблей владеешь так же мастерски, как трепешься языком?","Ну что же, пришло время проделать в твоем бренном теле дополнительных пару дырок...");
				link.l1.go = "fight";
			}
			NextDiag.TempNode = "CaveBanditosSit";
		break;
		
		case "CaveBanditosStay":
			dialog.text = LinkRandPhrase("Хо-хо, ну надо же! Даже искать добычу не надо - сама явилась... Ну-ка, ребята, порастрясем этого пижона!","Приятель, тебя никто сюда не звал... но раз пришел - мы очень рады! Ну-ка, поглядим, тяжел ли твой кошель!","А ведь тебя никто сюда не тянул, хе-хе... Но раз явился - то мы тебя малость пощекочем, посмотрим, что высыпется из карманов...");
			link.l1 = LinkRandPhrase("Сейчас я тебе язычок-то подкорочу...","Надеюсь, саблей владеешь так же мастерски, как трепешься языком?","Ну что же, пришло время проделать в твоем бренном теле дополнительных пару дырок...");
			link.l1.go = "fight";
		break;
		
		case "CaveBanditosTreasure":
			dialog.text = NPCStringReactionRepeat("Проваливай отсюда, приятель. Нечего тут шастать!", "Слушай, по-хорошему прошу: уйди отсюда. Неровен час...", "Последний раз предупреждаю: не уйдешь - пожалеешь об этом.", "Ну всё, приятель, ты сам напросился...", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Не указывай мне, что делать, ладно?", "И что тут такого особенного? Пещера и пещера...", "Да ладно тебе...", "Ха! Ну давай, посмотрим, кто крепче!", npchar, Dialog.CurrentNode); 
			link.l1.go = DialogGoNodeRepeat("exit", "exit", "exit", "fight", npchar, Dialog.CurrentNode);
			NextDiag.TempNode = "CaveBanditosTreasure";
		break;
		
		case "CaveCaribSit":
			if (drand(2) == 2) 
			{
				dialog.text = NPCStringReactionRepeat("Бледнолицый уходить прочь. Он радоваться, что "+npchar.name+" добр. Боги сжалиться над тобой сегодня.", "Убираться из мой пещера, пока я и мой братья не злиться!", "Проваливать прочь, бледнолицый пес!", "Твоя удача и жизнь подойти к концу, белая собака!", "block", 1, npchar, Dialog.CurrentNode);
				link.l1 = HeroStringReactionRepeat("Ну спасибо, приятель, удружил...", "Пещера не твоя - хочу и хожу.", "Меньше гонору, сын болота.", "Сейчас я заткну эти слова тебе в глотку, скотина...", npchar, Dialog.CurrentNode); 
				link.l1.go = DialogGoNodeRepeat("exit_talk", "exit", "exit", "fight", npchar, Dialog.CurrentNode);
			}
			else
			{
				dialog.text = LinkRandPhrase("Проклятый бледнолицый пес сам явиться на наш костер! О-ей! Тебе конец!","Глупый яланауи сам прийти в пасть ягуар. Я поджарить твой печень на костер!","Наглый бледнолицый посметь прийти мой пещера? Тогда он не выйти отсюда никогда!");
				link.l1 = LinkRandPhrase("Сейчас я тебе язычок-то подкорочу...","Сейчас несколькими каннибалами на земле меньше станет...","Похоже, настало время проделать в твоем бренном теле пару дырок, краснорожая обезьяна...");
				link.l1.go = "fight";
			}
			NextDiag.TempNode = "CaveCaribSit";
		break;
		
		case "CaveCaribStay":
			dialog.text = LinkRandPhrase("Подлый бледнолицый собака прийти наш пещера! О-ей! Я вырезать твой сердце и зажарить его!","Глупый яланауи сам прийти в пасть ягуар. Братья, рубить проклятый белый пес!","Наглый бледнолицый посметь явиться мой пещера? Тогда он не выйти отсюда никогда!");
			link.l1 = LinkRandPhrase("Сейчас я тебе язычок-то подкорочу...","Сейчас несколькими каннибалами на земле меньше станет...","Похоже, настало время проделать в твоем бренном теле пару дырок, краснорожая обезьяна...");
			link.l1.go = "fight";
		break;
		
		case "exit_talk":
			DialogExit();
			sGroup = "CaveGroup_" + locations[FindLocation(pchar.location)].index;
			for(i=0; i<4; i++)
			{
				sld = CharacterFromID(sTemp + i);
				LAi_CharacterDisableDialog(sld);
			}
			LAi_CharacterEnableDialog(npchar);
		break;
		
		case "fight":
			DialogExit();
			sGroup = "CaveGroup_" + locations[FindLocation(pchar.location)].index;
			for(i=0; i<4; i++)
			{
				sld = CharacterFromID(sTemp + i);
				LAi_SetWarriorTypeNoGroup(sld);
				LAi_group_MoveCharacter(sld, sGroup);
				LAi_RemoveCheckMinHP(sld);
				LAi_SetImmortal(sld, false);
			}
			LAi_group_SetRelation(sGroup, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups(sGroup, LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck(sGroup, "CaveEnc_RaidersAfrer");
			chrDisableReloadToLocation = true;
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}