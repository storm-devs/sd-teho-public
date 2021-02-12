void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i, iTemp;
	string sTemp;
	
	DeleteAttribute(&Dialog,"Links");
	
	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "Явный баг в коде. Сообщите Jason'у, как и при каких обстоятельствах его получили.";
			link.l1 = "Обязательно сообщу!";
			link.l1.go = "exit";
		break;
		
		//разговор на палубе
		case "MarginCap":
			dialog.text = "Здравствуйте, капитан. Вы что-то от меня хотели, раз подошли так близко к моему судну?";
			link.l1 = "Да. Именно так, "+GetAddress_FormToNPC(NPChar)+". У вас на борту в пассажирах находится интересующий меня человек, а именно - "+pchar.GenQuest.Marginpassenger.q1Name+". Я хочу, чтобы ваш пассажир стал моим пассажиром. Если вы не будете против этого возражать, то мы спокойно разойдемся и, возможно, более никогда не увидимся.";
			link.l1.go = "MarginCap_1";
		break;
	
		case "MarginCap_1":
			dialog.text = "Вот как? А если я буду возражать против этого вашего хотения?";
			link.l1 = "Тогда мне придется образумить вас несколькими бортовыми залпами моих пушек, которые направлены как раз в вашу сторону. Не стоит искушать судьбу, "+GetAddress_FormToNPC(NPChar)+".";
			link.l1.go = "MarginCap_2";
		break;
		
		case "MarginCap_2":
			int MCparam = (6-sti(RealShips[sti(pchar.ship.type)].Class))*100+sti(pchar.ship.Crew.Morale)+sti(pchar.Ship.Crew.Exp.Sailors)+sti(pchar.Ship.Crew.Exp.Cannoners)+sti(pchar.Ship.Crew.Exp.Soldiers);
			int NPCparam = (6-sti(RealShips[sti(npchar.ship.type)].Class))*100+sti(npchar.ship.Crew.Morale)+sti(npchar.Ship.Crew.Exp.Sailors)+sti(npchar.Ship.Crew.Exp.Cannoners)+sti(npchar.Ship.Crew.Exp.Soldiers);
			if (MCparam > NPCparam)//отдаст сам
			{
				dialog.text = "Пожалуй, у меня нет выбора. Судьба всего экипажа важнее судьбы одного человека. Но вам это так просто с рук не сойдет, имейте это в виду! Я это так не оставлю!";
				link.l1 = "Не кипятитесь, удар хватит... Приведите сюда моего нового пассажира!";
				link.l1.go = "MarginCap_3";
			}
			else
			{
				dialog.text = "Убирались бы вы на свое корыто, сударь, пока я вам это позволяю. Нечего тут меня пугать. Только посмейте атаковать мое судно - получите достойный отпор. Проваливайте, пока я окончательно не вышел из себя!";
				link.l1 = "Ну, я вас предупредил. А теперь мне действительно пора на свой корабль. До скорой встречи, "+GetAddress_FormToNPC(NPChar)+"!";
				link.l1.go = "MarginCap_4";
			}
		break;
	
		case "MarginCap_3":
			DialogExit();
			npchar.Dialog.CurrentNode = "MarginCap_repeat";
			//отдаем пассажира
			sld = GetCharacter(NPC_GenerateCharacter("MarginPass", pchar.GenQuest.Marginpassenger.model, pchar.GenQuest.Marginpassenger.sex, pchar.GenQuest.Marginpassenger.ani, 2, sti(pchar.GenQuest.Marginpassenger.Nation), -1, true, "quest"));
			sld.Dialog.Filename = "Quest\Marginpassenger.c";
			sld.Dialog.currentnode = "MarginPass";
			sld.name = pchar.GenQuest.Marginpassenger.q1Name;
			sld.lastname = "";
			GetCharacterPos(pchar, &locx, &locy, &locz);
			ChangeCharacterAddressGroup(sld, pchar.location, "goto", LAi_FindNearestFreeLocator("goto", locx, locy, locz));
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
			Map_ReleaseQuestEncounter(npchar.id);
			npchar.Abordage.Enable = false; // запрет абордажа
			npchar.ShipEnemyDisable = true;
			npchar.AlwaysFriend = true;
			ChangeCharacterNationReputation(pchar, sti(npchar.Nation), -1);
		break;
		
		case "MarginCap_4":
			DialogExit();
			NextDiag.CurrentNode = "MarginCap_repeat";
			pchar.GenQuest.Marginpassenger.Mustboarding = "true";
			AddQuestRecord("Marginpassenger", "5");
			AddQuestUserData("Marginpassenger", "sShipType", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.Marginpassenger.ShipType), "Name")+"Acc")));
			AddQuestUserData("Marginpassenger", "sShipName", pchar.GenQuest.Marginpassenger.ShipName);
			ChangeCharacterNationReputation(pchar, sti(npchar.Nation), -1);
		break;
		
		case "MarginCap_repeat":
			dialog.text = "Мы уже все обсудили, не так ли? Убирайтесь с моего судна!";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "MarginCap_repeat";
		break;
		
		case "MarginCap_abordage":
			if (CheckAttribute(pchar, "GenQuest.Marginpassenger.Mustboarding"))
			{
				dialog.text = "Аргх, мерзавец! Гореть тебе в аду за твои злодеяния!";
				link.l1 = "Я же предлагал тебе решить вопрос миром... ты не захотел. Теперь пеняй на себя!";
				link.l1.go = "MarginCap_abordage_1";
			}
			else
			{
				dialog.text = "Аргх, мерзавец! Зачем ты напал на мирное судно? У нас нет ни золота, ни ценных товаров!";
				link.l1 = "Зато у тебя на борту есть ценный человек... "+pchar.GenQuest.Marginpassenger.q1Name+". Мне нужен твой пассажир.";
				link.l1.go = "MarginCap_abordage_2";
			}
		break;
		
		case "MarginCap_abordage_1":
			dialog.text = "Ты... гнусный негодяй!";
			link.l1 = "Меньше громких слов, сударь...";
			link.l1.go = "MarginCap_abordage_3";
		break;
		
		case "MarginCap_abordage_2":
			dialog.text = "И только ради этого ты учинил резню на моем судне? Погибло столько людей! Ах ты, гнусный негодяй!";
			link.l1 = "Меньше громких слов, сударь...";
			link.l1.go = "MarginCap_abordage_3";
		break;
		
		case "MarginCap_abordage_3":
			DialogExit();
			LAi_SetCurHPMax(npchar);
			QuestAboardCabinDialogFree();
			LAi_group_SetRelation(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck(LAI_GROUP_BRDENEMY, "Marginpassenger_GivePrisoner");
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "MarginNeed":
			dialog.text = "Что вам угодно, "+GetAddress_Form(NPChar)+"?";
			link.l1 = "Вы - "+pchar.GenQuest.Marginpassenger.q2Name+"?";
			link.l1.go = "MarginNeed_1";
		break;
		
		case "MarginNeed_1":
			dialog.text = "Да, это я. Вы что, хотите подать прошение? Тогда вам следует знать...";
			link.l1 = "Подождите, сударь. У меня прошение несколько... иного рода. Вам знакома особа по имени "+pchar.GenQuest.Marginpassenger.q1Name+"?";
			link.l1.go = "MarginNeed_2";
		break;
		
		case "MarginNeed_2":
			switch (pchar.GenQuest.Marginpassenger.sex)
			{
				case "woman":
					dialog.text = "Да, я знаю эту девушку... Еще бы! А в чем дело?";
					link.l1 = "Она попала в одну неприятную историю: корабль, на котором она путешествовала, захватили пираты. Волею счастливого случая я абордировал корабль этих пиратов и освободил бедняжку. Она назвала мне ваше имя - вот я и пришел к вам.";
					link.l1.go = "MarginNeed_woman";
				break;
				case "man":
					dialog.text = "Да, я хорошо знаю этого человека. А в чем дело?";
					link.l1 = "Он попал в одну неприятную историю: корабль, на котором он путешествовал, захватили пираты. Волею счастливого случая я абордировал корабль этих пиратов и освободил пленника. Он назвал мне ваше имя - вот я и пришел к вам.";
					link.l1.go = "MarginNeed_man";
				break;
			}
		break;
		
		case "MarginNeed_woman":
			dialog.text = "Какой ужас! Где она сейчас? И почему вы не привели ее с собой?";
			link.l1 = "Она в безопасности. Что касается вашего второго вопроса - тут немного сложнее. Я мог бы отвезти ее домой сам, но учитывая то, что вы... что она вам небезразлична, то я мог бы уступить эту возможность вам. За скромное вознаграждение, конечно.";
			link.l1.go = "MarginNeed_woman_1";
		break;
		
		case "MarginNeed_woman_1":
			dialog.text = "Кхм... Что-то я не понимаю...";
			link.l1 = "Ну что тут непонятного? Вы платите мне золото, я передаю вам девушку, а вы уже используете эту ситуацию в своих целях... Вы ведь хотите на ней жениться, так? А я починю на эти деньги корабль, поистрепавшийся в битве с пиратами.";
			link.l1.go = "MarginNeed_money";
		break;
		
		case "MarginNeed_man":
			dialog.text = "Какой ужас! Где он сейчас? И почему его нет вместе с вами?";
			link.l1 = "Он в безопасности. Что касается вашего второго вопроса - тут немного сложнее. Я мог бы отвезти его домой сам, но учитывая то, что вы... что у вас есть определенные интересы в отношении его семьи, я мог бы уступить эту возможность вам. За скромное вознаграждение, конечно.";
			link.l1.go = "MarginNeed_man_1";
		break;
		
		case "MarginNeed_man_1":
			dialog.text = "Кхм... Что-то я не понимаю...";
			link.l1 = "Ну что тут непонятного? Вы платите мне золото, я передаю вам вашего знакомого, а вы уже используете эту ситуацию в своих целях. Мне ведь кое-что известно... А я починю на эти деньги корабль, поистрепавшийся в битве с пиратами.";
			link.l1.go = "MarginNeed_money";
		break;
		
		case "MarginNeed_money":
			dialog.text = "Так-так... И сколько же вы за это хотите?";
			link.l1 = "Сразу оговорюсь - мне нужны дублоны, а не песо.";
			link.l1.go = "MarginNeed_money_1";
		break;
		
		case "MarginNeed_money_1":
			dialog.text = "Хорошо-хорошо... Так сколько дублонов вы хотите?";
			Link.l1.edit = 1;			
			link.l1 = "";
			link.l1.go = "MarginNeed_money_2";
		break;
		
		case "MarginNeed_money_2":
		iTemp = sti(dialogEditStrings[1]);
		int iSum = makeint(sti(pchar.GenQuest.Marginpassenger.Dublon)*5*stf(pchar.GenQuest.Marginpassenger.Chance));
		if (iTemp <= 0)
		{
			dialog.text = "Очень смешно! Хорошо, будем считать, что ваш розыгрыш вам удался. Прощайте!";
			link.l1 = "Гм...";
			link.l1.go = "MarginNeed_exit";
			break;
		}
		if (iTemp > 0 && iTemp <= iSum)
		{
			if (drand(2) > 1) // Addon-2016 Jason уменьшаем раздачу дублонов
			{
				dialog.text = "Хорошо, я согласен. У меня есть с собой требуемая сумма. Где "+pchar.GenQuest.Marginpassenger.q1Name+"?";
				link.l1 = "Должно быть, уже на пирсе. Так что идите, принимайте пассажира.";
				link.l1.go = "MarginNeed_dublon";
			}
			else
			{
				dialog.text = "К сожалению, у меня нет такого количества дублонов. Песо вас не устроит?";
				link.l1 = "Хм. Нужны, конечно, дублоны, но, думаю, хозяин верфи возьмет и песо... Давайте песо.";
				link.l1.go = "MarginNeed_peso";
				link.l2 = "Нет. Мне нужны именно дублоны.";
				link.l2.go = "MarginNeed_dublon_exit";
			}
			break;
		}
		if (iTemp > iSum && iTemp < 1000)
		{
			dialog.text = "К сожалению, такой суммы у меня нет. Так что при всем своем желании я не смогу пойти на ваше предложение. Прощайте!";
			link.l1 = "Гм...";
			link.l1.go = "MarginNeed_exit";
			break;
		}
		if (iTemp > 1000 && iTemp < 3000)
		{
			dialog.text = "Сударь, вы отдаете себе отчет? Вы вообще представляете, какие это деньги? Убирайтесь к черту!";
			link.l1 = "Гм...";
			link.l1.go = "MarginNeed_exit";
			break;
		}
			dialog.text = "М-да... Сударь, вам стоит обратиться к лекарю, и немедленно. У вас определенно жар, или... впрочем, вам в любом случае требуется квалифицированная помощь. А мне тут некогда с вами. Прощайте!";
			link.l1 = "Гм...";
			link.l1.go = "MarginNeed_exit";
		break;
		
		case "MarginNeed_dublon":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "", -1);
			npchar.lifeday = 0;
			sld = characterFromId("MarginPass");
			RemovePassenger(Pchar, sld);
			sld.lifeday = 0;
			iTemp = sti(dialogEditStrings[1]);
			TakeNItems(pchar, "gold_dublon", iTemp);
			AddQuestRecord("Marginpassenger", "9");
			AddQuestUserData("Marginpassenger", "sSum", iTemp);
			CloseQuestHeader("Marginpassenger");
			DeleteAttribute(Pchar, "GenQuest.Marginpassenger");
			AddCharacterExpToSkill(pchar, "Fortune", 100);//везение
		break;
		
		case "MarginNeed_peso":
			dialog.text = "Вот сумма в пересчете на песо, которую вы хотите... Где "+pchar.GenQuest.Marginpassenger.q1Name+"?";
			link.l1 = "Должно быть, уже на пирсе. Так что идите, принимайте пассажира.";
			link.l1.go = "MarginNeed_peso_1";
		break;
		
		case "MarginNeed_peso_1":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "", -1);
			npchar.lifeday = 0;
			sld = characterFromId("MarginPass");
			RemovePassenger(Pchar, sld);
			sld.lifeday = 0;
			iTemp = sti(dialogEditStrings[1])*100;
			AddMoneyToCharacter(pchar, iTemp);
			AddQuestRecord("Marginpassenger", "10");
			AddQuestUserData("Marginpassenger", "sSum", FindRussianMoneyString(iTemp));
			CloseQuestHeader("Marginpassenger");
			DeleteAttribute(Pchar, "GenQuest.Marginpassenger");
			AddCharacterExpToSkill(pchar, "Fortune", 80);//везение
		break;
		
		case "MarginNeed_dublon_exit":
			dialog.text = "Тогда я при всем своем желании не смогу пойти на ваше предложение. Прощайте!";
			link.l1 = "Гм...";
			link.l1.go = "MarginNeed_exit";
		break;
		
		case "MarginNeed_exit":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeday = 0;
			AddQuestRecord("Marginpassenger", "11");
			AddQuestUserData("Marginpassenger", "sName2", pchar.GenQuest.Marginpassenger.q2Name);
			AddQuestUserData("Marginpassenger", "sCity", XI_ConvertString("Colony"+pchar.GenQuest.Marginpassenger.City));
			pchar.GenQuest.Marginpassenger = "cabin";
		break;
		
		case "MarginPass":
			dialog.text = "Что?.. Что здесь происходит?!";
			link.l1 = "Все очень просто, "+NPCharSexPhrase(NPChar, "приятель","милочка")+". Ты отправляешься на мой корабль в качестве почетного пассажира... с охраной. Сопротивляться не стоит, потому что в противном случае я отправлю тебя в трюм.";
			link.l1.go = "MarginPass_1";
		break;
		
		case "MarginPass_1":
			dialog.text = "То есть вы хотите сказать, что я - "+NPCharSexPhrase(NPChar, "ваш пленник","ваша пленница")+"?";
			link.l1 = "О нет, отнюдь. Не "+NPCharSexPhrase(NPChar, "пленник, а дорогой гость. Очень дорогой...","пленница, а дорогая гостья. Очень дорогая...")+"";
			link.l1.go = "MarginPass_2";
		break;
		
		case "MarginPass_2":
			dialog.text = "Вы... вы заплатите за этот произвол!";
			link.l1 = "Ты опять не прав"+NPCharSexPhrase(NPChar, ", приятель","а, дорогуша")+". Платить буду не я, платить будут мне. А теперь довольно разговоров - живо марш в каюту!";
			link.l1.go = "MarginPass_3";
		break;
		
		case "MarginPass_3":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "", "", "none", "", "", "", 1.0);
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, false);
			pchar.quest.Marginpassenger_InWorldOver.over = "yes"; //снять прерывание
			pchar.quest.Marginpassenger_Sink.over = "yes"; //снять прерывание
			pchar.GenQuest.Marginpassenger = "take";
			if (rand(2) == 1) pchar.GenQuest.Marginpassenger.lose = "true";
			else Marginpassenger_CreateNeedman();
			if (CheckAttribute(pchar, "GenQuest.Marginpassenger.Boarding")) AddQuestRecord("Marginpassenger", "6");
			else AddQuestRecord("Marginpassenger", "4");
			AddQuestUserData("Marginpassenger", "sName1", pchar.GenQuest.Marginpassenger.q1Name);
			AddQuestUserData("Marginpassenger", "sShipName", pchar.GenQuest.Marginpassenger.ShipName);
			AddQuestUserData("Marginpassenger", "sShipType", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.Marginpassenger.ShipType), "Name")+"Acc")));
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}