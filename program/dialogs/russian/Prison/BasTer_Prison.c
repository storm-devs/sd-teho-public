// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
 	switch(Dialog.CurrentNode)
	{
        case "quests":
            dialog.text = "Говорите, я слушаю.";
			link.l1 = "Я "+ GetSexPhrase("ошибся","ошиблась") +". Прощайте.";
			link.l1.go = "Exit";
			if (CheckAttribute(pchar, "questTemp.Sharlie.Tichingitu") && pchar.questTemp.Sharlie.Tichingitu == "true")
            {
                link.l1 = "У вас под стражей содержится некий индеец, которого схватил Фадей Московит. Можно мне было бы взглянуть на него?";
                link.l1.go = "Tichingitu";
            }
			if (CheckAttribute(pchar, "questTemp.Sharlie.Tichingitu") && pchar.questTemp.Sharlie.Tichingitu == "commandante")
            {
                link.l1 = "Скажите, вы действительно собираетесь повесить этого индейца? Не слишком ли суровое наказание за столь мелкое пригрешение?";
                link.l1.go = "Tichingitu_3";
            }
			if (CheckAttribute(pchar, "questTemp.Sharlie.Tichingitu") && pchar.questTemp.Sharlie.Tichingitu == "pay")
            {
                link.l1 = "Это опять я, комендант. Фадей Московит написал прошение о помиловании индейца. Вот оно.";
                link.l1.go = "Tichingitu_6";
            }
		break;
		
		case "Tichingitu":
			dialog.text = "А-а, Фадей и вам рассказал свою историю? Не вижу причин препятствовать вам, месье. Вы не первый, кто приходит смотреть на этого краснокожего. Хотя дней через десять на него смогут полюбоваться все жители нашего города, когда мы его вздернем сушиться на солнышке...";
			link.l1 = "Так я могу пройти в казематы?";
			link.l1.go = "Tichingitu_1";
		break;
		
		case "Tichingitu_1":
			dialog.text = "Я же говорю - не вижу причины отказывать вам. Проходите.";
			link.l1 = "Спасибо!";
			link.l1.go = "Tichingitu_2";
		break;
		
		case "Tichingitu_2":
			DialogExit();
			pchar.questTemp.Sharlie.Tichingitu = "wait";
			pchar.questTemp.jailCanMove = true;
		break;
		
		case "Tichingitu_3":
			dialog.text = "Месье, вы, наверное, недавно прибыли к нам из Европы? Вы не понимаете ситуации в наших колониях. Эта казнь послужит уроком всем остальным краснокожим негодяям, осмелящимся посягнуть на имущество французких колонистов. Кроме того, на этом настаивает Фадей, а он очень уважаемый человек в нашем городе и близкий друг губернатора.";
			link.l1 = "Неужели никак нельзя смягчить наказание? Я все равно считаю, что это неоправданно сурово...";
			link.l1.go = "Tichingitu_4";
		break;
		
		case "Tichingitu_4":
			dialog.text = "Ох, молодой человек, не вдавайтесь в философию! Если вас так задел этот вопрос - отправляйтесь к Фадею Московиту и просите за индейца именно его. Если Фадей напишет ходатайство о помиловании - мы удовлетворим его.";
			link.l1 = "Я все понял, офицер. Отправляюсь к Фадею.";
			link.l1.go = "Tichingitu_5";
		break;
		
		case "Tichingitu_5":
			DialogExit();
			pchar.questTemp.Sharlie.Tichingitu = "fadey";
		break;
		
		case "Tichingitu_6":
			RemoveItems(pchar, "letter_1", 1);
			dialog.text = "(читает) Хм... Странный этот Фадей: сначала требует показательной казни, а теперь просит отпустить индейца... Ну да ладно, видимо, у всех губернаторских друзей подобные причуды. Хорошо, можете идти к камере и забирать этого краснокожего.";
			link.l1 = "Благодарствую, офицер!";
			link.l1.go = "Tichingitu_7";
		break;
		
		case "Tichingitu_7":
			DialogExit();
			pchar.questTemp.Sharlie.Tichingitu = "wait";
			pchar.questTemp.jailCanMove = true;
			sld = characterFromId("Tichingitu");
			sld.dialog.currentnode = "Tichingitu_6";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
