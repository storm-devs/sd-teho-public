// диалог начальника шахты
void ProcessDialogEvent()
{
	ref NPChar, sld, location;
	aref Link, NextDiag;
	int i, iTemp;
	string sTemp;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		location = &Locations[FindLocation(pchar.location)];
		case "First time":
			if (LAi_grp_playeralarm > 0)
			{
       			dialog.text = NPCharRepPhrase(pchar, 
					LinkRandPhrase("Вы посмели явиться сюда?! Смелый шаг...", "Как эти бездельники допустили, чтобы ко мне ворвался враг?! Уму непостижимо...", "Да уж, моя охрана немногого стоит, раз "+ GetSexPhrase("какой-то бездельник","какая-то бездельница") +" бегает в тут..."), 
					LinkRandPhrase("Что тебе нужно, "+ GetSexPhrase("негодяй","мерзавка") +"?! Мои солдаты уже взяли твой след, далеко тебе не уйти"+ GetSexPhrase(", грязный пират","") +"!", "Грязн"+ GetSexPhrase("ый","ая") +" убийца, вон из моей резиденции! Стража!!", "Я не боюсь тебя, мерзав"+ GetSexPhrase("ец","ка") +"! Скоро тебя повесят, далеко тебе не уйти..."));
				link.l1 = NPCharRepPhrase(pchar,
					RandPhraseSimple("Солдатня мало чего стоит...", "Им меня ни за что не поймать."), 
					RandPhraseSimple("Заткни свою пасть, " + GetWorkTypeOfMan(npchar, "") + ", а не то вырву твой поганый язык!", "Вот что я тебе скажу, приятель: сиди тихо, и будешь жить..."));
				link.l1.go = "fight";
				break;
			}
			if (GetNationRelation2MainCharacter(sti(NPChar.nation)) == RELATION_ENEMY)
			{
    			dialog.text = "Враг в шахте! Тревога!!";
				link.l1 = "А-ать, дьявол!";
				link.l1.go = "fight"; 
				break;
			}	
			dialog.text = LinkRandPhrase(""+TimeGreeting()+", сеньор. Я - "+GetFullName(npchar)+", дежурный горный инженер рудника Лос-Текес. Что вам тут нужно?","Здравствуйте, сударь. Что вам угодно?","Хм. Вы что-то хотели от меня, сеньор? Я вас слушаю.");
			if (!CheckAttribute(location, "quest.info"))
			{
				link.l9 = "Я здесь недавно, и хотел бы немного больше узнать об этом руднике...";
				link.l9.go = "info";
			}
			if (GetSquadronGoods(pchar, GOOD_SLAVES) > 4)
			{
				link.l2 = "У меня в трюмах есть товар, который вас интересует. Рабы для вашего рудника. Поторгуемся?";
				if (!CheckAttribute(location, "quest.slaves")) link.l2.go = "slaves_0";
				else link.l2.go = "slaves";
			}
			link.l1 = "Я просто зашел с вами поздороваться и уже ухожу.";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
		case "info":
			dialog.text = "Наш рудник Лос-Текес добывает золото для испанской короны. Все добытое на руднике принадлежит Испании, и только ей. Кроме золота, здесь часто встречаются серебряные самородки и изредка - ценные самоцветы. Торговлю золотом мы не ведем - все добытое отправляется под усиленным конвоем в Старый Свет\nОднако насчет золотых и серебряных самородков действуют два исключения. Первое: вы можете приобрести некоторое количество самородков в нашем магазине у интенданта. Иногда жалование гарнизону из метрополии задерживается, и мы вынуждены иметь некоторый запас монет на этот случай - потому продажа самородков и была разрешена\nВторое: нам практически постоянно требуются рабочие руки для труда на руднике, поэтому мы покупаем рабов в обмен на самородки. Так что если у вас есть, что предложить - обращайтесь ко мне, будем договариваться\nКасательно поведения в шахте, думаю, вам и так должно быть ясно: не пытайтесь что-либо украсть, ибо закончится это для вас плачевно, не отвлекайте каторжников от работы и не путайтесь под ногами у солдат охранения.";
			link.l1 = "Спасибо!";			
			link.l1.go = "exit";
			location.quest.info = "true";
		break;
		
		// генератор купли-продажи рабов
		case "slaves_0":
			location.quest.slaves.qty = 200; // стартовая потребность
			dialog.text = "Конечно, сеньор! Сколько у вас голов 'живого товара'?";
			link.l1 = "У меня есть "+FindRussianQtyString(GetSquadronGoods(pchar, GOOD_SLAVES))+".";
			link.l1.go = "slaves_1";
		break;
		
		case "slaves":
			location.quest.slaves.qty = sti(location.quest.slaves.qty)+GetNpcQuestPastDayParam(location, "slave_date"); // каждый день дает +1 потребности
			if (sti(location.quest.slaves.qty) > 350) location.quest.slaves.qty = 350; // максимум потребности
			if (sti(location.quest.slaves.qty) < 5)
			{
				dialog.text = "Сеньор, к сожалению, на данный момент у нас нет нужды в рабах. Но ситуация меняется ежедневно, так что загляните ко мне попозже, через несколько недель, ну, или в другой раз.";
				link.l1 = "Хорошо, сударь. Я все понимаю: не нужны сейчас - понадобятся потом.";
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = "Конечно, сеньор! Сколько у вас голов 'живого товара'?";
				link.l1 = "У меня есть "+FindRussianQtyString(GetSquadronGoods(pchar, GOOD_SLAVES))+".";
				link.l1.go = "slaves_1";
			}
		break;
		
		case "slaves_1":
			dialog.text = "За каждого раба я готов выдать вам либо один золотой самородок, либо два серебряных. Что выбираете?";
			link.l1 = "Золотые самородки.";
			link.l1.go = "slaves_g";
			link.l2 = "Серебрные самородки.";
			link.l2.go = "slaves_s";
			link.l3 = "Извините, сеньор, но что-то я передумал. В другой раз.";
			link.l3.go = "slaves_exit";
		break;
		
		case "slaves_g":
			location.quest.slaves.type = "gold";
			dialog.text = "Хорошо. Сколько рабов вы готовы мне продать?";
			link.l1 = "";
			link.l1.edit = 6;
			link.l1.go = "slaves_trade";
		break;
		
		case "slaves_s":
			location.quest.slaves.type = "silver";
			dialog.text = "Хорошо. Сколько рабов вы готовы мне продать?";
			link.l1 = "";
			link.l1.edit = 6;
			link.l1.go = "slaves_trade";
		break;
		
		case "slaves_trade":
			iTotalTemp = sti(dialogEditStrings[6]);
			if (iTotalTemp < 1)
			{
				dialog.text = "Сеньор, я не расположен к глупым шуткам. Паясничать отправляйтесь в таверну!";
				link.l1 = "Гм...";
				link.l1.go = "slaves_exit";
				break;
			}
			if (iTotalTemp > GetSquadronGoods(pchar, GOOD_SLAVES))
			{
				dialog.text = "Сеньор, мне кажется, вам нужно отдохнуть. Видимо, вы очень устали, или перегрелись на нашем солнце. Сходите в таверну, поспите, а потом продолжим нашу торговлю.";
				link.l1 = "Гм...";
				link.l1.go = "slaves_exit";
				break;
			}
			if (iTotalTemp > sti(location.quest.slaves.qty))
			{
				dialog.text = "К сожалению, сеньор, нам в данный момент не нужно так много рабов. Потребность рудника на сегодняшний день составляет "+FindRussianQtyString(sti(location.quest.slaves.qty))+". Будете продавать?";
				link.l1 = "Да, конечно!";
				link.l1.go = "slaves_max";
				link.l2 = "Гм... Нет, пожалуй.";
				link.l2.go = "slaves_exit";
				break;
			}
			dialog.text = ""+FindRussianQtyString(iTotalTemp)+"? Замечательно. Прикажите доставить их к городским воротам, я пошлю своих людей.";
			link.l1 = "Не извольте беспокоиться, сеньор. Ваши рабы будут доставлены как можно скорее. Я немедленно отдам нужные распоряжения.";
			link.l1.go = "slaves_calk";
		break;
		
		case "slaves_max":
			iTotalTemp = sti(location.quest.slaves.qty);
			dialog.text = "Замечательно. Прикажите доставить их к городским воротам, я пошлю своих людей.";
			link.l1 = "Не извольте беспокоиться, сеньор. Ваши рабы будут доставлены как можно скорее. Я немедленно отдам нужные распоряжения.";
			link.l1.go = "slaves_calk";
		break;
		
		case "slaves_calk":
			DialogExit();
			Log_Info("Обмен рабов на самородки произведен");
			PlaySound("interface\important_item.wav");
			LAi_Fade("", "");
			WaitDate("",0,0,0,5,10);
			RemoveCharacterGoods(pchar, GOOD_SLAVES, iTotalTemp);
			if (location.quest.slaves.type == "gold") TakeNItems(pchar, "jewelry5", iTotalTemp);
			else TakeNItems(pchar, "jewelry6", iTotalTemp*2);
			DeleteAttribute(location, "slave_date");
			SaveCurrentNpcQuestDateParam(location, "slave_date");
			location.quest.slaves.qty = sti(location.quest.slaves.qty)-iTotalTemp;
		break;
		
		case "slaves_exit":
			DialogExit();
			DeleteAttribute(location, "slave_date");
			SaveCurrentNpcQuestDateParam(location, "slave_date");
		break;
		
		case "fight":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
		    LAi_group_Attack(NPChar, Pchar);
			i = GetCharIDXByParam("CityType", "location", Pchar.location); // фантом солдат
			if (i != -1)
			{
			    LAi_group_Attack(&Characters[i], Pchar);
			}
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
