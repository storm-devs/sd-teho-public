// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Что вам угодно?", "Что вы хотели узнать?"), "Так скажите, что же вас интересует, " + GetAddress_Form(NPChar) + "?", "Третий раз за сегодня вы пытаетесь задать вопрос...", "Всё, вы меня утомили. Покиньте мой дом!", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Я передумал"+ GetSexPhrase("","а") +"...", "Сейчас мне не о чем говорить"), "Ох, что-то я запамятовал. Простите...",
                      "Да уж, действительно в третий раз...", "Извиняюсь...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			// калеуче
			if (CheckAttribute(pchar, "questTemp.Caleuche") && pchar.questTemp.Caleuche == "graveyard" && !CheckAttribute(npchar, "quest.caleuche"))
			{
				link.l1 = "Послушай, ты не встречал в Гаване или окрестностях человека по имени Жоаким Мерриман? Немолодой сеньор, португалец, носит усы и эспаньолку, с пронзительным взглядом? В бухтах, в джунглях? Не видал такого?";
				link.l1.go = "caleuche";
			}
		break;
		
		// калеуче
		case "caleuche":
			dialog.text = "Н-нет, моряк, т-точно, нет. Здесь, знаешь ли, вообще мало кто бывает, и такого типа я не видал...";
			link.l1 = "Хм. А чего это ты вдруг заикаться стал, приятель? И глазки из стороны в сторону забегали... Сдается мне, что ты врешь. Ну-ка, признавайся: ты видел этого человека?";
			link.l1.go = "caleuche_1";
		break;
		
		case "caleuche_1":
			dialog.text = "Г-говорю же вам, сеньор, не видел я н-никого! А з-заикаюсь я с детства, в-вот...";
			link.l1 = "Ты лжешь. Я по глазам вижу. Где Мерриман?! Отвечай!";
			link.l1.go = "caleuche_2";
		break;
		
		case "caleuche_2":
			dialog.text = "Не знаю я никакого Мерримана! А если вы меня тронете - то комендант вас вздернет в форте, имейте это в виду!";
			link.l1 = "Ах, вот как! Ну ладно... Теперь слушай внимательно и вникай: Жоаким Мерриман - колдун. Его жаждет заполучить священная инквизиция. Его много лет назад, еще в Европе, приговорили к сожжению за раскапывание могил, надругательства над трупами и колдовство. Я точно знаю, что он прячется в окрестностях Гаваны...";
			link.l1.go = "caleuche_3";
		break;
		
		case "caleuche_3":
			dialog.text = "";
			link.l1 = "...я недавно зачистил пещеру, тут, недалеко, от зомби. И я знаю, чьих это рук дело. Ха! Конечно, куда бы мог пойти Мерриман, как не на кладбище! Ты знаешь, где он. Так вот: я тебя пальцем не трону, зато прямо сейчас отправлюсь в Сантьяго в инквизицию и доложу отцу Винсенто, что Жоаким Мерриман скрывается на кладбище Гаваны, и в пособниках у него кладбищенский сторож...";
			link.l1.go = "caleuche_4";
		break;
		
		case "caleuche_4":
			dialog.text = "";
			link.l1 = "... Что ты так побледнел? Я даю тебе слово дворянина, что и дня не пройдет после моего доклада, как здесь будет все кишеть испанскими солдатами, а ты, вздернутый на дыбу, будешь рассказывать, где прячется колдун. И потом пойдешь вместе с ним на костер как соучастник. А я приду посмотреть на аутодафе. Как тебе перспектива?";
			link.l1.go = "caleuche_5";
		break;
		
		case "caleuche_5":
			dialog.text = "Помилуйте, помилуйте, сеньор! Я не участвую во всем этом, клянусь! Я просто... я просто ничего не мог... Как я могу противостоять ему? Он ужасный человек, он может... вы не представляете, что он может! Пощадите!";
			link.l1 = "Я знаю, что он может. Своими глазами видел. Ну? Где он? Расскажешь сам - даю слово, что не буду впутывать тебя в это дело.";
			link.l1.go = "caleuche_6";
		break;
		
		case "caleuche_6":
			dialog.text = "Он... он скрывается в пещере под кладбищем. Туда можно попасть только через дверь в часовне. Когда он выходит оттуда, я прячусь в своем доме и носа не кажу. Вы не представляете, как я хотел бы избавиться от этого ужаса!\nНо я не смею даже приблизиться к нему. Я видел... как он раскопал свежую могилу, вытащил оттуда труп, а потом этот труп ходил по кладбищу при луне! Я тогда чуть расудка не лишился. Мерриман запретил мне уходить. Сказал, что если я посмею отлучиться из дома без разрешения хоть на полдня, то он меня найдет и превратит... вот в это, в скелет ходячий!";
			link.l1 = "Как часто он выходит из своего логова?";
			link.l1.go = "caleuche_7";
		break;
		
		case "caleuche_7":
			dialog.text = "Я приношу ему из города еду, лечебные зелья и всё, что он потребует. Сам он выходит редко, не чаще раза или двух в месяц... когда на небе полная луна. Он оставляет записку у двери, в которой указывает, что ему нужно, я приношу, ставлю у двери, а он потом забирает.";
			link.l1 = "Ясно. Эта дверь в его логово - она заперта?";
			link.l1.go = "caleuche_8";
		break;
		
		case "caleuche_8":
			dialog.text = "Всегда заперта, очень прочна, и с надежным замком.";
			link.l1 = "Хм. Мерриман не дурак - наверняка в его убежище есть потайной выход, как в его европейском доме. Начнем ломать дверь - он сбежит, и ищи-свищи потом. Надо подумать...";
			link.l1.go = "caleuche_9";
		break;
		
		case "caleuche_9":
			dialog.text = "Сеньор, вы клянетесь, что не выдадите меня инквизиции?";
			link.l1 = "Я тебе дал слово, а слово дворянина - священно. Клянусь, что не выдам тебя.";
			link.l1.go = "caleuche_10";
		break;
		
		case "caleuche_10":
			dialog.text = "Я знаю, как попасть туда. Есть второй ключ... он у меня. Мерриман не знал, что у замка два ключа. Сам бы я никогда не осмелился войти туда, но вам...";
			link.l1 = "Дай мне этот ключ, и я избавлю твою жизнь от кошмара.";
			link.l1.go = "caleuche_11";
		break;
		
		case "caleuche_11":
			GiveItem2Character(pchar, "kaleuche_key");
			ChangeItemDescribe("kaleuche_key", "itmdescr_kaleuche_key_crypt");
			dialog.text = "Возьмите, сеньор. Вы собираетесь пойти туда?";
			link.l1 = "Именно. Запрись в доме и не высовывайся, когда я туда пойду. Если я не вернусь - беги из этих мест без оглядки.";
			link.l1.go = "caleuche_12";
		break;
		
		case "caleuche_12":
			dialog.text = "Будьте осторожны, сеньор. Из его пещеры доносятся такие страшные звуки, что я даже боюсь представить, кто или что там живет. Но Мерриман там не один, это точно.";
			link.l1 = "Я приму все возможные меры.";
			link.l1.go = "caleuche_13";
		break;
		
		case "caleuche_13":
			DialogExit();
			AddQuestRecord("Caleuche", "30");
			pchar.questTemp.Caleuche = "merriman";
			pchar.quest.caleuche_merriman_cave.win_condition.l1 = "locator";
			pchar.quest.caleuche_merriman_cave.win_condition.l1.location = "Havana_CryptBig2";
			pchar.quest.caleuche_merriman_cave.win_condition.l1.locator_group = "reload";
			pchar.quest.caleuche_merriman_cave.win_condition.l1.locator = "reload2";
			pchar.quest.caleuche_merriman_cave.function = "Caleuche_OpenMerrimanCave";
			pchar.quest.caleuche_merriman_cave1.win_condition.l1 = "location";
			pchar.quest.caleuche_merriman_cave1.win_condition.l1.location = "Havana_CryptDungeon";
			pchar.quest.caleuche_merriman_cave1.function = "Caleuche_InMerrimanCave";
			SetFunctionTimerCondition("Caleuche_MerrimanCaveOver", 0, 0, 3, false); // таймер
			npchar.quest.caleuche = "true";
			// логово Мерримана
			int n = Findlocation("Havana_CryptDungeon");
			locations[n].id.label = "Merrimancave";
		break;
	}
	UnloadSegment(NPChar.FileDialog2); 
}

