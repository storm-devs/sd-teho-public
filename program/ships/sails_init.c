void InitSailsColors()
{
	// в КВЛ 1.2.3 переделано использование  icon и texture не используются, принцип радуга + белый и черный
	// нужно только name и color 
	SailsColors[0].icon = "interfaces\sails\blue.tga";
	SailsColors[0].texture = "parus_blue";
	SailsColors[0].name  = "White";
	SailsColors[0].color = argb(255, 255, 255, 255);

	SailsColors[1].icon = "interfaces\sails\green.tga";
	SailsColors[1].texture = "parus_green";
	SailsColors[1].name  = "Red";
	SailsColors[1].color = argb(255, 255, 60, 60);

	SailsColors[2].icon = "interfaces\sails\red.tga";
	SailsColors[2].texture = "parus_red";
	SailsColors[2].name  = "Orange";
	SailsColors[2].color = argb(255, 255, 128, 60);

	SailsColors[3].icon = "interfaces\sails\yellow.tga";
	SailsColors[3].texture = "parus_yellow";
	SailsColors[3].name  = "Yellow";
	SailsColors[3].color = argb(255, 255, 255, 60);

	SailsColors[4].icon = "interfaces\sails\lilo.tga";
	SailsColors[4].texture = "parus_lilo";
	SailsColors[4].name  = "Green";
	SailsColors[4].color = argb(255, 60, 255, 60);

	SailsColors[5].icon = "interfaces\sails\gray.tga";
	SailsColors[5].texture = "parus_gray";
	SailsColors[5].name  = "Blue";
	SailsColors[5].color = argb(255, 128, 190, 255);

	SailsColors[6].icon = "interfaces\sails\white.tga";
	SailsColors[6].texture = "parus_white";
	SailsColors[6].name  = "Dark Blue";
	SailsColors[6].color = argb(255, 60, 60, 255);

	SailsColors[7].icon = "interfaces\sails\black.tga";
	SailsColors[7].texture = "parus_black";
	SailsColors[7].name  = "Violet";
	SailsColors[7].color = argb(255, 255, 60, 255);
	
	SailsColors[8].icon = "interfaces\sails\black.tga";
	SailsColors[8].texture = "parus_black";
	SailsColors[8].name  = "Black";
	SailsColors[8].color = argb(255, 60, 60, 60);
}
