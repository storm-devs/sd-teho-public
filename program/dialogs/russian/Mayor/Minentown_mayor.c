void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i;
	string sLoc;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (LAi_grp_playeralarm > 0)
			{
       			dialog.text = NPCharRepPhrase(pchar, 
					LinkRandPhrase("Вы посмели явиться сюда?! Смелый шаг...", "Как эти бездельники допустили, чтобы ко мне ворвался враг?! Уму непостижимо...", "Да уж, моя охрана немногого стоит, раз "+ GetSexPhrase("какой-то бездельник","какая-то бездельница") +" бегает в моей резиденции..."), 
					LinkRandPhrase("Что тебе нужно, "+ GetSexPhrase("негодяй","мерзавка") +"?! Мои солдаты уже взяли твой след, далеко тебе не уйти"+ GetSexPhrase(", грязный пират","") +"!", "Грязн"+ GetSexPhrase("ый","ая") +" убийца, вон из моей резиденции! Стража!!", "Я не боюсь тебя, мерзав"+ GetSexPhrase("ец","ка") +"! Скоро тебя повесят, далеко тебе не уйти..."));
				link.l1 = NPCharRepPhrase(pchar,
					RandPhraseSimple("Солдатня мало чего стоит...", "Им меня ни за что не поймать."), 
					RandPhraseSimple("Заткни свою пасть, " + GetWorkTypeOfMan(npchar, "") + ", а не то вырву твой поганый язык!", "Вот что я тебе скажу, приятель: сиди тихо, и будешь жить..."));
				link.l1.go = "fight";
				break;
			}
			if (GetNationRelation2MainCharacter(sti(NPChar.nation)) == RELATION_ENEMY)
			{
    			dialog.text = "Враг в резиденции! Тревога!!";
				link.l1 = "А-ать, дьявол!";
				link.l1.go = "fight"; 
				break;
			}			
			if (npchar.quest.meeting == "0")
			{
				dialog.text = TimeGreeting() + " сударь. Я - "+GetFullName(npchar)+", комендант рудника Лос-Текес подданства " + NationKingsName(npchar)+". А теперь соблаговолите сообщить цель вашего визита, " + GetAddress_Form(NPChar) + ".";
				link.l1 = "Я здесь впервые, и хотел бы немного больше узнать об этом поселении, правилах, действующих здесь...";
				link.l1.go = "info";
				link.l2 = "Я просто зашел с вами поздороваться и уже ухожу.";
				link.l2.go = "exit";
				npchar.quest.meeting = "1";
				break;
			}
			dialog.text = "Это опять вы, сударь? Вы еще что-то хотели?";
			link.l1 = "Да нет, ничего. Я уже ухожу.";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
		case "info":
			dialog.text = "Весьма похвально, что вы столь дисциплинированы. Что же, я введу вас в курс дела, раз это так вам интересно\nРудник Лос-Текес находится во владениях испанской короны. Здесь производится добыча неочищенной серебряной и золотой руды, а также золотых и серебряных самородков. Все добытое золото и серебро принадлежит Испании и в дальнейшем вывозится под усиленной охраной в Старый Свет\nРудник надежно охраняется, здесь постоянно присутствует гарнизон отборных испанских солдат. Пираты неоднократно предпринимали попытки ограбить наш рудник, и все они закончились плачевно... для них\nКак вы могли видеть, рудник представляет собой небольшой город. У нас есть магазин, таверна. В нашем магазине вы можете приобрести золотые и серебряные слитки по сходной цене. Кроме того, наш интендант, он же торговец в магазине, сможет продать вам и другие интересные металлы и руду\nНа руднике работают в основном заключенные, меньше - черные рабы. Как вы понимаете, мы постоянно нуждаемся в рабочих руках - не проходит и дня, чтобы кто-то из этих чертовых каторжников не умер\nТак что если вы сможете привезти нам рабов - мы купим их у вас в обмен на самородки. По этому вопросу вам нужно будет обратиться непосредственно к старшему горному инженеру, его всегда можно найти в шахте\nПо вопросам поведения на руднике: не устраивайте ссор или дуэлей, это может закончиться для вас плохо, так как тюрьмы у нас нет, зато есть военно-полевой суд. Не пытайтесь что-нибудь украсть, или вынести из шахты тайком самородки - это карается у нас беспощадно\nВот в принципе и все. Соблюдайте эти несложные правила и никаких проблем у вас не будет. По руднику можете передвигаться свободно. Обязательно посетите таверну - там с моего ведома предоставляются определенные... услуги. Добро пожаловать!";
			link.l1 = "Спасибо!";			
			link.l1.go = "exit";
		break;

 		case "Exit":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
		break;

		// ============== Грабеж среди бела дня, попытка залезть в сундуки =========================
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("Грабеж среди бела дня!!! Это что же такое делается?! Ну, погоди, "+ GetSexPhrase("приятель","подруга") +"...", "Эй, ты чего это там копаешься?! Никак, вздумал"+ GetSexPhrase("","а") +" ограбить меня? Ну, тогда тебе конец...", "Постой, ты куда это полез"+ GetSexPhrase("","ла") +"? Да ты вор"+ GetSexPhrase("","овка") +", оказывается! Ну, считай, что ты приплыл"+ GetSexPhrase("","а") +", родн"+ GetSexPhrase("ой","ая") +"...");
			link.l1 = LinkRandPhrase("Дьявол!!", "Каррамба!!", "А-ать, черт!");
			link.l1.go = "PL_Q3_fight";
		break;
		
		case "fight":
            Pchar.quest.ArestInResidenceEnd.win_condition.l1          = "ExitFromLocation";
		    Pchar.quest.ArestInResidenceEnd.win_condition.l1.location = Pchar.location;
		    Pchar.quest.ArestInResidenceEnd.win_condition             = "ArestInResidenceEnd";
		    Pchar.quest.ArestInResidenceEnd.ResidenceLocation = Pchar.location;
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;

			LAi_LockFightMode(Pchar, true); // ножками путь убегает
		    LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
		    LAi_group_Attack(NPChar, Pchar); // не работает на бессмертного мера :(
			i = GetCharIDXByParam("CityType", "location", Pchar.location); // фантом солдат
			if (i != -1)
			{
			    LAi_group_Attack(&Characters[i], Pchar);
			}
		break;
	}
}
