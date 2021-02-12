// Addon-2016 Jason, французские миниквесты (ФМК) Сент-Кристофер
void ProcessDialogEvent()
{
	ref sld, NPChar;
	aref Link, NextDiag;
	int i;
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
		
		case "seafox":
			PlaySound("VOICE\Russian\military01.wav");
			dialog.text = TimeGreeting()+", капитан. Разрешите представиться - лейтенант "+GetFullName(npchar)+", морская пехота, Сент-Джонс, Антигуа. Хочу обратиться к вам с просьбой об оказании услуги.";
			link.l1 = "Здравствуйте, лейтенант. Моё имя "+GetFullName(pchar)+". Какого рода услуга вам требуется?";
			link.l1.go = "seafox_1";
		break;
		
		case "seafox_1":
			dialog.text = "Позвольте в двух словах объяснить ситуацию. Я и четверо моих подчиненных отправились из Сент-Джонса к берегам острова Синт-Маартен для выполнения задания. По пути шхуну, на борту которой мы находились, захватил внезапно налетевший шторм. И хоть длился он совсем недолго, старая лоханка дала течь, была вынуждена изменить курс и отдать якорь здесь, в Капстервиле. В доках обнаружилось, что её днище сплошь источено червями, и на починку этого гнилого корыта уйдёт уйма времени\nМне и моим людям крайне срочно требуется прибыть на Синт-Маартен, в бухту Гранд Кейс. Окажите помощь, капитан, доставьте мой отряд в указанное место, и как можно скорее. Это же совсем рядом, дня два пути, или даже быстрее при попутном ветре. Ваши услуги будут щедро оплачены.";
			link.l1 = "Военное задание на голландском острове? Гм...";
			link.l1.go = "seafox_2";
		break;
		
		case "seafox_2":
			dialog.text = "Месье, это вас волновать не должно. Франция с Голландией не воюет, вам ничего не угрожает. Вы просто высадите нас в бухте и всё. Ну как, по рукам?";
			link.l1 = "Хорошо, я согласен, здесь действительно недалеко. Что насчёт оплаты?";
			link.l1.go = "seafox_3";
			link.l2 = "Прошу извинить меня, но я направляюсь совсем в другую сторону, и не менее срочно.";
			link.l2.go = "seafox_exit";
		break;
		
		case "seafox_exit":
			dialog.text = "Как скажете, капитан. Буду искать другое судно. Всего доброго!";
			link.l1 = "Прощайте, лейтенант.";
			link.l1.go = "seafox_exit_1";
		break;
		
		case "seafox_exit_1":
			DialogExit();
			chrDisableReloadToLocation = false;
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload4_back", "none", "", "", "", 20.0);
			npchar.lifeday = 0;
		break;
		
		case "seafox_3":
			GiveItem2Character(pchar, "purse2"); 
			Log_Info("Вы получили кошель дублонов");
			dialog.text = "Десять тысяч песо. Вот задаток.";
			link.l1 = "Хорошо. Собирайте ваших людей и поднимайтесь на борт - не будем мешкать.";
			link.l1.go = "seafox_4";
		break;
		
		case "seafox_4":
			dialog.text = "Так точно, капитан!";
			link.l1 = "...";
			link.l1.go = "seafox_5";
		break;
		
		case "seafox_5":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload4_back", "none", "", "", "FMQN_SailMaarten", 10.0);
			AddQuestRecord("FMQ_Nevis", "1");
			pchar.questTemp.FMQN = "begin";
		break;
		
		case "seafox_6":
			PlaySound("VOICE\Russian\QuestMan04.wav");
			dialog.text = "Благодарю за доставку, капитан! Однако, к сожалению, я не могу сейчас с вами полностью рассчитаться: я ожидал увидеть у берегов Синт-Маартена люггер из Сент-Джонса, но, как видите, его нет. Вынужден вас снова просить о помощи: задержитесь на два-три дня в этой бухте, а когда мы вернёмся - доставьте нас на Антигуа. Полковник Фокс не станет скупиться на оплату ваших услуг.";
			link.l1 = "Гм... Я, конечно, рассчитывал на другое...";
			link.l1.go = "seafox_7";
		break;
		
		case "seafox_7":
			dialog.text = "Я понимаю вас, капитан, но увы: у меня нет более денег, кроме тех, что я отдал вам. Обещаю, что на Антигуа вы получите полный расчёт за оба рейса и простой у берегов Синт-Маартена.";
			link.l1 = "Ясно. Выбора у меня нет. Хорошо, лейтенант...";
			link.l1.go = "seafox_8";
		break;
		
		case "seafox_8":
			dialog.text = "Отлично. Мы отправляемся в глубь острова. Ваше ожидание не затянется более, чем на три дня.";
			link.l1 = "Удачи, сэр...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("FMQN_EnglishmanGo");
		break;
		
		case "seafox_9":
			PlaySound("VOICE\Russian\QuestMan04.wav");
			dialog.text = "Гхм... Неожиданная встреча! Я думал, вы сейчас стоите на якоре в бухте Гранд Кейс, капитан...";
			link.l1 = "Тоже не ожидал: лейтенант Каспар Грэттон в мундире голландских колониальных войск!.. Я искал вас, сэр.";
			link.l1.go = "seafox_10";
		break;
		
		case "seafox_10":
			dialog.text = "Мой мундир - это прикрытие... Зачем вы искали нас, капитан?";
			link.l1 = "Чтобы сообщить вам новости. Не очень приятные, кстати.";
			link.l1.go = "seafox_11";
		break;
		
		case "seafox_11":
			dialog.text = "Говорите!";
			link.l1 = "После нашего с вами расставания я отправился в Филипсбург и побеседовал с жителями. Голландцы знают о том, что на Синт-Маартен должна прибыть диверсионная группа англичан для того, чтобы вытащить из тюрьмы нескольких высокопоставленных английских офицеров.";
			link.l1.go = "seafox_12";
		break;
		
		case "seafox_12":
			dialog.text = "Разрази меня гром! Как они сумели узнать об этом?";
			link.l1 = "Говорят, один из ваших пленных проболтался. В обмен на свободу он сдал голандцам план побега. Теперь в Филипсбурге все предупреждены и вас ждут. Воды острова патрулирует военный корвет. Вы в мышеловке, лейтенант.";
			link.l1.go = "seafox_13";
		break;
		
		case "seafox_13":
			dialog.text = RandSwear()+"И что же нам теперь предпринять?.. Гм...";
			link.l1 = "Мне кажется, выход только один: пробирайтесь ночью в бухту Гранд Кейс, поднимайтесь на борт моего корабля и уходим отсюда.";
			link.l1.go = "seafox_14";
		break;
		
		case "seafox_14":
			dialog.text = "Уйти, не выполнив задание? О, нет! Вы просто не знаете, капитан, что значит не выполнить приказ полковника Фокса!";
			link.l1 = "То есть, лучше попасть на виселицу, так?";
			link.l1.go = "seafox_15";
		break;
		
		case "seafox_15":
			dialog.text = "Отнюдь... Капитан, мне нужна ваша помощь. Раз мы уже оказались в одной лодке - давайте выпутываться вместе, ведь если голландцы схватят нас, то и вам может не поздоровиться, как соучастнику.";
			link.l1 = "Внимательно вас слушаю.";
			link.l1.go = "seafox_16";
		break;
		
		case "seafox_16":
			dialog.text = "Пленников надо освободить. Мы уже позаботились о маскировке - мой отряд одет в голландскую форму. Если бы не предательство... мы бы запросто проникли в тюрьму, уложили охрану и всё было бы сделано. Но в тюрьме наверняка будет засада. Поэтому придётся воспользоваться дополнительными ресурсами... Капитан, вам надо отправиться в Филипсбург, в местную церковь, и найти там служку по имени Филип Якобсен. Это надо сделать с восьми до десяти утра, так как потом в церкви его не найти. Филип - наш человек\nСкажете ему пароль: 'Давно ли была исповедь пленных моряков', затем обрисуете ситуацию, и от моего имени потребуете помощи. Потом принесёте его ответ мне. Как видите - ничего сложного или опасного для вас.";
			link.l1 = "Ясно. Хорошо, я сделаю это. Скажите, лейтенант, эта форма... снята с голландского патруля, не иначе?";
			link.l1.go = "seafox_17";
		break;
		
		case "seafox_17":
			dialog.text = "Именно.";
			link.l1 = "А сами голландцы где?";
			link.l1.go = "seafox_18";
		break;
		
		case "seafox_18":
			dialog.text = "Лежат недалеко от пещеры в зарослях связанные. Я подумал, что в случае чего они могут сгодиться как заложники.";
			link.l1 = "Понятно. Ладно, отправляюсь в город. Ждите меня тут и не высовывайтесь особо - голландцы рейдируют не только море, но и джунгли.";
			link.l1.go = "seafox_19";
		break;
		
		case "seafox_19":
			dialog.text = "Торопитесь, капитан!..";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("FMQN_ToChurch");
		break;
		
		case "seafox_20":
			PlaySound("VOICE\Russian\soldier_common_4.wav");
			dialog.text = "Опять? Капитан, да что вы тут ошиваетесь? Идите в город, а так вы только внимание кого не следует привлечёте...";
			link.l1 = "Я только что из города. В какие игры вы играете?";
			link.l1.go = "seafox_21";
		break;
		
		case "seafox_21":
			dialog.text = "Не понял - о чём вы?";
			link.l1 = "Я сказал - я только что из города. Я был в церкви. И мне там ответили, что никакого служки по имени Филип Якобсен в их приходе нет.";
			link.l1.go = "seafox_22";
		break;
		
		case "seafox_22":
			dialog.text = "Он там бывает по утрам, я же говорил...";
			link.l1 = "Карамба! А мне сказали, что его нет там, ни по утрам, ни по вечерам! "+RandSwear()+" И зачем я только связался с вами! "+RandSwear()+"";
			link.l1.go = "seafox_23";
		break;
		
		case "seafox_23":
			dialog.text = "Да что вы разорались как баба старая, капитан? Уймитесь!";
			link.l1 = ""+RandSwear()+"";
			link.l1.go = "seafox_24";
		break;
		
		case "seafox_24":
			PlaySound("Ambient\Jail\chain.wav");
			PlaySound("Ambient\Land\door_001.wav");
			dialog.text = "А?! А ну, заткнитесь! Что это, вы слышали?..";
			link.l1 = "";
			link.l1.go = "seafox_25";
		break;
		
		case "seafox_25":
			PlaySound("Ambient\Land\cough_01.wav");
			dialog.text = "Чёрт побери, кто-то лезет сюда!.. Ты привёл голландцев, каналья! Предатель!";
			link.l1 = ""+RandSwear()+"!!";
			link.l1.go = "exit";
			AddDialogExitQuest("FMQN_HollandBattleFight");
		break;
		
		case "seafox_26":
			pchar.quest.FMQN_fail1.over = "yes";
			PlaySound("VOICE\Russian\QuestMan04.wav");
			dialog.text = "Как успехи, капитан?";
			link.l1 = "Встретился я с вашим агентом. Он всё организовал: сегодня вечером в тюрьму будет доставлено вино, разбавленное каким-то цыганским зельем, вызывающим глубокий сон. Так что ночью вам нужно идти в город и вытаскивать своих пленных. Кстати, помощь вам обошлась в два с половиной десятка дублонов - надеюсь, это будет учтено при окончательном расчёте.";
			link.l1.go = "seafox_27";
		break;
		
		case "seafox_27":
			dialog.text = "За деньги не волнуйтесь. Капитан, я попрошу вас принять участие в этой операции - сопроводите нас до тюрьмы. Вы уже не раз бывали в Филипсбурге, и наверняка знаете расположение зданий. В саму тюрьму ходить не нужно - мы всё сделаем сами. Просто помогите найти дорогу.";
			link.l1 = "Эх... Подведёте вы меня под монастырь, лейтенант! Но ладно, раз я уже начал вам помогать - помогу.";
			link.l1.go = "seafox_28";
		break;
		
		case "seafox_28":
			dialog.text = "Вы не пожалеете об этом. У вас корабль сейчас в бухте Гранд Кейс?";
			if (pchar.location.from_sea == "Shore40")
			{
				link.l1 = "Да.";
				link.l1.go = "seafox_29";
			}
			else
			{
				link.l1 = "Нет.";
				link.l1.go = "seafox_29x";
			}
		break;
		
		case "seafox_29":
			dialog.text = "Отлично. Тогда подготовьтесь к походу и встречайте нас в джунглях у городских ворот в одиннадцать вечера.";
			link.l1 = "Договорились. До встречи.";
			link.l1.go = "seafox_30";
		break;
		
		case "seafox_29x":
			dialog.text = "Тогда поставьте судно на якорь в бухте - уходить будем сразу, через джунгли к морю и на ваш корабль. Отплывать из порта или залива Симпсон опасно - можно попасть под огонь форта, если поднимется тревога. А затем подготовьтесь к походу и встречайте нас в джунглях у городских ворот в одиннадцать вечера.";
			link.l1 = "Договорились. До встречи.";
			link.l1.go = "seafox_30";
		break;
		
		case "seafox_30":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			AddDialogExitQuestFunction("FMQN_EnglandPrepare");
		break;
		
		case "seafox_31":
			PlaySound("VOICE\Russian\Gr_hovernor01.wav");
			dialog.text = "Вы готовы, капитан?";
			link.l1 = "Да.";
			link.l1.go = "seafox_32";
		break;
		
		case "seafox_32":
			dialog.text = "Тогда не будем терять времени. Вперёд!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("FMQN_EnglandReload");
		break;
		
		case "seafox_33":
			dialog.text = "Пс-с-т-т... Капитан! Чш-ш-ш... Дело сделано! Теперь быстро уходим!..";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuest("FMQN_EnglandRunToJungle");
		break;
		
		case "seafox_34":
			dialog.text = "Всё прошло успешно. Вы молодец, капитан. Теперь осталось последнее - унести ноги с этого острова. Быстрее отправляемся в бухту Гранд Кейс!";
			link.l1 = "Идём!";
			link.l1.go = "exit";
			AddDialogExitQuest("FMQN_EnglandRunToShore");
		break;
		
		case "seafox_35":
			PlaySound("VOICE\Russian\QuestMan05.wav");
			dialog.text = "Спасибо за вашу помощь, капитан! Вы вели себя, как настоящий герой! Я прошу вас погостить один день в нашей колонии, пока я сделаю доклад полковнику Фоксу, а завтра прошу вас явиться к нему на приём. Если вы не знаете - штаб-квартира полковника Фокса находится в резиденции губернатора, налево.";
			link.l1 = "Хорошо, лейтенант. Вы уж там постарайтесь... за меня перед вашим начальством. Из-за вас меня голландцы теперь не жалуют";
			link.l1.go = "seafox_36";
		break;
		
		case "seafox_35x":
			PlaySound("VOICE\Russian\QuestMan05.wav");
			dialog.text = "Спасибо за вашу помощь, капитан! Вы вели себя, как настоящий герой! Очень жаль лейтенанта Каспара Грэттона, но он погиб, как настоящий солдат и патриот Англии. Я прошу вас погостить один день в нашей колонии, пока я сделаю доклад полковнику Фоксу, а завтра прошу вас явиться к нему на приём. Если вы не знаете - штаб-квартира полковника Фокса находится в резиденции губернатора, налево.";
			link.l1 = "Хорошо, сэр. Вы уж там постарайтесь... за меня перед мистером Фоксом. Мне ведь теперь проблемы с голландскими властями решать придётся.";
			link.l1.go = "seafox_36";
		break;
		
		case "seafox_36":
			dialog.text = "Не беспокойтесь, я опишу ваши действия в докладе в самом лучшем виде. Был рад знакомству, сэр!";
			link.l1 = "...";
			link.l1.go = "seafox_37";
		break;
		
		case "seafox_37":
			DialogExit();
			npchar.lifeday = 0;
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload3_back", "none", "", "", "", -1);
			pchar.quest.FMQN_eng_reward.win_condition.l1 = "Timer";
			pchar.quest.FMQN_eng_reward.win_condition.l1.date.hour  = 6.0;
			pchar.quest.FMQN_eng_reward.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.FMQN_eng_reward.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.FMQN_eng_reward.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.FMQN_eng_reward.function = "FMQN_EnglandReward";
			AddQuestRecord("FMQ_Nevis", "28");
		break;
		
		case "soldier":
			PlaySound("VOICE\Russian\soldier_common_2.wav");
			dialog.text = "Капитан "+GetFullName(pchar)+"?";
			link.l1 = "Кхм... Да, это я. Чем могу служить?";
			link.l1.go = "soldier_1";
		break;
		
		case "soldier_1":
			dialog.text = "В портовом управлении сообщили, что ваш корабль недавно прибыл в порт. Его Светлость губернатор Филипсбурга, минхер Мартин Томас, желает с вами побеседовать.";
			link.l1 = "Что-то я не понимаю... Я арестован? С какой стати?";
			link.l1.go = "soldier_2";
		break;
		
		case "soldier_2":
			dialog.text = "Никак нет, минхер капитан, вы не арестованы. Губернатор отдал приказ приглашать к нему всех капитанов кораблей, отдающих якорь у нас в порту, в связи с особой ситуацией. Пройдёмте!";
			link.l1 = "А, ну тогда хорошо... Иду!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("FMQN_ReloadToGovernor");
		break;
		
		case "hol_officer":
			PlaySound("VOICE\Russian\hol_gov_complete.wav");
			dialog.text = "Итак, минхер, показывайте дорогу туда, где вы видели подозрительных личностей.";
			link.l1 = "Нам надо к пещере, что находится в джунглях. Они там.";
			link.l1.go = "hol_officer_1";
		break;
		
		case "hol_officer_1":
			dialog.text = "Ступайте вперёд, мы за вами!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuest("FMQN_HollandBattleMarch");
		break;
		
		case "hol_officer_2":
			PlaySound("VOICE\Russian\hol_gov_quest.wav");
			dialog.text = "Стойте, капитан! Говорите, что встретили шпионов там - у входа в пещеру?";
			link.l1 = "Да. Но я краем глаза видел, как они после беседы со мной направились внутрь пещеры.";
			link.l1.go = "hol_officer_3";
		break;
		
		case "hol_officer_3":
			dialog.text = "Скорее всего, они в ней и засели. Если мы сунемся всем отрядом ко входу - нас наверняка заметят, займут удобные позиции в узких проходах пещеры и бой будет трудным. Надо сделать иначе. Вы, капитан, отправитесь туда один - подозрений вы не вызовите, а я с частью отряда пройду немного дальше. Там, за поворотом - есть сухой колодец, он ведёт прямиком в эту пещеру. Из колодца негодяи нас не увидят\nВы войдёте в пещеру, и если шпионы там - отвлечёте их внимание каким-либо глупым вопросом, а потом громко выругайтесь, как можно громче. Едва мы это услышим - как тут же по верёвке десантируемся в колодец и накроем мерзавцев. Два человека следом за вами пройдут ко входу в пещеру и перекроют шпионам путь к бегству. Возьмём их в клещи.";
			link.l1 = "Гм... Кажется, шпионы начнут в первую очередь рубить именно меня...";
			link.l1.go = "hol_officer_4";
		break;
		
		case "hol_officer_4":
			dialog.text = "Не бойтесь, капитан: ваша задача - крикнуть погромче при обнаружении диверсантов, чтобы мы услышали из колодца. А если они нападут на вас - бегите со всех ног и орите во всю глотку. Не беспокойтесь, мои люди знают своё дело и уложат противника.";
			link.l1 = "Хорошо. Ну... я пошёл.";
			link.l1.go = "exit";
			AddDialogExitQuest("FMQN_HollandBattlePosition");
		break;
		
		case "hol_officer_5":
			PlaySound("VOICE\Russian\hol_gov_common.wav");
			dialog.text = "Крепкие, мерзавцы, оказались... Отлично сработали, капитан! Поздравляю. Английские собаки ликвидированы, комендант и губернатор будут довольны.";
			link.l1 = "Как-то вы немного задержались, минхер...";
			link.l1.go = "hol_officer_6";
		break;
		
		case "hol_officer_6":
			dialog.text = "Верёвка подлая рваться стала, когда начали спуск... из-за этого и замешкались немного.";
			link.l1 = "Недалеко от пещеры где-то в зарослях лежат ваши патрульные. Поищите их - может, ещё живы.";
			link.l1.go = "hol_officer_7";
		break;
		
		case "hol_officer_7":
			dialog.text = "Я займусь этим немедленно. А вы отправляйтесь в город и отдыхайте. Завтра утром мой доклад будет лежать на столе у губернатора - пожалуйте к нему на приём за честно заработанной наградой.";
			link.l1 = "Обязательно. Удачи, минхер.";
			link.l1.go = "exit";
			AddDialogExitQuest("FMQN_HollandBattleRest");
		break;
		
		case "monk":
			pchar.questTemp.FMQN = "way_eng_2";
			dialog.text = "Чем я могу помочь тебе, сын мой?";
			link.l1 = "Я бы хотел узнать, давно ли была исповедь пленных моряков.";
			link.l1.go = "monk_1";
		break;
		
		case "monk_1":
			dialog.text = "Вчерашним вечером, сын мой. Ч-ш-ш... Говори тише... (шёпотом) Полагаю, вы уже в курсе, что было совершено предательство, и вас ждут?";
			link.l1 = "Безусловно. Иначе бы я тут не стоял. Отряд лейтенанта Каспара Грэттона сейчас находится в джунглях. Все одеты в форму голландских военных, но в тюрьме ждёт засада. Меня прислали за помощью к вам.";
			link.l1.go = "monk_2";
		break;
		
		case "monk_2":
			dialog.text = "Я молился ежедневно о том, чтобы ваше неведение не завело вас в ловушку. План у меня давно созрел, но для его реализации мне не хватает средств: нужны две дюжины золотых дублонов.";
			link.l1 = "Что за план - не поведаете ли мне?";
			link.l1.go = "monk_3";
		break;
		
		case "monk_3":
			dialog.text = "Конечно. Солдатам в тюрьме, в связи с ожиданием английских шпионов, добавили в довольствие ежевечернюю порцию хорошего вина для поддержания морального духа. Его доставляют со склада, куда у меня есть доступ. А у цыганки-торговки, которая мне кое-чем обязана, я могу достать зелье, погружающее употребившего в глубокий сон на несколько часов. Я должен купить несколько бутылок хорошего вина, подмешать в них зелье цыганки, а затем подменить бутылки на складе. Вот для чего мне нужны деньги.";
			if (GetCharacterItem(pchar, "gold_dublon") >= 24)
			{
				link.l1 = "У меня есть с собой нужная сумма. Держите.";
				link.l1.go = "monk_4";
			}
			else
			{
				link.l1 = "Я принесу их!..";
				link.l1.go = "monk_wait";
			}
		break;
		
		case "monk_wait":
			DialogExit();
			sld.dialog.currentnode = "monk_repeat";
		break;
		
		case "monk_repeat":
			dialog.text = "Ты принёс две дюжины дублонов, сын мой?";
			if (GetCharacterItem(pchar, "gold_dublon") >= 24)
			{
				link.l1 = "Да. Держите.";
				link.l1.go = "monk_4";
			}
			else
			{
				link.l1 = "Скоро я соберу нужное количество, ждите...";
				link.l1.go = "monk_wait";
			}
		break;
		
		case "monk_4":
			RemoveItems(pchar, "gold_dublon", 24);
			Log_Info("Вы отдали 24 дублона");
			PlaySound("interface\important_item.wav");
			dialog.text = "Прекрасно. Приходите завтра в это же время - я сообщу вам результаты.";
			link.l1 = "Хорошо...";
			link.l1.go = "monk_5";
		break;
		
		case "monk_5":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			AddQuestRecord("FMQ_Nevis", "18");
			pchar.quest.FMQN_monk.win_condition.l1 = "Timer";
			pchar.quest.FMQN_monk.win_condition.l1.date.hour  = 6.0;
			pchar.quest.FMQN_monk.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.FMQN_monk.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.FMQN_monk.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.FMQN_monk.function = "FMQN_EnglandMonkPlan";
			pchar.quest.FMQN_fail.win_condition.l1 = "Timer";
			pchar.quest.FMQN_fail.win_condition.l1.date.hour  = 11.0;
			pchar.quest.FMQN_fail.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.FMQN_fail.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.FMQN_fail.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.FMQN_fail.function = "FMQN_EnglandFail";
			pchar.questTemp.FMQN = "way_eng_3";
		break;
		
		case "monk_6":
			pchar.quest.FMQN_fail.over = "yes";
			dialog.text = "Приветствую тебя, сын мой.";
			link.l1 = "И вам доброго утра, отче. Есть у вас какие-нибудь новости?";
			link.l1.go = "monk_6x";
		break;
		
		case "monk_6x":
			dialog.text = "Да. Всё готово. Вино 'заряжено' и нужные бутылки сегодня вечером попадут тюремной страже. Ужин у них в девять вечера, так что к полуночи вся охрана уже будет мирно спать на посту. Это ваша единственная возможность выполнить задачу: не справитесь - второго шанса не будет. Сегодня ночью или никогда. Будьте осторожны - хоть у вас и голландские мундиры, но и патруль не дурак. Держитесь от дозорных в городе подальше.";
			link.l1 = "Всё ясно. Не буду терять времени! До свидания.";
			link.l1.go = "monk_7";
		break;
		
		case "monk_7":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeday = 0;
			AddQuestRecord("FMQ_Nevis", "20");
			sld = CharacterFromID("FMQN_seafox_1");
			sld.dialog.currentnode = "seafox_26";
			LAi_CharacterEnableDialog(sld);
			sld.talker = 9;
			pchar.quest.FMQN_fail1.win_condition.l1 = "Timer";
			pchar.quest.FMQN_fail1.win_condition.l1.date.hour  = 20.0;
			pchar.quest.FMQN_fail1.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 0);
			pchar.quest.FMQN_fail1.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 0);
			pchar.quest.FMQN_fail1.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 0);
			pchar.quest.FMQN_fail1.function = "FMQN_EnglandFail";
			pchar.questTemp.FMQN = "way_eng_4";
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
