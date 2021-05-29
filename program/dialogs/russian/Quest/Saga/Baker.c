// Раймонд Бейкер - палач Сент-Джонса и возможный офицер
void ProcessDialogEvent()
{
	ref NPChar, sld, rItm, rItem;
	aref Link, NextDiag, rType;
	int i;
	string 	sAttr, sGun, sBullet, attrL;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	sAttr = Dialog.CurrentNode;
	if (findsubstr(sAttr, "SetGunBullets1_" , 0) != -1)
 	{
        i = findsubstr(sAttr, "_" , 0);
	 	NPChar.SetGunBullets = strcut(sAttr, i + 1, strlen(sAttr) - 1); // индекс в конце
 	    Dialog.CurrentNode = "SetGunBullets2";
 	}
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "Вы что-то хотели?";
			link.l1 = "Да нет, ничего.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		case "baker":
			dialog.text = "Благодарю вас, капитан! Даже не знаю, что бы я без вас делал...";
			link.l1 = "Зато я знаю: умерли бы с голоду, или оказались в желудке дикарей с Доминики. Но у вас есть шанс отплатить за моё добро.";
			link.l1.go = "baker_1";
		break;
		
		case "baker_1":
			dialog.text = "Чем могу служить, капитан?";
			link.l1 = "Меня интересует один человек. Он наш общий знакомый, так скажем. Причём вам он был знаком очень близко. Я говорю о капитане Бучере. Да, том самом, которого вы повесили двадцать лет назад. Господи, да что же вы так побледнели? Глоток рому?";
			link.l1.go = "baker_2";
		break;
		
		case "baker_2":
			dialog.text = "Вы... вы от него?";
			link.l1 = "Что за чушь! Как я могу быть 'от него', если он давно уже мёртв! Меня интересует не сколько сам Бучер, сколько то, что могло остаться после него. Какие-нибудь письма, документы. Может быть что-то было в карманах его камзола... Постойте! Я что-то не понял. Вы что, считаете, что Бучер - жив? Вы же сами казнили его!";
			link.l1.go = "baker_3";
		break;
		
		case "baker_3":
			dialog.text = "Фу-у-у! Вы ничего не знаете. Значит вы не от Бучера, а я уж было подумал...";
			link.l1 = "Так-так. Становится всё занятнее и занятнее. Значит, Генри недаром боялся Бучера, и недаром его удар прикончил... Получается, Бучер жив?";
			link.l1.go = "baker_4";
		break;
		
		case "baker_4":
			dialog.text = "Это так, капитан... И они ищут меня.";
			link.l1 = "Раймонд, мне вас представляли как неглупого человека. Не нужно со мной хитрить. Кто бы ни угрожал вам, под моей защитой вы в безопасности. Расскажите мне всё, что знаете, а я подумаю, как вам помочь. Возможно, у нас общие враги, и мне не придётся делать это специально. Начнём с Бучера.";
			link.l1.go = "baker_5";
		break;
		
		case "baker_5":
			dialog.text = "Он жив! Только зовут его теперь иначе. В ночь казни ко мне пришли его люди. Джекман и ещё один со странным прозвищем. Кажется, 'Утопленник'.";
			link.l1 = "Висельник. Генри Висельник.";
			link.l1.go = "baker_6";
		break;
		
		case "baker_6":
			dialog.text = "Точно! Они предложили мне умереть в муках, если я не спасу их капитана. Ну мне и пришлось инсценировать казнь при помощи приспособления, которое я разработал от нечего делать. Такая конструкция из ремней и зажимов, равномерно распределяющая вес тела\nДостаточно прицепить её сзади к незаметному крюку в петле и дело сделано. Главное чтобы 'покойник' вел себя правдоподобно. Нужно сказать, что Лоуренс оказался способным учеником и сделал всё правильно, только мочиться отказался наотрез, потому что видите ли...";
			link.l1 = "Вы назвали Бучера Лоуренсом?";
			link.l1.go = "baker_7";
		break;
		
		case "baker_7":
			dialog.text = "Это его настоящее имя. Я же говорю, что его теперь зовут по-другому. Лоуренс Белтроп. С тех пор как он появился на Карибах год назад, я места себе не нахожу. А уж когда узнал, что меня ищут какие-то угрюмые люди, совсем потерял голову от страха\nЯ уже и признание написал для властей. Ношу вот постоянно с собой, а отдать боюсь. Вдруг решат, что я был добровольным помощником. Я вас умоляю, оставьте меня в своей команде. Ей-Богу, я отличный врач и могу быть полезен.";
			link.l1 = "Хорошо. Что на счёт личных вещей Бучера... э-э-э, Белтропа? Он случайно не родственник Томаса Белтропа?";
			link.l1.go = "baker_8";
		break;
		
		case "baker_8":
			dialog.text = "Не знаю. Собственно от Белтропа у меня ничего особого нет. Но я вам отдам всё, что есть, и делайте с этим, что хотите. У меня в саквояже есть все бумаги, которые так или иначе касались этого дела. Я всё сохранил, на всякий случай, и теперь ношу с собой\nВот смотрите... это легенда о капитане Бучере, а вот это - моё письменное подтверждение инсценировки казни... Вот вещи, принадлежавшие Джошуа Ледбиттеру...";
			link.l1 = "Стоп! Кто такой Ледбиттер?";
			link.l1.go = "baker_9";
		break;
		
		case "baker_9":
			dialog.text = "О-о-о! Это очень серьёзный человек. Тот, кто поймал самого Бучера. Народ запомнил его, как 'человека в маске'. Его убили сразу после казни Бучера. Акульим зубом по горлу... Вжик, и нет человека! Он, наверное, очень страдал при жизни\nВидели бы вы его лицо под маской! Сплошное месиво! Так вот у него была в кармане вот эта страничка из дневника. Должно быть, это рука Джессики Роуз. Жуткая история! Вы почитайте легенду, многое станет понятно\nА вот это тот самый зуб. На нём выцарапаны инициалы С.Д. Чтобы это значило? Видите, тут даже пятна крови ещё...";
			link.l1 = "Достаточно! Мне нужно всё внимательно прочитать и хорошенько подумать. А вы остаётесь у меня пассажиром, или врачом - это уже как получится, до тех пор, пока я не разберусь со всем этим делом. Можете успокоиться, Раймонд, у меня на борту вы в безопасности.";
			link.l1.go = "baker_10";
		break;
		
		case "baker_10":
			DialogExit();
			sld = characterFromId("Baker_Cap");
			LAi_SetImmortal(sld, false);
			sld.lifeday = 0;
			//sld.ship.hp = 0;
			//sld.SinkTenPercent = true;
			bQuestDisableMapEnter = false;
			GiveItem2Character(pchar, "shark_teeth");
			GiveItem2Character(pchar, "letter_jess");
			GiveItem2Character(pchar, "letter_baker"); // показания бейкера
			ChangeItemDescribe("letter_baker", "itmdescr_letter_baker"); // Addon-2016 Jason
			AddQuestRecordInfo("Legend_CapBucher", "1");
			AddQuestRecordInfo("Letter_jess", "1");
			AddQuestRecord("Shadows", "5");
			pchar.questTemp.Saga.Shadows = "islatesoro";
			// в офицеры
			npchar.quest.OfficerPrice = sti(pchar.rank)*500;
			npchar.OfficerWantToGo.DontGo = true; //не пытаться уйти
			npchar.CompanionDisable = true; //нельзя в компаньоны
			npchar.loyality = MAX_LOYALITY;
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, true);
			npchar.Payment = true;
			npchar.DontClearDead = true;
			NextDiag.CurrentNode = "Baker_officer";
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			SaveCurrentNpcQuestDateParam(npchar, "HiredDate");
			AddCharacterExpToSkill(pchar, "Sailing", 50);
			AddCharacterExpToSkill(pchar, "Fortune", 100);
		break;
		
		//--> ----------------------------------- офицерский блок ------------------------------------------
		case "Baker_officer":
			dialog.text = "Да, капитан?";
			Link.l1 = "Слушай мой приказ!";
            Link.l1.go = "stay_follow";
			
			////////////////////////казначей///////////////////////////////////////////////////////////
           	// boal отчёт о корабле
			if(CheckAttribute(NPChar, "treasurer") && NPChar.treasurer == 1)
			{
			    Link.l11 = "Раймонд, дай мне полный отчёт о корабле.";
			    Link.l11.go = "QMASTER_1";

			    // Warship. Автозакупка товара
				Link.l12 = "Я хочу, чтобы во время стоянки в колонии ты закупал товары.";
				Link.l12.go = "QMASTER_2";
			}
			
			link.l2 = "Пока ничего. Вольно!";
			link.l2.go = "exit";
			NextDiag.TempNode = "Baker_officer";
		break;
		
		/////////////////////////// ответы для казначея ///////////////////////////////////
        case "QMASTER_1":
			dialog.Text = "Капитан, так я же врач, а не казначей. Ну, раньше ещё была другая у меня профессия... Но не хочу обо всём этом вспоминать. Я правда не разбираюсь в счёте товаров, прошу извинить.";
			Link.l1 = "Ладно, согласен: когда я тебя брал в команду, мы договаривались, что ты будешь врачом.";
			Link.l1.go = "exit";
		break;	

		case "QMASTER_2":
			dialog.text = "Капитан, я торговлей, если честно, никогда не занимался. Цен не знаю, торговаться не умею. Да и... боюсь я с корабля куда-то ходить без вас, тем более, к купцам. Вдруг кто-нибудь признает, и на следующую ночь за мной придут люди в масках...";
			link.l1 = "Эх, так и будешь жить в страхе перед своим прошлым всю жизнь... Ладно, успокойся, товары я сам закупать буду.";
			Link.l1.go = "exit";
        break;
		
		case "stay_follow":
            dialog.Text = "Какие быть приказания?";
            Link.l1 = "Стой здесь!";
            Link.l1.go = "Boal_Stay";
            Link.l2 = "Следуй за мной и не отставай!";
            Link.l2.go = "Boal_Follow";
			sGun = GetCharacterEquipByGroup(NPChar, GUN_ITEM_TYPE);
			if(sGun != "")
			{
				rItm = ItemsFromID(sGun);
				if(CheckAttribute(NPChar, "chr_ai.bulletNum") && sti(NPChar.chr_ai.bulletNum) > 1)
				{
					Link.l3 = "Нужно изменить тип боеприпаса для твоего огнестрельного оружия.";
					Link.l3.go = "SetGunBullets";
				}	
			}		
		break;
		
		case "SetGunBullets":
			Dialog.Text = "Выбор типа боеприпаса:";
			sGun = GetCharacterEquipByGroup(NPChar, GUN_ITEM_TYPE);
			rItm = ItemsFromID(sGun);
			makearef(rType, rItm.type);	
			for (i = 0; i < sti(NPChar.chr_ai.bulletNum); i++)
			{
				sAttr = GetAttributeName(GetAttributeN(rType, i));
				sBullet = rItm.type.(sAttr).bullet;
				rItem = ItemsFromID(sBullet);								
				attrL = "l" + i;
				Link.(attrL) = GetConvertStr(rItem.name, "ItemsDescribe.txt");;
				Link.(attrL).go = "SetGunBullets1_" + i;
			}
		break;	

		case "SetGunBullets2":
			i = sti(NPChar.SetGunBullets) + 1; 
			sGun = GetCharacterEquipByGroup(NPChar, GUN_ITEM_TYPE);
			rItm = ItemsFromID(sGun);
			sAttr = "t" + i;
			sBullet = rItm.type.(sAttr).bullet;
			LAi_SetCharacterUseBullet(NPChar, sBullet);
			LAi_GunSetUnload(NPChar);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DeleteAttribute(NPChar,"SetGunBullets");
			DialogExit();
		break;		
		
        case "Boal_Stay":
            Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(Npchar.id);
            AddDialogExitQuestFunction("LandEnc_OfficerStay");
            dialog.Text = "Есть изменить дислокацию!";
            Link.l1 = "Вольно.";
            Link.l1.go = "Exit";
            Npchar.chr_ai.tmpl = LAI_TMPL_STAY;
        break;
        
        case "Boal_Follow":
            SetCharacterTask_FollowCharacter(Npchar, PChar);
            dialog.Text = "Есть изменить дислокацию!";
            Link.l1 = "Вольно.";
            Link.l1.go = "Exit";
        break;
	//<-- ----------------------------------- офицерский блок ----------------------------------------
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}