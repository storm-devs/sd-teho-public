void ProcessDialogEvent()
{
	ref sld, NPChar;
	aref Link, NextDiag;
	string sTemp;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "Явный баг. Сообщите Jason'у, как и при каких обстоятельствах его получили.";
			link.l1 = "Обязательно сообщу!";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
		case "FalseTrace":
			dialog.text = "Добрый день, капитан... кхм... кха! Треклятые рудники... Разрешите представиться - Адам Рейнер. Я человек простой, и не люблю пышных предисловий, так что перейду сразу к сути дела. Вы хотите неплохо заработать? Предлагаю вам небольшое дельце, в котором ни я без вас, ни вы без меня обойтись не сможем.";
			link.l1 = "Хех! Неплохо заработать? Очень интересно. Я готов вас выслушать, Адам.";
			link.l1.go = "FalseTrace_1";
			link.l2 = "Знаете что, уважаемый, вы конечно извините, но вы мне не внушаете доверия. Так что никаких дел я с вами вести не буду.";
			link.l2.go = "FalseTrace_exit";
		break;
		
		case "FalseTrace_exit":
			dialog.text = "Доверия? Ха-ха! Судить о человеке по его физиономии - неблагодарное дело, капитан. Впрочем, черт с вами. Вы упустили прекрасную возможность легко и быстро заработать. Я легко найду другого, более сговорчивого...";
			link.l1 = "Все, разговор окончен, сударь. Всего доброго!";
			link.l1.go = "FalseTrace_exit_1";
		break;
		
		case "FalseTrace_exit_1":
			DialogExit();
			LAi_ActorRunToLocation(npchar, "reload", "reload4_back", "none", "", "", "", -1);
			npchar.lifeday = 0;
			DeleteAttribute(pchar, "questTemp.FalseTrace");
			chrDisableReloadToLocation = false;
			bDisableFastReload = false;
		break;
		
		case "FalseTrace_1":
			//выбираем целевой пункт
			switch (drand(2))
			{
				case 0: 
					pchar.questTemp.FalseTrace.DayQty = 18;
					pchar.questTemp.FalseTrace.TargetCity = "Beliz";
					pchar.questTemp.FalseTrace.TargetShore = "Shore8";
				break;
				case 1: 
					pchar.questTemp.FalseTrace.DayQty = 22;
					pchar.questTemp.FalseTrace.TargetCity = "Marigo";
					pchar.questTemp.FalseTrace.TargetShore = "Shore41";
				break;
				case 2: 
					pchar.questTemp.FalseTrace.DayQty = 20;
					pchar.questTemp.FalseTrace.TargetCity = "Santodomingo";
					pchar.questTemp.FalseTrace.TargetShore = "Mayak8";
				break;
			}
			pchar.questTemp.FalseTrace.ShipName = GenerateRandomNameToShip(sti(npchar.nation));
			pchar.questTemp.FalseTrace.Mation = sti(npchar.nation);
			dialog.text = "Кха! Приятно иметь дело с быстро мыслящим человеком, капитан... Суть дела такова: буквально на днях из одного порта должен выйти галеон с приличным грузом серебра. Корабль пойдет один, без охранения - такая вот глупость, хе-хе\nЗахватить его - плевое дело. Я сообщаю вам, откуда и куда идет корабль, вы его захватываете, я получаю свою долю. Всё просто.";
			link.l1 = "И вы, конечно, хотите получить её наличными прямо сейчас?";
			link.l1.go = "FalseTrace_2";
		break;
		
		case "FalseTrace_2":
			dialog.text = "Я что, похож на мелкого жулика, кэп? Нет. Я поднимусь на борт вашей посудины и мы вместе пойдем искать добычу. Отсиживаться во время боя в трюме я не стану - я прошу назначить меня в абордажную команду офицером, временно, конечно\nУмений владеть саблей и пистолем мне не занимать. Так что разделю с вами все опасности пути... кхе... кха! А после того, как захватим галеон, вы выдадите мне мою долю серебром.";
			link.l1 = "И на какую часть добычи вы претендуете?";
			link.l1.go = "FalseTrace_3";
		break;
		
		case "FalseTrace_3":
			dialog.text = "Я не жадный, кэп. Моя доля составит столько, сколько влезет в трюм моего старого баркаса, это примерно 200 мер серебра. По моим сведениям, на галеоне будет не меньше двух тысяч мер серебра, так что мне достанется десятая часть. Согласитесь, это справедливо.";
			link.l1 = "Десятую часть добычи за простую информацию? Да я в таверне у местной пьяни за кружку рома такие сведения покупаю. Нет, уважаемый, нам с вами не по пути!";
			link.l1.go = "FalseTrace_4";
			link.l2 = "Хм. Пожалуй, соглашусь. Я принимаю ваше предложение, Адам. Добро пожаловать на борт. Теперь информация: откуда, куда, сроки, название корабля?";
			link.l2.go = "FalseTrace_5";
		break;
		
		case "FalseTrace_4":
			dialog.text = "Ну и скряга же вы, капитан! Ну, раз не хотите - так вообще ничего не получите. Прощайте!";
			link.l1 = "Счастливого пути! Поищите другого простака для своей авантюры!";
			link.l1.go = "FalseTrace_exit_1";
		break;
		
		case "FalseTrace_5":
			dialog.text = "Галеон называется '"+pchar.questTemp.FalseTrace.ShipName+"', выходит из Картахены и направляется в колонию "+XI_ConvertString("Colony"+pchar.questTemp.FalseTrace.TargetCity)+". Времени у нас немного, не больше двух-трех недель. Если не отыщем за эти дни - значит, прозевали.";
			link.l1 = "Тогда не будем терять ни минуты! В путь!";
			link.l1.go = "FalseTrace_6";
		break;
		
		case "FalseTrace_6":
			DialogExit();
			NextDiag.CurrentNode = "FalseTrace_officer";
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "", -1);
			AddPassenger(pchar, npchar, false);
			//LAi_ActorFollowEverywhere(npchar, "", -1);
			chrDisableReloadToLocation = false;
			bDisableFastReload = false;
			AddQuestRecord("FalseTrace", "1");
			AddQuestUserData("FalseTrace", "sCity1", XI_ConvertString("Colony"+pchar.questTemp.FalseTrace.StartCity+"Gen"));
			AddQuestUserData("FalseTrace", "sCity2", XI_ConvertString("Colony"+pchar.questTemp.FalseTrace.TargetCity));
			AddQuestUserData("FalseTrace", "sShip", pchar.questTemp.FalseTrace.ShipName);
			//установим таймер на генерацию энкаунтера
			pchar.quest.False_Trace_2.win_condition.l1 = "Timer";
			pchar.quest.False_Trace_2.win_condition.l1.date.hour  = sti(GetTime());
			pchar.quest.False_Trace_2.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 2);
			pchar.quest.False_Trace_2.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 2);
			pchar.quest.False_Trace_2.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 2);
			pchar.quest.False_Trace_2.function = "CreateFalseTraceGaleonOnMap";
			SetFunctionTimerCondition("FalseTraceGaleonOver", 0, 0, sti(pchar.questTemp.FalseTrace.DayQty)+2, false);//таймер
		break;
		
		case "FalseTrace_officer":
			dialog.text = "Вы что-то хотели, кэп?";
			link.l1 = "Да нет, ничего.";
			link.l1.go = "exit";
			NextDiag.TempNode = "FalseTrace_officer";
		break;
		
		case "FalseTrace_7":
			chrDisableReloadToLocation = true;
			dialog.text = "Вы меня хотели видеть, кэп?";
			link.l1 = "Думаю, для тебя это не было неожиданностью... Где серебро, черт возьми?! Где серебро?! Я тебя спрашиваю! Капитан галеона заявил, что это просто фуражное военное судно! Ты обманул меня!";
			link.l1.go = "FalseTrace_8";
		break;
		
		case "FalseTrace_8":
			dialog.text = "Капитан, прошу вас, успокойтесь. Я вам сейчас постараюсь все объяснить.";
			link.l1 = "Да, да! Я уже спокоен! Ты до сих пор не болтаешься на нок-рее лишь потому, что я не могу понять мотивов твоего странного поступка - ты сам отправился за мной на охоту за этим галеоном, зная, что у него в трюмах нет никакого серебра. Так что уж изволь объясниться.";
			link.l1.go = "FalseTrace_9";
		break;
		
		case "FalseTrace_9":
			dialog.text = "Я именно это и хочу сделать, кэп. Да, я действительно обманул вас. Но в противном случае я бы никогда не смог убедить вас сделать то, что мне нужно, а именно - захватить... кхе... кха! Захватить этот треклятый галеон\nНо обещаю, что в долгу я не останусь, и сполна расплачусь за вашу помощь. Теперь к сути вопроса - зачем мне это было нужно. Вы нашли на галеоне женщину? Я видел, как ваши матросы отводили ее на ваше судно...";
			link.l1 = "Хм... Так тебе что, нужна была эта девка? И ты за этим заставил меня устроить морское сражение и перебить кучу народа?!";
			link.l1.go = "FalseTrace_10";
		break;
		
		case "FalseTrace_10":
			dialog.text = "Это моя жена. Катерина Рейнер. Она сбежала от меня три месяца назад с этим капитанишкой. Я приложил все усилия, чтобы разыскать их, и нашел. Они отправлялись вдвоем в "+XI_ConvertString("Colony"+pchar.questTemp.FalseTrace.TargetCity)+". Более удобного случая одновременно и вернуть Катерину, и расквитаться с подлым похитителем чужих жен трудно было и представить\nЕсли бы я сказал вам правду, вы бы плюнули мне в глаза, развернулись и ушли - какое вам дело до моих семейных проблем? А представив галеон в виде богатой добычи, у меня был шанс, что вы согласитесь.";
			link.l1 = "Хех! Значит, жена сбежала от вас? Очень интересно...";
			link.l1.go = "FalseTrace_11";
		break;
		
		case "FalseTrace_11":
			dialog.text = "Это моя законная жена, и я люблю ее, и никто, кроме меня, не имеет права быть с ней! Этот прохвост навешал ей лапши на уши, напел красивых сказок про романтику и прочее, пока я был на дел... в отъезде. А вы разве не знаете этих женщин? Поверила ему, глупышка, и сбежала с ним в море.";
			link.l1 = "Ладно, оставим это. Мне действительно нет никакого дела до вашей семейной жизни, разбирайтесь со своей женой сами. Но вы говорили мне там что-то о компенсации моих убытков? Мне ничего не послышалось?";
			link.l1.go = "FalseTrace_12";
		break;
		
		case "FalseTrace_12":
			if (pchar.basenation == SPAIN || pchar.basenation == HOLLAND)
			{
				pchar.questTemp.FalseTrace.QuestCity = "Portobello";
				pchar.questTemp.FalseTrace.QuestShore = "Shore48";
			}
			else
			{
				pchar.questTemp.FalseTrace.QuestCity = "SantaCatalina";
				pchar.questTemp.FalseTrace.QuestShore = "Shore54";
			}
			dialog.text = "Вы не ослышались, капитан. Услуга за услугу. Денег у меня нет, но если вы отвезете меня с Катериной в "+XI_ConvertString("Colony"+pchar.questTemp.FalseTrace.QuestCity)+", я сообщу вам на этот раз совершенно достоверную информацию, где можно без малейшего труда разжиться золотишком.";
			link.l1 = "Очень интересно. А почему бы вам не выдать мне эту 'достоверную информацию' прямо сейчас?";
			link.l1.go = "FalseTrace_13";
		break;
		
		case "FalseTrace_13":
			dialog.text = "Потому что я ей еще не располагаю. Позвольте объяснить подробно. Один джентльмен удачи, по имени Косой Солли - не слыхали о таком? - за день до нашего с вами отплытия отправился с отрядом из Блювельда в глубь континента, чтобы хорошенько пощипать золотые рудники\nУ берегов Мейна его должно было встретить судно, когда он будет возвращаться с добычей, но по определенным причинам этого не произойдет, и Косой Солли будет вынужден пешком отправиться в Блювельд, или Белиз - не знаю, куда ближе, за кораблем, чтобы погрузить награбленное\nЕстественно, золото он через джунгли не потащит и спрячет в какой-нибудь бухте и поставит небольшую охрану. У него в отряде есть мой человек. Он будет ждать меня в городе "+XI_ConvertString("Colony"+pchar.questTemp.FalseTrace.QuestCity)+". Как только мы бросим якорь в порту, он и сообщит мне, в какой бухте Косой Солли спрятал награбленное добро\nВы пойдете туда, без труда вырежете его бандитов и заберете себе золото. Я сам собирался сделать это, но учитывая обстоятельства, полностью отдаю это дело вам, и даже не прошу себе ни песо.";
			link.l1 = "Что-то ваша история попахивает очередным 'галеоном с серебром'. Один раз вы меня уже обманули. Где гарантии, что вы и сейчас не лжете?";
			link.l1.go = "FalseTrace_14";
		break;
		
		case "FalseTrace_14":
			dialog.text = "Я даю вам честное слово. Больше у меня нет никаких гарантий. Но вы можете мне верить, клянусь.. кхе... кха! Треклятые рудники...";
			link.l1 = "Ладно. Ступай, я подумаю над тем, что ты мне сказал.";
			link.l1.go = "FalseTrace_15";
		break;
		
		case "FalseTrace_15":
			dialog.text = "Не затягивайте, капитан. Косой Солли в конце-концов вернется за своим добром, как вы понимаете. По моим расчетам, у вас не больше двух недель, чтобы добраться до "+XI_ConvertString("Colony"+pchar.questTemp.FalseTrace.QuestCity+"Gen")+".";
			link.l1 = "Я учту это. А теперь отправляйся в кубрик к матросам. До прибытия на место, я думаю, что вам с вашей женой лучше побыть раздельно. Всё, я тебя больше не задерживаю.";
			link.l1.go = "FalseTrace_16";
		break;
		
		case "FalseTrace_16":
			DialogExit();
			LAi_SetActorType(npchar);
			pchar.questTemp.FalseTrace = "TalkCabinWoman";
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "TalkSelf_Quest", 3.0);
			SetFunctionTimerCondition("FalseTraceSollyOver", 0, 0, 15, false);//таймер
			AddQuestRecord("FalseTrace", "5");
			AddQuestUserData("FalseTrace", "sCity", XI_ConvertString("Colony"+pchar.questTemp.FalseTrace.QuestCity));
		break;
		
		case "FalseTrace_17":
			dialog.text = "Вызывали, капитан?";
			link.l1 = "Да. Адам Рейнер, я арестую тебя и посажу под замок. Ты обманул меня, и у меня нет другого выхода, как изолировать тебя и сдать властям.";
			link.l1.go = "FalseTrace_18";
		break;
		
		case "FalseTrace_18":
			dialog.text = "Вот как? Я подозревал, что вы так сделаете, кэп. Особенно после того, как увидел, что вы пошли в трюм, беседовать с этим гнусным похитителем чужих жен. Решили встать на его сторону, так, кэп?";
			link.l1 = "Не твое дело. Ты использовал меня, подставил и пытаешься обмануть сказками про какие-то сокровища! Боцман, взять его!";
			link.l1.go = "FalseTrace_19";
		break;
		
		case "FalseTrace_19":
			dialog.text = "Кха! Не так быстро, капитан... Боцман и ваши люди еще не скоро смогут сюда войти. Вы не заметили, что я запер дверь? Теперь мы здесь вдвоем - вы и я. Покажите-ка кэп, на что вы способны!";
			link.l1 = "Ах вот как? Ну, держись, пес!";
			link.l1.go = "FalseTrace_20";
		break;
		
		case "FalseTrace_20":
			DialogExit();
			NextDiag.currentnode = "FalseTrace_21";
			chrDisableReloadToLocation = true;
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_SetCheckMinHP(npchar, 10.0, true, "FalseTrace_capture");
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
		case "FalseTrace_21":
			dialog.text = "";
			link.l1 = "Так-то лучше... Брось оружие, мерзавец! Боцман! Надеть на негодяя кандалы и бросить в трюм!";
			link.l1.go = "FalseTrace_22";
		break;
		
		case "FalseTrace_22":
			DialogExit();
			chrDisableReloadToLocation = false;
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], true);
			bQuestDisableMapEnter = false;
			RemovePassenger(Pchar, npchar);
			pchar.GenQuest.LastQuestPrisonerIdx = SetCharToPrisoner(npchar);
			SetCharacterRemovable(&characters[sti(pchar.GenQuest.LastQuestPrisonerIdx)], false);
			Pchar.questTemp.FalseTrace.PrisonerAdamIDX = sti(pchar.GenQuest.LastQuestPrisonerIdx);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", 3.0);
			LAi_SetPlayerType(pchar);
			RemoveCharacterEquip(npchar, BLADE_ITEM_TYPE);
			RemoveCharacterEquip(npchar, GUN_ITEM_TYPE);
			RemoveCharacterEquip(npchar, CIRASS_ITEM_TYPE);
			sld = &Characters[sti(Pchar.questTemp.FalseTrace.PrisonerIDX)];
			ReleasePrisoner(sld); //освободили пленника
			AddPassenger(pchar, sld, false);
			SetCharacterRemovable(sld, false);
			DeleteAttribute(sld, "LifeDay") //постоянный персонаж
			GiveItem2Character(sld, "blade_10");
			EquipCharacterbyItem(sld, "blade_10");
			GiveItem2Character(sld, "pistol1");
			EquipCharacterbyItem(sld, "pistol1");//патроны не даю - все одно для антуражу
			DeleteAttribute(pchar, "GenQuest.DontSetCabinOfficer");
			AddComplexSelfExpToScill(40, 40, 40, 40);
			AddQuestRecord("FalseTrace", "11");
			AddQuestUserData("FalseTrace", "sShore", XI_ConvertString(pchar.questTemp.FalseTrace.TargetShore+"Gen"));
			pchar.questTemp.FalseTrace = "AdamPrisoner";
		break;
		
		case "FalseTrace_23":
			pchar.quest.FalseTraceSollyOver.over = "yes"; //снять таймер
			dialog.text = "Благодарю вас, кэп, что помогли мне вернуть мою жену! Адам Рейнер у вас в долгу, и он этого не забудет, ха-ха, клянусь... кха! Треклятые рудники... Теперь о Косом Солли. Мой человек уже все сообщил мне. Солли оставил награбленное золото в гроте залива Сан-Хуан-дель-Норте под охраной своих головорезов, а сам отправился за кораблем в Блювельд\nВам следует поторопиться - у вас в запасе не больше пяти дней, по расчетам моего товарища. Возьмите с собой людей на высадку - бандиты Солли отчаянные ребята, и так просто своего не отдадут. Но проблем все равно не будет - я видел, как вы лихо управились с галеоном\nА теперь нам пора проститься. Спасибо еще раз и - удачи, кэп!";
			link.l1 = "И тебе удачи, Адам. Не обижай жену!";
			link.l1.go = "FalseTrace_Remove_exit";
			SetFunctionTimerCondition("FalseTraceBonanzaOver", 0, 0, 5, false);//таймер
			pchar.quest.False_Trace_4.win_condition.l1 = "location";
			pchar.quest.False_Trace_4.win_condition.l1.location = "Shore55";
			pchar.quest.False_Trace_4.function = "FalseTrace_SollyBonanza";
			ChangeCharacterComplexReputation(pchar, "nobility", -2);
			AddQuestRecord("FalseTrace", "14");
			AddQuestUserData("FalseTrace", "sCity", XI_ConvertString("Colony"+pchar.questTemp.FalseTrace.QuestCity));
		break;
		
		case "FalseTrace_24":
			pchar.quest.FalseTraceSollyOver.over = "yes"; //снять таймер
			dialog.text = "Кха! Капитан, какого черта мы высадились в этой бухте? Я же сказал вам - мой человек ждет меня в порту "+XI_ConvertString("Colony"+pchar.questTemp.FalseTrace.QuestCity+"Gen")+"! Или вы решили топать до города пешком через джунгли?";
			link.l1 = "Не угадал, Адам. Неужели ты думал, что я поверю твоим россказням и во второй раз? Ты меня за дурака держишь? На этот раз я заключил сделку с твоей женой.";
			link.l1.go = "FalseTrace_25";
		break;
		
		case "FalseTrace_25":
			dialog.text = "Что-о?! Кха! Какую еще сделку с моей женой? Ты что городишь, рыбья чешуя?";
			link.l1 = "По твоей фальшивой наводке я захватил пустой галеон и убил его капитана. Я сожалею, что сделал это, хотя уже поздно. Твоя жена, как я понял, любила этого моряка. Поэтому она заказала тебя. Мне. Вот почему мы здесь втроем, в этой бухте.";
			link.l1.go = "FalseTrace_26";
		break;
		
		case "FalseTrace_26":
			dialog.text = "Ушам не верю! Катерина... вот ведь маленькая дрянь! Ну доберусь я еще до тебя... И чем же она пообещала расплатиться с тобой, ты, олух? У нее нет ни гроша, даже украшения свои, которые я ей дарил, она продала, чтобы сбежать с этим капитанишкой!";
			link.l1 = "Не твое собачье дело, прохвост. Пора заканчивать наш разговор. Теперь я отправлю тебя в ад, где тебе самое место!";
			link.l1.go = "FalseTrace_27";
		break;
		
		case "FalseTrace_27":
			dialog.text = "Ну что же, посмотрим, что ты стоишь, тухлая селедка!";
			link.l1 = "...";
			link.l1.go = "FalseTrace_28";
		break;
		
		case "FalseTrace_28":
			DialogExit();
			LAi_SetWarriorType(npchar);
			LAi_SetImmortal(npchar, false);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "FalseTrace_AdamDead");
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
		case "FalseTrace_abordage":
			dialog.text = "Аргх! Какого черта ты напал на мой корабль, мерзавец? Вообще в толк не возьму...";
			link.l1 = "Не притворяйся овечкой, капитан. Мне стало известно о грузе, который ты везешь. Он-то мне и нужен.";
			link.l1.go = "FalseTrace_abordage_1";
		break;
		
		case "FalseTrace_abordage_1":
			dialog.text = "Грузе? Ха-ха! Какой груз ты ожидал здесь увидеть? У меня пустые трюмы!";
			link.l1 = "Что ты сказал, каналья? А ну, повтори!";
			link.l1.go = "FalseTrace_abordage_2";
		break;
		
		case "FalseTrace_abordage_2":
			dialog.text = "Повторяю - у меня нет никакого груза. Этот галеон - военное фуражное судно, и оно направлялось в "+XI_ConvertString("Colony"+pchar.questTemp.FalseTrace.TargetCity)+" за продовольствием для солдат и за пушечными ядрами.";
			link.l1 = "Ты что-то темнишь, негодяй. У тебя должны были быть полные трюмы серебра! И я собираюсь это проверить, после того, как мы закончим этот разговор...";
			link.l1.go = "FalseTrace_abordage_3";
		break;
		
		case "FalseTrace_abordage_3":
			dialog.text = "Я не знаю, кто сказал тебе о серебре, но это все полная чушь... Я проиграл абордаж и сдаюсь. Вот моя шпага. Теперь можешь идти смотреть трюмы - они пусты.";
			link.l1 = "Сдаешься? Ну уж нет! Мне свидетели ни к чему! Поднимай свою железяку и защищайся, или я прирежу тебя, как овцу!";
			link.l1.go = "FalseTrace_abordage_4";
			link.l2 = "Очень хорошо, что ты проявил благоразумие. Думаю, я смогу получить за тебя выкуп... Эй, ребята, отведите господина капитана в трюм!";
			link.l2.go = "FalseTrace_abordage_5";
		break;
		
		case "FalseTrace_abordage_4":
			DialogExit();
			pchar.questTemp.FalseTrace.KillCaptain = "true";//атрибут квеста
			Lai_SetPlayerType(pchar);
			QuestAboardCabinDialogFree();
			LAi_group_SetRelation(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck(LAI_GROUP_BRDENEMY, "FalseTrace_AfterFight");
			AddDialogExitQuest("MainHeroFightModeOn");
			pchar.questTemp.FalseTrace.CapName = GetFullName(npchar);
			ChangeCharacterComplexReputation(pchar, "nobility", -3);
		break;
		
		case "FalseTrace_abordage_5":
			DialogExit();
			pchar.questTemp.FalseTrace.CapPrisoner = "true";//атрибут квеста
			Lai_SetPlayerType(pchar);
			DeleteAttribute(npchar, "DontRansackCaptain");
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "FalseTrace_AfterFight", 3.0);
			pchar.GenQuest.LastQuestPrisonerIdx = SetCharToPrisoner(npchar);
			SetCharacterRemovable(&characters[sti(pchar.GenQuest.LastQuestPrisonerIdx)], false);
			pchar.questTemp.FalseTrace.CapName = GetFullName(npchar);
			ChangeCharacterComplexReputation(pchar, "nobility", 2);
		break;
		
		case "FalseTrace_wife":
			dialog.text = "Вы убили его, негодяй! Мерзавец! Подонок! Несчастный "+pchar.questTemp.FalseTrace.CapName+"!";
			link.l1 = "Это еще что за чудо? Откуда ты взялась, милочка?";
			link.l1.go = "FalseTrace_wife_1";
		break;
		
		case "FalseTrace_wife_1":
			dialog.text = "Гореть вам в аду за ваши деяния! Будьте вы...";
			link.l1 = "А ну тихо, барышня! Не испытывай судьбу, изливая здесь потоки брани и проклятий, иначе я мигом отправлю тебя следом за твоим капитаном!";
			link.l1.go = "FalseTrace_wife_2";
		break;
		
		case "FalseTrace_wife_2":
			dialog.text = "Вы... Вы не посмеете поднять руку на женщину!";
			link.l1 = "Да мне и руки поднимать не надо будет. Просто выброшу тебя за борт, а там дело довершат акулы... Ну? Чего встала? Топай живо на мой корабль! Не бойся, в обиду тебя я не дам и сам не трону, если будешь вести себя тихо...";
			link.l1.go = "FalseTrace_wife_3";
		break;
		
		case "FalseTrace_wife_3":
			DialogExit();
			pchar.quest.False_Trace_AfterBattle.over = "yes";
			pchar.quest.FalseTraceGaleonOver.over = "yes";
			if (CheckAttribute(pchar, "questTemp.FalseTrace.CapPrisoner")) AddQuestRecord("FalseTrace", "");
			else AddQuestRecord("FalseTrace", "");
			sld = characterFromId("Mugger");
			DeleteAttribute(sld, "HalfImmortal");
			RemovePassenger(Pchar, sld);
			AddPassenger(pchar, sld, false);
			SetCharacterRemovable(sld, false);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", 3.0);
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, false);
			DoQuestCheckDelay("LAi_ReloadBoarding", 4.0);
			bQuestDisableMapEnter = true;
			pchar.questTemp.FalseTrace = "TalkCabin";
			AddQuestRecord("FalseTrace", "4");
		break;
		
		case "FalseTrace_wife_4":
			dialog.text = "Вы.. вы... Что вы сделаете с ним?";
			link.l1 = "Это еще что за чудо? Откуда ты взялась, милочка?";
			link.l1.go = "FalseTrace_wife_5";
		break;
		
		case "FalseTrace_wife_5":
			dialog.text = "Бедный "+pchar.questTemp.FalseTrace.CapName+"! Ответьте мне - вы задумали убить его?! Не...";
			link.l1 = "Послушай, барышня, если бы я хотел его убить - я уже бы это сделал. А так он пока посидит в трюме, потом, может, я его отпущу или сдам за выкуп... второе более вероятно. А тебя я также попрошу пройти на мой корабль, и не бойся, в обиду не дам и сам не обижу, если будешь вести себя тихо...";
			link.l1.go = "FalseTrace_wife_3";
		break;
		
		case "FalseTrace_wife_6":
			if (CheckAttribute(pchar, "questTemp.FalseTrace.KillCaptain"))
			{
				dialog.text = "Что вам от меня еще нужно? Бросить акулам, как вы обещали? Вы разбили мне жизнь, и я...";
				link.l1 = "Полно, милочка. Никто никуда тебя бросать не собирается. Я вообще хочу прояснить ситуацию, поскольку нападением на галеон я обязан именно тебе, и никому другому.";
				link.l1.go = "FalseTrace_wife_7";
			}
			else
			{
				dialog.text = "Что вы от меня хотите? Где "+pchar.questTemp.FalseTrace.CapName+"? Выкуп? Вам нужен выкуп?";
				link.l1 = "Так, милочка, давай прекратим этот поток бессмысленных вопросов, я не для того тебя позвал сюда. Выяснился один факт, который тебе, безусловно, будет интересен.";
				link.l1.go = "FalseTrace_wife_20";
			}
		break;
		
		case "FalseTrace_wife_7":
			dialog.text = "Обязаны мне? Вы хотите сказать, что я виновна в том, что вы напали на наше судно и убили моего... мужчину? Бедный "+pchar.questTemp.FalseTrace.CapName+", что он вам сделал? Не кощунствуйте, вы за все ответите перед...";
			link.l1 = "Так, ты опять за свое? Нам что, снова вернуться к разговору об акулах?";
			link.l1.go = "FalseTrace_wife_8";
		break;
		
		case "FalseTrace_wife_8"://ноды пересечения - старт
			dialog.text = "";
			link.l1 = "Молчишь? Замечательно. Выслушай же меня наконец! Я совершил нападение на это судно, потому что у меня были сведения, что оно везет огромный груз серебра. И сведения эти я получил от Адама Рейнера.";
			link.l1.go = "FalseTrace_wife_9";
		break;
		
		case "FalseTrace_wife_9":
			dialog.text = "Ах! Что?! Адам? Где он? Неужели здесь?";
			link.l1 = "Вижу, это имя тебе знакомо... Катерина. Как видишь, я уже все про тебя знаю. Как я понимаю, Адам Рейнер - действительно твой муж?";
			link.l1.go = "FalseTrace_wife_10";
		break;
		
		case "FalseTrace_wife_10":
			dialog.text = "Да. Я действительно жена этого изверга. И наивно полагала, что с этим кошмаром уже покончено навсегда... Так это он вас нанял, чтобы захватить меня?";
			link.l1 = "В общем, получилось именно так. Адам солгал мне о грузе серебра, чтобы я захватил галеон '"+pchar.questTemp.FalseTrace.ShipName+"', с очевидной целью вернуть тебя. Четверть часа назад он дал мне полный отчет о своих дейстиях...";
			link.l1.go = "FalseTrace_wife_11";
		break;
		
		case "FalseTrace_wife_11":
			dialog.text = "И... что же он хочет? Что он вам сказал?";
			link.l1 = "Он хочет, чтобы его законная жена вернулась к нему. В качестве компенсации за то, что ввел меня в заблуждение, он обеспечит меня информацией о золоте Косого Солли. Мне только нужно доставить вас обоих в "+XI_ConvertString("Colony"+pchar.questTemp.FalseTrace.QuestCity)+".";
			link.l1.go = "FalseTrace_wife_12";
		break;
		
		case "FalseTrace_wife_12":
			dialog.text = "Нет...(плачет) Я не хочу возвращаться к этому мерзавцу! Я приложила столько сил, чтобы сбежать от него и замести следы, но он все равно меня нашел... Негодяй! Бандит! Вор проклятый!";
			link.l1 = "Тише, Катерина, успокойся... Он ведь все-таки твой муж. И он сказал, что любит тебя.";
			link.l1.go = "FalseTrace_wife_13";
		break;
		
		case "FalseTrace_wife_13":
			dialog.text = "(сквозь слезы) Мой муж? А вы знаете, кто он, мой муж? Он бывший заключенный, каторжник, а нынче - самый жестокий бандит "+XI_ConvertString("Colony"+pchar.questTemp.FalseTrace.StartCity+"Gen")+"! Он низкое и грубое животное, а я для него - не больше чем просто... подстилка!";
			link.l1 = "Катерина, но неужели ты не видела всего этого, когда выходила за него замуж?";
			link.l1.go = "FalseTrace_wife_14";
		break;
		
		case "FalseTrace_wife_14":
			dialog.text = "Поначалу он был другим. А его прошлое казалось мне тогда таким романтичным... Но потом все изменилось. И я не хочу его теперь даже видеть, не то, что жить с ним, понимаете - не хочу! Особенно после того, как он организовал нападение на галеон!";
			link.l1 = "Хм... И что же ты теперь прикажешь с тобой делать, милая барышня?";
			link.l1.go = "FalseTrace_wife_15";
		break;
		
		case "FalseTrace_wife_15"://ноды пересечения - конец
			if (CheckAttribute(pchar, "questTemp.FalseTrace.KillCaptain"))
			{
				dialog.text = "Что делать? А я вот знаю, что делать. Вы, благодаря преступным деяниям моего мужа, взяли грех на душу, убили ни в чем не повинного человека... единственного человека, которых хорошо ко мне относился... Искупите свою вину, капитан. Убейте Адама. Причем прямо у меня на глазах. Я хочу видеть, как будет умирать эта скотина, я хочу плюнуть на его труп\nА когда он испустит дух, я расскажу вам, где он прячет свои богатства, полученные воровством и грабежами. Он не знает, что мне известен его тайник, ха-ха! Пьяный негодяй проболтался во сне, и даже не вспомнил...";
				link.l1 = "Ого! А ты жестокая, Катерина, как я посмотрю!";
				link.l1.go = "FalseTrace_wife_16";
			}
			else
			{
				dialog.text = ""+pchar.questTemp.FalseTrace.CapName+"... Капитан галеона. Вы пленили его. Поговорите с ним, прошу вас! Он что-нибудь предложит вам за наши жизни и свободу! Он придумает! Я... я не хочу вернуться к Адаму, для меня теперь "+pchar.questTemp.FalseTrace.CapName+" - муж! Умоляю вас, не отдавайте меня Адаму, этому чудовищу!";
				link.l1 = "Хм. Интересно, и что же может мне предложить мой пленник? Выкуп за него я могу получить и у властей, и золотишко Косого Солли мне тоже достанется...";
				link.l1.go = "FalseTrace_wife_21";
			}
		break;
		
		case "FalseTrace_wife_16":
			dialog.text = "Не вам говорить о жестокости, капитан. Отправляйтесь в "+XI_ConvertString("Colony"+pchar.questTemp.FalseTrace.QuestCity)+", как вам Адам и сказал, но высадитесь не в порту, а в ближайшей бухте. Там мы втроем выйдем на берег, и вы прикончите мерзавца\nИ я сразу же расскажу вам о тайнике. Клянусь, что не лгу, и богатства Адама действительно существуют. Во всяком случае, поверить мне у вас больше оснований, чем Адаму с его мифическими сокровищами Косого Солли. Неужели вы ему верите? Он обманет вас так же, как обманул в первый раз, как обманывал меня всю нашу совместную жизнь\nЧто скажете, капитан?";
			link.l1 = "Да уж... Недаром говорят: муж и жена - одна сатана. Смотрю я на тебя, Катерина, и вижу, что ты для Адама - самая пара... Если тебе так нужна его смерть, сама зарежь его кинжалом, когда он будет в очередной раз спать, пьяный в стельку, и бормотать о каких-то тайниках... Боцман! Увести ее!";
			link.l1.go = "FalseTrace_wife_17";
			link.l2 = "Ненавижу мерзавцев, которые пытаются меня обмануть и использовать в своих целях. Так и поступим, Катерина, ибо Адаму уже нет веры. Но если ты меня обманешь - клянусь, что разыщу тебя даже в Европе, и всажу тебе пулю прямо в лоб. А теперь ступай. Боцман! Увести ее!";
			link.l2.go = "FalseTrace_wife_19";
		break;
		
		case "FalseTrace_wife_17":
			dialog.text = "Вы об этом пожалеете... Клянусь, что я...";
			link.l1 = "Боцман! Приставить к ней охрану и глаз не спускать до самого "+XI_ConvertString("Colony"+pchar.questTemp.FalseTrace.QuestCity+"Gen")+"!";
			link.l1.go = "FalseTrace_wife_18";
		break;
		
		case "FalseTrace_wife_18":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", 3.0);
			AddQuestRecord("FalseTrace", "6");
			AddQuestUserData("FalseTrace", "sCity", XI_ConvertString("Colony"+pchar.questTemp.FalseTrace.QuestCity));
			AddDialogExitQuestFunction("SetCheckForSolly");
			chrDisableReloadToLocation = false;
			bQuestDisableMapEnter = false;
			DeleteAttribute(pchar, "GenQuest.DontSetCabinOfficer");
		break;
		
		case "FalseTrace_wife_19":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", 3.0);
			AddQuestRecord("FalseTrace", "7");
			AddQuestUserData("FalseTrace", "sCity", XI_ConvertString("Colony"+pchar.questTemp.FalseTrace.QuestCity));
			AddDialogExitQuestFunction("SetCheckForKillAdam");
			chrDisableReloadToLocation = false;
			bQuestDisableMapEnter = false;
			DeleteAttribute(pchar, "GenQuest.DontSetCabinOfficer");
		break;
		
		case "FalseTrace_wife_20":
			dialog.text = "Какой еще факт? Что вы намерены сделать с нами? Зачем вы захватили наше судно?";
			link.l1 = "Ты дашь мне в конце концов слово сказать, или мне приказать боцману заткнуть тебе рот кляпом?!";
			link.l1.go = "FalseTrace_wife_8";
		break;
		
		case "FalseTrace_wife_21":
			dialog.text = "Золото Косого Солли? Вы верите Адаму, этому прохвосту? Да он обманет вас, как обманул с этим серебром, как обманывал меня всю нашу совместную жизнь! Вы ничего от него не получите, у него нет ни капли совести! Поговорите с вашим пленником!\n"+pchar.questTemp.FalseTrace.CapName+" - настоящий джентльмен, он не солжет и не изменит слову!";
			link.l1 = "Не убедила ты меня, барышня. Мне не о чем говорить с твоим капитаном. За него я получу выкуп, а от Адама - золото Солли. А если Адам меня обманет - разыщу хоть на краю света, и он пожалеет, что появился на свет... Боцман! Увести ее!";
			link.l1.go = "FalseTrace_wife_23";
			link.l2 = "Сказать честно, к Адаму у меня более нет доверия... Ненавижу, когда меня используют в своих целях. Ладно. Поговорю я с твоим капитаном, послушаем, что он сможет сказать. А ты ступай пока... Боцман! Увести ее!";
			link.l2.go = "FalseTrace_wife_24";
		break;
		
		case "FalseTrace_wife_23":
			dialog.text = "Вы жестокий, безжалостный человек! Клянусь, что я...";
			link.l1 = "Боцман! Приставить к ней охрану и глаз не спускать до самого "+XI_ConvertString("Colony"+pchar.questTemp.FalseTrace.QuestCity+"Gen")+"!";
			link.l1.go = "FalseTrace_wife_18";
			SetCharacterRemovable(&characters[sti(pchar.GenQuest.LastQuestPrisonerIdx)], true);
		break;
		
		case "FalseTrace_wife_24":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", 3.0);
			AddQuestRecord("FalseTrace", "8");
			chrDisableReloadToLocation = false;
			pchar.questTemp.FalseTrace.Prisoner = "true";
			SetCharacterRemovable(&characters[sti(pchar.GenQuest.LastQuestPrisonerIdx)], true);
		break;
		
		case "FalseTrace_wife_25":
			dialog.text = "Ну вот и всё... Несчастный "+pchar.questTemp.FalseTrace.CapName+" отомщен, и я наконец-то могу спокойно вздохнуть и назвать себя вдовой...";
			link.l1 = "Я выполнил свою часть сделки, Катерина. Теперь твоя очередь.";
			link.l1.go = "FalseTrace_wife_26";
		break;
		
		case "FalseTrace_wife_26":
			dialog.text = "Конечно, капитан. Мой муж, слава Богу, уже бывший, как вы знаете, был бандитом. Опасаясь обысков, он не держал дома награбленных ценностей. Он организовал тайник, о котором случайно и проболтался. Спрятал он его очень хитро - к тайнику нет доступа по суше.";
			link.l1 = "Очень интересно... И где же это?";
			link.l1.go = "FalseTrace_wife_27";
		break;
		
		case "FalseTrace_wife_27":
			dialog.text = "На небольшом островке у берегов Эспаньолы. На маяке.";
			link.l1 = "Маяк Порт-о-Пренса! Он находится на острове!";
			link.l1.go = "FalseTrace_wife_28";
		break;
		
		case "FalseTrace_wife_28":
			dialog.text = "Наверное, так. Там вы сможете найти много чего... Сами увидите. А теперь все. Прощайте, капитан.";
			link.l1 = "Подожди... Прости, Катерина, если сможешь, за то, что причинил тебе зло. Надеюсь, смерть виновника твоих несчастий хотя бы немного облегчит твои страдания. Я искренне сожалею...";
			link.l1.go = "FalseTrace_wife_29";
		break;
		
		case "FalseTrace_wife_29":
			dialog.text = "Мне не нужны ваши сожаления, капитан. Вы сделали, что я вас просила, я рассказала вам все, что вы хотели. Прощайте, и оставьте меня наедине с моим горем...";
			link.l1 = "Прощай, Катерина.";
			link.l1.go = "FalseTrace_wife_30";
		break;
		
		case "FalseTrace_wife_30":
			DialogExit();
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "", 15);
			LAi_LocationDisableOfficersGen(pchar.questTemp.FalseTrace.QuestShore, false);//офицеров пускать
			LAi_LocationDisableOfficersGen("Mayak7", true);//офицеров не пускать
			locations[FindLocation("Mayak7")].DisableEncounters = true;//энкаунтеры закрыть
			chrDisableReloadToLocation = false;
			bDisableFastReload = false;
			pchar.quest.False_Trace_7.win_condition.l1 = "location";
			pchar.quest.False_Trace_7.win_condition.l1.location = "Mayak7";
			pchar.quest.False_Trace_7.function = "FalseTrace_AdamTreasure";
			AddQuestRecord("FalseTrace", "23");
		break;
		
		case "FalseTrace_wife_31":
			dialog.text = "Гнусный негодяй! Вы ухитрились убить всех четверых! Невероятно!";
			link.l1 = "Не ожидала такого поворота, а, Катерина? Здорово ты умеешь вести двойные игры!";
			link.l1.go = "FalseTrace_wife_32";
		break;
		
		case "FalseTrace_wife_32":
			dialog.text = "Вы убили моего мужчину. Неужели вы думаете, что я могла позволить вам после этого спокойно ходить по этой земле?! И вы решили, что смерть Адама меня удовлетворила? Нет! Но вам не уйти так просто отсюда. У острова стоит корабль - он отправит вас и ваше корыто на дно!\nА теперь делайте со мной, что хотите.";
			link.l1 = "Я говорил тебе, милочка, что ты поплатишься своей головой, если обманешь меня? Коварная бестия! Мертвой ты будешь безопаснее. Так что помолись напоследок...";
			link.l1.go = "FalseTrace_wife_33";
			link.l2 = "Мне жаль тебя, Катерина. Жажда мести не довела тебя до добра. Я предоставляю тебя своей судьбе - ты останешься на этом островке. Думаю, местные рыбаки быстро найдут тебя и доставят на Эспаньолу. И Бог нам всем судья...";
			link.l2.go = "FalseTrace_wife_35";
		break;
		
		case "FalseTrace_wife_33":
			dialog.text = "Это вам нужно молиться, изверг! Убийца! Будьте вы...";
			link.l1 = "Пожалуй, хватит...";
			link.l1.go = "FalseTrace_wife_34";
		break;
		
		case "FalseTrace_wife_34":
			DialogExit();
			LAi_SetActorType(pchar);
			LAi_SetImmortal(npchar, false);
			LAi_ActorAnimation(pchar, "shot", "FalseTrace_CaterinaKilled", 1.0);
		break;
		
		case "FalseTrace_wife_35":
			dialog.text = "Да чтоб вам утонуть! Чтоб ваш корабль разбился о скалы! Чтобы вам...";
			link.l1 = "Прощай, Катерина.";
			link.l1.go = "FalseTrace_wife_36";
		break;
		
		case "FalseTrace_wife_36":
			DialogExit();
			sld = characterFromID("FalseTraceWife"); 
			sld.lifeday = 0;
			LAi_ActorGoToLocation(npchar, "goto", "goto33", "none", "", "", "", -1);
			LAi_SetPlayerType(pchar);
			chrDisableReloadToLocation = false;
			LAi_LocationDisableOfficersGen("Mayak7", false);//офицеров пускать
			locations[FindLocation("Mayak7")].DisableEncounters = false;//энкаунтеры открыть
			AddQuestRecord("FalseTrace", "25");
			ChangeCharacterComplexReputation(pchar, "nobility", 5);
			OfficersReaction("good");
		break;
		
		case "FalseTrace_Bandits":
			dialog.text = "А-а, вот и явился убийца Адама! Катерина была права - этот гад пришел разграбить тайник покойного!";
			link.l1 = "Что? Катерина?! Кто вы такие?";
			link.l1.go = "FalseTrace_Bandits_1";
		break;
		
		case "FalseTrace_Bandits_1":
			dialog.text = "Мы? Мы друзья Адама Рейнера, которого ты убил. Он был главой нашего братства. Теперь это место занимаю я, "+GetFullName(npchar)+", и я покараю тебя за убийство моего бывшего босса и товарища, и за насилие, которое ты учинил над его женой.";
			link.l1 = "Насилие? Что ты мелешь? Какое насилие?";
			link.l1.go = "FalseTrace_Bandits_2";
		break;
		
		case "FalseTrace_Bandits_2":
			dialog.text = "После того, как ты расправился с Адамом, вероломно убив ударом в спину, ты силой и угрозами выбил из его жены сведения, где Адам прячет свои сбережения, а затем бросил несчастную женщину на пустынном берегу на верную смерть\nНо она осталась жива, и пришла к нам за помощью, справедливо рассудив, что злодеяние не должно остаться безнаказанным. Мы уже который день дежурим здесь, ожидая твоего появления. И вот ты пришел, мерзавец!";
			link.l1 = "Ха-ха! Узнаю Катерину... Слушай, ты, я действительно убил Адама, но сделал это по просьбе его собственной жены - это была месть за смерть ее любовника. И за это она и рассказала мне, где находится тайник...";
			link.l1.go = "FalseTrace_Bandits_3";
		break;
		
		case "FalseTrace_Bandits_3":
			dialog.text = "Ты клевещешь на бедную вдову, негодяй! А зачем бы тогда она пришла к нам? Зачем она сказала нам забрать себе всё из тайника Адама, лишь бы мы убили тебя? Ей не нужно золото, ей нужна твоя смерть! Священная месть за смерть мужа!\nНо клянусь, она не умрет в нищете, и это так же верно, что меня зовут "+GetFullName(npchar)+", и то, что пришел твой последний час, иуда!";
			link.l1 = "Понятно... Смотрю, она сама лично явилась понаблюдать за этой комедией... К бою, джентльмены!";
			link.l1.go = "FalseTrace_Bandits_4";
		break;
		
		case "FalseTrace_Bandits_4":
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешим драться
			DialogExit();
			for (i=1; i<=4; i++)
			{
				sld = characterFromId("Adam_bandit_"+i);	
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "FalseTrace_BanditsAfterFight");
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
		case "FalseTrace_Remove1":
			dialog.text = "Ну и растяпа же вы, капитан! Прозевать галеон, полный серебра... Зря я связался с вами. Прощайте!";
			link.l1 = "Прощай, Адам.";
			link.l1.go = "FalseTrace_Remove2";
		break;
		
		case "FalseTrace_Remove2":
			DialogExit();
			LAi_ActorGoToLocation(npchar, "reload", "reload4_back", "none", "", "", "", 15);
		break;
		
		case "FalseTrace_Remove_exit":
			DialogExit();
			LAi_ActorGoToLocation(npchar, "reload", "reload4_back", "none", "", "", "FalseTraceWife_Remove", 15);
		break;
		
		case "FalseTrace_Remove2":
			dialog.text = "Я же предупреждал вас, капитан - в запасе две недели! Теперь Косой Солли уже вывез свою добычу. Я не виноват, что вы такой растяпа. Прощайте!";
			link.l1 = "Да уж, затянул я с этим делом. Прощай, надеюсь, больше не встретимся - ты приносишь одни неудачи.";
			link.l1.go = "FalseTrace_Remove_exit";
		break;
		
		case "FalseTrace_Solly":
			dialog.text = "Хех! Ну наконец-то, уже устали ждать, всех москиты изгрызли, проклятые... Постой... А где Солли? Что-то не понял...";
			link.l1 = "Солли не будет. Я за него... Так что вы или сами отдадите золото, или останетесь здесь на корм чайкам.";
			link.l1.go = "FalseTrace_Solly_1";
		break;
		
		case "FalseTrace_Solly_1":
			dialog.text = "Аргх! Ну, это мы еще посмотрим, кто кого! Ребята, на помощь! К бою!";
			link.l1 = "Вот теперь вам точно конец, шакалы!";
			link.l1.go = "FalseTrace_Solly_2";
			AddDialogExitQuestFunction("FalseTrace_SollyBonanzaAdd");
		break;
		
		case "FalseTrace_Solly_2":
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешим драться
			DialogExit();
			for (i=1; i<=6; i++)
			{
				sld = characterFromId("FTEnemy_crew_"+i);	
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "FalseTrace_SollyAfterFight");
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
		case "FalseTrace_GoldShip":
			dialog.text = "Вы все сделали, как мы договаривались, капитан. Спасибо, что поверили и пошли навстречу. Насчет Адама не беспокойтесь - я передам его в надежные руки и он получит по заслугам.";
			link.l1 = "Адам меня мало волнует. Что там насчет вашего обещания о неком корабле?";
			link.l1.go = "FalseTrace_GoldShip_1";
		break;
		
		case "FalseTrace_GoldShip_1":
			if (sti(pchar.basenation == HOLLAND) || sti(pchar.basenation == SPAIN))
			{
				pchar.questTemp.FalseTrace.ShipNation = ENGLAND;
				pchar.questTemp.FalseTrace.ShipCity = "PortRoyal";
			}
			else
			{
				pchar.questTemp.FalseTrace.ShipNation = SPAIN;
				pchar.questTemp.FalseTrace.ShipCity = "Maracaibo";
			}
			dialog.text = "Да-да, конечно. Так, прикинем начиная от сегодняшнего числа... Ага... Через двенадцать-четырнадцать дней из "+XI_ConvertString("Colony"+pchar.questTemp.FalseTrace.ShipCity+"Gen")+" выйдет тяжелый галеон с грузом золотой неочищенной руды и отправится в Европу. Его будет охранять судно сопровождения, думаю, корвет или фрегат\nТак что подготовьтесь как следует - добыча богатая, но зубастая. Хотя уверен, вы справитесь - я помню, как лихо вы подавили мое сопротивление... За две недели вам нужно добраться до "+XI_ConvertString("Colony"+pchar.questTemp.FalseTrace.ShipCity+"Gen")+" и устроить засаду\nПомните - ваша цель - тяжелый галеон с одним кораблем сопровождения. Вот пожалуй и всё... Остальное - в ваших руках.";
			link.l1 = "Понятно... Ну что же, "+pchar.questTemp.FalseTrace.CapName+", прощайте. Наверное, я должен пожелать вам удачи и счастья с Катериной? Надеюсь, у вас все будет хорошо. Жаль, что мы познакомились с вами при таких печальных обстоятельствах.";
			link.l1.go = "FalseTrace_GoldShip_2";
		break;
		
		case "FalseTrace_GoldShip_2":
			dialog.text = "Спасибо, капитан. Как я уже говорил - вы не лишены чувства благородства. Надеюсь, вы вскоре решите для себя, что честные поступки приносят гораздо больше пользы, нежели бесчестные. Посвятите себя службе во благо вашей державы - из вас выйдет отличный военный моряк.";
			link.l1 = "Я подумаю над вашими словами. Ну, а теперь - прощайте!";
			link.l1.go = "FalseTrace_GoldShip_3";
		break;
		
		case "FalseTrace_GoldShip_3":
			DialogExit();
			locations[FindLocation(pchar.questTemp.FalseTrace.TargetShore)].DisableEncounters = false; //энкаутеры открыть
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "FalseTraceDouble_Remove", -1);
			pchar.quest.False_Trace_6.win_condition.l1 = "Timer";
			pchar.quest.False_Trace_6.win_condition.l1.date.hour  = sti(GetTime());
			pchar.quest.False_Trace_6.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 14);
			pchar.quest.False_Trace_6.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 14);
			pchar.quest.False_Trace_6.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 14);
			pchar.quest.False_Trace_6.function = "CreateFalseTraceGoldShipOnMap";
			AddQuestRecord("FalseTrace", "19");
			AddQuestUserData("FalseTrace", "sCity", XI_ConvertString("Colony"+pchar.questTemp.FalseTrace.ShipCity+"Gen"));
			ChangeCharacterComplexReputation(pchar, "nobility", 3);
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
