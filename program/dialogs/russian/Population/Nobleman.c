//Jason общий диалог дворян
#include "DIALOGS\russian\Rumours\Common_rumours.c"
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int iTemp, iTest;
	string sTemp, sTitle;
	float locx, locy, locz;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	// вызов диалога по городам -->
    NPChar.FileDialog2 = "DIALOGS\" + LanguageGetLanguage() + "\Citizen\" + NPChar.City + "_Citizen.c";
    if (LoadSegment(NPChar.FileDialog2))
	{
        ProcessCommonDialog(NPChar, Link, NextDiag);
		UnloadSegment(NPChar.FileDialog2);
	}
    // вызов диалога по городам <--
	
	ProcessCommonDialogRumors(NPChar, Link, NextDiag);
	
	iTest = FindColony(NPChar.City); // 170712
    ref rColony;
	if (iTest != -1)
	{
		rColony = GetColonyByIndex(iTest);
	}
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			//--> проверка межнациональных отношений
				if (sti(NPChar.nation) != PIRATE && GetNationRelation2MainCharacter(sti(NPChar.nation)) == RELATION_ENEMY)
				{
				dialog.text = NPCStringReactionRepeat("Хм. Ты ходишь под флагом "+NationNameGenitive(sti(pchar.nation))+", приятель. Какого чёрта ты делаешь здесь, в нашем городе? Убирайся!", 
					"Я не желаю, чтобы меня заподозрили в связи с "+NationNameAblative(sti(pchar.nation))+"! Проваливай, не то точно страже доложу!", 
					"Даю тебе последний шанс убраться прочь. Потом - пеняй на себя.",
					"Ну, я тебя предупреждал. Теперь ты поплатишься за свою дерзость, негодяй!", "block", 1, npchar, Dialog.CurrentNode);
				link.l1 = HeroStringReactionRepeat("Тоже мне, патриот выискался...", 
					"Ладно-ладно, не кипятись. Ухожу.",
					"Не шуми, я уже ушёл...", 
					"Что?!", npchar, Dialog.CurrentNode);
				link.l1.go = DialogGoNodeRepeat("exit", "", "", "fight", npchar, Dialog.CurrentNode);
			break;
			}
			
			//--> проверка репутации - дворяне гнобят супернегодяев
			if (sti(pchar.reputation.nobility) < 10)
			{
				dialog.text = NPCStringReactionRepeat("Ну надо же! И как только стража позволяет таким мерзавцам расхаживать по нашему городу? Невероятно...", 
					"Проваливайте, я не желаю даже разговаривать с вами! Висельник...", 
					"Даю тебе последний шанс убраться прочь. Потом - пеняй на себя.",
					"Ну, я тебя предупреждал. Теперь ты поплатишься за свою дерзость, негодяй!", "block", 1, npchar, Dialog.CurrentNode);
				link.l1 = HeroStringReactionRepeat("Но-но, сударь, проявляйте больше уважения!", 
					"На себя посмотри, святоша...",
					"Не шуми...", 
					"Что?!", npchar, Dialog.CurrentNode);
				link.l1.go = DialogGoNodeRepeat("exit", "", "", "fight", npchar, Dialog.CurrentNode);
			break;
			}
			
			//--> диалог первой встречи
            if(NPChar.quest.meeting == "0")
			{
				// проверка наличия корабля в порту
				bool ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
				if (ok && sti(Pchar.Ship.Type) != SHIP_NOTUSED && CheckAttribute(npchar, "quest.passenger") && !CheckAttribute(pchar, "GenQuest.Noblepassenger") && 4-sti(RealShips[sti(Pchar.Ship.Type)].Class) > 0)//дворянин-пассажир
				{
					dialog.text = "Приветствую, "+GetAddress_Form(NPChar)+". Вижу, вы капитан солидного корабля. У меня будет к вам просьба, или предложение - как вам угодно...";
					link.l1 = "Слушаю вас, "+GetAddress_FormToNPC(NPChar)+". О чём пойдёт речь?";
					link.l1.go = "passenger";
					link.l2 = "Простите, "+GetAddress_FormToNPC(NPChar)+", но я очень спешу.";
					link.l2.go = "exit";
					npchar.quest.meeting = "1";
					DeleteAttribute(npchar, "talker"); //снимаем говорилку
					break;
				}
				if (CheckAttribute(npchar, "quest.donation"))//клянчит деньги
				{
					dialog.text = "А-а, рад видеть приличного человека в нашем захолустье! Ручаюсь, вы не так давно из Европы. Послушайте, я хочу попросить вас о помощи, как дворянин дворянина. Надеюсь, вы поймёте меня правильно.";
					link.l1 = "Здравствуйте, сударь. Я вас внимательно слушаю.";
					link.l1.go = "donation";
					npchar.quest.meeting = "1";
					break;
				}
				if (CheckAttribute(npchar, "quest.lombard") && !CheckAttribute(pchar, "GenQuest.Noblelombard"))//семейная реликвия
				{
					dialog.text = "Добрый день, "+GetAddress_Form(NPChar)+"! Приятно встретить представителя дворянского сословия на улицах нашего города! Позволите отнять несколько минут вашего драгоценного времени?";
					link.l1 = "Конечно, сударь. Внимательно вас слушаю.";
					link.l1.go = "lombard";
					npchar.quest.meeting = "1";
					break;
				}
				if (CheckAttribute(npchar, "quest.slaves") && !CheckAttribute(Colonies[FindColony(npchar.city)], "questslaves"))//привезти рабов
				{
					dialog.text = "Приветствую, капитан! Рад вас видеть, потому что вы выглядите человеком, который в состоянии помочь мне в одном вопросе.";
					link.l1 = "Очень интересно. И в чём же будет заключаться моя помощь, "+GetAddress_FormToNPC(NPChar)+"?";
					link.l1.go = "slaves";
					npchar.quest.meeting = "1";
					break;
				}
				dialog.text = RandPhraseSimple("Здравствуйте, "+GetAddress_Form(NPChar)+". Вы что-то от меня хотели?", "Что вам угодно, сударь?");
				link.l1 = TimeGreeting()+", "+GetAddress_FormToNPC(NPChar)+". Я не задержу вас надолго, просто хочу спросить у вас...";
				link.l1.go = "question";
				link.l2 = RandPhraseSimple("Мне нужна информация о делах в вашей колонии.", "Мне нужна информация.");
				link.l2.go = "quests";//(перессылка в файл города)
				npchar.quest.meeting = "1";
			}
			else //--> повторные обращения
			{
				dialog.text = NPCStringReactionRepeat("Что? Опять? Нет у меня на вас времени. Поищите для болтовни кого-нибудь другого. Тут полно бездельников, слоняющихся по улицам. А мне пора - вечером приём у губернатора, надо готовиться...", 
				"Нет, это уже начинает действительно утомлять! Вы что, не понимаете с первого раза? Вы тугодум?", 
					"Сударь, я начинаю подозревать то, что вы не тупица, а банальный невежа и хам. Предупреждаю: не лезьте на рожон!",
					"Так, ну всё. Теперь я проучу тебя, наглец!", "block", 1, npchar, Dialog.CurrentNode);
				link.l1 = HeroStringReactionRepeat("Понятно. Всего доброго.", 
					"Да-да, я помню, просто забыл спросить вот что...",
					"Вы меня неправильно поняли...", 
					"Что?!", npchar, Dialog.CurrentNode);
				link.l1.go = DialogGoNodeRepeat("exit", "", "", "fight", npchar, Dialog.CurrentNode);
			}
			NextDiag.TempNode = "First time";
		break;

		case "question":
			dialog.text = LinkRandPhrase("Тогда выкладывайте.","Ох, ну хорошо. Что вы хотите?","Вопросы задавать будем? Ладно, моряк, слушаю.");
			link.l1 = LinkRandPhrase("Не расскажете последние новости вашего города?","Расскажите пожалуйста, что интересного в последнее время произошло?","Что интересного творится на архипелаге, сударь, вы не в курсе?");
			link.l1.go = "rumours_nobleman";
			NextDiag.TempNode = "First time";
		break;

//--------------------------------------------дворянин-пассажир---------------------------------------------------
		case "passenger":
			if (drand(19) > 9) SetPassengerParameter("Noblepassenger", false);
			else SetPassengerParameter("Noblepassenger", true);
			dialog.text = "Сударь, мне срочно нужно добраться до колонии " + XI_ConvertString("Colony"+pchar.GenQuest.Noblepassenger.City)+", это на "+XI_ConvertString(GetIslandByCityName(pchar.GenQuest.Noblepassenger.City)+"Dat")+", за "+FindRussianDaysString(sti(pchar.GenQuest.Noblepassenger.DaysQty))+". Ваше судно выглядит вполне надёжным, в отличие от большинства ошивающихся у нас лоханок. Я готов выложить за это путешествие "+FindRussianMoneyString(sti(pchar.GenQuest.Noblepassenger.Money))+". Что скажете?";
			link.l1 = "Хм. Нам с вами по пути, так что я готов взять вас на борт на этих условиях.";
			link.l1.go = "passenger_1";
			link.l2 = "Сожалею, "+GetAddress_FormToNPC(NPChar)+", но мне совсем в другую сторону. Ничем не могу помочь.";
			link.l2.go = "passenger_exit";
		break;
		
		case "passenger_exit":
			dialog.text = "Жаль. Ну что же, подожду другого корабля. Прощайте!";
			link.l1 = "Всего доброго.";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "GenQuest.Noblepassenger");
		break;
		
		case "passenger_1":
			dialog.text = "Очень хорошо, а то я уже устал ждать. Оплату получите по прибытии на место.";
			link.l1 = "Отправляйтесь на моё судно, "+GetAddress_FormToNPC(NPChar)+". Мы скоро отчаливаем.";
			link.l1.go = "passenger_2";
		break;
		
		case "passenger_2":
			DialogExit();
			pchar.GenQuest.Noblepassenger.id = npchar.id;
			LAi_SetImmortal(npchar, true);
			DeleteAttribute(npchar, "LifeDay");
			LAi_RemoveLoginTime(npchar);
			DeleteAttribute(npchar, "CityType");//удалить признак фантома, иначе - пустые города
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "", 20.0);
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, false);
			sTitle = npchar.index+"Citizpassenger";

// LDH 13Sep17 - do not add to an existing Citizpassenger record -->
// "Rename" the quest record by copying it to a new name and deleting the old record
			if (CheckAttribute(pchar, "questinfo."+sTitle))
			{
				string sTempLDH = frand(1);
				sTempLDH = strcut(sTempLDH, 2, 5);    // 4 random digits
				string sTitle1 = sTitle+sTempLDH;

				aref arTo, arFrom;
				makearef(arFrom, pchar.questinfo.(sTitle));
				makearef(arTo,   pchar.questinfo.(sTitle1));
				CopyAttributes(arTo, arFrom);
				pchar.questinfo.(sTitle1) = "";

				DeleteAttribute(pchar, "questinfo."+sTitle);

				Trace("Duplicate Citizpassenger record "+sTitle+" copied to "+sTitle1+" **");
			}
// <--

			AddQuestRecordEx(sTitle, "Citizpassenger", "1");
			AddQuestUserDataForTitle(sTitle, "sType", "дворянина");
			AddQuestUserDataForTitle(sTitle, "sName", GetFullName(npchar));
			sTemp = XI_ConvertString("Colony" +pchar.GenQuest.Noblepassenger.City+"Gen") + ", что на " + XI_ConvertString(GetIslandByCityName(pchar.GenQuest.Noblepassenger.City)+"Dat")+".";
			AddQuestUserDataForTitle(sTitle, "sCity", sTemp);
			AddQuestUserData(sTitle, "sName", GetFullName(npchar));
			AddQuestUserData(sTitle, "sCity", sTemp);
			AddQuestUserData(sTitle, "sDays", FindRussianDaysString(sti(pchar.GenQuest.Noblepassenger.DaysQty)));
            AddQuestUserData(sTitle, "sMoney", FindRussianMoneyString(sti(pchar.GenQuest.Noblepassenger.Money)));
			AddQuestUserData(sTitle, "sName", GetFullName(npchar));
			pchar.quest.Noblepassenger.win_condition.l1 = "location";
			pchar.quest.Noblepassenger.win_condition.l1.location = pchar.GenQuest.Noblepassenger.City+"_town";
			pchar.quest.Noblepassenger.function = "Noblepassenger_complete";
			SetFunctionTimerCondition("Noblepassenger_Over", 0, 0, sti(pchar.GenQuest.Noblepassenger.DaysQty), false);
		break;
		
		case "passenger_3":
			pchar.quest.Noblepassenger_Over.over = "yes"; //снять таймер
			dialog.text = "Вот мы и на месте, замечательно! Путешествие на вашем корабле меня весьма и весьма устроило. Благодарю. Вот ваши деньги, сударь.";
			link.l1 = "Удачи, "+GetAddress_FormToNPC(NPChar)+"! Всего доброго.";
			link.l1.go = "passenger_4";
		break;
		
		case "passenger_4":
			chrDisableReloadToLocation = false;//открыть локацию
			DialogExit();
			npchar.lifeday = 0;
			RemovePassenger(Pchar, npchar);
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload4_back", "none", "", "", "", 20.0);
			AddMoneyToCharacter(pchar, sti(pchar.GenQuest.Noblepassenger.Money));
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
			ChangeCharacterComplexReputation(pchar, "fame", 1);
			OfficersReaction("good");				
			AddCharacterExpToSkill(pchar, "Sailing", 80);
			AddCharacterExpToSkill(pchar, "Leadership", 20);
			if (CheckAttribute(pchar, "GenQuest.Noblepassenger.Enemycity")) AddCharacterExpToSkill(pchar, "Sneak", 50);
			sTitle = npchar.index+"Citizpassenger";
			AddQuestRecordEx(sTitle, "Citizpassenger", "3");
			CloseQuestHeader(sTitle);
			DeleteAttribute(Pchar, "GenQuest.Noblepassenger");
		break;
//<-- дворянин-пассажир

//-------------------------------------------------помощь деньгами------------------------------------------------
		case "donation":
			sTemp = DonationText();
			dialog.text = "Тут такое дело, очень щекотливое... "+sTemp+" Деньги нужны мне срочно, прямо сейчас, иначе - катастрофа. Я бы никогда не позволил себе обратиться к вам с такой просьбой, если бы не пиковая ситуация.";
			link.l1 = "Сколько конкретно денег вам нужно?";
			link.l1.go = "donation_1";
		break;
		
		case "donation_1":
			iTemp = drand(4)+1;
			pchar.GenQuest.Nobledonation.Money = iTemp*1000+rand(iTemp)*150;
			dialog.text = "Сумма небольшая, всего "+FindRussianMoneyString(sti(pchar.GenQuest.Nobledonation.Money))+". Ну как, поможете?";
			if (sti(pchar.money) >= sti(pchar.GenQuest.Nobledonation.Money))
			{
				link.l1 = "Да без проблем. Вот, держите.";
				link.l1.go = "donation_2";
			}
			link.l2 = "Я бы помог, но я сам сейчас на мели, нет ни песо лишнего в кармане.";
			link.l2.go = "donation_exit";
		break;
		
		case "donation_exit":
			DialogExit();
			ChangeOfficersLoyality("bad_all", 1);
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeday = 0;
			DeleteAttribute(pchar, "GenQuest.Nobledonation");
		break;
		
		case "donation_2":
			AddMoneyToCharacter(pchar, -sti(pchar.GenQuest.Nobledonation.Money));
			dialog.text = "Искренне благодарю вас, "+GetAddress_Form(NPChar)+"! Вы меня просто спасли! У меня есть друзья в губернаторском дворце, и я при случае обязательно упомяну о вашем благородстве. Ещё раз большое спасибо!";
			link.l1 = "Да не за что, сударь. Уверен, вы бы на моем месте поступили точно так же.";
			link.l1.go = "donation_3";
		break;
		
		case "donation_3":
			DialogExit();
			ChangeOfficersLoyality("good_all", rand(2)+1);
			ChangeCharacterNationReputation(pchar, sti(npchar.Nation), rand(1)+2);
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeday = 0;
			DeleteAttribute(pchar, "GenQuest.Nobledonation");
		break;
//<-- помощь деньгами

//-------------------------------------------------семейная реликвия---------------------------------------------
		case "lombard":
			LombardText();
			dialog.text = "Я хочу попросить вас о помощи. Как человек не бедный, и благородного происхождения, думаю, вы меня правильно поймёте. Некоторое время назад у меня возникла острая потребность в деньгах, и я был вынужден заложить у нашего ростовщика "+pchar.GenQuest.Noblelombard.Item+"\nОн предоставил выгодные условия - всего десять процентов ежемесячно, на три месяца. Однако сроки истекли, а у меня ввиду неудачно сложившихся обстоятельств так и не появились деньги на выкуп\nТеперь он говорит, что на "+pchar.GenQuest.Noblelombard.Item+" появился покупатель, и он продаст мою вещь, если я немедленно не погашу проценты по долгу и сам долг. Однако у меня сейчас нет достаточной суммы, моя реликвия - вещь дорогая...";
			link.l1 = "И чем же я могу помочь вам в этой ситуации, "+GetAddress_FormToNPC(NPChar)+"?";
			link.l1.go = "lombard_1";
		break;
		
		case "lombard_1":
			dialog.text = "Я прошу вас - поговорите с нашим ростовщиком. Посулите ему денег, поручитесь, может, что ещё. К сожалению, мне не к кому обратиться - у всех моих знакомых 'внезапно' не стало денег. Через три месяца "+pchar.GenQuest.Noblelombard.Text+", и я возмещу все ваши расходы в двухкратном размере. Слово чести!";
			link.l1 = "Ну хорошо, попробую вам помочь, раз такое дело.";
			link.l1.go = "lombard_2";
			link.l2 = "К сожалению, я сейчас тоже на мели. Так что ничем не могу помочь, увы!";
			link.l2.go = "lombard_exit";
		break;
		
		case "lombard_exit":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeday = 0;
			DeleteAttribute(pchar, "GenQuest.Noblelombard");
		break;
		
		case "lombard_2":
			dialog.text = "Спасибо за понимание. Я буду ждать вас в таверне. Приходите скорее!";
			link.l1 = "...";
			link.l1.go = "lombard_3";
		break;
		
		case "lombard_3":
			DialogExit();
			pchar.GenQuest.Noblelombard = "true"
			pchar.GenQuest.Noblelombard.Name = GetFullName(npchar);
			pchar.GenQuest.Noblelombard.id = npchar.id;
			pchar.GenQuest.Noblelombard.City = npchar.city;
			pchar.GenQuest.Noblelombard.Money = 20000+drand(60)*500;
			pchar.GenQuest.Noblelombard.Percent = makeint(sti(pchar.GenQuest.Noblelombard.Money)*0.3);
			pchar.GenQuest.Noblelombard.Summ = sti(pchar.GenQuest.Noblelombard.Money)+sti(pchar.GenQuest.Noblelombard.Percent);
			pchar.GenQuest.Noblelombard.Chance = drand(9);
			chrDisableReloadToLocation = true;//закрыть локацию
			LAi_SetActorType(npchar);
			LAi_RemoveLoginTime(npchar);
			DeleteAttribute(npchar, "CityType");//удалить признак фантома
			FreeSitLocator(pchar.GenQuest.Noblelombard.City + "_tavern", "sit1");
			LAi_ActorRunToLocation(npchar, "reload", "reload4_back", pchar.GenQuest.Noblelombard.City+"_tavern", "sit", "sit1", "Nobleman_lombardTavern", 10);
			SetFunctionTimerCondition("Noblelombard_Over", 0, 0, 1, false); //таймер до конца суток
			ReOpenQuestHeader("Noblelombard");
			AddQuestRecord("Noblelombard", "1");
			AddQuestUserData("Noblelombard", "sCity", XI_ConvertString("Colony"+pchar.GenQuest.Noblelombard.City));
			AddQuestUserData("Noblelombard", "sName", pchar.GenQuest.Noblelombard.Name);
		break;
		
		case "lombard_4":
			if (CheckAttribute(pchar, "GenQuest.Noblelombard.Regard"))
			{
				pchar.quest.Noblelombard_Over.over = "yes"; //снять таймер
				dialog.text = "Что скажете, "+GetAddress_Form(NPChar)+"? Вы были у ростовщика? Сможете меня порадовать, или нет?";
				if (pchar.GenQuest.Noblelombard == "full") link.l1 = "Да, был. Я оплатил проценты за три месяца и стоимость вашего раритета. Можете идти и забирать его.";
				if (pchar.GenQuest.Noblelombard == "maxpercent") link.l1 = "Да, был. Я оплатил проценты за истекшие три месяца, и авансом за следующие три. Так что можете спокойно ждать денег. Главное - не позже, чем через три месяца, оплатить сумму основного долга.";
				if (pchar.GenQuest.Noblelombard == "minpercent") link.l1 = "Да, был. Я оплатил проценты за истекшие три месяца. Ростовщик согласен подождать ещё три, пока вы соберёте нужную сумму.";
				link.l1.go = "lombard_5";
			break;
			}
			if (pchar.GenQuest.Noblelombard == "fail")
			{
				dialog.text = "Что скажете, "+GetAddress_Form(NPChar)+"? Вы были у ростовщика? Сможете меня порадовать, или нет?";
				link.l1 = "Да, был. Этот скряга заломил просто невероятную сумму! На уступки он пойти не согласился, а требуемой суммы у меня нет. Так что я ничем не смог вам помочь, увы!";
				link.l1.go = "lombard_fail";
			}
			else
			{
				dialog.text = "Что скажете, "+GetAddress_Form(NPChar)+"? Вы были у ростовщика? Сможете меня порадовать, или нет?";
				link.l1 = "Я ещё работаю над этим, ждите.";
				link.l1.go = "exit";
				NextDiag.TempNode = "lombard_4";
			}
		break;
		
		case "lombard_fail":
			pchar.quest.Noblelombard_Over.over = "yes"; //снять таймер
			dialog.text = "Эх, "+GetAddress_Form(NPChar)+"... Вот вы и оказались свидетелем неуёмной жадности этих проклятых кровопийц-ростовщиков. Помните об этом, когда будете одалживать у них деньги, не попадитесь, как я. Спасибо вам за участие, что хотя бы попробовали...";
			link.l1 = "Никогда не любил ростовщиков. Да, впрочем, кто их любит? Мне жаль, что так вышло, "+GetAddress_FormToNPC(NPChar)+". Прощайте.";
			link.l1.go = "lombard_fail_1";
		break;
		
		case "lombard_fail_1":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeday = 0;
			AddQuestRecord("Noblelombard", "4");
			AddQuestUserData("Noblelombard", "sName", pchar.GenQuest.Noblelombard.Name);
			CloseQuestHeader("Noblelombard");
			sld = characterFromId(pchar.GenQuest.Noblelombard.City+"_usurer");
			DeleteAttribute(sld, "quest.noblelombard");
			DeleteAttribute(Pchar, "GenQuest.Noblelombard");
		break;
		
		case "lombard_5":
			dialog.text = "Невероятно! Вы меня просто спасли, "+GetAddress_Form(NPChar)+"! Никогда этого не забуду. Можете быть уверены - ваши расходы будут компенсированы, как я и обещал - в двухкратном размере. Через три месяца зайдите к нашему ростовщику - я открою у него депозит на ваше имя - и заберите свои деньги.";
			link.l1 = "Хорошо, так и поступим. Всего доброго!";
			link.l1.go = "lombard_6";
		break;
		
		case "lombard_6":
			dialog.text = "Ещё раз большое спасибо, капитан! Удачи!";
			link.l1 = "...";
			link.l1.go = "lombard_7";
		break;
		
		case "lombard_7":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeday = 0;
			ChangeCharacterComplexReputation(pchar, "authority", 2);
			ChangeOfficersLoyality("good_all", 1);
			AddQuestRecord("Noblelombard", "5");
			AddQuestUserData("Noblelombard", "sName", pchar.GenQuest.Noblelombard.Name);
			SetFunctionTimerCondition("Noblelombard_Regard", 0, 0, 90, false); //таймер
		break;
//<-- семейная реликвия

//------------------------------------------привезти рабов под заказ--------------------------------------------
		case "slaves":
			npchar.quest.slaves.price = 3+drand(1);//цена на рабов в дублонах
			npchar.quest.slaves.qty = 50+drand(5)*10;//количество
			npchar.quest.slaves.money = sti(npchar.quest.slaves.qty)*sti(npchar.quest.slaves.price);
			dialog.text = "Мне для работы на "+LinkRandPhrase("моей фактории","моём руднике","моей плантации")+" постоянно требуются рабы. В данный момент эта потребность составляет "+sti(npchar.quest.slaves.qty)+" человек. Я хочу заказать у вас эту партию рабов. Плачу я щедро, золотом, по "+sti(npchar.quest.slaves.price)+" дублона за голову\nОсобой спешки нет, так что в сроках я вас сильно не ограничиваю. Ну, конечно, если вы не растянете это больше, чем на полгода. Ну как, по рукам?";
			link.l1 = "По рукам! Дело хлопотное, но оно того стоит.";
			link.l1.go = "slaves_1";
			link.l2 = "Простите, но работорговлей я не занимаюсь. Не мой профиль.";
			link.l2.go = "exit_slaves";
		break;
		
		case "exit_slaves":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeday = 0;
		break;
		
		case "slaves_1":
			dialog.text = "Очень хорошо. Буду ждать вас с товаром. Найти меня вы сможете в городской церкви ежедневно с одиннадцати до часу дня. В остальное время я или в разъездах, или занят.";
			link.l1 = "Хорошо. Я приму это к сведению. До встречи, "+GetAddress_FormToNPC(NPChar)+".";
			link.l1.go = "slaves_2";
		break;
		
		case "slaves_2":
			DialogExit();
			sGlobalTemp = npchar.id;
			DeleteAttribute(npchar, "LifeDay");
			DeleteAttribute(npchar, "CityType");//удалить признак фантома, иначе - пустые города
			SaveCurrentNpcQuestDateParam(npchar, "slaves_date");//запоминаем дату
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload4_back", npchar.city+"_church", "sit", "sit"+(1+rand(5)), "Nobleslaves_Place", 10.0);
			chrDisableReloadToLocation = true;//закрыть локацию
			Colonies[FindColony(npchar.city)].questslaves = true;
			sTitle = npchar.city+"Nobleslaves";
			ReOpenQuestHeader(sTitle);
			AddQuestRecordEx(sTitle, "Nobleslaves", "1");
			AddQuestUserDataForTitle(sTitle, "sCity", XI_ConvertString("Colony"+npchar.city+"Gen"));
			AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony"+npchar.city+"Gen"));
			AddQuestUserData(sTitle, "sName", GetFullName(npchar));
			AddQuestUserData(sTitle, "sQty", sti(npchar.quest.slaves.qty));
			AddQuestUserData(sTitle, "sMoney", sti(npchar.quest.slaves.money));
		break;
		
		case "slaves_3":
			if (GetNpcQuestPastDayParam(npchar, "slaves_date") < 180)
			{
				dialog.text = "Вы привезли мне "+sti(npchar.quest.slaves.qty)+" рабов, как я вас просил, капитан?";
				if (GetSquadronGoods(pchar, GOOD_SLAVES) >= sti(npchar.quest.slaves.qty))
				{
					link.l1 = "Да. Вся партия находится у меня в трюме. Я готов передать их вам.";
					link.l1.go = "slaves_4";
				}
				else
				{
					link.l1 = "Нет. Я ещё работаю над этим вопросом.";
					link.l1.go = "exit";
					NextDiag.TempNode = "slaves_3";
				}
			}
			else
			{
				dialog.text = "Капитан, если вы по поводу рабов - то я уже приобрёл достаточное количество и пока больше в них не нуждаюсь. Уж очень долго вы мне их везли.";
				link.l1 = "Эх, жаль! Но вы правы - затянул я с этим делом. До свидания!";
				link.l1.go = "slaves_8";
			}
		break;
		
		case "slaves_4":
			dialog.text = "Великолепно! Я немедленно распоряжусь прислать за ними барку.";
			link.l1 = "Что там насчёт моей оплаты?";
			link.l1.go = "slaves_5";
		break;
		
		case "slaves_5":
			dialog.text = "Не беспокойтесь, я не забыл об этом. Вот, держите оговоренную сумму - по "+sti(npchar.quest.slaves.price)+" дублона за раба.";
			link.l1 = "Благодарю, сударь. С вами приятно иметь дело!";
			link.l1.go = "slaves_6";
		break;
		
		case "slaves_6":
			RemoveCharacterGoods(pchar, GOOD_SLAVES, sti(npchar.quest.slaves.qty));
			TakeNItems(pchar, "gold_dublon", sti(npchar.quest.slaves.money));
			Log_Info("Вы получили "+FindRussianDublonString(sti(npchar.quest.slaves.money))+"");
			PlaySound("interface\important_item.wav");
			dialog.text = "Еще бы... А теперь прошу меня простить - дела ждут. Всего доброго!";
			link.l1 = "До свидания, "+GetAddress_FormToNPC(NPChar)+".";
			link.l1.go = "slaves_7";
		break;
		
		case "slaves_7":
			DialogExit();
			npchar.lifeday = 0;
			DeleteAttribute(Colonies[FindColony(npchar.city)], "questslaves");
			LAi_SetActorType(npchar);
			GetCharacterPos(pchar, &locx, &locy, &locz);
         	ChangeCharacterAddressGroup(npchar, npchar.city+"_church", "goto", LAi_FindNearestFreeLocator("goto", locx, locy, locz));
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "", 10.0);
			AddCharacterExpToSkill(pchar, "Commerce", 150);//торговля
			AddCharacterExpToSkill(pchar, "Sailing", 50);//навигация
			AddCharacterExpToSkill(pchar, "Fortune", 30);//везение
			ChangeCharacterComplexReputation(pchar, "nobility", -1);
			sTitle = npchar.city+"Nobleslaves";
			AddQuestRecordEx(sTitle, "Nobleslaves", "2");
			CloseQuestHeader(sTitle);
		break;

		case "slaves_8":
			DialogExit();
			npchar.lifeday = 0;
			LAi_CharacterDisableDialog(npchar);
			DeleteAttribute(Colonies[FindColony(npchar.city)], "questslaves");
			sTitle = npchar.city+"Nobleslaves";
			AddQuestRecordEx(sTitle, "Nobleslaves", "3");
			CloseQuestHeader(sTitle);
		break;
//<-- привезти рабов под заказ

		//замечание по обнаженному оружию от персонажей типа citizen
		case "CitizenNotBlade":
			dialog.text = NPCharSexPhrase(NPChar, "Послушайте, я, как гражданин этого города, прошу вас не ходить у нас с обнажённым клинком.", "Знаете, я, как гражданка этого города, прошу вас не ходить у нас с обнажённым клинком.");
			link.l1 = LinkRandPhrase("Хорошо.", "Ладно.", "Как скажете...");
			link.l1.go = "exit";
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "fight":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_SetHP(NPChar, 400, 400);
			TakeNItems(NPChar, "potion2", 3);
			SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
			LAi_group_MoveCharacter(NPChar, "TempFight");
			LAi_group_Attack(NPChar, Pchar);
			AddDialogExitQuest("MainHeroFightModeOn");
			ChangeCharacterNationReputation(pchar, sti(npchar.nation), -3);
		break;
	}
}

string DonationText()
{
	string sText;
	switch (drand(5))
	{
		case 0: sText = "Я вчера проигрался в карты, и на покрытие долга не хватает сущей безделицы. Не сможете меня выручить?" break;
		case 1: sText = "Я вчера здорово повеселился с одной... девкой, а теперь она меня пытается шантажировать. Мне нужно заплатить ей, ну а потом я уже с ней разберусь... Не могли бы вы мне помочь небольшой суммой?" break;
		case 2: sText = "Я тут на днях проткнул одного невежу шпагой, так теперь комендант требует мзду, чтобы замять дело. Мне не хватает совсем немного. Может, выручите?" break;
		case 3: sText = "Я имел неосторожность проиграть в споре, а на уплату долга чести у меня банально не хватает нескольких жалких монет. Не поможете?" break;
		case 4: sText = "Один негодяй узнал о моей причастности к пикантной истории с одной дамой... В общем, мне не хватает буквально несколько золотых, чтобы купить его молчание." break;
		case 5: sText = "Один негодяй выкрал из моего дома важные бумаги и требует за них кругленькую сумму. Я собрал всё, что нужно, но не хватает сущего пустяка. Выручите?" break;
	}
	return sText;
}

void LombardText()
{
	switch (drand(5))
	{
		case 0:
			pchar.GenQuest.Noblelombard.Item = "алмазные подвески моей матери работы мадридского ювелира";
			pchar.GenQuest.Noblelombard.Text = RandPhraseSimple("я получу причитающееся мне наследство","вернётся мой корабль из плавания к берегам Африки, с грузом рабов");
		break;
		case 1: pchar.GenQuest.Noblelombard.Item = "изумрудное колье моей сестры работы парижского ювелира";
				pchar.GenQuest.Noblelombard.Text = RandPhraseSimple("я вступлю в право наследования графством в Европе","вернётся мой корабль из плавания к берегам Индии, с грузом пряностей");
		break;
		case 2:
			pchar.GenQuest.Noblelombard.Item = "фамильный перстень с гербом нашего рода, передающийся от отца к сыну";
			pchar.GenQuest.Noblelombard.Text = RandPhraseSimple("вернётся моя экспедиция из глубин Мейна с золотыми слитками","я получу причитающееся мне наследство");
		break;
		case 3:
			pchar.GenQuest.Noblelombard.Item = "браслет жены с рубинами и бриллиантами, подарок её матери";
			pchar.GenQuest.Noblelombard.Text = RandPhraseSimple("я получу свой вклад с процентами из европейского банка","я получу прибыль от проводимой сейчас спекуляции");
		break;
		case 4:
			pchar.GenQuest.Noblelombard.Item = "ожерелье из золота и бриллиантов, штучной работы, гордость моей жены";
			pchar.GenQuest.Noblelombard.Text = RandPhraseSimple("я получу прибыль от проводимой сейчас спекуляции","вернётся мой корабль из плавания к берегам Африки, с грузом рабов");
		break;
		case 5:
			pchar.GenQuest.Noblelombard.Item = "трость из слоновой кости с самоцветами, подарок моего деда";
			pchar.GenQuest.Noblelombard.Text = RandPhraseSimple("вернётся мой корабль из плавания к берегам Индии, с грузом пряностей","я получу свой вклад с процентами из европейского банка");
		break;
	}
}