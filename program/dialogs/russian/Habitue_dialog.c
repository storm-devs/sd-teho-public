#include "DIALOGS\russian\Common_Duel.c" //navy
#include "DIALOGS\russian\Rumours\Common_rumours.c"  //homo 25/06/06
void ProcessDialogEvent()
{
    ref NPChar, d;
	aref Link, Diag;
	string NPC_Meeting, TempInfoCharacterID_1, TempInfoCharacterID_2, sQuestTitle;
	int DonationSize;
    	
	// Warship 18.05.08
	int iLa_Puesta; // La puesta - это ставка по-испански
    	
	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makeref(d, Dialog);
	makearef(Diag, NPChar.Dialog);
	
    ProcessCommonDialogRumors(NPChar, Link, Diag);//homo 25/06/06
    ProcessDuelDialog(NPChar, Link, Diag); //navy

	int iEnemyDice, iPCDice;
	int d1,d2,d3,d4;
	bool ok;
    ref sld;
    
	if (npchar.quest.Meeting != LastSpeakDate())
	{
		npchar.quest.Meeting = LastSpeakDate();
		npchar.money = 100 + rand(10) * makeint(50 * sti(PChar.rank) * (10.0 / MOD_SKILL_ENEMY_RATE));
		if (sti(npchar.money) < 150) npchar.money = 150;
        if (bBettaTestMode)
        {
            Dialog.CurrentNode = "Beta_test";
        }
	}
	switch (Dialog.CurrentNode)
	{
		// -----------------------------------Диалог первый - первая встреча
		case "exit":
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
		break;

        case "Beta_test":
            dialog.text = "Это меню выбора типа пьяни (бетатест)";
			link.l1 = "Пусть будет алкаш";
			link.l1.go = "Beta_test_alc";
            link.l2 = "Игрок в карты";
			link.l2.go = "Beta_test_card";
			link.l3 = "Игрок в кости";
			link.l3.go = "Beta_test_dice";
		break;
		
		case "Beta_test_alc":
            dialog.text = "Алкаш выбран";
			link.l1 = "Продолжить";
			link.l1.go = "First time";
			npchar.quest.last_theme = 0;
		    npchar.quest.last_theme_game = 0;
		break;
		
		case "Beta_test_card":
            dialog.text = "Игрок в карты (30%% что пошлет с первого раза)";
			link.l1 = "Продолжить";
			link.l1.go = "First time";
			npchar.quest.last_theme = 1;
		    npchar.quest.last_theme_game = 0;
		break;
		
		case "Beta_test_dice":
            dialog.text = "Игрок в кости (30%% что пошлет с первого раза)";
			link.l1 = "Продолжить";
			link.l1.go = "First time";
			npchar.quest.last_theme = 1;
		    npchar.quest.last_theme_game = 1;
		break;
		
		case "First time":
			if (LAi_grp_playeralarm > 0)
			{
       			dialog.text = LinkRandPhrase("Я, может, и пьян, но в своем уме. Сейчас вот выпью с тобой, а солдаты и меня загребут! Не-е-ет...", "Я не враг городу, в котором живу. Не буду с тобой пить!" , ""+ GetSexPhrase("Приятель","Подруга") +", тебе лучше бы убраться отсюда подобру-поздорову...");
				link.l1 = RandPhraseSimple("Ну, как знаешь...", "Хех, больно надо глаза заливать! Не то время."); 
				link.l1.go = "exit";
				break;
			}
			if(CheckAttribute(pchar,"questTemp.HabitueSpeakDisable") && rand(1) == 0) // если дуэлянт то каждый второй посылает нафик
			{
				dialog.text = "Ха, судар"+ GetSexPhrase("ь","ыня") +", слыхал я о вас, как же, как же, хе-хе. В тавернах говорят, что вы записн"+ GetSexPhrase("ой","ая") +" задира и дуэлянт"+ GetSexPhrase("","ка") +", и по пьяному делу уже чуть ли не дюжину душ представили пред очи Господни. Смотрите, народ у нас, конечно, не из пугливых, да только кому охота за кружку рому живота лишиться. Мне вот лично даже за одним столом с вами сидеть боязно, так что, пойду я пожалуй.";
				link.l1 = LinkRandPhrase("Ну и скатертью дорога!","Катись, пока я добр"+ GetSexPhrase("ый","ая") +"...","Давай-давай! Улепетывай, рыбья снедь!");
				link.l1.go = "exit";
				link.l2 = "Постойте, я хотел"+ GetSexPhrase("","а") +" спросить кое-что....";
				link.l2.go = "talk_habitue_duel";
				break;
			}
			
            ok = CheckFreeSitFront(npchar);
            
            dialog.text = "Не загораживай мне свет, мух в кружке не видно!";
            link.l1 = "Уже отош"+ GetSexPhrase("ел","ла") +"...";
		    link.l1.go = "exit";
		    if (!chrDisableReloadToLocation)
		    {
	            switch (npchar.quest.last_theme)
				{
					case "0": //пьяный.
						dialog.text = "И-ик! О, "+ GetSexPhrase("парень, ты выглядишь бывалым морским волком","деваха, ты выглядишь настоящей морской волчицей") +"! Может, купишь мне стаканчик рома?";
						link.l1 = "Может, я и "+ GetSexPhrase("морской волк","морская волчица") +", только это не значит, что я буду поить всякую рвань...";
						link.l1.go = "exit";

						if (makeint(pchar.money) >= 100 && ok) // только старые острова окучены на сесть
						{
							link.l2 = "Я и сам"+ GetSexPhrase("","а") +" с радостью присоединюсь к тебе, за компанию.";
							link.l2.go = "talk_with_alchogol";
						}
						else
						{
	                        link.l2 = "Это еще почему?";
							link.l2.go = "talk_with_alchogol_song";
						}
					break;

					case "1":
	                    if (rand(3) != 1 && ok)
	                    {
							switch (sti(npchar.quest.last_theme_game))
							{
							    case 0 :
									// Игра в карты boal 20/05/05 -->
	                                if (CheckNPCQuestDate(npchar, "Card_date_begin"))
									{
										Dialog.text = RandPhraseSimple("Сыграем в карты? Очень интересная игра!", "Предлагаю перекинуться в картишки. Ты как?");
										link.l1 = "Отчего же не сыграть? Давай сыграем.";
										link.l1.go = "Cards_begin";
										link.l2 = "А правила игры какие?";
										link.l2.go = "Cards_Rule";
										link.l3 = "Не сейчас.";
										link.l3.go = "exit";
									}
									else
					    			{
										Dialog.text = "Нет, не хочу я больше играть с тобой в карты.";
						    			link.l1 = "Ну и не надо.";
						    			link.l1.go = "exit";
									}
			                        // Игра в карты boal 20/05/05 <--
		                        break;

								case 1:
								// кости
		    						// Игра в кости boal 13/07/05 -->
	                                if (CheckNPCQuestDate(npchar, "Dice_date_begin"))
									{
										Dialog.text = RandPhraseSimple("Сыграем в кости? Очень интересная игра!", "Предлагаю постучать костяшками. Ты как?");
										link.l1 = "Отчего же не сыграть? Давай сыграем.";
										link.l1.go = "Dice_begin";
										link.l2 = "А правила игры какие?";
										link.l2.go = "Dice_Rule";
										link.l3 = "Не сейчас.";
										link.l3.go = "exit";
									}
									else
					    			{
										Dialog.text = "Нет, не хочу я больше играть с тобой в кости.";
					    				link.l1 = "Ну и не надо.";
					    				link.l1.go = "exit";
									}
			                        // Игра в кости boal 13/07/05 <--
			                        //navy --> Дуэли
									if (CheckAttribute(NPchar, "Quest.DiceCheats") && sti(NPchar.Quest.DiceCheats) >= 1) 
									{
					    				link.l9 = RandSwear() + " Ты жульничал!!!";
					    				link.l9.go = "outraged";
									}
									//navy <--
			    				break;
	    					} 
						}
	        			else
	        			{
	                        dialog.text = RandPhraseSimple("Убирайся от моего стола ко всем чертям!", " А... чего? Кто это?.. и-ик.. Отвали!");
	                        link.l1 = RandPhraseSimple("Пьянство губит твою грешную душу - опомнись!", "Не нужно мне грубить.");
	        			    link.l1.go = "exit";
	        			    link.l2 = RandPhraseSimple("Как ты со мной разговариваешь, скотина! Сейчас я научу тебя хорошим манерам.", "Вот я тресну тебя сейчас по башке, вмиг протрезвеешь.");
	        	            link.l2.go = "tavern_keeper";
	        			}
					break;
				}
			}
			Diag.TempNode = "First time";
	    break;
	    
		case "talk_habitue_duel":
			dialog.text = "Ничего, судар"+ GetSexPhrase("ь","ыня") +", я вам не скажу! И вряд ли кто еще согласится, ведь разговоры с вами плохо кончаются... Но память людская коротка - глядишь через месяцок-другой все ваши похождения и подзабудутся. Если вы, конечно, память-то людям не освежите, хе-хе... Прощайте, судар"+ GetSexPhrase("ь","ыня") +". ";
			link.l1 = "Ну и ладно ....";
			link.l1.go = "exit";
		break;
		
	    // карты -->
	    case "Cards_Rule":
   			dialog.text = CARDS_RULE;
			link.l1 = "Что ж, давай начнем!";
			link.l1.go = "Cards_begin";
			link.l3 = "Нет, это не для меня...";
			link.l3.go = "exit";
		break;
		
		case "Cards_begin":
			Diag.tempnode = "Cards_Node";
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
			pchar.questTemp.friend_in_tavern = npchar.id;
			AddDialogExitQuest("alc");
		break;

		case "Cards_Node":
			Diag.tempNode = "first time";

			Dialog.text = "Тогда давай определимся со ставкой (введите ставку).";
			link.l1 = "100";
			link.l1.edit = 1;
			link.l1.go = "Cards_Node_2";
			link.l3 = "Пожалуй, мне пора.";
			link.l3.go = "exit_sit";
		break;
		
		case "Cards_Node_2":
			iLa_Puesta = GetStrSmallRegister(dialogEditStrings[1]);
            if (!CheckCardsGameSmallRate())
		    {
                dialog.text = "О тебе ходит слава непревзойденного шулера. Я не буду с тобой играть в карты вообще.";
                link.l1 = "Все врут! Ну и не нужно.";
			    link.l1.go = "exit_sit";
			    break;
		    }
		    
			if (sti(PCHar.Money) < sti(iLa_Puesta)*3)
		    {
                dialog.text = "Да ты, "+ GetSexPhrase("дружок","дорогуша") +", на мели. Приходи, когда разбогатеешь.";
                link.l1 = "Ладно.";
			    link.l1.go = "exit_sit";
			    break;
		    }
		
			if (sti(NPChar.Money) < sti(iLa_Puesta)*3)
		    {
                dialog.text = "Я уже проигрался в пух и прах, не мой день.";
                link.l1 = "Ладно.";
			    link.l1.go = "exit_sit";
			    break;
		    }
		else
		{
			if(sti(iLa_Puesta) < 50)
			{
				dialog.text = "Хех, ты смеешься?! Играть на " + iLa_Puesta + " песо?! Давай ставку поменяем, иначе я с тобой играть не буду!";
				link.l1 = "Да, пожалуй. Ставку надо бы повысить.";
				link.l1.go = "Cards_begin_2";
				link.l2 = "Что-то я играть раздумал"+ GetSexPhrase("","а") +".";
				link.l2.go = "exit_sit";
				break;
			}
			
			if(sti(iLa_Puesta) > 1000)
			{
				dialog.text = "Играть на такие деньжища? Нет, увольте... Давай ставку менять!";
				link.l1 = "Да, ты прав. Ставку нужно понизить.";
				link.l1.go = "Cards_begin_2";
				link.l2 = "Что-то я вообще играть раздумал"+ GetSexPhrase("","а") +".";
				link.l2.go = "exit_sit";
				break;
			}
			dialog.text = "Хорошо, играем по " + iLa_Puesta + " монет.";
			link.l1 = "Сдавай!";
			link.l1.go = "Cards_begin_go";
			pchar.GenQuest.Cards.npcharIdx = npchar.index;
			pchar.GenQuest.Cards.iRate     = sti(iLa_Puesta);
            pchar.GenQuest.Cards.SitType   = true;
		}
		break;
		
		case "Cards_begin_2":
			dialog.text = "Так какая ставка будет? (Введите ставку).";
			link.l1 = "50";
			link.l1.edit = 1;
			link.l1.go = "Cards_Node_2";
			link.l2 = "Пожалуй, я играть не буду...";
			link.l2.go = "exit_sit";
		break;
							
		case "Cards_begin_go":
            // анлим игры в день SetNPCQuestDate(npchar, "Card_date_begin");
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
            LaunchCardsGame();
		break;
	    // карты <--
	    // КОСТИ -->
	    case "Dice_Rule":
   			dialog.text = DICE_RULE;
			link.l1 = "Что ж, давай начнем!";
			link.l1.go = "Dice_begin";
			link.l3 = "Нет, это не для меня...";
			link.l3.go = "exit";
		break;

		case "Dice_begin":
			Diag.tempnode = "Dice_Node";
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
			pchar.questTemp.friend_in_tavern = npchar.id;
			AddDialogExitQuest("alc");
		break;

		case "Dice_Node":
		    Diag.tempNode = "first time";		    
			Dialog.text = "Давай определимся со ставкой (введите ставку).";
			link.l1 = "50";
			link.l1.edit = 1;
			link.l1.go = "Dice_Node_2";
			link.l3 = "Пожалуй, мне пора.";
			link.l3.go = "exit_sit";
		break;

		case "Dice_Node_2":
			iLa_Puesta = GetStrSmallRegister(dialogEditStrings[1]);
            if (!CheckDiceGameSmallRate())
		    {
				dialog.text = "О тебе ходит слава непревзойденного шулера. Я не буду с тобой играть в кубики вообще.";
                link.l1 = "Все врут! Ну и не нужно.";
			    link.l1.go = "exit_sit";
			    break;
		    }

			if (sti(pchar.Money) < sti(iLa_Puesta)*6)
		    {
                dialog.text = "Да ты, "+ GetSexPhrase("дружок","дорогуша") +", на мели. Приходи, когда разбогатеешь.";
                link.l1 = "Ладно.";
			    link.l1.go = "exit_sit";
			    break;
		    }
			
			if (sti(npchar.Money) < sti(iLa_Puesta)*6)
		    {
                dialog.text = "Я уже проигрался в пух и прах, не мой день.";
                link.l1 = "Ладно.";
			    link.l1.go = "exit_sit";
			    break;
		    }
		else
		{
			if(sti(iLa_Puesta) < 50)
			{
				dialog.text = "Хех, ты смеешься?! Играть по " + iLa_Puesta + " песо за кубик?! Давай ставку поменяем, иначе я с тобой играть не буду!";
				link.l1 = "Да, пожалуй. Ставку надо бы повысить.";
				link.l1.go = "Dice_begin_2";
				link.l2 = "Что-то я играть раздумал"+ GetSexPhrase("","а") +".";
				link.l2.go = "exit_sit";
				break;
			}
			
			if(sti(iLa_Puesta) > 1000)
			{
				dialog.text = "Играть в кубики на такие деньжища? Нет, увольте... Давай ставку менять!";
				link.l1 = "Да, ты прав. Ставку нужно понизить";
				link.l1.go = "Dice_begin_2";
				link.l2 = "Что-то я вообще играть раздумал"+ GetSexPhrase("","а") +".";
				link.l2.go = "exit_sit";
				break;
			}
			dialog.text = "Хорошо, играем по " + iLa_Puesta + " монет за кубик.";
			link.l1 = "Поехали!";
			link.l1.go = "Dice_begin_go";
			pchar.GenQuest.Dice.npcharIdx = npchar.index;
			pchar.GenQuest.Dice.iRate     = sti(iLa_Puesta);
            pchar.GenQuest.Dice.SitType   = true;
		}
		break;
		
		case "Dice_begin_2":
			dialog.text = "Так какая ставка будет? (Введите ставку).";
			link.l1 = "50";
			link.l1.edit = 1;
			link.l1.go = "Dice_Node_2";
			link.l2 = "Пожалуй, я играть не буду...";
			link.l2.go = "exit_sit";
			break;

		case "Dice_begin_go":
            // анлим игры в день SetNPCQuestDate(npchar, "Dice_date_begin");
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
            LaunchDiceGame();
		break;
	    // КОСТИ <--

		/////////////////////////////////////////////
        case "talk_with_alchogol_song":
			dialog.text = "Ну... И-ик! Бывает все на свете хорошо... И-ик! В чем дело сразу не поймешь... И-ик! А просто славно ром пошел... И-ик! ямайский черный ром... И-ик!\nПодставляй, наливай!";
			link.l1 = "А дальше?";
			link.l1.go = "talk_with_alchogol_song_2";
			link.l2 = "Да ну тебя!";
			link.l2.go = "exit";
		break;
		
		case "talk_with_alchogol_song_2":
			dialog.text = "Мелькают кружки, лица, каблуки... И-ик! И полом по башке. Я пью всегда со всеми и везде... И-ик! Где выпивка? Нужна!";
			link.l1 = "А дальше?";
			link.l1.go = "talk_with_alchogol_song_3";
			link.l2 = "Да ну тебя!";
			link.l2.go = "exit";
		break;
		
		case "talk_with_alchogol_song_3":
			dialog.text = "Когда на сердце тяжесть и холодно в груди, ты пару кружек рома на грудь себе прими! И без забот и фальши все станет вдруг вокруг. Поймешь ты, что я лучший тебе я самый друг!";
			link.l1 = "Да ну тебя!";
			link.l1.go = "exit";
		break;
		
		case "talk_with_alchogol":
			Diag.TempNode = "begin_sit";
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
			pchar.questTemp.friend_in_tavern = npchar.id;
			AddDialogExitQuest("alc");
		break;

		case "begin_sit":
			Diag.TempNode = "first time";
			dialog.snd = "Voice\HADI\HADI028";
			dialog.text = LinkRandPhrase("Ик! Вот это я понимаю! Вот это по-нашему! Ну, так чего? Поставишь мне кружечку рома?",
						"Присаживайтесь, " + GetAddress_Form(npchar) + ", опрокинем по кружечке доброго ямайского рому. Это здоровью никогда не повредит. А для человека, интересующегося делами, лучше места, чем таверна не найти, это я вам точно говорю... Немного денег, пара кружек хорошей выпивки - и вы узнаете все, что хотите... и даже больше. Уж поверьте старому завсегдатаю...",
						"Эхе-хе, присаживайтесь, "+ GetSexPhrase("сударь мой","сударыня") +", выпьем... отчего ж не выпить в хорошей-то кампании? В нашей портовой таверне иногда очень интересные вещи можно услышать, если иметь терпение и пить маленькими глотками, чтобы аверкиль не свалиться... То кэп какой-нибудь загрузит лишку на борт и начнет своими похождениями хвалиться, то кто-то знающий чего сболтнет в нужной кондиции... Тут разный люд обретается, и многим есть что порассказать, поверьте, "+ GetSexPhrase("сударь мой","сударыня") +".");
			link.l1 = "Да запросто! Трактирщик, рома!";
			link.l1.go = "sit_2";
		break;

		// Церковный генератор. Квест №2 -->
		case "Alcogol_GenQuest_Church_2_1":
			dialog.text = "А то! Слыхал"+ GetSexPhrase("","а") +" - уже и церкви грабить начали!";
				link.l1 = "Ну, на такое только пираты способны...";
				link.l1.go = "Alcogol_GenQuest_Church_2_2";
				DeleteAttribute(PChar, "GenQuest.ChurchQuest_2.AskPeople");
				DeleteAttribute(PChar, "GenQuest.ChurchQuest_2.AskBarmen");
				DeleteAttribute(PChar, "GenQuest.ChurchQuest_2.AskAlcash");
			break;
			
		case "Alcogol_GenQuest_Church_2_2":
			dialog.text = "Да какие там пираты! Обыкновенные сухопутные проходимцы, к тому же явно свои, местные: откуда пиратам знать, когда церковная мошна полным-полна под завязку? Да и не стали бы они связываться.";
				link.l1 = "Храбрые однако молодчики. Отважно вскрыли хлипкий церковный засов...";
				link.l1.go = "Alcogol_GenQuest_Church_2_3";
			break;
			
		case "Alcogol_GenQuest_Church_2_3":
			dialog.text = "Во-во. И умные, сил нет. Кто ж так подставляется?!";
				link.l1 = "Твоя правда. Весь приход, затянув пояса, откладывал лишнюю монету, чтоб отнести в церковную кружку, а теперь какие-то умники одним махом нажились? Да им теперь спуску не дадут, всем миром выловят.";
				link.l1.go = "Alcogol_GenQuest_Church_2_4";
			break;
			
		case "Alcogol_GenQuest_Church_2_4":
			dialog.text = "Да не. Кто их выловит, грабанули пожертвования - и поминай как звали, за город рванули. А джунгли-то большие, их теперь ищи-свищи хоть до второго пришествия. А пройдёт месяц-другой, и про это дело совсем забудут. Я тебе другое толкую...";
				link.l1 = "Ну знаешь, такое люди не прощают.";
				link.l1.go = "Alcogol_GenQuest_Church_2_5";
			break;
			
		case "Alcogol_GenQuest_Church_2_5":
			dialog.text = "У людей память, как дырявый ялик. Люди простят. А Бог?! Он всё видит... Вот кого бояться надо! Случилась лет десять назад жуткая история с одним моим приятелем, который за неуважение к Создателю чуть не угодил морскому чёрту в зубы...";
				link.l1 = "Извини, друг, твою историю я послушаю в другой раз. Бывай.";
				link.l1.go = "Alcogol_GenQuest_Church_2_6";
			break;
			
		case "Alcogol_GenQuest_Church_2_6":
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
			AddDialogExitQuest("exit_sit");			
			string sGenLocation = QuestGetGangLocation(PChar.GenQuest.ChurchQuest_2.QuestTown);
			PChar.GenQuest.ChurchQuest_2.QuestGangJungle = sGenLocation;
			SetFunctionLocationCondition("Church_GenQuest2_GenerateBandits", sGenLocation, false);
			locations[FindLocation(sGenLocation)].DisableEncounters = true;
			PChar.GenQuest.ChurchQuest_2.WayOfShortVariant = true; // Нужно для проверки при убийстве банды
			SetFunctionTimerConditionParam("Church_GenQuest2_TimeIsLeft", 0, 0, 1, MakeInt(24 - GetHour()), false);
			Log_TestInfo("Бандюганы, грабанувшие церковь, будут в локации - " + sGenLocation + " Времени на их поиск - 1 день");
			sQuestTitle = PChar.GenQuest.ChurchQuest_2.QuestTown + "ChurchGenQuest2";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest2", "2");
			break;
		// <-- Церковный генератор. Квест №2
		//--> работорговец
			case "Jamaica_ratH_1":
				dialog.text = "А-а, Франсуа! Помню, помню такого... Не, не знаю. Но вот что я тебе скажу: расспроси-ка ты о нем нашу официантку. Сколько он здесь жил - она каждую ночь к нему бегала. Оторва, одно слово. Может, он ей чего сболтнул.";
				link.l1 = "Спасибо тебе, приятель, за добрый совет. Пойду, поговорю с ней.";
				link.l1.go = "exit_sit";
				pchar.questTemp.Slavetrader = "FindRatJamaica_W";
			break;
			
			case "EscapeSlave_Villemstad_H1":
				dialog.text = "Да-а-а, чего только не увидишь в море... Вот и в последнем рейсе тако-ое случилось...";
				link.l1 = "Ну, рассказывай, только не ври сильно. А я пока еще рому налью.";
				link.l1.go = "EscapeSlave_Villemstad_H2";
			break;
			
			case "EscapeSlave_Villemstad_H2":
				dialog.text = "Вот вам крест, благородн"+ GetSexPhrase("ый господин","ая госпожа") +" - своими глазами видел... Идет корабль, а вместо экипажа на нем - образины-гаврилы... э-э... обезьяны-гориллы... ну, или макаки, черт их разберет...";
				link.l1 = "Чего-о?! А скажи, любезный, ты и на вахте к бутылке прикладываешься?";
				link.l1.go = "EscapeSlave_Villemstad_H3";
			break;
			
			case "EscapeSlave_Villemstad_H3":
				dialog.text = "Да не сойти мне с этого места, ежели я вру! Ты разве никогда не слыхал"+ GetSexPhrase("","а") +" про корабль обезьян? Так вот, это был он... забодай меня креветка!";
				link.l1 = "Какой еще корабль обезьян? Нет, не слыхал"+ GetSexPhrase("","а") +".";
				link.l1.go = "EscapeSlave_Villemstad_H4";
			break;
			
			case "EscapeSlave_Villemstad_H4":
				dialog.text = "О-о... а я говорю, что видел его собственными глазами. В шторм это было, " + pchar.questTemp.SlavetraderAreal.add + ". Темень - хоть глаз выколи, и тут появляется из ниоткуда он - корабль с рваными парусами... У него были сломаны фок, и грот, и нок, и бак, и-и-и... короче - все было у него сломано! А он себе идет прямо против ветра и хоть бы что!\nА на палубе - столько обезьян в лохмотьях, как тюленей на лежбище! И за штурвалом стоит натуральная горилла! Роста девяти футов, в леопардовой шкуре, а на груди вместо нательного креста у него акульи зубы... Глаза горят, зубы сверкают, увидел он нас и ка-а-ак заорет нечеловеческим голосом...";
				link.l1 = "Ну, совсем ты, братец, заврался. Чего только с пьяных глаз не привидится. Ты еще скажи, что на корме у него надпись была 'Летучий Голландец'.";
				link.l1.go = "EscapeSlave_Villemstad_H5";
			break;
			
			case "EscapeSlave_Villemstad_H5":
				dialog.text = "Э, нет, это был не 'Голландец'. Говорю же - не вру я! Это был барк, а на корме было написано " + pchar.questTemp.Slavetrader.ShipName + ".";
				link.l1 = "Кха-ркх!! Черт возьми! Кажется, я знаю, что это были за обезьяны... Действительно, ром развязывает языки, надо только слушать.";
				link.l1.go = "EscapeSlave_Villemstad_H6";
			break;
			
			case "EscapeSlave_Villemstad_H6":
				dialog.text = "Ну я же говорю тебе! А ты не веришь!.. Давай, выпьем по единой и все... я швартуюсь.";
				link.l1 = "Ладно, спасибо тебе за интересную историю. Мне пора. Счастливо, приятель.";
				link.l1.go = "exit_sit";
				Pchar.quest.Slavetrader_EscapeSlave.win_condition.l1 = "location";
				Pchar.quest.Slavetrader_EscapeSlave.win_condition.l1.location = pchar.questTemp.Slavetrader.Island.Shore;
				Pchar.quest.Slavetrader_EscapeSlave.function = "Slavetrader_EscapeSlaveInShore";
				AddQuestRecord("Slavetrader", "22_4");
				AddQuestUserData("Slavetrader", "sAreal", pchar.questTemp.SlavetraderAreal.add);
				pchar.questTemp.Slavetrader = "FindMayak";
			break;
		
		//Голландский Гамбит, против всех
		case "Lucas_Tavern":
			dialog.text = "Не-е, капитан. Матросом - это не мое. У меня у самого когда-то был корабль, да... эх! Неудача однажды приключилась.";
			link.l1 = "Послушай, я вот видел на рейде необычный корабль - 'Мейфенг' называется. Я раньше таких никогда не видел. Чей он? Может, продается? Я бы посмотрел.";
			link.l1.go = "Lucas_Tavern_1";
		break;
		
		case "Lucas_Tavern_1":
			dialog.text = "Ха! Эка хватил, капитан! Не думаю, что китаец захочет продать тебе или кому-либо свою посудину.";
			link.l1 = "Китаец? А что, на Кюрасао есть китайцы, да еще и капитаны собственных кораблей?";
			link.l1.go = "Lucas_Tavern_2";
		break;
		
		case "Lucas_Tavern_2":
			dialog.text = "Как видишь, есть. Хотя корабль вовсе и не его, а принадлежит Торговой Компании. Причем, говорят, самому вице-директору, а теперь исполняющему обязанности губернатора, минхеру Роденбургу.";
			link.l1 = "О! Так Матиас Бек ушел в отставку?";
			link.l1.go = "Lucas_Tavern_3";
		break;
		
		case "Lucas_Tavern_3":
			dialog.text = "Ха! Минхер, надо почаще бывать на берегу, или новости узнавать. Матиас Бек отстранен от исполнения обязанностей губернатора и помещен в тюрьму до выяснения.";
			link.l1 = "Ну дела! Действительно, надо чаще на суше бывать. И давно это случилось?";
			link.l1.go = "Lucas_Tavern_4";
		break;
		
		case "Lucas_Tavern_4":
			dialog.text = "Да буквально два дня назад. В порт прибыла курьерская бригантина. Весьма потрепанная, надо сказать - явно побывала в серьезном бою. Капитан бригантины отправился на доклад к минхеру Роденбургу. А буквально через несколько часов Матиас Бек был арестован минхером Роденбургом и комендантом по подозрению в связи с агентами английской разведки.";
			link.l1 = "Ты рассказываешь просто невероятные вещи. Губернатор Кюрасао - английский шпион?";
			link.l1.go = "Lucas_Tavern_5";
		break;
		
		case "Lucas_Tavern_5":
			dialog.text = "Честно говоря, мне тоже в это слабо верится. Я слышал, к нам скоро должен прибыть директор Компании, сам Питер Стайвесант. Наверно, он и будет вести следствие.";
			link.l1 = "Ну, тогда, пожалуй, ты прав - рискованно беспокоить минхера Роденбурга в такое время.";
			link.l1.go = "Lucas_Tavern_6";
		break;
		
		case "Lucas_Tavern_6":
			dialog.text = "Ты здраво мыслишь, капитан! Тем более, что 'Мейфенг' сейчас под погрузкой - она сегодня ночью вернулась из плавания к берегам южного Мэйна и вновь выходит в море. И вообще, на этом корабле сейчас творится что-то невероятное - голландские матросы и гвардейцы Компании отправлены в увольнение на берег, и набирается другая команда. И скажу тебе - эти новые волонтеры через одного - пираты и уголовники, не пить мне рома до конца дней моих...";
			link.l1 = "Чудеса, да и только... Эх, жаль! Такой красивый кораблик... Ну, значит, не судьба. Спасибо за интересный рассказ, за свежие новости! Рад был пообщаться.";
			link.l1.go = "Lucas_Tavern_7";
		break;
		
		case "Lucas_Tavern_7":
			dialog.text = "И тебе спасибо за компанию и за ром, капитан! Заходи еще!";
			link.l1 = "Непременно!";
			link.l1.go = "exit_sit";
			AddQuestRecord("Holl_Gambit", "3-44");
			pchar.questTemp.HWIC.Self = "AttackMeifeng";
			//ставим прерывание на выход в море Мейфенг
			pchar.quest.HWIC_Meifeng.win_condition.l1 = "Timer";
			pchar.quest.HWIC_Meifeng.win_condition.l1.date.hour  = sti(GetTime());
			pchar.quest.HWIC_Meifeng.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.HWIC_Meifeng.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.HWIC_Meifeng.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.HWIC_Meifeng.function = "CreateMeifengOnMap";
			SetFunctionTimerCondition("QuestShipsTerms_Over", 0, 0, 12, false); // таймер
			pchar.quest.Meifeng_fail.over = "yes"; //снять прерывание
			Group_DelCharacter("Meifeng_Empty", "Longway");
			Group_DeleteGroup("Meifeng_Empty");//удалить Мейфенг из порта
		break;
		
			//Jason --> поиск дезертира
		case "FindFugitiveHb":
			npchar.quest.fugitive = "true";
			if (npchar.location == pchar.GenQuest.FindFugitive.City+"_tavern" && sti(pchar.GenQuest.FindFugitive.Chance) == 2)
			{
				pchar.GenQuest.FindFugitive.Shore = SelectQuestShoreLocation();
				dialog.text = "Ха! "+pchar.GenQuest.FindFugitive.Name+"? Знаю, знаю... Очень он нелюдимый, твой сослуживец. Одиночка, одно слово. Целый день, до ночи, на своем баркасе шарится вдоль берегов острова. Скажу по секрету: все думают, что он рыбак, а он ловит жемчуг... Хе-хе, я точно знаю!";
				link.l1 = "Хех! Так ты не подскажешь, где я смогу его найти?";
				link.l1.go = "FindFugitiveHb_1";
			}
			else
			{
				dialog.text = ""+pchar.GenQuest.FindFugitive.Name+"? Нет, клянусь всеми выпитыми кружками, я впервые слышу это имя... А ты... ик! Спроси у нашего бармена - он-то точно всё знает!";
				link.l1 = "Хм... Ладно, поспрашиваю еще людей. Ну, дружище, спасибо за компанию. Бывай!";
				link.l1.go = "exit_sit";
			}
		break;
		
		case "FindFugitiveHb_1":
			dialog.text = "Подскажу, конечно! Каждое утро его можно найти на берегу, у "+XI_ConvertString(pchar.GenQuest.FindFugitive.Shore+"Gen")+". Только приходи очень рано, не то уйдет в море, и будешь ждать до следующего утра.";
			link.l1 = "Спасибо! Ты мне очень помог, дружище. Бывай!";
			link.l1.go = "exit_sit";
			pchar.GenQuest.FindFugitive.Chance = 3; // чтобы никто больше не говорил
			AddQuestRecord("MayorsQuestsList", "12-3");
			AddQuestUserData("MayorsQuestsList", "sShore", XI_ConvertString(pchar.GenQuest.FindFugitive.Shore+"Gen"));
			sld = characterFromId("Fugitive");
			LAi_SetWarriorType(sld);
			LAi_warrior_DialogEnable(sld, true);
			sld.dialog.currentnode = "Fugitive_shore";
			LAi_SetLoginTime(sld, 4.0, 6.0);
			ChangeCharacterAddressGroup(sld, pchar.GenQuest.FindFugitive.Shore, "goto", "goto1");
		break;
		//<-- поиск дезертира
		
		// Карибские нравы
		case "trial_spy":
			dialog.text = "Да все около верфи нашей ошивался, плотников о чем-то расспрашивал... Вот и дорасспрашивался. Шепнули добрые люди коменданту, что подозрительный тип по городу расхаживает, тот его - р-раз! Ик! И в казематы. Там-то и оказалось, что он вовсе не торговец.";
			link.l1 = "Не иначе, как хотел украсть какую-то секретную разработку вашего корабела, да?";
			link.l1.go = "trial_spy_1";
		break;
		
		case "trial_spy_1":
			dialog.text = "А кто же его ведает! Но скажу тебе так, дружище: я лично уверен, что его интересовал галеон 'Алькантара'. Ик! Вот руку на отсечение даю! Этот корабль снаряжает сам сеньор губернатор, так что целью этого прохвоста наверняка был сбор информации об этом судне.";
			link.l1 = "Ха! Вполне возможно. Наверняка сеньор губернатор повезет на нем что-то ценное...";
			link.l1.go = "trial_spy_2";
		break;
		
		case "trial_spy_2":
			dialog.text = "А то как же! Уж наверняка что-то стоящее внимания, ик! Да и поговаривают, что видали рыбаки в наших водах какое-то чужое военное судно, вроде как фрегат. Уж не оттуда ли этот шпик пришел?";
			link.l1 = "Всякое может быть. Ладно, приятель, спасибо за компанию, пора мне уже!";
			link.l1.go = "exit_sit";
			pchar.questTemp.Trial = "spy_drink";
			AddQuestRecord("Trial", "14");
		break;
		
		case "sit_2":
			Statistic_AddValue(pchar, "TavernDrink", 1);
			AddMoneyToCharacter(pchar, -2);
			//navy --> Alcohol - rum count;
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
			//<-- navy
			WaitDate("",0,0,0, 0, 30);
			
			if (CheckAttribute(pchar, "questTemp.Rum"))
			{
				DeleteAttribute(pchar, "chr_ai.drunk");
				if (sti(pchar.questTemp.Rum) < 3) LAi_AlcoholSetDrunk(pchar, 51, 5600);
				else
				{
					LAi_AlcoholSetDrunk(pchar, 71, sti(pchar.questTemp.Rum)*2800);
					Pchar.GenQuest.CamShuttle = makeint(sti(pchar.questTemp.Rum)/2); // Jason
				}
			}
			
			
			dialog.text = LinkRandPhrase("Ты настоящ"+ GetSexPhrase("ий друг","ая морячка") +"! Давай за знакомство!",
										 "Ик! Какой ром! Ну... вздрогнем!",
										 "За твое здоровье и за твою щедрость!");
			link.l1 = "Эх, забористый ром. Ладно, мне уже пора, удачно посидеть.";
			link.l1.go = "exit_sit";
			if (makeint(pchar.money) >=2)
			{
				link.l2 = "Давай еще по одной кружечке.";
				link.l2.go = "sit_3";
			}

			link.l4 = LinkRandPhrase("Кажется, что провел"+ GetSexPhrase("","а") +" в море целую вечность. Что новенького в ваших краях?",
									"Расскажи-ка мне, о чем теперь болтают? Не зря же я пою тебя ромом...",
									"Скажи мне, братец, какие байки ходят по тавернам?");
			link.l4.go = "rumours_habitue";
		break;

		case "sit_3":
			int iSituation;
			if(IsEquipCharacterByArtefact(pchar, "totem_01")) iSituation = makeint(rand(3));
			else iSituation = makeint(rand(5));
			switch (iSituation)
			{
				case 0:
					dialog.text = "О! Здравая идея!";
					link.l1 = "Трактирщик! Рома!";
					link.l1.go = "sit_2";
				break;

				case 1:
					dialog.text = "За тебя! А, дьявол! Кто это?!";
					link.l1 = "А? Что? Где? Показалось видать.";
					link.l1.go = "sit_2";// to_do "sit_case_5_exit";
				break;
				
                case 2:
	         		dialog.text = "Пить так пить! Еще давай?";
					link.l1 = "Наливай!";
					link.l1.go = "sit_2";
                break;				
				
				case 3:
					if(rand(1) == 0)
					{
						dialog.text = RandPhraseSimple("Вот вы, " + GetAddress_Form(NPChar) + ", наверное думаете, что вами все восхищаются, да? А по мне - так вы обычн"+ GetSexPhrase("ый","ая") +" разбойни-"+ GetSexPhrase("гик","гица") +"!.. и убийца. Придумали тоже - 'бла-ародный пират'! Бандит - он и есть бандит, что на мор-ик, что на суше...",
							"Ик! "+ GetSexPhrase("Под... подонок","Др... дрянь") +"! Ты х-хочешь меня споить, ик! И украсть мои деньги!");
						link.l1 = "Я вижу, ты уже лишнего на борт принял... иди-ка - проспись, да и мне уже пора.";
						link.l1.go = "exit_sit";						
						link.l2 = "Что-то не нравится мне твой тон, приятель. Попридержал бы ты язык.";
						link.l2.go = "sit_case_2_enemy";
						link.l3 = "Ты кого бандитом назвал, сухопутная крыса?! Поглядим, как ты запоешь, с дырой в брюхе!";
						link.l3.go = "sit_case_2_enemy2";
					}
					else
					{
						dialog.text = RandPhraseSimple("Чего ты на меня так уставил"+ GetSexPhrase("ся","ась") +"? Н-небось, хочешь споить и обчистить карманы?! Понаехало здесь разного сброду!  Ик!.. Честному человеку уже и в таверну зайти нельзя!",
							"Ты меня уважаешь?.. Уважаешь, я тебя с-спрашиваю?!! А-то гляди у меня... Я ни-ко-му не спущу - сразу промеж глаз ка-ак... и всё - заказывай п-панихиду.");
						link.l1 = "Приятель, вижу - трюм у тебя под завязку. Шёл бы ты домой... да и мне уже пора.";	
						link.l1.go = "exit_sit";
						link.l2 = "Не так шибко, парень. Ты всё-таки знай, с кем разговариваешь...";
						link.l2.go = "sit_case_2_enemy1";
						link.l3 = "Ты на кого рот разинул?! Сейчас я тебя научу уму-разуму!";
						link.l3.go = "sit_case_2_enemy2";
					}
					link.l4 = "Спокойней! Ты чего забыл? Я твой единственный настоящий друг!";
					link.l4.go = "sit_case_2_friend";					
				break;

				case 4:
					dialog.text = "Слушай! Ты х-хороший человек! М-может быть, т-ты поможешь мне в... в... в одном дельце?";
					link.l1 = "Нет, пожалуй, мне уже пора идти.";
					link.l1.go = "exit_sit";
					link.l2 = "К-конечно! Ведь мы же... ик... друзья!";
					link.l2.go = "sit_case_3";
				break;

				case 5:
					if (GetSummonSkillFromName(pchar, SKILL_SNEAK) > rand(110) )
					{
						dialog.text = "...И тогда я схв-схватил его шпагу за л-лезвие и...";
						link.l1 = "... а она мне и говорит...";
						link.l1.go = "sit_2";
					}
					else
					{
						dialog.text = "...И тогда я схв-схватил его шпагу за л-лезвие и...";
						link.l1 = "... и-ик! А она мне и г-говорит...";
						link.l1.go = "sit_case_4_exit";
					}
				break;
			}
		break;

		case "sit_case_5_exit": // дуэль
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
			AddDialogExitQuest("fighting");
		break;

		case "sit_case_4_exit":
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
			pchar.questTemp.friend_in_tavern = npchar.id;
			AddDialogExitQuest("without_memory");
		break;

		case "sit_case_3":
			dialog.snd = "Voice\HADI\HADI037";
			dialog.text = "Дело в т-том, что м-меня оскорбил один из с-солдат. В-вот!";
			link.l1 = "С-солдат? Н-нет, я, пожалуй пас.";
			link.l1.go = "exit_sit";
			link.l2 = "Спокойней! Ты чего забыл? Я твой единственный настоящий друг!";
			link.l2.go = "sit_2";
		break;

		case "sit_case_2_friend":
			dialog.snd = "Voice\HADI\HADI038";
			dialog.text = "Ты? К-какой ты мне друг?! Н-нет! Ты хочешь... ик...  ты хочешь меня убить! В-вот!";
			link.l1 = "Ладно, вижу, тебе уже хватит на сегодня. Прощай.";
			link.l1.go = "exit_sit";
			link.l2 = "Что? Да я тебе сейчас докажу, что я не хочу тебя убивать! Я тебе сейчас руку... ик... отрежу!";
			link.l2.go = "sit_case_2_friend_2";
		break;

		case "sit_case_2_friend_2":
			dialog.snd = "Voice\HADI\HADI039";
			dialog.text = "А-а-а! Уберите "+ GetSexPhrase("его","ее") +" от меня!!";
			link.l1 = "Да ты успокойся... ик... больно не будет!";
			link.l1.go = "tavern_keeper";
		break;

		case "sit_case_2_enemy":
			dialog.snd = "Voice\HADI\HADI040";
			dialog.text = "А вы меня не пугайте!.. не на того напал-ик!.. Таким как вы, самое место на виселице, как и всякому отре-ик! Сколько перья ни распускай - а гнилой рыбой за версту несёт. И выбирать выражения с таки-ик, как вы, я не намерен!";
			link.l1 = "Арх, да что с такой пьяни взять. Пойду, подышу свежим воздухом...";
			link.l1.go = "exit_sit1";
			link.l2 = "А ты, парень, зарвался. Сейчас я запихну эти слова тебе в глотку!";
			link.l2.go = "sit_case_2_enemy3";
		break;

		case "sit_case_2_enemy1":		
			dialog.snd = "Voice\HADI\HADI040";
			dialog.text = "Чего-о?! Да я тебя сейчас вот этими руками... Ик!.. От меня ещё ни один не ушёл!";
			link.l1 = "Вот же пьяная свинья, такой вечер испортил. Ладно, лови своих тараканов, пойду я, пожалуй.";
			link.l1.go = "exit_sit1";
			link.l2 = RandSwear() + "Вижу, ты не угомонишься. Придётся дать урок хороших манер.";
			link.l2.go = "sit_case_2_enemy3";
		break;
		
		case "sit_case_2_enemy2":	
			ChangeCharacterComplexReputation(pchar,"nobility", -2);
			if(rand(1) == 0)
			{
				dialog.text = LinkRandPhrase("Подходи, каналья! Сейчас ты получишь сполна!", RandSwear() + "Сейчас я тебя разделаю, как подобает!","Ха! Давай, моряч"+ GetSexPhrase("ок","ка") +" - поглядим, что ты можешь на суше!");
				link.l1 = RandPhraseSimple(RandPhraseSimple("Клянусь, ты об этом пожалеешь!!!","Я укорочу твой поганый язык по самые уши!"), RandPhraseSimple("Я выпотрошу тебя, как селёдку!","Клянусь, я заставлю тебя замолчать!!!"));
				link.l1.go = "fight_right_now";
			}
			else
			{
				dialog.text = "А ну-ка, парни! выметем эту чешую из нашего города!";
				link.l1 = RandPhraseSimple(RandSwear() + "Ну, молитесь, недоноски!","Ах, ты ещё и не один!!! Ну - будет тебе в аду компания!");
				link.l1.go = "fight_right_now_1";
			}
		break;
		
		case "sit_case_2_enemy3":	
			ChangeCharacterComplexReputation(pchar,"nobility", 2);
			if(rand(1) == 0)
			{
				dialog.text = LinkRandPhrase("Подходи, каналья! Сейчас ты получишь сполна!", RandSwear() + "Сейчас я тебя разделаю, как подобает!","Ха! Давай, моряч"+ GetSexPhrase("ок","ка") +" - поглядим, что ты можешь на суше!");
				link.l1 = RandPhraseSimple(RandPhraseSimple("Клянусь, ты об этом пожалеешь!!!","Я укорочу твой поганый язык по самые уши!"), RandPhraseSimple("Я выпотрошу тебя, как селёдку!","Клянусь, я заставлю тебя замолчать!!!"));
				link.l1.go = "fight_right_now";
			}
			else
			{
				dialog.text = "А ну-ка, парни! выметем эту чешую из нашего города!";
				link.l1 = RandPhraseSimple(RandSwear() + "Ну, молитесь, недоноски!","Ах, ты ещё и не один!!! Ну - будет тебе в аду компания!");
				link.l1.go = "fight_right_now_1";
			}
		break;		
		
		case "exit_sit":			
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
			AddDialogExitQuest("exit_sit");
		break;

		case "exit_sit1":
			ChangeCharacterComplexReputationToNeutral(pchar,"nobility", 2.0);			
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
			AddDialogExitQuest("exit_sit");
		break;
				
		case "tavern_keeper":			
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
			AddDialogExitQuest("tavern_keeper");
		break;
	}
}

bool CheckFreeSitFront(ref _npchar)
{
 	ref rCharacter; //ищем
	int n;

	if (!CheckAttribute(_npchar, "Default.ToLocator")) return false;
	
	for (n=0; n<MAX_CHARACTERS; n++)
	{
		makeref(rCharacter, Characters[n]);
		if (CheckAttribute(rCharacter, "location") && rCharacter.location == _npchar.location)
		{
            if (rCharacter.location.locator == _npchar.Default.ToLocator)
                return  false;
		}
    }
    return  true;
}
