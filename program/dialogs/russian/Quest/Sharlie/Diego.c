// Диего де Монтойя
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "Ты что-то хотел?";
			link.l1 = "Да нет, ничего.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		case "patrol":
			dialog.text = TimeGreeting()+", "+GetFullName(npchar)+", начальник патруля из Сан-Хосе. Поступило сообщение о подозрительных людях в окрестностях города. Будьте любезны объяснить, кто вы и что тут делаете.";
			link.l1 = "Капитан "+GetFullName(pchar)+", сеньор офицер. Я нахожусь здесь по поручению и прямому указанию отца Винсенто, инквизитора. Вот бумага, подтверждающая мои полномочия.";
			link.l1.go = "patrol_1";
		break;
		
		case "patrol_1":
			dialog.text = "Так-так... всё верно. Грамота за подписью инквизитора в полном порядке. Прошу извинить мою подозрительность - что вы делаете на маяке?";
			link.l1 = "Я не вправе отвечать на подобные вопросы. Если вас действительно интересует цель моей работы на инквизитора, то вам лучше обратиться за разъяснениями прямо к нему, в Сантьяго. Вы офицер, и знаете о военной и служебной тайне. Единственное, что могу сказать - я расследую обстоятельства гибели одного испанского судна.";
			link.l1.go = "patrol_2";
		break;
		
		case "patrol_2":
			dialog.text = "Ещё раз приношу свои извинения, месье. Не смею вас задерживать... ах, минуточку! Это действительно так, или мне показалось? Какая у вас интересная дага! Не покажете?";
			link.l1 = "Смотрите, только не забудьте вернуть. Это очень дорогая вещь.";
			link.l1.go = "patrol_3";
		break;
		
		case "patrol_3":
			dialog.text = "Чёрт побери, я видел её рисунок в одной из книг в библиотеке! Это же кинжал самого Кортеса! Вот и клеймо на нём... Месье, не откажите в любезности, уступите мне эту дагу! Я коллекционирую древнее и именное оружие, а это просто изумительный экземпляр. Я хорошо заплачу.";
			link.l1 = "Сеньор, эта дага не продаётся. Я получил её в подарок и не намерен никому продавать. Верните её, пожалуйста.";
			link.l1.go = "patrol_4";
		break;
		
		case "patrol_4":
			dialog.text = "Даже пятьсот золотых дублонов вас не устроит? Это же целая куча денег, на них корабль можно купить!";
			link.l1 = "Нет. Корабль у меня уже есть, а вот дага - одна. Я её не продам.";
			link.l1.go = "patrol_5";
		break;
		
		case "patrol_5":
			dialog.text = "Эх, жаль... Ладно, возьмите вашу ценность. Не смею больше задерживать. Удачи!";
			link.l1 = "Всего доброго, офицер.";
			link.l1.go = "patrol_6";
		break;
		
		case "patrol_6":
			DialogExit();
			AddQuestRecord("Guardoftruth", "42");
			LAi_ActorGoToLocation(npchar, "reload", "reload2", "none", "", "", "GuardOT_ClearMayakPatrol", 12.0);
			for(i=1; i<=3; i++)
			{
				sld = characterFromId("GOT_spamayaksold_"+i);
				sld.lifeday = 0;
				LAi_SetActorType(sld);
				LAi_ActorGoToLocation(sld, "reload", "reload2", "none", "", "", "", 10.0);
			}
		break;
		
		case "shore":
			PlaySound("VOICE\Russian\Sharlie\Diego De Montoya.wav");
			dialog.text = "Довольно! Я хочу говорить с ним...";
			link.l1 = "Итак, я вижу перед собой самого Диего де Монтойя... но позвольте, сеньор, мы ведь с вами уже встречались? Да-да, точно. На маяке Тринидада. Вот только там вы назвали себя как-то по-другому...";
			link.l1.go = "shore_1";
		break;
		
		case "shore_1":
			dialog.text = "У вас хорошая память, сударь. Что же до встречи на маяке - не вы один умеете плести интриги и вести закулисные войны. Я хорошо осведомлён о вашем неуёмном желании меня увидеть. Что же, ваше желание исполнилось.";
			link.l1 = "Немного не такой встречи я хотел, сеньор.";
			link.l1.go = "shore_2";
		break;
		
		case "shore_2":
			dialog.text = "Ну уж какая получилась. Но я всё же дам вам шанс уйти отсюда живым, если вы отдадите мне свою дагу.";
			link.l1 = "Неужели страсть к коллекционированию завела вас настолько далеко, кабальеро, что вы подготовили для меня столь продуманную ловушку? О нет! Вам не даёт покоя Страж Истины, я угадал?";
			link.l1.go = "shore_3";
		break;
		
		case "shore_3":
			dialog.text = "Понятия не имею, о чём вы там толкуете. Дага должна вернуться на положенное ей место, и это всё, что вам необходимо знать. Не захотели расстаться с ней за золото - сейчас обменяете на свою жизнь.";
			link.l1 = "И вы думаете, сеньор, что я поверю вашим словам? Вы уже давно для себя решили, что из этой бухты я не уйду. Разве нет?";
			link.l1.go = "shore_4";
		break;
		
		case "shore_4":
			dialog.text = "А если я дам слово?";
			link.l1 = "Слово, данное 'лягушатнику'? Хм...";
			link.l1.go = "shore_5";
		break;
		
		case "shore_5":
			dialog.text = "Месье, даю вам последний шанс. Или вы немедленно передадите мне интересующую меня дагу, или через короткое время я буду обыскивать ваш труп. Сопротивляться бесполезно - у нас подавляющее численное преимущество.";
			if (CheckAttribute(pchar, "questTemp.Guardoftruth.SanAntonio")) link.l1 = "Вы, право, удивили меня, сеньор. Неужели вы и впрямь решили, что я такой набитый дурак, что полезу в пасть к акуле, не позаботившись прихватить с собой гарпун? Отря-яд, к бою!";
			else link.l1 = "Воюют не числом, а умением, сеньор!";
			link.l1.go = "shore_6";
		break;
		
		case "shore_6":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "goto", "goto5", "none", "", "", "", 10.0);
			if (CheckAttribute(pchar, "questTemp.Guardoftruth.SanAntonio"))
			{
				PlaySound("interface\abordage_wining.wav");
				PlaySound("interface\abordage_wining.wav");
				for(i=1; i<=10; i++)
				{
					sld = characterFromId("GuardOT_Oursoldier_"+i);
					LAi_SetWarriorType(sld);
					ChangeCharacterAddressGroup(sld, "Shore15", "reload", "reload1_back");
					LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
				}
			}
			sld = CharacterFromID("spa_baseprisoner");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			for(i=1; i<=13; i++)
			{
				sld = characterFromId("GOT_spashore_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "GuardOT_DiegoShoreGuardDie");
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "":
			dialog.text = "";
			link.l1 = "";
			link.l1.go = "";
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
	}
}