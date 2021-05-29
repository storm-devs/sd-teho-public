// реплики солдат на палубе при разговоре в море
// форт-стража и комендант форта
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	switch(Dialog.CurrentNode)
	{
        case "exit":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
		break;
		
        case "First time":
			dialog.text = "Поговорите с нашим капитаном. Мне нечего вам сказать";
			Link.l1 = "Хорошо.";
			Link.l1.go = "exit";
			
			NextDiag.TempNode = "first time";
		break;
		//  на палубе -->
		case "On_Deck":
			dialog.text = "Поговорите с нашим капитаном. Мне нечего вам сказать";
			Link.l1 = "Хорошо.";
			Link.l1.go = "exit";

			NextDiag.TempNode = "On_Deck";
/*			
			// Первый церковный генератор
			if(CheckAttribute(PChar, "GenQuest.ChurchQuest_1.CapWaitOnTavern"))
			{
				if(CheckAttribute(PChar, "GenQuest.ChurchQuest_1.NeedToDialogWithSailors"))
				{
					dialog.text = "Госпо"+ GetSexPhrase("дин","жа") +", вы кого-то ищете?";
					Link.l1 = "Да, парень. Могу я видеть капитана этого судна?";
					Link.l1.go = "ChurchQuest1_Node1";
				}
				else
				{
					dialog.text = "По всем вопросам обращайтесь к капитану. Он недавно сошёл на берег.";
					Link.l1 = "Хорошо-хорошо";
					Link.l1.go = "exit";
				}
				break;
			}
*/			
			//--> eddy. квест мэра, закрываем выход с палубы и ноду даем нужную
			if (CheckAttribute(pchar, "GenQuest.DestroyPirate") && pchar.GenQuest.CaptainId == "MQPirate")
			{
	    		dialog.text = RandPhraseSimple("Надо же, сам"+ GetSexPhrase("","а") +" к нам приш"+ GetSexPhrase("ёл","ла") +"... Ну, раз приш"+ GetSexPhrase("ёл","ла") +", то иди к кэпу. Поговоришь о делах своих скорбных...",
	                                           "Хех, ну ты даёшь, "+ GetSexPhrase("приятель","подруга") +"! Такого я ещё не видал... Подойди к капитану, он с тобой будет говорить.");
				Link.l1 = "Жаль...";
				Link.l1.go = "exit";
			}
			//<-- eddy. квест мэра, закрываем выход с палубы
		break;
/*		
		case "ChurchQuest1_Node1":
			dialog.text = "Вам лучше поискать его в порту.";
			Link.l1 = "Спасибо, любезный.";
			Link.l1.go = "exit";
			NextDiag.TempNode = "On_Deck";
			PChar.GenQuest.ChurchQuest_1.CapWaitOnTavern = true; 
			DeleteAttribute(PChar, "GenQuest.ChurchQuest_1.NeedToDialogWithSailors"); // Не спрашиваем моряков
		break;
*/		
        //  на палубе <--
				
		// ugeen --> разговор с боцманом по генератору "Повод для спешки"
		case "On_MyShip_Deck":
			dialog.text = "Ну и навели же Вы шороху, капитан! Мы с ребятами только заказали ещё по стаканчику, как услышали вопли на улице. Выскочив из таверны и узнав, что Вас пытаются арестовать, мы решили рубить концы и уходить из этой негостеприимной гавани.";
			link.l1 = "Да уж, у некоторых людей странное понимание справедливости.";
			link.l1.go = "On_MyShip_Deck_1";
		break;
		
		case "On_MyShip_Deck_1":
		    if(pchar.questTemp.ReasonToFast == "speakSuccess_chain_A") 
			{
				// карты не было
				dialog.text = "Капитан! Бросьте печалиться! Раз уж всё равно было миром не уйти, в суматохе мы решили заскочить к местному ростовщику и слегка облегчили его сундуки. Вот Ваша доля - " + sti(pchar.questTemp.ReasonToFast.p9) + " песо...";
			}
			if(pchar.questTemp.ReasonToFast == "speakSuccess_chain_B")
			{
				// карту отобрали
				GiveItem2Character(pchar, pchar.questTemp.ReasonToFast.p6);
				dialog.text = "Капитан! Бросьте печалиться! Раз уж всё равно было миром не уйти, в суматохе мы решили заскочить к местному ростовщику и слегка облегчили его сундуки. Да ещё и клинок приличный прихватили из ломбардного шкафа. Вот Ваша доля - " + sti(pchar.questTemp.ReasonToFast.p9) + " песо и клинок...";
			}		
			link.l1 = "Весьма кстати. Молодцы!";
			link.l1.go = "On_MyShip_Deck_End";
			AddMoneyToCharacter(pchar, sti(pchar.questTemp.ReasonToFast.p9));			
			pchar.Ship.Crew.Morale = MORALE_MAX;
			chrDisableReloadToLocation = false; // Откроем выход
			AddQuestRecord("ReasonToFast", "17");		
			AddQuestUserData("ReasonToFast", "sSex", GetSexPhrase("ся","ась"));		
			CloseQuestHeader("ReasonToFast");
			DeleteAttribute(pchar,"TownEscape");
			DeleteAttribute(pchar,"questTemp.ReasonToFast");
			QuestOpenSeaExit();
		break;
		
		case "On_MyShip_Deck_End":
			DialogExit();
			AddDialogExitQuest("CanEnterToMap");
		break;
		
		// разговор с боцманом по генератору 'Операция Галеон'
		case "CapComission_OnShipDeck":
			dialog.text = "Капитан, ваш приятель сбежал.";
			link.l1 = "Какой приятель?";
			link.l1.go = "CapComission_OnShipDeck1";
		break;
		
		case "CapComission_OnShipDeck1":
			dialog.text = "Ну этот, которого вы из тюрьмы вытащили.";
			link.l1 = "Да как же вы могли его проворонить?!!";
			link.l1.go = "CapComission_OnShipDeck2";
		break;
		
		case "CapComission_OnShipDeck2":
			dialog.text = "Да мы-то чего? Он ночью через гальюнные брусья перелез, якобы по нужде, а сам спустился по якорному канату и вплавь... Мы стреляли, но темно было...";
			link.l1 = "Чёрт!!! Совсем распустились! Всех на берег спишу, будете тростник на плантациях окучивать! Такую ценную птицу упустили!..";
			link.l1.go = "CapComission_OnShipDeck3";
		break;
		
		case "CapComission_OnShipDeck3":
			chrDisableReloadToLocation = false; // Откроем выход
			AddQuestRecord("CaptainComission2", "25");	
			AddQuestUserData("CaptainComission2", "sSex", GetSexPhrase("","а"));			
			AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);
			CloseQuestHeader("CaptainComission2");	
			ChangeOfficersLoyality("bad_all", 1);
			ChangeCharacterComplexReputationABS(pchar, "authority", 1);
			DeleteAttribute(pchar,"TownEscape");
			DeleteAttribute(pchar,"GenQuest.CaptainComission.canSpeakBoatswain");
			DeleteAttribute(pchar, "GenQuest.CaptainComission");
			QuestOpenSeaExit();		
			DialogExit();
			AddDialogExitQuest("CanEnterToMap");
		break;
		// <-- ugeen
		
		// разговор с боцманом по ситуациям в трюме
		case "Hold_GenQuest_OnShipDeck":
			dialog.text = "Капитан, простите, не доглядели - пленный сбежал.";
			link.l1 = "Что за пленный? Кто сбежал?";
			link.l1.go = "Hold_GenQuest_OnShipDeck1";
		break;
				
		case "Hold_GenQuest_OnShipDeck1":
			dialog.text = "Да этот, как его, " + pchar.GenQuest.Hold_GenQuest.CapName + " что ли.";
			link.l1 = "Вот чёрт! Куда же вы смотрели?!";
			link.l1.go = "Hold_GenQuest_OnShipDeck2";
		break;
		
		case "Hold_GenQuest_OnShipDeck2":
			dialog.text = "Да он из трюма выбрался, сиганул через фальшборт и был таков. Мы стрелять не стали, чтоб шуму не поднимать, а пока спустили шлюпку, его уже рыбаки подобрали.";
			link.l1 = "За что я вам только жалование плачу! Старшего вахты высечь и лишить недельной пайки рому. Все по местам! Снимаемся с якоря...";
			link.l1.go = "Hold_GenQuest_OnShipDeck3";
		break;
		
		case "Hold_GenQuest_OnShipDeck3":
			chrDisableReloadToLocation = false; // Откроем выход
			sld = characterFromId(pchar.GenQuest.Hold_GenQuest.CapId);
			ReleasePrisoner(sld);			
			CloseQuestHeader("HoldQuest");	
			DeleteAttribute(pchar, "TownEscape");
			DeleteAttribute(pchar, "GenQuest.Hold_GenQuest.canSpeakSailor");
			DeleteAttribute(pchar, "GenQuest.Hold_GenQuest");
			QuestOpenSeaExit();					
			DialogExit();
			AddDialogExitQuest("CanEnterToMap");
		break;
		
		case "Hold_GenQuest_OnShipDeck4":
			dialog.text = "Приветствую, капитан. За время вашего отсутствия на борту никаких происшествий не...";
			link.l1 = "Ладно-ладно, понятно... У нас в трюме пленник сидит, " + pchar.GenQuest.Hold_GenQuest.CapName + " зовут. Отряди команду доставить его в порт. Он свободен.";
			link.l1.go = "Hold_GenQuest_OnShipDeck5";
		break;
		
		case "Hold_GenQuest_OnShipDeck5":
			dialog.text = "Как, совсем что ли отпустить? На шлюпке что ли отправить?";
			link.l1 = "На черепахе... Я по-моему предельно ясно выразился. И пусть пошевеливаются! Нужно сняться с якорей к началу отлива.";
			link.l1.go = "Hold_GenQuest_OnShipDeck3";
		break;
		
		// Warship 09.07.09 Базар с нашим матросом на палубе Мэри Селест -->
		case "On_MaryCeleste_Deck":
			Dialog.text = "Капитан, на корабле нет ни единого человека! Здесь что-то нечисто... Томми говорит, в кубрике кошку видел, а больше ни одной живой души...";
			Link.l1 = "Болван, у кошки нет души. Видать давно в церкви не был... если вообще был когда-нибудь... В каюте капитана смотрели? Мне нужен судовой журнал.";
			Link.l1.go = "On_MaryCeleste_Deck_1";
		break;
		
		case "On_MaryCeleste_Deck_1":
			Dialog.text = "Всё осмотрели, ни журнала, ни навигационных приборов нет. Нет также кормовой шлюпки...";
			Link.l1 = "Шлюпка сорвана штормом?..";
			Link.l1.go = "On_MaryCeleste_Deck_2";
		break;
		
		case "On_MaryCeleste_Deck_2":
			Dialog.text = "Нет, капитан, шлюпку снимали талью... И это... мы дюсак нашли на полу в кубрике. То ли окровавленный, то ли ржавый. Вот взгляните...";
			Link.l1 = "Да что ты суёшь мне разную дрянь?! Осмотрите трюм и уходим... Ох, что-то не нравится мне всё это...";
			Link.l1.go = "On_MaryCeleste_Last";
			NextDiag.TempNode = "On_MaryCeleste_Deck_SailorLast";
		break;
		
		case "On_MaryCeleste_Last":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_SetCitizenType(NPChar); // Чтоб по палубе ходил
			
			NPChar = GetRealShip(GetCharacterShipType(CharacterFromID("MaryCelesteCapitan")));
			NPChar.TurnRate = sti(PChar.QuestTemp.MaryCeleste.TurnRate); // Вернем маневренность, для интерфейса
			
			chrDisableReloadToLocation = false; // Откроем выход
			
			LaunchTransferMain(PChar, CharacterFromID("MaryCelesteCapitan"), "MaryCelesteTransfer");
		break;
		
		case "On_MaryCeleste_Deck_SailorLast":
			switch(rand(2))
			{
				case 0:
					Dialog.text = "Капитан, жутковато здесь как-то... Может пора уже уходить?";
					Link.l1 = "Да... Садитесь в шлюпку.";
					Link.l1.go = "exit";
				break;
				
				case 1:
					Dialog.text = "Капитан, если Вы планируете вести это странное судно в порт, то я на нём не останусь. Уж лучше сразу за борт.";
					Link.l1 = "Ничего я не планирую... Само"+ GetSexPhrase("му","й") +" жутковато.";
					Link.l1.go = "exit";
				break;
				
				case 2:
					Dialog.text = "Может затопить его, а капитан?";
					Link.l1 = "Чтобы потом живущие здесь души пропавших моряков являлись нам в ночных кошмарах?..";
					Link.l1.go = "On_MaryCeleste_Deck_SailorLast_1";
				break;
			}
			
			NextDiag.TempNode = "On_MaryCeleste_Deck_SailorLast";
		break;
		
		case "On_MaryCeleste_Deck_SailorLast_1":
			Dialog.text = "Упаси Бог, капитан... что Вы такое говорите!..";
			Link.l1 = "Не бледней так, шучу я... Садитесь в шлюпку.";
			Link.l1.go = "exit";
		break;
		// <-- Базар с нашим матросом на палубе Мэри Селест
		
        //  на палубе <--
        case "On_Fort":
			dialog.text = RandPhraseSimple("Поговорите с начальником. Мне нечего вам сказать.", "Я на посту. Со всеми вопросами - к коменданту форта.");
			Link.l1 = "Хорошо.";
			Link.l1.go = "exit";

			NextDiag.TempNode = "On_Fort";
		break;
		
		case "On_Fort_Head":
			dialog.text = RandPhraseSimple("Я сейчас страшно занят. Оставьте меня в покое.",
                                           "Не мешайте мне работать. Нам не о чем говорить.");
			Link.l1 = "Жаль...";
			Link.l1.go = "exit";

			NextDiag.TempNode = "On_Fort_Head";
		break;
		
		case "Morgan_wait_you":
			Dialog.defAni = "dialog_stay1";
			Dialog.defCam = "1";
			Dialog.defSnd = "dialogs\0\017";
			Dialog.defLinkAni = "dialog_1";
			Dialog.defLinkCam = "1";
			Dialog.defLinkSnd = "dialogs\woman\024";
			Dialog.ani = "dialog_stay2";
			Dialog.cam = "1";
			Dialog.snd = "dialogs\0\009";

			dialog.text = RandPhraseSimple("Морган хотел тебе сказать 'пару ласковых'... Он где-то здесь, на палубе.",
                                           "Хех, найди Моргана. Тебя ждут неприятные новости...");
			Link.l1 = "Хорошо.";
			Link.l1.go = "exit";

			NextDiag.TempNode = "Morgan_wait_you";
		break;
	}
}
