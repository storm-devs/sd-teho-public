#include "cannons\cannons.h"

extern void InitCannons();

void CannonsInit()
{
	if(LoadSegment("cannons\cannons_init.c"))
	{
		InitCannons();
		UnloadSegment("cannons\cannons_init.c");
	}

	SetEventHandler(GET_CANNON_BY_TYPE_EVENT,"CannonGetByTypeEvent",0);
}

aref CannonGetByTypeEvent()
{
	int iCannonType = GetEventData();
	return &Cannon[iCannonType];
}

int GetCannonByTypeAndCaliber(string sCannonType, int iCaliber)
{
	switch (sCannonType)
	{
		case "cannon":
			switch (iCaliber)
			{									
                case 3:
					return CANNON_TYPE_CANNON_LBS3;
				break;
				case 6:
					return CANNON_TYPE_CANNON_LBS6;
				break;
				case 8:
					return CANNON_TYPE_CANNON_LBS6; 
                break;				
				case 12:
					return CANNON_TYPE_CANNON_LBS12;
				break;
				case 16:
					return CANNON_TYPE_CANNON_LBS16;
				break;
				case 18:
					return CANNON_TYPE_CANNON_LBS16;
				break;
				case 20:
					return CANNON_TYPE_CANNON_LBS20;
				break;
				case 24:
					return CANNON_TYPE_CANNON_LBS24;
				break;
				case 32:
					return CANNON_TYPE_CANNON_LBS32;
				break;
				case 36:
					return CANNON_TYPE_CANNON_LBS36;
				break;
				case 42:
					return CANNON_TYPE_CANNON_LBS42;
				break;
				case 48:
					return CANNON_TYPE_CANNON_LBS48;
				break;
			}
		break;
		case "culverine":
			switch (iCaliber)
			{
				case 3:
					return CANNON_TYPE_CANNON_LBS3;
				break;
				case 6:
					return CANNON_TYPE_CANNON_LBS6;
				break;			
                case 8:
					return CANNON_TYPE_CULVERINE_LBS8;
				break;
				case 12:
					return CANNON_TYPE_CULVERINE_LBS8;
				break;
				case 16:
					return CANNON_TYPE_CULVERINE_LBS8;
				break;
				case 18:
					return CANNON_TYPE_CULVERINE_LBS18;
				break;
				case 20:
					return CANNON_TYPE_CULVERINE_LBS18;
				break;
				case 24:
					return CANNON_TYPE_CULVERINE_LBS18;
				break;
				case 32:
					return CANNON_TYPE_CULVERINE_LBS18;
				break;
				case 36:
					return CANNON_TYPE_CULVERINE_LBS36;
				break;
			}
		break;
	}

	return CANNON_TYPE_NONECANNON;
}

int FindCannonByText(string sId)
{
	for(int i = 0; i < CANNON_TYPES_QUANTITY; i++)
	{
		if(Cannon[i].picture == sId)
		{
			return i;
		}
	}
	return -1;
}

string GetCannonType(int iCannon)
{
	if (iCannon != CANNON_TYPE_NONECANNON) //fix
	{
		int iCannonType = sti(Cannon[iCannon].type);

		switch(iCannonType)
		{
			case CANNON_NAME_CULVERINE:
				return "Culverine";
			break;
			case CANNON_NAME_CANNON:
				return "Cannon";
			break;
		}
	}
	return "NoneCannon";
}

// boal 09/02/05
float GetCannonReloadTime(ref rCannon)
{
	if (!iArcadeSails)
	{
	    return  stf(rCannon.ReloadTime) * 3;
	}
	else
	{
	    return  stf(rCannon.ReloadTime);
	}
}

int GetCannonGoodsIdxByType(int iCannon)
{
	int i;
	
	for (i = 0; i< GOODS_QUANTITY; i++)
	{
		if (CheckAttribute(&Goods[i], "CannonIdx"))
		{
			if (sti(Goods[i].CannonIdx) == iCannon) return i;
		}
	}
	return -1;	
}