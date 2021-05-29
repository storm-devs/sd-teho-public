// Элен Мак Артур - сомнительная любовь и офицер
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
		
		case "After_boarding":
			dialog.text = "Благодарю за помощь, капитан!";
			link.l1 = "Хм... Ты ещё красивей, чем я тебя представлял по рассказам!";
			link.l1.go = "After_boarding_1";
		break;
		
		case "After_boarding_1":
			dialog.text = "Чёрт бы побрал эту красоту! Из-за неё я чуть было не сыграла в ящик. Живой бы он меня с корвета не отпустил, только с ядром на шее, потому как я слишком много знаю про этого ублюдка. Вчера он сказал, что устал ждать и намерен добиться от меня расположения вопреки моей воле\nТак что ты вовремя успел, кэп! Давай знакомиться. Меня зовут Элен Мак Артур. Отец с детства называл Румбой за веселый нрав, так это прозвище ко мне и приклеилось.";
			link.l1 = "Ну а меня зовут "+GetFullName(pchar)+". Вот уже несколько дней разыскиваю тебя по всему архипелагу по просьбе миссис Глэдис.";
			link.l1.go = "After_boarding_2";
		break;
		
		case "After_boarding_2":
			dialog.text = "Как она?";
			link.l1 = "Сильно переживает за тебя. Впрочем, скоро ты её увидишь, мы идём в Блювельд. По дороге расскажешь про свои злоключения подробнее...";
			link.l1.go = "After_boarding_3";
		break;
		
		case "After_boarding_3":
			dialog.text = "Сказать по чести, "+pchar.name+", мне сейчас больше всего хотелось бы поесть и лечь спать. Я зверски устала за все эти кошмарные дни, проведённые на корабле этого изверга...";
			link.l1 = "Нет проблем, Элен. Я прикажу подать тебе еду и приготовить койку. Будь моей гостьей!";
			link.l1.go = "After_boarding_4";
		break;
		
		case "After_boarding_4":
			DialogExit();
			LAi_SetActorType(npchar);
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, false);
			npchar.greeting = "helena_2";
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", 10.0);
			pchar.questTemp.Saga = "returntoblueveld";
			Island_SetReloadEnableGlobal("Antigua", true);//на остров можно
			bQuestDisableMapEnter = false;//открыть карту
			AddQuestRecord("Saga", "11");
			pchar.quest.Saga_returnBlueveld.win_condition.l1 = "location";
			pchar.quest.Saga_returnBlueveld.win_condition.l1.location = "Santacatalina_town";
			pchar.quest.Saga_returnBlueveld.function = "Saga_returnBlueveld";
			SetFunctionTimerCondition("Helena_ReturnOver", 0, 0, 45, false);
			sld = characterFromId("gladis");
			sld.greeting = "gladis_3";
		break;
		
		case "Return_blueveld":
			pchar.quest.Helena_ReturnOver.over = "yes";
			dialog.text = "Ещё раз от всего сердца благодарю тебя, мой капитан, за чудесное спасение. Ты обязательно должен навестить нас с матушкой. Наш домик тут совсем рядом. Вот он, налево от пирса в самом конце. И учти, "+pchar.name+", если ты исчезнешь, не простившись, никогда тебе этого не прощу, так и знай!";
			link.l1 = "Зайду обязательно!";
			link.l1.go = "Return_blueveld_1";
		break;
		
		case "Return_blueveld_1":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "houseSp3", "SantaCatalina_houseSp3_bedroom", "goto", "goto1", "OpenTheDoors", -1);
			AddQuestRecord("Saga", "13");
			LocatorReloadEnterDisable("SantaCatalina_houseS1", "reload2", false); // открыть кабинет Свенсона
			pchar.questTemp.Saga = "svenson";//идем к Свенсону
			sld = characterFromId("JS_girl");
			sld.dialog.currentnode = "js_girl";
			npchar.dialog.currentnode = "Helena_wait";
			sld = characterFromId("Gladis");
			sld.dialog.currentnode = "Gladis_regard";
			LocatorReloadEnterDisable("SantaCatalina_houseSp3", "reload2", true);//закрыть спальню Элен
			// закрыть город до беседы с Глэдис
			LocatorReloadEnterDisable("SantaCatalina_town", "reload1_back", true);
			LocatorReloadEnterDisable("SantaCatalina_town", "reload2_back", true);
			LocatorReloadEnterDisable("SantaCatalina_town", "gate_back", true);
		break;
		
		case "Helena_wait":
			dialog.text = "А вот и ты, мой капитан! Как я рада, "+pchar.name+", что ты решил наконец меня проведать. Я о многом хотела бы поговорить с тобой.";
			link.l1 = "Отложим этот разговор на некоторое время. Я должен кое-что выяснить, прежде чем смогу ответить на твои вопросы. А пока убедительно прошу не показываться на людях без особой необходимости. Надеюсь, твоё ожидание будет недолгим. Верь мне и жди.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Helena_wait";
		break;
		
		case "Helena_hire":
			dialog.text = "А вот и ты, мой капитан! По глазам вижу, у тебя есть новости для меня!";
			link.l1 = "Свенсон сказал, что ты рвёшься ко мне в офицеры. Я очень рад твоему желанию - Глэдис говорила, что ты очень тоскуешь без моря. Добро пожаловать в мою команду, офицер Элен Мак Артур!";
			link.l1.go = "Helena_hire_1";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_friend"))
			{
				link.l2 = "Свенсон сказал, что ты хочешь стать офицером на моём корабле. Я очень рад твоему желанию - Глэдис говорила, что ты очень тоскуешь без моря. Добро пожаловать в мою команду, офицер Элен Шарп!";
			link.l2.go = "Helena_hire_2";
			}
		break;
		
		case "Helena_hire_1":
			DeleteAttribute(pchar, "questTemp.Saga.Helena_friend");
			dialog.text = "Есть, мой капитан! Но учти, я девушка гордая, могу за себя постоять и никаких вольностей не потерплю.";
			link.l1 = "Не волнуйся, у нас на корабле с этим строго. Кроме того, хочу добавить ещё кое-что...";
			link.l1.go = "Helena_hire_1_1";
		break;
		
		case "Helena_hire_1_1":
			dialog.text = "И что же это?";
			link.l1 = "Мы с Яном Свенсоном выяснили, что у тебя есть все права на наследование острова Исла Тесоро. Да, да, именно так, хотя на первый взгляд кажется невероятным. У меня есть половинка карты, которая поможет доказать это. Хотя с этим делом всё не так просто, мы с мистером Свенсоном поможем тебе стать полноправной наследницей острова.";
			link.l1.go = "Helena_hire_1_2";
		break;
		
		case "Helena_hire_1_2":
			dialog.text = ""+pchar.name+", ты серьезно? Нет, ты смеешься над бедной девушкой! Откуда у меня могут быть права на целый остров?";
			link.l1 = "Я абсолютно серьёзен, Элен. Более того - намерен помочь тебе устроить твою жизнь. А сейчас - отправляемся в путь!";
			link.l1.go = "Helena_hire_6";
		break;
		
		case "Helena_hire_2":
			dialog.text = "Как ты сказал? Элен Шарп? А почему Шарп?";
			link.l1 = "Элен, ты - дочь Беатрисс Шарп, и единственная наследница по линии Шарпов. Эта половинка карты, которую бережно хранила Глэдис все эти годы, является подтверждением твоих прав на остров Исла-Тесоро и Шарптаун. Но с этим делом всё не так просто, и мы с мистером Свенсоном поможем тебе стать полноправной наследницей твоего деда.";
			link.l1.go = "Helena_hire_3";
		break;
		
		case "Helena_hire_3":
			dialog.text = "Ах... Бедная моя мама! Надеюсь когда-нибудь найти её могилку и позаботиться о ней. Но... постой! Невероятно!";
			link.l1 = "Что такое, Элен?";
			link.l1.go = "Helena_hire_4";
		break;
		
		case "Helena_hire_4":
			dialog.text = "Сбылось пророчество цыганки... Я только сейчас это поняла.";
			link.l1 = "Какое ещё пророчество? О чём ты это сейчас?";
			link.l1.go = "Helena_hire_5";
		break;
		
		case "Helena_hire_5":
			dialog.text = ""+pchar.name+", ты, наверное, сочтёшь меня наивной, но я всё равно скажу тебе. Несколько лет назад цыганка на улице сказала мне: 'твоя судьба в руках того, кто не возьмёт денег вдовы, вернёт золото мертвеца и назовёт имя матери'\nТогда я подумала, что это полная чушь. Но появился ты, и не только спас меня от позорной смерти, но и умудрился выполнить все три условия пророчества, о котором не мог ничего знать заранее!";
			link.l1 = "Судьба, говоришь... Что жe, вполне может быть и так. Я постараюсь не разочаровать тебя, а могилку твоей матери мы поищем вместе. А пока... Офицер Элен Шарп! Собирайся и не опаздывай к отплытию!";
			link.l1.go = "Helena_hire_6";
		break;
		
		case "Helena_hire_6":
			dialog.text = "Есть, капитан!";
			link.l1 = "...";
			link.l1.go = "Helena_hire_add";
		break;
		
		case "Helena_hire_add":
			LAi_SetImmortal(npchar, false);
			chrDisableReloadToLocation = true;//закрыть локацию
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "Saga_HireHelena", -1);
			LocatorReloadEnterDisable("SantaCatalina_town", "reload1_back", false);
			LocatorReloadEnterDisable("SantaCatalina_town", "reload2_back", false);
			LocatorReloadEnterDisable("SantaCatalina_town", "gate_back", false);//открыть выходы из города
			pchar.questTemp.Saga = "svenson_wait";
			AddQuestRecord("Saga", "24");
			SetFunctionTimerCondition("Saga_BaronsQuestsGo", 0, 0, 2+rand(2), false);
			AddCharacterExpToSkill(pchar, "Leadership", 100);
		break;
		
		//-->  консультации по морским сражениям в искушении барбазона
		case "sea_bomb":
			dialog.text = ""+pchar.name+"! У меня возникла одна идея...";
			link.l1 = ""+npchar.name+"? Тут вообще-то опасно, и я велел оставаться на корабле...";
			link.l1.go = "sea_bomb_1";
		break;
		
		case "sea_bomb_1":
			dialog.text = ""+pchar.name+", на этом корыте столько пороха, что взорвись он - и взлетит на воздух весь остров, так что разницы нет - на этом судне мы, или на нашем. Но ты выслушай меня!";
			link.l1 = "Ну? Что ты хотела сказать?";
			link.l1.go = "sea_bomb_2";
		break;
		
		case "sea_bomb_2":
			dialog.text = "Корвет и фрегат. Они считают нас за своего... Валета. Мы можем этим воспользоваться. Сейчас возьмём пару самых больших бочек с порохом отсюда, приладим фитиль и поплывём к тем кораблям\nОни подпустят нас вплотную и мы незаметно скинем бочку рядом с одним из них, зажжём шнур и быстро слиняем. Главное - успеть подальше отойти. А потом понаблюдаем, как вражеское корыто взлетит к небесам... Что скажешь?";
			link.l1 = "Ну ты выдумщица! Хотя, твой план может сработать... Но только если нас не распознают.";
			link.l1.go = "sea_bomb_3";
		break;
		
		case "sea_bomb_3":
			dialog.text = "Рискнем, "+pchar.name+"? Ведь с двумя кораблями нам будет трудно управиться, а так есть шанс...";
			link.l1 = "Хорошо. Так и сделаем! Ребята! Заберите три бочки с порохом на борт! И уходим! Ну у тебя и фантазия, "+npchar.name+"... Я бы не додумался.";
			link.l1.go = "sea_bomb_4";
		break;
		
		case "sea_bomb_4":
			chrDisableReloadToLocation = false;
			DialogExit();
			LAi_SetOfficerType(npchar);
			npchar.dialog.currentnode = "Helena_officer";
			pchar.questTemp.Saga.BarbTemptation.Bomb = "true";
			pchar.questTemp.Saga.BarbTemptation.adviser = "Helena";
		break;
		
		case "fugas":
			dialog.text = "Да, конечно. О чём пойдёт речь?";
			link.l1 = "В бухте Сабу-Матила стоит корабль Джекмана, тяжёлый фрегат 'Центурион'. Это судно принадлежало раньше Хоукам, кроме того, в каюте Джекмана должны быть важные документы и вещи... в общем, его нужно брать на абордаж.";
			link.l1.go = "fugas_1";
		break;
		
		case "fugas_1":
			dialog.text = "Понятно. И ты сейчас думаешь, как ухитриться сделать это на нашем полакре? У них команды больше, чем у нас, и пушек тоже.";
			link.l1 = "Именно так. У Джекмана как минимум вдвое больше людей, и все отлично обучены - отборные наёмники. Атаковать нахрапом, без артподготовки - полное безумие. Затяжная морская баталия тоже может обернуться не в нашу пользу. Вот я и ломаю голову - что бы такое придумать.";
			link.l1.go = "fugas_2";
		break;
		
		case "fugas_2":
			dialog.text = "Ты не поверишь, "+pchar.name+", но я уже об этом думала и кое-что придумала! Они ведь нас пока ещё не узнали - считают своим, как те два олуха, на Терксе... Можно повторить операцию.";
			link.l1 = "Элен! Я же только что сказал - фрегат нельзя топить, его нужно абордировать!";
			link.l1.go = "fugas_3";
		break;
		
		case "fugas_3":
			dialog.text = "Я всё помню, "+pchar.name+". Топить не будем. Послушай: берём несколько пустых бочонков из-под рома, засыпаем туда порох, мелкую картечь и прилаживаем очень короткий фитиль. Затем подходим к борту фрегата и кидаем бочонки с нашим огненным ромом им на палубу.";
			link.l1 = "Ха! Ты думаешь, это получится?";
			link.l1.go = "fugas_4";
		break;
		
		case "fugas_4":
			dialog.text = "А почему нет? Борта у них выше, но два человека вполне забросят бочонок наверх. Крикнем - 'лови ром в подарок от Валета'! Пока они будут соображать, что да как - бочонки взорвутся.";
			link.l1 = "Картечь разлетится в стороны и буквально сметёт всех, кто будет поблизости... Чёрт возьми, звучит заманчиво. Там целые толпы наёмников слоняются по палубе от безделья! Они как раз и есть самые опасные.";
			link.l1.go = "fugas_5";
		break;
		
		case "fugas_5":
			dialog.text = "Кинем не один бочонок, а штук пять в разные места. "+pchar.name+", у нас огромное преимущество - внезапность. Они ничего не подозревают! А потом сразу отходим от них подальше, чтобы не успели забросить абордажные крючья.";
			link.l1 = "Ну что же, попробуем. Главное - чтобы они не увидели раньше времени, что 'Марлин' уже не под командованием братца Джекмана... Чёрт возьми, это будет нелегко - к ним подобраться. Джекман не такой простак, как Упырь.";
			link.l1.go = "fugas_6";
		break;
		
		case "fugas_6":
			dialog.text = "Рискнём, "+pchar.name+"! Если не получится - хуже не будет.";
			link.l1 = "Хуже не будет, это точно... Готовим фугасы, и к бою!";
			link.l1.go = "fugas_7";
		break;
		
		case "fugas_7":
			DialogExit();
			npchar.dialog.currentnode = "Helena_officer";
			pchar.questTemp.Saga.BarbTemptation.Fugas = "true";
			AddQuestRecord("BarbTemptation", "21");
			DeleteAttribute(npchar, "quest.fugas");
		break;
		//<--  консультации по морским сражениям
		
	// --> разговор по итогам Саги
		case "result":
			if (!CheckAttribute(pchar, "questTemp.Saga.Helena_friend")) // не друзья
			{
				dialog.text = "Ну что, мой капитан... Настало время нам с тобой проститься. Моя служба закончилась, и мне пора привыкать к роли хозяйки Исла-Тесоро. Надеюсь, я смогу стать достойной преемницей своего дяди. Благодарю тебя за помощь.";
				link.l1 = "Жаль, конечно, расставаться, но что же поделать. У тебя теперь есть дела поважнее, чем служба на моём судне.";
				link.l1.go = "result_1";
			}
			else
			{
				dialog.text = "Как странно, "+pchar.name+"! Я только что стала владелицей целого острова, но совсем не чувствую себя хозяйкой Исла Тесоро... Полагаю, новый глава Берегового братства управится с делами колонии куда лучше меня. Мне же будет достаточно просто ренты.";
				link.l1 = "Хм. Ты уверена, Элен? Подумай, у тебя же в собственности целый остров!";
				link.l1.go = "result_9";
			}
		break;
		
		case "result_1":
			dialog.text = "Ты прав... Мне тут удалось собрать немного золота - то, что я заработала на твоём корабле. Возьми его и не вздумай отказываться - я не хочу чувствовать себя твоим должником.";
			link.l1 = "Гм. Вообще-то...";
			link.l1.go = "result_2";
		break;
		
		case "result_2":
			dialog.text = "Я понимаю, что ты хочешь сказать. Безусловно, твоя помощь была намного значительней этого сундука с монетами. Но это почти всё, что у меня есть, а отблагодарить тебя я просто обязана. Бери, а если не возьмешь сам - я оставлю его у тебя в каюте.";
			link.l1 = "Ты что, сходишь на берег прямо сейчас? Может, тебя отвезти на Исла Тесоро?";
			link.l1.go = "result_3";
		break;
		
		case "result_3":
			GiveItem2Character(pchar, "chest");
			Log_Info("Вы получили сундук с дублонами");
			PlaySound("interface\important_item.wav");
			dialog.text = "Не стоит, "+pchar.name+". Я сама доберусь до своего острова. Некоторая сумма денег у меня есть, на первое время хватит... А хозяйке Исла Тесоро, я уверена, не придётся беспокоиться о доходах.";
			link.l1 = "Ну что же - как скажешь. Желаю тебе удачи в твоей новой жизни.";
			if (!CheckAttribute(pchar, "questTemp.Saga.Beltrop_die")) link.l1.go = "result_4";
			else link.l1.go = "result_7";
		break;
		
		case "result_4":
			dialog.text = "Спасибо. Но это ещё не всё. Я вновь обрела отца, хотя и столь необычным образом. Фактически, он заплатил своим добрым именем английского дворянина за моё наследство, и меня это очень угнетает. На него объявлена охота, и я бы очень не хотела, чтобы ты, "+pchar.name+", принял в ней участие.";
			link.l1 = "Опомнись, Элен! Он же бандит и пират!";
			link.l1.go = "result_5";
		break;
		
		case "result_5":
			dialog.text = "Пират? А ты-то кто? В первую очередь он мой отец! И мне, дочери бандита и пирата, глубоко плевать, что о нём думает английское правосудие. И если ты попробуешь причинить вред моему отцу, то я забуду всё то хорошее, что ты успел для меня сделать. Учти, я тебя предупредила.";
			link.l1 = "Вот как? Вообще-то, девочка, можно было и повежливее. Что-то я не заметил от тебя критики по поводу моего пиратского поведения, когда я вытаскивал тебя из лап Донована, самым разбойничьм образом захватив его корвет!";
			link.l1.go = "result_6";
		break;
		
		case "result_6":
			dialog.text = "Извини. Я погорячилась. Но мне всё-таки хотелось бы остаться с тобой друзьями, что станет невозможным, если ты начнёшь строить козни против моего отца.";
			link.l1 = "Я услышал тебя. Но более никогда не смей угрожать мне, Элен... Белтроп. За время службы на моём корабле ты должна была понять, что я не боюсь ни чёрта, ни морского дьявола. И тебя тоже не испугаюсь, поверь мне. А теперь - прощай. И не смотря ни на что, я желаю тебе удачи.";
			link.l1.go = "result_8";
		break;
		
		case "result_7":
			dialog.text = "Спасибо. Возможно, ещё когда-нибудь встретимся, "+pchar.name+"...";
			link.l1 = "А почему нет? На Исла Тесоро мне предстоит побывать ещё не раз. Там и увидимся... Пока, Элен!";
			link.l1.go = "result_8";
		break;
		
		case "result_8": // Элен уходит, но ее не затираем
			DialogExit();
			RemovePassenger(pchar, npchar);
			//chrDisableReloadToLocation = true;//закрыть локацию  // уже не надо.
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "goto", "goto24", "", "", "", "", 7);//OpenTheDoors лесник . чтобы бежала и исчезла а не стояла.
			AddQuestRecord("Testament", "11");
			CloseQuestHeader("Testament");
			LocatorReloadEnterDisable("PortRoyal_town", "reload1_back", false); // лесник . пирс. 
			LocatorReloadEnterDisable("PortRoyal_town", "gate_back", false); // ворота.
			InterfaceStates.Buttons.Save.enable = true;//можно сохраняться		
		break;
		
		case "result_9": // вот тут - ключевой момент, если игрок нашел Мэри - выбирай, какая девушка милее
			dialog.text = "Я уже подумала. "+pchar.name+", если ты позволишь, я бы и дальше хотела остаться у тебя на корабле. Рядом с тобой...";
			if (CheckAttribute(pchar, "questTemp.LSC.Mary") && pchar.questTemp.LSC.Mary == "alive")
			{
				link.l1 = "(выбрать Мэри) Элен! Ты, похоже, не понимаешь. Ты обеспечена до конца своих дней, и можешь не беспокоиться о будущем. У меня же впереди - война, закулисные интриги и полная неизвестность. Тебе нужно устраивать свою жизнь, а не связывать её с авантюристом.";
				link.l1.go = "result_10";
				link.l2 = "(выбрать Элен) Я мог только мечтать об этом, Элен. Конечно, я не хочу терять тебя, но, возможно, тебе было бы лучше отправиться на Исла Тесоро. Кто знает, куда приведёт меня моя судьба. У меня впереди - война, закулисные интриги и полная неизвестность.";
				link.l2.go = "result_15";
			}
			else
			{
				link.l1 = "Я мог только мечтать об этом, Элен. Конечно, я не хочу терять тебя, но, возможно, тебе было бы лучше отправиться на Исла Тесоро. Кто знает, куда приведёт меня моя судьба. У меня впереди - война, закулисные интриги и полная неизвестность.";
				link.l1.go = "result_15";
			}
		break;
		
		case "result_10":
			dialog.text = ""+pchar.name+"! Не лги мне. Ты просто не хочешь, чтобы... Скажи: это она? Та рыжая девчонка с Острова Погибших Кораблей? Да?";
			link.l1 = "Элен! Я в первую очередь думаю о тебе! Как ты этого не понимаешь?!";
			link.l1.go = "result_11";
		break;
		
		case "result_11":
			dialog.text = "Я так и знала... И чем же она тебя так очаровала, а? Эх, "+pchar.name+"... Ну, раз ты так решил - то мне и впрямь больше ничего не остается, как отправиться на свой остров. Я не буду стоять между вами\nВ любом случае, огромное спасибо тебе за всё, что ты для меня сделал. Ты - лучший из всех, кого я только знала. Ну а друзьями-то мы останемся?";
			link.l1 = "Конечно... Элен, мы с тобой ещё не раз встретимся на Исла Тесоро. Тебя отвезти на твой остров?";
			link.l1.go = "result_12";
		break;
		
		case "result_12":
			dialog.text = "Не надо. Я куплю себе корабль. За время службы у тебя я собрала сумму, достаточную для покупки и снаряжения шхуны. У меня снова будет моя 'Радуга'.";
			link.l1 = "Очень рад, Элен, что ты оказалась такой... хозяйственной. Но владелице Исла Тесоро не пристало ходить на шхуне - думаю, в скором времени ты обзаведёшься собственным фрегатом.";
			link.l1.go = "result_13";
		break;
		
		case "result_13":
			dialog.text = "Всё возможно, "+pchar.name+". Ладно. Пойду на верфь, присматривать себе новый корабль, но сначала... поцелуй меня, на прощание. Пожалуйста...";
			link.l1 = "Элен...";
			link.l1.go = "result_14";
		break;
		
		case "result_14": // прощальный поцелуй
			DialogExit();
			SetMusic("music_romantic");
			SetLaunchFrameFormParam("", "", 0, 12);
			SetLaunchFrameFormPic("loading\inside\kiss.tga");
			LaunchFrameForm();
			WaitDate("", 0, 0, 0, 0, 20); //крутим время
			RecalculateJumpTable();
			DoQuestCheckDelay("Saga_HelenaBye", 12.0);
			pchar.questTemp.LSC.Mary = "return"; // к Мэри
			LocatorReloadEnterDisable("PortRoyal_town", "reload1_back", false); // лесник . пирс. 
			LocatorReloadEnterDisable("PortRoyal_town", "gate_back", false); // ворота.
			InterfaceStates.Buttons.Save.enable = true;//можно сохраняться																					   
		break;
		
		case "result_15":
			dialog.text = "С первой же нашей встречи твоя судьба стала моей судьбой. Неужели ты до сих пор этого не понял, "+pchar.name+"? Я пойду с тобой хоть на край света!";
			link.l1 = "А твой отец? Лоуренс Белтроп? Ведь вышло так, что он оказался моим врагом...";
			link.l1.go = "result_16";
		break;
		
		case "result_16":
			dialog.text = "Мой отец - Шон Мак Артур! Я любила его, и уже оплакала его смерть. Другого отца у меня нет и быть не может. А этот пират... я не хочу о нём даже говорить.";
			link.l1 = "Элен... Дорогая Элен!..";
			link.l1.go = "result_17";
		break;
		
		case "result_17":
			dialog.text = ""+pchar.name+", я давно хотела тебе сказать: ты - лучший, ты - удивительный! Ты столько сделал для меня, что мне жизни не хватит, чтобы отплатить за твоё добро. Я хочу быть с тобой рядом. Всегда. И если ты этого захочешь, я стану твоей женой... Я люблю тебя.";
			link.l1 = "Мы будем вместе. Обещаю!"; // а куда же ты теперь денешься :)
			link.l1.go = "result_18";
		break;
		
		case "result_18":
			dialog.text = ""+pchar.name+", дорогой... Обними меня! Я так долго ждала этого момента!";
			link.l1 = "Элен, девочка моя...";
			link.l1.go = "result_19";
		break;
		
		case "result_19": // романтик-сцена
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_SetActorType(pchar);
			StartQuestMovie(true, true, true);
			PlayStereoOGG("music_romantic");
			bDisableCharacterMenu = true;//лоченые интерфейсы
			InterfaceStates.Buttons.Save.enable = false;//запретить сохраняться
			locCameraRotateAroundHero(0.0, 2.0, 0.0, 0.01, 0.0, 2.0, 0.0, 580);
			DoQuestCheckDelay("Saga_HelenaRomantic", 20.0);
			pchar.GenQuest.MusicContinue = true;
			AddCharacterExpToSkill(pchar, "Leadership", 100);
			DeleteAttribute(pchar, "questTemp.LSC.MaryWait");
			LocatorReloadEnterDisable("PortRoyal_town", "reload1_back", false); // лесник . пирс. 
			LocatorReloadEnterDisable("PortRoyal_town", "gate_back", false); // ворота.																					   
		break;
		
		case "happy":
			dialog.text = ""+pchar.name+"! Это было просто... замечательно! Я никуда не хочу уходить... Давай останемся тут до утра. И пусть весь мир подождёт!";
			link.l1 = "Пускай подождёт, Элен!";
			link.l1.go = "happy_1";
		break;
		
		case "happy_1":
			DialogExit();
			LSC_MaryLoveWaitTime();
			SetLaunchFrameFormParam("Следующим утром...", "", 0, 4);
			LaunchFrameForm();
			DoQuestCheckDelay("Saga_HelenaRomantic_5", 4.0);
			pchar.questTemp.Saga.Helena_officer = "true"; // показатель, что Элен - наша навсегда
		break;
		
	// -------------------------------------------- провалы саги ------------------------------------
		case "failcenturion":
			dialog.text = "Капитан! Джекман уничтожен... Это значит, что более ни с чьей стороны в адрес моей семьи угроз и опасностей нет?";
			link.l1 = "Да, Элен, это так. Но радости у меня мало - вместе с 'Центурионом' утонули документы и вещи, которые могли бы позволить нам найти могилу твоей мамы, и доказать твои права на Исла Тесоро. Эх... Теперь и Тортугу придётся брать в одиночку...";
			link.l1.go = "failcenturion_1";
		break;
		
		case "failcenturion_1":
			dialog.text = ""+pchar.name+", не огорчайся. Ну что же теперь поделать. А из-за меня точно не печалься - я прекрасно проживу и без этого острова. Спасибо тебе за всё, что ты сделал для меня!";
			link.l1 = "Ты так говоришь, словно уходишь... да?";
			link.l1.go = "failcenturion_2";
		break;
		
		case "failcenturion_2":
			dialog.text = "Да, мой капитан. Мне удалось отложить на твоей службе денег, достаточных для покупки и снаряжения шхуны. У меня снова будет моя 'Радуга'. Но мы с тобой ещё не раз увидимся в Блювельде, правда? Я возвращаюсь домой.";
			link.l1 = "Ну что же... удачи, Элен!";
			link.l1.go = "failcenturion_3";
		break;
		
		case "failcenturion_3":
			DialogExit();
			RemovePassenger(pchar, npchar);
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "OpenTheDoors", 5.0);
			if (CheckAttribute(pchar, "questTemp.LSC.Mary") && GetCharacterIndex("Mary") != -1 && !CheckAttribute(pchar, "questTemp.LSC.Mary_officer")) // patch-6
			{
				pchar.questTemp.LSC.Mary = "return"; // к Мэри
			}
		break;
		
		case "late_l1":
			dialog.text = "Ну что же, мой капитан... Видимо, так и не удалось нам с тобой осуществить задуманное. Прощай. Я возвращаюсь домой. На заработанные у тебя деньги я куплю себе новую шхуну, так что ещё, думаю, не раз увидимся в море!";
			link.l1 = "Удачи, Элен. Мне жаль, что всё так неудачно вышло. Прощай.";
			link.l1.go = "failcenturion_3";
		break;
		
		case "late_l2":
			dialog.text = "Капитан! Джекман уничтожен... Это значит, что более ни с чьей стороны в адрес моей семьи угроз и опасностей нет?";
			link.l1 = "Да, Элен, это так. Но радости у меня мало - я потерял очень много времени, и Исла Тесоро теперь - английская колония. И ты теперь без положенного наследства, и мне придётся брать Тортугу самому...";
			link.l1.go = "failcenturion_1";
		break;
		
		case "late_l3":
			dialog.text = ""+pchar.name+", что там сказал адвокат?";
			link.l1 = "Эх! Я потерял очень много времени, и Исла Тесоро теперь - английская колония. И ты теперь без положенного наследства, и мне придётся брать Тортугу самому... Увы, но мы проиграли.";
			link.l1.go = "failcenturion_1";
		break;
	// <-- провалы Саги
		
		// секс - Элен соглашается не всегда (голова болит, а что вы хотели? :)) и сама не требует секса
		case "cabin_sex":
			if (drand(4) == 0)// вероятность отказа 20%
			{
				dialog.text = RandPhraseSimple(""+pchar.name+", я себя что-то совсем неважно чувствую. Не обижайся, пожалуйста. Давай не сегодня...",""+pchar.name+", дорогой, я так устала за последние несколько дней. Честно говоря, мне хочется просто поспать. Не обижайся. Давай в другой раз.");
				link.l1 = RandPhraseSimple("Ну хорошо...","Не обижаюсь. Как скажешь...");
				SaveCurrentNpcQuestDateParam(npchar, "sex_go"); // лесник = так же . но в корабле . отказ сохраняем . 
				npchar.quest.daily_sex_cabin = true; // на случай если в самый первый раз откажет чтоб по 10000 раз не приставал .. в кабине
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = RandPhraseSimple(""+pchar.name+", я с радостью поддерживаю твоё предложение! Идем!",""+pchar.name+", ну конечно же не возражаю! Идём!");
				link.l1 = RandPhraseSimple("Ты моя умничка...","Ты - просто прелесть, Элен...");
				link.l1.go = "cabin_sex_go";
			}
		break;
		
		
		case "cabin_sex_go":
			DialogExit();
			npchar.quest.daily_sex_cabin = true; // для первого раза в каюте перед счетчиком. лесник
			npchar.quest.daily_sex_room = true; // для первого раза в таверне чтобы счетчик запустить . лесник
			chrDisableReloadToLocation = true;//закрыть локацию
			DoQuestCheckDelay("Helena_LoveSex", 1.0);
			NextDiag.CurrentNode = "sex_after";
		break;
		
		case "sex_after":
			dialog.text = RandPhraseSimple("Всё было отлично, "+pchar.name+"!..","Ты как всегда на высоте, дорогой...");
			link.l1 = RandPhraseSimple("Я рад, что ты осталась довольна...","Мне с тобой очень хорошо, Элен...");
			//DeleteAttribute(npchar, "sex_go");
			link.l1.go = "exit";
			NextDiag.TempNode = "Helena_officer";
			chrDisableReloadToLocation = false;//открыть локаци.
			//SetFunctionTimerCondition("Helena_SexReady", 0, 0, 1, false); // лесник . уже не надо.
			SaveCurrentNpcQuestDateParam(npchar, "sex_go"); // вот тут теперь сохраняются параметры времени . 
		break;
		
		case "room_sex":
			if (CheckAttribute(pchar, "questTemp.Terrapin") && pchar.questTemp.Terrapin == "tavern")
			{
				dialog.text = ""+pchar.name+", я всегда этому рада... Но сейчас немного не время - нужно отловить этого прохвоста Тибо, пока он не скрылся где-нибудь.";
				link.l1 = "Ты как всегда права, моя девочка...";
				link.l1.go = "exit";
				break;
			}
			if (drand(4) == 0) // вероятность отказа 20%
			{
				dialog.text = RandPhraseSimple(""+pchar.name+", я себя что-то совсем неважно чувствую. Не обижайся, пожалуйста. Давай не сегодня...",""+pchar.name+", дорогой, я так устала за последние несколько дней. Честно говоря, мне хочется просто поспать. Не обижайся. Давай в другой раз.");
				link.l1 = RandPhraseSimple("Ну хорошо...","Не обижаюсь. Как скажешь...");
				SaveCurrentNpcQuestDateParam(npchar, "sex_go"); // лесник - если отказала , сохраним . чтоб не приставал по 100 раз.
				npchar.quest.daily_sex_room = true; // сли первый раз в таверне отказала. лесник
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = RandPhraseSimple(""+pchar.name+", я с радостью поддержу твоё предложение! Идём!",""+pchar.name+", ну конечно же не возражаю! Идём!");
				link.l1 = RandPhraseSimple("Ты моя умничка...","Ты - просто прелесть, Элен...");
				link.l1.go = "room_sex_go";
			}
		break;
		
		case "room_sex_go":
			DialogExit();
			npchar.quest.daily_sex_room = true; // для первого раза в таверне чтобы счетчик запустить . лесник
			npchar.quest.daily_sex_cabin = true;
			if (sti(pchar.money) >= 10) AddMoneyToCharacter(pchar, -10);
			chrDisableReloadToLocation = true;//закрыть локацию // лесник - добавил закрцтие локи в таверне, чтоб поговорил после траханья с ней.
			DoQuestReloadToLocation(pchar.location+"_upstairs", "quest", "quest4", "");
			ChangeCharacterAddressGroup(npchar, pchar.location+"_upstairs", "quest", "quest3");
			DoQuestCheckDelay("Helena_LoveSex", 2.5); // mitrokosta fix
			NextDiag.CurrentNode = "sex_after";
		break;
		
		//--> ----------------------------------- офицерский блок ------------------------------------------
		case "Helena_officer":
			ref rLoc = &Locations[FindLocation(pchar.location)];
			dialog.text = LinkRandPhrase("Да, "+pchar.name+"?","Да, мой капитан?","Слушаю тебя, "+pchar.name+"...");
			if (CheckAttribute(pchar, "questTemp.Dolly_Tieyasal") && !CheckAttribute(npchar, "quest.Tieyasal"))
			{
				Link.l4 = "Элен, я собираюсь отправиться в старый индейский город Тайясаль. Не буду скрывать: это крайне опасное путешествие, и более того - необычное: через телепортационный истукан. Ты... пойдёшь со мной?";
				Link.l4.go = "tieyasal";
			}
       ////////////////////////казначей///////////////////////////////////////////////////////////
           		// boal отчёт о корабле
			if(CheckAttribute(NPChar, "treasurer") && NPChar.treasurer == 1)
			{
			    Link.l11 = "Элен, дай мне полный отчёт о корабле.";
			    Link.l11.go = "QMASTER_1";
			        
			    // Warship. Автозакупка товара
				Link.l12 = "Я хочу, чтобы во время стоянки в колонии ты закупала товары.";
				Link.l12.go = "QMASTER_2";
			}
			
            /////////////////////////////////////казначей////////////////////////////////////////////////////////////     			
			if (CheckAttribute(NPChar, "IsCompanionClone"))//////////////////компаньон//////////////////////////////////////////////
			{
				//dialog.text = "Я прибыл по вашему распоряжению, капитан.";
				Link.l2 = "Элен, у меня есть для тебя несколько распоряжений.";
				Link.l2.go = "Companion_Tasks";
				NextDiag.TempNode = "Helena_officer";// не забыть менять в зависисомости от оффа
				break;
			}																															
			if (CheckAttribute(npchar, "quest.fugas"))
			{
				Link.l3 = "Элен, я хочу с тобой посоветоваться.";
				Link.l3.go = "fugas";
			}
			Link.l1 = "Элен, у меня для тебя есть распоряжение...";
            Link.l1.go = "stay_follow";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && pchar.location == Get_My_Cabin() && GetNpcQuestPastDayParam(npchar, "sex_go") >= 1 || !CheckAttribute(npchar, "quest.daily_sex_cabin") && pchar.location == Get_My_Cabin()) // лесник - ждем 1 день и снова трах предлагать можно.
			{
				Link.l2 = RandPhraseSimple("Элен, может, останемся в каюте вдвоём... на ближайшие пару часов? Ты не против?","Дорогая, может, проведём следующие несколько часов тет-а-тет? Ты не против?");
				Link.l2.go = "cabin_sex";
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && rLoc.type == "tavern" && sti(pchar.money) >= 10 && GetNpcQuestPastDayParam(npchar, "sex_go") >= 1 || !CheckAttribute(npchar, "quest.daily_sex_room") && rLoc.type == "tavern")//  лесник - так же ждем 1 день и снова предлогать можно.
			{
				Link.l2 = RandPhraseSimple("Элен, может, снимем комнату и останемся там вдвоём... на ближайшие пару часов? Ты не против?","Дорогая, может, проведём следующие несколько часов тет-а-тет? Снимем комнату... Ты не против?");
				Link.l2.go = "room_sex";
			}
			link.l9 = "Пока ничего, Элен.";
			NPChar.id = "Helena"; // лесник . Идентификация Элен на всяк. случай . если потеряет сознание.
			link.l9.go = "exit";
			NextDiag.TempNode = "Helena_officer";
		break;
		
	/////////////////////////// ответы для казнаячея - Элен ..(элен казначей - ужас!))///////////////////////////////////
        case "QMASTER_1":
			dialog.Text = "Шарль, дорогой, ты ничего не перепутал? Ты думаешь, что я сейчас пойду и буду считать крыс в трюме?";
			Link.l1 = "О, милая, конечно, извини, я как-то не подумал...";
			Link.l1.go = "exit";
		break;	

		case "QMASTER_2":
			dialog.text = "А я хочу себе фрегат с сотней-другой орудий и скоростью в двадцать узлов. Шарль, я вообще-то капитаном всю жизнь была, как и ты. Найми себе купца для этого дела.";
			link.l1 = "Да, дорогая, наверное, ты права. Извини меня.";
			Link.l1.go = "exit";
        break;			
		//Указания для компаньона 19.02.08 -->/////////////////////////////////////////////////////////////////////////////////////////
		case "Companion_Tasks":
			dialog.Text = "Внимательно слушаю.";
			Link.l1 = "Это касается абордажа.";
			Link.l1.go = "Companion_TaskBoarding";
			Link.l2 = "Это касается твоего корабля.";
			Link.l2.go = "Companion_TaskChange";
			Link.l8 = "Пока ничего.";
			Link.l8.go = "exit";
			 
		break;
		
		case "Companion_TaskBoarding":
			dialog.Text = "Что желает мой капитан?";
			Link.l1 = "Я хочу чтобы ты не брала корабли на абордаж. Побереги себя и свою команду.";
			Link.l1.go = "Companion_TaskBoardingNo";
			Link.l2 = "Мне нужно чтобы ты брала вражеские корабли на абордаж.";
			Link.l2.go = "Companion_TaskBoardingYes";
		break;
		
		case "Companion_TaskChange":
			dialog.Text = "Что желает мой капитан?";
			Link.l1 = "Я хочу чтобы ты не меняла свой корабль после абордажа. Он слишком ценен.";
			Link.l1.go = "Companion_TaskChangeNo";
			Link.l2 = "Когда будешь брать врагов на абордаж, посмотри, вдруг кораблик приличный будет, тогда бери себе.";
			Link.l2.go = "Companion_TaskChangeYes";
		break;
		
		case "Companion_TaskBoardingNo":
			dialog.Text = "Ладно, я подумаю.";
			Link.l1 = "Подумает она... Да уж, тебе приказов не отдашь.";
			Link.l1.go = "exit";
			NPChar.Tasks.CanBoarding = false;
		break;
		
		case "Companion_TaskBoardingYes":
			dialog.Text = "Ладно, я подумаю.";
			Link.l1 = "Подумает она... Да уж, тебе приказов не отдашь.";
			Link.l1.go = "exit";
			NPChar.Tasks.CanBoarding = true;
		break;
		
		case "Companion_TaskChangeNo":
			dialog.Text = "Ладно, я подумаю.";
			Link.l1 = "Подумает она... Да уж, тебе приказов не отдашь.";
			Link.l1.go = "exit";
			NPChar.Tasks.CanChangeShipAfterBoarding = false;
		break;
		
		case "Companion_TaskChangeYes":
			dialog.Text = "Ладно, я подумаю.";
			Link.l1 = "Подумает она... Да уж, тебе приказов не отдашь.";
			Link.l1.go = "exit";
			NPChar.Tasks.CanChangeShipAfterBoarding = true;
		break;
	//	<========//////////////////////////////////////																																			  
		
		case "stay_follow":
            dialog.Text = "Какие будут приказания?";
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
            dialog.Text = "Будет сделано, капитан!";
            Link.l1 = "...";
            Link.l1.go = "Exit";
            Npchar.chr_ai.tmpl = LAI_TMPL_STAY;
        break;
        
        case "Boal_Follow":
            SetCharacterTask_FollowCharacter(Npchar, PChar);
            dialog.Text = "Будет сделано, капитан!";
            Link.l1 = "...";
            Link.l1.go = "Exit";
        break;
		//<-- ----------------------------------- офицерский блок ----------------------------------------
		
		// --> суп из черепахи
		case "terrapin_grot":
			dialog.text = "Вот ты где спрятался! Насилу тебя нашла... Ну ты дал жару, мой капитан! Такого забега по крышам и прыжка с головокружительной высоты мне ещё не доводилось видеть! У меня чуть сердце не выпрыгнуло из груди! Ты однажды доведёшь меня своими выходками до удара, дорогой... О, так ты тут не один? Кто эта девушка?";
			link.l1 = "Это Кэтрин Фокс, дочь полковника Фокса, командира 'морских лис'. Мы отвезём её на Антигуа.";
			link.l1.go = "terrapin_grot_1";
		break;
		
		case "terrapin_grot_1":
			dialog.text = "Как интересно! Добро пожаловать на борт, мисс Фокс... А теперь быстрее грузимся в шлюпку - надо убираться отсюда.";
			link.l1 = "Ты умничка, Элен! И что бы я без тебя делал?.. Кэтрин, следуй за мной!";
			link.l1.go = "terrapin_grot_2";
		break;
		
		case "terrapin_grot_2":
			DialogExit();
			npchar.dialog.currentnode = "Helena_officer";
			LAi_SetOfficerType(npchar);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			Terrapin_GotoShip();
		break;
		// <-- суп из черепахи
		
		// --> калеуче
		case "on_coast":
			dialog.text = "Ну наконец-то ты очнулся, мой дорогой... Как ты себя чувствуешь? Ты очень напугал меня.";
			link.l1 = "Элен... Милая, что произошло? Аргх, голова раскалывается...";
			link.l1.go = "on_coast_1";
		break;
		
		case "on_coast_1":
			dialog.text = "Когда мы зашли в капитанскую каюту, ты лежал на полу без движения. У меня чуть сердце не остановилось! Ребята подхватили тебя и потащили на наш корабль, и вовремя, потому что эти ужасные скелеты, что валялись на палубе, начали подниматься и снова взялись за сабли\nЭто просто кошмар! Их нельзя одолеть! Мы быстро обрубили лини и отчалили от их корабля, но далеко уйти не успели: негодяи всадили в нас залп бортовой батареи, и наше судно в один миг превратилось в щепки. А затем они подняли паруса и в мгновение ока скрылись за горизонтом\nКорабль наш затонул, а все, кто выжил, добрались на лодке до берега. Я смогла прихватить твой капитанский рундук из каюты с твоими вещами. Там ведь много чего важного, я знаю.";
			link.l1 = "Ты умничка, Элен... Что бы я без тебя делал?";
			link.l1.go = "on_coast_2";
		break;
		
		case "on_coast_2":
			dialog.text = "Я вытащила тебя в лодку, а потом и на берег. А ты был словно мёртвый, только сердце едва билось. У меня до сих пор руки дрожат...";
			link.l1 = "Спасибо, моя милая. Я в долгу перед тобой. Сколько я здесь валялся без сознания?";
			link.l1.go = "on_coast_3";
		break;
		
		case "on_coast_3":
			dialog.text = "Сутки. Я промыла и перевязала тебе раны, влила в рот лекарства и ром. Ты просто обязан теперь выздороветь!";
			link.l1 = "Обещаю, что не умру, моя дорогая. Хотя чувствую себя на редкость паршиво...";
			link.l1.go = "on_coast_4";
		break;
		
		case "on_coast_4":
			dialog.text = "Не сомневаюсь... Это был 'Летучий Голландец', да? Почему они на нас напали? И почему сразу не сделали ни одного выстрела, а после абордажа потопили одним залпом?";
			link.l1 = "Их капитану нужен был амулет, по поводу которого я ходил к Туттуатхапаку, индейскому шаману. Поэтому они и не потопили нас сразу. А как только главный мертвец забрал амулет, они и расправились с нами... Жуть какая! Корабль с командой живых мертвецов! Поверить невозможно...";
			link.l1.go = "on_coast_5";
		break;
		
		case "on_coast_5":
			dialog.text = "Вот мы и повстречались с 'Летучим Голландцем'. В первой же колонии я пойду в церковь,  поставлю свечу из чистого воска за наше спасение, и буду молиться...";
			link.l1 = "Знаешь, Элен, я, пожалуй, тоже. Но сейчас мы пойдём назад в деревню карибов. Я должен всё рассказать Туттуатхапаку. Этот проклятый корабль напал на нас из-за амулета! Надеюсь, краснокожий дьявол сможет объяснить мне, зачем он понадобился мертвецам.";
			link.l1.go = "on_coast_6";
		break;
		
		case "on_coast_6":
			dialog.text = "Хорошо. Но тебе нужно беречь себя - твои раны до сих пор сочатся кровью.";
			link.l1 = "Но ты же поможешь мне исцелиться, моя девочка? И, Элен: я люблю тебя...";
			link.l1.go = "on_coast_7";
		break;
		
		case "on_coast_7":
			chrDisableReloadToLocation = false;//открыть локацию
			dialog.text = "Я тебя тоже, дорогой...";
			link.l1 = "...";
			link.l1.go = "on_coast_8";
		break;
		
		case "on_coast_8":
			DialogExit();
			npchar.dialog.currentnode = "Helena_officer";
			LAi_SetOfficerType(npchar);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			AddQuestRecord("Caleuche", "5");
		break;
		// <-- калеуче
		
		// на Тайясаль
		case "tieyasal":
			dialog.text = ""+pchar.name+", я как-то сказала тебе, что наши судьбы теперь едины. Твоя судьба - моя судьба. Когда мы отправляемся?";
			link.l1 = "Значит, ты согласна, моя умничка... Я очень рад. А когда выдвигаться - я скажу немного позже. Пока нам нужно подготовиться.";
			link.l1.go = "tieyasal_1";
		break;
		
		case "tieyasal_1":
			dialog.text = "Я готова в любой момент, мой капитан! С тобой - хоть на край света!";
			link.l1 = "Спасибо, любимая...";
			link.l1.go = "tieyasal_2";
		break;
		
		case "tieyasal_2":
			DialogExit();
			AddQuestRecord("Tieyasal", "20");
			npchar.quest.Tieyasal = "teleport";
		break;
		
		// на Исла Тесоро
		case "islatesoro":
			dialog.text = "О, "+pchar.name+"! Рада тебя видеть! Какими судьбами на Исла Тесоро?";
			link.l1 = "Да всё как обычно - по делам. И, конечно, не забыл тебя проведать, Элен...";
			link.l1.go = "islatesoro_1";
		break;
		
		case "islatesoro_1":
			DialogExit();
			NextDiag.CurrentNode = "islatesoro";
		break;
		
		// Jason Дороже золота
		case "GoldenGirl":
			dialog.text = "Ну, капитан, что там припекло в этот раз нашему дражайшему губернатору? С кем дерёмся? Испанцы, пираты, или что похуже?";
			link.l1 = "Хуже, Элен, хуже. Губернатор намерен посетить крайне дорогую куртизанку, а я при нём в качестве диковинки, обещанной хозяйке. Скучная болтовня, дорогое вино и унылые аристократы.";
			link.l1.go = "GoldenGirl_1";
			link.l2 = "Ровно наоборот - необременительный приём у дамы из высшего общества. Его светлость настоятельно просит его сопровождать, совершенно неожиданно, но я рад случаю немного отдохнуть от всей этой беготни.";
			link.l2.go = "GoldenGirl_5";
		break;
		
		case "GoldenGirl_1":
			dialog.text = "Отлично, и ты как ручная обезьянка будешь прыгать на потеху вельможных бестолочей? Очень мило! Может, ну его к дьяволу? Пополним запасы и поднимем паруса? Если хочешь отдохнуть - на Исла Тесоро '"+pchar.ship.name+"' всегда желанный гость. Развеемся, поваляемся на солнышке, проведаем старых друзей.";
			link.l1 = "Послушай, это всё прекрасно звучит, и я с радостью так и сделаю, но потом. Я обещал губернатору, для старика это важно, и вообще...";
			link.l1.go = "GoldenGirl_2";
		break;
		
		case "GoldenGirl_2":
			dialog.text = "Вообще что? Ты думаешь, твоя голубая кровь для них что-то значит? Я знаю, что такое 'высшее общество': для них Шарль де Мор не капитан, которому доверяют жизнь и за которым идут в огонь. Не равный вельможа - равные сидят в кресле в канцелярии, а не скачут по вантам в пороховом дыму. Даже не человек! Он просто... необычная приправа к ужину или беседе. Знаешь, как комнатный леопард, или заморский уродец с двумя головами! Занятная безделушка, пока не надоест! С каких пор ты готов быть безделушкой?!";
			link.l1 = "Элен, не беспокойся, я способен выдержать несколько любопытных взглядов, чтобы уважить губернатора. Это проще чем идти на абордаж под картечью. Уверен, я справлюсь. И эти самые 'бестолочи' не всегда такие. Даже в высшем обществе есть достойные люди... ну, или должны быть.";
			link.l1.go = "GoldenGirl_3";
		break;
		
		case "GoldenGirl_3":
			dialog.text = "Хорошо. Но учти - ради этих 'достойных' я в платье не полезу - хотят, пусть падают в обморок или возмущённо шепчутся под веерами, мне плевать.";
			link.l1 = "Я и не собирался тебя заставлять. Не вижу смысла страдать всем вместе. Я переживу этот приём, а потом махнем на Исла Тесоро. Я помню в трюме был ящик отличной испанской мадеры...";
			link.l1.go = "GoldenGirl_4";
		break;
		
		case "GoldenGirl_4":
			dialog.text = "То есть я для такой компании не подхожу, это ты хочешь сказать? Когда обезьянка приводит с собой ещё одну, это уже перебор? Интересно. Хорошо, не забудьте одеться поприличнее, капитан. Когда на обезьянке воротник и манжеты, это приводит в умиление даже куртизанок. Удачного выступления!";
			link.l1 = "Элен, постой! Проклятье...";
			link.l1.go = "GoldenGirl_8";
		break;
		
		case "GoldenGirl_5":
			dialog.text = "Да, мы заслужили отдых, согласна. Но будь я проклята, если полезу в платье ради этого приёма. Как думаешь, долго потом будут сплетничать о твоей спутнице, заявившейся в мужской рубахе и матросских штанах, в высших кругах Сен-Пьера?";
			link.l1 = "Не думаю, что это хорошая идея. Эта маркиза из тех, на приёмы к которым мужчины своих дам не берут. Уважаемых дам.";
			link.l1.go = "GoldenGirl_6";
		break;
		
		case "GoldenGirl_6":
			dialog.text = "Отлично - куртизанки и великосветский разврат! Мог бы и сразу сказать. Я же не ревнивая идиотка, стрелять в тебя не буду. Во всяком случае, не сразу.";
			link.l1 = "Элен, я просто буду сопровождать губернатора, по его же настоятельной просьбе. Никаких... куртизанок. Ну то есть, они там будут, но... Проклятье! Да это просто визит вежливости!";
			link.l1.go = "GoldenGirl_7";
		break;
		
		case "GoldenGirl_7":
			dialog.text = "Рекомендую тогда одеться поприличнее, капитан. Высшее общество, дело такое. С человеком без воротника и манжет не станут разговаривать даже из вежливости. Даже куртизанки. Удачного... визита.";
			link.l1 = "Элен, постой! Проклятье...";
			link.l1.go = "GoldenGirl_9";
		break;
		
		case "GoldenGirl_8":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "GoldenGirl_GirlExit", 15.0);
			pchar.questTemp.GoldenGirl.Angry1 = "true";
		break;
		
		case "GoldenGirl_9":
			DialogExit();
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "GoldenGirl_GirlExit", 15.0);
			pchar.questTemp.GoldenGirl.Angry2 = "true";
		break;
		
		case "GoldenGirl_10":
			dialog.text = "Воротник и манжеты, капитан. Возможно - кружева, они сейчас снова в моде.";
			link.l1 = "Элен, ну сколько можно?!";
			link.l1.go = "GoldenGirl_11";
		break;
		
		case "GoldenGirl_11":
			DialogExit();
			NextDiag.CurrentNode = "GoldenGirl_10";
		break;
		
		case "GoldenGirl_12":
			dialog.text = "Смотрите-ка, кого мы нашли! Наш бесследно пропавший в высшем обществе капитан!";
			link.l1 = "...";
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.Angry1")) link.l1.go = "GoldenGirl_13";
			else link.l1.go = "GoldenGirl_18";
		break;
		
		case "GoldenGirl_13":
			dialog.text = "Ну, и как местным вельможам новая обезьянка? В городе болтают, что её выступление произвело настоящий фурор! Играть в карты на корабли и куртизанок, а потом бросить вызов какому то вельможному мерзавцу? Может объяснишь, что это за чертовщина?";
			link.l1 = "Элен, всё немного сложнее. Проклятье, прости меня, я не думал, что задержусь настолько, пришлось заночевать в доме мадам Бото. Одному, клянусь! И да, я выиграл в карты отменный фрегат. Представляешь?";
			link.l1.go = "GoldenGirl_14";
		break;
		
		case "GoldenGirl_14":
			dialog.text = "Отлично! Я начинаю думать, что ты либо святой, либо дурак. Но выигранных куртизанок и корабли обсудим позже - сейчас рассказывай что за дуэль и почему все говорят об этом так, словно ты дерёшься по меньшей мере с наследным принцем?";
			link.l1 = "Этот человек - бастард крайне могущественного вельможи, графа де Леви Вантадура. Он сам бросил мне вызов, и теперь придётся постараться не умереть самому, и не убить его, дабы не разгневать его отца.";
			link.l1.go = "GoldenGirl_15";
		break;
		
		case "GoldenGirl_15":
			dialog.text = "Проклятье! И как мы это сделаем? А если он задумает что-то бесчестное? Мы ведь не раз такое видели!";
			link.l1 = "Вот поэтому его светлость дал мне секундантов из благородных офицеров гарнизона. Больше я никого с собой не возьму - если дойдёт до разбирательств и суда, не должно быть никаких сомнений, что всё было по кодексу и по закону. А тебя прошу, присмотри за фрегатом, пока меня не будет.";
			link.l1.go = "GoldenGirl_16";
		break;
		
		case "GoldenGirl_16":
			dialog.text = "Давай-ка уточним, правильно ли я поняла. Ты пропал почти на сутки, выиграл в карты баснословно дорогую... даму. Теперь идёшь драться из-за неё с могущественным благородным выродком, которого даже нельзя убивать, а я... мы все, должны сидеть на заднице и ждать, чем всё закончится? Интересно, что я должна думать по этому поводу? Как считаешь?";
			link.l1 = "Элен, послушай, ты имеешь право злиться, и мне очень жаль, но всё не так просто...";
			link.l1.go = "GoldenGirl_17";
		break;
		
		case "GoldenGirl_17":
			dialog.text = "Знаешь что, хватит. Иди и делай то, что считаешь нужным. Мне здесь, судя по всему, места нет, но об этом мы поговорим, когда всё закончится. А я, пока, пойду и попытаюсь это как следует запить. За твоим новым фрегатом я присмотрю, не беспокойся. И капитан, постарайся выжить... чтоб я сама могла тебя прибить.";
			link.l1 = "Элен, да позволь мне всё объяснить, наконец! Проклятье... Опять?!";
			link.l1.go = "GoldenGirl_23";
		break;
		
		case "GoldenGirl_18":
			dialog.text = "Говорят, в городе теперь новая мода - корабли и куртизанок надо выигрывать в карты, а не покупать! Причём, бывших владельцев, чтобы быть до конца утончённым, следует вызывать на дуэль. Во что ты, чёрт возьми вляпался на этот раз?";
			link.l1 = "Элен, всё немного сложнее. Проклятье, прости меня, я не думал что задержусь настолько. Этот вечер превратился в форменное сражение за карточными столами. И да, я выиграл в карты отменный фрегат. Представляешь?";
			link.l1.go = "GoldenGirl_19";
		break;
		
		case "GoldenGirl_19":
			dialog.text = "Отлично, значит и куртизанку ты действительно выиграл? А этот фрегат, что ты ставил? Неужели наш...";
			link.l1 = "Мне пришлось. Долго объяснять, но я выиграл. А теперь - мой соперник, обвинил меня в мошенничестве и вызвал на дуэль. Он бастард крайне могущественного вельможи, графа де Леви Вантадура, и мне придётся изо всех сил постараться, чтобы не убить его на дуэли.";
			link.l1.go = "GoldenGirl_20";
		break;
		
		case "GoldenGirl_20":
			dialog.text = "А он тоже будет стараться не убить тебя? Ты совсем рехнулся, капитан? Рисковать всем кораблём, а теперь и своей жизнью из-за какой-то... мадам? Она действительно того стоит?";
			link.l1 = "Элен, для ревности нет повода, клянусь. Просто так сложилось. Я должен это сделать, и губернатор назначил мне секундантов из числа благородных офицеров, чтобы исключить любые сомнения после дуэли. Я не могу взять ни тебя ни кого-то из ребят. Прошу, присмотри за фрегатом, пока меня не будет.";
			link.l1.go = "GoldenGirl_21";
		break;
		
		case "GoldenGirl_21":
			dialog.text = "Просто чудесно! Ты отправляешься к куртизанкам - заметь, я тебе даже в спину не выстрелила - пропадаешь неизвестно куда почти на сутки. Возвращаешься с известием, что только чудом не проиграл корабль, зато выиграл эту самую куртизанку. И теперь из-за неё будешь драться с вельможным засранцем, которого даже убивать нельзя? Интересно, что я должна думать по этому поводу? Как считаешь?";
			link.l1 = "Элен, послушай, ты имеешь право злиться, но всё не так просто...";
			link.l1.go = "GoldenGirl_22";
		break;
		
		case "GoldenGirl_22":
			dialog.text = "Знаешь что, хватит. Иди и делай то, что считаешь нужным. Мне здесь, судя по всему, места нет, но об этом мы поговорим, когда всё закончится. А я, пока, пойду и попытаюсь это как следует запить. За твоим новым фрегатом я присмотрю, не беспокойся. Но если с тобой хоть что-то случится - клянусь Богом, я направлю пушки на город и сровняю с землёй и этот бордель и особняк нашей разлюбезной светлости.";
			link.l1 = "Элен, всё будет хорошо, поверь мне. Постой, ну куда ты?! Проклятье... Опять?!";
			link.l1.go = "GoldenGirl_23";
		break;
		
		case "GoldenGirl_23":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "GoldenGirl_GirlToFregat", 15.0);
		break;
		
		case "GoldenGirl_24":
			dialog.text = "Шарль, а теперь будь добр, объясни мне: что за чертовщина тут вообще творилась? На корабль среди ночи ворвались какие-то головорезы. Потом этот немытый хмырь, гнусно хихикая, спрашивал меня, на что ты пойдёшь, чтобы меня вернуть. А затем меня заперли в кубрике, и я потеряла счёт дням!";
			link.l1 = "Мерзавец решил посчитаться со мной за свой позор. Больше всего я боялся, что он что-нибудь с тобой сделает! Но, слава Богу, ты в порядке!";
			link.l1.go = "GoldenGirl_25";
		break;
		
		case "GoldenGirl_25":
			dialog.text = "Я так понимаю, тебе пришлось что-то сделать ради этого? Что-то плохое, ведь так?";
			link.l1 = "Главное - ты теперь снова со мной. Я так виноват перед тобой, Элен, за всю эту историю! Не знаю, сможешь ли ты меня простить!";
			link.l1.go = "GoldenGirl_26";
		break;
		
		case "GoldenGirl_26":
			dialog.text = "Уже. И ты прости меня, Шарль. Если бы я не приняла всё так близко к сердцу с этой дуэлью и маркизой, и хотя бы расставила вахту на фрегате... Глупо всё вышло!";
			link.l1 = "Всё вышло как вышло, и это уже в прошлом. Ты вернулась ко мне, и это всё, о чём я смел мечтать последние недели. Я многое понял за это время, Элен. Очень многое. Я люблю тебя, и больше никогда не оставлю. Обещаю!";
			link.l1.go = "GoldenGirl_27";
		break;
		
		case "GoldenGirl_27":
			dialog.text = "Полагаю, мне лучше не знать что именно ты сделал, так? Ладно, мы снова вместе и это, главное.";
			link.l1 = "У меня нет от тебя секретов. Я расскажу тебе...";
			link.l1.go = "GoldenGirl_28";
		break;
		
		case "GoldenGirl_28":
			DialogExit();
			SetLaunchFrameFormParam("Прошло немного времени...", "", 0.1, 3.0);
			LaunchFrameForm();
			WaitDate("", 0, 0, 0, 1, 0);
			npchar.dialog.currentnode = "GoldenGirl_28_1";
			LAi_SetActorType(npchar);
			LAi_ActorDialogDelay(npchar, pchar, "", 4.0);
		break;
		
		case "GoldenGirl_28_1":
			if (pchar.questTemp.GoldenGirl == "alarm_fin")
			{
				dialog.text = "Ну и история вышла... Я верю, что у тебя не было иного выбора, но как мы объясним всё Дил ду Парке и прочим? Ты же фактически поставил себя вне закона?";
				link.l1 = "Я согласился с этой ценой. И да - выбора действительно не было. Не беспокойся - я найду способ восстановить своё доброе имя. А нет - так на Исла Тессоро нам всегда рады! Если ты со мной - остальное неважно.";
			}
			else
			{
				dialog.text = "Ну и история вышла... Я верю, что у тебя не было иного выбора, но что теперь будет? Этот британец действительно всё уладит, или будем воевать? Не хочешь отправится в Бас-Тер и лично полюбоваться как на заносчивого мерзавца оденут цепи?";
				link.l1 = "Знаешь, Элен, пару недель назад я бы ни за что не упустил такой шанс. Но теперь - пусть бастард отправляется к чёрту! Мне даже плевать поймают его или нет - это всё больше не моя проблема. Мы снова вместе - вот что по настоящему важно!";
			}
			link.l1.go = "GoldenGirl_29";
		break;
		
		case "GoldenGirl_29":
			if (pchar.questTemp.GoldenGirl == "alarm_fin")
			{
				dialog.text = "Я всегда с тобой, ты же знаешь. А вместе мы и не из таких передряг выпутывались. Не впервой.";
				link.l1 = "Точно. Ну, милая, поднимаем паруса! Жизнь продолжается!";
			}
			else
			{
				dialog.text = "Мне нравится такой подход, Шарль! Французы, британцы, испанцы - пусть сами разбираются. Думаю - мы действительно заслужили немного покоя!";
				link.l1 = "Согласен. Только ты, я и никаких губернаторов и высокородных интриганов!";
			}
			link.l1.go = "GoldenGirl_30";
		break;
		
		case "GoldenGirl_30":
			if (pchar.questTemp.GoldenGirl == "alarm_fin")
			{
				dialog.text = "Так точно, капитан!";
				link.l1 = "";
			}
			else
			{
				dialog.text = "Звучит отлично! Пойду отдам ребятам команду сниматься с якоря! И, Шарль, ты же знаешь...";
				link.l1 = "Да, Элен, я знаю. Поднимайся на палубу, я сейчас буду.";
			}
			link.l1.go = "GoldenGirl_31";
		break;
		
		case "GoldenGirl_31":
			DialogExit();
			npchar.dialog.currentnode = "Helena_officer";
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "sea", "none", "", "", "GoldenGirl_GirlGoOnBoard", 10.0);
		break;
		
		case "GoldenGirl_32":
			dialog.text = "Шарль, ты жив! У тебя получилось!! Португалец мне всё рассказал! Ну и история вышла!";
			link.l1 = "Слава Богу, ты жива, Элен. Ты не представляешь, как я рад тебя видеть!";
			link.l1.go = "GoldenGirl_33";
		break;
		
		case "GoldenGirl_33":
			dialog.text = "Кстати, об этом. Ты всё мне обещал что-то рассказать? Что-то важное и сложное. Это твой шанс, капитан, я жду. Что, чёрт возьми, за безумие тут вообще произошло?!";
			link.l1 = "Я... я люблю тебя Элен. А всё остальное - неважно.";
			link.l1.go = "GoldenGirl_34";
		break;
		
		case "GoldenGirl_34":
			dialog.text = "Ну да, это многое объясняет, но... Чёрт, я тоже, Шарль. Я тоже тебя люблю. Боже, как я скучала!";
			link.l1 = "И я скучал. Пойдём, сегодня я тебя не оставлю, даже если небо начнёт рушиться на этот город, будь он неладен. Я тебя вообще больше не оставлю. Никогда.";
			link.l1.go = "GoldenGirl_35";
		break;
		
		case "GoldenGirl_35":
			dialog.text = "Полагаю, мне лучше не знать что именно ты сделал, так? Ладно, мы снова вместе и это, главное.";
			link.l1 = "У меня нет от тебя сектретов. Я расскажу тебе...";
			link.l1.go = "GoldenGirl_36";
		break;
		
		case "GoldenGirl_36":
			DialogExit();
			SetLaunchFrameFormParam("Прошло немного времени...", "", 0.1, 3.0);
			LaunchFrameForm();
			WaitDate("", 0, 0, 0, 1, 0);
			npchar.dialog.currentnode = "GoldenGirl_36_1";
			LAi_SetActorType(npchar);
			LAi_ActorDialogDelay(npchar, pchar, "", 4.0);
		break;
		
		case "GoldenGirl_36_1":
			dialog.text = "Невероятно! То есть Франция сейчас на пороге войны с Англией из-за меня?";
			link.l1 = "Нет, Элен, из-за моей глупости. Я должен был тебя вернуть и всё исправить.";
			link.l1.go = "GoldenGirl_37";
		break;
		
		case "GoldenGirl_37":
			dialog.text = "Очень романтично, я даже готова забыть о том, с чего всё началось... Ну, почти готова. Ладно, чёрт с ним! Так тебя подозревали, потому что Португалец сказал тебе неверное название этой клятой бригантины?";
			link.l1 = "Наоборот, верное! И я бы дорого дал, чтобы узнать, как он об этом пронюхал, и почему вообще... Кстати, а где он сам?!";
			link.l1.go = "GoldenGirl_38";
		break;
		
		case "GoldenGirl_38":
			dialog.text = "Отплыл. Почти сразу, как доставил меня сюда. Гостеприимством твоей выигранной куртизанки я не воспользовалась, и Бартоломью снял мне комнату тут, оплатив её на пару недель, и исчез, даже не попрощавшись. Ой нет, погоди - он же оставил письмо!";
			link.l1 = "Письмо? Бартоломью Португалец? Это что-то новенькое. Меня терзают смутные сомнения...";
			link.l1.go = "GoldenGirl_39";
		break;
		
		case "GoldenGirl_39":
			dialog.text = "Ладно, ты читай, а я побегу - покажусь нашим, а то мы ещё сутки тут просидим, а они же тоже волнуются. Не думала, что буду скучать по этим вечно хмурым рожам! А ты постарайся не влипнуть в очередное безобразие!";
			link.l1 = "Я бы и неделю так просидел... Проклятье, я всё таки тебя вернул! Поверить не могу!";
			link.l1.go = "GoldenGirl_40";
		break;
		
		case "GoldenGirl_40":
			DialogExit();
			npchar.dialog.currentnode = "Helena_officer";
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "GoldenGirl_SPGirlReturn", 10.0);
		break;
		
		// Jason Долго и счастливо
		case "LongHappy":
			RemoveItems(pchar, "potionwine", 2);
			dialog.text = "Прибой и ветер, ты и я, хорошее вино - стоило бы почаще вот так выбираться, а Шарль?";
			link.l1 = "Рад, что тебе нравится. Думаю, у нас теперь будет больше времени на это и вообще друг на друга.";
			link.l1.go = "LongHappy_1";
		break;
		
		case "LongHappy_1":
			dialog.text = "Шарль, что ты задумал, и почему ты на коленях? Это же не...";
			link.l1 = "Элен, я люблю тебя. И я хочу прожить с тобой каждый день, отпущенный мне свыше. Потому, здесь и сейчас, перед этим морем и небом, я прошу тебя: Элен Беатрисс Шарп, окажи мне честь быть со мной, перед людьми и Богом, пока смерть не разлучит нас. Я, Шарль де Мор, шевалье де Монпе, спрашиваю тебя - ты станешь моей женой?";
			link.l1.go = "LongHappy_2";
		break;
		
		case "LongHappy_2":
			if (pchar.location == "Shore_ship1")
			{
				dialog.text = "Ты знаешь, мне эти формальности никогда не нравились, но с тобой я хоть на край света. А что до твоего вопроса, ответим так... ой, прости!";
				link.l1 = "Ничего, это всего лишь вино, и я никогда не любил эту рубаху...";
				link.l1.go = "LongHappy_3";
			}
			else
			{
				dialog.text = "Конечно да! Шарль, Да, да, и ещё раз да! Но... мы же не отправимся в пыльный фамильный замок выращивать репу, до конца дней своих?";
				link.l1 = "Ну, замок имеется и вполне себе пыльный, но мы там не задержимся. Наша жизнь - свобода и горизонт по курсу. И с тобой я хотел бы жить её вечно!";
				link.l1.go = "LongHappy_4";
			}
		break;
		
		case "LongHappy_3":
			DialogExit();
			chrDisableReloadToLocation = true;//закрыть локацию
			DoQuestCheckDelay("Helena_LoveSex", 1.0);
			npchar.dialog.currentnode = "LongHappy_5";
			LAi_SetStayType(npchar);
		break;
		
		case "LongHappy_4":
			dialog.text = "Тогда - выпьем за тебя, мой капитан, мой муж, и моя судьба!";
			link.l1 = "За тебя, моя любовь! И за наше будущее вместе, то ли ещё будет!!";
			link.l1.go = "LongHappy_6";
		break;
		
		case "LongHappy_5":
			dialog.text = "Выпьем за тебя, мой капитан, мой муж, и моя судьба!";
			link.l1 = "За тебя, моя любовь! И за наше будущее вместе, то ли ещё будет!!";
			link.l1.go = "LongHappy_6";
		break;
		
		case "LongHappy_6":
			DialogExit();
			chrDisableReloadToLocation = false;
			npchar.dialog.currentnode = "Helena_officer";
			LongHappy_MarryToSenPierre();
		break;
		
		case "LongHappy_7":
			dialog.text = "Итак, аббат Бенуа вернулся в свою церковь и готов нас обвенчать. Но я не полезу в платье даже ради такого случая! Как думаешь - это будет очередной фурор в местном бомонде?";
			link.l1 = "Элен, я тебя в любом наряде люблю, а они - пусть смирятся, не впервой. Но, я как раз хотел посоветоваться с тобой о гостях и церемонии.";
			link.l1.go = "LongHappy_8";
		break;
		
		case "LongHappy_8":
			dialog.text = "Да, тут есть проблема - большинство тех, с кем мы с радостью разделили бы этот день, в город на пушечный выстрел не подпустят, не то, что в церковь. Поэтому - давай обвенчаемся здесь, ну как положено, а потом махнём на Исла Тесоро и устроим там настоящий праздник, что скажешь?";
			link.l1 = "Звучит отлично! Так и поступим. С Аббатом Бенуа я поговорю, но нам надо разослать приглашения и ещё...";
			link.l1.go = "LongHappy_9";
		break;
		
		case "LongHappy_9":
			dialog.text = "Спокойнее, капитан. Твоя будущая жена подхватит часть твоей ноши! Я устрою всё на Исла Тесоро и напишу нашим друзьям, ты только скажи: каким ты видишь этот праздник?";
			link.l1 = "Мой идеал - ты, я и самые близкие друзья. После всех официальных рож здесь на Мартинике, захочется душевного тепла.";
			link.l1.go = "LongHappy_10";
			link.l2 = "Мы должны запомнить этот день. Зови всех! Пусть никто не уйдёт обиженным!";
			link.l2.go = "LongHappy_11";
		break;
		
		case "LongHappy_10":
			pchar.questTemp.LongHappy.SmallMarry = "true";
			dialog.text = "Уютно и по семейному - ты читаешь мои мысли! Нам придётся заскочить в Шарптаун, и я всё подготовлю. Я уже прикидывала - думаю полсотни бочонков рома и пару десятков бочек вина будет достаточно. Также, на еду и увеселения нам потребуется тысяч триста серебром.";
			link.l1 = "Напомни - почему не ты ведёшь корабельные финансы? Я всё достану. Заскочу к аббату, и мы отплываем в Шарптаун.";
			link.l1.go = "LongHappy_12";
		break;
		
		case "LongHappy_11":
			pchar.questTemp.LongHappy.BigMarry = "true";
			dialog.text = "Значит, будем кутить как морские волки - сделаем! Нам придётся заскочить в Шарптаун, и я всё подготовлю. Но тут придётся серьёзно запастись - думаю, сотни бочонков рома и полсотни бочек вина должно хватить. И на прочие расходы уйдёт не меньше пятисот тысяч.";
			link.l1 = "Ну, я не совсем всё Береговое Братство имел в виду... А впрочем - давай! Припасы я достану. Вот только заскочу к аббату и мы отплываем в Шарптаун.";
			link.l1.go = "LongHappy_12";
		break;
		
		case "LongHappy_12":
			DialogExit();
			npchar.dialog.currentnode = "Helena_officer";
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "LongHappy_GirlNorm", 5.0);
			AddQuestRecord("LongHappy", "10");
			AddQuestUserData("LongHappy", "sName", "Элен");
			LongHappy_MarryGoToBenua();
		break;
		
		case "LongHappy_13":
			dialog.text = "Шарль, я разберусь с погрузкой, а потом отнесу письма барону и договорюсь с таверной. Ты не успеешь соскучиться?";
			link.l1 = "Я буду стараться изо всех сил! Или - просто полежу на песочке... не думал, что к штурму Тортуги подготовиться проще, чем к свадьбе.";
			link.l1.go = "LongHappy_14";
		break;
		
		case "LongHappy_14":
			DialogExit();
			SetLaunchFrameFormParam("Прошло несколько часов...", "", 0.1, 3.0);
			LaunchFrameForm();
			WaitDate("", 0, 0, 0, 4, 0);
			LongHappy_IslaTesoroRemoveGoods();
			npchar.dialog.currentnode = "LongHappy_15";
			LAi_SetActorType(npchar);
			LAi_ActorDialogDelay(npchar, pchar, "", 4.0);
		break;
		
		case "LongHappy_15":
			dialog.text = "Успел отдохнуть, Шарль? Представляешь - местные ребята так разгулялись неделю назад, что сожгли 'Старый Дятел', но барон обещал что к нашему приезду её отстроят больше и лучше, чем была. Об остальном я договорилась, так что можно отчаливать.";
			link.l1 = "Надеюсь, наша свадьба не оставит тут ещё пару пепелищ. Эх, а мне ведь нравился местный притон - уютно, антуражно! Ну да ладно, милая, ты права - время не ждёт.";
			link.l1.go = "LongHappy_16";
		break;
		
		case "LongHappy_16":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "LongHappy_GirlNorm", 5.0);
			AddQuestRecord("LongHappy", "12");
			pchar.questTemp.LongHappy = "marry_wait";
			pchar.questTemp.LongHappy.DrinkReady = "true";
		break;
		
		case "LongHappy_17":
			dialog.text = "Ян уже в городе, с ним Глэдис, представляешь? Вот уж не думала, что старики когда-нибудь, спляшут на моей свадьбе! Ох, гром и молния! Да в том кошмарном индейском городе-храме мне не было так... страшно.";
			link.l1 = "Всё хорошо, милая, всё хорошо. Я тоже волнуюсь - это нормально. Раз гости уже собрались - мне пора к отцу Бенуа. Узнаю, когда будет служба.";
			link.l1.go = "LongHappy_18";
		break;
		
		case "LongHappy_18":
			dialog.text = "Чувствую я, это будет чертовски длинный и непростой день. Ладно - ты иди, Шарль, а я пока схожу проведаю Яна и Глэдис.";
			link.l1 = "Я рад, что они смогли приехать. Старик Свенсон любит тебя как родную дочь, а мадам Мак Артур и подавно. Хорошо, что сегодня они будут рядом. Иди, и не волнуйся - всё будет прекрасно.";
			link.l1.go = "LongHappy_19";
		break;
		
		case "LongHappy_19":
			DialogExit();
			pchar.GenQuest.CannotWait = true;//запрет ожидания
			LAi_ActorRunToLocation(npchar, "reload", "reload4_back", "none", "", "", "OpenTheDoors", 5.0);
			AddQuestRecord("LongHappy", "14");
			AddQuestUserData("LongHappy", "sName", "Элен");
		break;
		
		case "LongHappy_20":
			dialog.text = "Да.";
			link.l1 = "";
			link.l1.go = "LongHappy_21";
		break;
		
		case "LongHappy_21":
			DialogExit();
			sld = characterFromId("Benua");
			sld.dialog.currentnode = "LH_abbat_27";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "LongHappy_22":
			dialog.text = "Да.";
			link.l1 = "";
			link.l1.go = "LongHappy_23";
		break;
		
		case "LongHappy_23":
			DialogExit();
			sld = characterFromId("Benua");
			sld.dialog.currentnode = "LH_abbat_29";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "LongHappy_24":
			dialog.text = "Да.";
			link.l1 = "";
			link.l1.go = "LongHappy_25";
		break;
		
		case "LongHappy_25":
			DialogExit();
			sld = characterFromId("Benua");
			sld.dialog.currentnode = "LH_abbat_31";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "LongHappy_26":
			dialog.text = "";
			link.l1 = "Я, Шарль, Анри де Мор, шевалье де Монпе, беру тебя, Элен Беатрисс Шарп, в законные жёны, и клянусь хранить верность в счастье и в несчастии, в болезни и в здравии, а так же любить и уважать тебя все отпущенные мне дни.";
			link.l1.go = "LongHappy_27";
		break;
		
		case "LongHappy_27":
			dialog.text = "Я, Элен Беатрисс Шарп, беру тебя Шарль Анри де Мор в законные мужья, и клянусь хранить верность в счастье и в несчастии, в здравии и в болезни, а также любить тебя и уважать все дни жизни моей.";
			link.l1 = "";
			link.l1.go = "LongHappy_28";
		break;
		
		case "LongHappy_28":
			DialogExit();
			sld = characterFromId("Benua");
			sld.dialog.currentnode = "LH_abbat_33";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "LongHappy_29":
			dialog.text = "Amen.";
			link.l1 = "";
			link.l1.go = "LongHappy_30";
		break;
		
		case "LongHappy_30":
			DialogExit();
			sld = characterFromId("Benua");
			sld.dialog.currentnode = "LH_abbat_35";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "LongHappy_31":
			dialog.text = "Элен Беатрисс де Мор, мадам де Монпе - а что, звучит, да муж мой?";
			link.l1 = "Не слышал ничего прекраснее, жена моя!";
			link.l1.go = "LongHappy_32";
		break;
		
		case "LongHappy_32":
			dialog.text = "Знаешь - я думала, что это ничего не изменит, и, наверное, так и есть - я любила тебя и раньше и хотела прожить с тобой остаток дней, но этот день, эта служба... Я счастлива, Шарль! Счастлива как никогда раньше, и погляди на Глэдис и Яна - они словно светятся! Вокруг вообще столько счастливых лиц! Кстати - тебе пора обойти гостей, и принимать поздравления. Возвращайся, когда закончишь - нас ждут в Шарптауне, не забывай.";
			link.l1 = "Так и сделаю, дорогая. Один поцелуй и я пошёл!";
			link.l1.go = "LongHappy_33";
		break;
		
		case "LongHappy_33":
			DialogExit();
			LongHappy_MarryKiss();
		break;
		
		case "LongHappy_34":
			dialog.text = "О, муж мой, ты уже поговорил с гостями?";
			link.l1 = "Пока нет, потерпи, милая, я скоро.";
			link.l1.go = "LongHappy_34_1";
			link.l2 = "Да, никогда не выслушивал столько поздравлений за раз. И знаешь что - большинство ведь говорили искренне!";
			link.l2.go = "LongHappy_35";
		break;
		
		case "LongHappy_34_1":
			DialogExit();
			npchar.dialog.currentnode = "LongHappy_34";
		break;
		
		case "LongHappy_35":
			dialog.text = "Да, этот бомонд на удивление душевный - признаться, я ожидала больше фальши и лицемерия. Или - я просто счастлива настолько, что не замечаю ничего. Но - нас ведь заждались наши друзья в Шарптауне! Когда отплываем?";
			link.l1 = "Прямо сейчас. Полетим как на крыльях, прямо к дружескому застолью. Надеюсь, жена моя, ты не против провести эту ночь в нашей каюте?";
			link.l1.go = "LongHappy_36";
		break;
		
		case "LongHappy_36":
			dialog.text = "О да, муж мой, ты знаешь толк в романтике! И не дёргайся так - я теперь имею право целовать тебя на публике... Вот, теперь пошли!";
			link.l1 = "Главное - не забыть приказать сняться с якоря...";
			link.l1.go = "LongHappy_37";
		break;
		
		case "LongHappy_37":
			DialogExit();
			npchar.dialog.currentnode = "LongHappy_38";
			LongHappy_MarryComplete();
		break;
		
		case "LongHappy_38":
			dialog.text = "Ой, мой дорогой, я так рада! Сегодня у нас замечательный день...";
			link.l1 = "";
			link.l1.go = "LongHappy_38_1";
		break;
		
		case "LongHappy_38_1":
			DialogExit();
			npchar.dialog.currentnode = "LongHappy_38";
		break;
		
		case "LongHappy_39":
			dialog.text = "Давай, Шарль. Этот брехун и в стену не попадёт!";
			link.l1 = "";
			link.l1.go = "LongHappy_40";
		break;
		
		case "LongHappy_40":
			DialogExit();
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.Angerran")) // fix 02-04-20
			{
				sld = characterFromId("Angerran");
				sld.dialog.currentnode = "Shivo_6";
			}
			else 
			{
				sld = characterFromId("LH_Dussak");
				sld.dialog.currentnode = "Dussak_5";
			}
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;
		
		case "LongHappy_41":
			dialog.text = "Я в порядке, Шарль, всё хорошо. Как Натан? Что с ним?";
			link.l1 = "Сколько крови... Данни, подожди, он дышит? Я вижу, он дышит!";
			link.l1.go = "LongHappy_42";
		break;
		
		case "LongHappy_42":
			DialogExit();
			sld = characterFromId("Danielle");
			sld.dialog.currentnode = "Danielle_9";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;
		
		case "LongHappy_43":
			dialog.text = "Быстрее, дорогой, нельзя терять время на разговоры!";
			link.l1 = "";
			link.l1.go = "LongHappy_43_1";
		break;
		
		case "LongHappy_43_1":
			DialogExit();
			npchar.dialog.currentnode = "LongHappy_43";
		break;
		
		case "LongHappy_44":
			dialog.text = "Шарль, ты цел? Ну и бойня... Прости - нас задержали - целая дюжина этих крыс пряталась под шканцами. Пришлось с ними повозиться!";
			link.l1 = "Не страшно, я справился. Рад, что смог закончить нашу с Жаком историю... наконец-то. Он получил по заслугам за все свои дела.";
			link.l1.go = "LongHappy_45";
		break;
		
		case "LongHappy_45":
			dialog.text = "Хорошо, муж мой - давай, заканчивай тут и возвращаемся. Мне не даёт покоя Натан, как он там? Он ведь меня прикрыл от того выстрела.";
			link.l1 = "Ты права, милая, я тоже о нём беспокоюсь. Иди - я сразу за тобой.";
			if (CheckAttribute(pchar, "questTemp.LongHappy.Terrax.Prisoner")) link.l1.go = "LongHappy_46";
			else link.l1.go = "LongHappy_48";
		break;
		
		case "LongHappy_46":
			dialog.text = "Кстати, мы нашли Маркуса - он был в трюме, связанный и без сознания, словно подарок на рождество.";
			link.l1 = "Но он жив, ведь так?";
			link.l1.go = "LongHappy_47";
		break;
		
		case "LongHappy_47":
			dialog.text = "Не беспокойся, любимый, барон Тиракс ещё всех нас переживёт. Только очнулся и уже буянить - требует саблю и на мостик.";
			link.l1 = "Узнаю старину Маркуса. Пусть отдохнёт пока. А мы закончим здесь, и на берег.";
			link.l1.go = "LongHappy_48";
		break;
		
		case "LongHappy_48":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "LongHappy_BarbExit", -1);
		break;
		
		case "LongHappy_49":
			if (CheckAttribute(pchar, "questTemp.LongHappy.Tichingitu_died") && CheckAttribute(pchar, "questTemp.LongHappy.Jino_died"))
			{
				dialog.text = "Мне так жаль, любимый. Сначала наш верный друг Тичингиту, потом Джино... Барбазона надо было убить дюжину раз за все его подлости!";
				link.l1 = "К сожалению, я сделал это лишь единожды. Мне тоже грустно... но мы победили, а Жак Добряк больше никому не сможет навредить.";
				link.l1.go = "LongHappy_50";
			}
			else
			{
				if (CheckAttribute(pchar, "questTemp.LongHappy.Jino_died"))
				{
					dialog.text = "Мне так жаль Джино, Шарль!! Я как узнала не поверила! Как ты, любимый?";
					link.l1 = "Тоже не укладывается в голове... глупо всё вышло, нечего сказать. Не так я себе представлял этот день.";
				}
				else
				{
					dialog.text = "Интересно, хронисты напишут о сражении в Бухте Приватира, как думаешь? Бароны Берегового братства сошлись в открытом бою - испанские власти утирают слезу умиления! Но, мы опять победили! Друзья живы, а враги мертвы - славный подарок к свадьбе!";
					link.l1 = "Да уж, тот ещё праздник вышел, но мы справились, любимая. Мы справились.";
				}
				link.l1.go = "LongHappy_50";
			}
		break;
		
		case "LongHappy_50":
			dialog.text = "Всё это необходимо как следует запить, вот что я думаю. Пойдем, Данни нашла нам домик тут на окраине - не хочу сейчас возвращаться на корабль. Посидим, помянем наших друзей, как подобает.";
			link.l1 = "Да, Элен, пойдем.";
			link.l1.go = "LongHappy_51";
		break;
		
		case "LongHappy_51":
			DialogExit();
			LongHappy_LogBook();
			DoQuestCheckDelay("LongHappy_MarryFinalizing", 0.5);
		break;
		
		case "LongHappy_52":
			if (CheckAttribute(pchar, "questTemp.LongHappy.Jino_died"))
			{
				dialog.text = "Мне так жаль Джино, Шарль!! Я как узнала не поверила! Как ты, любимый?";
				link.l1 = "Тоже не укладывается в голове... глупо всё вышло, нечего сказать. Не так я себе представлял этот день.";
			}
			else
			{
				dialog.text = "Повидался с Хоуком, или Данни тебя не пустила? Она и меня выставила, когда Джино сказал, что опасность миновала. Хорошо, что всё обошлось. Друзья живы, а враги мертвы - славный подарок к свадьбе!";
				link.l1 = "Да, мы победили - Барбазон кормит рыб, а бароны собирают остатки своих команд на берегу. Сражение в бухте Приватира закончено.";
			}
			link.l1.go = "LongHappy_53";
		break;
		
		case "LongHappy_53":
			dialog.text = "Шарль, я понимаю, что ты на ногах, наверное, еле держишься, но я была в таверне, и, представь, чего я наслушалась от местного халдея?";
			link.l1 = "Да, я только от Яна узнал - он сюда тоже приходил. Сдается мне, наш суровый маског пошёл в разнос. Давай-ка прогуляемся до бухты Сабу Матила - кое-кто видел его, ушедшего в том направлении.";
			link.l1.go = "LongHappy_54";
		break;
		
		case "LongHappy_54":
			DialogExit();
			LongHappy_LogBook();
			chrDisableReloadToLocation = false;
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			pchar.quest.longhappy_shoregirl.win_condition.l1 = "location";
			pchar.quest.longhappy_shoregirl.win_condition.l1.location = "Shore_ship1";
			pchar.quest.longhappy_shoregirl.function = "LongHappy_SetShoreGirl";
		break;
		
		case "LongHappy_55":
			dialog.text = "Ну Тичингиту, ну герой! Я едва со смеху не лопнула! Почему этот прекрасный обычай нынче не в ходу, а? Ладно - ты уже спишь на ходу, любимый. Пойдём, Данни нашла нам домик тут на окраине - тебе надо отдохнуть.";
			link.l1 = "Веди... кажется, я заснул ещё на том пляже.";
			link.l1.go = "LongHappy_56";
		break;
		
		case "LongHappy_56":
			DialogExit();
			DoQuestCheckDelay("LongHappy_MarryFinalizing", 0.5);
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
	}
}