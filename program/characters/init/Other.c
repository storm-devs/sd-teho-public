int CreateOtherCharacters(int n)
{
	ref ch;
	
	////////////////////////////////////////////////////////////////////////////////////////
	/// персонаж для ВАНО
	/// делаем его неписем для корректного отображения флага ГГ на шлюпке
	////////////////////////////////////////////////////////////////////////////////////////
	

	makeref(ch,Characters[n]);		// boat character  // boal

	ch.name 	= "Моряк";
	ch.lastname = "Моряк";
	ch.id		= "BoatChar";
	ch.nation	= ENGLAND;
	ch.activity_begin = "0";
	ch.activity_end = "24";
	ch.experience = "0";
	ch.Ship.Name = "Лодка";
	ch.Ship.Type = GenerateShip(SHIP_BOAT, 1);
	ch.Ship.Stopped = true;
	n = n + 1;
	
	return n;
}
