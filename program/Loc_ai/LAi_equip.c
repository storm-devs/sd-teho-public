#define PERK_TEMPLATE_SHIPDEFENCE	0	// 3 perks
#define PERK_TEMPLATE_REPAIR		1	// 2 perks
#define PERK_TEMPLATE_CANNONS		2	// 8 perks
#define PERK_TEMPLATE_COMMERCE		3	// 5 perks
#define PERK_TEMPLATE_SAILING		4	// 5 perks
#define PERK_TEMPLATE_GRAPPLING		5	// 3 perks
#define PERK_TEMPLATE_MELEE		    6	// 9 perks
#define PERK_TEMPLATE_PERSONAL		7	// 6 perks
#define PERK_TEMPLATE_LAST          8

//Экипировать NPC оружием и перками (переделал полнсотью 11/11/04 boal)
void LAi_NPC_Equip(ref chr, int rank, bool isWeapons, bool isGun)
{
	// boal не нужно - ранг и так точно расчитан r = rank + rand(3) - 1;
	string sBullet = "bullet";
	string sGunPowder;
	
	DeleteAttribute(chr, "equip");
	DeleteAttribute(chr, "perks.list"); // FIX 101104 убрать накопивщиеся умения
	DelBakSkillAttr(chr); // fix
	
	if (chr.model.animation == "mushketer") return;
	if (chr.sex == "woman") return;
	
	if (CheckAttribute(chr, "quest.officertype"))
	{
		// наши офицеры
		LAi_NPC_EquipPerk(chr, chr.quest.officertype);
	}
	else
	{
		LAi_NPC_EquipPerk(chr, "fantom");
	}
	
	//Подберём саблю
	if(isWeapons)
	{
		string blade;
		if (CheckAttribute(chr, "CityType") && chr.CityType == "soldier")
		{   // у солдат в городе свои сабли
			blade = LAi_Soldier_EquipBlade();
		}
		else
		{
            blade = LAi_NPC_EquipBladeSelection(chr);
		}
		
		DeleteAttribute(chr, "items"); // это можно не делать, но так наверняка (идет проверка на колво предметов, и сабель может стать вагон)
		//DeleteAttribute(chr, "cirassId"); // трем броню
		
		// Warship Нет, не генерим все-таки, с отображением жопа - ищет models/ammo/blade4_xxx :(
		// Ugeen -- > и все-таки генерим !! :)
		blade = GetGeneratedItem(blade); // Генерим оружие
		
		GiveItem2Character(chr, blade);
		EquipCharacterByItem(chr, blade);
		// boal -->
		if(rand(1500) < MOD_SKILL_ENEMY_RATE*100)
        {
		   TakeNItems(chr, "potion1", rand(makeint(rank/(11-MOD_SKILL_ENEMY_RATE) +0.5))); // даю меньше
		}
		// boal <--
	}
    else
    {
		isGun = false;
	}
	// boal выдаем пистоль -->
	if(isGun)
	{
		if(CheckAttribute(chr, "PhantomType") && chr.PhantomType == "native") return; //Jason
		if(CheckAttribute(chr, "PhantomType") && chr.PhantomType == "slave") return; //Jason
		
		if(rand(1000) < MOD_SKILL_ENEMY_RATE * sti(chr.rank) * 8)
		{
			int iRnd = rand(1);
			if(sti(chr.rank) > 10) iRnd = rand(2);
			if(sti(chr.rank) > 15) iRnd = rand(2) + 1;
			if(sti(chr.rank) > 20) iRnd = rand(3) + 2;
				
			switch(iRnd)
			{
				case 0:
					if(rand(100) < 70)
					{
						GiveItem2Character(chr, "pistol1");
						EquipCharacterByItem(chr, "pistol1");
						sBullet = "bullet";
					}	
				break;
				
				case 1:
					if(rand(100) < 75)
					{
						GiveItem2Character(chr, "pistol3");
						EquipCharacterByItem(chr, "pistol3");
						sBullet = "grapeshot";
					}	
				break;
				
				case 2:
					if(rand(100) < 80)
					{
						GiveItem2Character(chr, "pistol6");
						EquipCharacterByItem(chr, "pistol6");				
						sBullet = "bullet";
					}	
				break;
				
				case 3:
					if(rand(100) < 85)
					{
						GiveItem2Character(chr, "pistol2");
						EquipCharacterByItem(chr, "pistol2");
						sBullet = "grapeshot";
					}	
				break;
				
				case 4:
					if(rand(100) < 90)
					{
						GiveItem2Character(chr, "pistol4");
						EquipCharacterByItem(chr, "pistol4");
						sBullet = "bullet";
					}	
				break;
				
				case 5:
					if(rand(100) < 95)
					{
						GiveItem2Character(chr, "pistol5");
						EquipCharacterByItem(chr, "pistol5");
						sBullet = "bullet";
					}	
				break;
			}
			TakeNItems(chr, sBullet, 5 + rand(10));// boal gun bullet
			LAi_SetCharacterUseBullet(chr, sBullet);
			sGunPowder = LAi_GetCharacterGunpowderType(chr);
			if(sGunPowder != "")
			{
				AddItems(chr, sGunPowder, 5 + rand(10)); // Warship. Порох
			}	
		}
	}
	// boal выдаем пистоль <--
}

void LAi_NPC_MushketerEquip(ref chr)
{
	string sMush 	= "mushket1";
	string sBullet 	= "bullet";

	while (FindCharacterItemByGroup(chr, BLADE_ITEM_TYPE) != "")
    {
        TakeItemFromCharacter(chr, FindCharacterItemByGroup(chr, BLADE_ITEM_TYPE));
    }
    while (FindCharacterItemByGroup(chr, GUN_ITEM_TYPE) != "")
    {             
        TakeItemFromCharacter(chr, FindCharacterItemByGroup(chr, GUN_ITEM_TYPE));
    }		
	GiveItem2Character(chr, "unarmed");
	EquipCharacterbyItem(chr, "unarmed");
	
	if(CheckAttribute(chr, "MushketBulletType"))	sBullet = chr.MushketBulletType;
	if(CheckAttribute(chr, "MushketType")) 			sMush 	= chr.MushketType;
	else
	{
		if(CheckAttribute(chr, "model"))
		{
			if(HasSubStr(chr.model, "mush_eng_") || HasSubStr(chr.model, "mush_hol_")) sMush = "mushket2";
			if(HasSubStr(chr.model, "mush_fra_") || HasSubStr(chr.model, "mush_spa_")) sMush = "mushket1";
			
			if(HasSubStr(chr.model, "mush_cnb_") || HasSubStr(chr.model, "mush_msk_") || HasSubStr(chr.model, "mush_itza_")) 
			{
				if(rand(1) == 0) sMush = "mushket1";
				else			 sMush = "mushket3";
			}	
			
			if(HasSubStr(chr.model, "mush_ctz_") || HasSubStr(chr.model, "mushketer_")) 
			{
				if(rand(1) == 0) sMush = "mushket1";
				else			 sMush = "mushket3";
			}	
			
			if(HasSubStr(chr.model, "mush_rvd_")) sMush = "mushket1";
		}
	}
			
	GiveItem2Character(chr, sMush);
	EquipCharacterbyItem(chr, sMush);
	
	switch (sMush)
	{
		case "mushket1"		:
			AddItems(chr, "cartridge", 	50);
			AddItems(chr, "bullet", 	50);
			AddItems(chr, "gunpowder", 	50);
			if(CheckAttribute(chr, "MushketType") && 
			   CheckAttribute(chr, "MushketBulletType")) 	LAi_SetCharacterUseBullet(chr, sBullet);
			else											LAi_SetCharacterDefaultBulletType(chr);
		break;
		case "mushket2"		:
			AddItems(chr, "cartridge", 	50);
			AddItems(chr, "bullet", 	50);
			AddItems(chr, "gunpowder", 	50);
			if(CheckAttribute(chr, "MushketType") && 
			   CheckAttribute(chr, "MushketBulletType")) 	LAi_SetCharacterUseBullet(chr, sBullet);
			else											LAi_SetCharacterDefaultBulletType(chr);		
		break;
		case "mushket3"		:
			AddItems(chr, "grapeshot", 	50);
			AddItems(chr, "gunpowder", 	50);
			LAi_SetCharacterUseBullet(chr, "grapeshot");		
		break;
		case "mushket5"		:
			AddItems(chr, "cartridge", 	50);
			AddItems(chr, "bullet", 	50);
			AddItems(chr, "gunpowder", 	50);
			if(CheckAttribute(chr, "MushketType") && 
			   CheckAttribute(chr, "MushketBulletType")) 	LAi_SetCharacterUseBullet(chr, sBullet);
			else											LAi_SetCharacterDefaultBulletType(chr);		
		break;
		case "mushket6"		:
			AddItems(chr, "grapeshot", 	50);
			AddItems(chr, "gunpowder", 	50);
			
			if(CheckAttribute(chr, "MushketType") && 
			   CheckAttribute(chr, "MushketBulletType")) 
			{
				if(sBullet == "GunEchin") AddItems(chr, sBullet, 15);
				LAi_SetCharacterUseBullet(chr, sBullet);
			}
			else
			{
				LAi_SetCharacterUseBullet(chr, "grapeshot");		
			}			
		break;
		case "grape_mushket":
			if(CheckAttribute(chr, "MushketBulletType")) 
			{
				AddItems(chr, sBullet, 15);
				LAi_SetCharacterUseBullet(chr, sBullet);		
			}
			else
			{
				if(rand(1) == 0)
				{
					AddItems(chr, "grenade", 	15);
					LAi_SetCharacterUseBullet(chr, "grenade");		
				}
				else
				{
					AddItems(chr, "powder_pellet", 	15);
					LAi_SetCharacterUseBullet(chr, "powder_pellet");		
				}
			}
		break;
		
		case "mushket2x2"	:
			AddItems(chr, "cartridge", 	50);
			AddItems(chr, "bullet", 	50);
			AddItems(chr, "gunpowder", 	50);
			if(CheckAttribute(chr, "MushketType") && 
			   CheckAttribute(chr, "MushketBulletType")) 	LAi_SetCharacterUseBullet(chr, sBullet);
			else											LAi_SetCharacterDefaultBulletType(chr);		
		break;
	}
			
	chr.isMusketer = true;
	chr.isMusketer.weapon = true; // Jason: а пули с порохом кто удалять будет? И вообще, что за муть - менять мушкет при каждой установке типа?
	if (!CheckAttribute(chr, "MusketerDistance")) chr.MusketerDistance = 10.0 + frand(10.0);
}

string LAi_NPC_EquipBladeSelection(ref chr)
{
	string sType;
	string blade;
	
	if(CheckAttribute(chr, "PhantomType"))
	{
		sType = chr.PhantomType;
		switch( sType )
		{
			case "slave" 		:
				blade = SelectGeneratedItem(TGT_YANKEE, "", "");
				if(blade == "") SelectGeneratedItem(TGT_MARGINAL, B_ORDINARY, "");
			break;
			case "native" 		:
				blade = SelectGeneratedItem(TGT_YANKEE, "", "");
				if(blade == "") SelectGeneratedItem(TGT_MARGINAL, B_ORDINARY, "");
			break;
			case "marginal" 	:
				blade = SelectGeneratedItem(TGT_MARGINAL, B_ORDINARY, "");
			break;
			case "skeleton" 	:
				blade = SelectGeneratedItem(TGT_MARGINAL, B_ORDINARY, "");
			break;
			case "hunter" 		:
				if(rand(1) == 0 ) blade = SelectGeneratedItem(TGT_SOLDIER, "", "");
				else              blade = SelectGeneratedItem(TGT_MARGINAL, "", "");
			break;
			case "mercenary"	:
			break;
			case "governor" 	:
				blade = SelectGeneratedItem(TGT_OFFICER, "", "");
			break;
			case "itza" 		:
				blade = SelectGeneratedItem(TGT_NATIVE, "", "");
			break;
			case "quest" 		:
				blade = SelectGeneratedItem(TGT_SOLDIER, "", "");
			break;
			case "pofficer" 	:
				blade = SelectGeneratedItem(TGT_MARGINAL, B_ORDINARY, "");
			break;
			case "officer" 		:
				blade = SelectGeneratedItem(TGT_SOLDIER, B_ORDINARY, "");
			break;
			case "soldier"		:
				blade = SelectGeneratedItem(TGT_SOLDIER, B_ORDINARY, "");
			break;
			case "pirate"		:
				blade = SelectGeneratedItem(TGT_MARGINAL, "", "");
			break;
			case "citizen"		:
				blade = SelectGeneratedItem(TGT_MARGINAL, B_ORDINARY, "");
			break;
		}
	}
	else blade = SelectGeneratedItem(TGT_MARGINAL, B_ORDINARY, "");	
	return blade;
}
// казенная сабля солдат в городе
string LAi_Soldier_EquipBlade()
{	
	return SelectGeneratedItem(TGT_SOLDIER, "", "");
}

// new perks generator, more specialized (Gray 12.11.2004)
void LAi_NPC_EquipPerk(ref chr, string kind)
{
	int  i;
    int  rest;
    int  PerkTemplates[PERK_TEMPLATE_LAST];
    int  NumPerks[PERK_TEMPLATE_LAST];
    int  rank = sti(chr.rank);
    bool ok;

	for (i = 0; i < PERK_TEMPLATE_LAST; i++)
	{
		PerkTemplates[i] = 0;
	}

	switch (kind)        // to_do
	{
		 case "boatswain" :
			PerkTemplates[PERK_TEMPLATE_SHIPDEFENCE] = makeint((rank + rand(4)) / 7.0 + 1);
			PerkTemplates[PERK_TEMPLATE_GRAPPLING]   = makeint((rank + rand(3)) / 6.0);
			PerkTemplates[PERK_TEMPLATE_MELEE]       = makeint((rank + rand(3)) / 5.0);
		break;

		case "cannoner" :
			PerkTemplates[PERK_TEMPLATE_CANNONS] = makeint((rank + rand(2)) / 3.0 + 1);
			PerkTemplates[PERK_TEMPLATE_MELEE]   = makeint((rank + rand(3)) / 6.0);
		break;

		case "treasurer" :
			PerkTemplates[PERK_TEMPLATE_COMMERCE] = makeint((rank + rand(1)) / 5.0 + 1);
			PerkTemplates[PERK_TEMPLATE_REPAIR]   = makeint((rank + rand(3)) / 5.0);
			PerkTemplates[PERK_TEMPLATE_MELEE]    = makeint((rank + rand(3)) / 6.0);
			PerkTemplates[PERK_TEMPLATE_SHIPDEFENCE] = makeint((rank + rand(4)) / 7.0 + 1);
		break;

		case "navigator" :
			PerkTemplates[PERK_TEMPLATE_SAILING]     = makeint((rank + rand(2)) / 4.0 + 1);
			PerkTemplates[PERK_TEMPLATE_SHIPDEFENCE] = makeint((rank + rand(3)) / 6.0);
			PerkTemplates[PERK_TEMPLATE_MELEE]       = makeint((rank + rand(3)) / 6.0);
		break;

		case "fighter" :
			PerkTemplates[PERK_TEMPLATE_MELEE] = makeint((rank + rand(1)) / 2.0 + 1);
		break;

		case "fantom" : 
			PerkTemplates[PERK_TEMPLATE_MELEE]       = makeint((rank + rand(4)) / 4.0);
			PerkTemplates[PERK_TEMPLATE_SAILING]     = makeint((rank + rand(5)) / 8.0);
			PerkTemplates[PERK_TEMPLATE_GRAPPLING]   = makeint((rank + rand(7)) / 9.0);
			PerkTemplates[PERK_TEMPLATE_REPAIR]      = makeint((rank + rand(10)) / 15.0);
			PerkTemplates[PERK_TEMPLATE_CANNONS]     = makeint((rank + rand(2)) / 5.0);
			PerkTemplates[PERK_TEMPLATE_SHIPDEFENCE] = makeint((rank + rand(4)) / 7.0);
		break;
    } 

	NumPerks[PERK_TEMPLATE_SHIPDEFENCE] = 3;
	NumPerks[PERK_TEMPLATE_REPAIR]      = 4;
	NumPerks[PERK_TEMPLATE_CANNONS]     = 8;
	NumPerks[PERK_TEMPLATE_COMMERCE]    = 3;
	NumPerks[PERK_TEMPLATE_SAILING]     = 7;
	NumPerks[PERK_TEMPLATE_GRAPPLING]   = 5;
	NumPerks[PERK_TEMPLATE_MELEE]       = 11;
	NumPerks[PERK_TEMPLATE_PERSONAL]    = 4;

	rest = 0;
	for (i = 0; i < PERK_TEMPLATE_LAST; i++)
	{
		if (PerkTemplates[i] > NumPerks[i])
		{
			PerkTemplates[i] = NumPerks[i];
		}
		rest += NumPerks[i];
	}

	if (rest > rank)
	{
		rest = rank;
	}
	for (i = 0; i < PERK_TEMPLATE_LAST; i++)
	{
		rest = rest - PerkTemplates[i];
	}

	// the rest perks (like half usually) distributed randomly among templates
	while (rest > 0)
	{
		i = rand(PERK_TEMPLATE_LAST - 1);
		if (PerkTemplates[i] < NumPerks[i])
		{
			PerkTemplates[i] = PerkTemplates[i] + 1;
			rest--;
		}
	}


	if (PerkTemplates[PERK_TEMPLATE_SHIPDEFENCE] >= 1)
	{
		if (kind == "boatswain" || kind == "navigator")
		{
			chr.perks.list.Doctor1 = "1";
			if (PerkTemplates[PERK_TEMPLATE_SHIPDEFENCE] >= 2)
			{
				chr.perks.list.Doctor2 = "1";
			}
			if (PerkTemplates[PERK_TEMPLATE_SHIPDEFENCE] == 3)
			{	
				chr.perks.list.BasicBattleState = "1";			
			}
		}
		else
		{
			chr.perks.list.BasicBattleState = "1";
			if (PerkTemplates[PERK_TEMPLATE_SHIPDEFENCE] >= 2)
			{
				chr.perks.list.AdvancedBattleState = "1";
				if (PerkTemplates[PERK_TEMPLATE_SHIPDEFENCE] == 3)
				{
					if (kind == "fantom" || rand(1) == 1)
					{
						chr.perks.list.ShipDefenseProfessional = "1";
					}
				}
			}
		}
		if (kind == "fantom" || rand(2) == 1)
		{
			chr.perks.list.Doctor1 = "1";
			if (rand(2) == 1)
			{
				chr.perks.list.Doctor2 = "1";
			}
		}
	}

	if (PerkTemplates[PERK_TEMPLATE_REPAIR] >= 1)
	{
		chr.perks.list.Carpenter = "1";
		if (PerkTemplates[PERK_TEMPLATE_REPAIR] >= 2)
		{
			chr.perks.list.InstantRepair = "1";
		}
		if (PerkTemplates[PERK_TEMPLATE_REPAIR] >= 3)
		{
			chr.perks.list.LightRepair = "1";
			if (PerkTemplates[PERK_TEMPLATE_REPAIR] == 4) // mitrokosta & kokkai fix
			{
				chr.perks.list.Builder = "1";
			}
		}
	}

	if (PerkTemplates[PERK_TEMPLATE_CANNONS] >= 1)
	{
		chr.perks.list.HullDamageUp = "1";
		if (PerkTemplates[PERK_TEMPLATE_CANNONS] >= 2)
		{
			chr.perks.list.SailsDamageUp = "1";
			if (PerkTemplates[PERK_TEMPLATE_CANNONS] >= 3)
			{
				chr.perks.list.CrewDamageUp = "1";
				if (PerkTemplates[PERK_TEMPLATE_CANNONS] >= 4)
				{
					chr.perks.list.CriticalShoot = "1";
					if (PerkTemplates[PERK_TEMPLATE_CANNONS] >= 5)
					{
						chr.perks.list.FastReload = "1";
						if (PerkTemplates[PERK_TEMPLATE_CANNONS] >= 6)
						{
							chr.perks.list.LongRangeShoot = "1";
							if (PerkTemplates[PERK_TEMPLATE_CANNONS] >= 7)
							{
								chr.perks.list.CannonProfessional = "1";
								if (PerkTemplates[PERK_TEMPLATE_CANNONS] == 8)
								{
									chr.perks.list.ImmediateReload = "1";
								}
							}
						}
					}
				}
			}
		}
	}

	if (PerkTemplates[PERK_TEMPLATE_COMMERCE] >= 1)
	{
		chr.perks.list.BasicCommerce = "1";
		if (PerkTemplates[PERK_TEMPLATE_COMMERCE] >= 2)
		{
			chr.perks.list.AdvancedCommerce = "1";
		}
		if (PerkTemplates[PERK_TEMPLATE_COMMERCE] >= 3)
		{
			chr.perks.list.ProfessionalCommerce = "1";
		}
	}

	if (PerkTemplates[PERK_TEMPLATE_SAILING] >= 1)
	{
		chr.perks.list.ShipSpeedUp = "1";
		if (PerkTemplates[PERK_TEMPLATE_SAILING] >= 2)
		{
			chr.perks.list.ShipTurnRateUp = "1";
			if (PerkTemplates[PERK_TEMPLATE_SAILING] >= 3)
			{
				chr.perks.list.StormProfessional = "1";
				if (PerkTemplates[PERK_TEMPLATE_SAILING] >= 4)
				{
					chr.perks.list.SailsMan = "1";
				}
				if (PerkTemplates[PERK_TEMPLATE_SAILING] >= 5)
				{
					chr.perks.list.WindCatcher = "1";
				}
				if (PerkTemplates[PERK_TEMPLATE_SAILING] >= 6)
				{
					chr.perks.list.Turn180 = "1";
					if (PerkTemplates[PERK_TEMPLATE_SAILING] == 7)
					{
						chr.perks.list.SailingProfessional = "1";
					}				
				}					
			}
		}
	}

    ok = true;
	if (PerkTemplates[PERK_TEMPLATE_GRAPPLING] >= 1)
	{
		chr.perks.list.LongRangeGrappling = "1";
		if (PerkTemplates[PERK_TEMPLATE_GRAPPLING] >= 2)
		{
            if (rand(3) == 1)
            {
                chr.perks.list.MusketsShoot = "1";
                ok = false;
            }
            else
            {
                chr.perks.list.GrapplingProfessional = "1";
            }
			if (PerkTemplates[PERK_TEMPLATE_GRAPPLING] >= 3)
			{
                if (ok)
                {
                    if (rand(2) == 1)
                    {
                        chr.perks.list.MusketsShoot = "1";
                    }
                }
                else
                {
                    chr.perks.list.GrapplingProfessional = "1";
                }
			}
		}
		if (PerkTemplates[PERK_TEMPLATE_GRAPPLING] >= 4)
		{
			chr.perks.list.Brander = "1";
		}
		if (PerkTemplates[PERK_TEMPLATE_GRAPPLING] >= 5)
		{
			chr.perks.list.Troopers = "1";
		}
	}

	if (PerkTemplates[PERK_TEMPLATE_MELEE] >= 1)
	{
		chr.perks.list.BasicDefense = "1";
		if (PerkTemplates[PERK_TEMPLATE_MELEE] >= 2)
		{
			chr.perks.list.AdvancedDefense = "1";
			if (PerkTemplates[PERK_TEMPLATE_MELEE] >= 3)
			{
				chr.perks.list.CriticalHit = "1";
			}
			if (PerkTemplates[PERK_TEMPLATE_MELEE] >= 4)
			{
				chr.perks.list.Gunman = "1";
			}	
			if (PerkTemplates[PERK_TEMPLATE_MELEE] >= 5)
			{
				chr.perks.list.HardHitter = "1";
			}
			if (PerkTemplates[PERK_TEMPLATE_MELEE] >= 6)
			{
				chr.perks.list.Tireless = "1";
			}
			if (PerkTemplates[PERK_TEMPLATE_MELEE] >= 7)
			{
				chr.perks.list.Sliding = "1";
			}
			if (PerkTemplates[PERK_TEMPLATE_MELEE] >= 8)
			{
				chr.perks.list.BladeDancer = "1";
			}
			if (PerkTemplates[PERK_TEMPLATE_MELEE] >= 9)
			{
				chr.perks.list.SwordplayProfessional = "1";
			}
			if (PerkTemplates[PERK_TEMPLATE_MELEE] >= 10)
			{
				chr.perks.list.GunProfessional = "1";
			}
			if (PerkTemplates[PERK_TEMPLATE_MELEE] >= 11)
			{
				chr.perks.list.Grus = "1";
			}
		}
	}

	if (PerkTemplates[PERK_TEMPLATE_PERSONAL] >= 1)
	{
		chr.perks.list.ByWorker = "1";
		if (PerkTemplates[PERK_TEMPLATE_PERSONAL] >= 2)
		{
			chr.perks.list.IronWill = "1";
		}
		if (PerkTemplates[PERK_TEMPLATE_PERSONAL] >= 3)
		{
			chr.perks.list.ByWorker2 = "1";
		}
		if (PerkTemplates[PERK_TEMPLATE_PERSONAL] >= 4)
		{
			chr.perks.list.ShipEscape = "1";
		}
	}
}