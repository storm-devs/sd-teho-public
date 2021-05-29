// Санчо Карпентеро - бармен
#include "DIALOGS\russian\Rumours\Common_rumours.c"
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	ProcessCommonDialogRumors(NPChar, Link, NextDiag);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (CheckAttribute(pchar, "GenQuest.CitizenConflict") && sti(pchar.GenQuest.CitizenConflict) > 3)
			{
				dialog.text = "Я не желаю с тобой общаться. Ты нападаешь без причины на мирных граждан, провоцируешь их на драку. Уходи прочь из моей таверны!";
				link.l1 = "Гм...";
				link.l1.go = "exit";
				break;
			}
			if (pchar.questTemp.LSC == "return" && !CheckAttribute(npchar, "quest.return_isl"))
			{
				dialog.text = ""+pchar.name+"! Как же я рад тебя видеть! Я знал, я знал, что эти слухи - лживые! Черт возьми, за это надо немедленно выпить!";
				link.l1 = "Ну давай, выпьем, дружище! Я тоже чертовски рад видеть тебя.";
				link.l1.go = "exit";
				npchar.quest.return_isl = "true";
				break;
			}
			// пей до дна
			if (CheckAttribute(npchar, "quest.drink") && npchar.quest.drink == "fail")
			{
				dialog.text = ""+pchar.name+", я сожалею о твоем проигрыше. Этого толстяка редко кому удавалось обыграть. Сильно голова болит?";
				link.l1 = "Да, уж, дружище, ром у тебя знатный. Я тебе должен за выпивку... сколько?";
				link.l1.go = "drunk_fail";
				break;
			}
			if (CheckAttribute(npchar, "quest.drink") && npchar.quest.drink == "win")
			{
				dialog.text = "Ну, ты дал жару этому толстяку Фацио, "+pchar.name+"! Я, право, удивлен - мало кому удавалось обыграть его. Я искренне рад твоей победе. Вот, держи свои двести дублонов.";
				link.l1 = "Спасибо за теплые слова, дружище!";
				link.l1.go = "drunk_win";
				break;
			}
			// крабовый салат
			if (CheckAttribute(npchar, "quest.drink") && npchar.quest.crab == "begin")
			{
				dialog.text = ""+pchar.name+"? тут слушок прошел, что ты спускался на дно в водолазном костюме механика нарвалов. Это правда, или, как обычно, бабские сплетни?";
				link.l1 = "Слухи не врут, дружище. Я действительно спускался под воду.";
				link.l1.go = "crab";
				break;
			}
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "Приветствую нового человека в моей таверне! Добро пожаловать! У меня вы всегда найдете что выпить - благо, мои винные погреба полны - а вот насчет закусить - это уже сложнее, ха-ха... Шучу. Меня зовут Санчо Карпентеро, и я хозяин этой таверны.";
				link.l1 = TimeGreeting()+", Санчо. Меня зовут "+GetFullName(pchar)+". Приятно познакомиться.";
				link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "А, мой друг "+pchar.name+"! Рад вас видеть в моей таверне, как всегда! Желаете выпить?";
				// квестовые ветки
				if (CheckAttribute(pchar, "questTemp.Saga.SharkHunt") && pchar.questTemp.Saga.SharkHunt == "search_mush_1" && !CheckAttribute(npchar, "quest.mushket"))
				{
					link.l6 = "Послушай, Санчо, ты не знаешь, у кого можно достать хороший мушкет? Не обычное солдатское ружье, а что-нибудь для прицельной стрельбы, точное и дальнобойное?";
					link.l6.go = "mushket";
				}
				if (CheckAttribute(pchar, "questTemp.Saga.SharkHunt") && pchar.questTemp.Saga.SharkHunt == "search_mush_2")
				{
					link.l6 = "Послушай, Санчо, у меня к тебе несколько вопросов. Я ищу человека по имени Адольф Барбье. Говорят, что он у тебя частенько появляется...";
					link.l6.go = "adolf";
				}
				if (CheckAttribute(pchar, "questTemp.Saga.SharkHunt") && pchar.questTemp.Saga.SharkHunt == "barmen_whiskey")
				{
					link.l6 = "Послушай, Санчо, говорят, к тебе обращался Чад Каппер по поводу покупки мышьяка...";
					link.l6.go = "whiskey";
				}
				if (CheckCharacterItem(pchar, "talisman1") && CheckAttribute(npchar, "quest.rat"))
				{
					link.l7 = "Санчо, хочешь, я тебе кое-что покажу? Не эту ли маску летучей мыши ты так жаждешь заполучить?";
					link.l7.go = "rat";
				}
				if (makeint(pchar.money) >= 25)
				{
					link.l1 = "Налей мне рому, Санчо.";
					link.l1.go = "drink";
				}
				if (makeint(pchar.money) >= 20)
				{
					link.l2 = "Мне нужно переночевать.";
					link.l2.go = "room";
				}
				if (stf(environment.time) >= 6.0 && stf(environment.time) <= 18.0 && makeint(pchar.money) >= 300)
				{
					link.l9 = "Скукотища... Санчо, я хочу посидеть у тебя в таверне до вечера с бутылочкой хорошего вина. Так и время скоротаю...";
					link.l9.go = "drink_sit";
				}
				link.l3 = LinkRandPhrase("Что-нибудь интересное мне расскажешь?", "Что нового произошло на острове в последнее время?", "Не расскажешь ли последние сплетни?");
				link.l3.go = "rumours_LSC";
				if (CheckAttribute(npchar, "quest.crab") && npchar.quest.crab == "current" && CheckCharacterItem(pchar, "crab_pincers"))
				{
					link.l10 = "Санчо, я могу продать тебе крабовые клешни.";
					link.l10.go = "crab_trade";
				}
				link.l4 = "Санчо, я хочу задать тебе пару вопросов об острове.";
				link.l4.go = "int_quests"; //информационный блок
				link.l5 = "Нет, приятель. Я просто зашел проведать тебя.";
				link.l5.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting":
			dialog.text = "Мне тоже. Надеюсь, я буду видеть вас у себя если не каждый вечер, то хотя бы через день, ха-ха! Я искренне рад каждому посетителю моей таверны.";
			if (makeint(pchar.money) >= 25)
			{
				link.l1 = "Налей мне рому, Санчо.";
				link.l1.go = "drink";
			}
			if (makeint(pchar.money) >= 20)
			{
				link.l2 = "Мне нужно переночевать.";
				link.l2.go = "room";
			}
			link.l3 = "Санчо, я хочу задать тебе пару вопросов об острове.";
			link.l3.go = "int_quests"; //информационный блок
			link.l4 = "Еще увидимся, Санчо!";
			link.l4.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
		case "mushket":
			dialog.text = "Нет, дружище, не подскажу. Знаешь ли, я специалист по пивным кружкам и винным бутылкам, но никак не по мушкетам, ха-ха! Спроси в магазине, как я слышал, у Йоста в продаже периодически появляются неплохие образцы оружия. Может, что и подберешь себе.";
			link.l1 = "Спасибо за совет!";
			link.l1.go = "exit";
			npchar.quest.mushket = "true";
		break;
		
		case "adolf":
			dialog.text = "Адольф? Да, бывает он у меня, правда, последние дни что-то не заходит. Как посидел за одним столиком с толстяком Джузеппе, так и пропал после этого.";
			link.l1 = "Джузеппе? Уж не с Джузеппе Фацио ли?";
			link.l1.go = "adolf_1";
		break;
		
		case "adolf_1":
			dialog.text = "Ха, дружище, у нас на острове один Джузеппе, другого нет. Да, именно с ним. Они сидели несколько часов, пили ром, оживленно разговаривали, а потом ушли.";
			link.l1 = "Ссорились?";
			link.l1.go = "adolf_2";
		break;
		
		case "adolf_2":
			dialog.text = "Отнюдь. Вели себя как старые друзья. Послушай, тебе проще сходить в гости к Фацио на 'Каролину' и расспросить его самого об Адольфе.";
			link.l1 = "Хорошо, так и поступим.";
			link.l1.go = "adolf_3";
		break;
		
		case "adolf_3":
			dialog.text = "Это всё? Ты говорил, что у тебя несколько вопросов...";
			link.l1 = "Да. Скажи мне, кто такие Красная Мэри и Циклоп Марчелло?";
			link.l1.go = "adolf_4";
		break;
		
		case "adolf_4":
			dialog.text = "Красная Мэри - одна из нарвалов. Молодая красивая девушка, но с совершенно диким характером, да... Со шпагой и пистолетом управляется не хуже любого мужика. Была подружкой Алана Милроу, бывшего главы клана нарвал, пока того адмирал не прикончил\nСильно переживает по поводу смерти Алана, почти на улицах не показывается, а раньше чуть не каждый день у меня появлялась. Сидит у себя в каюте на 'Церес Смити', льет слезы и проклинает Акулу... Но ничего, погорюет-погорюет и утешится - жить-то надо дальше\nЧто касается Марчелло, тут ничего особого не скажу, так как видел его буквально пару раз. Подозрительный тип. Говорят, что в прошлом он был королевским егерем, потерял глаз в бою и подался в охрану кораблей, на одном из которых его сюда и прибило\nЛюто ненавидит всех пиратов, видать, имеет зуб на них. Впрочем, это неудивительно, учитывая его бывшую службу в абордажной роте торговых лоханок.";
			link.l1 = "Понятно. Спасибо большое, Санчо, ты мне очень помог!";
			link.l1.go = "adolf_5";
		break;
		
		case "adolf_5":
			dialog.text = "Да не за что, дружище, заходи еще, поболтаем за кружечкой эля...";
			link.l1 = "Обязательно!";
			link.l1.go = "adolf_6";
		break;
		
		case "adolf_6":
			DialogExit();
			pchar.questTemp.Saga.SharkHunt = "search_mush_3"; //флаг на Джузеппе
			AddQuestRecord("SharkHunt", "13");
		break;
		
		// виски для Акулы
		case "whiskey":
			dialog.text = "Каппер? Нет. Он в последнее время даже не заходил ко мне. Но пузырек мышьяка у меня буквально четверть часа назад купил Марчелло Циклоп - его тоже замучили крысы. Как я его понимаю... Житья от них нет, проклятых.";
			link.l1 = "Марчелло Циклоп?!";
			link.l1.go = "whiskey_1";
		break;
		
		case "whiskey_1":
			dialog.text = "Ну да. А ты видишь в этом что-то странное?";
			link.l1 = "Нет, ты что! Просто я уже который день его ищу, а тут, оказывается, он к тебе заходил. Не скажешь, куда он направился?";
			link.l1.go = "whiskey_2";
		break;
		
		case "whiskey_2":
			dialog.text = "Он уходил вместе с Адольфом Барбье, что живет на 'Санта-Флорентине'. Наверное, к нему и пошли.";
			link.l1 = "Спасибо!";
			link.l1.go = "whiskey_3";
		break;
		
		case "whiskey_3":
			dialog.text = "Если тебе нужен мышьяк - могу продать пузырек за два десятка дублонов.";
			link.l1 = "Хорошо. Вернемся к этому разговору позже, Санчо. Бывай!";
			link.l1.go = "whiskey_4";
		break;
		
		case "whiskey_4":
			DialogExit();
			pchar.questTemp.Saga.SharkHunt = "whiskey_poison"; // флаг - виски травят
			AddQuestRecord("SharkHunt", "37");
			sld = CharacterFromID("LSC_Adolf");
			LAi_SetActorType(sld);
			ChangeCharacterAddressGroup(sld, "SantaFlorentinaShipInside4", "goto", "goto2");
			sld = CharacterFromID("Dodson");
			sld.dialog.currentnode = "whiskey"; // ноду Акуле
			// важный момент! От дальнейшего поведения геймера зависит результат
			pchar.quest.LSC_Whiskeypoison_SF.win_condition.l1 = "location";
			pchar.quest.LSC_Whiskeypoison_SF.win_condition.l1.location = "SantaFlorentinaShipInside4";
			pchar.quest.LSC_Whiskeypoison_SF.function = "LSC_WhiskeyPoison_SF"; // прерывание на Санта-Флорентину
			pchar.quest.LSC_Whiskeypoison_AE.win_condition.l1 = "location";
			pchar.quest.LSC_Whiskeypoison_AE.win_condition.l1.location = "AvaShipInside3";
			pchar.quest.LSC_Whiskeypoison_AE.function = "LSC_WhiskeyPoison_AE"; // прерывание на Эву
			pchar.quest.LSC_Whiskeypoison_exit.win_condition.l1 = "location";
			pchar.quest.LSC_Whiskeypoison_exit.win_condition.l1.location = "LostShipsCity_town";
			pchar.quest.LSC_Whiskeypoison_exit.function = "LSC_Whiskeypoison_exit"; // прерывание на выход из таверны
			// закрываем вход к Фацио
			LocatorReloadEnterDisable("LostShipsCity_town", "reload20", true);
			LocatorReloadEnterDisable("LostShipsCity_town", "reload24", true);
		break;
		
		// пей до дна
		case "drunk_fail":
			dialog.text = "Да Бог с тобой, приятель! Ничего ты мне не должен. Ты и так облегчил свой карман на сотню дублонов. Зря ты пошел на поводу у Фацио...";
			if (sti(pchar.money) >= 500)
			{
				link.l1 = "Нет-нет, Санчо! Спасибо, вот, возьми пятьсот песо. Примерно на столько мы вчера и выпили. Не хочу быть должен.";
				AddMoneyToCharacter(pchar, -500);
			}
			else link.l1 = "Эх, спасибо, Санчо. Ну, что есть - то есть.";
			link.l1.go = "exit";
			DeleteAttribute(npchar, "quest.drink");
		break;
		
		case "drunk_win":
			DialogExit();
			TakeNItems(pchar, "gold_dublon", 200);
			Log_Info("Вы получили 200 дублонов");
			PlaySound("interface\important_item.wav");
			DeleteAttribute(npchar, "quest.drink");
		break;
		
		// крабовый салат
		case "crab":
			dialog.text = "Гм... тогда у меня к тебе будет предложение. Ты не встречал на дне гигантских крабов?";
			link.l1 = "Встречал ли я крабов? Да их там целая куча! А что за предложение?";
			link.l1.go = "crab_1";
		break;
		
		case "crab_1":
			dialog.text = "Если тебе вдруг придется вступить с крабом в схватку и ты убьешь его, то можешь отрезать у него клешни и принести мне. Я очень хорошо заплачу за них. Буду платить даже не песо, а дублонами - по пять монет за штуку. Аксель Йост столько не заплатит, поверь. Нет, я не подбиваю тебя охотиться на крабов, ты не подумай, но если вдруг доведется...";
			link.l1 = "А почему именно клешни? Другие части краба непригодны? И что ты с ними делаешь?";
			link.l1.go = "crab_2";
		break;
		
		case "crab_2":
			dialog.text = "Почему клешни? Да потому что на них находится больше всего мяса. На ногах у крабов мяса почти нет, а тело покрыто твердым панцирем. Если ты не в курсе, у нас крабовое мясо - деликатес, поскольку оно очень вкусное и питательное\nА я еще умею делать из него такие блюда, которые не сможет сделать никто на Острове, так что в желающих их отведать недостатка не было и не будет. Поэтому я и готов платить по пять дублонов за штуку.";
			link.l1 = "Хорошо. Буду иметь в виду.";
			link.l1.go = "crab_3";
		break;
		
		case "crab_3":
			DialogExit();
			npchar.quest.crab = "current";
		break;
		
		case "crab_trade":
			iTotalTemp = GetCharacterItem(pchar, "crab_pincers")
			dialog.text = "Отлично! Сколько у тебя есть?";
			link.l1 = ""+FindRussianQtyString(iTotalTemp)+".";
			link.l1.go = "crab_trade_1";
		break;
		
		case "crab_trade_1":
			dialog.text = "Забираю. Вот, держи свои дублоны - "+FindRussianQtyString(iTotalTemp*5)+". Спасибо, приятель, если добудешь еще клешней - обязательно приноси!";
			link.l1 = "Хорошо, дружище.";
			link.l1.go = "crab_trade_2";
		break;
		
		case "crab_trade_2":
			DialogExit();
			RemoveItems(pchar, "crab_pincers", iTotalTemp);
			TakeNItems(pchar, "gold_dublon", iTotalTemp*5);
			PlaySound("interface\important_item.wav");
			Log_Info("Вы получили "+iTotalTemp*5+" дублонов");
		break;
		
		// крыс
		case "rat":
			dialog.text = "Что?! А ну, покажи мне поближе! Дай рассмотреть!";
			link.l1 = "Пожалуйста.";
			link.l1.go = "rat_1";
		break;
		
		case "rat_1":
			PlaySound("interface\important_item.wav");
			dialog.text = "Она... Точно - она! Именнно такую мне и нарисовал моряк, рассказывавший о ней! Дружище, ты ведь не просто так принес ее мне, правда? Что ты за нее хочешь? Сколько?";
			link.l1 = "Ну конечно, не просто так. Что я хочу? Не знаю. А что ты предлагаешь? Помнится, ты обещал вознаградить по-царски...";
			link.l1.go = "rat_2";
			link.l2 = "Извини, приятель, но я ее не продаю. Она нужна мне самому. Просто я хотел убедиться, что это действительно тот самый оберег.";
			link.l2.go = "rat_exit";
		break;
		
		case "rat_exit":
			PlaySound("interface\important_item.wav");
			dialog.text = "Эх, какая жалость... Да, парень, скорее всего, это и есть тот самый талисман. Везунчик! Теперь тебе можно не бояться крыс. А я все так и буду травить их мышьяком...";
			link.l1 = "Прости, Санчо, что раздразнил тебя. Просто я сам никогда его раньше не видел и нужна была консультация. Извини.";
			link.l1.go = "exit";
			DeleteAttribute(npchar, "quest.rat");
		break;
		
		case "rat_2":
			dialog.text = ""+pchar.name+", я отдам тебе за нее самый лучший и дорогой предмет, который у меня есть. Мне он точно ни к чему, а бравому вояке, вроде тебя, будет отличной заменой этому оберегу. Сейчас принесу\nВот, посмотри: уникальная, великолепная миланская кираса штучной работы! Отлично защищает в бою, практически не сковывает движений, легкая, удобная. Таких на Карибах днем с огнем не сыскать, да и в Европе редкость\nЯ нашел этот доспех в капитанской каюте одного испанского военного корабля несколько лет назад и хранил специально для такого случая, чтобы выменять на что-то ценное. И, похоже, этот момент наступил. Бери себе эту кирасу взамен на Крысиного Бога!";
			link.l1 = "Хм... Отличная кираса! Думаю, такой обмен меня устраивает. С крысами я как-нибудь управлюсь, а вот второй такой кирасы и впрямь не найти. Я такую впервые вижу. Действительно, уникальный доспех.";
			link.l1.go = "rat_3";
		break;
		
		case "rat_3":
			dialog.text = "Я рад, что ты согласился, дружище. Спасибо тебе за то, что не забыл про мою проблему! Держи кирасу, и пусть она служит тебе надежной защитой в бою.";
			link.l1 = "Держи и ты свой оберег - похоже, для крыс в твоей таверне наступают черные дни!";
			link.l1.go = "rat_4";
		break;
		
		case "rat_4":
			DialogExit();
			GiveItem2Character(pchar, "cirass4");
			RemoveItems(pchar, "talisman1", 1);
			Log_Info("Вы отдали оберег 'Крысиный бог'");
			Log_Info("Вы получили миланский панцирь");
			PlaySound("interface\important_item.wav");
			DeleteAttribute(npchar, "quest.rat");
		break;
		
		//--> информационный блок
		case "int_quests":
			dialog.text = "Внимательно тебя слушаю.";
			if (!CheckAttribute(npchar, "quest.answer_1"))
			{
				link.l1 = "Что это за место такое? Можешь поподробнее рассказать?";
				link.l1.go = "ansewer_1";
			}
			if (!CheckAttribute(npchar, "quest.answer_2"))
			{
				link.l2 = "Как можно уплыть отсюда на архипелаг?";
				link.l2.go = "ansewer_2";
			}
			if (!CheckAttribute(npchar, "quest.answer_3"))
			{
				link.l3 = "Что мне следует знать об Острове?";
				link.l3.go = "ansewer_3";
			}
			if (!CheckAttribute(npchar, "quest.answer_4"))
			{
				link.l4 = "А как тебе самому-то тут? Как твоя таверна?";
				link.l4.go = "ansewer_4";
			}
			link.l10 = "Нет вопросов. Извини...";
			link.l10.go = "exit";
		break;
		
		case "ansewer_1":
			dialog.text = "Место? Ну, его называют Островом Справедливости, Островом Погибших Кораблей, но мы его зовем просто Остров. Состоит из остовов разбитых кораблей, осевших на мелководье среди рифов. Центральная часть Острова приспособлена под жилые помещения, а внешнее кольцо - необитаемо. Связи с внешним миром уже как десять лет нет.";
			link.l1 = "Понятно...";
			link.l1.go = "int_quests";
			npchar.quest.answer_1 = "true";
		break;
		
		case "ansewer_2":
			dialog.text = "Построить лодку или плот. Но закончится это плохо для тебя: за внешним кольцом - аномальная зона штормов. Сильный шквал может налететь в любую минуту, и твоему утлому челну придет конец. К тому же, Остров огибает сильное течение, которое прибивает сюда новые корабли, так что тебе придется здорово потрудиться, сидя на веслах, пока преодолеешь его\nВ одиночку это у тебя не выйдет - проверено не раз. А помощников ты навряд ли найдешь, потому как всем известно, что покидать Остров на жалкой лодке равносильно самоубийству. А построить хороший корабль, который сумеет пройти сквозь течение и устоять перед штормом - сложно в наших условиях, несмотря на обилие корабельных остовов\nК тому же, надо еще будет вывести построенный корабль за пределы внешнего кольца и провести через рифы, а это задача, скажу тебя прямо - невыполнимая. Так что лучше привыкай к жизни у нас\nСкажу по секрету: все, кто пожил здесь хотя бы три-четыре года, оставляют все свои помыслы о возврате назад, и не потому, что отчаялись, а потому, что здесь ничуть не хуже, а для большинства - лучше, чем на Большой земле. Поспрашивай у людей - тут очень мало тех, кто хочет покинуть Остров.";
			link.l1 = "Ясно...";
			link.l1.go = "int_quests";
			npchar.quest.answer_2 = "true";
		break;
		
		case "ansewer_3":
			dialog.text = "В первую очередь ты должен помнить о том, что не все места на острове доступны для свободного посещения. На острове живут две группировки, или клана - нарвалы и ривадос, как они сами себя называют. Кланы издавна враждуют между собой и ревностно охраняют свою территорию, не пуская чужаков. Если ты попробуешь сунуться к ним без разрешения - они тебя попросту убьют\nЧтобы пройти к ним на корабли, ты должен знать текущий пароль. Но можешь не опасаться того, что ты забредешь к ним на территорию по ошибке - перед запретными зонами стоят блок-посты, на которых охрана предупреждает, что дальше идти не следует. Ну, а если ты все-таки полезешь - то пеняй на себя.";
			link.l1 = "Приму к сведению...";
			link.l1.go = "int_quests";
			npchar.quest.answer_3 = "true";
		break;
		
		case "ansewer_4":
			dialog.text = "Ты знаешь, дружище, нормально. До того, как я попал на Остров, вся моя деятельность была связана с едой и выпивкой: работал поваром, еще в Европе, интендантом в гарнизоне, корчмарем, коком на корабле. А когда попал сюда - уже полтора десятка лет прошло с этого момента - сразу занялся организацией таверны\nМне моя работа нравится, да и жизнью вполне доволен. Люди тут в большинстве своем дружелюбные, или, по крайней мере - не буйные, кланы в мою деятельность не вмешиваются. По вечерам у меня бывает многолюдно - то с одним поговоришь, то с другим... В общем, это лучшее место, которое было у меня в жизни. Я сам себе хозяин\nЕдинственное, что меня донимает - это крысы. Совсем замучали, проклятые, житья от них нет. Грызут, портят мои продукты и посуду. Никак изничтожить их не могу.";
			link.l1 = "Крысы? Да, это бич для всех...";
			link.l1.go = "ansewer_4_1";
		break;
		
		case "ansewer_4_1":
			dialog.text = "Увы, но мне 'везет' больше других. Если на прочих кораблях крыс умеренное количество, а в магазине Акселя Йоста их вообще нет - не знаю, как он ухитрился их вывести - то у меня этих проклятых грызунов буквально полчища. Эх, рассказывали мне моряки, что на Карибах встречается редкий оберег\n'Крысиный бог' называется. Вроде как маска в виде морды летучей мыши. Говорят, что при наличии этого предмета крысы разбегаются без оглядки. Видимо, Акселю кто-то продал такой амулет - он скупает и перепродает весь хлам, что люди находят на внешнем кольце\nПринес бы мне кто такой оберег - честное слово, отблагодарил бы по-царски!";
			link.l1 = "Интересно...";
			link.l1.go = "int_quests";
			npchar.quest.answer_4 = "true";
			npchar.quest.rat = "true";
		break;
		//<-- информационный блок
		
		//--> выпивка
		case "drink":
			if (CheckAttribute(pchar, "questTemp.Rum") && sti(pchar.questTemp.Rum) > 4)
			{
				dialog.text = ""+pchar.name+", по-моему, тебе следует остановиться. Не дай Бог беды пьяным натворишь, или полезешь куда не надо, или свалишься за борт крабам в клешни... У нас пьяные выходки смертельно опасны, и уже не одного человека свели в могилу раньше времени.";
				link.l1 = "Хм... Пожалуй, ты прав, Санчо - я уже достаточно выпил. Спасибо за заботу!";			
				link.l1.go = "exit";
			}
			else
			{
				AddMoneyToCharacter(pchar, -25);
				if(!IsEquipCharacterByArtefact(pchar, "totem_01"))
				{
					if (CheckAttribute(pchar, "questTemp.Rum"))
					{
						pchar.questTemp.Rum = sti(pchar.questTemp.Rum) + 1;
					}
					else pchar.questTemp.Rum = 1;
				}
				else 
				{
					if(CheckAttribute(pchar, "questTemp.Rum")) DeleteAttribute(pchar, "questTemp.Rum");
				}				
				WaitDate("",0,0,0, 0, 30);
				
				dialog.text = "Пожалуйста, приятель. Всего за двадцать пять песо - пинта моего лучшего рома!";
				link.l1 = RandPhraseSimple(LinkRandPhrase("Ну, за твое здоровье и процветание твоего заведения, дружище!","Ну, за тех, кто в море!","Ну, за здоровье жителей вашего острова!"), LinkRandPhrase("Ну, за то, чтобы этот остров стоял вечно!","Ну, за то, чтобы ветер всегда был попутным во всех делах!","Ну, за счастье, удачу, радости и... женщин!"));		
				link.l1.go = "drink_1";
			}
		break;
		
		case "drink_1":
			DialogExit();
			LAi_Fade("", "");
			if (CheckAttribute(pchar, "questTemp.Rum"))
			{
				if (sti(pchar.questTemp.Rum) < 3) LAi_AlcoholSetDrunk(pchar, 51, 5600);
				else LAi_AlcoholSetDrunk(pchar, 71, sti(pchar.questTemp.Rum)*2800);
			}
		break;
		
		case "drink_sit":
			if (chrDisableReloadToLocation || pchar.questTemp.Saga.SharkHunt == "barmen_whiskey" || pchar.questTemp.Saga.SharkHunt == "whiskey_poison") //идет квест
			{
				dialog.text = "Я думаю, что тебе не стоит сейчас выпивать. Поверь мне...";
				link.l1 = "Ладно.";
				link.l1.go = "exit";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.LSC.MaryBye") || CheckAttribute(pchar, "questTemp.LSC.MaryWait")) // подружился с Мэри
			{
				dialog.text = "Хех, ну ты точно чудак, право... Разве тебе не с кем скоротать время на Острове? Дружище, да меня потом Мэри просто изведет, если узнает, что я позволил тебе тут просиживать в одиночку и напиваться. Приходите вечером вдвоем и балагурьте, хоть до самого утра.";
				link.l1 = "Ладно...";
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = "Да не вопрос, дружище. За каких-то три сотни песо ты получишь бутылку отличного "+LinkRandPhrase("испанского","итальянского","французского")+" вина, и расслабляйся, сколько душе угодно.";
				link.l1 = "Спасибо!";
				link.l1.go = "drink_sit_1";
			}
		break;
		
		case "drink_sit_1":
			DialogExit();
			sld = ItemsFromID("potionrum");
			sld.shown = true;
			sld.startLocation = "FleuronTavern";
			sld.startLocator = "bottle";
			DoQuestReloadToLocation("FleuronTavern", "quest", "sit2", "LSC_DrinkSit");
		break;
		//<-- выпивка
		
		//--> сон в таверне
		case "room":
   			if (chrDisableReloadToLocation || pchar.questTemp.Saga.SharkHunt == "barmen_whiskey" || pchar.questTemp.Saga.SharkHunt == "whiskey_poison") //идет квест
			{
				dialog.text = "Я думаю, что тебе не стоит сейчас спать. Поверь мне...";
				link.l1 = "Ладно.";
				link.l1.go = "exit";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.LSC.MaryBye") || CheckAttribute(pchar, "questTemp.LSC.MaryWait")) // подружился с Мэри
			{
				if(!isDay())
				{
					dialog.text = "Такого чудака я еще не встречал. Его ждет на 'Церес Смити' замечательная девушка, а он в таверну ночевать приперся. Даже не думай, что я тебе позволю у меня спать. Мэри потом меня со свету сживет.";
					link.l1 = "Ладно...";
					link.l1.go = "exit";
				}
				else
				{
					dialog.text = "Можешь отдохнуть у меня наверху до вечера. Но ночевать здесь я тебе не позволю - Мэри меня потом со свету сживет. Ты уж извини...";
					link.l1 = "Хорошо. Я остаюсь у тебя до вечера.";
					link.l1.go = "hall_night_wait";
					link.l2 = "Ладно... Тогда я обойдусь без сна.";
					link.l2.go = "exit";
				}
				break;
			}
			dialog.text = "Ты можешь выспаться на кровати, что находится на верхнем ярусе, всего за двадцать песо. Когда тебя разбудить?";
			if(!isDay())
			{
				link.l1 = "Утром.";
				link.l1.go = "hall_day_wait";
			}
			else
			{
				link.l1 = "К ночи.";
				link.l1.go = "hall_night_wait";
				link.l2 = "Следующим утром.";
				link.l2.go = "hall_day_wait";
			}
			link.l3 = "Передумал"+ GetSexPhrase("","а") +". Обойдусь без сна.";
			link.l3.go = "exit";
		break;
		
		case "hall_night_wait":
			AddMoneyToCharacter(pchar, -20);
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			TavernWaitDate_LSC("wait_night");
		break;
		
		case "hall_day_wait":
			AddMoneyToCharacter(pchar, -20);
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			TavernWaitDate_LSC("wait_day");
		break;
		//<-- сон в таверне
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
	}
}