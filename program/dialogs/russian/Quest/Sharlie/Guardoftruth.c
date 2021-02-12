// диалоги НПС по квесту 'В поисках Стража Истины'
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i, iTemp;
	string sTemp;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "Что вам угодно?";
			link.l1 = "Ничего.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		// пленный испанец
		case "spa_prisoner":
			PlaySound("VOICE\Russian\Ransack_1.wav");
			dialog.text = "Что вам от меня нужно? Опять допрос?";
			link.l1 = "Сеньор, как ваше имя?";
			link.l1.go = "spa_prisoner_1";			
		break;
		
		case "spa_prisoner_1":
			dialog.text = "Да какая к черту вам разница, кого вам расстреливать или вешать? Я имел неосторожность угодить к вам в лапы, и...";
			link.l1 = "Сеньор, повторяю еще раз: назовите ваше имя. Я не могу разговаривать с человеком, не зная, как его зовут.";
			link.l1.go = "spa_prisoner_2";			
		break;
		
		case "spa_prisoner_2":
			dialog.text = "Дон "+GetFullName(npchar)+". Вас устраивает мой ответ? А с кем я имею честь вести беседу?";
			link.l1 = "Меня зовут "+GetFullName(pchar)+". Никогда обо мне не слышали?";
			link.l1.go = "spa_prisoner_3";			
		break;
		
		case "spa_prisoner_3":
			dialog.text = "Нет, черт побери! Я не обязан знать весь...";
			link.l1 = "Довольно. Обойдемся без оскорблений и постараемся вести себя, как культурные люди. От того, что именно вы сможете мне сообщить, будет зависеть ваша судьба. Если вы скажете хоть что-то меня интересующее - я походатайствую о вашей выдаче в мое распоряжение, и вы сможете избежать расстрела или виселицы, которая вас ждет.";
			link.l1.go = "spa_prisoner_4";			
		break;
		
		case "spa_prisoner_4":
			dialog.text = "Ну что же, тогда я готов. Что именно вы хотите узнать, сударь?";
			link.l1 = "Кто и зачем организовал столь масштабное нападение на Сен-Пьер?";
			link.l1.go = "spa_prisoner_5";			
		break;
		
		case "spa_prisoner_5":
			dialog.text = "Приказ был отдан доном Рамоном де-Мендосой-и-Риба, главнокомандующим гарнизоном острова Провиденсия. Им же была снаряжена эскадра. Цель - захват материальных ценностей французской колонии.";
			link.l1 = "Какова была ваша непосредственная задача при штурме города? Лично ваша?";
			link.l1.go = "spa_prisoner_6";			
		break;
		
		case "spa_prisoner_6":
			dialog.text = "Я - командир ударной группы, в нашу задачу входил захват форта и обеспечение безопасной высадки десанта в город. Также мой отряд принимал участие в атаке на сам город.";
			link.l1 = "Вы были осведомлены о ценностях, находящихся в городе? Об их размере, качественном составе?";
			link.l1.go = "spa_prisoner_7";			
		break;
		
		case "spa_prisoner_7":
			dialog.text = "Точных сведений у нас не было, но барон де-Мендоса-и-Риба утверждал, что в подземельях форта хранится серебро, а на портовых складах - стратегическое сырье: бакаут и корабельный шелк.";
			link.l1 = "Вы нашли эти ценности?";
			link.l1.go = "spa_prisoner_8";			
		break;
		
		case "spa_prisoner_8":
			dialog.text = "Нет. Ни того, ни другого обнаружено не было. Склады были заполнены обычным колониальным товаром, а подземелья форта - порохом, оружием и боеприпасами. Но мы не успели произвести тщательные поиски, ибо нагрянуло подкрепление французов и мы были вынуждены принять бой.";
			link.l1 = "Отсутствие ценных товаров вам не показалось странным?";
			link.l1.go = "spa_prisoner_9";			
		break;
		
		case "spa_prisoner_9":
			dialog.text = "Показалось, но я не имею привычки обсуждать приказы.";
			link.l1 = "Я вам скажу следующее: в форте Сен-Пьера никогда не было серебра, а на складах - бакаута и шелка. А вот теперь хорошо подумайте, офицер, перед тем как отвечать, ибо если ваш ответ мне не понравится, я развернусь и уйду, оставив вас своей судьбе... весьма печальной судьбе.";
			link.l1.go = "spa_prisoner_10";			
		break;
		
		case "spa_prisoner_10":
			dialog.text = "Я вас внимательно слушаю.";
			link.l1 = "Я не верю, что единственной целью налета был банальный грабеж. Сен-Пьер - далеко не такая богатая колония, чтобы присылать сюда эскадру во главе с линейным кораблем. Наверняка вы, или ваш командир, или кто-то еще, имел дополнительные приказы или указания. Какие именно? Хорошенько подумайте, прежде чем отвечать...";
			link.l1.go = "spa_prisoner_11";			
		break;
		
		case "spa_prisoner_11":
			dialog.text = "";
			link.l1 = "Молчите? Хорошо. Думайте, я подожду.";
			link.l1.go = "spa_prisoner_12";			
		break;
		
		case "spa_prisoner_12":
			dialog.text = "Сеньор, от моего ответа будет зависеть моя дальнейшая судьба?";
			link.l1 = "Именно!";
			link.l1.go = "spa_prisoner_13";			
		break;
		
		case "spa_prisoner_13":
			dialog.text = "У меня есть кое-что... Но вы должны поклясться мне, что заберете меня отсюда и в дальнейшем передадите за выкуп Испании.";
			link.l1 = "Если вы скажете нечто заслуживающее внимания - клянусь, что вы будете доставлены на борт моего корабля и избежите казни.";
			link.l1.go = "spa_prisoner_14";			
		break;
		
		case "spa_prisoner_14":
			dialog.text = "Хорошо. Дон Диего де Монтойя инструктировал штурмовые роты, что нужно в обязательном порядке найти и взять в плен человека по имени Мигель Дичозо, который находится где-то в Сен-Пьере под защитой властей.";
			link.l1 = "Продолжайте. Кто такой Диего де Монтойя?";
			link.l1.go = "spa_prisoner_15";			
		break;
		
		case "spa_prisoner_15":
			dialog.text = "Непосредственный руководитель экспедиции. Он сумел скрыться после прихода на помощь вашей эскадры...";
			link.l1 = "Кто он такой, этот дон Диего?";
			link.l1.go = "spa_prisoner_16";			
		break;
		
		case "spa_prisoner_16":
			dialog.text = "Я знаю лишь то, что он доверенное лицо барона де-Мендосы-и-Риба, его правая рука и агент по особо важным поручениям.";
			link.l1 = "Интересно... Ну а кто же этот Мигель Дичозо, ради которого, судя по всему, и была устроена вся эта заваруха? Видать, большая шишка?";
			link.l1.go = "spa_prisoner_17";			
		break;
		
		case "spa_prisoner_17":
			dialog.text = "Вы помните о своей клятве, сеньор?";
			link.l1 = "Да. Я подтверждаю, что если вы продолжите ваш рассказ, вы будете доставлены как важный свидетель на мое судно, а в дальнейшем... в общем, я найду способ отправить вас в испанское поселение. Но не раньше, чем вы поведаете все, что меня может заинтересовать.";
			link.l1.go = "spa_prisoner_18";			
		break;
		
		case "spa_prisoner_18":
			dialog.text = "Мигель Дичозо - бывший соратник барона, однако, как говорят, он предал его. Сеньор де-Мендоса-и-Риба хочет найти его, причем живым, ибо нам был отдан приказ ни в коем случае не убивать Дичозо.";
			link.l1 = "Дичозо - испанец?";
			link.l1.go = "spa_prisoner_19";			
		break;
		
		case "spa_prisoner_19":
			dialog.text = "Да. Дон Диего де Монтойя дал приблизительное описание и потребовал всех подпадающих под него лиц доставлять именно к нему. Но за то время, что мы находились в городе, у нас даже не было времени разыскивать Мигеля.";
			link.l1 = "Вы знали Дичозо лично?";
			link.l1.go = "spa_prisoner_20";			
		break;
		
		case "spa_prisoner_20":
			dialog.text = "Нет. Но в моем отряде были люди, знавшие его в лицо. Все они мертвы.";
			link.l1 = "Какого рода предательство совершил Дичозо в отношении вашего дона Мендосы, что он прислал за ним целую эскадру? Вам это известно?";
			link.l1.go = "spa_prisoner_21";			
		break;
		
		case "spa_prisoner_21":
			dialog.text = "В общих чертах - да. Барон прибыл на Карибы из Европы относительно недавно. В его задачу входило обеспечение безопасности передвижения испанских кораблей с ценными грузами, однако вместо этого он занялся поисками индейских сокровищ. Он решил, что где-то в глубине Юкатана находится старый город индейцев майя-ица - Тайясаль, в котором полно золота\nБарон отправил несколько экспедиций на поиск этого города, но все они, как одна, канули безвестно в дикой сельве. Без сомнения, их всех перебили воинственные индейцы ица, обитающие в тех краях\nВ конце-концов его многочисленные провалы и бессмысленная гибель солдат вызвали недовольство инквизитора - отца Винсенто, и он доложил об этом в Мадрид. Барону запретили заниматься поисками мифического города. Вот тут-то и появился Мигель Дичозо\nОни организовали экспедицию, во время которой, как это ни странно, были найдены руины старого индейского города и куча золота и драгоценных камней. Однако на обратном пути на экспедицию напали индейцы москитос\nОтряд сумел отбиться от них и дойти до побережья, однако все, кроме Мигеля, умерли - оружие индейцев было отравлено каким-то туземным ядом - даже небольшая царапина приводила через несколько дней к смерти. Дичозо же с сокровищами вернулся на Провиденсию\nВот так было шума! Барон несказанно радовался, отправил срочную депешу в Мадрид и отцу Винсенто в Сантьяго - чтобы позлить того. Затем был снаряжен фрегат с этими сокровищами для отправки в Испанию. Сопровождать сокровища отправился Мигель Дичозо...";
			link.l1 = "И он, конечно, их не довез?";
			link.l1.go = "spa_prisoner_22";			
		break;
		
		case "spa_prisoner_22":
			dialog.text = "Именно! Фрегат бесследно исчез вместе со всем грузом и экипажем, включая Дичозо, так и не дойдя до Испании. Барон был просто в ярости, потому что он опять опозорился перед Эскориалом на радость отцу Винсенто. Он словно... в общем, Мигель Дичозо стал его навязчивой идеей...";
			link.l1 = "Так быть может, фрегат просто попал в шторм и утонул? Был захвачен пиратами?";
			link.l1.go = "spa_prisoner_23";			
		break;
		
		case "spa_prisoner_23":
			dialog.text = "Барон в запале как-то утверждал, что уверен в том, что Дичозо его предал. Подробностей я не знаю. Потом появился дон Диего де Монтойя, который, как я понимаю, и сообщил барону, что Мигель Дичозо может быть в Сен-Пьере.";
			link.l1 = "Хм. Занятно. Опять эти индейские сокровища. Что-то все так подозрительно на них завязано... Значит, Дичозо так и не нашли?";
			link.l1.go = "spa_prisoner_24";			
		break;
		
		case "spa_prisoner_24":
			dialog.text = "Нет. И я не удивлюсь, если его тут и не было. Барон просто одержим мыслью схватить Дичозо, да так, что верит самым невероятным фантазиям.";
			link.l1 = "Скажите, "+npchar.name+", а откуда дон Мендоса узнал про этот... как его... Тайясаль? Он же не во сне его увидел, ведь так? Были какие-то факты, или что-то еще?";
			link.l1.go = "spa_prisoner_25";			
		break;
		
		case "spa_prisoner_25":
			dialog.text = "О предположительном существовании Тайясаля и индейских сокровищ сообщил в Мадрид инквизитор, отец Винсенто. Откуда ему это стало известно - понятия не имею. Вот после его депеши здесь и появился дон Рамон Мендоса, на нашу голову...";
			link.l1 = "Интересно получается. Отец Винсенто сам выдвинул теорию сущестования Тайясаля, сам сообщил об этом в Мадрид, и сам же начал вставлять палки в колеса барону, сообщая о его неудачах...";
			link.l1.go = "spa_prisoner_26";			
		break;
		
		case "spa_prisoner_26":
			dialog.text = "Ну вы же должны знать этих святых отцов... Он же не просто так сообщал в Мадрид. Какую-то выгоду он преследовал, но приезд барона видимо, не входил в его планы. Впрочем, мне об этом ничего не известно. Никогда не имел желания связываться с инквизицией.";
			link.l1 = "Хорошо. Вы собщили много интересного, "+npchar.name+", и я вас забираю отсюда. Вы мне еще пригодитесь. А пока... дайте немного подумать и проанализировать ваши слова...";
			link.l1.go = "spa_prisoner_27";			
		break;
		
		case "spa_prisoner_27":
			DialogExit();
			pchar.questTemp.Guardoftruth = "think";
			LAi_CharacterDisableDialog(npchar);//запрет диалога
			LAi_SetActorType(pchar);
			LAi_ActorGoToLocator(pchar, "goto", "goto3", "GuardOT_MCthink", -1);
		break;
		
		case "spa_prisoner_28":
			PlaySound("VOICE\Russian\Ransack_2.wav");
			dialog.text = "Что скажете? Вы выполните свое обещание?";
			link.l1 = "Я всегда выполняю свои обещания. Сегодня ваш счастливый день, "+npchar.name+". Вы отправляетесь со мной на Кубу, в Сантьяго. Подробнее я объясню вам по прибытии. А пока - добро пожаловать на борт. Вас препроводят в порт и доставят на мой корабль.";
			link.l1.go = "spa_prisoner_29";			
		break;
		
		case "spa_prisoner_29":
			dialog.text = "Благодарю, капитан. Рад, что вы оказались человеком слова.";
			link.l1 = "Благодарность выскажете позднее. Вы отправитесь в путь в качестве пассажира, но под замком: уж не обессудьте, но вы мне очень дороги.";
			link.l1.go = "spa_prisoner_30";			
		break;
		
		case "spa_prisoner_30":
			dialog.text = "Можете не утруждаться, капитан. Даю слово, что не приму никаких попыток к бегству.";
			link.l1 = "Береженого Бог бережет. Увидимся на корабле.";
			link.l1.go = "spa_prisoner_31";			
		break;
		
		case "spa_prisoner_31":
			DialogExit();
			pchar.questTemp.Guardoftruth = "cuba";
			LAi_CharacterDisableDialog(npchar);//запрет диалога
			chrDisableReloadToLocation = false;//открыть локацию
			pchar.quest.GuardOT_exitbase.win_condition.l1 = "ExitFromLocation";
			pchar.quest.GuardOT_exitbase.win_condition.l1.location = pchar.location;
			pchar.quest.GuardOT_exitbase.function = "GuardOT_ExitFrombase";
			AddQuestRecord("Guardoftruth", "4");
		break;
		
		case "spa_prisoner_32":
			PlaySound("VOICE\Russian\Serve_senior.wav");
			dialog.text = "Капитан, с какой целью вы явились на испанский остров? Только для того, чтобы высадить меня здесь? Не смею на это надеяться...";
			link.l1 = "Именно для того, чтобы высадить вас. Однако смысл моего прибытия сюда несколько глубже, чем вам кажется. Но вас это уже никоим образом не касается. Я отпущу вас прямо сейчас, без всякого выкупа, но при условии того, что вы поклянетесь мне в двух вещах.";
			link.l1.go = "spa_prisoner_33";			
		break;
		
		case "spa_prisoner_33":
			dialog.text = "О чем пойдет речь?";
			link.l1 = "Первое - я дам вам запечатанное письмо, а вы доставите его инквизитору Сантьяго, отцу Винсенто, лично в руки. Если он спросит, от кого и как оно к вам попало - смело говорите правду...";
			link.l1.go = "spa_prisoner_34";			
		break;
		
		case "spa_prisoner_34":
			dialog.text = "";
			link.l1 = "А второе - вы не предпримете никаких действий для того, чтобы попытаться найти меня или атаковать мой корабль, по крайней мере, неделю. Вы согласны?";
			link.l1.go = "spa_prisoner_35";			
		break;
		
		case "spa_prisoner_35":
			dialog.text = "И это всё?";
			link.l1 = "Да, это всё. Выполните мои условия - и полностью свободны.";
			link.l1.go = "spa_prisoner_36";			
		break;
		
		case "spa_prisoner_36":
			dialog.text = "Я клянусь вам, сеньор, что доставлю письмо отцу Винсенто лично в руки, а также в том, что не стану предпринимать никаких действий, которые смогут спровоцировать агрессию гарнизона Сантьяго против вас. Можете не сомневаться - я сдержу слово. Я испанец, и я уважаю сильных и благородных противников.";
			link.l1 = "Хорошо, дон "+GetFullName(npchar)+", я принимаю вашу клятву и отпускаю вас прямо сейчас. Вот, возьмите письмо для инквизитора. А теперь вы свободны.";
			link.l1.go = "spa_prisoner_37";			
		break;
		
		case "spa_prisoner_37":
			Log_Info("Вы передали письмо");
			PlaySound("interface\important_item.wav");
			dialog.text = "Прощайте, сеньор. Надеюсь, мы более никогда не встретимся с вами на поле брани. Клянусь, мне это будет крайне неприятно.";
			link.l1 = "Прощайте, сударь...";
			link.l1.go = "spa_prisoner_38";			
		break;
		
		case "spa_prisoner_38":
			DialogExit();
			RemovePassenger(pchar, npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "", -1);
			chrDisableReloadToLocation = false;//открыть локацию
			AddQuestRecord("Guardoftruth", "5");
			pchar.quest.GuardOT_mayak.win_condition.l1 = "Timer";
			pchar.quest.GuardOT_mayak.win_condition.l1.date.hour  = sti(GetTime()-(rand(4)));
			pchar.quest.GuardOT_mayak.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.GuardOT_mayak.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.GuardOT_mayak.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.GuardOT_mayak.win_condition.l2 = "location";
			pchar.quest.GuardOT_mayak.win_condition.l2.location = "mayak9";
			pchar.quest.GuardOT_mayak.function = "GuardOT_CreateVinsentoAgent";
			AddCharacterExpToSkill(pchar, "Leadership", 200);
		break;
		
		case "spa_prisoner_39":
			dialog.text = "О, какая встреча! Здравствуйте, месье "+GetFullName(pchar)+"! Смотрю, вы стали желанным гостем в Сантьяго. Работаете на Священную Инквизицию?";
			link.l1 = "Приветствую, сеньор "+npchar.name+". Я думал, что мы больше никогда не увидимся, а тут - на тебе! Нет, просто зашел в гости к отцу Винсенто. Ну а вы как? Служите теперь в Сантьяго?";
			link.l1.go = "spa_prisoner_40";
		break;
		
		case "spa_prisoner_40":
			dialog.text = "После того, как вы освободили меня из-под ареста, я действительно был вынужден задержаться в Сантьяго... но как видите, я сдержал слово: никаких преследований в ваш адрес...";
			link.l1 = "Это очень похвально, что вы оказались человеком чести.";
			link.l1.go = "spa_prisoner_41";
		break;
		
		case "spa_prisoner_41":
			dialog.text = "Послушайте, капитан, а не хотите по стаканчику, так сказать - за встречу? Никогда бы не подумал, что стану предлагать такое французу, но вы - исключение.";
			link.l1 = "Не буду возражать, я не против немножко промочить ромом горло. Пойдемте в таверну.";
			link.l1.go = "spa_prisoner_42";
		break;
		
		case "spa_prisoner_42":
			DialogExit();
			NextDiag.CurrentNode = "spa_prisoner_43"; 
			FreeSitLocator("Santiago_tavern", "sit_front4");
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload4_back", "Santiago_tavern", "sit", "sit_front4", "GuardOT_SpaOfficerInTavern", -1);
		break;
		
		case "spa_prisoner_43":
			LAi_SetSitType(Pchar);
			dialog.text = "Эх, ну давайте, поднимем кружки, месье капитан!";
			link.l1 = "За что выпьем, сеньор офицер?";
			link.l1.go = "spa_prisoner_44";
		break;
		
		case "spa_prisoner_44":
			dialog.text = "Давайте за что-нибудь нейтральное, но касающееся нас обоих. Например, за доблестную и успешную службу державе! Каждому - своей!";
			link.l1 = "И давайте еще за то, чтобы наши власти когда-нибудь договорились друг с другом, и французы с испанцами прекратили вражду на архипелаге.";
			link.l1.go = "spa_prisoner_45";
		break;
		
		case "spa_prisoner_45":
			dialog.text = "Хорошо сказано, капитан! Будем!";
			link.l1 = "Угм... (пьет)";
			link.l1.go = "spa_prisoner_46";
		break;
		
		case "spa_prisoner_46":
			dialog.text = "Аха! Неплохое пойло у местного тавернщика...";
			link.l1 = "Согласен. Расскажите, не сильно вы поплатились на службе за свое пленение в Сен-Пьере?";
			link.l1.go = "spa_prisoner_47";
		break;
		
		case "spa_prisoner_47":
			dialog.text = "Нет. Все неурядицы позади. В конце-концов, это же солдатская судьба.";
			link.l1 = "А где сейчас ваш командир, как его... Диего, да? Как на нем отразился неудачный поход? Разжаловали?";
			link.l1.go = "spa_prisoner_48";
		break;
		
		case "spa_prisoner_48":
			dialog.text = "О, нет! Наш славный Диего де Монтойя непотопляем, пока за ним стоит дон Рамон де Мендоса-и-Риба. Кстати, дон Диего только вчера был в Сантьяго. Прибыл из Сан-Хосе.";
			link.l1 = "Да вы что? Ну надо же! Хорошо, что мы не встретились - боюсь, дело могло бы закончится вызовом на дуэль, ха-ха!";
			link.l1.go = "spa_prisoner_49";
		break;
		
		case "spa_prisoner_49":
			dialog.text = "Дону Диего сейчас не до вас, капитан. У него дела поважнее, чем рисковать жизнью на дуэли. Он вместе с бароном затеял что-то на Западном Мэйне. В Гаване он собрал эскадру и намерен с дня на день отплыть на материк.";
			link.l1 = "Вы тоже в его команде?";
			link.l1.go = "spa_prisoner_50";
		break;
		
		case "spa_prisoner_50":
			dialog.text = "Нет. Завтра я отбываю в гарнизон Сан-Хуан, что на Пуэрто-Рико. На Провиденсии у дона Мендосы я более не в почете.";
			link.l1 = "Ну, так давайте выпьем за ваше новое место службы, и чтобы там вас ждали одни только радости.";
			link.l1.go = "spa_prisoner_51";
		break;
		
		case "spa_prisoner_51":
			dialog.text = "Спасибо, месье. Вам тоже всяческих удач. Да и, пожалуй, мне пора. Допиваю - и на выход.";
			link.l1 = "Счастливого пути, сеньор "+npchar.name+". Может, еще как-нибудь встратимся в более мирное время.";
			link.l1.go = "spa_prisoner_52";
		break;
		
		case "spa_prisoner_52":
			DialogExit();
			AddDialogExitQuest("GuardOT_SpaOfficerOutTavern");
		break;
		
		case "spa_prisoner_53":
			PlaySound("VOICE\Russian\other\OZGi-01.wav");
			dialog.text = "Как я вам и говорил, дон Диего: рыбка заглотила наживку целиком... вот и еще раз встретились, месье. Правда, не в мирной обстановке, как вы хотели.";
			link.l1 = ""+npchar.name+"? Не ожидал, однако. Я почему-то думал, что ты честный и благородный солдат. Выходит, ошибался.";
			link.l1.go = "spa_prisoner_54";
		break;
		
		case "spa_prisoner_54":
			dialog.text = "Отчего же ошибались? Я свое слово сдержал, а вот в вечной дружбе вам не клялся. Ничего не изменилось, месье - вы по-прежнему враг Испании и мой личный враг. Здесь не Сантьяго, и тут нет отца Винсенто, и его бумага вам не поможет...";
			link.l1 = "Вот как? И все же мне кажется, что пить ром за одним столом, вести дружескую беседу и при этом преследовать цель заманить в западню - это довольно подло, вы так не считаете, сеньор "+npchar.name+"?";
			link.l1.go = "spa_prisoner_55";
		break;
		
		case "spa_prisoner_55":
			dialog.text = "Ты смеешь называть меня подлецом, лягушатник?!";
			link.l1 = "...";
			link.l1.go = "spa_prisoner_56";
		break;
		
		case "spa_prisoner_56":
			DialogExit();
			sld = CharacterFromID("Diego");
			sld.dialog.currentnode = "shore";
			LAi_SetActorType(sld);
			LAi_ActorDialogNow(sld, pchar, "", -1);
		break;
		
		// посланец Винсенто
		case "vinsentoagent":
			PlaySound("VOICE\Russian\other\OZGi-02.wav");
			dialog.text = "Эй, ты! Да-да, ты! "+GetFullName(pchar)+"?";
			link.l1 = "В точку, приятель. Это я.";
			link.l1.go = "vinsentoagent_1";			
		break;
		
		case "vinsentoagent_1":
			dialog.text = "Тебе письмо от одного важного человека. Сам знаешь, от кого.";
			link.l1 = "Знаю, знаю. Давай его сюда.";
			link.l1.go = "vinsentoagent_2";			
		break;
		
		case "vinsentoagent_2":
			GiveItem2Character(pchar, "specialletter");
			ChangeItemDescribe("specialletter", "itmdescr_specialletter_vinsento");
			sld = ItemsFromID("specialletter");
			sld.text = "Letter_Vincento";
			dialog.text = "Держи. Как насчет нескольких монет за труды?";
			if (sti(Pchar.money) >= 2000)
			{
				link.l1 = "Возьми немного серебра. Ты честно заработал его.";
				link.l1.go = "vinsentoagent_2_1";	
				AddCharacterExpToSkill(pchar, "Leadership", 50);
			}
			else
			{
				link.l1 = "Не дури, дружище. Тебе уже заплатили за его доставку.";
				link.l1.go = "vinsentoagent_2_2";
			}
		break;
		
		case "vinsentoagent_2_1":
			AddMoneyToCharacter(pchar, -2000);
			dialog.text = "Спасибо, дружище. Приятно иметь дело с щедрым человеком.";
			link.l1 = "Все, давай проваливай, и не трепи языком о том, что здесь произошло.";
			link.l1.go = "vinsentoagent_3";			
		break;
		
		case "vinsentoagent_2_2":
			dialog.text = "Гаванский волк тебе дружище...";
			link.l1 = "Чего? Шел бы ты отсюда...";
			link.l1.go = "vinsentoagent_3";			
		break;
		
		case "vinsentoagent_3":
			DialogExit();
			npchar.lifeday = 0;
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "", -1);
			chrDisableReloadToLocation = false;//открыть локацию
		break;
		
		// боцман Гая Марше
		case "boatsvandega":
			dialog.text = "Приветствую на палубе 'Восхитительного', капитан "+GetFullName(pchar)+"!";
			link.l1 = TimeGreeting()+"! Немного не ожидал - вы меня знаете?";
			link.l1.go = "boatsvandega_1";			
		break;
		
		case "boatsvandega_1":
			dialog.text = "Да кто же во французских колониях не слышал про капитана по имени "+GetFullName(pchar)+", разгромившего наголову испанскую эскадру во главе с линейным кораблем, напавшую на Сен-Пьер, и перебившего весь вражеский десант! Вы, можно сказать, национальный герой!";
			link.l1 = "Да ладно вам, 'герой'... Я просто солдат, и исполнял свой долг перед Францией.";
			link.l1.go = "boatsvandega_2";
		break;
		
		case "boatsvandega_2":
			dialog.text = "Много ли солдат способны на такое, а, капитан?.. Эх, я бы с удовольствием угостил бы вас ромом в кают-компании, да вот беда: капитан запретил выдавать хоть каплю рома матросам, а я не хочу своим примером разлагать дисциплину...";
			link.l1 = "Хм... так вы не капитан?";
			link.l1.go = "boatsvandega_3";
		break;
		
		case "boatsvandega_3":
			dialog.text = "А я похож на капитана? Хо-хо! Нет, я всего лишь боцман, Серж Дега. Наш капитан - Гай Марше, целыми днями сидит в таверне, а мы уже которую неделю стоим на рейде, ожидая караван каких-то 'купцов'. Кэп задолжал жалование матросам, да и нам тоже, и вся команда совсем не в духе... Будь она неладна его чертова ваниль!";
			link.l1 = "А что такое случилось? Караван испанских купцов с ванилью никак не появляется, чтобы его пощипать?";
			link.l1.go = "boatsvandega_4";
		break;
		
		case "boatsvandega_4":
			dialog.text = "Какое там - 'пощипать'! Кэп завязал с каперством, как только захватил у испанцев вот этот самый галеон. А случилось вот что: он услышал, что на Гваделупу скоро прибудет купеческий караван, следующий в Европу, и что будут закупаться пряности. Вот он и забил трюмы в Бриджтауне доверху этой ванилью! Решил, что продаст по триста песо за ящик, ага, держи карман шире!\nНикакого каравана, конечно, нет, ваниль же в местном магазине продавать невыгодно. Вот мы и ждем этих 'купцов', которых, наверняка, не будет еще года три... Целыми днями кэп сидит в таверне и расспрашивает всех приезжих, только ночевать на корабль приходит. Уже готов и по двести песо продать, лишь бы свое вернуть\nДенег нет - всё в товар вложил. Дождется, что его и нас всех матросы скрутят и спустят ваниль за долги по бросовой цене... Клянусь громом, всё к этому и идет.";
			link.l1 = "Да уж... и чего же ваш капитан так промахнулся?";
			link.l1.go = "boatsvandega_5";
		break;
		
		case "boatsvandega_5":
			dialog.text = "Да потому что не умеешь - не берись. Торгаш из Гая никудышный. Ладно бы еще фрахты возил, так нет же - захотелось себя негоциантом почувствовать, якорь ему в корму...";
			link.l1 = "Все ясно, Серж. Ладно, глядишь - еще и появится ваш... караван.";
			link.l1.go = "boatsvandega_6";
		break;
		
		case "boatsvandega_6":
			dialog.text = "Ох, не верю я в чудеса, капитан. Уже уходите? Возможно, как-нибудь еще встретимся, попьем рому... эх, так в горле пересохло!";
			link.l1 = "Удачи, приятель...";
			link.l1.go = "boatsvandega_7";
		break;
		
		case "boatsvandega_7":
			DialogExit();
			NextDiag.currentnode = "boatsvandega_8";
			npchar.DeckDialogNode = "boatsvandega_8";
			// активируем каракку
			sld = characterFromId("GOT_Gevarra");
			sld.Dialog.Filename = "Quest\Sharlie\Guardoftruth.c";
			sld.DeckDialogNode = "gevarra";
			AddQuestRecord("Guardoftruth", "16");
		break;
		
		case "boatsvandega_8":
			dialog.text = "Эх, капитан, с таким удовольствием бы выпил глоточек рома!";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "boatsvandega_8";
		break;
		
		// Гай Марше
		case "marshe_tavern":
			PlaySound("VOICE\Russian\tavern\Kontrabandisti-08.wav");
			dialog.text = NPCStringReactionRepeat("Хо! Вы случайно не из купеческого каравана? Ах, простите, конечно же, нет... Обознался.", "У меня совсем нет настроения, месье, так что поищите себе другого собеседника.", "Ах, опять вы? Да сколько же можно?!", "Кхм...", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Да ничего, дружище, бывает.", "Выпей рому, капитан, и настроения прибавится...", "Не нервничай, приятель, это вредно для здоровья.", "Ладно-ладно, ухожу.", npchar, Dialog.CurrentNode); 
			link.l1.go = DialogGoNodeRepeat("exit", "", "", "", npchar, Dialog.CurrentNode);
			NextDiag.TempNode = "marshe_tavern";
		break;
		
		case "marshe_lay":
			PlaySound("VOICE\Russian\citizen\convict-03.wav");
			dialog.text = "А-аргх... М-м... Черт возьми, что такое?..";
			link.l1 = "Тихо, приятель... Не шуми...";
			link.l1.go = "marshe_lay_1";
		break;
		
		case "marshe_lay_1":
			PlaySound("VOICE\Russian\citizen\convict-02.wav");
			dialog.text = "А? Что?.. Проклятие!";
			link.l1 = "";
			link.l1.go = "marshe_lay_2";
		break;
		
		case "marshe_lay_2":
			DialogExit();
			LAi_SetgroundSitType(npchar);
			NextDiag.currentnode = "marshe_sitground";
		break;
		
		case "marshe_sitground":
			PlaySound("VOICE\Russian\EvilPirates07.wav");
			dialog.text = "А-ать! Кто ты такой? Что тебе от меня нужно?";
			link.l1 = "Будешь орать - быстро угомоню кастетом по голове, усек? Где церковная утварь, которую ты прихватил, когда абордировал этот корабль?";
			link.l1.go = "marshe_sitground_1";
		break;
		
		case "marshe_sitground_1":
			dialog.text = "Какую утварь? Я не понимаю! Это мой корабль!";
			link.l1 = "Как же, твой... Еще не так давно он был 'Санта Маргаритой' и ходил под испанским флагом... Где церковные драгоценности, я тебя спрашиваю? Золотой остензорий, крест с лазуритом и золотое кадило? Куда ты их дел? Продал уже, небось?";
			link.l1.go = "marshe_sitground_2";
		break;
		
		case "marshe_sitground_2":
			dialog.text = "Ушам не верю... ты что же -испанец? О нет... ты не испанец! Но это еще хуже! Ты продался гнусным кастильцам! Почем нынче они покупают души французов? Я ничего тебе не скажу, не получишь ты этих церковных вещичек!";
			link.l1 = "Не скажешь? Да и черт с тобой, тут не лучшее место для допроса... Сейчас мы заткнем тебе рот кляпом, чтобы не визжал, и пойдем ко мне в шлюпку... ты все равно заговоришь, дружок. Ой как заговоришь!";
			link.l1.go = "marshe_sitground_3";
		break;
		
		case "marshe_sitground_3":
			dialog.text = "Испанский приспешник! Будь ты...";
			link.l1 = "Умолкни, пес... Вот так. И топай за мной сам, иначе оглушу и поволоку через всю палубу за ноги.";
			link.l1.go = "marshe_sitground_4";
		break;
		
		case "marshe_sitground_4":
			DialogExit();
			RemoveAllCharacterItems(npchar, true);
			ChangeCharacterAddressGroup(npchar, "Deck_Galeon_Ship", "goto", "stand");
			LAi_SetActorType(npchar);
			LAi_ActorFollow(npchar, pchar, "", -1);
			pchar.quest.GuardOT_marchfromgaleon.win_condition.l1 = "locator";
			pchar.quest.GuardOT_marchfromgaleon.win_condition.l1.location = "Deck_Galeon_Ship";
			pchar.quest.GuardOT_marchfromgaleon.win_condition.l1.locator_group = "reload";
			pchar.quest.GuardOT_marchfromgaleon.win_condition.l1.locator = "reload2";
			pchar.quest.GuardOT_marchfromgaleon.function = "GuardOT_ExitGaleon";
		break;
		
		// капитан каракки - Карлос Геварра
		case "gevarra":
			dialog.text = "Что вам угодно, сударь?";
			link.l1 = "Как дела, капитан? Какими судьбами в Бас-Тере? Вы, как я понимаю - испанец, хоть и под голландским флагом?";
			link.l1.go = "gevarra_1";			
		break;
		
		case "gevarra_1":
			dialog.text = "А в чем проблема, сударь? Да, я испанец, это легко догадасть по типу моего корабля и по названию, но я нахожусь здесь на законных основаниях, у меня есть лицензия Голландской Вест-Индской Компании, так что...";
			link.l1 = "Да что же вы так кипятитесь, сеньор! Это как раз очень хорошо, что вы испанец... Скажите, вы здесь под погрузкой или выгрузкой?";
			link.l1.go = "gevarra_2";			
		break;
		
		case "gevarra_2":
			dialog.text = "Я привез из Гаваны товар и продал его в местном магазине. Сейчас жду выгодного фрахта, чтобы не идти порожняком домой.";
			link.l1 = "Черт возьми! Сеньор, у меня к вам деловое предложение. Вы можете очень неплохо заработать, если поможете мне. Обсудим? Кстати, как ваше имя?";
			link.l1.go = "gevarra_3";			
		break;
		
		case "gevarra_3":
			dialog.text = "Карлос. Капитан Карлос Геварра. Какое предложение?";
			link.l1 = "Мне нужно закупить большую партию ванили и отправить ее на Кубу, человеку по имени "+pchar.questTemp.Guardoftruth.LMname+", это смотритель маяка Сантьяго. Однако у меня с этим возникли серьезные трудности. Во-первых, столько ванили, сколько мне нужно, в магазине Бас-Тера нет...";
			link.l1.go = "gevarra_4";			
		break;
		
		case "gevarra_4":
			dialog.text = "";
			link.l1 = "Во-вторых, мне нужно немедленно отправляться на Сент-Кристофер, и неизвестно, сколько я там пробуду. У меня срывается заработок, понимаете? Обидно, черт возьми...";
			link.l1.go = "gevarra_5";			
		break;
		
		case "gevarra_5":
			dialog.text = "Понимаю. Такое бывает, сеньор. Всех денег не заработаешь. Так что же вы от меня хотите?";
			link.l1 = "Посмотрите вон туда. Видите вот тот галеон? У него полные трюмы так нужной мне ванили. Но беда в том, что капитан галеона втемяшил в свою глупую голову, что сюда скоро прибудет караван, который выгодно купит его груз, чуть ли не по триста песо...";
			link.l1.go = "gevarra_6";			
		break;
		
		case "gevarra_6":
			dialog.text = "Да, наивные люди частенько попадаются в наше время...";
			link.l1 = "Наивные - это мало, так еще и тупые! Я преложил купить у него ваниль по двести десять песо - он и двести-то не выручит в магазине - так представляете: он послал меня к черту! Сказал, что продаст по двести пятьдесят!";
			link.l1.go = "gevarra_7";			
		break;
		
		case "gevarra_7":
			dialog.text = "Ха-ха-ха! Нет границ у человеческой глупости...";
			link.l1 = "Вот-вот! Я примерно это ему и сказал. Он, конечно, разозлился... но мне очень нужна эта ваниль! Сеньор, я все-таки не торговец, а вы, как я вижу, на этом деле собаку съели, да и каракка у вас вместительная...";
			link.l1.go = "gevarra_8";			
		break;
		
		case "gevarra_8":
			dialog.text = "";
			link.l1 = "Уговорите этого чертового дурака продать груз вам - мне он его уже точно не продаст. Я готов заплатить по двести десять песо за ящик. Если вы собьете цену ниже - оставьте разницу себе. А я за это зафрахтую ваше судно до Сантьяго - вы отвезете ваниль туда и передадите смотрителю...";
			link.l1.go = "gevarra_9";			
		break;
		
		case "gevarra_9":
			dialog.text = "Сколько вы готовы заплатить за фрахт?";
			link.l1 = "А сколько вы хотите?";
			link.l1.go = "gevarra_10";			
		break;
		
		case "gevarra_10":
			dialog.text = "До Сантьяго приличное расстояние... тридцать тысяч песо.";
			link.l1 = "Хм...";
			link.l1.go = "gevarra_11";			
		break;
		
		case "gevarra_11":
			dialog.text = "Хорошо, мне ведь все-таки по пути... Двадцать пять тысяч и ни монетой меньше.";
			link.l1 = "Я согласен. Капитана галеона зовут Гай Марше, он постоянно днем сидит в таверне. Надеюсь, вам удасться уговорить его.";
			link.l1.go = "gevarra_12";			
		break;
		
		case "gevarra_12":
			dialog.text = "И не с такими чудаками дело приходилось иметь... я ему в подробностях расскажу, кто и для чего распускает слухи о караванах, закупающих товары по заоблачным ценам... После этого он быстро захочет избавиться от своего груза.";
			link.l1 = "Значит, мы договорились?";
			link.l1.go = "gevarra_13";			
		break;
		
		case "gevarra_13":
			iTemp = sti(pchar.questTemp.Guardoftruth.VanilleQty)*210+25000;
			dialog.text = "Договоримся, если у вас есть деньги на оплату товара и фрахт. Они у вас с собой? Покажите.";
			if (sti(Pchar.money) >= iTemp)
			{
				link.l1 = "Вот, пожалуйста, смотрите. Этого должно хватить. Я не обманываю.";
				link.l1.go = "gevarra_14";
			}
			else
			{
				link.l1 = "Они у меня в рундуке на корабле. Сейчас принесу!";
				link.l1.go = "gevarra_14_no";
			}
		break;
		
		case "gevarra_14_no":
			DialogExit();
			NextDiag.currentnode = "gevarra_wait";
			npchar.DeckDialogNode = "gevarra_wait";
		break;
		
		case "gevarra_wait":
			iTemp = sti(pchar.questTemp.Guardoftruth.VanilleQty)*210+25000;
			dialog.text = "Вы принесли деньги?";
			if (sti(Pchar.money) >= iTemp)
			{
				link.l1 = "Вот, пожалуйста, смотрите. Этого должно хватить. Я не обманываю.";
				link.l1.go = "gevarra_14";
			}
			else
			{
				link.l1 = "Уже несу!";
				link.l1.go = "exit";
			}	
		break;
		
		case "gevarra_14":
			if (stf(environment.time) < 24.0)
			{
				sTemp = "завтра";
				iTemp = 1;
			}
			else
			{
				sTemp = "сегодня";
				iTemp = 0;
			}
			if (stf(environment.time) > 21.0 && stf(environment.time) < 7.0)
			{
				dialog.text = "Прекрасно. Люблю вести дела с толковыми партнерами. Приходите "+sTemp+" часикам к десяти утра - думаю, к этому моменту ваш клиент уже 'созреет'.";
				link.l1 = "Отлично! До встречи!";
				link.l1.go = "gevarra_15";
				pchar.quest.GuardOT_tradetimer.win_condition.l1 = "Timer";
				pchar.quest.GuardOT_tradetimer.win_condition.l1.date.hour  = 10.0;
				pchar.quest.GuardOT_tradetimer.win_condition.l1.date.day   = GetAddingDataDay(0, 0, iTemp);
				pchar.quest.GuardOT_tradetimer.win_condition.l1.date.month = GetAddingDataMonth(0, 0, iTemp);
				pchar.quest.GuardOT_tradetimer.win_condition.l1.date.year  = GetAddingDataYear(0, 0, iTemp);
				pchar.quest.GuardOT_tradetimer.function = "GuardOT_PrepareTrade";
			}
			else
			{
				dialog.text = "Прекрасно. Люблю вести дела с толковыми партнерами. Я отправляюсь на берег. Приходите часа через три - думаю, к этому моменту ваш клиент уже 'созреет'.";
				link.l1 = "Отлично! До встречи!";
				link.l1.go = "gevarra_15";
				pchar.quest.GuardOT_tradetimer.win_condition.l1 = "Timer";
				pchar.quest.GuardOT_tradetimer.win_condition.l1.date.hour  = sti(GetTime()+3);
				pchar.quest.GuardOT_tradetimer.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 0);
				pchar.quest.GuardOT_tradetimer.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 0);
				pchar.quest.GuardOT_tradetimer.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 0);
				pchar.quest.GuardOT_tradetimer.function = "GuardOT_PrepareTrade";
			}
		break;
		
		case "gevarra_15":
			iTemp = sti(pchar.questTemp.Guardoftruth.VanilleQty)*210+25000;
			DialogExit();
			NextDiag.currentnode = "gevarra_time";
			npchar.DeckDialogNode = "gevarra_time";
			AddMoneyToCharacter(pchar, -iTemp); // деньги сразу списываем
			bQuestDisableMapEnter = true;
			pchar.GenQuest.MapClosedNoBattle = true;
			AddQuestRecord("Guardoftruth", "17");
			AddCharacterExpToSkill(pchar, "Sneak", 50);
		break;
		
		case "gevarra_time":
			dialog.text = "Сеньор, я все помню. Не переживайте, заключим мы вашу сделку с этим горе-торговцем.";
			link.l1 = "Хорошо...";
			link.l1.go = "exit";
			NextDiag.TempNode = "gevarra_time";
		break;
		
		case "gevarra_16":
			dialog.text = "Всё улажено, сеньор, как вы того и хотели. Бедняга был очень рад, что я вообще согласился купить его ваниль. У него аж руки тряслись, когда я отсчитал ему аванс. Перегрузка товара состоится завтра в полдень у пляжа Капстер - решили, что так будет лучше, дабы не привлекать ненужного внимания портовых чинуш\nКак только груз будет у меня на борту - сразу же лечу на всех парусах к Сантьяго. С выгрузкой вашему компаньону я помогу. Что-нибудь ему передать?";
			link.l1 = "Да. Вот это письмо. Говорите, сделка будет у пляжа Капстер завтра в полдень? Хорошо, я на всякий случай буду неподалеку, у мыса Недоступный на островке...";
			link.l1.go = "gevarra_17";
		break;
		
		case "gevarra_17":
			Log_Info("Вы передали письмо");
			PlaySound("interface\important_item.wav");
			dialog.text = "Можете мне доверять, сеньор. Я честно веду дела. И к тому же у меня нет желания с вами ссориться. Но хотите смотреть - смотрите, мне спокойней будет.";
			link.l1 = "Прекрасно. Я очень рад этому. Тогда я завтра прослежу за сделкой, и как только вы отправитесь в путь - уйду по своим делам.";
			link.l1.go = "gevarra_18";
		break;
		
		case "gevarra_18":
			DialogExit();
			NextDiag.currentnode = "gevarra_exit";
			npchar.DeckDialogNode = "gevarra_exit";
			bQuestDisableMapEnter = true;
			pchar.GenQuest.MapClosedNoBattle = true;
			pchar.GenQuest.CannotWait = true;//запрет ожидания
			AddQuestRecord("Guardoftruth", "18");
			pchar.quest.GuardOT_gotoshore.win_condition.l1 = "ExitFromSea";
			pchar.quest.GuardOT_gotoshore.function = "GuardOT_TradeComplete";
		break;
		
		case "gevarra_exit":
			dialog.text = "Капитан, можете быть уверены: я не подведу и выполню условия нашего договора в точности.";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "gevarra_exit";
		break;
		
		// матросы Марше
		case "marshe_sailor":
			dialog.text = LinkRandPhrase("И-ик! К-капит-тан након-нец выд-дал жалование! Иех!","Я е-еще только н-начал... ик!","Морда об стол... тело под забор... йо-хо-хо, и бутылка рома-а!");
			link.l1 = LinkRandPhrase("Да уж... Ну-ну.","Ясно... Пора завязывать с этим ромом, не считаешь?","Тяжелый случай...");
			link.l1.go = "exit";
		break;
		
		case "galeonguard":
			PlaySound("VOICE\Russian\EvilPirates01.wav");
			dialog.text = "Стой! Что ты тут делаешь? Тревога! На палубе враг!";
			link.l1 = "...";
			link.l1.go = "galeonguard_1";
		break;
		
		case "galeonguard_1":
			DialogExit();
			DeleteAttribute(pchar, "GenQuest.CantRun");
			CheckAndSetOverloadMode(GetMainCharacter());
			DeleteAttribute(pchar, "questTemp.Guardoftruth.Attack");
			LAi_RemoveCheckMinHP(pchar);
			GuardOT_GaleonGuardFightAdd();
			for (i=1; i<=8; i++)
			{
				sld = characterFromId("GuardOT_galeonguard_"+i);
				LAi_SetWarriorTypeNoGroup(sld);
				LAi_group_MoveCharacter(sld, "GaleonFight");
			}
			LAi_group_FightGroups("GaleonFight", LAI_GROUP_PLAYER, true);
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
		// англичане в бухте
		case "dominica_hunter":
			dialog.text = "Хо-хо! Ты тоже за кладом Ролли Колпака явился? А то мы тут неделю ищем, ищем, никак не найдем. И хоть бы один из этих дураков догадался заплыть в скалы за водопад!";
			link.l1 = "Ты из людей полковника Фокса, так?";
			link.l1.go = "dominica_hunter_1";
		break;
		
		case "dominica_hunter_1":
			dialog.text = "Скажем, я имею отношение к 'морским лисам'. Но тебе это знать необязательно, а точнее - ни к чему. Тебе уже вообще никакие знания ни к чему. Ты нашел для меня клад, за что тебе мы сейчас скажем огромное спасибо...";
			link.l1 = "Да ты не морской лис, а скорее - морской пес... или шакал. Что тебе ближе?";
			link.l1.go = "dominica_hunter_2";
		break;
		
		case "dominica_hunter_2":
			dialog.text = "Ты, я погляжу, еще и остряк... молодец!";
			link.l1 = "Проверим остроту сабель, шакал?";
			link.l1.go = "dominica_hunter_3";
		break;
		
		case "dominica_hunter_3":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			for (i=1; i<=8; i++)
			{
				sld = characterFromId("GuardOT_DH_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "GuardOT_HuntersDie");
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
		// Белинда Риберо
		case "belinda":
			dialog.text = TimeGreeting()+", сеньор. Что вам угодно?";
			link.l1 = "Здравстуйте. Ведь это вы - донна Белинда де Риберо?";
			link.l1.go = "belinda_1";
		break;
		
		case "belinda_1":
			dialog.text = "Да, это я. С кем имею честь разговаривать?";
			link.l1 = "Капитан "+GetFullName(pchar)+", сударыня. Но пусть вас не беспокоит моя национальность - в данный момент я выполняю задание Его Преосвященства, инквизитора Сантьяго, отца Винсенто.";
			link.l1.go = "belinda_2";
		break;
		
		case "belinda_2":
			dialog.text = "Как интересно! Я слыхала, что среди братьев Ордена Иисуса есть самые разные люди, всех сословий и национальностей, но до сих пор ни разу не сталкивалась ни с кем из них так близко. Чем могу помочь вам, сеньор?";
			link.l1 = "У вас есть вещь, которая очень интересует Его Преосвященство. Это золотой остензорий, церковный потир, приобретенный вами недавно в лавке ростовщика в Виллемстаде.";
			link.l1.go = "belinda_3";
		break;
		
		case "belinda_3":
			dialog.text = "Вы хорошо осведомлены, сеньор. Впрочем, зная, кто вы, это не должно меня удивлять. Да, я приобрела этот ценный остензорий, ибо ему совсем не место в лавке торговца краденым, пропитанной насквозь людскими слезами и скорбями.";
			link.l1 = "Потир у вас, сударыня?";
			link.l1.go = "belinda_4";
		break;
		
		case "belinda_4":
			dialog.text = "Да. Я хотела принести его в дар нашей церкви, но тут на меня столько всего навалилось... я так и не успела... ах, простите меня...";
			link.l1 = "Вы плачете, сударыня? Мои слова вас чем-то огорчили? Прошу меня простить...";
			link.l1.go = "belinda_5";
		break;
		
		case "belinda_5":
			dialog.text = "Ах что вы, сударь... Давайте вернемся к нашему разговору. Как я понимаю, этот остензорий нужен отцу Винсенто? Вы хотите, чтобы я вам его отдала?";
			link.l1 = "Этот драгоценный потир предназначался для прихода Сантьяго, но был захвачен пиратом и продан ростовщику с несколькими прочими предметами церковной утвари. Моя задача - вернуть украденное туда, где ему положено быть. Безусловно, я полностью компенсирую ваши затраты.";
			link.l1.go = "belinda_6";
		break;
		
		case "belinda_6":
			dialog.text = "Ах, оставьте... Неужели вы думаете, что мне так дороги эти деньги? Я выкупила его, чтобы отдать Святой Церкви, и без колебаний передам этот потир ее представителю, тем более, члену Ордена Иисуса, служащему отца Винсенто. Но... быть может, вы не оставите меня в беде?";
			link.l1 = "Вы благородная женщина, сударыня. Что у вас стряслось?";
			link.l1.go = "belinda_7";
		break;
		
		case "belinda_7":
			dialog.text = "Помочь мне? Ах, сеньор... я и не смела надеяться на помощь от самого брата-иезуита...";
			link.l1 = "Расскажите, что вас тревожит?";
			link.l1.go = "belinda_8";
		break;
		
		case "belinda_8":
			dialog.text = "Вы можете пообещать мне, как представитель Святой Церкви, что никто и никогда не узнает того, о чем я вас попрошу?";
			link.l1 = "Даю слово, сеньора.";
			link.l1.go = "belinda_9";
		break;
		
		case "belinda_9":
			dialog.text = "Хорошо. Я верю вам. Мой очень близкий знакомый, Эстебан Соса, попал в беду - его похитили бандиты и требуют выкуп в сто тысяч песо. У меня нет таких денег, мне удалось собрать всего лишь половину, а просить помощи мне не у кого\nКроме того, я очень переживаю за... друга, и опасаюсь худшего - бандиты, получив выкуп, все равно могут расправиться с пленником, дабы он не выдал их коменданту. Если бы вы, отважный капитан, брат Ордена Иисуса, смогли бы как-то уговорить бандитов отдать Эстебана за имеющуюся сумму и проследить, чтобы он остался жив...";
			link.l1 = "Когда и где должен состояться обмен?";
			link.l1.go = "belinda_10";
		break;
		
		case "belinda_10":
			dialog.text = "Их главарь по кличке Барти Живодер сказал, что они будут ждать выкупа за Эстебана каждую ночь с одиннадцати вечера до полуночи у входа в пещеру в джунглях...";
			link.l1 = "Какое-то необычное условие...";
			link.l1.go = "belinda_11";
		break;
		
		case "belinda_11":
			dialog.text = "Видимо, они понимают, что я не могу собрать всю сумму быстро, поэтому и поставили вопрос таким образом... но я не смогу найти таких денег, никогда не смогу!";
			link.l1 = "Не плачьте, сударыня, я попробую вам помочь. Брату Ордена Иисуса не пристало бросать в беде благочестивую женщину.";
			link.l1.go = "belinda_12";
		break;
		
		case "belinda_12":
			dialog.text = "Я не смела на это надеяться... Но, капитан, Барти Живодер также сказал, что если посланник придет не один, или я обращусь к коменданту - то они немедленно убьют пленника...";
			link.l1 = "Я учту это.";
			link.l1.go = "belinda_13";
		break;
		
		case "belinda_13":
			dialog.text = "Вот, возьмите. Здесь пятьдесят тысяч. Уговорите этих негодяев взять хоть это, скажите, что у меня нет больше ни песо! Верните Эстебана! И я с радостью отдам вам остензорий для отца Винсенто.";
			link.l1 = "Я сделаю все возможное, сударыня. Будем надеяться на лучшее.";
			link.l1.go = "belinda_14";
		break;
		
		case "belinda_14":
			dialog.text = "Храни вас Господь, отважный капитан!";
			link.l1 = "...";
			link.l1.go = "belinda_15";
		break;
		
		case "belinda_15":
			AddMoneyToCharacter(pchar, 50000);
			DialogExit();
			NextDiag.CurrentNode = "belinda_16";
			AddQuestRecord("Guardoftruth", "31");
			bQuestDisableMapEnter = true;//закрыть карту
			locations[FindLocation("Cumana_CaveEntrance")].DisableEncounters = true; //энкаутеры закрыть
			LAi_LocationDisableOfficersGen("Cumana_CaveEntrance", true);
			LAi_LocationDisableOfficersGen("Cumana_Cave", true);
			pchar.quest.GuardOT_gotocave.win_condition.l1 = "location";
			pchar.quest.GuardOT_gotocave.win_condition.l1.location = "Cumana_CaveEntrance";
			pchar.quest.GuardOT_gotocave.win_condition.l2 = "HardHour";
			pchar.quest.GuardOT_gotocave.win_condition.l2.hour = 23.00;
			pchar.quest.GuardOT_gotocave.function = "GuardOT_InCaveEntrance";
		break;
		
		case "belinda_16":
			dialog.text = "У вас есть какие-нибудь новости, капитан?";
			link.l1 = "Пока нет. Ждите, сеньора, я не подведу.";
			link.l1.go = "exit";
			NextDiag.TempNode = "belinda_16";
		break;
		
		case "belinda_17":
			dialog.text = "У вас есть какие-нибудь новости, капитан?";
			link.l1 = "Да, сеньора. И боюсь, они не очень вас порадуют.";
			link.l1.go = "belinda_18";
		break;
		
		case "belinda_18":
			dialog.text = "Говорите же, не томите! Вы встречались с бандитами?";
			if (sti(Pchar.money) >= 50000)
			{
				link.l1 = "Возьмите назад ваши пятьдесят тысяч. Они мне не понадобились. А также вот этот перстень. Он знаком вам, как я полагаю?";
				link.l1.go = "belinda_19_1";
			}
			link.l2 = "Возьмите вот этот перстень, сеньора. Он знаком вам, как я полагаю?";
			link.l2.go = "belinda_19_2";
		break;
		
		case "belinda_19_1":
			RemoveItems(pchar, "jewelry29", 1);
			PlaySound("interface\important_item.wav");
			AddMoneyToCharacter(pchar, -50000);
			dialog.text = "Это... да, знаком. Что с Эстебаном?";
			link.l1 = "Я встретился с негодяями в пещере. Барти Живодер и Эстебан Соса - одно и то же лицо. Он инсценировал похищение, чтобы вытянуть из вас деньги. Он рассказал о вашей... связи. Сказал также и то, что более не желает вас видеть. Поэтому и пошел на эту гнусность. Я забрал у него этот перстень в качестве доказательства.";
			link.l1.go = "belinda_20";
		break;
		
		case "belinda_19_2":
			dialog.text = "Это... да, знаком. Что с Эстебаном?";
			link.l1 = "Я встретился с негодяями в пещере, где они набросились, скрутили меня и забрали ваши деньги. Барти Живодер и Эстебан Соса - одно и то же лицо. Он сам инсценировал похищение. Он рассказал о вашей... связи. Эстебан отпустил меня и отдал этот перстень как доказательство. Он сказал, что больше не желает вас видеть и знать.";
			link.l1.go = "belinda_20";
			npchar.quest.nomoney = true;
		break;
		
		case "belinda_20":
			if (CheckAttribute(npchar, "quest.nomoney")) sTemp = "";
			else sTemp = "Я хорошенько проучил его, но убивать не стал, из уважения к вам.";
			dialog.text = "Боже мой, Боже мой! Я не верю своим ушам! За что мне все это, за что? Что я ему сделала, что он так...";
			link.l1 = "Сеньора, я прошу вас - не убивайтесь. Этот негодяй не стоит даже одной вашей слезинки. "+sTemp+"";
			link.l1.go = "belinda_21";
		break;
		
		case "belinda_21":
			if (CheckAttribute(npchar, "quest.nomoney")) sTemp = "";
			else sTemp = "И кроме того, вот этот подарок за ваше мужество.";
			dialog.text = "Ах... я постараюсь успокоиться. Сеньор, я должна поблагодарить вас за вашу помощь. Вот, возьмите ваш остензорий. "+sTemp+" Храни вас Бог.";
			link.l1 = "Спасибо, сеньора. Не беспокойтесь: обо всем, что произошло в пещере, никто не узнает. Братья Ордена Иисуса всегда держат свое слово. А теперь разрешите откланяться.";
			link.l1.go = "belinda_22";
		break;
		
		case "belinda_22":
			DialogExit();
			AddQuestRecord("Guardoftruth", "33");
			bQuestDisableMapEnter = false;
			DeleteAttribute(pchar, "GenQuest.CannotWait");
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeday = 3;
			GiveItem2Character(pchar, "jewelry33");
			Log_Info("Вы получили золотой остензорий");
			PlaySound("interface\important_item.wav");
			if (CheckAttribute(npchar, "quest.nomoney"))
			{
				ChangeCharacterComplexReputation(pchar, "nobility", -3);
				OfficersReaction("bad");
			}
			else
			{
				Log_Info("Вы получили амулет");
				GiveItem2Character(pchar, "amulet_7");
				ChangeCharacterComplexReputation(pchar, "nobility", 5);
				OfficersReaction("good");
				ChangeCharacterNationReputation(pchar, SPAIN, 3);
				AddCharacterExpToSkill(pchar, "Leadership", 300);
			}
		break;
		
		// бандит Эстебана
		case "bandos_mush":
			PlaySound("VOICE\Russian\other\OZGi-04.wav");
			dialog.text = "Стой где стоишь, приятель!";
			link.l1 = "Уже стою.";
			link.l1.go = "bandos_mush_1";
		break;
		
		case "bandos_mush_1":
			dialog.text = "Принес деньги?";
			link.l1 = "Глупый вопрос. Иначе зачем я сюда явился, как думаешь?";
			link.l1.go = "bandos_mush_2";
		break;
		
		case "bandos_mush_2":
			dialog.text = "Строишь из себя умника, кретин? Топай в пещеру, Барти уже заждался.";
			link.l1 = "Ты раньше в карауле служил? Замашки похожие... ладно-ладно, уже иду.";
			link.l1.go = "bandos_mush_3";
		break;
		
		case "bandos_mush_3":
			DialogExit();
			chrDisableReloadToLocation = false;//открыть локацию
			LocatorReloadEnterDisable("Cumana_CaveEntrance", "reload2_back", true);
			LAi_SetWarriorType(npchar);
			LAi_CharacterDisableDialog(npchar);
			pchar.GenQuest.CannotWait = true;//запрет ожидания
			pchar.quest.GuardOT_incave.win_condition.l1 = "location";
			pchar.quest.GuardOT_incave.win_condition.l1.location = "Cumana_Cave";
			pchar.quest.GuardOT_incave.function = "GuardOT_InCumanaCave";
		break;
		
		// Эстебан-Барти
		case "barty":
			PlaySound("VOICE\Russian\other\OZGi-03.wav");
			dialog.text = "Долго же тебя дожидаться пришлось... деньги при тебе?";
			link.l1 = "Это ты - Барти Живодер? Совсем не похож на матерого бандита...";
			link.l1.go = "barty_1";
		break;
		
		case "barty_1":
			dialog.text = "Тебе дело, на кого я похож? Где деньги?";
			link.l1 = "А где пленник?";
			link.l1.go = "barty_2";
		break;
		
		case "barty_2":
			dialog.text = "Будет тебе пленник. Давай сюда монеты и не зли меня!";
			link.l1 = "Барти, я что, похож на идиота? Пока я не увижу Эстебана Соса в добром здравии, никаких денег ты не увидишь. Где он?";
			link.l1.go = "barty_3";
		break;
		
		case "barty_3":
			dialog.text = "Ах, ты еще ерепенишься? Ну ладно, сейчас мы тебя хорошенько проучим... ребята, зададим жару этому умнику!";
			link.l1 = "Вот мразь!..";
			link.l1.go = "barty_4";
		break;
		
		case "barty_4":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			GuardOT_InCumanaCaveEnemyAdd();
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			for (i=1; i<=2; i++)
			{
				sld = characterFromId("GOT_bandos_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "GuardOT_CumanaCaveBandosDie");
			AddDialogExitQuest("MainHeroFightModeOn");
			// офицеров насильно
			LAi_LocationDisableOfficersGen("Cumana_Cave", false); //офицеров пускать
			DoQuestFunctionDelay("GuardOT_SetOfficerCumanaCave", 3.0);
		break;
		
		case "barty_5":
			PlaySound("VOICE\Russian\other\Plennie-02.wav");
			dialog.text = "";
			link.l1 = "Ну что, герой, допрыгался? Где Эстебан Соса? Ну, отвечай, или буду макать тебя в воду, пока не разговоришься!";
			link.l1.go = "barty_6";
		break;
		
		case "barty_6":
			dialog.text = "Не трогай... не надо. Я и есть Эстебан Соса.";
			link.l1 = "Что?..";
			link.l1.go = "barty_7";
		break;
		
		case "barty_7":
			dialog.text = "Да-да, я никакой не Барти Живодер. Я просто...";
			link.l1 = "Ах ты засранец! Значит, ты просто решил вытрясти из Белинды сто тысяч, 'похитив' самого себя?";
			link.l1.go = "barty_8";
		break;
		
		case "barty_8":
			dialog.text = "Пойми меня как мужчина мужчину. Белинда... она действительно мне осточертела со своей любовью, да и ее муж начал догадываться...";
			link.l1 = "Вот так номер! Вы любовники?";
			link.l1.go = "barty_9";
		break;
		
		case "barty_9":
			dialog.text = "Уже нет. Я просто сбежал от нее.";
			link.l1 = "И решил заодно прихватить денежек на дорогу, так? Все ясно. Ну и что же мне с тобой сделать? Утопить в этом болоте за то, что пытался убить меня?";
			link.l1.go = "barty_10";
		break;
		
		case "barty_10":
			dialog.text = "Я не хотел крови, клянусь!";
			link.l1 = "И поэтому натравил на меня своих головорезов?";
			link.l1.go = "barty_11";
		break;
		
		case "barty_11":
			dialog.text = "Мы бы просто выпотрошили твои карманы, и все!";
			link.l1 = "Дружок, уже за одно это я должен вздернуть тебя на ноке рея своего корабля. Но из уважения к порядочной женщине, которая имела несчастье связаться с тобой, я этого не сделаю. Я доставлю тебя к ней, и пусть она разбирается, что с тобой делать...";
			link.l1.go = "barty_12";
		break;
		
		case "barty_12":
			dialog.text = "Только не это! Я не пойду в Куману!";
			link.l1 = "Предпочитаешь навечно остаться в этой пещере?";
			link.l1.go = "barty_13";
		break;
		
		case "barty_13":
			dialog.text = "Пощадите, сеньор! Отпустите меня, я просто уплыву отсюда и никогда более не появлюсь в Кумане! Я не собираюсь дожидаться, пока муж Белинды прикончит меня на дуэли или подошлет наемного убийцу...";
			link.l1 = "Ладно. Ради блага самой же сеньоры Белинды я не поведу тебя к ней. Но даже не думай, что я оставлю все в тайне - она узнает, с какой мразью ей пришлось столкнуться в этой жизни. Что у тебя есть из вещей, которые она сможет опознать?";
			link.l1.go = "barty_14";
		break;
		
		case "barty_14":
			dialog.text = "Вот... вот этот перстень с бирюзой. Она сама подарила мне его.";
			link.l1 = "Превосходно. Давай его сюда и проваливай с глаз моих!";
			link.l1.go = "barty_15";
		break;
		
		case "barty_15":
			DialogExit();
			GiveItem2Character(pchar, "jewelry29");
			Log_Info("Вы получили перстень с бирюзой");
			PlaySound("interface\important_item.wav");
			chrDisableReloadToLocation = false;//открыть локацию
			LAi_LocationDisableOfficersGen("Cumana_CaveEntrance", false);//офицеров пускать
			locations[FindLocation("Cumana_CaveEntrance")].DisableEncounters = false; //энкаутеры открыть
			locations[FindLocation("Cumana_Cave")].DisableEncounters = false; // patch
			LAi_LocationFightDisable(&Locations[FindLocation("Cumana_CaveEntrance")], false);//разрешить драться
			DeleteAttribute(pchar, "GenQuest.CannotWait");//можно мотать время
			LocatorReloadEnterDisable("Cumana_CaveEntrance", "reload2_back", false);
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "", -1);
			npchar.lifeday = 0;
			sld = characterFromId("GOT_Belinda");
			sld.dialog.currentnode = "Belinda_17";
			AddQuestRecord("Guardoftruth", "32");
		break;
		
		// охотники
		case "spa_hunter":
			dialog.text = "У тебя есть то, что нам нужно, приятель...";
			link.l1 = "Хм. Надо же... И что же это может быть?";
			link.l1.go = "spa_hunter_1";
		break;
		
		case "spa_hunter_1":
			dialog.text = "Да я и сам не знаю, дружочек. Мне просто велено забрать все твои вещи, абсолютно все, что имеются при тебе. Сам отдашь, или брыкаться будешь?";
			link.l1 = "Забавно. Похоже, ты действительно не знаешь, с кем связался. Я таких как ты по десятку за завтраком съедаю.";
			link.l1.go = "spa_hunter_2";
		break;
		
		case "spa_hunter_2":
			dialog.text = "Да ты шутничок, лягушатник, да? Что же, сейчас посмотрим, какого цвета твои потроха!";
			link.l1 = "Такого же, как и твои, дурашка... И сейчас ты в этом убедишься.";
			link.l1.go = "spa_hunter_3";
		break;
		
		case "spa_hunter_3":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			for(i=1; i<=5; i++)
			{
				sld = characterFromID("GOT_santiagoband_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "GuardOT_SantiagoBandDie");
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
		case "cabin_hunter":
			dialog.text = "Хо-хо, дружочек, а вот и ты... живо выворачивай карманы! Будешь паинькой - останешься цел. Ну?";
			link.l1 = "Да что же это за наказание такое! Даже сюда забрались... Кто вас нанял, черт побери?!";
			link.l1.go = "cabin_hunter_1";
		break;
		
		case "cabin_hunter_1":
			dialog.text = "Не твое дело. Будешь рыпаться - заберем вещички с твоего трупа. Как тебе такая перспектива?";
			link.l1 = "А как тебе перспектива самому стать трупом?";
			link.l1.go = "cabin_hunter_2";
		break;
		
		case "cabin_hunter_2":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешить драться
			for(i=1; i<=2; i++)
			{
				sld = CharacterFromID("GOT_cabinband_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "GuardOT_CabinBandosDie");
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
		// командир абордажников
		case "batabano_officer":
			dialog.text = "Ждем ваших приказаний, капитан!";
			link.l1 = "Выдвигайтесь через джунгли в сторону мыса Сан-Антонио. По тропе налево, потом все время прямо. Затаитесь в засаде у самой бухты и будьте наготове. Я отправляюсь туда морем. Сколько времени потребуется на переход?";
			link.l1.go = "batabano_officer_1";
		break;
		
		case "batabano_officer_1":
			dialog.text = "Часов через шесть будем там, капитан!";
			link.l1 = "Хорошо. Вперед!";
			link.l1.go = "batabano_officer_2";
		break;
		
		case "batabano_officer_2":
			DialogExit();
			LocatorReloadEnterDisable("Shore13", "boat", false);
			for(i=1; i<=10; i++)
			{
				sld = characterFromID("GuardOT_Oursoldier_"+i);
				LAi_SetActorType(sld);
				LAi_ActorGoToLocation(sld, "reload", "reload1", "none", "", "", "OpenTheDoors", 20.0);
			}
			AddQuestRecord("Guardoftruth", "48");
			// на мыс
			pchar.quest.GuardOT_sanantonio.win_condition.l1 = "Ship_location";
			pchar.quest.GuardOT_sanantonio.win_condition.l1.location = "Shore15";
			pchar.quest.GuardOT_sanantonio.function = "GuardOT_SanantonioArrive";
			// на время, специально для дебилов, не читающих диалоги и СЖ
			pchar.quest.GuardOT_sanantoniotimer.win_condition.l1 = "Timer";
			pchar.quest.GuardOT_sanantoniotimer.win_condition.l1.date.hour  = sti(GetTime()+6);
			pchar.quest.GuardOT_sanantoniotimer.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 0);
			pchar.quest.GuardOT_sanantoniotimer.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 0);
			pchar.quest.GuardOT_sanantoniotimer.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 0);
			pchar.quest.GuardOT_sanantoniotimer.function = "GuardOT_SanAntonio_Timer";
		break;
		
		// наемник Патерсона
		case "housemercen":
			dialog.text = "Вот живучий ублюдок! Не сдох еще... надо было побольше пороху положить. Ладно, сейчас я тебе помогу, недобитыш...";
			link.l1 = "...";
			link.l1.go = "housemercen_1";
		break;
		
		case "housemercen_1":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешить драться
			bDisableCharacterMenu = false;//разлочим F2
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			if (MOD_SKILL_ENEMY_RATE < 5) LAi_group_SetCheck("EnemyFight", "GuardOT_HouseMercenDie");
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}