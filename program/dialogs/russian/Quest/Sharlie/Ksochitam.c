// диалоги НПС по квесту Коварный остров Ксочитэм
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i, n;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "Ты что-то хотел?";
			link.l1 = "Да нет, ничего.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		// капитан-нежить Санта-Квитерии
		case "SQC_skeletcap":
			PlaySound("Types\skel.wav");
			dialog.text = "Тебе... всё равно... придётся... умереть. Он придёт... и убьёт тебя... как убил всех нас... как убил всех тут...";
			link.l1 = "Что? Кто ты? Кто убьёт?";
			link.l1.go = "SQC_skeletcap_1";
		break;
		
		case "SQC_skeletcap_1":
			PlaySound("Types\skel.wav");
			dialog.text = "Он огромен... он неуязвим... он убивать... он убить тебя. Я должен убить тебя... если я убью тебя - ты не станешь, как мы... ты не понимаешь... ты всё равно умрёшь от его меча... превратишься в такого, как мы... Как все на Санта-Квитерии...";
			link.l1 = "Ну уж нет!";
			link.l1.go = "SQC_skeletcap_2";
		break;
		
		case "SQC_skeletcap_2":
			DialogExit();
			LAi_SetWarriorType(npchar);
			LAi_SetImmortal(npchar, false);
			LAi_SetCurHPMax(npchar);
			LAi_GetCharacterMaxEnergy(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			for(i=2; i<=3; i++)
			{
				sld = characterFromId("SQI_skelet_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "Ksochitam_SQCskeletcapdie");
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		// Страж маски Кукулькана
		case "guardmask":
			PlaySound("VOICE\Russian\sharlie\Hranitel Maski Kukulkana.wav");
			dialog.text = "Как долго я тебя ждал!..";
			link.l1 = "Э!.. С ума сойти... вот это скелетище!";
			link.l1.go = "guardmask_1";
		break;
		
		case "guardmask_1":
			dialog.text = "Я вижу её... Я чувствую её... Ты принёс мне... моё освобождение...";
			link.l1 = "О чём ты сейчас говоришь? Кто ты?!";
			link.l1.go = "guardmask_2";
		break;
		
		case "guardmask_2":
			dialog.text = "Я - Страж Ксочитэма, Хранитель маски Кукулькана... и твоя неминуемая смерть!..";
			link.l1 = "...";
			link.l1.go = "guardmask_3";
		break;
		
		case "guardmask_3":
			PlaySound("Ambient\Teno_inside\big_ring.wav");
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			DialogExit();
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "KSOCHITAM_MONSTERS");
			LAi_group_FightGroups("KSOCHITAM_MONSTERS", LAI_GROUP_PLAYER, true);
			AddDialogExitQuest("MainHeroFightModeOn");
			DoQuestFunctionDelay("Terrapin_SetMusic", 1.2);
			n = Findlocation("Shore_mask");
			locations[n].type = "seashore";
			pchar.questTemp.Ksochitam.GuardMaskFight = "true";
			for (i=1; i<=4; i++)
			{
				CreateLocationParticles("fire_incas_Simple", "fire_incas", "fire_incas"+i, 1, 0, 0, "fortfire");
				CreateLocationParticles("fire_incas_Simple", "fire_incas", "fire_incas"+i, 2.5, 0, 0, "fortfire");
			}
		break;
		
		case "guardmask_4":
			PlaySound("VOICE\Russian\sharlie\Hranitel Maski Kukulkana.wav");
			dialog.text = "Остановись...";
			link.l1 = "И зачем же мне это делать, а? Ты на последнем издыхании, мешок костей?";
			link.l1.go = "guardmask_5";
		break;
		
		case "guardmask_5":
			dialog.text = "Нет. Ты не сможешь меня уничтожить, никогда. Даже этим магическим кинжалом. Наш поединок может длиться очень долго, пока ты не потеряешь все силы и не умрёшь.";
			link.l1 = "Да ну? И почему же тогда ты никак не можешь меня добить?";
			link.l1.go = "guardmask_6";
		break;
		
		case "guardmask_6":
			dialog.text = "Ты отважный и сильный воин, и ты носишь дагу 'Коготь вождя'. Я обязан сохранить тебе жизнь, ибо владеющий сей дагой и сумевший выстоять против меня в бою получает то, за чем пришёл.";
			link.l1 = "Кто ты? Кто ты на самом деле, Страж?";
			link.l1.go = "guardmask_7";
		break;
		
		case "guardmask_7":
			dialog.text = "Когда-то меня звали Альберто Каскос. Я был солдатом в отряде Алонсо де Мальдонадо. Мы нашли древний Тайясаль, но были схвачены и принесены в жертву. Меня, за мой рост и силу, язычник Канек преобразил в Стража Ксочитэма, Хранителя маски Кукулькана. Все, кто ступил на Ксочитэм, были найдены и убиты мной, а затем превращены в нежить\nИз моей плоти при помощи даги 'Коготь вождя' была создана карта, по которой владелец даги смог бы отыскать Ксочитэм. До тех пор, пока я не получу в свои руки дагу, я буду вечно хранить безопасность маски, не находя упокоения.";
			link.l1 = "Тебе нужен 'Коготь вождя'?";
			link.l1.go = "guardmask_8";
		break;
		
		case "guardmask_8":
			dialog.text = "Да. Так же как тебе нужна маска. Отдай мне дагу, и я найду долгожданное упокоение, а ты получишь маску. Я клянусь тебе, что ты сможешь её забрать и покинуть Ксочитэм живым.";
			link.l1 = "Я принимаю твоё предложение, Страж. Я видел маску на пьедестале за купелью с фонтаном. Это она?";
			link.l1.go = "guardmask_9";
		break;
		
		case "guardmask_9":
			dialog.text = "Да, это она. Это могущественный артефакт самого Крылатого Змея, Кукулькана. После того, как мы закончим разговор, ты сможешь пойти и забрать её.";
			link.l1 = "Ну что же, я надеюсь, ты сдержишь слово, Страж...";
			link.l1.go = "guardmask_10";
		break;
		
		case "guardmask_10":
			dialog.text = "Я дал клятву...";
			link.l1 = "Тогда возьми 'Коготь вождя'. надеюсь, он принесёт покой твоей душе.";
			link.l1.go = "guardmask_11";
		break;
		
		case "guardmask_11":
			RemoveItems(pchar, "knife_01", 1);
			PlaySound("interface\important_item.wav");
			Log_Info("Вы отдали дагу 'Коготь вождя'");
			RemoveCharacterEquip(pchar, BLADE_ITEM_TYPE);
			dialog.text = "Как долго я ждал этого момента! Теперь я могу уходить... Но на прощание я хочу передать тебе частицу своей силы. Это будет последний подарок, который когда-либо делал Альберто Каскос.";
			link.l1 = "...";
			link.l1.go = "guardmask_12";
		break;
		
		case "guardmask_12":
			DialogExit();
			LAi_SetActorType(pchar);
			DoQuestCheckDelay("Ksochitam_GuardMaskGift", 1.5);
		break;
		
		case "guardmask_13":
			dialog.text = "А теперь мне пора уходить. Ты тоже не задерживайся на Ксочитэме - без своего Стража и маски Кукулькана остров вскоре исчезнет навеки.";
			link.l1 = "Жалеть не о чем. Одним кошмарным местом на земле станет меньше... Но постой, Страж! Ты был в Тайясале! Расскажи - что это за место?";
			link.l1.go = "guardmask_14";
		break;
		
		case "guardmask_14":
			dialog.text = "Это старый город индейцев майя. Он сохранил своё обличие с тех времен, когда там ещё проживал этот народ. Величественные храмы, высокие пирамиды... Теперь его населяют ица, считающие себя прямыми потомками майя. Они стараются во всём следовать им - в религии, культуре и быту.";
			link.l1 = "Как мне попасть в него?";
			link.l1.go = "guardmask_15";
		break;
		
		case "guardmask_15":
			dialog.text = "Путь знал наш командир, Алонсо де Мальдонадо. Мы просто следовали за ним через джугли. Я помню лишь то, что мы высадились на берегу Москитос, это севернее мыса Перлас, и двинулись вглубь сельвы на запад.";
			link.l1 = "Что примечательного есть в Тайясале?";
			link.l1.go = "guardmask_16";
		break;
		
		case "guardmask_16":
			dialog.text = "Там примечательно всё. Абсолютно всё. Но нас интересовали лишь сокровища майя. И мы нашли их. Но поплатились за это, и я лично - в особенности. Но теперь я наконец-то свободен!";
			link.l1 = "Что нужно знать, отправляясь в Тайясаль?";
			link.l1.go = "guardmask_17";
		break;
		
		case "guardmask_17":
			dialog.text = "Ица сильны и коварны. Они ненавидят белых людей, независимо от их национальности, и стремятся уничтожить любого чужака, вторгшегося на их территоррию. Простые воины ица не будут вступать ни в какие переговоры, а вот Канек или его сын Уракан, увидев маску... возможно. Если ты живым сумеешь добраться до Тайясаля - всё поймёшь сам. Но вот сможешь ли ты оттуда уйти...";
			link.l1 = "Канек приносит в жертву всех белых людей, попавших в Тайясаль?";
			link.l1.go = "guardmask_18";
		break;
		
		case "guardmask_18":
			dialog.text = "Я полагаю - да. Но возможно, владельца маски Кукулькана это не коснётся.";
			link.l1 = "Ясно. Буду на это рассчитывать.";
			link.l1.go = "guardmask_19";
		break;
		
		case "guardmask_19":
			dialog.text = "Прощай, солдат. Надеюсь, ты используешь силу маски в правильных целях.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuest("Ksochitam_GuardMaskGoAway");
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}