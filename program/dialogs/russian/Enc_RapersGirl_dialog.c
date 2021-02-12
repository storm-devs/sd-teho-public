void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, Diag;
	int i, iRnd, iRnd1;
	string sTemp, sGems;
	
	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(Diag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "exit_1":
			AddDialogExitQuest("LandEnc_RapersTalk");
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();			
		break;
		
		case "exit":
			LAi_SetCitizenTypeNoGroup(NPChar);
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
		break;

		case "Begin_1":
			LAi_RemoveCheckMinHP(npchar);
			for(i = 1; i <= 3; i++)
			{
				if (GetCharacterIndex("GangMan_" + i) == -1) continue;
				sld = CharacterFromID("GangMan_" + i);
				LAi_type_actor_Reset(sld);
			}
			dialog.text = RandPhraseSimple(""+ GetSexPhrase("Капитан","Девушка") +"! Будьте милосердны, защитите меня! Прошу вас!","На помощь! "+ GetSexPhrase("Незнакомец","Девушка") +", спасите меня, умоляю!");
			link.l1 = LinkRandPhrase("Что случилось?","Что стряслось?",RandPhraseSimple("В чём дело?","Что происходит?"));
			link.l1.go = "Begin_11";
		break;

		case "Begin_2":
			LAi_RemoveCheckMinHP(NPChar);
			for(i = 1; i <= 3; i++)
			{
				if (GetCharacterIndex("GangMan_" + i) == -1) continue;
				sld = CharacterFromID("GangMan_" + i);
				LAi_type_actor_Reset(sld);
			}
			dialog.text = RandPhraseSimple(""+ GetSexPhrase("Капитан! Капитан","Девушка! Девушка") +", постойте!","Постойте, "+ GetSexPhrase("капитан","девушка") +"! Прошу вас.");
			link.l1 = LinkRandPhrase("Что случилось?","Что стряслось?",RandPhraseSimple("В чём дело?","Что происходит?"));
			link.l1.go = "Begin_21";
		break;

		case "Begin_3":
			LAi_RemoveCheckMinHP(NPChar);
			for(i = 1; i <= 3; i++)
			{
				if (GetCharacterIndex("GangMan_" + i) == -1) continue;
				sld = CharacterFromID("GangMan_" + i);
				LAi_type_actor_Reset(sld);
			}
			dialog.text = "Ах, незнаком"+ GetSexPhrase("ец","ка") +"! помогите бедной девушке, прошу вас! Эти люди замышляют что-то недоброе!";
			link.l1 = LinkRandPhrase("Что случилось?","Что стряслось?",RandPhraseSimple("В чём дело?","Что происходит?"));
			link.l1.go = "Begin_31";
		break;
		
		case "Begin_11":
			dialog.text = RandPhraseSimple("Эти негодяи хотят надругаться надо мной! Ради всего святого, не позволяйте им этого!","Христа ради, защитите меня от этих чудовищ! Они хотят обесчестить меня!");
			link.l1 = "Не паникуй"+ GetSexPhrase(", красавица","") +". Сейчас разберёмся.";
			link.l1.go = "exit_1";
		break;

		case "Begin_21":
			dialog.text = RandPhraseSimple("За мной гонятся насильники!"+ GetSexPhrase(" Не могли бы вы заступиться за честь дамы?","") +"","Капитан, "+ GetSexPhrase("будьте мужчиной","вы же женщина") +" - спасите девушку от бесчестия!");
			link.l1 = "Не паникуй"+ GetSexPhrase(", красавица","") +". Сейчас разберёмся.";
			link.l1.go = "exit_1";
		break;
		
		case "Begin_31":
			dialog.text = "За мной гонятся... за мной гонятся бандиты! Скажите им, чтобы оставили меня в покое!";
			link.l1 = "Не паникуй"+ GetSexPhrase(", красавица","") +". Сейчас разберёмся.";
			link.l1.go = "exit_1";
		break;
		
		case "First time":
			LAi_RemoveCheckMinHP(npchar);
			for(i = 1; i <= 3; i++)
			{
				if (GetCharacterIndex("GangMan_" + i) == -1) continue;
				sld = CharacterFromID("GangMan_" + i);
				LAi_type_actor_Reset(sld);
			}
			dialog.text = LinkRandPhrase("Помогите! Помогите! Эти люди преследуют меня! Спасите!",
				"А-а! На помощь, "+ GetSexPhrase("незнакомец","девушка") +"! Спасите меня от этих мерзавцев!",
				"Будьте милосердны, защитите меня от этих негодяев! Прошу вас!");
			Link.l1 = LinkRandPhrase("Что происходит?", "В чем дело?", "Что случилось?");
			Link.l1.go = "Node_2";			
		break;        

		case "Node_2":
			dialog.text = LinkRandPhrase("Они... они хотят надругаться надо мной! Умоляю вас, не позволяйте им этого! Спасите меня!",
				"Эти звери... они хотят сделать что-то ужасное... Защитите меня от них, пожалуйста!",
				"Во имя Господа нашего - защитите меня от этих похотливых чудовищ! Они хотят обесчестить меня!");
			Link.l1 = "Так, сейчас разберемся.";
			Link.l1.go = "exit_1";			
		break;

		case "ThanksForHelp":
			if(pchar.GenQuest.EncGirl == "Begin_11")
			{
				if(rand(1) == 0)
				{
					dialog.text = RandPhraseSimple("Спасибо вам, "+ GetSexPhrase("капитан","девушка") +". Я так испугалась!","Спасибо, что спасли меня! Я так вам благодарна!");
					link.l1 = "Ну всё, "+ GetSexPhrase("красавица","милочка") +", успокойся - теперь уже всё позади.";
					link.l1.go = "Node_11";
				}
				else
				{
					dialog.text = "Ах, спасибо, "+ GetSexPhrase("благородный человек! Вы настоящий джентльмен!","девушка! Вы меня спасли!") +"";
					link.l1 = "Я не мог"+ GetSexPhrase("","ла") +" поступить иначе.";
					link.l1.go = "Node_12";
				}
			}
			if(pchar.GenQuest.EncGirl == "Begin_22")
			{
				if(rand(1) == 0)
				{
					dialog.text = "Ах, спасибо, "+ GetSexPhrase("благородный человек! Вы настоящий джентльмен!","незнакомка! Вы меня спасли!") +"";
					link.l1 = "Я не мог"+ GetSexPhrase("","ла") +" поступить иначе.";
					link.l1.go = "Node_12";	
				}
				else
				{
					dialog.text = "Что же вы наделали?! Зачем вы их убили?! Теперь меня будут искать! Господи, ну за что мне такое наказание?!";
					link.l1 = "Вот это благодарность!";
					link.l1.go = "Node_22";
				}
			}
			if(pchar.GenQuest.EncGirl == "Begin_33")
			{
				dialog.text = "Ну что вы наделали, "+ GetSexPhrase("капитан","девушка") +"?! Зачем вы их убили?! Их действительно послал мой отец!.. Боже! он меня просто убьёт...";
				link.l1 = "Ну и дела! А чем ты думала, когда кричала, что за тобой бандиты гонятся?!";
				link.l1.go = "Node_31";
			}
		break;
		
		case "Node_11":
			Diag.TempNode = "Node_1Next";
			addMoneyToCharacter(pchar, makeint((sti(pchar.rank))*25 + frand(2)*500));
			dialog.text = "У меня с собой есть немного денег, не побрезгуйте - возьмите их в знак благодарности. Я теперь всем расскажу, "+ GetSexPhrase("какой вы благородный и храбрый человек","какая вы благородная и храбрая женщина") +".";
			link.l1 = "Хорошо-хорошо, расскажешь. Спасибо... А теперь иди домой.";
			link.l1.go = "exit";
			pchar.GenQuest.EncGirl = "close";
			sGlobalTemp = "Saved_CangGirl";
			Diag.CurrentNode = Diag.TempNode;
		break;
		
		case "Node_12":
			dialog.text = "Я до сих пор не могу прийти в себя. Не проводите "+ GetSexPhrase("даму","меня") +" до поселения " + XI_ConvertString("Colony" + pchar.GenQuest.EncGirl.city) + "? А то мне теперь за каждым кустом насильники мерещатся.";
			link.l1 = RandPhraseSimple("Да не волнуйся ты так... Ну ладно, пошли.","Что ж ты трусиха такая? Пошли, провожу.");
			link.l1.go = "Node_121Next";
			link.l2 = "Извини, милая, некогда мне - дела ждут.";
			link.l2.go = "Node_3End";
		break;
						
		case "Node_22":
			dialog.text = "Я же думала, что вы их просто напугаете!.. Вы должны отвести меня в таверну поселения " + XI_ConvertString("Colony" + pchar.GenQuest.EncGirl.city) + ", мне больше не у кого просить помощи.";
			link.l1 = "А, чёрт! Пошли. Только не отставай.";
			link.l1.go = "Node_122Next";
			link.l2 = "Ну уж нет, "+ GetSexPhrase("красавица","милочка") +"! На сегодня сюрпризов достаточно. Ищи себе другого помощника.";
			link.l2.go = "Node_3End";
		break;
		
		case "Node_31":
			dialog.text = "А что мне оставалось делать?! Отец меня замуж выдать хочет за сына ростовщика - этого слюнтяя... потому что у его папаши в сундуках полно денег. А я люблю другого! Отведите меня к нему, прошу вас.";
			link.l1 = "Вот навязалась на мою голову! Пошли, куда тебя теперь денешь... А как зовут твоего избранника, куда вести-то?";
			link.l1.go = "Node_32";
			link.l2 = "Ну уж нет, "+ GetSexPhrase("красавица","милочка") +"! На сегодня сюрпризов достаточно. Ищи себе другого помощника.";
			link.l2.go = "Node_3End";
		break;
		
		case "Node_32":
			pchar.GenQuest.EncGirl.sLoverId = GenerateRandomName(sti(npchar.nation), "man"); 
			dialog.text = "Его зовут " + pchar.GenQuest.EncGirl.sLoverId + ", он приезжий. Сейчас живёт в поселении " + XI_ConvertString("Colony" + pchar.GenQuest.EncGirl.city) + ", искал там работу, но у нас с этим туго. Все говорят - кризис... А домой мне всё равно теперь хода нет.";
			link.l1 = "Кризис, говоришь? Ну-ну... Для настоящего пирата кризис - это когда на горизонте караван, а в небе полный штиль... ";
			link.l1.go = "Node_12Next";
		break;
		
		case "Node_12Next":
			pchar.quest.LandEnc_RapersBadExit.over = "yes";
			Diag.TempNode = "Node_12End";
			Diag.CurrentNode = Diag.TempNode;
			pchar.GenQuest.EncGirl = "FindLover";
			pchar.GenQuest.EncGirl.MeetSoldiers = 2;
			AddDialogExitQuestFunction("EncGirl_GirlFollow");
			DialogExit();
		break;
		
		case "Node_121Next":
			pchar.quest.LandEnc_RapersBadExit.over = "yes";
			Diag.TempNode = "Node_253";
			pchar.GenQuest.EncGirl = "FindCoins";
			pchar.GenQuest.EncGirl.MeetSoldiers = 1;
			Diag.CurrentNode = Diag.TempNode;
			pchar.quest.EncGirl_DeliveBack.win_condition.l1 = "location";
			pchar.quest.EncGirl_DeliveBack.win_condition.l1.location = pchar.GenQuest.EncGirl.city + "_town";
			pchar.quest.EncGirl_DeliveBack.function = "EncGirl_DeliveBack";
			AddDialogExitQuestFunction("EncGirl_GirlFollow");
			DialogExit();
		break;
		
		case "Node_122Next":
			pchar.quest.LandEnc_RapersBadExit.over = "yes";
			Diag.TempNode = "Node_12End";
			pchar.GenQuest.EncGirl = "HorseToTavern";
			pchar.GenQuest.EncGirl.MeetSoldiers = 1;
			Diag.CurrentNode = Diag.TempNode;
			pchar.quest.EncGirl_DeliveBack.win_condition.l1 = "location";
			pchar.quest.EncGirl_DeliveBack.win_condition.l1.location = pchar.GenQuest.EncGirl.city + "_tavern";
			pchar.quest.EncGirl_DeliveBack.function = "EncGirl_DeliveBack";		
			AddDialogExitQuestFunction("EncGirl_GirlFollow");
			DialogExit();
		break;
		
		case "Node_12End":
			Diag.TempNode = "Node_12End";
			dialog.text = RandPhraseSimple("Вы знаете, "+ GetSexPhrase("капитан","девушка") +"? А я так испугалась, что до сих пор коленки дрожат.","Ох и натерпелась же я страху. Хорошо, что вас вовремя Бог послал.");
			link.l1 = RandPhraseSimple("Благодари Бога, что цела осталась.","Не бери близко к сердцу. Хорошо, что всё так обошлось.");
			link.l1.go = "exit";
		break;
		
		case "Node_1Next":
			dialog.text = RandPhraseSimple("Спасибо вам, "+ GetSexPhrase("капитан","девушка") +", ещё раз. Уж и не знаю, как благодарить.","Большое вам спасибо, "+ GetSexPhrase("капитан","девушка") +". Даже не представляю, что бы я делала, не подоспей вы ко времени.");
			link.l1 = RandPhraseSimple("Впредь будет тебе наука. Ну, счастливо оставаться...","В следующий раз будешь осторожнее... Ну, иди домой, меня дела ждут.");
			link.l1.go = "Node_1End";
			link.l2 = "Разве можно быть такой беспечной? Чего тебя одну в джунгли понесло?";
			link.l2.go = "Node_13";
		break;
		
		case "Node_1End":
			sTemp = LAi_FindNearestFreeLocator2Pchar("reload");
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", sTemp, "none", "", "","OpenTheDoors", -1.0);
			pchar.GenQuest.EncGirl = "close";
			sGlobalTemp = "Saved_CangGirl";
			DialogExit();
			AddDialogExitQuest("pchar_back_to_player");			
		break;
		
		case "Node_3End":
			Diag.TempNode = "Node_3Final";
			sTemp = LAi_FindNearestFreeLocator2Pchar("reload");
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", sTemp, "none", "", "","OpenTheDoors", -1.0);
			pchar.GenQuest.EncGirl = "close";
			sGlobalTemp = "Saved_CangGirl";
			ChangeCharacterComplexReputation(pchar,"nobility", -3);
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
		break;
		
		case "Node_3Final":
			Diag.TempNode = "Node_3Final";
			dialog.text = RandPhraseSimple("Неужели вы передумали?","Капитан, как хорошо, что вы передумали!");
			link.l1 = RandPhraseSimple("Нет-нет, дорогуша, без меня.","Даже не надейся...");
			link.l1.go = "exit";
		break;
		
		case "Node_13":
			if(pchar.GenQuest.EncGirl == "FindCoins") 
			{
				pchar.quest.LandEnc_RapersBadExit.win_condition.l1 = "ExitFromLocation";
				pchar.quest.LandEnc_RapersBadExit.win_condition.l1.location = pchar.location;
				pchar.quest.LandEnc_RapersBadExit.win_condition = "LandEnc_RapersBadExit";
			}
			pchar.GenQuest.EncGirl = "Begin_11";
			switch(sti(pchar.GenQuest.EncGirl.variant))
			{
				case 0:
					if(rand(1) == 0)
					{
						dialog.text = "Вы, наверное, будете смеяться... Я зелье приворотное собирала... Одна ведунья сказала, что есть такой корень, который в любовных делах помогает.";
						link.l1 = "Господи! И чем "+ GetSexPhrase("эти женщины думают","ты только думала") +"?! Видать, много набрала, что за тобой целая свора женихов увязалась - насилу отбил"+ GetSexPhrase("","а") +". Ха-ха-ха-ха... Ну, бывай здорова.";
						link.l1.go = "Node_1End";
					}
					else
					{
						dialog.text = "Просто погулять решила, воздухом дышала, травы собирала... Да видать, не в добрый час вышла.";
						link.l1 = "Что за легкомыслие?! Благодари Бога, что всё так обернулось... Ну, всего хорошего.";
						link.l1.go = "Node_1End";
					}
				break;
				case 1:
					dialog.text = "Хозяйка моя где-то здесь жемчужное ожерелье рассыпала, когда прогуливалась. Домой пришла - раскричалась, и меня послала искать. Говорит: 'Пока жемчужины не соберёшь - домой не приходи'... А я даже места толком не знаю. Да и как их разыщешь - малюсенькие жемчужины в такой траве? Вот, брожу теперь - не знаю, что и делать.";
					link.l1 = "А что за ожерелье? Может дешевле выйдет новое купить, чем по джунглям слоняться незнамо где?.. Много в нём жемчуга было?";
					link.l1.go = "Node_131";
				break;
				case 2:
					dialog.text = "Мне от покойного отца карта досталась, а его дружки отнять хотели. Пока отец жив был, все перед ним дрожали, а как похоронила - совсем житья не стало. Сначала пытались карту выкупить, а когда отказала, угрожать начали. ";
					link.l1 = "А что же не продала? Чего в этой карте такого, что пираты за ней целыми шайками рыщут?";
					link.l1.go = "Node_132";
				break;
			}	
		break;
		
		case "Node_131":
			pchar.GenQuest.EncGirl.SmallCoins = rand(25) + 20;
			pchar.GenQuest.EncGirl.BigCoins = rand(15) + 5;
			dialog.text = "Там жемчуг был отборный. Такое задёшево не купишь. В нём было " + sti(pchar.GenQuest.EncGirl.BigCoins) + " крупных жемчужин и " + sti(pchar.GenQuest.EncGirl.SmallCoins) + " мелких. Если бы такие жемчужины удалось подобрать, то можно было бы изготовить подобное ожерелье по заказу.";
			link.l1 = "Да, нелёгкую работу твоя хозяйка задала... Что ж, ищи, раз поручено. Счастливо оставаться.";
			link.l1.go = "Node_131End";
			link.l2 = "Бесполезно твоё занятие... Искать жемчуг в такой траве - всё равно, что иголку в стоге сена. Тем более, точного места ты не знаешь...";
			link.l2.go = "Node_133";
		break;
		
		case "Node_131End":
			Diag.TempNode = "Node_12End";
			pchar.GenQuest.EncGirl = "close";
			sGlobalTemp = "Saved_CangGirl";
			ChangeCharacterComplexReputation(pchar,"nobility", -2);
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
			pchar.quest.LandEnc_RapersBadExit.win_condition.l1 = "ExitFromLocation";
			pchar.quest.LandEnc_RapersBadExit.win_condition.l1.location = pchar.location;
			pchar.quest.LandEnc_RapersBadExit.win_condition = "LandEnc_RapersBadExit";
			AddDialogExitQuest("pchar_back_to_player");			
		break;
		
		case "Node_132":
			pchar.GenQuest.EncGirl.mapOwner = "l" + rand(GetNamesCount(NAMETYPE_ORIG) - 1); 
			dialog.text = "Отец на ней место отметил, где свои сокровища спрятал. Вы не слыхали о знаменитом пирате " + GetName( NAMETYPE_ORIG, pchar.GenQuest.EncGirl.mapOwner, NAME_VOC) + "?";
			link.l1 = "Нет, ничего не слыхал"+ GetSexPhrase("","а") +".";
			link.l1.go = "Node_132_1";
		break;
		
		case "Node_132_1":
			dialog.text = "Так вот " + GetName( NAMETYPE_ORIG, pchar.GenQuest.EncGirl.mapOwner, NAME_NOM) + " и был мой отец. Все его боялись, даже пикнуть никто не смел. Теперь, конечно, обнаглели. Когда я карту продать отказалась, заявили, что их доля в этом кладе тоже есть. Я карту спрятать хотела, а они выследили...";
			link.l1 = "Так чего её прятать? Нанимай судно и езжай - забирай свои сокровища. Даром что ли родитель твой их припрятывал?";
			link.l1.go = "Node_132_2";
		break;
		
		case "Node_132_2":
			dialog.text = "Легко сказать. У меня денег на судно нет, да и боюсь я... Как я всё это буду выкапывать, перетаскивать... а везти куда? Любой меня по дороге ограбит, ещё и жизни лишит...";
			link.l1 = "Да и то верно... Ну что ж, иди - прячь свою карту. Только место потом не забудь.";
			link.l1.go = "Node_132_2End";
			if(GetCharacterItem(pchar, "map_full") == 0)
			{
				link.l2 = "Хм, верно говоришь. Так тем более, продавать надо было.";
				link.l2.go = "Node_132_3";
			}
			link.l3 = "А попутчика найти не пробовала?";
			link.l3.go = "Node_132_8";	
		break;
		
		case "Node_132_2End":
			Diag.TempNode = "Node_12End";
			pchar.GenQuest.EncGirl = "close";
			sGlobalTemp = "Saved_CangGirl";
			sTemp = LAi_FindNearestFreeLocator2Pchar("reload");
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", sTemp, "none", "", "","OpenTheDoors", -1.0);
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
			AddDialogExitQuest("pchar_back_to_player");			
		break;
		
		case "Node_132_3":
			dialog.text = "Жалко... Отец мне рассказывал, сколько он там всего спрятал. Кто же мне столько заплатит?";
			link.l1 = "Смотри, не продешеви. Любое золото не стоит того, чтоб из-за него голову сложить. Да и забот у тебя никаких - взяла деньги и пошла с улыбочкой...";
			link.l1.go = "Node_132_4";
		break;
		
		case "Node_132_4":
			pchar.GenQuest.EncGirl.mapPrice = 20000 + 500 * sti(pchar.rank);
			dialog.text = "Заманчиво конечно... А сколько вы готовы за неё дать?";
			link.l1 = "Не думаю, что она может стоить дороже " + sti(pchar.GenQuest.EncGirl.mapPrice) + " песо.";
			link.l1.go = "Node_132_5";
		break;
		
		case "Node_132_5":
			if((GetSummonSkillFromName(pchar, SKILL_COMMERCE) + GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) + GetSummonSkillFromName(pchar, SKILL_FORTUNE)) > (rand(220) + 100) && (makeint(pchar.money) >= sti(pchar.GenQuest.EncGirl.mapPrice)))
			{
				dialog.text = "Эх, женская доля... Я согласна. Избавлюсь наконец от этого кошмара... Уж лучше пусть эта карта достанется вам"+ GetSexPhrase(" - благородному джентльмену","") +", чем каким-то проходимцам.";
				link.l1 = "Вот и отлично. Держи деньги, только не трать все сразу.";
				link.l1.go = "Node_132_6";
			}
			else
			{
				dialog.text = "Нет, "+ GetSexPhrase("капитан","девушка") +". Не стану я её продавать. Вот замуж выйду, мы с мужем клад и вывезем... ";
				link.l1 = "Ну, тебе решать. Всё равно, за твою бумажку никто больше не даст.";
				link.l1.go = "Node_132_2End";
			}	
		break;
		
		case "Node_132_6":
			AddMoneyToCharacter(pchar, -makeint(sti(pchar.GenQuest.EncGirl.mapPrice))); 
			GiveItem2Character(pchar, "map_full");
			Diag.TempNode = "Node_12End";
			pchar.GenQuest.EncGirl = "close";
			sGlobalTemp = "Saved_CangGirl";
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
			AddDialogExitQuest("pchar_back_to_player");			
		break;
		
		case "Node_132_8":
			dialog.text = "Где же их найдёшь? На молодых надежды никакой - они сразу под юбку лезут, им и сокровища не нужны. А старых я боюсь, они мне дружков отца напоминают, все такие хитрые - не знаешь, чего от них ждать.";
			link.l1 = "Ха-ха-ха... А со мной за кладом поедешь?";
			link.l1.go = "Node_132_9";
		break;
		
		case "Node_132_9":
			dialog.text = "С вами?! А можно? Только вы потом меня назад сюда привезёте, в поселение " + XI_ConvertString("Colony" + pchar.GenQuest.EncGirl.city) + ", ладно?!";
			link.l1 = "Поехали, если скажешь куда.";
			link.l1.go = "Node_132_10";
		break;
		
		case "Node_132_10":
			EncGirl_GenQuest_GetChestPlaceName();
			dialog.text = "Клад спрятан в пещере на " + XI_ConvertString(pchar.GenQuest.EncGirl.islandId + "Acc") + ", нам нужно высадиться у " + XI_ConvertString(pchar.GenQuest.EncGirl.shoreId + "Gen") + ", а место покажу сама... Только, чур, делить пополам будем!";
			link.l1 = "Хорошо-хорошо, не обижу. Иди за мной и не отставай.";
			link.l1.go = "Node_132_11";
		break;
		
		case "Node_132_11":
			ReOpenQuestHeader("JungleGirl");
			AddQuestRecord("JungleGirl", "4");
			AddQuestUserData("JungleGirl", "sName", pchar.GenQuest.EncGirl.name);
			AddQuestUserData("JungleGirl", "sPirateName", GetName( NAMETYPE_ORIG, pchar.GenQuest.EncGirl.mapOwner, NAME_GEN));
			AddQuestUserData("JungleGirl", "sTreasureLoc", XI_ConvertString(pchar.GenQuest.EncGirl.islandId));
			AddQuestUserData("JungleGirl", "sShore", XI_ConvertString(pchar.GenQuest.EncGirl.shoreId + "Gen"));
			AddQuestUserData("JungleGirl", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.EncGirl.city));
			pchar.quest.EncGirl_Death.win_condition.l1 = "NPC_Death";
			pchar.quest.EncGirl_Death.win_condition.l1.character = npchar.id;
			pchar.quest.EncGirl_Death.function = "EncGirl_Death";
			pchar.quest.EncGirl_FindChest.win_condition.l1 = "location";
			pchar.quest.EncGirl_FindChest.win_condition.l1.location = pchar.GenQuest.EncGirl.placeId;
			pchar.quest.EncGirl_FindChest.function = "EncGirl_FindChest";
			SetFunctionExitFromLocationCondition("EncGirl_AddPassenger", pchar.location, false);
			SetFunctionLocationCondition("EncGirl_DialogAtShore", pchar.GenQuest.EncGirl.shoreId, false);
			Diag.TempNode = "Node_12End";
			pchar.GenQuest.EncGirl = "GetChest";
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
			AddDialogExitQuest("pchar_back_to_player");			
		break;
		
		case "Node_132_11_1":
			dialog.text = "Капитан, теперь мы должны найти пещеру.";
			link.l1 = "Ну что ж, давай поищем.";
			link.l1.go = "exit";
			Diag.TempNode = "Node_132_11_2";
			Diag.CurrentNode = Diag.TempNode;
			AddDialogExitQuestFunction("EncGirl_GirlFollow");
		break;
		
		case "Node_132_11_2":
			Diag.TempNode = "Node_132_11_2";
			dialog.text = "Капитан, мы должны найти пещеру.";
			link.l1 = "Ну что ж, давай поищем.";
			link.l1.go = "exit";
		break;
		
		case "Node_132_12":
			dialog.text = "Вот. Я его нашла!.. Как говорил отец - здесь целая куча драгоценностей! Ваша половина - как и договаривались.";
			link.l1 = "Вот видишь, как всё просто оказалось? А ты боялась.";
			link.l1.go = "Node_132_13";
		break;
		
		case "Node_132_13":
			dialog.text = "Ха-ха-ха!.. Теперь я богата! Свою долю возьмёте сейчас?";
			link.l1 = "Пожалуй.";
			link.l1.go = "Node_132_15";
		break;
		
		case "Node_132_15":
			dialog.text = "Тогда держите и помогите мне отнести сокровища на корабль. Вы не забыли, что обещали отвезти меня домой?";
			link.l1 = "Не забыл"+ GetSexPhrase("","а") +". Отвезу обязательно.";
			link.l1.go = "Node_132_16";
		break;
		
		case "Node_132_16":
			pchar.quest.EncGirl_DeathSimple.over = "yes";
			LAi_LocationDisableMonstersGen(pchar.location, false);
			chrDisableReloadToLocation = false;
			Log_Info("Вы получили свою долю клада");
			PlaySound("interface\important_item.wav");
			TakeNItems(pchar, "icollection", 1+drand(1));
			TakeNItems(pchar, "chest", 2+drand(6));
			TakeNItems(pchar, "jewelry1", 30+drand(15));
			TakeNItems(pchar, "jewelry2", 30+drand(15));
			TakeNItems(pchar, "jewelry3", 30+drand(15));
			TakeNItems(pchar, "jewelry4", 30+drand(15));
			TakeNItems(pchar, "jewelry5", 30+rand(10));
			TakeNItems(pchar, "jewelry6", 10+rand(10));
			TakeNItems(pchar, "jewelry42", 20+rand(10));
			TakeNItems(pchar, "jewelry44", 30+rand(10));
			TakeNItems(pchar, "jewelry46", 50+rand(20));
			AddQuestRecord("JungleGirl", "6");
			AddQuestUserData("JungleGirl", "sSex", GetSexPhrase("","а"));
			AddQuestUserData("JungleGirl", "sPirateName", GetName( NAMETYPE_ORIG, pchar.GenQuest.EncGirl.mapOwner, NAME_GEN));
			AddQuestUserData("JungleGirl", "sName", pchar.GenQuest.EncGirl.name);
			AddQuestUserData("JungleGirl", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.EncGirl.city));		
			pchar.GenQuest.EncGirl = "ChestGetted";
			pchar.quest.EncGirl_DeliveBack.win_condition.l1 = "location";
			pchar.quest.EncGirl_DeliveBack.win_condition.l1.location = pchar.GenQuest.EncGirl.city + "_town";
			pchar.quest.EncGirl_DeliveBack.function = "EncGirl_DeliveBack";
			pchar.quest.EncGirl_DeathAgain.win_condition.l1 = "NPC_Death";
			pchar.quest.EncGirl_DeathAgain.win_condition.l1.character = npchar.id;
			pchar.quest.EncGirl_DeathAgain.function = "EncGirl_DeathAgain";
			Diag.TempNode = "Node_132_17";
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
			AddDialogExitQuestFunction("EncGirl_GirlFollow");
		break;
		
		case "Node_132_17":
			Diag.TempNode = "Node_132_17";
			dialog.text = "Как здорово быть богатой! Я себя чувствую другим человеком."; 
			link.l1 = "Я рад"+ GetSexPhrase("","а") +" за тебя.";
			link.l1.go = "exit";
		break;
		
		case "Node_132_18":
			dialog.text = "Ну всё, капитан. Моё путешествие закончено. Спасибо вам за помощь.";
			link.l1 = "Пожалуйста... Что думаешь делать со своим богатством? Небось плантацию купишь, рабов заведёшь...";
			link.l1.go = "Node_132_19";
		break;
		
		case "Node_132_19":
			dialog.text = "Не знаю, не решила ещё... Может, в Европу уеду...";
			link.l1 = "Ну, счастливо оставаться.";
			link.l1.go = "Node_132_20";
		break;
		
		case "Node_132_20":
			dialog.text = "Постойте... В кладе отца была вот эта вещица. Мне она ни к чему, а вам может пригодиться. Возьмите её, как подарок за то, что вы для меня сделали... Это из моей доли, ха-ха-ха...";
			link.l1 = "Ух-ты, какой подарок. Спасибо"+ GetSexPhrase(", красавица","") +". Жениха тебе хорошего...";
			link.l1.go = "Node_132_21";
		break;
		
		case "Node_132_21":
			chrDisableReloadToLocation = false;		
			RemovePassenger(pchar, npchar);			
			GiveItem2Character(pchar, pchar.GenQuest.EncGirl.item); 
			AddQuestRecord("JungleGirl", "8");
			AddQuestUserData("JungleGirl", "sSex", GetSexPhrase("","а"));
			AddQuestUserData("JungleGirl", "sName", pchar.GenQuest.EncGirl.name);
			CloseQuestHeader("JungleGirl");
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeDay = 0;
			DeleteAttribute(pchar, "GenQuest.EncGirl");
			DialogExit();
			AddDialogExitQuest("pchar_back_to_player");			
		break;
		
		case "Node_133":
			dialog.text = "Но что же мне делать? Я же не могу ослушаться хозяйки! Она с меня три шкуры спустит.";
			link.l1 = "Жди меня в церкви поселения " + XI_ConvertString("Colony" + pchar.GenQuest.EncGirl.city) + ", привезу я тебе жемчуга для ожерелья.";
			link.l1.go = "Node_133_1";
			if(sti(pchar.money) >= 15000)
			{
				link.l2 = "Вот, держи 15000 песо, за эти деньги можно, если не целое ожерелье купить, то жемчужины к нему подобрать - уж наверняка.";
				link.l2.go = "Node_135";
			}							
		break;
		
		case "Node_133_1":
			pchar.GenQuest.EncGirl = "GetCoins";
			pchar.quest.EncGirl_Coins.win_condition.l1 = "ExitFromLocation";
			pchar.quest.EncGirl_Coins.win_condition.l1.location = pchar.location;
			pchar.quest.EncGirl_Coins.function = "EncGirl_toChurch";
			pchar.quest.EncGirl_GetCoins.win_condition.l1 = "Timer";
			pchar.quest.EncGirl_GetCoins.win_condition.l1.date.day = GetAddingDataDay(0, 0, 10);
			pchar.quest.EncGirl_GetCoins.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 10);
			pchar.quest.EncGirl_GetCoins.win_condition.l1.date.year = GetAddingDataYear(0, 0, 10);
			pchar.quest.EncGirl_GetCoins.function = "EncGirl_GenQuest_GetCoins";	
            sTemp = LAi_FindNearestFreeLocator2Pchar("reload");// лесник - девица убегает если ГГ сказал ждать в цервки
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", sTemp, "none", "", "","OpenTheDoors", -1.0);			
			Diag.TempNode = "Node_134"; 
			Diag.CurrentNode = Diag.TempNode;
			ReOpenQuestHeader("JungleGirl");
			AddQuestRecord("JungleGirl", "1"); 
			AddQuestUserData("JungleGirl", "sSex", GetSexPhrase("","а")); 
			AddQuestUserData("JungleGirl", "sName", pchar.GenQuest.EncGirl.name); 
			AddQuestUserData("JungleGirl", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.EncGirl.city));
			AddQuestUserData("JungleGirl", "sText1", sti(pchar.GenQuest.EncGirl.BigCoins)); 
			AddQuestUserData("JungleGirl", "sText2", sti(pchar.GenQuest.EncGirl.SmallCoins)); 		
			DialogExit();
			AddDialogExitQuest("pchar_back_to_player");			
		break;
		
		case "Node_134":
			dialog.text = RandPhraseSimple(""+ GetSexPhrase("капитан","девушка") +", как я рада вас снова видеть! Вам удалось собрать жемчуг для ожерелья?","Здравствуйте, капитан! Ну что, привезли жемчужины? А то хозяйка очень нервничает.");
			if (GetCharacterItem(pchar, "jewelry52") >= sti(pchar.GenQuest.EncGirl.BigCoins) && GetCharacterItem(pchar, "jewelry53") >= sti(pchar.GenQuest.EncGirl.SmallCoins))
			{
				link.l1 = "Да. Держи свои жемчужины. Отдай их хозяйке и передай, пусть в следующий раз место выбирает прежде, чем ожерелье рассыпать.";
				link.l1.go = "Node_134_1";
			}
			else
			{
				link.l1 = "Нет ещё. Это оказалось не так просто... Жди, я обязательно привезу.";
				link.l1.go = "Node_134_2";
			}	
		break;
		
		case "Node_134_1":
			TakeNItems(pchar, "jewelry52", -sti(pchar.GenQuest.EncGirl.BigCoins)); 
			TakeNItems(pchar, "jewelry53", -sti(pchar.GenQuest.EncGirl.SmallCoins)); 
			pchar.quest.EncGirl_GetCoins.over = "yes";
			pchar.quest.EncGirl_DeathSimple.over = "yes";
			dialog.text = "Ах, "+ GetSexPhrase("капитан","девушка") +", как я счастлива, что встретила вас! В знак благодарности за всё, что вы для меня сделали, хочу подарить одну вещицу и эти камешки. Надеюсь, вам все это очень пригодится. ";
			link.l1 = "Ого! Спасибо и тебе"+ GetSexPhrase(", красавица","") +", никак не ожидал"+ GetSexPhrase("","а") +"... Прощай, и будь счастлива.";
			link.l1.go = "Node_134_End";
		break;
		
		case "Node_134_2":
			dialog.text = "Ах, "+ GetSexPhrase("капитан","девушка") +", я на вас очень надеюсь.";
			link.l1 = "И правильно делаешь...";
			link.l1.go = "exit";
			LAi_SetStayType(NPChar);
		break;
		
		case "Node_134_End":
			GiveItem2Character(pchar, pchar.GenQuest.EncGirl.item); 
			TakeNItems(pchar, "jewelry1", 15+drand(8));
			AddQuestRecord("JungleGirl", "2");
			AddQuestUserData("JungleGirl", "sSex", GetSexPhrase("","а"));
			AddQuestUserData("JungleGirl", "sName", pchar.GenQuest.EncGirl.name); 
			CloseQuestHeader("JungleGirl");
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeDay = 0;
			DeleteAttribute(pchar, "GenQuest.EncGirl");
			DialogExit();
		break;
		
		case "Node_135":
			addMoneyToCharacter(pchar, -15000);
			ChangeCharacterComplexReputation(pchar,"nobility", 10);
			dialog.text = "Ах, "+ GetSexPhrase("капитан","девушка") +", вы сегодня уже второй раз меня выручаете. Спасибо вам огромное. Я никогда не забуду вашей доброты.";
			link.l1 = "Пожалуйста. Передавай привет хозяйке...";
			link.l1.go = "Node_135End";
		break;
		
		case "Node_135End":
			pchar.quest.LandEnc_RapersBadExit.over = "yes";
			NPChar.lifeDay = 0;
			sTemp = LAi_FindNearestFreeLocator2Pchar("reload");
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", sTemp, "none", "", "","OpenTheDoors", -1.0);
			DeleteAttribute(pchar, "GenQuest.EncGirl");
			DialogExit();		
			AddDialogExitQuest("pchar_back_to_player");			
		break;	
		
		case "ThanksForSave":
			if (npchar.city == "Bridgetown" || npchar.city == "Charles" || npchar.city == "FortFrance" || npchar.city == "Marigo" || npchar.city == "Panama" || npchar.city == "PortRoyal" || npchar.city == "SantoDomingo" || npchar.city == "Tortuga") 
			{
				if(CheckAttribute(pchar, "GenQuest.EncGirl.Horse")) 
				{
					iRnd = 2;
					pchar.GenQuest.EncGirl.BrothelCity = true;
				}	
				else
				{	
					iRnd = 1;
				}	
			}
			else
			{
				iRnd = 1;
			}
			switch(rand(iRnd))
			{
				case 0:
					dialog.text = RandPhraseSimple("Напрасно вы им деньги отдали. Врут они.","Не верьте им. Врут они всё... Ещё и деньги отдали.");
					link.l1 = "Надо было их убить?";
					link.l1.go = "Node_200";
				break;
				case 1:
					dialog.text = "Ах, какой благородный поступок! Сразу видно "+ GetSexPhrase("настоящего джентльмена","благородную леди") +"! Примите мою искреннюю благодарность... Я надеюсь, вы не поверили тому, что болтали эти проходимцы?";
					link.l1 = "Это не имеет значения. Девушка с толпой голодранцев в джунглях - это вполне естественно... ";
					link.l1.go = "Node_210";
					link.l2 = "Ну что ты, "+ GetSexPhrase("красавица","милочка") +"? Как можно?";
					link.l2.go = "Node_211";
				break;
				case 2:
					dialog.text = "Спасибо вам, капитан. Извините, что впутала в такую неприятную историю, но у меня не было другого выхода.";
					link.l1 = "Да, я вижу, ты и сама здорово влипла. Как это тебя угораздило?";
					link.l1.go = "Node_220";		
				break;
			}
		break;
		
		case "Node_200":
			if(rand(1) == 0)
			{
				dialog.text = "Может и так... Они меня всё равно в покое не оставят.";
				link.l1 = "Скажешь тоже. Иди домой, тебе больше нечего бояться.";
				link.l1.go = "Node_200End";
				link.l2 = "Ого! Откуда такая неприязнь к мужчинам?";
				link.l2.go = "Node_201";
			}
			else
			{
				dialog.text = "Нет, конечно! Только они всё равно не отстанут. Проводите меня до поселения " + XI_ConvertString("Colony" + pchar.GenQuest.EncGirl.city) + ", пожалуйста.";
				link.l1 = "Иди домой, они тебя уже не тронут. Они сейчас в таверну пойдут, дармовые денежки тратить.";
				link.l1.go = "Node_200End";
				link.l2 = RandPhraseSimple("Да не волнуйся ты так... Ну ладно, пошли.","Что ж ты трусиха такая? Пошли, провожу.");
				link.l2.go = "Node_121Next";
			}
		break;
		
		case "Node_201":
			dialog.text = "Да нет, что вы? Просто этих негодяев я хорошо знаю. Это бывшие дружки моего отца. Они выслеживают место, где отец драгоценности прятал.";
			link.l1 = "А что с отцом?";
			link.l1.go = "Node_202";
		break;
		
		case "Node_202":
			dialog.text = "Он был капитаном пиратского корабля. Умер недавно... На похоронах они все такие вежливые были, а как время прошло - и про отца забыли и про совесть... Хорошо, что я их заметила. Как только они узнают где клад, мне больше не жить...";
			link.l1 = "Да, невесёлая история. И что же ты, так и будешь от них прятаться?";
			link.l1.go = "Node_203";
		break;
		
		case "Node_203":
			dialog.text = "Я не могу держать ценности дома, меня некому защищать. Вот так и хожу по ночам в пещеру, когда деньги заканчиваются...\nПроводите меня, пожалуйста, до пещеры, а я верну вам деньги, которые вы им отдали... Думаю, пираты не рискнут идти за нами пока вы со мной.";
			link.l1 = "Извини, дорогуша, у меня совсем другие планы. В следующий раз заберёшь свои сокровища.";
			link.l1.go = "Node_200End";
			link.l2 = "Ну пошли, если ты меня не боишься.";
			link.l2.go = "Node_204";
		break;
		
		case "Node_204":
			dialog.text = "Вас почему-то не боюсь...";
			link.l1 = "Ну и правильно делаешь.";
			link.l1.go = "Node_205";
		break;
		
		case "Node_205":
			Diag.TempNode = "Node_206";
			EncGirl_GenerateChest(npchar);
			Diag.CurrentNode = Diag.TempNode;
			AddDialogExitQuestFunction("EncGirl_GirlFollow");
			DialogExit();
		break;
		
		case "Node_206":
			Diag.TempNode = "Node_206";
			dialog.text = "Капитан, вы обещали проводить меня до пещеры.";
			link.l1 = "Пошли...";
			link.l1.go = "exit";
		break;
		
		case "Node_207":
			dialog.text = "Всё, капитан, я взяла сколько нужно. Можем возвращаться.";
			link.l1 = "Вроде не видно твоих приятелей.";
			link.l1.go = "Node_208";
		break;
		
		case "Node_208":
			dialog.text = "Ну и слава Богу. Меньше неприятностей будет... Вот, возьмите эти слитки, это должно покрыть ваши расходы. Ступайте од"+ GetSexPhrase("ин","на") +", я пойду другой дорогой...";
			link.l1 = "Ну счастливо, коль не боишься.";
			link.l1.go = "Node_209";
		break;
		
		case "Node_209":
			LAi_LocationDisableMonstersGen(pchar.location, false);
			i = makeint(sti(pchar.GenQuest.EncGirl.price)/100.0);
			TakeNItems(pchar, "jewelry6", i);
			sTemp = LAi_FindNearestFreeLocator2Pchar("reload");
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", sTemp, "none", "", "","OpenTheDoors", -1.0);
			npchar.lifeDay = 0;
			pchar.quest.EncGirl_RapersExit.win_condition.l1 = "ExitFromLocation";
			pchar.quest.EncGirl_RapersExit.win_condition.l1.location = pchar.location;
			pchar.quest.EncGirl_RapersExit.function = "EncGirl_MeetRapers";
			DialogExit();
		break;
		
		case "Node_200End":
			pchar.quest.LandEnc_RapersBadExit.over = "yes";
			AddDialogExitQuestFunction("EncGirl_GirlGoAway");
			DialogExit();
		break;
		
		case "Node_210":
			dialog.text = "Хм, "+ GetSexPhrase("капитан","девушка") +", мне не нравится ваша ирония.";
			link.l1 = "Свободна, "+ GetSexPhrase("красотка","милочка") +". Лучше поспеши в город, пока они снова за тобой не увязались.";
			link.l1.go = "Node_1End";
		break;
		
		case "Node_211":
			dialog.text = "Я так разволновалась! Не проводите меня в таверну поселения " + XI_ConvertString("Colony" + pchar.GenQuest.EncGirl.city) + "? Не то, боюсь, они опять за мной увяжутся.";
			link.l1 = "Пожалуй, ты права. Пошли...";
			link.l1.go = "Node_122Next";
			ChangeCharacterComplexReputation(pchar,"nobility", 1);
		break;
		
		case "Node_220":
			dialog.text = "Ох, капитан - это длинная история, не думаю, что она будет вам интересна. Хотя... мне всё равно теперь без вашей помощи не обойтись. Не согласитесь ли проводить до таверны поселения " + XI_ConvertString("Colony" + pchar.GenQuest.EncGirl.city) + "? А то, боюсь, они не отвяжутся.";
			link.l1 = "Извини, милая, некогда мне, дела ждут.";
			link.l1.go = "Node_221";
			link.l2 = "Чего ж ты такая скрытная?";
			link.l2.go = "Node_222";
		break;
		
		case "Node_221":
			ChangeCharacterComplexReputation(pchar,"nobility", -2);
			AddDialogExitQuestFunction("EncGirl_GirlGoAway");
			DialogExit();
		break;
		
		case "Node_222":
			dialog.text = "Как же тут не быть скрытной, если каждый норовит на твоём несчастье нажиться?";
			link.l1 = "Ну пошли...";
			link.l1.go = "Node_223";
		break;
		
		case "Node_223":
			Diag.TempNode = "Node_224";
			pchar.GenQuest.EncGirl = "HorseToTavern";
			pchar.quest.EncGirl_DeliveBack.win_condition.l1 = "location";
			pchar.quest.EncGirl_DeliveBack.win_condition.l1.location = pchar.GenQuest.EncGirl.city + "_tavern";
			pchar.quest.EncGirl_DeliveBack.function = "EncGirl_DeliveBack";		
			Diag.CurrentNode = Diag.TempNode;
			AddDialogExitQuestFunction("EncGirl_GirlFollow");
			DialogExit();		
		break;
		
		case "Node_224":
			dialog.text = "Капитан, вы обещали проводить меня в таверну поселения " + XI_ConvertString("Colony" + pchar.GenQuest.EncGirl.city) + ".";
			link.l1 = RandPhraseSimple("Помню я, помню.","Не волнуйся - провожу.");
			link.l1.go = "exit";
		break;
		
		case "Node_225":
			chrDisableReloadToLocation = false;
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") || CheckAttribute(pchar, "questTemp.LSC.Mary_officer"))
			{
				if (CheckAttribute(pchar, "GenQuest.EncGirl.BrothelCity") && sti(pchar.rank) > 15)
				{
					dialog.text = "Здесь слишком людно. Давайте пройдём в комнату, мне нужно вам кое-что рассказать.";
					link.l1 = LinkRandPhrase("Я и так для тебя много сделал, так что прощай.","Не стоит злоупотреблять моим расположением. До свидания, дорогуша.","Мне твои россказни малоинтересны. Дальше разберёшься сама.");
					link.l1.go = "Node_226";
					link.l2 = "Хм, ну хорошо. Сейчас возьму ключи у бармена.";
					link.l2.go = "Node_227";
				}
				else
				{
					dialog.text = "Большое спасибо за вашу помощь. Я никогда не забуду вашей доброты.";
					link.l1 = "Да ладно тебе. Лучше будь осторожнее впредь.";
					link.l1.go = "Node_226_1";
				}
			}
			else
			{
				if (CheckAttribute(pchar, "questTemp.FMQP") && pchar.questTemp.FMQP == "begin") // Addon-2016 Jason, французские миниквесты (ФМК)
				{
					dialog.text = "Большое спасибо за вашу помощь. Я никогда не забуду вашей доброты.";
					link.l1 = "Да ладно тебе. Лучше будь осторожнее впредь.";
					link.l1.go = "Node_226_1";
				}
				else
				{
					dialog.text = "Здесь слишком людно. Давайте пройдём в комнату, мне нужно вам кое-что рассказать.";
					link.l1 = LinkRandPhrase("Я и так для тебя много сделал, так что прощай.","Не стоит злоупотреблять моим расположением. До свидания, дорогуша.","Мне твои россказни малоинтересны. Дальше разберёшься сама.");
					link.l1.go = "Node_226";
					link.l2 = "Хм, ну хорошо. Сейчас возьму ключи у бармена.";
					link.l2.go = "Node_227";
				}
			}
		break;
		
		case "Node_226":
			ChangeCharacterComplexReputation(pchar,"nobility", -1);
			sTemp = LAi_FindNearestFreeLocator2Pchar("reload");
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", sTemp, "none", "", "","OpenTheDoors", -1.0);
			npchar.lifeDay = 0;
			DeleteAttribute(pchar, "GenQuest.EncGirl");
			DialogExit();		
			AddDialogExitQuest("pchar_back_to_player");			
		break;
		
		case "Node_226_1":
			ChangeCharacterComplexReputation(pchar,"nobility", 3);
			sTemp = LAi_FindNearestFreeLocator2Pchar("reload");
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", sTemp, "none", "", "","OpenTheDoors", -1.0);
			npchar.lifeDay = 0;
			DeleteAttribute(pchar, "GenQuest.EncGirl");
			DialogExit();		
			AddDialogExitQuest("pchar_back_to_player");			
		break;
		
		case "Node_227":
			pchar.GenQuest.EncGirl = "EncGirl_ToTavern";
			pchar.quest.EncGirl_inRoom.win_condition.l1 = "location";
			pchar.quest.EncGirl_inRoom.win_condition.l1.location = npchar.city + "_tavern_upstairs";
			pchar.quest.EncGirl_inRoom.function = "EncGirl_SpeakInRoom";
			DialogExit();
			AddDialogExitQuest("pchar_back_to_player");			
		break;
		
		case "Node_228":
			if(CheckAttribute(pchar, "GenQuest.EncGirl.Horse") && CheckAttribute(pchar,"GenQuest.EncGirl.BrothelCity") && sti(pchar.rank) > 15) // душещипательная история о невинной девочке попавшей в бордель
			{
				DeleteAttribute(pchar, "GenQuest.EncGirl.BrothelCity");
				dialog.text = "Вы ещё хотите услышать мою историю?";
				link.l1 = "Нет, пожалуй, мне уже пора. Счастливо оставаться.";
				link.l1.go = "Node_232";
				link.l2 = "Рассказывай, раз начала.";
				link.l2.go = "Node_233";	
			}
			else						
			{
				dialog.text = "Ах, мой благородный спаситель, наконец-то я могу вас отблагодарить так, как это умеют делать только женщины\n Когда я увидела вас в джунглях, во мне всё так и перевернулось. Я забыла и о насильниках, и об острых пальмовых листьях, что хлестали меня по щекам. Забыла куда бегу, зачем бегу... Я видела только вас. И хотела только вас... А после того, что вы для меня сделали...";
				link.l1 = "Ого! Вот это темперамент! Твои преследователи знали, за кем нужно бежать...";
				link.l1.go = "Node_229"; // ГГ допрыгался - щас его попросту трахнут
				link.l2 = "Послушай, красотка, мне понятен твой энтузиазм, но оставь свой темперамент при себе.";
				link.l2.go = "Node_230"; // Послал в пешее эротическое путешествие
			}
		break;
		
		case "Node_229":
			dialog.text = "Ну, иди же ко мне, мой герой...";
			link.l1 = "Ах, красавица...";
			link.l1.go = "exit";
			pchar.GenQuest.EncGirl = "EncGirl_facking";
			DoQuestCheckDelay("PlaySex_1", 3.0);
		break;
		
		case "Node_230":
			dialog.text = "Ах! Да как вы!.. Да как ты смеешь?! Мужлан! Девушка к нему со всей душой и телом, а он!..";
			link.l1 = "Если б ты поменьше хвостом крутила, да на шею первому встречному вешалась, у тебя и проблем бы поменьше было. А то задерут юбку, а потом спасай их по джунглям...";
			link.l1.go = "Node_231";
		break;
		
		case "Node_231":
			dialog.text = "Ну такого я ещё ни от кого не слышала! И никому прощать не намерена! Попомнишь ещё мои слова!";
			link.l1 = "Топай-топай. И чулки подбери, а то опять спасать придётся...";
			link.l1.go = "Node_231_1";
		break;
		
		case "Node_231_1":
			ChangeCharacterComplexReputation(pchar,"nobility", 1);
			sTemp = LAi_FindNearestFreeLocator2Pchar("reload");
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", sTemp, "none", "", "","", -1.0);
			npchar.lifeDay = 0;
			DoQuestFunctionDelay("EncGirl_SetBerglar", 5.0);
			DialogExit();		
		break;
		
		case "Node_232":
			ChangeCharacterComplexReputation(pchar,"nobility", -3);
			sTemp = LAi_FindNearestFreeLocator2Pchar("reload");
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", sTemp, "none", "", "","OpenTheDoors", -1.0);
			npchar.lifeDay = 0;
			DeleteAttribute(pchar, "GenQuest.EncGirl");
			DialogExit();
		break;
		
		case "Node_233":
			pchar.GenQuest.EncGirl.Parents_City = GetQuestNationsCity(sti(pchar.GenQuest.EncGirl.nation));
			dialog.text = "Моя семья живёт в поселении " + XI_ConvertString("Colony" + pchar.GenQuest.EncGirl.Parents_City) + ". Сюда я попала совершенно случайно - судно, на котором жених вёз меня, к своим родителям, захватили пираты. Корабль забрали, а пассажиров высадили в бухте недалеко отсюда. Мой жених погиб во время абордажа, а я тяжело заболела во время перехода по джунглям\nВыходила меня хозяйка местного борделя, а когда я встала на ноги, она потребовала отработать средства потраченные на лечение. Но шлюхи из меня не получилось, и мадам-хозяйка, чтобы хоть что-то заработать, продала меня каким-то бандитам. Остальное вы знаете.";
			link.l1 = "Так бросай всё это и езжай домой! Чего ты позволяешь обращаться с собой, как с рабыней?!";
			link.l1.go = "Node_234";
		break;
		
		case "Node_234":
			dialog.text = "Не могу я! Все мои вещи - приличная одежда, деньги, документы - остались в борделе в походном саквояже. Я его спрятала в комнате свиданий. А в таком наряде мне матросы в порту проходу не дадут, не говоря уже о путешествии. Да и кто меня на борт возьмёт без денег и документов? А теперь и в городе появиться не могу - меня в тюрьму посадят...";
			link.l1 = "Вот проблему придумала! Собирайся, поехали. Я тебя отвезу.";
			link.l1.go = "Node_235";
			link.l2 = "Жди здесь. Я принесу твой саквояж.";
			link.l2.go = "Node_236";													
			if(sti(pchar.money) >= 5000) 
			{
				link.l3 = "Да кому интересны твои документы? Сколько тебе нужно денег, чтоб добраться домой?";
				link.l3.go = "Node_237";							
			}			
		break;
		
		case "Node_235":
			dialog.text = "Вот спасибо вам, капитан... Но мне ведь нечем с вами расплатиться.";
			link.l1 = "Какая расплата?! Пошли, пока тебя не хватились.";
			link.l1.go = "Node_240";				
		break;
		
		case "Node_240":
			ReOpenQuestHeader("JungleGirl");
			AddQuestRecord("JungleGirl", "20");
			AddQuestUserData("JungleGirl", "sSex", GetSexPhrase("ся","ась"));
			AddQuestUserData("JungleGirl", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.EncGirl.Parents_City));
			AddQuestUserData("JungleGirl", "sBrothelCity", XI_ConvertString("Colony" + pchar.GenQuest.EncGirl.city + "Gen"));
			AddQuestUserData("JungleGirl", "sName", pchar.GenQuest.EncGirl.name);
		
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, false);
			OfficersReaction("bad");
			chrDisableReloadToLocation = false;
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "OpenTheDoors", 3.0);
			pchar.quest.EncGirl_DeliveToParents.win_condition.l1 = "location";
			pchar.quest.EncGirl_DeliveToParents.win_condition.l1.location = pchar.GenQuest.EncGirl.Parents_City + "_town";
			pchar.quest.EncGirl_DeliveToParents.function = "EncGirl_DeliveToParents";
			DialogExit(); 		
		break;
		
		case "Node_236":
			dialog.text = "Ах, капитан, а я не смела даже просить об этом.";
			link.l1 = "Не бойся. Я скоро приду.";
			link.l1.go = "Node_239";				
		break;		
		
		case "Node_239":
			ReOpenQuestHeader("JungleGirl");
			AddQuestRecord("JungleGirl", "21");
			AddQuestUserData("JungleGirl", "sSex", GetSexPhrase("ся","ась"));
			AddQuestUserData("JungleGirl", "sName", pchar.GenQuest.EncGirl.name);

			pchar.quest.EncGirl_GenerateBag.win_condition.l1 = "location";
			if(GetSummonSkillFromName(pchar, SKILL_FORTUNE) > rand(100))
			{
				pchar.GenQuest.EncGirl = "Bag_BrothelRoomUp";
				pchar.quest.EncGirl_GenerateBag.win_condition.l1.location = pchar.GenQuest.EncGirl.city + "_Brothel_room";
			}
			else
			{
				pchar.GenQuest.EncGirl = "Bag_BrothelRoom";
				pchar.quest.EncGirl_GenerateBag.win_condition.l1.location = pchar.GenQuest.EncGirl.city + "_SecBrRoom";
			}
			pchar.quest.EncGirl_GenerateBag.function = "EncGirl_GenerateLeatherBag";

			pchar.quest.EncGirl_GetBagFail.win_condition.l1 = "Timer";
			pchar.quest.EncGirl_GetBagFail.win_condition.l1.date.day = GetAddingDataDay(0, 0, 1);
			pchar.quest.EncGirl_GetBagFail.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.EncGirl_GetBagFail.win_condition.l1.date.year = GetAddingDataYear(0, 0, 1);
			pchar.quest.EncGirl_GetBagFail.function = "EncGirl_GenQuest_GetBag";
						
			pchar.quest.EncGirl_ExitRoom.win_condition.l1 = "ExitFromLocation";
			pchar.quest.EncGirl_ExitRoom.win_condition.l1.location = pchar.location;
			pchar.quest.EncGirl_ExitRoom.function = "EncGirl_ExitTavernRoom";

			AddDialogExitQuest("OpenTheDoors");
			DialogExit();
		break;
		
		case "Node_240_1":
			pchar.quest.EncGirl_GetBagFail.over = "yes";
			dialog.text = "Ах, я уж думала, с вами что-то случилось.";
			if(CheckCharacterItem(pchar, "leather_bag"))
			{
				link.l1 = "Что со мной может случиться? Вот, держи свои вещи.";
				link.l1.go = "Node_241";
			}	
			else
			{
				link.l1 = "Слушай, я ничего там не наш"+ GetSexPhrase("ел","ла") +". Ты уверена, что оставляла саквояж в комнате свиданий?";
				link.l1.go = "Node_242";			
			}	
		break;
		
		case "Node_241":
			TakeNItems(pchar, "leather_bag", -1);
			dialog.text = "Спасибо вам, "+ GetSexPhrase("благородный капитан","благородная девушка") +". Я никогда не забуду того, что вы для меня сделали. И хоть у меня ничего нет, разрешите подарить вам этот амулет, может быть только благодаря ему я осталась жива после атаки пиратов.";
			link.l1 = "Спасибо тебе. Удачно добраться. Прощай.";
			link.l1.go = "Node_243";
		break;
		
		case "Node_242":
			dialog.text = "Неужели мой тайник нашли?..";
			if(sti(pchar.money) >= 5000)
			{
				link.l1 = "Сколько тебе нужно денег, чтоб добраться домой?";
				link.l1.go = "Node_237";
			}
			link.l2 = "Возможно нашли. Только теперь наши пути расходятся. Прощай!";
			link.l2.go = "Node_244";
		break;
		
		case "Node_243":
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "OpenTheDoors", -1.0);
			npchar.lifeDay = 0;
			TakeNItems(pchar, pchar.GenQuest.EncGirl.item, 1);
			AddQuestRecord("JungleGirl", "23");
			AddQuestUserData("JungleGirl", "sSex", GetSexPhrase("","ла"));
			AddQuestUserData("JungleGirl", "sSex1", GetSexPhrase("","а"));
			AddQuestUserData("JungleGirl", "sName", pchar.GenQuest.EncGirl.name);
			CloseQuestHeader("JungleGirl");
			ChangeCharacterComplexReputation(pchar,"nobility", 1);
			DeleteAttribute(pchar, "GenQuest.EncGirl");
			DialogExit();
		break;
		
		case "Node_244":
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "OpenTheDoors", -1.0);
			npchar.lifeDay = 0;
			AddQuestRecord("JungleGirl", "23");
			AddQuestUserData("JungleGirl", "sName", pchar.GenQuest.EncGirl.name);
			CloseQuestHeader("JungleGirl");
			ChangeCharacterComplexReputation(pchar,"nobility", -5);
			DeleteAttribute(pchar, "GenQuest.EncGirl");
			DialogExit();
		break;
		
		case "Node_245":
			dialog.text = "Спасибо вам, капитан. Даже не верится, что я дома. Прошу вас, не откажите, пойдёмте, я вас познакомлю с родителями.";
			link.l1 = "Слушай, "+ GetSexPhrase("красавица","милочка") +", мне действительно некогда. Давай как-нибудь в следующий раз.";
			link.l1.go = "Node_246";
		break;
		
		case "Node_246":
			dialog.text = "Очень жаль... Ну что ж, тогда прощайте, и да хранит вас Бог. И хоть у меня ничего нет, разрешите подарить вам этот амулет.";
			link.l1 = "Спасибо! Беги-беги, обрадуй родителей...";
			link.l1.go = "Node_247";
		break;
		
		case "Node_247":
			sTemp = LAi_FindNearestFreeLocator2Pchar("reload");
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", sTemp, "none", "", "","OpenTheDoors", -1.0);		
			TakeNItems(pchar, pchar.GenQuest.EncGirl.item, 1);
			AddQuestRecord("JungleGirl", "24");
			AddQuestUserData("JungleGirl", "sSex", GetSexPhrase("","а"));
			AddQuestUserData("JungleGirl","sName", pchar.GenQuest.EncGirl.name);
			AddQuestUserData("JungleGirl","sCity", XI_ConvertString("Colony" + pchar.GenQuest.EncGirl.Parents_City));
			CloseQuestHeader("JungleGirl");
			npchar.lifeDay = 0;
			DeleteAttribute(pchar, "GenQuest.EncGirl");
			DialogExit();			
		break;
		
		case "Node_248":
		break;
		
		case "Node_237":
			dialog.text = "Ну, я не знаю... Может быть, какое-то время придётся ждать попутного рейса. Но я не могу просить у вас денег.";
			if(makeint(pchar.money)>=5000)
			{
				link.l1 = "Понятно. Вот, держи 5000 песо. Этого должно хватить.";
				link.l1.go = "Node_237_1";
			}
			if(makeint(pchar.money)>=25000)
			{
				link.l2 = "Понятно. Вот, держи 25000 песо. И отправляйся домой.";
				link.l2.go = "Node_237_2";
			}
			if(makeint(pchar.money)>=35000)
			{
				link.l3 = "Понятно. Вот, держи 35000 песо. Снимешь себе каюту 'люкс'.";
				link.l3.go = "Node_237_3";
			}
		break;
		
		case "Node_237_1":
			AddMoneyToCharacter(pchar, -5000);
			ChangeCharacterComplexReputation(pchar,"nobility", -5);
			dialog.text = "Спасибо вам, "+ GetSexPhrase("благородный капитан","благородная девушка") +". Я никогда не забуду того, что вы для меня сделали.";
			link.l1 = "Удачно тебе добраться. Прощай...";
			link.l1.go = "Node_238";
			pchar.GenQuest.EncGirl = "EncGirlFack_GetMoney";
		break;
		
		case "Node_237_2":
			AddMoneyToCharacter(pchar, -25000);
			ChangeCharacterComplexReputation(pchar,"nobility", 1);
			dialog.text = "Спасибо вам, "+ GetSexPhrase("благородный капитан","благородная девушка") +". Я никогда не забуду того, что вы для меня сделали.";
			link.l1 = "Удачно тебе добраться. Прощай...";
			link.l1.go = "Node_238";
		break;
		
		case "Node_237_3":
			AddMoneyToCharacter(pchar, -35000);
			ChangeCharacterComplexReputation(pchar,"nobility", 2);
			dialog.text = "Спасибо вам, "+ GetSexPhrase("благородный капитан","благородная девушка") +". Я никогда не забуду того, что вы для меня сделали.";
			link.l1 = "Удачно тебе добраться. Прощай...";
			link.l1.go = "Node_238";
		break;
		
		case "Node_238":
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "OpenTheDoors", -1.0);
			npchar.lifeDay = 0;
			if(pchar.GenQuest.EncGirl == "EncGirlFack_GetMoney") 
			{
				AddSimpleRumour(RandPhraseSimple("Вы слышали, какая-то шлюха пыталась без документов проникнуть на корабль? Её поймали и отвели назад в бордель. Говорят, она задолжала хозяйке кругленькую сумму.",  
				"Слыхали? у нас в порту поймали какую-то шлюху без документов. Говорят, из борделя сбежала, предварительно почистив сундуки тамошней хозяйки. Давно бы следовало прикрыть этот разносчик заразы и воровства. Ведь наши дети всё это видят, чему они могут научиться?"), sti(pchar.GenQuest.EncGirl.nation), 3, 1);
			}
			DeleteAttribute(pchar, "GenQuest.EncGirl");
			DialogExit();
		break;
		
		case "Node_250":
			dialog.text = "Не губите, капитан! Отец меня замуж выдать хочет за сына ростовщика - урода слюнявого... потому что у его папаши в сундуках полно денег! Лучше я в джунглях останусь, на съедение диким зверям! Не отправляйте в пожизненную кабалу, умоляю!";
			link.l1 = "Да чего ты, "+ GetSexPhrase("красавица","милочка") +", от замужества бегаешь? Иди за того, кто сватает, пока берут. Пройдёт время - и уроду слюнявому рада будешь, ан не позовёт уже...";
			link.l1.go = "Node_251";
		break;
		
		case "Node_251":
			pchar.GenQuest.EncGirl.sLoverId = GenerateRandomName(sti(npchar.nation), "man"); 
			dialog.text = "Нет!.. нет, капитан, я люблю " + pchar.GenQuest.EncGirl.sLoverId + " и, кроме него, никого не хочу знать! А отец против! Говорит, что он в поселении " + XI_ConvertString("Colony" + pchar.GenQuest.EncGirl.city) + " приезжий, и никогда не найдёт здесь работу, вот-вот по миру пойдёт и меня за собой поведёт. А мне хоть на край света, лишь бы с ним рядом... Отведите меня к нему, прошу вас.";
			link.l1 = "Ладно, пошли. По дороге подумаю, куда тебя девать...";
			link.l1.go = "Node_252";
		break;
		
		case "Node_252":
			Diag.TempNode = "Node_253";
			ReOpenQuestHeader("JungleGirl");
			AddQuestRecord("JungleGirl", "9");
			AddQuestUserData("JungleGirl","sText", pchar.GenQuest.EncGirl.FatherGen);
			AddQuestUserData("JungleGirl","sCity", XI_ConvertString("Colony" + pchar.GenQuest.EncGirl.city));
			AddQuestUserData("JungleGirl", "sLover", pchar.GenQuest.EncGirl.sLoverId); 
			pchar.GenQuest.EncGirl.MeetSoldiers = 2;
			Diag.CurrentNode = Diag.TempNode;
			AddDialogExitQuestFunction("EncGirl_GirlFollow");
			DialogExit();
		break;
		
		case "Node_253":
			Diag.TempNode = "Node_253";
			dialog.text = "Капитан, вы обещали проводить меня в поселение " + XI_ConvertString("Colony" + pchar.GenQuest.EncGirl.city) +".";
			link.l1 = RandPhraseSimple("Помню я, помню.","Не волнуйся - провожу.");
			link.l1.go = "exit";			
		break;
		
		case "Node_260":
			chrDisableReloadToLocation = false;
			if(rand(1) == 0)
			{
				dialog.text = RandPhraseSimple("Спасибо вам, "+ GetSexPhrase("капитан","девушка") +", ещё раз. Уж и не знаю, как благодарить.","Большое вам спасибо, "+ GetSexPhrase("капитан","девушка") +". Даже не представляю, что бы я делала, не подоспей вы ко времени.");
				link.l1 = RandPhraseSimple("Впредь будет тебе наука. Ну, счастливо оставаться...","В следующий раз будешь осторожнее... Ну, иди домой, меня дела ждут.");
				link.l1.go = "Node_260End";
				link.l2 = "Разве можно быть такой беспечной? Чего тебя одну в джунгли понесло?";
				link.l2.go = "Node_13";
			}
			else
			{
				dialog.text = "Ах, "+ GetSexPhrase("капитан","девушка") +", я уж и не знаю, как вас благодарить.";
				link.l1 = "Не стоит благодарности. Всегда рад"+ GetSexPhrase("","а") +" помочь...";
				link.l1.go = "Node_261";
			}
		break;
		
		case "Node_260End":
			sTemp = LAi_FindNearestFreeLocator2Pchar("reload");
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", sTemp, "none", "", "","OpenTheDoors", -1.0);
			npchar.lifeDay = 0;
			DeleteAttribute(pchar, "GenQuest.EncGirl");			
			DialogExit();
			AddDialogExitQuest("pchar_back_to_player");			
		break;
		
		case "Node_261":
			dialog.text = "Не отведёте меня в таверну? Мне нужно дождаться свою тётку и отдохнуть, я так переволновалась...";
			link.l1 = "Нет, "+ GetSexPhrase("красавица","милочка") +", дальше без меня. У меня и так дел по горло.";
			link.l1.go = "Node_262";
			link.l2 = ""+ GetSexPhrase("Ох эти женщины! Шагу без мужчины ступить не могут!","И чего ты такая беспомощная?") +" Пошли...";
			link.l2.go = "Node_263";
		break;
		
		case "Node_262":
			sTemp = LAi_FindNearestFreeLocator2Pchar("reload");
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", sTemp, "none", "", "", "", -1.0);
			npchar.lifeday = 0;
			DeleteAttribute(pchar, "GenQuest.EncGirl");
			DialogExit();
			AddDialogExitQuest("pchar_back_to_player");			
		break;
		
		case "Node_263":
			Diag.TempNode = "Node_224";
			pchar.GenQuest.EncGirl = "HorseToTavern";
			pchar.quest.EncGirl_DeliveBack.win_condition.l1 = "location";
			pchar.quest.EncGirl_DeliveBack.win_condition.l1.location = pchar.GenQuest.EncGirl.city + "_tavern";
			pchar.quest.EncGirl_DeliveBack.function = "EncGirl_DeliveBack";					
			Diag.CurrentNode = Diag.TempNode;
			AddDialogExitQuestFunction("EncGirl_GirlFollow");
			DialogExit();
			AddDialogExitQuest("pchar_back_to_player");			
		break;
				
		case "ThanksForHelp_1":
			Diag.TempNode = "ThanksAgain";
			if(makeint(Pchar.reputation.nobility) >= 80)
			{
				dialog.text = "У меня есть немного денег. Возьмите их в знак моей благодарности!";
				Link.l1 = "Спасибо. Будьте осторожнее в следующий раз.";
				Link.l1.go = "exit";
			}
			else 
			{
				if(drand(1) == 0)
				{
					dialog.text = "Я всем расскажу, что вы меня спасли! Пусть все знают, "+ GetSexPhrase("какой вы храбрый и добрый человек","какая вы храбрая и добрая") +"!";
					Link.l1 = "Спасибо. Теперь вам лучше отправляться домой.";
					Link.l1.go = "exit";
				}
				else
				{
					addMoneyToCharacter(Pchar, makeint(PChar.rank)*100);
					dialog.text = "У меня есть немного денег. Возьмите их в знак моей благодарности!";
					Link.l1 = "Спасибо. Будьте осторожнее в следующий раз.";
					Link.l1.go = "exit";
				}
			}
		break;

		case "ThanksAgain":
            Diag.TempNode = "ThanksAgain";
            dialog.text = "Я всем расскажу, что вы меня спасли! Пусть все знают, "+ GetSexPhrase("какой вы храбрый и добрый человек","какая вы храбрая и добрая") +"!";
			Link.l1 = "Спасибо. Теперь вам лучше отправляться домой.";
			Link.l1.go = "exit";
		break;
	}
}
