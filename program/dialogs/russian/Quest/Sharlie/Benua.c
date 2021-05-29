// аббат Бенуа
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int rate;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (CheckAttribute(pchar, "questTemp.Sharlie.BenuaLoan.Late")) // Addon 2016-1 Jason пиратская линейка 1
			{
				dialog.text = "Рад видеть тебя, сын мой. Ты пришёл, чтобы вернуть мне займ?";
				if (GetCharacterItem(pchar, "gold_dublon") >= 100 && sti(pchar.money) >= 50000)
				{
					link.l1 = "Да, отче. Я готов отдать вам долг.";
					link.l1.go = "FastStart_7";
				}
				else
				{
					link.l1 = "Я всё помню, отче. Прошу прощения за задержку - дела идут не лучшим образом, но в ближайшее время я рассчитаюсь, обещаю.";
					link.l1.go = "exit";
				}
				break;
			}
			if (CheckAttribute(pchar, "questTemp.Sharlie") && pchar.questTemp.Sharlie == "benua_final")
			{
				dialog.text = "Ты что-то хотел, сын мой?";
				link.l1 = "Да, отче. Я хочу увидеть своего брата, Мишеля де Монпе. Он сказал, что...";
				link.l1.go = "escape";
				break;
			}
			dialog.text = "Ты что-то хотел, сын мой?";
			if (CheckAttribute(pchar, "questTemp.Sharlie.FastStart") && !CheckAttribute(npchar, "quest.FastStart") && !CheckAttribute(npchar, "quest.meet")) // еще не виделись
			{
				link.l1 = "Да, отче. Мне нужна ваша помощь. Меня зовут "+GetFullName(pchar)+". Мне порекомендовал обратиться к вам мой брат, Мишель де Монпе.";
				link.l1.go = "FastStart";
			}
			if (CheckAttribute(npchar, "quest.help") && !CheckAttribute(npchar, "quest.meet")) // еще не виделись
			{
				link.l1 = "Да, отче. Мне нужна ваша помощь. Меня зовут "+GetFullName(pchar)+". Мне порекомендовал обратиться к вам мой брат, Мишель де Монпе.";
				link.l1.go = "meet";
			}
			if (CheckAttribute(pchar, "questTemp.Sharlie.FastStart") && !CheckAttribute(npchar, "quest.FastStart") && CheckAttribute(npchar, "quest.meet"))
			{
				link.l1 = "Да, отче. Для того, чтобы помочь Мишелю, мне нужен корабль. Но я только недавно прибыл на Карибы, и почти без гроша в кармане. Мой брат сказал мне, что вы можете ссудить мне некоторую сумму денег...";
				link.l1.go = "FastStart_2";
			}
			if (CheckAttribute(npchar, "quest.help") && CheckAttribute(npchar, "quest.meet"))
			{
				link.l1 = "Да, отче. Мне нужна ваша помощь.";
				if (CheckAttribute(npchar, "quest.relation_info")) link.l1.go = "help";
				else link.l1.go = "help_start";
			}
			if (CheckAttribute(pchar, "questTemp.Sharlie.BenuaLoan") && GetCharacterItem(pchar, "gold_dublon") >= 100 && sti(pchar.money) >= 50000)
			{
				link.l2 = "Да, отче. Я готов отдать вам долг.";
				link.l2.go = "FastStart_7";
			}
			link.l9 = "Да нет, ничего, отче.";
			link.l9.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		case "Benua_meeting":
			dialog.text = "Что привело тебя ко мне, сын мой?";
			link.l1 = "Здравствуйте, отче. Мне посоветовали обратиться к вам. Моё имя - Шарль де Мор. Я разыскиваю Мишеля де Монпе. Как мне известно, он должен быть где-то здесь, на Мартинике. Я... его брат.";
			link.l1.go = "Benua_meeting_1";			
		break;
		
		case "Benua_meeting_1":
			dialog.text = "Брат Мишеля де Монпе? Де Мор? Очень странно...";
			link.l1 = "Я понимаю ваши сомнения, отче. У нас просто разные фамилии. Мой отец - Анри де Монпе.";
			link.l1.go = "Benua_meeting_2";			
		break;
		
		case "Benua_meeting_2":
			dialog.text = "А-а, это всё проясняет. Я лично знал Анри де Монпе. Повернись к свету, юноша... Точно! Ты действительно похож на него... Такой же взгляд, такой же благородный профиль! Я рад видеть сына Анри де Монпе в нашей обители\nЧто же до вопроса твоего, то я сообщу тебе, что Мишель - один из высокопоставленных членов Ордена мальтийских рыцарей, однако... с ним случилась беда. Приходи завтра утром, сын мой, я познакомлю тебя с одним человеком - думаю, он сможет проводить тебя к брату.";
			link.l1 = "Спасибо, отче! Я буду завтра утром.";
			link.l1.go = "Benua_meeting_3";			
		break;
		
		case "Benua_meeting_3":
			DialogExit();
			NextDiag.CurrentNode = "Benua_meeting_repeat";
			AddQuestRecord("Sharlie", "4");
			pchar.quest.Sharlie_Benua.win_condition.l1 = "Timer";
			pchar.quest.Sharlie_Benua.win_condition.l1.date.hour  = 6;
			pchar.quest.Sharlie_Benua.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.Sharlie_Benua.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.Sharlie_Benua.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.Sharlie_Benua.function = "Sharlie_BenuaMaltie";
		break;
		
		case "Benua_meeting_repeat":
			dialog.text = "Сын мой, приходи завтра утром. Мне пока нечего сказать тебе более.";
			link.l1 = "Хорошо.";
			link.l1.go = "exit";	
			NextDiag.TempNode = "Benua_meeting_repeat";
		break;
		
		case "Benua_maltie":
			dialog.text = "Здравствуй, сын мой. Как я и обещал - нужный человек уже здесь и ждёт тебя. Он готов провести тебя к твоему несчастному брату, да смилуется Господь над его судьбой...";
			link.l1 = "Где же этот человек, отче?";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Sharlie_enterMaltie");
			NextDiag.TempNode = "First time";
			npchar.quest.meet = true;
		break;
		
		case "escape":
			dialog.text = "Да, Шарль, я в курсе. Но вынужден тебя огорчить. Мишеля здесь нет.";
			link.l1 = "Как нет?! Он же сказал, что будет ждать меня в церкви у вас! Отче, что случилось? Где мой брат?!";
			link.l1.go = "escape_1";
		break;
		
		case "escape_1":
			dialog.text = "Сын мой, твой брат был здесь и покинул мою скромную обитель глубокой ночью. Куда он отправился - мне неведомо. Но он оставил для тебя письмо.";
			link.l1 = "Невероятно... и это после того, что я сделал для него! Дайте же мне это письмо!";
			link.l1.go = "escape_2";
		break;
		
		case "escape_2":
			dialog.text = "Не горячись, Шарль. Вот это письмо. Прочти его, а потом... потом я хочу поговорить с тобой. Но сначала прочитай послание своего брата.";
			link.l1 = "Я сгораю от нетерпения!";
			link.l1.go = "escape_3";
		break;
		
		case "escape_3":
			DialogExit();
			GiveItem2Character(pchar, "specialletter");
			ChangeItemDescribe("specialletter", "itmdescr_specialletter_mishelle");
			sld = ItemsFromID("specialletter");
			sld.text = "Letter_Mishelle";
			NextDiag.CurrentNode = "escape_4";
			LocatorReloadEnterDisable("FortFrance_town", "reload91", false); // лесник открыл входы
			LocatorReloadEnterDisable("FortFrance_town", "reload_jail", false);
		break;
		
		case "escape_4":
			if (CheckAttribute(pchar, "GenQuest.specialletter.read") && pchar.GenQuest.specialletter.read == "Letter_Mishelle")
			{
				dialog.text = "Я вижу, ты прочёл письмо. Теперь я хочу сказать тебе кое-что, Шарль...";
				link.l1 = "Но... как же так? Что за ахинею он несёт? Я знаю, что у моего брата есть странности, но на сумасшедшего он не похож!";
				link.l1.go = "escape_5";
			}
			else
			{
				dialog.text = "Сын мой, прочти письмо. Потом поговорим.";
				link.l1 = "Да, отче...";
				link.l1.go = "exit";
				NextDiag.TempNode = "escape_4";
			}
		break;
		
		case "escape_5":
			dialog.text = "Меня тоже удивил поступок твоего брата, Шарль. Более того - я до сих пор пребываю в растерянности. Верный слуга Ордена и Отечества - и поступает как дезертир...";
			link.l1 = "Вы не догадываетесь о причинах этого странного поступка?";
			link.l1.go = "escape_6";
		break;
		
		case "escape_6":
			dialog.text = "Увы, но - нет. Но полагаю, что для этого есть мотивы, очень глубокие мотивы. Ибо чтобы отречься от всего своего прошлого, нужно иметь какую-то очень значительную причину. Я даже не могу представить, какую. Но я чувствую, что здесь замешано что-то крайне нехорошее... даже ужасное.";
			link.l1 = "Что именно, отче?";
			link.l1.go = "escape_7";
		break;
		
		case "escape_7":
			dialog.text = "Сын мой, священник видит не глазами, а сердцем. Я не могу объяснить тебе словами, но... твой брат задумал что-то скверное. Я никогда не думал, что мои уста смогут произнести такое, однако...";
			link.l1 = "Ну, в том, что мой брат что-то задумал - я не сомневаюсь. Я даже догадываюсь, что именно. Это 'что-то' лежит где-то, имеет жёлтый цвет и приятно позвякивает.";
			link.l1.go = "escape_8";
		break;
		
		case "escape_8":
			dialog.text = "Я не думаю, что жажда золота движет твоим братом. Сдаётся мне, что ему нужно нечто большее.";
			link.l1 = "Я многому научился от Мишеля и постиг его философию, так что могу допускать, что для него важно, а что нет. Но я учту ваши слова, святой отец.";
			link.l1.go = "escape_9";
		break;
		
		case "escape_9":
			dialog.text = "Благословляю тебя, сын мой. А теперь ступай. Да хранит тебя Господь!";
			link.l1 = "Спасибо, отче. До свидания!";
			link.l1.go = "escape_10";
		break;
		
		case "escape_10":
			DialogExit();
			NextDiag.CurrentNode = "first time";
			pchar.questTemp.Sharlie = "escape";
			CloseQuestHeader("Sharlie");
			AddQuestRecord("Guardoftruth", "1");
			pchar.questTemp.Guardoftruth = "begin";
			// ставим пленного испанца
			sld = GetCharacter(NPC_GenerateCharacter("spa_baseprisoner", "q_spa_off_1", "man", "man", 30, SPAIN, -1, true, "quest"));
			FantomMakeCoolFighter(sld, 30, 80, 80, "blade_13", "pistol1", "bullet", 150);
			sld.dialog.FileName = "Quest\Sharlie\Guardoftruth.c";
			sld.dialog.currentnode = "spa_prisoner";
			RemoveAllCharacterItems(sld, true);
			LAi_SetStayType(sld);
			LAi_SetImmortal(sld, true);
			ChangeCharacterAddressGroup(sld, "Fortfrance_dungeon", "quest", "quest1");
			LAi_CharacterDisableDialog(sld);//запрет диалога
		break;
		
		// уменьшение награды за голову
		case "meet":
			dialog.text = "Брат Мишеля де Монпе? Де Мор? Очень странно...";
			link.l1 = "Я понимаю ваши сомнения, отче. У нас просто разные фамилии. Мой отец - Анри де Монпе.";
			link.l1.go = "meet_1";			
		break;
		
		case "meet_1":
			dialog.text = "А-а, это всё проясняет. Я лично знал Анри де Монпе. Повернись к свету, юноша... Точно! Ты действительно похож на него... Такой же взгляд, такой же благородный профиль! Я рад видеть сына Анри де Монпе в нашей обители\nЯ уже слышал, что Мишеля посещал некий человек, прибывший из Европы, но даже и представить себе не мог, что это - его брат. Надеюсь, что ты сможешь помочь Мишелю, у него сейчас трудные дни. Так что я могу сделать для тебя?";
			link.l1 = "Мишель сказал мне, что вы можете помочь в случае, если у меня возникнут проблемы с властями...";
			link.l1.go = "help_info";	
			npchar.quest.meet = true;
		break;
		
		case "help_info":
			dialog.text = "Это Мишель так сказал? Ясно... Что же, оказать некоторую помощь в этом вопросе я смогу. У меня есть определенное влияние в обители Римской католической церкви здесь, на архипелаге, а также в голланских поселениях. Таким образом, я могу ходатайствовать за тебя перед властями Испании и Голландии. Безусловно, я не смогу просить о многом, и если твоя провинность будет велика - то сумею лишь снизить враждебное отношение к тебе\nДля полного примирения потребуется несколько ходатайств. Кроме того, ты должен будешь снабдить меня золотыми дублонами для уплаты пожертвований и дорожных издержек. Ну, и только с одной державой за раз, конечно. Если тебя такое устраивает - обращайся, будем разрешать твои беды.";
			link.l1 = "Спасибо! Приму к сведению.";
			link.l1.go = "exit";
			npchar.quest.relation_info = "true";
		break;
		
		case "help_start":
			dialog.text = "Так что я могу сделать для тебя, сын мой? Говори, я слушаю.";
			link.l1 = "Мишель сказал мне, что вы можете помочь в случае, если у меня возникнут проблемы с властями...";
			link.l1.go = "help_info";
		break;
		
		case "help":
			dialog.text = "Чем я могу помочь, сын мой?";
			if (ChangeCharacterNationReputation(pchar, SPAIN, 0) < 0 && !CheckAttribute(npchar, "quest.relation"))
			{
				link.l1 = "У меня возникли неприятности с испанскими властями.";
				link.l1.go = "relation_spa";
			}
			if (ChangeCharacterNationReputation(pchar, HOLLAND, 0) < 0 && !CheckAttribute(npchar, "quest.relation"))
			{
				link.l2 = "У меня возникли неприятности с голландскими властями.";
				link.l2.go = "relation_hol";
			}
			link.l9 = "Извините, я пока обойдусь своими силами.";
			link.l9.go = "exit";
		break;
		
		case "relation_spa": // patch-10
			pchar.GenQuest.BenuaNation = SPAIN;
			dialog.text = "Значит, благородные сеньоры жаждут увидеть тебя закованным в кандалы в казематах Гаваны...";
			link.l1 = "Именно так, отче...";
			link.l1.go = "relation";
		break;
		
		case "relation_hol":
			pchar.GenQuest.BenuaNation = HOLLAND;
			dialog.text = "Значит, предприимчивые негоцианты жаждут увидеть тебя закованным в кандалы в казематах Виллемстада...";
			link.l1 = "Именно так, отче...";
			link.l1.go = "relation";
		break;
		
		case "relation":
			rate = abs(ChangeCharacterNationReputation(pchar, sti(pchar.GenQuest.BenuaNation), 0));
			if (rate <= 10)
			{
				dialog.text = "Да, эти слухи достигли и нашей церкви. Смогу я помочь твоей беде, это дело поправимое. Мне нужно двести пятьдесят золотых дублонов, чтобы уладить неприятности.";
				if (GetCharacterItem(pchar, "gold_dublon") >= 250)
				{
					link.l1 = "Отлично! Вот, держите золотые.";
					link.l1.go = "agree";
					iTotalTemp = 250;
				}
				link.l2 = "Тогда мне самое время отправиться за монетами.";
				link.l2.go = "exit";
			}
			else
			{
				if (rate <= 20)
				{
					dialog.text = "Да, слухи о твоих 'подвигах' достигли и нашей церкви. Подмочил ты свою репутацию, сын мой, надо было быть осмотрительнее. Но помочь всё же я сумею. Мне нужно пятьсот золотых дублонов, чтобы уладить неприятности.";
					if (GetCharacterItem(pchar, "gold_dublon") >= 500)
					{
						link.l1 = "Отлично! Вот, держите золотые.";
						link.l1.go = "agree";
						iTotalTemp = 500;
					}
					link.l2 = "Тогда мне самое время отправиться за монетами.";
					link.l2.go = "exit";
				}
				else
				{
					dialog.text = "Да, сын мой, ты такой же отчаянный, как и твой брат... Это, вероятно, ваша родовая черта. Полностью ситуацию я исправить не смогу, но улучшить твоё бедственное положение - думаю, сумею. А потом ещё раз пожертвования сделаем, если пожелаешь. Мне нужно шестьсот золотых дублонов - и сразу начну решать твои проблемы.";
					if (GetCharacterItem(pchar, "gold_dublon") >= 600)
					{
						link.l1 = "Отлично! Вот, держите золотые.";
						link.l1.go = "agree";
						iTotalTemp = 600;
					}
					link.l2 = "Тогда мне самое время отправиться за монетами.";
					link.l2.go = "exit";
				}
			}
		break;
		
		case "agree":
			RemoveItems(pchar, "gold_dublon", iTotalTemp);
			Log_Info("Вы отдали "+iTotalTemp+" дублонов");
			PlaySound("interface\important_item.wav");
			dialog.text = "Теперь ожидай не менее двух недель. Думаю, за это время я встречусь и переговорю с нужными людьми.";
			link.l1 = "Спасибо, отче! Буду ждать...";
			link.l1.go = "agree_1";
		break;
		
		case "agree_1":
			DialogExit();
			SetFunctionTimerCondition("ChangeNationRelationFromBenuaComplete", 0, 0, 10+rand(5), false);
			pchar.GenQuest.BenuaNation.Rate = abs(ChangeCharacterNationReputation(pchar, sti(pchar.GenQuest.BenuaNation), 0));
			npchar.quest.relation = "true";
		break;
		
		// Addon 2016-1 Jason пиратская линейка 1
		case "FastStart":
			dialog.text = "Брат Мишеля де Монпе? Де Мор? Очень странно...";
			link.l1 = "Я понимаю ваши сомнения, отче. У нас просто разные фамилии. Мой отец - Анри де Монпе.";
			link.l1.go = "FastStart_1";			
		break;
		
		case "FastStart_1":
			dialog.text = "А-а, это всё проясняет. Я лично знал Анри де Монпе. Повернись к свету, юноша... Точно! Ты действительно похож на него... Такой же взгляд, такой же благородный профиль! Я рад видеть сына Анри де Монпе в нашей обители. Надеюсь, что ты сможешь помочь Мишелю, у него сейчас трудные дни. Так что я могу сделать для тебя?";
			link.l1 = "Для того, чтобы помочь Мишелю, мне нужен корабль. Но я только недавно прибыл на Карибы, и почти без гроша в кармане. Мой брат сказал мне, что вы можете ссудить мне некоторую сумму денег...";
			link.l1.go = "FastStart_2";	
			npchar.quest.meet = true;
		break;
		
		case "FastStart_2":
			dialog.text = "Это Мишель так сказал?";
			link.l1 = "Отче, я понимаю ваши сомнения, но это действительно так. Чем быстрее я стану владельцем и капитаном судна, тем быстрее смогу выполнить задачу, поставленную де Пуанси и освободить брата из темницы.";
			link.l1.go = "FastStart_3";
		break;
		
		case "FastStart_3":
			dialog.text = "Я понял, сын мой. И слышу, что ты говоришь мне правду. Что же, ради Мишеля и ради твоего отца, я, конечно, помогу тебе. У меня есть личные сбережения, которые я завещал монастырю Сен-Пьера. Я готов передать их тебе на время, если это действительно поможет твоему брату. Пятьдесят тысяч песо и сто золотых дублонов - этого должно тебе хватить с лихвой.";
			link.l1 = "Спасибо, отче. Сколько времени у меня на возврат займа?";
			link.l1.go = "FastStart_4";
		break;
		
		case "FastStart_4":
			AddMoneyToCharacter(pchar, 50000);
			TakeNItems(pchar, "gold_dublon", 100);
			dialog.text = "Я не буду тебя торопить. Полгода - срок, более, чем достаточный.";
			link.l1 = "Хорошо, святой отец. Ещё раз благодарю вас!";
			link.l1.go = "FastStart_5";
		break;
		
		case "FastStart_5":
			dialog.text = "Ступай с моим благословением, сын мой.";
			link.l1 = "...";
			link.l1.go = "FastStart_6";
		break;
		
		case "FastStart_6":
			DialogExit();
			NextDiag.CurrentNode = "first time";
			npchar.quest.FastStart = "true";
			pchar.questTemp.Sharlie.BenuaLoan = "true";
			SetFunctionTimerCondition("Sharlie_BenuaLoanTime", 0, 0, 180, false);
			AddQuestRecord("Sharlie", "5-2");
		break;
		
		case "FastStart_7":
			dialog.text = "Прекрасно, сын мой. Надеюсь, эти деньги тебе пригодились.";
			link.l1 = "Ещё как, отче! Спасибо.";
			link.l1.go = "FastStart_8";
		break;
		
		case "FastStart_8":
			DialogExit();
			NextDiag.CurrentNode = "first time";
			AddMoneyToCharacter(pchar, -50000);
			RemoveItems(pchar, "gold_dublon", 100);
			pchar.quest.Sharlie_BenuaLoanTime.over = "yes";
			DeleteAttribute(pchar, "questTemp.Sharlie.BenuaLoan");
			AddQuestRecord("Sharlie", "5-3");
		break;
		
		// Jason Долго и счастливо
		case "LH_abbat":
			dialog.text = "Шарль, не верю глазам своим! Какими судьбами?!";
			link.l1 = "Благословите меня святой отец, ибо я с добрыми новостями - я женюсь, и хотел бы видеть вас священником на моей свадьбе.";
			link.l1.go = "LH_abbat_1";
		break;
		
		case "LH_abbat_1":
			dialog.text = "Сын мой, это прекрасно! Значит, ты получил то письмо от отца и решил, как всегда, действовать по своему разумению? Искренне рад за тебя! Но, боюсь, я не смогу тебе помочь, разве что ты решишь венчаться в этой самой церкви.";
			link.l1 = "Я так понимаю, что ваша миссия зашла в тупик, святой отец? Могу я чем-то помочь, так как бракосочетание в испанской капелле, конечно, авантюра в моём духе, но я твёрдо намерен провести торжество на Мартинике. Умеренно пышно, и в присутствии солидных свидетелей и почётных гостей.";
			link.l1.go = "LH_abbat_2";
		break;
		
		case "LH_abbat_2":
			dialog.text = "Жаль, мой мальчик, но весь твой авторитет ничто перед твердолобостью высших иерархов католической церкви, тем более в Испанских колониях. Мы не сошлись в вопросе раздела влияния католических миссий наших стран, и теперь я тут нечто среднее между почётным гостем и почётным же заложником. Испанцы ждут более выгодного предложения с нашей стороны. Я отправил послание в Европу, месяца через два придёт ответ, и мы возобновим переговоры. Максимум - через полгода\nДа, Папа Римский и Мазарини пошли навстречу друг другу, но о настоящей оттепели говорить ещё рано. Честно сказать, я не уверен, что мы вообще придём здесь к какому-то соглашению. Мне кажется, Палотти просто держит у себя французского аббата как некий аргумент в своей собственной политике. Впрочем, кофе у отца инквизитора отменный - грех жаловаться.";
			link.l1 = "У меня нет полгода или даже двух месяцев! Я должен исполнить волю отца, пока он меня за глаза окончательно не женил. Да и здоровье его оставляет желать лучшего, а я хотел бы успеть познакомить его со своей избранницей и будущей хозяйкой Монпе.";
			link.l1.go = "LH_abbat_3";
		break;
		
		case "LH_abbat_3":
			dialog.text = "Боюсь, тогда тебе придётся подыскать другого священника на свою свадьбу, сын мой. Увы, но я здесь надолго.";
			link.l1 = "А что вы скажете, если я разлучу вас и кофе отца инквизитора?";
			link.l1.go = "LH_abbat_4";
		break;
		
		case "LH_abbat_4":
			dialog.text = "Я бы с радостью принял твоё предложение. Подозреваю, что меня выбрали для этой миссии не случайно, чтобы, в случае чего, просто забыть об отце Бенуа. И, хоть Господь и заповедовал терпеть, но я отягощён своим заключением, несмотря на все его... блага. Но, повторюсь - отец Палотти вряд ли снизойдёт к твоим просьбам.";
			link.l1 = "Значит, я сэкономлю время и не буду пытаться его убедить. Мы просто выйдем из церкви, когда служба закончится, и отправимся на мой корабль. Медлить нельзя, святой отец - нашу встречу видели, и меня могли узнать, а из особняка губернатора выручить вас будет куда сложнее.";
			link.l1.go = "LH_abbat_5";
		break;
		
		case "LH_abbat_5":
			dialog.text = "Это рискованно, мальчик мой. Очень. На выходе меня ждёт эскорт, чтобы сопроводить в особняк, и город полон солдат.";
			link.l1 = "Элемент неожиданности, отец Бенуа. Это мой конёк - доверьтесь мне и всё будет хорошо. В таких делах у меня есть некоторый... опыт.";
			link.l1.go = "LH_abbat_6";
		break;
		
		case "LH_abbat_6":
			dialog.text = "Будь по-твоему. И хотел бы я попросить обойтись без лишнего кровопролития, но я тоже... имел некоторый опыт подобного рода. Так что веди, сын мой. Я сразу за тобой. Но оружие я в руки не возьму, и не проси.";
			link.l1 = "И не думал, святой отец. Я справлюсь. Идите за мной, но будьте осторожны - возможно, в нас будут стрелять.";
			link.l1.go = "LH_abbat_7";
		break;
		
		case "LH_abbat_7":
			DialogExit();
			LongHappy_SantiagoBenuaEscape();
		break;
		
		case "LH_abbat_8":
			LocatorReloadEnterDisable("FortFrance_town", "reload1_back", false);
			LocatorReloadEnterDisable("FortFrance_town", "reload2_back", false);
			LocatorReloadEnterDisable("FortFrance_town", "gate_back", false);
			dialog.text = "Сын мой, я не успел поблагодарить тебя за своё освобождение. Судя по всему, испанский епископ и инквизиция Палотти желали сорвать едва установившиеся отношения между нашим кардиналом и Святым Престолом, так что ты действовал вполне в интересах государства. Опять. Но 'спасибо', кроме меня, тебе вряд ли кто скажет.";
			link.l1 = "Обычное дело, святой отец. Рад, что удалось помочь. Но - у меня ведь тоже есть просьба, помните?";
			link.l1.go = "LH_abbat_9";
		break;
		
		case "LH_abbat_9":
			dialog.text = "Конечно! Так перейдём же к делам приятным - Шарль, как продвигаются ваши приготовления к столь важному дню?";
			link.l1 = "Помаленьку. Знавал я военные походы, в которые собирались проще и быстрее, но дело того стоит!";
			link.l1.go = "LH_abbat_10";
		break;
		
		case "LH_abbat_10":
			dialog.text = "Несомненно, сын мой! И, по этому поводу, я хочу уточнить один момент - какой ты видишь свою церемонию венчания?";
			link.l1 = "В смысле - насколько помпезной?";
			link.l1.go = "LH_abbat_11";
		break;
		
		case "LH_abbat_11":
			dialog.text = "Именно, ведь мне нужно подготовить церковь, возможно - ты захочешь пригласить важных персон.";
			link.l1 = "Никакого особенного шума, святой отец. Те, кого я считаю друзьями, будут ждать нас в другом месте. Здесь будет лишь несколько официальных лиц, мои ребята, да обычные зеваки.";
			link.l1.go = "LH_abbat_12";
		break;
		
		case "LH_abbat_12":
			dialog.text = "Хорошо, тогда, думаю, мы обойдёмся небольшим пожертвованием.";
			link.l1 = "Звучит нестрашно. И сколько составляет это самое пожертвование в золоте?";
			link.l1.go = "LH_abbat_13";
		break;
		
		case "LH_abbat_13":
			dialog.text = "На хор, торжественную службу, и прочие расходы - сотни полторы, не больше. Плюс обычное пожертвование от молодожёнов - и того две сотни дублонов.";
			if (GetCharacterItem(pchar, "gold_dublon") >= 200)
			{
				link.l1 = "Вот, прошу, святой отец.";
				link.l1.go = "LH_abbat_15";
			}
			else
			{
				link.l1 = "К вопросу о военных походах... Прогуляюсь до банка и вернусь.";
				link.l1.go = "LH_abbat_14";
			}
		break;
		
		case "LH_abbat_14":
			DialogExit();
			npchar.dialog.currentnode = "LH_abbat_14_1";
		break;
		
		case "LH_abbat_14_1":
			dialog.text = "Что насчёт пожертвования, сын мой?";
			if (GetCharacterItem(pchar, "gold_dublon") >= 200)
			{
				link.l1 = "Вот, прошу, святой отец.";
				link.l1.go = "LH_abbat_15";
			}
			else
			{
				link.l1 = "Да-да, скоро принесу...";
				link.l1.go = "LH_abbat_14";
			}
		break;
		
		case "LH_abbat_15":
			RemoveItems(pchar, "gold_dublon", 200);
			dialog.text = "Остается ещё вопрос, который необходимо решить - кто будет посажёным отцом невесты и свидетельствовать о заключении брака с её стороны?";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer"))
			{
				pchar.questTemp.LongHappy.Pater1 = "Svenson";
				link.l1 = "Ян Свенсон, из Блювельда. Он англичанин, но уважаемый человек и привязан к Элен как к родной дочери, и её приёмная мать Глэдис Мак Артур.";
			}
			else
			{
				if (CheckAttribute(pchar, "questTemp.Patria.GenGovernor"))
				{
					pchar.questTemp.LongHappy.Pater1 = "Noel";
					link.l1 = "Барон Форже. Уверен, он окажет мне такую честь.";
				}
				else
				{
					pchar.questTemp.LongHappy.Pater1 = "Puancie";
					link.l1 = "Шевалье де Пуанси. Уверен, он окажет мне такую честь.";
				}
			}
			link.l1.go = "LH_abbat_16";
		break;
		
		case "LH_abbat_16":
			dialog.text = "Хорошо, а кто будет свидетельствовать со стороны жениха? Помните, это должен быть человек благородного происхождения и достойной репутации.";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer"))
			{
				if (CheckAttribute(pchar, "questTemp.Patria.GenGovernor"))
				{
					link.l1 = "Барон Форже. Уверен, он окажет мне такую честь.";
					link.l1.go = "LH_abbat_17_1";
				}
				else
				{
					link.l1 = "Шевалье де Пуанси. Уверен, он окажет мне такую честь.";
					link.l1.go = "LH_abbat_17_2";
				}
				link.l2 = "Фадей Московит - видный купец с Гваделупы. Надо только запастись его любимым пойлом.";
				link.l2.go = "LH_abbat_17_3";
			}
			else
			{
				link.l1 = "Фадей Московит - видный купец с Гваделупы. Надо только запастись его любимым пойлом.";
				link.l1.go = "LH_abbat_17_3";
			}
		break;
		
		case "LH_abbat_17_1":
			pchar.questTemp.LongHappy.Pater2 = "Noel";
			dialog.text = "Отлично, я разошлю приглашения, но гостям потребуется время, чтобы добраться. Думаю, не позже, чем через месяц, всё будет готово, и указанные персоны прибудут в город.";
			link.l1 = "Значит у меня есть время уладить ещё пару дел. До встречи, святой отец и пожелайте мне удачи!";
			link.l1.go = "LH_abbat_18";
		break;
		
		case "LH_abbat_17_2":
			pchar.questTemp.LongHappy.Pater2 = "Puancie";
			dialog.text = "Отлично, я разошлю приглашения, но гостям потребуется время, чтобы добраться. Думаю, не позже, чем через месяц, всё будет готово, и указанные персоны прибудут в город.";
			link.l1 = "Значит у меня есть время уладить ещё пару дел. До встречи, святой отец и пожелайте мне удачи!";
			link.l1.go = "LH_abbat_18";
		break;
		
		case "LH_abbat_17_3":
			pchar.questTemp.LongHappy.Pater2 = "Fadey";
			dialog.text = "Отлично, я разошлю приглашения, но гостям потребуется время, чтобы добраться. Думаю, не позже, чем через месяц, всё будет готово, и указанные персоны прибудут в город.";
			link.l1 = "Значит, у меня есть время уладить ещё пару дел. До встречи, святой отец, и пожелайте мне удачи!";
			link.l1.go = "LH_abbat_18";
		break;
		
		case "LH_abbat_18":
			DialogExit();
			AddQuestRecord("LongHappy", "11");
			SetFunctionTimerCondition("LongHappy_SenPierreGuests", 0, 0, 31, false); // таймер
			if (!CheckAttribute(pchar, "questTemp.LongHappy.MarryRum"))
			{
			pchar.questTemp.LongHappy = "toIslaTesoro";
			LocatorReloadEnterDisable("Pirates_town", "reload4_back", true);//закрыть таверну Исла-Тесоро
			}
			npchar.dialog.currentnode = "First time";
		break;
		
		case "LH_abbat_19":
			dialog.text = "И вот, этот день настал, мой мальчик! У нас всё готово - через пару часов можем начинать. Ты выглядишь бледновато!";
			link.l1 = "Нервничаю немного, святой отец.";
			link.l1.go = "LH_abbat_20";
		break;
		
		case "LH_abbat_20":
			dialog.text = "Это в порядке вещей. Это важнейший день в вашей жизни, и я искренне за вас рад, как и все, кто здесь соберутся. Надеюсь, ты вспомнил хотя бы основные молитвы - ты ведь никогда не баловал церкви своим вниманием? Впрочем, я подскажу, если что\nИ ещё одно - я так понимаю, невеста своим принципам не изменит и в платье мы её не увидим? Что ж, высшее общество ждёт очередной сюрприз - ты на них щедр. А теперь - иди, сын мой, приведи себя в подобающий вид, и будем начинать.";
			link.l1 = "Хорошо, святой отец. Приступим.";
			link.l1.go = "LH_abbat_21";
		break;
		
		case "LH_abbat_21":
			DialogExit();
			chrDisableReloadToLocation = true;
			WaitDate("", 0, 0, 0, 2, 0);
			DoQuestReloadToLocation("FortFrance_church", "reload", "reload1", "LongHappy_MarryInit");
		break;
		
		case "LH_abbat_22":
			pchar.questTemp.LongHappy.Mistake = 0;
			dialog.text = "Pater noster, qui es in caelis, sanctificetur nomen tuum, ad...";
			link.l1 = "...adveniat regnum tuum";
			link.l1.go = "LH_abbat_23_1";
			link.l2 = "...requiem aeternam dona eis";
			link.l2.go = "LH_abbat_23_2";
		break;
		
		case "LH_abbat_23_1":
			dialog.text = "...fiat voluntas tua, sicut in caelo et in terra. Panem nostrum quotidianum da nobis hodie, et dimitte nobis debita nostra si...";
			link.l1 = "...sicut et nos dimittimus debitoribus nostris";
			link.l1.go = "LH_abbat_24_1";
			link.l2 = "...sicut erat in principio, et nunc et semper, et in saecula saeculorum. Amen";
			link.l2.go = "LH_abbat_24_2";
		break;
		
		case "LH_abbat_23_2":
			pchar.questTemp.LongHappy.Mistake = sti(pchar.questTemp.LongHappy.Mistake)+1;
			dialog.text = "Э-э... кхм!";
			link.l1 = "";
			link.l1.go = "LH_abbat_23_1";
		break;
		
		case "LH_abbat_24_2":
			pchar.questTemp.LongHappy.Mistake = sti(pchar.questTemp.LongHappy.Mistake)+1;
			dialog.text = "Кхм-кхм!";
			link.l1 = "";
			link.l1.go = "LH_abbat_24_1";
		break;
		
		case "LH_abbat_24_1":
			dialog.text = "et ne nos inducas in tentationem; sed libera nos a malo. Amen.";
			link.l1 = "Amen.";
			link.l1.go = "LH_abbat_25";
		break;
		
		case "LH_abbat_25":
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			dialog.text = "Мы все собрались здесь в этот прекрасный день, чтобы засвидетельствовать перед Господом нашим союз двух любящих душ. Возлюбленные "+sld.name+" и Шарль, вы слушали слово Божие, напомнившее вам о значении человеческой любви и супружества. Теперь от имени святой Церкви я желаю испытать ваши намерения\n"+sld.name+" и Шарль, имеете ли вы добровольное и искреннее желание соединиться друг с другом узами супружества, перед лицом Господа нашего?";
			link.l1 = "Да.";
			link.l1.go = "LH_abbat_26";
		break;
		
		case "LH_abbat_26":
			DialogExit();
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "LH_abbat_27":
			dialog.text = "Имеете ли вы намерение хранить верность друг другу в здравии и болезни, в счастье и в несчастии, до конца своей жизни?";
			link.l1 = "Да.";
			link.l1.go = "LH_abbat_28";
		break;
		
		case "LH_abbat_28":
			DialogExit();
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			sld.dialog.currentnode = "LongHappy_22";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "LH_abbat_29":
			dialog.text = "Имеете ли вы намерение с любовью принимать детей, которых пошлёт вам Бог, и воспитывать их в христианской вере?";
			link.l1 = "Да.";
			link.l1.go = "LH_abbat_30";
		break;
		
		case "LH_abbat_30":
			DialogExit();
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			sld.dialog.currentnode = "LongHappy_24";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "LH_abbat_31":
			dialog.text = "Что ж, обернитесь друг к другу и произнесите слова клятвы.";
			link.l1 = "";
			link.l1.go = "LH_abbat_32";
		break;
		
		case "LH_abbat_32":
			DialogExit();
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			sld.dialog.currentnode = "LongHappy_26";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "LH_abbat_33":
			dialog.text = "Есть ли в этом зале кто-то, кто знает причину, по которой эти двое не могут вступить в законный брак? Если так - пусть он выйдет вперёд и назовет её сейчас, или молчит вечно\nТогда, пред ликом Господним, и собравшимися здесь людьми, я объявляю вас мужем и женой! In nomine Patris, et Filii, et Spiritus Sancti. Amen.";
			link.l1 = "Amen.";
			link.l1.go = "LH_abbat_34";
		break;
		
		case "LH_abbat_34":
			DialogExit();
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			sld.dialog.currentnode = "LongHappy_29";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "LH_abbat_35":
			string sTemp;
			if (sti(pchar.questTemp.LongHappy.Mistake) > 1) sTemp = "(шепчет) Шарль, сын мой, просто открывай рот, умоляю - ни звука...";
			else sTemp = "";
			dialog.text = "Молодожёны, опуститесь на колени, и помолимся вместе. Oratio fidelium. "+sTemp+"";
			link.l1 = "";
			link.l1.go = "LH_abbat_36";
		break;
		
		case "LH_abbat_36":
			DialogExit();
			SetLaunchFrameFormParam("Прошло некоторое время...", "", 0.1, 3.0);
			LaunchFrameForm();
			WaitDate("", 0, 0, 0, 1, 0);
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			sld.lastname = "де Мор";
			sld.dialog.currentnode = "LongHappy_31";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 4.0);
		break;
		
		case "LH_abbat_37":
			dialog.text = "Мои поздравления, сын мой. Твой отец может тобой гордиться, и я горжусь. Будьте счастливы и берегите друг друга в наше непростое время.";
			link.l1 = "Спасибо вам святой отец. Это была прекрасная служба и я рад, что именно вы её провели.";
			link.l1.go = "LH_abbat_38";
		break;
		
		case "LH_abbat_38":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}