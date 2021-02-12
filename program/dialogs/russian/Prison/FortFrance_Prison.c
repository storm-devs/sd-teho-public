// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
 	switch(Dialog.CurrentNode)
	{
        case "quests":
            dialog.text = "Говорите, я слушаю.";
			link.l1 = "Я "+ GetSexPhrase("ошибся","ошиблась") +". Прощайте.";
			link.l1.go = "Exit";
			//--> Бремя гасконца
			if (CheckAttribute(pchar, "questTemp.Sharlie") && pchar.questTemp.Sharlie == "jailskiper")
			{
				link.l1 = "Офицер, я тут узнал, что у вас в тюрьме содержится человек по имени Фульк Делюк. Можно ли как-нибудь поспособствовать его освобождению?";
                link.l1.go = "Sharlie";
			}
			if (CheckAttribute(pchar, "questTemp.Sharlie") && pchar.questTemp.Sharlie == "freeskiper")
			{
				link.l1 = "Офицер, я снова по поводу заключённого Фульк Делюка. Я купил право на его долг у ростовщика, и теперь хочу, чтобы этого человека передали мне. Вот его долговые бумаги, ознакомьтесь.";
                link.l1.go = "Sharlie_3";
			}	
			//<-- Бремя гасконца
		break;
		
		//--> Бремя гасконца
		case "Sharlie":
			dialog.text = "А, этот моряк? Он взял в долг у нашего ростовщика приличную сумму денег, не вернул её вовремя и, более того - стал скрываться. Однако его быстро нашли. С тех пор он под замком, и пока не выплатит всю сумму - будет сидеть за решёткой.";
			link.l1 = "Хм. Но как же он сможет заработать денег, находясь в тюрьме?";
			link.l1.go = "Sharlie_1";
		break;
		
		case "Sharlie_1":
			dialog.text = "А это, месье, меня не касается.";
			link.l1 = "Забавно... И сколько же он должен, этот несчастный?";
			link.l1.go = "Sharlie_2";
		break;
		
		case "Sharlie_2":
			dialog.text = "Не знаю. Спросите у ростовщика - он вам подробно всё расскажет.";
			link.l1 = "Понятно. Ну что же, спасибо за информацию, офицер.";
			link.l1.go = "exit";
			pchar.questTemp.Sharlie = "bankskiper";
		break;
		
		case "Sharlie_3":
			Log_Info("Вы передали долговые расписки");
			PlaySound("interface\important_item.wav");
			RemoveItems(pchar, "letter_open", 1);
			dialog.text = "Хм. Всё верно. Вы действительно хотите, чтобы я освободил этого заключённого?";
			link.l1 = "Да. Иначе как он мне вернёт мои деньги? У меня есть способ заставить его отработать уплаченную сумму.";
			link.l1.go = "Sharlie_4";
		break;
		
		case "Sharlie_4":
			dialog.text = "Хорошо, месье. Я не вижу причин вам отказывать. Делюка сейчас приведут. Но я считаю своим долгом предупредить вас, что этот лис ускользнёт от вас при первой же возможности, так что не питайте на его счёт никаких иллюзий.";
			link.l1 = "Я учту это, офицер. А теперь я бы хотел забрать своего должника.";
			link.l1.go = "Sharlie_5";
		break;
		
		case "Sharlie_5":
			dialog.text = "Да, конечно. Сержант! Привести сюда заключённого Фулька Делюка!";
			link.l1 = "...";
			link.l1.go = "Sharlie_6";
		break;
		
		case "Sharlie_6":
			DialogExit();
			chrDisableReloadToLocation = true;//закрыть локацию
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], true);//запретить драться
			// замораживаем ГГ
			LAi_SetActorType(pchar);
			LAi_ActorTurnToLocator(pchar, "goto", "goto17"); // 170712
			//создаем штурмана
			ref sld = GetCharacter(NPC_GenerateCharacter("Folke", "DeLuck", "man", "man", 1, FRANCE, -1, false, "quest"));
			sld.name = "Фульк";
			sld.lastname = "Делюк";
			sld.greeting = "officer_hire";
			sld.Dialog.Filename = "Quest\Sharlie\OtherNPC.c";
			sld.dialog.currentnode = "Folke";
			LAi_SetImmortal(sld, true);
			sld.CompanionDisable = true;
			sld.rank = 5;
			LAi_SetHP(sld, 90, 90);
			sld.money = 0;
			SetSelfSkill(sld, 25, 28, 21, 24, 22);
			SetShipSkill(sld, 10, 5, 24, 22, 25, 15, 5, 15, 18);
			SetSPECIAL(sld, 8, 9, 6, 5, 10, 7, 5);
			SetCharacterPerk(sld, "ShipSpeedUp");
			SetCharacterPerk(sld, "HullDamageUp");
			SetCharacterPerk(sld, "BasicDefense");
			GiveItem2Character(sld, "unarmed");
			EquipCharacterbyItem(sld, "unarmed");
			ChangeCharacterAddressGroup(sld, "Fortfrance_prison", "goto", "goto23");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocator(sld, "reload", "reload1", "FolkeStay", -1);
			pchar.questTemp.Sharlie = "takeskiper";
		break;
		//<-- Бремя гасконца
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
