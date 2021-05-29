#include "Net\Common\cannons.h"

int iNetCannonsNum;

int NETCANNON_CANNON, NETCANNON_CULVERINE, NETCANNON_MORTAR;

ref Net_GetCannonByIndex(int iIndex) { return &NetCannons[iIndex]; }
int Net_GetCannonsNum() { return iNetCannonsNum; }

void Net_InitCannonsCalcSpeedV0(ref rCannon, float fFireRange)
{
	rCannon.FireRange = fFireRange;
	rCannon.SpeedV0 = sqrt(fFireRange * 9.81 / sin( 2.0 * MakeFloat(rCannon.FireAngMax)) );
}

int Net_GetCannonCost(int iCannonIndex)
{
	if (iCannonIndex < 0) { return 0; }
	return sti(NetCannons[iCannonIndex].Cost);
}

int Net_GetCannonUpgradeCost(int iCannonIndex, int iUpgradeType)
{
	if (iCannonIndex < 0) { return 0; }
	if (iUpgradeType < 0) { return 0; }

	string sUpgrade = "Upgrade" + (iUpgradeType + 1);
	return sti(NetCannons[iCannonIndex].(sUpgrade));
}

void Net_InitCannons()
{
	ref rCannon;
	int n = 0;

	makeref(rCannon,NetCannons[NET_CANNON_TYPE_CANNON_LBS3]);
	rCannon.type = NET_CANNON_NAME_CANNON;
	rCannon.name = "cannon";
	rCannon.picture = "Cannon_3";
	rCannon.Sound = "cannon_fire_cannon_3";
	rCannon.caliber = 3;
	rCannon.ReloadTime = 10;
	rCannon.Cost = 105;
	rCannon.Weight = 3;
	rCannon.FireAngMax = 0.60;
	rCannon.FireAngMin = -0.35;
	rCannon.TimeSpeedMultiply = 1.0;
	rCannon.BigBall = 0;
	rCannon.SizeMultiply = 1.0;
	rCannon.HeightMultiply = 1.0;
	rCannon.DamageMultiply = 1.0;
	rCannon.hp = 20.0;
	rCannon.Upgrade1 = 0;
	rCannon.Upgrade2 = 30;
	rCannon.Upgrade3 = 60;
	Net_InitCannonsCalcSpeedV0(&rCannon,350.0);
	n++;
	
	makeref(rCannon,NetCannons[NET_CANNON_TYPE_CANNON_LBS6]);
	rCannon.type = NET_CANNON_NAME_CANNON;
	rCannon.name = "cannon";
	rCannon.picture = "Cannon_6";
	rCannon.Sound = "cannon_fire_cannon_6";
	rCannon.caliber = 6;
	rCannon.ReloadTime = 19;
	rCannon.Cost = 215;
	rCannon.Weight = 6;
	rCannon.FireAngMax = 0.60;
	rCannon.FireAngMin = -0.35;
	rCannon.TimeSpeedMultiply = 1.0;
	rCannon.BigBall = 0;
	rCannon.SizeMultiply = 1.0;
	rCannon.HeightMultiply = 1.0;
	rCannon.DamageMultiply = 1.5;
	rCannon.hp = 45.0;
	rCannon.Upgrade1 = 0;
	rCannon.Upgrade2 = 30;
	rCannon.Upgrade3 = 60;
	Net_InitCannonsCalcSpeedV0(&rCannon,450.0);
	n++;
	
	makeref(rCannon,NetCannons[NET_CANNON_TYPE_CANNON_LBS12]);
	rCannon.type = NET_CANNON_NAME_CANNON;
	rCannon.name = "cannon";
	rCannon.picture = "Cannon_12";
	rCannon.Sound = "cannon_fire_cannon_12";
	rCannon.caliber = 12;
	rCannon.ReloadTime = 31;
	rCannon.Cost = 425;
	rCannon.Weight = 11;
	rCannon.FireAngMax = 0.60;
	rCannon.FireAngMin = -0.35;
	rCannon.TimeSpeedMultiply = 1.0;
	rCannon.BigBall = 0;
	rCannon.SizeMultiply = 1.0;
	rCannon.HeightMultiply = 1.0;
	rCannon.DamageMultiply = 2.0;
	rCannon.hp = 79.0;
	rCannon.Upgrade1 = 0;
	rCannon.Upgrade2 = 30;
	rCannon.Upgrade3 = 60;
	Net_InitCannonsCalcSpeedV0(&rCannon,550.0);
	n++;

	makeref(rCannon,NetCannons[NET_CANNON_TYPE_CANNON_LBS16]);
	rCannon.type = NET_CANNON_NAME_CANNON;
	rCannon.name = "cannon";
	rCannon.picture = "Cannon_16";
	rCannon.Sound = "cannon_fire_cannon_16";
	rCannon.caliber = 16;
	rCannon.ReloadTime = 40;
	rCannon.Cost = 600;
	rCannon.Weight = 16;
	rCannon.FireAngMax = 0.60;
	rCannon.FireAngMin = -0.35;
	rCannon.TimeSpeedMultiply = 1.0;
	rCannon.BigBall = 0;
	rCannon.SizeMultiply = 1.0;
	rCannon.HeightMultiply = 1.0;
	rCannon.DamageMultiply = 2.5;
	rCannon.Upgrade1 = 0;
	rCannon.Upgrade2 = 30;
	rCannon.Upgrade3 = 60;
	rCannon.hp = 76.0;
	Net_InitCannonsCalcSpeedV0(&rCannon,600.0);
	n++;
		
	makeref(rCannon,NetCannons[NET_CANNON_TYPE_CANNON_LBS20]);
	rCannon.type = NET_CANNON_NAME_CANNON;
	rCannon.name = "cannon";
	rCannon.picture = "Cannon_20";
	rCannon.Sound = "cannon_fire_cannon_20";
	rCannon.caliber = 20;
	rCannon.ReloadTime = 48;
	rCannon.Weight = 20;
	rCannon.Cost = 815;
	rCannon.FireAngMax = 0.60;
	rCannon.FireAngMin = -0.35;
	rCannon.TimeSpeedMultiply = 1.0;
	rCannon.BigBall = 0;
	rCannon.SizeMultiply = 1.0;
	rCannon.HeightMultiply = 1.0;
	rCannon.DamageMultiply = 3.0;
	rCannon.hp = 73.0;
	rCannon.Upgrade1 = 0;
	rCannon.Upgrade2 = 30;
	rCannon.Upgrade3 = 60;
	Net_InitCannonsCalcSpeedV0(&rCannon,650.0);
	n++;
	
	makeref(rCannon,NetCannons[NET_CANNON_TYPE_CANNON_LBS24]);
	rCannon.type = NET_CANNON_NAME_CANNON;
	rCannon.name = "cannon";
	rCannon.picture = "Cannon_24";
	rCannon.Sound = "cannon_fire_cannon_24";
	rCannon.caliber = 24;
	rCannon.ReloadTime = 56;
	rCannon.Weight = 29;
	rCannon.Cost = 1200;
	rCannon.FireAngMax = 0.60;
	rCannon.FireAngMin = -0.35;
	rCannon.TimeSpeedMultiply = 1.0;
	rCannon.BigBall = 0;
	rCannon.SizeMultiply = 1.0;
	rCannon.HeightMultiply = 1.0;
	rCannon.DamageMultiply = 4.0;
	rCannon.hp = 70.0;
	rCannon.Upgrade1 = 0;
	rCannon.Upgrade2 = 30;
	rCannon.Upgrade3 = 60;
	Net_InitCannonsCalcSpeedV0(&rCannon,700.0);
	n++;
	
	makeref(rCannon,NetCannons[NET_CANNON_TYPE_CANNON_LBS32]);
	rCannon.type = NET_CANNON_NAME_CANNON;
	rCannon.caliber = 32;
	rCannon.name = "cannon";
	rCannon.picture = "Cannon_32";
	rCannon.Sound = "cannon_fire_cannon_32";
	rCannon.ReloadTime = 61;
	rCannon.Cost = 1705;
	rCannon.Weight = 40;
	rCannon.FireAngMax = 0.60;
	rCannon.FireAngMin = -0.45;
	rCannon.TimeSpeedMultiply = 1.0;
	rCannon.BigBall = 0;
	rCannon.SizeMultiply = 1.0;
	rCannon.HeightMultiply = 1.0;
	rCannon.DamageMultiply = 5.0;
	rCannon.hp = 65.0;
	rCannon.Upgrade1 = 0;
	rCannon.Upgrade2 = 30;
	rCannon.Upgrade3 = 60;
	Net_InitCannonsCalcSpeedV0(&rCannon,650.0);
	n++;
	
	makeref(rCannon,NetCannons[NET_CANNON_TYPE_CANNON_LBS36]);
	rCannon.type = NET_CANNON_NAME_CANNON;
	rCannon.caliber = 36;
	rCannon.name = "cannon";
	rCannon.picture = "Cannon_36";
	rCannon.Sound = "cannon_fire_cannon_36";
	rCannon.ReloadTime = 63;
	rCannon.Cost = 2055;
	rCannon.Weight = 46;
	rCannon.FireAngMax = 0.60;
	rCannon.FireAngMin = -0.35;
	rCannon.TimeSpeedMultiply = 1.0;
	rCannon.BigBall = 0;
	rCannon.SizeMultiply = 1.0;
	rCannon.HeightMultiply = 1.0;
	rCannon.DamageMultiply = 6.0;
	rCannon.TradeOff = true;
	rCannon.hp = 60.0;
	rCannon.Upgrade1 = 0;
	rCannon.Upgrade2 = 30;
	rCannon.Upgrade3 = 60;
	Net_InitCannonsCalcSpeedV0(&rCannon,600.0); 
	n++;
	
	NETCANNON_CANNON = n - 1;
	
	
    makeref(rCannon,NetCannons[NET_CANNON_TYPE_CULVERINE_LBS8]);
	rCannon.type = NET_CANNON_NAME_CULVERINE;
	rCannon.name = "culverine";
	rCannon.picture = "Culverine_8";
	rCannon.Sound = "cannon_fire_culverine_8";
	rCannon.caliber = 8;
	rCannon.ReloadTime = 35;
	rCannon.Cost = 345;
	rCannon.Weight = 16;
	rCannon.FireAngMax = 0.60;
	rCannon.FireAngMin = -0.35;
	rCannon.TimeSpeedMultiply = 1.0;
	rCannon.BigBall = 0;
	rCannon.SizeMultiply = 1.0;
	rCannon.HeightMultiply = 1.0;
	rCannon.DamageMultiply = 2.0;
	rCannon.hp = 60.0;
	rCannon.Upgrade1 = 0;
	rCannon.Upgrade2 = 30;
	rCannon.Upgrade3 = 60;
	Net_InitCannonsCalcSpeedV0(&rCannon,700.0);
	n++;
	
	makeref(rCannon,NetCannons[NET_CANNON_TYPE_CULVERINE_LBS18]);
	rCannon.type = NET_CANNON_NAME_CULVERINE;
	rCannon.name = "culverine";
	rCannon.picture = "Culverine_18";
	rCannon.Sound = "cannon_fire_culverine_18";
	rCannon.caliber = 18;
	rCannon.ReloadTime = 52;
	rCannon.Cost = 885;
	rCannon.Weight = 32;
	rCannon.FireAngMax = 0.60;
	rCannon.FireAngMin = -0.35;
	rCannon.TimeSpeedMultiply = 1.0;
	rCannon.BigBall = 0;
	rCannon.SizeMultiply = 1.0;
	rCannon.HeightMultiply = 1.0;
	rCannon.DamageMultiply = 3.0;
	rCannon.hp = 75.0;
	rCannon.Upgrade1 = 0;
	rCannon.Upgrade2 = 30;
	rCannon.Upgrade3 = 60;
	Net_InitCannonsCalcSpeedV0(&rCannon,850.0);
	n++;

    makeref(rCannon,NetCannons[NET_CANNON_TYPE_CULVERINE_LBS36]);
	rCannon.type = NET_CANNON_NAME_CULVERINE;
	rCannon.caliber = 36;
	rCannon.name = "culverine";
	rCannon.picture = "Culverine_36";
	rCannon.Sound = "cannon_fire_culverine_36";
	rCannon.ReloadTime = 70;
	rCannon.Cost = 2545;
	rCannon.Weight = 50;
	rCannon.FireAngMax = 0.60;
	rCannon.FireAngMin = -0.45;
	rCannon.TimeSpeedMultiply = 1.0;
	rCannon.BigBall = 0;
	rCannon.SizeMultiply = 1.0;
	rCannon.HeightMultiply = 1.0;
	rCannon.DamageMultiply = 5.5;
	rCannon.TradeOff = true;
	rCannon.hp = 80.0;
	rCannon.Upgrade1 = 0;
	rCannon.Upgrade2 = 30;
	rCannon.Upgrade3 = 60;
	Net_InitCannonsCalcSpeedV0(&rCannon,900.0);
	n++;
	
	NETCANNON_CULVERINE = n - 1;
	NETCANNON_MORTAR 	= n - 1;
	iNetCannonsNum 		= n;
}
