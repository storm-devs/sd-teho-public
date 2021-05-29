void InitShips()
{
  ref refShip;

	for (int idx=0;idx<SHIP_TYPES_QUANTITY_WITH_FORT;idx++)
	{
		makeref(refShip,ShipsTypes[idx]);

		refship.index = idx;

		refship.InertiaAccelerationX = 0.2;		refship.InertiaBrakingX = 0.7;
		refship.InertiaAccelerationY = 0.4;		refship.InertiaBrakingY = 0.4;
		refship.InertiaAccelerationZ = 1.0;		refship.InertiaBrakingZ = 1.0;

		refship.Rocking.y 	= 0.5;
		refship.Rocking.az 	= 0.05;

		refship.NetGeraldSails = "";
		refship.Soundtype = "";

		refship.WaterLine 			= 0.0;
		refship.SpeedDependWeight 	= 0.0;
		refship.SubSeaDependWeight 	= 0.0;
		refship.TurnDependWeight 	= 0.0;
		refship.TurnDependSpeed 	= 0.0;

		refShip.Height.Bombs.Y		= 3.0;		refShip.Height.Bombs.DY		= 1.0;
		refShip.Height.Grapes.Y		= 4.0;		refShip.Height.Grapes.DY	= 1.0;
		refShip.Height.Knippels.Y	= 25.0;		refShip.Height.Knippels.DY	= 15.0;
		refShip.Height.Balls.Y		= 3.0;		refShip.Height.Balls.DY		= 1.0;

        refship.WindAgainstSpeed   	= 1.0;//boal
		refship.CabinType          	= "Cabin_Small"; // потом припишем слово My_ и будет каютой для ГГ
        refShip.AbordageLocation	= "BOARDING_SMALL_DECK";
        refship.DeckType          	= "Low";
        
		refShip.MaxCaliber			= 6;
		refShip.Cannon				= CANNON_TYPE_CANNON_LBS6;
		refShip.CannonsQuantity		= 0;
		refShip.CannonsQuantityMin	= 0;

		aref cannonl, cannonr, cannonb, cannonf;

		refship.CanEncounter 	= true;
		refship.Type.Merchant 	= true;
		refship.Type.War 		= true;
		refship.Track.Enable 	= false;
		refShip.FireHeight 		= 3.0;

		refShip.Massa = 1500000.0;
		refShip.Volume = 900.0;
		refShip.lowpolycrew = 5;

		refShip.rcannon = 0;
		refShip.lcannon = 0;
		refShip.fcannon = 0;
		refShip.bcannon = 0;
		
		ShipsTypes[idx].Cannons.Borts.cannonl = "";
		ShipsTypes[idx].Cannons.Borts.cannonr = "";
		ShipsTypes[idx].Cannons.Borts.cannonf = "";
		ShipsTypes[idx].Cannons.Borts.cannonb = "";

		makearef(cannonl,ShipsTypes[idx].Cannons.Borts.cannonl);
		makearef(cannonr,ShipsTypes[idx].Cannons.Borts.cannonr);
		makearef(cannonf,ShipsTypes[idx].Cannons.Borts.cannonf);
		makearef(cannonb,ShipsTypes[idx].Cannons.Borts.cannonb);

		cannonf.FireZone	= Degree2Radian(30.0);
		cannonf.FireDir		= Degree2Radian(0.0);
		cannonf.FireAngMin	= -0.35;
		cannonf.FireAngMax	= 0.60;

		cannonr.FireZone	= Degree2Radian(80.0);
		cannonr.FireDir		= Degree2Radian(90.0);
		cannonr.FireAngMin	= -0.35;
		cannonr.FireAngMax	= 0.60;

		cannonb.FireZone	= Degree2Radian(30.0);
		cannonb.FireDir		= Degree2Radian(180.0);
		cannonb.FireAngMin	= -0.35;
		cannonb.FireAngMax	= 0.60;

		cannonl.FireZone	= Degree2Radian(80.0);
		cannonl.FireDir		= Degree2Radian(270.0);
		cannonl.FireAngMin	= -0.35;
		cannonl.FireAngMax	= 0.60;
	}
	
	///////////////////////////////////////////////////////////////////////////
	//// Лодка
	///////////////////////////////////////////////////////////////////////////
	makeref(refShip,ShipsTypes[SHIP_BOAT]);
	refShip.Name									= "Boat";
	refship.Soundtype								= "lugger";
	refShip.Class									= 6;
	refShip.Cannon									= CANNON_TYPE_NONECANNON;
	refShip.MaxCaliber								= 12;
	refShip.Weight									= Tonnes2CWT(10);
	refShip.Capacity								= 50;
	refShip.CannonsQuantity							= 0;
	refShip.CannonsQuantityMin						= 0;
	refShip.rcannon 								= 0;
	refShip.lcannon 								= 0;
	refShip.fcannon 								= 0;
	refShip.bcannon 								= 0;
	refShip.MaxCrew									= 10; 
	refShip.OptCrew									= 5; 
	refShip.MinCrew									= 1;
	refShip.SpeedRate								= 4;
	refShip.TurnRate								= 40;
	refShip.Price									= 100;
	refShip.HP										= 100;
	refShip.SP										= 100;
	refship.CanEncounter							= false;
	refship.Type.Merchant							= false;
	refship.Type.War								= false;
	refShip.lowpolycrew 							= 0;
	refship.WaterLine								= -0.3;

	refShip.Massa 									= 10000.0;
	refShip.Volume 									= 100.0;
	
	refship.InertiaAccelerationX	= 5.0;	refship.InertiaBrakingX		= 3.0;
	refship.InertiaAccelerationY	= 0.4;	refship.InertiaBrakingY		= 0.2;
	refship.InertiaAccelerationZ	= 0.15;	refship.InertiaBrakingZ		= 0.05;
	
	//////////////////////////////////////////////////////////////////////////
	//// ОРДИНАРНЫЕ КОРАБЛИ
	//////////////////////////////////////////////////////////////////////////		
	///////////////////////////////////////////////////////////////////////////
	//// Баркас
	///////////////////////////////////////////////////////////////////////////
	makeref(refShip,ShipsTypes[SHIP_TARTANE]);
	refShip.Name									= "Tartane";
	refship.Soundtype								= "lugger";
	refShip.Class									= 6;
	refShip.Cannon									= CANNON_TYPE_NONECANNON;
	refShip.MaxCaliber								= 3;
	refShip.Weight									= Tonnes2CWT(10);
	refShip.Capacity								= 80;
	refShip.CannonsQuantity							= 0;
	refShip.CannonsQuantityMin						= 0;
	refShip.rcannon 								= 0;
	refShip.lcannon 								= 0;
	refShip.fcannon 								= 0;
	refShip.bcannon 								= 0;
	refShip.MaxCrew									= 15;
	refShip.OptCrew									= 12;
	refShip.MinCrew									= 1;	
	refShip.SpeedRate								= 7.0;
	refShip.TurnRate								= 75;
	refShip.Price									= 2100;
	refShip.HP										= 150;
	refShip.SP										= 100;
	refship.CanEncounter							= false;
	refship.Type.Merchant							= false;
	refship.Type.War								= false;
	refShip.lowpolycrew 							= 3;

	refShip.Massa 									= 10000.0;
	refShip.Volume 									= 20.0;
	refship.WindAgainstSpeed   						= 1.0;
		
	refship.InertiaAccelerationX	= 3.0;	refship.InertiaBrakingX		= 2.0;
	refship.InertiaAccelerationY	= 14;	refship.InertiaBrakingY		= 5;
	refship.InertiaAccelerationZ	= 5.0;	refship.InertiaBrakingZ		= 3.0;
	
	refShip.Height.Bombs.Y				= 0.4;	refShip.Height.Bombs.DY		= 0.2;
	refShip.Height.Grapes.Y				= 1.3;	refShip.Height.Grapes.DY	= 0.6;
	refShip.Height.Knippels.Y			= 6.5;	refShip.Height.Knippels.DY	= 5.8;
	refShip.Height.Balls.Y				= 0.4;	refShip.Height.Balls.DY		= 0.2;

	refship.Track.Enable	= true;
	refship.Track1.ZStart	= 0.20;
	refship.Track1.LifeTime = 9;
	refship.Track1.Width	= "1.0, 2.0";
	refship.Track1.Speed	= "5.2, 6.2";

	refship.Track2.ZStart	= -0.15;
	refship.Track2.LifeTime = 7;
	refship.Track2.Width	= "1.2, 2.0";
	refship.Track2.Speed	= "0.15, 0.25";
	
	refship.nation.england	= true;
	refship.nation.france	= true;
	refship.nation.spain	= true;
	refship.nation.holland	= true;
	refship.nation.pirate	= false;
	
	///////////////////////////////////////////////////////////////////////////
	//// Тартана
	///////////////////////////////////////////////////////////////////////////
	makeref(refShip,ShipsTypes[SHIP_WAR_TARTANE]);
	refShip.Name								= "WarTartane";
	refship.Soundtype							= "lugger";
	refShip.Class								= 6;
	refShip.Cannon								= CANNON_TYPE_CANNON_LBS3;
	refShip.MaxCaliber							= 3;
	refShip.Weight								= Tonnes2CWT(30);
	refShip.Capacity							= 210;
	refShip.CannonsQuantity						= 6; // 0,0,3,3
	refShip.CannonsQuantityMin					= 6;
	refShip.rcannon 							= 3; 
	refShip.lcannon 							= 3; 
	refShip.fcannon 							= 0;
	refShip.bcannon 							= 0;
	refShip.MaxCrew								= 25;
	refShip.OptCrew								= 20;
	refShip.MinCrew								= 3;
	refShip.SpeedRate							= 12.0;
	refShip.TurnRate							= 70;
	refShip.Price								= 4800;
	refShip.HP									= 400;
	refShip.SP									= 100;
	refship.CanEncounter						= true;
	refship.Type.Merchant						= true;
	refship.Type.War							= true;
	refShip.lowpolycrew							= 3;
	
	refShip.Massa 								= 50000.0;
	refShip.Volume 								= 100.0;

	refship.WaterLine							= 0.1;
	refship.SpeedDependWeight					= 0.2;
	refship.SubSeaDependWeight					= 0.4;
	refship.TurnDependWeight					= 0.2;
    refship.WindAgainstSpeed   					= 1.25;
    
	refship.InertiaAccelerationX	= 3.0;	refship.InertiaBrakingX		= 2.0;
	refship.InertiaAccelerationY	= 14;	refship.InertiaBrakingY		= 5;
	refship.InertiaAccelerationZ	= 5.0;	refship.InertiaBrakingZ		= 3.0;
	
	refShip.Height.Bombs.Y				= 1.0;	refShip.Height.Bombs.DY		= 0.5;
	refShip.Height.Grapes.Y				= 1.8;	refShip.Height.Grapes.DY	= 0.9;
	refShip.Height.Knippels.Y			= 6.7;	refShip.Height.Knippels.DY	= 6.7;
	refShip.Height.Balls.Y				= 1.0;	refShip.Height.Balls.DY		= 0.5;
	
	refship.Track.Enable	= true;
	refship.Track1.ZStart	= 0.20;
	refship.Track1.LifeTime = 9;
	refship.Track1.Width	= "1.0, 2.0";
	refship.Track1.Speed	= "5.2, 6.2";

	refship.Track2.ZStart	= -0.15;
	refship.Track2.LifeTime = 7;
	refship.Track2.Width	= "1.2, 2.0";
	refship.Track2.Speed	= "0.15, 0.25";
	
	refship.nation.england	= true;
	refship.nation.france	= true;
	refship.nation.spain	= true;
	refship.nation.holland	= true;
	refship.nation.pirate	= true;

	///////////////////////////////////////////////////////////////////////////
	//// Барк
	///////////////////////////////////////////////////////////////////////////
	makeref(refShip,ShipsTypes[SHIP_BARQUE]);
	refShip.Name            			= "Barque";
	refship.Soundtype					= "lugger";
	refShip.Class						= 5;
	refShip.Cannon          			= CANNON_TYPE_CANNON_LBS3;
	refShip.MaxCaliber      			= 6;
	refShip.Weight						= Tonnes2CWT(350);
	refShip.Capacity       				= 1500;
	refShip.CannonsQuantity				= 14; // 0,2,6,6    0,2,5,5
	refShip.CannonsQuantityMin			= 12;
	refShip.rcannon 					= 6;
	refShip.lcannon 					= 6;
	refShip.fcannon 					= 0;
	refShip.bcannon 					= 2; 
	refShip.MaxCrew         			= 62;
	refShip.OptCrew         			= 50;
	refShip.MinCrew         			= 26;
	refShip.SpeedRate					= 9.0;
	refShip.TurnRate        			= 30.0;
	refShip.Price           			= 23300;
	refShip.HP              			= 1500;
	refShip.SP              			= 100;
	refship.Type.Merchant				= true;
	refship.Type.War					= false;
	refShip.lowpolycrew 				= 10;

	refship.Rocking.y 					= 0.4;
	refship.Rocking.az 					= 0.025;
	
	refship.WaterLine					= 0.00;
	refship.SpeedDependWeight			= 0.15;
	refship.SubSeaDependWeight			= 0.8;
	refship.TurnDependWeight			= 0.2;
	refship.WindAgainstSpeed   			= 0.7;
	
	refShip.Height.Bombs.Y				= 3.3;	refShip.Height.Bombs.DY		= 1.6;
	refShip.Height.Grapes.Y				= 4.9;	refShip.Height.Grapes.DY	= 2.4;
	refShip.Height.Knippels.Y			= 15.8;	refShip.Height.Knippels.DY	= 12.4;
	refShip.Height.Balls.Y				= 3.3;	refShip.Height.Balls.DY		= 1.6;	
	
	refship.InertiaAccelerationX	= 4.0;	refship.InertiaBrakingX		= 4.0;
	refship.InertiaAccelerationY	= 4;	refship.InertiaBrakingY		= 4.0;
	refship.InertiaAccelerationZ	= 6.0;	refship.InertiaBrakingZ		= 6.0;

	refship.Track.Enable	= true;
	refship.Track1.ZStart	= 0.20;
	refship.Track1.LifeTime = 7.5;
	refship.Track1.Width	= "6.0, 7.0";
	refship.Track1.Speed	= "7.2, 9.2";

	refship.Track2.ZStart	= -0.15;
	refship.Track2.LifeTime = 5.0;
	refship.Track2.Width	= "6.0, 8.0";
	refship.Track2.Speed	= "0.15, 0.25";
	
	refship.nation.england	= true;
	refship.nation.france	= true;
	refship.nation.spain	= true;
	refship.nation.holland	= true;
	refship.nation.pirate	= false;
	
	///////////////////////////////////////////////////////////////////////////
	//// Торговая шхуна
	///////////////////////////////////////////////////////////////////////////
	makeref(refShip,ShipsTypes[SHIP_SCHOONER]);
	refShip.Name            			= "Schooner";
	refship.Soundtype					= "lugger";
	refShip.Class						= 4;
	refShip.Cannon          			= CANNON_TYPE_CANNON_LBS12;
	refShip.MaxCaliber      			= 16;
	refShip.Weight						= Tonnes2CWT(250);
	refShip.Capacity        			= 1700;	

	refShip.CannonsQuantity				= 12; //	нуна буит 5/5/0/2
	refShip.CannonsQuantityMin			= 10;
	refShip.rcannon 					= 5;
	refShip.lcannon 					= 5;
	refShip.fcannon 					= 0;
	refShip.bcannon 					= 2;

	refShip.MaxCrew         			= 75;
	refShip.OptCrew         			= 60;
	refShip.MinCrew         			= 32;	
	refShip.SpeedRate					= 12.5;	
	refShip.TurnRate        			= 50.0;
	refShip.Price           			= 24300;	
	refShip.HP              			= 1250;
	refShip.SP              			= 100;
	refship.Type.Merchant				= true;
	refship.Type.War					= false;
	refShip.lowpolycrew 				= 12;
	
	refship.Rocking.y = 0.4;
	refship.Rocking.az = 0.03;

	refship.WaterLine					= 0.0;
	refship.SpeedDependWeight			= 0.2;
	refship.SubSeaDependWeight			= 0.2;
	refship.TurnDependWeight			= 0.3;
	refship.WindAgainstSpeed   			= 1.10;

	refship.CabinType          			= "Cabin_Medium";
	
	refship.InertiaAccelerationX	= 8.0;	refship.InertiaBrakingX		= 8.0;
	refship.InertiaAccelerationY	= 6;	refship.InertiaBrakingY		= 6;
	refship.InertiaAccelerationZ	= 6.0;	refship.InertiaBrakingZ		= 6.0;
	
	refShip.Height.Bombs.Y				= 1.7;		refShip.Height.Bombs.DY		= 0.8;
	refShip.Height.Grapes.Y				= 2.9;		refShip.Height.Grapes.DY	= 1.4;
	refShip.Height.Knippels.Y			= 13.9;		refShip.Height.Knippels.DY	= 13.7;
	refShip.Height.Balls.Y				= 1.7;		refShip.Height.Balls.DY		= 0.8;

	refship.Track.Enable	= true;
	refship.Track1.ZStart	= 0.20;
	refship.Track1.LifeTime = 8;
	refship.Track1.Width	= "1.2, 2.2";
	refship.Track1.Speed	= "7.2, 8.2";

	refship.Track2.ZStart	= -0.15;
	refship.Track2.LifeTime = 6;
	refship.Track2.Width	= "2.2, 3.2";
	refship.Track2.Speed	= "0.15, 0.25";

	refship.nation.england	= true;
	refship.nation.france	= true;
	refship.nation.spain	= true;
	refship.nation.holland	= true;
	refship.nation.pirate	= false;
	
	///////////////////////////////////////////////////////////////////////////
	//// Баркентина
	///////////////////////////////////////////////////////////////////////////
	makeref(refShip,ShipsTypes[SHIP_BARKENTINE]);
	refShip.Name            			= "Barkentine";
	refship.Soundtype					= "lugger";
	refShip.Class						= 4;
	refShip.Cannon          			= CANNON_TYPE_CANNON_LBS12;
	refShip.MaxCaliber      			= 16;
	refShip.Weight						= Tonnes2CWT(300);
	refShip.Capacity       				= 2000;
	refShip.CannonsQuantity				= 14; // 2,2,5,5     2,2,4,4
	refShip.CannonsQuantityMin			= 12;
	refShip.rcannon 					= 5;
	refShip.lcannon 					= 5;
	refShip.fcannon 					= 2;
	refShip.bcannon 					= 2;
	refShip.MaxCrew         			= 106;
	refShip.OptCrew         			= 85;
	refShip.MinCrew         			= 30;	
	refShip.SpeedRate       			= 11.0;
	refShip.TurnRate        			= 40.0;	
	refShip.Price           			= 31300;	
	refShip.HP              			= 2000;
	refShip.SP              			= 100;	
	refship.Type.Merchant				= true;
	refship.Type.War					= false;	
	refShip.lowpolycrew 				= 12;
	
	refship.Rocking.y 					= 0.5;
	refship.Rocking.az 					= 0.04;
	refship.WaterLine					= 1.15;
	refship.SpeedDependWeight			= 0.27;
	refship.SubSeaDependWeight			= 0.6;
	refship.TurnDependWeight			= 0.3;
	
	refship.WindAgainstSpeed   			= 1.25;
	
	refship.CabinType          			= "Cabin_Medium";
		
	refship.InertiaAccelerationX	= 5.5;	refship.InertiaBrakingX		= 5.5;
	refship.InertiaAccelerationY	= 8;	refship.InertiaBrakingY		= 8;
	refship.InertiaAccelerationZ	= 6.0;	refship.InertiaBrakingZ		= 6.0;
	
	refShip.Height.Bombs.Y				= 3.5;		refShip.Height.Bombs.DY		= 1.7;
	refShip.Height.Grapes.Y				= 4.8;		refShip.Height.Grapes.DY	= 2.4;
	refShip.Height.Knippels.Y			= 16.7;		refShip.Height.Knippels.DY	= 12.8;
	refShip.Height.Balls.Y				= 3.5;		refShip.Height.Balls.DY		= 1.7;
	
	refShip.GeraldSails.rey_b2		= 1;
	refShip.GeraldSails.rey_b3		= 1;
	refShip.GeraldSails.rey_b2.vscale		= 0.8;
	refShip.GeraldSails.rey_b3.vscale		= 0.8;
	
	refship.Track.Enable	= true;
	refship.Track1.ZStart	= 0.20;
	refship.Track1.LifeTime = 12;
	refship.Track1.Width	= "2.0, 3.0";
	refship.Track1.Speed	= "6.0, 8.0";

	refship.Track2.ZStart	= -0.15;
	refship.Track2.LifeTime = 7.5;
	refship.Track2.Width	= "4.0, 6.0";
	refship.Track2.Speed	= "0.15, 0.25";	
	
	refship.nation.england	= true;
	refship.nation.france	= true;
	refship.nation.spain	= true;
	refship.nation.holland	= true;
	refship.nation.pirate	= false;

	///////////////////////////////////////////////////////////////////////////
	//// Шнява
	///////////////////////////////////////////////////////////////////////////
	makeref(refShip,ShipsTypes[SHIP_SHNYAVA]);
	refShip.Name            			= "Shnyava";
	refship.Soundtype					= "lugger";
	refShip.Class						= 4;
	refShip.Cannon          			= CANNON_TYPE_CANNON_LBS16;
	refShip.MaxCaliber      			= 18;
	refShip.Weight						= Tonnes2CWT(350);
	refShip.Capacity       				= 2250;
	refShip.CannonsQuantity				= 16;	// 2,0,7,7	2,0,6,6
	refShip.CannonsQuantityMin			= 14;
	refShip.rcannon 					= 7;
	refShip.lcannon 					= 7;
	refShip.fcannon 					= 2;
	refShip.bcannon 					= 0;
	refShip.MaxCrew         			= 150;
	refShip.OptCrew         			= 120;
	refShip.MinCrew         			= 28;	
	refShip.SpeedRate       			= 13.5;
	refShip.TurnRate        			= 45.0;
	refShip.Price           			= 35200;
	refShip.HP              			= 2200;
	refShip.SP              			= 100;
	
	refship.Type.Merchant				= true;
	refship.Type.War					= false;	
	refShip.lowpolycrew 				= 12;

	refship.Rocking.y 					= 0.5;
	refship.Rocking.az 					= 0.04;
	
	refship.WaterLine					= 1.15;
	refship.SpeedDependWeight			= 0.27;
	refship.SubSeaDependWeight			= 0.6;
	refship.TurnDependWeight			= 0.3;
	refship.WindAgainstSpeed   			= 1.10;
	refship.CabinType          			= "Cabin_Medium"; 
		
	refship.InertiaAccelerationX	= 5.5;	refship.InertiaBrakingX		= 5.5;
	refship.InertiaAccelerationY	= 8;	refship.InertiaBrakingY		= 8;
	refship.InertiaAccelerationZ	= 6.0;	refship.InertiaBrakingZ		= 6.0;
	
	refShip.Height.Bombs.Y				= 3.5;		refShip.Height.Bombs.DY		= 1.7;
	refShip.Height.Grapes.Y				= 4.8;		refShip.Height.Grapes.DY	= 2.4;
	refShip.Height.Knippels.Y			= 16.7;		refShip.Height.Knippels.DY	= 12.8;
	refShip.Height.Balls.Y				= 3.5;		refShip.Height.Balls.DY		= 1.7;
	
	refShip.GeraldSails.rey_b2		= 1;
	refShip.GeraldSails.rey_b3		= 1;
	refShip.GeraldSails.rey_b2.vscale		= 0.8;
	refShip.GeraldSails.rey_b3.vscale		= 0.8;
	
	refship.Track.Enable	= true;
	refship.Track1.ZStart	= 0.20;
	refship.Track1.LifeTime = 12;
	refship.Track1.Width	= "2.0, 3.0";
	refship.Track1.Speed	= "6.0, 8.0";

	refship.Track2.ZStart	= -0.15;
	refship.Track2.LifeTime = 7.5;
	refship.Track2.Width	= "4.0, 6.0";
	refship.Track2.Speed	= "0.15, 0.25";	
	
	refship.nation.england	= true;
	refship.nation.france	= true;
	refship.nation.spain	= true;
	refship.nation.holland	= true;
	refship.nation.pirate	= false;
	
	///////////////////////////////////////////////////////////////////////////
	//// Флейт  
	///////////////////////////////////////////////////////////////////////////
	makeref(refShip,ShipsTypes[SHIP_FLEUT]);
	refShip.Name            			= "Fleut";
	refship.Soundtype					= "corvette";
	refShip.Class						= 4;
	refShip.Cannon          			= CANNON_TYPE_CANNON_LBS12;
	refShip.MaxCaliber      			= 16;	
	refShip.Weight						= Tonnes2CWT(450);	
	refShip.Capacity        			= 3000;	
	refShip.CannonsQuantity				= 16; // 2,2,6,6     2,2,5,5
	refShip.CannonsQuantityMin			= 14;
	refShip.rcannon 					= 6;
	refShip.lcannon 					= 6;
	refShip.fcannon 					= 2;
	refShip.bcannon 					= 2;
	
	refShip.MaxCrew         			= 175;
	refShip.OptCrew         			= 140;
	refShip.MinCrew         			= 40;	
	refShip.SpeedRate					= 13.0;
	refShip.TurnRate        			= 35.0;
	refShip.Price           			= 46800;
	refShip.HP              			= 3000;
	refShip.SP              			= 100;
	refship.Type.Merchant				= true;
	refship.Type.War					= false;
	refShip.lowpolycrew 				= 16;
	
	refship.Rocking.y 					= 0.5;
	refship.Rocking.az 					= 0.035;
	
	refship.WaterLine					= 1.2;
	refship.SpeedDependWeight			= 0.15;
	refship.SubSeaDependWeight			= 0.8;
	refship.TurnDependWeight			= 0.25;
	refship.WindAgainstSpeed   			= 0.65;
	
	refship.CabinType          			= "Cabin_Medium"; 
	refship.DeckType           			= "Medium";
		
	refship.InertiaAccelerationX	= 4.5;	refship.InertiaBrakingX		= 4.5;
	refship.InertiaAccelerationY	= 6;	refship.InertiaBrakingY		= 6;
	refship.InertiaAccelerationZ	= 4.0;	refship.InertiaBrakingZ		= 4.0;
	
	refShip.Height.Bombs.Y				= 3.4;		refShip.Height.Bombs.DY		= 1.7;
	refShip.Height.Grapes.Y				= 5.0;		refShip.Height.Grapes.DY	= 2.5;
	refShip.Height.Knippels.Y			= 17.8;		refShip.Height.Knippels.DY	= 13.3;
	refShip.Height.Balls.Y				= 3.4;		refShip.Height.Balls.DY		= 1.7;

	refship.Track.Enable	= true;
	refship.Track1.ZStart	= 0.20;
	refship.Track1.LifeTime = 12;
	refship.Track1.Width	= "2.0, 3.0";
	refship.Track1.Speed	= "8.0, 8.0";

	refship.Track2.ZStart	= -0.15;
	refship.Track2.LifeTime = 7.5;
	refship.Track2.Width	= "6.0, 8.0";
	refship.Track2.Speed	= "0.15, 0.25";
	
	refship.nation.england	= true;
	refship.nation.france	= true;
	refship.nation.spain	= true;
	refship.nation.holland	= true;
	refship.nation.pirate	= false;
		
	///////////////////////////////////////////////////////////////////////////
	//// Каравелла
	///////////////////////////////////////////////////////////////////////////
	makeref(refShip,ShipsTypes[SHIP_CARAVEL]);
	refShip.Name            			= "Caravel";
	refship.Soundtype					= "corvette";
	refShip.Class						= 3;
	refShip.Cannon          			= CANNON_TYPE_CANNON_LBS16;
	refShip.MaxCaliber      			= 20;
	refShip.Weight						= Tonnes2CWT(850);
	refShip.Capacity        			= 3500;
	refShip.CannonsQuantity				= 20; // 2,2,8,8    2,2,7,7
	refShip.CannonsQuantityMin			= 18;
	refShip.rcannon 					= 8;
	refShip.lcannon 					= 8;
	refShip.fcannon 					= 2;
	refShip.bcannon 					= 2;	
	refShip.MaxCrew         			= 225;
	refShip.OptCrew         			= 180;
	refShip.MinCrew         			= 48;	
	refShip.SpeedRate					= 11.0;
	refShip.TurnRate        			= 25.0;
	refShip.Price           			= 53200;	
	refShip.HP              			= 3200;
	refShip.SP              			= 100;

	refship.Type.Merchant				= true;
	refship.Type.War					= false;	
	refShip.lowpolycrew 				= 16;

	refship.Rocking.y 					= 0.5;
	refship.Rocking.az 					= 0.035;
	refship.CabinType          			= "Cabin_Medium"; 
	refship.DeckType           			= "Medium";
	
	refship.WaterLine					= 1.0;
	refship.SpeedDependWeight			= 0.15;
	refship.SubSeaDependWeight			= 0.6;
	refship.TurnDependWeight			= 0.2;
	refship.WindAgainstSpeed   			= 1.25;
	
	refship.InertiaAccelerationX	= 3.0;	refship.InertiaBrakingX		= 3.0;
	refship.InertiaAccelerationY	= 3;	refship.InertiaBrakingY		= 3;
	refship.InertiaAccelerationZ	= 3.0;	refship.InertiaBrakingZ		= 3.0;
	
	refShip.Height.Bombs.Y				= 2.7;	refShip.Height.Bombs.DY		= 1.3;
	refShip.Height.Grapes.Y				= 4.3;	refShip.Height.Grapes.DY	= 2.1;
	refShip.Height.Knippels.Y			= 13.0;	refShip.Height.Knippels.DY	= 11.7;
	refShip.Height.Balls.Y				= 2.7;	refShip.Height.Balls.DY		= 1.3;
	
	refship.Track.Enable	= true;
	refship.Track1.ZStart	= 0.20;
	refship.Track1.LifeTime = 10;
	refship.Track1.Width	= "4.0, 5.0";
	refship.Track1.Speed	= "7.2, 9.2";

	refship.Track2.ZStart	= -0.15;
	refship.Track2.LifeTime = 7.5;
	refship.Track2.Width	= "5.0, 7.0";
	refship.Track2.Speed	= "0.15, 0.25";
	
	refship.nation.england	= true;
	refship.nation.france	= true;
	refship.nation.spain	= true;
	refship.nation.holland	= true;
	refship.nation.pirate	= false;
	
	///////////////////////////////////////////////////////////////////////////
	//// Пинас
	///////////////////////////////////////////////////////////////////////////
	makeref(refShip,ShipsTypes[SHIP_PINNACE]);
	refShip.Name            			= "Pinnace";
	refship.Soundtype					= "frigate";
	refShip.Class						= 3;
	refShip.Cannon          			= CANNON_TYPE_CANNON_LBS12;
	refShip.MaxCaliber      			= 18;	
	refShip.Weight						= Tonnes2CWT(800);	
	refShip.Capacity        			= 4500;	
	refShip.CannonsQuantity				= 18; // 2,4,6,6	2,4,5,5
	refShip.CannonsQuantityMin			= 16;
	refShip.rcannon 					= 6;
	refShip.lcannon 					= 6;
	refShip.fcannon 					= 2;
	refShip.bcannon 					= 4;		
	refShip.MaxCrew						= 200;
	refShip.OptCrew         			= 160;
	refShip.MinCrew         			= 42;	
	refShip.SpeedRate					= 14.0;
	refShip.TurnRate        			= 35.0;
	refShip.Price           			= 68000;
	refShip.HP              			= 4200;
	refShip.SP              			= 100;	
	refship.Type.Merchant				= true;
	refship.Type.War					= false;
	
	refShip.lowpolycrew 				= 20;

	refship.Rocking.y 					= 0.4;
	refship.Rocking.az 					= 0.035;

	refship.WaterLine					= 0.4;
	refship.SpeedDependWeight			= 0.2;
	refship.SubSeaDependWeight			= 1.3;
	refship.TurnDependWeight			= 0.25;
	refship.WindAgainstSpeed   			= 0.65;
    refship.CabinType          			= "Cabin_Medium2";
    refship.DeckType           			= "Medium";
	
	refship.InertiaAccelerationX	= 3.0;	refship.InertiaBrakingX		= 3.0;
	refship.InertiaAccelerationY	= 4;	refship.InertiaBrakingY		= 4;
	refship.InertiaAccelerationZ	= 3.0;	refship.InertiaBrakingZ		= 3.0;

	refShip.Height.Bombs.Y				= 3.0;		refShip.Height.Bombs.DY		= 1.5;
	refShip.Height.Grapes.Y				= 5.5;		refShip.Height.Grapes.DY	= 2.7;
	refShip.Height.Knippels.Y			= 24.1;		refShip.Height.Knippels.DY	= 20.7;
	refShip.Height.Balls.Y				= 3.0;		refShip.Height.Balls.DY		= 1.5;	
	
	refShip.GeraldSails.rey_b2		= 1;
	refShip.GeraldSails.rey_b3		= 1;
	refShip.GeraldSails.rey_b1		= 1;
	refShip.GeraldSails.rey_b1.vscale		= 0.85;
	refShip.GeraldSails.rey_b2.vscale		= 0.65;
	refShip.GeraldSails.rey_b3.vscale		= 0.65;

	refship.Track.Enable	= true;
	refship.Track1.ZStart	= 0.30;
	refship.Track1.LifeTime = 14.5;
	refship.Track1.Width	= "5.7, 7.9";
	refship.Track1.Speed	= "6.0, 8.0";

	refship.Track2.ZStart	= -0.15;
	refship.Track2.LifeTime = 8.5;
	refship.Track2.Width	= "10.0, 12.0";
	refship.Track2.Speed	= "0.15, 0.25";
	
	refship.nation.england	= true;
	refship.nation.france	= true;
	refship.nation.spain	= true;
	refship.nation.holland	= true;
	refship.nation.pirate	= false;

	///////////////////////////////////////////////////////////////////////////
	//// Каракка
	///////////////////////////////////////////////////////////////////////////
	makeref(refShip,ShipsTypes[SHIP_CARACCA]);
	refShip.Name            			= "Caracca";
	refship.Soundtype					= "corvette";
	refShip.Class						= 3;
	refShip.Cannon          			= CANNON_TYPE_CANNON_LBS12;
	refShip.MaxCaliber      			= 18;	
	refShip.Weight						= Tonnes2CWT(750);
	refShip.Capacity        			= 4000;
	refShip.CannonsQuantity				= 20; // 2,2,8,8	2,2,7,7
	refShip.CannonsQuantityMin			= 18;
	refShip.rcannon 					= 8;
	refShip.lcannon 					= 8;
	refShip.fcannon 					= 2;
	refShip.bcannon 					= 2;	
	refShip.MaxCrew         			= 250;
	refShip.OptCrew         			= 200;
	refShip.MinCrew         			= 52;	
	refShip.SpeedRate					= 13.0;
	refShip.TurnRate        			= 30.0;
	refShip.Price           			= 60900;
	refShip.HP              			= 3700;
	refShip.SP              			= 100;
	
	refship.Type.Merchant				= true;
	refship.Type.War					= false;	
	refShip.lowpolycrew 				= 16;
	
	refship.Rocking.y 					= 0.45;
	refship.Rocking.az 					= 0.035;
	
	refship.WaterLine					= 0.6;
	refship.SpeedDependWeight			= 0.15;
	refship.SubSeaDependWeight			= 0.95;
	refship.TurnDependWeight			= 0.2;
	refship.WindAgainstSpeed   			= 0.75;
	
	refship.CabinType          			= "Cabin_Medium2"; // boal 28.03.05
	refship.DeckType           			= "Medium";
		
	refship.InertiaAccelerationX	= 4.0;	refship.InertiaBrakingX		= 4.0;
	refship.InertiaAccelerationY	= 6;	refship.InertiaBrakingY		= 6;
	refship.InertiaAccelerationZ	= 4.0;	refship.InertiaBrakingZ		= 4.0;
	
	refShip.Height.Bombs.Y				= 4.3;		refShip.Height.Bombs.DY		= 2.1;
	refShip.Height.Grapes.Y				= 5.6;		refShip.Height.Grapes.DY	= 2.8;
	refShip.Height.Knippels.Y			= 18.7;		refShip.Height.Knippels.DY	= 12.7;
	refShip.Height.Balls.Y				= 4.3;		refShip.Height.Balls.DY		= 2.1;
	
	refShip.GeraldSails.rey_b2				= 1;
	refShip.GeraldSails.rey_b3				= 1;
	refShip.GeraldSails.rey_b2.vscale		= 0.7;
	refShip.GeraldSails.rey_b3.vscale		= 0.7;

	refship.Track.Enable	= true;
	refship.Track1.ZStart	= 0.20;
	refship.Track1.LifeTime = 16.5;
	refship.Track1.Width	= "5.2, 7.3";
	refship.Track1.Speed	= "6.0, 8.0";

	refship.Track2.ZStart	= -0.15;
	refship.Track2.LifeTime = 10.5;
	refship.Track2.Width	= "6.0, 8.0";
	refship.Track2.Speed	= "0.15, 0.25";
	
	refship.nation.england	= true;
	refship.nation.france	= true;
	refship.nation.spain	= true;
	refship.nation.holland	= true;
	refship.nation.pirate	= false;

	///////////////////////////////////////////////////////////////////////////
	//// Навио
	///////////////////////////////////////////////////////////////////////////
	makeref(refShip,ShipsTypes[SHIP_NAVIO]);
	refShip.Name            			= "Navio";
	refship.Soundtype					= "frigate";
	refShip.Class						= 2;
	refShip.Cannon          			= CANNON_TYPE_CANNON_LBS20;
	refShip.MaxCaliber      			= 20;
	refShip.Weight						= Tonnes2CWT(1100);
	refShip.Capacity        			= 5000;
	refShip.CannonsQuantity				= 36; // 2,4,14,14	2,4,13,13	2,4,12,12
	refShip.CannonsQuantityMin			= 32;
	refShip.rcannon 					= 15;
	refShip.lcannon 					= 15;
	refShip.fcannon 					= 2;
	refShip.bcannon 					= 4;
	refShip.MaxCrew         			= 350;
	refShip.OptCrew         			= 280;
	refShip.MinCrew         			= 62;	
	refShip.SpeedRate					= 12.0;
	refShip.TurnRate        			= 32.0;
	refShip.Price           			= 77400;
	refShip.HP              			= 4800;
	refShip.SP              			= 100;
	refship.Type.Merchant				= true;
	refship.Type.War					= false;
	
	refShip.lowpolycrew 				= 20;
	
	refship.Rocking.y 					= 0.4;
	refship.Rocking.az 					= 0.02;
	
	refship.WaterLine					= -0.2;

	refship.SpeedDependWeight			= 0.15;
	refship.SubSeaDependWeight			= 0.3;
	refship.TurnDependWeight			= 0.2;
	refship.WindAgainstSpeed   			= 0.60;
	
	refship.CabinType          			= "Cabin"; 
	refship.DeckType           			= "Big";
	
	refship.InertiaAccelerationX	= 4.5;	refship.InertiaBrakingX		= 4.5;
	refship.InertiaAccelerationY	= 3;	refship.InertiaBrakingY		= 3;
	refship.InertiaAccelerationZ	= 4.5;	refship.InertiaBrakingZ		= 4.5;

	refShip.Height.Bombs.Y				= 3.0;		refShip.Height.Bombs.DY		= 1.5;
	refShip.Height.Grapes.Y				= 4.4;		refShip.Height.Grapes.DY	= 2.2;
	refShip.Height.Knippels.Y			= 21.4;		refShip.Height.Knippels.DY	= 19.8;
	refShip.Height.Balls.Y				= 3.0;		refShip.Height.Balls.DY		= 1.5;
	
	refShip.GeraldSails.rey_b2		= 1;
	refShip.GeraldSails.rey_b3		= 1;
	refShip.GeraldSails.rey_b2.vscale		= 0.98;
	refShip.GeraldSails.rey_b3.vscale		= 0.8;

	refship.Track.Enable	= true;
	refship.Track1.ZStart	= 0.0;
	refship.Track1.LifeTime = 14.5;
	refship.Track1.Width	= "5.2, 7.3";
	refship.Track1.Speed	= "5.5, 6.5";

	refship.Track2.ZStart	= -0.15;
	refship.Track2.LifeTime = 8.5;
	refship.Track2.Width	= "6.0, 8.0";
	refship.Track2.Speed	= "0.15, 0.25";	
	
	refship.nation.england	= true;
	refship.nation.france	= true;
	refship.nation.spain	= true;
	refship.nation.holland	= true;
	refship.nation.pirate	= false;
	
	///////////////////////////////////////////////////////////////////////////
	//// Ост-Индец
	///////////////////////////////////////////////////////////////////////////
	makeref(refShip,ShipsTypes[SHIP_EASTINDIAMAN]);
	refShip.Name            			= "EastIndiaMan";
	refship.Soundtype					= "frigate";
	refShip.Class						= 2;
	refShip.Cannon          			= CANNON_TYPE_CANNON_LBS20;
	refShip.MaxCaliber      			= 24;
	refShip.Weight						= Tonnes2CWT(1000);
	refShip.Capacity        			= 5800;
	refShip.CannonsQuantity				= 36;	// 0,6,15,15	0,6,14,14	0,6,13,13
	refShip.CannonsQuantityMin			= 32;
	refShip.rcannon 					= 15;
	refShip.lcannon 					= 15;
	refShip.fcannon 					= 0;
	refShip.bcannon 					= 6;	
	refShip.MaxCrew         			= 425;
	refShip.OptCrew         			= 340;
	refShip.MinCrew         			= 76;	
	refShip.SpeedRate					= 13.5;
	refShip.TurnRate        			= 30.0;
	refShip.Price           			= 88000;
	refShip.HP              			= 5200;
	refShip.SP              			= 100;

	refship.Type.Merchant				= true;
	refship.Type.War					= false;	
	refShip.lowpolycrew 				= 20;
	
	refship.Rocking.y 					= 0.4;
	refship.Rocking.az 					= 0.02;
	
	refship.WaterLine					= -0.5;

	refship.SpeedDependWeight			= 0.15;
	refship.SubSeaDependWeight			= 0.3;
	refship.TurnDependWeight			= 0.2;
	refship.WindAgainstSpeed   			= 0.55;
	
	refship.CabinType          			= "Cabin"; 
	refship.DeckType           			= "Big";
	
	refship.InertiaAccelerationX	= 4.5;	refship.InertiaBrakingX		= 4.5;
	refship.InertiaAccelerationY	= 3;	refship.InertiaBrakingY		= 3;
	refship.InertiaAccelerationZ	= 4.5;	refship.InertiaBrakingZ		= 4.5;

	refShip.Height.Bombs.Y				= 3.0;		refShip.Height.Bombs.DY		= 1.5;
	refShip.Height.Grapes.Y				= 4.4;		refShip.Height.Grapes.DY	= 2.2;
	refShip.Height.Knippels.Y			= 21.4;		refShip.Height.Knippels.DY	= 19.8;
	refShip.Height.Balls.Y				= 3.0;		refShip.Height.Balls.DY		= 1.5;
	
	refShip.GeraldSails.rey_b2				= 1;
	refShip.GeraldSails.rey_b3				= 1;
	refShip.GeraldSails.rey_b2.vscale		= 0.98;
	refShip.GeraldSails.rey_b3.vscale		= 0.8;

	refship.Track.Enable	= true;
	refship.Track1.ZStart	= 0.0;
	refship.Track1.LifeTime = 14.5;
	refship.Track1.Width	= "5.2, 7.3";
	refship.Track1.Speed	= "5.5, 6.5";

	refship.Track2.ZStart	= -0.15;
	refship.Track2.LifeTime = 8.5;
	refship.Track2.Width	= "6.0, 8.0";
	refship.Track2.Speed	= "0.15, 0.25";
	
	refship.nation.england	= true;
	refship.nation.france	= true;
	refship.nation.spain	= true;
	refship.nation.holland	= true;
	refship.nation.pirate	= false;
	
	///////////////////////////////////////////////////////////////////////////
	//// Курьерский люггер
	///////////////////////////////////////////////////////////////////////////
	makeref(refShip,ShipsTypes[SHIP_CAREERLUGGER]);
	refShip.Name            			= "LuggerQuest";
	refship.Soundtype					= "lugger";
	refShip.Class						= 5;
	refShip.Cannon          			= CANNON_TYPE_CANNON_LBS6;
	refShip.MaxCaliber      			= 12;
	refShip.Weight						= Tonnes2CWT(120);	
	refShip.Capacity        			= 550;
	refShip.CannonsQuantity				= 10; // 0,2,4,4	0,2,3,3
	refShip.CannonsQuantityMin			= 8;
	refShip.rcannon 					= 4;
	refShip.lcannon 					= 4;
	refShip.fcannon 					= 0;
	refShip.bcannon 					= 2;	
	refShip.MaxCrew         			= 37;
	refShip.OptCrew         			= 30;
	refShip.MinCrew         			= 8;	
	refShip.SpeedRate       			= 16.0;
	refShip.TurnRate        			= 65.0;
	refShip.Price           			= 10100;
	refShip.HP              			= 750;
	refShip.SP              			= 100;
	
	refship.Type.Merchant				= false;
	refship.Type.War					= true;	
	refShip.lowpolycrew 				= 8;

	refship.Rocking.y 					= 0.5;
	refship.Rocking.az 					= 0.035;

	refship.WaterLine					= 0.0;
	refship.SpeedDependWeight			= 0.2;
	refship.SubSeaDependWeight			= 0.6;
	refship.TurnDependWeight			= 0.2;
	refship.WindAgainstSpeed   			= 1.60;
	
	refship.InertiaAccelerationX	= 10.0;	refship.InertiaBrakingX		= 10.0;
	refship.InertiaAccelerationY	= 10;	refship.InertiaBrakingY		= 10;
	refship.InertiaAccelerationZ	= 10.0;	refship.InertiaBrakingZ		= 10.0;
	
	refShip.Height.Bombs.Y				= 1.65;	refShip.Height.Bombs.DY		= 1.35;
	refShip.Height.Grapes.Y				= 2.64;	refShip.Height.Grapes.DY	= 0.5;
	refShip.Height.Knippels.Y			= 14.64; refShip.Height.Knippels.DY	= 13.5;
	refShip.Height.Balls.Y				= 1.65;	refShip.Height.Balls.DY		= 1.35;

	refship.Track.Enable	= true;
	refship.Track1.ZStart	= 0.20;
	refship.Track1.LifeTime = 9;
	refship.Track1.Width	= "2.0, 3.0";
	refship.Track1.Speed	= "8.0, 10.0";

	refship.Track2.ZStart	= -0.15;
	refship.Track2.LifeTime = 7;
	refship.Track2.Width	= "3.0, 4.5";
	refship.Track2.Speed	= "0.15, 0.25";
	
	refship.nation.england	= true;
	refship.nation.france	= true;
	refship.nation.spain	= true;
	refship.nation.holland	= true;
	refship.nation.pirate	= false;

	///////////////////////////////////////////////////////////////////////////
	//// Люггер
	///////////////////////////////////////////////////////////////////////////
	makeref(refShip,ShipsTypes[SHIP_LUGGER]);
	refShip.Name            			= "Lugger";
	refship.Soundtype					= "lugger";
	refShip.Class						= 5;
	refShip.Cannon          			= CANNON_TYPE_CANNON_LBS3;
	refShip.MaxCaliber      			= 6;
	refShip.Weight						= Tonnes2CWT(150);
	refShip.Capacity        			= 670;
	refShip.CannonsQuantity				= 12;	//2,2,4,4	2,2,3,3
	refShip.CannonsQuantityMin			= 10;
	refShip.rcannon 					= 4;
	refShip.lcannon 					= 4;
	refShip.fcannon 					= 2;
	refShip.bcannon 					= 2;		
	refShip.MaxCrew         			= 50;
	refShip.OptCrew         			= 40;
	refShip.MinCrew         			= 8;	
	refShip.SpeedRate       			= 15.0;
	refShip.TurnRate        			= 60.0;
	refShip.Price           			= 10600;
	refShip.HP              			= 600;
	refShip.SP              			= 100;
	
	refship.Type.Merchant				= false;
	refship.Type.War					= true;	
	refShip.lowpolycrew 				= 8;

	refship.Rocking.y 					= 0.5;
	refship.Rocking.az 					= 0.035;

	refship.WaterLine					= 0.2;
	refship.SpeedDependWeight			= 0.2;
	refship.SubSeaDependWeight			= 0.6;
	refship.TurnDependWeight			= 0.2;
	refship.WindAgainstSpeed   			= 1.50;
	
	refship.InertiaAccelerationX	= 10.0;	refship.InertiaBrakingX		= 10.0;
	refship.InertiaAccelerationY	= 10;	refship.InertiaBrakingY		= 10;
	refship.InertiaAccelerationZ	= 10.0;	refship.InertiaBrakingZ		= 10.0;
	
	refShip.Height.Bombs.Y				= 2.1;	refShip.Height.Bombs.DY		= 1.0;
	refShip.Height.Grapes.Y				= 3.1;	refShip.Height.Grapes.DY	= 1.5;
	refShip.Height.Knippels.Y			= 10.5;	refShip.Height.Knippels.DY	= 8.5;
	refShip.Height.Balls.Y				= 2.1;	refShip.Height.Balls.DY		= 1.0;

	refship.Track.Enable	= true;
	refship.Track1.ZStart	= 0.20;
	refship.Track1.LifeTime = 9;
	refship.Track1.Width	= "2.0, 3.0";
	refship.Track1.Speed	= "8.0, 10.0";

	refship.Track2.ZStart	= -0.15;
	refship.Track2.LifeTime = 7;
	refship.Track2.Width	= "3.0, 4.5";
	refship.Track2.Speed	= "0.15, 0.25";
	
	refship.nation.england	= true;
	refship.nation.france	= true;
	refship.nation.spain	= true;
	refship.nation.holland	= true;
	refship.nation.pirate	= true;
	
	///////////////////////////////////////////////////////////////////////////
	//// Шлюп
	///////////////////////////////////////////////////////////////////////////
	makeref(refShip,ShipsTypes[SHIP_SLOOP]);
	refShip.Name            			= "Sloop";
	refship.Soundtype					= "lugger";
	refShip.Class						= 5;
	refShip.Cannon          			= CANNON_TYPE_CANNON_LBS6;
	refShip.MaxCaliber      			= 12;
	refShip.Weight						= Tonnes2CWT(170);
	refShip.Capacity        			= 900;	
	refShip.CannonsQuantity				= 14; // 2,2,5,5	2,2,4,4
	refShip.CannonsQuantityMin			= 12;
	refShip.rcannon 					= 5;
	refShip.lcannon 					= 5;
	refShip.fcannon 					= 2;
	refShip.bcannon 					= 2;
	
	refShip.MaxCrew         			= 62;
	refShip.OptCrew         			= 50;
	refShip.MinCrew         			= 10;	
	refShip.SpeedRate					= 14.0;
	refShip.TurnRate        			= 55.0;
	refShip.Price           			= 14500;
	refShip.HP              			= 900;
	refShip.SP              			= 100;

	refship.Type.Merchant				= true;
	refship.Type.War					= true;	
	refShip.lowpolycrew 				= 8;
	
	refship.Rocking.y 					= 0.45;
	refship.Rocking.az 					= 0.02;
	
	refship.WaterLine					= 0.0;

	refship.SpeedDependWeight			= 0.2;
	refship.SubSeaDependWeight			= 0.3;
	refship.TurnDependWeight			= 0.3;
	
	refship.WindAgainstSpeed   			= 1.30;

	refShip.Height.Bombs.Y				= 1.6;	refShip.Height.Bombs.DY		= 1.25;
	refShip.Height.Grapes.Y				= 2.75;	refShip.Height.Grapes.DY	= 0.6;
	refShip.Height.Knippels.Y			= 13.2;	refShip.Height.Knippels.DY	= 8.5;
	refShip.Height.Balls.Y				= 1.6;	refShip.Height.Balls.DY		= 1.25;
	
	refship.InertiaAccelerationX	= 8.0;	refship.InertiaBrakingX		= 8.0;
	refship.InertiaAccelerationY	= 8;	refship.InertiaBrakingY		= 8;
	refship.InertiaAccelerationZ	= 8.0;	refship.InertiaBrakingZ		= 8.0;

	refship.Track.Enable	= true;
	refship.Track1.ZStart	= 0.20;
	refship.Track1.LifeTime = 9;
	refship.Track1.Width	= "2.0, 2.5";
	refship.Track1.Speed	= "5.2, 6.2";

	refship.Track2.ZStart	= -0.05;
	refship.Track2.LifeTime = 7;
	refship.Track2.Width	= "3.0, 4.0";
	refship.Track2.Speed	= "0.15, 0.25";
	
	refship.nation.england	= true;
	refship.nation.france	= true;
	refship.nation.spain	= true;
	refship.nation.holland	= true;
	refship.nation.pirate	= true;
	
	///////////////////////////////////////////////////////////////////////////
	//// Бригантина 
	///////////////////////////////////////////////////////////////////////////
	makeref(refShip,ShipsTypes[SHIP_BRIGANTINE]);
	refShip.Name            			= "Brigantine";
	refship.Soundtype					= "corvette";
	refShip.Class						= 4;
	refShip.Cannon          			= CANNON_TYPE_CANNON_LBS16;
	refShip.MaxCaliber      			= 18;	
	refShip.Weight						= Tonnes2CWT(320);	
	refShip.Capacity        			= 1800;
	refShip.CannonsQuantity				= 16; // 2,0,7,7	2,0,6,6
	refShip.CannonsQuantityMin			= 14;
	refShip.rcannon 					= 7;
	refShip.lcannon 					= 7;
	refShip.fcannon 					= 2;
	refShip.bcannon 					= 0;		
	refShip.MaxCrew         			= 175;
	refShip.OptCrew         			= 140;
	refShip.MinCrew         			= 16;	
	refShip.SpeedRate       			= 14.0;
	refShip.TurnRate        			= 50.0;
	refShip.Price           			= 33900;
	refShip.HP              			= 2800;
	refShip.SP              			= 100;

	refship.Type.Merchant				= false;
	refship.Type.War					= true;	
	refShip.lowpolycrew 				= 12;

	refship.Rocking.y 					= 0.5;
	refship.Rocking.az 					= 0.04;
	
	refship.WaterLine					= 0.0;
	refship.SpeedDependWeight			= 0.27;
	refship.SubSeaDependWeight			= 0.6;
	refship.TurnDependWeight			= 0.3;
	refship.WindAgainstSpeed   			= 1.40;
	
	refship.CabinType          			= "Cabin_Medium"; 

	refship.InertiaAccelerationX	= 5.5;	refship.InertiaBrakingX		= 5.5;
	refship.InertiaAccelerationY	= 8;	refship.InertiaBrakingY		= 8;
	refship.InertiaAccelerationZ	= 6.0;	refship.InertiaBrakingZ		= 6.0;
	
	refShip.Height.Bombs.Y				= 2.0;		refShip.Height.Bombs.DY		= 1.0;
	refShip.Height.Grapes.Y				= 3.4;		refShip.Height.Grapes.DY	= 1.7;
	refShip.Height.Knippels.Y			= 13.2;		refShip.Height.Knippels.DY	= 11.6;
	refShip.Height.Balls.Y				= 2.0;		refShip.Height.Balls.DY		= 1.0;
	
	refShip.GeraldSails.rey_b2		= 1;
	refShip.GeraldSails.rey_b3		= 1;
	refShip.GeraldSails.rey_b2.vscale		= 0.8;
	refShip.GeraldSails.rey_b3.vscale		= 0.8;
	
	refship.Track.Enable	= true;
	refship.Track1.ZStart	= 0.20;
	refship.Track1.LifeTime = 12;
	refship.Track1.Width	= "2.0, 3.0";
	refship.Track1.Speed	= "6.0, 8.0";

	refship.Track2.ZStart	= -0.15;
	refship.Track2.LifeTime = 7.5;
	refship.Track2.Width	= "4.0, 6.0";
	refship.Track2.Speed	= "0.15, 0.25";
	
	refship.nation.england	= false;
	refship.nation.france	= false
	refship.nation.spain	= true;;
	refship.nation.holland	= false;
	refship.nation.pirate	= true;
    	
	///////////////////////////////////////////////////////////////////////////
	//// Бриг
	///////////////////////////////////////////////////////////////////////////
	makeref(refShip,ShipsTypes[SHIP_BRIG]);
	refShip.Name            			= "Brig";
	refship.Soundtype					= "lugger";
	refShip.Class						= 4;
	refShip.Cannon          			= CANNON_TYPE_CANNON_LBS16;
	refShip.MaxCaliber      			= 18;
	refShip.Weight						= Tonnes2CWT(300);
	refShip.Capacity        			= 1350;
	refShip.CannonsQuantity				= 16; // 2,2,6,6	2,2,5,5
	refShip.CannonsQuantityMin			= 14;
	refShip.rcannon 					= 6;
	refShip.lcannon 					= 6;
	refShip.fcannon 					= 2;
	refShip.bcannon 					= 2;	
	refShip.MaxCrew         			= 150;
	refShip.OptCrew         			= 120;
	refShip.MinCrew         			= 20;
	
	refShip.SpeedRate       			= 14.5;
	refShip.TurnRate        			= 45.0;
	refShip.Price           			= 27700;
	refShip.HP              			= 2500;
	refShip.SP              			= 100;
	
	refship.Type.Merchant				= false;
	refship.Type.War					= true;	
	refShip.lowpolycrew 				= 12;

	refship.Rocking.y 					= 0.5;
	refship.Rocking.az 					= 0.04;
	
	refship.WaterLine					= 0.0;
	refship.SpeedDependWeight			= 0.27;
	refship.SubSeaDependWeight			= 0.6;
	refship.TurnDependWeight			= 0.3;
	refship.WindAgainstSpeed   			= 0.55;
	refship.CabinType          			= "Cabin_Medium"; // boal 28.03.05
	
	refship.InertiaAccelerationX	= 5.5;	refship.InertiaBrakingX		= 5.5;
	refship.InertiaAccelerationY	= 8;	refship.InertiaBrakingY		= 8;
	refship.InertiaAccelerationZ	= 6.0;	refship.InertiaBrakingZ		= 6.0;
	
	refShip.Height.Bombs.Y				= 2.0;		refShip.Height.Bombs.DY		= 2.0;
	refShip.Height.Grapes.Y				= 3.3;		refShip.Height.Grapes.DY	= 1.6;
	refShip.Height.Knippels.Y			= 14.9;		refShip.Height.Knippels.DY	= 14.0;
	refShip.Height.Balls.Y				= 2.0;		refShip.Height.Balls.DY		= 2.0;
	
	refShip.GeraldSails.rey_b2		= 1;
	refShip.GeraldSails.rey_b3		= 1;
	refShip.GeraldSails.rey_b2.vscale		= 0.8;
	refShip.GeraldSails.rey_b3.vscale		= 0.8;
	
	refship.Track.Enable	= true;
	refship.Track1.ZStart	= 0.20;
	refship.Track1.LifeTime = 12;
	refship.Track1.Width	= "2.0, 3.0";
	refship.Track1.Speed	= "6.0, 8.0";

	refship.Track2.ZStart	= -0.15;
	refship.Track2.LifeTime = 7.5;
	refship.Track2.Width	= "4.0, 6.0";
	refship.Track2.Speed	= "0.15, 0.25";
	
	refship.nation.england	= true;
	refship.nation.france	= false;
	refship.nation.spain	= false;
	refship.nation.holland	= false;
	refship.nation.pirate	= true;

	///////////////////////////////////////////////////////////////////////////
	//// Военная шхуна
	///////////////////////////////////////////////////////////////////////////
	makeref(refShip,ShipsTypes[SHIP_SCHOONER_W]);
	refShip.Name            			= "Schooner_W";
	refship.Soundtype					= "lugger";
	refShip.Class						= 4;
	refShip.Cannon          			= CANNON_TYPE_CANNON_LBS12;
	refShip.MaxCaliber      			= 18;	
	
	refShip.Weight						= Tonnes2CWT(220);
	refShip.Capacity        			= 1350;
	refShip.CannonsQuantity				= 18; // 2,2,7,7	2,2,6,6
	refShip.CannonsQuantityMin			= 16;
	refShip.rcannon 					= 7;
	refShip.lcannon 					= 7;
	refShip.fcannon 					= 2;
	refShip.bcannon 					= 2;	
	refShip.MaxCrew         			= 122;
	refShip.OptCrew         			= 98;
	refShip.MinCrew         			= 18;
	refShip.SpeedRate					= 13.5;
	refShip.TurnRate        			= 55.0;
	refShip.Price           			= 22300;
	refShip.HP              			= 1450;
	refShip.SP              			= 100;	
	refship.Type.Merchant				= false;
	refship.Type.War					= true;
	
	refShip.lowpolycrew 				= 12;

	refship.Rocking.y 					= 0.4;
	refship.Rocking.az 					= 0.03;

	refship.WaterLine					= 0.0;

	refship.SpeedDependWeight			= 0.2;
	refship.SubSeaDependWeight			= 0.2;
	refship.TurnDependWeight			= 0.3;
	refship.WindAgainstSpeed   			= 1.15;
	
	refship.CabinType          			= "Cabin_Medium";
	
	refship.InertiaAccelerationX	= 8.0;	refship.InertiaBrakingX		= 8.0;
	refship.InertiaAccelerationY	= 6;	refship.InertiaBrakingY		= 6;
	refship.InertiaAccelerationZ	= 6.0;	refship.InertiaBrakingZ		= 6.0;
	
	refShip.Height.Bombs.Y				= 1.7;		refShip.Height.Bombs.DY		= 0.8;
	refShip.Height.Grapes.Y				= 2.9;		refShip.Height.Grapes.DY	= 1.4;
	refShip.Height.Knippels.Y			= 13.9;		refShip.Height.Knippels.DY	= 13.7;
	refShip.Height.Balls.Y				= 1.7;		refShip.Height.Balls.DY		= 0.8;

	refship.Track.Enable	= true;
	refship.Track1.ZStart	= 0.20;
	refship.Track1.LifeTime = 8;
	refship.Track1.Width	= "1.2, 2.2";
	refship.Track1.Speed	= "7.2, 8.2";

	refship.Track2.ZStart	= -0.15;
	refship.Track2.LifeTime = 6;
	refship.Track2.Width	= "2.2, 3.2";
	refship.Track2.Speed	= "0.15, 0.25";
	
	refship.nation.england	= false;
	refship.nation.france	= true;
	refship.nation.spain	= false;
	refship.nation.holland	= true;
	refship.nation.pirate	= true;
	
	///////////////////////////////////////////////////////////////////////////
	//// Галеон 
	///////////////////////////////////////////////////////////////////////////
	makeref(refShip,ShipsTypes[SHIP_GALEON_L]);
	refShip.Name            			= "Galeon_l";
	refship.Soundtype					= "corvette";
	refShip.Class						= 3;
	refShip.Cannon          			= CANNON_TYPE_CANNON_LBS16;
	refShip.MaxCaliber      			= 20;
	refShip.Weight						= Tonnes2CWT(720);
	refShip.Capacity        			= 3000;
	refShip.CannonsQuantity				= 20; // 2,2,9,9	2,2,8,8
	refShip.CannonsQuantityMin			= 18;
	refShip.rcannon 					= 8;
	refShip.lcannon 					= 8;
	refShip.fcannon 					= 2;
	refShip.bcannon 					= 2;	
	refShip.MaxCrew         			= 250;
	refShip.OptCrew         			= 200;
	refShip.MinCrew         			= 36;	
	refShip.SpeedRate					= 12.0;
	refShip.TurnRate        			= 35.0;
	refShip.Price           			= 52500;
	refShip.HP              			= 4000;
	refShip.SP              			= 100;
	refship.Type.Merchant				= false;
	refship.Type.War					= true;	
	refShip.lowpolycrew 				= 16;
	
	refship.Rocking.y 					= 0.45;
	refship.Rocking.az 					= 0.035;
	
	refship.WaterLine					= 0.85;
	refship.SpeedDependWeight			= 0.15;
	refship.SubSeaDependWeight			= 0.95;
	refship.TurnDependWeight			= 0.2;
	refship.WindAgainstSpeed   			= 0.60;
	
	refship.CabinType          			= "Cabin_Medium2"; 
	refship.DeckType           			= "Medium";
		
	refship.InertiaAccelerationX	= 4.0;	refship.InertiaBrakingX		= 4.0;
	refship.InertiaAccelerationY	= 6;	refship.InertiaBrakingY		= 6;
	refship.InertiaAccelerationZ	= 4.0;	refship.InertiaBrakingZ		= 4.0;
	
	refShip.Height.Bombs.Y				= 4.3;		refShip.Height.Bombs.DY		= 2.1;
	refShip.Height.Grapes.Y				= 5.6;		refShip.Height.Grapes.DY	= 2.8;
	refShip.Height.Knippels.Y			= 18.7;		refShip.Height.Knippels.DY	= 12.7;
	refShip.Height.Balls.Y				= 4.3;		refShip.Height.Balls.DY		= 2.1;
	
	refShip.GeraldSails.rey_b2		= 1;
	refShip.GeraldSails.rey_b3		= 1;
	refShip.GeraldSails.rey_b2.vscale		= 0.7;
	refShip.GeraldSails.rey_b3.vscale		= 0.7;

	refship.Track.Enable	= true;
	refship.Track1.ZStart	= 0.20;
	refship.Track1.LifeTime = 16.5;
	refship.Track1.Width	= "5.2, 7.3";
	refship.Track1.Speed	= "6.0, 8.0";

	refship.Track2.ZStart	= -0.15;
	refship.Track2.LifeTime = 10.5;
	refship.Track2.Width	= "6.0, 8.0";
	refship.Track2.Speed	= "0.15, 0.25";
	
	refship.nation.england	= true;
	refship.nation.france	= true;
	refship.nation.spain	= true;
	refship.nation.holland	= true;
	refship.nation.pirate	= true;
		
	///////////////////////////////////////////////////////////////////////////
	//// Корвет
	///////////////////////////////////////////////////////////////////////////
	makeref(refShip,ShipsTypes[SHIP_CORVETTE]);
	refShip.Name            			= "Corvette";
	refship.Soundtype					= "corvette";
	refShip.Class						= 3;
	refShip.Cannon          			= CANNON_TYPE_CANNON_LBS16;
	refShip.MaxCaliber      			= 20;
	refShip.Weight						= Tonnes2CWT(600);
	refShip.Capacity        			= 2700;
	refShip.CannonsQuantity				= 20; // 2,2,8,8	2,2,7,7
	refShip.CannonsQuantityMin			= 18;
	refShip.rcannon 					= 8;
	refShip.lcannon 					= 8;
	refShip.fcannon 					= 2;
	refShip.bcannon 					= 2;
	
	refShip.MaxCrew         			= 225;
	refShip.OptCrew						= 180;
	refShip.MinCrew         			= 28;
	
	refShip.SpeedRate					= 14.5;
	refShip.TurnRate        			= 40.0;
	refShip.Price           			= 45500;
	refShip.HP              			= 3250;
	refShip.SP              			= 100;
	
	refship.Type.Merchant				= false;
	refship.Type.War					= true;
	refShip.lowpolycrew 				= 16;

	refship.Rocking.y 					= 0.8;
	refship.Rocking.az 					= 0.025;
	
	refship.WaterLine					= 0.0;
	refship.SpeedDependWeight			= 0.3;
	refship.SubSeaDependWeight			= 0.7;
	refship.TurnDependWeight			= 0.35;
	refship.WindAgainstSpeed   			= 0.60;
	refship.CabinType          			= "Cabin_Medium2";
	
	refship.InertiaAccelerationX	= 8.0;	refship.InertiaBrakingX		= 8.0;
	refship.InertiaAccelerationY	= 6;	refship.InertiaBrakingY		= 6;
	refship.InertiaAccelerationZ	= 6.0;	refship.InertiaBrakingZ		= 6.0;
	
	refShip.Height.Bombs.Y				= 2.614;	refShip.Height.Bombs.DY		= 1.346;
	refShip.Height.Grapes.Y				= 4.694;	refShip.Height.Grapes.DY	= 0.666;
	refShip.Height.Knippels.Y			= 15.333;	refShip.Height.Knippels.DY	= 13.425;
	refShip.Height.Balls.Y				= 2.614;	refShip.Height.Balls.DY		= 1.346;	
	
	refShip.GeraldSails.rey_b2		= 1;
	refShip.GeraldSails.rey_b3		= 1;
	refShip.GeraldSails.rey_b2.vscale		= 0.7;
	refShip.GeraldSails.rey_b3.vscale		= 0.7;

	refship.Track.Enable	= true;
	refship.Track1.ZStart	= 0.17;
	refship.Track1.LifeTime = 12.5;
	refship.Track1.Width	= "4.0, 5.0";
	refship.Track1.Speed	= "6.0, 8.0";

	refship.Track2.ZStart	= -0.15;
	refship.Track2.LifeTime = 6.5;
	refship.Track2.Width	= "5.0, 7.0";
	refship.Track2.Speed	= "0.15, 0.25";
	
	refship.nation.england	= true;
	refship.nation.france	= true;
	refship.nation.spain	= false;
	refship.nation.holland	= false;
	refship.nation.pirate	= true;

	//////////////////////////////////////////////////////////////////////////
	//// Шебека
	//////////////////////////////////////////////////////////////////////////
	makeref(refShip,ShipsTypes[SHIP_XebekVML]);
	refShip.Name						= "XebekVML";
	refship.Soundtype					= "lugger";
	refShip.Class						= 3;
	refShip.Cannon  					= CANNON_TYPE_CANNON_LBS16;
	refShip.MaxCaliber  				= 20;
	refShip.Weight						= Tonnes2CWT(500);
	refShip.Capacity   					= 2500;
	refShip.CannonsQuantity				= 22; // 4,2,6,6	4,2,5,5	4,2,4,4
	refShip.CannonsQuantityMin			= 20;
	refShip.rcannon 					= 8;
	refShip.lcannon 					= 8;
	refShip.fcannon 					= 4;
	refShip.bcannon 					= 2;
	refShip.MaxCrew        				= 181;
	refShip.OptCrew        				= 145;
	refShip.MinCrew        				= 22;
	
	refShip.SpeedRate      				= 15.5;
	refShip.TurnRate       				= 60.0;
	refShip.Price          				= 42000;
	refShip.HP             				= 3000;
	refShip.SP             				= 100;

	refship.CabinType          			= "Cabin_Medium2";
	refship.Type.Merchant				= false;
	refship.Type.War					= true;
	
	refShip.lowpolycrew					= 12;

	refship.WindAgainstSpeed   			= 1.55;
		
	refship.Rocking.y	= 0.5;
	refship.Rocking.az	= 0.04;
	
	refship.WaterLine	= -0.10;
	refship.SpeedDependWeight		= 0.3;
	refship.SubSeaDependWeight		= 0.6;
	refship.TurnDependWeight		= 0.3;
	
	refship.InertiaAccelerationX	= 5.5;	refship.InertiaBrakingX	= 5.5;
	refship.InertiaAccelerationY	= 8;	refship.InertiaBrakingY	= 8;
	refship.InertiaAccelerationZ	= 6.0;	refship.InertiaBrakingZ	= 6.0;

	refShip.Height.Bombs.Y		= 1.7;		refShip.Height.Bombs.DY	= 0.8;
	refShip.Height.Grapes.Y		= 3.4;		refShip.Height.Grapes.DY	= 1.7;
	refShip.Height.Knippels.Y	= 10.1;		refShip.Height.Knippels.DY	= 9.2;
	refShip.Height.Balls.Y		= 1.7;		refShip.Height.Balls.DY	= 0.8;
	
	refShip.GeraldSails.rey_b2			= 1;
	refShip.GeraldSails.rey_b3			= 1;
	refShip.GeraldSails.rey_b2.vscale	= 0.8;
	refShip.GeraldSails.rey_b3.vscale	= 0.8;
	
	refship.Track.Enable	= true;
	refship.Track1.ZStart	= 0.20;
	refship.Track1.LifeTime = 12;
	refship.Track1.Width	= "2.0, 3.0";
	refship.Track1.Speed	= "6.0, 8.0";

	refship.Track2.ZStart	= -0.15;
	refship.Track2.LifeTime = 7.5;
	refship.Track2.Width	= "4.0, 6.0";
	refship.Track2.Speed	= "0.15, 0.25";	
	
	refship.nation.england	= false;
	refship.nation.france	= false;
	refship.nation.spain	= true;
	refship.nation.holland	= true;
	refship.nation.pirate	= false;
	
	///////////////////////////////////////////////////////////////////////////
	//// Полакр
	///////////////////////////////////////////////////////////////////////////	
	makeref(refShip,ShipsTypes[SHIP_POLACRE]);
	refShip.Name						= "Polacre";
	refship.Soundtype					= "lugger";
	refShip.Class						= 3;
	refShip.Cannon  					= CANNON_TYPE_CANNON_LBS16;
	refShip.MaxCaliber  				= 20;
	refShip.Weight						= Tonnes2CWT(550);
	refShip.Capacity   					= 2750;
	refShip.CannonsQuantity				= 22; // 2,2,9,9    2,2,8,8	2,2,7,7 
	refShip.CannonsQuantityMin			= 18;
	refShip.rcannon 					= 9;
	refShip.lcannon 					= 9;
	refShip.fcannon 					= 2;
	refShip.bcannon 					= 2;
	refShip.MaxCrew        				= 206;
	refShip.OptCrew        				= 165;
	refShip.MinCrew        				= 24;
	
	refShip.SpeedRate      				= 14.0;
	refShip.TurnRate       				= 50.0;
	refShip.Price          				= 45900;
	refShip.HP             				= 3250;
	refShip.SP             				= 100;

	refship.CabinType          			= "Cabin_Medium2";
	refship.Type.Merchant				= false;
	refship.Type.War					= true;
	
	refShip.lowpolycrew					= 12;

	refship.WindAgainstSpeed   			= 1.35;
		
	refship.Rocking.y	= 0.5;
	refship.Rocking.az	= 0.04;
	
	refship.WaterLine	= 0.0;
	refship.SpeedDependWeight		= 0.3;
	refship.SubSeaDependWeight		= 0.6;
	refship.TurnDependWeight		= 0.3;
	
	refship.InertiaAccelerationX	= 5.5;	refship.InertiaBrakingX	= 5.5;
	refship.InertiaAccelerationY	= 8;	refship.InertiaBrakingY	= 8;
	refship.InertiaAccelerationZ	= 6.0;	refship.InertiaBrakingZ	= 6.0;

	refShip.Height.Bombs.Y		= 1.7;		refShip.Height.Bombs.DY	= 0.8;
	refShip.Height.Grapes.Y		= 3.4;		refShip.Height.Grapes.DY	= 1.7;
	refShip.Height.Knippels.Y	= 10.1;		refShip.Height.Knippels.DY	= 9.2;
	refShip.Height.Balls.Y		= 1.7;		refShip.Height.Balls.DY	= 0.8;
	
	refShip.GeraldSails.rey_b2			= 1;
	refShip.GeraldSails.rey_b3			= 1;
	refShip.GeraldSails.rey_b2.vscale	= 0.8;
	refShip.GeraldSails.rey_b3.vscale	= 0.8;
	
	refship.Track.Enable	= true;
	refship.Track1.ZStart	= 0.20;
	refship.Track1.LifeTime = 12;
	refship.Track1.Width	= "2.0, 3.0";
	refship.Track1.Speed	= "6.0, 8.0";

	refship.Track2.ZStart	= -0.15;
	refship.Track2.LifeTime = 7.5;
	refship.Track2.Width	= "4.0, 6.0";
	refship.Track2.Speed	= "0.15, 0.25";	
	
	refship.nation.england	= false;
	refship.nation.france	= true;
	refship.nation.spain	= true;
	refship.nation.holland	= false;
	refship.nation.pirate	= false;
		
		
	///////////////////////////////////////////////////////////////////////////
	//// Тяжелый Галеон
	///////////////////////////////////////////////////////////////////////////
	makeref(refShip,ShipsTypes[SHIP_GALEON_H]);
	refShip.Name            			= "Galeon_h";
	refship.Soundtype					= "frigate";
	refShip.Class						= 2;
	refShip.Cannon          			= CANNON_TYPE_CANNON_LBS24;
	refShip.MaxCaliber      			= 32;
	refShip.Weight						= Tonnes2CWT(1050);
	refShip.Capacity        			= 5100;
	
	refShip.CannonsQuantity				= 54;	// 4,6,22,22	4,6,21,21	4,6,20,20	4,6,19,19    4,6,18,18
	refShip.CannonsQuantityMin			= 48;
	refShip.rcannon 					= 22;
	refShip.lcannon 					= 22;
	refShip.fcannon 					= 4;
	refShip.bcannon 					= 6;	
	
	refShip.MaxCrew         			= 525;
	refShip.OptCrew         			= 420;
	refShip.MinCrew         			= 60;	
	refShip.SpeedRate					= 11.5;
	refShip.TurnRate        			= 29.0;
	refShip.Price           			= 80900;
	refShip.HP              			= 5000;
	refShip.SP              			= 100;

	refship.Type.Merchant				= false;
	refship.Type.War					= true;	
	refShip.lowpolycrew 				= 20;
	
	refship.Rocking.y 					= 0.4;
	refship.Rocking.az 					= 0.02;
	
	refship.WaterLine					= 0.0;
	refship.SpeedDependWeight			= 0.15;
	refship.SubSeaDependWeight			= 0.3;
	refship.TurnDependWeight			= 0.2;
	refship.WindAgainstSpeed   			= 0.45;
	
	refship.CabinType          			= "Cabin"; 
	refship.DeckType           			= "Big";
	
	refship.InertiaAccelerationX	= 4.5;	refship.InertiaBrakingX		= 4.5;
	refship.InertiaAccelerationY	= 3;	refship.InertiaBrakingY		= 3;
	refship.InertiaAccelerationZ	= 4.5;	refship.InertiaBrakingZ		= 4.5;

	refShip.Height.Bombs.Y				= 3.0;		refShip.Height.Bombs.DY		= 1.5;
	refShip.Height.Grapes.Y				= 4.4;		refShip.Height.Grapes.DY	= 2.2;
	refShip.Height.Knippels.Y			= 21.4;		refShip.Height.Knippels.DY	= 19.8;
	refShip.Height.Balls.Y				= 3.0;		refShip.Height.Balls.DY		= 1.5;
	
	refShip.GeraldSails.rey_b2				= 1;
	refShip.GeraldSails.rey_b3				= 1;
	refShip.GeraldSails.rey_b2.vscale		= 0.98;
	refShip.GeraldSails.rey_b3.vscale		= 0.8;

	refship.Track.Enable	= true;
	refship.Track1.ZStart	= 0.0;
	refship.Track1.LifeTime = 14.5;
	refship.Track1.Width	= "5.2, 7.3";
	refship.Track1.Speed	= "5.5, 6.5";

	refship.Track2.ZStart	= -0.15;
	refship.Track2.LifeTime = 8.5;
	refship.Track2.Width	= "6.0, 8.0";
	refship.Track2.Speed	= "0.15, 0.25";
	
	refship.nation.england	= false;
	refship.nation.france	= false;
	refship.nation.spain	= true;
	refship.nation.holland	= false;
	refship.nation.pirate	= true;
	
	///////////////////////////////////////////////////////////////////////////
	//// Фрегат 
	///////////////////////////////////////////////////////////////////////////
	makeref(refShip,ShipsTypes[SHIP_FRIGATE]);
	refShip.Name            			= "Frigate";
	refship.Soundtype					= "frigate";
	refShip.Class						= 2;
	refShip.Cannon          			= CANNON_TYPE_CANNON_LBS20;
	refShip.MaxCaliber      			= 24;
	refShip.Weight						= Tonnes2CWT(950);
	refShip.Capacity        			= 4000;
	refShip.CannonsQuantity				= 46;
	refShip.CannonsQuantityMin			= 40;
	refShip.rcannon 					= 20;
	refShip.lcannon 					= 20;
	refShip.fcannon 					= 2;
	refShip.bcannon 					= 4;	
	refShip.MaxCrew         			= 400;
	refShip.OptCrew         			= 320;
	refShip.MinCrew         			= 52;	
	refShip.SpeedRate       			= 14.5;
	refShip.TurnRate        			= 35.0;
	refShip.Price           			= 66900;	
	refShip.HP              			= 4600;
	refShip.SP              			= 100;
	refship.Type.Merchant				= false;
	refship.Type.War					= true;
	
	refShip.lowpolycrew 				= 20;	
	refship.Rocking.y 					= 0.4;
	refship.Rocking.az 					= 0.035;
	
	refship.WaterLine					= 0.5;
	refship.SpeedDependWeight			= 0.3;
	refship.SubSeaDependWeight			= 1.0;
	refship.TurnDependWeight			= 0.3;
	refship.WindAgainstSpeed   			= 0.50;
	
	refship.CabinType          			= "Cabin"; 
	refship.DeckType           			= "Big";
		
	refship.InertiaAccelerationX	= 5.0;	refship.InertiaBrakingX		= 5.0;
	refship.InertiaAccelerationY	= 4;	refship.InertiaBrakingY		= 4;
	refship.InertiaAccelerationZ	= 5.0;	refship.InertiaBrakingZ		= 5.0;
	
	refShip.Height.Bombs.Y				= 3.7;	refShip.Height.Bombs.DY		= 1.8;
	refShip.Height.Grapes.Y				= 5.2;	refShip.Height.Grapes.DY	= 2.6;
	refShip.Height.Knippels.Y			= 24.0;	refShip.Height.Knippels.DY	= 19.7;
	refShip.Height.Balls.Y				= 3.7;	refShip.Height.Balls.DY		= 1.8;
	
	refShip.GeraldSails.rey_b1		= 1;
	refShip.GeraldSails.rey_b2		= 1;
	refShip.GeraldSails.rey_b3		= 1;
	refShip.GeraldSails.rey_b1.vscale		= 0.9;
	refShip.GeraldSails.rey_b2.vscale		= 0.7;
	refShip.GeraldSails.rey_b3.vscale		= 0.7;

	refship.Track.Enable	= true;
	refship.Track1.ZStart	= 0.20;
	refship.Track1.LifeTime = 14.5;
	refship.Track1.Width	= "3.7, 3.9";
	refship.Track1.Speed	= "7.0, 8.0";

	refship.Track2.ZStart	= -0.15;
	refship.Track2.LifeTime = 8.5;
	refship.Track2.Width	= "8.0, 9.0";
	refship.Track2.Speed	= "0.15, 0.25";
	
	refship.nation.england	= true;
	refship.nation.france	= true;
	refship.nation.spain	= false;
	refship.nation.holland	= true;
	refship.nation.pirate	= false;

	///////////////////////////////////////////////////////////////////////////
	//// Тяжелый фрегат
	///////////////////////////////////////////////////////////////////////////
	makeref(refShip,ShipsTypes[SHIP_FRIGATE_H]);
	refShip.Name            			= "Frigate_h";
	refship.Soundtype					= "frigate";
	refShip.Class						= 2;
	refShip.Cannon          			= CANNON_TYPE_CANNON_LBS24;
	refShip.MaxCaliber      			= 32;
	refShip.Weight						= Tonnes2CWT(1200);
	refShip.Capacity        			= 4250;
	refShip.CannonsQuantity				= 50;	// 4,6,20,20	4,6,19,19	4,6,18,18
	refShip.CannonsQuantityMin			= 46;
	refShip.rcannon 					= 20;
	refShip.lcannon 					= 20;
	refShip.fcannon 					= 4;
	refShip.bcannon 					= 6;	
	refShip.MaxCrew         			= 437;
	refShip.OptCrew         			= 350;
	refShip.MinCrew         			= 56;
	
	refShip.SpeedRate       			= 13.5;
	refShip.TurnRate        			= 32.0;
	refShip.Price           			= 73700;
	refShip.HP              			= 5400;
	refShip.SP              			= 100;
	
	refship.Type.Merchant				= false;
	refship.Type.War					= true;
	
	refShip.lowpolycrew 				= 20;
	
	refship.Rocking.y 					= 0.4;
	refship.Rocking.az 					= 0.035;	
	refship.WaterLine					= 0.0;

	refship.SpeedDependWeight			= 0.3;
	refship.SubSeaDependWeight			= 1.0;
	refship.TurnDependWeight			= 0.3;
	refship.WindAgainstSpeed   			= 0.45;
	refship.CabinType          			= "Cabin"; // boal 28.03.05
	refship.DeckType           			= "Big";
		
	refship.InertiaAccelerationX	= 5.0;	refship.InertiaBrakingX		= 5.0;
	refship.InertiaAccelerationY	= 4;	refship.InertiaBrakingY		= 4;
	refship.InertiaAccelerationZ	= 5.0;	refship.InertiaBrakingZ		= 5.0;
	
	refShip.Height.Bombs.Y				= 2.7;		refShip.Height.Bombs.DY		= 1.35;
	refShip.Height.Grapes.Y				= 5.325;	refShip.Height.Grapes.DY	= 1.575;
	refShip.Height.Knippels.Y			= 19.5;		refShip.Height.Knippels.DY	= 13.5;
	refShip.Height.Balls.Y				= 2.7;		refShip.Height.Balls.DY		= 1.35;
	
	refShip.GeraldSails.rey_b1		= 1;
	refShip.GeraldSails.rey_b2		= 1;
	refShip.GeraldSails.rey_b3		= 1;
	refShip.GeraldSails.rey_b1.vscale		= 0.9;
	refShip.GeraldSails.rey_b2.vscale		= 0.7;
	refShip.GeraldSails.rey_b3.vscale		= 0.7;

	refship.Track.Enable	= true;
	refship.Track1.ZStart	= 0.20;
	refship.Track1.LifeTime = 14.5;
	refship.Track1.Width	= "3.7, 3.9";
	refship.Track1.Speed	= "7.0, 8.0";

	refship.Track2.ZStart	= -0.15;
	refship.Track2.LifeTime = 8.5;
	refship.Track2.Width	= "8.0, 9.0";
	refship.Track2.Speed	= "0.15, 0.25";
	
	refship.nation.england	= true;
	refship.nation.france	= true;
	refship.nation.spain	= true;
	refship.nation.holland	= true;
	refship.nation.pirate	= false;

	///////////////////////////////////////////////////////////////////////////
	//// Военный корабль
	///////////////////////////////////////////////////////////////////////////
	makeref(refShip,ShipsTypes[SHIP_LINESHIP]);
	refShip.Name            			= "Lineship";
	refship.Soundtype					= "lineship";
	refShip.Class						= 1;   // на деле это воен кор
	refShip.Cannon          			= CANNON_TYPE_CANNON_LBS24;
	refShip.MaxCaliber      			= 32;
	refShip.Weight						= Tonnes2CWT(2000);
	refShip.Capacity        			= 5700;
	refShip.CannonsQuantity				= 56;	// 2,4,25,25	2,4,24,24	2,4,23,23	2,4,22,22
	refShip.CannonsQuantityMin			= 48;
	refShip.rcannon 					= 25;
	refShip.lcannon 					= 25;
	refShip.fcannon 					= 2;
	refShip.bcannon 					= 4;	
	refShip.MaxCrew         			= 750;
	refShip.OptCrew         			= 600;
	refShip.MinCrew         			= 80;	
	refShip.SpeedRate					= 13.0;
	refShip.TurnRate        			= 29.0;
	refShip.Price           			= 93800;
	refShip.HP              			= 7000;
	refShip.SP              			= 100;
	refship.Type.Merchant				= false;
	refship.Type.War					= true;
	
	refShip.lowpolycrew 				= 24;

	refship.Rocking.y 					= 0.5;
	refship.Rocking.az 					= 0.035;
		
	refship.WaterLine					= 1.6;
	refship.SpeedDependWeight			= 0.3;
	refship.SubSeaDependWeight			= 1.15;
	refship.TurnDependWeight			= 0.4;
	refship.WindAgainstSpeed            = 0.40;
	refship.CabinType          			= "Cabin_Huge"; 
	refship.DeckType           			= "Big";
	
	refship.InertiaAccelerationX	= 4.5;	refship.InertiaBrakingX		= 4.0;
	refship.InertiaAccelerationY	= 3.5;	refship.InertiaBrakingY		= 3;
	refship.InertiaAccelerationZ	= 4.5;	refship.InertiaBrakingZ		= 4.0;
	
	refShip.Height.Bombs.Y				= 6.7;		refShip.Height.Bombs.DY		= 3.3;
	refShip.Height.Grapes.Y				= 8.3;		refShip.Height.Grapes.DY	= 4.1;
	refShip.Height.Knippels.Y			= 32.1;		refShip.Height.Knippels.DY	= 25.8;
	refShip.Height.Balls.Y				= 6.7;		refShip.Height.Balls.DY		= 3.3;
	
	refShip.GeraldSails.rey_b2		= 1;
	refShip.GeraldSails.rey_b3		= 1;
	refShip.GeraldSails.rey_b1		= 1;
	refShip.GeraldSails.rey_b1.vscale		= 0.8;
	refShip.GeraldSails.rey_b2.vscale		= 0.6;
	refShip.GeraldSails.rey_b3.vscale		= 0.6;

	refship.Track.Enable	= true;
	refship.Track1.ZStart	= 0.15;
	refship.Track1.LifeTime = 16.5;
	refship.Track1.Width	= "3.0, 4.0";
	refship.Track1.Speed	= "8.0, 8.0";

	refship.Track2.ZStart	= -0.25;
	refship.Track2.LifeTime = 10.5;
	refship.Track2.Width	= "6.0, 7.0";
	refship.Track2.Speed	= "0.15, 0.25";	
	
	refship.nation.england	= true;
	refship.nation.france	= true;
	refship.nation.spain	= true;
	refship.nation.holland	= true;
	refship.nation.pirate	= true;

	///////////////////////////////////////////////////////////////////////////
	//// Французский линейный корабль
	///////////////////////////////////////////////////////////////////////////
	makeref(refShip,ShipsTypes[SHIP_LSHIP_FRA]);
	refShip.Name            			= "Warship";  
	refship.Soundtype					= "lineship";
	refShip.Class						= 1;
	refShip.Cannon          			= CANNON_TYPE_CANNON_LBS36;
	refShip.MaxCaliber      			= 42;
	refShip.Weight						= Tonnes2CWT(2500);
	refShip.Capacity        			= 6850;
	refShip.CannonsQuantity				= 66;	
	refShip.CannonsQuantityMin			= 58;
	refShip.rcannon 					= 30;
	refShip.lcannon 					= 30;
	refShip.fcannon 					= 2;
	refShip.bcannon 					= 4;		
	refShip.MaxCrew         			= 812;
	refShip.OptCrew         			= 650;
	refShip.MinCrew         			= 94;	
	refShip.SpeedRate					= 13.0;
	refShip.TurnRate        			= 28.0;
	refShip.Price           			= 110900;
	refShip.HP              			= 9000;
	refShip.SP              			= 100;
	
	refship.Type.Merchant				= false;
	refship.Type.War					= true;
	
	refShip.lowpolycrew 				= 24;
	refship.Rocking.y 					= 0.5;
	refship.Rocking.az 					= 0.035;
	
	refship.WaterLine					= 0.5;
	refship.SpeedDependWeight			= 0.35;
	refship.SubSeaDependWeight			= 1.0;
	refship.TurnDependWeight			= 0.4;
	refship.WindAgainstSpeed   			= 0.35;
	refship.CabinType          			= "Cabin_Huge"; 
	refship.DeckType           			= "Big";
	
	refship.InertiaAccelerationX	= 4.0;	refship.InertiaBrakingX		= 3.5;
	refship.InertiaAccelerationY	= 3.0;	refship.InertiaBrakingY		= 2.5;
	refship.InertiaAccelerationZ	= 4.0;	refship.InertiaBrakingZ		= 3.5;
	
	refShip.Height.Bombs.Y				= 7.2;		refShip.Height.Bombs.DY		= 3.6;
	refShip.Height.Grapes.Y				= 8.5;		refShip.Height.Grapes.DY	= 4.2;
	refShip.Height.Knippels.Y			= 28.3;		refShip.Height.Knippels.DY	= 22.0;
	refShip.Height.Balls.Y				= 7.2;		refShip.Height.Balls.DY		= 3.6;
	
	refShip.GeraldSails.rey_b2		= 1;
	refShip.GeraldSails.rey_b3		= 1;
	refShip.GeraldSails.rey_b1		= 1;
	refShip.GeraldSails.rey_b1.vscale		= 0.8;
	refShip.GeraldSails.rey_b2.vscale		= 0.65;
	refShip.GeraldSails.rey_b3.vscale		= 0.55;

	refship.Track.Enable	= true;
	refship.Track1.ZStart	= 0.25;
	refship.Track1.LifeTime = 9.5;
	refship.Track1.Width	= "7.0, 7.5";
	refship.Track1.Speed	= "8.0, 9.0";

	refship.Track2.ZStart	= -0.15;
	refship.Track2.LifeTime = 7.5;
	refship.Track2.Width	= "8.0, 10.0";
	refship.Track2.Speed	= "1.0, 2.0";
	
	refship.nation.england	= false;
	refship.nation.france	= true;
	refship.nation.spain	= false;
	refship.nation.holland	= false;
	refship.nation.pirate	= false;

	///////////////////////////////////////////////////////////////////////////
	//// Голландский линейный корабль 
	///////////////////////////////////////////////////////////////////////////
	makeref(refShip,ShipsTypes[SHIP_LSHIP_HOL]);
	refShip.Name            			= "Battleship";
	refship.Soundtype					= "lineship";
	refShip.Class						= 1;
	refShip.Cannon          			= CANNON_TYPE_CANNON_LBS32;
	refShip.MaxCaliber      			= 42;
	refShip.Weight						= Tonnes2CWT(3200);
	refShip.Capacity        			= 7400;
	refShip.CannonsQuantity				= 80;	// 2,6,35,35      2,6,34,34     2,6,33,33     2,6,32,32     2,6,31,31      2,6,30,30
	refShip.CannonsQuantityMin			= 72;
	refShip.rcannon 					= 36;
	refShip.lcannon 					= 36;
	refShip.fcannon 					= 2;
	refShip.bcannon 					= 6;		
	refShip.MaxCrew         			= 875;
	refShip.OptCrew         			= 700;
	refShip.MinCrew         			= 120;
	
	refShip.SpeedRate					= 12.0;
	refShip.TurnRate        			= 27.0;
	refShip.Price           			= 122000;
	refShip.HP              			= 9500;
	refShip.SP              			= 100;
	refship.Type.Merchant				= false;
	refship.Type.War					= true;
	
	refShip.lowpolycrew 				= 24;
	refship.Rocking.y 					= 0.5;
	refship.Rocking.az 					= 0.035;
		
	refship.WaterLine					= -0.2;
	refship.SpeedDependWeight			= 0.35;
	refship.SubSeaDependWeight			= 0.75;
	refship.TurnDependWeight			= 0.4;
	refship.WindAgainstSpeed   			= 0.30;
	refship.CabinType          			= "Cabin_Huge"; 
	refship.DeckType           			= "Big";
		
	refship.InertiaAccelerationX	= 3.5;	refship.InertiaBrakingX		= 3.0;
	refship.InertiaAccelerationY	= 2.5;	refship.InertiaBrakingY		= 2.5;
	refship.InertiaAccelerationZ	= 3.5;	refship.InertiaBrakingZ		= 3.0;
	
	refShip.Height.Bombs.Y				= 6.8;		refShip.Height.Bombs.DY		= 3.4;
	refShip.Height.Grapes.Y				= 8.2;		refShip.Height.Grapes.DY	= 4.1;
	refShip.Height.Knippels.Y			= 33.6;		refShip.Height.Knippels.DY	= 24.8;
	refShip.Height.Balls.Y				= 6.8;		refShip.Height.Balls.DY		= 3.4;
	
	refShip.GeraldSails.rey_b2				= 1;
	refShip.GeraldSails.rey_b3				= 1;
	refShip.GeraldSails.rey_b1				= 1;
	refShip.GeraldSails.rey_b1.vscale		= 0.7;
	refShip.GeraldSails.rey_b2.vscale		= 0.65;
	refShip.GeraldSails.rey_b3.vscale		= 0.65;

	refship.Track.Enable	= true;
	refship.Track1.ZStart	= 0.25;
	refship.Track1.LifeTime = 16.5;
	refship.Track1.Width	= "6.0, 8.2";
	refship.Track1.Speed	= "9.0, 9.0";

	refship.Track2.ZStart	= 0.0;
	refship.Track2.LifeTime = 13.5;
	refship.Track2.Width	= "8.0, 9.0";
	refship.Track2.Speed	= "0.15, 0.25";
	
	refship.nation.england	= false;
	refship.nation.france	= false;
	refship.nation.spain	= false;
	refship.nation.holland	= true;
	refship.nation.pirate	= false;

	///////////////////////////////////////////////////////////////////////////
	//// Испанский линейный корабль
	///////////////////////////////////////////////////////////////////////////
	makeref(refShip,ShipsTypes[SHIP_LSHIP_SPA]);
	refShip.Name            			= "Manowar";
	refship.Soundtype					= "manowar";
	refShip.Class						= 1;
	refShip.Cannon          			= CANNON_TYPE_CANNON_LBS36;
	refShip.MaxCaliber      			= 42;
	refShip.Weight						= Tonnes2CWT(3700);
	refShip.Capacity        			= 8600;
	refShip.CannonsQuantity				= 102; // 4,4,40,40   4,4,39,39    4,4,38,38     4,4,37,37    4,4,36,36     4,4,35,35
	refShip.CannonsQuantityMin			= 92;
	refShip.rcannon 					= 45;
	refShip.lcannon 					= 45;
	refShip.fcannon 					= 4;
	refShip.bcannon 					= 8;		
	refShip.MaxCrew         			= 937;
	refShip.OptCrew         			= 750;
	refShip.MinCrew         			= 140;
	
	refShip.SpeedRate					= 12.0;
	refShip.TurnRate        			= 26.0;
	refShip.Price           			= 139600;
	refShip.HP              			= 10000;
	refShip.SP              			= 100;
	refship.Type.Merchant				= false;
	refship.Type.War					= true;
	refShip.lowpolycrew 				= 28;

	refship.Rocking.y 					= 0.3;
	refship.Rocking.az 					= 0.02	;

	refship.WaterLine					= 0.5;
	refship.SpeedDependWeight			= 0.45;
	refship.SubSeaDependWeight			= 1.8;
	refship.TurnDependWeight			= 0.45;
	refship.WindAgainstSpeed   			= 0.25;
	refship.CabinType          			= "Cabin_Huge"; 
	refship.DeckType           			= "Big";
	
	refship.InertiaAccelerationX	= 1.5;	refship.InertiaBrakingX		= 1.5;
	refship.InertiaAccelerationY	= 1.5;	refship.InertiaBrakingY		= 1.5;
	refship.InertiaAccelerationZ	= 1.5;	refship.InertiaBrakingZ		= 1.5;
	
	refShip.Height.Bombs.Y				= 8.6;		refShip.Height.Bombs.DY		= 4.3;
	refShip.Height.Grapes.Y				= 12.5;		refShip.Height.Grapes.DY	= 6.2;
	refShip.Height.Knippels.Y			= 36.8;		refShip.Height.Knippels.DY	= 29.6;
	refShip.Height.Balls.Y				= 8.6;		refShip.Height.Balls.DY		= 4.3;
	
	refShip.GeraldSails.rey_b2		= 1;
	refShip.GeraldSails.rey_b3		= 1;
	refShip.GeraldSails.rey_c1		= 1;
	refShip.GeraldSails.rey_c1.vscale		= 0.98;
	refShip.GeraldSails.rey_b2.vscale		= 0.98;
	refShip.GeraldSails.rey_b3.vscale		= 0.98;

	refship.Track.Enable	= true;
	refship.Track1.ZStart	= 0.30;
	refship.Track1.LifeTime = 18.5;
	refship.Track1.Width	= "6.5, 7.5";
	refship.Track1.Speed	= "8.0, 9.0";

	refship.Track2.ZStart	= -0.15;
	refship.Track2.LifeTime = 10.5;
	refship.Track2.Width	= "16.0, 18.0";
	refship.Track2.Speed	= "0.15, 0.25";
	
	refship.nation.england	= false;
	refship.nation.france	= false;
	refship.nation.spain	= true;
	refship.nation.holland	= false;
	refship.nation.pirate	= false;

	///////////////////////////////////////////////////////////////////////////
	//// Английский линейный корабль
	///////////////////////////////////////////////////////////////////////////
	makeref(refShip,ShipsTypes[SHIP_LSHIP_ENG]);
	refShip.Name            			= "Manowar_e";
	refship.Soundtype					= "manowar";
	refShip.Class						= 1;
	refShip.Cannon          			= CANNON_TYPE_CANNON_LBS36;
	refShip.MaxCaliber      			= 42;
	refShip.Weight						= Tonnes2CWT(4200);
	refShip.Capacity        			= 9200;
	refShip.CannonsQuantity				= 112;
	refShip.CannonsQuantityMin			= 102;
	refShip.rcannon 					= 50; // 6,8,40,40	6,8,39,39	6,8,38,38	6,8,37,37	6,8,36,36	6,8,35,35
	refShip.lcannon 					= 50;
	refShip.fcannon 					= 4;
	refShip.bcannon 					= 8;		
	refShip.MaxCrew         			= 1000;
	refShip.OptCrew         			= 800;
	refShip.MinCrew         			= 160;	
	refShip.SpeedRate					= 12.0;
	refShip.TurnRate        			= 25.0;
	refShip.Price           			= 151100;
	refShip.HP              			= 10800;
	refShip.SP              			= 100;
	refship.Type.Merchant				= false;
	refship.Type.War					= true;
	refShip.lowpolycrew 				= 28;

	refship.Rocking.y 					= 0.3;
	refship.Rocking.az 					= 0.02	;

	refship.WaterLine					= 0.5;
	refship.SpeedDependWeight			= 0.45;
	refship.SubSeaDependWeight			= 1.8;
	refship.TurnDependWeight			= 0.45;
	refship.WindAgainstSpeed   			= 0.25;
	refship.CabinType          			= "Cabin_Huge"; // boal 28.03.05
	refship.DeckType           			= "Big";
	
	refship.InertiaAccelerationX	= 1.5;	refship.InertiaBrakingX		= 1.5;
	refship.InertiaAccelerationY	= 1.5;	refship.InertiaBrakingY		= 1.5;
	refship.InertiaAccelerationZ	= 1.5;	refship.InertiaBrakingZ		= 1.5;
	
	refShip.Height.Bombs.Y				= 8.6;		refShip.Height.Bombs.DY		= 4.3;
	refShip.Height.Grapes.Y				= 12.5;		refShip.Height.Grapes.DY	= 6.2;
	refShip.Height.Knippels.Y			= 36.8;		refShip.Height.Knippels.DY	= 29.6;
	refShip.Height.Balls.Y				= 8.6;		refShip.Height.Balls.DY		= 4.3;
	
	refShip.GeraldSails.rey_b2		= 1;
	refShip.GeraldSails.rey_b3		= 1;
	refShip.GeraldSails.rey_c1		= 1;
	refShip.GeraldSails.rey_c1.vscale		= 0.98;
	refShip.GeraldSails.rey_b2.vscale		= 0.98;
	refShip.GeraldSails.rey_b3.vscale		= 0.98;

	refship.Track.Enable	= true;
	refship.Track1.ZStart	= 0.30;
	refship.Track1.LifeTime = 18.5;
	refship.Track1.Width	= "6.5, 7.5";
	refship.Track1.Speed	= "8.0, 9.0";

	refship.Track2.ZStart	= -0.15;
	refship.Track2.LifeTime = 10.5;
	refship.Track2.Width	= "16.0, 18.0";
	refship.Track2.Speed	= "0.15, 0.25";
	
	refship.nation.england	= true;
	refship.nation.france	= false;
	refship.nation.spain	= false;
	refship.nation.holland	= false;
	refship.nation.pirate	= false;
	
	//////////////////////////////////////////////////////////////////////////
	//// КВЕСТОВЫЕ КОРАБЛИ
	//////////////////////////////////////////////////////////////////////////	
	//////////////////////////////////////////////////////////////////////////
	//// Легкая шебека "Мэйфэнг" -квестовый
	//////////////////////////////////////////////////////////////////////////
	makeref(refShip,ShipsTypes[SHIP_MAYFANG]);
	refShip.Name					= "Mayfang";
	refship.Soundtype				= "lugger";
	refShip.Class					= 4;
	refShip.Cannon  				= CANNON_TYPE_CANNON_LBS20;
	refShip.MaxCaliber  			= 20;
	refShip.Weight					= Tonnes2CWT(270);
	refShip.Capacity   				= 1900;
	refShip.CannonsQuantity			= 20;	// 4,2,7,7
	refShip.CannonsQuantityMin		= 20;
	refShip.rcannon 				= 7;
	refShip.lcannon 				= 7;
	refShip.fcannon 				= 4;
	refShip.bcannon 				= 2;	
	refShip.MaxCrew        			= 137;
	refShip.OptCrew        			= 110;
	refShip.MinCrew        			= 20;
	
	refShip.SpeedRate      			= 17.0;
	refShip.TurnRate       			= 65.0;
	refShip.Price          			= 30500;
	refShip.HP             			= 1950;
	refShip.SP             			= 100;
	refship.CabinType          		= "Cabin_Medium";
	refship.Type.Merchant			= false;
	refship.Type.War				= true;
	refship.QuestShip				= true; 

	refShip.lowpolycrew				= 12;
	refship.WindAgainstSpeed   		= 1.60;
		
	refship.Rocking.y				= 0.5;
	refship.Rocking.az				= 0.04;
	
	refship.WaterLine				= 0.0;
	refship.SpeedDependWeight		= 0.3;
	refship.SubSeaDependWeight		= 0.6;
	refship.TurnDependWeight		= 0.3;
	
	refship.InertiaAccelerationX	= 5.5;	refship.InertiaBrakingX	= 5.5;
	refship.InertiaAccelerationY	= 8;	refship.InertiaBrakingY	= 8;
	refship.InertiaAccelerationZ	= 6.0;	refship.InertiaBrakingZ	= 6.0;

	refShip.Height.Bombs.Y	= 2.5;			refShip.Height.Bombs.DY	= 1.5;
	refShip.Height.Grapes.Y	= 2.76;			refShip.Height.Grapes.DY	= 0.5;
	refShip.Height.Knippels.Y	= 14.4;		refShip.Height.Knippels.DY	= 7.8;
	refShip.Height.Balls.Y		= 2.5;		refShip.Height.Balls.DY	= 1.5;
	
	refShip.GeraldSails.rey_b2			= 1;
	refShip.GeraldSails.rey_b3			= 1;
	refShip.GeraldSails.rey_b2.vscale	= 0.8;
	refShip.GeraldSails.rey_b3.vscale	= 0.8;
	
	refship.Track.Enable	= true;
	refship.Track1.ZStart	= 0.20;
	refship.Track1.LifeTime = 12;
	refship.Track1.Width	= "2.0, 3.0";
	refship.Track1.Speed	= "6.0, 8.0";

	refship.Track2.ZStart	= -0.15;
	refship.Track2.LifeTime = 7.5;
	refship.Track2.Width	= "4.0, 6.0";
	refship.Track2.Speed	= "0.15, 0.25";
	
	//////////////////////////////////////////////////////////////////////////
	//// Приватирский кеч "Мираж" - квестовый
	//////////////////////////////////////////////////////////////////////////
	makeref(refShip,ShipsTypes[SHIP_MIRAGE]);
	refShip.Name				= "Mirage";
	refship.Soundtype			= "lugger";
	refShip.Class				= 4;
	refShip.Cannon  			= CANNON_TYPE_CANNON_LBS20;
	refShip.MaxCaliber  		= 20;
	refShip.Weight				= Tonnes2CWT(290);
	refShip.Capacity   			= 2300;
	refShip.CannonsQuantity		= 22;	//	4,2,6,6
	refShip.CannonsQuantityMin	= 22;
	refShip.rcannon 			= 8;
	refShip.lcannon 			= 8
	refShip.fcannon 			= 4;
	refShip.bcannon 			= 2;	
	refShip.MaxCrew        		= 200;
	refShip.OptCrew        		= 160;
	refShip.MinCrew        		= 16;	
	refShip.SpeedRate      		= 16.0;
	refShip.TurnRate       		= 45.0;
	refShip.Price          		= 36900;
	refShip.HP             		= 2350;
	refShip.SP             		= 100;
	
	refship.CabinType          	= "Cabin_Medium2"; 
	refship.Type.Merchant		= false;
	refship.Type.War			= true;
	refship.QuestShip			= true; 
	refShip.lowpolycrew			= 12;

	refship.WindAgainstSpeed   	= 1.40;
	
	refship.Rocking.y			= 0.5;
	refship.Rocking.az			= 0.04;
	
	refship.WaterLine				= -0.02;
	refship.SpeedDependWeight		= 0.3;
	refship.SubSeaDependWeight		= 0.6;
	refship.TurnDependWeight		= 0.3;
	
	refship.InertiaAccelerationX	= 5.5;	refship.InertiaBrakingX	= 5.5;
	refship.InertiaAccelerationY	= 8;	refship.InertiaBrakingY	= 8;
	refship.InertiaAccelerationZ	= 6.0;	refship.InertiaBrakingZ	= 6.0;

	refShip.Height.Bombs.Y		= 1.2;		refShip.Height.Bombs.DY	= 0.6;
	refShip.Height.Grapes.Y		= 3.1;		refShip.Height.Grapes.DY	= 1.5;
	refShip.Height.Knippels.Y	= 17.7;		refShip.Height.Knippels.DY	= 16.7;
	refShip.Height.Balls.Y		= 1.2;		refShip.Height.Balls.DY	= 0.6;
	
	refShip.GeraldSails.rey_b2			= 1;
	refShip.GeraldSails.rey_b2.vscale	= 0.8;
	
	refship.Track.Enable	= true;
	refship.Track1.ZStart	= 0.20;
	refship.Track1.LifeTime = 12;
	refship.Track1.Width	= "2.0, 3.0";
	refship.Track1.Speed	= "6.0, 8.0";

	refship.Track2.ZStart	= -0.15;
	refship.Track2.LifeTime = 7.5;
	refship.Track2.Width	= "4.0, 6.0";
	refship.Track2.Speed	= "0.15, 0.25";

	//////////////////////////////////////////////////////////////////////////
	//// Патрульный бриг "Валькирия"  - квестовый
	//////////////////////////////////////////////////////////////////////////
	makeref(refShip,ShipsTypes[SHIP_VALCIRIA]);
	refShip.Name				= "Valciria";
	refship.Soundtype			= "lugger";
	refShip.Class				= 4;
	refShip.Cannon  			= CANNON_TYPE_CANNON_LBS20;
	refShip.MaxCaliber  		= 20;
	refShip.Weight				= Tonnes2CWT(310);
	refShip.Capacity   			= 2000;
	refShip.CannonsQuantity		= 20;	// 2,2,8,8
	refShip.CannonsQuantityMin	= 20;
	refShip.rcannon 			= 8;
	refShip.lcannon 			= 8;
	refShip.fcannon 			= 2;
	refShip.bcannon 			= 2;	
	refShip.MaxCrew        		= 181;
	refShip.OptCrew        		= 145;
	refShip.MinCrew        		= 22;	
	refShip.SpeedRate      		= 15.5;
	refShip.TurnRate       		= 55.0;
	refShip.Price          		= 35300;
	refShip.HP             		= 2650;
	refShip.SP             		= 100;

	refship.CabinType          	= "Cabin_Medium"; 
	refship.Type.Merchant		= false;
	refship.Type.War			= true;
	refship.QuestShip			= true; 
	refShip.lowpolycrew			= 12;

	refship.WindAgainstSpeed   	= 1.20;
		
	refship.Rocking.y	= 0.5;
	refship.Rocking.az	= 0.04;
	
	refship.WaterLine	= -0.6;
	
	refship.SpeedDependWeight		= 0.3;
	refship.SubSeaDependWeight		= 0.6;
	refship.TurnDependWeight		= 0.3;
	
	refship.InertiaAccelerationX	= 5.5;	refship.InertiaBrakingX	= 5.5;
	refship.InertiaAccelerationY	= 8;	refship.InertiaBrakingY	= 8;
	refship.InertiaAccelerationZ	= 6.0;	refship.InertiaBrakingZ	= 6.0;

	refShip.Height.Bombs.Y	= 1.5;			refShip.Height.Bombs.DY	= 0.7;
	refShip.Height.Grapes.Y	= 2.8;			refShip.Height.Grapes.DY	= 1.4;
	refShip.Height.Knippels.Y	= 16.9;		refShip.Height.Knippels.DY	= 15.4;
	refShip.Height.Balls.Y		= 1.5;		refShip.Height.Balls.DY	= 0.7;
	
	refShip.GeraldSails.rey_b2		= 1;
	refShip.GeraldSails.rey_b3		= 1;
	refShip.GeraldSails.rey_b2.vscale	= 0.8;
	refShip.GeraldSails.rey_b3.vscale	= 0.8;
	
	refship.Track.Enable	= true;
	refship.Track1.ZStart	= 0.20;
	refship.Track1.LifeTime = 12;
	refship.Track1.Width	= "2.0, 3.0";
	refship.Track1.Speed	= "6.0, 8.0";

	refship.Track2.ZStart	= -0.15;
	refship.Track2.LifeTime = 7.5;
	refship.Track2.Width	= "4.0, 6.0";
	refship.Track2.Speed	= "0.15, 0.25";

	///////////////////////////////////////////////////////////////////////////
	//// Малый фрегат "Гриффондор" - квестовый
	///////////////////////////////////////////////////////////////////////////
	makeref(refShip,ShipsTypes[SHIP_CORVETTE_QUEST]);
	refShip.Name            			= "Corvette_quest";
	refship.Soundtype					= "corvette";
	refShip.Class						= 3;
	refShip.Cannon          			= CANNON_TYPE_CANNON_LBS24;
	refShip.MaxCaliber      			= 24;
	refShip.Weight						= Tonnes2CWT(780);
	refShip.Capacity        			= 3800;
	refShip.CannonsQuantity				= 34;	// 2,4,14,14
	refShip.CannonsQuantityMin			= 34;
	refShip.rcannon 					= 14;
	refShip.lcannon 					= 14;
	refShip.fcannon 					= 2;
	refShip.bcannon 					= 4;	
	refShip.MaxCrew         			= 312;
	refShip.OptCrew         			= 250;
	refShip.MinCrew         			= 45;
	
	refShip.SpeedRate					= 15.75;
	refShip.TurnRate        			= 38.0;
	refShip.Price           			= 61100;
	refShip.HP              			= 4000;
	refShip.SP              			= 100;
	refship.Type.Merchant				= false;
	refship.Type.War					= true;
	refship.QuestShip					= true; 
	
	refShip.lowpolycrew 				= 16;

	refship.Rocking.y 					= 0.8;
	refship.Rocking.az 					= 0.025;
	
	refship.WaterLine					= 0.0;
	refship.SpeedDependWeight			= 0.3;
	refship.SubSeaDependWeight			= 0.7;
	refship.TurnDependWeight			= 0.35;
	refship.WindAgainstSpeed   			= 0.65;
	refship.CabinType          			= "Cabin_Medium2"; 

	refship.InertiaAccelerationX	= 8.0;	refship.InertiaBrakingX		= 8.0;
	refship.InertiaAccelerationY	= 6;	refship.InertiaBrakingY		= 6;
	refship.InertiaAccelerationZ	= 6.0;	refship.InertiaBrakingZ		= 6.0;
	
	refShip.Height.Bombs.Y				= 1.3;		refShip.Height.Bombs.DY		= 0.6;
	refShip.Height.Grapes.Y				= 3.1;		refShip.Height.Grapes.DY	= 1.5;
	refShip.Height.Knippels.Y			= 14.7;		refShip.Height.Knippels.DY	= 15.0;
	refShip.Height.Balls.Y				= 1.3;		refShip.Height.Balls.DY		= 0.6;
	
	refShip.GeraldSails.rey_b2		= 1;
	refShip.GeraldSails.rey_b3		= 1;
	refShip.GeraldSails.rey_b2.vscale		= 0.7;
	refShip.GeraldSails.rey_b3.vscale		= 0.7;

	refship.Track.Enable	= true;
	refship.Track1.ZStart	= 0.17;
	refship.Track1.LifeTime = 12.5;
	refship.Track1.Width	= "4.0, 5.0";
	refship.Track1.Speed	= "6.0, 8.0";

	refship.Track2.ZStart	= -0.15;
	refship.Track2.LifeTime = 6.5;
	refship.Track2.Width	= "5.0, 7.0";
	refship.Track2.Speed	= "0.15, 0.25";
	
	///////////////////////////////////////////////////////////////////////////
	//// Полакр Тореро - квестовый
	///////////////////////////////////////////////////////////////////////////	
	makeref(refShip,ShipsTypes[SHIP_POLACRE_QUEST]);
	refShip.Name						= "Polacre_q";
	refship.Soundtype					= "lugger";
	refShip.Class						= 3;
	refShip.Cannon  					= CANNON_TYPE_CANNON_LBS24;
	refShip.MaxCaliber  				= 24;
	refShip.Weight						= Tonnes2CWT(600);
	refShip.Capacity   					= 3100;
	refShip.CannonsQuantity				= 24; 
	refShip.CannonsQuantityMin			= 24;
	refShip.rcannon 					= 10;
	refShip.lcannon 					= 10;
	refShip.fcannon 					= 2;
	refShip.bcannon 					= 2;
	refShip.MaxCrew        				= 220;
	refShip.OptCrew        				= 175;
	refShip.MinCrew        				= 25;
	
	refShip.SpeedRate      				= 14.25;
	refShip.TurnRate       				= 52.0;
	refShip.Price          				= 55000;
	refShip.HP             				= 3750;
	refShip.SP             				= 100;

	refship.CabinType          			= "Cabin_Medium2";
	refship.Type.Merchant				= false;
	refship.Type.War					= true;
	refship.QuestShip					= true;
	
	refShip.lowpolycrew					= 12;

	refship.WindAgainstSpeed   			= 1.35;
		
	refship.Rocking.y	= 0.5;
	refship.Rocking.az	= 0.04;
	
	refship.WaterLine	= 0.0;
	refship.SpeedDependWeight		= 0.3;
	refship.SubSeaDependWeight		= 0.6;
	refship.TurnDependWeight		= 0.3;
	
	refship.InertiaAccelerationX	= 5.5;	refship.InertiaBrakingX	= 5.5;
	refship.InertiaAccelerationY	= 8;	refship.InertiaBrakingY	= 8;
	refship.InertiaAccelerationZ	= 6.0;	refship.InertiaBrakingZ	= 6.0;

	refShip.Height.Bombs.Y		= 1.7;		refShip.Height.Bombs.DY	= 0.8;
	refShip.Height.Grapes.Y		= 3.4;		refShip.Height.Grapes.DY	= 1.7;
	refShip.Height.Knippels.Y	= 10.1;		refShip.Height.Knippels.DY	= 9.2;
	refShip.Height.Balls.Y		= 1.7;		refShip.Height.Balls.DY	= 0.8;
	
	refShip.GeraldSails.rey_b2			= 1;
	refShip.GeraldSails.rey_b3			= 1;
	refShip.GeraldSails.rey_b2.vscale	= 0.8;
	refShip.GeraldSails.rey_b3.vscale	= 0.8;
	
	refship.Track.Enable	= true;
	refship.Track1.ZStart	= 0.20;
	refship.Track1.LifeTime = 12;
	refship.Track1.Width	= "2.0, 3.0";
	refship.Track1.Speed	= "6.0, 8.0";

	refship.Track2.ZStart	= -0.15;
	refship.Track2.LifeTime = 7.5;
	refship.Track2.Width	= "4.0, 6.0";
	refship.Track2.Speed	= "0.15, 0.25";	
	
	///////////////////////////////////////////////////////////////////////////
	//// Быстрый фрегат "Фортуна" - квестовый
	///////////////////////////////////////////////////////////////////////////
	makeref(refShip,ShipsTypes[SHIP_FRIGATE_L]);
	refShip.Name            			= "ArabellaShip";
	refship.Soundtype					= "frigate";
	refShip.Class						= 2;
	refShip.Cannon          			= CANNON_TYPE_CANNON_LBS24;
	refShip.MaxCaliber      			= 24;
	refShip.Weight						= Tonnes2CWT(920);
	refShip.Capacity        			= 4000;
	refShip.CannonsQuantity				= 42;	// 4,4,17,17
	refShip.CannonsQuantityMin			= 42;
	refShip.rcannon 					= 17;
	refShip.lcannon 					= 17;
	refShip.fcannon 					= 4;
	refShip.bcannon 					= 4;
	
	refShip.MaxCrew         			= 425;
	refShip.OptCrew         			= 340;
	refShip.MinCrew         			= 50;
	
	refShip.SpeedRate       			= 17.25;
	refShip.TurnRate        			= 37.25;
	refShip.Price           			= 67700;
	refShip.HP              			= 4800;
	refShip.SP              			= 100;

	refship.Type.Merchant				= false;
	refship.Type.War					= true;
	refship.QuestShip					= true; 

	refShip.lowpolycrew 				= 20;
	
	refship.Rocking.y 					= 0.4;
	refship.Rocking.az 					= 0.035;	
	refship.WaterLine					= 0.0;

	refship.SpeedDependWeight			= 0.3;
	refship.SubSeaDependWeight			= 1.0;
	refship.TurnDependWeight			= 0.3;
	refship.WindAgainstSpeed   			= 0.60;
	refship.CabinType          			= "Cabin"; 
	refship.DeckType           			= "Big";
	
	refship.InertiaAccelerationX	= 5.0;	refship.InertiaBrakingX		= 5.0;
	refship.InertiaAccelerationY	= 4;	refship.InertiaBrakingY		= 4;
	refship.InertiaAccelerationZ	= 5.0;	refship.InertiaBrakingZ		= 5.0;
	
	refShip.Height.Bombs.Y				= 3.4;	refShip.Height.Bombs.DY		= 1.5;
	refShip.Height.Grapes.Y				= 5.3;	refShip.Height.Grapes.DY	= 1.575;
	refShip.Height.Knippels.Y			= 19.5;	refShip.Height.Knippels.DY	= 13.5;
	refShip.Height.Balls.Y				= 3.4;	refShip.Height.Balls.DY		= 1.5;
	
	refShip.GeraldSails.rey_b1		= 1;
	refShip.GeraldSails.rey_b2		= 1;
	refShip.GeraldSails.rey_b3		= 1;
	refShip.GeraldSails.rey_b1.vscale		= 0.9;
	refShip.GeraldSails.rey_b2.vscale		= 0.7;
	refShip.GeraldSails.rey_b3.vscale		= 0.7;

	refship.Track.Enable	= true;
	refship.Track1.ZStart	= 0.20;
	refship.Track1.LifeTime = 14.5;
	refship.Track1.Width	= "3.7, 3.9";
	refship.Track1.Speed	= "7.0, 8.0";

	refship.Track2.ZStart	= -0.15;
	refship.Track2.LifeTime = 8.5;
	refship.Track2.Width	= "8.0, 9.0";
	refship.Track2.Speed	= "0.15, 0.25";	

	// --> квестовые корабли - заглушки
	///////////////////////////////////////////////////////////////////////////
	//// квестовый корабль №0 - 6-ый класс
	///////////////////////////////////////////////////////////////////////////
	makeref(refShip,ShipsTypes[SHIP_QUEST0]);
	refShip.Name									= "QuestShip0";
	refship.Soundtype								= "lugger";
	refShip.Class									= 6;
	refShip.Cannon									= CANNON_TYPE_NONECANNON;
	refShip.MaxCaliber								= 3;
	refShip.Weight									= Tonnes2CWT(10);
	refShip.Capacity								= 80;
	refShip.CannonsQuantity							= 0;
	refShip.CannonsQuantityMin						= 0;
	refShip.rcannon 								= 0;
	refShip.lcannon 								= 0;
	refShip.fcannon 								= 0;
	refShip.bcannon 								= 0;
	refShip.MaxCrew									= 15;
	refShip.OptCrew									= 12;
	refShip.MinCrew									= 1;	
	refShip.SpeedRate								= 7.0;
	refShip.TurnRate								= 75;
	refShip.Price									= 2100;
	refShip.HP										= 150;
	refShip.SP										= 100;
	refship.CanEncounter							= false;
	refship.Type.Merchant							= false;
	refship.Type.War								= false;
	refShip.lowpolycrew 							= 3;

	refShip.Massa 									= 10000.0;
	refShip.Volume 									= 20.0;
	refship.WindAgainstSpeed   						= 1.0;
		
	refship.InertiaAccelerationX	= 3.0;	refship.InertiaBrakingX		= 2.0;
	refship.InertiaAccelerationY	= 14;	refship.InertiaBrakingY		= 5;
	refship.InertiaAccelerationZ	= 5.0;	refship.InertiaBrakingZ		= 3.0;
	
	refShip.Height.Bombs.Y				= 0.4;	refShip.Height.Bombs.DY		= 0.2;
	refShip.Height.Grapes.Y				= 1.3;	refShip.Height.Grapes.DY	= 0.6;
	refShip.Height.Knippels.Y			= 6.5;	refShip.Height.Knippels.DY	= 5.8;
	refShip.Height.Balls.Y				= 0.4;	refShip.Height.Balls.DY		= 0.2;

	refship.Track.Enable	= true;
	refship.Track1.ZStart	= 0.20;
	refship.Track1.LifeTime = 9;
	refship.Track1.Width	= "1.0, 2.0";
	refship.Track1.Speed	= "5.2, 6.2";

	refship.Track2.ZStart	= -0.15;
	refship.Track2.LifeTime = 7;
	refship.Track2.Width	= "1.2, 2.0";
	refship.Track2.Speed	= "0.15, 0.25";
	
	refship.nation.england	= true;
	refship.nation.france	= true;
	refship.nation.spain	= true;
	refship.nation.holland	= true;
	refship.nation.pirate	= false;


	///////////////////////////////////////////////////////////////////////////
	//// квестовый корабль №1 - 5-ый класс
	///////////////////////////////////////////////////////////////////////////
	makeref(refShip,ShipsTypes[SHIP_QUEST1]);
	refShip.Name            			= "QuestShip1";
	refship.Soundtype					= "lugger";
	refShip.Class						= 5;
	refShip.Cannon          			= CANNON_TYPE_CANNON_LBS6;
	refShip.MaxCaliber      			= 12;
	refShip.Weight						= Tonnes2CWT(170);
	refShip.Capacity        			= 900;	
	refShip.CannonsQuantity				= 14; // 2,2,5,5	2,2,4,4
	refShip.CannonsQuantityMin			= 12;
	refShip.rcannon 					= 5;
	refShip.lcannon 					= 5;
	refShip.fcannon 					= 2;
	refShip.bcannon 					= 2;
	
	refShip.MaxCrew         			= 62;
	refShip.OptCrew         			= 50;
	refShip.MinCrew         			= 10;	
	refShip.SpeedRate					= 14.0;
	refShip.TurnRate        			= 55.0;
	refShip.Price           			= 14500;
	refShip.HP              			= 900;
	refShip.SP              			= 100;

	refship.Type.Merchant				= true;
	refship.Type.War					= true;	
	refShip.lowpolycrew 				= 8;
	
	refship.Rocking.y 					= 0.45;
	refship.Rocking.az 					= 0.02;
	
	refship.WaterLine					= 0.0;

	refship.SpeedDependWeight			= 0.2;
	refship.SubSeaDependWeight			= 0.3;
	refship.TurnDependWeight			= 0.3;
	
	refship.WindAgainstSpeed   			= 1.30;

	refShip.Height.Bombs.Y				= 1.6;	refShip.Height.Bombs.DY		= 1.25;
	refShip.Height.Grapes.Y				= 2.75;	refShip.Height.Grapes.DY	= 0.6;
	refShip.Height.Knippels.Y			= 13.2;	refShip.Height.Knippels.DY	= 8.5;
	refShip.Height.Balls.Y				= 1.6;	refShip.Height.Balls.DY		= 1.25;
	
	refship.InertiaAccelerationX	= 8.0;	refship.InertiaBrakingX		= 8.0;
	refship.InertiaAccelerationY	= 8;	refship.InertiaBrakingY		= 8;
	refship.InertiaAccelerationZ	= 8.0;	refship.InertiaBrakingZ		= 8.0;

	refship.Track.Enable	= true;
	refship.Track1.ZStart	= 0.20;
	refship.Track1.LifeTime = 9;
	refship.Track1.Width	= "2.0, 2.5";
	refship.Track1.Speed	= "5.2, 6.2";

	refship.Track2.ZStart	= -0.05;
	refship.Track2.LifeTime = 7;
	refship.Track2.Width	= "3.0, 4.0";
	refship.Track2.Speed	= "0.15, 0.25";
	
	refship.nation.england	= true;
	refship.nation.france	= true;
	refship.nation.spain	= true;
	refship.nation.holland	= true;
	refship.nation.pirate	= true;
	
	
	///////////////////////////////////////////////////////////////////////////
	//// квестовый корабль №2 - 4-ый класс
	///////////////////////////////////////////////////////////////////////////
	makeref(refShip,ShipsTypes[SHIP_QUEST3]);
	refShip.Name				= "QuestShip2";
	refship.Soundtype			= "lugger";
	refShip.Class				= 4;
	refShip.Cannon  			= CANNON_TYPE_CANNON_LBS20;
	refShip.MaxCaliber  		= 20;
	refShip.Weight				= Tonnes2CWT(310);
	refShip.Capacity   			= 2000;
	refShip.CannonsQuantity		= 20;	// 2,2,8,8
	refShip.CannonsQuantityMin	= 20;
	refShip.rcannon 			= 8;
	refShip.lcannon 			= 8;
	refShip.fcannon 			= 2;
	refShip.bcannon 			= 2;	
	refShip.MaxCrew        		= 181;
	refShip.OptCrew        		= 145;
	refShip.MinCrew        		= 22;	
	refShip.SpeedRate      		= 15.5;
	refShip.TurnRate       		= 55.0;
	refShip.Price          		= 35300;
	refShip.HP             		= 2650;
	refShip.SP             		= 100;

	refship.CabinType          	= "Cabin_Medium"; 
	refship.Type.Merchant		= false;
	refship.Type.War			= true;
	refship.QuestShip			= true; 
	refShip.lowpolycrew			= 12;

	refship.WindAgainstSpeed   	= 1.20;
		
	refship.Rocking.y	= 0.5;
	refship.Rocking.az	= 0.04;
	
	refship.WaterLine	= -0.6;
	
	refship.SpeedDependWeight		= 0.3;
	refship.SubSeaDependWeight		= 0.6;
	refship.TurnDependWeight		= 0.3;
	
	refship.InertiaAccelerationX	= 5.5;	refship.InertiaBrakingX	= 5.5;
	refship.InertiaAccelerationY	= 8;	refship.InertiaBrakingY	= 8;
	refship.InertiaAccelerationZ	= 6.0;	refship.InertiaBrakingZ	= 6.0;

	refShip.Height.Bombs.Y	= 1.5;			refShip.Height.Bombs.DY	= 0.7;
	refShip.Height.Grapes.Y	= 2.8;			refShip.Height.Grapes.DY	= 1.4;
	refShip.Height.Knippels.Y	= 16.9;		refShip.Height.Knippels.DY	= 15.4;
	refShip.Height.Balls.Y		= 1.5;		refShip.Height.Balls.DY	= 0.7;
	
	refShip.GeraldSails.rey_b2		= 1;
	refShip.GeraldSails.rey_b3		= 1;
	refShip.GeraldSails.rey_b2.vscale	= 0.8;
	refShip.GeraldSails.rey_b3.vscale	= 0.8;
	
	refship.Track.Enable	= true;
	refship.Track1.ZStart	= 0.20;
	refship.Track1.LifeTime = 12;
	refship.Track1.Width	= "2.0, 3.0";
	refship.Track1.Speed	= "6.0, 8.0";

	refship.Track2.ZStart	= -0.15;
	refship.Track2.LifeTime = 7.5;
	refship.Track2.Width	= "4.0, 6.0";
	refship.Track2.Speed	= "0.15, 0.25";
	
	
	///////////////////////////////////////////////////////////////////////////
	//// квестовый корабль №3 - 4-ый класс
	///////////////////////////////////////////////////////////////////////////
	makeref(refShip,ShipsTypes[SHIP_QUEST3]);
	refShip.Name            			= "QuestShip2";
	refship.Soundtype					= "corvette";
	refShip.Class						= 4;
	refShip.Cannon          			= CANNON_TYPE_CANNON_LBS16;
	refShip.MaxCaliber      			= 18;	
	refShip.Weight						= Tonnes2CWT(320);	
	refShip.Capacity        			= 1800;
	refShip.CannonsQuantity				= 16; // 2,0,7,7	2,0,6,6
	refShip.CannonsQuantityMin			= 14;
	refShip.rcannon 					= 7;
	refShip.lcannon 					= 7;
	refShip.fcannon 					= 2;
	refShip.bcannon 					= 0;		
	refShip.MaxCrew         			= 175;
	refShip.OptCrew         			= 140;
	refShip.MinCrew         			= 16;	
	refShip.SpeedRate       			= 14.0;
	refShip.TurnRate        			= 50.0;
	refShip.Price           			= 33900;
	refShip.HP              			= 2800;
	refShip.SP              			= 100;

	refship.Type.Merchant				= false;
	refship.Type.War					= true;	
	refShip.lowpolycrew 				= 12;

	refship.Rocking.y 					= 0.5;
	refship.Rocking.az 					= 0.04;
	
	refship.WaterLine					= 0.0;
	refship.SpeedDependWeight			= 0.27;
	refship.SubSeaDependWeight			= 0.6;
	refship.TurnDependWeight			= 0.3;
	refship.WindAgainstSpeed   			= 1.40;
	
	refship.CabinType          			= "Cabin_Medium"; 

	refship.InertiaAccelerationX	= 5.5;	refship.InertiaBrakingX		= 5.5;
	refship.InertiaAccelerationY	= 8;	refship.InertiaBrakingY		= 8;
	refship.InertiaAccelerationZ	= 6.0;	refship.InertiaBrakingZ		= 6.0;
	
	refShip.Height.Bombs.Y				= 2.0;		refShip.Height.Bombs.DY		= 1.0;
	refShip.Height.Grapes.Y				= 3.4;		refShip.Height.Grapes.DY	= 1.7;
	refShip.Height.Knippels.Y			= 13.2;		refShip.Height.Knippels.DY	= 11.6;
	refShip.Height.Balls.Y				= 2.0;		refShip.Height.Balls.DY		= 1.0;
	
	refShip.GeraldSails.rey_b2		= 1;
	refShip.GeraldSails.rey_b3		= 1;
	refShip.GeraldSails.rey_b2.vscale		= 0.8;
	refShip.GeraldSails.rey_b3.vscale		= 0.8;
	
	refship.Track.Enable	= true;
	refship.Track1.ZStart	= 0.20;
	refship.Track1.LifeTime = 12;
	refship.Track1.Width	= "2.0, 3.0";
	refship.Track1.Speed	= "6.0, 8.0";

	refship.Track2.ZStart	= -0.15;
	refship.Track2.LifeTime = 7.5;
	refship.Track2.Width	= "4.0, 6.0";
	refship.Track2.Speed	= "0.15, 0.25";
	
	refship.nation.england	= false;
	refship.nation.france	= false
	refship.nation.spain	= true;;
	refship.nation.holland	= false;
	refship.nation.pirate	= true;
	
		
	///////////////////////////////////////////////////////////////////////////
	//// квестовый корабль №4 - 3-ый класс
	///////////////////////////////////////////////////////////////////////////
	makeref(refShip,ShipsTypes[SHIP_QUEST4]);
	refShip.Name						= "QuestShip4";
	refship.Soundtype					= "lugger";
	refShip.Class						= 3;
	refShip.Cannon  					= CANNON_TYPE_CANNON_LBS24;
	refShip.MaxCaliber  				= 24;
	refShip.Weight						= Tonnes2CWT(600);
	refShip.Capacity   					= 3100;
	refShip.CannonsQuantity				= 24; 
	refShip.CannonsQuantityMin			= 24;
	refShip.rcannon 					= 10;
	refShip.lcannon 					= 10;
	refShip.fcannon 					= 2;
	refShip.bcannon 					= 2;
	refShip.MaxCrew        				= 220;
	refShip.OptCrew        				= 175;
	refShip.MinCrew        				= 25;
	
	refShip.SpeedRate      				= 14.25;
	refShip.TurnRate       				= 52.0;
	refShip.Price          				= 55000;
	refShip.HP             				= 3750;
	refShip.SP             				= 100;

	refship.CabinType          			= "Cabin_Medium2";
	refship.Type.Merchant				= false;
	refship.Type.War					= true;
	refship.QuestShip					= true;
	
	refShip.lowpolycrew					= 12;

	refship.WindAgainstSpeed   			= 1.35;
		
	refship.Rocking.y	= 0.5;
	refship.Rocking.az	= 0.04;
	
	refship.WaterLine	= 0.0;
	refship.SpeedDependWeight		= 0.3;
	refship.SubSeaDependWeight		= 0.6;
	refship.TurnDependWeight		= 0.3;
	
	refship.InertiaAccelerationX	= 5.5;	refship.InertiaBrakingX	= 5.5;
	refship.InertiaAccelerationY	= 8;	refship.InertiaBrakingY	= 8;
	refship.InertiaAccelerationZ	= 6.0;	refship.InertiaBrakingZ	= 6.0;

	refShip.Height.Bombs.Y		= 1.7;		refShip.Height.Bombs.DY	= 0.8;
	refShip.Height.Grapes.Y		= 3.4;		refShip.Height.Grapes.DY	= 1.7;
	refShip.Height.Knippels.Y	= 10.1;		refShip.Height.Knippels.DY	= 9.2;
	refShip.Height.Balls.Y		= 1.7;		refShip.Height.Balls.DY	= 0.8;
	
	refShip.GeraldSails.rey_b2			= 1;
	refShip.GeraldSails.rey_b3			= 1;
	refShip.GeraldSails.rey_b2.vscale	= 0.8;
	refShip.GeraldSails.rey_b3.vscale	= 0.8;
	
	refship.Track.Enable	= true;
	refship.Track1.ZStart	= 0.20;
	refship.Track1.LifeTime = 12;
	refship.Track1.Width	= "2.0, 3.0";
	refship.Track1.Speed	= "6.0, 8.0";

	refship.Track2.ZStart	= -0.15;
	refship.Track2.LifeTime = 7.5;
	refship.Track2.Width	= "4.0, 6.0";
	refship.Track2.Speed	= "0.15, 0.25";	

	///////////////////////////////////////////////////////////////////////////
	//// квестовый корабль №5 - 3-ый класс
	///////////////////////////////////////////////////////////////////////////
	makeref(refShip,ShipsTypes[SHIP_QUEST5]);
	refShip.Name            			= "QuestShip5";
	refship.Soundtype					= "corvette";
	refShip.Class						= 3;
	refShip.Cannon          			= CANNON_TYPE_CANNON_LBS16;
	refShip.MaxCaliber      			= 20;
	refShip.Weight						= Tonnes2CWT(600);
	refShip.Capacity        			= 2700;
	refShip.CannonsQuantity				= 20; // 2,2,8,8	2,2,7,7
	refShip.CannonsQuantityMin			= 18;
	refShip.rcannon 					= 8;
	refShip.lcannon 					= 8;
	refShip.fcannon 					= 2;
	refShip.bcannon 					= 2;
	
	refShip.MaxCrew         			= 225;
	refShip.OptCrew						= 180;
	refShip.MinCrew         			= 28;
	
	refShip.SpeedRate					= 14.5;
	refShip.TurnRate        			= 40.0;
	refShip.Price           			= 45500;
	refShip.HP              			= 3250;
	refShip.SP              			= 100;
	
	refship.Type.Merchant				= false;
	refship.Type.War					= true;
	refShip.lowpolycrew 				= 16;

	refship.Rocking.y 					= 0.8;
	refship.Rocking.az 					= 0.025;
	
	refship.WaterLine					= 0.0;
	refship.SpeedDependWeight			= 0.3;
	refship.SubSeaDependWeight			= 0.7;
	refship.TurnDependWeight			= 0.35;
	refship.WindAgainstSpeed   			= 0.60;
	refship.CabinType          			= "Cabin_Medium2";
	
	refship.InertiaAccelerationX	= 8.0;	refship.InertiaBrakingX		= 8.0;
	refship.InertiaAccelerationY	= 6;	refship.InertiaBrakingY		= 6;
	refship.InertiaAccelerationZ	= 6.0;	refship.InertiaBrakingZ		= 6.0;
	
	refShip.Height.Bombs.Y				= 2.614;	refShip.Height.Bombs.DY		= 1.346;
	refShip.Height.Grapes.Y				= 4.694;	refShip.Height.Grapes.DY	= 0.666;
	refShip.Height.Knippels.Y			= 15.333;	refShip.Height.Knippels.DY	= 13.425;
	refShip.Height.Balls.Y				= 2.614;	refShip.Height.Balls.DY		= 1.346;	
	
	refShip.GeraldSails.rey_b2		= 1;
	refShip.GeraldSails.rey_b3		= 1;
	refShip.GeraldSails.rey_b2.vscale		= 0.7;
	refShip.GeraldSails.rey_b3.vscale		= 0.7;

	refship.Track.Enable	= true;
	refship.Track1.ZStart	= 0.17;
	refship.Track1.LifeTime = 12.5;
	refship.Track1.Width	= "4.0, 5.0";
	refship.Track1.Speed	= "6.0, 8.0";

	refship.Track2.ZStart	= -0.15;
	refship.Track2.LifeTime = 6.5;
	refship.Track2.Width	= "5.0, 7.0";
	refship.Track2.Speed	= "0.15, 0.25";
	
	refship.nation.england	= true;
	refship.nation.france	= true;
	refship.nation.spain	= false;
	refship.nation.holland	= false;
	refship.nation.pirate	= true;
	
	///////////////////////////////////////////////////////////////////////////
	//// квестовый корабль №6 - 2-ый класс
	///////////////////////////////////////////////////////////////////////////
	makeref(refShip,ShipsTypes[SHIP_QUEST6]);
	refShip.Name            			= "QuestShip6";
	refship.Soundtype					= "frigate";
	refShip.Class						= 2;
	refShip.Cannon          			= CANNON_TYPE_CANNON_LBS24;
	refShip.MaxCaliber      			= 24;
	refShip.Weight						= Tonnes2CWT(920);
	refShip.Capacity        			= 4000;
	refShip.CannonsQuantity				= 42;	// 4,4,17,17
	refShip.CannonsQuantityMin			= 42;
	refShip.rcannon 					= 17;
	refShip.lcannon 					= 17;
	refShip.fcannon 					= 4;
	refShip.bcannon 					= 4;
	
	refShip.MaxCrew         			= 425;
	refShip.OptCrew         			= 340;
	refShip.MinCrew         			= 50;
	
	refShip.SpeedRate       			= 17.25;
	refShip.TurnRate        			= 37.25;
	refShip.Price           			= 67700;
	refShip.HP              			= 4800;
	refShip.SP              			= 100;

	refship.Type.Merchant				= false;
	refship.Type.War					= true;
	refship.QuestShip					= true; 

	refShip.lowpolycrew 				= 20;
	
	refship.Rocking.y 					= 0.4;
	refship.Rocking.az 					= 0.035;	
	refship.WaterLine					= 0.0;

	refship.SpeedDependWeight			= 0.3;
	refship.SubSeaDependWeight			= 1.0;
	refship.TurnDependWeight			= 0.3;
	refship.WindAgainstSpeed   			= 0.60;
	refship.CabinType          			= "Cabin"; 
	refship.DeckType           			= "Big";
	
	refship.InertiaAccelerationX	= 5.0;	refship.InertiaBrakingX		= 5.0;
	refship.InertiaAccelerationY	= 4;	refship.InertiaBrakingY		= 4;
	refship.InertiaAccelerationZ	= 5.0;	refship.InertiaBrakingZ		= 5.0;
	
	refShip.Height.Bombs.Y				= 3.4;	refShip.Height.Bombs.DY		= 1.5;
	refShip.Height.Grapes.Y				= 5.3;	refShip.Height.Grapes.DY	= 1.575;
	refShip.Height.Knippels.Y			= 19.5;	refShip.Height.Knippels.DY	= 13.5;
	refShip.Height.Balls.Y				= 3.4;	refShip.Height.Balls.DY		= 1.5;
	
	refShip.GeraldSails.rey_b1		= 1;
	refShip.GeraldSails.rey_b2		= 1;
	refShip.GeraldSails.rey_b3		= 1;
	refShip.GeraldSails.rey_b1.vscale		= 0.9;
	refShip.GeraldSails.rey_b2.vscale		= 0.7;
	refShip.GeraldSails.rey_b3.vscale		= 0.7;

	refship.Track.Enable	= true;
	refship.Track1.ZStart	= 0.20;
	refship.Track1.LifeTime = 14.5;
	refship.Track1.Width	= "3.7, 3.9";
	refship.Track1.Speed	= "7.0, 8.0";

	refship.Track2.ZStart	= -0.15;
	refship.Track2.LifeTime = 8.5;
	refship.Track2.Width	= "8.0, 9.0";
	refship.Track2.Speed	= "0.15, 0.25";	
	
	///////////////////////////////////////////////////////////////////////////
	//// квестовый корабль №7 - 2-ый класс
	///////////////////////////////////////////////////////////////////////////
	makeref(refShip,ShipsTypes[SHIP_QUEST7]);
	refShip.Name            			= "QuestShip7";
	refship.Soundtype					= "frigate";
	refShip.Class						= 2;
	refShip.Cannon          			= CANNON_TYPE_CANNON_LBS24;
	refShip.MaxCaliber      			= 32;
	refShip.Weight						= Tonnes2CWT(1200);
	refShip.Capacity        			= 4250;
	refShip.CannonsQuantity				= 50;	// 4,6,20,20	4,6,19,19	4,6,18,18
	refShip.CannonsQuantityMin			= 46;
	refShip.rcannon 					= 20;
	refShip.lcannon 					= 20;
	refShip.fcannon 					= 4;
	refShip.bcannon 					= 6;	
	refShip.MaxCrew         			= 437;
	refShip.OptCrew         			= 350;
	refShip.MinCrew         			= 56;
	
	refShip.SpeedRate       			= 13.5;
	refShip.TurnRate        			= 32.0;
	refShip.Price           			= 73700;
	refShip.HP              			= 5400;
	refShip.SP              			= 100;
	
	refship.Type.Merchant				= false;
	refship.Type.War					= true;
	
	refShip.lowpolycrew 				= 20;
	
	refship.Rocking.y 					= 0.4;
	refship.Rocking.az 					= 0.035;	
	refship.WaterLine					= 0.0;

	refship.SpeedDependWeight			= 0.3;
	refship.SubSeaDependWeight			= 1.0;
	refship.TurnDependWeight			= 0.3;
	refship.WindAgainstSpeed   			= 0.45;
	refship.CabinType          			= "Cabin"; // boal 28.03.05
	refship.DeckType           			= "Big";
		
	refship.InertiaAccelerationX	= 5.0;	refship.InertiaBrakingX		= 5.0;
	refship.InertiaAccelerationY	= 4;	refship.InertiaBrakingY		= 4;
	refship.InertiaAccelerationZ	= 5.0;	refship.InertiaBrakingZ		= 5.0;
	
	refShip.Height.Bombs.Y				= 2.7;		refShip.Height.Bombs.DY		= 1.35;
	refShip.Height.Grapes.Y				= 5.325;	refShip.Height.Grapes.DY	= 1.575;
	refShip.Height.Knippels.Y			= 19.5;		refShip.Height.Knippels.DY	= 13.5;
	refShip.Height.Balls.Y				= 2.7;		refShip.Height.Balls.DY		= 1.35;
	
	refShip.GeraldSails.rey_b1		= 1;
	refShip.GeraldSails.rey_b2		= 1;
	refShip.GeraldSails.rey_b3		= 1;
	refShip.GeraldSails.rey_b1.vscale		= 0.9;
	refShip.GeraldSails.rey_b2.vscale		= 0.7;
	refShip.GeraldSails.rey_b3.vscale		= 0.7;

	refship.Track.Enable	= true;
	refship.Track1.ZStart	= 0.20;
	refship.Track1.LifeTime = 14.5;
	refship.Track1.Width	= "3.7, 3.9";
	refship.Track1.Speed	= "7.0, 8.0";

	refship.Track2.ZStart	= -0.15;
	refship.Track2.LifeTime = 8.5;
	refship.Track2.Width	= "8.0, 9.0";
	refship.Track2.Speed	= "0.15, 0.25";
	
	refship.nation.england	= true;
	refship.nation.france	= true;
	refship.nation.spain	= true;
	refship.nation.holland	= true;
	refship.nation.pirate	= false;

	///////////////////////////////////////////////////////////////////////////
	//// квестовый корабль №8 - 1-ый класс
	///////////////////////////////////////////////////////////////////////////
	makeref(refShip,ShipsTypes[SHIP_QUEST8]);
	refShip.Name            			= "QuestShip8";
	refship.Soundtype					= "lineship";
	refShip.Class						= 1;   // на деле это воен кор
	refShip.Cannon          			= CANNON_TYPE_CANNON_LBS24;
	refShip.MaxCaliber      			= 32;
	refShip.Weight						= Tonnes2CWT(2000);
	refShip.Capacity        			= 5700;
	refShip.CannonsQuantity				= 56;	// 2,4,25,25	2,4,24,24	2,4,23,23	2,4,22,22
	refShip.CannonsQuantityMin			= 48;
	refShip.rcannon 					= 25;
	refShip.lcannon 					= 25;
	refShip.fcannon 					= 2;
	refShip.bcannon 					= 4;	
	refShip.MaxCrew         			= 750;
	refShip.OptCrew         			= 600;
	refShip.MinCrew         			= 80;	
	refShip.SpeedRate					= 13.0;
	refShip.TurnRate        			= 29.0;
	refShip.Price           			= 93800;
	refShip.HP              			= 7000;
	refShip.SP              			= 100;
	refship.Type.Merchant				= false;
	refship.Type.War					= true;
	
	refShip.lowpolycrew 				= 24;

	refship.Rocking.y 					= 0.5;
	refship.Rocking.az 					= 0.035;
		
	refship.WaterLine					= 0.7;
	refship.SpeedDependWeight			= 0.3;
	refship.SubSeaDependWeight			= 1.15;
	refship.TurnDependWeight			= 0.4;
	refship.WindAgainstSpeed            = 0.40;
	refship.CabinType          			= "Cabin_Huge"; 
	refship.DeckType           			= "Big";
	
	refship.InertiaAccelerationX	= 4.5;	refship.InertiaBrakingX		= 4.0;
	refship.InertiaAccelerationY	= 3.5;	refship.InertiaBrakingY		= 3;
	refship.InertiaAccelerationZ	= 4.5;	refship.InertiaBrakingZ		= 4.0;
	
	refShip.Height.Bombs.Y				= 6.7;		refShip.Height.Bombs.DY		= 3.3;
	refShip.Height.Grapes.Y				= 8.3;		refShip.Height.Grapes.DY	= 4.1;
	refShip.Height.Knippels.Y			= 32.1;		refShip.Height.Knippels.DY	= 25.8;
	refShip.Height.Balls.Y				= 6.7;		refShip.Height.Balls.DY		= 3.3;
	
	refShip.GeraldSails.rey_b2		= 1;
	refShip.GeraldSails.rey_b3		= 1;
	refShip.GeraldSails.rey_b1		= 1;
	refShip.GeraldSails.rey_b1.vscale		= 0.8;
	refShip.GeraldSails.rey_b2.vscale		= 0.6;
	refShip.GeraldSails.rey_b3.vscale		= 0.6;

	refship.Track.Enable	= true;
	refship.Track1.ZStart	= 0.15;
	refship.Track1.LifeTime = 16.5;
	refship.Track1.Width	= "3.0, 4.0";
	refship.Track1.Speed	= "8.0, 8.0";

	refship.Track2.ZStart	= -0.25;
	refship.Track2.LifeTime = 10.5;
	refship.Track2.Width	= "6.0, 7.0";
	refship.Track2.Speed	= "0.15, 0.25";	
	
	refship.nation.england	= true;
	refship.nation.france	= true;
	refship.nation.spain	= true;
	refship.nation.holland	= true;
	refship.nation.pirate	= true;
	
	
	// <-- квестовые корабли - заглушки
	
	///////////////////////////////////////////////////////////////////////////
	//// Проклятый "Калеуче" - квестовый
	///////////////////////////////////////////////////////////////////////////
	makeref(refShip,ShipsTypes[SHIP_CURSED_FDM]);
	refShip.Name            			= "Flyingdutchman";  
	refship.Soundtype					= "lineship";
	refShip.Class						= 1;
	refShip.Cannon          			= CANNON_TYPE_CANNON_LBS32;
	refShip.MaxCaliber      			= 36;
	refShip.Weight						= Tonnes2CWT(1500);
	refShip.Capacity        			= 5000;
	refShip.CannonsQuantity				= 56;	// 6,4,23,23
	refShip.CannonsQuantityMin			= 56;
	refShip.rcannon 					= 23;
	refShip.lcannon 					= 23;
	refShip.fcannon 					= 6;
	refShip.bcannon 					= 4;		
	refShip.MaxCrew         			= 777;
	refShip.OptCrew         			= 622;
	refShip.MinCrew         			= 94;	
	refShip.SpeedRate					= 15.2;
	refShip.TurnRate        			= 32.0;
	refShip.Price           			= 100000;
	refShip.HP              			= 6666;
	refShip.SP              			= 100;
	refship.EmblemedSails.normalTex 	= "ships/parus_common.tga";	
	refship.Type.Merchant				= false;
	refship.Type.War					= true;
	refship.QuestShip					= true; 
	
	refShip.lowpolycrew 				= 24;	
	refship.Rocking.y 					= 0.5;
	refship.Rocking.az 					= 0.035;
	
	refship.WaterLine					= 0.5;

	refship.SpeedDependWeight			= 0.35;
	refship.SubSeaDependWeight			= 1.0;
	refship.TurnDependWeight			= 0.4;
	refship.WindAgainstSpeed   			= 0.45;
	
	refship.CabinType          			= "CabineFDM"; 
	refship.DeckType           			= "Big";
		
	refship.InertiaAccelerationX	= 4.0;	refship.InertiaBrakingX		= 3.5;
	refship.InertiaAccelerationY	= 3.0;	refship.InertiaBrakingY		= 2.5;
	refship.InertiaAccelerationZ	= 4.0;	refship.InertiaBrakingZ		= 3.5;
	
	refShip.Height.Bombs.Y				= 6.4;		refShip.Height.Bombs.DY		= 3.2;
	refShip.Height.Grapes.Y				= 8.5;		refShip.Height.Grapes.DY	= 4.2;
	refShip.Height.Knippels.Y			= 27.4;		refShip.Height.Knippels.DY	= 23.4;
	refShip.Height.Balls.Y				= 6.4;		refShip.Height.Balls.DY		= 3.2;
	
	refShip.GeraldSails.rey_b2		= 1;
	refShip.GeraldSails.rey_b3		= 1;
	refShip.GeraldSails.rey_b1		= 1;
	refShip.GeraldSails.rey_b1.vscale		= 0.8;
	refShip.GeraldSails.rey_b2.vscale		= 0.65;
	refShip.GeraldSails.rey_b3.vscale		= 0.55;

	refship.Track.Enable	= true;
	refship.Track1.ZStart	= 0.25;
	refship.Track1.LifeTime = 9.5;
	refship.Track1.Width	= "7.0, 7.5";
	refship.Track1.Speed	= "8.0, 9.0";

	refship.Track2.ZStart	= -0.15;
	refship.Track2.LifeTime = 7.5;
	refship.Track2.Width	= "8.0, 10.0";
	refship.Track2.Speed	= "1.0, 2.0";

	///////////////////////////////////////////////////////////////////////////
	//// Копия "Калеуче" - квестовый
	///////////////////////////////////////////////////////////////////////////
	makeref(refShip,ShipsTypes[SHIP_FDM]);
	refShip.Name            			= "Flyingdutchman_l";  
	refship.Soundtype					= "lineship";
	refShip.Class						= 1;
	refShip.Cannon          			= CANNON_TYPE_CANNON_LBS32;
	refShip.MaxCaliber      			= 32;
	refShip.Weight						= Tonnes2CWT(1500);
	refShip.Capacity        			= 5000;
	refShip.CannonsQuantity				= 56;	// 6,4,23,23
	refShip.CannonsQuantityMin			= 56;
	refShip.rcannon 					= 23;
	refShip.lcannon 					= 23;
	refShip.fcannon 					= 6;
	refShip.bcannon 					= 4;		
	refShip.MaxCrew         			= 777;
	refShip.OptCrew         			= 622;
	refShip.MinCrew         			= 94;	
	refShip.SpeedRate					= 15.2;
	refShip.TurnRate        			= 32.0;
	refShip.Price           			= 100000;
	refShip.HP              			= 6600;
	refShip.SP              			= 100;
	refship.EmblemedSails.normalTex 	= "ships/parus_common.tga";	
	refship.Type.Merchant				= false;
	refship.Type.War					= true;
	refship.QuestShip					= true; 
	
	refShip.lowpolycrew 				= 24;	
	refship.Rocking.y 					= 0.5;
	refship.Rocking.az 					= 0.035;
	
	refship.WaterLine					= 0.5;

	refship.SpeedDependWeight			= 0.35;
	refship.SubSeaDependWeight			= 1.0;
	refship.TurnDependWeight			= 0.4;
	refship.WindAgainstSpeed   			= 0.45;
	
	refship.CabinType          			= "Cabin_Huge"; 
	refship.DeckType           			= "Big";
		
	refship.InertiaAccelerationX	= 4.0;	refship.InertiaBrakingX		= 3.5;
	refship.InertiaAccelerationY	= 3.0;	refship.InertiaBrakingY		= 2.5;
	refship.InertiaAccelerationZ	= 4.0;	refship.InertiaBrakingZ		= 3.5;
	
	refShip.Height.Bombs.Y				= 6.4;		refShip.Height.Bombs.DY		= 3.2;
	refShip.Height.Grapes.Y				= 8.5;		refShip.Height.Grapes.DY	= 4.2;
	refShip.Height.Knippels.Y			= 27.4;		refShip.Height.Knippels.DY	= 23.4;
	refShip.Height.Balls.Y				= 6.4;		refShip.Height.Balls.DY		= 3.2;
	
	refShip.GeraldSails.rey_b2		= 1;
	refShip.GeraldSails.rey_b3		= 1;
	refShip.GeraldSails.rey_b1		= 1;
	refShip.GeraldSails.rey_b1.vscale		= 0.8;
	refShip.GeraldSails.rey_b2.vscale		= 0.65;
	refShip.GeraldSails.rey_b3.vscale		= 0.55;

	refship.Track.Enable	= true;
	refship.Track1.ZStart	= 0.25;
	refship.Track1.LifeTime = 9.5;
	refship.Track1.Width	= "7.0, 7.5";
	refship.Track1.Speed	= "8.0, 9.0";

	refship.Track2.ZStart	= -0.15;
	refship.Track2.LifeTime = 7.5;
	refship.Track2.Width	= "8.0, 10.0";
	refship.Track2.Speed	= "1.0, 2.0";

	///////////////////////////////////////////////////////////////////////////
	//// Линейный корабль "Реус де Сан-Педро" - квестовый
	///////////////////////////////////////////////////////////////////////////
	makeref(refShip,ShipsTypes[SHIP_LSHIP_QUEST]);
	refShip.Name            			= "Santisima";
	refship.Soundtype					= "manowar";
	refShip.Class						= 1;
	refShip.Cannon          			= CANNON_TYPE_CANNON_LBS42;
	refShip.MaxCaliber      			= 42;
	refShip.Weight						= Tonnes2CWT(3500);
	refShip.Capacity        			= 8500;
	refShip.CannonsQuantity				= 106; // 6,8,38,38
	refShip.CannonsQuantityMin			= 106;
	refShip.rcannon 					= 46;
	refShip.lcannon 					= 46;
	refShip.fcannon 					= 6;
	refShip.bcannon 					= 8;	
	refShip.MaxCrew         			= 1000;
	refShip.OptCrew         			= 800;
	refShip.MinCrew         			= 190;
	
	refShip.SpeedRate					= 13.0;
	refShip.TurnRate        			= 30.0;
	refShip.Price           			= 141600;
	refShip.HP              			= 12600;
	refShip.SP              			= 100;
	refship.EmblemedSails.normalTex 	= "ships\parus_silk.tga";

	refship.CanEncounter 				= false;	
	refship.Type.Merchant				= false;
	refship.Type.War					= true;
	refship.QuestShip					= true; 
	refShip.lowpolycrew 				= 28;

	refship.Rocking.y 					= 0.3;
	refship.Rocking.az 					= 0.02;

	refship.WaterLine					= 0.5;
	refship.SpeedDependWeight			= 0.45;
	refship.SubSeaDependWeight			= 1.8;
	refship.TurnDependWeight			= 0.45;
	refship.WindAgainstSpeed   			= 0.30;
	refship.CabinType          			= "Cabin_Huge"; // boal 28.03.05
	refship.DeckType           			= "Big";
	
	refship.InertiaAccelerationX	= 2.0;	refship.InertiaBrakingX		= 2.0;
	refship.InertiaAccelerationY	= 2;	refship.InertiaBrakingY		= 2;
	refship.InertiaAccelerationZ	= 2.0;	refship.InertiaBrakingZ		= 2.0;
	
	refShip.Height.Bombs.Y				= 8.0;		refShip.Height.Bombs.DY		= 4.0;
	refShip.Height.Grapes.Y				= 9.7;		refShip.Height.Grapes.DY	= 4.8;
	refShip.Height.Knippels.Y			= 34.7;		refShip.Height.Knippels.DY	= 26.0;
	refShip.Height.Balls.Y				= 8.0;		refShip.Height.Balls.DY		= 4.0;
	
	refShip.GeraldSails.rey_b2				= 1;
	refShip.GeraldSails.rey_b3				= 1;
	refShip.GeraldSails.rey_c1				= 1;
	refShip.GeraldSails.rey_c1.vscale		= 0.98;
	refShip.GeraldSails.rey_b2.vscale		= 0.98;
	refShip.GeraldSails.rey_b3.vscale		= 0.98;

	refship.Track.Enable	= true;
	refship.Track1.ZStart	= 0.30;
	refship.Track1.LifeTime = 18.5;
	refship.Track1.Width	= "6.5, 7.5";
	refship.Track1.Speed	= "8.0, 9.0";

	refship.Track2.ZStart	= -0.15;
	refship.Track2.LifeTime = 10.5;
	refship.Track2.Width	= "16.0, 18.0";
	refship.Track2.Speed	= "0.15, 0.25";
	
	///////////////////////////////////////////////////////////////////////////
	//// FORT
	///////////////////////////////////////////////////////////////////////////
	makeref(refShip,ShipsTypes[SHIP_FORT]);
	refShip.Name								= "Fort";
	refShip.isFort      						= true; // для удобства проверок на rRealShip
	refShip.Class								= 1;
	refShip.Cannon          					= CANNON_TYPE_CANNON_LBS36;
	refShip.MaxCaliber							= 48;
	refShip.Weight								= Tonnes2CWT(22500);
	refShip.Capacity							= 300000;
	refShip.CannonsQuantity						= 68;
	refShip.CannonsQuantityMin					= 68;
	refShip.rcannon 							= 68;
	refShip.lcannon 							= 0;
	refShip.fcannon 							= 0;
	refShip.bcannon 							= 0;
	refShip.MaxCrew         					= 1800;
	refShip.OptCrew         					= 1600;
	refShip.MinCrew         					= 400;
	refShip.SpeedRate							= 0.0;
	refShip.TurnRate							= 0;
	refShip.Price								= 12000;
	refShip.HP									= 54000;
	refShip.SP									= 100;
	refShip.CanEncounter						= false;

	/// Check
	for (int i=0; i<SHIP_TYPES_QUANTITY_WITH_FORT-1; i++)
	{
	  	makeref(refShip, ShipsTypes[i]);
		if (!CheckAttribute(refShip,"Name")) { continue; }
		if (!CheckAttribute(refShip,"TurnRate"))
		{
			Trace("ERROR: Ship " + i + " doesn't have TurnRate attribute");
		}
		if (!CheckAttribute(refShip,"SpeedRate"))
		{
			Trace("ERROR: Ship " + i + " doesn't have SpeedRate attribute");
		}
		if (!CheckAttribute(refShip,"Class"))
		{
			Trace("ERROR: Ship " + i + " doesn't have class attribute");
		}
		else
		{
			int iClass = sti(refShip.Class);
			if (iClass > 6) { Trace("ERROR: Ship " + i + " class > 6"); }
			if (iClass < 1) { Trace("ERROR: Ship " + i + " class < 1"); }
		}
		refship.InertiaAccelerationY = stf(refship.InertiaAccelerationY) / 6.0;
		// boal 10/11/05 пробить оптимальный экипаж
		//refShip.OptCrew = sti(refShip.MaxCrew);
		//refShip.MaxCrew = makeint(sti(refShip.MaxCrew) * 1.25 + 0.5); // перегруз
		/// как говаривал мой папа - нахрена попу гармонь?  Приходится приводить к каноническому виду, править все буковки по файлу мне лень
		refShip.cannonr  = refShip.rcannon;
		refShip.cannonl  = refShip.lcannon;
		refShip.cannonf  = refShip.fcannon;
		refShip.cannonb  = refShip.bcannon;
	}
}