// Джессика Роуз - нежить и супербосс
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i;
	string sTemp;
	float locx, locy, locz;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "Вы что-то хотели?";
			link.l1 = "Да нет, ничего.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		// бой на рифе
		case "reef":
			PlaySound("VOICE\Russian\saga\Jessica Rose-06.wav");
			dialog.text = "Ты! Ты привёл её сюда! Она - его плоть и кровь! Она - её плоть и кровь! Дочь проклятой шлюхи явилась на могилу своей матери! Она умрёт! И ты не сможешь помешать этому! Не стой на пути Джессики! Да свершится месть!";
			link.l1 = "...";
			link.l1.go = "reef_1";
		break;
		
		case "reef_1":
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			DialogExit();
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "stage_1":
			PlaySound("VOICE\Russian\saga\Jessica Rose-07.wav");
			dialog.text = "Ха-ха-ха-ха! Тебе не одолеть меня!\nВоздух, вода, земля и огонь - призываю вас себе в помощь!\nДа поднимутся мертвецы и обнажат сабли, да взовьются над твердью языки пламени, да встанет вода на страже у моста, да подхватит тебя ветер на крылья свои, и да притянет тебя земля хваткой тяжести!\nПолучай, ха-ха-ха!!!";
			link.l1 = "...";
			link.l1.go = "stage_1_exit";
		break;
		
		case "stage_1_exit":
			DialogExit();
			LAi_SetActorType(pchar);
			CreateLocationParticles("blast_inv", "quest", "top", 1.6, 0, 0, "");
			PlaySound("Sea Battles_01\Bomb_Explosion_03.wav");
			PlaySound("People Fight\Death_NPC_08.wav");
			GetCharacterPos(pchar, &locx, &locy, &locz);
			ChangeCharacterAddressGroup(pchar, "shore67", "goto", LAi_FindFarFreeLocator("goto", locx, locy, locz));
			LAi_ActorAnimation(Pchar, "Ground_sitting", "", 3.5);
			DoQuestCheckDelay("Saga_JessikaFirstKick_2", 3.5);
		break;
		
		case "stage_2":
			PlaySound("VOICE\Russian\saga\Jessica Rose-07.wav");
			dialog.text = "Ха-ха-ха-ха! Тебе не одолеть меня!\nРезерв встанет из могил и да пойдёт в атаку, да вспыхнет пламя над скалой, да подхватит тебя ветер плащом своим и да поглотит земля твои силы хваткой слабости!\nПолучай, ха-ха-ха!!!";
			link.l1 = "...";
			link.l1.go = "stage_2_exit";
		break;
		
		case "stage_2_exit":
			DialogExit();
			LAi_SetActorType(pchar);
			CreateLocationParticles("blast_inv", "quest", "rock", 1.6, 0, 0, "");
			PlaySound("Sea Battles_01\Bomb_Explosion_03.wav");
			PlaySound("People Fight\Death_NPC_08.wav");
			pchar.GenQuest.BladePenalty = 30;
			GetCharacterPos(pchar, &locx, &locy, &locz);
			ChangeCharacterAddressGroup(pchar, "shore67", "goto", LAi_FindNearestFreeLocator("goto", locx, locy, locz));
			LAi_ActorAnimation(Pchar, "Ground_sitting", "", 3.5);
			DoQuestCheckDelay("Saga_JessikaSecondKick_2", 3.5);
		break;
		
		case "stage_3":
			PlaySound("VOICE\Russian\saga\Jessica Rose-07.wav");
			dialog.text = "Ха-ха-ха-ха! Тебе не одолеть меня!\nМой фламберж да окропится ядом, да схватит тебя ветер в объятия свои, да поглотит вода твою ловкость хваткой усталости!\nПолучай, ха-ха-ха!!!";
			link.l1 = "...";
			link.l1.go = "stage_3_exit";
		break;
		
		case "stage_3_exit":
			DialogExit();
			npchar.viper = true;
			TakeNItems(npchar, "potion2", 3);
			LAi_SetActorType(pchar);
			PlaySound("Sea Battles_01\Bomb_Explosion_03.wav");
			PlaySound("People Fight\Death_NPC_08.wav");
			pchar.GenQuest.EnergyPenalty = 2;
			GetCharacterPos(pchar, &locx, &locy, &locz);
			ChangeCharacterAddressGroup(pchar, "shore67", "quest", "bridge2");
			LAi_ActorTurnToLocator(pchar, "quest", "bridge1");
			LAi_ActorAnimation(Pchar, "Ground_sitting", "", 3.5);
			DoQuestCheckDelay("Saga_JessikaThirdKick_2", 3.5);
		break;
		
		case "stage_4":
			PlayStereoOGG("music_shore");
			sld = characterFromId("Svenson");
			dialog.text = "Довольно... У меня нет больше сил. Я побеждена... Сжалься хоть ты над судьбой несчастной Джессики!";
			link.l1 = "Конечно... Я освобожу твою бедную душу от тягот этого мёртвого тела!";
			link.l1.go = "exit_battle";
			if (CheckAttribute(sld, "quest.jessika_peace")) // выслушал историю Джессики
			{
				link.l2 = "Я знаю твою историю, Джессика. И мне жаль, что жизнь твоя сложилась так грустно и закончилась так нелепо. Я вижу, ты хочешь поговорить? Что же, я постараюсь забыть о том, что ты только что чуть не убила меня, и выслушаю, хотя мне это и непросто...";
				link.l2.go = "exit_talk";
			}
		break;
		
		case "exit_battle":
			DialogExit();
			SetMusic("music_teleport");
			DeleteAttribute(npchar, "viper");
			LAi_SetImmortal(npchar, false);
			npchar.chr_ai.hp = stf(npchar.chr_ai.hp)+100;
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "Saga_JessikaDie");
			AddDialogExitQuest("MainHeroFightModeOn");
			pchar.questTemp.Saga.JessSeekTreatment = 0;
			LAi_LocationDisableOfficersGen(pchar.location, false);//офицеров пускать
		break;
		
		case "exit_talk":
			dialog.text = "Спасибо... Ты уже знаешь о Беатрисс Шарп и Лоуренсе... моём Лоуренсе. Я без колебаний убила её, но его - не смогла. Моя рука дрогнула, а его - нет. Джессика погибла...";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuest("Video_Reef");
			NextDiag.TempNode = "exit_talk_0";
		break;
		
		case "exit_talk_0":
			dialog.text = "... но обет, принятый и связанный страшной клятвой, остался не исполненным. Сила этого обета в сочетании с индейским заклятием подняла мёртвое тело из могилы\nНенависть превратила мою душу в пустыню. Все, кто приходил на этот риф ночью, были убиты мной, а их мёртвые тела подчинились мне. Только того, кто смог победить меня, могу я просить о помощи...";
			link.l1 = "Да что же я могу для тебя сделать? Единственное - это освободить от страданий...";
			link.l1.go = "exit_talk_1";
		break;
		
		case "exit_talk_1":
			PlaySound("VOICE\Russian\saga\Jessica Rose-03.wav");
			dialog.text = "Помоги мне... Отвези меня к нему.";
			link.l1 = "К Лоуренсу Белтропу? Да как же я это сделаю? Моя команда или разбежится, завидев тебя, или отправит на костёр без рассуждений. Да и ты можешь перерезать моих людей, а потом 'подчинить их себе'...";
			link.l1.go = "exit_talk_2";
		break;
		
		case "exit_talk_2":
			dialog.text = "Меня никто не увидит. Кроме тебя. Ты должен был уже понять, что мне доступно то, чего никогда не сможет сделать живой. Но я не смогу подняться на твой корабль без твоего согласия. Отвези меня к нему! Отсюда до Ямайки несколько дней пути\nЯ недолго буду твоим спутником. Людей твоих я не трону. Высади меня в полночь в бухте Портленд, а в следующую ночь мы снова встретимся, и ты получишь то, за чем сюда пришёл.";
			link.l1 = "Откуда ты знаешь, почему я здесь?";
			link.l1.go = "exit_talk_3";
		break;
		
		case "exit_talk_3":
			PlaySound("VOICE\Russian\saga\Jessica Rose-01.wav");
			dialog.text = "Я знаю многое. Больше, чем вы, живые. И я видела её... Тебе нужна одна бумага, для неё, и ты её получишь. Ты получишь больше - я дам тебе ещё кое-что. Отвези...";
			link.l1 = "Гм. Мне очень не нравятся твои кровожадные намерения в отношении Элен. Не смей её трогать. В конце концов, она не несёт ответ за свою мать.";
			link.l1.go = "exit_talk_4";
		break;
		
		case "exit_talk_4":
			dialog.text = "Ты победил меня. Я не трону её... Я обещаю.";
			link.l1 = "Это не всё. Ты собираешься снимать с меня заклятия, которыми так обильно наградила? Признаюсь, мне бы не хотелось до конца дней своих остаться в таком виде, в который ты меня привела...";
			link.l1.go = "exit_talk_5";
		break;
		
		case "exit_talk_5":
			dialog.text = "Это не так просто... Когда мы встретимся с тобой в бухте Портленд, после того, как я... Я расскажу тебе, как исцелиться.";
			link.l1 = "После того, как ты?.. Что именно?";
			link.l1.go = "exit_talk_6";
		break;
		
		case "exit_talk_6":
			dialog.text = "После того, как я встречусь с ним.";
			link.l1 = "Ох, он будет очень рад. Могу представить. Ладно, подведём итоги: ты обещаешь, что никто тебя не увидит - раз, что ты не тронешь мою команду - два, что ты забудешь даже думать про Элен - три, отдашь мне то, что я ищу - четыре, и вылечишь от своего колдовства - пять. Так?";
			link.l1.go = "exit_talk_7";
		break;
		
		case "exit_talk_7":
			dialog.text = "Почти. Я не вылечу. Я скажу, как исцелиться. Ты сделаешь это сам.";
			link.l1 = "Хорошо. Тогда договорились. Я разрешаю тебе взойти на мой корабль...";
			link.l1.go = "exit_talk_8";
		break;
		
		case "exit_talk_8":
			PlaySound("Ambient\Teno_inside\teleporter.wav");
			ChangeCharacterAddressGroup(npchar, "none", "", "");
			dialog.text = "";
			link.l1 = "Эй! Ты где? Словно испарилась...";
			link.l1.go = "exit_talk_9";
		break;
		
		case "exit_talk_9":
			DialogExit();
			LAi_group_Delete("EnemyFight");
			pchar.quest.Saga_JessFire.over = "yes"; 
			pchar.quest.Saga_JessFire1.over = "yes"; 
			pchar.quest.Saga_JessFire2.over = "yes";
			ref chr = &Locations[FindLocation(pchar.location)];
			DeleteAttribute(chr, "hell_fire_1");
			DeleteAttribute(chr, "hell_fire_2");
			DeleteAttribute(chr, "hell_fire_3");
			chrDisableReloadToLocation = false;//открыть локацию
			DeleteAttribute(pchar, "GenQuest.CannotWait");//можно мотать время
			AddQuestRecord("Shadows", "9");
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, false);
			pchar.questTemp.Saga.JessOnShip = "true"; // атрибут на отрицательные последствия
			pchar.quest.Saga_Jessika_Travel.win_condition.l1 = "Hour";
			pchar.quest.Saga_Jessika_Travel.win_condition.l1.start.hour = 0.00;
			pchar.quest.Saga_Jessika_Travel.win_condition.l1.finish.hour = 2.00;
			pchar.quest.Saga_Jessika_Travel.win_condition.l2 = "location";
			pchar.quest.Saga_Jessika_Travel.win_condition.l2.location = "shore36";
			pchar.quest.Saga_Jessika_Travel.function = "Saga_JessikaOnJamaica";
			NextDiag.CurrentNode = "shore";
			npchar.greeting = "jessika_2";
			LAi_LocationDisableOfficersGen(pchar.location, false);//офицеров пускать
			LAi_LocationDisableOfficersGen("shore36", true);//офицеров не пускать в бухту Портленд
		break;
		
		case "shore":
			dialog.text = "Ты сдержал слово - мы на Ямайке. Приходи сюда завтра ночью - я выполню своё обещание. До встречи.";
			link.l1 = "До встречи...";
			link.l1.go = "shore_1";
		break;
		
		case "shore_1":
			DialogExit();
			DeleteAttribute(pchar, "questTemp.Saga.JessOnShip");
			DeleteAttribute(npchar, "SaveItemsForDead");
			DeleteAttribute(npchar, "DontClearDead");
			LAi_SetActorType(npchar);
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешить драться
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "OpenTheDoors", -1);
			AddQuestRecord("Shadows", "10");
			SetFunctionTimerCondition("Saga_JessikaShoreWait", 0, 0, 1, false);
			NextDiag.CurrentNode = "shore_2";
			npchar.greeting = "jessika_3";
		break;
		
		case "shore_2":
			dialog.text = "Вот и всё, "+pchar.name+"...";
			link.l1 = "Что - всё?";
			link.l1.go = "shore_3";
		break;
		
		case "shore_3":
			dialog.text = "Всё - это всё... Вот, держи то, что ты искал. Это письмо моей соперницы, похороненное вместе с ней. Оно хорошо сохранилось. Теперь я простила её, и в моей душе нет более ненависти.";
			link.l1 = "Ты... встретилась с ним? С Лоуренсом?";
			link.l1.go = "shore_4";
		break;
		
		case "shore_4":
			GiveItem2Character(pchar, "letter_beatriss"); // дать письмо
			AddQuestRecordInfo("Letter_beatriss", "1");
			dialog.text = "Да. Последнее, что он испытал в своей жизни - это ужас. Мне не жаль его.";
			link.l1 = "Упокой Господи его грешную душу... Видно, так и не придётся мне с ним встретиться.";
			link.l1.go = "shore_5";
		break;
		
		case "shore_5":
			dialog.text = "Ты ничего не потерял от того, что не увидел его. Он очень плохой человек. А сейчас будем прощаться - меня ничего более здесь не держит. Обет выполнен, заклятие потеряло силу. Я обещала тебе подарок. Вот. Это мой фламберж. Мне он больше не нужен. Это уникальный клинок, второго такого нет на свете.";
			link.l1 = "Спасибо...";
			link.l1.go = "shore_6";
		break;
		
		case "shore_6":
			RemoveAllCharacterItems(npchar, true);
			GiveItem2Character(pchar, "blade_25");
			PlaySound("interface\important_item.wav");
			dialog.text = "Теперь о тебе. Чтобы снять мои заклятия, отправляйся в Бриджтаун, в местную церковь. Там найдёшь священника. Он знал меня лично. Обратись к нему - он скажет, что делать. Запасись заранее двумя десятками восковых свечей - они тебе понадобятся.";
			link.l1 = "Он точно вылечит меня?";
			link.l1.go = "shore_7";
		break;
		
		case "shore_7":
			dialog.text = "Ты всё сделаешь сам. Господь поможет тебе. Будь уверен. Всё будет хорошо.";
			link.l1 = "Ладно, я немедленно отправлюсь на Барбадос. И что теперь?";
			link.l1.go = "shore_8";
		break;
		
		case "shore_8":
			PlaySound("VOICE\Russian\saga\Jessica Rose-04.wav");
			dialog.text = "А теперь у меня к тебе последняя просьба: похорони моё тело в этой бухте, у моря. Я так хочу. Может, когда-нибудь навестишь могилку несчастной Джессики. Прощай, "+pchar.name+", и помолись за меня...";
			link.l1 = "Джесс?..";
			link.l1.go = "shore_9";
		break;
		
		case "shore_9":
			DialogExit();
			LAi_KillCharacter(npchar);
			bQuestDisableMapEnter = false;
			DeleteAttribute(pchar, "GenQuest.MapClosedNoBattle");
			chrDisableReloadToLocation = false;
			LAi_LocationDisableOfficersGen("shore36", false);
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			AddQuestRecord("Shadows", "11");
			pchar.questTemp.Saga.JessTreatment = "true";
			// вытираем Белтропа
			sld = characterFromId("Beltrop");
			sld.lifeday = 0;
			pchar.questTemp.Saga.Beltrop_die = "true"; // Белтроп убит
			sld = ItemsFromID("letter_jess");
			sld.price = 1; // страницу можно выкладывать 270912 
		break;
		
		case "soul":
			dialog.text = "Ты не узнал меня, капитан?";
			link.l1 = "Это... это ты? Но как?";
			link.l1.go = "soul_1";
		break;
		
		case "soul_1":
			dialog.text = "Да, "+pchar.name+", это я, Джессика! По крайней мере, такой я была двадцать лет назад.";
			link.l1 = "Получается... я тоже умер? Но когда же я успел? Как это случилось?";
			link.l1.go = "soul_2";
		break;
		
		case "soul_2":
			dialog.text = "Ты не умер, "+pchar.name+". Сейчас ты находишься в церкви Бриджтауна. Ты просто... спишь.";
			link.l1 = "А ты мне видишься? Что-то уж очень реально...";
			link.l1.go = "soul_3";
		break;
		
		case "soul_3":
			dialog.text = "Так бывает, "+pchar.name+". Господь услышал тебя. Твои молитвы не только исцелили тебя, но и очистили мою душу от скверны. Спасибо тебе большое, "+pchar.name+"! И я хочу попросить у тебя прощения за то, что произошло на рифе. Это... в общем, просто прости меня. Я не могла уйти, не испросив твоего прощения.";
			link.l1 = "Я прощаю тебя, Джессика. А я точно жив?";
			link.l1.go = "soul_4";
		break;
		
		case "soul_4":
			dialog.text = "Точно... Не переживай. Скоро ты проснёшься. Я просто пришла с тобой проститься.";
			link.l1 = "Какая ты... красивая!";
			link.l1.go = "soul_5";
		break;
		
		case "soul_5":
			dialog.text = "Нравлюсь? Да, когда-то за мной бегали лучшие женихи Малых Антил, а каждый третий пират с Исла Тесоро был готов драться за меня на дуэли.";
			link.l1 = "Но тебе был нужен только один... Эх, рыжий талисман! За что же тебя так?..";
			link.l1.go = "soul_6";
		break;
		
		case "soul_6":
			dialog.text = "За злобу. За ненависть. За неспособность понять, простить и забыть. Я могла начать новую жизнь, но предпочла посвятить себя глупой и бессмысленной мести. И была наказана страшной карой. Ты смог освободить меня. Спасибо тебе, "+pchar.name+"...";
			link.l1 = "Мне действительно жаль, что у тебя всё так вышло...";
			link.l1.go = "soul_7";
		break;
		
		// здесь проверяем Мэри
		case "soul_7":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{ // Мэри-офицер
				dialog.text = "Не жалей... У тебя, кстати, тоже есть рыжий талисман...";
				link.l1 = "Да? И кто же это?";
				link.l1.go = "mary_1";
				break;
			}
			if (!CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && CheckAttribute(pchar, "questTemp.LSC.marywait"))
			{ // Мэри осталась на острове
				dialog.text = "Не жалей... У тебя, кстати, тоже есть рыжий талисман...";
				link.l1 = "Да? И кто же это?";
				link.l1.go = "mary_3";
				break;
			}
			dialog.text = "Не жалей... Лучше учти мой горький опыт и не повтори подобного в своей жизни. И не позволь повторить близкому тебе человеку.";
			link.l1 = "Я учту. Я обязательно это учту...";
			link.l1.go = "soul_8";
		break;
		
		case "mary_1":
			dialog.text = "Подумай немного. Она у тебя на корабле.";
			link.l1 = "Мэри?!";
			link.l1.go = "mary_2";
		break;
		
		case "mary_2":
			dialog.text = "Да. Она - лучшее, что есть, и что будет у тебя в жизни. Запомни это. Её любовь чиста, её преданность безгранична. Она смела, отчаянна, но молода и неопытна, и многого не понимает. Заботься о ней, береги её, не позволь никому встать между вами. Она - твой талисман...";
			link.l1 = "Я учту. Я обязательно это учту...";
			link.l1.go = "soul_8";
		break;
		
		case "mary_3":
			dialog.text = "Она на странном острове из погибших кораблей посреди моря... Она там не одна, но она одинока. Каждое её утро начинается с мысли о тебе, каждый день она посылает Господу молитву за тебя, а по ночам в её каюте не гаснет свет, и подушка её мокра от слёз...";
			link.l1 = "Мэри...";
			link.l1.go = "mary_4";
		break;
		
		case "mary_4":
			dialog.text = "Между ней и тобой стоит дочь той, которая встала когда-то между мной и Лоуренсом. Судьба твоего талисмана в твоих руках. Они не смогут сосуществовать вместе, точно так же, как я и Беатрисс.";
			link.l1 = "Откуда же тебе всё известно?";
			link.l1.go = "mary_5";
		break;
		
		case "mary_5":
			dialog.text = "Там... там становится известно многое. Решай, но помни: Мэри - лучшее, что есть, и что будет у тебя в жизни. Её любовь чиста, её преданность безгранична. Она смела, отчаянна, но молода и неопытна, и многого не понимает. Ей нужна твоя защита, твоя забота и твоя любовь. Она - твой талисман.";
			link.l1 = "Я учту. Я обязательно это учту...";
			link.l1.go = "soul_8";
		break;
		
		case "soul_8":
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_friend")) sTemp = "";
			else sTemp = "Что же касается дочери Беатрисс, то твои благородные поступки в её отношении так и останутся неоцененными. Скоро ты в этом убедишься. Будь с ней осторожен. Ну а теперь\n";
			dialog.text = ""+sTemp+"Мне пора уходить. Пришло время расстаться... На этот раз - навсегда. Не забывай Джессику, и хотя бы изредка навещай её могилку... Ведь только ты один знаешь, где она.";
			link.l1 = "Обязательно, Джесс. Я и навещу, и помолюсь за тебя.";
			link.l1.go = "soul_9";
		break;
		
		case "soul_9":
			dialog.text = "Спасибо. Прощай, "+pchar.name+"! Прощай!";
			link.l1 = "Прощай, Джессика...";
			link.l1.go = "soul_10";
		break;
		
		case "soul_10":
			DialogExit();
			LAi_SetActorType(pchar);
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "Saga_JessikaSoul_4", -1);
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}