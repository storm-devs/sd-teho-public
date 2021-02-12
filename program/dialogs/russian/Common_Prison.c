// городские тюрьмы
void ProcessDialogEvent()
{
	int amount, iGunQty, iGunGoods, iGunPrice, iTemp;
	int iTest;
	ref NPChar, sld, location;
	ref arItem;
	ref rColony;
	aref Link, NextDiag;
	string sTemp;
	float locx, locy, locz;
	bool  ok;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

    // вызов диалога по городам -->
    NPChar.FileDialog2 = "DIALOGS\" + LanguageGetLanguage() + "\Prison\" + NPChar.City + "_Prison.c";
    if (LoadSegment(NPChar.FileDialog2))
	{
        ProcessCommonDialog(NPChar, Link, NextDiag);
		UnloadSegment(NPChar.FileDialog2);
	}
    // вызов диалога по городам <--

	switch(Dialog.CurrentNode)
	{
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	
		case "fight":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_group_Attack(NPChar, Pchar);
			if (rand(3) != 1) SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;

		case "NoMoreTalkExit":
			LAi_CharacterDisableDialog(npchar);
			DialogExit();
		break;
		//---------------- Начальник тюрьмы ------------------
		case "First_officer":
			dialog.text = RandPhraseSimple("Я начальник тюрьмы. Что вам нужно здесь?", "Что вам нужно? Зачем вы явились в тюрьму?");
			link.l1 = "Да ничего особенного, осматриваю город, знаете ли. Вот и забрёл"+ GetSexPhrase("","а") +" сюда по случаю.";
			link.l1.go = "exit";
			link.l2 = "Хочу поговорить по делу.";
			if (CheckCharacterItem(pchar, "CaptainBook") && !CheckAttribute(pchar, "questTemp.different.GiveShipLetters.speakFort"))
			{
				if((pchar.questTemp.different.GiveShipLetters.city == npchar.city) && CheckAttribute(pchar, "questTemp.different.GiveShipLetters"))
				{
					link.l2.go = "F_ShipLetters_1";
				}
				else
				{
					link.l2.go = "quests";
				}		
			}
			else
			{
				if(CheckAttribute(pchar,"questTemp.ReasonToFast") && !CheckAttribute(pchar,"questTemp.ReasonToFast.SpeakOther") && !CheckAttribute(pchar, "questTemp.ReasonToFast.cantSpeakOther") && (pchar.questTemp.ReasonToFast.city == NPChar.city))
				{
					link.l2.go = "ReasonToFast_Prison1";
				}
				else
				{
					link.l2.go = "quests";
				}	
			}
			if (!sti(pchar.questTemp.jailCanMove))
			{
				link.l4 = "Я хочу пройти внутрь тюрьмы.";
				link.l4.go = "ForGoodMove";		
			}
			if (CheckAttribute(pchar, "questTemp.jailCanMove.City") && npchar.city == pchar.questTemp.jailCanMove.City)
			{
				link.l5 = "Послушайте, не подскажете мне, за какое преступление сидит здесь заключённый по имени " + GetFullName(characterFromId(pchar.questTemp.jailCanMove.prisonerId)) + "?";
				link.l5.go = "KnowAboutPrisoner";	
			}
			
			if(CheckAttribute(pchar,"GenQuest.CaptainComission") && (pchar.GenQuest.CaptainComission.variant == "A2") && (pchar.GenQuest.CaptainComission.City == NPChar.city))
			{
				if(!CheckAttribute(pchar,"GenQuest.CaptainComission.PrisonFree"))
				{
					bool zMsm = (CheckAttribute(pchar,"GenQuest.CaptainComission.GetRumour")) && (!CheckAttribute(pchar,"GenQuest.CaptainComission.SpeakMayor"));
					if(pchar.GenQuest.CaptainComission == "MayorTalkBad" || zMsm) //говорил с губером и отказался или узнал слухи, но не говорил с губером
					{
						link.l6 = "До меня дошли слухи, что бывший капитан патрульного " + GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name") + "Gen")) + " " + pchar.GenQuest.CaptainComission.Name + " содержится у вас под стражей. Могу я с ним переговорить?";
						link.l6.go = "CapComission_PrisonBad1";
					}
					if(pchar.GenQuest.CaptainComission == "MayorTalkGood")
					{
						link.l6 = "Я " + GetFullName(pchar) + ", действую от имени и по поручению губернатора " + XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Gen") + ". Мне нужно переговорить с бывшим капитаном по имени " + pchar.GenQuest.CaptainComission.Name + ".";
						link.l6.go = "CapComission_PrisonGood1";
					}
				}	
			}
			if(CheckAttribute(pchar,"GenQuest.EncGirl"))
			{
				if(pchar.GenQuest.EncGirl == "toParents" || pchar.GenQuest.EncGirl == "FindLover")
				{
					if(pchar.GenQuest.EncGirl.Father == "fort_keeper"  && npchar.city == pchar.GenQuest.EncGirl.city)
					{
						link.l9 = "Я по поводу вашей дочери...";
						link.l9.go = "EncGirl_1";
					}
				}
			}
			//Jason --> Бесчестный конкурент
			if (CheckAttribute(pchar, "questTemp.Shadowtrader.Fort") && NPChar.location == pchar.questTemp.Shadowtrader.City + "_prison")
			{
				link.l10 = "Я пришёл к вам по просьбе хозяина местного магазина, его зовут "+pchar.questTemp.Shadowtrader.Tradername+". Он просил передать вам вот это письмо.";
				link.l10.go = "Shadowtrader_prison";
			}
			
			if (CheckAttribute(pchar, "questTemp.Shadowtrader.SeekTrader") && NPChar.location == pchar.questTemp.Shadowtrader.City + "_prison")
			{
				link.l10 = "Это опять я. У меня есть веские доказательства того, что "+pchar.questTemp.Shadowtrader.Tradername+" прав.";
				link.l10.go = "Shadowtrader_prison2";
			}
			//Jason <-- Бесчестный конкурент
			
			if (CheckAttribute(pchar, "GenQuest.Marginpassenger") && pchar.GenQuest.Marginpassenger == "begin" && NPChar.location == pchar.GenQuest.Marginpassenger.City + "_prison")
			{
				link.l12 = "У меня к вам дело, офицер. Думаю, вас это заинтересует по долгу службы.";
				link.l12.go = "Marginpassenger";
			}
			
			// Warship, 16.05.11. Генер "Правосудие на продажу".
			if(CheckAttribute(PChar, "GenQuest.JusticeOnSale.PrisonWait") && CheckAttribute(PChar, "GenQuest.JusticeOnSale.CityId") && NPChar.location == PChar.GenQuest.JusticeOnSale.CityId + "_prison")
			{
				link.l13 = "Хотел поговорить с вами об одном человеке - " + PChar.GenQuest.JusticeOnSale.SmugglerName + ". Если не ошибаюсь – он ваш заключённый.";
				link.l13.go = "JusticeOnSale_1";
			}
			
			NextDiag.TempNode = "First_officer";
		break;

		//Jason --> мини-квест Бесчестный конкурент
		case "Shadowtrader_prison":
			dialog.text = "Опять этот "+pchar.questTemp.Shadowtrader.Tradername+" со своими жалобами! Давайте прочтём, что он на этот раз пишет... (читает)";
			link.l1 = "...";
			link.l1.go = "Shadowtrader_prison_1";
			RemoveItems(PChar, "letter_1", 1);
			DeleteAttribute(pchar, "questTemp.Shadowtrader.Fort");
		break;
		
		case "Shadowtrader_prison_1":
			dialog.text = "Опять эти абсурдные домыслы и ни одного чёткого доказательства! Так. Передайте ему, что этого недостаточно для того, чтобы я поднял стражу на уши и заставил прочёсывать город.";
			link.l1 = "Так и передать?";
			link.l1.go = "Shadowtrader_prison_2";
		break;
		
		case "Shadowtrader_prison_2":
			dialog.text = "Да, именно так, и желательно дословно. Он поймёт, о чём речь. Марать бумагу ради ответа на этот пасквиль я не буду.";
			link.l1 = "Я понял. Всего доброго.";
			link.l1.go = "exit";
			pchar.questTemp.Shadowtrader.Trouble = "true";
			NextDiag.TempNode = "First_officer";
		break;
		
		case "Shadowtrader_prison2":
			dialog.text = "Интересно, и какие же это такие 'веские' доказательства вам удалось добыть?";
			link.l1 = "Я договорился с контрабандистами о закупке товаров через их неофициальный магазин. Их агент придёт сегодня ночью к портовому управлению, для того, чтобы провести меня в свою так называемую 'лавку'.";
			link.l1.go = "Shadowtrader_prison2_1";
			DeleteAttribute(pchar, "questTemp.Shadowtrader.SeekTrader");
			pchar.quest.ShadowtraderTimeSmugglers_Over.over = "yes";
			pchar.quest.Shadowtrader_SMG.over = "yes";//снять оба прерывания
			sld = characterFromID("ShadowAgent_1");
			sld.lifeday = 0;
		break;
		
		case "Shadowtrader_prison2_1":
			dialog.text = "Кхм... Отличная работа, капитан! Дальше действовать будем мы - пошлём на встречу своего человека, найдём их убежище и всех арестуем. Благодарю за проявленную инициативу!";
			link.l1 = "Всегда рад помочь. Уверен, ваша операция пройдёт успешно.";
			link.l1.go = "exit";
			pchar.questTemp.Shadowtrader.End.Fort = "true";
			AddQuestRecord("Shadowtrader", "7");
			SaveCurrentQuestDateParam("pchar.questTemp.Shadowtrader.EndFort");
			AddCharacterExpToSkill(pchar, "Leadership", 50);//авторитет
			AddCharacterExpToSkill(pchar, "Fortune", 100);//везение
			AddCharacterExpToSkill(pchar, "Sneak", 100);//скрытность
			NextDiag.TempNode = "First_officer";
		break;
		// <-- мини-квест Бесчестный конкурент
		
		// --> Jason Похититель
		case "Marginpassenger":
			dialog.text = "Да? И что же такое вы хотите мне поведать?";
			link.l1 = "Ко мне на улице недавно подошёл некий "+pchar.GenQuest.Marginpassenger.Name+" и предложил провернуть чёрное дельце: захватить в плен и в дальнейшем сдать за выкуп человека по имени "+pchar.GenQuest.Marginpassenger.q1Name+". Это "+pchar.GenQuest.Marginpassenger.Text+"...";
			link.l1.go = "Marginpassenger_1";
		break;
		
		case "Marginpassenger_1":
			dialog.text = "Хм... Очень интересно. продолжайте!";
			link.l1 = "Ему было известно название судна, на котором "+pchar.GenQuest.Marginpassenger.q1Name+" планирует отправиться в путь. Это "+GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.Marginpassenger.ShipType), "Name")))+" под названием '"+pchar.GenQuest.Marginpassenger.ShipName+"'. Также он указал и время выхода судна в плавание.";
			link.l1.go = "Marginpassenger_2";
		break;
	
		case "Marginpassenger_2":
			dialog.text = "И он предложил вам захватить пассажира, а потом потребовать выкуп?";
			link.l1 = "Именно так. За выкупом нужно обратиться в "+XI_ConvertString("Colony"+pchar.GenQuest.Marginpassenger.Targetcity)+", к некому человеку по имени "+pchar.GenQuest.Marginpassenger.q2Name+". Я заплатил ему за эту информацию, но, конечно, даже и не собирался осуществлять похищение.";
			link.l1.go = "Marginpassenger_3";
		break;
		
		case "Marginpassenger_3":
			dialog.text = "И вы решили явиться ко мне и доложить обо всём, так?";
			link.l1 = "Именно так. Я считаю, что действия негодяя угрожают безопасности жителей вашего города, и вы примете в отношении него адекватные меры.";
			link.l1.go = "Marginpassenger_4";
		break;
		
		case "Marginpassenger_4":
			dialog.text = "Вы очень правильно сделали, что пришли ко мне, "+GetAddress_Form(NPChar)+"! Этот негодяй, "+pchar.GenQuest.Marginpassenger.Name+", уже давно у нас под наблюдением. Я проведу расследование, и если всё, что вы сказали, подтвердится, мы упечём мерзавца за решётку на полгодика. Это отучит его строить всевозможные козни уважаемым гражданам\nНу, а о вашей честности и готовности служить правому делу я, безусловно, доложу нашему губернатору, что, конечно, отразится на его отношении к вам... как вы понимаете, в положительную сторону. Благодарю за помощь, капитан!";
			link.l1 = "Хм... Да, собственно, не за что... Рад был помочь. До свидания!";
			link.l1.go = "Marginpassenger_5";
		break;
		
		case "Marginpassenger_5":
			DialogExit();
			NextDiag.CurrentNode = "First_officer";
			AddQuestRecord("Marginpassenger", "20");
			AddQuestUserData("Marginpassenger", "sName", pchar.GenQuest.Marginpassenger.Name);
			CloseQuestHeader("Marginpassenger");
			pchar.quest.Marginpassenger_InWorld.over = "yes"; //снять таймер
			DeleteAttribute(Pchar, "GenQuest.Marginpassenger");
			ChangeCharacterComplexReputation(pchar, "nobility", 3);
			ChangeCharacterNationReputation(pchar, sti(npchar.Nation), 5);
			AddCharacterExpToSkill(pchar, "Leadership", 100);//авторитет
			ChangeContrabandRelation(pchar, -25);
			if (GetCharacterIndex("MarginCap") != -1)
			{
				sld = characterFromId("MarginCap");
				sld.lifeday = 0;
				Map_ReleaseQuestEncounter(sld.id);
				Group_DeleteGroup("Sea_MarginCap1");
			}
		break;
		//<-- Похититель

		case "EncGirl_1":
			dialog.text = "Слушаю вас внимательно.";
			link.l1 = "Я привел"+ GetSexPhrase("","а") +" вашу беглянку.";
			link.l1.go = "EncGirl_2";
		break;
		
		case "EncGirl_2":
			dialog.text = "Ах, капитан, спасибо вам большое! Как она? здорова, не пострадала? Уж скоро сутки, как убежала, негодница. Разве ж я ей плохого желаю? Замуж отдать собрался... Жених богатый, молодой, а что собою не пригож, так ведь с лица воду не пить. Нет! она всё по-своему норовит - вся в мать, чтоб её...\nХотя, и она бы на свет не появилась, если бы её мамаша в своё время не сбежала с одним предприимчивым оболтусом... ну да что вспоминать... Молодость наивна, глупа... и жестока.";
			link.l1 = "Конечно, вы отец и решать вам, но я бы не торопил"+ GetSexPhrase("ся","ась") +" со свадьбой...";
			link.l1.go = "EncGirl_3";
		break;
		
		case "EncGirl_3":
			dialog.text = "Да что вы понимаете?.. У вас свои дети есть? Нету? Вот, когда будут - заходите, тогда и поговорим\nДа... я обещал вознаграждение тому, кто её вернёт, - примите, пожалуйста.";
			link.l1 = "Спасибо. И держите её покрепче. Что-то мне подсказывает, что она на этом не остановится.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("EncGirl_ToLoverParentsExit");
		break;
		
		// ------------------------- Повод для спешки -----------------------------
		case "ReasonToFast_Prison1":
			pchar.questTemp.ReasonToFast.SpeakOther = true;
			dialog.text = "Я внимательно слушаю Вас, капитан.";
			link.l1 = "Я хочу доложить о преступном сговоре офицера Вашего гарнизона и пиратов (излагает обстоятельства дела).";
			if(makeint(pchar.reputation.nobility) < 41)
			{
				link.l1.go = "ReasonToFast_Prison_BadRep";			
			}
			else
			{
				link.l1.go = "ReasonToFast_Prison_GoodRep";	
			}
		break;
		case "ReasonToFast_Prison_GoodRep":
			if(pchar.questTemp.ReasonToFast == "PatrolSuccess_1") 
			{ 
				// вилка_А
				dialog.text = "Благодарю вас, судар"+ GetSexPhrase("ь","ыня") +"! Я немедленно отдам приказ задержать негодяя.\nОднако вы изрядно потратились, а муниципальная казна, увы, пуста...";
				link.l1 = "Ваша светлость! Я делал"+ GetSexPhrase("","а") +" это не ради денег...";
				link.l1.go = "ReasonToFast_Prison_GoodRep_11";
				
				if(pchar.questTemp.ReasonToFast.chain == "A0") ReasonToFast_RemoveVictim();
				if(pchar.questTemp.ReasonToFast.chain == "A1") pchar.quest.ReasonToFast_ClearLakey.over = "yes";
			}
			if(pchar.questTemp.ReasonToFast == "PatrolSuccess_2") 
			{ 
				// получена карта
				dialog.text = "Благодарю вас, судар"+ GetSexPhrase("ь","ыня") +"! Я немедленно отдам приказ задержать негодяя.\nТолько подумайте! Мы хотели наградить его именным оружием за безупречную службу. Как хорошо, что всё прояснилось, и не вышло такого конфуза!";
				link.l1 = "Всегда рад"+ GetSexPhrase("","а") +" послужить справедливости...";
				link.l1.go = "ReasonToFast_Prison_GoodRep_21";			
			}
			if(pchar.questTemp.ReasonToFast == "PatrolDied") 
			{ 
				// патруль перебит
				dialog.text = "Судар"+ GetSexPhrase("ь","ыня") +"! Мы давно подозревали, что этот офицер и окружавший его сброд нечисты на руку, но мне кажется, что Вы поступили опрометчиво, разделавшись с ними без свидетелей.";
				link.l1 = "Ваша светлость! Но я вынужден"+ GetSexPhrase("","а") +" был"+ GetSexPhrase("","а") +" защищать свою жизнь...";
				link.l1.go = "ReasonToFast_Prison_GoodRep_31";	
				pchar.questTemp.ReasonToFast.speakAfterPatrolDied = true;	
				pchar.quest.ReasonToFast_SpeakMayor.over = "yes";	
			}
		break;
		
		case "ReasonToFast_Prison_BadRep":
			if(pchar.questTemp.ReasonToFast == "PatrolSuccess_1") 
			{ 
				// вилка_А
				dialog.text = "Капитан, Вы хоть понимаете, во что вляпались?!! Мы больше месяца пытались организовать эту ловушку! А Вы ради развлечения сорвали встречу нашего патруля с посыльным " + GetName( NAMETYPE_MAIN, pchar.questTemp.ReasonToFast.p3, NAME_GEN) + " и ещё пришли ко мне этим похвастаться! Может, Вы теперь расскажете, каким образом я должен обосновать казённые затраты для организации этой операции?!!";
				link.l1 = "Ваша Честь! Вы отказываетесь видеть суть происходящего...";
				link.l1.go = "ReasonToFast_Prison_BadRep1";
				pchar.questTemp.ReasonToFast = "speakSuccess_chain_A";
				
				if(pchar.questTemp.ReasonToFast.chain == "A0") ReasonToFast_RemoveVictim();
				if(pchar.questTemp.ReasonToFast.chain == "A1") pchar.quest.ReasonToFast_ClearLakey.over = "yes";
			}
			if(pchar.questTemp.ReasonToFast == "PatrolSuccess_2") 
			{ 
				// получена карта
				dialog.text = "Дайте-ка взглянуть на эту карту...\nВы надо мной издеваетесь? Этот затёртый клочок пергамента - доказательство?";
				link.l1 = "Ваша Честь! Вы отказываетесь видеть суть происходящего...";
				link.l1.go = "ReasonToFast_Prison_BadRep1";
				TakeItemFromCharacter(pchar, "mapQuest");	
				pchar.questTemp.ReasonToFast = "speakSuccess_chain_B";	
			}
			if(pchar.questTemp.ReasonToFast == "PatrolDied") 
			{ 
				// патруль перебит
				dialog.text = "Оригинальное оправдание гибели целого патрульного отряда. Ну что ж, по крайней мере, придя сюда, Вы избавили нас от необходимости искать убийцу";
				link.l1 = "Ваша Светлость! Вы отказываетесь видеть суть происходящего...";
				link.l1.go = "ReasonToFast_Prison_BadRep1";			
				pchar.questTemp.ReasonToFast = "speakSuccess_chain_A";
				pchar.quest.ReasonToFast_SpeakMayor.over = "yes";
			}		
		break;
		
		case "ReasonToFast_Prison_GoodRep_11":
			dialog.text = "Тем не менее, я хочу, чтобы Ваши труды были вознаграждены. Вот, возьмите карту, найденную в вещах недавно вздёрнутого морского разбойника. Возможно, при содействии Господа, Вы действительно обнаружите сокровища, хотя это весьма сомнительно...";
			link.l1 = "Спасибо, Вы очень щедры!";
			link.l1.go = "exit";
			AddQuestRecord("ReasonToFast", "15");
			ChangeCharacterComplexReputation(pchar,"nobility", 1); 
			GiveItem2Character(pchar, "mapQuest"); 
			arItem = ItemsFromID("mapQuest");
			ReasonToFast_GenerateTreasureMap(arItem);
			pchar.questTemp.ReasonToFast.state = "chain_A"; // вилка_А, наводки не генерим
			pchar.questTemp.ReasonToFast = "GetMap";			
			ReasonToFast_SetHunterCoastal();
		break;
		case "ReasonToFast_Prison_GoodRep_21":
			dialog.text = "Похвальное рвение. Возьмите этот клинок в награду, - это меньшее, чем я могу вас одарить! Да.. и оставьте эту карту себе. Уверен, - по Архипелагу ходит множество подобных фальшивок.";
			link.l1 = "Спасибо, Вы очень щедры!";
			link.l1.go = "exit";
			AddQuestRecord("ReasonToFast", "14");
			ChangeCharacterComplexReputation(pchar,"nobility", 1); 
			GiveItem2Character(pchar, pchar.questTemp.ReasonToFast.p6);
			pchar.questTemp.ReasonToFast.state = "chain_B"; // была получена карта
			pchar.questTemp.ReasonToFast = "GetMap";			
			ReasonToFast_SetHunterCoastal();
		break;
		case "ReasonToFast_Prison_GoodRep_31":
			dialog.text = "Да, возможно, возможно... Что же, я готов считать, что дело разрешилось Божьим судом и по воле Его.";
			link.l1 = "Спасибо, Вы очень щедры!";
			link.l1.go = "exit";
			ChangeCharacterComplexReputation(pchar,"nobility", 1); 
			AddQuestRecord("ReasonToFast", "16");
			CloseQuestHeader("ReasonToFast");
			DeleteAttribute(pchar,"ReasonToFast");			
		break;
		
		case "ReasonToFast_Prison_BadRep1":
			dialog.text = "Не смейте меня поучать! Для меня очевиден ваш сговор с мошенниками! Караул, взять "+ GetSexPhrase("этого 'доброжелателя'","эту 'доброжелательницу'") +"!";
			link.l1 = "Ну уж нет!";
			link.l1.go = "fight";
			
			pchar.quest.ReasonToFast_ExitFromTown.win_condition.l1			= "EnterToSea";           	
            pchar.quest.ReasonToFast_ExitFromTown.function    				= "ReasonToFast_ExitFromTownFight";
			pchar.questTemp.ReasonToFast.canSpeakSailor = true;			
			pchar.TownEscape = true;
			Flag_PIRATE();
		break;
		// ------------------------- Повод для спешки -----------------------------
		
		// -------------------------- Операция 'Галеон' ----------------------------
		case "CapComission_PrisonBad1":
			dialog.text = "А по какому делу он вам понадобился?";
			link.l1 = "У меня к нему несколько вопросов личного характера.";
			link.l1.go = "CapComission_PrisonBad2";
		break;
		
		case "CapComission_PrisonBad2":
			dialog.text = "Капитан, у меня есть чёткое предписание брать под стражу и направлять в резиденцию для дознания любого, кто будет интересоваться этой персоной.";
			link.l1 = "Неплохо вы устроились! Заключённые уже сами приходят к вам для ареста!";
			link.l1.go = "CapComission_PrisonBad3";
		break;
		
		case "CapComission_PrisonBad3":
			dialog.text = "И тем не менее, прошу сдать оружие.";
			link.l1 = "Ну уж нет! Вам придётся отбирать его силой.";
			link.l1.go = "fight";
			CaptainComission_GenerateCaptainInPrison(); // данила . на всякий случай ,чтобы сгенерился нормально.
			AddDialogExitQuest("CaptainComission_GenerateCapJail");
		break;
		
		case "CapComission_PrisonGood1":
			dialog.text = "Да, конечно. Я получил предписание губернатора оказывать вам содействие в этом вопросе. Можете пройти к заключённому.";
			link.l1 = "Благодарю вас...";
			link.l1.go = "exit";
			pchar.questTemp.jailCanMove = true;
			AddDialogExitQuest("CaptainComission_GenerateCapJail");
		break;
		
		case "CapComission_PrisonFree1":
		if(CheckAttribute(pchar,"GenQuest.CaptainComission"))// лесник . разделение диалога если кеп убит или нет
		{
			dialog.text = "Э-э, капитан, у меня нет указаний выпускать этого заключённого из-под стражи. Вам нужно испросить на это разрешение губернатора.";
			link.l1 = "Офицер, я действую в интересах дознания. Заключённый согласился сотрудничать с властями и готов указать место тайника. Любое промедление грозит тем, что ценный груз будет найден контрабандистами и утерян для поселения.";
			link.l1.go = "CapComission_PrisonFree2";
		}
         else
		 {
         	dialog.text = "Зря вы его убили, капитан.. Хотя мне это не важно. Теперь вместо него казнить будем вас. Стража! Взять его!";
            link.l2 = "Не на того напали!...";
             link.l2.go = "fight";
			 NextDiag.TempNode = "First_officer";
			NextDiag.CurrentNode = NextDiag.TempNode; 
			AddDialogExitQuest("OpenTheDoors");
		 }			 
		break;
		
		case "CapComission_PrisonFree2":
			dialog.text = "Но я мог бы выделить эскорт для его сопровождения.";
			link.l1 = "Этого не понадобится, у меня достаточно охраны. Кроме того, я опасаюсь огласки местоположения тайника.";
			link.l1.go = "CapComission_PrisonFree3";
		break;
		
		case "CapComission_PrisonFree3":
			dialog.text = "М-м... ну хорошо. Только учтите, что отвечаете за него головой.";
			link.l1 = "Безусловно...";
			link.l1.go = "exit";
			NextDiag.TempNode = "First_officer";
			NextDiag.CurrentNode = NextDiag.TempNode; 
			AddDialogExitQuest("OpenTheDoors");
		break;
		// -------------------------- Операция 'Галеон' ----------------------------
		
		case "F_ShipLetters_1":
			dialog.text = "Говорите, я слушаю.";
			link.l1 = "У меня есть судовые документы. Думаю, владелец их по рассеянности позабыл, а вам они будут интересны.....";
			link.l1.go = "F_ShipLetters_2";
			pchar.questTemp.different.GiveShipLetters.speakFort = true;
		break;
		
		case "F_ShipLetters_2":			
			if(sti(pchar.questTemp.different.GiveShipLetters.variant) == 0)
			{
				dialog.text = "Вздор! Не мешайте работать, идите лучше в портовое управление.";
				link.l1 = "Спасибо и на этом....";
				link.l1.go = "exit";
			}
			else
			{
				if(!CheckAttribute(pchar, "questTemp.different.GiveShipLetters.speakUsurer_1"))
				{
					dialog.text = "Да, владелец из местных. Пожалуй, премия в " + sti(pchar.questTemp.different.GiveShipLetters.price2) + " песо послужит достойной наградой за Вашу бдительность, капитан.";
					link.l1 = "Пожалуй, нет.";
					link.l1.go = "F_ShipLetters_3";	
					link.l2 = "Щедрое предложение! Бумаги отныне ваши....";
					link.l2.go = "F_ShipLetters_4";
				}
				else
				{
					if(sti(pchar.questTemp.different.GiveShipLetters.variant) == 1)
					{
						dialog.text = "Ух, аж дух захватывает, насколько интересны! Думаю, городская казна благодарно выплатит Вам "+ sti(pchar.questTemp.different.GiveShipLetters.price4) +" песо, за содействие в борьбе с незаконным товарооборотом.";
						link.l1 = "Пожалуй, нет.";
						link.l1.go = "F_ShipLetters_3";
						link.l2 = "Щедрое предложение! Бумаги отныне ваши....";
						link.l2.go = "F_ShipLetters_4";
					}
					if(sti(pchar.questTemp.different.GiveShipLetters.variant) == 2)
					{
						dialog.text = "Боже! Какая удача, что Вы пришли ко мне. Я думаю, мой незадачливый коллега согласится заплатить " + sti(pchar.questTemp.different.GiveShipLetters.price3) + " песо, чтобы дело избежало огласки.";
						link.l1 = "Пожалуй, нет.";
						link.l1.go = "F_ShipLetters_3";
						link.l2 = "Щедрое предложение! Бумаги отныне ваши....";
						link.l2.go = "F_ShipLetters_4";
					}
				}
			}
		break;
		
		case "F_ShipLetters_3":
			dialog.text = "Хех! Это мой город, капитан.";
			link.l1 = "Я это запомню.";
			link.l1.go = "exit";
		break;
		
		case "F_ShipLetters_4":
			TakeItemFromCharacter(pchar, "CaptainBook"); 
			if(sti(pchar.questTemp.different.GiveShipLetters.variant) == 1)
			{
				if(!CheckAttribute(pchar, "questTemp.different.GiveShipLetters.speakUsurer_1"))
				{
					addMoneyToCharacter(pchar, sti(pchar.questTemp.different.GiveShipLetters.price2)); 
				}
				else
				{
					addMoneyToCharacter(pchar, sti(pchar.questTemp.different.GiveShipLetters.price4)); 
				}
			}
			if(sti(pchar.questTemp.different.GiveShipLetters.variant) == 2)
			{
				if(!CheckAttribute(pchar, "questTemp.different.GiveShipLetters.speakUsurer_1"))
				{
					addMoneyToCharacter(pchar, sti(pchar.questTemp.different.GiveShipLetters.price2)); 
				}
				else
				{
					addMoneyToCharacter(pchar, sti(pchar.questTemp.different.GiveShipLetters.price3)); 
				}
			}
						
			if((sti(pchar.questTemp.different.GiveShipLetters.variant) == 0) || (sti(pchar.questTemp.different.GiveShipLetters.variant) == 2))
			{	
				ChangeCharacterComplexReputation(pchar,"nobility", -1); 
				OfficersReaction("bad"); 
			}	
			pchar.questTemp.different = "free";
			pchar.quest.GiveShipLetters_null.over = "yes"; //снимаем таймер 
			AddQuestRecord("GiveShipLetters", "8");			
			CloseQuestHeader("GiveShipLetters");
			DeleteAttribute(pchar, "questTemp.different.GiveShipLetters");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		
        case "ForGoodMove":
			dialog.text = NPCStringReactionRepeat("Но зачем вам это? Поверьте мне, там нет ничего достойного внимания, одни воры и бандиты.", "Мы уже обсуждали это ваше желание.", 
				"Опять о том же? Уже дважды мы с вами говорили об этом!", "Гм, опять...", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Тем не менее, я хотел"+ GetSexPhrase("","а") +" бы провести экскурс по вашим казематам. Мне очень интересно!", "Да, именно так. Но я хотел"+ GetSexPhrase("","а") +" ещё поговорить на эту тему.", 
				"Ну, может в третий раз...", "Надежда посмотреть на ваших узников не покидает меня...", npchar, Dialog.CurrentNode);
			link.l1.go = "ForGoodMove_1";
		break;
		
        case "ForGoodMove_1":
			pchar.questTemp.jailCanMove.money = 20+drand(3)*10;
			if (sti(colonies[FindColony(npchar.city)].jail) && GetCharacterItem(pchar, "gold_dublon") >= sti(pchar.questTemp.jailCanMove.money))
			{
				dialog.text = "Ну что же, не вижу причины вам отказывать. " + FindRussianDublonString(sti(pchar.questTemp.jailCanMove.money)) + " - и пока вы не покинете тюрьму, вы можете беспрепятственно ходить по коридорам и даже разговаривать с заключёнными.";
				link.l1 = "Я соглас"+ GetSexPhrase("ен","на") +", вот ваши монеты!";
				link.l1.go = "ForGoodMove_agree";
				link.l2 = "Не пойдёт, слишком дорого для бесцельного хождения по коридорам.";
				link.l2.go = "exit";
			}
			else
			{
				dialog.text = RandPhraseSimple("Нет, это категорически запрещено уставом. Вам здесь что, цирк? Уходите, и не отвлекайте меня от несения службы.", "Я не могу позволить расхаживать по тюрьме посторонним людям. Прошу вас, не мешайте мне!");
				link.l1 = "Хорошо, как скажете...";
				link.l1.go = "exit";
			}
		break;
		
        case "ForGoodMove_agree":
            dialog.text = "Ну что же, вы можете приступать к своему, так сказать, экскурсу...";
			link.l1 = "Спасибо, офицер.";
			link.l1.go = "exit";
			pchar.questTemp.jailCanMove = true;
			RemoveItems(pchar, "gold_dublon", sti(pchar.questTemp.jailCanMove.money));
			Log_Info("Вы отдали " + FindRussianDublonString(sti(pchar.questTemp.jailCanMove.money)) + "");
		break;
		
        case "KnowAboutPrisoner":
			switch (pchar.questTemp.jailCanMove.ownerPrison)
			{
				case "0": sTemp = "За убийство."; break;
				case "1": sTemp = "Он обвиняется в пиратстве."; break;
				case "2": sTemp = "За бандитизм и разбойное нападение."; break;
				case "3": sTemp = "Он попался на воровстве."; break;
				case "4": sTemp = "За мелкую кражу."; break;
				case "5": sTemp = "За шулерство."; break;
				case "6": sTemp = "За бродяжничество и попрошайничество."; break;
			}
			dialog.text = sTemp;
			link.l1 = "Понятно... А есть шанс внести за него выкуп, залог, или ещё как-нибудь содействовать его вызволению?";
			link.l1.go = "KnowAboutPrisoner_" + pchar.questTemp.jailCanMove.ownerPrison;
			DeleteAttribute(pchar, "questTemp.jailCanMove.City");
		break;
		
        case "KnowAboutPrisoner_0":
			dialog.text = "Нет, конечно. Этому висельнику прямая дорога в ад. Он на особом контроле у губернатора!";
			link.l1 = "Хех, понятно...";
			link.l1.go = "notFree_exit";
		break;	
		
		case "KnowAboutPrisoner_1":
			dialog.text = "Вы шутите? Его место - на виселице! Конопляная тётушка уже давно плачет по нему. Забудьте об этом.";
			link.l1 = "Понял. Уже забыл...";
			link.l1.go = "notFree_exit";
		break;
		
        case "KnowAboutPrisoner_2":
			dialog.text = "Не думаю. Много он крови попортил жителям нашего города. Так что даже и не просите.";
			link.l1 = "Хм, ясно.";
			link.l1.go = "notFree_exit";
		break;
		
        case "KnowAboutPrisoner_3":
			dialog.text = "Нет, пожалуй. Он вор, а вор должен сидеть в тюрьме!";
			link.l1 = "О как! Хорошо сказано, лейтенант...";
			link.l1.go = "notFree_exit";
		break;
		
        case "KnowAboutPrisoner_4":
			dialog.text = "Не знаю даже. Этот паршивец украл сущую мелочь. И отпустить его не могу, но и гноить здесь за такую ерунду - тоже не дело...";
			link.l1 = "Так отдайте его мне, лейтенант. Я заплачу, в разумных пределах, естественно.";
			link.l1.go = "KnowAboutPrisoner_free";
		break;
		
        case "KnowAboutPrisoner_5":
			dialog.text = "Вызволению? Вполне возможно. С моей точки зрения, содержать этого мелкого жулика здесь не имеет никакого смысла.";
			link.l1 = "Так отдайте его мне, лейтенант. Я заплачу, в разумных пределах, естественно.";
			link.l1.go = "KnowAboutPrisoner_free";
		break;
		
		case "KnowAboutPrisoner_6":
			dialog.text = "Хм. В ваших словах есть резон. От этого бродяжки только вонь и блохи по всей тюрьме...";
			link.l1 = "Так отдайте его мне, лейтенант. Я заплачу, в разумных пределах, естественно.";
			link.l1.go = "KnowAboutPrisoner_free";
		break;
		
        case "KnowAboutPrisoner_free":
			pchar.questTemp.jailCanMove.ownerPrison.money = 50+drand(10)*10;
			dialog.text = "Хорошо, договорились. " + FindRussianDublonString(sti(pchar.questTemp.jailCanMove.ownerPrison.money)) + " на бочку, и забирайте его хоть прямо сейчас.";
			if (GetCharacterItem(pchar, "gold_dublon") >= sti(pchar.questTemp.jailCanMove.ownerPrison.money))
			{
				link.l1 = LinkRandPhrase("Вот это здорово! Я согласен!","По рукам, офицер!","Отлично. Я готов уплатить взнос.");
				link.l1.go = "KnowAboutPrisoner_agree";
			}
			link.l2 = "Нет, дороговато будет. Откажусь.";
			link.l2.go = "KnowAboutPrisoner_exit";
		break;
		
        case "KnowAboutPrisoner_agree":
			dialog.text = "Всё, вы можете пройти к его камере и забирать этого оборванца.";
			link.l1 = "Спасибо.";
			link.l1.go = "exit";
			pchar.questTemp.jailCanMove = true;
			RemoveItems(pchar, "gold_dublon", sti(pchar.questTemp.jailCanMove.ownerPrison.money));
			Log_Info("Вы отдали " + FindRussianDublonString(sti(pchar.questTemp.jailCanMove.ownerPrison.money)) + "");
			DeleteAttribute(pchar, "questTemp.jailCanMove.ownerPrison");
			sld = characterFromId(pchar.questTemp.jailCanMove.prisonerId)
			LAi_CharacterEnableDialog(sld);
			sld.dialog.currentnode = "ToPrisonHead_canMove";
		break;
		
        case "KnowAboutPrisoner_exit":
			dialog.text = "Ну, смотрите, другого шанса я не дам...";
			link.l1 = "И не надо. Я принял"+ GetSexPhrase("","а") +" решение.";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.jailCanMove.ownerPrison");
			sld = characterFromId(pchar.questTemp.jailCanMove.prisonerId);
			LAi_CharacterEnableDialog(sld);
			sld.dialog.currentnode = "ToPrisonHead_expansive";
		break;
		
        case "notFree_exit":
			sld = characterFromId(pchar.questTemp.jailCanMove.prisonerId);
			LAi_CharacterEnableDialog(sld);
			sld.dialog.currentnode = "ToPrisonHead_notFree";
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		//---------------- Протектор ------------------
        case "First_protector":
			if (sti(pchar.questTemp.jailCanMove))
			{
				dialog.text = RandPhraseSimple("Вы можете пройти, начальник разрешил...", "Получен приказ начальника тюрьмы. Вы можете свободно проходить.");
				link.l1 = "Ну, вот и чудно.";
				link.l1.go = "exit";
				DeleteAttribute(pchar, "questTemp.jailCanMove.ownerPrison.money");
			}
			else
			{
				dialog.text = RandPhraseSimple("Проходить далее без разрешения начальника тюрьмы категорически запрещено!", "Я подчиняюсь только начальнику тюрьмы. Если ты попытаешься пройти дальше без его разрешения - тебе конец!");
				link.l1 = RandPhraseSimple("Понятно", "Ясно") + ", солдат.";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "First_protector";
		break;
		//---------------- Солдаты ------------------
        case "First_soldier":
            dialog.text = RandPhraseSimple("Я на посту, не отвлекайте меня.", "Проходите мимо, я не могу с вами разговаривать.");
			link.l1 = "Хорошо, солдат.";
			link.l1.go = "exit";
			NextDiag.TempNode = "First_soldier";
		break;
		//---------------- Заключенные ------------------
        case "First_prisoner": 
			if (GetNationRelation2MainCharacter(sti(npchar.nation)) == RELATION_ENEMY)
			{
				dialog.text = LinkRandPhrase("Хо-хо, до чего же весело!!", "Режь их, "+ GetSexPhrase("приятель","подруга") +", режь!!!", "Эх, дьявол! Уж не думал, что увижу труп своего надсмотрщика!");
				link.l1 = RandPhraseSimple("Хех!", "Аргх...");
				link.l1.go = "NoMoreTalkExit";
				if (rand(10) > 6 && !CheckAttribute(pchar, "questTemp.Sharlie.Lock") && !CheckAttribute(pchar, "GenQuest.PrisonQuestLock") && !CheckAttribute(pchar, "quest.GivePrisonFree") && !CheckAttribute(pchar, "quest.GivePrisonFree_Over") && !CheckAttribute(pchar, "quest.DeliverToBander")) // Addon 2016-1 Jason пиратская линейка
				{
					dialog.text = RandPhraseSimple("Постой, "+ GetSexPhrase("дружище","подруга") +"!! Выпусти меня!", "Послушай, "+ GetSexPhrase("приятель","подруга") +", будь так добр"+ GetSexPhrase("","а") +", открой камеру.");
					link.l1 = "С какой это стати?";
					link.l1.go = "Prisoner_1"; // на квест освобождения заключенного
				}
			}
			else
			{
				dialog.text = LinkRandPhrase("Меня взяли за грабеж, дело шьют...", "Агрх, холён"+ GetSexPhrase("ый","ая") +" ты... Тебя бы ко мне в камеру на недельку! Кхе-хе-хе...", "Я ни в чём не виноват!");
				link.l1 = RandPhraseSimple("Заткнись!", "Мне нет до тебя дела...");
				link.l1.go = "NoMoreTalkExit";
				if (rand(10) > 6 && !CheckAttribute(pchar, "questTemp.Sharlie.Lock") && !CheckAttribute(pchar, "GenQuest.PrisonQuestLock") && !CheckAttribute(pchar, "quest.GivePrisonFree_Over") && !CheckAttribute(pchar, "quest.GivePrisonFree") && !CheckAttribute(pchar, "quest.DeliverToBander") && !sti(colonies[FindColony(npchar.city)].HeroOwn)) // Addon 2016-1 Jason пиратская линейка
				{
					dialog.text = RandPhraseSimple("Постой, "+ GetSexPhrase("приятель","подруга") +", не проходи мимо моей камеры так быстро!", "Не торопись, "+ GetSexPhrase("дружище","подруга") +", давай поговорим.");
					link.l1 = "С какой это стати?";
					if (rand(1))
					{
						link.l1.go = "Prisoner_1"; // на квест освобождения заключенного
					}
					else
					{
						link.l1.go = "Deliver_1"; // на квест передачу весточки
					}
				}
			}
		break;
		// -------------------- освобождение заключенного --------------------
        case "Prisoner_1":
            dialog.text = "Чтобы послушать меня. Ты не смотри, что сейчас я в таком виде. Мне бы выбраться отсюда...";
			link.l1 = "Чего?!";
			link.l1.go = "Prisoner_2";
			GetChestPlaceName();
			pchar.questTemp.jailCanMove.prisonerId = npchar.id; //запомним Id
			pchar.questTemp.jailCanMove.IsTrue = rand(4); //вид клада
			pchar.questTemp.jailCanMove.Item1 = GenQuestPrison_GenerateArtefact();
			pchar.questTemp.jailCanMove.Item2 = GenQuestPrison_GenerateBlade();
			pchar.questTemp.jailCanMove.Name = GetFullName(npchar); //имя перца
		break;
        case "Prisoner_2":
            dialog.text = "Что слышал"+ GetSexPhrase("","а") +". Помоги мне выбраться, и я сумею отблагодарить.";
			link.l1 = "Уже интересно. Кто ты такой и что можешь мне предложить?";
			link.l1.go = "Prisoner_3";
		break;
        case "Prisoner_3":
            dialog.text = "Меня зовут " + GetFullName(npchar) + ". Кое-что у меня припрятано в надёжном месте. Вытащи меня отсюда и отвези на " + XI_ConvertString(pchar.questTemp.jailCanMove.islandId + "Acc") + ". Там в гроте у меня спрятан клад. Достанем его и поделим поровну!";
			link.l1 = "И что там у тебя в кладе? И откуда мне знать, что твои слова - правда?";
			link.l1.go = "Prisoner_4";
		break;
        case "Prisoner_4":
            dialog.text = "Клянусь тебе, я говорю чистейшую правду! А в кладе я спрятал деньги и драгоценности...";
			link.l1 = "Нет, приятель. Я не собираюсь рисковать шкурой из-за сомнительного клада. Извини...";
			link.l1.go = "Prisoner_5";
			if (GetNationRelation2MainCharacter(sti(npchar.nation)) != RELATION_ENEMY)
			{			
				link.l2 = "Пожалуй, стоит рискнуть... Предлагаю следующее: я могу перебить стражу в тюрьме и забрать тебя на свой корабль. Если всё получится, я хочу, чтобы ты не отходил от меня до тех пор, пока мы не доберёмся до грота на " + XI_ConvertString(pchar.questTemp.jailCanMove.islandId + "Dat") + ". Идёт?";
				link.l2.go = "Prisoner_agree"; //силовой способ вызволения
				link.l3 = "Ну, хорошо, я постараюсь помочь тебе - поговорю с начальником тюрьмы. Возможно, удастся внести залог за твоё освобождение.";
				link.l3.go = "ToPrisonHead_agree"; //мирный способ вызволения
			}
			else
			{
				link.l2 = "Ну, хорошо, поверю тебе и открою камеру. Я хочу, чтобы ты не отходил от меня до тех пор, пока мы не доберёмся до грота на " + XI_ConvertString(pchar.questTemp.jailCanMove.islandId + "Dat") + ". Идёт?";
				link.l2.go = "Prisoner_agree_3"; //силовой способ вызволения, когда тюремщики убиты
			}
		break;
        case "Prisoner_5":
            dialog.text = RandPhraseSimple("Будь ты проклят"+ GetSexPhrase("","а") +", каналья!!", "Чтоб тебя разорвало, иуда...");
			link.l1 = RandPhraseSimple("И тебе всего хорошего. Прощай...", "Собака лаяла на дядю фраера...");
			link.l1.go = "NoMoreTalkExit";
		break;
        case "Prisoner_agree":
            dialog.text = "Идёт, мне выбирать не приходится.";
			link.l1 = "Хорошо. Я сейчас сломаю твой замок, выходи оттуда, и будем прорываться. Ты готов?";
			link.l1.go = "Prisoner_agree_1";
		break;
        case "Prisoner_agree_1":
            dialog.text = "Да, "+ GetSexPhrase("приятель","подруга") +", я готов!";
			link.l1 = "За дело!";
			link.l1.go = "Prisoner_agree_2";
		break;
        case "Prisoner_agree_2":
			string slai_group = GetNationNameByType(sti(npchar.nation))  + "_citizens";
			LAi_group_AttackGroup(slai_group, LAI_GROUP_PLAYER);
			if (rand(3) != 1) SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
			ReOpenQuestHeader("GivePrisonFree");
			AddQuestRecord("GivePrisonFree", "1");
            AddQuestUserData("GivePrisonFree", "sCity", XI_ConvertString("Colony"+npchar.city+"Gen"));
            AddQuestUserData("GivePrisonFree", "sName", pchar.questTemp.jailCanMove.Name);
            AddQuestUserData("GivePrisonFree", "sIsland", XI_ConvertString(pchar.questTemp.jailCanMove.islandId+"Dat"));
			pchar.quest.GivePrisonFree_Death.win_condition.l1 = "NPC_Death";
			pchar.quest.GivePrisonFree_Death.win_condition.l1.character = npchar.id;
			pchar.quest.GivePrisonFree_Death.win_condition = "GivePrisonFree_Death";
			Pchar.quest.GivePrisonFree.win_condition.l1 = "location";
			Pchar.quest.GivePrisonFree.win_condition.l1.location = pchar.questTemp.jailCanMove.placeId;
			Pchar.quest.GivePrisonFree.win_condition = "GivePrisonFree";			
			DeleteAttribute(npchar, "LifeDay");
			GiveItem2Character(npchar, "unarmed");
			EquipCharacterbyItem(npchar, "unarmed");
			GetCharacterPos(npchar, &locx, &locy, &locz);	
			ChangeCharacterAddressGroup(npchar, npchar.location, "reload", LAi_FindNearestFreeLocator("reload", locx, locy, locz));
			LAi_SetActorType(npchar);
			LAi_group_Register("DeliveQuest_Prison");
			LAi_group_SetRelation("DeliveQuest_Prison", LAI_GROUP_PLAYER, LAI_GROUP_FRIEND);
			//LAi_group_SetAlarmReaction(LAI_GROUP_PLAYER, "DeliveQuest_Prison", LAI_GROUP_ENEMY, LAI_GROUP_FRIEND);
			LAi_group_MoveCharacter(npchar, "DeliveQuest_Prison");
			LAi_ActorFollowEverywhere(npchar, "", -1);
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;

        case "Prisoner_agree_3":
            dialog.text = "Идёт, мне выбирать не приходится.";
			link.l1 = "Хорошо. Следуй за мной как можно быстрей, нам нужно ещё добраться до моего корабля. Не отставай!";
			link.l1.go = "Prisoner_agree_4";
		break;
        case "Prisoner_agree_4":
			ReOpenQuestHeader("GivePrisonFree");
			AddQuestRecord("GivePrisonFree", "1");
            AddQuestUserData("GivePrisonFree", "sCity", XI_ConvertString("Colony"+npchar.city+"Gen"));
            AddQuestUserData("GivePrisonFree", "sName", pchar.questTemp.jailCanMove.Name);
            AddQuestUserData("GivePrisonFree", "sIsland", XI_ConvertString(pchar.questTemp.jailCanMove.islandId+"Dat"));
			pchar.quest.GivePrisonFree_Death.win_condition.l1 = "NPC_Death";
			pchar.quest.GivePrisonFree_Death.win_condition.l1.character = npchar.id;
			pchar.quest.GivePrisonFree_Death.win_condition = "GivePrisonFree_Death";
			Pchar.quest.GivePrisonFree.win_condition.l1 = "location";
			Pchar.quest.GivePrisonFree.win_condition.l1.location = pchar.questTemp.jailCanMove.placeId;
			Pchar.quest.GivePrisonFree.win_condition = "GivePrisonFree";
			DeleteAttribute(npchar, "LifeDay");
			GiveItem2Character(npchar, "unarmed");
			EquipCharacterbyItem(npchar, "unarmed");
			GetCharacterPos(npchar, &locx, &locy, &locz);	
			ChangeCharacterAddressGroup(npchar, npchar.location, "reload", LAi_FindNearestFreeLocator("reload", locx, locy, locz));
			LAi_SetActorType(npchar);
			LAi_group_Register("DeliveQuest_Prison");
			LAi_group_SetRelation("DeliveQuest_Prison", LAI_GROUP_PLAYER, LAI_GROUP_FRIEND);
			//LAi_group_SetAlarmReaction(LAI_GROUP_PLAYER, "DeliveQuest_Prison", LAI_GROUP_ENEMY, LAI_GROUP_FRIEND);
			LAi_group_MoveCharacter(npchar, "DeliveQuest_Prison");
			LAi_ActorFollowEverywhere(npchar, "", -1);
			DialogExit();
		break;

        case "ToPrisonHead_agree":
            dialog.text = "Ну, попробуй. Эх-х-х, получилось бы! Только не теряй времени, через пару дней меня здесь уже не будет...";
			link.l1 = "Жди, я всё улажу.";
			link.l1.go = "NoMoreTalkExit";
			pchar.questTemp.jailCanMove.City = npchar.City; //город
			pchar.questTemp.jailCanMove.ownerPrison = rand(6); //характер преступления
			SetTimerCondition("GivePrisonFree_Over", 0, 0, 2, false);
			AddQuestRecord("GivePrisonFree", "5");
			AddQuestUserData("GivePrisonFree", "sSex", GetSexPhrase("ся","ась"));
            AddQuestUserData("GivePrisonFree", "sCity", XI_ConvertString("Colony"+npchar.city+"Gen"));
            AddQuestUserData("GivePrisonFree", "sName", pchar.questTemp.jailCanMove.Name);
		break;

        case "ToPrisonHead_canMove":
            dialog.text = "Ну, что скажешь, "+ GetSexPhrase("приятель","подруга") +"?";
			link.l1 = "Всё улажено, я могу забирать тебя.";
			link.l1.go = "ToPrisonHead_canMove_1";
		break;
        case "ToPrisonHead_canMove_1":
            dialog.text = "Ну, так пойдём отсюда быстрее! Чёрт возьми, как я рад!";
			link.l1 = "Подведём итоги. Я хочу, чтобы всё время, пока мы не доберемся до грота на " + XI_ConvertString(pchar.questTemp.jailCanMove.islandId + "Dat") + ", ты не отходил от меня ни на шаг. На всякий случай. Ты согласен?";
			link.l1.go = "ToPrisonHead_canMove_2";
		break;
        case "ToPrisonHead_canMove_2":
            dialog.text = "Конечно, согласен! Да и выбирать мне не приходится.";
			link.l1 = "Тогда ты свободен.";
			link.l1.go = "ToPrisonHead_canMove_exit";
		break;
        case "ToPrisonHead_canMove_exit":
			pchar.quest.GivePrisonFree_Over.over = "yes";
			ReOpenQuestHeader("GivePrisonFree");
			AddQuestRecord("GivePrisonFree", "1");
            AddQuestUserData("GivePrisonFree", "sCity", XI_ConvertString("Colony"+npchar.city+"Gen"));
            AddQuestUserData("GivePrisonFree", "sName", pchar.questTemp.jailCanMove.Name);
            AddQuestUserData("GivePrisonFree", "sIsland", XI_ConvertString(pchar.questTemp.jailCanMove.islandId+"Dat"));
			pchar.quest.GivePrisonFree_Death.win_condition.l1 = "NPC_Death";
			pchar.quest.GivePrisonFree_Death.win_condition.l1.character = npchar.id;
			pchar.quest.GivePrisonFree_Death.win_condition = "GivePrisonFree_Death";
			Pchar.quest.GivePrisonFree.win_condition.l1 = "location";
			Pchar.quest.GivePrisonFree.win_condition.l1.location = pchar.questTemp.jailCanMove.placeId;
			Pchar.quest.GivePrisonFree.win_condition = "GivePrisonFree";			
			DeleteAttribute(npchar, "LifeDay");
			GiveItem2Character(npchar, "unarmed");
			EquipCharacterbyItem(npchar, "unarmed");
			GetCharacterPos(npchar, &locx, &locy, &locz);	
			ChangeCharacterAddressGroup(npchar, npchar.location, "reload", LAi_FindNearestFreeLocator("reload", locx, locy, locz));
			LAi_SetActorType(npchar);
			LAi_group_Register("DeliveQuest_Prison");
			LAi_group_SetRelation("DeliveQuest_Prison", LAI_GROUP_PLAYER, LAI_GROUP_FRIEND);
			//LAi_group_SetAlarmReaction(LAI_GROUP_PLAYER, "DeliveQuest_Prison", LAI_GROUP_ENEMY, LAI_GROUP_FRIEND);
			LAi_group_MoveCharacter(npchar, "DeliveQuest_Prison");
			LAi_ActorFollowEverywhere(npchar, "", -1);
			DialogExit();
		break;

        case "ToPrisonHead_notFree":
			switch (pchar.questTemp.jailCanMove.ownerPrison)
			{
				case "0": sTemp = "убийстве"; break;
				case "1": sTemp = "пиратстве"; break;
				case "2": sTemp = "разбое"; break;
				case "3": sTemp = "воровстве"; break;
			}
            dialog.text = "Ну, что скажешь, "+ GetSexPhrase("приятель","подруга") +"?";
			link.l1 = "Мне не удалось договориться о твоём освобождении. Тебя обвиняют в " + sTemp + ", так что ни о каких залогах речи быть не может.";
			link.l1.go = "ToPrisonHead_notFree_1";
			DeleteAttribute(pchar, "questTemp.jailCanMove.ownerPrison");
		break;
		
        case "ToPrisonHead_notFree_1":
            dialog.text = "Меня оболгали!.. Вот дьявол!! И что теперь мне делать? Я же сгнию здесь заживо!";
			link.l1 = "Очень жаль, приятель, но я ничем не могу тебе помочь.";
			link.l1.go = "ToPrisonHead_notFree_2";
			link.l2 = "Остаётся шанс освободить тебя силой. Я сейчас сломаю твой замок, выходи оттуда, и будем прорываться. Ты готов?";
			link.l2.go = "Prisoner_agree_1";
			pchar.quest.GivePrisonFree_Over.over = "yes";
		break;
		
        case "ToPrisonHead_notFree_2":
            dialog.text = RandPhraseSimple("Будь ты проклят"+ GetSexPhrase("","а") +", каналья!!", "Чтоб тебя разорвало, иуда...");
			link.l1 = "И тебе всего хорошего. Прощай...";
			link.l1.go = "NoMoreTalkExit";
			AddQuestRecord("GivePrisonFree", "7");
            AddQuestUserData("GivePrisonFree", "sName", pchar.questTemp.jailCanMove.Name);
			DeleteAttribute(pchar, "questTemp.jailCanMove.islandId");	
			DeleteAttribute(pchar, "questTemp.jailCanMove.placeId");
			DeleteAttribute(pchar, "questTemp.jailCanMove.prisonerId");
			DeleteAttribute(pchar, "questTemp.jailCanMove.IsTrue");
			DeleteAttribute(pchar, "questTemp.jailCanMove.Sum");
			DeleteAttribute(pchar, "questTemp.jailCanMove.Name");
		break;

        case "ToPrisonHead_expansive":
			dialog.text = "Ну, чем обрадуешь, "+ GetSexPhrase("приятель","подруга") +"?";
			link.l1 = "Залог за твоё освобождение слишком велик, у меня нет таких денег. Я вынужден"+ GetSexPhrase("","а") +" отказаться от помощи тебе.";
			link.l1.go = "ToPrisonHead_notFree_2";
			pchar.quest.GivePrisonFree_Over.over = "yes";
		break;
		//==> в месте, где клад припрятан
        case "PrisonerInPlace":
			switch (sti(pchar.questTemp.jailCanMove.IsTrue))
			{
				case 0:
					dialog.text = "Слушай, я тут проверил всё, но моего клада не нашёл. Очень жаль, что так вышло, наверное, кто-то раскопал его до нас.";
					link.l1 = "Как такое может быть?!";
					link.l1.go = "PrisonerInPlace_1";
				break;
				case 1:
					dialog.text = "Я нашёл его! Драгоценности лежали там, где я их и оставил.";
					link.l1 = "Великолепно. Ну что, будем делить?";
					link.l1.go = "Node_1";
				break;
				case 2:
					dialog.text = "Ну вот он, мой схрон. Невелик, правда, но это всё, что у меня есть. Как договаривались - половина ваша.";
					link.l1 = "Да, клад и в самом деле, не ахти. Ну что же, спасибо и на том.";
					link.l1.go = "Node_2";
				break;
				case 3:
					dialog.text = "Капитан, извините, тут так вышло... короче, нет клада.";
					link.l1 = "Что? Ты меня обманул, негодяй! Я тебя вытащил"+ GetSexPhrase("","а") +" из-за решётки, тащил"+ GetSexPhrase("ся","ась") +" на этот остров, и всё ради чего?! Это тебе с рук не сойдёт!";
					link.l1.go = "Node_3";
				break;
				case 4:
					dialog.text = "Чёрт возьми... Ну как же так? Не может быть!";
					link.l1 = "Ты чего, приятель? Где наш клад? Только не говори, что его нет!";
					link.l1.go = "Node_4";
				break;
			}
		break;
			
		case "Node_1":
			dialog.text = "Да, конечно, как договаривались. Половина сокровищ ваша.";
			link.l1 = "Ух ты, сколько тут всего ценного!";
			link.l1.go = "PrisonerInPlace_3";
			Log_Info("Вы получили свою долю клада");
			PlaySound("interface\important_item.wav");
			TakeNItems(pchar, "icollection", 1+drand(1));
			TakeNItems(pchar, "chest", 4+drand(4));
			TakeNItems(pchar, "jewelry1", 70+rand(15));
			TakeNItems(pchar, "jewelry2", 50+rand(15));
			TakeNItems(pchar, "jewelry3", 60+rand(15));
			TakeNItems(pchar, "jewelry4", 40+rand(10));
			TakeNItems(pchar, "jewelry5", 10+rand(10));
			TakeNItems(pchar, "jewelry46", 60+rand(20));
			TakeNItems(pchar, "jewelry47", 40+rand(15));
			TakeNItems(pchar, "jewelry40", 60+rand(20));
			AddQuestRecord("GivePrisonFree", "3_1");
			AddQuestUserData("GivePrisonFree", "sName", pchar.questTemp.jailCanMove.Name);
			CloseQuestHeader("GivePrisonFree");
			DeleteAttribute(pchar, "questTemp.jailCanMove.Item1");
			DeleteAttribute(pchar, "questTemp.jailCanMove.Item2");
		break;
			
		case "Node_2":
			dialog.text = "Капитан, здесь среди прочего есть вот этот индейский предмет. Возьмите его сверх вашей доли.";
			link.l1 = "Ну, хоть что-то толковое получу за твоё освобождение! Давай его сюда.";
			link.l1.go = "PrisonerInPlace_3";
			Log_Info("Вы получили свою долю клада");
			PlaySound("interface\important_item.wav");
			sTemp = pchar.questTemp.jailCanMove.Item1;
			TakeNItems(pchar, sTemp, 1);
			TakeNItems(pchar, "jewelry5", 40+rand(10));
			TakeNItems(pchar, "jewelry6", 20+rand(20));
			TakeNItems(pchar, "jewelry17", 80+rand(20));
			TakeNItems(pchar, "jewelry13", 10+rand(10));
			TakeNItems(pchar, "jewelry10", 20+rand(20));
			TakeNItems(pchar, "jewelry12", 50+rand(20));
			TakeNItems(pchar, "jewelry11", rand(2)+1);
			AddQuestRecord("GivePrisonFree", "3_2");
			AddQuestUserData("GivePrisonFree", "sName", pchar.questTemp.jailCanMove.Name);
			CloseQuestHeader("GivePrisonFree");
			DeleteAttribute(pchar, "questTemp.jailCanMove.Item1");
			DeleteAttribute(pchar, "questTemp.jailCanMove.Item2");
		break;
			
		case "Node_3":
			dialog.text = "Подождите, капитан, не горячитесь, дайте мне сказать. Я тоже моряк, как и вы. Меня бросили в тюрьму по ошибке, клянусь. Вы были моим единственным шансом спастись, и мне пришлось вам солгать о кладе\nКлада нет, но я спрятал тут одну хорошую вещь. Возьмите её, и отпустите меня с миром. Возможно, в бою вы ещё не раз помянете меня добрым словом.";
			link.l1 = "Ладно, всё равно взять с тебя нечего. Благодари Бога, что я отходчив"+ GetSexPhrase("ый","ая") +".";
			link.l1.go = "PrisonerInPlace_3";
			Log_Info("Вы получили экипировку");
			PlaySound("interface\important_item.wav");
			sTemp = pchar.questTemp.jailCanMove.Item2;
			TakeNItems(pchar, sTemp, 1);
			AddQuestRecord("GivePrisonFree", "3_3");
			AddQuestUserData("GivePrisonFree", "sName", pchar.questTemp.jailCanMove.Name);
			CloseQuestHeader("GivePrisonFree");
			DeleteAttribute(pchar, "questTemp.jailCanMove.Item1");
			DeleteAttribute(pchar, "questTemp.jailCanMove.Item2");
		break;
			
		case "Node_4":
			dialog.text = "Нет!!! Его действительно нет! Проклятый обрывок... Капитан, поверьте, я действительно думал, что он здесь! Но, видимо, я ошибся! На этом клочке бумаги всё так непонятно...";
			link.l1 = "Та-ак, похоже, сейчас у тебя будут серьёзные проблемы, приятель. Но сперва я хочу послушать твои объяснения.";
			link.l1.go = "Node_4_1";
		break;
			
		case "Node_4_1":
			dialog.text = "У меня был кусок карты. Подлинной карты, клянусь! Но по нему так тяжело разобрать, что за остров на нём указан... Я подумал, что это здесь. Но, как вы видите, это не так.";
			link.l1 = "Что за кусок карты? Давай его сюда, живо!";
			link.l1.go = "Node_4_2";
		break;
			
		case "Node_4_2":
			if (CheckCharacterItem(pchar, "map_part1"))
			{
				GiveItem2Character(pchar, "map_part2");
			}
			else
			{
				GiveItem2Character(pchar, "map_part1");
			}
			dialog.text = "Вот, берите, конечно. Капитан, отпустите меня, пожалуйста... Я и в самом деле думал, что клад тут. Может, вы разберётесь по этому клочку, где он, и заберёте всё себе. Прошу вас.";
			link.l1 = "Да уж... Разобрать что-либо тут очень сложно. Нужна вторая половина карты. Ладно, проваливай, вижу, ты действительно хотел, как лучше.";
			link.l1.go = "PrisonerInPlace_4";
		break;
			
		case "PrisonerInPlace_1":
			dialog.text = "Да очень просто, "+ GetSexPhrase("приятель","подруга") +". Ещё и не такое в жизни случается\nНу ладно, ты тут, если хочешь, оставайся, поищи ещё. Ну, а мне пора!\nПрощай, "+ GetSexPhrase("друг","подруга") +", спасибо, что спас"+ GetSexPhrase("","ла") +" мне жизнь. Я буду помнить тебя вечно!";
			link.l1 = "Ах ты мерзавец! Думаешь, я дам тебе так просто уйти?! Эй... А ну стой, трус!";
			link.l1.go = "PrisonerInPlace_2";
			AddQuestRecord("GivePrisonFree", "4");
			AddQuestUserData("GivePrisonFree", "sName", pchar.questTemp.jailCanMove.Name);
			CloseQuestHeader("GivePrisonFree");
			DeleteAttribute(pchar, "questTemp.jailCanMove.Item1");
			DeleteAttribute(pchar, "questTemp.jailCanMove.Item2");
		break;
			
        case "PrisonerInPlace_2":
			LAi_group_Delete("EnemyFight");
			DeleteAttribute(pchar, "questTemp.jailCanMove.islandId");	
			DeleteAttribute(pchar, "questTemp.jailCanMove.placeId");
			DeleteAttribute(pchar, "questTemp.jailCanMove.prisonerId");
			DeleteAttribute(pchar, "questTemp.jailCanMove.IsTrue");
			DeleteAttribute(pchar, "questTemp.jailCanMove.Sum");
			DeleteAttribute(pchar, "questTemp.jailCanMove.Name");
			chrDisableReloadToLocation = false;
			LAi_LocationDisableMonstersGen(pchar.location, false);
			npchar.lifeDay = 0;
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_SetActorType(npchar);
            LAi_ActorRunToLocation(NPChar, "reload", "reload1_back", "none", "", "", "", -1);
			DialogExit();

            Pchar.quest.DeletePrisonGroup.win_condition.l1 = "ExitFromLocation";
            Pchar.quest.DeletePrisonGroup.win_condition.l1.location = pchar.location;
            Pchar.quest.DeletePrisonGroup.win_condition = "DeletePrisonGroup";
		break;
		
        case "PrisonerInPlace_3":
			dialog.text = "Пожалуйста, получите. И спасибо вам!";
			link.l1 = "Прощай...";
			link.l1.go = "PrisonerInPlace_2";
		break;
		
        case "PrisonerInPlace_4":
			dialog.text = "Спасибо вам, капитан! Я буду молиться за вас до конца своих дней!";
			link.l1 = "Ладно тебе заливать! Иди с Богом...";
			link.l1.go = "PrisonerInPlace_2";
			AddQuestRecord("GivePrisonFree", "3_4");
            AddQuestUserData("GivePrisonFree", "sName", pchar.questTemp.jailCanMove.Name);
			AddQuestUserData("GivePrisonFree", "sSex", GetSexPhrase("","а"));
			CloseQuestHeader("GivePrisonFree");
			DeleteAttribute(pchar, "questTemp.jailCanMove.Item1");
			DeleteAttribute(pchar, "questTemp.jailCanMove.Item2");
		break;
        
		// -------------------- освобождение заключенного --------------------
		// ------------------------ передать маляву --------------------------
        case "Deliver_1":
			dialog.text = "Меня кличут " + GetFullName(npchar) + ". Есть у меня к тебе просьба одна, хе-хе...";
			link.l1 = "Что такое?";
			link.l1.go = "Deliver_2";
		break;
        case "Deliver_2":
			dialog.text = "Нужно передать маляву на волю. Сделаешь?";
			link.l1 = "А какой мне с этого резон?";
			link.l1.go = "Deliver_3";
		break;
        case "Deliver_3":
			dialog.text = "Не обидят тебя кореши, чего уж... Ну так что, возьмёшься?";
			link.l1 = "Нет, меня это не интересует.";
			link.l1.go = "Prisoner_5";
			link.l2 = "Хм, если далеко ходить не надо, то возьмусь.";
			link.l2.go = "Deliver_agree";
		break;
        case "Deliver_agree":
			dialog.text = "Хорошо. Слушай теперь меня внимательно. В городе ждут мою маляву два кента, заныкались они в доме, чтобы под шмон не попасть. В каком доме - не ведаю, надо будет поискать.";
			link.l1 = "Как поискать?";
			link.l1.go = "Deliver_4";
		break;
        case "Deliver_4":
			dialog.text = "Обычно поискать. По городу побегаешь, в дома позаглядываешь... Как в нужное место попадёшь, они тебя сами без разговора не выпустят. Только имей в виду, что здесь я ещё дня два пробуду, не более. Так что не тяни.";
			link.l1 = "Ясно. Ну, давай свою весточку.";
			link.l1.go = "Deliver_5";
		break;
        case "Deliver_5":
			pchar.questTemp.jailCanMove.Deliver.locationId = GetBanderLocation(npchar); //Id коммона
			if (pchar.questTemp.jailCanMove.Deliver.locationId == "none")
			{
				dialog.text = "Хм, что-то ты мне не нравишься. Я передумал. Давай, проходи, не стой здесь!";
				link.l1 = "Вот это да! Ну ладно, как хочешь...";
				link.l1.go = "NoMoreTalkExit";
				DeleteAttribute(pchar, "questTemp.jailCanMove.Deliver");
			}
			else
			{
				dialog.text = "Держи. Спасибо тебе, "+ GetSexPhrase("приятель","подруга") +"!";
				link.l1 = "Да не за что.";
				link.l1.go = "NoMoreTalkExit";
				GiveItem2Character(Pchar, "Malyava");
				pchar.questTemp.jailCanMove.Deliver.Id = npchar.id; //Id зэка
				pchar.questTemp.jailCanMove.Deliver.name = GetFullName(npchar); //имя зэка
				pchar.questTemp.jailCanMove.Deliver.City = npchar.city; //город (Id колонии)
				pchar.questTemp.jailCanMove.Deliver.good = rand(3); //опрокинут или нет
				pchar.questTemp.jailCanMove.Deliver.price = rand(6)*500+500; //цена услуги
				pchar.quest.DeliverToBander.win_condition.l1 = "location";
				pchar.quest.DeliverToBander.win_condition.l1.location = pchar.questTemp.jailCanMove.Deliver.locationId;
				pchar.quest.DeliverToBander.win_condition = "DeliverToBander";
				pchar.quest.DeliverToBander.again = true; 
				SetTimerCondition("DeliverToBander_over", 0, 0, 2, false);
				ReOpenQuestHeader("GivePrisonFree");
				AddQuestRecord("GivePrisonFree", "8");
				AddQuestUserData("GivePrisonFree", "sSex", GetSexPhrase("cя","ась"));
				AddQuestUserData("GivePrisonFree", "sCity", XI_ConvertString("Colony"+npchar.city+"Gen"));
				AddQuestUserData("GivePrisonFree", "sName", pchar.questTemp.jailCanMove.Deliver.name);
			}
		break;
		
		// Warship, 16.05.11. Генер "Правосудие на продажу".
		case "JusticeOnSale_1":
			dialog.text = "Да, он был взят по обвинению в контрабанде. А что вам до этого висельника, " + GetAddress_Form(NPChar) + "?";
			link.l1 = "Его шайка планирует вызволить его и продолжить свой грязный промысел.";
			link.l1.go = "JusticeOnSale_2";
			link.l2 = "До меня дошли слухи, что он невиновен.";
			link.l2.go = "JusticeOnSale_3";
			
			DeleteAttribute(PChar, "GenQuest.JusticeOnSale.PrisonWait");
		break;
		
		case "JusticeOnSale_2":
			dialog.text = "Вам необходимо поставить в известность губернатора, " + GetAddress_Form(NPChar) + ", этих мерзавцев нужно выловить всех до единого!";
			link.l1 = "Так и сделаю.";
			link.l1.go = "exit";
			NextDiag.TempNode = "First_officer";
		break;
		
		case "JusticeOnSale_3":
			dialog.text = "Послушайте, " + GetFullName(PChar) + ", этот тип был взят при попытке сбыть запрещённый товар, прямо в городе! Как вы можете утверждать его невиновность?";
			link.l1 = "Я слышал, что обвинение бездоказательно и улик у вас нет, разве не так? Нельзя держать за решёткой несправедливо обвиненного человека.";
			link.l1.go = "JusticeOnSale_4";
		break;
		
		case "JusticeOnSale_4":
			dialog.text = "У нас нет свидетелей и собственно товара, но это ничего не меняет, капитан " + GetFullName(PChar) + "! Этот человек совершенно точно виновен, и, возможно, не только в незаконной торговле. В любом случае – какое вам дело до заключённого?";
			link.l1 = "Ну, может быть моё слово послужит порукой этому несчастному?";
			link.l1.go = "JusticeOnSale_5_WithoutMoney";
			
			if(sti(PChar.money) >= 5000)
			{
				link.l2 = "Может эти 5000 песо и моё слово послужат порукой этому несчастному?";
				link.l2.go = "JusticeOnSale_5";
			}
		break;
		
		case "JusticeOnSale_5_WithoutMoney":
			if(GetCharacterSkill(PChar, SKILL_LEADERSHIP) > dRand(100) || sti(PChar.money) < 5000)
			{
				dialog.text = "Хорошо, " + GetAddress_Form(NPChar) + ", забирайте этого проходимца и уходите, пока я не передумал.";
				link.l1 = "Приятно наблюдать торжество правосудия, не находите?";
				link.l1.go = "JusticeOnSale_6";
			}
			else
			{
				dialog.text = "Нет, " + GetAddress_Form(NPChar) + ", так не пойдёт.";
				link.l1 = "В таком случае может эти 5000 песо будут более весомым доводом?";
				link.l1.go = "JusticeOnSale_5";
			}
		break;
		
		case "JusticeOnSale_5":
			dialog.text = "Хорошо, " + GetAddress_Form(NPChar) + ", забирайте этого проходимца и уходите, пока я не передумал.";
			link.l1 = "Приятно наблюдать торжество правосудия, не находите?";
			link.l1.go = "JusticeOnSale_6";
			AddMoneyToCharacter(PChar, -5000);
			PChar.GenQuest.JusticeOnSale.PrisonMoney = true;
		break;
		
		case "JusticeOnSale_6":
			DialogExit();
			sld = GetCharacter(NPC_GenerateCharacter("JusticeOnSale_Smuggler", "mercen_"+(rand(9)+1), "man", "man", sti(PChar.rank)+5, PIRATE, -1, true, "marginal"));
			SetFantomParamFromRank(sld, sti(PChar.rank)+5, true);
			sld.name = PChar.GenQuest.JusticeOnSale.SmugglerName;
			sld.lastName = "";
			sld.dialog.filename = "GenQuests_Dialog.c";
			sld.dialog.currentnode = "First time";
			sld.greeting = "Enc_Raiders"; 
			AddPassenger(PChar, sld, false);
			SetCharacterRemovable(sld, false);
			PChar.GenQuest.JusticeOnSale.SmugglerModel = sld.model;
			DeleteAttribute(PChar, "GenQuest.JusticeOnSale.MayorWait");
			sld = &Locations[FindLocation(PChar.GenQuest.JusticeOnSale.ShoreId)];
			sld.DisableEncounters = true;
			PChar.Quest.JusticeOnSale_ShoreEnterWithSmuggler.win_condition.l1  = "location";
			PChar.Quest.JusticeOnSale_ShoreEnterWithSmuggler.win_condition.l1.location = PChar.GenQuest.JusticeOnSale.ShoreId;
			PChar.Quest.JusticeOnSale_ShoreEnterWithSmuggler.function = "JusticeOnSale_ShoreEnterWithSmuggler";
			Log_Info("Капитан контрабандистов поднялся к вам на борт");
			PlaySound("interface\notebook.wav");
			LAi_Fade("", "");
			WaitDate("",0,0,0,0,60); // 280313 // лесник. прокрутка времени было так WaitDate("",0,0,0,2,5);
		break;
	}
}

void GetChestPlaceName()
{
	string islandId;
	int iTemp = rand(3);
	switch (iTemp)
	{
		case 0: 
			pchar.questTemp.jailCanMove.islandId = "Bermudes";
			pchar.questTemp.jailCanMove.placeId = "Bermudes_Cavern";
		break;
		case 1: 
			pchar.questTemp.jailCanMove.islandId = "Caiman";
			pchar.questTemp.jailCanMove.placeId = "Caiman_Grot";
		break;
		case 2: 
			pchar.questTemp.jailCanMove.islandId = "Dominica";
			pchar.questTemp.jailCanMove.placeId = "Dominica_Grot";
		break;
		case 3: 
			pchar.questTemp.jailCanMove.islandId = "Terks";
			pchar.questTemp.jailCanMove.placeId = "Terks_Grot";
		break;
	}
}

string GetBanderLocation(ref npchar)
{
    aref	arCommon, arRld, arRld2;
    int	i, n, Qty, Qty2;
	string LocId; 
	string	storeArray [50];
	int howStore = 0;
    makearef(arRld, Locations[FindLocation(npchar.city + "_town")].reload);
	Qty = GetAttributesNum(arRld);
    if (CheckAttribute(pchar, "GenQuest.SeekSpy.Location")) //если взят квест мэра по поиску шпиона
	{
		for (i=0; i<Qty; i++)
		{
    		arCommon = GetAttributeN(arRld, i);
			LocId = arCommon.go;
    		if (findsubstr(LocId, "Common" , 0) != -1 && LocId != pchar.GenQuest.SeekSpy.Location)
    		{			
				storeArray[howStore] = LocId;
				howStore++; 
			}
			if (arCommon.label != "Sea")
			{	
				makearef(arRld2, Locations[FindLocation(LocId)].reload);
				Qty2 = GetAttributesNum(arRld2);
				for (n=0; n<Qty2; n++)
				{
    				arCommon = GetAttributeN(arRld2, n);
					LocId = arCommon.go;
					if (findsubstr(LocId, "Common" , 0) != -1 && LocId != pchar.GenQuest.SeekSpy.Location)
    				{
						storeArray[howStore] = LocId;
						howStore++; 					
					}
				}
			}	
		}
	}
	else
	{
		for (i=0; i<Qty; i++)
		{
    		arCommon = GetAttributeN(arRld, i);
			LocId = arCommon.go;
    		if (findsubstr(LocId, "Common" , 0) != -1)
    		{			
				storeArray[howStore] = LocId;
				howStore++; 
			}
			if (arCommon.label != "Sea")
			{	
				makearef(arRld2, Locations[FindLocation(LocId)].reload);
				Qty2 = GetAttributesNum(arRld2);
				for (n=0; n<Qty2; n++)
				{
    				arCommon = GetAttributeN(arRld2, n);
					LocId = arCommon.go;
					if (findsubstr(LocId, "Common" , 0) != -1)
    				{
						storeArray[howStore] = LocId;
						howStore++; 
					}
				}
			}	
		}
	}
	if (howStore == 0) return "none";
	LocId = storeArray[rand(howStore-1)];
	SetOpenDoorCommonLoc(npchar.city, LocId); //открываем дверь
	for(n=0; n<MAX_CHARACTERS; n++)
	{
		if (CheckAttribute(&characters[n], "locations") && characters[n].locations == LocId) 
		{			
			characters[n].lifeDay = 0;
		}
	}
	return LocId;
}

string GenQuestPrison_GenerateArtefact() // артефакты
{
	string itemID;
	switch(rand(7))
	{
		case 0:
			itemID = "indian_5";
		break;
		case 1:
			itemID = "indian_7"; 
		break;
		case 2:
			itemID = "indian_8"; 
		break;
		case 3:
			itemID = "indian_9"; 
		break;
		case 4:
			itemID = "indian_10"; 
		break;
		case 5:
			itemID = "indian_11"; 
		break;
		case 6:
			itemID = "indian_3"; 
		break;
		case 7:
			itemID = "indian_6"; 
		break;
	}
	return itemID;
}

string GenQuestPrison_GenerateBlade() // клинки и другое
{
	string itemID;
	switch(rand(8))
	{
		case 0:
			itemID = GetGeneratedItem("blade_16");
		break;
		case 1:
			itemID = GetGeneratedItem("blade_15"); 
		break;
		case 2:
			itemID = GetGeneratedItem("blade_13"); 
		break;
		case 3:
			itemID = "cirass2"; 
		break;
		case 4:
			itemID = GetGeneratedItem("blade_10"); 
		break;
		case 5:
			itemID = "spyglass3"; 
		break;
		case 6:
			itemID = "cirass6"; 
		break;
		case 7:
			itemID = "cirass7"; 
		break;
		case 8:
			itemID = "cirass1"; 
		break;	
		
	}
	return itemID;
}