#define GOODS_QUANTITY  	47
// порядок не менять !!! порядок важен для AI фантомов ! <-- ugeen

// боеприпасы
#define GOOD_BALLS	    	0
#define GOOD_GRAPES	    	1
#define GOOD_KNIPPELS		2
#define GOOD_BOMBS	    	3

// товары повседневного спроса
#define GOOD_FOOD       	4
#define GOOD_SAILCLOTH  	5
#define GOOD_PLANKS     	6
#define GOOD_BRICK      	7
#define GOOD_WHEAT      	8
#define GOOD_CLOTHES		9
#define GOOD_FRUITS     	10

// колониальные (экспортные) товары
#define GOOD_COFFEE	    	11
#define GOOD_CHOCOLATE		12
#define GOOD_TOBACCO		13
#define GOOD_SUGAR	    	14
#define GOOD_COTTON	    	15
#define GOOD_LEATHER		16
#define GOOD_EBONY      	17
#define GOOD_MAHOGANY 		18
#define GOOD_CINNAMON   	19
#define GOOD_COPRA      	20
#define GOOD_PAPRIKA    	21

// привозные товары из Европы
#define GOOD_POWDER     	22
#define GOOD_WEAPON	    	23
#define GOOD_MEDICAMENT 	24
#define GOOD_WINE	    	25
#define GOOD_RUM	    	26
#define GOOD_ALE	    	27

// уникальные товары
#define GOOD_SHIPSILK	    28
#define GOOD_ROPES	    	29
#define GOOD_SANDAL	    	30
#define GOOD_OIL        	31

// коронные товары
#define GOOD_SLAVES     	32
#define GOOD_GOLD       	33
#define GOOD_SILVER	    	34

//   орудия
#define GOOD_CANNON_3    	35
#define GOOD_CANNON_6    	36
#define GOOD_CANNON_12   	37
#define GOOD_CANNON_16   	38
#define GOOD_CANNON_20   	39
#define GOOD_CANNON_24   	40
#define GOOD_CANNON_32   	41
#define GOOD_CANNON_36   	42
#define GOOD_CANNON_42   	43

#define GOOD_CULVERINE_8  	44
#define GOOD_CULVERINE_18 	45
#define GOOD_CULVERINE_36 	46

object  Goods[GOODS_QUANTITY];

ref GetGoodByType(int iGoodType)
{
	return &Goods[iGoodType];
}

int FindGood(string sGood)
{
	for (int i=0; i<GOODS_QUANTITY; i++) 
	{ 
		if (Goods[i].Name == sGood) return i; 
	}
	return -1;
}

ref GetGoodByID(string sGood)
{
	for (int i=0; i<GOODS_QUANTITY; i++) 
	{ 
		if (Goods[i].Name == sGood) 
		{
			return &Goods[i];
		}
	}
	trace("WARNING! Goods ID (" + sGood +") not found!");
}

int GetGoodWeightByType(int iGoodType,int quantity)
{
	int unitSize = sti(Goods[iGoodType].Units);
	int unitQuantity = (quantity+unitSize-1)/unitSize;
	int weight = makeint(unitQuantity*stf(Goods[iGoodType].Weight) + 0.05);
	return weight;
}

int GetGoodQuantityByWeight(int iGoodType,int weight)
{
	int unitSize = sti(Goods[iGoodType].Units);
	int uqnt = makeint( weight / stf(Goods[iGoodType].Weight) );
	return unitSize*uqnt;
}