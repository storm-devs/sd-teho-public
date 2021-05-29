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
					dialog.text = "Hm. You sail under the flag of "+NationNameGenitive(sti(pchar.nation))+", pal. I have no wish in talking with you and I don't want problems... Leave me!";
					link.l1 = "And you call yourself a captain...";
					link.l1.go = "exit";
					break;
				}
				if (CheckAttribute(npchar, "quest.march") && !CheckAttribute(pchar, "questTemp.Sharlie.Lock"))//боевые генераторные квесты
				{
					dialog.text = "Ha! You're just in time, captain... I have a business proposal to you. Do you have a few hours for me?";
					link.l1 = "I don't. I am in a hurry, colleague. Next time maybe.";
					link.l1.go = "exit_quest";
					link.l2 = "I do. I am ready to listen to you. Where are we going? To the tavern?";
					link.l2.go = "march";
					break;
				}
				dialog.text = "Ha, good day to you, colleague! It's good to see a prosperous captain!";
				link.l1 = "Glad to see you, sir! My name is "+GetFullName(pchar)+". Do you have a spare minute to talk?";
				link.l1.go = "question";
				npchar.quest.meeting = "1";
			}
			else
			{
				//повторные обращения
				if (sti(NPChar.nation) != PIRATE && GetNationRelation2MainCharacter(sti(NPChar.nation)) == RELATION_ENEMY)
				{
					dialog.text = "Should I repeat myself? I don't want to be suspected as a friend of "+NationNameAblative(sti(pchar.nation))+"! Get lost or I will call the guards!";
					link.l1 = "Fine, fine, calm down. I am leaving.";
					link.l1.go = "exit";
				}
				else
				{
					dialog.text = "What do you want?";
					link.l1 = "Nothing.";
					link.l1.go = "exit";
				}
			}
			NextDiag.TempNode = "First time";
		break;

		case "question":
			dialog.text = NPCStringReactionRepeat(""+GetFullName(npchar)+" at you service, good sir! What would you like to know?", 
				"Glad to talk with you, captain!", 
				"Well, I suppose I have a free minute to talk...",
                "Unfortunately, I have to go. See you!", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Do you have anything interesting to tell me about?", 
				"Do you have anything interesting to tell me about?",
                "Do you have anything interesting to tell me about?", 
				"Sure. Good luck!", npchar, Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("rumours_landcaptain", "rumours_landcaptain", "rumours_landcaptain", "exit", npchar, Dialog.CurrentNode);
		break;
		
		//квестовая часть
			case "march":
				dialog.text = "No, captain there are a lot of eyes and ears on sreets and in the tavern and we don't need them, trust me. This proposal is all about taking something from someone so... let's have a talk on my ship.";
				link.l1 = "Fine... What's your ship and her name?";
				link.l1.go = "march_1";
				link.l2 = "It looks quite suspicious to me... No, I'd better reject your invitation... Farewell, sir!";
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
				dialog.text = "My ship is "+GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.MarchCap.shiptype), "Name")))+" '"+pchar.GenQuest.MarchCap.shipname+" and she's in the harbor. Don't be late captain, I'll be away in six hours!";
				link.l1 = "I see, I will try to be in time. See you!";
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
			dialog.text = NPCharSexPhrase(NPChar, "Listen, as a citizen of this town I'm asking you to return your blade into its sheath.", "Listen, as a citizen of this town I'm asking you to return your blade into its sheath.");
			link.l1 = LinkRandPhrase("Fine.", "As you wish.", "As you say...");
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