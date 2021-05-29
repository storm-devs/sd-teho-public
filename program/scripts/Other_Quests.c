// Прочие квесты

//=====================================================================================================================================
// Warship, 26.05.11. Серия миниквестов "Дело чести" -->
//=====================================================================================================================================
// Функция вернет строковый идентификатор квеста из дел чести, который выполняется в данный момент.
string AffairOfHonor_GetCurQuest()
{
	// "Навязчивый кавалер"
	if(CheckAttribute(PChar, "QuestTemp.AffairOfHonor.Cavalier.Started"))
	{
		return "Cavalier";
	}
	
	// "Невольник чести"
	if(CheckAttribute(PChar, "QuestTemp.AffairOfHonor.HonorSlave.Started"))
	{
		return "HonorSlave";
	}
	
	// "Красотка и пират"
	if(CheckAttribute(PChar, "QuestTemp.AffairOfHonor.BeautifulPirate.Started"))
	{
		return "BeautifulPirate";
	}
	
	// "Заносчивый нахал"
	if(CheckAttribute(PChar, "QuestTemp.AffairOfHonor.Jackanapes.Started"))
	{
		return "Jackanapes";
	}
	
	// "Волки и овцы"
	if(CheckAttribute(PChar, "QuestTemp.AffairOfHonor.WolvesAndSheeps.Started"))
	{
		return "WolvesAndSheeps";
	}
	
	// "Трусливый фехтовальщик"
	if(CheckAttribute(PChar, "QuestTemp.AffairOfHonor.CowardFencer.Started"))
	{
		return "CowardFencer";
	}
	
	// "Честь мундира"
	if(CheckAttribute(PChar, "QuestTemp.AffairOfHonor.CoatHonor.Started"))
	{
		return "CoatHonor";
	}
	
	// "Божий суд"
	if(CheckAttribute(PChar, "QuestTemp.AffairOfHonor.GodJudgement.Started"))
	{
		return "GodJudgement";
	}
	
	return "";
}

// Jason: отсрочка на два часа, раз уж в диалоге договорились
void AffairOfHonor_LighthouseGotoMeeting(string _quest)
{
	SetFunctionLocationCondition("AffairOfHonor_LighthouseLocEnter", PChar.QuestTemp.AffairOfHonor.LighthouseId, false);
}

// Функция, вызываемая при заходе в локацию маяка, где должна происходить дуэль.
void AffairOfHonor_LighthouseLocEnter(string _quest)
{
	string modelFirst, modelSecond;
	
	sld = &Locations[FindLocation(PChar.QuestTemp.AffairOfHonor.LighthouseId)];
	DeleteAttribute(sld, "DisableEncounters");
	LAi_LocationFightDisable(sld, true); // Пока-что низя рубиццо.
	
	sld = CharacterFromID("AffairOfHonor_" + AffairOfHonor_GetCurQuest() + "_Man");
	
	switch(AffairOfHonor_GetCurQuest())
	{
		case "Cavalier":
			modelFirst = GetRandQuestSoldierModel(sti(sld.nation));
			modelSecond = GetRandQuestSoldierModel(sti(sld.nation));
		break;
		
		case "HonorSlave":
			modelFirst = "citiz_" + (rand(9) + 41);
			modelSecond = "citiz_" + (rand(9) + 41);
		break;
		
		case "BeautifulPirate":
			modelFirst = "citiz_" + (rand(9) + 41);
			modelSecond = "citiz_" + (rand(9) + 41);
		break;
		
		case "Jackanapes":
			modelFirst = "citiz_" + (rand(9) + 41);
			modelSecond = "citiz_" + (rand(9) + 41);
		break;
		
		case "WolvesAndSheeps":
			modelFirst = "citiz_" + (rand(9) + 41);
			modelSecond = "citiz_" + (rand(9) + 41);
		break;
		
		case "CowardFencer":
			modelFirst = "pirate_" + (rand(9) + 1);
			modelSecond = "pirate_" + (rand(9) + 1);
		break;
		
		case "CoatHonor":
			modelFirst = GetRandQuestSoldierModel(sti(sld.nation));
			modelSecond = GetRandQuestSoldierModel(sti(sld.nation));
		break;
		
		case "GodJudgement":
			modelFirst = "pirate_" + (rand(9) + 1);
			modelSecond = "pirate_" + (rand(9) + 1);
		break;
	}
	
	ChangeCharacterAddressGroup(sld, PChar.QuestTemp.AffairOfHonor.LighthouseId, "goto", "goto20");
	LAi_SetGuardianType(sld);
	sld.protector = true; // Начать диалог.
	sld.Dialog.CurrentNode = "AffairOfHonor_BeforeFight_1";
	LAi_SetImmortal(sld, false);
	LAi_CharacterEnableDialog(sld);
	
	int Rank = sti(pchar.rank)+MOD_SKILL_ENEMY_RATE+5;
	sld = GetCharacter(NPC_GenerateCharacter("AffairOfHonor_Helper_1", modelFirst, "man", "man", Rank, sti(sld.nation), -1, true, "soldier"));
	SetFantomParamFromRank(sld, Rank, true);
	ChangeCharacterAddressGroup(sld, PChar.QuestTemp.AffairOfHonor.LighthouseId, "goto", "goto22");
	LAi_SetActorType(sld);
	LAi_ActorTurnToLocator(sld, "goto", "goto19");
	LAi_SetImmortal(sld, true);
	
	sld = GetCharacter(NPC_GenerateCharacter("AffairOfHonor_Helper_2", modelSecond, "man", "man", sti(PChar.rank) + rand(5), sti(sld.nation), -1, true, "soldier"));
	SetFantomParamFromRank(sld, sti(PChar.rank) + rand(5), true);
	ChangeCharacterAddressGroup(sld, PChar.QuestTemp.AffairOfHonor.LighthouseId, "goto", "goto23");
	LAi_SetActorType(sld);
	LAi_ActorTurnToCharacter(sld, PChar);
	LAi_SetImmortal(sld, true);
	
	DeleteQuestCondition("AffairOfHonor_TimeIsLeft");
	DeleteQuestCondition("AffairOfHonor_TimeIsLeft2");
	
	DisableAllExits(true);
	
	Log_Info("Time to cross blades");
}

// Функция, вызываемая по истечении двух часов с момента взятия квеста.
void AffairOfHonor_TimeIsLeft(string _quest)
{
	int charIndex;
	
	DeleteAttribute(&Locations[FindLocation(PChar.QuestTemp.AffairOfHonor.LighthouseId)], "DisableEncounters");
	LAi_LocationDisableOfficersGen(PChar.QuestTemp.AffairOfHonor.LighthouseId, false);
	DeleteQuestCondition("AffairOfHonor_LighthouseLocEnter");
	
	charIndex = GetCharacterIndex("AffairOfHonor_" + AffairOfHonor_GetCurQuest() + "_Man");
	
	// Вариант истечения времени при живом противнике
	if(charIndex != -1)
	{
		ChangeCharacterAddressGroup(GetCharacter(charIndex), "none", "", "");
		sld = CharacterFromId("AffairOfHonor_QuestMan");
		
		switch(AffairOfHonor_GetCurQuest())
		{
			case "Cavalier":
				LAi_CharacterEnableDialog(sld);
				
				AddQuestRecord("AffairOfHonor", "2_1");
				sld.Dialog.CurrentNode = "AffairOfHonor_Cavalier_6";
				// ChangeCharacterAddressGroup(sld, sld.City + "_church", "quest", "quest3");
			break;
			
			case "HonorSlave":
				LAi_CharacterEnableDialog(sld);
				
				AddQuestRecord("AffairOfHonor", "4_1");
				sld.Dialog.CurrentNode = "AffairOfHonor_HonorSlave_9";
			break;
			
			case "BeautifulPirate":
				ChangeCharacterAddressGroup(sld, "none", "", "");
				
				AddQuestRecord("AffairOfHonor", "6_1");
			break;
			
			case "Jackanapes":
				LAi_CharacterEnableDialog(sld);
				
				AddQuestRecord("AffairOfHonor", "8_1");
				sld.Dialog.CurrentNode = "AffairOfHonor_Jackanapes_2";
			break;
			
			case "WolvesAndSheeps":
				ChangeCharacterAddressGroup(sld, "none", "", "");
				
				AddQuestRecord("AffairOfHonor", "10_1");
			break;
			
			case "CowardFencer":
				LAi_CharacterEnableDialog(sld);
				
				AddQuestRecord("AffairOfHonor", "12_1");
				sld.Dialog.CurrentNode = "AffairOfHonor_CowardFencer_4_1";
			break;
			
			case "CoatHonor":
				ChangeCharacterAddressGroup(sld, "none", "", "");
				
				AddQuestRecord("AffairOfHonor", "14_1");
			break;
			
			case "GodJudgement":
				ChangeCharacterAddressGroup(sld, "none", "", "");
				
				AddQuestRecord("AffairOfHonor", "16_1");
			break;
		}
	}
	
	DeleteAttribute(PChar, "QuestTemp.AffairOfHonor." + AffairOfHonor_GetCurQuest() + ".Started");
	DeleteAttribute(PChar, "QuestTemp.AffairOfHonor.CoatHonor.NeedGenerateDuelMan");
	
	CloseQuestHeader("AffairOfHonor");
	
	Log_TestInfo("Дело чести: время вышло");
}

// Тоже, что и выше. Нужно было просто другое название, чтобы параллельно они могли работать (разное время стоит).
void AffairOfHonor_TimeIsLeft2(string _quest)
{
	// В чем фича:
	// Если делать как
	//
	// DeleteQuestCondition("AffairOfHonor_TimeIsLeft");
	// SetFunctionTimerConditionParam("AffairOfHonor_TimeIsLeft", 0, 0, 0, 3, false);
	//
	// В один момент времени, то выйдет так, что прошлому квесту "AffairOfHonor_TimeIsLeft" присвоится ветка "завершен", но он не удалится,
	// а затем на его место станет новый квест "AffairOfHonor_TimeIsLeft", который автоматом будет с пометкой "завершен". Поэтому вот так сделано.
	
	AffairOfHonor_TimeIsLeft(_quest);
}

// Функция, вызываемая при убийстве персонажа, с которым дуэлимся.
void AffairOfHonor_KillChar(string _quest)
{
	switch(AffairOfHonor_GetCurQuest())
	{
		case "Cavalier":
			AddQuestRecord("AffairOfHonor", "2");
		break;
		
		case "HonorSlave":
			AddQuestRecord("AffairOfHonor", "4");
		break;
		
		case "BeautifulPirate":
			AddQuestRecord("AffairOfHonor", "6");
		break;
		
		case "Jackanapes":
			AddQuestRecord("AffairOfHonor", "8");
		break;
		
		case "WolvesAndSheeps":
			AddQuestRecord("AffairOfHonor", "10");
		break;
		
		case "CowardFencer":
			AddQuestRecord("AffairOfHonor", "12");
			
			PChar.QuestTemp.AffairOfHonor.CowardFencer.CanTraderTalk = true;
		break;
		
		case "CoatHonor":
			AddQuestRecord("AffairOfHonor", "14");
		break;
		
		case "GodJudgement":
			AddQuestRecord("AffairOfHonor", "16");
		break;
	}
	
	CloseQuestHeader("AffairOfHonor");
	
	SetFunctionTimerCondition("AffairOfHonor_DayAfterDuel", 0, 0, 1, false);
	
	sld = CharacterFromID("AffairOfHonor_Helper_1");
	sld.Dialog.filename = "Quest\ForAll_dialog.c";
	sld.Dialog.CurrentNode = "AffairOfHonor_AfterFight_1";
	LAi_ActorDialog(sld, PChar, "", -1, 5);
	
	PChar.QuestTemp.AffairOfHonor.FinishCount = sti(PChar.QuestTemp.AffairOfHonor.FinishCount) + 1;
	
	DisableAllExits(false);
	
	SetFunctionExitFromLocationCondition("AffairOfHonor_LocExitAfterFight", PChar.location, false);
}

// Функция, вызываемая по истечении одного дня с момента дуэли.
void AffairOfHonor_DayAfterDuel(string quest)
{
	DeleteAttribute(PChar, "QuestTemp.AffairOfHonor.CowardFencer.CanTraderTalk");
}

// Функция, вызываемая при выходе из локации после дуэли.
void AffairOfHonor_LocExitAfterFight(string _quest)
{
	sld = CharacterFromId("AffairOfHonor_QuestMan");
	LAi_SetFightMode(PChar, false);
	
	DeleteAttribute(sld, "CityType");
	
	if(!CheckAttribute(PChar, "QuestTemp.AffairOfHonor.FightWithHelpers"))
	{
		ChangeCharacterAddressGroup(CharacterFromID("AffairOfHonor_Helper_1"), "none", "", "");
		ChangeCharacterAddressGroup(CharacterFromID("AffairOfHonor_Helper_2"), "none", "", "");
	}
	
	switch(AffairOfHonor_GetCurQuest())
	{
		case "Cavalier":
			LAi_CharacterEnableDialog(sld);
			sld.Dialog.CurrentNode = "AffairOfHonor_Cavalier_5";
			// ChangeCharacterAddressGroup(sld, sld.City + "_church", "quest", "quest3");
		break;
		
		case "HonorSlave":
			LAi_CharacterEnableDialog(sld);
			sld.Dialog.CurrentNode = "AffairOfHonor_HonorSlave_7";
		break;
		
		case "WolvesAndSheeps":
			LAi_CharacterEnableDialog(sld);
			sld.Dialog.CurrentNode = "AffairOfHonor_WolvesAndSheeps_12";
			// ChangeCharacterAddressGroup(sld, sld.City + "_church", "quest", "quest3");
		break;
		
		case "CowardFencer":
			LAi_CharacterEnableDialog(sld);
			sld.Dialog.CurrentNode = "AffairOfHonor_CowardFencer_5";
			// ChangeCharacterAddressGroup(sld, sld.City + "_church", "quest", "quest3");
		break;
		
		case "GodJudgement":
			LAi_CharacterEnableDialog(sld);
			sld.Dialog.CurrentNode = "AffairOfHonor_GodJudgement_2";
			// ChangeCharacterAddressGroup(sld, sld.City + "_church", "quest", "quest3");
		break;
		
		case "CoatHonor":
			sld.Dialog.CurrentNode = "AffairOfHonor_CoatHonor_Final";
		break;
		
		case "BeautifulPirate":
			LAi_CharacterEnableDialog(sld);
			sld.Dialog.CurrentNode = "AffairOfHonor_BeautifulPirate_5";
		break;
		
		case "Jackanapes":
			ChangeCharacterComplexReputation(pchar, "authority", 1);
			ChangeOfficersLoyality("good_all", 1);
			AddComplexSelfExpToScill(50, 50, 50, 50);
			AddCharacterExpToSkill(pchar, "Fortune", 150);
		break;
	}
	LAi_LocationDisableOfficersGen(PChar.QuestTemp.AffairOfHonor.LighthouseId, false);
	DeleteAttribute(PChar, "QuestTemp.AffairOfHonor." + AffairOfHonor_GetCurQuest() + ".Started");
}

// Функция, вызываемая при выходе из интерфекса карт, когда играем с челом по квесту "волки и овцы".
void AffairOfHonor_AfterCards(string _quest)
{
	sld = characterFromID("AffairOfHonor_WolvesAndSheeps_Man");
	
	LAi_SetSitType(PChar);
	LAi_SetActorType(sld);
	LAi_ActorSetSitMode(sld);
	LAi_ActorDialogNow(sld, PChar, "", -1);
}
//=====================================================================================================================================
// <-- Серия миниквестов "Дело чести".
//=====================================================================================================================================
