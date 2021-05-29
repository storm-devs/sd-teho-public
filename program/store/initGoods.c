void InitGoods()
{
	int i;
	
	// боеприпасы
	Goods[GOOD_BALLS].Name					= "Balls";
	Goods[GOOD_BALLS].Cost					= 40;
	Goods[GOOD_BALLS].Weight				= 2;
	Goods[GOOD_BALLS].Units					= 20;
	Goods[GOOD_BALLS].SpeedV0				= 1.0;
	Goods[GOOD_BALLS].DamageHull			= 8.0;
	Goods[GOOD_BALLS].DamageRig				= 0.5;
	Goods[GOOD_BALLS].DamageCrew			= 0.2;
	Goods[GOOD_BALLS].AfraidWater 			= 0;    // рудимент от к3
	Goods[GOOD_BALLS].DontDrop				= 1;	
	Goods[GOOD_BALLS].type					= T_TYPE_AMMUNITION;
	Goods[GOOD_BALLS].trade_type			= T_TYPE_AMMUNITION;
	Goods[GOOD_BALLS].Norm					= 600;
	Goods[GOOD_BALLS].MediumNorm			= 1.0;
	Goods[GOOD_BALLS].SmallNorm				= 0.5;
	
	Goods[GOOD_GRAPES].Name					= "Grapes";
	Goods[GOOD_GRAPES].Cost					= 20;
	Goods[GOOD_GRAPES].Weight				= 1;
	Goods[GOOD_GRAPES].Units				= 20;
	Goods[GOOD_GRAPES].SpeedV0				= 0.6; // boal
	Goods[GOOD_GRAPES].DamageHull			= 1.0;
	Goods[GOOD_GRAPES].DamageRig			= 2.0;
	Goods[GOOD_GRAPES].DamageCrew			= 1.5;
	Goods[GOOD_GRAPES].AfraidWater			= 0;
	Goods[GOOD_GRAPES].DontDrop				= 1;	
	Goods[GOOD_GRAPES].type					= T_TYPE_AMMUNITION;
	Goods[GOOD_GRAPES].trade_type			= T_TYPE_AMMUNITION;
	Goods[GOOD_GRAPES].Norm					= 600;
	Goods[GOOD_GRAPES].MediumNorm			= 1.0;
	Goods[GOOD_GRAPES].SmallNorm				= 0.5;
	
	Goods[GOOD_KNIPPELS].Name				= "Knippels";
	Goods[GOOD_KNIPPELS].Cost				= 40;
	Goods[GOOD_KNIPPELS].Weight				= 2;
	Goods[GOOD_KNIPPELS].Units				= 20;
	Goods[GOOD_KNIPPELS].SpeedV0			= 0.9;
	Goods[GOOD_KNIPPELS].DamageHull 		= 1.5;
	Goods[GOOD_KNIPPELS].DamageRig			= 9.0;
	Goods[GOOD_KNIPPELS].DamageCrew 		= 0.3;
	Goods[GOOD_KNIPPELS].AfraidWater 		= 0;
	Goods[GOOD_KNIPPELS].DontDrop			= 1;	
	Goods[GOOD_KNIPPELS].type				= T_TYPE_AMMUNITION;
	Goods[GOOD_KNIPPELS].trade_type			= T_TYPE_AMMUNITION;
	Goods[GOOD_KNIPPELS].Norm				= 600;
	Goods[GOOD_KNIPPELS].MediumNorm			= 1.0;
	Goods[GOOD_KNIPPELS].SmallNorm				= 0.5;
	
	Goods[GOOD_BOMBS].Name					= "Bombs";
	Goods[GOOD_BOMBS].Cost					= 60;
	Goods[GOOD_BOMBS].Weight				= 3;
	Goods[GOOD_BOMBS].Units					= 20;
	Goods[GOOD_BOMBS].SpeedV0				= 0.8;
	Goods[GOOD_BOMBS].DamageHull			= 15.0;
	Goods[GOOD_BOMBS].DamageRig				= 1.0;
	Goods[GOOD_BOMBS].DamageCrew			= 0.5;
	Goods[GOOD_BOMBS].AfraidWater 			= 0;
	Goods[GOOD_BOMBS].DontDrop				= 1;	
	Goods[GOOD_BOMBS].type					= T_TYPE_AMMUNITION;
	Goods[GOOD_BOMBS].trade_type			= T_TYPE_AMMUNITION;
	Goods[GOOD_BOMBS].Norm					= 600;
	Goods[GOOD_BOMBS].MediumNorm			= 1.0;
	Goods[GOOD_BOMBS].SmallNorm				= 0.5;	

	// товары повседневного спроса	
	Goods[GOOD_FOOD].Name		    		= "Food";
	Goods[GOOD_FOOD].Weight	        		= 1;
	Goods[GOOD_FOOD].Cost	        		= 20;
	Goods[GOOD_FOOD].Units	        		= 10;
	Goods[GOOD_FOOD].Swim.Model	    		= "barrel";
	Goods[GOOD_FOOD].Swim.Time	    		= 45;
	Goods[GOOD_FOOD].AfraidWater 			= 1;
	Goods[GOOD_FOOD].DontDrop				= 1;	
	Goods[GOOD_FOOD].trade_type				= T_TYPE_AMMUNITION;
	Goods[GOOD_FOOD].type					= T_TYPE_NORMAL;
	Goods[GOOD_FOOD].Norm          			= 1200;
	Goods[GOOD_FOOD].MediumNorm			= 0.5;
	Goods[GOOD_FOOD].SmallNorm				= 0.5;	
		
	Goods[GOOD_SAILCLOTH].Name				= "Sailcloth";
	Goods[GOOD_SAILCLOTH].Weight			= 2;
	Goods[GOOD_SAILCLOTH].Cost				= 40;
	Goods[GOOD_SAILCLOTH].Units				= 1;
	Goods[GOOD_SAILCLOTH].Swim.Model		= "roll_of_materials";
	Goods[GOOD_SAILCLOTH].Swim.Time			= 45;
	Goods[GOOD_SAILCLOTH].AfraidWater 		= 0;
	Goods[GOOD_SAILCLOTH].trade_type		= T_TYPE_AMMUNITION;
	Goods[GOOD_SAILCLOTH].type				= T_TYPE_NORMAL;
	Goods[GOOD_SAILCLOTH].Norm				= 1200;
	Goods[GOOD_SAILCLOTH].MediumNorm			= 0.5;
	Goods[GOOD_SAILCLOTH].SmallNorm				= 0.5;	

	Goods[GOOD_PLANKS].Name		    		= "Planks";
	Goods[GOOD_PLANKS].Weight	    		= 3;
	Goods[GOOD_PLANKS].Cost		    		= 60;
	Goods[GOOD_PLANKS].Units	    		= 1;
	Goods[GOOD_PLANKS].Swim.Model			= "roll_of_planks";
	Goods[GOOD_PLANKS].Swim.Time			= 45; 
	Goods[GOOD_PLANKS].AfraidWater 			= 0;
	Goods[GOOD_PLANKS].trade_type			= T_TYPE_AMMUNITION;
	Goods[GOOD_PLANKS].type					= T_TYPE_NORMAL;
	Goods[GOOD_PLANKS].Norm          		= 1200; 
	Goods[GOOD_PLANKS].MediumNorm			= 0.5;
	Goods[GOOD_PLANKS].SmallNorm			= 0.5;	
	
	Goods[GOOD_BRICK].Name	        		= "Brick";
	Goods[GOOD_BRICK].Weight        		= 6;
	Goods[GOOD_BRICK].Cost	        		= 120;
	Goods[GOOD_BRICK].Units	        		= 10;
	Goods[GOOD_BRICK].AfraidWater 			= 0;
	Goods[GOOD_BRICK].type 					= T_TYPE_NORMAL;
	Goods[GOOD_BRICK].Norm					= 1200;
	Goods[GOOD_BRICK].MediumNorm			= 0.5;
	Goods[GOOD_BRICK].SmallNorm				= 0.5;	
	
	Goods[GOOD_WHEAT].Name		    		= "Wheat";
	Goods[GOOD_WHEAT].Weight	    		= 1;
	Goods[GOOD_WHEAT].Cost		    		= 20;
	Goods[GOOD_WHEAT].Units		    		= 1;
	Goods[GOOD_WHEAT].Swim.Model			= "sack";
	Goods[GOOD_WHEAT].Swim.Time				= 30;
	Goods[GOOD_WHEAT].AfraidWater 			= 3;
	Goods[GOOD_WHEAT].type		 			= T_TYPE_NORMAL;
	Goods[GOOD_WHEAT].Norm					= 1200;
	Goods[GOOD_WHEAT].MediumNorm			= 0.5;
	Goods[GOOD_WHEAT].SmallNorm				= 0.5;	

	Goods[GOOD_CLOTHES].Name	    		= "Clothes";
	Goods[GOOD_CLOTHES].Weight	    		= 1;
	Goods[GOOD_CLOTHES].Cost	    		= 20;
	Goods[GOOD_CLOTHES].Units	    		= 10;
	Goods[GOOD_CLOTHES].Swim.Model			= "bale";
	Goods[GOOD_CLOTHES].Swim.Time			= 30;
	Goods[GOOD_CLOTHES].AfraidWater 		= 2;
	Goods[GOOD_CLOTHES].type 				= T_TYPE_NORMAL;
	Goods[GOOD_CLOTHES].Norm				= 1200;
	Goods[GOOD_CLOTHES].MediumNorm			= 0.5;
	Goods[GOOD_CLOTHES].SmallNorm			= 0.5;	
	
	Goods[GOOD_FRUITS].Name		    		= "Fruits";
	Goods[GOOD_FRUITS].Weight	    		= 1;
	Goods[GOOD_FRUITS].Cost		    		= 20;
	Goods[GOOD_FRUITS].Units	    		= 1;
	Goods[GOOD_FRUITS].Swim.Model			= "box";
	Goods[GOOD_FRUITS].Swim.Time			= 25;
	Goods[GOOD_FRUITS].AfraidWater 			= 3;
	Goods[GOOD_FRUITS].type 				= T_TYPE_NORMAL;
	Goods[GOOD_FRUITS].Norm					= 1200;
	Goods[GOOD_FRUITS].MediumNorm			= 0.5;
	Goods[GOOD_FRUITS].SmallNorm			= 0.5;	
	
	// колониальные (экспортные) товары
	Goods[GOOD_COFFEE].Name		    		= "Coffee";
	Goods[GOOD_COFFEE].Weight	    		= 2;
	Goods[GOOD_COFFEE].Cost		    		= 80;
	Goods[GOOD_COFFEE].Units	    		= 1;
	Goods[GOOD_COFFEE].Swim.Model			= "sack";
	Goods[GOOD_COFFEE].Swim.Time			= 25;
	Goods[GOOD_COFFEE].AfraidWater 			= 3;
	Goods[GOOD_COFFEE].type 				= T_TYPE_EXPORT;
	Goods[GOOD_COFFEE].Norm          		= 2400; 
	Goods[GOOD_COFFEE].MediumNorm			= 0.75;
	Goods[GOOD_COFFEE].SmallNorm			= 0.5;		
	
	Goods[GOOD_CHOCOLATE].Name				= "Chocolate";
	Goods[GOOD_CHOCOLATE].Weight			= 2;
	Goods[GOOD_CHOCOLATE].Cost				= 80;
	Goods[GOOD_CHOCOLATE].Units				= 1;
	Goods[GOOD_CHOCOLATE].Swim.Model		= "bale";
	Goods[GOOD_CHOCOLATE].Swim.Time			= 25;
	Goods[GOOD_CHOCOLATE].AfraidWater 		= 3;
	Goods[GOOD_CHOCOLATE].type 				= T_TYPE_EXPORT;
	Goods[GOOD_CHOCOLATE].Norm          	= 2400;  	
	Goods[GOOD_CHOCOLATE].MediumNorm		= 0.75;
	Goods[GOOD_CHOCOLATE].SmallNorm			= 0.5;		

	Goods[GOOD_TOBACCO].Name	    		= "Tobacco";
	Goods[GOOD_TOBACCO].Weight	    		= 2;
	Goods[GOOD_TOBACCO].Cost	    		= 80;
	Goods[GOOD_TOBACCO].Units	    		= 1;
	Goods[GOOD_TOBACCO].Swim.Model			= "bale";
	Goods[GOOD_TOBACCO].Swim.Time			= 25;
	Goods[GOOD_TOBACCO].AfraidWater 		= 3;
	Goods[GOOD_TOBACCO].type 				= T_TYPE_EXPORT;
	Goods[GOOD_TOBACCO].Norm          		= 2400;  
	Goods[GOOD_TOBACCO].MediumNorm			= 0.75;
	Goods[GOOD_TOBACCO].SmallNorm			= 0.5;		
	
	Goods[GOOD_SUGAR].Name		    		= "Sugar";
	Goods[GOOD_SUGAR].Weight	    		= 2;
	Goods[GOOD_SUGAR].Cost		    		= 80;
	Goods[GOOD_SUGAR].Units		    		= 1;
	Goods[GOOD_SUGAR].AfraidWater 			= 3;
	Goods[GOOD_SUGAR].type		 			= T_TYPE_EXPORT;
	Goods[GOOD_SUGAR].Norm          		= 2400;  	
	Goods[GOOD_SUGAR].MediumNorm			= 0.75;
	Goods[GOOD_SUGAR].SmallNorm				= 0.5;		
	
	Goods[GOOD_COTTON].Name		    		= "Cotton";
	Goods[GOOD_COTTON].Weight	    		= 1;
	Goods[GOOD_COTTON].Cost		    		= 40;
	Goods[GOOD_COTTON].Units	    		= 1;
	Goods[GOOD_COTTON].Swim.Model			= "bale";
	Goods[GOOD_COTTON].Swim.Time			= 25; 
	Goods[GOOD_COTTON].AfraidWater 			= 3;
	Goods[GOOD_COTTON].type		 			= T_TYPE_EXPORT;
	Goods[GOOD_COTTON].Norm					= 2400;
	Goods[GOOD_COTTON].MediumNorm			= 0.75;
	Goods[GOOD_COTTON].SmallNorm			= 0.5;		
	
	Goods[GOOD_LEATHER].Name	    		= "Leather";
	Goods[GOOD_LEATHER].Weight	    		= 1;
	Goods[GOOD_LEATHER].Cost	    		= 40;
	Goods[GOOD_LEATHER].Units	    		= 1;
	Goods[GOOD_LEATHER].Swim.Model			= "bale";
	Goods[GOOD_LEATHER].Swim.Time			= 30;
	Goods[GOOD_LEATHER].AfraidWater 		= 1;
	Goods[GOOD_LEATHER].type 				= T_TYPE_EXPORT;
	Goods[GOOD_LEATHER].Norm				= 2400;
	Goods[GOOD_LEATHER].MediumNorm			= 0.75;
	Goods[GOOD_LEATHER].SmallNorm			= 0.5;		
	
	Goods[GOOD_EBONY].Name		    		= "Ebony";
	Goods[GOOD_EBONY].Weight	    		= 5;
	Goods[GOOD_EBONY].Cost		    		= 200;
	Goods[GOOD_EBONY].Units		    		= 1;
	Goods[GOOD_EBONY].Swim.Model			= "roll_of_planks";
	Goods[GOOD_EBONY].Swim.Time				= 20; 
	Goods[GOOD_EBONY].AfraidWater 			= 0;    
	Goods[GOOD_EBONY].type 					= T_TYPE_EXPORT;    
	Goods[GOOD_EBONY].Norm          		= 2400;  
	Goods[GOOD_EBONY].MediumNorm			= 0.75;
	Goods[GOOD_EBONY].SmallNorm			= 0.5;		

	Goods[GOOD_MAHOGANY].Name	    		= "Mahogany";
	Goods[GOOD_MAHOGANY].Weight	    		= 4;
	Goods[GOOD_MAHOGANY].Cost	    		= 160;
	Goods[GOOD_MAHOGANY].Units	    		= 1;
	Goods[GOOD_MAHOGANY].Swim.Model			= "roll_of_planks";
	Goods[GOOD_MAHOGANY].Swim.Time			= 45;
	Goods[GOOD_MAHOGANY].AfraidWater 		= 1;
	Goods[GOOD_MAHOGANY].type 				= T_TYPE_EXPORT;
	Goods[GOOD_MAHOGANY].Norm          		= 2400;  
	Goods[GOOD_MAHOGANY].MediumNorm			= 0.75;
	Goods[GOOD_MAHOGANY].SmallNorm			= 0.5;		

	Goods[GOOD_CINNAMON].Name	    		= "Cinnamon";
	Goods[GOOD_CINNAMON].Weight	    		= 2;
	Goods[GOOD_CINNAMON].Cost	    		= 80;
	Goods[GOOD_CINNAMON].Units	    		= 1;
	Goods[GOOD_CINNAMON].Swim.Model			= "bale";
	Goods[GOOD_CINNAMON].Swim.Time			= 25;
	Goods[GOOD_CINNAMON].AfraidWater 		= 3;
	Goods[GOOD_CINNAMON].type 				= T_TYPE_EXPORT;
	Goods[GOOD_CINNAMON].Norm          		= 2400;  
	Goods[GOOD_CINNAMON].MediumNorm			= 0.75;
	Goods[GOOD_CINNAMON].SmallNorm			= 0.5;		

	Goods[GOOD_COPRA].Name		    		= "Copra";
	Goods[GOOD_COPRA].Weight	    		= 2;
	Goods[GOOD_COPRA].Cost		    		= 80;
	Goods[GOOD_COPRA].Units		    		= 1;
	Goods[GOOD_COPRA].Swim.Model			= "basket";
	Goods[GOOD_COPRA].Swim.Time				= 30;
	Goods[GOOD_COPRA].AfraidWater 			= 3;
	Goods[GOOD_COPRA].type 					= T_TYPE_EXPORT;
	Goods[GOOD_COPRA].Norm          		= 2400;  
	Goods[GOOD_COPRA].MediumNorm			= 0.75;
	Goods[GOOD_COPRA].SmallNorm				= 0.5;		

	Goods[GOOD_PAPRIKA].Name	    		= "Paprika";
	Goods[GOOD_PAPRIKA].Weight	    		= 2;
	Goods[GOOD_PAPRIKA].Cost	    		= 40;
	Goods[GOOD_PAPRIKA].Units	    		= 1;
	Goods[GOOD_PAPRIKA].Swim.Model			= "box";
	Goods[GOOD_PAPRIKA].Swim.Time			= 25;
	Goods[GOOD_PAPRIKA].AfraidWater 		= 3;
	Goods[GOOD_PAPRIKA].type 				= T_TYPE_EXPORT;
	Goods[GOOD_PAPRIKA].Norm          		= 2400;  
	Goods[GOOD_PAPRIKA].MediumNorm			= 0.75;
	Goods[GOOD_PAPRIKA].SmallNorm			= 0.5;		

	// привозные товары из Европы
	Goods[GOOD_POWDER].Name		    		= "Powder";
	Goods[GOOD_POWDER].Weight	    		= 1;
	Goods[GOOD_POWDER].Cost	        		= 60;
	Goods[GOOD_POWDER].Units	    		= 20;
	Goods[GOOD_POWDER].AfraidWater 			= 1;
	Goods[GOOD_POWDER].DontDrop				= 1;	
	Goods[GOOD_POWDER].trade_type			= T_TYPE_AMMUNITION;
	Goods[GOOD_POWDER].type					= T_TYPE_IMPORT;
	Goods[GOOD_POWDER].Norm          		= 1200;
	Goods[GOOD_POWDER].MediumNorm			= 1.0;
	Goods[GOOD_POWDER].SmallNorm			= 0.5;		

	Goods[GOOD_WEAPON].Name	  	    		= "Weapon";
	Goods[GOOD_WEAPON].Weight	    		= 1;
	Goods[GOOD_WEAPON].Cost	        		= 60;
	Goods[GOOD_WEAPON].Units	    		= 10;
	Goods[GOOD_WEAPON].AfraidWater 			= 0;
	Goods[GOOD_WEAPON].DontDrop				= 1;	
	Goods[GOOD_WEAPON].trade_type			= T_TYPE_AMMUNITION;
	Goods[GOOD_WEAPON].type					= T_TYPE_IMPORT;
	Goods[GOOD_WEAPON].Norm          		= 1200; 
	Goods[GOOD_WEAPON].MediumNorm			= 1.0;
	Goods[GOOD_WEAPON].SmallNorm			= 0.5;		
	
	Goods[GOOD_MEDICAMENT].Name		    	= "Medicament";
	Goods[GOOD_MEDICAMENT].Weight	    	= 1;
	Goods[GOOD_MEDICAMENT].Cost		    	= 60;
	Goods[GOOD_MEDICAMENT].Units	    	= 30;
	Goods[GOOD_MEDICAMENT].Swim.Model		= "box";
	Goods[GOOD_MEDICAMENT].Swim.Time		= 45;
	Goods[GOOD_MEDICAMENT].AfraidWater 		= 0;
	Goods[GOOD_MEDICAMENT].DontDrop			= 1;	
	Goods[GOOD_MEDICAMENT].type 			= T_TYPE_IMPORT;
	Goods[GOOD_MEDICAMENT].Norm          	= 1200; 	
	Goods[GOOD_MEDICAMENT].MediumNorm		= 1.0;
	Goods[GOOD_MEDICAMENT].SmallNorm		= 0.5;		
		
	Goods[GOOD_WINE].Name		    		= "Wine";
	Goods[GOOD_WINE].Weight	        		= 2;
	Goods[GOOD_WINE].Cost		    		= 120;
	Goods[GOOD_WINE].Units		    		= 1;
	Goods[GOOD_WINE].Swim.Model	    		= "barrel";
	Goods[GOOD_WINE].Swim.Time	    		= 30;
	Goods[GOOD_WINE].AfraidWater 			= 1;
	Goods[GOOD_WINE].type 					= T_TYPE_IMPORT;
	Goods[GOOD_WINE].Norm          			= 1200;  
	Goods[GOOD_WINE].MediumNorm				= 1.0;
	Goods[GOOD_WINE].SmallNorm				= 0.5;		

	Goods[GOOD_RUM].Name		    		= "Rum";
	Goods[GOOD_RUM].Weight		    		= 1;
	Goods[GOOD_RUM].Cost		    		= 60;
	Goods[GOOD_RUM].Units		    		= 1;
	Goods[GOOD_RUM].Swim.Model	    		= "barrel";
	Goods[GOOD_RUM].Swim.Time	    		= 30;
	Goods[GOOD_RUM].AfraidWater 			= 1;
	Goods[GOOD_RUM].type 					= T_TYPE_IMPORT;
	Goods[GOOD_RUM].Norm					= 1200;
	Goods[GOOD_RUM].MediumNorm				= 1.0;
	Goods[GOOD_RUM].SmallNorm				= 0.5;		

	Goods[GOOD_ALE].Name	        		= "Ale";
	Goods[GOOD_ALE].Weight	        		= 1;
	Goods[GOOD_ALE].Cost	        		= 60;
	Goods[GOOD_ALE].Units	        		= 1;
	Goods[GOOD_ALE].Swim.Model	    		= "barrel";
	Goods[GOOD_ALE].Swim.Time	    		= 30;
	Goods[GOOD_ALE].AfraidWater 			= 1;
	Goods[GOOD_ALE].type 					= T_TYPE_IMPORT;
	Goods[GOOD_ALE].Norm					= 1200;	
	Goods[GOOD_ALE].MediumNorm				= 1.0;
	Goods[GOOD_ALE].SmallNorm				= 0.5;		
	
	// уникальные товары
	Goods[GOOD_SHIPSILK].Name		    	= "Shipsilk";
	Goods[GOOD_SHIPSILK].Weight	    		= 2;
	Goods[GOOD_SHIPSILK].Cost		    	= 160;
	Goods[GOOD_SHIPSILK].Units		    	= 1;
	Goods[GOOD_SHIPSILK].Swim.Model			= "roll_of_rolls";
	Goods[GOOD_SHIPSILK].Swim.Time			= 20;
	Goods[GOOD_SHIPSILK].AfraidWater 		= 1;
	Goods[GOOD_SHIPSILK].DontDrop			= 1;	
	Goods[GOOD_SHIPSILK].type 				= T_TYPE_UNIQUE;
	Goods[GOOD_SHIPSILK].Norm          		= 1200;  
	Goods[GOOD_SHIPSILK].MediumNorm			= 0.5;
	Goods[GOOD_SHIPSILK].SmallNorm			= 0.25;		

	Goods[GOOD_ROPES].Name	        		= "Ropes";
	Goods[GOOD_ROPES].Weight	        	= 1;
	Goods[GOOD_ROPES].Cost	        		= 80;
	Goods[GOOD_ROPES].Units	        		= 1;
	Goods[GOOD_ROPES].Swim.Model	    	= "sack";
	Goods[GOOD_ROPES].Swim.Time	    		= 20;
	Goods[GOOD_ROPES].AfraidWater 			= 0;
	Goods[GOOD_ROPES].DontDrop				= 1;	
	Goods[GOOD_ROPES].type 					= T_TYPE_UNIQUE;
	Goods[GOOD_ROPES].Norm					= 1200;
	Goods[GOOD_ROPES].MediumNorm			= 0.5;
	Goods[GOOD_ROPES].SmallNorm				= 0.25;		

	Goods[GOOD_SANDAL].Name		    		= "Sandal";
	Goods[GOOD_SANDAL].Weight	    		= 7;
	Goods[GOOD_SANDAL].Cost		    		= 240;
	Goods[GOOD_SANDAL].Units	    		= 1;
	Goods[GOOD_SANDAL].Swim.Model			= "box";
	Goods[GOOD_SANDAL].Swim.Time			= 45;
	Goods[GOOD_SANDAL].AfraidWater 			= 1;
	Goods[GOOD_SANDAL].type 				= T_TYPE_UNIQUE;
	Goods[GOOD_SANDAL].Norm          		= 1200;  
	Goods[GOOD_SANDAL].MediumNorm				= 0.5;
	Goods[GOOD_SANDAL].SmallNorm				= 0.25;		

	Goods[GOOD_OIL].Name	        		= "Oil";
	Goods[GOOD_OIL].Weight	        		= 1;
	Goods[GOOD_OIL].Cost	        		= 80;
	Goods[GOOD_OIL].Units	        		= 1;
	Goods[GOOD_OIL].Swim.Model	    		= "barrel";
	Goods[GOOD_OIL].Swim.Time	    		= 20;
	Goods[GOOD_OIL].AfraidWater 			= 0;
	Goods[GOOD_OIL].DontDrop				= 1;	
	Goods[GOOD_OIL].type	 				= T_TYPE_UNIQUE;
	Goods[GOOD_OIL].Norm          			= 1200;  
	Goods[GOOD_OIL].MediumNorm				= 0.5;
	Goods[GOOD_OIL].SmallNorm				= 0.25;		
	
	// коронные товары
	Goods[GOOD_SLAVES].Name		    		= "Slaves";
	Goods[GOOD_SLAVES].Weight	    		= 1;
	Goods[GOOD_SLAVES].Cost		    		= 100;
	Goods[GOOD_SLAVES].Units	    		= 1;
	Goods[GOOD_SLAVES].Swim.Model			= "lo_man";
	Goods[GOOD_SLAVES].Swim.Time			= 20;
	Goods[GOOD_SLAVES].AfraidWater 			= 0;
	Goods[GOOD_SLAVES].type 				= T_TYPE_CROWN;
	Goods[GOOD_SLAVES].Norm          		= 1200; 
	Goods[GOOD_SLAVES].MediumNorm			= 0.5;
	Goods[GOOD_SLAVES].SmallNorm			= 0.25;		

	Goods[GOOD_GOLD].Name		    		= "Gold";
	Goods[GOOD_GOLD].Weight	        		= 2;
	Goods[GOOD_GOLD].Cost	        		= 200;
	Goods[GOOD_GOLD].Units	        		= 1;
	Goods[GOOD_GOLD].AfraidWater 			= 0;
	Goods[GOOD_GOLD].DontDrop				= 1;	
	Goods[GOOD_GOLD].type	 				= T_TYPE_CROWN;
	Goods[GOOD_GOLD].Norm          			= 1200; 
	Goods[GOOD_GOLD].MediumNorm				= 0.5;
	Goods[GOOD_GOLD].SmallNorm				= 0.25;		
	Goods[GOOD_GOLD].NotSale				= 1;
	
	Goods[GOOD_SILVER].Name		    		= "Silver";
	Goods[GOOD_SILVER].Weight	    		= 1;
	Goods[GOOD_SILVER].Cost	        		= 100;
	Goods[GOOD_SILVER].Units	    		= 1;
	Goods[GOOD_SILVER].AfraidWater 			= 0;
	Goods[GOOD_SILVER].DontDrop				= 1;	
	Goods[GOOD_SILVER].type 				= T_TYPE_CROWN;
	Goods[GOOD_SILVER].Norm          		= 1200; 
	Goods[GOOD_SILVER].MediumNorm			= 0.5;
	Goods[GOOD_SILVER].SmallNorm			= 0.25;		
	Goods[GOOD_SILVER].NotSale				= 1;
		
	////////////////////////////////////////////////////// пушки это товар - boal 27/07/06	
	Goods[GOOD_CANNON_3].Name				= "Cannon_3";
	Goods[GOOD_CANNON_3].CannonIdx			= CANNON_TYPE_CANNON_LBS3;
	Goods[GOOD_CANNON_3].Cost				= Cannon[CANNON_TYPE_CANNON_LBS3].Cost;
	Goods[GOOD_CANNON_3].Weight		    	= Cannon[CANNON_TYPE_CANNON_LBS3].Weight;
	Goods[GOOD_CANNON_3].FireRange	    	= Cannon[CANNON_TYPE_CANNON_LBS3].FireRange;
	Goods[GOOD_CANNON_3].DamageMultiply		= Cannon[CANNON_TYPE_CANNON_LBS3].DamageMultiply;
	Goods[GOOD_CANNON_3].ReloadTime			= sti(GetCannonReloadTime(&Cannon[CANNON_TYPE_CANNON_LBS3]));
	Goods[GOOD_CANNON_3].Units				= 1;
	Goods[GOOD_CANNON_3].AfraidWater		= 0;
	Goods[GOOD_CANNON_3].type				= T_TYPE_CANNONS;
	Goods[GOOD_CANNON_3].trade_type			= T_TYPE_CANNONS;
	Goods[GOOD_CANNON_3].NotSale			= 0;
	Goods[GOOD_CANNON_3].Norm           	= 30; 
	Goods[GOOD_CANNON_3].MediumNorm			= 1.0;
	Goods[GOOD_CANNON_3].SmallNorm			= 1.0;
	
	Goods[GOOD_CANNON_6].Name				= "Cannon_6";
	Goods[GOOD_CANNON_6].CannonIdx			= CANNON_TYPE_CANNON_LBS6;
	Goods[GOOD_CANNON_6].Cost				= Cannon[CANNON_TYPE_CANNON_LBS6].Cost;
	Goods[GOOD_CANNON_6].Weight		    	= Cannon[CANNON_TYPE_CANNON_LBS6].Weight;
	Goods[GOOD_CANNON_6].FireRange	    	= Cannon[CANNON_TYPE_CANNON_LBS6].FireRange;
	Goods[GOOD_CANNON_6].DamageMultiply		= Cannon[CANNON_TYPE_CANNON_LBS6].DamageMultiply;
	Goods[GOOD_CANNON_6].ReloadTime			= sti(GetCannonReloadTime(&Cannon[CANNON_TYPE_CANNON_LBS6]));
	Goods[GOOD_CANNON_6].Units				= 1;
	Goods[GOOD_CANNON_6].AfraidWater		= 0;
	Goods[GOOD_CANNON_6].type				= T_TYPE_CANNONS;
	Goods[GOOD_CANNON_6].trade_type			= T_TYPE_CANNONS;
	Goods[GOOD_CANNON_6].NotSale			= 0;
	Goods[GOOD_CANNON_6].Norm           	= 25; 
	Goods[GOOD_CANNON_6].MediumNorm			= 1.0;
	Goods[GOOD_CANNON_6].SmallNorm			= 1.0;
	
	Goods[GOOD_CANNON_12].Name				= "Cannon_12";
	Goods[GOOD_CANNON_12].CannonIdx			= CANNON_TYPE_CANNON_LBS12;
	Goods[GOOD_CANNON_12].Cost				= Cannon[CANNON_TYPE_CANNON_LBS12].Cost;
	Goods[GOOD_CANNON_12].Weight			= Cannon[CANNON_TYPE_CANNON_LBS12].Weight;
	Goods[GOOD_CANNON_12].FireRange		    = Cannon[CANNON_TYPE_CANNON_LBS12].FireRange;
	Goods[GOOD_CANNON_12].DamageMultiply	= Cannon[CANNON_TYPE_CANNON_LBS12].DamageMultiply;
	Goods[GOOD_CANNON_12].ReloadTime		= sti(GetCannonReloadTime(&Cannon[CANNON_TYPE_CANNON_LBS12]));
	Goods[GOOD_CANNON_12].Units				= 1;
	Goods[GOOD_CANNON_12].AfraidWater		= 0;
	Goods[GOOD_CANNON_12].type				= T_TYPE_CANNONS;
	Goods[GOOD_CANNON_12].trade_type		= T_TYPE_CANNONS;
	Goods[GOOD_CANNON_12].NotSale			= 0;
	Goods[GOOD_CANNON_12].Norm          	= 25; 
	Goods[GOOD_CANNON_12].MediumNorm		= 1.0;
	Goods[GOOD_CANNON_12].SmallNorm			= 1.0;
	
	Goods[GOOD_CANNON_16].Name				= "Cannon_16";
	Goods[GOOD_CANNON_16].CannonIdx			= CANNON_TYPE_CANNON_LBS16;
	Goods[GOOD_CANNON_16].Cost				= Cannon[CANNON_TYPE_CANNON_LBS16].Cost;
	Goods[GOOD_CANNON_16].Weight			= Cannon[CANNON_TYPE_CANNON_LBS16].Weight;
	Goods[GOOD_CANNON_16].Units				= 1;
	Goods[GOOD_CANNON_16].AfraidWater		= 0;
	Goods[GOOD_CANNON_16].type				= T_TYPE_CANNONS;
	Goods[GOOD_CANNON_16].trade_type		= T_TYPE_CANNONS;
	Goods[GOOD_CANNON_16].NotSale			= 0;
	Goods[GOOD_CANNON_16].FireRange		    = Cannon[CANNON_TYPE_CANNON_LBS16].FireRange;
	Goods[GOOD_CANNON_16].DamageMultiply	= Cannon[CANNON_TYPE_CANNON_LBS16].DamageMultiply;
	Goods[GOOD_CANNON_16].ReloadTime		= sti(GetCannonReloadTime(&Cannon[CANNON_TYPE_CANNON_LBS16]));
	Goods[GOOD_CANNON_16].Norm          	= 20; 
	Goods[GOOD_CANNON_16].MediumNorm		= 1.0;
	Goods[GOOD_CANNON_16].SmallNorm			= 1.0;
	
	Goods[GOOD_CANNON_20].Name				= "Cannon_20";
	Goods[GOOD_CANNON_20].CannonIdx			= CANNON_TYPE_CANNON_LBS20;
	Goods[GOOD_CANNON_20].Cost				= Cannon[CANNON_TYPE_CANNON_LBS20].Cost;
	Goods[GOOD_CANNON_20].Weight			= Cannon[CANNON_TYPE_CANNON_LBS20].Weight;
	Goods[GOOD_CANNON_20].Units				= 1;
	Goods[GOOD_CANNON_20].AfraidWater		= 0;
	Goods[GOOD_CANNON_20].type				= T_TYPE_CANNONS;
	Goods[GOOD_CANNON_20].trade_type		= T_TYPE_CANNONS;
	Goods[GOOD_CANNON_20].NotSale			= 0;
	Goods[GOOD_CANNON_20].FireRange		    = Cannon[CANNON_TYPE_CANNON_LBS20].FireRange;
	Goods[GOOD_CANNON_20].DamageMultiply	= Cannon[CANNON_TYPE_CANNON_LBS20].DamageMultiply;
	Goods[GOOD_CANNON_20].ReloadTime		= sti(GetCannonReloadTime(&Cannon[CANNON_TYPE_CANNON_LBS20]));
	Goods[GOOD_CANNON_20].Norm          	= 15; 
	Goods[GOOD_CANNON_20].MediumNorm		= 1.0;
	Goods[GOOD_CANNON_20].SmallNorm			= 0.5;
	
	Goods[GOOD_CANNON_24].Name				= "Cannon_24";
	Goods[GOOD_CANNON_24].CannonIdx			= CANNON_TYPE_CANNON_LBS24;
	Goods[GOOD_CANNON_24].Cost				= Cannon[CANNON_TYPE_CANNON_LBS24].Cost;
	Goods[GOOD_CANNON_24].Weight			= Cannon[CANNON_TYPE_CANNON_LBS24].Weight;
	Goods[GOOD_CANNON_24].Units				= 1;
	Goods[GOOD_CANNON_24].AfraidWater		= 0;
	Goods[GOOD_CANNON_24].type				= T_TYPE_CANNONS;
	Goods[GOOD_CANNON_24].trade_type		= T_TYPE_CANNONS;
	Goods[GOOD_CANNON_24].NotSale   		= 0;
	Goods[GOOD_CANNON_24].FireRange		    = Cannon[CANNON_TYPE_CANNON_LBS24].FireRange;
	Goods[GOOD_CANNON_24].DamageMultiply	= Cannon[CANNON_TYPE_CANNON_LBS24].DamageMultiply;
	Goods[GOOD_CANNON_24].ReloadTime		= sti(GetCannonReloadTime(&Cannon[CANNON_TYPE_CANNON_LBS24]));
	Goods[GOOD_CANNON_24].Norm          	= 15; 
	Goods[GOOD_CANNON_24].MediumNorm		= 1.0;
	Goods[GOOD_CANNON_24].SmallNorm			= 1.0;
	
	Goods[GOOD_CANNON_32].Name				= "Cannon_32";
	Goods[GOOD_CANNON_32].CannonIdx			= CANNON_TYPE_CANNON_LBS32;
	Goods[GOOD_CANNON_32].Cost				= Cannon[CANNON_TYPE_CANNON_LBS32].Cost;
	Goods[GOOD_CANNON_32].Weight			= Cannon[CANNON_TYPE_CANNON_LBS32].Weight;
	Goods[GOOD_CANNON_32].Units				= 1;
	Goods[GOOD_CANNON_32].AfraidWater		= 0;
	Goods[GOOD_CANNON_32].type				= T_TYPE_CANNONS;
	Goods[GOOD_CANNON_32].trade_type		= T_TYPE_CANNONS;
	Goods[GOOD_CANNON_32].NotSale			= 0;
	Goods[GOOD_CANNON_32].FireRange		    = Cannon[CANNON_TYPE_CANNON_LBS32].FireRange;
	Goods[GOOD_CANNON_32].DamageMultiply	= Cannon[CANNON_TYPE_CANNON_LBS32].DamageMultiply;
	Goods[GOOD_CANNON_32].ReloadTime		= sti(GetCannonReloadTime(&Cannon[CANNON_TYPE_CANNON_LBS32]));
	Goods[GOOD_CANNON_32].Norm          	= 10; 
	Goods[GOOD_CANNON_32].MediumNorm		= 1.0;
	Goods[GOOD_CANNON_32].SmallNorm			= 1.0;
	
	Goods[GOOD_CANNON_36].Name				= "Cannon_36";
	Goods[GOOD_CANNON_36].CannonIdx			= CANNON_TYPE_CANNON_LBS36;
	Goods[GOOD_CANNON_36].Cost				= Cannon[CANNON_TYPE_CANNON_LBS36].Cost;
	Goods[GOOD_CANNON_36].Weight			= Cannon[CANNON_TYPE_CANNON_LBS36].Weight;
	Goods[GOOD_CANNON_36].Units				= 1;
	Goods[GOOD_CANNON_36].AfraidWater		= 0;
	Goods[GOOD_CANNON_36].type				= T_TYPE_CANNONS;
	Goods[GOOD_CANNON_36].trade_type		= T_TYPE_CANNONS;
	Goods[GOOD_CANNON_36].NotSale			= 1;
	Goods[GOOD_CANNON_36].FireRange		    = Cannon[CANNON_TYPE_CANNON_LBS36].FireRange;
	Goods[GOOD_CANNON_36].DamageMultiply	= Cannon[CANNON_TYPE_CANNON_LBS36].DamageMultiply;
	Goods[GOOD_CANNON_36].ReloadTime		= sti(GetCannonReloadTime(&Cannon[CANNON_TYPE_CANNON_LBS36]));
	Goods[GOOD_CANNON_36].Norm          	= 10; 
	Goods[GOOD_CANNON_36].MediumNorm		= 1.0;
	Goods[GOOD_CANNON_36].SmallNorm			= 1.0;
	
	Goods[GOOD_CANNON_42].Name				= "Cannon_42";
	Goods[GOOD_CANNON_42].CannonIdx			= CANNON_TYPE_CANNON_LBS42;
	Goods[GOOD_CANNON_42].Cost				= Cannon[CANNON_TYPE_CANNON_LBS42].Cost;
	Goods[GOOD_CANNON_42].Weight			= Cannon[CANNON_TYPE_CANNON_LBS42].Weight;
	Goods[GOOD_CANNON_42].Units				= 1;
	Goods[GOOD_CANNON_42].AfraidWater		= 0;
	Goods[GOOD_CANNON_42].type				= T_TYPE_CANNONS;
	Goods[GOOD_CANNON_42].trade_type		= T_TYPE_CANNONS;
	Goods[GOOD_CANNON_42].NotSale			= 1;
	Goods[GOOD_CANNON_42].FireRange		    = Cannon[CANNON_TYPE_CANNON_LBS42].FireRange;
	Goods[GOOD_CANNON_42].DamageMultiply	= Cannon[CANNON_TYPE_CANNON_LBS42].DamageMultiply;
	Goods[GOOD_CANNON_42].ReloadTime		= sti(GetCannonReloadTime(&Cannon[CANNON_TYPE_CANNON_LBS42]));
	Goods[GOOD_CANNON_42].Norm          	= 10; 
	Goods[GOOD_CANNON_42].MediumNorm		= 1.0;
	Goods[GOOD_CANNON_42].SmallNorm			= 1.0;
	
    Goods[GOOD_CULVERINE_8].Name			= "Culverine_8";
	Goods[GOOD_CULVERINE_8].CannonIdx	 	= CANNON_TYPE_CULVERINE_LBS8;
	Goods[GOOD_CULVERINE_8].Cost			= Cannon[CANNON_TYPE_CULVERINE_LBS8].Cost;
	Goods[GOOD_CULVERINE_8].Weight			= Cannon[CANNON_TYPE_CULVERINE_LBS8].Weight;
	Goods[GOOD_CULVERINE_8].Units			= 1;
	Goods[GOOD_CULVERINE_8].AfraidWater	    = 0;
	Goods[GOOD_CULVERINE_8].type			= T_TYPE_CANNONS;
	Goods[GOOD_CULVERINE_8].trade_type		= T_TYPE_CANNONS;
	Goods[GOOD_CULVERINE_8].NotSale  		= 0;
	Goods[GOOD_CULVERINE_8].FireRange		= Cannon[CANNON_TYPE_CULVERINE_LBS8].FireRange;
	Goods[GOOD_CULVERINE_8].DamageMultiply	= Cannon[CANNON_TYPE_CULVERINE_LBS8].DamageMultiply;
	Goods[GOOD_CULVERINE_8].ReloadTime		= sti(GetCannonReloadTime(&Cannon[CANNON_TYPE_CULVERINE_LBS8]));
	Goods[GOOD_CULVERINE_8].Norm          	= 30; 
	Goods[GOOD_CULVERINE_8].MediumNorm		= 1.0;
	Goods[GOOD_CULVERINE_8].SmallNorm		= 1.0;
		
	Goods[GOOD_CULVERINE_18].Name			= "Culverine_18";
	Goods[GOOD_CULVERINE_18].CannonIdx	 	= CANNON_TYPE_CULVERINE_LBS18;
	Goods[GOOD_CULVERINE_18].Cost			= Cannon[CANNON_TYPE_CULVERINE_LBS18].Cost;
	Goods[GOOD_CULVERINE_18].Weight			= Cannon[CANNON_TYPE_CULVERINE_LBS18].Weight;
	Goods[GOOD_CULVERINE_18].Units			= 1;
	Goods[GOOD_CULVERINE_18].AfraidWater	= 0;
	Goods[GOOD_CULVERINE_18].type			= T_TYPE_CANNONS;
	Goods[GOOD_CULVERINE_18].trade_type		= T_TYPE_CANNONS;
	Goods[GOOD_CULVERINE_18].NotSale 		= 0;
	Goods[GOOD_CULVERINE_18].FireRange		= Cannon[CANNON_TYPE_CULVERINE_LBS18].FireRange;
	Goods[GOOD_CULVERINE_18].DamageMultiply	= Cannon[CANNON_TYPE_CULVERINE_LBS18].DamageMultiply;
	Goods[GOOD_CULVERINE_18].ReloadTime		= sti(GetCannonReloadTime(&Cannon[CANNON_TYPE_CULVERINE_LBS18]));
	Goods[GOOD_CULVERINE_18].Norm          	= 20; 
	Goods[GOOD_CULVERINE_18].MediumNorm		= 1.0;
	Goods[GOOD_CULVERINE_18].SmallNorm		= 1.0;
			
	Goods[GOOD_CULVERINE_36].Name			= "Culverine_36";
	Goods[GOOD_CULVERINE_36].CannonIdx	 	= CANNON_TYPE_CULVERINE_LBS36;
	Goods[GOOD_CULVERINE_36].Cost			= Cannon[CANNON_TYPE_CULVERINE_LBS36].Cost;
	Goods[GOOD_CULVERINE_36].Weight			= Cannon[CANNON_TYPE_CULVERINE_LBS36].Weight;
	Goods[GOOD_CULVERINE_36].Units			= 1;
	Goods[GOOD_CULVERINE_36].AfraidWater	= 0;
	Goods[GOOD_CULVERINE_36].type			= T_TYPE_CANNONS;
	Goods[GOOD_CULVERINE_36].trade_type		= T_TYPE_CANNONS;
	Goods[GOOD_CULVERINE_36].NotSale 		= 1;
	Goods[GOOD_CULVERINE_36].FireRange		= Cannon[CANNON_TYPE_CULVERINE_LBS36].FireRange;
	Goods[GOOD_CULVERINE_36].DamageMultiply	= Cannon[CANNON_TYPE_CULVERINE_LBS36].DamageMultiply;
	Goods[GOOD_CULVERINE_36].ReloadTime		= sti(GetCannonReloadTime(&Cannon[CANNON_TYPE_CULVERINE_LBS36]));
	Goods[GOOD_CULVERINE_36].Norm          	= 10; 
	Goods[GOOD_CULVERINE_36].MediumNorm		= 1.0;
	Goods[GOOD_CULVERINE_36].SmallNorm		= 1.0;
	
	// boal 24/01/08 Норма товара в магазине (режим Экспорта), то есть максимум, ниже установлены исключения
	for (i = 0; i< GOODS_QUANTITY; i++)
	{
		if (!CheckAttribute(&Goods[i], "Norm"))
		{
			Goods[i].Norm          = 1200; 
			Goods[i].MediumNorm    = 0.5;
			Goods[i].SmallNorm     = 0.25;
		}
	}
}