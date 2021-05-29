
extern void InitColonies();

void ColoniesInit()
{
	if(LoadSegment("Colonies\Colonies_init.c"))
	{
		InitColonies();
		UnloadSegment("Colonies\Colonies_init.c");
	}
}
 
int FindColony(string sColony)
{
	for (int i=0; i<MAX_COLONIES; i++)
	{
		if(Colonies[i].id == sColony)
		{
			return i;
		}
	}
	
	return -1;
}

ref GetColonyByIndex(int iColony);
{
	return &Colonies[iColony];
}

// Warship -->
ref GetColonyRefByID(string sColony)
{
	return GetColonyByIndex(FindColony(sColony));
}

int GetDistanceToColony2D(string _sColony) // Дистанция до колонии
{
	ref rColony = GetColonyRefByID(_sColony);
	string sColonyIslandID = rColony.Island;
	string sColonyTown = _sColony + "_town";

	if(_sColony == "FortOrange") sColonyTown = "Shore36";
	if(_sColony == "LaVega") sColonyTown = "LaVega_Port";
	
//	float X1 = makefloat(worldMap.playerShipX)+1000;
//	float Z1 = -makefloat(worldMap.playerShipZ)+980;
        float X1, Z1;
	if(IsEntity(&worldMap))
	{
		X1 =  stf(worldMap.playerShipX);
		Z1 = -stf(worldMap.playerShipZ);
	}
	else
	{
		X1 =  GetSeaShipX(stf(pchar.Ship.Pos.X))+1000;
		Z1 = -GetSeaShipZ(stf(pchar.Ship.Pos.Z))+1000;
	}
	float X2 = makefloat(worldMap.islands.(sColonyIslandID).(sColonyTown).position.x)+1000;
	float Z2 = -makefloat(worldMap.islands.(sColonyIslandID).(sColonyTown).position.z)+1000;
	
	return makeint(GetDistance2D(X1, Z1, X2, Z2));
}

// Jason: функция возвращает id маяка на текущем острове. Работает только в городских локациях.
string Colony_GetLighthouseId(string _colony) 
{
	string sMayak;
	int imay;
	int iColony = FindColony(_colony);
	ref rCol = &Colonies[iColony];
	if(CheckAttribute(rCol, "mayak"))
	{
		imay = sti(rCol.mayak);
		sMayak = "mayak"+imay;
		log_Testinfo(sMayak);
	}
	else
	{
		log_Testinfo("Lighthouse not found");
		sMayak = "";
	}
	return sMayak;
}
// <--