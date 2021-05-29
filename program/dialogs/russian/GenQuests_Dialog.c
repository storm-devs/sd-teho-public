void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;
	
	DeleteAttribute(&Dialog,"Links");
	
	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	ref rItem, rChar, sld, MerPrm;
	aref arTemp1, arTemp2;
	bool bTemp;
	int iBanditsCount, i, iMoney, iNation, iTmp, iGoods;
	String sTitle, sGroup, sTemp;
	float locx, locy, locz;
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "Явный баг. Как он здесь оказался? Сообщите о нем Warship'у и подробно расскажите, как Вы его получили.";
					link.l1 = RandSwear() + "Обязательно сообщу!";
					link.l1.go = "exit";
					
			if(HasSubStr(NPChar.id, "ContraMeetManQuest_Soldier_")) // Солдеры по квесту "встреча в бухте"
			{
				dialog.text = "Я не уполномочен с вами разговаривать. Обратитесь к нашему офицеру.";
					link.l1 = LinkRandPhrase("Конечно...", "Ясно.", "Обязательно!");
					link.l1.go = "exit";
				break;
			}
			
			if(HasSubStr(NPChar.id, "ContraMeetManQuest_Officer_")) // Офицер по квесту "встреча в бухте"
			{
				dialog.text = "Представьтесь, я хочу знать, с кем разговариваю!";
					link.l1 = "Меня зовут " + GetFullName(PChar) + ". Что здесь происходит?";
					link.l1.go = "ContraMeetManQuest_Sold_1";
				break;
			}
					
			if(NPChar.id == "ContraMeetManQuest_QuestMan" && PChar.location == PChar.GenQuest.ContraMeetMan.ShoreID) // Квестовый чел по генеру "встреча в бухте" 
			{
				dialog.text = "Кэп, тебя зовут" + GetFullName(PChar) + ", не так-ли?";
					link.l1 = "Да, это так...";
					link.l1.go = "ContraMeetManQuest_1";
					link.l2 = "Нет. Вы меня с кем-то спутали...";
					link.l2.go = "exit";
					break;
			}
			
			if(NPChar.id == "ContraMeetManQuest_QuestMan" && CheckAttribute(PChar, "GenQuest.ContraMeetMan.ContraIsDead")) // В комнате таверны после убицства контриков
			{
				LAi_LocationFightDisable(LoadedLocation, false);
				dialog.text = PChar.name + ", спасибо вам большое! Если бы не вы, моя участь была бы прискорбна... Как я могу вас отблагодарить?";
					link.l1 = "Мне ничего не нужно...";
					link.l1.go = "ContraMeetManQuest_7";
					link.l2 = "Я бы не отказал"+ GetSexPhrase("ся","ась") +" от небольшого вознаграждения.";
					link.l2.go = "ContraMeetManQuest_8";
					break;
			}
			
			if(NPChar.id == "ContraMeetManQuest_Contrick_0") // Контрик в комнате по квесту "встреча в бухте"
			{
				iMoney = (rand(3)+2)*500;
				PChar.GenQuest.ContraMeetMan.Money = iMoney;
				if(!CheckAttribute(PChar, "GenQuest.ContraMeetMan.ManIsTraitor")) // Просто платят деньги
				{
					dialog.text = "...Хм, и вправду, это он... Спасибо, "+ GetSexPhrase("парень","деваха") +", без твоей помощи нам пришлось бы туго - все пути за город нам заказаны. Вот, держи " + FindRussianMoneyString(iMoney) + " и можешь проваливать. А мы пойдем побеседуем с нашим товарищем...";
						link.l1 = "...";
						link.l1.go = "ContraMeetManQuest_3";
				}
				else
				{
					dialog.text = "...Хм, и вправду, это он... Спасибо, "+ GetSexPhrase("парень","деваха") +", без твоей помощи нам пришлось бы туго - все пути за город нам заказаны. Вот, держи " + FindRussianMoneyString(iMoney) + " и проваливай. Не мешай нам выпустить кишки этому предателю!...";
						link.l1 = "Конечно. До встречи, господа...";
						link.l1.go = "ContraMeetManQuest_4";
						link.l2 = "Что?! Нет, я не позволю совершаться убийству, кто бы он ни был... И не нужны мне ваши кровавые деньги!";
						link.l2.go = "ContraMeetManQuest_5";
				}
					break;
			}
			
			if(NPChar.id == "ContraDeliverQuest_Soldier_0") // Солдер в комнате
			{
				dialog.text = "Так-так-так... Что тут у нас?! Пираты?! Вам придется пройти с нами в комендатуру для разбирательства...";
					link.l1 = "Мы вовсе не пираты! Я этого человека даже не знаю! Он только что въехал в эту комнату, а я просто не успел"+ GetSexPhrase("","а") +" ее освободить!";
					link.l1.go = "ContraDeliverQuest_Sold1";
					break;
			}
				
			if(CheckAttribute(PChar, "GenQuest.ContraDeliver.WaitOnRoom") && NPChar.id == "ContraDeliverQuest_Contra_1")
			{
				dialog.text = "Так что ты там говорил"+ GetSexPhrase("","а") +"? Весточку мне долж"+ GetSexPhrase("ен","на") +" передать?! Ну так давай!";
					link.l1 = "Держи...";
					link.l1.go = "ContraDeliverQuest_1";
					DeleteAttribute(PChar, "GenQuest.ContraDeliver.WaitOnRoom");
					DeleteAttribute(PChar, "GenQuest.ContraDeliver.GoToTavern");
					break;
			}
			
			if(CheckAttribute(PChar, "GenQuest.ChurchQuest_2.BanditsInShore") && NPChar.id == "Church_GenQuest2_Bandit_0")
			{
				dialog.text = "Эй вы! Да, вы. Вижу, вы "+ GetSexPhrase("человек","девушка") +" приличн"+ GetSexPhrase("ый","ая") +", не бедн"+ GetSexPhrase("ый","ая") +".";
					link.l1 = "Я бы расценил"+ GetSexPhrase("","а") +" это как комплимент, если бы он прозвучал не от такого проходимца, как ты.";
					link.l1.go = "Church_GenQuest_2_ShoreBandit_1";
					break;
			}
					
			if(CheckAttribute(PChar, "GenQuest.ChurchQuest_2.WayOfShortVariant") && NPChar.id == "Church_GenQuest2_Bandit_0")
			{
				dialog.text = "Стой! Ну-ка, "+ GetSexPhrase("приятель","подруга") +", покажи, не слишком ли тяжёл твой кошель!";
					link.l1 = "А что, церковные денежки уже пристроили?..";
					link.l1.go = "Church_GenQuest_2_1";
					break;
			}
			
			if(NPChar.id == "ReasonToFast_Hunter")
			{
				if(GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) > sti(pchar.questTemp.ReasonToFast.p2))
				{
					dialog.text = "Эй-ик, в лодке! Очисти фарватер, мне с ребятами потолковать нужно...";
					link.l1 = "Эк тебя развезло, приятель. Пойди-ка, проспись.";
					link.l1.go = "ReasonToFast_Hunter1";
				}
				else
				{
					dialog.text = "Эй, кэп! Бросай якорь, приплыли...";
					link.l1 = "А с чего это я долж"+ GetSexPhrase("ен","на") +"....";
					link.l1.go = "ReasonToFast_Hunter2";
				}
				link.l2 = "Ты кому хамишь!?";
				link.l2.go = "ReasonToFast_Hunter3";	
			}
			
			if(NPChar.id == "PirateOnUninhabited_0")
			{
				dialog.text = RandPhraseSimple("Приветствую Вас! Наконец-то Бог услышал наши молитвы и надоумил отважного капитана высадиться на этот берег.",
					"Слава Провидению! Теперь наши гнилые кости не достанутся местным падальщикам!");
				link.l1 = "Здравствуйте, милейший, я капитан " + GetFullName(PChar) + ". Вижу у вас серьёзные неприятности...";
				link.l1.go = "PiratesOnUninhabited_3";
				link.l2 = "Милейший, я прибыл"+ GetSexPhrase("","а") +" сюда по своим делам, и у меня совершенно нет времени решать ваши проблемы.";
				link.l2.go = "PiratesOnUninhabited_1";
			}
			
			if(NPChar.id == "ShipWreck_0")
			{
				dialog.text = RandPhraseSimple("Ах, капитан! Какое счастье, что Бог послал Вам попутный ветер и привёл в это пустынное место!",
					"Капитан! Слава Провидению, что вы решили высадиться на этот берег!");
				link.l1 = "Здравствуйте, милейший, я капитан " + GetFullName(pchar) + ". Вижу у вас серьёзные неприятности.";	
				link.l1.go = "ShipWreck_2";
				link.l2 = "Милейший, я прибыл"+ GetSexPhrase("","а") +" сюда по своим делам и у меня совершенно нет времени решать ваши проблемы.";
				link.l2.go = "ShipWreck_1";
			}
			
			if(NPChar.id == "Convict_0")
			{
				dialog.text = LinkRandPhrase("Постойте, "+ GetAddress_Form(pchar) +"! Не уделите минутку вашего драгоценного внимания?","Не согласится ли благородн"+ GetSexPhrase("ый","ая") +" госпо"+ GetSexPhrase("дин","жа") +" выслушать скромную просьбу своих недостойных собеседников?","Благородн"+ GetSexPhrase("ый","ая") +" госпо"+ GetSexPhrase("дин","жа") +", уделите пару минут вашего драгоценного времени на разговор с обездоленными.");
				link.l1 = LinkRandPhrase("Некогда мне.", "Прочь с дороги, и без вас забот хватает.", "Отвяжитесь. Не до вас.");
				link.l1.go = "Convict_0End";
				link.l2 = LinkRandPhrase("Что надо?", "Чего вы хотите?", "В чём дело?");
				link.l2.go = "Convict_Begin";
			}
			
			// Warship, 15.05.11. Генер "Правосудие на продажу".
			if(HasSubStr(NPChar.id, "JusticeOnSale_Jungle_"))
			{
				dialog.text = "Приветствую, кэп! Не интересуют индейские вещички, и товар, который в магазине не купишь, а? Или может немного наличных?";
					link.l1 = "Обычно оборванцы вроде вас не предлагают, а клянчат! С чего вдруг такая любезность?";
					link.l1.go = "JusticeOnSale_1";
					link.l2 = "С такими, как ты, обычно говорит мой пистолет!";
					link.l2.go = "JusticeOnSale_2";
			}
		break;
		
		// Генератор "Ситуация в трюме -Выкуп"
		case "Hold_GenQuest1":
			pchar.quest.Hold_GenQuest_FindCharTimeIsOver.over = "yes";
			dialog.text = "Слушаю вас, капитан. Вы по делу?";
			link.l1 = "Я разыскиваю некоего господина " + pchar.GenQuest.Hold_GenQuest.Name + "?";
			link.l1.go = "Hold_GenQuest2";
		break;
		
		case "Hold_GenQuest2":
			dialog.text = RandPhraseSimple("Я и есть " + pchar.GenQuest.Hold_GenQuest.Name + ". С кем имею честь, простите?","Вы его нашли. Чем могу служить?");
			link.l1 = "Я капитан " + GetFullName(pchar) + ", у меня к вам дело относительно " + pchar.GenQuest.Hold_GenQuest.CapName + ".";
			link.l1.go = "Hold_GenQuest3";
		break;
		
		case "Hold_GenQuest3":
			sld = characterFromId(pchar.GenQuest.Hold_GenQuest.CapId);
			pchar.GenQuest.Hold_GenQuest.RansomSum = makeint(3 * sti(sld.rank) * (800 + GetCharacterSPECIALSimple(NPChar, SPECIAL_L) * 100) + GetCharacterSkillToOld(sld, "Leadership")*500 + GetCharacterSkillToOld(pchar, "commerce")*500); 
						
			switch(drand(3))
			{
				case 0:
					dialog.text = "А кто это?";
					link.l1 = "Погодите, вы - " + pchar.GenQuest.Hold_GenQuest.Name + ", и вы не знаете кто такой " + pchar.GenQuest.Hold_GenQuest.CapName + "?";
					link.l1.go = "Hold_GenQuest40";
				break;
				case 1:
					dialog.text = "О-о, давненько ничего не было слышно от этого старого плута? Что с ним произошло на этот раз?";
					link.l1 = "На этот раз у него серьёзные неприятности... Он попал в плен и просит вашей помощи.";
					link.l1.go = "Hold_GenQuest50";
				break;
				case 2:
					dialog.text = "Так, слушаю вас внимательно.";
					link.l1 = "Его судно подверглось нападению пиратов, а сам он попал в плен и предложил мне обратиться к вам за выкупом.";
					link.l1.go = "Hold_GenQuest60";
				break;
				case 3:
					dialog.text = "Да, рад слышать о старом приятеле. Как он поживает?";
					link.l1 = "Он в таком тяжёлом положении, что и представить трудно.";
					link.l1.go = "Hold_GenQuest70";
				break;				
			}	
		break;
		
		case "Hold_GenQuest40":
			dialog.text = "Совершенно верно, я - " + pchar.GenQuest.Hold_GenQuest.Name + "! Но почему я должен знать какого-то " + pchar.GenQuest.Hold_GenQuest.CapName + "?!";
			link.l1 = "Извините, наверное произошла ошибка...";
			link.l1.go = "Hold_GenQuest41";
		break;
		
		case "Hold_GenQuest41":
			AddQuestRecord("HoldQuest", "10");
			AddQuestUserData("HoldQuest", "sName", pchar.GenQuest.Hold_GenQuest.CapName);
			pchar.GenQuest.Hold_GenQuest = "prisoner_escaped";
			LAi_CharacterDisableDialog(NPChar);
			NPChar.LifeDay = 0;
			DialogExit();
			AddDialogExitQuestFunction("Hold_GenQuest_PrisonerEscaped");
		break;
		
		case "Hold_GenQuest50":
			dialog.text = "Ого! И чем же я ему помогу? Не освободить ли его перебив всех неприятелей, ха-ха-ха?";
			link.l1 = "Нет, этого не потребуется... Нужно просто передать " + pchar.GenQuest.Hold_GenQuest.RansomSum + " песо в качестве выкупа.";
			link.l1.go = "Hold_GenQuest51";
		break;		
		
		case "Hold_GenQuest51":
			dialog.text = "Вот это бесцеремонность! С какой это стати я должен платить за него выкуп?! Кто он мне, собственно, такой?!";
			link.l1 = "Хм, а мне он сказал, что вы его последняя надежда. И ещё на какой-то должок намекал...";
			link.l1.go = "Hold_GenQuest52";
		break;		
		
		case "Hold_GenQuest52":
			dialog.text = LinkRandPhrase("Ах, каков нахал! Он сам задолжал мне кругленькую сумму! Но это же не повод платить за него ещё и выкуп в надежде, что он вернёт оба долга.",
				"Ну не мерзавец ли?! Мало того, что обчистил меня, когда мы делили бизнес, так ещё хватает совести просить о выкупе!",
				"Вот те раз! С какой стати я буду ради него раскошеливаться?! Мы не так близко знакомы.");
			link.l1 = "Значит так ему и передать, что выкуп платить вы отказываетесь и долга своего не признаёте?";	
			link.l1.go = "Hold_GenQuest53";
		break;
		
		case "Hold_GenQuest53":
			dialog.text = "Господи! Ну какой долг?! Я же всё уже вам объяснил! И вообще, если кроме этой глупой истории у вас больше нет вопросов, то разрешите откланяться.";
			link.l1 = "Ну что ж, к вам вопросов больше нет... Зато появилось множество вопросов к вашему приятелю...";
			link.l1.go = "Hold_GenQuest54";
		break;
		
		case "Hold_GenQuest54":
			AddQuestRecord("HoldQuest", "10");
			AddQuestUserData("HoldQuest", "sName", GetFullName(NPChar));
			pchar.GenQuest.Hold_GenQuest = "prisoner_escaped";
			LAi_CharacterDisableDialog(NPChar);
			NPChar.LifeDay = 0;
			DialogExit();
			AddDialogExitQuestFunction("Hold_GenQuest_PrisonerEscaped");
		break;
		
		case "Hold_GenQuest60":
			dialog.text = "Хм, а вы, значит, и есть т"+ GetSexPhrase("от","а") +", кто его удерживает... Что ж, я с удовольствием ему помогу.";
			link.l1 = "Вот и великолепно. Сумма выкупа составляет " + pchar.GenQuest.Hold_GenQuest.RansomSum + " песо.";
			link.l1.go = "Hold_GenQuest61";
		break;
		
		case "Hold_GenQuest61":
			dialog.text = "Вы меня неправильно поняли: перед вами - член городского совета по надзору за соблюдением хартии.\n" + 
				"Стража!!! Стража! Арестовать "+ GetSexPhrase("этого человека","ее") +" по подозрению в работорговле и разбойном нападении на суда " + NationNameGenitive(sti(pchar.GenQuest.Hold_GenQuest.Nation)) + "!";
			link.l1 = "Ну, 'товарищ', доберусь я до тебя...";
			link.l1.go = "Hold_GenQuest62";
		break;
		
		case "Hold_GenQuest62":
			LAi_SetImmortal(NPChar, false);
			AddQuestRecord("HoldQuest", "10");
			AddQuestUserData("HoldQuest", "sName", GetFullName(NPChar));
			pchar.GenQuest.Hold_GenQuest = "prisoner_escaped";
			LAi_SetWarriorTypeNoGroup(NPChar);
   	        LAi_warrior_DialogEnable(NPChar, false);
            LAi_group_MoveCharacter(NPChar, "TmpEnemy");			
			LAi_group_Attack(NPChar, Pchar);
			LAi_group_SetRelation("TmpEnemy", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_SetCheckFunction("TmpEnemy", "Hold_GenQuest_AfterBattle");
			chrDisableReloadToLocation = true; 
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);  
			AddDialogExitQuest("MainHeroFightModeOn"); 
			AddDialogExitQuestFunction("Hold_GenQuest_PrisonerEscaped");
			DialogExit();
		break;
		
		case "Hold_GenQuest70":
			dialog.text = "Да что вы говорите?! Я могу ему чем-то помочь?";
			link.l1 = "Он попал в плен и просил меня поговорить с вами о выкупе.";
			link.l1.go = "Hold_GenQuest71";
		break;		
		
		case "Hold_GenQuest71":
			dialog.text = "Конечно-конечно. Я сделаю всё, что могу. Где это? о какой сумме идёт речь?";
			link.l1 = "Пираты требуют " + pchar.GenQuest.Hold_GenQuest.RansomSum + " песо. Я долж"+ GetSexPhrase("ен","на") +" доставить деньги в порт, и тогда ваш друг будет свободен.";
			link.l1.go = "Hold_GenQuest72";
		break;
		
		case "Hold_GenQuest72":
			dialog.text = "Вот деньги. К счастью у меня оказалось с собой достаточно.";
			link.l1 = "Да, действительно удачно получилось. Ступайте в порт, скоро вы сможете увидеть своего приятеля.";
			link.l1.go = "Hold_GenQuest73";
		break;
		
		case "Hold_GenQuest73":
			addMoneyToCharacter(pchar, sti(pchar.GenQuest.Hold_GenQuest.RansomSum));
			AddQuestRecord("HoldQuest", "11");
			AddQuestUserData("HoldQuest", "sName", GetFullName(NPChar));
			AddQuestUserData("HoldQuest", "sNameChar", NPChar.Hold_GenQuest.Name);
			AddQuestUserData("HoldQuest", "sSum", pchar.GenQuest.Hold_GenQuest.RansomSum);
			pchar.GenQuest.Hold_GenQuest = "prisoner_ransom";
			LAi_CharacterDisableDialog(NPChar);
			NPChar.LifeDay = 0;
			DialogExit();
			AddDialogExitQuestFunction("Hold_GenQuest_PrisonerEscaped");
		break;				
		// Генератор "Ситуация в трюме -Выкуп"
		
		// Генератор "Ситуация в трюме -Подельник"
		case "Hold_GenQuest80":
			dialog.text = "Здравствуйте, капитан, не имел чести быть представленным. Мне сказали, что вы меня ищете.";
			link.l1 = "Совершенно верно, если вы и есть господин " + pchar.GenQuest.Hold_GenQuest.Name + ". Я капитан " + GetFullName(pchar) + ", хотел"+ GetSexPhrase("","а") +" поговорить по одному делу.";
			link.l1.go = "Hold_GenQuest81";
		break;
		
		case "Hold_GenQuest81":
			dialog.text = "И что это за дело, капитан " + GetFullName(pchar) + "?";
			link.l1 = "Дошли до меня слухи, что вещица у вас есть, от которой вы не прочь избавиться.";
			link.l1.go = "Hold_GenQuest82";
		break;
		
		case "Hold_GenQuest82":
			dialog.text = "На что это вы намекаете?";
			link.l1 = "Не упорствуйте, милейший, мне точно известно и о вашем тёмном прошлом, и о карте самодельной, где место клада " + GetName( NAMETYPE_VIP, pchar.GenQuest.Hold_GenQuest.PirateName, NAME_ACC) + " указано.";
			link.l1.go = "Hold_GenQuest83";
		break;
		
		case "Hold_GenQuest83":
			dialog.text = "Ах ты чёрт! Вот знал же я, что этот подлец " + pchar.GenQuest.Hold_GenQuest.CapName + " рано или поздно всё выболтает! И дёрнуло же меня за язык, предлагать ему это дело!";
			link.l1 = "Ладно, хватит причитать. Я не со злом... Продайте мне эту карту и живите дальше, как жили.";
			link.l1.go = "Hold_GenQuest84";
		break;
		
		case "Hold_GenQuest84":
			dialog.text = "Хм, хорошо бы, если так... А сколько за неё дадите? Ведь, учтите, золота в сундуке было немеряно - четверо его к месту тащили... упокой Господи их души...";
			link.l1 = "Но ведь " + GetName( NAMETYPE_VIP, pchar.GenQuest.Hold_GenQuest.PirateName, NAME_NOM) + " мог своё сокровище уже того... в смысле забрать...";
			link.l1.go = "Hold_GenQuest85";
		break;
		
		case "Hold_GenQuest85":
			dialog.text = "И то ваша правда... Эх, была не была - за " + pchar.GenQuest.Hold_GenQuest.Sum + " песо её отдам. Всё одно сам не решусь покойников тревожить.";
			if(sti(pchar.money) >= sti(pchar.GenQuest.Hold_GenQuest.Sum) && !CheckCharacterItem(pchar,"mapQuest") && !CheckCharacterItem(pchar,"map_full"))
			{
				link.l1 = "Так и быть, по рукам...";
				link.l1.go = "Hold_GenQuest86";
			}	
			link.l2 = "Нет, уважаемый, не стоит ваш клочок бумаги таких денег. Прощайте...";
			link.l2.go = "Hold_GenQuest87";
			pchar.quest.Hold_GenQuest_GetMapTimeIsOver.over = "yes";
		break;
		
		case "Hold_GenQuest86":		
			AddMoneyToCharacter(pchar, -sti(pchar.GenQuest.Hold_GenQuest.Sum));
			GiveItem2Character(pchar, "mapQuest"); 
			rItem = ItemsFromID("mapQuest");
			Hold_GenQuest_GenerateTreasureMap(rItem);
			AddQuestRecord("HoldQuest", "15");
			AddQuestUserData("HoldQuest", "sPirateName", GetName( NAMETYPE_VIP, pchar.GenQuest.Hold_GenQuest.PirateName, NAME_ACC));
			AddQuestUserData("HoldQuest", "sSex", GetSexPhrase("","а"));
			AddQuestUserData("HoldQuest", "sSum", pchar.GenQuest.Hold_GenQuest.Sum);						
			NPChar.LifeDay = 0;
			LAi_CharacterDisableDialog(NPChar);			
			DialogExit();
			AddDialogExitQuest("OpenTheDoors");
		break;	
		
		case "Hold_GenQuest87":
			NPChar.LifeDay = 0;
			LAi_CharacterDisableDialog(NPChar);
			AddQuestRecord("HoldQuest", "16");
			AddQuestUserData("HoldQuest", "sSex", GetSexPhrase("","а"));
			AddQuestUserData("HoldQuest", "sName", pchar.GenQuest.Hold_GenQuest.Name);
			AddQuestUserData("HoldQuest", "sSum", pchar.GenQuest.Hold_GenQuest.Sum);			
			CloseQuestHeader("HoldQuest");
			DeleteAttribute(pchar,"GenQuest.Hold_GenQuest");				
			DialogExit();
			AddDialogExitQuest("OpenTheDoors");
		break;
		// Генератор "Ситуация в трюме -Подельник"
		
		// Генератор "Потерпевшие кораблекрушение"
		case "ShipWreck_1":
			dialog.text = "Возможно ли такое, капитан?! Бог Вам этого не простит.";
			link.l1 = "Это как ему будет угодно.";
			link.l1.go = "exit";
			ChangeCharacterComplexReputation(pchar,"nobility", -1);
			AddDialogExitQuestFunction("ShipWreck_DialogDisable");
		break;
		
		case "ShipWreck_2":
			pchar.GenQuest.ShipWreck.StartShipType = PiratesOnUninhabited_GenerateShipType(); 		
			pchar.GenQuest.ShipWreck.ShipTypeName = GenerateRandomNameToShip(sti(pchar.GenQuest.ShipWreck.Nation));			
			if(rand(1) == 0)
			{// лесник правка окончания типа корабля.
				dialog.text = RandPhraseSimple("Здравствуйте, я " + pchar.GenQuest.ShipWreck.Name + ", капитан " + GetStrSmallRegister(XI_ConvertString(ShipsTypes[sti(pchar.GenQuest.ShipWreck.StartShipType)].Name + "Gen")) + " '" + pchar.GenQuest.ShipWreck.ShipTypeName + "', моё судно разбилось о рифы недалеко от берега. " + 
					"Из всей команды удалось спастись лишь немногим. Нас вынесло приливом на этот безлюдный пляж. Мы голодаем и страдаем от жажды вот уже " + (5 + dRand(7)) + " недель",
					"Здравствуйте, я " + pchar.GenQuest.ShipWreck.Name + ", капитан " + GetStrSmallRegister(XI_ConvertString(ShipsTypes[sti(pchar.GenQuest.ShipWreck.StartShipType)].Name + "Gen")) + " '" + pchar.GenQuest.ShipWreck.ShipTypeName + "'. Наше судно потерпело крушение недалеко отсюда. " + 
					"На его обломках нам удалось добраться до этого берега, но он оказался необитаем. Мы вынуждены были питаться моллюсками и пальмовыми плодами на протяжении " + (5 + dRand(7)) + " недель.");
				link.l1 = RandPhraseSimple("И сколько же вас осталось?", "И скольким из вас посчастливилось выжить?");
				link.l1.go = "ShipWreck_3";
			}
			else
			{			
				pchar.GenQuest.ShipWreck.Mutiny = true;
				pchar.GenQuest.ShipWreck.BadName = GenerateRandomName_Generator(sti(pchar.GenQuest.ShipWreck.Nation), "man");
				pchar.GenQuest.ShipWreck.City = GetQuestNationsCity(sti(pchar.GenQuest.ShipWreck.Nation));
				dialog.text = "Ох, капитан, такие серьёзные, что и  врагу не пожелаешь... Здравствуйте, я " + pchar.GenQuest.ShipWreck.Name + ", капитан и владелец " + GetStrSmallRegister(XI_ConvertString(ShipsTypes[sti(pchar.GenQuest.ShipWreck.StartShipType)].Name + "Gen")) + " '" + pchar.GenQuest.ShipWreck.ShipTypeName + "'. Вернее, бывший капитан и владелец. " + 
					"Этот негодяй " + pchar.GenQuest.ShipWreck.BadName + ", которого я нанял " + LinkRandPhrase(RandPhraseSimple("старшим помощником","судовым врачом"), RandPhraseSimple("штурманом","боцманом"), RandPhraseSimple("коком","старшим плотником")) + " в " + XI_ConvertString("Colony" + pchar.GenQuest.ShipWreck.City + "Dat") + ", подбил команду на бунт. В итоге нас высадили в этом безлюдном месте. Это случилось " + (5 + dRand(7)) + " недель назад.";
				link.l1 = "И что, вся команда примкнула к бунтовщикам?";
				link.l1.go = "ShipWreck_4";			
			}
		break;
		
		case "ShipWreck_3":
			dialog.text = RandPhraseSimple("Из всей команды посчастливилось выжить только " + ShipWreck_GetStringQty(sti(pchar.GenQuest.ShipWreck.Qty)) + ". Остальные погибли… некоторые уже здесь - от ран и лихорадки",
				"Посчастливилось лишь " + ShipWreck_GetStringQty(sti(pchar.GenQuest.ShipWreck.Qty)) + ". Остальные покоятся, кто в морской пучине, кто в песчаных дюнах этого пляжа...");
			link.l1 = LinkRandPhrase("Вам не позавидуешь. Но такова жизнь моряка - любой из нас мог оказаться на вашем месте",
				"Понимаю... Все мы в руках Господа, но у него видимо слишком много забот, чтобы помнить о каждом.",
				"Да уж. Человек предполагает, а Господь располагает...");
			link.l1.go = "ShipWreck_5";	
		break;
		
		case "ShipWreck_4":
			dialog.text = "Нет, конечно! Отказавшихся примкнуть к зачинщикам было достаточно много, но негодяи захватили арсенал, и хорошо ещё, что нам хватило выдержки не оказывать сопротивление. Многие умерли уже здесь от лихорадки и ядовитых насекомых,  выжить посчастливилось лишь " + ShipWreck_GetStringQty(sti(pchar.GenQuest.ShipWreck.Qty)) + ". Но теперь-то уж наши мучения закончились... ";
			link.l1 = RandPhraseSimple("Да уж, попали вы в переделку...","Да уж, чего только не случается в этих Богом забытых краях...");
			link.l1.go = "ShipWreck_5";			
			link.l2 = "Не торопитесь, милейший. А почему я долж"+ GetSexPhrase("ен","на") +" верить, что вас высадили не как зачинщиков бунта?";
			link.l2.go = "ShipWreck_6";			
		break;
		
		case "ShipWreck_5":
			dialog.text = RandPhraseSimple("Капитан, я очень надеюсь, что на вашем корабле найдётся несколько свободных рундуков. Ведь у каждого из нас остались семьи, которые наверняка уже оплакивают нашу гибель. Мы были бы очень Вам благодарны.",
				"Капитан, мы в полном отчаянии, нам больше не на кого надеяться. Не откажите в услуге, вытащите нас из этого забытого Богом места.");
			if(GetFreeCrewQuantity(pchar) >= sti(pchar.GenQuest.ShipWreck.Qty) && GetPassengersQuantity(pchar) < PASSENGERS_MAX)
			{
				link.l1 = "Да уж... и куда прикажете вас доставить?";
				link.l1.go = "ShipWreck_7";			
			}
			link.l2 = RandPhraseSimple(RandPhraseSimple("Увы, мне очень жаль, но на корабле нет ни одного свободного гамака, не говоря уже о каютах. Матросы спят на палубе, не имея возможности восстановить силы после тяжёлой вахты...",
				"Мне бы очень не хотелось вас разочаровывать, но на корабле команда с перегрузом, люди спят под открытым небом. Стоит вспыхнуть болезни, и я потеряю половину экипажа."), 
				RandPhraseSimple("Очень жаль, но кубрики на корабле переполнены. Матросы живут в тесноте, и у меня нет никакой возможности брать ещё и пассажиров.",
				"Вынужден"+ GetSexPhrase("","а") +" вас разочаровать, но на корабле команда с перегрузом. Я опасаюсь вспышки эпидемии."));
			link.l2.go = "ShipWreck_8";	
			if(stf(pchar.reputation.nobility) <= REPUTATION_NEUTRAL)
			{
				link.l3 = "Вам ли, бывалому моряку, не знать, что присутствие на борту потерпевшего кораблекрушение - это дурная примета? Мои матросы просто выбросят всех вас за борт.";
				link.l3.go = "ShipWreck_9";
			}
		break;
		
		case "ShipWreck_6":
			dialog.text = "Что вы, " + GetAddress_Form(npchar) + " " + pchar.lastname + "?! Побойтесь Бога! Я достаточно известный на Карибах негоциант! ...Был известным негоциантом. Теперь уж и не знаю... без судна, без средств...";
			link.l1 = "Как же... Небось бунт на корабле подняли или проворовались. Вот и досталось вам поделом.";
			link.l1.go = "ShipWreck_18";
			if(GetPassengersQuantity(pchar) < PASSENGERS_MAX)
			{
				link.l2 = "Но каков мошенник этот ваш " + pchar.GenQuest.ShipWreck.BadName + "! Неужели вы готовы спустить это ему с рук и вот так запросто смириться со своей участью?";
				link.l2.go = "ShipWreck_19";
			}	
		break;		
		
		case "ShipWreck_7":
			if(rand(1) == 0)
			{
				if(rand(100) < 90)
				{
					pchar.GenQuest.ShipWreck.variant = "1";
					dialog.text = "В любое поселение " + NationNameGenitive(sti(pchar.GenQuest.ShipWreck.Nation)) + ".";
					link.l1 = "Что ж, и рундуков, и гамаков на судне достаточно. Загружайтесь в шлюпку.";
					link.l1.go = "ShipWreck_10";
					link.l2 = "Хм.  Вот незадача... Нам предстоят тяжёлые бои, и ещё неизвестно где вы будете в большей безопасности - у меня на борту или в этой уютной лагуне.";
					link.l2.go = "ShipWreck_11";
				}
				else
				{				
					dialog.text = "В Дюнкерк!.. у меня там мама...";
					link.l1 = "Вы в своём уме?! Наверное, во время крушения Вы сильно стукнулись головой...";
					link.l1.go = "ShipWreck_12";					
					pchar.GenQuest.ShipWreck.Crazy = true; // получите психа на борт :-)
					
				}				
			}
			else
			{
				pchar.GenQuest.ShipWreck.variant = "2";
				dialog.text = "Да всё равно куда! Ведь нам нечем даже с Вами расплатиться...";
				link.l1 = "Что ж, и рундуков, и гамаков на судне достаточно. Загружайтесь в шлюпку.";
				link.l1.go = "ShipWreck_10_1";
				link.l2 = "Хм.  Вот незадача... Нам предстоят тяжёлые бои, и ещё неизвестно где вы будете в большей безопасности - у меня на борту или в этой уютной лагуне.";
				link.l2.go = "ShipWreck_11";		
			}						
		break;		

		case "ShipWreck_8":
			pchar.GenQuest.ShipWreck.FoodQty = sti(pchar.GenQuest.ShipWreck.Qty) * 10 + rand(10);
			pchar.GenQuest.ShipWreck.MedicamentQty = sti(pchar.GenQuest.ShipWreck.Qty) * 5 + rand(10);
			pchar.GenQuest.ShipWreck.AmunitionQty = sti(pchar.GenQuest.ShipWreck.Qty) * 3 + rand(5);
			pchar.GenQuest.ShipWreck.RumQty = sti(pchar.GenQuest.ShipWreck.Qty) * 7 + rand(10);
			if(GetFreeCrewQuantity(pchar) < sti(pchar.GenQuest.ShipWreck.Qty))
			{
				if(GetSquadronGoods(pchar, GOOD_FOOD) < sti(pchar.GenQuest.ShipWreck.FoodQty) || GetSquadronGoods(pchar, GOOD_MEDICAMENT) < sti(pchar.GenQuest.ShipWreck.MedicamentQty))
				{
					dialog.text = "Но своим отказом вы обрекаете нас на верную гибель! Мы намерены прорываться на судно с боем, даже если это будет стоить нам жизни!";
					link.l1 = "О каком бое Вы говорите? В Вас едва остались силы, чтоб держаться на ногах...";
					link.l1.go = "ShipWreck_8_1";
					link.l2 = "Попробуйте...";
					link.l2.go = "ShipWreck_16";
				}
				else
				{
					dialog.text = "Но Вы не можете с нами так поступить! Без вашей помощи нам здесь долго не выжить...";
					if(GetSquadronGoods(pchar, GOOD_WEAPON) < sti(pchar.GenQuest.ShipWreck.AmunitionQty) || GetSquadronGoods(pchar, GOOD_RUM) < sti(pchar.GenQuest.ShipWreck.RumQty))
					{			
						link.l1 = "Единственно, чем я могу вам помочь, это оставить провианта и лекарств, и дать шлюпку. От голода и жажды не умрёте, а морскому делу вас учить не нужно...";
						link.l1.go = "ShipWreck_8_2";
					}
					else
					{
						if(rand(1) == 0)
						{
							link.l1 = "Единственно, чем я могу вам помочь, это оставить провианта и лекарств, и дать шлюпку. От голода и жажды не умрёте, а морскому делу вас учить не нужно...";
							link.l1.go = "ShipWreck_8_2";
						}
						else
						{
							link.l1 = "Я могу оставить вам лекарств, оружия, рому и провианта на месяц. За это время или сам"+ GetSexPhrase("","а") +" вернусь, или пришлю кого-то.";
							link.l1.go = "ShipWreck_8_4";
						}
					}
				}
			}
			else
			{
				if(stf(pchar.reputation.nobility) <= REPUTATION_NEUTRAL) // плохиш
				{
					if(GetSquadronGoods(pchar, GOOD_FOOD) < sti(pchar.GenQuest.ShipWreck.FoodQty) || GetSquadronGoods(pchar, GOOD_MEDICAMENT) < sti(pchar.GenQuest.ShipWreck.MedicamentQty))				
					{
						dialog.text = "Но своим отказом вы обрекаете нас на верную гибель! Мы намерены прорываться на судно с боем, даже если это будет стоить нам жизни!";
						link.l1 = "О каком бое Вы говорите? В Вас едва остались силы, чтоб держаться на ногах...";
						link.l1.go = "ShipWreck_8_1";
						link.l2 = "Попробуйте...";
						link.l2.go = "ShipWreck_16";					
					}
					else
					{
						link.l1 = "Единственно, чем я могу вам помочь, это оставить провианта и лекарств, и дать шлюпку. От голода и жажды не умрёте, а морскому делу вас учить не нужно...";
						link.l1.go = "ShipWreck_8_2";					
					}
				}
				else // кибальчиш
				{
					if(GetSquadronGoods(pchar, GOOD_FOOD) < sti(pchar.GenQuest.ShipWreck.FoodQty) || GetSquadronGoods(pchar, GOOD_MEDICAMENT) < sti(pchar.GenQuest.ShipWreck.MedicamentQty))				
					{
						if(rand(1) == 0)
						{
							dialog.text = "Но своим отказом вы обрекаете нас на верную гибель! Мы намерены прорываться на судно с боем, даже если это будет стоить нам жизни!";
							link.l1 = "О каком бое Вы говорите? В Вас едва остались силы, чтоб держаться на ногах...";
							link.l1.go = "ShipWreck_8_1";
							link.l2 = "Попробуйте...";
							link.l2.go = "ShipWreck_16";						
						}
						else
						{
							dialog.text = "Да как вы смеете так поступать?!.. Вы не только забыли морской устав! Вы растоптали свою честь!";
							link.l1 = "Не тебе судить о моей чести, сморчок!!!";
							link.l1.go = "ShipWreck_16";
						}	
					}
					else
					{
						link.l1 = "Единственно, чем я могу вам помочь, это оставить провианта и лекарств, и дать шлюпку. От голода и жажды не умрёте, а морскому делу вас учить не нужно...";
						link.l1.go = "ShipWreck_8_2";											
					}						
				}
			}			
		break;				
	
		case "ShipWreck_8_1":
			dialog.text = "Вы правы, у нас нет шансов... Что ж, Бог Вам судья. Да воздаст Он каждому по делам его...";
			link.l1 = "Ну, с этим я уж как-нибудь сам" + GetSexPhrase("","а") + " разберусь...";
			link.l1.go = "exit";
			ChangeCharacterComplexReputation(pchar,"nobility", -5);
			AddDialogExitQuestFunction("ShipWreck_DialogDisable");
		break;
	
		case "ShipWreck_8_2":
			dialog.text = "Что ж... Вы не оставляете нам выбора... Будем молиться, чтобы штормы и жажда не унесли наши жизни раньше, чем мы доберёмся до обжитых мест...";
			link.l1 = "Прощайте. Да храни вас Господь...";
			link.l1.go = "ShipWreck_8_3";
		break;
		
		case "ShipWreck_8_3":
			ChangeCharacterComplexReputation(pchar,"nobility", -2);
			AddCharacterExpToSkill(pchar, "Leadership", 25);
			RemoveCharacterGoods(pchar, GOOD_FOOD, sti(pchar.GenQuest.ShipWreck.FoodQty));
			RemoveCharacterGoods(pchar, GOOD_MEDICAMENT, sti(pchar.GenQuest.ShipWreck.MedicamentQty));			
			Log_SetStringToLog("Вы потратили " + pchar.GenQuest.ShipWreck.FoodQty + " единиц провианта.");
			Log_SetStringToLog("Вы потратили " + pchar.GenQuest.ShipWreck.MedicamentQty + " единиц лекарств.");
			DialogExit();
			NextDiag.TempNode = "ShipWreck_8_7";
			NextDiag.CurrentNode = NextDiag.TempNode;			
		break;
	
		case "ShipWreck_8_4":	
			dialog.text = "Похоже, у нас нет выбора... Но умоляю Вас, капитан, возвращайтесь скорее или пришлите экспедиционное судно.";
			link.l1 = "Я что-нибудь придумаю. Ждите...";
			link.l1.go = "ShipWreck_8_5";
		break;
	
		case "ShipWreck_8_5":		
			pchar.quest.ShipWreck_LocationExit.over = "yes";
			AddCharacterExpToSkill(pchar, "Leadership", 50); 
			RemoveCharacterGoods(pchar, GOOD_FOOD, sti(pchar.GenQuest.ShipWreck.FoodQty));
			RemoveCharacterGoods(pchar, GOOD_MEDICAMENT, sti(pchar.GenQuest.ShipWreck.MedicamentQty));			
			RemoveCharacterGoods(pchar, GOOD_WEAPON, sti(pchar.GenQuest.ShipWreck.AmunitionQty));
			RemoveCharacterGoods(pchar, GOOD_RUM, sti(pchar.GenQuest.ShipWreck.RumQty));			
			Log_SetStringToLog("Вы потратили " + pchar.GenQuest.ShipWreck.FoodQty + " единиц провианта.");
			Log_SetStringToLog("Вы потратили " + pchar.GenQuest.ShipWreck.MedicamentQty + " единиц лекарств.");		
			Log_SetStringToLog("Вы потратили " + pchar.GenQuest.ShipWreck.AmunitionQty + " единиц оружия.");
			Log_SetStringToLog("Вы потратили " + pchar.GenQuest.ShipWreck.RumQty + " единиц рома.");	
			ReOpenQuestHeader("ShipWrecked");
			if(CheckAttribute(pchar, "GenQuest.ShipWreck.Mutiny"))
			{
				AddQuestRecord("ShipWrecked", "11");
				AddQuestUserData("ShipWrecked", "sSex", GetSexPhrase("","а"));
				AddQuestUserData("ShipWrecked", "ShoreName", UpperFirst(XI_ConvertString(pchar.location + "Dat")));
				AddQuestUserData("ShipWrecked", "sBadName", pchar.GenQuest.ShipWreck.BadName);			
				AddQuestUserData("ShipWrecked", "sNation", NationNameGenitive(sti(pchar.GenQuest.ShipWreck.Nation)));
			}
			else
			{
				AddQuestRecord("ShipWrecked", "10");
				AddQuestUserData("ShipWrecked", "sSex", GetSexPhrase("","а"));
				AddQuestUserData("ShipWrecked", "ShoreName", UpperFirst(XI_ConvertString(pchar.location + "Dat")));
				AddQuestUserData("ShipWrecked", "sNation", NationNameGenitive(sti(pchar.GenQuest.ShipWreck.Nation)));
			}
			DialogExit();
			NextDiag.TempNode = "ShipWreck_8_6";
			NextDiag.CurrentNode = NextDiag.TempNode;	
			pchar.GenQuest.ShipWreck = "SailorsOnShore";
			SetFunctionTimerCondition("ShipWreck_SaveSailors", 0, 0, 30, false);
			pchar.GenQuest.ShipWreck.Shore = pchar.location;
			SaveCurrentQuestDateParam("GenQuest.ShipWreck");
			SetFunctionLocationCondition("ShipWreck_MeetInShore", pchar.GenQuest.ShipWreck.Shore, true);
		break;
	
		case "ShipWreck_8_6":			
			dialog.text = RandPhraseSimple("Капитан, помните, что надеяться нам больше не на кого...","Чего же Вы медлите? Для нас каждая минута пребывания здесь невыносима...");
			link.l1 = "Сделаю всё, что смогу. Прощайте...";
			link.l1.go = "exit";
			NextDiag.TempNode = "ShipWreck_8_6";		
		break;

		case "ShipWreck_8_7":			
			dialog.text = RandPhraseSimple("Прощайте, капитан... Нам нужно готовиться к отплытию.","Прощайте... и поставьте свечки за спасение наших душ..");
			link.l1 = "Прощайте. Да храни вас Господь...";
			link.l1.go = "exit";
			NextDiag.TempNode = "ShipWreck_8_7";		
		break;
		
		case "ShipWreck_9":
			dialog.text = "Да как вы смеете так поступать?!.. Вы не только забыли морской устав! Вы растоптали свою честь!";
			link.l1 = "Не тебе судить о моей чести, сморчок!!!";
			link.l1.go = "ShipWreck_16";
		break;					
		
		case "ShipWreck_10":
			dialog.text = "Спасибо, капитан! Погрузка не займёт много времени. Как мы все молились, чтобы этот момент наступил скорее...";
			link.l1 = "Ну вот и прекрасно. Скоро ваши лишения закончатся.";
			link.l1.go = "ShipWreck_13";
			pchar.quest.ShipWreck_DeliveToCity.win_condition.l1 = "Nation_City";
			pchar.quest.ShipWreck_DeliveToCity.win_condition.l1.nation = sti(pchar.GenQuest.ShipWreck.Nation);
			pchar.quest.ShipWreck_DeliveToCity.function = "ShipWreck_DeliveToCity";
			ReOpenQuestHeader("ShipWrecked");
			if(CheckAttribute(pchar, "GenQuest.ShipWreck.Mutiny"))
			{
				AddQuestRecord("ShipWrecked", "2");
				AddQuestUserData("ShipWrecked", "ShoreName", UpperFirst(XI_ConvertString(pchar.location + "Dat")));
				AddQuestUserData("ShipWrecked", "count", pchar.GenQuest.ShipWreck.Qty);
				AddQuestUserData("ShipWrecked", "sBadName", pchar.GenQuest.ShipWreck.BadName);
				AddQuestUserData("ShipWrecked", "sNation", NationNameGenitive(sti(pchar.GenQuest.ShipWreck.Nation)));
			}
			else
			{
				AddQuestRecord("ShipWrecked", "1");
				AddQuestUserData("ShipWrecked", "ShoreName", UpperFirst(XI_ConvertString(pchar.location + "Dat")));
				AddQuestUserData("ShipWrecked", "count", pchar.GenQuest.ShipWreck.Qty);
				AddQuestUserData("ShipWrecked", "ShipType", GetStrSmallRegister(XI_ConvertString(ShipsTypes[sti(pchar.GenQuest.ShipWreck.StartShipType)].Name + "Acc")));
				AddQuestUserData("ShipWrecked", "ShipName", pchar.GenQuest.ShipWreck.ShipTypeName);
				AddQuestUserData("ShipWrecked", "sNation", NationNameGenitive(sti(pchar.GenQuest.ShipWreck.Nation)));
			}
			
		break;							

		case "ShipWreck_10_1":
			dialog.text = "Спасибо, капитан! Погрузка не займёт много времени. Как мы все молились, чтобы этот момент наступил скорее...";
			link.l1 = "Ну вот и прекрасно. Скоро ваши лишения закончатся.";
			link.l1.go = "ShipWreck_13";
			pchar.quest.ShipWreck_DeliveToCity.win_condition.l1 = "Location_Type";
			pchar.quest.ShipWreck_DeliveToCity.win_condition.l1.location_type = "town";
			pchar.quest.ShipWreck_DeliveToCity.function = "ShipWreck_DeliveToCity";
			ReOpenQuestHeader("ShipWrecked");
			if(CheckAttribute(pchar,"GenQuest.ShipWreck.Mutiny"))
			{
				AddQuestRecord("ShipWrecked", "4");
				AddQuestUserData("ShipWrecked", "ShoreName", UpperFirst(XI_ConvertString(pchar.location + "Dat")));
				AddQuestUserData("ShipWrecked", "count", pchar.GenQuest.ShipWreck.Qty);
				AddQuestUserData("ShipWrecked", "sBadName", pchar.GenQuest.ShipWreck.BadName);
			}
			else
			{
				AddQuestRecord("ShipWrecked", "3");
				AddQuestUserData("ShipWrecked", "ShoreName", UpperFirst(XI_ConvertString(pchar.location + "Dat")));
				AddQuestUserData("ShipWrecked", "count", pchar.GenQuest.ShipWreck.Qty);
				AddQuestUserData("ShipWrecked", "ShipType", GetStrSmallRegister(XI_ConvertString(ShipsTypes[sti(pchar.GenQuest.ShipWreck.StartShipType)].Name + "Acc")));
				AddQuestUserData("ShipWrecked", "ShipName", pchar.GenQuest.ShipWreck.ShipTypeName);
			}			
		break;							
				
		case "ShipWreck_11":
			dialog.text = "Что Вы!.. Что Вы, капитан! Нам ли бояться смерти?! Мы её уже раз обманули, обманем ещё. Просто не хочется так бездарно расставаться с жизнью. Сгнить вот здесь, вдали от людей и явиться поживой падальщикам...\nМы бы с радостью пошли к вам в команду и в любой схватке служили примером остальным... Только не бросайте нас здесь...";
			link.l1 = "Я вижу, вы готовы пойти на всё, лишь бы убраться отсюда. Но посмотрите на себя: какие из вас матросы?";
			link.l1.go = "ShipWreck_14";
			if(GetFreeCrewQuantity(pchar) >= sti(pchar.GenQuest.ShipWreck.Qty))
			{
				link.l2 = "А это неплохая мысль. Пожалуй, я готов"+ GetSexPhrase("","а") +" вас нанять.";
				link.l2.go = "ShipWreck_15";
			}	
		break;									
		
		case "ShipWreck_12":
			dialog.text = "Нет-нет, я не шучу! Увезите меня из этой Карибской мясорубки... из этого ада! Ведь я богат... я очень богат. У меня столько золота, что Папе Римскому и не снилось... Я осыплю Вас золотом...";
			link.l1 = "Тьфу ты! Что за напасть такая?.. садитесь в шлюпку.";
			link.l1.go = "ShipWreck_13";
			pchar.quest.ShipWreck_DeliveToCity.win_condition.l1 = "Location_Type";
			pchar.quest.ShipWreck_DeliveToCity.win_condition.l1.location_type = "town";
			pchar.quest.ShipWreck_DeliveToCity.function = "ShipWreck_DeliveToCity";			
			ChangeOfficersLoyality("bad_all", 1);
			ReOpenQuestHeader("ShipWrecked");
			AddQuestRecord("ShipWrecked", "5");
			AddQuestUserData("ShipWrecked", "sSex", GetSexPhrase("","а"));
			AddQuestUserData("ShipWrecked", "ShoreName", UpperFirst(XI_ConvertString(pchar.location + "Dat")));
			AddQuestUserData("ShipWrecked", "count", pchar.GenQuest.ShipWreck.Qty);
			AddQuestUserData("ShipWrecked", "ShipType", GetStrSmallRegister(XI_ConvertString(ShipsTypes[sti(pchar.GenQuest.ShipWreck.StartShipType)].Name + "Acc")));
			AddQuestUserData("ShipWrecked", "ShipName", pchar.GenQuest.ShipWreck.ShipTypeName);	
		break;							

		case "ShipWreck_13": // берем пассажирами
			pchar.GenQuest.ShipWreck = "SailorsSaved";			
			if(CheckAttribute(pchar,"GenQuest.ShipWreck.variant"))
			{
				if(pchar.GenQuest.ShipWreck.variant == "1") ChangeCharacterComplexReputation(pchar,"nobility", 1);			
				if(pchar.GenQuest.ShipWreck.variant == "2") ChangeCharacterComplexReputation(pchar,"nobility", 2);			
			}	
			for(i = 0; i < sti(pchar.GenQuest.ShipWreck.Qty); i++)
			{
				rChar = CharacterFromID("ShipWreck_" + i);
				if(i == 0) 
				{
					AddPassenger(pchar, rChar, false);
					SetCharacterRemovable(rChar, false);	
				}
				LAi_SetWarriorTypeNoGroup(rChar);
				rChar.Dialog.currentnode = "ShipWreck_13_again";
			}
			DialogExit();
		break;
		
		case "ShipWreck_13_again":
			dialog.text = LinkRandPhrase("Чего же вы медлите, капитан? Прикажите сниматься с якоря.","Извините, капитан, нам нужно готовиться к отплытию.","Удача, что вы решили здесь высадиться!");
			link.l1 = "Поторопитесь. Судно никого ждать не будет.";
			link.l1.go = "exit";
			NextDiag.TempNode = "ShipWreck_13_again";		
		break;
		
		case "ShipWreck_14":
			dialog.text = "Капитан, нам терять нечего. Смерть уже охотится за нами... Так лучше умереть от клинка в бою, чем от вонючих зубов койота.";
			link.l1 = "Ого! Это вызов?! Так давайте закончим наш спор"+ GetSexPhrase(", как подобает мужчинам","") +"!";
			link.l1.go = "ShipWreck_16";
			AddDialogExitQuest("MainHeroFightModeOn"); 
		break;		
		
		case "ShipWreck_15":
			dialog.text = "Клянусь, капитан, вы не пожалеете! Мы будем лучшими матросами во всём архипелаге.";
			link.l1 = "Вот и отлично! Грузитесь в шлюпку...";
			link.l1.go = "ShipWreck_17";			
		break;				
		
		case "ShipWreck_16":
			ChangeCharacterComplexReputation(pchar,"nobility", -3);
			for(i = 0; i < sti(pchar.GenQuest.ShipWreck.Qty); i++)
			{
				rChar = CharacterFromID("ShipWreck_" + i);
				LAi_SetImmortal(rChar, false);
				if(CheckPassengerInCharacter(pchar, "ShipWreck_" + i)) 
				{
					RemovePassenger(pchar, rChar);
				}
				LAi_SetWarriorType(rChar);
				LAi_group_MoveCharacter(rChar, "ShipWreckGroup");
			}

			LAi_Group_SetRelation("ShipWreckGroup", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_Group_FightGroups("ShipWreckGroup", LAI_GROUP_PLAYER, true);
			if(pchar.GenQuest.ShipWreck == "fight")
			{
				LAi_group_SetCheck("ShipWreckGroup", "OpenTheDoors"); 
				LAi_group_SetCheckFunction("ShipWreckGroup", "ShipWreck_AfterBattle");
			}	
			DialogExit();		
		break;
		
		case "ShipWreck_17": // принимаем в команду
			if(pchar.GenQuest.ShipWreck.variant == "1") ChangeCharacterComplexReputation(pchar,"nobility", 1);			
			if(pchar.GenQuest.ShipWreck.variant == "2") ChangeCharacterComplexReputation(pchar,"nobility", 2);			
			for(i = 0; i < sti(pchar.GenQuest.ShipWreck.Qty); i++)
			{
				rChar = CharacterFromID("ShipWreck_" + i);
				LAi_SetWarriorTypeNoGroup(rChar);
				rChar.LifeDay = 0;			
				rChar.Dialog.currentnode = "ShipWreck_17_again";
			}
			AddCharacterCrew(pchar, sti(pchar.GenQuest.ShipWreck.Qty));
			Log_Info("Ваша команда пополнилась на " + pchar.GenQuest.ShipWreck.Qty + " человек.");
			Achievment_SetStat(pchar, 29, sti(pchar.GenQuest.ShipWreck.Qty));
			pchar.quest.ShipWreck_LocExit.over = "yes"; // Снимаем прерывание на выход из локации			
			DeleteAttribute(pchar, "GenQuest.ShipWreck");			
			AddCharacterExpToSkill(pchar, "Leadership", 50); 			
			DialogExit();
		break;

		case "ShipWreck_17_again":
			dialog.text = LinkRandPhrase("Клянусь, капитан, Вы не пожалеете.", "Вы очень правильно сделали, капитан.", "Капитан, будьте уверены, что Вам повезло не меньше нашего!");
			link.l1 = RandPhraseSimple("Хочется в это верить.", "Поторопитесь. Судно никого ждать не будет.");
			link.l1.go = "exit";
			NextDiag.TempNode = "ShipWreck_17_again";
		break;
		
		case "ShipWreck_18":
			dialog.text = "Капитан, зачем же обижать недоверием честных людей? Ты погляди на эти лица - разве ж они похожи на бунтарей?..";
			link.l1 = "И что же мне с вами прикажете делать?";
			link.l1.go = "ShipWreck_20";
		break;
		
		case "ShipWreck_19":
			dialog.text = "А что я могу сделать?.. по крайней мере сейчас. Я благодарен Богу, что хоть жив остался! Но, если вы поможете мне вернуть корабль и отомстить за унижение, то я готов отдать вам всё содержимое трюма, которое сумеет награбить этот негодяй.";
			link.l1 = "Ну хорошо, считайте, что мы договорились.";
			link.l1.go = "ShipWreck_13";
			ShipWreck_SetCapToMap();
			SetFunctionTimerCondition("prosralisrok", 0, 0, 180, false); // таймер лесник тамймер на поиск корабля 																																   
			ReOpenQuestHeader("ShipWrecked");
			AddQuestRecord("ShipWrecked", "16");
			AddQuestUserData("ShipWrecked", "ShoreName", UpperFirst(XI_ConvertString(pchar.location + "Dat")));
			AddQuestUserData("ShipWrecked", "sName", pchar.GenQuest.ShipWreck.Name);
			AddQuestUserData("ShipWrecked", "count", pchar.GenQuest.ShipWreck.Qty);
			AddQuestUserData("ShipWrecked", "sBadName", pchar.GenQuest.ShipWreck.BadName);
			AddQuestUserData("ShipWrecked", "ShipName", pchar.GenQuest.ShipWreck.ShipTypeName);	
		break;
		
		case "ShipWreck_20":
			dialog.text = "Да уж куда нам приказывать? Воля ваша, хотите в поселение доставьте, хотите в команду возьмите.";
			if(GetFreeCrewQuantity(pchar) >= sti(pchar.GenQuest.ShipWreck.Qty))
			{
				link.l1 = "Хорошо, давайте в команду. Только гляди мне, - не баловать! У меня с этим строго!";
				link.l1.go = "ShipWreck_17";
			}
			link.l2 = "Не повезу я вас никуда. У меня в команде и своих головорезов хватает.";	
			link.l2.go = "ShipWreck_22";
			link.l3 = "Ладно, садитесь в шлюпку, отвезу вас куда-нибудь.";
			link.l3.go = "ShipWreck_10_1";
		break;		
		
		case "ShipWreck_22":
			dialog.text = "Что ж... Вы не оставляете нам выбора... Будем молиться, чтобы Провидение сжалилось над нами и позволило выбраться из этого гибельного места. Глядишь, с Божьей помощью нам всё-таки удастся добраться до обжитой земли...";
			link.l1 = "Прощайте. Да храни вас Господь...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("ShipWreck_DialogDisable");
		break;		
		
		case "ShipWreck_30":
			if(pchar.GenQuest.ShipWreck == "SailorsSaved")
			{
				dialog.text = "Спасибо Вам огромное, капитан " + GetFullName(pchar) + "! Вы для нас сделали столько, что любая благодарность будет недостаточна… И хотя все наши пожитки и ломанного гроша не стоят, разрешите подарить Вам этот амулет. Он может быть очень полезен капитану, часто вступающему в морские бои.";
				link.l1 = "Спасибо за подарок. Вещь действительно очень нужная!.. Прощайте капитан " + pchar.GenQuest.ShipWreck.Name + " и да сопутствует Вам удача в морских походах.";
				link.l1.go = "ShipWreck_47";
			}
			else
			{
				dialog.text = "Капитан, спасибо вам большое. Вы для нас сделали столько, что любое вознаграждение будет меньше благодарности, которую мы испытываем. Не побрезгуйте, возьмите этот скромный подарок в знак нашей признательности.";
				link.l1 = "Право же не стоило... Вам сейчас деньги куда нужнее. Но всё равно приятно. Спасибо и прощайте.";
				link.l1.go = "ShipWreck_31";
			}	
		break;
		
		case "ShipWreck_31":
			//addMoneyToCharacter(pchar, sti(pchar.rank) * 200 + rand(2000));
			AddCharacterExpToSkill(pchar, "Commerce", 50);
			AddCharacterExpToSkill(pchar, "Sailing", 100);
			TakeNItems(pchar, "jewelry2", 15+drand(10));
			AddQuestRecord("ShipWrecked", "6");
			AddQuestUserData("ShipWrecked", "sSex", GetSexPhrase("","а"));
			AddQuestUserData("ShipWrecked", "sName", pchar.GenQuest.ShipWreck.Name);
			AddQuestUserData("ShipWrecked", "sCity", XI_ConvertString("Colony"+ Locations[FindLocation(PChar.location)].townsack + "Acc"));
			CloseQuestHeader("ShipWrecked");
			DialogExit();
			AddDialogExitQuestFunction("ShipWreck_GoOut");
		break;
		
		case "ShipWreck_32":	
			dialog.text = "Капитан, знайте, что на свете есть люди, готовые сделать для вас всё. Жаль, что мне нечем вас отблагодарить. Хотя... вот возьмите этот предмет, я нашёл его в той злополучной бухте. Пусть он принесёт вам удачу.";
			link.l1 = "На моём месте так поступил бы каждый. Всего доброго.";
			link.l1.go = "ShipWreck_33";
		break;
		
		case "ShipWreck_33":
			GiveItem2Character(pchar, pchar.GenQuest.ShipWreck.Prize);
			AddCharacterExpToSkill(pchar, "Fortune", 100);
			AddCharacterExpToSkill(pchar, "Sailing", 100);
			AddQuestRecord("ShipWrecked", "6");
			AddQuestUserData("ShipWrecked", "sSex", GetSexPhrase("","а"));
			AddQuestUserData("ShipWrecked", "sName", pchar.GenQuest.ShipWreck.Name);
			AddQuestUserData("ShipWrecked", "sCity", XI_ConvertString(pchar.location + "Acc"));
			CloseQuestHeader("ShipWrecked");		
			DialogExit();
			AddDialogExitQuestFunction("ShipWreck_GoOut");
		break;
		
		case "ShipWreck_34":
			dialog.text = RandPhraseSimple(RandPhraseSimple("Капитан, это уже Дюнкерк?","Неужели мы в Дюнкерке, капитан?"),RandPhraseSimple("Капитан, это Европа?","Мы так быстро добрались до Европы?"));
			bTemp = !GetCharacterItem(pchar, "map_part1") || !GetCharacterItem(pchar, "map_part2");
			if(rand(100) > 75 && !isDay() && bTemp)
			{
				link.l1 = "Угу...";
				link.l1.go = "ShipWreck_40";
			}
			else
			{
				link.l1 = LinkRandPhrase("Нет ещё...","Какой Дюнкерк, какая Европа? Посмотрите вокруг...","О, Господи!..");
				link.l1.go = "ShipWreck_35";
			}
		break;
		
		case "ShipWreck_35":
			dialog.text = LinkRandPhrase("Но, капитан, Вы мне обещали!","Как вы могли не сдержать слово, капитан?","А когда будет Европа?");
			if(rand(100) < 70)
			{
				link.l1 = "Так. Уважаемый, забирай своих людей и манатки и вали на все четыре стороны. Я не намерен"+ GetSexPhrase("","а") +" с тобой нянчиться вечно!";
				link.l1.go = "ShipWreck_36";
			}
			link.l2 = RandPhraseSimple(LinkRandPhrase("А Вы уверены, что Вам нужно именно в Дюнкерк?","Моё судно не предназначено для трансатлантических переходов.","Капитан, чем Вам не угодили Карибы?"), 
					LinkRandPhrase("Но у меня совершенно другие планы...","Далась вам эта Европа...","Вы только посмотрите, какие здесь мулатки... в Европе таких нет..."));
			link.l2.go = "ShipWreck_37";	
		break;
		
		case "ShipWreck_36":
			pchar.quest.ShipWreck_DeliveToCity.over = "yes";
			pchar.GenQuest.ShipWreck = "fight";
			dialog.text = "Да как Вы можете?.. Да как Вы посмели?! Какое вероломство!.. Сейчас я научу Вас держать слово!";
			link.l1 = "Ну, ты сам напросился...";
			link.l1.go = "ShipWreck_16";
			AddCharacterExpToSkill(pchar, "Sneak", 100);
			AddDialogExitQuest("MainHeroFightModeOn"); 
		break;
		
		case "ShipWreck_37":
			dialog.text = LinkRandPhrase(RandPhraseSimple("Нет! Мне нужен именно Дюнкерк.","Вместо того, чтобы учить меня географии, лучше выполните своё обещание!"), 
				RandPhraseSimple("Я ничего не желаю слышать! Вы обещали доставить меня в Европу!","Нет, капитан, так не пойдёт. Мы идём в Европу."),"Я не намерен прозябать в этой дыре вечно!");
			link.l1 = "Я уже не знаю, кончится ли это когда-нибудь...";
			link.l1.go = "ShipWreck_38";
		break;		
		
		case "ShipWreck_38":
			chrDisableReloadToLocation = false;			
			SetFunctionExitFromLocationCondition("ShipWreck_ExitFromTown", pchar.location, false);				
			if(!CheckAttribute(pchar,"GenQuest.ShipWreck.CrazyRec")) // mitrokosta исправлена блокировка поручения капитана
			{
				pchar.GenQuest.ShipWreck.CrazyRec = true;
				AddQuestRecord("ShipWrecked", "7");
			}
			DialogExit();
		break;
		
		case "ShipWreck_40":
			pchar.quest.ShipWreck_DeliveToCity.over = "yes";
			dialog.text = "Вот! Вот сразу видно порядочного человека!.. Ах Европа! Старушка Европа... И дым отечества... Да-да-да\nДа! Вы выполнили своё обещание, и я, как джентльмен, должен выполнить своё. Здесь половинка карты, вторая половина была у моего компаньона, но он утонул в тот злополучный день, когда мы разбились... Пусть земля ему будет пухом... или вода? Ну, не важно. Полгода назад приятель пригласил меня спонсировать это авантюрное предприятие.";
			link.l1 = "Подождите, так вы не моряк? Капитаном был Ваш приятель?";
			link.l1.go = "ShipWreck_41";
		break;
		
		case "ShipWreck_41":
			dialog.text = "Господи!.. Ну конечно же нет! То есть да - я не моряк. Его смыло за борт гигантской волной, когда он решил править дальше от берега. Тогда я принял командование судном и приказал идти в лагуну... Мы отважно пробирались через рифы, но роковая случайность решила всё! Судно напоролось на обломок скалы, и затонуло...";
			link.l1 = "Это же надо было так бездарно погубить людей...";
			link.l1.go = "ShipWreck_42";
		break;
		
		case "ShipWreck_42":
			dialog.text = "Что Вы говорите?.. Ах да, мы отвлеклись... Послушайте, а это точно Дюнкерк? Подумать только, всего каких-то полгода я здесь не был, а как всё изменилось\nВ общем, вот карта, вернее её половина. Но эта половина самая главная: на ней указано точное место - клад в пещере! Правда, не знаю на каком острове, это было на второй половинке. Но вы-то, как опытн"+ GetSexPhrase("ый","ая") +" моря"+ GetSexPhrase("к","чка") +", наверняка уж определите, что это за остров... Я гарантирую, что в этом кладе несметные сокровища пирата м-э-э...";
			link.l1 = "Спасибо, милейший. Если там нет сокровищ, я не расстроюсь. Прощайте, я очень надеюсь, что мы больше не увидимся...";
			link.l1.go = "ShipWreck_43";
		break;
		
		case "ShipWreck_43":
			sld = CharacterFromID("ShipWreck_0");
			RemovePassenger(pchar, sld);
			AddCharacterExpToSkill(pchar, "Fortune", 200);
			if (!GetCharacterItem(pchar, "map_part1")) 	GiveItem2Character(pchar, "map_part1");
			else 										GiveItem2Character(pchar, "map_part2");
			AddQuestRecord("ShipWrecked", "9");
			AddQuestUserData("ShipWrecked", "sSex", GetSexPhrase("","а"));
			CloseQuestHeader("ShipWrecked");	
			AddSimpleRumourCity(LinkRandPhrase(RandPhraseSimple("Говорят, что какой-то псих на острове объявился. Рассказывает, что потерял документы и пытается наняться капитаном на корабль до Дюнкерка...",
				"Поговаривают, что на острове объявился какой-то маньяк. Украл в лавке заступ и роет яму за городскими воротами..."),
				RandPhraseSimple("Представляете, недавно какой-то заезжий европеец в затасканном костюме пытался прорваться на приём к Губернатору. Кричал, что ему срочно нужно увидеть губернатора Дюнкерка.",
				"Недавно в ратуше был скандал: поймали какого-то бродягу, который утверждал что лично знаком с губернатором Дюнкерка."),
				"Вас недавно какой-то псих искал, говорил, что якобы Вы ему денег должны..."), pchar.location, 5, 3,"");
			DialogExit();
			AddDialogExitQuestFunction("ShipWreck_GoOut");
		break;
		
		case "ShipWreck_44":
			dialog.text = RandPhraseSimple("Капитан, какое счастье, что Вы о нас не забыли! Как мы все молились за Вас!..","Капитан, неужели наше спасение близко? Как мы молились, чтобы это быстрее случилось! Некоторые уже стали отчаиваться...");
			link.l1 = "Приветствую " + pchar.GenQuest.ShipWreck.Name + "! Ну как я мог"+ GetSexPhrase("","ла") +" бросить своих коллег в таком положении?.. Куда же вас доставить?";
			link.l1.go = "ShipWreck_45";
			link.l2 = "Приветствую " + pchar.GenQuest.ShipWreck.Name + "! Боюсь, у меня плохие новости. Обстоятельства изменились, и я не смогу взять вас на борт.";
			link.l2.go = "ShipWreck_9";
		break;
		
		case "ShipWreck_45":
			dialog.text = "Нам всё равно куда идти, лишь бы подальше от этого проклятого места... Разрешите начать погрузку?";
			link.l1 = "Загружайтесь. Скоро ваши лишения закончатся.";
			link.l1.go = "ShipWreck_46";
		break;

		case "ShipWreck_46":
			ChangeCharacterComplexReputation(pchar,"nobility", 4);			
			for(i = 0; i < sti(pchar.GenQuest.ShipWreck.Qty); i++)
			{
				rChar = CharacterFromID("ShipWreck_" + i);
				if(i == 0) 
				{
					AddPassenger(pchar, rChar, false);
					SetCharacterRemovable(rChar, false);	
				}
				LAi_SetWarriorTypeNoGroup(rChar);
				rChar.dialog.currentnode = "ShipWreck_13_again";
			}			
			pchar.quest.ShipWreck_DeliveToCity.win_condition.l1 = "Location_Type";
			pchar.quest.ShipWreck_DeliveToCity.win_condition.l1.location_type = "town";
			pchar.quest.ShipWreck_DeliveToCity.function = "ShipWreck_DeliveToCity";			
			pchar.GenQuest.ShipWreck = "SailorsSaved";
			if(CheckAttribute(pchar,"GenQuest.ShipWreck.Mutiny")) DeleteAttribute(pchar,"GenQuest.ShipWreck.Mutiny"));
			SetFunctionExitFromLocationCondition("ShipWreck_LocationExit", pchar.location, false);				
			DialogExit();			
		break;

		case "ShipWreck_47":
			AddCharacterExpToSkill(pchar, "Fortune", 50);
			AddCharacterExpToSkill(pchar, "Sailing", 100);
			GiveItem2Character(pchar, "indian_10");
			AddQuestRecord("ShipWrecked", "15");
			AddQuestUserData("ShipWrecked", "sSex", GetSexPhrase("","а"));
			AddQuestUserData("ShipWrecked", "sName", pchar.GenQuest.ShipWreck.Name);
			CloseQuestHeader("ShipWrecked");				
			DialogExit();
			AddDialogExitQuestFunction("ShipWreck_GoOut");
		break;
		
		case "ShipWreck_48":
			dialog.text = "Спасибо вам, капитан. Мы уж было отчаялись, но вы снова вернули нас к жизни.";
			link.l1 = "Не стоит благодарности... Прощайте.";
			link.l1.go = "ShipWreck_49";
		break;
		
		case "ShipWreck_49":
			AddQuestRecord("ShipWrecked", "17");
			AddQuestUserData("ShipWrecked", "sSex", GetSexPhrase("","а"));
			CloseQuestHeader("ShipWrecked");								
			DialogExit();
			AddDialogExitQuestFunction("ShipWreck_GoOut");
		break;
		
		case "ShipWreck_50":
			dialog.text = "Какого чёрта тебе нужно?";
			link.l1 = "Я приш"+ GetSexPhrase("ел","ла") +" передать тебе привет от " + pchar.GenQuest.ShipWreck.Name + ". Знаешь такого?";
			link.l1.go = "ShipWreck_51";
		break;
		
		case "ShipWreck_51":
			dialog.text = "Жаль я не удавил эту каналью раньше... Значит пришло время расплачиваться за своё благодушие...";
			link.l1 = "Угу... И это время уже истекло...";
			link.l1.go = "ShipWreck_52";
		break;
		
		case "ShipWreck_52":
			LAi_SetCurHPMax(NPChar);
			LAi_GetCharacterMaxEnergy(NPChar);			
			QuestAboardCabinDialogFree(); // важный метод
			LAi_group_SetRelation(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, true);
			LAi_group_SetCheckFunction(LAI_GROUP_BRDENEMY, "ShipWreck_afterCabinFight");
			DialogExit();	
			AddDialogExitQuest("MainHeroFightModeOn");				
		break;

		case "ShipWreck_53":
			AddCharacterExpToSkill(pchar, "Leadership", 100);
			pchar.quest.ShipWreck_ShipSink.over = "yes";
			dialog.text = "Отличная работа, капитан! Всё как и договаривались, корабль нам - трюм вам.";
			link.l1 = "Да, по рукам. Забирайте и владейте.";
			link.l1.go = "exit";
			NextDiag.TempNode = "ShipWreck_53_again";		
			AddDialogExitQuestFunction("ShipWreck_SetShipNew");
		break;
		
		case "ShipWreck_53_again":
			dialog.text = "Приветствую вас, капитан " + GetFullName(pchar) + ".";
			link.l1 = "Ну, как тебе твой корабль?";
			link.l1.go = "ShipWreck_53_again1";
		break;
		
		case "ShipWreck_53_again1":
			dialog.text = "Хе-х, он стал таким же скрипучим, как и я. Видать уже недолго нам обоим бороздить эти моря..";
			link.l1 = "Ну счастливо...";
			link.l1.go = "exit";
			NextDiag.TempNode = "ShipWreck_53_again";		
		break;
		// Генератор "Потерпевшие кораблекрушение"
		
		// Генератор "Каторжане"
		case "Convict_0End":
			DialogExit();
			pchar.GenQuest.Convict = "close";
			chrDisableReloadToLocation = false;
			ChangeCharacterComplexReputation(pchar,"nobility", -1);
			AddDialogExitQuestFunction("Convict_DialogDisable");
		break;
		
		case "Convict_Begin":					
			switch(sti(pchar.GenQuest.Convict.var))
			{
				case 0:
					dialog.text = "Капитан, помогите раздобыть кораблик - баркас или тартану, нам всё едино. По воле обстоятельств мы вынуждены покинуть это негостеприимное место, а светиться в поселении никак нельзя.";
					link.l1 = "А что ж это за обстоятельства такие?";
					link.l1.go = "Convict_11";
				break;
				case 1:
					dialog.text = "Капитан, не одолжите несколько сотен песо? Мы бы и не просили, но нужда заставила.";
					link.l1 = "Нужда говоришь? Небось ром закончился - вот и вся нужда.";
					link.l1.go = "Convict_12";			
				break;
				case 2:
					pchar.GenQuest.Convict.ToCity = FindColonyWithMayakExceptIsland(GetCharacterCurrentIslandId(pchar));	
					pchar.GenQuest.Convict.Mayak = GetMayakByCityName(pchar.GenQuest.Convict.ToCity);
					dialog.text = "Капитан, не откажите в любезности - подбросьте нашу скромную компанию до маяка " + XI_ConvertString("Colony" + pchar.GenQuest.Convict.ToCity + "Gen") + ".";
					link.l1 = "Что-то не заметно на ваших физиономиях особой скромности.";
					link.l1.go = "Convict_13";								
				break;
			}						
			link.l2 = LinkRandPhrase("Я по пятницам не подаю.","Нет у меня времени на всякую ерунду.","Я не стану помогать невесть кому.");
			link.l2.go = "Convict_14";
			Convict_GetMineType();
			pchar.GenQuest.Convict.ShoreLocation = SelectQuestShoreLocation();
		break;
		
		case "Convict_11":
			dialog.text = "Беглые мы... с " + GetStrSmallRegister(XI_ConvertString("MineType" + pchar.GenQuest.Convict.MineType + "Dat")) + ". Того и гляди, бывший хозяин спохватится - тогда уж петли не миновать...";
			if(GetFreeCrewQuantity(pchar) >= sti(pchar.GenQuest.Convict.ConvictQty))
			{
				link.l1 = "Так вы с парусами управляться умеете?";
				link.l1.go = "Convict_11_1";
			}	
			link.l2 = "А расплачиваться чем собираетесь?";
			link.l2.go = "Convict_11_2";
		break;
		
		case "Convict_12":
			dialog.text = "Не до рому нам нынче. Мы, почитай, неделю, как с " + GetStrSmallRegister(XI_ConvertString("MineType" + pchar.GenQuest.Convict.MineType + "Dat")) + " бежали, теперь вот по джунглям прячемся, с голоду бы не помереть...";
			if(sti(pchar.money) >= 3000)
			{
				link.l1 = "Ну положим, дам я вам денег, а дальше-то что? Так и будете прятаться, пока патруль не нагрянет?";
				link.l1.go = "Convict_12_1";		
				link.l2 = "Хорошо, сколько просите?";
				link.l2.go = "Convict_12_2";
			}	
			link.l3 = "У меня с такими как вы разговор короткий - голову на плаху и приговор к исполнению.";
			link.l3.go = "Convict_12_3";
		break;		
		
		case "Convict_12_1":
			if(drand(1) == 0 && GetFreeCrewQuantity(pchar) >= sti(pchar.GenQuest.Convict.ConvictQty))
			{
				dialog.text = "А что же нам делать прикажете? Мы бы и не прочь матросами наняться, только кто же нас беглых возьмёт?";
				link.l1 = "Я возьму, если с парусом знакомы и от пули бегать не станете.";
				link.l1.go = "Convict_12_1_1";
			}
			else
			{
				dialog.text = "Да мы уже с местными рыбаками договорились. Нам всего три тысячи недостаёт, чтоб убраться отсюда.";
				link.l1 = "Держите свои три тысячи, если это действительно поможет.";
				link.l1.go = "Convict_12_1_2";
			}
			link.l2 = "Ну, не знаю... Это ваши проблемы, решайте их как-нибудь без меня.";
			link.l2.go = "Convict_12_1_End"; // выход из локи с закрытием квеста
		break;
		
		case "Convict_12_1_1":
			pchar.GenQuest.Convict.PirateName = "l" + rand(GetNamesCount(NAMETYPE_NICK) - 1);
			dialog.text = "Возьмите, капитан - не пожалеете! Мы ещё с " + GetName( NAMETYPE_NICK, pchar.GenQuest.Convict.PirateName, NAME_ABL) + " в Адриатике пиратствовали, пока его не вздёрнули, а нас " + pchar.GenQuest.Convict.ConvictQty + " человек сюда не сослали.";
			link.l1 = "Вот и славно. Здесь неподалёку есть одно местечко, " + XI_ConvertString(pchar.GenQuest.Convict.ShoreLocation) + " называется. Ближе к полуночи я вас там подберу. Чай не заблудитесь.";
			link.l1.go = "Convict_11_6";
			pchar.GenQuest.Convict = "ToShore";		
		break;

		case "Convict_12_1_2":
			addMoneyToCharacter(pchar, -3000);
			AddCharacterExpToSkill(pchar, "Leadership", 30);
			AddCharacterExpToSkill(pchar, "Commerce", 60);
			iTmp = drand(3);
			if(iTmp <= 1)
			{
				dialog.text = "Конечно поможет! Сегодня и отчалим, если ветер позволит и рыбаки не подведут. Благодарствуем, капитан, да хранит вас Господь...";
				link.l1 = "И вам удачного избавления.";
				link.l1.go = "exit";
				pchar.GenQuest.Convict = "close";
				AddDialogExitQuestFunction("Convict_DialogDisable");
				AddDialogExitQuest("OpenTheDoors");
			}
			if(iTmp == 2)
			{
				dialog.text = "Вот так удача! мы и не чаяли так быстро денег раздобыть. Разрешите, капитан, от чистого сердца презентовать вам вещицу, что мы у хозяина бывшего стащили. Возможно она и вам принесёт удачу.";
				link.l1 = "Спасибо, хорошая вещица. Удачи вам.";
				link.l1.go = "exit";
				pchar.GenQuest.Convict = "close";
				GiveItem2Character(pchar, pchar.GenQuest.Convict.Item);
				AddDialogExitQuestFunction("Convict_DialogDisable");
				AddDialogExitQuest("OpenTheDoors");
				AddCharacterExpToSkill(pchar, "Fortune", 30);
			}
			if(iTmp == 3)
			{
				pchar.GenQuest.Find_Merchant.lastspeak_date = LastSpeakDate();
				GenerateMerchant();
				makeref(MerPrm, MerchantParam);
				dialog.text = "Вот сразу видно щедрого человека, который не боится расставаться с деньгами, потому что знает, как их нужно добывать!\nПрошлой ночью мы видели, как контрабандисты грузили в лодки груз " + MerPrm.QuestGoodsIdx + ". Было темно, но на борту одной из лодок удалось прочесть название судна - '" + MerPrm.ShipName + "'... Корабль идет под флагом " + MerPrm.nation + ". Думается, это может вам пригодиться, хе-хе.";			
				link.l1 = "Н-да? Может и пригодится... Ну, прощайте, следопыты.";
				link.l1.go = "exit";
				pchar.GenQuest.Convict = "close";
				AddQuestRecord("Convict", "7");
				AddQuestUserData("Convict", "sShipName", MerPrm.ShipName);
				AddQuestUserData("Convict", "sGoodName", MerPrm.QuestGoodsIdx);
				CloseQuestHeader("Convict");
				SetFunctionExitFromLocationCondition("Convict_LocExit", pchar.location, false);
				AddDialogExitQuestFunction("Convict_DialogDisable");			
				AddDialogExitQuest("OpenTheDoors");
				AddCharacterExpToSkill(pchar, "Sneak", 30);
			}
		break;
		
		case "Convict_12_2":
			dialog.text = "Да помилуйте, нам ли условия ставить? Сколько ни дадите - за всё благодарны будем.";
			link.l1 = "300 песо.";
			link.l1.go = "Convict_12_2_1";
			link.l2 = "1000 песо.";
			link.l2.go = "Convict_12_2_2";
			link.l3 = "3000 песо.";
			link.l3.go = "Convict_12_2_3";
		break;
		
		case "Convict_12_2_1":
			addMoneyToCharacter(pchar, -300);
			AddCharacterExpToSkill(pchar, "Leadership", 30);
			AddCharacterExpToSkill(pchar, "Commerce", 20);
			dialog.text = "Благодарствуем, капитан, да хранит вас Господь...";
			link.l1 = "И вам удачи.";
			link.l1.go = "exit";
			pchar.GenQuest.Convict = "close";
			AddDialogExitQuestFunction("Convict_DialogDisable");
			AddDialogExitQuest("OpenTheDoors");
		break;

		case "Convict_12_2_2":
			addMoneyToCharacter(pchar, -1000);
			AddCharacterExpToSkill(pchar, "Leadership", 30);
			AddCharacterExpToSkill(pchar, "Commerce", 40);
			if(drand(1) == 0)
			{
				GiveItem2Character(pchar, pchar.GenQuest.Convict.Item);
				dialog.text = "Вот так удача! мы и не чаяли так быстро денег раздобыть. Разрешите, капитан, от чистого сердца презентовать вам вещицу, что мы у хозяина бывшего стащили. Возможно она и вам принесёт удачу.";
				link.l1 = "Спасибо, хорошая вещица. Удачи вам.";
				AddCharacterExpToSkill(pchar, SKILL_FORTUNE, 20);
			}
			else
			{
				dialog.text = "Благодарствуем, капитан, да хранит вас Господь...";
				link.l1 = "И вам удачи.";
			}
			link.l1.go = "exit";
			pchar.GenQuest.Convict = "close";
			AddDialogExitQuestFunction("Convict_DialogDisable");
			AddDialogExitQuest("OpenTheDoors");
		break;

		case "Convict_12_2_3":
			addMoneyToCharacter(pchar, -3000);
			AddCharacterExpToSkill(pchar, "Leadership", 30);
			AddCharacterExpToSkill(pchar, "Commerce", 60);
			if(drand(1) == 0)
			{
				dialog.text = "Вот так удача! мы и не чаяли так быстро денег раздобыть. Разрешите, капитан, от чистого сердца презентовать вам вещицу, что мы у хозяина бывшего стащили. Возможно она и вам принесёт удачу.";
				link.l1 = "Спасибо, хорошая вещица. Удачи вам.";
				link.l1.go = "exit";
				pchar.GenQuest.Convict = "close";
				GiveItem2Character(pchar, pchar.GenQuest.Convict.Item);
				AddDialogExitQuestFunction("Convict_DialogDisable");
				AddDialogExitQuest("OpenTheDoors");
				AddCharacterExpToSkill(pchar, "Fortune", 30);
			}
			else
			{
				pchar.GenQuest.Find_Merchant.lastspeak_date = LastSpeakDate();
				GenerateMerchant();
				makeref(MerPrm, MerchantParam);
				dialog.text = "Вот сразу видно щедрого человека, который не боится расставаться с деньгами, потому что знает, как их нужно добывать!\nПрошлой ночью мы видели, как контрабандисты грузили в лодки груз " + MerPrm.QuestGoodsIdx + ". Было темно, но на борту одной из лодок удалось прочесть название судна - '" + MerPrm.ShipName + "'... Корабль идет под флагом " + MerPrm.nation + ". Думается, это может вам пригодиться, хе-хе.";
				link.l1 = "Н-да? Может и пригодится... Ну, прощайте, следопыты.";
				link.l1.go = "exit";
				pchar.GenQuest.Convict = "close";
				AddQuestRecord("Convict", "7");
				AddQuestUserData("Convict", "sShipName", MerPrm.ShipName);
				AddQuestUserData("Convict", "sGoodName", MerPrm.QuestGoodsIdx);				
				CloseQuestHeader("Convict");
				SetFunctionExitFromLocationCondition("Convict_LocExit", pchar.location, false);
				AddDialogExitQuestFunction("Convict_DialogDisable");
				AddDialogExitQuest("OpenTheDoors");
				AddCharacterExpToSkill(pchar, "Sneak", 30);
			}			
		break;
		
		case "Convict_12_1_End":
			ChangeCharacterComplexReputation(pchar,"nobility", -2);
			OfficersReaction("bad");	
			pchar.GenQuest.Convict = "close";
			DialogExit();
			AddDialogExitQuestFunction("Convict_DialogDisable");
			AddDialogExitQuest("OpenTheDoors");
		break;
		
		case "Convict_12_3":
			if(drand(1) == 0)
			{
				dialog.text = "Не губи, капитан! Вещица у нас есть достойная - возьми как выкуп, да и отпусти подобру-поздорову...";
				link.l1 = "Давайте свою вещицу и проваливайте, пока целы.";
				link.l1.go = "exit";
				pchar.GenQuest.Convict = "close";
				GiveItem2Character(pchar, pchar.GenQuest.Convict.Item);
				AddDialogExitQuestFunction("Convict_DialogDisable");
				AddDialogExitQuest("OpenTheDoors");
			}
			else
			{
				dialog.text = "Нет у нас выбора - двум смертям не бывать, а одной не миновать. Эх, вздрогнем напоследок!";
				link.l1 = "Это другой разговор! А то ишь - любезничать надумали!";
				link.l1.go = "Convict_Fight";
			}			
		break;
		
		case "Convict_13":
			dialog.text = "Ну, мы конечно не святые, но и ссориться по пустякам нам ни к чему... Беглые мы, нам бы убраться отсюда поскорее.";
			link.l1 = "Есть чем за извоз платить?";
			link.l1.go = "Convict_13_1";		
			link.l2 = "Вот оно что... Не с руки мне репутацию из-за вас марать. Прощайте.";
			link.l2.go = "Convict_11_5";
		break;
		
		case "Convict_11_1":
			pchar.GenQuest.Convict.PirateName = "l" + rand(GetNamesCount(NAMETYPE_NICK) - 1);
			dialog.text = "А как же без этого? Мы и к абордажам привычные. Почитай два года с покойным " + GetName( NAMETYPE_NICK, pchar.GenQuest.Convict.PirateName, NAME_ABL) + " местных купцов в страхе держали, только его потом повесили, а нас - " + pchar.GenQuest.Convict.ConvictQty + " человек в каторгу продали.";
			link.l1 = "А ко мне в команду не желаете? В расчётах я не скуп"+ GetSexPhrase("","а") +", но и спокойной жизни не обещаю.";
			link.l1.go = "Convict_11_3";			
		break;
		
		case "Convict_11_2":
			dialog.text = "Да мы прихватили кое-что с " + GetStrSmallRegister(XI_ConvertString("MineType" + pchar.GenQuest.Convict.MineType + "Dat")) + ", чтоб на первое время не бедствовать, так что заплатим вдвойне. Только расчёт будет на месте. И не вздумайте привести стражу. Мы обид не прощаем...";
			link.l1 = "Ну хорошо, ждите меня " + XI_ConvertString(pchar.GenQuest.Convict.ShoreLocation + "Dat") + ". Ближе к полуночи будет вам кораблик... И не надейтесь меня обмануть!";
			link.l1.go = "Convict_11_4";
			link.l2 = "Нет, господа хорошие, а вдруг я вам кораблик - а вы мне кортик под ребро? Словом - не помощни"+ GetSexPhrase("к","ца") +" я вам в этом деле.";
			link.l2.go = "Convict_11_5";
		break;
		
		case "Convict_11_3":
			dialog.text = "С превеликим удовольствием, госпо"+ GetSexPhrase("дин","жа") +" капитан. Это дело нам знакомо, а в королевский флот для нас дорога заказана - с такими-то рекомендациями, хе-хе.";
			link.l1 = "Вот и славно. Здесь неподалёку есть одно местечко, " + XI_ConvertString(pchar.GenQuest.Convict.ShoreLocation) + " называется. После полуночи я вас там подберу. Чай не заблудитесь.";
			link.l1.go = "Convict_11_6";
		break;
		
		case "Convict_11_4":
			dialog.text = "Но, госпо"+ GetSexPhrase("дин","жа") +" капитан, мы-то рискуем поболее вашего. А вдруг вы решите доложить коменданту?";
			link.l1 = "И то верно... Если не появлюсь к утру - значит сделка отменяется.";
			link.l1.go = "Convict_11_7";			
		break;
		
		case "Convict_11_5":
			if(makeint(pchar.reputation.nobility) < 11 || makeint(pchar.reputation.nobility) > 79) //макс. репутатция 90
			{
				dialog.text = "Эх, капитан, а мы так надеялись...";
				link.l1 = "Ничего. Если деньги есть, то извозчик найдётся. Прощайте.";
				link.l1.go = "exit";
				pchar.GenQuest.Convict = "close";
				ChangeCharacterComplexReputation(pchar,"nobility", -2);
				AddDialogExitQuestFunction("Convict_DialogDisable");
				AddDialogExitQuest("OpenTheDoors");
			}
			else
			{
				dialog.text = "А ты, капитан - хитр"+ GetSexPhrase("ец","юга, как я посмотрю") +". Небось прямиком в комендатуру побежишь. Думаешь, удастся так просто улизнуть?";
				link.l1 = "Да вы, никак, мне помешать решили?! Ну, тогда получайте!";
				link.l1.go = "Convict_Fight";
				pchar.GenQuest.Convict = "fight";
			}	
		break;
		
		case "Convict_11_6":
			pchar.GenQuest.Convict = "ToShore";
			ReOpenQuestHeader("Convict");
			AddQuestRecord("Convict", "1");
			AddQuestUserData("Convict", "sSex", GetSexPhrase("","а"));
			AddQuestUserData("Convict", "sIslandType", XI_ConvertString(GetIslandByCityName(pchar.GenQuest.Convict.city) + "Gen"));
			AddQuestUserData("Convict", "sConvictNum", pchar.GenQuest.Convict.ConvictQty);
			AddQuestUserData("Convict", "sShoreName", XI_ConvertString(pchar.GenQuest.Convict.ShoreLocation + "Dat"));							
			SetFunctionTimerCondition("Convict_SetTimerMeet", 0, 0, 1, false);	
			locations[FindLocation(pchar.GenQuest.Convict.ShoreLocation)].DisableEncounters = true;			
			DialogExit();
			AddDialogExitQuestFunction("Convict_DialogDisable");
			AddDialogExitQuest("OpenTheDoors");
		break;
		
		case "Convict_11_7":
			pchar.GenQuest.Convict = "GetShip";
			ReOpenQuestHeader("Convict");
			AddQuestRecord("Convict", "2");		
			AddQuestUserData("Convict", "sSex", GetSexPhrase("","а"));		
			AddQuestUserData("Convict", "sIslandType", XI_ConvertString(GetIslandByCityName(pchar.GenQuest.Convict.city) + "Gen"));
			AddQuestUserData("Convict", "sShoreName", XI_ConvertString(pchar.GenQuest.Convict.ShoreLocation + "Acc"));					
			SetFunctionTimerCondition("Convict_SetTimerMeet", 0, 0, 1, false);
			locations[FindLocation(pchar.GenQuest.Convict.ShoreLocation)].DisableEncounters = true;			
			DialogExit();		
			AddDialogExitQuestFunction("Convict_DialogDisable");		
			AddDialogExitQuest("OpenTheDoors");
		break;
		
		case "Convict_13_1":
			pchar.GenQuest.Convict.Sum = (sti(pchar.rank)+10)*100+1000;
			dialog.text = "Есть кое-что. Мы у хозяина в сундуках маленько пошарили, правда шуму из-за этого много случилось - пришлось прорываться с боем. Только " + PChar.GenQuest.Convict.ConvictQty + " человек живыми и вырвались.";
			link.l1 = "Учитывая обстоятельства, дешевле, чем по " + FindRussianMoneyString(sti(pchar.GenQuest.Convict.Sum)) + " с носа не повезу.";
			link.l1.go = "Convict_13_2";
			if(GetFreeCrewQuantity(pchar) >= sti(pchar.GenQuest.Convict.ConvictQty) && GetPassengersQuantity(pchar) < PASSENGERS_MAX)
			{
				link.l2 = "А вы, я вижу, не из робкого десятка. В команду ко мне пойдёте?";
				link.l2.go = "Convict_13_3";
			}
		break;
		
		case "Convict_13_2":
			dialog.text = "А разве у нас есть выбор? Вези по " + FindRussianMoneyString(sti(pchar.GenQuest.Convict.Sum)) + "...";
			link.l1 = "Тогда топайте " + XI_ConvertString(pchar.GenQuest.Convict.ShoreLocation + "Acc") + ". После полуночи пришлю за вами шлюпку.";
			link.l1.go = "Convict_13_4";
			pchar.GenQuest.Convict = "ToMayak";
			pchar.GenQuest.Convict.Sum = sti(pchar.GenQuest.Convict.Sum) * sti(pchar.GenQuest.Convict.ConvictQty);
		break;
		
		case "Convict_13_3":
			pchar.GenQuest.Convict.PirateName = "l" + rand(GetNamesCount(NAMETYPE_NICK) - 1);
			dialog.text = "Чего же не пойти? Это дело нам знакомо, мы ещё с " + GetName( NAMETYPE_NICK, pchar.GenQuest.Convict.PirateName, NAME_ABL) + " в " + RandPhraseSimple("Гибралтаре","Ла-Манше") + " промышляли, пока сюда не угодили.";
			link.l1 = "Вот и славно. Здесь неподалёку есть одно местечко, " + XI_ConvertString(pchar.GenQuest.Convict.ShoreLocation) + " называется. Ближе к полуночи я вас там подберу. Чай не заблудитесь. ";
			link.l1.go = "Convict_11_6";
			pchar.GenQuest.Convict = "ToShore";
		break;
		
		case "Convict_13_4":
			ReOpenQuestHeader("Convict");
			AddQuestRecord("Convict", "8");					
			AddQuestUserData("Convict", "sSex", GetSexPhrase("ся","ась"));		
			AddQuestUserData("Convict", "sIslandType", XI_ConvertString(GetIslandByCityName(pchar.GenQuest.Convict.city) + "Gen"));
			AddQuestUserData("Convict", "sConvictNum", pchar.GenQuest.Convict.ConvictQty);
			AddQuestUserData("Convict", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.Convict.ToCity + "Gen"));
			AddQuestUserData("Convict", "sSum", pchar.GenQuest.Convict.Sum);
			AddQuestUserData("Convict", "sShoreName", XI_ConvertString(pchar.GenQuest.Convict.ShoreLocation + "Acc"));			
			SetFunctionTimerCondition("Convict_SetTimerMeet", 0, 0, 1, false);
			locations[FindLocation(pchar.GenQuest.Convict.ShoreLocation)].DisableEncounters = true;			
			DialogExit();
			AddDialogExitQuestFunction("Convict_DialogDisable");
			AddDialogExitQuest("OpenTheDoors");
		break;
				
		case "Convict_14":
			dialog.text = RandPhraseSimple(RandPhraseSimple("Эх, капитан, небось сам"+ GetSexPhrase("","а") +" недавно с пустым кошелем бегал"+ GetSexPhrase("","а") +", а как в карманах зазвенело - нос от простого люда воротишь.","Капитан, негоже так с простыми людьми обходиться. Все под одним Богом ходим."), 
											RandPhraseSimple("Эх-ех, совсем народ душой зачерствел. Живёте, будто вам два века отмерено.","Сразу видно, что недавно из Европы - не понюхали ещё смрада нашей тропической помойки."));
			link.l1 = LinkRandPhrase("Да ты никак совестить меня собрался?! Вот я тебе сейчас язык укорочу!","Да ты мне угрожать вздумал?! Ну, держись!!!","Философ что ли? Сейчас я тебе мозги-то поправлю!");
			link.l1.go = "Convict_Fight";	
			pchar.GenQuest.Convict = "fight";
		break;
		
		case "Convict_Fight":
			LAi_SetPlayerType(pchar);
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);	 
			LAi_LockFightMode(pchar, false); 
			LAi_SetFightMode(pchar, true);
			chrDisableReloadToLocation = true;
			iTemp = sti(PChar.GenQuest.Convict.ConvictQty);
			for(i = 0; i < iTemp; i++)
			{
				rChar = CharacterFromID("Convict_" + i);
				DeleteAttribute(rChar, "City");
				LAi_SetWarriorType(rChar);
				LAi_group_MoveCharacter(rChar, "ConvictGroup");
				LAi_SetImmortal(rChar, false);
			}
			LAi_group_SetRelation("ConvictGroup", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("ConvictGroup", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("ConvictGroup", "OpenTheDoors"); 
			DialogExit();	
			AddDialogExitQuest("MainHeroFightModeOn");		
		break;
		
		case "Convict_15":
			dialog.text = LinkRandPhrase("Ну что, капитан? пригнали кораблик?","Приветствуем вас, капитан. Ну что, дело сделано?","Здравствуйте капитан, а мы уж испереживались. Всё прошло гладко?");
			if(Convict_CheckShipType(SHIP_TARTANE) || Convict_CheckShipType(SHIP_WAR_TARTANE))
			{
				link.l1 = "Да, получите свою скорлупку. И про деньги не забудьте. Я выложил"+ GetSexPhrase("","а") +" за неё " + pchar.GenQuest.Convict.ShipPrice + " монет, так что с вас " + sti(pchar.GenQuest.Convict.ShipPrice) * 2 + ", как и договорились.";
				link.l1.go = "Convict_15_1";
			}	
			link.l2 = "Нет, я передумал"+ GetSexPhrase("","а") +". Поищите себе другого помощника. Счастливо оставаться...";
			link.l2.go = "Convict_15_2";
		break;
		
		case "Convict_15_1":
			switch(sti(pchar.GenQuest.Convict.variant))
			{
				case 1:
					dialog.text = "О чём разговор?! У нас отобрали свободу, но не совесть - получите расчёт и нашу безмерную благодарность. Вы нас очень выручили. Мы рассчитаемся с вами серебряными слитками - вы не против?";
					link.l1 = "Нет, конечно. Удачного вам плавания. Только не попадайтесь в открытом море - там у меня разговор короткий.";
					link.l1.go = "Convict_15_1_1End";
					AddCharacterExpToSkill(pchar, "Leadership", 30);
					AddCharacterExpToSkill(pchar, "Commerce", 30);
					TakeNItems(pchar, "jewelry6", makeint(sti(pchar.GenQuest.Convict.ShipPrice)/50));
				break;
				case 2:
					dialog.text = "Капитан, мы тут подумали, что деньги в этой жизни не главное. И наверняка они нам сейчас нужнее. А есть у нас одна вещица, что мы у бывшего хозяина стащили, возможно она заинтересует вас больше любых денег. Вот взгляните...";
					link.l1 = "Да, вы правы. Вещь действительно интересная. Ну, спасибо, и прощайте.";
					link.l1.go = "Convict_15_1_2End";
					AddCharacterExpToSkill(pchar, "Leadership", 30);
					AddCharacterExpToSkill(pchar, "Fortune", 30);
					GiveItem2Character(pchar, pchar.GenQuest.Convict.Item);
				break;
				case 3:
					pchar.GenQuest.Convict = "FightInShore";
					SetFunctionExitFromLocationCondition("Convict_LocExit", pchar.location, false);				
					dialog.text = "Зачем вам столько денег, капитан? Вы и без того не бедствуете. А нам без этой лодки - верная смерть. Так что не обессудьте. Мы кораблик - того, этого... забираем, короче.";
					link.l1 = "Вот тут вы просчитались. Без лодки вы могли уйти вплавь, а теперь останетесь здесь навсегда.";
					link.l1.go = "Convict_Fight";
					AddCharacterExpToSkill(pchar, "Leadership", 30);
					AddCharacterExpToSkill(pchar, "Sneak", 30);
				break;
			}
		break;
	
		case "Convict_15_1_1End":
			AddQuestRecord("Convict", "4");
			AddQuestUserData("Convict", "sSex", GetSexPhrase("","а"));
			AddQuestUserData("Convict", "sShoreName", XI_ConvertString(pchar.GenQuest.Convict.ShoreLocation + "Acc"));
			CloseQuestHeader("Convict");
			AddDialogExitQuestFunction("Convict_DialogDisable");
			AddDialogExitQuestFunction("Convict_SetConvictToShip");
			AddDialogExitQuest("OpenTheDoors");
			DialogExit();
		break;
	
		case "Convict_15_1_2End":
			AddQuestRecord("Convict", "5");
			AddQuestUserData("Convict", "sSex", GetSexPhrase("","а"));
			AddQuestUserData("Convict", "sShoreName", XI_ConvertString(pchar.GenQuest.Convict.ShoreLocation + "Acc"));
			CloseQuestHeader("Convict");
			AddDialogExitQuestFunction("Convict_DialogDisable");
			AddDialogExitQuestFunction("Convict_SetConvictToShip");
			AddDialogExitQuest("OpenTheDoors");
			DialogExit();
		break;	
	
		case "Convict_15_2":
			AddQuestRecord("Convict", "3");
			AddQuestUserData("Convict", "sSex", GetSexPhrase("","а"));
			CloseQuestHeader("Convict");
			for(i = 0; i < sti(pchar.GenQuest.Convict.ConvictQty); i++)
			{
				sld = CharacterFromID("Convict_" + i);
				sld.LifeDay = 0;
			}	
			ChangeCharacterComplexReputation(pchar,"nobility", -2);	
			LAi_group_Delete("ConvictGroup");
			DeleteAttribute(pchar, "GenQuest.Convict");
			DialogExit();
			AddDialogExitQuestFunction("Convict_DialogDisable");
			AddDialogExitQuest("OpenTheDoors");
		break;
		
		case "Convict_16":
			dialog.text = RandPhraseSimple("Ну что, капитан? можно грузиться?","Наконец-то, а мы уж заволновались - решили, что вы передумали.");
			link.l1 = "У меня изменились планы. Придётся вам искать другого капитана.";
			link.l1.go = "Convict_16_1";
			if(pchar.GenQuest.Convict == "ToMayak")
			{
				link.l2 = "Грузитесь в шлюпку, у меня мало времени.";
				link.l2.go = "Convict_16_2";			
			}			
			if(pchar.GenQuest.Convict == "ToShore" && GetFreeCrewQuantity(pchar) >= sti(pchar.GenQuest.Convict.ConvictQty))
			{
				link.l2 = "Грузитесь в шлюпку, у меня мало времени.";
				link.l2.go = "Convict_16_2";			
			}			
		break;
		
		case "Convict_16_1":
			if(rand(1) == 0)
			{
				dialog.text = "А, чтоб тебя!.. Небось уже и патруль за нами послал"+ GetSexPhrase("","а") +"?! Это тебе даром не пройдет!";
				link.l1 = "Что ты мелешь?! Жить надоело?!";
				link.l1.go = "Convict_Fight";
				pchar.GenQuest.Convict = "ShoreFight";
				SetFunctionExitFromLocationCondition("Convict_LocExit", pchar.location, false);
			}
			else
			{
				dialog.text = "Что ж ты, капитан"+ GetSexPhrase(", как девица красная?","?") +" Семь пятниц на неделе...";
				link.l1 = "Но-но, поговори у меня...";
				link.l1.go = "Convict_16_3";
			}
		break;
		
		case "Convict_16_2":
			if(pchar.GenQuest.Convict == "ToShore")
			{
				AddCharacterExpToSkill(pchar, "Leadership", 30);
				AddCharacterCrew(pchar, sti(pchar.GenQuest.Convict.ConvictQty));
				OfficersReaction("bad");
				pchar.GenQuest.Convict = "close";
				AddQuestRecord("Convict", "10");
				CloseQuestHeader("Convict");				
				SetFunctionExitFromLocationCondition("Convict_LocExit", pchar.location, false);
			}
			if(pchar.GenQuest.Convict == "ToMayak")
			{
				AddQuestRecord("Convict", "10");
				sld = characterFromId("Convict_0");
				AddPassenger(pchar, sld, false);
				SetCharacterRemovable(sld, false); 
				SetFunctionExitFromLocationCondition("Convict_LocExit", pchar.location, false);
				SetFunctionLocationCondition("Convict_OnMayak", pchar.GenQuest.Convict.Mayak, true);
				locations[FindLocation(pchar.GenQuest.Convict.Mayak)].DisableEncounters = true;			
			}
			DialogExit();
			AddDialogExitQuestFunction("Convict_DialogDisable");
			AddDialogExitQuest("OpenTheDoors");
		break;
		
		case "Convict_16_3":
			ChangeCharacterComplexReputation(pchar,"nobility", -2);
			OfficersReaction("bad");
			pchar.GenQuest.Convict = "close";
			AddQuestRecord("Convict", "3");
			AddQuestUserData("Convict", "sSex", GetSexPhrase("","а"));
			CloseQuestHeader("Convict");				
			SetFunctionExitFromLocationCondition("Convict_LocExit", pchar.location, false);
			AddDialogExitQuestFunction("Convict_DialogDisable");			
			DialogExit();
			AddDialogExitQuest("OpenTheDoors");
		break;
						
		case "Convict_17":
			dialog.text = LinkRandPhrase("Вот спасибо, "+ GetSexPhrase("добрый человек","милая девушка") +".","Спасибо тебе, капитан - считай, из петли вытащил"+ GetSexPhrase("","а") +".","Благодарствуем за приятное путешествие.");
			link.l1 = LinkRandPhrase("Всё это хорошо, но я жду расчёта.","Пора бы и расплатиться.","Деньги на бочку, как договаривались.");
			link.l1.go = "Convict_17_1";
		break;
		
		case "Convict_17_1":
			switch(sti(pchar.GenQuest.Convict.variant))
			{
				case 1:
					dialog.text = "Конечно-конечно! Какие могут быть вопросы! Вот, держите оговоренную сумму в золотых слитках и нашу безмерную благодарность.";
					link.l1 = "Удачи и вам... Счастливо оставаться.";
					link.l1.go = "Convict_17_1_1End";
					AddCharacterExpToSkill(pchar, "Sailing", 80);
					AddCharacterExpToSkill(pchar, "Commerce", 80);
					TakeNItems(pchar, "jewelry5", makeint(sti(pchar.GenQuest.Convict.Sum)/200));
					break;
				case 2:
					dialog.text = "Капитан, мы тут подумали, что деньги в этой жизни не главное. И наверняка они нам сейчас нужнее. А есть у нас одна вещица, что мы у бывшего хозяина стащили, возможно она заинтересует вас больше любых денег. Вот взгляните...";
					link.l1 = "Да, вы правы. Вещь действительно интересная. Ну, спасибо, и прощайте.";
					link.l1.go = "Convict_17_1_2End";
					AddCharacterExpToSkill(pchar, "Sailing", 80);
					AddCharacterExpToSkill(pchar, "Fortune", 80);
					GiveItem2Character(pchar, pchar.GenQuest.Convict.Item);
					break;
				case 3:
					dialog.text = "Зачем вам столько денег? Вы и без того не бедствуете. Вы нас выручили - будет случай, и мы вас выручим.";
					link.l1 = "Не будет. Молитесь, канальи, я долгов не прощаю.";
					link.l1.go = "Convict_Fight";
					pchar.GenQuest.Convict = "MayakFight";
					SetFunctionExitFromLocationCondition("Convict_LocExit", pchar.location, false);				
					AddCharacterExpToSkill(pchar, "Sailing", 80);
					AddCharacterExpToSkill(pchar, "Sneak", 80);			
					break;
			}
		break;
		
		
		case "Convict_17_1_1End":
			AddQuestRecord("Convict", "11");
			AddQuestUserData("Convict", "sSex", GetSexPhrase("","а"));
			AddQuestUserData("Convict", "sMayak", XI_ConvertString(pchar.GenQuest.Convict.Mayak + "Abl"));		
			AddQuestUserData("Convict", "sSum", makeint(pchar.GenQuest.Convict.Sum));
			CloseQuestHeader("Convict");
			pchar.GenQuest.Convict = "close";
			SetFunctionExitFromLocationCondition("Convict_LocExit", pchar.location, false);
			DialogExit();
			AddDialogExitQuest("OpenTheDoors");
		break;
		
		case "Convict_17_1_2End":
			AddQuestRecord("Convict", "12");
			AddQuestUserData("Convict", "sSex", GetSexPhrase("","а"));
			AddQuestUserData("Convict", "sMayak", XI_ConvertString(pchar.GenQuest.Convict.Mayak + "Abl"));		
			CloseQuestHeader("Convict");
			pchar.GenQuest.Convict = "close";
			SetFunctionExitFromLocationCondition("Convict_LocExit", pchar.location, false);
			DialogExit();
			AddDialogExitQuest("OpenTheDoors");
		break;		
		// <-- Генератор "Каторжане"
		
		// Генератор "Повод для спешки" -->
		// Встреча с ОЗГ на берегу
		case "ReasonToFast_Hunter1":
			dialog.text = "Да меня сюда сам "  + GetName( NAMETYPE_MAIN, pchar.questTemp.ReasonToFast.p3, NAME_NOM) + " прислал...";
			link.l1 = GetName( NAMETYPE_MAIN, pchar.questTemp.ReasonToFast.p3, NAME_NOM) + " тебя уже часа два, как с ответом дожидается. Вот, меня следом послал.";
			link.l1.go = "ReasonToFast_Hunter4";
		break;
		
		case "ReasonToFast_Hunter2":
			dialog.text = "Я давно за тобой в кильватере иду, только больно ты резв"+ GetSexPhrase("ый","ая") +".";
			link.l1 = "И что с того?";
			link.l1.go = "ReasonToFast_Hunter6";		
		break;
		
		case "ReasonToFast_Hunter3":
			dialog.text = "Ответь-ка лучше, много ли губернатор своим шестёркам платит?";
			link.l1 = "Вот черт!...";
			link.l1.go = "ReasonToFast_Fight";		
		break;
		
		case "ReasonToFast_Hunter4":
			dialog.text = "Да не пил я совсем - боцмана искал...";
			link.l1 = "Иди-иди... Я скажу "  + GetName( NAMETYPE_MAIN, pchar.questTemp.ReasonToFast.p3, NAME_DAT) + ", что ты в джунглях заплутал.";
			link.l1.go = "ReasonToFast_Hunter5";		
			AddQuestRecord("ReasonToFast", "5");
			AddQuestUserData("ReasonToFast", "sName", GetName( NAMETYPE_MAIN, pchar.questTemp.ReasonToFast.p3, NAME_GEN));
		break;
		
		case "ReasonToFast_Hunter5":
			LAi_SetPlayerType(pchar);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			AddDialogExitQuest("ReasonToFast_HunterGoOut");
		break;
		
		case "ReasonToFast_Hunter6":
			pchar.questTemp.ReasonToFast = "MeetHunterFail";
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			AddDialogExitQuest("ReasonToFast_PatrolAngry");
		break;
		
		case "ReasonToFast_Fight":
			LAi_SetPlayerType(pchar);
			pchar.questTemp.ReasonToFast = "PatrolAngry";
			pchar.questTemp.ReasonToFast.relation = GetNationRelation2MainCharacter(sti(pchar.questTemp.ReasonToFast.GuardNation));
			SetNationRelation2MainCharacter(sti(pchar.questTemp.ReasonToFast.GuardNation), RELATION_ENEMY); 
			pchar.GenQuest.HunterScore2Pause = 1; //НЗГ не начисляются
			pchar.GenQuest.ReputationNotChange = 1; //репутацию не менять
			sTemp = "Patrol" + pchar.questTemp.ReasonToFast.LocIdx + "_";
			sGroup = "PatrolGroup_" + pchar.questTemp.ReasonToFast.LocIdx;
			LAi_LocationFightDisable(&locations[FindLocation(pchar.questTemp.ReasonToFast.PatrolLocation)], false);	
			iTemp = sti(pchar.questTemp.ReasonToFast.PatrolNum);
			chrDisableReloadToLocation = true;
			rChar = CharacterFromID("ReasonToFast_Hunter");
			LAi_SetWarriorType(rChar);
			LAi_group_MoveCharacter(rChar, sGroup);
			for(i = 0; i < iTemp; i++)
			{
				rChar = CharacterFromID(sTemp + i);
				LAi_SetWarriorType(rChar);
				LAi_group_MoveCharacter(rChar, sGroup);
			}			
			LAi_group_SetRelation(sGroup, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups(sGroup, LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck(sGroup, "OpenTheDoors"); 
			LAi_group_SetCheck(sGroup, "ReasonToFast_PatrolDied");
			DialogExit();	
			AddDialogExitQuest("MainHeroFightModeOn");		
		break;
		
		// бой с кэпом пиратского корабля
		case "ReasonToFast_FightCap": 
			dialog.text = "А ты оказал"+ GetSexPhrase("ся шустрым малым","ась шустрой малой") +". Моли Бога, чтоб о твоих проделках не дознался " + GetName( NAMETYPE_MAIN, pchar.questTemp.ReasonToFast.p3, NAME_NOM) + ".";
			link.l1 = "Не дознается, если ты ему не расскажешь... А ты этого не сделаешь, правда?";
			link.l1.go = "ReasonToFast_FightCap_1";
		break;
		
		case "ReasonToFast_FightCap_1":
			dialog.text = "От чего же?! Я это сделаю с большим удовольствием!";
			link.l1 = "Он тебя всё равно повесит. За глупость, которую вы допустили. Так что не теряй времени, и я помогу тебе избавиться от виселицы.";
			link.l1.go = "ReasonToFast_FightCap_2";
		break;
		
		case "ReasonToFast_FightCap_2":
			dialog.text = "Хм... Каким образом?";
			link.l1 = "Я прикончу тебя сам"+ GetSexPhrase("","а") +"...";
			link.l1.go = "ReasonToFast_FightCap_Last";
		break;
		
		case "ReasonToFast_FightCap_Last":
			LAi_SetCurHPMax(NPChar);
			LAi_GetCharacterMaxEnergy(NPChar);
			QuestAboardCabinDialogExitWithBattle(""); 
			DialogExit();	
			AddDialogExitQuest("MainHeroFightModeOn");		
		break;		
		
		// встреча с лакеем в резиденции
		case "ReasonToFast_Lakey":
			dialog.text = "Вы по делу, "+ GetSexPhrase("месье","мадемуазель") +"?";
			link.l1 = "Нет, я по приглашению очаровательной супруги губернатора, осматриваю эту поистине роскошную резиденцию.";
			link.l1.go = "ReasonToFast_Lakey1";
			link.l2 = "Я принес"+ GetSexPhrase("","ла") +" весточку от известных тебе людей.";
			link.l2.go = "ReasonToFast_Lakey2";
			link.l3 = "Да. Хочу передать тебя в руки правосудия!";
			link.l3.go = "ReasonToFast_Lakey3";
			pchar.questTemp.ReasonToFast = "MeetLakey";
			pchar.questTemp.ReasonToFast.SpeakOther = true;			
		break;
		
		case "ReasonToFast_Lakey1":
			NextDiag.TempNode = "ReasonToFast_Lakey11";
			dialog.text = "О да, мне повезло служить в таком шикарном доме.";
			link.l1 = "Неудивительно...";
			link.l1.go = "ReasonToFast_Lakey11";
		break;

		case "ReasonToFast_Lakey11":
			NextDiag.TempNode = "ReasonToFast_Lakey11";
			dialog.text = "Не забудьте взглянуть на наш сад!";
			link.l1 = "Спасибо, милейший!";
			link.l1.go = "exit";			
			bDisableFastReload = false;
		break;
		
		case "ReasonToFast_Lakey2":
			dialog.text = "Эээ... " + pchar.questTemp.ReasonToFast.password + "?";
			link.l1.edit = 1;			
			link.l1 = ""; 
			link.l1.go = "ReasonToFast_Lakey21";
		break;

		case "ReasonToFast_Lakey3":
			dialog.text = "Тебе это не удастся, иуда!";
			link.l1 = "Стой, мерзавец!!!";
			link.l1.go = "ReasonToFast_Lakey_exit";
			pchar.questTemp.ReasonToFast = "LakeyExitFail";
			bDisableFastReload = false;			
		break;

		case "ReasonToFast_Lakey21":
			if(GetStrSmallRegister(pchar.questTemp.ReasonToFast.ShipName) == GetStrSmallRegister(dialogEditStrings[1]))
			{
				dialog.text = "Скорее, забирайте ценности, и уходите!";
				link.l1 = "Я думаю, тебе тоже пора уносить ноги.";
				link.l1.go = "ReasonToFast_Lakey_exit";
				TakeNItems(pchar,"icollection", sti(pchar.questTemp.ReasonToFast.p8));
				TakeNItems(pchar,"Chest", sti(pchar.questTemp.ReasonToFast.p7));
				pchar.questTemp.ReasonToFast = "LakeyExitSuccess";					
				bDisableFastReload = true;		
				//chrDisableReloadToLocation = true;			
			}
			else
			{
				dialog.text = "М-м, извините, мне нужно срочно удалиться.";
				link.l1 = "Стой, мерзавец!!!";
				link.l1.go = "ReasonToFast_Lakey_exit";
				pchar.questTemp.ReasonToFast = "LakeyExitFail";
				bDisableFastReload = false;
			}			 
		break;

		case "ReasonToFast_Lakey_exit":
			DialogExit();	
			DeleteAttribute(pchar, "GenQuest.CannotWait");
			pchar.quest.ReasonToFast_ClearLakey.over = "yes"; //снимаем таймер
			ReasonToFast_SetHunterCoastal();
			AddDialogExitQuest("ReasonToFast_LakeyGoOut");
		break;		
		
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("Да ты "+ GetSexPhrase("вор, милейший! Стража, держи его","воровка! Стража, держи ее") +"!!!", "Вот это да! Чуть я загляделся, а ты сразу в сундук с головой! Держи "+ GetSexPhrase("вора","воровку") +"!!!", "Стража! Грабят!!! Держи "+ GetSexPhrase("вора","воровку") +"!!!");
			link.l1 = "А-ать, дьявол!!!";
			link.l1.go = "ReasonToFast_Lakey_exit";
			pchar.questTemp.ReasonToFast = "LakeyExitFail";
			bDisableFastReload = false;
		break; 
		// Генератор "Повод для спешки" <--
		
		// ситуации с капитаном захваченного корабля
		// взрыв на корабле
		case "ShipSituation11": // пираты или ДУ
			dialog.text = RandPhraseSimple("Привет, "+ GetSexPhrase("приятель","подруга") +"! Я приготовил тебе сюрприз - поджёг шнур, ведущий в крюйт-камеру. Сейчас такой взрыв будет, что черти в аду услышат!","Чего стоишь?! В крюйт-камере пожар! Сейчас такой фейерверк будет - в Европе увидят!");
			link.l1 = RandPhraseSimple("Ах ты, каналья! Тебе меня не провести. Дерись, трус!","Вижу, крысы бегут с корабля, а ты в первых рядах?!");
			link.l1.go = "ShipSituation12";
		break;
		
		case "ShipSituation12":
			dialog.text = RandPhraseSimple("Беги и ты, если жить хочешь... Ладно, некогда мне - шлюпка ждёт. А тебе удачной рыбалки!","Некогда мне в благородство играть - ребята в шлюпке ждать не будут. Удачной тебе рыбалки, победитель"+ GetSexPhrase("","ница") +"!");
			link.l1 = RandPhraseSimple("Ах ты чёрт!!!.. Руби кранцы!!! Уходим!","Это же надо так вляпаться!.. Открыть кингстоны! Отваливаем!");
			link.l1.go = "ShipSituation_End";
		break;
		
		case "ShipSituation21": // военный корабль (не флагман)
			dialog.text = "Что?! Думаешь, выиграл"+ GetSexPhrase("","а") +" поединок?! Рано радуешься. Я поджёг шнур, ведущий в крюйт-камеру - так что жив" +GetSexPhrase("ым","ой") + " тебе с этого корабля не уйти.";
			link.l1 = RandPhraseSimple("Ах ты, каналья! Тебе меня не провести. Дерись, трус!","Вижу, крысы бегут с корабля, а ты в первых рядах?!");
			link.l1.go = "ShipSituation22";
		break;
		
		case "ShipSituation22":
			dialog.text = RandPhraseSimple("Я выполняю присягу, но это не обязывает меня так бездарно умирать. Извини, место в шлюпке не предлагаю, боюсь - матросы не поймут.","Корабли надёжно свалились в абордаже, так что твоя участь решена. Извини, шлюпка ждёт...");
			link.l1 = RandPhraseSimple("Ах ты чёрт!!!.. Руби кранцы!!! Уходим!","Это же надо так вляпаться!.. Открыть кингстоны! Отваливаем!");
			link.l1.go = "ShipSituation_End";
		break;
		
		case "ShipSituation31": // ОЗГ
			dialog.text = RandPhraseSimple("Ну что, победитель"+ GetSexPhrase("","ница") +"?! Добро пожаловать в преисподнюю! Я поджёг шнур, ведущий в крюйт-камеру.","Вот ты, голуб"+ GetSexPhrase("чик","ушка") +", и попал"+ GetSexPhrase("ся","ась") +"! Теперь уже тебе не вывернуться - я поджёг крюйт-камеру.");
			link.l1 = RandPhraseSimple("Ах ты, каналья! Тебе меня не провести. Дерись, трус!","Вижу, крысы бегут с корабля, а ты в первых рядах?!");
			link.l1.go = "ShipSituation32";
		break;
		
		case "ShipSituation32":
			dialog.text = RandPhraseSimple("Я давно тебя выслеживал. Жаль, кораблём жертвовать пришлось. Да ничего, за твою голову дают столько, что пару новых куплю. Удачной рыбалки!","Видишь как приходится тебя убирать? С фейерверками, как индийск"+ GetSexPhrase("ого","ую") +" принц"+ GetSexPhrase("а","ессу") +". Ну, да ладно, я не в накладе. Твоя голова стоит дороже моего кораблика. Прощай, шлюпка ждать не будет...");
			link.l1 = RandPhraseSimple("Ах ты чёрт!!!.. Руби кранцы!!! Уходим!","Это же надо так вляпаться!.. Открыть кингстоны! Отваливаем!");
			link.l1.go = "ShipSituation_End";			
		break;
		
		case "ShipSituation_End":
			AddCharacterExpToSkill(pchar, "Sneak", 200);
			DialogExit();
			LAi_SetActorType(NPChar); 
			LAi_ActorRunToLocation(NPChar, "reload", "reload1", "none", "", "", "", -1);
			NPChar.LifeDay = 0;
			LAi_LockFightMode(pchar, false);	
			Log_Info(XI_ConvertString("Ship can explode"));
			pchar.GenQuest.ShipSituation.Explosion = ShipSituation_4;	
			pchar.GenQuest.ShipSituation.Explosion.CapId = NPChar.CaptanId;
			LAi_EnableReload();
			Log_SetActiveAction("Reload");
		break;
		
		// эпидемия
		case "ShipEpidemy1":
			AddCharacterExpToSkill(pchar, "Fortune", 200);
			dialog.text = RandPhraseSimple("Стой, капитан! Хочу сказать тебе пару слов.","Подожди, капитан! Думаю, тебе интересно будет это узнать.");
			link.l1 = LinkRandPhrase("Что за беседы во время боя?!","О чём я долж"+ GetSexPhrase("ен","на") +" говорить с покойником?","В чём дело?! Хочешь завещание на моё имя оставить?");
			link.l1.go = "ShipEpidemy2";
		break;
		
		case "ShipEpidemy2":
			dialog.text = "На борту эпидемия. Я ещё во время плавания потерял четверть команды. Так что все вы обречены...";
			link.l1 = RandPhraseSimple("Ах ты, гнилой мешок! Почему не подняли сигнал, что на корабле бедствие?!","Что же ты морской устав забыл? На мачте должен быть сигнал, что на корабле бедствие!");
			link.l1.go = "ShipEpidemy3";
		break;
		
		case "ShipEpidemy3":
			dialog.text = "А нам всё одно помирать было. Поэтому и сдаваться не стали, чтоб тебя и твоих прихвостней на тот свет забрать!.. Вот теперь я удовлетворён. Можешь заканчивать своё грязное дело.";
			link.l1 = RandPhraseSimple("Ну, ты мне за это ответишь!..","Я тоже удовлетворен"+ GetSexPhrase("","а") +", что ты подохнешь раньше. И я это увижу...");
			link.l1.go = "ShipEpidemy31";
			link.l2 = RandPhraseSimple("Не стану я клинок пачкать о твою поганую кровь - живи... хотя зачем тебе это? Я увожу команду с этого гнилого корыта.","За такое полагается виселица, но тебе она уже не понадобится. Я увожу людей... Доживай, сколько тебе осталось.");
			link.l2.go = "ShipEpidemy32";
			pchar.GenQuest.ShipSituation.Epidemy.CapId = NPChar.CaptanId;
			pchar.GenQuest.ShipSituation.Epidemy = ShipSituation_4;
		break;
		
		case "ShipEpidemy31":
			pchar.GenQuest.QuestAboardCabinDialogIdx = NPChar.index;
			pchar.GenQuest.ShipSituation.Epidemy.CapState = "Died"; // вражеский кэп на волосок от смерти от переизбытка стали и свинца в организме
			LAi_LockFightMode(pchar, false);
			QuestAboardCabinDialogExitWithBattle(""); 
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "ShipEpidemy32":
			DialogExit();
			LAi_SetActorType(NPChar); 
			LAi_ActorGoToLocation(NPChar, "reload", "reload1", "none", "", "", "", -1);
			LAi_LockFightMode(pchar, false);	
			pchar.GenQuest.ShipSituation.Epidemy.CapState = "Live"; // вражеский кэп остался в живых
			LAi_EnableReload();
			Log_SetActiveAction("Reload");
		break;
		// ситуации с капитаном захваченного корабля
		
		// Генератор "Девица в джунглях"
		case "EncGirl_Lover":
			dialog.text = "Здравствуйте, капитан, мне сказали, что вы меня ищете.";
			link.l1 = "Тебя, если ты и есть " + pchar.GenQuest.EncGirl.sLoverId + ".";
			link.l1.go = "EncGirl_Lover1";
		break;
		
		case "EncGirl_Lover1":
			dialog.text = "Да, это я. У вас что-то важное?";
			link.l1 = "Не знаю, насколько это важно для тебя, но я привел"+ GetSexPhrase("","а") +" молодую особу по имени " + pchar.GenQuest.EncGirl.name +". Она сбежала из дому и сейчас ждёт тебя недалеко от таверны."; // belamour
			link.l1.go = "EncGirl_Lover2";
		break;
		
		case "EncGirl_Lover2":
			dialog.text = "Господи, я знал, что всё этим и закончится... А почему она сбежала, не говорила?";
			link.l1 = "Её замуж выдают, за сына ростовщика.";
			link.l1.go = "EncGirl_Lover3";
		break;
		
		case "EncGirl_Lover3":
			pchar.GenQuest.EncGirl.LoverCity = GetQuestNationsCity(sti(pchar.GenQuest.EncGirl.nation));
			pchar.GenQuest.EncGirl.LoverIsland = GetIslandByCityName(pchar.GenQuest.EncGirl.LoverCity);
			dialog.text = "Ну, нет, этого допустить нельзя! Капитан, я в таком дурацком положении... в общем, хочу просить отвезти нас на " + XI_ConvertString(pchar.GenQuest.EncGirl.LoverIsland + "Acc") + " в поселение " + XI_ConvertString("Colony" + pchar.GenQuest.EncGirl.LoverCity) + ", но у меня сейчас совершенно нет денег - я так и не нашёл работу. А в поселении " + XI_ConvertString("Colony" + pchar.GenQuest.EncGirl.LoverCity) + " у меня состоятельные родители и виды на службу...\nУверяю вас, родители будут рады видеть меня с молодой невестой и щедро вас отблагодарят. Ну как, берётесь?";
			link.l1 = "...Послушай, у меня сейчас совсем другие планы. Могу посоветовать тебе наняться матросом на любое судно, а вместо жалования снять своей невесте каюту. Люди из Европы так переезжают, а до твоего поселения - баклан за ночь долетит.";
			link.l1.go = "EncGirl_Lover4";
			link.l2 = "Эх, молодость! Ты, хоть понимаешь, о чём просишь? Увезти дочь от родителей без благословения?.. Берусь конечно!";
			link.l2.go = "EncGirl_Lover5";
		break;
		
		case "EncGirl_Lover4":
			npchar.lifeDay = 0;
			AddDialogExitQuestFunction("EncGirl_LoverExit");	
			DialogExit();
		break;
		
		case "EncGirl_Lover5":
			AddDialogExitQuestFunction("EncGirl_ToLoverParents");	
			DialogExit();
		break;
		
		case "EncGirl_Lover6":
			AddSimpleRumourCityTip(RandPhraseSimple("Вы слышали, " + pchar.GenQuest.EncGirl.name + " сбежала с любовником из-под венца. Не захотела свою жизнь с инвалидом связывать. А во всём виноваты её родители - прельстились на деньги жениха, незачем было такую красавицу за урода сватать.",  
				"Слыхали? " + pchar.GenQuest.EncGirl.name + " оставила с носом и своего папашу и новоиспечённого жениха. Говорят, что один благородный капитан помог ей с любовником бежать на другой остров, где живут родители её возлюбленного... Эх, есть ведь люди, которые ещё не забыли что такое страсть!"), pchar.GenQuest.EncGirl.LoverCity, 3, 2, "citizen,habitue", "");
			dialog.text = "Спасибо вам, капитан. Мы до конца жизни не забудем этой услуги.";
			link.l1 = "Не стоит благодарности. Главное, чтоб у вас теперь всё удачно сложилось.";
			link.l1.go = "EncGirl_Lover7";
		break;
		
		case "EncGirl_Lover7":
			switch (rand(4))
			{
				case 0:
					sTemp = "в магазин";
					pchar.GenQuest.EncGirl.LoverFather = "store_keeper";
				break;
				case 1:
					sTemp = "на верфь";					
					pchar.GenQuest.EncGirl.LoverFather = "shipyard_keeper";
				break;
				case 2:
					sTemp = "в портовое управление";					
					pchar.GenQuest.EncGirl.LoverFather = "portman_keeper";
				break;
				case 3:
					sTemp = "в таверну";					
					pchar.GenQuest.EncGirl.LoverFather = "tavern_keeper";
				break;
				case 4:
					sTemp = "в банк";					
					pchar.GenQuest.EncGirl.LoverFather = "usurer_keeper";
				break;
			}	
			pchar.GenQuest.EncGirl.FatherLoc = sTemp;
			dialog.text = "Я обещал познакомить вас с родителями. Когда освободитесь, зайдите " + sTemp + ", там работает мой отец, я расскажу ему, что вы для нас сделали. Уверяю, он будет рад вас видеть.";
			link.l1 = "Хорошо-хорошо, зайду. Будьте счастливы...";
			link.l1.go = "EncGirl_Lover8";
		break;
		
		case "EncGirl_Lover8":
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "", 5.0);
			npchar.lifeday = 0;
			AddQuestRecord("JungleGirl", "16");
			AddQuestUserData("JungleGirl", "sSex", GetSexPhrase("","а"));
			AddQuestUserData("JungleGirl", "sText", pchar.GenQuest.EncGirl.FatherLoc);
			if((GetSummonSkillFromName(pchar, SKILL_FORTUNE) + GetSummonSkillFromName(pchar, SKILL_LEADERSHIP)) < 175)
			{
				pchar.GenQuest.EncGirl.LoverFatherAngry = 0; // папочка жениха счастлив за сына :)
			}
			else
			{
				pchar.GenQuest.EncGirl.LoverFatherAngry = 1; // папочка жениха разъярен за то что сын притащил в дом шалаву :)
			}
			chrDisableReloadToLocation = false; 
			pchar.GenQuest.EncGirl = "toLoverFather";
			pchar.quest.EncGirl_GetLoverFather.win_condition.l1 = "Timer";
			pchar.quest.EncGirl_GetLoverFather.win_condition.l1.date.day = GetAddingDataDay(0, 0, 2);
			pchar.quest.EncGirl_GetLoverFather.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 2);
			pchar.quest.EncGirl_GetLoverFather.win_condition.l1.date.year = GetAddingDataYear(0, 0, 2);
			pchar.quest.EncGirl_GetLoverFather.function = "EncGirl_GenQuest_GetLoverFather";
			DialogExit();	
		break;
		// Генератор "Девица в джунглях"
		
		// Генератор "Поручение капитана"
		case "CaptainComission_1":
			dialog.text = RandPhraseSimple("Стой!.. Стой, капитан! подожди.","Капитан, подожди, умоляю...");
			link.l1 = LinkRandPhrase("Что, одышка замучила?","Подними клинок! трус.","В чём дело?! Забыл завещание оставить?");
			link.l1.go = "CaptainComission_2";
		break;
		
		case "CaptainComission_2":
			dialog.text = "Подождите, я ранен и больше не в силах сопротивляться... Пощады не прошу, но у меня осталось незавершённым одно дело. Пообещайте, что не откажете умирающему.";
			link.l1 = RandPhraseSimple("Не будьте слюнтяем, капитан, примите смерть, как мужчина!..","Капитан, какие сантименты? Вокруг грохочет бой. И давайте достойно завершим начатое.");
			link.l1.go = "CaptainComission_21";
			link.l2 = "Излагайте, только побыстрее. ";
			link.l2.go = "CaptainComission_22";
		break;
		
		case "CaptainComission_21":
			LAi_SetCurHPMax(NPChar);
			LAi_GetCharacterMaxEnergy(NPChar);
			ChangeCharacterComplexReputation(pchar,"nobility", -2);
			DeleteAttribute(pchar,"GenQuest.CaptainComission");
			QuestAboardCabinDialogExitWithBattle(""); 
			DialogExit();	
			AddDialogExitQuest("MainHeroFightModeOn");		
		break;
		
		case "CaptainComission_22":		
			if(rand(1) == 0) 
			{
				CaptainComission_Init(NPChar);
				dialog.text = "Передайте человеку по имени " + pchar.GenQuest.CaptainComission.Name + ", из поселения " + XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City) + ", что я не смог выполнить его поручение... вернее, не успел. Пусть меня простит...";
				link.l1 = RandPhraseSimple("И всего-то?! Хорошо, я это сделаю. Э-э, любезный...","Хорошо, передам, если найду время. Э-э, любезный...");
				link.l1.go = "CaptainComission_22_1";
				link.l2 = "Не думаю, что стану заниматься подобными глупостями. И давайте достойно завершим начатое.";
				link.l2.go = "CaptainComission_22_2";
			}
			else // "операция 'Галеон'"          
			{			
				CaptainComission_GaleonInit(NPChar);
			
				dialog.text = "Передайте капитану патрульного " + GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType), "Name") + "Gen")) + " '" + pchar.GenQuest.CaptainComission.ShipTypeName + "', что ему нельзя появляться в " + XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Dat") + "... " +
							"Властям стали известны обстоятельства гибели " + GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipTypeVictim), "Name") + "Gen")) + " '" + pchar.GenQuest.CaptainComission.VictimShipName + "'... нужно успеть... " + pchar.GenQuest.CaptainComission.Name + "... его ждёт арест... " + GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType), "Name"))) + " идёт в " + XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Acc") + " из " + XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City1 + "Gen") + " и дней через 15 бросит якорь в порту... нужно постараться перехватить...";
				link.l1 = RandPhraseSimple("Ничего не обещаю, но при случае передам. Э-э, любезный... ","Хорошо, передам, если успею. Э-э, любезный... ");
				link.l1.go = "CaptainComission_300";
			}					
		break;
		
		case "CaptainComission_22_1":
			ReOpenQuestHeader("CaptainComission1");
			AddQuestRecord("CaptainComission1", "1");
			AddQuestUserData("CaptainComission1", "sShipName", pchar.GenQuest.CaptainComission.ShipName);
			AddQuestUserData("CaptainComission1", "sCapName", pchar.GenQuest.CaptainComission.CapName);
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City));	
			SetFunctionTimerCondition("CaptainComission_Speak", 0, 0, 30, false);
			SetFunctionTimerCondition("CaptainComission_SellSlave", 0, 0, 15 + rand(5), false);
			LAi_KillCharacter(NPChar);
			LAi_SetPlayerType(pchar); 
			pchar.GenQuest.CaptainComission = "Begin_1";
			LAi_EnableReload();
			Log_SetActiveAction("Reload");
			DialogExit();	
		break;
		
		case "CaptainComission_22_2":
			dialog.text = "Какая жестокость! Надеюсь, на том свете вам это зачтётся.";
			link.l1 = "И не только это..";
			link.l1.go = "CaptainComission_22_3";
		break;
		
		case "CaptainComission_22_3":
			ReOpenQuestHeader("CaptainComission1");
			AddQuestRecord("CaptainComission1", "1");
			AddQuestUserData("CaptainComission1", "sShipName", pchar.GenQuest.CaptainComission.ShipName);
			AddQuestUserData("CaptainComission1", "sCapName", pchar.GenQuest.CaptainComission.CapName);
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City));
			SetFunctionTimerCondition("CaptainComission_Speak", 0, 0, 30, false);
			SetFunctionTimerCondition("CaptainComission_SellSlave", 0, 0, 15 + rand(5), false);
			LAi_SetCurHPMax(NPChar);
			LAi_GetCharacterMaxEnergy(NPChar);
			ChangeCharacterComplexReputation(pchar,"nobility", -3);
			pchar.GenQuest.CaptainComission = "Begin_2";
			QuestAboardCabinDialogExitWithBattle(""); 
			DialogExit();	
			AddDialogExitQuest("MainHeroFightModeOn");		
		break;
		
		case "CaptainComission_3":
			dialog.text = LinkRandPhrase("Слушаю вас, " + GetAddress_Form(pchar) + ".","Что вы хотели?","Чем могу служить?");
			if (pchar.GenQuest.CaptainComission == "Begin_1" || pchar.GenQuest.CaptainComission == "Begin_2") // лесник - доп.проверка если есть квест. для перехода .
			{	
			link.l1 = "Вы " + pchar.GenQuest.CaptainComission.Name + "? У меня к вам поручение. Капитан " + pchar.GenQuest.CaptainComission.CapName + " просил передать вам важную информацию.";
			link.l1.go = "CaptainComission_4";
			break;
			}
			link.l2 = "Нет,ничего...";
			link.l2.go = "exit";
			NextDiag.TempNode = "CaptainComission_3"; // лесник - переход чтобы не вызывал баг при повтороном обращении
		break;
		
		case "CaptainComission_4":
			dialog.text = "Да? Ну давайте потолкуем. Так о чём вас просил капитан " + pchar.GenQuest.CaptainComission.CapName + "?";
			link.l1 = "Он просил передать, что не сможет выполнить ваше поручение.";
			link.l1.go = "CaptainComission_5";
		break;
		
		case "CaptainComission_5":
			dialog.text = "Да что вы такое говорите?! Я его давно знаю, это честнейший человек - он не мог так поступить!";
			link.l1 = "Скажем так, ему помешали обстоятельства. Иными словами - он погиб.";
			link.l1.go = "CaptainComission_6";
		break;
		
		case "CaptainComission_6":
			CaptainComission_GetPirateIsland();
			CaptainComission_GetFamilyType();
			if(pchar.GenQuest.CaptainComission == "Begin_1")
			{
				dialog.text = "Ах, как это всё некстати! Столько времени упущено...\n"
					+ "Капитан, в таком случае, я вынужден просить помощи у вас. Пираты из " + XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.PiratesCity + "Gen") + " захватили моего " + GetStrSmallRegister(XI_ConvertString("Family" + pchar.GenQuest.CaptainComission.FamilyType + "Gen")) + ", его зовут " + pchar.GenQuest.CaptainComission.SlaveName + ", и требуют за него выкуп. Вы не согласились бы взять эту миссию на себя? Вознаграждение будет щедрым.";
				link.l1 = "К сожалению, у меня несколько другие планы.";
				link.l1.go = "CaptainComission_6_1";
				link.l2 = "Попытаюсь вам помочь, если изложите суть дела подробнее.";
				link.l2.go = "CaptainComission_6_2";
			}
			
			if(pchar.GenQuest.CaptainComission == "Begin_2")
			{
				dialog.text = "Ах, как это всё некстати! Столько времени упущено...\nА где сундуки?";
				link.l1 = "М-м... какие сундуки?";
				link.l1.go = "CaptainComission_6_3";
				pchar.GenQuest.CaptainComission.CanFindChest = true;
			}	
		break;
		
		case "CaptainComission_6_1":
			dialog.text = "Очень жаль, капитан... очень жаль, что вы не хотите мне помочь.";
			link.l1 = "Тут не в желании дело, уважаемый. Вы же сами понимаете... До свидания.";
			link.l1.go = "CaptainComission_6_1End";
		break;
		
		case "CaptainComission_6_2": // лесник - от пиратского барона
			dialog.text = "Вчера я получил письмо от пиратского барона, в котором он сообщил, что повышает сумму выкупа и грозится продать пленника в рабство. Покойный капитан должен был известить " + ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_ACC) + ", что я согласен на прежние условия, и выдать аванс. Но теперь мне понятно, почему пираты повысили ставки.";
			link.l1 = "И что вы предлагаете?";
			link.l1.go = "CaptainComission_6_21";
		break;
		
		case "CaptainComission_6_3":
			dialog.text = "О-о, "+ GetSexPhrase("приятель","подруга") +", сдаётся мне, кто-то затеял нечестную игру. Предупреждаю сразу - это опасно и чревато неприятностями. У этого капитана было три сундука золота, которые он должен был передать главе пиратов, в " + XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.PiratesCity + "Acc") + ", в качестве выкупа за одного человека по имени " + pchar.GenQuest.CaptainComission.SlaveName + ". Раз он поручил тебе связаться с нами, то не мог не сказать о сундуках.";
			link.l1 = "Может он просто не успел?";
			link.l1.go = "CaptainComission_6_31";
		break;
		
		case "CaptainComission_6_1End":
			AddQuestRecord("CaptainComission1", "3");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("cя","ась"));
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			AddQuestUserData("CaptainComission1", "sCharType", GetStrSmallRegister(XI_ConvertString("Family" + pchar.GenQuest.CaptainComission.FamilyType + "Gen")));
			CloseQuestHeader("CaptainComission1");
			sld = CharacterFromID("CapComission_1"); // удаление если послал нахуй. лесник.
			sld.LifeDay = 0;
			DeleteAttribute(pchar,"GenQuest.CaptainComission");
			ChangeCharacterComplexReputation(pchar,"nobility", -2);
			DialogExit();	
		break;
		
		case "CaptainComission_6_21":
			dialog.text = "Мне не оставляют выбора... Нужную сумму - 150 000 песо, я уже собрал. Хочу просить вас доставить её в " + XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.PiratesCity + "Acc") + " и привезти " + GetStrSmallRegister(XI_ConvertString("Family" + pchar.GenQuest.CaptainComission.FamilyType + "Gen")) + " сюда. За услугу готов заплатить 40 000, которые вы получите по возвращении.";
			link.l1 = "Хорошо, я готов"+ GetSexPhrase("","а") +" этим заняться.";
			link.l1.go = "CaptainComission_6_22";
			link.l2 = "К сожалению, у меня несколько другие планы.";
			link.l2.go = "CaptainComission_6_1";			
		break;
		
		case "CaptainComission_6_22":
			dialog.text = "Тогда держите деньги, и благослови вас Господь... Только нужно торопиться - боюсь, что " + ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_NOM) + " не станет ждать и продаст беднягу в рабство.";
			link.l1 = "Ждите меня здесь. Думаю, это не займёт много времени.";
			link.l1.go = "CaptainComission_6_22End";
		break;
		
		case "CaptainComission_6_22End":
			AddQuestRecord("CaptainComission1", "4");
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Gen"));
			AddQuestUserData("CaptainComission1", "sPirateName", ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_DAT));
			AddQuestUserData("CaptainComission1", "sPirateCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.PiratesCity + "Acc"));
			AddQuestUserData("CaptainComission1", "sFamilyType", GetStrSmallRegister(XI_ConvertString("Family" + pchar.GenQuest.CaptainComission.FamilyType + "Gen")));
			AddQuestUserData("CaptainComission1", "sSlaveName",pchar.GenQuest.CaptainComission.SlaveName);
			addMoneyToCharacter(pchar, 150000);
			pchar.GenQuest.CaptainComission = "Begin_11";
			pchar.GenQuest.CaptainComission.AfterTavernSpeak = "goodSpeak";
			pchar.GenQuest.CaptainComission.GetSlave = "NoSlave";
			pchar.GenQuest.CaptainComission.toMayor = true;
			SetFunctionTimerCondition("CaptainComission_30DaysIsLeft", 0, 0, 30, false);
			NextDiag.TempNode = "CaptainComission_7";
			NextDiag.CurrentNode = NextDiag.TempNode; 
			DialogExit();
		break;
		
		case "CaptainComission_6_31":
			dialog.text = "Или не захотел... это дела не меняет.\nЛюди, которые собирали выкуп, этим интересоваться не станут. Им нужен результат - живой и невредимый " + pchar.GenQuest.CaptainComission.SlaveName + ". Поэтому не теряй времени.";
			link.l1 = "А если я не соглашусь?";
			link.l1.go = "CaptainComission_6_32";
		break;
						
		case "CaptainComission_6_32":
			dialog.text = "А мне и не нужно твоего согласия. Я просто ставлю тебя в известность, что если через тридцать дней ты не доставишь в эту таверну живого пленника, то я отправлю по твоему следу охотников за головами...";
			link.l1 = "Хм, однако же... А если доставлю?";
			link.l1.go = "CaptainComission_6_33";
		break;
		
		case "CaptainComission_6_33":
			dialog.text = "А вот тогда и потолкуем...";
			link.l1 = "Ну ладно... посмотрим, как оно обернётся.";
			link.l1.go = "CaptainComission_6_33End";
		break;
		
		case "CaptainComission_6_33End":
			AddQuestRecord("CaptainComission1", "5");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("","а"));
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("","ла"));
			AddQuestUserData("CaptainComission1", "sCapName",pchar.GenQuest.CaptainComission.CapName);
			AddQuestUserData("CaptainComission1", "sPirateName", ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_DAT));
			AddQuestUserData("CaptainComission1", "sPirateCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.PiratesCity + "Acc"));
			AddQuestUserData("CaptainComission1", "sSlaveName",pchar.GenQuest.CaptainComission.SlaveName);
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Gen"));
			pchar.GenQuest.CaptainComission = "Begin_22";
			pchar.GenQuest.CaptainComission.AfterTavernSpeak = "badSpeak";
			pchar.GenQuest.CaptainComission.GetSlave = "NoSlave";
			pchar.GenQuest.CaptainComission.toMayor = true;
			SetFunctionTimerCondition("CaptainComission_30DaysIsLeft", 0, 0, 30, false);
			NextDiag.TempNode = "CaptainComission_7";
			NextDiag.CurrentNode = NextDiag.TempNode; 
			DialogExit();
		break;
		
		case "CaptainComission_7":
			if(pchar.GenQuest.CaptainComission.GetSlave == "NoSlave")
			{
				if(pchar.GenQuest.CaptainComission.AfterTavernSpeak == "goodSpeak")
				{
					dialog.text = LinkRandPhrase("Здравствуйте, капитан " + GetFullName(pchar) + ". Есть какие-нибудь новости?","Ну что, капитан, вы уже доставили выкуп?","Здравствуйте, я надеюсь, вы привезли хорошие известия?");
					if(makeint(pchar.money)>=150000)
					{
						link.l1 = "К сожалению, у меня изменились планы, я вынужден"+ GetSexPhrase("","а") +" разорвать наш договор.";
						link.l1.go = "CaptainComission_7_1";
					}
					link.l2 = "Нет ещё. Я этим занимаюсь.";
					link.l2.go = "CaptainComission_7_2";
				}
				if(pchar.GenQuest.CaptainComission.AfterTavernSpeak == "badSpeak")
				{
					dialog.text = LinkRandPhrase("А-а, приветствую вас, капитан " + GetFullName(pchar) + ". Как успехи?","Ну что, капитан, вызволили нашего страдальца?","Рад вас видеть, капитан, в добром здравии. Как продвигается наше общее дело?");
					link.l1 = "Новостей пока никаких, но я этим занимаюсь.";
					link.l1.go = "CaptainComission_7_3";
					link.l2 = "Послушайте, уважаемый, а на каком основании вы меня обязываете заниматься этим вопросом?";
					link.l2.go = "CaptainComission_7_4";
				}
			}
			if(pchar.GenQuest.CaptainComission.GetSlave == "GetSlave")
			{
				if(pchar.GenQuest.CaptainComission.AfterTavernSpeak == "goodSpeak")
				{
					dialog.text = LinkRandPhrase("Здравствуйте, капитан " + GetFullName(pchar) + ". Есть какие-нибудь новости?","Ну что, капитан, вы уже доставили выкуп?","Здравствуйте, я надеюсь, вы привезли хорошие известия?");
					link.l1 = "Да. Ваше поручение выполнено, " + pchar.GenQuest.CaptainComission.SlaveName + " у меня на борту и готовится сойти на берег.";
					link.l1.go = "CaptainComission_30";
				}
				else
				{
					dialog.text = LinkRandPhrase("А-а, приветствую вас, капитан " + GetFullName(pchar) + ". Как успехи?","Ну что, капитан, вызволили нашего страдальца?","Рад вас видеть, капитан, в добром здравии. Как продвигается наше общее дело?");	
					link.l1 = "Я привез"+ GetSexPhrase("","ла") +" человека, о котором вы говорили. Он у меня на борту.";
					link.l1.go = "CaptainComission_32";
				}
			}
			if(pchar.GenQuest.CaptainComission.GetSlave == "SlaveDied")
			{
				if(pchar.GenQuest.CaptainComission.AfterTavernSpeak == "goodSpeak")
				{
					dialog.text = LinkRandPhrase("Здравствуйте, капитан " + GetFullName(pchar) + ". Есть какие-нибудь новости?","Ну что, капитан, вы уже доставили выкуп?","Здравствуйте, я надеюсь, вы привезли хорошие известия?");
					link.l1 = "Здравствуйте " + pchar.GenQuest.CaptainComission.Name + ", я вынужден"+ GetSexPhrase("","а") +" вас огорчить.";
					link.l1.go = "CaptainComission_50";
				}
				else
				{
					dialog.text = LinkRandPhrase("А-а, приветствую вас, капитан " + GetFullName(pchar) + ". Как успехи?","Ну что, капитан, вызволили нашего страдальца?","Рад вас видеть, капитан, в добром здравии. Как продвигается наше общее дело?");
					link.l1 = "Человек, о котором вы просили, погиб.";
					link.l1.go = "CaptainComission_60";
				}
			}
		break;
		
		case "CaptainComission_30":
			dialog.text = "Спасибо, капитан, вы оказали неоценимую услугу всей нашей семье. Вот ваше вознаграждение... Здесь три сундука - это как раз 40 000 песо. Извините, но я поспешу ему навстречу.";
			link.l1 = "Конечно-конечно, счастливой встречи и всего наилучшего.";
			link.l1.go = "CaptainComission_30_1";
			if(CheckAttribute(pchar, "GenQuest.CaptainComission.SlaveAddMoney"))
			{
				link.l2 = "Мне понятно ваше нетерпение, но возникли обстоятельства, которые заставили меня понести дополнительные траты.";
				link.l2.go = "CaptainComission_31";
			}	
		break;
		
		case "CaptainComission_30_1":
			//addMoneyToCharacter(pchar, 25000);
			TakeNItems(pchar, "chest", 3);
			Log_Info("Вы получили кредитные сундуки");
			PlaySound("interface\important_item.wav");
			AddQuestRecord("CaptainComission1", "14");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("","а"));
			AddQuestUserData("CaptainComission1", "sName", pchar.GenQuest.CaptainComission.SlaveName);
			CloseQuestHeader("CaptainComission1");
			ChangeCharacterComplexReputation(pchar,"nobility", 2);
			DialogExit();
			AddDialogExitQuestFunction("CaptainComission_EndTavern");
		break;
		
		case "CaptainComission_31":
			//addMoneyToCharacter(pchar, 25000);
			TakeNItems(pchar, "chest", 2);
			Log_Info("Вы получили кредитные сундуки");
			PlaySound("interface\important_item.wav");
			dialog.text = "Я вас не понимаю... Мы же заранее оговорили сумму вознаграждения.";
			link.l1 = "Да, но вместо 150000 песо, мне пришлось выложить 200000. И ещё на Барбадос мотаться.";
			link.l1.go = "CaptainComission_31_1";
		break;
		
		case "CaptainComission_31_1":
			dialog.text = "Капитан, это всего лишь результат вашей нерасторопности. Никаких дополнительных условий от пиратов я не получал. Что за странная манера - пытаться нажить дивиденды на чужих неприятностях?!";
			link.l1 = "Вижу, вам бесполезно что-либо объяснять...";
			link.l1.go = "CaptainComission_31_1End";
		break;
		
		case "CaptainComission_31_1End":
			AddQuestRecord("CaptainComission1", "15");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("","а"));
			AddQuestUserData("CaptainComission1", "sName", pchar.GenQuest.CaptainComission.SlaveName);
			CloseQuestHeader("CaptainComission1");			
			DialogExit();
			AddDialogExitQuestFunction("CaptainComission_EndTavern");
		break;

		case "CaptainComission_32":
			dialog.text = "Вот и великолепно! А вы сомневались, что мы сработаемся.";
			link.l1 = "Но мне пришлось изрядно потратиться на это мероприятие.";
			link.l1.go = "CaptainComission_32_1";
		break;
		
		case "CaptainComission_32_1":
			GetSlaveSpeciality();
			dialog.text = "Знаю-знаю... Но отчасти вы сами виноваты. Как можно было утопить целых три сундука золота, которое мы с таким трудом вытрясли из казны, чтобы " + NationNameNominative(sti(pchar.GenQuest.CaptainComission.Nation)) + " могла заполучить этого специалиста " + pchar.GenQuest.CaptainComission.SlaveSpeciality + "?";
			link.l1 = "Имейте в виду, что я не намерен"+ GetSexPhrase("","а") +" выдавать вам его без достойной компенсации.";
			link.l1.go = "CaptainComission_32_2";
		break;
		
		case "CaptainComission_32_2":
			dialog.text = "Ну, вы, как "+ GetSexPhrase("человек неглупый","девушка неглупая") +", должны понимать, что торговаться уже поздно. Мы могли бы просто арестовать ваше судно вместе со всем барахлом.\nНо компенсация была предусмотрена заранее... Итак, от имени правительства " + NationNameGenitive(sti(pchar.GenQuest.CaptainComission.Nation)) + " разрешите вас поздравить с успешным завершением операции и вручить этот ценный подарок и небольшое материальное вознаграждение.";
			link.l1 = "Гхм-гхм... Спасибо и на этом. Забирайте своего важного специалиста.";
			link.l1.go = "CaptainComission_32_2End";
		break;
		
		case "CaptainComission_32_2End":
			AddQuestRecord("CaptainComission1", "16");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("","а"));
			AddQuestUserData("CaptainComission1", "sSpeciality", pchar.GenQuest.CaptainComission.SlaveSpeciality);
			AddQuestUserData("CaptainComission1", "sNation", NationNameNominative(sti(pchar.GenQuest.CaptainComission.Nation)));
			CloseQuestHeader("CaptainComission1");			
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 15);			
			GiveItem2Character(pchar, pchar.GenQuest.CaptainComission.Item); 
			TakeNItems(pchar, "jewelry5", 100);
			PlaySound("interface\important_item.wav");
			DialogExit();
			AddDialogExitQuestFunction("CaptainComission_EndTavern");
		break;
		
		case "CaptainComission_7_1":
			dialog.text = "Ах, какая досада! Я и без того потерял слишком много времени. Вы меня очень подвели, капитан!";
			link.l1 = "Понимаю, но обстоятельства оказались сильнее. Вот ваши деньги.";
			link.l1.go = "CaptainComission_7_1End";
		break;
		
		case "CaptainComission_7_1End":
			AddQuestRecord("CaptainComission1", "8");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("","а"));
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			CloseQuestHeader("CaptainComission1");
			rChar = characterFromId("CapComission_1");
			rChar.lifeDay = 0; 
			pchar.quest.CaptainComission1_30DaysIsLeft.over = "yes";
			addMoneyToCharacter(pchar, -150000);
			ChangeCharacterComplexReputation(pchar,"nobility", -4);
			LAi_CharacterDisableDialog(NPChar);
			DialogExit();
			AddDialogExitQuestFunction("CaptainComission_EndTavern");
		break;
		
		case "CaptainComission_7_2":
			dialog.text = "Нельзя ли поторопиться? Я боюсь, что пираты снова изменят условия.";
			link.l1 = "Не волнуйтесь, мы всё успеем.";
			link.l1.go = "exit";
			NextDiag.TempNode = "CaptainComission_7";
		break;
		
		case "CaptainComission_7_3":
			dialog.text = "Надеюсь, вы понимаете, что время работает против вас?";
			link.l1 = "Я повторяю, что занимаюсь вашим вопросом.";
			link.l1.go = "exit";
			NextDiag.TempNode = "CaptainComission_7";
		break;
		
		case "CaptainComission_7_4":
			dialog.text = "Боже упаси! Никаких обязательств - исключительно помощь пуританина на добровольных началах...\nНечего было лезть не в своё дело. Ты убил"+ GetSexPhrase("","а") +" посыльного, сорвал"+ GetSexPhrase("","а") +" нам выкуп ценного человека, да ещё золото наше проворонил"+ GetSexPhrase("","а") +". Заварил"+ GetSexPhrase("","а") +" кашу - теперь расхлёбывай. И не надейся, что это тебе сойдёт с рук...";
			link.l1 = "Чёрт бы вас побрал..";
			link.l1.go = "exit";
			NextDiag.TempNode = "CaptainComission_7";
		break;
		
		// диалоги с управляющим на плантации
		case "CaptainComission_10":
			dialog.text = "Здравствуйте, вы что-то хотели?";
			link.l1 = "Могу я видеть хозяина плантаций?";
			link.l1.go = "CaptainComission_10_1";
		break;
		
		case "CaptainComission_10_1":
			dialog.text = "Он в отъезде, ищет какого-то беглого раба - не то Блэйда, не то Блада. А я здешний управляющий " + npchar.name + " и уполномочен решать все вопросы в отсутствие хозяина.";
			link.l1 = "Вот как? Это хорошо... А вопросы о продаже рабов тоже входят в вашу компетенцию?";
			link.l1.go = "CaptainComission_10_2";
		break;
		
		case "CaptainComission_10_2":
			dialog.text = "Безусловно. У вас большая партия?";
			link.l1 = "Нет, я хочу купить только одного невольника.";
			link.l1.go = "CaptainComission_10_3";
		break;
		
		case "CaptainComission_10_3":
			dialog.text = "Э-э, а вы уверены, что вам нужен только один раб?";
			link.l1 = "Ну конечно уверен"+ GetSexPhrase("","а") +" - его имя " + pchar.GenQuest.CaptainComission.SlaveName + ".";
			link.l1.go = "CaptainComission_10_4";
		break;
		
		case "CaptainComission_10_4":
			if(rand(1) == 0)
			{
				dialog.text = "Ну, вы же понимаете, что стоимость одного невольника всегда будет выше, чем удельная цена невольника при покупке большой партии?";
				link.l1 = "Ну хорошо, я могу в конце концов эту цену услышать?";
				link.l1.go = "CaptainComission_11";
			}
			else
			{
				if(rand(100) < makeint(sti(pchar.rank) + 0.75 * GetSummonSkillFromName(pchar, SKILL_FORTUNE)))
				{
					dialog.text = "Хм, я полагаю, вы знаете, за кого просите?";
					link.l1 = "В каком смысле?";
					link.l1.go = "CaptainComission_12";
				}
				else
				{
					dialog.text = "А-а, этот лежебока. Я бы за него и ломаного гроша не дал. С тех пор, как его привезли, он ещё палец о палец не ударил. И зачем только полковник тратит деньги на этих каторжников? Другое дело негры - вот это работники! Страсть к работе у них в крови. И поверьте, им абсолютно всё равно какую работу выполнять! Хочешь - на тростник их посылай, хочешь - ставь президентом...";
					link.l1 = "Эй, милейший, мне не нужны негры, мне нужен тот лентяй, о котором вы говорили.";
					link.l1.go = "CaptainComission_13";
				}
			}
		break;
		
		case "CaptainComission_11":
			dialog.text = "Конечно-конечно, вот прейскурант...\nОго!!! 150000 песо... ";
			link.l1 = "Однако...";
			link.l1.go = "CaptainComission_11_1";
		break;
		
		case "CaptainComission_11_1":
			dialog.text = "Так указано в прейскуранте, вот взгляните. Сам не пойму... На остальных рабов цены нормальные, а за этого полковник почему-то выставил целое состояние..";
			if(sti(pchar.money) >= 150000)
			{
				link.l1 = "Кажется, я догадываюсь в чём здесь дело... Вот деньги, я его забираю.";
				link.l1.go = "CaptainComission_14";
			}	
			link.l2 = "Хм... Но я же не заложника освобождаю, а всего лишь покупаю раба. Вы не находите, что за такие деньги можно корабль купить в полном боевом снаряжении.";
			link.l2.go = "CaptainComission_15";
		break;
		
		case "CaptainComission_12":
			dialog.text = "Это не простой невольник. Полковник Бишоп строго-настрого приказал следить за ним в оба, даже охрану усиленную приставил.";
			link.l1 = "Так что же, его и купить нельзя?";
			link.l1.go = "CaptainComission_12_1";
		break;
		
		case "CaptainComission_12_1":
			dialog.text = "Почему же нельзя? Полковник назначил за него цену в 200000 песо, согласно прейскуранту.";
			if(sti(pchar.money) >= 200000)
			{
				link.l1 = "Ого! Полагаю, полковник знает, что за человек попал к нему в лапы... ";
				link.l1.go = "CaptainComission_16";
			}	
			link.l2 = "Хм... Но я же не заложника освобождаю, а всего лишь покупаю раба. Вы не находите, что за такие деньги можно корабль купить в полном боевом снаряжении.";
			link.l2.go = "CaptainComission_15";	
		break;
		
		case "CaptainComission_13":
			dialog.text = "Ах да, извините. Где-то здесь Бишоп оставил прейскурант. \nАга, вот. Мм-э... Ого!.. 150000!..";
			if(sti(pchar.money) >= 15000)
			{
				link.l1 = "Вероятно здесь какая-то ошибка. Согласитесь, что такая сумма никак не может соответствовать цене одного невольника. Я полагаю, там поставлен лишний нолик и сумма должна быть 15000. Да и то многовато за такого лежебоку.";
				link.l1.go = "CaptainComission_17";
			}	
			link.l2 = "Хм... Но я же не заложника освобождаю, а всего лишь покупаю раба. Вы не находите, что за такие деньги можно корабль купить в полном боевом снаряжении.";
			link.l2.go = "CaptainComission_15";
		break;
		
		case "CaptainComission_14":
			addMoneyToCharacter(pchar, -150000);
			pchar.GenQuest.CaptainComission.SlaveMoney = 150000;
			dialog.text = "Вот и хорошо! Вот и великолепно! Его сейчас приведут... Э-э, чайку не желаете?";
			link.l1 = "Нет, спасибо... Передайте привет полковнику Бишопу.";
			link.l1.go = "CaptainComission_14_1";
		break;
		
		case "CaptainComission_14_1":
			dialog.text = "А от кого, извините?";
			link.l1 = "Мм... да нет, не нужно. До свидания. ";
			link.l1.go = "CaptainComission_14_1End";
		break;
		
		case "CaptainComission_14_1End":
			NextDiag.TempNode = "CaptainComission_18";
			NextDiag.CurrentNode = NextDiag.TempNode;
			pchar.GenQuest.CaptainComission.GetSlave = "GetSlave";
			DialogExit();
			AddDialogExitQuestFunction("CaptainComission_GetSlave");
		break;
		
		case "CaptainComission_15":
			dialog.text = "Увы, к сожалению, ничего не могу поделать... Вот прейскурант...";
			link.l1 = "Да что ты заладил - прейскурант, прейскурант... Без Бишопа и шагу ступить не можете. Передай ему... а впрочем не надо ничего.";
			link.l1.go = "CaptainComission_15_1";
		break;
		
		case "CaptainComission_15_1":
			dialog.text = "Так вы не будете покупать этого невольника?";
			link.l1 = "Нет. До свидания.";
			link.l1.go = "CaptainComission_15_1End";
		break;
		
		case "CaptainComission_15_1End":
			OfficersReaction("bad");
			AddQuestRecord("CaptainComission1", "30");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("","а"));
			NextDiag.TempNode = "CaptainComission_19";
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			AddDialogExitQuestFunction("CaptainComission_GetSlave");
		break;
		
		case "CaptainComission_16":
			dialog.text = "Мне об этом ничего не известно. Я имею лишь чёткие инструкции на случай его продажи.";
			link.l1 = "Чёрт знает, что такое... Вот деньги. Прикажите привести невольника.";
			link.l1.go = "CaptainComission_16_1"; 
		break;
		
		case "CaptainComission_16_1":
			addMoneyToCharacter(pchar, -200000);
			pchar.GenQuest.CaptainComission.SlaveMoney = 200000;
			dialog.text = "Да, конечно. Он сейчас же будет доставлен.";
			link.l1 = "Прощайте.";
			link.l1.go = "CaptainComission_16_1End";
		break;
		
		case "CaptainComission_16_1End":
			NextDiag.TempNode = "CaptainComission_18";
			NextDiag.CurrentNode = NextDiag.TempNode;
			pchar.GenQuest.CaptainComission.GetSlave = "GetSlave";
			DialogExit();
			AddDialogExitQuestFunction("CaptainComission_GetSlave");
		break;
		
		case "CaptainComission_17":
			dialog.text = "Уф-ф, вы наверное правы. Просто ошибка.";
			link.l1 = "Ну, раз мы определились с ценой, я могу его забрать?";
			link.l1.go = "CaptainComission_17_1";
		break;
		
		case "CaptainComission_17_1":
			dialog.text = "Да, конечно. Его сейчас приведут.";
			link.l1 = "Вот и хорошо. Вот ваши деньги... До свидания.";
			link.l1.go = "CaptainComission_17_1End";
		break;
		
		case "CaptainComission_17_1End":
			addMoneyToCharacter(pchar, -15000);
			pchar.GenQuest.CaptainComission.SlaveMoney = 15000;
			NextDiag.TempNode = "CaptainComission_18";
			NextDiag.CurrentNode = NextDiag.TempNode;
			pchar.GenQuest.CaptainComission.GetSlave = "GetSlave";
			DialogExit();
			AddDialogExitQuestFunction("CaptainComission_GetSlave");
		break;
		
		case "CaptainComission_18":
			dialog.text = "Может быть чайку, капитан?";
			link.l1 = "Нет. Спасибо.";
			link.l1.go = "exit";
		break;
		
		case "CaptainComission_19":
			dialog.text = "Вы всё-таки решили его купить?";
			link.l1 = "Нет. До свидания.";
			link.l1.go = "exit";
		break;
		
		// диалоги с рабом
		case "CaptainComission_20":
			if(pchar.GenQuest.CaptainComission.AfterTavernSpeak == "goodSpeak")
			{
				dialog.text = "Здравствуйте, капитан. Как я могу вас благодарить? Даже не верится, что закончился этот ад.";
				link.l1 = "Это не меня нужно благодарить, а вашего родственника по нмени " + pchar.GenQuest.CaptainComission.Name + " из " + XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Gen") + ". Он собрал за вас выкуп.";
				link.l1.go = "CaptainComission_201";
			}
			else
			{
				dialog.text = "Здравствуйте капитан. Мне сказали, что это вы внесли залог. Благодарю вас, хотя и понимаю, что вы лишь курьер.";
				link.l1 = "А вы не выглядите счастливым от вновь приобретённой свободы. Вас что-то смущает?";
				link.l1.go = "CaptainComission_202";
			}
		break;
		
		case "CaptainComission_201":
			dialog.text = "Очень вас прошу, если это не нарушит ваши планы, отвезите меня к нему пожалуйста. Я должен его отблагодарить.";
			link.l1 = "Конечно отвезу. Идёмте, я провожу вас на борт.";
			link.l1.go = "CaptainComission_201_1";
		break;
		
		case "CaptainComission_201_1":
			AddQuestRecord("CaptainComission1", "11");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("","а"));
			AddQuestUserData("CaptainComission1", "sName", pchar.GenQuest.CaptainComission.SlaveName);
			AddQuestUserData("CaptainComission1", "sSum", pchar.GenQuest.CaptainComission.SlaveMoney);
			AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Acc"));
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, false);
			LAi_SetActorType(NPChar);
			LAi_ActorRunToLocation(NPChar, "reload", "reload2_back", "none", "", "", "OpenTheDoors", -1.0);
			DialogExit();
		break;
		
		case "CaptainComission_202":
			dialog.text = "Чтоб быть уверенным, в своей свободе, мне нужно знать имена тех, кто за неё заплатил.";
			link.l1 = "Ну, положим, заплатил"+ GetSexPhrase("","а") +" за неё я, хотя и сделал"+ GetSexPhrase("","а") +" это не по своей воле.";
			link.l1.go = "CaptainComission_202_1";
		break;
		
		case "CaptainComission_202_1":
			dialog.text = "Итак, мои опасения подтверждаются. Вас заставили это сделать " + NationNamePeople(sti(pchar.GenQuest.CaptainComission.Nation)) + "?";
			link.l1 = "Да, это " + pchar.GenQuest.CaptainComission.Name + " из " + XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Gen") + ".";
			link.l1.go = "CaptainComission_202_2";
		break;
		
		case "CaptainComission_202_2":
			iNation = FindEnemyNation2NationWithoutPirates(sti(pchar.GenQuest.CaptainComission.Nation));	// mitrokosta 
			if(iNation == -1) iNation(rand(3));
			pchar.GenQuest.CaptainComission.SlaveCity = FindAlliedColonyForNation(iNation, true);
			pchar.GenQuest.CaptainComission.EnemyNation = iNation;
			LAi_SetImmortal(npchar, true);// лесник . откатил .  и защиту  чтоб умники не убили.
			dialog.text = "Ясно... Не знаю, что они вам пообещали, но предлагаю сделку: вы меня доставите в таверну " + XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.SlaveCity + "Gen") + ", где я буду действительно в безопасности, а я поделюсь с вами частью информации, которой обладаю.";
			link.l1 = "Годится. Тем более, что они ничего и не обещали. Идите за мной, я провожу вас на корабль.";
			link.l1.go = "CaptainComission_202_3"; 
			link.l2 = "Я не стану рисковать получить неприятности из-за какой-то информации сомнительного толка.";
			link.l2.go = "CaptainComission_203";
		break;
		
		
		
		case "CaptainComission_202_3":
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, false);
			rChar = characterFromId("CapComission_1");
			ChangeCharacterAddress(rChar, "none", "");			
			rChar.lifeDay = 0; 
			AddQuestRecord("CaptainComission1", "12");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("","а"));
			AddQuestUserData("CaptainComission1", "sSex1", GetSexPhrase("ся","ась"));
			AddQuestUserData("CaptainComission1", "sName", pchar.GenQuest.CaptainComission.SlaveName);
			AddQuestUserData("CaptainComission1", "sSum", pchar.GenQuest.CaptainComission.SlaveMoney);
			AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.SlaveCity + "Acc"));
			pchar.quest.CapComission_DeliveSlave.win_condition.l1 = "location";
			pchar.quest.CapComission_DeliveSlave.win_condition.l1.location = pchar.GenQuest.CaptainComission.SlaveCity + "_tavern";
			pchar.quest.CapComission_DeliveSlave.function = "CaptainComission_DeliveSlave";
			LAi_SetActorType(NPChar);
			LAi_ActorFollow(NPChar, PChar, "OpenTheDoors", -1.0); //лесник  идем за ГГ
			DialogExit();
		break;
		
		case "CaptainComission_203":
			dialog.text = "К сожалению, я не могу вам открыть её свойства сейчас. Это может навредить нам обоим.";
			link.l1 = "Тем более... Вас проводят на корабль и не вздумайте чудить. Считайте, что вы опять под арестом.";
			link.l1.go = "CaptainComission_203_1";
		break;
		
		case "CaptainComission_203_1":
			AddQuestRecord("CaptainComission1", "13");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("","а"));
			AddQuestUserData("CaptainComission1", "sName", pchar.GenQuest.CaptainComission.SlaveName);
			AddQuestUserData("CaptainComission1", "sSum", pchar.GenQuest.CaptainComission.SlaveMoney);
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, false);
			LAi_SetActorType(NPChar);
			LAi_ActorRunToLocation(NPChar, "reload", "reload2_back", "none", "", "", "OpenTheDoors", -1.0); //лесник - провожаем на корабль типа..
			DialogExit();
		break;
		
		case "CaptainComission_50":
			dialog.text = "Что?! Пираты опять изменили условия? Но я не в состоянии больше изымать деньги из оборота. Скоро всё моё дело пойдёт прахом!";
			link.l1 = "Нет... Ваш родственник погиб на плантациях Барбадоса при неудачной попытке бежать.";
			link.l1.go = "CaptainComission_51";
		break;
		
		case "CaptainComission_51":
			ChangeCharacterComplexReputation(pchar,"nobility", -3);
			dialog.text = "Ах... я просто раздавлен... Как же это случилось?";
			link.l1 = "Пираты, не дождавшись выкупа продали его в рабство. Я пош"+ GetSexPhrase("ел","ла") +" за ним на Барбадос, но спасти не сумел"+ GetSexPhrase("","а") +"...";
			link.l1.go = "CaptainComission_52";
		break;
		
		case "CaptainComission_52":
			dialog.text = "Господи! что же это творится?..\nХорошо, капитан, спасибо за участие... И верните, пожалуйста, деньги, которые вы поучили от меня для выкупа.";
			link.l1 = "Мои расходы превысили все ожидания, поэтому ваши деньги я оставляю у себя... Прощайте.";
			link.l1.go = "CaptainComission_53";
			if(sti(pchar.money) >= 150000)
			{
				link.l2 = "Да, конечно возьмите... Извините, что не сумел"+ GetSexPhrase("","а") +" вам помочь... Прощайте.";
				link.l2.go = "CaptainComission_54";
			}
		break;
		
		case "CaptainComission_53":
			ChangeCharacterComplexReputation(pchar,"nobility", -5);
			OfficersReaction("bad");			
			AddQuestRecord("CaptainComission1", "22");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("","а"));
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			AddQuestUserData("CaptainComission1", "sName", pchar.GenQuest.CaptainComission.SlaveName);
			CloseQuestHeader("CaptainComission1");
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeDay = 0; 			
			DeleteAttribute(pchar,"GenQuest.CaptainComission");
			DialogExit();
		break;
		
		case "CaptainComission_54":
			OfficersReaction("good");
			addMoneyToCharacter(pchar, -150000);
			AddQuestRecord("CaptainComission1", "23");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("","а"));
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			AddQuestUserData("CaptainComission1", "sName", pchar.GenQuest.CaptainComission.SlaveName);
			CloseQuestHeader("CaptainComission1");
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeDay = 0; 			
			DeleteAttribute(pchar,"GenQuest.CaptainComission");
			DialogExit();
		break;
		
		case "CaptainComission_60":
			dialog.text = "Это скверно... вы даже не представляете себе, насколько это скверно..";
			link.l1 = "Ничем не могу помочь... Я даже рад"+ GetSexPhrase("","а") +", что так получилось. Прощайте.";
			link.l1.go = "CaptainComission_61";
		break;
		
		case "CaptainComission_61":
			ChangeCharacterComplexReputation(pchar,"nobility", -2);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), -15);
			AddQuestRecord("CaptainComission1", "32");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("","а"));
			AddQuestUserData("CaptainComission1", "sName", pchar.GenQuest.CaptainComission.Name);
			CloseQuestHeader("CaptainComission1");
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeDay = 0; 			
			DeleteAttribute(pchar,"GenQuest.CaptainComission");			
			DialogExit();
		break;
		
		// диалог с рабом в колодках
		case "CaptainComission_70":
			dialog.text = "Пить... капитан, принесите воды...";
			link.l1 = "Эй, приятель, не ты ли будешь " + pchar.GenQuest.CaptainComission.SlaveName + "?";
			link.l1.go = "CaptainComission_71";
		break;
		
		case "CaptainComission_71":
			dialog.text = "Да... это я...";
			link.l1 = "Слушай, если не хочешь подохнуть здесь, как камбала на мелководье - предлагаю очнуться и выслушать меня. Ты знаешь, где на Барбадосе маяк?";
			link.l1.go = "CaptainComission_72";
		break;
		
		case "CaptainComission_72":
			dialog.text = "Знаю...";
			link.l1 = "Как только у тебя появится возможность, беги туда. А я постараюсь эту возможность организовать.";
			link.l1.go = "CaptainComission_73";			
		break;
		
		case "CaptainComission_73":	
			LAi_SetPlayerType(pchar); 
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			LAi_LockFightMode(pchar, false);			
			sTemp = GetNationNameByType(GetCityNation("Bridgetown"))  + "_citizens";
			for(i = 0; i < 3; i++)
			{
				if (GetCharacterIndex("SlaveGuard_" + i) == -1) continue;
				sld = CharacterFromID("SlaveGuard_" + i);			
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "SlaveGuards");
			}
						
			LAi_group_SetRelation("SlaveGuards", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_SetRelation("SlaveGuards", sTemp, LAI_GROUP_NEITRAL);			
			LAi_group_SetAlarmReaction("SlaveGuards", sTemp, LAI_GROUP_NEITRAL, LAI_GROUP_FRIEND);
			LAi_group_FightGroups("SlaveGuards", LAI_GROUP_PLAYER, true);
			LAi_group_SetAlarm("SlaveGuards", LAI_GROUP_PLAYER, 0);
			LAi_group_SetCheck("SlaveGuards", "OpenTheDoors");
			LAi_group_SetCheckFunction("SlaveGuards", "CaptainComission_GuardsAfter");
			
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn"); 
		break;
		
		// диалог охранников раба
		case "CaptainComission_80":
			dialog.text = RandPhraseSimple("Спрашивайте, капитан, только коротко - я на службе.","Говорите, только по делу, я не могу отвлекаться на пустяки.");
			link.l1 = RandPhraseSimple("Не подскажешь, как мне найти одного раба? Его имя " + pchar.GenQuest.CaptainComission.SlaveName + ".","Где-то на плантации должен работать невольник по имени " + pchar.GenQuest.CaptainComission.SlaveName + ". Не подскажешь, как я могу с ним переговорить?");
			link.l1.go = "CaptainComission_81";			
		break;
		
		case "CaptainComission_81":
			dialog.text = "Он сегодня наказан и находится под стражей.";
			link.l1 = "Спасибо.";
			link.l1.go = "exit";
			NextDiag.TempNode = "CaptainComission_80";
			NextDiag.CurrentNode = NextDiag.TempNode;
		break;
		
		case "CaptainComission_85":
			dialog.text = "Спасибо... капитан, вы спасли мне жизнь...";
			link.l1 = "Беги к маяку Барбадоса и жди меня там.";
			link.l1.go = "CaptainComission_86";
		break;
		
		case "CaptainComission_86":
			LAi_SetActorType(NPChar);
			LAi_ActorRunToLocation(NPChar, "reload", "reload2_back", "none", "", "", "OpenTheDoors", -1.0);
			sTemp = GetNationNameByType(GetCityNation("Bridgetown"))  + "_citizens";
			LAi_group_AttackGroup(sTemp, LAI_GROUP_PLAYER);
			DialogExit();
		break;
		
		case "CaptainComission_90":
			if(pchar.GenQuest.CaptainComission.AfterTavernSpeak == "goodSpeak")
			{
				dialog.text = "Капитан, как я могу вас благодарить? Даже не верится, что закончился этот ад.";
				link.l1 = "Меня уже отблагодарил твой родственник " + pchar.GenQuest.CaptainComission.Name + " из " + XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Gen") + ". Я действую по его поручению.";
				link.l1.go = "CaptainComission_91";
			}
			if(pchar.GenQuest.CaptainComission.AfterTavernSpeak == "badSpeak")
			{
				dialog.text = "Благодарю вас, капитан. Не знаю, от чьего имени вы действуете, но плохая свобода всегда лучше хорошего рабства.";
				link.l1 = "О чём это вы?";
				link.l1.go = "CaptainComission_92";
			}
		break;
		
		case "CaptainComission_91":
			dialog.text = "Если это не нарушит ваши планы, отвезите меня к нему пожалуйста. Я слишком устал от всего этого.";
			link.l1 = "Конечно отвезу, если удастся вырваться отсюда живыми.";
			link.l1.go = "CaptainComission_91End";
		break;
		
		case "CaptainComission_91End":
			pchar.GenQuest.CaptainComission = "toOurTavern";
			rChar = CharacterFromID("CapComission_Slave");
			LAi_SetWarriorType(rChar);
			LAi_group_MoveCharacter(rChar, LAI_GROUP_PLAYER);
			DialogExit();
			AddDialogExitQuestFunction("CaptainComission_GeneratePatrol");
		break;
		
		case "CaptainComission_92":
			dialog.text = "Могу я узнать имена людей, которые заплатили вам за моё освобождение?";
			link.l1 = "Ну, положим, мне никто ничего не платил... Мне просто не оставили выбора.";
			link.l1.go = "CaptainComission_93";
		break;
		
		case "CaptainComission_93":
			dialog.text = "Итак, мои опасения подтверждаются. Вас заставили это сделать " + NationNamePeople(sti(pchar.GenQuest.CaptainComission.Nation)) + "?";
			link.l1 = "Да, это " + pchar.GenQuest.CaptainComission.Name + " из " + XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Gen") + ".";
			link.l1.go = "CaptainComission_94";
		break;		
		
		case "CaptainComission_94":
			iNation = FindEnemyNation2NationWithoutPirates(sti(pchar.GenQuest.CaptainComission.Nation));	// mitrokosta
			if(iNation == -1) iNation(rand(3));
			pchar.GenQuest.CaptainComission.SlaveCity = FindAlliedColonyForNation(iNation, true);
			pchar.GenQuest.CaptainComission.EnemyNation = iNation;
			LAi_SetImmortal(npchar, true);// лесник . откатил .  и защиту  чтоб умники не убили.
			dialog.text = "Ясно... Не знаю, что они вам пообещали, но предлагаю сделку: вы меня доставите в таверну " + XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.SlaveCity + "Gen") + ", где я буду действительно в безопасности, а я поделюсь с вами частью информации, которой обладаю.";
			link.l1 = "Годится. Тем более, что они ничего и не обещали. Идите за мной, я провожу вас на корабль.";
			link.l1.go = "CaptainComission_95";
			link.l2 = "Я не стану рисковать получить неприятности из-за какой-то информации сомнительного толка.";
			link.l2.go = "CaptainComission_96";
		break;	
		
		case "CaptainComission_95":
		AddQuestRecord("CaptainComission1", "12"); // поставил запись в СЖ лесник
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("","а"));
			AddQuestUserData("CaptainComission1", "sSex1", GetSexPhrase("ся","ась"));
			AddQuestUserData("CaptainComission1", "sName", pchar.GenQuest.CaptainComission.SlaveName);
			AddQuestUserData("CaptainComission1", "sSum", pchar.GenQuest.CaptainComission.SlaveMoney);
			AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.SlaveCity + "Acc"));
			pchar.GenQuest.CaptainComission = "toEnemyTavern";
			DialogExit();
			AddDialogExitQuestFunction("CaptainComission_GeneratePatrol");
		break;
		
		case "CaptainComission_96":
			dialog.text = "К сожалению, я не могу вам открыть её свойства сейчас. Это может навредить нам обоим.";
			link.l1 = "Тем более... Следуйте за мной и не вздумайте чудить. Считайте, что вы опять под арестом.";
			link.l1.go = "CaptainComission_97";
		break;
		
		case "CaptainComission_97":	
            AddQuestRecord("CaptainComission1", "13");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("","а"));
			AddQuestUserData("CaptainComission1", "sName", pchar.GenQuest.CaptainComission.SlaveName);
			AddQuestUserData("CaptainComission1", "sSum", pchar.GenQuest.CaptainComission.SlaveMoney);		
			pchar.GenQuest.CaptainComission = "toTavern";
			DialogExit();
			AddDialogExitQuestFunction("CaptainComission_GeneratePatrol");
		break;
		
		case "CaptainComission_100":		
			dialog.text = "Спасибо вам, капитан. вот теперь я действительно в безопасности. Не предлагаю вам денег, так как уверен, что знания и их умелое использование стоят гораздо больше, чем этот тленный металл.";
			link.l1 = "Жду обещанной информации.";
			link.l1.go = "CaptainComission_101";
		break;
		
		case "CaptainComission_101":
			GetSlaveSpeciality();
			dialog.text = "Дело в том, что я учёный, специалист " + pchar.GenQuest.CaptainComission.SlaveSpeciality + " и " + NationNamePeople(sti(pchar.GenQuest.CaptainComission.EnemyNation)) + " давно предлагали мне сотрудничество," + 
				"но я, как военный инженер, оставался верен присяге. Тогда меня попытались выкрасть. Но это было ещё полбеды, настоящий кошмар начался, когда предводители пиратов узнали о важности моей персоны.\n"+
				"В конце концов им удалось меня выкрасть, но они жаждали золота, а знания мои им были ни к чему. Заинтересованные стороны - как мои союзники, так и противники, почему-то тянули с выкупом, так я оказался на плантациях... Ну а дальше вы знаете.";
			link.l1 = "Да уж - горе от ума, иначе и не скажешь.";	
			link.l1.go = "CaptainComission_102";
		break;
		
		case "CaptainComission_102":
			switch(sti(pchar.GenQuest.CaptainComission.Speciality))
			{
				case 0:
					sTemp = "защищать судно и команду во время боя.";
				break;	
				case 1:
					sTemp = "быстро заряжать орудия и вести прицельный артиллерийский огонь в условиях морской качки.";
				break;					
				case 2:
					sTemp = "быстро обращаться с парусами и маневрировать судном во время боя.";
				break;					
			}
			dialog.text = "Ну, можно выразиться и так. Если вы меня внимательно выслушаете, то станете на голову выше своих противников в умении " + sTemp;
			link.l1 = "Благодарю вас, полученная информация действительно очень полезна.";
			link.l1.go = "CaptainComission_103";
		break;
		
		case "CaptainComission_103":
			dialog.text = "Ну что ж, до свидания и спасибо вам за всё.";
			link.l1 = "И вам спасибо. Прощайте и больше не попадайтесь.";
			link.l1.go = "CaptainComission_104";
		break;
		
		case "CaptainComission_104":
			AddQuestRecord("CaptainComission1", "21");
			CloseQuestHeader("CaptainComission1");
			// а теперь раздача слонов !!!!!!!
			switch(sti(pchar.GenQuest.CaptainComission.Speciality))
			{
				case 0:
					if(drand(1) == 0) 
					{
						AddCharacterSkill(pchar, SKILL_DEFENCE, 10);
					}
					else
					{
						AddCharacterSkill(pchar, SKILL_REPAIR, 10);
					}					
				break;
				case 1:
					if(drand(1) == 0) 
					{
						AddCharacterSkill(pchar, SKILL_CANNONS, 10);
					}
					else
					{
						AddCharacterSkill(pchar, SKILL_ACCURACY, 10);
					}	
				break;
				case 2:
					AddCharacterSkill(pchar, SKILL_SAILING, 10);
				break;
			}
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "","OpenTheDoors", -1.0);
			NPChar.lifeDay = 0;
			DeleteAttribute(pchar,"GenQuest.CaptainComission");
			DialogExit();
		break;
		// Генератор "Поручение капитана"
		
		// Генератор "Операция Галеон"
		case "CaptainComission_300":
			ReOpenQuestHeader("CaptainComission2");
			AddQuestRecord("CaptainComission2", "1");
			AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.CapName);
			AddQuestUserData("CaptainComission2", "sShipType", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name") + "Gen"))); //ПРАВКА
			AddQuestUserData("CaptainComission2", "sShipName", pchar.GenQuest.CaptainComission.ShipTypeName);
			AddQuestUserData("CaptainComission2", "sCapName",  pchar.GenQuest.CaptainComission.Name);
			AddQuestUserData("CaptainComission2", "sCity1", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Dat"));
			AddQuestUserData("CaptainComission2", "sShipTypeNom", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name"))));
			AddQuestUserData("CaptainComission2", "sCity2", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City1 + "Gen"));
			AddQuestUserData("CaptainComission2", "sCity11", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Gen"));			
			SetFunctionLocationCondition("CaptainComission_GenerateQuestContinuation", GetArealByCityName(pchar.GenQuest.CaptainComission.City), false);
			SetFunctionTimerCondition("CaptainComission_TimeIsOver", 0, 0, 15, false);
			SaveCurrentQuestDateParam("GenQuest.CaptainComission");
			LAi_KillCharacter(NPChar);
			LAi_SetPlayerType(pchar); 
			pchar.GenQuest.CaptainComission = "Begin_1";
			LAi_EnableReload();
			Log_SetActiveAction("Reload");
			DialogExit();			
		break;
		
		// диалог с кэпом на палубе 
		case "CaptainComission_301":
		    if (!CheckAttribute(pchar,"GenQuest.pizdezh_uze_bil")) // проверка если разговор уже состоялся . чтобы не повторяться. лесник
			{
			pchar.quest.CaptainComission_TimeIsOver.over = "yes";
			dialog.text = RandPhraseSimple("Здравствуйте, я капитан " + GetFullName(NPChar) + ", что привело вас на палубу моего корабля '" + pchar.GenQuest.CaptainComission.ShipTypeName + "'?","Здравствуйте, я всегда рад гостям на борту своего судна. Капитан " + GetFullName(NPChar) + " к вашим услугам.");
			link.l1 = "Здравствуйте, я капитан " + GetFullName(pchar) +", действую по поручению некоего капитана по имени " + pchar.GenQuest.CaptainComission.CapName +". Он просил передать, что в " + XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Dat") + " вас ждёт арест. Властям стала известна информация насчёт какого-то судна, если не ошибаюсь " + GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipTypeVictim),"Name") + "Gen")) + "."; // ПРАВКА
			link.l1.go = "CaptainComission_302";
			break;
			}
			dialog.text = "Какого чёрта вы тут делаете? Мы обо всём уже договорились! Отправляйтесь обратно на свой корабль!";
			link.l2 = "Эмм..Да, точно!";
			link.l2.go = "exit";
			NextDiag.TempNode = "CaptainComission_301"; // чтобы не было перехода на баг  - и т.д.  лесник 
			
		break;
		
		case "CaptainComission_302":
			dialog.text = "Ах, какая неудача! Погодите, дайте соображу...\nА где сам капитан " + pchar.GenQuest.CaptainComission.CapName + "?";
			link.l1 = "Он погиб.";
			link.l1.go = "CaptainComission_303";
		break;
		
		case "CaptainComission_303":
			dialog.text = "Чёрт! Час от часу не легче... Послушайте, " + GetFullName(pchar) + ", я совсем не готов к такому повороту событий. Мы с этим капитаном условились встретиться в " + XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Dat") + ", чтобы загрузить к нему на борт кое-какой товар. Теперь же выясняется, что он погиб, а я не могу даже появиться в поселении, чтоб организовать вывоз.\nПохоже, у меня просто нет другого выхода, кроме как просить помощи у вас.";
			link.l1 = "Моё согласие будет зависеть от того, какого рода помощь вам нужна.";
			link.l1.go = "CaptainComission_304";
		break;
		
		case "CaptainComission_304":
			pchar.GenQuest.CaptainComission.ShoreLocation = SelectQuestShoreLocationFromSea(GetArealByCityName(pchar.GenQuest.CaptainComission.City));
			dialog.text = "Помогите мне людьми и шлюпками, чтобы вывезти груз из " + XI_ConvertString(pchar.GenQuest.CaptainComission.ShoreLocation + "Gen") + ", а за это заберёте всё, что не войдёт в мой трюм.";
			link.l1 = "Хм, похоже вы откусили слишком большой кусок и теперь не можете его проглотить.";
			link.l1.go = "CaptainComission_305";
			link.l2 = "К сожалению, обстоятельства не позволяют мне тратить на это время.";
			link.l2.go = "CaptainComission_306";
		break;
		
		case "CaptainComission_305":
			sTemp = GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipTypeVictim),"Name") + "Acc")); // ПРАВКА
			dialog.text = "Ну хорошо, чтоб не водить вас за нос, расскажу всё по порядку.\n" +
				"Во время одного из патрульных рейдов мне повстречалось судно, шедшее под флагом " + NationNameGenitive(sti(pchar.GenQuest.CaptainComission.Nation)) + ". Приказ лечь в дрейф был проигнорирован. " +
				"Когда после короткой погони мы настигли " + sTemp + " '" + pchar.GenQuest.CaptainComission.VictimShipName + "', беглецы подняли пиратский флаг. Поскольку дело было уже далеко от форта, пришлось принимать бой в одиночку. Нам повредили утлегарь, поэтому абордажа избежать не удалось.\n" + 
				"Мы уже приготовились было к смерти, но, благодаря Пресвятой Деве Марии и взводу мушкетёров, нам удалось перебить пиратов. Каково же было наше ликование, когда обнаружилось, что трюм корабля под завязку набит " + GetStrSmallRegister(XI_ConvertString(Goods[sti(pchar.GenQuest.CaptainComission.Goods)].Name + "Abl")) + ". " +  //ПРАВКА корабля
				"Мы решили, что это Знак Божий и достойная компенсация за наши раны и смерть товарищей...\nК тому времени уже сгустились сумерки. Мы завели " + sTemp +" в ближайшую бухту, содержимое трюма вывезли на берег и надёжно спрятали, а " + sTemp + " отогнали подальше в море и взорвали. Наутро я отрапортовал по службе о потоплении пиратского судна, но ни слова не упомянул о содержимом трюма.";
			link.l1 = "Но видать, кто-то всё-таки проболтался...";	
			link.l1.go = "CaptainComission_307";
		break;
		
		case "CaptainComission_306":
			dialog.text = "Очень жаль, капитан... очень жаль, что вы не хотите мне помочь.";
			link.l1 = "Тут не в желании дело, уважаемый. Вы же сами понимаете... До свидания...";
			link.l1.go = "CaptainComission_306End";			
		break;
		
		case "CaptainComission_306End":
			AddQuestRecord("CaptainComission2", "3");
			AddQuestUserData("CaptainComission2", "sSex", GetSexPhrase("","а"));
			AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.CapName);
			CloseQuestHeader("CaptainComission2");
			GetCharacterPos(pchar, &locx, &locy, &locz);
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", LAi_FindNearestLocator("reload", locx, locy, locz), "none", "", "", "", 1.5);			
			pchar.GenQuest.CaptainComission = "close";
			SetFunctionExitFromLocationCondition("CaptainComission_ExitFromLoc", pchar.location, false);
			DialogExit();
		break;
		
		case "CaptainComission_307":
			dialog.text = "Я не думаю, что это мои люди. Скорее всего, это владелец груза пытается отыграться за свою неудачу.\nНу так что? могу я рассчитывать на вашу помощь?";
			link.l1 = "Да пожалуй, мне это интересно.";
			link.l1.go = "CaptainComission_308";
			link.l2 = "Нет, уважаемый. Во-первых: я не знаю, сколько товара придется на мой трюм, а во-вторых: нет гарантии, что власти его не нашли и не вывезли, а у тайника не оставили засаду.";
			link.l2.go = "CaptainComission_309";
		break;
		
		case "CaptainComission_308":
			dialog.text = "Тогда давайте встретимся " + XI_ConvertString(pchar.GenQuest.CaptainComission.ShoreLocation + "Dat") + " сразу после полуночи, а то при моём нынешнем положении маячить на рейде слишком опасно. Как бы нас не обнаружил патруль.";
			link.l1 = "Хорошо, ждите меня там.";
			link.l1.go = "CaptainComission_313";
//			bQuestDisableMapEnter = true;
		break;
		
		case "CaptainComission_309":
			dialog.text = "Очень жаль, но вы не оставляете мне выбора. Одного " + GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name") + "Gen")) + " недостаточно, чтоб вывезти весь груз, ради которого я пожертвовал успешной карьерой и рискую жизнью. Да и ваша команда, в отличие от вас, наверняка будет не против помочь мне взамен на свою долю.";
			link.l1 = "И что вы предлагаете?";
			link.l1.go = "CaptainComission_310";
		break;
		
		case "CaptainComission_310":
			dialog.text = "Я заберу ваше судно, а вас оставлю " + XI_ConvertString(pchar.GenQuest.CaptainComission.ShoreLocation + "Dat") + ".";
			link.l1 = "Вряд ли это у вас получится. Я вернусь к себе на борт, даже если для этого мне придётся вырезать всю вашу команду.";
			link.l1.go = "CaptainComission_311";
			link.l2 = "Похоже, вы тоже не оставляете мне выбора. Что ж, вынужден"+ GetSexPhrase("","а") +" подчиниться насилию...";
			link.l2.go = "CaptainComission_312";
		break;
		
		case "CaptainComission_311":
			pchar.GenQuest.CaptainComission.FightAfterDeck = true; //после резни на палубе - драка в море		
			GetCharacterPos(pchar, &locx, &locy, &locz);
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", LAi_FindNearestLocator("reload", locx, locy, locz), "none", "", "", "CaptainComission_FightInDeck", 3.5);
			DialogExit();
		break;
		
		case "CaptainComission_312":
			DialogExit();
			AddDialogExitQuestFunction("CaptainComission_toShore");
		break;
		
		case "CaptainComission_313": 		
			NextDiag.TempNode = "CaptainComission_314";
			NextDiag.CurrentNode = NextDiag.TempNode;
			AddQuestRecord("CaptainComission2", "7");
			AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);
			AddQuestUserData("CaptainComission2", "sGoods", GetStrSmallRegister(XI_ConvertString(Goods[sti(pchar.GenQuest.CaptainComission.Goods)].Name + "Gen")));
			AddQuestUserData("CaptainComission2", "sShoreName", XI_ConvertString(pchar.GenQuest.CaptainComission.ShoreLocation + "Gen"));
			AddQuestUserData("CaptainComission2", "sShoreNameDat", XI_ConvertString(pchar.GenQuest.CaptainComission.ShoreLocation + "Acc"));
			SetFunctionTimerCondition("CaptainComission_SailToShore", 0, 0, 1, false);
		    pchar.GenQuest.pizdezh_uze_bil = "true"; // лесник временная запоминалка для диалога 
			DialogExit();			
		break;
		
		case "CaptainComission_314":
			NextDiag.TempNode = "CaptainComission_314";
			dialog.text = "Капитан, нам нужно торопиться. Я боюсь, как бы нас не обнаружил патруль.";
			link.l1 = "Хорошо, давайте поторопимся.";
			link.l1.go = "exit";
		break;
		
		case "CaptainComission_315":
			dialog.text = "Капитан, прикажите спустить все шлюпки. Придётся сделать не одну ходку, а я боюсь, что в бухту может зайти патруль.";
			link.l1 = "Не волнуйтесь, всё будет в лучшем виде. Шлюпки уже подходят к берегу.";
			link.l1.go = "CaptainComission_316";
		break;
		
		case "CaptainComission_316":
			dialog.text = "Ах, чёрт! А вот и гости пожаловали...";
			link.l1 = "Не даром в народе говорят - вспомни дурака, и он появится...";
			link.l1.go = "exit";		
			DeleteAttribute(pchar,"GenQuest.pizdezh_uze_bil"); // удаление проверки на повтор диалога лесник
			AddDialogExitQuestFunction("CaptainComission_GenerateShorePatrol");
		break;
		
		// диалог с патрулем на берегу
		case "CaptainComission_317":
			dialog.text = "Капитан, мы разыскиваем военного преступника, укрывшего от властей ценный груз. Предъявите ваши документы.";
			link.l1 = "Офицер, какие документы? Мы высадились для пополнения запасов пресной воды.";
			link.l1.go = "CaptainComission_318";
		break;
		
		case "CaptainComission_318":
			dialog.snd = "Voice\COGU\COGU004"; 
			dialog.text = "А вот, похоже, и он собственной персоной. Сдать оружие и следуйте за мной... Оба.";
			link.l1 = "Эх, офицер, как же вы не вовремя...";
			link.l1.go = "CaptainComission_319";
		break;
		
		case "CaptainComission_319":
			DialogExit();
			for (i = 1; i <= sti(pchar.GenQuest.CaptainComission.SoldierQty); i++)
			{
    			sTemp = "SoldierIDX" + i;
				sld = GetCharacter(sti(pchar.GenQuest.CaptainComission.(sTemp)));
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "CoastalGuards");
            }
			
			LAi_group_SetHearRadius("CoastalGuards", 100.0);			
		    sld = characterFromId("CapComission_1");
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);		
			LAi_group_SetRelation("CoastalGuards", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("CoastalGuards", LAI_GROUP_PLAYER, true);
            LAi_SetFightMode(Pchar, true);
				
		break;
		
		case "CaptainComission_320":
		    pchar.quest.CaptainComission_Capitan_Cdoxul.over = "yes"; // лесник . снял событие если жив.
			pchar.GenQuest.CaptainComission.GoodsQty = makeint((sti(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipTypeVictim),"Capacity")) - sti(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Capacity")) + rand(250)) / sti(Goods[sti(pchar.GenQuest.CaptainComission.Goods)].Weight));	
			pchar.GenQuest.CaptainComission.GoodsQtyNorm = sti(pchar.GenQuest.CaptainComission.GoodsQty);
			dialog.text = "Нам нужно спешить, пока сюда не нагрянуло подкрепление. Загрузка уже подходит к концу, на вашу долю пришлось " + pchar.GenQuest.CaptainComission.GoodsQty + " шт. " + GetStrSmallRegister(XI_ConvertString(Goods[sti(pchar.GenQuest.CaptainComission.Goods)].Name + "Gen")) +".";
			link.l1 = "Великолепно. Пора уходить. Приятно было иметь с вами дело.";
			link.l1.go = "CaptainComission_321";
		break;
		
		case "CaptainComission_321":		
			iTmp = FindNonEnemyColonyForAdventure(sti(pchar.GenQuest.CaptainComission.Nation),pchar.GenQuest.CaptainComission.City, true);			
			sTemp = Colonies[iTmp].id;
			pchar.GenQuest.CaptainComission.ConvoyIsland = GetArealByCityName(sTemp);
			pchar.GenQuest.CaptainComission.ConvoyShore = SelectQuestShoreLocationFromSea(pchar.GenQuest.CaptainComission.ConvoyIsland);
			pchar.GenQuest.CaptainComission.ConvoyCity = sTemp;
			dialog.text = "Ещё одна просьба. Власти наверняка организуют погоню, вы не могли бы сопроводить моё судно до " + XI_ConvertString(pchar.GenQuest.CaptainComission.ConvoyShore + "Gen") + ", что на " + XI_ConvertString(GetIslandByCityName(sTemp) + "Dat") + "?";
			link.l1 = "Нет, уважаемый, дальше каждый сам за себя. Прощайте...";
			link.l1.go = "CaptainComission_322";
			if (GetCompanionQuantity(pchar) < COMPANION_MAX)
			{
				link.l2 = "Конечно мог"+ GetSexPhrase("","ла") +" бы, если вознаграждение будет соответствующим.";
				link.l2.go = "CaptainComission_323";
			}				
		break;
		
		case "CaptainComission_322":
			Group_DeleteGroup("Sea_CapComission_1"); 
			sld = characterFromId("CapComission_1");
			GetCharacterPos(pchar, &locx, &locy, &locz);
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", LAi_FindNearestFreeLocator("reload", locx, locy, locz), "none", "", "", "OpenTheDoors", 5.0);
			sld.lifeDay = 0; 	
			CaptainComission_GenerateCoastalPatrol();
			iGoods = GetSquadronFreeSpace(pchar, sti(pchar.GenQuest.CaptainComission.Goods)); 
			if(iGoods < sti(pchar.GenQuest.CaptainComission.GoodsQty)) pchar.GenQuest.CaptainComission.GoodsQty = iGoods;
			SetCharacterGoods(pchar, sti(pchar.GenQuest.CaptainComission.Goods), GetCargoGoods(pchar, sti(pchar.GenQuest.CaptainComission.Goods)) + sti(pchar.GenQuest.CaptainComission.GoodsQty));// перегруз
			AddQuestRecord("CaptainComission2", "10");
			AddQuestUserData("CaptainComission2", "sGoodsQuantity", pchar.GenQuest.CaptainComission.GoodsQty);
			AddQuestUserData("CaptainComission2", "sGoods", GetStrSmallRegister(XI_ConvertString(Goods[sti(pchar.GenQuest.CaptainComission.Goods)].Name + "Gen")));
			CloseQuestHeader("CaptainComission2");	
			DeleteAttribute(pchar, "GenQuest.CaptainComission");		
			DialogExit();
		break;
		
		case "CaptainComission_323":
			sld = characterFromId("CapComission_1");
			Fantom_SetCharacterGoods(sld, sti(pchar.GenQuest.CaptainComission.Goods), GetCargoFreeSpace(sld), 1);
			pchar.GenQuest.CaptainComission.ConvoyMoney = makeint((sti(pchar.rank)*100 + sti(NPChar.rank)*170 + cRand(30)*20) * 2.5);
			pchar.GenQuest.CaptainComission.iDay  = 15 + cRand(10);
			iGoods = GetSquadronFreeSpace(pchar, sti(pchar.GenQuest.CaptainComission.Goods)); 
			if(iGoods < sti(pchar.GenQuest.CaptainComission.GoodsQty)) pchar.GenQuest.CaptainComission.GoodsQty = iGoods;
			SetCharacterGoods(pchar, sti(pchar.GenQuest.CaptainComission.Goods), GetCargoGoods(pchar, sti(pchar.GenQuest.CaptainComission.Goods)) + sti(pchar.GenQuest.CaptainComission.GoodsQty));// перегруз
			dialog.text = "Это само собой разумеется. За эскорт я готов заплатить " + pchar.GenQuest.CaptainComission.ConvoyMoney + " песо. Но при условии, что мы потратим не более " + pchar.GenQuest.CaptainComission.iDay + " дней. Это важно.";	
			link.l1 = "По рукам. Уходим немедленно.";
			link.l1.go = "CaptainComission_324";
			NextDiag.TempNode = "CaptainComission_325";
			NextDiag.CurrentNode = NextDiag.TempNode;
		break;
		
		case "CaptainComission_324":
			pchar.GenQuest.CannotWait = 1; // лочим интерфейс отдыха 
			sld = characterFromId("CapComission_1");
			sTemp = LAi_FindNearestFreeLocator2Pchar("reload");
			LAi_SetActorType(sld);
			LAi_ActorSetStayMode(sld);
			CharacterIntoCompanionAndGoOut(pchar, sld, "reload", sTemp, 5, false);
			SetShipRemovable(sld, false);
			SetCharacterRemovable(sld, false);
			Group_ChangeCharacter(PLAYER_GROUP, "CapComission_1");
			AddQuestRecord("CaptainComission2", "11");
			AddQuestUserData("CaptainComission2", "sSex", GetSexPhrase("","а"));
			AddQuestUserData("CaptainComission2", "sGoodsQuantity", pchar.GenQuest.CaptainComission.GoodsQty);
			AddQuestUserData("CaptainComission2", "sGoods", GetStrSmallRegister(XI_ConvertString(Goods[sti(pchar.GenQuest.CaptainComission.Goods)].Name + "Gen")));		
			AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);
			AddQuestUserData("CaptainComission2", "sShoreName", XI_ConvertString(pchar.GenQuest.CaptainComission.ConvoyShore + "Gen"));
			AddQuestUserData("CaptainComission2", "sShoreType", XI_ConvertString(GetIslandByCityName(pchar.GenQuest.CaptainComission.ConvoyCity) + "Dat"));
			AddQuestUserData("CaptainComission2", "sSum", pchar.GenQuest.CaptainComission.ConvoyMoney);
			CaptainComission_GenerateCoastalPatrol();
			pchar.quest.CaptainComission_MapEnter.win_condition.l1 = "MapEnter";
			pchar.quest.CaptainComission_MapEnter.function = "CaptainComission_MapEnter"; 
			pchar.quest.CaptainComission_CapShip_Sink.win_condition.l1 = "Character_sink";
			pchar.quest.CaptainComission_CapShip_Sink.win_condition.l1.character = "CapComission_1";
			pchar.quest.CaptainComission_CapShip_Sink.function = "CaptainComission_CapShip_Sink";
			DialogExit();
		break;
		
		case "CaptainComission_325":
			NextDiag.TempNode = "CaptainComission_314";
			dialog.text = LinkRandPhrase("Капитан, мы теряем время. Нас в любую минуту могут обнаружить.","Капитан, время играет против нас. Не забывайте, что меня ищут.","Капитан, промедление недопустимо. Мой " + GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name"))) + " слишком приметен для патруля.");
			link.l1 = LinkRandPhrase("Да, вы правы, нужно спешить...","Так грузитесь в шлюпки без лишних разговоров.","Всё... Собирайте своих людей. Уходим.");
			link.l1.go = "exit";
		break;
		
		case "CaptainComission_326_0":
			dialog.text = "Капитан, мне необходимо поговорить с моими людьми.";
			link.l1 = "Разрешаю.";
			link.l1.go = "exit";
			InterfaceStates.Buttons.Save.enable = false; 
			AddDialogExitQuestFunction("CaptainComission_DialogInShore");
		break;
		
		case "CaptainComission_326":
			sld = characterFromId("Blaze");
			dialog.text = "Приветствую вас, капитан " + pchar.CaptainComission.Name + ". Ну что, весь груз привезли? А где капитан " + pchar.CaptainComission.CapName + "?";
			link.l1 = pchar.CaptainComission.CapName + " погиб. Пришлось воспользоваться услугами это"+ NPCharSexPhrase(sld, "го джентльмена","й леди") +". Разрешите представить, капитан " + pchar.CaptainComission.FullName + ".";
			link.l1.go = "CaptainComission_327";
		break;
		
		case "CaptainComission_327":
			sld = characterFromId("Blaze");
			dialog.text = "А "+ NPCharSexPhrase(sld, "что он за тип? Он","кто она такая? Она") +" в курсе наших дел?";
			link.l1 = "В общих чертах, да. Но есть нюанс - "+ NPCharSexPhrase(sld, "он уверен","она уверена") +", что половина груза принадлежит "+ NPCharSexPhrase(sld, "ему","ей") +". Нужно убедить "+ NPCharSexPhrase(sld, "его","ее") +", что это не совсем так.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("CaptainComission_GangDialog");
		break;
		
		case "CaptainComission_328":
			dialog.text = "Уважаем"+ GetSexPhrase("ый","ая") +" " + GetFullName(pchar) +", всё, что вам следовало знать, вы уже услышали. Нам нужен доступ к вашему трюму.";
			link.l1 = "Вы думаете, мои ребята будут спокойно смотреть, как какие-то голодранцы чистят их трюм?";
			link.l1.go = "CaptainComission_329";
		break;
		
		case "CaptainComission_329":
			pchar.GenQuest.CaptainComission.GoodsSum = 2 * sti(pchar.GenQuest.CaptainComission.GoodsQtyNorm) * sti(Goods[sti(pchar.GenQuest.CaptainComission.Goods)].Cost);
			dialog.text = "Тоже верно. Наличная сумма, скажем " + pchar.GenQuest.CaptainComission.GoodsSum + " песо, избавит нас от необходимости конфликтовать с вашей командой. Обратите внимание - это стоимость половины нашего товара, так что всё справедливо... Соглашайтесь, и никто не пострадает.";
			link.l1 = "А если я откажусь?";
			link.l1.go = "CaptainComission_330";
		break;
		
		case "CaptainComission_330":
			dialog.text = "Тогда насилия избежать не удастся. Но вы станете первой жертвой и обретёте покой в этой уютной бухте, а команда вашего судна просто не успеет прийти вам на помощь... Как вам такая перспектива?";
			link.l1 = "Вы не оставляете мне выбора. Я вынужден"+ GetSexPhrase("","а") +" принять бой.";
			link.l1.go = "CaptainComission_331";
			if(sti(pchar.money) >= sti(pchar.GenQuest.CaptainComission.GoodsSum))
			{
				link.l2 = "Похоже у меня нет выбора. Вот ваши деньги.";
				link.l2.go = "CaptainComission_332";
			}	
		break;
		
		case "CaptainComission_331":
			dialog.text = "Что ж, решение достойное "+ GetSexPhrase("благородного джентльмена","отважной леди") +".";
			link.l1 = "Хватит философствовать! давайте ближе к делу!";
			link.l1.go = "CaptainComission_334";
			CaptainComission_ChangeCaptain();
		break;
		
		case "CaptainComission_332":
			dialog.text = "Разумное решение. Всего вам наилучшего.";
			link.l1 = "Чтоб вы подавились...";
			link.l1.go = "CaptainComission_333";
		break;
		
		case "CaptainComission_333":
		    LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);// лесник - разрешить снова драться после сдачи денег. но после драки кулаками не машут ..как говориться))
			addMoneyToCharacter(pchar, -sti(pchar.GenQuest.CaptainComission.GoodsSum));
			AddQuestRecord("CaptainComission2", "17");
			AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);
			AddQuestUserData("CaptainComission2", "sShoreName", UpperFirst(XI_ConvertString(pchar.GenQuest.CaptainComission.ConvoyShore + "Gen")));
			AddQuestUserData("CaptainComission2", "sSum", pchar.GenQuest.CaptainComission.GoodsSum);
			CloseQuestHeader("CaptainComission2");	
			ChangeOfficersLoyality("bad_all", 1);
			DialogExit();
			AddDialogExitQuestFunction("CaptainComission_GangExit");
		break;

		case "CaptainComission_334":
			LAi_SetPlayerType(pchar);
			sTemp = "Gang_";
			sGroup = "GangGroup_0";			
			LAi_LocationFightDisable(&locations[FindLocation(pchar.GenQuest.CaptainComission.ConvoyShore)], false);	
			iTemp = sti(pchar.GenQuest.CaptainComission.GangNum);
			chrDisableReloadToLocation = true;
			rChar = CharacterFromID("CapComission_1");
			LAi_SetWarriorType(rChar);
			LAi_group_MoveCharacter(rChar, sGroup);
			for(i = 0; i < iTemp; i++)
			{
				rChar = CharacterFromID(sTemp + i);
				LAi_SetWarriorType(rChar);
				LAi_group_MoveCharacter(rChar, sGroup);
				LAi_SetImmortal(rChar, false);
			}			
			LAi_group_SetRelation(sGroup, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups(sGroup, LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck(sGroup, "OpenTheDoors"); 
			LAi_group_SetCheckFunction(sGroup, "CaptainComission_GangDied");
			DialogExit();	
			AddDialogExitQuest("MainHeroFightModeOn");		
		break;

		case "CaptainComission_340":
			dialog.text = "Капитан " + GetFullName(pchar) + ", мы опоздали. Я думаю, вы понимаете, что о вознаграждении не может быть и речи.";
			link.l1 = "Конечно понимаю. Я и так немало заработал"+ GetSexPhrase("","а") +" благодаря вам. Прощайте...";
			link.l1.go = "CaptainComission_341";
		break;
		
		case "CaptainComission_341":
			Group_DeleteGroup("Sea_CapComission_1");			
			LAi_SetImmortal(NPChar, true);
			GetCharacterPos(pchar, &locx, &locy, &locz);
			LAi_SetActorType(NPChar);
			LAi_ActorGoToLocation(NPChar, "reload", LAi_FindNearestLocator("reload", locx, locy, locz), "none", "", "", "OpenTheDoors", 5.0);
			NPChar.lifeDay = 0; 						
			AddQuestRecord("CaptainComission2", "15");
			AddQuestUserData("CaptainComission2", "sSex", GetSexPhrase("ся","ась"));
			AddQuestUserData("CaptainComission2", "sSex1", GetSexPhrase("","а"));
			AddQuestUserData("CaptainComission2", "sShipType", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name")))); 
			AddQuestUserData("CaptainComission2", "sShipName", pchar.GenQuest.CaptainComission.ShipTypeName);
			AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);
			CloseQuestHeader("CaptainComission2");	
			DeleteAttribute(pchar, "GenQuest.CaptainComission");					
			DialogExit();
		break;
		
		case "CaptainComission_Canoneer":
			dialog.text = "Не угостите ромом старого вояку, пострадавшего в жестоких морских сражениях во славу короны?";
			link.l1 = "Рому нам, трактирщик!..";
			link.l1.go = "exit";
			NextDiag.TempNode = "CaptainComission_Canoneer1";
			NextDiag.CurrentNode = NextDiag.TempNode;
			AddDialogExitQuest("CaptainComission_TalkCanoneer");
		break;
		
		case "CaptainComission_Canoneer1":
			dialog.text = "Вот спасибо, " + GetAddress_Form(pchar) + ", вот уважили инвалида, потерявшего память...";
			link.l1 = "Так уж и потерявшего?";
			link.l1.go = "CaptainComission_Canoneer2";
		break;
		
		case "CaptainComission_Canoneer2":
			dialog.text = "Начисто, госпо"+ GetSexPhrase("дин","жа") +" капитан - как обухом отшибло. Ничего не помню, только книппель, летящий прямо мне в голову. Вот, взгляните, какую он дырку в моей башке пробил. Через неё, наверное, вся память из головы и вытекла.";
			link.l1 = "Приятель, я видел"+ GetSexPhrase("","а") +" людей после прямого попадания картечи, у них память сносило вместе с головой. А ты про целый книппель байки травишь...Меня интересуют не душещипательные истории для скудоумных домохозяек, а та, в которую втянул себя и команду капитан " + pchar.GenQuest.CaptainComission.Name +"."; // лесник правка диалога (автор Эмилио Роканера)
			link.l1.go = "CaptainComission_Canoneer3";
		break;
		
		case "CaptainComission_Canoneer3":
			dialog.text = "Да это я так, нужно же чем-то на жизнь зарабатывать... А насчёт капитана мне трепаться не с руки. Если бы я за каждый вопрос о нём брал 100 монет, то уже имел бы столько золота, сколько губернатор за год со всего поселения не собирает..."; // лесник -поправил диалог
			link.l1 = "А груз, припрятанный капитаном, продать не пытался?";
			link.l1.go = "CaptainComission_Canoneer4";
		break;
		
		case "CaptainComission_Canoneer4":
			dialog.text = "Что опять ищейку подослали?! Не помню я никаких капитанов! Вам же сказано - контуженый, и справка имеется! Чего ещё надо?!";
			link.l1 = "Ладно-ладно, не кипятись. Тут такое дело... В общем, опоздал"+ GetSexPhrase("","а") +" я. Капитан " + pchar.GenQuest.CaptainComission.CapName + " просил меня предупредить, чтоб " + pchar.GenQuest.CaptainComission.Name + " не ходил в это поселение, что властям стали известны обстоятельства гибели " + GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipTypeVictim),"Name") + "Gen")) + " '" + pchar.GenQuest.CaptainComission.VictimShipName + "', и его ждёт арест.";// лесник - окончание . GEN
			link.l1.go = "CaptainComission_Canoneer5";
		break;
		
		case "CaptainComission_Canoneer5":
			dialog.text = "Тьфу-ты. Так бы сразу и говорили, а то ходите вокруг да около... Это по моей просьбе капитан " + pchar.GenQuest.CaptainComission.CapName + " взялся перехватить наш " + GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name"))) + " до того, как он вернётся из эллингов " + XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City1 + "Gen") + ". " +  //лесник правка диалога. автор - Эмилио Роканера
				"Его туда на ремонт отбуксировали после этого злополучного боя... Откуда этот пират взялся вместе с его " + GetStrSmallRegister(XI_ConvertString(Goods[sti(pchar.GenQuest.CaptainComission.Goods)].Name + "Abl")) + "?! Многие наши из-за него сложили головы... в бою... и на плахе...";
			link.l1 = "А ты-то как уцелел?";
			link.l1.go = "CaptainComission_Canoneer6";	
		break;
		
		case "CaptainComission_Canoneer6":
			dialog.text = "По ошибке. По своей же ошибке уцелел - ирония судьбы. Я шнур в крюйт-камере " + GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipTypeVictim),"Name") + "Gen")) + " коротко отрезал, вот и не успела шлюпка далеко отойти, когда порох рванул. И ведь только меня взрывной волной и выкинуло, да ещё и контузило обломком фальшборта... Ребята в темноте не нашли, а как до берега добрался - действительно не помню.";
			link.l1 = "А от дознания как отвертелся?";
			link.l1.go = "CaptainComission_Canoneer7";
		break;
		
		case "CaptainComission_Canoneer7":
			dialog.text = "А я сказал, что меня контузило ещё во время абордажа, поэтому ни о каком грузе не знаю - не ведаю. Ещё и слабоумным прикинулся, я ведь только недавно на ноги встал, перед самым приходом " + GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name") + "Gen")) + ". До этого нормально двигаться не мог, координация нарушилась от контузии."; // лесник- окончание Gen
			link.l1 = "Слушай, а кто всё-таки проболтался про груз-то?";
			link.l1.go = "CaptainComission_Canoneer8";
		break;
		
		case "CaptainComission_Canoneer8":
			dialog.text = "Пираты письмо губернатору отправили, якобы от потерпевшего купца. Решили отомстить капитану за настойчивость. Ведь если бы не его упрямство, мы бы " + GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipTypeVictim),"Name") + "Acc")) + " не догнали... да и жив бы остался капитан - голова бедовая."; // Acc лесник. - окончание
			link.l1 = "А как вы с этим пиратом столкнулись-то?";
			link.l1.go = "CaptainComission_Canoneer9";
		break;
		
		case "CaptainComission_Canoneer9":
			dialog.text = "Да чёрт его знает... Обычное патрулирование, обычное судно шедшее под флагом " + NationNameGenitive(sti(pchar.GenQuest.CaptainComission.Nation)) + ". Чего капитан решил его досмотреть - не знаю, только на предупредительный выстрел судно не отреагировало, а когда мы его настигли, пираты подняли Весёлого Роджера. " +
				"Мы уже далеко отошли от форта, поэтому пришлось несладко. Потом была абордажная свалка... до сих пор не пойму, как нам удалось одержать верх.\n" + 
				"Ну, а когда спустились в трюм и увидели, что там полно " + GetStrSmallRegister(XI_ConvertString(Goods[sti(pchar.GenQuest.CaptainComission.Goods)].Name + "Gen")) + ", тут и началась вся эта свистопляска. Не иначе сам чёрт подсунул нам эту добычу... Товар пришлось выгрузить на берег, а " + GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipTypeVictim),"Name") + "Acc")) + " взорвать - крен был почти до фальшборта, да и такелаж сильно поврежден...";// Acc лесник
			link.l1 = "Не боишься, что все ваши усилия и жертвы окажутся напрасными, если люди губернатора найдут тайник?";	
			link.l1.go = "CaptainComission_Canoneer10";
		break;
		
		case "CaptainComission_Canoneer10":
			iTmp = FindNonEnemyColonyForAdventure(sti(pchar.GenQuest.CaptainComission.Nation),pchar.GenQuest.CaptainComission.City, true);			
			pchar.GenQuest.CaptainComission.CanoneerCity = Colonies[iTmp].id;			
			pchar.GenQuest.CaptainComission.Sum = 20000 + 2000 * sti(pchar.rank);
			dialog.text = "Не найдут. Я вход в пещеру взорвал так, что комар не пролезет, я ведь лучший пиротехник во всей эскадре. Если кто и найдёт - только контрабандисты, они каждую щель на острове знают...\n" + 
				"Слушай, я давно голову ломаю, что с этим грузом делать, особенно после казни команды. В одиночку мне его ни продать, ни вывезти, тем более, что серьёзных дел с контуженым никто водить не будет... Я не хочу спекулировать на гибели товарищей, но за " + pchar.GenQuest.CaptainComission.Sum + " песо готов показать вам тайник, при условии, что после загрузки вы доставите меня в поселение " + XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.CanoneerCity) + ".";
			if(sti(pchar.money) >= sti(pchar.GenQuest.CaptainComission.Sum))	
			{
				link.l1 = "Я соглас"+ GetSexPhrase("ен","на") +". Вот деньги. Теперь твоё слово.";	
				link.l1.go = "CaptainComission_Canoneer11";
			}
			else
			{
				link.l1 = "Вот чёрт! Сиди здесь, сейчас принесу деньги.";
				link.l1.go = "CaptainComission_Canoneer12";				
			}	
			link.l2 = "Слишком дорого просишь, приятель. Да и посудины подходящей у меня нет. Удачи тебе и прощай...";
			link.l2.go = "CaptainComission_Canoneer13";
		break;
		
		case "CaptainComission_Canoneer11":
			addMoneyToCharacter(pchar, -sti(pchar.GenQuest.CaptainComission.Sum));
			pchar.GenQuest.CaptainComission.ConvoyShore = SelectQuestShoreLocationFromSea(GetArealByCityName(pchar.GenQuest.CaptainComission.City));
			pchar.GenQuest.CaptainComission.GoodsQty = makeint(sti(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipTypeVictim),"Capacity")) / sti(Goods[sti(pchar.GenQuest.CaptainComission.Goods)].Weight));
			dialog.text = "Вот и славно. Встречаемся сегодня после полуночи " + XI_ConvertString(pchar.GenQuest.CaptainComission.ConvoyShore + "Dat") + ". И позаботьтесь, чтоб в вашем трюме было место для " + pchar.GenQuest.CaptainComission.GoodsQty + " шт. " + GetStrSmallRegister(XI_ConvertString(Goods[sti(pchar.GenQuest.CaptainComission.Goods)].Name + "Gen")) + ". Жалко ведь бросать с таким трудом добытое...";
			link.l1 = "Позабочусь обязательно. До встречи в бухте...";
			link.l1.go = "CaptainComission_Canoneer14";
		break;
		
		case "CaptainComission_Canoneer12":
			AddQuestRecord("CaptainComission2", "41");
			AddQuestUserData("CaptainComission2", "sShipType", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name") + "Gen"))); //Gen лесник
			AddQuestUserData("CaptainComission2", "sShipName", pchar.GenQuest.CaptainComission.ShipTypeName);			
			AddQuestUserData("CaptainComission2", "sSum", pchar.GenQuest.CaptainComission.Sum);
			AddQuestUserData("CaptainComission2", "sName", GetName( NAMETYPE_ORIG, pchar.GenQuest.CaptainComission.CanoneerName, NAME_NOM));
			SetFunctionTimerCondition("CaptainComission_CanoneerWaitMoney", 0, 0, 1, false);
			NextDiag.TempNode = "CaptainComission_Canoneer15";
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			AddDialogExitQuest("CaptainComission_exit_sit");
		break;
		
		case "CaptainComission_Canoneer13":
			AddQuestRecord("CaptainComission2", "40");
			AddQuestUserData("CaptainComission2", "sSex", GetSexPhrase("","а"));
			AddQuestUserData("CaptainComission2", "sShipType", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name") + "Acc"))); 
			AddQuestUserData("CaptainComission2", "sShipName", pchar.GenQuest.CaptainComission.ShipTypeName);			
			AddQuestUserData("CaptainComission2", "sName", GetName( NAMETYPE_ORIG, pchar.GenQuest.CaptainComission.CanoneerName, NAME_NOM));
			AddQuestUserData("CaptainComission2", "sShipTypeQuest", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipTypeVictim),"Name") + "Acc")));
			AddQuestUserData("CaptainComission2", "sShipNameQuest", pchar.GenQuest.CaptainComission.VictimShipName);
			CloseQuestHeader("CaptainComission2");
			LAi_CharacterDisableDialog(NPChar);
			pchar.GenQuest.CaptainComission = "close";
			SetFunctionExitFromLocationCondition("CaptainComission_ExitFromLoc", pchar.location, false);
			DialogExit();
			AddDialogExitQuest("CaptainComission_exit_sit");
		break;
		
		case "CaptainComission_Canoneer14":
			AddQuestRecord("CaptainComission2", "43");
			AddQuestUserData("CaptainComission2", "sShipType", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name") + "Gen"))); 
			AddQuestUserData("CaptainComission2", "sShipName", pchar.GenQuest.CaptainComission.ShipTypeName);			
			AddQuestUserData("CaptainComission2", "sName", GetName( NAMETYPE_ORIG, pchar.GenQuest.CaptainComission.CanoneerName, NAME_NOM));
			AddQuestUserData("CaptainComission2", "sShipTypeQuest", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipTypeVictim),"Name") + "Gen")));
			AddQuestUserData("CaptainComission2", "sShipNameQuest", pchar.GenQuest.CaptainComission.VictimShipName);
			AddQuestUserData("CaptainComission2", "sSum", pchar.GenQuest.CaptainComission.GoodsQty);
			AddQuestUserData("CaptainComission2", "sGoods", GetStrSmallRegister(XI_ConvertString(Goods[sti(pchar.GenQuest.CaptainComission.Goods)].Name + "Gen")));
			AddQuestUserData("CaptainComission2", "sShoreName", XI_ConvertString(pchar.GenQuest.CaptainComission.ConvoyShore + "Acc"));			
			LAi_CharacterDisableDialog(NPChar);
			SetFunctionTimerConditionParam("CaptainComission_TimeIsOver", 0, 0, 1, MakeInt(24 - GetHour()), false);
			SetFunctionTimerCondition("CaptainComission_MeetCanoneerInShoreTimer", 0, 0, 1, false);
			DialogExit();
			AddDialogExitQuest("CaptainComission_exit_sit");
		break;
		
		case "CaptainComission_Canoneer15":
			if(sti(pchar.money) >= sti(pchar.GenQuest.CaptainComission.Sum))	
			{
				dialog.text = "Вот наконец и вы. Я уж, было, начал волноваться. Подумал, что сдадите меня властям со всеми потрохами.";
				link.l1 = "Я ещё не сош"+ GetSexPhrase("ел","ла") +" с ума. Вот деньги. Теперь твоё слово.";
				pchar.quest.CaptainComission_CanoneerWaitMoney.over = "yes";// лесник . снят таймер ожилания бабла
				link.l1.go = "CaptainComission_Canoneer11";
			}	
			else
			{
				dialog.text = "Ну и где деньги ?";	
				link.l1 = "Вот чёрт! Сиди здесь, сейчас принесу.";
				link.l1.go = "exit";
				NextDiag.TempNode = "CaptainComission_Canoneer15";
				NextDiag.CurrentNode = NextDiag.TempNode;
			}
		break;
		
		case "CaptainComission_350":
			dialog.text = "Капитан, похоже, мы опоздали. Контрабандисты всё-таки добрались до тайника.";
			link.l1 = "Я не намерен"+ GetSexPhrase("","а") +" упускать свою добычу, даже если за нею придёт сам дьявол.";
			link.l1.go = "CaptainComission_351";
			link.l2 = "Вот чёрт! Я умываю руки, разбирайся сам"+ GetSexPhrase("","а") +" со своими конкурентами.";	
			link.l2.go = "CaptainComission_352";
		break;
		
		case "CaptainComission_351":
			DialogExit();
			AddDialogExitQuest("CaptainComission_GangDialog_1");
		break;
		
		case "CaptainComission_352":
			DialogExit();
			//SetFunctionExitFromLocationCondition("CaptainComission_NoGangDialog", pchar.location, false);
			 AddDialogExitQuestFunction("CaptainComission_NoGangDialog");   // лесник - исправлено . предыдцщий код не работал
		break;
		
		case "CaptainComission_360":
			dialog.text = "Капитан, у нас здесь серьёзное мероприятие, вы бы увели свою эскадру от греха подальше, пока не подошли наши суда для загрузки.";
			link.l1 = "Джентльмены, похоже, вы пытаетесь взять то, что вам не принадлежит.";
			link.l1.go = "CaptainComission_361";
		break;
		
		case "CaptainComission_361":
			dialog.text = "Ого! Это вы с кем сейчас разговариваете?";
			link.l1 = "С тобой, милейший. У товара, который вы намерены присвоить есть владелец, интересы которого я в данный момент представляю.";
			link.l1.go = "CaptainComission_362";
		break;
		
		case "CaptainComission_362":
			dialog.text = "Да будь ты хоть мессией самого Господа Бога, мы не позволим соваться в наши дела! Очисти фарватер, если жизнь дорога!";
			link.l1 = "Тебе что, не ясно, что этот товар мой, и я без него не уйду?";
			link.l1.go = "CaptainComission_363";
		break;
		
		case "CaptainComission_363":
			dialog.text = "Чёрт бы тебя побрал! Тогда ты останешься здесь навсегда!..";
			link.l1 = "Сейчас выясним, кто здесь останется!..";
			link.l1.go = "CaptainComission_364";
		break;
				
		case "CaptainComission_364":
			LAi_SetPlayerType(pchar);
			sTemp = "Gang_";
			sGroup = "GangGroup_0";			
			LAi_LocationFightDisable(&locations[FindLocation(pchar.GenQuest.CaptainComission.ConvoyShore)], false);	
			iTemp = sti(pchar.GenQuest.CaptainComission.GangNum);
			chrDisableReloadToLocation = true;
			if(pchar.GenQuest.CaptainComission.variant == "A2")
			{
				rChar = CharacterFromID("CapComission_1");
				LAi_SetWarriorType(rChar);
				LAi_group_MoveCharacter(rChar, LAI_GROUP_PLAYER);						
			}
			if(pchar.GenQuest.CaptainComission.variant == "A3")
			{
				rChar = CharacterFromID("CapComission_Canoneer");
				//LAi_SetWarriorType(rChar);
				LAi_SetImmortal(rChar, false);
				LAi_group_MoveCharacter(rChar, LAI_GROUP_PLAYER);			
			}	
			for(i = 0; i < iTemp; i++)
			{
				rChar = CharacterFromID(sTemp + i);
				LAi_SetWarriorType(rChar);
				LAi_group_MoveCharacter(rChar, sGroup);
				LAi_SetImmortal(rChar, false);
			}			
			LAi_group_SetRelation(sGroup, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups(sGroup, LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck(sGroup, "OpenTheDoors"); 
			if(pchar.GenQuest.CaptainComission.variant == "A2")
			{
				LAi_group_SetCheckFunction(sGroup, "CaptainComission_CheckCaptainAfterBattle");
			}
			if(pchar.GenQuest.CaptainComission.variant == "A3")
			{
				LAi_group_SetCheckFunction(sGroup, "CaptainComission_CheckGangAfterBattle");
			}	
			DialogExit();	
			AddDialogExitQuest("MainHeroFightModeOn");						
		break;
		
		case "CaptainComission_365":
			dialog.text = "Капитан, прикажите поторопиться, сюда в любой момент может наведаться патруль. Да и контрабандисты явно ждали транспорт для загрузки.";
			link.l1 = "Конечно поторопимся... Быстро грузим товар в трюмы и уходим.";
			link.l1.go = "exit";
			NextDiag.TempNode = "CaptainComission_365";
			NextDiag.CurrentNode = NextDiag.TempNode;
		break;
		
		case "CaptainComission_366":
			dialog.text = "Спасибо вам капитан " + GetFullName(pchar) + ". Если бы не вы, достался бы наш груз контрабандистам, нечем было бы даже ребят помянуть, которые за него головы сложили...";
			link.l1 = "Это тебе спасибо, что поверил.";
			link.l1.go = "CaptainComission_367";
		break;
		
		case "CaptainComission_367":
			dialog.text = "Есть у меня одна вещица, благодаря которой я может быть и жив-то остался. Хочу подарить её вам, как амулет. Держите и прощайте.";
			link.l1 = "Спасибо за подарок, не ожидал"+ GetSexPhrase("","а") +". Ты бы подлечил здоровье, пока деньги не кончились.";
			link.l1.go = "CaptainComission_368";
		break;
		
		case "CaptainComission_368":
			LAi_SetActorType(NPChar);
			LAi_SetImmortal(NPChar, true);
			GetCharacterPos(pchar, &locx, &locy, &locz);
			LAi_SetActorType(NPChar);
			LAi_ActorGoToLocation(NPChar, "reload", LAi_FindNearestLocator("reload", locx, locy, locz), "none", "", "", "OpenTheDoors", 5.0);			
			NPChar.LifeDay = 0;
			GiveItem2Character(pchar, pchar.GenQuest.CaptainComission.Prize);
			AddQuestRecord("CaptainComission2", "48");
			AddQuestUserData("CaptainComission2", "sShipType", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name") + "Gen"))); // лесник окончание
			AddQuestUserData("CaptainComission2", "sShipName", pchar.GenQuest.CaptainComission.ShipTypeName);
			AddQuestUserData("CaptainComission2", "sCharName", GetName( NAMETYPE_ORIG, pchar.GenQuest.CaptainComission.CanoneerName, NAME_ABL));
			AddQuestUserData("CaptainComission2", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.CanoneerCity + "Gen"));
			CloseQuestHeader("CaptainComission2");
			DeleteAttribute(pchar, "GenQuest.CaptainComission");
			DialogExit();
		break;
		
		case "CaptainComission_370":
			if(pchar.GenQuest.CaptainComission == "MayorTalkBad")
			{
				pchar.quest.CaptainComission_TimeIsOver.over = "yes";
			}	
			dialog.text = "Похоже, у меня сегодня приёмный день...Полагаю вы ко мне?"; // лесник
			link.l1 = "Если вы и есть капитан " + pchar.GenQuest.CaptainComission.Name + ", то к вам.";
			link.l1.go = "CaptainComission_371";
		break;
		
		case "CaptainComission_371":
			dialog.text = "...бывший капитан " + pchar.GenQuest.CaptainComission.Name + "...";
			link.l1 = "Я " + GetFullName(pchar) + ", у меня есть пара вопросов.";
			link.l1.go = "CaptainComission_372";
		break;
		
		case "CaptainComission_372":
			dialog.text = "А почему вы думаете, что я стану на них отвечать?";
			link.l1 = "Капитан " + pchar.GenQuest.CaptainComission.CapName + " просил предупредить вас о том, что обстоятельства гибели " + GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipTypeVictim),"Name") + "Gen")) + " '" + pchar.GenQuest.CaptainComission.VictimShipName + "' стали известны властям, " +
				"но я не успел"+ GetSexPhrase("","а") +" перехватить ваш " + GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name"))) + " на переходе из " + XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City1 + "Gen") + ".";
			link.l1.go = "CaptainComission_373";	
		break;
		
		case "CaptainComission_373":
			dialog.text = "А где сам капитан " + pchar.GenQuest.CaptainComission.CapName + "?";
			link.l1 = "Он погиб.";
			link.l1.go = "CaptainComission_374";
		break;
		
		case "CaptainComission_374":
			dialog.text = "Ага... Вот, значит, в чём дело. Ну, теперь многое прояснилось... Итак, кто-то проболтался, что мы выпотрошили " + GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipTypeVictim),"Name") + "Acc")) + ". " +
				"Рано или поздно груз найдут, и тогда меня повесят. Капитан " + pchar.GenQuest.CaptainComission.CapName + " мёртв, значит помощи больше ждать не от кого...\nКроме, как от вас...\nКапитан " + GetFullName(pchar) + ", вытащите меня отсюда, и я щедро вас отблагодарю.";
			if(!CheckAttribute(pchar,"GenQuest.CaptainComission.GetRumour"))
			{
				if(CheckAttribute(pchar,"GenQuest.CaptainComission.SpeakMayor"))
				{
					link.l1 = "На имя губернатора поступило донесение от владельца груза. Там фигурируют внушительные цифры.";
					link.l1.go = "CaptainComission_375";
				}
				else
				{
					link.l1 = "Но вы же не думаете, что я стану помогать вслепую?";
					link.l1.go = "CaptainComission_375";
				}
			}			
			else
			{
				if(CheckAttribute(pchar,"GenQuest.CaptainComission.SpeakMayor"))
				{
					link.l1 = "На имя губернатора поступило донесение от владельца груза. Там фигурируют внушительные цифры.";
					link.l1.go = "CaptainComission_375";				
				}
				else
				{
					link.l1 = "В колонии ходят слухи, что вы связаны с контрабандистами...";
					link.l1.go = "CaptainComission_375";				
				}
			}
		break;
		
		case "CaptainComission_375":
			sTemp = GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipTypeVictim),"Name") + "Acc"));// ПРАВКА
			dialog.text = "Вижу, придётся рассказать вам всё по порядку, чтоб у вас не оставалось сомнений на мой счёт.\n" +
				"Во время одного из патрульных рейдов мне повстречалось судно, шедшее под флагом " + NationNameGenitive(sti(pchar.GenQuest.CaptainComission.Nation)) + ". Приказ лечь в дрейф был проигнорирован. " +
				"Когда после короткой погони мы настигли " + sTemp + " '" + pchar.GenQuest.CaptainComission.VictimShipName + "', беглецы подняли пиратский флаг. Поскольку дело было уже далеко от форта, пришлось принимать бой в одиночку. Нам повредили утлегарь, поэтому абордажа избежать не удалось.\n" + 
				"Мы уже приготовились было к смерти, но, благодаря Пресвятой Деве Марии и взводу мушкетёров, нам удалось перебить пиратов. Каково же было наше ликование, когда обнаружилось, что трюм корабля под завязку набит " + GetStrSmallRegister(XI_ConvertString(Goods[sti(pchar.GenQuest.CaptainComission.Goods)].Name + "Abl")) + ". " + // ПРАВКА  корабля 
				"Мы решили, что это Знак Божий и достойная компенсация за наши раны и смерть товарищей...\nК тому времени уже сгустились сумерки. Мы завели " + sTemp +" в ближайшую бухту, содержимое трюма вывезли на берег и надёжно спрятали, а " + sTemp + " отогнали подальше в море и взорвали. Наутро я отрапортовал по службе о потоплении пиратского судна, но ни слова не упомянул о содержимом трюма.";		
			link.l1 = "Думаю, вам нет смысла меня обманывать... Итак, предлагаю сделку - вы показываете мне тайник, а я доставляю вас в любое место архипелага, которое вы укажете.";
			link.l1.go = "CaptainComission_376";
		break;
		
		case "CaptainComission_376":
			dialog.text = "Ха-ха-ха... Не-ет, капитан, без своей доли я поселение не оставлю, даже если мне придётся болтаться на виселице.";
			link.l1 = "Хорошо. Вы получите свою половину.";
			link.l1.go = "CaptainComission_377";
			link.l2 = "Хм... Я не стану рисковать своей головой ради вашего благополучия. Прощайте...";
			link.l2.go = "CaptainComission_378";
		break;
		
		case "CaptainComission_377":
			dialog.text = "Это другое дело. Теперь я готов хоть к чёрту в зубы.\nПервым делом вы должны укрыть меня на борту своего судна. Там я укажу бухту, в которой находится тайник.";
			link.l1 = "Тогда действуем быстро и слажено: я открываю камеру, а вы следуете за мной. Не отставать и рот не открывать, пока не выберемся из тюрьмы.";
			link.l1.go = "CaptainComission_379";
		break;
		
		case "CaptainComission_378":
			pchar.quest.CaptainComission_GetSecretTimeIsOut.over = "yes";
			sld = CharacterFromID("CapComission_1");
			sld.LifeDay = 0;
			ChangeCharacterComplexReputation(pchar,"nobility", -5);			
			AddQuestRecord("CaptainComission2", "8");
			AddQuestUserData("CaptainComission2", "sSex", GetSexPhrase("","а"));
			AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);
			CloseQuestHeader("CaptainComission2");
			LAi_CharacterDisableDialog(npchar);// лесник - запрет диалога
			DeleteAttribute(pchar, "GenQuest.CaptainComission");
			DialogExit();
		break;
		
		case "CaptainComission_379":
			AddQuestRecord("CaptainComission2", "21");
			AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);
			pchar.quest.CaptainComission_PrisonFree_Death.win_condition.l1 = "NPC_Death";
			pchar.quest.CaptainComission_PrisonFree_Death.win_condition.l1.character = "CapComission_1";
			pchar.quest.CaptainComission_PrisonFree_Death.win_condition = "CaptainComission_PrisonFree_Death";
			GetCharacterPos(npchar, &locx, &locy, &locz);	
			ChangeCharacterAddressGroup(npchar, npchar.location, "reload", LAi_FindNearestFreeLocator("reload", locx, locy, locz));
			LAi_group_Register("CapComission_Prison");
			LAi_group_SetRelation("CapComission_Prison", LAI_GROUP_PLAYER, LAI_GROUP_FRIEND);
			LAi_group_SetAlarmReaction(LAI_GROUP_PLAYER, "CapComission_Prison", LAI_GROUP_ENEMY, LAI_GROUP_FRIEND);
			LAi_group_MoveCharacter(npchar, "CapComission_Prison");
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			LAi_CharacterDisableDialog(npchar);
			pchar.GenQuest.CaptainComission.PrisonFree = true;
			if(pchar.GenQuest.CaptainComission == "MayorTalkGood") 
			{
				chrDisableReloadToLocation = true;	
				sld = CharacterFromId(pchar.GenQuest.CaptainComission.City + "JailOff");	
				sld.dialog.currentnode = "CapComission_PrisonFree1";
			}	
			pchar.quest.CapComission_ExitFromPrison.win_condition.l1 = "ExitFromLocation";
            pchar.quest.CapComission_ExitFromPrison.win_condition.l1.location = pchar.location;
            pchar.quest.CapComission_ExitFromPrison.win_condition = "CaptainComission_ExitFromPrison"; 
			DialogExit();
		break;		
		
		case "CaptainComission_380":
			pchar.quest.CaptainComission_GetSecretTimeIsOut.over = "yes";
			pchar.quest.CaptainComission_PrisonFree_Death.over = "yes";
			DeleteAttribute(pchar,"GenQuest.CaptainComission.canSpeakCaptain");
			DeleteAttribute(pchar,"GenQuest.CaptainComission.PrisonFree");
			pchar.GenQuest.CaptainComission = "CanGetGoods";
			pchar.GenQuest.CaptainComission.ConvoyShore = SelectQuestShoreLocationFromSea(GetArealByCityName(pchar.GenQuest.CaptainComission.City));
			dialog.text = "Благодарю за спасение. Теперь нам нужно отправляться " + XI_ConvertString(pchar.GenQuest.CaptainComission.ConvoyShore + "Acc") + ", там я укажу место тайника. Только нужно торопиться пока до него не добрались ищейки.";			
			link.l1 = "Вы уверены, что мы сможем забрать весь товар?";
			link.l1.go = "CaptainComission_381";
		break;
		
		case "CaptainComission_381":
			pchar.GenQuest.CaptainComission.GoodsQty = makeint(sti(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipTypeVictim),"Capacity")) / sti(Goods[sti(pchar.GenQuest.CaptainComission.Goods)].Weight));
			dialog.text = "Да, вы правы, нужно позаботиться, чтоб в ваших трюмах нашлось место для " + pchar.GenQuest.CaptainComission.GoodsQty + " шт. " + GetStrSmallRegister(XI_ConvertString(Goods[sti(pchar.GenQuest.CaptainComission.Goods)].Name + "Gen")) + ". Добыча оказалась солидной, и будет обидно терять груз, доставшийся ценой стольких жизней. А второго шанса вывезти товар нам уже не дадут.";
			link.l1 = "Обязательно позабочусь.";
			link.l1.go = "CaptainComission_382";
		break;
		
		case "CaptainComission_382":
			AddQuestRecord("CaptainComission2", "24");
			AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);
			AddQuestUserData("CaptainComission2", "sShoreName", XI_ConvertString(pchar.GenQuest.CaptainComission.ConvoyShore + "Dat"));
			AddQuestUserData("CaptainComission2", "sGoodsQuantity", pchar.GenQuest.CaptainComission.GoodsQty);
			AddQuestUserData("CaptainComission2", "sGoods", GetStrSmallRegister(XI_ConvertString(Goods[sti(pchar.GenQuest.CaptainComission.Goods)].Name + "Gen")));
			SetFunctionLocationCondition("CaptainComission_MeetInShore", pchar.GenQuest.CaptainComission.ConvoyShore, false); 
			SetFunctionTimerConditionParam("CaptainComission_CapEscapeTimer", 0, 0, 1, MakeInt(24 - GetHour()), false);
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, false);
			chrDisableReloadToLocation = false; // Откроем выход
			DeleteAttribute(pchar,"TownEscape");
			QuestOpenSeaExit();
			DialogExit();
			AddDialogExitQuest("CanEnterToMap");
		break;
		
		case "CaptainComission_383":
			dialog.text = "Капитан, нам не нужны свидетели. Попробуйте спровадить этих людей из бухты.";
			link.l1 = "Хорошо, сейчас сделаем...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("CaptainComission_GangDialogGetGoods");
		break;
		
		case "CaptainComission_384":
			dialog.text = "Капитан, вы выбрали неудачное место для моциона. Этот док уже занят.";
			link.l1 = "Джентльмены, я приш"+ GetSexPhrase("ел","ла") +" сюда не окрестностями любоваться. У меня здесь дело.";
			link.l1.go = "CaptainComission_385";
		break;
		
		case "CaptainComission_385":
			dialog.text = "Мы здесь тоже не медуз ловим - разворачивай свою лоханку и уводи по ветру.";
			link.l1 = "У меня нет ни времени, ни желания вас уговаривать. Или вы уходите и живёте долго и счастливо, или остаётесь здесь, но уже навсегда.";
			link.l1.go = "CaptainComission_386";
		break;
		
		case "CaptainComission_386":
			dialog.text = "Я вижу, слов ты не понимаешь. Ну, тогда держись...";
			link.l1 = "Вот это другой разговор...";
			link.l1.go = "CaptainComission_364";
		break;
		
		case "CaptainComission_387":
			LAi_LocationDisableOfficersGen(pchar.GenQuest.CaptainComission.ConvoyShore, false);
			pchar.GenQuest.CaptainComission.MaxGoodsQty = GetSquadronFreeSpace(pchar, sti(pchar.GenQuest.CaptainComission.Goods));
			if(sti(pchar.GenQuest.CaptainComission.MaxGoodsQty) > sti(pchar.GenQuest.CaptainComission.GoodsQty)) pchar.GenQuest.CaptainComission.MaxGoodsQty = pchar.GenQuest.CaptainComission.GoodsQty;
			dialog.text = "Вот мы и пришли. Тайник в нише вон той скалы. Вход завален камнями. В тайнике " + pchar.GenQuest.CaptainComission.GoodsQty +" шт. " + GetStrSmallRegister(XI_ConvertString(Goods[sti(pchar.GenQuest.CaptainComission.Goods)].Name + "Gen")) +". Вы не забыли, что половина моя?";
			link.l1 = "Не забыл"+ GetSexPhrase("","а") +". Пока мои люди займутся погрузкой, давайте выясним, куда необходимо доставить вас и ваш груз.";
			link.l1.go = "CaptainComission_388";
			if (!CheckAttribute(pchar,"GenQuest.CaptainComission.MayorTalkGood"))
			{	
			link.l2 = "Вот и славно. А теперь скажите, какая причина может заставить меня делиться с вами?";
			link.l2.go = "CaptainComission_389";
			}
			if(CheckAttribute(pchar,"GenQuest.CaptainComission.MayorTalkGood"))
			{
				link.l3 = "Капитан " + pchar.GenQuest.CaptainComission.Name + ", я вынужден"+ GetSexPhrase("","а") +" вас огорчить. Я действительно работаю по заданию губернатора. И намерен"+ GetSexPhrase("","а") +" передать ему весь укрытый вами груз. А вам придётся вернуться в тюрьму и дожидаться там своей участи.";
				link.l3.go = "CaptainComission_389";
				link.l2 = "Вот и славно. Тут такая история вышла.. Сперва я намеревался сдать вас властям, но потом подумал - какого чёрта я стану это делать да к тому же ещё и делиться с вами?";
			    link.l2.go = "CaptainComission_3899"; // // лесник . отдельный диалог в случае обмана всех.
			}	
		break;
		
		case "CaptainComission_388":
		    pchar.quest.CaptainComission_Capitan_Cdoxul.over = "yes"; // лесник . снял событие ,иначе в СЖ не то пишут.
			iTmp = FindNonEnemyColonyForAdventure(sti(pchar.GenQuest.CaptainComission.Nation),pchar.GenQuest.CaptainComission.City, true);			
			sTemp = Colonies[iTmp].id;
			pchar.GenQuest.CaptainComission.ConvoyIsland = GetArealByCityName(sTemp);
			pchar.GenQuest.CaptainComission.ConvoyShore = SelectQuestShoreLocationFromSea(pchar.GenQuest.CaptainComission.ConvoyIsland);
			pchar.GenQuest.CaptainComission.ConvoyCity = sTemp;			
			pchar.GenQuest.CaptainComission.iDay  = 20 + cRand(10);
			iGoods = GetSquadronFreeSpace(pchar, sti(pchar.GenQuest.CaptainComission.Goods)); 
			if(iGoods < sti(pchar.GenQuest.CaptainComission.GoodsQty)) pchar.GenQuest.CaptainComission.GoodsQty = iGoods;
			SetCharacterGoods(pchar, sti(pchar.GenQuest.CaptainComission.Goods), GetCargoGoods(pchar, sti(pchar.GenQuest.CaptainComission.Goods)) + sti(pchar.GenQuest.CaptainComission.GoodsQty));// перегруз
			dialog.text = "Мне нужно добраться до " + XI_ConvertString(pchar.GenQuest.CaptainComission.ConvoyShore + "Gen") + ", что на " + XI_ConvertString(GetIslandByCityName(sTemp) + "Dat") + " за " + pchar.GenQuest.CaptainComission.iDay + " дней. Там мои люди должны были подготовить сбыт товара.";
			link.l1 = "Хорошо. Пора уходить.";
			link.l1.go = "CaptainComission_391";
		break;
		case "CaptainComission_3899": // лесник . отдельный диалог в случае обмана всех.
		    DeleteAttribute(pchar,"GenQuest.CaptainComission.MayorTalkGood");
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), -10);
		    pchar.quest.CaptainComission_Capitan_Cdoxul.over = "yes"; // лесник . снял событие ,иначе в СЖ не то пишут.
			dialog.text = "Да уж... 'Чему бы жизнь нас ни учила, а сердце верит в чудеса...' Запиши, а то забудешь.\nВы ещё тот мерзавец, капитан. Мне ничего не остаётся сделать, как убить вас за ваше вероломство.";
			link.l1 = "Ну это если тебе повезёт...";
			link.l1.go = "CaptainComission_390";
			SetFunctionTimerConditionParam("CaptainComission_NaebalGubera", 0, 0, 1, MakeInt(24 - GetHour()), false);
		break;
		
		case "CaptainComission_389":
		    pchar.quest.CaptainComission_Capitan_Cdoxul.over = "yes"; // лесник . снял событие ,иначе в СЖ не то пишут.
			dialog.text = "Да уж... 'Чему бы жизнь нас ни учила, а сердце верит в чудеса...' Запиши, а то забудешь.\nХоть я и не ожидал такого поворота, но к бою готов всегда. Вам придётся ответить за своё вероломство.";
			link.l1 = "Ну это если тебе повезёт...";
			link.l1.go = "CaptainComission_390";
		break;
		
		
		case "CaptainComission_390":
			LAi_SetPlayerType(pchar);
			LAi_group_Delete("EnemyFight");
			chrDisableReloadToLocation = true;
			rChar = CharacterFromID("CapComission_1");
			LAi_SetWarriorType(rChar);
			LAi_SetImmortal(rChar, false);// лесник.  
			LAi_group_MoveCharacter(rChar, "EnemyFight");		
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "OpenTheDoors"); 			
			if(pchar.GenQuest.CaptainComission == "CapDuel")
			{
				LAi_group_SetCheckFunction("EnemyFight", "CaptainComission_CaptainDiedDuel");
			}
			else
			{
				LAi_group_SetCheckFunction("EnemyFight", "CaptainComission_CheckCaptainDied");
			}	
			DialogExit();	
			AddDialogExitQuest("MainHeroFightModeOn");						
		break;
		
		case "CaptainComission_391":
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, false);
			GetCharacterPos(NPChar, &locx, &locy, &locz);
			LAi_SetActorType(NPChar);
			LAi_ActorGoToLocation(NPChar, "reload", LAi_FindNearestLocator("reload", locx, locy, locz), "none", "", "", "OpenTheDoors", 5.0);			
			pchar.GenQuest.CaptainComission.CapGoodsQty = sti(pchar.GenQuest.CaptainComission.GoodsQty)/2;
			if(sti(pchar.GenQuest.CaptainComission.CapGoodsQty) > sti(pchar.GenQuest.CaptainComission.MaxGoodsQty)) pchar.GenQuest.CaptainComission.CapGoodsQty = pchar.GenQuest.CaptainComission.MaxGoodsQty;
			if(CheckAttribute(pchar,"GenQuest.CaptainComission.MayorTalkGood"))AddQuestRecord("CaptainComission2", "53");// лесник. выбор записи в СЖ
			else AddQuestRecord("CaptainComission2", "26");// смотря по какому пути пошел 
			AddQuestUserData("CaptainComission2", "sGoodsQuantity", pchar.GenQuest.CaptainComission.MaxGoodsQty);
			AddQuestUserData("CaptainComission2", "sGoods", GetStrSmallRegister(XI_ConvertString(Goods[sti(pchar.GenQuest.CaptainComission.Goods)].Name + "Gen")));
			AddQuestUserData("CaptainComission2", "sSum1", pchar.GenQuest.CaptainComission.CapGoodsQty);
			AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);
			AddQuestUserData("CaptainComission2", "sDays", pchar.GenQuest.CaptainComission.iDay);
			AddQuestUserData("CaptainComission2", "sShoreName", XI_ConvertString(pchar.GenQuest.CaptainComission.ConvoyShore + "Acc"))
			AddQuestUserData("CaptainComission2", "sShoreType", XI_ConvertString(pchar.GenQuest.CaptainComission.ConvoyIsland + "Dat"));
			OfficersReaction("bad");
			if(CheckAttribute(pchar,"GenQuest.CaptainComission.MayorTalkGood"))
			{
				ChangeCharacterComplexReputation(pchar,"nobility", -5);
				ChangeCharacterNationReputation(pchar, sti(NPChar.nation), -10);
			}
			CaptainComission_GenerateCoastalPatrol();
			pchar.GenQuest.CaptainComission = "GetGoodsEscape";
			SetFunctionLocationCondition("CaptainComission_CapMeetInShore", pchar.GenQuest.CaptainComission.ConvoyShore, false);
			SaveCurrentQuestDateParam("GenQuest.CaptainComission.DeleiveCapShore");	
			DialogExit();
		break;
		
		case "CaptainComission_392":
			dialog.text = "Похоже, мы опоздали... Покупатели не дождались, а у меня нет никакой возможности в одиночку организовать хранение и сбыт товара...";
			link.l1 = "Вы имеете какие-то конкретные предложения на этот счёт?";
			link.l1.go = "CaptainComission_393";
		break;
		
		case "CaptainComission_393":
			pchar.GenQuest.CaptainComission.GoodsPrice = makeint(sti(pchar.GenQuest.CaptainComission.CapGoodsQty) * 0.75 * sti(Goods[sti(pchar.GenQuest.CaptainComission.Goods)].Cost));
			dialog.text = "Капитан " + GetFullName(pchar) + ", мне несколько неловко такое предлагать, но не могли бы вы отдать мою долю деньгами? Я думаю, " + pchar.GenQuest.CaptainComission.GoodsPrice + " песо будет достойным компромиссом.";
			if(sti(pchar.money) >= sti(pchar.GenQuest.CaptainComission.GoodsPrice))
			{
				link.l1 = "Да, это хорошая цена. Я не возражаю. Получите свои деньги и прощайте.";
				link.l1.go = "CaptainComission_394";
			}
			link.l2 = "Э, нет, уважаемый, мы так не договаривались. Я не могу нянчиться с вами вечно. Если не хотите забирать груз, то я с чистой совестью оставлю его себе. Я уж сумею организовать его хранение и сбыт.";
			link.l2.go = "CaptainComission_3951"; // лесник . верный переход
		break;
		
		case "CaptainComission_394":
			addMoneyToCharacter(pchar, -sti(pchar.GenQuest.CaptainComission.GoodsPrice));
			dialog.text = "Погодите, капитан. Я хочу отблагодарить вас за спасение. Я ведь уже ни на что не надеялся... Вот вещица, которая вам очень пригодится во многих ситуациях... А теперь прощайте.";
			link.l1 = "Спасибо. Не ожидал"+ GetSexPhrase("","а") +". Приятно было иметь с вами дело.";
			link.l1.go = "CaptainComission_395";
		break;
		
		case "CaptainComission_3951": // лесник . верное назначение диалога
		    pchar.quest.CaptainComission_Capitan_Cdoxul.over = "yes";
			dialog.text = "Не ожидал я от вас такого поворота... Похоже, у меня нет другого выбора, кроме как предложить вам дуэль.";
			link.l1 = "Я к вашим услугам...";
			link.l1.go = "CaptainComission_390";
			pchar.GenQuest.CaptainComission = "CapDuel";
		break;
		
		case "CaptainComission_395":
			GiveItem2Character(pchar, pchar.GenQuest.CaptainComission.Prize);
			AddQuestRecord("CaptainComission2", "32");
			AddQuestUserData("CaptainComission2", "sSex", GetSexPhrase("ся","ась"));
			AddQuestUserData("CaptainComission2", "sShoreName", XI_ConvertString(pchar.GenQuest.CaptainComission.ConvoyShore + "Dat"));
			AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);
			AddQuestUserData("CaptainComission2", "sSum", pchar.GenQuest.CaptainComission.GoodsPrice);
			CloseQuestHeader("CaptainComission2");	
			GetCharacterPos(pchar, &locx, &locy, &locz);
			LAi_SetActorType(NPChar);
			LAi_ActorGoToLocation(NPChar, "reload", LAi_FindNearestLocator("reload", locx, locy, locz), "none", "", "", "OpenTheDoors", 5.0);
			NPChar.lifeDay = 0; 						
			DeleteAttribute(pchar, "GenQuest.CaptainComission");
			DialogExit();
		break;

		case "CaptainComission_396_0":
			dialog.text = "Капитан, мне необходимо поговорить с моими людьми.";
			link.l1 = "Разрешаю.";
			link.l1.go = "exit";
			InterfaceStates.Buttons.Save.enable = false; 
			AddDialogExitQuestFunction("CaptainComission_DialogInShore");
		break;
		
		case "CaptainComission_396":
			sld = characterFromId("Blaze");
			dialog.text = "Приветствую вас, капитан " + GetFullName(pchar) + ". Ну что, весь груз привезли? А где капитан " + pchar.CaptainComission.CapName + "?";
			link.l1 =  pchar.CaptainComission.CapName + " погиб, а я был арестован по доносу. В общем, если бы мне не помог"+ NPCharSexPhrase(sld, "","ла") +" капитан " + pchar.CaptainComission.FullName + ", не видать бы вам ни меня, ни товара.";
			link.l1.go = "CaptainComission_397";
		break;
		
		case "CaptainComission_397":
			sld = characterFromId("Blaze");
			dialog.text = "А "+ NPCharSexPhrase(sld, "что он за тип? Он","кто она такая? Она") +" в курсе наших дел?";
			link.l1 = "Более чем. "+ NPCharSexPhrase(sld, "Он вытащил","Она вытащила") +" меня из тюрьмы и взял"+ NPCharSexPhrase(sld, "ся","ась") +" доставить сюда половину груза, другую половину я пообещал "+ NPCharSexPhrase(sld, "ему","ей") +" в уплату за хлопоты.";
			link.l1.go = "CaptainComission_398";
		break;
		
		case "CaptainComission_398":
			sld = characterFromId("Blaze");
			dialog.text = "Э, нет, капитан, это уже твои проблемы! Ведь я сразу предлагал уводить " + GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.CaptainComission.ShipTypeVictim),"Name") + "Acc")) + " в укромное место, а ты всё за свою карьеру хватался. Вот и дождался, пока твой любимый губернатор не упёк тебя в тюрьму." +
				" И твоя доля в этом деле была куда меньше половины, вот ею бы и распоряжался! А мы свои головы под картечь подставляли не для того, чтобы "+ NPCharSexPhrase(sld, "какой-то хлыщ мог","какая-то девка могла") +" так просто прикарманить себе целую половину!";
			link.l1 = "Послушай, боцман, ты разве забыл что у " + GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.CaptainComission.ShipTypeVictim),"Name") + "Gen")) + " был разбит грот? А про крен до самого фальшборта ты тоже забыл? А ты хоть понимаешь, что, если бы я не отдал "+ NPCharSexPhrase(sld, "этому человеку","ей") +" половину, то ты скорее бы снега дождался, чем товара?";	
			link.l1.go = "CaptainComission_399";
		break;
		
		case "CaptainComission_399":
			dialog.text = "Гладко стелешь, но меня не проведёшь! Откуда нам знать, что вы не сговорились? Может, никакого ареста и не было?! Может, жадность тебя заставила на матросское добро позариться? Или ты думаешь, что мы разучились управляться со своими клинками?!";
			link.l1 = "Вижу, ты совсем потерял голову, наверное звон песо уже стоит в твоих ушах.";
			link.l1.go = "CaptainComission_400";
		break;
		
		case "CaptainComission_400":
			sld = characterFromId("Blaze");
			dialog.text = "Братцы! Смотрите, как запел наш капитан! Вот что делает с людьми жадность. Он продал нашу долю "+ NPCharSexPhrase(sld, "проходимцу","авантюристке") +"!!";
			link.l1 = "Закрой свой поганый рот! Или я заставлю тебя заткнуться навечно!..";
			link.l1.go = "exit";
			AddDialogExitQuest("CaptainComission_ShoreGangDialog");
		break;
		
		case "CaptainComission_401":
			dialog.text = "Извините, капитан, что вам пришлось стать свидетелем и участником этой нелепой сцены. Трудно даже поверить, что ещё какой-то месяц назад мы были единой командой, в которой каждый готов был жизнь отдать за товарища.";
			link.l1 = "Признаюсь, даже моя богатая фантазия не в силах представить эту картину.";
			link.l1.go = "CaptainComission_402";
		break;
		
		case "CaptainComission_402":
			dialog.text = "К сожалению, у меня теперь нет никакой возможности в одиночку организовать хранение и сбыт товара...";
			link.l1 = "Вы имеете какие-то конкретные предложения на этот счёт?";
			link.l1.go = "CaptainComission_403";
		break;
		
		case "CaptainComission_403":
			pchar.GenQuest.CaptainComission.GoodsPrice = makeint(sti(pchar.GenQuest.CaptainComission.CapGoodsQty) * 0.75 * sti(Goods[sti(pchar.GenQuest.CaptainComission.Goods)].Cost));
			dialog.text = "Капитан " + GetFullName(pchar) + ", мне несколько неловко такое предлагать, но не могли бы вы отдать мою долю деньгами? Я думаю, " + pchar.GenQuest.CaptainComission.GoodsPrice + " песо будет достойным компромиссом.";
			if(sti(pchar.money) >= sti(pchar.GenQuest.CaptainComission.GoodsPrice))
			{ 
		        pchar.quest.CaptainComission_Capitan_Cdox.over = "yes"; // на всякий случай .лесник
				pchar.quest.CaptainComission_Capitan_Cdoxul.over = "yes"; // лесник
				link.l1 = "Пожалуй так. Не возражаю. Получите свои деньги и прощайте.";
				link.l1.go = "CaptainComission_404";
			}	
			link.l2 = "Нет, такая перспектива меня не устраивает. Вы можете забрать груз или оставить в трюме, но денег я вам не дам.";
			link.l2.go = "CaptainComission_405";
		break;
		
		case "CaptainComission_404":
			bTemp = false;
			if(drand(1) == 0)
			{
			    NPChar.reputation = 60 + rand(20); 
				NPChar.alignment = "good"; 
			}	
			else
			{
			    NPChar.reputation = 10 + rand(20); 
				NPChar.alignment = "bad"; 			
			}
			if (NPChar.alignment == "good" && sti(pchar.reputation.nobility) > 50) bTemp = true; 
			if (NPChar.alignment == "bad" && sti(pchar.reputation.nobility) <= 50) bTemp = true;
			
			addMoneyToCharacter(pchar, -sti(pchar.GenQuest.CaptainComission.GoodsPrice));
			
			if(!bTemp || FindFreeRandomOfficer() < 0)
			{
				dialog.text = "Подождите, я хочу отблагодарить вас за спасение. Я ведь уже ни на что не надеялся... Вот вещица, которая вам очень пригодится во многих ситуациях... А теперь прощайте.";
				link.l1 = "Спасибо. Не ожидал"+ GetSexPhrase("","а") +". Приятно было иметь с вами дело.";
				link.l1.go = "CaptainComission_406";
			}
			else
			{
				dialog.text = "Подождите... Я тут подумал, что карьера моя всё равно лопнула, команды не осталось, у себя на родине я изгой. А вам наверняка нужны верные люди, умеющие держать клинок в руках и язык за зубами. Возьмите меня в команду - не пожалеете.";
				if(!CaptainComission_CheckAllPassengersHired())
				{
					link.l1 = "Признаться, я давно ждал"+ GetSexPhrase("","а") +", когда ты на это решишься. Беру конечно. Встретимся на борту.";
					link.l1.go = "CaptainComission_407";
				}	
				link.l2 = "Хм... мне кажется, вы слишком умный человек, чтоб служить под чьим-то началом. Прощайте...";
				link.l2.go = "CaptainComission_408";
			}
		break;
		
		case "CaptainComission_405":
			dialog.text = "Да уж, видимо, сегодня не мой день... Капитан, давайте обнажим клинки и покончим со всем разом...";
			link.l1 = "Я к вашим услугам...";
			link.l1.go = "CaptainComission_390";
			pchar.GenQuest.CaptainComission = "CapDuel";
			pchar.GenQuest.CaptainComission.Duel = true;
		break;
		
		case "CaptainComission_406":
			GiveItem2Character(pchar, pchar.GenQuest.CaptainComission.Prize);
			AddQuestRecord("CaptainComission2", "34");
			AddQuestUserData("CaptainComission2", "sSex", GetSexPhrase("ся","ась"));
			AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);
			AddQuestUserData("CaptainComission2", "sSum", pchar.GenQuest.CaptainComission.GoodsPrice);
			CloseQuestHeader("CaptainComission2");
			GetCharacterPos(pchar, &locx, &locy, &locz);
			LAi_SetActorType(NPChar);
			LAi_ActorGoToLocation(NPChar, "reload", LAi_FindNearestLocator("reload", locx, locy, locz), "none", "", "", "OpenTheDoors", 5.0);			
			NPChar.lifeDay = 0; 						
			DeleteAttribute(pchar, "GenQuest.CaptainComission");
			DialogExit();
		break;
	
		
		case "CaptainComission_407":	
			AddQuestRecord("CaptainComission2", "36");
			AddQuestUserData("CaptainComission2", "sSex", GetSexPhrase("","а"));
			AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);
			AddQuestUserData("CaptainComission2", "sSum", pchar.GenQuest.CaptainComission.GoodsPrice);
			CloseQuestHeader("CaptainComission2");		
			npchar.CaptainComission = true;
			SetCharacterRemovable(Npchar, true);
			DeleteAttribute(pchar, "GenQuest.CaptainComission");
			NPChar.Dialog.Filename = "Enc_Officer_dialog.c";
			NPChar.Dialog.CurrentNode = "hired";
            NPChar.greeting = "Gr_Officer"; 			
			NPChar.quest.OfficerPrice = sti(pchar.rank)*500;	
			NPChar.loyality = MAX_LOYALITY;
			DeleteAttribute(NPChar, "LifeDay");
			NPChar.id = "GenChar_" + NPChar.index;// лесник . смена ИД при взятии в оффы. 
			pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(NPChar.id);
			AddDialogExitQuestFunction("LandEnc_OfficerHired"); 
			NPChar.quest.meeting = true; 
			DialogExit();
		break;		
		
		case "CaptainComission_408":
			AddQuestRecord("CaptainComission2", "35");
			AddQuestUserData("CaptainComission2", "sSex", GetSexPhrase("","а"));
			AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);
			AddQuestUserData("CaptainComission2", "sSum", pchar.GenQuest.CaptainComission.GoodsPrice);
			CloseQuestHeader("CaptainComission2");
			GetCharacterPos(pchar, &locx, &locy, &locz);
			LAi_SetActorType(NPChar);
			LAi_ActorGoToLocation(NPChar, "reload", LAi_FindNearestLocator("reload", locx, locy, locz), "none", "", "", "OpenTheDoors", 5.0);						
			NPChar.lifeDay = 0; 						
			DeleteAttribute(pchar, "GenQuest.CaptainComission");		
			DialogExit();
		break;		
		// Генератор "Операция Галеон"
		
		// Квест "встреча в бухте" -->
		// Офицер
		case "ContraMeetManQuest_Sold_1":
			dialog.text = "Это вас не касается. Немедленно говори, что ты здесь вынюхиваешь! Уж не того ли ты человека ищешь, которого мы только что задержали?!";
				link.l1 = "Человека?! Не-е...";
				link.l1.go = "ContraMeetManQuest_Sold_2";
			break;
			
		case "ContraMeetManQuest_Sold_2":
			dialog.text = "И это хорошо... Для тебя... Иначе попал"+ GetSexPhrase("","а") +" бы ты в тюрьму вместе с ним. Теперь не путайся у нас под ногами, моря"+ GetSexPhrase("к","чка") +". И не смей больше отвлекать меня!...";
				link.l1 = "Да, я лучше пойду...";
				link.l1.go = "ContraMeetManQuest_Sold_3";
			break;
			
		case "ContraMeetManQuest_Sold_3":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			DeleteQuestCondition("ContraMeetManQuest_TimeIsLeft"); // Время больше не роляет
			sQuestTitle = PChar.GenQuest.ContraMeetMan.QuestTown + "ContraMeetManQuest";
			AddQuestRecordEx(sQuestTitle, "ContraMeetManQuest", "8");
			PChar.GenQuest.ContraMeetMan.ToTavernPatrolInShore = true;
			LAi_CharacterDisableDialog(NPChar);
			DeleteAttribute(&Locations[FindLocation(PChar.GenQuest.ContraMeetMan.ShoreID)], "DisableEncounters"); // Включаем случайки
			ContraMeetManQuest_DeletePatrolFromShore(); // По выходу потрем всех из локации
			break;
			
		// Сам чел
		case "ContraMeetManQuest_1":
			dialog.text = "Отлично! Нам нужно немедленно отправиться в таверну к контрабандисту - мне бы очень не хотелось задерживаться!";
				link.l1 = "Не вижу никаких проблем. Пойдем...";
				link.l1.go = "ContraMeetManQuest_2";
			break;
			
		case "ContraMeetManQuest_2":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LAi_SetActorType(NPChar);
			LAi_ActorFollowEverywhere(NPChar, "", -1);
			sQuestTitle = PChar.GenQuest.ContraMeetMan.QuestTown + "ContraMeetManQuest";
			AddQuestRecordEx(sQuestTitle, "ContraMeetManQuest", "3");
			AddQuestUserData(sQuestTitle, "sDestination", XI_ConvertString(PChar.GenQuest.ContraMeetMan.ShoreID + "Dat"));
			PChar.GenQuest.ContraMeetMan.ToTavernWithMan = true;
			DeleteAttribute(&Locations[FindLocation(PChar.GenQuest.ContraMeetMan.ShoreID)], "DisableEncounters"); // Включаем случайки
			break;
		
		// Контрики в комнате таверны	
		case "ContraMeetManQuest_3":
			ContraMeetManQuest_ContersGoQut();
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			AddMoneyToCharacter(PChar, sti(PChar.GenQuest.ContraMeetMan.Money));
			sQuestTitle = PChar.GenQuest.ContraMeetMan.QuestTown + "ContraMeetManQuest";
			AddQuestRecordEx(sQuestTitle, "ContraMeetManQuest", "4");
			AddQuestUserData(sQuestTitle, "sMoney", FindRussianMoneyString(sti(PChar.GenQuest.ContraMeetMan.Money)));
			CloseQuestHeader(sQuestTitle);
			ChangeContrabandRelation(PChar, 5);
			DeleteAttribute(PChar, "GenQuest.ContraMeetMan");
			break;
			
		case "ContraMeetManQuest_4":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			AddMoneyToCharacter(PChar, sti(PChar.GenQuest.ContraMeetMan.Money));
			sQuestTitle = PChar.GenQuest.ContraMeetMan.QuestTown + "ContraMeetManQuest";
			AddQuestRecordEx(sQuestTitle, "ContraMeetManQuest", "5");
			AddQuestUserData(sQuestTitle, "sMoney", FindRussianMoneyString(sti(PChar.GenQuest.ContraMeetMan.Money)));
			CloseQuestHeader(sQuestTitle);
			ContraMeetManQuest_ContraBeatMan();
			ChangeContrabandRelation(PChar, 5);
			ChangeCharacterComplexReputation(pchar,"nobility", -5);
			DeleteAttribute(PChar, "GenQuest.ContraMeetMan");
			break;
			
		case "ContraMeetManQuest_5":
			dialog.text = "Хе-хе... Похоже, "+ GetSexPhrase("парень","деваха") +", ты сейчас отправишься в ад вместе с ним... Эй, дружище, давай вспорем им животы!";
				link.l1 = "Ах ты грязная свинья! Защищайся!";
				link.l1.go = "ContraMeetManQuest_6";
			break;
			
		case "ContraMeetManQuest_6":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			ContraMeetManQuest_PlayerBeatContra();
			break;
			
		case "ContraMeetManQuest_7":
			dialog.text = "Спасибо вам еще раз, " + PChar.name + ". Прощайте...";
				link.l1 = "...";
				link.l1.go = "ContraMeetManQuest_9";
			break;
			
		case "ContraMeetManQuest_8":
			iMoney = (rand(3)+2)*500;
			PChar.GenQuest.ContraMeetMan.Money = iMoney;
			dialog.text = "Вознаграждения?! Ах да, конечно... Вот, возьмите " + FindRussianMoneyString(iMoney) + " и прощайте...";
				link.l1 = "До встречи...";
				link.l1.go = "ContraMeetManQuest_10";
			break;
			
		case "ContraMeetManQuest_9":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			ChangeCharacterComplexReputation(pchar,"nobility", 10);
			sQuestTitle = PChar.GenQuest.ContraMeetMan.QuestTown + "ContraMeetManQuest";
			AddQuestRecordEx(sQuestTitle, "ContraMeetManQuest", "6");
			AddQuestUserData(sQuestTitle, "sMoney", FindRussianMoneyString(iMoney));
			AddQuestUserData(sQuestTitle, "sDestination", XI_ConvertString(PChar.GenQuest.ContraMeetMan.ShoreID + "Dat"));
			CloseQuestHeader(sQuestTitle);
			ContraMeetManQuest_ContersGoQut();
			DeleteAttribute(PChar, "GenQuest.ContraMeetMan");
			break;
			
		case "ContraMeetManQuest_10":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			AddMoneyToCharacter(PChar, sti(PChar.GenQuest.ContraMeetMan.Money));
			sQuestTitle = PChar.GenQuest.ContraMeetMan.QuestTown + "ContraMeetManQuest";
			AddQuestRecordEx(sQuestTitle, "ContraMeetManQuest", "7");
			AddQuestUserData(sQuestTitle, "sMoney", FindRussianMoneyString(sti(PChar.GenQuest.ContraMeetMan.Money)));
			AddQuestUserData(sQuestTitle, "sDestination", XI_ConvertString(PChar.GenQuest.ContraMeetMan.ShoreID + "Dat"));
			CloseQuestHeader(sQuestTitle);
			ContraMeetManQuest_ContersGoQut();
			DeleteAttribute(PChar, "GenQuest.ContraMeetMan");
			break;
		// <-- Квест "встреча в бухте"
			
		// Квест на доставку письма контрику -->
		case "ContraDeliverQuest_Sold1":
			dialog.text = "Хех, и ты думаешь, мы поверим этой ерунде?! А-ну, ребятки, забирайте этих двоих висельников!";
			//if(80 > rand(100) || sti(PChar.skill.Fortune) > rand(100)) // Попытка отмазаться
			//{
				link.l1 = "Офицер, поверьте, вы совершаете ужастную ошибку и пытаетесь арестовать ни в чем не повинных людей. Поверьте, я совсем не знаю этого человека и, более того, не желаю его знать."
				+ " Я думаю, ваш комендант будет очень недоволен, если вы арестуете двух законопослушных граждан...";
				link.l1.go = "ContraDeliverQuest_Sold2_Liberty";
			//}
			/*else // Тюрьма
			{
				link.l1 = "";
				link.l1.go = "ContraDeliverQuest_Sold2_Prison";
			}*/
			break;
			
		case "ContraDeliverQuest_Sold2_Liberty":
			dialog.text = "Кхм, да, вы, пожалуй, правы. Комендант будет очень недоволен. Знаете что, давайте просто забудем об этом маленьком недоразумении.";
				link.l1 = "Спасибо, офицер, вы сэкономили нам время. Впредь попрошу вас быть более внимательным, ведь вы же не хотите лишиться этого высокого звания - офицер?!";
				link.l1.go = "ContraDeliverQuest_Sold2_Liberty1";
			break;
			
		case "ContraDeliverQuest_Sold2_Liberty1":
			dialog.text = "Никак нет, этого я не желаю. Теперь попрошу вас разойтись. Честь имею...";
				link.l1 = "Вот так бы сразу!";
				link.l1.go = "ContraDeliverQuest_Sold2_Liberty2";
			break;
			
		case "ContraDeliverQuest_Sold2_Liberty2":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			ContraDeliverQuest_SoldiersGoOut();
			break;
		
		case "ContraDeliverQuest_1":
			iMoney = (rand(3)+2)*500;
			if(rand(1) == 0) // Денег не дает
			{
				dialog.text = "Отлично. Теперь можешь проваливать!";
					link.l1 = "Что?! А как же деньги? Мы же договаривались...";
					link.l1.go = "ContraDeliverQuest_NoMon";
			}
			else // Деньги или патруль
			{
				if(rand(2) == 1) // Патруль
				{
					dialog.text = "Спасибо за доставку. Теперь можешь прова... Хм, кто-то идет...";
						link.l1 = "Что?!";
						link.l1.go = "ContraDeliverQuest_Patrol";
				}
				else // Просто отдает деньги
				{
					dialog.text = "Отлично. Спасибо за доставку. Вот, держи " + FindRussianMoneyString(iMoney) ". И помни - контрабандисты хороших людей не забывают...";
					link.l1 = "Очень на это надеюсь. Прощайте.";
					link.l1.go = "ContraDeliverQuest_GoWithMoney";
					PChar.GenQuest.ContraDeliver.Money = iMoney;
				}
			}
			
			ChangeContrabandRelation(PChar, 5); // Письмо доставили - повышаем отношение у контриков
			ChangeCharacterComplexReputation(pchar,"nobility", -5); // Помогли контрикам - репу понижаем
			RemoveItems(PChar, "letter_1", 1);
			BackItemDescribe("letter_1");
			DeleteAttribute(&Items[FindItem("letter_1")], "City");
			rChar = &Characters[GetCharacterIndex(Locations[FindLocation(PChar.location)].townsack + "_Smuggler")];
			SaveCurrentNpcQuestDateParam(rChar, "work_date");
			break;
			
		case "ContraDeliverQuest_Patrol":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LAi_LocationFightDisable(LoadedLocation, true); // Чтоб не поубивали кого-нить
			ContraDeliverQuest_GeneratePatrolToRoom();
			break;
			
		case "ContraDeliverQuest_NoMon":
			dialog.text = "Слушай сюда - мы с тобой ни о чем не договаривались. Вот тот, кто с тобой договаривался - тот тебе деньги и должен дать.";
				link.l1 = "Неудачный у меня сегодня день, что тут еще можно сказать?! Ладно, прощай...";
				link.l1.go = "ContraDeliverQuest_GoWithoutMoney";
				link.l2 = RandSwear() + "Ты за это ответишь! Приготовься к смерти!";
				link.l2.go = "ContraDeliverQuest_PrepareToFight";
			break;
			
		case "ContraDeliverQuest_GoWithoutMoney": // Уходим без денег
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			chrDisableReloadToLocation = false;
			bDisableFastReload         = false;
			PChar.GenQuest.ContraDeliver.Complete.WithoutMoney = true;
			sQuestTitle = PChar.GenQuest.ContraDeliver.QuestTown + "ContraDeliverQuest";
			AddQuestRecordEx(sQuestTitle, "ContraDeliverQuest", "4");
			AddQuestUserData(sQuestTitle, "sColony", XI_ConvertString("Colony" + PChar.GenQuest.ContraDeliver.QuestTown));
			LAi_ActorGoToLocation(NPChar, "reload", "reload1_back", "none", "", "", "", 3.0);
			break;
			
		case "ContraDeliverQuest_PrepareToFight":
			dialog.text = "Ты осмелил"+ GetSexPhrase("ся","ась") +" бросить мне вызов, "+ GetSexPhrase("щенок","дрянь") +"? Что ж, тебе же хуже. Сейчас я вспорю тебе брюхо!";
				link.l1 = "...";
				link.l1.go = "ContraDeliverQuest_Fight";
			break;
			
		case "ContraDeliverQuest_Fight": // Бой
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LAi_SetImmortal(NPChar, false);
			LAi_ActorAttack(NPChar, PChar, "");
			LAi_SetFightMode(PChar, true);
			SetFunctionNPCDeathCondition("ContraDeliverQuest_ContraIsDead", NPChar.ID, false);
			break;
			
		case "ContraDeliverQuest_GoWithMoney": // Уходим с деньгами
			AddMoneyToCharacter(PChar, sti(PChar.GenQuest.ContraDeliver.Money));
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			chrDisableReloadToLocation = false;
			bDisableFastReload         = false;
			sQuestTitle = PChar.GenQuest.ContraDeliver.QuestTown + "ContraDeliverQuest";
			AddQuestRecordEx(sQuestTitle, "ContraDeliverQuest", "3");
			AddQuestUserData(sQuestTitle, "sMoney", FindRussianMoneyString(sti(PChar.GenQuest.ContraDeliver.Money)));
			CloseQuestHeader(sQuestTitle);
			DeleteAttribute(PChar, "GenQuest.ContraDeliver"); // Квест пройден - атрибуды потрем
			LAi_ActorGoToLocation(NPChar, "reload", "reload1_back", "none", "", "", "", 3.0);
			break;
		// <-- Квест на доставку письма контрику
			
		// Церковеый генератор. Квест № 1. Диалог кэпа, которого ищем -->
		case "ChurchGenQuest_1_DeckDialog_1":
			if(CheckAttribute(PChar, "GenQuest.ChurchQuest_1.NeedToDialogWithCap"))
			{
				if(CheckAttribute(PChar, "GenQuest.ChurchQuest_1.CapWaitOnTavern")) // Если ждет в таверне
				{
					dialog.text = RandPhraseSimple("Пятьсот чело-ик! И сун-ик! мертвеца!.. Ик!", "Пей-ик! дьявол тебя доведёт до... ик! к-конца.");
						link.l1 = "О-о-о... м-да. Приветствую Вас, господин " + GetFullname(NPChar) + ".";
						link.l1.go = "ChurchGenQuest1_DialogInTavernWithCap_2";
						PChar.Quest.Church_GenQuest1_Timer.over = "yes";
				}
				else // на палубе своего шипа
				{
					if(!CheckAttribute(PChar, "GenQuest.ChurchQuest_1.Complete"))
					{
						dialog.text = "Так, что у нас тут... Три штуки парусины и доски на обшивку, ещё битенги заменить и троса на брасах...";
							link.l1 = "Приветствую Вас, господин " + GetFullName(NPChar) + ". Я - капитан " + PChar.name + ".";
							link.l1.go = "ChurchGenQuest1_DialogShip_1";
					}
					else
					{
						dialog.text = LinkRandPhrase("Убирайтесь с моего судна - у меня и без вас дел по горло!", "Вы получили книги, чего вам ещё надо?!", "Я сделал, как вы хотели, какого вам ещё рожна?!");
							link.l1 = "Не кипятитесь так, не то вас удар хватит!";
							link.l1.go = "exit";
					}					
				}
			}
			else
			{
				dialog.text = RandPhraseSimple("Рому, рому! Дайте мне рому... ик!", "Давненько я... ик! так не напивался...");
					link.l1 = "Да, трюм уже под завязку, не пора ли в гавань?";
					link.l1.go = "exit";
			}			
			NextDiag.TempNode = "ChurchGenQuest_1_DeckDialog_1";
			break;
			
		case "ChurchGenQuest1_DialogInTavernWithCap_2":
			dialog.text = RandPhraseSimple("Присаживайтесь, кап-ик-ан! Что будем пить?", "Извольте к столу, кэп! Что будете пить... Ик!");
					link.l1 = "Благодарю, но я бы предпоч"+ GetSexPhrase("ел","ла") +" приятную беседу с хорошим человеком.";
					link.l1.go = "ChurchGenQuest1_DialogInTavernWithCap_3";
			break;
			
		case "ChurchGenQuest1_DialogInTavernWithCap_3":
			dialog.text = "Обидеть хочешь-ик?.. тут во всей таверне ни одного приятного и хорошего. Сплошь бандиты, головорезы проклятые! Все, как один, вымогатели, а вон тот - первый! Главарь. Предводитель, мурену ему в глотку!";
				link.l1 = "Собственно, я имел"+ GetSexPhrase("","а") +" в виду вас. И побеседовать хотел"+ GetSexPhrase("","а") +" именно с вами. А кто тут главарь вымогателей-бандитов, и за что ему...";
				link.l1.go = "ChurchGenQuest1_DialogInTavernWithCap_4";
			break;
			
		case "ChurchGenQuest1_DialogInTavernWithCap_4":
			dialog.text = "Судар"+ GetSexPhrase("ь","ыня") +"! Любезн"+ GetSexPhrase("ый","ая") +"! Как, вы сказали, вас звать? Я тебя уважаю! Ещё ни одна душа не называла старого морского волка приятным и любезным! Да я тебе!.. Да я для тебя!.. Да я тебе всё!.. До последнего песо!.. Эх-х, забыл... деньги кончились. Даже рулики кончились. Только что этот гад, вымогатель последний рулик отнял, чтоб его кишками черти в аду мортиру заряжали!";
				link.l1 = "Г-н капитан... Может, позвать лекаря? Вам нехорошо, у вас горячка... Вам уже мерещатся какие-то рулики...";
				link.l1.go = "ChurchGenQuest1_DialogInTavernWithCap_5";
			break;
			
		case "ChurchGenQuest1_DialogInTavernWithCap_5":
			dialog.text = "Но-но! Старина кэп может и пьян, но пока еще в своём уме. Книжки и рулики дал отец " + PChar.GenQuest.ChurchQuest_1.ToName + ", я вёз их в " + XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.QuestTown) + ". А тут с утреца зашёл я в местную церковь, ну и помянул про эти бумажки. Здешнему падре очень захотелось на них взглянуть хоть одним глазом. Сами знаете, эту братию хлебом не корми - дай почитать про ихних святых и праведников. Ну, я отправил юнгу на корабль, чтоб притащил мой рундучок с этим богатством. Пока ждал, успел в пух и прах проиграться, ободрали дочиста, да еще за выпивку неуплачено. Кабатчик мигом сообразил, взял книжки в залог, а потом я и рулики ему отдал...";
				link.l1 = "То есть, вы пропили доверенные вам священником " + XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.ToColony + "Gen") + " рукописи и свитки?..";
				link.l1.go = "ChurchGenQuest1_DialogInTavernWithCap_6";
			break;
			
		case "ChurchGenQuest1_DialogInTavernWithCap_6":
			dialog.text = "Знаю, гореть мне в геене, потому как теперь не могу на глаза показаться ни тому падре, что поручение дал, ни тому, которому вёз эти бумаги, ни здешнему... Кто ж отмолит мою душу? А может, меня и от церкви отлучат? О-о-о, горе мне... выпить бы... ";
				link.l1 = "Ну-ну, не убивайтесь так. Поступили вы гнусно и богопротивно, однако я готов"+ GetSexPhrase("","а") +" помочь вам. Я оплачу ваш долг тавернщику и выкуплю эти рули... эти рукописи. Более того, поскольку я знаком"+ GetSexPhrase("","а") +" с обоими упомянутыми священниками и направляюсь прямиком в " + XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.QuestTown) + ", я в целости и сохранности доставлю эти труды по адресу. Вы согласны?";
				link.l1.go = "ChurchGenQuest1_DialogInTavernWithCap_7";
			break;
			
		case "ChurchGenQuest1_DialogInTavernWithCap_7":
			dialog.text = "Спаситель! Ангел Божий... Да как же не согласен. Согласен!.. Всеми руками отдам, всё отдам... только выпить бы ещё...";
				link.l1 = "С вас уже довольно... впрочем, ладно. Пойду, поговорю с кабатчиком и закажу вам немного рому.";
				link.l1.go = "ChurchGenQuest1_DialogInTavernWithCap_8";
			break;
			
		case "ChurchGenQuest1_DialogInTavernWithCap_8":
			DialogExit();
			DeleteAttribute(PChar, "GenQuest.ChurchQuest_1.NeedToDialogWithCap");
			PChar.GenQuest.ChurchQuest_1.NeedToDialogWithBarmen = true;
			sQuestTitle = PChar.GenQuest.ChurchQuest_1.QuestTown + "ChurchGenQuest1";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest1", "7_2");
			AddQuestUserData(sQuestTitle, "sColony", XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.QuestTown));
			AddQuestUserData(sQuestTitle, "sCapName", GetFullName(NPChar));
			NextDiag.CurrentNode = "ChurchGenQuest_1_DeckDialog_1";
			break;
			
		case "ChurchGenQuest1_DialogShip_1":
			dialog.text = "...и шкоты! шкоты поменять нужно!.. А, да - приветствую и всё такое. Не сочтите за грубость, г-"+ GetSexPhrase("н","жа") +" как-вас-там, но в данный момент я весьма занят, и просил бы как можно быстрее изложить суть безделицы, которая привела вас на борт моего судна.";
				link.l1 = "Кхм. Собственно, дело и впрямь пустяшное. Насколько мне известно, в " + XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.ToColony + "Dat") + " вы получили от отца " + PChar.GenQuest.ChurchQuest_1.ToName + " некоторые богословские труды, которые взялись доставить в " + XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.QuestTown) + ", поскольку направлялись в ту сторону.";
				link.l1.go = "ChurchGenQuest1_DialogShip_2";
			break;
			
		case "ChurchGenQuest1_DialogShip_2":
			dialog.text = "Я направлялся, да! Но этот проклятый шторм, чтоб его, чуть не прикончил мою старую посудину, и теперь я застрял здесь чёрт знает на сколько! Потому как эти мошенники в доках так и норовят залатать корпус гнилыми досками с разбитых лоханок, которые шторм прибил к берегу, а вместо парусов натянуть старую дерюгу, на которой околела ещё их прабабушка.";
				link.l1 = "Э-э... Сударь, в другой раз я с удовольствием выслушаю ваше мнение о прабабушке местных докеров, но сейчас я хотел"+ GetSexPhrase("","а") +" бы узнать судьбу книг и рукописей, которые вы получили в " + XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.ToColony + "Dat") + ".";
				link.l1.go = "ChurchGenQuest1_DialogShip_3";
			break;
			
		case "ChurchGenQuest1_DialogShip_3":
			dialog.text = "Никто - никто, слышите?! Никто не смеет обвинять меня в том, что я слишком задержался с доставкой этих треклятых бумажек!";
				link.l1 = "Упаси Господь, кто же посмеет?! Просто я хотел"+ GetSexPhrase("","а") +" избавить вас от излишнего беспокойства. Дело в том, что отец " + PChar.GenQuest.ChurchQuest_1.ToName + " весьма озабочен тем, чтобы книги и рукописи были доставлены по назначению в самое короткое время, а я как раз направляюсь прямиком в " + XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.QuestTown) + "...";
				link.l1.go = "ChurchGenQuest1_DialogShip_4";
			break;
			
		case "ChurchGenQuest1_DialogShip_4":
		if(rand(3) != 1)
		{
			dialog.text = "Сдаётся мне, судар"+ GetSexPhrase("ь","ыня") +", в каждом порту вам отпускает грехи очередной духовный наставник. Впрочем, это не моё дело. Если вам со всеми вашими наставниками так неймётся, берите свои книжки и проваливайте. Попутного ветра!";
				link.l1 = "Благодарю, г-н капитан, и желаю удачного ремонта.";
				link.l1.go = "ChurchGenQuest1_DialogShip_5_1";
		}
		else // Свитки не отдает
		{
			dialog.text = "Лучше избавьте от излишнего беспокойства себя сам"+ GetSexPhrase("ого","у") +", судар"+ GetSexPhrase("ь","ыня") +", и отправляйтесь в " +  XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.QuestTown) + " налегке, потому как я взялся доставить эти бумаги и я их доставлю, чего бы мне это ни стоило, ибо не родился еще тот прощелыга, который посмеет заявить, что капитан " + NPChar.name + " не держит слово!";
				link.l1 = "Но, господин капитан, дело не в том...";
				link.l1.go = "ChurchGenQuest1_DialogShip_5_2";
		}
			break;
			
		case "ChurchGenQuest1_DialogShip_5_1":
			DialogExit();
			AddItems(PChar, "Bible", 1);	// Даем рукописи
			items[FindItem("Bible")].Name = "itmname_ChurchGenQuest1Bible";	// Меняем имя. Потом поменять обратно!
			ChangeItemDescribe("Bible", "itmdescr_ChurchGenQuest1Bible"); // Меняем дескрайб. Потом поменять обратно!
			items[FindItem("Bible")].City = XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.QuestTown + "Gen"); // Переменная. Потом удалить!
			sQuestTitle = PChar.GenQuest.ChurchQuest_1.QuestTown + "ChurchGenQuest1";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest1", "10");
			AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("","а"));
			AddQuestUserData(sQuestTitle, "sColony", XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.QuestTown));
			AddQuestUserData(sQuestTitle, "sCapName", GetFullName(NPChar));
			PChar.GenQuest.ChurchQuest_1.Complete = true; // Квест выполнен
			SetFunctionTimerCondition("Church_GenQuest1_DeleteCapitan", 0, 0, 1, false); // Трем судно кэпа
			break;
			
		case "ChurchGenQuest1_DialogShip_5_2":
			dialog.text = "Дело в том, что собственно с Вами у меня нет никаких дел. У меня поручение от Святого Отца - отвезти книги в " + XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.QuestTown) + " и вручить их тамошнему Падре. Где тут Вы? Нету Вас никаким боком. Всего хорошего.";
//				link.l1 = "Что ж. Вы человек ответственный, но это Ваша единственная приятная черта. Всего хорошего, мой нелюбезный друг.";
//				link.l1.go = "ChurchGenQuest1_DialogShip_5_2_1"; // Сваливаем, поверили ему
				link.l2 = "Я достаточно долго терпел"+ GetSexPhrase("","а") +" ваше хамское обращение, но это ослиное упрямство и наглость способны вывести из себя даже ангела, не говоря уж обо мне, грешно"+ GetSexPhrase("м","й") +". Я долж"+ GetSexPhrase("ен","на") +" выполнить поручение моего духовника, и если вы не желаете добровольно отдать то, что вам не принадлежит, мне придётся обнажить оружие!";
				link.l2.go = "ChurchGenQuest1_DialogShip_5_2_2"; // 
			break;
			
		case "ChurchGenQuest1_DialogShip_5_2_1":
			DialogExit();
			sQuestTitle = PChar.GenQuest.ChurchQuest_1.QuestTown + "ChurchGenQuest1";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest1", "11");
			AddQuestUserData(sQuestTitle, "sColony", XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.QuestTown));
			AddQuestUserData(sQuestTitle, "sCapName", GetFullName(NPChar));
			PChar.GenQuest.ChurchQuest_1.Complete.NoManuscripts = true; // Квест выполнен без манускриптов
			SetFunctionTimerCondition("Church_GenQuest1_DeleteCapitan", 0, 0, 1, false); // Трем судно кэпа
			break;
			
		case "ChurchGenQuest1_DialogShip_5_2_2":
			dialog.text = "Тише, тише, капитан " + PChar.name + "! Эк Вас разобрало. Видать и правда, если не привезёте бумаги, то достанется Вам как следует от всех Ваших духовных Отцов, да и Отец Небесный ещё добавит. Берите свои богословские драгоценности и ступайте с Богом.";
				link.l1 = "Я рад"+ GetSexPhrase("","а") +", что вы не только вошли в моё положение, но и запомнили моё имя. Советую вам трижды повторять его всякий раз, как ваш дурной характер будет вредно отражаться на состоянии вашего здоровья.";
				link.l1.go = "ChurchGenQuest1_DialogShip_5_2_3"; // Сваливаем, поверили ему
			break;
			
		case "ChurchGenQuest1_DialogShip_5_2_3":
			DialogExit();
			AddItems(PChar, "Bible", 1);	// Даем рукописи
			items[FindItem("Bible")].Name = "itmname_ChurchGenQuest1Bible";	// Меняем имя. Потом поменять обратно!
			ChangeItemDescribe("Bible", "itmdescr_ChurchGenQuest1Bible"); // Меняем дескрайб. Потом поменять обратно!
			items[FindItem("Bible")].City = XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.QuestTown + "Gen"); // Переменная. Потом удалить!
			sQuestTitle = PChar.GenQuest.ChurchQuest_1.QuestTown + "ChurchGenQuest1";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest1", "10");
			AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("","а"));
			AddQuestUserData(sQuestTitle, "sColony", XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.QuestTown + "Dat"));
			AddQuestUserData(sQuestTitle, "sCapName", GetFullName(NPChar));
			PChar.GenQuest.ChurchQuest_1.Complete = true; // Квест выполнен
			SetFunctionTimerCondition("Church_GenQuest1_DeleteCapitan", 0, 0, 1, false); // Трем судно кэпа
			break;
			
		// <-- Церковеый генератор. Квест № 1. Диалог кэпа, которого ищем
			
		case "Left_Time_Case":
			dialog.text = RandPhraseSimple("Проваливай отсюда...", "Не мешай мне!");
				link.l1 = "...";
				link.l1.go = "exit";
				NextDiag.TempNode = "Left_Time_Case";
			break;
			
		case "Church_GenQuest_2_1":
			if(sti(PChar.GenQuest.ChurchQuest_2.BanditsCount) == 1)
			{
				dialog.text = RandSwear() + "А вот этого говорить не стоило... Теперь придётся отправить тебя к Господу, замаливать мои грехи!";
			}
			
			if(sti(PChar.GenQuest.ChurchQuest_2.BanditsCount) == 2)
			{
				dialog.text = RandSwear() + "А вот этого говорить не стоило... Теперь придётся отправить тебя к Господу, замаливать наши грехи!";
			}
			
			if(sti(PChar.GenQuest.ChurchQuest_2.BanditsCount) > 2)
			{
				dialog.text = RandSwear() + "А вот этого говорить не стоило... Теперь придётся отправить тебя к Господу, замаливать перед ним наши грехи!";
			}
			
				link.l1 = "Да нет уж, приятель. Перед Господом каждый будет отвечать за себя!";
				link.l1.go = "exit";
				NPChar.money = sti(PChar.GenQuest.ChurchQuest_2.MoneyCount);
				LAi_LocationFightDisable(LoadedLocation, false);
				AddDialogExitQuest("Church_GenQuest2_BanditsIsEnemies");
			break;
			
		case "Church_GenQuest_2_ShoreBandit_1":
			dialog.text = "А Вы не ругайтесь почём зря, у меня к Вам дело, может быть.";
				link.l1 = "Это новость! У меня с такими, как ты, разговор короткий.";
				link.l1.go = "Church_GenQuest_2_ShoreBandit_2";
				LAi_LocationFightDisable(LoadedLocation, false);
			break;
			
		case "Church_GenQuest_2_ShoreBandit_2":
			dialog.text = "А я с вами долго беседовать и не собираюсь. Предложить хотел - может, купите пару безделушек? Недорого отдадим...";
				link.l1 = "По-твоему я похож"+ GetSexPhrase("","а") +" на скупщи"+ GetSexPhrase("ка","цу") +" краденого?!!";
				link.l1.go = "Church_GenQuest_2_ShoreBandit_3";
			break;
			
		case "Church_GenQuest_2_ShoreBandit_3":
			if(rand(1) == 0)
			{
				dialog.text = "Полегче, уважаем"+ GetSexPhrase("ый","ая") +", среди нас нет воров! Эту вазу мы получили за честную работу. Вот, гляньте, чистое золото, а отделана жемчугом. Только нам-то она без надобности. Хотим продать и по-честному разделить деньги.";
					link.l1 = "Дай-ка посмотреть поближе... Ба! Да это же чаша для причастия!!! Так вы и есть те безбожники, что ограбили церковь " + XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_2.QuestTown + "Gen") + "?! Вот я вас и выследил"+ GetSexPhrase("","а") +"!";
					link.l1.go = "Church_GenQuest_2_ShoreBandit_4";
					break;
			}
		
			dialog.text = "Потише, госпо"+ GetSexPhrase("дин","жа") +" ханжа! Мы слегка поиздержались в путешествии и решили продать кое-что. Вот, гляньте на эту вазу: чистое золото, а отделана жемчугом. Хорошему человеку отдадим недорого... скажем, за тысячу монет.";
				link.l1 = "Дай-ка посмотреть поближе... Ба! Да это же чаша для причастия!!! Так вы и есть те безбожники, что ограбили церковь " + XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_2.QuestTown + "Gen") + "?! Вот я вас и выследил"+ GetSexPhrase("","а") +"!";
				link.l1.go = "Church_GenQuest_2_ShoreBandit_Real_Band_1";
			break;
			
		case "Church_GenQuest_2_ShoreBandit_4":
			dialog.text = "Эй, полегче на поворотах, судар"+ GetSexPhrase("ь","ыня") +"!.. Черт, я же просил этого олуха не поднимать шума раньше времени...";
				link.l1 = "Что ты там бормочешь?! Выбирай: или добровольно отдаёте краденое, или я зову стражу.";
				link.l1.go = "Church_GenQuest_2_ShoreBandit_5";
			break;
			
		case "Church_GenQuest_2_ShoreBandit_5":
			dialog.text = "Послушайте, "+ GetSexPhrase("мил человек","девушка") +", нам не нужна ссора... Давайте решим все по-тихому. Вам придётся поверить - церковь мы не грабили, и денег у нас нет. Да, мы получили несколько песо и золотую цацку за то, что изобразили ограбление. Эта чёртова чашка - единственное, что осталось после того, как мы расплатились с контрабандистами...";
				link.l1 = "И ты хочешь сказать, что...";
				link.l1.go = "Church_GenQuest_2_ShoreBandit_6";
			break;
			
		case "Church_GenQuest_2_ShoreBandit_6":
			dialog.text = "Проклятый священник сам нанял нас! Только зачем было погоню снаряжать?! Но, уж теперь-то мы в расчёте... Возьмите вазу и покажите её святоше, тут и сами увидите, что он станет извиваться, как кальмар на мелководье!..";
				link.l1 = "Давай сюда чашу и проваливайте, пока я не передумал"+ GetSexPhrase("","а") +".";
				link.l1.go = "Church_GenQuest_2_ShoreBandit_7";
				link.l2 = "Складно поёшь. Но я не так легковер"+ GetSexPhrase("ен","на") +". Хочешь убедить меня - убеди сначала мой клинок.";
				link.l2.go = "Church_GenQuest_2_ShoreBandit_8";
				// Тут давать чашу, если будет
				ChurchGenQuest2_GiveCup();
				PChar.GenQuest.ChurchQuest_2.Complete.PriestIsThief = true;
			break;
			
		case "Church_GenQuest_2_ShoreBandit_7":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			iBanditsCount = PChar.GenQuest.ChurchQuest_2.BanditsCount;
			for(i=0; i<iBanditsCount; i++)
			{
				rChar = CharacterFromID("Church_GenQuest2_Bandit_" + i);
				LAi_Type_Actor_Reset(rChar);
				LAi_CharacterDisableDialog(rChar);
				rChar.LifeDay = 0;
				LAi_ActorRunToLocation(rChar, "reload", "reload1_back", "none", "", "", "", -1);
			}
			
			// Разрешим генерацию энкаунтеров, откроем выходы
			DeleteAttribute(LoadedLocation, "DisableEncounters");
			chrDisableReloadToLocation = false;
			
			sQuestTitle = PChar.GenQuest.ChurchQuest_2.QuestTown + "ChurchGenQuest2";
			AddQuestrecordEx(sQuestTitle, "ChurchGenQuest2", "10_1");
			AddQuestUserData(sQuestTitle, "sName", PChar.GenQuest.ChurchQuest_2.QuestTown.PriestName);
			break;
			
		case "Church_GenQuest_2_ShoreBandit_8":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			AddDialogExitQuest("Church_GenQuest2_BanditsIsEnemies");
			sQuestTitle = PChar.GenQuest.ChurchQuest_2.QuestTown + "ChurchGenQuest2";
			AddQuestrecordEx(sQuestTitle, "ChurchGenQuest2", "10_2");
			break;
			
		case "Church_GenQuest_2_ShoreBandit_Real_Band_1":
			if(PChar.GenQuest.ChurchQuest_2.BanditsCount == 1)
			{
				dialog.text = RandSwear() + "Говорил я этим бакланам: придержите свои загребущие лапы, не тащите у попа ничего, кроме денег!";
			}
			else
			{
				dialog.text = RandSwear() + "Говорил я вам, бакланы ненасытные: придержите свои загребущие лапы, не тащите у попа ничего, кроме денег!";
			}
			
					link.l1 = "Что ты там бормочешь?! Выбирай: или добровольно отдаёте мне краденое, или я зову стражу.";
					link.l1.go = "Church_GenQuest_2_ShoreBandit_Real_Band_2";
			break;
			
		case "Church_GenQuest_2_ShoreBandit_Real_Band_2":
			dialog.text = "Я выбираю другое - ты закрываешь свой болтливый рот и даришь мне содержимое своего кошеля, а я дарю тебе жизнь.";
				link.l1 = "Сейчас я подарю тебе аудиенцию с Господом!";
				link.l1.go = "Church_GenQuest_2_ShoreBandit_Real_Band_2_1";
				link.l2 = "Так и быть, я дам тебе денег, но лишь из благородных побуждений. Чтобы ты и твои приятели могли начать честную жизнь. И не опускались до ограбления церкви.";
				link.l2.go = "Church_GenQuest_2_ShoreBandit_Real_Band_2_2";
				link.l3 = "Э-э... Давай забудем наши разногласия и вернёмся к началу разговора. Так сколько ты хотел за эту поделку?";
				link.l3.go = "Church_GenQuest_2_ShoreBandit_Real_Band_2_3";
			break;
			
		case "Church_GenQuest_2_ShoreBandit_Real_Band_2_1":
			// Не забыть чашу!
			ChurchGenQuest2_GiveCup();
			PChar.GenQuest.ChurchQuest_2.Complete.With_All = true;
			NPChar.money = ((rand(3) + 6) * 1000);
			PChar.GenQuest.ChurchQuest_2.MoneyCount = NPChar.money;
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			AddDialogExitQuest("Church_GenQuest2_BanditsIsEnemies");
			sQuestTitle = PChar.GenQuest.ChurchQuest_2.QuestTown + "ChurchGenQuest2";
			AddQuestrecordEx(sQuestTitle, "ChurchGenQuest2", "11_1");
			AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("ёл","ла"));
			AddQuestUserData(sQuestTitle, "sSex1", GetSexPhrase("","а"));
			break;
			
		case "Church_GenQuest_2_ShoreBandit_Real_Band_2_2":
			AddMoneyToCharacter(PChar, -sti(PChar.money)/2); // Забираем половину денег
			PChar.GenQuest.ChurchQuest_2.Complete.Without_All = true; // Полностью проигрышный вариант. Остаемся ни с чем
			iBanditsCount = PChar.GenQuest.ChurchQuest_2.BanditsCount;
			for(i=0; i<iBanditsCount; i++)
			{
				rChar = CharacterFromID("Church_GenQuest2_Bandit_" + i);
				LAi_SetCitizenType(rChar);
				rChar.LifeDay = 0;
				rChar.Dialog.Currentnode = "First time";
			}
			
			DeleteAttribute(PChar, "GenQuest.ChurchQuest_2.BanditsInShore");
			sQuestTitle = PChar.GenQuest.ChurchQuest_2.QuestTown + "ChurchGenQuest2";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest2", "11_2");
			AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("","а"));
			AddQuestUserData(sQuestTitle, "sSex1", GetSexPhrase("ся","ась"));
			DeleteAttribute(LoadedLocation, "DisableEncounters");
			chrDisableReloadToLocation = false;
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			break;
			
		case "Church_GenQuest_2_ShoreBandit_Real_Band_2_3":
			iMoney = makeint(makeint(Pchar.money)/20)*10;
			dialog.text = "Мне лишние проблемы тоже не нужны, " + GetAddress_Form(pchar) + ", но теперь цены повысились. За эту бесценную вазу я возьму всё, что у тебя есть.";
			if(iMoney >= makeint(Pchar.rank)*300)
			{
				link.l1 = "Алчное ты отребье!.. У меня с собой только" + FindRussianMoneyString(iMoney) + ". Берите и проваливайте!";
				link.l1.go = "Church_GenQuest_2_ShoreBandit_Real_Band_2_3_1";
			}
			else
			{
				link.l1 = "А вот здесь ты промахнулся, алчная крыса - за мой счет поживиться не удастся!"+ GetSexPhrase(" Я вольный ветер, сегодня - здесь, завтра - там, сегодня нищ, завтра богат...","") +"";
				link.l1.go = "Church_GenQuest_2_ShoreBandit_Real_Band_2_3_2";
			}
			break;
			
		case "Church_GenQuest_2_ShoreBandit_Real_Band_2_3_1":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			ChurchGenQuest2_GiveCup();	// Даем чашу
			AddMoneyToCharacter(PChar, -(makeint(makeint(Pchar.money)/20)*10));
			PChar.GenQuest.ChurchQuest_2.Complete.Only_With_Cup = true;
			iBanditsCount = PChar.GenQuest.ChurchQuest_2.BanditsCount;
			for(i=0; i<iBanditsCount; i++)
			{
				rChar = CharacterFromID("Church_GenQuest2_Bandit_" + i);
				LAi_SetCitizenType(rChar);
				rChar.LifeDay = 0;
				rChar.Dialog.Currentnode = "Left_Time_Case"; // Диалог не забыть поменять.
			}
			
			DeleteAttribute(LoadedLocation, "DisableEncounters");
			chrDisableReloadToLocation = false;
			sQuestTitle = PChar.GenQuest.ChurchQuest_2.QuestTown + "ChurchGenQuest2";
			AddQuestrecordEx(sQuestTitle, "ChurchGenQuest2", "11_3");
			AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("","а"));
			DeleteAttribute(PChar, "GenQuest.ChurchQuest_2.BanditsInShore");
			break;

		case "Church_GenQuest_2_ShoreBandit_Real_Band_2_3_2":
			dialog.text = "Уж не хочешь ли ты сказать, что именно сегодня "+ GetSexPhrase("ты нищ","у тебя нет денег") +"?!";
				link.l1 = "О да, мой бедный жадный друг! К твоему глубокому разочарованию. А теперь долж"+ GetSexPhrase("ен","на") +" откланяться, меня ждут великие дела.";
				link.l1.go = "Church_GenQuest_2_ShoreBandit_Real_Band_2_3_3";	
			break;
			
		case "Church_GenQuest_2_ShoreBandit_Real_Band_2_3_3":
			dialog.text = "Стой! Сейчас мы это проверим, и, если ты солгал"+ GetSexPhrase("","а") +", то я засуну твой лживый язык в муравейник!";
				link.l1 = "После таких слов тебе не жить!";
				link.l1.go = "Church_GenQuest_2_ShoreBandit_Real_Band_2_3_4";
			break;
			
		// Можно этот кэйс - Church_GenQuest_2_ShoreBandit_Real_Band_2_1
		case "Church_GenQuest_2_ShoreBandit_Real_Band_2_3_4":
				// ГГ как-бы может обыскать трупики и забрать все барахло...
				PChar.GenQuest.ChurchQuest_2.Complete.With_All = true;
				NPChar.money = ((rand(3) + 6) * 1000);
				PChar.GenQuest.ChurchQuest_2.MoneyCount = NPChar.money;
				DialogExit();
				NextDiag.CurrentNode = NextDiag.TempNode;
				AddDialogExitQuest("Church_GenQuest2_BanditsIsEnemies");
				sQuestTitle = PChar.GenQuest.ChurchQuest_2.QuestTown + "ChurchGenQuest2";
				AddQuestrecordEx(sQuestTitle, "ChurchGenQuest2", "11_4");
				AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("Как истинный джентльмен, я честен","Я честна"));
			break;
			
		///////////////////////////////////////////////////////////////////////////////////////////////////
		// ГЕНЕР "ПИРАТЫ НА НЕОБИТАЕМОМ ОСТРОВЕ"
		///////////////////////////////////////////////////////////////////////////////////////////////////
		
		case "PiratesOnUninhabited_1":
			dialog.text = "А ничего решать и не нужно. Мы сами всё решим. Только заберём твой кораблик, чтоб убраться отсюда.";
			link.l1 = "При одном условии: сначала заберите мой клинок...";
			link.l1.go = "PiratesOnUninhabited_2";
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "PiratesOnUninhabited_2":
			for(i = 0; i < sti(PChar.GenQuest.PiratesOnUninhabited.PiratesQty); i++)
			{
				LAi_SetImmortal(CharacterFromID("PirateOnUninhabited_" + i), false);
			}
			
			LAi_Group_SetRelation("PiratesOnUninhabitedGroup", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_Group_FightGroups("PiratesOnUninhabitedGroup", LAI_GROUP_PLAYER, true);
			DialogExit();
		break;
		
		case "PiratesOnUninhabited_3":
			PChar.GenQuest.PiratesOnUninhabited.MainPirateName = GetRandName(NAMETYPE_NICK, NAME_GEN);
			PChar.GenQuest.PiratesOnUninhabited.BadPirateName = GetRandName(NAMETYPE_ORIG, NAME_NOM);
			
				i = PiratesOnUninhabited_GenerateShipType();
				PChar.GenQuest.PiratesOnUninhabited.StartShipType = i;
			
			if(dRand(1) == 0)
			{
				PChar.GenQuest.PiratesOnUninhabited.Shipwrecked = true;
				
				dialog.text = "Здравствуйте капитан! Не иначе сам Бог прислал Вас на выручку " + PChar.GenQuest.PiratesOnUninhabited.MainPirateName + " и его ребят... Мы с приятелями оказались в очень затруднительном положении. " +
					"Наш " + GetStrSmallRegister(XI_ConvertString(ShipsTypes[i].Name)) + " разбило штормом о здешние рифы, а прилив вынес остатки команды на этот безлюдный пляж. " +
					"Целых " + (5 + dRand(7)) + " недель мы до боли в глазах всматривались в горизонт, надеясь увидеть парус хоть какого-то судёнышка.";
				link.l1 = RandPhraseSimple(RandPhraseSimple("Вам не позавидуешь. Но такова жизнь моряка - любой из нас мог оказаться на вашем месте", "Понимаю... Все мы в руках Господа, но у него видимо слишком много забот, чтобы помнить о каждом..."),
					RandPhraseSimple("Да уж. Человек предполагает, а Господь располагает.", "Да уж, попали вы в переделку..."));
				link.l1.go = "PiratesOnUninhabited_4";
			}
			else
			{
				dialog.text = "Куда уж серьёзнее! Этот негодяй " + PChar.GenQuest.PiratesOnUninhabited.BadPirateName + " не придумал худшего наказания, чем выбросить " + ChangeNameCase(NAMETYPE_NICK, PChar.GenQuest.PiratesOnUninhabited.MainPirateName, NAME_ACC) + " на необитаемый остров, как ненужный ботинок! " +
					"Он надеялся, что солнце и жажда высушат нас, как вяленую ставриду на прилавке лоточника! Но и здесь он просчитался - Провидение оказалось на нашей стороне, послав спасение в вашем лице...";
				link.l1 = RandPhraseSimple("Не так скоро, милейший. Насколько я могу понять - вы представители свободной профессии, и оказались здесь не случайно.", "Не рано ли говорить о спасении? Я так понял"+ GetSexPhrase("","а") +", что здесь вы оказались за особые, так сказать, заслуги.");
				link.l1.go = "PiratesOnUninhabited_41";
			}
		break;
		
		case "PiratesOnUninhabited_4":
			PChar.GenQuest.PiratesOnUninhabited.PiratesCount = 5 + dRand(5);
			
			dialog.text = RandPhraseSimple("Капитан, не откажите в любезности, помогите " + PiratesOnUninhabited_GetStringNum(sti(PChar.GenQuest.PiratesOnUninhabited.PiratesCount)) + " обездоленным. Ведь нам больше не на кого надеяться, кроме, как на Вас да Господа Бога.",
				"Капитан, не найдётся ли на Вашем корабле свободных рундуков " + PiratesOnUninhabited_GetStringNum(sti(PChar.GenQuest.PiratesOnUninhabited.PiratesCount)) + " обездоленным?");
			
			if(GetFreeCrewQuantity(PChar) >= sti(PChar.GenQuest.PiratesOnUninhabited.PiratesCount) && GetPassengersQuantity(PChar) < PASSENGERS_MAX)
			{
				link.l1 = "Да уж... и куда прикажете вас доставить?";
				link.l1.go = "PiratesOnUninhabited_5";
			}
			
			link.l2 = RandPhraseSimple(RandPhraseSimple("Увы, мне очень жаль, но на корабле нет ни одного свободного гамака, не говоря уже о каютах. Матросы спят на палубе, не имея возможности восстановить силы после тяжёлой вахты...",
				"Мне бы очень не хотелось вас разочаровывать, но на корабле команда с перегрузом, люди спят под открытым небом. Стоит вспыхнуть болезни, и я потеряю половину экипажа..."),
				RandPhraseSimple("Очень жаль, но кубрики на корабле переполнены. Матросы живут в тесноте, и у меня нет никакой возможности брать ещё и пассажиров...", "Вынужден"+ GetSexPhrase("","а") +" вас разочаровать, но на корабле команда с перегрузом. Я опасаюсь вспышки эпидемии..."));
			link.l2.go = "PiratesOnUninhabited_21";
			
			if(stf(PChar.reputation.nobility) <= REPUTATION_NEUTRAL)
			{
				link.l3 = "Вам ли, бывалому моряку, не знать, что присутствие на борту потерпевшего кораблекрушение - это дурная примета? Мои матросы просто выбросят всех вас за борт.";
				link.l3.go = "PiratesOnUninhabited_7";
			}
		break;
		
		case "PiratesOnUninhabited_5":
			dialog.text = "М-м, по ряду причин нам бы не хотелось попадаться на глаза представителям власти... Доставьте нас в какую-нибудь уютную бухту на обжитом острове или Мейне. А дальше мы уж сами будем выбираться.";
			link.l1 = "Что ж, и рундуков, и гамаков на судне достаточно. Загружайтесь в шлюпку.";
			link.l1.go = "PiratesOnUninhabited_10";
			link.l2 = "Хм. Вот незадача... Нам предстоят тяжёлые бои, и ещё неизвестно где вы будете в большей безопасности - у меня на борту или в этой уютной лагуне.";
			link.l2.go = "PiratesOnUninhabited_6";
		break;
		
		case "PiratesOnUninhabited_6":
			dialog.text = "О-о, капитан! В этой жизни даже под одеялом у жены никто не может чувствовать себя в безопасности. А уж в море и подавно... Взгляните на этих головорезов, готовых с голыми задницами лезть на неприятельскую картечь. Разве Вы видите в их лицах стремление к уюту и безопасности?..";
			link.l1 = "Я вижу в их лицах готовность при первом удобном случае воткнуть нож в спину доверчивого благодетеля.";
			link.l1.go = "PiratesOnUninhabited_7";
			link.l2 = "Хм, а ведь это неплохая мысль. Скажи-ка приятель, а готовы ли твои головорезы пойти ко мне в команду?";
			link.l2.go = "PiratesOnUninhabited_8";
		break;
		
		case "PiratesOnUninhabited_7":
			dialog.text = "Жаль, капитан... я вижу по-хорошему нам не договориться. Что ж, придётся напомнить вам морской устав. Но учтите - нам не впервой брать суда абордажем...";
			link.l1 = "Вот теперь я вижу, кто вы есть на самом деле...";
			link.l1.go = "PiratesOnUninhabited_2";
			AddDialogExitQuest("MainHeroFightModeOn");
			ChangeCharacterComplexReputation(pchar,"nobility", -3.0);
		break;
		
		// Берем их в команду
		case "PiratesOnUninhabited_8":
			dialog.text = "Ого-го! Что я слышу! Клянусь, что каждый из них спал и видел себя в составе вашей абордажной команды! В горячей схватке разве только черти способны противостоять им.";
			link.l1 = "Вот и по рукам! Грузитесь в шлюпки...";
			link.l1.go = "PiratesOnUninhabited_9";
		break;
		
		case "PiratesOnUninhabited_9":
			bTemp = CheckAttribute(PChar, "GenQuest.PiratesOnUninhabited.Shipwrecked");
			
			for(i = 0; i < sti(PChar.GenQuest.PiratesOnUninhabited.PiratesQty); i++)
			{
				rChar = CharacterFromID("PirateOnUninhabited_" + i);
				LAi_SetWarriorTypeNoGroup(rChar);
				rChar.LifeDay = 0;
				
				if(bTemp)
				{
					rChar.Dialog.currentnode = "PiratesOnUninhabited_11_Again";
				}
				else
				{
					rChar.Dialog.currentnode = "PiratesOnUninhabited_43_again";
				}
			}
			
			AddCharacterCrew(PChar, sti(PChar.GenQuest.PiratesOnUninhabited.PiratesCount));
			
			Log_Info("Ваша команда пополнилась на " + PChar.GenQuest.PiratesOnUninhabited.PiratesCount + " человек.");
			OfficersReaction("bad");
			
			//PChar.Quest.PiratesOnUninhabited_LocExit.over = "yes"; // Снимаем прерывание на выход из локации
			
			//DeleteAttribute(PChar, "GenQuest.PiratesOnUninhabited");
			
			DialogExit();
			
			// Конец квеста
		break;
		
		case "PiratesOnUninhabited_10":
			dialog.text = "Спасибо, капитан! Погрузка не займёт много времени. Как мы все молились, чтобы этот момент наступил скорее...";
			link.l1 = "Ну вот и прекрасно.";
			link.l1.go = "PiratesOnUninhabited_11";
		break;
		
		// Берем их в пассажирами - держать курс на населенный остров
		case "PiratesOnUninhabited_11":
			for(i = 0; i < sti(PChar.GenQuest.PiratesOnUninhabited.PiratesQty); i++)
			{
				rChar = CharacterFromID("PirateOnUninhabited_" + i);
				LAi_SetWarriorTypeNoGroup(rChar);
				rChar.Dialog.currentnode = "PiratesOnUninhabited_11_Again";
			}
			
			Log_Info("Ваша команда пополнилась на " + PChar.GenQuest.PiratesOnUninhabited.PiratesCount + " человек.");
			
			ChangeCharacterComplexReputation(pchar,"nobility", 3.0);
			
			AddCharacterCrew(PChar, sti(PChar.GenQuest.PiratesOnUninhabited.PiratesCount) - 1);
			OfficersReaction("good");
			PChar.Quest.PiratesOnUninhabited_LocExit.over = "yes"; // Снимаем прерывание на выход из локации
			
			AddPassenger(PChar, NPChar, false); // Главного в пассажиры
			SetCharacterRemovable(NPChar, false);
			
			sTemp = XI_ConvertString(PChar.location + "Dat");
			
			sTitle = "PiratesOnUninhabited" + PChar.location;
			ReOpenQuestHeader(sTitle);
			
			if(!CheckAttribute(PChar, "GenQuest.PiratesOnUninhabited.TreasureMap"))
			{
				if(CheckAttribute(PChar, "GenQuest.PiratesOnUninhabited.Shipwrecked"))
				{
				AddQuestRecordEx(sTitle, "PiratesOnUninhabited", "1");
					AddQuestUserData(sTitle, "shipTypeName", GetStrSmallRegister(XI_ConvertString(ShipsTypes[sti(PChar.GenQuest.PiratesOnUninhabited.StartShipType)].name + "Acc")));
			}
			else
			{
					AddQuestRecordEx(sTitle, "PiratesOnUninhabited", "11");
					AddQuestUserData(sTitle, "pirateName", ChangeNameCase(NAMETYPE_ORIG, PChar.GenQuest.PiratesOnUninhabited.BadPirateName, NAME_ABL));
				}
			}
			else
			{
				AddQuestRecordEx(sTitle, "PiratesOnUninhabited", "5");
				AddQuestUserData(sTitle, "shipTypeName", GetStrSmallRegister(XI_ConvertString(ShipsTypes[sti(PChar.GenQuest.PiratesOnUninhabited.StartShipType)].name + "Acc")));
			}
			
			AddQuestUserDataForTitle(sTitle, "shoreName", sTemp);
			AddQuestUserData(sTitle, "shoreName", sTemp);
			AddQuestUserData(sTitle, "count", PChar.GenQuest.PiratesOnUninhabited.PiratesCount);
			
			PChar.GenQuest.PiratesOnUninhabited.StartShore = PChar.location;
			
			PChar.Quest.PiratesOnUninhabited_LocExitGood.win_condition.l1 = "ExitFromLocation";
			PChar.Quest.PiratesOnUninhabited_LocExitGood.win_condition.l1.location = PChar.location;
			PChar.Quest.PiratesOnUninhabited_LocExitGood.function = "PiratesOnUninhabited_LocationExit_Good";
			
			PChar.Quest.PiratesOnUninhabited_OnShore.win_condition.l1 = "Location_Type";
			PChar.Quest.PiratesOnUninhabited_OnShore.win_condition.l1.location_type = "seashore";
			PChar.Quest.PiratesOnUninhabited_OnShore.again = true;
			PChar.Quest.PiratesOnUninhabited_OnShore.function = "PiratesOnUninhabited_OnShore";
			
			PChar.Quest.PiratesOnUninhabited_OnMayak.win_condition.l1 = "Location_Type";
			PChar.Quest.PiratesOnUninhabited_OnMayak.win_condition.l1.location_type = "mayak";
			PChar.Quest.PiratesOnUninhabited_OnMayak.again = true;
			PChar.Quest.PiratesOnUninhabited_OnMayak.function = "PiratesOnUninhabited_OnShore";
			
			DialogExit();
		break;
		
		case "PiratesOnUninhabited_11_Again":
			dialog.text = LinkRandPhrase("Чего же Вы медлите, капитан? Прикажите сниматься с якоря...", "Извините, капитан, нам нужно готовиться к отплытию.", "Какая удача, что Вы решили здесь высадиться!");
			link.l1 = "Поторопитесь. Судно никого ждать не будет...";
			link.l1.go = "exit";
			NextDiag.TempNode = "PiratesOnUninhabited_11_Again";
		break;
		
		// Базар с главарем уже в другой бухте на обитаемом острове
		case "PiratesOnUninhabited_12":
			if(dRand(1) == 0)
			{
				// Успешное завершение квеста - даст награду
				dialog.text = "Спасибо Вам, капитан. Не зря мы верили в свою удачу... Вот возьмите изумруд, я нашёл его в той злополучной бухте. Пусть он принесёт удачу и Вам.";
				link.l1 = "Никак не ожидал"+ GetSexPhrase("","а") +" получить такой подарок. Спасибо и удачи вам... Прощайте.";
				link.l1.go = "PiratesOnUninhabited_13";
			}
			else
			{
				// Требуют денег
				dialog.text = "Капитан, не сочтите за наглость, но мы несколько поиздержались. Шутка ли потерять всё. Не могли бы вы ссудить нам пару горстей песо на первое время? Мы обязательно их вернём... при случае...";
				link.l1 = "Ого! По истине наглость человеческая безгранична. Единственное, что я могу добавить к уже сделанному - это не сообщать о вас властям.";
				link.l1.go = "PiratesOnUninhabited_15";
				link.l2 = "Однако же... И сколько вы хотите песо?";
				link.l2.go = "PiratesOnUninhabited_17";
			}
			
			RemovePassenger(PChar, NPChar);
			RemoveCharacterCrew(PChar, sti(PChar.GenQuest.PiratesOnUninhabited.PiratesCount) - 1);
		break;
		
		case "PiratesOnUninhabited_13":
			AddItems(PChar, "jewelry4", 1);
			
			for(i = 0; i < sti(PChar.GenQuest.PiratesOnUninhabited.PiratesQty); i++)
			{
				rChar = CharacterFromID("PirateOnUninhabited_" + i);
				LAi_SetWarriorTypeNoGroup(rChar);
				LAi_SetImmortal(rChar, false);
				rChar.LifeDay = 0;
				
				rChar.Dialog.currentnode = "PiratesOnUninhabited_14";
			}
			
			sTitle = "PiratesOnUninhabited" + PChar.GenQuest.PiratesOnUninhabited.StartShore;
			AddQuestRecordEx(sTitle, "PiratesOnUninhabited", "2");
			AddQuestUserData(sTitle, "sSex", GetSexPhrase("","а"));
			AddQuestUserData(sTitle, "toShore", LowerFirst(XI_ConvertString(PChar.location + "Acc")));
			CloseQuestHeader(sTitle);
			
			DeleteAttribute(PChar, "GenQuest.PiratesOnUninhabited");
			
			DialogExit();
			
			// Конец квеста
		break;
		
		case "PiratesOnUninhabited_14":
			dialog.text = LinkRandPhrase("Спасибо Вам, капитан.", "Капитан, мы Вам очень благодарны.", "Мы будем молиться за Вас, капитан " + PChar.name + "!");
			link.l1 = "Удачи вам. Прощайте...";
			link.l1.go = "exit";
			NextDiag.TempNode = "PiratesOnUninhabited_14";
		break;
		
		case "PiratesOnUninhabited_15":
			dialog.text = "Эх, капитан... а ведь мы до этого так хорошо ладили. Жаль будет Вас убивать...";
			link.l1 = "Что ж, попробуйте!";
			link.l1.go = "PiratesOnUninhabited_16";
			AddDialogExitQuest("MainHeroFightModeOn");
			ChangeCharacterComplexReputation(pchar,"nobility", 2.0);
		break;
		
		case "PiratesOnUninhabited_16":
			for(i = 0; i < sti(PChar.GenQuest.PiratesOnUninhabited.PiratesQty); i++)
			{
				rChar = CharacterFromID("PirateOnUninhabited_" + i);
				
				LAi_SetImmortal(rChar, false);
				rChar.LifeDay = 0;
			}
			
			LAi_Group_SetRelation("PiratesOnUninhabitedGroup", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_Group_FightGroups("PiratesOnUninhabitedGroup", LAI_GROUP_PLAYER, true);
			
			sTitle = "PiratesOnUninhabited" + PChar.GenQuest.PiratesOnUninhabited.StartShore;
			AddQuestRecordEx(sTitle, "PiratesOnUninhabited", "3");
			AddQuestUserData(sTitle, "sSex", GetSexPhrase("","а"));
			AddQuestUserData(sTitle, "toShore", LowerFirst(XI_ConvertString(PChar.location + "Acc")));
			CloseQuestHeader(sTitle);
			
			DeleteAttribute(PChar, "GenQuest.PiratesOnUninhabited");
			
			DialogExit();
			
			// Конец квеста
		break;
		
		case "PiratesOnUninhabited_17":
			iMoney = sti(PChar.rank) * 500;
			PChar.GenQuest.PiratesOnUninhabited.Money = iMoney * sti(PChar.GenQuest.PiratesOnUninhabited.PiratesCount);
			
			dialog.text = "Ну скажем, по " + iMoney + " песо на брата, нас бы вполне устроило... Если конечно капитан не считает, что это слишком малая компенсация, за те лишения, которые выпали на нашу долю... хе-хе...";
			link.l1 = RandPhraseSimple("Как раз напротив! Я считаю, что это слишком много... Каждому по петле на шею - вот это было бы в самый раз!", "Да за такие деньги я сам"+ GetSexPhrase("","а") +" развешаю вас, как обезьян на пальмах!");
			link.l1.go = "PiratesOnUninhabited_18";
			
			if(sti(PChar.money) >= iMoney * sti(PChar.GenQuest.PiratesOnUninhabited.PiratesCount))
			{
				link.l2 = "Что ж, возьмите... Надеюсь больше я вам ничего не долж"+ GetSexPhrase("ен","на") +"?";
				link.l2.go = "PiratesOnUninhabited_19";
			}
		break;
		
		case "PiratesOnUninhabited_18":
			dialog.text = "Ах, какая щедрость! А я думал, Вы уже успели убедиться, что мы всегда получаем желаемое. И в этот раз уступать не намерены...";
			link.l1 = "Что ж, попробуйте!";
			link.l1.go = "PiratesOnUninhabited_16";
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "PiratesOnUninhabited_19":
			dialog.text = "Ну, что Вы, капитан, как можно?! Мы обязательно поставим за Вас свечку... Если когда-нибудь доберёмся до церкви...";
			link.l1 = "Будем надеяться...";
			link.l1.go = "PiratesOnUninhabited_20";
			
			iMoney = sti(PChar.GenQuest.PiratesOnUninhabited.Money);
			
			AddMoneyToCharacter(PChar, -iMoney);
			AddMoneyToCharacter(NPChar, iMoney);
		break;
		
		case "PiratesOnUninhabited_20":
			for(i = 0; i < sti(PChar.GenQuest.PiratesOnUninhabited.PiratesQty); i++)
			{
				rChar = CharacterFromID("PirateOnUninhabited_" + i);
				
				LAi_SetWarriorTypeNoGroup(rChar);
				LAi_CharacterDisableDialog(rChar);
				LAi_SetImmortal(rChar, false);
				rChar.LifeDay = 0;
			}
			
			ChangeCharacterComplexReputation(pchar,"nobility", 2.0);
			OfficersReaction("good");
			
			sTitle = "PiratesOnUninhabited" + PChar.GenQuest.PiratesOnUninhabited.StartShore;
			AddQuestRecordEx(sTitle, "PiratesOnUninhabited", "4");
			AddQuestUserData(sTitle, "sSex", GetSexPhrase("","а"));
			AddQuestUserData(sTitle, "sSex1", GetSexPhrase("ся","ась"));
			AddQuestUserData(sTitle, "toShore", LowerFirst(XI_ConvertString(PChar.location + "Acc")));
			CloseQuestHeader(sTitle);
			
			NPChar.SaveItemsForDead = true; // сохранять на трупе вещи
			NPChar.DontClearDead = true;  // не убирать труп через 200с
			
			DeleteAttribute(PChar, "GenQuest.PiratesOnUninhabited");
			
			DialogExit();
			
			// Конец квеста
		break;
		
		case "PiratesOnUninhabited_21":
			if(GetFreeCrewQuantity(PChar) >= sti(PChar.GenQuest.PiratesOnUninhabited.PiratesCount))
			{
				// Игрок врет - свободное место есть
				dialog.text = "Ну, что Вы, капитан, как можно?! Мы обязательно поставим за Вас свечку... Если когда-нибудь доберёмся до церкви...";
				link.l1 = "Будем надеяться...";
				link.l1.go = "PiratesOnUninhabited_23";
			}
			else
			{
				dialog.text = "Хе-х, капитан, а ведь это легко поправить. Я со своими молодцами готов освободить с десяток гамаков на твоём корабле от их постояльцев...";
				link.l1 = "Хм... это звучит, как угроза...";
				link.l1.go = "PiratesOnUninhabited_22";
			}
		break;
		
		case "PiratesOnUninhabited_22":
			dialog.text = "А это угроза и есть. Мне нужно твоё корыто! И я отсюда уберусь, с твоего согласия или без!";
			link.l1 = "Вот теперь я вижу, кто вы есть на самом деле...";
			link.l1.go = "PiratesOnUninhabited_2";
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "PiratesOnUninhabited_23":
			dialog.text = "Я понимаю Вас, капитан. Я Вас прекрасно понимаю... Кому охота возиться с бедными пиратами, по которым давно петля плачет?.. А если я предложу Вам обмен? Вы доставляете нас в любую бухту на обжитом острове или Мейне, а я Вам за это даю карту клада... Идёт?";
			link.l1 = "Хм... а где гарантии, что эта карта - не фальшивка?";
			link.l1.go = "PiratesOnUninhabited_25";
			link.l2 = "Ха-х, уверен"+ GetSexPhrase("","а") +", что цена вашей карте не больше, чем клочку бумаги на котором она намалёвана...";
			link.l2.go = "PiratesOnUninhabited_24";
		break;
		
		case "PiratesOnUninhabited_24":
			dialog.text = "Что ж... Вы не оставляете нам выбора... Мы в любом случае намерены убраться из этого места. С Вашего согласия или без...";
			link.l1 = "Вот теперь я вижу, кто вы есть на самом деле...";
			link.l1.go = "PiratesOnUninhabited_2";
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "PiratesOnUninhabited_25":
			dialog.text = "А где гарантии, что вы не сдадите нас властям в первом же порту?.. Оба играем втёмную...";
			link.l1 = "Ну хорошо, считайте, что мы договорились.";
			link.l1.go = "PiratesOnUninhabited_11";
			PChar.GenQuest.PiratesOnUninhabited.TreasureMap = true;
		break;
		
		// Базар с главарем уже в другой бухте на обитаемом острове. Вариант, когда нам обещали карту сокровищ
		case "PiratesOnUninhabited_26":
			// PChar.GenQuest.PiratesOnUninhabited.MainPirateName - имя в родительном падеже
			
			dialog.text = "Спасибо тебе, капитан " + PChar.name + ". Ты выполнил"+ GetSexPhrase("","а") +" своё обещание, пришло время " + ChangeNameCase(NAMETYPE_NICK, PChar.GenQuest.PiratesOnUninhabited.MainPirateName, NAME_DAT) + " выполнять своё. Карты у меня с собой нет, но я тебе расскажу где сокровища. Отправляйся в бухту...";
			link.l1 = "Вот как ты запел! Значит всё-таки решил меня надуть...";
			link.l1.go = "PiratesOnUninhabited_27";
			link.l2 = "А ведь я сразу тебе не поверил"+ GetSexPhrase("","а") +"... Жаль, не сдал"+ GetSexPhrase("","а") +" властям - хоть что-то бы заработал"+ GetSexPhrase("","а") +".";
			link.l2.go = "PiratesOnUninhabited_30";
			link.l3 = "Вот так и верь пиратам. Что ж вы за люди такие? Ничего святого за душой...";
			link.l3.go = "PiratesOnUninhabited_33";
			
			RemovePassenger(PChar, NPChar);
			RemoveCharacterCrew(PChar, sti(PChar.GenQuest.PiratesOnUninhabited.PiratesCount) - 1);
		break;
		
		case "PiratesOnUninhabited_27":
			dialog.text = "Не суетись... Я конечно не святой, но слово своё держу!";
			link.l1 = "Ты думаешь я поверю тебе ещё раз?! Чтобы завтра надо мной потешался весь архипелаг?!";
			link.l1.go = "PiratesOnUninhabited_28";
		break;
		
		case "PiratesOnUninhabited_28":
			dialog.text = "Гхм... по всему видать, - мирного исхода не получится. Но видит Бог, я этого не хотел...";
			link.l1 = "Обнажай свой клинок! Иначе мне придётся просто раздавить тебя, как крысу!";
			link.l1.go = "PiratesOnUninhabited_29";
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "PiratesOnUninhabited_29":
			for(i = 0; i < sti(PChar.GenQuest.PiratesOnUninhabited.PiratesQty); i++)
			{
				rChar = CharacterFromID("PirateOnUninhabited_" + i);
				
				LAi_SetImmortal(rChar, false);
				rChar.LifeDay = 0;
			}
			
			LAi_Group_SetRelation("PiratesOnUninhabitedGroup", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_Group_FightGroups("PiratesOnUninhabitedGroup", LAI_GROUP_PLAYER, true);
			
			sTitle = "PiratesOnUninhabited" + PChar.GenQuest.PiratesOnUninhabited.StartShore;
			AddQuestRecordEx(sTitle, "PiratesOnUninhabited", "6");
			CloseQuestHeader(sTitle);
			
			DeleteAttribute(PChar, "GenQuest.PiratesOnUninhabited");
			
			DialogExit();
			
			// Конец квеста
		break;
		
		case "PiratesOnUninhabited_30":
			sTitle = PiratesOnUninhabited_GenerateTreasureShore(&sTemp);
			PChar.GenQuest.PiratesOnUninhabited.TreasureShore = sTitle;
			PChar.GenQuest.PiratesOnUninhabited.TreasureBox = sTemp;
			
			dialog.text = "А что мне оставалось делать? Сгнить в той вонючей луже вместе с моими людьми? Лучше выслушай до конца... " + XI_ConvertString(sTitle + "Dat") + " у капитана " + ChangeNameCase(NAMETYPE_ORIG, PChar.GenQuest.PiratesOnUninhabited.BadPirateName, NAME_GEN) + " есть тайник, в котором он хранит свою добычу. Но будь осторож"+ GetSexPhrase("ен","на") +", он туда частенько наведывается. Найти тайник несложно, если ты с головой дружишь...";
			link.l1 = "Ты думаешь я поверю тебе ещё раз?! Чтобы завтра надо мной потешался весь архипелаг?!";
			link.l1.go = "PiratesOnUninhabited_28";
			link.l2 = "Ну, гляди. Если и на этот раз обманул - из-под земли достану.";
			link.l2.go = "PiratesOnUninhabited_31";
		break;
		
		case "PiratesOnUninhabited_31":
			for(i = 0; i < sti(PChar.GenQuest.PiratesOnUninhabited.PiratesQty); i++)
			{
				rChar = CharacterFromID("PirateOnUninhabited_" + i);
				
				LAi_SetWarriorTypeNoGroup(rChar);
				LAi_SetImmortal(rChar, false);
				rChar.LifeDay = 0;
				rChar.Dialog.currentnode = "PiratesOnUninhabited_32";
			}
			
			sTitle = "PiratesOnUninhabited" + PChar.GenQuest.PiratesOnUninhabited.StartShore;
			AddQuestRecordEx(sTitle, "PiratesOnUninhabited", "7");
			AddQuestUserData(sTitle, "capName", ChangeNameCase(NAMETYPE_ORIG, PChar.GenQuest.PiratesOnUninhabited.BadPirateName, NAME_NOM));
			AddQuestUserData(sTitle, "toShore", LowerFirst(XI_ConvertString(PChar.GenQuest.PiratesOnUninhabited.TreasureShore + "Acc")));
			
			// Таймер для клада. По прошествии 10 дней в кладе будут всякие бакланы и т.д.
			PChar.Quest.PiratesOnUninhabited_TreasureLose.win_condition.l1 = "Timer";
			PChar.Quest.PiratesOnUninhabited_TreasureLose.win_condition.l1.date.day = GetAddingDataDay(0, 0, 10);
			PChar.Quest.PiratesOnUninhabited_TreasureLose.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 10);
			PChar.Quest.PiratesOnUninhabited_TreasureLose.win_condition.l1.date.year = GetAddingDataYear(0, 0, 10);
			PChar.Quest.PiratesOnUninhabited_TreasureLose.win_condition = "PiratesOnUninhabited_TreasureLose";
			
			PChar.Quest.PiratesOnUninhabited_InTreasureLoc.win_condition.l1 = "Location";
			PChar.Quest.PiratesOnUninhabited_InTreasureLoc.win_condition.l1.Location = PChar.GenQuest.PiratesOnUninhabited.TreasureShore;
			PChar.Quest.PiratesOnUninhabited_InTreasureLoc.function = "PiratesOnUninhabited_InTreasureLoc";
			
			DialogExit();
			
			// Курс в бухту, которую назвал пират. У нас сроку 10 дней, котом клад пропадет
		break;
		
		case "PiratesOnUninhabited_32":
			sTemp = ChangeNameCase(NAMETYPE_NICK, PChar.GenQuest.PiratesOnUninhabited.MainPirateName, NAME_ACC);
			
			dialog.text = LinkRandPhrase("Послушайте " + sTemp + ", он дело говорит.", "Не обижайтесь на " + sTemp + ", у него не было другого выхода.", "Спасибо Вам, капитан.");
			link.l1 = "Счастливо оставаться...";
			link.l1.go = "exit";
			NextDiag.TempNode = "PiratesOnUninhabited_32";
		break;
		
		case "PiratesOnUninhabited_33":
			sTitle = PiratesOnUninhabited_GenerateTreasureShore(&sTemp);
			PChar.GenQuest.PiratesOnUninhabited.TreasureShore = sTitle;
			PChar.GenQuest.PiratesOnUninhabited.TreasureBox = sTemp;
			
			dialog.text = "А что мне оставалось делать? Сгнить в той вонючей луже вместе с моими людьми? Лучше выслушай до конца... " + XI_ConvertString(sTitle + "Dat") + " у капитана " + ChangeNameCase(NAMETYPE_ORIG, PChar.GenQuest.PiratesOnUninhabited.BadPirateName, NAME_GEN) + " есть тайник, в котором он хранит свою добычу. Но будь осторож"+ GetSexPhrase("ен","на") +", он туда частенько наведывается. Найти тайник несложно, если ты с головой дружишь...";
			link.l1 = "Ты думаешь я поверю тебе ещё раз?! Чтобы завтра надо мной потешался весь архипелаг?!";
			link.l1.go = "PiratesOnUninhabited_28";
		break;
		
		// Пираты в бухте с сокровищем
		case "PiratesOnUninhabited_34":
			dialog.text = "Ты кто так"+ GetSexPhrase("ой, приятель","ая, подруга") +",? И что привело тебя в это безлюдное место?";
			link.l1 = "Я остановил"+ GetSexPhrase("ся","ась") +" пополнить запасы пресной воды.";
			link.l1.go = "PiratesOnUninhabited_35";
			link.l2 = "Я здесь по поручению " + ChangeNameCase(NAMETYPE_NICK, PChar.GenQuest.PiratesOnUninhabited.MainPirateName, NAME_GEN) + ".";
			link.l2.go = "PiratesOnUninhabited_38";
			NextDiag.TempNode = "PiratesOnUninhabited_34";
		break;
		
		case "PiratesOnUninhabited_35":
			dialog.text = "Неудачное ты место выбрал"+ GetSexPhrase("","а") +"... Ну да ладно, пополняй, только не задерживайся...";
			link.l1 = "Угу...";
			link.l1.go = "exit";
			link.l2 = "А почему ты решил, что можешь мне указывать?";
			link.l2.go = "PiratesOnUninhabited_36";
		break;
		
		case "PiratesOnUninhabited_36":
			dialog.text = "Потому что я всем здесь указываю. А кто слишком умный - тот будет болтаться на пальме.";
			link.l1 = "Придётся подрезать тебе язык.";
			link.l1.go = "PiratesOnUninhabited_37";
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "PiratesOnUninhabited_37":
			DialogExit();
			LAi_Group_SetRelation("PiratesOnUninhabited_ShoreGroup", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
		break;
		
		case "PiratesOnUninhabited_38":
			dialog.text = "А чего же он сам не явился?";
			link.l1 = "Не захотел, остался " + LowerFirst(XI_ConvertString(PChar.GenQuest.PiratesOnUninhabited.StartShore + "Dat")) + " меня дожидаться.";
			link.l1.go = "PiratesOnUninhabited_39";
		break;
		
		case "PiratesOnUninhabited_39":
			dialog.text = "Ах старая каналья! Опять решил нас надуть! Ну, это у него не пройдёт. Передай, что деньги он сможет забрать только вместе с нами!";
			link.l1 = "Он велел без денег не возвращаться и на борт никого не брать...";
			link.l1.go = "PiratesOnUninhabited_40";
		break;
		
		case "PiratesOnUninhabited_40":
			dialog.text = "Раз уж ты ему так веришь, то можешь оставаться здесь. А мы заберём твой корабль, прихватим денежки и отправимся " + LowerFirst(XI_ConvertString(PChar.GenQuest.PiratesOnUninhabited.StartShore + "Acc")) + ". Нам очень хочется взглянуть в лицо " + PChar.GenQuest.PiratesOnUninhabited.MainPirateName + ".";
			link.l1 = "Если вы так по нему соскучились - можете отправляться вплавь... а можете подохнуть здесь.";
			link.l1.go = "PiratesOnUninhabited_37";
			AddDialogExitQuest("MainHeroFightModeOn");
			PChar.GenQuest.PiratesOnUninhabited.UseMainPiratename = true;
		break;
		
		// Ветка из PiratesOnUninhabited_3
		case "PiratesOnUninhabited_41":
			iBanditsCount = 5 + dRand(5);
			iMoney = GetFreeCrewQuantity(PChar);
			
			PChar.GenQuest.PiratesOnUninhabited.PiratesCount = iBanditsCount;
			
			dialog.text = "А Вы проницательный человек. Но уверяю Вас, что наш конфликт с капитаном " + ChangeNameCase(NAMETYPE_ORIG, PChar.GenQuest.PiratesOnUninhabited.BadPirateName, NAME_ABL) + " возник исключительно на почве идейных разногласий. Я предупреждал, что его скверные делишки не останутся безнаказанными, а теперь мне и " + iBanditsCount + "-м моим единомышленникам приходится страдать за нашу любовь к Богу и справедливости...";
			link.l1 = "Как же... Небось бунт на корабле подняли или проворовались. Вот и досталось вам поделом.";
			link.l1.go = "PiratesOnUninhabited_42";
			
			if(iMoney >= iBanditsCount - 1 && GetPassengersQuantity(PChar) < PASSENGERS_MAX)
			{
				link.l2 = "Угу... было бы ещё неплохо узнать мнение самого капитана " + ChangeNameCase(NAMETYPE_ORIG, PChar.GenQuest.PiratesOnUninhabited.BadPirateName, NAME_GEN) + " по поводу ваших разногласий.";
				link.l2.go = "PiratesOnUninhabited_44";
			}
		break;
		
		case "PiratesOnUninhabited_42":
			dialog.text = "Капитан, зачем же обижать недоверием честных людей? Ты погляди на эти лица, - разве ж они похожи на бунтарей?.. Аки агнецы небесные во плоти... Но за правое дело, да под умелым началом - в драке равных им не будет! Ручаюсь за каждого.";
			link.l1 = "И что же мне с вами прикажете делать?";
			link.l1.go = "PiratesOnUninhabited_43";
		break;
		
		case "PiratesOnUninhabited_43":
			iBanditsCount = sti(PChar.GenQuest.PiratesOnUninhabited.PiratesCount);
			iMoney = GetFreeCrewQuantity(PChar);
			
			dialog.text = "А что хочешь, то и делай. Хочешь - в бухту обжитую доставь, хочешь - в команду возьми.";
			
			if(iMoney >= iBanditsCount)
			{
				link.l1 = "Хорошо, давайте в команду. Только гляди мне, - не баловать! У меня с этим строго!";
				link.l1.go = "PiratesOnUninhabited_9"; // Берем в команду
			}
			
			link.l2 = "Не повезу я вас никуда. У меня в команде и своих головорезов хватает.";
			link.l2.go = "PiratesOnUninhabited_24"; // Рубилово и конец квеста
			
			if(iMoney >= iBanditsCount - 1 && GetPassengersQuantity(PChar) < PASSENGERS_MAX)
			{
				link.l3 = "Ладно, садитесь в шлюпку, отвезу вас куда-нибудь.";
				link.l3.go = "PiratesOnUninhabited_11"; // В пассажиры и на остров
			}
		break;
		
		case "PiratesOnUninhabited_43_again":
			dialog.text = LinkRandPhrase("Клянусь, капитан, Вы не пожалеете.", "Вы очень правильно сделали, капитан.", "Капитан, будьте уверены, что Вам повезло не меньше нашего!");
			link.l1 = RandPhraseSimple("Хочется в это верить.", "Поторопитесь. Судно никого ждать не будет.");
			link.l1.go = "exit";
			NextDiag.TempNode = "PiratesOnUninhabited_43_again";
		break;
		
		case "PiratesOnUninhabited_44":
			sTitle = GenerateRandomNameToShip(PIRATE);
			PChar.GenQuest.PiratesOnUninhabited.StartShipName = sTitle;
			
			dialog.text = "А это можно легко устроить. Он ходит на " + GetStrSmallRegister(XI_ConvertString(ShipsTypes[sti(PChar.GenQuest.PiratesOnUninhabited.StartShipType)].Name + "Dat")) + " '" + sTitle + "' и промышляет работорговлей... Давай так: если его найдём - трюм тебе, а корабль мне. Заодно и порасспросишь, знает ли он " + ChangeNameCase(NAMETYPE_NICK, PChar.GenQuest.PiratesOnUninhabited.MainPirateName, NAME_ACC) + ". Только гляди, чтоб он в штаны не наложил, когда это имя услышит, ведь он ходит на моём корабле...";
			link.l1 = "Ну хорошо, считайте, что мы договорились.";
			link.l1.go = "PiratesOnUninhabited_45";
		break;
		
		case "PiratesOnUninhabited_45":
			for(i = 0; i < sti(PChar.GenQuest.PiratesOnUninhabited.PiratesQty); i++)
			{
				rChar = CharacterFromID("PirateOnUninhabited_" + i);
				LAi_SetWarriorTypeNoGroup(rChar);
				rChar.Dialog.currentnode = "PiratesOnUninhabited_11_Again";
				rChar.location = "none"; // Убираем из локации при выходе   исправлено с NPChar на rChar - лесник
				rChar.location.locator = ""; // лесник  - так же исправлено .  тогда бага не будет.
			}
			
			Log_Info("Ваша команда пополнилась на " + PChar.GenQuest.PiratesOnUninhabited.PiratesCount + " человек.");
			
			ChangeCharacterComplexReputation(pchar,"nobility", 3.0);
			
			AddCharacterCrew(PChar, sti(PChar.GenQuest.PiratesOnUninhabited.PiratesCount) - 1)
			AddPassenger(PChar, NPChar, false); // Главного в пассажиры
			SetCharacterRemovable(NPChar, false);
			//NPChar.FaceId = 101; // лесник потом подобрать аву бандиту.   
			
			PChar.Quest.PiratesOnUninhabited_LocExit.over = "yes"; // Снимаем прерывание на выход из локации
			
			sTemp = XI_ConvertString(PChar.location + "Dat");
			
			sTitle = "PiratesOnUninhabited" + PChar.location;
			ReOpenQuestHeader(sTitle);
			AddQuestRecordEx(sTitle, "PiratesOnUninhabited", "13");
			AddQuestUserDataForTitle(sTitle, "shoreName", sTemp);
			AddQuestUserData(sTitle, "shoreName", sTemp);
			AddQuestUserData(sTitle, "count", PChar.GenQuest.PiratesOnUninhabited.PiratesCount);
			AddQuestUserData(sTitle, "badCapName", ChangeNameCase(NAMETYPE_ORIG, PChar.GenQuest.PiratesOnUninhabited.BadPirateName, NAME_ABL));
			AddQuestUserData(sTitle, "ship", GetStrSmallRegister(XI_ConvertString(ShipsTypes[sti(PChar.GenQuest.PiratesOnUninhabited.StartShipType)].name + "Dat")) + " '" + PChar.GenQuest.PiratesOnUninhabited.StartShipName + "'");
			
			PChar.GenQuest.PiratesOnUninhabited.StartShore = PChar.location;
			
			PiratesOnUninhabited_SetCapToMap(); // Ставим корабль на карту
			
			DialogExit();
		break;
		
		// Диалог с кэпом в каюте
		case "PiratesOnUninhabited_46":
			dialog.text = "Какого чёрта тебе нужно?";
			link.l1 = "Я приш"+ GetSexPhrase("ел","ла") +" передать тебе привет от " + ChangeNameCase(NAMETYPE_NICK, PChar.GenQuest.PiratesOnUninhabited.MainPirateName, NAME_GEN) + ". Знаешь такого?";
			link.l1.go = "PiratesOnUninhabited_47";
			
			PChar.Quest.PiratesOnUninhabited_ShipSink.over = "yes";
			PChar.GenQuest.PiratesOnUninhabited.ClearShip = true;
			Map_ReleaseQuestEncounter("PiratesOnUninhabited_BadPirate"); // Убираем с глобалки
		break;
		
		case "PiratesOnUninhabited_47":
			dialog.text = "Жаль я не удавил эту каналью раньше... Значит пришло время расплачиваться за своё благодушие...";
			link.l1 = "Угу... И это время уже истекло...";
			link.l1.go = "PiratesOnUninhabited_48";
		break;
		
		case "PiratesOnUninhabited_48":
			LAi_CharacterDisableDialog(NPChar);
			LAi_Group_Attack(NPChar, Pchar);
			
			LAi_SetCurHPMax(NPChar);
			QuestAboardCabinDialogFree(); // важный метод
			
			LAi_Group_SetRelation(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_Group_FightGroups(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, true);
			LAi_Group_SetCheckFunction(LAI_GROUP_BRDENEMY, "PiratesOnUninhabited_CapDeath");
			
			AddDialogExitQuest("MainHeroFightModeOn");
			
			DialogExit();
		break;
		
		case "PiratesOnUninhabited_49":
			dialog.text = "Отличная работа, капитан! Всё, как и договаривались: корабль нам, трюм вам.";
			link.l1 = "Да, по рукам. Забирайте и владейте.";
			link.l1.go = "PiratesOnUninhabited_50";
		break;
		
		case "PiratesOnUninhabited_50":
			NPChar.LifeDay = 0;
			NPChar.location = "none"; // Убираем из каюты
			NPChar.location.locator = "";
			
			RemovePassenger(PChar, NPChar);
			RemoveCharacterCrew(PChar, sti(PChar.GenQuest.PiratesOnUninhabited.PiratesCount) - 1);
			
			sTitle = "PiratesOnUninhabited" + PChar.GenQuest.PiratesOnUninhabited.StartShore;
			AddQuestRecordEx(sTitle, "PiratesOnUninhabited", "14");
			AddQuestUserData(sTitle, "ship", GetStrSmallRegister(XI_ConvertString(ShipsTypes[sti(PChar.GenQuest.PiratesOnUninhabited.StartShipType)].name)) + " '" + PChar.GenQuest.PiratesOnUninhabited.StartShipName + "'");
			CloseQuestHeader(sTitle);
			
			DeleteAttribute(PChar, "GenQuest.PiratesOnUninhabited");
			
			ChangeAttributesFromCharacter(CharacterFromID("PiratesOnUninhabited_BadPirate"), NPChar, true);
			DialogExit();
			
		break;
		
		// На палубе, когда корабль с нашим пиратом отпустили
		case "PiratesOnUninhabited_50_Deck1":
			dialog.text = "Приветствую вас, капитан " + PChar.name + ".";
			link.l1 = "Ну, как тебе твой корабль?";
			link.l1.go = "PiratesOnUninhabited_50_Deck2";
		break;
		
		case "PiratesOnUninhabited_50_Deck2":
			dialog.text = "Хе-х, он стал таким же скрипучим, как и я. Видать, уже недолго нам обоим бороздить эти моря...";
			link.l1 = "Ну счастливо...";
			link.l1.go = "exit";
			NextDiag.TempNode = "PiratesOnUninhabited_50_Deck1";
		break;
		
		// В бухте, вариант, когда корабль, который нужно было захватить, утопили
		case "PiratesOnUninhabited_51":
			dialog.text = "Ты зачем мой корабль утопил"+ GetSexPhrase("","а") +"?! Мы о чём договаривались?";
			link.l1 = "Было бы лучше, если бы он утопил меня? Видишь, сам"+ GetSexPhrase("","а") +" еле корму унес"+ GetSexPhrase("","ла") +"?";
			link.l1.go = "PiratesOnUninhabited_52";
		break;
		
		case "PiratesOnUninhabited_52":
			if(dRand(1) == 1)
			{
				dialog.text = "Кто так воюет? Такой кораблик погубил"+ GetSexPhrase("","а") +"! И как только мама тебя одн"+ GetSexPhrase("ого","у") +" погулять выпустила?";
				link.l1 = "Придётся подрезать тебе язык.";
				link.l1.go = "PiratesOnUninhabited_53";
			}
			else
			{
				iMoney = sti(ShipsTypes[sti(PChar.GenQuest.PiratesOnUninhabited.StartShipType)].Price);
				iMoney = MakeInt((iMoney / 1.2 + dRand(iMoney - (iMoney / 1.2))) * 1.2);
				dialog.text = "Кто так воюет? Такой кораблик погубил"+ GetSexPhrase("","а") +"! Ты знаешь во сколько он мне обошёлся? Я за него целых " + FindRussianMoneyString(iMoney) + " отдал! Так что с тебя должок...";
				link.l1 = "А не жирно ли будет? Не забывай, что одну услугу я тебе уже оказал"+ GetSexPhrase("","а") +".";
				link.l1.go = "PiratesOnUninhabited_54";
				
				if(sti(PChar.money) >= iMoney)
				{
					link.l2 = "Чёрт бы тебя побрал с твоим кораблём вместе! Держи свои деньги и не попадайся мне больше на глаза!..";
					link.l2.go = "PiratesOnUninhabited_55";
				}
			}
		break;
		
		case "PiratesOnUninhabited_53":
			for(i = 0; i < sti(PChar.GenQuest.PiratesOnUninhabited.PiratesQty); i++)
			{
				rChar = CharacterFromID("PirateOnUninhabited_" + i);
				LAi_SetImmortal(rChar, false);
				rChar.LifeDay = 0;
			}
			
			LAi_Group_SetRelation("PiratesOnUninhabitedGroup", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_Group_FightGroups("PiratesOnUninhabitedGroup", LAI_GROUP_PLAYER, true);
			
			sTitle = "PiratesOnUninhabited" + PChar.GenQuest.PiratesOnUninhabited.StartShore;
			AddQuestRecordEx(sTitle, "PiratesOnUninhabited", "15");
			AddQuestUserData(sTitle, "ship", GetStrSmallRegister(XI_ConvertString(ShipsTypes[sti(PChar.GenQuest.PiratesOnUninhabited.StartShipType)].name)) + " '" + PChar.GenQuest.PiratesOnUninhabited.StartShipName + "'");
			CloseQuestHeader(sTitle);
			
			DeleteAttribute(PChar, "GenQuest.PiratesOnUninhabited");
			
			AddDialogExitQuest("MainHeroFightModeOn");
			
			DialogExit();
		break;
		
		case "PiratesOnUninhabited_54":
			dialog.text = "Что мне твоя услуга?! если капитан " + ChangeNameCase(NAMETYPE_ORIG, PChar.GenQuest.PiratesOnUninhabited.BadPirateName, NAME_NOM) + " уже на дне вместе с моей лоханкой! Ни долю с него получить не могу, ни корабль отобрать!.. Мне теперь только и осталось - сдохнуть под забором, как нищему бродяге!!!";
			link.l1 = "Зачем же под забором? Я могу тебе пышные похороны организовать. Прямо здесь, если не возражаешь...";
			link.l1.go = "PiratesOnUninhabited_53";
		break;
		
		case "PiratesOnUninhabited_55":
			for(i = 0; i < sti(PChar.GenQuest.PiratesOnUninhabited.PiratesQty); i++)
			{
				rChar = CharacterFromID("PirateOnUninhabited_" + i);
				LAi_SetWarriorTypeNoGroup(rChar);
				LAi_SetImmortal(rChar, false);
				LAi_CharacterDisableDialog(rChar);
				rChar.LifeDay = 0;
			}
			
			sTitle = "PiratesOnUninhabited" + PChar.GenQuest.PiratesOnUninhabited.StartShore;
			AddQuestRecordEx(sTitle, "PiratesOnUninhabited", "16");
			AddQuestUserData(sTitle, "sSex", GetSexPhrase("","а"));
			AddQuestUserData(sTitle, "ship", GetStrSmallRegister(XI_ConvertString(ShipsTypes[sti(PChar.GenQuest.PiratesOnUninhabited.StartShipType)].name)) + " '" + PChar.GenQuest.PiratesOnUninhabited.StartShipName + "'");
			CloseQuestHeader(sTitle);
			
			DeleteAttribute(PChar, "GenQuest.PiratesOnUninhabited");
			
			DialogExit();
		break;
		
		// КОНЕЦ
		
		// Warship, 15.05.11. Генер "Правосудие на продажу".
		case "JusticeOnSale_1":
			dialog.text = "Я думаю, мы могли бы, ну... договориться? Если вы окажете нам одну услугу, мы уж в долгу не останемся, хе-хе.";
			link.l1 = "Услугу? А в чем суть дела, и что вы предлагаете взамен?";
			link.l1.go = "JusticeOnSale_3";
		break;
		
		case "JusticeOnSale_2":
			LAi_Group_SetRelation("JusticeOnSaleGroup_" + LoadedLocation.index, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_Group_FightGroups("JusticeOnSaleGroup_" + LoadedLocation.index, LAI_GROUP_PLAYER, true);
			
			DialogExit();
			LAi_SetFightMode(PChar, true);
		break;
		
		case "JusticeOnSale_3":
			dialog.text = "Наш капитан " + PChar.GenQuest.JusticeOnSale.SmugglerName + " попался патрулю из города " + XI_ConvertString("Colony" + PChar.GenQuest.JusticeOnSale.CityId) + ", его бросили за решетку, но улик на него, чтобы к вдове тощей приставить, у них нет. Вытащить его самим нам не по силам\n" +
				"А вы человек уважаемый, вас в городе знают. Может, вы сможете договориться, внести залог, или просто выкупить его? Поверьте, мы сразу же уйдем, и никогда больше не вернемся на этот остров – ваша репутация ничуть не пострадает!";
			link.l1 = "Положим, я смогу его вызволить. Но я не услышал ни слова о моей оплате!";
			link.l1.go = "JusticeOnSale_4";
			link.l2 = "Убирайся к дьяволу, воровское отродье! Я не собираюсь иметь с тобой дело!";
			link.l2.go = "JusticeOnSale_5";
		break;
		
		case "JusticeOnSale_4":
			dialog.text = "Несколько индейских побрякушек и талисманов вас устроят? Они довольно редки... Или предпочитаете звонкую монету? В количестве этак нескольких тысяч песо?";
			link.l1 = "Убирайся к дьяволу, воровское отродье! Я не собираюсь иметь с тобой дело!";
			link.l1.go = "JusticeOnSale_5";
			link.l2 = "Меня интересуют индейские штучки. Думаю, я соглашусь.";
			link.l2.go = "JusticeOnSale_6";
			link.l3 = "Звонкая монета – радость моряка. Деньги, как известно, не пахнут – я согласен.";
			link.l3.go = "JusticeOnSale_7";
		break;
		
		case "JusticeOnSale_5":
			for(i = 0; i < sti(PChar.GenQuest.JusticeOnSale.EncQty); i++)
			{
				rChar = CharacterFromID("JusticeOnSale_Jungle_" + i);
				LAi_CharacterDisableDialog(rChar);
			}
			DialogExit();
		break;
		
		case "JusticeOnSale_6":
			PChar.GenQuest.JusticeOnSale.ShipName = GenerateRandomNameToShip(PIRATE);
			PChar.GenQuest.JusticeOnSale.ShipType = PiratesOnUninhabited_GenerateShipType();
			PChar.GenQuest.JusticeOnSale.RewardType = 0; // Подрякушки.
			dialog.text = "Благодарю вас, кэп. Мы возместим вам сумму залога, сверх вашей премии. Думаю, вам стоит поговорить с комендантом о нашем капитане, может, вам удастся его убедить. А когда вызволите его, приходите " + XI_ConvertString(PChar.GenQuest.JusticeOnSale.ShoreId + "Acc") + ", там отдал якорь наш корабль - " + LowerFirst(XI_ConvertString(ShipsTypes[sti(PChar.GenQuest.JusticeOnSale.ShipType)].name)) + " '" + PChar.GenQuest.JusticeOnSale.ShipName + "'. Будем ждать вас на берегу.";
			link.l1 = "...";
			link.l1.go = "JusticeOnSale_8";
		break;
		
		case "JusticeOnSale_7":
			PChar.GenQuest.JusticeOnSale.ShipName = GenerateRandomNameToShip(PIRATE);
			PChar.GenQuest.JusticeOnSale.ShipType = PiratesOnUninhabited_GenerateShipType();
			PChar.GenQuest.JusticeOnSale.RewardType = 1; // Монеты.
			
			dialog.text = "Благодарю вас, кэп. Мы возместим вам сумму залога, сверх вашей премии. Думаю, вам стоит поговорить с комендантом форта о нашем капитане, может вам удастся его убедить. А когда вызволите его, приходите " + XI_ConvertString(PChar.GenQuest.JusticeOnSale.ShoreId + "Acc") + ", там отдал якорь наш корабль - " + LowerFirst(XI_ConvertString(ShipsTypes[sti(PChar.GenQuest.JusticeOnSale.ShipType)].name)) + " '" + PChar.GenQuest.JusticeOnSale.ShipName + "'. Будем ждать вас на берегу.";
			link.l1 = "...";
			link.l1.go = "JusticeOnSale_8";
		break;
		
		case "JusticeOnSale_8":
			for(i = 0; i < sti(PChar.GenQuest.JusticeOnSale.EncQty); i++)
			{
				rChar = CharacterFromID("JusticeOnSale_Jungle_" + i);
				LAi_CharacterDisableDialog(rChar);
			}
			ReOpenQuestHeader("JusticeOnSale");
			AddQuestRecord("JusticeOnSale", "1");
			AddQuestUserData("JusticeOnSale", "cityName", XI_ConvertString("Colony" + PChar.GenQuest.JusticeOnSale.CityId));
			PChar.GenQuest.JusticeOnSale.MayorWait = true;
			PChar.GenQuest.JusticeOnSale.PrisonWait = true;
			
			DialogExit();
		break;
		
		case "JusticeOnSale_9":
			if(dRand(1) == 0)
			{
				if(sti(PChar.GenQuest.JusticeOnSale.RewardType) == 0)
				{
					// Награда побрякушками.
					dialog.text = "Вот мы и на месте, капитан! А вы отлично провели этих толстопузых чинушей! Вот ваша награда, ребята, давайте побрякушки!";
				}
				else
				{
					// Награда золотом.
					dialog.text = "Вот мы и на месте, капитан! А вы отлично провели этих толстопузых чинушей! Вот ваша награда, тащи сундук ребята!";
				}
				
				link.l1 = "Давайте сюда, что мне причитается, и проваливайте!";
				link.l1.go = "JusticeOnSale_10";
			}
			else
			{
				// Массакра.
				dialog.text = "Ну, вот мы и на месте капитан! Вижу, вам удалось отлично все устроить... Но вот беда – свидетели-то нам совсем не кстати... А ну-ка, парни, скажем капитану спасибо!";
				link.l1 = RandSwear() + "Надо было сразу тебя пристрелить!";
				link.l1.go = "JusticeOnSale_11";
			}
			chrDisableReloadToLocation = false;
		break;
		
		case "JusticeOnSale_10":
			DialogExit();
			if(sti(PChar.GenQuest.JusticeOnSale.RewardType) == 0)
			{
				if(CheckAttribute(PChar, "GenQuest.JusticeOnSale.PrisonMoney"))
				{
					AddItems(PChar, "indian_"+(1+dRand(10)), 1);
				}
				else
				{
					AddItems(PChar, "obereg_"+(1+dRand(10)), 1);
				}
			}
			else
			{
				if(CheckAttribute(PChar, "GenQuest.JusticeOnSale.PrisonMoney"))
				{
					AddMoneyToCharacter(PChar, sti(PChar.rank) * 700 + dRand(2000));
				}
				else
				{
					AddMoneyToCharacter(PChar, sti(PChar.rank) * 500 + dRand(1000));
				}
			}
			for(i = 0; i < sti(PChar.GenQuest.JusticeOnSale.EncQty); i++)
			{
				rChar = CharacterFromID("JusticeOnSale_ShorePirate_" + i);
				LAi_Type_Actor_Reset(rChar);
				LAi_ActorGoToLocation(rChar, "reload", LAi_FindNearestFreeLocator2Pchar("reload"), "none", "", "", "", 3.0);
			}
			AddQuestRecord("JusticeOnSale", "3");
			CloseQuestHeader("JusticeOnSale");
		break;
		
		case "JusticeOnSale_11":
			AddQuestRecord("JusticeOnSale", "4");
			CloseQuestHeader("JusticeOnSale");
			for(i = 0; i < sti(PChar.GenQuest.JusticeOnSale.EncQty); i++)
			{
				rChar = CharacterFromID("JusticeOnSale_ShorePirate_" + i);
				LAi_SetWarriorTypeNoGroup(rChar);
				LAi_Group_MoveCharacter(rChar, "JusticeOnSale_ShoreGroup");
			}
			
			LAi_Group_SetRelation("JusticeOnSale_ShoreGroup", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			AddDialogExitQuest("MainHeroFightModeOn");
			DialogExit();
		break;
			//замечание по обнаженному оружию от персонажей типа citizen // лесник вставил в ген.квесты чтобы не было пустого диалога .
		case "CitizenNotBlade":
			dialog.text = NPCharSexPhrase(NPChar, "Не искушай судьбу, приятель! Убери свою саблю!", "Знаете, я, как гражданка этого города, прошу вас не ходить у нас с обнажённым клинком.");
			link.l1 = LinkRandPhrase("Хорошо.", "Ладно.", "Как скажешь...");
			link.l1.go = "exit";
		break;																																																				  
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			break;
	}
}

void ChurchGenQuest2_GiveCup()
{
	AddItems(PChar, "Bible", 1);
	ref rItem = ItemsFromID("Bible");
	rItem.Name = "itmname_ChurchGenQuest2Cup"; // rItem.Name = "itmname_bible";
	rItem.City = XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_2.QuestTown + "Gen");
	rItem.Weight = 15.0; // rItem.Weight = 2;
	rItem.picIndex = 13; // itm.picIndex = 6;
	rItem.picTexture = "ITEMS_31"; // itm.picTexture = "ITEMS_9";
	ChangeItemDescribe("Bible", "itmdescr_ChurchGenQuest2Cup");
}

// Для генера "Пираты на необитаемом острове"
String PiratesOnUninhabited_GetStringNum(int _num)
{
	String retValue = "";
	
	switch(_num)
	{
		case 5: retValue = "пятерым"; break;
		case 6: retValue = "шестерым"; break;
		case 7: retValue = "семерым"; break;
		case 8: retValue = "восьмерым"; break;
		case 9: retValue = "девятерым"; break;
		case 10: retValue = "десятерым"; break;
	}
	
	return retValue;
}

int PiratesOnUninhabited_GenerateShipType()
{
	int rank = sti(PChar.rank);
	int retShipType;
	
	if(rank < 5)
	{
		switch(dRand(1))
		{
			case 0: retShipType = SHIP_LUGGER; break;
			case 1: retShipType = SHIP_SLOOP; break;
		}
	}
	
	if(rank >= 5 && rank < 20)
	{
		switch(dRand(3))
		{
			case 0: retShipType = SHIP_SLOOP; break;
			case 1: retShipType = SHIP_BRIGANTINE; break;
			case 2: retShipType = SHIP_SCHOONER_W; break;
			case 3: retShipType = SHIP_BRIG; break;
		}
	}
	
	if(rank >= 20)
	{
		switch(dRand(2))
		{
			case 0: retShipType = SHIP_CORVETTE; break;
			case 1: retShipType = SHIP_GALEON_H; break;
			case 2: retShipType = SHIP_FRIGATE; break;
		}
	}
	
	return retShipType;
}

String PiratesOnUninhabited_GenerateTreasureShore(ref _boxId)
{
	String retShoreId;
	
	switch(dRand(4))
	{
		case 0:
			retShoreId = "Shore9";
			_boxId = "box1";
		break;
		
		case 1:
			retShoreId = "Shore55";
			_boxId = "box" + (1 + rand(1)); // Сундук пусть рандомится и при с/л
		break;
	
		case 2:
			retShoreId = "Shore_ship1";
			_boxId = "box" + (1 + rand(1)); // Сундук пусть рандомится и при с/л
		break;
		
		case 3:
			retShoreId = "Shore_ship2";
			_boxId = "box" + (1 + rand(1)); // Сундук пусть рандомится и при с/л
		break;
		
		case 4:
			retShoreId = "Shore_ship3";
			_boxId = "box" + (1 + rand(1)); // Сундук пусть рандомится и при с/л
		break;
	}
	
	return retShoreId;
}

void PiratesOnUninhabited_SetCapToMap()
{
	int temp;
	String group = "PiratesOnUninhabited_SeaGroup";
	ref character = GetCharacter(NPC_GenerateCharacter("PiratesOnUninhabited_BadPirate", "", "man", "man", sti(pchar.rank) + 5, PIRATE, -1, true, "soldier"));		
	character.Ship.Type = GenerateShipExt(sti(PChar.GenQuest.PiratesOnUninhabited.StartShipType), true, character);
	character.Ship.Name = PChar.GenQuest.PiratesOnUninhabited.StartShipName;
    SetBaseShipData(character);
    SetCrewQuantityFull(character);
    Fantom_SetCannons(character, "pirate");
    Fantom_SetBalls(character, "pirate");
	Fantom_SetUpgrade(character, "pirate");
	
	character.Ship.Mode = "pirate";	
	SetCaptanModelByEncType(character, "pirate");

	DeleteAttribute(character, "SinkTenPercent");
	DeleteAttribute(character, "SaveItemsForDead");
	DeleteAttribute(character, "DontClearDead");
	DeleteAttribute(character, "AboardToFinalDeck");
	DeleteAttribute(character, "SinkTenPercent");
	
	character.AlwaysSandbankManeuver = true;
	character.AnalizeShips = true;  //анализировать вражеские корабли при выборе таска
	character.DontRansackCaptain = true; //не сдаваться
	
	SelAllPerksToChar(character, false);
	
	Group_FindOrCreateGroup(group);
	Group_SetTaskAttackInMap(group, PLAYER_GROUP);
	Group_LockTask(group);
	Group_AddCharacter(group, character.id);
	Group_SetGroupCommander(group, character.id);
	SetRandGeraldSail(character, PIRATE);
	
	character.fromCity = SelectAnyColony(""); // Колония, из бухты которой выйдет
	character.fromShore = GetIslandRandomShoreId(GetArealByCityName(character.fromCity));
	character.toCity = SelectAnyColony(character.fromCity); // Колония, в бухту которой придет
	character.toShore = GetIslandRandomShoreId(GetArealByCityName(character.toCity));
	
	character.mapEnc.type = "trade";
	character.mapEnc.worldMapShip = "quest_ship";
	character.mapEnc.Name = LowerFirst(XI_ConvertString(ShipsTypes[sti(PChar.GenQuest.PiratesOnUninhabited.StartShipType)].name)) + " '" + PChar.GenQuest.PiratesOnUninhabited.StartShipName + "'";
	
	Map_CreateTrader(character.fromShore, character.toShore, "PiratesOnUninhabited_BadPirate", GetMaxDaysFromIsland2Island(GetArealByCityName(character.toCity), GetArealByCityName(character.fromCity)) + 3);
	
	temp = GetCharacterFreeSpace(character, GOOD_SLAVES); // Сколько влезет рабов
	AddCharacterGoodsSimple(character, GOOD_SLAVES, makeint(temp / 2 + dRand(temp / 2)) - 1);
	
	PChar.Quest.PiratesOnUninhabited_ShipSink.win_condition.l1 = "Character_sink";
	PChar.Quest.PiratesOnUninhabited_ShipSink.win_condition.l1.character = "PiratesOnUninhabited_BadPirate";
	PChar.Quest.PiratesOnUninhabited_ShipSink.function = "PiratesOnUninhabited_ShipSink";
	
	Log_TestInfo("Пираты на необитайке: кэп вышел из " + character.fromCity + " и направился в: " + character.toShore);
}
