extern void StoreInit();

void InitStores()
{
    int i;

    for(i=0; i<STORE_QUANTITY; i++)
    {
		stores[i].index = i;
        StoreVoidFill(&stores[i]);
    }

	if(LoadSegment("store\store_init.c"))
	{
		StoreInit();
		UnloadSegment("store\store_init.c");
	}

   for(i=0; i<STORE_QUANTITY; i++)
   {
       FillStoreGoods(&stores[i]);
   }
}

void SetStoresTradeType(int StoreNum,int GoodsNum,int TradeType)
{
	string tmpstr = Goods[GoodsNum].Name;
	Stores[StoreNum].Goods.(tmpstr).TradeType = TradeType;
}

void FillStoreGoods(ref pRef)
{
	int 	i,j,nq,n,tt;
	string 	goodName;
	string 	goodType;
	float 	RndPriceModify;
	float 	RndPriceModifySign = -1.0;

	int iColony 	= FindColony(pRef.Colony); 		// город магазина

	aref arTypes, arCurType;
	if (iColony != -1)
	{
		ref rColony = GetColonyByIndex(iColony);
		int islandIdx 	= FindIsland(rColony.island); 	// остров города
		if (islandIdx!=-1)
		{
			ref rIsland = GetIslandByIndex(islandIdx);
			if(CheckAttribute(rIsland,"RndPriceModify")) 
			{
				RndPriceModify = stf(rIsland.RndPriceModify);
				if(CheckAttribute(rIsland,"RndPriceModifySign")) RndPriceModifySign = stf(rIsland.RndPriceModifySign);
			}	
			else
			{	
				RndPriceModify = frnd() * 0.15;
				rIsland.RndPriceModify = RndPriceModify;
			
				if(sti(rColony.ismaincolony) == 1 || 
				   sti(rColony.nation) == PIRATE) RndPriceModifySign = 1.0;
				rIsland.RndPriceModifySign = RndPriceModifySign;
			}
			makearef(arTypes, rIsland.Trade); // вся инфа как и в ПКМ по островам
			nq = GetAttributesNum(arTypes);
			for(i=0; i<nq; i++)
			{
				arCurType = GetAttributeN(arTypes,i);
				tt = T_TYPE_NORMAL;
				switch(GetAttributeName(arCurType))
				{
					case "Export":		tt=T_TYPE_EXPORT;		break; // экспортные товары
					case "Import":		tt=T_TYPE_IMPORT;		break; // импортные товары
					case "Aggressive":	tt=T_TYPE_AGGRESSIVE;	break; // товары агрессивного спроса
					case "Contraband":	tt=T_TYPE_CONTRABAND;	break; // контрабанда
				}
				n = GetAttributesNum(arCurType);
				for(j=0; j<n; j++)
				{
					goodName = Goods[sti(GetAttributeValue(GetAttributeN(arCurType,j)))].name;
					pRef.Goods.(goodName).TradeType = tt;
					pRef.Goods.(goodName).Type = Goods[sti(GetAttributeValue(GetAttributeN(arCurType,j)))].type;
				}
			}			
		}		
		else
		{		
			trace("Mistake island id into store:  id="+rColony.island);
		}	
	}
	else
	{
		trace("Mistake Colony id into store:  id=" + pRef.Colony);
	}
	
	for (i=0; i<GOODS_QUANTITY; i++)
	{
	   	goodName = Goods[i].Name;
	   	// boal 22.01.2004 -->
		switch(sti(pRef.Goods.(goodName).TradeType))
		{
			case T_TYPE_NORMAL:
			    pRef.Goods.(goodName).Quantity = sti(sti(Goods[i].Norm)*0.75 + rand(sti(sti(Goods[i].Norm)*0.1)));
				pRef.Goods.(goodName).RndPriceModify = RndPriceModify * RndPriceModifySign;
				break;

			case T_TYPE_EXPORT:
			    pRef.Goods.(goodName).Quantity = sti(sti(Goods[i].Norm)*0.9 + rand(sti(sti(Goods[i].Norm)*0.2))); 
				pRef.Goods.(goodName).RndPriceModify = RndPriceModify * RndPriceModifySign;
				break;

			case T_TYPE_IMPORT:
			    pRef.Goods.(goodName).Quantity = sti(sti(Goods[i].Norm)*0.4 + rand(sti(sti(Goods[i].Norm)*0.05)));
				pRef.Goods.(goodName).RndPriceModify = RndPriceModify * RndPriceModifySign; 
				break;
				
			case T_TYPE_AGGRESSIVE:
				pRef.Goods.(goodName).Quantity = sti(sti(Goods[i].Norm)*0.1 + rand(sti(sti(Goods[i].Norm)*0.05)));
				pRef.Goods.(goodName).RndPriceModify = RndPriceModify * RndPriceModifySign;
				break;	

			case T_TYPE_CONTRABAND:
			    pRef.Goods.(goodName).Quantity = sti(sti(Goods[i].Norm)*0.1 + rand(sti(sti(Goods[i].Norm)*0.05)));
				pRef.Goods.(goodName).RndPriceModify = RndPriceModify * RndPriceModifySign;
				break;
				
			case T_TYPE_AMMUNITION:  //делаю все тоже, что и для нормального товара, а тип нужен, чтоб на корабле не скупали лишнее.				
				pRef.Goods.(goodName).Quantity = sti(sti(Goods[i].Norm)*0.75 + rand(sti(sti(Goods[i].Norm)*0.1)));				
				pRef.Goods.(goodName).RndPriceModify = RndPriceModify * RndPriceModifySign;
				break;
				
			case T_TYPE_CANNONS: 
				if(sti(Goods[i].NotSale) == 1) // 1.2.5 --> старшие калибры не продаем !!!
				{
					pRef.Goods.(goodName).Quantity = 0;
				}
				else
				{
					pRef.Goods.(goodName).Quantity = sti(sti(Goods[i].Norm)*0.4 + rand(sti(sti(Goods[i].Norm)*0.4)));
				}	
				pRef.Goods.(goodName).RndPriceModify = (frnd() * 0.03 + RndPriceModify + 0.10) * RndPriceModifySign; 
				pRef.Goods.(goodName).canbecontraband = CONTRA_SELL;			// все орудия можем продавать контрабандистам !!
				break;	
		}

		// ?????? ????? ????????
		if (pRef.StoreSize == "medium")
		{
		    pRef.Goods.(goodName).Quantity = makeint(sti(pRef.Goods.(goodName).Quantity) * stf(Goods[i].MediumNorm)); 
		}
		if (pRef.StoreSize == "small")
		{
		    pRef.Goods.(goodName).Quantity = makeint(sti(pRef.Goods.(goodName).Quantity) * stf(Goods[i].SmallNorm)); 
		}
		// 24/01/08
		pRef.Goods.(goodName).Norm            = pRef.Goods.(goodName).Quantity; 		// колво в начале, это норма магазина навсегда
		pRef.Goods.(goodName).NormPriceModify = pRef.Goods.(goodName).RndPriceModify; 	// начальная цена - тоже limit стремлений
		pRef.Goods.(goodName).AddPriceModify  = 1.0;
		
//		trace("FillStoreGoods    colony : " + pRef.Colony + " good : " + goodName + " RndPriceModify : " + pRef.Goods.(goodName).RndPriceModify);
	}
	UpdateStore(pRef);
}

void StoreVoidFill(ref pRef)
{
	string goodName;
	pRef.Island = "";
	for(int i = 0; i < GOODS_QUANTITY; i++)
	{
		goodName = Goods[i].Name;
		if (CheckAttribute(&Goods[i], "trade_type"))
		{
		    pRef.Goods.(goodName).TradeType = Goods[i].trade_type;
		}
		else
		{ // boal fix <--
			pRef.Goods.(goodName).TradeType = T_TYPE_NORMAL;
		}
		
		if (CheckAttribute(&Goods[i], "type"))
		{
		    pRef.Goods.(goodName).Type = Goods[i].type;
		}
		else
		{ // boal fix <--
			pRef.Goods.(goodName).Type = T_TYPE_NORMAL;
		}
		
		pRef.Goods.(goodName).NotUsed 			= false;
		pRef.Goods.(goodName).Quantity 			= 0;
		pRef.Goods.(goodName).canbecontraband 	= 0;
	}
}