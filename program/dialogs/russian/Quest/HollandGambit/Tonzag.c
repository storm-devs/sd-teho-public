// Эркюль Тонзаг, он же Плешивый Гастон
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
			if (CheckAttribute(pchar, "questTemp.HWIC.Self") && pchar.questTemp.HWIC.Self == "MainBegin")
			{
				dialog.text = "Ну, здравствуй, " + pchar.name + ". Рад тебя видеть!";
				link.l1 = "Гастон!? Это ты?";
				link.l1.go = "SJ_talk";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.HWIC.Self") && pchar.questTemp.HWIC.Self == "MeetTonzag")
			{
				dialog.text = "Здравствуй, " + pchar.name + ". Я уже в курсе о твох делах - Джон мне все рассказал. Я, даже, право, не знаю, что и сказать. Я восхищен!";
				link.l1 = "Приятно слышать похвалу из твоих уст, Эркюль!";
				link.l1.go = "SJ_talk_11";
				break;
			}
			dialog.text = "Добрый день. У вас ко мне дело?";
			link.l1 = "Нет. Вероятно, я ошибся. Прошу меня извинить. До свидания.";
			link.l1.go = "exit";	
			NextDiag.TempNode = "First time";
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "SJ_talk":
			dialog.text = "Ты знал меня под этим именем. Но мое настоящее имя - Эркюль. Эркюль Тонзаг.";
			link.l1 = "Вот это да! Я тоже рад тебя видеть... А я тебя и не узнал в пылу драки. Ты вовремя подоспел ко мне на выручку.";
			link.l1.go = "SJ_talk_1";
		break;
		
		case "SJ_talk_1":
			dialog.text = "После твоего отбытия, я буквально на следующий день получил известия, что Флитвуд значительно усилил охрану своего дома. Предполагая, что за этим может крыться некая ловушка, или что-то подобное, я немедленно на своем люггере выдвинулся на Антигуа. И, как видишь, не зря.";
			link.l1 = "Это точно. Я еле управился с гвардейцами внутри дома, на бой на улице сил уже не хватило... немного не хватило.";
			link.l1.go = "SJ_talk_2";
		break;
		
		case "SJ_talk_2":
			dialog.text = "После этой бойни, Флитвуд объявил розыск голландского шпиона - они приняли тебя именно за голландца. У Флитвуда старая вражда с ними... Плохо было то, что один из солдат в доме остался жив и запомнил твое лицо. Впрочем, эта проблема уже решена - я сегодня доделал то, что начал ты. Больше этот солдат уже никого не опознает...";
			link.l1 = "Ты его - того? Понятно...";
			link.l1.go = "SJ_talk_3";
		break;
		
		case "SJ_talk_3":
			dialog.text = "Да. А пока ты валялся без сознания у Джона, я приложил нашему дружку, Флитвуду, но тут вышла промашка. Я ослепил его, бросив перец в глаза, и рубанул, прежде чем он успел обнажить клинок. Но этот гад носит под мундиром пурпан... это и спасло его. Сейчас он отлеживается у себя в доме, под усиленной охраной. Очень плохо, что он остался жив.";
			link.l1 = "Так твоя основная задача на Антигуа - убрать Флитвуда?";
			link.l1.go = "SJ_talk_4";
		break;
		
		case "SJ_talk_4":
			dialog.text = "Ну, в общем, да. Но теперь это, похоже, невыполнимо - дом всегда на замке, в нем дежурит полдюжины отборных гвардейцев, и пропускают к Флитвуду только его доверенное лицо - старого артиллериста Чарли, по прозвищу Книппель.";
			link.l1 = "Уже что-то...";
			link.l1.go = "SJ_talk_5";
		break;
		
		case "SJ_talk_5":
			dialog.text = "Постой-ка... Ты что, задумал вмешаться в это дело?";
			link.l1 = "А почему бы и нет? Разве тебе не нужна помощь? Ты спас меня, и я хочу помочь.";
			link.l1.go = "SJ_talk_6";
		break;
		
		case "SJ_talk_6":
			dialog.text = "Поверь мне, парень, ты с этим не справишься. Ты молодец, добытый тобой журнал помог мне спланировать покушение на Флитвуда, ты здорово покрошил в капусту гвардейцев, но до Флитвуда тебе не добраться. Даже я не представляю теперь, как это сделать.";
			if (pchar.Ship.Type == SHIP_NOTUSED)
			{
				link.l1 = "Я подумаю. Время у меня есть. Вот только жаль, корабль мой арестовали, да и команды не осталось.";
				link.l1.go = "SJ_talk_7";
			}
			else
			{
				link.l1 = "Я подумаю. Время у меня есть, и корабль тоже.";
				link.l1.go = "SJ_talk_8";
			}
		break;
		
		case "SJ_talk_7":
			dialog.text = "Не переживай по поводу этого. Когда твою лоханку взяли под стражу, я собрал весь твой офицерский состав и часть матросов на своем люггере. Они знают, что ты жив и остались на службе. В качестве награды за журнал я передаю тебе в постоянное пользование свой люггер.";
			link.l1 = "Спасибо! Я в долгу не останусь.";
			link.l1.go = "SJ_talk_9";
			pchar.Ship.Type = GenerateShipHand(pchar, SHIP_CAREERLUGGER, 12, 580, 30, 800, 20000, 16.5, 65.5, 1.6);
			pchar.Ship.name = "Сумрак";
			SetBaseShipData(pchar);
			pchar.Ship.Cannons.Type = CANNON_TYPE_CANNON_LBS12;
			SetCrewQuantityFull(pchar);
			pchar.Ship.Crew.Morale = 80;
			pchar.Ship.Crew.Exp.Sailors = 90;
			pchar.Ship.Crew.Exp.Cannoners = 70;
			pchar.Ship.Crew.Exp.Soldiers = 70;
			SetCharacterGoods(pchar, GOOD_BALLS, 100);
			SetCharacterGoods(pchar, GOOD_GRAPES, 100);
			SetCharacterGoods(pchar, GOOD_KNIPPELS, 100);
			SetCharacterGoods(pchar, GOOD_BOMBS, 100);
			SetCharacterGoods(pchar, GOOD_FOOD, 100);
			SetCharacterGoods(pchar, GOOD_POWDER, 300);
			SetCharacterGoods(pchar, GOOD_WEAPON, 60);
			SetCharacterGoods(pchar, GOOD_MEDICAMENT, 60);
		break;
		
		case "SJ_talk_8":
			AddMoneyToCharacter(pchar, 15000);
			dialog.text = "Да, я хочу передать тебе деньги за журнал. Вот 15 000 - больше у меня на данный момент нет, к сожалению. Потом сочтемся.";
			link.l1 = "Не надо. Этого хватит. Если бы не ты, мне бы и эти деньги уже не понадобились бы.";
			link.l1.go = "SJ_talk_9";
		break;
		
		case "SJ_talk_9":
			dialog.text = "Ладно, " + pchar.name + ", мне пора идти. В Бриджтаун я пока не намерен возвращаться. Если я тебе сильно понадоблюсь - поспрашивай Джона. Счастливо!";
			link.l1 = "Удачи, Эркюль!";
			link.l1.go = "SJ_talk_10";
		break;
		
		case "SJ_talk_10":
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "", 10);
			DialogExit();
			AddQuestRecord("Holl_Gambit", "3-13");
			pchar.questTemp.HWIC.Self = "HuntFleetwood";
		break;
		
		case "SJ_talk_11":
			dialog.text = "За ликвидацию Флитвуда я хочу подарить тебе этот доспех - он надежно защитит тебя в схватках. А теперь пойдем к Джону. У него к тебе серьезный разговор - он хочет предложить тебе... одно дело.";
			link.l1 = "За подарок спасибо! Хорошо, пойдем...";
			link.l1.go = "SJ_talk_12";
		break;
		
		case "SJ_talk_12":
			DialogExit();
			GiveItem2Character(pchar, "cirass7");//дать вещь
			sld = characterFromId("Merdok");
			LAi_SetOwnerType(sld);
			LAi_SetActorType(npchar);
			LAi_ActorFollow(npchar, pchar, "", -1);
			AddQuestRecord("Holl_Gambit", "3-35");
		break;
		
		case "Tonzag_hired":
			dialog.text = "Капитан, у меня тоже к тебе дело. Я собирался учить тебя ремеслу, но вижу, что мне самому есть чему у тебя поучиться на старости лет. Возьми меня к себе офицером на корабль - не пожалеешь.";
			link.l1 = "С удовольствием, Эркюль! Добро пожаловать в команду!";
			link.l1.go = "Tonzag_hired_1";
			link.l2 = "Эркюль, я не могу представить себя в роли твоего босса. Спасибо за предложение, но я не могу себе позволить командовать тобой.";
			link.l2.go = "Tonzag_exit";
		break;
		
		case "Tonzag_hired_1"://Тонзага - в офицеры
			DialogExit();
			DeleteAttribute(npchar, "LifeDay");
			npchar.quest.OfficerPrice = sti(pchar.rank)*500;
			npchar.OfficerWantToGo.DontGo = true;
			npchar.loyality = MAX_LOYALITY;
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, true);
			npchar.Payment = true;
			LAi_SetOfficerType(npchar);
			npchar.greeting = "tonzag_hire";
			NextDiag.CurrentNode = "tonzag_officer";
			npchar.quest.meeting = true;
			npchar.HoldEquip = true;
			LAi_SetImmortal(npchar, false);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			SaveCurrentNpcQuestDateParam(npchar, "HiredDate");
		break;
		
		case "Tonzag_exit":
			dialog.text = "Ну, как скажешь, " + pchar.name + ". Бывай. Может, еще встретимся. Приятно было с тобой работать!";
			link.l1 = "И тебе всего хорошего, дружище!";
			link.l1.go = "Tonzag_exit_1";
		break;
		
		case "Tonzag_exit_1":
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "", -1);
			npchar.lifeday = 0;
			DialogExit();
		break;
		
		//--> ----------------------------------- офицерский блок ------------------------------------------
		case "tonzag_officer":
			dialog.text = "Слушаю, тебя, кэп. Что скажешь?";
			if (CheckAttribute(pchar, "questTemp.Dolly_Tieyasal") && !CheckAttribute(npchar, "quest.Tieyasal"))
			{
				Link.l4 = "Эркюль, я собираюсь отправиться в старый индейский город Тайясаль. Не буду скрывать: это крайне опасное путешествие, и более того - необычное: через телепортационный истукан. Ты... пойдешь со мной?";
				Link.l4.go = "tieyasal";
			}
			Link.l1 = "Слушай мой приказ!";
            Link.l1.go = "stay_follow";
			link.l2 = "Пока ничего. Вольно!";
			link.l2.go = "exit";
			NextDiag.TempNode = "tonzag_officer";
		break;
		
		case "stay_follow":
            dialog.Text = "Какие приказания?";
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
	
	// на Тайясаль
		case "tieyasal":
			dialog.text = "Ты чертовски удачлив, кэп. Я рад, что присоединился к тебе тогда, у Джона. И проглоти меня акула, если я не поддержу тебя и в этом предприятии!";
			link.l1 = "Спасибо, Эркюль! Я рад, что не ошибся в тебе.";
			link.l1.go = "tieyasal_1";
		break;
		
		case "tieyasal_1":
			dialog.text = "Когда мы будем отправляться?";
			link.l1 = "Немного позже. А пока подготовимся к походу.";
			link.l1.go = "tieyasal_2";
		break;
		
		case "tieyasal_2":
			DialogExit();
			AddQuestRecord("Tieyasal", "23");
			npchar.quest.Tieyasal = "teleport";
		break;
	}
}