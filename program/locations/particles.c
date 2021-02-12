
#event_handler("StormReSynchronization", "StormReSynchronization");
#event_handler("RainReSynchronization", "RainReSynchronization");
#event_handler("RainAdditions", "RainAdditions");
#event_handler("CanonadaReSynchronization", "CanonadaReSynchronization");

void StormReSynchronization()
{
	float x = GetEventdata();
	float y = GetEventdata();
	float z = GetEventdata();
	int isBigStorm = GetEventData();

	if(CheckAttribute(loadedLocation, "storm"))
	{
		if(isBigStorm == 1)
		{
			if(sti(loadedLocation.storm) == 1)
			{
				CreateParticleSystem("storm", x, y, z,0,1.0,0,0);
			}
		}
		if(isBigStorm == 0)
		{
			if(sti(loadedLocation.storm) == 1)
			{
				CreateParticleSystem("small_storm", x, y, z,0,1.0,0,0);
			}
		}
	}
}

void CanonadaReSynchronization()
{
	float x = GetEventdata();
	float y = GetEventdata();
	float z = GetEventdata();
	CreateParticleSystem("ShipExplode", x, y, z,0,1.0,0,0);
	Play3DSound("ship_explosion", x, y, z);

	CreateParticleSystem("large_smoke", x, y, z, -1.57,0,0,0);
}

void RainReSynchronization()
{
	//aref locator = GetEventData();
	float x = GetEventdata();
	float y = GetEventdata();
	float z = GetEventdata();
	CreateParticleSystem("rain", x, y, z,0,1.0,0,0);

	for(int i = 0; i < 12; i ++)
	{
		PostEvent("RainAdditions", i * 300, "fffl", x,y,z, i);
	}
}

void RainAdditions()
{
	float x = GetEventdata();
	float y = GetEventdata();
	float z = GetEventdata();

	int i = GetEventData();

	if(CheckAttribute(loadedLocation, "rain_enable"))
	{
		switch(i)
		{
			case 0:
				CreateParticleSystem("rain",x + 1.0,y,z + 1.0,0,1.0,0,0);
			break;
			case 1:
				CreateParticleSystem("rain",x + 0.5,y,z + 0.5,0,1.0,0,0);
			break;
			case 2:
				CreateParticleSystem("rain",x - 0.5,y,z - 0.5,0,1.0,0,0);
			break;
			case 3:
				CreateParticleSystem("rain",x - 1.0,y,z - 1.0,0,1.0,0,0);
			break;

			case 4:
				CreateParticleSystem("rain",x - 1.0,y,z,0,1.0,0,0);
			break;
			case 5:
				CreateParticleSystem("rain",x + 0.5,y,z,0,1.0,0,0);
			break;
			case 6:
				CreateParticleSystem("rain",x + 1.0,y,z,0,1.0,0,0);
			break;
			case 7:
				CreateParticleSystem("rain",x - 0.5,y,z,0,1.0,0,0);
			break;

			case 8:
				CreateParticleSystem("rain",x,y,z - 1.0,0,1.0,0,0);
			break;
			case 9:
				CreateParticleSystem("rain",x,y,z + 0.5,0,1.0,0,0);
			break;
			case 10:
				CreateParticleSystem("rain",x,y,z + 1.0,0,1.0,0,0);
			break;
			case 11:
				CreateParticleSystem("rain",x,y,z - 0.5,0,1.0,0,0);
			break;
		}
	}
}



void CreateParticles(ref Location)
{
	aref locator_group;
	aref locator;
	int n;
	int num;
	
	// DumpAttributes(Location);

	if(!CheckAttribute(Location, "locators")) return;

    SendMessage(&Particles,"l", PS_CREATIONCAPTURE_BEG);
	/*
	if(CheckAttribute(Location, "locators.tavern_door"))
	{
		makearef(locator_group, location.locators.tavern_door);
		num = GetAttributesNum(locator_group);
		for(n = 0; n < num; n++)
		{
			locator = GetAttributeN(locator_group, n);
			//if(frnd() < 0.3 ) 
			CreateParticleSystem("signstar",stf(locator.x),stf(locator.y),stf(locator.z),-1.57,0,0,0);
			
			

		}
	}*/

	/*if(CheckAttribute(Location, "locators.stream"))
	{
		if(!CheckAttribute(Location, "stream_disable"))
		{
			makearef(locator_group, location.locators.stream);
			num = GetAttributesNum(locator_group);
			for(n = 0; n < num; n++)
			{
				locator = GetAttributeN(locator_group, n);
				CreateParticleSystem("stream",stf(locator.x),stf(locator.y),stf(locator.z),0.0,0.0,0.0,0);
			}
		}
	}*/

	if(CheckAttribute(Location, "locators.ship_foam"))
	{
		makearef(locator_group, location.locators.ship_foam);
		num = GetAttributesNum(locator_group);
		for(n = 0; n < num; n++)
		{
			locator = GetAttributeN(locator_group, n);
			CreateParticleSystem("ship_foam",stf(locator.x),stf(locator.y),stf(locator.z),-1.57,0,0,0);
			
			

		}
	}

	if(CheckAttribute(Location, "locators.storm"))
	{
		if(bCurWeatherStorm == true)
		{
			location.oldtype = location.type;
			location.type = "slave_deck";
			if(!CheckAttribute(Location, "storm_disable"))
			{
				makearef(locator_group, location.locators.storm);
				num = GetAttributesNum(locator_group);
				for(n = 0; n < num; n++)
				{
					locator = GetAttributeN(locator_group, n);
					PostEvent("StormReSynchronization", n * 1000, "fffl", stf(locator.x), stf(locator.y), stf(locator.z), 1);
				}
			}
		}
		else
		{
			if(CheckAttribute(&location, "oldtype"))
			{
				location.type = location.oldtype;
			}

		}
	}

	if(CheckAttribute(Location, "locators.storm_small"))
	{
		if(!CheckAttribute(Location, "storm_disable"))
		{
			makearef(locator_group, location.locators.storm_small);
			num = GetAttributesNum(locator_group);
			for(n = 0; n < num; n++)
			{
				locator = GetAttributeN(locator_group, n);
				PostEvent("StormReSynchronization", n * 1000, "fffl", stf(locator.x), stf(locator.y), stf(locator.z), 0);
			}
		}
	}

	if(CheckAttribute(Location, "locators.rain"))
	{
		if(!CheckAttribute(Location, "rain_disable"))
		{
			makearef(locator_group, location.locators.rain);
			num = GetAttributesNum(locator_group);
			for(n = 0; n < num; n++)
			{
				locator = GetAttributeN(locator_group, n);
				PostEvent("RainReSynchronization", n * 100, "fff", stf(locator.x), stf(locator.y), stf(locator.z));
			}
		}
	}

	if(CheckAttribute(Location, "locators.waterfall"))
	{
		makearef(locator_group, location.locators.waterfall);
		num = GetAttributesNum(locator_group);
		for(n = 0; n < num; n++)
		{
			locator = GetAttributeN(locator_group, n);
			CreateParticleSystemX("waterfall",stf(locator.x),stf(locator.y),stf(locator.z),
				stf(locator.vz.x),stf(locator.vz.y),stf(locator.vz.z),0);
		}
	}

//Ursus
	if(CheckAttribute(Location, "locators.bubbles"))
	{
		makearef(locator_group, location.locators.bubbles);
		num = GetAttributesNum(locator_group);
		for(n = 0; n < num; n++)
		{
			locator = GetAttributeN(locator_group, n);
			CreateParticleSystemX("bubbles",stf(locator.x),stf(locator.y),stf(locator.z),
				stf(locator.vz.x),stf(locator.vz.y),stf(locator.vz.z),0);
		}
	}
	
		if(CheckAttribute(Location, "locators.fishblue"))
	{
		makearef(locator_group, location.locators.fishblue);
		num = GetAttributesNum(locator_group);
		for(n = 0; n < num; n++)
		{
			locator = GetAttributeN(locator_group, n);
			CreateParticleSystemX("fishblue",stf(locator.x),stf(locator.y),stf(locator.z),
				stf(locator.vz.x),stf(locator.vz.y),stf(locator.vz.z),0);
		}
	}
	
		{
		makearef(locator_group, location.locators.shadowstar);
		num = GetAttributesNum(locator_group);
		for(n = 0; n < num; n++)
		{
			locator = GetAttributeN(locator_group, n);
			CreateParticleSystemX("shadowstar",stf(locator.x),stf(locator.y),stf(locator.z),
				stf(locator.vz.x),stf(locator.vz.y),stf(locator.vz.z),0);
		}
	}
	
//Ursus





/*	if(CheckAttribute(Location, "locators.reload"))
	{
		makearef(locator_group, location.locators.reload);
		num = GetAttributesNum(locator_group);
		for(n = 0; n < num; n++)
		{
			locator = GetAttributeN(locator_group, n);
			CreateParticleSystem("fire_mix",stf(locator.x),stf(locator.y),stf(locator.z),-1.57,0,0,0);
		}
	}
*/
	if(CheckAttribute(Location, "locators.fountains"))
	{
		makearef(locator_group, location.locators.fountains);
		num = GetAttributesNum(locator_group);
		for(n = 0; n < num; n++)
		{
			locator = GetAttributeN(locator_group, n);
			//CreateParticleSystem("fountain",stf(locator.x),stf(locator.y),stf(locator.z),-1.57,0,0,0);
			CreateParticleSystemX("fountain",stf(locator.x),stf(locator.y),stf(locator.z),
				stf(locator.vz.x),stf(locator.vz.y),stf(locator.vz.z),0);
		}
	}
	
	if(CheckAttribute(Location, "locators.Waterfog"))
	{
		makearef(locator_group, location.locators.waterfog);
		num = GetAttributesNum(locator_group);
		for(n = 0; n < num; n++)
		{
			locator = GetAttributeN(locator_group, n);
			CreateParticleSystemX("waterfog",stf(locator.x),stf(locator.y),stf(locator.z),
				stf(locator.vz.x),stf(locator.vz.y),stf(locator.vz.z),0);
		}
	}

	if(CheckAttribute(Location, "locators.Waterfogfall"))
	{
		makearef(locator_group, location.locators.waterfogfall);
		num = GetAttributesNum(locator_group);
		for(n = 0; n < num; n++)
		{
			locator = GetAttributeN(locator_group, n);
			CreateParticleSystemX("waterfog_fall",stf(locator.x),stf(locator.y),stf(locator.z),
				stf(locator.vz.x),stf(locator.vz.y),stf(locator.vz.z),0);
		}
	}

	if(CheckAttribute(Location, "locators.stars"))
	{
		makearef(locator_group, location.locators.stars);
		num = GetAttributesNum(locator_group);
		for(n = 0; n < num; n++)
		{
			locator = GetAttributeN(locator_group, n);
			CreateParticleSystemX("stars",stf(locator.x),stf(locator.y),stf(locator.z),
				stf(locator.vz.x),stf(locator.vz.y),stf(locator.vz.z),0);
		}
	}

    if(CheckAttribute(Location, "locators.smoke") && !CheckAttribute(Location, "hidden_effects"))
	{
		makearef(locator_group, location.locators.smoke);
		num = GetAttributesNum(locator_group);
		for(n = 0; n < num; n++)
		{
			locator = GetAttributeN(locator_group, n);
			if(frnd() < 0.3 ) CreateParticleSystem("smoke",stf(locator.x),stf(locator.y),stf(locator.z),-1.57,0,0,0);
		}
	}

 	if(CheckAttribute(Location, "locators.fire"))
	{
		makearef(locator_group, location.locators.fire);
		num = GetAttributesNum(locator_group);
		for(n = 0; n < num; n++)
		{
			locator = GetAttributeN(locator_group, n);
			CreateParticleSystem("fire",stf(locator.x),stf(locator.y),stf(locator.z),-1.57,0,0,0);
		}
	}


    if(CheckAttribute(Location, "locators.torchlightes_p"))
	{
		makearef(locator_group, location.locators.torchlightes_p);
		num = GetAttributesNum(locator_group);
		for(n = 0; n < num; n++)
		{
			locator = GetAttributeN(locator_group, n);
			CreateParticleSystem("torch",stf(locator.x),stf(locator.y) - 0.07,stf(locator.z),-1.57,0,0,0);
		}
	}

	if(CheckAttribute(Location, "locators.torchlightes_o_p") && Whr_IsLight() != 0)
	{
		makearef(locator_group, location.locators.torchlightes_o_p);
		num = GetAttributesNum(locator_group);
		for(n = 0; n < num; n++)
		{
			locator = GetAttributeN(locator_group, n);
			CreateParticleSystem("torch",stf(locator.x),stf(locator.y) - 0.07,stf(locator.z),-1.57,0,0,0);
		}
	}
	
	if(CheckAttribute(Location, "locators.fortfire_s"))
	{
		makearef(locator_group, location.locators.fortfire_s);
		num = GetAttributesNum(locator_group);
		for(n = 0; n < num; n++)
		{
			locator = GetAttributeN(locator_group, n);
			CreateParticleSystemX("shipfire",stf(locator.x),stf(locator.y),stf(locator.z),
				stf(locator.vz.x),stf(locator.vz.y),stf(locator.vz.z),0);
		}
	}

	if(CheckAttribute(Location, "locators.candles_p"))
	{
		makearef(locator_group, location.locators.candles_p);
		num = GetAttributesNum(locator_group);
		for(n = 0; n < num; n++)
		{
			locator = GetAttributeN(locator_group, n);
			//Candles_p =   // boal нигде не используется
			CreateParticleSystem("candle",stf(locator.x),stf(locator.y) + 0.04,stf(locator.z),-1.57,0,0,0);
		}
	}


	if(CheckAttribute(Location, "locators.fortfire"))
	{
		makearef(locator_group, location.locators.fortfire);
		num = GetAttributesNum(locator_group);
		for(n = 0; n < num; n++)
		{
			locator = GetAttributeN(locator_group, n);
			//Fortfire_p =   // boal
			CreateParticleSystemX("fortfire",stf(locator.x),stf(locator.y),stf(locator.z),
				stf(locator.vz.x),stf(locator.vz.y),stf(locator.vz.z),0);
		}
	}
		/* if(CheckAttribute(Location, "locators.fortsmoke"))
	{
		makearef(locator_group, location.locators.fortsmoke);
		num = GetAttributesNum(locator_group);
		for(n = 0; n < num; n++)
		{
			locator = GetAttributeN(locator_group, n);
			CreateParticleSystemX("fire_from_hole",stf(locator.x),stf(locator.y),stf(locator.z),
				stf(locator.vz.x),stf(locator.vz.y),stf(locator.vz.z),0);
		}
	} */
	
	if(CheckAttribute(Location, "locators.torch_deck"))
	{
		makearef(locator_group, location.locators.torch_deck);
		num = GetAttributesNum(locator_group);
		for(n = 0; n < num; n++)
		{
			locator = GetAttributeN(locator_group, n);
			//Torch_deck_p =  // boal
			CreateParticleSystemX("torch",stf(locator.x),stf(locator.y),stf(locator.z),
				stf(locator.vz.x),stf(locator.vz.y),stf(locator.vz.z),0);
			//Trace("Torch_deck created");
		}
	}
	//eddy. новые партиклы
	if(CheckAttribute(Location, "locators.shipfire_big"))
	{
		makearef(locator_group, location.locators.shipfire_big);
		num = GetAttributesNum(locator_group);
		for(n = 0; n < num; n++)
		{
			locator = GetAttributeN(locator_group, n);
			CreateParticleSystemX("shipfire1",stf(locator.x),stf(locator.y),stf(locator.z),
				stf(locator.vz.x),stf(locator.vz.y),stf(locator.vz.z), 0);
			//Trace("shipfire_deck created");
		}
	}

	if(CheckAttribute(Location, "locators.large_smoke"))
	{
		makearef(locator_group, location.locators.large_smoke);
		num = GetAttributesNum(locator_group);
		for(n = 0; n < num; n++)
		{
			locator = GetAttributeN(locator_group, n);
			CreateParticleSystemX("large_smoke",stf(locator.x),stf(locator.y),stf(locator.z),
				stf(locator.vz.x),stf(locator.vz.y),stf(locator.vz.z), 0);
		}
	}

	if(CheckAttribute(Location, "locators.hid_torchSmoke") && CheckAttribute(Location, "hidden_effects"))
	{
		makearef(locator_group, location.locators.hid_torchSmoke);
		num = GetAttributesNum(locator_group);
		for(n = 0; n < num; n++)
		{
			locator = GetAttributeN(locator_group, n);
			CreateParticleSystemX("large_smoke",stf(locator.x),stf(locator.y),stf(locator.z),
				stf(locator.vz.x),stf(locator.vz.y),stf(locator.vz.z), 0);
			CreateParticleSystemX("torch",stf(locator.x),stf(locator.y),stf(locator.z),
				stf(locator.vz.x),stf(locator.vz.y),stf(locator.vz.z),0);
			SendMessage(Sound, "lsllllllfff", MSG_SOUND_PLAY, "torch_deck", SOUND_WAV_3D, VOLUME_FX, 
				0, 1, 0, 0, stf(locator.x), stf(locator.y), stf(locator.z));

		}
	}

	if(CheckAttribute(Location, "locators.hid_fire") && CheckAttribute(Location, "hidden_effects"))
	{
		makearef(locator_group, location.locators.hid_fire);
		num = GetAttributesNum(locator_group);
		for(n = 0; n < num; n++)
		{
			locator = GetAttributeN(locator_group, n);
			CreateParticleSystemX("shipfire",stf(locator.x),stf(locator.y),stf(locator.z),
				stf(locator.vz.x),stf(locator.vz.y),stf(locator.vz.z), 0);
			SendMessage(Sound, "lsllllllfff", MSG_SOUND_PLAY, "fortfire", SOUND_WAV_3D, VOLUME_FX, 
				0, 1, 0, 0, stf(locator.x), stf(locator.y), stf(locator.z));

		}
	}

	if(CheckAttribute(Location, "locators.burn")) // Jason
	{
		makearef(locator_group, location.locators.burn);
		num = GetAttributesNum(locator_group);
		for(n = 0; n < num; n++)
		{
			locator = GetAttributeN(locator_group, n);
			if (CheckAttribute(Location, "hidden_fire"))
			{
				CreateParticleSystemX("shipfire",stf(locator.x),stf(locator.y),stf(locator.z), stf(locator.vz.x),stf(locator.vz.y),stf(locator.vz.z), 0);
				CreateParticleSystemX("large_smoke",stf(locator.x),stf(locator.y),stf(locator.z), stf(locator.vz.x),stf(locator.vz.y),stf(locator.vz.z), 0);
			}
			if (CheckAttribute(Location, "hidden_sound")) SendMessage(Sound, "lsllllllfff", MSG_SOUND_PLAY, "fortfire", SOUND_WAV_3D, VOLUME_FX, 0, 1, 0, 0, stf(locator.x), stf(locator.y), stf(locator.z));
		}
	}

	if(CheckAttribute(Location, "locators.fire_incas")) // Tymofei & Jason
	{
		makearef(locator_group, location.locators.fire_incas);
		num = GetAttributesNum(locator_group);
		for(n = 0; n < num; n++)
		{
			locator = GetAttributeN(locator_group, n);
			CreateParticleSystem("fire_incas",stf(locator.x),stf(locator.y),stf(locator.z),0,0,0,0);
		}
	}

	CreateHeaters(Location);

	SendMessage(&Particles,"l", PS_CREATIONCAPTURE_END);

	Particles.winddirection.y = 0;
}

void CreateHeaters(aref Location)
{
	aref locator_group;
	int num;
	aref locator;
	float x, y, z;
	bool bLandfire = false;
	
	if(CheckAttribute(Location, "locators.landfire"))
	{
		bLandfire = true;
	}
	
	if(CheckAttribute(Location, "locators.heaters_p"))
	{
		bool isHeatersEnable = true;
		if(CheckAttribute(location, "heaters_night_only"))
		{			
			if(CheckAttribute(&Weathers[iCurWeatherNum], "Lights"))
			{
				if(sti(Weathers[iCurWeatherNum].Lights) == 0)
				{
					isHeatersEnable = false;
				}
			}			
		}
		if(CheckAttribute(location, "heaters_disable"))
		{
			if(sti(location.heaters_disable) == 1)
			{
				isHeatersEnable = false;
			}
		}

		if(isHeatersEnable == true)
		{
			makearef(locator_group, location.locators.heaters_p);
			num = GetAttributesNum(locator_group);
			for(int n = 0; n < num; n++)
			{
				locator = GetAttributeN(locator_group, n);
	
				x = stf(locator.x);
				y = stf(locator.y);
				z = stf(locator.z);
				
				if(bLandfire)
				{
					CreateParticleSystem("Fire",  x, y + 0.15, z, -1.57, 0,  0,  0); // Огонь
					CreateParticleSystem("Fire",  x, y + 0.30, z, -1.57, 0,  0,  0); // Для пущей красоты создаем два партикла
					CreateParticleSystem("Smoke", x, y + 0.30, z, -1.57, 0,  0,  0); // Дым
				}	
				else
				{
					CreateParticleSystem("fire",x,y,z,-1.57,0,0,0);
				}	
			}
		}
	}
}

void LaunchCananada()
{
	ref location = &Locations[FindLocation(pchar.location)];

	int num;
	aref locator;
	aref locator_group;
	
	if(CheckAttribute(Location, "locators.Cannon_explode"))
	{
		bool isHeatersEnable = true;

		makearef(locator_group, location.locators.Cannon_explode);
		num = GetAttributesNum(locator_group);
		for(int n = 0; n < num; n++)
		{
			locator = GetAttributeN(locator_group, n);
			PostEvent("CanonadaReSynchronization", n * 2000, "fff", stf(locator.x), stf(locator.y), stf(locator.z));
		}
	}
}

// Warship. Создаем партикл огня + дым
bool CreateFireParticles(string sGroup, string sLocator)
{
	ref rLoc = &locations[FindLocation(PChar.location)];
	
	float x = stf(rLoc.locators.(sGroup).(sLocator).x);
	float y = stf(rLoc.locators.(sGroup).(sLocator).y);
	float z = stf(rLoc.locators.(sGroup).(sLocator).z);
	
	CreateParticleSystemX("Fire", x, y+0.15, z, x, y+0.15, z, 0); // Огонь
	CreateParticleSystemX("Fire", x, y+0.3, z, x, y+0.3, z, 0); // Для пущей красоты создаем два партикла
	CreateParticleSystemX("Smoke", x, y+1.15, z, x, y+1.15, z, 0); // Дым
	return true;
}

// Jason: универсальный создатель партиклов в локации ручным способом. Создает партикл в указанном локаторе или рядом с ним по оси Y и добавляет звук. up - на сколько над локатором должен быть поднят/опущен партикл. ax и az - корректировщики для соотв. осей при ориентировании направленных партиклов. Звуки брать из алиаса. Список некоторых партикловых схем: blood/blood_big - брызги крови, stream - ручеек, Splash - водный всплеск, item - фиолетовая крутящаяся звезда, Firering - мигающее желтое мистическое кольцо, Ship_cannon_fire - выстрел из пушки, blast_inv/Bombard - вспышка+дым, blast/blast_dirt - взрыв с летающими какашками, GunFire - выстрел из пистоля, fountain - фонтан, bubbles - пузыри, fishblue - косяк рыбок, shipfire - большой огонь, torch - факел, shadowstar - теневая звезда, large_smoke - большой дым, smoke - дым, ShipExplode - взрыв
bool CreateLocationParticles(string sParticle, string sGroup, string sLocator, float up, float ax, float az, string sSound)
{
	ref rLoc = &locations[FindLocation(PChar.location)];
	
	float x = stf(rLoc.locators.(sGroup).(sLocator).x);
	float y = stf(rLoc.locators.(sGroup).(sLocator).y);
	float z = stf(rLoc.locators.(sGroup).(sLocator).z);
	
	CreateParticleSystemX(sParticle, x, y+up, z, x+ax, y+up, z+az, 0);
	Play3DSound(sSound, x, y, z);
	return true;
}

void StartTorchesInTown(aref location)
{
	if(!CheckAttribute(Location, "locators")) return;
	
	aref locator_group;
	aref locator;
	int n;
	int num;
	
	if(CheckAttribute(Location, "locators.torchlightes_p"))
	{
		makearef(locator_group, location.locators.torchlightes_p);	
		num = GetAttributesNum(locator_group);
		for(n = 0; n < num; n++)
		{
			locator = GetAttributeN(locator_group, n);
			CreateParticleSystem("torch", stf(locator.x), stf(locator.y) - 0.07, stf(locator.z), -1.57, 0.0, 0.0, 0);
		}		
	}
	if(CheckAttribute(Location, "locators.torchlightes_o_p") && Whr_IsLight() != 0)
	{
		makearef(locator_group, location.locators.torchlightes_o_p);
		num = GetAttributesNum(locator_group);
		for(n = 0; n < num; n++)
		{
			locator = GetAttributeN(locator_group, n);
			CreateParticleSystem("torch", stf(locator.x), stf(locator.y) - 0.07, stf(locator.z), -1.57, 0.0, 0.0, 0);
		}
	}
}

void StartFireRing()
{
	aref locator_group;
	aref locator;
	int n, num;
	ref Location;
	
	Location = &Locations[FindLocation(pchar.location)];
	if(CheckAttribute(Location, "locators.town_exposion"))
	{
		makearef(locator_group, location.locators.town_exposion);
		num = GetAttributesNum(locator_group);
		for(n = 0; n < num; n++)
		{
			locator = GetAttributeN(locator_group, n);
			CreateParticleSystemX("town_explodion",stf(locator.x),stf(locator.y),stf(locator.z), 0.0, 0.0, 0.0, 0);
		}
	}
}

void StartPozhar()
{
	aref locator_group;
	aref locator;
	int n, num;
	ref Location;
	
	Location = &Locations[FindLocation(pchar.location)];
	if(CheckAttribute(Location, "locators.pozhar"))
	{
		makearef(locator_group, location.locators.pozhar);
		num = GetAttributesNum(locator_group);
		for(n = 0; n < num; n++)
		{
			locator = GetAttributeN(locator_group, n);
			CreateParticleSystemX("pozhar",stf(locator.x),stf(locator.y),stf(locator.z),
				stf(locator.vz.x),stf(locator.vz.y),stf(locator.vz.z),0);
		}
	}
}

void LaunchSingleBoom(int iLocNum)
{
	ref location = &Locations[FindLocation(pchar.location)];
	int num;
	aref locator;
	aref locator_group;
	
	if(CheckAttribute(Location, "locators.single_explode"))
	{		
		makearef(locator_group, location.locators.Single_explode);
		int n = iLocNum-1;
		locator = GetAttributeN(locator_group, n);
		if(CheckAttribute(&locator, "x") && CheckAttribute(&locator, "y") && CheckAttribute(&locator, "z"))
		{
			CreateParticleSystem("ShipExplode", stf(locator.x), stf(locator.y), stf(locator.z), 0.0, 1.0, 0.0, 0);
			Play3DSound("scene_ship_explosion", stf(locator.x), stf(locator.y), stf(locator.z));
			CreateParticleSystem("large_smoke", stf(locator.x), stf(locator.y), stf(locator.z), 0.0, 0.0, 0.0, 0);
		}
	}
}