#include "Weather\Init\Common.c"
#include "Weather\Init\Day.c"
#include "Weather\Init\Evening.c"
#include "Weather\Init\Morning.c"
#include "Weather\Init\Night.c"
#include "Weather\Init\DayStorm.c"
#include "Weather\Init\Special.c"
#include "Weather\Init\Rain.c" //navy

int InitWeather()
{
	int n = 0;

	n = Whr_InitNight(n);
	n = Whr_InitMorning(n);
	n = Whr_InitDay(n);
	n = Whr_InitEvening(n);
	n = Whr_InitDayStorm(n);
	n = Whr_InitSpecial(n);
	//n = Whr_InitRain(n);

	Whr_InitCommon();

	Trace("Init weathers complete. " + n + " weathers found.");

	for (int i=0; i<n; i++)
	{
		if (!CheckAttribute(&Weathers[i], "Stars.Enable")) { Weathers[i].Stars.Enable = false; }
		if (!CheckAttribute(&Weathers[i], "Planets.Enable")) { Weathers[i].Planets.Enable = false; }
		if (!CheckAttribute(&Weathers[i], "Sun.Reflection.Enable")) { Weathers[i].Sun.Reflection.Enable = false; }
		if (!CheckAttribute(&Weathers[i], "Sounds.Sea.Postfix")) { Weathers[i].Sounds.Sea.Postfix = ""; }
		if (!CheckAttribute(&Weathers[i], "Sun.Moon")) { Weathers[i].Sun.Moon = false; }

		if (!CheckAttribute(&Weathers[i], "Rain.DropsNearNum")) { Weathers[i].Rain.DropsNearNum = 0; };
		if (!CheckAttribute(&Weathers[i], "Rain.DropsFarNum")) { Weathers[i].Rain.DropsFarNum = 0; };
		if (!CheckAttribute(&Weathers[i], "Rain.DropsNearRadius")) { Weathers[i].Rain.DropsNearRadius = 12.0; };
		if (!CheckAttribute(&Weathers[i], "Rain.DropsFarRadius")) { Weathers[i].Rain.DropsFarRadius = 55.0; };
		if (!CheckAttribute(&Weathers[i], "Rain.DropsLifeTime")) { Weathers[i].Rain.DropsLifeTime = 0.25; };
		if (!CheckAttribute(&Weathers[i], "Rain.DropsSize")) { Weathers[i].Rain.DropsSize = 0.07; };
		if (!CheckAttribute(&Weathers[i], "Rain.DropsTexture")) { Weathers[i].Rain.DropsTexture = "weather\rain_drops.tga"; };
		if (!CheckAttribute(&Weathers[i], "Rain.DropsColor")) { Weathers[i].Rain.DropsColor = argb(63, 255, 255, 255); };

		if (!CheckAttribute(&Weathers[i], "Sea2.FoamK")) { Weathers[i].Sea2.FoamK = 0.0; };
		if (!CheckAttribute(&Weathers[i], "Sea2.FoamV")) { Weathers[i].Sea2.FoamV = 3.0; };
		if (!CheckAttribute(&Weathers[i], "Sea2.FoamUV")) { Weathers[i].Sea2.FoamUV = 3.0; };
		if (!CheckAttribute(&Weathers[i], "Sea2.FoamTexDisturb")) { Weathers[i].Sea2.FoamTexDisturb = 0.7; };
	}

	return n;
}
