//ugeen 12.01.10 --> отдельный файл для функций, общих для всех генераторов
string GenQuest_GenerateGoodBlade() // генерация хороших клинков для призов и подарков
{	
	//return GetGeneratedItem(SelectGeneratedItem("", B_GOOD , ""));
	// Jason: вот место, по которому генерировались квестовые клинки в кладах!! 
	// будет выбор вручную. 020912
	string itemID;
	switch(rand(6))
	{
		case 0:
			itemID = GetGeneratedItem("blade_04"); 
		break;
		case 1:
			itemID = GetGeneratedItem("blade_06"); 
		break;
		case 2:
			itemID = GetGeneratedItem("blade_10"); 
		break;
		case 3:
			itemID = GetGeneratedItem("blade_13"); 
		break;
		case 4:
			itemID = GetGeneratedItem("blade_15"); 
		break;
		case 5:
			itemID = GetGeneratedItem("blade_16"); 
		break;
	}	
	return itemID;
}

string GenQuest_GenerateBestBlade() // генерация отличных клинков для призов и подарков
{
	string itemID;
	switch(rand(5)) // Jason: и тут квестовые клинки... убрал. 020912
	{
		case 0:
			itemID = GetGeneratedItem("blade_17"); 
		break;
		case 1:
			itemID = GetGeneratedItem("blade_18"); 
		break;
		case 2:
			itemID = GetGeneratedItem("blade_19"); 
		break;
		case 3:
			itemID = GetGeneratedItem("blade_20"); 
		break;
		case 4:
			itemID = GetGeneratedItem("blade_21"); 
		break;		
	}	
	return itemID;
}

string GenQuest_GenerateArtefact() // артефакты
{
	string itemID;
	switch(rand(21))
	{
		case 0:
			itemID = "indian_1";
		break;
		case 1:
			itemID = "indian_2"; 
		break;
		case 2:
			itemID = "indian_3"; 
		break;
		case 3:
			itemID = "indian_4"; 
		break;
		case 4:
			itemID = "indian_5"; 
		break;
		case 5:
			itemID = "indian_6"; 
		break;
		case 6:
			itemID = "indian_7"; 
		break;
		case 7:
			itemID = "indian_8"; 
		break;
		case 8:
			itemID = "indian_9"; 
		break;
		case 9:
			itemID = "indian_10"; 
		break;
		case 10:
			itemID = "indian_11"; 
		break;
		case 11:
			itemID = "amulet_1"; 
		break;
		case 12:
			itemID = "amulet_2"; 
		break;
		case 13:
			itemID = "amulet_3"; 
		break;
		case 14:
			itemID = "amulet_4"; 
		break;
		case 15:
			itemID = "amulet_5"; 
		break;		
		case 16:
			itemID = "amulet_6"; 
		break;	
		case 17:
			itemID = "amulet_7"; 
		break;			
		case 18:
			itemID = "amulet_8"; 
		break;
		case 19:
			itemID = "amulet_9"; 
		break;		
		case 20:
			itemID = "amulet_10"; 
		break;	
		case 21:
			itemID = "amulet_11"; 
		break;			
	}
	return itemID;
}

string GenQuest_GeneratePrize() // клинок или артефакт
{
	string itm;
	
	if(rand(12) > 4) itm = GenQuest_GenerateArtefact();
	else
	{
		if (sti(pchar.rank) > 15) itm = GenQuest_GenerateBestBlade(); // Addon 2016 Jason
		else itm = GenQuest_GenerateGoodBlade();
	}
	return itm;
}

string GenQuestCommon_GenerateItem()
{
	string itm;
	if(rand(1) == 0) itm = GenQuest_GeneratePrize();
	else
	{
		if(rand(1) == 0 )
		{
			if (GetCharacterItem(pchar, "map_full") == 0) 
			{
				if (GetCharacterItem(pchar, "map_part1") == 0) { itm = "map_part1"; }
				else
				{
					if (GetCharacterItem(pchar, "map_part2") == 0) { itm = "map_part2"; }
					else itm = GenQuest_GenerateGoodBlade();
				}
			} 					
		}
		else itm = GenQuest_GenerateGoodBlade();
	}
	return itm;
}

string GenQuest_GetQuestTreasureMapDescription(ref itmRef) // надпись на квестовой карте
{
	string MapDescription;
	int i;

	i = FindLocation(itmRef.MapLocId);  // ищем ареал
	if (i != -1 && locations[i].islandId != "Mein")
	{
		string MapLocation = GetConvertStr(locations[i].islandId, "LocLables.txt");
		MapDescription = GetConvertStr("type_quest_0_isl", "MapDescribe.txt") + " " + MapLocation;
	}
	else
	{
		MapDescription = GetConvertStr("type_quest_0_mein", "MapDescribe.txt");
	}
	itmRef.MapIslName = MapDescription;
	
	MapDescription = GetConvertStr(itmRef.MapLocId, "MapDescribe.txt") + ", " + GetConvertStr(itmRef.MapLocId + "_" + itmRef.MapBoxId, "MapDescribe.txt");
	itmRef.MaplocName = MapDescription;

	MapDescription = itmRef.MapOwnId;
	itmRef.MapOwner = MapDescription;	
		
	MapDescription = GetConvertStr("type_quest_0", "MapDescribe.txt");
	MapDescription = GetAssembledString(MapDescription, itmRef);
	
	itmRef.MapDescription = MapDescription; 
	return MapDescription;   	
}