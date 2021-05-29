#define NET_CANNON_TYPES_QUANTITY		11

#define NET_CANNON_TYPE_CANNON_LBS3	    0
#define NET_CANNON_TYPE_CANNON_LBS6	    1
#define NET_CANNON_TYPE_CANNON_LBS12    2
#define NET_CANNON_TYPE_CANNON_LBS16    3
#define NET_CANNON_TYPE_CANNON_LBS20    4
#define NET_CANNON_TYPE_CANNON_LBS24    5
#define NET_CANNON_TYPE_CANNON_LBS32    6
#define NET_CANNON_TYPE_CANNON_LBS36	7

#define NET_CANNON_TYPE_CULVERINE_LBS8	8
#define NET_CANNON_TYPE_CULVERINE_LBS18 9
#define NET_CANNON_TYPE_CULVERINE_LBS36 10

#define NET_CANNON_TYPE_NONECANNON		1000

#define NET_CANNON_NAME_CANNON              1
#define NET_CANNON_NAME_CULVERINE           2
#define NET_CANNON_NAME_SPECIAL_CANNON		3

object NetCannons[NET_CANNON_TYPES_QUANTITY];
//object  Cannon[CANNON_TYPES_QUANTITY];

ref Net_GetCannonByType(int iCannonType) 
{ 
	if (iCannonType == NET_CANNON_TYPE_NONECANNON) return &NullCharacter; // fix
	return &NetCannons[iCannonType]; 
}

int Net_GetCannonCaliber(int nCannon)
{
    switch(nCannon)
    {
		case NET_CANNON_TYPE_NONECANNON:
			return 0;
        break;
		case NET_CANNON_TYPE_CANNON_LBS3:
			return 3;
		break;
		case NET_CANNON_TYPE_CANNON_LBS6:
			return 6;
		break;
		case NET_CANNON_TYPE_CULVERINE_LBS8:
			return 8;
        break;
		case NET_CANNON_TYPE_CANNON_LBS12:
			return 12;
        break;
		case NET_CANNON_TYPE_CANNON_LBS16:
			return 16;
        break;
		case NET_CANNON_TYPE_CULVERINE_LBS18:
			return 18;
        break;
		case NET_CANNON_TYPE_CANNON_LBS20:
			return 20;
        break;		
		case NET_CANNON_TYPE_CANNON_LBS24:
			return 24;
        break;
		case NET_CANNON_TYPE_CANNON_LBS32:
			return 32;
        break;	
		case NET_CANNON_TYPE_CANNON_LBS36:
			return 36;
        break;  		
		case NET_CANNON_TYPE_CULVERINE_LBS36:
			return 36;
        break;		
    }
}