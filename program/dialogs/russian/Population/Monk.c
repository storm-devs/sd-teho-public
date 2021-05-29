//Jason общий диалог уличных монахов
#include "DIALOGS\russian\Rumours\Common_rumours.c"
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i, iTemp, iTest;
	string sTemp, sTitle;

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
	
	iTest = FindColony(NPChar.City);
    ref rColony;
	if (iTest != -1)
	{
		rColony = GetColonyByIndex(iTest);
	}
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			//--> диалог первой встречи
			if (npchar.quest.meeting == "0")
			{
				if (CheckAttribute(npchar, "quest.donation"))//пожертвования
				{
					dialog.text = "Добрый день, сын мой. Я прошу тебя оказать милость и пожертвовать несколько серебряных монет во благое дело.";
					link.l1 = "Ну, если благое дело - то конечно, жертвовать надо. Церковь учит помогать ближнему. А что за дело такое - я могу узнать?";
					link.l1.go = "donation";
					link.l2 = "Сожалею, но расставаться с деньгами в данный момент мне совершенно не с руки.";
					link.l2.go = "exit";
					npchar.quest.meeting = "1";
					DeleteAttribute(npchar, "talker"); //снимаем говорилку
					break;
				}
				bool ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
				if (ok && sti(Pchar.Ship.Type) != SHIP_NOTUSED && CheckAttribute(npchar, "quest.passenger") && !CheckAttribute(pchar, "GenQuest.Monkpassenger") && 6-sti(RealShips[sti(Pchar.Ship.Type)].Class) > 0 && 6-sti(RealShips[sti(Pchar.Ship.Type)].Class) < 3)//монах-пассажир
				{
					dialog.text = "Добрый день, сын мой. Я бы хотел попросить тебя об одной услуге. На возмездной основе, конечно.";
					link.l1 = "Слушаю вас, святой отец. О чём пойдёт речь?";
					link.l1.go = "passenger";
					link.l2 = "Простите, падре, но я очень спешу.";
					link.l2.go = "exit";
					npchar.quest.meeting = "1";
					DeleteAttribute(npchar, "talker"); //снимаем говорилку
					break;
				}
				if (sti(Pchar.Ship.Type) != SHIP_NOTUSED && CheckAttribute(npchar, "quest.capellan") && !CheckAttribute(pchar, "questTemp.ShipCapellan"))//корабельный капеллан
				{
					dialog.text = "Приветствую тебя, сын мой. Как я вижу, ты - капитан. Поэтому у меня к тебе есть предложение.";
					link.l1 = "Слушаю вас внимательно, святой отец.";
					link.l1.go = "capellan";
					npchar.quest.meeting = "1";
					DeleteAttribute(npchar, "talker"); //снимаем говорилку
					break;
				}
				dialog.text = PCharRepPhrase(LinkRandPhrase("Приветствую, сын мой. Какая нужда привела тебя ко мне?","Здравствуй, сын мой. Если ты желаешь покаяться в грехах своих - обратись к настоятелю церкви.","Добрый день, сын мой. Обрати свой взор к Господу, пока ещё не слишком поздно."),LinkRandPhrase("Приветствую, сын мой. Какая нужда привела тебя ко мне?","Здравствуй, сын мой, да будут благословенны дела твои!","Добрый день, сын мой. Да снизойдёт на тебя благодать Господня!"));
				link.l1 = LinkRandPhrase("И вам доброго дня, святой отец. Как ваши дела?","Здравствуйте, святой отец. Как дела в приходе?","Как ваши дела, святой отец?");
				link.l1.go = "check";//на возможную выдачу квестов
				link.l2 = RandPhraseSimple("У меня есть вопрос к вам.", "Мне нужна информация.");
				link.l2.go = "quests";//(перессылка в файл города)
				if (GetSquadronGoods(pchar, GOOD_SLAVES) > 0 && sti(pchar.money) >= GetSquadronGoods(pchar, GOOD_SLAVES)*10)
				{
					link.l3 = "Святой отец, у меня на борту находятся люди. Это обращённые в рабство христиане и некрещёные. Я бы хотел попросить вас окрестить некрещёных, причастить крещёных, а я затем отпущу их на свободу во славу нашей церкви.";
					link.l3.go = "slaves";
				}
				if (sti(Pchar.Ship.Type) != SHIP_NOTUSED && sti(pchar.reputation.nobility) > 41 && !CheckAttribute(pchar, "GenQuest.Shipshine") && 6-sti(RealShips[sti(Pchar.Ship.Type)].Class) > 0)
				{
					link.l4 = "Святой отец, я бы хотел попросить вас освятить мой корабль. Сколько это будет мне стоить?";
					link.l4.go = "shipshine";
				}
				link.l10 = LinkRandPhrase("Извините, святой отец, мне пора идти.","Простите за беспокойство, святой отец.","Мне нужно отправляться на корабль, святой отец. До свидания!");
				link.l10.go = "exit";
				npchar.quest.meeting = "1";
			}
			else
			{
				//--> диалог второй встречи
				dialog.text = LinkRandPhrase("Это снова ты, сын мой? Что ты хотел?","Ты что-то ещё хотел сказать мне, сын мой?","Рад снова видеть тебя, сын мой.");
				link.l1 = LinkRandPhrase("Хотел спросить, святой отец, как ваши дела?","Хотел спросить, святой отец, как дела в приходе?","Как ваши дела, святой отец?");
				link.l1.go = "check";//на возможную выдачу квестов
				link.l2 = RandPhraseSimple("У меня есть вопрос к вам.", "Мне нужна информация.");
				link.l2.go = "quests";//(перессылка в файл города)
				if (GetSquadronGoods(pchar, GOOD_SLAVES) > 0 && sti(pchar.money) >= GetSquadronGoods(pchar, GOOD_SLAVES)*10 && !CheckAttribute(npchar, "quest.slaves"))
					{
						link.l3 = "Святой отец, у меня на борту находятся люди. Это обращённые в рабство христиане и некрещёные. Я бы хотел попросить вас окрестить некрещёных, причастить крещёных, а я затем отпущу их на свободу во славу нашей церкви.";
						link.l3.go = "slaves";
					}
				if (sti(Pchar.Ship.Type) != SHIP_NOTUSED && sti(pchar.reputation.nobility) > 41 && !CheckAttribute(pchar, "GenQuest.Shipshine") && 6-sti(RealShips[sti(Pchar.Ship.Type)].Class) > 0)
				{
					link.l4 = "Святой отец, я бы хотел попросить вас освятить мой корабль. Сколько это будет мне стоить?";
					link.l4.go = "shipshine";
				}
				link.l10 = LinkRandPhrase("Извините, святой отец, мне пора идти.","Простите за беспокойство, святой отец.","Мне нужно отправляться на корабль, святой отец. До свидания!");
				link.l10.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "check":
			if (sti(Pchar.Ship.Type) != SHIP_NOTUSED && rand(8) < 3 && !CheckAttribute(npchar, "quest.monkletter") && !CheckAttribute(pchar, "GenQuest.Monkletter") && !CheckAttribute(npchar, "quest.passenger")) //церковная депеша
			{
				pchar.GenQuest.Monkletter.City = FindFriendCityToMC(false);
				pchar.GenQuest.Monkletter.StartCity = npchar.city;//город квестодателя
				dialog.text = "У меня как раз есть просьба к тебе, сын мой. Мне необходимо по возможности быстрее передать бумаги для настоятеля церкви "+XI_ConvertString("Colony"+pchar.GenQuest.Monkletter.City+"Gen")+". Ты случаем не в ту сторону отправляешься? Нужно доставить документы за две недели...";
				link.l1 = "Я без труда смогу помочь вам, святой отец. Давайте ваши бумаги, я передам их в церковь "+XI_ConvertString("Colony"+pchar.GenQuest.Monkletter.City+"Gen")+".";
				link.l1.go = "Monkletter";
				link.l2 = "Я бы и рад, святой отец, но мне совсем в другую сторону.";
				link.l2.go = "exit_monkletter";
				npchar.quest.monkletter = "true";
				break;
			}
			if (sti(Pchar.Ship.Type) != SHIP_NOTUSED && rand(8) > 5 && sti(pchar.rank < 11) && !CheckAttribute(npchar, "quest.churchbooks") && !CheckAttribute(pchar, "GenQuest.Churchbooks") && !CheckAttribute(npchar, "quest.passenger")) //привезти молитвенники
			{
				pchar.GenQuest.Churchbooks.StartCity = npchar.city;//город квестодателя
				pchar.GenQuest.Churchbooks.Nation = npchar.nation;
				dialog.text = "Сын мой, не согласишься ли мне помочь в одном несложном деле? В нашей церкви заканчиваются молитвенники, которые мы безвозмездно раздаём нашим прихожанам по их просьбе\nНе мог бы ты отправиться в ближайшую колонию "+NationNameGenitive(sti(npchar.nation))+", взять у настоятеля тамошней церкви несколько десятков молитвенников и привезти в наш приход? И если возможно - сделай это за месяц: молитвенники уже на исходе.";
				link.l1 = "С удовольствием помогу вашей церкви. Молитвенники можно получить у любого настоятеля?";
				link.l1.go = "Churchbooks";
				link.l2 = "Я бы и рад, святой отец, но у меня действительно сейчас нет такой возможности.";
				link.l2.go = "exit_churchbooks";
				npchar.quest.churchbooks = "true";
				break;
			}
			
			dialog.text = RandPhraseSimple("Всё хорошо, сын мой. Спасибо за беспокойство о делах церкви.", "В нашем приходе всё спокойно, сын мой. Благодарю за проявленную заботу о благополучии церкви.");
			link.l1 = "Тогда я пойду по своим делам, святой отец.";
			link.l1.go = "exit";
		break;
		
//-------------------------------------------------пожертвования------------------------------------------------
		case "donation":
			sTemp = DonationType();
			dialog.text = "Конечно, сын мой. "+sTemp+"";
			link.l1 = "Какое пожертвование будет считаться достаточным?";
			link.l1.go = "donation_1";
		break;
		
		case "donation_1":
			dialog.text = "Сколько позволит тебе твой кошель и твоё личное желание, сын мой. Я буду рад любому дару.";
			link.l1 = "100 песо.";
			link.l1.go = "donation_rate_1";
			link.l2 = "1000 песо.";
			link.l2.go = "donation_rate_2";
			link.l3 = "5000 песо.";
			link.l3.go = "donation_rate_3";
			link.l4 = "10000 песо.";
			link.l4.go = "donation_rate_4";
		break;
		
		case "donation_rate_1"://никаких плюшек
			if (sti(pchar.money) >= 100)
			{
				AddMoneyToCharacter(pchar, -100);
				dialog.text = "Благодарю тебя, сын мой, за твои монеты. Они пойдут на благое дело!";
				link.l1 = "Да не за что, святой отец.";
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = "Кара Господня ждёт тебя, нечестивец! Насмешка над служителем святой церкви - богохульство!";
				link.l1 = "Ха-ха! Я не подаю милостыни. Проваливай!";
				link.l1.go = "donation_exit";
			}
		break;
		
		case "donation_rate_2":
			if (sti(pchar.money) >= 1000)
			{
				AddMoneyToCharacter(pchar, -1000);
				dialog.text = "Благодарю тебя, сын мой. Эта сумма очень поможет в моих благих начинаниях. Благословляю тебя!";
				link.l1 = "Успехов в вашем нелёгком деле, святой отец!";
				link.l1.go = "exit";
				AddCharacterHealth(pchar, 5);
				AddCharacterExpToSkill(pchar, "Leadership", 20);
				AddCrewMorale(pchar, 2);
			}
			else
			{
				dialog.text = "Кара Господня ждёт тебя, нечестивец! Насмешка над служителем святой церкви - богохульство!";
				link.l1 = "Ха-ха! Я не подаю милостыни. Проваливай!";
				link.l1.go = "donation_exit";
			}
		break;
		
		case "donation_rate_3":
			if (sti(pchar.money) >= 5000)
			{
				AddMoneyToCharacter(pchar, -5000);
				dialog.text = "Я даже не мог подумать, что ты будешь столь щедр, сын мой. Благословляю тебя и с благодарностью принимаю твои деньги.";
				link.l1 = "Мне не жаль денег на богоугодное дело. Успехов вам, святой отец!";
				link.l1.go = "exit";
				AddCharacterHealth(pchar, 5);
				AddCharacterExpToSkill(pchar, "Leadership", 40);
				AddCrewMorale(pchar, 3);
				ChangeCharacterComplexReputation(pchar, "nobility", 1);
				ChangeCharacterNationReputation(pchar, sti(npchar.Nation), 1);
			}
			else
			{
				dialog.text = "Кара Господня ждёт тебя, нечестивец! Насмешка над служителем святой церкви - богохульство!";
				link.l1 = "Ха-ха! Я не подаю милостыни. Проваливай!";
				link.l1.go = "donation_exit";
			}
		break;
		
		case "donation_rate_4":
			if (sti(pchar.money) >= 10000)
			{
				AddMoneyToCharacter(pchar, -10000);
				dialog.text = "Я не ослышался, сын мой? Ты действительно жертвуешь десять тысяч? Благословляю тебя и с благодарностью принимаю столь щедрое подношение - огромный вклад в благое дело!";
				link.l1 = "Мы все должны по силам помогать святой церкви. Я могу позволить себе потратить такую сумму, и я с радостью передаю её вам. Успехов, святой отец!";
				link.l1.go = "exit";
				AddCharacterHealth(pchar, 10);
				AddCharacterExpToSkill(pchar, "Leadership", 60);
				AddCrewMorale(pchar, 5);
				ChangeCharacterComplexReputation(pchar, "nobility", 1);
				ChangeCharacterNationReputation(pchar, sti(npchar.Nation), 2);
				ChangeCrewExp(pchar, "Sailors", 5);
				ChangeCrewExp(pchar, "Cannoners", 5);
				ChangeCrewExp(pchar, "Soldiers", 5);
			}
			else
			{
				dialog.text = "Кара Господня ждёт тебя, нечестивец! Насмешка над служителем святой церкви - богохульство!";
				link.l1 = "Ха-ха! Я не подаю милостыни. Проваливай!";
				link.l1.go = "donation_exit";
			}
		break;
		
		case "donation_exit":
			DialogExit();
			ChangeCharacterComplexReputation(pchar, "nobility", -1);
			AddCharacterHealth(pchar, -5);
			LAi_CharacterDisableDialog(npchar);
		break;
		
//-------------------------------------------отпустить рабов---------------------------------------------------
		case "slaves":
			dialog.text = "Конечно, сын мой. Наш долг - помогать страдальцам. Я выполню твою просьбу.";
			link.l1 = "Благодарю, святой отец. Я пожертвую на благо церкви по десять серебряных монет за каждого окрещённого и причащённого узника.";
			link.l1.go = "slaves_1";
		break;
		
		case "slaves_1":
			AddMoneyToCharacter(pchar, -GetSquadronGoods(pchar, GOOD_SLAVES)*10);
			dialog.text = "Очень хорошо, сын мой, что ты не забываешь к словесной благодарности присоединить благодарность материальную. Твои деньги пойдут на благое дело. Теперь пойдём на твой корабль?";
			link.l1 = "Да, падре. Следуйте за мной!";
			link.l1.go = "slaves_2";
		break;
		
		case "slaves_2":
			npchar.quest.slaves = "true";
			DialogExit();
			SetLaunchFrameFormParam("Прошло два часа"+ NewStr() +"Рабы отпущены на свободу", "Monk_RemoveSlaves", 0, 4);
			LaunchFrameForm();
			WaitDate("", 0, 0, 0, 2, 10); //крутим время
			RecalculateJumpTable();
		break;
//<-- отпустить рабов

//----------------------------------------------освятить корабль------------------------------------------------
		case "shipshine":
			//поиск старшего класса
			iTemp = 6;
			for (i=0; i<COMPANION_MAX; i++)
			{
				int iIdx = GetCompanionIndex(GetMainCharacter(), i);
				if (iIdx >= 0)
				{
					sld = GetCharacter(iIdx);
					if (GetCharacterShipClass(sld) < iTemp) iTemp = GetCharacterShipClass(sld);
				}
			}
			switch (GetCompanionQuantity(pchar))
			{
				case 1: 
					sTemp = "У меня в эскадре один корабль, "+iTemp+" класса.";
					pchar.GenQuest.Shipshine.Money = 5000*(6-iTemp);
				break;
				case 2:
					sTemp = "У меня в эскадре два корабля, наибольший - "+iTemp+" класса.";
					pchar.GenQuest.Shipshine.Money = makeint(1.8*(5000*(6-iTemp)));
				break;
				case 3:
					sTemp = "У меня в эскадре три корабля, наибольший - "+iTemp+" класса.";
					pchar.GenQuest.Shipshine.Money = makeint(2.6*(5000*(6-iTemp)));
				break;
				case 4:
					sTemp = "У меня в эскадре четыре корабля, наибольший - "+iTemp+" класса.";
					pchar.GenQuest.Shipshine.Money = makeint(3.4*(5000*(6-iTemp)));
				break;
				case 5:
					sTemp = "У меня в эскадре пять кораблей, наибольший - "+iTemp+" класса.";
					pchar.GenQuest.Shipshine.Money = makeint(4.2*(5000*(6-iTemp)));
				break;
			}
			dialog.text = "Это будет зависеть от того, сколько у тебя кораблей в эскадре, и насколько они велики.";
			link.l1 = ""+sTemp+"";
			link.l1.go = "shipshine_1";
		break;
		
		case "shipshine_1":
			dialog.text = "Это обойдётся тебе в "+FindRussianMoneyString(sti(pchar.GenQuest.Shipshine.Money))+", сын мой.";
			if (sti(pchar.money) >= sti(pchar.GenQuest.Shipshine.Money))
			{
				link.l1 = "Я готов заплатить эту сумму, падре. Вот деньги.";
				link.l1.go = "shipshine_2";
			}
			link.l2 = "К сожалению, у меня нет такой суммы.";
			link.l2.go = "shipshine_exit";
		break;
		
		case "shipshine_2":
			AddMoneyToCharacter(pchar, -sti(pchar.GenQuest.Shipshine.Money));
			dialog.text = "Хорошо, сын мой. Тогда не будем медлить и отправимся в порт.";
			link.l1 = "Следуйте за мной, святой отец...";
			link.l1.go = "shipshine_3";
		break;
		
		case "shipshine_3":
			DialogExit();
			SetLaunchFrameFormParam("Прошло несколько часов"+ NewStr() +"Падре выполнил освящение", "Monk_Shipshine", 0, 4);
			LaunchFrameForm();
			WaitDate("", 0, 0, 0, GetCompanionQuantity(pchar), 10); //крутим время
			RecalculateJumpTable();
		break;
		
		case "shipshine_exit":
			DialogExit();
			DeleteAttribute(Pchar, "GenQuest.Shipshine");
		break;
//<-- освятить корабль

//------------------------------------------корабельный капеллан-----------------------------------------------
		case "capellan":
			dialog.text = "Я - корабельный капеллан со стажем. С прошлого места службы я уволился из нравственных соображений. Сейчас я ищу нового капитана, к которому я бы нанялся на судно. Не желаете зачислить меня в команду?";
			link.l1 = "Корабельный священник? Скажите, падре, а какую функцию вы будете выполнять на корабле?";
			link.l1.go = "capellan_1";
			pchar.questTemp.ShipCapellan = "true";
		break;
		
		case "capellan_1":
			dialog.text = "Сын мой, это же просто. Я молюсь Господу за тебя и твою команду, благословляю твоих матросов перед боем, моё слово дарует им крепость руки и духа. Твоя команда будет регулярно причащаться и исповедоваться, а матрос с чистой душой выживет там, где нечестивец непременно погибнет\nДля себя же я прошу немного: единоразовое пособие в размере пятидесяти тысяч песо, койку в каюте и стол, как для твоих офицеров. И всё.";
			if (sti(pchar.money) >= 50000)
			{
				link.l1 = "Очень интересно... Вы правы - хороший капитан должен заботиться не только о бренных матросских телах, но также и об их бессмертных душах. Добро пожаловать на борт, падре!";
				link.l1.go = "capellan_2";
			}
			link.l2 = "Нет, падре. К сожалению, у меня недостаточно средств, чтобы оплатить ваши услуги.";
			link.l2.go = "capellan_exit";
		break;
		
		case "capellan_exit":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
		break;
		
		case "capellan_2":
			AddMoneyToCharacter(pchar, -50000);
			chrDisableReloadToLocation = true;//закрыть локацию
			dialog.text = "Благодарю за доверие, сын мой. Ты недаром потратил свои деньги. Но хочу сразу предупредить тебя: я служу только достойным капитанам, неважно, торговец он или капер. Но я никогда не стану проповедовать на борту пиратского судна!\nЕсли ты вдруг решишь поднять на флагштоке Весёлого Роджера и творить бесчинства под пиратским флагом - я немедленно покину твой корабль в первом же порту.";
			link.l1 = "Я учту это, святой отец, и постараюсь не разочаровать вас. А теперь будьте добры проследовать на моё судно!";
			link.l1.go = "capellan_3";
		break;
		
		case "capellan_3":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "My_Campus", "rld", "loc1", "Monk_Capellan", -1);
			pchar.questTemp.ShipCapellan.id = npchar.id;
			DeleteAttribute(npchar, "LifeDay");
			DeleteAttribute(npchar, "CityType");//удалить признак фантома
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, false);
			pchar.questTemp.ShipCapellan.Yes = "true";//капеллан в команде
			ChangeCharacterComplexReputation(pchar, "authority", 5);
			npchar.reputation = 60;
		break;
		
		case "capellan_4":
			dialog.text = "Ты что-то хотел, сын мой?";
			link.l1 = "Нет, ничего, святой отец.";
			link.l1.go = "exit";
			link.l2 = "Падре, я бы хотел попросить вас в ближайшем порту сойти на берег. Позвольте мне не объяснять причины моего решения.";
			link.l2.go = "capellan_5";
			NextDiag.TempNode = "capellan_4";
		break;
		
		case "capellan_5":
			dialog.text = "Хорошо, сын мой. Как скажешь - на своём корабле ты волен принимать решения, какие считаешь нужными. Я сойду в первом же поселении.";
			link.l1 = "Спасибо за понимание, святой отец.";
			link.l1.go = "capellan_6";
		break;
		
		case "capellan_6":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			ShipCapellan_Remove();
		break;
		
		case "capellan_7":
			dialog.text = "Я вас предупреждал, капитан: будете пиратствовать - ноги моей не будет на вашем судне. В первом же порту я схожу на берег.";
			link.l1 = "Гм...";
			link.l1.go = "exit";
			NextDiag.TempNode = "capellan_7";
		break;
//<-- капеллан
	
//--------------------------------------------монах-пассажир---------------------------------------------------
		case "passenger":
			if (drand(19) < 15) SetPassengerParameter("Monkpassenger", false);
			else SetPassengerParameter("Monkpassenger", true);
			dialog.text = "Сын мой, мне срочно нужно добраться до колонии " + XI_ConvertString("Colony"+pchar.GenQuest.Monkpassenger.City)+", это на "+XI_ConvertString(GetIslandByCityName(pchar.GenQuest.Monkpassenger.City)+"Dat")+", за "+FindRussianDaysString(sti(pchar.GenQuest.Monkpassenger.DaysQty))+". За это я заплачу тебе "+FindRussianMoneyString(sti(pchar.GenQuest.Monkpassenger.Money))+". Что скажешь?";
			link.l1 = "Я согласен, святой отец.";
			link.l1.go = "passenger_1";
			link.l2 = "Сожалею, святой отец, но мне совсем в другую сторону. Ничем не могу помочь.";
			link.l2.go = "passenger_exit";
			npchar.quest.passenger = true;
		break;
		
		case "passenger_exit":
			dialog.text = "На всё воля Божья, сын мой. Подожду другого корабля. Ступай с миром!";
			link.l1 = "До свидания, падре.";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "GenQuest.Monkpassenger");
		break;
		
		case "passenger_1":
			dialog.text = "Благодарю тебя. Оплату получишь по прибытии на место.";
			link.l1 = "Отправляйтесь на моё судно, святой отец. Мы скоро отправляемся.";
			link.l1.go = "passenger_2";
		break;
		
		case "passenger_2":
			DialogExit();
			pchar.GenQuest.Monkpassenger.id = npchar.id;
			DeleteAttribute(npchar, "LifeDay");
			LAi_RemoveLoginTime(npchar);
			DeleteAttribute(npchar, "CityType");//удалить признак фантома, иначе - пустые города
			LAi_SetImmortal(npchar, true);
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
			AddQuestUserDataForTitle(sTitle, "sType", "монаха");
			AddQuestUserDataForTitle(sTitle, "sName", GetFullName(npchar));
			sTemp = XI_ConvertString("Colony" +pchar.GenQuest.Monkpassenger.City+"Gen") + ", что на " + XI_ConvertString(GetIslandByCityName(pchar.GenQuest.Monkpassenger.City)+"Dat")+".";
			AddQuestUserDataForTitle(sTitle, "sCity", sTemp);
			AddQuestUserData(sTitle, "sName", GetFullName(npchar));
			AddQuestUserData(sTitle, "sCity", sTemp);
			AddQuestUserData(sTitle, "sDays", FindRussianDaysString(sti(pchar.GenQuest.Monkpassenger.DaysQty)));
            AddQuestUserData(sTitle, "sMoney", FindRussianMoneyString(sti(pchar.GenQuest.Monkpassenger.Money)));
			AddQuestUserData(sTitle, "sName", GetFullName(npchar));
			pchar.quest.Monkpassenger.win_condition.l1 = "location";
			pchar.quest.Monkpassenger.win_condition.l1.location = pchar.GenQuest.Monkpassenger.City+"_town";
			pchar.quest.Monkpassenger.function = "Monkpassenger_complete";
			SetFunctionTimerCondition("Monkpassenger_Over", 0, 0, sti(pchar.GenQuest.Monkpassenger.DaysQty), false);
		break;
		
		case "passenger_3":
			pchar.quest.Monkpassenger_Over.over = "yes"; //снять таймер
			dialog.text = "Благодарствую, сын мой. Ты выполнил свои обязательства, теперь моя очередь выполнить свои. Держи деньги, как я и обещал.";
			link.l1 = "Спасибо. Удачи, святой отец!";
			link.l1.go = "passenger_4";
		break;
		
		case "passenger_4":
			DialogExit();
			npchar.lifeday = 0;
			RemovePassenger(Pchar, npchar);
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload4_back", "none", "", "", "", 20.0);
			AddMoneyToCharacter(pchar, sti(pchar.GenQuest.Monkpassenger.Money));
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
			ChangeCharacterComplexReputation(pchar, "fame", 1);
			OfficersReaction("good");				
			AddCharacterExpToSkill(pchar, "Sailing", 80);
			AddCharacterExpToSkill(pchar, "Leadership", 20);
			if (CheckAttribute(pchar, "GenQuest.Monkpassenger.Enemycity")) AddCharacterExpToSkill(pchar, "Sneak", 50);
			sTitle = npchar.index+"Citizpassenger";
			AddQuestRecordEx(sTitle, "Citizpassenger", "3");
			CloseQuestHeader(sTitle);
			DeleteAttribute(Pchar, "GenQuest.Monkpassenger");
		break;
//<-- монах-пассажир
		
//---------------------------------------------церковная депеша-------------------------------------------------
		case "exit_monkletter":
			DialogExit();
			DeleteAttribute(pchar, "GenQuest.Monkletter");
		break;
		
		case "Monkletter":
			dialog.text = "Вот. Держи этот пакет, сын мой. Помни - тебе нужно привезти его в течение двух недель, настоятель очень ждёт. Ступай, и да хранит тебя Господь в твоих странствиях!";
			link.l1 = "Я не подведу, святой отец. До свидания!";
			link.l1.go = "Monkletter_1";
		break;
		
		case "Monkletter_1":
			DialogExit();
			GiveItem2Character(pchar, "letter_church");
			ReOpenQuestHeader("Monkletter");
			AddQuestRecord("Monkletter", "1");
			AddQuestUserData("Monkletter", "sCity", XI_ConvertString("Colony"+pchar.GenQuest.Monkletter.City+"Gen"));
			AddQuestUserData("Monkletter", "sStartCity", XI_ConvertString("Colony"+pchar.GenQuest.Monkletter.StartCity));
			SetFunctionTimerCondition("Monkletter_Over", 0, 0, 15, false);
			OfficersReaction("good");
		break;
//<-- Церковная депеша
		
//-------------------------------------------доставить молитвенники---------------------------------------------
		case "exit_churchbooks":
			DialogExit();
			DeleteAttribute(pchar, "GenQuest.Churchbooks");
		break;

		case "Churchbooks":
			dialog.text = "Да. Ты сможешь получить их в любой колонии "+NationNameGenitive(sti(npchar.nation))+". Полученные молитвенники отдай нашему святому отцу, в церковь. Да охранит тебя Господь в пути!";
			link.l1 = "Спасибо. Скоро молитвенники будут у вас.";
			link.l1.go = "Churchbooks_1";
		break;
		
		case "Churchbooks_1":
			DialogExit();
			ReOpenQuestHeader("Churchbooks");
			AddQuestRecord("Churchbooks", "1");
			AddQuestUserData("Churchbooks", "sNation", NationNameGenitive(sti(pchar.GenQuest.Churchbooks.Nation)));
			AddQuestUserData("Churchbooks", "sStartCity", XI_ConvertString("Colony"+pchar.GenQuest.Churchbooks.StartCity));
			SetFunctionTimerCondition("Churchbooks_Over", 0, 0, 30, false);
			pchar.GenQuest.Churchbooks = "go";
			switch (rand(4))
			{
				case 0: pchar.GenQuest.Churchbooks.Item = "amulet_2"; break;
				case 1: pchar.GenQuest.Churchbooks.Item = "amulet_3"; break;
				case 2: pchar.GenQuest.Churchbooks.Item = "amulet_6"; break;
				case 3: pchar.GenQuest.Churchbooks.Item = "amulet_7"; break;
				case 4: pchar.GenQuest.Churchbooks.Item = "amulet_10"; break;
			}
			OfficersReaction("good");
		break;
//<-- доставить молитвенники
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}

string DonationType()
{
	string sText;
	switch (drand(9))
	{
		case 0: sText = "Я собираю деньги на постройку "+LinkRandPhrase("часовни","богадельни","лазарета")+". Местные жители подают мало и неохотно, и я вынужден обращаться к состоятельным людям вроде вас." break;
		case 1: sText = "Я собираю пожертвования для нашей церкви. Не у каждого моряка есть время посетить храм Божий, но каждый должен стараться спасти свою грешную душу." break;
		case 2: sText = "Я собираю деньги на покупку лекарств для нашего приюта сирых и немощных. Пожертвуйте, ибо каждый из нас под старость может оказаться там." break;
		case 3: sText = "Я собираю средства на новую утварь для нашей церкви - привезённая из Европы уже фактически пришла в негодность. Забота о церкви - долг каждого истинного христианина." break;
		case 4: sText = "Я собираю деньги на ремонт нашей церкви - кровля протекает даже в небольшой дождь, и церковные скамьи нуждаются в починке. Забота о церкви - долг каждого истинного христианина." break;
		case 5: sText = "Я собираю денежные средства, чтобы оплатить труд хорошего живописца, который сможет расписать стены нашей церкви замечательными картинами на библейские сюжеты. Помогать церкви в сим благом деле - долг каждого истинного христианина." break;
		case 6: sText = "Я собираю деньги на новый иконостас для нашей церкви. Приход у нас бедный, и дело продвигается медленно. Я надеюсь на вашу помощь." break;
		case 7: sText = "В нашем лазарете сейчас много раненых моряков с военного корабля. Им требуются лекарства и перевязочный материал. Помогите им, ибо вы, как никто другой, должны понимать страдания простых матросов." break;
		case 8: sText = "Я пытаюсь собрать деньги на пропитание и одежду для беднейших жителей нашей колонии, у которых одна надежда - на святую церковь. Помогите им." break;
		case 9: sText = "Я намереваюсь отбыть с миссионерской целью в глубь острова к коренным жителям, нести свет заблудшим душам, и собираю средства на организацию экспедиции. Помогите же и вы благому делу!" break;
	}
	return sText;
}