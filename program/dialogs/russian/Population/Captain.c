//Jason общий диалог праздношатающихся по улицам капитанов
#include "DIALOGS\russian\Rumours\Common_rumours.c"
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	ProcessCommonDialogRumors(NPChar, Link, NextDiag);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			//первая встреча
			if (npchar.quest.meeting == "0")
			{
				if (sti(NPChar.nation) != PIRATE && GetNationRelation2MainCharacter(sti(NPChar.nation)) == RELATION_ENEMY)//проверка межнациональных отношений
				{
					dialog.text = "Хм. Ты ходишь под флагом "+NationNameGenitive(sti(pchar.nation))+", приятель. У меня нет никакого желания с тобой общаться - потом проблем не оберешься... Ступай своей дорогой!";
					link.l1 = "Ну надо же, сам - капитан, а все туда же...";
					link.l1.go = "exit";
					break;
				}
				if (CheckAttribute(npchar, "quest.march") && !CheckAttribute(pchar, "questTemp.Sharlie.Lock") && GetCompanionQuantity(pchar) < 5)//боевые генераторные квесты 2015
				{
					dialog.text = "Ха! Вы очень вовремя, капитан... У меня к вам деловое предложение. У вас есть пара свободных часов?";
					link.l1 = "Нет. Я тороплюсь, коллега. Как-нибудь в другой раз.";
					link.l1.go = "exit_quest";
					link.l2 = "Есть. Я готов вас выслушать. Куда отправимся? В таверну?";
					link.l2.go = "march";
					break;
				}
				dialog.text = "Ха, приветствую вас, коллега! Приятно видеть преуспевающего капитана!";
				link.l1 = "Рад встрече, уважаемый! Мое имя - "+GetFullName(pchar)+". Не найдется минутки поболтать?";
				link.l1.go = "question";
				npchar.quest.meeting = "1";
			}
			else
			{
				//повторные обращения
				if (sti(NPChar.nation) != PIRATE && GetNationRelation2MainCharacter(sti(NPChar.nation)) == RELATION_ENEMY)
				{
					dialog.text = "Я что, непонятно выражаюсь? Я не желаю, чтобы меня заподозрили в связи с "+NationNameAblative(sti(pchar.nation))+"! Проваливай, не то точно страже доложу!";
					link.l1 = "Ладно-ладно, не кипятись. Ухожу.";
					link.l1.go = "exit";
				}
				else
				{
					dialog.text = "Что вам надо?";
					link.l1 = "Ничего.";
					link.l1.go = "exit";
				}
			}
			NextDiag.TempNode = "First time";
		break;

		case "question":
			dialog.text = NPCStringReactionRepeat(""+GetFullName(npchar)+" к вашим услугам, милейший! Что вы хотели узнать?", 
				"Рад поболтать, капитан!", 
				"Ну, пожалуй, у меня есть еще время...",
                "К сожалению, мне пора идти. Всего доброго!", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Может, расскажете что интересное?", 
				"Может, расскажете что интересное?",
                "Может, расскажете что интересное?", 
				"Да, конечно. Удачи вам!", npchar, Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("rumours_landcaptain", "rumours_landcaptain", "rumours_landcaptain", "exit", npchar, Dialog.CurrentNode);
		break;
		
		//квестовая часть
			case "march":
				dialog.text = "Нет, капитан, на улице и в таверне много лишних ушей, а они нам ни к чему, уверяю вас. Дело пойдет о том, чтобы кое-кого хорошенько пощипать, так что... давайте лучше побеседуем у меня на корабле.";
				link.l1 = "Хорошо... Что у вас за судно и как называется?";
				link.l1.go = "march_1";
				link.l2 = "Что-то мне это кажется подозрительным... Нет, пожалуй, я откажусь от вашего приглашения. Прощайте, сударь!";
				link.l2.go = "exit_quest";
			break;
			
			case "march_1":
				//генерируем и запоминаем параметры в пчар, т.к. через нпчар не хочет нормально работать :(
				pchar.GenQuest.MarchCap.Startisland = Islands[GetCharacterCurrentIsland(PChar)].id;
				pchar.GenQuest.MarchCap.Parts = GetCompanionQuantity(pchar)+1;
				pchar.GenQuest.MarchCap.shiptype = SelectCaptainShipType();
				pchar.GenQuest.MarchCap.shipname = GenerateRandomNameToShip(sti(npchar.nation));
				pchar.GenQuest.MarchCap.nation = sti(npchar.Nation);
				pchar.GenQuest.MarchCap.model = npchar.model;
				pchar.GenQuest.MarchCap.rank = sti(npchar.rank);
				pchar.GenQuest.MarchCap.name = npchar.name;
				pchar.GenQuest.MarchCap.lastname = npchar.lastname;
				pchar.GenQuest.MarchCap.BaseNation = npchar.nation;
				pchar.GenQuest.MarchCap.Nation = drand(HOLLAND);
				pchar.GenQuest.MarchCap.basecity = npchar.city;
				dialog.text = "Мой корабль - "+GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.MarchCap.shiptype), "Name")))+" '"+pchar.GenQuest.MarchCap.shipname+"', стоит на рейде. Не затягивайте, капитан: через шесть часов я планирую поднимать якоря!";
				link.l1 = "Понятно. Постараюсь прибыть к вам вовремя. До встречи!";
				link.l1.go = "march_2";
			break;
			
			case "march_2":
			DialogExit();
				LAi_SetActorType(npchar);
				LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "", 30.0);
				npchar.lifeday = 0;
				pchar.quest.MarchCapOver.win_condition.l1 = "Timer";
				pchar.quest.MarchCapOver.win_condition.l1.date.hour  = sti(GetTime() + 6);
				pchar.quest.MarchCapOver.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 0);
				pchar.quest.MarchCapOver.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 0);
				pchar.quest.MarchCapOver.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 0);
				pchar.quest.MarchCapOver.function = "MarchCap_Over";
				pchar.quest.MarchCap_Create.win_condition.l1 = "location";
				pchar.quest.MarchCap_Create.win_condition.l1.location = pchar.GenQuest.MarchCap.Startisland;
				pchar.quest.MarchCap_Create.function = "MarchCap_Create";
				log_Testinfo(pchar.GenQuest.MarchCap.Startisland);
			break;
			
		//замечание по обнаженному оружию от персонажей типа citizen
		case "CitizenNotBlade":
			dialog.text = NPCharSexPhrase(NPChar, "Послушайте, я, как гражданин этого города, прошу вас не ходить у нас с обнаженным клинком.", "Знаете, я, как гражданка этого города, прошу вас не ходить у нас с обнаженным клинком.");
			link.l1 = LinkRandPhrase("Хорошо.", "Ладно.", "Как скажете...");
			link.l1.go = "exit";
		break;
		
		case "exit_quest":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}

int SelectCaptainShipType()
{
	int iType;
	if (sti(pchar.rank) >= 19) iType = SHIP_FRIGATE_H;	
	if (sti(pchar.rank) >= 13 && sti(pchar.rank) < 19) iType = SHIP_GALEON_H + drand(makeint(SHIP_FRIGATE_H - SHIP_GALEON_H));	
	if (sti(pchar.rank) >= 8 && sti(pchar.rank) < 12) iType =  SHIP_CORVETTE + drand(makeint(SHIP_POLACRE -  SHIP_CORVETTE));
	if (sti(pchar.rank) >= 5 && sti(pchar.rank) < 8) iType = SHIP_BRIGANTINE + drand(makeint(SHIP_GALEON_L - SHIP_BRIGANTINE));
	if (sti(pchar.rank) < 5) iType = SHIP_CAREERLUGGER + drand(makeint(SHIP_SLOOP - SHIP_CAREERLUGGER));
	
	return iType;
}