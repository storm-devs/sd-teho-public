void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, Diag;
	int i, iGun, iMush, qty;
	string sGroup, sLink, sText;
	
	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(Diag, NPChar.Dialog);
	int iTemp = sti(npchar.EncQty);
	string sTemp = "Carib" + locations[FindLocation(npchar.location)].index + "_";

	switch(Dialog.CurrentNode)
	{
		case "exit":
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();			
		break;
		
		case "First time":
			dialog.text = "Явный баг. Сообщите Jason'у, как и при каких обстоятельствах его получили.";
			link.l1 = "Обязательно сообщу!";
			link.l1.go = "exit";
			Diag.TempNode = "First time";
		break;

		case "exit_fight":
			sGroup = "CaribGroup_" + locations[FindLocation(npchar.location)].index;
			for(i = 0; i < iTemp; i++)
			{
				sld = CharacterFromID(sTemp + i);
				LAi_SetWarriorTypeNoGroup(sld);
				LAi_group_MoveCharacter(sld, sGroup);
				LAi_RemoveCheckMinHP(sld);
				LAi_SetImmortal(sld, false);
			}
			LAi_group_SetRelation(sGroup, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups(sGroup, LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck(sGroup, "LandEnc_CaribAfrer");
			DialogExit();	
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "exit_peace":
			DialogExit();
			sGroup = "CaribGroup_" + locations[FindLocation(npchar.location)].index;
			for(i = 0; i < iTemp; i++)
			{
				sld = CharacterFromID(sTemp + i);
				LAi_SetWarriorTypeNoGroup(sld);
				LAi_group_MoveCharacter(sld, sGroup);
				LAi_SetImmortal(sld, false);
				LAi_CharacterDisableDialog(sld);
			}	
			ChangeIndianRelation(0.25);
		break;
		
		// военные индеи - карибы
		case "war_indian":
			for(i = 0; i < iTemp; i++)
			{
				sld = CharacterFromID(sTemp + i);
				LAi_type_actor_Reset(sld);
				LAi_RemoveCheckMinHP(sld);
				LAi_SetImmortal(sld, false);
			}
			if (sti(pchar.questTemp.Indian.relation) > 79)
			{
				dialog.text = LinkRandPhrase("Приветствовать тебя, сын моря! Я слыхать о тебе. Ступать спокойно по наш земля.",""+npchar.name+" приветствовать тебя, бледнолицый брат. Мы рады видеть твоя гости у нас.","Привет тебе, славный бледнолицый воин! "+npchar.name+" рад встрече с друг индеец. Ступать с миром!");
				link.l1 = RandPhraseSimple("Привет и тебе, краснокожий брат! Пусть будет удачна твоя охота!","Приветствую, храбрый воин! Да не обойдут боги вниманием тебя и твою семью!");
				link.l1.go = "exit_peace";
				if (CheckCaribGuns())
				{
					npchar.quest.count = 0;
					link.l2 = RandPhraseSimple("У меня есть то, что интересно тебе, краснокожий брат. Поторгуем?","Я могу предложить тебе кое-что купить, храбрый воин. Будем меняться?");
					link.l2.go = "war_indian_trade";
				}
			}
			else
			{
				dialog.text = LinkRandPhrase("Стоять, бледнолицый! По какому праву ты ходить мой земля?","Стой, белый человек! Ты находиться земля моих предков и мой земля!","Остановись, яланауи! Тебе не место на мой земля!");
				link.l1 = RandPhraseSimple("Твой земля? А ну, прочь с дороги, краснорожая образина!","Ну надо же - обезьяна, а разговаривает! Пошел прочь!");
				link.l1.go = "war_indian_1";
				link.l2 = RandPhraseSimple("Я пришел с миром, краснокожий воин. Ни к чему нам развязывать бой не из-за чего.","Я не посягаю на твою землю, воин. Я пришел с миром.");
				if (sti(pchar.questTemp.Indian.relation)+(makeint(GetSummonSkillFromName(pchar, SKILL_LEADERSHIP)/3)) > drand(80)) link.l2.go = "war_indian_2_1";
				else link.l2.go = "war_indian_2_2";
				link.l3 = RandPhraseSimple("Я пришел сюда не воевать с вами, а торговать.","Я не воюю с индейцами. Я с ними торгую.");
				if (sti(pchar.questTemp.Indian.relation)+(makeint(GetSummonSkillFromName(pchar, SKILL_LEADERSHIP)/6)+makeint(GetSummonSkillFromName(pchar, SKILL_FORTUNE)/6)) > drand(90)) link.l3.go = "war_indian_3_1";
				else link.l3.go = "war_indian_3_2";
			}
		break;
		
		case "war_indian_1":
			dialog.text = RandPhraseSimple("Ты пожалеть, что родиться на этот свет, бледнолицый собака... Я вырезать твое сердце и поджарить огонь!","Я заставить тебя есть камень, белолицый пес! Ты на коленях умолять о смерти!");
			link.l1 = RandPhraseSimple("Ты все не уймешься, чучело крашеное? Ну, я сейчас загоню тебя назад в джунгли, из которых ты выполз...","Ты смеешь мне угрожать, мразь? Сейчас ты побежишь на дерево, с которого только вчера слез...");
			link.l1.go = "exit_fight";
		break;
		
		case "war_indian_2_1":
			dialog.text = RandPhraseSimple("Я слышать твой голос - он говорить правда. Мы не обнажить топор друг против друг сегодня. Идти с миром, бледнолицый.","Бледнолицый редко приходить с мир на наш земля, но я видеть твой глаза - ты не лгать. Ступай.");
			link.l1 = RandPhraseSimple("Ты поступил правильно, воин. Прощай.","Я рад, что мы поняли друг друга, воин.");
			link.l1.go = "exit_peace";
		break;
		
		case "war_indian_2_2":
			dialog.text = RandPhraseSimple("Ты лгать, бледнолицый собака! Вы приходить сюда убивать индеец! Готовь к бой, яланауи!","Вы убивать индеец. Язык бледнолицых - лживый язык. Я вырвать его и поджарить огонь!");
			link.l1 = RandPhraseSimple("Ну раз так, то не обессудь, приятель. Видит Бог, я этого не хотел...","Ну что же, ты сам напросился, горе-вояка...");
			link.l1.go = "exit_fight";
		break;
		
		case "war_indian_3_1":
			if (CheckCaribGuns())
			{
				npchar.quest.count = 0;
				dialog.text = "Торговать? Нам нужен оружие бледнолицых. Одноручный огненный оружие бледнолицых! За него мы быть меняться наш товар! У тебя есть огненный оружие на обмен?";
				link.l1 = "Хм. Есть. А что ты дашь мне взамен?";
				link.l1.go = "war_indian_trade";
				link.l2 = "Ах ты, каналья! А потом ты из моих пистолей будешь отстреливать колонистов? Ну уж нет, не бывать тому! А вас, шакалы, я сейчас всех перережу...";
				link.l2.go = "exit_fight";
			}
			else
			{
				dialog.text = "У тебя нет то, что мы хотеть, бледнолицый... Ты стать наш военный трофей!";
				link.l1 = "Ну, рискни, чучело...";
				link.l1.go = "exit_fight";
			}
		break;
		
		case "war_indian_3_2":
			dialog.text = RandPhraseSimple("Мы не торговать с бледнолицый пес. Мы забирать всё у них сами!","Мы не жалкий мискито или аравак, мы не торговать с яланауи! Мы убивать яланауи и получать военный трофей!");
			link.l1 = RandPhraseSimple("Ну, попробуй ограбить меня, каналья!","Сначала тебе придется забрать у меня саблю, мерзавец!");
			link.l1.go = "exit_fight";
		break;
		
		case "war_indian_trade":
			iGun = 1;
			dialog.text = "Показывать, что у тебя есть, а мы сказать, что дать тебе за это.";
			for (i=6; i>=1; i--)
			{
				if (GetCharacterFreeItem(pchar, "pistol"+i) > 0)
				{
					sLink = "l"+iGun;
					link.(sLink) = "Предложить "+XI_ConvertString("pistol"+i)+".";
					link.(sLink).go = "gun_"+i;
					iGun++;				
				}
			}
		break;
		
		case "gun_1":
			npchar.quest.gun = "pistol1";
			if (drand(1) == 0)
			{
				npchar.quest.item = "potion"+(rand(2)+2);
				iTotalTemp = drand(1)+1;
				sText = ""+FindRussianQtyString(iTotalTemp)+" пузырек хороший целебный зелье";
			}
			else
			{
				npchar.quest.item = "jewelry"+(drand(9)+14);
				iTotalTemp = drand(2)+1;
				sText = ""+FindRussianQtyString(iTotalTemp)+" вот этот красивый камень";
			}
			dialog.text = "О-ей! Мы дать тебе за него "+sText+".";
			link.l1 = "По рукам!";
			link.l1.go = "war_indian_trade_agree";
			link.l2 = "Нет. Не пойдет.";
			link.l2.go = "war_indian_trade_bad";
		break;
		
		case "gun_2":
			npchar.quest.gun = "pistol2";
			if (drand(3) < 2)
			{
				npchar.quest.item = "potion"+(rand(2)+2);
				iTotalTemp = drand(2)+2;
				sText = ""+FindRussianQtyString(iTotalTemp)+" пузырек хороший целебный зелье";
			}
			else
			{
				npchar.quest.item = "jewelry"+(drand(3)+1);
				iTotalTemp = drand(2)+2;
				sText = ""+FindRussianQtyString(iTotalTemp)+" вот этот красивый камень";
			}
			dialog.text = "О-ей! Хитрый оружие... Мы дать тебе за него "+sText+".";
			link.l1 = "По рукам!";
			link.l1.go = "war_indian_trade_agree";
			link.l2 = "Нет. Не пойдет.";
			link.l2.go = "war_indian_trade_bad";
		break;
		
		case "gun_3":
			npchar.quest.gun = "pistol3";
			if (drand(5) < 3)
			{
				qty = rand(1)+2;
				npchar.quest.item = "jewelry5"+qty;
				iTotalTemp = drand(6)+qty*15;
				sText = ""+FindRussianQtyString(iTotalTemp)+" вот этот красивый жемчужина";
			}
			else
			{
				npchar.quest.item = "jewelry"+(drand(2)+2);
				iTotalTemp = drand(2)+5;
				sText = ""+FindRussianQtyString(iTotalTemp)+" вот этот красивый камень";
			}
			dialog.text = "О-ей! Это сильный оружие! Бить сразу много-много врагов! Мы дать тебе за него "+sText+".";
			link.l1 = "По рукам!";
			link.l1.go = "war_indian_trade_agree";
			link.l2 = "Нет. Не пойдет.";
			link.l2.go = "war_indian_trade_bad";
		break;
		
		case "gun_4":
			npchar.quest.gun = "pistol4";
			if (drand(9) < 8)
			{
				qty = rand(1)+1;
				npchar.quest.item = "jewelry"+(qty+4);
				iTotalTemp = drand(10)+qty*30;
				sText = ""+FindRussianQtyString(iTotalTemp)+" кусок этот металл, который бледнолицый любить больше жизни";
			}
			else
			{
				npchar.quest.item = "obereg_"+(drand(10)+1);
				iTotalTemp = 1;
				sText = "вот этот амулет";
			}
			dialog.text = "О-ей! Страшный оружие! Мы дать тебе за него "+sText+".";
			link.l1 = "По рукам!";
			link.l1.go = "war_indian_trade_agree";
			link.l2 = "Нет. Не пойдет.";
			link.l2.go = "war_indian_trade_bad";
		break;
		
		case "gun_5":
			npchar.quest.gun = "pistol5";
			if (drand(7) < 7)
			{
				if (drand(10) < 8)
				{
					npchar.quest.item = "jewelry7";
					iTotalTemp = 2+drand(1);
				}
				else
				{
					npchar.quest.item = "jewelry8";
					iTotalTemp = drand(4)+10;
				}
				qty = drand(1)+1;
				npchar.quest.item = "jewelry"+(qty+6);
				if (qty == 1) iTotalTemp = 2;
				else iTotalTemp = drand(5)+qty*15;
				sText = ""+FindRussianQtyString(iTotalTemp)+" вот этот красивый и ценный каменный смола";
			}
			else
			{
				npchar.quest.item = "indian_"+(drand(10)+1);
				iTotalTemp = 1;
				sText = "вот этот амулет";
			}
			dialog.text = "О-ей! Красивый и мощный оружие! Мы дать тебе за него "+sText+".";
			link.l1 = "По рукам!";
			link.l1.go = "war_indian_trade_agree";
			link.l2 = "Нет. Не пойдет.";
			link.l2.go = "war_indian_trade_bad";
		break;
		
		case "gun_6":
			npchar.quest.gun = "pistol6";
			if (drand(9) < 8)
			{
				qty = rand(1)+1;
				npchar.quest.item = "jewelry"+(qty+4);
				iTotalTemp = drand(8)+qty*20;
				sText = ""+FindRussianQtyString(iTotalTemp)+" кусок этот металл, который бледнолицый любить больше жизни";
			}
			else
			{
				npchar.quest.item = "amulet_"+(drand(10)+1);
				iTotalTemp = 1;
				sText = "вот этот амулет";
			}
			dialog.text = "О-ей! Удобный оружие! Мы дать тебе за него "+sText+".";
			link.l1 = "По рукам!";
			link.l1.go = "war_indian_trade_agree";
			link.l2 = "Нет. Не пойдет.";
			link.l2.go = "war_indian_trade_bad";
		break;
		
		case "war_indian_trade_agree":
			ChangeIndianRelation(0.3);
			npchar.quest.count = sti(npchar.quest.count)+1;
			TakeNItems(pchar, npchar.quest.item, iTotalTemp);
			RemoveItems(pchar, npchar.quest.gun, 1);
			Log_Info("Вы отдали "+XI_ConvertString(npchar.quest.gun)+"");
			Log_Info("Вы получили "+XI_ConvertString(npchar.quest.item)+" в количестве "+FindRussianQtyString(iTotalTemp)+"");
			PlaySound("interface\important_item.wav");
			if (sti(npchar.quest.count) > 3+drand(2));
			{
				dialog.text = "Хорошо. Вот твой товар. Больше мы не менять. Приносить потом. Чем лучше огненный оружие - тем дороже мы его купить. Ступай!";
				link.l1 = "Прощай, краснокожий воин.";
				link.l1.go = "exit_peace";
			}
			else
			{
				dialog.text = "Хорошо. Вот твой товар. У тебя есть еще огненный оружие на менять?";
				if (CheckCaribGuns())
				{
					link.l1 = "Есть. Будешь покупать?";
					link.l1.go = "war_indian_trade";
				}
				link.l2 = "Пока нет. В следующий раз принесу еще.";
				link.l2.go = "war_indian_trade_exit";
			}
		break;
		
		case "war_indian_trade_exit":
			dialog.text = "Приносить. Чем лучше огненный оружие - тем дороже мы его купить. Ступай!";
			link.l1 = "До встречи, воин...";
			link.l1.go = "exit_peace";
		break;
		
		case "war_indian_trade_bad":
			if (sti(pchar.questTemp.Indian.relation) > 79)
			{
				DialogExit();
				sGroup = "CaribGroup_" + locations[FindLocation(npchar.location)].index;
				for(i = 0; i < iTemp; i++)
				{
					sld = CharacterFromID(sTemp + i);
					LAi_SetWarriorTypeNoGroup(sld);
					LAi_group_MoveCharacter(sld, sGroup);
					LAi_SetImmortal(sld, false);
					LAi_CharacterDisableDialog(sld);
				}	
			}
			else
			{
				dialog.text = "Тогда мы забрать всё и просто так, яланауи!";
				link.l1 = "Ну, попробуй...";
				link.l1.go = "exit_fight";
			}
		break;
		
		// мирные индеи - мискито
		case "peace_indian":
			for(i = 0; i < iTemp; i++)
			{
				sld = CharacterFromID(sTemp + i);
				LAi_type_actor_Reset(sld);
				LAi_RemoveCheckMinHP(sld);
				LAi_SetImmortal(sld, false);
			}
			dialog.text = LinkRandPhrase("Здравствуй, белый человек. Что тебе нужно в наши джунгли?","Наши джунгли много опасность. Что ты делать тут?","Что привести тебя сюда, храбрый бледнолицый?");
			link.l1 = RandPhraseSimple("Я просто прохожу мимо, краснокожий друг. Надеюсь, на этой тропе нам обоим хватит места?","Приветствую, сын джунглей! Дела привели меня сюда. Но я не враждую с индейцами.");
			link.l1.go = "peace_indian_1";
			link.l2 = RandPhraseSimple("А тебе до этого какое дело? Иди своей дорогой и не нарывайся!","Топай себе дальше, краснокожий. Мне не до бесед с тобой.");
			link.l2.go = "peace_indian_2";
		break;
		
		case "peace_indian_1":
			dialog.text = RandPhraseSimple("Мы мирный народ. Мы не враждовать белый человек. Ступай, но будь острожен на наши тропы!","Я рад видеть бледнолицый - друг индеец. Ступать с мир, сын моря!");
			link.l1 = RandPhraseSimple("И тебе удачи, сын сельвы...","Прощай, краснокожий друг.");
			link.l1.go = "exit_peace";
		break;
		
		case "peace_indian_2":
			dialog.text = RandPhraseSimple("Мы просто мирный охотники. Но не терпеть, чтобы нам так говорить на наш земля!","Мы не воевать с белый, но если белый обнажить против нас топор или слово - мы ответить ему, как учить наши предки!");
			link.l1 = RandPhraseSimple("Ты все не уймешься, краснокожая образина? Ну, я сейчас загоню тебя назад в джунгли, из которых ты выполз...","Ты смеешь мне угрожать, мразь? Сейчас ты побежишь на дерево, с которого только вчера слез...");
			link.l1.go = "exit_fight";
		break;
	}
}